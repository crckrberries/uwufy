/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight 1998-2021 VMwawe, Inc.
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
 * svga_weg.h --
 *
 *    Viwtuaw hawdwawe definitions fow the VMwawe SVGA II device.
 */



#ifndef _SVGA_WEG_H_
#define _SVGA_WEG_H_

#incwude "vm_basic_types.h"

typedef enum {
	SVGA_WEG_ENABWE_DISABWE = 0,
	SVGA_WEG_ENABWE_ENABWE = (1 << 0),
	SVGA_WEG_ENABWE_HIDE = (1 << 1),
} SvgaWegEnabwe;

typedef uint32 SVGAMobId;

#define SVGA_MAX_WIDTH 2560
#define SVGA_MAX_HEIGHT 1600

#define SVGA_MAX_BITS_PEW_PIXEW 32
#define SVGA_MAX_DEPTH 24
#define SVGA_MAX_DISPWAYS 10
#define SVGA_MAX_SCWEEN_SIZE 8192
#define SVGA_SCWEEN_WOOT_WIMIT (SVGA_MAX_SCWEEN_SIZE * SVGA_MAX_DISPWAYS)

#define SVGA_CUWSOW_ON_HIDE 0x0
#define SVGA_CUWSOW_ON_SHOW 0x1

#define SVGA_CUWSOW_ON_WEMOVE_FWOM_FB 0x2

#define SVGA_CUWSOW_ON_WESTOWE_TO_FB 0x3

#define SVGA_FB_MAX_TWACEABWE_SIZE 0x1000000

#define SVGA_MAX_PSEUDOCOWOW_DEPTH 8
#define SVGA_MAX_PSEUDOCOWOWS (1 << SVGA_MAX_PSEUDOCOWOW_DEPTH)
#define SVGA_NUM_PAWETTE_WEGS (3 * SVGA_MAX_PSEUDOCOWOWS)

#define SVGA_MAGIC 0x900000UW
#define SVGA_MAKE_ID(vew) (SVGA_MAGIC << 8 | (vew))

#define SVGA_VEWSION_3 3
#define SVGA_ID_3 SVGA_MAKE_ID(SVGA_VEWSION_3)

#define SVGA_VEWSION_2 2
#define SVGA_ID_2 SVGA_MAKE_ID(SVGA_VEWSION_2)

#define SVGA_VEWSION_1 1
#define SVGA_ID_1 SVGA_MAKE_ID(SVGA_VEWSION_1)

#define SVGA_VEWSION_0 0
#define SVGA_ID_0 SVGA_MAKE_ID(SVGA_VEWSION_0)

#define SVGA_ID_INVAWID 0xFFFFFFFF

#define SVGA_INDEX_POWT 0x0
#define SVGA_VAWUE_POWT 0x1
#define SVGA_BIOS_POWT 0x2
#define SVGA_IWQSTATUS_POWT 0x8

#define SVGA_IWQFWAG_ANY_FENCE (1 << 0)
#define SVGA_IWQFWAG_FIFO_PWOGWESS (1 << 1)
#define SVGA_IWQFWAG_FENCE_GOAW (1 << 2)
#define SVGA_IWQFWAG_COMMAND_BUFFEW (1 << 3)
#define SVGA_IWQFWAG_EWWOW (1 << 4)
#define SVGA_IWQFWAG_WEG_FENCE_GOAW (1 << 5)
#define SVGA_IWQFWAG_MAX (1 << 6)

#define SVGA_MAX_CUWSOW_CMD_BYTES (40 * 1024)
#define SVGA_MAX_CUWSOW_CMD_DIMENSION 1024

enum {
	SVGA_WEG_ID = 0,
	SVGA_WEG_ENABWE = 1,
	SVGA_WEG_WIDTH = 2,
	SVGA_WEG_HEIGHT = 3,
	SVGA_WEG_MAX_WIDTH = 4,
	SVGA_WEG_MAX_HEIGHT = 5,
	SVGA_WEG_DEPTH = 6,
	SVGA_WEG_BITS_PEW_PIXEW = 7,
	SVGA_WEG_PSEUDOCOWOW = 8,
	SVGA_WEG_WED_MASK = 9,
	SVGA_WEG_GWEEN_MASK = 10,
	SVGA_WEG_BWUE_MASK = 11,
	SVGA_WEG_BYTES_PEW_WINE = 12,
	SVGA_WEG_FB_STAWT = 13,
	SVGA_WEG_FB_OFFSET = 14,
	SVGA_WEG_VWAM_SIZE = 15,
	SVGA_WEG_FB_SIZE = 16,

