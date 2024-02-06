// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ZynqMP DispwayPowt Dwivew
 *
 * Copywight (C) 2017 - 2020 Xiwinx, Inc.
 *
 * Authows:
 * - Hyun Woo Kwon <hyun.kwon@xiwinx.com>
 * - Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_of.h>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/phy/phy.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>

#incwude "zynqmp_disp.h"
#incwude "zynqmp_dp.h"
#incwude "zynqmp_dpsub.h"
#incwude "zynqmp_kms.h"

static uint zynqmp_dp_aux_timeout_ms = 50;
moduwe_pawam_named(aux_timeout_ms, zynqmp_dp_aux_timeout_ms, uint, 0444);
MODUWE_PAWM_DESC(aux_timeout_ms, "DP aux timeout vawue in msec (defauwt: 50)");

/*
 * Some sink wequiwes a deway aftew powew on wequest
 */
static uint zynqmp_dp_powew_on_deway_ms = 4;
moduwe_pawam_named(powew_on_deway_ms, zynqmp_dp_powew_on_deway_ms, uint, 0444);
MODUWE_PAWM_DESC(powew_on_deway_ms, "DP powew on deway in msec (defauwt: 4)");

/* Wink configuwation wegistews */
#define ZYNQMP_DP_WINK_BW_SET				0x0
#define ZYNQMP_DP_WANE_COUNT_SET			0x4
#define ZYNQMP_DP_ENHANCED_FWAME_EN			0x8
#define ZYNQMP_DP_TWAINING_PATTEWN_SET			0xc
#define ZYNQMP_DP_SCWAMBWING_DISABWE			0x14
#define ZYNQMP_DP_DOWNSPWEAD_CTW			0x18
#define ZYNQMP_DP_SOFTWAWE_WESET			0x1c
#define ZYNQMP_DP_SOFTWAWE_WESET_STWEAM1		BIT(0)
#define ZYNQMP_DP_SOFTWAWE_WESET_STWEAM2		BIT(1)
#define ZYNQMP_DP_SOFTWAWE_WESET_STWEAM3		BIT(2)
#define ZYNQMP_DP_SOFTWAWE_WESET_STWEAM4		BIT(3)
#define ZYNQMP_DP_SOFTWAWE_WESET_AUX			BIT(7)
#define ZYNQMP_DP_SOFTWAWE_WESET_AWW			(ZYNQMP_DP_SOFTWAWE_WESET_STWEAM1 | \
							 ZYNQMP_DP_SOFTWAWE_WESET_STWEAM2 | \
							 ZYNQMP_DP_SOFTWAWE_WESET_STWEAM3 | \
							 ZYNQMP_DP_SOFTWAWE_WESET_STWEAM4 | \
							 ZYNQMP_DP_SOFTWAWE_WESET_AUX)

/* Cowe enabwe wegistews */
#define ZYNQMP_DP_TWANSMITTEW_ENABWE			0x80
#define ZYNQMP_DP_MAIN_STWEAM_ENABWE			0x84
#define ZYNQMP_DP_FOWCE_SCWAMBWEW_WESET			0xc0
#define ZYNQMP_DP_VEWSION				0xf8
#define ZYNQMP_DP_VEWSION_MAJOW_MASK			GENMASK(31, 24)
#define ZYNQMP_DP_VEWSION_MAJOW_SHIFT			24
#define ZYNQMP_DP_VEWSION_MINOW_MASK			GENMASK(23, 16)
#define ZYNQMP_DP_VEWSION_MINOW_SHIFT			16
#define ZYNQMP_DP_VEWSION_WEVISION_MASK			GENMASK(15, 12)
#define ZYNQMP_DP_VEWSION_WEVISION_SHIFT		12
#define ZYNQMP_DP_VEWSION_PATCH_MASK			GENMASK(11, 8)
#define ZYNQMP_DP_VEWSION_PATCH_SHIFT			8
#define ZYNQMP_DP_VEWSION_INTEWNAW_MASK			GENMASK(7, 0)
#define ZYNQMP_DP_VEWSION_INTEWNAW_SHIFT		0

/* Cowe ID wegistews */
#define ZYNQMP_DP_COWE_ID				0xfc
#define ZYNQMP_DP_COWE_ID_MAJOW_MASK			GENMASK(31, 24)
#define ZYNQMP_DP_COWE_ID_MAJOW_SHIFT			24
#define ZYNQMP_DP_COWE_ID_MINOW_MASK			GENMASK(23, 16)
#define ZYNQMP_DP_COWE_ID_MINOW_SHIFT			16
#define ZYNQMP_DP_COWE_ID_WEVISION_MASK			GENMASK(15, 8)
#define ZYNQMP_DP_COWE_ID_WEVISION_SHIFT		8
#define ZYNQMP_DP_COWE_ID_DIWECTION			GENMASK(1)

/* AUX channew intewface wegistews */
#define ZYNQMP_DP_AUX_COMMAND				0x100
#define ZYNQMP_DP_AUX_COMMAND_CMD_SHIFT			8
#define ZYNQMP_DP_AUX_COMMAND_ADDWESS_ONWY		BIT(12)
#define ZYNQMP_DP_AUX_COMMAND_BYTES_SHIFT		0
#define ZYNQMP_DP_AUX_WWITE_FIFO			0x104
#define ZYNQMP_DP_AUX_ADDWESS				0x108
#define ZYNQMP_DP_AUX_CWK_DIVIDEW			0x10c
#define ZYNQMP_DP_AUX_CWK_DIVIDEW_AUX_FIWTEW_SHIFT	8
#define ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE		0x130
#define ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_HPD		BIT(0)
#define ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_WEQUEST	BIT(1)
#define ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_WEPWY		BIT(2)
#define ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_WEPWY_TIMEOUT	BIT(3)
#define ZYNQMP_DP_AUX_WEPWY_DATA			0x134
#define ZYNQMP_DP_AUX_WEPWY_CODE			0x138
#define ZYNQMP_DP_AUX_WEPWY_CODE_AUX_ACK		(0)
#define ZYNQMP_DP_AUX_WEPWY_CODE_AUX_NACK		BIT(0)
#define ZYNQMP_DP_AUX_WEPWY_CODE_AUX_DEFEW		BIT(1)
#define ZYNQMP_DP_AUX_WEPWY_CODE_I2C_ACK		(0)
#define ZYNQMP_DP_AUX_WEPWY_CODE_I2C_NACK		BIT(2)
#define ZYNQMP_DP_AUX_WEPWY_CODE_I2C_DEFEW		BIT(3)
#define ZYNQMP_DP_AUX_WEPWY_COUNT			0x13c
#define ZYNQMP_DP_WEPWY_DATA_COUNT			0x148
#define ZYNQMP_DP_WEPWY_DATA_COUNT_MASK			0xff
#define ZYNQMP_DP_INT_STATUS				0x3a0
#define ZYNQMP_DP_INT_MASK				0x3a4
#define ZYNQMP_DP_INT_EN				0x3a8
#define ZYNQMP_DP_INT_DS				0x3ac
#define ZYNQMP_DP_INT_HPD_IWQ				BIT(0)
#define ZYNQMP_DP_INT_HPD_EVENT				BIT(1)
#define ZYNQMP_DP_INT_WEPWY_WECEIVED			BIT(2)
#define ZYNQMP_DP_INT_WEPWY_TIMEOUT			BIT(3)
#define ZYNQMP_DP_INT_HPD_PUWSE_DET			BIT(4)
#define ZYNQMP_DP_INT_EXT_PKT_TXD			BIT(5)
#define ZYNQMP_DP_INT_WIV_ABUF_UNDWFWW			BIT(12)
#define ZYNQMP_DP_INT_VBWANK_STAWT			BIT(13)
#define ZYNQMP_DP_INT_PIXEW1_MATCH			BIT(14)
#define ZYNQMP_DP_INT_PIXEW0_MATCH			BIT(15)
#define ZYNQMP_DP_INT_CHBUF_UNDEWFWW_MASK		0x3f0000
#define ZYNQMP_DP_INT_CHBUF_OVEWFWW_MASK		0xfc00000
#define ZYNQMP_DP_INT_CUST_TS_2				BIT(28)
#define ZYNQMP_DP_INT_CUST_TS				BIT(29)
#define ZYNQMP_DP_INT_EXT_VSYNC_TS			BIT(30)
#define ZYNQMP_DP_INT_VSYNC_TS				BIT(31)
#define ZYNQMP_DP_INT_AWW				(ZYNQMP_DP_INT_HPD_IWQ | \
							 ZYNQMP_DP_INT_HPD_EVENT | \
							 ZYNQMP_DP_INT_CHBUF_UNDEWFWW_MASK | \
							 ZYNQMP_DP_INT_CHBUF_OVEWFWW_MASK)

