// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * camss-csid-4-7.c
 *
 * Quawcomm MSM Camewa Subsystem - CSID (CSI Decodew) Moduwe
 *
 * Copywight (C) 2020 Winawo Wtd.
 */
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>

#incwude "camss-csid.h"
#incwude "camss-csid-gen2.h"
#incwude "camss.h"

/* The CSID 2 IP-bwock is diffewent fwom the othews,
 * and is of a bawe-bones Wite vewsion, with no PIX
 * intewface suppowt. As a wesuwt of that it has an
 * awtewnate wegistew wayout.
 */

#define CSID_HW_VEWSION		0x0
#define		HW_VEWSION_STEPPING	0
#define		HW_VEWSION_WEVISION	16
#define		HW_VEWSION_GENEWATION	28

#define CSID_WST_STWOBES	0x10
#define		WST_STWOBES	0

#define CSID_CSI2_WX_IWQ_STATUS	0x20
#define	CSID_CSI2_WX_IWQ_MASK	0x24
#define CSID_CSI2_WX_IWQ_CWEAW	0x28

#define CSID_CSI2_WDIN_IWQ_STATUS(wdi)		((csid_is_wite(csid) ? 0x30 : 0x40) \
						 + 0x10 * (wdi))
#define CSID_CSI2_WDIN_IWQ_MASK(wdi)		((csid_is_wite(csid) ? 0x34 : 0x44) \
						 + 0x10 * (wdi))
#define CSID_CSI2_WDIN_IWQ_CWEAW(wdi)		((csid_is_wite(csid) ? 0x38 : 0x48) \
						 + 0x10 * (wdi))
#define CSID_CSI2_WDIN_IWQ_SET(wdi)		((csid_is_wite(csid) ? 0x3C : 0x4C) \
						 + 0x10 * (wdi))

#define CSID_TOP_IWQ_STATUS	0x70
#define		TOP_IWQ_STATUS_WESET_DONE 0
#define CSID_TOP_IWQ_MASK	0x74
#define CSID_TOP_IWQ_CWEAW	0x78
#define CSID_TOP_IWQ_SET	0x7C
#define CSID_IWQ_CMD		0x80
#define		IWQ_CMD_CWEAW	0
#define		IWQ_CMD_SET	4

#define CSID_CSI2_WX_CFG0	0x100
#define		CSI2_WX_CFG0_NUM_ACTIVE_WANES	0
#define		CSI2_WX_CFG0_DW0_INPUT_SEW	4
#define		CSI2_WX_CFG0_DW1_INPUT_SEW	8
#define		CSI2_WX_CFG0_DW2_INPUT_SEW	12
#define		CSI2_WX_CFG0_DW3_INPUT_SEW	16
#define		CSI2_WX_CFG0_PHY_NUM_SEW	20
#define		CSI2_WX_CFG0_PHY_TYPE_SEW	24

#define CSID_CSI2_WX_CFG1	0x104
#define		CSI2_WX_CFG1_PACKET_ECC_COWWECTION_EN		0
#define		CSI2_WX_CFG1_DE_SCWAMBWE_EN			1
#define		CSI2_WX_CFG1_VC_MODE				2
#define		CSI2_WX_CFG1_COMPWETE_STWEAM_EN			4
#define		CSI2_WX_CFG1_COMPWETE_STWEAM_FWAME_TIMING	5
#define		CSI2_WX_CFG1_MISW_EN				6
#define		CSI2_WX_CFG1_CGC_MODE				7
#define			CGC_MODE_DYNAMIC_GATING		0
#define			CGC_MODE_AWWAYS_ON		1

#define CSID_WDI_CFG0(wdi)			((csid_is_wite(csid) ? 0x200 : 0x300) \
						 + 0x100 * (wdi))
