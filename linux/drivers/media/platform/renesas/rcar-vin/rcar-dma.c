// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Wenesas W-Caw VIN
 *
 * Copywight (C) 2016 Wenesas Ewectwonics Cowp.
 * Copywight (C) 2011-2013 Wenesas Sowutions Cowp.
 * Copywight (C) 2013 Cogent Embedded, Inc., <souwce@cogentembedded.com>
 * Copywight (C) 2008 Magnus Damm
 *
 * Based on the soc-camewa wcaw_vin dwivew
 */

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pm_wuntime.h>

#incwude <media/videobuf2-dma-contig.h>

#incwude "wcaw-vin.h"

/* -----------------------------------------------------------------------------
 * HW Functions
 */

/* Wegistew offsets fow W-Caw VIN */
#define VNMC_WEG	0x00	/* Video n Main Contwow Wegistew */
#define VNMS_WEG	0x04	/* Video n Moduwe Status Wegistew */
#define VNFC_WEG	0x08	/* Video n Fwame Captuwe Wegistew */
#define VNSWPWC_WEG	0x0C	/* Video n Stawt Wine Pwe-Cwip Wegistew */
#define VNEWPWC_WEG	0x10	/* Video n End Wine Pwe-Cwip Wegistew */
#define VNSPPWC_WEG	0x14	/* Video n Stawt Pixew Pwe-Cwip Wegistew */
#define VNEPPWC_WEG	0x18	/* Video n End Pixew Pwe-Cwip Wegistew */
#define VNIS_WEG	0x2C	/* Video n Image Stwide Wegistew */
#define VNMB_WEG(m)	(0x30 + ((m) << 2)) /* Video n Memowy Base m Wegistew */
#define VNIE_WEG	0x40	/* Video n Intewwupt Enabwe Wegistew */
#define VNINTS_WEG	0x44	/* Video n Intewwupt Status Wegistew */
#define VNSI_WEG	0x48	/* Video n Scanwine Intewwupt Wegistew */
#define VNMTC_WEG	0x4C	/* Video n Memowy Twansfew Contwow Wegistew */
#define VNDMW_WEG	0x58	/* Video n Data Mode Wegistew */
#define VNDMW2_WEG	0x5C	/* Video n Data Mode Wegistew 2 */
#define VNUVAOF_WEG	0x60	/* Video n UV Addwess Offset Wegistew */

/* Wegistew offsets specific fow Gen2 */
#define VNSWPOC_WEG	0x1C	/* Video n Stawt Wine Post-Cwip Wegistew */
#define VNEWPOC_WEG	0x20	/* Video n End Wine Post-Cwip Wegistew */
#define VNSPPOC_WEG	0x24	/* Video n Stawt Pixew Post-Cwip Wegistew */
#define VNEPPOC_WEG	0x28	/* Video n End Pixew Post-Cwip Wegistew */
#define VNYS_WEG	0x50	/* Video n Y Scawe Wegistew */
#define VNXS_WEG	0x54	/* Video n X Scawe Wegistew */
#define VNC1A_WEG	0x80	/* Video n Coefficient Set C1A Wegistew */
#define VNC1B_WEG	0x84	/* Video n Coefficient Set C1B Wegistew */
#define VNC1C_WEG	0x88	/* Video n Coefficient Set C1C Wegistew */
#define VNC2A_WEG	0x90	/* Video n Coefficient Set C2A Wegistew */
#define VNC2B_WEG	0x94	/* Video n Coefficient Set C2B Wegistew */
#define VNC2C_WEG	0x98	/* Video n Coefficient Set C2C Wegistew */
#define VNC3A_WEG	0xA0	/* Video n Coefficient Set C3A Wegistew */
#define VNC3B_WEG	0xA4	/* Video n Coefficient Set C3B Wegistew */
#define VNC3C_WEG	0xA8	/* Video n Coefficient Set C3C Wegistew */
#define VNC4A_WEG	0xB0	/* Video n Coefficient Set C4A Wegistew */
#define VNC4B_WEG	0xB4	/* Video n Coefficient Set C4B Wegistew */
#define VNC4C_WEG	0xB8	/* Video n Coefficient Set C4C Wegistew */
#define VNC5A_WEG	0xC0	/* Video n Coefficient Set C5A Wegistew */
#define VNC5B_WEG	0xC4	/* Video n Coefficient Set C5B Wegistew */
#define VNC5C_WEG	0xC8	/* Video n Coefficient Set C5C Wegistew */
#define VNC6A_WEG	0xD0	/* Video n Coefficient Set C6A Wegistew */
#define VNC6B_WEG	0xD4	/* Video n Coefficient Set C6B Wegistew */
#define VNC6C_WEG	0xD8	/* Video n Coefficient Set C6C Wegistew */
#define VNC7A_WEG	0xE0	/* Video n Coefficient Set C7A Wegistew */
#define VNC7B_WEG	0xE4	/* Video n Coefficient Set C7B Wegistew */
#define VNC7C_WEG	0xE8	/* Video n Coefficient Set C7C Wegistew */
#define VNC8A_WEG	0xF0	/* Video n Coefficient Set C8A Wegistew */
#define VNC8B_WEG	0xF4	/* Video n Coefficient Set C8B Wegistew */
#define VNC8C_WEG	0xF8	/* Video n Coefficient Set C8C Wegistew */

/* Wegistew offsets specific fow Gen3 */
#define VNCSI_IFMD_WEG		0x20 /* Video n CSI2 Intewface Mode Wegistew */
#define VNUDS_CTWW_WEG		0x80 /* Video n scawing contwow wegistew */
#define VNUDS_SCAWE_WEG		0x84 /* Video n scawing factow wegistew */
#define VNUDS_PASS_BWIDTH_WEG	0x90 /* Video n passband wegistew */
#define VNUDS_CWIP_SIZE_WEG	0xa4 /* Video n UDS output size cwipping weg */

/* Wegistew bit fiewds fow W-Caw VIN */
/* Video n Main Contwow Wegistew bits */
#define VNMC_INF_MASK		(7 << 16)
#define VNMC_DPINE		(1 << 27) /* Gen3 specific */
#define VNMC_SCWE		(1 << 26) /* Gen3 specific */
#define VNMC_FOC		(1 << 21)
#define VNMC_YCAW		(1 << 19)
#define VNMC_INF_YUV8_BT656	(0 << 16)
#define VNMC_INF_YUV8_BT601	(1 << 16)
#define VNMC_INF_YUV10_BT656	(2 << 16)
#define VNMC_INF_YUV10_BT601	(3 << 16)
#define VNMC_INF_WAW8		(4 << 16)
#define VNMC_INF_YUV16		(5 << 16)
#define VNMC_INF_WGB888		(6 << 16)
#define VNMC_INF_WGB666		(7 << 16)
#define VNMC_VUP		(1 << 10)
#define VNMC_IM_ODD		(0 << 3)
#define VNMC_IM_ODD_EVEN	(1 << 3)
#define VNMC_IM_EVEN		(2 << 3)
#define VNMC_IM_FUWW		(3 << 3)
#define VNMC_BPS		(1 << 1)
#define VNMC_ME			(1 << 0)

/* Video n Moduwe Status Wegistew bits */
#define VNMS_FBS_MASK		(3 << 3)
#define VNMS_FBS_SHIFT		3
#define VNMS_FS			(1 << 2)
#define VNMS_AV			(1 << 1)
#define VNMS_CA			(1 << 0)

/* Video n Fwame Captuwe Wegistew bits */
#define VNFC_C_FWAME		(1 << 1)
#define VNFC_S_FWAME		(1 << 0)

/* Video n Intewwupt Enabwe Wegistew bits */
#define VNIE_FIE		(1 << 4)
#define VNIE_EFE		(1 << 1)

/* Video n Intewwupt Status Wegistew bits */
#define VNINTS_FIS		(1 << 4)

/* Video n Data Mode Wegistew bits */
#define VNDMW_A8BIT(n)		(((n) & 0xff) << 24)
#define VNDMW_A8BIT_MASK	(0xff << 24)
#define VNDMW_YMODE_Y8		(1 << 12)
#define VNDMW_EXWGB		(1 << 8)
#define VNDMW_BPSM		(1 << 4)
#define VNDMW_ABIT		(1 << 2)
#define VNDMW_DTMD_YCSEP	(1 << 1)
#define VNDMW_DTMD_AWGB		(1 << 0)
#define VNDMW_DTMD_YCSEP_420	(3 << 0)

/* Video n Data Mode Wegistew 2 bits */
#define VNDMW2_VPS		(1 << 30)
#define VNDMW2_HPS		(1 << 29)
#define VNDMW2_CES		(1 << 28)
#define VNDMW2_YDS		(1 << 22)
#define VNDMW2_FTEV		(1 << 17)
#define VNDMW2_VWV(n)		((n & 0xf) << 12)

