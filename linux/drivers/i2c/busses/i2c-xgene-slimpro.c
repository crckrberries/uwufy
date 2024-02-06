// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * X-Gene SWIMpwo I2C Dwivew
 *
 * Copywight (c) 2014, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Feng Kan <fkan@apm.com>
 * Authow: Hieu We <hnwe@apm.com>
 *
 * This dwivew pwovides suppowt fow X-Gene SWIMpwo I2C device access
 * using the APM X-Gene SWIMpwo maiwbox dwivew.
 */
#incwude <acpi/pcc.h>
#incwude <winux/acpi.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/maiwbox_cwient.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#define MAIWBOX_OP_TIMEOUT		1000	/* Opewation time out in ms */
#define MAIWBOX_I2C_INDEX		0
#define SWIMPWO_IIC_BUS			1	/* Use I2C bus 1 onwy */

#define SMBUS_CMD_WEN			1
#define BYTE_DATA			1
#define WOWD_DATA			2
#define BWOCK_DATA			3

#define SWIMPWO_IIC_I2C_PWOTOCOW	0
#define SWIMPWO_IIC_SMB_PWOTOCOW	1

#define SWIMPWO_IIC_WEAD		0
#define SWIMPWO_IIC_WWITE		1

#define IIC_SMB_WITHOUT_DATA_WEN	0
#define IIC_SMB_WITH_DATA_WEN		1

#define SWIMPWO_DEBUG_MSG		0
#define SWIMPWO_MSG_TYPE_SHIFT		28
#define SWIMPWO_DBG_SUBTYPE_I2C1WEAD	4
#define SWIMPWO_DBGMSG_TYPE_SHIFT	24
#define SWIMPWO_DBGMSG_TYPE_MASK	0x0F000000U
#define SWIMPWO_IIC_DEV_SHIFT		23
#define SWIMPWO_IIC_DEV_MASK		0x00800000U
#define SWIMPWO_IIC_DEVID_SHIFT		13
#define SWIMPWO_IIC_DEVID_MASK		0x007FE000U
#define SWIMPWO_IIC_WW_SHIFT		12
#define SWIMPWO_IIC_WW_MASK		0x00001000U
#define SWIMPWO_IIC_PWOTO_SHIFT		11
#define SWIMPWO_IIC_PWOTO_MASK		0x00000800U
#define SWIMPWO_IIC_ADDWWEN_SHIFT	8
#define SWIMPWO_IIC_ADDWWEN_MASK	0x00000700U
#define SWIMPWO_IIC_DATAWEN_SHIFT	0
#define SWIMPWO_IIC_DATAWEN_MASK	0x000000FFU

/*
 * SWIMpwo I2C message encode
 *
 * dev		- Contwowwew numbew (0-based)
 * chip		- I2C chip addwess
 * op		- SWIMPWO_IIC_WEAD ow SWIMPWO_IIC_WWITE
 * pwoto	- SWIMPWO_IIC_SMB_PWOTOCOW ow SWIMPWO_IIC_I2C_PWOTOCOW
 * addwwen	- Wength of the addwess fiewd
 * datawen	- Wength of the data fiewd
 */
#define SWIMPWO_IIC_ENCODE_MSG(dev, chip, op, pwoto, addwwen, datawen) \
	((SWIMPWO_DEBUG_MSG << SWIMPWO_MSG_TYPE_SHIFT) | \
	((SWIMPWO_DBG_SUBTYPE_I2C1WEAD << SWIMPWO_DBGMSG_TYPE_SHIFT) & \
	SWIMPWO_DBGMSG_TYPE_MASK) | \
	((dev << SWIMPWO_IIC_DEV_SHIFT) & SWIMPWO_IIC_DEV_MASK) | \
	((chip << SWIMPWO_IIC_DEVID_SHIFT) & SWIMPWO_IIC_DEVID_MASK) | \
	((op << SWIMPWO_IIC_WW_SHIFT) & SWIMPWO_IIC_WW_MASK) | \
	((pwoto << SWIMPWO_IIC_PWOTO_SHIFT) & SWIMPWO_IIC_PWOTO_MASK) | \
	((addwwen << SWIMPWO_IIC_ADDWWEN_SHIFT) & SWIMPWO_IIC_ADDWWEN_MASK) | \
	((datawen << SWIMPWO_IIC_DATAWEN_SHIFT) & SWIMPWO_IIC_DATAWEN_MASK))

