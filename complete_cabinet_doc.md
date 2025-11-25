
 Complete Parts List

 Electronic Components

| Component | Quantity | Specifications | Purpose |
|-----------|----------|----------------|---------|
| Arduino Uno R3 | 1 | ATmega328P | Main microcontroller |
| GSM Module | 1 | SIM800L or SIM900A | SMS communication |
| IR Obstacle Sensors | 11 | 5V, adjustable distance | Detect compartment access |
| Motorcycle Battery | 1 | 12V, 7-9Ah recommended | Main power supply |
| LM2596 Buck Converter | 2 | DC-DC step-down | Voltage regulation |
| Resistors 10kΩ | 11 | 1/4W | Pull-down (optional) |
| Jumper Wires | 1 pack | Male-Male, Male-Female | Connections |
| Breadboard or Prototyping PCB | 1 | - | Circuit assembly |
| Power Switch | 1 | SPST, 2A minimum | Main power control |
| Automotive Fuse | 1 | 2A blade type | Battery protection |
| Fuse Holder | 1 | Inline blade type | Fuse mounting |
| Wire (20-22 AWG) | 5 meters | Stranded copper | Power distribution |
| Screw Terminal Blocks | 10-15 | 2-3 position | Secure connections |
| Heat Shrink Tubing | 1 pack | Various sizes | Connection insulation |
| Zip Ties | 1 pack | - | Cable management |

 Wiring Diagram

 Power Distribution System

```
MOTORCYCLE BATTERY (12V, 7Ah)
         |
         +-- [FUSE HOLDER with 2A FUSE]
                    |
              [POWER SWITCH]
                    |
         +----------+----------+
         |                     |
    LM2596 1              LM2596 2
    (Set to 5V)            (Set to 4V)
         |                     |
         |                     |
    ARDUINO UNO            GSM MODULE
    -----------            -----------
    Vin (or 5V pin)        VCC
    GND                    GND
```

 Arduino Connections

```
ARDUINO UNO R3
==============

POWER:
  Vin  ←─── 5V from LM2596 1
  GND  ←─── Common Ground

SERIAL COMMUNICATION (GSM):
  Pin 2 (TX) ───→ GSM RX
  Pin 3 (RX) ───→ GSM TX

SENSOR INPUTS:
  Pin 4  ←─── IR Sensor 1 OUT (Compartment 1)
  Pin 5  ←─── IR Sensor 2 OUT (Compartment 2)
  Pin 6  ←─── IR Sensor 3 OUT (Compartment 3)
  Pin 7  ←─── IR Sensor 4 OUT (Compartment 4)
  Pin 8  ←─── IR Sensor 5 OUT (Compartment 5)
  Pin 9  ←─── IR Sensor 6 OUT (Compartment 6)
  Pin 10 ←─── IR Sensor 7 OUT (Compartment 7)
  Pin 11 ←─── IR Sensor 8 OUT (Compartment 8)
  Pin 12 ←─── IR Sensor 9 OUT (Compartment 9)
  Pin 13 ←─── IR Sensor 10 OUT (Compartment 10)
  Pin A0 ←─── IR Sensor 11 OUT (Compartment 11)

5V POWER OUTPUT (for sensors):
  5V   ───→ All IR Sensors VCC (connect in parallel)
  GND  ───→ All IR Sensors GND (connect in parallel)
```

 GSM Module Connections

```
GSM MODULE (SIM800L)
====================
VCC  ←─── 4V from LM2596 2
GND  ←─── Common Ground
TX   ───→ Arduino Pin 3 (RX)
RX   ───→ Arduino Pin 2 (TX)
ANT  ───→ Antenna (included with module)
```

 IR Obstacle Sensor Connections (Each of 11 sensors)

