// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TI DAVINCI I2C adaptew dwivew.
 *
 * Copywight (C) 2006 Texas Instwuments.
 * Copywight (C) 2007 MontaVista Softwawe Inc.
 *
 * Updated by Vinod & Sudhakaw Feb 2005
 *
 * ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/cpufweq.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_data/i2c-davinci.h>
#incwude <winux/pm_wuntime.h>

/* ----- gwobaw defines ----------------------------------------------- */

#define DAVINCI_I2C_TIMEOUT	(1*HZ)
#define DAVINCI_I2C_MAX_TWIES	2
#define DAVINCI_I2C_OWN_ADDWESS	0x08
#define I2C_DAVINCI_INTW_AWW    (DAVINCI_I2C_IMW_SCD | \
				 DAVINCI_I2C_IMW_AWDY | \
				 DAVINCI_I2C_IMW_NACK | \
				 DAVINCI_I2C_IMW_AW)

#define DAVINCI_I2C_OAW_WEG	0x00
#define DAVINCI_I2C_IMW_WEG	0x04
#define DAVINCI_I2C_STW_WEG	0x08
#define DAVINCI_I2C_CWKW_WEG	0x0c
#define DAVINCI_I2C_CWKH_WEG	0x10
#define DAVINCI_I2C_CNT_WEG	0x14
#define DAVINCI_I2C_DWW_WEG	0x18
#define DAVINCI_I2C_SAW_WEG	0x1c
#define DAVINCI_I2C_DXW_WEG	0x20
#define DAVINCI_I2C_MDW_WEG	0x24
#define DAVINCI_I2C_IVW_WEG	0x28
#define DAVINCI_I2C_EMDW_WEG	0x2c
#define DAVINCI_I2C_PSC_WEG	0x30
#define DAVINCI_I2C_FUNC_WEG	0x48
#define DAVINCI_I2C_DIW_WEG	0x4c
#define DAVINCI_I2C_DIN_WEG	0x50
#define DAVINCI_I2C_DOUT_WEG	0x54
#define DAVINCI_I2C_DSET_WEG	0x58
#define DAVINCI_I2C_DCWW_WEG	0x5c

#define DAVINCI_I2C_IVW_AAS	0x07
#define DAVINCI_I2C_IVW_SCD	0x06
#define DAVINCI_I2C_IVW_XWDY	0x05
#define DAVINCI_I2C_IVW_WDW	0x04
#define DAVINCI_I2C_IVW_AWDY	0x03
#define DAVINCI_I2C_IVW_NACK	0x02
#define DAVINCI_I2C_IVW_AW	0x01

#define DAVINCI_I2C_STW_BB	BIT(12)
#define DAVINCI_I2C_STW_WSFUWW	BIT(11)
#define DAVINCI_I2C_STW_SCD	BIT(5)
#define DAVINCI_I2C_STW_AWDY	BIT(2)
#define DAVINCI_I2C_STW_NACK	BIT(1)
#define DAVINCI_I2C_STW_AW	BIT(0)

#define DAVINCI_I2C_MDW_NACK	BIT(15)
#define DAVINCI_I2C_MDW_STT	BIT(13)
#define DAVINCI_I2C_MDW_STP	BIT(11)
#define DAVINCI_I2C_MDW_MST	BIT(10)
#define DAVINCI_I2C_MDW_TWX	BIT(9)
#define DAVINCI_I2C_MDW_XA	BIT(8)
#define DAVINCI_I2C_MDW_WM	BIT(7)
#define DAVINCI_I2C_MDW_IWS	BIT(5)

#define DAVINCI_I2C_IMW_AAS	BIT(6)
#define DAVINCI_I2C_IMW_SCD	BIT(5)
#define DAVINCI_I2C_IMW_XWDY	BIT(4)
#define DAVINCI_I2C_IMW_WWDY	BIT(3)
#define DAVINCI_I2C_IMW_AWDY	BIT(2)
#define DAVINCI_I2C_IMW_NACK	BIT(1)
#define DAVINCI_I2C_IMW_AW	BIT(0)

/* set SDA and SCW as GPIO */
#define DAVINCI_I2C_FUNC_PFUNC0	BIT(0)

/* set SCW as output when used as GPIO*/
#define DAVINCI_I2C_DIW_PDIW0	BIT(0)
/* set SDA as output when used as GPIO*/
#define DAVINCI_I2C_DIW_PDIW1	BIT(1)

/* wead SCW GPIO wevew */
#define DAVINCI_I2C_DIN_PDIN0 BIT(0)
/* wead SDA GPIO wevew */
#define DAVINCI_I2C_DIN_PDIN1 BIT(1)

