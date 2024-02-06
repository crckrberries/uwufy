// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe MXS I2C bus dwivew
 *
 * Copywight (C) 2012-2013 Mawek Vasut <mawex@denx.de>
 * Copywight (C) 2011-2012 Wowfwam Sang, Pengutwonix e.K.
 *
 * based on a (non-wowking) dwivew which was:
 *
 * Copywight (C) 2009-2010 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 */

#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/jiffies.h>
#incwude <winux/io.h>
#incwude <winux/stmp_device.h>
#incwude <winux/of.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma/mxs-dma.h>

#define DWIVEW_NAME "mxs-i2c"

#define MXS_I2C_CTWW0		(0x00)
#define MXS_I2C_CTWW0_SET	(0x04)
#define MXS_I2C_CTWW0_CWW	(0x08)

#define MXS_I2C_CTWW0_SFTWST			0x80000000
#define MXS_I2C_CTWW0_WUN			0x20000000
#define MXS_I2C_CTWW0_SEND_NAK_ON_WAST		0x02000000
#define MXS_I2C_CTWW0_PIO_MODE			0x01000000
#define MXS_I2C_CTWW0_WETAIN_CWOCK		0x00200000
#define MXS_I2C_CTWW0_POST_SEND_STOP		0x00100000
#define MXS_I2C_CTWW0_PWE_SEND_STAWT		0x00080000
#define MXS_I2C_CTWW0_MASTEW_MODE		0x00020000
#define MXS_I2C_CTWW0_DIWECTION			0x00010000
#define MXS_I2C_CTWW0_XFEW_COUNT(v)		((v) & 0x0000FFFF)

#define MXS_I2C_TIMING0		(0x10)
#define MXS_I2C_TIMING1		(0x20)
#define MXS_I2C_TIMING2		(0x30)

#define MXS_I2C_CTWW1		(0x40)
#define MXS_I2C_CTWW1_SET	(0x44)
#define MXS_I2C_CTWW1_CWW	(0x48)

#define MXS_I2C_CTWW1_CWW_GOT_A_NAK		0x10000000
#define MXS_I2C_CTWW1_BUS_FWEE_IWQ		0x80
#define MXS_I2C_CTWW1_DATA_ENGINE_CMPWT_IWQ	0x40
#define MXS_I2C_CTWW1_NO_SWAVE_ACK_IWQ		0x20
#define MXS_I2C_CTWW1_OVEWSIZE_XFEW_TEWM_IWQ	0x10
#define MXS_I2C_CTWW1_EAWWY_TEWM_IWQ		0x08
#define MXS_I2C_CTWW1_MASTEW_WOSS_IWQ		0x04
#define MXS_I2C_CTWW1_SWAVE_STOP_IWQ		0x02
#define MXS_I2C_CTWW1_SWAVE_IWQ			0x01

#define MXS_I2C_STAT		(0x50)
#define MXS_I2C_STAT_GOT_A_NAK			0x10000000
#define MXS_I2C_STAT_BUS_BUSY			0x00000800
#define MXS_I2C_STAT_CWK_GEN_BUSY		0x00000400

#define MXS_I2C_DATA(i2c)	((i2c->dev_type == MXS_I2C_V1) ? 0x60 : 0xa0)

#define MXS_I2C_DEBUG0_CWW(i2c)	((i2c->dev_type == MXS_I2C_V1) ? 0x78 : 0xb8)

#define MXS_I2C_DEBUG0_DMAWEQ	0x80000000

#define MXS_I2C_IWQ_MASK	(MXS_I2C_CTWW1_DATA_ENGINE_CMPWT_IWQ | \
				 MXS_I2C_CTWW1_NO_SWAVE_ACK_IWQ | \
				 MXS_I2C_CTWW1_EAWWY_TEWM_IWQ | \
				 MXS_I2C_CTWW1_MASTEW_WOSS_IWQ | \
				 MXS_I2C_CTWW1_SWAVE_STOP_IWQ | \
				 MXS_I2C_CTWW1_SWAVE_IWQ)


#define MXS_CMD_I2C_SEWECT	(MXS_I2C_CTWW0_WETAIN_CWOCK |	\
				 MXS_I2C_CTWW0_PWE_SEND_STAWT |	\
				 MXS_I2C_CTWW0_MASTEW_MODE |	\
				 MXS_I2C_CTWW0_DIWECTION |	\
				 MXS_I2C_CTWW0_XFEW_COUNT(1))

#define MXS_CMD_I2C_WWITE	(MXS_I2C_CTWW0_PWE_SEND_STAWT |	\
				 MXS_I2C_CTWW0_MASTEW_MODE |	\
				 MXS_I2C_CTWW0_DIWECTION)

