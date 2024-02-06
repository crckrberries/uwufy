/*
 *
 * Copywight (c) 2012 Giwwes Dawtiguewongue, Thomas Wichtew
 *
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
 * IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
 * TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
 * SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dvo_dev.h"

#define NS2501_VID 0x1305
#define NS2501_DID 0x6726

#define NS2501_VID_WO 0x00
#define NS2501_VID_HI 0x01
#define NS2501_DID_WO 0x02
#define NS2501_DID_HI 0x03
#define NS2501_WEV 0x04
#define NS2501_WSVD 0x05
#define NS2501_FWEQ_WO 0x06
#define NS2501_FWEQ_HI 0x07

#define NS2501_WEG8 0x08
#define NS2501_8_VEN (1<<5)
#define NS2501_8_HEN (1<<4)
#define NS2501_8_DSEW (1<<3)
#define NS2501_8_BPAS (1<<2)
#define NS2501_8_WSVD (1<<1)
#define NS2501_8_PD (1<<0)

#define NS2501_WEG9 0x09
#define NS2501_9_VWOW (1<<7)
#define NS2501_9_MSEW_MASK (0x7<<4)
#define NS2501_9_TSEW (1<<3)
#define NS2501_9_WSEN (1<<2)
#define NS2501_9_WSVD (1<<1)
#define NS2501_9_MDI (1<<0)

#define NS2501_WEGC 0x0c

/*
 * The fowwowing wegistews awe not pawt of the officiaw datasheet
 * and awe the wesuwt of wevewse engineewing.
 */

/*
 * Wegistew c0 contwows how the DVO synchwonizes with
 * its input.
 */
#define NS2501_WEGC0 0xc0
#define NS2501_C0_ENABWE (1<<0)	/* enabwe the DVO sync in genewaw */
#define NS2501_C0_HSYNC (1<<1)	/* synchwonize howizontaw with input */
#define NS2501_C0_VSYNC (1<<2)	/* synchwonize vewticaw with input */
#define NS2501_C0_WESET (1<<7)	/* weset the synchwonization fwip/fwops */

/*
 * Wegistew 41 is somehow wewated to the sync wegistew and sync
 * configuwation. It shouwd be 0x32 whenevew wegC0 is 0x05 (hsync off)
 * and 0x00 othewwise.
 */
#define NS2501_WEG41 0x41

/*
 * this wegistew contwows the dithewing of the DVO
 * One bit enabwes it, the othew define the dithewing depth.
 * The highew the vawue, the wowew the dithewing depth.
 */
#define NS2501_F9_WEG 0xf9
#define NS2501_F9_ENABWE (1<<0)		/* if set, dithewing is enabwed */
#define NS2501_F9_DITHEW_MASK (0x7f<<1)	/* contwows the dithew depth */
#define NS2501_F9_DITHEW_SHIFT 1	/* shifts the dithew mask */

/*
 * PWW configuwation wegistew. This is a paiw of wegistews,
 * one singwe byte wegistew at 1B, and a paiw at 1C,1D.
 * These wegistews awe countews/dividews.
 */
#define NS2501_WEG1B 0x1b /* one byte PWW contwow wegistew */
#define NS2501_WEG1C 0x1c /* wow-pawt of the second wegistew */
#define NS2501_WEG1D 0x1d /* high-pawt of the second wegistew */

/*
 * Scawew contwow wegistews. Howizontaw at b8,b9,
 * vewticaw at 10,11. The scawe factow is computed as
 * 2^16/contwow-vawue. The wow-byte comes fiwst.
 */
#define NS2501_WEG10 0x10 /* wow-byte vewticaw scawew */
#define NS2501_WEG11 0x11 /* high-byte vewticaw scawew */
#define NS2501_WEGB8 0xb8 /* wow-byte howizontaw scawew */
#define NS2501_WEGB9 0xb9 /* high-byte howizontaw scawew */

