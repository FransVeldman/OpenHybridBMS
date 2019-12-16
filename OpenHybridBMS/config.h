
// ***************************************************************************************************************************
// ********* The definitions below are hardware dependent settings which must be set before commissioning the system *********
// ***************************************************************************************************************************

#define LACAPACITY  540   // Lead Acid battery capacity in Amp hours.
#define LICAPACITY  360   // Lithium battery capacity in Amp hours.

// For current measurement, shunt resistors are used. A shunt is often rated in the max amount of amps, and the voltage
// over the shunt at max amp. Like 500A, 50mV. In this case this means that every 1mV equals 10 Amps.
#define LASHUNT     10.0  // Amps per millivolt
#define LISHUNT     10.0  // Amps per millivolt

// The LASERIES definition defines how the LA shunt is wired to the LI shunt: Parallel = 0, Series = 1
#define LASERIES    1

// RELAYHOLD specifies the time the signal output for the latching relay is activated
#define RELAYHOLD   300   // Time in milliseconds

// The CCL and DCL definitions are softfuses which limit the maximum current to go in or out of the Lithium battery.
// The correct setting is determined by the weakest link, typically the current limit of the relay,
// or by the specifications of the lithium battery.
// If the current limit is exceeded the BMS will disconnect with a recoverable/automatic error message.
// Note that it is highly recommended to also install a (higher rated) hardware fuse to guard against shortcircuits.
// Also note that these softfuses only apply to the Lithium battery. The BMS has no means to disconnect the LeadAcid batteries.
#define CCL         150   // Charge Current Limit in Amperes.
#define DCL         300   // Discharge Current Limit in Amperes.

// ***************************************************************************************************************************
// ***************** The definitions below are factory set software values which can be changed by the user. *****************
// ***************************************************************************************************************************

// ******** Network interface settings *********

#define MAC               {0x5A, 'I', 'F', 0x30, 0x30, 0x30}  // Should be in the form 0xXA, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX
#define IPADDRESS         {192,168,1,8}                       // The IP-address of the Ethernet interface

// Status http-page reload timer in seconds
#define SRVTIMER          5

// NTP server values (for time synchronization)
#define IPTIMESRV         {129,6,15,28}                       // time.nist.gov NTP server
#define NTP_TIMER         30                                  // Time between NTP synchronization attempts in minutes

// NMEA server
#define NMEA_IP           {192,168,11,255}
#define NMEA_PORT         10110

#define TIME_SYNC_EXPIRE  48                                  // Time in hours before last synchronization expires

// Syslog server values (for remote logging facility)
#define SYSLOG_SERVER     {192,168,11,1}
#define SYSLOG_PORT       514


// ******** User interface settings *********

#define BRIGHTNESS        64      // Default display brightness. 0 - 255
#define LOGLEN            48      // Maximum length of a log message (excluding timestamp and priority)
#define NUMLOGS           3       // Amount of logs kept in memory for display on the web interface.


// ********* BMS Lead/acid operational values ********

// Peukert is the correction factor that needs to be applied when discharging lead/acid batteries.
// A higher discharge current results in less apparent capacity of the battery.
#define PEUKERT           1.20    // Peukert factor for lead/acid batteries

// The capacity of a lead/acid battery is stated for a specific discharge rate, usually a total discharge over 20 hours.
// This value is important for the Peukert correction
#define LACAPHR           20      // Lead Acid Capacity Hours, the amount of discharge hours for which the capacity is specified.

// Lead Acid voltages are temperature dependent. Usually -3.5mV/degree Celsius per cell. If the charge source has
// temperature correction implemented, add the value below. This is the value for the entire battery, not per cell!
// This temperature correction will be used to adjust the LAFULLVOLTS and LAPRIOEND voltages at any deviation from 25 degrees.
// If no temperature correction is used, set to 0.
#define LATEMPCORRECTION  21      // Lead Acid battery Temperature Correction per degree Celsius in milliVolts

// The charge voltage of Lead Acid batteries is capped. The only way to assume a Lead Acid battery is fully charged is to monitor
// the charge current at the capped voltage. If the charge current tapers off this indicates the Lead Acid battery is full.
// So we monitor whether the charge current is less than LAFULLAMPS percent of the battery capacity for LAFULLTIME minutes,
// while the voltage is at least LAFULLVOLTS. If these conditions are met the battery is assumed to be fully charged.
#define LAFULLAMPS        1.5     // Amps percentage of the capacity. So with a capacity of 400Ah, a value of 1.5 means 6 Amps.
#define LAFULLVOLTS       14.10   // Volts @ 25 degree Celsius. At (or above) this voltage the amount of amps are examined.
#define LAFULLTIME        15      // Time in minutes

