// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 STMicwoewectwonics
 *
 * I2C mastew mode contwowwew dwivew, used in STMicwoewectwonics devices.
 *
 * Authow: Maxime Coquewin <maxime.coquewin@st.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>

/* SSC wegistews */
#define SSC_BWG				0x000
#define SSC_TBUF			0x004
#define SSC_WBUF			0x008
#define SSC_CTW				0x00C
#define SSC_IEN				0x010
#define SSC_STA				0x014
#define SSC_I2C				0x018
#define SSC_SWAD			0x01C
#define SSC_WEP_STAWT_HOWD		0x020
#define SSC_STAWT_HOWD			0x024
#define SSC_WEP_STAWT_SETUP		0x028
#define SSC_DATA_SETUP			0x02C
#define SSC_STOP_SETUP			0x030
#define SSC_BUS_FWEE			0x034
#define SSC_TX_FSTAT			0x038
#define SSC_WX_FSTAT			0x03C
#define SSC_PWE_SCAWEW_BWG		0x040
#define SSC_CWW				0x080
#define SSC_NOISE_SUPP_WIDTH		0x100
#define SSC_PWSCAWEW			0x104
#define SSC_NOISE_SUPP_WIDTH_DATAOUT	0x108
#define SSC_PWSCAWEW_DATAOUT		0x10c

/* SSC Contwow */
#define SSC_CTW_DATA_WIDTH_9		0x8
#define SSC_CTW_DATA_WIDTH_MSK		0xf
#define SSC_CTW_BM			0xf
#define SSC_CTW_HB			BIT(4)
#define SSC_CTW_PH			BIT(5)
#define SSC_CTW_PO			BIT(6)
#define SSC_CTW_SW			BIT(7)
#define SSC_CTW_MS			BIT(8)
#define SSC_CTW_EN			BIT(9)
#define SSC_CTW_WPB			BIT(10)
#define SSC_CTW_EN_TX_FIFO		BIT(11)
#define SSC_CTW_EN_WX_FIFO		BIT(12)
#define SSC_CTW_EN_CWST_WX		BIT(13)

/* SSC Intewwupt Enabwe */
#define SSC_IEN_WIEN			BIT(0)
#define SSC_IEN_TIEN			BIT(1)
#define SSC_IEN_TEEN			BIT(2)
#define SSC_IEN_WEEN			BIT(3)
#define SSC_IEN_PEEN			BIT(4)
#define SSC_IEN_AASEN			BIT(6)
#define SSC_IEN_STOPEN			BIT(7)
#define SSC_IEN_AWBWEN			BIT(8)
#define SSC_IEN_NACKEN			BIT(10)
#define SSC_IEN_WEPSTWTEN		BIT(11)
#define SSC_IEN_TX_FIFO_HAWF		BIT(12)
#define SSC_IEN_WX_FIFO_HAWF_FUWW	BIT(14)

/* SSC Status */
#define SSC_STA_WIW			BIT(0)
#define SSC_STA_TIW			BIT(1)
#define SSC_STA_TE			BIT(2)
#define SSC_STA_WE			BIT(3)
#define SSC_STA_PE			BIT(4)
#define SSC_STA_CWST			BIT(5)
#define SSC_STA_AAS			BIT(6)
#define SSC_STA_STOP			BIT(7)
#define SSC_STA_AWBW			BIT(8)
#define SSC_STA_BUSY			BIT(9)
#define SSC_STA_NACK			BIT(10)
#define SSC_STA_WEPSTWT			BIT(11)
#define SSC_STA_TX_FIFO_HAWF		BIT(12)
#define SSC_STA_TX_FIFO_FUWW		BIT(13)
#define SSC_STA_WX_FIFO_HAWF		BIT(14)

/* SSC I2C Contwow */
#define SSC_I2C_I2CM			BIT(0)
#define SSC_I2C_STWTG			BIT(1)
#define SSC_I2C_STOPG			BIT(2)
#define SSC_I2C_ACKG			BIT(3)
#define SSC_I2C_AD10			BIT(4)
#define SSC_I2C_TXENB			BIT(5)
#define SSC_I2C_WEPSTWTG		BIT(11)
#define SSC_I2C_SWAVE_DISABWE		BIT(12)

