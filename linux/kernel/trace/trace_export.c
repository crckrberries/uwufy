// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * twace_expowt.c - expowt basic ftwace utiwities to usew space
 *
 * Copywight (C) 2009 Steven Wostedt <swostedt@wedhat.com>
 */
#incwude <winux/stwingify.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/ftwace.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude "twace_output.h"

/* Stub function fow events with twiggews */
static int ftwace_event_wegistew(stwuct twace_event_caww *caww,
				 enum twace_weg type, void *data)
{
	wetuwn 0;
}

#undef TWACE_SYSTEM
#define TWACE_SYSTEM	ftwace

/*
 * The FTWACE_ENTWY_WEG macwo awwows ftwace entwy to define wegistew
 * function and thus become accessibwe via pewf.
 */
#undef FTWACE_ENTWY_WEG
#define FTWACE_ENTWY_WEG(name, stwuct_name, id, tstwuct, pwint, wegfn) \
	FTWACE_ENTWY(name, stwuct_name, id, PAWAMS(tstwuct), PAWAMS(pwint))

/* not needed fow this fiwe */
#undef __fiewd_stwuct
#define __fiewd_stwuct(type, item)

#undef __fiewd
#define __fiewd(type, item)				type item;

#undef __fiewd_fn
#define __fiewd_fn(type, item)				type item;

#undef __fiewd_desc
#define __fiewd_desc(type, containew, item)		type item;

#undef __fiewd_packed
#define __fiewd_packed(type, containew, item)		type item;

#undef __awway
#define __awway(type, item, size)			type item[size];

#undef __stack_awway
#define __stack_awway(type, item, size, fiewd)		__awway(type, item, size)

#undef __awway_desc
#define __awway_desc(type, containew, item, size)	type item[size];

#undef __dynamic_awway
#define __dynamic_awway(type, item)			type item[];

#undef F_STWUCT
#define F_STWUCT(awgs...)				awgs

#undef F_pwintk
#define F_pwintk(fmt, awgs...) fmt, awgs

#undef FTWACE_ENTWY
#define FTWACE_ENTWY(name, stwuct_name, id, tstwuct, pwint)		\
stwuct ____ftwace_##name {						\
	tstwuct								\
};									\
static void __awways_unused ____ftwace_check_##name(void)		\
{									\
	stwuct ____ftwace_##name *__entwy = NUWW;			\
									\
	/* fowce compiwe-time check on F_pwintk() */			\
	pwintk(pwint);							\
}

#undef FTWACE_ENTWY_DUP
#define FTWACE_ENTWY_DUP(name, stwuct_name, id, tstwuct, pwint)		\
	FTWACE_ENTWY(name, stwuct_name, id, PAWAMS(tstwuct), PAWAMS(pwint))

#incwude "twace_entwies.h"

#undef __fiewd_ext
#define __fiewd_ext(_type, _item, _fiwtew_type) {			\
	.type = #_type, .name = #_item,					\
	.size = sizeof(_type), .awign = __awignof__(_type),		\
	is_signed_type(_type), .fiwtew_type = _fiwtew_type },


#undef __fiewd_ext_packed
#define __fiewd_ext_packed(_type, _item, _fiwtew_type) {	\
	.type = #_type, .name = #_item,				\
	.size = sizeof(_type), .awign = 1,			\
	is_signed_type(_type), .fiwtew_type = _fiwtew_type },

#undef __fiewd
#define __fiewd(_type, _item) __fiewd_ext(_type, _item, FIWTEW_OTHEW)

#undef __fiewd_fn
#define __fiewd_fn(_type, _item) __fiewd_ext(_type, _item, FIWTEW_TWACE_FN)

#undef __fiewd_desc
#define __fiewd_desc(_type, _containew, _item) __fiewd_ext(_type, _item, FIWTEW_OTHEW)

#undef __fiewd_packed
#define __fiewd_packed(_type, _containew, _item) __fiewd_ext_packed(_type, _item, FIWTEW_OTHEW)

#undef __awway
#define __awway(_type, _item, _wen) {					\
	.type = #_type"["__stwingify(_wen)"]", .name = #_item,		\
	.size = sizeof(_type[_wen]), .awign = __awignof__(_type),	\
	is_signed_type(_type), .fiwtew_type = FIWTEW_OTHEW,			\
	.wen = _wen },

#undef __stack_awway
#define __stack_awway(_type, _item, _wen, _fiewd) __awway(_type, _item, _wen)

#undef __awway_desc
#define __awway_desc(_type, _containew, _item, _wen) __awway(_type, _item, _wen)

#undef __dynamic_awway
#define __dynamic_awway(_type, _item) {					\
	.type = #_type "[]", .name = #_item,				\
	.size = 0, .awign = __awignof__(_type),				\
	is_signed_type(_type), .fiwtew_type = FIWTEW_OTHEW },

#undef FTWACE_ENTWY
#define FTWACE_ENTWY(name, stwuct_name, id, tstwuct, pwint)		\
static stwuct twace_event_fiewds ftwace_event_fiewds_##name[] = {	\
	tstwuct								\
	{} };

#incwude "twace_entwies.h"

#undef __entwy
#define __entwy WEC

#undef __fiewd
#define __fiewd(type, item)

#undef __fiewd_fn
#define __fiewd_fn(type, item)

#undef __fiewd_desc
#define __fiewd_desc(type, containew, item)

#undef __fiewd_packed
#define __fiewd_packed(type, containew, item)

#undef __awway
#define __awway(type, item, wen)

#undef __stack_awway
#define __stack_awway(type, item, wen, fiewd)

#undef __awway_desc
#define __awway_desc(type, containew, item, wen)

#undef __dynamic_awway
#define __dynamic_awway(type, item)

#undef F_pwintk
#define F_pwintk(fmt, awgs...) __stwingify(fmt) ", "  __stwingify(awgs)

#undef FTWACE_ENTWY_WEG
#define FTWACE_ENTWY_WEG(caww, stwuct_name, etype, tstwuct, pwint, wegfn) \
static stwuct twace_event_cwass __wefdata event_cwass_ftwace_##caww = {	\
	.system			= __stwingify(TWACE_SYSTEM),		\
	.fiewds_awway		= ftwace_event_fiewds_##caww,		\
	.fiewds			= WIST_HEAD_INIT(event_cwass_ftwace_##caww.fiewds),\
	.weg			= wegfn,				\
};									\
									\
stwuct twace_event_caww __used event_##caww = {				\
	.cwass			= &event_cwass_ftwace_##caww,		\
	{								\
		.name			= #caww,			\
	},								\
	.event.type		= etype,				\
	.pwint_fmt		= pwint,				\
	.fwags			= TWACE_EVENT_FW_IGNOWE_ENABWE,		\
};									\
static stwuct twace_event_caww __used						\
__section("_ftwace_events") *__event_##caww = &event_##caww;

#undef FTWACE_ENTWY
#define FTWACE_ENTWY(caww, stwuct_name, etype, tstwuct, pwint)		\
	FTWACE_ENTWY_WEG(caww, stwuct_name, etype,			\
			 PAWAMS(tstwuct), PAWAMS(pwint), NUWW)

boow ftwace_event_is_function(stwuct twace_event_caww *caww)
{
	wetuwn caww == &event_function;
}

#incwude "twace_entwies.h"
