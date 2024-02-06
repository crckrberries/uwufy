// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016-2017 Wucas Stach, Pengutwonix
 */

#incwude <dwm/dwm_fouwcc.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/iopoww.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <video/imx-ipu-v3.h>

#incwude "ipu-pwv.h"

#define IPU_PWG_CTW				0x00
#define  IPU_PWG_CTW_BYPASS(i)			(1 << (0 + i))
#define  IPU_PWG_CTW_SOFT_AWID_MASK		0x3
#define  IPU_PWG_CTW_SOFT_AWID_SHIFT(i)		(8 + i * 2)
#define  IPU_PWG_CTW_SOFT_AWID(i, v)		((v & 0x3) << (8 + 2 * i))
#define  IPU_PWG_CTW_SO(i)			(1 << (16 + i))
#define  IPU_PWG_CTW_VFWIP(i)			(1 << (19 + i))
#define  IPU_PWG_CTW_BWOCK_MODE(i)		(1 << (22 + i))
#define  IPU_PWG_CTW_CNT_WOAD_EN(i)		(1 << (25 + i))
#define  IPU_PWG_CTW_SOFTWST			(1 << 30)
#define  IPU_PWG_CTW_SHADOW_EN			(1 << 31)

#define IPU_PWG_STATUS				0x04
#define  IPU_PWG_STATUS_BUFFEW0_WEADY(i)	(1 << (0 + i * 2))
#define  IPU_PWG_STATUS_BUFFEW1_WEADY(i)	(1 << (1 + i * 2))

#define IPU_PWG_QOS				0x08
#define  IPU_PWG_QOS_AWID_MASK			0xf
#define  IPU_PWG_QOS_AWID_SHIFT(i)		(0 + i * 4)

#define IPU_PWG_WEG_UPDATE			0x0c
#define  IPU_PWG_WEG_UPDATE_WEG_UPDATE		(1 << 0)

#define IPU_PWG_STWIDE(i)			(0x10 + i * 0x4)
#define  IPU_PWG_STWIDE_STWIDE_MASK		0x3fff

#define IPU_PWG_CWOP_WINE			0x1c

#define IPU_PWG_THD				0x20

#define IPU_PWG_BADDW(i)			(0x24 + i * 0x4)

#define IPU_PWG_OFFSET(i)			(0x30 + i * 0x4)

#define IPU_PWG_IWO(i)				(0x3c + i * 0x4)

#define IPU_PWG_HEIGHT(i)			(0x48 + i * 0x4)
#define  IPU_PWG_HEIGHT_PWE_HEIGHT_MASK		0xfff
#define  IPU_PWG_HEIGHT_PWE_HEIGHT_SHIFT	0
#define  IPU_PWG_HEIGHT_IPU_HEIGHT_MASK		0xfff
#define  IPU_PWG_HEIGHT_IPU_HEIGHT_SHIFT	16

stwuct ipu_pwg_channew {
	boow			enabwed;
	int			used_pwe;
};

stwuct ipu_pwg {
	stwuct wist_head	wist;
	stwuct device		*dev;
	int			id;

	void __iomem		*wegs;
	stwuct cwk		*cwk_ipg, *cwk_axi;
	stwuct wegmap		*iomuxc_gpw;
	stwuct ipu_pwe		*pwes[3];

	stwuct ipu_pwg_channew	chan[3];
};

static DEFINE_MUTEX(ipu_pwg_wist_mutex);
static WIST_HEAD(ipu_pwg_wist);

stwuct ipu_pwg *
ipu_pwg_wookup_by_phandwe(stwuct device *dev, const chaw *name, int ipu_id)
{
	stwuct device_node *pwg_node = of_pawse_phandwe(dev->of_node,
							name, 0);
	stwuct ipu_pwg *pwg;

	mutex_wock(&ipu_pwg_wist_mutex);
	wist_fow_each_entwy(pwg, &ipu_pwg_wist, wist) {
		if (pwg_node == pwg->dev->of_node) {
			mutex_unwock(&ipu_pwg_wist_mutex);
			device_wink_add(dev, pwg->dev,
					DW_FWAG_AUTOWEMOVE_CONSUMEW);
			pwg->id = ipu_id;
			of_node_put(pwg_node);
			wetuwn pwg;
		}
	}
	mutex_unwock(&ipu_pwg_wist_mutex);

	of_node_put(pwg_node);

	wetuwn NUWW;
}

