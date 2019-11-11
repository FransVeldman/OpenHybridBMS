# OpenHybridBMS
Arduino based BMS for lead-acid/LiFePO4 hybrid systems tailored for long term off grid sailing boats.<br>

## Status
At the moment, this is just a reserved namespace for this project:
I have a prototype running and once I'm satisfied about its performance I will release the first version of the code.

## About lead-acid/LiFePO4 hybrid systems
Detailed explanation why one would want a lead-acid/LiFePO4 hybrid system will follow soon on www.zwerfcat.nl, but  a summarized idea is given below.<br>
Note that it is beyond the scope of this README to go into detail about the properties of LiFePO4 batteries and the duties of a BMS.

### The problems
Lithium batteries are gaining popularity as they offer some significant advantages over lead-acid batteries. However, Lithium batteries exibit three properties which are somewhat problematic on sailing boats:
- Lithium batteries, unlike lead-acid batteries,  need charge termination once they are fully charged.
- Lithium batteries love to cycle but they hate to spend the majority of the time being fully charged.
- Lithium batteries are dependant on a sensive BMS operating in harsh conditions, which forms an unwelcome additional failure point.

Let's take a closer look at these problems:

#### Charge termination
Sailing vessels usually have several charge sources:
- Engine alternators
- Wind generator
- Solar panels
- Diesel generator
- Shore power charger

All these chargers are usually designed to charge lead-acid batteries. To terminate the charge, you can't just disconnect the Lithium battery from the bus: the alternator will surge, fry its diodes and destroy all connected equipment in the process. The other charge sources often exibit similar problems when the battery is suddenly disconnected. To facilitate gracefull charge termination, all of these chargers need to be modified or replaced so they can be wired to the BMS to listen and obey to a "terminate charge" command, which is impractical and prone to failures.<br>
Another problem is what to do with the on board equipment once the Lithium battery is fully charged and disconnected from the chargers: Leave the running equipment connected to the Lithium battery? Then the equipment immediately starts draining the battery, even while charge sources are still available. Or leave the equipment connected to the charge sources? Then we have sensitive equipment directly connected to the charge source (alternator) without a battery to act as a buffer. Both alternatives are unsatisfying.

#### Capacity
Most of the time the batteries only need to provide power to get through the night when no solar power is available. Only occasionally the batteries need to be able to provide power for a longer time or when there is an unusual power demand. But if you want to have enough capacity to cover the occasional longer requests for power, then most of the time the Lithium batteries spend their time in a high state of charge, which is detrimental to their longevity. It is better to have less capacity so the battery is on an avarage lower state of charge, and that would be more economical too. But in that case, how to provide power at the odd day when reserve capacity is needed?

#### Reliability
Electronics on sailing boats have to operate in harsh conditions and often fail due to corroded contacts, lightning strikes, metal fatigue because of the constant movement, etc. At the same time, failure is often not an option, especially during an ocean passage. A Lithium battery, despite its advantages, adds a significant failure point due to its dependancy on a BMS. A redundant simple fall back energy source is highly recommended.

### Hybrid solutions
A hybrid installation is an installation where the lead-acid installation is left intact and the LiFePO4 battery is, via a bistable power relais, piggy backed onto the lead-acid batteries, and this solves all our problems:
- The lead-acid batteries spend most of their time being fully charged and only have to cycle occasionally, which will extend their lifetime considerably.
- The Lithium batteries only have to cover the day/night cycle so they are discharged deeply enough, which is good for their longevity.
- Standard Lead-acid charge sources  will first charge the Lithium batteries (they charge with a lower voltage than the LA-batteries) and once the fully charged Lithium battery is taken off line, the chargers will still "see" the LA-battery which they are designed for, continue the lead-acid charge curve and top off the lead-acid batteries..
- When power is used from the batteries, the Lithium batteries will be used first as they have a higher discharge voltage than the lead-acid batteries.
- The lead-acid batteries will act as a buffer once the Lithium battery is taken offline (when it is fully charged or fully depleted), act as long term reserve capacity, and act as a redundant system in case there is something wrong with the BMS.

## OpenHybridBMS
Using a hybrid power bank requires a special BMS which doesn't interfere with the lead-acid battery but deals with its existence. OpenHybridBMS is especially designed for hybrid systems which have variable chargers and variable loads which will remain connected during the charge process.<br>

### Features
Apart from managing the Lithium battery, OpenHybridBMS has the following features:
- Tracking both Lithium and lead-acid State Of Charge, current, voltage and temperatures
- Dedicated display to show dynamic system parameters
- Detailed monitoring via web-interface
- Remote logging
- Remote display
- Environmental control (battery heating for charging at sub-zero temperatures, cooling fan to cool battery down)
- User configurable charge targets
- Automatic Lead-acid priority bulk charging
- Trickle charge guarding
- Watchdog output
- Dedicated outputs for controlling equipment (like desalinators) which can be enabled/disabled on various conditions
- NMEA output
- Overcurrent "soft fuse"

Features are still being added, stay tuned.

## Versions
I anticipate two versions of this project:

### DIY version
To make this project suitable for DIY, only commonly available parts and breakout boards suitable for DIY projects are used. Unfortunately, this sets a few limits:
- The BMS is only suitable for 12V systems due to limitations of the ADC and high side current sensors. Suitable parts for 24V are only available in SMD,  not on breakout boards.
- Cell imbalance can be detected and reported, but not automatically corrected. Circuitry for automatic cell balancing would become quite complex for this DIY project and would add some unnessecary failure points. Experience from other builders has shown that in a healthy battery pack cell balancing is only benificial if performed no more frequent than once per year. If the BMS reports a cell imbalance the rebalancing can be performed manually if desired.

### Readily built version
I plan to produce a limited batch of the BMS which will be completely built and ready to be used. This version will use a few different components which allow the BMS to be used for 24V systems as well and will feature automatic cell balancing. If you are interested, please let me know.