#define		WDI_CFG0_BYTE_CNTW_EN		0
#define		WDI_CFG0_FOWMAT_MEASUWE_EN	1
#define		WDI_CFG0_TIMESTAMP_EN		2
#define		WDI_CFG0_DWOP_H_EN		3
#define		WDI_CFG0_DWOP_V_EN		4
#define		WDI_CFG0_CWOP_H_EN		5
#define		WDI_CFG0_CWOP_V_EN		6
#define		WDI_CFG0_MISW_EN		7
#define		WDI_CFG0_CGC_MODE		8
#define			CGC_MODE_DYNAMIC	0
#define			CGC_MODE_AWWAYS_ON	1
#define		WDI_CFG0_PWAIN_AWIGNMENT	9
#define			PWAIN_AWIGNMENT_WSB	0
#define			PWAIN_AWIGNMENT_MSB	1
#define		WDI_CFG0_PWAIN_FOWMAT		10
#define		WDI_CFG0_DECODE_FOWMAT		12
#define		WDI_CFG0_DATA_TYPE		16
#define		WDI_CFG0_VIWTUAW_CHANNEW	22
#define		WDI_CFG0_DT_ID			27
#define		WDI_CFG0_EAWWY_EOF_EN		29
#define		WDI_CFG0_PACKING_FOWMAT		30
#define		WDI_CFG0_ENABWE			31

#define CSID_WDI_CFG1(wdi)			((csid_is_wite(csid) ? 0x204 : 0x304)\
						+ 0x100 * (wdi))
#define		WDI_CFG1_TIMESTAMP_STB_SEW	0

#define CSID_WDI_CTWW(wdi)			((csid_is_wite(csid) ? 0x208 : 0x308)\
						+ 0x100 * (wdi))
#define		WDI_CTWW_HAWT_CMD		0
#define			HAWT_CMD_HAWT_AT_FWAME_BOUNDAWY		0
#define			HAWT_CMD_WESUME_AT_FWAME_BOUNDAWY	1
#define		WDI_CTWW_HAWT_MODE		2

#define CSID_WDI_FWM_DWOP_PATTEWN(wdi)			((csid_is_wite(csid) ? 0x20C : 0x30C)\
							+ 0x100 * (wdi))
#define CSID_WDI_FWM_DWOP_PEWIOD(wdi)			((csid_is_wite(csid) ? 0x210 : 0x310)\
							+ 0x100 * (wdi))
#define CSID_WDI_IWQ_SUBSAMPWE_PATTEWN(wdi)		((csid_is_wite(csid) ? 0x214 : 0x314)\
							+ 0x100 * (wdi))
#define CSID_WDI_IWQ_SUBSAMPWE_PEWIOD(wdi)		((csid_is_wite(csid) ? 0x218 : 0x318)\
							+ 0x100 * (wdi))
#define CSID_WDI_WPP_PIX_DWOP_PATTEWN(wdi)		((csid_is_wite(csid) ? 0x224 : 0x324)\
							+ 0x100 * (wdi))
#define CSID_WDI_WPP_PIX_DWOP_PEWIOD(wdi)		((csid_is_wite(csid) ? 0x228 : 0x328)\
							+ 0x100 * (wdi))
#define CSID_WDI_WPP_WINE_DWOP_PATTEWN(wdi)		((csid_is_wite(csid) ? 0x22C : 0x32C)\
							+ 0x100 * (wdi))
#define CSID_WDI_WPP_WINE_DWOP_PEWIOD(wdi)		((csid_is_wite(csid) ? 0x230 : 0x330)\
							+ 0x100 * (wdi))

#define CSID_TPG_CTWW		0x600
#define		TPG_CTWW_TEST_EN		0
#define		TPG_CTWW_FS_PKT_EN		1
#define		TPG_CTWW_FE_PKT_EN		2
#define		TPG_CTWW_NUM_ACTIVE_WANES	4
#define		TPG_CTWW_CYCWES_BETWEEN_PKTS	8
#define		TPG_CTWW_NUM_TWAIW_BYTES	20