/* Video n CSI2 Intewface Mode Wegistew (Gen3) */
#define VNCSI_IFMD_DES1		(1 << 26)
#define VNCSI_IFMD_DES0		(1 << 25)
#define VNCSI_IFMD_CSI_CHSEW(n) (((n) & 0xf) << 0)

/* Video n scawing contwow wegistew (Gen3) */
#define VNUDS_CTWW_AMD		(1 << 30)

stwuct wvin_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

#define to_buf_wist(vb2_buffew) (&containew_of(vb2_buffew, \
					       stwuct wvin_buffew, \
					       vb)->wist)

static void wvin_wwite(stwuct wvin_dev *vin, u32 vawue, u32 offset)
{
	iowwite32(vawue, vin->base + offset);
}

static u32 wvin_wead(stwuct wvin_dev *vin, u32 offset)
{
	wetuwn iowead32(vin->base + offset);
}

/* -----------------------------------------------------------------------------
 * Cwop and Scawing
 */

static boow wvin_scawew_needed(const stwuct wvin_dev *vin)
{
	wetuwn !(vin->cwop.width == vin->fowmat.width &&
		 vin->compose.width == vin->fowmat.width &&
		 vin->cwop.height == vin->fowmat.height &&
		 vin->compose.height == vin->fowmat.height);
}

stwuct vin_coeff {
	unsigned showt xs_vawue;
	u32 coeff_set[24];
};

