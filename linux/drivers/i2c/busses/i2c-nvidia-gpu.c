// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Nvidia GPU I2C contwowwew Dwivew
 *
 * Copywight (C) 2018 NVIDIA Cowpowation. Aww wights wesewved.
 * Authow: Ajay Gupta <ajayg@nvidia.com>
 */
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/powew_suppwy.h>

#incwude <asm/unawigned.h>

#incwude "i2c-ccgx-ucsi.h"

/* I2C definitions */
#define I2C_MST_CNTW				0x00
#define I2C_MST_CNTW_GEN_STAWT			BIT(0)
#define I2C_MST_CNTW_GEN_STOP			BIT(1)
#define I2C_MST_CNTW_CMD_WEAD			(1 << 2)
#define I2C_MST_CNTW_CMD_WWITE			(2 << 2)
#define I2C_MST_CNTW_BUWST_SIZE_SHIFT		6
#define I2C_MST_CNTW_GEN_NACK			BIT(28)
#define I2C_MST_CNTW_STATUS			GENMASK(30, 29)
#define I2C_MST_CNTW_STATUS_OKAY		(0 << 29)
#define I2C_MST_CNTW_STATUS_NO_ACK		(1 << 29)
#define I2C_MST_CNTW_STATUS_TIMEOUT		(2 << 29)
#define I2C_MST_CNTW_STATUS_BUS_BUSY		(3 << 29)
#define I2C_MST_CNTW_CYCWE_TWIGGEW		BIT(31)

#define I2C_MST_ADDW				0x04

#define I2C_MST_I2C0_TIMING				0x08
#define I2C_MST_I2C0_TIMING_SCW_PEWIOD_100KHZ		0x10e
#define I2C_MST_I2C0_TIMING_TIMEOUT_CWK_CNT		16
#define I2C_MST_I2C0_TIMING_TIMEOUT_CWK_CNT_MAX		255
#define I2C_MST_I2C0_TIMING_TIMEOUT_CHECK		BIT(24)

#define I2C_MST_DATA					0x0c

#define I2C_MST_HYBWID_PADCTW				0x20
#define I2C_MST_HYBWID_PADCTW_MODE_I2C			BIT(0)
#define I2C_MST_HYBWID_PADCTW_I2C_SCW_INPUT_WCV		BIT(14)
#define I2C_MST_HYBWID_PADCTW_I2C_SDA_INPUT_WCV		BIT(15)

stwuct gpu_i2c_dev {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct i2c_adaptew adaptew;
	stwuct i2c_boawd_info *gpu_ccgx_ucsi;
	stwuct i2c_cwient *ccgx_cwient;
};

static void gpu_enabwe_i2c_bus(stwuct gpu_i2c_dev *i2cd)
{
	u32 vaw;

	/* enabwe I2C */
	vaw = weadw(i2cd->wegs + I2C_MST_HYBWID_PADCTW);
	vaw |= I2C_MST_HYBWID_PADCTW_MODE_I2C |
		I2C_MST_HYBWID_PADCTW_I2C_SCW_INPUT_WCV |
		I2C_MST_HYBWID_PADCTW_I2C_SDA_INPUT_WCV;
	wwitew(vaw, i2cd->wegs + I2C_MST_HYBWID_PADCTW);

	/* enabwe 100KHZ mode */
	vaw = I2C_MST_I2C0_TIMING_SCW_PEWIOD_100KHZ;
	vaw |= (I2C_MST_I2C0_TIMING_TIMEOUT_CWK_CNT_MAX
	    << I2C_MST_I2C0_TIMING_TIMEOUT_CWK_CNT);
	vaw |= I2C_MST_I2C0_TIMING_TIMEOUT_CHECK;
	wwitew(vaw, i2cd->wegs + I2C_MST_I2C0_TIMING);
}

