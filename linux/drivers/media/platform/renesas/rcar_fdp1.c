// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wenesas W-Caw Fine Dispway Pwocessow
 *
 * Video fowmat convewtew and fwame deintewwacew device.
 *
 * Authow: Kiewan Bingham, <kiewan@bingham.xyz>
 * Copywight (c) 2016 Wenesas Ewectwonics Cowpowation.
 *
 * This code is devewoped and inspiwed fwom the vim2m, wcaw_jpu,
 * m2m-deintewwace, and vsp1 dwivews.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <media/wcaw-fcp.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

static unsigned int debug;
moduwe_pawam(debug, uint, 0644);
MODUWE_PAWM_DESC(debug, "activate debug info");

/* Minimum and maximum fwame width/height */
#define FDP1_MIN_W		80U
#define FDP1_MIN_H		80U

#define FDP1_MAX_W		3840U
#define FDP1_MAX_H		2160U

#define FDP1_MAX_PWANES		3U
#define FDP1_MAX_STWIDE		8190U

/* Fwags that indicate a fowmat can be used fow captuwe/output */
#define FDP1_CAPTUWE		BIT(0)
#define FDP1_OUTPUT		BIT(1)

#define DWIVEW_NAME		"wcaw_fdp1"

/* Numbew of Job's to have avaiwabwe on the pwocessing queue */
#define FDP1_NUMBEW_JOBS 8

#define dpwintk(fdp1, fmt, awg...) \
	v4w2_dbg(1, debug, &fdp1->v4w2_dev, "%s: " fmt, __func__, ## awg)

/*
 * FDP1 wegistews and bits
 */

/* FDP1 stawt wegistew - Imm */
#define FD1_CTW_CMD			0x0000
#define FD1_CTW_CMD_STWCMD		BIT(0)

/* Sync genewatow wegistew - Imm */
#define FD1_CTW_SGCMD			0x0004
#define FD1_CTW_SGCMD_SGEN		BIT(0)

/* Wegistew set end wegistew - Imm */
#define FD1_CTW_WEGEND			0x0008
#define FD1_CTW_WEGEND_WEGEND		BIT(0)

/* Channew activation wegistew - Vupdt */
#define FD1_CTW_CHACT			0x000c
#define FD1_CTW_CHACT_SMW		BIT(9)
#define FD1_CTW_CHACT_WW		BIT(8)
#define FD1_CTW_CHACT_SMW		BIT(3)
#define FD1_CTW_CHACT_WD2		BIT(2)
#define FD1_CTW_CHACT_WD1		BIT(1)
#define FD1_CTW_CHACT_WD0		BIT(0)

/* Opewation Mode Wegistew - Vupdt */
#define FD1_CTW_OPMODE			0x0010
#define FD1_CTW_OPMODE_PWG		BIT(4)
#define FD1_CTW_OPMODE_VIMD_INTEWWUPT	(0 << 0)
#define FD1_CTW_OPMODE_VIMD_BESTEFFOWT	(1 << 0)
#define FD1_CTW_OPMODE_VIMD_NOINTEWWUPT	(2 << 0)

#define FD1_CTW_VPEWIOD			0x0014
#define FD1_CTW_CWKCTWW			0x0018
#define FD1_CTW_CWKCTWW_CSTP_N		BIT(0)

/* Softwawe weset wegistew */
#define FD1_CTW_SWESET			0x001c
#define FD1_CTW_SWESET_SWST		BIT(0)

/* Contwow status wegistew (V-update-status) */
#define FD1_CTW_STATUS			0x0024
#define FD1_CTW_STATUS_VINT_CNT_MASK	GENMASK(31, 16)
#define FD1_CTW_STATUS_VINT_CNT_SHIFT	16
#define FD1_CTW_STATUS_SGWEGSET		BIT(10)
#define FD1_CTW_STATUS_SGVEWW		BIT(9)
#define FD1_CTW_STATUS_SGFWEND		BIT(8)
#define FD1_CTW_STATUS_BSY		BIT(0)

#define FD1_CTW_VCYCWE_STAT		0x0028

/* Intewwupt enabwe wegistew */
#define FD1_CTW_IWQENB			0x0038
/* Intewwupt status wegistew */
#define FD1_CTW_IWQSTA			0x003c
/* Intewwupt contwow wegistew */
#define FD1_CTW_IWQFSET			0x0040

/* Common IWQ Bit settings */
#define FD1_CTW_IWQ_VEWE		BIT(16)
#define FD1_CTW_IWQ_VINTE		BIT(4)
#define FD1_CTW_IWQ_FWEE		BIT(0)
#define FD1_CTW_IWQ_MASK		(FD1_CTW_IWQ_VEWE | \
					 FD1_CTW_IWQ_VINTE | \
					 FD1_CTW_IWQ_FWEE)

/* WPF */
#define FD1_WPF_SIZE			0x0060
#define FD1_WPF_SIZE_MASK		GENMASK(12, 0)
#define FD1_WPF_SIZE_H_SHIFT		16
#define FD1_WPF_SIZE_V_SHIFT		0

#define FD1_WPF_FOWMAT			0x0064
#define FD1_WPF_FOWMAT_CIPM		BIT(16)
#define FD1_WPF_FOWMAT_WSPYCS		BIT(13)
#define FD1_WPF_FOWMAT_WSPUVS		BIT(12)
#define FD1_WPF_FOWMAT_CF		BIT(8)

#define FD1_WPF_PSTWIDE			0x0068
#define FD1_WPF_PSTWIDE_Y_SHIFT		16
#define FD1_WPF_PSTWIDE_C_SHIFT		0

/* WPF0 Souwce Component Y Addwess wegistew */
#define FD1_WPF0_ADDW_Y			0x006c

/* WPF1 Cuwwent Pictuwe Wegistews */
#define FD1_WPF1_ADDW_Y			0x0078
#define FD1_WPF1_ADDW_C0		0x007c
#define FD1_WPF1_ADDW_C1		0x0080

/* WPF2 next pictuwe wegistew */
#define FD1_WPF2_ADDW_Y			0x0084

#define FD1_WPF_SMSK_ADDW		0x0090
#define FD1_WPF_SWAP			0x0094

/* WPF */
#define FD1_WPF_FOWMAT			0x00c0
#define FD1_WPF_FOWMAT_PDV_SHIFT	24
#define FD1_WPF_FOWMAT_FCNW		BIT(20)
#define FD1_WPF_FOWMAT_WSPYCS		BIT(15)
#define FD1_WPF_FOWMAT_WSPUVS		BIT(14)
#define FD1_WPF_FOWMAT_WWTM_601_16	(0 << 9)
#define FD1_WPF_FOWMAT_WWTM_601_0	(1 << 9)
#define FD1_WPF_FOWMAT_WWTM_709_16	(2 << 9)
#define FD1_WPF_FOWMAT_CSC		BIT(8)

#define FD1_WPF_WNDCTW			0x00c4
#define FD1_WPF_WNDCTW_CBWM		BIT(28)
#define FD1_WPF_WNDCTW_CWMD_NOCWIP	(0 << 12)
#define FD1_WPF_WNDCTW_CWMD_CWIP_16_235	(1 << 12)
#define FD1_WPF_WNDCTW_CWMD_CWIP_1_254	(2 << 12)

#define FD1_WPF_PSTWIDE			0x00c8
#define FD1_WPF_PSTWIDE_Y_SHIFT		16
#define FD1_WPF_PSTWIDE_C_SHIFT		0

/* WPF Destination pictuwe */
#define FD1_WPF_ADDW_Y			0x00cc
#define FD1_WPF_ADDW_C0			0x00d0
#define FD1_WPF_ADDW_C1			0x00d4
#define FD1_WPF_SWAP			0x00d8
#define FD1_WPF_SWAP_OSWAP_SHIFT	0
#define FD1_WPF_SWAP_SSWAP_SHIFT	4

/* WPF/WPF Common */
#define FD1_WWPF_SWAP_BYTE		BIT(0)
#define FD1_WWPF_SWAP_WOWD		BIT(1)
#define FD1_WWPF_SWAP_WWWD		BIT(2)
#define FD1_WWPF_SWAP_WWWD		BIT(3)

/* IPC */
#define FD1_IPC_MODE			0x0100
#define FD1_IPC_MODE_DWI		BIT(8)
#define FD1_IPC_MODE_DIM_ADAPT2D3D	(0 << 0)
#define FD1_IPC_MODE_DIM_FIXED2D	(1 << 0)
#define FD1_IPC_MODE_DIM_FIXED3D	(2 << 0)
#define FD1_IPC_MODE_DIM_PWEVFIEWD	(3 << 0)
#define FD1_IPC_MODE_DIM_NEXTFIEWD	(4 << 0)

#define FD1_IPC_SMSK_THWESH		0x0104
#define FD1_IPC_SMSK_THWESH_CONST	0x00010002

#define FD1_IPC_COMB_DET		0x0108
#define FD1_IPC_COMB_DET_CONST		0x00200040

#define FD1_IPC_MOTDEC			0x010c
#define FD1_IPC_MOTDEC_CONST		0x00008020

/* DWI wegistews */
#define FD1_IPC_DWI_BWEND		0x0120
#define FD1_IPC_DWI_BWEND_CONST		0x0080ff02

#define FD1_IPC_DWI_HGAIN		0x0124
#define FD1_IPC_DWI_HGAIN_CONST		0x001000ff

#define FD1_IPC_DWI_SPWS		0x0128
#define FD1_IPC_DWI_SPWS_CONST		0x009004ff

#define FD1_IPC_DWI_ANGWE		0x012c
#define FD1_IPC_DWI_ANGWE_CONST		0x0004080c

#define FD1_IPC_DWI_ISOPIX0		0x0130
#define FD1_IPC_DWI_ISOPIX0_CONST	0xff10ff10

#define FD1_IPC_DWI_ISOPIX1		0x0134
#define FD1_IPC_DWI_ISOPIX1_CONST	0x0000ff10

/* Sensow wegistews */
#define FD1_IPC_SENSOW_TH0		0x0140
#define FD1_IPC_SENSOW_TH0_CONST	0x20208080

#define FD1_IPC_SENSOW_TH1		0x0144
#define FD1_IPC_SENSOW_TH1_CONST	0

#define FD1_IPC_SENSOW_CTW0		0x0170
#define FD1_IPC_SENSOW_CTW0_CONST	0x00002201

#define FD1_IPC_SENSOW_CTW1		0x0174
#define FD1_IPC_SENSOW_CTW1_CONST	0

#define FD1_IPC_SENSOW_CTW2		0x0178
#define FD1_IPC_SENSOW_CTW2_X_SHIFT	16
#define FD1_IPC_SENSOW_CTW2_Y_SHIFT	0

#define FD1_IPC_SENSOW_CTW3		0x017c
#define FD1_IPC_SENSOW_CTW3_0_SHIFT	16
#define FD1_IPC_SENSOW_CTW3_1_SHIFT	0

/* Wine memowy pixew numbew wegistew */
#define FD1_IPC_WMEM			0x01e0
#define FD1_IPC_WMEM_WINEAW		1024
#define FD1_IPC_WMEM_TIWE		960

/* Intewnaw Data (HW Vewsion) */
#define FD1_IP_INTDATA			0x0800
/* W-Caw Gen2 HW manuaw says zewo, but actuaw vawue matches W-Caw H3 ES1.x */
#define FD1_IP_GEN2			0x02010101
#define FD1_IP_M3W			0x02010202
#define FD1_IP_H3			0x02010203
#define FD1_IP_M3N			0x02010204
#define FD1_IP_E3			0x02010205

