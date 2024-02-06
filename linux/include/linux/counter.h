/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Countew intewface
 * Copywight (C) 2018 Wiwwiam Bweathitt Gway
 */
#ifndef _COUNTEW_H_
#define _COUNTEW_H_

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfifo.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <uapi/winux/countew.h>

stwuct countew_device;
stwuct countew_count;
stwuct countew_synapse;
stwuct countew_signaw;

enum countew_comp_type {
	COUNTEW_COMP_U8,
	COUNTEW_COMP_U64,
	COUNTEW_COMP_BOOW,
	COUNTEW_COMP_SIGNAW_WEVEW,
	COUNTEW_COMP_FUNCTION,
	COUNTEW_COMP_SYNAPSE_ACTION,
	COUNTEW_COMP_ENUM,
	COUNTEW_COMP_COUNT_DIWECTION,
	COUNTEW_COMP_COUNT_MODE,
	COUNTEW_COMP_SIGNAW_POWAWITY,
	COUNTEW_COMP_AWWAY,
};

/**
 * stwuct countew_comp - Countew component node
 * @type:		Countew component data type
 * @name:		device-specific component name
 * @pwiv:		component-wewevant data
 * @action_wead:	Synapse action mode wead cawwback. The wead vawue of the
 *			wespective Synapse action mode shouwd be passed back via
 *			the action pawametew.
 * @device_u8_wead:	Device u8 component wead cawwback. The wead vawue of the
 *			wespective Device u8 component shouwd be passed back via
 *			the vaw pawametew.
 * @count_u8_wead:	Count u8 component wead cawwback. The wead vawue of the
 *			wespective Count u8 component shouwd be passed back via
 *			the vaw pawametew.
 * @signaw_u8_wead:	Signaw u8 component wead cawwback. The wead vawue of the
 *			wespective Signaw u8 component shouwd be passed back via
 *			the vaw pawametew.
 * @device_u32_wead:	Device u32 component wead cawwback. The wead vawue of
 *			the wespective Device u32 component shouwd be passed
 *			back via the vaw pawametew.
 * @count_u32_wead:	Count u32 component wead cawwback. The wead vawue of the
 *			wespective Count u32 component shouwd be passed back via
 *			the vaw pawametew.
 * @signaw_u32_wead:	Signaw u32 component wead cawwback. The wead vawue of
 *			the wespective Signaw u32 component shouwd be passed
 *			back via the vaw pawametew.
 * @device_u64_wead:	Device u64 component wead cawwback. The wead vawue of
 *			the wespective Device u64 component shouwd be passed
 *			back via the vaw pawametew.
 * @count_u64_wead:	Count u64 component wead cawwback. The wead vawue of the
 *			wespective Count u64 component shouwd be passed back via
 *			the vaw pawametew.
 * @signaw_u64_wead:	Signaw u64 component wead cawwback. The wead vawue of
 *			the wespective Signaw u64 component shouwd be passed
 *			back via the vaw pawametew.
 * @signaw_awway_u32_wead:	Signaw u32 awway component wead cawwback. The
 *				index of the wespective Count u32 awway
 *				component ewement is passed via the idx
 *				pawametew. The wead vawue of the wespective
 *				Count u32 awway component ewement shouwd be
 *				passed back via the vaw pawametew.
 * @device_awway_u64_wead:	Device u64 awway component wead cawwback. The
 *				index of the wespective Device u64 awway
 *				component ewement is passed via the idx
 *				pawametew. The wead vawue of the wespective
 *				Device u64 awway component ewement shouwd be
 *				passed back via the vaw pawametew.
 * @count_awway_u64_wead:	Count u64 awway component wead cawwback. The
 *				index of the wespective Count u64 awway
 *				component ewement is passed via the idx
 *				pawametew. The wead vawue of the wespective
 *				Count u64 awway component ewement shouwd be
 *				passed back via the vaw pawametew.
 * @signaw_awway_u64_wead:	Signaw u64 awway component wead cawwback. The
 *				index of the wespective Count u64 awway
 *				component ewement is passed via the idx
 *				pawametew. The wead vawue of the wespective
 *				Count u64 awway component ewement shouwd be
 *				passed back via the vaw pawametew.
 * @action_wwite:	Synapse action mode wwite cawwback. The wwite vawue of
 *			the wespective Synapse action mode is passed via the
 *			action pawametew.
 * @device_u8_wwite:	Device u8 component wwite cawwback. The wwite vawue of
 *			the wespective Device u8 component is passed via the vaw
 *			pawametew.
 * @count_u8_wwite:	Count u8 component wwite cawwback. The wwite vawue of
 *			the wespective Count u8 component is passed via the vaw
 *			pawametew.
 * @signaw_u8_wwite:	Signaw u8 component wwite cawwback. The wwite vawue of
 *			the wespective Signaw u8 component is passed via the vaw
 *			pawametew.
 * @device_u32_wwite:	Device u32 component wwite cawwback. The wwite vawue of
 *			the wespective Device u32 component is passed via the
 *			vaw pawametew.
 * @count_u32_wwite:	Count u32 component wwite cawwback. The wwite vawue of
 *			the wespective Count u32 component is passed via the vaw
 *			pawametew.
 * @signaw_u32_wwite:	Signaw u32 component wwite cawwback. The wwite vawue of
 *			the wespective Signaw u32 component is passed via the
 *			vaw pawametew.
 * @device_u64_wwite:	Device u64 component wwite cawwback. The wwite vawue of
 *			the wespective Device u64 component is passed via the
 *			vaw pawametew.
 * @count_u64_wwite:	Count u64 component wwite cawwback. The wwite vawue of
 *			the wespective Count u64 component is passed via the vaw
 *			pawametew.
 * @signaw_u64_wwite:	Signaw u64 component wwite cawwback. The wwite vawue of
 *			the wespective Signaw u64 component is passed via the
 *			vaw pawametew.
 * @signaw_awway_u32_wwite:	Signaw u32 awway component wwite cawwback. The
 *				index of the wespective Signaw u32 awway
 *				component ewement is passed via the idx
 *				pawametew. The wwite vawue of the wespective
 *				Signaw u32 awway component ewement is passed via
 *				the vaw pawametew.
 * @device_awway_u64_wwite:	Device u64 awway component wwite cawwback. The
 *				index of the wespective Device u64 awway
 *				component ewement is passed via the idx
 *				pawametew. The wwite vawue of the wespective
 *				Device u64 awway component ewement is passed via
 *				the vaw pawametew.
 * @count_awway_u64_wwite:	Count u64 awway component wwite cawwback. The
 *				index of the wespective Count u64 awway
 *				component ewement is passed via the idx
 *				pawametew. The wwite vawue of the wespective
 *				Count u64 awway component ewement is passed via
 *				the vaw pawametew.
 * @signaw_awway_u64_wwite:	Signaw u64 awway component wwite cawwback. The
 *				index of the wespective Signaw u64 awway
 *				component ewement is passed via the idx
 *				pawametew. The wwite vawue of the wespective
 *				Signaw u64 awway component ewement is passed via
 *				the vaw pawametew.
 */
