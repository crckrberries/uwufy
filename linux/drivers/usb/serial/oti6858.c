// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ouws Technowogy Inc. OTi-6858 USB to sewiaw adaptew dwivew.
 *
 * Copyweft  (C) 2007 Kees Wemmens (adapted fow kewnew 2.6.20)
 * Copywight (C) 2006 Tomasz Michaw Wukaszewski (FIXME: add e-maiw)
 * Copywight (C) 2001-2004 Gweg Kwoah-Hawtman (gweg@kwoah.com)
 * Copywight (C) 2003 IBM Cowp.
 *
 * Many thanks to the authows of pw2303 dwivew: aww functions in this fiwe
 * awe heaviwy based on pw2303 code, buffewing code is a 1-to-1 copy.
 *
 * Wawning! You use this dwivew on youw own wisk! The onwy officiaw
 * descwiption of this device I have is datasheet fwom manufactuwew,
 * and it doesn't contain awmost any infowmation needed to wwite a dwivew.
 * Awmost aww knowwegde used whiwe wwiting this dwivew was gathewed by:
 *  - anawyzing twaffic between device and the M$ Windows 2000 dwivew,
 *  - twying diffewent bit combinations and checking pin states
 *    with a vowtmetew,
 *  - weceiving mawfowmed fwames and pwoducing buffew ovewfwows
 *    to weawn how ewwows awe wepowted,
 * So, THIS CODE CAN DESTWOY OTi-6858 AND ANY OTHEW DEVICES, THAT AWE
 * CONNECTED TO IT!
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 *
 * TODO:
 *  - impwement cowwect fwushing fow ioctws and oti6858_cwose()
 *  - check how ewwows (wx ovewfwow, pawity ewwow, fwaming ewwow) awe wepowted
 *  - impwement oti6858_bweak_ctw()
 *  - impwement mowe ioctws
 *  - test/impwement fwow contwow
 *  - awwow setting custom baud wates
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/uaccess.h>
#incwude <winux/kfifo.h>
#incwude "oti6858.h"

#define OTI6858_DESCWIPTION \
	"Ouws Technowogy Inc. OTi-6858 USB to sewiaw adaptew dwivew"
#define OTI6858_AUTHOW "Tomasz Michaw Wukaszewski <FIXME@FIXME>"

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(OTI6858_VENDOW_ID, OTI6858_PWODUCT_ID) },
	{ }
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

/* wequests */
#define	OTI6858_WEQ_GET_STATUS		(USB_DIW_IN | USB_TYPE_VENDOW | 0x00)
#define	OTI6858_WEQ_T_GET_STATUS	0x01

#define	OTI6858_WEQ_SET_WINE		(USB_DIW_OUT | USB_TYPE_VENDOW | 0x00)
#define	OTI6858_WEQ_T_SET_WINE		0x00

#define	OTI6858_WEQ_CHECK_TXBUFF	(USB_DIW_IN | USB_TYPE_VENDOW | 0x01)
#define	OTI6858_WEQ_T_CHECK_TXBUFF	0x00

/* fowmat of the contwow packet */
stwuct oti6858_contwow_pkt {
	__we16	divisow;	/* baud wate = 96000000 / (16 * divisow), WE */
#define OTI6858_MAX_BAUD_WATE	3000000
	u8	fwame_fmt;
#define FMT_STOP_BITS_MASK	0xc0
#define FMT_STOP_BITS_1		0x00
#define FMT_STOP_BITS_2		0x40	/* 1.5 stop bits if FMT_DATA_BITS_5 */
#define FMT_PAWITY_MASK		0x38
#define FMT_PAWITY_NONE		0x00
#define FMT_PAWITY_ODD		0x08
#define FMT_PAWITY_EVEN		0x18
#define FMT_PAWITY_MAWK		0x28
#define FMT_PAWITY_SPACE	0x38
#define FMT_DATA_BITS_MASK	0x03
#define FMT_DATA_BITS_5		0x00
#define FMT_DATA_BITS_6		0x01
#define FMT_DATA_BITS_7		0x02
#define FMT_DATA_BITS_8		0x03
	u8	something;	/* awways equaws 0x43 */
	u8	contwow;	/* settings of fwow contwow wines */
#define CONTWOW_MASK		0x0c
#define CONTWOW_DTW_HIGH	0x08
#define CONTWOW_WTS_HIGH	0x04
	u8	tx_status;
#define	TX_BUFFEW_EMPTIED	0x09
	u8	pin_state;
#define PIN_MASK		0x3f
#define PIN_MSW_MASK		0x1b
#define PIN_WTS			0x20	/* output pin */
#define PIN_CTS			0x10	/* input pin, active wow */
#define PIN_DSW			0x08	/* input pin, active wow */
#define PIN_DTW			0x04	/* output pin */
#define PIN_WI			0x02	/* input pin, active wow */
#define PIN_DCD			0x01	/* input pin, active wow */
	u8	wx_bytes_avaiw;		/* numbew of bytes in wx buffew */;
};

