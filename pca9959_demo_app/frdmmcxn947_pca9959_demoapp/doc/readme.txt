Hardware requirements
===================
- Mini/micro C USB cable
- FRDM-MCXN947 board
- PCA9957-ARD board 
- Personal Computer

Board settings

- There are jumpers corresponding to each LED, we can remove particular jumper to 
  disconnect a particular LED from LED Channel.
  eg. J76,J77,J78.
- To connect external LED, Use J21 and J26.
- To test short and open circuit:
  Short Circuit: J49, J58, J57 etc.
  Open Circuit:  J76,J77,J78 etc. 
- Jumper to control Imax: J84

Prepare the Demo
===============
1.  Connect a USB cable between the host PC and the OpenSDA USB port on the target board.
2.  Open a serial terminal with the following settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Either press the reset button on your board or launch the debugger in your IDE to begin running the demo.

Running the demo
===============
When the demo runs successfully, you can see the logs printed on the terminal based on the menu options user chooses.

LOGS:
=============
ISSDK PCA9959 LED driver example demonstration for SPI

 Successfully Applied PCA9959 Configuration

  It is recommended to use external supply (3V - 3.3V) on J1

  To use external supply Please connect pin number 2 and 3 of J2

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 10

 1. Auto Switch Off Enable

 2. Auto Switch Off Disable

 Enter your choice :- 2

 Auto Switch Off Disable

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 1

 By default side 0 gets configured and executed

 Configure side 0/1 and perform LED control configurations for that particular side

 User can switch between side 0 and side 1 using side execute only when gradation is enabled


 ******** Side Control ********

 1. Side Configuration

 2. Side Execute

 3. Exit From Side Control

 Enter your choice :- 1

 Press 1 for side 0

 Press 2 for side 1

 Enter Side Number [1 or 2] :- 1

 Side configuration completed


 ******** Side Control ********

 1. Side Configuration

 2. Side Execute

 3. Exit From Side Control

 Enter your choice :- 2

 Press 1 for side 0

 Press 2 for side 1

 Enter Side Number [1 or 2] :- 2

 Side executed


 ******** Side Control ********

 1. Side Configuration

 2. Side Execute

 3. Exit From Side Control

 Enter your choice :- 3

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 7

 Reset Done

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 2


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 1

 Enter Group Number [1 to 4] :- 2

 ******** Choose one of the below options for preset current configurations ********

 1. Selected LEDs are in off state

 2. Selected LEDs will get preset current 1

 3. Selected LEDs will get preset current 2

 4. Selected LEDs will get preset current 3

 Enter Grid preset current configuration [1 to 4] :- 2

 Please Select Ending Grid Number as Grid Configuration Starts from Grid 0

 Enter Grid End Value [1 to 64] :- 8

 Page Select done for gradation configuration

 Grid Group Configuration Done


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 3

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 2


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 2

 Page Select done for channel configuration

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 1

 Enter LED Number [1 to 24] :- 1

 LED Channel Enable Done

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 3

 Enter LED Number [1 to 24] :- 1

 Enter Group Number [1 to 4] :- 2

 LED Assignment Done

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 4

 ********* Set Preset Current for individual LEDs *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 1

 Enter LED Number [1 to 24] :- 1

 Enter Brightness [1 to 64] :- 40

 LED Preset Current 1 Setting Done

 ********* Set Preset Current for individual LEDs *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 4

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 5


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 3

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 10

 1. Auto Switch Off Enable

 2. Auto Switch Off Disable

 Enter your choice :- 2

 Auto Switch Off Disable

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 2


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 2

 Page Select done for channel configuration

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 2

 Enter LED Number [1 to 24] :- 1

 LED Channel Disable Done

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 5


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 221


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 3

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 7

 Reset Done

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 10

 1. Auto Switch Off Enable

 2. Auto Switch Off Disable

 Enter your choice :- 2

 Auto Switch Off Disable

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 3


 ******** ALL LED Control ********

 1. All Grid Group Configuration

 2. All LED Channels Configuration

 3. Exit From ALL LED Control

 Enter your choice :- 1

 Enter Group Number [1 to 4] :- 2

 ******** Choose one of the below options for preset current configurations ********

 1. Selected LEDs are in off state

 2. Selected LEDs will get preset current 1

 3. Selected LEDs will get preset current 2

 4. Selected LEDs will get preset current 3

 Enter Grid preset current configuration [1 to 4] :- 3

 Please Select Ending Grid Number as Grid Configuration Starts from Grid 0

 Enter Grid End Value [1 to 64] :- 10

 Page Select done for gradation configuration

 All Grid Group Configuration Done


 ******** ALL LED Control ********

 1. All Grid Group Configuration

 2. All LED Channels Configuration

 3. Exit From ALL LED Control

 Enter your choice :- 2

 Page Select done for channel configuration

 ********* All Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. All LED Channel Group Assignment

 4. Set Preset Current for All LED Channel

 5. Exit LED channel Main Menu

 Enter your choice :- 1

 All LED Channel Enable Done

 ********* All Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. All LED Channel Group Assignment

 4. Set Preset Current for All LED Channel

 5. Exit LED channel Main Menu

 Enter your choice :- 3

 Enter Group Number [1 to 4] :- 2

 All LED Assignment Done

 ********* All Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. All LED Channel Group Assignment

 4. Set Preset Current for All LED Channel

 5. Exit LED channel Main Menu

 Enter your choice :- 4

 ********* Set Preset Current for all LEDs *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 2

 Enter Brightness [1 to 64] :- 40

 LED Preset Current 2 Setting Done

 ********* Set Preset Current for all LEDs *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 4

 ********* All Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. All LED Channel Group Assignment

 4. Set Preset Current for All LED Channel

 5. Exit LED channel Main Menu

 Enter your choice :- 5


 ******** ALL LED Control ********

 1. All Grid Group Configuration

 2. All LED Channels Configuration

 3. Exit From ALL LED Control

 Enter your choice :- 3

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 9

 1. Enable Sleep

 2. Disable Sleep

 Enter your choice :- 2

 Disable Sleep

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 9

 1. Enable Sleep

 2. Disable Sleep

 Enter your choice :- 1

 Enabled Sleep

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 9

 1. Enable Sleep

 2. Disable Sleep

 Enter your choice :- 2

 Disable Sleep

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 3


 ******** ALL LED Control ********

 1. All Grid Group Configuration

 2. All LED Channels Configuration

 3. Exit From ALL LED Control

 Enter your choice :- 2

 Page Select done for channel configuration

 ********* All Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. All LED Channel Group Assignment

 4. Set Preset Current for All LED Channel

 5. Exit LED channel Main Menu

 Enter your choice :- 2

 All LED Channel Disable Done

 ********* All Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. All LED Channel Group Assignment

 4. Set Preset Current for All LED Channel

 5. Exit LED channel Main Menu

 Enter your choice :- 5


 ******** ALL LED Control ********

 1. All Grid Group Configuration

 2. All LED Channels Configuration

 3. Exit From ALL LED Control

 Enter your choice :- 3

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 7

 Reset Done

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 10

 1. Auto Switch Off Enable

 2. Auto Switch Off Disable

 Enter your choice :- 2

 Auto Switch Off Disable

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 4


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 1

 Enter Group Number [1 to 4] :- 3

 ******** Choose one of the below options for preset current configurations ********

 1. Selected LEDs are in off state

 2. Selected LEDs will get preset current 1

 3. Selected LEDs will get preset current 2

 4. Selected LEDs will get preset current 3

 Enter Grid preset current configuration [1 to 4] :- 4

 Please Select Ending Grid Number as Grid Configuration Starts from Grid 0

 Enter Grid End Value [1 to 64] :- 24

 Page Select done for gradation configuration

 Range Grid Group Configuration Done


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 3

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 4


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 2

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 1

 Enter Start Value [1 to 24] :- 1

 Enter End Value [1 to 24] :- 8

 Range LED Channel Enable Done

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 3

 Enter Start Value [1 to 24] :- 1

 Enter End Value [1 to 24] :- 8

 Enter Group Number [1 to 4] :- 3

 Range LED Assignment Done

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 4

 ********* Set Individual Preset Current for LEDs in Range *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 3

 Enter Start Value [1 to 24] :- 1

 Enter End Value [1 to 24] :- 8

 Enter Brightness [1 to 64] :- 30

 LED Preset Current 3 Setting Done

 ********* Set Individual Preset Current for LEDs in Range *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 4

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 5


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 3

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 4


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 2

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 2

 Enter Start Value [1 to 24] :- 1

 Enter End Value [1 to 24] :- 8

 Range LED Channel Disable Done

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 5


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 3

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 4


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 2

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 1

 Enter Start Value [1 to 24] :- 1

 Enter End Value [1 to 24] :- 8

 Range LED Channel Enable Done

 ********* Range Channel Configuration Main Menu *********

 1. Enable LED Channel in Range

 2. Disable LED Channel in Range

 3. Range LED Channel Group Assignment

 4. Set Preset Current for LED Channels in Range

 5. Exit LED channel Main Menu

 Enter your choice :- 5


 ******** Range LED Control ********

 1. Range Grid Group Configuration

 2. Range LED Channels Configuration

 3. Exit From Range LED Control

 Enter your choice :- 3

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 5


 ******** Gradation Configuration Menu ********

 1. Grid Duration

 2. Gradation Mode

 3. Start Gradation

 4. Stop Gradation

 5. Exit From Gradation Control

 Enter your choice :- 1


 ******** ALL LED Control ********

 1. Set TStep Value

 2. Set Duration Counter Value

 3. Exit From Duration Control

 Enter your choice :- 1

 1. TStep: 2.5 microseconds

 2. TStep: 5 microseconds

 3. TStep: 10 microseconds

 4. TStep: 20 microseconds

 Enter TStep Value [1 to 4] :- 4

 TStep Value Setting Done


 ******** ALL LED Control ********

 1. Set TStep Value

 2. Set Duration Counter Value

 3. Exit From Duration Control

 Enter your choice :- 2

 Enter Duration count [1 to 64] :- 24

 Duration Counter Value Setting Done


 ******** ALL LED Control ********

 1. Set TStep Value

 2. Set Duration Counter Value

 3. Exit From Duration Control

 Enter your choice :- 3


 ******** Gradation Configuration Menu ********

 1. Grid Duration

 2. Gradation Mode

 3. Start Gradation

 4. Stop Gradation

 5. Exit From Gradation Control

 Enter your choice :- 2

 1. Single Shot

 2. Continuous

 Enter your choice :- 2

 Gradation Mode Setting Done


 ******** Gradation Configuration Menu ********

 1. Grid Duration

 2. Gradation Mode

 3. Start Gradation

 4. Stop Gradation

 5. Exit From Gradation Control

 Enter your choice :- 3

 Gradation Started


 ******** Gradation Configuration Menu ********

 1. Grid Duration

 2. Gradation Mode

 3. Start Gradation

 4. Stop Gradation

 5. Exit From Gradation Control

 Enter your choice :- 4

 Gradation Stop Done


 ******** Gradation Configuration Menu ********

 1. Grid Duration

 2. Gradation Mode

 3. Start Gradation

 4. Stop Gradation

 5. Exit From Gradation Control

 Enter your choice :- 5

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 6

 LED Delay Set Done

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 7

 Reset Done

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 8

 User have to use external clock generator to generate 20MHz clock on OSCIN pin if user chooses option 2 i.e. external clock

 Before using external clock for gradation control, user have to provide 20MHz external clock on OSCIN pin

 1. Use ceralock resonator b/w OSCIN & OSCIN for gradation control

 2. Use external clock on OSCOUT for gradation control

 Enter your choice :- 1

 Ceralock Resonator for Gradation Control Enable Done

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 9

 1. Enable Sleep

 2. Disable Sleep

 Enter your choice :- 1

 Enabled Sleep

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 10

 1. Auto Switch Off Enable

 2. Auto Switch Off Disable

 Enter your choice :- 2

 Auto Switch Off Disable

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 7

 Reset Done

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 10

 1. Auto Switch Off Enable

 2. Auto Switch Off Disable

 Enter your choice :- 2

 Auto Switch Off Disable

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 11

 1. Set Max Current 30 MA

 2. Set Max Current 20 MA

 Enter your choice :- 2

 20 MA maximum Current Set

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 1

 By default side 0 gets configured and executed

 Configure side 0/1 and perform LED control configurations for that particular side

 User can switch between side 0 and side 1 using side execute only when gradation is enabled


 ******** Side Control ********

 1. Side Configuration

 2. Side Execute

 3. Exit From Side Control

 Enter your choice :- 1

 Press 1 for side 0

 Press 2 for side 1

 Enter Side Number [1 or 2] :- 1

 Side configuration completed


 ******** Side Control ********

 1. Side Configuration

 2. Side Execute

 3. Exit From Side Control

 Enter your choice :- 3

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 2


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 1

 Enter Group Number [1 to 4] :- 1

 ******** Choose one of the below options for preset current configurations ********

 1. Selected LEDs are in off state

 2. Selected LEDs will get preset current 1

 3. Selected LEDs will get preset current 2

 4. Selected LEDs will get preset current 3

 Enter Grid preset current configuration [1 to 4] :- 2

 Please Select Ending Grid Number as Grid Configuration Starts from Grid 0

 Enter Grid End Value [1 to 64] :- 10

 Page Select done for gradation configuration

 Grid Group Configuration Done


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 2

 Page Select done for channel configuration

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 1

 Enter LED Number [1 to 24] :- 1

 LED Channel Enable Done

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 3

 Enter LED Number [1 to 24] :- 1

 Enter Group Number [1 to 4] :- 1

 LED Assignment Done

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 3

 Enter LED Number [1 to 24] :- 1

 Enter Group Number [1 to 4] :- 1

 LED Assignment Done

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 4

 ********* Set Preset Current for individual LEDs *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 1

 Enter LED Number [1 to 24] :- 1

 Enter Brightness [1 to 64] :- 20

 LED Preset Current 1 Setting Done

 ********* Set Preset Current for individual LEDs *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 5

 ********* Set Preset Current for individual LEDs *********

 1. Set Preset Current 1

 2. Set Preset Current 2

 3. Set Preset Current 3

 4. Exit Preset Current Setting Main Menu

 Enter your choice :- 4

 ********* Individual Channel Configuration Main Menu *********

 1. LED Channel Enable

 2. LED Channel Disable

 3. LED Channel Group Assignment

 4. Set Preset Current for LED Channel

 5. Exit Gradation Main Menu

 Enter your choice :- 5


 ******** Individual LED Control ********

 1. Individual Grid Group Configuration

 2. Individual LED Channel Configuration

 3. Exit From Individual LED Control

 Enter your choice :- 3

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 12

 1. Check Error

 2. Clear Error

 3. Check Individual LED Error

 Enter your choice :- 1

 Short Circuit Occurred for Led :- 1

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 13

 Operating in Under Temperature

  Error Occurred on one or more LEDs...For more details goto "LED Error " option in main menu

 Press Enter for main menu

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 7

 Reset Done

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 13

 Operating in Under Temperature

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :- 14

 If user enables 20 MHz external clock for gradation control, user have to provide external clock by using clock generator

 Otherwise use only ceralock resonator to get 20MHz clock for gradation control

 Clock detected in correct range

 *********** Main Menu ***************

 1.  Side Control

 2.  Individual LED Control

 3.  All LED Control

 4.  Control LEDs in Range

 5.  Gradation Configuration

 6.  Set Turn on Delay of 50ns between LED(X) and LED(X+1)

 7.  Software Reset

 8.  Use 20MHz Internal/External clock for gradation control

 9.  Sleep Control

 10. Auto Switch Off Control

 11. Set Max Current

 12. Error Control

 13. Over Temperature Check

 14. Check presence of valid external clock

 Enter your choice :-