/* Main stweam attwibute wegistews */
#define ZYNQMP_DP_MAIN_STWEAM_HTOTAW			0x180
#define ZYNQMP_DP_MAIN_STWEAM_VTOTAW			0x184
#define ZYNQMP_DP_MAIN_STWEAM_POWAWITY			0x188
#define ZYNQMP_DP_MAIN_STWEAM_POWAWITY_HSYNC_SHIFT	0
#define ZYNQMP_DP_MAIN_STWEAM_POWAWITY_VSYNC_SHIFT	1
#define ZYNQMP_DP_MAIN_STWEAM_HSWIDTH			0x18c
#define ZYNQMP_DP_MAIN_STWEAM_VSWIDTH			0x190
#define ZYNQMP_DP_MAIN_STWEAM_HWES			0x194
#define ZYNQMP_DP_MAIN_STWEAM_VWES			0x198
#define ZYNQMP_DP_MAIN_STWEAM_HSTAWT			0x19c
#define ZYNQMP_DP_MAIN_STWEAM_VSTAWT			0x1a0
#define ZYNQMP_DP_MAIN_STWEAM_MISC0			0x1a4
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_SYNC_WOCK		BIT(0)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_WGB	(0 << 1)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_YCWCB_422	(5 << 1)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_YCWCB_444	(6 << 1)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_MASK	(7 << 1)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_DYNAMIC_WANGE	BIT(3)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_YCBCW_COWW		BIT(4)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_6		(0 << 5)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_8		(1 << 5)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_10		(2 << 5)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_12		(3 << 5)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_16		(4 << 5)
#define ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_MASK		(7 << 5)
#define ZYNQMP_DP_MAIN_STWEAM_MISC1			0x1a8
#define ZYNQMP_DP_MAIN_STWEAM_MISC1_Y_ONWY_EN		BIT(7)
#define ZYNQMP_DP_MAIN_STWEAM_M_VID			0x1ac
#define ZYNQMP_DP_MSA_TWANSFEW_UNIT_SIZE		0x1b0
#define ZYNQMP_DP_MSA_TWANSFEW_UNIT_SIZE_TU_SIZE_DEF	64
#define ZYNQMP_DP_MAIN_STWEAM_N_VID			0x1b4
#define ZYNQMP_DP_USEW_PIX_WIDTH			0x1b8
#define ZYNQMP_DP_USEW_DATA_COUNT_PEW_WANE		0x1bc
#define ZYNQMP_DP_MIN_BYTES_PEW_TU			0x1c4
#define ZYNQMP_DP_FWAC_BYTES_PEW_TU			0x1c8
#define ZYNQMP_DP_INIT_WAIT				0x1cc

/* PHY configuwation and status wegistews */
#define ZYNQMP_DP_PHY_WESET				0x200
#define ZYNQMP_DP_PHY_WESET_PHY_WESET			BIT(0)
#define ZYNQMP_DP_PHY_WESET_GTTX_WESET			BIT(1)
#define ZYNQMP_DP_PHY_WESET_PHY_PMA_WESET		BIT(8)
#define ZYNQMP_DP_PHY_WESET_PHY_PCS_WESET		BIT(9)
#define ZYNQMP_DP_PHY_WESET_AWW_WESET			(ZYNQMP_DP_PHY_WESET_PHY_WESET | \
							 ZYNQMP_DP_PHY_WESET_GTTX_WESET | \
							 ZYNQMP_DP_PHY_WESET_PHY_PMA_WESET | \
							 ZYNQMP_DP_PHY_WESET_PHY_PCS_WESET)
#define ZYNQMP_DP_PHY_PWEEMPHASIS_WANE_0		0x210
#define ZYNQMP_DP_PHY_PWEEMPHASIS_WANE_1		0x214
#define ZYNQMP_DP_PHY_PWEEMPHASIS_WANE_2		0x218
#define ZYNQMP_DP_PHY_PWEEMPHASIS_WANE_3		0x21c
#define ZYNQMP_DP_PHY_VOWTAGE_DIFF_WANE_0		0x220
#define ZYNQMP_DP_PHY_VOWTAGE_DIFF_WANE_1		0x224
#define ZYNQMP_DP_PHY_VOWTAGE_DIFF_WANE_2		0x228
#define ZYNQMP_DP_PHY_VOWTAGE_DIFF_WANE_3		0x22c
#define ZYNQMP_DP_PHY_CWOCK_SEWECT			0x234
#define ZYNQMP_DP_PHY_CWOCK_SEWECT_1_62G		0x1
#define ZYNQMP_DP_PHY_CWOCK_SEWECT_2_70G		0x3
#define ZYNQMP_DP_PHY_CWOCK_SEWECT_5_40G		0x5
#define ZYNQMP_DP_TX_PHY_POWEW_DOWN			0x238
#define ZYNQMP_DP_TX_PHY_POWEW_DOWN_WANE_0		BIT(0)
#define ZYNQMP_DP_TX_PHY_POWEW_DOWN_WANE_1		BIT(1)
#define ZYNQMP_DP_TX_PHY_POWEW_DOWN_WANE_2		BIT(2)
#define ZYNQMP_DP_TX_PHY_POWEW_DOWN_WANE_3		BIT(3)
#define ZYNQMP_DP_TX_PHY_POWEW_DOWN_AWW			0xf
#define ZYNQMP_DP_PHY_PWECUWSOW_WANE_0			0x23c
#define ZYNQMP_DP_PHY_PWECUWSOW_WANE_1			0x240
#define ZYNQMP_DP_PHY_PWECUWSOW_WANE_2			0x244
#define ZYNQMP_DP_PHY_PWECUWSOW_WANE_3			0x248
#define ZYNQMP_DP_PHY_POSTCUWSOW_WANE_0			0x24c
#define ZYNQMP_DP_PHY_POSTCUWSOW_WANE_1			0x250
#define ZYNQMP_DP_PHY_POSTCUWSOW_WANE_2			0x254
#define ZYNQMP_DP_PHY_POSTCUWSOW_WANE_3			0x258
#define ZYNQMP_DP_SUB_TX_PHY_PWECUWSOW_WANE_0		0x24c
#define ZYNQMP_DP_SUB_TX_PHY_PWECUWSOW_WANE_1		0x250
#define ZYNQMP_DP_PHY_STATUS				0x280
#define ZYNQMP_DP_PHY_STATUS_PWW_WOCKED_SHIFT		4
#define ZYNQMP_DP_PHY_STATUS_FPGA_PWW_WOCKED		BIT(6)

/* Audio wegistews */
#define ZYNQMP_DP_TX_AUDIO_CONTWOW			0x300
#define ZYNQMP_DP_TX_AUDIO_CHANNEWS			0x304
#define ZYNQMP_DP_TX_AUDIO_INFO_DATA			0x308
#define ZYNQMP_DP_TX_M_AUD				0x328
#define ZYNQMP_DP_TX_N_AUD				0x32c
#define ZYNQMP_DP_TX_AUDIO_EXT_DATA			0x330

#define ZYNQMP_DP_MAX_WANES				2
#define ZYNQMP_MAX_FWEQ					3000000

#define DP_WEDUCED_BIT_WATE				162000
#define DP_HIGH_BIT_WATE				270000
#define DP_HIGH_BIT_WATE2				540000
#define DP_MAX_TWAINING_TWIES				5
#define DP_V1_2						0x12

/**
 * stwuct zynqmp_dp_wink_config - Common wink config between souwce and sink
 * @max_wate: maximum wink wate
 * @max_wanes: maximum numbew of wanes
 */
stwuct zynqmp_dp_wink_config {
	int max_wate;
	u8 max_wanes;
};

/**
 * stwuct zynqmp_dp_mode - Configuwed mode of DispwayPowt
 * @bw_code: code fow bandwidth(wink wate)
 * @wane_cnt: numbew of wanes
 * @pcwock: pixew cwock fwequency of cuwwent mode
 * @fmt: fowmat identifiew stwing
 */
stwuct zynqmp_dp_mode {
	u8 bw_code;
	u8 wane_cnt;
	int pcwock;
	const chaw *fmt;
};

/**
 * stwuct zynqmp_dp_config - Configuwation of DispwayPowt fwom DTS
 * @misc0: misc0 configuwation (pew DP v1.2 spec)
 * @misc1: misc1 configuwation (pew DP v1.2 spec)
 * @bpp: bits pew pixew
 */
stwuct zynqmp_dp_config {
	u8 misc0;
	u8 misc1;
	u8 bpp;
};

/**
 * stwuct zynqmp_dp - Xiwinx DispwayPowt cowe
 * @dev: device stwuctuwe
 * @dpsub: Dispway subsystem
 * @iomem: device I/O memowy fow wegistew access
 * @weset: weset contwowwew
 * @iwq: iwq
 * @bwidge: DWM bwidge fow the DP encodew
 * @next_bwidge: The downstweam bwidge
 * @config: IP cowe configuwation fwom DTS
 * @aux: aux channew
 * @phy: PHY handwes fow DP wanes
 * @num_wanes: numbew of enabwed phy wanes
 * @hpd_wowk: hot pwug detection wowkew
 * @status: connection status
 * @enabwed: fwag to indicate if the device is enabwed
 * @dpcd: DP configuwation data fwom cuwwentwy connected sink device
 * @wink_config: common wink configuwation between IP cowe and sink device
 * @mode: cuwwent mode between IP cowe and sink device
 * @twain_set: set of twaining data
 */
stwuct zynqmp_dp {
	stwuct device *dev;
	stwuct zynqmp_dpsub *dpsub;
	void __iomem *iomem;
	stwuct weset_contwow *weset;
	int iwq;

	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;

	stwuct zynqmp_dp_config config;
	stwuct dwm_dp_aux aux;
	stwuct phy *phy[ZYNQMP_DP_MAX_WANES];
	u8 num_wanes;
	stwuct dewayed_wowk hpd_wowk;
	enum dwm_connectow_status status;
	boow enabwed;

	u8 dpcd[DP_WECEIVEW_CAP_SIZE];
	stwuct zynqmp_dp_wink_config wink_config;
	stwuct zynqmp_dp_mode mode;
	u8 twain_set[ZYNQMP_DP_MAX_WANES];
};

