#ifndef ASC_H
#define ASC_H

#include <Common.h>

/* Parameters for a specific Actuated Controller Unit phase. */
typedef struct PhaseEntry
{
	/* The phase number for objects in this row. This value shall not exceed the
	 * maxPhases object value.
	 */
	uint8_t phaseNumber;

	/* Phase Walk Parameter in seconds. This shall control the amount of time
	 * the Walk indication shall be displayed.
	 */
	uint8_t phaseWalk;

	/* Phase Pedestrian Clear Parameter in seconds. This shall control the
	 * duration of the Pedestrian Clearance output (if present) and the flashing
	 * period of the Don’t Walk output.
	 */
	uint8_t phasePedestrianClear;

	/* Phase Minimum Green Parameter in seconds (NEMA TS 2 range: 1-255 sec).
	 * The first timed portion of the Green interval which may be set in
	 * consideration of the storage of vehicles between the zone of detection
	 * for the approach vehicle detector(s) and the stop line.
	 */
	uint8_t phaseMinimumGreen;
	
	/* Phase Passage Parameter in tenth seconds (0-25.5 sec). Passage Time,
	 * Vehicle Interval, Preset Gap, Vehicle Extension: the extensible portion
	 * of the Green shall be a function of vehicle actuations that occur during
	 * the Green interval. The phase shall remain in the extensible portion of
	 * the Green interval as long as the passage timer is not timed out. The
	 * timing of this portion of the green interval shall be reset with each
	 * subsequent vehicle actuation and shall not commence to time again until
	 * the vehicle actuation is removed.
	 */
	uint8_t phasePassage;
	
	/* Phase Maximum 1 Parameter in seconds (NEMA TS 2 range: 1-255 sec). This
	 * time setting shall determine the maximum length of time this phase may be
	 * held Green in the presence of a serviceable conflicting call. In the
	 * absence of a serviceable conflicting call the Maximum Green timer shall
	 * be held reset unless Max Vehicle Recall is enabled for this phase. This
	 * is the default maximum value to use. It may be overridden via an external
	 * input, coordMaximumMode or other method.
	 */
	uint8_t phaseMaximum1;

	/* Phase Maximum 2 Parameter in seconds (NEMA TS 2 range: 1-255 sec). This
	 * time setting shall determine the maximum length of time this phase may be
	 * held Green in the presence of a serviceable conflicting call. In the
	 * absence of a serviceable conflicting call the Maximum Green timer shall
	 * be held reset unless Max Vehicle Recall is enabled for this phase. This
	 * may be implemented as the max green timer via an external input,
	 * coordMaximumMode or other method.
	 */
	uint8_t phaseMaximum2;
	
	/* Phase Yellow Change Parameter in tenth seconds (NEMA TS 2 range: 3-25.5
	 * sec). Following the Green interval of each phase the CU shall provide a
	 * Yellow Change interval which is timed according to the Yellow Change
	 * parameter for that phase.
	 */
	uint8_t phaseYellowChange;
	
	/* Phase Red Clearance Parameter in tenth seconds (0-25.5 sec). Following
	 * the Yellow Change interval for each phase, the CU shall provide a Red
	 * Clearance interval which is timed according to the Red Clearance
	 * parameter for that phase.
	 */
	uint8_t phaseRedClear;
	
	/* Red revert time parameter in tenth seconds . A minimum Red indication to
	 * be timed following the Yellow Change interval and prior to the next
	 * display of Green on the same signal output driver group. The
	 * unitRedRevert parameter shall act as a minimum red revert time for all
	 * signal displays. The phaseRedRevert parameter may increase the red revert
	 * time for a specific phase. If the phaseRedRevert parameter is less than
	 * the unitRedRevert the unitRedRevert time shall be used.
	 */
	uint8_t phaseRedRevert;
	
	/* Phase Added Initial Parameter in tenths of seconds (0-25.5 sec). Added
	 * Initial parameter (Seconds / Actuation) shall determine the time by which
	 * the variable initial time period will be increased from zero with each
	 * vehicle actuation received during the associated phase Yellow and Red
	 * intervals.
	 */
	uint8_t phaseAddedInitial;
	
	/* Phase Maximum Initial Parameter in seconds (0-255 sec). The maximum value
	 * of the variable initial timing period. Variable Initial timing shall
	 * equal the lesser of
	 * [added initial(seconds / actuation) * number of actuations]
	 * or
	 * [ Max Initial ].
	 * The variable initial time shall not be less than Minimum Green.
	 */
	uint8_t phaseMaximumInitial;
	
	/* Phase Time Before Reduction (TBR) Parameter in seconds (0-255 sec). The
	 * Time Before Reduction period shall begin when the phase is Green and
	 * there is a serviceable conflicting call. If the serviceable conflicting
	 * call is removed before completion of this time (or time to reduce), the
	 * timer shall reset. Upon completion of the TBR period or the
	 * CarsBeforeReduction (CBR) parameter is satisfied, whichever occurs first,
	 * the linear reduction of the allowable gap from the Passage Time shall
	 * begin.
	 */
	uint8_t phaseTimeBeforeReduction;
	
	/* Phase Cars Before Reduction (CBR) Parameter (0-255 vehicles). When the
	 * phase is Green and the sum of the cars waiting (vehicle actuations during
	 * Yellow & Red intervals) on serviceable conflicting phases equals or
	 * exceeds the CBR parameter or the Time Before Reduction (TBR) parameter is
	 * satisfied, whichever occurs first, the linear reduction of the allowable
	 * gap from the Passage Time shall begin.
	 */
	uint8_t phaseCarsBeforeReduction;
	
	/* Phase Time To Reduce Parameter in seconds (0-255 sec). This parameter
	 * shall control the rate of reduction of the allowable gap between the
	 * Passage Time and Minimum Gap setting.
	 */
	uint8_t phaseTimeToReduce;
	
	/* This object may be used for volume density gap reduction as an alternate
	 * to the linear reduction defined by NEMA TS 1 and TS 2. It contains the
	 * tenths of seconds to reduce the gap by (0.0 - 25.5 seconds). The
	 * frequency of reduction shall produce the Minimum Gap after a time equal
	 * to the ‘phaseTimeToReduce’ object.
	 */
	uint8_t phaseReduceBy;
	
	/* Phase Minimum Gap Parameter in tenth seconds (0-25.5 sec). The reduction
	 * of the allowable gap shall continue until the gap reaches a value equal
	 * to or less than the minimum gap as set on the Minimum Gap control after
	 * which the allowable gap shall remain fixed at the values set on the
	 * Minimum Gap control.
	 */
	uint8_t phaseMinimumGap;
	
	/* This object shall determine either the upper or lower limit of the
	 * running max in seconds (0-255) during dynamic max operation.
	 * The normal maximum (i.e. Max1, Max2, etc.) shall determine the other
	 * limit as follows:
	 *   * When dynamicMaxLimit is larger than the normal maximum, it shall
	 *     become the upper limit.
	 *   * When dynamicMaxLimit is smaller than the normal maximum, it shall
	 *     become the lower limit.
	 * Setting dynamicMaxLimit greater than zero enables dynamic max operation
	 * with the normal maximum used as the initial maximum setting.
	 * See dynamicMaxStep for details on dynamic max operation.
	 * Maximum recall or a failed detector that is assigned to the associated
	 * phase shall disable dynamic max operation for the phase.
	 */
	uint8_t phaseDynamicMaxLimit;
	
	/* This object shall determine the automatic adjustment to the running max
	 * in tenth seconds (0-25.5). When a phase maxes out twice in a row, and on
	 * each successive max out thereafter, one dynamic max step value shall be
	 * added to the running max until such addition would mean the running max
	 * was greater than the larger of normal max or dynamic max limit. When a
	 * phase gaps out twice in a row, and on each successive gap out thereafter,
	 * one dynamic max step value shall be subtracted from the running max until
	 * such subtraction would mean the running max was less than the smaller of
	 * the normal max or the dynamic max limit. If a phase gaps out in one cycle
	 * and maxes out in the next cycle, or vice versa, the running max will not
	 * change.
	 */
	uint8_t phaseDynamicMaxStep;
	
	/* The Phase Startup parameter is an enumerated integer which selects the
	 * startup state for each phase after restoration of a defined power
	 * interruption or activation of the external start input. The following
	 * entries are defined:
	 *   * other; this phase initializes in a state not defined by this
	 *     standard.
	 *   * phaseNotOn; this phase initializes in a Red state (the phase is not
	 *     active and no intervals are timing).
	 *   * greenWalk; this phase initializes at the beginning of the minimum
	 *     green and walk timing intervals.
	 *   * greenNoWalk; this phase initializes at the beginning of the minimum
	 *     green timing interval.
	 *   * yellowChange; this phase initializes at the beginning of the Yellow
	 *     Change interval.
	 *   * redClear; this phase initializes at the beginning of the Red
	 *     Clearance interval.
	 */
	enum
	{
		other        = 1,
		phaseNotOn   = 2,
		greenWalk    = 3,
		greenNoWalk  = 4,
		yellowChange = 5,
		redClear     = 6
	} phaseStartup;
	
	/* Optional phase functions ( 0 = False/Disabled, 1 = True/Enabled)
	 *
	 * +-----+-----------------------------------------------------------------+
	 * | Bit | Description                                                     |
	 * +-----+-----------------------------------------------------------------+
	 * | 0   | Enabled Phase - provide a means to define whether this phase is |
	 * |     | used in the current configuration. A disabled phase shall not   |
	 * |     | provide any outputs nor respond to any phase inputs.            |
	 * +-----+-----------------------------------------------------------------+
	 * | 1   | Automatic Flash Entry Phase - When Automatic Flash is called,   |
	 * |     | the CU shall service the Entry Phase(s), clear to an All Red,   |
	 * |     | then initiate flashing operation. Support is optional.          |
	 * +-----+-----------------------------------------------------------------+
	 * | 2   | Automatic Flash Exit Phase - The CU shall move immediately to   |
	 * |     | the beginning of the phase(s) programmed as Exit Phase(s) when  |
	 * |     | Automatic Flash terminates. Support is optional.                |
	 * +-----+-----------------------------------------------------------------+
	 * | 3   | Non-Actuated 1 - when set to 1 causes a phase to respond to the |
	 * |     | Call To Non-Actuated 1 input (if present) or other method.      |
	 * |     | Support is optional.                                            |
	 * +-----+-----------------------------------------------------------------+
	 * | 4   | Non-Actuated 2 - when set to 1 causes a phase to respond to the |
	 * |     | Call To Non-Actuated 2 input (if present) or other method.      |
	 * |     | Support is optional.                                            |
	 * +-----+-----------------------------------------------------------------+
	 * | 5   | Non Lock Detector Memory - when set to 0 will cause the call to |
	 * |     | be locked at the beginning of the yellow interval. When set to  |
	 * |     | 1 call locking will depend on the detectorOptions object.       |
	 * +-----+-----------------------------------------------------------------+
	 * | 6   | Min. Vehicle Recall - when set to 1 causes recurring demand for |
	 * |     | vehicle service on the phase when that phase is not in its      |
	 * |     | Green interval.                                                 |
	 * +-----+-----------------------------------------------------------------+
	 * | 7   | Max Vehicle Recall - when set to 1 causes a call on a phase     |
	 * |     | such that the timing of the Green interval for that phase shall |
	 * |     | be extended to Maximum Green time.                              |
	 * +-----+-----------------------------------------------------------------+
	 * | 8   | Ped. Recall - when set to 1 causes a recurring pedestrian       |
	 * |     | demand which shall function in the same manner as an external   |
	 * |     | pedestrian call except that it shall not recycle the pedestrian |
	 * |     | service until a conflicting phase is serviced.                  |
	 * +-----+-----------------------------------------------------------------+
	 * | 9   | Soft Vehicle Recall - when set to 1 causes a call on a phase    |
	 * |     | when all conflicting phases are in green dwell or red dwell and |
	 * |     | there are no serviceable conflicting calls. Support is          |
	 * |     | optional.                                                       |
	 * +-----+-----------------------------------------------------------------+
	 * | 10  | Dual Entry Phase - in multi-ring configurations when set to 1   |
	 * |     | causes the phase to become active upon entry into a concurrency |
	 * |     | group (crossing a barrier) when no calls exist in its ring      |
	 * |     | within its concurrency group.                                   |
	 * +-----+-----------------------------------------------------------------+
	 * | 11  | Simultaneous Gap Disable - in multi-ring configurations when    |
	 * |     | set to 1 disables a gapped out phase from reverting to the      |
	 * |     | extensible portion. Support is optional.                        |
	 * +-----+-----------------------------------------------------------------+
	 * | 12  | Guaranteed Passage - when set to 1 enables an actuated phase    |
	 * |     | operating in volume density mode (using gap reduction) to       |
	 * |     | retain the right of way for the unexpired portion of the        |
	 * |     | Passage time following the decision to terminate the green due  |
	 * |     | to a reduced gap. Support is optional.                          |
	 * +-----+-----------------------------------------------------------------+
	 * | 13  | Actuated Rest In Walk - when set to 1 causes an actuated phase  |
	 * |     | to rest in Walk when there is no serviceable conflicting call   |
	 * |     | at the end of Walk Timing.                                      |
	 * +-----+-----------------------------------------------------------------+
	 * | 14  | Conditional Service Enable - in multi-ring configurations when  |
	 * |     | set to 1 causes a gapped/maxed phase to conditionally service a |
	 * |     | preceding actuated vehicle phase when sufficient time remains   |
	 * |     | before max time out of the phase(s) not prepared to terminate.  |
	 * |     | Support is optional.                                            |
	 * +-----+-----------------------------------------------------------------+
	 * | 15  | AddedInitialCalculation - If set (1) the CU shall compare       |
	 * |     | counts from all associated AddedInitial detectors and use the   |
	 * |     | largest count value for the calculations. If clear (0) the CU   |
	 * |     | shall sum all associated AddedInitial detector counts and use   |
	 * |     | this sum for the calculations. The ability to modify the        |
	 * |     | setting of this bit is optional.                                |
	 * +-----+-----------------------------------------------------------------+
	 */
	uint32_t phaseOptions;
	
	/* Phase ring number (1..maxRings) that identified the ring which contains
	 * the associated phase. This value must not exceed the maxRings object
	 * value.
	 */
	uint8_t phaseRing;
	
	/* Each octet contains a phase number (binary value) that may run
	 * concurrently with the associated phase. Phases that are contained in the
	 * same ring may NOT run concurrently.
	 */
	const char *const phaseConcurrency
} PhaseEntry;

