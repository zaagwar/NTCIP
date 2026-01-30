#ifndef COMMON_OBJECTS_H
#define COMMON_OBJECTS_H

#include <Common.h>

enum Month
{
	JANUARY   = 1,
	FEBRUARY  = 2,
	MARCH     = 3,
	APRIL     = 4,
	MAY       = 5,
	JUNE      = 6,
	JULY      = 7,
	AUGUST    = 8,
	SEPTEMBER = 9,
	OCTOBER   = 10,
	NOVEMBER  = 11,
	DECEMBER  = 12,
	ABSOLUTE  = 13,
	DISABLED  = 14
};

enum Day
{
	SUNDAY    = 1,
	MONDAY    = 2,
	TUESDAY   = 3,
	WEDNESDAY = 4,
	THURSDAY  = 5,
	FRIDAY    = 6,
	SATURDAY  = 7
};

enum Occurrence
{
	FIRST        = 1,
	SECOND       = 2,
	THIRD        = 3,
	FOURTH       = 4,
	LASE         = 5,
	SECOND_LAST  = 6,
	THIRD_LAST   = 7,
	FOURTH_LAST  = 8,
	SPECIFIC_DAY = 9
};

/* This object defines an entry in the module table. */
typedef struct ModuleTableEntry
{
	/* This object contains the row number (1 .. 255) within this table for the
	 * associated module.
	 */
	uint8_t moduleNumber;

	/* This object contains the device node number of the device-type, e.g., an
	 * ASC signal controller would have an OID of 1.3.6.1.4.1.1206.4.2.1.
	 */
	const char *const moduleDeviceNode;

	/* This object specifies the manufacturer of the associated module.
	 * A null-string shall be transmitted if this object has no entry.
	 */
	const char *const moduleMake;

	/* This object specifies the model number (hardware) or firmware reference
	 * (software) of the associated module. A null-string shall be transmitted
	 * if this object has no entry.
	 */
	const char *const moduleModel;

	/* This object specifies the version of the associated module. If the
	 * moduleType has a value of software, the value of this object shall
	 * include the date on which the software was released as a string in the
	 * form of YYYYMMDD, it shall be followed by a space, a hyphen, another
	 * space, the lower-case letter ‘v’, followed by a version or configuration
	 * number. Preceding zeros shall be required for the date. For example,
	 * version 7.03.02 of the software released on July 5, 2002 would be
	 * presented as 20020705 – v7.03.02 A null-string shall be transmitted if
	 * this object has no entry.
	 */
	const char *const moduleVersion;

	/* This object specifies whether the associated module is a hardware or
	 * software module.
	 */
	enum
	{
		MODULE_TYPE_OTHER    = 1,
		MODULE_TYPE_HARDWARE = 2,
		MODULE_TYPE_SOFTWARE = 3
	} moduleType;
} ModuleTableEntry;

/* This node is an identifier used to group all objects for support of
 * configuration functions that are common to most device types.
 */
typedef struct GlobalConfiguration
{
	/* Specifies a relatively unique ID (e.g., this could be a counter, a
	 * check-sum, etc.) for all user-changeable parameters of the particular
	 * device-type currently implemented in the device. Often this ID is
	 * calculated using a CRC algorithm. This value shall be calculated when a
	 * change of any static database object has occurred. The value reported by
	 * this object shall not change unless there has been a change in the static
	 * data since the last request. If the actual objects, which are to be
	 * included to create this object value, are not defined in the actual
	 * device-level standard such as 1202 or 1203, then the general guidance is
	 * to include all configuration objects that are stored in a type of memory
	 * that survives power outages. A management station can use this object to
	 * detect any change in the static database objects by monitoring this value
	 * after it has established a baseline.
	 */
	uint16_t globalSetIDParameter;

	/* The number of rows that are listed in the globalModuleTable. */
	uint8_t globalMaxModules;

	/* A table containing information regarding manufacturer of software and
	 * hardware and the associated module models and version numbers as well as
	 * an indicator if the module is hardware or software related. The number of
	 * rows in this table shall equal the value of the globalMaxModules object.
	 */
	ModuleTableEntry *globalModuleTable;

	/* For use in this object, an ASCII string that shall identify all of the
	 * standard document numbers that define or reference MIBs upon which the
	 * device is based. Where applicable, profiles shall be referenced rather
	 * than the base standards. The version string shall be constructed as
	 * follows: The acronym of the standards development organization (or other
	 * body) that developed and approved the standard; a space; the standards
	 * document number; a colon; and the documents version number as designated
	 * by the standards development organization (or other body). Separate
	 * entries in the list of standards shall be separated by a carriage return
	 * (0x0d) and line feed (0x0a). In the case of NTCIP documents prior to
	 * formal approval, the version number shall be the version number in the
	 * form of lower case ‘v’ followed by the major version followed by a period
	 * followed by the minor revision. In the case of approved NTCIP standards,
	 * the publication year shall precede the version number. In the case of
	 * amended NTCIP standards, the version number shall be replaced by the four
	 * digit year of publication of the published standard followed by the upper
	 * case letter ‘A’, followed by the amendment number.
	 *
	 * For example, a message sign may have the following value for this object:
	 *   NTCIP 1201:v02.19
	 *   NTCIP 1203:1997A1
	 *   NTCIP 2101:2001 v01.19
	 *   NTCIP 2103:v01.13
	 *   NTCIP 2201:v01.14
	 *   NTCIP 2301:2001 v01.08
	 */
	const char *const controllerBaseStandards;
} GlobalConfiguration;

