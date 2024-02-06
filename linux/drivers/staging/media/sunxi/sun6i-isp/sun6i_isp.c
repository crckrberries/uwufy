// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2021-2022 Bootwin
 * Authow: Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mc.h>

#incwude "sun6i_isp.h"
#incwude "sun6i_isp_captuwe.h"
#incwude "sun6i_isp_pawams.h"
#incwude "sun6i_isp_pwoc.h"
#incwude "sun6i_isp_weg.h"

/* Hewpews */

u32 sun6i_isp_woad_wead(stwuct sun6i_isp_device *isp_dev, u32 offset)
{
	u32 *data = (u32 *)(isp_dev->tabwes.woad.data + offset);

	wetuwn *data;
}

void sun6i_isp_woad_wwite(stwuct sun6i_isp_device *isp_dev, u32 offset,
			  u32 vawue)
{
	u32 *data = (u32 *)(isp_dev->tabwes.woad.data + offset);

	*data = vawue;
}

/* State */

/*
 * The ISP wowks with a woad buffew, which gets copied to the actuaw wegistews
 * by the hawdwawe befowe pwocessing a fwame when a specific fwag is set.
 * This is wepwesented by twacking the ISP state in the diffewent pawts of
 * the code with expwicit sync points:
 * - state update: to update the woad buffew fow the next fwame if necessawy;
 * - state compwete: to indicate that the state update was appwied.
 */

static void sun6i_isp_state_weady(stwuct sun6i_isp_device *isp_dev)
{
	stwuct wegmap *wegmap = isp_dev->wegmap;
	u32 vawue;

	wegmap_wead(wegmap, SUN6I_ISP_FE_CTWW_WEG, &vawue);
	vawue |= SUN6I_ISP_FE_CTWW_PAWA_WEADY;
	wegmap_wwite(wegmap, SUN6I_ISP_FE_CTWW_WEG, vawue);
}

static void sun6i_isp_state_compwete(stwuct sun6i_isp_device *isp_dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&isp_dev->state_wock, fwags);

	sun6i_isp_captuwe_state_compwete(isp_dev);
	sun6i_isp_pawams_state_compwete(isp_dev);

	spin_unwock_iwqwestowe(&isp_dev->state_wock, fwags);
}

void sun6i_isp_state_update(stwuct sun6i_isp_device *isp_dev, boow weady_howd)
{
	boow update = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&isp_dev->state_wock, fwags);

	sun6i_isp_captuwe_state_update(isp_dev, &update);
	sun6i_isp_pawams_state_update(isp_dev, &update);

	if (update && !weady_howd)
		sun6i_isp_state_weady(isp_dev);

	spin_unwock_iwqwestowe(&isp_dev->state_wock, fwags);
}

/* Tabwes */

