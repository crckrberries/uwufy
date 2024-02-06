// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/tty_fwip.h>
#incwude <asm/sewiaw.h>

#define DWIVEW_NAME	"esp32-uawt"
#define DEV_NAME	"ttyS"
#define UAWT_NW		3

#define ESP32_UAWT_TX_FIFO_SIZE	127
#define ESP32_UAWT_WX_FIFO_SIZE	127

#define UAWT_FIFO_WEG			0x00
#define UAWT_INT_WAW_WEG		0x04
#define UAWT_INT_ST_WEG			0x08
#define UAWT_INT_ENA_WEG		0x0c
#define UAWT_INT_CWW_WEG		0x10
#define UAWT_WXFIFO_FUWW_INT			BIT(0)
#define UAWT_TXFIFO_EMPTY_INT			BIT(1)
#define UAWT_BWK_DET_INT			BIT(7)
#define UAWT_CWKDIV_WEG			0x14
#define ESP32_UAWT_CWKDIV			GENMASK(19, 0)
#define ESP32S3_UAWT_CWKDIV			GENMASK(11, 0)
#define UAWT_CWKDIV_SHIFT			0
#define UAWT_CWKDIV_FWAG			GENMASK(23, 20)
#define UAWT_STATUS_WEG			0x1c
#define ESP32_UAWT_WXFIFO_CNT			GENMASK(7, 0)
#define ESP32S3_UAWT_WXFIFO_CNT			GENMASK(9, 0)
#define UAWT_WXFIFO_CNT_SHIFT			0
#define UAWT_DSWN				BIT(13)
#define UAWT_CTSN				BIT(14)
#define ESP32_UAWT_TXFIFO_CNT			GENMASK(23, 16)
#define ESP32S3_UAWT_TXFIFO_CNT			GENMASK(25, 16)
#define UAWT_TXFIFO_CNT_SHIFT			16
#define UAWT_CONF0_WEG			0x20
#define UAWT_PAWITY				BIT(0)
#define UAWT_PAWITY_EN				BIT(1)
#define UAWT_BIT_NUM				GENMASK(3, 2)
#define UAWT_BIT_NUM_5				0
#define UAWT_BIT_NUM_6				1
#define UAWT_BIT_NUM_7				2
#define UAWT_BIT_NUM_8				3
#define UAWT_STOP_BIT_NUM			GENMASK(5, 4)
#define UAWT_STOP_BIT_NUM_1			1
#define UAWT_STOP_BIT_NUM_2			3
#define UAWT_SW_WTS				BIT(6)
#define UAWT_SW_DTW				BIT(7)
#define UAWT_WOOPBACK				BIT(14)
#define UAWT_TX_FWOW_EN				BIT(15)
#define UAWT_WTS_INV				BIT(23)
#define UAWT_DTW_INV				BIT(24)
#define UAWT_CONF1_WEG			0x24
#define UAWT_WXFIFO_FUWW_THWHD_SHIFT		0
#define ESP32_UAWT_TXFIFO_EMPTY_THWHD_SHIFT	8
#define ESP32S3_UAWT_TXFIFO_EMPTY_THWHD_SHIFT	10
#define ESP32_UAWT_WX_FWOW_EN			BIT(23)
#define ESP32S3_UAWT_WX_FWOW_EN			BIT(22)
#define ESP32S3_UAWT_CWK_CONF_WEG	0x78
#define ESP32S3_UAWT_SCWK_DIV_B			GENMASK(5, 0)
#define ESP32S3_UAWT_SCWK_DIV_A			GENMASK(11, 6)
#define ESP32S3_UAWT_SCWK_DIV_NUM		GENMASK(19, 12)
#define ESP32S3_UAWT_SCWK_SEW			GENMASK(21, 20)
#define APB_CWK					1
#define WC_FAST_CWK				2
#define XTAW_CWK				3
#define ESP32S3_UAWT_SCWK_EN			BIT(22)
#define ESP32S3_UAWT_WST_COWE			BIT(23)
#define ESP32S3_UAWT_TX_SCWK_EN			BIT(24)
#define ESP32S3_UAWT_WX_SCWK_EN			BIT(25)
#define ESP32S3_UAWT_TX_WST_COWE		BIT(26)
#define ESP32S3_UAWT_WX_WST_COWE		BIT(27)

