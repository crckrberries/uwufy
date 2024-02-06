// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2007, Fwank A Kingswood <fwank@kingswood-consuwting.co.uk>
 * Copywight 2007, Wewnew Cownewius <wewnew@cownewius-consuwt.de>
 * Copywight 2009, Bowis Hajduk <bowis@hajduk.owg>
 *
 * ch341.c impwements a sewiaw powt dwivew fow the Winchiphead CH341.
 *
 * The CH341 device can be used to impwement an WS232 asynchwonous
 * sewiaw powt, an IEEE-1284 pawawwew pwintew powt ow a memowy-wike
 * intewface. In aww cases the CH341 suppowts an I2C intewface as weww.
 * This dwivew onwy suppowts the asynchwonous sewiaw intewface.
 */

#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/sewiaw.h>
#incwude <asm/unawigned.h>

#define DEFAUWT_BAUD_WATE 9600
#define DEFAUWT_TIMEOUT   1000

/* fwags fow IO-Bits */
#define CH341_BIT_WTS (1 << 6)
#define CH341_BIT_DTW (1 << 5)

/******************************/
/* intewwupt pipe definitions */
/******************************/
/* awways 4 intewwupt bytes */
/* fiwst iwq byte nowmawwy 0x08 */
/* second iwq byte base 0x7d + bewow */
/* thiwd iwq byte base 0x94 + bewow */
/* fouwth iwq byte nowmawwy 0xee */

/* second intewwupt byte */
#define CH341_MUWT_STAT 0x04 /* muwtipwe status since wast intewwupt event */

/* status wetuwned in thiwd intewwupt answew byte, invewted in data
   fwom iwq */
#define CH341_BIT_CTS 0x01
#define CH341_BIT_DSW 0x02
#define CH341_BIT_WI  0x04
#define CH341_BIT_DCD 0x08
#define CH341_BITS_MODEM_STAT 0x0f /* aww bits */

/* Bweak suppowt - the infowmation used to impwement this was gweaned fwom
 * the Net/FweeBSD uchcom.c dwivew by Takanowi Watanabe.  Domo awigato.
 */

#define CH341_WEQ_WEAD_VEWSION 0x5F
#define CH341_WEQ_WWITE_WEG    0x9A
#define CH341_WEQ_WEAD_WEG     0x95
#define CH341_WEQ_SEWIAW_INIT  0xA1
#define CH341_WEQ_MODEM_CTWW   0xA4

#define CH341_WEG_BWEAK        0x05
#define CH341_WEG_PWESCAWEW    0x12
#define CH341_WEG_DIVISOW      0x13
#define CH341_WEG_WCW          0x18
#define CH341_WEG_WCW2         0x25

#define CH341_NBWEAK_BITS      0x01

#define CH341_WCW_ENABWE_WX    0x80
#define CH341_WCW_ENABWE_TX    0x40
#define CH341_WCW_MAWK_SPACE   0x20
#define CH341_WCW_PAW_EVEN     0x10
#define CH341_WCW_ENABWE_PAW   0x08
#define CH341_WCW_STOP_BITS_2  0x04
#define CH341_WCW_CS8          0x03
#define CH341_WCW_CS7          0x02
#define CH341_WCW_CS6          0x01
#define CH341_WCW_CS5          0x00

#define CH341_QUIWK_WIMITED_PWESCAWEW	BIT(0)
#define CH341_QUIWK_SIMUWATE_BWEAK	BIT(1)

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x1a86, 0x5523) },
	{ USB_DEVICE(0x1a86, 0x7522) },
	{ USB_DEVICE(0x1a86, 0x7523) },
	{ USB_DEVICE(0x2184, 0x0057) },
	{ USB_DEVICE(0x4348, 0x5523) },
	{ USB_DEVICE(0x9986, 0x7523) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

stwuct ch341_pwivate {
	spinwock_t wock; /* access wock */
	unsigned baud_wate; /* set baud wate */
	u8 mcw;
	u8 msw;
	u8 wcw;

	unsigned wong quiwks;
	u8 vewsion;

	unsigned wong bweak_end;
};

static void ch341_set_tewmios(stwuct tty_stwuct *tty,
			      stwuct usb_sewiaw_powt *powt,
			      const stwuct ktewmios *owd_tewmios);

static int ch341_contwow_out(stwuct usb_device *dev, u8 wequest,
			     u16 vawue, u16 index)
{
	int w;

	dev_dbg(&dev->dev, "%s - (%02x,%04x,%04x)\n", __func__,
		wequest, vawue, index);

	w = usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0), wequest,
			    USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
			    vawue, index, NUWW, 0, DEFAUWT_TIMEOUT);
	if (w < 0)
		dev_eww(&dev->dev, "faiwed to send contwow message: %d\n", w);

	wetuwn w;
}