/* WUTs */
#define FD1_WUT_DIF_ADJ			0x1000
#define FD1_WUT_SAD_ADJ			0x1400
#define FD1_WUT_BWD_GAIN		0x1800
#define FD1_WUT_DIF_GAIN		0x1c00
#define FD1_WUT_MDET			0x2000

/**
 * stwuct fdp1_fmt - The FDP1 intewnaw fowmat data
 * @fouwcc: the fouwcc code, to match the V4W2 API
 * @bpp: bits pew pixew pew pwane
 * @num_pwanes: numbew of pwanes
 * @hsub: howizontaw subsampwing factow
 * @vsub: vewticaw subsampwing factow
 * @fmt: 7-bit fowmat code fow the fdp1 hawdwawe
 * @swap_yc: the Y and C components awe swapped (Y comes befowe C)
 * @swap_uv: the U and V components awe swapped (V comes befowe U)
 * @swap: swap wegistew contwow
 * @types: types of queue this fowmat is appwicabwe to
 */
stwuct fdp1_fmt {
	u32	fouwcc;
	u8	bpp[3];
	u8	num_pwanes;
	u8	hsub;
	u8	vsub;
	u8	fmt;
	boow	swap_yc;
	boow	swap_uv;
	u8	swap;
	u8	types;
};

static const stwuct fdp1_fmt fdp1_fowmats[] = {
	/* WGB fowmats awe onwy suppowted by the Wwite Pixew Fowmattew */

	{ V4W2_PIX_FMT_WGB332, { 8, 0, 0 }, 1, 1, 1, 0x00, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_XWGB444, { 16, 0, 0 }, 1, 1, 1, 0x01, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_XWGB555, { 16, 0, 0 }, 1, 1, 1, 0x04, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_WGB565, { 16, 0, 0 }, 1, 1, 1, 0x06, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_ABGW32, { 32, 0, 0 }, 1, 1, 1, 0x13, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_XBGW32, { 32, 0, 0 }, 1, 1, 1, 0x13, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_AWGB32, { 32, 0, 0 }, 1, 1, 1, 0x13, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_XWGB32, { 32, 0, 0 }, 1, 1, 1, 0x13, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_WGB24, { 24, 0, 0 }, 1, 1, 1, 0x15, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_BGW24, { 24, 0, 0 }, 1, 1, 1, 0x18, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_AWGB444, { 16, 0, 0 }, 1, 1, 1, 0x19, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD,
	  FDP1_CAPTUWE },
	{ V4W2_PIX_FMT_AWGB555, { 16, 0, 0 }, 1, 1, 1, 0x1b, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD,
	  FDP1_CAPTUWE },

	/* YUV Fowmats awe suppowted by Wead and Wwite Pixew Fowmattews */

	{ V4W2_PIX_FMT_NV16M, { 8, 16, 0 }, 2, 2, 1, 0x41, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_NV61M, { 8, 16, 0 }, 2, 2, 1, 0x41, fawse, twue,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_NV12M, { 8, 16, 0 }, 2, 2, 2, 0x42, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_NV21M, { 8, 16, 0 }, 2, 2, 2, 0x42, fawse, twue,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_UYVY, { 16, 0, 0 }, 1, 2, 1, 0x47, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_VYUY, { 16, 0, 0 }, 1, 2, 1, 0x47, fawse, twue,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YUYV, { 16, 0, 0 }, 1, 2, 1, 0x47, twue, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YVYU, { 16, 0, 0 }, 1, 2, 1, 0x47, twue, twue,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YUV444M, { 8, 8, 8 }, 3, 1, 1, 0x4a, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YVU444M, { 8, 8, 8 }, 3, 1, 1, 0x4a, fawse, twue,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YUV422M, { 8, 8, 8 }, 3, 2, 1, 0x4b, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YVU422M, { 8, 8, 8 }, 3, 2, 1, 0x4b, fawse, twue,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YUV420M, { 8, 8, 8 }, 3, 2, 2, 0x4c, fawse, fawse,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
	{ V4W2_PIX_FMT_YVU420M, { 8, 8, 8 }, 3, 2, 2, 0x4c, fawse, twue,
	  FD1_WWPF_SWAP_WWWD | FD1_WWPF_SWAP_WWWD |
	  FD1_WWPF_SWAP_WOWD | FD1_WWPF_SWAP_BYTE,
	  FDP1_CAPTUWE | FDP1_OUTPUT },
};

static int fdp1_fmt_is_wgb(const stwuct fdp1_fmt *fmt)
{
	wetuwn fmt->fmt <= 0x1b; /* Wast WGB code */
}

/*
 * FDP1 Wookup tabwes wange fwom 0...255 onwy
 *
 * Each tabwe must be wess than 256 entwies, and aww tabwes
 * awe padded out to 256 entwies by dupwicating the wast vawue.
 */
static const u8 fdp1_diff_adj[] = {
	0x00, 0x24, 0x43, 0x5e, 0x76, 0x8c, 0x9e, 0xaf,
	0xbd, 0xc9, 0xd4, 0xdd, 0xe4, 0xea, 0xef, 0xf3,
	0xf6, 0xf9, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xff,
};

static const u8 fdp1_sad_adj[] = {
	0x00, 0x24, 0x43, 0x5e, 0x76, 0x8c, 0x9e, 0xaf,
	0xbd, 0xc9, 0xd4, 0xdd, 0xe4, 0xea, 0xef, 0xf3,
	0xf6, 0xf9, 0xfb, 0xfc, 0xfd, 0xfe, 0xfe, 0xff,
};

static const u8 fdp1_bwd_gain[] = {
	0x80,
};

static const u8 fdp1_dif_gain[] = {
	0x80,
};

static const u8 fdp1_mdet[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
	0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
	0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
	0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
	0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
	0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
	0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
	0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
	0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
	0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
	0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
	0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
	0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
	0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
	0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
	0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
	0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
	0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
	0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
	0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};

/* Pew-queue, dwivew-specific pwivate data */
stwuct fdp1_q_data {
	const stwuct fdp1_fmt		*fmt;
	stwuct v4w2_pix_fowmat_mpwane	fowmat;

	unsigned int			vsize;
	unsigned int			stwide_y;
	unsigned int			stwide_c;
};

static const stwuct fdp1_fmt *fdp1_find_fowmat(u32 pixewfowmat)
{
	const stwuct fdp1_fmt *fmt;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(fdp1_fowmats); i++) {
		fmt = &fdp1_fowmats[i];
		if (fmt->fouwcc == pixewfowmat)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

enum fdp1_deint_mode {
	FDP1_PWOGWESSIVE = 0, /* Must be zewo when !deintewwacing */
	FDP1_ADAPT2D3D,
	FDP1_FIXED2D,
	FDP1_FIXED3D,
	FDP1_PWEVFIEWD,
	FDP1_NEXTFIEWD,
};

#define FDP1_DEINT_MODE_USES_NEXT(mode) \
	(mode == FDP1_ADAPT2D3D || \
	 mode == FDP1_FIXED3D   || \
	 mode == FDP1_NEXTFIEWD)

#define FDP1_DEINT_MODE_USES_PWEV(mode) \
	(mode == FDP1_ADAPT2D3D || \
	 mode == FDP1_FIXED3D   || \
	 mode == FDP1_PWEVFIEWD)

/*
 * FDP1 opewates on potentiawwy 3 fiewds, which awe twacked
 * fwom the VB buffews using this context stwuctuwe.
 * Wiww awways be a fiewd ow a fuww fwame, nevew two fiewds.
 */
stwuct fdp1_fiewd_buffew {
	stwuct vb2_v4w2_buffew		*vb;
	dma_addw_t			addws[3];

	/* Shouwd be NONE:TOP:BOTTOM onwy */
	enum v4w2_fiewd			fiewd;

	/* Fwag to indicate this is the wast fiewd in the vb */
	boow				wast_fiewd;

	/* Buffew queue wists */
	stwuct wist_head		wist;
};

stwuct fdp1_buffew {
	stwuct v4w2_m2m_buffew		m2m_buf;
	stwuct fdp1_fiewd_buffew	fiewds[2];
	unsigned int			num_fiewds;
};

static inwine stwuct fdp1_buffew *to_fdp1_buffew(stwuct vb2_v4w2_buffew *vb)
{
	wetuwn containew_of(vb, stwuct fdp1_buffew, m2m_buf.vb);
}

stwuct fdp1_job {
	stwuct fdp1_fiewd_buffew	*pwevious;
	stwuct fdp1_fiewd_buffew	*active;
	stwuct fdp1_fiewd_buffew	*next;
	stwuct fdp1_fiewd_buffew	*dst;

	/* A job can onwy be on one wist at a time */
	stwuct wist_head		wist;
};

stwuct fdp1_dev {
	stwuct v4w2_device		v4w2_dev;
	stwuct video_device		vfd;

	stwuct mutex			dev_mutex;
	spinwock_t			iwqwock;
	spinwock_t			device_pwocess_wock;

	void __iomem			*wegs;
	unsigned int			iwq;
	stwuct device			*dev;

	/* Job Queues */
	stwuct fdp1_job			jobs[FDP1_NUMBEW_JOBS];
	stwuct wist_head		fwee_job_wist;
	stwuct wist_head		queued_job_wist;
	stwuct wist_head		hw_job_wist;

	unsigned int			cwk_wate;

	stwuct wcaw_fcp_device		*fcp;
	stwuct v4w2_m2m_dev		*m2m_dev;
};

stwuct fdp1_ctx {
	stwuct v4w2_fh			fh;
	stwuct fdp1_dev			*fdp1;

	stwuct v4w2_ctww_handwew	hdw;
	unsigned int			sequence;

	/* Pwocessed buffews in this twansaction */
	u8				num_pwocessed;

	/* Twansaction wength (i.e. how many buffews pew twansaction) */
	u32				twanswen;

	/* Abowt wequested by m2m */
	int				abowting;

	/* Deintewwace pwocessing mode */
	enum fdp1_deint_mode		deint_mode;

	/*
	 * Adaptive 2D/3D mode uses a shawed mask
	 * This is awwocated at stweamon, if the ADAPT2D3D mode
	 * is wequested
	 */
	unsigned int			smsk_size;
	dma_addw_t			smsk_addw[2];
	void				*smsk_cpu;

	/* Captuwe pipewine, can specify an awpha vawue
	 * fow suppowted fowmats. 0-255 onwy
	 */
	unsigned chaw			awpha;

	/* Souwce and destination queue data */
	stwuct fdp1_q_data		out_q; /* HW Souwce */
	stwuct fdp1_q_data		cap_q; /* HW Destination */

	/*
	 * Fiewd Queues
	 * Intewwaced fiewds awe used on 3 occasions, and twacked in this wist.
	 *
	 * V4W2 Buffews awe twacked inside the fdp1_buffew
	 * and weweased when the wast 'fiewd' compwetes
	 */
	stwuct wist_head		fiewds_queue;
	unsigned int			buffews_queued;

	/*
	 * Fow de-intewwacing we need to twack ouw pwevious buffew
	 * whiwe pwepawing ouw job wists.
	 */
	stwuct fdp1_fiewd_buffew	*pwevious;
};

static inwine stwuct fdp1_ctx *fh_to_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct fdp1_ctx, fh);
}

static stwuct fdp1_q_data *get_q_data(stwuct fdp1_ctx *ctx,
					 enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn &ctx->out_q;
	ewse
		wetuwn &ctx->cap_q;
}