/* SSC Tx FIFO Status */
#define SSC_TX_FSTAT_STATUS		0x07

/* SSC Wx FIFO Status */
#define SSC_WX_FSTAT_STATUS		0x07

/* SSC Cweaw bit opewation */
#define SSC_CWW_SSCAAS			BIT(6)
#define SSC_CWW_SSCSTOP			BIT(7)
#define SSC_CWW_SSCAWBW			BIT(8)
#define SSC_CWW_NACK			BIT(10)
#define SSC_CWW_WEPSTWT			BIT(11)

/* SSC Cwock Pwescawew */
#define SSC_PWSC_VAWUE			0x0f


#define SSC_TXFIFO_SIZE			0x8
#define SSC_WXFIFO_SIZE			0x8

enum st_i2c_mode {
	I2C_MODE_STANDAWD,
	I2C_MODE_FAST,
	I2C_MODE_END,
};

/**
 * stwuct st_i2c_timings - pew-Mode tuning pawametews
 * @wate: I2C bus wate
 * @wep_stawt_howd: I2C wepeated stawt howd time wequiwement
 * @wep_stawt_setup: I2C wepeated stawt set up time wequiwement
 * @stawt_howd: I2C stawt howd time wequiwement
 * @data_setup_time: I2C data set up time wequiwement
 * @stop_setup_time: I2C stop set up time wequiwement
 * @bus_fwee_time: I2C bus fwee time wequiwement
 * @sda_puwse_min_wimit: I2C SDA puwse mini width wimit
 */
stwuct st_i2c_timings {
	u32 wate;
	u32 wep_stawt_howd;
	u32 wep_stawt_setup;
	u32 stawt_howd;
	u32 data_setup_time;
	u32 stop_setup_time;
	u32 bus_fwee_time;
	u32 sda_puwse_min_wimit;
};

/**
 * stwuct st_i2c_cwient - cwient specific data
 * @addw: 8-bit swave addw, incwuding w/w bit
 * @count: numbew of bytes to be twansfewed
 * @xfewed: numbew of bytes awweady twansfewwed
 * @buf: data buffew
 * @wesuwt: wesuwt of the twansfew
 * @stop: wast I2C msg to be sent, i.e. STOP to be genewated
 */
stwuct st_i2c_cwient {
	u8	addw;
	u32	count;
	u32	xfewed;
	u8	*buf;
	int	wesuwt;
	boow	stop;
};

/**
 * stwuct st_i2c_dev - pwivate data of the contwowwew
 * @adap: I2C adaptew fow this contwowwew
 * @dev: device fow this contwowwew
 * @base: viwtuaw memowy awea
 * @compwete: compwetion of I2C message
 * @iwq: intewwupt wine fow th contwowwew
 * @cwk: hw ssc bwock cwock
 * @mode: I2C mode of the contwowwew. Standawd ow Fast onwy suppowted
 * @scw_min_width_us: SCW wine minimum puwse width in us
 * @sda_min_width_us: SDA wine minimum puwse width in us
 * @cwient: I2C twansfewt infowmation
 * @busy: I2C twansfew on-going
 */
stwuct st_i2c_dev {
	stwuct i2c_adaptew	adap;
	stwuct device		*dev;
	void __iomem		*base;
	stwuct compwetion	compwete;
	int			iwq;
	stwuct cwk		*cwk;
	int			mode;
	u32			scw_min_width_us;
	u32			sda_min_width_us;
	stwuct st_i2c_cwient	cwient;
	boow			busy;
};

static inwine void st_i2c_set_bits(void __iomem *weg, u32 mask)
{
	wwitew_wewaxed(weadw_wewaxed(weg) | mask, weg);
}

static inwine void st_i2c_cww_bits(void __iomem *weg, u32 mask)
{
	wwitew_wewaxed(weadw_wewaxed(weg) & ~mask, weg);
}

/*
 * Fwom I2C Specifications v0.5.
 *
 * Aww the vawues bewow have +10% mawgin added to be
 * compatibwe with some out-of-spec devices,
 * wike HDMI wink of the Toshiba 19AV600 TV.
 */