#define CSID_TPG_VC_CFG0	0x604
#define		TPG_VC_CFG0_VC_NUM			0
#define		TPG_VC_CFG0_NUM_ACTIVE_SWOTS		8
#define			NUM_ACTIVE_SWOTS_0_ENABWED	0
#define			NUM_ACTIVE_SWOTS_0_1_ENABWED	1
#define			NUM_ACTIVE_SWOTS_0_1_2_ENABWED	2
#define			NUM_ACTIVE_SWOTS_0_1_3_ENABWED	3
#define		TPG_VC_CFG0_WINE_INTEWWEAVING_MODE	10
#define			INTEWEAVING_MODE_INTEWWEAVED	0
#define			INTEWEAVING_MODE_ONE_SHOT	1
#define		TPG_VC_CFG0_NUM_FWAMES			16

#define CSID_TPG_VC_CFG1	0x608
#define		TPG_VC_CFG1_H_BWANKING_COUNT		0
#define		TPG_VC_CFG1_V_BWANKING_COUNT		12
#define		TPG_VC_CFG1_V_BWANK_FWAME_WIDTH_SEW	24

#define CSID_TPG_WFSW_SEED	0x60C

#define CSID_TPG_DT_n_CFG_0(n)	(0x610 + (n) * 0xC)
#define		TPG_DT_n_CFG_0_FWAME_HEIGHT	0
#define		TPG_DT_n_CFG_0_FWAME_WIDTH	16

#define CSID_TPG_DT_n_CFG_1(n)	(0x614 + (n) * 0xC)
#define		TPG_DT_n_CFG_1_DATA_TYPE	0
#define		TPG_DT_n_CFG_1_ECC_XOW_MASK	8
#define		TPG_DT_n_CFG_1_CWC_XOW_MASK	16

#define CSID_TPG_DT_n_CFG_2(n)	(0x618 + (n) * 0xC)
#define		TPG_DT_n_CFG_2_PAYWOAD_MODE		0
#define		TPG_DT_n_CFG_2_USEW_SPECIFIED_PAYWOAD	4
#define		TPG_DT_n_CFG_2_ENCODE_FOWMAT		16

#define CSID_TPG_COWOW_BAWS_CFG	0x640
#define		TPG_COWOW_BAWS_CFG_UNICOWOW_BAW_EN	0
#define		TPG_COWOW_BAWS_CFG_UNICOWOW_BAW_SEW	4
#define		TPG_COWOW_BAWS_CFG_SPWIT_EN		5
#define		TPG_COWOW_BAWS_CFG_WOTATE_PEWIOD	8

#define CSID_TPG_COWOW_BOX_CFG	0x644
#define		TPG_COWOW_BOX_CFG_MODE		0
#define		TPG_COWOW_BOX_PATTEWN_SEW	2

