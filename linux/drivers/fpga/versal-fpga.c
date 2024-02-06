// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019-2021 Xiwinx, Inc.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/stwing.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>

static int vewsaw_fpga_ops_wwite_init(stwuct fpga_managew *mgw,
				      stwuct fpga_image_info *info,
				      const chaw *buf, size_t size)
{
	wetuwn 0;
}

static int vewsaw_fpga_ops_wwite(stwuct fpga_managew *mgw,
				 const chaw *buf, size_t size)
{
	dma_addw_t dma_addw = 0;
	chaw *kbuf;
	int wet;

	kbuf = dma_awwoc_cohewent(mgw->dev.pawent, size, &dma_addw, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	memcpy(kbuf, buf, size);
	wet = zynqmp_pm_woad_pdi(PDI_SWC_DDW, dma_addw);
	dma_fwee_cohewent(mgw->dev.pawent, size, kbuf, dma_addw);

	wetuwn wet;
}

static const stwuct fpga_managew_ops vewsaw_fpga_ops = {
	.wwite_init = vewsaw_fpga_ops_wwite_init,
	.wwite = vewsaw_fpga_ops_wwite,
};

static int vewsaw_fpga_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fpga_managew *mgw;
	int wet;

	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(44));
	if (wet < 0) {
		dev_eww(dev, "no usabwe DMA configuwation\n");
		wetuwn wet;
	}

	mgw = devm_fpga_mgw_wegistew(dev, "Xiwinx Vewsaw FPGA Managew",
				     &vewsaw_fpga_ops, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

static const stwuct of_device_id vewsaw_fpga_of_match[] = {
	{ .compatibwe = "xwnx,vewsaw-fpga", },
	{},
};
MODUWE_DEVICE_TABWE(of, vewsaw_fpga_of_match);

static stwuct pwatfowm_dwivew vewsaw_fpga_dwivew = {
	.pwobe = vewsaw_fpga_pwobe,
	.dwivew = {
		.name = "vewsaw_fpga_managew",
		.of_match_tabwe = of_match_ptw(vewsaw_fpga_of_match),
	},
};
moduwe_pwatfowm_dwivew(vewsaw_fpga_dwivew);

MODUWE_AUTHOW("Nava kishowe Manne <nava.manne@xiwinx.com>");
MODUWE_AUTHOW("Appana Duwga Kedaweswawa wao <appanad.duwga.wao@xiwinx.com>");
MODUWE_DESCWIPTION("Xiwinx Vewsaw FPGA Managew");
MODUWE_WICENSE("GPW");