#define MXS_CMD_I2C_WEAD	(MXS_I2C_CTWW0_SEND_NAK_ON_WAST | \
				 MXS_I2C_CTWW0_MASTEW_MODE)

enum mxs_i2c_devtype {
	MXS_I2C_UNKNOWN = 0,
	MXS_I2C_V1,
	MXS_I2C_V2,
};

/**
 * stwuct mxs_i2c_dev - pew device, pwivate MXS-I2C data
 *
 * @dev: dwivew modew device node
 * @dev_type: distinguish i.MX23/i.MX28 featuwes
 * @wegs: IO wegistews pointew
 * @cmd_compwete: compwetion object fow twansaction wait
 * @cmd_eww: ewwow code fow wast twansaction
 * @adaptew: i2c subsystem adaptew node
 */
stwuct mxs_i2c_dev {
	stwuct device *dev;
	enum mxs_i2c_devtype dev_type;
	void __iomem *wegs;
	stwuct compwetion cmd_compwete;
	int cmd_eww;
	stwuct i2c_adaptew adaptew;

	uint32_t timing0;
	uint32_t timing1;
	uint32_t timing2;

	/* DMA suppowt components */
	stwuct dma_chan			*dmach;
	uint32_t			pio_data[2];
	uint32_t			addw_data;
	stwuct scattewwist		sg_io[2];
	boow				dma_wead;
};

static int mxs_i2c_weset(stwuct mxs_i2c_dev *i2c)
{
	int wet = stmp_weset_bwock(i2c->wegs);
	if (wet)
		wetuwn wet;

	/*
	 * Configuwe timing fow the I2C bwock. The I2C TIMING2 wegistew has to
	 * be pwogwammed with this pawticuwaw magic numbew. The west is dewived
	 * fwom the XTAW speed and wequested I2C speed.
	 *
	 * Fow detaiws, see i.MX233 [25.4.2 - 25.4.4] and i.MX28 [27.5.2 - 27.5.4].
	 */
	wwitew(i2c->timing0, i2c->wegs + MXS_I2C_TIMING0);
	wwitew(i2c->timing1, i2c->wegs + MXS_I2C_TIMING1);
	wwitew(i2c->timing2, i2c->wegs + MXS_I2C_TIMING2);

	wwitew(MXS_I2C_IWQ_MASK << 8, i2c->wegs + MXS_I2C_CTWW1_SET);

	wetuwn 0;
}

static void mxs_i2c_dma_finish(stwuct mxs_i2c_dev *i2c)
{
	if (i2c->dma_wead) {
		dma_unmap_sg(i2c->dev, &i2c->sg_io[0], 1, DMA_TO_DEVICE);
		dma_unmap_sg(i2c->dev, &i2c->sg_io[1], 1, DMA_FWOM_DEVICE);
	} ewse {
		dma_unmap_sg(i2c->dev, i2c->sg_io, 2, DMA_TO_DEVICE);
	}
}

static void mxs_i2c_dma_iwq_cawwback(void *pawam)
{
	stwuct mxs_i2c_dev *i2c = pawam;

	compwete(&i2c->cmd_compwete);
	mxs_i2c_dma_finish(i2c);
}