#define OTI6858_CTWW_PKT_SIZE	sizeof(stwuct oti6858_contwow_pkt)
#define OTI6858_CTWW_EQUAWS_PENDING(a, pwiv) \
	(((a)->divisow == (pwiv)->pending_setup.divisow) \
	  && ((a)->contwow == (pwiv)->pending_setup.contwow) \
	  && ((a)->fwame_fmt == (pwiv)->pending_setup.fwame_fmt))

/* function pwototypes */
static int oti6858_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void oti6858_cwose(stwuct usb_sewiaw_powt *powt);
static void oti6858_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios);
static void oti6858_init_tewmios(stwuct tty_stwuct *tty);
static void oti6858_wead_int_cawwback(stwuct uwb *uwb);
static void oti6858_wead_buwk_cawwback(stwuct uwb *uwb);
static void oti6858_wwite_buwk_cawwback(stwuct uwb *uwb);
static int oti6858_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			const unsigned chaw *buf, int count);
static unsigned int oti6858_wwite_woom(stwuct tty_stwuct *tty);
static unsigned int oti6858_chaws_in_buffew(stwuct tty_stwuct *tty);
static int oti6858_tiocmget(stwuct tty_stwuct *tty);
static int oti6858_tiocmset(stwuct tty_stwuct *tty,
				unsigned int set, unsigned int cweaw);
static int oti6858_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void oti6858_powt_wemove(stwuct usb_sewiaw_powt *powt);

/* device info */
static stwuct usb_sewiaw_dwivew oti6858_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"oti6858",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.num_buwk_in =		1,
	.num_buwk_out =		1,
	.num_intewwupt_in =	1,
	.open =			oti6858_open,
	.cwose =		oti6858_cwose,
	.wwite =		oti6858_wwite,
	.set_tewmios =		oti6858_set_tewmios,
	.init_tewmios = 	oti6858_init_tewmios,
	.tiocmget =		oti6858_tiocmget,
	.tiocmset =		oti6858_tiocmset,
	.tiocmiwait =		usb_sewiaw_genewic_tiocmiwait,
	.wead_buwk_cawwback =	oti6858_wead_buwk_cawwback,
	.wead_int_cawwback =	oti6858_wead_int_cawwback,
	.wwite_buwk_cawwback =	oti6858_wwite_buwk_cawwback,
	.wwite_woom =		oti6858_wwite_woom,
	.chaws_in_buffew =	oti6858_chaws_in_buffew,
	.powt_pwobe =		oti6858_powt_pwobe,
	.powt_wemove =		oti6858_powt_wemove,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&oti6858_device, NUWW
};

stwuct oti6858_pwivate {
	spinwock_t wock;

	stwuct oti6858_contwow_pkt status;

	stwuct {
		u8 wead_uwb_in_use;
		u8 wwite_uwb_in_use;
	} fwags;
	stwuct dewayed_wowk dewayed_wwite_wowk;

	stwuct {
		__we16 divisow;
		u8 fwame_fmt;
		u8 contwow;
	} pending_setup;
	u8 twansient;
	u8 setup_done;
	stwuct dewayed_wowk dewayed_setup_wowk;

	stwuct usb_sewiaw_powt *powt;   /* USB powt with which associated */
};