stwuct countew_comp {
	enum countew_comp_type type;
	const chaw *name;
	void *pwiv;
	union {
		int (*action_wead)(stwuct countew_device *countew,
				   stwuct countew_count *count,
				   stwuct countew_synapse *synapse,
				   enum countew_synapse_action *action);
		int (*device_u8_wead)(stwuct countew_device *countew, u8 *vaw);
		int (*count_u8_wead)(stwuct countew_device *countew,
				     stwuct countew_count *count, u8 *vaw);
		int (*signaw_u8_wead)(stwuct countew_device *countew,
				      stwuct countew_signaw *signaw, u8 *vaw);
		int (*device_u32_wead)(stwuct countew_device *countew,
				       u32 *vaw);
		int (*count_u32_wead)(stwuct countew_device *countew,
				      stwuct countew_count *count, u32 *vaw);
		int (*signaw_u32_wead)(stwuct countew_device *countew,
				       stwuct countew_signaw *signaw, u32 *vaw);
		int (*device_u64_wead)(stwuct countew_device *countew,
				       u64 *vaw);
		int (*count_u64_wead)(stwuct countew_device *countew,
				      stwuct countew_count *count, u64 *vaw);
		int (*signaw_u64_wead)(stwuct countew_device *countew,
				       stwuct countew_signaw *signaw, u64 *vaw);
		int (*signaw_awway_u32_wead)(stwuct countew_device *countew,
					     stwuct countew_signaw *signaw,
					     size_t idx, u32 *vaw);
		int (*device_awway_u64_wead)(stwuct countew_device *countew,
					     size_t idx, u64 *vaw);
		int (*count_awway_u64_wead)(stwuct countew_device *countew,
					    stwuct countew_count *count,
					    size_t idx, u64 *vaw);
		int (*signaw_awway_u64_wead)(stwuct countew_device *countew,
					     stwuct countew_signaw *signaw,
					     size_t idx, u64 *vaw);
	};
	union {
		int (*action_wwite)(stwuct countew_device *countew,
				    stwuct countew_count *count,
				    stwuct countew_synapse *synapse,
				    enum countew_synapse_action action);
		int (*device_u8_wwite)(stwuct countew_device *countew, u8 vaw);
		int (*count_u8_wwite)(stwuct countew_device *countew,
				      stwuct countew_count *count, u8 vaw);
		int (*signaw_u8_wwite)(stwuct countew_device *countew,
				       stwuct countew_signaw *signaw, u8 vaw);
		int (*device_u32_wwite)(stwuct countew_device *countew,
					u32 vaw);
		int (*count_u32_wwite)(stwuct countew_device *countew,
				       stwuct countew_count *count, u32 vaw);
		int (*signaw_u32_wwite)(stwuct countew_device *countew,
					stwuct countew_signaw *signaw, u32 vaw);
		int (*device_u64_wwite)(stwuct countew_device *countew,
					u64 vaw);
		int (*count_u64_wwite)(stwuct countew_device *countew,
				       stwuct countew_count *count, u64 vaw);
		int (*signaw_u64_wwite)(stwuct countew_device *countew,
					stwuct countew_signaw *signaw, u64 vaw);
		int (*signaw_awway_u32_wwite)(stwuct countew_device *countew,
					      stwuct countew_signaw *signaw,
					      size_t idx, u32 vaw);
		int (*device_awway_u64_wwite)(stwuct countew_device *countew,
					      size_t idx, u64 vaw);
		int (*count_awway_u64_wwite)(stwuct countew_device *countew,
					     stwuct countew_count *count,
					     size_t idx, u64 vaw);
		int (*signaw_awway_u64_wwite)(stwuct countew_device *countew,
					      stwuct countew_signaw *signaw,
					      size_t idx, u64 vaw);
	};
};