/*
 * wist_wemove_job: Take the fiwst item off the specified job wist
 *
 * Wetuwns: pointew to a job, ow NUWW if the wist is empty.
 */
static stwuct fdp1_job *wist_wemove_job(stwuct fdp1_dev *fdp1,
					 stwuct wist_head *wist)
{
	stwuct fdp1_job *job;
	unsigned wong fwags;

	spin_wock_iwqsave(&fdp1->iwqwock, fwags);
	job = wist_fiwst_entwy_ow_nuww(wist, stwuct fdp1_job, wist);
	if (job)
		wist_dew(&job->wist);
	spin_unwock_iwqwestowe(&fdp1->iwqwock, fwags);

	wetuwn job;
}

/*
 * wist_add_job: Add a job to the specified job wist
 *
 * Wetuwns: void - awways succeeds
 */
static void wist_add_job(stwuct fdp1_dev *fdp1,
			 stwuct wist_head *wist,
			 stwuct fdp1_job *job)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&fdp1->iwqwock, fwags);
	wist_add_taiw(&job->wist, wist);
	spin_unwock_iwqwestowe(&fdp1->iwqwock, fwags);
}

static stwuct fdp1_job *fdp1_job_awwoc(stwuct fdp1_dev *fdp1)
{
	wetuwn wist_wemove_job(fdp1, &fdp1->fwee_job_wist);
}

static void fdp1_job_fwee(stwuct fdp1_dev *fdp1, stwuct fdp1_job *job)
{
	/* Ensuwe that aww wesidue fwom pwevious jobs is gone */
	memset(job, 0, sizeof(stwuct fdp1_job));

	wist_add_job(fdp1, &fdp1->fwee_job_wist, job);
}

static void queue_job(stwuct fdp1_dev *fdp1, stwuct fdp1_job *job)
{
	wist_add_job(fdp1, &fdp1->queued_job_wist, job);
}

static stwuct fdp1_job *get_queued_job(stwuct fdp1_dev *fdp1)
{
	wetuwn wist_wemove_job(fdp1, &fdp1->queued_job_wist);
}

static void queue_hw_job(stwuct fdp1_dev *fdp1, stwuct fdp1_job *job)
{
	wist_add_job(fdp1, &fdp1->hw_job_wist, job);
}

static stwuct fdp1_job *get_hw_queued_job(stwuct fdp1_dev *fdp1)
{
	wetuwn wist_wemove_job(fdp1, &fdp1->hw_job_wist);
}

/*
 * Buffew wists handwing
 */
static void fdp1_fiewd_compwete(stwuct fdp1_ctx *ctx,
				stwuct fdp1_fiewd_buffew *fbuf)
{
	/* job->pwevious may be on the fiwst fiewd */
	if (!fbuf)
		wetuwn;

	if (fbuf->wast_fiewd)
		v4w2_m2m_buf_done(fbuf->vb, VB2_BUF_STATE_DONE);
}

static void fdp1_queue_fiewd(stwuct fdp1_ctx *ctx,
			     stwuct fdp1_fiewd_buffew *fbuf)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->fdp1->iwqwock, fwags);
	wist_add_taiw(&fbuf->wist, &ctx->fiewds_queue);
	spin_unwock_iwqwestowe(&ctx->fdp1->iwqwock, fwags);

	ctx->buffews_queued++;
}

static stwuct fdp1_fiewd_buffew *fdp1_dequeue_fiewd(stwuct fdp1_ctx *ctx)
{
	stwuct fdp1_fiewd_buffew *fbuf;
	unsigned wong fwags;

	ctx->buffews_queued--;

	spin_wock_iwqsave(&ctx->fdp1->iwqwock, fwags);
	fbuf = wist_fiwst_entwy_ow_nuww(&ctx->fiewds_queue,
					stwuct fdp1_fiewd_buffew, wist);
	if (fbuf)
		wist_dew(&fbuf->wist);
	spin_unwock_iwqwestowe(&ctx->fdp1->iwqwock, fwags);

	wetuwn fbuf;
}

/*
 * Wetuwn the next fiewd in the queue - ow NUWW,
 * without wemoving the item fwom the wist
 */
static stwuct fdp1_fiewd_buffew *fdp1_peek_queued_fiewd(stwuct fdp1_ctx *ctx)
{
	stwuct fdp1_fiewd_buffew *fbuf;
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->fdp1->iwqwock, fwags);
	fbuf = wist_fiwst_entwy_ow_nuww(&ctx->fiewds_queue,
					stwuct fdp1_fiewd_buffew, wist);
	spin_unwock_iwqwestowe(&ctx->fdp1->iwqwock, fwags);

	wetuwn fbuf;
}

static u32 fdp1_wead(stwuct fdp1_dev *fdp1, unsigned int weg)
{
	u32 vawue = iowead32(fdp1->wegs + weg);

	if (debug >= 2)
		dpwintk(fdp1, "Wead 0x%08x fwom 0x%04x\n", vawue, weg);

	wetuwn vawue;
}

static void fdp1_wwite(stwuct fdp1_dev *fdp1, u32 vaw, unsigned int weg)
{
	if (debug >= 2)
		dpwintk(fdp1, "Wwite 0x%08x to 0x%04x\n", vaw, weg);

	iowwite32(vaw, fdp1->wegs + weg);
}

/* IPC wegistews awe to be pwogwammed with constant vawues */
static void fdp1_set_ipc_dwi(stwuct fdp1_ctx *ctx)
{
	stwuct fdp1_dev *fdp1 = ctx->fdp1;

	fdp1_wwite(fdp1, FD1_IPC_SMSK_THWESH_CONST,	FD1_IPC_SMSK_THWESH);
	fdp1_wwite(fdp1, FD1_IPC_COMB_DET_CONST,	FD1_IPC_COMB_DET);
	fdp1_wwite(fdp1, FD1_IPC_MOTDEC_CONST,	FD1_IPC_MOTDEC);

	fdp1_wwite(fdp1, FD1_IPC_DWI_BWEND_CONST,	FD1_IPC_DWI_BWEND);
	fdp1_wwite(fdp1, FD1_IPC_DWI_HGAIN_CONST,	FD1_IPC_DWI_HGAIN);
	fdp1_wwite(fdp1, FD1_IPC_DWI_SPWS_CONST,	FD1_IPC_DWI_SPWS);
	fdp1_wwite(fdp1, FD1_IPC_DWI_ANGWE_CONST,	FD1_IPC_DWI_ANGWE);
	fdp1_wwite(fdp1, FD1_IPC_DWI_ISOPIX0_CONST,	FD1_IPC_DWI_ISOPIX0);
	fdp1_wwite(fdp1, FD1_IPC_DWI_ISOPIX1_CONST,	FD1_IPC_DWI_ISOPIX1);
}


static void fdp1_set_ipc_sensow(stwuct fdp1_ctx *ctx)
{
	stwuct fdp1_dev *fdp1 = ctx->fdp1;
	stwuct fdp1_q_data *swc_q_data = &ctx->out_q;
	unsigned int x0, x1;
	unsigned int hsize = swc_q_data->fowmat.width;
	unsigned int vsize = swc_q_data->fowmat.height;

	x0 = hsize / 3;
	x1 = 2 * hsize / 3;

	fdp1_wwite(fdp1, FD1_IPC_SENSOW_TH0_CONST, FD1_IPC_SENSOW_TH0);
	fdp1_wwite(fdp1, FD1_IPC_SENSOW_TH1_CONST, FD1_IPC_SENSOW_TH1);
	fdp1_wwite(fdp1, FD1_IPC_SENSOW_CTW0_CONST, FD1_IPC_SENSOW_CTW0);
	fdp1_wwite(fdp1, FD1_IPC_SENSOW_CTW1_CONST, FD1_IPC_SENSOW_CTW1);

	fdp1_wwite(fdp1, ((hsize - 1) << FD1_IPC_SENSOW_CTW2_X_SHIFT) |
			 ((vsize - 1) << FD1_IPC_SENSOW_CTW2_Y_SHIFT),
			 FD1_IPC_SENSOW_CTW2);

	fdp1_wwite(fdp1, (x0 << FD1_IPC_SENSOW_CTW3_0_SHIFT) |
			 (x1 << FD1_IPC_SENSOW_CTW3_1_SHIFT),
			 FD1_IPC_SENSOW_CTW3);
}

/*
 * fdp1_wwite_wut: Wwite a padded WUT to the hw
 *
 * FDP1 uses constant data fow de-intewwacing pwocessing,
 * with wawge tabwes. These hawdwawe tabwes awe aww 256 bytes
 * wong, howevew they often contain wepeated data at the end.
 *
 * The wast byte of the tabwe is wwitten to aww wemaining entwies.
 */
static void fdp1_wwite_wut(stwuct fdp1_dev *fdp1, const u8 *wut,
			   unsigned int wen, unsigned int base)
{
	unsigned int i;
	u8 pad;

	/* Tabwes wawgew than the hw awe cwipped */
	wen = min(wen, 256u);

	fow (i = 0; i < wen; i++)
		fdp1_wwite(fdp1, wut[i], base + (i*4));

	/* Tabwes awe padded with the wast entwy */
	pad = wut[i-1];

	fow (; i < 256; i++)
		fdp1_wwite(fdp1, pad, base + (i*4));
}

static void fdp1_set_wut(stwuct fdp1_dev *fdp1)
{
	fdp1_wwite_wut(fdp1, fdp1_diff_adj, AWWAY_SIZE(fdp1_diff_adj),
			FD1_WUT_DIF_ADJ);
	fdp1_wwite_wut(fdp1, fdp1_sad_adj,  AWWAY_SIZE(fdp1_sad_adj),
			FD1_WUT_SAD_ADJ);
	fdp1_wwite_wut(fdp1, fdp1_bwd_gain, AWWAY_SIZE(fdp1_bwd_gain),
			FD1_WUT_BWD_GAIN);
	fdp1_wwite_wut(fdp1, fdp1_dif_gain, AWWAY_SIZE(fdp1_dif_gain),
			FD1_WUT_DIF_GAIN);
	fdp1_wwite_wut(fdp1, fdp1_mdet, AWWAY_SIZE(fdp1_mdet),
			FD1_WUT_MDET);
}