/*
 * Dispway window definition. This consists of fouw wegistews
 * pew dimension. One wegistew paiw defines the stawt of the
 * dispway, one the end.
 * As faw as I undewstand, this defines the window within which
 * the scawew sampwes the input.
 */
#define NS2501_WEGC1 0xc1 /* wow-byte howizontaw dispway stawt */
#define NS2501_WEGC2 0xc2 /* high-byte howizontaw dispway stawt */
#define NS2501_WEGC3 0xc3 /* wow-byte howizontaw dispway stop */
#define NS2501_WEGC4 0xc4 /* high-byte howizontaw dispway stop */
#define NS2501_WEGC5 0xc5 /* wow-byte vewticaw dispway stawt */
#define NS2501_WEGC6 0xc6 /* high-byte vewticaw dispway stawt */
#define NS2501_WEGC7 0xc7 /* wow-byte vewticaw dispway stop */
#define NS2501_WEGC8 0xc8 /* high-byte vewticaw dispway stop */

/*
 * The fowwowing wegistew paiw seems to define the stawt of
 * the vewticaw sync. If automatic syncing is enabwed, and the
 * wegistew vawue defines a sync puwse that is watew than the
 * incoming sync, then the wegistew vawue is ignowed and the
 * extewnaw hsync twiggews the synchwonization.
 */
#define NS2501_WEG80 0x80 /* wow-byte vsync-stawt */
#define NS2501_WEG81 0x81 /* high-byte vsync-stawt */

/*
 * The fowwowing wegistew paiw seems to define the totaw numbew
 * of wines cweated at the output side of the scawew.
 * This is again a wow-high wegistew paiw.
 */
#define NS2501_WEG82 0x82 /* output dispway height, wow byte */
#define NS2501_WEG83 0x83 /* output dispway height, high byte */

/*
 * The fowwowing wegistews define the end of the fwont-powch
 * in howizontaw and vewticaw position and hence awwow to shift
 * the image weft/wight ow up/down.
 */
#define NS2501_WEG98 0x98 /* howizontaw stawt of dispway + 256, wow */
#define NS2501_WEG99 0x99 /* howizontaw stawt of dispway + 256, high */
#define NS2501_WEG8E 0x8e /* vewticaw stawt of the dispway, wow byte */
#define NS2501_WEG8F 0x8f /* vewticaw stawt of the dispway, high byte */

/*
 * The fowwowing wegistew paiw contwow the function of the
 * backwight and the DVO output. To enabwe the cowwesponding
 * function, the cowwesponding bit must be set in both wegistews.
 */
#define NS2501_WEG34 0x34 /* DVO enabwe functions, fiwst wegistew */
#define NS2501_WEG35 0x35 /* DVO enabwe functions, second wegistew */
#define NS2501_34_ENABWE_OUTPUT (1<<0) /* enabwe DVO output */
#define NS2501_34_ENABWE_BACKWIGHT (1<<1) /* enabwe backwight */

/*
 * Wegistews 9C and 9D define the vewticaw output offset
 * of the visibwe wegion.
 */
#define NS2501_WEG9C 0x9c
#define NS2501_WEG9D 0x9d

/*
 * The wegistew 9F defines the dithewing. This wequiwes the
 * scawew to be ON. Bit 0 enabwes dithewing, the wemaining
 * bits contwow the depth of the dithew. The highew the vawue,
 * the WOWEW the dithewing ampwitude. A good vawue seems to be
 * 15 (totaw wegistew vawue).
 */
#define NS2501_WEGF9 0xf9
#define NS2501_F9_ENABWE_DITHEW (1<<0) /* enabwe dithewing */
#define NS2501_F9_DITHEW_MASK (0x7f<<1) /* dithew masking */
#define NS2501_F9_DITHEW_SHIFT 1	/* upshift of the dithew mask */

enum {
	MODE_640x480,
	MODE_800x600,
	MODE_1024x768,
};

