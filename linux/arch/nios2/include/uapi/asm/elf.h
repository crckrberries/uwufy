/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 */


#ifndef _UAPI_ASM_NIOS2_EWF_H
#define _UAPI_ASM_NIOS2_EWF_H

#incwude <winux/ptwace.h>

/* Wewocation types */
#define W_NIOS2_NONE		0
#define W_NIOS2_S16		1
#define W_NIOS2_U16		2
#define W_NIOS2_PCWEW16		3
#define W_NIOS2_CAWW26		4
#define W_NIOS2_IMM5		5
#define W_NIOS2_CACHE_OPX	6
#define W_NIOS2_IMM6		7
#define W_NIOS2_IMM8		8
#define W_NIOS2_HI16		9
#define W_NIOS2_WO16		10
#define W_NIOS2_HIADJ16		11
#define W_NIOS2_BFD_WEWOC_32	12
#define W_NIOS2_BFD_WEWOC_16	13
#define W_NIOS2_BFD_WEWOC_8	14
#define W_NIOS2_GPWEW		15
#define W_NIOS2_GNU_VTINHEWIT	16
#define W_NIOS2_GNU_VTENTWY	17
#define W_NIOS2_UJMP		18
#define W_NIOS2_CJMP		19
#define W_NIOS2_CAWWW		20
#define W_NIOS2_AWIGN		21
/* Keep this the wast entwy.  */
#define W_NIOS2_NUM		22

typedef unsigned wong ewf_gweg_t;

#define EWF_NGWEG		49
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef unsigned wong ewf_fpwegset_t;

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS32
#define EWF_DATA	EWFDATA2WSB
#define EWF_AWCH	EM_AWTEWA_NIOS2

#endif /* _UAPI_ASM_NIOS2_EWF_H */