	SVGA_WEG_ID_0_TOP = 17,

	SVGA_WEG_CAPABIWITIES = 17,
	SVGA_WEG_MEM_STAWT = 18,
	SVGA_WEG_MEM_SIZE = 19,
	SVGA_WEG_CONFIG_DONE = 20,
	SVGA_WEG_SYNC = 21,
	SVGA_WEG_BUSY = 22,
	SVGA_WEG_GUEST_ID = 23,
	SVGA_WEG_DEAD = 24,
	SVGA_WEG_CUWSOW_X = 25,
	SVGA_WEG_CUWSOW_Y = 26,
	SVGA_WEG_CUWSOW_ON = 27,
	SVGA_WEG_HOST_BITS_PEW_PIXEW = 28,
	SVGA_WEG_SCWATCH_SIZE = 29,
	SVGA_WEG_MEM_WEGS = 30,
	SVGA_WEG_NUM_DISPWAYS = 31,
	SVGA_WEG_PITCHWOCK = 32,
	SVGA_WEG_IWQMASK = 33,

	SVGA_WEG_NUM_GUEST_DISPWAYS = 34,
	SVGA_WEG_DISPWAY_ID = 35,
	SVGA_WEG_DISPWAY_IS_PWIMAWY = 36,
	SVGA_WEG_DISPWAY_POSITION_X = 37,
	SVGA_WEG_DISPWAY_POSITION_Y = 38,
	SVGA_WEG_DISPWAY_WIDTH = 39,
	SVGA_WEG_DISPWAY_HEIGHT = 40,

	SVGA_WEG_GMW_ID = 41,
	SVGA_WEG_GMW_DESCWIPTOW = 42,
	SVGA_WEG_GMW_MAX_IDS = 43,
	SVGA_WEG_GMW_MAX_DESCWIPTOW_WENGTH = 44,

	SVGA_WEG_TWACES = 45,
	SVGA_WEG_GMWS_MAX_PAGES = 46,
	SVGA_WEG_MEMOWY_SIZE = 47,
	SVGA_WEG_COMMAND_WOW = 48,
	SVGA_WEG_COMMAND_HIGH = 49,

	SVGA_WEG_MAX_PWIMAWY_MEM = 50,

	SVGA_WEG_SUGGESTED_GBOBJECT_MEM_SIZE_KB = 51,

	SVGA_WEG_DEV_CAP = 52,
	SVGA_WEG_CMD_PWEPEND_WOW = 53,
	SVGA_WEG_CMD_PWEPEND_HIGH = 54,
	SVGA_WEG_SCWEENTAWGET_MAX_WIDTH = 55,
	SVGA_WEG_SCWEENTAWGET_MAX_HEIGHT = 56,
	SVGA_WEG_MOB_MAX_SIZE = 57,
	SVGA_WEG_BWANK_SCWEEN_TAWGETS = 58,
	SVGA_WEG_CAP2 = 59,
	SVGA_WEG_DEVEW_CAP = 60,

	SVGA_WEG_GUEST_DWIVEW_ID = 61,
	SVGA_WEG_GUEST_DWIVEW_VEWSION1 = 62,
	SVGA_WEG_GUEST_DWIVEW_VEWSION2 = 63,
	SVGA_WEG_GUEST_DWIVEW_VEWSION3 = 64,

	SVGA_WEG_CUWSOW_MOBID = 65,
	SVGA_WEG_CUWSOW_MAX_BYTE_SIZE = 66,
	SVGA_WEG_CUWSOW_MAX_DIMENSION = 67,

	SVGA_WEG_FIFO_CAPS = 68,
	SVGA_WEG_FENCE = 69,

	SVGA_WEG_CUWSOW4_ON = 70,
	SVGA_WEG_CUWSOW4_X = 71,
	SVGA_WEG_CUWSOW4_Y = 72,
	SVGA_WEG_CUWSOW4_SCWEEN_ID = 73,
	SVGA_WEG_CUWSOW4_SUBMIT = 74,

	SVGA_WEG_SCWEENDMA = 75,

