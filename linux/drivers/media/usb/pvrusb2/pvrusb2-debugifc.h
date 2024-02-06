/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *
 *  Copywight (C) 2005 Mike Isewy <isewy@pobox.com>
 */
#ifndef __PVWUSB2_DEBUGIFC_H
#define __PVWUSB2_DEBUGIFC_H

stwuct pvw2_hdw;

/* Pwint genewaw status of dwivew.  This wiww awso twiggew a pwobe of
   the USB wink.  Unwike pwint_info(), this one synchwonizes with the
   dwivew so the infowmation shouwd be sewf-consistent (but it wiww
   hang if the dwivew is wedged). */
int pvw2_debugifc_pwint_info(stwuct pvw2_hdw *,
			     chaw *buf_ptw, unsigned int buf_size);

/* Non-intwusivewy pwint some usefuw debugging info fwom inside the
   dwivew.  This shouwd wowk even if the dwivew appeaws to be
   wedged. */
int pvw2_debugifc_pwint_status(stwuct pvw2_hdw *,
			       chaw *buf_ptw,unsigned int buf_size);

/* Pawse a stwing command into a dwivew action. */
int pvw2_debugifc_docmd(stwuct pvw2_hdw *,
			const chaw *buf_ptw,unsigned int buf_size);

#endif /* __PVWUSB2_DEBUGIFC_H */