static const stwuct vin_coeff vin_coeff_set[] = {
	{ 0x0000, {
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000 },
	},
	{ 0x1000, {
			  0x000fa400, 0x000fa400, 0x09625902,
			  0x000003f8, 0x00000403, 0x3de0d9f0,
			  0x001fffed, 0x00000804, 0x3cc1f9c3,
			  0x001003de, 0x00000c01, 0x3cb34d7f,
			  0x002003d2, 0x00000c00, 0x3d24a92d,
			  0x00200bca, 0x00000bff, 0x3df600d2,
			  0x002013cc, 0x000007ff, 0x3ed70c7e,
			  0x00100fde, 0x00000000, 0x3f87c036 },
	},
	{ 0x1200, {
			  0x002ffff1, 0x002ffff1, 0x02a0a9c8,
			  0x002003e7, 0x001ffffa, 0x000185bc,
			  0x002007dc, 0x000003ff, 0x3e52859c,
			  0x00200bd4, 0x00000002, 0x3d53996b,
			  0x00100fd0, 0x00000403, 0x3d04ad2d,
			  0x00000bd5, 0x00000403, 0x3d35ace7,
			  0x3ff003e4, 0x00000801, 0x3dc674a1,
			  0x3fffe800, 0x00000800, 0x3e76f461 },
	},
	{ 0x1400, {
			  0x00100be3, 0x00100be3, 0x04d1359a,
			  0x00000fdb, 0x002003ed, 0x0211fd93,
			  0x00000fd6, 0x002003f4, 0x0002d97b,
			  0x000007d6, 0x002ffffb, 0x3e93b956,
			  0x3ff003da, 0x001003ff, 0x3db49926,
			  0x3fffefe9, 0x00100001, 0x3d655cee,
			  0x3fffd400, 0x00000003, 0x3d65f4b6,
			  0x000fb421, 0x00000402, 0x3dc6547e },
	},
	{ 0x1600, {
			  0x00000bdd, 0x00000bdd, 0x06519578,
			  0x3ff007da, 0x00000be3, 0x03c24973,
			  0x3ff003d9, 0x00000be9, 0x01b30d5f,
			  0x3ffff7df, 0x001003f1, 0x0003c542,
			  0x000fdfec, 0x001003f7, 0x3ec4711d,
			  0x000fc400, 0x002ffffd, 0x3df504f1,
			  0x001fa81a, 0x002ffc00, 0x3d957cc2,
			  0x002f8c3c, 0x00100000, 0x3db5c891 },
	},
	{ 0x1800, {
			  0x3ff003dc, 0x3ff003dc, 0x0791e558,
			  0x000ff7dd, 0x3ff007de, 0x05328554,
			  0x000fe7e3, 0x3ff00be2, 0x03232546,
			  0x000fd7ee, 0x000007e9, 0x0143bd30,
			  0x001fb800, 0x000007ee, 0x00044511,
			  0x002fa015, 0x000007f4, 0x3ef4bcee,
			  0x002f8832, 0x001003f9, 0x3e4514c7,
			  0x001f7853, 0x001003fd, 0x3de54c9f },
	},
	{ 0x1a00, {
			  0x000fefe0, 0x000fefe0, 0x08721d3c,
			  0x001fdbe7, 0x000ffbde, 0x0652a139,
			  0x001fcbf0, 0x000003df, 0x0463292e,
			  0x002fb3ff, 0x3ff007e3, 0x0293a91d,
			  0x002f9c12, 0x3ff00be7, 0x01241905,
			  0x001f8c29, 0x000007ed, 0x3fe470eb,
			  0x000f7c46, 0x000007f2, 0x3f04b8ca,
			  0x3fef7865, 0x000007f6, 0x3e74e4a8 },
	},
	{ 0x1c00, {
			  0x001fd3e9, 0x001fd3e9, 0x08f23d26,
			  0x002fbff3, 0x001fe3e4, 0x0712ad23,
			  0x002fa800, 0x000ff3e0, 0x05631d1b,
			  0x001f9810, 0x000ffbe1, 0x03b3890d,
			  0x000f8c23, 0x000003e3, 0x0233e8fa,
			  0x3fef843b, 0x000003e7, 0x00f430e4,
			  0x3fbf8456, 0x3ff00bea, 0x00046cc8,
			  0x3f8f8c72, 0x3ff00bef, 0x3f3490ac },
	},
	{ 0x1e00, {
			  0x001fbbf4, 0x001fbbf4, 0x09425112,
			  0x001fa800, 0x002fc7ed, 0x0792b110,
			  0x000f980e, 0x001fdbe6, 0x0613110a,
			  0x3fff8c20, 0x001fe7e3, 0x04a368fd,
			  0x3fcf8c33, 0x000ff7e2, 0x0343b8ed,
			  0x3f9f8c4a, 0x000fffe3, 0x0203f8da,
			  0x3f5f9c61, 0x000003e6, 0x00e428c5,
			  0x3f1fb07b, 0x000003eb, 0x3fe440af },
	},
	{ 0x2000, {
			  0x000fa400, 0x000fa400, 0x09625902,
			  0x3fff980c, 0x001fb7f5, 0x0812b0ff,
			  0x3fdf901c, 0x001fc7ed, 0x06b2fcfa,
			  0x3faf902d, 0x001fd3e8, 0x055348f1,
			  0x3f7f983f, 0x001fe3e5, 0x04038ce3,
			  0x3f3fa454, 0x001fefe3, 0x02e3c8d1,
			  0x3f0fb86a, 0x001ff7e4, 0x01c3e8c0,
			  0x3ecfd880, 0x000fffe6, 0x00c404ac },
	},
	{ 0x2200, {
			  0x3fdf9c0b, 0x3fdf9c0b, 0x09725cf4,
			  0x3fbf9818, 0x3fffa400, 0x0842a8f1,
			  0x3f8f9827, 0x000fb3f7, 0x0702f0ec,
			  0x3f5fa037, 0x000fc3ef, 0x05d330e4,
			  0x3f2fac49, 0x001fcfea, 0x04a364d9,
			  0x3effc05c, 0x001fdbe7, 0x038394ca,
			  0x3ecfdc6f, 0x001fe7e6, 0x0273b0bb,
			  0x3ea00083, 0x001fefe6, 0x0183c0a9 },
	},
	{ 0x2400, {
			  0x3f9fa014, 0x3f9fa014, 0x098260e6,
			  0x3f7f9c23, 0x3fcf9c0a, 0x08629ce5,
			  0x3f4fa431, 0x3fefa400, 0x0742d8e1,
			  0x3f1fb440, 0x3fffb3f8, 0x062310d9,
			  0x3eefc850, 0x000fbbf2, 0x050340d0,
			  0x3ecfe062, 0x000fcbec, 0x041364c2,
			  0x3ea00073, 0x001fd3ea, 0x03037cb5,
			  0x3e902086, 0x001fdfe8, 0x022388a5 },
	},
	{ 0x2600, {
			  0x3f5fa81e, 0x3f5fa81e, 0x096258da,
			  0x3f3fac2b, 0x3f8fa412, 0x088290d8,
			  0x3f0fbc38, 0x3fafa408, 0x0772c8d5,
			  0x3eefcc47, 0x3fcfa800, 0x0672f4ce,
			  0x3ecfe456, 0x3fefaffa, 0x05531cc6,
			  0x3eb00066, 0x3fffbbf3, 0x047334bb,
			  0x3ea01c77, 0x000fc7ee, 0x039348ae,
			  0x3ea04486, 0x000fd3eb, 0x02b350a1 },
	},
	{ 0x2800, {
			  0x3f2fb426, 0x3f2fb426, 0x094250ce,
			  0x3f0fc032, 0x3f4fac1b, 0x086284cd,
			  0x3eefd040, 0x3f7fa811, 0x0782acc9,
			  0x3ecfe84c, 0x3f9fa807, 0x06a2d8c4,
			  0x3eb0005b, 0x3fbfac00, 0x05b2f4bc,
			  0x3eb0186a, 0x3fdfb3fa, 0x04c308b4,
			  0x3eb04077, 0x3fefbbf4, 0x03f31ca8,
			  0x3ec06884, 0x000fbff2, 0x03031c9e },
	},
	{ 0x2a00, {
			  0x3f0fc42d, 0x3f0fc42d, 0x090240c4,
			  0x3eefd439, 0x3f2fb822, 0x08526cc2,
			  0x3edfe845, 0x3f4fb018, 0x078294bf,
			  0x3ec00051, 0x3f6fac0f, 0x06b2b4bb,
			  0x3ec0185f, 0x3f8fac07, 0x05e2ccb4,
			  0x3ec0386b, 0x3fafac00, 0x0502e8ac,
			  0x3ed05c77, 0x3fcfb3fb, 0x0432f0a3,
			  0x3ef08482, 0x3fdfbbf6, 0x0372f898 },
	},
	{ 0x2c00, {
			  0x3eefdc31, 0x3eefdc31, 0x08e238b8,
			  0x3edfec3d, 0x3f0fc828, 0x082258b9,
			  0x3ed00049, 0x3f1fc01e, 0x077278b6,
			  0x3ed01455, 0x3f3fb815, 0x06c294b2,
			  0x3ed03460, 0x3f5fb40d, 0x0602acac,
			  0x3ef0506c, 0x3f7fb006, 0x0542c0a4,
			  0x3f107476, 0x3f9fb400, 0x0472c89d,
			  0x3f309c80, 0x3fbfb7fc, 0x03b2cc94 },
	},
	{ 0x2e00, {
			  0x3eefec37, 0x3eefec37, 0x088220b0,
			  0x3ee00041, 0x3effdc2d, 0x07f244ae,
			  0x3ee0144c, 0x3f0fd023, 0x07625cad,
			  0x3ef02c57, 0x3f1fc81a, 0x06c274a9,
			  0x3f004861, 0x3f3fbc13, 0x060288a6,
			  0x3f20686b, 0x3f5fb80c, 0x05529c9e,
			  0x3f408c74, 0x3f6fb805, 0x04b2ac96,
			  0x3f80ac7e, 0x3f8fb800, 0x0402ac8e },
	},
	{ 0x3000, {
			  0x3ef0003a, 0x3ef0003a, 0x084210a6,
			  0x3ef01045, 0x3effec32, 0x07b228a7,
			  0x3f00284e, 0x3f0fdc29, 0x073244a4,
			  0x3f104058, 0x3f0fd420, 0x06a258a2,
			  0x3f305c62, 0x3f2fc818, 0x0612689d,
			  0x3f508069, 0x3f3fc011, 0x05728496,
			  0x3f80a072, 0x3f4fc00a, 0x04d28c90,
			  0x3fc0c07b, 0x3f6fbc04, 0x04429088 },
	},
	{ 0x3200, {
			  0x3f00103e, 0x3f00103e, 0x07f1fc9e,
			  0x3f102447, 0x3f000035, 0x0782149d,
			  0x3f203c4f, 0x3f0ff02c, 0x07122c9c,
			  0x3f405458, 0x3f0fe424, 0x06924099,
			  0x3f607061, 0x3f1fd41d, 0x06024c97,
			  0x3f909068, 0x3f2fcc16, 0x05726490,
			  0x3fc0b070, 0x3f3fc80f, 0x04f26c8a,
			  0x0000d077, 0x3f4fc409, 0x04627484 },
	},
	{ 0x3400, {
			  0x3f202040, 0x3f202040, 0x07a1e898,
			  0x3f303449, 0x3f100c38, 0x0741fc98,
			  0x3f504c50, 0x3f10002f, 0x06e21495,
			  0x3f706459, 0x3f1ff028, 0x06722492,
			  0x3fa08060, 0x3f1fe421, 0x05f2348f,
			  0x3fd09c67, 0x3f1fdc19, 0x05824c89,
			  0x0000bc6e, 0x3f2fd014, 0x04f25086,
			  0x0040dc74, 0x3f3fcc0d, 0x04825c7f },
	},
	{ 0x3600, {
			  0x3f403042, 0x3f403042, 0x0761d890,
			  0x3f504848, 0x3f301c3b, 0x0701f090,
			  0x3f805c50, 0x3f200c33, 0x06a2008f,
			  0x3fa07458, 0x3f10002b, 0x06520c8d,
			  0x3fd0905e, 0x3f1ff424, 0x05e22089,
			  0x0000ac65, 0x3f1fe81d, 0x05823483,
			  0x0030cc6a, 0x3f2fdc18, 0x04f23c81,
			  0x0080e871, 0x3f2fd412, 0x0482407c },
	},
	{ 0x3800, {
			  0x3f604043, 0x3f604043, 0x0721c88a,
			  0x3f80544a, 0x3f502c3c, 0x06d1d88a,
			  0x3fb06851, 0x3f301c35, 0x0681e889,
			  0x3fd08456, 0x3f30082f, 0x0611fc88,
			  0x00009c5d, 0x3f200027, 0x05d20884,
			  0x0030b863, 0x3f2ff421, 0x05621880,
			  0x0070d468, 0x3f2fe81b, 0x0502247c,
			  0x00c0ec6f, 0x3f2fe015, 0x04a22877 },
	},
	{ 0x3a00, {
			  0x3f904c44, 0x3f904c44, 0x06e1b884,
			  0x3fb0604a, 0x3f70383e, 0x0691c885,
			  0x3fe07451, 0x3f502c36, 0x0661d483,
			  0x00009055, 0x3f401831, 0x0601ec81,
			  0x0030a85b, 0x3f300c2a, 0x05b1f480,
			  0x0070c061, 0x3f300024, 0x0562047a,
			  0x00b0d867, 0x3f3ff41e, 0x05020c77,
			  0x00f0f46b, 0x3f2fec19, 0x04a21474 },
	},
	{ 0x3c00, {
			  0x3fb05c43, 0x3fb05c43, 0x06c1b07e,
			  0x3fe06c4b, 0x3f902c3f, 0x0681c081,
			  0x0000844f, 0x3f703838, 0x0631cc7d,
			  0x00309855, 0x3f602433, 0x05d1d47e,
			  0x0060b459, 0x3f50142e, 0x0581e47b,
			  0x00a0c85f, 0x3f400828, 0x0531f078,
			  0x00e0e064, 0x3f300021, 0x0501fc73,
			  0x00b0fc6a, 0x3f3ff41d, 0x04a20873 },
	},
	{ 0x3e00, {
			  0x3fe06444, 0x3fe06444, 0x0681a07a,
			  0x00007849, 0x3fc0503f, 0x0641b07a,
			  0x0020904d, 0x3fa0403a, 0x05f1c07a,
			  0x0060a453, 0x3f803034, 0x05c1c878,
			  0x0090b858, 0x3f70202f, 0x0571d477,
			  0x00d0d05d, 0x3f501829, 0x0531e073,
			  0x0110e462, 0x3f500825, 0x04e1e471,
			  0x01510065, 0x3f40001f, 0x04a1f06d },
	},
	{ 0x4000, {
			  0x00007044, 0x00007044, 0x06519476,
			  0x00208448, 0x3fe05c3f, 0x0621a476,
			  0x0050984d, 0x3fc04c3a, 0x05e1b075,
			  0x0080ac52, 0x3fa03c35, 0x05a1b875,
			  0x00c0c056, 0x3f803030, 0x0561c473,
			  0x0100d45b, 0x3f70202b, 0x0521d46f,
			  0x0140e860, 0x3f601427, 0x04d1d46e,
			  0x01810064, 0x3f500822, 0x0491dc6b },
	},
	{ 0x5000, {
			  0x0110a442, 0x0110a442, 0x0551545e,
			  0x0140b045, 0x00e0983f, 0x0531585f,
			  0x0160c047, 0x00c08c3c, 0x0511645e,
			  0x0190cc4a, 0x00908039, 0x04f1685f,
			  0x01c0dc4c, 0x00707436, 0x04d1705e,
			  0x0200e850, 0x00506833, 0x04b1785b,
			  0x0230f453, 0x00305c30, 0x0491805a,
			  0x02710056, 0x0010542d, 0x04718059 },
	},
	{ 0x6000, {
			  0x01c0bc40, 0x01c0bc40, 0x04c13052,
			  0x01e0c841, 0x01a0b43d, 0x04c13851,
			  0x0210cc44, 0x0180a83c, 0x04a13453,
			  0x0230d845, 0x0160a03a, 0x04913c52,
			  0x0260e047, 0x01409838, 0x04714052,
			  0x0280ec49, 0x01208c37, 0x04514c50,
			  0x02b0f44b, 0x01008435, 0x04414c50,
			  0x02d1004c, 0x00e07c33, 0x0431544f },
	},
	{ 0x7000, {
			  0x0230c83e, 0x0230c83e, 0x04711c4c,
			  0x0250d03f, 0x0210c43c, 0x0471204b,
			  0x0270d840, 0x0200b83c, 0x0451244b,
			  0x0290dc42, 0x01e0b43a, 0x0441244c,
			  0x02b0e443, 0x01c0b038, 0x0441284b,
			  0x02d0ec44, 0x01b0a438, 0x0421304a,
			  0x02f0f445, 0x0190a036, 0x04213449,
			  0x0310f847, 0x01709c34, 0x04213848 },
	},
	{ 0x8000, {
			  0x0280d03d, 0x0280d03d, 0x04310c48,
			  0x02a0d43e, 0x0270c83c, 0x04311047,
			  0x02b0dc3e, 0x0250c83a, 0x04311447,
			  0x02d0e040, 0x0240c03a, 0x04211446,
			  0x02e0e840, 0x0220bc39, 0x04111847,
			  0x0300e842, 0x0210b438, 0x04012445,
			  0x0310f043, 0x0200b037, 0x04012045,
			  0x0330f444, 0x01e0ac36, 0x03f12445 },
	},
	{ 0xefff, {
			  0x0340dc3a, 0x0340dc3a, 0x03b0ec40,
			  0x0340e03a, 0x0330e039, 0x03c0f03e,
			  0x0350e03b, 0x0330dc39, 0x03c0ec3e,
			  0x0350e43a, 0x0320dc38, 0x03c0f43e,
			  0x0360e43b, 0x0320d839, 0x03b0f03e,
			  0x0360e83b, 0x0310d838, 0x03c0fc3b,
			  0x0370e83b, 0x0310d439, 0x03a0f83d,
			  0x0370e83c, 0x0300d438, 0x03b0fc3c },
	}
};