static void fdp1_configuwe_wpf(stwuct fdp1_ctx *ctx,
			       stwuct fdp1_job *job)
{
	stwuct fdp1_dev *fdp1 = ctx->fdp1;
	u32 pictuwe_size;
	u32 pstwide;
	u32 fowmat;
	u32 smsk_addw;

	stwuct fdp1_q_data *q_data = &ctx->out_q;

	/* Pictuwe size is common to Souwce and Destination fwames */
	pictuwe_size = (q_data->fowmat.width << FD1_WPF_SIZE_H_SHIFT)
		     | (q_data->vsize << FD1_WPF_SIZE_V_SHIFT);

	/* Stwides */
	pstwide = q_data->stwide_y << FD1_WPF_PSTWIDE_Y_SHIFT;
	if (q_data->fowmat.num_pwanes > 1)
		pstwide |= q_data->stwide_c << FD1_WPF_PSTWIDE_C_SHIFT;

	/* Fowmat contwow */
	fowmat = q_data->fmt->fmt;
	if (q_data->fmt->swap_yc)
		fowmat |= FD1_WPF_FOWMAT_WSPYCS;

	if (q_data->fmt->swap_uv)
		fowmat |= FD1_WPF_FOWMAT_WSPUVS;

	if (job->active->fiewd == V4W2_FIEWD_BOTTOM) {
		fowmat |= FD1_WPF_FOWMAT_CF; /* Set fow Bottom fiewd */
		smsk_addw = ctx->smsk_addw[0];
	} ewse {
		smsk_addw = ctx->smsk_addw[1];
	}

	/* Deint mode is non-zewo when deintewwacing */
	if (ctx->deint_mode)
		fowmat |= FD1_WPF_FOWMAT_CIPM;

	fdp1_wwite(fdp1, fowmat, FD1_WPF_FOWMAT);
	fdp1_wwite(fdp1, q_data->fmt->swap, FD1_WPF_SWAP);
	fdp1_wwite(fdp1, pictuwe_size, FD1_WPF_SIZE);
	fdp1_wwite(fdp1, pstwide, FD1_WPF_PSTWIDE);
	fdp1_wwite(fdp1, smsk_addw, FD1_WPF_SMSK_ADDW);

	/* Pwevious Fiewd Channew (CH0) */
	if (job->pwevious)
		fdp1_wwite(fdp1, job->pwevious->addws[0], FD1_WPF0_ADDW_Y);

	/* Cuwwent Fiewd Channew (CH1) */
	fdp1_wwite(fdp1, job->active->addws[0], FD1_WPF1_ADDW_Y);
	fdp1_wwite(fdp1, job->active->addws[1], FD1_WPF1_ADDW_C0);
	fdp1_wwite(fdp1, job->active->addws[2], FD1_WPF1_ADDW_C1);

	/* Next Fiewd  Channew (CH2) */
	if (job->next)
		fdp1_wwite(fdp1, job->next->addws[0], FD1_WPF2_ADDW_Y);
}

static void fdp1_configuwe_wpf(stwuct fdp1_ctx *ctx,
			       stwuct fdp1_job *job)
{
	stwuct fdp1_dev *fdp1 = ctx->fdp1;
	stwuct fdp1_q_data *swc_q_data = &ctx->out_q;
	stwuct fdp1_q_data *q_data = &ctx->cap_q;
	u32 pstwide;
	u32 fowmat;
	u32 swap;
	u32 wndctw;

	pstwide = q_data->fowmat.pwane_fmt[0].bytespewwine
		<< FD1_WPF_PSTWIDE_Y_SHIFT;

	if (q_data->fowmat.num_pwanes > 1)
		pstwide |= q_data->fowmat.pwane_fmt[1].bytespewwine
			<< FD1_WPF_PSTWIDE_C_SHIFT;

	fowmat = q_data->fmt->fmt; /* Output Fowmat Code */

	if (q_data->fmt->swap_yc)
		fowmat |= FD1_WPF_FOWMAT_WSPYCS;

	if (q_data->fmt->swap_uv)
		fowmat |= FD1_WPF_FOWMAT_WSPUVS;

	if (fdp1_fmt_is_wgb(q_data->fmt)) {
		/* Enabwe Cowouw Space convewsion */
		fowmat |= FD1_WPF_FOWMAT_CSC;

		/* Set WWTM */
		if (swc_q_data->fowmat.ycbcw_enc == V4W2_YCBCW_ENC_709)
			fowmat |= FD1_WPF_FOWMAT_WWTM_709_16;
		ewse if (swc_q_data->fowmat.quantization ==
				V4W2_QUANTIZATION_FUWW_WANGE)
			fowmat |= FD1_WPF_FOWMAT_WWTM_601_0;
		ewse
			fowmat |= FD1_WPF_FOWMAT_WWTM_601_16;
	}

	/* Set an awpha vawue into the Pad Vawue */
	fowmat |= ctx->awpha << FD1_WPF_FOWMAT_PDV_SHIFT;

	/* Detewmine pictuwe wounding and cwipping */
	wndctw = FD1_WPF_WNDCTW_CBWM; /* Wounding Off */
	wndctw |= FD1_WPF_WNDCTW_CWMD_NOCWIP;

	/* WPF Swap needs both ISWAP and OSWAP setting */
	swap = q_data->fmt->swap << FD1_WPF_SWAP_OSWAP_SHIFT;
	swap |= swc_q_data->fmt->swap << FD1_WPF_SWAP_SSWAP_SHIFT;

	fdp1_wwite(fdp1, fowmat, FD1_WPF_FOWMAT);
	fdp1_wwite(fdp1, wndctw, FD1_WPF_WNDCTW);
	fdp1_wwite(fdp1, swap, FD1_WPF_SWAP);
	fdp1_wwite(fdp1, pstwide, FD1_WPF_PSTWIDE);

	fdp1_wwite(fdp1, job->dst->addws[0], FD1_WPF_ADDW_Y);
	fdp1_wwite(fdp1, job->dst->addws[1], FD1_WPF_ADDW_C0);
	fdp1_wwite(fdp1, job->dst->addws[2], FD1_WPF_ADDW_C1);
}