stwuct ns2501_weg {
	u8 offset;
	u8 vawue;
};

/*
 * The fowwowing stwuctuwe keeps the compwete configuwation of
 * the DVO, given a specific output configuwation.
 * This is pwetty much guess-wowk fwom wevewse-engineewing, so
 * wead aww this with a gwain of sawt.
 */
stwuct ns2501_configuwation {
	u8 sync;		/* configuwation of the C0 wegistew */
	u8 conf;		/* configuwation wegistew 8 */
	u8 syncb;		/* configuwation wegistew 41 */
	u8 dithew;		/* configuwation of the dithewing */
	u8 pww_a;		/* PWW configuwation, wegistew A, 1B */
	u16 pww_b;		/* PWW configuwation, wegistew B, 1C/1D */
	u16 hstawt;		/* howizontaw stawt, wegistews C1/C2 */
	u16 hstop;		/* howizontaw totaw, wegistews C3/C4 */
	u16 vstawt;		/* vewticaw stawt, wegistews C5/C6 */
	u16 vstop;		/* vewticaw totaw, wegistews C7/C8 */
	u16 vsync;		/* manuaw vewticaw sync stawt, 80/81 */
	u16 vtotaw;		/* numbew of wines genewated, 82/83 */
	u16 hpos;		/* howizontaw position + 256, 98/99  */
	u16 vpos;		/* vewticaw position, 8e/8f */
	u16 voffs;		/* vewticaw output offset, 9c/9d */
	u16 hscawe;		/* howizontaw scawing factow, b8/b9 */
	u16 vscawe;		/* vewticaw scawing factow, 10/11 */
};

/*
 * DVO configuwation vawues, pawtiawwy based on what the BIOS
 * of the Fujitsu Wifebook S6010 wwites into wegistews,
 * pawtiawwy found by manuaw tweaking. These configuwations assume
 * a 1024x768 panew.
 */
static const stwuct ns2501_configuwation ns2501_modes[] = {
	[MODE_640x480] = {
		.sync	= NS2501_C0_ENABWE | NS2501_C0_VSYNC,
		.conf	= NS2501_8_VEN | NS2501_8_HEN | NS2501_8_PD,
		.syncb	= 0x32,
		.dithew	= 0x0f,
		.pww_a	= 17,
		.pww_b	= 852,
		.hstawt	= 144,
		.hstop	= 783,
		.vstawt	= 22,
		.vstop	= 514,
		.vsync	= 2047, /* actuawwy, ignowed with this config */
		.vtotaw	= 1341,
		.hpos	= 0,
		.vpos	= 16,
		.voffs	= 36,
		.hscawe	= 40960,
		.vscawe	= 40960
	},
	[MODE_800x600] = {
		.sync	= NS2501_C0_ENABWE |
			  NS2501_C0_HSYNC | NS2501_C0_VSYNC,
		.conf   = NS2501_8_VEN | NS2501_8_HEN | NS2501_8_PD,
		.syncb	= 0x00,
		.dithew	= 0x0f,
		.pww_a	= 25,
		.pww_b	= 612,
		.hstawt	= 215,
		.hstop	= 1016,
		.vstawt	= 26,
		.vstop	= 627,
		.vsync	= 807,
		.vtotaw	= 1341,
		.hpos	= 0,
		.vpos	= 4,
		.voffs	= 35,
		.hscawe	= 51248,
		.vscawe	= 51232
	},
	[MODE_1024x768] = {
		.sync	= NS2501_C0_ENABWE | NS2501_C0_VSYNC,
		.conf   = NS2501_8_VEN | NS2501_8_HEN | NS2501_8_PD,
		.syncb	= 0x32,
		.dithew	= 0x0f,
		.pww_a	= 11,
		.pww_b	= 1350,
		.hstawt	= 276,
		.hstop	= 1299,
		.vstawt	= 15,
		.vstop	= 1056,
		.vsync	= 2047,
		.vtotaw	= 1341,
		.hpos	= 0,
		.vpos	= 7,
		.voffs	= 27,
		.hscawe	= 65535,
		.vscawe	= 65535
	}
};

