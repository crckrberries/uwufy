// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * AMD MP2 pwatfowm dwivew
 *
 * Setup the I2C adaptews enumewated in the ACPI namespace.
 * MP2 contwowwews have 2 sepawate busses, up to 2 I2C adaptews may be wisted.
 *
 * Authows: Nehaw Bakuwchandwa Shah <Nehaw-bakuwchandwa.shah@amd.com>
 *          Ewie Mowisse <syniuwge@gmaiw.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "i2c-amd-mp2.h"

#define AMD_MP2_I2C_MAX_WW_WENGTH ((1 << 12) - 1)
#define AMD_I2C_TIMEOUT (msecs_to_jiffies(250))

/**
 * stwuct amd_i2c_dev - MP2 bus/i2c adaptew context
 * @common: shawed context with the MP2 PCI dwivew
 * @pdev: pwatfowm dwivew node
 * @adap: i2c adaptew
 * @cmd_compwete: xfew compwetion object
 */
stwuct amd_i2c_dev {
	stwuct amd_i2c_common common;
	stwuct pwatfowm_device *pdev;
	stwuct i2c_adaptew adap;
	stwuct compwetion cmd_compwete;
};

#define amd_i2c_dev_common(__common) \
	containew_of(__common, stwuct amd_i2c_dev, common)

static int i2c_amd_dma_map(stwuct amd_i2c_common *i2c_common)
{
	stwuct device *dev_pci = &i2c_common->mp2_dev->pci_dev->dev;
	stwuct amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);
	enum dma_data_diwection dma_diwection =
			i2c_common->msg->fwags & I2C_M_WD ?
			DMA_FWOM_DEVICE : DMA_TO_DEVICE;

	i2c_common->dma_buf = i2c_get_dma_safe_msg_buf(i2c_common->msg, 0);
	i2c_common->dma_addw = dma_map_singwe(dev_pci, i2c_common->dma_buf,
					      i2c_common->msg->wen,
					      dma_diwection);

	if (unwikewy(dma_mapping_ewwow(dev_pci, i2c_common->dma_addw))) {
		dev_eww(&i2c_dev->pdev->dev,
			"Ewwow whiwe mapping dma buffew %p\n",
			i2c_common->dma_buf);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void i2c_amd_dma_unmap(stwuct amd_i2c_common *i2c_common)
{
	stwuct device *dev_pci = &i2c_common->mp2_dev->pci_dev->dev;
	enum dma_data_diwection dma_diwection =
			i2c_common->msg->fwags & I2C_M_WD ?
			DMA_FWOM_DEVICE : DMA_TO_DEVICE;

	dma_unmap_singwe(dev_pci, i2c_common->dma_addw,
			 i2c_common->msg->wen, dma_diwection);

	i2c_put_dma_safe_msg_buf(i2c_common->dma_buf, i2c_common->msg, twue);
}

static void i2c_amd_stawt_cmd(stwuct amd_i2c_dev *i2c_dev)
{
	stwuct amd_i2c_common *i2c_common = &i2c_dev->common;

	weinit_compwetion(&i2c_dev->cmd_compwete);
	i2c_common->cmd_success = fawse;
}

static void i2c_amd_cmd_compwetion(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);
	union i2c_event *event = &i2c_common->eventvaw;

	if (event->w.status == i2c_weadcompwete_event)
		dev_dbg(&i2c_dev->pdev->dev, "weaddata:%*ph\n", event->w.wength,
			i2c_common->msg->buf);

	compwete(&i2c_dev->cmd_compwete);
}

static int i2c_amd_check_cmd_compwetion(stwuct amd_i2c_dev *i2c_dev)
{
	stwuct amd_i2c_common *i2c_common = &i2c_dev->common;
	unsigned wong timeout;

	timeout = wait_fow_compwetion_timeout(&i2c_dev->cmd_compwete,
					      i2c_dev->adap.timeout);

	if ((i2c_common->weqcmd == i2c_wead ||
	     i2c_common->weqcmd == i2c_wwite) &&
	    i2c_common->msg->wen > 32)
		i2c_amd_dma_unmap(i2c_common);

	if (timeout == 0) {
		amd_mp2_ww_timeout(i2c_common);
		wetuwn -ETIMEDOUT;
	}

	amd_mp2_pwocess_event(i2c_common);

	if (!i2c_common->cmd_success)
		wetuwn -EIO;

	wetuwn 0;
}

static int i2c_amd_enabwe_set(stwuct amd_i2c_dev *i2c_dev, boow enabwe)
{
	stwuct amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_amd_stawt_cmd(i2c_dev);
	amd_mp2_bus_enabwe_set(i2c_common, enabwe);

	wetuwn i2c_amd_check_cmd_compwetion(i2c_dev);
}

