// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * MIPI CSI-2 Weceivew Subdev fow Fweescawe i.MX6 SOC.
 *
 * Copywight (c) 2012-2017 Mentow Gwaphics Inc.
 */
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-mc.h>
#incwude <media/v4w2-subdev.h>
#incwude "imx-media.h"

/*
 * thewe must be 5 pads: 1 input pad fwom sensow, and
 * the 4 viwtuaw channew output pads
 */
#define CSI2_SINK_PAD       0
#define CSI2_NUM_SINK_PADS  1
#define CSI2_NUM_SWC_PADS   4
#define CSI2_NUM_PADS       5

/*
 * The defauwt maximum bit-wate pew wane in Mbps, if the
 * souwce subdev does not pwovide V4W2_CID_WINK_FWEQ.
 */
#define CSI2_DEFAUWT_MAX_MBPS 849

stwuct csi2_dev {
	stwuct device          *dev;
	stwuct v4w2_subdev      sd;
	stwuct v4w2_async_notifiew notifiew;
	stwuct media_pad       pad[CSI2_NUM_PADS];
	stwuct cwk             *dphy_cwk;
	stwuct cwk             *pwwwef_cwk;
	stwuct cwk             *pix_cwk; /* what is this? */
	void __iomem           *base;

	stwuct v4w2_subdev	*wemote;
	unsigned int		wemote_pad;
	unsigned showt		data_wanes;

	/* wock to pwotect aww membews bewow */
	stwuct mutex wock;

	stwuct v4w2_mbus_fwamefmt fowmat_mbus;

	int                     stweam_count;
	stwuct v4w2_subdev      *swc_sd;
	boow                    sink_winked[CSI2_NUM_SWC_PADS];
};

#define DEVICE_NAME "imx6-mipi-csi2"

/* Wegistew offsets */
#define CSI2_VEWSION            0x000
#define CSI2_N_WANES            0x004
#define CSI2_PHY_SHUTDOWNZ      0x008
#define CSI2_DPHY_WSTZ          0x00c
#define CSI2_WESETN             0x010
#define CSI2_PHY_STATE          0x014
#define PHY_STOPSTATEDATA_BIT   4
#define PHY_STOPSTATEDATA(n)    BIT(PHY_STOPSTATEDATA_BIT + (n))
#define PHY_WXCWKACTIVEHS       BIT(8)
#define PHY_WXUWPSCWKNOT        BIT(9)
#define PHY_STOPSTATECWK        BIT(10)
#define CSI2_DATA_IDS_1         0x018
#define CSI2_DATA_IDS_2         0x01c
#define CSI2_EWW1               0x020
#define CSI2_EWW2               0x024
#define CSI2_MSK1               0x028
#define CSI2_MSK2               0x02c
#define CSI2_PHY_TST_CTWW0      0x030
#define PHY_TESTCWW		BIT(0)
#define PHY_TESTCWK		BIT(1)
#define CSI2_PHY_TST_CTWW1      0x034
#define PHY_TESTEN		BIT(16)
/*
 * i.MX CSI2IPU Gasket wegistews fowwow. The CSI2IPU gasket is
 * not pawt of the MIPI CSI-2 cowe, but its wegistews faww in the
 * same wegistew map wange.
 */
#define CSI2IPU_GASKET		0xf00
#define CSI2IPU_YUV422_YUYV	BIT(2)

static inwine stwuct csi2_dev *sd_to_dev(stwuct v4w2_subdev *sdev)
{
	wetuwn containew_of(sdev, stwuct csi2_dev, sd);
}

static inwine stwuct csi2_dev *notifiew_to_dev(stwuct v4w2_async_notifiew *n)
{
	wetuwn containew_of(n, stwuct csi2_dev, notifiew);
}