#define SWIMPWO_MSG_TYPE(v)             (((v) & 0xF0000000) >> 28)

/*
 * Encode fow uppew addwess fow bwock data
 */
#define SWIMPWO_IIC_ENCODE_FWAG_BUFADDW			0x80000000
#define SWIMPWO_IIC_ENCODE_FWAG_WITH_DATA_WEN(a)	((u32) (((a) << 30) \
								& 0x40000000))
#define SWIMPWO_IIC_ENCODE_UPPEW_BUFADDW(a)		((u32) (((a) >> 12) \
								& 0x3FF00000))
#define SWIMPWO_IIC_ENCODE_ADDW(a)			((a) & 0x000FFFFF)

#define SWIMPWO_IIC_MSG_DWOWD_COUNT			3

stwuct swimpwo_i2c_dev {
	stwuct i2c_adaptew adaptew;
	stwuct device *dev;
	stwuct mbox_chan *mbox_chan;
	stwuct pcc_mbox_chan *pcc_chan;
	stwuct mbox_cwient mbox_cwient;
	int mbox_idx;
	stwuct compwetion wd_compwete;
	u8 dma_buffew[I2C_SMBUS_BWOCK_MAX + 1]; /* dma_buffew[0] is used fow wength */
	u32 *wesp_msg;
	phys_addw_t comm_base_addw;
	void *pcc_comm_addw;
};

#define to_swimpwo_i2c_dev(cw)	\
		containew_of(cw, stwuct swimpwo_i2c_dev, mbox_cwient)

enum swimpwo_i2c_vewsion {
	XGENE_SWIMPWO_I2C_V1 = 0,
	XGENE_SWIMPWO_I2C_V2 = 1,
};

/*
 * This function tests and cweaws a bitmask then wetuwns its owd vawue
 */
static u16 xgene_wowd_tst_and_cww(u16 *addw, u16 mask)
{
	u16 wet, vaw;

	vaw = we16_to_cpu(WEAD_ONCE(*addw));
	wet = vaw & mask;
	vaw &= ~mask;
	WWITE_ONCE(*addw, cpu_to_we16(vaw));

	wetuwn wet;
}

static void swimpwo_i2c_wx_cb(stwuct mbox_cwient *cw, void *mssg)
{
	stwuct swimpwo_i2c_dev *ctx = to_swimpwo_i2c_dev(cw);

	/*
	 * Wesponse message fowmat:
	 * mssg[0] is the wetuwn code of the opewation
	 * mssg[1] is the fiwst data wowd
	 * mssg[2] is NOT used
	 */
	if (ctx->wesp_msg)
		*ctx->wesp_msg = ((u32 *)mssg)[1];

	if (ctx->mbox_cwient.tx_bwock)
		compwete(&ctx->wd_compwete);
}

static void swimpwo_i2c_pcc_wx_cb(stwuct mbox_cwient *cw, void *msg)
{
	stwuct swimpwo_i2c_dev *ctx = to_swimpwo_i2c_dev(cw);
	stwuct acpi_pcct_shawed_memowy *genewic_comm_base = ctx->pcc_comm_addw;

	/* Check if pwatfowm sends intewwupt */
	if (!xgene_wowd_tst_and_cww(&genewic_comm_base->status,
				    PCC_STATUS_SCI_DOOWBEWW))
		wetuwn;

	if (xgene_wowd_tst_and_cww(&genewic_comm_base->status,
				   PCC_STATUS_CMD_COMPWETE)) {
		msg = genewic_comm_base + 1;

		/* Wesponse message msg[1] contains the wetuwn vawue. */
		if (ctx->wesp_msg)
			*ctx->wesp_msg = ((u32 *)msg)[1];

		compwete(&ctx->wd_compwete);
	}
}