/* Red, Yellow, & Green Output Status and Vehicle and Pedestrian Call for eight
 * Actuated Controller Unit Phases.
 */
typedef struct PhaseStatusGroupEntry
{
	/* The Phase StatusGroup number for objects in this row. This value shall
	 * not exceed the maxPhaseGroups object value.
	 */
	uint8_t phaseStatusGroupNumber;

	/* Phase Red Output Status Mask, when a bit = 1, the Phase Red is currently
	 * active. When a bit = 0, the Phase Red is NOT currently active.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupReds;

	/* Phase Yellow Output Status Mask, when a bit = 1, the Phase Yellow is
	 * currently active. When a bit = 0, the Phase Yellow is NOT currently
	 * active.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupYellows;
	
	/* Phase Green Output Status Mask, when a bit = 1, the Phase Green is
	 * currently active. When a bit = 0, the Phase Green is NOT currently
	 * active.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupGreens;

	/* Phase Dont Walk Output Status Mask, when a bit = 1, the Phase Dont Walk
	 * is currently active. When a bit = 0, the Phase Dont Walk is NOT currently
	 * active.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupDontWalks;

	/* Phase Ped. Clear Output Status Mask, when a bit = 1, the Phase Ped. Clear
	 * is currently active. When a bit = 0, the Phase Ped. Clear is NOT
	 * currently active.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupPedClears;
	
	/* Phase Walk Output Status Mask, when a bit = 1, the Phase Walk is
	 * currently active. When a bit = 0, the Phase Walk is NOT currently active.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupWalks;
	
	/* Phase Vehicle Call Status Mask, when a bit = 1, the Phase vehicle
	 * currently has a call for service. When a bit = 0, the Phase vehicle
	 * currently does NOT have a call for service.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupVehCalls;
	
	/* Phase Pedestrian Call Status Mask, when a bit = 1, the Phase pedestrian
	 * currently has a call for service. When a bit = 0, the Phase pedestrian
	 * currently does NOT have a call for service.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupPedCalls;
	
	/* Phase On Status Mask, when a bit = 1, the Phase is currently active. When
	 * a bit = 0, the Phase currently is NOT active. The phase is ON during the
	 * Green, Yellow, & Red Clearance intervals of that phase. It shall be
	 * permissible for this status to be True (bit=1) during the Red Dwell
	 * state.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupPhaseOns;
	
	/* Phase Next Status Mask, when a bit = 1, the Phase currently is committed
	 * to be NEXT in sequence & remains present until the phase becomes active
	 * (On/Timing). When a bit = 0, the Phase currently is NOT committed to be
	 * NEXT in sequence. The phase next to be serviced shall be determined at
	 * the end of the green interval of the terminating phase; except that if
	 * the decision cannot be made at the end of the Green interval, it shall
	 * not be made until after the end of all Vehicle Change & Clearance
	 * intervals.
	 *   Bit 7 = Phase number = (phaseStatusGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseStatusGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseStatusGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseStatusGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseStatusGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseStatusGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseStatusGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseStatusGroupNumber * 8) - 7
	 */
	uint8_t phaseStatusGroupPhaseNexts;
} PhaseStatusGroupEntry;