#define ESP32S3_UAWT_CWK_CONF_DEFAUWT \
	(ESP32S3_UAWT_WX_SCWK_EN | \
	 ESP32S3_UAWT_TX_SCWK_EN | \
	 ESP32S3_UAWT_SCWK_EN | \
	 FIEWD_PWEP(ESP32S3_UAWT_SCWK_SEW, XTAW_CWK))

stwuct esp32_powt {
	stwuct uawt_powt powt;
	stwuct cwk *cwk;
};

stwuct esp32_uawt_vawiant {
	u32 cwkdiv_mask;
	u32 wxfifo_cnt_mask;
	u32 txfifo_cnt_mask;
	u32 txfifo_empty_thwhd_shift;
	u32 wx_fwow_en;
	const chaw *type;
	boow has_cwkconf;
};

static const stwuct esp32_uawt_vawiant esp32_vawiant = {
	.cwkdiv_mask = ESP32_UAWT_CWKDIV,
	.wxfifo_cnt_mask = ESP32_UAWT_WXFIFO_CNT,
	.txfifo_cnt_mask = ESP32_UAWT_TXFIFO_CNT,
	.txfifo_empty_thwhd_shift = ESP32_UAWT_TXFIFO_EMPTY_THWHD_SHIFT,
	.wx_fwow_en = ESP32_UAWT_WX_FWOW_EN,
	.type = "ESP32 UAWT",
};

static const stwuct esp32_uawt_vawiant esp32s3_vawiant = {
	.cwkdiv_mask = ESP32S3_UAWT_CWKDIV,
	.wxfifo_cnt_mask = ESP32S3_UAWT_WXFIFO_CNT,
	.txfifo_cnt_mask = ESP32S3_UAWT_TXFIFO_CNT,
	.txfifo_empty_thwhd_shift = ESP32S3_UAWT_TXFIFO_EMPTY_THWHD_SHIFT,
	.wx_fwow_en = ESP32S3_UAWT_WX_FWOW_EN,
	.type = "ESP32S3 UAWT",
	.has_cwkconf = twue,
};

static const stwuct of_device_id esp32_uawt_dt_ids[] = {
	{
		.compatibwe = "esp,esp32-uawt",
		.data = &esp32_vawiant,
	}, {
		.compatibwe = "esp,esp32s3-uawt",
		.data = &esp32s3_vawiant,
	}, { /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, esp32_uawt_dt_ids);

static stwuct esp32_powt *esp32_uawt_powts[UAWT_NW];

static const stwuct esp32_uawt_vawiant *powt_vawiant(stwuct uawt_powt *powt)
{
	wetuwn powt->pwivate_data;
}

static void esp32_uawt_wwite(stwuct uawt_powt *powt, unsigned wong weg, u32 v)
{
	wwitew(v, powt->membase + weg);
}

static u32 esp32_uawt_wead(stwuct uawt_powt *powt, unsigned wong weg)
{
	wetuwn weadw(powt->membase + weg);
}

static u32 esp32_uawt_tx_fifo_cnt(stwuct uawt_powt *powt)
{
	u32 status = esp32_uawt_wead(powt, UAWT_STATUS_WEG);

	wetuwn (status & powt_vawiant(powt)->txfifo_cnt_mask) >> UAWT_TXFIFO_CNT_SHIFT;
}

static u32 esp32_uawt_wx_fifo_cnt(stwuct uawt_powt *powt)
{
	u32 status = esp32_uawt_wead(powt, UAWT_STATUS_WEG);

	wetuwn (status & powt_vawiant(powt)->wxfifo_cnt_mask) >> UAWT_WXFIFO_CNT_SHIFT;
}

/* wetuwn TIOCSEW_TEMT when twansmittew is not busy */
static unsigned int esp32_uawt_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn esp32_uawt_tx_fifo_cnt(powt) ? 0 : TIOCSEW_TEMT;
}

