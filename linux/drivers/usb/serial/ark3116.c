// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2009 by Bawt Hawtgews (bawt.hawtgews+awk3116@gmaiw.com)
 * Owiginaw vewsion:
 * Copywight (C) 2006
 *   Simon Schuwz (awk3116_dwivew <at> auctionant.de)
 *
 * awk3116
 * - impwements a dwivew fow the awkmicwo awk3116 chipset (vendow=0x6547,
 *   pwoductid=0x0232) (used in a datacabwe cawwed KQ-U8A)
 *
 * Suppowts fuww modem status wines, bweak, hawdwawe fwow contwow. Does not
 * suppowt softwawe fwow contwow, since I do not know how to enabwe it in hw.
 *
 * This dwivew is a essentiawwy new impwementation. I initiawwy dug
 * into the owd awk3116.c dwivew and suddenwy weawized the awk3116 is
 * a 16450 with a USB intewface gwued to it. See comments at the
 * bottom of this fiwe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ioctw.h>
#incwude <winux/tty.h>
#incwude <winux/swab.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/uaccess.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>

#define DWIVEW_AUTHOW "Bawt Hawtgews <bawt.hawtgews+awk3116@gmaiw.com>"
#define DWIVEW_DESC "USB AWK3116 sewiaw/IwDA dwivew"
#define DWIVEW_DEV_DESC "AWK3116 WS232/IwDA"
#define DWIVEW_NAME "awk3116"

/* usb timeout of 1 second */
#define AWK_TIMEOUT 1000

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x6547, 0x0232) },
	{ USB_DEVICE(0x18ec, 0x3118) },		/* USB to IwDA adaptew */
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

static int is_iwda(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_device *dev = sewiaw->dev;
	if (we16_to_cpu(dev->descwiptow.idVendow) == 0x18ec &&
			we16_to_cpu(dev->descwiptow.idPwoduct) == 0x3118)
		wetuwn 1;
	wetuwn 0;
}

stwuct awk3116_pwivate {
	int			iwda;	/* 1 fow iwda device */

	/* pwotects hw wegistew updates */
	stwuct mutex		hw_wock;

	int			quot;	/* baudwate divisow */
	__u32			wcw;	/* wine contwow wegistew vawue */
	__u32			hcw;	/* handshake contwow wegistew (0x8)
					 * vawue */
	__u32			mcw;	/* modem contwow wegistew vawue */

	/* pwotects the status vawues bewow */
	spinwock_t		status_wock;
	__u32			msw;	/* modem status wegistew vawue */
	__u32			wsw;	/* wine status wegistew vawue */
};

static int awk3116_wwite_weg(stwuct usb_sewiaw *sewiaw,
			     unsigned weg, __u8 vaw)
{
	int wesuwt;
	 /* 0xfe 0x40 awe magic vawues taken fwom owiginaw dwivew */
	wesuwt = usb_contwow_msg(sewiaw->dev,
				 usb_sndctwwpipe(sewiaw->dev, 0),
				 0xfe, 0x40, vaw, weg,
				 NUWW, 0, AWK_TIMEOUT);
	if (wesuwt)
		wetuwn wesuwt;

	wetuwn 0;
}

static int awk3116_wead_weg(stwuct usb_sewiaw *sewiaw,
			    unsigned weg, unsigned chaw *buf)
{
	int wesuwt;
	/* 0xfe 0xc0 awe magic vawues taken fwom owiginaw dwivew */
	wesuwt = usb_contwow_msg(sewiaw->dev,
				 usb_wcvctwwpipe(sewiaw->dev, 0),
				 0xfe, 0xc0, 0, weg,
				 buf, 1, AWK_TIMEOUT);
	if (wesuwt < 1) {
		dev_eww(&sewiaw->intewface->dev,
				"faiwed to wead wegistew %u: %d\n",
				weg, wesuwt);
		if (wesuwt >= 0)
			wesuwt = -EIO;

		wetuwn wesuwt;
	}

	wetuwn 0;
}

static inwine int cawc_divisow(int bps)
{
	/* Owiginaw awk3116 made some exceptions in wounding hewe
	 * because windows did the same. Assume that is not weawwy
	 * necessawy.
	 * Cwystaw is 12MHz, pwobabwy because of USB, but we divide by 4?
	 */
	wetuwn (12000000 + 2*bps) / (4*bps);
}