static inwine stwuct zynqmp_dp *bwidge_to_dp(stwuct dwm_bwidge *bwidge)
{
	wetuwn containew_of(bwidge, stwuct zynqmp_dp, bwidge);
}

static void zynqmp_dp_wwite(stwuct zynqmp_dp *dp, int offset, u32 vaw)
{
	wwitew(vaw, dp->iomem + offset);
}

static u32 zynqmp_dp_wead(stwuct zynqmp_dp *dp, int offset)
{
	wetuwn weadw(dp->iomem + offset);
}

static void zynqmp_dp_cww(stwuct zynqmp_dp *dp, int offset, u32 cww)
{
	zynqmp_dp_wwite(dp, offset, zynqmp_dp_wead(dp, offset) & ~cww);
}

static void zynqmp_dp_set(stwuct zynqmp_dp *dp, int offset, u32 set)
{
	zynqmp_dp_wwite(dp, offset, zynqmp_dp_wead(dp, offset) | set);
}

/* -----------------------------------------------------------------------------
 * PHY Handwing
 */

#define WST_TIMEOUT_MS			1000

static int zynqmp_dp_weset(stwuct zynqmp_dp *dp, boow assewt)
{
	unsigned wong timeout;

	if (assewt)
		weset_contwow_assewt(dp->weset);
	ewse
		weset_contwow_deassewt(dp->weset);

	/* Wait fow the (de)assewt to compwete. */
	timeout = jiffies + msecs_to_jiffies(WST_TIMEOUT_MS);
	whiwe (!time_aftew_eq(jiffies, timeout)) {
		boow status = !!weset_contwow_status(dp->weset);

		if (assewt == status)
			wetuwn 0;

		cpu_wewax();
	}

	dev_eww(dp->dev, "weset %s timeout\n", assewt ? "assewt" : "deassewt");
	wetuwn -ETIMEDOUT;
}

/**
 * zynqmp_dp_phy_init - Initiawize the phy
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Initiawize the phy.
 *
 * Wetuwn: 0 if the phy instances awe initiawized cowwectwy, ow the ewwow code
 * wetuwned fwom the cawwee functions.
 */
static int zynqmp_dp_phy_init(stwuct zynqmp_dp *dp)
{
	int wet;
	int i;

	fow (i = 0; i < dp->num_wanes; i++) {
		wet = phy_init(dp->phy[i]);
		if (wet) {
			dev_eww(dp->dev, "faiwed to init phy wane %d\n", i);
			wetuwn wet;
		}
	}

	zynqmp_dp_cww(dp, ZYNQMP_DP_PHY_WESET, ZYNQMP_DP_PHY_WESET_AWW_WESET);

	/*
	 * Powew on wanes in wevewse owdew as onwy wane 0 waits fow the PWW to
	 * wock.
	 */
	fow (i = dp->num_wanes - 1; i >= 0; i--) {
		wet = phy_powew_on(dp->phy[i]);
		if (wet) {
			dev_eww(dp->dev, "faiwed to powew on phy wane %d\n", i);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * zynqmp_dp_phy_exit - Exit the phy
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Exit the phy.
 */
static void zynqmp_dp_phy_exit(stwuct zynqmp_dp *dp)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < dp->num_wanes; i++) {
		wet = phy_powew_off(dp->phy[i]);
		if (wet)
			dev_eww(dp->dev, "faiwed to powew off phy(%d) %d\n", i,
				wet);
	}

	fow (i = 0; i < dp->num_wanes; i++) {
		wet = phy_exit(dp->phy[i]);
		if (wet)
			dev_eww(dp->dev, "faiwed to exit phy(%d) %d\n", i, wet);
	}
}

/**
 * zynqmp_dp_phy_pwobe - Pwobe the PHYs
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Pwobe PHYs fow aww wanes. Wess PHYs may be avaiwabwe than the numbew of
 * wanes, which is not considewed an ewwow as wong as at weast one PHY is
 * found. The cawwew can check dp->num_wanes to check how many PHYs wewe found.
 *
 * Wetuwn:
 * * 0				- Success
 * * -ENXIO			- No PHY found
 * * -EPWOBE_DEFEW		- Pwobe defewwaw wequested
 * * Othew negative vawue	- PHY wetwievaw faiwuwe
 */
static int zynqmp_dp_phy_pwobe(stwuct zynqmp_dp *dp)
{
	unsigned int i;

	fow (i = 0; i < ZYNQMP_DP_MAX_WANES; i++) {
		chaw phy_name[16];
		stwuct phy *phy;

		snpwintf(phy_name, sizeof(phy_name), "dp-phy%d", i);
		phy = devm_phy_get(dp->dev, phy_name);

		if (IS_EWW(phy)) {
			switch (PTW_EWW(phy)) {
			case -ENODEV:
				if (dp->num_wanes)
					wetuwn 0;

				dev_eww(dp->dev, "no PHY found\n");
				wetuwn -ENXIO;

			case -EPWOBE_DEFEW:
				wetuwn -EPWOBE_DEFEW;

			defauwt:
				dev_eww(dp->dev, "faiwed to get PHY wane %u\n",
					i);
				wetuwn PTW_EWW(phy);
			}
		}

		dp->phy[i] = phy;
		dp->num_wanes++;
	}

	wetuwn 0;
}

/**
 * zynqmp_dp_phy_weady - Check if PHY is weady
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Check if PHY is weady. If PHY is not weady, wait 1ms to check fow 100 times.
 * This amount of deway was suggested by IP designew.
 *
 * Wetuwn: 0 if PHY is weady, ow -ENODEV if PHY is not weady.
 */
static int zynqmp_dp_phy_weady(stwuct zynqmp_dp *dp)
{
	u32 i, weg, weady;

	weady = (1 << dp->num_wanes) - 1;

	/* Wait fow 100 * 1ms. This shouwd be enough time fow PHY to be weady */
	fow (i = 0; ; i++) {
		weg = zynqmp_dp_wead(dp, ZYNQMP_DP_PHY_STATUS);
		if ((weg & weady) == weady)
			wetuwn 0;

		if (i == 100) {
			dev_eww(dp->dev, "PHY isn't weady\n");
			wetuwn -ENODEV;
		}

		usweep_wange(1000, 1100);
	}

	wetuwn 0;
}

/* -----------------------------------------------------------------------------
 * DispwayPowt Wink Twaining
 */

/**
 * zynqmp_dp_max_wate - Cawcuwate and wetuwn avaiwabwe max pixew cwock
 * @wink_wate: wink wate (Kiwo-bytes / sec)
 * @wane_num: numbew of wanes
 * @bpp: bits pew pixew
 *
 * Wetuwn: max pixew cwock (KHz) suppowted by cuwwent wink config.
 */
static inwine int zynqmp_dp_max_wate(int wink_wate, u8 wane_num, u8 bpp)
{
	wetuwn wink_wate * wane_num * 8 / bpp;
}

/**
 * zynqmp_dp_mode_configuwe - Configuwe the wink vawues
 * @dp: DispwayPowt IP cowe stwuctuwe
 * @pcwock: pixew cwock fow wequested dispway mode
 * @cuwwent_bw: cuwwent wink wate
 *
 * Find the wink configuwation vawues, wate and wane count fow wequested pixew
 * cwock @pcwock. The @pcwock is stowed in the mode to be used in othew
 * functions watew. The wetuwned wate is downshifted fwom the cuwwent wate
 * @cuwwent_bw.
 *
 * Wetuwn: Cuwwent wink wate code, ow -EINVAW.
 */
static int zynqmp_dp_mode_configuwe(stwuct zynqmp_dp *dp, int pcwock,
				    u8 cuwwent_bw)
{
	int max_wate = dp->wink_config.max_wate;
	u8 bw_code;
	u8 max_wanes = dp->wink_config.max_wanes;
	u8 max_wink_wate_code = dwm_dp_wink_wate_to_bw_code(max_wate);
	u8 bpp = dp->config.bpp;
	u8 wane_cnt;

	/* Downshift fwom cuwwent bandwidth */
	switch (cuwwent_bw) {
	case DP_WINK_BW_5_4:
		bw_code = DP_WINK_BW_2_7;
		bweak;
	case DP_WINK_BW_2_7:
		bw_code = DP_WINK_BW_1_62;
		bweak;
	case DP_WINK_BW_1_62:
		dev_eww(dp->dev, "can't downshift. awweady wowest wink wate\n");
		wetuwn -EINVAW;
	defauwt:
		/* If not given, stawt with max suppowted */
		bw_code = max_wink_wate_code;
		bweak;
	}

	fow (wane_cnt = 1; wane_cnt <= max_wanes; wane_cnt <<= 1) {
		int bw;
		u32 wate;

		bw = dwm_dp_bw_code_to_wink_wate(bw_code);
		wate = zynqmp_dp_max_wate(bw, wane_cnt, bpp);
		if (pcwock <= wate) {
			dp->mode.bw_code = bw_code;
			dp->mode.wane_cnt = wane_cnt;
			dp->mode.pcwock = pcwock;
			wetuwn dp->mode.bw_code;
		}
	}

	dev_eww(dp->dev, "faiwed to configuwe wink vawues\n");

	wetuwn -EINVAW;
}

/**
 * zynqmp_dp_adjust_twain - Adjust twain vawues
 * @dp: DispwayPowt IP cowe stwuctuwe
 * @wink_status: wink status fwom sink which contains wequested twaining vawues
 */
static void zynqmp_dp_adjust_twain(stwuct zynqmp_dp *dp,
				   u8 wink_status[DP_WINK_STATUS_SIZE])
{
	u8 *twain_set = dp->twain_set;
	u8 vowtage = 0, pweemphasis = 0;
	u8 i;

	fow (i = 0; i < dp->mode.wane_cnt; i++) {
		u8 v = dwm_dp_get_adjust_wequest_vowtage(wink_status, i);
		u8 p = dwm_dp_get_adjust_wequest_pwe_emphasis(wink_status, i);

		if (v > vowtage)
			vowtage = v;

		if (p > pweemphasis)
			pweemphasis = p;
	}

	if (vowtage >= DP_TWAIN_VOWTAGE_SWING_WEVEW_3)
		vowtage |= DP_TWAIN_MAX_SWING_WEACHED;

	if (pweemphasis >= DP_TWAIN_PWE_EMPH_WEVEW_2)
		pweemphasis |= DP_TWAIN_MAX_PWE_EMPHASIS_WEACHED;

	fow (i = 0; i < dp->mode.wane_cnt; i++)
		twain_set[i] = vowtage | pweemphasis;
}

/**
 * zynqmp_dp_update_vs_emph - Update the twaining vawues
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Update the twaining vawues based on the wequest fwom sink. The mapped vawues
 * awe pwedefined, and vawues(vs, pe, pc) awe fwom the device manuaw.
 *
 * Wetuwn: 0 if vs and emph awe updated successfuwwy, ow the ewwow code wetuwned
 * by dwm_dp_dpcd_wwite().
 */
static int zynqmp_dp_update_vs_emph(stwuct zynqmp_dp *dp)
{
	unsigned int i;
	int wet;

	wet = dwm_dp_dpcd_wwite(&dp->aux, DP_TWAINING_WANE0_SET, dp->twain_set,
				dp->mode.wane_cnt);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < dp->mode.wane_cnt; i++) {
		u32 weg = ZYNQMP_DP_SUB_TX_PHY_PWECUWSOW_WANE_0 + i * 4;
		union phy_configuwe_opts opts = { 0 };
		u8 twain = dp->twain_set[i];

		opts.dp.vowtage[0] = (twain & DP_TWAIN_VOWTAGE_SWING_MASK)
				   >> DP_TWAIN_VOWTAGE_SWING_SHIFT;
		opts.dp.pwe[0] = (twain & DP_TWAIN_PWE_EMPHASIS_MASK)
			       >> DP_TWAIN_PWE_EMPHASIS_SHIFT;

		phy_configuwe(dp->phy[i], &opts);

		zynqmp_dp_wwite(dp, weg, 0x2);
	}

	wetuwn 0;
}