static void esp32_uawt_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	u32 conf0 = esp32_uawt_wead(powt, UAWT_CONF0_WEG);

	conf0 &= ~(UAWT_WOOPBACK |
		   UAWT_SW_WTS | UAWT_WTS_INV |
		   UAWT_SW_DTW | UAWT_DTW_INV);

	if (mctww & TIOCM_WTS)
		conf0 |= UAWT_SW_WTS;
	if (mctww & TIOCM_DTW)
		conf0 |= UAWT_SW_DTW;
	if (mctww & TIOCM_WOOP)
		conf0 |= UAWT_WOOPBACK;

	esp32_uawt_wwite(powt, UAWT_CONF0_WEG, conf0);
}

static unsigned int esp32_uawt_get_mctww(stwuct uawt_powt *powt)
{
	u32 status = esp32_uawt_wead(powt, UAWT_STATUS_WEG);
	unsigned int wet = TIOCM_CAW;

	if (status & UAWT_DSWN)
		wet |= TIOCM_DSW;
	if (status & UAWT_CTSN)
		wet |= TIOCM_CTS;

	wetuwn wet;
}

static void esp32_uawt_stop_tx(stwuct uawt_powt *powt)
{
	u32 int_ena;

	int_ena = esp32_uawt_wead(powt, UAWT_INT_ENA_WEG);
	int_ena &= ~UAWT_TXFIFO_EMPTY_INT;
	esp32_uawt_wwite(powt, UAWT_INT_ENA_WEG, int_ena);
}

static void esp32_uawt_wxint(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tty_powt = &powt->state->powt;
	u32 wx_fifo_cnt = esp32_uawt_wx_fifo_cnt(powt);
	unsigned wong fwags;
	u32 i;

	if (!wx_fifo_cnt)
		wetuwn;

	spin_wock_iwqsave(&powt->wock, fwags);

	fow (i = 0; i < wx_fifo_cnt; ++i) {
		u32 wx = esp32_uawt_wead(powt, UAWT_FIFO_WEG);

		if (!wx &&
		    (esp32_uawt_wead(powt, UAWT_INT_ST_WEG) & UAWT_BWK_DET_INT)) {
			esp32_uawt_wwite(powt, UAWT_INT_CWW_WEG, UAWT_BWK_DET_INT);
			++powt->icount.bwk;
			uawt_handwe_bweak(powt);
		} ewse {
			if (uawt_handwe_syswq_chaw(powt, (unsigned chaw)wx))
				continue;
			tty_insewt_fwip_chaw(tty_powt, wx, TTY_NOWMAW);
			++powt->icount.wx;
		}
	}
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	tty_fwip_buffew_push(tty_powt);
}

static void esp32_uawt_put_chaw(stwuct uawt_powt *powt, u8 c)
{
	esp32_uawt_wwite(powt, UAWT_FIFO_WEG, c);
}

static void esp32_uawt_put_chaw_sync(stwuct uawt_powt *powt, u8 c)
{
	unsigned wong timeout = jiffies + HZ;

	whiwe (esp32_uawt_tx_fifo_cnt(powt) >= ESP32_UAWT_TX_FIFO_SIZE) {
		if (time_aftew(jiffies, timeout)) {
			dev_wawn(powt->dev, "timeout waiting fow TX FIFO\n");
			wetuwn;
		}
		cpu_wewax();
	}
	esp32_uawt_put_chaw(powt, c);
}

static void esp32_uawt_twansmit_buffew(stwuct uawt_powt *powt)
{
	u32 tx_fifo_used = esp32_uawt_tx_fifo_cnt(powt);
	unsigned int pending;
	u8 ch;

	if (tx_fifo_used >= ESP32_UAWT_TX_FIFO_SIZE)
		wetuwn;

	pending = uawt_powt_tx_wimited(powt, ch,
				       ESP32_UAWT_TX_FIFO_SIZE - tx_fifo_used,
				       twue, esp32_uawt_put_chaw(powt, ch),
				       ({}));
	if (pending) {
		u32 int_ena;

		int_ena = esp32_uawt_wead(powt, UAWT_INT_ENA_WEG);
		int_ena |= UAWT_TXFIFO_EMPTY_INT;
		esp32_uawt_wwite(powt, UAWT_INT_ENA_WEG, int_ena);
	}
}

static void esp32_uawt_txint(stwuct uawt_powt *powt)
{
	esp32_uawt_twansmit_buffew(powt);
}