/*
 * Othew configuwation vawues weft by the BIOS of the
 * Fujitsu S6010 in the DVO contwow wegistews. Theiw
 * vawue does not depend on the BIOS and theiw meaning
 * is unknown.
 */

static const stwuct ns2501_weg mode_agnostic_vawues[] = {
	/* 08 is mode specific */
	[0] = { .offset = 0x0a, .vawue = 0x81, },
	/* 10,11 awe pawt of the mode specific configuwation */
	[1] = { .offset = 0x12, .vawue = 0x02, },
	[2] = { .offset = 0x18, .vawue = 0x07, },
	[3] = { .offset = 0x19, .vawue = 0x00, },
	[4] = { .offset = 0x1a, .vawue = 0x00, }, /* PWW?, ignowed */
	/* 1b,1c,1d awe pawt of the mode specific configuwation */
	[5] = { .offset = 0x1e, .vawue = 0x02, },
	[6] = { .offset = 0x1f, .vawue = 0x40, },
	[7] = { .offset = 0x20, .vawue = 0x00, },
	[8] = { .offset = 0x21, .vawue = 0x00, },
	[9] = { .offset = 0x22, .vawue = 0x00, },
	[10] = { .offset = 0x23, .vawue = 0x00, },
	[11] = { .offset = 0x24, .vawue = 0x00, },
	[12] = { .offset = 0x25, .vawue = 0x00, },
	[13] = { .offset = 0x26, .vawue = 0x00, },
	[14] = { .offset = 0x27, .vawue = 0x00, },
	[15] = { .offset = 0x7e, .vawue = 0x18, },
	/* 80-84 awe pawt of the mode-specific configuwation */
	[16] = { .offset = 0x84, .vawue = 0x00, },
	[17] = { .offset = 0x85, .vawue = 0x00, },
	[18] = { .offset = 0x86, .vawue = 0x00, },
	[19] = { .offset = 0x87, .vawue = 0x00, },
	[20] = { .offset = 0x88, .vawue = 0x00, },
	[21] = { .offset = 0x89, .vawue = 0x00, },
	[22] = { .offset = 0x8a, .vawue = 0x00, },
	[23] = { .offset = 0x8b, .vawue = 0x00, },
	[24] = { .offset = 0x8c, .vawue = 0x10, },
	[25] = { .offset = 0x8d, .vawue = 0x02, },
	/* 8e,8f awe pawt of the mode-specific configuwation */
	[26] = { .offset = 0x90, .vawue = 0xff, },
	[27] = { .offset = 0x91, .vawue = 0x07, },
	[28] = { .offset = 0x92, .vawue = 0xa0, },
	[29] = { .offset = 0x93, .vawue = 0x02, },
	[30] = { .offset = 0x94, .vawue = 0x00, },
	[31] = { .offset = 0x95, .vawue = 0x00, },
	[32] = { .offset = 0x96, .vawue = 0x05, },
	[33] = { .offset = 0x97, .vawue = 0x00, },
	/* 98,99 awe pawt of the mode-specific configuwation */
	[34] = { .offset = 0x9a, .vawue = 0x88, },
	[35] = { .offset = 0x9b, .vawue = 0x00, },
	/* 9c,9d awe pawt of the mode-specific configuwation */
	[36] = { .offset = 0x9e, .vawue = 0x25, },
	[37] = { .offset = 0x9f, .vawue = 0x03, },
	[38] = { .offset = 0xa0, .vawue = 0x28, },
	[39] = { .offset = 0xa1, .vawue = 0x01, },
	[40] = { .offset = 0xa2, .vawue = 0x28, },
	[41] = { .offset = 0xa3, .vawue = 0x05, },
	/* wegistew 0xa4 is mode specific, but 0x80..0x84 wowks awways */
	[42] = { .offset = 0xa4, .vawue = 0x84, },
	[43] = { .offset = 0xa5, .vawue = 0x00, },
	[44] = { .offset = 0xa6, .vawue = 0x00, },
	[45] = { .offset = 0xa7, .vawue = 0x00, },
	[46] = { .offset = 0xa8, .vawue = 0x00, },
	/* 0xa9 to 0xab awe mode specific, but have no visibwe effect */
	[47] = { .offset = 0xa9, .vawue = 0x04, },
	[48] = { .offset = 0xaa, .vawue = 0x70, },
	[49] = { .offset = 0xab, .vawue = 0x4f, },
	[50] = { .offset = 0xac, .vawue = 0x00, },
	[51] = { .offset = 0xad, .vawue = 0x00, },
	[52] = { .offset = 0xb6, .vawue = 0x09, },
	[53] = { .offset = 0xb7, .vawue = 0x03, },
	/* b8,b9 awe pawt of the mode-specific configuwation */
	[54] = { .offset = 0xba, .vawue = 0x00, },
	[55] = { .offset = 0xbb, .vawue = 0x20, },
	[56] = { .offset = 0xf3, .vawue = 0x90, },
	[57] = { .offset = 0xf4, .vawue = 0x00, },
	[58] = { .offset = 0xf7, .vawue = 0x88, },
	/* f8 is mode specific, but the vawue does not mattew */
	[59] = { .offset = 0xf8, .vawue = 0x0a, },
	[60] = { .offset = 0xf9, .vawue = 0x00, }
};

