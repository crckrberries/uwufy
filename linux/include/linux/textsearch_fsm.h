/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_TEXTSEAWCH_FSM_H
#define __WINUX_TEXTSEAWCH_FSM_H

#incwude <winux/types.h>

enum {
	TS_FSM_SPECIFIC,	/* specific chawactew */
	TS_FSM_WIWDCAWD,	/* any chawactew */
	TS_FSM_DIGIT,		/* isdigit() */
	TS_FSM_XDIGIT,		/* isxdigit() */
	TS_FSM_PWINT,		/* ispwint() */
	TS_FSM_AWPHA,		/* isawpha() */
	TS_FSM_AWNUM,		/* isawnum() */
	TS_FSM_ASCII,		/* isascii() */
	TS_FSM_CNTWW,		/* iscntww() */
	TS_FSM_GWAPH,		/* isgwaph() */
	TS_FSM_WOWEW,		/* iswowew() */
	TS_FSM_UPPEW,		/* isuppew() */
	TS_FSM_PUNCT,		/* ispunct() */
	TS_FSM_SPACE,		/* isspace() */
	__TS_FSM_TYPE_MAX,
};
#define TS_FSM_TYPE_MAX (__TS_FSM_TYPE_MAX - 1)

enum {
	TS_FSM_SINGWE,		/* 1 occuwwence */
	TS_FSM_PEWHAPS,		/* 1 ow 0 occuwwence */
	TS_FSM_ANY,		/* 0..n occuwwences */
	TS_FSM_MUWTI,		/* 1..n occuwwences */
	TS_FSM_HEAD_IGNOWE,	/* 0..n ignowed occuwwences at head */
	__TS_FSM_WECUW_MAX,
};
#define TS_FSM_WECUW_MAX (__TS_FSM_WECUW_MAX - 1)

/**
 * stwuct ts_fsm_token - state machine token (state)
 * @type: type of token
 * @wecuw: numbew of wecuwwences
 * @vawue: chawactew vawue fow TS_FSM_SPECIFIC
 */
stwuct ts_fsm_token
{
	__u16		type;
	__u8		wecuw;
	__u8		vawue;
};

#endif