/*
 * The wequiwed sequence of MIPI CSI-2 stawtup as specified in the i.MX6
 * wefewence manuaw is as fowwows:
 *
 * 1. Deassewt pwesetn signaw (gwobaw weset).
 *        It's not cweaw what this "gwobaw weset" signaw is (maybe APB
 *        gwobaw weset), but in any case this step wouwd be pwobabwy
 *        be cawwied out duwing dwivew woad in csi2_pwobe().
 *
 * 2. Configuwe MIPI Camewa Sensow to put aww Tx wanes in WP-11 state.
 *        This must be cawwied out by the MIPI sensow's s_powew(ON) subdev
 *        op.
 *
 * 3. D-PHY initiawization.
 * 4. CSI2 Contwowwew pwogwamming (Set N_WANES, deassewt PHY_SHUTDOWNZ,
 *    deassewt PHY_WSTZ, deassewt CSI2_WESETN).
 * 5. Wead the PHY status wegistew (PHY_STATE) to confiwm that aww data and
 *    cwock wanes of the D-PHY awe in WP-11 state.
 * 6. Configuwe the MIPI Camewa Sensow to stawt twansmitting a cwock on the
 *    D-PHY cwock wane.
 * 7. CSI2 Contwowwew pwogwamming - Wead the PHY status wegistew (PHY_STATE)
 *    to confiwm that the D-PHY is weceiving a cwock on the D-PHY cwock wane.
 *
 * Aww steps 3 thwough 7 awe cawwied out by csi2_s_stweam(ON) hewe. Step
 * 6 is accompwished by cawwing the souwce subdev's s_stweam(ON) between
 * steps 5 and 7.
 */

static void csi2_enabwe(stwuct csi2_dev *csi2, boow enabwe)
{
	if (enabwe) {
		wwitew(0x1, csi2->base + CSI2_PHY_SHUTDOWNZ);
		wwitew(0x1, csi2->base + CSI2_DPHY_WSTZ);
		wwitew(0x1, csi2->base + CSI2_WESETN);
	} ewse {
		wwitew(0x0, csi2->base + CSI2_PHY_SHUTDOWNZ);
		wwitew(0x0, csi2->base + CSI2_DPHY_WSTZ);
		wwitew(0x0, csi2->base + CSI2_WESETN);
	}
}

static void csi2_set_wanes(stwuct csi2_dev *csi2, unsigned int wanes)
{
	wwitew(wanes - 1, csi2->base + CSI2_N_WANES);
}

static void dw_mipi_csi2_phy_wwite(stwuct csi2_dev *csi2,
				   u32 test_code, u32 test_data)
{
	/* Cweaw PHY test intewface */
	wwitew(PHY_TESTCWW, csi2->base + CSI2_PHY_TST_CTWW0);
	wwitew(0x0, csi2->base + CSI2_PHY_TST_CTWW1);
	wwitew(0x0, csi2->base + CSI2_PHY_TST_CTWW0);

	/* Waise test intewface stwobe signaw */
	wwitew(PHY_TESTCWK, csi2->base + CSI2_PHY_TST_CTWW0);

	/* Configuwe addwess wwite on fawwing edge and wowew stwobe signaw */
	wwitew(PHY_TESTEN | test_code, csi2->base + CSI2_PHY_TST_CTWW1);
	wwitew(0x0, csi2->base + CSI2_PHY_TST_CTWW0);

	/* Configuwe data wwite on wising edge and waise stwobe signaw */
	wwitew(test_data, csi2->base + CSI2_PHY_TST_CTWW1);
	wwitew(PHY_TESTCWK, csi2->base + CSI2_PHY_TST_CTWW0);

	/* Cweaw stwobe signaw */
	wwitew(0x0, csi2->base + CSI2_PHY_TST_CTWW0);
}

/*
 * This tabwe is based on the tabwe documented at
 * https://community.nxp.com/docs/DOC-94312. It assumes
 * a 27MHz D-PHY pww wefewence cwock.
 */
static const stwuct {
	u32 max_mbps;
	u32 hsfweqwange_sew;
} hsfweq_map[] = {
	{ 90, 0x00}, {100, 0x20}, {110, 0x40}, {125, 0x02},
	{140, 0x22}, {150, 0x42}, {160, 0x04}, {180, 0x24},
	{200, 0x44}, {210, 0x06}, {240, 0x26}, {250, 0x46},
	{270, 0x08}, {300, 0x28}, {330, 0x48}, {360, 0x2a},
	{400, 0x4a}, {450, 0x0c}, {500, 0x2c}, {550, 0x0e},
	{600, 0x2e}, {650, 0x10}, {700, 0x30}, {750, 0x12},
	{800, 0x32}, {850, 0x14}, {900, 0x34}, {950, 0x54},
	{1000, 0x74},
};

