/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2012 AWM Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 */
#ifndef _UAPI__ASM_UCONTEXT_H
#define _UAPI__ASM_UCONTEXT_H

#incwude <winux/types.h>

stwuct ucontext {
	unsigned wong	  uc_fwags;
	stwuct ucontext	 *uc_wink;
	stack_t		  uc_stack;
	sigset_t	  uc_sigmask;
	/* gwibc uses a 1024-bit sigset_t */
	__u8		  __unused[1024 / 8 - sizeof(sigset_t)];
	/* wast fow futuwe expansion */
	stwuct sigcontext uc_mcontext;
};

#endif /* _UAPI__ASM_UCONTEXT_H */