/* Phase Control for eight Actuated Controller Unit phases. */
typedef struct PhaseControlGroupEntry
{
	/* The Phase Control Group number for objects in this row. This value shall
	 * not exceed the maxPhaseGroups object value.
	 */
	uint8_t phaseControlGroupNumber;

	/* This object is used to allow a remote entity to omit phases from being
	 * serviced in the device. When a bit = 1, the device shall activate the
	 * System Phase Omit control for that phase. When a bit = 0, the device
	 * shall not activate the System Phase Omit control for that phase.
	 *   Bit 7 = Phase number = (phaseControlGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseControlGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseControlGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseControlGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseControlGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseControlGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseControlGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseControlGroupNumber * 8) - 7
	 * The device shall reset this object to ZERO when in BACKUP Mode. A write
	 * to this object shall reset the Backup timer to ZERO.
	 */
	uint8_t phaseControlGroupPhaseOmit;

	/* This object is used to allow a remote entity to omit peds from being
	 * serviced in the device. When a bit = 1, the device shall activate the
	 * System Ped Omit control for that phase. When a bit = 0, the device shall
	 * not activate the System Ped Omit control for that phase.
	 *   Bit 7 = Phase number = (phaseControlGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseControlGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseControlGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseControlGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseControlGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseControlGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseControlGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseControlGroupNumber * 8) - 7
	 * The device shall reset this object to ZERO when in BACKUP Mode. A write
	 * to this object shall reset the Backup timer to ZERO.
	 */
	uint8_t phaseControlGroupPedOmit;

	/* This object is used to allow a remote entity to hold phases in the
	 * device. When a bit = 1, the device shall activate the System Phase Hold
	 * control for that phase. When a bit = 0, the device shall not activate the
	 * System Phase Hold control for that phase.
	 *   Bit 7 = Phase number = (phaseControlGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseControlGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseControlGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseControlGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseControlGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseControlGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseControlGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseControlGroupNumber * 8) - 7
	 * The device shall reset this object to ZERO when in BACKUP Mode. A write
	 * to this object shall reset the Backup timer to ZERO.
	 */
	uint8_t phaseControlGroupHold;

	/* This object is used to apply force offs on a per phase basis. When a
	 * bit = 1, the device shall activate the System Phase Force Off control for
	 * that phase. When a bit = 0, the device shall not activate the System
	 * Phase Force Off control for that phase. When the phase green terminates,
	 * the associated bit shall be reset to 0.
	 *   Bit 7 = Phase number = (phaseControlGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseControlGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseControlGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseControlGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseControlGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseControlGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseControlGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseControlGroupNumber * 8) - 7
	 * The device shall reset this object to ZERO when in BACKUP Mode. A write
	 * to this object shall reset the Backup timer to ZERO.
	 */
	uint8_t phaseControlGroupForceOff;

	/* This object is used to allow a remote entity to place calls for vehicle
	 * service in the device. When a bit = 1, the device shall place a call for
	 * vehicle service on that phase. When a bit = 0, the device shall not place
	 * a call for vehicle service on that phase.
	 *   Bit 7 = Phase number = (phaseControlGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseControlGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseControlGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseControlGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseControlGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseControlGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseControlGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseControlGroupNumber * 8) - 7
	 * The device shall reset this object to ZERO when in BACKUP Mode. A write
	 * to this object shall reset the Backup timer to ZERO.
	 */
	uint8_t phaseControlGroupVehCall;

	/* This object is used to allow a remote entity to place calls for ped
	 * service in the device. When a bit = 1, the device shall place a call for
	 * ped service on that phase. When a bit = 0, the device shall not place a
	 * call for ped service on that phase.
	 *   Bit 7 = Phase number = (phaseControlGroupNumber * 8)
	 *   Bit 6 = Phase number = (phaseControlGroupNumber * 8) - 1
	 *   Bit 5 = Phase number = (phaseControlGroupNumber * 8) - 2
	 *   Bit 4 = Phase number = (phaseControlGroupNumber * 8) - 3
	 *   Bit 3 = Phase number = (phaseControlGroupNumber * 8) - 4
	 *   Bit 2 = Phase number = (phaseControlGroupNumber * 8) - 5
	 *   Bit 1 = Phase number = (phaseControlGroupNumber * 8) - 6
	 *   Bit 0 = Phase number = (phaseControlGroupNumber * 8) - 7
	 * The device shall reset this object to ZERO when in BACKUP Mode. A write
	 * to this object shall reset the Backup timer to ZERO.
	 */
	uint8_t phaseControlGroupPedCall;
} PhaseControlGroupEntry;