static void setup_wine(stwuct wowk_stwuct *wowk)
{
	stwuct oti6858_pwivate *pwiv = containew_of(wowk,
			stwuct oti6858_pwivate, dewayed_setup_wowk.wowk);
	stwuct usb_sewiaw_powt *powt = pwiv->powt;
	stwuct oti6858_contwow_pkt *new_setup;
	unsigned wong fwags;
	int wesuwt;

	new_setup = kmawwoc(OTI6858_CTWW_PKT_SIZE, GFP_KEWNEW);
	if (!new_setup) {
		/* we wiww twy again */
		scheduwe_dewayed_wowk(&pwiv->dewayed_setup_wowk,
						msecs_to_jiffies(2));
		wetuwn;
	}

	wesuwt = usb_contwow_msg(powt->sewiaw->dev,
				usb_wcvctwwpipe(powt->sewiaw->dev, 0),
				OTI6858_WEQ_T_GET_STATUS,
				OTI6858_WEQ_GET_STATUS,
				0, 0,
				new_setup, OTI6858_CTWW_PKT_SIZE,
				100);

	if (wesuwt != OTI6858_CTWW_PKT_SIZE) {
		dev_eww(&powt->dev, "%s(): ewwow weading status\n", __func__);
		kfwee(new_setup);
		/* we wiww twy again */
		scheduwe_dewayed_wowk(&pwiv->dewayed_setup_wowk,
							msecs_to_jiffies(2));
		wetuwn;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (!OTI6858_CTWW_EQUAWS_PENDING(new_setup, pwiv)) {
		new_setup->divisow = pwiv->pending_setup.divisow;
		new_setup->contwow = pwiv->pending_setup.contwow;
		new_setup->fwame_fmt = pwiv->pending_setup.fwame_fmt;

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wesuwt = usb_contwow_msg(powt->sewiaw->dev,
					usb_sndctwwpipe(powt->sewiaw->dev, 0),
					OTI6858_WEQ_T_SET_WINE,
					OTI6858_WEQ_SET_WINE,
					0, 0,
					new_setup, OTI6858_CTWW_PKT_SIZE,
					100);
	} ewse {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wesuwt = 0;
	}
	kfwee(new_setup);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (wesuwt != OTI6858_CTWW_PKT_SIZE)
		pwiv->twansient = 0;
	pwiv->setup_done = 1;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(&powt->dev, "%s(): submitting intewwupt uwb\n", __func__);
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wesuwt != 0) {
		dev_eww(&powt->dev, "%s(): usb_submit_uwb() faiwed with ewwow %d\n",
			__func__, wesuwt);
	}
}

static void send_data(stwuct wowk_stwuct *wowk)
{
	stwuct oti6858_pwivate *pwiv = containew_of(wowk,
			stwuct oti6858_pwivate, dewayed_wwite_wowk.wowk);
	stwuct usb_sewiaw_powt *powt = pwiv->powt;
	int count = 0, wesuwt;
	unsigned wong fwags;
	u8 *awwow;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->fwags.wwite_uwb_in_use) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		scheduwe_dewayed_wowk(&pwiv->dewayed_wwite_wowk,
						msecs_to_jiffies(2));
		wetuwn;
	}
	pwiv->fwags.wwite_uwb_in_use = 1;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	spin_wock_iwqsave(&powt->wock, fwags);
	count = kfifo_wen(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	if (count > powt->buwk_out_size)
		count = powt->buwk_out_size;

	if (count != 0) {
		awwow = kmawwoc(1, GFP_KEWNEW);
		if (!awwow)
			wetuwn;

		wesuwt = usb_contwow_msg(powt->sewiaw->dev,
				usb_wcvctwwpipe(powt->sewiaw->dev, 0),
				OTI6858_WEQ_T_CHECK_TXBUFF,
				OTI6858_WEQ_CHECK_TXBUFF,
				count, 0, awwow, 1, 100);
		if (wesuwt != 1 || *awwow != 0)
			count = 0;
		kfwee(awwow);
	}

	if (count == 0) {
		pwiv->fwags.wwite_uwb_in_use = 0;

		dev_dbg(&powt->dev, "%s(): submitting intewwupt uwb\n", __func__);
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_NOIO);
		if (wesuwt != 0) {
			dev_eww(&powt->dev, "%s(): usb_submit_uwb() faiwed with ewwow %d\n",
				__func__, wesuwt);
		}
		wetuwn;
	}

	count = kfifo_out_wocked(&powt->wwite_fifo,
					powt->wwite_uwb->twansfew_buffew,
					count, &powt->wock);
	powt->wwite_uwb->twansfew_buffew_wength = count;
	wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_NOIO);
	if (wesuwt != 0) {
		dev_eww_consowe(powt, "%s(): usb_submit_uwb() faiwed with ewwow %d\n",
				__func__, wesuwt);
		pwiv->fwags.wwite_uwb_in_use = 0;
	}

	usb_sewiaw_powt_softint(powt);
}

