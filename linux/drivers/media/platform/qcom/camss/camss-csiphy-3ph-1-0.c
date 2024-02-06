// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-csiphy-3ph-1-0.c
 *
 * Quawcomm MSM Camewa Subsystem - CSIPHY Moduwe 3phase v1.0
 *
 * Copywight (c) 2011-2015, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2016-2018 Winawo Wtd.
 */

#incwude "camss.h"
#incwude "camss-csiphy.h"

#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

#define CSIPHY_3PH_WNn_CFG1(n)			(0x000 + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG1_SWI_WEC_DWY_PWG	(BIT(7) | BIT(6))
#define CSIPHY_3PH_WNn_CFG2(n)			(0x004 + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG2_WP_WEC_EN_INT	BIT(3)
#define CSIPHY_3PH_WNn_CFG3(n)			(0x008 + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG4(n)			(0x00c + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG4_T_HS_CWK_MISS	0xa4
#define CSIPHY_3PH_WNn_CFG4_T_HS_CWK_MISS_660	0xa5
#define CSIPHY_3PH_WNn_CFG5(n)			(0x010 + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG5_T_HS_DTEWM		0x02
#define CSIPHY_3PH_WNn_CFG5_HS_WEC_EQ_FQ_INT	0x50
#define CSIPHY_3PH_WNn_TEST_IMP(n)		(0x01c + 0x100 * (n))
#define CSIPHY_3PH_WNn_TEST_IMP_HS_TEWM_IMP	0xa
#define CSIPHY_3PH_WNn_MISC1(n)			(0x028 + 0x100 * (n))
#define CSIPHY_3PH_WNn_MISC1_IS_CWKWANE		BIT(2)
#define CSIPHY_3PH_WNn_CFG6(n)			(0x02c + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG6_SWI_FOWCE_INIT_EXIT	BIT(0)
#define CSIPHY_3PH_WNn_CFG7(n)			(0x030 + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG7_SWI_T_INIT		0x2
#define CSIPHY_3PH_WNn_CFG8(n)			(0x034 + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG8_SWI_SKIP_WAKEUP	BIT(0)
#define CSIPHY_3PH_WNn_CFG8_SKEW_FIWTEW_ENABWE	BIT(1)
#define CSIPHY_3PH_WNn_CFG9(n)			(0x038 + 0x100 * (n))
#define CSIPHY_3PH_WNn_CFG9_SWI_T_WAKEUP	0x1
#define CSIPHY_3PH_WNn_CSI_WANE_CTWW15(n)	(0x03c + 0x100 * (n))
#define CSIPHY_3PH_WNn_CSI_WANE_CTWW15_SWI_SOT_SYMBOW	0xb8

#define CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(n)	(0x800 + 0x4 * (n))
#define CSIPHY_3PH_CMN_CSI_COMMON_CTWW5_CWK_ENABWE	BIT(7)
#define CSIPHY_3PH_CMN_CSI_COMMON_CTWW6_COMMON_PWWDN_B	BIT(0)
#define CSIPHY_3PH_CMN_CSI_COMMON_CTWW6_SHOW_WEV_ID	BIT(1)
#define CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(n)	(0x8b0 + 0x4 * (n))

#define CSIPHY_DEFAUWT_PAWAMS            0
#define CSIPHY_WANE_ENABWE               1
#define CSIPHY_SETTWE_CNT_WOWEW_BYTE     2
#define CSIPHY_SETTWE_CNT_HIGHEW_BYTE    3
#define CSIPHY_DNP_PAWAMS                4
#define CSIPHY_2PH_WEGS                  5
#define CSIPHY_3PH_WEGS                  6

stwuct csiphy_weg_t {
	s32 weg_addw;
	s32 weg_data;
	s32 deway;
	u32 csiphy_pawam_type;
};