// Normally the Lithium batteries should receive charge priority, because they are the first to be discharged and they make more
// efficient use of the available charge source. However, if the Lead Acid batteries are discharged below a certain
// StateOfCharge percentage (LAPRIOSOC) they should be given priority because a low charge state is detrimental for their health.
// Once the voltage of the Lead Acid batteries goes up and reaches LAPRIOEND it means that they don't accept the full available
// charge current anymore. Priority is then given to the Lithium batteries.
// Once the Lithium batteries are fully charged, then finally the Lead Acid batteries will be topped up to 100%.
// A few notes:
// - LAPRIOEND should be somewhat lower than the capped voltage of the charge source, otherwise the Lithium batteries will
//   wait for the timer to expire. A voltage correction is applied if the temperature differs from 25 degrees Celsius.
// - Also note that, depending on the health of the lead-acid battery and the available charge current, LAPRIOEND may be
//   reached before LAPRIOSOC is reached, which means that in that case the charge priority goes to the Lithium batteries.
// - Usually the capped voltage will be reached when the leadacid batteries are more than 80% charged. So it is best to
//   set the LAPRIOSOC somewhat lower than 80%, otherwise LAPRIOEND will be reached immediately.
#define LAPRIOSOC         75      // At a SOC below this percentage the lead acid batteries will get charge priority.
#define LAPRIOEND         14.00   // After this charge voltage is reached priority is transferred to the lithium battery.
// LAPRIOTMR is a timer which specifies the maximum time the lead-acid batteries are given charge priority.
// This is intended as a fall back in case of misconfiguration or failure of the lead-acid batteries.
#define LAPRIOTMR         120     // Maximum time in minutes the lead-acid batteries are given priority.


// ********* BMS Lithium operational values ********

// The HIVOLTLIMIT definitions defines the voltage which indicates a full cell.
// The BMS terminates charging when a cell reaches this voltage
#define HIVOLTLIMIT       3.55    // Recoverable Max CellVoltage

// The LOVOLTLIMIT definition defines the voltage which indicates an empty cell.
// The BMS terminates discharging when a cell reaches this voltage.
#define LOVOLTLIMIT       2.65    // Recoverable Min CellVoltage

// The OVERVOLT definition defines the maximum voltage of a cell.
// When this is reached something is wrong. Shutdown with a fatal error.
#define OVERVOLT          3.60    // Permanent high shutdown voltage

// The UNDERVOLT definition defines the minimum voltage of a cell.
// When this is reached something is wrong. Shutdown with a fatal error.
#define UNDERVOLT         2.55    // Permanent low shutdown voltage

#define CELLDEFECT        2.40    // Below this voltage a cell is considered to be defect. Exit with a fatal error.

// Trickle charge is a condition where a battery is charged with a low current, insufficient to reach a full charge,
// but keeping the voltage up for a long time. This is detrimental for the longevity of the Lithium battery.
// When a cell is almost fully charged the voltage increases. From there the charge termination voltage should be quickly reached.
// But if a charger has a too low output voltage set or insufficient charge capacity, it is possible that this trickle condition
// persists for a very long time, which is detrimental for the health of the cell.
// So we set a timer which defines the maximum time this trickle condition is allowed to persist.
#define TRICKLE           3.40    // Voltage above this value indicates a possible trickle condition.
#define TRICKLETMR        300     // Max Trickle Time in minutes

// The values below are to prevent rapid on and off switching. This could happen with a pulsing charge or discharge source,
// alternating continuously between charging and discharging. If the batteries are nearly full or empty this would
// result in continuously connecting and disconnecting.
#define DISCONWAIT        30      // Seconds to wait before attempting to reconnect after a non fatal shutdown
#define VOLTHYST          100     // Millivolts bus voltage and battery voltage difference required before reconnecting

// We don't want to make charge or discharge decisions based on a "charge" or "discharge" current of just a few milliamps.
// The sensor may be inaccurate or noisy. Therefore we maintain a window around 0, assuming 0 for all values in that window.
#define DEADBAND          20      // Shunt deadband in millivolts, either positive or negative from 0.

// By comparing the battery voltage with the bus voltage the BMS can calculate how much power is lost in the battery cable
// and relays. Losses are converted into heat and may damage the relays or melt the cables.
// MAXLOSS defines the maximum amount of energy that may get lost.
// Of course the losses can only be measured between the battery and current shunt.
#define MAXLOSS           20      // Maximum connection loss in Watts.

#define ADAPTEXPIRE       60      // Expiration of the internal resistance measurement in minutes
#define ADAPTCURRENT      20.0    // Minimum amps to conduct a measurement of the internal resistance

// Lithium batteries get damaged when they are charged below a certain temperature.
// Most manufacturers consider charging at 0 degrees and below as unacceptable
#define CHRGMINTEMP       0.0     // Miniumum temperature to allow any charging

// The HIGHTEMP definition defines the absolute maximum cell temperature
#define HIGHTEMP          45.0    // Temperature to go into error mode

// The OVERTEMP definition defines the maximum cell temperature difference over the ambient temperature. A higher temperature
// indicates that something is wrong with the battery.
#define OVERTEMP          3.0     // Maximum cell temperature elevation against ambient temperature.

