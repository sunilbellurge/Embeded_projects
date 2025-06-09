#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

//Consider Dummy register set for UART and LED
//
typedef struct{
        uint32_t ModeR;
        uint32_t ODR;
}GPIO_output;

typedef struct{
        uint32_t SR;//status register
        uint32_t DR;//Data Register
        uint32_t CR; //Control Register
}uart;

void GPIO_config(GPIO_output *gpioA){
        gpioA->ModeR |= (0x1111<<0);  //Output Mode
        //gpioA->ODR |=(0x0000<<4);     // Set or clear;
}
void GPIO_write(GPIO_output *gpioA,int value,int pin){
        if(value){
                gpioA->ODR |= (1<<pin);
        }else{
                gpioA->ODR |=(0<<pin);
        }
}
void UART_init(uart *ux){
   ux->SR = 0x01;
   ux->CR= 0x80; // TX is ready
}

void UART_tx(uart *ux , char c){
        while(!(ux->CR & 0x80));
        ux->DR = c;
        printf("The Data is %c\n",ux->DR);
}

void sendchar(uart *ux ,char *c){
        whiel(*c){
                UART_tx(ux,*c++);
        }
}
typedef struct {
        int pin;
        GPIO_output *gpiox;
        int value;
}wrapper;
void *LEDON(void *args){
     wrapper *gpioA=(wrapper *) args;
     GPIO_config(gpioA->gpiox);
     while(1){
     GPIO_write(gpioA->gpiox,gpioA->value , gpioA->pin);
     if(gpioA->value ==1){
             printf("LED is On....\n");
    }else{
            printf("LED is Off....\n");
}}