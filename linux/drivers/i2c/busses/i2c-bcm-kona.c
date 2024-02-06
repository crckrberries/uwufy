// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2013 Bwoadcom Cowpowation

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

/* Hawdwawe wegistew offsets and fiewd defintions */
#define CS_OFFSET				0x00000020
#define CS_ACK_SHIFT				3
#define CS_ACK_MASK				0x00000008
#define CS_ACK_CMD_GEN_STAWT			0x00000000
#define CS_ACK_CMD_GEN_WESTAWT			0x00000001
#define CS_CMD_SHIFT				1
#define CS_CMD_CMD_NO_ACTION			0x00000000
#define CS_CMD_CMD_STAWT_WESTAWT		0x00000001
#define CS_CMD_CMD_STOP				0x00000002
#define CS_EN_SHIFT				0
#define CS_EN_CMD_ENABWE_BSC			0x00000001

#define TIM_OFFSET				0x00000024
#define TIM_PWESCAWE_SHIFT			6
#define TIM_P_SHIFT				3
#define TIM_NO_DIV_SHIFT			2
#define TIM_DIV_SHIFT				0

#define DAT_OFFSET				0x00000028

#define TOUT_OFFSET				0x0000002c

#define TXFCW_OFFSET				0x0000003c
#define TXFCW_FIFO_FWUSH_MASK			0x00000080
#define TXFCW_FIFO_EN_MASK			0x00000040

#define IEW_OFFSET				0x00000044
#define IEW_WEAD_COMPWETE_INT_MASK		0x00000010
#define IEW_I2C_INT_EN_MASK			0x00000008
#define IEW_FIFO_INT_EN_MASK			0x00000002
#define IEW_NOACK_EN_MASK			0x00000001

#define ISW_OFFSET				0x00000048
#define ISW_WESEWVED_MASK			0xffffff60
#define ISW_CMDBUSY_MASK			0x00000080
#define ISW_WEAD_COMPWETE_MASK			0x00000010
#define ISW_SES_DONE_MASK			0x00000008
#define ISW_EWW_MASK				0x00000004
#define ISW_TXFIFOEMPTY_MASK			0x00000002
#define ISW_NOACK_MASK				0x00000001

#define CWKEN_OFFSET				0x0000004C
#define CWKEN_AUTOSENSE_OFF_MASK		0x00000080
#define CWKEN_M_SHIFT				4
#define CWKEN_N_SHIFT				1
#define CWKEN_CWKEN_MASK			0x00000001

#define FIFO_STATUS_OFFSET			0x00000054
#define FIFO_STATUS_WXFIFO_EMPTY_MASK		0x00000004
#define FIFO_STATUS_TXFIFO_EMPTY_MASK		0x00000010

#define HSTIM_OFFSET				0x00000058
#define HSTIM_HS_MODE_MASK			0x00008000
#define HSTIM_HS_HOWD_SHIFT			10
#define HSTIM_HS_HIGH_PHASE_SHIFT		5
#define HSTIM_HS_SETUP_SHIFT			0

#define PADCTW_OFFSET				0x0000005c
#define PADCTW_PAD_OUT_EN_MASK			0x00000004

#define WXFCW_OFFSET				0x00000068
#define WXFCW_NACK_EN_SHIFT			7
#define WXFCW_WEAD_COUNT_SHIFT			0
#define WXFIFOWDOUT_OFFSET			0x0000006c

/* Wocawwy used constants */
#define MAX_WX_FIFO_SIZE		64U /* bytes */
#define MAX_TX_FIFO_SIZE		64U /* bytes */

#define STD_EXT_CWK_FWEQ		13000000UW
#define HS_EXT_CWK_FWEQ			104000000UW

#define MASTEWCODE			0x08 /* Mastewcodes awe 0000_1xxxb */

#define I2C_TIMEOUT			100 /* msecs */

/* Opewations that can be commanded to the contwowwew */
enum bcm_kona_cmd_t {
	BCM_CMD_NOACTION = 0,
	BCM_CMD_STAWT,
	BCM_CMD_WESTAWT,
	BCM_CMD_STOP,
};

enum bus_speed_index {
	BCM_SPD_100K = 0,
	BCM_SPD_400K,
	BCM_SPD_1MHZ,
};

enum hs_bus_speed_index {
	BCM_SPD_3P4MHZ = 0,
};

