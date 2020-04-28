#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <sensehat.h>
#include <stdint.h>

#define I2C_CHANNEL 1

static bool loop = true;

int temperature;
int pressure;
int humidity;
int x_axis;
int y_axis;
int z_axis;

void timer_handler(union sigval arg){
    int status;
    printf("Thread handler\n");

    if (shGetTempHumid(&temperature, &humidity))
		{
			printf("T=%d, H=%d\n", t, h);
		}
		if (shGetPressure(&pressure, &temperature))
		{
			printf("P=%d, T=%d\n", pressure, temperature);
		}
		if (shGetMagneto(&x_axis, &y_axis, &z_axis))
		{
			printf("accX=%d, accY=%d, accZ=%d\n", x, y, z);
		}

}

int create_timer(void){

    timer_t t;
    struct itimerspec t_spec;
    struct sigevent sig_evt;
    int result = -1;

    sig_evt.sigev_notify = SIGEV_THREAD;
    sig_evt.sigev_value.sival_ptr = &t;
    sig_evt.sigev_notify_function = timer_handler;
    sig_evt.sigev_notify_attributes = NULL;

    t_spec.it_value.tv_sec = 1;
    t_spec.it_value.tv_nsec = 0;
    t_spec.it_interval.tv_sec = 1;
    t_spec.it_interval.tv_nsec = 0;

    result = timer_create(CLOCK_REALTIME, &sig_evt, &t);
    if (result == -1)
        return -1;

  result = timer_settime(t, 0, &t_spec, 0);
  if (result == -1)
        return -1;

        while(!flg);
        return 0;

}

int main(void){
    if (shInit(I2C_CHANNEL) == 0) // Open I2C	
	{
		printf("Unable to open sense hat; is it connected?\n");
		return -1;
	}
    while(loop);
}