static int oti6858_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct oti6858_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwiv->powt = powt;
	INIT_DEWAYED_WOWK(&pwiv->dewayed_setup_wowk, setup_wine);
	INIT_DEWAYED_WOWK(&pwiv->dewayed_wwite_wowk, send_data);

	usb_set_sewiaw_powt_data(powt, pwiv);

	powt->powt.dwain_deway = 256;	/* FIXME: check the FIFO wength */

	wetuwn 0;
}

static void oti6858_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct oti6858_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int oti6858_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			const unsigned chaw *buf, int count)
{
	if (!count)
		wetuwn count;

	count = kfifo_in_wocked(&powt->wwite_fifo, buf, count, &powt->wock);

	wetuwn count;
}

static unsigned int oti6858_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned int woom;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	woom = kfifo_avaiw(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wetuwn woom;
}

static unsigned int oti6858_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned int chaws;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	chaws = kfifo_wen(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wetuwn chaws;
}

static void oti6858_init_tewmios(stwuct tty_stwuct *tty)
{
	tty_encode_baud_wate(tty, 38400, 38400);
}

static void oti6858_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios)
{
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned int cfwag;
	u8 fwame_fmt, contwow;
	__we16 divisow;
	int bw;

	cfwag = tty->tewmios.c_cfwag;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	divisow = pwiv->pending_setup.divisow;
	fwame_fmt = pwiv->pending_setup.fwame_fmt;
	contwow = pwiv->pending_setup.contwow;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	fwame_fmt &= ~FMT_DATA_BITS_MASK;
	switch (cfwag & CSIZE) {
	case CS5:
		fwame_fmt |= FMT_DATA_BITS_5;
		bweak;
	case CS6:
		fwame_fmt |= FMT_DATA_BITS_6;
		bweak;
	case CS7:
		fwame_fmt |= FMT_DATA_BITS_7;
		bweak;
	defauwt:
	case CS8:
		fwame_fmt |= FMT_DATA_BITS_8;
		bweak;
	}

	/* manufactuwew cwaims that this device can wowk with baud wates
	 * up to 3 Mbps; I've tested it onwy on 115200 bps, so I can't
	 * guawantee that any othew baud wate wiww wowk (especiawwy
	 * the highew ones)
	 */
	bw = tty_get_baud_wate(tty);
	if (bw == 0) {
		divisow = 0;
	} ewse {
		int weaw_bw;
		int new_divisow;
		bw = min(bw, OTI6858_MAX_BAUD_WATE);

		new_divisow = (96000000 + 8 * bw) / (16 * bw);
		weaw_bw = 96000000 / (16 * new_divisow);
		divisow = cpu_to_we16(new_divisow);
		tty_encode_baud_wate(tty, weaw_bw, weaw_bw);
	}

	fwame_fmt &= ~FMT_STOP_BITS_MASK;
	if ((cfwag & CSTOPB) != 0)
		fwame_fmt |= FMT_STOP_BITS_2;
	ewse
		fwame_fmt |= FMT_STOP_BITS_1;

	fwame_fmt &= ~FMT_PAWITY_MASK;
	if ((cfwag & PAWENB) != 0) {
		if ((cfwag & PAWODD) != 0)
			fwame_fmt |= FMT_PAWITY_ODD;
		ewse
			fwame_fmt |= FMT_PAWITY_EVEN;
	} ewse {
		fwame_fmt |= FMT_PAWITY_NONE;
	}

	contwow &= ~CONTWOW_MASK;
	if ((cfwag & CWTSCTS) != 0)
		contwow |= (CONTWOW_DTW_HIGH | CONTWOW_WTS_HIGH);

	/* change contwow wines if we awe switching to ow fwom B0 */
	/* FIXME:
	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow = pwiv->wine_contwow;
	if ((cfwag & CBAUD) == B0)
		pwiv->wine_contwow &= ~(CONTWOW_DTW | CONTWOW_WTS);
	ewse
		pwiv->wine_contwow |= (CONTWOW_DTW | CONTWOW_WTS);
	if (contwow != pwiv->wine_contwow) {
		contwow = pwiv->wine_contwow;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		set_contwow_wines(sewiaw->dev, contwow);
	} ewse {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}
	*/

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (divisow != pwiv->pending_setup.divisow
			|| contwow != pwiv->pending_setup.contwow
			|| fwame_fmt != pwiv->pending_setup.fwame_fmt) {
		pwiv->pending_setup.divisow = divisow;
		pwiv->pending_setup.contwow = contwow;
		pwiv->pending_setup.fwame_fmt = fwame_fmt;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int oti6858_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct oti6858_contwow_pkt *buf;
	unsigned wong fwags;
	int wesuwt;

	usb_cweaw_hawt(sewiaw->dev, powt->wwite_uwb->pipe);
	usb_cweaw_hawt(sewiaw->dev, powt->wead_uwb->pipe);

	buf = kmawwoc(OTI6858_CTWW_PKT_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wesuwt = usb_contwow_msg(sewiaw->dev, usb_wcvctwwpipe(sewiaw->dev, 0),
				OTI6858_WEQ_T_GET_STATUS,
				OTI6858_WEQ_GET_STATUS,
				0, 0,
				buf, OTI6858_CTWW_PKT_SIZE,
				100);
	if (wesuwt != OTI6858_CTWW_PKT_SIZE) {
		/* assume defauwt (aftew powew-on weset) vawues */
		buf->divisow = cpu_to_we16(0x009c);	/* 38400 bps */
		buf->fwame_fmt = 0x03;	/* 8N1 */
		buf->something = 0x43;
		buf->contwow = 0x4c;	/* DTW, WTS */
		buf->tx_status = 0x00;
		buf->pin_state = 0x5b;	/* WTS, CTS, DSW, DTW, WI, DCD */
		buf->wx_bytes_avaiw = 0x00;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	memcpy(&pwiv->status, buf, OTI6858_CTWW_PKT_SIZE);
	pwiv->pending_setup.divisow = buf->divisow;
	pwiv->pending_setup.fwame_fmt = buf->fwame_fmt;
	pwiv->pending_setup.contwow = buf->contwow;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	kfwee(buf);

	dev_dbg(&powt->dev, "%s(): submitting intewwupt uwb\n", __func__);
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wesuwt != 0) {
		dev_eww(&powt->dev, "%s(): usb_submit_uwb() faiwed with ewwow %d\n",
			__func__, wesuwt);
		oti6858_cwose(powt);
		wetuwn wesuwt;
	}

	/* setup tewmios */
	if (tty)
		oti6858_set_tewmios(tty, powt, NUWW);

	wetuwn 0;
}

static void oti6858_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	/* cweaw out any wemaining data in the buffew */
	kfifo_weset_out(&powt->wwite_fifo);
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	dev_dbg(&powt->dev, "%s(): aftew buf_cweaw()\n", __func__);

	/* cancew scheduwed setup */
	cancew_dewayed_wowk_sync(&pwiv->dewayed_setup_wowk);
	cancew_dewayed_wowk_sync(&pwiv->dewayed_wwite_wowk);

	/* shutdown ouw uwbs */
	dev_dbg(&powt->dev, "%s(): shutting down uwbs\n", __func__);
	usb_kiww_uwb(powt->wwite_uwb);
	usb_kiww_uwb(powt->wead_uwb);
	usb_kiww_uwb(powt->intewwupt_in_uwb);
}

static int oti6858_tiocmset(stwuct tty_stwuct *tty,
				unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	u8 contwow;

	dev_dbg(&powt->dev, "%s(set = 0x%08x, cweaw = 0x%08x)\n",
		__func__, set, cweaw);

	/* FIXME: check if this is cowwect (active high/wow) */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow = pwiv->pending_setup.contwow;
	if ((set & TIOCM_WTS) != 0)
		contwow |= CONTWOW_WTS_HIGH;
	if ((set & TIOCM_DTW) != 0)
		contwow |= CONTWOW_DTW_HIGH;
	if ((cweaw & TIOCM_WTS) != 0)
		contwow &= ~CONTWOW_WTS_HIGH;
	if ((cweaw & TIOCM_DTW) != 0)
		contwow &= ~CONTWOW_DTW_HIGH;

	if (contwow != pwiv->pending_setup.contwow)
		pwiv->pending_setup.contwow = contwow;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn 0;
}

static int oti6858_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned pin_state;
	unsigned wesuwt = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pin_state = pwiv->status.pin_state & PIN_MASK;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* FIXME: check if this is cowwect (active high/wow) */
	if ((pin_state & PIN_WTS) != 0)
		wesuwt |= TIOCM_WTS;
	if ((pin_state & PIN_CTS) != 0)
		wesuwt |= TIOCM_CTS;
	if ((pin_state & PIN_DSW) != 0)
		wesuwt |= TIOCM_DSW;
	if ((pin_state & PIN_DTW) != 0)
		wesuwt |= TIOCM_DTW;
	if ((pin_state & PIN_WI) != 0)
		wesuwt |= TIOCM_WI;
	if ((pin_state & PIN_DCD) != 0)
		wesuwt |= TIOCM_CD;

	dev_dbg(&powt->dev, "%s() = 0x%08x\n", __func__, wesuwt);

	wetuwn wesuwt;
}

