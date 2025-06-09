#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    float temperature;
    float pressure;
    pthread_mutex_t lock;
} sensor_data;

sensor_data sensor = {0};

void* read_temperature(void* args) {
    while (1) {
        pthread_mutex_lock(&sensor.lock);
        sensor.temperature = 25.0 + (rand() % 100) / 10.0;
        pthread_mutex_unlock(&sensor.lock);
        printf("Temperature updated\n");
        usleep(100000); // 100ms
    }
    return NULL;
}

void* read_pressure(void* args) {
    while (1) {
        pthread_mutex_lock(&sensor.lock);
        sensor.pressure = (rand() % 100) / 10.0;
        pthread_mutex_unlock(&sensor.lock);
        printf("Pressure updated\n");
        usleep(100000); // 100ms
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&sensor.lock, NULL);

    pthread_create(&t1, NULL, read_temperature, NULL);
    pthread_create(&t2, NULL, read_pressure, NULL);

    int count = 0;
    while (count < 200) {
        pthread_mutex_lock(&sensor.lock);
        printf("Reading %d: Temperature = %.2f°C, Pressure = %.2f bar\n", count + 1, sensor.temperature, sensor.pressure);
        pthread_mutex_unlock(&sensor.lock);
        count++;
        usleep(200000); // 200ms
    }

    // In a real app, you'd use a signal to stop threads, here we exit forcefully
    pthread_cancel(t1);
    pthread_cancel(t2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&sensor.lock);

    return 0;
}