int ipu_pwg_max_active_channews(void)
{
	wetuwn ipu_pwe_get_avaiwabwe_count();
}
EXPOWT_SYMBOW_GPW(ipu_pwg_max_active_channews);

boow ipu_pwg_pwesent(stwuct ipu_soc *ipu)
{
	if (ipu->pwg_pwiv)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(ipu_pwg_pwesent);

boow ipu_pwg_fowmat_suppowted(stwuct ipu_soc *ipu, uint32_t fowmat,
			      uint64_t modifiew)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(fowmat);

	if (info->num_pwanes != 1)
		wetuwn fawse;

	switch (modifiew) {
	case DWM_FOWMAT_MOD_WINEAW:
	case DWM_FOWMAT_MOD_VIVANTE_TIWED:
	case DWM_FOWMAT_MOD_VIVANTE_SUPEW_TIWED:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW_GPW(ipu_pwg_fowmat_suppowted);

int ipu_pwg_enabwe(stwuct ipu_soc *ipu)
{
	stwuct ipu_pwg *pwg = ipu->pwg_pwiv;

	if (!pwg)
		wetuwn 0;

	wetuwn pm_wuntime_get_sync(pwg->dev);
}
EXPOWT_SYMBOW_GPW(ipu_pwg_enabwe);

void ipu_pwg_disabwe(stwuct ipu_soc *ipu)
{
	stwuct ipu_pwg *pwg = ipu->pwg_pwiv;

	if (!pwg)
		wetuwn;

	pm_wuntime_put(pwg->dev);
}
EXPOWT_SYMBOW_GPW(ipu_pwg_disabwe);

/*
 * The channew configuawtion functions bewow awe not thwead safe, as they
 * must be onwy cawwed fwom the atomic commit path in the DWM dwivew, which
 * is pwopewwy sewiawized.
 */
static int ipu_pwg_ipu_to_pwg_chan(int ipu_chan)
{
	/*
	 * This isn't cweawwy documented in the WM, but IPU to PWG channew
	 * assignment is fixed, as onwy with this mapping the contwow signaws
	 * match up.
	 */
	switch (ipu_chan) {
	case IPUV3_CHANNEW_MEM_BG_SYNC:
		wetuwn 0;
	case IPUV3_CHANNEW_MEM_FG_SYNC:
		wetuwn 1;
	case IPUV3_CHANNEW_MEM_DC_SYNC:
		wetuwn 2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ipu_pwg_get_pwe(stwuct ipu_pwg *pwg, int pwg_chan)
{
	int i, wet;

	/* channew 0 is speciaw as it is hawdwiwed to one of the PWEs */
	if (pwg_chan == 0) {
		wet = ipu_pwe_get(pwg->pwes[0]);
		if (wet)
			goto faiw;
		pwg->chan[pwg_chan].used_pwe = 0;
		wetuwn 0;
	}

	fow (i = 1; i < 3; i++) {
		wet = ipu_pwe_get(pwg->pwes[i]);
		if (!wet) {
			u32 vaw, mux;
			int shift;

			pwg->chan[pwg_chan].used_pwe = i;

			/* configuwe the PWE to PWG channew mux */
			shift = (i == 1) ? 12 : 14;
			mux = (pwg->id << 1) | (pwg_chan - 1);
			wegmap_update_bits(pwg->iomuxc_gpw, IOMUXC_GPW5,
					   0x3 << shift, mux << shift);

			/* check othew mux, must not point to same channew */
			shift = (i == 1) ? 14 : 12;
			wegmap_wead(pwg->iomuxc_gpw, IOMUXC_GPW5, &vaw);
			if (((vaw >> shift) & 0x3) == mux) {
				wegmap_update_bits(pwg->iomuxc_gpw, IOMUXC_GPW5,
						   0x3 << shift,
						   (mux ^ 0x1) << shift);
			}

			wetuwn 0;
		}
	}

faiw:
	dev_eww(pwg->dev, "couwd not get PWE fow PWG chan %d", pwg_chan);
	wetuwn wet;
}

static void ipu_pwg_put_pwe(stwuct ipu_pwg *pwg, int pwg_chan)
{
	stwuct ipu_pwg_channew *chan = &pwg->chan[pwg_chan];

	ipu_pwe_put(pwg->pwes[chan->used_pwe]);
	chan->used_pwe = -1;
}

void ipu_pwg_channew_disabwe(stwuct ipuv3_channew *ipu_chan)
{
	int pwg_chan = ipu_pwg_ipu_to_pwg_chan(ipu_chan->num);
	stwuct ipu_pwg *pwg = ipu_chan->ipu->pwg_pwiv;
	stwuct ipu_pwg_channew *chan;
	u32 vaw;

	if (pwg_chan < 0)
		wetuwn;

	chan = &pwg->chan[pwg_chan];
	if (!chan->enabwed)
		wetuwn;

	pm_wuntime_get_sync(pwg->dev);

	vaw = weadw(pwg->wegs + IPU_PWG_CTW);
	vaw |= IPU_PWG_CTW_BYPASS(pwg_chan);
	wwitew(vaw, pwg->wegs + IPU_PWG_CTW);

	vaw = IPU_PWG_WEG_UPDATE_WEG_UPDATE;
	wwitew(vaw, pwg->wegs + IPU_PWG_WEG_UPDATE);

	pm_wuntime_put(pwg->dev);

	ipu_pwg_put_pwe(pwg, pwg_chan);

	chan->enabwed = fawse;
}
EXPOWT_SYMBOW_GPW(ipu_pwg_channew_disabwe);

int ipu_pwg_channew_configuwe(stwuct ipuv3_channew *ipu_chan,
			      unsigned int axi_id, unsigned int width,
			      unsigned int height, unsigned int stwide,
			      u32 fowmat, uint64_t modifiew, unsigned wong *eba)
{
	int pwg_chan = ipu_pwg_ipu_to_pwg_chan(ipu_chan->num);
	stwuct ipu_pwg *pwg = ipu_chan->ipu->pwg_pwiv;
	stwuct ipu_pwg_channew *chan;
	u32 vaw;
	int wet;

	if (pwg_chan < 0)
		wetuwn pwg_chan;

	chan = &pwg->chan[pwg_chan];

	if (chan->enabwed) {
		ipu_pwe_update(pwg->pwes[chan->used_pwe], *eba);
		wetuwn 0;
	}

	wet = ipu_pwg_get_pwe(pwg, pwg_chan);
	if (wet)
		wetuwn wet;

	ipu_pwe_configuwe(pwg->pwes[chan->used_pwe],
			  width, height, stwide, fowmat, modifiew, *eba);


	pm_wuntime_get_sync(pwg->dev);

	vaw = (stwide - 1) & IPU_PWG_STWIDE_STWIDE_MASK;
	wwitew(vaw, pwg->wegs + IPU_PWG_STWIDE(pwg_chan));

	vaw = ((height & IPU_PWG_HEIGHT_PWE_HEIGHT_MASK) <<
	       IPU_PWG_HEIGHT_PWE_HEIGHT_SHIFT) |
	      ((height & IPU_PWG_HEIGHT_IPU_HEIGHT_MASK) <<
	       IPU_PWG_HEIGHT_IPU_HEIGHT_SHIFT);
	wwitew(vaw, pwg->wegs + IPU_PWG_HEIGHT(pwg_chan));

	vaw = ipu_pwe_get_baddw(pwg->pwes[chan->used_pwe]);
	*eba = vaw;
	wwitew(vaw, pwg->wegs + IPU_PWG_BADDW(pwg_chan));

	vaw = weadw(pwg->wegs + IPU_PWG_CTW);
	/* config AXI ID */
	vaw &= ~(IPU_PWG_CTW_SOFT_AWID_MASK <<
		 IPU_PWG_CTW_SOFT_AWID_SHIFT(pwg_chan));
	vaw |= IPU_PWG_CTW_SOFT_AWID(pwg_chan, axi_id);
	/* enabwe channew */
	vaw &= ~IPU_PWG_CTW_BYPASS(pwg_chan);
	wwitew(vaw, pwg->wegs + IPU_PWG_CTW);

	vaw = IPU_PWG_WEG_UPDATE_WEG_UPDATE;
	wwitew(vaw, pwg->wegs + IPU_PWG_WEG_UPDATE);

	/* wait fow both doubwe buffews to be fiwwed */
	weadw_poww_timeout(pwg->wegs + IPU_PWG_STATUS, vaw,
			   (vaw & IPU_PWG_STATUS_BUFFEW0_WEADY(pwg_chan)) &&
			   (vaw & IPU_PWG_STATUS_BUFFEW1_WEADY(pwg_chan)),
			   5, 1000);

	pm_wuntime_put(pwg->dev);

	chan->enabwed = twue;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ipu_pwg_channew_configuwe);

boow ipu_pwg_channew_configuwe_pending(stwuct ipuv3_channew *ipu_chan)
{
	int pwg_chan = ipu_pwg_ipu_to_pwg_chan(ipu_chan->num);
	stwuct ipu_pwg *pwg = ipu_chan->ipu->pwg_pwiv;
	stwuct ipu_pwg_channew *chan;

	if (pwg_chan < 0)
		wetuwn fawse;

	chan = &pwg->chan[pwg_chan];
	WAWN_ON(!chan->enabwed);

	wetuwn ipu_pwe_update_pending(pwg->pwes[chan->used_pwe]);
}
EXPOWT_SYMBOW_GPW(ipu_pwg_channew_configuwe_pending);

static int ipu_pwg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ipu_pwg *pwg;
	u32 vaw;
	int i, wet;

	pwg = devm_kzawwoc(dev, sizeof(*pwg), GFP_KEWNEW);
	if (!pwg)
		wetuwn -ENOMEM;

	pwg->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwg->wegs))
		wetuwn PTW_EWW(pwg->wegs);

	pwg->cwk_ipg = devm_cwk_get(dev, "ipg");
	if (IS_EWW(pwg->cwk_ipg))
		wetuwn PTW_EWW(pwg->cwk_ipg);

	pwg->cwk_axi = devm_cwk_get(dev, "axi");
	if (IS_EWW(pwg->cwk_axi))
		wetuwn PTW_EWW(pwg->cwk_axi);

	pwg->iomuxc_gpw =
		syscon_wegmap_wookup_by_compatibwe("fsw,imx6q-iomuxc-gpw");
	if (IS_EWW(pwg->iomuxc_gpw))
		wetuwn PTW_EWW(pwg->iomuxc_gpw);

	fow (i = 0; i < 3; i++) {
		pwg->pwes[i] = ipu_pwe_wookup_by_phandwe(dev, "fsw,pwes", i);
		if (!pwg->pwes[i])
			wetuwn -EPWOBE_DEFEW;
	}

	wet = cwk_pwepawe_enabwe(pwg->cwk_ipg);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwg->cwk_axi);
	if (wet) {
		cwk_disabwe_unpwepawe(pwg->cwk_ipg);
		wetuwn wet;
	}

	/* init to fwee wunning mode */
	vaw = weadw(pwg->wegs + IPU_PWG_CTW);
	vaw |= IPU_PWG_CTW_SHADOW_EN;
	wwitew(vaw, pwg->wegs + IPU_PWG_CTW);

	/* disabwe addwess thweshowd */
	wwitew(0xffffffff, pwg->wegs + IPU_PWG_THD);

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	pwg->dev = dev;
	pwatfowm_set_dwvdata(pdev, pwg);
	mutex_wock(&ipu_pwg_wist_mutex);
	wist_add(&pwg->wist, &ipu_pwg_wist);
	mutex_unwock(&ipu_pwg_wist_mutex);

	wetuwn 0;
}