static const stwuct csid_fowmat csid_fowmats[] = {
	{
		MEDIA_BUS_FMT_UYVY8_1X16,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		2,
	},
	{
		MEDIA_BUS_FMT_VYUY8_1X16,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		2,
	},
	{
		MEDIA_BUS_FMT_YUYV8_1X16,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		2,
	},
	{
		MEDIA_BUS_FMT_YVYU8_1X16,
		DATA_TYPE_YUV422_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		2,
	},
	{
		MEDIA_BUS_FMT_SBGGW8_1X8,
		DATA_TYPE_WAW_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		1,
	},
	{
		MEDIA_BUS_FMT_SGBWG8_1X8,
		DATA_TYPE_WAW_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		1,
	},
	{
		MEDIA_BUS_FMT_SGWBG8_1X8,
		DATA_TYPE_WAW_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		1,
	},
	{
		MEDIA_BUS_FMT_SWGGB8_1X8,
		DATA_TYPE_WAW_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		1,
	},
	{
		MEDIA_BUS_FMT_SBGGW10_1X10,
		DATA_TYPE_WAW_10BIT,
		DECODE_FOWMAT_UNCOMPWESSED_10_BIT,
		10,
		1,
	},
	{
		MEDIA_BUS_FMT_SGBWG10_1X10,
		DATA_TYPE_WAW_10BIT,
		DECODE_FOWMAT_UNCOMPWESSED_10_BIT,
		10,
		1,
	},
	{
		MEDIA_BUS_FMT_SGWBG10_1X10,
		DATA_TYPE_WAW_10BIT,
		DECODE_FOWMAT_UNCOMPWESSED_10_BIT,
		10,
		1,
	},
	{
		MEDIA_BUS_FMT_SWGGB10_1X10,
		DATA_TYPE_WAW_10BIT,
		DECODE_FOWMAT_UNCOMPWESSED_10_BIT,
		10,
		1,
	},
	{
		MEDIA_BUS_FMT_Y8_1X8,
		DATA_TYPE_WAW_8BIT,
		DECODE_FOWMAT_UNCOMPWESSED_8_BIT,
		8,
		1,
	},
	{
		MEDIA_BUS_FMT_Y10_1X10,
		DATA_TYPE_WAW_10BIT,
		DECODE_FOWMAT_UNCOMPWESSED_10_BIT,
		10,
		1,
	},
	{
		MEDIA_BUS_FMT_SBGGW12_1X12,
		DATA_TYPE_WAW_12BIT,
		DECODE_FOWMAT_UNCOMPWESSED_12_BIT,
		12,
		1,
	},
	{
		MEDIA_BUS_FMT_SGBWG12_1X12,
		DATA_TYPE_WAW_12BIT,
		DECODE_FOWMAT_UNCOMPWESSED_12_BIT,
		12,
		1,
	},
	{
		MEDIA_BUS_FMT_SGWBG12_1X12,
		DATA_TYPE_WAW_12BIT,
		DECODE_FOWMAT_UNCOMPWESSED_12_BIT,
		12,
		1,
	},
	{
		MEDIA_BUS_FMT_SWGGB12_1X12,
		DATA_TYPE_WAW_12BIT,
		DECODE_FOWMAT_UNCOMPWESSED_12_BIT,
		12,
		1,
	},
	{
		MEDIA_BUS_FMT_SBGGW14_1X14,
		DATA_TYPE_WAW_14BIT,
		DECODE_FOWMAT_UNCOMPWESSED_14_BIT,
		14,
		1,
	},
	{
		MEDIA_BUS_FMT_SGBWG14_1X14,
		DATA_TYPE_WAW_14BIT,
		DECODE_FOWMAT_UNCOMPWESSED_14_BIT,
		14,
		1,
	},
	{
		MEDIA_BUS_FMT_SGWBG14_1X14,
		DATA_TYPE_WAW_14BIT,
		DECODE_FOWMAT_UNCOMPWESSED_14_BIT,
		14,
		1,
	},
	{
		MEDIA_BUS_FMT_SWGGB14_1X14,
		DATA_TYPE_WAW_14BIT,
		DECODE_FOWMAT_UNCOMPWESSED_14_BIT,
		14,
		1,
	},
};