typedef struct VehicleDetectorEntry
{
	/* The vehicle detector number for objects in this row. The value shall not
	 * exceed the maxVehicleDetectors object value.
	 */
	uint8_t vehicleDetectorNumber;

	/* Vehicle Detector Options Parameter as follows:
	 * +-----+-----------------------------------------------------------------+
	 * | Bit | Function                                                        |
	 * +-----+-----------------------------------------------------------------+
	 * | 7   | Call - if set (1) the CU shall place a demand for vehicular     |
	 * |     | service on the assigned phase when the phase is not timing the  |
	 * |     | green interval.                                                 |
	 * +-----+-----------------------------------------------------------------+
	 * | 6   | Queue - if set (1) the CU shall extend the green interval of    |
	 * |     | the assigned phase until a gap occurs (no actuation) or until   |
	 * |     | the green has been active longer than the                       |
	 * |     | vehicleDetectorQueueLimit time. This is optional.               |
	 * +-----+-----------------------------------------------------------------+
	 * | 5   | AddedInitial - if set (1) the CU shall accumulate detector      |
	 * |     | actuation counts for use in the added initial calculations.     |
	 * |     | Counts shall be accumulated from the beginning of the yellow    |
	 * |     | interval to the beginning of the green interval.                |
	 * +-----+-----------------------------------------------------------------+
	 * | 4   | Passage - if set (1) the CU shall maintain a reset to the       |
	 * |     | associated phase passage timer for the duration of the detector |
	 * |     | actuation when the phase is green.                              |
	 * +-----+-----------------------------------------------------------------+
	 * | 3   | Red Lock Call - if set (1) the detector will lock a call to the |
	 * |     | assigned phase if an actuation occurs while the phase is not    |
	 * |     | timing Green or Yellow. This mode is optional.                  |
	 * +-----+-----------------------------------------------------------------+
	 * | 2   | Yellow Lock Call - if set (1) the detector will lock a call to  |
	 * |     | the assigned phase if an actuation occurs while the phase is    |
	 * |     | not timing Green.                                               |
	 * +-----+-----------------------------------------------------------------+
	 * | 1   | Occupancy Detector - if set (1) the detector collects data for  |
	 * |     | the associated detector occupancy object(s). This capability    |
	 * |     | may not be supported on all detector inputs to a device.        |
	 * +-----+-----------------------------------------------------------------+
	 * | 0   | Volume Detector - if set (1) the detector collects data for the |
	 * |     | associated detector volume object(s). This capability may not   |
	 * |     | be supported on all detector inputs to a device.                |
	 * +-----+-----------------------------------------------------------------+
	 */
	uint8_t vehicleDetectorOptions;

	/* This object contains assigned phase number for the detector input
	 * associated with this row. The associated detector call capability is
	 * enabled when this object is set to a non-zero value. The value shall not
	 * exceed the value of maxPhases.
	 */
	uint8_t vehicleDetectorCallPhase;

	/* Detector Switch Phase Parameter (i.e., Phase Number). The phase to which
	 * a vehicle detector actuation shall be switched when the assigned phase is
	 * Yellow or Red and the Switch Phase is Green.
	 */
	uint8_t vehicleDetectorSwitchPhase;

	/* Detector Delay Parameter in tenth seconds (0–255.0 sec). The period a
	 * detector actuation (input recognition) shall be delayed when the phase is
	 * not Green.
	 */
	uint8_t vehicleDetectorDelay;

	/* Detector Extend Parameter in tenth seconds (0–25.5 sec). The period a
	 * vehicle detector actuation (input duration) shall be extended from the
	 * point of termination, when the phase is Green.
	 */
	uint8_t vehicleDetectorExtend;

	/* Detector Queue Limit parameter in seconds (0-255 sec). The length of time
	 * that an actuation from a queue detector may continue into the phase green.
	 * This time begins when the phase becomes green and when it expires any
	 * associated detector inputs shall be ignored. This time may be shorter due
	 * to other overriding device parameters
	 * (i.e. Maximum time, Force Off’s, ...).
	 */
	uint8_t vehicleDetectorQueueLimit;

	/* Detector No Activity diagnostic Parameter in minutes (0–255 min.). If an
	 * active detector does not exhibit an actuation in the specified period, it
	 * is considered a fault by the diagnostics and the detector is classified
	 * as Failed. A value of 0 for this object shall disable this diagnostic for
	 * this detector.
	 */
	uint8_t vehicleDetectorNoActivity;

	/* Detector Maximum Presence diagnostic Parameter in minutes (0-255 min.).
	 * If an active detector exhibits continuous detection for too long a
	 * period, it is considered a fault by the diagnostics and the detector is
	 * classified as Failed. A value of 0 for this object shall disable this
	 * diagnostic for this detector.
	 */
	uint8_t vehicleDetectorMaxPresence;

	/* Detector Erratic Counts diagnostic Parameter in counts/minute
	 * (0-255 cpm). If an active detector exhibits excessive actuations, it is
	 * considered a fault by the diagnostics and the detector is classified as
	 * Failed. A value of 0 for this object shall disable this diagnostic for
	 * this detector.
	 */
	uint8_t vehicleDetectorErraticCounts;

	/* Detector Fail Time in seconds (0..255). If a detector diagnostic
	 * indicates that the associated detector input is failed, then a call shall
	 * be placed on the associated phase during all non-green intervals. When
	 * each green interval begins the call shall be maintained for the length of
	 * time specified by this object and then removed. If the value of this
	 * object equals the maximum value (255) then a constant call shall be
	 * placed on the associated phase (max recall). If the value of this object
	 * equals zero then no call shall be placed on the associated phase for any
	 * interval (no recall). Compliant devices may support a limited capability
	 * for this object (i.e. only max recall or max recall and no recall). At a
	 * minimum the max recall setting must be supported.
	 */
	uint8_t vehicleDetectorFailTime;

	/* This object shall return indications of detector alarms. Detector Alarms
	 * are indicated as follows:
	 *
	 * +-----+-----------------------------------------------------------------+
	 * | Bit | Definition                                                      |
	 * +-----+-----------------------------------------------------------------+
	 * | 0   | No Activity Fault: This detector has been flagged as            |
	 * |     | non-operational due to lower than expected activity by the CU   |
	 * |     | detector diagnostic.                                            |
	 * +-----+-----------------------------------------------------------------+
	 * | 1   | Max Presence Fault: This detector has been flagged as           |
	 * |     | non-operational due to a presence indicator that exceeded the   |
	 * |     | maximum expected time by the CU detector diagnostic.            |
	 * +-----+-----------------------------------------------------------------+
	 * | 2   | Erratic Output Fault: This detector has been flagged as         |
	 * |     | non-operational due to erratic outputs (excessive counts) by    |
	 * |     | the CU detector diagnostic.                                     |
	 * +-----+-----------------------------------------------------------------+
	 * | 3   | Communications Fault: Communications to the device (if present) |
	 * |     | have failed.                                                    |
	 * +-----+-----------------------------------------------------------------+
	 * | 4   | Configuration Fault: Detector is assigned but is not supported. |
	 * +-----+-----------------------------------------------------------------+
	 * | 5-6 | Reserved.                                                       |
	 * +-----+-----------------------------------------------------------------+
	 * | 7   | Other Fault: The detector has failed due to some other cause.   |
	 * +-----+-----------------------------------------------------------------+
	 *
	 * Once set a bit shall maintain its state as long as the condition exists.
	 * The bit shall clear when the condition no longer exists.
	 */
	uint8_t vehicleDetectorAlarms;

	/* This object shall return detector device reported alarms (via some
	 * communications mechanism). Inductive Loop Detector Alarms are indicated
	 * as follows:
	 *
	 * +-----+-----------------------------------------------------------------+
	 * | Bit | Definition                                                      |
	 * +-----+-----------------------------------------------------------------+
	 * | 0   | Other                                                           |
	 * +-----+-----------------------------------------------------------------+
	 * | 1   | Watchdog Fault: This detector has been flagged as               |
	 * |     | non-operational due to a watchdog error.                        |
	 * +-----+-----------------------------------------------------------------+
	 * | 2   | Open Loop Fault: This detector has been flagged as              |
	 * |     | non-operational due to an open loop (broken wire).              |
	 * +-----+-----------------------------------------------------------------+
	 * | 3   | Shorted Loop Fault: This detector has been flagged as           |
	 * |     | non-operational due to a shorted loop wire.                     |
	 * +-----+-----------------------------------------------------------------+
	 * | 4   | Excessive Change Fault: This detector has been flagged as       |
	 * |     | non-operational due to an inductance change that exceeded       |
	 * |     | expected values.                                                |
	 * +-----+-----------------------------------------------------------------+
	 * | 5-7 | Reserved.                                                       |
	 * +-----+-----------------------------------------------------------------+
	 *
	 * Once set a bit shall maintain its state as long as the condition exists.
	 * The bit shall clear when the condition no longer exists.
	 */
	uint8_t vehicleDetectorReportedAlarms;

	/* This object when set to TRUE (non-zero) shall cause the CU to command the
	 * associated detector to reset. This object shall automatically return to
	 * FALSE (zero) after the CU has issued the reset command.
	 * NOTE: this may affect other detectors (detector channels) that are
	 * physically attached to a common reset line.
	 */
	uint8_t vehicleDetectorReset;
} VehicleDetectorEntry;