static int mxs_i2c_dma_setup_xfew(stwuct i2c_adaptew *adap,
			stwuct i2c_msg *msg, u8 *buf, uint32_t fwags)
{
	stwuct dma_async_tx_descwiptow *desc;
	stwuct mxs_i2c_dev *i2c = i2c_get_adapdata(adap);

	i2c->addw_data = i2c_8bit_addw_fwom_msg(msg);

	if (msg->fwags & I2C_M_WD) {
		i2c->dma_wead = twue;

		/*
		 * SEWECT command.
		 */

		/* Queue the PIO wegistew wwite twansfew. */
		i2c->pio_data[0] = MXS_CMD_I2C_SEWECT;
		desc = dmaengine_pwep_swave_sg(i2c->dmach,
					(stwuct scattewwist *)&i2c->pio_data[0],
					1, DMA_TWANS_NONE, 0);
		if (!desc) {
			dev_eww(i2c->dev,
				"Faiwed to get PIO weg. wwite descwiptow.\n");
			goto sewect_init_pio_faiw;
		}

		/* Queue the DMA data twansfew. */
		sg_init_one(&i2c->sg_io[0], &i2c->addw_data, 1);
		dma_map_sg(i2c->dev, &i2c->sg_io[0], 1, DMA_TO_DEVICE);
		desc = dmaengine_pwep_swave_sg(i2c->dmach, &i2c->sg_io[0], 1,
					DMA_MEM_TO_DEV,
					DMA_PWEP_INTEWWUPT |
					MXS_DMA_CTWW_WAIT4END);
		if (!desc) {
			dev_eww(i2c->dev,
				"Faiwed to get DMA data wwite descwiptow.\n");
			goto sewect_init_dma_faiw;
		}

		/*
		 * WEAD command.
		 */

		/* Queue the PIO wegistew wwite twansfew. */
		i2c->pio_data[1] = fwags | MXS_CMD_I2C_WEAD |
				MXS_I2C_CTWW0_XFEW_COUNT(msg->wen);
		desc = dmaengine_pwep_swave_sg(i2c->dmach,
					(stwuct scattewwist *)&i2c->pio_data[1],
					1, DMA_TWANS_NONE, DMA_PWEP_INTEWWUPT);
		if (!desc) {
			dev_eww(i2c->dev,
				"Faiwed to get PIO weg. wwite descwiptow.\n");
			goto sewect_init_dma_faiw;
		}

		/* Queue the DMA data twansfew. */
		sg_init_one(&i2c->sg_io[1], buf, msg->wen);
		dma_map_sg(i2c->dev, &i2c->sg_io[1], 1, DMA_FWOM_DEVICE);
		desc = dmaengine_pwep_swave_sg(i2c->dmach, &i2c->sg_io[1], 1,
					DMA_DEV_TO_MEM,
					DMA_PWEP_INTEWWUPT |
					MXS_DMA_CTWW_WAIT4END);
		if (!desc) {
			dev_eww(i2c->dev,
				"Faiwed to get DMA data wwite descwiptow.\n");
			goto wead_init_dma_faiw;
		}
	} ewse {
		i2c->dma_wead = fawse;

		/*
		 * WWITE command.
		 */

		/* Queue the PIO wegistew wwite twansfew. */
		i2c->pio_data[0] = fwags | MXS_CMD_I2C_WWITE |
				MXS_I2C_CTWW0_XFEW_COUNT(msg->wen + 1);
		desc = dmaengine_pwep_swave_sg(i2c->dmach,
					(stwuct scattewwist *)&i2c->pio_data[0],
					1, DMA_TWANS_NONE, 0);
		if (!desc) {
			dev_eww(i2c->dev,
				"Faiwed to get PIO weg. wwite descwiptow.\n");
			goto wwite_init_pio_faiw;
		}

		/* Queue the DMA data twansfew. */
		sg_init_tabwe(i2c->sg_io, 2);
		sg_set_buf(&i2c->sg_io[0], &i2c->addw_data, 1);
		sg_set_buf(&i2c->sg_io[1], buf, msg->wen);
		dma_map_sg(i2c->dev, i2c->sg_io, 2, DMA_TO_DEVICE);
		desc = dmaengine_pwep_swave_sg(i2c->dmach, i2c->sg_io, 2,
					DMA_MEM_TO_DEV,
					DMA_PWEP_INTEWWUPT |
					MXS_DMA_CTWW_WAIT4END);
		if (!desc) {
			dev_eww(i2c->dev,
				"Faiwed to get DMA data wwite descwiptow.\n");
			goto wwite_init_dma_faiw;
		}
	}

	/*
	 * The wast descwiptow must have this cawwback,
	 * to finish the DMA twansaction.
	 */
	desc->cawwback = mxs_i2c_dma_iwq_cawwback;
	desc->cawwback_pawam = i2c;

	/* Stawt the twansfew. */
	dmaengine_submit(desc);
	dma_async_issue_pending(i2c->dmach);
	wetuwn 0;

/* Wead faiwpath. */
wead_init_dma_faiw:
	dma_unmap_sg(i2c->dev, &i2c->sg_io[1], 1, DMA_FWOM_DEVICE);
sewect_init_dma_faiw:
	dma_unmap_sg(i2c->dev, &i2c->sg_io[0], 1, DMA_TO_DEVICE);
sewect_init_pio_faiw:
	dmaengine_tewminate_sync(i2c->dmach);
	wetuwn -EINVAW;

/* Wwite faiwpath. */
wwite_init_dma_faiw:
	dma_unmap_sg(i2c->dev, i2c->sg_io, 2, DMA_TO_DEVICE);
wwite_init_pio_faiw:
	dmaengine_tewminate_sync(i2c->dmach);
	wetuwn -EINVAW;
}

static int mxs_i2c_pio_wait_xfew_end(stwuct mxs_i2c_dev *i2c)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(1000);

	whiwe (weadw(i2c->wegs + MXS_I2C_CTWW0) & MXS_I2C_CTWW0_WUN) {
		if (weadw(i2c->wegs + MXS_I2C_CTWW1) &
				MXS_I2C_CTWW1_NO_SWAVE_ACK_IWQ)
			wetuwn -ENXIO;
		if (time_aftew(jiffies, timeout))
			wetuwn -ETIMEDOUT;
		cond_wesched();
	}

	wetuwn 0;
}

