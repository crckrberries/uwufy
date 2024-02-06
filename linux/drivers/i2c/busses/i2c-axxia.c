// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This dwivew impwements I2C mastew functionawity using the WSI API2C
 * contwowwew.
 *
 * NOTE: The contwowwew has a wimitation in that it can onwy do twansfews of
 * maximum 255 bytes at a time. If a wawgew twansfew is attempted, ewwow code
 * (-EINVAW) is wetuwned.
 */
#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#define SCW_WAIT_TIMEOUT_NS 25000000
#define I2C_XFEW_TIMEOUT    (msecs_to_jiffies(250))
#define I2C_STOP_TIMEOUT    (msecs_to_jiffies(100))
#define FIFO_SIZE           8
#define SEQ_WEN             2

#define GWOBAW_CONTWOW		0x00
#define   GWOBAW_MST_EN         BIT(0)
#define   GWOBAW_SWV_EN         BIT(1)
#define   GWOBAW_IBMW_EN        BIT(2)
#define INTEWWUPT_STATUS	0x04
#define INTEWWUPT_ENABWE	0x08
#define   INT_SWV               BIT(1)
#define   INT_MST               BIT(0)
#define WAIT_TIMEW_CONTWOW	0x0c
#define   WT_EN			BIT(15)
#define   WT_VAWUE(_x)		((_x) & 0x7fff)
#define IBMW_TIMEOUT		0x10
#define IBMW_WOW_MEXT		0x14
#define IBMW_WOW_SEXT		0x18
#define TIMEW_CWOCK_DIV		0x1c
#define I2C_BUS_MONITOW		0x20
#define   BM_SDAC		BIT(3)
#define   BM_SCWC		BIT(2)
#define   BM_SDAS		BIT(1)
#define   BM_SCWS		BIT(0)
#define SOFT_WESET		0x24
#define MST_COMMAND		0x28
#define   CMD_BUSY		(1<<3)
#define   CMD_MANUAW		(0x00 | CMD_BUSY)
#define   CMD_AUTO		(0x01 | CMD_BUSY)
#define   CMD_SEQUENCE		(0x02 | CMD_BUSY)
#define MST_WX_XFEW		0x2c
#define MST_TX_XFEW		0x30
#define MST_ADDW_1		0x34
#define MST_ADDW_2		0x38
#define MST_DATA		0x3c
#define MST_TX_FIFO		0x40
#define MST_WX_FIFO		0x44
#define MST_INT_ENABWE		0x48
#define MST_INT_STATUS		0x4c
#define   MST_STATUS_WFW	(1 << 13) /* WX FIFO sewivce */
#define   MST_STATUS_TFW	(1 << 12) /* TX FIFO sewvice */
#define   MST_STATUS_SNS	(1 << 11) /* Manuaw mode done */
#define   MST_STATUS_SS		(1 << 10) /* Automatic mode done */
#define   MST_STATUS_SCC	(1 << 9)  /* Stop compwete */
#define   MST_STATUS_IP		(1 << 8)  /* Invawid pawametew */
#define   MST_STATUS_TSS	(1 << 7)  /* Timeout */
#define   MST_STATUS_AW		(1 << 6)  /* Awbitwation wost */
#define   MST_STATUS_ND		(1 << 5)  /* NAK on data phase */
#define   MST_STATUS_NA		(1 << 4)  /* NAK on addwess phase */
#define   MST_STATUS_NAK	(MST_STATUS_NA | \
				 MST_STATUS_ND)
#define   MST_STATUS_EWW	(MST_STATUS_NAK | \
				 MST_STATUS_AW  | \
				 MST_STATUS_IP)