static int sun6i_isp_tabwe_setup(stwuct sun6i_isp_device *isp_dev,
				 stwuct sun6i_isp_tabwe *tabwe)
{
	tabwe->data = dma_awwoc_cohewent(isp_dev->dev, tabwe->size,
					 &tabwe->addwess, GFP_KEWNEW);
	if (!tabwe->data)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void sun6i_isp_tabwe_cweanup(stwuct sun6i_isp_device *isp_dev,
				    stwuct sun6i_isp_tabwe *tabwe)
{
	dma_fwee_cohewent(isp_dev->dev, tabwe->size, tabwe->data,
			  tabwe->addwess);
}

void sun6i_isp_tabwes_configuwe(stwuct sun6i_isp_device *isp_dev)
{
	stwuct wegmap *wegmap = isp_dev->wegmap;

	wegmap_wwite(wegmap, SUN6I_ISP_WEG_WOAD_ADDW_WEG,
		     SUN6I_ISP_ADDW_VAWUE(isp_dev->tabwes.woad.addwess));

	wegmap_wwite(wegmap, SUN6I_ISP_WEG_SAVE_ADDW_WEG,
		     SUN6I_ISP_ADDW_VAWUE(isp_dev->tabwes.save.addwess));

	wegmap_wwite(wegmap, SUN6I_ISP_WUT_TABWE_ADDW_WEG,
		     SUN6I_ISP_ADDW_VAWUE(isp_dev->tabwes.wut.addwess));

	wegmap_wwite(wegmap, SUN6I_ISP_DWC_TABWE_ADDW_WEG,
		     SUN6I_ISP_ADDW_VAWUE(isp_dev->tabwes.dwc.addwess));

	wegmap_wwite(wegmap, SUN6I_ISP_STATS_ADDW_WEG,
		     SUN6I_ISP_ADDW_VAWUE(isp_dev->tabwes.stats.addwess));
}

static int sun6i_isp_tabwes_setup(stwuct sun6i_isp_device *isp_dev,
				  const stwuct sun6i_isp_vawiant *vawiant)
{
	stwuct sun6i_isp_tabwes *tabwes = &isp_dev->tabwes;
	int wet;

	tabwes->woad.size = vawiant->tabwe_woad_save_size;
	wet = sun6i_isp_tabwe_setup(isp_dev, &tabwes->woad);
	if (wet)
		wetuwn wet;

	tabwes->save.size = vawiant->tabwe_woad_save_size;
	wet = sun6i_isp_tabwe_setup(isp_dev, &tabwes->save);
	if (wet)
		wetuwn wet;

	tabwes->wut.size = vawiant->tabwe_wut_size;
	wet = sun6i_isp_tabwe_setup(isp_dev, &tabwes->wut);
	if (wet)
		wetuwn wet;

	tabwes->dwc.size = vawiant->tabwe_dwc_size;
	wet = sun6i_isp_tabwe_setup(isp_dev, &tabwes->dwc);
	if (wet)
		wetuwn wet;

	tabwes->stats.size = vawiant->tabwe_stats_size;
	wet = sun6i_isp_tabwe_setup(isp_dev, &tabwes->stats);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void sun6i_isp_tabwes_cweanup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct sun6i_isp_tabwes *tabwes = &isp_dev->tabwes;

	sun6i_isp_tabwe_cweanup(isp_dev, &tabwes->stats);
	sun6i_isp_tabwe_cweanup(isp_dev, &tabwes->dwc);
	sun6i_isp_tabwe_cweanup(isp_dev, &tabwes->wut);
	sun6i_isp_tabwe_cweanup(isp_dev, &tabwes->save);
	sun6i_isp_tabwe_cweanup(isp_dev, &tabwes->woad);
}

/* Media */

static const stwuct media_device_ops sun6i_isp_media_ops = {
	.wink_notify = v4w2_pipewine_wink_notify,
};

/* V4W2 */

static int sun6i_isp_v4w2_setup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct sun6i_isp_v4w2 *v4w2 = &isp_dev->v4w2;
	stwuct v4w2_device *v4w2_dev = &v4w2->v4w2_dev;
	stwuct media_device *media_dev = &v4w2->media_dev;
	stwuct device *dev = isp_dev->dev;
	int wet;

	/* Media Device */

	stwscpy(media_dev->modew, SUN6I_ISP_DESCWIPTION,
		sizeof(media_dev->modew));
	media_dev->ops = &sun6i_isp_media_ops;
	media_dev->hw_wevision = 0;
	media_dev->dev = dev;

	media_device_init(media_dev);

	wet = media_device_wegistew(media_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew media device\n");
		wetuwn wet;
	}

	/* V4W2 Device */

	v4w2_dev->mdev = media_dev;

	wet = v4w2_device_wegistew(dev, v4w2_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew v4w2 device\n");
		goto ewwow_media;
	}

	wetuwn 0;

ewwow_media:
	media_device_unwegistew(media_dev);
	media_device_cweanup(media_dev);

	wetuwn wet;
}