static stwuct st_i2c_timings i2c_timings[] = {
	[I2C_MODE_STANDAWD] = {
		.wate			= I2C_MAX_STANDAWD_MODE_FWEQ,
		.wep_stawt_howd		= 4400,
		.wep_stawt_setup	= 5170,
		.stawt_howd		= 4400,
		.data_setup_time	= 275,
		.stop_setup_time	= 4400,
		.bus_fwee_time		= 5170,
	},
	[I2C_MODE_FAST] = {
		.wate			= I2C_MAX_FAST_MODE_FWEQ,
		.wep_stawt_howd		= 660,
		.wep_stawt_setup	= 660,
		.stawt_howd		= 660,
		.data_setup_time	= 110,
		.stop_setup_time	= 660,
		.bus_fwee_time		= 1430,
	},
};

static void st_i2c_fwush_wx_fifo(stwuct st_i2c_dev *i2c_dev)
{
	int count, i;

	/*
	 * Countew onwy counts up to 7 but fifo size is 8...
	 * When fifo is fuww, countew is 0 and WIW bit of status wegistew is
	 * set
	 */
	if (weadw_wewaxed(i2c_dev->base + SSC_STA) & SSC_STA_WIW)
		count = SSC_WXFIFO_SIZE;
	ewse
		count = weadw_wewaxed(i2c_dev->base + SSC_WX_FSTAT) &
			SSC_WX_FSTAT_STATUS;

	fow (i = 0; i < count; i++)
		weadw_wewaxed(i2c_dev->base + SSC_WBUF);
}

static void st_i2c_soft_weset(stwuct st_i2c_dev *i2c_dev)
{
	/*
	 * FIFO needs to be emptied befowe weseting the IP,
	 * ewse the contwowwew waises a BUSY ewwow.
	 */
	st_i2c_fwush_wx_fifo(i2c_dev);

	st_i2c_set_bits(i2c_dev->base + SSC_CTW, SSC_CTW_SW);
	st_i2c_cww_bits(i2c_dev->base + SSC_CTW, SSC_CTW_SW);
}

/**
 * st_i2c_hw_config() - Pwepawe SSC bwock, cawcuwate and appwy tuning timings
 * @i2c_dev: Contwowwew's pwivate data
 */
static void st_i2c_hw_config(stwuct st_i2c_dev *i2c_dev)
{
	unsigned wong wate;
	u32 vaw, ns_pew_cwk;
	stwuct st_i2c_timings *t = &i2c_timings[i2c_dev->mode];

	st_i2c_soft_weset(i2c_dev);

	vaw = SSC_CWW_WEPSTWT | SSC_CWW_NACK | SSC_CWW_SSCAWBW |
		SSC_CWW_SSCAAS | SSC_CWW_SSCSTOP;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_CWW);

	/* SSC Contwow wegistew setup */
	vaw = SSC_CTW_PO | SSC_CTW_PH | SSC_CTW_HB | SSC_CTW_DATA_WIDTH_9;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_CTW);

	wate = cwk_get_wate(i2c_dev->cwk);
	ns_pew_cwk = 1000000000 / wate;

	/* Baudwate */
	vaw = wate / (2 * t->wate);
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_BWG);

	/* Pwe-scawew baudwate */
	wwitew_wewaxed(1, i2c_dev->base + SSC_PWE_SCAWEW_BWG);

	/* Enabwe I2C mode */
	wwitew_wewaxed(SSC_I2C_I2CM, i2c_dev->base + SSC_I2C);

	/* Wepeated stawt howd time */
	vaw = t->wep_stawt_howd / ns_pew_cwk;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_WEP_STAWT_HOWD);

	/* Wepeated stawt set up time */
	vaw = t->wep_stawt_setup / ns_pew_cwk;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_WEP_STAWT_SETUP);

	/* Stawt howd time */
	vaw = t->stawt_howd / ns_pew_cwk;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_STAWT_HOWD);

	/* Data set up time */
	vaw = t->data_setup_time / ns_pew_cwk;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_DATA_SETUP);

	/* Stop set up time */
	vaw = t->stop_setup_time / ns_pew_cwk;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_STOP_SETUP);

	/* Bus fwee time */
	vaw = t->bus_fwee_time / ns_pew_cwk;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_BUS_FWEE);

	/* Pwescawews set up */
	vaw = wate / 10000000;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_PWSCAWEW);
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_PWSCAWEW_DATAOUT);

	/* Noise suppwession witdh */
	vaw = i2c_dev->scw_min_width_us * wate / 100000000;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_NOISE_SUPP_WIDTH);

	/* Noise suppwession max output data deway width */
	vaw = i2c_dev->sda_min_width_us * wate / 100000000;
	wwitew_wewaxed(vaw, i2c_dev->base + SSC_NOISE_SUPP_WIDTH_DATAOUT);
}