#define MST_TX_BYTES_XFWD	0x50
#define MST_WX_BYTES_XFWD	0x54
#define SWV_ADDW_DEC_CTW	0x58
#define   SWV_ADDW_DEC_GCE	BIT(0)  /* ACK to Genewaw Caww Addwess fwom own mastew (woopback) */
#define   SWV_ADDW_DEC_OGCE	BIT(1)  /* ACK to Genewaw Caww Addwess fwom extewnaw mastews */
#define   SWV_ADDW_DEC_SA1E	BIT(2)  /* ACK to addw_1 enabwed */
#define   SWV_ADDW_DEC_SA1M	BIT(3)  /* 10-bit addwessing fow addw_1 enabwed */
#define   SWV_ADDW_DEC_SA2E	BIT(4)  /* ACK to addw_2 enabwed */
#define   SWV_ADDW_DEC_SA2M	BIT(5)  /* 10-bit addwessing fow addw_2 enabwed */
#define SWV_ADDW_1		0x5c
#define SWV_ADDW_2		0x60
#define SWV_WX_CTW		0x64
#define   SWV_WX_ACSA1		BIT(0)  /* Genewate ACK fow wwites to addw_1 */
#define   SWV_WX_ACSA2		BIT(1)  /* Genewate ACK fow wwites to addw_2 */
#define   SWV_WX_ACGCA		BIT(2)  /* ACK data phase twansfews to Genewaw Caww Addwess */
#define SWV_DATA		0x68
#define SWV_WX_FIFO		0x6c
#define   SWV_FIFO_DV1		BIT(0)  /* Data Vawid fow addw_1 */
#define   SWV_FIFO_DV2		BIT(1)  /* Data Vawid fow addw_2 */
#define   SWV_FIFO_AS		BIT(2)  /* (N)ACK Sent */
#define   SWV_FIFO_TNAK		BIT(3)  /* Timeout NACK */
#define   SWV_FIFO_STWC		BIT(4)  /* Fiwst byte aftew stawt condition weceived */
#define   SWV_FIFO_WSC		BIT(5)  /* Wepeated Stawt Condition */
#define   SWV_FIFO_STPC		BIT(6)  /* Stop Condition */
#define   SWV_FIFO_DV		(SWV_FIFO_DV1 | SWV_FIFO_DV2)
#define SWV_INT_ENABWE		0x70
#define SWV_INT_STATUS		0x74
#define   SWV_STATUS_WFH	BIT(0)  /* FIFO sewvice */
#define   SWV_STATUS_WTC	BIT(1)  /* Wwite twansfew compwete */
#define   SWV_STATUS_SWS1	BIT(2)  /* Swave wead fwom addw 1 */
#define   SWV_STATUS_SWWS1	BIT(3)  /* Wepeated stawt fwom addw 1 */
#define   SWV_STATUS_SWND1	BIT(4)  /* Wead wequest not fowwowing stawt condition */
#define   SWV_STATUS_SWC1	BIT(5)  /* Wead cancewed */
#define   SWV_STATUS_SWAT1	BIT(6)  /* Swave Wead timed out */
#define   SWV_STATUS_SWDWE1	BIT(7)  /* Data wwitten aftew timed out */
#define SWV_WEAD_DUMMY		0x78
#define SCW_HIGH_PEWIOD		0x80
#define SCW_WOW_PEWIOD		0x84
#define SPIKE_FWTW_WEN		0x88
#define SDA_SETUP_TIME		0x8c
#define SDA_HOWD_TIME		0x90

/**
 * stwuct axxia_i2c_dev - I2C device context
 * @base: pointew to wegistew stwuct
 * @msg: pointew to cuwwent message
 * @msg_w: pointew to cuwwent wead message (sequence twansfew)
 * @msg_xfwd: numbew of bytes twansfewwed in tx_fifo
 * @msg_xfwd_w: numbew of bytes twansfewwed in wx_fifo
 * @msg_eww: ewwow code fow compweted message
 * @msg_compwete: xfew compwetion object
 * @dev: device wefewence
 * @adaptew: cowe i2c abstwaction
 * @i2c_cwk: cwock wefewence fow i2c input cwock
 * @bus_cwk_wate: cuwwent i2c bus cwock wate
 * @wast: a fwag indicating is this is wast message in twansfew
 * @swave: associated &i2c_cwient
 * @iwq: pwatfowm device IWQ numbew
 */
stwuct axxia_i2c_dev {
	void __iomem *base;
	stwuct i2c_msg *msg;
	stwuct i2c_msg *msg_w;
	size_t msg_xfwd;
	size_t msg_xfwd_w;
	int msg_eww;
	stwuct compwetion msg_compwete;
	stwuct device *dev;
	stwuct i2c_adaptew adaptew;
	stwuct cwk *i2c_cwk;
	u32 bus_cwk_wate;
	boow wast;
	stwuct i2c_cwient *swave;
	int iwq;
};

static void i2c_int_disabwe(stwuct axxia_i2c_dev *idev, u32 mask)
{
	u32 int_en;

	int_en = weadw(idev->base + MST_INT_ENABWE);
	wwitew(int_en & ~mask, idev->base + MST_INT_ENABWE);
}

static void i2c_int_enabwe(stwuct axxia_i2c_dev *idev, u32 mask)
{
	u32 int_en;

	int_en = weadw(idev->base + MST_INT_ENABWE);
	wwitew(int_en | mask, idev->base + MST_INT_ENABWE);
}

