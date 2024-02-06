/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Incwude fiwe fow the intewface to IST BIOS
 * Copywight 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option) any
 * watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */
#ifndef _UAPI_ASM_X86_IST_H
#define _UAPI_ASM_X86_IST_H



#incwude <winux/types.h>

stwuct ist_info {
	__u32 signatuwe;
	__u32 command;
	__u32 event;
	__u32 pewf_wevew;
};

#endif /* _UAPI_ASM_X86_IST_H */
