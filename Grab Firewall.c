#include <kipr/wombat.h>
#include <stdlib.h>

int LEFT_WHEEL_PORT = 0;
int RIGHT_WHEEL_PORT = 3;


// distance in tipks, never use speed more than 1300
// speed -1300 to 1300, negtaive is backwards
void drive(int distance, int speed) { 
    cmpc(LEFT_WHEEL_PORT); // clear motor postion counter
    while (abs(gmpc(LEFT_WHEEL_PORT)) < distance) {
        mav(LEFT_WHEEL_PORT, speed);
        mav(RIGHT_WHEEL_PORT, speed);
    }
    // full stop
    mav(LEFT_WHEEL_PORT, 0);
    mav(RIGHT_WHEEL_PORT, 0);
    msleep(20);
}

void turn_right(int distance, int speed) {
    cmpc(LEFT_WHEEL_PORT); // clear motor postion counter, left wheel move forward in right turn
    while (gmpc(LEFT_WHEEL_PORT) < distance) {
        mav(LEFT_WHEEL_PORT, speed);
        mav(RIGHT_WHEEL_PORT, -speed);
    }
    // full stop
    mav(LEFT_WHEEL_PORT, 0);
    mav(RIGHT_WHEEL_PORT, 0);
    msleep(20);
}

void turn_left(int distance, int speed) {
    cmpc(RIGHT_WHEEL_PORT); // clear motor postion counter, right wheel move forward in left turn
    while (gmpc(RIGHT_WHEEL_PORT) < distance) {
        mav(LEFT_WHEEL_PORT, -speed);
        mav(RIGHT_WHEEL_PORT, speed);
    }
    // full stop
    mav(LEFT_WHEEL_PORT, 0);
    mav(RIGHT_WHEEL_PORT, 0);
    msleep(20);
}



// 1700 is the average between completely black and completely white
int middle_of_black_white = 17000;
void simple_line_follow(int distance, int speed, int light_sensor_port) {
    cmpc(LEFT_WHEEL_PORT);
    while (abs(gmpc(LEFT_WHEEL_PORT)) < distance) {
        if (analog(light_sensor_port) < middle_of_black_white) { // white, turn left
            mav(RIGHT_WHEEL_PORT, speed + 25);
            mav(LEFT_WHEEL_PORT, speed - 25);
        }
        if (analog(light_sensor_port) > middle_of_black_white) { // black, turn right
            mav(RIGHT_WHEEL_PORT, speed - 25);
            mav(LEFT_WHEEL_PORT, speed + 25);
        }
    }
    // full stop
    mav(LEFT_WHEEL_PORT, 0);
    mav(RIGHT_WHEEL_PORT, 0);
    msleep(20);    
}


int main() {


    enable_servos();
    set_servo_position(3,595);
    msleep(1000);
    drive(300, 750);
    turn_right(1350, 1000);
    drive(6000,1150); 
    turn_left(50,100);
    drive(2000,600);
    set_servo_position(3,3);
    msleep(1000);
    drive(500,100);
    set_servo_position(3,595);
    msleep(1000);
    turn_left(1500,200);
    drive(8000,-700);
    turn_left(400,100);
    drive(10000,-700);
    drive(600,200);
    turn_left(2300,1000);
    drive(4000,1000);
    turn_right(400,1000);
    drive(2000,-1000);
    set_servo_position(3,1);
    msleep(1000);
    turn_left(700,-100);
    drive(300,-100);
    turn_right(300,100);
    turn_left(300,100);
    drive(300,-100);
    disable_servos();

  return 0;
} 