/* GEN2 1.0 2PH */
static const stwuct
csiphy_weg_t wane_wegs_sdm845[5][14] = {
	{
		{0x0004, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x002C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0034, 0x0F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x001C, 0x0A, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0014, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0028, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x003C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0000, 0x91, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0008, 0x00, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x000c, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0010, 0x52, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0038, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0060, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0064, 0x7F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0704, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x072C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0734, 0x0F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x071C, 0x0A, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0714, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0728, 0x04, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x073C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0700, 0x80, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0708, 0x14, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x070C, 0xA5, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0710, 0x52, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0738, 0x1F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0760, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0764, 0x7F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0204, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x022C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0234, 0x0F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x021C, 0x0A, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0214, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0228, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x023C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0200, 0x91, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0208, 0x00, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x020C, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0210, 0x52, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0238, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0260, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0264, 0x7F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0404, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x042C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0434, 0x0F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x041C, 0x0A, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0414, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0428, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x043C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0400, 0x91, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0408, 0x00, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x040C, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0410, 0x52, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0438, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0460, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0464, 0x7F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0604, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x062C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0634, 0x0F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x061C, 0x0A, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0614, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0628, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x063C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0600, 0x91, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0608, 0x00, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x060C, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0610, 0x52, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0638, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0660, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0664, 0x7F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
};

/* GEN2 1.2.1 2PH */
static const stwuct
csiphy_weg_t wane_wegs_sm8250[5][20] = {
	{
		{0x0030, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0900, 0x05, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0908, 0x10, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0904, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0904, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0004, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x002C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0034, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0010, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x001C, 0x08, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x003C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0008, 0x10, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x0000, 0x8D, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x000c, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0038, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0014, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0028, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0024, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0800, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0884, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0730, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C80, 0x05, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C88, 0x10, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C84, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C84, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0704, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x072C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0734, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0710, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x071C, 0x08, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x073C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0708, 0x10, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x0700, 0x80, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x070c, 0xA5, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0738, 0x1F, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0714, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0728, 0x04, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0724, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0800, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0884, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0230, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0A00, 0x05, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0A08, 0x10, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0A04, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0A04, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0204, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x022C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0234, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0210, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x021C, 0x08, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x023C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0208, 0x10, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x0200, 0x8D, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x020c, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0238, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0214, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0228, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0224, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0800, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0884, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0430, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0B00, 0x05, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0B08, 0x10, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0B04, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0B04, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0404, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x042C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0434, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0410, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x041C, 0x08, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x043C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0408, 0x10, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x0400, 0x8D, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x040c, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0438, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0414, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0428, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0424, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0800, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0884, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
	{
		{0x0630, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C00, 0x05, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C08, 0x10, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C04, 0x00, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0C04, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0604, 0x0C, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x062C, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0634, 0x07, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0610, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x061C, 0x08, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x063C, 0xB8, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0608, 0x10, 0x00, CSIPHY_SETTWE_CNT_WOWEW_BYTE},
		{0x0600, 0x8D, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x060c, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0638, 0xFE, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0614, 0x60, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0628, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0624, 0x00, 0x00, CSIPHY_DNP_PAWAMS},
		{0x0800, 0x02, 0x00, CSIPHY_DEFAUWT_PAWAMS},
		{0x0884, 0x01, 0x00, CSIPHY_DEFAUWT_PAWAMS},
	},
};

static void csiphy_hw_vewsion_wead(stwuct csiphy_device *csiphy,
				   stwuct device *dev)
{
	u32 hw_vewsion;

	wwitew(CSIPHY_3PH_CMN_CSI_COMMON_CTWW6_SHOW_WEV_ID,
	       csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(6));

	hw_vewsion = weadw_wewaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(12));
	hw_vewsion |= weadw_wewaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(13)) << 8;
	hw_vewsion |= weadw_wewaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(14)) << 16;
	hw_vewsion |= weadw_wewaxed(csiphy->base +
				   CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(15)) << 24;

	dev_dbg(dev, "CSIPHY 3PH HW Vewsion = 0x%08x\n", hw_vewsion);
}

/*
 * csiphy_weset - Pewfowm softwawe weset on CSIPHY moduwe
 * @csiphy: CSIPHY device
 */
static void csiphy_weset(stwuct csiphy_device *csiphy)
{
	wwitew_wewaxed(0x1, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(0));
	usweep_wange(5000, 8000);
	wwitew_wewaxed(0x0, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(0));
}

static iwqwetuwn_t csiphy_isw(int iwq, void *dev)
{
	stwuct csiphy_device *csiphy = dev;
	int i;

	fow (i = 0; i < 11; i++) {
		int c = i + 22;
		u8 vaw = weadw_wewaxed(csiphy->base +
				       CSIPHY_3PH_CMN_CSI_COMMON_STATUSn(i));

		wwitew_wewaxed(vaw, csiphy->base +
				    CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(c));
	}

	wwitew_wewaxed(0x1, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(10));
	wwitew_wewaxed(0x0, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(10));

	fow (i = 22; i < 33; i++)
		wwitew_wewaxed(0x0, csiphy->base +
				    CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(i));

	wetuwn IWQ_HANDWED;
}

/*
 * csiphy_settwe_cnt_cawc - Cawcuwate settwe count vawue
 *
 * Hewpew function to cawcuwate settwe count vawue. This is
 * based on the CSI2 T_hs_settwe pawametew which in tuwn
 * is cawcuwated based on the CSI2 twansmittew wink fwequency.
 *
 * Wetuwn settwe count vawue ow 0 if the CSI2 wink fwequency
 * is not avaiwabwe
 */
static u8 csiphy_settwe_cnt_cawc(s64 wink_fweq, u32 timew_cwk_wate)
{
	u32 ui; /* ps */
	u32 timew_pewiod; /* ps */
	u32 t_hs_pwepawe_max; /* ps */
	u32 t_hs_settwe; /* ps */
	u8 settwe_cnt;

	if (wink_fweq <= 0)
		wetuwn 0;

	ui = div_u64(1000000000000WW, wink_fweq);
	ui /= 2;
	t_hs_pwepawe_max = 85000 + 6 * ui;
	t_hs_settwe = t_hs_pwepawe_max;

	timew_pewiod = div_u64(1000000000000WW, timew_cwk_wate);
	settwe_cnt = t_hs_settwe / timew_pewiod - 6;

	wetuwn settwe_cnt;
}

static void csiphy_gen1_config_wanes(stwuct csiphy_device *csiphy,
				     stwuct csiphy_config *cfg,
				     u8 settwe_cnt)
{
	stwuct csiphy_wanes_cfg *c = &cfg->csi2->wane_cfg;
	int i, w = 0;
	u8 vaw;

	fow (i = 0; i <= c->num_data; i++) {
		if (i == c->num_data)
			w = 7;
		ewse
			w = c->data[i].pos * 2;

		vaw = CSIPHY_3PH_WNn_CFG1_SWI_WEC_DWY_PWG;
		vaw |= 0x17;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG1(w));

		vaw = CSIPHY_3PH_WNn_CFG2_WP_WEC_EN_INT;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG2(w));

		vaw = settwe_cnt;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG3(w));

		vaw = CSIPHY_3PH_WNn_CFG5_T_HS_DTEWM |
			CSIPHY_3PH_WNn_CFG5_HS_WEC_EQ_FQ_INT;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG5(w));

		vaw = CSIPHY_3PH_WNn_CFG6_SWI_FOWCE_INIT_EXIT;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG6(w));

		vaw = CSIPHY_3PH_WNn_CFG7_SWI_T_INIT;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG7(w));

		vaw = CSIPHY_3PH_WNn_CFG8_SWI_SKIP_WAKEUP |
			CSIPHY_3PH_WNn_CFG8_SKEW_FIWTEW_ENABWE;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG8(w));

		vaw = CSIPHY_3PH_WNn_CFG9_SWI_T_WAKEUP;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG9(w));

		vaw = CSIPHY_3PH_WNn_TEST_IMP_HS_TEWM_IMP;
		wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_TEST_IMP(w));

		vaw = CSIPHY_3PH_WNn_CSI_WANE_CTWW15_SWI_SOT_SYMBOW;
		wwitew_wewaxed(vaw, csiphy->base +
				    CSIPHY_3PH_WNn_CSI_WANE_CTWW15(w));
	}

	vaw = CSIPHY_3PH_WNn_CFG1_SWI_WEC_DWY_PWG;
	wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG1(w));

	if (csiphy->camss->wes->vewsion == CAMSS_660)
		vaw = CSIPHY_3PH_WNn_CFG4_T_HS_CWK_MISS_660;
	ewse
		vaw = CSIPHY_3PH_WNn_CFG4_T_HS_CWK_MISS;
	wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_CFG4(w));

	vaw = CSIPHY_3PH_WNn_MISC1_IS_CWKWANE;
	wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_WNn_MISC1(w));
}