/* This node is an identifier used to group those objects used to manage a
 * transaction. A transaction is a SET of one or more database parameters that
 * have inter-relationships with other database parameters, as such a SET for
 * any one of these objects must be validated against a set of consistency
 * checks and may potentially require the setting of a large number of objects
 * simultaneously. Thus, the mode described by these objects allow for such a
 * large database download. Any device standard that allows this feature shall
 * define which objects are database parameters versus status or control
 * objects.
 */
typedef struct GlobalDatabaseManagement
{
	/* This object provides transaction control for device configuration. The
	 * transaction mode changes the behavior of the agent to force buffering of
	 * database objects until all related database objects have been modified.
	 * In the normal mode, SET operations to any database object shall either be
	 * stored in a device’s database immediately with no regard to whether other
	 * changes will be made or be rejected (as defined in the device-specific
	 * Information Profile). In the transaction mode, SET operations to any
	 * database object shall be buffered until a verify state performs a
	 * consistency check. When the consistency check completes, the device
	 * automatically transitions to the done state where a normal or transaction
	 * command may be issued. A database object is a user-provided piece of
	 * setup information (or it may be defined in an information profile) that
	 * is necessary for the proper operation of a device. It is static in nature
	 * in that the agent would never change it without direction from the
	 * management station. For example, a parameter that defines a default mode
	 * of operation would be a database object. A parameter that indicates the
	 * current state of the device would not be a database object. The states
	 * and commands are defined as:
	 *
	 * NORMAL: SET operations behave as normal SETs and shall have an immediate
	 * effect on the value of any database objects used by the device if none of
	 * the objects contained in the operation require the use of the transaction
	 * mode (as defined in the device-specific Information Profile). A SET
	 * operation containing any database object that requires the use of
	 * transaction mode shall result in a genErr. This is the default state of
	 * this object. The only command that may be written to dbCreateTransaction
	 * while in this state is TRANSACTION. Any other values written to this
	 * object in this state shall result in an error response of ‘badValue’.
	 *
	 * TRANSACTION: A SET operation of one or more database objects that use the
	 * same community name as used in the request for the TRANSACTION state are
	 * buffered by the agent device for later consistency checks and a normal
	 * response is returned. A SET operation of one or more database objects
	 * using different community names shall result in a genErr with the index
	 * set to zero. A SET operation without a community name field (e.g., an
	 * STMP operation) shall be buffered by the agent device for later
	 * consistency checks and a normal response is returned. Standard SYNTAX
	 * checking shall take place at the time of the SET operation. A transaction
	 * may consist of multiple SET operations over multiple frames. A SET
	 * operation for one or more non-database objects shall be processed as
	 * normal even if it uses another community name, except for this (i.e., the
	 * dbCreateTransaction) object. A SET operation containing both database and
	 * non-database objects shall be processed in full according to these two
	 * rules. Thus, if it contains the same community name as used in the
	 * request for the TRANSACTION state, the non-database objects shall be
	 * stored immediately while the database objects shall be buffered. If it
	 * uses a different community name, the entire request will be rejected and
	 * a genErr with an index of zero shall be returned. GET operations on any
	 * object shall return the values of the data stored in the controller and
	 * shall ignore any values contained in the buffer. Any valid community name
	 * may read this (dbCreateTransaction) object when in this state, but only
	 * the community name used to command the object to the transaction mode and
	 * the administrator community name can set this object. A set from any
	 * other community name shall result in a genErr with an index of zero. The
	 * only commands that can be written to dbCreateTransaction while in this
	 * state are VERIFY and NORMAL. A VERIFY command will change the state to
	 * VERIFY. If a NORMAL command is received, all buffered data is discarded
	 * and the state is returned to NORMAL. Any other values written to this
	 * object when in this state shall result in an error response of
	 * ‘badValue’.
	 *
	 * VERIFY: Specific database objects are checked for consistency. When
	 * consistency checks are complete the device will automatically advance to
	 * the DONE state. The state of dbCreateTransaction cannot be changed when
	 * in the VERIFY state. Any values written to this object in this state
	 * shall result in an error response of ‘badValue’. The consistency check
	 * analyzes certain critical objects 'in context' and treats them as an
	 * interrelated whole rather than separate non-related data items. The
	 * consistency check rules are not defined in NTCIP 1201 v03, since these
	 * are device and implementation specific. Where applicable, the consistency
	 * check rules are defined in application specific object definition
	 * standards. A specific implementation may add additional checks
	 * beyond those defined in NTCIP standards. A SET operation containing any
	 * database objects while in the VERIFY state shall result in a genErr with
	 * the index set to zero.
	 *
	 * DONE: This state is entered automatically once consistency checks have
	 * completed in the VERIFY mode. The value of dbVerifyStatus and
	 * dbVerifyError indicate whether the consistency check found any errors.
	 * A SET operation containing any database objects while in the DONE state
	 * shall result in a genErr with the index set to zero. Any valid community
	 * name may read this (dbCreateTransaction) object when in this state, but
	 * only the community name used to command the object to the transaction
	 * mode and the administrator community name can set this object. A set from
	 * any other community name shall result in a genErr with an index of zero.
	 * The only commands that can be written to dbCreateTransaction while in
	 * this state are NORMAL and TRANSACTION. Any other values written to this
	 * object in this state shall result in an error response of ‘badValue’. If
	 * a NORMAL command is issued and dbVerifyStatus indicates doneWithNoError,
	 * the buffered data is transferred to the device memory and the state is
	 * returned to NORMAL. If a NORMAL command is issued and dbVerifyStatus
	 * indicates something other than doneWithNoError then the buffered data is
	 * discarded and the state is returned to NORMAL. If a TRANSACTION command
	 * is issued, regardless of dbVerifyStatus, no action takes place (the
	 * buffered data is not changed) and the TRANSACTION state is re-entered.

               +-----------------+------------+------------+-----------------+
               | TRANSACTION     | VERIFY     | NORMAL     | DONE            |
 +-------------+-----------------+------------+------------+-----------------+
 | NORMAL      | TRANSACTION (1) | NORMAL (2) | NORMAL (2) | NORMAL      (2) |
 | TRANSACTION | TRANSACTION (2) | VERIFY (3) | NORMAL (4) | TRANSACTION (2) |
 | VERIFY (7)  | VERIFY      (2) | VERIFY (2) | VERIFY (2) | VERIFY      (2) |
 | DONE   (8)  | TRANSACTION (5) | DONE   (2) | NORMAL (6) | DONE        (2) |
 +-------------+-----------------+------------+------------+-----------------+

	* Operational procedures and error responses:
	* (1) Once a copy of all database objects is placed in a buffer, the state
	*     is changed to transaction and error response indicates noError. If the
	*     operation fails, the state remains the same and error response
	*     indicates genErr.
	* (2) No action takes place, the state remains the same, but response
	*     indicates badValue.
	* (3) The state is changed to verify, a consistency check is started, and
	*     response indicates noError. Once the consistency check is completed,
	*     the state automatically changes to done.
	* (4) The buffered copy of all database objects is discarded, the state is
	*     changed to normal, and response indicates noError.
	* (5) The buffered copy of all database objects is not changed or reloaded,
	*     the state is changed to transaction, and response indicates noError.
	* (6) If dbVerifyStatus indicates doneWithNoError, then the copy of all
	*     database objects is transferred to memory, the state is changed to
	*     normal and response indicates noError. If dbVerifyStatus indicates
	*     doneWithError then the buffered data is discarded, the state is
	*     changed to NORMAL, and response indicates noError.
	* (7) The state automatically changes to done when the consistency check
	*     completes.
	* (8) dbVerifyStatus and dbVerifyError are only valid in this state.
	* (9) All SET operations on this (dbCreateTransaction) parameter shall be
	*     made using a protocol that uses a community name, or equivalent field
	*     (e.g., SNMP).
	*/
	enum
	{
		NORMAL      = 1,
		TRANSACTION = 2,
		VERIFY      = 3,
		DONE        = 6
	} dbCreateTransaction;


	/* This object has been deprecated since 1996.
	 * This object returns the current error status of the transaction. The
	 * value of this object is only valid when the dbCreateTransaction object is
	 * in the Done or Error state.
	 */
	enum
	{
		tooBig      = 1,
		noSuchName  = 2,
		badValue    = 3,
		readOnly    = 4,
		genError    = 5,
		updateError = 6,
		noError     = 7
	} dbErrorType;

	/* This object has been deprecated since 1996.
	 * This object contains the object identifier of the first object in the
	 * transaction buffer that caused an error while dbCreateTransaction object
	 * was in the Verifying or Updating state. The value of this object is only
	 * valid when the dbCreateTransaction object is in the Error state. It is
	 * undefined when the dbCreateTransaction object is in other states.
	 */
	const char *const dbErrorID;

	/* This object has been deprecated since 1996.
	 * This object contains the transaction ID value that is to be contained in
	 * all SET operation writes while the dbCreateTransaction object is not in
	 * the Normal state. During transaction operations every SET command shall
	 * begin with a write to this object with the current value of this object.
	 * If a SET operation is performed without writing to this object, or with a
	 * value that does not match the current value, then an error response of
	 * ‘genError’ shall be returned. This mechanism is used to determine that
	 * the same management station that started the transaction is performing
	 * the SET operations that are being buffered or modifying the state of
	 * dbCreateTransaction.
	 */
	const char *const dbTransactionID;

	/* This object has been deprecated since 1996.
	 * This object is used to create unique transaction ID’s for management
	 * stations to use when starting transactions using the dbCreateTransaction
	 * object. This object will be incremented by one every time it is read, so
	 * that different values will be returned for each read. Management stations
	 * wishing to start a transaction should first read the dbCreateTransaction
	 * object to verify that it is in the Normal state. If so then the
	 * management shall GET dbMakeID to obtain a transaction ID to use, then
	 * SET dbCreateTransaction to startCmd and dbTransactionID to the value just
	 * received. If the response to the SET operation is ‘noError’ then the
	 * management station has started a transaction. If the response to the SET
	 * operation is ‘genError’ then the management station should read the
	 * dbCreateTransaction and dbTransactionID objects to ensure that the error
	 * was not due to a communications retry. If the dbCreateTransaction is in
	 * the Transaction state, and the dbTransactionID is the same value returned
	 * by the read of this object, then the management station is the owner of
	 * the transaction. If the dbTransactionID does not match the value
	 * originally returned by this object, then the management station is not
	 * the owner of the transaction and must wait until the dbCreateTransaction
	 * object returns to the Normal state before attempting to start the
	 * transaction.
	 */
	uint8_t dbMakeID;

	/* This object indicates the current status of verify (consistency checking)
	 * processing. The value of this object is only meaningful when the
	 * dbCreateTransaction object is in the Verify or Done state.
	 */
	enum
	{
		notDone         = 1,
		doneWithError   = 2,
		doneWithNoError = 3
	} dbVerifyStatus;

	/* This object contains a textual description of or a reference to an error
	 * that was found by the verify (consistency checking) processing. The value
	 * of this object is only meaningful when the dbCreateTransaction object is
	 * in the Done state and the dbVerifyStatus object is in the doneWithError
	 * state.
	 */
	const char *const dbVerifyError;
} GlobalDatabaseManagement;