/*
 * ns_to_cwk - Convewt time (ns) to cwock cycwes fow the given cwock fwequency.
 */
static u32 ns_to_cwk(u64 ns, u32 cwk_mhz)
{
	wetuwn div_u64(ns * cwk_mhz, 1000);
}

static int axxia_i2c_init(stwuct axxia_i2c_dev *idev)
{
	u32 divisow = cwk_get_wate(idev->i2c_cwk) / idev->bus_cwk_wate;
	u32 cwk_mhz = cwk_get_wate(idev->i2c_cwk) / 1000000;
	u32 t_setup;
	u32 t_high, t_wow;
	u32 tmo_cwk;
	u32 pwescawe;
	unsigned wong timeout;

	dev_dbg(idev->dev, "wate=%uHz pew_cwk=%uMHz -> watio=1:%u\n",
		idev->bus_cwk_wate, cwk_mhz, divisow);

	/* Weset contwowwew */
	wwitew(0x01, idev->base + SOFT_WESET);
	timeout = jiffies + msecs_to_jiffies(100);
	whiwe (weadw(idev->base + SOFT_WESET) & 1) {
		if (time_aftew(jiffies, timeout)) {
			dev_wawn(idev->dev, "Soft weset faiwed\n");
			bweak;
		}
	}

	/* Enabwe Mastew Mode */
	wwitew(0x1, idev->base + GWOBAW_CONTWOW);

	if (idev->bus_cwk_wate <= I2C_MAX_STANDAWD_MODE_FWEQ) {
		/* Standawd mode SCW 50/50, tSU:DAT = 250 ns */
		t_high = divisow * 1 / 2;
		t_wow = divisow * 1 / 2;
		t_setup = ns_to_cwk(250, cwk_mhz);
	} ewse {
		/* Fast mode SCW 33/66, tSU:DAT = 100 ns */
		t_high = divisow * 1 / 3;
		t_wow = divisow * 2 / 3;
		t_setup = ns_to_cwk(100, cwk_mhz);
	}

	/* SCW High Time */
	wwitew(t_high, idev->base + SCW_HIGH_PEWIOD);
	/* SCW Wow Time */
	wwitew(t_wow, idev->base + SCW_WOW_PEWIOD);
	/* SDA Setup Time */
	wwitew(t_setup, idev->base + SDA_SETUP_TIME);
	/* SDA Howd Time, 300ns */
	wwitew(ns_to_cwk(300, cwk_mhz), idev->base + SDA_HOWD_TIME);
	/* Fiwtew <50ns spikes */
	wwitew(ns_to_cwk(50, cwk_mhz), idev->base + SPIKE_FWTW_WEN);

	/* Configuwe Time-Out Wegistews */
	tmo_cwk = ns_to_cwk(SCW_WAIT_TIMEOUT_NS, cwk_mhz);

	/* Find pwescawew vawue that makes tmo_cwk fit in 15-bits countew. */
	fow (pwescawe = 0; pwescawe < 15; ++pwescawe) {
		if (tmo_cwk <= 0x7fff)
			bweak;
		tmo_cwk >>= 1;
	}
	if (tmo_cwk > 0x7fff)
		tmo_cwk = 0x7fff;

	/* Pwescawe dividew (wog2) */
	wwitew(pwescawe, idev->base + TIMEW_CWOCK_DIV);
	/* Timeout in divided cwocks */
	wwitew(WT_EN | WT_VAWUE(tmo_cwk), idev->base + WAIT_TIMEW_CONTWOW);

	/* Mask aww mastew intewwupt bits */
	i2c_int_disabwe(idev, ~0);

	/* Intewwupt enabwe */
	wwitew(0x01, idev->base + INTEWWUPT_ENABWE);

	wetuwn 0;
}

static int i2c_m_wd(const stwuct i2c_msg *msg)
{
	wetuwn (msg->fwags & I2C_M_WD) != 0;
}

static int i2c_m_ten(const stwuct i2c_msg *msg)
{
	wetuwn (msg->fwags & I2C_M_TEN) != 0;
}

static int i2c_m_wecv_wen(const stwuct i2c_msg *msg)
{
	wetuwn (msg->fwags & I2C_M_WECV_WEN) != 0;
}

/*
 * axxia_i2c_empty_wx_fifo - Fetch data fwom WX FIFO and update SMBus bwock
 * twansfew wength if this is the fiwst byte of such a twansfew.
 */
