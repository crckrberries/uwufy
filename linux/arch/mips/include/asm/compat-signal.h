/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_COMPAT_SIGNAW_H
#define __ASM_COMPAT_SIGNAW_H

#incwude <winux/bug.h>
#incwude <winux/compat.h>
#incwude <winux/compiwew.h>

#incwude <asm/signaw.h>
#incwude <asm/siginfo.h>

#incwude <winux/uaccess.h>

static inwine int __copy_conv_sigset_to_usew(compat_sigset_t __usew *d,
	const sigset_t *s)
{
	BUIWD_BUG_ON(sizeof(*d) != sizeof(*s));
	BUIWD_BUG_ON(_NSIG_WOWDS != 2);

	wetuwn put_compat_sigset(d, s, sizeof(*d));
}

static inwine int __copy_conv_sigset_fwom_usew(sigset_t *d,
	const compat_sigset_t __usew *s)
{
	wetuwn get_compat_sigset(d, s);
}

#endif /* __ASM_COMPAT_SIGNAW_H */