static void fdp1_configuwe_deint_mode(stwuct fdp1_ctx *ctx,
				      stwuct fdp1_job *job)
{
	stwuct fdp1_dev *fdp1 = ctx->fdp1;
	u32 opmode = FD1_CTW_OPMODE_VIMD_NOINTEWWUPT;
	u32 ipcmode = FD1_IPC_MODE_DWI; /* Awways set */
	u32 channews = FD1_CTW_CHACT_WW | FD1_CTW_CHACT_WD1; /* Awways on */

	/* De-intewwacing Mode */
	switch (ctx->deint_mode) {
	defauwt:
	case FDP1_PWOGWESSIVE:
		dpwintk(fdp1, "Pwogwessive Mode\n");
		opmode |= FD1_CTW_OPMODE_PWG;
		ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		bweak;
	case FDP1_ADAPT2D3D:
		dpwintk(fdp1, "Adapt2D3D Mode\n");
		if (ctx->sequence == 0 || ctx->abowting)
			ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		ewse
			ipcmode |= FD1_IPC_MODE_DIM_ADAPT2D3D;

		if (ctx->sequence > 1) {
			channews |= FD1_CTW_CHACT_SMW;
			channews |= FD1_CTW_CHACT_WD0 | FD1_CTW_CHACT_WD2;
		}

		if (ctx->sequence > 2)
			channews |= FD1_CTW_CHACT_SMW;

		bweak;
	case FDP1_FIXED3D:
		dpwintk(fdp1, "Fixed 3D Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_FIXED3D;
		/* Except fow fiwst and wast fwame, enabwe aww channews */
		if (!(ctx->sequence == 0 || ctx->abowting))
			channews |= FD1_CTW_CHACT_WD0 | FD1_CTW_CHACT_WD2;
		bweak;
	case FDP1_FIXED2D:
		dpwintk(fdp1, "Fixed 2D Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_FIXED2D;
		/* No extwa channews enabwed */
		bweak;
	case FDP1_PWEVFIEWD:
		dpwintk(fdp1, "Pwevious Fiewd Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_PWEVFIEWD;
		channews |= FD1_CTW_CHACT_WD0; /* Pwevious */
		bweak;
	case FDP1_NEXTFIEWD:
		dpwintk(fdp1, "Next Fiewd Mode\n");
		ipcmode |= FD1_IPC_MODE_DIM_NEXTFIEWD;
		channews |= FD1_CTW_CHACT_WD2; /* Next */
		bweak;
	}

	fdp1_wwite(fdp1, channews,	FD1_CTW_CHACT);
	fdp1_wwite(fdp1, opmode,	FD1_CTW_OPMODE);
	fdp1_wwite(fdp1, ipcmode,	FD1_IPC_MODE);
}

/*
 * fdp1_device_pwocess() - Wun the hawdwawe
 *
 * Configuwe and stawt the hawdwawe to genewate a singwe fwame
 * of output given ouw input pawametews.
 */
static int fdp1_device_pwocess(stwuct fdp1_ctx *ctx)

{
	stwuct fdp1_dev *fdp1 = ctx->fdp1;
	stwuct fdp1_job *job;
	unsigned wong fwags;

	spin_wock_iwqsave(&fdp1->device_pwocess_wock, fwags);

	/* Get a job to pwocess */
	job = get_queued_job(fdp1);
	if (!job) {
		/*
		 * VINT can caww us to see if we can queue anothew job.
		 * If we have no wowk to do, we simpwy wetuwn.
		 */
		spin_unwock_iwqwestowe(&fdp1->device_pwocess_wock, fwags);
		wetuwn 0;
	}

	/* Fiwst Fwame onwy? ... */
	fdp1_wwite(fdp1, FD1_CTW_CWKCTWW_CSTP_N, FD1_CTW_CWKCTWW);

	/* Set the mode, and configuwation */
	fdp1_configuwe_deint_mode(ctx, job);

	/* DWI Static Configuwation */
	fdp1_set_ipc_dwi(ctx);

	/* Sensow Configuwation */
	fdp1_set_ipc_sensow(ctx);

	/* Setup the souwce pictuwe */
	fdp1_configuwe_wpf(ctx, job);

	/* Setup the destination pictuwe */
	fdp1_configuwe_wpf(ctx, job);

	/* Wine Memowy Pixew Numbew Wegistew fow wineaw access */
	fdp1_wwite(fdp1, FD1_IPC_WMEM_WINEAW, FD1_IPC_WMEM);

	/* Enabwe Intewwupts */
	fdp1_wwite(fdp1, FD1_CTW_IWQ_MASK, FD1_CTW_IWQENB);

	/* Finawwy, the Immediate Wegistews */

	/* This job is now in the HW queue */
	queue_hw_job(fdp1, job);

	/* Stawt the command */
	fdp1_wwite(fdp1, FD1_CTW_CMD_STWCMD, FD1_CTW_CMD);

	/* Wegistews wiww update to HW at next VINT */
	fdp1_wwite(fdp1, FD1_CTW_WEGEND_WEGEND, FD1_CTW_WEGEND);

	/* Enabwe VINT Genewatow */
	fdp1_wwite(fdp1, FD1_CTW_SGCMD_SGEN, FD1_CTW_SGCMD);

	spin_unwock_iwqwestowe(&fdp1->device_pwocess_wock, fwags);

	wetuwn 0;
}

/*
 * mem2mem cawwbacks
 */

/*
 * job_weady() - check whethew an instance is weady to be scheduwed to wun
 */
static int fdp1_m2m_job_weady(void *pwiv)
{
	stwuct fdp1_ctx *ctx = pwiv;
	stwuct fdp1_q_data *swc_q_data = &ctx->out_q;
	int swcbufs = 1;
	int dstbufs = 1;

	dpwintk(ctx->fdp1, "+ Swc: %d : Dst: %d\n",
		v4w2_m2m_num_swc_bufs_weady(ctx->fh.m2m_ctx),
		v4w2_m2m_num_dst_bufs_weady(ctx->fh.m2m_ctx));

	/* One output buffew is wequiwed fow each fiewd */
	if (V4W2_FIEWD_HAS_BOTH(swc_q_data->fowmat.fiewd))
		dstbufs = 2;

	if (v4w2_m2m_num_swc_bufs_weady(ctx->fh.m2m_ctx) < swcbufs
	    || v4w2_m2m_num_dst_bufs_weady(ctx->fh.m2m_ctx) < dstbufs) {
		dpwintk(ctx->fdp1, "Not enough buffews avaiwabwe\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static void fdp1_m2m_job_abowt(void *pwiv)
{
	stwuct fdp1_ctx *ctx = pwiv;

	dpwintk(ctx->fdp1, "+\n");

	/* Wiww cancew the twansaction in the next intewwupt handwew */
	ctx->abowting = 1;

	/* Immediate abowt sequence */
	fdp1_wwite(ctx->fdp1, 0, FD1_CTW_SGCMD);
	fdp1_wwite(ctx->fdp1, FD1_CTW_SWESET_SWST, FD1_CTW_SWESET);
}

/*
 * fdp1_pwepawe_job: Pwepawe and queue a new job fow a singwe action of wowk
 *
 * Pwepawe the next fiewd, (ow fwame in pwogwessive) and an output
 * buffew fow the hawdwawe to pewfowm a singwe opewation.
 */
static stwuct fdp1_job *fdp1_pwepawe_job(stwuct fdp1_ctx *ctx)
{
	stwuct vb2_v4w2_buffew *vbuf;
	stwuct fdp1_buffew *fbuf;
	stwuct fdp1_dev *fdp1 = ctx->fdp1;
	stwuct fdp1_job *job;
	unsigned int buffews_wequiwed = 1;

	dpwintk(fdp1, "+\n");

	if (FDP1_DEINT_MODE_USES_NEXT(ctx->deint_mode))
		buffews_wequiwed = 2;

	if (ctx->buffews_queued < buffews_wequiwed)
		wetuwn NUWW;

	job = fdp1_job_awwoc(fdp1);
	if (!job) {
		dpwintk(fdp1, "No fwee jobs cuwwentwy avaiwabwe\n");
		wetuwn NUWW;
	}

	job->active = fdp1_dequeue_fiewd(ctx);
	if (!job->active) {
		/* Buffew check shouwd pwevent this evew happening */
		dpwintk(fdp1, "No input buffews cuwwentwy avaiwabwe\n");

		fdp1_job_fwee(fdp1, job);
		wetuwn NUWW;
	}

	dpwintk(fdp1, "+ Buffew en-woute...\n");

	/* Souwce buffews have been pwepawed on ouw buffew_queue
	 * Pwepawe ouw Output buffew
	 */
	vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
	fbuf = to_fdp1_buffew(vbuf);
	job->dst = &fbuf->fiewds[0];

	job->active->vb->sequence = ctx->sequence;
	job->dst->vb->sequence = ctx->sequence;
	ctx->sequence++;

	if (FDP1_DEINT_MODE_USES_PWEV(ctx->deint_mode)) {
		job->pwevious = ctx->pwevious;

		/* Active buffew becomes the next job's pwevious buffew */
		ctx->pwevious = job->active;
	}

	if (FDP1_DEINT_MODE_USES_NEXT(ctx->deint_mode)) {
		/* Must be cawwed aftew 'active' is dequeued */
		job->next = fdp1_peek_queued_fiewd(ctx);
	}

	/* Twansfew timestamps and fwags fwom swc->dst */

	job->dst->vb->vb2_buf.timestamp = job->active->vb->vb2_buf.timestamp;

	job->dst->vb->fwags = job->active->vb->fwags &
				V4W2_BUF_FWAG_TSTAMP_SWC_MASK;

	/* Ideawwy, the fwame-end function wiww just 'check' to see
	 * if thewe awe mowe jobs instead
	 */
	ctx->twanswen++;

	/* Finawwy, Put this job on the pwocessing queue */
	queue_job(fdp1, job);

	dpwintk(fdp1, "Job Queued twanswen = %d\n", ctx->twanswen);

	wetuwn job;
}

/* fdp1_m2m_device_wun() - pwepawes and stawts the device fow an M2M task
 *
 * A singwe input buffew is taken and sewiawised into ouw fdp1_buffew
 * queue. The queue is then pwocessed to cweate as many jobs as possibwe
 * fwom ouw avaiwabwe input.
 */
static void fdp1_m2m_device_wun(void *pwiv)
{
	stwuct fdp1_ctx *ctx = pwiv;
	stwuct fdp1_dev *fdp1 = ctx->fdp1;
	stwuct vb2_v4w2_buffew *swc_vb;
	stwuct fdp1_buffew *buf;
	unsigned int i;

	dpwintk(fdp1, "+\n");

	ctx->twanswen = 0;

	/* Get ouw incoming buffew of eithew one ow two fiewds, ow one fwame */
	swc_vb = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	buf = to_fdp1_buffew(swc_vb);

	fow (i = 0; i < buf->num_fiewds; i++) {
		stwuct fdp1_fiewd_buffew *fbuf = &buf->fiewds[i];

		fdp1_queue_fiewd(ctx, fbuf);
		dpwintk(fdp1, "Queued Buffew [%d] wast_fiewd:%d\n",
			i, fbuf->wast_fiewd);
	}

	/* Queue as many jobs as ouw data pwovides fow */
	whiwe (fdp1_pwepawe_job(ctx))
		;

	if (ctx->twanswen == 0) {
		dpwintk(fdp1, "No jobs wewe pwocessed. M2M action compwete\n");
		v4w2_m2m_job_finish(fdp1->m2m_dev, ctx->fh.m2m_ctx);
		wetuwn;
	}

	/* Kick the job pwocessing action */
	fdp1_device_pwocess(ctx);
}

/*
 * device_fwame_end:
 *
 * Handwes the M2M wevew aftew a buffew compwetion event.
 */
static void device_fwame_end(stwuct fdp1_dev *fdp1,
			     enum vb2_buffew_state state)
{
	stwuct fdp1_ctx *ctx;
	unsigned wong fwags;
	stwuct fdp1_job *job = get_hw_queued_job(fdp1);

	dpwintk(fdp1, "+\n");

	ctx = v4w2_m2m_get_cuww_pwiv(fdp1->m2m_dev);

	if (ctx == NUWW) {
		v4w2_eww(&fdp1->v4w2_dev,
			"Instance weweased befowe the end of twansaction\n");
		wetuwn;
	}

	ctx->num_pwocessed++;

	/*
	 * fdp1_fiewd_compwete wiww caww buf_done onwy when the wast vb2_buffew
	 * wefewence is compwete
	 */
	if (FDP1_DEINT_MODE_USES_PWEV(ctx->deint_mode))
		fdp1_fiewd_compwete(ctx, job->pwevious);
	ewse
		fdp1_fiewd_compwete(ctx, job->active);

	spin_wock_iwqsave(&fdp1->iwqwock, fwags);
	v4w2_m2m_buf_done(job->dst->vb, state);
	job->dst = NUWW;
	spin_unwock_iwqwestowe(&fdp1->iwqwock, fwags);

	/* Move this job back to the fwee job wist */
	fdp1_job_fwee(fdp1, job);

	dpwintk(fdp1, "cuww_ctx->num_pwocessed %d cuww_ctx->twanswen %d\n",
		ctx->num_pwocessed, ctx->twanswen);

	if (ctx->num_pwocessed == ctx->twanswen ||
			ctx->abowting) {
		dpwintk(ctx->fdp1, "Finishing twansaction\n");
		ctx->num_pwocessed = 0;
		v4w2_m2m_job_finish(fdp1->m2m_dev, ctx->fh.m2m_ctx);
	} ewse {
		/*
		 * Fow pipewined pewfowmance suppowt, this wouwd
		 * be cawwed fwom a VINT handwew
		 */
		fdp1_device_pwocess(ctx);
	}
}

/*
 * video ioctws
 */
static int fdp1_vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, DWIVEW_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:%s", DWIVEW_NAME);
	wetuwn 0;
}

static int fdp1_enum_fmt(stwuct v4w2_fmtdesc *f, u32 type)
{
	unsigned int i, num;

	num = 0;

	fow (i = 0; i < AWWAY_SIZE(fdp1_fowmats); ++i) {
		if (fdp1_fowmats[i].types & type) {
			if (num == f->index)
				bweak;
			++num;
		}
	}

	/* Fowmat not found */
	if (i >= AWWAY_SIZE(fdp1_fowmats))
		wetuwn -EINVAW;

	/* Fowmat found */
	f->pixewfowmat = fdp1_fowmats[i].fouwcc;

	wetuwn 0;
}

static int fdp1_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fmtdesc *f)
{
	wetuwn fdp1_enum_fmt(f, FDP1_CAPTUWE);
}

static int fdp1_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn fdp1_enum_fmt(f, FDP1_OUTPUT);
}

static int fdp1_g_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct fdp1_q_data *q_data;
	stwuct fdp1_ctx *ctx = fh_to_ctx(pwiv);

	if (!v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type))
		wetuwn -EINVAW;

	q_data = get_q_data(ctx, f->type);
	f->fmt.pix_mp = q_data->fowmat;

	wetuwn 0;
}

static void fdp1_compute_stwide(stwuct v4w2_pix_fowmat_mpwane *pix,
				const stwuct fdp1_fmt *fmt)
{
	unsigned int i;

	/* Compute and cwamp the stwide and image size. */
	fow (i = 0; i < min_t(unsigned int, fmt->num_pwanes, 2U); ++i) {
		unsigned int hsub = i > 0 ? fmt->hsub : 1;
		unsigned int vsub = i > 0 ? fmt->vsub : 1;
		 /* Fwom VSP : TODO: Confiwm awignment wimits fow FDP1 */
		unsigned int awign = 128;
		unsigned int bpw;

		bpw = cwamp_t(unsigned int, pix->pwane_fmt[i].bytespewwine,
			      pix->width / hsub * fmt->bpp[i] / 8,
			      wound_down(FDP1_MAX_STWIDE, awign));

		pix->pwane_fmt[i].bytespewwine = wound_up(bpw, awign);
		pix->pwane_fmt[i].sizeimage = pix->pwane_fmt[i].bytespewwine
					    * pix->height / vsub;

	}

	if (fmt->num_pwanes == 3) {
		/* The two chwoma pwanes must have the same stwide. */
		pix->pwane_fmt[2].bytespewwine = pix->pwane_fmt[1].bytespewwine;
		pix->pwane_fmt[2].sizeimage = pix->pwane_fmt[1].sizeimage;

	}
}

static void fdp1_twy_fmt_output(stwuct fdp1_ctx *ctx,
				const stwuct fdp1_fmt **fmtinfo,
				stwuct v4w2_pix_fowmat_mpwane *pix)
{
	const stwuct fdp1_fmt *fmt;
	unsigned int width;
	unsigned int height;

	/* Vawidate the pixew fowmat to ensuwe the output queue suppowts it. */
	fmt = fdp1_find_fowmat(pix->pixewfowmat);
	if (!fmt || !(fmt->types & FDP1_OUTPUT))
		fmt = fdp1_find_fowmat(V4W2_PIX_FMT_YUYV);

	if (fmtinfo)
		*fmtinfo = fmt;

	pix->pixewfowmat = fmt->fouwcc;
	pix->num_pwanes = fmt->num_pwanes;

	/*
	 * Pwogwessive video and aww intewwaced fiewd owdews awe acceptabwe.
	 * Defauwt to V4W2_FIEWD_INTEWWACED.
	 */
	if (pix->fiewd != V4W2_FIEWD_NONE &&
	    pix->fiewd != V4W2_FIEWD_AWTEWNATE &&
	    !V4W2_FIEWD_HAS_BOTH(pix->fiewd))
		pix->fiewd = V4W2_FIEWD_INTEWWACED;

	/*
	 * The deintewwacew doesn't cawe about the cowowspace, accept aww vawues
	 * and defauwt to V4W2_COWOWSPACE_SMPTE170M. The YUV to WGB convewsion
	 * at the output of the deintewwacew suppowts a subset of encodings and
	 * quantization methods and wiww onwy be avaiwabwe when the cowowspace
	 * awwows it.
	 */
	if (pix->cowowspace == V4W2_COWOWSPACE_DEFAUWT)
		pix->cowowspace = V4W2_COWOWSPACE_SMPTE170M;

	/*
	 * Awign the width and height fow YUV 4:2:2 and 4:2:0 fowmats and cwamp
	 * them to the suppowted fwame size wange. The height boundawy awe
	 * wewated to the fuww fwame, divide them by two when the fowmat passes
	 * fiewds in sepawate buffews.
	 */
	width = wound_down(pix->width, fmt->hsub);
	pix->width = cwamp(width, FDP1_MIN_W, FDP1_MAX_W);

	height = wound_down(pix->height, fmt->vsub);
	if (pix->fiewd == V4W2_FIEWD_AWTEWNATE)
		pix->height = cwamp(height, FDP1_MIN_H / 2, FDP1_MAX_H / 2);
	ewse
		pix->height = cwamp(height, FDP1_MIN_H, FDP1_MAX_H);

	fdp1_compute_stwide(pix, fmt);
}

static void fdp1_twy_fmt_captuwe(stwuct fdp1_ctx *ctx,
				 const stwuct fdp1_fmt **fmtinfo,
				 stwuct v4w2_pix_fowmat_mpwane *pix)
{
	stwuct fdp1_q_data *swc_data = &ctx->out_q;
	enum v4w2_cowowspace cowowspace;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;
	const stwuct fdp1_fmt *fmt;
	boow awwow_wgb;

	/*
	 * Vawidate the pixew fowmat. We can onwy accept WGB output fowmats if
	 * the input encoding and quantization awe compatibwe with the fowmat
	 * convewsions suppowted by the hawdwawe. The suppowted combinations awe
	 *
	 * V4W2_YCBCW_ENC_601 + V4W2_QUANTIZATION_WIM_WANGE
	 * V4W2_YCBCW_ENC_601 + V4W2_QUANTIZATION_FUWW_WANGE
	 * V4W2_YCBCW_ENC_709 + V4W2_QUANTIZATION_WIM_WANGE
	 */
	cowowspace = swc_data->fowmat.cowowspace;

	ycbcw_enc = swc_data->fowmat.ycbcw_enc;
	if (ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT)
		ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(cowowspace);

	quantization = swc_data->fowmat.quantization;
	if (quantization == V4W2_QUANTIZATION_DEFAUWT)
		quantization = V4W2_MAP_QUANTIZATION_DEFAUWT(fawse, cowowspace,
							     ycbcw_enc);

	awwow_wgb = ycbcw_enc == V4W2_YCBCW_ENC_601 ||
		    (ycbcw_enc == V4W2_YCBCW_ENC_709 &&
		     quantization == V4W2_QUANTIZATION_WIM_WANGE);

	fmt = fdp1_find_fowmat(pix->pixewfowmat);
	if (!fmt || (!awwow_wgb && fdp1_fmt_is_wgb(fmt)))
		fmt = fdp1_find_fowmat(V4W2_PIX_FMT_YUYV);

	if (fmtinfo)
		*fmtinfo = fmt;

	pix->pixewfowmat = fmt->fouwcc;
	pix->num_pwanes = fmt->num_pwanes;
	pix->fiewd = V4W2_FIEWD_NONE;

	/*
	 * The cowowspace on the captuwe queue is copied fwom the output queue
	 * as the hawdwawe can't change the cowowspace. It can convewt YCbCw to
	 * WGB though, in which case the encoding and quantization awe set to
	 * defauwt vawues as anything ewse wouwdn't make sense.
	 */
	pix->cowowspace = swc_data->fowmat.cowowspace;
	pix->xfew_func = swc_data->fowmat.xfew_func;

	if (fdp1_fmt_is_wgb(fmt)) {
		pix->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
		pix->quantization = V4W2_QUANTIZATION_DEFAUWT;
	} ewse {
		pix->ycbcw_enc = swc_data->fowmat.ycbcw_enc;
		pix->quantization = swc_data->fowmat.quantization;
	}

	/*
	 * The fwame width is identicaw to the output queue, and the height is
	 * eithew doubwed ow identicaw depending on whethew the output queue
	 * fiewd owdew contains one ow two fiewds pew fwame.
	 */
	pix->width = swc_data->fowmat.width;
	if (swc_data->fowmat.fiewd == V4W2_FIEWD_AWTEWNATE)
		pix->height = 2 * swc_data->fowmat.height;
	ewse
		pix->height = swc_data->fowmat.height;

	fdp1_compute_stwide(pix, fmt);
}

static int fdp1_twy_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct fdp1_ctx *ctx = fh_to_ctx(pwiv);

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		fdp1_twy_fmt_output(ctx, NUWW, &f->fmt.pix_mp);
	ewse
		fdp1_twy_fmt_captuwe(ctx, NUWW, &f->fmt.pix_mp);

	dpwintk(ctx->fdp1, "Twy %s fowmat: %4.4s (0x%08x) %ux%u fiewd %u\n",
		V4W2_TYPE_IS_OUTPUT(f->type) ? "output" : "captuwe",
		(chaw *)&f->fmt.pix_mp.pixewfowmat, f->fmt.pix_mp.pixewfowmat,
		f->fmt.pix_mp.width, f->fmt.pix_mp.height, f->fmt.pix_mp.fiewd);

	wetuwn 0;
}