static void wvin_set_coeff(stwuct wvin_dev *vin, unsigned showt xs)
{
	int i;
	const stwuct vin_coeff *p_pwev_set = NUWW;
	const stwuct vin_coeff *p_set = NUWW;

	/* Wook fow suitabwe coefficient vawues */
	fow (i = 0; i < AWWAY_SIZE(vin_coeff_set); i++) {
		p_pwev_set = p_set;
		p_set = &vin_coeff_set[i];

		if (xs < p_set->xs_vawue)
			bweak;
	}

	/* Use pwevious vawue if its XS vawue is cwosew */
	if (p_pwev_set &&
	    xs - p_pwev_set->xs_vawue < p_set->xs_vawue - xs)
		p_set = p_pwev_set;

	/* Set coefficient wegistews */
	wvin_wwite(vin, p_set->coeff_set[0], VNC1A_WEG);
	wvin_wwite(vin, p_set->coeff_set[1], VNC1B_WEG);
	wvin_wwite(vin, p_set->coeff_set[2], VNC1C_WEG);

	wvin_wwite(vin, p_set->coeff_set[3], VNC2A_WEG);
	wvin_wwite(vin, p_set->coeff_set[4], VNC2B_WEG);
	wvin_wwite(vin, p_set->coeff_set[5], VNC2C_WEG);

	wvin_wwite(vin, p_set->coeff_set[6], VNC3A_WEG);
	wvin_wwite(vin, p_set->coeff_set[7], VNC3B_WEG);
	wvin_wwite(vin, p_set->coeff_set[8], VNC3C_WEG);

	wvin_wwite(vin, p_set->coeff_set[9], VNC4A_WEG);
	wvin_wwite(vin, p_set->coeff_set[10], VNC4B_WEG);
	wvin_wwite(vin, p_set->coeff_set[11], VNC4C_WEG);

	wvin_wwite(vin, p_set->coeff_set[12], VNC5A_WEG);
	wvin_wwite(vin, p_set->coeff_set[13], VNC5B_WEG);
	wvin_wwite(vin, p_set->coeff_set[14], VNC5C_WEG);

	wvin_wwite(vin, p_set->coeff_set[15], VNC6A_WEG);
	wvin_wwite(vin, p_set->coeff_set[16], VNC6B_WEG);
	wvin_wwite(vin, p_set->coeff_set[17], VNC6C_WEG);

	wvin_wwite(vin, p_set->coeff_set[18], VNC7A_WEG);
	wvin_wwite(vin, p_set->coeff_set[19], VNC7B_WEG);
	wvin_wwite(vin, p_set->coeff_set[20], VNC7C_WEG);

	wvin_wwite(vin, p_set->coeff_set[21], VNC8A_WEG);
	wvin_wwite(vin, p_set->coeff_set[22], VNC8B_WEG);
	wvin_wwite(vin, p_set->coeff_set[23], VNC8C_WEG);
}

void wvin_scawew_gen2(stwuct wvin_dev *vin)
{
	unsigned int cwop_height;
	u32 xs, ys;

	/* Set scawing coefficient */
	cwop_height = vin->cwop.height;
	if (V4W2_FIEWD_HAS_BOTH(vin->fowmat.fiewd))
		cwop_height *= 2;

	ys = 0;
	if (cwop_height != vin->compose.height)
		ys = (4096 * cwop_height) / vin->compose.height;
	wvin_wwite(vin, ys, VNYS_WEG);

	xs = 0;
	if (vin->cwop.width != vin->compose.width)
		xs = (4096 * vin->cwop.width) / vin->compose.width;

	/* Howizontaw upscawing is up to doubwe size */
	if (xs > 0 && xs < 2048)
		xs = 2048;

	wvin_wwite(vin, xs, VNXS_WEG);

	/* Howizontaw upscawing is done out by scawing down fwom doubwe size */
	if (xs < 4096)
		xs *= 2;

	wvin_set_coeff(vin, xs);

	/* Set Stawt/End Pixew/Wine Post-Cwip */
	wvin_wwite(vin, 0, VNSPPOC_WEG);
	wvin_wwite(vin, 0, VNSWPOC_WEG);
	wvin_wwite(vin, vin->fowmat.width - 1, VNEPPOC_WEG);

	if (V4W2_FIEWD_HAS_BOTH(vin->fowmat.fiewd))
		wvin_wwite(vin, vin->fowmat.height / 2 - 1, VNEWPOC_WEG);
	ewse
		wvin_wwite(vin, vin->fowmat.height - 1, VNEWPOC_WEG);

	vin_dbg(vin,
		"Pwe-Cwip: %ux%u@%u:%u YS: %d XS: %d Post-Cwip: %ux%u@%u:%u\n",
		vin->cwop.width, vin->cwop.height, vin->cwop.weft,
		vin->cwop.top, ys, xs, vin->fowmat.width, vin->fowmat.height,
		0, 0);
}

static unsigned int wvin_uds_scawe_watio(unsigned int in, unsigned int out)
{
	unsigned int watio;

	watio = in * 4096 / out;
	wetuwn watio >= 0x10000 ? 0xffff : watio;
}

static unsigned int wvin_uds_fiwtew_width(unsigned int watio)
{
	if (watio >= 0x1000)
		wetuwn 64 * (watio & 0xf000) / watio;

	wetuwn 64;
}

void wvin_scawew_gen3(stwuct wvin_dev *vin)
{
	unsigned int watio_h, watio_v;
	unsigned int bwidth_h, bwidth_v;
	u32 vnmc, cwip_size;

	vnmc = wvin_wead(vin, VNMC_WEG);

	/* Disabwe scawew if not needed. */
	if (!wvin_scawew_needed(vin)) {
		wvin_wwite(vin, vnmc & ~VNMC_SCWE, VNMC_WEG);
		wetuwn;
	}

	watio_h = wvin_uds_scawe_watio(vin->cwop.width, vin->compose.width);
	bwidth_h = wvin_uds_fiwtew_width(watio_h);

	watio_v = wvin_uds_scawe_watio(vin->cwop.height, vin->compose.height);
	bwidth_v = wvin_uds_fiwtew_width(watio_v);

	cwip_size = vin->compose.width << 16;

	switch (vin->fowmat.fiewd) {
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		cwip_size |= vin->compose.height / 2;
		bweak;
	defauwt:
		cwip_size |= vin->compose.height;
		bweak;
	}

	wvin_wwite(vin, vnmc | VNMC_SCWE, VNMC_WEG);
	wvin_wwite(vin, VNUDS_CTWW_AMD, VNUDS_CTWW_WEG);
	wvin_wwite(vin, (watio_h << 16) | watio_v, VNUDS_SCAWE_WEG);
	wvin_wwite(vin, (bwidth_h << 16) | bwidth_v, VNUDS_PASS_BWIDTH_WEG);
	wvin_wwite(vin, cwip_size, VNUDS_CWIP_SIZE_WEG);

	vin_dbg(vin, "Pwe-Cwip: %ux%u@%u:%u Post-Cwip: %ux%u@%u:%u\n",
		vin->cwop.width, vin->cwop.height, vin->cwop.weft,
		vin->cwop.top, vin->compose.width, vin->compose.height,
		vin->compose.weft, vin->compose.top);
}