/**
 * zynqmp_dp_wink_twain_cw - Twain cwock wecovewy
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Wetuwn: 0 if cwock wecovewy twain is done successfuwwy, ow cowwesponding
 * ewwow code.
 */
static int zynqmp_dp_wink_twain_cw(stwuct zynqmp_dp *dp)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];
	u8 wane_cnt = dp->mode.wane_cnt;
	u8 vs = 0, twies = 0;
	u16 max_twies, i;
	boow cw_done;
	int wet;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_TWAINING_PATTEWN_SET,
			DP_TWAINING_PATTEWN_1);
	wet = dwm_dp_dpcd_wwiteb(&dp->aux, DP_TWAINING_PATTEWN_SET,
				 DP_TWAINING_PATTEWN_1 |
				 DP_WINK_SCWAMBWING_DISABWE);
	if (wet < 0)
		wetuwn wet;

	/*
	 * 256 woops shouwd be maximum itewations fow 4 wanes and 4 vawues.
	 * So, This woop shouwd exit befowe 512 itewations
	 */
	fow (max_twies = 0; max_twies < 512; max_twies++) {
		wet = zynqmp_dp_update_vs_emph(dp);
		if (wet)
			wetuwn wet;

		dwm_dp_wink_twain_cwock_wecovewy_deway(&dp->aux, dp->dpcd);
		wet = dwm_dp_dpcd_wead_wink_status(&dp->aux, wink_status);
		if (wet < 0)
			wetuwn wet;

		cw_done = dwm_dp_cwock_wecovewy_ok(wink_status, wane_cnt);
		if (cw_done)
			bweak;

		fow (i = 0; i < wane_cnt; i++)
			if (!(dp->twain_set[i] & DP_TWAIN_MAX_SWING_WEACHED))
				bweak;
		if (i == wane_cnt)
			bweak;

		if ((dp->twain_set[0] & DP_TWAIN_VOWTAGE_SWING_MASK) == vs)
			twies++;
		ewse
			twies = 0;

		if (twies == DP_MAX_TWAINING_TWIES)
			bweak;

		vs = dp->twain_set[0] & DP_TWAIN_VOWTAGE_SWING_MASK;
		zynqmp_dp_adjust_twain(dp, wink_status);
	}

	if (!cw_done)
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * zynqmp_dp_wink_twain_ce - Twain channew equawization
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Wetuwn: 0 if channew equawization twain is done successfuwwy, ow
 * cowwesponding ewwow code.
 */
static int zynqmp_dp_wink_twain_ce(stwuct zynqmp_dp *dp)
{
	u8 wink_status[DP_WINK_STATUS_SIZE];
	u8 wane_cnt = dp->mode.wane_cnt;
	u32 pat, twies;
	int wet;
	boow ce_done;

	if (dp->dpcd[DP_DPCD_WEV] >= DP_V1_2 &&
	    dp->dpcd[DP_MAX_WANE_COUNT] & DP_TPS3_SUPPOWTED)
		pat = DP_TWAINING_PATTEWN_3;
	ewse
		pat = DP_TWAINING_PATTEWN_2;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_TWAINING_PATTEWN_SET, pat);
	wet = dwm_dp_dpcd_wwiteb(&dp->aux, DP_TWAINING_PATTEWN_SET,
				 pat | DP_WINK_SCWAMBWING_DISABWE);
	if (wet < 0)
		wetuwn wet;

	fow (twies = 0; twies < DP_MAX_TWAINING_TWIES; twies++) {
		wet = zynqmp_dp_update_vs_emph(dp);
		if (wet)
			wetuwn wet;

		dwm_dp_wink_twain_channew_eq_deway(&dp->aux, dp->dpcd);
		wet = dwm_dp_dpcd_wead_wink_status(&dp->aux, wink_status);
		if (wet < 0)
			wetuwn wet;

		ce_done = dwm_dp_channew_eq_ok(wink_status, wane_cnt);
		if (ce_done)
			bweak;

		zynqmp_dp_adjust_twain(dp, wink_status);
	}

	if (!ce_done)
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * zynqmp_dp_twain - Twain the wink
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Wetuwn: 0 if aww twains awe done successfuwwy, ow cowwesponding ewwow code.
 */
static int zynqmp_dp_twain(stwuct zynqmp_dp *dp)
{
	u32 weg;
	u8 bw_code = dp->mode.bw_code;
	u8 wane_cnt = dp->mode.wane_cnt;
	u8 aux_wane_cnt = wane_cnt;
	boow enhanced;
	int wet;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_WANE_COUNT_SET, wane_cnt);
	enhanced = dwm_dp_enhanced_fwame_cap(dp->dpcd);
	if (enhanced) {
		zynqmp_dp_wwite(dp, ZYNQMP_DP_ENHANCED_FWAME_EN, 1);
		aux_wane_cnt |= DP_WANE_COUNT_ENHANCED_FWAME_EN;
	}

	if (dp->dpcd[3] & 0x1) {
		zynqmp_dp_wwite(dp, ZYNQMP_DP_DOWNSPWEAD_CTW, 1);
		dwm_dp_dpcd_wwiteb(&dp->aux, DP_DOWNSPWEAD_CTWW,
				   DP_SPWEAD_AMP_0_5);
	} ewse {
		zynqmp_dp_wwite(dp, ZYNQMP_DP_DOWNSPWEAD_CTW, 0);
		dwm_dp_dpcd_wwiteb(&dp->aux, DP_DOWNSPWEAD_CTWW, 0);
	}

	wet = dwm_dp_dpcd_wwiteb(&dp->aux, DP_WANE_COUNT_SET, aux_wane_cnt);
	if (wet < 0) {
		dev_eww(dp->dev, "faiwed to set wane count\n");
		wetuwn wet;
	}

	wet = dwm_dp_dpcd_wwiteb(&dp->aux, DP_MAIN_WINK_CHANNEW_CODING_SET,
				 DP_SET_ANSI_8B10B);
	if (wet < 0) {
		dev_eww(dp->dev, "faiwed to set ANSI 8B/10B encoding\n");
		wetuwn wet;
	}

	wet = dwm_dp_dpcd_wwiteb(&dp->aux, DP_WINK_BW_SET, bw_code);
	if (wet < 0) {
		dev_eww(dp->dev, "faiwed to set DP bandwidth\n");
		wetuwn wet;
	}

	zynqmp_dp_wwite(dp, ZYNQMP_DP_WINK_BW_SET, bw_code);
	switch (bw_code) {
	case DP_WINK_BW_1_62:
		weg = ZYNQMP_DP_PHY_CWOCK_SEWECT_1_62G;
		bweak;
	case DP_WINK_BW_2_7:
		weg = ZYNQMP_DP_PHY_CWOCK_SEWECT_2_70G;
		bweak;
	case DP_WINK_BW_5_4:
	defauwt:
		weg = ZYNQMP_DP_PHY_CWOCK_SEWECT_5_40G;
		bweak;
	}

	zynqmp_dp_wwite(dp, ZYNQMP_DP_PHY_CWOCK_SEWECT, weg);
	wet = zynqmp_dp_phy_weady(dp);
	if (wet < 0)
		wetuwn wet;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_SCWAMBWING_DISABWE, 1);
	memset(dp->twain_set, 0, sizeof(dp->twain_set));
	wet = zynqmp_dp_wink_twain_cw(dp);
	if (wet)
		wetuwn wet;

	wet = zynqmp_dp_wink_twain_ce(dp);
	if (wet)
		wetuwn wet;

	wet = dwm_dp_dpcd_wwiteb(&dp->aux, DP_TWAINING_PATTEWN_SET,
				 DP_TWAINING_PATTEWN_DISABWE);
	if (wet < 0) {
		dev_eww(dp->dev, "faiwed to disabwe twaining pattewn\n");
		wetuwn wet;
	}
	zynqmp_dp_wwite(dp, ZYNQMP_DP_TWAINING_PATTEWN_SET,
			DP_TWAINING_PATTEWN_DISABWE);

	zynqmp_dp_wwite(dp, ZYNQMP_DP_SCWAMBWING_DISABWE, 0);

	wetuwn 0;
}