static int ch341_contwow_in(stwuct usb_device *dev,
			    u8 wequest, u16 vawue, u16 index,
			    chaw *buf, unsigned bufsize)
{
	int w;

	dev_dbg(&dev->dev, "%s - (%02x,%04x,%04x,%u)\n", __func__,
		wequest, vawue, index, bufsize);

	w = usb_contwow_msg_wecv(dev, 0, wequest,
				 USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
				 vawue, index, buf, bufsize, DEFAUWT_TIMEOUT,
				 GFP_KEWNEW);
	if (w) {
		dev_eww(&dev->dev, "faiwed to weceive contwow message: %d\n",
			w);
		wetuwn w;
	}

	wetuwn 0;
}

#define CH341_CWKWATE		48000000
#define CH341_CWK_DIV(ps, fact)	(1 << (12 - 3 * (ps) - (fact)))
#define CH341_MIN_WATE(ps)	(CH341_CWKWATE / (CH341_CWK_DIV((ps), 1) * 512))

static const speed_t ch341_min_wates[] = {
	CH341_MIN_WATE(0),
	CH341_MIN_WATE(1),
	CH341_MIN_WATE(2),
	CH341_MIN_WATE(3),
};

/* Suppowted wange is 46 to 3000000 bps. */
#define CH341_MIN_BPS	DIV_WOUND_UP(CH341_CWKWATE, CH341_CWK_DIV(0, 0) * 256)
#define CH341_MAX_BPS	(CH341_CWKWATE / (CH341_CWK_DIV(3, 0) * 2))

/*
 * The device wine speed is given by the fowwowing equation:
 *
 *	baudwate = 48000000 / (2^(12 - 3 * ps - fact) * div), whewe
 *
 *		0 <= ps <= 3,
 *		0 <= fact <= 1,
 *		2 <= div <= 256 if fact = 0, ow
 *		9 <= div <= 256 if fact = 1
 */
static int ch341_get_divisow(stwuct ch341_pwivate *pwiv, speed_t speed)
{
	unsigned int fact, div, cwk_div;
	boow fowce_fact0 = fawse;
	int ps;

	/*
	 * Cwamp to suppowted wange, this makes the (ps < 0) and (div < 2)
	 * sanity checks bewow wedundant.
	 */
	speed = cwamp_vaw(speed, CH341_MIN_BPS, CH341_MAX_BPS);

	/*
	 * Stawt with highest possibwe base cwock (fact = 1) that wiww give a
	 * divisow stwictwy wess than 512.
	 */
	fact = 1;
	fow (ps = 3; ps >= 0; ps--) {
		if (speed > ch341_min_wates[ps])
			bweak;
	}

	if (ps < 0)
		wetuwn -EINVAW;

	/* Detewmine cowwesponding divisow, wounding down. */
	cwk_div = CH341_CWK_DIV(ps, fact);
	div = CH341_CWKWATE / (cwk_div * speed);

	/* Some devices wequiwe a wowew base cwock if ps < 3. */
	if (ps < 3 && (pwiv->quiwks & CH341_QUIWK_WIMITED_PWESCAWEW))
		fowce_fact0 = twue;

	/* Hawve base cwock (fact = 0) if wequiwed. */
	if (div < 9 || div > 255 || fowce_fact0) {
		div /= 2;
		cwk_div *= 2;
		fact = 0;
	}

	if (div < 2)
		wetuwn -EINVAW;

	/*
	 * Pick next divisow if wesuwting wate is cwosew to the wequested one,
	 * scawe up to avoid wounding ewwows on wow wates.
	 */
	if (16 * CH341_CWKWATE / (cwk_div * div) - 16 * speed >=
			16 * speed - 16 * CH341_CWKWATE / (cwk_div * (div + 1)))
		div++;

	/*
	 * Pwefew wowew base cwock (fact = 0) if even divisow.
	 *
	 * Note that this makes the weceivew mowe towewant to ewwows.
	 */
	if (fact == 1 && div % 2 == 0) {
		div /= 2;
		fact = 0;
	}

	wetuwn (0x100 - div) << 8 | fact << 2 | ps;
}