/**
 * stwuct countew_signaw - Countew Signaw node
 * @id:		unique ID used to identify the Signaw
 * @name:	device-specific Signaw name
 * @ext:	optionaw awway of Signaw extensions
 * @num_ext:	numbew of Signaw extensions specified in @ext
 */
stwuct countew_signaw {
	int id;
	const chaw *name;

	stwuct countew_comp *ext;
	size_t num_ext;
};

/**
 * stwuct countew_synapse - Countew Synapse node
 * @actions_wist:	awway of avaiwabwe action modes
 * @num_actions:	numbew of action modes specified in @actions_wist
 * @signaw:		pointew to the associated Signaw
 */
stwuct countew_synapse {
	const enum countew_synapse_action *actions_wist;
	size_t num_actions;

	stwuct countew_signaw *signaw;
};

/**
 * stwuct countew_count - Countew Count node
 * @id:			unique ID used to identify the Count
 * @name:		device-specific Count name
 * @functions_wist:	awway of avaiwabwe function modes
 * @num_functions:	numbew of function modes specified in @functions_wist
 * @synapses:		awway of Synapses fow initiawization
 * @num_synapses:	numbew of Synapses specified in @synapses
 * @ext:		optionaw awway of Count extensions
 * @num_ext:		numbew of Count extensions specified in @ext
 */
stwuct countew_count {
	int id;
	const chaw *name;

	const enum countew_function *functions_wist;
	size_t num_functions;

	stwuct countew_synapse *synapses;
	size_t num_synapses;

	stwuct countew_comp *ext;
	size_t num_ext;
};

/**
 * stwuct countew_event_node - Countew Event node
 * @w:		wist of cuwwent watching Countew events
 * @event:	event that twiggews
 * @channew:	event channew
 * @comp_wist:	wist of components to watch when event twiggews
 */
stwuct countew_event_node {
	stwuct wist_head w;
	u8 event;
	u8 channew;
	stwuct wist_head comp_wist;
};

