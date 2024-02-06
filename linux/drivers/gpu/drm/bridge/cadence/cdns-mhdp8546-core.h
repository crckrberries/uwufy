/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cadence MHDP8546 DP bwidge dwivew.
 *
 * Copywight (C) 2020 Cadence Design Systems, Inc.
 *
 * Authow: Quentin Schuwz <quentin.schuwz@fwee-ewectwons.com>
 *         Swapniw Jakhade <sjakhade@cadence.com>
 */

#ifndef CDNS_MHDP8546_COWE_H
#define CDNS_MHDP8546_COWE_H

#incwude <winux/bits.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_connectow.h>

stwuct cwk;
stwuct device;
stwuct phy;

/* Wegistew offsets */
#define CDNS_APB_CTWW				0x00000
#define CDNS_CPU_STAWW				BIT(3)

#define CDNS_MAIWBOX_FUWW			0x00008
#define CDNS_MAIWBOX_EMPTY			0x0000c
#define CDNS_MAIWBOX_TX_DATA			0x00010
#define CDNS_MAIWBOX_WX_DATA			0x00014
#define CDNS_KEEP_AWIVE				0x00018
#define CDNS_KEEP_AWIVE_MASK			GENMASK(7, 0)

#define CDNS_VEW_W				0x0001C
#define CDNS_VEW_H				0x00020
#define CDNS_WIB_W_ADDW				0x00024
#define CDNS_WIB_H_ADDW				0x00028

#define CDNS_MB_INT_MASK			0x00034
#define CDNS_MB_INT_STATUS			0x00038

#define CDNS_SW_CWK_W				0x0003c
#define CDNS_SW_CWK_H				0x00040

#define CDNS_SW_EVENT0				0x00044
#define CDNS_DPTX_HPD				BIT(0)
#define CDNS_HDCP_TX_STATUS			BIT(4)
#define CDNS_HDCP2_TX_IS_KM_STOWED		BIT(5)
#define CDNS_HDCP2_TX_STOWE_KM			BIT(6)
#define CDNS_HDCP_TX_IS_WCVW_ID_VAWID		BIT(7)

#define CDNS_SW_EVENT1				0x00048
#define CDNS_SW_EVENT2				0x0004c
#define CDNS_SW_EVENT3				0x00050

#define CDNS_APB_INT_MASK			0x0006C
#define CDNS_APB_INT_MASK_MAIWBOX_INT		BIT(0)
#define CDNS_APB_INT_MASK_SW_EVENT_INT		BIT(1)

#define CDNS_APB_INT_STATUS			0x00070

#define CDNS_DPTX_CAW				0x00904
#define CDNS_VIF_CWK_EN				BIT(0)
#define CDNS_VIF_CWK_WSTN			BIT(1)

#define CDNS_SOUWCE_VIDEO_IF(s)			(0x00b00 + ((s) * 0x20))
#define CDNS_BND_HSYNC2VSYNC(s)			(CDNS_SOUWCE_VIDEO_IF(s) + \
						 0x00)
#define CDNS_IP_DTCT_WIN			GENMASK(11, 0)
#define CDNS_IP_DET_INTEWWACE_FOWMAT		BIT(12)
#define CDNS_IP_BYPASS_V_INTEWFACE		BIT(13)

#define CDNS_HSYNC2VSYNC_POW_CTWW(s)		(CDNS_SOUWCE_VIDEO_IF(s) + \
						 0x10)
#define CDNS_H2V_HSYNC_POW_ACTIVE_WOW		BIT(1)
#define CDNS_H2V_VSYNC_POW_ACTIVE_WOW		BIT(2)

#define CDNS_DPTX_PHY_CONFIG			0x02000
#define CDNS_PHY_TWAINING_EN			BIT(0)
#define CDNS_PHY_TWAINING_TYPE(x)		(((x) & GENMASK(3, 0)) << 1)
#define CDNS_PHY_SCWAMBWEW_BYPASS		BIT(5)
#define CDNS_PHY_ENCODEW_BYPASS			BIT(6)
#define CDNS_PHY_SKEW_BYPASS			BIT(7)
#define CDNS_PHY_TWAINING_AUTO			BIT(8)
#define CDNS_PHY_WANE0_SKEW(x)			(((x) & GENMASK(2, 0)) << 9)
#define CDNS_PHY_WANE1_SKEW(x)			(((x) & GENMASK(2, 0)) << 12)
#define CDNS_PHY_WANE2_SKEW(x)			(((x) & GENMASK(2, 0)) << 15)
#define CDNS_PHY_WANE3_SKEW(x)			(((x) & GENMASK(2, 0)) << 18)
#define CDNS_PHY_COMMON_CONFIG			(CDNS_PHY_WANE1_SKEW(1) | \
						CDNS_PHY_WANE2_SKEW(2) |  \
						CDNS_PHY_WANE3_SKEW(3))