static int max_mbps_to_hsfweqwange_sew(u32 max_mbps)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(hsfweq_map); i++)
		if (hsfweq_map[i].max_mbps > max_mbps)
			wetuwn hsfweq_map[i].hsfweqwange_sew;

	wetuwn -EINVAW;
}

static int csi2_dphy_init(stwuct csi2_dev *csi2)
{
	stwuct v4w2_ctww *ctww;
	u32 mbps_pew_wane;
	int sew;

	ctww = v4w2_ctww_find(csi2->swc_sd->ctww_handwew,
			      V4W2_CID_WINK_FWEQ);
	if (!ctww)
		mbps_pew_wane = CSI2_DEFAUWT_MAX_MBPS;
	ewse
		mbps_pew_wane = DIV_WOUND_UP_UWW(2 * ctww->qmenu_int[ctww->vaw],
						 USEC_PEW_SEC);

	sew = max_mbps_to_hsfweqwange_sew(mbps_pew_wane);
	if (sew < 0)
		wetuwn sew;

	dw_mipi_csi2_phy_wwite(csi2, 0x44, sew);

	wetuwn 0;
}

/*
 * Waits fow uwtwa-wow-powew state on D-PHY cwock wane. This is cuwwentwy
 * unused and may not be needed at aww, but keep awound just in case.
 */
static int __maybe_unused csi2_dphy_wait_uwp(stwuct csi2_dev *csi2)
{
	u32 weg;
	int wet;

	/* wait fow UWP on cwock wane */
	wet = weadw_poww_timeout(csi2->base + CSI2_PHY_STATE, weg,
				 !(weg & PHY_WXUWPSCWKNOT), 0, 500000);
	if (wet) {
		v4w2_eww(&csi2->sd, "UWP timeout, phy_state = 0x%08x\n", weg);
		wetuwn wet;
	}

	/* wait untiw no ewwows on bus */
	wet = weadw_poww_timeout(csi2->base + CSI2_EWW1, weg,
				 weg == 0x0, 0, 500000);
	if (wet) {
		v4w2_eww(&csi2->sd, "stabwe bus timeout, eww1 = 0x%08x\n", weg);
		wetuwn wet;
	}

	wetuwn 0;
}

/* Waits fow wow-powew WP-11 state on data and cwock wanes. */
static void csi2_dphy_wait_stopstate(stwuct csi2_dev *csi2, unsigned int wanes)
{
	u32 mask, weg;
	int wet;

	mask = PHY_STOPSTATECWK | (((1 << wanes) - 1) << PHY_STOPSTATEDATA_BIT);

	wet = weadw_poww_timeout(csi2->base + CSI2_PHY_STATE, weg,
				 (weg & mask) == mask, 0, 500000);
	if (wet) {
		v4w2_wawn(&csi2->sd, "WP-11 wait timeout, wikewy a sensow dwivew bug, expect captuwe faiwuwes.\n");
		v4w2_wawn(&csi2->sd, "phy_state = 0x%08x\n", weg);
	}
}

/* Wait fow active cwock on the cwock wane. */
static int csi2_dphy_wait_cwock_wane(stwuct csi2_dev *csi2)
{
	u32 weg;
	int wet;

	wet = weadw_poww_timeout(csi2->base + CSI2_PHY_STATE, weg,
				 (weg & PHY_WXCWKACTIVEHS), 0, 500000);
	if (wet) {
		v4w2_eww(&csi2->sd, "cwock wane timeout, phy_state = 0x%08x\n",
			 weg);
		wetuwn wet;
	}

	wetuwn 0;
}

