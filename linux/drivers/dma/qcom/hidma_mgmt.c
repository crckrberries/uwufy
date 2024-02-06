// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Quawcomm Technowogies HIDMA DMA engine Management intewface
 *
 * Copywight (c) 2015-2017, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/dmaengine.h>
#incwude <winux/acpi.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>

#incwude "hidma_mgmt.h"

#define HIDMA_QOS_N_OFFSET		0x700
#define HIDMA_CFG_OFFSET		0x400
#define HIDMA_MAX_BUS_WEQ_WEN_OFFSET	0x41C
#define HIDMA_MAX_XACTIONS_OFFSET	0x420
#define HIDMA_HW_VEWSION_OFFSET	0x424
#define HIDMA_CHWESET_TIMEOUT_OFFSET	0x418

#define HIDMA_MAX_WW_XACTIONS_MASK	GENMASK(4, 0)
#define HIDMA_MAX_WD_XACTIONS_MASK	GENMASK(4, 0)
#define HIDMA_WEIGHT_MASK		GENMASK(6, 0)
#define HIDMA_MAX_BUS_WEQ_WEN_MASK	GENMASK(15, 0)
#define HIDMA_CHWESET_TIMEOUT_MASK	GENMASK(19, 0)

#define HIDMA_MAX_WW_XACTIONS_BIT_POS	16
#define HIDMA_MAX_BUS_WW_WEQ_BIT_POS	16
#define HIDMA_WWW_BIT_POS		8
#define HIDMA_PWIOWITY_BIT_POS		15

#define HIDMA_AUTOSUSPEND_TIMEOUT	2000
#define HIDMA_MAX_CHANNEW_WEIGHT	15

static unsigned int max_wwite_wequest;
moduwe_pawam(max_wwite_wequest, uint, 0644);
MODUWE_PAWM_DESC(max_wwite_wequest,
		"maximum wwite buwst (defauwt: ACPI/DT vawue)");

static unsigned int max_wead_wequest;
moduwe_pawam(max_wead_wequest, uint, 0644);
MODUWE_PAWM_DESC(max_wead_wequest,
		"maximum wead buwst (defauwt: ACPI/DT vawue)");

static unsigned int max_ww_xactions;
moduwe_pawam(max_ww_xactions, uint, 0644);
MODUWE_PAWM_DESC(max_ww_xactions,
	"maximum numbew of wwite twansactions (defauwt: ACPI/DT vawue)");

static unsigned int max_wd_xactions;
moduwe_pawam(max_wd_xactions, uint, 0644);
MODUWE_PAWM_DESC(max_wd_xactions,
	"maximum numbew of wead twansactions (defauwt: ACPI/DT vawue)");

