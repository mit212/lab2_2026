#include <Arduino.h>
#include <math.h>
#include "PID.h"
#include "EncoderVelocity.h"
#include "util.h"
#include "MotorDriver.h"
#include "kinematics.h"
#include "joystick.h"

//PID Parameters
double tau = 0.1; //seconds
PID motorPID1(8.0, 0.0, 0.75, tau, 0.1, false);
PID motorPID2(3.0, 0.0, 0.5, tau, 0.1, false);

JoystickReading joystick_reading;

JointSpace setpoint = {THETA1_OFFSET, 0.0};
JointSpace new_setpoint;

double theta1 = 0; //radians
double theta2 = 0; //radians
double controlEffort1 = 0; //duty cycle
double controlEffort2 = 0; //duty cycle

MotorDriver motor1(DIR1, PWM1, 0);
MotorDriver motor2(DIR2, PWM2, 1);
EncoderVelocity encoder1(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM, 0.2);
EncoderVelocity encoder2(ENCODER2_A_PIN, ENCODER2_B_PIN, CPR_60_RPM, 0.2);

// Checks if provided JointSpace state is within safety limits
// Returns true if it is and false otherwise
bool safetyLimit(JointSpace state) {
    return abs(state.theta1 - M_PI/2.0) <= M_PI/2.0 &&
           abs(state.theta2) <= M_PI*0.9;
};

void setup() {
    motor1.setup();
    motor2.setup();

    Serial.begin(); 
    setupJoystick();
}

void loop() {
    // Update setpoint at 1kHz
    EVERY_N_MICROS(1000) {
        // TODO: Use the function you implemented in joystick.cpp to read inputs from the joystick 
        // joystick_reading = 

        // TODO: Scale joystick_reading from range [-1, 1] to range [-M_PI/3.0, M_PI/3.0]
        new_setpoint.theta1 = 0;
        new_setpoint.theta2 = 0;

        // Translates the setpoint to the defined coordinate system
        new_setpoint.theta1 += THETA1_OFFSET;
        new_setpoint.theta2 = -new_setpoint.theta2;


        // Only update setpoint if new setpoint is within safety limits
        if (safetyLimit(new_setpoint)) {
            setpoint = new_setpoint;
        }
    }

    // Update PID at 10kHz
    EVERY_N_MICROS(100) {        

        theta1 = encoder1.getPosition() + THETA1_OFFSET;
        theta2 = -encoder2.getPosition();
        controlEffort1 = motorPID1.calculateParallel(theta1, setpoint.theta1);
        controlEffort2 = motorPID2.calculateParallel(theta2, setpoint.theta2);

        motor1.drive(controlEffort1);
        motor2.drive(controlEffort2);
    }

    // Print values at 10Hz
    EVERY_N_MILLIS(100) {

            // Print values to serial monitor
            Serial.printf("T1 SP (rad): %.2f, POS (rad): %.2f, CE: %.2f,   "
                          "T2 SP (rad): %.2f, POS (rad): %.2f, CE: %.2f\n",
                          setpoint.theta1, theta1, controlEffort1,
                          setpoint.theta2, theta2, controlEffort2);

    }
}
