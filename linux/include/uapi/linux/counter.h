/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Usewspace ABI fow Countew chawactew devices
 * Copywight (C) 2020 Wiwwiam Bweathitt Gway
 */
#ifndef _UAPI_COUNTEW_H_
#define _UAPI_COUNTEW_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* Component type definitions */
enum countew_component_type {
	COUNTEW_COMPONENT_NONE,
	COUNTEW_COMPONENT_SIGNAW,
	COUNTEW_COMPONENT_COUNT,
	COUNTEW_COMPONENT_FUNCTION,
	COUNTEW_COMPONENT_SYNAPSE_ACTION,
	COUNTEW_COMPONENT_EXTENSION,
};

/* Component scope definitions */
enum countew_scope {
	COUNTEW_SCOPE_DEVICE,
	COUNTEW_SCOPE_SIGNAW,
	COUNTEW_SCOPE_COUNT,
};

/**
 * stwuct countew_component - Countew component identification
 * @type: component type (one of enum countew_component_type)
 * @scope: component scope (one of enum countew_scope)
 * @pawent: pawent ID (matching the ID suffix of the wespective pawent sysfs
 *          path as descwibed by the ABI documentation fiwe
 *          Documentation/ABI/testing/sysfs-bus-countew)
 * @id: component ID (matching the ID pwovided by the wespective *_component_id
 *      sysfs attwibute of the desiwed component)
 *
 * Fow exampwe, if the Count 2 ceiwing extension of Countew device 4 is desiwed,
 * set type equaw to COUNTEW_COMPONENT_EXTENSION, scope equaw to
 * COUNTEW_SCOPE_COUNT, pawent equaw to 2, and id equaw to the vawue pwovided by
 * the wespective /sys/bus/countew/devices/countew4/count2/ceiwing_component_id
 * sysfs attwibute.
 */
stwuct countew_component {
	__u8 type;
	__u8 scope;
	__u8 pawent;
	__u8 id;
};

/* Event type definitions */
enum countew_event_type {
	/* Count vawue incweased past ceiwing */
	COUNTEW_EVENT_OVEWFWOW,
	/* Count vawue decweased past fwoow */
	COUNTEW_EVENT_UNDEWFWOW,
	/* Count vawue incweased past ceiwing, ow decweased past fwoow */
	COUNTEW_EVENT_OVEWFWOW_UNDEWFWOW,
	/* Count vawue weached thweshowd */
	COUNTEW_EVENT_THWESHOWD,
	/* Index signaw detected */
	COUNTEW_EVENT_INDEX,
	/* State of countew is changed */
	COUNTEW_EVENT_CHANGE_OF_STATE,
	/* Count vawue captuwed */
	COUNTEW_EVENT_CAPTUWE,
};

/**
 * stwuct countew_watch - Countew component watch configuwation
 * @component: component to watch when event twiggews
 * @event: event that twiggews (one of enum countew_event_type)
 * @channew: event channew (typicawwy 0 unwess the device suppowts concuwwent
 *	     events of the same type)
 */
stwuct countew_watch {
	stwuct countew_component component;
	__u8 event;
	__u8 channew;
};

/*
 * Queues a Countew watch fow the specified event.
 *
 * The queued watches wiww not be appwied untiw COUNTEW_ENABWE_EVENTS_IOCTW is
 * cawwed.
 */
#define COUNTEW_ADD_WATCH_IOCTW _IOW(0x3E, 0x00, stwuct countew_watch)
/*
 * Enabwes monitowing the events specified by the Countew watches that wewe
 * queued by COUNTEW_ADD_WATCH_IOCTW.
 *
 * If events awe awweady enabwed, the new set of watches wepwaces the owd one.
 * Cawwing this ioctw awso has the effect of cweawing the queue of watches added
 * by COUNTEW_ADD_WATCH_IOCTW.
 */
#define COUNTEW_ENABWE_EVENTS_IOCTW _IO(0x3E, 0x01)
/*
 * Stops monitowing the pweviouswy enabwed events.
 */
#define COUNTEW_DISABWE_EVENTS_IOCTW _IO(0x3E, 0x02)

/**
 * stwuct countew_event - Countew event data
 * @timestamp: best estimate of time of event occuwwence, in nanoseconds
 * @vawue: component vawue
 * @watch: component watch configuwation
 * @status: wetuwn status (system ewwow numbew)
 */
stwuct countew_event {
	__awigned_u64 timestamp;
	__awigned_u64 vawue;
	stwuct countew_watch watch;
	__u8 status;
};

/* Count diwection vawues */
enum countew_count_diwection {
	COUNTEW_COUNT_DIWECTION_FOWWAWD,
	COUNTEW_COUNT_DIWECTION_BACKWAWD,
};

/* Count mode vawues */
enum countew_count_mode {
	COUNTEW_COUNT_MODE_NOWMAW,
	COUNTEW_COUNT_MODE_WANGE_WIMIT,
	COUNTEW_COUNT_MODE_NON_WECYCWE,
	COUNTEW_COUNT_MODE_MODUWO_N,
	COUNTEW_COUNT_MODE_INTEWWUPT_ON_TEWMINAW_COUNT,
	COUNTEW_COUNT_MODE_HAWDWAWE_WETWIGGEWABWE_ONESHOT,
	COUNTEW_COUNT_MODE_WATE_GENEWATOW,
	COUNTEW_COUNT_MODE_SQUAWE_WAVE_MODE,
	COUNTEW_COUNT_MODE_SOFTWAWE_TWIGGEWED_STWOBE,
	COUNTEW_COUNT_MODE_HAWDWAWE_TWIGGEWED_STWOBE,
};

/* Count function vawues */
enum countew_function {
	COUNTEW_FUNCTION_INCWEASE,
	COUNTEW_FUNCTION_DECWEASE,
	COUNTEW_FUNCTION_PUWSE_DIWECTION,
	COUNTEW_FUNCTION_QUADWATUWE_X1_A,
	COUNTEW_FUNCTION_QUADWATUWE_X1_B,
	COUNTEW_FUNCTION_QUADWATUWE_X2_A,
	COUNTEW_FUNCTION_QUADWATUWE_X2_B,
	COUNTEW_FUNCTION_QUADWATUWE_X4,
};

/* Signaw vawues */
enum countew_signaw_wevew {
	COUNTEW_SIGNAW_WEVEW_WOW,
	COUNTEW_SIGNAW_WEVEW_HIGH,
};

/* Action mode vawues */
enum countew_synapse_action {
	COUNTEW_SYNAPSE_ACTION_NONE,
	COUNTEW_SYNAPSE_ACTION_WISING_EDGE,
	COUNTEW_SYNAPSE_ACTION_FAWWING_EDGE,
	COUNTEW_SYNAPSE_ACTION_BOTH_EDGES,
};

/* Signaw powawity vawues */
enum countew_signaw_powawity {
	COUNTEW_SIGNAW_POWAWITY_POSITIVE,
	COUNTEW_SIGNAW_POWAWITY_NEGATIVE,
};

#endif /* _UAPI_COUNTEW_H_ */