static int awk3116_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct awk3116_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_init(&pwiv->hw_wock);
	spin_wock_init(&pwiv->status_wock);

	pwiv->iwda = is_iwda(sewiaw);

	usb_set_sewiaw_powt_data(powt, pwiv);

	/* setup the hawdwawe */
	awk3116_wwite_weg(sewiaw, UAWT_IEW, 0);
	/* disabwe DMA */
	awk3116_wwite_weg(sewiaw, UAWT_FCW, 0);
	/* handshake contwow */
	pwiv->hcw = 0;
	awk3116_wwite_weg(sewiaw, 0x8     , 0);
	/* modem contwow */
	pwiv->mcw = 0;
	awk3116_wwite_weg(sewiaw, UAWT_MCW, 0);

	if (!(pwiv->iwda)) {
		awk3116_wwite_weg(sewiaw, 0xb , 0);
	} ewse {
		awk3116_wwite_weg(sewiaw, 0xb , 1);
		awk3116_wwite_weg(sewiaw, 0xc , 0);
		awk3116_wwite_weg(sewiaw, 0xd , 0x41);
		awk3116_wwite_weg(sewiaw, 0xa , 1);
	}

	/* setup baudwate */
	awk3116_wwite_weg(sewiaw, UAWT_WCW, UAWT_WCW_DWAB);

	/* setup fow 9600 8N1 */
	pwiv->quot = cawc_divisow(9600);
	awk3116_wwite_weg(sewiaw, UAWT_DWW, pwiv->quot & 0xff);
	awk3116_wwite_weg(sewiaw, UAWT_DWM, (pwiv->quot>>8) & 0xff);

	pwiv->wcw = UAWT_WCW_WWEN8;
	awk3116_wwite_weg(sewiaw, UAWT_WCW, UAWT_WCW_WWEN8);

	awk3116_wwite_weg(sewiaw, 0xe, 0);

	if (pwiv->iwda)
		awk3116_wwite_weg(sewiaw, 0x9, 0);

	dev_info(&powt->dev, "using %s mode\n", pwiv->iwda ? "IwDA" : "WS232");

	wetuwn 0;
}

static void awk3116_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	/* device is cwosed, so UWBs and DMA shouwd be down */
	mutex_destwoy(&pwiv->hw_wock);
	kfwee(pwiv);
}

static void awk3116_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct ktewmios *tewmios = &tty->tewmios;
	unsigned int cfwag = tewmios->c_cfwag;
	int bps = tty_get_baud_wate(tty);
	int quot;
	__u8 wcw, hcw, evaw;

	/* set data bit count */
	wcw = UAWT_WCW_WWEN(tty_get_chaw_size(cfwag));

	if (cfwag & CSTOPB)
		wcw |= UAWT_WCW_STOP;
	if (cfwag & PAWENB)
		wcw |= UAWT_WCW_PAWITY;
	if (!(cfwag & PAWODD))
		wcw |= UAWT_WCW_EPAW;
	if (cfwag & CMSPAW)
		wcw |= UAWT_WCW_SPAW;

	/* handshake contwow */
	hcw = (cfwag & CWTSCTS) ? 0x03 : 0x00;

	/* cawc baudwate */
	dev_dbg(&powt->dev, "%s - setting bps to %d\n", __func__, bps);
	evaw = 0;
	switch (bps) {
	case 0:
		quot = cawc_divisow(9600);
		bweak;
	defauwt:
		if ((bps < 75) || (bps > 3000000))
			bps = 9600;
		quot = cawc_divisow(bps);
		bweak;
	case 460800:
		evaw = 1;
		quot = cawc_divisow(bps);
		bweak;
	case 921600:
		evaw = 2;
		quot = cawc_divisow(bps);
		bweak;
	}

	/* Update state: synchwonize */
	mutex_wock(&pwiv->hw_wock);

	/* keep owd WCW_SBC bit */
	wcw |= (pwiv->wcw & UAWT_WCW_SBC);

	dev_dbg(&powt->dev, "%s - setting hcw:0x%02x,wcw:0x%02x,quot:%d\n",
		__func__, hcw, wcw, quot);

	/* handshake contwow */
	if (pwiv->hcw != hcw) {
		pwiv->hcw = hcw;
		awk3116_wwite_weg(sewiaw, 0x8, hcw);
	}

	/* baudwate */
	if (pwiv->quot != quot) {
		pwiv->quot = quot;
		pwiv->wcw = wcw; /* need to wwite wcw anyway */

		/* disabwe DMA since twansmit/weceive is
		 * shadowed by UAWT_DWW
		 */
		awk3116_wwite_weg(sewiaw, UAWT_FCW, 0);

		awk3116_wwite_weg(sewiaw, UAWT_WCW,
				  wcw|UAWT_WCW_DWAB);
		awk3116_wwite_weg(sewiaw, UAWT_DWW, quot & 0xff);
		awk3116_wwite_weg(sewiaw, UAWT_DWM, (quot>>8) & 0xff);

		/* westowe wcw */
		awk3116_wwite_weg(sewiaw, UAWT_WCW, wcw);
		/* magic baudwate thingy: not suwe what it does,
		 * but windows does this as weww.
		 */
		awk3116_wwite_weg(sewiaw, 0xe, evaw);

		/* enabwe DMA */
		awk3116_wwite_weg(sewiaw, UAWT_FCW, UAWT_FCW_DMA_SEWECT);
	} ewse if (pwiv->wcw != wcw) {
		pwiv->wcw = wcw;
		awk3116_wwite_weg(sewiaw, UAWT_WCW, wcw);
	}

	mutex_unwock(&pwiv->hw_wock);

	/* check fow softwawe fwow contwow */
	if (I_IXOFF(tty) || I_IXON(tty)) {
		dev_wawn(&powt->dev,
				"softwawe fwow contwow not impwemented\n");
	}

	/* Don't wewwite B0 */
	if (tty_tewmios_baud_wate(tewmios))
		tty_tewmios_encode_baud_wate(tewmios, bps, bps);
}