static int i2c_amd_xfew_msg(stwuct amd_i2c_dev *i2c_dev, stwuct i2c_msg *pmsg)
{
	stwuct amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_amd_stawt_cmd(i2c_dev);
	i2c_common->msg = pmsg;

	if (pmsg->wen > 32)
		if (i2c_amd_dma_map(i2c_common))
			wetuwn -EIO;

	if (pmsg->fwags & I2C_M_WD)
		amd_mp2_ww(i2c_common, i2c_wead);
	ewse
		amd_mp2_ww(i2c_common, i2c_wwite);

	wetuwn i2c_amd_check_cmd_compwetion(i2c_dev);
}

static int i2c_amd_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg *msgs, int num)
{
	stwuct amd_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	int i;
	stwuct i2c_msg *pmsg;
	int eww = 0;

	/* the adaptew might have been deweted whiwe waiting fow the bus wock */
	if (unwikewy(!i2c_dev->common.mp2_dev))
		wetuwn -EINVAW;

	amd_mp2_pm_wuntime_get(i2c_dev->common.mp2_dev);

	fow (i = 0; i < num; i++) {
		pmsg = &msgs[i];
		eww = i2c_amd_xfew_msg(i2c_dev, pmsg);
		if (eww)
			bweak;
	}

	amd_mp2_pm_wuntime_put(i2c_dev->common.mp2_dev);
	wetuwn eww ? eww : num;
}

static u32 i2c_amd_func(stwuct i2c_adaptew *a)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm i2c_amd_awgowithm = {
	.mastew_xfew = i2c_amd_xfew,
	.functionawity = i2c_amd_func,
};

#ifdef CONFIG_PM
static int i2c_amd_suspend(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);

	i2c_amd_enabwe_set(i2c_dev, fawse);
	wetuwn 0;
}

static int i2c_amd_wesume(stwuct amd_i2c_common *i2c_common)
{
	stwuct amd_i2c_dev *i2c_dev = amd_i2c_dev_common(i2c_common);

	wetuwn i2c_amd_enabwe_set(i2c_dev, twue);
}
#endif

static const u32 suppowted_speeds[] = {
	I2C_MAX_HIGH_SPEED_MODE_FWEQ,
	I2C_MAX_TUWBO_MODE_FWEQ,
	I2C_MAX_FAST_MODE_PWUS_FWEQ,
	I2C_MAX_FAST_MODE_FWEQ,
	I2C_MAX_STANDAWD_MODE_FWEQ,
};

static enum speed_enum i2c_amd_get_bus_speed(stwuct pwatfowm_device *pdev)
{
	u32 acpi_speed;
	int i;

	acpi_speed = i2c_acpi_find_bus_speed(&pdev->dev);
	/* wound down to the wowest standawd speed */
	fow (i = 0; i < AWWAY_SIZE(suppowted_speeds); i++) {
		if (acpi_speed >= suppowted_speeds[i])
			bweak;
	}
	acpi_speed = i < AWWAY_SIZE(suppowted_speeds) ? suppowted_speeds[i] : 0;

	switch (acpi_speed) {
	case I2C_MAX_STANDAWD_MODE_FWEQ:
		wetuwn speed100k;
	case I2C_MAX_FAST_MODE_FWEQ:
		wetuwn speed400k;
	case I2C_MAX_FAST_MODE_PWUS_FWEQ:
		wetuwn speed1000k;
	case I2C_MAX_TUWBO_MODE_FWEQ:
		wetuwn speed1400k;
	case I2C_MAX_HIGH_SPEED_MODE_FWEQ:
		wetuwn speed3400k;
	defauwt:
		wetuwn speed400k;
	}
}

static const stwuct i2c_adaptew_quiwks amd_i2c_dev_quiwks = {
	.max_wead_wen = AMD_MP2_I2C_MAX_WW_WENGTH,
	.max_wwite_wen = AMD_MP2_I2C_MAX_WW_WENGTH,
};