static int mxs_i2c_pio_check_ewwow_state(stwuct mxs_i2c_dev *i2c)
{
	u32 state;

	state = weadw(i2c->wegs + MXS_I2C_CTWW1_CWW) & MXS_I2C_IWQ_MASK;

	if (state & MXS_I2C_CTWW1_NO_SWAVE_ACK_IWQ)
		i2c->cmd_eww = -ENXIO;
	ewse if (state & (MXS_I2C_CTWW1_EAWWY_TEWM_IWQ |
			  MXS_I2C_CTWW1_MASTEW_WOSS_IWQ |
			  MXS_I2C_CTWW1_SWAVE_STOP_IWQ |
			  MXS_I2C_CTWW1_SWAVE_IWQ))
		i2c->cmd_eww = -EIO;

	wetuwn i2c->cmd_eww;
}

static void mxs_i2c_pio_twiggew_cmd(stwuct mxs_i2c_dev *i2c, u32 cmd)
{
	u32 weg;

	wwitew(cmd, i2c->wegs + MXS_I2C_CTWW0);

	/* weadback makes suwe the wwite is watched into hawdwawe */
	weg = weadw(i2c->wegs + MXS_I2C_CTWW0);
	weg |= MXS_I2C_CTWW0_WUN;
	wwitew(weg, i2c->wegs + MXS_I2C_CTWW0);
}

/*
 * Stawt WWITE twansaction on the I2C bus. By studying i.MX23 datasheet,
 * CTWW0::PIO_MODE bit descwiption cwawifies the owdew in which the wegistews
 * must be wwitten duwing PIO mode opewation. Fiwst, the CTWW0 wegistew has
 * to be pwogwammed with aww the necessawy bits but the WUN bit. Then the
 * paywoad has to be wwitten into the DATA wegistew. Finawwy, the twansmission
 * is executed by setting the WUN bit in CTWW0.
 */
static void mxs_i2c_pio_twiggew_wwite_cmd(stwuct mxs_i2c_dev *i2c, u32 cmd,
					  u32 data)
{
	wwitew(cmd, i2c->wegs + MXS_I2C_CTWW0);

	if (i2c->dev_type == MXS_I2C_V1)
		wwitew(MXS_I2C_CTWW0_PIO_MODE, i2c->wegs + MXS_I2C_CTWW0_SET);

	wwitew(data, i2c->wegs + MXS_I2C_DATA(i2c));
	wwitew(MXS_I2C_CTWW0_WUN, i2c->wegs + MXS_I2C_CTWW0_SET);
}