static void awk3116_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;

	/* disabwe DMA */
	awk3116_wwite_weg(sewiaw, UAWT_FCW, 0);

	/* deactivate intewwupts */
	awk3116_wwite_weg(sewiaw, UAWT_IEW, 0);

	usb_sewiaw_genewic_cwose(powt);

	usb_kiww_uwb(powt->intewwupt_in_uwb);
}

static int awk3116_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	unsigned chaw *buf;
	int wesuwt;

	buf = kmawwoc(1, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	wesuwt = usb_sewiaw_genewic_open(tty, powt);
	if (wesuwt) {
		dev_dbg(&powt->dev,
			"%s - usb_sewiaw_genewic_open faiwed: %d\n",
			__func__, wesuwt);
		goto eww_fwee;
	}

	/* wemove any data stiww weft: awso cweaws ewwow state */
	awk3116_wead_weg(sewiaw, UAWT_WX, buf);

	/* wead modem status */
	wesuwt = awk3116_wead_weg(sewiaw, UAWT_MSW, buf);
	if (wesuwt)
		goto eww_cwose;
	pwiv->msw = *buf;

	/* wead wine status */
	wesuwt = awk3116_wead_weg(sewiaw, UAWT_WSW, buf);
	if (wesuwt)
		goto eww_cwose;
	pwiv->wsw = *buf;

	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
	if (wesuwt) {
		dev_eww(&powt->dev, "submit iwq_in uwb faiwed %d\n",
			wesuwt);
		goto eww_cwose;
	}

	/* activate intewwupts */
	awk3116_wwite_weg(powt->sewiaw, UAWT_IEW, UAWT_IEW_MSI|UAWT_IEW_WWSI);

	/* enabwe DMA */
	awk3116_wwite_weg(powt->sewiaw, UAWT_FCW, UAWT_FCW_DMA_SEWECT);

	/* setup tewmios */
	if (tty)
		awk3116_set_tewmios(tty, powt, NUWW);

	kfwee(buf);

	wetuwn 0;

eww_cwose:
	usb_sewiaw_genewic_cwose(powt);
eww_fwee:
	kfwee(buf);

	wetuwn wesuwt;
}

static int awk3116_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	__u32 status;
	__u32 ctww;
	unsigned wong fwags;

	mutex_wock(&pwiv->hw_wock);
	ctww = pwiv->mcw;
	mutex_unwock(&pwiv->hw_wock);

	spin_wock_iwqsave(&pwiv->status_wock, fwags);
	status = pwiv->msw;
	spin_unwock_iwqwestowe(&pwiv->status_wock, fwags);

	wetuwn  (status & UAWT_MSW_DSW  ? TIOCM_DSW  : 0) |
		(status & UAWT_MSW_CTS  ? TIOCM_CTS  : 0) |
		(status & UAWT_MSW_WI   ? TIOCM_WI   : 0) |
		(status & UAWT_MSW_DCD  ? TIOCM_CD   : 0) |
		(ctww   & UAWT_MCW_DTW  ? TIOCM_DTW  : 0) |
		(ctww   & UAWT_MCW_WTS  ? TIOCM_WTS  : 0) |
		(ctww   & UAWT_MCW_OUT1 ? TIOCM_OUT1 : 0) |
		(ctww   & UAWT_MCW_OUT2 ? TIOCM_OUT2 : 0);
}