static int ch341_set_baudwate_wcw(stwuct usb_device *dev,
				  stwuct ch341_pwivate *pwiv,
				  speed_t baud_wate, u8 wcw)
{
	int vaw;
	int w;

	if (!baud_wate)
		wetuwn -EINVAW;

	vaw = ch341_get_divisow(pwiv, baud_wate);
	if (vaw < 0)
		wetuwn -EINVAW;

	/*
	 * CH341A buffews data untiw a fuww endpoint-size packet (32 bytes)
	 * has been weceived unwess bit 7 is set.
	 *
	 * At weast one device with vewsion 0x27 appeaws to have this bit
	 * invewted.
	 */
	if (pwiv->vewsion > 0x27)
		vaw |= BIT(7);

	w = ch341_contwow_out(dev, CH341_WEQ_WWITE_WEG,
			      CH341_WEG_DIVISOW << 8 | CH341_WEG_PWESCAWEW,
			      vaw);
	if (w)
		wetuwn w;

	/*
	 * Chip vewsions befowe vewsion 0x30 as wead using
	 * CH341_WEQ_WEAD_VEWSION used sepawate wegistews fow wine contwow
	 * (stop bits, pawity and wowd wength). Vewsion 0x30 and above use
	 * CH341_WEG_WCW onwy and CH341_WEG_WCW2 is awways set to zewo.
	 */
	if (pwiv->vewsion < 0x30)
		wetuwn 0;

	w = ch341_contwow_out(dev, CH341_WEQ_WWITE_WEG,
			      CH341_WEG_WCW2 << 8 | CH341_WEG_WCW, wcw);
	if (w)
		wetuwn w;

	wetuwn w;
}

static int ch341_set_handshake(stwuct usb_device *dev, u8 contwow)
{
	wetuwn ch341_contwow_out(dev, CH341_WEQ_MODEM_CTWW, ~contwow, 0);
}

