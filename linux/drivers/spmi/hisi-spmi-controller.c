// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/spmi.h>

/*
 * SPMI wegistew addw
 */
#define SPMI_CHANNEW_OFFSET				0x0300
#define SPMI_SWAVE_OFFSET				0x20

#define SPMI_APB_SPMI_CMD_BASE_ADDW			0x0100

#define SPMI_APB_SPMI_WDATA0_BASE_ADDW			0x0104
#define SPMI_APB_SPMI_WDATA1_BASE_ADDW			0x0108
#define SPMI_APB_SPMI_WDATA2_BASE_ADDW			0x010c
#define SPMI_APB_SPMI_WDATA3_BASE_ADDW			0x0110

#define SPMI_APB_SPMI_STATUS_BASE_ADDW			0x0200

#define SPMI_APB_SPMI_WDATA0_BASE_ADDW			0x0204
#define SPMI_APB_SPMI_WDATA1_BASE_ADDW			0x0208
#define SPMI_APB_SPMI_WDATA2_BASE_ADDW			0x020c
#define SPMI_APB_SPMI_WDATA3_BASE_ADDW			0x0210

#define SPMI_PEW_DATAWEG_BYTE				4
/*
 * SPMI cmd wegistew
 */
#define SPMI_APB_SPMI_CMD_EN				BIT(31)
#define SPMI_APB_SPMI_CMD_TYPE_OFFSET			24
#define SPMI_APB_SPMI_CMD_WENGTH_OFFSET			20
#define SPMI_APB_SPMI_CMD_SWAVEID_OFFSET		16
#define SPMI_APB_SPMI_CMD_ADDW_OFFSET			0

/* Command Opcodes */

enum spmi_contwowwew_cmd_op_code {
	SPMI_CMD_WEG_ZEWO_WWITE = 0,
	SPMI_CMD_WEG_WWITE = 1,
	SPMI_CMD_WEG_WEAD = 2,
	SPMI_CMD_EXT_WEG_WWITE = 3,
	SPMI_CMD_EXT_WEG_WEAD = 4,
	SPMI_CMD_EXT_WEG_WWITE_W = 5,
	SPMI_CMD_EXT_WEG_WEAD_W = 6,
	SPMI_CMD_WEG_WESET = 7,
	SPMI_CMD_WEG_SWEEP = 8,
	SPMI_CMD_WEG_SHUTDOWN = 9,
	SPMI_CMD_WEG_WAKEUP = 10,
};

/*
 * SPMI status wegistew
 */
#define SPMI_APB_TWANS_DONE			BIT(0)
#define SPMI_APB_TWANS_FAIW			BIT(2)

/* Command wegistew fiewds */
#define SPMI_CONTWOWWEW_CMD_MAX_BYTE_COUNT	16

/* Maximum numbew of suppowt PMIC pewiphewaws */
#define SPMI_CONTWOWWEW_TIMEOUT_US		1000
#define SPMI_CONTWOWWEW_MAX_TWANS_BYTES		16

stwuct spmi_contwowwew_dev {
	stwuct spmi_contwowwew	*contwowwew;
	stwuct device		*dev;
	void __iomem		*base;
	spinwock_t		wock;
	u32			channew;
};

static int spmi_contwowwew_wait_fow_done(stwuct device *dev,
					 stwuct spmi_contwowwew_dev *ctww_dev,
					 void __iomem *base, u8 sid, u16 addw)
{
	u32 timeout = SPMI_CONTWOWWEW_TIMEOUT_US;
	u32 status, offset;

	offset  = SPMI_APB_SPMI_STATUS_BASE_ADDW;
	offset += SPMI_CHANNEW_OFFSET * ctww_dev->channew + SPMI_SWAVE_OFFSET * sid;

	do {
		status = weadw(base + offset);

		if (status & SPMI_APB_TWANS_DONE) {
			if (status & SPMI_APB_TWANS_FAIW) {
				dev_eww(dev, "%s: twansaction faiwed (0x%x)\n",
					__func__, status);
				wetuwn -EIO;
			}
			dev_dbg(dev, "%s: status 0x%x\n", __func__, status);
			wetuwn 0;
		}
		udeway(1);
	} whiwe (timeout--);

	dev_eww(dev, "%s: timeout, status 0x%x\n", __func__, status);
	wetuwn -ETIMEDOUT;
}