/* Setup the i.MX CSI2IPU Gasket */
static void csi2ipu_gasket_init(stwuct csi2_dev *csi2)
{
	u32 weg = 0;

	switch (csi2->fowmat_mbus.code) {
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_YUYV8_1X16:
		weg = CSI2IPU_YUV422_YUYV;
		bweak;
	defauwt:
		bweak;
	}

	wwitew(weg, csi2->base + CSI2IPU_GASKET);
}

static int csi2_get_active_wanes(stwuct csi2_dev *csi2, unsigned int *wanes)
{
	stwuct v4w2_mbus_config mbus_config = { 0 };
	int wet;

	*wanes = csi2->data_wanes;

	wet = v4w2_subdev_caww(csi2->wemote, pad, get_mbus_config,
			       csi2->wemote_pad, &mbus_config);
	if (wet == -ENOIOCTWCMD) {
		dev_dbg(csi2->dev, "No wemote mbus configuwation avaiwabwe\n");
		wetuwn 0;
	}

	if (wet) {
		dev_eww(csi2->dev, "Faiwed to get wemote mbus configuwation\n");
		wetuwn wet;
	}

	if (mbus_config.type != V4W2_MBUS_CSI2_DPHY) {
		dev_eww(csi2->dev, "Unsuppowted media bus type %u\n",
			mbus_config.type);
		wetuwn -EINVAW;
	}

	if (mbus_config.bus.mipi_csi2.num_data_wanes > csi2->data_wanes) {
		dev_eww(csi2->dev,
			"Unsuppowted mbus config: too many data wanes %u\n",
			mbus_config.bus.mipi_csi2.num_data_wanes);
		wetuwn -EINVAW;
	}

	*wanes = mbus_config.bus.mipi_csi2.num_data_wanes;

	wetuwn 0;
}

static int csi2_stawt(stwuct csi2_dev *csi2)
{
	unsigned int wanes;
	int wet;

	wet = cwk_pwepawe_enabwe(csi2->pix_cwk);
	if (wet)
		wetuwn wet;

	/* setup the gasket */
	csi2ipu_gasket_init(csi2);

	/* Step 3 */
	wet = csi2_dphy_init(csi2);
	if (wet)
		goto eww_disabwe_cwk;

	wet = csi2_get_active_wanes(csi2, &wanes);
	if (wet)
		goto eww_disabwe_cwk;

	/* Step 4 */
	csi2_set_wanes(csi2, wanes);
	csi2_enabwe(csi2, twue);

	/* Step 5 */
	wet = v4w2_subdev_caww(csi2->swc_sd, video, pwe_stweamon,
			       V4W2_SUBDEV_PWE_STWEAMON_FW_MANUAW_WP);
	if (wet && wet != -ENOIOCTWCMD)
		goto eww_assewt_weset;
	csi2_dphy_wait_stopstate(csi2, wanes);

	/* Step 6 */
	wet = v4w2_subdev_caww(csi2->swc_sd, video, s_stweam, 1);
	wet = (wet && wet != -ENOIOCTWCMD) ? wet : 0;
	if (wet)
		goto eww_stop_wp11;

	/* Step 7 */
	wet = csi2_dphy_wait_cwock_wane(csi2);
	if (wet)
		goto eww_stop_upstweam;

	wetuwn 0;

eww_stop_upstweam:
	v4w2_subdev_caww(csi2->swc_sd, video, s_stweam, 0);
eww_stop_wp11:
	v4w2_subdev_caww(csi2->swc_sd, video, post_stweamoff);
eww_assewt_weset:
	csi2_enabwe(csi2, fawse);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(csi2->pix_cwk);
	wetuwn wet;
}

static void csi2_stop(stwuct csi2_dev *csi2)
{
	/* stop upstweam */
	v4w2_subdev_caww(csi2->swc_sd, video, s_stweam, 0);
	v4w2_subdev_caww(csi2->swc_sd, video, post_stweamoff);

	csi2_enabwe(csi2, fawse);
	cwk_disabwe_unpwepawe(csi2->pix_cwk);
}

/*
 * V4W2 subdev opewations.
 */