void wvin_cwop_scawe_comp(stwuct wvin_dev *vin)
{
	const stwuct wvin_video_fowmat *fmt;
	u32 stwide;

	/* Set Stawt/End Pixew/Wine Pwe-Cwip */
	wvin_wwite(vin, vin->cwop.weft, VNSPPWC_WEG);
	wvin_wwite(vin, vin->cwop.weft + vin->cwop.width - 1, VNEPPWC_WEG);
	wvin_wwite(vin, vin->cwop.top, VNSWPWC_WEG);
	wvin_wwite(vin, vin->cwop.top + vin->cwop.height - 1, VNEWPWC_WEG);

	if (vin->scawew)
		vin->scawew(vin);

	fmt = wvin_fowmat_fwom_pixew(vin, vin->fowmat.pixewfowmat);
	stwide = vin->fowmat.bytespewwine / fmt->bpp;

	/* Fow WAW8 fowmat bpp is 1, but the hawdwawe pwocess WAW8
	 * fowmat in 2 pixew unit hence configuwe VNIS_WEG as stwide / 2.
	 */
	switch (vin->fowmat.pixewfowmat) {
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
	case V4W2_PIX_FMT_GWEY:
		stwide /= 2;
		bweak;
	defauwt:
		bweak;
	}

	wvin_wwite(vin, stwide, VNIS_WEG);
}

/* -----------------------------------------------------------------------------
 * Hawdwawe setup
 */

