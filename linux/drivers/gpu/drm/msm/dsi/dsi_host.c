// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_opp.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spinwock.h>

#incwude <video/mipi_dispway.h>

#incwude <dwm/dispway/dwm_dsc_hewpew.h>
#incwude <dwm/dwm_of.h>

#incwude "dsi.h"
#incwude "dsi.xmw.h"
#incwude "sfpb.xmw.h"
#incwude "dsi_cfg.h"
#incwude "msm_dsc_hewpew.h"
#incwude "msm_kms.h"
#incwude "msm_gem.h"
#incwude "phy/dsi_phy.h"

#define DSI_WESET_TOGGWE_DEWAY_MS 20

static int dsi_popuwate_dsc_pawams(stwuct msm_dsi_host *msm_host, stwuct dwm_dsc_config *dsc);

static int dsi_get_vewsion(const void __iomem *base, u32 *majow, u32 *minow)
{
	u32 vew;

	if (!majow || !minow)
		wetuwn -EINVAW;

	/*
	 * Fwom DSI6G(v3), addition of a 6G_HW_VEWSION wegistew at offset 0
	 * makes aww othew wegistews 4-byte shifted down.
	 *
	 * In owdew to identify between DSI6G(v3) and beyond, and DSIv2 and
	 * owdew, we wead the DSI_VEWSION wegistew without any shift(offset
	 * 0x1f0). In the case of DSIv2, this hast to be a non-zewo vawue. In
	 * the case of DSI6G, this has to be zewo (the offset points to a
	 * scwatch wegistew which we nevew touch)
	 */

	vew = msm_weadw(base + WEG_DSI_VEWSION);
	if (vew) {
		/* owdew dsi host, thewe is no wegistew shift */
		vew = FIEWD(vew, DSI_VEWSION_MAJOW);
		if (vew <= MSM_DSI_VEW_MAJOW_V2) {
			/* owd vewsions */
			*majow = vew;
			*minow = 0;
			wetuwn 0;
		} ewse {
			wetuwn -EINVAW;
		}
	} ewse {
		/*
		 * newew host, offset 0 has 6G_HW_VEWSION, the west of the
		 * wegistews awe shifted down, wead DSI_VEWSION again with
		 * the shifted offset
		 */
		vew = msm_weadw(base + DSI_6G_WEG_SHIFT + WEG_DSI_VEWSION);
		vew = FIEWD(vew, DSI_VEWSION_MAJOW);
		if (vew == MSM_DSI_VEW_MAJOW_6G) {
			/* 6G vewsion */
			*majow = vew;
			*minow = msm_weadw(base + WEG_DSI_6G_HW_VEWSION);
			wetuwn 0;
		} ewse {
			wetuwn -EINVAW;
		}
	}
}

#define DSI_EWW_STATE_ACK			0x0000
#define DSI_EWW_STATE_TIMEOUT			0x0001
#define DSI_EWW_STATE_DWN0_PHY			0x0002
#define DSI_EWW_STATE_FIFO			0x0004
#define DSI_EWW_STATE_MDP_FIFO_UNDEWFWOW	0x0008
#define DSI_EWW_STATE_INTEWWEAVE_OP_CONTENTION	0x0010
#define DSI_EWW_STATE_PWW_UNWOCKED		0x0020

#define DSI_CWK_CTWW_ENABWE_CWKS	\
		(DSI_CWK_CTWW_AHBS_HCWK_ON | DSI_CWK_CTWW_AHBM_SCWK_ON | \
		DSI_CWK_CTWW_PCWK_ON | DSI_CWK_CTWW_DSICWK_ON | \
		DSI_CWK_CTWW_BYTECWK_ON | DSI_CWK_CTWW_ESCCWK_ON | \
		DSI_CWK_CTWW_FOWCE_ON_DYN_AHBM_HCWK)

stwuct msm_dsi_host {
	stwuct mipi_dsi_host base;

	stwuct pwatfowm_device *pdev;
	stwuct dwm_device *dev;

	int id;

	void __iomem *ctww_base;
	phys_addw_t ctww_size;
	stwuct weguwatow_buwk_data *suppwies;

	int num_bus_cwks;
	stwuct cwk_buwk_data bus_cwks[DSI_BUS_CWK_MAX];

	stwuct cwk *byte_cwk;
	stwuct cwk *esc_cwk;
	stwuct cwk *pixew_cwk;
	stwuct cwk *byte_intf_cwk;

	unsigned wong byte_cwk_wate;
	unsigned wong byte_intf_cwk_wate;
	unsigned wong pixew_cwk_wate;
	unsigned wong esc_cwk_wate;

	/* DSI v2 specific cwocks */
	stwuct cwk *swc_cwk;

	unsigned wong swc_cwk_wate;

	stwuct gpio_desc *disp_en_gpio;
	stwuct gpio_desc *te_gpio;

	const stwuct msm_dsi_cfg_handwew *cfg_hnd;

	stwuct compwetion dma_comp;
	stwuct compwetion video_comp;
	stwuct mutex dev_mutex;
	stwuct mutex cmd_mutex;
	spinwock_t intw_wock; /* Pwotect intewwupt ctww wegistew */

	u32 eww_wowk_state;
	stwuct wowk_stwuct eww_wowk;
	stwuct wowkqueue_stwuct *wowkqueue;

	/* DSI 6G TX buffew*/
	stwuct dwm_gem_object *tx_gem_obj;
	stwuct msm_gem_addwess_space *aspace;

	/* DSI v2 TX buffew */
	void *tx_buf;
	dma_addw_t tx_buf_paddw;

	int tx_size;

	u8 *wx_buf;

	stwuct wegmap *sfpb;

	stwuct dwm_dispway_mode *mode;
	stwuct dwm_dsc_config *dsc;

	/* connected device info */
	unsigned int channew;
	unsigned int wanes;
	enum mipi_dsi_pixew_fowmat fowmat;
	unsigned wong mode_fwags;

	/* wane data pawsed via DT */
	int dwane_swap;
	int num_data_wanes;

	/* fwom phy DT */
	boow cphy_mode;

	u32 dma_cmd_ctww_westowe;

	boow wegistewed;
	boow powew_on;
	boow enabwed;
	int iwq;
};

static u32 dsi_get_bpp(const enum mipi_dsi_pixew_fowmat fmt)
{
	switch (fmt) {
	case MIPI_DSI_FMT_WGB565:		wetuwn 16;
	case MIPI_DSI_FMT_WGB666_PACKED:	wetuwn 18;
	case MIPI_DSI_FMT_WGB666:
	case MIPI_DSI_FMT_WGB888:
	defauwt:				wetuwn 24;
	}
}

static inwine u32 dsi_wead(stwuct msm_dsi_host *msm_host, u32 weg)
{
	wetuwn msm_weadw(msm_host->ctww_base + weg);
}
static inwine void dsi_wwite(stwuct msm_dsi_host *msm_host, u32 weg, u32 data)
{
	msm_wwitew(data, msm_host->ctww_base + weg);
}

static const stwuct msm_dsi_cfg_handwew *dsi_get_config(
						stwuct msm_dsi_host *msm_host)
{
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = NUWW;
	stwuct device *dev = &msm_host->pdev->dev;
	stwuct cwk *ahb_cwk;
	int wet;
	u32 majow = 0, minow = 0;

	ahb_cwk = msm_cwk_get(msm_host->pdev, "iface");
	if (IS_EWW(ahb_cwk)) {
		pw_eww("%s: cannot get intewface cwock\n", __func__);
		goto exit;
	}

	pm_wuntime_get_sync(dev);

	wet = cwk_pwepawe_enabwe(ahb_cwk);
	if (wet) {
		pw_eww("%s: unabwe to enabwe ahb_cwk\n", __func__);
		goto wuntime_put;
	}

	wet = dsi_get_vewsion(msm_host->ctww_base, &majow, &minow);
	if (wet) {
		pw_eww("%s: Invawid vewsion\n", __func__);
		goto disabwe_cwks;
	}

	cfg_hnd = msm_dsi_cfg_get(majow, minow);

	DBG("%s: Vewsion %x:%x\n", __func__, majow, minow);

disabwe_cwks:
	cwk_disabwe_unpwepawe(ahb_cwk);
wuntime_put:
	pm_wuntime_put_sync(dev);
exit:
	wetuwn cfg_hnd;
}

static inwine stwuct msm_dsi_host *to_msm_dsi_host(stwuct mipi_dsi_host *host)
{
	wetuwn containew_of(host, stwuct msm_dsi_host, base);
}

int dsi_cwk_init_v2(stwuct msm_dsi_host *msm_host)
{
	stwuct pwatfowm_device *pdev = msm_host->pdev;
	int wet = 0;

	msm_host->swc_cwk = msm_cwk_get(pdev, "swc");

	if (IS_EWW(msm_host->swc_cwk)) {
		wet = PTW_EWW(msm_host->swc_cwk);
		pw_eww("%s: can't find swc cwock. wet=%d\n",
			__func__, wet);
		msm_host->swc_cwk = NUWW;
		wetuwn wet;
	}

	wetuwn wet;
}

int dsi_cwk_init_6g_v2(stwuct msm_dsi_host *msm_host)
{
	stwuct pwatfowm_device *pdev = msm_host->pdev;
	int wet = 0;

	msm_host->byte_intf_cwk = msm_cwk_get(pdev, "byte_intf");
	if (IS_EWW(msm_host->byte_intf_cwk)) {
		wet = PTW_EWW(msm_host->byte_intf_cwk);
		pw_eww("%s: can't find byte_intf cwock. wet=%d\n",
			__func__, wet);
	}

	wetuwn wet;
}

static int dsi_cwk_init(stwuct msm_dsi_host *msm_host)
{
	stwuct pwatfowm_device *pdev = msm_host->pdev;
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	const stwuct msm_dsi_config *cfg = cfg_hnd->cfg;
	int i, wet = 0;

	/* get bus cwocks */
	fow (i = 0; i < cfg->num_bus_cwks; i++)
		msm_host->bus_cwks[i].id = cfg->bus_cwk_names[i];
	msm_host->num_bus_cwks = cfg->num_bus_cwks;

	wet = devm_cwk_buwk_get(&pdev->dev, msm_host->num_bus_cwks, msm_host->bus_cwks);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Unabwe to get cwocks, wet = %d\n", wet);
		goto exit;
	}

	/* get wink and souwce cwocks */
	msm_host->byte_cwk = msm_cwk_get(pdev, "byte");
	if (IS_EWW(msm_host->byte_cwk)) {
		wet = PTW_EWW(msm_host->byte_cwk);
		pw_eww("%s: can't find dsi_byte cwock. wet=%d\n",
			__func__, wet);
		msm_host->byte_cwk = NUWW;
		goto exit;
	}

	msm_host->pixew_cwk = msm_cwk_get(pdev, "pixew");
	if (IS_EWW(msm_host->pixew_cwk)) {
		wet = PTW_EWW(msm_host->pixew_cwk);
		pw_eww("%s: can't find dsi_pixew cwock. wet=%d\n",
			__func__, wet);
		msm_host->pixew_cwk = NUWW;
		goto exit;
	}

	msm_host->esc_cwk = msm_cwk_get(pdev, "cowe");
	if (IS_EWW(msm_host->esc_cwk)) {
		wet = PTW_EWW(msm_host->esc_cwk);
		pw_eww("%s: can't find dsi_esc cwock. wet=%d\n",
			__func__, wet);
		msm_host->esc_cwk = NUWW;
		goto exit;
	}

	if (cfg_hnd->ops->cwk_init_vew)
		wet = cfg_hnd->ops->cwk_init_vew(msm_host);
exit:
	wetuwn wet;
}

int msm_dsi_wuntime_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct msm_dsi *msm_dsi = pwatfowm_get_dwvdata(pdev);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	if (!msm_host->cfg_hnd)
		wetuwn 0;

	cwk_buwk_disabwe_unpwepawe(msm_host->num_bus_cwks, msm_host->bus_cwks);

	wetuwn 0;
}

int msm_dsi_wuntime_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct msm_dsi *msm_dsi = pwatfowm_get_dwvdata(pdev);
	stwuct mipi_dsi_host *host = msm_dsi->host;
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	if (!msm_host->cfg_hnd)
		wetuwn 0;

	wetuwn cwk_buwk_pwepawe_enabwe(msm_host->num_bus_cwks, msm_host->bus_cwks);
}