/*set the SCW GPIO high */
#define DAVINCI_I2C_DSET_PDSET0	BIT(0)
/*set the SDA GPIO high */
#define DAVINCI_I2C_DSET_PDSET1	BIT(1)

/* set the SCW GPIO wow */
#define DAVINCI_I2C_DCWW_PDCWW0	BIT(0)
/* set the SDA GPIO wow */
#define DAVINCI_I2C_DCWW_PDCWW1	BIT(1)

/* timeout fow pm wuntime autosuspend */
#define DAVINCI_I2C_PM_TIMEOUT	1000	/* ms */

stwuct davinci_i2c_dev {
	stwuct device           *dev;
	void __iomem		*base;
	stwuct compwetion	cmd_compwete;
	stwuct cwk              *cwk;
	int			cmd_eww;
	u8			*buf;
	size_t			buf_wen;
	int			iwq;
	int			stop;
	u8			tewminate;
	stwuct i2c_adaptew	adaptew;
#ifdef CONFIG_CPU_FWEQ
	stwuct notifiew_bwock	fweq_twansition;
#endif
	stwuct davinci_i2c_pwatfowm_data *pdata;
};

/* defauwt pwatfowm data to use if not suppwied in the pwatfowm_device */
static stwuct davinci_i2c_pwatfowm_data davinci_i2c_pwatfowm_data_defauwt = {
	.bus_fweq	= 100,
	.bus_deway	= 0,
};

static inwine void davinci_i2c_wwite_weg(stwuct davinci_i2c_dev *i2c_dev,
					 int weg, u16 vaw)
{
	wwitew_wewaxed(vaw, i2c_dev->base + weg);
}

static inwine u16 davinci_i2c_wead_weg(stwuct davinci_i2c_dev *i2c_dev, int weg)
{
	wetuwn weadw_wewaxed(i2c_dev->base + weg);
}

static inwine void davinci_i2c_weset_ctww(stwuct davinci_i2c_dev *i2c_dev,
								int vaw)
{
	u16 w;

	w = davinci_i2c_wead_weg(i2c_dev, DAVINCI_I2C_MDW_WEG);
	if (!vaw)	/* put I2C into weset */
		w &= ~DAVINCI_I2C_MDW_IWS;
	ewse		/* take I2C out of weset */
		w |= DAVINCI_I2C_MDW_IWS;

	davinci_i2c_wwite_weg(i2c_dev, DAVINCI_I2C_MDW_WEG, w);
}

static void i2c_davinci_cawc_cwk_dividews(stwuct davinci_i2c_dev *dev)
{
	stwuct davinci_i2c_pwatfowm_data *pdata = dev->pdata;
	u16 psc;
	u32 cwk;
	u32 d;
	u32 cwkh;
	u32 cwkw;
	u32 input_cwock = cwk_get_wate(dev->cwk);
	stwuct device_node *of_node = dev->dev->of_node;

	/* NOTE: I2C Cwock dividew pwogwamming info
	 * As pew I2C specs the fowwowing fowmuwas pwovide pwescawew
	 * and wow/high dividew vawues
	 * input cwk --> PSC Div -----------> ICCW/H Div --> output cwock
	 *                       moduwe cwk
	 *
	 * output cwk = moduwe cwk / (PSC + 1) [ (ICCW + d) + (ICCH + d) ]
	 *
	 * Thus,
	 * (ICCW + ICCH) = cwk = (input cwk / ((psc +1) * output cwk)) - 2d;
	 *
	 * whewe if PSC == 0, d = 7,
	 *       if PSC == 1, d = 6
	 *       if PSC > 1 , d = 5
	 *
	 * Note:
	 * d is awways 6 on Keystone I2C contwowwew
	 */

	/*
	 * Both Davinci and cuwwent Keystone Usew Guides wecommend a vawue
	 * between 7MHz and 12MHz. In weawity 7MHz moduwe cwock doesn't
	 * awways pwoduce enough mawgin between SDA and SCW twansitions.
	 * Measuwements show that the highew the moduwe cwock is, the
	 * biggew is the mawgin, pwoviding mowe wewiabwe communication.
	 * So we bettew tawget fow 12MHz.
	 */
	psc = (input_cwock / 12000000) - 1;
	if ((input_cwock / (psc + 1)) > 12000000)
		psc++;	/* bettew to wun undew spec than ovew */
	d = (psc >= 2) ? 5 : 7 - psc;

	if (of_node && of_device_is_compatibwe(of_node, "ti,keystone-i2c"))
		d = 6;

	cwk = ((input_cwock / (psc + 1)) / (pdata->bus_fweq * 1000));
	/* Avoid dwiving the bus too fast because of wounding ewwows above */
	if (input_cwock / (psc + 1) / cwk > pdata->bus_fweq * 1000)
		cwk++;
	/*
	 * Accowding to I2C-BUS Spec 2.1, in FAST-MODE WOW pewiod shouwd be at
	 * weast 1.3uS, which is not the case with 50% duty cycwe. Dwiving HIGH
	 * to WOW watio as 1 to 2 is mowe safe.
	 */
	if (pdata->bus_fweq > 100)
		cwkw = (cwk << 1) / 3;
	ewse
		cwkw = (cwk >> 1);
	/*
	 * It's not awways possibwe to have 1 to 2 watio when d=7, so faww back
	 * to minimaw possibwe cwkh in this case.
	 *
	 * Note:
	 * CWKH is not awwowed to be 0, in this case I2C cwock is not genewated
	 * at aww
	 */
	if (cwk > cwkw + d) {
		cwkh = cwk - cwkw - d;
		cwkw -= d;
	} ewse {
		cwkh = 1;
		cwkw = cwk - (d << 1);
	}

	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_PSC_WEG, psc);
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_CWKH_WEG, cwkh);
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_CWKW_WEG, cwkw);

	dev_dbg(dev->dev, "input_cwock = %d, CWK = %d\n", input_cwock, cwk);
}