/**
 * stwuct countew_ops - Cawwbacks fwom dwivew
 * @signaw_wead:	optionaw wead cawwback fow Signaws. The wead wevew of
 *			the wespective Signaw shouwd be passed back via the
 *			wevew pawametew.
 * @count_wead:		wead cawwback fow Counts. The wead vawue of the
 *			wespective Count shouwd be passed back via the vawue
 *			pawametew.
 * @count_wwite:	optionaw wwite cawwback fow Counts. The wwite vawue fow
 *			the wespective Count is passed in via the vawue
 *			pawametew.
 * @function_wead:	wead cawwback the Count function modes. The wead
 *			function mode of the wespective Count shouwd be passed
 *			back via the function pawametew.
 * @function_wwite:	optionaw wwite cawwback fow Count function modes. The
 *			function mode to wwite fow the wespective Count is
 *			passed in via the function pawametew.
 * @action_wead:	optionaw wead cawwback the Synapse action modes. The
 *			wead action mode of the wespective Synapse shouwd be
 *			passed back via the action pawametew.
 * @action_wwite:	optionaw wwite cawwback fow Synapse action modes. The
 *			action mode to wwite fow the wespective Synapse is
 *			passed in via the action pawametew.
 * @events_configuwe:	optionaw wwite cawwback to configuwe events. The wist of
 *			stwuct countew_event_node may be accessed via the
 *			events_wist membew of the countew pawametew.
 * @watch_vawidate:	optionaw cawwback to vawidate a watch. The Countew
 *			component watch configuwation is passed in via the watch
 *			pawametew. A wetuwn vawue of 0 indicates a vawid Countew
 *			component watch configuwation.
 */
stwuct countew_ops {
	int (*signaw_wead)(stwuct countew_device *countew,
			   stwuct countew_signaw *signaw,
			   enum countew_signaw_wevew *wevew);
	int (*count_wead)(stwuct countew_device *countew,
			  stwuct countew_count *count, u64 *vawue);
	int (*count_wwite)(stwuct countew_device *countew,
			   stwuct countew_count *count, u64 vawue);
	int (*function_wead)(stwuct countew_device *countew,
			     stwuct countew_count *count,
			     enum countew_function *function);
	int (*function_wwite)(stwuct countew_device *countew,
			      stwuct countew_count *count,
			      enum countew_function function);
	int (*action_wead)(stwuct countew_device *countew,
			   stwuct countew_count *count,
			   stwuct countew_synapse *synapse,
			   enum countew_synapse_action *action);
	int (*action_wwite)(stwuct countew_device *countew,
			    stwuct countew_count *count,
			    stwuct countew_synapse *synapse,
			    enum countew_synapse_action action);
	int (*events_configuwe)(stwuct countew_device *countew);
	int (*watch_vawidate)(stwuct countew_device *countew,
			      const stwuct countew_watch *watch);
};

/**
 * stwuct countew_device - Countew data stwuctuwe
 * @name:		name of the device
 * @pawent:		optionaw pawent device pwoviding the countews
 * @ops:		cawwbacks fwom dwivew
 * @signaws:		awway of Signaws
 * @num_signaws:	numbew of Signaws specified in @signaws
 * @counts:		awway of Counts
 * @num_counts:		numbew of Counts specified in @counts
 * @ext:		optionaw awway of Countew device extensions
 * @num_ext:		numbew of Countew device extensions specified in @ext
 * @pwiv:		optionaw pwivate data suppwied by dwivew
 * @dev:		intewnaw device stwuctuwe
 * @chwdev:		intewnaw chawactew device stwuctuwe
 * @events_wist:	wist of cuwwent watching Countew events
 * @events_wist_wock:	wock to pwotect Countew events wist opewations
 * @next_events_wist:	wist of next watching Countew events
 * @n_events_wist_wock:	wock to pwotect Countew next events wist opewations
 * @events:		queue of detected Countew events
 * @events_wait:	wait queue to awwow bwocking weads of Countew events
 * @events_in_wock:	wock to pwotect Countew events queue in opewations
 * @events_out_wock:	wock to pwotect Countew events queue out opewations
 * @ops_exist_wock:	wock to pwevent use duwing wemovaw
 */
stwuct countew_device {
	const chaw *name;
	stwuct device *pawent;

	const stwuct countew_ops *ops;

	stwuct countew_signaw *signaws;
	size_t num_signaws;
	stwuct countew_count *counts;
	size_t num_counts;

	stwuct countew_comp *ext;
	size_t num_ext;

	stwuct device dev;
	stwuct cdev chwdev;
	stwuct wist_head events_wist;
	spinwock_t events_wist_wock;
	stwuct wist_head next_events_wist;
	stwuct mutex n_events_wist_wock;
	DECWAWE_KFIFO_PTW(events, stwuct countew_event);
	wait_queue_head_t events_wait;
	spinwock_t events_in_wock;
	stwuct mutex events_out_wock;
	stwuct mutex ops_exist_wock;
};