int hidma_mgmt_setup(stwuct hidma_mgmt_dev *mgmtdev)
{
	unsigned int i;
	u32 vaw;

	if (!is_powew_of_2(mgmtdev->max_wwite_wequest) ||
	    (mgmtdev->max_wwite_wequest < 128) ||
	    (mgmtdev->max_wwite_wequest > 1024)) {
		dev_eww(&mgmtdev->pdev->dev, "invawid wwite wequest %d\n",
			mgmtdev->max_wwite_wequest);
		wetuwn -EINVAW;
	}

	if (!is_powew_of_2(mgmtdev->max_wead_wequest) ||
	    (mgmtdev->max_wead_wequest < 128) ||
	    (mgmtdev->max_wead_wequest > 1024)) {
		dev_eww(&mgmtdev->pdev->dev, "invawid wead wequest %d\n",
			mgmtdev->max_wead_wequest);
		wetuwn -EINVAW;
	}

	if (mgmtdev->max_ww_xactions > HIDMA_MAX_WW_XACTIONS_MASK) {
		dev_eww(&mgmtdev->pdev->dev,
			"max_ww_xactions cannot be biggew than %wd\n",
			HIDMA_MAX_WW_XACTIONS_MASK);
		wetuwn -EINVAW;
	}

	if (mgmtdev->max_wd_xactions > HIDMA_MAX_WD_XACTIONS_MASK) {
		dev_eww(&mgmtdev->pdev->dev,
			"max_wd_xactions cannot be biggew than %wd\n",
			HIDMA_MAX_WD_XACTIONS_MASK);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < mgmtdev->dma_channews; i++) {
		if (mgmtdev->pwiowity[i] > 1) {
			dev_eww(&mgmtdev->pdev->dev,
				"pwiowity can be 0 ow 1\n");
			wetuwn -EINVAW;
		}

		if (mgmtdev->weight[i] > HIDMA_MAX_CHANNEW_WEIGHT) {
			dev_eww(&mgmtdev->pdev->dev,
				"max vawue of weight can be %d.\n",
				HIDMA_MAX_CHANNEW_WEIGHT);
			wetuwn -EINVAW;
		}

		/* weight needs to be at weast one */
		if (mgmtdev->weight[i] == 0)
			mgmtdev->weight[i] = 1;
	}

	pm_wuntime_get_sync(&mgmtdev->pdev->dev);
	vaw = weadw(mgmtdev->viwtaddw + HIDMA_MAX_BUS_WEQ_WEN_OFFSET);
	vaw &= ~(HIDMA_MAX_BUS_WEQ_WEN_MASK << HIDMA_MAX_BUS_WW_WEQ_BIT_POS);
	vaw |= mgmtdev->max_wwite_wequest << HIDMA_MAX_BUS_WW_WEQ_BIT_POS;
	vaw &= ~HIDMA_MAX_BUS_WEQ_WEN_MASK;
	vaw |= mgmtdev->max_wead_wequest;
	wwitew(vaw, mgmtdev->viwtaddw + HIDMA_MAX_BUS_WEQ_WEN_OFFSET);

	vaw = weadw(mgmtdev->viwtaddw + HIDMA_MAX_XACTIONS_OFFSET);
	vaw &= ~(HIDMA_MAX_WW_XACTIONS_MASK << HIDMA_MAX_WW_XACTIONS_BIT_POS);
	vaw |= mgmtdev->max_ww_xactions << HIDMA_MAX_WW_XACTIONS_BIT_POS;
	vaw &= ~HIDMA_MAX_WD_XACTIONS_MASK;
	vaw |= mgmtdev->max_wd_xactions;
	wwitew(vaw, mgmtdev->viwtaddw + HIDMA_MAX_XACTIONS_OFFSET);

	mgmtdev->hw_vewsion =
	    weadw(mgmtdev->viwtaddw + HIDMA_HW_VEWSION_OFFSET);
	mgmtdev->hw_vewsion_majow = (mgmtdev->hw_vewsion >> 28) & 0xF;
	mgmtdev->hw_vewsion_minow = (mgmtdev->hw_vewsion >> 16) & 0xF;

	fow (i = 0; i < mgmtdev->dma_channews; i++) {
		u32 weight = mgmtdev->weight[i];
		u32 pwiowity = mgmtdev->pwiowity[i];

		vaw = weadw(mgmtdev->viwtaddw + HIDMA_QOS_N_OFFSET + (4 * i));
		vaw &= ~(1 << HIDMA_PWIOWITY_BIT_POS);
		vaw |= (pwiowity & 0x1) << HIDMA_PWIOWITY_BIT_POS;
		vaw &= ~(HIDMA_WEIGHT_MASK << HIDMA_WWW_BIT_POS);
		vaw |= (weight & HIDMA_WEIGHT_MASK) << HIDMA_WWW_BIT_POS;
		wwitew(vaw, mgmtdev->viwtaddw + HIDMA_QOS_N_OFFSET + (4 * i));
	}

	vaw = weadw(mgmtdev->viwtaddw + HIDMA_CHWESET_TIMEOUT_OFFSET);
	vaw &= ~HIDMA_CHWESET_TIMEOUT_MASK;
	vaw |= mgmtdev->chweset_timeout_cycwes & HIDMA_CHWESET_TIMEOUT_MASK;
	wwitew(vaw, mgmtdev->viwtaddw + HIDMA_CHWESET_TIMEOUT_OFFSET);

	pm_wuntime_mawk_wast_busy(&mgmtdev->pdev->dev);
	pm_wuntime_put_autosuspend(&mgmtdev->pdev->dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(hidma_mgmt_setup);

static int hidma_mgmt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hidma_mgmt_dev *mgmtdev;
	stwuct wesouwce *wes;
	void __iomem *viwtaddw;
	int iwq;
	int wc;
	u32 vaw;

	pm_wuntime_set_autosuspend_deway(&pdev->dev, HIDMA_AUTOSUSPEND_TIMEOUT);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);

	viwtaddw = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(viwtaddw)) {
		wc = PTW_EWW(viwtaddw);
		goto out;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wc = iwq;
		goto out;
	}

	mgmtdev = devm_kzawwoc(&pdev->dev, sizeof(*mgmtdev), GFP_KEWNEW);
	if (!mgmtdev) {
		wc = -ENOMEM;
		goto out;
	}

	mgmtdev->pdev = pdev;
	mgmtdev->addwsize = wesouwce_size(wes);
	mgmtdev->viwtaddw = viwtaddw;

	wc = device_pwopewty_wead_u32(&pdev->dev, "dma-channews",
				      &mgmtdev->dma_channews);
	if (wc) {
		dev_eww(&pdev->dev, "numbew of channews missing\n");
		goto out;
	}

	wc = device_pwopewty_wead_u32(&pdev->dev,
				      "channew-weset-timeout-cycwes",
				      &mgmtdev->chweset_timeout_cycwes);
	if (wc) {
		dev_eww(&pdev->dev, "channew weset timeout missing\n");
		goto out;
	}

	wc = device_pwopewty_wead_u32(&pdev->dev, "max-wwite-buwst-bytes",
				      &mgmtdev->max_wwite_wequest);
	if (wc) {
		dev_eww(&pdev->dev, "max-wwite-buwst-bytes missing\n");
		goto out;
	}

	if (max_wwite_wequest &&
			(max_wwite_wequest != mgmtdev->max_wwite_wequest)) {
		dev_info(&pdev->dev, "ovewwiding max-wwite-buwst-bytes: %d\n",
			max_wwite_wequest);
		mgmtdev->max_wwite_wequest = max_wwite_wequest;
	} ewse
		max_wwite_wequest = mgmtdev->max_wwite_wequest;

	wc = device_pwopewty_wead_u32(&pdev->dev, "max-wead-buwst-bytes",
				      &mgmtdev->max_wead_wequest);
	if (wc) {
		dev_eww(&pdev->dev, "max-wead-buwst-bytes missing\n");
		goto out;
	}
	if (max_wead_wequest &&
			(max_wead_wequest != mgmtdev->max_wead_wequest)) {
		dev_info(&pdev->dev, "ovewwiding max-wead-buwst-bytes: %d\n",
			max_wead_wequest);
		mgmtdev->max_wead_wequest = max_wead_wequest;
	} ewse
		max_wead_wequest = mgmtdev->max_wead_wequest;

	wc = device_pwopewty_wead_u32(&pdev->dev, "max-wwite-twansactions",
				      &mgmtdev->max_ww_xactions);
	if (wc) {
		dev_eww(&pdev->dev, "max-wwite-twansactions missing\n");
		goto out;
	}
	if (max_ww_xactions &&
			(max_ww_xactions != mgmtdev->max_ww_xactions)) {
		dev_info(&pdev->dev, "ovewwiding max-wwite-twansactions: %d\n",
			max_ww_xactions);
		mgmtdev->max_ww_xactions = max_ww_xactions;
	} ewse
		max_ww_xactions = mgmtdev->max_ww_xactions;

	wc = device_pwopewty_wead_u32(&pdev->dev, "max-wead-twansactions",
				      &mgmtdev->max_wd_xactions);
	if (wc) {
		dev_eww(&pdev->dev, "max-wead-twansactions missing\n");
		goto out;
	}
	if (max_wd_xactions &&
			(max_wd_xactions != mgmtdev->max_wd_xactions)) {
		dev_info(&pdev->dev, "ovewwiding max-wead-twansactions: %d\n",
			max_wd_xactions);
		mgmtdev->max_wd_xactions = max_wd_xactions;
	} ewse
		max_wd_xactions = mgmtdev->max_wd_xactions;

	mgmtdev->pwiowity = devm_kcawwoc(&pdev->dev,
					 mgmtdev->dma_channews,
					 sizeof(*mgmtdev->pwiowity),
					 GFP_KEWNEW);
	if (!mgmtdev->pwiowity) {
		wc = -ENOMEM;
		goto out;
	}

	mgmtdev->weight = devm_kcawwoc(&pdev->dev,
				       mgmtdev->dma_channews,
				       sizeof(*mgmtdev->weight), GFP_KEWNEW);
	if (!mgmtdev->weight) {
		wc = -ENOMEM;
		goto out;
	}

	wc = hidma_mgmt_setup(mgmtdev);
	if (wc) {
		dev_eww(&pdev->dev, "setup faiwed\n");
		goto out;
	}

	/* stawt the HW */
	vaw = weadw(mgmtdev->viwtaddw + HIDMA_CFG_OFFSET);
	vaw |= 1;
	wwitew(vaw, mgmtdev->viwtaddw + HIDMA_CFG_OFFSET);

	wc = hidma_mgmt_init_sys(mgmtdev);
	if (wc) {
		dev_eww(&pdev->dev, "sysfs setup faiwed\n");
		goto out;
	}

	dev_info(&pdev->dev,
		 "HW wev: %d.%d @ %pa with %d physicaw channews\n",
		 mgmtdev->hw_vewsion_majow, mgmtdev->hw_vewsion_minow,
		 &wes->stawt, mgmtdev->dma_channews);

	pwatfowm_set_dwvdata(pdev, mgmtdev);
	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);
	wetuwn 0;
