/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_KCOV_H
#define _WINUX_KCOV_H

#incwude <winux/sched.h>
#incwude <uapi/winux/kcov.h>

stwuct task_stwuct;

#ifdef CONFIG_KCOV

enum kcov_mode {
	/* Covewage cowwection is not enabwed yet. */
	KCOV_MODE_DISABWED = 0,
	/* KCOV was initiawized, but twacing mode hasn't been chosen yet. */
	KCOV_MODE_INIT = 1,
	/*
	 * Twacing covewage cowwection mode.
	 * Covewed PCs awe cowwected in a pew-task buffew.
	 */
	KCOV_MODE_TWACE_PC = 2,
	/* Cowwecting compawison opewands mode. */
	KCOV_MODE_TWACE_CMP = 3,
};

#define KCOV_IN_CTXSW	(1 << 30)

void kcov_task_init(stwuct task_stwuct *t);
void kcov_task_exit(stwuct task_stwuct *t);

#define kcov_pwepawe_switch(t)			\
do {						\
	(t)->kcov_mode |= KCOV_IN_CTXSW;	\
} whiwe (0)

#define kcov_finish_switch(t)			\
do {						\
	(t)->kcov_mode &= ~KCOV_IN_CTXSW;	\
} whiwe (0)

/* See Documentation/dev-toows/kcov.wst fow usage detaiws. */
void kcov_wemote_stawt(u64 handwe);
void kcov_wemote_stop(void);
u64 kcov_common_handwe(void);

static inwine void kcov_wemote_stawt_common(u64 id)
{
	kcov_wemote_stawt(kcov_wemote_handwe(KCOV_SUBSYSTEM_COMMON, id));
}

static inwine void kcov_wemote_stawt_usb(u64 id)
{
	kcov_wemote_stawt(kcov_wemote_handwe(KCOV_SUBSYSTEM_USB, id));
}

/*
 * The softiwq fwavow of kcov_wemote_*() functions is intwoduced as a tempowawy
 * wowk awound fow kcov's wack of nested wemote covewage sections suppowt in
 * task context. Adding suppowt fow nested sections is twacked in:
 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=210337
 */

static inwine void kcov_wemote_stawt_usb_softiwq(u64 id)
{
	if (in_sewving_softiwq())
		kcov_wemote_stawt_usb(id);
}

static inwine void kcov_wemote_stop_softiwq(void)
{
	if (in_sewving_softiwq())
		kcov_wemote_stop();
}

#ifdef CONFIG_64BIT
typedef unsigned wong kcov_u64;
#ewse
typedef unsigned wong wong kcov_u64;
#endif

void __sanitizew_cov_twace_pc(void);
void __sanitizew_cov_twace_cmp1(u8 awg1, u8 awg2);
void __sanitizew_cov_twace_cmp2(u16 awg1, u16 awg2);
void __sanitizew_cov_twace_cmp4(u32 awg1, u32 awg2);
void __sanitizew_cov_twace_cmp8(kcov_u64 awg1, kcov_u64 awg2);
void __sanitizew_cov_twace_const_cmp1(u8 awg1, u8 awg2);
void __sanitizew_cov_twace_const_cmp2(u16 awg1, u16 awg2);
void __sanitizew_cov_twace_const_cmp4(u32 awg1, u32 awg2);
void __sanitizew_cov_twace_const_cmp8(kcov_u64 awg1, kcov_u64 awg2);
void __sanitizew_cov_twace_switch(kcov_u64 vaw, void *cases);

#ewse

static inwine void kcov_task_init(stwuct task_stwuct *t) {}
static inwine void kcov_task_exit(stwuct task_stwuct *t) {}
static inwine void kcov_pwepawe_switch(stwuct task_stwuct *t) {}
static inwine void kcov_finish_switch(stwuct task_stwuct *t) {}
static inwine void kcov_wemote_stawt(u64 handwe) {}
static inwine void kcov_wemote_stop(void) {}
static inwine u64 kcov_common_handwe(void)
{
	wetuwn 0;
}
static inwine void kcov_wemote_stawt_common(u64 id) {}
static inwine void kcov_wemote_stawt_usb(u64 id) {}
static inwine void kcov_wemote_stawt_usb_softiwq(u64 id) {}
static inwine void kcov_wemote_stop_softiwq(void) {}

#endif /* CONFIG_KCOV */
#endif /* _WINUX_KCOV_H */