/* A group (row) of detector status. */
typedef struct VehicleDetectorStatusGroupEntry
{
	/* The detector status group number for objects in this row. This value
	 * shall not exceed the maxVehicleDetectorStatusGroups object value.
	 */
	uint8_t vehicleDetectorStatusGroupNumber;

	/* This object shall return the detection status of each detector associated
	 * with the group. Each detector shall be represented as ON (detect) or OFF
	 * (no-detect) by individual bits in this object. If a detector is ON then
	 * the associated bit shall be set (1). If a detector is OFF then the
	 * associated bit shall be clear (0).
	 *   Bit 7 = Detector number = ( vehicleDetectorStatusGroupNumber * 8)
	 *   Bit 6 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 1
	 *   Bit 5 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 2
	 *   Bit 4 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 3
	 *   Bit 3 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 4
	 *   Bit 2 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 5
	 *   Bit 1 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 6
	 *   Bit 0 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 7
	 */
	uint8_t vehicleDetectorStatusGroupActive;

	/* This object shall return the alarm status of the detectors associated
	 * with the group. Each detector alarm status shall be represented as ON or
	 * OFF by individual bits in this object. If any detector alarm (defined in
	 * the vehicleDetectorAlarm object) is active the associated bit shall be
	 * set (1). If a detector alarm is not active the associated bit shall be
	 * clear (0).
	 *   Bit 7 = Detector number = ( vehicleDetectorStatusGroupNumber * 8)
	 *   Bit 6 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 1
	 *   Bit 5 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 2
	 *   Bit 4 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 3
	 *   Bit 3 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 4
	 *   Bit 2 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 5
	 *   Bit 1 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 6
	 *   Bit 0 = Detector number = ( vehicleDetectorStatusGroupNumber * 8) - 7
	 */
	uint8_t vehicleDetectorStatusGroupAlarms;
} VehicleDetectorStatusGroupEntry;

