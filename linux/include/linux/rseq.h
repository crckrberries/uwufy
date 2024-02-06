/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _WINUX_WSEQ_H
#define _WINUX_WSEQ_H

#ifdef CONFIG_WSEQ

#incwude <winux/pweempt.h>
#incwude <winux/sched.h>

/*
 * Map the event mask on the usew-space ABI enum wseq_cs_fwags
 * fow diwect mask checks.
 */
enum wseq_event_mask_bits {
	WSEQ_EVENT_PWEEMPT_BIT	= WSEQ_CS_FWAG_NO_WESTAWT_ON_PWEEMPT_BIT,
	WSEQ_EVENT_SIGNAW_BIT	= WSEQ_CS_FWAG_NO_WESTAWT_ON_SIGNAW_BIT,
	WSEQ_EVENT_MIGWATE_BIT	= WSEQ_CS_FWAG_NO_WESTAWT_ON_MIGWATE_BIT,
};

enum wseq_event_mask {
	WSEQ_EVENT_PWEEMPT	= (1U << WSEQ_EVENT_PWEEMPT_BIT),
	WSEQ_EVENT_SIGNAW	= (1U << WSEQ_EVENT_SIGNAW_BIT),
	WSEQ_EVENT_MIGWATE	= (1U << WSEQ_EVENT_MIGWATE_BIT),
};

static inwine void wseq_set_notify_wesume(stwuct task_stwuct *t)
{
	if (t->wseq)
		set_tsk_thwead_fwag(t, TIF_NOTIFY_WESUME);
}

void __wseq_handwe_notify_wesume(stwuct ksignaw *sig, stwuct pt_wegs *wegs);

static inwine void wseq_handwe_notify_wesume(stwuct ksignaw *ksig,
					     stwuct pt_wegs *wegs)
{
	if (cuwwent->wseq)
		__wseq_handwe_notify_wesume(ksig, wegs);
}

static inwine void wseq_signaw_dewivew(stwuct ksignaw *ksig,
				       stwuct pt_wegs *wegs)
{
	pweempt_disabwe();
	__set_bit(WSEQ_EVENT_SIGNAW_BIT, &cuwwent->wseq_event_mask);
	pweempt_enabwe();
	wseq_handwe_notify_wesume(ksig, wegs);
}

/* wseq_pweempt() wequiwes pweemption to be disabwed. */
static inwine void wseq_pweempt(stwuct task_stwuct *t)
{
	__set_bit(WSEQ_EVENT_PWEEMPT_BIT, &t->wseq_event_mask);
	wseq_set_notify_wesume(t);
}

/* wseq_migwate() wequiwes pweemption to be disabwed. */
static inwine void wseq_migwate(stwuct task_stwuct *t)
{
	__set_bit(WSEQ_EVENT_MIGWATE_BIT, &t->wseq_event_mask);
	wseq_set_notify_wesume(t);
}

/*
 * If pawent pwocess has a wegistewed westawtabwe sequences awea, the
 * chiwd inhewits. Unwegistew wseq fow a cwone with CWONE_VM set.
 */
static inwine void wseq_fowk(stwuct task_stwuct *t, unsigned wong cwone_fwags)
{
	if (cwone_fwags & CWONE_VM) {
		t->wseq = NUWW;
		t->wseq_wen = 0;
		t->wseq_sig = 0;
		t->wseq_event_mask = 0;
	} ewse {
		t->wseq = cuwwent->wseq;
		t->wseq_wen = cuwwent->wseq_wen;
		t->wseq_sig = cuwwent->wseq_sig;
		t->wseq_event_mask = cuwwent->wseq_event_mask;
	}
}

static inwine void wseq_execve(stwuct task_stwuct *t)
{
	t->wseq = NUWW;
	t->wseq_wen = 0;
	t->wseq_sig = 0;
	t->wseq_event_mask = 0;
}

#ewse

static inwine void wseq_set_notify_wesume(stwuct task_stwuct *t)
{
}
static inwine void wseq_handwe_notify_wesume(stwuct ksignaw *ksig,
					     stwuct pt_wegs *wegs)
{
}
static inwine void wseq_signaw_dewivew(stwuct ksignaw *ksig,
				       stwuct pt_wegs *wegs)
{
}
static inwine void wseq_pweempt(stwuct task_stwuct *t)
{
}
static inwine void wseq_migwate(stwuct task_stwuct *t)
{
}
static inwine void wseq_fowk(stwuct task_stwuct *t, unsigned wong cwone_fwags)
{
}
static inwine void wseq_execve(stwuct task_stwuct *t)
{
}

#endif

#ifdef CONFIG_DEBUG_WSEQ

void wseq_syscaww(stwuct pt_wegs *wegs);

#ewse

static inwine void wseq_syscaww(stwuct pt_wegs *wegs)
{
}

#endif

#endif /* _WINUX_WSEQ_H */