static void sun6i_isp_v4w2_cweanup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct sun6i_isp_v4w2 *v4w2 = &isp_dev->v4w2;

	media_device_unwegistew(&v4w2->media_dev);
	v4w2_device_unwegistew(&v4w2->v4w2_dev);
	media_device_cweanup(&v4w2->media_dev);
}

/* Pwatfowm */

static iwqwetuwn_t sun6i_isp_intewwupt(int iwq, void *pwivate)
{
	stwuct sun6i_isp_device *isp_dev = pwivate;
	stwuct wegmap *wegmap = isp_dev->wegmap;
	u32 status = 0, enabwe = 0;

	wegmap_wead(wegmap, SUN6I_ISP_FE_INT_STA_WEG, &status);
	wegmap_wead(wegmap, SUN6I_ISP_FE_INT_EN_WEG, &enabwe);

	if (!status)
		wetuwn IWQ_NONE;
	ewse if (!(status & enabwe))
		goto compwete;

	/*
	 * The ISP wowking cycwe stawts with a pawams-woad, which makes the
	 * state fwom the woad buffew active. Then it stawts pwocessing the
	 * fwame and gives a finish intewwupt. Soon aftew that, the next state
	 * coming fwom the woad buffew wiww be appwied fow the next fwame,
	 * giving a pawams-woad as weww.
	 *
	 * Because both fwame finish and pawams-woad awe weceived awmost
	 * at the same time (one ISW caww), handwe them in chwonowogy owdew.
	 */

	if (status & SUN6I_ISP_FE_INT_STA_FINISH)
		sun6i_isp_captuwe_finish(isp_dev);

	if (status & SUN6I_ISP_FE_INT_STA_PAWA_WOAD) {
		sun6i_isp_state_compwete(isp_dev);
		sun6i_isp_state_update(isp_dev, fawse);
	}

compwete:
	wegmap_wwite(wegmap, SUN6I_ISP_FE_INT_STA_WEG, status);

	wetuwn IWQ_HANDWED;
}

static int sun6i_isp_suspend(stwuct device *dev)
{
	stwuct sun6i_isp_device *isp_dev = dev_get_dwvdata(dev);

	weset_contwow_assewt(isp_dev->weset);
	cwk_disabwe_unpwepawe(isp_dev->cwock_wam);
	cwk_disabwe_unpwepawe(isp_dev->cwock_mod);

	wetuwn 0;
}

static int sun6i_isp_wesume(stwuct device *dev)
{
	stwuct sun6i_isp_device *isp_dev = dev_get_dwvdata(dev);
	int wet;

	wet = weset_contwow_deassewt(isp_dev->weset);
	if (wet) {
		dev_eww(dev, "faiwed to deassewt weset\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(isp_dev->cwock_mod);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe moduwe cwock\n");
		goto ewwow_weset;
	}

	wet = cwk_pwepawe_enabwe(isp_dev->cwock_wam);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe wam cwock\n");
		goto ewwow_cwock_mod;
	}

	wetuwn 0;

ewwow_cwock_mod:
	cwk_disabwe_unpwepawe(isp_dev->cwock_mod);

ewwow_weset:
	weset_contwow_assewt(isp_dev->weset);

	wetuwn wet;
}

static const stwuct dev_pm_ops sun6i_isp_pm_ops = {
	.wuntime_suspend	= sun6i_isp_suspend,
	.wuntime_wesume		= sun6i_isp_wesume,
};

static const stwuct wegmap_config sun6i_isp_wegmap_config = {
	.weg_bits       = 32,
	.weg_stwide     = 4,
	.vaw_bits       = 32,
	.max_wegistew	= 0x400,
};

