#include "mbed.h"
#include "adrobo.h"
#include "Motor.h"

BusOut led(LED1,LED2,LED3,LED4,LED5,LED);

Motor motor1(MOTOR11, MOTOR12);
Motor motor2(MOTOR21, MOTOR22);

AnalogIn ad[] = {AD1, AD2};

int main() {
	float value = 0.0f, value1 = 0.0f;
	float delta = 0.5f;
	float sensor1, sensor2;	
	float t = 0.01;
	
	while(1) {
		sensor1 = ad[0].read();
		sensor2 = ad[1].read();
		/*壁よけ*/
		if(sensor1 > 0.35 && sensor2 >= 0.83) {
			value = 0.1f;
			value1 = -0.5f;
			t = 1.5;
		}
   /*直進*/
	  else if(sensor2 >= 0.83){
			value = -0.5f;
			value1 = 0.5f;
		}
		/*崖よけ*/
		else {
			value = 0;
			value1 = 0;
		}
		
		printf("%f    %f\r\n", sensor1, sensor2);
		motor1 = value1;
		motor2 = value;
		wait(t);
		t = 0.01;
	}
}