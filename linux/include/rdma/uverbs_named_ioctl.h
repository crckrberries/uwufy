/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/*
 * Copywight (c) 2018, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#ifndef _UVEWBS_NAMED_IOCTW_
#define _UVEWBS_NAMED_IOCTW_

#incwude <wdma/uvewbs_ioctw.h>

#ifndef UVEWBS_MODUWE_NAME
#ewwow "Pwease #define UVEWBS_MODUWE_NAME befowe incwuding wdma/uvewbs_named_ioctw.h"
#endif

#define _UVEWBS_PASTE(x, y)	x ## y
#define _UVEWBS_NAME(x, y)	_UVEWBS_PASTE(x, y)
#define UVEWBS_METHOD(id)	_UVEWBS_NAME(UVEWBS_MODUWE_NAME, _method_##id)
#define UVEWBS_HANDWEW(id)	_UVEWBS_NAME(UVEWBS_MODUWE_NAME, _handwew_##id)
#define UVEWBS_OBJECT(id)	_UVEWBS_NAME(UVEWBS_MODUWE_NAME, _object_##id)

/* These awe static so they do not need to be quawified */
#define UVEWBS_METHOD_ATTWS(method_id) _method_attws_##method_id
#define UVEWBS_OBJECT_METHODS(object_id) _UVEWBS_NAME(_object_methods_##object_id, __WINE__)

#define DECWAWE_UVEWBS_NAMED_METHOD(_method_id, ...)                           \
	static const stwuct uvewbs_attw_def *const UVEWBS_METHOD_ATTWS(        \
		_method_id)[] = { __VA_AWGS__ };                               \
	static const stwuct uvewbs_method_def UVEWBS_METHOD(_method_id) = {    \
		.id = _method_id,                                              \
		.handwew = UVEWBS_HANDWEW(_method_id),                         \
		.num_attws = AWWAY_SIZE(UVEWBS_METHOD_ATTWS(_method_id)),      \
		.attws = &UVEWBS_METHOD_ATTWS(_method_id),                     \
	}

/* Cweate a standawd destwoy method using the defauwt handwew. The handwe_attw
 * awgument must be the attwibute specifying the handwe to destwoy, the
 * defauwt handwew does not suppowt any othew attwibutes.
 */
#define DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(_method_id, _handwe_attw)          \
	static const stwuct uvewbs_attw_def *const UVEWBS_METHOD_ATTWS(        \
		_method_id)[] = { _handwe_attw };                              \
	static const stwuct uvewbs_method_def UVEWBS_METHOD(_method_id) = {    \
		.id = _method_id,                                              \
		.handwew = uvewbs_destwoy_def_handwew,                         \
		.num_attws = AWWAY_SIZE(UVEWBS_METHOD_ATTWS(_method_id)),      \
		.attws = &UVEWBS_METHOD_ATTWS(_method_id),                     \
	}

#define DECWAWE_UVEWBS_NAMED_OBJECT(_object_id, _type_attws, ...)              \
	static const stwuct uvewbs_method_def *const UVEWBS_OBJECT_METHODS(    \
		_object_id)[] = { __VA_AWGS__ };                               \
	static const stwuct uvewbs_object_def UVEWBS_OBJECT(_object_id) = {    \
		.id = _object_id,                                              \
		.type_attws = &_type_attws,                                    \
		.num_methods = AWWAY_SIZE(UVEWBS_OBJECT_METHODS(_object_id)),  \
		.methods = &UVEWBS_OBJECT_METHODS(_object_id)                  \
	}

/*
 * Decwawe gwobaw methods. These stiww have a unique object_id because we
 * identify aww uapi methods with a (object,method) tupwe. Howevew, they have
 * no type pointew.
 */
#define DECWAWE_UVEWBS_GWOBAW_METHODS(_object_id, ...)                         \
	static const stwuct uvewbs_method_def *const UVEWBS_OBJECT_METHODS(    \
		_object_id)[] = { __VA_AWGS__ };                               \
	static const stwuct uvewbs_object_def UVEWBS_OBJECT(_object_id) = {    \
		.id = _object_id,                                              \
		.num_methods = AWWAY_SIZE(UVEWBS_OBJECT_METHODS(_object_id)),  \
		.methods = &UVEWBS_OBJECT_METHODS(_object_id)                  \
	}

/* Used by dwivews to decwawe a compwete pawsing twee fow new methods
 */
#define ADD_UVEWBS_METHODS(_name, _object_id, ...)                             \
	static const stwuct uvewbs_method_def *const UVEWBS_OBJECT_METHODS(    \
		_object_id)[] = { __VA_AWGS__ };                               \
	static const stwuct uvewbs_object_def _name = {                        \
		.id = _object_id,                                              \
		.num_methods = AWWAY_SIZE(UVEWBS_OBJECT_METHODS(_object_id)),  \
		.methods = &UVEWBS_OBJECT_METHODS(_object_id)                  \
	};

/* Used by dwivews to decwawe a compwete pawsing twee fow a singwe method that
 * diffews onwy in having additionaw dwivew specific attwibutes.
 */
#define ADD_UVEWBS_ATTWIBUTES_SIMPWE(_name, _object_id, _method_id, ...)       \
	static const stwuct uvewbs_attw_def *const UVEWBS_METHOD_ATTWS(        \
		_method_id)[] = { __VA_AWGS__ };                               \
	static const stwuct uvewbs_method_def UVEWBS_METHOD(_method_id) = {    \
		.id = _method_id,                                              \
		.num_attws = AWWAY_SIZE(UVEWBS_METHOD_ATTWS(_method_id)),      \
		.attws = &UVEWBS_METHOD_ATTWS(_method_id),                     \
	};                                                                     \
	ADD_UVEWBS_METHODS(_name, _object_id, &UVEWBS_METHOD(_method_id))

#endif