```
IR OBSTACLE SENSOR
==================
VCC  ───→ Arduino 5V (parallel connection)
GND  ───→ Arduino GND (parallel connection)
OUT  ───→ Arduino Digital Pin (4-14, A0)

Each sensor has 3 pins typically labeled:
- VCC (or +, or V+)
- GND (or -, or G)
- OUT (or DO, or Signal)
```

---

 Detailed Connection Guide

 Step 1: Power System Setup

CRITICAL: Complete this step FIRST before connecting any sensitive components

1. Battery Preparation:
   - Ensure motorcycle battery is fully charged (12V minimum)
   - Clean battery terminals
   - Attach ring terminals to red (positive) and black (negative) wires

2. Fuse Installation:
   - Connect fuse holder to battery positive terminal
   - Insert 2A fuse into holder
   - This protects against short circuits

3. Power Switch Installation:
   - Connect power switch after the fuse
   - Use screw terminals for secure connections
   - Label switch position (ON/OFF)

4. Buck Converter 1 Setup (for Arduino - 5V):
   - BEFORE connecting to circuit:
     - Connect battery to buck converter input
     - Use multimeter to measure output voltage
     - Adjust potentiometer until output reads exactly 5.0V
     - Disconnect from battery
   - Connect INPUT: Battery (+) → IN+, Battery (-) → IN-
   - Connect OUTPUT: OUT+ → Arduino Vin, OUT- → GND

5. Buck Converter 2 Setup (for GSM - 4V):
   - BEFORE connecting GSM module:
     - Connect battery to buck converter input
     - Adjust output to 4.0V (critical for SIM800L)
     - Never exceed 4.2V or you'll damage the GSM module
   - Connect INPUT: Battery (+) → IN+, Battery (-) → IN-
   - Connect OUTPUT: OUT+ → GSM VCC, OUT- → GND

IMPORTANT: Use a common ground! All GND connections must be connected together.

 Step 2: Arduino Installation

1. Power Connection:
   - Connect 5V from Buck Converter 1 to Arduino Vin pin
   - Connect GND from Buck Converter 1 to Arduino GND pin
   - Test: Power on - Arduino LED should light up

2. Verify Arduino is working:
   - Connect Arduino to computer via USB (disconnect Vin temporarily)
   - Upload a simple "Blink" sketch
   - If successful, Arduino is ready

 Step 3: GSM Module Installation

CRITICAL: SIM800L is voltage-sensitive - only 3.7-4.2V!

1. SIM Card Installation:
   - Power OFF everything
   - Insert activated SIM card (metal contacts facing down)
   - Ensure card has SMS capability and credit
   - Ensure PIN lock is DISABLED

2. Antenna Connection:
   - Screw antenna connector onto GSM module
   - Ensure tight connection for good signal

3. Power Connection:
   - Connect 4V from Buck Converter 2 to GSM VCC
   - Connect GND to common ground
   - DO NOT connect to 5V or 12V!

4. Serial Communication:
   - GSM TX → Arduino Pin 3 (RX)
   - GSM RX → Arduino Pin 2 (TX)
   - Note: Some modules require a resistor divider for RX (check your module datasheet)

5. Test GSM Module:
   - Power on system
   - GSM status LED should blink (searching for network)
   - After 10-30 seconds, LED should blink every 3 seconds (connected)

 Step 4: IR Sensor Installation

For each of the 11 IR sensors:

1. Power Connections (Parallel):
   - Create a 5V power rail using terminal blocks or breadboard
   - Connect all sensor VCC pins to this rail
   - Create a GND rail and connect all sensor GND pins
   - Connect rails to Arduino 5V and GND

2. Signal Connections:
   - Sensor 1 OUT → Arduino Pin 4
   - Sensor 2 OUT → Arduino Pin 5
   - Sensor 3 OUT → Arduino Pin 6
   - Sensor 4 OUT → Arduino Pin 7
   - Sensor 5 OUT → Arduino Pin 8
   - Sensor 6 OUT → Arduino Pin 9
   - Sensor 7 OUT → Arduino Pin 10
   - Sensor 8 OUT → Arduino Pin 11
   - Sensor 9 OUT → Arduino Pin 12
   - Sensor 10 OUT → Arduino Pin 13
   - Sensor 11 OUT → Arduino Pin A0