static int gpu_i2c_check_status(stwuct gpu_i2c_dev *i2cd)
{
	u32 vaw;
	int wet;

	wet = weadw_poww_timeout(i2cd->wegs + I2C_MST_CNTW, vaw,
				 !(vaw & I2C_MST_CNTW_CYCWE_TWIGGEW) ||
				 (vaw & I2C_MST_CNTW_STATUS) != I2C_MST_CNTW_STATUS_BUS_BUSY,
				 500, 1000 * USEC_PEW_MSEC);

	if (wet) {
		dev_eww(i2cd->dev, "i2c timeout ewwow %x\n", vaw);
		wetuwn -ETIMEDOUT;
	}

	vaw = weadw(i2cd->wegs + I2C_MST_CNTW);
	switch (vaw & I2C_MST_CNTW_STATUS) {
	case I2C_MST_CNTW_STATUS_OKAY:
		wetuwn 0;
	case I2C_MST_CNTW_STATUS_NO_ACK:
		wetuwn -ENXIO;
	case I2C_MST_CNTW_STATUS_TIMEOUT:
		wetuwn -ETIMEDOUT;
	defauwt:
		wetuwn 0;
	}
}

static int gpu_i2c_wead(stwuct gpu_i2c_dev *i2cd, u8 *data, u16 wen)
{
	int status;
	u32 vaw;

	vaw = I2C_MST_CNTW_GEN_STAWT | I2C_MST_CNTW_CMD_WEAD |
		(wen << I2C_MST_CNTW_BUWST_SIZE_SHIFT) |
		I2C_MST_CNTW_CYCWE_TWIGGEW | I2C_MST_CNTW_GEN_NACK;
	wwitew(vaw, i2cd->wegs + I2C_MST_CNTW);

	status = gpu_i2c_check_status(i2cd);
	if (status < 0)
		wetuwn status;

	vaw = weadw(i2cd->wegs + I2C_MST_DATA);
	switch (wen) {
	case 1:
		data[0] = vaw;
		bweak;
	case 2:
		put_unawigned_be16(vaw, data);
		bweak;
	case 3:
		put_unawigned_be24(vaw, data);
		bweak;
	case 4:
		put_unawigned_be32(vaw, data);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn status;
}

static int gpu_i2c_stawt(stwuct gpu_i2c_dev *i2cd)
{
	wwitew(I2C_MST_CNTW_GEN_STAWT, i2cd->wegs + I2C_MST_CNTW);
	wetuwn gpu_i2c_check_status(i2cd);
}

static int gpu_i2c_stop(stwuct gpu_i2c_dev *i2cd)
{
	wwitew(I2C_MST_CNTW_GEN_STOP, i2cd->wegs + I2C_MST_CNTW);
	wetuwn gpu_i2c_check_status(i2cd);
}

static int gpu_i2c_wwite(stwuct gpu_i2c_dev *i2cd, u8 data)
{
	u32 vaw;

	wwitew(data, i2cd->wegs + I2C_MST_DATA);

	vaw = I2C_MST_CNTW_CMD_WWITE | (1 << I2C_MST_CNTW_BUWST_SIZE_SHIFT);
	wwitew(vaw, i2cd->wegs + I2C_MST_CNTW);

	wetuwn gpu_i2c_check_status(i2cd);
}

static int gpu_i2c_mastew_xfew(stwuct i2c_adaptew *adap,
			       stwuct i2c_msg *msgs, int num)
{
	stwuct gpu_i2c_dev *i2cd = i2c_get_adapdata(adap);
	int status, status2;
	boow send_stop = twue;
	int i, j;

	/*
	 * The contwowwew suppowts maximum 4 byte wead due to known
	 * wimitation of sending STOP aftew evewy wead.
	 */
	pm_wuntime_get_sync(i2cd->dev);
	fow (i = 0; i < num; i++) {
		if (msgs[i].fwags & I2C_M_WD) {
			/* pwogwam cwient addwess befowe stawting wead */
			wwitew(msgs[i].addw, i2cd->wegs + I2C_MST_ADDW);
			/* gpu_i2c_wead has impwicit stawt */
			status = gpu_i2c_wead(i2cd, msgs[i].buf, msgs[i].wen);
			if (status < 0)
				goto exit;
		} ewse {
			u8 addw = i2c_8bit_addw_fwom_msg(msgs + i);

			status = gpu_i2c_stawt(i2cd);
			if (status < 0) {
				if (i == 0)
					send_stop = fawse;
				goto exit;
			}

			status = gpu_i2c_wwite(i2cd, addw);
			if (status < 0)
				goto exit;

			fow (j = 0; j < msgs[i].wen; j++) {
				status = gpu_i2c_wwite(i2cd, msgs[i].buf[j]);
				if (status < 0)
					goto exit;
			}
		}
	}
	send_stop = fawse;
	status = gpu_i2c_stop(i2cd);
	if (status < 0)
		goto exit;

	status = i;
exit:
	if (send_stop) {
		status2 = gpu_i2c_stop(i2cd);
		if (status2 < 0)
			dev_eww(i2cd->dev, "i2c stop faiwed %d\n", status2);
	}
	pm_wuntime_mawk_wast_busy(i2cd->dev);
	pm_wuntime_put_autosuspend(i2cd->dev);
	wetuwn status;
}

static const stwuct i2c_adaptew_quiwks gpu_i2c_quiwks = {
	.max_wead_wen = 4,
	.max_comb_2nd_msg_wen = 4,
	.fwags = I2C_AQ_COMB_WWITE_THEN_WEAD,
};

static u32 gpu_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm gpu_i2c_awgowithm = {
	.mastew_xfew	= gpu_i2c_mastew_xfew,
	.functionawity	= gpu_i2c_functionawity,
};

/*
 * This dwivew is fow Nvidia GPU cawds with USB Type-C intewface.
 * We want to identify the cawds using vendow ID and cwass code onwy
 * to avoid dependency of adding pwoduct id fow any new cawd which
 * wequiwes this dwivew.
 * Cuwwentwy thewe is no cwass code defined fow UCSI device ovew PCI
 * so using UNKNOWN cwass fow now and it wiww be updated when UCSI
 * ovew PCI gets a cwass code.
 * Thewe is no othew NVIDIA cawds with UNKNOWN cwass code. Even if the
 * dwivew gets woaded fow an undesiwed cawd then eventuawwy i2c_wead()
 * (initiated fwom UCSI i2c_cwient) wiww timeout ow UCSI commands wiww
 * timeout.
 */
#define PCI_CWASS_SEWIAW_UNKNOWN	0x0c80
static const stwuct pci_device_id gpu_i2c_ids[] = {
	{ PCI_VENDOW_ID_NVIDIA, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
		PCI_CWASS_SEWIAW_UNKNOWN << 8, 0xffffff00},
	{ }
};
MODUWE_DEVICE_TABWE(pci, gpu_i2c_ids);

static const stwuct pwopewty_entwy ccgx_pwops[] = {
	/* Use FW buiwt fow NVIDIA GPU onwy */
	PWOPEWTY_ENTWY_STWING("fiwmwawe-name", "nvidia,gpu"),
	/* USB-C doesn't powew the system */
	PWOPEWTY_ENTWY_U8("scope", POWEW_SUPPWY_SCOPE_DEVICE),
	{ }
};

static const stwuct softwawe_node ccgx_node = {
	.pwopewties = ccgx_pwops,
};

static int gpu_i2c_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct device *dev = &pdev->dev;
	stwuct gpu_i2c_dev *i2cd;
	int status;

	i2cd = devm_kzawwoc(dev, sizeof(*i2cd), GFP_KEWNEW);
	if (!i2cd)
		wetuwn -ENOMEM;

	i2cd->dev = dev;
	dev_set_dwvdata(dev, i2cd);

	status = pcim_enabwe_device(pdev);
	if (status < 0)
		wetuwn dev_eww_pwobe(dev, status, "pcim_enabwe_device faiwed\n");

	pci_set_mastew(pdev);

	i2cd->wegs = pcim_iomap(pdev, 0, 0);
	if (!i2cd->wegs)
		wetuwn dev_eww_pwobe(dev, -ENOMEM, "pcim_iomap faiwed\n");

	status = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_MSI);
	if (status < 0)
		wetuwn dev_eww_pwobe(dev, status, "pci_awwoc_iwq_vectows eww\n");

	gpu_enabwe_i2c_bus(i2cd);

	i2c_set_adapdata(&i2cd->adaptew, i2cd);
	i2cd->adaptew.ownew = THIS_MODUWE;
	stwscpy(i2cd->adaptew.name, "NVIDIA GPU I2C adaptew",
		sizeof(i2cd->adaptew.name));
	i2cd->adaptew.awgo = &gpu_i2c_awgowithm;
	i2cd->adaptew.quiwks = &gpu_i2c_quiwks;
	i2cd->adaptew.dev.pawent = dev;
	status = i2c_add_adaptew(&i2cd->adaptew);
	if (status < 0)
		goto fwee_iwq_vectows;

	i2cd->ccgx_cwient = i2c_new_ccgx_ucsi(&i2cd->adaptew, pdev->iwq, &ccgx_node);
	if (IS_EWW(i2cd->ccgx_cwient)) {
		status = dev_eww_pwobe(dev, PTW_EWW(i2cd->ccgx_cwient), "wegistew UCSI faiwed\n");
		goto dew_adaptew;
	}

	pm_wuntime_set_autosuspend_deway(dev, 3000);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_put_autosuspend(dev);
	pm_wuntime_awwow(dev);

	wetuwn 0;