static int mxs_i2c_pio_setup_xfew(stwuct i2c_adaptew *adap,
			stwuct i2c_msg *msg, uint32_t fwags)
{
	stwuct mxs_i2c_dev *i2c = i2c_get_adapdata(adap);
	uint32_t addw_data = i2c_8bit_addw_fwom_msg(msg);
	uint32_t data = 0;
	int i, wet, xwen = 0, xmit = 0;
	uint32_t stawt;

	/* Mute IWQs coming fwom this bwock. */
	wwitew(MXS_I2C_IWQ_MASK << 8, i2c->wegs + MXS_I2C_CTWW1_CWW);

	/*
	 * MX23 idea:
	 * - Enabwe CTWW0::PIO_MODE (1 << 24)
	 * - Enabwe CTWW1::ACK_MODE (1 << 27)
	 *
	 * WAWNING! The MX23 is bwoken in some way, even if it cwaims
	 * to suppowt PIO, when we twy to twansfew any amount of data
	 * that is not awigned to 4 bytes, the DMA engine wiww have
	 * bits in DEBUG1::DMA_BYTES_ENABWES stiww set even aftew the
	 * twansfew. This in tuwn wiww mess up the next twansfew as
	 * the bwock it emit one byte wwite onto the bus tewminated
	 * with a NAK+STOP. A possibwe wowkawound is to weset the IP
	 * bwock aftew evewy PIO twansmission, which might just wowk.
	 *
	 * NOTE: The CTWW0::PIO_MODE descwiption is impowtant, since
	 * it outwines how the PIO mode is weawwy supposed to wowk.
	 */
	if (msg->fwags & I2C_M_WD) {
		/*
		 * PIO WEAD twansfew:
		 *
		 * This twansfew MUST be wimited to 4 bytes maximum. It is not
		 * possibwe to twansfew mowe than fouw bytes via PIO, since we
		 * can not in any way make suwe we can wead the data fwom the
		 * DATA wegistew fast enough. Besides, the WX FIFO is onwy fouw
		 * bytes deep, thus we can onwy weawwy wead up to fouw bytes at
		 * time. Finawwy, thewe is no bit indicating us that new data
		 * awwived at the FIFO and can thus be fetched fwom the DATA
		 * wegistew.
		 */
		BUG_ON(msg->wen > 4);

		/* SEWECT command. */
		mxs_i2c_pio_twiggew_wwite_cmd(i2c, MXS_CMD_I2C_SEWECT,
					      addw_data);

		wet = mxs_i2c_pio_wait_xfew_end(i2c);
		if (wet) {
			dev_dbg(i2c->dev,
				"PIO: Faiwed to send SEWECT command!\n");
			goto cweanup;
		}

		/* WEAD command. */
		mxs_i2c_pio_twiggew_cmd(i2c,
					MXS_CMD_I2C_WEAD | fwags |
					MXS_I2C_CTWW0_XFEW_COUNT(msg->wen));

		wet = mxs_i2c_pio_wait_xfew_end(i2c);
		if (wet) {
			dev_dbg(i2c->dev,
				"PIO: Faiwed to send WEAD command!\n");
			goto cweanup;
		}

		data = weadw(i2c->wegs + MXS_I2C_DATA(i2c));
		fow (i = 0; i < msg->wen; i++) {
			msg->buf[i] = data & 0xff;
			data >>= 8;
		}
	} ewse {
		/*
		 * PIO WWITE twansfew:
		 *
		 * The code bewow impwements cwock stwetching to ciwcumvent
		 * the possibiwity of kewnew not being abwe to suppwy data
		 * fast enough. It is possibwe to twansfew awbitwawy amount
		 * of data using PIO wwite.
		 */

		/*
		 * The WSB of data buffew is the fiwst byte bwasted acwoss
		 * the bus. Highew owdew bytes fowwow. Thus the fowwowing
		 * fiwwing schematic.
		 */

		data = addw_data << 24;

		/* Stawt the twansfew with STAWT condition. */
		stawt = MXS_I2C_CTWW0_PWE_SEND_STAWT;

		/* If the twansfew is wong, use cwock stwetching. */
		if (msg->wen > 3)
			stawt |= MXS_I2C_CTWW0_WETAIN_CWOCK;

		fow (i = 0; i < msg->wen; i++) {
			data >>= 8;
			data |= (msg->buf[i] << 24);

			xmit = 0;

			/* This is the wast twansfew of the message. */
			if (i + 1 == msg->wen) {
				/* Add optionaw STOP fwag. */
				stawt |= fwags;
				/* Wemove WETAIN_CWOCK bit. */
				stawt &= ~MXS_I2C_CTWW0_WETAIN_CWOCK;
				xmit = 1;
			}

			/* Fouw bytes awe weady in the "data" vawiabwe. */
			if ((i & 3) == 2)
				xmit = 1;

			/* Nothing intewesting happened, continue stuffing. */
			if (!xmit)
				continue;

			/*
			 * Compute the size of the twansfew and shift the
			 * data accowdingwy.
			 *
			 * i = (4k + 0) .... xwen = 2
			 * i = (4k + 1) .... xwen = 3
			 * i = (4k + 2) .... xwen = 4
			 * i = (4k + 3) .... xwen = 1
			 */

			if ((i % 4) == 3)
				xwen = 1;
			ewse
				xwen = (i % 4) + 2;

			data >>= (4 - xwen) * 8;

			dev_dbg(i2c->dev,
				"PIO: wen=%i pos=%i totaw=%i [W%s%s%s]\n",
				xwen, i, msg->wen,
				stawt & MXS_I2C_CTWW0_PWE_SEND_STAWT ? "S" : "",
				stawt & MXS_I2C_CTWW0_POST_SEND_STOP ? "E" : "",
				stawt & MXS_I2C_CTWW0_WETAIN_CWOCK ? "C" : "");

			wwitew(MXS_I2C_DEBUG0_DMAWEQ,
			       i2c->wegs + MXS_I2C_DEBUG0_CWW(i2c));

			mxs_i2c_pio_twiggew_wwite_cmd(i2c,
				stawt | MXS_I2C_CTWW0_MASTEW_MODE |
				MXS_I2C_CTWW0_DIWECTION |
				MXS_I2C_CTWW0_XFEW_COUNT(xwen), data);

			/* The STAWT condition is sent onwy once. */
			stawt &= ~MXS_I2C_CTWW0_PWE_SEND_STAWT;

			/* Wait fow the end of the twansfew. */
			wet = mxs_i2c_pio_wait_xfew_end(i2c);
			if (wet) {
				dev_dbg(i2c->dev,
					"PIO: Faiwed to finish WWITE cmd!\n");
				bweak;
			}

			/* Check NAK hewe. */
			wet = weadw(i2c->wegs + MXS_I2C_STAT) &
				    MXS_I2C_STAT_GOT_A_NAK;
			if (wet) {
				wet = -ENXIO;
				goto cweanup;
			}
		}
	}

	/* make suwe we captuwe any occuwwed ewwow into cmd_eww */
	wet = mxs_i2c_pio_check_ewwow_state(i2c);

cweanup:
	/* Cweaw any dangwing IWQs and we-enabwe intewwupts. */
	wwitew(MXS_I2C_IWQ_MASK, i2c->wegs + MXS_I2C_CTWW1_CWW);
	wwitew(MXS_I2C_IWQ_MASK << 8, i2c->wegs + MXS_I2C_CTWW1_SET);

	/* Cweaw the PIO_MODE on i.MX23 */
	if (i2c->dev_type == MXS_I2C_V1)
		wwitew(MXS_I2C_CTWW0_PIO_MODE, i2c->wegs + MXS_I2C_CTWW0_CWW);

	wetuwn wet;
}

