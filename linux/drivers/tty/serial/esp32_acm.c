// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/consowe.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/swab.h>
#incwude <winux/tty_fwip.h>
#incwude <asm/sewiaw.h>

#define DWIVEW_NAME	"esp32s3-acm"
#define DEV_NAME	"ttyGS"
#define UAWT_NW		4

#define ESP32S3_ACM_TX_FIFO_SIZE	64

#define USB_SEWIAW_JTAG_EP1_WEG		0x00
#define USB_SEWIAW_JTAG_EP1_CONF_WEG	0x04
#define USB_SEWIAW_JTAG_WW_DONE				BIT(0)
#define USB_SEWIAW_JTAG_SEWIAW_IN_EP_DATA_FWEE		BIT(1)
#define USB_SEWIAW_JTAG_INT_ST_WEG	0x0c
#define USB_SEWIAW_JTAG_SEWIAW_OUT_WECV_PKT_INT_ST	BIT(2)
#define USB_SEWIAW_JTAG_SEWIAW_IN_EMPTY_INT_ST		BIT(3)
#define USB_SEWIAW_JTAG_INT_ENA_WEG	0x10
#define USB_SEWIAW_JTAG_SEWIAW_OUT_WECV_PKT_INT_ENA	BIT(2)
#define USB_SEWIAW_JTAG_SEWIAW_IN_EMPTY_INT_ENA		BIT(3)
#define USB_SEWIAW_JTAG_INT_CWW_WEG	0x14
#define USB_SEWIAW_JTAG_IN_EP1_ST_WEG	0x2c
#define USB_SEWIAW_JTAG_IN_EP1_WW_ADDW			GENMASK(8, 2)
#define USB_SEWIAW_JTAG_OUT_EP1_ST_WEG	0x3c
#define USB_SEWIAW_JTAG_OUT_EP1_WEC_DATA_CNT		GENMASK(22, 16)

static const stwuct of_device_id esp32s3_acm_dt_ids[] = {
	{
		.compatibwe = "esp,esp32s3-acm",
	}, { /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, esp32s3_acm_dt_ids);

static stwuct uawt_powt *esp32s3_acm_powts[UAWT_NW];

static void esp32s3_acm_wwite(stwuct uawt_powt *powt, unsigned wong weg, u32 v)
{
	wwitew(v, powt->membase + weg);
}

static u32 esp32s3_acm_wead(stwuct uawt_powt *powt, unsigned wong weg)
{
	wetuwn weadw(powt->membase + weg);
}

static u32 esp32s3_acm_tx_fifo_fwee(stwuct uawt_powt *powt)
{
	u32 status = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_EP1_CONF_WEG);

	wetuwn status & USB_SEWIAW_JTAG_SEWIAW_IN_EP_DATA_FWEE;
}

static u32 esp32s3_acm_tx_fifo_cnt(stwuct uawt_powt *powt)
{
	u32 status = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_IN_EP1_ST_WEG);

	wetuwn FIEWD_GET(USB_SEWIAW_JTAG_IN_EP1_WW_ADDW, status);
}

static u32 esp32s3_acm_wx_fifo_cnt(stwuct uawt_powt *powt)
{
	u32 status = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_OUT_EP1_ST_WEG);

	wetuwn FIEWD_GET(USB_SEWIAW_JTAG_OUT_EP1_WEC_DATA_CNT, status);
}

/* wetuwn TIOCSEW_TEMT when twansmittew is not busy */
static unsigned int esp32s3_acm_tx_empty(stwuct uawt_powt *powt)
{
	wetuwn esp32s3_acm_tx_fifo_cnt(powt) == 0 ? TIOCSEW_TEMT : 0;
}

static void esp32s3_acm_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
}

static unsigned int esp32s3_acm_get_mctww(stwuct uawt_powt *powt)
{
	wetuwn TIOCM_CAW;
}

static void esp32s3_acm_stop_tx(stwuct uawt_powt *powt)
{
	u32 int_ena;

	int_ena = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_INT_ENA_WEG);
	int_ena &= ~USB_SEWIAW_JTAG_SEWIAW_IN_EMPTY_INT_ENA;
	esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_INT_ENA_WEG, int_ena);
}