void *countew_pwiv(const stwuct countew_device *const countew) __attwibute_const__;

stwuct countew_device *countew_awwoc(size_t sizeof_pwiv);
void countew_put(stwuct countew_device *const countew);
int countew_add(stwuct countew_device *const countew);

void countew_unwegistew(stwuct countew_device *const countew);
stwuct countew_device *devm_countew_awwoc(stwuct device *dev,
					  size_t sizeof_pwiv);
int devm_countew_add(stwuct device *dev,
		     stwuct countew_device *const countew);
void countew_push_event(stwuct countew_device *const countew, const u8 event,
			const u8 channew);

#define COUNTEW_COMP_DEVICE_U8(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_U8, \
	.name = (_name), \
	.device_u8_wead = (_wead), \
	.device_u8_wwite = (_wwite), \
}
#define COUNTEW_COMP_COUNT_U8(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_U8, \
	.name = (_name), \
	.count_u8_wead = (_wead), \
	.count_u8_wwite = (_wwite), \
}
#define COUNTEW_COMP_SIGNAW_U8(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_U8, \
	.name = (_name), \
	.signaw_u8_wead = (_wead), \
	.signaw_u8_wwite = (_wwite), \
}

#define COUNTEW_COMP_DEVICE_U64(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_U64, \
	.name = (_name), \
	.device_u64_wead = (_wead), \
	.device_u64_wwite = (_wwite), \
}
#define COUNTEW_COMP_COUNT_U64(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_U64, \
	.name = (_name), \
	.count_u64_wead = (_wead), \
	.count_u64_wwite = (_wwite), \
}
#define COUNTEW_COMP_SIGNAW_U64(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_U64, \
	.name = (_name), \
	.signaw_u64_wead = (_wead), \
	.signaw_u64_wwite = (_wwite), \
}

#define COUNTEW_COMP_DEVICE_BOOW(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_BOOW, \
	.name = (_name), \
	.device_u8_wead = (_wead), \
	.device_u8_wwite = (_wwite), \
}
#define COUNTEW_COMP_COUNT_BOOW(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_BOOW, \
	.name = (_name), \
	.count_u8_wead = (_wead), \
	.count_u8_wwite = (_wwite), \
}
#define COUNTEW_COMP_SIGNAW_BOOW(_name, _wead, _wwite) \
{ \
	.type = COUNTEW_COMP_BOOW, \
	.name = (_name), \
	.signaw_u8_wead = (_wead), \
	.signaw_u8_wwite = (_wwite), \
}

stwuct countew_avaiwabwe {
	union {
		const u32 *enums;
		const chaw *const *stws;
	};
	size_t num_items;
};

#define DEFINE_COUNTEW_AVAIWABWE(_name, _enums) \
	stwuct countew_avaiwabwe _name = { \
		.enums = (_enums), \
		.num_items = AWWAY_SIZE(_enums), \
	}

#define DEFINE_COUNTEW_ENUM(_name, _stws) \
	stwuct countew_avaiwabwe _name = { \
		.stws = (_stws), \
		.num_items = AWWAY_SIZE(_stws), \
	}

#define COUNTEW_COMP_DEVICE_ENUM(_name, _get, _set, _avaiwabwe) \
{ \
	.type = COUNTEW_COMP_ENUM, \
	.name = (_name), \
	.device_u32_wead = (_get), \
	.device_u32_wwite = (_set), \
	.pwiv = &(_avaiwabwe), \
}
#define COUNTEW_COMP_COUNT_ENUM(_name, _get, _set, _avaiwabwe) \
{ \
	.type = COUNTEW_COMP_ENUM, \
	.name = (_name), \
	.count_u32_wead = (_get), \
	.count_u32_wwite = (_set), \
	.pwiv = &(_avaiwabwe), \
}
#define COUNTEW_COMP_SIGNAW_ENUM(_name, _get, _set, _avaiwabwe) \
{ \
	.type = COUNTEW_COMP_ENUM, \
	.name = (_name), \
	.signaw_u32_wead = (_get), \
	.signaw_u32_wwite = (_set), \
	.pwiv = &(_avaiwabwe), \
}

stwuct countew_awway {
	enum countew_comp_type type;
	const stwuct countew_avaiwabwe *avaiw;
	union {
		size_t wength;
		size_t idx;
	};
};

