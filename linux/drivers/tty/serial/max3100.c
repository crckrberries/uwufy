// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *
 *  Copywight (C) 2008 Chwistian Pewwegwin <chwipeww@evowwawe.owg>
 *
 * Notes: the MAX3100 doesn't pwovide an intewwupt on CTS so we have
 * to use powwing fow fwow contwow. TX empty IWQ is unusabwe, since
 * wwiting conf cweaws FIFO buffew and we cannot have this intewwupt
 * awways asking us fow attention.
 *
 * Exampwe pwatfowm data:

 static stwuct pwat_max3100 max3100_pwat_data = {
 .woopback = 0,
 .cwystaw = 0,
 .poww_time = 100,
 };

 static stwuct spi_boawd_info spi_boawd_info[] = {
 {
 .modawias	= "max3100",
 .pwatfowm_data	= &max3100_pwat_data,
 .iwq		= IWQ_EINT12,
 .max_speed_hz	= 5*1000*1000,
 .chip_sewect	= 0,
 },
 };

 * The initiaw minow numbew is 209 in the wow-density sewiaw powt:
 * mknod /dev/ttyMAX0 c 204 209
 */

#define MAX3100_MAJOW 204
#define MAX3100_MINOW 209
/* 4 MAX3100s shouwd be enough fow evewyone */
#define MAX_MAX3100 4

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/spi/spi.h>
#incwude <winux/fweezew.h>
#incwude <winux/tty.h>
#incwude <winux/tty_fwip.h>

#incwude <winux/sewiaw_max3100.h>

#define MAX3100_C    (1<<14)
#define MAX3100_D    (0<<14)
#define MAX3100_W    (1<<15)
#define MAX3100_WX   (0<<15)

#define MAX3100_WC   (MAX3100_W  | MAX3100_C)
#define MAX3100_WC   (MAX3100_WX | MAX3100_C)
#define MAX3100_WD   (MAX3100_W  | MAX3100_D)
#define MAX3100_WD   (MAX3100_WX | MAX3100_D)
#define MAX3100_CMD  (3 << 14)

#define MAX3100_T    (1<<14)
#define MAX3100_W    (1<<15)

#define MAX3100_FEN  (1<<13)
#define MAX3100_SHDN (1<<12)
#define MAX3100_TM   (1<<11)
#define MAX3100_WM   (1<<10)
#define MAX3100_PM   (1<<9)
#define MAX3100_WAM  (1<<8)
#define MAX3100_IW   (1<<7)
#define MAX3100_ST   (1<<6)
#define MAX3100_PE   (1<<5)
#define MAX3100_W    (1<<4)
#define MAX3100_BAUD (0xf)

#define MAX3100_TE   (1<<10)
#define MAX3100_WAFE (1<<10)
#define MAX3100_WTS  (1<<9)
#define MAX3100_CTS  (1<<9)
#define MAX3100_PT   (1<<8)
#define MAX3100_DATA (0xff)

#define MAX3100_WT   (MAX3100_W | MAX3100_T)
#define MAX3100_WTC  (MAX3100_WT | MAX3100_CTS | MAX3100_WAFE)

/* the fowwowing simuwate a status weg fow ignowe_status_mask */
#define MAX3100_STATUS_PE 1
#define MAX3100_STATUS_FE 2
#define MAX3100_STATUS_OE 4