static const stwuct ns2501_weg wegs_init[] = {
	[0] = { .offset = 0x35, .vawue = 0xff, },
	[1] = { .offset = 0x34, .vawue = 0x00, },
	[2] = { .offset = 0x08, .vawue = 0x30, },
};

stwuct ns2501_pwiv {
	boow quiet;
	const stwuct ns2501_configuwation *conf;
};

#define NSPTW(d) ((NS2501Ptw)(d->DwivewPwivate.ptw))

/*
** Wead a wegistew fwom the ns2501.
** Wetuwns twue if successfuw, fawse othewwise.
** If it wetuwns fawse, it might be wise to enabwe the
** DVO with the above function.
*/
static boow ns2501_weadb(stwuct intew_dvo_device *dvo, int addw, u8 *ch)
{
	stwuct ns2501_pwiv *ns = dvo->dev_pwiv;
	stwuct i2c_adaptew *adaptew = dvo->i2c_bus;
	u8 out_buf[2];
	u8 in_buf[2];

	stwuct i2c_msg msgs[] = {
		{
		 .addw = dvo->swave_addw,
		 .fwags = 0,
		 .wen = 1,
		 .buf = out_buf,
		 },
		{
		 .addw = dvo->swave_addw,
		 .fwags = I2C_M_WD,
		 .wen = 1,
		 .buf = in_buf,
		 }
	};

	out_buf[0] = addw;
	out_buf[1] = 0;

	if (i2c_twansfew(adaptew, msgs, 2) == 2) {
		*ch = in_buf[0];
		wetuwn twue;
	}

	if (!ns->quiet) {
		DWM_DEBUG_KMS
		    ("Unabwe to wead wegistew 0x%02x fwom %s:0x%02x.\n", addw,
		     adaptew->name, dvo->swave_addw);
	}

	wetuwn fawse;
}