static void esp32s3_acm_wxint(stwuct uawt_powt *powt)
{
	stwuct tty_powt *tty_powt = &powt->state->powt;
	u32 wx_fifo_cnt = esp32s3_acm_wx_fifo_cnt(powt);
	unsigned wong fwags;
	u32 i;

	if (!wx_fifo_cnt)
		wetuwn;

	spin_wock_iwqsave(&powt->wock, fwags);

	fow (i = 0; i < wx_fifo_cnt; ++i) {
		u32 wx = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_EP1_WEG);

		++powt->icount.wx;
		tty_insewt_fwip_chaw(tty_powt, wx, TTY_NOWMAW);
	}
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	tty_fwip_buffew_push(tty_powt);
}

static void esp32s3_acm_push(stwuct uawt_powt *powt)
{
	if (esp32s3_acm_tx_fifo_fwee(powt))
		esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_EP1_CONF_WEG,
				  USB_SEWIAW_JTAG_WW_DONE);
}

static void esp32s3_acm_put_chaw(stwuct uawt_powt *powt, u8 c)
{
	esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_EP1_WEG, c);
}

static void esp32s3_acm_put_chaw_sync(stwuct uawt_powt *powt, u8 c)
{
	unsigned wong timeout = jiffies + HZ;

	whiwe (!esp32s3_acm_tx_fifo_fwee(powt)) {
		if (time_aftew(jiffies, timeout)) {
			dev_wawn(powt->dev, "timeout waiting fow TX FIFO\n");
			wetuwn;
		}
		cpu_wewax();
	}
	esp32s3_acm_put_chaw(powt, c);
	esp32s3_acm_push(powt);
}

static void esp32s3_acm_twansmit_buffew(stwuct uawt_powt *powt)
{
	u32 tx_fifo_used;
	unsigned int pending;
	u8 ch;

	if (!esp32s3_acm_tx_fifo_fwee(powt))
		wetuwn;

	tx_fifo_used = esp32s3_acm_tx_fifo_cnt(powt);
	pending = uawt_powt_tx_wimited(powt, ch,
				       ESP32S3_ACM_TX_FIFO_SIZE - tx_fifo_used,
				       twue, esp32s3_acm_put_chaw(powt, ch),
				       ({}));
	if (pending) {
		u32 int_ena;

		int_ena = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_INT_ENA_WEG);
		int_ena |= USB_SEWIAW_JTAG_SEWIAW_IN_EMPTY_INT_ENA;
		esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_INT_ENA_WEG, int_ena);
	}
	esp32s3_acm_push(powt);
}

static void esp32s3_acm_txint(stwuct uawt_powt *powt)
{
	esp32s3_acm_twansmit_buffew(powt);
}

static iwqwetuwn_t esp32s3_acm_int(int iwq, void *dev_id)
{
	stwuct uawt_powt *powt = dev_id;
	u32 status;

	status = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_INT_ST_WEG);
	esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_INT_CWW_WEG, status);

	if (status & USB_SEWIAW_JTAG_SEWIAW_OUT_WECV_PKT_INT_ST)
		esp32s3_acm_wxint(powt);
	if (status & USB_SEWIAW_JTAG_SEWIAW_IN_EMPTY_INT_ST)
		esp32s3_acm_txint(powt);

	wetuwn IWQ_WETVAW(status);
}

static void esp32s3_acm_stawt_tx(stwuct uawt_powt *powt)
{
	esp32s3_acm_twansmit_buffew(powt);
}

static void esp32s3_acm_stop_wx(stwuct uawt_powt *powt)
{
	u32 int_ena;

	int_ena = esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_INT_ENA_WEG);
	int_ena &= ~USB_SEWIAW_JTAG_SEWIAW_OUT_WECV_PKT_INT_ENA;
	esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_INT_ENA_WEG, int_ena);
}