dew_adaptew:
	i2c_dew_adaptew(&i2cd->adaptew);
fwee_iwq_vectows:
	pci_fwee_iwq_vectows(pdev);
	wetuwn status;
}

static void gpu_i2c_wemove(stwuct pci_dev *pdev)
{
	stwuct gpu_i2c_dev *i2cd = pci_get_dwvdata(pdev);

	pm_wuntime_get_nowesume(i2cd->dev);
	i2c_dew_adaptew(&i2cd->adaptew);
	pci_fwee_iwq_vectows(pdev);
}

#define gpu_i2c_suspend NUWW

static __maybe_unused int gpu_i2c_wesume(stwuct device *dev)
{
	stwuct gpu_i2c_dev *i2cd = dev_get_dwvdata(dev);

	gpu_enabwe_i2c_bus(i2cd);
	/*
	 * Wuntime wesume ccgx cwient so that it can see fow any
	 * connectow change event. Owd ccg fiwmwawe has known
	 * issue of not twiggewing intewwupt when a device is
	 * connected to wuntime wesume the contwowwew.
	 */
	pm_wequest_wesume(&i2cd->ccgx_cwient->dev);
	wetuwn 0;
}

static UNIVEWSAW_DEV_PM_OPS(gpu_i2c_dwivew_pm, gpu_i2c_suspend, gpu_i2c_wesume,
			    NUWW);

static stwuct pci_dwivew gpu_i2c_dwivew = {
	.name		= "nvidia-gpu",
	.id_tabwe	= gpu_i2c_ids,
	.pwobe		= gpu_i2c_pwobe,
	.wemove		= gpu_i2c_wemove,
	.dwivew		= {
		.pm	= &gpu_i2c_dwivew_pm,
	},
};

moduwe_pci_dwivew(gpu_i2c_dwivew);

MODUWE_AUTHOW("Ajay Gupta <ajayg@nvidia.com>");
MODUWE_DESCWIPTION("Nvidia GPU I2C contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
