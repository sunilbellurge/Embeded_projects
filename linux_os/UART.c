#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

// Dummy register set for UART and LED
pthread_mutex_t lock;
pthread_cond_t wait;

typedef struct {
    uint32_t ModeR;
    uint32_t ODR;
} GPIO_output;

typedef struct {
    uint32_t SR; // Status Register
    uint32_t DR; // Data Register
    uint32_t CR; // Control Register
} uart;

void GPIO_config(GPIO_output *gpioA) {
    gpioA->ModeR |= (0x1111 << 0);  // Output Mode
}

void GPIO_write(GPIO_output *gpioA, int value, int pin) {
    if (value) {
        gpioA->ODR |= (1 << pin); // Set pin
    } else {
        gpioA->ODR &= ~(1 << pin); // Clear pin (❗ you had |= with 0 which does nothing)
    }
}

void UART_init(uart *ux) {
    ux->SR = 0x01;
    ux->CR = 0x80; // TX ready
}

void UART_tx(uart *ux, char c) {
    while (!(ux->CR & 0x80));
    ux->DR = c;
    printf("The Data is %c\n", ux->DR);
}

void sendchar(uart *ux, char *c) {
    int n = strlen(c);
    int i = 0;
    while (i < n) {
        UART_tx(ux, c[i]);
        i++;
    }
}

typedef struct {
    int pin;
    GPIO_output *gpiox;
    int value;
} wrapper;

typedef struct {
    char *ch;
    uart *uartx;
} uartWrapper;

int uart_send = 0;

void *LEDON(void *args) {
    wrapper *gpioA = (wrapper *) args;
    GPIO_config(gpioA->gpiox);
    while (1) {
        pthread_mutex_lock(&lock);
        while (uart_send != 0) {
            pthread_cond_wait(&wait, &lock); // ❗ You had signal instead of wait
        }

        uart_send = 1;
        GPIO_write(gpioA->gpiox, gpioA->value, gpioA->pin);
        if (gpioA->value == 1) {
            printf("LED is On....\n");
        } else {
            printf("LED is Off....\n");
        }
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&wait);
        sleep(1); // Optional: to prevent CPU spinning
    }
    return NULL;
}

void *UARTSEND(void *args) {
    uartWrapper *uartxx = (uartWrapper *) args;
    while (1) {
        pthread_mutex_lock(&lock);
        UART_init(uartxx->uartx);

        while (uart_send != 1) {
            pthread_cond_wait(&wait, &lock);
        }

        sendchar(uartxx->uartx, uartxx->ch);
        uart_send = 0;

        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&wait);
        sleep(1); // Optional: simulate delay
    }
    return NULL;
}

int main() {
    pthread_t UART_TASK, BLINKER;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&wait, NULL);

    GPIO_output *GPIO1 = malloc(sizeof(GPIO_output));
    uart *uart1 = malloc(sizeof(uart));
    char *ch = "Sunil Bellurge";

    wrapper *wrapper1 = malloc(sizeof(wrapper));
    wrapper1->gpiox = GPIO1;
    wrapper1->pin = 5;
    wrapper1->value = 1;

    uartWrapper *uartwrapper1 = malloc(sizeof(uartWrapper));
    uartwrapper1->uartx = uart1;
    uartwrapper1->ch = ch;

    pthread_create(&BLINKER, NULL, &LEDON, wrapper1);
    pthread_create(&UART_TASK, NULL, &UARTSEND, uartwrapper1);

    pthread_join(BLINKER, NULL);
    pthread_join(UART_TASK, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&wait);

    free(GPIO1);
    free(uart1);
    free(wrapper1);
    free(uartwrapper1);

    return 0;
}
