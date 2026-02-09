# Lab 2: 2-DoF Robot Assembly

2.12/2.120 Intro to Robotics  
Spring 2026[^1]

- [1 Hardware Assembly](#1-hardware-assembly)
- [2 Wiring and Validation](#2-wiring-and-validation)
  - [2.1 Microcontroller](#21-microcontroller)
  - [2.2 Motors](#22-motors)
  - [2.3 Encoders](#23-encoders)
- [3 Feedback Form](#3-feedback-form)
- [X Optional](#x-optional)
  - [X.1 Adding the Joystick](#x1-adding-the-joystick)
  - [X.2 Moving in Joint Space](#x2-moving-in-joint-space)
  - [X.2.1 Refactoring Code](#x21-refactoring-code)
  - [X.2.2 Commanding the Robot](#x22-commanding-the-robot)
  - [X.2.3 Draw A Line](#x23-draw-a-line)
    
## 1 Hardware Assembly

Below is an image of the 2-DoF robot arm you will assemble. Completing this section should take less than 20 minutes, so please ask for help if you feel like you are taking longer! We want you to have enough time to complete the remaining sections.

<p align=center>
  <img src=./.images/0_full.png width=600>
</p>
<p align=center>
  <em> Figure 1 </em>
</p>

Materials:

- 2 [arm links (low-side U-channel)](https://www.gobilda.com/1143-series-mini-low-side-u-channel-8-hole-216mm-length/)
- 3 [base mounts (U-channel)](https://www.gobilda.com/1120-series-u-channel-4-hole-120mm-length/)
- 2 [motors (60 RPM)](https://www.gobilda.com/5203-series-yellow-jacket-planetary-gear-motor-99-5-1-ratio-24mm-length-8mm-rex-shaft-60-rpm-3-3-5v-encoder/)
- 2 [hubs](https://www.gobilda.com/1310-series-hyper-hub-8mm-rex-bore/)
- [socket head bolts (M4)](https://www.gobilda.com/2800-series-zinc-plated-steel-socket-head-screw-m4-x-0-7mm-8mm-length-25-pack/)
- [hex nuts (M4)](https://www.gobilda.com/2811-series-zinc-plated-steel-hex-nut-m4-x-0-7mm-7mm-hex-25-pack/)
- marker holder

Steps:
1. Attach the 2 motors on either end of a single arm link (Fig. 2).
    <p align=center>
      <img src=./.images/1_motors.png width=400>
    </p>
    <p align=center>
      <em> Figure 2 </em>
    </p>

2. Add the hubs onto each shaft using 2 set screws (Fig. 3).
    <p align=center>
      <img src=./.images/2_hub.png width=350>
    </p>
    <p align=center>
      <em> Figure 3 </em>
    </p>

3. Attach the base made of 3 U-channels to one of the hubs (Fig. 4).
    <p align=center>
      <img src=./.images/3_attach.png width=300>
    </p>
    <p align=center>
      <em> Figure 4 </em>
    </p>

4. Attach a new arm to the other hub and attach the marker holder to the end of that arm if it is not already present (Fig. 5).
    <p align=center>
      <img src=./.images/4_holder.png width=600>
    </p>
    <p align=center>
      <em> Figure 5 </em>
    </p>
    
5. Use two clamps to hold the base down to the table. **IMPORTANT:** Ensure there is enough space for each arm link to move +/- 30° from the position when the arm is fully extended (both links are parallel) without hitting anything.

## 2 Wiring and Validation

Similar to Lab 1, we also need to wire and validate the microcontroller, motors, and encoders.

### 2.1 Microcontroller

1. Plug the microcontroller in the breadboard so that the USB-C port is near the edge of the breadboard.
2. Use solid wires to connect the `3.3V` to both `+` rails and `GND` to both `-` rails.
   
    <details>
    <summary><i> What is a rail?</i>
    </summary>

    Rails on a breadboard refer to the two long strips labeled `+` and `-` on either side. They are typically located between red and blue lines parallel to the rails.
    </details>
3. Open the VSCode application. Click "File" on the upper-left corner then click "New Window". 
4. Clone this repository.
5. Run `blink_test.cpp`. The onboard LED should change colors.
    <details>
    <summary><i> How do I put the microcontroller in download mode again?</i>
    </summary>

    Press and hold `BOOT`. Click `RST` while still holding down `BOOT`. Let go of `BOOT`.
    </details>


### 2.2 Motors 

1. Wire the motor driver board to the microcontroller according to `include/pinout.h`. Remember to wire the `GND` pin of the motor driver to the `-` rail. Make sure that the motor ground wire is connected to the right of the terminal block, and the positive to the left (it should be the same order as the power supply pigtails).
    <details>
    <summary><i> Can I see a wiring diagram?</i>
    </summary>
    It is a good skill to be able to wire motors and sensors without an explicit wiring diagram. That being said, everyone in the class has different levels of experience with wiring components to microcontrollers. If your group is confused or needs guidance, feel free to take a look at the demo setup the TAs have built to see how the wiring was done.
    </details>

2. Connect the motors to the motor driver board. `M1` should correspond to the motor attached to the base and `M2` should correspond to the motor closer to the marker holder. 
2. Connect the button/switch that has barrel jack connectors between the motor driver and the power supply. This should cut off the power supply's voltage when toggled, acting as an emergency stop.
3. Reduce the power supply output to around `5.2V`. **Remember, the motors are powerful. Always keep the workspace clear of obstacles (laptops) and hold on to the power supply switch you just connected.**
4. Confirm that the motor driver has power. The green `PWR` LED should be on. If not, turn on the power supply switch.
5. Push and hold the `M1A`, `M1B`, `M2A`, and `M2B` buttons on the motor driver one at a time to check that the motors can spin in both directions. Make sure that `M1` corresponds to the motor attached to the base. 
6. Turn off the power supply switch. The green `PWR` LED should be off. The power supply switch should always be off unless the motors need to move.
7. Make the arm point straight up in full extension. This is the default position the arm should be in **before running any code**. 
8. Run `motor_drive_test.cpp`. You should see both motors turn slightly in both directions at two different speeds.
    <details>
    <summary><i> Nothing is happening?</i>
    </summary>

    Check that the motor driver has power by looking at the green `PWR` LED. If not, turn on the power supply switch.
    </details>
  
9. Turn off the power supply switch. The motor driver does not need power for the encoder wiring and validation.

### 2.3 Encoders 

1. Wire the encoders according to `include/pinout.h`. Use extension jumper cables for encoder 2.
2. Use zip ties to attach the encoder 2 wires to link 1 so that `M1` can rotate freely without snagging wires.
3. Run `encoder_basic_test.cpp` and open the Serial Monitor. Move the robot links by hand, observe which turn directions make the encoder counts increase, and think about why this is the case.
4. Run `encoder_test.cpp`. Confirm that the position increases when turning link 1 counter-clockwise looking down at the table and decreases when turning link 2 counter-clockwise looking down at the table.

| :white_check_mark: CHECKOFF 1 :white_check_mark:   |
|:---------------------------------------------------|
| Demonstrate `encoder_test.cpp` to a TA or LA! |

## 3 Feedback Form

If you have any feedback, please fill out the form here: https://forms.gle/GXQCmbxuda3mm2cy6

## X Optional

### X.1 Adding the Joystick

Now that we have a validated 2-DoF robot, let's add a joystick to control it.

1. Wire the joystick according to pinout.h: connect `U/D+` and `L/R+` to the `3.3v` rail, the two `GND` pins to the ground rail, one `L/R` to XPIN, and one `U/D` to YPIN.
2. To validate that you can read the joystick input, run `joystick_test.cpp` and open the Serial Monitor. You should see joystick readings in the range `[-1, 1]`.

### X.2 Moving in Joint Space

With the joystick in place, we can then use code to connect the joystick reading to the robot motion.

### X.2.1 Refactoring Code
We will now refactor our joystick control code to have a structure that employs multiple files. Though this might seem more confusing at first, it makes our code more modular, so that multiple programs can share the same functions without copy-and-pasting code in each program file.

1. Open `include/joystick.h` and define a `struct` to store the `x` and `y` values of a joystick reading as floats.
    <details>
    <summary>  <i> What is a struct?</i></summary>

    A structure or `struct` is a user-defined data type that can group *members* of possibly different types into a single type. An example usage is shown below.
    ``` 
    struct Student {
      int id;
      float gpa;
    };

    Student bob = {1, 2.0}; // Initializes a Student variable called bob with id = 1 and gpa = 2.0
    bob.gpa = 2.3; // Updates the gpa member of bob to 2.3. Good job, bob!
    Serial.printf("GPA: %.2f\n", bob.gpa); // Prints the new gpa 2.3 in the Serial Monitor
    ```
    </details>

2. Open `src/lab_code/joystick.cpp` and complete the `TODO`s. 
3. Open `src/test_code/joystick_test.cpp` and complete the `TODO`s. 
4. Move `joystick_test.cpp` and `joystick.cpp` to the `src/robot/` directory. 
5. Run the new `joystick_test.cpp` and open the Serial Monitor. Confirm that your joystick readings are the same as before. 
    
### X.2.2 Commanding the Robot

Open `src/lab_code/drawing.cpp` and complete all the `TODO`s. At a high level, the code should do the following:
   - reads the joystick
   - scales the joystick reading from `[-1, 1]` to `[-pi/3, pi/3]`
   - feeds the joystick reading to a position setpoint
   - smoothes the position setpoint using exponential smoothing
   - drives the motor using a PID controller

Simply put, the x-axis of the joystick controls the position of motor 1 and the y-axis of the joystick controls the position of motor 2. This is joint space!

### X.2.3 Draw A Line
Attach a marker to the end of your 2-DoF robot and try drawing a straight line on your whiteboard. Make sure to move 2 files `drawing.cpp` and `joystick.cpp` from `lab_code/` to `robot/`, and move `joystick_test.cpp` out of `robot/`.

| :white_check_mark: CHECKOFF 2 :white_check_mark:   |
|:---------------------------------------------------|
| Show your work of art to a TA or LA! |

[^1]: Version 1 - 2020: Rachel Hoffman  
  Version 2 - 2024: Phillip Daniel  
  Version 3 - 2024: Ravi Tejwani, Kentaro Barhydt  
  Version 4 - 2024: Jinger Chong, Josh Sohn  
  Version 5 - 2025: Roberto Bolli, Kaleb Blake
  Version 6 - 2026: Stephan Stansfield