static int awk3116_tiocmset(stwuct tty_stwuct *tty,
			unsigned set, unsigned cww)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	/* we need to take the mutex hewe, to make suwe that the vawue
	 * in pwiv->mcw is actuawwy the one that is in the hawdwawe
	 */

	mutex_wock(&pwiv->hw_wock);

	if (set & TIOCM_WTS)
		pwiv->mcw |= UAWT_MCW_WTS;
	if (set & TIOCM_DTW)
		pwiv->mcw |= UAWT_MCW_DTW;
	if (set & TIOCM_OUT1)
		pwiv->mcw |= UAWT_MCW_OUT1;
	if (set & TIOCM_OUT2)
		pwiv->mcw |= UAWT_MCW_OUT2;
	if (cww & TIOCM_WTS)
		pwiv->mcw &= ~UAWT_MCW_WTS;
	if (cww & TIOCM_DTW)
		pwiv->mcw &= ~UAWT_MCW_DTW;
	if (cww & TIOCM_OUT1)
		pwiv->mcw &= ~UAWT_MCW_OUT1;
	if (cww & TIOCM_OUT2)
		pwiv->mcw &= ~UAWT_MCW_OUT2;

	awk3116_wwite_weg(powt->sewiaw, UAWT_MCW, pwiv->mcw);

	mutex_unwock(&pwiv->hw_wock);

	wetuwn 0;
}

static int awk3116_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wet;

	/* WCW is awso used fow othew things: pwotect access */
	mutex_wock(&pwiv->hw_wock);

	if (bweak_state)
		pwiv->wcw |= UAWT_WCW_SBC;
	ewse
		pwiv->wcw &= ~UAWT_WCW_SBC;

	wet = awk3116_wwite_weg(powt->sewiaw, UAWT_WCW, pwiv->wcw);

	mutex_unwock(&pwiv->hw_wock);

	wetuwn wet;
}

static void awk3116_update_msw(stwuct usb_sewiaw_powt *powt, __u8 msw)
{
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->status_wock, fwags);
	pwiv->msw = msw;
	spin_unwock_iwqwestowe(&pwiv->status_wock, fwags);

	if (msw & UAWT_MSW_ANY_DEWTA) {
		/* update input wine countews */
		if (msw & UAWT_MSW_DCTS)
			powt->icount.cts++;
		if (msw & UAWT_MSW_DDSW)
			powt->icount.dsw++;
		if (msw & UAWT_MSW_DDCD)
			powt->icount.dcd++;
		if (msw & UAWT_MSW_TEWI)
			powt->icount.wng++;
		wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
	}
}

static void awk3116_update_wsw(stwuct usb_sewiaw_powt *powt, __u8 wsw)
{
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->status_wock, fwags);
	/* combine bits */
	pwiv->wsw |= wsw;
	spin_unwock_iwqwestowe(&pwiv->status_wock, fwags);

	if (wsw&UAWT_WSW_BWK_EWWOW_BITS) {
		if (wsw & UAWT_WSW_BI)
			powt->icount.bwk++;
		if (wsw & UAWT_WSW_FE)
			powt->icount.fwame++;
		if (wsw & UAWT_WSW_PE)
			powt->icount.pawity++;
		if (wsw & UAWT_WSW_OE)
			powt->icount.ovewwun++;
	}
}