typedef struct TimeBaseScheduleEntry
{
	/* The time base schedule number for objects in this row. The value of this
	 * object shall not exceed the value of the maxTimeBaseScheduleEntries
	 * object. The activation of a scheduled entry shall occur whenever allowed
	 * by all other objects within this table.
	 */
	uint16_t timeBaseScheduleNumber;


	/* The Month(s) Of the Year that the schedule entry shall be allowed. Each
	 * bit represents a specific month. If the bit is set to one (1), then the
	 * scheduled entry shall be allowed during the associated month. If the bit
	 * is set to zero (0), then the scheduled entry shall not be allowed during
	 * the associated month. The bits are defined as:
	 *
	 *     Bit      | Month of Year
	 *     ---------+-------------
	 *     0        | Reserved
	 *     1        | January
	 *     2        | February
	 *     3        | March
	 *     4        | April
	 *     5        | May
	 *     6        | June
	 *     7        | July
	 *     8        | August
	 *     9        | September
	 *     10       | October
	 *     11       | November
	 *     12       | December
	 *     13 .. 15 | Reserved
	 *
	 * Thus, a value of six (6) would indicate that the entry would only be
	 * allowed during the months of January and February. A value of zero (0)
	 * shall indicate that this row has been disabled.
	 */
	uint16_t timeBaseScheduleMonth;

	/* The Day(s) Of Week that the schedule entry shall be allowed. Each bit
	 * represents a specific day of the week. If the bit is set to one (1), then
	 * the scheduled entry shall be allowed during the associated DOW. If the
	 * bit is set to zero (0), then the scheduled entry shall not be allowed
	 * during the associated DOW. The bits are defined as:
	 * Bit Day of Week
	 * 0 Reserved ('Holiday', not defined by this standard)
	 *
	 *     Bit      | Day of Week
	 *     ---------+-------------
	 *     0        | Reserved ('Holiday', not defined by this standard)
	 *     1        | Sunday
	 *     2        | Monday
	 *     3        | Tuesday
	 *     4        | Wednesday
	 *     5        | Thursday
	 *     6        | Friday
	 *     7        | Saturday
	 *
	 * Thus, a value of six (6) would indicate that the entry would only be
	 * allowed on Sundays and Mondays. A value of zero (0) shall indicate that
	 * this row has been disabled.
	 */
	uint8_t  timeBaseScheduleDay;

	/* The Day(s) Of a Month that the schedule entry shall be allowed. Each bit
	 * represents a specific date of the month. If the bit is set to one (1),
	 * then the scheduled entry shall be allowed during the associated date. If
	 * the bit is set to zero (0), then the scheduled entry shall not be allowed
	 * during the associated date. The bits are defined as:
	 *
	 *     Bit      | Day Number
	 *     ---------+-------------
	 *     0        | Reserved
	 *     1        | Day 1
	 *     2        | Day 2
	 *             ...
	 *     31       | Day 31
	 *
	 * Thus, a value of six (6) would indicate that the entry would only be
	 * allowed on the first and second of the allowed months. A value of zero
	 * (0) shall indicate that this row has been disabled.
	 */
	uint32_t timeBaseScheduleDate;

	/* This object specifies what Plan number shall be associated with this
	 * timeBaseScheduleDayPlan object. The value of this object cannot exceed
	 * the value of the maxDayPlans object. A value of zero (0) shall indicate
	 * that this row has been disabled.
	 */
	uint8_t  timeBaseScheduleDayPlan;
} TimeBaseScheduleEntry;