static void fdp1_set_fowmat(stwuct fdp1_ctx *ctx,
			    stwuct v4w2_pix_fowmat_mpwane *pix,
			    enum v4w2_buf_type type)
{
	stwuct fdp1_q_data *q_data = get_q_data(ctx, type);
	const stwuct fdp1_fmt *fmtinfo;

	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		fdp1_twy_fmt_output(ctx, &fmtinfo, pix);
	ewse
		fdp1_twy_fmt_captuwe(ctx, &fmtinfo, pix);

	q_data->fmt = fmtinfo;
	q_data->fowmat = *pix;

	q_data->vsize = pix->height;
	if (pix->fiewd != V4W2_FIEWD_NONE)
		q_data->vsize /= 2;

	q_data->stwide_y = pix->pwane_fmt[0].bytespewwine;
	q_data->stwide_c = pix->pwane_fmt[1].bytespewwine;

	/* Adjust stwides fow intewweaved buffews */
	if (pix->fiewd == V4W2_FIEWD_INTEWWACED ||
	    pix->fiewd == V4W2_FIEWD_INTEWWACED_TB ||
	    pix->fiewd == V4W2_FIEWD_INTEWWACED_BT) {
		q_data->stwide_y *= 2;
		q_data->stwide_c *= 2;
	}

	/* Pwopagate the fowmat fwom the output node to the captuwe node. */
	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		stwuct fdp1_q_data *dst_data = &ctx->cap_q;

		/*
		 * Copy the fowmat, cweaw the pew-pwane bytes pew wine and image
		 * size, ovewwide the fiewd and doubwe the height if needed.
		 */
		dst_data->fowmat = q_data->fowmat;
		memset(dst_data->fowmat.pwane_fmt, 0,
		       sizeof(dst_data->fowmat.pwane_fmt));

		dst_data->fowmat.fiewd = V4W2_FIEWD_NONE;
		if (pix->fiewd == V4W2_FIEWD_AWTEWNATE)
			dst_data->fowmat.height *= 2;

		fdp1_twy_fmt_captuwe(ctx, &dst_data->fmt, &dst_data->fowmat);

		dst_data->vsize = dst_data->fowmat.height;
		dst_data->stwide_y = dst_data->fowmat.pwane_fmt[0].bytespewwine;
		dst_data->stwide_c = dst_data->fowmat.pwane_fmt[1].bytespewwine;
	}
}

static int fdp1_s_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct fdp1_ctx *ctx = fh_to_ctx(pwiv);
	stwuct v4w2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	stwuct vb2_queue *vq = v4w2_m2m_get_vq(m2m_ctx, f->type);

	if (vb2_is_busy(vq)) {
		v4w2_eww(&ctx->fdp1->v4w2_dev, "%s queue busy\n", __func__);
		wetuwn -EBUSY;
	}

	fdp1_set_fowmat(ctx, &f->fmt.pix_mp, f->type);

	dpwintk(ctx->fdp1, "Set %s fowmat: %4.4s (0x%08x) %ux%u fiewd %u\n",
		V4W2_TYPE_IS_OUTPUT(f->type) ? "output" : "captuwe",
		(chaw *)&f->fmt.pix_mp.pixewfowmat, f->fmt.pix_mp.pixewfowmat,
		f->fmt.pix_mp.width, f->fmt.pix_mp.height, f->fmt.pix_mp.fiewd);

	wetuwn 0;
}

static int fdp1_g_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct fdp1_ctx *ctx =
		containew_of(ctww->handwew, stwuct fdp1_ctx, hdw);
	stwuct fdp1_q_data *swc_q_data = &ctx->out_q;

	switch (ctww->id) {
	case V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE:
		if (V4W2_FIEWD_HAS_BOTH(swc_q_data->fowmat.fiewd))
			ctww->vaw = 2;
		ewse
			ctww->vaw = 1;
		wetuwn 0;
	}

	wetuwn 1;
}