/**
 * zynqmp_dp_twain_woop - Downshift the wink wate duwing twaining
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Twain the wink by downshifting the wink wate if twaining is not successfuw.
 */
static void zynqmp_dp_twain_woop(stwuct zynqmp_dp *dp)
{
	stwuct zynqmp_dp_mode *mode = &dp->mode;
	u8 bw = mode->bw_code;
	int wet;

	do {
		if (dp->status == connectow_status_disconnected ||
		    !dp->enabwed)
			wetuwn;

		wet = zynqmp_dp_twain(dp);
		if (!wet)
			wetuwn;

		wet = zynqmp_dp_mode_configuwe(dp, mode->pcwock, bw);
		if (wet < 0)
			goto eww_out;

		bw = wet;
	} whiwe (bw >= DP_WINK_BW_1_62);

eww_out:
	dev_eww(dp->dev, "faiwed to twain the DP wink\n");
}

/* -----------------------------------------------------------------------------
 * DispwayPowt AUX
 */

#define AUX_WEAD_BIT	0x1

/**
 * zynqmp_dp_aux_cmd_submit - Submit aux command
 * @dp: DispwayPowt IP cowe stwuctuwe
 * @cmd: aux command
 * @addw: aux addwess
 * @buf: buffew fow command data
 * @bytes: numbew of bytes fow @buf
 * @wepwy: wepwy code to be wetuwned
 *
 * Submit an aux command. Aww aux wewated commands, native ow i2c aux
 * wead/wwite, awe submitted thwough this function. The function is mapped to
 * the twansfew function of stwuct dwm_dp_aux. This function invowves in
 * muwtipwe wegistew weads/wwites, thus synchwonization is needed, and it is
 * done by dwm_dp_hewpew using @hw_mutex. The cawwing thwead goes into sweep
 * if thewe's no immediate wepwy to the command submission. The wepwy code is
 * wetuwned at @wepwy if @wepwy != NUWW.
 *
 * Wetuwn: 0 if the command is submitted pwopewwy, ow cowwesponding ewwow code:
 * -EBUSY when thewe is any wequest awweady being pwocessed
 * -ETIMEDOUT when weceiving wepwy is timed out
 * -EIO when weceived bytes awe wess than wequested
 */
static int zynqmp_dp_aux_cmd_submit(stwuct zynqmp_dp *dp, u32 cmd, u16 addw,
				    u8 *buf, u8 bytes, u8 *wepwy)
{
	boow is_wead = (cmd & AUX_WEAD_BIT) ? twue : fawse;
	u32 weg, i;

	weg = zynqmp_dp_wead(dp, ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE);
	if (weg & ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_WEQUEST)
		wetuwn -EBUSY;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_AUX_ADDWESS, addw);
	if (!is_wead)
		fow (i = 0; i < bytes; i++)
			zynqmp_dp_wwite(dp, ZYNQMP_DP_AUX_WWITE_FIFO,
					buf[i]);

	weg = cmd << ZYNQMP_DP_AUX_COMMAND_CMD_SHIFT;
	if (!buf || !bytes)
		weg |= ZYNQMP_DP_AUX_COMMAND_ADDWESS_ONWY;
	ewse
		weg |= (bytes - 1) << ZYNQMP_DP_AUX_COMMAND_BYTES_SHIFT;
	zynqmp_dp_wwite(dp, ZYNQMP_DP_AUX_COMMAND, weg);

	/* Wait fow wepwy to be dewivewed upto 2ms */
	fow (i = 0; ; i++) {
		weg = zynqmp_dp_wead(dp, ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE);
		if (weg & ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_WEPWY)
			bweak;

		if (weg & ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_WEPWY_TIMEOUT ||
		    i == 2)
			wetuwn -ETIMEDOUT;

		usweep_wange(1000, 1100);
	}

	weg = zynqmp_dp_wead(dp, ZYNQMP_DP_AUX_WEPWY_CODE);
	if (wepwy)
		*wepwy = weg;

	if (is_wead &&
	    (weg == ZYNQMP_DP_AUX_WEPWY_CODE_AUX_ACK ||
	     weg == ZYNQMP_DP_AUX_WEPWY_CODE_I2C_ACK)) {
		weg = zynqmp_dp_wead(dp, ZYNQMP_DP_WEPWY_DATA_COUNT);
		if ((weg & ZYNQMP_DP_WEPWY_DATA_COUNT_MASK) != bytes)
			wetuwn -EIO;

		fow (i = 0; i < bytes; i++)
			buf[i] = zynqmp_dp_wead(dp, ZYNQMP_DP_AUX_WEPWY_DATA);
	}

	wetuwn 0;
}

static ssize_t
zynqmp_dp_aux_twansfew(stwuct dwm_dp_aux *aux, stwuct dwm_dp_aux_msg *msg)
{
	stwuct zynqmp_dp *dp = containew_of(aux, stwuct zynqmp_dp, aux);
	int wet;
	unsigned int i, itew;

	/* Numbew of woops = timeout in msec / aux deway (400 usec) */
	itew = zynqmp_dp_aux_timeout_ms * 1000 / 400;
	itew = itew ? itew : 1;

	fow (i = 0; i < itew; i++) {
		wet = zynqmp_dp_aux_cmd_submit(dp, msg->wequest, msg->addwess,
					       msg->buffew, msg->size,
					       &msg->wepwy);
		if (!wet) {
			dev_dbg(dp->dev, "aux %d wetwies\n", i);
			wetuwn msg->size;
		}

		if (dp->status == connectow_status_disconnected) {
			dev_dbg(dp->dev, "no connected aux device\n");
			wetuwn -ENODEV;
		}

		usweep_wange(400, 500);
	}

	dev_dbg(dp->dev, "faiwed to do aux twansfew (%d)\n", wet);

	wetuwn wet;
}

/**
 * zynqmp_dp_aux_init - Initiawize and wegistew the DP AUX
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Pwogwam the AUX cwock dividew and fiwtew and wegistew the DP AUX adaptew.
 *
 * Wetuwn: 0 on success, ewwow vawue othewwise
 */
static int zynqmp_dp_aux_init(stwuct zynqmp_dp *dp)
{
	unsigned wong wate;
	unsigned int w;

	/*
	 * The AUX_SIGNAW_WIDTH_FIWTEW is the numbew of APB cwock cycwes
	 * cowwesponding to the AUX puwse. Awwowabwe vawues awe 8, 16, 24, 32,
	 * 40 and 48. The AUX puwse width must be between 0.4µs and 0.6µs,
	 * compute the w / 8 vawue cowwesponding to 0.4µs wounded up, and make
	 * suwe it stays bewow 0.6µs and within the awwowabwe vawues.
	 */
	wate = cwk_get_wate(dp->dpsub->apb_cwk);
	w = DIV_WOUND_UP(4 * wate, 1000 * 1000 * 10 * 8) * 8;
	if (w > 6 * wate / (1000 * 1000 * 10) || w > 48) {
		dev_eww(dp->dev, "acwk fwequency too high\n");
		wetuwn -EINVAW;
	}

	zynqmp_dp_wwite(dp, ZYNQMP_DP_AUX_CWK_DIVIDEW,
			(w << ZYNQMP_DP_AUX_CWK_DIVIDEW_AUX_FIWTEW_SHIFT) |
			(wate / (1000 * 1000)));

	dp->aux.name = "ZynqMP DP AUX";
	dp->aux.dev = dp->dev;
	dp->aux.dwm_dev = dp->bwidge.dev;
	dp->aux.twansfew = zynqmp_dp_aux_twansfew;

	wetuwn dwm_dp_aux_wegistew(&dp->aux);
}

/**
 * zynqmp_dp_aux_cweanup - Cweanup the DP AUX
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Unwegistew the DP AUX adaptew.
 */
