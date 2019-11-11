# Installation-notes

## Battery placement
In general, you will want to place the Lithium cells as close as possible to the lead-acid batteries. But beware of high temperatures! Engine rooms are not the best place for Lithium batteries. Elevated temperatures significantly reduce the lifetime of Lithium batteries.

## Tools
If you are implementing this project for its intended purpose you need to work with heavy high current power cables. A crimping tool is an absolute must.<br>
When working on the Lithium cells, it is highly recommended to prepare a special tool: Insulate a spanner with some wraps of duct tape so that when you tighten the terminal connections you can not accidentially touch something else. Remember: these Lithium cells are capable of delivering short cut currents of 1000Amps or more, instantly melting your spanner and throwing white hot metal chunks around if you just briefly touch the opposite pole.

## BMS power supply
The BMS is fed from the system bus, NOT from the Lithium battery! When the Lithium battery is disconnected from the system bus, the chargers and/or lead-acid batteries are feeding the BMS. The BMS remains powered all the time.<br>
To conserve power, you may want to use an external 12V to 5V DC/DC converter instead of using the built in linear 5V regulator.

## Connections

### Individual wires
Please use individual wires for sensors, power supplies, relais and control outputs, even if they are all "ground" or "12V". The power required for the high power relais can be quite high and if part of the wire is shared with the sensor wire (which is supposed to have the same potential) the resistance of the cable and/or voltage spike caused by the relais can cause false sensor readings.

### Connection points
Give some thought about the connection points. With heavy currents, even heavy gauge cable will cause a significant voltage drop. Sensor wires need to be connected directly onto the cell terminals, the same applies to the ground of the Arduino. Beware of ground loops: If your Arduino is connected to something "downstream" which has its own ground, then that "ground" may have a slightly different potential than the ground of the Arduino, especially when heavy currents are drawn from the Lithium batteries.

### Safety
As a general rule, all wires connected to the 12V bus, shunts, or individual Lithium cells, need to be appropriately fused. This would be cumbersome with the sensors so I usually put a small resistor in series with the shunt sensor wires, as close as possible to the shunts. A 12 Ohm resistor will, in case of a short cut, limit the current to about 1 Amp but doesn't disturb the sensor reading during normal situations. For the Lithium cell voltage probes I put the "hot" resistor of the resistor divider as close as possible to the cell positive terminal. This way, in case a cable becomes loose or shafes through, it won't burn down your boat.

## Control relais
The control relais is connected directly to the positive terminal of the Lithium battery, the shunt is placed further downstream. It is recommended to include a high power fuse in the cable from the Lithium positive terminal to the control relais to protect the latter.<br>
Although the BMS has an output for a monostable relay, it is highly recommended to use a bistable relay. The former requires quite some power to stay engaged (often more than 1 amp which would by itself already consume more than 24Ah per day!) but the latter only a brief pulse to switch from one state to the other. The downsides of a bistable relais is that it will not disengage by itself in case of a loose wire *and becomes unable to disengage which can lead to dangerous situations* and that a powerful bistable relais is quite expensive and somewhat harder to find.<br>
Although the BMS has an off-buttom which will immediately disconnect the Lithium battery until further notice, you might want to install an extra push button wired directly to the "off-coil" of the bistable relais so you can bypass the BMS and manually switch off the relais in case of some malfunction. Don't forget to power down or disconnect the BMS in that case otherwise it might power up the relais again!