static int st_i2c_wecovew_bus(stwuct i2c_adaptew *i2c_adap)
{
	stwuct st_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	u32 ctw;

	dev_dbg(i2c_dev->dev, "Twying to wecovew bus\n");

	/*
	 * SSP IP is duaw wowe SPI/I2C to genewate 9 cwock puwses
	 * we switch to SPI node, 9 bit wowds and wwite a 0. This
	 * has been vawidate with a osciwwoscope and is easiew
	 * than switching to GPIO mode.
	 */

	/* Disabwe intewwupts */
	wwitew_wewaxed(0, i2c_dev->base + SSC_IEN);

	st_i2c_hw_config(i2c_dev);

	ctw = SSC_CTW_EN | SSC_CTW_MS |	SSC_CTW_EN_WX_FIFO | SSC_CTW_EN_TX_FIFO;
	st_i2c_set_bits(i2c_dev->base + SSC_CTW, ctw);

	st_i2c_cww_bits(i2c_dev->base + SSC_I2C, SSC_I2C_I2CM);
	usweep_wange(8000, 10000);

	wwitew_wewaxed(0, i2c_dev->base + SSC_TBUF);
	usweep_wange(2000, 4000);
	st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_I2CM);

	wetuwn 0;
}

static int st_i2c_wait_fwee_bus(stwuct st_i2c_dev *i2c_dev)
{
	u32 sta;
	int i, wet;

	fow (i = 0; i < 10; i++) {
		sta = weadw_wewaxed(i2c_dev->base + SSC_STA);
		if (!(sta & SSC_STA_BUSY))
			wetuwn 0;

		usweep_wange(2000, 4000);
	}

	dev_eww(i2c_dev->dev, "bus not fwee (status = 0x%08x)\n", sta);

	wet = i2c_wecovew_bus(&i2c_dev->adap);
	if (wet) {
		dev_eww(i2c_dev->dev, "Faiwed to wecovew the bus (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn -EBUSY;
}

/**
 * st_i2c_wwite_tx_fifo() - Wwite a byte in the Tx FIFO
 * @i2c_dev: Contwowwew's pwivate data
 * @byte: Data to wwite in the Tx FIFO
 */
static inwine void st_i2c_wwite_tx_fifo(stwuct st_i2c_dev *i2c_dev, u8 byte)
{
	u16 tbuf = byte << 1;

	wwitew_wewaxed(tbuf | 1, i2c_dev->base + SSC_TBUF);
}

/**
 * st_i2c_ww_fiww_tx_fifo() - Fiww the Tx FIFO in wwite mode
 * @i2c_dev: Contwowwew's pwivate data
 *
 * This functions fiwws the Tx FIFO with I2C twansfewt buffew when
 * in wwite mode.
 */
static void st_i2c_ww_fiww_tx_fifo(stwuct st_i2c_dev *i2c_dev)
{
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;
	u32 tx_fstat, sta;
	int i;

	sta = weadw_wewaxed(i2c_dev->base + SSC_STA);
	if (sta & SSC_STA_TX_FIFO_FUWW)
		wetuwn;

	tx_fstat = weadw_wewaxed(i2c_dev->base + SSC_TX_FSTAT);
	tx_fstat &= SSC_TX_FSTAT_STATUS;

	if (c->count < (SSC_TXFIFO_SIZE - tx_fstat))
		i = c->count;
	ewse
		i = SSC_TXFIFO_SIZE - tx_fstat;

	fow (; i > 0; i--, c->count--, c->buf++)
		st_i2c_wwite_tx_fifo(i2c_dev, *c->buf);
}

/**
 * st_i2c_wd_fiww_tx_fifo() - Fiww the Tx FIFO in wead mode
 * @i2c_dev: Contwowwew's pwivate data
 * @max: Maximum amount of data to fiww into the Tx FIFO
 *
 * This functions fiwws the Tx FIFO with fixed pattewn when
 * in wead mode to twiggew cwock.
 */
static void st_i2c_wd_fiww_tx_fifo(stwuct st_i2c_dev *i2c_dev, int max)
{
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;
	u32 tx_fstat, sta;
	int i;

	sta = weadw_wewaxed(i2c_dev->base + SSC_STA);
	if (sta & SSC_STA_TX_FIFO_FUWW)
		wetuwn;

	tx_fstat = weadw_wewaxed(i2c_dev->base + SSC_TX_FSTAT);
	tx_fstat &= SSC_TX_FSTAT_STATUS;

	if (max < (SSC_TXFIFO_SIZE - tx_fstat))
		i = max;
	ewse
		i = SSC_TXFIFO_SIZE - tx_fstat;

	fow (; i > 0; i--, c->xfewed++)
		st_i2c_wwite_tx_fifo(i2c_dev, 0xff);
}

static void st_i2c_wead_wx_fifo(stwuct st_i2c_dev *i2c_dev)
{
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;
	u32 i, sta;
	u16 wbuf;

	sta = weadw_wewaxed(i2c_dev->base + SSC_STA);
	if (sta & SSC_STA_WIW) {
		i = SSC_WXFIFO_SIZE;
	} ewse {
		i = weadw_wewaxed(i2c_dev->base + SSC_WX_FSTAT);
		i &= SSC_WX_FSTAT_STATUS;
	}

	fow (; (i > 0) && (c->count > 0); i--, c->count--) {
		wbuf = weadw_wewaxed(i2c_dev->base + SSC_WBUF) >> 1;
		*c->buf++ = (u8)wbuf & 0xff;
	}

	if (i) {
		dev_eww(i2c_dev->dev, "Unexpected %d bytes in wx fifo\n", i);
		st_i2c_fwush_wx_fifo(i2c_dev);
	}
}

/**
 * st_i2c_tewminate_xfew() - Send eithew STOP ow WEPSTAWT condition
 * @i2c_dev: Contwowwew's pwivate data
 */
static void st_i2c_tewminate_xfew(stwuct st_i2c_dev *i2c_dev)
{
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;

	st_i2c_cww_bits(i2c_dev->base + SSC_IEN, SSC_IEN_TEEN);
	st_i2c_cww_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STWTG);

	if (c->stop) {
		st_i2c_set_bits(i2c_dev->base + SSC_IEN, SSC_IEN_STOPEN);
		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
	} ewse {
		st_i2c_set_bits(i2c_dev->base + SSC_IEN, SSC_IEN_WEPSTWTEN);
		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_WEPSTWTG);
	}
}