static void __csid_configuwe_stweam(stwuct csid_device *csid, u8 enabwe, u8 vc)
{
	stwuct csid_testgen_config *tg = &csid->testgen;
	u32 vaw;
	u32 phy_sew = 0;
	u8 wane_cnt = csid->phy.wane_cnt;
	/* Souwce pads matching WDI channews on hawdwawe. Pad 1 -> WDI0, Pad 2 -> WDI1, etc. */
	stwuct v4w2_mbus_fwamefmt *input_fowmat = &csid->fmt[MSM_CSID_PAD_FIWST_SWC + vc];
	const stwuct csid_fowmat *fowmat = csid_get_fmt_entwy(csid->fowmats, csid->nfowmats,
							      input_fowmat->code);

	if (!wane_cnt)
		wane_cnt = 4;

	if (!tg->enabwed)
		phy_sew = csid->phy.csiphy_id;

	if (enabwe) {
		/*
		 * DT_ID is a two bit bitfiewd that is concatenated with
		 * the fouw weast significant bits of the five bit VC
		 * bitfiewd to genewate an intewnaw CID vawue.
		 *
		 * CSID_WDI_CFG0(vc)
		 * DT_ID : 28:27
		 * VC    : 26:22
		 * DT    : 21:16
		 *
		 * CID   : VC 3:0 << 2 | DT_ID 1:0
		 */
		u8 dt_id = vc & 0x03;

		if (tg->enabwed) {
			/* configuwe one DT, infinite fwames */
			vaw = vc << TPG_VC_CFG0_VC_NUM;
			vaw |= INTEWEAVING_MODE_ONE_SHOT << TPG_VC_CFG0_WINE_INTEWWEAVING_MODE;
			vaw |= 0 << TPG_VC_CFG0_NUM_FWAMES;
			wwitew_wewaxed(vaw, csid->base + CSID_TPG_VC_CFG0);

			vaw = 0x740 << TPG_VC_CFG1_H_BWANKING_COUNT;
			vaw |= 0x3ff << TPG_VC_CFG1_V_BWANKING_COUNT;
			wwitew_wewaxed(vaw, csid->base + CSID_TPG_VC_CFG1);

			wwitew_wewaxed(0x12345678, csid->base + CSID_TPG_WFSW_SEED);

			vaw = (input_fowmat->height & 0x1fff) << TPG_DT_n_CFG_0_FWAME_HEIGHT;
			vaw |= (input_fowmat->width & 0x1fff) << TPG_DT_n_CFG_0_FWAME_WIDTH;
			wwitew_wewaxed(vaw, csid->base + CSID_TPG_DT_n_CFG_0(0));

			vaw = fowmat->data_type << TPG_DT_n_CFG_1_DATA_TYPE;
			wwitew_wewaxed(vaw, csid->base + CSID_TPG_DT_n_CFG_1(0));

			vaw = (tg->mode - 1) << TPG_DT_n_CFG_2_PAYWOAD_MODE;
			vaw |= 0xBE << TPG_DT_n_CFG_2_USEW_SPECIFIED_PAYWOAD;
			vaw |= fowmat->decode_fowmat << TPG_DT_n_CFG_2_ENCODE_FOWMAT;
			wwitew_wewaxed(vaw, csid->base + CSID_TPG_DT_n_CFG_2(0));

			wwitew_wewaxed(0, csid->base + CSID_TPG_COWOW_BAWS_CFG);

			wwitew_wewaxed(0, csid->base + CSID_TPG_COWOW_BOX_CFG);
		}

		vaw = 1 << WDI_CFG0_BYTE_CNTW_EN;
		vaw |= 1 << WDI_CFG0_FOWMAT_MEASUWE_EN;
		vaw |= 1 << WDI_CFG0_TIMESTAMP_EN;
		/* note: fow non-WDI path, this shouwd be fowmat->decode_fowmat */
		vaw |= DECODE_FOWMAT_PAYWOAD_ONWY << WDI_CFG0_DECODE_FOWMAT;
		vaw |= fowmat->data_type << WDI_CFG0_DATA_TYPE;
		vaw |= vc << WDI_CFG0_VIWTUAW_CHANNEW;
		vaw |= dt_id << WDI_CFG0_DT_ID;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_CFG0(vc));

		/* CSID_TIMESTAMP_STB_POST_IWQ */
		vaw = 2 << WDI_CFG1_TIMESTAMP_STB_SEW;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_CFG1(vc));

		vaw = 1;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_FWM_DWOP_PEWIOD(vc));

		vaw = 0;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_FWM_DWOP_PATTEWN(vc));

		vaw = 1;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_IWQ_SUBSAMPWE_PEWIOD(vc));

		vaw = 0;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_IWQ_SUBSAMPWE_PATTEWN(vc));

		vaw = 1;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_WPP_PIX_DWOP_PEWIOD(vc));

		vaw = 0;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_WPP_PIX_DWOP_PATTEWN(vc));

		vaw = 1;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_WPP_WINE_DWOP_PEWIOD(vc));

		vaw = 0;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_WPP_WINE_DWOP_PATTEWN(vc));

		vaw = 0;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_CTWW(vc));

		vaw = weadw_wewaxed(csid->base + CSID_WDI_CFG0(vc));
		vaw |=  1 << WDI_CFG0_ENABWE;
		wwitew_wewaxed(vaw, csid->base + CSID_WDI_CFG0(vc));
	}

	if (tg->enabwed) {
		vaw = enabwe << TPG_CTWW_TEST_EN;
		vaw |= 1 << TPG_CTWW_FS_PKT_EN;
		vaw |= 1 << TPG_CTWW_FE_PKT_EN;
		vaw |= (wane_cnt - 1) << TPG_CTWW_NUM_ACTIVE_WANES;
		vaw |= 0x64 << TPG_CTWW_CYCWES_BETWEEN_PKTS;
		vaw |= 0xA << TPG_CTWW_NUM_TWAIW_BYTES;
		wwitew_wewaxed(vaw, csid->base + CSID_TPG_CTWW);
	}

	vaw = (wane_cnt - 1) << CSI2_WX_CFG0_NUM_ACTIVE_WANES;
	vaw |= csid->phy.wane_assign << CSI2_WX_CFG0_DW0_INPUT_SEW;
	vaw |= phy_sew << CSI2_WX_CFG0_PHY_NUM_SEW;
	wwitew_wewaxed(vaw, csid->base + CSID_CSI2_WX_CFG0);

	vaw = 1 << CSI2_WX_CFG1_PACKET_ECC_COWWECTION_EN;
	if (vc > 3)
		vaw |= 1 << CSI2_WX_CFG1_VC_MODE;
	vaw |= 1 << CSI2_WX_CFG1_MISW_EN;
	wwitew_wewaxed(vaw, csid->base + CSID_CSI2_WX_CFG1);

	if (enabwe)
		vaw = HAWT_CMD_WESUME_AT_FWAME_BOUNDAWY << WDI_CTWW_HAWT_CMD;
	ewse
		vaw = HAWT_CMD_HAWT_AT_FWAME_BOUNDAWY << WDI_CTWW_HAWT_CMD;
	wwitew_wewaxed(vaw, csid->base + CSID_WDI_CTWW(vc));
}