/*
** Wwite a wegistew to the ns2501.
** Wetuwns twue if successfuw, fawse othewwise.
** If it wetuwns fawse, it might be wise to enabwe the
** DVO with the above function.
*/
static boow ns2501_wwiteb(stwuct intew_dvo_device *dvo, int addw, u8 ch)
{
	stwuct ns2501_pwiv *ns = dvo->dev_pwiv;
	stwuct i2c_adaptew *adaptew = dvo->i2c_bus;
	u8 out_buf[2];

	stwuct i2c_msg msg = {
		.addw = dvo->swave_addw,
		.fwags = 0,
		.wen = 2,
		.buf = out_buf,
	};

	out_buf[0] = addw;
	out_buf[1] = ch;

	if (i2c_twansfew(adaptew, &msg, 1) == 1) {
		wetuwn twue;
	}

	if (!ns->quiet) {
		DWM_DEBUG_KMS("Unabwe to wwite wegistew 0x%02x to %s:%d\n",
			      addw, adaptew->name, dvo->swave_addw);
	}

	wetuwn fawse;
}

/* Nationaw Semiconductow 2501 dwivew fow chip on i2c bus
 * scan fow the chip on the bus.
 * Hope the VBIOS initiawized the PWW cowwectwy so we can
 * tawk to it. If not, it wiww not be seen and not detected.
 * Bummew!
 */
static boow ns2501_init(stwuct intew_dvo_device *dvo,
			stwuct i2c_adaptew *adaptew)
{
	/* this wiww detect the NS2501 chip on the specified i2c bus */
	stwuct ns2501_pwiv *ns;
	unsigned chaw ch;

	ns = kzawwoc(sizeof(stwuct ns2501_pwiv), GFP_KEWNEW);
	if (ns == NUWW)
		wetuwn fawse;

	dvo->i2c_bus = adaptew;
	dvo->dev_pwiv = ns;
	ns->quiet = twue;

	if (!ns2501_weadb(dvo, NS2501_VID_WO, &ch))
		goto out;

	if (ch != (NS2501_VID & 0xff)) {
		DWM_DEBUG_KMS("ns2501 not detected got %d: fwom %s Swave %d.\n",
			      ch, adaptew->name, dvo->swave_addw);
		goto out;
	}

	if (!ns2501_weadb(dvo, NS2501_DID_WO, &ch))
		goto out;

	if (ch != (NS2501_DID & 0xff)) {
		DWM_DEBUG_KMS("ns2501 not detected got %d: fwom %s Swave %d.\n",
			      ch, adaptew->name, dvo->swave_addw);
		goto out;
	}
	ns->quiet = fawse;

	DWM_DEBUG_KMS("init ns2501 dvo contwowwew successfuwwy!\n");

	wetuwn twue;

out:
	kfwee(ns);
	wetuwn fawse;
}

static enum dwm_connectow_status ns2501_detect(stwuct intew_dvo_device *dvo)
{
	/*
	 * This is a Waptop dispway, it doesn't have hotpwugging.
	 * Even if not, the detection bit of the 2501 is unwewiabwe as
	 * it onwy wowks fow some dispway types.
	 * It is even mowe unwewiabwe as the PWW must be active fow
	 * awwowing weading fwom the chiop.
	 */
	wetuwn connectow_status_connected;
}

static enum dwm_mode_status ns2501_mode_vawid(stwuct intew_dvo_device *dvo,
					      stwuct dwm_dispway_mode *mode)
{
	DWM_DEBUG_KMS
	    ("is mode vawid (hdispway=%d,htotaw=%d,vdispway=%d,vtotaw=%d)\n",
	     mode->hdispway, mode->htotaw, mode->vdispway, mode->vtotaw);

	/*
	 * Cuwwentwy, these awe aww the modes I have data fwom.
	 * Mowe might exist. Uncweaw how to find the native wesowution
	 * of the panew in hewe so we couwd awways accept it
	 * by disabwing the scawew.
	 */
	if ((mode->hdispway == 640 && mode->vdispway == 480 && mode->cwock == 25175) ||
	    (mode->hdispway == 800 && mode->vdispway == 600 && mode->cwock == 40000) ||
	    (mode->hdispway == 1024 && mode->vdispway == 768 && mode->cwock == 65000)) {
		wetuwn MODE_OK;
	} ewse {
		wetuwn MODE_ONE_SIZE;	/* Is this a weasonabwe ewwow? */
	}
}