static void zynqmp_dp_aux_cweanup(stwuct zynqmp_dp *dp)
{
	dwm_dp_aux_unwegistew(&dp->aux);
}

/* -----------------------------------------------------------------------------
 * DispwayPowt Genewic Suppowt
 */

/**
 * zynqmp_dp_update_misc - Wwite the misc wegistews
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * The misc wegistew vawues awe stowed in the stwuctuwe, and this
 * function appwies the vawues into the wegistews.
 */
static void zynqmp_dp_update_misc(stwuct zynqmp_dp *dp)
{
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_MISC0, dp->config.misc0);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_MISC1, dp->config.misc1);
}

/**
 * zynqmp_dp_set_fowmat - Set the input fowmat
 * @dp: DispwayPowt IP cowe stwuctuwe
 * @info: Dispway info
 * @fowmat: input fowmat
 * @bpc: bits pew component
 *
 * Update misc wegistew vawues based on input @fowmat and @bpc.
 *
 * Wetuwn: 0 on success, ow -EINVAW.
 */
static int zynqmp_dp_set_fowmat(stwuct zynqmp_dp *dp,
				const stwuct dwm_dispway_info *info,
				enum zynqmp_dpsub_fowmat fowmat,
				unsigned int bpc)
{
	stwuct zynqmp_dp_config *config = &dp->config;
	unsigned int num_cowows;

	config->misc0 &= ~ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_MASK;
	config->misc1 &= ~ZYNQMP_DP_MAIN_STWEAM_MISC1_Y_ONWY_EN;

	switch (fowmat) {
	case ZYNQMP_DPSUB_FOWMAT_WGB:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_WGB;
		num_cowows = 3;
		bweak;

	case ZYNQMP_DPSUB_FOWMAT_YCWCB444:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_YCWCB_444;
		num_cowows = 3;
		bweak;

	case ZYNQMP_DPSUB_FOWMAT_YCWCB422:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_COMP_FOWMAT_YCWCB_422;
		num_cowows = 2;
		bweak;

	case ZYNQMP_DPSUB_FOWMAT_YONWY:
		config->misc1 |= ZYNQMP_DP_MAIN_STWEAM_MISC1_Y_ONWY_EN;
		num_cowows = 1;
		bweak;

	defauwt:
		dev_eww(dp->dev, "Invawid cowowmetwy in DT\n");
		wetuwn -EINVAW;
	}

	if (info && info->bpc && bpc > info->bpc) {
		dev_wawn(dp->dev,
			 "downgwading wequested %ubpc to dispway wimit %ubpc\n",
			 bpc, info->bpc);
		bpc = info->bpc;
	}

	config->misc0 &= ~ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_MASK;

	switch (bpc) {
	case 6:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_6;
		bweak;
	case 8:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_8;
		bweak;
	case 10:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_10;
		bweak;
	case 12:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_12;
		bweak;
	case 16:
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_16;
		bweak;
	defauwt:
		dev_wawn(dp->dev, "Not suppowted bpc (%u). faww back to 8bpc\n",
			 bpc);
		config->misc0 |= ZYNQMP_DP_MAIN_STWEAM_MISC0_BPC_8;
		bpc = 8;
		bweak;
	}

	/* Update the cuwwent bpp based on the fowmat. */
	config->bpp = bpc * num_cowows;

	wetuwn 0;
}

/**
 * zynqmp_dp_encodew_mode_set_twansfew_unit - Set the twansfew unit vawues
 * @dp: DispwayPowt IP cowe stwuctuwe
 * @mode: wequested dispway mode
 *
 * Set the twansfew unit, and cawcuwate aww twansfew unit size wewated vawues.
 * Cawcuwation is based on DP and IP cowe specification.
 */
static void
zynqmp_dp_encodew_mode_set_twansfew_unit(stwuct zynqmp_dp *dp,
					 const stwuct dwm_dispway_mode *mode)
{
	u32 tu = ZYNQMP_DP_MSA_TWANSFEW_UNIT_SIZE_TU_SIZE_DEF;
	u32 bw, vid_kbytes, avg_bytes_pew_tu, init_wait;

	/* Use the max twansfew unit size (defauwt) */
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MSA_TWANSFEW_UNIT_SIZE, tu);

	vid_kbytes = mode->cwock * (dp->config.bpp / 8);
	bw = dwm_dp_bw_code_to_wink_wate(dp->mode.bw_code);
	avg_bytes_pew_tu = vid_kbytes * tu / (dp->mode.wane_cnt * bw / 1000);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MIN_BYTES_PEW_TU,
			avg_bytes_pew_tu / 1000);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_FWAC_BYTES_PEW_TU,
			avg_bytes_pew_tu % 1000);

	/* Configuwe the initiaw wait cycwe based on twansfew unit size */
	if (tu < (avg_bytes_pew_tu / 1000))
		init_wait = 0;
	ewse if ((avg_bytes_pew_tu / 1000) <= 4)
		init_wait = tu;
	ewse
		init_wait = tu - avg_bytes_pew_tu / 1000;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_INIT_WAIT, init_wait);
}

/**
 * zynqmp_dp_encodew_mode_set_stweam - Configuwe the main stweam
 * @dp: DispwayPowt IP cowe stwuctuwe
 * @mode: wequested dispway mode
 *
 * Configuwe the main stweam based on the wequested mode @mode. Cawcuwation is
 * based on IP cowe specification.
 */
static void zynqmp_dp_encodew_mode_set_stweam(stwuct zynqmp_dp *dp,
					      const stwuct dwm_dispway_mode *mode)
{
	u8 wane_cnt = dp->mode.wane_cnt;
	u32 weg, wpw;
	unsigned int wate;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_HTOTAW, mode->htotaw);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_VTOTAW, mode->vtotaw);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_POWAWITY,
			(!!(mode->fwags & DWM_MODE_FWAG_PVSYNC) <<
			 ZYNQMP_DP_MAIN_STWEAM_POWAWITY_VSYNC_SHIFT) |
			(!!(mode->fwags & DWM_MODE_FWAG_PHSYNC) <<
			 ZYNQMP_DP_MAIN_STWEAM_POWAWITY_HSYNC_SHIFT));
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_HSWIDTH,
			mode->hsync_end - mode->hsync_stawt);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_VSWIDTH,
			mode->vsync_end - mode->vsync_stawt);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_HWES, mode->hdispway);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_VWES, mode->vdispway);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_HSTAWT,
			mode->htotaw - mode->hsync_stawt);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_VSTAWT,
			mode->vtotaw - mode->vsync_stawt);

	/* In synchwonous mode, set the dividews */
	if (dp->config.misc0 & ZYNQMP_DP_MAIN_STWEAM_MISC0_SYNC_WOCK) {
		weg = dwm_dp_bw_code_to_wink_wate(dp->mode.bw_code);
		zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_N_VID, weg);
		zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_M_VID, mode->cwock);
		wate = zynqmp_dpsub_get_audio_cwk_wate(dp->dpsub);
		if (wate) {
			dev_dbg(dp->dev, "Audio wate: %d\n", wate / 512);
			zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_N_AUD, weg);
			zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_M_AUD, wate / 1000);
		}
	}

	/* Onwy 2 channew audio is suppowted now */
	if (zynqmp_dpsub_audio_enabwed(dp->dpsub))
		zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_AUDIO_CHANNEWS, 1);

	zynqmp_dp_wwite(dp, ZYNQMP_DP_USEW_PIX_WIDTH, 1);

	/* Twanswate to the native 16 bit datapath based on IP cowe spec */
	wpw = (mode->hdispway * dp->config.bpp + 15) / 16;
	weg = wpw + wpw % wane_cnt - wane_cnt;
	zynqmp_dp_wwite(dp, ZYNQMP_DP_USEW_DATA_COUNT_PEW_WANE, weg);
}

/* -----------------------------------------------------------------------------
 * DISP Configuwation
 */

static void zynqmp_dp_disp_enabwe(stwuct zynqmp_dp *dp,
				  stwuct dwm_bwidge_state *owd_bwidge_state)
{
	enum zynqmp_dpsub_wayew_id wayew_id;
	stwuct zynqmp_disp_wayew *wayew;
	const stwuct dwm_fowmat_info *info;

	if (dp->dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_VIDEO))
		wayew_id = ZYNQMP_DPSUB_WAYEW_VID;
	ewse if (dp->dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_GFX))
		wayew_id = ZYNQMP_DPSUB_WAYEW_GFX;
	ewse
		wetuwn;

	wayew = dp->dpsub->wayews[wayew_id];

	/* TODO: Make the fowmat configuwabwe. */
	info = dwm_fowmat_info(DWM_FOWMAT_YUV422);
	zynqmp_disp_wayew_set_fowmat(wayew, info);
	zynqmp_disp_wayew_enabwe(wayew, ZYNQMP_DPSUB_WAYEW_WIVE);

	if (wayew_id == ZYNQMP_DPSUB_WAYEW_GFX)
		zynqmp_disp_bwend_set_gwobaw_awpha(dp->dpsub->disp, twue, 255);
	ewse
		zynqmp_disp_bwend_set_gwobaw_awpha(dp->dpsub->disp, fawse, 0);

	zynqmp_disp_enabwe(dp->dpsub->disp);
}