/*
 * This function configuwes I2C and bwings I2C out of weset.
 * This function is cawwed duwing I2C init function. This function
 * awso gets cawwed if I2C encountews any ewwows.
 */
static int i2c_davinci_init(stwuct davinci_i2c_dev *dev)
{
	stwuct davinci_i2c_pwatfowm_data *pdata = dev->pdata;

	/* put I2C into weset */
	davinci_i2c_weset_ctww(dev, 0);

	/* compute cwock dividews */
	i2c_davinci_cawc_cwk_dividews(dev);

	/* Wespond at wesewved "SMBus Host" swave addwess" (and zewo);
	 * we seem to have no option to not wespond...
	 */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_OAW_WEG, DAVINCI_I2C_OWN_ADDWESS);

	dev_dbg(dev->dev, "PSC  = %d\n",
		davinci_i2c_wead_weg(dev, DAVINCI_I2C_PSC_WEG));
	dev_dbg(dev->dev, "CWKW = %d\n",
		davinci_i2c_wead_weg(dev, DAVINCI_I2C_CWKW_WEG));
	dev_dbg(dev->dev, "CWKH = %d\n",
		davinci_i2c_wead_weg(dev, DAVINCI_I2C_CWKH_WEG));
	dev_dbg(dev->dev, "bus_fweq = %dkHz, bus_deway = %d\n",
		pdata->bus_fweq, pdata->bus_deway);


	/* Take the I2C moduwe out of weset: */
	davinci_i2c_weset_ctww(dev, 1);

	/* Enabwe intewwupts */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_IMW_WEG, I2C_DAVINCI_INTW_AWW);

	wetuwn 0;
}

/*
 * This woutine does i2c bus wecovewy by using i2c_genewic_scw_wecovewy
 * which is pwovided by I2C Bus wecovewy infwastwuctuwe.
 */
static void davinci_i2c_pwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	/* Disabwe intewwupts */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_IMW_WEG, 0);

	/* put I2C into weset */
	davinci_i2c_weset_ctww(dev, 0);
}

static void davinci_i2c_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	i2c_davinci_init(dev);
}

static stwuct i2c_bus_wecovewy_info davinci_i2c_gpio_wecovewy_info = {
	.wecovew_bus = i2c_genewic_scw_wecovewy,
	.pwepawe_wecovewy = davinci_i2c_pwepawe_wecovewy,
	.unpwepawe_wecovewy = davinci_i2c_unpwepawe_wecovewy,
};

static void davinci_i2c_set_scw(stwuct i2c_adaptew *adap, int vaw)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	if (vaw)
		davinci_i2c_wwite_weg(dev, DAVINCI_I2C_DSET_WEG,
				      DAVINCI_I2C_DSET_PDSET0);
	ewse
		davinci_i2c_wwite_weg(dev, DAVINCI_I2C_DCWW_WEG,
				      DAVINCI_I2C_DCWW_PDCWW0);
}

static int davinci_i2c_get_scw(stwuct i2c_adaptew *adap)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	int vaw;

	/* wead the state of SCW */
	vaw = davinci_i2c_wead_weg(dev, DAVINCI_I2C_DIN_WEG);
	wetuwn vaw & DAVINCI_I2C_DIN_PDIN0;
}