typedef struct TimeBaseDayPlanEntry
{
	/* This object specifies the day plan number for objects in this row. The
	 * value shall not exceed the value of the maxDayPlans object. Day plan
	 * numbers are used in the TimeBase Event Table to specify day plan numbers
	 * to be implemented on specific days of the year or as part of the week
	 * plans.
	 */
	uint8_t dayPlanNumber;

	/* This object identifies day plan event number(s) to be scheduled on a
	 * specific day plan number. Several different events can be scheduled to
	 * take place during a day, and each of these events is one entry or row
	 * within a specified day plan number. The total number of events for one
	 * day plan shall not exceed the value of the maxDayPlanEvents object. If
	 * multiple non-conflicting events are scheduled to occur at the same time,
	 * they shall be logically executed in order of their dayPlanEventNumber
	 * with the lowest number occurring first. An implementation shall omit
	 * lower number actions that are in conflict with higher number actions at
	 * the same time.
	 */
	uint8_t dayPlanEventNumber;

	/* The Hour of day, as measured by the controllerLocalTime object, that the
	 * associated event shall become active.
	 */
	uint8_t dayPlanHourNumber;

	/* The Minute of the hour (defined in the dayPlanHour), as measured by the
	 * controllerLocalTime object, that the associated event shall become
	 * active.
	 */
	uint8_t dayPlanMinuteNumber;

	/* This object provides a reference to the device-type specific action that
	 * shall be executed. The object shall reference the action by its
	 * associated object identifier, including its instance (i.e., the full OID
	 * of the scalar or columnar object). Only objects whose description field
	 * explicitly states that they may be called by the action table may be
	 * referenced. If a management system attempts to set this value to any
	 * other object identifier, the device shall respond with a genErr. Any
	 * object allowing the action table to reference it shall define precisely
	 * what action takes place when it is activated, and whether the action is
	 * transitionary or continuous until deactivated. The object shall also
	 * define what, if any, restrictions may be placed on other operations the
	 * device may be able to perform. If the action to be performed is defined
	 * by a row of a table, one of the index columns should be identified as the
	 * explicit object that is referenced.
	 */
	const char *const dayPlanActionNumberOID;
} TimeBaseDayPlanEntry;