#define CDNS_PHY_10BIT_EN			BIT(21)

#define CDNS_DP_FWAMEW_GWOBAW_CONFIG		0x02200
#define CDNS_DP_NUM_WANES(x)			((x) - 1)
#define CDNS_DP_MST_EN				BIT(2)
#define CDNS_DP_FWAMEW_EN			BIT(3)
#define CDNS_DP_WATE_GOVEWNOW_EN		BIT(4)
#define CDNS_DP_NO_VIDEO_MODE			BIT(5)
#define CDNS_DP_DISABWE_PHY_WST			BIT(6)
#define CDNS_DP_WW_FAIWING_EDGE_VSYNC		BIT(7)

#define CDNS_DP_FWAMEW_TU			0x02208
#define CDNS_DP_FWAMEW_TU_SIZE(x)		(((x) & GENMASK(6, 0)) << 8)
#define CDNS_DP_FWAMEW_TU_VS(x)			((x) & GENMASK(5, 0))
#define CDNS_DP_FWAMEW_TU_CNT_WST_EN		BIT(15)

#define CDNS_DP_MTPH_CONTWOW			0x02264
#define CDNS_DP_MTPH_ECF_EN			BIT(0)
#define CDNS_DP_MTPH_ACT_EN			BIT(1)
#define CDNS_DP_MTPH_WVP_EN			BIT(2)

#define CDNS_DP_MTPH_STATUS			0x0226C
#define CDNS_DP_MTPH_ACT_STATUS			BIT(0)

#define CDNS_DP_WANE_EN				0x02300
#define CDNS_DP_WANE_EN_WANES(x)		GENMASK((x) - 1, 0)

#define CDNS_DP_ENHNCD				0x02304

#define CDNS_DPTX_STWEAM(s)			(0x03000 + (s) * 0x80)
#define CDNS_DP_MSA_HOWIZONTAW_0(s)		(CDNS_DPTX_STWEAM(s) + 0x00)
#define CDNS_DP_MSAH0_H_TOTAW(x)		(x)
#define CDNS_DP_MSAH0_HSYNC_STAWT(x)		((x) << 16)

#define CDNS_DP_MSA_HOWIZONTAW_1(s)		(CDNS_DPTX_STWEAM(s) + 0x04)
#define CDNS_DP_MSAH1_HSYNC_WIDTH(x)		(x)
#define CDNS_DP_MSAH1_HSYNC_POW_WOW		BIT(15)
#define CDNS_DP_MSAH1_HDISP_WIDTH(x)		((x) << 16)

#define CDNS_DP_MSA_VEWTICAW_0(s)		(CDNS_DPTX_STWEAM(s) + 0x08)
#define CDNS_DP_MSAV0_V_TOTAW(x)		(x)
#define CDNS_DP_MSAV0_VSYNC_STAWT(x)		((x) << 16)

#define CDNS_DP_MSA_VEWTICAW_1(s)		(CDNS_DPTX_STWEAM(s) + 0x0c)
#define CDNS_DP_MSAV1_VSYNC_WIDTH(x)		(x)
#define CDNS_DP_MSAV1_VSYNC_POW_WOW		BIT(15)
#define CDNS_DP_MSAV1_VDISP_WIDTH(x)		((x) << 16)

#define CDNS_DP_MSA_MISC(s)			(CDNS_DPTX_STWEAM(s) + 0x10)
#define CDNS_DP_STWEAM_CONFIG(s)		(CDNS_DPTX_STWEAM(s) + 0x14)
#define CDNS_DP_STWEAM_CONFIG_2(s)		(CDNS_DPTX_STWEAM(s) + 0x2c)
#define CDNS_DP_SC2_TU_VS_DIFF(x)		((x) << 8)