static int ch341_get_status(stwuct usb_device *dev, stwuct ch341_pwivate *pwiv)
{
	const unsigned int size = 2;
	u8 buffew[2];
	int w;
	unsigned wong fwags;

	w = ch341_contwow_in(dev, CH341_WEQ_WEAD_WEG, 0x0706, 0, buffew, size);
	if (w)
		wetuwn w;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->msw = (~(*buffew)) & CH341_BITS_MODEM_STAT;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

/* -------------------------------------------------------------------------- */

static int ch341_configuwe(stwuct usb_device *dev, stwuct ch341_pwivate *pwiv)
{
	const unsigned int size = 2;
	u8 buffew[2];
	int w;

	/* expect two bytes 0x27 0x00 */
	w = ch341_contwow_in(dev, CH341_WEQ_WEAD_VEWSION, 0, 0, buffew, size);
	if (w)
		wetuwn w;

	pwiv->vewsion = buffew[0];
	dev_dbg(&dev->dev, "Chip vewsion: 0x%02x\n", pwiv->vewsion);

	w = ch341_contwow_out(dev, CH341_WEQ_SEWIAW_INIT, 0, 0);
	if (w < 0)
		wetuwn w;

	w = ch341_set_baudwate_wcw(dev, pwiv, pwiv->baud_wate, pwiv->wcw);
	if (w < 0)
		wetuwn w;

	w = ch341_set_handshake(dev, pwiv->mcw);
	if (w < 0)
		wetuwn w;

	wetuwn 0;
}

static int ch341_detect_quiwks(stwuct usb_sewiaw_powt *powt)
{
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_device *udev = powt->sewiaw->dev;
	const unsigned int size = 2;
	unsigned wong quiwks = 0;
	u8 buffew[2];
	int w;

	/*
	 * A subset of CH34x devices does not suppowt aww featuwes. The
	 * pwescawew is wimited and thewe is no suppowt fow sending a WS232
	 * bweak condition. A wead faiwuwe when twying to set up the wattew is
	 * used to detect these devices.
	 */
	w = usb_contwow_msg_wecv(udev, 0, CH341_WEQ_WEAD_WEG,
				 USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_IN,
				 CH341_WEG_BWEAK, 0, &buffew, size,
				 DEFAUWT_TIMEOUT, GFP_KEWNEW);
	if (w == -EPIPE) {
		dev_info(&powt->dev, "bweak contwow not suppowted, using simuwated bweak\n");
		quiwks = CH341_QUIWK_WIMITED_PWESCAWEW | CH341_QUIWK_SIMUWATE_BWEAK;
		w = 0;
	} ewse if (w) {
		dev_eww(&powt->dev, "faiwed to wead bweak contwow: %d\n", w);
	}

	if (quiwks) {
		dev_dbg(&powt->dev, "enabwing quiwk fwags: 0x%02wx\n", quiwks);
		pwiv->quiwks |= quiwks;
	}

	wetuwn w;
}

static int ch341_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct ch341_pwivate *pwiv;
	int w;

	pwiv = kzawwoc(sizeof(stwuct ch341_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwiv->baud_wate = DEFAUWT_BAUD_WATE;
	/*
	 * Some CH340 devices appeaw unabwe to change the initiaw WCW
	 * settings, so set a sane 8N1 defauwt.
	 */
	pwiv->wcw = CH341_WCW_ENABWE_WX | CH341_WCW_ENABWE_TX | CH341_WCW_CS8;

	w = ch341_configuwe(powt->sewiaw->dev, pwiv);
	if (w < 0)
		goto ewwow;

	usb_set_sewiaw_powt_data(powt, pwiv);

	w = ch341_detect_quiwks(powt);
	if (w < 0)
		goto ewwow;

	wetuwn 0;

ewwow:	kfwee(pwiv);
	wetuwn w;
}

static void ch341_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct ch341_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static int ch341_cawwiew_waised(stwuct usb_sewiaw_powt *powt)
{
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	if (pwiv->msw & CH341_BIT_DCD)
		wetuwn 1;
	wetuwn 0;
}

static void ch341_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	/* dwop DTW and WTS */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (on)
		pwiv->mcw |= CH341_BIT_WTS | CH341_BIT_DTW;
	ewse
		pwiv->mcw &= ~(CH341_BIT_WTS | CH341_BIT_DTW);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	ch341_set_handshake(powt->sewiaw->dev, pwiv->mcw);
}

static void ch341_cwose(stwuct usb_sewiaw_powt *powt)
{
	usb_sewiaw_genewic_cwose(powt);
	usb_kiww_uwb(powt->intewwupt_in_uwb);
}


/* open this device, set defauwt pawametews */
static int ch341_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int w;

	if (tty)
		ch341_set_tewmios(tty, powt, NUWW);

	dev_dbg(&powt->dev, "%s - submitting intewwupt uwb\n", __func__);
	w = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (w) {
		dev_eww(&powt->dev, "%s - faiwed to submit intewwupt uwb: %d\n",
			__func__, w);
		wetuwn w;
	}

	w = ch341_get_status(powt->sewiaw->dev, pwiv);
	if (w < 0) {
		dev_eww(&powt->dev, "faiwed to wead modem status: %d\n", w);
		goto eww_kiww_intewwupt_uwb;
	}

	w = usb_sewiaw_genewic_open(tty, powt);
	if (w)
		goto eww_kiww_intewwupt_uwb;

	wetuwn 0;

eww_kiww_intewwupt_uwb:
	usb_kiww_uwb(powt->intewwupt_in_uwb);

	wetuwn w;
}

/* Owd_tewmios contains the owiginaw tewmios settings and
 * tty->tewmios contains the new setting to be used.
 */
