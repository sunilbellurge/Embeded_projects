#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<pthread.h>
#include<time.h>

//Dummy Register set for LED toggle ;
typedef struct {
        uint32_t LED_cntrl ;   //0 off and 1 On
        uint32_t LED_status ; //Current status
}LED_Blinker ;

int GLOBLE_CHECKER ;
typedef struct {
        uint32_t CAN_CNTRL ; //Bit is '0' Enable and Bit 1 loop
        uint32_t CAN_STATUS; //'0' Tx and '1' Rx
        char *CAN_TXDATA; //Transmitt Buffer
        char *CAN_RXDATA; // receive Buffer
}CAN_Controller;

typedef struct {
        uint32_t error_code;
        uint32_t last_status_timing;
}CAN_diagnostic;

void sleep_ms(int milliseconds) {
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1e6;
    nanosleep(&ts, NULL);
}
int current_led_state(LED_Blinker *led1){
    led1->LED_cntrl ^=1;
        if(led1->LED_cntrl ==1){
                GLOBLE_CHECKER=1;
                return 1 ;

        }else{
                GLOBLE_CHECKER=0;
                return 0;
        }
}

void CAN_init(CAN_Controller *CAN1,int RXorTX)
{
        if(GLOBLE_CHECKER==1){
             CAN1->CAN_CNTRL =1;//Enable the
        }else{

                 CAN1->CAN_CNTRL =1;
        }

        if(RXorTX ==1){
                CAN1->CAN_STATUS = 1;
        }else{
                 CAN1->CAN_STATUS = 0;
        }

}
volatile int res;
void *LED_BLINK(void *args)
{
        LED_Blinker *LED1=(LED_Blinker *) args;
        while(1){
                res= current_led_state(LED1);

               sleep_ms(10);
}}
void *CAN_CONTROLLER(void *args){
    CAN_Controller *CANx=(CAN_Controller *) args;
    int bit;
    while(1){
        bit = rand() % 2;
        CAN_init(CANx,bit);
        if(res==1){
                CANx->CAN_TXDATA="The LED IS ON";
        }else{
                CANx->CAN_TXDATA="Ooooooops LED IS OFF";
        }

        printf("%s\n" ,CANx->CAN_TXDATA);


    sleep_ms(10);
}}

int main()

{
        srand(time(NULL));
        pthread_t LED , CAN ;
        LED_Blinker Blinker;
        CAN_Controller CANxx;

        pthread_create(&LED , NULL , &LED_BLINK ,&Blinker);
        pthread_create(&CAN , NULL , &CAN_CONTROLLER,&CANxx);

        pthread_join(LED , NULL);
        pthread_join(CAN , NULL);
}