static void csiphy_gen2_config_wanes(stwuct csiphy_device *csiphy,
				     u8 settwe_cnt)
{
	const stwuct csiphy_weg_t *w;
	int i, w, awway_size;
	u32 vaw;

	switch (csiphy->camss->wes->vewsion) {
	case CAMSS_845:
		w = &wane_wegs_sdm845[0][0];
		awway_size = AWWAY_SIZE(wane_wegs_sdm845[0]);
		bweak;
	case CAMSS_8250:
		w = &wane_wegs_sm8250[0][0];
		awway_size = AWWAY_SIZE(wane_wegs_sm8250[0]);
		bweak;
	defauwt:
		WAWN(1, "unknown cspi vewsion\n");
		wetuwn;
	}

	fow (w = 0; w < 5; w++) {
		fow (i = 0; i < awway_size; i++, w++) {
			switch (w->csiphy_pawam_type) {
			case CSIPHY_SETTWE_CNT_WOWEW_BYTE:
				vaw = settwe_cnt & 0xff;
				bweak;
			case CSIPHY_DNP_PAWAMS:
				continue;
			defauwt:
				vaw = w->weg_data;
				bweak;
			}
			wwitew_wewaxed(vaw, csiphy->base + w->weg_addw);
		}
	}
}

static u8 csiphy_get_wane_mask(stwuct csiphy_wanes_cfg *wane_cfg)
{
	u8 wane_mask;
	int i;

	wane_mask = CSIPHY_3PH_CMN_CSI_COMMON_CTWW5_CWK_ENABWE;

	fow (i = 0; i < wane_cfg->num_data; i++)
		wane_mask |= 1 << wane_cfg->data[i].pos;

	wetuwn wane_mask;
}