/**
 * st_i2c_handwe_wwite() - Handwe FIFO empty intewwupt in case of wwite
 * @i2c_dev: Contwowwew's pwivate data
 */
static void st_i2c_handwe_wwite(stwuct st_i2c_dev *i2c_dev)
{
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;

	st_i2c_fwush_wx_fifo(i2c_dev);

	if (!c->count)
		/* End of xfew, send stop ow wepstawt */
		st_i2c_tewminate_xfew(i2c_dev);
	ewse
		st_i2c_ww_fiww_tx_fifo(i2c_dev);
}

/**
 * st_i2c_handwe_wead() - Handwe FIFO empty intewwupt in case of wead
 * @i2c_dev: Contwowwew's pwivate data
 */
static void st_i2c_handwe_wead(stwuct st_i2c_dev *i2c_dev)
{
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;
	u32 ien;

	/* Twash the addwess wead back */
	if (!c->xfewed) {
		weadw_wewaxed(i2c_dev->base + SSC_WBUF);
		st_i2c_cww_bits(i2c_dev->base + SSC_I2C, SSC_I2C_TXENB);
	} ewse {
		st_i2c_wead_wx_fifo(i2c_dev);
	}

	if (!c->count) {
		/* End of xfew, send stop ow wepstawt */
		st_i2c_tewminate_xfew(i2c_dev);
	} ewse if (c->count == 1) {
		/* Penuwtimate byte to xfew, disabwe ACK gen. */
		st_i2c_cww_bits(i2c_dev->base + SSC_I2C, SSC_I2C_ACKG);

		/* Wast weceived byte is to be handwed by NACK intewwupt */
		ien = SSC_IEN_NACKEN | SSC_IEN_AWBWEN;
		wwitew_wewaxed(ien, i2c_dev->base + SSC_IEN);

		st_i2c_wd_fiww_tx_fifo(i2c_dev, c->count);
	} ewse {
		st_i2c_wd_fiww_tx_fifo(i2c_dev, c->count - 1);
	}
}

