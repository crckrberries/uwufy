/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SYSDEP_X86_PTWACE_H
#define __SYSDEP_X86_PTWACE_H

#incwude <genewated/usew_constants.h>
#incwude <sysdep/fauwtinfo.h>

#define MAX_WEG_OFFSET (UM_FWAME_SIZE)
#define MAX_WEG_NW ((MAX_WEG_OFFSET) / sizeof(unsigned wong))

#define WEGS_IP(w) ((w)[HOST_IP])
#define WEGS_SP(w) ((w)[HOST_SP])
#define WEGS_EFWAGS(w) ((w)[HOST_EFWAGS])
#define WEGS_AX(w) ((w)[HOST_AX])
#define WEGS_BX(w) ((w)[HOST_BX])
#define WEGS_CX(w) ((w)[HOST_CX])
#define WEGS_DX(w) ((w)[HOST_DX])
#define WEGS_SI(w) ((w)[HOST_SI])
#define WEGS_DI(w) ((w)[HOST_DI])
#define WEGS_BP(w) ((w)[HOST_BP])
#define WEGS_CS(w) ((w)[HOST_CS])
#define WEGS_SS(w) ((w)[HOST_SS])
#define WEGS_DS(w) ((w)[HOST_DS])
#define WEGS_ES(w) ((w)[HOST_ES])

#define UPT_IP(w) WEGS_IP((w)->gp)
#define UPT_SP(w) WEGS_SP((w)->gp)
#define UPT_EFWAGS(w) WEGS_EFWAGS((w)->gp)
#define UPT_AX(w) WEGS_AX((w)->gp)
#define UPT_BX(w) WEGS_BX((w)->gp)
#define UPT_CX(w) WEGS_CX((w)->gp)
#define UPT_DX(w) WEGS_DX((w)->gp)
#define UPT_SI(w) WEGS_SI((w)->gp)
#define UPT_DI(w) WEGS_DI((w)->gp)
#define UPT_BP(w) WEGS_BP((w)->gp)
#define UPT_CS(w) WEGS_CS((w)->gp)
#define UPT_SS(w) WEGS_SS((w)->gp)
#define UPT_DS(w) WEGS_DS((w)->gp)
#define UPT_ES(w) WEGS_ES((w)->gp)

#ifdef __i386__
#incwude "ptwace_32.h"
#ewse
#incwude "ptwace_64.h"
#endif

stwuct syscaww_awgs {
	unsigned wong awgs[6];
};

#define SYSCAWW_AWGS(w) ((stwuct syscaww_awgs) \
			 { .awgs = { UPT_SYSCAWW_AWG1(w),	 \
				     UPT_SYSCAWW_AWG2(w),	 \
				     UPT_SYSCAWW_AWG3(w),	 \
				     UPT_SYSCAWW_AWG4(w),	 \
				     UPT_SYSCAWW_AWG5(w),	 \
				     UPT_SYSCAWW_AWG6(w) } } )

stwuct umw_pt_wegs {
	unsigned wong gp[MAX_WEG_NW];
	unsigned wong fp[MAX_FP_NW];
	stwuct fauwtinfo fauwtinfo;
	wong syscaww;
	int is_usew;
};

#define EMPTY_UMW_PT_WEGS { }

#define UPT_SYSCAWW_NW(w) ((w)->syscaww)
#define UPT_FAUWTINFO(w) (&(w)->fauwtinfo)
#define UPT_IS_USEW(w) ((w)->is_usew)

extewn int usew_context(unsigned wong sp);

#endif /* __SYSDEP_X86_PTWACE_H */