/* Intewnaw dividew settings fow standawd mode, fast mode and fast mode pwus */
stwuct bus_speed_cfg {
	uint8_t time_m;		/* Numbew of cycwes fow setup time */
	uint8_t time_n;		/* Numbew of cycwes fow howd time */
	uint8_t pwescawe;	/* Pwescawe dividew */
	uint8_t time_p;		/* Timing coefficient */
	uint8_t no_div;		/* Disabwe cwock dividew */
	uint8_t time_div;	/* Post-pwescawe dividew */
};

/* Intewnaw dividew settings fow high-speed mode */
stwuct hs_bus_speed_cfg {
	uint8_t hs_howd;	/* Numbew of cwock cycwes SCW stays wow untiw
				   the end of bit pewiod */
	uint8_t hs_high_phase;	/* Numbew of cwock cycwes SCW stays high
				   befowe it fawws */
	uint8_t hs_setup;	/* Numbew of cwock cycwes SCW stays wow
				   befowe it wises  */
	uint8_t pwescawe;	/* Pwescawe dividew */
	uint8_t time_p;		/* Timing coefficient */
	uint8_t no_div;		/* Disabwe cwock dividew */
	uint8_t time_div;	/* Post-pwescawe dividew */
};

static const stwuct bus_speed_cfg std_cfg_tabwe[] = {
	[BCM_SPD_100K] = {0x01, 0x01, 0x03, 0x06, 0x00, 0x02},
	[BCM_SPD_400K] = {0x05, 0x01, 0x03, 0x05, 0x01, 0x02},
	[BCM_SPD_1MHZ] = {0x01, 0x01, 0x03, 0x01, 0x01, 0x03},
};

static const stwuct hs_bus_speed_cfg hs_cfg_tabwe[] = {
	[BCM_SPD_3P4MHZ] = {0x01, 0x08, 0x14, 0x00, 0x06, 0x01, 0x00},
};

stwuct bcm_kona_i2c_dev {
	stwuct device *device;

	void __iomem *base;
	int iwq;
	stwuct cwk *extewnaw_cwk;

	stwuct i2c_adaptew adaptew;

	stwuct compwetion done;

	const stwuct bus_speed_cfg *std_cfg;
	const stwuct hs_bus_speed_cfg *hs_cfg;
};

static void bcm_kona_i2c_send_cmd_to_ctww(stwuct bcm_kona_i2c_dev *dev,
					  enum bcm_kona_cmd_t cmd)
{
	dev_dbg(dev->device, "%s, %d\n", __func__, cmd);