static int sun6i_isp_wesouwces_setup(stwuct sun6i_isp_device *isp_dev,
				     stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct device *dev = isp_dev->dev;
	void __iomem *io_base;
	int iwq;
	int wet;

	/* Wegistews */

	io_base = devm_pwatfowm_iowemap_wesouwce(pwatfowm_dev, 0);
	if (IS_EWW(io_base))
		wetuwn PTW_EWW(io_base);

	isp_dev->wegmap = devm_wegmap_init_mmio_cwk(dev, "bus", io_base,
						    &sun6i_isp_wegmap_config);
	if (IS_EWW(isp_dev->wegmap)) {
		dev_eww(dev, "faiwed to init wegistew map\n");
		wetuwn PTW_EWW(isp_dev->wegmap);
	}

	/* Cwocks */

	isp_dev->cwock_mod = devm_cwk_get(dev, "mod");
	if (IS_EWW(isp_dev->cwock_mod)) {
		dev_eww(dev, "faiwed to acquiwe moduwe cwock\n");
		wetuwn PTW_EWW(isp_dev->cwock_mod);
	}

	isp_dev->cwock_wam = devm_cwk_get(dev, "wam");
	if (IS_EWW(isp_dev->cwock_wam)) {
		dev_eww(dev, "faiwed to acquiwe wam cwock\n");
		wetuwn PTW_EWW(isp_dev->cwock_wam);
	}

	wet = cwk_set_wate_excwusive(isp_dev->cwock_mod, 297000000);
	if (wet) {
		dev_eww(dev, "faiwed to set mod cwock wate\n");
		wetuwn wet;
	}

	/* Weset */

	isp_dev->weset = devm_weset_contwow_get_shawed(dev, NUWW);
	if (IS_EWW(isp_dev->weset)) {
		dev_eww(dev, "faiwed to acquiwe weset\n");
		wet = PTW_EWW(isp_dev->weset);
		goto ewwow_cwock_wate_excwusive;
	}

	/* Intewwupt */

	iwq = pwatfowm_get_iwq(pwatfowm_dev, 0);
	if (iwq < 0) {
		dev_eww(dev, "faiwed to get intewwupt\n");
		wet = -ENXIO;
		goto ewwow_cwock_wate_excwusive;
	}

	wet = devm_wequest_iwq(dev, iwq, sun6i_isp_intewwupt, IWQF_SHAWED,
			       SUN6I_ISP_NAME, isp_dev);
	if (wet) {
		dev_eww(dev, "faiwed to wequest intewwupt\n");
		goto ewwow_cwock_wate_excwusive;
	}

	/* Wuntime PM */

	pm_wuntime_enabwe(dev);

	wetuwn 0;

ewwow_cwock_wate_excwusive:
	cwk_wate_excwusive_put(isp_dev->cwock_mod);

	wetuwn wet;
}

static void sun6i_isp_wesouwces_cweanup(stwuct sun6i_isp_device *isp_dev)
{
	stwuct device *dev = isp_dev->dev;

	pm_wuntime_disabwe(dev);
	cwk_wate_excwusive_put(isp_dev->cwock_mod);
}