typedef struct VolumeOccupancyEntry
{
	/* Detector Volume data collected over the Volume / Occupancy Period. This
	 * value shall range from 0 to 254 indicating the volume of traffic crossing
	 * the associated detectorNumber during the collection period. The value 255
	 * shall indicate volume overflow.
	 */
	uint8_t detectorVolume;

	/* Detector Occupancy data collected over the Volume / Occupancy Period or
	 * Detector Unit Diagnostic Information. The value of the object shall
	 * indicate occupancy or detector diagnostic information as follows:
	 *
	 * +---------+-------------------------------------------------------------+
	 * | Range   | Meaning                                                     |
	 * +---------+-------------------------------------------------------------+
	 * | 0-200   | Detector Occupancy in 0.5% Increments                       |
	 * +---------+-------------------------------------------------------------+
	 * | 201-209 | Reserved                                                    |
	 * +---------+-------------------------------------------------------------+
	 * | 210     | Max Presence Fault                                          |
	 * +---------+-------------------------------------------------------------+
	 * | 211     | No Activity Fault                                           |
	 * +---------+-------------------------------------------------------------+
	 * | 212     | Open loop Fault                                             |
	 * +---------+-------------------------------------------------------------+
	 * | 213     | Shorted loop Fault                                          |
	 * +---------+-------------------------------------------------------------+
	 * | 214     | Excessive Change Fault                                      |
	 * +---------+-------------------------------------------------------------+
	 * | 215     | Reserved                                                    |
	 * +---------+-------------------------------------------------------------+
	 * | 216     | Watchdog Fault                                              |
	 * +---------+-------------------------------------------------------------+
	 * | 217     | Erratic Output Fault                                        |
	 * +---------+-------------------------------------------------------------+
	 * | 218-255 | Reserved                                                    |
	 * +---------+-------------------------------------------------------------+
	 *
	 * Faults shall be indicated for all collection periods during which a fault
	 * is detected if either occupancy data or volume data is being collected.
	 * The highest numbered fault shall be presented if more than one fault is
	 * active (i.e. indicate OpenLoop rather than NoActivity).
	 */
	uint8_t detectorOccupancy;
} VolumeOccupancyEntry;