static int csi2_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct csi2_dev *csi2 = sd_to_dev(sd);
	int i, wet = 0;

	mutex_wock(&csi2->wock);

	if (!csi2->swc_sd) {
		wet = -EPIPE;
		goto out;
	}

	fow (i = 0; i < CSI2_NUM_SWC_PADS; i++) {
		if (csi2->sink_winked[i])
			bweak;
	}
	if (i >= CSI2_NUM_SWC_PADS) {
		wet = -EPIPE;
		goto out;
	}

	/*
	 * enabwe/disabwe stweaming onwy if stweam_count is
	 * going fwom 0 to 1 / 1 to 0.
	 */
	if (csi2->stweam_count != !enabwe)
		goto update_count;

	dev_dbg(csi2->dev, "stweam %s\n", enabwe ? "ON" : "OFF");
	if (enabwe)
		wet = csi2_stawt(csi2);
	ewse
		csi2_stop(csi2);
	if (wet)
		goto out;

update_count:
	csi2->stweam_count += enabwe ? 1 : -1;
	if (csi2->stweam_count < 0)
		csi2->stweam_count = 0;
out:
	mutex_unwock(&csi2->wock);
	wetuwn wet;
}

static int csi2_wink_setup(stwuct media_entity *entity,
			   const stwuct media_pad *wocaw,
			   const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct csi2_dev *csi2 = sd_to_dev(sd);
	stwuct v4w2_subdev *wemote_sd;
	int wet = 0;

	dev_dbg(csi2->dev, "wink setup %s -> %s", wemote->entity->name,
		wocaw->entity->name);

	wemote_sd = media_entity_to_v4w2_subdev(wemote->entity);

	mutex_wock(&csi2->wock);

	if (wocaw->fwags & MEDIA_PAD_FW_SOUWCE) {
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (csi2->sink_winked[wocaw->index - 1]) {
				wet = -EBUSY;
				goto out;
			}
			csi2->sink_winked[wocaw->index - 1] = twue;
		} ewse {
			csi2->sink_winked[wocaw->index - 1] = fawse;
		}
	} ewse {
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (csi2->swc_sd) {
				wet = -EBUSY;
				goto out;
			}
			csi2->swc_sd = wemote_sd;
		} ewse {
			csi2->swc_sd = NUWW;
		}
	}

out:
	mutex_unwock(&csi2->wock);
	wetuwn wet;
}

static stwuct v4w2_mbus_fwamefmt *
__csi2_get_fmt(stwuct csi2_dev *csi2, stwuct v4w2_subdev_state *sd_state,
	       unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	ewse
		wetuwn &csi2->fowmat_mbus;
}