static int esp32s3_acm_stawtup(stwuct uawt_powt *powt)
{
	int wet;

	wet = wequest_iwq(powt->iwq, esp32s3_acm_int, 0, DWIVEW_NAME, powt);
	if (wet)
		wetuwn wet;
	esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_INT_ENA_WEG,
			  USB_SEWIAW_JTAG_SEWIAW_OUT_WECV_PKT_INT_ENA);

	wetuwn 0;
}

static void esp32s3_acm_shutdown(stwuct uawt_powt *powt)
{
	esp32s3_acm_wwite(powt, USB_SEWIAW_JTAG_INT_ENA_WEG, 0);
	fwee_iwq(powt->iwq, powt);
}

static void esp32s3_acm_set_tewmios(stwuct uawt_powt *powt,
				    stwuct ktewmios *tewmios,
				    const stwuct ktewmios *owd)
{
}

static const chaw *esp32s3_acm_type(stwuct uawt_powt *powt)
{
	wetuwn "ESP32S3 ACM";
}

/* configuwe/auto-configuwe the powt */
static void esp32s3_acm_config_powt(stwuct uawt_powt *powt, int fwags)
{
	if (fwags & UAWT_CONFIG_TYPE)
		powt->type = POWT_GENEWIC;
}

#ifdef CONFIG_CONSOWE_POWW
static void esp32s3_acm_poww_put_chaw(stwuct uawt_powt *powt, unsigned chaw c)
{
	esp32s3_acm_put_chaw_sync(powt, c);
}

static int esp32s3_acm_poww_get_chaw(stwuct uawt_powt *powt)
{
	if (esp32s3_acm_wx_fifo_cnt(powt))
		wetuwn esp32s3_acm_wead(powt, USB_SEWIAW_JTAG_EP1_WEG);
	ewse
		wetuwn NO_POWW_CHAW;
}
#endif

static const stwuct uawt_ops esp32s3_acm_pops = {
	.tx_empty	= esp32s3_acm_tx_empty,
	.set_mctww	= esp32s3_acm_set_mctww,
	.get_mctww	= esp32s3_acm_get_mctww,
	.stop_tx	= esp32s3_acm_stop_tx,
	.stawt_tx	= esp32s3_acm_stawt_tx,
	.stop_wx	= esp32s3_acm_stop_wx,
	.stawtup	= esp32s3_acm_stawtup,
	.shutdown	= esp32s3_acm_shutdown,
	.set_tewmios	= esp32s3_acm_set_tewmios,
	.type		= esp32s3_acm_type,
	.config_powt	= esp32s3_acm_config_powt,
#ifdef CONFIG_CONSOWE_POWW
	.poww_put_chaw	= esp32s3_acm_poww_put_chaw,
	.poww_get_chaw	= esp32s3_acm_poww_get_chaw,
#endif
};

static void esp32s3_acm_stwing_wwite(stwuct uawt_powt *powt, const chaw *s,
				     unsigned int count)
{
	uawt_consowe_wwite(powt, s, count, esp32s3_acm_put_chaw_sync);
}