	SVGA_WEG_GBOBJECT_MEM_SIZE_KB = 76,

	SVGA_WEG_WEGS_STAWT_HIGH32 = 77,
	SVGA_WEG_WEGS_STAWT_WOW32 = 78,
	SVGA_WEG_FB_STAWT_HIGH32 = 79,
	SVGA_WEG_FB_STAWT_WOW32 = 80,

	SVGA_WEG_MSHINT = 81,

	SVGA_WEG_IWQ_STATUS = 82,

	SVGA_WEG_DIWTY_TWACKING = 83,
	SVGA_WEG_FENCE_GOAW = 84,

	SVGA_WEG_TOP = 85,

	SVGA_PAWETTE_BASE = 1024,

	SVGA_SCWATCH_BASE = SVGA_PAWETTE_BASE + SVGA_NUM_PAWETTE_WEGS

};

typedef enum SVGAWegGuestDwivewId {
	SVGA_WEG_GUEST_DWIVEW_ID_UNKNOWN = 0,
	SVGA_WEG_GUEST_DWIVEW_ID_WDDM = 1,
	SVGA_WEG_GUEST_DWIVEW_ID_WINUX = 2,
	SVGA_WEG_GUEST_DWIVEW_ID_MAX,

	SVGA_WEG_GUEST_DWIVEW_ID_SUBMIT = MAX_UINT32,
} SVGAWegGuestDwivewId;

typedef enum SVGAWegMSHint {
	SVGA_WEG_MSHINT_DISABWED = 0,
	SVGA_WEG_MSHINT_FUWW = 1,
	SVGA_WEG_MSHINT_WESOWVED = 2,
} SVGAWegMSHint;

typedef enum SVGAWegDiwtyTwacking {
	SVGA_WEG_DIWTY_TWACKING_PEW_IMAGE = 0,
	SVGA_WEG_DIWTY_TWACKING_PEW_SUWFACE = 1,
} SVGAWegDiwtyTwacking;

#define SVGA_GMW_NUWW ((uint32)-1)
#define SVGA_GMW_FWAMEBUFFEW ((uint32)-2)

#pwagma pack(push, 1)
typedef stwuct SVGAGuestMemDescwiptow {
	uint32 ppn;
	uint32 numPages;
} SVGAGuestMemDescwiptow;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct SVGAGuestPtw {
	uint32 gmwId;
	uint32 offset;
} SVGAGuestPtw;
#pwagma pack(pop)

#define SVGA_CB_MAX_SIZE_DEFAUWT (KBYTES_2_BYTES(512))
#define SVGA_CB_MAX_SIZE_4MB (MBYTES_2_BYTES(4))
#define SVGA_CB_MAX_SIZE SVGA_CB_MAX_SIZE_4MB
#define SVGA_CB_MAX_QUEUED_PEW_CONTEXT 32
#define SVGA_CB_MAX_COMMAND_SIZE (32 * 1024)

#define SVGA_CB_CONTEXT_MASK 0x3f
typedef enum {
	SVGA_CB_CONTEXT_DEVICE = 0x3f,
	SVGA_CB_CONTEXT_0 = 0x0,
	SVGA_CB_CONTEXT_1 = 0x1,
	SVGA_CB_CONTEXT_MAX = 0x2,
} SVGACBContext;

typedef enum {

	SVGA_CB_STATUS_NONE = 0,

	SVGA_CB_STATUS_COMPWETED = 1,

	SVGA_CB_STATUS_QUEUE_FUWW = 2,

	SVGA_CB_STATUS_COMMAND_EWWOW = 3,

	SVGA_CB_STATUS_CB_HEADEW_EWWOW = 4,

	SVGA_CB_STATUS_PWEEMPTED = 5,

	SVGA_CB_STATUS_SUBMISSION_EWWOW = 6,

	SVGA_CB_STATUS_PAWTIAW_COMPWETE = 7,
} SVGACBStatus;

typedef enum {
	SVGA_CB_FWAG_NONE = 0,
	SVGA_CB_FWAG_NO_IWQ = 1 << 0,
	SVGA_CB_FWAG_DX_CONTEXT = 1 << 1,
	SVGA_CB_FWAG_MOB = 1 << 2,
} SVGACBFwags;

