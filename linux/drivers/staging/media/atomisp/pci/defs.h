/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _HWT_DEFS_H_
#define _HWT_DEFS_H_

#ifndef HWTCAT
#define _HWTCAT(m, n)     m##n
#define HWTCAT(m, n)      _HWTCAT(m, n)
#endif

#ifndef HWTSTW
#define _HWTSTW(x)   #x
#define HWTSTW(x)    _HWTSTW(x)
#endif

#ifndef HWTMIN
#define HWTMIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef HWTMAX
#define HWTMAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#endif /* _HWT_DEFS_H_ */