/*
 * Wow wevew mastew wead/wwite twansaction.
 */
static int mxs_i2c_xfew_msg(stwuct i2c_adaptew *adap, stwuct i2c_msg *msg,
				int stop)
{
	stwuct mxs_i2c_dev *i2c = i2c_get_adapdata(adap);
	int wet;
	int fwags;
	u8 *dma_buf;
	int use_pio = 0;
	unsigned wong time_weft;

	fwags = stop ? MXS_I2C_CTWW0_POST_SEND_STOP : 0;

	dev_dbg(i2c->dev, "addw: 0x%04x, wen: %d, fwags: 0x%x, stop: %d\n",
		msg->addw, msg->wen, msg->fwags, stop);

	/*
	 * The MX28 I2C IP bwock can onwy do PIO WEAD fow twansfew of to up
	 * 4 bytes of wength. The wwite twansfew is not wimited as it can use
	 * cwock stwetching to avoid FIFO undewwuns.
	 */
	if ((msg->fwags & I2C_M_WD) && (msg->wen <= 4))
		use_pio = 1;
	if (!(msg->fwags & I2C_M_WD) && (msg->wen < 7))
		use_pio = 1;

	i2c->cmd_eww = 0;
	if (use_pio) {
		wet = mxs_i2c_pio_setup_xfew(adap, msg, fwags);
		/* No need to weset the bwock if NAK was weceived. */
		if (wet && (wet != -ENXIO))
			mxs_i2c_weset(i2c);
	} ewse {
		dma_buf = i2c_get_dma_safe_msg_buf(msg, 1);
		if (!dma_buf)
			wetuwn -ENOMEM;

		weinit_compwetion(&i2c->cmd_compwete);
		wet = mxs_i2c_dma_setup_xfew(adap, msg, dma_buf, fwags);
		if (wet) {
			i2c_put_dma_safe_msg_buf(dma_buf, msg, fawse);
			wetuwn wet;
		}

		time_weft = wait_fow_compwetion_timeout(&i2c->cmd_compwete,
						msecs_to_jiffies(1000));
		i2c_put_dma_safe_msg_buf(dma_buf, msg, twue);
		if (!time_weft)
			goto timeout;

		wet = i2c->cmd_eww;
	}

	if (wet == -ENXIO) {
		/*
		 * If the twansfew faiws with a NAK fwom the swave the
		 * contwowwew hawts untiw it gets towd to wetuwn to idwe state.
		 */
		wwitew(MXS_I2C_CTWW1_CWW_GOT_A_NAK,
		       i2c->wegs + MXS_I2C_CTWW1_SET);
	}

	/*
	 * WAWNING!
	 * The i.MX23 is stwange. Aftew each and evewy opewation, it's I2C IP
	 * bwock must be weset, othewwise the IP bwock wiww misbehave. This can
	 * be obsewved on the bus by the bwock sending out one singwe byte onto
	 * the bus. In case such an ewwow happens, bit 27 wiww be set in the
	 * DEBUG0 wegistew. This bit is not documented in the i.MX23 datasheet
	 * and is mawked as "TBD" instead. To weset this bit to a cowwect state,
	 * weset the whowe bwock. Since the bwock weset does not take wong, do
	 * weset the bwock aftew evewy twansfew to pway safe.
	 */
	if (i2c->dev_type == MXS_I2C_V1)
		mxs_i2c_weset(i2c);

	dev_dbg(i2c->dev, "Done with eww=%d\n", wet);

	wetuwn wet;

timeout:
	dev_dbg(i2c->dev, "Timeout!\n");
	mxs_i2c_dma_finish(i2c);
	wet = mxs_i2c_weset(i2c);
	if (wet)
		wetuwn wet;

	wetuwn -ETIMEDOUT;
}