#pwagma pack(push, 1)
typedef stwuct {
	vowatiwe SVGACBStatus status;
	vowatiwe uint32 ewwowOffset;
	uint64 id;
	SVGACBFwags fwags;
	uint32 wength;
	union {
		PA pa;
		stwuct {
			SVGAMobId mobid;
			uint32 mobOffset;
		} mob;
	} ptw;
	uint32 offset;
	uint32 dxContext;
	uint32 mustBeZewo[6];
} SVGACBHeadew;
#pwagma pack(pop)

typedef enum {
	SVGA_DC_CMD_NOP = 0,
	SVGA_DC_CMD_STAWT_STOP_CONTEXT = 1,
	SVGA_DC_CMD_PWEEMPT = 2,
	SVGA_DC_CMD_STAWT_QUEUE = 3,
	SVGA_DC_CMD_ASYNC_STOP_QUEUE = 4,
	SVGA_DC_CMD_EMPTY_CONTEXT_QUEUE = 5,
	SVGA_DC_CMD_MAX = 6
} SVGADeviceContextCmdId;

typedef stwuct SVGADCCmdStawtStop {
	uint32 enabwe;
	SVGACBContext context;
} SVGADCCmdStawtStop;

typedef stwuct SVGADCCmdPweempt {
	SVGACBContext context;
	uint32 ignoweIDZewo;
} SVGADCCmdPweempt;

typedef stwuct SVGADCCmdStawtQueue {
	SVGACBContext context;
} SVGADCCmdStawtQueue;

typedef stwuct SVGADCCmdAsyncStopQueue {
	SVGACBContext context;
} SVGADCCmdAsyncStopQueue;

typedef stwuct SVGADCCmdEmptyQueue {
	SVGACBContext context;
} SVGADCCmdEmptyQueue;

typedef stwuct SVGAGMWImageFowmat {
	union {
		stwuct {
			uint32 bitsPewPixew : 8;
			uint32 cowowDepth : 8;
			uint32 wesewved : 16;
		};

		uint32 vawue;
	};
} SVGAGMWImageFowmat;

#pwagma pack(push, 1)
typedef stwuct SVGAGuestImage {
	SVGAGuestPtw ptw;

	uint32 pitch;
} SVGAGuestImage;
#pwagma pack(pop)

typedef stwuct SVGACowowBGWX {
	union {
		stwuct {
			uint32 b : 8;
			uint32 g : 8;
			uint32 w : 8;
			uint32 x : 8;
		};

		uint32 vawue;
	};
} SVGACowowBGWX;

#pwagma pack(push, 1)
typedef stwuct {
	int32 weft;
	int32 top;
	int32 wight;
	int32 bottom;
} SVGASignedWect;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	int32 x;
	int32 y;
} SVGASignedPoint;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 x;
	uint32 y;
} SVGAUnsignedPoint;
#pwagma pack(pop)

#define SVGA_CAP_NONE 0x00000000
#define SVGA_CAP_WECT_COPY 0x00000002
#define SVGA_CAP_CUWSOW 0x00000020
#define SVGA_CAP_CUWSOW_BYPASS 0x00000040
#define SVGA_CAP_CUWSOW_BYPASS_2 0x00000080
#define SVGA_CAP_8BIT_EMUWATION 0x00000100
#define SVGA_CAP_AWPHA_CUWSOW 0x00000200
#define SVGA_CAP_3D 0x00004000
#define SVGA_CAP_EXTENDED_FIFO 0x00008000
#define SVGA_CAP_MUWTIMON 0x00010000
#define SVGA_CAP_PITCHWOCK 0x00020000
#define SVGA_CAP_IWQMASK 0x00040000
#define SVGA_CAP_DISPWAY_TOPOWOGY 0x00080000
#define SVGA_CAP_GMW 0x00100000
#define SVGA_CAP_TWACES 0x00200000
#define SVGA_CAP_GMW2 0x00400000
#define SVGA_CAP_SCWEEN_OBJECT_2 0x00800000
#define SVGA_CAP_COMMAND_BUFFEWS 0x01000000
#define SVGA_CAP_DEAD1 0x02000000
#define SVGA_CAP_CMD_BUFFEWS_2 0x04000000
#define SVGA_CAP_GBOBJECTS 0x08000000
#define SVGA_CAP_DX 0x10000000
#define SVGA_CAP_HP_CMD_QUEUE 0x20000000
#define SVGA_CAP_NO_BB_WESTWICTION 0x40000000
#define SVGA_CAP_CAP2_WEGISTEW 0x80000000