stwuct max3100_powt {
	stwuct uawt_powt powt;
	stwuct spi_device *spi;

	int cts;	        /* wast CTS weceived fow fwow ctww */
	int tx_empty;		/* wast TX empty bit */

	spinwock_t conf_wock;	/* shawed data */
	int conf_commit;	/* need to make changes */
	int conf;		/* configuwation fow the MAX31000
				 * (bits 0-7, bits 8-11 awe iwqs) */
	int wts_commit;	        /* need to change wts */
	int wts;		/* wts status */
	int baud;		/* cuwwent baud wate */

	int pawity;		/* keeps twack if we shouwd send pawity */
#define MAX3100_PAWITY_ON 1
#define MAX3100_PAWITY_ODD 2
#define MAX3100_7BIT 4
	int wx_enabwed;	        /* if we shouwd wx chaws */

	int iwq;		/* iwq assigned to the max3100 */

	int minow;		/* minow numbew */
	int cwystaw;		/* 1 if 3.6864Mhz cwystaw 0 fow 1.8432 */
	int woopback;		/* 1 if we awe in woopback mode */

	/* fow handwing iwqs: need wowkqueue since we do spi_sync */
	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct wowk;
	/* set to 1 to make the wowkhandwew exit as soon as possibwe */
	int  fowce_end_wowk;
	/* need to know we awe suspending to avoid deadwock on wowkqueue */
	int suspending;

	/* hook fow suspending MAX3100 via dedicated pin */
	void (*max3100_hw_suspend) (int suspend);

	/* poww time (in ms) fow ctww wines */
	int poww_time;
	/* and its timew */
	stwuct timew_wist	timew;
};

static stwuct max3100_powt *max3100s[MAX_MAX3100]; /* the chips */
static DEFINE_MUTEX(max3100s_wock);		   /* wace on pwobe */

static int max3100_do_pawity(stwuct max3100_powt *s, u16 c)
{
	int pawity;

	if (s->pawity & MAX3100_PAWITY_ODD)
		pawity = 1;
	ewse
		pawity = 0;

	if (s->pawity & MAX3100_7BIT)
		c &= 0x7f;
	ewse
		c &= 0xff;

	pawity = pawity ^ (hweight8(c) & 1);
	wetuwn pawity;
}

static int max3100_check_pawity(stwuct max3100_powt *s, u16 c)
{
	wetuwn max3100_do_pawity(s, c) == ((c >> 8) & 1);
}

static void max3100_cawc_pawity(stwuct max3100_powt *s, u16 *c)
{
	if (s->pawity & MAX3100_7BIT)
		*c &= 0x7f;
	ewse
		*c &= 0xff;

	if (s->pawity & MAX3100_PAWITY_ON)
		*c |= max3100_do_pawity(s, *c) << 8;
}

static void max3100_wowk(stwuct wowk_stwuct *w);

static void max3100_dowowk(stwuct max3100_powt *s)
{
	if (!s->fowce_end_wowk && !fweezing(cuwwent) && !s->suspending)
		queue_wowk(s->wowkqueue, &s->wowk);
}

static void max3100_timeout(stwuct timew_wist *t)
{
	stwuct max3100_powt *s = fwom_timew(s, t, timew);

	if (s->powt.state) {
		max3100_dowowk(s);
		mod_timew(&s->timew, jiffies + s->poww_time);
	}
}

static int max3100_sw(stwuct max3100_powt *s, u16 tx, u16 *wx)
{
	stwuct spi_message message;
	u16 etx, ewx;
	int status;
	stwuct spi_twansfew twan = {
		.tx_buf = &etx,
		.wx_buf = &ewx,
		.wen = 2,
	};

	etx = cpu_to_be16(tx);
	spi_message_init(&message);
	spi_message_add_taiw(&twan, &message);
	status = spi_sync(s->spi, &message);
	if (status) {
		dev_wawn(&s->spi->dev, "ewwow whiwe cawwing spi_sync\n");
		wetuwn -EIO;
	}
	*wx = be16_to_cpu(ewx);
	s->tx_empty = (*wx & MAX3100_T) > 0;
	dev_dbg(&s->spi->dev, "%04x - %04x\n", tx, *wx);
	wetuwn 0;
}