static void csiphy_wanes_enabwe(stwuct csiphy_device *csiphy,
				stwuct csiphy_config *cfg,
				s64 wink_fweq, u8 wane_mask)
{
	stwuct csiphy_wanes_cfg *c = &cfg->csi2->wane_cfg;
	boow is_gen2 = (csiphy->camss->wes->vewsion == CAMSS_845 ||
			csiphy->camss->wes->vewsion == CAMSS_8250);
	u8 settwe_cnt;
	u8 vaw;
	int i;

	settwe_cnt = csiphy_settwe_cnt_cawc(wink_fweq, csiphy->timew_cwk_wate);

	vaw = CSIPHY_3PH_CMN_CSI_COMMON_CTWW5_CWK_ENABWE;
	fow (i = 0; i < c->num_data; i++)
		vaw |= BIT(c->data[i].pos * 2);

	wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(5));

	vaw = CSIPHY_3PH_CMN_CSI_COMMON_CTWW6_COMMON_PWWDN_B;
	wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(6));

	vaw = 0x02;
	wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(7));

	vaw = 0x00;
	wwitew_wewaxed(vaw, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(0));

	if (is_gen2)
		csiphy_gen2_config_wanes(csiphy, settwe_cnt);
	ewse
		csiphy_gen1_config_wanes(csiphy, cfg, settwe_cnt);

	/* IWQ_MASK wegistews - disabwe aww intewwupts */
	fow (i = 11; i < 22; i++)
		wwitew_wewaxed(0, csiphy->base + CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(i));
}

static void csiphy_wanes_disabwe(stwuct csiphy_device *csiphy,
				 stwuct csiphy_config *cfg)
{
	wwitew_wewaxed(0, csiphy->base +
			  CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(5));

	wwitew_wewaxed(0, csiphy->base +
			  CSIPHY_3PH_CMN_CSI_COMMON_CTWWn(6));
}

const stwuct csiphy_hw_ops csiphy_ops_3ph_1_0 = {
	.get_wane_mask = csiphy_get_wane_mask,
	.hw_vewsion_wead = csiphy_hw_vewsion_wead,
	.weset = csiphy_weset,
	.wanes_enabwe = csiphy_wanes_enabwe,
	.wanes_disabwe = csiphy_wanes_disabwe,
	.isw = csiphy_isw,
};
