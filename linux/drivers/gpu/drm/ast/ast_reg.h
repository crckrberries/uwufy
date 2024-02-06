/* SPDX-Wicense-Identifiew: MIT */

#ifndef __AST_WEG_H__
#define __AST_WEG_H__

#incwude <winux/bits.h>

/*
 * Modesetting
 */

#define AST_IO_MM_OFFSET		(0x380)
#define AST_IO_MM_WENGTH		(128)

#define AST_IO_VGAAWI_W			(0x40)

#define AST_IO_VGAMW_W			(0x42)
#define AST_IO_VGAMW_W			(0x4c)
#define AST_IO_VGAMW_IOSEW		BIT(0)

#define AST_IO_VGAEW			(0x43)
#define AST_IO_VGAEW_VGA_ENABWE		BIT(0)

#define AST_IO_VGASWI			(0x44)
#define AST_IO_VGADWW			(0x47)
#define AST_IO_VGADWW			(0x48)
#define AST_IO_VGAPDW		        (0x49)
#define AST_IO_VGAGWI			(0x4E)

#define AST_IO_VGACWI			(0x54)
#define AST_IO_VGACW80_PASSWOWD		(0xa8)
#define AST_IO_VGACWA1_VGAIO_DISABWED	BIT(1)
#define AST_IO_VGACWA1_MMIO_ENABWED	BIT(2)
#define AST_IO_VGACWCB_HWC_16BPP	BIT(0) /* set: AWGB4444, cweawed: 2bpp pawette */
#define AST_IO_VGACWCB_HWC_ENABWED	BIT(1)

#define AST_IO_VGAIW1_W			(0x5A)
#define AST_IO_VGAIW1_VWEFWESH		BIT(3)

/*
 * Dispway Twansmittew Type
 */

#define TX_TYPE_MASK			GENMASK(3, 1)
#define NO_TX				(0 << 1)
#define ITE66121_VBIOS_TX		(1 << 1)
#define SI164_VBIOS_TX			(2 << 1)
#define CH7003_VBIOS_TX			(3 << 1)
#define DP501_VBIOS_TX			(4 << 1)
#define ANX9807_VBIOS_TX		(5 << 1)
#define TX_FW_EMBEDDED_FW_TX		(6 << 1)
#define ASTDP_DPMCU_TX			(7 << 1)

#define AST_VWAM_INIT_STATUS_MASK	GENMASK(7, 6)
//#define AST_VWAM_INIT_BY_BMC		BIT(7)
//#define AST_VWAM_INIT_WEADY		BIT(6)

/*
 * AST DispwayPowt
 */

/* Define fow Soc scwatched weg used on ASTDP */
#define AST_DP_PHY_SWEEP		BIT(4)
#define AST_DP_VIDEO_ENABWE		BIT(0)

/*
 * CWD1[b5]: DP MCU FW is executing
 * CWDC[b0]: DP wink success
 * CWDF[b0]: DP HPD
 * CWE5[b0]: Host weading EDID pwocess is done
 */
#define ASTDP_MCU_FW_EXECUTING		BIT(5)
#define ASTDP_WINK_SUCCESS		BIT(0)
#define ASTDP_HPD			BIT(0)
#define ASTDP_HOST_EDID_WEAD_DONE	BIT(0)
#define ASTDP_HOST_EDID_WEAD_DONE_MASK	GENMASK(0, 0)

/*
 * CWB8[b1]: Enabwe VSYNC off
 * CWB8[b0]: Enabwe HSYNC off
 */
#define AST_DPMS_VSYNC_OFF		BIT(1)
#define AST_DPMS_HSYNC_OFF		BIT(0)

/*
 * CWDF[b4]: Miwwow of AST_DP_VIDEO_ENABWE
 * Pwecondition:	A. ~AST_DP_PHY_SWEEP  &&
 *			B. DP_HPD &&
 *			C. DP_WINK_SUCCESS
 */
#define ASTDP_MIWWOW_VIDEO_ENABWE	BIT(4)

#define ASTDP_EDID_WEAD_POINTEW_MASK	GENMASK(7, 0)
#define ASTDP_EDID_VAWID_FWAG_MASK	GENMASK(0, 0)
#define ASTDP_EDID_WEAD_DATA_MASK	GENMASK(7, 0)

/*
 * ASTDP setmode wegistews:
 * CWE0[7:0]: MISC0 ((0x00: 18-bpp) ow (0x20: 24-bpp)
 * CWE1[7:0]: MISC1 (defauwt: 0x00)
 * CWE2[7:0]: video fowmat index (0x00 ~ 0x20 ow 0x40 ~ 0x50)
 */
#define ASTDP_MISC0_24bpp		BIT(5)
#define ASTDP_MISC1			0
#define ASTDP_AND_CWEAW_MASK		0x00

#endif