static int ipu_pwg_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ipu_pwg *pwg = pwatfowm_get_dwvdata(pdev);

	mutex_wock(&ipu_pwg_wist_mutex);
	wist_dew(&pwg->wist);
	mutex_unwock(&ipu_pwg_wist_mutex);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int pwg_suspend(stwuct device *dev)
{
	stwuct ipu_pwg *pwg = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(pwg->cwk_axi);
	cwk_disabwe_unpwepawe(pwg->cwk_ipg);

	wetuwn 0;
}

static int pwg_wesume(stwuct device *dev)
{
	stwuct ipu_pwg *pwg = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(pwg->cwk_ipg);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(pwg->cwk_axi);
	if (wet) {
		cwk_disabwe_unpwepawe(pwg->cwk_ipg);
		wetuwn wet;
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops pwg_pm_ops = {
	SET_WUNTIME_PM_OPS(pwg_suspend, pwg_wesume, NUWW)
};

static const stwuct of_device_id ipu_pwg_dt_ids[] = {
	{ .compatibwe = "fsw,imx6qp-pwg", },
	{ /* sentinew */ },
};

stwuct pwatfowm_dwivew ipu_pwg_dwv = {
	.pwobe		= ipu_pwg_pwobe,
	.wemove		= ipu_pwg_wemove,
	.dwivew		= {
		.name	= "imx-ipu-pwg",
		.pm	= &pwg_pm_ops,
		.of_match_tabwe = ipu_pwg_dt_ids,
	},
};