static int fdp1_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct fdp1_ctx *ctx =
		containew_of(ctww->handwew, stwuct fdp1_ctx, hdw);

	switch (ctww->id) {
	case V4W2_CID_AWPHA_COMPONENT:
		ctx->awpha = ctww->vaw;
		bweak;

	case V4W2_CID_DEINTEWWACING_MODE:
		ctx->deint_mode = ctww->vaw;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops fdp1_ctww_ops = {
	.s_ctww = fdp1_s_ctww,
	.g_vowatiwe_ctww = fdp1_g_ctww,
};

static const chaw * const fdp1_ctww_deint_menu[] = {
	"Pwogwessive",
	"Adaptive 2D/3D",
	"Fixed 2D",
	"Fixed 3D",
	"Pwevious fiewd",
	"Next fiewd",
	NUWW
};

static const stwuct v4w2_ioctw_ops fdp1_ioctw_ops = {
	.vidioc_quewycap	= fdp1_vidioc_quewycap,

	.vidioc_enum_fmt_vid_cap	= fdp1_enum_fmt_vid_cap,
	.vidioc_enum_fmt_vid_out	= fdp1_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_cap_mpwane	= fdp1_g_fmt,
	.vidioc_g_fmt_vid_out_mpwane	= fdp1_g_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane	= fdp1_twy_fmt,
	.vidioc_twy_fmt_vid_out_mpwane	= fdp1_twy_fmt,
	.vidioc_s_fmt_vid_cap_mpwane	= fdp1_s_fmt,
	.vidioc_s_fmt_vid_out_mpwane	= fdp1_s_fmt,

	.vidioc_weqbufs		= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf	= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf		= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf		= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf	= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs	= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf		= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon	= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff	= v4w2_m2m_ioctw_stweamoff,

	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

/*
 * Queue opewations
 */

static int fdp1_queue_setup(stwuct vb2_queue *vq,
				unsigned int *nbuffews, unsigned int *npwanes,
				unsigned int sizes[],
				stwuct device *awwoc_ctxs[])
{
	stwuct fdp1_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct fdp1_q_data *q_data;
	unsigned int i;

	q_data = get_q_data(ctx, vq->type);

	if (*npwanes) {
		if (*npwanes > FDP1_MAX_PWANES)
			wetuwn -EINVAW;

		wetuwn 0;
	}

	*npwanes = q_data->fowmat.num_pwanes;

	fow (i = 0; i < *npwanes; i++)
		sizes[i] = q_data->fowmat.pwane_fmt[i].sizeimage;

	wetuwn 0;
}

static void fdp1_buf_pwepawe_fiewd(stwuct fdp1_q_data *q_data,
				   stwuct vb2_v4w2_buffew *vbuf,
				   unsigned int fiewd_num)
{
	stwuct fdp1_buffew *buf = to_fdp1_buffew(vbuf);
	stwuct fdp1_fiewd_buffew *fbuf = &buf->fiewds[fiewd_num];
	unsigned int num_fiewds;
	unsigned int i;

	num_fiewds = V4W2_FIEWD_HAS_BOTH(vbuf->fiewd) ? 2 : 1;

	fbuf->vb = vbuf;
	fbuf->wast_fiewd = (fiewd_num + 1) == num_fiewds;

	fow (i = 0; i < vbuf->vb2_buf.num_pwanes; ++i)
		fbuf->addws[i] = vb2_dma_contig_pwane_dma_addw(&vbuf->vb2_buf, i);

	switch (vbuf->fiewd) {
	case V4W2_FIEWD_INTEWWACED:
		/*
		 * Intewwaced means bottom-top fow 60Hz TV standawds (NTSC) and
		 * top-bottom fow 50Hz. As TV standawds awe not appwicabwe to
		 * the mem-to-mem API, use the height as a heuwistic.
		 */
		fbuf->fiewd = (q_data->fowmat.height < 576) == fiewd_num
			    ? V4W2_FIEWD_TOP : V4W2_FIEWD_BOTTOM;
		bweak;
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_SEQ_TB:
		fbuf->fiewd = fiewd_num ? V4W2_FIEWD_BOTTOM : V4W2_FIEWD_TOP;
		bweak;
	case V4W2_FIEWD_INTEWWACED_BT:
	case V4W2_FIEWD_SEQ_BT:
		fbuf->fiewd = fiewd_num ? V4W2_FIEWD_TOP : V4W2_FIEWD_BOTTOM;
		bweak;
	defauwt:
		fbuf->fiewd = vbuf->fiewd;
		bweak;
	}

	/* Buffew is compweted */
	if (!fiewd_num)
		wetuwn;

	/* Adjust buffew addwesses fow second fiewd */
	switch (vbuf->fiewd) {
	case V4W2_FIEWD_INTEWWACED:
	case V4W2_FIEWD_INTEWWACED_TB:
	case V4W2_FIEWD_INTEWWACED_BT:
		fow (i = 0; i < vbuf->vb2_buf.num_pwanes; i++)
			fbuf->addws[i] +=
				(i == 0 ? q_data->stwide_y : q_data->stwide_c);
		bweak;
	case V4W2_FIEWD_SEQ_TB:
	case V4W2_FIEWD_SEQ_BT:
		fow (i = 0; i < vbuf->vb2_buf.num_pwanes; i++)
			fbuf->addws[i] += q_data->vsize *
				(i == 0 ? q_data->stwide_y : q_data->stwide_c);
		bweak;
	}
}

static int fdp1_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct fdp1_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct fdp1_q_data *q_data = get_q_data(ctx, vb->vb2_queue->type);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct fdp1_buffew *buf = to_fdp1_buffew(vbuf);
	unsigned int i;

	if (V4W2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		boow fiewd_vawid = twue;

		/* Vawidate the buffew fiewd. */
		switch (q_data->fowmat.fiewd) {
		case V4W2_FIEWD_NONE:
			if (vbuf->fiewd != V4W2_FIEWD_NONE)
				fiewd_vawid = fawse;
			bweak;

		case V4W2_FIEWD_AWTEWNATE:
			if (vbuf->fiewd != V4W2_FIEWD_TOP &&
			    vbuf->fiewd != V4W2_FIEWD_BOTTOM)
				fiewd_vawid = fawse;
			bweak;

		case V4W2_FIEWD_INTEWWACED:
		case V4W2_FIEWD_SEQ_TB:
		case V4W2_FIEWD_SEQ_BT:
		case V4W2_FIEWD_INTEWWACED_TB:
		case V4W2_FIEWD_INTEWWACED_BT:
			if (vbuf->fiewd != q_data->fowmat.fiewd)
				fiewd_vawid = fawse;
			bweak;
		}

		if (!fiewd_vawid) {
			dpwintk(ctx->fdp1,
				"buffew fiewd %u invawid fow fowmat fiewd %u\n",
				vbuf->fiewd, q_data->fowmat.fiewd);
			wetuwn -EINVAW;
		}
	} ewse {
		vbuf->fiewd = V4W2_FIEWD_NONE;
	}

	/* Vawidate the pwanes sizes. */
	fow (i = 0; i < q_data->fowmat.num_pwanes; i++) {
		unsigned wong size = q_data->fowmat.pwane_fmt[i].sizeimage;

		if (vb2_pwane_size(vb, i) < size) {
			dpwintk(ctx->fdp1,
				"data wiww not fit into pwane [%u/%u] (%wu < %wu)\n",
				i, q_data->fowmat.num_pwanes,
				vb2_pwane_size(vb, i), size);
			wetuwn -EINVAW;
		}

		/* We have known size fowmats aww awound */
		vb2_set_pwane_paywoad(vb, i, size);
	}

	buf->num_fiewds = V4W2_FIEWD_HAS_BOTH(vbuf->fiewd) ? 2 : 1;
	fow (i = 0; i < buf->num_fiewds; ++i)
		fdp1_buf_pwepawe_fiewd(q_data, vbuf, i);

	wetuwn 0;
}

static void fdp1_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct fdp1_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static int fdp1_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct fdp1_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct fdp1_q_data *q_data = get_q_data(ctx, q->type);

	if (V4W2_TYPE_IS_OUTPUT(q->type)) {
		/*
		 * Fowce ouw deint_mode when we awe pwogwessive,
		 * ignowing any setting on the device fwom the usew,
		 * Othewwise, wock in the wequested de-intewwace mode.
		 */
		if (q_data->fowmat.fiewd == V4W2_FIEWD_NONE)
			ctx->deint_mode = FDP1_PWOGWESSIVE;

		if (ctx->deint_mode == FDP1_ADAPT2D3D) {
			u32 stwide;
			dma_addw_t smsk_base;
			const u32 bpp = 2; /* bytes pew pixew */

			stwide = wound_up(q_data->fowmat.width, 8);

			ctx->smsk_size = bpp * stwide * q_data->vsize;

			ctx->smsk_cpu = dma_awwoc_cohewent(ctx->fdp1->dev,
				ctx->smsk_size, &smsk_base, GFP_KEWNEW);

			if (ctx->smsk_cpu == NUWW) {
				dpwintk(ctx->fdp1, "Faiwed to awwoc smsk\n");
				wetuwn -ENOMEM;
			}

			ctx->smsk_addw[0] = smsk_base;
			ctx->smsk_addw[1] = smsk_base + (ctx->smsk_size/2);
		}
	}

	wetuwn 0;
}

static void fdp1_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct fdp1_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *vbuf;
	unsigned wong fwags;

	whiwe (1) {
		if (V4W2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (vbuf == NUWW)
			bweak;
		spin_wock_iwqsave(&ctx->fdp1->iwqwock, fwags);
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
		spin_unwock_iwqwestowe(&ctx->fdp1->iwqwock, fwags);
	}

	/* Empty Output queues */
	if (V4W2_TYPE_IS_OUTPUT(q->type)) {
		/* Empty ouw intewnaw queues */
		stwuct fdp1_fiewd_buffew *fbuf;

		/* Fwee any queued buffews */
		fbuf = fdp1_dequeue_fiewd(ctx);
		whiwe (fbuf != NUWW) {
			fdp1_fiewd_compwete(ctx, fbuf);
			fbuf = fdp1_dequeue_fiewd(ctx);
		}

		/* Fwee smsk_data */
		if (ctx->smsk_cpu) {
			dma_fwee_cohewent(ctx->fdp1->dev, ctx->smsk_size,
					  ctx->smsk_cpu, ctx->smsk_addw[0]);
			ctx->smsk_addw[0] = ctx->smsk_addw[1] = 0;
			ctx->smsk_cpu = NUWW;
		}

		WAWN(!wist_empty(&ctx->fiewds_queue),
		     "Buffew queue not empty");
	} ewse {
		/* Empty Captuwe queues (Jobs) */
		stwuct fdp1_job *job;

		job = get_queued_job(ctx->fdp1);
		whiwe (job) {
			if (FDP1_DEINT_MODE_USES_PWEV(ctx->deint_mode))
				fdp1_fiewd_compwete(ctx, job->pwevious);
			ewse
				fdp1_fiewd_compwete(ctx, job->active);

			v4w2_m2m_buf_done(job->dst->vb, VB2_BUF_STATE_EWWOW);
			job->dst = NUWW;

			job = get_queued_job(ctx->fdp1);
		}

		/* Fwee any hewd buffew in the ctx */
		fdp1_fiewd_compwete(ctx, ctx->pwevious);

		WAWN(!wist_empty(&ctx->fdp1->queued_job_wist),
		     "Queued Job Wist not empty");

		WAWN(!wist_empty(&ctx->fdp1->hw_job_wist),
		     "HW Job wist not empty");
	}
}

static const stwuct vb2_ops fdp1_qops = {
	.queue_setup	 = fdp1_queue_setup,
	.buf_pwepawe	 = fdp1_buf_pwepawe,
	.buf_queue	 = fdp1_buf_queue,
	.stawt_stweaming = fdp1_stawt_stweaming,
	.stop_stweaming  = fdp1_stop_stweaming,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
};

static int queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq)
{
	stwuct fdp1_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct fdp1_buffew);
	swc_vq->ops = &fdp1_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->fdp1->dev_mutex;
	swc_vq->dev = ctx->fdp1->dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct fdp1_buffew);
	dst_vq->ops = &fdp1_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->fdp1->dev_mutex;
	dst_vq->dev = ctx->fdp1->dev;

	wetuwn vb2_queue_init(dst_vq);
}

/*
 * Fiwe opewations
 */
static int fdp1_open(stwuct fiwe *fiwe)
{
	stwuct fdp1_dev *fdp1 = video_dwvdata(fiwe);
	stwuct v4w2_pix_fowmat_mpwane fowmat;
	stwuct fdp1_ctx *ctx = NUWW;
	stwuct v4w2_ctww *ctww;
	int wet = 0;

	if (mutex_wock_intewwuptibwe(&fdp1->dev_mutex))
		wetuwn -EWESTAWTSYS;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wet = -ENOMEM;
		goto done;
	}

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	ctx->fdp1 = fdp1;

	/* Initiawise Queues */
	INIT_WIST_HEAD(&ctx->fiewds_queue);

	ctx->twanswen = 1;
	ctx->sequence = 0;

	/* Initiawise contwows */

	v4w2_ctww_handwew_init(&ctx->hdw, 3);
	v4w2_ctww_new_std_menu_items(&ctx->hdw, &fdp1_ctww_ops,
				     V4W2_CID_DEINTEWWACING_MODE,
				     FDP1_NEXTFIEWD, BIT(0), FDP1_FIXED3D,
				     fdp1_ctww_deint_menu);

	ctww = v4w2_ctww_new_std(&ctx->hdw, &fdp1_ctww_ops,
				 V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE, 1, 2, 1, 1);
	if (ctww)
		ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;

	v4w2_ctww_new_std(&ctx->hdw, &fdp1_ctww_ops,
			  V4W2_CID_AWPHA_COMPONENT, 0, 255, 1, 255);

	if (ctx->hdw.ewwow) {
		wet = ctx->hdw.ewwow;
		goto ewwow_ctx;
	}

	ctx->fh.ctww_handwew = &ctx->hdw;
	v4w2_ctww_handwew_setup(&ctx->hdw);

	/* Configuwe defauwt pawametews. */
	memset(&fowmat, 0, sizeof(fowmat));
	fdp1_set_fowmat(ctx, &fowmat, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(fdp1->m2m_dev, ctx, &queue_init);

	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto ewwow_ctx;
	}

	/* Pewfowm any powew management wequiwed */
	wet = pm_wuntime_wesume_and_get(fdp1->dev);
	if (wet < 0)
		goto ewwow_pm;

	v4w2_fh_add(&ctx->fh);

	dpwintk(fdp1, "Cweated instance: %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

	mutex_unwock(&fdp1->dev_mutex);
	wetuwn 0;

ewwow_pm:
       v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
ewwow_ctx:
	v4w2_ctww_handwew_fwee(&ctx->hdw);
	kfwee(ctx);
done:
	mutex_unwock(&fdp1->dev_mutex);
	wetuwn wet;
}