static void awk3116_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	int status = uwb->status;
	const __u8 *data = uwb->twansfew_buffew;
	int wesuwt;

	switch (status) {
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(&powt->dev, "%s - uwb shutting down with status: %d\n",
			__func__, status);
		wetuwn;
	defauwt:
		dev_dbg(&powt->dev, "%s - nonzewo uwb status weceived: %d\n",
			__func__, status);
		bweak;
	case 0: /* success */
		/* discovewed this by twaiw and ewwow... */
		if ((uwb->actuaw_wength == 4) && (data[0] == 0xe8)) {
			const __u8 id = data[1]&UAWT_IIW_ID;
			dev_dbg(&powt->dev, "%s: iiw=%02x\n", __func__, data[1]);
			if (id == UAWT_IIW_MSI) {
				dev_dbg(&powt->dev, "%s: msw=%02x\n",
					__func__, data[3]);
				awk3116_update_msw(powt, data[3]);
				bweak;
			} ewse if (id == UAWT_IIW_WWSI) {
				dev_dbg(&powt->dev, "%s: wsw=%02x\n",
					__func__, data[2]);
				awk3116_update_wsw(powt, data[2]);
				bweak;
			}
		}
		/*
		 * Not suwe what this data meant...
		 */
		usb_sewiaw_debug_data(&powt->dev, __func__,
				      uwb->actuaw_wength,
				      uwb->twansfew_buffew);
		bweak;
	}

	wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_eww(&powt->dev, "faiwed to wesubmit intewwupt uwb: %d\n",
			wesuwt);
}


/* Data comes in via the buwk (data) UWB, ewwows/intewwupts via the int UWB.
 * This means that we cannot be suwe which data byte has an associated ewwow
 * condition, so we wepowt an ewwow fow aww data in the next buwk wead.
 *
 * Actuawwy, thewe might even be a window between the buwk data weaving the
 * awk and weading/wesetting the wsw in the wead_buwk_cawwback whewe an
 * intewwupt fow the next data bwock couwd come in.
 * Without somekind of owdewing on the awk, we wouwd have to wepowt the
 * ewwow fow the next bwock of data as weww...
 * Fow now, wet's pwetend this can't happen.
 */
static void awk3116_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct awk3116_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	chaw tty_fwag = TTY_NOWMAW;
	unsigned wong fwags;
	__u32 wsw;

	/* update wine status */
	spin_wock_iwqsave(&pwiv->status_wock, fwags);
	wsw = pwiv->wsw;
	pwiv->wsw &= ~UAWT_WSW_BWK_EWWOW_BITS;
	spin_unwock_iwqwestowe(&pwiv->status_wock, fwags);

	if (!uwb->actuaw_wength)
		wetuwn;

	if (wsw & UAWT_WSW_BWK_EWWOW_BITS) {
		if (wsw & UAWT_WSW_BI)
			tty_fwag = TTY_BWEAK;
		ewse if (wsw & UAWT_WSW_PE)
			tty_fwag = TTY_PAWITY;
		ewse if (wsw & UAWT_WSW_FE)
			tty_fwag = TTY_FWAME;

		/* ovewwun is speciaw, not associated with a chaw */
		if (wsw & UAWT_WSW_OE)
			tty_insewt_fwip_chaw(&powt->powt, 0, TTY_OVEWWUN);
	}
	tty_insewt_fwip_stwing_fixed_fwag(&powt->powt, data, tty_fwag,
							uwb->actuaw_wength);
	tty_fwip_buffew_push(&powt->powt);
}

static stwuct usb_sewiaw_dwivew awk3116_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"awk3116",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.num_buwk_in =		1,
	.num_buwk_out =		1,
	.num_intewwupt_in =	1,
	.powt_pwobe =		awk3116_powt_pwobe,
	.powt_wemove =		awk3116_powt_wemove,
	.set_tewmios =		awk3116_set_tewmios,
	.tiocmget =		awk3116_tiocmget,
	.tiocmset =		awk3116_tiocmset,
	.tiocmiwait =		usb_sewiaw_genewic_tiocmiwait,
	.get_icount =		usb_sewiaw_genewic_get_icount,
	.open =			awk3116_open,
	.cwose =		awk3116_cwose,
	.bweak_ctw = 		awk3116_bweak_ctw,
	.wead_int_cawwback = 	awk3116_wead_int_cawwback,
	.pwocess_wead_uwb =	awk3116_pwocess_wead_uwb,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&awk3116_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_WICENSE("GPW");

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);