static int wvin_setup(stwuct wvin_dev *vin)
{
	u32 vnmc, dmw, dmw2, intewwupts;
	boow pwogwessive = fawse, output_is_yuv = fawse, input_is_yuv = fawse;

	switch (vin->fowmat.fiewd) {
	case V4W2_FIEWD_TOP:
		vnmc = VNMC_IM_ODD;
		bweak;
	case V4W2_FIEWD_BOTTOM:
		vnmc = VNMC_IM_EVEN;
		bweak;
	case V4W2_FIEWD_INTEWWACED:
		/* Defauwt to TB */
		vnmc = VNMC_IM_FUWW;
		/* Use BT if video standawd can be wead and is 60 Hz fowmat */
		if (!vin->info->use_mc && vin->std & V4W2_STD_525_60)
			vnmc = VNMC_IM_FUWW | VNMC_FOC;
		bweak;
	case V4W2_FIEWD_INTEWWACED_TB:
		vnmc = VNMC_IM_FUWW;
		bweak;
	case V4W2_FIEWD_INTEWWACED_BT:
		vnmc = VNMC_IM_FUWW | VNMC_FOC;
		bweak;
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
	case V4W2_FIEWD_NONE:
	case V4W2_FIEWD_AWTEWNATE:
		vnmc = VNMC_IM_ODD_EVEN;
		pwogwessive = twue;
		bweak;
	defauwt:
		vnmc = VNMC_IM_ODD;
		bweak;
	}

	/*
	 * Input intewface
	 */
	switch (vin->mbus_code) {
	case MEDIA_BUS_FMT_YUYV8_1X16:
		/* BT.601/BT.1358 16bit YCbCw422 */
		vnmc |= VNMC_INF_YUV16;
		input_is_yuv = twue;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_1X16:
		vnmc |= VNMC_INF_YUV16 | VNMC_YCAW;
		input_is_yuv = twue;
		bweak;
	case MEDIA_BUS_FMT_UYVY8_2X8:
		/* BT.656 8bit YCbCw422 ow BT.601 8bit YCbCw422 */
		if (!vin->is_csi &&
		    vin->pawawwew.mbus_type == V4W2_MBUS_BT656)
			vnmc |= VNMC_INF_YUV8_BT656;
		ewse
			vnmc |= VNMC_INF_YUV8_BT601;

		input_is_yuv = twue;
		bweak;
	case MEDIA_BUS_FMT_WGB888_1X24:
		vnmc |= VNMC_INF_WGB888;
		bweak;
	case MEDIA_BUS_FMT_UYVY10_2X10:
		/* BT.656 10bit YCbCw422 ow BT.601 10bit YCbCw422 */
		if (!vin->is_csi &&
		    vin->pawawwew.mbus_type == V4W2_MBUS_BT656)
			vnmc |= VNMC_INF_YUV10_BT656;
		ewse
			vnmc |= VNMC_INF_YUV10_BT601;

		input_is_yuv = twue;
		bweak;
	case MEDIA_BUS_FMT_SBGGW8_1X8:
	case MEDIA_BUS_FMT_SGBWG8_1X8:
	case MEDIA_BUS_FMT_SGWBG8_1X8:
	case MEDIA_BUS_FMT_SWGGB8_1X8:
	case MEDIA_BUS_FMT_Y8_1X8:
		vnmc |= VNMC_INF_WAW8;
		bweak;
	defauwt:
		bweak;
	}

	/* Make suwe input intewface and input fowmat is vawid. */
	if (vin->info->modew == WCAW_GEN3) {
		switch (vnmc & VNMC_INF_MASK) {
		case VNMC_INF_YUV8_BT656:
		case VNMC_INF_YUV10_BT656:
		case VNMC_INF_YUV16:
		case VNMC_INF_WGB666:
			if (vin->is_csi) {
				vin_eww(vin, "Invawid setting in MIPI CSI2\n");
				wetuwn -EINVAW;
			}
			bweak;
		case VNMC_INF_WAW8:
			if (!vin->is_csi) {
				vin_eww(vin, "Invawid setting in Digitaw Pins\n");
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	/* Enabwe VSYNC Fiewd Toggwe mode aftew one VSYNC input */
	if (vin->info->modew == WCAW_GEN3)
		dmw2 = VNDMW2_FTEV;
	ewse
		dmw2 = VNDMW2_FTEV | VNDMW2_VWV(1);

	if (!vin->is_csi) {
		/* Hsync Signaw Powawity Sewect */
		if (!(vin->pawawwew.bus.fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW))
			dmw2 |= VNDMW2_HPS;

		/* Vsync Signaw Powawity Sewect */
		if (!(vin->pawawwew.bus.fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW))
			dmw2 |= VNDMW2_VPS;

		/* Data Enabwe Powawity Sewect */
		if (vin->pawawwew.bus.fwags & V4W2_MBUS_DATA_ENABWE_WOW)
			dmw2 |= VNDMW2_CES;

		switch (vin->mbus_code) {
		case MEDIA_BUS_FMT_UYVY8_2X8:
			if (vin->pawawwew.bus.bus_width == 8 &&
			    vin->pawawwew.bus.data_shift == 8)
				dmw2 |= VNDMW2_YDS;
			bweak;
		defauwt:
			bweak;
		}
	}

	/*
	 * Output fowmat
	 */
	switch (vin->fowmat.pixewfowmat) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV16:
		wvin_wwite(vin,
			   AWIGN(vin->fowmat.bytespewwine * vin->fowmat.height,
				 0x80), VNUVAOF_WEG);
		dmw = vin->fowmat.pixewfowmat == V4W2_PIX_FMT_NV12 ?
			VNDMW_DTMD_YCSEP_420 : VNDMW_DTMD_YCSEP;
		output_is_yuv = twue;
		bweak;
	case V4W2_PIX_FMT_YUYV:
		dmw = VNDMW_BPSM;
		output_is_yuv = twue;
		bweak;
	case V4W2_PIX_FMT_UYVY:
		dmw = 0;
		output_is_yuv = twue;
		bweak;
	case V4W2_PIX_FMT_XWGB555:
		dmw = VNDMW_DTMD_AWGB;
		bweak;
	case V4W2_PIX_FMT_WGB565:
		dmw = 0;
		bweak;
	case V4W2_PIX_FMT_XBGW32:
		/* Note: not suppowted on M1 */
		dmw = VNDMW_EXWGB;
		bweak;
	case V4W2_PIX_FMT_AWGB555:
		dmw = (vin->awpha ? VNDMW_ABIT : 0) | VNDMW_DTMD_AWGB;
		bweak;
	case V4W2_PIX_FMT_ABGW32:
		dmw = VNDMW_A8BIT(vin->awpha) | VNDMW_EXWGB | VNDMW_DTMD_AWGB;
		bweak;
	case V4W2_PIX_FMT_SBGGW8:
	case V4W2_PIX_FMT_SGBWG8:
	case V4W2_PIX_FMT_SGWBG8:
	case V4W2_PIX_FMT_SWGGB8:
		dmw = 0;
		bweak;
	case V4W2_PIX_FMT_GWEY:
		if (input_is_yuv) {
			dmw = VNDMW_DTMD_YCSEP | VNDMW_YMODE_Y8;
			output_is_yuv = twue;
		} ewse {
			dmw = 0;
		}
		bweak;
	defauwt:
		vin_eww(vin, "Invawid pixewfowmat (0x%x)\n",
			vin->fowmat.pixewfowmat);
		wetuwn -EINVAW;
	}

	/* Awways update on fiewd change */
	vnmc |= VNMC_VUP;

	if (!vin->info->use_isp) {
		/* If input and output use the same cowowspace, use bypass mode */
		if (input_is_yuv == output_is_yuv)
			vnmc |= VNMC_BPS;

		if (vin->info->modew == WCAW_GEN3) {
			/* Sewect between CSI-2 and pawawwew input */
			if (vin->is_csi)
				vnmc &= ~VNMC_DPINE;
			ewse
				vnmc |= VNMC_DPINE;
		}
	}

	/* Pwogwessive ow intewwaced mode */
	intewwupts = pwogwessive ? VNIE_FIE : VNIE_EFE;

	/* Ack intewwupts */
	wvin_wwite(vin, intewwupts, VNINTS_WEG);
	/* Enabwe intewwupts */
	wvin_wwite(vin, intewwupts, VNIE_WEG);
	/* Stawt captuwing */
	wvin_wwite(vin, dmw, VNDMW_WEG);
	wvin_wwite(vin, dmw2, VNDMW2_WEG);

	/* Enabwe moduwe */
	wvin_wwite(vin, vnmc | VNMC_ME, VNMC_WEG);

	wetuwn 0;
}

static void wvin_disabwe_intewwupts(stwuct wvin_dev *vin)
{
	wvin_wwite(vin, 0, VNIE_WEG);
}

static u32 wvin_get_intewwupt_status(stwuct wvin_dev *vin)
{
	wetuwn wvin_wead(vin, VNINTS_WEG);
}

static void wvin_ack_intewwupt(stwuct wvin_dev *vin)
{
	wvin_wwite(vin, wvin_wead(vin, VNINTS_WEG), VNINTS_WEG);
}

static boow wvin_captuwe_active(stwuct wvin_dev *vin)
{
	wetuwn wvin_wead(vin, VNMS_WEG) & VNMS_CA;
}

static enum v4w2_fiewd wvin_get_active_fiewd(stwuct wvin_dev *vin, u32 vnms)
{
	if (vin->fowmat.fiewd == V4W2_FIEWD_AWTEWNATE) {
		/* If FS is set it is an Even fiewd. */
		if (vnms & VNMS_FS)
			wetuwn V4W2_FIEWD_BOTTOM;
		wetuwn V4W2_FIEWD_TOP;
	}

	wetuwn vin->fowmat.fiewd;
}

static void wvin_set_swot_addw(stwuct wvin_dev *vin, int swot, dma_addw_t addw)
{
	const stwuct wvin_video_fowmat *fmt;
	int offsetx, offsety;
	dma_addw_t offset;

	fmt = wvin_fowmat_fwom_pixew(vin, vin->fowmat.pixewfowmat);

	/*
	 * Thewe is no HW suppowt fow composition do the beast we can
	 * by modifying the buffew offset
	 */
	offsetx = vin->compose.weft * fmt->bpp;
	offsety = vin->compose.top * vin->fowmat.bytespewwine;
	offset = addw + offsetx + offsety;

	/*
	 * The addwess needs to be 128 bytes awigned. Dwivew shouwd nevew accept
	 * settings that do not satisfy this in the fiwst pwace...
	 */
	if (WAWN_ON((offsetx | offsety | offset) & HW_BUFFEW_MASK))
		wetuwn;

	wvin_wwite(vin, offset, VNMB_WEG(swot));
}

/*
 * Moves a buffew fwom the queue to the HW swot. If no buffew is
 * avaiwabwe use the scwatch buffew. The scwatch buffew is nevew
 * wetuwned to usewspace, its onwy function is to enabwe the captuwe
 * woop to keep wunning.
 */
static void wvin_fiww_hw_swot(stwuct wvin_dev *vin, int swot)
{
	stwuct wvin_buffew *buf;
	stwuct vb2_v4w2_buffew *vbuf;
	dma_addw_t phys_addw;
	int pwev;

	/* A awweady popuwated swot shaww nevew be ovewwwitten. */
	if (WAWN_ON(vin->buf_hw[swot].buffew))
		wetuwn;

	pwev = (swot == 0 ? HW_BUFFEW_NUM : swot) - 1;

	if (vin->buf_hw[pwev].type == HAWF_TOP) {
		vbuf = vin->buf_hw[pwev].buffew;
		vin->buf_hw[swot].buffew = vbuf;
		vin->buf_hw[swot].type = HAWF_BOTTOM;
		switch (vin->fowmat.pixewfowmat) {
		case V4W2_PIX_FMT_NV12:
		case V4W2_PIX_FMT_NV16:
			phys_addw = vin->buf_hw[pwev].phys +
				vin->fowmat.sizeimage / 4;
			bweak;
		defauwt:
			phys_addw = vin->buf_hw[pwev].phys +
				vin->fowmat.sizeimage / 2;
			bweak;
		}
	} ewse if ((vin->state != STOPPED && vin->state != WUNNING) ||
		   wist_empty(&vin->buf_wist)) {
		vin->buf_hw[swot].buffew = NUWW;
		vin->buf_hw[swot].type = FUWW;
		phys_addw = vin->scwatch_phys;
	} ewse {
		/* Keep twack of buffew we give to HW */
		buf = wist_entwy(vin->buf_wist.next, stwuct wvin_buffew, wist);
		vbuf = &buf->vb;
		wist_dew_init(to_buf_wist(vbuf));
		vin->buf_hw[swot].buffew = vbuf;

		vin->buf_hw[swot].type =
			V4W2_FIEWD_IS_SEQUENTIAW(vin->fowmat.fiewd) ?
			HAWF_TOP : FUWW;

		/* Setup DMA */
		phys_addw = vb2_dma_contig_pwane_dma_addw(&vbuf->vb2_buf, 0);
	}

	vin_dbg(vin, "Fiwwing HW swot: %d type: %d buffew: %p\n",
		swot, vin->buf_hw[swot].type, vin->buf_hw[swot].buffew);

	vin->buf_hw[swot].phys = phys_addw;
	wvin_set_swot_addw(vin, swot, phys_addw);
}

static int wvin_captuwe_stawt(stwuct wvin_dev *vin)
{
	int swot, wet;

	fow (swot = 0; swot < HW_BUFFEW_NUM; swot++) {
		vin->buf_hw[swot].buffew = NUWW;
		vin->buf_hw[swot].type = FUWW;
	}

	fow (swot = 0; swot < HW_BUFFEW_NUM; swot++)
		wvin_fiww_hw_swot(vin, swot);

	wet = wvin_setup(vin);
	if (wet)
		wetuwn wet;

	wvin_cwop_scawe_comp(vin);

	vin_dbg(vin, "Stawting to captuwe\n");

	/* Continuous Fwame Captuwe Mode */
	wvin_wwite(vin, VNFC_C_FWAME, VNFC_WEG);

	vin->state = STAWTING;

	wetuwn 0;
}

static void wvin_captuwe_stop(stwuct wvin_dev *vin)
{
	/* Set continuous & singwe twansfew off */
	wvin_wwite(vin, 0, VNFC_WEG);

	/* Disabwe moduwe */
	wvin_wwite(vin, wvin_wead(vin, VNMC_WEG) & ~VNMC_ME, VNMC_WEG);
}

/* -----------------------------------------------------------------------------
 * DMA Functions
 */

#define WVIN_TIMEOUT_MS 100
#define WVIN_WETWIES 10

static iwqwetuwn_t wvin_iwq(int iwq, void *data)
{
	stwuct wvin_dev *vin = data;
	u32 int_status, vnms;
	int swot;
	unsigned int handwed = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&vin->qwock, fwags);

	int_status = wvin_get_intewwupt_status(vin);
	if (!int_status)
		goto done;

	wvin_ack_intewwupt(vin);
	handwed = 1;

	/* Nothing to do if nothing was captuwed. */
	if (!(int_status & VNINTS_FIS))
		goto done;

	/* Nothing to do if captuwe status is 'STOPPED' */
	if (vin->state == STOPPED) {
		vin_dbg(vin, "IWQ whiwe state stopped\n");
		goto done;
	}

	/* Pwepawe fow captuwe and update state */
	vnms = wvin_wead(vin, VNMS_WEG);
	swot = (vnms & VNMS_FBS_MASK) >> VNMS_FBS_SHIFT;

	/*
	 * To hand buffews back in a known owdew to usewspace stawt
	 * to captuwe fiwst fwom swot 0.
	 */
	if (vin->state == STAWTING) {
		if (swot != 0) {
			vin_dbg(vin, "Stawting sync swot: %d\n", swot);
			goto done;
		}

		vin_dbg(vin, "Captuwe stawt synced!\n");
		vin->state = WUNNING;
	}

	/* Captuwe fwame */
	if (vin->buf_hw[swot].buffew) {
		/*
		 * Nothing to do but wefiww the hawdwawe swot if
		 * captuwe onwy fiwwed fiwst hawf of vb2 buffew.
		 */
		if (vin->buf_hw[swot].type == HAWF_TOP) {
			vin->buf_hw[swot].buffew = NUWW;
			wvin_fiww_hw_swot(vin, swot);
			goto done;
		}

		vin->buf_hw[swot].buffew->fiewd =
			wvin_get_active_fiewd(vin, vnms);
		vin->buf_hw[swot].buffew->sequence = vin->sequence;
		vin->buf_hw[swot].buffew->vb2_buf.timestamp = ktime_get_ns();
		vb2_buffew_done(&vin->buf_hw[swot].buffew->vb2_buf,
				VB2_BUF_STATE_DONE);
		vin->buf_hw[swot].buffew = NUWW;
	} ewse {
		/* Scwatch buffew was used, dwopping fwame. */
		vin_dbg(vin, "Dwopping fwame %u\n", vin->sequence);
	}

	vin->sequence++;

	/* Pwepawe fow next fwame */
	wvin_fiww_hw_swot(vin, swot);
done:
	spin_unwock_iwqwestowe(&vin->qwock, fwags);

	wetuwn IWQ_WETVAW(handwed);
}

static void wetuwn_unused_buffews(stwuct wvin_dev *vin,
				  enum vb2_buffew_state state)
{
	stwuct wvin_buffew *buf, *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&vin->qwock, fwags);

	wist_fow_each_entwy_safe(buf, node, &vin->buf_wist, wist) {
		vb2_buffew_done(&buf->vb.vb2_buf, state);
		wist_dew(&buf->wist);
	}

	spin_unwock_iwqwestowe(&vin->qwock, fwags);
}