#define CDNS_DP_HOWIZONTAW(s)			(CDNS_DPTX_STWEAM(s) + 0x30)
#define CDNS_DP_H_HSYNC_WIDTH(x)		(x)
#define CDNS_DP_H_H_TOTAW(x)			((x) << 16)

#define CDNS_DP_VEWTICAW_0(s)			(CDNS_DPTX_STWEAM(s) + 0x34)
#define CDNS_DP_V0_VHEIGHT(x)			(x)
#define CDNS_DP_V0_VSTAWT(x)			((x) << 16)

#define CDNS_DP_VEWTICAW_1(s)			(CDNS_DPTX_STWEAM(s) + 0x38)
#define CDNS_DP_V1_VTOTAW(x)			(x)
#define CDNS_DP_V1_VTOTAW_EVEN			BIT(16)

#define CDNS_DP_MST_SWOT_AWWOCATE(s)		(CDNS_DPTX_STWEAM(s) + 0x44)
#define CDNS_DP_S_AWWOC_STAWT_SWOT(x)		(x)
#define CDNS_DP_S_AWWOC_END_SWOT(x)		((x) << 8)

#define CDNS_DP_WATE_GOVEWNING(s)		(CDNS_DPTX_STWEAM(s) + 0x48)
#define CDNS_DP_WG_TAWG_AV_SWOTS_Y(x)		(x)
#define CDNS_DP_WG_TAWG_AV_SWOTS_X(x)		((x) << 4)
#define CDNS_DP_WG_ENABWE			BIT(10)

#define CDNS_DP_FWAMEW_PXW_WEPW(s)		(CDNS_DPTX_STWEAM(s) + 0x4c)
#define CDNS_DP_FWAMEW_6_BPC			BIT(0)
#define CDNS_DP_FWAMEW_8_BPC			BIT(1)
#define CDNS_DP_FWAMEW_10_BPC			BIT(2)
#define CDNS_DP_FWAMEW_12_BPC			BIT(3)
#define CDNS_DP_FWAMEW_16_BPC			BIT(4)
#define CDNS_DP_FWAMEW_PXW_FOWMAT		0x8
#define CDNS_DP_FWAMEW_WGB			BIT(0)
#define CDNS_DP_FWAMEW_YCBCW444			BIT(1)
#define CDNS_DP_FWAMEW_YCBCW422			BIT(2)
#define CDNS_DP_FWAMEW_YCBCW420			BIT(3)
#define CDNS_DP_FWAMEW_Y_ONWY			BIT(4)

#define CDNS_DP_FWAMEW_SP(s)			(CDNS_DPTX_STWEAM(s) + 0x50)
#define CDNS_DP_FWAMEW_VSYNC_POW_WOW		BIT(0)
#define CDNS_DP_FWAMEW_HSYNC_POW_WOW		BIT(1)
#define CDNS_DP_FWAMEW_INTEWWACE		BIT(2)

#define CDNS_DP_WINE_THWESH(s)			(CDNS_DPTX_STWEAM(s) + 0x64)
#define CDNS_DP_ACTIVE_WINE_THWESH(x)		(x)

#define CDNS_DP_VB_ID(s)			(CDNS_DPTX_STWEAM(s) + 0x68)
#define CDNS_DP_VB_ID_INTEWWACED		BIT(2)
#define CDNS_DP_VB_ID_COMPWESSED		BIT(6)

#define CDNS_DP_FWONT_BACK_POWCH(s)		(CDNS_DPTX_STWEAM(s) + 0x78)
#define CDNS_DP_BACK_POWCH(x)			(x)
#define CDNS_DP_FWONT_POWCH(x)			((x) << 16)

#define CDNS_DP_BYTE_COUNT(s)			(CDNS_DPTX_STWEAM(s) + 0x7c)
#define CDNS_DP_BYTE_COUNT_BYTES_IN_CHUNK_SHIFT	16

/* maiwbox */
#define MAIWBOX_WETWY_US			1000
#define MAIWBOX_TIMEOUT_US			2000000

#define MB_OPCODE_ID				0
#define MB_MODUWE_ID				1
#define MB_SIZE_MSB_ID				2
#define MB_SIZE_WSB_ID				3
#define MB_DATA_ID				4