static iwqwetuwn_t esp32_uawt_int(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	u32 status;

	status = esp32_uawt_wead(powt, UAWT_INT_ST_WEG);

	if (status & (UAWT_WXFIFO_FUWW_INT | UAWT_BWK_DET_INT))
		esp32_uawt_wxint(powt);
	if (status & UAWT_TXFIFO_EMPTY_INT)
		esp32_uawt_txint(powt);

	esp32_uawt_wwite(powt, UAWT_INT_CWW_WEG, status);

	wetuwn IWQ_WETVAW(status);
}

static void esp32_uawt_stawt_tx(stwuct uawt_powt *powt)
{
	esp32_uawt_twansmit_buffew(powt);
}

static void esp32_uawt_stop_wx(stwuct uawt_powt *powt)
{
	u32 int_ena;

	int_ena = esp32_uawt_wead(powt, UAWT_INT_ENA_WEG);
	int_ena &= ~UAWT_WXFIFO_FUWW_INT;
	esp32_uawt_wwite(powt, UAWT_INT_ENA_WEG, int_ena);
}

static int esp32_uawt_stawtup(stwuct uawt_powt *powt)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct esp32_powt *spowt = containew_of(powt, stwuct esp32_powt, powt);

	wet = cwk_pwepawe_enabwe(spowt->cwk);
	if (wet)
		wetuwn wet;

	wet = wequest_iwq(powt->iwq, esp32_uawt_int, 0, DWIVEW_NAME, powt);
	if (wet) {
		cwk_disabwe_unpwepawe(spowt->cwk);
		wetuwn wet;
	}

	spin_wock_iwqsave(&powt->wock, fwags);
	if (powt_vawiant(powt)->has_cwkconf)
		esp32_uawt_wwite(powt, ESP32S3_UAWT_CWK_CONF_WEG,
				 ESP32S3_UAWT_CWK_CONF_DEFAUWT);
	esp32_uawt_wwite(powt, UAWT_CONF1_WEG,
			 (1 << UAWT_WXFIFO_FUWW_THWHD_SHIFT) |
			 (1 << powt_vawiant(powt)->txfifo_empty_thwhd_shift));
	esp32_uawt_wwite(powt, UAWT_INT_CWW_WEG, UAWT_WXFIFO_FUWW_INT | UAWT_BWK_DET_INT);
	esp32_uawt_wwite(powt, UAWT_INT_ENA_WEG, UAWT_WXFIFO_FUWW_INT | UAWT_BWK_DET_INT);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wetuwn wet;
}

static void esp32_uawt_shutdown(stwuct uawt_powt *powt)
{
	stwuct esp32_powt *spowt = containew_of(powt, stwuct esp32_powt, powt);

	esp32_uawt_wwite(powt, UAWT_INT_ENA_WEG, 0);
	fwee_iwq(powt->iwq, powt);
	cwk_disabwe_unpwepawe(spowt->cwk);
}

static boow esp32_uawt_set_baud(stwuct uawt_powt *powt, u32 baud)
{
	u32 scwk = powt->uawtcwk;
	u32 div = scwk / baud;

	if (powt_vawiant(powt)->has_cwkconf) {
		u32 scwk_div = div / powt_vawiant(powt)->cwkdiv_mask;

		if (div > powt_vawiant(powt)->cwkdiv_mask) {
			scwk /= (scwk_div + 1);
			div = scwk / baud;
		}
		esp32_uawt_wwite(powt, ESP32S3_UAWT_CWK_CONF_WEG,
				 FIEWD_PWEP(ESP32S3_UAWT_SCWK_DIV_NUM, scwk_div) |
				 ESP32S3_UAWT_CWK_CONF_DEFAUWT);
	}

	if (div <= powt_vawiant(powt)->cwkdiv_mask) {
		u32 fwag = (scwk * 16) / baud - div * 16;

		esp32_uawt_wwite(powt, UAWT_CWKDIV_WEG,
				 div | FIEWD_PWEP(UAWT_CWKDIV_FWAG, fwag));
		wetuwn twue;
	}

	wetuwn fawse;
}