typedef struct Timebase
{
	/* The value of this object specifies the maximum number of different
	 * entries supported by the device as shown by the number of rows in the
	 * timeBaseScheduleTable.
	 */
	uint16_t maxTimeBaseScheduleEntries;

	/* A table containing the time base schedule parameters for the device. The
	 * number of rows in this table shall be equal to the
	 * maxTimeBaseScheduleEntries object. The table references the appropriate
	 * day plan for the device. The plan is determined by comparing the current
	 * month (MONTH), day of week (DOW) and date of month (DOM) to the
	 * appropriate fields. The settings for MONTH, DOW and DOM are connected
	 * with a logical AND. To determine which timebased event to select,
	 * determine the event which has the most specific date specified. Select
	 * the more specific event based on their MONTH settings; if the same,
	 * select the most specific DOM; if that is still the same, select the most
	 * specific DOW; if still the same, the first occurrence within the time
	 * base event table shall be selected. ’More specific’ means the least
	 * number of bits set within an object. All entries in Time Base Schedule
	 * Table are expressed in local time and date. A row in the table may be
	 * deactivated by setting the Month, Day, Date, or DayPlan parameters to
	 * zero (0)
	 */
	TimeBaseScheduleEntry *timeBaseScheduleTable;

	/* This object specifies what Plan number shall be associated with this
	 * timeBaseScheduleDayPlan object. The value of this object cannot exceed
	 * the value of the maxDayPlans object. A value of zero (0) shall indicate
	 * that this row has been disabled.
	 */
	uint8_t maxDayPlans;

	/* The value of this object specifies the fixed number of different
	 * timebased Day Plan Events within each Day Plan supported by the device.
	 * The value of this object represents the number of rows (secondary key
	 * into the table) available within each of the day plans that are available
	 * in the timeBaseDayPlanTable. All day plans shall have the same number of
	 * day plan events available for use.
	 */
	uint8_t maxDayPlanEvents;

	/* A table containing day plan numbers, the times when to implement them and
	 * the associated actions. The number of rows in this table shall be equal
	 * to the product of the maxDayPlans object and the maxDayPlanEvents object.
	 * The dayPlanNumbers within this table shall begin with day plan number 1
	 * and increment by one to the maxDayPlans. The dayPlanEventNumbers within
	 * this table shall begin with day plan event number 1 and increment by one
	 * to the maxDayPlanEvents. This table is always used in association with
	 * device-type specific objects specifying device-type specific actions such
	 * as activating a message on a VMS sign or initiating a pattern for a
	 * signal controller. A device MIB that defines an action table should
	 * define the relative priority of the action table as compared to the
	 * priority of system and other commands. The device-type specific action is
	 * only initiated when (1) the specific DayPlan has been activated, (2) the
	 * scheduler has sufficient priority to override the current operation of
	 * the device, and (3) at the indicated time. After a power recovery, or
	 * after a change to any object that affects controlerLocalTime, the
	 * operational mode called for by thescheduler shall be per the last event
	 * that would have been called for by the currently defined schedule; the
	 * logic searches for all events that may have occurred for at least the
	 * previous 24 hours.
	 */
	TimeBaseDayPlanEntry *timeBaseDayPlanTable;

	/* This object indicates the current value of the active
	 * dayPlanNumber-object. A value of zero (0) indicates that there is no
	 * dayPlanNumber that is currently active.
	 */
	uint8_t dayPlanStatus;

	/* This object indicates the number of the TimeBaseSchedule which is
	 * currently selected by the scheduling logic; the device may or may not be
	 * using the selected schedule. The value of zero (0) indicates that there
	 * is no timeBaseScheduleNumber that is currently selected.
	 */
	uint16_t timeBaseScheduleTableStatus;
} Timebase;