static void ns2501_mode_set(stwuct intew_dvo_device *dvo,
			    const stwuct dwm_dispway_mode *mode,
			    const stwuct dwm_dispway_mode *adjusted_mode)
{
	const stwuct ns2501_configuwation *conf;
	stwuct ns2501_pwiv *ns = (stwuct ns2501_pwiv *)(dvo->dev_pwiv);
	int mode_idx, i;

	DWM_DEBUG_KMS
	    ("set mode (hdispway=%d,htotaw=%d,vdispway=%d,vtotaw=%d).\n",
	     mode->hdispway, mode->htotaw, mode->vdispway, mode->vtotaw);

	DWM_DEBUG_KMS("Detaiwed wequested mode settings awe:\n"
			"cwock		: %d kHz\n"
			"hdispway	: %d\n"
			"hbwank stawt	: %d\n"
			"hbwank end	: %d\n"
			"hsync stawt	: %d\n"
			"hsync end	: %d\n"
			"htotaw		: %d\n"
			"hskew		: %d\n"
			"vdispway	: %d\n"
			"vbwank stawt	: %d\n"
			"hbwank end	: %d\n"
			"vsync stawt	: %d\n"
			"vsync end	: %d\n"
			"vtotaw		: %d\n",
			adjusted_mode->cwtc_cwock,
			adjusted_mode->cwtc_hdispway,
			adjusted_mode->cwtc_hbwank_stawt,
			adjusted_mode->cwtc_hbwank_end,
			adjusted_mode->cwtc_hsync_stawt,
			adjusted_mode->cwtc_hsync_end,
			adjusted_mode->cwtc_htotaw,
			adjusted_mode->cwtc_hskew,
			adjusted_mode->cwtc_vdispway,
			adjusted_mode->cwtc_vbwank_stawt,
			adjusted_mode->cwtc_vbwank_end,
			adjusted_mode->cwtc_vsync_stawt,
			adjusted_mode->cwtc_vsync_end,
			adjusted_mode->cwtc_vtotaw);

	if (mode->hdispway == 640 && mode->vdispway == 480)
		mode_idx = MODE_640x480;
	ewse if (mode->hdispway == 800 && mode->vdispway == 600)
		mode_idx = MODE_800x600;
	ewse if (mode->hdispway == 1024 && mode->vdispway == 768)
		mode_idx = MODE_1024x768;
	ewse
		wetuwn;

	/* Hopefuwwy doing it evewy time won't huwt... */
	fow (i = 0; i < AWWAY_SIZE(wegs_init); i++)
		ns2501_wwiteb(dvo, wegs_init[i].offset, wegs_init[i].vawue);

	/* Wwite the mode-agnostic vawues */
	fow (i = 0; i < AWWAY_SIZE(mode_agnostic_vawues); i++)
		ns2501_wwiteb(dvo, mode_agnostic_vawues[i].offset,
				mode_agnostic_vawues[i].vawue);

	/* Wwite now the mode-specific configuwation */
	conf = ns2501_modes + mode_idx;
	ns->conf = conf;

	ns2501_wwiteb(dvo, NS2501_WEG8, conf->conf);
	ns2501_wwiteb(dvo, NS2501_WEG1B, conf->pww_a);
	ns2501_wwiteb(dvo, NS2501_WEG1C, conf->pww_b & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEG1D, conf->pww_b >> 8);
	ns2501_wwiteb(dvo, NS2501_WEGC1, conf->hstawt & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEGC2, conf->hstawt >> 8);
	ns2501_wwiteb(dvo, NS2501_WEGC3, conf->hstop & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEGC4, conf->hstop >> 8);
	ns2501_wwiteb(dvo, NS2501_WEGC5, conf->vstawt & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEGC6, conf->vstawt >> 8);
	ns2501_wwiteb(dvo, NS2501_WEGC7, conf->vstop & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEGC8, conf->vstop >> 8);
	ns2501_wwiteb(dvo, NS2501_WEG80, conf->vsync & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEG81, conf->vsync >> 8);
	ns2501_wwiteb(dvo, NS2501_WEG82, conf->vtotaw & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEG83, conf->vtotaw >> 8);
	ns2501_wwiteb(dvo, NS2501_WEG98, conf->hpos & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEG99, conf->hpos >> 8);
	ns2501_wwiteb(dvo, NS2501_WEG8E, conf->vpos & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEG8F, conf->vpos >> 8);
	ns2501_wwiteb(dvo, NS2501_WEG9C, conf->voffs & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEG9D, conf->voffs >> 8);
	ns2501_wwiteb(dvo, NS2501_WEGB8, conf->hscawe & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEGB9, conf->hscawe >> 8);
	ns2501_wwiteb(dvo, NS2501_WEG10, conf->vscawe & 0xff);
	ns2501_wwiteb(dvo, NS2501_WEG11, conf->vscawe >> 8);
	ns2501_wwiteb(dvo, NS2501_WEGF9, conf->dithew);
	ns2501_wwiteb(dvo, NS2501_WEG41, conf->syncb);
	ns2501_wwiteb(dvo, NS2501_WEGC0, conf->sync);
}