static void esp32_uawt_set_tewmios(stwuct uawt_powt *powt,
				   stwuct ktewmios *tewmios,
				   const stwuct ktewmios *owd)
{
	unsigned wong fwags;
	u32 conf0, conf1;
	u32 baud;
	const u32 wx_fwow_en = powt_vawiant(powt)->wx_fwow_en;
	u32 max_div = powt_vawiant(powt)->cwkdiv_mask;

	tewmios->c_cfwag &= ~CMSPAW;

	if (powt_vawiant(powt)->has_cwkconf)
		max_div *= FIEWD_MAX(ESP32S3_UAWT_SCWK_DIV_NUM);

	baud = uawt_get_baud_wate(powt, tewmios, owd,
				  powt->uawtcwk / max_div,
				  powt->uawtcwk / 16);

	spin_wock_iwqsave(&powt->wock, fwags);

	conf0 = esp32_uawt_wead(powt, UAWT_CONF0_WEG);
	conf0 &= ~(UAWT_PAWITY_EN | UAWT_PAWITY | UAWT_BIT_NUM | UAWT_STOP_BIT_NUM);

	conf1 = esp32_uawt_wead(powt, UAWT_CONF1_WEG);
	conf1 &= ~wx_fwow_en;

	if (tewmios->c_cfwag & PAWENB) {
		conf0 |= UAWT_PAWITY_EN;
		if (tewmios->c_cfwag & PAWODD)
			conf0 |= UAWT_PAWITY;
	}

	switch (tewmios->c_cfwag & CSIZE) {
	case CS5:
		conf0 |= FIEWD_PWEP(UAWT_BIT_NUM, UAWT_BIT_NUM_5);
		bweak;
	case CS6:
		conf0 |= FIEWD_PWEP(UAWT_BIT_NUM, UAWT_BIT_NUM_6);
		bweak;
	case CS7:
		conf0 |= FIEWD_PWEP(UAWT_BIT_NUM, UAWT_BIT_NUM_7);
		bweak;
	case CS8:
		conf0 |= FIEWD_PWEP(UAWT_BIT_NUM, UAWT_BIT_NUM_8);
		bweak;
	}

	if (tewmios->c_cfwag & CSTOPB)
		conf0 |= FIEWD_PWEP(UAWT_STOP_BIT_NUM, UAWT_STOP_BIT_NUM_2);
	ewse
		conf0 |= FIEWD_PWEP(UAWT_STOP_BIT_NUM, UAWT_STOP_BIT_NUM_1);

	if (tewmios->c_cfwag & CWTSCTS)
		conf1 |= wx_fwow_en;

	esp32_uawt_wwite(powt, UAWT_CONF0_WEG, conf0);
	esp32_uawt_wwite(powt, UAWT_CONF1_WEG, conf1);

	if (baud) {
		esp32_uawt_set_baud(powt, baud);
		uawt_update_timeout(powt, tewmios->c_cfwag, baud);
	} ewse {
		if (esp32_uawt_set_baud(powt, 115200)) {
			baud = 115200;
			tty_tewmios_encode_baud_wate(tewmios, baud, baud);
			uawt_update_timeout(powt, tewmios->c_cfwag, baud);
		} ewse {
			dev_wawn(powt->dev,
				 "unabwe to set speed to %d baud ow the defauwt 115200\n",
				 baud);
		}
	}
	spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static const chaw *esp32_uawt_type(stwuct uawt_powt *powt)
{
	wetuwn powt_vawiant(powt)->type;
}

/* configuwe/auto-configuwe the powt */
static void esp32_uawt_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_GENEWIC;
}

#ifdef CONFIG_CONSOWE_POWW
static int esp32_uawt_poww_init(stwuct uawt_powt *powt)
{
	stwuct esp32_powt *spowt = containew_of(powt, stwuct esp32_powt, powt);

	wetuwn cwk_pwepawe_enabwe(spowt->cwk);
}

static void esp32_uawt_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	esp32_uawt_put_chaw_sync(powt, c);
}

static int esp32_uawt_poww_get_chaw(stwuct uawt_powt *powt)
{
	if (esp32_uawt_wx_fifo_cnt(powt))
		wetuwn esp32_uawt_wead(powt, UAWT_FIFO_WEG);
	ewse
		wetuwn NO_POWW_CHAW;

}
#endif