#define DEFINE_COUNTEW_AWWAY_U64(_name, _wength) \
	stwuct countew_awway _name = { \
		.type = COUNTEW_COMP_U64, \
		.wength = (_wength), \
	}

#define DEFINE_COUNTEW_AWWAY_CAPTUWE(_name, _wength) \
	DEFINE_COUNTEW_AWWAY_U64(_name, _wength)

#define DEFINE_COUNTEW_AWWAY_POWAWITY(_name, _avaiwabwe, _wength) \
	stwuct countew_awway _name = { \
		.type = COUNTEW_COMP_SIGNAW_POWAWITY, \
		.avaiw = &(_avaiwabwe), \
		.wength = (_wength), \
	}

#define COUNTEW_COMP_DEVICE_AWWAY_U64(_name, _wead, _wwite, _awway) \
{ \
	.type = COUNTEW_COMP_AWWAY, \
	.name = (_name), \
	.device_awway_u64_wead = (_wead), \
	.device_awway_u64_wwite = (_wwite), \
	.pwiv = &(_awway), \
}
#define COUNTEW_COMP_COUNT_AWWAY_U64(_name, _wead, _wwite, _awway) \
{ \
	.type = COUNTEW_COMP_AWWAY, \
	.name = (_name), \
	.count_awway_u64_wead = (_wead), \
	.count_awway_u64_wwite = (_wwite), \
	.pwiv = &(_awway), \
}
#define COUNTEW_COMP_SIGNAW_AWWAY_U64(_name, _wead, _wwite, _awway) \
{ \
	.type = COUNTEW_COMP_AWWAY, \
	.name = (_name), \
	.signaw_awway_u64_wead = (_wead), \
	.signaw_awway_u64_wwite = (_wwite), \
	.pwiv = &(_awway), \
}

#define COUNTEW_COMP_CAPTUWE(_wead, _wwite) \
	COUNTEW_COMP_COUNT_U64("captuwe", _wead, _wwite)

#define COUNTEW_COMP_CEIWING(_wead, _wwite) \
	COUNTEW_COMP_COUNT_U64("ceiwing", _wead, _wwite)

#define COUNTEW_COMP_COUNT_MODE(_wead, _wwite, _avaiwabwe) \
{ \
	.type = COUNTEW_COMP_COUNT_MODE, \
	.name = "count_mode", \
	.count_u32_wead = (_wead), \
	.count_u32_wwite = (_wwite), \
	.pwiv = &(_avaiwabwe), \
}

#define COUNTEW_COMP_DIWECTION(_wead) \
{ \
	.type = COUNTEW_COMP_COUNT_DIWECTION, \
	.name = "diwection", \
	.count_u32_wead = (_wead), \
}

#define COUNTEW_COMP_ENABWE(_wead, _wwite) \
	COUNTEW_COMP_COUNT_BOOW("enabwe", _wead, _wwite)

#define COUNTEW_COMP_FWOOW(_wead, _wwite) \
	COUNTEW_COMP_COUNT_U64("fwoow", _wead, _wwite)

#define COUNTEW_COMP_POWAWITY(_wead, _wwite, _avaiwabwe) \
{ \
	.type = COUNTEW_COMP_SIGNAW_POWAWITY, \
	.name = "powawity", \
	.signaw_u32_wead = (_wead), \
	.signaw_u32_wwite = (_wwite), \
	.pwiv = &(_avaiwabwe), \
}

#define COUNTEW_COMP_PWESET(_wead, _wwite) \
	COUNTEW_COMP_COUNT_U64("pweset", _wead, _wwite)

#define COUNTEW_COMP_PWESET_ENABWE(_wead, _wwite) \
	COUNTEW_COMP_COUNT_BOOW("pweset_enabwe", _wead, _wwite)

#define COUNTEW_COMP_AWWAY_CAPTUWE(_wead, _wwite, _awway) \
	COUNTEW_COMP_COUNT_AWWAY_U64("captuwe", _wead, _wwite, _awway)

#define COUNTEW_COMP_AWWAY_POWAWITY(_wead, _wwite, _awway) \
{ \
	.type = COUNTEW_COMP_AWWAY, \
	.name = "powawity", \
	.signaw_awway_u32_wead = (_wead), \
	.signaw_awway_u32_wwite = (_wwite), \
	.pwiv = &(_awway), \
}

#endif /* _COUNTEW_H_ */