typedef struct DSTEntry
{
	/* The entry number for the DST objects in this row. This value shall not
	 * exceed the maxDaylightSavingEntries object value.
	 */
	uint8_t dstEntryNumber;

	/* The month during which daylight saving time (DST) begins. An entry of
	 * 'absolute' means that dstBeginSecondsToTransition defines an absolute
	 * time to begin DST relative to midnight January 1, 1970. In this case, any
	 * value indicated in the dstEndMonth, dstBeginOccurences,
	 * dstBeginDayOfWeek, dstBeginDayOfMonth, dstEndOccurances, dstEndDayOfWeek,
	 * and dstEndDayOfMonth objects are irrelevant, and the
	 * dstEndSecondsToTransition object defines an absolute time to end DST
	 * relative to midnight January 1, 1970.
	 *     If the daylightSavingNode is enabled (i.e. globalDaylightSaving =
	 *     enableDaylightSavingNode), and the value of this object is
	 *     disabled (14), then the values in the remaining objects in this row
	 *     of the dstTable are irrelevant and therefore ignored by the device.
	 */
	enum Month dstBeginMonth;

	/* For values of 1-4, the number of occurrences of the specific day of week
	 * that shall occur on or after dstBeginDayOfMonth until the daylight saving
	 * transition shall take place.
	 * For values of 5-8, the number of occurrences of the specific day of week
	 * that shall occur on or before dstBeginDayOfMonth until the daylight
	 * saving transition shall take place.
	 * For value = 9, dstBeginDayOfMonth defines the specific day of the month
	 * that the DST transition occurs regardless of value in dstBeginDayOfWeek
	 * object.
	 * NOTE: To specify the last occurrence of a specified day of the month,
	 * simply specify the last occurrence of the specified day of the week on or
	 * before the last day of the month (e.g., 31).
	 */
	enum Occurrence dstBeginOccurrences;

	/* The Day of the week on which daylight saving time (DST) begins. This
	 * object shall only apply if dstBeginOccurrences = 1-8.
	 */
	enum Day dstBeginDayOfWeek;

	/* If dstBeginOccurrences = 1-8: The day of the month from which to begin
	 * counting occurrences of a specific day of the week (forward for values
	 * 1-4, and backwards for values 5-8). If dstBeginOccurrences = 9: The
	 * specific day of the month on which the transition occurs.
	 */
	uint8_t dstBeginDayOfMonth;

	/* If dstBeginMonth = absolute, then this object defines when DST begins
	 * based on the seconds from midnight January 1, 1970 (UTC/GMT). If
	 * dstBeginMonth = 1-12 (January to December), then this object defines the
	 * time when DST begins in seconds past midnight relative to local time (see
	 * the controllerLocalTime object).
	 * NOTE: a set of parameters that causes a day transition that crosses the
	 * midnight boundary may result in unexpected behavior.
	 */
	uint32_t dstBeginSecondsToTransition;

	/* The month during which daylight saving time (DST) ends. If the value of
	 * dstBeginMonth object = 'absolute' or 'disabled', then the agent shall
	 * ignore the value of this object. Otherwise, the value of this object is
	 * valid.
	 */
	enum Month dstEndMonth;

	/* For values of 1-4, the number of occurrences of the specific day of week
	 * that shall occur on or after dstEndDayOfMonth until the daylight saving
	 * transition shall take place.
	 * For values of 5-8, the number of occurrences of the specific day of week
	 * that shall occur on or before dstEndDayOfMonth until the daylight saving
	 * transition shall take place.
	 * For value = 9, dstEndDayOfMonth defines the specific day of the month
	 * that the DST transition occurs regardless of value in dstEndDayOfWeek
	 * object.
	 * NOTE: To specify the last occurrence of a specified day of the month,
	 * simply specify the last occurrence of the specified day of the week on or
	 * before the last day of the month (e.g. 31).
	 */
	enum Occurrence dstEndOccurrences;

	/* The Day of the week on which daylight saving time (DST) ends. This object
	 * shall only apply if dstEndOccurrences = 1-8.
	 */
	enum Day dstEndDayOfWeek;

	/* If dstEndOccurrences = 1-8: The day of the month from which to begin
	 * counting occurrences of a specific day of the week (forward for values
	 * 1-4, and backwards for values 5-8). If dstEndOccurrences = 9: The
	 * specific day of the month on which the transition occurs.
	 */
	uint8_t dstEndDayOfMonth;

	/* If dstBeginMonth = absolute, then this object defines when DST ends based
	 * on the seconds from midnight January 1, 1970 (UTC/GMT). If
	 * dstBeginMonth = 1-12 (January to December), then this object defines the
	 * time when DST ends in seconds past midnight relative to local time (see
	 * the controllerLocalTime object).
	 * NOTE: a set of parameters that causes a day transition that crosses the
	 * midnight boundary may result in unexpected behavior.
	 */
	uint32_t dstEndSecondsToTransition;

	/* This is the absolute offset in seconds that will be added to the local
	 * time reference point to determine the local time when DST is in effect as
	 * specified by this row entry. Values of this object in adjacent rows, even
	 * if they overlap, are not cumulative. That is, the row with the latest
	 * dstBegin time, which has not terminated due to passing the dstEnd time,
	 * shall determine the setting of the local TOD clock; the
	 * dstSecondsToAdjust for the latest dstBegin governs the Local TOD clock
	 * settings. The maximum offset to adjust is 21600 seconds, an equivalent of
	 * 6 hours.
	 */
	uint16_t dstSecondsToAdjust;
} DSTEntry;

typedef struct DaylightSavingNode
{
	/* The maximum number of entries (begin and end date pairs) that the DST
	 * Table can contain within the device. As of July 2007, devices used within
	 * the United States only require 1 entry when using the generic begin and
	 * end date method.
	 * 
	 * NOTE: It is expected that, for devices using the absolute date method,
	 * the device would need to support at least 1 entry per year programmed.
	 *
	 * For multi-step DST transitions, a minimum of 2 rows are required
	 * (see Annex A.2.1 Figure 6).
	 * More than one row may be required if absolute date method (see Section
	 * 2.4.8.2.2) is used for more than one year, or if more than one time
	 * change is implemented in a given year.
	 */
	uint8_t maxDaylightSavingEntries;

	/* A table containing DST Begin and End dates. The table is useful for
	 * agencies with multiple daylight saving time incremental steps per year.
	 * The number of rows in this table is equal to the maxDaylightSavingEntries
	 * object.
	 */
	DSTEntry *dstTable;
} DaylightSavingNode;

/* This node is an identifier used to organize all objects for support of
 * time-related functions that are common to most device types.
 */