// The DIFFTEMP definitions defines the maximum cell temperature difference between individual cells. There is no reason why
// a specific cell should have a higher temperature than the other cells. If this is the case, the cell is possibly damaged.
#define DIFFTEMP          1.5     // Maximum allowable difference between cell temperatures


// ******** Environmental control ********

// The FANWARMUP definition sets the temperature under which the fan will be used to attempt to warm up the cells, provided that
// either the ambient or outside temperature is higher than the cell temperature. It is up to the user to make sure in these
// conditions that the fan draws air from a warm source.
#define FANWARMUP         4.0     // The fan will be used to warm up the cells at temperatures below this value.
// To allow charging below CHRGMINTEMP the batteries need to warm up. The BMS is able to control a battery heater.
#define HEATERTEMP        2.0     // Activate a battery heater below this temperature.
// If the heater is consuming power from the charge current, it is a charge heater. It will only switch on if sufficient
// charge current is available for the heater so it won't discharge the battery. If it is an independent heater,
// like a solenoid to activate a coolant coil from the generator, or from shore power, set the type to 2.
#define HEATERTYPE        0       // Defines heater type. 0 is no heater, 1 is charge heater, 2 is independant heater.

// The FANMINTEMP definition sets the minimum ambient temperature to allow the fan to switch on for cooling.
// Default setting is 25 degrees Celsius. 25 degrees is recommended by manufacturers as the top of the temperature window.
// Anything above that is detrimental to the longevity of the cells.
#define FANMINTEMP        25.0    // Minimum Temperature to allow switching the battery fan on.

// The FANMAXTEMP definition defines the upper temperature for the fan to work. Temperatures above this value are abnormal
// and might indicate a fire. Using the fan would only add oxigen to what might be a fire. So better to switch the fan off.
#define FANMAXTEMP        70.0    // Fan upper limit in temperature

// The FANHYST definition sets the temperature hysteresis of the fan. This is the difference between switching on and
// switching off. If there would be no hysteresis then the fan would spool up, the air cools the sensor just 0.1 degree,
// the fan switches off, etc.
#define FANHYST           1.0     // FAN hysteresis in degrees Celsius.

// It is not recommended to start a fan at low RPM from a stop. Better first use full power and once it has accelerated switch to low RPM.
#define FANSPOOLUP        500     // Time in milliseconds to allow the fan to spool up before switching to low PWM

// This sets the low RPM level of the fan. Factory setting is 50% power.
#define FANLOWPWM         128     // Duty cycle for FAN in low PMW mode. 255 = 100%

// The OUTDIFFTEMP definitions sets the temperature difference which allows the fan to run on low RPM.
#define OUTDIFFTEMP       3.0     // Temperature ambient higher to outside temperature to switch fan on in low power

// The OUTDIFFHIGH definitions defines the temperature difference which requires the fan to run on full power.
#define OUTDIFFHIGH       5.0     // Temperature ambient higher to outside temperature to switch fan to high power


// ************ Cell balancing parameters ***************

// Cell imbalance is most solidly detected when the cell which terminated the charge is not the same as the cell which terminated
// the discharge.
// Of course when the cells are nearly identical it is sort of random which cells triggers the termination. So we need to set a
// minium voltage difference in charge termination between the cells to make the imbalance significant.
#define BALANCEDIFF       0.100   // The minimum charge termination voltage difference to detect cell imbalance.
// In a well designed system it is possible that the battery is never depleted to the shut-off point, in which case
// we need to use a less precise way to detect cell imbalance, by just comparing the cell voltages.
#define VOLTDIFF          0.100   // The maximum voltage difference between cells when the first cell hits the charge termination voltage.


// ******** Signal port settings *********

// One of the signal output ports is programmable by user with custom values. The "factory reset" values can be set below:
// The custom signal output port will be set when the batteries reache a charge state as specified.
// Note about the Lithium battery: When the charge target is reached, 100% is assumed, even if the target is lower than 100%.
#define CUSTOM_LI         50      // Minimum charge state percentage of the Lithium battery.
// Note about the Lead/Acid battery:  A value of 0 means "as soon as the LA battery doesn't accept full charge current anymore".
#define CUSTOM_LA         75      // Minimum charge state percentage of the Lead/Acid battery.
// If the output signal is used to switch on a load, it might be possible that the conditions change due to the load, especially when
// the load current exceeds the available charge current, and thus at the next cycle the output signal is deactivated again.
// To prevent rapid alternation between the two conditions, two variables can be set
// A minimum "ON"-time can be specified. Even if the conditions change, the signal will be kept active until the minimum time has elapsed.
#define CUSTOM_TM         30      // Minimum time in seconds to keep the signal active against the specified conditions.
// If no minimum time has been set (i.e. value 0), the CUSTOM_AH will be evaluated. Note that a value 0 means that no charge may
// be used from the batteries, so it means "only while charging".
#define CUSTOM_AH         0       // Maximum Amp hours that may be consumed from the batteries (only when CUSTOM_TM = 0).


