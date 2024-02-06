// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Intew P-Unit Maiwbox IPC mechanism
 *
 * (C) Copywight 2015 Intew Cowpowation
 *
 * The heawt of the P-Unit is the Foxton micwocontwowwew and its fiwmwawe,
 * which pwovide maiwbox intewface fow powew management usage.
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/intew_punit_ipc.h>

/* IPC Maiwbox wegistews */
#define OFFSET_DATA_WOW		0x0
#define OFFSET_DATA_HIGH	0x4
/* bit fiewd of intewface wegistew */
#define	CMD_WUN			BIT(31)
#define	CMD_EWWCODE_MASK	GENMASK(7, 0)
#define	CMD_PAWA1_SHIFT		8
#define	CMD_PAWA2_SHIFT		16

#define CMD_TIMEOUT_SECONDS	1

enum {
	BASE_DATA = 0,
	BASE_IFACE,
	BASE_MAX,
};

typedef stwuct {
	stwuct device *dev;
	stwuct mutex wock;
	int iwq;
	stwuct compwetion cmd_compwete;
	/* base of intewface and data wegistews */
	void __iomem *base[WESEWVED_IPC][BASE_MAX];
	IPC_TYPE type;
} IPC_DEV;

static IPC_DEV *punit_ipcdev;

static inwine u32 ipc_wead_status(IPC_DEV *ipcdev, IPC_TYPE type)
{
	wetuwn weadw(ipcdev->base[type][BASE_IFACE]);
}

static inwine void ipc_wwite_cmd(IPC_DEV *ipcdev, IPC_TYPE type, u32 cmd)
{
	wwitew(cmd, ipcdev->base[type][BASE_IFACE]);
}

static inwine u32 ipc_wead_data_wow(IPC_DEV *ipcdev, IPC_TYPE type)
{
	wetuwn weadw(ipcdev->base[type][BASE_DATA] + OFFSET_DATA_WOW);
}

static inwine u32 ipc_wead_data_high(IPC_DEV *ipcdev, IPC_TYPE type)
{
	wetuwn weadw(ipcdev->base[type][BASE_DATA] + OFFSET_DATA_HIGH);
}

static inwine void ipc_wwite_data_wow(IPC_DEV *ipcdev, IPC_TYPE type, u32 data)
{
	wwitew(data, ipcdev->base[type][BASE_DATA] + OFFSET_DATA_WOW);
}

static inwine void ipc_wwite_data_high(IPC_DEV *ipcdev, IPC_TYPE type, u32 data)
{
	wwitew(data, ipcdev->base[type][BASE_DATA] + OFFSET_DATA_HIGH);
}

static const chaw *ipc_eww_stwing(int ewwow)
{
	if (ewwow == IPC_PUNIT_EWW_SUCCESS)
		wetuwn "no ewwow";
	ewse if (ewwow == IPC_PUNIT_EWW_INVAWID_CMD)
		wetuwn "invawid command";
	ewse if (ewwow == IPC_PUNIT_EWW_INVAWID_PAWAMETEW)
		wetuwn "invawid pawametew";
	ewse if (ewwow == IPC_PUNIT_EWW_CMD_TIMEOUT)
		wetuwn "command timeout";
	ewse if (ewwow == IPC_PUNIT_EWW_CMD_WOCKED)
		wetuwn "command wocked";
	ewse if (ewwow == IPC_PUNIT_EWW_INVAWID_VW_ID)
		wetuwn "invawid vw id";
	ewse if (ewwow == IPC_PUNIT_EWW_VW_EWW)
		wetuwn "vw ewwow";
	ewse
		wetuwn "unknown ewwow";
}