typedef struct GlobalTimeManagement
{
	/* The number of seconds since the epoch of 00:00:00 (midnight)
	 * January 1, 1970 UTC (a.k.a. Zulu or GMT).
	 */
	size_t globalTime;

	/* This object specifies whether the daylight saving time (DST) is enabled,
	 * disabled or some other form of DST is active.
	 * other               - DST adjustments by a mechanism not defined within
	 *                       this standard.
	 * disableDST          - DST clock adjustments shall NOT occur.
	 * enableUSDST         - DST shall begin the first Sunday in April and shall
	 *                       end the last Sunday of October. All changes of time
	 *                       occur at 2:00 AM. (This is the pre-2007 DST
	 *                       settings for the USA.)
	 * enableEuropeDST     - DST shall start the last Sunday of March at 2:00 AM
	 *                       and ends the last Sunday of October at 3:00 AM.
	 * enableAustraliaDST  - DST shall start the last Sunday in October at 2:00
	 *                       AM and ends the last Sunday in March at 2:00 AM.
	 * enableTasmaniaDST   - DST shall start the first Sunday in October at 2:00
	 *                       A.M. and ends the last Sunday in March at 3:00 A.M.
	 * enableEgyptDST      - DST shall start the last Friday in April and end
	 *                       the last Thursday in September.
	 * enableNamibiaDST    - DST shall start the first Sunday in September and
	 *                       end the first Sunday in April.
	 * enableIraqDST       - DST shall start on April 1 and end on October 1.
	 * enableMongoliaDST   - DST shall start the last Sunday in March and end
	 *                       the last Sunday in September.
	 * enableIranDST       - DST shall start the first day of Farvardin and end
	 *                       the first day of Mehr.
	 * enableFijiDST       - DST shall start the first Sunday in November and
	 *                       end the last Sunday in February.
	 * enableNewZealandDST - DST shall start the first Sunday in October and end
	 *                       the first Sunday on or after March 5th.
	 * enableTongaDST      - DST shall start the first Saturday in October and
	 *                       end the first Saturday on or after April 15th.
	 * enableCubaDST       - DST shall start April 1st and end last Sunday in
	 *                       October.
	 * enableBrazilDST     - DST shall start the first Sunday in October and end
	 *                       the last Sunday in February.
	 * enableChileDST      - DST shall start the first Sunday on or after
	 *                       October 9th and end the first Sunday on or after
	 *                       March 9th.
	 * enableFalklandsDST  - DST shall start the first Sunday on or after
	 *                       September 8th and end the first Sunday on or after
	 *                       April 8th.
	 * enableParaguayDST   - DST shall start the first Sunday in October and end
	 *                       the last Saturday in February.
	 * enableDaylightSavingNode - DST operation is controlled by objects located
	 *                            under the daylightSavingNode.
	 * NOTE: This object is maintained for backward compatibility and it is
	 *       envisioned that only the following values are supported with all
	 *       other values being ‘retired’:
	 *           - DST_other (1),
	 *           - DST_disableDST (2),
	 *           - DST_enableDaylightSavingNode (20)
	 * NOTE: Users should ensure that the values of globalDaylightSaving and the
	 *       entries in the new DST Table are coordinated. The
	 *       globalDaylightSaving object is intended to be used to enable and
	 *       disable DST and should not be set to the value ‘20’,
	 *       enableDaylightSavingNode until after the dstTable entries have been
	 *       fully configured. Further, the globalDaylightSaving object
	 *       supersedes the settings in the DST Table.
	 */
	enum
	{
		otherDST                 = 1,
		disableDST               = 2,
		enableUSDST              = 3,
		enableEuropeDST          = 4,
		enableAustraliaDST       = 5,
		enableTasmaniaDST        = 6,
		enableEgyptDST           = 7,
		enableNamibiaDST         = 8,
		enableIraqDST            = 9,
		enableMangoliaDST        = 10,
		enableIranDST            = 11,
		enableFijiDST            = 12,
		enableNewZealandDST      = 13,
		enableTongaDST           = 14,
		enableCubaDST            = 15,
		enableBrazilDST          = 16,
		enableChileDST           = 17,
		enableFalklandsDST       = 18,
		enableParaguayDST        = 19,
		enableDaylightSavingNode = 20,
	} globalDaylightSaving;

	/* This node is an identifier used to organize the main objects for event
	 * scheduling. Device type-specific objects (tables) pointed to are defined
	 * within the appropriate MIB.
	 */
	Timebase timebase;

	/* This object has been deprecated.
	 * Indicates the number of seconds offset between local time and GMT.
	 * Positive values indicate local times in the Eastern Hemisphere up to the
	 * International Date Line and negative values indicate local times in the
	 * Western Hemisphere back to the International Date Line. If one of the
	 * daylight saving times is activated, this value will change automatically
	 * at the referenced time. For example, Central Standard Time (CST) is
	 * -21600 and Central Daylight Time (CDT) is -18000.
	 */
	int32_t globalLocationTimeDifferential;

	/* Indicates the number of seconds offset between local Standard Time and
	 * GMT. Positive values indicate local times in the Eastern Hemisphere up to
	 * the International Date Line and negative values indicate local times in
	 * the Western Hemisphere back to the International Date Line. This value
	 * does not change in response to a DST event.
	 */
	int32_t controllerStandardTimeZone;

	/* The current local time expressed in seconds since 00:00:00 (midnight)
	 * January 1, 1970 of the same time offset. This value changes by 3600
	 * seconds in response to a DST event.
	 */
	size_t controllerLocalTime;

	DaylightSavingNode daylightSavingNode;
} GlobalTimeManagement;

