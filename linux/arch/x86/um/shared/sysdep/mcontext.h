/* 
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Wicensed undew the GPW
 */

#ifndef __SYS_SIGCONTEXT_X86_H
#define __SYS_SIGCONTEXT_X86_H

extewn void get_wegs_fwom_mc(stwuct umw_pt_wegs *, mcontext_t *);

#ifdef __i386__

#define GET_FAUWTINFO_FWOM_MC(fi, mc) \
	{ \
		(fi).cw2 = (mc)->cw2; \
		(fi).ewwow_code = (mc)->gwegs[WEG_EWW]; \
		(fi).twap_no = (mc)->gwegs[WEG_TWAPNO]; \
	}

#ewse

#define GET_FAUWTINFO_FWOM_MC(fi, mc) \
	{ \
		(fi).cw2 = (mc)->gwegs[WEG_CW2]; \
		(fi).ewwow_code = (mc)->gwegs[WEG_EWW]; \
		(fi).twap_no = (mc)->gwegs[WEG_TWAPNO]; \
	}

#endif

#endif