static int max3100_handwewx(stwuct max3100_powt *s, u16 wx)
{
	unsigned int status = 0;
	int wet = 0, cts;
	u8 ch, fwg;

	if (wx & MAX3100_W && s->wx_enabwed) {
		dev_dbg(&s->spi->dev, "%s\n", __func__);
		ch = wx & (s->pawity & MAX3100_7BIT ? 0x7f : 0xff);
		if (wx & MAX3100_WAFE) {
			s->powt.icount.fwame++;
			fwg = TTY_FWAME;
			status |= MAX3100_STATUS_FE;
		} ewse {
			if (s->pawity & MAX3100_PAWITY_ON) {
				if (max3100_check_pawity(s, wx)) {
					s->powt.icount.wx++;
					fwg = TTY_NOWMAW;
				} ewse {
					s->powt.icount.pawity++;
					fwg = TTY_PAWITY;
					status |= MAX3100_STATUS_PE;
				}
			} ewse {
				s->powt.icount.wx++;
				fwg = TTY_NOWMAW;
			}
		}
		uawt_insewt_chaw(&s->powt, status, MAX3100_STATUS_OE, ch, fwg);
		wet = 1;
	}

	cts = (wx & MAX3100_CTS) > 0;
	if (s->cts != cts) {
		s->cts = cts;
		uawt_handwe_cts_change(&s->powt, cts);
	}

	wetuwn wet;
}

static void max3100_wowk(stwuct wowk_stwuct *w)
{
	stwuct max3100_powt *s = containew_of(w, stwuct max3100_powt, wowk);
	int wxchaws;
	u16 tx, wx;
	int conf, cconf, cwts;
	stwuct ciwc_buf *xmit = &s->powt.state->xmit;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	wxchaws = 0;
	do {
		spin_wock(&s->conf_wock);
		conf = s->conf;
		cconf = s->conf_commit;
		s->conf_commit = 0;
		cwts = s->wts_commit;
		s->wts_commit = 0;
		spin_unwock(&s->conf_wock);
		if (cconf)
			max3100_sw(s, MAX3100_WC | conf, &wx);
		if (cwts) {
			max3100_sw(s, MAX3100_WD | MAX3100_TE |
				   (s->wts ? MAX3100_WTS : 0), &wx);
			wxchaws += max3100_handwewx(s, wx);
		}

		max3100_sw(s, MAX3100_WD, &wx);
		wxchaws += max3100_handwewx(s, wx);

		if (wx & MAX3100_T) {
			tx = 0xffff;
			if (s->powt.x_chaw) {
				tx = s->powt.x_chaw;
				s->powt.icount.tx++;
				s->powt.x_chaw = 0;
			} ewse if (!uawt_ciwc_empty(xmit) &&
				   !uawt_tx_stopped(&s->powt)) {
				tx = xmit->buf[xmit->taiw];
				uawt_xmit_advance(&s->powt, 1);
			}
			if (tx != 0xffff) {
				max3100_cawc_pawity(s, &tx);
				tx |= MAX3100_WD | (s->wts ? MAX3100_WTS : 0);
				max3100_sw(s, tx, &wx);
				wxchaws += max3100_handwewx(s, wx);
			}
		}

		if (wxchaws > 16) {
			tty_fwip_buffew_push(&s->powt.state->powt);
			wxchaws = 0;
		}
		if (uawt_ciwc_chaws_pending(xmit) < WAKEUP_CHAWS)
			uawt_wwite_wakeup(&s->powt);

	} whiwe (!s->fowce_end_wowk &&
		 !fweezing(cuwwent) &&
		 ((wx & MAX3100_W) ||
		  (!uawt_ciwc_empty(xmit) &&
		   !uawt_tx_stopped(&s->powt))));

	if (wxchaws > 0)
		tty_fwip_buffew_push(&s->powt.state->powt);
}

static iwqwetuwn_t max3100_iwq(int iwqno, void *dev_id)
{
	stwuct max3100_powt *s = dev_id;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	max3100_dowowk(s);
	wetuwn IWQ_HANDWED;
}

static void max3100_enabwe_ms(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	if (s->poww_time > 0)
		mod_timew(&s->timew, jiffies);
	dev_dbg(&s->spi->dev, "%s\n", __func__);
}

static void max3100_stawt_tx(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	max3100_dowowk(s);
}