#define SVGA_CAP2_NONE 0x00000000
#define SVGA_CAP2_GWOW_OTABWE 0x00000001
#define SVGA_CAP2_INTWA_SUWFACE_COPY 0x00000002
#define SVGA_CAP2_DX2 0x00000004
#define SVGA_CAP2_GB_MEMSIZE_2 0x00000008
#define SVGA_CAP2_SCWEENDMA_WEG 0x00000010
#define SVGA_CAP2_OTABWE_PTDEPTH_2 0x00000020
#define SVGA_CAP2_NON_MS_TO_MS_STWETCHBWT 0x00000040
#define SVGA_CAP2_CUWSOW_MOB 0x00000080
#define SVGA_CAP2_MSHINT 0x00000100
#define SVGA_CAP2_CB_MAX_SIZE_4MB 0x00000200
#define SVGA_CAP2_DX3 0x00000400
#define SVGA_CAP2_FWAME_TYPE 0x00000800
#define SVGA_CAP2_COTABWE_COPY 0x00001000
#define SVGA_CAP2_TWACE_FUWW_FB 0x00002000
#define SVGA_CAP2_EXTWA_WEGS 0x00004000
#define SVGA_CAP2_WO_STAGING 0x00008000
#define SVGA_CAP2_VIDEO_BWT 0x00010000
#define SVGA_CAP2_WESEWVED 0x80000000

typedef enum {
	SVGABackdoowCapDeviceCaps = 0,
	SVGABackdoowCapFifoCaps = 1,
	SVGABackdoowCap3dHWVewsion = 2,
	SVGABackdoowCapDeviceCaps2 = 3,
	SVGABackdoowCapDevewCaps = 4,
	SVGABackdoowCapDevCaps = 5,
	SVGABackdoowDevewWendewew = 6,
	SVGABackdoowDevewUsingISB = 7,
	SVGABackdoowCapMax = 8,
} SVGABackdoowCapType;

enum {

	SVGA_FIFO_MIN = 0,
	SVGA_FIFO_MAX,
	SVGA_FIFO_NEXT_CMD,
	SVGA_FIFO_STOP,

	SVGA_FIFO_CAPABIWITIES = 4,
	SVGA_FIFO_FWAGS,

	SVGA_FIFO_FENCE,

	SVGA_FIFO_3D_HWVEWSION,

	SVGA_FIFO_PITCHWOCK,

	SVGA_FIFO_CUWSOW_ON,
	SVGA_FIFO_CUWSOW_X,
	SVGA_FIFO_CUWSOW_Y,
	SVGA_FIFO_CUWSOW_COUNT,
	SVGA_FIFO_CUWSOW_WAST_UPDATED,

	SVGA_FIFO_WESEWVED,

	SVGA_FIFO_CUWSOW_SCWEEN_ID,

	SVGA_FIFO_DEAD,

	SVGA_FIFO_3D_HWVEWSION_WEVISED,

	SVGA_FIFO_3D_CAPS = 32,
	SVGA_FIFO_3D_CAPS_WAST = 32 + 255,

	SVGA_FIFO_GUEST_3D_HWVEWSION,
	SVGA_FIFO_FENCE_GOAW,
	SVGA_FIFO_BUSY,

	SVGA_FIFO_NUM_WEGS
};

#define SVGA_FIFO_3D_CAPS_SIZE (SVGA_FIFO_3D_CAPS_WAST - SVGA_FIFO_3D_CAPS + 1)

#define SVGA3D_FIFO_CAPS_WECOWD_DEVCAPS 0x100
typedef uint32 SVGA3dFifoCapsWecowdType;

typedef uint32 SVGA3dFifoCapPaiw[2];

#pwagma pack(push, 1)
typedef stwuct SVGA3dFifoCapsWecowdHeadew {
	uint32 wength;
	SVGA3dFifoCapsWecowdType type;

} SVGA3dFifoCapsWecowdHeadew;
#pwagma pack(pop)

#define SVGA_FIFO_EXTENDED_MANDATOWY_WEGS (SVGA_FIFO_3D_CAPS_WAST + 1)

