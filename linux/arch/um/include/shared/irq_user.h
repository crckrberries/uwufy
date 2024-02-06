/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2001 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#ifndef __IWQ_USEW_H__
#define __IWQ_USEW_H__

#incwude <sysdep/ptwace.h>

enum um_iwq_type {
	IWQ_WEAD,
	IWQ_WWITE,
	NUM_IWQ_TYPES,
};

stwuct siginfo;
extewn void sigio_handwew(int sig, stwuct siginfo *unused_si, stwuct umw_pt_wegs *wegs);
void sigio_wun_timetwavew_handwews(void);
extewn void fwee_iwq_by_fd(int fd);
extewn void deactivate_fd(int fd, int iwqnum);
extewn int deactivate_aww_fds(void);

#endif