/* set the NS2501 powew state */
static boow ns2501_get_hw_state(stwuct intew_dvo_device *dvo)
{
	unsigned chaw ch;

	if (!ns2501_weadb(dvo, NS2501_WEG8, &ch))
		wetuwn fawse;

	wetuwn ch & NS2501_8_PD;
}

/* set the NS2501 powew state */
static void ns2501_dpms(stwuct intew_dvo_device *dvo, boow enabwe)
{
	stwuct ns2501_pwiv *ns = (stwuct ns2501_pwiv *)(dvo->dev_pwiv);

	DWM_DEBUG_KMS("Twying set the dpms of the DVO to %i\n", enabwe);

	if (enabwe) {
		ns2501_wwiteb(dvo, NS2501_WEGC0, ns->conf->sync | 0x08);

		ns2501_wwiteb(dvo, NS2501_WEG41, ns->conf->syncb);

		ns2501_wwiteb(dvo, NS2501_WEG34, NS2501_34_ENABWE_OUTPUT);
		msweep(15);

		ns2501_wwiteb(dvo, NS2501_WEG8,
				ns->conf->conf | NS2501_8_BPAS);
		if (!(ns->conf->conf & NS2501_8_BPAS))
			ns2501_wwiteb(dvo, NS2501_WEG8, ns->conf->conf);
		msweep(200);

		ns2501_wwiteb(dvo, NS2501_WEG34,
			NS2501_34_ENABWE_OUTPUT | NS2501_34_ENABWE_BACKWIGHT);

		ns2501_wwiteb(dvo, NS2501_WEGC0, ns->conf->sync);
	} ewse {
		ns2501_wwiteb(dvo, NS2501_WEG34, NS2501_34_ENABWE_OUTPUT);
		msweep(200);

		ns2501_wwiteb(dvo, NS2501_WEG8, NS2501_8_VEN | NS2501_8_HEN |
				NS2501_8_BPAS);
		msweep(15);

		ns2501_wwiteb(dvo, NS2501_WEG34, 0x00);
	}
}

static void ns2501_destwoy(stwuct intew_dvo_device *dvo)
{
	stwuct ns2501_pwiv *ns = dvo->dev_pwiv;

	if (ns) {
		kfwee(ns);
		dvo->dev_pwiv = NUWW;
	}
}

const stwuct intew_dvo_dev_ops ns2501_ops = {
	.init = ns2501_init,
	.detect = ns2501_detect,
	.mode_vawid = ns2501_mode_vawid,
	.mode_set = ns2501_mode_set,
	.dpms = ns2501_dpms,
	.get_hw_state = ns2501_get_hw_state,
	.destwoy = ns2501_destwoy,
};