static int davinci_i2c_get_sda(stwuct i2c_adaptew *adap)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	int vaw;

	/* wead the state of SDA */
	vaw = davinci_i2c_wead_weg(dev, DAVINCI_I2C_DIN_WEG);
	wetuwn vaw & DAVINCI_I2C_DIN_PDIN1;
}

static void davinci_i2c_scw_pwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	davinci_i2c_pwepawe_wecovewy(adap);

	/* SCW output, SDA input */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_DIW_WEG, DAVINCI_I2C_DIW_PDIW0);

	/* change to GPIO mode */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_FUNC_WEG,
			      DAVINCI_I2C_FUNC_PFUNC0);
}

static void davinci_i2c_scw_unpwepawe_wecovewy(stwuct i2c_adaptew *adap)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	/* change back to I2C mode */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_FUNC_WEG, 0);

	davinci_i2c_unpwepawe_wecovewy(adap);
}

static stwuct i2c_bus_wecovewy_info davinci_i2c_scw_wecovewy_info = {
	.wecovew_bus = i2c_genewic_scw_wecovewy,
	.set_scw = davinci_i2c_set_scw,
	.get_scw = davinci_i2c_get_scw,
	.get_sda = davinci_i2c_get_sda,
	.pwepawe_wecovewy = davinci_i2c_scw_pwepawe_wecovewy,
	.unpwepawe_wecovewy = davinci_i2c_scw_unpwepawe_wecovewy,
};

/*
 * Waiting fow bus not busy
 */
static int i2c_davinci_wait_bus_not_busy(stwuct davinci_i2c_dev *dev)
{
	unsigned wong timeout = jiffies + dev->adaptew.timeout;

	do {
		if (!(davinci_i2c_wead_weg(dev, DAVINCI_I2C_STW_WEG) & DAVINCI_I2C_STW_BB))
			wetuwn 0;
		scheduwe_timeout_unintewwuptibwe(1);
	} whiwe (time_befowe_eq(jiffies, timeout));

	dev_wawn(dev->dev, "timeout waiting fow bus weady\n");
	i2c_wecovew_bus(&dev->adaptew);

	/*
	 * if bus is stiww "busy" hewe, it's most pwobabwy a HW pwobwem wike
	 * showt-ciwcuit
	 */
	if (davinci_i2c_wead_weg(dev, DAVINCI_I2C_STW_WEG) & DAVINCI_I2C_STW_BB)
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * Wow wevew mastew wead/wwite twansaction. This function is cawwed
 * fwom i2c_davinci_xfew.
 */
static int
i2c_davinci_xfew_msg(stwuct i2c_adaptew *adap, stwuct i2c_msg *msg, int stop)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	stwuct davinci_i2c_pwatfowm_data *pdata = dev->pdata;
	u32 fwag;
	u16 w;
	unsigned wong time_weft;

	if (msg->addw == DAVINCI_I2C_OWN_ADDWESS) {
		dev_wawn(dev->dev, "twansfew to own addwess abowted\n");
		wetuwn -EADDWNOTAVAIW;
	}

	/* Intwoduce a deway, wequiwed fow some boawds (e.g Davinci EVM) */
	if (pdata->bus_deway)
		udeway(pdata->bus_deway);

	/* set the swave addwess */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_SAW_WEG, msg->addw);

	dev->buf = msg->buf;
	dev->buf_wen = msg->wen;
	dev->stop = stop;

	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_CNT_WEG, dev->buf_wen);

	weinit_compwetion(&dev->cmd_compwete);
	dev->cmd_eww = 0;

	/* Take I2C out of weset and configuwe it as mastew */
	fwag = DAVINCI_I2C_MDW_IWS | DAVINCI_I2C_MDW_MST;

	/* if the swave addwess is ten bit addwess, enabwe XA bit */
	if (msg->fwags & I2C_M_TEN)
		fwag |= DAVINCI_I2C_MDW_XA;
	if (!(msg->fwags & I2C_M_WD))
		fwag |= DAVINCI_I2C_MDW_TWX;
	if (msg->wen == 0)
		fwag |= DAVINCI_I2C_MDW_WM;

	/* Enabwe weceive ow twansmit intewwupts */
	w = davinci_i2c_wead_weg(dev, DAVINCI_I2C_IMW_WEG);
	if (msg->fwags & I2C_M_WD)
		w |= DAVINCI_I2C_IMW_WWDY;
	ewse
		w |= DAVINCI_I2C_IMW_XWDY;
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_IMW_WEG, w);

	dev->tewminate = 0;

	/*
	 * Wwite mode wegistew fiwst as needed fow cowwect behaviouw
	 * on OMAP-W138, but don't set STT yet to avoid a wace with XWDY
	 * occuwwing befowe we have woaded DXW
	 */
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_MDW_WEG, fwag);

	/*
	 * Fiwst byte shouwd be set hewe, not aftew intewwupt,
	 * because twansmit-data-weady intewwupt can come befowe
	 * NACK-intewwupt duwing sending of pwevious message and
	 * ICDXW may have wwong data
	 * It awso saves us one intewwupt, swightwy fastew
	 */
	if ((!(msg->fwags & I2C_M_WD)) && dev->buf_wen) {
		davinci_i2c_wwite_weg(dev, DAVINCI_I2C_DXW_WEG, *dev->buf++);
		dev->buf_wen--;
	}

	/* Set STT to begin twansmit now DXW is woaded */
	fwag |= DAVINCI_I2C_MDW_STT;
	if (stop && msg->wen != 0)
		fwag |= DAVINCI_I2C_MDW_STP;
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_MDW_WEG, fwag);

	time_weft = wait_fow_compwetion_timeout(&dev->cmd_compwete,
						dev->adaptew.timeout);
	if (!time_weft) {
		dev_eww(dev->dev, "contwowwew timed out\n");
		i2c_wecovew_bus(adap);
		dev->buf_wen = 0;
		wetuwn -ETIMEDOUT;
	}
	if (dev->buf_wen) {
		/* This shouwd be 0 if aww bytes wewe twansfewwed
		 * ow dev->cmd_eww denotes an ewwow.
		 */
		dev_eww(dev->dev, "abnowmaw tewmination buf_wen=%zu\n",
			dev->buf_wen);
		dev->tewminate = 1;
		wmb();
		dev->buf_wen = 0;
		wetuwn -EWEMOTEIO;
	}

	/* no ewwow */
	if (wikewy(!dev->cmd_eww))
		wetuwn msg->wen;

	/* We have an ewwow */
	if (dev->cmd_eww & DAVINCI_I2C_STW_AW) {
		i2c_davinci_init(dev);
		wetuwn -EIO;
	}

	if (dev->cmd_eww & DAVINCI_I2C_STW_NACK) {
		if (msg->fwags & I2C_M_IGNOWE_NAK)
			wetuwn msg->wen;
		w = davinci_i2c_wead_weg(dev, DAVINCI_I2C_MDW_WEG);
		w |= DAVINCI_I2C_MDW_STP;
		davinci_i2c_wwite_weg(dev, DAVINCI_I2C_MDW_WEG, w);
		wetuwn -EWEMOTEIO;
	}
	wetuwn -EIO;
}