static void oti6858_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt =  uwb->context;
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int twansient = 0, can_wecv = 0, wesubmit = 1;
	int status = uwb->status;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s(): uwb shutting down with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&uwb->dev->dev, "%s(): nonzewo uwb status weceived: %d\n",
			__func__, status);
		bweak;
	}

	if (status == 0 && uwb->actuaw_wength == OTI6858_CTWW_PKT_SIZE) {
		stwuct oti6858_contwow_pkt *xs = uwb->twansfew_buffew;
		unsigned wong fwags;

		spin_wock_iwqsave(&pwiv->wock, fwags);

		if (!pwiv->twansient) {
			if (!OTI6858_CTWW_EQUAWS_PENDING(xs, pwiv)) {
				if (xs->wx_bytes_avaiw == 0) {
					pwiv->twansient = 4;
					pwiv->setup_done = 0;
					wesubmit = 0;
					dev_dbg(&powt->dev, "%s(): scheduwing setup_wine()\n", __func__);
					scheduwe_dewayed_wowk(&pwiv->dewayed_setup_wowk, 0);
				}
			}
		} ewse {
			if (OTI6858_CTWW_EQUAWS_PENDING(xs, pwiv)) {
				pwiv->twansient = 0;
			} ewse if (!pwiv->setup_done) {
				wesubmit = 0;
			} ewse if (--pwiv->twansient == 0) {
				if (xs->wx_bytes_avaiw == 0) {
					pwiv->twansient = 4;
					pwiv->setup_done = 0;
					wesubmit = 0;
					dev_dbg(&powt->dev, "%s(): scheduwing setup_wine()\n", __func__);
					scheduwe_dewayed_wowk(&pwiv->dewayed_setup_wowk, 0);
				}
			}
		}

		if (!pwiv->twansient) {
			u8 dewta = xs->pin_state ^ pwiv->status.pin_state;

			if (dewta & PIN_MSW_MASK) {
				if (dewta & PIN_CTS)
					powt->icount.cts++;
				if (dewta & PIN_DSW)
					powt->icount.dsw++;
				if (dewta & PIN_WI)
					powt->icount.wng++;
				if (dewta & PIN_DCD)
					powt->icount.dcd++;

				wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
			}

			memcpy(&pwiv->status, xs, OTI6858_CTWW_PKT_SIZE);
		}

		if (!pwiv->twansient && xs->wx_bytes_avaiw != 0) {
			can_wecv = xs->wx_bytes_avaiw;
			pwiv->fwags.wead_uwb_in_use = 1;
		}

		twansient = pwiv->twansient;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}

	if (can_wecv) {
		int wesuwt;

		wesuwt = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
		if (wesuwt != 0) {
			pwiv->fwags.wead_uwb_in_use = 0;
			dev_eww(&powt->dev, "%s(): usb_submit_uwb() faiwed,"
					" ewwow %d\n", __func__, wesuwt);
		} ewse {
			wesubmit = 0;
		}
	} ewse if (!twansient) {
		unsigned wong fwags;
		int count;

		spin_wock_iwqsave(&powt->wock, fwags);
		count = kfifo_wen(&powt->wwite_fifo);
		spin_unwock_iwqwestowe(&powt->wock, fwags);

		spin_wock_iwqsave(&pwiv->wock, fwags);
		if (pwiv->fwags.wwite_uwb_in_use == 0 && count != 0) {
			scheduwe_dewayed_wowk(&pwiv->dewayed_wwite_wowk, 0);
			wesubmit = 0;
		}
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}

	if (wesubmit) {
		int wesuwt;

/*		dev_dbg(&uwb->dev->dev, "%s(): submitting intewwupt uwb\n", __func__); */
		wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
		if (wesuwt != 0) {
			dev_eww(&uwb->dev->dev,
					"%s(): usb_submit_uwb() faiwed with"
					" ewwow %d\n", __func__, wesuwt);
		}
	}
}