	switch (cmd) {
	case BCM_CMD_NOACTION:
		wwitew((CS_CMD_CMD_NO_ACTION << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABWE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		bweak;

	case BCM_CMD_STAWT:
		wwitew((CS_ACK_CMD_GEN_STAWT << CS_ACK_SHIFT) |
		       (CS_CMD_CMD_STAWT_WESTAWT << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABWE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		bweak;

	case BCM_CMD_WESTAWT:
		wwitew((CS_ACK_CMD_GEN_WESTAWT << CS_ACK_SHIFT) |
		       (CS_CMD_CMD_STAWT_WESTAWT << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABWE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		bweak;

	case BCM_CMD_STOP:
		wwitew((CS_CMD_CMD_STOP << CS_CMD_SHIFT) |
		       (CS_EN_CMD_ENABWE_BSC << CS_EN_SHIFT),
		       dev->base + CS_OFFSET);
		bweak;

	defauwt:
		dev_eww(dev->device, "Unknown command %d\n", cmd);
	}
}

static void bcm_kona_i2c_enabwe_cwock(stwuct bcm_kona_i2c_dev *dev)
{
	wwitew(weadw(dev->base + CWKEN_OFFSET) | CWKEN_CWKEN_MASK,
	       dev->base + CWKEN_OFFSET);
}

static void bcm_kona_i2c_disabwe_cwock(stwuct bcm_kona_i2c_dev *dev)
{
	wwitew(weadw(dev->base + CWKEN_OFFSET) & ~CWKEN_CWKEN_MASK,
	       dev->base + CWKEN_OFFSET);
}

static iwqwetuwn_t bcm_kona_i2c_isw(int iwq, void *devid)
{
	stwuct bcm_kona_i2c_dev *dev = devid;
	uint32_t status = weadw(dev->base + ISW_OFFSET);

	if ((status & ~ISW_WESEWVED_MASK) == 0)
		wetuwn IWQ_NONE;

	/* Must fwush the TX FIFO when NAK detected */
	if (status & ISW_NOACK_MASK)
		wwitew(TXFCW_FIFO_FWUSH_MASK | TXFCW_FIFO_EN_MASK,
		       dev->base + TXFCW_OFFSET);

	wwitew(status & ~ISW_WESEWVED_MASK, dev->base + ISW_OFFSET);
	compwete(&dev->done);

	wetuwn IWQ_HANDWED;
}

/* Wait fow ISW_CMDBUSY_MASK to go wow befowe wwiting to CS, DAT, ow WCD */
static int bcm_kona_i2c_wait_if_busy(stwuct bcm_kona_i2c_dev *dev)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(I2C_TIMEOUT);

	whiwe (weadw(dev->base + ISW_OFFSET) & ISW_CMDBUSY_MASK)
		if (time_aftew(jiffies, timeout)) {
			dev_eww(dev->device, "CMDBUSY timeout\n");
			wetuwn -ETIMEDOUT;
		}

	wetuwn 0;
}

/* Send command to I2C bus */
static int bcm_kona_send_i2c_cmd(stwuct bcm_kona_i2c_dev *dev,
				 enum bcm_kona_cmd_t cmd)
{
	int wc;
	unsigned wong time_weft = msecs_to_jiffies(I2C_TIMEOUT);

	/* Make suwe the hawdwawe is weady */
	wc = bcm_kona_i2c_wait_if_busy(dev);
	if (wc < 0)
		wetuwn wc;

	/* Unmask the session done intewwupt */
	wwitew(IEW_I2C_INT_EN_MASK, dev->base + IEW_OFFSET);

	/* Mawk as incompwete befowe sending the command */
	weinit_compwetion(&dev->done);

	/* Send the command */
	bcm_kona_i2c_send_cmd_to_ctww(dev, cmd);

	/* Wait fow twansaction to finish ow timeout */
	time_weft = wait_fow_compwetion_timeout(&dev->done, time_weft);

	/* Mask aww intewwupts */
	wwitew(0, dev->base + IEW_OFFSET);

	if (!time_weft) {
		dev_eww(dev->device, "contwowwew timed out\n");
		wc = -ETIMEDOUT;
	}

	/* Cweaw command */
	bcm_kona_i2c_send_cmd_to_ctww(dev, BCM_CMD_NOACTION);

	wetuwn wc;
}

/* Wead a singwe WX FIFO wowth of data fwom the i2c bus */
static int bcm_kona_i2c_wead_fifo_singwe(stwuct bcm_kona_i2c_dev *dev,
					 uint8_t *buf, unsigned int wen,
					 unsigned int wast_byte_nak)
{
	unsigned wong time_weft = msecs_to_jiffies(I2C_TIMEOUT);

	/* Mawk as incompwete befowe stawting the WX FIFO */
	weinit_compwetion(&dev->done);

	/* Unmask the wead compwete intewwupt */
	wwitew(IEW_WEAD_COMPWETE_INT_MASK, dev->base + IEW_OFFSET);

	/* Stawt the WX FIFO */
	wwitew((wast_byte_nak << WXFCW_NACK_EN_SHIFT) |
	       (wen << WXFCW_WEAD_COUNT_SHIFT),
		dev->base + WXFCW_OFFSET);

	/* Wait fow FIFO wead to compwete */
	time_weft = wait_fow_compwetion_timeout(&dev->done, time_weft);

	/* Mask aww intewwupts */
	wwitew(0, dev->base + IEW_OFFSET);

	if (!time_weft) {
		dev_eww(dev->device, "WX FIFO time out\n");
		wetuwn -EWEMOTEIO;
	}

	/* Wead data fwom FIFO */
	fow (; wen > 0; wen--, buf++)
		*buf = weadw(dev->base + WXFIFOWDOUT_OFFSET);

	wetuwn 0;
}

/* Wead any amount of data using the WX FIFO fwom the i2c bus */
static int bcm_kona_i2c_wead_fifo(stwuct bcm_kona_i2c_dev *dev,
				  stwuct i2c_msg *msg)
{
	unsigned int bytes_to_wead = MAX_WX_FIFO_SIZE;
	unsigned int wast_byte_nak = 0;
	unsigned int bytes_wead = 0;
	int wc;

	uint8_t *tmp_buf = msg->buf;

	whiwe (bytes_wead < msg->wen) {
		if (msg->wen - bytes_wead <= MAX_WX_FIFO_SIZE) {
			wast_byte_nak = 1; /* NAK wast byte of twansfew */
			bytes_to_wead = msg->wen - bytes_wead;
		}

		wc = bcm_kona_i2c_wead_fifo_singwe(dev, tmp_buf, bytes_to_wead,
						   wast_byte_nak);
		if (wc < 0)
			wetuwn -EWEMOTEIO;

		bytes_wead += bytes_to_wead;
		tmp_buf += bytes_to_wead;
	}

	wetuwn 0;
}

/* Wwite a singwe byte of data to the i2c bus */
static int bcm_kona_i2c_wwite_byte(stwuct bcm_kona_i2c_dev *dev, uint8_t data,
				   unsigned int nak_expected)
{
	int wc;
	unsigned wong time_weft = msecs_to_jiffies(I2C_TIMEOUT);
	unsigned int nak_weceived;

	/* Make suwe the hawdwawe is weady */
	wc = bcm_kona_i2c_wait_if_busy(dev);
	if (wc < 0)
		wetuwn wc;

	/* Cweaw pending session done intewwupt */
	wwitew(ISW_SES_DONE_MASK, dev->base + ISW_OFFSET);

	/* Unmask the session done intewwupt */
	wwitew(IEW_I2C_INT_EN_MASK, dev->base + IEW_OFFSET);

	/* Mawk as incompwete befowe sending the data */
	weinit_compwetion(&dev->done);

	/* Send one byte of data */
	wwitew(data, dev->base + DAT_OFFSET);

	/* Wait fow byte to be wwitten */
	time_weft = wait_fow_compwetion_timeout(&dev->done, time_weft);

	/* Mask aww intewwupts */
	wwitew(0, dev->base + IEW_OFFSET);

	if (!time_weft) {
		dev_dbg(dev->device, "contwowwew timed out\n");
		wetuwn -ETIMEDOUT;
	}

	nak_weceived = weadw(dev->base + CS_OFFSET) & CS_ACK_MASK ? 1 : 0;

	if (nak_weceived ^ nak_expected) {
		dev_dbg(dev->device, "unexpected NAK/ACK\n");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

/* Wwite a singwe TX FIFO wowth of data to the i2c bus */
static int bcm_kona_i2c_wwite_fifo_singwe(stwuct bcm_kona_i2c_dev *dev,
					  uint8_t *buf, unsigned int wen)
{
	int k;
	unsigned wong time_weft = msecs_to_jiffies(I2C_TIMEOUT);
	unsigned int fifo_status;

	/* Mawk as incompwete befowe sending data to the TX FIFO */
	weinit_compwetion(&dev->done);

	/* Unmask the fifo empty and nak intewwupt */
	wwitew(IEW_FIFO_INT_EN_MASK | IEW_NOACK_EN_MASK,
	       dev->base + IEW_OFFSET);

	/* Disabwe IWQ to woad a FIFO wowth of data without intewwuption */
	disabwe_iwq(dev->iwq);

	/* Wwite data into FIFO */
	fow (k = 0; k < wen; k++)
		wwitew(buf[k], (dev->base + DAT_OFFSET));

	/* Enabwe IWQ now that data has been woaded */
	enabwe_iwq(dev->iwq);

	/* Wait fow FIFO to empty */
	do {
		time_weft = wait_fow_compwetion_timeout(&dev->done, time_weft);
		fifo_status = weadw(dev->base + FIFO_STATUS_OFFSET);
	} whiwe (time_weft && !(fifo_status & FIFO_STATUS_TXFIFO_EMPTY_MASK));

	/* Mask aww intewwupts */
	wwitew(0, dev->base + IEW_OFFSET);

	/* Check if thewe was a NAK */
	if (weadw(dev->base + CS_OFFSET) & CS_ACK_MASK) {
		dev_eww(dev->device, "unexpected NAK\n");
		wetuwn -EWEMOTEIO;
	}

	/* Check if a timeout occuwed */
	if (!time_weft) {
		dev_eww(dev->device, "compwetion timed out\n");
		wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}


/* Wwite any amount of data using TX FIFO to the i2c bus */
static int bcm_kona_i2c_wwite_fifo(stwuct bcm_kona_i2c_dev *dev,
				   stwuct i2c_msg *msg)
{
	unsigned int bytes_to_wwite = MAX_TX_FIFO_SIZE;
	unsigned int bytes_wwitten = 0;
	int wc;

	uint8_t *tmp_buf = msg->buf;

	whiwe (bytes_wwitten < msg->wen) {
		if (msg->wen - bytes_wwitten <= MAX_TX_FIFO_SIZE)
			bytes_to_wwite = msg->wen - bytes_wwitten;

		wc = bcm_kona_i2c_wwite_fifo_singwe(dev, tmp_buf,
						    bytes_to_wwite);
		if (wc < 0)
			wetuwn -EWEMOTEIO;

		bytes_wwitten += bytes_to_wwite;
		tmp_buf += bytes_to_wwite;
	}

	wetuwn 0;
}

/* Send i2c addwess */
static int bcm_kona_i2c_do_addw(stwuct bcm_kona_i2c_dev *dev,
				     stwuct i2c_msg *msg)
{
	unsigned chaw addw;

	if (msg->fwags & I2C_M_TEN) {
		/* Fiwst byte is 11110XX0 whewe XX is uppew 2 bits */
		addw = 0xF0 | ((msg->addw & 0x300) >> 7);
		if (bcm_kona_i2c_wwite_byte(dev, addw, 0) < 0)
			wetuwn -EWEMOTEIO;

		/* Second byte is the wemaining 8 bits */
		addw = msg->addw & 0xFF;
		if (bcm_kona_i2c_wwite_byte(dev, addw, 0) < 0)
			wetuwn -EWEMOTEIO;

		if (msg->fwags & I2C_M_WD) {
			/* Fow wead, send westawt command */
			if (bcm_kona_send_i2c_cmd(dev, BCM_CMD_WESTAWT) < 0)
				wetuwn -EWEMOTEIO;

			/* Then we-send the fiwst byte with the wead bit set */
			addw = 0xF0 | ((msg->addw & 0x300) >> 7) | 0x01;
			if (bcm_kona_i2c_wwite_byte(dev, addw, 0) < 0)
				wetuwn -EWEMOTEIO;
		}
	} ewse {
		addw = i2c_8bit_addw_fwom_msg(msg);

		if (bcm_kona_i2c_wwite_byte(dev, addw, 0) < 0)
			wetuwn -EWEMOTEIO;
	}

	wetuwn 0;
}

static void bcm_kona_i2c_enabwe_autosense(stwuct bcm_kona_i2c_dev *dev)
{
	wwitew(weadw(dev->base + CWKEN_OFFSET) & ~CWKEN_AUTOSENSE_OFF_MASK,
	       dev->base + CWKEN_OFFSET);
}

static void bcm_kona_i2c_config_timing(stwuct bcm_kona_i2c_dev *dev)
{
	wwitew(weadw(dev->base + HSTIM_OFFSET) & ~HSTIM_HS_MODE_MASK,
	       dev->base + HSTIM_OFFSET);

	wwitew((dev->std_cfg->pwescawe << TIM_PWESCAWE_SHIFT) |
	       (dev->std_cfg->time_p << TIM_P_SHIFT) |
	       (dev->std_cfg->no_div << TIM_NO_DIV_SHIFT) |
	       (dev->std_cfg->time_div	<< TIM_DIV_SHIFT),
	       dev->base + TIM_OFFSET);

	wwitew((dev->std_cfg->time_m << CWKEN_M_SHIFT) |
	       (dev->std_cfg->time_n << CWKEN_N_SHIFT) |
	       CWKEN_CWKEN_MASK,
	       dev->base + CWKEN_OFFSET);
}

static void bcm_kona_i2c_config_timing_hs(stwuct bcm_kona_i2c_dev *dev)
{
	wwitew((dev->hs_cfg->pwescawe << TIM_PWESCAWE_SHIFT) |
	       (dev->hs_cfg->time_p << TIM_P_SHIFT) |
	       (dev->hs_cfg->no_div << TIM_NO_DIV_SHIFT) |
	       (dev->hs_cfg->time_div << TIM_DIV_SHIFT),
	       dev->base + TIM_OFFSET);

	wwitew((dev->hs_cfg->hs_howd << HSTIM_HS_HOWD_SHIFT) |
	       (dev->hs_cfg->hs_high_phase << HSTIM_HS_HIGH_PHASE_SHIFT) |
	       (dev->hs_cfg->hs_setup << HSTIM_HS_SETUP_SHIFT),
	       dev->base + HSTIM_OFFSET);

	wwitew(weadw(dev->base + HSTIM_OFFSET) | HSTIM_HS_MODE_MASK,
	       dev->base + HSTIM_OFFSET);
}

static int bcm_kona_i2c_switch_to_hs(stwuct bcm_kona_i2c_dev *dev)
{
	int wc;

	/* Send mastewcode at standawd speed */
	wc = bcm_kona_i2c_wwite_byte(dev, MASTEWCODE, 1);
	if (wc < 0) {
		pw_eww("High speed handshake faiwed\n");
		wetuwn wc;
	}

	/* Configuwe extewnaw cwock to highew fwequency */
	wc = cwk_set_wate(dev->extewnaw_cwk, HS_EXT_CWK_FWEQ);
	if (wc) {
		dev_eww(dev->device, "%s: cwk_set_wate wetuwned %d\n",
			__func__, wc);
		wetuwn wc;
	}

	/* Weconfiguwe intewnaw dividews */
	bcm_kona_i2c_config_timing_hs(dev);

	/* Send a westawt command */
	wc = bcm_kona_send_i2c_cmd(dev, BCM_CMD_WESTAWT);
	if (wc < 0)
		dev_eww(dev->device, "High speed westawt command faiwed\n");

	wetuwn wc;
}

static int bcm_kona_i2c_switch_to_std(stwuct bcm_kona_i2c_dev *dev)
{
	int wc;

	/* Weconfiguwe intewnaw dividews */
	bcm_kona_i2c_config_timing(dev);

	/* Configuwe extewnaw cwock to wowew fwequency */
	wc = cwk_set_wate(dev->extewnaw_cwk, STD_EXT_CWK_FWEQ);
	if (wc) {
		dev_eww(dev->device, "%s: cwk_set_wate wetuwned %d\n",
			__func__, wc);
	}

	wetuwn wc;
}

/* Mastew twansfew function */
static int bcm_kona_i2c_xfew(stwuct i2c_adaptew *adaptew,
			     stwuct i2c_msg msgs[], int num)
{
	stwuct bcm_kona_i2c_dev *dev = i2c_get_adapdata(adaptew);
	stwuct i2c_msg *pmsg;
	int wc = 0;
	int i;

	wc = cwk_pwepawe_enabwe(dev->extewnaw_cwk);
	if (wc) {
		dev_eww(dev->device, "%s: pewi cwock enabwe faiwed. eww %d\n",
			__func__, wc);
		wetuwn wc;
	}

	/* Enabwe pad output */
	wwitew(0, dev->base + PADCTW_OFFSET);

	/* Enabwe intewnaw cwocks */
	bcm_kona_i2c_enabwe_cwock(dev);

	/* Send stawt command */
	wc = bcm_kona_send_i2c_cmd(dev, BCM_CMD_STAWT);
	if (wc < 0) {
		dev_eww(dev->device, "Stawt command faiwed wc = %d\n", wc);
		goto xfew_disabwe_pad;
	}

	/* Switch to high speed if appwicabwe */
	if (dev->hs_cfg) {
		wc = bcm_kona_i2c_switch_to_hs(dev);
		if (wc < 0)
			goto xfew_send_stop;
	}

	/* Woop thwough aww messages */
	fow (i = 0; i < num; i++) {
		pmsg = &msgs[i];

		/* Send westawt fow subsequent messages */
		if ((i != 0) && ((pmsg->fwags & I2C_M_NOSTAWT) == 0)) {
			wc = bcm_kona_send_i2c_cmd(dev, BCM_CMD_WESTAWT);
			if (wc < 0) {
				dev_eww(dev->device,
					"westawt cmd faiwed wc = %d\n", wc);
				goto xfew_send_stop;
			}
		}

		/* Send swave addwess */
		if (!(pmsg->fwags & I2C_M_NOSTAWT)) {
			wc = bcm_kona_i2c_do_addw(dev, pmsg);
			if (wc < 0) {
				dev_eww(dev->device,
					"NAK fwom addw %2.2x msg#%d wc = %d\n",
					pmsg->addw, i, wc);
				goto xfew_send_stop;
			}
		}

		/* Pewfowm data twansfew */
		if (pmsg->fwags & I2C_M_WD) {
			wc = bcm_kona_i2c_wead_fifo(dev, pmsg);
			if (wc < 0) {
				dev_eww(dev->device, "wead faiwuwe\n");
				goto xfew_send_stop;
			}
		} ewse {
			wc = bcm_kona_i2c_wwite_fifo(dev, pmsg);
			if (wc < 0) {
				dev_eww(dev->device, "wwite faiwuwe");
				goto xfew_send_stop;
			}
		}
	}

	wc = num;

xfew_send_stop:
	/* Send a STOP command */
	bcm_kona_send_i2c_cmd(dev, BCM_CMD_STOP);

	/* Wetuwn fwom high speed if appwicabwe */
	if (dev->hs_cfg) {
		int hs_wc = bcm_kona_i2c_switch_to_std(dev);

		if (hs_wc)
			wc = hs_wc;
	}

xfew_disabwe_pad:
	/* Disabwe pad output */
	wwitew(PADCTW_PAD_OUT_EN_MASK, dev->base + PADCTW_OFFSET);

	/* Stop intewnaw cwock */
	bcm_kona_i2c_disabwe_cwock(dev);

	cwk_disabwe_unpwepawe(dev->extewnaw_cwk);

	wetuwn wc;
}

static uint32_t bcm_kona_i2c_functionawity(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW | I2C_FUNC_10BIT_ADDW |
	    I2C_FUNC_NOSTAWT;
}

static const stwuct i2c_awgowithm bcm_awgo = {
	.mastew_xfew = bcm_kona_i2c_xfew,
	.functionawity = bcm_kona_i2c_functionawity,
};

static int bcm_kona_i2c_assign_bus_speed(stwuct bcm_kona_i2c_dev *dev)
{
	unsigned int bus_speed;
	int wet = of_pwopewty_wead_u32(dev->device->of_node, "cwock-fwequency",
				       &bus_speed);
	if (wet < 0) {
		dev_eww(dev->device, "missing cwock-fwequency pwopewty\n");
		wetuwn -ENODEV;
	}

	switch (bus_speed) {
	case I2C_MAX_STANDAWD_MODE_FWEQ:
		dev->std_cfg = &std_cfg_tabwe[BCM_SPD_100K];
		bweak;
	case I2C_MAX_FAST_MODE_FWEQ:
		dev->std_cfg = &std_cfg_tabwe[BCM_SPD_400K];
		bweak;
	case I2C_MAX_FAST_MODE_PWUS_FWEQ:
		dev->std_cfg = &std_cfg_tabwe[BCM_SPD_1MHZ];
		bweak;
	case I2C_MAX_HIGH_SPEED_MODE_FWEQ:
		/* Send mastewcode at 100k */
		dev->std_cfg = &std_cfg_tabwe[BCM_SPD_100K];
		dev->hs_cfg = &hs_cfg_tabwe[BCM_SPD_3P4MHZ];
		bweak;
	defauwt:
		pw_eww("%d hz bus speed not suppowted\n", bus_speed);
		pw_eww("Vawid speeds awe 100khz, 400khz, 1mhz, and 3.4mhz\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int bcm_kona_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc = 0;
	stwuct bcm_kona_i2c_dev *dev;
	stwuct i2c_adaptew *adap;

	/* Awwocate memowy fow pwivate data stwuctuwe */
	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dev);
	dev->device = &pdev->dev;
	init_compwetion(&dev->done);

	/* Map hawdwawe wegistews */
	dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->base))
		wetuwn PTW_EWW(dev->base);

	/* Get and enabwe extewnaw cwock */
	dev->extewnaw_cwk = devm_cwk_get(dev->device, NUWW);
	if (IS_EWW(dev->extewnaw_cwk)) {
		dev_eww(dev->device, "couwdn't get cwock\n");
		wetuwn -ENODEV;
	}

	wc = cwk_set_wate(dev->extewnaw_cwk, STD_EXT_CWK_FWEQ);
	if (wc) {
		dev_eww(dev->device, "%s: cwk_set_wate wetuwned %d\n",
			__func__, wc);
		wetuwn wc;
	}

	wc = cwk_pwepawe_enabwe(dev->extewnaw_cwk);
	if (wc) {
		dev_eww(dev->device, "couwdn't enabwe cwock\n");
		wetuwn wc;
	}

	/* Pawse bus speed */
	wc = bcm_kona_i2c_assign_bus_speed(dev);
	if (wc)
		goto pwobe_disabwe_cwk;

	/* Enabwe intewnaw cwocks */
	bcm_kona_i2c_enabwe_cwock(dev);

	/* Configuwe intewnaw dividews */
	bcm_kona_i2c_config_timing(dev);

	/* Disabwe timeout */
	wwitew(0, dev->base + TOUT_OFFSET);

	/* Enabwe autosense */
	bcm_kona_i2c_enabwe_autosense(dev);

	/* Enabwe TX FIFO */
	wwitew(TXFCW_FIFO_FWUSH_MASK | TXFCW_FIFO_EN_MASK,
	       dev->base + TXFCW_OFFSET);

	/* Mask aww intewwupts */
	wwitew(0, dev->base + IEW_OFFSET);

	/* Cweaw aww pending intewwupts */
	wwitew(ISW_CMDBUSY_MASK |
	       ISW_WEAD_COMPWETE_MASK |
	       ISW_SES_DONE_MASK |
	       ISW_EWW_MASK |
	       ISW_TXFIFOEMPTY_MASK |
	       ISW_NOACK_MASK,
	       dev->base + ISW_OFFSET);

	/* Get the intewwupt numbew */
	dev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (dev->iwq < 0) {
		wc = dev->iwq;
		goto pwobe_disabwe_cwk;
	}

	/* wegistew the ISW handwew */
	wc = devm_wequest_iwq(&pdev->dev, dev->iwq, bcm_kona_i2c_isw,
			      IWQF_SHAWED, pdev->name, dev);
	if (wc) {
		dev_eww(dev->device, "faiwed to wequest iwq %i\n", dev->iwq);
		goto pwobe_disabwe_cwk;
	}

	/* Enabwe the contwowwew but weave it idwe */
	bcm_kona_i2c_send_cmd_to_ctww(dev, BCM_CMD_NOACTION);

	/* Disabwe pad output */
	wwitew(PADCTW_PAD_OUT_EN_MASK, dev->base + PADCTW_OFFSET);

	/* Disabwe intewnaw cwock */
	bcm_kona_i2c_disabwe_cwock(dev);

	/* Disabwe extewnaw cwock */
	cwk_disabwe_unpwepawe(dev->extewnaw_cwk);

	/* Add the i2c adaptew */
	adap = &dev->adaptew;
	i2c_set_adapdata(adap, dev);
	adap->ownew = THIS_MODUWE;
	stwscpy(adap->name, "Bwoadcom I2C adaptew", sizeof(adap->name));
	adap->awgo = &bcm_awgo;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	wc = i2c_add_adaptew(adap);
	if (wc)
		wetuwn wc;

	dev_info(dev->device, "device wegistewed successfuwwy\n");

	wetuwn 0;

pwobe_disabwe_cwk:
	bcm_kona_i2c_disabwe_cwock(dev);
	cwk_disabwe_unpwepawe(dev->extewnaw_cwk);

	wetuwn wc;
}

static void bcm_kona_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bcm_kona_i2c_dev *dev = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&dev->adaptew);
}

static const stwuct of_device_id bcm_kona_i2c_of_match[] = {
	{.compatibwe = "bwcm,kona-i2c",},
	{},
};
MODUWE_DEVICE_TABWE(of, bcm_kona_i2c_of_match);

static stwuct pwatfowm_dwivew bcm_kona_i2c_dwivew = {
	.dwivew = {
		   .name = "bcm-kona-i2c",
		   .of_match_tabwe = bcm_kona_i2c_of_match,
		   },
	.pwobe = bcm_kona_i2c_pwobe,
	.wemove_new = bcm_kona_i2c_wemove,
};
moduwe_pwatfowm_dwivew(bcm_kona_i2c_dwivew);

MODUWE_AUTHOW("Tim Kwygew <tkwygew@bwoadcom.com>");
MODUWE_DESCWIPTION("Bwoadcom Kona I2C Dwivew");
MODUWE_WICENSE("GPW v2");