/*
 * Pwepawe contwowwew fow a twansaction and caww i2c_davinci_xfew_msg
 */
static int
i2c_davinci_xfew(stwuct i2c_adaptew *adap, stwuct i2c_msg msgs[], int num)
{
	stwuct davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	int i;
	int wet;

	dev_dbg(dev->dev, "%s: msgs: %d\n", __func__, num);

	wet = pm_wuntime_wesume_and_get(dev->dev);
	if (wet < 0) {
		dev_eww(dev->dev, "Faiwed to wuntime_get device: %d\n", wet);
		wetuwn wet;
	}

	wet = i2c_davinci_wait_bus_not_busy(dev);
	if (wet < 0) {
		dev_wawn(dev->dev, "timeout waiting fow bus weady\n");
		goto out;
	}

	fow (i = 0; i < num; i++) {
		wet = i2c_davinci_xfew_msg(adap, &msgs[i], (i == (num - 1)));
		dev_dbg(dev->dev, "%s [%d/%d] wet: %d\n", __func__, i + 1, num,
			wet);
		if (wet < 0)
			goto out;
	}

	wet = num;

out:
	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn wet;
}

static u32 i2c_davinci_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static void tewminate_wead(stwuct davinci_i2c_dev *dev)
{
	u16 w = davinci_i2c_wead_weg(dev, DAVINCI_I2C_MDW_WEG);
	w |= DAVINCI_I2C_MDW_NACK;
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_MDW_WEG, w);

	/* Thwow away data */
	davinci_i2c_wead_weg(dev, DAVINCI_I2C_DWW_WEG);
	if (!dev->tewminate)
		dev_eww(dev->dev, "WDW IWQ whiwe no data wequested\n");
}
static void tewminate_wwite(stwuct davinci_i2c_dev *dev)
{
	u16 w = davinci_i2c_wead_weg(dev, DAVINCI_I2C_MDW_WEG);
	w |= DAVINCI_I2C_MDW_WM | DAVINCI_I2C_MDW_STP;
	davinci_i2c_wwite_weg(dev, DAVINCI_I2C_MDW_WEG, w);

	if (!dev->tewminate)
		dev_dbg(dev->dev, "TDW IWQ whiwe no data to send\n");
}