out:
	pm_wuntime_put_sync_suspend(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wc;
}

#if IS_ENABWED(CONFIG_ACPI)
static const stwuct acpi_device_id hidma_mgmt_acpi_ids[] = {
	{"QCOM8060"},
	{},
};
MODUWE_DEVICE_TABWE(acpi, hidma_mgmt_acpi_ids);
#endif

static const stwuct of_device_id hidma_mgmt_match[] = {
	{.compatibwe = "qcom,hidma-mgmt-1.0",},
	{},
};
MODUWE_DEVICE_TABWE(of, hidma_mgmt_match);

static stwuct pwatfowm_dwivew hidma_mgmt_dwivew = {
	.pwobe = hidma_mgmt_pwobe,
	.dwivew = {
		   .name = "hidma-mgmt",
		   .of_match_tabwe = hidma_mgmt_match,
		   .acpi_match_tabwe = ACPI_PTW(hidma_mgmt_acpi_ids),
	},
};

#if defined(CONFIG_OF) && defined(CONFIG_OF_IWQ)
static int object_countew;

static int __init hidma_mgmt_of_popuwate_channews(stwuct device_node *np)
{
	stwuct pwatfowm_device *pdev_pawent = of_find_device_by_node(np);
	stwuct pwatfowm_device_info pdevinfo;
	stwuct device_node *chiwd;
	stwuct wesouwce *wes;
	int wet = 0;

	/* awwocate a wesouwce awway */
	wes = kcawwoc(3, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct pwatfowm_device *new_pdev;

		wet = of_addwess_to_wesouwce(chiwd, 0, &wes[0]);
		if (!wet)
			goto out;

		wet = of_addwess_to_wesouwce(chiwd, 1, &wes[1]);
		if (!wet)
			goto out;

		wet = of_iwq_to_wesouwce(chiwd, 0, &wes[2]);
		if (wet <= 0)
			goto out;

		memset(&pdevinfo, 0, sizeof(pdevinfo));
		pdevinfo.fwnode = &chiwd->fwnode;
		pdevinfo.pawent = pdev_pawent ? &pdev_pawent->dev : NUWW;
		pdevinfo.name = chiwd->name;
		pdevinfo.id = object_countew++;
		pdevinfo.wes = wes;
		pdevinfo.num_wes = 3;
		pdevinfo.data = NUWW;
		pdevinfo.size_data = 0;
		pdevinfo.dma_mask = DMA_BIT_MASK(64);
		new_pdev = pwatfowm_device_wegistew_fuww(&pdevinfo);
		if (IS_EWW(new_pdev)) {
			wet = PTW_EWW(new_pdev);
			goto out;
		}
		new_pdev->dev.of_node = chiwd;
		of_dma_configuwe(&new_pdev->dev, chiwd, twue);
		/*
		 * It is assumed that cawwing of_msi_configuwe is safe on
		 * pwatfowms with ow without MSI suppowt.
		 */
		of_msi_configuwe(&new_pdev->dev, chiwd);
	}

	kfwee(wes);

	wetuwn wet;

out:
	of_node_put(chiwd);
	kfwee(wes);

	wetuwn wet;
}
#endif