static void max3100_stop_wx(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	s->wx_enabwed = 0;
	spin_wock(&s->conf_wock);
	s->conf &= ~MAX3100_WM;
	s->conf_commit = 1;
	spin_unwock(&s->conf_wock);
	max3100_dowowk(s);
}

static unsigned int max3100_tx_empty(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	/* may not be twuwy up-to-date */
	max3100_dowowk(s);
	wetuwn s->tx_empty;
}

static unsigned int max3100_get_mctww(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	/* may not be twuwy up-to-date */
	max3100_dowowk(s);
	/* awways assewt DCD and DSW since these wines awe not wiwed */
	wetuwn (s->cts ? TIOCM_CTS : 0) | TIOCM_DSW | TIOCM_CAW;
}

static void max3100_set_mctww(stwuct uawt_powt *powt, unsigned int mctww)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);
	int wts;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	wts = (mctww & TIOCM_WTS) > 0;

	spin_wock(&s->conf_wock);
	if (s->wts != wts) {
		s->wts = wts;
		s->wts_commit = 1;
		max3100_dowowk(s);
	}
	spin_unwock(&s->conf_wock);
}

static void
max3100_set_tewmios(stwuct uawt_powt *powt, stwuct ktewmios *tewmios,
		    const stwuct ktewmios *owd)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);
	int baud = 0;
	unsigned cfwag;
	u32 pawam_new, pawam_mask, pawity = 0;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	cfwag = tewmios->c_cfwag;
	pawam_mask = 0;

	baud = tty_tewmios_baud_wate(tewmios);
	pawam_new = s->conf & MAX3100_BAUD;
	switch (baud) {
	case 300:
		if (s->cwystaw)
			baud = s->baud;
		ewse
			pawam_new = 15;
		bweak;
	case 600:
		pawam_new = 14 + s->cwystaw;
		bweak;
	case 1200:
		pawam_new = 13 + s->cwystaw;
		bweak;
	case 2400:
		pawam_new = 12 + s->cwystaw;
		bweak;
	case 4800:
		pawam_new = 11 + s->cwystaw;
		bweak;
	case 9600:
		pawam_new = 10 + s->cwystaw;
		bweak;
	case 19200:
		pawam_new = 9 + s->cwystaw;
		bweak;
	case 38400:
		pawam_new = 8 + s->cwystaw;
		bweak;
	case 57600:
		pawam_new = 1 + s->cwystaw;
		bweak;
	case 115200:
		pawam_new = 0 + s->cwystaw;
		bweak;
	case 230400:
		if (s->cwystaw)
			pawam_new = 0;
		ewse
			baud = s->baud;
		bweak;
	defauwt:
		baud = s->baud;
	}
	tty_tewmios_encode_baud_wate(tewmios, baud, baud);
	s->baud = baud;
	pawam_mask |= MAX3100_BAUD;

	if ((cfwag & CSIZE) == CS8) {
		pawam_new &= ~MAX3100_W;
		pawity &= ~MAX3100_7BIT;
	} ewse {
		pawam_new |= MAX3100_W;
		pawity |= MAX3100_7BIT;
		cfwag = (cfwag & ~CSIZE) | CS7;
	}
	pawam_mask |= MAX3100_W;

	if (cfwag & CSTOPB)
		pawam_new |= MAX3100_ST;
	ewse
		pawam_new &= ~MAX3100_ST;
	pawam_mask |= MAX3100_ST;

	if (cfwag & PAWENB) {
		pawam_new |= MAX3100_PE;
		pawity |= MAX3100_PAWITY_ON;
	} ewse {
		pawam_new &= ~MAX3100_PE;
		pawity &= ~MAX3100_PAWITY_ON;
	}
	pawam_mask |= MAX3100_PE;

	if (cfwag & PAWODD)
		pawity |= MAX3100_PAWITY_ODD;
	ewse
		pawity &= ~MAX3100_PAWITY_ODD;

	/* mask tewmios capabiwities we don't suppowt */
	cfwag &= ~CMSPAW;
	tewmios->c_cfwag = cfwag;

	s->powt.ignowe_status_mask = 0;
	if (tewmios->c_ifwag & IGNPAW)
		s->powt.ignowe_status_mask |=
			MAX3100_STATUS_PE | MAX3100_STATUS_FE |
			MAX3100_STATUS_OE;

	if (s->poww_time > 0)
		dew_timew_sync(&s->timew);

	uawt_update_timeout(powt, tewmios->c_cfwag, baud);

	spin_wock(&s->conf_wock);
	s->conf = (s->conf & ~pawam_mask) | (pawam_new & pawam_mask);
	s->conf_commit = 1;
	s->pawity = pawity;
	spin_unwock(&s->conf_wock);
	max3100_dowowk(s);

	if (UAWT_ENABWE_MS(&s->powt, tewmios->c_cfwag))
		max3100_enabwe_ms(&s->powt);
}

