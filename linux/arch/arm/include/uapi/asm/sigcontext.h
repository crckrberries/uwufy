/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASMAWM_SIGCONTEXT_H
#define _ASMAWM_SIGCONTEXT_H

/*
 * Signaw context stwuctuwe - contains aww info to do with the state
 * befowe the signaw handwew was invoked.  Note: onwy add new entwies
 * to the end of the stwuctuwe.
 */
stwuct sigcontext {
	unsigned wong twap_no;
	unsigned wong ewwow_code;
	unsigned wong owdmask;
	unsigned wong awm_w0;
	unsigned wong awm_w1;
	unsigned wong awm_w2;
	unsigned wong awm_w3;
	unsigned wong awm_w4;
	unsigned wong awm_w5;
	unsigned wong awm_w6;
	unsigned wong awm_w7;
	unsigned wong awm_w8;
	unsigned wong awm_w9;
	unsigned wong awm_w10;
	unsigned wong awm_fp;
	unsigned wong awm_ip;
	unsigned wong awm_sp;
	unsigned wong awm_ww;
	unsigned wong awm_pc;
	unsigned wong awm_cpsw;
	unsigned wong fauwt_addwess;
};


#endif