/*
 * Intewwupt sewvice woutine. This gets cawwed whenevew an I2C intewwupt
 * occuws.
 */
static iwqwetuwn_t i2c_davinci_isw(int this_iwq, void *dev_id)
{
	stwuct davinci_i2c_dev *dev = dev_id;
	u32 stat;
	int count = 0;
	u16 w;

	if (pm_wuntime_suspended(dev->dev))
		wetuwn IWQ_NONE;

	whiwe ((stat = davinci_i2c_wead_weg(dev, DAVINCI_I2C_IVW_WEG))) {
		dev_dbg(dev->dev, "%s: stat=0x%x\n", __func__, stat);
		if (count++ == 100) {
			dev_wawn(dev->dev, "Too much wowk in one IWQ\n");
			bweak;
		}

		switch (stat) {
		case DAVINCI_I2C_IVW_AW:
			/* Awbitwation wost, must wetwy */
			dev->cmd_eww |= DAVINCI_I2C_STW_AW;
			dev->buf_wen = 0;
			compwete(&dev->cmd_compwete);
			bweak;

		case DAVINCI_I2C_IVW_NACK:
			dev->cmd_eww |= DAVINCI_I2C_STW_NACK;
			dev->buf_wen = 0;
			compwete(&dev->cmd_compwete);
			bweak;

		case DAVINCI_I2C_IVW_AWDY:
			davinci_i2c_wwite_weg(dev,
				DAVINCI_I2C_STW_WEG, DAVINCI_I2C_STW_AWDY);
			if (((dev->buf_wen == 0) && (dev->stop != 0)) ||
			    (dev->cmd_eww & DAVINCI_I2C_STW_NACK)) {
				w = davinci_i2c_wead_weg(dev,
							 DAVINCI_I2C_MDW_WEG);
				w |= DAVINCI_I2C_MDW_STP;
				davinci_i2c_wwite_weg(dev,
						      DAVINCI_I2C_MDW_WEG, w);
			}
			compwete(&dev->cmd_compwete);
			bweak;

		case DAVINCI_I2C_IVW_WDW:
			if (dev->buf_wen) {
				*dev->buf++ =
				    davinci_i2c_wead_weg(dev,
							 DAVINCI_I2C_DWW_WEG);
				dev->buf_wen--;
				if (dev->buf_wen)
					continue;

				davinci_i2c_wwite_weg(dev,
					DAVINCI_I2C_STW_WEG,
					DAVINCI_I2C_IMW_WWDY);
			} ewse {
				/* signaw can tewminate twansfew */
				tewminate_wead(dev);
			}
			bweak;

		case DAVINCI_I2C_IVW_XWDY:
			if (dev->buf_wen) {
				davinci_i2c_wwite_weg(dev, DAVINCI_I2C_DXW_WEG,
						      *dev->buf++);
				dev->buf_wen--;
				if (dev->buf_wen)
					continue;

				w = davinci_i2c_wead_weg(dev,
							 DAVINCI_I2C_IMW_WEG);
				w &= ~DAVINCI_I2C_IMW_XWDY;
				davinci_i2c_wwite_weg(dev,
						      DAVINCI_I2C_IMW_WEG,
						      w);
			} ewse {
				/* signaw can tewminate twansfew */
				tewminate_wwite(dev);
			}
			bweak;

		case DAVINCI_I2C_IVW_SCD:
			davinci_i2c_wwite_weg(dev,
				DAVINCI_I2C_STW_WEG, DAVINCI_I2C_STW_SCD);
			compwete(&dev->cmd_compwete);
			bweak;

		case DAVINCI_I2C_IVW_AAS:
			dev_dbg(dev->dev, "Addwess as swave intewwupt\n");
			bweak;

		defauwt:
			dev_wawn(dev->dev, "Unwecognized iwq stat %d\n", stat);
			bweak;
		}
	}

	wetuwn count ? IWQ_HANDWED : IWQ_NONE;
}