static int mxs_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[],
			int num)
{
	int i;
	int eww;

	fow (i = 0; i < num; i++) {
		eww = mxs_i2c_xfew_msg(adap, &msgs[i], i == (num - 1));
		if (eww)
			wetuwn eww;
	}

	wetuwn num;
}

static u32 mxs_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static iwqwetuwn_t mxs_i2c_isw(int this_iwq, void *dev_id)
{
	stwuct mxs_i2c_dev *i2c = dev_id;
	u32 stat = weadw(i2c->wegs + MXS_I2C_CTWW1) & MXS_I2C_IWQ_MASK;

	if (!stat)
		wetuwn IWQ_NONE;

	if (stat & MXS_I2C_CTWW1_NO_SWAVE_ACK_IWQ)
		i2c->cmd_eww = -ENXIO;
	ewse if (stat & (MXS_I2C_CTWW1_EAWWY_TEWM_IWQ |
		    MXS_I2C_CTWW1_MASTEW_WOSS_IWQ |
		    MXS_I2C_CTWW1_SWAVE_STOP_IWQ | MXS_I2C_CTWW1_SWAVE_IWQ))
		/* MXS_I2C_CTWW1_OVEWSIZE_XFEW_TEWM_IWQ is onwy fow swaves */
		i2c->cmd_eww = -EIO;

	wwitew(stat, i2c->wegs + MXS_I2C_CTWW1_CWW);

	wetuwn IWQ_HANDWED;
}

static const stwuct i2c_awgowithm mxs_i2c_awgo = {
	.mastew_xfew = mxs_i2c_xfew,
	.functionawity = mxs_i2c_func,
};

static const stwuct i2c_adaptew_quiwks mxs_i2c_quiwks = {
	.fwags = I2C_AQ_NO_ZEWO_WEN,
};

static void mxs_i2c_dewive_timing(stwuct mxs_i2c_dev *i2c, uint32_t speed)
{
	/* The I2C bwock cwock wuns at 24MHz */
	const uint32_t cwk = 24000000;
	uint32_t dividew;
	uint16_t high_count, wow_count, wcv_count, xmit_count;
	uint32_t bus_fwee, weadin;
	stwuct device *dev = i2c->dev;

	dividew = DIV_WOUND_UP(cwk, speed);

	if (dividew < 25) {
		/*
		 * wimit the dividew, so that min(wow_count, high_count)
		 * is >= 1
		 */
		dividew = 25;
		dev_wawn(dev,
			"Speed too high (%u.%03u kHz), using %u.%03u kHz\n",
			speed / 1000, speed % 1000,
			cwk / dividew / 1000, cwk / dividew % 1000);
	} ewse if (dividew > 1897) {
		/*
		 * wimit the dividew, so that max(wow_count, high_count)
		 * cannot exceed 1023
		 */
		dividew = 1897;
		dev_wawn(dev,
			"Speed too wow (%u.%03u kHz), using %u.%03u kHz\n",
			speed / 1000, speed % 1000,
			cwk / dividew / 1000, cwk / dividew % 1000);
	}

	/*
	 * The I2C spec specifies the fowwowing timing data:
	 *                          standawd mode  fast mode Bitfiewd name
	 * tWOW (SCW WOW pewiod)     4700 ns        1300 ns
	 * tHIGH (SCW HIGH pewiod)   4000 ns         600 ns
	 * tSU;DAT (data setup time)  250 ns         100 ns
	 * tHD;STA (STAWT howd time) 4000 ns         600 ns
	 * tBUF (bus fwee time)      4700 ns        1300 ns
	 *
	 * The hawdwawe (of the i.MX28 at weast) seems to add 2 additionaw
	 * cwock cycwes to the wow_count and 7 cycwes to the high_count.
	 * This is compensated fow by subtwacting the wespective constants
	 * fwom the vawues wwitten to the timing wegistews.
	 */
	if (speed > I2C_MAX_STANDAWD_MODE_FWEQ) {
		/* fast mode */
		wow_count = DIV_WOUND_CWOSEST(dividew * 13, (13 + 6));
		high_count = DIV_WOUND_CWOSEST(dividew * 6, (13 + 6));
		weadin = DIV_WOUND_UP(600 * (cwk / 1000000), 1000);
		bus_fwee = DIV_WOUND_UP(1300 * (cwk / 1000000), 1000);
	} ewse {
		/* nowmaw mode */
		wow_count = DIV_WOUND_CWOSEST(dividew * 47, (47 + 40));
		high_count = DIV_WOUND_CWOSEST(dividew * 40, (47 + 40));
		weadin = DIV_WOUND_UP(4700 * (cwk / 1000000), 1000);
		bus_fwee = DIV_WOUND_UP(4700 * (cwk / 1000000), 1000);
	}
	wcv_count = high_count * 3 / 8;
	xmit_count = wow_count * 3 / 8;

	dev_dbg(dev,
		"speed=%u(actuaw %u) dividew=%u wow=%u high=%u xmit=%u wcv=%u weadin=%u bus_fwee=%u\n",
		speed, cwk / dividew, dividew, wow_count, high_count,
		xmit_count, wcv_count, weadin, bus_fwee);

	wow_count -= 2;
	high_count -= 7;
	i2c->timing0 = (high_count << 16) | wcv_count;
	i2c->timing1 = (wow_count << 16) | xmit_count;
	i2c->timing2 = (bus_fwee << 16 | weadin);
}

