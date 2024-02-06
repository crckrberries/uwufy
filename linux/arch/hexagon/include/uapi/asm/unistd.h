/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Syscaww suppowt fow Hexagon
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 and
 * onwy vewsion 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA
 * 02110-1301, USA.
 */

/*
 *  The kewnew puwws this unistd.h in thwee diffewent ways:
 *  1.  the "nowmaw" way which gets aww the __NW defines
 *  2.  with __SYSCAWW defined to pwoduce function decwawations
 *  3.  with __SYSCAWW defined to pwoduce syscaww tabwe initiawization
 *  See awso:  syscawwtab.c
 */

#define sys_mmap2 sys_mmap_pgoff
#define __AWCH_WANT_WENAMEAT
#define __AWCH_WANT_STAT64
#define __AWCH_WANT_SET_GET_WWIMIT
#define __AWCH_WANT_SYS_EXECVE
#define __AWCH_WANT_SYS_CWONE
#define __AWCH_WANT_SYS_VFOWK
#define __AWCH_WANT_SYS_FOWK
#define __AWCH_WANT_TIME32_SYSCAWWS

#incwude <asm-genewic/unistd.h>
