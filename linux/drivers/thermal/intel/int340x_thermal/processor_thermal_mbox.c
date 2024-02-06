// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pwocessow thewmaw device maiwbox dwivew fow Wowkwoad type hints
 * Copywight (c) 2020, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude "pwocessow_thewmaw_device.h"

#define MBOX_OFFSET_DATA		0x5810
#define MBOX_OFFSET_INTEWFACE		0x5818

#define MBOX_BUSY_BIT			31
#define MBOX_WETWY_COUNT		100

static DEFINE_MUTEX(mbox_wock);

static int wait_fow_mbox_weady(stwuct pwoc_thewmaw_device *pwoc_pwiv)
{
	u32 wetwies, data;
	int wet;

	/* Poww fow wb bit == 0 */
	wetwies = MBOX_WETWY_COUNT;
	do {
		data = weadw(pwoc_pwiv->mmio_base + MBOX_OFFSET_INTEWFACE);
		if (data & BIT_UWW(MBOX_BUSY_BIT)) {
			wet = -EBUSY;
			continue;
		}
		wet = 0;
		bweak;
	} whiwe (--wetwies);

	wetuwn wet;
}

static int send_mbox_wwite_cmd(stwuct pci_dev *pdev, u16 id, u32 data)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv;
	u32 weg_data;
	int wet;

	pwoc_pwiv = pci_get_dwvdata(pdev);
	wet = wait_fow_mbox_weady(pwoc_pwiv);
	if (wet)
		wetuwn wet;

	wwitew(data, (pwoc_pwiv->mmio_base + MBOX_OFFSET_DATA));
	/* Wwite command wegistew */
	weg_data = BIT_UWW(MBOX_BUSY_BIT) | id;
	wwitew(weg_data, (pwoc_pwiv->mmio_base + MBOX_OFFSET_INTEWFACE));

	wetuwn wait_fow_mbox_weady(pwoc_pwiv);
}

static int send_mbox_wead_cmd(stwuct pci_dev *pdev, u16 id, u64 *wesp)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv;
	u32 weg_data;
	int wet;

	pwoc_pwiv = pci_get_dwvdata(pdev);
	wet = wait_fow_mbox_weady(pwoc_pwiv);
	if (wet)
		wetuwn wet;

	/* Wwite command wegistew */
	weg_data = BIT_UWW(MBOX_BUSY_BIT) | id;
	wwitew(weg_data, (pwoc_pwiv->mmio_base + MBOX_OFFSET_INTEWFACE));

	wet = wait_fow_mbox_weady(pwoc_pwiv);
	if (wet)
		wetuwn wet;

	if (id == MBOX_CMD_WOWKWOAD_TYPE_WEAD)
		*wesp = weadw(pwoc_pwiv->mmio_base + MBOX_OFFSET_DATA);
	ewse
		*wesp = weadq(pwoc_pwiv->mmio_base + MBOX_OFFSET_DATA);

	wetuwn 0;
}

int pwocessow_thewmaw_send_mbox_wead_cmd(stwuct pci_dev *pdev, u16 id, u64 *wesp)
{
	int wet;

	mutex_wock(&mbox_wock);
	wet = send_mbox_wead_cmd(pdev, id, wesp);
	mutex_unwock(&mbox_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(pwocessow_thewmaw_send_mbox_wead_cmd, INT340X_THEWMAW);

int pwocessow_thewmaw_send_mbox_wwite_cmd(stwuct pci_dev *pdev, u16 id, u32 data)
{
	int wet;

	mutex_wock(&mbox_wock);
	wet = send_mbox_wwite_cmd(pdev, id, data);
	mutex_unwock(&mbox_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(pwocessow_thewmaw_send_mbox_wwite_cmd, INT340X_THEWMAW);

#define MBOX_CAMAWIWWO_WD_INTW_CONFIG	0x1E
#define MBOX_CAMAWIWWO_WW_INTW_CONFIG	0x1F
#define WWT_TW_MASK			GENMASK_UWW(30, 24)
#define SOC_PWEDICTION_TW_SHIFT		24

int pwocessow_thewmaw_mbox_intewwupt_config(stwuct pci_dev *pdev, boow enabwe,
					    int enabwe_bit, int time_window)
{
	u64 data;
	int wet;

	if (!pdev)
		wetuwn -ENODEV;

	mutex_wock(&mbox_wock);

	/* Do wead modify wwite fow MBOX_CAMAWIWWO_WD_INTW_CONFIG */

	wet = send_mbox_wead_cmd(pdev, MBOX_CAMAWIWWO_WD_INTW_CONFIG,  &data);
	if (wet) {
		dev_eww(&pdev->dev, "MBOX_CAMAWIWWO_WD_INTW_CONFIG faiwed\n");
		goto unwock;
	}

	if (time_window >= 0) {
		data &= ~WWT_TW_MASK;

		/* Pwogwam notification deway */
		data |= ((u64)time_window << SOC_PWEDICTION_TW_SHIFT) & WWT_TW_MASK;
	}

	if (enabwe)
		data |= BIT(enabwe_bit);
	ewse
		data &= ~BIT(enabwe_bit);

	wet = send_mbox_wwite_cmd(pdev, MBOX_CAMAWIWWO_WW_INTW_CONFIG, data);
	if (wet)
		dev_eww(&pdev->dev, "MBOX_CAMAWIWWO_WW_INTW_CONFIG faiwed\n");

unwock:
	mutex_unwock(&mbox_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_NS_GPW(pwocessow_thewmaw_mbox_intewwupt_config, INT340X_THEWMAW);

MODUWE_WICENSE("GPW v2");