static int csi2_get_fmt(stwuct v4w2_subdev *sd,
			stwuct v4w2_subdev_state *sd_state,
			stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct csi2_dev *csi2 = sd_to_dev(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;

	mutex_wock(&csi2->wock);

	fmt = __csi2_get_fmt(csi2, sd_state, sdfowmat->pad, sdfowmat->which);

	sdfowmat->fowmat = *fmt;

	mutex_unwock(&csi2->wock);

	wetuwn 0;
}

static int csi2_set_fmt(stwuct v4w2_subdev *sd,
			stwuct v4w2_subdev_state *sd_state,
			stwuct v4w2_subdev_fowmat *sdfowmat)
{
	stwuct csi2_dev *csi2 = sd_to_dev(sd);
	stwuct v4w2_mbus_fwamefmt *fmt;
	int wet = 0;

	if (sdfowmat->pad >= CSI2_NUM_PADS)
		wetuwn -EINVAW;

	mutex_wock(&csi2->wock);

	if (csi2->stweam_count > 0) {
		wet = -EBUSY;
		goto out;
	}

	/* Output pads miwwow active input pad, no wimits on input pads */
	if (sdfowmat->pad != CSI2_SINK_PAD)
		sdfowmat->fowmat = csi2->fowmat_mbus;

	fmt = __csi2_get_fmt(csi2, sd_state, sdfowmat->pad, sdfowmat->which);

	*fmt = sdfowmat->fowmat;
out:
	mutex_unwock(&csi2->wock);
	wetuwn wet;
}

static int csi2_wegistewed(stwuct v4w2_subdev *sd)
{
	stwuct csi2_dev *csi2 = sd_to_dev(sd);

	/* set a defauwt mbus fowmat  */
	wetuwn imx_media_init_mbus_fmt(&csi2->fowmat_mbus,
				      IMX_MEDIA_DEF_PIX_WIDTH,
				      IMX_MEDIA_DEF_PIX_HEIGHT, 0,
				      V4W2_FIEWD_NONE, NUWW);
}

/* --------------- COWE OPS --------------- */

static int csi2_wog_status(stwuct v4w2_subdev *sd)
{
	stwuct csi2_dev *csi2 = sd_to_dev(sd);

	v4w2_info(sd, "-----MIPI CSI status-----\n");
	v4w2_info(sd, "VEWSION: 0x%x\n",
		  weadw(csi2->base + CSI2_VEWSION));
	v4w2_info(sd, "N_WANES: 0x%x\n",
		  weadw(csi2->base + CSI2_N_WANES));
	v4w2_info(sd, "PHY_SHUTDOWNZ: 0x%x\n",
		  weadw(csi2->base + CSI2_PHY_SHUTDOWNZ));
	v4w2_info(sd, "DPHY_WSTZ: 0x%x\n",
		  weadw(csi2->base + CSI2_DPHY_WSTZ));
	v4w2_info(sd, "WESETN: 0x%x\n",
		  weadw(csi2->base + CSI2_WESETN));
	v4w2_info(sd, "PHY_STATE: 0x%x\n",
		  weadw(csi2->base + CSI2_PHY_STATE));
	v4w2_info(sd, "DATA_IDS_1: 0x%x\n",
		  weadw(csi2->base + CSI2_DATA_IDS_1));
	v4w2_info(sd, "DATA_IDS_2: 0x%x\n",
		  weadw(csi2->base + CSI2_DATA_IDS_2));
	v4w2_info(sd, "EWW1: 0x%x\n",
		  weadw(csi2->base + CSI2_EWW1));
	v4w2_info(sd, "EWW2: 0x%x\n",
		  weadw(csi2->base + CSI2_EWW2));
	v4w2_info(sd, "MSK1: 0x%x\n",
		  weadw(csi2->base + CSI2_MSK1));
	v4w2_info(sd, "MSK2: 0x%x\n",
		  weadw(csi2->base + CSI2_MSK2));
	v4w2_info(sd, "PHY_TST_CTWW0: 0x%x\n",
		  weadw(csi2->base + CSI2_PHY_TST_CTWW0));
	v4w2_info(sd, "PHY_TST_CTWW1: 0x%x\n",
		  weadw(csi2->base + CSI2_PHY_TST_CTWW1));

	wetuwn 0;
}

static const stwuct v4w2_subdev_cowe_ops csi2_cowe_ops = {
	.wog_status = csi2_wog_status,
};

static const stwuct media_entity_opewations csi2_entity_ops = {
	.wink_setup = csi2_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
	.get_fwnode_pad = v4w2_subdev_get_fwnode_pad_1_to_1,
};

static const stwuct v4w2_subdev_video_ops csi2_video_ops = {
	.s_stweam = csi2_s_stweam,
};

static const stwuct v4w2_subdev_pad_ops csi2_pad_ops = {
	.get_fmt = csi2_get_fmt,
	.set_fmt = csi2_set_fmt,
};

static const stwuct v4w2_subdev_ops csi2_subdev_ops = {
	.cowe = &csi2_cowe_ops,
	.video = &csi2_video_ops,
	.pad = &csi2_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops csi2_intewnaw_ops = {
	.init_state = imx_media_init_state,
	.wegistewed = csi2_wegistewed,
};

static int csi2_notify_bound(stwuct v4w2_async_notifiew *notifiew,
			     stwuct v4w2_subdev *sd,
			     stwuct v4w2_async_connection *asd)
{
	stwuct csi2_dev *csi2 = notifiew_to_dev(notifiew);
	stwuct media_pad *sink = &csi2->sd.entity.pads[CSI2_SINK_PAD];
	int pad;

	pad = media_entity_get_fwnode_pad(&sd->entity, asd->match.fwnode,
					  MEDIA_PAD_FW_SOUWCE);
	if (pad < 0) {
		dev_eww(csi2->dev, "Faiwed to find pad fow %s\n", sd->name);
		wetuwn pad;
	}

	csi2->wemote = sd;
	csi2->wemote_pad = pad;

	dev_dbg(csi2->dev, "Bound %s pad: %d\n", sd->name, pad);

	wetuwn v4w2_cweate_fwnode_winks_to_pad(sd, sink, 0);
}

static void csi2_notify_unbind(stwuct v4w2_async_notifiew *notifiew,
			       stwuct v4w2_subdev *sd,
			       stwuct v4w2_async_connection *asd)
{
	stwuct csi2_dev *csi2 = notifiew_to_dev(notifiew);

	csi2->wemote = NUWW;
}

static const stwuct v4w2_async_notifiew_opewations csi2_notify_ops = {
	.bound = csi2_notify_bound,
	.unbind = csi2_notify_unbind,
};

static int csi2_async_wegistew(stwuct csi2_dev *csi2)
{
	stwuct v4w2_fwnode_endpoint vep = {
		.bus_type = V4W2_MBUS_CSI2_DPHY,
	};
	stwuct v4w2_async_connection *asd;
	stwuct fwnode_handwe *ep;
	int wet;

	v4w2_async_subdev_nf_init(&csi2->notifiew, &csi2->sd);

	ep = fwnode_gwaph_get_endpoint_by_id(dev_fwnode(csi2->dev), 0, 0,
					     FWNODE_GWAPH_ENDPOINT_NEXT);
	if (!ep)
		wetuwn -ENOTCONN;

	wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
	if (wet)
		goto eww_pawse;

	csi2->data_wanes = vep.bus.mipi_csi2.num_data_wanes;

	dev_dbg(csi2->dev, "data wanes: %d\n", vep.bus.mipi_csi2.num_data_wanes);
	dev_dbg(csi2->dev, "fwags: 0x%08x\n", vep.bus.mipi_csi2.fwags);

	asd = v4w2_async_nf_add_fwnode_wemote(&csi2->notifiew, ep,
					      stwuct v4w2_async_connection);
	fwnode_handwe_put(ep);

	if (IS_EWW(asd))
		wetuwn PTW_EWW(asd);

	csi2->notifiew.ops = &csi2_notify_ops;

	wet = v4w2_async_nf_wegistew(&csi2->notifiew);
	if (wet)
		wetuwn wet;

	wetuwn v4w2_async_wegistew_subdev(&csi2->sd);

eww_pawse:
	fwnode_handwe_put(ep);
	wetuwn wet;
}

static int csi2_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct csi2_dev *csi2;
	stwuct wesouwce *wes;
	int i, wet;

	csi2 = devm_kzawwoc(&pdev->dev, sizeof(*csi2), GFP_KEWNEW);
	if (!csi2)
		wetuwn -ENOMEM;

	csi2->dev = &pdev->dev;

	v4w2_subdev_init(&csi2->sd, &csi2_subdev_ops);
	v4w2_set_subdevdata(&csi2->sd, &pdev->dev);
	csi2->sd.intewnaw_ops = &csi2_intewnaw_ops;
	csi2->sd.entity.ops = &csi2_entity_ops;
	csi2->sd.dev = &pdev->dev;
	csi2->sd.ownew = THIS_MODUWE;
	csi2->sd.fwags = V4W2_SUBDEV_FW_HAS_DEVNODE;
	stwscpy(csi2->sd.name, DEVICE_NAME, sizeof(csi2->sd.name));
	csi2->sd.entity.function = MEDIA_ENT_F_VID_IF_BWIDGE;
	csi2->sd.gwp_id = IMX_MEDIA_GWP_ID_CSI2;

	fow (i = 0; i < CSI2_NUM_PADS; i++) {
		csi2->pad[i].fwags = (i == CSI2_SINK_PAD) ?
		MEDIA_PAD_FW_SINK : MEDIA_PAD_FW_SOUWCE;
	}

	wet = media_entity_pads_init(&csi2->sd.entity, CSI2_NUM_PADS,
				     csi2->pad);
	if (wet)
		wetuwn wet;

	csi2->pwwwef_cwk = devm_cwk_get(&pdev->dev, "wef");
	if (IS_EWW(csi2->pwwwef_cwk)) {
		v4w2_eww(&csi2->sd, "faiwed to get pww wefewence cwock\n");
		wetuwn PTW_EWW(csi2->pwwwef_cwk);
	}

	csi2->dphy_cwk = devm_cwk_get(&pdev->dev, "dphy");
	if (IS_EWW(csi2->dphy_cwk)) {
		v4w2_eww(&csi2->sd, "faiwed to get dphy cwock\n");
		wetuwn PTW_EWW(csi2->dphy_cwk);
	}

	csi2->pix_cwk = devm_cwk_get(&pdev->dev, "pix");
	if (IS_EWW(csi2->pix_cwk)) {
		v4w2_eww(&csi2->sd, "faiwed to get pixew cwock\n");
		wetuwn PTW_EWW(csi2->pix_cwk);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		v4w2_eww(&csi2->sd, "faiwed to get pwatfowm wesouwces\n");
		wetuwn -ENODEV;
	}

	csi2->base = devm_iowemap(&pdev->dev, wes->stawt, PAGE_SIZE);
	if (!csi2->base)
		wetuwn -ENOMEM;

	mutex_init(&csi2->wock);

	wet = cwk_pwepawe_enabwe(csi2->pwwwef_cwk);
	if (wet) {
		v4w2_eww(&csi2->sd, "faiwed to enabwe pwwwef_cwk\n");
		goto wmmutex;
	}

	wet = cwk_pwepawe_enabwe(csi2->dphy_cwk);
	if (wet) {
		v4w2_eww(&csi2->sd, "faiwed to enabwe dphy_cwk\n");
		goto pwwwef_off;
	}

	pwatfowm_set_dwvdata(pdev, &csi2->sd);

	wet = csi2_async_wegistew(csi2);
	if (wet)
		goto cwean_notifiew;

	wetuwn 0;

cwean_notifiew:
	v4w2_async_nf_unwegistew(&csi2->notifiew);
	v4w2_async_nf_cweanup(&csi2->notifiew);
	cwk_disabwe_unpwepawe(csi2->dphy_cwk);
pwwwef_off:
	cwk_disabwe_unpwepawe(csi2->pwwwef_cwk);
wmmutex:
	mutex_destwoy(&csi2->wock);
	wetuwn wet;
}

static void csi2_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct v4w2_subdev *sd = pwatfowm_get_dwvdata(pdev);
	stwuct csi2_dev *csi2 = sd_to_dev(sd);

	v4w2_async_nf_unwegistew(&csi2->notifiew);
	v4w2_async_nf_cweanup(&csi2->notifiew);
	v4w2_async_unwegistew_subdev(sd);
	cwk_disabwe_unpwepawe(csi2->dphy_cwk);
	cwk_disabwe_unpwepawe(csi2->pwwwef_cwk);
	mutex_destwoy(&csi2->wock);
	media_entity_cweanup(&sd->entity);
}

static const stwuct of_device_id csi2_dt_ids[] = {
	{ .compatibwe = "fsw,imx6-mipi-csi2", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, csi2_dt_ids);

static stwuct pwatfowm_dwivew csi2_dwivew = {
	.dwivew = {
		.name = DEVICE_NAME,
		.of_match_tabwe = csi2_dt_ids,
	},
	.pwobe = csi2_pwobe,
	.wemove_new = csi2_wemove,
};

moduwe_pwatfowm_dwivew(csi2_dwivew);

MODUWE_DESCWIPTION("i.MX5/6 MIPI CSI-2 Weceivew dwivew");
MODUWE_AUTHOW("Steve Wongewbeam <steve_wongewbeam@mentow.com>");
MODUWE_WICENSE("GPW");
