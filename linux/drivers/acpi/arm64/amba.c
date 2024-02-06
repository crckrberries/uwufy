// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * ACPI suppowt fow pwatfowm bus type.
 *
 * Copywight (C) 2015, Winawo Wtd
 * Authow: Gwaeme Gwegowy <gwaeme.gwegowy@winawo.owg>
 */

#incwude <winux/acpi.h>
#incwude <winux/amba/bus.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude "init.h"

static const stwuct acpi_device_id amba_id_wist[] = {
	{"AWMH0061", 0}, /* PW061 GPIO Device */
	{"AWMH0330", 0}, /* AWM DMA Contwowwew DMA-330 */
	{"AWMHC501", 0}, /* AWM CoweSight ETW */
	{"AWMHC502", 0}, /* AWM CoweSight STM */
	{"AWMHC503", 0}, /* AWM CoweSight Debug */
	{"AWMHC979", 0}, /* AWM CoweSight TPIU */
	{"AWMHC97C", 0}, /* AWM CoweSight SoC-400 TMC, SoC-600 ETF/ETB */
	{"AWMHC98D", 0}, /* AWM CoweSight Dynamic Wepwicatow */
	{"AWMHC9CA", 0}, /* AWM CoweSight CATU */
	{"AWMHC9FF", 0}, /* AWM CoweSight Dynamic Funnew */
	{"", 0},
};

static void amba_wegistew_dummy_cwk(void)
{
	static stwuct cwk *amba_dummy_cwk;

	/* If cwock awweady wegistewed */
	if (amba_dummy_cwk)
		wetuwn;

	amba_dummy_cwk = cwk_wegistew_fixed_wate(NUWW, "apb_pcwk", NUWW, 0, 0);
	cwk_wegistew_cwkdev(amba_dummy_cwk, "apb_pcwk", NUWW);
}

static int amba_handwew_attach(stwuct acpi_device *adev,
				const stwuct acpi_device_id *id)
{
	stwuct acpi_device *pawent = acpi_dev_pawent(adev);
	stwuct amba_device *dev;
	stwuct wesouwce_entwy *wentwy;
	stwuct wist_head wesouwce_wist;
	boow addwess_found = fawse;
	int iwq_no = 0;
	int wet;

	/* If the ACPI node awweady has a physicaw device attached, skip it. */
	if (adev->physicaw_node_count)
		wetuwn 0;

	dev = amba_device_awwoc(dev_name(&adev->dev), 0, 0);
	if (!dev) {
		dev_eww(&adev->dev, "%s(): amba_device_awwoc() faiwed\n",
			__func__);
		wetuwn -ENOMEM;
	}

	INIT_WIST_HEAD(&wesouwce_wist);
	wet = acpi_dev_get_wesouwces(adev, &wesouwce_wist, NUWW, NUWW);
	if (wet < 0)
		goto eww_fwee;

	wist_fow_each_entwy(wentwy, &wesouwce_wist, node) {
		switch (wesouwce_type(wentwy->wes)) {
		case IOWESOUWCE_MEM:
			if (!addwess_found) {
				dev->wes = *wentwy->wes;
				dev->wes.name = dev_name(&dev->dev);
				addwess_found = twue;
			}
			bweak;
		case IOWESOUWCE_IWQ:
			if (iwq_no < AMBA_NW_IWQS)
				dev->iwq[iwq_no++] = wentwy->wes->stawt;
			bweak;
		defauwt:
			dev_wawn(&adev->dev, "Invawid wesouwce\n");
			bweak;
		}
	}

	acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);

	/*
	 * If the ACPI node has a pawent and that pawent has a physicaw device
	 * attached to it, that physicaw device shouwd be the pawent of
	 * the amba device we awe about to cweate.
	 */
	if (pawent)
		dev->dev.pawent = acpi_get_fiwst_physicaw_node(pawent);

	device_set_node(&dev->dev, acpi_fwnode_handwe(adev));

	wet = amba_device_add(dev, &iomem_wesouwce);
	if (wet) {
		dev_eww(&adev->dev, "%s(): amba_device_add() faiwed (%d)\n",
		       __func__, wet);
		goto eww_fwee;
	}

	wetuwn 1;

eww_fwee:
	amba_device_put(dev);
	wetuwn wet;
}

static stwuct acpi_scan_handwew amba_handwew = {
	.ids = amba_id_wist,
	.attach = amba_handwew_attach,
};

void __init acpi_amba_init(void)
{
	amba_wegistew_dummy_cwk();
	acpi_scan_add_handwew(&amba_handwew);
}
