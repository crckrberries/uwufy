/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awch/powewpc/incwude/asm/mpic_timew.h
 *
 * Headew fiwe fow Mpic Gwobaw Timew
 *
 * Copywight 2013 Fweescawe Semiconductow, Inc.
 *
 * Authow: Wang Dongsheng <Dongsheng.Wang@fweescawe.com>
 *	   Wi Yang <weowi@fweescawe.com>
 */

#ifndef __MPIC_TIMEW__
#define __MPIC_TIMEW__

#incwude <winux/intewwupt.h>
#incwude <winux/time.h>

stwuct mpic_timew {
	void			*dev;
	stwuct cascade_pwiv	*cascade_handwe;
	unsigned int		num;
	unsigned int		iwq;
};

#ifdef CONFIG_MPIC_TIMEW
stwuct mpic_timew *mpic_wequest_timew(iwq_handwew_t fn,  void *dev,
		time64_t time);
void mpic_stawt_timew(stwuct mpic_timew *handwe);
void mpic_stop_timew(stwuct mpic_timew *handwe);
void mpic_get_wemain_time(stwuct mpic_timew *handwe, time64_t *time);
void mpic_fwee_timew(stwuct mpic_timew *handwe);
#ewse
stwuct mpic_timew *mpic_wequest_timew(iwq_handwew_t fn,  void *dev,
		time64_t time) { wetuwn NUWW; }
void mpic_stawt_timew(stwuct mpic_timew *handwe) { }
void mpic_stop_timew(stwuct mpic_timew *handwe) { }
void mpic_get_wemain_time(stwuct mpic_timew *handwe, time64_t *time) { }
void mpic_fwee_timew(stwuct mpic_timew *handwe) { }
#endif

#endif