3. Cable Management:
   - Use zip ties to bundle wires
   - Label each sensor cable (1-11)
   - Leave enough slack for sensor adjustment

---

 Physical Installation

 IR Sensor Mounting Strategy

Sensor Positioning:

```
     COMPARTMENT VIEW (TOP DOWN)
     
     [Door/Opening]
     ═════════════════
     ║               ║
     ║  IR Sensor    ║  ← Mount HERE on side frame
     ║     →         ║     pointing across opening
     ║               ║
     ║   [Parts]     ║
     ║   [Inside]    ║
     ║               ║
     ═════════════════
```

For each compartment:

1. Sensor Location:
   - Mount on the side wall of compartment entrance
   - Position 5-10cm inside from the front edge
   - Height: Where hands typically enter (middle of opening)

2. Mounting Method:
   - Temporary (for testing): Double-sided tape
   - Permanent: Hot glue or small screws through mounting holes
   - Use brackets for adjustable positioning

3. Sensor Orientation:
   - Point sensor ACROSS the opening (not into compartment)
   - Angle slightly downward (10-15 degrees)
   - Ensure clear line of sight across opening

4. Distance Adjustment:
   - Most IR sensors have a potentiometer (small screw)
   - Turn clockwise: shorter detection distance
   - Turn counter-clockwise: longer detection distance
   - Goal: Trigger when hand is 5-15cm from sensor

 Sensor Calibration Process

For each sensor:

1. Power on the system
2. Observe sensor LED (most have onboard LED)
3. Wave hand through compartment opening
4. LED should light up when hand passes
5. Adjust potentiometer if needed:
   - Too sensitive: Triggering from vibrations → Turn clockwise
   - Not sensitive: Doesn't detect hand → Turn counter-clockwise
6. Test multiple times to ensure reliability


 Hardware Testing

Test 1: Power System
- [ ] Turn on power switch
- [ ] Arduino LED lights up
- [ ] GSM module LED starts blinking
- [ ] Measure voltages with multimeter:
  - Battery: ~12V
  - Arduino Vin: ~5V
  - GSM VCC: ~4V

Test 2: GSM Module
- [ ] Open Serial Monitor (Tools → Serial Monitor)
- [ ] Set to 9600 baud
- [ ] Wait for initialization messages
- [ ] Look for "GSM module ready!"
- [ ] Check signal strength (should show +CSQ: XX,Y where XX > 10)
- [ ] Wait for startup SMS on your phone (2-5 minutes)

Test 3: Individual Sensors
- [ ] Note which compartment each sensor monitors
- [ ] Wave hand through each opening one by one
- [ ] Serial Monitor should show "ALERT! Compartment accessed"
- [ ] Verify correct compartment number displays
- [ ] Check SMS arrives for each test

Test 4: Full System
- [ ] Access multiple compartments
- [ ] Verify each generates separate SMS
- [ ] Check 2-second debounce works (no duplicate alerts)
- [ ] Leave system running for 30 minutes
- [ ] Verify no false alerts

Calibration

1. Sensor Sensitivity:
   - Access each compartment normally
   - If alert doesn't trigger: Increase sensitivity (turn counter-clockwise)
   - If false alerts occur: Decrease sensitivity (turn clockwise)

2. Debounce Timing:
   - Default is 2 seconds
   - If too many alerts: Increase `debounceDelay` in code (line 26)
   - If too slow to respond: Decrease to 1000 (1 second)

3. Phone Number Verification:
   - Philippines: +639XXXXXXXXX
   - Remove spaces and dashes

---

 Troubleshooting

 Power Issues

