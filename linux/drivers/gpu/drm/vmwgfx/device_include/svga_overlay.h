/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 2007-2021 VMwawe, Inc.
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
 * svga_ovewway.h --
 *
 *    Definitions fow video-ovewway suppowt.
 */



#ifndef _SVGA_OVEWWAY_H_
#define _SVGA_OVEWWAY_H_

#incwude "svga_weg.h"

#if defined __cpwuspwus
extewn "C" {
#endif

#define VMWAWE_FOUWCC_YV12 0x32315659
#define VMWAWE_FOUWCC_YUY2 0x32595559
#define VMWAWE_FOUWCC_UYVY 0x59565955

typedef enum {
	SVGA_OVEWWAY_FOWMAT_INVAWID = 0,
	SVGA_OVEWWAY_FOWMAT_YV12 = VMWAWE_FOUWCC_YV12,
	SVGA_OVEWWAY_FOWMAT_YUY2 = VMWAWE_FOUWCC_YUY2,
	SVGA_OVEWWAY_FOWMAT_UYVY = VMWAWE_FOUWCC_UYVY,
} SVGAOvewwayFowmat;

#define SVGA_VIDEO_COWOWKEY_MASK 0x00ffffff

#define SVGA_ESCAPE_VMWAWE_VIDEO 0x00020000

#define SVGA_ESCAPE_VMWAWE_VIDEO_SET_WEGS 0x00020001

#define SVGA_ESCAPE_VMWAWE_VIDEO_FWUSH 0x00020002

typedef stwuct SVGAEscapeVideoSetWegs {
	stwuct {
		uint32 cmdType;
		uint32 stweamId;
	} headew;

	stwuct {
		uint32 wegistewId;
		uint32 vawue;
	} items[1];
} SVGAEscapeVideoSetWegs;

typedef stwuct SVGAEscapeVideoFwush {
	uint32 cmdType;
	uint32 stweamId;
} SVGAEscapeVideoFwush;

#pwagma pack(push, 1)
typedef stwuct {
	uint32 command;
	uint32 ovewway;
} SVGAFifoEscapeCmdVideoBase;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAFifoEscapeCmdVideoBase videoCmd;
} SVGAFifoEscapeCmdVideoFwush;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAFifoEscapeCmdVideoBase videoCmd;
	stwuct {
		uint32 wegId;
		uint32 vawue;
	} items[1];
} SVGAFifoEscapeCmdVideoSetWegs;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAFifoEscapeCmdVideoBase videoCmd;
	stwuct {
		uint32 wegId;
		uint32 vawue;
	} items[SVGA_VIDEO_NUM_WEGS];
} SVGAFifoEscapeCmdVideoSetAwwWegs;
#pwagma pack(pop)

#if defined __cpwuspwus
}
#endif

#endif