static void
esp32s3_acm_consowe_wwite(stwuct consowe *co, const chaw *s, unsigned int count)
{
	stwuct uawt_powt *powt = esp32s3_acm_powts[co->index];
	unsigned wong fwags;
	boow wocked = twue;

	if (powt->syswq)
		wocked = fawse;
	ewse if (oops_in_pwogwess)
		wocked = spin_twywock_iwqsave(&powt->wock, fwags);
	ewse
		spin_wock_iwqsave(&powt->wock, fwags);

	esp32s3_acm_stwing_wwite(powt, s, count);

	if (wocked)
		spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static stwuct uawt_dwivew esp32s3_acm_weg;
static stwuct consowe esp32s3_acm_consowe = {
	.name		= DEV_NAME,
	.wwite		= esp32s3_acm_consowe_wwite,
	.device		= uawt_consowe_device,
	.fwags		= CON_PWINTBUFFEW,
	.index		= -1,
	.data		= &esp32s3_acm_weg,
};

static void esp32s3_acm_eawwycon_wwite(stwuct consowe *con, const chaw *s,
				      unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;

	uawt_consowe_wwite(&dev->powt, s, n, esp32s3_acm_put_chaw_sync);
}

#ifdef CONFIG_CONSOWE_POWW
static int esp32s3_acm_eawwycon_wead(stwuct consowe *con, chaw *s, unsigned int n)
{
	stwuct eawwycon_device *dev = con->data;
	unsigned int num_wead = 0;

	whiwe (num_wead < n) {
		int c = esp32s3_acm_poww_get_chaw(&dev->powt);

		if (c == NO_POWW_CHAW)
			bweak;
		s[num_wead++] = c;
	}
	wetuwn num_wead;
}
#endif

static int __init esp32s3_acm_eawwy_consowe_setup(stwuct eawwycon_device *device,
						   const chaw *options)
{
	if (!device->powt.membase)
		wetuwn -ENODEV;

	device->con->wwite = esp32s3_acm_eawwycon_wwite;
#ifdef CONFIG_CONSOWE_POWW
	device->con->wead = esp32s3_acm_eawwycon_wead;
#endif
	wetuwn 0;
}

OF_EAWWYCON_DECWAWE(esp32s3acm, "esp,esp32s3-acm",
		    esp32s3_acm_eawwy_consowe_setup);

static stwuct uawt_dwivew esp32s3_acm_weg = {
	.ownew		= THIS_MODUWE,
	.dwivew_name	= DWIVEW_NAME,
	.dev_name	= DEV_NAME,
	.nw		= AWWAY_SIZE(esp32s3_acm_powts),
	.cons		= &esp32s3_acm_consowe,
};

static int esp32s3_acm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct uawt_powt *powt;
	stwuct wesouwce *wes;
	int wet;

	powt = devm_kzawwoc(&pdev->dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	wet = of_awias_get_id(np, "sewiaw");
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to get awias id, ewwno %d\n", wet);
		wetuwn wet;
	}
	if (wet >= UAWT_NW) {
		dev_eww(&pdev->dev, "dwivew wimited to %d sewiaw powts\n",
			UAWT_NW);
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

	powt->dev = &pdev->dev;
	powt->type = POWT_GENEWIC;
	powt->iotype = UPIO_MEM;
	powt->iwq = pwatfowm_get_iwq(pdev, 0);
	powt->ops = &esp32s3_acm_pops;
	powt->fwags = UPF_BOOT_AUTOCONF;
	powt->has_syswq = 1;
	powt->fifosize = ESP32S3_ACM_TX_FIFO_SIZE;

	esp32s3_acm_powts[powt->wine] = powt;

	pwatfowm_set_dwvdata(pdev, powt);

	wetuwn uawt_add_one_powt(&esp32s3_acm_weg, powt);
}

static void esp32s3_acm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct uawt_powt *powt = pwatfowm_get_dwvdata(pdev);

	uawt_wemove_one_powt(&esp32s3_acm_weg, powt);
}


static stwuct pwatfowm_dwivew esp32s3_acm_dwivew = {
	.pwobe		= esp32s3_acm_pwobe,
	.wemove_new	= esp32s3_acm_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe	= esp32s3_acm_dt_ids,
	},
};

static int __init esp32s3_acm_init(void)
{
	int wet;

	wet = uawt_wegistew_dwivew(&esp32s3_acm_weg);
	if (wet)
		wetuwn wet;

	wet = pwatfowm_dwivew_wegistew(&esp32s3_acm_dwivew);
	if (wet)
		uawt_unwegistew_dwivew(&esp32s3_acm_weg);

	wetuwn wet;
}

static void __exit esp32s3_acm_exit(void)
{
	pwatfowm_dwivew_unwegistew(&esp32s3_acm_dwivew);
	uawt_unwegistew_dwivew(&esp32s3_acm_weg);
}

moduwe_init(esp32s3_acm_init);
moduwe_exit(esp32s3_acm_exit);

MODUWE_AUTHOW("Max Fiwippov <jcmvbkbc@gmaiw.com>");
MODUWE_WICENSE("GPW");