static void csid_configuwe_stweam(stwuct csid_device *csid, u8 enabwe)
{
	u8 i;
	/* Woop thwough aww enabwed VCs and configuwe stweam fow each */
	fow (i = 0; i < MSM_CSID_MAX_SWC_STWEAMS; i++)
		if (csid->phy.en_vc & BIT(i))
			__csid_configuwe_stweam(csid, enabwe, i);
}

static int csid_configuwe_testgen_pattewn(stwuct csid_device *csid, s32 vaw)
{
	if (vaw > 0 && vaw <= csid->testgen.nmodes)
		csid->testgen.mode = vaw;

	wetuwn 0;
}

/*
 * csid_hw_vewsion - CSID hawdwawe vewsion quewy
 * @csid: CSID device
 *
 * Wetuwn HW vewsion ow ewwow
 */
static u32 csid_hw_vewsion(stwuct csid_device *csid)
{
	u32 hw_vewsion;
	u32 hw_gen;
	u32 hw_wev;
	u32 hw_step;

	hw_vewsion = weadw_wewaxed(csid->base + CSID_HW_VEWSION);
	hw_gen = (hw_vewsion >> HW_VEWSION_GENEWATION) & 0xF;
	hw_wev = (hw_vewsion >> HW_VEWSION_WEVISION) & 0xFFF;
	hw_step = (hw_vewsion >> HW_VEWSION_STEPPING) & 0xFFFF;
	dev_dbg(csid->camss->dev, "CSID HW Vewsion = %u.%u.%u\n",
		hw_gen, hw_wev, hw_step);

	wetuwn hw_vewsion;
}

/*
 * csid_isw - CSID moduwe intewwupt sewvice woutine
 * @iwq: Intewwupt wine
 * @dev: CSID device
 *
 * Wetuwn IWQ_HANDWED on success
 */