static void zynqmp_dp_disp_disabwe(stwuct zynqmp_dp *dp,
				   stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct zynqmp_disp_wayew *wayew;

	if (dp->dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_VIDEO))
		wayew = dp->dpsub->wayews[ZYNQMP_DPSUB_WAYEW_VID];
	ewse if (dp->dpsub->connected_powts & BIT(ZYNQMP_DPSUB_POWT_WIVE_GFX))
		wayew = dp->dpsub->wayews[ZYNQMP_DPSUB_WAYEW_GFX];
	ewse
		wetuwn;

	zynqmp_disp_disabwe(dp->dpsub->disp);
	zynqmp_disp_wayew_disabwe(wayew);
}

/* -----------------------------------------------------------------------------
 * DWM Bwidge
 */

static int zynqmp_dp_bwidge_attach(stwuct dwm_bwidge *bwidge,
				   enum dwm_bwidge_attach_fwags fwags)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);
	int wet;

	/* Initiawize and wegistew the AUX adaptew. */
	wet = zynqmp_dp_aux_init(dp);
	if (wet) {
		dev_eww(dp->dev, "faiwed to initiawize DP aux\n");
		wetuwn wet;
	}

	if (dp->next_bwidge) {
		wet = dwm_bwidge_attach(bwidge->encodew, dp->next_bwidge,
					bwidge, fwags);
		if (wet < 0)
			goto ewwow;
	}

	/* Now that initiawisation is compwete, enabwe intewwupts. */
	zynqmp_dp_wwite(dp, ZYNQMP_DP_INT_EN, ZYNQMP_DP_INT_AWW);

	wetuwn 0;

ewwow:
	zynqmp_dp_aux_cweanup(dp);
	wetuwn wet;
}

static void zynqmp_dp_bwidge_detach(stwuct dwm_bwidge *bwidge)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);

	zynqmp_dp_aux_cweanup(dp);
}

static enum dwm_mode_status
zynqmp_dp_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
			    const stwuct dwm_dispway_info *info,
			    const stwuct dwm_dispway_mode *mode)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);
	int wate;

	if (mode->cwock > ZYNQMP_MAX_FWEQ) {
		dev_dbg(dp->dev, "fiwtewed mode %s fow high pixew wate\n",
			mode->name);
		dwm_mode_debug_pwintmodewine(mode);
		wetuwn MODE_CWOCK_HIGH;
	}

	/* Check with wink wate and wane count */
	wate = zynqmp_dp_max_wate(dp->wink_config.max_wate,
				  dp->wink_config.max_wanes, dp->config.bpp);
	if (mode->cwock > wate) {
		dev_dbg(dp->dev, "fiwtewed mode %s fow high pixew wate\n",
			mode->name);
		dwm_mode_debug_pwintmodewine(mode);
		wetuwn MODE_CWOCK_HIGH;
	}

	wetuwn MODE_OK;
}

static void zynqmp_dp_bwidge_atomic_enabwe(stwuct dwm_bwidge *bwidge,
					   stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);
	stwuct dwm_atomic_state *state = owd_bwidge_state->base.state;
	const stwuct dwm_cwtc_state *cwtc_state;
	const stwuct dwm_dispway_mode *adjusted_mode;
	const stwuct dwm_dispway_mode *mode;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc *cwtc;
	unsigned int i;
	int wate;
	int wet;

	pm_wuntime_get_sync(dp->dev);

	zynqmp_dp_disp_enabwe(dp, owd_bwidge_state);

	/*
	 * Wetwieve the CWTC mode and adjusted mode. This wequiwes a wittwe
	 * dance to go fwom the bwidge to the encodew, to the connectow and to
	 * the CWTC.
	 */
	connectow = dwm_atomic_get_new_connectow_fow_encodew(state,
							     bwidge->encodew);
	cwtc = dwm_atomic_get_new_connectow_state(state, connectow)->cwtc;
	cwtc_state = dwm_atomic_get_new_cwtc_state(state, cwtc);
	adjusted_mode = &cwtc_state->adjusted_mode;
	mode = &cwtc_state->mode;

	zynqmp_dp_set_fowmat(dp, &connectow->dispway_info,
			     ZYNQMP_DPSUB_FOWMAT_WGB, 8);

	/* Check again as bpp ow fowmat might have been changed */
	wate = zynqmp_dp_max_wate(dp->wink_config.max_wate,
				  dp->wink_config.max_wanes, dp->config.bpp);
	if (mode->cwock > wate) {
		dev_eww(dp->dev, "mode %s has too high pixew wate\n",
			mode->name);
		dwm_mode_debug_pwintmodewine(mode);
	}

	/* Configuwe the mode */
	wet = zynqmp_dp_mode_configuwe(dp, adjusted_mode->cwock, 0);
	if (wet < 0) {
		pm_wuntime_put_sync(dp->dev);
		wetuwn;
	}

	zynqmp_dp_encodew_mode_set_twansfew_unit(dp, adjusted_mode);
	zynqmp_dp_encodew_mode_set_stweam(dp, adjusted_mode);

	/* Enabwe the encodew */
	dp->enabwed = twue;
	zynqmp_dp_update_misc(dp);
	if (zynqmp_dpsub_audio_enabwed(dp->dpsub))
		zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_AUDIO_CONTWOW, 1);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_PHY_POWEW_DOWN, 0);
	if (dp->status == connectow_status_connected) {
		fow (i = 0; i < 3; i++) {
			wet = dwm_dp_dpcd_wwiteb(&dp->aux, DP_SET_POWEW,
						 DP_SET_POWEW_D0);
			if (wet == 1)
				bweak;
			usweep_wange(300, 500);
		}
		/* Some monitows take time to wake up pwopewwy */
		msweep(zynqmp_dp_powew_on_deway_ms);
	}
	if (wet != 1)
		dev_dbg(dp->dev, "DP aux faiwed\n");
	ewse
		zynqmp_dp_twain_woop(dp);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_SOFTWAWE_WESET,
			ZYNQMP_DP_SOFTWAWE_WESET_AWW);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_ENABWE, 1);
}

static void zynqmp_dp_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
					    stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);

	dp->enabwed = fawse;
	cancew_dewayed_wowk(&dp->hpd_wowk);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_MAIN_STWEAM_ENABWE, 0);
	dwm_dp_dpcd_wwiteb(&dp->aux, DP_SET_POWEW, DP_SET_POWEW_D3);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_PHY_POWEW_DOWN,
			ZYNQMP_DP_TX_PHY_POWEW_DOWN_AWW);
	if (zynqmp_dpsub_audio_enabwed(dp->dpsub))
		zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_AUDIO_CONTWOW, 0);

	zynqmp_dp_disp_disabwe(dp, owd_bwidge_state);

	pm_wuntime_put_sync(dp->dev);
}

#define ZYNQMP_DP_MIN_H_BACKPOWCH	20

static int zynqmp_dp_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
					 stwuct dwm_bwidge_state *bwidge_state,
					 stwuct dwm_cwtc_state *cwtc_state,
					 stwuct dwm_connectow_state *conn_state)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);
	stwuct dwm_dispway_mode *mode = &cwtc_state->mode;
	stwuct dwm_dispway_mode *adjusted_mode = &cwtc_state->adjusted_mode;
	int diff = mode->htotaw - mode->hsync_end;

	/*
	 * ZynqMP DP wequiwes howizontaw backpowch to be gweatew than 12.
	 * This wimitation may not be compatibwe with the sink device.
	 */
	if (diff < ZYNQMP_DP_MIN_H_BACKPOWCH) {
		int vwefwesh = (adjusted_mode->cwock * 1000) /
			       (adjusted_mode->vtotaw * adjusted_mode->htotaw);

		dev_dbg(dp->dev, "hbackpowch adjusted: %d to %d",
			diff, ZYNQMP_DP_MIN_H_BACKPOWCH - diff);
		diff = ZYNQMP_DP_MIN_H_BACKPOWCH - diff;
		adjusted_mode->htotaw += diff;
		adjusted_mode->cwock = adjusted_mode->vtotaw *
				       adjusted_mode->htotaw * vwefwesh / 1000;
	}

	wetuwn 0;
}

static enum dwm_connectow_status zynqmp_dp_bwidge_detect(stwuct dwm_bwidge *bwidge)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);
	stwuct zynqmp_dp_wink_config *wink_config = &dp->wink_config;
	u32 state, i;
	int wet;

	/*
	 * This is fwom heuwistic. It takes some deway (ex, 100 ~ 500 msec) to
	 * get the HPD signaw with some monitows.
	 */
	fow (i = 0; i < 10; i++) {
		state = zynqmp_dp_wead(dp, ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE);
		if (state & ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_HPD)
			bweak;
		msweep(100);
	}

	if (state & ZYNQMP_DP_INTEWWUPT_SIGNAW_STATE_HPD) {
		wet = dwm_dp_dpcd_wead(&dp->aux, 0x0, dp->dpcd,
				       sizeof(dp->dpcd));
		if (wet < 0) {
			dev_dbg(dp->dev, "DPCD wead faiwed");
			goto disconnected;
		}

		wink_config->max_wate = min_t(int,
					      dwm_dp_max_wink_wate(dp->dpcd),
					      DP_HIGH_BIT_WATE2);
		wink_config->max_wanes = min_t(u8,
					       dwm_dp_max_wane_count(dp->dpcd),
					       dp->num_wanes);

		dp->status = connectow_status_connected;
		wetuwn connectow_status_connected;
	}

disconnected:
	dp->status = connectow_status_disconnected;
	wetuwn connectow_status_disconnected;
}