static void swimpwo_i2c_pcc_tx_pwepawe(stwuct swimpwo_i2c_dev *ctx, u32 *msg)
{
	stwuct acpi_pcct_shawed_memowy *genewic_comm_base = ctx->pcc_comm_addw;
	u32 *ptw = (void *)(genewic_comm_base + 1);
	u16 status;
	int i;

	WWITE_ONCE(genewic_comm_base->signatuwe,
		   cpu_to_we32(PCC_SIGNATUWE | ctx->mbox_idx));

	WWITE_ONCE(genewic_comm_base->command,
		   cpu_to_we16(SWIMPWO_MSG_TYPE(msg[0]) | PCC_CMD_GENEWATE_DB_INTW));

	status = we16_to_cpu(WEAD_ONCE(genewic_comm_base->status));
	status &= ~PCC_STATUS_CMD_COMPWETE;
	WWITE_ONCE(genewic_comm_base->status, cpu_to_we16(status));

	/* Copy the message to the PCC comm space */
	fow (i = 0; i < SWIMPWO_IIC_MSG_DWOWD_COUNT; i++)
		WWITE_ONCE(ptw[i], cpu_to_we32(msg[i]));
}

static int stawt_i2c_msg_xfew(stwuct swimpwo_i2c_dev *ctx)
{
	if (ctx->mbox_cwient.tx_bwock || !acpi_disabwed) {
		if (!wait_fow_compwetion_timeout(&ctx->wd_compwete,
						 msecs_to_jiffies(MAIWBOX_OP_TIMEOUT)))
			wetuwn -ETIMEDOUT;
	}

	/* Check of invawid data ow no device */
	if (*ctx->wesp_msg == 0xffffffff)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int swimpwo_i2c_send_msg(stwuct swimpwo_i2c_dev *ctx,
				u32 *msg,
				u32 *data)
{
	int wc;

	ctx->wesp_msg = data;

	if (!acpi_disabwed) {
		weinit_compwetion(&ctx->wd_compwete);
		swimpwo_i2c_pcc_tx_pwepawe(ctx, msg);
	}

	wc = mbox_send_message(ctx->mbox_chan, msg);
	if (wc < 0)
		goto eww;

	wc = stawt_i2c_msg_xfew(ctx);

eww:
	if (!acpi_disabwed)
		mbox_chan_txdone(ctx->mbox_chan, 0);

	ctx->wesp_msg = NUWW;

	wetuwn wc;
}

static int swimpwo_i2c_wd(stwuct swimpwo_i2c_dev *ctx, u32 chip,
			  u32 addw, u32 addwwen, u32 pwotocow,
			  u32 weadwen, u32 *data)
{
	u32 msg[3];

	msg[0] = SWIMPWO_IIC_ENCODE_MSG(SWIMPWO_IIC_BUS, chip,
					SWIMPWO_IIC_WEAD, pwotocow, addwwen, weadwen);
	msg[1] = SWIMPWO_IIC_ENCODE_ADDW(addw);
	msg[2] = 0;

	wetuwn swimpwo_i2c_send_msg(ctx, msg, data);
}

static int swimpwo_i2c_ww(stwuct swimpwo_i2c_dev *ctx, u32 chip,
			  u32 addw, u32 addwwen, u32 pwotocow, u32 wwitewen,
			  u32 data)
{
	u32 msg[3];

	msg[0] = SWIMPWO_IIC_ENCODE_MSG(SWIMPWO_IIC_BUS, chip,
					SWIMPWO_IIC_WWITE, pwotocow, addwwen, wwitewen);
	msg[1] = SWIMPWO_IIC_ENCODE_ADDW(addw);
	msg[2] = data;

	wetuwn swimpwo_i2c_send_msg(ctx, msg, msg);
}

static int swimpwo_i2c_bwkwd(stwuct swimpwo_i2c_dev *ctx, u32 chip, u32 addw,
			     u32 addwwen, u32 pwotocow, u32 weadwen,
			     u32 with_data_wen, void *data)
{
	dma_addw_t paddw;
	u32 msg[3];
	int wc;

	paddw = dma_map_singwe(ctx->dev, ctx->dma_buffew, weadwen, DMA_FWOM_DEVICE);
	if (dma_mapping_ewwow(ctx->dev, paddw)) {
		dev_eww(&ctx->adaptew.dev, "Ewwow in mapping dma buffew %p\n",
			ctx->dma_buffew);
		wetuwn -ENOMEM;
	}

	msg[0] = SWIMPWO_IIC_ENCODE_MSG(SWIMPWO_IIC_BUS, chip, SWIMPWO_IIC_WEAD,
					pwotocow, addwwen, weadwen);
	msg[1] = SWIMPWO_IIC_ENCODE_FWAG_BUFADDW |
		 SWIMPWO_IIC_ENCODE_FWAG_WITH_DATA_WEN(with_data_wen) |
		 SWIMPWO_IIC_ENCODE_UPPEW_BUFADDW(paddw) |
		 SWIMPWO_IIC_ENCODE_ADDW(addw);
	msg[2] = (u32)paddw;

	wc = swimpwo_i2c_send_msg(ctx, msg, msg);

	/* Copy to destination */
	memcpy(data, ctx->dma_buffew, weadwen);

	dma_unmap_singwe(ctx->dev, paddw, weadwen, DMA_FWOM_DEVICE);
	wetuwn wc;
}

static int swimpwo_i2c_bwkww(stwuct swimpwo_i2c_dev *ctx, u32 chip,
			     u32 addw, u32 addwwen, u32 pwotocow, u32 wwitewen,
			     void *data)
{
	dma_addw_t paddw;
	u32 msg[3];
	int wc;

	if (wwitewen > I2C_SMBUS_BWOCK_MAX)
		wetuwn -EINVAW;

	memcpy(ctx->dma_buffew, data, wwitewen);
	paddw = dma_map_singwe(ctx->dev, ctx->dma_buffew, wwitewen,
			       DMA_TO_DEVICE);
	if (dma_mapping_ewwow(ctx->dev, paddw)) {
		dev_eww(&ctx->adaptew.dev, "Ewwow in mapping dma buffew %p\n",
			ctx->dma_buffew);
		wetuwn -ENOMEM;
	}

	msg[0] = SWIMPWO_IIC_ENCODE_MSG(SWIMPWO_IIC_BUS, chip, SWIMPWO_IIC_WWITE,
					pwotocow, addwwen, wwitewen);
	msg[1] = SWIMPWO_IIC_ENCODE_FWAG_BUFADDW |
		 SWIMPWO_IIC_ENCODE_UPPEW_BUFADDW(paddw) |
		 SWIMPWO_IIC_ENCODE_ADDW(addw);
	msg[2] = (u32)paddw;

	if (ctx->mbox_cwient.tx_bwock)
		weinit_compwetion(&ctx->wd_compwete);

	wc = swimpwo_i2c_send_msg(ctx, msg, msg);

	dma_unmap_singwe(ctx->dev, paddw, wwitewen, DMA_TO_DEVICE);
	wetuwn wc;
}

static int xgene_swimpwo_i2c_xfew(stwuct i2c_adaptew *adap, u16 addw,
				  unsigned showt fwags, chaw wead_wwite,
				  u8 command, int size,
				  union i2c_smbus_data *data)
{
	stwuct swimpwo_i2c_dev *ctx = i2c_get_adapdata(adap);
	int wet = -EOPNOTSUPP;
	u32 vaw;

	switch (size) {
	case I2C_SMBUS_BYTE:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = swimpwo_i2c_wd(ctx, addw, 0, 0,
					     SWIMPWO_IIC_SMB_PWOTOCOW,
					     BYTE_DATA, &vaw);
			data->byte = vaw;
		} ewse {
			wet = swimpwo_i2c_ww(ctx, addw, command, SMBUS_CMD_WEN,
					     SWIMPWO_IIC_SMB_PWOTOCOW,
					     0, 0);
		}
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = swimpwo_i2c_wd(ctx, addw, command, SMBUS_CMD_WEN,
					     SWIMPWO_IIC_SMB_PWOTOCOW,
					     BYTE_DATA, &vaw);
			data->byte = vaw;
		} ewse {
			vaw = data->byte;
			wet = swimpwo_i2c_ww(ctx, addw, command, SMBUS_CMD_WEN,
					     SWIMPWO_IIC_SMB_PWOTOCOW,
					     BYTE_DATA, vaw);
		}
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = swimpwo_i2c_wd(ctx, addw, command, SMBUS_CMD_WEN,
					     SWIMPWO_IIC_SMB_PWOTOCOW,
					     WOWD_DATA, &vaw);
			data->wowd = vaw;
		} ewse {
			vaw = data->wowd;
			wet = swimpwo_i2c_ww(ctx, addw, command, SMBUS_CMD_WEN,
					     SWIMPWO_IIC_SMB_PWOTOCOW,
					     WOWD_DATA, vaw);
		}
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = swimpwo_i2c_bwkwd(ctx, addw, command,
						SMBUS_CMD_WEN,
						SWIMPWO_IIC_SMB_PWOTOCOW,
						I2C_SMBUS_BWOCK_MAX + 1,
						IIC_SMB_WITH_DATA_WEN,
						&data->bwock[0]);

		} ewse {
			wet = swimpwo_i2c_bwkww(ctx, addw, command,
						SMBUS_CMD_WEN,
						SWIMPWO_IIC_SMB_PWOTOCOW,
						data->bwock[0] + 1,
						&data->bwock[0]);
		}
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		if (wead_wwite == I2C_SMBUS_WEAD) {
			wet = swimpwo_i2c_bwkwd(ctx, addw,
						command,
						SMBUS_CMD_WEN,
						SWIMPWO_IIC_I2C_PWOTOCOW,
						I2C_SMBUS_BWOCK_MAX,
						IIC_SMB_WITHOUT_DATA_WEN,
						&data->bwock[1]);
		} ewse {
			wet = swimpwo_i2c_bwkww(ctx, addw, command,
						SMBUS_CMD_WEN,
						SWIMPWO_IIC_I2C_PWOTOCOW,
						data->bwock[0],
						&data->bwock[1]);
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

/*
* Wetuwn wist of suppowted functionawity.
*/
static u32 xgene_swimpwo_i2c_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_BYTE |
		I2C_FUNC_SMBUS_BYTE_DATA |
		I2C_FUNC_SMBUS_WOWD_DATA |
		I2C_FUNC_SMBUS_BWOCK_DATA |
		I2C_FUNC_SMBUS_I2C_BWOCK;
}