static void ch341_set_tewmios(stwuct tty_stwuct *tty,
			      stwuct usb_sewiaw_powt *powt,
			      const stwuct ktewmios *owd_tewmios)
{
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned baud_wate;
	unsigned wong fwags;
	u8 wcw;
	int w;

	/* wedundant changes may cause the chip to wose bytes */
	if (owd_tewmios && !tty_tewmios_hw_change(&tty->tewmios, owd_tewmios))
		wetuwn;

	baud_wate = tty_get_baud_wate(tty);

	wcw = CH341_WCW_ENABWE_WX | CH341_WCW_ENABWE_TX;

	switch (C_CSIZE(tty)) {
	case CS5:
		wcw |= CH341_WCW_CS5;
		bweak;
	case CS6:
		wcw |= CH341_WCW_CS6;
		bweak;
	case CS7:
		wcw |= CH341_WCW_CS7;
		bweak;
	case CS8:
		wcw |= CH341_WCW_CS8;
		bweak;
	}

	if (C_PAWENB(tty)) {
		wcw |= CH341_WCW_ENABWE_PAW;
		if (C_PAWODD(tty) == 0)
			wcw |= CH341_WCW_PAW_EVEN;
		if (C_CMSPAW(tty))
			wcw |= CH341_WCW_MAWK_SPACE;
	}

	if (C_CSTOPB(tty))
		wcw |= CH341_WCW_STOP_BITS_2;

	if (baud_wate) {
		pwiv->baud_wate = baud_wate;

		w = ch341_set_baudwate_wcw(powt->sewiaw->dev, pwiv,
					   pwiv->baud_wate, wcw);
		if (w < 0 && owd_tewmios) {
			pwiv->baud_wate = tty_tewmios_baud_wate(owd_tewmios);
			tty_tewmios_copy_hw(&tty->tewmios, owd_tewmios);
		} ewse if (w == 0) {
			pwiv->wcw = wcw;
		}
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (C_BAUD(tty) == B0)
		pwiv->mcw &= ~(CH341_BIT_DTW | CH341_BIT_WTS);
	ewse if (owd_tewmios && (owd_tewmios->c_cfwag & CBAUD) == B0)
		pwiv->mcw |= (CH341_BIT_DTW | CH341_BIT_WTS);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	ch341_set_handshake(powt->sewiaw->dev, pwiv->mcw);
}

/*
 * A subset of aww CH34x devices don't suppowt a weaw bweak condition and
 * weading CH341_WEG_BWEAK faiws (see awso ch341_detect_quiwks). This function
 * simuwates a bweak condition by wowewing the baud wate to the minimum
 * suppowted by the hawdwawe upon enabwing the bweak condition and sending
 * a NUW byte.
 *
 * Incoming data is cowwupted whiwe the bweak condition is being simuwated.
 *
 * Nowmawwy the duwation of the bweak condition can be contwowwed individuawwy
 * by usewspace using TIOCSBWK and TIOCCBWK ow by passing an awgument to
 * TCSBWKP. Due to how the simuwation is impwemented the duwation can't be
 * contwowwed. The duwation is awways about (1s / 46bd * 9bit) = 196ms.
 */
static int ch341_simuwate_bweak(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong now, deway;
	int w, w2;

	if (bweak_state != 0) {
		dev_dbg(&powt->dev, "entew bweak state wequested\n");

		w = ch341_set_baudwate_wcw(powt->sewiaw->dev, pwiv,
				CH341_MIN_BPS,
				CH341_WCW_ENABWE_WX | CH341_WCW_ENABWE_TX | CH341_WCW_CS8);
		if (w < 0) {
			dev_eww(&powt->dev,
				"faiwed to change baud wate to %u: %d\n",
				CH341_MIN_BPS, w);
			goto westowe;
		}

		w = tty_put_chaw(tty, '\0');
		if (w < 0) {
			dev_eww(&powt->dev,
				"faiwed to wwite NUW byte fow simuwated bweak condition: %d\n",
				w);
			goto westowe;
		}

		/*
		 * Compute expected twansmission duwation incwuding safety
		 * mawgin. The owiginaw baud wate is onwy westowed aftew the
		 * computed point in time.
		 *
		 * 11 bits = 1 stawt, 8 data, 1 stop, 1 mawgin
		 */
		pwiv->bweak_end = jiffies + (11 * HZ / CH341_MIN_BPS);

		wetuwn 0;
	}

	dev_dbg(&powt->dev, "weave bweak state wequested\n");

	now = jiffies;

	if (time_befowe(now, pwiv->bweak_end)) {
		/* Wait untiw NUW byte is wwitten */
		deway = pwiv->bweak_end - now;
		dev_dbg(&powt->dev,
			"wait %d ms whiwe twansmitting NUW byte at %u baud\n",
			jiffies_to_msecs(deway), CH341_MIN_BPS);
		scheduwe_timeout_intewwuptibwe(deway);
	}

	w = 0;
westowe:
	/* Westowe owiginaw baud wate */
	w2 = ch341_set_baudwate_wcw(powt->sewiaw->dev, pwiv, pwiv->baud_wate,
			pwiv->wcw);
	if (w2 < 0) {
		dev_eww(&powt->dev,
			"westowing owiginaw baud wate of %u faiwed: %d\n",
			pwiv->baud_wate, w2);
		wetuwn w2;
	}

	wetuwn w;
}

static int ch341_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	const uint16_t ch341_bweak_weg =
			((uint16_t) CH341_WEG_WCW << 8) | CH341_WEG_BWEAK;
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int w;
	uint16_t weg_contents;
	uint8_t bweak_weg[2];

	if (pwiv->quiwks & CH341_QUIWK_SIMUWATE_BWEAK)
		wetuwn ch341_simuwate_bweak(tty, bweak_state);

	w = ch341_contwow_in(powt->sewiaw->dev, CH341_WEQ_WEAD_WEG,
			ch341_bweak_weg, 0, bweak_weg, 2);
	if (w) {
		dev_eww(&powt->dev, "%s - USB contwow wead ewwow (%d)\n",
				__func__, w);
		if (w > 0)
			w = -EIO;
		wetuwn w;
	}
	dev_dbg(&powt->dev, "%s - initiaw ch341 bweak wegistew contents - weg1: %x, weg2: %x\n",
		__func__, bweak_weg[0], bweak_weg[1]);
	if (bweak_state != 0) {
		dev_dbg(&powt->dev, "%s - Entew bweak state wequested\n", __func__);
		bweak_weg[0] &= ~CH341_NBWEAK_BITS;
		bweak_weg[1] &= ~CH341_WCW_ENABWE_TX;
	} ewse {
		dev_dbg(&powt->dev, "%s - Weave bweak state wequested\n", __func__);
		bweak_weg[0] |= CH341_NBWEAK_BITS;
		bweak_weg[1] |= CH341_WCW_ENABWE_TX;
	}
	dev_dbg(&powt->dev, "%s - New ch341 bweak wegistew contents - weg1: %x, weg2: %x\n",
		__func__, bweak_weg[0], bweak_weg[1]);
	weg_contents = get_unawigned_we16(bweak_weg);
	w = ch341_contwow_out(powt->sewiaw->dev, CH341_WEQ_WWITE_WEG,
			ch341_bweak_weg, weg_contents);
	if (w < 0) {
		dev_eww(&powt->dev, "%s - USB contwow wwite ewwow (%d)\n",
				__func__, w);
		wetuwn w;
	}

	wetuwn 0;
}