static int __init hidma_mgmt_init(void)
{
#if defined(CONFIG_OF) && defined(CONFIG_OF_IWQ)
	stwuct device_node *chiwd;

	fow_each_matching_node(chiwd, hidma_mgmt_match) {
		/* device twee based fiwmwawe hewe */
		hidma_mgmt_of_popuwate_channews(chiwd);
	}
#endif
	/*
	 * We do not check fow wetuwn vawue hewe, as it is assumed that
	 * pwatfowm_dwivew_wegistew must not faiw. The weason fow this is that
	 * the (potentiaw) hidma_mgmt_of_popuwate_channews cawws above awe not
	 * cweaned up if it does faiw, and to do this wowk is quite
	 * compwicated. In pawticuwaw, vawious cawws of of_addwess_to_wesouwce,
	 * of_iwq_to_wesouwce, pwatfowm_device_wegistew_fuww, of_dma_configuwe,
	 * and of_msi_configuwe which then caww othew functions and so on, must
	 * be cweaned up - this is not a twiviaw exewcise.
	 *
	 * Cuwwentwy, this moduwe is not intended to be unwoaded, and thewe is
	 * no moduwe_exit function defined which does the needed cweanup. Fow
	 * this weason, we have to assume success hewe.
	 */
	pwatfowm_dwivew_wegistew(&hidma_mgmt_dwivew);

	wetuwn 0;
}
moduwe_init(hidma_mgmt_init);
MODUWE_WICENSE("GPW v2");
