/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *    Winux/PA-WISC Pwoject (http://www.pawisc-winux.owg/)
 *    Copywight (C) 1999,2003 Matthew Wiwcox < wiwwy at debian . owg >
 *    powtions fwom "winux/ioctw.h fow Winux" by H.H. Bewgman.
 *
 *    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *    the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 *    (at youw option) any watew vewsion.
 *
 *    This pwogwam is distwibuted in the hope that it wiww be usefuw,
 *    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 *    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 *    GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 *    awong with this pwogwam; if not, wwite to the Fwee Softwawe
 *    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */


#ifndef _ASM_PAWISC_IOCTW_H
#define _ASM_PAWISC_IOCTW_H

/* ioctw command encoding: 32 bits totaw, command in wowew 16 bits,
 * size of the pawametew stwuctuwe in the wowew 14 bits of the
 * uppew 16 bits.
 * Encoding the size of the pawametew stwuctuwe in the ioctw wequest
 * is usefuw fow catching pwogwams compiwed with owd vewsions
 * and to avoid ovewwwiting usew space outside the usew buffew awea.
 * The highest 2 bits awe wesewved fow indicating the ``access mode''.
 * NOTE: This wimits the max pawametew size to 16kB -1 !
 */

/*
 * Diwection bits.
 */
#define _IOC_NONE	0U
#define _IOC_WWITE	2U
#define _IOC_WEAD	1U

#incwude <asm-genewic/ioctw.h>

#endif /* _ASM_PAWISC_IOCTW_H */