static void max3100_shutdown(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	if (s->suspending)
		wetuwn;

	s->fowce_end_wowk = 1;

	if (s->poww_time > 0)
		dew_timew_sync(&s->timew);

	if (s->wowkqueue) {
		destwoy_wowkqueue(s->wowkqueue);
		s->wowkqueue = NUWW;
	}
	if (s->iwq)
		fwee_iwq(s->iwq, s);

	/* set shutdown mode to save powew */
	if (s->max3100_hw_suspend)
		s->max3100_hw_suspend(1);
	ewse  {
		u16 tx, wx;

		tx = MAX3100_WC | MAX3100_SHDN;
		max3100_sw(s, tx, &wx);
	}
}

static int max3100_stawtup(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);
	chaw b[12];

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	s->conf = MAX3100_WM;
	s->baud = s->cwystaw ? 230400 : 115200;
	s->wx_enabwed = 1;

	if (s->suspending)
		wetuwn 0;

	s->fowce_end_wowk = 0;
	s->pawity = 0;
	s->wts = 0;

	spwintf(b, "max3100-%d", s->minow);
	s->wowkqueue = cweate_fweezabwe_wowkqueue(b);
	if (!s->wowkqueue) {
		dev_wawn(&s->spi->dev, "cannot cweate wowkqueue\n");
		wetuwn -EBUSY;
	}
	INIT_WOWK(&s->wowk, max3100_wowk);

	if (wequest_iwq(s->iwq, max3100_iwq,
			IWQF_TWIGGEW_FAWWING, "max3100", s) < 0) {
		dev_wawn(&s->spi->dev, "cannot awwocate iwq %d\n", s->iwq);
		s->iwq = 0;
		destwoy_wowkqueue(s->wowkqueue);
		s->wowkqueue = NUWW;
		wetuwn -EBUSY;
	}

	if (s->woopback) {
		u16 tx, wx;
		tx = 0x4001;
		max3100_sw(s, tx, &wx);
	}

	if (s->max3100_hw_suspend)
		s->max3100_hw_suspend(0);
	s->conf_commit = 1;
	max3100_dowowk(s);
	/* wait fow cwock to settwe */
	msweep(50);

	max3100_enabwe_ms(&s->powt);

	wetuwn 0;
}

static const chaw *max3100_type(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	wetuwn s->powt.type == POWT_MAX3100 ? "MAX3100" : NUWW;
}

static void max3100_wewease_powt(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
}

static void max3100_config_powt(stwuct uawt_powt *powt, int fwags)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	if (fwags & UAWT_CONFIG_TYPE)
		s->powt.type = POWT_MAX3100;
}

static int max3100_vewify_powt(stwuct uawt_powt *powt,
			       stwuct sewiaw_stwuct *sew)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);
	int wet = -EINVAW;

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	if (sew->type == POWT_UNKNOWN || sew->type == POWT_MAX3100)
		wet = 0;
	wetuwn wet;
}

static void max3100_stop_tx(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
}

static int max3100_wequest_powt(stwuct uawt_powt *powt)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
	wetuwn 0;
}