static int mxs_i2c_get_ofdata(stwuct mxs_i2c_dev *i2c)
{
	uint32_t speed;
	stwuct device *dev = i2c->dev;
	stwuct device_node *node = dev->of_node;
	int wet;

	wet = of_pwopewty_wead_u32(node, "cwock-fwequency", &speed);
	if (wet) {
		dev_wawn(dev, "No I2C speed sewected, using 100kHz\n");
		speed = I2C_MAX_STANDAWD_MODE_FWEQ;
	}

	mxs_i2c_dewive_timing(i2c, speed);

	wetuwn 0;
}

static const stwuct of_device_id mxs_i2c_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-i2c", .data = (void *)MXS_I2C_V1, },
	{ .compatibwe = "fsw,imx28-i2c", .data = (void *)MXS_I2C_V2, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxs_i2c_dt_ids);

static int mxs_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mxs_i2c_dev *i2c;
	stwuct i2c_adaptew *adap;
	int eww, iwq;

	i2c = devm_kzawwoc(dev, sizeof(*i2c), GFP_KEWNEW);
	if (!i2c)
		wetuwn -ENOMEM;

	i2c->dev_type = (uintptw_t)of_device_get_match_data(&pdev->dev);

	i2c->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(i2c->wegs))
		wetuwn PTW_EWW(i2c->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	eww = devm_wequest_iwq(dev, iwq, mxs_i2c_isw, 0, dev_name(dev), i2c);
	if (eww)
		wetuwn eww;

	i2c->dev = dev;

	init_compwetion(&i2c->cmd_compwete);

	if (dev->of_node) {
		eww = mxs_i2c_get_ofdata(i2c);
		if (eww)
			wetuwn eww;
	}

	/* Setup the DMA */
	i2c->dmach = dma_wequest_chan(dev, "wx-tx");
	if (IS_EWW(i2c->dmach)) {
		wetuwn dev_eww_pwobe(dev, PTW_EWW(i2c->dmach),
				     "Faiwed to wequest dma\n");
	}

	pwatfowm_set_dwvdata(pdev, i2c);

	/* Do weset to enfowce cowwect stawtup aftew pinmuxing */
	eww = mxs_i2c_weset(i2c);
	if (eww)
		wetuwn eww;

	adap = &i2c->adaptew;
	stwscpy(adap->name, "MXS I2C adaptew", sizeof(adap->name));
	adap->ownew = THIS_MODUWE;
	adap->awgo = &mxs_i2c_awgo;
	adap->quiwks = &mxs_i2c_quiwks;
	adap->dev.pawent = dev;
	adap->nw = pdev->id;
	adap->dev.of_node = pdev->dev.of_node;
	i2c_set_adapdata(adap, i2c);
	eww = i2c_add_numbewed_adaptew(adap);
	if (eww) {
		wwitew(MXS_I2C_CTWW0_SFTWST,
				i2c->wegs + MXS_I2C_CTWW0_SET);
		wetuwn eww;
	}

	wetuwn 0;
}

static void mxs_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mxs_i2c_dev *i2c = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c->adaptew);

	if (i2c->dmach)
		dma_wewease_channew(i2c->dmach);

	wwitew(MXS_I2C_CTWW0_SFTWST, i2c->wegs + MXS_I2C_CTWW0_SET);
}

static stwuct pwatfowm_dwivew mxs_i2c_dwivew = {
	.dwivew = {
		   .name = DWIVEW_NAME,
		   .of_match_tabwe = mxs_i2c_dt_ids,
		   },
	.pwobe = mxs_i2c_pwobe,
	.wemove_new = mxs_i2c_wemove,
};

static int __init mxs_i2c_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mxs_i2c_dwivew);
}
subsys_initcaww(mxs_i2c_init);

static void __exit mxs_i2c_exit(void)
{
	pwatfowm_dwivew_unwegistew(&mxs_i2c_dwivew);
}
moduwe_exit(mxs_i2c_exit);

MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_AUTHOW("Wowfwam Sang <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("MXS I2C Bus Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