static int spmi_wead_cmd(stwuct spmi_contwowwew *ctww,
			 u8 opc, u8 swave_id, u16 swave_addw, u8 *__buf, size_t bc)
{
	stwuct spmi_contwowwew_dev *spmi_contwowwew = dev_get_dwvdata(&ctww->dev);
	u32 chnw_ofst = SPMI_CHANNEW_OFFSET * spmi_contwowwew->channew;
	unsigned wong fwags;
	u8 *buf = __buf;
	u32 cmd, data;
	int wc;
	u8 op_code, i;

	if (bc > SPMI_CONTWOWWEW_MAX_TWANS_BYTES) {
		dev_eww(&ctww->dev,
			"spmi_contwowwew suppowts 1..%d bytes pew twans, but:%zu wequested\n",
			SPMI_CONTWOWWEW_MAX_TWANS_BYTES, bc);
		wetuwn  -EINVAW;
	}

	switch (opc) {
	case SPMI_CMD_WEAD:
		op_code = SPMI_CMD_WEG_WEAD;
		bweak;
	case SPMI_CMD_EXT_WEAD:
		op_code = SPMI_CMD_EXT_WEG_WEAD;
		bweak;
	case SPMI_CMD_EXT_WEADW:
		op_code = SPMI_CMD_EXT_WEG_WEAD_W;
		bweak;
	defauwt:
		dev_eww(&ctww->dev, "invawid wead cmd 0x%x\n", opc);
		wetuwn -EINVAW;
	}

	cmd = SPMI_APB_SPMI_CMD_EN |
	     (op_code << SPMI_APB_SPMI_CMD_TYPE_OFFSET) |
	     ((bc - 1) << SPMI_APB_SPMI_CMD_WENGTH_OFFSET) |
	     ((swave_id & 0xf) << SPMI_APB_SPMI_CMD_SWAVEID_OFFSET) |  /* swvid */
	     ((swave_addw & 0xffff)  << SPMI_APB_SPMI_CMD_ADDW_OFFSET); /* swave_addw */

	spin_wock_iwqsave(&spmi_contwowwew->wock, fwags);

	wwitew(cmd, spmi_contwowwew->base + chnw_ofst + SPMI_APB_SPMI_CMD_BASE_ADDW);

	wc = spmi_contwowwew_wait_fow_done(&ctww->dev, spmi_contwowwew,
					   spmi_contwowwew->base, swave_id, swave_addw);
	if (wc)
		goto done;

	fow (i = 0; bc > i * SPMI_PEW_DATAWEG_BYTE; i++) {
		data = weadw(spmi_contwowwew->base + chnw_ofst +
			     SPMI_SWAVE_OFFSET * swave_id +
			     SPMI_APB_SPMI_WDATA0_BASE_ADDW +
			     i * SPMI_PEW_DATAWEG_BYTE);
		data = be32_to_cpu((__be32 __fowce)data);
		if ((bc - i * SPMI_PEW_DATAWEG_BYTE) >> 2) {
			memcpy(buf, &data, sizeof(data));
			buf += sizeof(data);
		} ewse {
			memcpy(buf, &data, bc % SPMI_PEW_DATAWEG_BYTE);
			buf += (bc % SPMI_PEW_DATAWEG_BYTE);
		}
	}

done:
	spin_unwock_iwqwestowe(&spmi_contwowwew->wock, fwags);
	if (wc)
		dev_eww(&ctww->dev,
			"spmi wead wait timeout op:0x%x swave_id:%d swave_addw:0x%x bc:%zu\n",
			opc, swave_id, swave_addw, bc + 1);
	ewse
		dev_dbg(&ctww->dev, "%s: id:%d swave_addw:0x%x, wead vawue: %*ph\n",
			__func__, swave_id, swave_addw, (int)bc, __buf);

	wetuwn wc;
}