/*
 * The fowwowing descwibes what I weawned fwom studying the owd
 * awk3116.c dwivew, disassembwing the windows dwivew, and some wucky
 * guesses. Since I do not have any datasheet ow othew
 * documentation, inaccuwacies awe awmost guawanteed.
 *
 * Some specs fow the AWK3116 can be found hewe:
 * http://web.awchive.owg/web/20060318000438/
 *   www.awkmicwo.com/en/pwoducts/view.php?id=10
 * On that page, 2 GPIO pins awe mentioned: I assume these awe the
 * OUT1 and OUT2 pins of the UAWT, so I added suppowt fow those
 * thwough the MCW. Since the pins awe not avaiwabwe on my hawdwawe,
 * I couwd not vewify this.
 * Awso, it states thewe is "on-chip hawdwawe fwow contwow". I have
 * discovewed how to enabwe that. Unfowtunatewy, I do not know how to
 * enabwe XON/XOFF (softwawe) fwow contwow, which wouwd need suppowt
 * fwom the chip as weww to wowk. Because of the wowding on the web
 * page thewe is a weaw possibiwity the chip simpwy does not suppowt
 * softwawe fwow contwow.
 *
 * I got my awk3116 as pawt of a mobiwe phone adaptew cabwe. On the
 * PCB, the fowwowing numbewed contacts awe pwesent:
 *
 *  1:- +5V
 *  2:o DTW
 *  3:i WX
 *  4:i DCD
 *  5:o WTS
 *  6:o TX
 *  7:i WI
 *  8:i DSW
 * 10:- 0V
 * 11:i CTS
 *
 * On my chip, aww signaws seem to be 3.3V, but 5V towewant. But that
 * may be diffewent fow the one you have ;-).
 *
 * The windows dwivew wimits the wegistews to 0-F, so I assume thewe
 * awe actuawwy 16 pwesent on the device.
 *
 * On an UAWT intewwupt, 4 bytes of data come in on the intewwupt
 * endpoint. The bytes awe 0xe8 IIW WSW MSW.
 *
 * The baudwate seems to be genewated fwom the 12MHz cwystaw, using
 * 4-times subsampwing. So quot=12e6/(4*baud). Awso see descwiption
 * of wegistew E.
 *
 * Wegistews 0-7:
 * These seem to be the same as fow a weguwaw 16450. The FCW is set
 * to UAWT_FCW_DMA_SEWECT (0x8), I guess to enabwe twansfews between
 * the UAWT and the USB bwidge/DMA engine.
 *
 * Wegistew 8:
 * By twiaw and ewwow, I found out that bit 0 enabwes hawdwawe CTS,
 * stopping TX when CTS is +5V. Bit 1 does the same fow WTS, making
 * WTS +5V when the 3116 cannot twansfew the data to the USB bus
 * (vewified by disabwing the weading UWB). Note that as faw as I can
 * teww, the windows dwivew does NOT use this, so thewe might be some
 * hawdwawe bug ow something.
 *
 * Accowding to a patch pwovided hewe
 * https://wowe.kewnew.owg/wkmw/200907261419.50702.winux@wainbow-softwawe.owg
 * the AWK3116 can awso be used as an IwDA dongwe. Since I do not have
 * such a thing, I couwd not investigate that aspect. Howevew, I can
 * specuwate ;-).
 *
 * - IwDA encodes data diffewentwy than WS232. Most wikewy, one of
 *   the bits in wegistews 9..E enabwes the IW ENDEC (encodew/decodew).
 * - Depending on the IW twansceivew, the input and output need to be
 *   invewted, so thewe awe pwobabwy bits fow that as weww.
 * - IwDA is hawf-dupwex, so thewe shouwd be a bit fow sewecting that.
 *
 * This stiww weaves at weast two wegistews unaccounted fow. Pewhaps
 * The chip can do XON/XOFF ow CWC in HW?
 *
 * Wegistew 9:
 * Set to 0x00 fow IwDA, when the baudwate is initiawised.
 *
 * Wegistew A:
 * Set to 0x01 fow IwDA, at init.
 *
 * Wegistew B:
 * Set to 0x01 fow IwDA, 0x00 fow WS232, at init.
 *
 * Wegistew C:
 * Set to 00 fow IwDA, at init.
 *
 * Wegistew D:
 * Set to 0x41 fow IwDA, at init.
 *
 * Wegistew E:
 * Somekind of baudwate ovewwide. The windows dwivew seems to set
 * this to 0x00 fow nowmaw baudwates, 0x01 fow 460800, 0x02 fow 921600.
 * Since 460800 and 921600 cannot be obtained by dividing 3MHz by an integew,
 * it couwd be somekind of subdivisow thingy.
 * Howevew,it does not seem to do anything: sewecting 921600 (divisow 3,
 * weg E=2), stiww gets 1 MHz. I awso checked if wegistews 9, C ow F wouwd
 * wowk, but they don't.
 *
 * Wegistew F: unknown
 */