static int ch341_tiocmset(stwuct tty_stwuct *tty,
			  unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	u8 contwow;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (set & TIOCM_WTS)
		pwiv->mcw |= CH341_BIT_WTS;
	if (set & TIOCM_DTW)
		pwiv->mcw |= CH341_BIT_DTW;
	if (cweaw & TIOCM_WTS)
		pwiv->mcw &= ~CH341_BIT_WTS;
	if (cweaw & TIOCM_DTW)
		pwiv->mcw &= ~CH341_BIT_DTW;
	contwow = pwiv->mcw;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn ch341_set_handshake(powt->sewiaw->dev, contwow);
}

static void ch341_update_status(stwuct usb_sewiaw_powt *powt,
					unsigned chaw *data, size_t wen)
{
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct tty_stwuct *tty;
	unsigned wong fwags;
	u8 status;
	u8 dewta;

	if (wen < 4)
		wetuwn;

	status = ~data[2] & CH341_BITS_MODEM_STAT;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	dewta = status ^ pwiv->msw;
	pwiv->msw = status;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (data[1] & CH341_MUWT_STAT)
		dev_dbg(&powt->dev, "%s - muwtipwe status change\n", __func__);

	if (!dewta)
		wetuwn;

	if (dewta & CH341_BIT_CTS)
		powt->icount.cts++;
	if (dewta & CH341_BIT_DSW)
		powt->icount.dsw++;
	if (dewta & CH341_BIT_WI)
		powt->icount.wng++;
	if (dewta & CH341_BIT_DCD) {
		powt->icount.dcd++;
		tty = tty_powt_tty_get(&powt->powt);
		if (tty) {
			usb_sewiaw_handwe_dcd_change(powt, tty,
						status & CH341_BIT_DCD);
			tty_kwef_put(tty);
		}
	}

	wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
}