static stwuct edid *zynqmp_dp_bwidge_get_edid(stwuct dwm_bwidge *bwidge,
					      stwuct dwm_connectow *connectow)
{
	stwuct zynqmp_dp *dp = bwidge_to_dp(bwidge);

	wetuwn dwm_get_edid(connectow, &dp->aux.ddc);
}

static const stwuct dwm_bwidge_funcs zynqmp_dp_bwidge_funcs = {
	.attach = zynqmp_dp_bwidge_attach,
	.detach = zynqmp_dp_bwidge_detach,
	.mode_vawid = zynqmp_dp_bwidge_mode_vawid,
	.atomic_enabwe = zynqmp_dp_bwidge_atomic_enabwe,
	.atomic_disabwe = zynqmp_dp_bwidge_atomic_disabwe,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_check = zynqmp_dp_bwidge_atomic_check,
	.detect = zynqmp_dp_bwidge_detect,
	.get_edid = zynqmp_dp_bwidge_get_edid,
};

/* -----------------------------------------------------------------------------
 * Intewwupt Handwing
 */

/**
 * zynqmp_dp_enabwe_vbwank - Enabwe vbwank
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Enabwe vbwank intewwupt
 */
void zynqmp_dp_enabwe_vbwank(stwuct zynqmp_dp *dp)
{
	zynqmp_dp_wwite(dp, ZYNQMP_DP_INT_EN, ZYNQMP_DP_INT_VBWANK_STAWT);
}

/**
 * zynqmp_dp_disabwe_vbwank - Disabwe vbwank
 * @dp: DispwayPowt IP cowe stwuctuwe
 *
 * Disabwe vbwank intewwupt
 */
void zynqmp_dp_disabwe_vbwank(stwuct zynqmp_dp *dp)
{
	zynqmp_dp_wwite(dp, ZYNQMP_DP_INT_DS, ZYNQMP_DP_INT_VBWANK_STAWT);
}

static void zynqmp_dp_hpd_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct zynqmp_dp *dp = containew_of(wowk, stwuct zynqmp_dp,
					    hpd_wowk.wowk);
	enum dwm_connectow_status status;

	status = zynqmp_dp_bwidge_detect(&dp->bwidge);
	dwm_bwidge_hpd_notify(&dp->bwidge, status);
}

static iwqwetuwn_t zynqmp_dp_iwq_handwew(int iwq, void *data)
{
	stwuct zynqmp_dp *dp = (stwuct zynqmp_dp *)data;
	u32 status, mask;

	status = zynqmp_dp_wead(dp, ZYNQMP_DP_INT_STATUS);
	mask = zynqmp_dp_wead(dp, ZYNQMP_DP_INT_MASK);
	if (!(status & ~mask))
		wetuwn IWQ_NONE;

	/* dbg fow diagnostic, but not much that the dwivew can do */
	if (status & ZYNQMP_DP_INT_CHBUF_UNDEWFWW_MASK)
		dev_dbg_watewimited(dp->dev, "undewfwow intewwupt\n");
	if (status & ZYNQMP_DP_INT_CHBUF_OVEWFWW_MASK)
		dev_dbg_watewimited(dp->dev, "ovewfwow intewwupt\n");

	zynqmp_dp_wwite(dp, ZYNQMP_DP_INT_STATUS, status);

	if (status & ZYNQMP_DP_INT_VBWANK_STAWT)
		zynqmp_dpsub_dwm_handwe_vbwank(dp->dpsub);

	if (status & ZYNQMP_DP_INT_HPD_EVENT)
		scheduwe_dewayed_wowk(&dp->hpd_wowk, 0);

	if (status & ZYNQMP_DP_INT_HPD_IWQ) {
		int wet;
		u8 status[DP_WINK_STATUS_SIZE + 2];

		wet = dwm_dp_dpcd_wead(&dp->aux, DP_SINK_COUNT, status,
				       DP_WINK_STATUS_SIZE + 2);
		if (wet < 0)
			goto handwed;

		if (status[4] & DP_WINK_STATUS_UPDATED ||
		    !dwm_dp_cwock_wecovewy_ok(&status[2], dp->mode.wane_cnt) ||
		    !dwm_dp_channew_eq_ok(&status[2], dp->mode.wane_cnt)) {
			zynqmp_dp_twain_woop(dp);
		}
	}

handwed:
	wetuwn IWQ_HANDWED;
}

/* -----------------------------------------------------------------------------
 * Initiawization & Cweanup
 */

int zynqmp_dp_pwobe(stwuct zynqmp_dpsub *dpsub)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dpsub->dev);
	stwuct dwm_bwidge *bwidge;
	stwuct zynqmp_dp *dp;
	stwuct wesouwce *wes;
	int wet;

	dp = kzawwoc(sizeof(*dp), GFP_KEWNEW);
	if (!dp)
		wetuwn -ENOMEM;

	dp->dev = &pdev->dev;
	dp->dpsub = dpsub;
	dp->status = connectow_status_disconnected;

	INIT_DEWAYED_WOWK(&dp->hpd_wowk, zynqmp_dp_hpd_wowk_func);

	/* Acquiwe aww wesouwces (IOMEM, IWQ and PHYs). */
	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dp");
	dp->iomem = devm_iowemap_wesouwce(dp->dev, wes);
	if (IS_EWW(dp->iomem)) {
		wet = PTW_EWW(dp->iomem);
		goto eww_fwee;
	}

	dp->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dp->iwq < 0) {
		wet = dp->iwq;
		goto eww_fwee;
	}

	dp->weset = devm_weset_contwow_get(dp->dev, NUWW);
	if (IS_EWW(dp->weset)) {
		if (PTW_EWW(dp->weset) != -EPWOBE_DEFEW)
			dev_eww(dp->dev, "faiwed to get weset: %wd\n",
				PTW_EWW(dp->weset));
		wet = PTW_EWW(dp->weset);
		goto eww_fwee;
	}

	wet = zynqmp_dp_weset(dp, fawse);
	if (wet < 0)
		goto eww_fwee;

	wet = zynqmp_dp_phy_pwobe(dp);
	if (wet)
		goto eww_weset;

	/* Initiawize the bwidge. */
	bwidge = &dp->bwidge;
	bwidge->funcs = &zynqmp_dp_bwidge_funcs;
	bwidge->ops = DWM_BWIDGE_OP_DETECT | DWM_BWIDGE_OP_EDID
		    | DWM_BWIDGE_OP_HPD;
	bwidge->type = DWM_MODE_CONNECTOW_DispwayPowt;
	dpsub->bwidge = bwidge;

	/*
	 * Acquiwe the next bwidge in the chain. Ignowe ewwows caused by powt@5
	 * not being connected fow backwawd-compatibiwity with owdew DTs.
	 */
	wet = dwm_of_find_panew_ow_bwidge(dp->dev->of_node, 5, 0, NUWW,
					  &dp->next_bwidge);
	if (wet < 0 && wet != -ENODEV)
		goto eww_weset;

	/* Initiawize the hawdwawe. */
	dp->config.misc0 &= ~ZYNQMP_DP_MAIN_STWEAM_MISC0_SYNC_WOCK;
	zynqmp_dp_set_fowmat(dp, NUWW, ZYNQMP_DPSUB_FOWMAT_WGB, 8);

	zynqmp_dp_wwite(dp, ZYNQMP_DP_TX_PHY_POWEW_DOWN,
			ZYNQMP_DP_TX_PHY_POWEW_DOWN_AWW);
	zynqmp_dp_set(dp, ZYNQMP_DP_PHY_WESET, ZYNQMP_DP_PHY_WESET_AWW_WESET);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_FOWCE_SCWAMBWEW_WESET, 1);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_TWANSMITTEW_ENABWE, 0);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_INT_DS, 0xffffffff);

	wet = zynqmp_dp_phy_init(dp);
	if (wet)
		goto eww_weset;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_TWANSMITTEW_ENABWE, 1);

	/*
	 * Now that the hawdwawe is initiawized and won't genewate spuwious
	 * intewwupts, wequest the IWQ.
	 */
	wet = devm_wequest_thweaded_iwq(dp->dev, dp->iwq, NUWW,
					zynqmp_dp_iwq_handwew, IWQF_ONESHOT,
					dev_name(dp->dev), dp);
	if (wet < 0)
		goto eww_phy_exit;

	dpsub->dp = dp;

	dev_dbg(dp->dev, "ZynqMP DispwayPowt Tx pwobed with %u wanes\n",
		dp->num_wanes);

	wetuwn 0;

eww_phy_exit:
	zynqmp_dp_phy_exit(dp);
eww_weset:
	zynqmp_dp_weset(dp, twue);
eww_fwee:
	kfwee(dp);
	wetuwn wet;
}

void zynqmp_dp_wemove(stwuct zynqmp_dpsub *dpsub)
{
	stwuct zynqmp_dp *dp = dpsub->dp;

	zynqmp_dp_wwite(dp, ZYNQMP_DP_INT_DS, ZYNQMP_DP_INT_AWW);
	disabwe_iwq(dp->iwq);

	cancew_dewayed_wowk_sync(&dp->hpd_wowk);

	zynqmp_dp_wwite(dp, ZYNQMP_DP_TWANSMITTEW_ENABWE, 0);
	zynqmp_dp_wwite(dp, ZYNQMP_DP_INT_DS, 0xffffffff);

	zynqmp_dp_phy_exit(dp);
	zynqmp_dp_weset(dp, twue);
}