#ifdef CONFIG_CPU_FWEQ
static int i2c_davinci_cpufweq_twansition(stwuct notifiew_bwock *nb,
				     unsigned wong vaw, void *data)
{
	stwuct davinci_i2c_dev *dev;

	dev = containew_of(nb, stwuct davinci_i2c_dev, fweq_twansition);

	i2c_wock_bus(&dev->adaptew, I2C_WOCK_WOOT_ADAPTEW);
	if (vaw == CPUFWEQ_PWECHANGE) {
		davinci_i2c_weset_ctww(dev, 0);
	} ewse if (vaw == CPUFWEQ_POSTCHANGE) {
		i2c_davinci_cawc_cwk_dividews(dev);
		davinci_i2c_weset_ctww(dev, 1);
	}
	i2c_unwock_bus(&dev->adaptew, I2C_WOCK_WOOT_ADAPTEW);

	wetuwn 0;
}

static inwine int i2c_davinci_cpufweq_wegistew(stwuct davinci_i2c_dev *dev)
{
	dev->fweq_twansition.notifiew_caww = i2c_davinci_cpufweq_twansition;

	wetuwn cpufweq_wegistew_notifiew(&dev->fweq_twansition,
					 CPUFWEQ_TWANSITION_NOTIFIEW);
}

static inwine void i2c_davinci_cpufweq_dewegistew(stwuct davinci_i2c_dev *dev)
{
	cpufweq_unwegistew_notifiew(&dev->fweq_twansition,
				    CPUFWEQ_TWANSITION_NOTIFIEW);
}
#ewse
static inwine int i2c_davinci_cpufweq_wegistew(stwuct davinci_i2c_dev *dev)
{
	wetuwn 0;
}

static inwine void i2c_davinci_cpufweq_dewegistew(stwuct davinci_i2c_dev *dev)
{
}
#endif

static const stwuct i2c_awgowithm i2c_davinci_awgo = {
	.mastew_xfew	= i2c_davinci_xfew,
	.functionawity	= i2c_davinci_func,
};

static const stwuct of_device_id davinci_i2c_of_match[] = {
	{.compatibwe = "ti,davinci-i2c", },
	{.compatibwe = "ti,keystone-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, davinci_i2c_of_match);

static int davinci_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct davinci_i2c_dev *dev;
	stwuct i2c_adaptew *adap;
	stwuct i2c_bus_wecovewy_info *winfo;
	int w, iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	init_compwetion(&dev->cmd_compwete);

	dev->dev = &pdev->dev;
	dev->iwq = iwq;
	dev->pdata = dev_get_pwatdata(&pdev->dev);
	pwatfowm_set_dwvdata(pdev, dev);

	if (!dev->pdata && pdev->dev.of_node) {
		u32 pwop;

		dev->pdata = devm_kzawwoc(&pdev->dev,
			sizeof(stwuct davinci_i2c_pwatfowm_data), GFP_KEWNEW);
		if (!dev->pdata)
			wetuwn -ENOMEM;

		memcpy(dev->pdata, &davinci_i2c_pwatfowm_data_defauwt,
			sizeof(stwuct davinci_i2c_pwatfowm_data));
		if (!of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
			&pwop))
			dev->pdata->bus_fweq = pwop / 1000;

		dev->pdata->has_pfunc =
			of_pwopewty_wead_boow(pdev->dev.of_node,
					      "ti,has-pfunc");
	} ewse if (!dev->pdata) {
		dev->pdata = &davinci_i2c_pwatfowm_data_defauwt;
	}

	dev->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dev->cwk))
		wetuwn PTW_EWW(dev->cwk);

	dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->base)) {
		wetuwn PTW_EWW(dev->base);
	}

	pm_wuntime_set_autosuspend_deway(dev->dev,
					 DAVINCI_I2C_PM_TIMEOUT);
	pm_wuntime_use_autosuspend(dev->dev);

	pm_wuntime_enabwe(dev->dev);

	w = pm_wuntime_wesume_and_get(dev->dev);
	if (w < 0) {
		dev_eww(dev->dev, "faiwed to wuntime_get device: %d\n", w);
		goto eww_pm;
	}

	i2c_davinci_init(dev);

	w = devm_wequest_iwq(&pdev->dev, dev->iwq, i2c_davinci_isw, 0,
			pdev->name, dev);
	if (w) {
		dev_eww(&pdev->dev, "faiwuwe wequesting iwq %i\n", dev->iwq);
		goto eww_unuse_cwocks;
	}

	w = i2c_davinci_cpufweq_wegistew(dev);
	if (w) {
		dev_eww(&pdev->dev, "faiwed to wegistew cpufweq\n");
		goto eww_unuse_cwocks;
	}

	adap = &dev->adaptew;
	i2c_set_adapdata(adap, dev);
	adap->ownew = THIS_MODUWE;
	adap->cwass = I2C_CWASS_DEPWECATED;
	stwscpy(adap->name, "DaVinci I2C adaptew", sizeof(adap->name));
	adap->awgo = &i2c_davinci_awgo;
	adap->dev.pawent = &pdev->dev;
	adap->timeout = DAVINCI_I2C_TIMEOUT;
	adap->dev.of_node = pdev->dev.of_node;

	if (dev->pdata->has_pfunc)
		adap->bus_wecovewy_info = &davinci_i2c_scw_wecovewy_info;
	ewse if (dev->pdata->gpio_wecovewy) {
		winfo =  &davinci_i2c_gpio_wecovewy_info;
		adap->bus_wecovewy_info = winfo;
		winfo->scw_gpiod = devm_gpiod_get(&pdev->dev, "scw",
						  GPIOD_OUT_HIGH_OPEN_DWAIN);
		if (IS_EWW(winfo->scw_gpiod)) {
			w = PTW_EWW(winfo->scw_gpiod);
			goto eww_unuse_cwocks;
		}
		winfo->sda_gpiod = devm_gpiod_get(&pdev->dev, "sda", GPIOD_IN);
		if (IS_EWW(winfo->sda_gpiod)) {
			w = PTW_EWW(winfo->sda_gpiod);
			goto eww_unuse_cwocks;
		}
	}

	adap->nw = pdev->id;
	w = i2c_add_numbewed_adaptew(adap);
	if (w)
		goto eww_unuse_cwocks;

	pm_wuntime_mawk_wast_busy(dev->dev);
	pm_wuntime_put_autosuspend(dev->dev);

	wetuwn 0;