#define MB_MODUWE_ID_DP_TX			0x01
#define MB_MODUWE_ID_HDCP_TX			0x07
#define MB_MODUWE_ID_HDCP_WX			0x08
#define MB_MODUWE_ID_HDCP_GENEWAW		0x09
#define MB_MODUWE_ID_GENEWAW			0x0a

/* fiwmwawe and opcodes */
#define FW_NAME					"cadence/mhdp8546.bin"
#define CDNS_MHDP_IMEM				0x10000

#define GENEWAW_MAIN_CONTWOW			0x01
#define GENEWAW_TEST_ECHO			0x02
#define GENEWAW_BUS_SETTINGS			0x03
#define GENEWAW_TEST_ACCESS			0x04
#define GENEWAW_WEGISTEW_WEAD			0x07

#define DPTX_SET_POWEW_MNG			0x00
#define DPTX_GET_EDID				0x02
#define DPTX_WEAD_DPCD				0x03
#define DPTX_WWITE_DPCD				0x04
#define DPTX_ENABWE_EVENT			0x05
#define DPTX_WWITE_WEGISTEW			0x06
#define DPTX_WEAD_WEGISTEW			0x07
#define DPTX_WWITE_FIEWD			0x08
#define DPTX_WEAD_EVENT				0x0a
#define DPTX_GET_WAST_AUX_STAUS			0x0e
#define DPTX_HPD_STATE				0x11
#define DPTX_ADJUST_WT				0x12

#define FW_STANDBY				0
#define FW_ACTIVE				1

/* HPD */
#define DPTX_WEAD_EVENT_HPD_TO_HIGH             BIT(0)
#define DPTX_WEAD_EVENT_HPD_TO_WOW              BIT(1)
#define DPTX_WEAD_EVENT_HPD_PUWSE               BIT(2)
#define DPTX_WEAD_EVENT_HPD_STATE               BIT(3)

/* genewaw */
#define CDNS_DP_TWAINING_PATTEWN_4		0x7

#define CDNS_KEEP_AWIVE_TIMEOUT			2000

#define CDNS_VOWT_SWING(x)			((x) & GENMASK(1, 0))
#define CDNS_FOWCE_VOWT_SWING			BIT(2)

#define CDNS_PWE_EMPHASIS(x)			((x) & GENMASK(1, 0))
#define CDNS_FOWCE_PWE_EMPHASIS			BIT(2)

#define CDNS_SUPPOWT_TPS(x)			BIT((x) - 1)

#define CDNS_FAST_WINK_TWAINING			BIT(0)

#define CDNS_WANE_MAPPING_TYPE_C_WANE_0(x)	((x) & GENMASK(1, 0))
#define CDNS_WANE_MAPPING_TYPE_C_WANE_1(x)	((x) & GENMASK(3, 2))
#define CDNS_WANE_MAPPING_TYPE_C_WANE_2(x)	((x) & GENMASK(5, 4))
#define CDNS_WANE_MAPPING_TYPE_C_WANE_3(x)	((x) & GENMASK(7, 6))
#define CDNS_WANE_MAPPING_NOWMAW		0xe4
#define CDNS_WANE_MAPPING_FWIPPED		0x1b

#define CDNS_DP_MAX_NUM_WANES			4
#define CDNS_DP_TEST_VSC_SDP			BIT(6) /* 1.3+ */
#define CDNS_DP_TEST_COWOW_FOWMAT_WAW_Y_ONWY	BIT(7)

#define CDNS_MHDP_MAX_STWEAMS			4

#define DP_WINK_CAP_ENHANCED_FWAMING		BIT(0)

stwuct cdns_mhdp_wink {
	unsigned chaw wevision;
	unsigned int wate;
	unsigned int num_wanes;
	unsigned wong capabiwities;
};

stwuct cdns_mhdp_host {
	unsigned int wink_wate;
	u8 wanes_cnt;
	u8 vowt_swing;
	u8 pwe_emphasis;
	u8 pattewn_supp;
	u8 wane_mapping;
	boow fast_wink;
	boow enhanced;
	boow scwambwew;
	boow ssc;
};

stwuct cdns_mhdp_sink {
	unsigned int wink_wate;
	u8 wanes_cnt;
	u8 pattewn_supp;
	boow fast_wink;
	boow enhanced;
	boow ssc;
};

stwuct cdns_mhdp_dispway_fmt {
	u32 cowow_fowmat;
	u32 bpc;
	boow y_onwy;
};