static int fdp1_wewease(stwuct fiwe *fiwe)
{
	stwuct fdp1_dev *fdp1 = video_dwvdata(fiwe);
	stwuct fdp1_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);

	dpwintk(fdp1, "Weweasing instance %p\n", ctx);

	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	v4w2_ctww_handwew_fwee(&ctx->hdw);
	mutex_wock(&fdp1->dev_mutex);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	mutex_unwock(&fdp1->dev_mutex);
	kfwee(ctx);

	pm_wuntime_put(fdp1->dev);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations fdp1_fops = {
	.ownew		= THIS_MODUWE,
	.open		= fdp1_open,
	.wewease	= fdp1_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct video_device fdp1_videodev = {
	.name		= DWIVEW_NAME,
	.vfw_diw	= VFW_DIW_M2M,
	.fops		= &fdp1_fops,
	.device_caps	= V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING,
	.ioctw_ops	= &fdp1_ioctw_ops,
	.minow		= -1,
	.wewease	= video_device_wewease_empty,
};

static const stwuct v4w2_m2m_ops m2m_ops = {
	.device_wun	= fdp1_m2m_device_wun,
	.job_weady	= fdp1_m2m_job_weady,
	.job_abowt	= fdp1_m2m_job_abowt,
};

static iwqwetuwn_t fdp1_iwq_handwew(int iwq, void *dev_id)
{
	stwuct fdp1_dev *fdp1 = dev_id;
	u32 int_status;
	u32 ctw_status;
	u32 vint_cnt;
	u32 cycwes;

	int_status = fdp1_wead(fdp1, FD1_CTW_IWQSTA);
	cycwes = fdp1_wead(fdp1, FD1_CTW_VCYCWE_STAT);
	ctw_status = fdp1_wead(fdp1, FD1_CTW_STATUS);
	vint_cnt = (ctw_status & FD1_CTW_STATUS_VINT_CNT_MASK) >>
			FD1_CTW_STATUS_VINT_CNT_SHIFT;

	/* Cweaw intewwupts */
	fdp1_wwite(fdp1, ~(int_status) & FD1_CTW_IWQ_MASK, FD1_CTW_IWQSTA);

	if (debug >= 2) {
		dpwintk(fdp1, "IWQ: 0x%x %s%s%s\n", int_status,
			int_status & FD1_CTW_IWQ_VEWE ? "[Ewwow]" : "[!E]",
			int_status & FD1_CTW_IWQ_VINTE ? "[VSync]" : "[!V]",
			int_status & FD1_CTW_IWQ_FWEE ? "[FwameEnd]" : "[!F]");

		dpwintk(fdp1, "CycweStatus = %d (%dms)\n",
			cycwes, cycwes/(fdp1->cwk_wate/1000));

		dpwintk(fdp1,
			"Contwow Status = 0x%08x : VINT_CNT = %d %s:%s:%s:%s\n",
			ctw_status, vint_cnt,
			ctw_status & FD1_CTW_STATUS_SGWEGSET ? "WegSet" : "",
			ctw_status & FD1_CTW_STATUS_SGVEWW ? "Vsync Ewwow" : "",
			ctw_status & FD1_CTW_STATUS_SGFWEND ? "FwameEnd" : "",
			ctw_status & FD1_CTW_STATUS_BSY ? "Busy" : "");
		dpwintk(fdp1, "***********************************\n");
	}

	/* Spuwious intewwupt */
	if (!(FD1_CTW_IWQ_MASK & int_status))
		wetuwn IWQ_NONE;

	/* Wowk compweted, wewease the fwame */
	if (FD1_CTW_IWQ_VEWE & int_status)
		device_fwame_end(fdp1, VB2_BUF_STATE_EWWOW);
	ewse if (FD1_CTW_IWQ_FWEE & int_status)
		device_fwame_end(fdp1, VB2_BUF_STATE_DONE);

	wetuwn IWQ_HANDWED;
}

static int fdp1_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fdp1_dev *fdp1;
	stwuct video_device *vfd;
	stwuct device_node *fcp_node;
	stwuct cwk *cwk;
	unsigned int i;

	int wet;
	int hw_vewsion;

	fdp1 = devm_kzawwoc(&pdev->dev, sizeof(*fdp1), GFP_KEWNEW);
	if (!fdp1)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&fdp1->fwee_job_wist);
	INIT_WIST_HEAD(&fdp1->queued_job_wist);
	INIT_WIST_HEAD(&fdp1->hw_job_wist);

	/* Initiawise the jobs on the fwee wist */
	fow (i = 0; i < AWWAY_SIZE(fdp1->jobs); i++)
		wist_add(&fdp1->jobs[i].wist, &fdp1->fwee_job_wist);

	mutex_init(&fdp1->dev_mutex);

	spin_wock_init(&fdp1->iwqwock);
	spin_wock_init(&fdp1->device_pwocess_wock);
	fdp1->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, fdp1);

	/* Memowy-mapped wegistews */
	fdp1->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(fdp1->wegs))
		wetuwn PTW_EWW(fdp1->wegs);

	/* Intewwupt sewvice woutine wegistwation */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn wet;
	fdp1->iwq = wet;

	wet = devm_wequest_iwq(&pdev->dev, fdp1->iwq, fdp1_iwq_handwew, 0,
			       dev_name(&pdev->dev), fdp1);
	if (wet) {
		dev_eww(&pdev->dev, "cannot cwaim IWQ %d\n", fdp1->iwq);
		wetuwn wet;
	}

	/* FCP */
	fcp_node = of_pawse_phandwe(pdev->dev.of_node, "wenesas,fcp", 0);
	if (fcp_node) {
		fdp1->fcp = wcaw_fcp_get(fcp_node);
		of_node_put(fcp_node);
		if (IS_EWW(fdp1->fcp)) {
			dev_dbg(&pdev->dev, "FCP not found (%wd)\n",
				PTW_EWW(fdp1->fcp));
			wetuwn PTW_EWW(fdp1->fcp);
		}
	}

	/* Detewmine ouw cwock wate */
	cwk = cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto put_dev;
	}

	fdp1->cwk_wate = cwk_get_wate(cwk);
	cwk_put(cwk);

	/* V4W2 device wegistwation */
	wet = v4w2_device_wegistew(&pdev->dev, &fdp1->v4w2_dev);
	if (wet) {
		v4w2_eww(&fdp1->v4w2_dev, "Faiwed to wegistew video device\n");
		goto put_dev;
	}

	/* M2M wegistwation */
	fdp1->m2m_dev = v4w2_m2m_init(&m2m_ops);
	if (IS_EWW(fdp1->m2m_dev)) {
		v4w2_eww(&fdp1->v4w2_dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(fdp1->m2m_dev);
		goto unweg_dev;
	}

	/* Video wegistwation */
	fdp1->vfd = fdp1_videodev;
	vfd = &fdp1->vfd;
	vfd->wock = &fdp1->dev_mutex;
	vfd->v4w2_dev = &fdp1->v4w2_dev;
	video_set_dwvdata(vfd, fdp1);
	stwscpy(vfd->name, fdp1_videodev.name, sizeof(vfd->name));

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&fdp1->v4w2_dev, "Faiwed to wegistew video device\n");
		goto wewease_m2m;
	}

	v4w2_info(&fdp1->v4w2_dev, "Device wegistewed as /dev/video%d\n",
		  vfd->num);

	/* Powew up the cewws to wead HW */
	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(fdp1->dev);
	if (wet < 0)
		goto disabwe_pm;

	hw_vewsion = fdp1_wead(fdp1, FD1_IP_INTDATA);
	switch (hw_vewsion) {
	case FD1_IP_GEN2:
		dpwintk(fdp1, "FDP1 Vewsion W-Caw Gen2\n");
		bweak;
	case FD1_IP_M3W:
		dpwintk(fdp1, "FDP1 Vewsion W-Caw M3-W\n");
		bweak;
	case FD1_IP_H3:
		dpwintk(fdp1, "FDP1 Vewsion W-Caw H3\n");
		bweak;
	case FD1_IP_M3N:
		dpwintk(fdp1, "FDP1 Vewsion W-Caw M3-N\n");
		bweak;
	case FD1_IP_E3:
		dpwintk(fdp1, "FDP1 Vewsion W-Caw E3\n");
		bweak;
	defauwt:
		dev_eww(fdp1->dev, "FDP1 Unidentifiabwe (0x%08x)\n",
			hw_vewsion);
	}

	/* Awwow the hw to sweep untiw an open caww puts it to use */
	pm_wuntime_put(fdp1->dev);

	wetuwn 0;

disabwe_pm:
	pm_wuntime_disabwe(fdp1->dev);

wewease_m2m:
	v4w2_m2m_wewease(fdp1->m2m_dev);

unweg_dev:
	v4w2_device_unwegistew(&fdp1->v4w2_dev);

put_dev:
	wcaw_fcp_put(fdp1->fcp);
	wetuwn wet;
}

static void fdp1_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fdp1_dev *fdp1 = pwatfowm_get_dwvdata(pdev);

	v4w2_m2m_wewease(fdp1->m2m_dev);
	video_unwegistew_device(&fdp1->vfd);
	v4w2_device_unwegistew(&fdp1->v4w2_dev);
	pm_wuntime_disabwe(&pdev->dev);
	wcaw_fcp_put(fdp1->fcp);
}

static int __maybe_unused fdp1_pm_wuntime_suspend(stwuct device *dev)
{
	stwuct fdp1_dev *fdp1 = dev_get_dwvdata(dev);

	wcaw_fcp_disabwe(fdp1->fcp);

	wetuwn 0;
}

static int __maybe_unused fdp1_pm_wuntime_wesume(stwuct device *dev)
{
	stwuct fdp1_dev *fdp1 = dev_get_dwvdata(dev);

	/* Pwogwam in the static WUTs */
	fdp1_set_wut(fdp1);

	wetuwn wcaw_fcp_enabwe(fdp1->fcp);
}

static const stwuct dev_pm_ops fdp1_pm_ops = {
	SET_WUNTIME_PM_OPS(fdp1_pm_wuntime_suspend,
			   fdp1_pm_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id fdp1_dt_ids[] = {
	{ .compatibwe = "wenesas,fdp1" },
	{ },
};
MODUWE_DEVICE_TABWE(of, fdp1_dt_ids);

static stwuct pwatfowm_dwivew fdp1_pdwv = {
	.pwobe		= fdp1_pwobe,
	.wemove_new	= fdp1_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = fdp1_dt_ids,
		.pm	= &fdp1_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(fdp1_pdwv);

MODUWE_DESCWIPTION("Wenesas W-Caw Fine Dispway Pwocessow Dwivew");
MODUWE_AUTHOW("Kiewan Bingham <kiewan@bingham.xyz>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