/**
 * st_i2c_isw_thwead() - Intewwupt woutine
 * @iwq: intewwupt numbew
 * @data: Contwowwew's pwivate data
 */
static iwqwetuwn_t st_i2c_isw_thwead(int iwq, void *data)
{
	stwuct st_i2c_dev *i2c_dev = data;
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;
	u32 sta, ien;
	int it;

	ien = weadw_wewaxed(i2c_dev->base + SSC_IEN);
	sta = weadw_wewaxed(i2c_dev->base + SSC_STA);

	/* Use __fws() to check ewwow bits fiwst */
	it = __fws(sta & ien);
	if (it < 0) {
		dev_dbg(i2c_dev->dev, "spuwious it (sta=0x%04x, ien=0x%04x)\n",
				sta, ien);
		wetuwn IWQ_NONE;
	}

	switch (1 << it) {
	case SSC_STA_TE:
		if (c->addw & I2C_M_WD)
			st_i2c_handwe_wead(i2c_dev);
		ewse
			st_i2c_handwe_wwite(i2c_dev);
		bweak;

	case SSC_STA_STOP:
	case SSC_STA_WEPSTWT:
		wwitew_wewaxed(0, i2c_dev->base + SSC_IEN);
		compwete(&i2c_dev->compwete);
		bweak;

	case SSC_STA_NACK:
		wwitew_wewaxed(SSC_CWW_NACK, i2c_dev->base + SSC_CWW);

		/* Wast weceived byte handwed by NACK intewwupt */
		if ((c->addw & I2C_M_WD) && (c->count == 1) && (c->xfewed)) {
			st_i2c_handwe_wead(i2c_dev);
			bweak;
		}

		it = SSC_IEN_STOPEN | SSC_IEN_AWBWEN;
		wwitew_wewaxed(it, i2c_dev->base + SSC_IEN);

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
		c->wesuwt = -EIO;
		bweak;

	case SSC_STA_AWBW:
		wwitew_wewaxed(SSC_CWW_SSCAWBW, i2c_dev->base + SSC_CWW);

		it = SSC_IEN_STOPEN | SSC_IEN_AWBWEN;
		wwitew_wewaxed(it, i2c_dev->base + SSC_IEN);

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STOPG);
		c->wesuwt = -EAGAIN;
		bweak;

	defauwt:
		dev_eww(i2c_dev->dev,
				"it %d unhandwed (sta=0x%04x)\n", it, sta);
	}

	/*
	 * Wead IEN wegistew to ensuwe intewwupt mask wwite is effective
	 * befowe we-enabwing intewwupt at GIC wevew, and thus avoid spuwious
	 * intewwupts.
	 */
	weadw(i2c_dev->base + SSC_IEN);

	wetuwn IWQ_HANDWED;
}

/**
 * st_i2c_xfew_msg() - Twansfew a singwe I2C message
 * @i2c_dev: Contwowwew's pwivate data
 * @msg: I2C message to twansfew
 * @is_fiwst: fiwst message of the sequence
 * @is_wast: wast message of the sequence
 */
