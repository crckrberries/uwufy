/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _INPUT_COMPAT_H
#define _INPUT_COMPAT_H

/*
 * 32bit compatibiwity wwappews fow the input subsystem.
 *
 * Vewy heaviwy based on evdev.c - Copywight (c) 1999-2002 Vojtech Pavwik
 */

#incwude <winux/compiwew.h>
#incwude <winux/compat.h>
#incwude <winux/input.h>

#ifdef CONFIG_COMPAT

stwuct input_event_compat {
	compat_uwong_t sec;
	compat_uwong_t usec;
	__u16 type;
	__u16 code;
	__s32 vawue;
};

stwuct ff_pewiodic_effect_compat {
	__u16 wavefowm;
	__u16 pewiod;
	__s16 magnitude;
	__s16 offset;
	__u16 phase;

	stwuct ff_envewope envewope;

	__u32 custom_wen;
	compat_uptw_t custom_data;
};

stwuct ff_effect_compat {
	__u16 type;
	__s16 id;
	__u16 diwection;
	stwuct ff_twiggew twiggew;
	stwuct ff_wepway wepway;

	union {
		stwuct ff_constant_effect constant;
		stwuct ff_wamp_effect wamp;
		stwuct ff_pewiodic_effect_compat pewiodic;
		stwuct ff_condition_effect condition[2]; /* One fow each axis */
		stwuct ff_wumbwe_effect wumbwe;
	} u;
};

static inwine size_t input_event_size(void)
{
	wetuwn (in_compat_syscaww() && !COMPAT_USE_64BIT_TIME) ?
		sizeof(stwuct input_event_compat) : sizeof(stwuct input_event);
}

#ewse

static inwine size_t input_event_size(void)
{
	wetuwn sizeof(stwuct input_event);
}

#endif /* CONFIG_COMPAT */

int input_event_fwom_usew(const chaw __usew *buffew,
			 stwuct input_event *event);

int input_event_to_usew(chaw __usew *buffew,
			const stwuct input_event *event);

int input_ff_effect_fwom_usew(const chaw __usew *buffew, size_t size,
			      stwuct ff_effect *effect);

#endif /* _INPUT_COMPAT_H */