typedef struct VolumeOccupancyReport
{
	uint8_t               volumeOccupancySequence;
	uint8_t               volumeOccupancyPeriod;
	uint8_t               activeVolumeOccupancyDetectors;
	VolumeOccupancyEntry *volumeOccupancyTable;

} VolumeOccupancyReport;

typedef struct PedestrianDetectorEntry
{
	/* The pedestrianDetector number for objects in this row. The value shall
	 * not exceed the maxPedestrianDetectors object value.
	 */
	uint8_t pedestrianDetectorNumber;

	/* This object contains assigned phase number for the pedestrian detector
	 * input associated with this row. The associated detector call capability
	 * is enabled when this object is set to a non-zero value. The value shall
	 * not exceed the value of maxPhases.
	 */
	uint8_t pedestrianDetectorCallPhase;

	/* Pedestrian Detector No Activity diagnostic Parameter in minutes
	 * (0–255 min.). If an active detector does not exhibit an actuation in the
	 * specified period, it is considered a fault by the diagnostics and the
	 * detector is classified as Failed. A value of 0 for this object shall
	 * disable this diagnostic for this detector.
	 */
	uint8_t pedestrianDetectorNoActivity;

	/* Pedestrian Detector Maximum Presence diagnostic Parameter in minutes
	 * (0-255 min.). If an active detector exhibits continuous detection for too
	 * long a period, it is considered a fault by the diagnostics and the
	 * detector is classified as Failed. A value of 0 for this object shall
	 * disable this diagnostic for this detector.
	 */
	uint8_t pedestrianDetectorMaxPresence;

	/* Pedestrian Detector Erratic Counts diagnostic Parameter in counts/minute
	 * (0-255 cpm). If an active detector exhibits excessive actuations, it is
	 * considered a fault by the diagnostics and the detector is classified as
	 * Failed. A value of 0 for this object shall disable this diagnostic for
	 * this detector.
	 */
	uint8_t pedestrianDetectorErraticCounts;

	/* This object shall return indications of detector alarms. Detector Alarms
	 * are indicated as follows:
	 *
	 * +-----+-----------------------------------------------------------------+
	 * | Bit | Definition                                                      |
	 * +-----+-----------------------------------------------------------------+
	 * | 0   | No Activity Fault: This detector has been flagged as            |
	 * |     | non-operational due to lower than expected activity by the CU   |
	 * |     | detector diagnostic.                                            |
	 * +-----+-----------------------------------------------------------------+
	 * | 1   | Max Presence Fault: This detector has been flagged as           |
	 * |     | non-operational due to a presence indicator that exceeded the   |
	 * |     | maximum expected time by the CU detector diagnostic.            |
	 * +-----+-----------------------------------------------------------------+
	 * | 2   | Erratic Output Fault: This detector has been flagged as         |
	 * |     | non-operational due to erratic outputs (excessive counts) by    |
	 * |     | the CU detector diagnostic.                                     |
	 * +-----+-----------------------------------------------------------------+
	 * | 3   | Communications Fault: Communications to the device (if present) |
	 * |     | have failed.                                                    |
	 * +-----+-----------------------------------------------------------------+
	 * | 4   | Configuration Fault: Detector is assigned but is not supported. |
	 * +-----+-----------------------------------------------------------------+
	 * | 5-6 | Reserved.                                                       |
	 * +-----+-----------------------------------------------------------------+
	 * | 7   | Other Fault: The detector has failed due to some other cause.   |
	 * +-----+-----------------------------------------------------------------+
	 *
	 * Once set a bit shall maintain its state as long as the condition exists.
	 * The bit shall clear when the condition no longer exists.
	 */
	uint8_t pedestrianDetectorAlarms;
} PedestrianDetectorEntry;

