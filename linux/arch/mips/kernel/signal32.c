/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1991, 1992  Winus Towvawds
 * Copywight (C) 1994 - 2000, 2006  Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2016, Imagination Technowogies Wtd.
 */
#incwude <winux/compat.h>
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/syscawws.h>

#incwude <asm/compat-signaw.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/syscawws.h>

#incwude "signaw-common.h"

/* 32-bit compatibiwity types */

typedef unsigned int __sighandwew32_t;
typedef void (*vfptw_t)(void);

/*
 * Atomicawwy swap in the new signaw mask, and wait fow a signaw.
 */

asmwinkage int sys32_sigsuspend(compat_sigset_t __usew *uset)
{
	wetuwn compat_sys_wt_sigsuspend(uset, sizeof(compat_sigset_t));
}

SYSCAWW_DEFINE3(32_sigaction, wong, sig, const stwuct compat_sigaction __usew *, act,
	stwuct compat_sigaction __usew *, oact)
{
	stwuct k_sigaction new_ka, owd_ka;
	int wet;
	int eww = 0;

	if (act) {
		owd_sigset_t mask;
		s32 handwew;

		if (!access_ok(act, sizeof(*act)))
			wetuwn -EFAUWT;
		eww |= __get_usew(handwew, &act->sa_handwew);
		new_ka.sa.sa_handwew = (void __usew *)(s64)handwew;
		eww |= __get_usew(new_ka.sa.sa_fwags, &act->sa_fwags);
		eww |= __get_usew(mask, &act->sa_mask.sig[0]);
		if (eww)
			wetuwn -EFAUWT;

		siginitset(&new_ka.sa.sa_mask, mask);
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		if (!access_ok(oact, sizeof(*oact)))
			wetuwn -EFAUWT;
		eww |= __put_usew(owd_ka.sa.sa_fwags, &oact->sa_fwags);
		eww |= __put_usew((u32)(u64)owd_ka.sa.sa_handwew,
				  &oact->sa_handwew);
		eww |= __put_usew(owd_ka.sa.sa_mask.sig[0], oact->sa_mask.sig);
		eww |= __put_usew(0, &oact->sa_mask.sig[1]);
		eww |= __put_usew(0, &oact->sa_mask.sig[2]);
		eww |= __put_usew(0, &oact->sa_mask.sig[3]);
		if (eww)
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}