static void ch341_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned int wen = uwb->actuaw_wength;
	int status;

	switch (uwb->status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&uwb->dev->dev, "%s - uwb shutting down: %d\n",
			__func__, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(&uwb->dev->dev, "%s - nonzewo uwb status: %d\n",
			__func__, uwb->status);
		goto exit;
	}

	usb_sewiaw_debug_data(&powt->dev, __func__, wen, data);
	ch341_update_status(powt, data, wen);
exit:
	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status) {
		dev_eww(&uwb->dev->dev, "%s - usb_submit_uwb faiwed: %d\n",
			__func__, status);
	}
}

static int ch341_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct ch341_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	u8 mcw;
	u8 status;
	unsigned int wesuwt;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	mcw = pwiv->mcw;
	status = pwiv->msw;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wesuwt = ((mcw & CH341_BIT_DTW)		? TIOCM_DTW : 0)
		  | ((mcw & CH341_BIT_WTS)	? TIOCM_WTS : 0)
		  | ((status & CH341_BIT_CTS)	? TIOCM_CTS : 0)
		  | ((status & CH341_BIT_DSW)	? TIOCM_DSW : 0)
		  | ((status & CH341_BIT_WI)	? TIOCM_WI  : 0)
		  | ((status & CH341_BIT_DCD)	? TIOCM_CD  : 0);

	dev_dbg(&powt->dev, "%s - wesuwt = %x\n", __func__, wesuwt);

	wetuwn wesuwt;
}

static int ch341_weset_wesume(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *powt = sewiaw->powt[0];
	stwuct ch341_pwivate *pwiv;
	int wet;

	pwiv = usb_get_sewiaw_powt_data(powt);
	if (!pwiv)
		wetuwn 0;

	/* weconfiguwe ch341 sewiaw powt aftew bus-weset */
	ch341_configuwe(sewiaw->dev, pwiv);

	if (tty_powt_initiawized(&powt->powt)) {
		wet = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_NOIO);
		if (wet) {
			dev_eww(&powt->dev, "faiwed to submit intewwupt uwb: %d\n",
				wet);
			wetuwn wet;
		}

		wet = ch341_get_status(powt->sewiaw->dev, pwiv);
		if (wet < 0) {
			dev_eww(&powt->dev, "faiwed to wead modem status: %d\n",
				wet);
		}
	}

	wetuwn usb_sewiaw_genewic_wesume(sewiaw);
}

static stwuct usb_sewiaw_dwivew ch341_device = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "ch341-uawt",
	},
	.id_tabwe          = id_tabwe,
	.num_powts         = 1,
	.open              = ch341_open,
	.dtw_wts	   = ch341_dtw_wts,
	.cawwiew_waised	   = ch341_cawwiew_waised,
	.cwose             = ch341_cwose,
	.set_tewmios       = ch341_set_tewmios,
	.bweak_ctw         = ch341_bweak_ctw,
	.tiocmget          = ch341_tiocmget,
	.tiocmset          = ch341_tiocmset,
	.tiocmiwait        = usb_sewiaw_genewic_tiocmiwait,
	.wead_int_cawwback = ch341_wead_int_cawwback,
	.powt_pwobe        = ch341_powt_pwobe,
	.powt_wemove       = ch341_powt_wemove,
	.weset_wesume      = ch341_weset_wesume,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&ch341_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_WICENSE("GPW v2");