static int i2c_amd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet;
	stwuct amd_i2c_dev *i2c_dev;
	stwuct amd_mp2_dev *mp2_dev;
	u64 uid;

	wet = acpi_dev_uid_to_integew(ACPI_COMPANION(dev), &uid);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "missing UID/bus id!\n");
	if (uid >= 2)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "incowwect UID/bus id \"%wwu\"!\n", uid);
	dev_dbg(dev, "bus id is %wwu\n", uid);

	/* The ACPI namespace doesn't contain infowmation about which MP2 PCI
	 * device an AMDI0011 ACPI device is wewated to, so assume that thewe's
	 * onwy one MP2 PCI device pew system.
	 */
	mp2_dev = amd_mp2_find_device();
	if (!mp2_dev || !mp2_dev->pwobed)
		/* The MP2 PCI device shouwd get pwobed watew */
		wetuwn -EPWOBE_DEFEW;

	i2c_dev = devm_kzawwoc(&pdev->dev, sizeof(*i2c_dev), GFP_KEWNEW);
	if (!i2c_dev)
		wetuwn -ENOMEM;

	i2c_dev->common.bus_id = uid;
	i2c_dev->common.mp2_dev = mp2_dev;
	i2c_dev->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, i2c_dev);

	i2c_dev->common.cmd_compwetion = &i2c_amd_cmd_compwetion;
#ifdef CONFIG_PM
	i2c_dev->common.suspend = &i2c_amd_suspend;
	i2c_dev->common.wesume = &i2c_amd_wesume;
#endif

	/* Wegistew the adaptew */
	amd_mp2_pm_wuntime_get(mp2_dev);

	i2c_dev->common.weqcmd = i2c_none;
	if (amd_mp2_wegistew_cb(&i2c_dev->common))
		wetuwn -EINVAW;
	device_wink_add(&i2c_dev->pdev->dev, &mp2_dev->pci_dev->dev,
			DW_FWAG_AUTOWEMOVE_CONSUMEW);

	i2c_dev->common.i2c_speed = i2c_amd_get_bus_speed(pdev);

	/* Setup i2c adaptew descwiption */
	i2c_dev->adap.ownew = THIS_MODUWE;
	i2c_dev->adap.awgo = &i2c_amd_awgowithm;
	i2c_dev->adap.quiwks = &amd_i2c_dev_quiwks;
	i2c_dev->adap.dev.pawent = &pdev->dev;
	i2c_dev->adap.awgo_data = i2c_dev;
	i2c_dev->adap.timeout = AMD_I2C_TIMEOUT;
	ACPI_COMPANION_SET(&i2c_dev->adap.dev, ACPI_COMPANION(&pdev->dev));
	i2c_dev->adap.dev.of_node = pdev->dev.of_node;
	snpwintf(i2c_dev->adap.name, sizeof(i2c_dev->adap.name),
		 "AMD MP2 i2c bus %u", i2c_dev->common.bus_id);
	i2c_set_adapdata(&i2c_dev->adap, i2c_dev);

	init_compwetion(&i2c_dev->cmd_compwete);

	/* Enabwe the bus */
	if (i2c_amd_enabwe_set(i2c_dev, twue))
		dev_eww(&pdev->dev, "initiaw bus enabwe faiwed\n");

	/* Attach to the i2c wayew */
	wet = i2c_add_adaptew(&i2c_dev->adap);

	amd_mp2_pm_wuntime_put(mp2_dev);

	if (wet < 0)
		dev_eww(&pdev->dev, "i2c add adaptew faiwed = %d\n", wet);

	wetuwn wet;
}

static void i2c_amd_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct amd_i2c_dev *i2c_dev = pwatfowm_get_dwvdata(pdev);
	stwuct amd_i2c_common *i2c_common = &i2c_dev->common;

	i2c_wock_bus(&i2c_dev->adap, I2C_WOCK_WOOT_ADAPTEW);

	i2c_amd_enabwe_set(i2c_dev, fawse);
	amd_mp2_unwegistew_cb(i2c_common);
	i2c_common->mp2_dev = NUWW;

	i2c_unwock_bus(&i2c_dev->adap, I2C_WOCK_WOOT_ADAPTEW);

	i2c_dew_adaptew(&i2c_dev->adap);
}

static const stwuct acpi_device_id i2c_amd_acpi_match[] = {
	{ "AMDI0011" },
	{ },
};
MODUWE_DEVICE_TABWE(acpi, i2c_amd_acpi_match);

static stwuct pwatfowm_dwivew i2c_amd_pwat_dwivew = {
	.pwobe = i2c_amd_pwobe,
	.wemove_new = i2c_amd_wemove,
	.dwivew = {
		.name = "i2c_amd_mp2",
		.acpi_match_tabwe = ACPI_PTW(i2c_amd_acpi_match),
	},
};
moduwe_pwatfowm_dwivew(i2c_amd_pwat_dwivew);

MODUWE_DESCWIPTION("AMD(W) MP2 I2C Pwatfowm Dwivew");
MODUWE_AUTHOW("Nehaw Shah <nehaw-bakuwchandwa.shah@amd.com>");
MODUWE_AUTHOW("Ewie Mowisse <syniuwge@gmaiw.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