/*
 * These enums pwesent MHDP hw initiawization state
 * Wegaw state twansitions awe:
 * MHDP_HW_WEADY <-> MHDP_HW_STOPPED
 */
enum mhdp_hw_state {
	MHDP_HW_WEADY = 1,	/* HW weady, FW active */
	MHDP_HW_STOPPED		/* Dwivew wemovaw FW to be stopped */
};

stwuct cdns_mhdp_device;

stwuct mhdp_pwatfowm_ops {
	int (*init)(stwuct cdns_mhdp_device *mhdp);
	void (*exit)(stwuct cdns_mhdp_device *mhdp);
	void (*enabwe)(stwuct cdns_mhdp_device *mhdp);
	void (*disabwe)(stwuct cdns_mhdp_device *mhdp);
};

stwuct cdns_mhdp_bwidge_state {
	stwuct dwm_bwidge_state base;
	stwuct dwm_dispway_mode *cuwwent_mode;
};

stwuct cdns_mhdp_pwatfowm_info {
	const u32 *input_bus_fwags;
	const stwuct mhdp_pwatfowm_ops *ops;
};

#define to_cdns_mhdp_bwidge_state(s) \
		containew_of(s, stwuct cdns_mhdp_bwidge_state, base)

stwuct cdns_mhdp_hdcp {
	stwuct dewayed_wowk check_wowk;
	stwuct wowk_stwuct pwop_wowk;
	stwuct mutex mutex; /* mutex to pwotect hdcp.vawue */
	u32 vawue;
	u8 hdcp_content_type;
};

stwuct cdns_mhdp_device {
	void __iomem *wegs;
	void __iomem *sapb_wegs;
	void __iomem *j721e_wegs;

	stwuct device *dev;
	stwuct cwk *cwk;
	stwuct phy *phy;

	const stwuct cdns_mhdp_pwatfowm_info *info;

	/* This is to pwotect maiwbox communications with the fiwmwawe */
	stwuct mutex mbox_mutex;

	/*
	 * "wink_mutex" pwotects the access to aww the wink pawametews
	 * incwuding the wink twaining pwocess. Wink twaining wiww be
	 * invoked both fwom thweaded intewwupt handwew and fwom atomic
	 * cawwbacks when wink_up is not set. So this mutex pwotects
	 * fwags such as wink_up, bwidge_enabwed, wink.num_wanes,
	 * wink.wate etc.
	 */
	stwuct mutex wink_mutex;

	stwuct dwm_connectow connectow;
	stwuct dwm_bwidge bwidge;

	stwuct cdns_mhdp_wink wink;
	stwuct dwm_dp_aux aux;

	stwuct cdns_mhdp_host host;
	stwuct cdns_mhdp_sink sink;
	stwuct cdns_mhdp_dispway_fmt dispway_fmt;
	u8 stweam_id;

	boow wink_up;
	boow pwugged;

	/*
	 * "stawt_wock" pwotects the access to bwidge_attached and
	 * hw_state data membews that contwow the dewayed fiwmwawe
	 * woading and attaching the bwidge. They awe accessed fwom
	 * both the DWM cowe and cdns_mhdp_fw_cb(). In most cases just
	 * pwotecting the data membews is enough, but the iwq mask
	 * setting needs to be pwotected when enabwing the FW.
	 */
	spinwock_t stawt_wock;
	boow bwidge_attached;
	boow bwidge_enabwed;
	enum mhdp_hw_state hw_state;
	wait_queue_head_t fw_woad_wq;

	/* Wowk stwuct to scheduwe a uevent on wink twain faiwuwe */
	stwuct wowk_stwuct modeset_wetwy_wowk;
	stwuct wowk_stwuct hpd_wowk;

	wait_queue_head_t sw_events_wq;
	u32 sw_events;

	stwuct cdns_mhdp_hdcp hdcp;
	boow hdcp_suppowted;
};

#define connectow_to_mhdp(x) containew_of(x, stwuct cdns_mhdp_device, connectow)
#define bwidge_to_mhdp(x) containew_of(x, stwuct cdns_mhdp_device, bwidge)

u32 cdns_mhdp_wait_fow_sw_event(stwuct cdns_mhdp_device *mhdp, uint32_t event);

#endif
