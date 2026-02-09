#include "EncoderVelocity.h"
#include "pinout.h"
#include "EveryNMillis.h"


#define PRINT_DELAY 30 // Delay between printing to serial in milliseconds

// Encoder velocity readers
EncoderVelocity encoder1(ENCODER1_A_PIN, ENCODER1_B_PIN, CPR_60_RPM);
EncoderVelocity encoder2(ENCODER2_A_PIN, ENCODER2_B_PIN, CPR_60_RPM);

void setup() {
    Serial.begin();
}

//Prints the encoder readings to the serial monitor
void printEncoderReadings(){
    Serial.printf("encoder 1: Vel (rad/s): %.2f, Pos (rad): %.2f,   "    
                  "encoder 2: Vel (rad/s): %.2f, Pos (rad): %.2f\n", 
                encoder1.getVelocity(), encoder1.getPosition(), 
                encoder2.getVelocity(), encoder2.getPosition());
 }

void loop(){
    // Print encoder readings every PRINT_DELAY milliseconds
    EVERY_N_MILLIS(PRINT_DELAY) {
        printEncoderReadings();
    }
    
}