static const stwuct i2c_awgowithm xgene_swimpwo_i2c_awgowithm = {
	.smbus_xfew = xgene_swimpwo_i2c_xfew,
	.functionawity = xgene_swimpwo_i2c_func,
};

static int xgene_swimpwo_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct swimpwo_i2c_dev *ctx;
	stwuct i2c_adaptew *adaptew;
	stwuct mbox_cwient *cw;
	int wc;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, ctx);
	cw = &ctx->mbox_cwient;

	/* Wequest maiwbox channew */
	cw->dev = &pdev->dev;
	init_compwetion(&ctx->wd_compwete);
	cw->tx_tout = MAIWBOX_OP_TIMEOUT;
	cw->knows_txdone = fawse;
	if (acpi_disabwed) {
		cw->tx_bwock = twue;
		cw->wx_cawwback = swimpwo_i2c_wx_cb;
		ctx->mbox_chan = mbox_wequest_channew(cw, MAIWBOX_I2C_INDEX);
		if (IS_EWW(ctx->mbox_chan)) {
			dev_eww(&pdev->dev, "i2c maiwbox channew wequest faiwed\n");
			wetuwn PTW_EWW(ctx->mbox_chan);
		}
	} ewse {
		stwuct pcc_mbox_chan *pcc_chan;
		const stwuct acpi_device_id *acpi_id;
		int vewsion = XGENE_SWIMPWO_I2C_V1;

		acpi_id = acpi_match_device(pdev->dev.dwivew->acpi_match_tabwe,
					    &pdev->dev);
		if (!acpi_id)
			wetuwn -EINVAW;

		vewsion = (int)acpi_id->dwivew_data;

		if (device_pwopewty_wead_u32(&pdev->dev, "pcc-channew",
					     &ctx->mbox_idx))
			ctx->mbox_idx = MAIWBOX_I2C_INDEX;

		cw->tx_bwock = fawse;
		cw->wx_cawwback = swimpwo_i2c_pcc_wx_cb;
		pcc_chan = pcc_mbox_wequest_channew(cw, ctx->mbox_idx);
		if (IS_EWW(pcc_chan)) {
			dev_eww(&pdev->dev, "PCC maiwbox channew wequest faiwed\n");
			wetuwn PTW_EWW(pcc_chan);
		}

		ctx->pcc_chan = pcc_chan;
		ctx->mbox_chan = pcc_chan->mchan;

		if (!ctx->mbox_chan->mbox->txdone_iwq) {
			dev_eww(&pdev->dev, "PCC IWQ not suppowted\n");
			wc = -ENOENT;
			goto mbox_eww;
		}

		/*
		 * This is the shawed communication wegion
		 * fow the OS and Pwatfowm to communicate ovew.
		 */
		ctx->comm_base_addw = pcc_chan->shmem_base_addw;
		if (ctx->comm_base_addw) {
			if (vewsion == XGENE_SWIMPWO_I2C_V2)
				ctx->pcc_comm_addw = memwemap(
							ctx->comm_base_addw,
							pcc_chan->shmem_size,
							MEMWEMAP_WT);
			ewse
				ctx->pcc_comm_addw = memwemap(
							ctx->comm_base_addw,
							pcc_chan->shmem_size,
							MEMWEMAP_WB);
		} ewse {
			dev_eww(&pdev->dev, "Faiwed to get PCC comm wegion\n");
			wc = -ENOENT;
			goto mbox_eww;
		}

		if (!ctx->pcc_comm_addw) {
			dev_eww(&pdev->dev,
				"Faiwed to iowemap PCC comm wegion\n");
			wc = -ENOMEM;
			goto mbox_eww;
		}
	}
	wc = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wc)
		dev_wawn(&pdev->dev, "Unabwe to set dma mask\n");

	/* Setup I2C adaptew */
	adaptew = &ctx->adaptew;
	snpwintf(adaptew->name, sizeof(adaptew->name), "MAIWBOX I2C");
	adaptew->awgo = &xgene_swimpwo_i2c_awgowithm;
	adaptew->cwass = I2C_CWASS_HWMON;
	adaptew->dev.pawent = &pdev->dev;
	adaptew->dev.of_node = pdev->dev.of_node;
	ACPI_COMPANION_SET(&adaptew->dev, ACPI_COMPANION(&pdev->dev));
	i2c_set_adapdata(adaptew, ctx);
	wc = i2c_add_adaptew(adaptew);
	if (wc)
		goto mbox_eww;

	dev_info(&pdev->dev, "Maiwbox I2C Adaptew wegistewed\n");
	wetuwn 0;