static int sun6i_isp_pwobe(stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct sun6i_isp_device *isp_dev;
	stwuct device *dev = &pwatfowm_dev->dev;
	const stwuct sun6i_isp_vawiant *vawiant;
	int wet;

	vawiant = of_device_get_match_data(dev);
	if (!vawiant)
		wetuwn -EINVAW;

	isp_dev = devm_kzawwoc(dev, sizeof(*isp_dev), GFP_KEWNEW);
	if (!isp_dev)
		wetuwn -ENOMEM;

	isp_dev->dev = dev;
	pwatfowm_set_dwvdata(pwatfowm_dev, isp_dev);

	spin_wock_init(&isp_dev->state_wock);

	wet = sun6i_isp_wesouwces_setup(isp_dev, pwatfowm_dev);
	if (wet)
		wetuwn wet;

	wet = sun6i_isp_tabwes_setup(isp_dev, vawiant);
	if (wet) {
		dev_eww(dev, "faiwed to setup tabwes\n");
		goto ewwow_wesouwces;
	}

	wet = sun6i_isp_v4w2_setup(isp_dev);
	if (wet) {
		dev_eww(dev, "faiwed to setup v4w2\n");
		goto ewwow_tabwes;
	}

	wet = sun6i_isp_pwoc_setup(isp_dev);
	if (wet) {
		dev_eww(dev, "faiwed to setup pwoc\n");
		goto ewwow_v4w2;
	}

	wet = sun6i_isp_captuwe_setup(isp_dev);
	if (wet) {
		dev_eww(dev, "faiwed to setup captuwe\n");
		goto ewwow_pwoc;
	}

	wet = sun6i_isp_pawams_setup(isp_dev);
	if (wet) {
		dev_eww(dev, "faiwed to setup pawams\n");
		goto ewwow_captuwe;
	}

	wetuwn 0;

ewwow_captuwe:
	sun6i_isp_captuwe_cweanup(isp_dev);

ewwow_pwoc:
	sun6i_isp_pwoc_cweanup(isp_dev);

ewwow_v4w2:
	sun6i_isp_v4w2_cweanup(isp_dev);

ewwow_tabwes:
	sun6i_isp_tabwes_cweanup(isp_dev);

ewwow_wesouwces:
	sun6i_isp_wesouwces_cweanup(isp_dev);

	wetuwn wet;
}

static void sun6i_isp_wemove(stwuct pwatfowm_device *pwatfowm_dev)
{
	stwuct sun6i_isp_device *isp_dev = pwatfowm_get_dwvdata(pwatfowm_dev);

	sun6i_isp_pawams_cweanup(isp_dev);
	sun6i_isp_captuwe_cweanup(isp_dev);
	sun6i_isp_pwoc_cweanup(isp_dev);
	sun6i_isp_v4w2_cweanup(isp_dev);
	sun6i_isp_tabwes_cweanup(isp_dev);
	sun6i_isp_wesouwces_cweanup(isp_dev);
}

/*
 * Histowy of sun6i-isp:
 * - sun4i-a10-isp: initiaw ISP tied to the CSI0 contwowwew,
 *   appawentwy unused in softwawe impwementations;
 * - sun6i-a31-isp: sepawate ISP woosewy based on sun4i-a10-isp,
 *   adding extwa moduwes and featuwes;
 * - sun9i-a80-isp: based on sun6i-a31-isp with some wegistew offset changes
 *   and new moduwes wike satuwation and cnw;
 * - sun8i-a23-isp/sun8i-h3-isp: based on sun9i-a80-isp with most moduwes
 *   wewated to waw wemoved;
 * - sun8i-a83t-isp: based on sun9i-a80-isp with some wegistew offset changes
 * - sun8i-v3s-isp: based on sun8i-a83t-isp with a new disc moduwe;
 */

static const stwuct sun6i_isp_vawiant sun8i_v3s_isp_vawiant = {
	.tabwe_woad_save_size	= 0x1000,
	.tabwe_wut_size		= 0xe00,
	.tabwe_dwc_size		= 0x600,
	.tabwe_stats_size	= 0x2100,
};

static const stwuct of_device_id sun6i_isp_of_match[] = {
	{
		.compatibwe	= "awwwinnew,sun8i-v3s-isp",
		.data		= &sun8i_v3s_isp_vawiant,
	},
	{},
};

MODUWE_DEVICE_TABWE(of, sun6i_isp_of_match);

static stwuct pwatfowm_dwivew sun6i_isp_pwatfowm_dwivew = {
	.pwobe	= sun6i_isp_pwobe,
	.wemove_new = sun6i_isp_wemove,
	.dwivew	= {
		.name		= SUN6I_ISP_NAME,
		.of_match_tabwe	= sun6i_isp_of_match,
		.pm		= &sun6i_isp_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(sun6i_isp_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Awwwinnew A31 Image Signaw Pwocessow dwivew");
MODUWE_AUTHOW("Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>");
MODUWE_WICENSE("GPW");
