# zHeat PCB
A dedicated PCB using ESP32C6 µC as been designed to optimize reliability and costs.

![Iso view of zTank PCB](<screenshot/zHeat iso.png>)

The board connect to:

* Homebus to connect Daikin Heat Pump via P1P2 connector

* 12V serial bus to connect on heating circuit controller

* 4-20mA port to connect to pressure sensor on the circuit

## Tools

 The design of the PCB has been done with KiCad 10.0. Particular footprint and 3D STEP file are included in the `/library` folder for sake of maintenance

## Design

 The design is based on ESP32C6 WROOM with the following peripherials:
 * USB for power, flash device and output serial debug / info.
 * Powering circuit is done using MCP1826S 
 * A 4-20mA loop is built based on a LM2735X (1.6MHz) to raise voltage to about 20V
 * 4 channels 4-20mA sensors is provided and converted using ADS1115IDGS. It communicate with µC with i2c port
 * a debounced contact is provided for pulse counter
 * A push button is also provided for very simple HMI
 * PCB is also equipped by a LED for simpl HMI
 * Finally PCB is equipped with header that can be used for a touchscreen device in case of future needs (software lib already written and tested)

 Component size has been selected to 0805, except ESD protective diodes that are smaller.

### USB

  ![USB schematic](<screenshot/zTank USB.png>)

  USB socket is grounded to the main ground planes (2 sides).
  USB Lines `USB-` and `USB+` are directly connected to ESP32C6 to flash and monitor µC.
  `VBUS` is used to provide `+5V` (which is in fact lower than +5V) via a protective diode `D3`.

  All this 3 lines are protected by ESD protective diode.

### Voltage regulator

  ![Regulator schematic](<screenshot/zTank MCP1826S.png>)

  All the board is powered using `+3.3V`. This voltage is provided by a fixed low-voltage regulator MCP1826S-3302E that can provide up to 1000mA.
  Fixed voltage regulator requires only few external component, in this case only capacitors are installed as per datasheet.


### 4-20mA Voltage circuit

  ![LM2735X schematic](<screenshot/zTank LM2735X.png>)

  To avoid noise on lines and due to voltage drop at each stage, 4-20mA loop voltage shall be at around 20V. Care shall be taken when changing this voltage as it may require adjustment (in the shunt values for instance) to avoid damaging other components.

  This voltage is produced from `+5V` using a boost type regulator LM2735X (@1.6MHz). Computation of the external components are provided in the LibreOffice Spreadsheet [PCB comput spreadsheet](<2024-06-29 Comput.ods>). A 33µH inductance has been selected to get a clean output voltage to avoid noise on sensors line.

### 4-20mA conversion

 ![4 channel connector schematic](<screenshot/zTank 4channel connector.png>)

  4 channels are available via Phoenix contact 8 poles connector. Each channel input current is injected in a 133R shunt (low tolerance resistor) to output a voltage below 3.3V. A 100nF capacitor is provided to reduce noise.

  ![ADS1115 schematic](<screenshot/zTank ADS1115.png>)

  Each channel voltage is then converted in a digital signal using an ADS1115IDGS, that communicate with µC using i2c protocol. A ready pin is used to trigger an interrupt to the µC when data are available.
  External components are:
   * 10k resistor connected to the ground for the address of the device (only one on board so gnd is the common one)
   * 10k pull-up resistor on each signal (`SCL`, `SDA`, `RDY`) connected to µC
   * Decoupling capacitor for power lines and rearmable fuse to protect circuit

### Debounced contact

![Debounced pulse schematic](<screenshot/zTank Pulse contact.png>)

An harware RC filter has been set up on this input to avoid false triggering. The computation of this filter is detailed in the spreadsheet file [PCB comput spreadsheet](<2024-06-29 Comput.ods>), bouncing duration has been measured using an oscilloscope in a unique water meter equiped with dry contact pulse output. It may be required to adjust this filter if the water meter seems to input false pulse to the µC. 

The only other component is a pull-up resistor to not let a float input.

### µC ESP32C6 WROOM

![µC schematic](<screenshot/zTank ESP32C6.png>)

ESP32C6 power up is done using decoupling capacitor (10µF // 100nF).

The `EN` pin is driven to the `+3.3V` to enable the µC. 

`GPIO9` shall be pulled up to `+3.3V` to set the µC in normal execution mode (instead of ROM serial bootloader when `GPIO9` is pulled to the ground). Despite the doc says that it has an internal pull-up, µC will not boot normally after reporg if not driven to `+3.3V`.

`GPIO8` shall be driven to `+3.3V` as doc says, in order to enter the serial bootloader reliably.

### Push Button

Push button has been connected to `GPIO9`, so it can be used to boot/flash device by driving the pin low. Indeed, no operation is required on this button to flash µC using USB directly, and push button is used by software for HMI purpose.

### Led

A led is connected to `GPIO23` for HMI purpose as well. Resistor has been calculated according to LED spec to grant the required current.

### Header

A header is available to drive a touchscreen if required. It has not been integrated in the enclosure of this repo. It was planned and tested using a ILI9341 TFT touchscreen.

## PCB fabrication

Gerber files are included for fabrication. A batch of PCB has been produced by JLCPCB with the following configuration:

|Base Material        |	FR-4	                             | Layers                     |	2                 |
|---------------------|------------------------------------|----------------------------|-------------------|
|Dimension            |	49 mm* 91 mm                       | PCB Qty                    |	20                |
|Product Type         |	Industrial/Consumer electronics    | Different Design           |	1                 |
|Delivery Format      |	Single PCB	                       | PCB Thickness              |	1.6mm             |
|Specify Stackup      |	no	                               | Layer Sequence             |                   |	
|PCB Color            |	Purple	                           | Silkscreen                 |	White             |
|Material Type        |	TG135	                             | Via Covering               |	Tented            |
|Surface Finish       |	ENIG Gold Thickness: 1U"	         | Deburring/Edge rounding    |	No                |
|Outer Copper Weight  |	1 oz	                             | Gold Fingers               |	No                |
|Electrical Test      |	Flying Probe Fully Test	           | Castellated Holes          |	no                |
|Edge Plating         |	No	                               | Mark on PCB	              | Order Number      |
|Blind Slot           |	No	                               | Min via hole size/diameter |	0.3mm/(0.4/0.45mm)|
|4-Wire Kelvin Test   |	No	                               | Paper between PCBs         |	No                |
|Appearance Quality   |	IPC Class 2 Standard	             | Confirm Production file    |	No                |
|Silkscreen Technology|	Ink-jet/Screen Printing Silkscreen | Package Box                |	With JLCPCB logo  |
|Inspection Report    |	No	                               | Board Outline Tolerance    |	±0.2mm(Regular)   |
|UL Marking           |	No	                               | Countersink Hole           |	No                |

## Assembly

A stencil as been produced by JLCPCB, so the assembly has been done using solder paste, manually placing components, and reflow is done using an hot plate.

The components that generate issues during that process are:
 * USB connector `J5` : often some bridges are created due to the high density of pin. It has to be manually fixed
 * ESD protection diodes `D4`, `D5` & `D6`: are they are really small and light, they moved during the reflow process. It has to be manually fixed with a soldering iron, as hot air gun make them move anyway whaterver the airflow is
 * Care should be taken on the pin of ADS converter `U1`(bridges) and µC `U4` (alke of solder)
 * Obviously connector `J1`, `J2` and `J3` have to be solded manually


## Usage

For routing simplicity, 4-20mA channels are not reparted logically on the board, please consider the scheme here below.

Debounced pulse contact don't have polarity.

![Board connectors](<screenshot/zTank Connections.png>)



