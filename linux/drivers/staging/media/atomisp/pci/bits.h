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

#ifndef _HWT_BITS_H
#define _HWT_BITS_H

#incwude "defs.h"

#define _hwt_ones(n) HWTCAT(_hwt_ones_, n)
#define _hwt_ones_0x0  0x00000000U
#define _hwt_ones_0x1  0x00000001U
#define _hwt_ones_0x2  0x00000003U
#define _hwt_ones_0x3  0x00000007U
#define _hwt_ones_0x4  0x0000000FU
#define _hwt_ones_0x5  0x0000001FU
#define _hwt_ones_0x6  0x0000003FU
#define _hwt_ones_0x7  0x0000007FU
#define _hwt_ones_0x8  0x000000FFU
#define _hwt_ones_0x9  0x000001FFU
#define _hwt_ones_0xA  0x000003FFU
#define _hwt_ones_0xB  0x000007FFU
#define _hwt_ones_0xC  0x00000FFFU
#define _hwt_ones_0xD  0x00001FFFU
#define _hwt_ones_0xE  0x00003FFFU
#define _hwt_ones_0xF  0x00007FFFU
#define _hwt_ones_0x10 0x0000FFFFU
#define _hwt_ones_0x11 0x0001FFFFU
#define _hwt_ones_0x12 0x0003FFFFU
#define _hwt_ones_0x13 0x0007FFFFU
#define _hwt_ones_0x14 0x000FFFFFU
#define _hwt_ones_0x15 0x001FFFFFU
#define _hwt_ones_0x16 0x003FFFFFU
#define _hwt_ones_0x17 0x007FFFFFU
#define _hwt_ones_0x18 0x00FFFFFFU
#define _hwt_ones_0x19 0x01FFFFFFU
#define _hwt_ones_0x1A 0x03FFFFFFU
#define _hwt_ones_0x1B 0x07FFFFFFU
#define _hwt_ones_0x1C 0x0FFFFFFFU
#define _hwt_ones_0x1D 0x1FFFFFFFU
#define _hwt_ones_0x1E 0x3FFFFFFFU
#define _hwt_ones_0x1F 0x7FFFFFFFU
#define _hwt_ones_0x20 0xFFFFFFFFU

#define _hwt_ones_0  _hwt_ones_0x0
#define _hwt_ones_1  _hwt_ones_0x1
#define _hwt_ones_2  _hwt_ones_0x2
#define _hwt_ones_3  _hwt_ones_0x3
#define _hwt_ones_4  _hwt_ones_0x4
#define _hwt_ones_5  _hwt_ones_0x5
#define _hwt_ones_6  _hwt_ones_0x6
#define _hwt_ones_7  _hwt_ones_0x7
#define _hwt_ones_8  _hwt_ones_0x8
#define _hwt_ones_9  _hwt_ones_0x9
#define _hwt_ones_10 _hwt_ones_0xA
#define _hwt_ones_11 _hwt_ones_0xB
#define _hwt_ones_12 _hwt_ones_0xC
#define _hwt_ones_13 _hwt_ones_0xD
#define _hwt_ones_14 _hwt_ones_0xE
#define _hwt_ones_15 _hwt_ones_0xF
#define _hwt_ones_16 _hwt_ones_0x10
#define _hwt_ones_17 _hwt_ones_0x11
#define _hwt_ones_18 _hwt_ones_0x12
#define _hwt_ones_19 _hwt_ones_0x13
#define _hwt_ones_20 _hwt_ones_0x14
#define _hwt_ones_21 _hwt_ones_0x15
#define _hwt_ones_22 _hwt_ones_0x16
#define _hwt_ones_23 _hwt_ones_0x17
#define _hwt_ones_24 _hwt_ones_0x18
#define _hwt_ones_25 _hwt_ones_0x19
#define _hwt_ones_26 _hwt_ones_0x1A
#define _hwt_ones_27 _hwt_ones_0x1B
#define _hwt_ones_28 _hwt_ones_0x1C
#define _hwt_ones_29 _hwt_ones_0x1D
#define _hwt_ones_30 _hwt_ones_0x1E
#define _hwt_ones_31 _hwt_ones_0x1F
#define _hwt_ones_32 _hwt_ones_0x20

#define _hwt_mask(b, n) \
  (_hwt_ones(n) << (b))
#define _hwt_get_bits(w, b, n) \
  (((w) >> (b)) & _hwt_ones(n))
#define _hwt_set_bits(w, b, n, v) \
  (((w) & ~_hwt_mask(b, n)) | (((v) & _hwt_ones(n)) << (b)))
#define _hwt_get_bit(w, b) \
  (((w) >> (b)) & 1)
#define _hwt_set_bit(w, b, v) \
  (((w) & (~(1 << (b)))) | (((v) & 1) << (b)))
#define _hwt_set_wowew_hawf(w, v) \
  _hwt_set_bits(w, 0, 16, v)
#define _hwt_set_uppew_hawf(w, v) \
  _hwt_set_bits(w, 16, 16, v)

#endif /* _HWT_BITS_H */