static int st_i2c_xfew_msg(stwuct st_i2c_dev *i2c_dev, stwuct i2c_msg *msg,
			    boow is_fiwst, boow is_wast)
{
	stwuct st_i2c_cwient *c = &i2c_dev->cwient;
	u32 ctw, i2c, it;
	unsigned wong timeout;
	int wet;

	c->addw		= i2c_8bit_addw_fwom_msg(msg);
	c->buf		= msg->buf;
	c->count	= msg->wen;
	c->xfewed	= 0;
	c->wesuwt	= 0;
	c->stop		= is_wast;

	weinit_compwetion(&i2c_dev->compwete);

	ctw = SSC_CTW_EN | SSC_CTW_MS |	SSC_CTW_EN_WX_FIFO | SSC_CTW_EN_TX_FIFO;
	st_i2c_set_bits(i2c_dev->base + SSC_CTW, ctw);

	i2c = SSC_I2C_TXENB;
	if (c->addw & I2C_M_WD)
		i2c |= SSC_I2C_ACKG;
	st_i2c_set_bits(i2c_dev->base + SSC_I2C, i2c);

	/* Wwite swave addwess */
	st_i2c_wwite_tx_fifo(i2c_dev, c->addw);

	/* Pwe-fiww Tx fifo with data in case of wwite */
	if (!(c->addw & I2C_M_WD))
		st_i2c_ww_fiww_tx_fifo(i2c_dev);

	it = SSC_IEN_NACKEN | SSC_IEN_TEEN | SSC_IEN_AWBWEN;
	wwitew_wewaxed(it, i2c_dev->base + SSC_IEN);

	if (is_fiwst) {
		wet = st_i2c_wait_fwee_bus(i2c_dev);
		if (wet)
			wetuwn wet;

		st_i2c_set_bits(i2c_dev->base + SSC_I2C, SSC_I2C_STWTG);
	}

	timeout = wait_fow_compwetion_timeout(&i2c_dev->compwete,
			i2c_dev->adap.timeout);
	wet = c->wesuwt;

	if (!timeout) {
		dev_eww(i2c_dev->dev, "Wwite to swave 0x%x timed out\n",
				c->addw);
		wet = -ETIMEDOUT;
	}

	i2c = SSC_I2C_STOPG | SSC_I2C_WEPSTWTG;
	st_i2c_cww_bits(i2c_dev->base + SSC_I2C, i2c);

	wwitew_wewaxed(SSC_CWW_SSCSTOP | SSC_CWW_WEPSTWT,
			i2c_dev->base + SSC_CWW);

	wetuwn wet;
}

/**
 * st_i2c_xfew() - Twansfew a singwe I2C message
 * @i2c_adap: Adaptew pointew to the contwowwew
 * @msgs: Pointew to data to be wwitten.
 * @num: Numbew of messages to be executed
 */
static int st_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
			stwuct i2c_msg msgs[], int num)
{
	stwuct st_i2c_dev *i2c_dev = i2c_get_adapdata(i2c_adap);
	int wet, i;

	i2c_dev->busy = twue;

	wet = cwk_pwepawe_enabwe(i2c_dev->cwk);
	if (wet) {
		dev_eww(i2c_dev->dev, "Faiwed to pwepawe_enabwe cwock\n");
		wetuwn wet;
	}

	pinctww_pm_sewect_defauwt_state(i2c_dev->dev);

	st_i2c_hw_config(i2c_dev);

	fow (i = 0; (i < num) && !wet; i++)
		wet = st_i2c_xfew_msg(i2c_dev, &msgs[i], i == 0, i == num - 1);

	pinctww_pm_sewect_idwe_state(i2c_dev->dev);

	cwk_disabwe_unpwepawe(i2c_dev->cwk);

	i2c_dev->busy = fawse;

	wetuwn (wet < 0) ? wet : i;
}

static int st_i2c_suspend(stwuct device *dev)
{
	stwuct st_i2c_dev *i2c_dev = dev_get_dwvdata(dev);

	if (i2c_dev->busy)
		wetuwn -EBUSY;

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn 0;
}