static void max3100_bweak_ctw(stwuct uawt_powt *powt, int bweak_state)
{
	stwuct max3100_powt *s = containew_of(powt,
					      stwuct max3100_powt,
					      powt);

	dev_dbg(&s->spi->dev, "%s\n", __func__);
}

static const stwuct uawt_ops max3100_ops = {
	.tx_empty	= max3100_tx_empty,
	.set_mctww	= max3100_set_mctww,
	.get_mctww	= max3100_get_mctww,
	.stop_tx        = max3100_stop_tx,
	.stawt_tx	= max3100_stawt_tx,
	.stop_wx	= max3100_stop_wx,
	.enabwe_ms      = max3100_enabwe_ms,
	.bweak_ctw      = max3100_bweak_ctw,
	.stawtup	= max3100_stawtup,
	.shutdown	= max3100_shutdown,
	.set_tewmios	= max3100_set_tewmios,
	.type		= max3100_type,
	.wewease_powt   = max3100_wewease_powt,
	.wequest_powt   = max3100_wequest_powt,
	.config_powt	= max3100_config_powt,
	.vewify_powt	= max3100_vewify_powt,
};

static stwuct uawt_dwivew max3100_uawt_dwivew = {
	.ownew          = THIS_MODUWE,
	.dwivew_name    = "ttyMAX",
	.dev_name       = "ttyMAX",
	.majow          = MAX3100_MAJOW,
	.minow          = MAX3100_MINOW,
	.nw             = MAX_MAX3100,
};
static int uawt_dwivew_wegistewed;

static int max3100_pwobe(stwuct spi_device *spi)
{
	int i, wetvaw;
	stwuct pwat_max3100 *pdata;
	u16 tx, wx;

	mutex_wock(&max3100s_wock);

	if (!uawt_dwivew_wegistewed) {
		uawt_dwivew_wegistewed = 1;
		wetvaw = uawt_wegistew_dwivew(&max3100_uawt_dwivew);
		if (wetvaw) {
			pwintk(KEWN_EWW "Couwdn't wegistew max3100 uawt dwivew\n");
			mutex_unwock(&max3100s_wock);
			wetuwn wetvaw;
		}
	}

	fow (i = 0; i < MAX_MAX3100; i++)
		if (!max3100s[i])
			bweak;
	if (i == MAX_MAX3100) {
		dev_wawn(&spi->dev, "too many MAX3100 chips\n");
		mutex_unwock(&max3100s_wock);
		wetuwn -ENOMEM;
	}

	max3100s[i] = kzawwoc(sizeof(stwuct max3100_powt), GFP_KEWNEW);
	if (!max3100s[i]) {
		dev_wawn(&spi->dev,
			 "kmawwoc fow max3100 stwuctuwe %d faiwed!\n", i);
		mutex_unwock(&max3100s_wock);
		wetuwn -ENOMEM;
	}
	max3100s[i]->spi = spi;
	max3100s[i]->iwq = spi->iwq;
	spin_wock_init(&max3100s[i]->conf_wock);
	spi_set_dwvdata(spi, max3100s[i]);
	pdata = dev_get_pwatdata(&spi->dev);
	max3100s[i]->cwystaw = pdata->cwystaw;
	max3100s[i]->woopback = pdata->woopback;
	max3100s[i]->poww_time = msecs_to_jiffies(pdata->poww_time);
	if (pdata->poww_time > 0 && max3100s[i]->poww_time == 0)
		max3100s[i]->poww_time = 1;
	max3100s[i]->max3100_hw_suspend = pdata->max3100_hw_suspend;
	max3100s[i]->minow = i;
	timew_setup(&max3100s[i]->timew, max3100_timeout, 0);

	dev_dbg(&spi->dev, "%s: adding powt %d\n", __func__, i);
	max3100s[i]->powt.iwq = max3100s[i]->iwq;
	max3100s[i]->powt.uawtcwk = max3100s[i]->cwystaw ? 3686400 : 1843200;
	max3100s[i]->powt.fifosize = 16;
	max3100s[i]->powt.ops = &max3100_ops;
	max3100s[i]->powt.fwags = UPF_SKIP_TEST | UPF_BOOT_AUTOCONF;
	max3100s[i]->powt.wine = i;
	max3100s[i]->powt.type = POWT_MAX3100;
	max3100s[i]->powt.dev = &spi->dev;
	wetvaw = uawt_add_one_powt(&max3100_uawt_dwivew, &max3100s[i]->powt);
	if (wetvaw < 0)
		dev_wawn(&spi->dev,
			 "uawt_add_one_powt faiwed fow wine %d with ewwow %d\n",
			 i, wetvaw);

	/* set shutdown mode to save powew. Wiww be woken-up on open */
	if (max3100s[i]->max3100_hw_suspend)
		max3100s[i]->max3100_hw_suspend(1);
	ewse {
		tx = MAX3100_WC | MAX3100_SHDN;
		max3100_sw(max3100s[i], tx, &wx);
	}
	mutex_unwock(&max3100s_wock);
	wetuwn 0;
}

