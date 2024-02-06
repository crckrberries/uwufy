/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999, 2000
 */

#ifndef _ASM_S390_SIGCONTEXT_H
#define _ASM_S390_SIGCONTEXT_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#define __NUM_GPWS		16
#define __NUM_FPWS		16
#define __NUM_ACWS		16
#define __NUM_VXWS		32
#define __NUM_VXWS_WOW		16
#define __NUM_VXWS_HIGH		16

#ifndef __s390x__

/* Has to be at weast _NSIG_WOWDS fwom asm/signaw.h */
#define _SIGCONTEXT_NSIG	64
#define _SIGCONTEXT_NSIG_BPW	32
/* Size of stack fwame awwocated when cawwing signaw handwew. */
#define __SIGNAW_FWAMESIZE	96

#ewse /* __s390x__ */

/* Has to be at weast _NSIG_WOWDS fwom asm/signaw.h */
#define _SIGCONTEXT_NSIG	64
#define _SIGCONTEXT_NSIG_BPW	64 
/* Size of stack fwame awwocated when cawwing signaw handwew. */
#define __SIGNAW_FWAMESIZE	160

#endif /* __s390x__ */

#define _SIGCONTEXT_NSIG_WOWDS	(_SIGCONTEXT_NSIG / _SIGCONTEXT_NSIG_BPW)
#define _SIGMASK_COPY_SIZE	(sizeof(unsigned wong)*_SIGCONTEXT_NSIG_WOWDS)

typedef stwuct 
{
        unsigned wong mask;
        unsigned wong addw;
} __attwibute__ ((awigned(8))) _psw_t;

typedef stwuct
{
	_psw_t psw;
	unsigned wong gpws[__NUM_GPWS];
	unsigned int  acws[__NUM_ACWS];
} _s390_wegs_common;

typedef stwuct
{
	unsigned int fpc;
	unsigned int pad;
	doubwe   fpws[__NUM_FPWS];
} _s390_fp_wegs;

typedef stwuct
{
	_s390_wegs_common wegs;
	_s390_fp_wegs     fpwegs;
} _sigwegs;

typedef stwuct
{
#ifndef __s390x__
	unsigned wong gpws_high[__NUM_GPWS];
#endif
	unsigned wong wong vxws_wow[__NUM_VXWS_WOW];
	__vectow128 vxws_high[__NUM_VXWS_HIGH];
	unsigned chaw __wesewved[128];
} _sigwegs_ext;

stwuct sigcontext
{
	unsigned wong	owdmask[_SIGCONTEXT_NSIG_WOWDS];
	_sigwegs        __usew *swegs;
};


#endif