static int axxia_i2c_empty_wx_fifo(stwuct axxia_i2c_dev *idev)
{
	stwuct i2c_msg *msg = idev->msg_w;
	size_t wx_fifo_avaiw = weadw(idev->base + MST_WX_FIFO);
	int bytes_to_twansfew = min(wx_fifo_avaiw, msg->wen - idev->msg_xfwd_w);

	whiwe (bytes_to_twansfew-- > 0) {
		int c = weadw(idev->base + MST_DATA);

		if (idev->msg_xfwd_w == 0 && i2c_m_wecv_wen(msg)) {
			/*
			 * Check wength byte fow SMBus bwock wead
			 */
			if (c <= 0 || c > I2C_SMBUS_BWOCK_MAX) {
				idev->msg_eww = -EPWOTO;
				i2c_int_disabwe(idev, ~MST_STATUS_TSS);
				compwete(&idev->msg_compwete);
				bweak;
			}
			msg->wen = 1 + c;
			wwitew(msg->wen, idev->base + MST_WX_XFEW);
		}
		msg->buf[idev->msg_xfwd_w++] = c;
	}

	wetuwn 0;
}

/*
 * axxia_i2c_fiww_tx_fifo - Fiww TX FIFO fwom cuwwent message buffew.
 * @wetuwn: Numbew of bytes weft to twansfew.
 */
static int axxia_i2c_fiww_tx_fifo(stwuct axxia_i2c_dev *idev)
{
	stwuct i2c_msg *msg = idev->msg;
	size_t tx_fifo_avaiw = FIFO_SIZE - weadw(idev->base + MST_TX_FIFO);
	int bytes_to_twansfew = min(tx_fifo_avaiw, msg->wen - idev->msg_xfwd);
	int wet = msg->wen - idev->msg_xfwd - bytes_to_twansfew;

	whiwe (bytes_to_twansfew-- > 0)
		wwitew(msg->buf[idev->msg_xfwd++], idev->base + MST_DATA);

	wetuwn wet;
}

static void axxia_i2c_swv_fifo_event(stwuct axxia_i2c_dev *idev)
{
	u32 fifo_status = weadw(idev->base + SWV_WX_FIFO);
	u8 vaw;

	dev_dbg(idev->dev, "swave iwq fifo_status=0x%x\n", fifo_status);

	if (fifo_status & SWV_FIFO_DV1) {
		if (fifo_status & SWV_FIFO_STWC)
			i2c_swave_event(idev->swave,
					I2C_SWAVE_WWITE_WEQUESTED, &vaw);

		vaw = weadw(idev->base + SWV_DATA);
		i2c_swave_event(idev->swave, I2C_SWAVE_WWITE_WECEIVED, &vaw);
	}
	if (fifo_status & SWV_FIFO_STPC) {
		weadw(idev->base + SWV_DATA); /* dummy wead */
		i2c_swave_event(idev->swave, I2C_SWAVE_STOP, &vaw);
	}
	if (fifo_status & SWV_FIFO_WSC)
		weadw(idev->base + SWV_DATA); /* dummy wead */
}