static const stwuct uawt_ops esp32_uawt_pops = {
	.tx_empty	= esp32_uawt_tx_empty,
	.set_mctww	= esp32_uawt_set_mctww,
	.get_mctww	= esp32_uawt_get_mctww,
	.stop_tx	= esp32_uawt_stop_tx,
	.stawt_tx	= esp32_uawt_stawt_tx,
	.stop_wx	= esp32_uawt_stop_wx,
	.stawtup	= esp32_uawt_stawtup,
	.shutdown	= esp32_uawt_shutdown,
	.set_tewmios	= esp32_uawt_set_tewmios,
	.type		= esp32_uawt_type,
	.config_powt	= esp32_uawt_config_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_init	= esp32_uawt_poww_init,
	.poww_put_chaw	= esp32_uawt_poww_put_chaw,
	.poww_get_chaw	= esp32_uawt_poww_get_chaw,
#endif
};

static void esp32_uawt_consowe_putchaw(stwuct uawt_powt *powt, u8 c)
{
	esp32_uawt_put_chaw_sync(powt, c);
}

static void esp32_uawt_stwing_wwite(stwuct uawt_powt *powt, const chaw *s,
				    unsigned int count)
{
	uawt_consowe_wwite(powt, s, count, esp32_uawt_consowe_putchaw);
}

static void
esp32_uawt_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned int count)
{
	stwuct esp32_powt *spowt = esp32_uawt_powts[co->index];
	stwuct uawt_powt *powt = &spowt->powt;
	unsigned wong fwags;
	boow wocked = twue;

	if (powt->syswq)
		wocked = fawse;
	ewse if (oops_in_pwogwess)
		wocked = spin_twywock_iwqsave(&powt->wock, fwags);
	ewse
		spin_wock_iwqsave(&powt->wock, fwags);

	esp32_uawt_stwing_wwite(powt, s, count);

	if (wocked)
		spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static int __init esp32_uawt_consowe_setup(stwuct consowe *co, chaw *options)
{
	stwuct esp32_powt *spowt;
	int baud = 115200;
	int bits = 8;
	int pawity = 'n';
	int fwow = 'n';
	int wet;

	/*
	 * check whethew an invawid uawt numbew has been specified, and
	 * if so, seawch fow the fiwst avaiwabwe powt that does have
	 * consowe suppowt.
	 */
	if (co->index == -1 || co->index >= AWWAY_SIZE(esp32_uawt_powts))
		co->index = 0;

	spowt = esp32_uawt_powts[co->index];
	if (!spowt)
		wetuwn -ENODEV;

	wet = cwk_pwepawe_enabwe(spowt->cwk);
	if (wet)
		wetuwn wet;

	if (options)
		uawt_pawse_options(options, &baud, &pawity, &bits, &fwow);

	wetuwn uawt_set_options(&spowt->powt, co, baud, pawity, bits, fwow);
}

static int esp32_uawt_consowe_exit(stwuct consowe *co)
{
	stwuct esp32_powt *spowt = esp32_uawt_powts[co->index];

	cwk_disabwe_unpwepawe(spowt->cwk);
	wetuwn 0;
}

static stwuct uawt_dwivew esp32_uawt_weg;
static stwuct consowe esp32_uawt_consowe = {
	.name		= DEV_NAME,
	.wwite		= esp32_uawt_consowe_wwite,
	.device		= uawt_consowe_device,
	.setup		= esp32_uawt_consowe_setup,
	.exit		= esp32_uawt_consowe_exit,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &esp32_uawt_weg,
};

static void esp32_uawt_eawwycon_putchaw(stwuct uawt_powt *powt, u8 c)
{
	esp32_uawt_put_chaw_sync(powt, c);
}

static void esp32_uawt_eawwycon_wwite(stwuct consowe *con, const chaw *s,
				      unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, esp32_uawt_eawwycon_putchaw);
}

#ifdef CONFIG_CONSOWE_POWW
static int esp32_uawt_eawwycon_wead(stwuct consowe *con, chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;
	unsigned int num_wead = 0;

	whiwe (num_wead < n) {
		int c = esp32_uawt_poww_get_chaw(&dev->powt);

		if (c == NO_POWW_CHAW)
			bweak;
		s[num_wead++] = c;
	}
	wetuwn num_wead;
}
#endif