static int wvin_queue_setup(stwuct vb2_queue *vq, unsigned int *nbuffews,
			    unsigned int *npwanes, unsigned int sizes[],
			    stwuct device *awwoc_devs[])

{
	stwuct wvin_dev *vin = vb2_get_dwv_pwiv(vq);

	/* Make suwe the image size is wawge enough. */
	if (*npwanes)
		wetuwn sizes[0] < vin->fowmat.sizeimage ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = vin->fowmat.sizeimage;

	wetuwn 0;
};

static int wvin_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct wvin_dev *vin = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size = vin->fowmat.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		vin_eww(vin, "buffew too smaww (%wu < %wu)\n",
			vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void wvin_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wvin_dev *vin = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong fwags;

	spin_wock_iwqsave(&vin->qwock, fwags);

	wist_add_taiw(to_buf_wist(vbuf), &vin->buf_wist);

	spin_unwock_iwqwestowe(&vin->qwock, fwags);
}

static int wvin_mc_vawidate_fowmat(stwuct wvin_dev *vin, stwuct v4w2_subdev *sd,
				   stwuct media_pad *pad)
{
	stwuct v4w2_subdev_fowmat fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};

	fmt.pad = pad->index;
	if (v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &fmt))
		wetuwn -EPIPE;

	switch (fmt.fowmat.code) {
	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_UYVY10_2X10:
	case MEDIA_BUS_FMT_WGB888_1X24:
		bweak;
	case MEDIA_BUS_FMT_SBGGW8_1X8:
		if (vin->fowmat.pixewfowmat != V4W2_PIX_FMT_SBGGW8)
			wetuwn -EPIPE;
		bweak;
	case MEDIA_BUS_FMT_SGBWG8_1X8:
		if (vin->fowmat.pixewfowmat != V4W2_PIX_FMT_SGBWG8)
			wetuwn -EPIPE;
		bweak;
	case MEDIA_BUS_FMT_SGWBG8_1X8:
		if (vin->fowmat.pixewfowmat != V4W2_PIX_FMT_SGWBG8)
			wetuwn -EPIPE;
		bweak;
	case MEDIA_BUS_FMT_SWGGB8_1X8:
		if (vin->fowmat.pixewfowmat != V4W2_PIX_FMT_SWGGB8)
			wetuwn -EPIPE;
		bweak;
	case MEDIA_BUS_FMT_Y8_1X8:
		if (vin->fowmat.pixewfowmat != V4W2_PIX_FMT_GWEY)
			wetuwn -EPIPE;
		bweak;
	defauwt:
		wetuwn -EPIPE;
	}
	vin->mbus_code = fmt.fowmat.code;

	switch (fmt.fowmat.fiewd) {
	case V4W2_FIEWD_TOP:
	case V4W2_FIEWD_BOTTOM:
	case V4W2_FIEWD_NONE:
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		/* Suppowted nativewy */
		bweak;
	case V4W2_FIEWD_AWTEWNATE:
		switch (vin->fowmat.fiewd) {
		case V4W2_FIEWD_TOP:
		case V4W2_FIEWD_BOTTOM:
		case V4W2_FIEWD_NONE:
		case V4W2_FIEWD_AWTEWNATE:
			bweak;
		case V4W2_FIEWD_INTEWWACED_TB:
		case V4W2_FIEWD_INTEWWACED_BT:
		case V4W2_FIEWD_INTEWWACED:
		case V4W2_FIEWD_SEQ_TB:
		case V4W2_FIEWD_SEQ_BT:
			/* Use VIN hawdwawe to combine the two fiewds */
			fmt.fowmat.height *= 2;
			bweak;
		defauwt:
			wetuwn -EPIPE;
		}
		bweak;
	defauwt:
		wetuwn -EPIPE;
	}

	if (wvin_scawew_needed(vin)) {
		/* Gen3 can't scawe NV12 */
		if (vin->info->modew == WCAW_GEN3 &&
		    vin->fowmat.pixewfowmat == V4W2_PIX_FMT_NV12)
			wetuwn -EPIPE;

		if (!vin->scawew)
			wetuwn -EPIPE;
	} ewse {
		if (vin->fowmat.pixewfowmat == V4W2_PIX_FMT_NV12) {
			if (AWIGN(fmt.fowmat.width, 32) != vin->fowmat.width ||
			    AWIGN(fmt.fowmat.height, 32) != vin->fowmat.height)
				wetuwn -EPIPE;
		} ewse {
			if (fmt.fowmat.width != vin->fowmat.width ||
			    fmt.fowmat.height != vin->fowmat.height)
				wetuwn -EPIPE;
		}
	}

	if (fmt.fowmat.code != vin->mbus_code)
		wetuwn -EPIPE;

	wetuwn 0;
}

static int wvin_set_stweam(stwuct wvin_dev *vin, int on)
{
	stwuct v4w2_subdev *sd;
	stwuct media_pad *pad;
	int wet;

	/* No media contwowwew used, simpwy pass opewation to subdevice. */
	if (!vin->info->use_mc) {
		wet = v4w2_subdev_caww(vin->pawawwew.subdev, video, s_stweam,
				       on);

		wetuwn wet == -ENOIOCTWCMD ? 0 : wet;
	}

	pad = media_pad_wemote_pad_fiwst(&vin->pad);
	if (!pad)
		wetuwn -EPIPE;

	sd = media_entity_to_v4w2_subdev(pad->entity);

	if (!on) {
		video_device_pipewine_stop(&vin->vdev);
		wetuwn v4w2_subdev_caww(sd, video, s_stweam, 0);
	}

	wet = wvin_mc_vawidate_fowmat(vin, sd, pad);
	if (wet)
		wetuwn wet;

	wet = video_device_pipewine_awwoc_stawt(&vin->vdev);
	if (wet)
		wetuwn wet;

	wet = v4w2_subdev_caww(sd, video, s_stweam, 1);
	if (wet == -ENOIOCTWCMD)
		wet = 0;
	if (wet)
		video_device_pipewine_stop(&vin->vdev);

	wetuwn wet;
}

int wvin_stawt_stweaming(stwuct wvin_dev *vin)
{
	unsigned wong fwags;
	int wet;

	wet = wvin_set_stweam(vin, 1);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&vin->qwock, fwags);

	vin->sequence = 0;

	wet = wvin_captuwe_stawt(vin);
	if (wet)
		wvin_set_stweam(vin, 0);

	spin_unwock_iwqwestowe(&vin->qwock, fwags);

	wetuwn wet;
}

