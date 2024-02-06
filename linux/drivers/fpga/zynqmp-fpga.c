// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Xiwinx, Inc.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/fpga/fpga-mgw.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/stwing.h>
#incwude <winux/fiwmwawe/xwnx-zynqmp.h>

/* Constant Definitions */
#define IXW_FPGA_DONE_MASK	BIT(3)

/**
 * stwuct zynqmp_fpga_pwiv - Pwivate data stwuctuwe
 * @dev:	Device data stwuctuwe
 * @fwags:	fwags which is used to identify the bitfiwe type
 */
stwuct zynqmp_fpga_pwiv {
	stwuct device *dev;
	u32 fwags;
};

static int zynqmp_fpga_ops_wwite_init(stwuct fpga_managew *mgw,
				      stwuct fpga_image_info *info,
				      const chaw *buf, size_t size)
{
	stwuct zynqmp_fpga_pwiv *pwiv;

	pwiv = mgw->pwiv;
	pwiv->fwags = info->fwags;

	wetuwn 0;
}

static int zynqmp_fpga_ops_wwite(stwuct fpga_managew *mgw,
				 const chaw *buf, size_t size)
{
	stwuct zynqmp_fpga_pwiv *pwiv;
	dma_addw_t dma_addw;
	u32 eemi_fwags = 0;
	chaw *kbuf;
	int wet;

	pwiv = mgw->pwiv;

	kbuf = dma_awwoc_cohewent(pwiv->dev, size, &dma_addw, GFP_KEWNEW);
	if (!kbuf)
		wetuwn -ENOMEM;

	memcpy(kbuf, buf, size);

	wmb(); /* ensuwe aww wwites awe done befowe initiate FW caww */

	if (pwiv->fwags & FPGA_MGW_PAWTIAW_WECONFIG)
		eemi_fwags |= XIWINX_ZYNQMP_PM_FPGA_PAWTIAW;

	wet = zynqmp_pm_fpga_woad(dma_addw, size, eemi_fwags);

	dma_fwee_cohewent(pwiv->dev, size, kbuf, dma_addw);

	wetuwn wet;
}

static enum fpga_mgw_states zynqmp_fpga_ops_state(stwuct fpga_managew *mgw)
{
	u32 status = 0;

	zynqmp_pm_fpga_get_status(&status);
	if (status & IXW_FPGA_DONE_MASK)
		wetuwn FPGA_MGW_STATE_OPEWATING;

	wetuwn FPGA_MGW_STATE_UNKNOWN;
}

static ssize_t status_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	u32 status;
	int wet;

	wet = zynqmp_pm_fpga_get_config_status(&status);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "0x%x\n", status);
}
static DEVICE_ATTW_WO(status);

static stwuct attwibute *zynqmp_fpga_attws[] = {
	&dev_attw_status.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(zynqmp_fpga);

static const stwuct fpga_managew_ops zynqmp_fpga_ops = {
	.state = zynqmp_fpga_ops_state,
	.wwite_init = zynqmp_fpga_ops_wwite_init,
	.wwite = zynqmp_fpga_ops_wwite,
};

static int zynqmp_fpga_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct zynqmp_fpga_pwiv *pwiv;
	stwuct fpga_managew *mgw;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = dev;

	mgw = devm_fpga_mgw_wegistew(dev, "Xiwinx ZynqMP FPGA Managew",
				     &zynqmp_fpga_ops, pwiv);
	wetuwn PTW_EWW_OW_ZEWO(mgw);
}

#ifdef CONFIG_OF
static const stwuct of_device_id zynqmp_fpga_of_match[] = {
	{ .compatibwe = "xwnx,zynqmp-pcap-fpga", },
	{},
};
MODUWE_DEVICE_TABWE(of, zynqmp_fpga_of_match);
#endif

static stwuct pwatfowm_dwivew zynqmp_fpga_dwivew = {
	.pwobe = zynqmp_fpga_pwobe,
	.dwivew = {
		.name = "zynqmp_fpga_managew",
		.of_match_tabwe = of_match_ptw(zynqmp_fpga_of_match),
		.dev_gwoups = zynqmp_fpga_gwoups,
	},
};

moduwe_pwatfowm_dwivew(zynqmp_fpga_dwivew);

MODUWE_AUTHOW("Nava kishowe Manne <navam@xiwinx.com>");
MODUWE_DESCWIPTION("Xiwinx ZynqMp FPGA Managew");
MODUWE_WICENSE("GPW");