/* This node shall contain objects that configure, monitor or control phase
 * functions for this device.
 */
typedef struct Phase
{
	/* The Maximum Number of Phases this Actuated Controller Unit supports. This
	 * object indicates the maximum rows which shall appear in the phaseTable
	 * object.
	 */
	uint8_t maxPhases;

	PhaseEntry *phaseTable;

	/* The Maximum Number of Phase Groups (8 Phases per group) this Actuated
	 * Controller Unit supports. This value is equal to TRUNCATE
	 * [(maxPhases + 7) / 8]. This object indicates the maximum rows which shall
	 * appear in the phaseStatusGroupTable and phaseControlGroupTable.
	 */
	uint8_t maxPhaseGroups;

	/* A table containing Actuated Controller Unit Phase Output (Red, Yellow, &
	 * Green) and Call (vehicle & pedestrian) status in groups of eight Phases.
	 * The number of rows in this table is equal to the maxPhaseGroups object.
	 */
	PhaseStatusGroupEntry *phaseStatusGroupTable;

	/* A table containing Actuated Controller Unit Phase Control in groups of
	 * eight phases. The number of rows in this table is equal to the
	 * maxPhaseGroups object. This table is optional for Actuated Controller
	 * Units conforming to this specification. If implemented then all objects
	 * in this table shall be implemented.
	 */
	PhaseControlGroupEntry *phaseControlGroupTable;
} Phase;

/* This defines a node for supporting detector objects. */
typedef struct Detector
{
	/* The Maximum Number of Vehicle Detectors this Actuated Controller Unit
	 * supports. This object indicates the maximum rows which shall appear in
	 * the vehicleDetectorTable object.
	 */
	uint8_t maxVehicleDetectors;

	/* A table containing Actuated Controller Unit vehicle detector parameters.
	 * The number of rows in this table is equal to the maxVehicleDetectors
	 * object.
	 */
	VehicleDetectorEntry *vehicleDetectorTable;

	/* The maximum number of detector status groups (8 detectors per group) this
	 * device supports. This value is equal to TRUNCATE
	 * [(maxVehicleDetectors + 7 ) / 8]. This object indicates the maximum
	 * number of rows which shall appear in the vehicleDetectorStatusGroupTable
	 * object.
	 */
	uint8_t maxVehicleDetectorStatusGroups;

	/* A table containing detector status in groups of eight detectors. The
	 * number of rows in this table is equal to the
	 * maxVehicleDetectorStatusGroups object.
	 */
	VehicleDetectorStatusGroupEntry *vehicleDetectorStatusGroupTable;

	/* This node contains the objects necessary to support volume / occupancy
	 * reporting.
	 */
	VolumeOccupancyReport volumeOccupancyReport;

	/* The Maximum Number of Pedestrian Detectors this Actuated Controller Unit
	 * supports. This object indicates the maximum rows which shall appear in
	 * the pedestrianDetectorTable object.
	 */
	uint8_t maxPedestrianDetectors;

	/* A table containing Actuated Controller Unit pedestrian detector
	 * parameters. The number of rows in this table is equal to the
	 * maxPedestrianDetectors object.
	 */
	PedestrianDetectorEntry *pedestrianDetectorTable;
} Detector;

typedef struct Unit
{
	/* Unit Start up Flash time parameter in seconds (0 to 255 sec). The
	 * period/state (Start-Up Flash occurs when power is restored following a
	 * device defined power interruption. During the Start-Up Flash state, the
	 * Fault Monitor and Voltage Monitor outputs shall be inactive (if present).
	 */
	uint8_t unitStartUpFlash;
} Unit;

typedef struct ASC
{
	Phase    phase;
	Detector detector;
	Unit     unit;
} ASC;

#endif /* ASC_H */