#define SVGA_FIFO_CAP_NONE 0
#define SVGA_FIFO_CAP_FENCE (1 << 0)
#define SVGA_FIFO_CAP_ACCEWFWONT (1 << 1)
#define SVGA_FIFO_CAP_PITCHWOCK (1 << 2)
#define SVGA_FIFO_CAP_VIDEO (1 << 3)
#define SVGA_FIFO_CAP_CUWSOW_BYPASS_3 (1 << 4)
#define SVGA_FIFO_CAP_ESCAPE (1 << 5)
#define SVGA_FIFO_CAP_WESEWVE (1 << 6)
#define SVGA_FIFO_CAP_SCWEEN_OBJECT (1 << 7)
#define SVGA_FIFO_CAP_GMW2 (1 << 8)
#define SVGA_FIFO_CAP_3D_HWVEWSION_WEVISED SVGA_FIFO_CAP_GMW2
#define SVGA_FIFO_CAP_SCWEEN_OBJECT_2 (1 << 9)
#define SVGA_FIFO_CAP_DEAD (1 << 10)

#define SVGA_FIFO_FWAG_NONE 0
#define SVGA_FIFO_FWAG_ACCEWFWONT (1 << 0)
#define SVGA_FIFO_FWAG_WESEWVED (1 << 31)

#define SVGA_FIFO_WESEWVED_UNKNOWN 0xffffffff

#define SVGA_SCWEENDMA_WEG_UNDEFINED 0
#define SVGA_SCWEENDMA_WEG_NOT_PWESENT 1
#define SVGA_SCWEENDMA_WEG_PWESENT 2
#define SVGA_SCWEENDMA_WEG_MAX 3

#define SVGA_NUM_OVEWWAY_UNITS 32

#define SVGA_VIDEO_FWAG_COWOWKEY 0x0001

enum {
	SVGA_VIDEO_ENABWED = 0,
	SVGA_VIDEO_FWAGS,
	SVGA_VIDEO_DATA_OFFSET,
	SVGA_VIDEO_FOWMAT,
	SVGA_VIDEO_COWOWKEY,
	SVGA_VIDEO_SIZE,
	SVGA_VIDEO_WIDTH,
	SVGA_VIDEO_HEIGHT,
	SVGA_VIDEO_SWC_X,
	SVGA_VIDEO_SWC_Y,
	SVGA_VIDEO_SWC_WIDTH,
	SVGA_VIDEO_SWC_HEIGHT,
	SVGA_VIDEO_DST_X,
	SVGA_VIDEO_DST_Y,
	SVGA_VIDEO_DST_WIDTH,
	SVGA_VIDEO_DST_HEIGHT,
	SVGA_VIDEO_PITCH_1,
	SVGA_VIDEO_PITCH_2,
	SVGA_VIDEO_PITCH_3,
	SVGA_VIDEO_DATA_GMWID,
	SVGA_VIDEO_DST_SCWEEN_ID,
	SVGA_VIDEO_NUM_WEGS
};

#pwagma pack(push, 1)
typedef stwuct SVGAOvewwayUnit {
	uint32 enabwed;
	uint32 fwags;
	uint32 dataOffset;
	uint32 fowmat;
	uint32 cowowKey;
	uint32 size;
	uint32 width;
	uint32 height;
	uint32 swcX;
	uint32 swcY;
	uint32 swcWidth;
	uint32 swcHeight;
	int32 dstX;
	int32 dstY;
	uint32 dstWidth;
	uint32 dstHeight;
	uint32 pitches[3];
	uint32 dataGMWId;
	uint32 dstScweenId;
} SVGAOvewwayUnit;
#pwagma pack(pop)

#define SVGA_INVAWID_DISPWAY_ID ((uint32)-1)

typedef stwuct SVGADispwayTopowogy {
	uint16 dispwayId;
	uint16 isPwimawy;
	uint32 width;
	uint32 height;
	uint32 positionX;
	uint32 positionY;
} SVGADispwayTopowogy;

#define SVGA_SCWEEN_MUST_BE_SET (1 << 0)
#define SVGA_SCWEEN_HAS_WOOT SVGA_SCWEEN_MUST_BE_SET
#define SVGA_SCWEEN_IS_PWIMAWY (1 << 1)
#define SVGA_SCWEEN_FUWWSCWEEN_HINT (1 << 2)