typedef struct AuxIOv2Entry
{
	/* Indicates the type of auxiliary I/O, which can be analog or digital.
	 * NOTE: From NTCIP 1201 v01 to v02 of these objects, it was determined that
	 * ports are either digital, analog, or other.
	 */
	enum
	{
		PORT_TYPE_OTHER   = 1,
		PORT_TYPE_ANALOG  = 2,
		PORT_TYPE_DIGITAL = 3
	} auxIOv2PortType;

	/* Indicates the port number for the associated port type. Port numbers are
	 * used sequentially from one to max for each port type. There can be a port
	 * 1 for analog port and port 1 for digital port.
	 */
	uint8_t auxIOv2PortNumber;

	/* Informational text field describing the device at the associated
	 * auxiliary I/O.
	 * NOTE: In NTCIP 1203 v01, the SYNTAX SIZE was listed as (0 .. 50).
	 * In NTCIP 1201 v02 and NTCIP 1201 v03, this was changed to (0 .. 255).
	 */
	char *auxIOv2PortDescription;

	/* Defines number of bits used for the IO-port (e.g. width of digital,
	 * resolution of analog). Thus, this feature allows the digital monitoring
	 * (via NTCIP) of an analog port on the agent.
	 * NOTE: In NTCIP 1203 v01, ACCESS was listed as read-write; however, in
	 * NTCIP 1201 v03, ACCESS changed to read-only . This changed because
	 * resolution is fixed by the hardware implementation and cannot be changed
	 * by the management station. The SYNTAX also changed from NTCIP 1201 v02 to
	 * NTCIP 1201 v03; it is now as it was originally under the experimental
	 * node defined in NTCIP 1203v01. This changed to address backward
	 * compatibility and the ‘aliasing’ between the version 1 objects (see
	 * Section 2.10) and the Version 02 objects.
	 */
	uint8_t auxIOv2PortResolution;

	/* For input or bidirectional ports, this contains the current value of the
	 * input. For output ports, this is the last commanded value of the port. A
	 * genError shall be generated, if this object is set and the port is an
	 * input. The actual value exchanged shall not exceed
	 * [2^(auxIOv2PortResolution) – 1];
	 * any SET operation to a value in excess of this number shall result in a
	 * genErr, and any GET response in excess of this value shall be considered
	 * erroneous.
	 */
	uint32_t auxIOv2PortValue;

	/* Indicates whether state of this port can be set (output), read (input) or
	 * both (bidirectional).
	 */
	enum
	{
		PORT_DIRECTION_OUTPUT        = 1,
		PORT_DIRECTION_INPUT         = 2,
		PORT_DIRECTION_BIDIRECTIONAL = 3
	} auxIOv2PortDirection;

	/* For bi-directional ports, this object indicates the last state to which
	 * the auxIOv2PortValue object was set. For output ports, this value shall
	 * always be equal to the auxIOv2PortValue object. For input ports, this
	 * value shall always be zero (0).
	 */
	uint32_t auxIOv2PortLastCommandedState;
} AuxIOv2Entry;

/* This node is an identifier used to group all objects supporting auxiliary
 * I/O functions
 *
 * NOTE: The auxiliary I/O management objects listed in NTCIP 1201 v03 define a
 * mechanism for the support of unspecified I/O for an NTCIP device. The agency
 * or device specifications define the intended operation of these ports.
 *
 * NOTE: NTCIP 1201 v01 defined functionality of these objects under the
 * experimental node. For the purposes of backward compatibility, the names of
 * these objects, originally defined in NTCIP 1201 v02, have been modified to
 * eliminate any conflicts/confusion with the objects defined under the
 * experimental node. For those agents that may support these objects and those
 * originally defined under the experimental node (see Section 2.10), the object
 * definitions aretreated as aliases such that a write to an object in one group
 * acts as write to the corresponding object in the other group. As aliases, a
 * read of an object in this group is equivalent to a read of the corresponding
 * object in the auxIO group.
 *
 * NOTE: Early NTCIP deployments included the Aux I/O objects defined in NTCIP
 * 1203v01 located under an experimental node. These objects were moved to a
 * permanent node with the release of NTCIP 1201 v02 and given new names. This
 * can create confusion and backward compatibility issues. As noted in the
 * object definition, both sets of objects refer to the same functions within
 * the device; hence, both sets of objects cause the same device action or
 * provide the same device status. Agency specifications that do NOT require
 * support for the Aux I/O objects under the experimental node should explicitly
 * exclude the support for these experimental objects (which have been
 * deprecated) for backward compatibility. Support of the Aux I/O objects under
 * the permanent node identified in NTCIP 1201 v03 may be optional or mandatory
 * depending on agency or device specifications.
 * Use the PRL to exclude support of NTCIP 1201 v01-defined aux I/O objects.
 * The relationship between mandatory and optional support of NTCIP v01
 * (experimental) and NTCIP v02 objects is unique to the Aux I/O objects.
 */
typedef struct AuxIOv2
{
	/* The number of rows contained in the 'auxIOv2Table' with the
	 * auxIOv2PortType set to 'digital'.
	 */
	uint8_t maxAuxIOv2TableNumDigitalPorts;

	/* The number of rows contained in the 'auxIOv2Table’ with the
	 * auxIOv2PortType set to 'analog’.
	 */
	uint8_t maxAuxIOv2TableNumAnalogPorts;

	/* A table providing the means to access any non-mission-critical or
	 * non-safety-related auxiliary I/O of the controller, including reading
	 * inputs and setting outputs. The number of rows in this table equals the
	 * sum of the values of the ‘maxAuxIOv2TableNumDigitalPorts’ and
	 * ‘maxAuxIOv2TableNumAnalogPorts’ objects. This table shall not be used to
	 * control or monitor any safety related equipment. The electrical levels
	 * used by the ports are not standardized by auxIOv2Table objects; such
	 * information should be contained in the hardware manual.
	 */
	AuxIOv2Entry *auxIOv2Table;
} AuxIOv2;

typedef struct Global
{
	GlobalConfiguration      globalConfiguration;  /* Node one */
	GlobalDatabaseManagement globalDBManagement;   /* Node two */
	GlobalTimeManagement     globalTimeManagement; /* Node three */
	/* Node four is defined in NTCIP 1103 */
	/* Node five is defined in NTCIP 1103 */
	/* Node six is not used. */
	AuxIOv2                  auxIOv2;              /* Node seven */
} Global;

#endif /* COMMON_OBJECTS_H */