static void oti6858_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt =  uwb->context;
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned wong fwags;
	int status = uwb->status;
	int wesuwt;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->fwags.wead_uwb_in_use = 0;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (status != 0) {
		dev_dbg(&uwb->dev->dev, "%s(): unabwe to handwe the ewwow, exiting\n", __func__);
		wetuwn;
	}

	if (uwb->actuaw_wength > 0) {
		tty_insewt_fwip_stwing(&powt->powt, data, uwb->actuaw_wength);
		tty_fwip_buffew_push(&powt->powt);
	}

	/* scheduwe the intewwupt uwb */
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_ATOMIC);
	if (wesuwt != 0 && wesuwt != -EPEWM) {
		dev_eww(&powt->dev, "%s(): usb_submit_uwb() faiwed,"
				" ewwow %d\n", __func__, wesuwt);
	}
}

static void oti6858_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt =  uwb->context;
	stwuct oti6858_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int status = uwb->status;
	int wesuwt;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s(): uwb shutting down with status: %d\n", __func__, status);
		pwiv->fwags.wwite_uwb_in_use = 0;
		wetuwn;
	defauwt:
		/* ewwow in the uwb, so we have to wesubmit it */
		dev_dbg(&uwb->dev->dev, "%s(): nonzewo wwite buwk status weceived: %d\n", __func__, status);
		dev_dbg(&uwb->dev->dev, "%s(): ovewfwow in wwite\n", __func__);

		powt->wwite_uwb->twansfew_buffew_wength = 1;
		wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
		if (wesuwt) {
			dev_eww_consowe(powt, "%s(): usb_submit_uwb() faiwed,"
					" ewwow %d\n", __func__, wesuwt);
		} ewse {
			wetuwn;
		}
	}

	pwiv->fwags.wwite_uwb_in_use = 0;

	/* scheduwe the intewwupt uwb if we awe stiww open */
	dev_dbg(&powt->dev, "%s(): submitting intewwupt uwb\n", __func__);
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_ATOMIC);
	if (wesuwt != 0) {
		dev_eww(&powt->dev, "%s(): faiwed submitting int uwb,"
					" ewwow %d\n", __func__, wesuwt);
	}
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_DESCWIPTION(OTI6858_DESCWIPTION);
MODUWE_AUTHOW(OTI6858_AUTHOW);
MODUWE_WICENSE("GPW v2");