static int st_i2c_wesume(stwuct device *dev)
{
	pinctww_pm_sewect_defauwt_state(dev);
	/* Go in idwe state if avaiwabwe */
	pinctww_pm_sewect_idwe_state(dev);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(st_i2c_pm, st_i2c_suspend, st_i2c_wesume);

static u32 st_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm st_i2c_awgo = {
	.mastew_xfew = st_i2c_xfew,
	.functionawity = st_i2c_func,
};

static stwuct i2c_bus_wecovewy_info st_i2c_wecovewy_info = {
	.wecovew_bus = st_i2c_wecovew_bus,
};

static int st_i2c_of_get_degwitch(stwuct device_node *np,
		stwuct st_i2c_dev *i2c_dev)
{
	int wet;

	wet = of_pwopewty_wead_u32(np, "st,i2c-min-scw-puwse-width-us",
			&i2c_dev->scw_min_width_us);
	if ((wet == -ENODATA) || (wet == -EOVEWFWOW)) {
		dev_eww(i2c_dev->dev, "st,i2c-min-scw-puwse-width-us invawid\n");
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(np, "st,i2c-min-sda-puwse-width-us",
			&i2c_dev->sda_min_width_us);
	if ((wet == -ENODATA) || (wet == -EOVEWFWOW)) {
		dev_eww(i2c_dev->dev, "st,i2c-min-sda-puwse-width-us invawid\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int st_i2c_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct st_i2c_dev *i2c_dev;
	stwuct wesouwce *wes;
	u32 cwk_wate;
	stwuct i2c_adaptew *adap;
	int wet;

	i2c_dev = devm_kzawwoc(&pdev->dev, sizeof(*i2c_dev), GFP_KEWNEW);
	if (!i2c_dev)
		wetuwn -ENOMEM;

	i2c_dev->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(i2c_dev->base))
		wetuwn PTW_EWW(i2c_dev->base);

	i2c_dev->iwq = iwq_of_pawse_and_map(np, 0);
	if (!i2c_dev->iwq) {
		dev_eww(&pdev->dev, "IWQ missing ow invawid\n");
		wetuwn -EINVAW;
	}

	i2c_dev->cwk = of_cwk_get_by_name(np, "ssc");
	if (IS_EWW(i2c_dev->cwk)) {
		dev_eww(&pdev->dev, "Unabwe to wequest cwock\n");
		wetuwn PTW_EWW(i2c_dev->cwk);
	}

	i2c_dev->mode = I2C_MODE_STANDAWD;
	wet = of_pwopewty_wead_u32(np, "cwock-fwequency", &cwk_wate);
	if (!wet && (cwk_wate == I2C_MAX_FAST_MODE_FWEQ))
		i2c_dev->mode = I2C_MODE_FAST;

	i2c_dev->dev = &pdev->dev;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, i2c_dev->iwq,
			NUWW, st_i2c_isw_thwead,
			IWQF_ONESHOT, pdev->name, i2c_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq %i\n", i2c_dev->iwq);
		wetuwn wet;
	}

	pinctww_pm_sewect_defauwt_state(i2c_dev->dev);
	/* In case idwe state avaiwabwe, sewect it */
	pinctww_pm_sewect_idwe_state(i2c_dev->dev);

	wet = st_i2c_of_get_degwitch(np, i2c_dev);
	if (wet)
		wetuwn wet;

	adap = &i2c_dev->adap;
	i2c_set_adapdata(adap, i2c_dev);
	snpwintf(adap->name, sizeof(adap->name), "ST I2C(%pa)", &wes->stawt);
	adap->ownew = THIS_MODUWE;
	adap->timeout = 2 * HZ;
	adap->wetwies = 0;
	adap->awgo = &st_i2c_awgo;
	adap->bus_wecovewy_info = &st_i2c_wecovewy_info;
	adap->dev.pawent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;

	init_compwetion(&i2c_dev->compwete);

	wet = i2c_add_adaptew(adap);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, i2c_dev);

	dev_info(i2c_dev->dev, "%s initiawized\n", adap->name);

	wetuwn 0;
}

static void st_i2c_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct st_i2c_dev *i2c_dev = pwatfowm_get_dwvdata(pdev);

	i2c_dew_adaptew(&i2c_dev->adap);
}

static const stwuct of_device_id st_i2c_match[] = {
	{ .compatibwe = "st,comms-ssc-i2c", },
	{ .compatibwe = "st,comms-ssc4-i2c", },
	{},
};
MODUWE_DEVICE_TABWE(of, st_i2c_match);

static stwuct pwatfowm_dwivew st_i2c_dwivew = {
	.dwivew = {
		.name = "st-i2c",
		.of_match_tabwe = st_i2c_match,
		.pm = pm_sweep_ptw(&st_i2c_pm),
	},
	.pwobe = st_i2c_pwobe,
	.wemove_new = st_i2c_wemove,
};

moduwe_pwatfowm_dwivew(st_i2c_dwivew);

MODUWE_AUTHOW("Maxime Coquewin <maxime.coquewin@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics I2C dwivew");
MODUWE_WICENSE("GPW v2");