Problem: Arduino doesn't power on
- Check battery voltage (should be >11V)
- Verify fuse is intact
- Check power switch is ON
- Verify buck converter output is 5V
- Check all ground connections

Problem: GSM module not working
- Verify voltage is 3.7-4.2V (measure with multimeter)
- Check if voltage exceeds 4.2V (will damage module)
- Ensure antenna is connected
- Verify SIM card is inserted correctly

 GSM/SMS Issues

Problem: No startup SMS received
- Check SIM card has credit
- Verify SIM card is activated for SMS
- Ensure SIM PIN is disabled
- Check phone number format (include country code)
- Wait up to 5 minutes (network registration takes time)
- Check Serial Monitor for error messages

Problem: GSM signal weak (CSQ < 10)
- Move antenna to higher position
- Use external antenna with extension cable
- Check if SIM card network has coverage in area
- Try different SIM card/network

Problem: SMS not sending
- Verify phone number format
- Check SIM credit balance
- Look for "SMS sent successfully!" in Serial Monitor
- Try sending test SMS manually: AT+CMGS="+639XXXXXXXXX"

 Sensor Issues

Problem: Sensor always triggered
- Object blocking sensor view
- Sensitivity too high - adjust potentiometer clockwise
- Sensor mounted too close to opposite wall
- Check wiring (VCC and GND reversed)

Problem: Sensor never triggers
- Sensitivity too low - adjust potentiometer counter-clockwise
- Check power connections (VCC, GND)
- Verify signal wire connected to correct Arduino pin
- Test sensor LED - should light when triggered
- Sensor may be faulty - swap with known working sensor

Problem: False alerts (random triggers)
- Increase debounce delay in code
- Decrease sensor sensitivity
- Shield sensor from ambient light changes
- Stabilize sensor mounting (vibrations can trigger)
- Add small capacitor (0.1µF) between OUT and GND

 Code Issues

Problem: Upload fails
- Wrong board selected (must be Arduino Uno)
- Wrong COM port selected
- USB cable issue (try different cable)
- Arduino bootloader damaged (rare)

Problem: Serial Monitor shows garbage
- Wrong baud rate (set to 9600)
- Poor USB cable connection

Problem: Compilation errors
- SoftwareSerial library missing (should be built-in)
- Code copied incorrectly (check brackets and semicolons)

 System Behavior Issues

Problem: Multiple SMS for one access
- Increase debounce delay (currently 2000ms)
- Check sensor stability (may be vibrating)

Problem: Compartment number wrong
- Verify sensor connected to correct Arduino pin
- Check pin array order in code (line 8)
- Label each sensor cable during installation

---

 Maintenance

 Daily
- Visual inspection of system status
- Check GSM LED (should blink every 3 seconds)

 Weekly
- Test one compartment access
- Verify SMS delivery
- Check battery voltage (should be >11.5V)

 Monthly
- Full system test (all 11 compartments)
- Check all wire connections
- Clean sensors (dust can affect performance)
- Verify SIM card credit balance
- Recharge battery if needed

 As Needed
- Replace fuse if blown
- Adjust sensor sensitivity if behavior changes
- Update phone number in code
- Recharge/replace battery when low

---

 Safety Warnings

ELECTRICAL SAFETY:
- Always disconnect battery before working on circuit
- Use proper fuse rating (2A maximum)
- Insulate all connections with heat shrink/tape
- Keep water away from electronics
- Ensure proper ventilation for battery

 BATTERY SAFETY:
- Use sealed lead-acid or AGM battery (safer than flooded)
- Don't short circuit battery terminals
- Charge in well-ventilated area
- Replace if swollen or damaged
- Keep away from children

 GSM MODULE:
- Never exceed 4.2V on SIM800L (permanent damage)
- Don't connect/disconnect while powered
- Use proper antenna (module can overheat without it)

GSM AT Commands:
- SIM800L: https://www.simcom.com/product/SIM800.html