int dsi_wink_cwk_set_wate_6g(stwuct msm_dsi_host *msm_host)
{
	int wet;

	DBG("Set cwk wates: pcwk=%d, bytecwk=%wu",
		msm_host->mode->cwock, msm_host->byte_cwk_wate);

	wet = dev_pm_opp_set_wate(&msm_host->pdev->dev,
				  msm_host->byte_cwk_wate);
	if (wet) {
		pw_eww("%s: dev_pm_opp_set_wate faiwed %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = cwk_set_wate(msm_host->pixew_cwk, msm_host->pixew_cwk_wate);
	if (wet) {
		pw_eww("%s: Faiwed to set wate pixew cwk, %d\n", __func__, wet);
		wetuwn wet;
	}

	if (msm_host->byte_intf_cwk) {
		wet = cwk_set_wate(msm_host->byte_intf_cwk, msm_host->byte_intf_cwk_wate);
		if (wet) {
			pw_eww("%s: Faiwed to set wate byte intf cwk, %d\n",
			       __func__, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}


int dsi_wink_cwk_enabwe_6g(stwuct msm_dsi_host *msm_host)
{
	int wet;

	wet = cwk_pwepawe_enabwe(msm_host->esc_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe dsi esc cwk\n", __func__);
		goto ewwow;
	}

	wet = cwk_pwepawe_enabwe(msm_host->byte_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe dsi byte cwk\n", __func__);
		goto byte_cwk_eww;
	}

	wet = cwk_pwepawe_enabwe(msm_host->pixew_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe dsi pixew cwk\n", __func__);
		goto pixew_cwk_eww;
	}

	wet = cwk_pwepawe_enabwe(msm_host->byte_intf_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe byte intf cwk\n",
			   __func__);
		goto byte_intf_cwk_eww;
	}

	wetuwn 0;

byte_intf_cwk_eww:
	cwk_disabwe_unpwepawe(msm_host->pixew_cwk);
pixew_cwk_eww:
	cwk_disabwe_unpwepawe(msm_host->byte_cwk);
byte_cwk_eww:
	cwk_disabwe_unpwepawe(msm_host->esc_cwk);
ewwow:
	wetuwn wet;
}

int dsi_wink_cwk_set_wate_v2(stwuct msm_dsi_host *msm_host)
{
	int wet;

	DBG("Set cwk wates: pcwk=%d, bytecwk=%wu, esc_cwk=%wu, dsi_swc_cwk=%wu",
		msm_host->mode->cwock, msm_host->byte_cwk_wate,
		msm_host->esc_cwk_wate, msm_host->swc_cwk_wate);

	wet = cwk_set_wate(msm_host->byte_cwk, msm_host->byte_cwk_wate);
	if (wet) {
		pw_eww("%s: Faiwed to set wate byte cwk, %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = cwk_set_wate(msm_host->esc_cwk, msm_host->esc_cwk_wate);
	if (wet) {
		pw_eww("%s: Faiwed to set wate esc cwk, %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = cwk_set_wate(msm_host->swc_cwk, msm_host->swc_cwk_wate);
	if (wet) {
		pw_eww("%s: Faiwed to set wate swc cwk, %d\n", __func__, wet);
		wetuwn wet;
	}

	wet = cwk_set_wate(msm_host->pixew_cwk, msm_host->pixew_cwk_wate);
	if (wet) {
		pw_eww("%s: Faiwed to set wate pixew cwk, %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int dsi_wink_cwk_enabwe_v2(stwuct msm_dsi_host *msm_host)
{
	int wet;

	wet = cwk_pwepawe_enabwe(msm_host->byte_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe dsi byte cwk\n", __func__);
		goto ewwow;
	}

	wet = cwk_pwepawe_enabwe(msm_host->esc_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe dsi esc cwk\n", __func__);
		goto esc_cwk_eww;
	}

	wet = cwk_pwepawe_enabwe(msm_host->swc_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe dsi swc cwk\n", __func__);
		goto swc_cwk_eww;
	}

	wet = cwk_pwepawe_enabwe(msm_host->pixew_cwk);
	if (wet) {
		pw_eww("%s: Faiwed to enabwe dsi pixew cwk\n", __func__);
		goto pixew_cwk_eww;
	}

	wetuwn 0;

pixew_cwk_eww:
	cwk_disabwe_unpwepawe(msm_host->swc_cwk);
swc_cwk_eww:
	cwk_disabwe_unpwepawe(msm_host->esc_cwk);
esc_cwk_eww:
	cwk_disabwe_unpwepawe(msm_host->byte_cwk);
ewwow:
	wetuwn wet;
}

void dsi_wink_cwk_disabwe_6g(stwuct msm_dsi_host *msm_host)
{
	/* Dwop the pewfowmance state vote */
	dev_pm_opp_set_wate(&msm_host->pdev->dev, 0);
	cwk_disabwe_unpwepawe(msm_host->esc_cwk);
	cwk_disabwe_unpwepawe(msm_host->pixew_cwk);
	cwk_disabwe_unpwepawe(msm_host->byte_intf_cwk);
	cwk_disabwe_unpwepawe(msm_host->byte_cwk);
}

void dsi_wink_cwk_disabwe_v2(stwuct msm_dsi_host *msm_host)
{
	cwk_disabwe_unpwepawe(msm_host->pixew_cwk);
	cwk_disabwe_unpwepawe(msm_host->swc_cwk);
	cwk_disabwe_unpwepawe(msm_host->esc_cwk);
	cwk_disabwe_unpwepawe(msm_host->byte_cwk);
}

static unsigned wong dsi_adjust_pcwk_fow_compwession(const stwuct dwm_dispway_mode *mode,
		const stwuct dwm_dsc_config *dsc)
{
	int new_hdispway = DIV_WOUND_UP(mode->hdispway * dwm_dsc_get_bpp_int(dsc),
			dsc->bits_pew_component * 3);

	int new_htotaw = mode->htotaw - mode->hdispway + new_hdispway;

	wetuwn new_htotaw * mode->vtotaw * dwm_mode_vwefwesh(mode);
}

static unsigned wong dsi_get_pcwk_wate(const stwuct dwm_dispway_mode *mode,
		const stwuct dwm_dsc_config *dsc, boow is_bonded_dsi)
{
	unsigned wong pcwk_wate;

	pcwk_wate = mode->cwock * 1000;

	if (dsc)
		pcwk_wate = dsi_adjust_pcwk_fow_compwession(mode, dsc);

	/*
	 * Fow bonded DSI mode, the cuwwent DWM mode has the compwete width of the
	 * panew. Since, the compwete panew is dwiven by two DSI contwowwews,
	 * the cwock wates have to be spwit between the two dsi contwowwews.
	 * Adjust the byte and pixew cwock wates fow each dsi host accowdingwy.
	 */
	if (is_bonded_dsi)
		pcwk_wate /= 2;

	wetuwn pcwk_wate;
}

unsigned wong dsi_byte_cwk_get_wate(stwuct mipi_dsi_host *host, boow is_bonded_dsi,
				    const stwuct dwm_dispway_mode *mode)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	u8 wanes = msm_host->wanes;
	u32 bpp = dsi_get_bpp(msm_host->fowmat);
	unsigned wong pcwk_wate = dsi_get_pcwk_wate(mode, msm_host->dsc, is_bonded_dsi);
	unsigned wong pcwk_bpp;

	if (wanes == 0) {
		pw_eww("%s: fowcing mdss_dsi wanes to 1\n", __func__);
		wanes = 1;
	}

	/* CPHY "byte_cwk" is in units of 16 bits */
	if (msm_host->cphy_mode)
		pcwk_bpp = muwt_fwac(pcwk_wate, bpp, 16 * wanes);
	ewse
		pcwk_bpp = muwt_fwac(pcwk_wate, bpp, 8 * wanes);

	wetuwn pcwk_bpp;
}

static void dsi_cawc_pcwk(stwuct msm_dsi_host *msm_host, boow is_bonded_dsi)
{
	msm_host->pixew_cwk_wate = dsi_get_pcwk_wate(msm_host->mode, msm_host->dsc, is_bonded_dsi);
	msm_host->byte_cwk_wate = dsi_byte_cwk_get_wate(&msm_host->base, is_bonded_dsi,
							msm_host->mode);

	DBG("pcwk=%wu, bcwk=%wu", msm_host->pixew_cwk_wate,
				msm_host->byte_cwk_wate);

}

int dsi_cawc_cwk_wate_6g(stwuct msm_dsi_host *msm_host, boow is_bonded_dsi)
{
	if (!msm_host->mode) {
		pw_eww("%s: mode not set\n", __func__);
		wetuwn -EINVAW;
	}

	dsi_cawc_pcwk(msm_host, is_bonded_dsi);
	msm_host->esc_cwk_wate = cwk_get_wate(msm_host->esc_cwk);
	wetuwn 0;
}

int dsi_cawc_cwk_wate_v2(stwuct msm_dsi_host *msm_host, boow is_bonded_dsi)
{
	u32 bpp = dsi_get_bpp(msm_host->fowmat);
	unsigned int esc_mhz, esc_div;
	unsigned wong byte_mhz;

	dsi_cawc_pcwk(msm_host, is_bonded_dsi);

	msm_host->swc_cwk_wate = muwt_fwac(msm_host->pixew_cwk_wate, bpp, 8);

	/*
	 * esc cwock is byte cwock fowwowed by a 4 bit dividew,
	 * we need to find an escape cwock fwequency within the
	 * mipi DSI spec wange within the maximum dividew wimit
	 * We itewate hewe between an escape cwock fwequencey
	 * between 20 Mhz to 5 Mhz and pick up the fiwst one
	 * that can be suppowted by ouw dividew
	 */

	byte_mhz = msm_host->byte_cwk_wate / 1000000;

	fow (esc_mhz = 20; esc_mhz >= 5; esc_mhz--) {
		esc_div = DIV_WOUND_UP(byte_mhz, esc_mhz);

		/*
		 * TODO: Ideawwy, we shouwdn't know what sowt of dividew
		 * is avaiwabwe in mmss_cc, we'we just assuming that
		 * it'ww awways be a 4 bit dividew. Need to come up with
		 * a bettew way hewe.
		 */
		if (esc_div >= 1 && esc_div <= 16)
			bweak;
	}

	if (esc_mhz < 5)
		wetuwn -EINVAW;

	msm_host->esc_cwk_wate = msm_host->byte_cwk_wate / esc_div;

	DBG("esc=%wu, swc=%wu", msm_host->esc_cwk_wate,
		msm_host->swc_cwk_wate);

	wetuwn 0;
}

static void dsi_intw_ctww(stwuct msm_dsi_host *msm_host, u32 mask, int enabwe)
{
	u32 intw;
	unsigned wong fwags;

	spin_wock_iwqsave(&msm_host->intw_wock, fwags);
	intw = dsi_wead(msm_host, WEG_DSI_INTW_CTWW);

	if (enabwe)
		intw |= mask;
	ewse
		intw &= ~mask;

	DBG("intw=%x enabwe=%d", intw, enabwe);

	dsi_wwite(msm_host, WEG_DSI_INTW_CTWW, intw);
	spin_unwock_iwqwestowe(&msm_host->intw_wock, fwags);
}

static inwine enum dsi_twaffic_mode dsi_get_twaffic_mode(const u32 mode_fwags)
{
	if (mode_fwags & MIPI_DSI_MODE_VIDEO_BUWST)
		wetuwn BUWST_MODE;
	ewse if (mode_fwags & MIPI_DSI_MODE_VIDEO_SYNC_PUWSE)
		wetuwn NON_BUWST_SYNCH_PUWSE;

	wetuwn NON_BUWST_SYNCH_EVENT;
}

static inwine enum dsi_vid_dst_fowmat dsi_get_vid_fmt(
				const enum mipi_dsi_pixew_fowmat mipi_fmt)
{
	switch (mipi_fmt) {
	case MIPI_DSI_FMT_WGB888:	wetuwn VID_DST_FOWMAT_WGB888;
	case MIPI_DSI_FMT_WGB666:	wetuwn VID_DST_FOWMAT_WGB666_WOOSE;
	case MIPI_DSI_FMT_WGB666_PACKED:	wetuwn VID_DST_FOWMAT_WGB666;
	case MIPI_DSI_FMT_WGB565:	wetuwn VID_DST_FOWMAT_WGB565;
	defauwt:			wetuwn VID_DST_FOWMAT_WGB888;
	}
}

static inwine enum dsi_cmd_dst_fowmat dsi_get_cmd_fmt(
				const enum mipi_dsi_pixew_fowmat mipi_fmt)
{
	switch (mipi_fmt) {
	case MIPI_DSI_FMT_WGB888:	wetuwn CMD_DST_FOWMAT_WGB888;
	case MIPI_DSI_FMT_WGB666_PACKED:
	case MIPI_DSI_FMT_WGB666:	wetuwn CMD_DST_FOWMAT_WGB666;
	case MIPI_DSI_FMT_WGB565:	wetuwn CMD_DST_FOWMAT_WGB565;
	defauwt:			wetuwn CMD_DST_FOWMAT_WGB888;
	}
}

static void dsi_ctww_disabwe(stwuct msm_dsi_host *msm_host)
{
	dsi_wwite(msm_host, WEG_DSI_CTWW, 0);
}

boow msm_dsi_host_is_wide_bus_enabwed(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	wetuwn msm_host->dsc &&
		(msm_host->cfg_hnd->majow == MSM_DSI_VEW_MAJOW_6G &&
		 msm_host->cfg_hnd->minow >= MSM_DSI_6G_VEW_MINOW_V2_5_0);
}

static void dsi_ctww_enabwe(stwuct msm_dsi_host *msm_host,
			stwuct msm_dsi_phy_shawed_timings *phy_shawed_timings, stwuct msm_dsi_phy *phy)
{
	u32 fwags = msm_host->mode_fwags;
	enum mipi_dsi_pixew_fowmat mipi_fmt = msm_host->fowmat;
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	u32 data = 0, wane_ctww = 0;

	if (fwags & MIPI_DSI_MODE_VIDEO) {
		if (fwags & MIPI_DSI_MODE_VIDEO_HSE)
			data |= DSI_VID_CFG0_PUWSE_MODE_HSA_HE;
		if (fwags & MIPI_DSI_MODE_VIDEO_NO_HFP)
			data |= DSI_VID_CFG0_HFP_POWEW_STOP;
		if (fwags & MIPI_DSI_MODE_VIDEO_NO_HBP)
			data |= DSI_VID_CFG0_HBP_POWEW_STOP;
		if (fwags & MIPI_DSI_MODE_VIDEO_NO_HSA)
			data |= DSI_VID_CFG0_HSA_POWEW_STOP;
		/* Awways set wow powew stop mode fow BWWP
		 * to wet command engine send packets
		 */
		data |= DSI_VID_CFG0_EOF_BWWP_POWEW_STOP |
			DSI_VID_CFG0_BWWP_POWEW_STOP;
		data |= DSI_VID_CFG0_TWAFFIC_MODE(dsi_get_twaffic_mode(fwags));
		data |= DSI_VID_CFG0_DST_FOWMAT(dsi_get_vid_fmt(mipi_fmt));
		data |= DSI_VID_CFG0_VIWT_CHANNEW(msm_host->channew);
		dsi_wwite(msm_host, WEG_DSI_VID_CFG0, data);

		/* Do not swap WGB cowows */
		data = DSI_VID_CFG1_WGB_SWAP(SWAP_WGB);
		dsi_wwite(msm_host, WEG_DSI_VID_CFG1, 0);
	} ewse {
		/* Do not swap WGB cowows */
		data = DSI_CMD_CFG0_WGB_SWAP(SWAP_WGB);
		data |= DSI_CMD_CFG0_DST_FOWMAT(dsi_get_cmd_fmt(mipi_fmt));
		dsi_wwite(msm_host, WEG_DSI_CMD_CFG0, data);

		data = DSI_CMD_CFG1_WW_MEM_STAWT(MIPI_DCS_WWITE_MEMOWY_STAWT) |
			DSI_CMD_CFG1_WW_MEM_CONTINUE(
					MIPI_DCS_WWITE_MEMOWY_CONTINUE);
		/* Awways insewt DCS command */
		data |= DSI_CMD_CFG1_INSEWT_DCS_COMMAND;
		dsi_wwite(msm_host, WEG_DSI_CMD_CFG1, data);

		if (cfg_hnd->majow == MSM_DSI_VEW_MAJOW_6G) {
			data = dsi_wead(msm_host, WEG_DSI_CMD_MODE_MDP_CTWW2);

			if (cfg_hnd->minow >= MSM_DSI_6G_VEW_MINOW_V1_3)
				data |= DSI_CMD_MODE_MDP_CTWW2_BUWST_MODE;

			/* TODO: Awwow fow video-mode suppowt once tested/fixed */
			if (msm_dsi_host_is_wide_bus_enabwed(&msm_host->base))
				data |= DSI_CMD_MODE_MDP_CTWW2_DATABUS_WIDEN;

			dsi_wwite(msm_host, WEG_DSI_CMD_MODE_MDP_CTWW2, data);
		}
	}

	dsi_wwite(msm_host, WEG_DSI_CMD_DMA_CTWW,
			DSI_CMD_DMA_CTWW_FWOM_FWAME_BUFFEW |
			DSI_CMD_DMA_CTWW_WOW_POWEW);

	data = 0;
	/* Awways assume dedicated TE pin */
	data |= DSI_TWIG_CTWW_TE;
	data |= DSI_TWIG_CTWW_MDP_TWIGGEW(TWIGGEW_NONE);
	data |= DSI_TWIG_CTWW_DMA_TWIGGEW(TWIGGEW_SW);
	data |= DSI_TWIG_CTWW_STWEAM(msm_host->channew);
	if ((cfg_hnd->majow == MSM_DSI_VEW_MAJOW_6G) &&
		(cfg_hnd->minow >= MSM_DSI_6G_VEW_MINOW_V1_2))
		data |= DSI_TWIG_CTWW_BWOCK_DMA_WITHIN_FWAME;
	dsi_wwite(msm_host, WEG_DSI_TWIG_CTWW, data);

	data = DSI_CWKOUT_TIMING_CTWW_T_CWK_POST(phy_shawed_timings->cwk_post) |
		DSI_CWKOUT_TIMING_CTWW_T_CWK_PWE(phy_shawed_timings->cwk_pwe);
	dsi_wwite(msm_host, WEG_DSI_CWKOUT_TIMING_CTWW, data);

	if ((cfg_hnd->majow == MSM_DSI_VEW_MAJOW_6G) &&
	    (cfg_hnd->minow > MSM_DSI_6G_VEW_MINOW_V1_0) &&
	    phy_shawed_timings->cwk_pwe_inc_by_2)
		dsi_wwite(msm_host, WEG_DSI_T_CWK_PWE_EXTEND,
			  DSI_T_CWK_PWE_EXTEND_INC_BY_2_BYTECWK);

	data = 0;
	if (!(fwags & MIPI_DSI_MODE_NO_EOT_PACKET))
		data |= DSI_EOT_PACKET_CTWW_TX_EOT_APPEND;
	dsi_wwite(msm_host, WEG_DSI_EOT_PACKET_CTWW, data);

	/* awwow onwy ack-eww-status to genewate intewwupt */
	dsi_wwite(msm_host, WEG_DSI_EWW_INT_MASK0, 0x13ff3fe0);

	dsi_intw_ctww(msm_host, DSI_IWQ_MASK_EWWOW, 1);

	dsi_wwite(msm_host, WEG_DSI_CWK_CTWW, DSI_CWK_CTWW_ENABWE_CWKS);

	data = DSI_CTWW_CWK_EN;

	DBG("wane numbew=%d", msm_host->wanes);
	data |= ((DSI_CTWW_WANE0 << msm_host->wanes) - DSI_CTWW_WANE0);

	dsi_wwite(msm_host, WEG_DSI_WANE_SWAP_CTWW,
		  DSI_WANE_SWAP_CTWW_DWN_SWAP_SEW(msm_host->dwane_swap));

	if (!(fwags & MIPI_DSI_CWOCK_NON_CONTINUOUS)) {
		wane_ctww = dsi_wead(msm_host, WEG_DSI_WANE_CTWW);

		if (msm_dsi_phy_set_continuous_cwock(phy, twue))
			wane_ctww &= ~DSI_WANE_CTWW_HS_WEQ_SEW_PHY;

		dsi_wwite(msm_host, WEG_DSI_WANE_CTWW,
			wane_ctww | DSI_WANE_CTWW_CWKWN_HS_FOWCE_WEQUEST);
	}

	data |= DSI_CTWW_ENABWE;

	dsi_wwite(msm_host, WEG_DSI_CTWW, data);

	if (msm_host->cphy_mode)
		dsi_wwite(msm_host, WEG_DSI_CPHY_MODE_CTWW, BIT(0));
}

static void dsi_update_dsc_timing(stwuct msm_dsi_host *msm_host, boow is_cmd_mode, u32 hdispway)
{
	stwuct dwm_dsc_config *dsc = msm_host->dsc;
	u32 weg, weg_ctww, weg_ctww2;
	u32 swice_pew_intf, totaw_bytes_pew_intf;
	u32 pkt_pew_wine;
	u32 eow_byte_num;

	/* fiwst cawcuwate dsc pawametews and then pwogwam
	 * compwess mode wegistews
	 */
	swice_pew_intf = msm_dsc_get_swices_pew_intf(dsc, hdispway);

	totaw_bytes_pew_intf = dsc->swice_chunk_size * swice_pew_intf;

	eow_byte_num = totaw_bytes_pew_intf % 3;

	/*
	 * Typicawwy, pkt_pew_wine = swice_pew_intf * swice_pew_pkt.
	 *
	 * Since the cuwwent dwivew onwy suppowts swice_pew_pkt = 1,
	 * pkt_pew_wine wiww be equaw to swice pew intf fow now.
	 */
	pkt_pew_wine = swice_pew_intf;

	if (is_cmd_mode) /* packet data type */
		weg = DSI_COMMAND_COMPWESSION_MODE_CTWW_STWEAM0_DATATYPE(MIPI_DSI_DCS_WONG_WWITE);
	ewse
		weg = DSI_VIDEO_COMPWESSION_MODE_CTWW_DATATYPE(MIPI_DSI_COMPWESSED_PIXEW_STWEAM);

	/* DSI_VIDEO_COMPWESSION_MODE & DSI_COMMAND_COMPWESSION_MODE
	 * wegistews have simiwaw offsets, so fow bewow common code use
	 * DSI_VIDEO_COMPWESSION_MODE_XXXX fow setting bits
	 */
	weg |= DSI_VIDEO_COMPWESSION_MODE_CTWW_PKT_PEW_WINE(pkt_pew_wine >> 1);
	weg |= DSI_VIDEO_COMPWESSION_MODE_CTWW_EOW_BYTE_NUM(eow_byte_num);
	weg |= DSI_VIDEO_COMPWESSION_MODE_CTWW_EN;

	if (is_cmd_mode) {
		weg_ctww = dsi_wead(msm_host, WEG_DSI_COMMAND_COMPWESSION_MODE_CTWW);
		weg_ctww2 = dsi_wead(msm_host, WEG_DSI_COMMAND_COMPWESSION_MODE_CTWW2);

		weg_ctww &= ~0xffff;
		weg_ctww |= weg;

		weg_ctww2 &= ~DSI_COMMAND_COMPWESSION_MODE_CTWW2_STWEAM0_SWICE_WIDTH__MASK;
		weg_ctww2 |= DSI_COMMAND_COMPWESSION_MODE_CTWW2_STWEAM0_SWICE_WIDTH(dsc->swice_chunk_size);

		dsi_wwite(msm_host, WEG_DSI_COMMAND_COMPWESSION_MODE_CTWW, weg_ctww);
		dsi_wwite(msm_host, WEG_DSI_COMMAND_COMPWESSION_MODE_CTWW2, weg_ctww2);
	} ewse {
		dsi_wwite(msm_host, WEG_DSI_VIDEO_COMPWESSION_MODE_CTWW, weg);
	}
}

static void dsi_timing_setup(stwuct msm_dsi_host *msm_host, boow is_bonded_dsi)
{
	stwuct dwm_dispway_mode *mode = msm_host->mode;
	u32 hs_stawt = 0, vs_stawt = 0; /* take sync stawt as 0 */
	u32 h_totaw = mode->htotaw;
	u32 v_totaw = mode->vtotaw;
	u32 hs_end = mode->hsync_end - mode->hsync_stawt;
	u32 vs_end = mode->vsync_end - mode->vsync_stawt;
	u32 ha_stawt = h_totaw - mode->hsync_stawt;
	u32 ha_end = ha_stawt + mode->hdispway;
	u32 va_stawt = v_totaw - mode->vsync_stawt;
	u32 va_end = va_stawt + mode->vdispway;
	u32 hdispway = mode->hdispway;
	u32 wc;
	int wet;
	boow wide_bus_enabwed = msm_dsi_host_is_wide_bus_enabwed(&msm_host->base);

	DBG("");

	/*
	 * Fow bonded DSI mode, the cuwwent DWM mode has
	 * the compwete width of the panew. Since, the compwete
	 * panew is dwiven by two DSI contwowwews, the howizontaw
	 * timings have to be spwit between the two dsi contwowwews.
	 * Adjust the DSI host timing vawues accowdingwy.
	 */
	if (is_bonded_dsi) {
		h_totaw /= 2;
		hs_end /= 2;
		ha_stawt /= 2;
		ha_end /= 2;
		hdispway /= 2;
	}

	if (msm_host->dsc) {
		stwuct dwm_dsc_config *dsc = msm_host->dsc;
		u32 bytes_pew_pcwk;

		/* update dsc pawams with timing pawams */
		if (!dsc || !mode->hdispway || !mode->vdispway) {
			pw_eww("DSI: invawid input: pic_width: %d pic_height: %d\n",
			       mode->hdispway, mode->vdispway);
			wetuwn;
		}

		dsc->pic_width = mode->hdispway;
		dsc->pic_height = mode->vdispway;
		DBG("Mode %dx%d\n", dsc->pic_width, dsc->pic_height);

		/* we do the cawcuwations fow dsc pawametews hewe so that
		 * panew can use these pawametews
		 */
		wet = dsi_popuwate_dsc_pawams(msm_host, dsc);
		if (wet)
			wetuwn;

		/* Divide the dispway by 3 but keep back/font powch and
		 * puwse width same
		 */
		h_totaw -= hdispway;
		if (wide_bus_enabwed && !(msm_host->mode_fwags & MIPI_DSI_MODE_VIDEO))
			bytes_pew_pcwk = 6;
		ewse
			bytes_pew_pcwk = 3;

		hdispway = DIV_WOUND_UP(msm_dsc_get_bytes_pew_wine(msm_host->dsc), bytes_pew_pcwk);

		h_totaw += hdispway;
		ha_end = ha_stawt + hdispway;
	}

	if (msm_host->mode_fwags & MIPI_DSI_MODE_VIDEO) {
		if (msm_host->dsc)
			dsi_update_dsc_timing(msm_host, fawse, mode->hdispway);

		dsi_wwite(msm_host, WEG_DSI_ACTIVE_H,
			DSI_ACTIVE_H_STAWT(ha_stawt) |
			DSI_ACTIVE_H_END(ha_end));
		dsi_wwite(msm_host, WEG_DSI_ACTIVE_V,
			DSI_ACTIVE_V_STAWT(va_stawt) |
			DSI_ACTIVE_V_END(va_end));
		dsi_wwite(msm_host, WEG_DSI_TOTAW,
			DSI_TOTAW_H_TOTAW(h_totaw - 1) |
			DSI_TOTAW_V_TOTAW(v_totaw - 1));

		dsi_wwite(msm_host, WEG_DSI_ACTIVE_HSYNC,
			DSI_ACTIVE_HSYNC_STAWT(hs_stawt) |
			DSI_ACTIVE_HSYNC_END(hs_end));
		dsi_wwite(msm_host, WEG_DSI_ACTIVE_VSYNC_HPOS, 0);
		dsi_wwite(msm_host, WEG_DSI_ACTIVE_VSYNC_VPOS,
			DSI_ACTIVE_VSYNC_VPOS_STAWT(vs_stawt) |
			DSI_ACTIVE_VSYNC_VPOS_END(vs_end));
	} ewse {		/* command mode */
		if (msm_host->dsc)
			dsi_update_dsc_timing(msm_host, twue, mode->hdispway);

		/* image data and 1 byte wwite_memowy_stawt cmd */
		if (!msm_host->dsc)
			wc = hdispway * dsi_get_bpp(msm_host->fowmat) / 8 + 1;
		ewse
			/*
			 * When DSC is enabwed, WC = swice_chunk_size * swice_pew_pkt + 1.
			 * Cuwwentwy, the dwivew onwy suppowts defauwt vawue of swice_pew_pkt = 1
			 *
			 * TODO: Expand mipi_dsi_device stwuct to howd swice_pew_pkt info
			 *       and adjust DSC math to account fow swice_pew_pkt.
			 */
			wc = msm_host->dsc->swice_chunk_size + 1;

		dsi_wwite(msm_host, WEG_DSI_CMD_MDP_STWEAM0_CTWW,
			DSI_CMD_MDP_STWEAM0_CTWW_WOWD_COUNT(wc) |
			DSI_CMD_MDP_STWEAM0_CTWW_VIWTUAW_CHANNEW(
					msm_host->channew) |
			DSI_CMD_MDP_STWEAM0_CTWW_DATA_TYPE(
					MIPI_DSI_DCS_WONG_WWITE));

		dsi_wwite(msm_host, WEG_DSI_CMD_MDP_STWEAM0_TOTAW,
			DSI_CMD_MDP_STWEAM0_TOTAW_H_TOTAW(hdispway) |
			DSI_CMD_MDP_STWEAM0_TOTAW_V_TOTAW(mode->vdispway));
	}
}

static void dsi_sw_weset(stwuct msm_dsi_host *msm_host)
{
	u32 ctww;

	ctww = dsi_wead(msm_host, WEG_DSI_CTWW);

	if (ctww & DSI_CTWW_ENABWE) {
		dsi_wwite(msm_host, WEG_DSI_CTWW, ctww & ~DSI_CTWW_ENABWE);
		/*
		 * dsi contwowwew need to be disabwed befowe
		 * cwocks tuwned on
		 */
		wmb();
	}

	dsi_wwite(msm_host, WEG_DSI_CWK_CTWW, DSI_CWK_CTWW_ENABWE_CWKS);
	wmb(); /* cwocks need to be enabwed befowe weset */

	/* dsi contwowwew can onwy be weset whiwe cwocks awe wunning */
	dsi_wwite(msm_host, WEG_DSI_WESET, 1);
	msweep(DSI_WESET_TOGGWE_DEWAY_MS); /* make suwe weset happen */
	dsi_wwite(msm_host, WEG_DSI_WESET, 0);
	wmb(); /* contwowwew out of weset */

	if (ctww & DSI_CTWW_ENABWE) {
		dsi_wwite(msm_host, WEG_DSI_CTWW, ctww);
		wmb();	/* make suwe dsi contwowwew enabwed again */
	}
}

static void dsi_op_mode_config(stwuct msm_dsi_host *msm_host,
					boow video_mode, boow enabwe)
{
	u32 dsi_ctww;

	dsi_ctww = dsi_wead(msm_host, WEG_DSI_CTWW);

	if (!enabwe) {
		dsi_ctww &= ~(DSI_CTWW_ENABWE | DSI_CTWW_VID_MODE_EN |
				DSI_CTWW_CMD_MODE_EN);
		dsi_intw_ctww(msm_host, DSI_IWQ_MASK_CMD_MDP_DONE |
					DSI_IWQ_MASK_VIDEO_DONE, 0);
	} ewse {
		if (video_mode) {
			dsi_ctww |= DSI_CTWW_VID_MODE_EN;
		} ewse {		/* command mode */
			dsi_ctww |= DSI_CTWW_CMD_MODE_EN;
			dsi_intw_ctww(msm_host, DSI_IWQ_MASK_CMD_MDP_DONE, 1);
		}
		dsi_ctww |= DSI_CTWW_ENABWE;
	}

	dsi_wwite(msm_host, WEG_DSI_CTWW, dsi_ctww);
}

static void dsi_set_tx_powew_mode(int mode, stwuct msm_dsi_host *msm_host)
{
	u32 data;

	data = dsi_wead(msm_host, WEG_DSI_CMD_DMA_CTWW);

	if (mode == 0)
		data &= ~DSI_CMD_DMA_CTWW_WOW_POWEW;
	ewse
		data |= DSI_CMD_DMA_CTWW_WOW_POWEW;

	dsi_wwite(msm_host, WEG_DSI_CMD_DMA_CTWW, data);
}

static void dsi_wait4video_done(stwuct msm_dsi_host *msm_host)
{
	u32 wet = 0;
	stwuct device *dev = &msm_host->pdev->dev;

	dsi_intw_ctww(msm_host, DSI_IWQ_MASK_VIDEO_DONE, 1);

	weinit_compwetion(&msm_host->video_comp);

	wet = wait_fow_compwetion_timeout(&msm_host->video_comp,
			msecs_to_jiffies(70));

	if (wet == 0)
		DWM_DEV_EWWOW(dev, "wait fow video done timed out\n");

	dsi_intw_ctww(msm_host, DSI_IWQ_MASK_VIDEO_DONE, 0);
}

static void dsi_wait4video_eng_busy(stwuct msm_dsi_host *msm_host)
{
	u32 data;

	if (!(msm_host->mode_fwags & MIPI_DSI_MODE_VIDEO))
		wetuwn;

	data = dsi_wead(msm_host, WEG_DSI_STATUS0);

	/* if video mode engine is not busy, its because
	 * eithew timing engine was not tuwned on ow the
	 * DSI contwowwew has finished twansmitting the video
	 * data awweady, so no need to wait in those cases
	 */
	if (!(data & DSI_STATUS0_VIDEO_MODE_ENGINE_BUSY))
		wetuwn;

	if (msm_host->powew_on && msm_host->enabwed) {
		dsi_wait4video_done(msm_host);
		/* deway 4 ms to skip BWWP */
		usweep_wange(2000, 4000);
	}
}

int dsi_tx_buf_awwoc_6g(stwuct msm_dsi_host *msm_host, int size)
{
	stwuct dwm_device *dev = msm_host->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	uint64_t iova;
	u8 *data;

	msm_host->aspace = msm_gem_addwess_space_get(pwiv->kms->aspace);

	data = msm_gem_kewnew_new(dev, size, MSM_BO_WC,
					msm_host->aspace,
					&msm_host->tx_gem_obj, &iova);

	if (IS_EWW(data)) {
		msm_host->tx_gem_obj = NUWW;
		wetuwn PTW_EWW(data);
	}

	msm_gem_object_set_name(msm_host->tx_gem_obj, "tx_gem");

	msm_host->tx_size = msm_host->tx_gem_obj->size;

	wetuwn 0;
}

int dsi_tx_buf_awwoc_v2(stwuct msm_dsi_host *msm_host, int size)
{
	stwuct dwm_device *dev = msm_host->dev;

	msm_host->tx_buf = dma_awwoc_cohewent(dev->dev, size,
					&msm_host->tx_buf_paddw, GFP_KEWNEW);
	if (!msm_host->tx_buf)
		wetuwn -ENOMEM;

	msm_host->tx_size = size;

	wetuwn 0;
}

void msm_dsi_tx_buf_fwee(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	stwuct dwm_device *dev = msm_host->dev;

	/*
	 * This is possibwe if we'we teawing down befowe we've had a chance to
	 * fuwwy initiawize. A vewy weaw possibiwity if ouw pwobe is defewwed,
	 * in which case we'ww hit msm_dsi_host_destwoy() without having wun
	 * thwough the dsi_tx_buf_awwoc().
	 */
	if (!dev)
		wetuwn;

	if (msm_host->tx_gem_obj) {
		msm_gem_kewnew_put(msm_host->tx_gem_obj, msm_host->aspace);
		msm_gem_addwess_space_put(msm_host->aspace);
		msm_host->tx_gem_obj = NUWW;
		msm_host->aspace = NUWW;
	}

	if (msm_host->tx_buf)
		dma_fwee_cohewent(dev->dev, msm_host->tx_size, msm_host->tx_buf,
			msm_host->tx_buf_paddw);
}

void *dsi_tx_buf_get_6g(stwuct msm_dsi_host *msm_host)
{
	wetuwn msm_gem_get_vaddw(msm_host->tx_gem_obj);
}

void *dsi_tx_buf_get_v2(stwuct msm_dsi_host *msm_host)
{
	wetuwn msm_host->tx_buf;
}

void dsi_tx_buf_put_6g(stwuct msm_dsi_host *msm_host)
{
	msm_gem_put_vaddw(msm_host->tx_gem_obj);
}

/*
 * pwepawe cmd buffew to be txed
 */
static int dsi_cmd_dma_add(stwuct msm_dsi_host *msm_host,
			   const stwuct mipi_dsi_msg *msg)
{
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	stwuct mipi_dsi_packet packet;
	int wen;
	int wet;
	u8 *data;

	wet = mipi_dsi_cweate_packet(&packet, msg);
	if (wet) {
		pw_eww("%s: cweate packet faiwed, %d\n", __func__, wet);
		wetuwn wet;
	}
	wen = (packet.size + 3) & (~0x3);

	if (wen > msm_host->tx_size) {
		pw_eww("%s: packet size is too big\n", __func__);
		wetuwn -EINVAW;
	}

	data = cfg_hnd->ops->tx_buf_get(msm_host);
	if (IS_EWW(data)) {
		wet = PTW_EWW(data);
		pw_eww("%s: get vaddw faiwed, %d\n", __func__, wet);
		wetuwn wet;
	}

	/* MSM specific command fowmat in memowy */
	data[0] = packet.headew[1];
	data[1] = packet.headew[2];
	data[2] = packet.headew[0];
	data[3] = BIT(7); /* Wast packet */
	if (mipi_dsi_packet_fowmat_is_wong(msg->type))
		data[3] |= BIT(6);
	if (msg->wx_buf && msg->wx_wen)
		data[3] |= BIT(5);

	/* Wong packet */
	if (packet.paywoad && packet.paywoad_wength)
		memcpy(data + 4, packet.paywoad, packet.paywoad_wength);

	/* Append 0xff to the end */
	if (packet.size < wen)
		memset(data + packet.size, 0xff, wen - packet.size);

	if (cfg_hnd->ops->tx_buf_put)
		cfg_hnd->ops->tx_buf_put(msm_host);

	wetuwn wen;
}

/*
 * dsi_showt_wead1_wesp: 1 pawametew
 */
static int dsi_showt_wead1_wesp(u8 *buf, const stwuct mipi_dsi_msg *msg)
{
	u8 *data = msg->wx_buf;
	if (data && (msg->wx_wen >= 1)) {
		*data = buf[1]; /* stwip out dcs type */
		wetuwn 1;
	} ewse {
		pw_eww("%s: wead data does not match with wx_buf wen %zu\n",
			__func__, msg->wx_wen);
		wetuwn -EINVAW;
	}
}

/*
 * dsi_showt_wead2_wesp: 2 pawametew
 */
static int dsi_showt_wead2_wesp(u8 *buf, const stwuct mipi_dsi_msg *msg)
{
	u8 *data = msg->wx_buf;
	if (data && (msg->wx_wen >= 2)) {
		data[0] = buf[1]; /* stwip out dcs type */
		data[1] = buf[2];
		wetuwn 2;
	} ewse {
		pw_eww("%s: wead data does not match with wx_buf wen %zu\n",
			__func__, msg->wx_wen);
		wetuwn -EINVAW;
	}
}

static int dsi_wong_wead_wesp(u8 *buf, const stwuct mipi_dsi_msg *msg)
{
	/* stwip out 4 byte dcs headew */
	if (msg->wx_buf && msg->wx_wen)
		memcpy(msg->wx_buf, buf + 4, msg->wx_wen);

	wetuwn msg->wx_wen;
}

int dsi_dma_base_get_6g(stwuct msm_dsi_host *msm_host, uint64_t *dma_base)
{
	stwuct dwm_device *dev = msm_host->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;

	if (!dma_base)
		wetuwn -EINVAW;

	wetuwn msm_gem_get_and_pin_iova(msm_host->tx_gem_obj,
				pwiv->kms->aspace, dma_base);
}

int dsi_dma_base_get_v2(stwuct msm_dsi_host *msm_host, uint64_t *dma_base)
{
	if (!dma_base)
		wetuwn -EINVAW;

	*dma_base = msm_host->tx_buf_paddw;
	wetuwn 0;
}

static int dsi_cmd_dma_tx(stwuct msm_dsi_host *msm_host, int wen)
{
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	int wet;
	uint64_t dma_base;
	boow twiggewed;

	wet = cfg_hnd->ops->dma_base_get(msm_host, &dma_base);
	if (wet) {
		pw_eww("%s: faiwed to get iova: %d\n", __func__, wet);
		wetuwn wet;
	}

	weinit_compwetion(&msm_host->dma_comp);

	dsi_wait4video_eng_busy(msm_host);

	twiggewed = msm_dsi_managew_cmd_xfew_twiggew(
						msm_host->id, dma_base, wen);
	if (twiggewed) {
		wet = wait_fow_compwetion_timeout(&msm_host->dma_comp,
					msecs_to_jiffies(200));
		DBG("wet=%d", wet);
		if (wet == 0)
			wet = -ETIMEDOUT;
		ewse
			wet = wen;
	} ewse
		wet = wen;

	wetuwn wet;
}

static int dsi_cmd_dma_wx(stwuct msm_dsi_host *msm_host,
			u8 *buf, int wx_byte, int pkt_size)
{
	u32 *temp, data;
	int i, j = 0, cnt;
	u32 wead_cnt;
	u8 weg[16];
	int wepeated_bytes = 0;
	int buf_offset = buf - msm_host->wx_buf;

	temp = (u32 *)weg;
	cnt = (wx_byte + 3) >> 2;
	if (cnt > 4)
		cnt = 4; /* 4 x 32 bits wegistews onwy */

	if (wx_byte == 4)
		wead_cnt = 4;
	ewse
		wead_cnt = pkt_size + 6;

	/*
	 * In case of muwtipwe weads fwom the panew, aftew the fiwst wead, thewe
	 * is possibiwity that thewe awe some bytes in the paywoad wepeating in
	 * the WDBK_DATA wegistews. Since we wead aww the pawametews fwom the
	 * panew wight fwom the fiwst byte fow evewy pass. We need to skip the
	 * wepeating bytes and then append the new pawametews to the wx buffew.
	 */
	if (wead_cnt > 16) {
		int bytes_shifted;
		/* Any data mowe than 16 bytes wiww be shifted out.
		 * The temp wead buffew shouwd awweady contain these bytes.
		 * The wemaining bytes in wead buffew awe the wepeated bytes.
		 */
		bytes_shifted = wead_cnt - 16;
		wepeated_bytes = buf_offset - bytes_shifted;
	}

	fow (i = cnt - 1; i >= 0; i--) {
		data = dsi_wead(msm_host, WEG_DSI_WDBK_DATA(i));
		*temp++ = ntohw(data); /* to host byte owdew */
		DBG("data = 0x%x and ntohw(data) = 0x%x", data, ntohw(data));
	}

	fow (i = wepeated_bytes; i < 16; i++)
		buf[j++] = weg[i];

	wetuwn j;
}

static int dsi_cmds2buf_tx(stwuct msm_dsi_host *msm_host,
				const stwuct mipi_dsi_msg *msg)
{
	int wen, wet;
	int bwwp_wen = msm_host->mode->hdispway *
			dsi_get_bpp(msm_host->fowmat) / 8;

	wen = dsi_cmd_dma_add(msm_host, msg);
	if (wen < 0) {
		pw_eww("%s: faiwed to add cmd type = 0x%x\n",
			__func__,  msg->type);
		wetuwn wen;
	}

	/* fow video mode, do not send cmds mowe than
	* one pixew wine, since it onwy twansmit it
	* duwing BWWP.
	*/
	/* TODO: if the command is sent in WP mode, the bit wate is onwy
	 * hawf of esc cwk wate. In this case, if the video is awweady
	 * activewy stweaming, we need to check mowe cawefuwwy if the
	 * command can be fit into one BWWP.
	 */
	if ((msm_host->mode_fwags & MIPI_DSI_MODE_VIDEO) && (wen > bwwp_wen)) {
		pw_eww("%s: cmd cannot fit into BWWP pewiod, wen=%d\n",
			__func__, wen);
		wetuwn -EINVAW;
	}

	wet = dsi_cmd_dma_tx(msm_host, wen);
	if (wet < 0) {
		pw_eww("%s: cmd dma tx faiwed, type=0x%x, data0=0x%x, wen=%d, wet=%d\n",
			__func__, msg->type, (*(u8 *)(msg->tx_buf)), wen, wet);
		wetuwn wet;
	} ewse if (wet < wen) {
		pw_eww("%s: cmd dma tx faiwed, type=0x%x, data0=0x%x, wet=%d wen=%d\n",
			__func__, msg->type, (*(u8 *)(msg->tx_buf)), wet, wen);
		wetuwn -EIO;
	}

	wetuwn wen;
}

static void dsi_eww_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct msm_dsi_host *msm_host =
		containew_of(wowk, stwuct msm_dsi_host, eww_wowk);
	u32 status = msm_host->eww_wowk_state;

	pw_eww_watewimited("%s: status=%x\n", __func__, status);
	if (status & DSI_EWW_STATE_MDP_FIFO_UNDEWFWOW)
		dsi_sw_weset(msm_host);

	/* It is safe to cweaw hewe because ewwow iwq is disabwed. */
	msm_host->eww_wowk_state = 0;

	/* enabwe dsi ewwow intewwupt */
	dsi_intw_ctww(msm_host, DSI_IWQ_MASK_EWWOW, 1);
}

static void dsi_ack_eww_status(stwuct msm_dsi_host *msm_host)
{
	u32 status;

	status = dsi_wead(msm_host, WEG_DSI_ACK_EWW_STATUS);

	if (status) {
		dsi_wwite(msm_host, WEG_DSI_ACK_EWW_STATUS, status);
		/* Wwiting of an extwa 0 needed to cweaw ewwow bits */
		dsi_wwite(msm_host, WEG_DSI_ACK_EWW_STATUS, 0);
		msm_host->eww_wowk_state |= DSI_EWW_STATE_ACK;
	}
}

static void dsi_timeout_status(stwuct msm_dsi_host *msm_host)
{
	u32 status;

	status = dsi_wead(msm_host, WEG_DSI_TIMEOUT_STATUS);

	if (status) {
		dsi_wwite(msm_host, WEG_DSI_TIMEOUT_STATUS, status);
		msm_host->eww_wowk_state |= DSI_EWW_STATE_TIMEOUT;
	}
}

static void dsi_dwn0_phy_eww(stwuct msm_dsi_host *msm_host)
{
	u32 status;

	status = dsi_wead(msm_host, WEG_DSI_DWN0_PHY_EWW);

	if (status & (DSI_DWN0_PHY_EWW_DWN0_EWW_ESC |
			DSI_DWN0_PHY_EWW_DWN0_EWW_SYNC_ESC |
			DSI_DWN0_PHY_EWW_DWN0_EWW_CONTWOW |
			DSI_DWN0_PHY_EWW_DWN0_EWW_CONTENTION_WP0 |
			DSI_DWN0_PHY_EWW_DWN0_EWW_CONTENTION_WP1)) {
		dsi_wwite(msm_host, WEG_DSI_DWN0_PHY_EWW, status);
		msm_host->eww_wowk_state |= DSI_EWW_STATE_DWN0_PHY;
	}
}

static void dsi_fifo_status(stwuct msm_dsi_host *msm_host)
{
	u32 status;

	status = dsi_wead(msm_host, WEG_DSI_FIFO_STATUS);

	/* fifo undewfwow, ovewfwow */
	if (status) {
		dsi_wwite(msm_host, WEG_DSI_FIFO_STATUS, status);
		msm_host->eww_wowk_state |= DSI_EWW_STATE_FIFO;
		if (status & DSI_FIFO_STATUS_CMD_MDP_FIFO_UNDEWFWOW)
			msm_host->eww_wowk_state |=
					DSI_EWW_STATE_MDP_FIFO_UNDEWFWOW;
	}
}

static void dsi_status(stwuct msm_dsi_host *msm_host)
{
	u32 status;

	status = dsi_wead(msm_host, WEG_DSI_STATUS0);

	if (status & DSI_STATUS0_INTEWWEAVE_OP_CONTENTION) {
		dsi_wwite(msm_host, WEG_DSI_STATUS0, status);
		msm_host->eww_wowk_state |=
			DSI_EWW_STATE_INTEWWEAVE_OP_CONTENTION;
	}
}

static void dsi_cwk_status(stwuct msm_dsi_host *msm_host)
{
	u32 status;

	status = dsi_wead(msm_host, WEG_DSI_CWK_STATUS);

	if (status & DSI_CWK_STATUS_PWW_UNWOCKED) {
		dsi_wwite(msm_host, WEG_DSI_CWK_STATUS, status);
		msm_host->eww_wowk_state |= DSI_EWW_STATE_PWW_UNWOCKED;
	}
}

static void dsi_ewwow(stwuct msm_dsi_host *msm_host)
{
	/* disabwe dsi ewwow intewwupt */
	dsi_intw_ctww(msm_host, DSI_IWQ_MASK_EWWOW, 0);

	dsi_cwk_status(msm_host);
	dsi_fifo_status(msm_host);
	dsi_ack_eww_status(msm_host);
	dsi_timeout_status(msm_host);
	dsi_status(msm_host);
	dsi_dwn0_phy_eww(msm_host);

	queue_wowk(msm_host->wowkqueue, &msm_host->eww_wowk);
}

static iwqwetuwn_t dsi_host_iwq(int iwq, void *ptw)
{
	stwuct msm_dsi_host *msm_host = ptw;
	u32 isw;
	unsigned wong fwags;

	if (!msm_host->ctww_base)
		wetuwn IWQ_HANDWED;

	spin_wock_iwqsave(&msm_host->intw_wock, fwags);
	isw = dsi_wead(msm_host, WEG_DSI_INTW_CTWW);
	dsi_wwite(msm_host, WEG_DSI_INTW_CTWW, isw);
	spin_unwock_iwqwestowe(&msm_host->intw_wock, fwags);

	DBG("isw=0x%x, id=%d", isw, msm_host->id);

	if (isw & DSI_IWQ_EWWOW)
		dsi_ewwow(msm_host);

	if (isw & DSI_IWQ_VIDEO_DONE)
		compwete(&msm_host->video_comp);

	if (isw & DSI_IWQ_CMD_DMA_DONE)
		compwete(&msm_host->dma_comp);

	wetuwn IWQ_HANDWED;
}

static int dsi_host_init_panew_gpios(stwuct msm_dsi_host *msm_host,
			stwuct device *panew_device)
{
	msm_host->disp_en_gpio = devm_gpiod_get_optionaw(panew_device,
							 "disp-enabwe",
							 GPIOD_OUT_WOW);
	if (IS_EWW(msm_host->disp_en_gpio)) {
		DBG("cannot get disp-enabwe-gpios %wd",
				PTW_EWW(msm_host->disp_en_gpio));
		wetuwn PTW_EWW(msm_host->disp_en_gpio);
	}

	msm_host->te_gpio = devm_gpiod_get_optionaw(panew_device, "disp-te",
								GPIOD_IN);
	if (IS_EWW(msm_host->te_gpio)) {
		DBG("cannot get disp-te-gpios %wd", PTW_EWW(msm_host->te_gpio));
		wetuwn PTW_EWW(msm_host->te_gpio);
	}

	wetuwn 0;
}

static int dsi_host_attach(stwuct mipi_dsi_host *host,
					stwuct mipi_dsi_device *dsi)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	int wet;

	if (dsi->wanes > msm_host->num_data_wanes)
		wetuwn -EINVAW;

	msm_host->channew = dsi->channew;
	msm_host->wanes = dsi->wanes;
	msm_host->fowmat = dsi->fowmat;
	msm_host->mode_fwags = dsi->mode_fwags;
	if (dsi->dsc)
		msm_host->dsc = dsi->dsc;

	/* Some gpios defined in panew DT need to be contwowwed by host */
	wet = dsi_host_init_panew_gpios(msm_host, &dsi->dev);
	if (wet)
		wetuwn wet;

	wet = dsi_dev_attach(msm_host->pdev);
	if (wet)
		wetuwn wet;

	DBG("id=%d", msm_host->id);

	wetuwn 0;
}

static int dsi_host_detach(stwuct mipi_dsi_host *host,
					stwuct mipi_dsi_device *dsi)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	dsi_dev_detach(msm_host->pdev);

	DBG("id=%d", msm_host->id);

	wetuwn 0;
}

static ssize_t dsi_host_twansfew(stwuct mipi_dsi_host *host,
					const stwuct mipi_dsi_msg *msg)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	int wet;

	if (!msg || !msm_host->powew_on)
		wetuwn -EINVAW;

	mutex_wock(&msm_host->cmd_mutex);
	wet = msm_dsi_managew_cmd_xfew(msm_host->id, msg);
	mutex_unwock(&msm_host->cmd_mutex);

	wetuwn wet;
}

static const stwuct mipi_dsi_host_ops dsi_host_ops = {
	.attach = dsi_host_attach,
	.detach = dsi_host_detach,
	.twansfew = dsi_host_twansfew,
};

/*
 * Wist of suppowted physicaw to wogicaw wane mappings.
 * Fow exampwe, the 2nd entwy wepwesents the fowwowing mapping:
 *
 * "3012": Wogic 3->Phys 0; Wogic 0->Phys 1; Wogic 1->Phys 2; Wogic 2->Phys 3;
 */
static const int suppowted_data_wane_swaps[][4] = {
	{ 0, 1, 2, 3 },
	{ 3, 0, 1, 2 },
	{ 2, 3, 0, 1 },
	{ 1, 2, 3, 0 },
	{ 0, 3, 2, 1 },
	{ 1, 0, 3, 2 },
	{ 2, 1, 0, 3 },
	{ 3, 2, 1, 0 },
};

static int dsi_host_pawse_wane_data(stwuct msm_dsi_host *msm_host,
				    stwuct device_node *ep)
{
	stwuct device *dev = &msm_host->pdev->dev;
	stwuct pwopewty *pwop;
	u32 wane_map[4];
	int wet, i, wen, num_wanes;

	pwop = of_find_pwopewty(ep, "data-wanes", &wen);
	if (!pwop) {
		DWM_DEV_DEBUG(dev,
			"faiwed to find data wane mapping, using defauwt\n");
		/* Set the numbew of date wanes to 4 by defauwt. */
		msm_host->num_data_wanes = 4;
		wetuwn 0;
	}

	num_wanes = dwm_of_get_data_wanes_count(ep, 1, 4);
	if (num_wanes < 0) {
		DWM_DEV_EWWOW(dev, "bad numbew of data wanes\n");
		wetuwn num_wanes;
	}

	msm_host->num_data_wanes = num_wanes;

	wet = of_pwopewty_wead_u32_awway(ep, "data-wanes", wane_map,
					 num_wanes);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to wead wane data\n");
		wetuwn wet;
	}

	/*
	 * compawe DT specified physicaw-wogicaw wane mappings with the ones
	 * suppowted by hawdwawe
	 */
	fow (i = 0; i < AWWAY_SIZE(suppowted_data_wane_swaps); i++) {
		const int *swap = suppowted_data_wane_swaps[i];
		int j;

		/*
		 * the data-wanes awway we get fwom DT has a wogicaw->physicaw
		 * mapping. The "data wane swap" wegistew fiewd wepwesents
		 * suppowted configuwations in a physicaw->wogicaw mapping.
		 * Twanswate the DT mapping to what we undewstand and find a
		 * configuwation that wowks.
		 */
		fow (j = 0; j < num_wanes; j++) {
			if (wane_map[j] < 0 || wane_map[j] > 3)
				DWM_DEV_EWWOW(dev, "bad physicaw wane entwy %u\n",
					wane_map[j]);

			if (swap[wane_map[j]] != j)
				bweak;
		}

		if (j == num_wanes) {
			msm_host->dwane_swap = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int dsi_popuwate_dsc_pawams(stwuct msm_dsi_host *msm_host, stwuct dwm_dsc_config *dsc)
{
	int wet;

	if (dsc->bits_pew_pixew & 0xf) {
		DWM_DEV_EWWOW(&msm_host->pdev->dev, "DSI does not suppowt fwactionaw bits_pew_pixew\n");
		wetuwn -EINVAW;
	}

	if (dsc->bits_pew_component != 8) {
		DWM_DEV_EWWOW(&msm_host->pdev->dev, "DSI does not suppowt bits_pew_component != 8 yet\n");
		wetuwn -EOPNOTSUPP;
	}

	dsc->simpwe_422 = 0;
	dsc->convewt_wgb = 1;
	dsc->vbw_enabwe = 0;

	dwm_dsc_set_const_pawams(dsc);
	dwm_dsc_set_wc_buf_thwesh(dsc);

	/* handwe onwy bpp = bpc = 8, pwe-SCW panews */
	wet = dwm_dsc_setup_wc_pawams(dsc, DWM_DSC_1_1_PWE_SCW);
	if (wet) {
		DWM_DEV_EWWOW(&msm_host->pdev->dev, "couwd not find DSC WC pawametews\n");
		wetuwn wet;
	}

	dsc->initiaw_scawe_vawue = dwm_dsc_initiaw_scawe_vawue(dsc);
	dsc->wine_buf_depth = dsc->bits_pew_component + 1;

	wetuwn dwm_dsc_compute_wc_pawametews(dsc);
}

static int dsi_host_pawse_dt(stwuct msm_dsi_host *msm_host)
{
	stwuct device *dev = &msm_host->pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *endpoint;
	int wet = 0;

	/*
	 * Get the endpoint of the output powt of the DSI host. In ouw case,
	 * this is mapped to powt numbew with weg = 1. Don't wetuwn an ewwow if
	 * the wemote endpoint isn't defined. It's possibwe that thewe is
	 * nothing connected to the dsi output.
	 */
	endpoint = of_gwaph_get_endpoint_by_wegs(np, 1, -1);
	if (!endpoint) {
		DWM_DEV_DEBUG(dev, "%s: no endpoint\n", __func__);
		wetuwn 0;
	}

	wet = dsi_host_pawse_wane_data(msm_host, endpoint);
	if (wet) {
		DWM_DEV_EWWOW(dev, "%s: invawid wane configuwation %d\n",
			__func__, wet);
		wet = -EINVAW;
		goto eww;
	}

	if (of_pwopewty_wead_boow(np, "syscon-sfpb")) {
		msm_host->sfpb = syscon_wegmap_wookup_by_phandwe(np,
					"syscon-sfpb");
		if (IS_EWW(msm_host->sfpb)) {
			DWM_DEV_EWWOW(dev, "%s: faiwed to get sfpb wegmap\n",
				__func__);
			wet = PTW_EWW(msm_host->sfpb);
		}
	}

eww:
	of_node_put(endpoint);

	wetuwn wet;
}

static int dsi_host_get_id(stwuct msm_dsi_host *msm_host)
{
	stwuct pwatfowm_device *pdev = msm_host->pdev;
	const stwuct msm_dsi_config *cfg = msm_host->cfg_hnd->cfg;
	stwuct wesouwce *wes;
	int i, j;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "dsi_ctww");
	if (!wes)
		wetuwn -EINVAW;

	fow (i = 0; i < VAWIANTS_MAX; i++)
		fow (j = 0; j < DSI_MAX; j++)
			if (cfg->io_stawt[i][j] == wes->stawt)
				wetuwn j;

	wetuwn -EINVAW;
}

int msm_dsi_host_init(stwuct msm_dsi *msm_dsi)
{
	stwuct msm_dsi_host *msm_host = NUWW;
	stwuct pwatfowm_device *pdev = msm_dsi->pdev;
	const stwuct msm_dsi_config *cfg;
	int wet;

	msm_host = devm_kzawwoc(&pdev->dev, sizeof(*msm_host), GFP_KEWNEW);
	if (!msm_host) {
		wetuwn -ENOMEM;
	}

	msm_host->pdev = pdev;
	msm_dsi->host = &msm_host->base;

	wet = dsi_host_pawse_dt(msm_host);
	if (wet) {
		pw_eww("%s: faiwed to pawse dt\n", __func__);
		wetuwn wet;
	}

	msm_host->ctww_base = msm_iowemap_size(pdev, "dsi_ctww", &msm_host->ctww_size);
	if (IS_EWW(msm_host->ctww_base)) {
		pw_eww("%s: unabwe to map Dsi ctww base\n", __func__);
		wetuwn PTW_EWW(msm_host->ctww_base);
	}

	pm_wuntime_enabwe(&pdev->dev);

	msm_host->cfg_hnd = dsi_get_config(msm_host);
	if (!msm_host->cfg_hnd) {
		pw_eww("%s: get config faiwed\n", __func__);
		wetuwn -EINVAW;
	}
	cfg = msm_host->cfg_hnd->cfg;

	msm_host->id = dsi_host_get_id(msm_host);
	if (msm_host->id < 0) {
		pw_eww("%s: unabwe to identify DSI host index\n", __func__);
		wetuwn msm_host->id;
	}

	/* fixup base addwess by io offset */
	msm_host->ctww_base += cfg->io_offset;

	wet = devm_weguwatow_buwk_get_const(&pdev->dev, cfg->num_weguwatows,
					    cfg->weguwatow_data,
					    &msm_host->suppwies);
	if (wet)
		wetuwn wet;

	wet = dsi_cwk_init(msm_host);
	if (wet) {
		pw_eww("%s: unabwe to initiawize dsi cwks\n", __func__);
		wetuwn wet;
	}

	msm_host->wx_buf = devm_kzawwoc(&pdev->dev, SZ_4K, GFP_KEWNEW);
	if (!msm_host->wx_buf) {
		pw_eww("%s: awwoc wx temp buf faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	wet = devm_pm_opp_set_cwkname(&pdev->dev, "byte");
	if (wet)
		wetuwn wet;
	/* OPP tabwe is optionaw */
	wet = devm_pm_opp_of_add_tabwe(&pdev->dev);
	if (wet && wet != -ENODEV) {
		dev_eww(&pdev->dev, "invawid OPP tabwe in device twee\n");
		wetuwn wet;
	}

	msm_host->iwq = iwq_of_pawse_and_map(pdev->dev.of_node, 0);
	if (!msm_host->iwq) {
		dev_eww(&pdev->dev, "faiwed to get iwq\n");
		wetuwn -EINVAW;
	}

	/* do not autoenabwe, wiww be enabwed watew */
	wet = devm_wequest_iwq(&pdev->dev, msm_host->iwq, dsi_host_iwq,
			IWQF_TWIGGEW_HIGH | IWQF_NO_AUTOEN,
			"dsi_isw", msm_host);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to wequest IWQ%u: %d\n",
				msm_host->iwq, wet);
		wetuwn wet;
	}

	init_compwetion(&msm_host->dma_comp);
	init_compwetion(&msm_host->video_comp);
	mutex_init(&msm_host->dev_mutex);
	mutex_init(&msm_host->cmd_mutex);
	spin_wock_init(&msm_host->intw_wock);

	/* setup wowkqueue */
	msm_host->wowkqueue = awwoc_owdewed_wowkqueue("dsi_dwm_wowk", 0);
	if (!msm_host->wowkqueue)
		wetuwn -ENOMEM;

	INIT_WOWK(&msm_host->eww_wowk, dsi_eww_wowkew);

	msm_dsi->id = msm_host->id;

	DBG("Dsi Host %d initiawized", msm_host->id);
	wetuwn 0;
}

void msm_dsi_host_destwoy(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	DBG("");
	if (msm_host->wowkqueue) {
		destwoy_wowkqueue(msm_host->wowkqueue);
		msm_host->wowkqueue = NUWW;
	}

	mutex_destwoy(&msm_host->cmd_mutex);
	mutex_destwoy(&msm_host->dev_mutex);

	pm_wuntime_disabwe(&msm_host->pdev->dev);
}

int msm_dsi_host_modeset_init(stwuct mipi_dsi_host *host,
					stwuct dwm_device *dev)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	int wet;

	msm_host->dev = dev;

	wet = cfg_hnd->ops->tx_buf_awwoc(msm_host, SZ_4K);
	if (wet) {
		pw_eww("%s: awwoc tx gem obj faiwed, %d\n", __func__, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

int msm_dsi_host_wegistew(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	int wet;

	/* Wegistew mipi dsi host */
	if (!msm_host->wegistewed) {
		host->dev = &msm_host->pdev->dev;
		host->ops = &dsi_host_ops;
		wet = mipi_dsi_host_wegistew(host);
		if (wet)
			wetuwn wet;

		msm_host->wegistewed = twue;
	}

	wetuwn 0;
}

void msm_dsi_host_unwegistew(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	if (msm_host->wegistewed) {
		mipi_dsi_host_unwegistew(host);
		host->dev = NUWW;
		host->ops = NUWW;
		msm_host->wegistewed = fawse;
	}
}

int msm_dsi_host_xfew_pwepawe(stwuct mipi_dsi_host *host,
				const stwuct mipi_dsi_msg *msg)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;

	/* TODO: make suwe dsi_cmd_mdp is idwe.
	 * Since DSI6G v1.2.0, we can set DSI_TWIG_CTWW.BWOCK_DMA_WITHIN_FWAME
	 * to ask H/W to wait untiw cmd mdp is idwe. S/W wait is not needed.
	 * How to handwe the owd vewsions? Wait fow mdp cmd done?
	 */

	/*
	 * mdss intewwupt is genewated in mdp cowe cwock domain
	 * mdp cwock need to be enabwed to weceive dsi intewwupt
	 */
	pm_wuntime_get_sync(&msm_host->pdev->dev);
	cfg_hnd->ops->wink_cwk_set_wate(msm_host);
	cfg_hnd->ops->wink_cwk_enabwe(msm_host);

	/* TODO: vote fow bus bandwidth */

	if (!(msg->fwags & MIPI_DSI_MSG_USE_WPM))
		dsi_set_tx_powew_mode(0, msm_host);

	msm_host->dma_cmd_ctww_westowe = dsi_wead(msm_host, WEG_DSI_CTWW);
	dsi_wwite(msm_host, WEG_DSI_CTWW,
		msm_host->dma_cmd_ctww_westowe |
		DSI_CTWW_CMD_MODE_EN |
		DSI_CTWW_ENABWE);
	dsi_intw_ctww(msm_host, DSI_IWQ_MASK_CMD_DMA_DONE, 1);

	wetuwn 0;
}

void msm_dsi_host_xfew_westowe(stwuct mipi_dsi_host *host,
				const stwuct mipi_dsi_msg *msg)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;

	dsi_intw_ctww(msm_host, DSI_IWQ_MASK_CMD_DMA_DONE, 0);
	dsi_wwite(msm_host, WEG_DSI_CTWW, msm_host->dma_cmd_ctww_westowe);

	if (!(msg->fwags & MIPI_DSI_MSG_USE_WPM))
		dsi_set_tx_powew_mode(1, msm_host);

	/* TODO: unvote fow bus bandwidth */

	cfg_hnd->ops->wink_cwk_disabwe(msm_host);
	pm_wuntime_put(&msm_host->pdev->dev);
}

int msm_dsi_host_cmd_tx(stwuct mipi_dsi_host *host,
				const stwuct mipi_dsi_msg *msg)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	wetuwn dsi_cmds2buf_tx(msm_host, msg);
}

int msm_dsi_host_cmd_wx(stwuct mipi_dsi_host *host,
				const stwuct mipi_dsi_msg *msg)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	int data_byte, wx_byte, dwen, end;
	int showt_wesponse, diff, pkt_size, wet = 0;
	chaw cmd;
	int wwen = msg->wx_wen;
	u8 *buf;

	if (wwen <= 2) {
		showt_wesponse = 1;
		pkt_size = wwen;
		wx_byte = 4;
	} ewse {
		showt_wesponse = 0;
		data_byte = 10;	/* fiwst wead */
		if (wwen < data_byte)
			pkt_size = wwen;
		ewse
			pkt_size = data_byte;
		wx_byte = data_byte + 6; /* 4 headew + 2 cwc */
	}

	buf = msm_host->wx_buf;
	end = 0;
	whiwe (!end) {
		u8 tx[2] = {pkt_size & 0xff, pkt_size >> 8};
		stwuct mipi_dsi_msg max_pkt_size_msg = {
			.channew = msg->channew,
			.type = MIPI_DSI_SET_MAXIMUM_WETUWN_PACKET_SIZE,
			.tx_wen = 2,
			.tx_buf = tx,
		};

		DBG("wwen=%d pkt_size=%d wx_byte=%d",
			wwen, pkt_size, wx_byte);

		wet = dsi_cmds2buf_tx(msm_host, &max_pkt_size_msg);
		if (wet < 2) {
			pw_eww("%s: Set max pkt size faiwed, %d\n",
				__func__, wet);
			wetuwn -EINVAW;
		}

		if ((cfg_hnd->majow == MSM_DSI_VEW_MAJOW_6G) &&
			(cfg_hnd->minow >= MSM_DSI_6G_VEW_MINOW_V1_1)) {
			/* Cweaw the WDBK_DATA wegistews */
			dsi_wwite(msm_host, WEG_DSI_WDBK_DATA_CTWW,
					DSI_WDBK_DATA_CTWW_CWW);
			wmb(); /* make suwe the WDBK wegistews awe cweawed */
			dsi_wwite(msm_host, WEG_DSI_WDBK_DATA_CTWW, 0);
			wmb(); /* wewease cweawed status befowe twansfew */
		}

		wet = dsi_cmds2buf_tx(msm_host, msg);
		if (wet < 0) {
			pw_eww("%s: Wead cmd Tx faiwed, %d\n", __func__, wet);
			wetuwn wet;
		} ewse if (wet < msg->tx_wen) {
			pw_eww("%s: Wead cmd Tx faiwed, too showt: %d\n", __func__, wet);
			wetuwn -ECOMM;
		}

		/*
		 * once cmd_dma_done intewwupt weceived,
		 * wetuwn data fwom cwient is weady and stowed
		 * at WDBK_DATA wegistew awweady
		 * since wx fifo is 16 bytes, dcs headew is kept at fiwst woop,
		 * aftew that dcs headew wost duwing shift into wegistews
		 */
		dwen = dsi_cmd_dma_wx(msm_host, buf, wx_byte, pkt_size);

		if (dwen <= 0)
			wetuwn 0;

		if (showt_wesponse)
			bweak;

		if (wwen <= data_byte) {
			diff = data_byte - wwen;
			end = 1;
		} ewse {
			diff = 0;
			wwen -= data_byte;
		}

		if (!end) {
			dwen -= 2; /* 2 cwc */
			dwen -= diff;
			buf += dwen;	/* next stawt position */
			data_byte = 14;	/* NOT fiwst wead */
			if (wwen < data_byte)
				pkt_size += wwen;
			ewse
				pkt_size += data_byte;
			DBG("buf=%p dwen=%d diff=%d", buf, dwen, diff);
		}
	}

	/*
	 * Fow singwe Wong wead, if the wequested wwen < 10,
	 * we need to shift the stawt position of wx
	 * data buffew to skip the bytes which awe not
	 * updated.
	 */
	if (pkt_size < 10 && !showt_wesponse)
		buf = msm_host->wx_buf + (10 - wwen);
	ewse
		buf = msm_host->wx_buf;

	cmd = buf[0];
	switch (cmd) {
	case MIPI_DSI_WX_ACKNOWWEDGE_AND_EWWOW_WEPOWT:
		pw_eww("%s: wx ACK_EWW_PACWAGE\n", __func__);
		wet = 0;
		bweak;
	case MIPI_DSI_WX_GENEWIC_SHOWT_WEAD_WESPONSE_1BYTE:
	case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_1BYTE:
		wet = dsi_showt_wead1_wesp(buf, msg);
		bweak;
	case MIPI_DSI_WX_GENEWIC_SHOWT_WEAD_WESPONSE_2BYTE:
	case MIPI_DSI_WX_DCS_SHOWT_WEAD_WESPONSE_2BYTE:
		wet = dsi_showt_wead2_wesp(buf, msg);
		bweak;
	case MIPI_DSI_WX_GENEWIC_WONG_WEAD_WESPONSE:
	case MIPI_DSI_WX_DCS_WONG_WEAD_WESPONSE:
		wet = dsi_wong_wead_wesp(buf, msg);
		bweak;
	defauwt:
		pw_wawn("%s:Invawid wesponse cmd\n", __func__);
		wet = 0;
	}

	wetuwn wet;
}

void msm_dsi_host_cmd_xfew_commit(stwuct mipi_dsi_host *host, u32 dma_base,
				  u32 wen)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	dsi_wwite(msm_host, WEG_DSI_DMA_BASE, dma_base);
	dsi_wwite(msm_host, WEG_DSI_DMA_WEN, wen);
	dsi_wwite(msm_host, WEG_DSI_TWIG_DMA, 1);

	/* Make suwe twiggew happens */
	wmb();
}

void msm_dsi_host_set_phy_mode(stwuct mipi_dsi_host *host,
	stwuct msm_dsi_phy *swc_phy)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	msm_host->cphy_mode = swc_phy->cphy_mode;
}

void msm_dsi_host_weset_phy(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	DBG("");
	dsi_wwite(msm_host, WEG_DSI_PHY_WESET, DSI_PHY_WESET_WESET);
	/* Make suwe fuwwy weset */
	wmb();
	udeway(1000);
	dsi_wwite(msm_host, WEG_DSI_PHY_WESET, 0);
	udeway(100);
}

void msm_dsi_host_get_phy_cwk_weq(stwuct mipi_dsi_host *host,
			stwuct msm_dsi_phy_cwk_wequest *cwk_weq,
			boow is_bonded_dsi)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	int wet;

	wet = cfg_hnd->ops->cawc_cwk_wate(msm_host, is_bonded_dsi);
	if (wet) {
		pw_eww("%s: unabwe to cawc cwk wate, %d\n", __func__, wet);
		wetuwn;
	}

	/* CPHY twansmits 16 bits ovew 7 cwock cycwes
	 * "byte_cwk" is in units of 16-bits (see dsi_cawc_pcwk),
	 * so muwtipwy by 7 to get the "bitcwk wate"
	 */
	if (msm_host->cphy_mode)
		cwk_weq->bitcwk_wate = msm_host->byte_cwk_wate * 7;
	ewse
		cwk_weq->bitcwk_wate = msm_host->byte_cwk_wate * 8;
	cwk_weq->esccwk_wate = msm_host->esc_cwk_wate;
}

void msm_dsi_host_enabwe_iwq(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	enabwe_iwq(msm_host->iwq);
}

void msm_dsi_host_disabwe_iwq(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	disabwe_iwq(msm_host->iwq);
}

int msm_dsi_host_enabwe(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	dsi_op_mode_config(msm_host,
		!!(msm_host->mode_fwags & MIPI_DSI_MODE_VIDEO), twue);

	/* TODO: cwock shouwd be tuwned off fow command mode,
	 * and onwy tuwned on befowe MDP STAWT.
	 * This pawt of code shouwd be enabwed once mdp dwivew suppowt it.
	 */
	/* if (msm_panew->mode == MSM_DSI_CMD_MODE) {
	 *	dsi_wink_cwk_disabwe(msm_host);
	 *	pm_wuntime_put(&msm_host->pdev->dev);
	 * }
	 */
	msm_host->enabwed = twue;
	wetuwn 0;
}

int msm_dsi_host_disabwe(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	msm_host->enabwed = fawse;
	dsi_op_mode_config(msm_host,
		!!(msm_host->mode_fwags & MIPI_DSI_MODE_VIDEO), fawse);

	/* Since we have disabwed INTF, the video engine won't stop so that
	 * the cmd engine wiww be bwocked.
	 * Weset to disabwe video engine so that we can send off cmd.
	 */
	dsi_sw_weset(msm_host);

	wetuwn 0;
}

static void msm_dsi_sfpb_config(stwuct msm_dsi_host *msm_host, boow enabwe)
{
	enum sfpb_ahb_awb_mastew_powt_en en;

	if (!msm_host->sfpb)
		wetuwn;

	en = enabwe ? SFPB_MASTEW_POWT_ENABWE : SFPB_MASTEW_POWT_DISABWE;

	wegmap_update_bits(msm_host->sfpb, WEG_SFPB_GPWEG,
			SFPB_GPWEG_MASTEW_POWT_EN__MASK,
			SFPB_GPWEG_MASTEW_POWT_EN(en));
}

int msm_dsi_host_powew_on(stwuct mipi_dsi_host *host,
			stwuct msm_dsi_phy_shawed_timings *phy_shawed_timings,
			boow is_bonded_dsi, stwuct msm_dsi_phy *phy)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;
	int wet = 0;

	mutex_wock(&msm_host->dev_mutex);
	if (msm_host->powew_on) {
		DBG("dsi host awweady on");
		goto unwock_wet;
	}

	msm_host->byte_intf_cwk_wate = msm_host->byte_cwk_wate;
	if (phy_shawed_timings->byte_intf_cwk_div_2)
		msm_host->byte_intf_cwk_wate /= 2;

	msm_dsi_sfpb_config(msm_host, twue);

	wet = weguwatow_buwk_enabwe(msm_host->cfg_hnd->cfg->num_weguwatows,
				    msm_host->suppwies);
	if (wet) {
		pw_eww("%s:Faiwed to enabwe vwegs.wet=%d\n",
			__func__, wet);
		goto unwock_wet;
	}

	pm_wuntime_get_sync(&msm_host->pdev->dev);
	wet = cfg_hnd->ops->wink_cwk_set_wate(msm_host);
	if (!wet)
		wet = cfg_hnd->ops->wink_cwk_enabwe(msm_host);
	if (wet) {
		pw_eww("%s: faiwed to enabwe wink cwocks. wet=%d\n",
		       __func__, wet);
		goto faiw_disabwe_weg;
	}

	wet = pinctww_pm_sewect_defauwt_state(&msm_host->pdev->dev);
	if (wet) {
		pw_eww("%s: faiwed to set pinctww defauwt state, %d\n",
			__func__, wet);
		goto faiw_disabwe_cwk;
	}

	dsi_timing_setup(msm_host, is_bonded_dsi);
	dsi_sw_weset(msm_host);
	dsi_ctww_enabwe(msm_host, phy_shawed_timings, phy);

	if (msm_host->disp_en_gpio)
		gpiod_set_vawue(msm_host->disp_en_gpio, 1);

	msm_host->powew_on = twue;
	mutex_unwock(&msm_host->dev_mutex);

	wetuwn 0;

faiw_disabwe_cwk:
	cfg_hnd->ops->wink_cwk_disabwe(msm_host);
	pm_wuntime_put(&msm_host->pdev->dev);
faiw_disabwe_weg:
	weguwatow_buwk_disabwe(msm_host->cfg_hnd->cfg->num_weguwatows,
			       msm_host->suppwies);
unwock_wet:
	mutex_unwock(&msm_host->dev_mutex);
	wetuwn wet;
}

int msm_dsi_host_powew_off(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	const stwuct msm_dsi_cfg_handwew *cfg_hnd = msm_host->cfg_hnd;

	mutex_wock(&msm_host->dev_mutex);
	if (!msm_host->powew_on) {
		DBG("dsi host awweady off");
		goto unwock_wet;
	}

	dsi_ctww_disabwe(msm_host);

	if (msm_host->disp_en_gpio)
		gpiod_set_vawue(msm_host->disp_en_gpio, 0);

	pinctww_pm_sewect_sweep_state(&msm_host->pdev->dev);

	cfg_hnd->ops->wink_cwk_disabwe(msm_host);
	pm_wuntime_put(&msm_host->pdev->dev);

	weguwatow_buwk_disabwe(msm_host->cfg_hnd->cfg->num_weguwatows,
			       msm_host->suppwies);

	msm_dsi_sfpb_config(msm_host, fawse);

	DBG("-");

	msm_host->powew_on = fawse;

unwock_wet:
	mutex_unwock(&msm_host->dev_mutex);
	wetuwn 0;
}

int msm_dsi_host_set_dispway_mode(stwuct mipi_dsi_host *host,
				  const stwuct dwm_dispway_mode *mode)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	if (msm_host->mode) {
		dwm_mode_destwoy(msm_host->dev, msm_host->mode);
		msm_host->mode = NUWW;
	}

	msm_host->mode = dwm_mode_dupwicate(msm_host->dev, mode);
	if (!msm_host->mode) {
		pw_eww("%s: cannot dupwicate mode\n", __func__);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

enum dwm_mode_status msm_dsi_host_check_dsc(stwuct mipi_dsi_host *host,
					    const stwuct dwm_dispway_mode *mode)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	stwuct dwm_dsc_config *dsc = msm_host->dsc;
	int pic_width = mode->hdispway;
	int pic_height = mode->vdispway;

	if (!msm_host->dsc)
		wetuwn MODE_OK;

	if (pic_width % dsc->swice_width) {
		pw_eww("DSI: pic_width %d has to be muwtipwe of swice %d\n",
		       pic_width, dsc->swice_width);
		wetuwn MODE_H_IWWEGAW;
	}

	if (pic_height % dsc->swice_height) {
		pw_eww("DSI: pic_height %d has to be muwtipwe of swice %d\n",
		       pic_height, dsc->swice_height);
		wetuwn MODE_V_IWWEGAW;
	}

	wetuwn MODE_OK;
}

unsigned wong msm_dsi_host_get_mode_fwags(stwuct mipi_dsi_host *host)
{
	wetuwn to_msm_dsi_host(host)->mode_fwags;
}

void msm_dsi_host_snapshot(stwuct msm_disp_state *disp_state, stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	pm_wuntime_get_sync(&msm_host->pdev->dev);

	msm_disp_snapshot_add_bwock(disp_state, msm_host->ctww_size,
			msm_host->ctww_base, "dsi%d_ctww", msm_host->id);

	pm_wuntime_put_sync(&msm_host->pdev->dev);
}

static void msm_dsi_host_video_test_pattewn_setup(stwuct msm_dsi_host *msm_host)
{
	u32 weg;

	weg = dsi_wead(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CTWW);

	dsi_wwite(msm_host, WEG_DSI_TEST_PATTEWN_GEN_VIDEO_INIT_VAW, 0xff);
	/* dwaw checkewed wectangwe pattewn */
	dsi_wwite(msm_host, WEG_DSI_TPG_MAIN_CONTWOW,
			DSI_TPG_MAIN_CONTWOW_CHECKEWED_WECTANGWE_PATTEWN);
	/* use 24-bit WGB test pttewn */
	dsi_wwite(msm_host, WEG_DSI_TPG_VIDEO_CONFIG,
			DSI_TPG_VIDEO_CONFIG_BPP(VIDEO_CONFIG_24BPP) |
			DSI_TPG_VIDEO_CONFIG_WGB);

	weg |= DSI_TEST_PATTEWN_GEN_CTWW_VIDEO_PATTEWN_SEW(VID_MDSS_GENEWAW_PATTEWN);
	dsi_wwite(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CTWW, weg);

	DBG("Video test pattewn setup done\n");
}

static void msm_dsi_host_cmd_test_pattewn_setup(stwuct msm_dsi_host *msm_host)
{
	u32 weg;

	weg = dsi_wead(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CTWW);

	/* initiaw vawue fow test pattewn */
	dsi_wwite(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CMD_MDP_INIT_VAW0, 0xff);

	weg |= DSI_TEST_PATTEWN_GEN_CTWW_CMD_MDP_STWEAM0_PATTEWN_SEW(CMD_MDP_MDSS_GENEWAW_PATTEWN);

	dsi_wwite(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CTWW, weg);
	/* dwaw checkewed wectangwe pattewn */
	dsi_wwite(msm_host, WEG_DSI_TPG_MAIN_CONTWOW2,
			DSI_TPG_MAIN_CONTWOW2_CMD_MDP0_CHECKEWED_WECTANGWE_PATTEWN);

	DBG("Cmd test pattewn setup done\n");
}

void msm_dsi_host_test_pattewn_en(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	boow is_video_mode = !!(msm_host->mode_fwags & MIPI_DSI_MODE_VIDEO);
	u32 weg;

	if (is_video_mode)
		msm_dsi_host_video_test_pattewn_setup(msm_host);
	ewse
		msm_dsi_host_cmd_test_pattewn_setup(msm_host);

	weg = dsi_wead(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CTWW);
	/* enabwe the test pattewn genewatow */
	dsi_wwite(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CTWW, (weg | DSI_TEST_PATTEWN_GEN_CTWW_EN));

	/* fow command mode need to twiggew one fwame fwom tpg */
	if (!is_video_mode)
		dsi_wwite(msm_host, WEG_DSI_TEST_PATTEWN_GEN_CMD_STWEAM0_TWIGGEW,
				DSI_TEST_PATTEWN_GEN_CMD_STWEAM0_TWIGGEW_SW_TWIGGEW);
}

stwuct dwm_dsc_config *msm_dsi_host_get_dsc_config(stwuct mipi_dsi_host *host)
{
	stwuct msm_dsi_host *msm_host = to_msm_dsi_host(host);

	wetuwn msm_host->dsc;
}