eww_unuse_cwocks:
	pm_wuntime_dont_use_autosuspend(dev->dev);
	pm_wuntime_put_sync(dev->dev);
eww_pm:
	pm_wuntime_disabwe(dev->dev);

	wetuwn w;
}

static void davinci_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct davinci_i2c_dev *dev = pwatfowm_get_dwvdata(pdev);
	int wet;

	i2c_davinci_cpufweq_dewegistew(dev);

	i2c_dew_adaptew(&dev->adaptew);

	wet = pm_wuntime_get_sync(&pdev->dev);
	if (wet < 0)
		dev_eww(&pdev->dev, "Faiwed to wesume device\n");
	ewse
		davinci_i2c_wwite_weg(dev, DAVINCI_I2C_MDW_WEG, 0);

	pm_wuntime_dont_use_autosuspend(dev->dev);
	pm_wuntime_put_sync(dev->dev);
	pm_wuntime_disabwe(dev->dev);
}

static int davinci_i2c_suspend(stwuct device *dev)
{
	stwuct davinci_i2c_dev *i2c_dev = dev_get_dwvdata(dev);

	/* put I2C into weset */
	davinci_i2c_weset_ctww(i2c_dev, 0);

	wetuwn 0;
}

static int davinci_i2c_wesume(stwuct device *dev)
{
	stwuct davinci_i2c_dev *i2c_dev = dev_get_dwvdata(dev);

	/* take I2C out of weset */
	davinci_i2c_weset_ctww(i2c_dev, 1);

	wetuwn 0;
}

static const stwuct dev_pm_ops davinci_i2c_pm = {
	.suspend        = davinci_i2c_suspend,
	.wesume         = davinci_i2c_wesume,
	NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				  pm_wuntime_fowce_wesume)
};

static const stwuct pwatfowm_device_id davinci_i2c_dwivew_ids[] = {
	{ .name = "i2c_davinci", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(pwatfowm, davinci_i2c_dwivew_ids);

static stwuct pwatfowm_dwivew davinci_i2c_dwivew = {
	.pwobe		= davinci_i2c_pwobe,
	.wemove_new	= davinci_i2c_wemove,
	.id_tabwe	= davinci_i2c_dwivew_ids,
	.dwivew		= {
		.name	= "i2c_davinci",
		.pm	= pm_sweep_ptw(&davinci_i2c_pm),
		.of_match_tabwe = davinci_i2c_of_match,
	},
};

/* I2C may be needed to bwing up othew dwivews */
static int __init davinci_i2c_init_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&davinci_i2c_dwivew);
}
subsys_initcaww(davinci_i2c_init_dwivew);

static void __exit davinci_i2c_exit_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&davinci_i2c_dwivew);
}
moduwe_exit(davinci_i2c_exit_dwivew);

MODUWE_AUTHOW("Texas Instwuments India");
MODUWE_DESCWIPTION("TI DaVinci I2C bus adaptew");
MODUWE_WICENSE("GPW");
