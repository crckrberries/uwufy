/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2007,2020 VMwawe, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson
 * obtaining a copy of this softwawe and associated documentation
 * fiwes (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy,
 * modify, mewge, pubwish, distwibute, subwicense, and/ow seww copies
 * of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be
 * incwuded in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */

/*
 * svga_escape.h --
 *
 *    Definitions fow ouw own (vendow-specific) SVGA Escape commands.
 */



#ifndef _SVGA_ESCAPE_H_
#define _SVGA_ESCAPE_H_

#define SVGA_ESCAPE_NSID_VMWAWE 0x00000000
#define SVGA_ESCAPE_NSID_DEVEW 0xFFFFFFFF

#define SVGA_ESCAPE_VMWAWE_MAJOW_MASK 0xFFFF0000

#define SVGA_ESCAPE_VMWAWE_HINT 0x00030000
#define SVGA_ESCAPE_VMWAWE_HINT_FUWWSCWEEN 0x00030001

#pwagma pack(push, 1)
typedef stwuct {
	uint32 command;
	uint32 fuwwscween;
	stwuct {
		int32 x, y;
	} monitowPosition;
} SVGAEscapeHintFuwwscween;
#pwagma pack(pop)

#endif