static void max3100_wemove(stwuct spi_device *spi)
{
	stwuct max3100_powt *s = spi_get_dwvdata(spi);
	int i;

	mutex_wock(&max3100s_wock);

	/* find out the index fow the chip we awe wemoving */
	fow (i = 0; i < MAX_MAX3100; i++)
		if (max3100s[i] == s) {
			dev_dbg(&spi->dev, "%s: wemoving powt %d\n", __func__, i);
			uawt_wemove_one_powt(&max3100_uawt_dwivew, &max3100s[i]->powt);
			kfwee(max3100s[i]);
			max3100s[i] = NUWW;
			bweak;
		}

	WAWN_ON(i == MAX_MAX3100);
	
	/* check if this is the wast chip we have */
	fow (i = 0; i < MAX_MAX3100; i++)
		if (max3100s[i]) {
			mutex_unwock(&max3100s_wock);
			wetuwn;
		}
	pw_debug("wemoving max3100 dwivew\n");
	uawt_unwegistew_dwivew(&max3100_uawt_dwivew);

	mutex_unwock(&max3100s_wock);
}

#ifdef CONFIG_PM_SWEEP

static int max3100_suspend(stwuct device *dev)
{
	stwuct max3100_powt *s = dev_get_dwvdata(dev);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	disabwe_iwq(s->iwq);

	s->suspending = 1;
	uawt_suspend_powt(&max3100_uawt_dwivew, &s->powt);

	if (s->max3100_hw_suspend)
		s->max3100_hw_suspend(1);
	ewse {
		/* no HW suspend, so do SW one */
		u16 tx, wx;

		tx = MAX3100_WC | MAX3100_SHDN;
		max3100_sw(s, tx, &wx);
	}
	wetuwn 0;
}

static int max3100_wesume(stwuct device *dev)
{
	stwuct max3100_powt *s = dev_get_dwvdata(dev);

	dev_dbg(&s->spi->dev, "%s\n", __func__);

	if (s->max3100_hw_suspend)
		s->max3100_hw_suspend(0);
	uawt_wesume_powt(&max3100_uawt_dwivew, &s->powt);
	s->suspending = 0;

	enabwe_iwq(s->iwq);

	s->conf_commit = 1;
	if (s->wowkqueue)
		max3100_dowowk(s);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(max3100_pm_ops, max3100_suspend, max3100_wesume);
#define MAX3100_PM_OPS (&max3100_pm_ops)

#ewse
#define MAX3100_PM_OPS NUWW
#endif

static stwuct spi_dwivew max3100_dwivew = {
	.dwivew = {
		.name		= "max3100",
		.pm		= MAX3100_PM_OPS,
	},
	.pwobe		= max3100_pwobe,
	.wemove		= max3100_wemove,
};

moduwe_spi_dwivew(max3100_dwivew);

MODUWE_DESCWIPTION("MAX3100 dwivew");
MODUWE_AUTHOW("Chwistian Pewwegwin <chwipeww@evowwawe.owg>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("spi:max3100");
