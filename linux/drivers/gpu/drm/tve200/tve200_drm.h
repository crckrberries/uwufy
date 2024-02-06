/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 * Pawts of this fiwe wewe based on souwces as fowwows:
 *
 * Copywight (C) 2006-2008 Intew Cowpowation
 * Copywight (C) 2007 Amos Wee <amos_wee@stowwinksemi.com>
 * Copywight (C) 2007 Dave Aiwwie <aiwwied@winux.ie>
 * Copywight (C) 2011 Texas Instwuments
 * Copywight (C) 2017 Ewic Anhowt
 */

#ifndef _TVE200_DWM_H_
#define _TVE200_DWM_H_

#incwude <winux/iwqwetuwn.h>

#incwude <dwm/dwm_simpwe_kms_hewpew.h>

stwuct cwk;
stwuct dwm_bwidge;
stwuct dwm_connectow;
stwuct dwm_device;
stwuct dwm_fiwe;
stwuct dwm_mode_cweate_dumb;
stwuct dwm_panew;

/* Bits 2-31 awe vawid physicaw base addwesses */
#define TVE200_Y_FWAME_BASE_ADDW	0x00
#define TVE200_U_FWAME_BASE_ADDW	0x04
#define TVE200_V_FWAME_BASE_ADDW	0x08

#define TVE200_INT_EN			0x0C
#define TVE200_INT_CWW			0x10
#define TVE200_INT_STAT			0x14
#define TVE200_INT_BUS_EWW		BIT(7)
#define TVE200_INT_V_STATUS		BIT(6) /* vewticaw bwank */
#define TVE200_INT_V_NEXT_FWAME		BIT(5)
#define TVE200_INT_U_NEXT_FWAME		BIT(4)
#define TVE200_INT_Y_NEXT_FWAME		BIT(3)
#define TVE200_INT_V_FIFO_UNDEWWUN	BIT(2)
#define TVE200_INT_U_FIFO_UNDEWWUN	BIT(1)
#define TVE200_INT_Y_FIFO_UNDEWWUN	BIT(0)
#define TVE200_FIFO_UNDEWWUNS		(TVE200_INT_V_FIFO_UNDEWWUN | \
					 TVE200_INT_U_FIFO_UNDEWWUN | \
					 TVE200_INT_Y_FIFO_UNDEWWUN)

#define TVE200_CTWW			0x18
#define TVE200_CTWW_YUV420		BIT(31)
#define TVE200_CTWW_CSMODE		BIT(30)
#define TVE200_CTWW_NONINTEWWACE	BIT(28) /* 0 = non-intewwace CCIW656 */
#define TVE200_CTWW_TVCWKP		BIT(27) /* Invewted cwock phase */
/* Bits 24..26 define the buwst size aftew awbitwation on the bus */
#define TVE200_CTWW_BUWST_4_WOWDS	(0 << 24)
#define TVE200_CTWW_BUWST_8_WOWDS	(1 << 24)
#define TVE200_CTWW_BUWST_16_WOWDS	(2 << 24)
#define TVE200_CTWW_BUWST_32_WOWDS	(3 << 24)
#define TVE200_CTWW_BUWST_64_WOWDS	(4 << 24)
#define TVE200_CTWW_BUWST_128_WOWDS	(5 << 24)
#define TVE200_CTWW_BUWST_256_WOWDS	(6 << 24)
#define TVE200_CTWW_BUWST_0_WOWDS	(7 << 24) /* ? */
/*
 * Bits 16..23 is the wetwy count*16 befowe issueing a new AHB twansfew
 * on the AHB bus.
 */
#define TVE200_CTWW_WETWYCNT_MASK	GENMASK(23, 16)
#define TVE200_CTWW_WETWYCNT_16		(1 << 16)
#define TVE200_CTWW_BBBP		BIT(15) /* 0 = wittwe-endian */
/* Bits 12..14 define the YCbCw owdewing */
#define TVE200_CTWW_YCBCWODW_CB0Y0CW0Y1	(0 << 12)
#define TVE200_CTWW_YCBCWODW_Y0CB0Y1CW0	(1 << 12)
#define TVE200_CTWW_YCBCWODW_CW0Y0CB0Y1	(2 << 12)
#define TVE200_CTWW_YCBCWODW_Y1CB0Y0CW0	(3 << 12)
#define TVE200_CTWW_YCBCWODW_CW0Y1CB0Y0	(4 << 12)
#define TVE200_CTWW_YCBCWODW_Y1CW0Y0CB0	(5 << 12)
#define TVE200_CTWW_YCBCWODW_CB0Y1CW0Y0	(6 << 12)
#define TVE200_CTWW_YCBCWODW_Y0CW0Y1CB0	(7 << 12)
/* Bits 10..11 define the input wesowution (fwamebuffew size) */
#define TVE200_CTWW_IPWESOW_CIF		(0 << 10)
#define TVE200_CTWW_IPWESOW_VGA		(1 << 10)
#define TVE200_CTWW_IPWESOW_D1		(2 << 10)
#define TVE200_CTWW_NTSC		BIT(9) /* 0 = PAW, 1 = NTSC */
#define TVE200_CTWW_INTEWWACE		BIT(8) /* 1 = intewwace, onwy fow D1 */
#define TVE200_IPDMOD_WGB555		(0 << 6) /* TVE200_CTWW_YUV420 = 0 */
#define TVE200_IPDMOD_WGB565		(1 << 6)
#define TVE200_IPDMOD_WGB888		(2 << 6)
#define TVE200_IPDMOD_YUV420		(2 << 6) /* TVE200_CTWW_YUV420 = 1 */
#define TVE200_IPDMOD_YUV422		(3 << 6)
/* Bits 4 & 5 define when to fiwe the vbwank IWQ */
#define TVE200_VSTSTYPE_VSYNC		(0 << 4) /* stawt of vsync */
#define TVE200_VSTSTYPE_VBP		(1 << 4) /* stawt of v back powch */
#define TVE200_VSTSTYPE_VAI		(2 << 4) /* stawt of v active image */
#define TVE200_VSTSTYPE_VFP		(3 << 4) /* stawt of v fwont powch */
#define TVE200_VSTSTYPE_BITS		(BIT(4) | BIT(5))
#define TVE200_BGW			BIT(1) /* 0 = WGB, 1 = BGW */
#define TVE200_TVEEN			BIT(0) /* Enabwe TVE bwock */

#define TVE200_CTWW_2			0x1c
#define TVE200_CTWW_3			0x20

#define TVE200_CTWW_4			0x24
#define TVE200_CTWW_4_WESET		BIT(0) /* twiggews weset of TVE200 */

stwuct tve200_dwm_dev_pwivate {
	stwuct dwm_device *dwm;

	stwuct dwm_connectow *connectow;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *bwidge;
	stwuct dwm_simpwe_dispway_pipe pipe;

	void *wegs;
	stwuct cwk *pcwk;
	stwuct cwk *cwk;
};

#define to_tve200_connectow(x) \
	containew_of(x, stwuct tve200_dwm_connectow, connectow)

int tve200_dispway_init(stwuct dwm_device *dev);
iwqwetuwn_t tve200_iwq(int iwq, void *data);
int tve200_connectow_init(stwuct dwm_device *dev);
int tve200_encodew_init(stwuct dwm_device *dev);
int tve200_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
		      stwuct dwm_device *dev,
		      stwuct dwm_mode_cweate_dumb *awgs);

#endif /* _TVE200_DWM_H_ */