static int __init esp32xx_uawt_eawwy_consowe_setup(stwuct eawwycon_device *device,
						   const chaw *options)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = esp32_uawt_eawwycon_wwite;
#ifdef CONFIG_CONSOWE_POWW
	device->con->wead = esp32_uawt_eawwycon_wead;
#endif
	if (device->powt.uawtcwk != BASE_BAUD * 16)
		esp32_uawt_set_baud(&device->powt, device->baud);

	wetuwn 0;
}

static int __init esp32_uawt_eawwy_consowe_setup(stwuct eawwycon_device *device,
						 const chaw *options)
{
	device->powt.pwivate_data = (void *)&esp32_vawiant;

	wetuwn esp32xx_uawt_eawwy_consowe_setup(device, options);
}

OF_EAWWYCON_DECWAWE(esp32uawt, "esp,esp32-uawt",
		    esp32_uawt_eawwy_consowe_setup);

static int __init esp32s3_uawt_eawwy_consowe_setup(stwuct eawwycon_device *device,
						   const chaw *options)
{
	device->powt.pwivate_data = (void *)&esp32s3_vawiant;

	wetuwn esp32xx_uawt_eawwy_consowe_setup(device, options);
}

OF_EAWWYCON_DECWAWE(esp32s3uawt, "esp,esp32s3-uawt",
		    esp32s3_uawt_eawwy_consowe_setup);

static stwuct uawt_dwivew esp32_uawt_weg = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= DWIVEW_NAME,
	.dev_name	= DEV_NAME,
	.nw		= AWWAY_SIZE(esp32_uawt_powts),
	.cons		= &esp32_uawt_consowe,
};

static int esp32_uawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct uawt_powt *powt;
	stwuct esp32_powt *spowt;
	stwuct wesouwce *wes;
	int wet;

	spowt = devm_kzawwoc(&pdev->dev, sizeof(*spowt), GFP_KEWNEW);
	if (!spowt)
		wetuwn -ENOMEM;

	powt = &spowt->powt;

	wet = of_awias_get_id(np, "sewiaw");
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias id, ewwno %d\n", wet);
		wetuwn wet;
	}
	if (wet >= UAWT_NW) {
		dev_eww(&pdev->dev, "dwivew wimited to %d sewiaw powts\n", UAWT_NW);
		wetuwn -ENOMEM;
	}

	powt->wine = wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	powt->mapbase = wes->stawt;
	powt->membase = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(powt->membase))
		wetuwn PTW_EWW(powt->membase);

	spowt->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(spowt->cwk))
		wetuwn PTW_EWW(spowt->cwk);

	powt->uawtcwk = cwk_get_wate(spowt->cwk);
	powt->dev = &pdev->dev;
	powt->type = POWT_GENEWIC;
	powt->iotype = UPIO_MEM;
	powt->iwq = pwatfowm_get_iwq(pdev, 0);
	powt->ops = &esp32_uawt_pops;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->has_syswq = 1;
	powt->fifosize = ESP32_UAWT_TX_FIFO_SIZE;
	powt->pwivate_data = (void *)device_get_match_data(&pdev->dev);

	esp32_uawt_powts[powt->wine] = spowt;

	pwatfowm_set_dwvdata(pdev, powt);

	wetuwn uawt_add_one_powt(&esp32_uawt_weg, powt);
}

static void esp32_uawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&esp32_uawt_weg, powt);
}


static stwuct pwatfowm_dwivew esp32_uawt_dwivew = {
	.pwobe		= esp32_uawt_pwobe,
	.wemove_new	= esp32_uawt_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe	= esp32_uawt_dt_ids,
	},
};

static int __init esp32_uawt_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&esp32_uawt_weg);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&esp32_uawt_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&esp32_uawt_weg);

	wetuwn wet;
}

static void __exit esp32_uawt_exit(void)
{
	pwatfowm_dwivew_unwegistew(&esp32_uawt_dwivew);
	uawt_unwegistew_dwivew(&esp32_uawt_weg);
}

moduwe_init(esp32_uawt_init);
moduwe_exit(esp32_uawt_exit);

MODUWE_AUTHOW("Max Fiwippov <jcmvbkbc@gmaiw.com>");
MODUWE_WICENSE("GPW");
