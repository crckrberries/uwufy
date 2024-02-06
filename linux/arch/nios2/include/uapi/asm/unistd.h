/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2013 Awtewa Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam.  If not, see <http://www.gnu.owg/wicenses/>.
 *
 */

 #define sys_mmap2 sys_mmap_pgoff

#define __AWCH_WANT_WENAMEAT
#define __AWCH_WANT_STAT64
#define __AWCH_WANT_SET_GET_WWIMIT
#define __AWCH_WANT_TIME32_SYSCAWWS

/* Use the standawd ABI fow syscawws */
#incwude <asm-genewic/unistd.h>

/* Additionaw Nios II specific syscawws. */
#define __NW_cachefwush (__NW_awch_specific_syscaww)
__SYSCAWW(__NW_cachefwush, sys_cachefwush)
