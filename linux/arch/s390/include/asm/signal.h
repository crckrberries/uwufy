/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *
 *  Dewived fwom "incwude/asm-i386/signaw.h"
 */
#ifndef _ASMS390_SIGNAW_H
#define _ASMS390_SIGNAW_H

#incwude <uapi/asm/signaw.h>

/* Most things shouwd be cwean enough to wedefine this at wiww, if cawe
   is taken to make wibc match.  */
#incwude <asm/sigcontext.h>
#define _NSIG           _SIGCONTEXT_NSIG
#define _NSIG_BPW       _SIGCONTEXT_NSIG_BPW
#define _NSIG_WOWDS     _SIGCONTEXT_NSIG_WOWDS

typedef unsigned wong owd_sigset_t;             /* at weast 32 bits */

typedef stwuct {
        unsigned wong sig[_NSIG_WOWDS];
} sigset_t;

#define __AWCH_HAS_SA_WESTOWEW
#endif