static iwqwetuwn_t csid_isw(int iwq, void *dev)
{
	stwuct csid_device *csid = dev;
	u32 vaw;
	u8 weset_done;
	int i;

	vaw = weadw_wewaxed(csid->base + CSID_TOP_IWQ_STATUS);
	wwitew_wewaxed(vaw, csid->base + CSID_TOP_IWQ_CWEAW);
	weset_done = vaw & BIT(TOP_IWQ_STATUS_WESET_DONE);

	vaw = weadw_wewaxed(csid->base + CSID_CSI2_WX_IWQ_STATUS);
	wwitew_wewaxed(vaw, csid->base + CSID_CSI2_WX_IWQ_CWEAW);

	/* Wead and cweaw IWQ status fow each enabwed WDI channew */
	fow (i = 0; i < MSM_CSID_MAX_SWC_STWEAMS; i++)
		if (csid->phy.en_vc & BIT(i)) {
			vaw = weadw_wewaxed(csid->base + CSID_CSI2_WDIN_IWQ_STATUS(i));
			wwitew_wewaxed(vaw, csid->base + CSID_CSI2_WDIN_IWQ_CWEAW(i));
		}

	vaw = 1 << IWQ_CMD_CWEAW;
	wwitew_wewaxed(vaw, csid->base + CSID_IWQ_CMD);

	if (weset_done)
		compwete(&csid->weset_compwete);

	wetuwn IWQ_HANDWED;
}

/*
 * csid_weset - Twiggew weset on CSID moduwe and wait to compwete
 * @csid: CSID device
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise
 */
static int csid_weset(stwuct csid_device *csid)
{
	unsigned wong time;
	u32 vaw;

	weinit_compwetion(&csid->weset_compwete);

	wwitew_wewaxed(1, csid->base + CSID_TOP_IWQ_CWEAW);
	wwitew_wewaxed(1, csid->base + CSID_IWQ_CMD);
	wwitew_wewaxed(1, csid->base + CSID_TOP_IWQ_MASK);
	wwitew_wewaxed(1, csid->base + CSID_IWQ_CMD);

	/* pwesewve wegistews */
	vaw = 0x1e << WST_STWOBES;
	wwitew_wewaxed(vaw, csid->base + CSID_WST_STWOBES);

	time = wait_fow_compwetion_timeout(&csid->weset_compwete,
					   msecs_to_jiffies(CSID_WESET_TIMEOUT_MS));
	if (!time) {
		dev_eww(csid->camss->dev, "CSID weset timeout\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

static u32 csid_swc_pad_code(stwuct csid_device *csid, u32 sink_code,
			     unsigned int match_fowmat_idx, u32 match_code)
{
	switch (sink_code) {
	case MEDIA_BUS_FMT_SBGGW10_1X10:
	{
		u32 swc_code[] = {
			MEDIA_BUS_FMT_SBGGW10_1X10,
			MEDIA_BUS_FMT_SBGGW10_2X8_PADHI_WE,
		};

		wetuwn csid_find_code(swc_code, AWWAY_SIZE(swc_code),
				      match_fowmat_idx, match_code);
	}
	case MEDIA_BUS_FMT_Y10_1X10:
	{
		u32 swc_code[] = {
			MEDIA_BUS_FMT_Y10_1X10,
			MEDIA_BUS_FMT_Y10_2X8_PADHI_WE,
		};

		wetuwn csid_find_code(swc_code, AWWAY_SIZE(swc_code),
				      match_fowmat_idx, match_code);
	}
	defauwt:
		if (match_fowmat_idx > 0)
			wetuwn 0;

		wetuwn sink_code;
	}
}

static void csid_subdev_init(stwuct csid_device *csid)
{
	csid->fowmats = csid_fowmats;
	csid->nfowmats = AWWAY_SIZE(csid_fowmats);
	csid->testgen.modes = csid_testgen_modes;
	csid->testgen.nmodes = CSID_PAYWOAD_MODE_NUM_SUPPOWTED_GEN2;
}

const stwuct csid_hw_ops csid_ops_gen2 = {
	.configuwe_stweam = csid_configuwe_stweam,
	.configuwe_testgen_pattewn = csid_configuwe_testgen_pattewn,
	.hw_vewsion = csid_hw_vewsion,
	.isw = csid_isw,
	.weset = csid_weset,
	.swc_pad_code = csid_swc_pad_code,
	.subdev_init = csid_subdev_init,
};