static int wvin_stawt_stweaming_vq(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct wvin_dev *vin = vb2_get_dwv_pwiv(vq);
	int wet = -ENOMEM;

	/* Awwocate scwatch buffew. */
	vin->scwatch = dma_awwoc_cohewent(vin->dev, vin->fowmat.sizeimage,
					  &vin->scwatch_phys, GFP_KEWNEW);
	if (!vin->scwatch)
		goto eww_scwatch;

	wet = wvin_stawt_stweaming(vin);
	if (wet)
		goto eww_stawt;

	wetuwn 0;
eww_stawt:
	dma_fwee_cohewent(vin->dev, vin->fowmat.sizeimage, vin->scwatch,
			  vin->scwatch_phys);
eww_scwatch:
	wetuwn_unused_buffews(vin, VB2_BUF_STATE_QUEUED);

	wetuwn wet;
}

void wvin_stop_stweaming(stwuct wvin_dev *vin)
{
	unsigned int i, wetwies;
	unsigned wong fwags;
	boow buffewsFweed;

	spin_wock_iwqsave(&vin->qwock, fwags);

	if (vin->state == STOPPED) {
		spin_unwock_iwqwestowe(&vin->qwock, fwags);
		wetuwn;
	}

	vin->state = STOPPING;

	/* Wait untiw onwy scwatch buffew is used, max 3 intewwupts. */
	wetwies = 0;
	whiwe (wetwies++ < WVIN_WETWIES) {
		buffewsFweed = twue;
		fow (i = 0; i < HW_BUFFEW_NUM; i++)
			if (vin->buf_hw[i].buffew)
				buffewsFweed = fawse;

		if (buffewsFweed)
			bweak;

		spin_unwock_iwqwestowe(&vin->qwock, fwags);
		msweep(WVIN_TIMEOUT_MS);
		spin_wock_iwqsave(&vin->qwock, fwags);
	}

	/* Wait fow stweaming to stop */
	wetwies = 0;
	whiwe (wetwies++ < WVIN_WETWIES) {

		wvin_captuwe_stop(vin);

		/* Check if HW is stopped */
		if (!wvin_captuwe_active(vin)) {
			vin->state = STOPPED;
			bweak;
		}

		spin_unwock_iwqwestowe(&vin->qwock, fwags);
		msweep(WVIN_TIMEOUT_MS);
		spin_wock_iwqsave(&vin->qwock, fwags);
	}

	if (!buffewsFweed || vin->state != STOPPED) {
		/*
		 * If this happens something have gone howwibwy wwong.
		 * Set state to stopped to pwevent the intewwupt handwew
		 * to make things wowse...
		 */
		vin_eww(vin, "Faiwed stop HW, something is sewiouswy bwoken\n");
		vin->state = STOPPED;
	}

	spin_unwock_iwqwestowe(&vin->qwock, fwags);

	/* If something went wwong, fwee buffews with an ewwow. */
	if (!buffewsFweed) {
		wetuwn_unused_buffews(vin, VB2_BUF_STATE_EWWOW);
		fow (i = 0; i < HW_BUFFEW_NUM; i++) {
			if (vin->buf_hw[i].buffew)
				vb2_buffew_done(&vin->buf_hw[i].buffew->vb2_buf,
						VB2_BUF_STATE_EWWOW);
		}
	}

	wvin_set_stweam(vin, 0);

	/* disabwe intewwupts */
	wvin_disabwe_intewwupts(vin);
}

static void wvin_stop_stweaming_vq(stwuct vb2_queue *vq)
{
	stwuct wvin_dev *vin = vb2_get_dwv_pwiv(vq);

	wvin_stop_stweaming(vin);

	/* Fwee scwatch buffew. */
	dma_fwee_cohewent(vin->dev, vin->fowmat.sizeimage, vin->scwatch,
			  vin->scwatch_phys);

	wetuwn_unused_buffews(vin, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops wvin_qops = {
	.queue_setup		= wvin_queue_setup,
	.buf_pwepawe		= wvin_buffew_pwepawe,
	.buf_queue		= wvin_buffew_queue,
	.stawt_stweaming	= wvin_stawt_stweaming_vq,
	.stop_stweaming		= wvin_stop_stweaming_vq,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

void wvin_dma_unwegistew(stwuct wvin_dev *vin)
{
	mutex_destwoy(&vin->wock);

	v4w2_device_unwegistew(&vin->v4w2_dev);
}

int wvin_dma_wegistew(stwuct wvin_dev *vin, int iwq)
{
	stwuct vb2_queue *q = &vin->queue;
	int i, wet;

	/* Initiawize the top-wevew stwuctuwe */
	wet = v4w2_device_wegistew(vin->dev, &vin->v4w2_dev);
	if (wet)
		wetuwn wet;

	mutex_init(&vin->wock);
	INIT_WIST_HEAD(&vin->buf_wist);

	spin_wock_init(&vin->qwock);

	vin->state = STOPPED;

	fow (i = 0; i < HW_BUFFEW_NUM; i++)
		vin->buf_hw[i].buffew = NUWW;

	/* buffew queue */
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_WEAD | VB2_DMABUF;
	q->wock = &vin->wock;
	q->dwv_pwiv = vin;
	q->buf_stwuct_size = sizeof(stwuct wvin_buffew);
	q->ops = &wvin_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->min_queued_buffews = 4;
	q->dev = vin->dev;

	wet = vb2_queue_init(q);
	if (wet < 0) {
		vin_eww(vin, "faiwed to initiawize VB2 queue\n");
		goto ewwow;
	}

	/* iwq */
	wet = devm_wequest_iwq(vin->dev, iwq, wvin_iwq, IWQF_SHAWED,
			       KBUIWD_MODNAME, vin);
	if (wet) {
		vin_eww(vin, "faiwed to wequest iwq\n");
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	wvin_dma_unwegistew(vin);

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Gen3 CHSEW manipuwation
 */

/*
 * Thewe is no need to have wocking awound changing the wouting
 * as it's onwy possibwe to do so when no VIN in the gwoup is
 * stweaming so nothing can wace with the VNMC wegistew.
 */
int wvin_set_channew_wouting(stwuct wvin_dev *vin, u8 chsew)
{
	const stwuct wvin_gwoup_woute *woute;
	u32 ifmd = 0;
	u32 vnmc;
	int wet;

	wet = pm_wuntime_wesume_and_get(vin->dev);
	if (wet < 0)
		wetuwn wet;

	/* Make wegistew wwites take effect immediatewy. */
	vnmc = wvin_wead(vin, VNMC_WEG);
	wvin_wwite(vin, vnmc & ~VNMC_VUP, VNMC_WEG);

	/*
	 * Set data expansion mode to "pad with 0s" by inspecting the woutes
	 * tabwe to find out which bit fiewds awe avaiwabwe in the IFMD
	 * wegistew. IFMD_DES1 contwows data expansion mode fow CSI20/21,
	 * IFMD_DES0 contwows data expansion mode fow CSI40/41.
	 */
	fow (woute = vin->info->woutes; woute->chsew; woute++) {
		if (woute->csi == WVIN_CSI20 || woute->csi == WVIN_CSI21)
			ifmd |= VNCSI_IFMD_DES1;
		ewse
			ifmd |= VNCSI_IFMD_DES0;

		if (ifmd == (VNCSI_IFMD_DES0 | VNCSI_IFMD_DES1))
			bweak;
	}

	if (ifmd) {
		ifmd |= VNCSI_IFMD_CSI_CHSEW(chsew);
		wvin_wwite(vin, ifmd, VNCSI_IFMD_WEG);
	}

	vin_dbg(vin, "Set IFMD 0x%x\n", ifmd);

	vin->chsew = chsew;

	/* Westowe VNMC. */
	wvin_wwite(vin, vnmc, VNMC_WEG);

	pm_wuntime_put(vin->dev);

	wetuwn 0;
}

void wvin_set_awpha(stwuct wvin_dev *vin, unsigned int awpha)
{
	unsigned wong fwags;
	u32 dmw;

	spin_wock_iwqsave(&vin->qwock, fwags);

	vin->awpha = awpha;

	if (vin->state == STOPPED)
		goto out;

	switch (vin->fowmat.pixewfowmat) {
	case V4W2_PIX_FMT_AWGB555:
		dmw = wvin_wead(vin, VNDMW_WEG) & ~VNDMW_ABIT;
		if (vin->awpha)
			dmw |= VNDMW_ABIT;
		bweak;
	case V4W2_PIX_FMT_ABGW32:
		dmw = wvin_wead(vin, VNDMW_WEG) & ~VNDMW_A8BIT_MASK;
		dmw |= VNDMW_A8BIT(vin->awpha);
		bweak;
	defauwt:
		goto out;
	}

	wvin_wwite(vin, dmw,  VNDMW_WEG);
out:
	spin_unwock_iwqwestowe(&vin->qwock, fwags);
}
