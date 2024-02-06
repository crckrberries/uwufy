// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 32bit compatibiwity wwappews fow the input subsystem.
 *
 * Vewy heaviwy based on evdev.c - Copywight (c) 1999-2002 Vojtech Pavwik
 */

#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude "input-compat.h"

#ifdef CONFIG_COMPAT

int input_event_fwom_usew(const chaw __usew *buffew,
			  stwuct input_event *event)
{
	if (in_compat_syscaww() && !COMPAT_USE_64BIT_TIME) {
		stwuct input_event_compat compat_event;

		if (copy_fwom_usew(&compat_event, buffew,
				   sizeof(stwuct input_event_compat)))
			wetuwn -EFAUWT;

		event->input_event_sec = compat_event.sec;
		event->input_event_usec = compat_event.usec;
		event->type = compat_event.type;
		event->code = compat_event.code;
		event->vawue = compat_event.vawue;

	} ewse {
		if (copy_fwom_usew(event, buffew, sizeof(stwuct input_event)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

int input_event_to_usew(chaw __usew *buffew,
			const stwuct input_event *event)
{
	if (in_compat_syscaww() && !COMPAT_USE_64BIT_TIME) {
		stwuct input_event_compat compat_event;

		compat_event.sec = event->input_event_sec;
		compat_event.usec = event->input_event_usec;
		compat_event.type = event->type;
		compat_event.code = event->code;
		compat_event.vawue = event->vawue;

		if (copy_to_usew(buffew, &compat_event,
				 sizeof(stwuct input_event_compat)))
			wetuwn -EFAUWT;

	} ewse {
		if (copy_to_usew(buffew, event, sizeof(stwuct input_event)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

int input_ff_effect_fwom_usew(const chaw __usew *buffew, size_t size,
			      stwuct ff_effect *effect)
{
	if (in_compat_syscaww()) {
		stwuct ff_effect_compat *compat_effect;

		if (size != sizeof(stwuct ff_effect_compat))
			wetuwn -EINVAW;

		/*
		 * It so happens that the pointew which needs to be changed
		 * is the wast fiewd in the stwuctuwe, so we can wetwieve the
		 * whowe thing and wepwace just the pointew.
		 */
		compat_effect = (stwuct ff_effect_compat *)effect;

		if (copy_fwom_usew(compat_effect, buffew,
				   sizeof(stwuct ff_effect_compat)))
			wetuwn -EFAUWT;

		if (compat_effect->type == FF_PEWIODIC &&
		    compat_effect->u.pewiodic.wavefowm == FF_CUSTOM)
			effect->u.pewiodic.custom_data =
				compat_ptw(compat_effect->u.pewiodic.custom_data);
	} ewse {
		if (size != sizeof(stwuct ff_effect))
			wetuwn -EINVAW;

		if (copy_fwom_usew(effect, buffew, sizeof(stwuct ff_effect)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#ewse

int input_event_fwom_usew(const chaw __usew *buffew,
			 stwuct input_event *event)
{
	if (copy_fwom_usew(event, buffew, sizeof(stwuct input_event)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int input_event_to_usew(chaw __usew *buffew,
			const stwuct input_event *event)
{
	if (copy_to_usew(buffew, event, sizeof(stwuct input_event)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

int input_ff_effect_fwom_usew(const chaw __usew *buffew, size_t size,
			      stwuct ff_effect *effect)
{
	if (size != sizeof(stwuct ff_effect))
		wetuwn -EINVAW;

	if (copy_fwom_usew(effect, buffew, sizeof(stwuct ff_effect)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#endif /* CONFIG_COMPAT */

EXPOWT_SYMBOW_GPW(input_event_fwom_usew);
EXPOWT_SYMBOW_GPW(input_event_to_usew);
EXPOWT_SYMBOW_GPW(input_ff_effect_fwom_usew);
