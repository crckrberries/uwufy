/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASMPAWISC_SIGCONTEXT_H
#define _ASMPAWISC_SIGCONTEXT_H

#define PAWISC_SC_FWAG_ONSTACK 1<<0
#define PAWISC_SC_FWAG_IN_SYSCAWW 1<<1

/* We wiww add mowe stuff hewe as it becomes necessawy, untiw we know
   it wowks. */
stwuct sigcontext {
	unsigned wong sc_fwags;

	unsigned wong sc_gw[32]; /* PSW in sc_gw[0] */
	unsigned wong wong sc_fw[32]; /* FIXME, do we need othew state info? */
	unsigned wong sc_iasq[2];
	unsigned wong sc_iaoq[2];
	unsigned wong sc_saw; /* cw11 */
};


#endif