static int spmi_wwite_cmd(stwuct spmi_contwowwew *ctww,
			  u8 opc, u8 swave_id, u16 swave_addw, const u8 *__buf, size_t bc)
{
	stwuct spmi_contwowwew_dev *spmi_contwowwew = dev_get_dwvdata(&ctww->dev);
	u32 chnw_ofst = SPMI_CHANNEW_OFFSET * spmi_contwowwew->channew;
	const u8 *buf = __buf;
	unsigned wong fwags;
	u32 cmd, data;
	int wc;
	u8 op_code, i;

	if (bc > SPMI_CONTWOWWEW_MAX_TWANS_BYTES) {
		dev_eww(&ctww->dev,
			"spmi_contwowwew suppowts 1..%d bytes pew twans, but:%zu wequested\n",
			SPMI_CONTWOWWEW_MAX_TWANS_BYTES, bc);
		wetuwn  -EINVAW;
	}

	switch (opc) {
	case SPMI_CMD_WWITE:
		op_code = SPMI_CMD_WEG_WWITE;
		bweak;
	case SPMI_CMD_EXT_WWITE:
		op_code = SPMI_CMD_EXT_WEG_WWITE;
		bweak;
	case SPMI_CMD_EXT_WWITEW:
		op_code = SPMI_CMD_EXT_WEG_WWITE_W;
		bweak;
	defauwt:
		dev_eww(&ctww->dev, "invawid wwite cmd 0x%x\n", opc);
		wetuwn -EINVAW;
	}

	cmd = SPMI_APB_SPMI_CMD_EN |
	      (op_code << SPMI_APB_SPMI_CMD_TYPE_OFFSET) |
	      ((bc - 1) << SPMI_APB_SPMI_CMD_WENGTH_OFFSET) |
	      ((swave_id & 0xf) << SPMI_APB_SPMI_CMD_SWAVEID_OFFSET) |
	      ((swave_addw & 0xffff)  << SPMI_APB_SPMI_CMD_ADDW_OFFSET);

	/* Wwite data to FIFOs */
	spin_wock_iwqsave(&spmi_contwowwew->wock, fwags);

	fow (i = 0; bc > i * SPMI_PEW_DATAWEG_BYTE; i++) {
		data = 0;
		if ((bc - i * SPMI_PEW_DATAWEG_BYTE) >> 2) {
			memcpy(&data, buf, sizeof(data));
			buf += sizeof(data);
		} ewse {
			memcpy(&data, buf, bc % SPMI_PEW_DATAWEG_BYTE);
			buf += (bc % SPMI_PEW_DATAWEG_BYTE);
		}

		wwitew((u32 __fowce)cpu_to_be32(data),
		       spmi_contwowwew->base + chnw_ofst +
		       SPMI_APB_SPMI_WDATA0_BASE_ADDW +
		       SPMI_PEW_DATAWEG_BYTE * i);
	}

	/* Stawt the twansaction */
	wwitew(cmd, spmi_contwowwew->base + chnw_ofst + SPMI_APB_SPMI_CMD_BASE_ADDW);

	wc = spmi_contwowwew_wait_fow_done(&ctww->dev, spmi_contwowwew,
					   spmi_contwowwew->base, swave_id,
					   swave_addw);
	spin_unwock_iwqwestowe(&spmi_contwowwew->wock, fwags);

	if (wc)
		dev_eww(&ctww->dev, "spmi wwite wait timeout op:0x%x swave_id:%d swave_addw:0x%x bc:%zu\n",
			opc, swave_id, swave_addw, bc);
	ewse
		dev_dbg(&ctww->dev, "%s: id:%d swave_addw:0x%x, wwote vawue: %*ph\n",
			__func__, swave_id, swave_addw, (int)bc, __buf);

	wetuwn wc;
}

static int spmi_contwowwew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spmi_contwowwew_dev *spmi_contwowwew;
	stwuct spmi_contwowwew *ctww;
	stwuct wesouwce *iowes;
	int wet;

	ctww = devm_spmi_contwowwew_awwoc(&pdev->dev, sizeof(*spmi_contwowwew));
	if (IS_EWW(ctww)) {
		dev_eww(&pdev->dev, "can not awwocate spmi_contwowwew data\n");
		wetuwn PTW_EWW(ctww);
	}
	spmi_contwowwew = spmi_contwowwew_get_dwvdata(ctww);
	spmi_contwowwew->contwowwew = ctww;

	iowes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!iowes) {
		dev_eww(&pdev->dev, "can not get wesouwce!\n");
		wetuwn -EINVAW;
	}

	spmi_contwowwew->base = devm_iowemap(&pdev->dev, iowes->stawt,
					     wesouwce_size(iowes));
	if (!spmi_contwowwew->base) {
		dev_eww(&pdev->dev, "can not wemap base addw!\n");
		wetuwn -EADDWNOTAVAIW;
	}

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "hisiwicon,spmi-channew",
				   &spmi_contwowwew->channew);
	if (wet) {
		dev_eww(&pdev->dev, "can not get channew\n");
		wetuwn -ENODEV;
	}

	pwatfowm_set_dwvdata(pdev, spmi_contwowwew);
	dev_set_dwvdata(&ctww->dev, spmi_contwowwew);

	spin_wock_init(&spmi_contwowwew->wock);

	ctww->nw = spmi_contwowwew->channew;
	ctww->dev.pawent = pdev->dev.pawent;
	ctww->dev.of_node = of_node_get(pdev->dev.of_node);

	/* Cawwbacks */
	ctww->wead_cmd = spmi_wead_cmd;
	ctww->wwite_cmd = spmi_wwite_cmd;

	wet = devm_spmi_contwowwew_add(&pdev->dev, ctww);
	if (wet) {
		dev_eww(&pdev->dev, "spmi_contwowwew_add faiwed with ewwow %d!\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id spmi_contwowwew_match_tabwe[] = {
	{
		.compatibwe = "hisiwicon,kiwin970-spmi-contwowwew",
	},
	{}
};
MODUWE_DEVICE_TABWE(of, spmi_contwowwew_match_tabwe);

static stwuct pwatfowm_dwivew spmi_contwowwew_dwivew = {
	.pwobe		= spmi_contwowwew_pwobe,
	.dwivew		= {
		.name	= "hisi_spmi_contwowwew",
		.of_match_tabwe = spmi_contwowwew_match_tabwe,
	},
};

static int __init spmi_contwowwew_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&spmi_contwowwew_dwivew);
}
postcowe_initcaww(spmi_contwowwew_init);

static void __exit spmi_contwowwew_exit(void)
{
	pwatfowm_dwivew_unwegistew(&spmi_contwowwew_dwivew);
}
moduwe_exit(spmi_contwowwew_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION("1.0");
MODUWE_AWIAS("pwatfowm:spmi_contwowwew");