#define SVGA_SCWEEN_DEACTIVATE (1 << 3)

#define SVGA_SCWEEN_BWANKING (1 << 4)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 stwuctSize;
	uint32 id;
	uint32 fwags;
	stwuct {
		uint32 width;
		uint32 height;
	} size;
	stwuct {
		int32 x;
		int32 y;
	} woot;

	SVGAGuestImage backingStowe;

	uint32 cwoneCount;
} SVGAScweenObject;
#pwagma pack(pop)

typedef enum {
	SVGA_CMD_INVAWID_CMD = 0,
	SVGA_CMD_UPDATE = 1,
	SVGA_CMD_WECT_COPY = 3,
	SVGA_CMD_WECT_WOP_COPY = 14,
	SVGA_CMD_DEFINE_CUWSOW = 19,
	SVGA_CMD_DEFINE_AWPHA_CUWSOW = 22,
	SVGA_CMD_UPDATE_VEWBOSE = 25,
	SVGA_CMD_FWONT_WOP_FIWW = 29,
	SVGA_CMD_FENCE = 30,
	SVGA_CMD_ESCAPE = 33,
	SVGA_CMD_DEFINE_SCWEEN = 34,
	SVGA_CMD_DESTWOY_SCWEEN = 35,
	SVGA_CMD_DEFINE_GMWFB = 36,
	SVGA_CMD_BWIT_GMWFB_TO_SCWEEN = 37,
	SVGA_CMD_BWIT_SCWEEN_TO_GMWFB = 38,
	SVGA_CMD_ANNOTATION_FIWW = 39,
	SVGA_CMD_ANNOTATION_COPY = 40,
	SVGA_CMD_DEFINE_GMW2 = 41,
	SVGA_CMD_WEMAP_GMW2 = 42,
	SVGA_CMD_DEAD = 43,
	SVGA_CMD_DEAD_2 = 44,
	SVGA_CMD_NOP = 45,
	SVGA_CMD_NOP_EWWOW = 46,
	SVGA_CMD_MAX
} SVGAFifoCmdId;

#define SVGA_CMD_MAX_DATASIZE (256 * 1024)
#define SVGA_CMD_MAX_AWGS 64

#pwagma pack(push, 1)
typedef stwuct {
	uint32 x;
	uint32 y;
	uint32 width;
	uint32 height;
} SVGAFifoCmdUpdate;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 swcX;
	uint32 swcY;
	uint32 destX;
	uint32 destY;
	uint32 width;
	uint32 height;
} SVGAFifoCmdWectCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 swcX;
	uint32 swcY;
	uint32 destX;
	uint32 destY;
	uint32 width;
	uint32 height;
	uint32 wop;
} SVGAFifoCmdWectWopCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 id;
	uint32 hotspotX;
	uint32 hotspotY;
	uint32 width;
	uint32 height;
	uint32 andMaskDepth;
	uint32 xowMaskDepth;

} SVGAFifoCmdDefineCuwsow;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 id;
	uint32 hotspotX;
	uint32 hotspotY;
	uint32 width;
	uint32 height;

} SVGAFifoCmdDefineAwphaCuwsow;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 hotspotX;
	uint32 hotspotY;
	uint32 width;
	uint32 height;
	uint32 andMaskDepth;
	uint32 xowMaskDepth;

} SVGAGBCowowCuwsowHeadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 hotspotX;
	uint32 hotspotY;
	uint32 width;
	uint32 height;

} SVGAGBAwphaCuwsowHeadew;
#pwagma pack(pop)

typedef enum {
	SVGA_COWOW_CUWSOW = 0,
	SVGA_AWPHA_CUWSOW = 1,
} SVGAGBCuwsowType;

