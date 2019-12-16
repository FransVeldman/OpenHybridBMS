# OpenHybridBMS
Arduino based BMS for lead-acid/LiFePO4 hybrid systems tailored for long term off grid sailing boats.

## Status
At the moment, this is just a reserved namespace for this project:
I have a prototype running and once I'm satisfied about its performance I will release the first version of the code.

## About lead-acid/LiFePO4 hybrid systems
Detailed explanation why one would want a lead-acid/LiFePO4 hybrid system can be found on [www.zwerfcat.nl](https://www.zwerfcat.nl/en/lithium-on-yachts.html), but  a summarized idea is given below.<br />
Note that it is beyond the scope of this README to go into detail about the properties of LiFePO4 batteries and the duties of a BMS.

### The problems
Lithium batteries are gaining popularity as they offer some significant advantages over lead-acid batteries. However, Lithium batteries exibit three properties which are somewhat problematic on sailing boats:
- Lithium batteries, unlike lead-acid batteries, need [charge termination](https://www.zwerfcat.nl/en/lithium-management.html#cterm) once they are fully charged.
- Lithium batteries love to cycle but they hate to spend the majority of the time being fully charged.
- Lithium batteries are dependent on a sensive BMS operating in harsh conditions, which forms an unwelcome additional failure point.

Let's take a closer look at these problems:

#### Charge termination
Sailing vessels usually have several charge sources:
- Engine alternators
- Wind generator
- Solar panels
- Diesel generator
- Shore power charger

All these chargers are usually designed to charge lead-acid batteries. To terminate the charge, you can't just disconnect the Lithium battery from the bus: the alternator will surge, fry its diodes and destroy all connected equipment in the process. The other charge sources often exibit similar problems when the battery is suddenly disconnected. To facilitate gracefull charge termination, all of these chargers need to be modified or replaced so they can be wired to the BMS to listen and obey to a "terminate charge" command, which is impractical and prone to failures.<br />
Another problem is what to do with the on board equipment once the Lithium battery is fully charged and disconnected from the chargers: Leave the running equipment connected to the Lithium battery? Then the equipment immediately starts draining the battery, even while charge sources are still available. Or leave the equipment connected to the charge sources? Then we have sensitive equipment directly connected to the charge source (alternator) without a battery to act as a buffer. Both alternatives are unsatisfying.

#### Capacity
Most of the time the batteries only need to provide power to get through the night when no solar power is available. Only occasionally the batteries need to be able to provide power for a longer time or when there is an unusual power demand. But if you want to have enough capacity to cover the occasional longer requests for power, then most of the time the Lithium batteries spend their time in a high state of charge, which is detrimental to their longevity. It is better to have less capacity so the battery is on an avarage lower state of charge, and that would be more economical too. But in that case, how to provide power at the odd day when reserve capacity is needed?

#### Reliability
Electronics on sailing boats have to operate in harsh conditions and often fail due to corroded contacts, lightning strikes, metal fatigue because of the constant movement, etc. At the same time, failure is often not an option, especially during an ocean passage. A Lithium battery, despite its advantages, adds a significant failure point due to its dependancy on a BMS. A redundant simple fall back energy source is highly recommended.

### Hybrid solutions
A [lithium/lead-acid hybrid](https://www.zwerfcat.nl/en/lithium-hybrid.html) installation is an installation where the lead-acid installation is left intact and the LiFePO4 battery is, via a bistable power relais, piggy backed onto the lead-acid batteries, and this solves all our problems:
- The lead-acid batteries spend most of their time being fully charged and only have to cycle occasionally, which will extend their lifetime considerably.
- The Lithium batteries only have to cover the day/night cycle so they are discharged deeply enough, which is good for their longevity.
- Standard Lead-acid charge sources  will first charge the Lithium batteries (they charge with a lower voltage than the LA-batteries) and once the fully charged Lithium battery is taken off line, the chargers will still "see" the LA-battery which they are designed for, continue the lead-acid charge curve and top off the lead-acid batteries..
- When power is used from the batteries, the Lithium batteries will be used first as they have a higher discharge voltage than the lead-acid batteries.
- The lead-acid batteries will act as a buffer once the Lithium battery is taken offline (when it is fully charged or fully discharged), act as long term reserve capacity, and act as a redundant system in case there is something wrong with the BMS.
- Redundancy. You have a plan B. If something fails with the Lithium battery or its BMS, one has still the lead-acid batteries to fall back to. Of course, Lithium batteries are very reliable if treated well, but they can not work without a BMS, which comprises of complex electronics and is sensitive to salt water, lightning discharges, connectors, corrosion, etc. In an emergency, nothing beats the simplicity of a lead-acid battery.

## OpenHybridBMS
Using a hybrid power bank requires a special BMS which doesn't interfere with the lead-acid battery but deals with its existence. OpenHybridBMS is especially designed for hybrid systems which have variable chargers and variable loads which will remain connected during the charge process.

This project was started because I was not satisfied with the commercial Battery Management System available.

With the knowledge I aquired about lithium batteries, I was wondering how many BMS manufacturers really "got it right". After all, there are so many otherwise respected manufacturers who produce chargers with a "voltage setting" for lithium batteries, while *[voltage regulation does not work with lithium batteries](https://www.zwerfcat.nl/en/lithium-management#vbcr)*. This didn't really put confidence in their knowledge about lithium systems. And that was a major obstacle, because my life could easily depend on it on the middle of the ocean.

Also, too many features were missing. It looks like these manufacturers never sail themselves. There are some useless features (bluetooth? Do they really think I keep caring for a darn cellphone while sailing in an area without coverage, just to keep track of the batteries?) but they lack important features like the ability to signal when there is surplus charge energy available so it can be used for non-critical devices like fuel polishers etc.

And above all, there were no Battery Management Systems available which could work nicely in a hybrid installation.

So, I decided to develop my own BMS. Which turned out to become much more complex than estimated...

## Features
For more information about each of the following features, click on the associated links

- [Special design for lead-acid/LiFePO4 hybrid systems](https://www.zwerfcat.nl/en/open-hybrid-bms.html#hybrid)
    - [No change necessary in existing installation](https://www.zwerfcat.nl/en/open-hybrid-bms.html#easy)
    - [Full redundancy](https://www.zwerfcat.nl/en/open-hybrid-bms.html#redundancy)
    - [Lead-acid bulk priority charging](https://www.zwerfcat.nl/en/open-hybrid-bms.html#laprio)
    - [High side current sensing](https://www.zwerfcat.nl/en/open-hybrid-bms.html#hiside)
- [Open source, others can verify the project and offer enhancements](https://www.zwerfcat.nl/en/open-hybrid-bms.html#open)
- [Rebuildable for the homebuilder with commonly available parts and tools](https://www.zwerfcat.nl/en/open-hybrid-bms.html#basic)
- [Optional pro-version, completely assembled, ready to be installed](https://www.zwerfcat.nl/en/open-hybrid-bms.html#pro)
    - Extended voltage range, so it is also suitable for 24V systems
    - On board cell balancing
    - Higher voltage and current resolution
- [Can control mono-stable relais and bi-stable (latching) relais](https://www.zwerfcat.nl/en/open-hybrid-bms.html#bistable)
- [Many communication and reporting options](https://www.zwerfcat.nl/en/open-hybrid-bms.html#comm)
    - Tracking both Lithium and lead-acid State Of Charge, current, voltage and temperatures
    - Dedicated display to show dynamic system parameters
    - Ethernet port
    - Detailed monitoring via web interface
    - Remote logging
    - Remote display
    - NMEA port
- [Safety](https://www.zwerfcat.nl/en/open-hybrid-bms.html#safety)
    - [Extensive voltage checking on cell level](https://www.zwerfcat.nl/en/open-hybrid-bms.html#volt)
    - [Temperature sensors for each cell](https://www.zwerfcat.nl/en/open-hybrid-bms.html#temp)
    - [Watchdog output](https://www.zwerfcat.nl/en/open-hybrid-bms.html#watchdog)
    - [Softfuse to limit discharge current](https://www.zwerfcat.nl/en/open-hybrid-bms.html#dfuse)
    - [Cable loss guard](https://www.zwerfcat.nl/en/open-hybrid-bms.html#loss)
- [Lithium battery life extending features](https://www.zwerfcat.nl/en/open-hybrid-bms.html#longevity)
    - [Trickle charge guarding](https://www.zwerfcat.nl/en/open-hybrid-bms.html#trickle)
    - [User selectable partial charge targets](https://www.zwerfcat.nl/en/open-hybrid-bms.html#targets)
    - [Charge current softfuse](https://www.zwerfcat.nl/en/open-hybrid-bms.html#cfuse)
    - Protection against charging at too low temperatures
- [Environmental control](https://www.zwerfcat.nl/en/open-hybrid-bms.html#environmental)
    - [Battery heater control for charging in sub-zero temperatures](https://www.zwerfcat.nl/en/open-hybrid-bms.html#heater)
    - [Two speed fan control for keeping the batteries cool in the tropics](https://www.zwerfcat.nl/en/open-hybrid-bms.html#fan)
- [Automatic energy management](https://www.zwerfcat.nl/en/open-hybrid-bms.html#signals)
    - 8 output ports signalling various conditions which can be used to control external equipment
    - 7 of these ports are preprogrammed, 1 of these signal ports is fully user configurable
    - The output port signals are also transmitted via the Ethernet and other communication ports