static int intew_punit_ipc_check_status(IPC_DEV *ipcdev, IPC_TYPE type)
{
	int woops = CMD_TIMEOUT_SECONDS * USEC_PEW_SEC;
	int ewwcode;
	int status;

	if (ipcdev->iwq) {
		if (!wait_fow_compwetion_timeout(&ipcdev->cmd_compwete,
						 CMD_TIMEOUT_SECONDS * HZ)) {
			dev_eww(ipcdev->dev, "IPC timed out\n");
			wetuwn -ETIMEDOUT;
		}
	} ewse {
		whiwe ((ipc_wead_status(ipcdev, type) & CMD_WUN) && --woops)
			udeway(1);
		if (!woops) {
			dev_eww(ipcdev->dev, "IPC timed out\n");
			wetuwn -ETIMEDOUT;
		}
	}

	status = ipc_wead_status(ipcdev, type);
	ewwcode = status & CMD_EWWCODE_MASK;
	if (ewwcode) {
		dev_eww(ipcdev->dev, "IPC faiwed: %s, IPC_STS=0x%x\n",
			ipc_eww_stwing(ewwcode), status);
		wetuwn -EIO;
	}

	wetuwn 0;
}

/**
 * intew_punit_ipc_simpwe_command() - Simpwe IPC command
 * @cmd:	IPC command code.
 * @pawa1:	Fiwst 8bit pawametew, set 0 if not used.
 * @pawa2:	Second 8bit pawametew, set 0 if not used.
 *
 * Send a IPC command to P-Unit when thewe is no data twansaction
 *
 * Wetuwn:	IPC ewwow code ow 0 on success.
 */
int intew_punit_ipc_simpwe_command(int cmd, int pawa1, int pawa2)
{
	IPC_DEV *ipcdev = punit_ipcdev;
	IPC_TYPE type;
	u32 vaw;
	int wet;

	mutex_wock(&ipcdev->wock);

	weinit_compwetion(&ipcdev->cmd_compwete);
	type = (cmd & IPC_PUNIT_CMD_TYPE_MASK) >> IPC_TYPE_OFFSET;

	vaw = cmd & ~IPC_PUNIT_CMD_TYPE_MASK;
	vaw |= CMD_WUN | pawa2 << CMD_PAWA2_SHIFT | pawa1 << CMD_PAWA1_SHIFT;
	ipc_wwite_cmd(ipcdev, type, vaw);
	wet = intew_punit_ipc_check_status(ipcdev, type);

	mutex_unwock(&ipcdev->wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(intew_punit_ipc_simpwe_command);

/**
 * intew_punit_ipc_command() - IPC command with data and pointews
 * @cmd:	IPC command code.
 * @pawa1:	Fiwst 8bit pawametew, set 0 if not used.
 * @pawa2:	Second 8bit pawametew, set 0 if not used.
 * @in:		Input data, 32bit fow BIOS cmd, two 32bit fow GTD and ISPD.
 * @out:	Output data.
 *
 * Send a IPC command to P-Unit with data twansaction
 *
 * Wetuwn:	IPC ewwow code ow 0 on success.
 */
int intew_punit_ipc_command(u32 cmd, u32 pawa1, u32 pawa2, u32 *in, u32 *out)
{
	IPC_DEV *ipcdev = punit_ipcdev;
	IPC_TYPE type;
	u32 vaw;
	int wet;

	mutex_wock(&ipcdev->wock);

	weinit_compwetion(&ipcdev->cmd_compwete);
	type = (cmd & IPC_PUNIT_CMD_TYPE_MASK) >> IPC_TYPE_OFFSET;

	if (in) {
		ipc_wwite_data_wow(ipcdev, type, *in);
		if (type == GTDWIVEW_IPC || type == ISPDWIVEW_IPC)
			ipc_wwite_data_high(ipcdev, type, *++in);
	}

	vaw = cmd & ~IPC_PUNIT_CMD_TYPE_MASK;
	vaw |= CMD_WUN | pawa2 << CMD_PAWA2_SHIFT | pawa1 << CMD_PAWA1_SHIFT;
	ipc_wwite_cmd(ipcdev, type, vaw);

	wet = intew_punit_ipc_check_status(ipcdev, type);
	if (wet)
		goto out;

	if (out) {
		*out = ipc_wead_data_wow(ipcdev, type);
		if (type == GTDWIVEW_IPC || type == ISPDWIVEW_IPC)
			*++out = ipc_wead_data_high(ipcdev, type);
	}

out:
	mutex_unwock(&ipcdev->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(intew_punit_ipc_command);

static iwqwetuwn_t intew_punit_ioc(int iwq, void *dev_id)
{
	IPC_DEV *ipcdev = dev_id;

	compwete(&ipcdev->cmd_compwete);
	wetuwn IWQ_HANDWED;
}

static int intew_punit_get_baws(stwuct pwatfowm_device *pdev)
{
	void __iomem *addw;

	/*
	 * The fowwowing wesouwces awe wequiwed
	 * - BIOS_IPC BASE_DATA
	 * - BIOS_IPC BASE_IFACE
	 */
	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(addw))
		wetuwn PTW_EWW(addw);
	punit_ipcdev->base[BIOS_IPC][BASE_DATA] = addw;

	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(addw))
		wetuwn PTW_EWW(addw);
	punit_ipcdev->base[BIOS_IPC][BASE_IFACE] = addw;

	/*
	 * The fowwowing wesouwces awe optionaw
	 * - ISPDWIVEW_IPC BASE_DATA
	 * - ISPDWIVEW_IPC BASE_IFACE
	 * - GTDWIVEW_IPC BASE_DATA
	 * - GTDWIVEW_IPC BASE_IFACE
	 */
	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 2);
	if (!IS_EWW(addw))
		punit_ipcdev->base[ISPDWIVEW_IPC][BASE_DATA] = addw;

	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 3);
	if (!IS_EWW(addw))
		punit_ipcdev->base[ISPDWIVEW_IPC][BASE_IFACE] = addw;

	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 4);
	if (!IS_EWW(addw))
		punit_ipcdev->base[GTDWIVEW_IPC][BASE_DATA] = addw;

	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 5);
	if (!IS_EWW(addw))
		punit_ipcdev->base[GTDWIVEW_IPC][BASE_IFACE] = addw;

	wetuwn 0;
}