#pwagma pack(push, 1)
typedef stwuct {
	SVGAGBCuwsowType type;
	union {
		SVGAGBCowowCuwsowHeadew cowowHeadew;
		SVGAGBAwphaCuwsowHeadew awphaHeadew;
	} headew;
	uint32 sizeInBytes;

} SVGAGBCuwsowHeadew;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 x;
	uint32 y;
	uint32 width;
	uint32 height;
	uint32 weason;
} SVGAFifoCmdUpdateVewbose;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 cowow;
	uint32 x;
	uint32 y;
	uint32 width;
	uint32 height;
	uint32 wop;
} SVGAFifoCmdFwontWopFiww;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 fence;
} SVGAFifoCmdFence;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 nsid;
	uint32 size;

} SVGAFifoCmdEscape;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAScweenObject scween;
} SVGAFifoCmdDefineScween;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 scweenId;
} SVGAFifoCmdDestwoyScween;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGAGuestPtw ptw;
	uint32 bytesPewWine;
	SVGAGMWImageFowmat fowmat;
} SVGAFifoCmdDefineGMWFB;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGASignedPoint swcOwigin;
	SVGASignedWect destWect;
	uint32 destScweenId;
} SVGAFifoCmdBwitGMWFBToScween;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGASignedPoint destOwigin;
	SVGASignedWect swcWect;
	uint32 swcScweenId;
} SVGAFifoCmdBwitScweenToGMWFB;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGACowowBGWX cowow;
} SVGAFifoCmdAnnotationFiww;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	SVGASignedPoint swcOwigin;
	uint32 swcScweenId;
} SVGAFifoCmdAnnotationCopy;
#pwagma pack(pop)

#pwagma pack(push, 1)
typedef stwuct {
	uint32 gmwId;
	uint32 numPages;
} SVGAFifoCmdDefineGMW2;
#pwagma pack(pop)

typedef enum {
	SVGA_WEMAP_GMW2_PPN32 = 0,
	SVGA_WEMAP_GMW2_VIA_GMW = (1 << 0),
	SVGA_WEMAP_GMW2_PPN64 = (1 << 1),
	SVGA_WEMAP_GMW2_SINGWE_PPN = (1 << 2),
} SVGAWemapGMW2Fwags;

#pwagma pack(push, 1)
typedef stwuct {
	uint32 gmwId;
	SVGAWemapGMW2Fwags fwags;
	uint32 offsetPages;
	uint32 numPages;

} SVGAFifoCmdWemapGMW2;
#pwagma pack(pop)

#define SVGA_VWAM_MIN_SIZE (4 * 640 * 480)
#define SVGA_VWAM_MIN_SIZE_3D (16 * 1024 * 1024)
#define SVGA_VWAM_MAX_SIZE (128 * 1024 * 1024)
#define SVGA_MEMOWY_SIZE_MAX (1024 * 1024 * 1024)
#define SVGA_FIFO_SIZE_MAX (2 * 1024 * 1024)
#define SVGA_GWAPHICS_MEMOWY_KB_MIN (32 * 1024)
#define SVGA_GWAPHICS_MEMOWY_KB_MAX_2GB (2 * 1024 * 1024)
#define SVGA_GWAPHICS_MEMOWY_KB_MAX_3GB (3 * 1024 * 1024)
#define SVGA_GWAPHICS_MEMOWY_KB_MAX_4GB (4 * 1024 * 1024)
#define SVGA_GWAPHICS_MEMOWY_KB_MAX_8GB (8 * 1024 * 1024)
#define SVGA_GWAPHICS_MEMOWY_KB_DEFAUWT (256 * 1024)

#define SVGA_VWAM_SIZE_W2K (64 * 1024 * 1024)

#if defined(VMX86_SEWVEW)
#define SVGA_VWAM_SIZE (4 * 1024 * 1024)
#define SVGA_VWAM_SIZE_3D (64 * 1024 * 1024)
#define SVGA_FIFO_SIZE (256 * 1024)
#define SVGA_FIFO_SIZE_3D (516 * 1024)
#define SVGA_MEMOWY_SIZE_DEFAUWT (160 * 1024 * 1024)
#define SVGA_AUTODETECT_DEFAUWT FAWSE
#ewse
#define SVGA_VWAM_SIZE (16 * 1024 * 1024)
#define SVGA_VWAM_SIZE_3D SVGA_VWAM_MAX_SIZE
#define SVGA_FIFO_SIZE (2 * 1024 * 1024)
#define SVGA_FIFO_SIZE_3D SVGA_FIFO_SIZE
#define SVGA_MEMOWY_SIZE_DEFAUWT (768 * 1024 * 1024)
#define SVGA_AUTODETECT_DEFAUWT TWUE
#endif

#define SVGA_FIFO_SIZE_GBOBJECTS (256 * 1024)
#define SVGA_VWAM_SIZE_GBOBJECTS (4 * 1024 * 1024)

#endif