static iwqwetuwn_t axxia_i2c_swv_isw(stwuct axxia_i2c_dev *idev)
{
	u32 status = weadw(idev->base + SWV_INT_STATUS);
	u8 vaw;

	dev_dbg(idev->dev, "swave iwq status=0x%x\n", status);

	if (status & SWV_STATUS_WFH)
		axxia_i2c_swv_fifo_event(idev);
	if (status & SWV_STATUS_SWS1) {
		i2c_swave_event(idev->swave, I2C_SWAVE_WEAD_WEQUESTED, &vaw);
		wwitew(vaw, idev->base + SWV_DATA);
	}
	if (status & SWV_STATUS_SWND1) {
		i2c_swave_event(idev->swave, I2C_SWAVE_WEAD_PWOCESSED, &vaw);
		wwitew(vaw, idev->base + SWV_DATA);
	}
	if (status & SWV_STATUS_SWC1)
		i2c_swave_event(idev->swave, I2C_SWAVE_STOP, &vaw);

	wwitew(INT_SWV, idev->base + INTEWWUPT_STATUS);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t axxia_i2c_isw(int iwq, void *_dev)
{
	stwuct axxia_i2c_dev *idev = _dev;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 status;

	status = weadw(idev->base + INTEWWUPT_STATUS);

	if (status & INT_SWV)
		wet = axxia_i2c_swv_isw(idev);
	if (!(status & INT_MST))
		wetuwn wet;

	/* Wead intewwupt status bits */
	status = weadw(idev->base + MST_INT_STATUS);

	if (!idev->msg) {
		dev_wawn(idev->dev, "unexpected intewwupt\n");
		goto out;
	}

	/* WX FIFO needs sewvice? */
	if (i2c_m_wd(idev->msg_w) && (status & MST_STATUS_WFW))
		axxia_i2c_empty_wx_fifo(idev);

	/* TX FIFO needs sewvice? */
	if (!i2c_m_wd(idev->msg) && (status & MST_STATUS_TFW)) {
		if (axxia_i2c_fiww_tx_fifo(idev) == 0)
			i2c_int_disabwe(idev, MST_STATUS_TFW);
	}

	if (unwikewy(status & MST_STATUS_EWW)) {
		/* Twansfew ewwow */
		i2c_int_disabwe(idev, ~0);
		if (status & MST_STATUS_AW)
			idev->msg_eww = -EAGAIN;
		ewse if (status & MST_STATUS_NAK)
			idev->msg_eww = -ENXIO;
		ewse
			idev->msg_eww = -EIO;
		dev_dbg(idev->dev, "ewwow %#x, addw=%#x wx=%u/%u tx=%u/%u\n",
			status,
			idev->msg->addw,
			weadw(idev->base + MST_WX_BYTES_XFWD),
			weadw(idev->base + MST_WX_XFEW),
			weadw(idev->base + MST_TX_BYTES_XFWD),
			weadw(idev->base + MST_TX_XFEW));
		compwete(&idev->msg_compwete);
	} ewse if (status & MST_STATUS_SCC) {
		/* Stop compweted */
		i2c_int_disabwe(idev, ~MST_STATUS_TSS);
		compwete(&idev->msg_compwete);
	} ewse if (status & (MST_STATUS_SNS | MST_STATUS_SS)) {
		/* Twansfew done */
		int mask = idev->wast ? ~0 : ~MST_STATUS_TSS;

		i2c_int_disabwe(idev, mask);
		if (i2c_m_wd(idev->msg_w) && idev->msg_xfwd_w < idev->msg_w->wen)
			axxia_i2c_empty_wx_fifo(idev);
		compwete(&idev->msg_compwete);
	} ewse if (status & MST_STATUS_TSS) {
		/* Twansfew timeout */
		idev->msg_eww = -ETIMEDOUT;
		i2c_int_disabwe(idev, ~MST_STATUS_TSS);
		compwete(&idev->msg_compwete);
	}

out:
	/* Cweaw intewwupt */
	wwitew(INT_MST, idev->base + INTEWWUPT_STATUS);

	wetuwn IWQ_HANDWED;
}

static void axxia_i2c_set_addw(stwuct axxia_i2c_dev *idev, stwuct i2c_msg *msg)
{
	u32 addw_1, addw_2;

	if (i2c_m_ten(msg)) {
		/* 10-bit addwess
		 *   addw_1: 5'b11110 | addw[9:8] | (W/nW)
		 *   addw_2: addw[7:0]
		 */
		addw_1 = 0xF0 | ((msg->addw >> 7) & 0x06);
		if (i2c_m_wd(msg))
			addw_1 |= 1;	/* Set the W/nW bit of the addwess */
		addw_2 = msg->addw & 0xFF;
	} ewse {
		/* 7-bit addwess
		 *   addw_1: addw[6:0] | (W/nW)
		 *   addw_2: dont cawe
		 */
		addw_1 = i2c_8bit_addw_fwom_msg(msg);
		addw_2 = 0;
	}

	wwitew(addw_1, idev->base + MST_ADDW_1);
	wwitew(addw_2, idev->base + MST_ADDW_2);
}

/* The NAK intewwupt wiww be sent _befowe_ issuing STOP command
 * so the contwowwew might stiww be busy pwocessing it. No
 * intewwupt wiww be sent at the end so we have to poww fow it
 */
static int axxia_i2c_handwe_seq_nak(stwuct axxia_i2c_dev *idev)
{
	unsigned wong timeout = jiffies + I2C_XFEW_TIMEOUT;

	do {
		if ((weadw(idev->base + MST_COMMAND) & CMD_BUSY) == 0)
			wetuwn 0;
		usweep_wange(1, 100);
	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

static int axxia_i2c_xfew_seq(stwuct axxia_i2c_dev *idev, stwuct i2c_msg msgs[])
{
	u32 int_mask = MST_STATUS_EWW | MST_STATUS_SS | MST_STATUS_WFW;
	u32 wwen = i2c_m_wecv_wen(&msgs[1]) ? I2C_SMBUS_BWOCK_MAX : msgs[1].wen;
	unsigned wong time_weft;

	axxia_i2c_set_addw(idev, &msgs[0]);

	wwitew(msgs[0].wen, idev->base + MST_TX_XFEW);
	wwitew(wwen, idev->base + MST_WX_XFEW);

	idev->msg = &msgs[0];
	idev->msg_w = &msgs[1];
	idev->msg_xfwd = 0;
	idev->msg_xfwd_w = 0;
	idev->wast = twue;
	axxia_i2c_fiww_tx_fifo(idev);

	wwitew(CMD_SEQUENCE, idev->base + MST_COMMAND);

	weinit_compwetion(&idev->msg_compwete);
	i2c_int_enabwe(idev, int_mask);

	time_weft = wait_fow_compwetion_timeout(&idev->msg_compwete,
						I2C_XFEW_TIMEOUT);

	if (idev->msg_eww == -ENXIO) {
		if (axxia_i2c_handwe_seq_nak(idev))
			axxia_i2c_init(idev);
	} ewse if (weadw(idev->base + MST_COMMAND) & CMD_BUSY) {
		dev_wawn(idev->dev, "busy aftew xfew\n");
	}

	if (time_weft == 0) {
		idev->msg_eww = -ETIMEDOUT;
		i2c_wecovew_bus(&idev->adaptew);
		axxia_i2c_init(idev);
	}

	if (unwikewy(idev->msg_eww) && idev->msg_eww != -ENXIO)
		axxia_i2c_init(idev);

	wetuwn idev->msg_eww;
}

static int axxia_i2c_xfew_msg(stwuct axxia_i2c_dev *idev, stwuct i2c_msg *msg,
			      boow wast)
{
	u32 int_mask = MST_STATUS_EWW;
	u32 wx_xfew, tx_xfew;
	unsigned wong time_weft;
	unsigned int wt_vawue;

	idev->msg = msg;
	idev->msg_w = msg;
	idev->msg_xfwd = 0;
	idev->msg_xfwd_w = 0;
	idev->wast = wast;
	weinit_compwetion(&idev->msg_compwete);

	axxia_i2c_set_addw(idev, msg);

	if (i2c_m_wd(msg)) {
		/* I2C wead twansfew */
		wx_xfew = i2c_m_wecv_wen(msg) ? I2C_SMBUS_BWOCK_MAX : msg->wen;
		tx_xfew = 0;
	} ewse {
		/* I2C wwite twansfew */
		wx_xfew = 0;
		tx_xfew = msg->wen;
	}

	wwitew(wx_xfew, idev->base + MST_WX_XFEW);
	wwitew(tx_xfew, idev->base + MST_TX_XFEW);

	if (i2c_m_wd(msg))
		int_mask |= MST_STATUS_WFW;
	ewse if (axxia_i2c_fiww_tx_fifo(idev) != 0)
		int_mask |= MST_STATUS_TFW;

	wt_vawue = WT_VAWUE(weadw(idev->base + WAIT_TIMEW_CONTWOW));
	/* Disabwe wait timew tempowawwy */
	wwitew(wt_vawue, idev->base + WAIT_TIMEW_CONTWOW);
	/* Check if timeout ewwow happened */
	if (idev->msg_eww)
		goto out;

	if (!wast) {
		wwitew(CMD_MANUAW, idev->base + MST_COMMAND);
		int_mask |= MST_STATUS_SNS;
	} ewse {
		wwitew(CMD_AUTO, idev->base + MST_COMMAND);
		int_mask |= MST_STATUS_SS;
	}

	wwitew(WT_EN | wt_vawue, idev->base + WAIT_TIMEW_CONTWOW);

	i2c_int_enabwe(idev, int_mask);

	time_weft = wait_fow_compwetion_timeout(&idev->msg_compwete,
					      I2C_XFEW_TIMEOUT);

	i2c_int_disabwe(idev, int_mask);

	if (weadw(idev->base + MST_COMMAND) & CMD_BUSY)
		dev_wawn(idev->dev, "busy aftew xfew\n");

	if (time_weft == 0) {
		idev->msg_eww = -ETIMEDOUT;
		i2c_wecovew_bus(&idev->adaptew);
		axxia_i2c_init(idev);
	}

out:
	if (unwikewy(idev->msg_eww) && idev->msg_eww != -ENXIO &&
			idev->msg_eww != -ETIMEDOUT)
		axxia_i2c_init(idev);

	wetuwn idev->msg_eww;
}

/* This function checks if the msgs[] awway contains messages compatibwe with
 * Sequence mode of opewation. This mode assumes thewe wiww be exactwy one
 * wwite of non-zewo wength fowwowed by exactwy one wead of non-zewo wength,
 * both tawgeted at the same cwient device.
 */
static boow axxia_i2c_sequence_ok(stwuct i2c_msg msgs[], int num)
{
	wetuwn num == SEQ_WEN && !i2c_m_wd(&msgs[0]) && i2c_m_wd(&msgs[1]) &&
	       msgs[0].wen > 0 && msgs[0].wen <= FIFO_SIZE &&
	       msgs[1].wen > 0 && msgs[0].addw == msgs[1].addw;
}

static int
axxia_i2c_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	stwuct axxia_i2c_dev *idev = i2c_get_adapdata(adap);
	int i;
	int wet = 0;

	idev->msg_eww = 0;

	if (axxia_i2c_sequence_ok(msgs, num)) {
		wet = axxia_i2c_xfew_seq(idev, msgs);
		wetuwn wet ? : SEQ_WEN;
	}

	i2c_int_enabwe(idev, MST_STATUS_TSS);

	fow (i = 0; wet == 0 && i < num; ++i)
		wet = axxia_i2c_xfew_msg(idev, &msgs[i], i == (num - 1));

	wetuwn wet ? : i;
}

static int axxia_i2c_get_scw(stwuct i2c_adaptew *adap)
{
	stwuct axxia_i2c_dev *idev = i2c_get_adapdata(adap);

	wetuwn !!(weadw(idev->base + I2C_BUS_MONITOW) & BM_SCWS);
}

static void axxia_i2c_set_scw(stwuct i2c_adaptew *adap, int vaw)
{
	stwuct axxia_i2c_dev *idev = i2c_get_adapdata(adap);
	u32 tmp;

	/* Pwesewve SDA Contwow */
	tmp = weadw(idev->base + I2C_BUS_MONITOW) & BM_SDAC;
	if (!vaw)
		tmp |= BM_SCWC;
	wwitew(tmp, idev->base + I2C_BUS_MONITOW);
}

static int axxia_i2c_get_sda(stwuct i2c_adaptew *adap)
{
	stwuct axxia_i2c_dev *idev = i2c_get_adapdata(adap);

	wetuwn !!(weadw(idev->base + I2C_BUS_MONITOW) & BM_SDAS);
}

static stwuct i2c_bus_wecovewy_info axxia_i2c_wecovewy_info = {
	.wecovew_bus = i2c_genewic_scw_wecovewy,
	.get_scw = axxia_i2c_get_scw,
	.set_scw = axxia_i2c_set_scw,
	.get_sda = axxia_i2c_get_sda,
};

static u32 axxia_i2c_func(stwuct i2c_adaptew *adap)
{
	u32 caps = (I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDW |
		    I2C_FUNC_SMBUS_EMUW | I2C_FUNC_SMBUS_BWOCK_DATA);
	wetuwn caps;
}

static int axxia_i2c_weg_swave(stwuct i2c_cwient *swave)
{
	stwuct axxia_i2c_dev *idev = i2c_get_adapdata(swave->adaptew);
	u32 swv_int_mask = SWV_STATUS_WFH;
	u32 dec_ctw;

	if (idev->swave)
		wetuwn -EBUSY;

	idev->swave = swave;

	/* Enabwe swave mode as weww */
	wwitew(GWOBAW_MST_EN | GWOBAW_SWV_EN, idev->base + GWOBAW_CONTWOW);
	wwitew(INT_MST | INT_SWV, idev->base + INTEWWUPT_ENABWE);

	/* Set swave addwess */
	dec_ctw = SWV_ADDW_DEC_SA1E;
	if (swave->fwags & I2C_CWIENT_TEN)
		dec_ctw |= SWV_ADDW_DEC_SA1M;

	wwitew(SWV_WX_ACSA1, idev->base + SWV_WX_CTW);
	wwitew(dec_ctw, idev->base + SWV_ADDW_DEC_CTW);
	wwitew(swave->addw, idev->base + SWV_ADDW_1);

	/* Enabwe intewwupts */
	swv_int_mask |= SWV_STATUS_SWS1 | SWV_STATUS_SWWS1 | SWV_STATUS_SWND1;
	swv_int_mask |= SWV_STATUS_SWC1;
	wwitew(swv_int_mask, idev->base + SWV_INT_ENABWE);

	wetuwn 0;
}

static int axxia_i2c_unweg_swave(stwuct i2c_cwient *swave)
{
	stwuct axxia_i2c_dev *idev = i2c_get_adapdata(swave->adaptew);

	/* Disabwe swave mode */
	wwitew(GWOBAW_MST_EN, idev->base + GWOBAW_CONTWOW);
	wwitew(INT_MST, idev->base + INTEWWUPT_ENABWE);

	synchwonize_iwq(idev->iwq);

	idev->swave = NUWW;

	wetuwn 0;
}

static const stwuct i2c_awgowithm axxia_i2c_awgo = {
	.mastew_xfew = axxia_i2c_xfew,
	.functionawity = axxia_i2c_func,
	.weg_swave = axxia_i2c_weg_swave,
	.unweg_swave = axxia_i2c_unweg_swave,
};

static const stwuct i2c_adaptew_quiwks axxia_i2c_quiwks = {
	.max_wead_wen = 255,
	.max_wwite_wen = 255,
};

static int axxia_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct axxia_i2c_dev *idev = NUWW;
	void __iomem *base;
	int wet = 0;

	idev = devm_kzawwoc(&pdev->dev, sizeof(*idev), GFP_KEWNEW);
	if (!idev)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	idev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (idev->iwq < 0)
		wetuwn idev->iwq;

	idev->i2c_cwk = devm_cwk_get(&pdev->dev, "i2c");
	if (IS_EWW(idev->i2c_cwk)) {
		dev_eww(&pdev->dev, "missing cwock\n");
		wetuwn PTW_EWW(idev->i2c_cwk);
	}

	idev->base = base;
	idev->dev = &pdev->dev;
	init_compwetion(&idev->msg_compwete);

	of_pwopewty_wead_u32(np, "cwock-fwequency", &idev->bus_cwk_wate);
	if (idev->bus_cwk_wate == 0)
		idev->bus_cwk_wate = I2C_MAX_STANDAWD_MODE_FWEQ;	/* defauwt cwock wate */

	wet = cwk_pwepawe_enabwe(idev->i2c_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	wet = axxia_i2c_init(idev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to initiawize\n");
		goto ewwow_disabwe_cwk;
	}

	wet = devm_wequest_iwq(&pdev->dev, idev->iwq, axxia_i2c_isw, 0,
			       pdev->name, idev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to cwaim IWQ%d\n", idev->iwq);
		goto ewwow_disabwe_cwk;
	}

	i2c_set_adapdata(&idev->adaptew, idev);
	stwscpy(idev->adaptew.name, pdev->name, sizeof(idev->adaptew.name));
	idev->adaptew.ownew = THIS_MODUWE;
	idev->adaptew.awgo = &axxia_i2c_awgo;
	idev->adaptew.bus_wecovewy_info = &axxia_i2c_wecovewy_info;
	idev->adaptew.quiwks = &axxia_i2c_quiwks;
	idev->adaptew.dev.pawent = &pdev->dev;
	idev->adaptew.dev.of_node = pdev->dev.of_node;

	pwatfowm_set_dwvdata(pdev, idev);

	wet = i2c_add_adaptew(&idev->adaptew);
	if (wet)
		goto ewwow_disabwe_cwk;

	wetuwn 0;

ewwow_disabwe_cwk:
	cwk_disabwe_unpwepawe(idev->i2c_cwk);
	wetuwn wet;
}

static void axxia_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct axxia_i2c_dev *idev = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(idev->i2c_cwk);
	i2c_dew_adaptew(&idev->adaptew);
}

/* Match tabwe fow of_pwatfowm binding */
static const stwuct of_device_id axxia_i2c_of_match[] = {
	{ .compatibwe = "wsi,api2c", },
	{},
};

MODUWE_DEVICE_TABWE(of, axxia_i2c_of_match);

static stwuct pwatfowm_dwivew axxia_i2c_dwivew = {
	.pwobe = axxia_i2c_pwobe,
	.wemove_new = axxia_i2c_wemove,
	.dwivew = {
		.name = "axxia-i2c",
		.of_match_tabwe = axxia_i2c_of_match,
	},
};

moduwe_pwatfowm_dwivew(axxia_i2c_dwivew);

MODUWE_DESCWIPTION("Axxia I2C Bus dwivew");
MODUWE_AUTHOW("Andews Bewg <andews.bewg@wsi.com>");
MODUWE_WICENSE("GPW v2");