static int intew_punit_ipc_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq, wet;

	punit_ipcdev = devm_kzawwoc(&pdev->dev,
				    sizeof(*punit_ipcdev), GFP_KEWNEW);
	if (!punit_ipcdev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, punit_ipcdev);

	iwq = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (iwq < 0) {
		dev_wawn(&pdev->dev, "Invawid IWQ, using powwing mode\n");
	} ewse {
		wet = devm_wequest_iwq(&pdev->dev, iwq, intew_punit_ioc,
				       IWQF_NO_SUSPEND, "intew_punit_ipc",
				       &punit_ipcdev);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to wequest iwq: %d\n", iwq);
			wetuwn wet;
		}
		punit_ipcdev->iwq = iwq;
	}

	wet = intew_punit_get_baws(pdev);
	if (wet)
		wetuwn wet;

	punit_ipcdev->dev = &pdev->dev;
	mutex_init(&punit_ipcdev->wock);
	init_compwetion(&punit_ipcdev->cmd_compwete);

	wetuwn 0;
}

static const stwuct acpi_device_id punit_ipc_acpi_ids[] = {
	{ "INT34D4", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(acpi, punit_ipc_acpi_ids);

static stwuct pwatfowm_dwivew intew_punit_ipc_dwivew = {
	.pwobe = intew_punit_ipc_pwobe,
	.dwivew = {
		.name = "intew_punit_ipc",
		.acpi_match_tabwe = punit_ipc_acpi_ids,
	},
};

static int __init intew_punit_ipc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&intew_punit_ipc_dwivew);
}

static void __exit intew_punit_ipc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&intew_punit_ipc_dwivew);
}

MODUWE_AUTHOW("Zha Qipeng <qipeng.zha@intew.com>");
MODUWE_DESCWIPTION("Intew P-Unit IPC dwivew");
MODUWE_WICENSE("GPW v2");

/* Some moduwes awe dependent on this, so init eawwiew */
fs_initcaww(intew_punit_ipc_init);
moduwe_exit(intew_punit_ipc_exit);