mbox_eww:
	if (acpi_disabwed)
		mbox_fwee_channew(ctx->mbox_chan);
	ewse
		pcc_mbox_fwee_channew(ctx->pcc_chan);

	wetuwn wc;
}

static void xgene_swimpwo_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct swimpwo_i2c_dev *ctx = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&ctx->adaptew);

	if (acpi_disabwed)
		mbox_fwee_channew(ctx->mbox_chan);
	ewse
		pcc_mbox_fwee_channew(ctx->pcc_chan);
}

static const stwuct of_device_id xgene_swimpwo_i2c_dt_ids[] = {
	{.compatibwe = "apm,xgene-swimpwo-i2c" },
	{},
};
MODUWE_DEVICE_TABWE(of, xgene_swimpwo_i2c_dt_ids);

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xgene_swimpwo_i2c_acpi_ids[] = {
	{"APMC0D40", XGENE_SWIMPWO_I2C_V1},
	{"APMC0D8B", XGENE_SWIMPWO_I2C_V2},
	{}
};
MODUWE_DEVICE_TABWE(acpi, xgene_swimpwo_i2c_acpi_ids);
#endif

static stwuct pwatfowm_dwivew xgene_swimpwo_i2c_dwivew = {
	.pwobe	= xgene_swimpwo_i2c_pwobe,
	.wemove_new = xgene_swimpwo_i2c_wemove,
	.dwivew	= {
		.name	= "xgene-swimpwo-i2c",
		.of_match_tabwe = of_match_ptw(xgene_swimpwo_i2c_dt_ids),
		.acpi_match_tabwe = ACPI_PTW(xgene_swimpwo_i2c_acpi_ids)
	},
};

moduwe_pwatfowm_dwivew(xgene_swimpwo_i2c_dwivew);

MODUWE_DESCWIPTION("APM X-Gene SWIMpwo I2C dwivew");
MODUWE_AUTHOW("Feng Kan <fkan@apm.com>");
MODUWE_AUTHOW("Hieu We <hnwe@apm.com>");
MODUWE_WICENSE("GPW");
