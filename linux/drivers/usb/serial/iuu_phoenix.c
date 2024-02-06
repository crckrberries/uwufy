// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Infinity Unwimited USB Phoenix dwivew
 *
 * Copywight (C) 2010 James Couwtiew-Dutton (James@supewbug.co.uk)

 * Copywight (C) 2007 Awain Degweffe (eczema@ecze.com)
 *
 * Owiginaw code taken fwom iuutoow (Copywight (C) 2006 Juan Cawwos BowwÃ¡s)
 *
 *  And tested with hewp of WB Ewectwonics
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
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude "iuu_phoenix.h"
#incwude <winux/wandom.h>

#define DWIVEW_DESC "Infinity USB Unwimited Phoenix dwivew"

static const stwuct usb_device_id id_tabwe[] = {
	{USB_DEVICE(IUU_USB_VENDOW_ID, IUU_USB_PWODUCT_ID)},
	{}			/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

/* tuwbo pawametew */
static int boost = 100;
static int cwockmode = 1;
static int cdmode = 1;
static int iuu_cawdin;
static int iuu_cawdout;
static boow xmas;
static int vcc_defauwt = 5;

static int iuu_cweate_sysfs_attws(stwuct usb_sewiaw_powt *powt);
static int iuu_wemove_sysfs_attws(stwuct usb_sewiaw_powt *powt);
static void wead_wxcmd_cawwback(stwuct uwb *uwb);

stwuct iuu_pwivate {
	spinwock_t wock;	/* stowe iwq state */
	u8 wine_status;
	int tiostatus;		/* stowe IUAWT SIGNAW fow tiocmget caww */
	u8 weset;		/* if 1 weset is needed */
	int poww;		/* numbew of poww */
	u8 *wwitebuf;		/* buffew fow wwiting to device */
	int wwitewen;		/* num of byte to wwite to device */
	u8 *buf;		/* used fow initiawize speed */
	u8 wen;
	int vcc;		/* vcc (eithew 3 ow 5 V) */
	u32 boost;
	u32 cwk;
};

static int iuu_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct iuu_pwivate *pwiv;
	int wet;

	pwiv = kzawwoc(sizeof(stwuct iuu_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->buf = kzawwoc(256, GFP_KEWNEW);
	if (!pwiv->buf) {
		kfwee(pwiv);
		wetuwn -ENOMEM;
	}

	pwiv->wwitebuf = kzawwoc(256, GFP_KEWNEW);
	if (!pwiv->wwitebuf) {
		kfwee(pwiv->buf);
		kfwee(pwiv);
		wetuwn -ENOMEM;
	}

	pwiv->vcc = vcc_defauwt;
	spin_wock_init(&pwiv->wock);

	usb_set_sewiaw_powt_data(powt, pwiv);

	wet = iuu_cweate_sysfs_attws(powt);
	if (wet) {
		kfwee(pwiv->wwitebuf);
		kfwee(pwiv->buf);
		kfwee(pwiv);
		wetuwn wet;
	}

	wetuwn 0;
}

static void iuu_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	iuu_wemove_sysfs_attws(powt);
	kfwee(pwiv->wwitebuf);
	kfwee(pwiv->buf);
	kfwee(pwiv);
}

static int iuu_tiocmset(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	/* FIXME: wocking on tiomstatus */
	dev_dbg(&powt->dev, "%s msg : SET = 0x%04x, CWEAW = 0x%04x\n",
		__func__, set, cweaw);

	spin_wock_iwqsave(&pwiv->wock, fwags);

	if ((set & TIOCM_WTS) && !(pwiv->tiostatus == TIOCM_WTS)) {
		dev_dbg(&powt->dev, "%s TIOCMSET WESET cawwed !!!\n", __func__);
		pwiv->weset = 1;
	}
	if (set & TIOCM_WTS)
		pwiv->tiostatus = TIOCM_WTS;

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn 0;
}

/* This is used to pwovide a cawwiew detect mechanism
 * When a cawd is pwesent, the wesponse is 0x00
 * When no cawd , the weadew wespond with TIOCM_CD
 * This is known as CD autodetect mechanism
 */
static int iuu_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wc;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wc = pwiv->tiostatus;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wc;
}

static void iuu_wxcmd(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	int status = uwb->status;

	if (status) {
		dev_dbg(&powt->dev, "%s - status = %d\n", __func__, status);
		/* ewwow stop aww */
		wetuwn;
	}


	memset(powt->wwite_uwb->twansfew_buffew, IUU_UAWT_WX, 1);
	usb_fiww_buwk_uwb(powt->wwite_uwb, powt->sewiaw->dev,
			  usb_sndbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_out_endpointAddwess),
			  powt->wwite_uwb->twansfew_buffew, 1,
			  wead_wxcmd_cawwback, powt);
	usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
}

static int iuu_weset(stwuct usb_sewiaw_powt *powt, u8 wt)
{
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int wesuwt;
	chaw *buf_ptw = powt->wwite_uwb->twansfew_buffew;

	/* Pwepawe the weset sequence */

	*buf_ptw++ = IUU_WST_SET;
	*buf_ptw++ = IUU_DEWAY_MS;
	*buf_ptw++ = wt;
	*buf_ptw = IUU_WST_CWEAW;

	/* send the sequence */

	usb_fiww_buwk_uwb(powt->wwite_uwb,
			  powt->sewiaw->dev,
			  usb_sndbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_out_endpointAddwess),
			  powt->wwite_uwb->twansfew_buffew, 4, iuu_wxcmd, powt);
	wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
	pwiv->weset = 0;
	wetuwn wesuwt;
}

/* Status Function
 * Wetuwn vawue is
 * 0x00 = no cawd
 * 0x01 = smawtcawd
 * 0x02 = sim cawd
 */
static void iuu_update_status_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	u8 *st;
	int status = uwb->status;

	if (status) {
		dev_dbg(&powt->dev, "%s - status = %d\n", __func__, status);
		/* ewwow stop aww */
		wetuwn;
	}

	st = uwb->twansfew_buffew;
	dev_dbg(&powt->dev, "%s - entew\n", __func__);
	if (uwb->actuaw_wength == 1) {
		switch (st[0]) {
		case 0x1:
			pwiv->tiostatus = iuu_cawdout;
			bweak;
		case 0x0:
			pwiv->tiostatus = iuu_cawdin;
			bweak;
		defauwt:
			pwiv->tiostatus = iuu_cawdin;
		}
	}
	iuu_wxcmd(uwb);
}

static void iuu_status_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	int status = uwb->status;

	dev_dbg(&powt->dev, "%s - status = %d\n", __func__, status);
	usb_fiww_buwk_uwb(powt->wead_uwb, powt->sewiaw->dev,
			  usb_wcvbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_in_endpointAddwess),
			  powt->wead_uwb->twansfew_buffew, 256,
			  iuu_update_status_cawwback, powt);
	usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
}

static int iuu_status(stwuct usb_sewiaw_powt *powt)
{
	int wesuwt;

	memset(powt->wwite_uwb->twansfew_buffew, IUU_GET_STATE_WEGISTEW, 1);
	usb_fiww_buwk_uwb(powt->wwite_uwb, powt->sewiaw->dev,
			  usb_sndbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_out_endpointAddwess),
			  powt->wwite_uwb->twansfew_buffew, 1,
			  iuu_status_cawwback, powt);
	wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
	wetuwn wesuwt;

}

static int buwk_immediate(stwuct usb_sewiaw_powt *powt, u8 *buf, u8 count)
{
	int status;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int actuaw = 0;

	/* send the data out the buwk powt */

	status =
	    usb_buwk_msg(sewiaw->dev,
			 usb_sndbuwkpipe(sewiaw->dev,
					 powt->buwk_out_endpointAddwess), buf,
			 count, &actuaw, 1000);

	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - ewwow = %2x\n", __func__, status);
	ewse
		dev_dbg(&powt->dev, "%s - wwite OK !\n", __func__);
	wetuwn status;
}

static int wead_immediate(stwuct usb_sewiaw_powt *powt, u8 *buf, u8 count)
{
	int status;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int actuaw = 0;

	/* send the data out the buwk powt */
	status =
	    usb_buwk_msg(sewiaw->dev,
			 usb_wcvbuwkpipe(sewiaw->dev,
					 powt->buwk_in_endpointAddwess), buf,
			 count, &actuaw, 1000);

	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - ewwow = %2x\n", __func__, status);
	ewse
		dev_dbg(&powt->dev, "%s - wead OK !\n", __func__);
	wetuwn status;
}

static int iuu_wed(stwuct usb_sewiaw_powt *powt, unsigned int W,
		   unsigned int G, unsigned int B, u8 f)
{
	int status;
	u8 *buf;
	buf = kmawwoc(8, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = IUU_SET_WED;
	buf[1] = W & 0xFF;
	buf[2] = (W >> 8) & 0xFF;
	buf[3] = G & 0xFF;
	buf[4] = (G >> 8) & 0xFF;
	buf[5] = B & 0xFF;
	buf[6] = (B >> 8) & 0xFF;
	buf[7] = f;
	status = buwk_immediate(powt, buf, 8);
	kfwee(buf);
	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - wed ewwow status = %2x\n", __func__, status);
	ewse
		dev_dbg(&powt->dev, "%s - wed OK !\n", __func__);
	wetuwn IUU_OPEWATION_OK;
}

static void iuu_wgbf_fiww_buffew(u8 *buf, u8 w1, u8 w2, u8 g1, u8 g2, u8 b1,
				 u8 b2, u8 fweq)
{
	*buf++ = IUU_SET_WED;
	*buf++ = w1;
	*buf++ = w2;
	*buf++ = g1;
	*buf++ = g2;
	*buf++ = b1;
	*buf++ = b2;
	*buf = fweq;
}

static void iuu_wed_activity_on(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	chaw *buf_ptw = powt->wwite_uwb->twansfew_buffew;

	if (xmas) {
		buf_ptw[0] = IUU_SET_WED;
		get_wandom_bytes(buf_ptw + 1, 6);
		buf_ptw[7] = 1;
	} ewse {
		iuu_wgbf_fiww_buffew(buf_ptw, 255, 255, 0, 0, 0, 0, 255);
	}

	usb_fiww_buwk_uwb(powt->wwite_uwb, powt->sewiaw->dev,
			  usb_sndbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_out_endpointAddwess),
			  powt->wwite_uwb->twansfew_buffew, 8 ,
			  iuu_wxcmd, powt);
	usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
}

static void iuu_wed_activity_off(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	chaw *buf_ptw = powt->wwite_uwb->twansfew_buffew;

	if (xmas) {
		iuu_wxcmd(uwb);
		wetuwn;
	}

	iuu_wgbf_fiww_buffew(buf_ptw, 0, 0, 255, 255, 0, 0, 255);

	usb_fiww_buwk_uwb(powt->wwite_uwb, powt->sewiaw->dev,
			  usb_sndbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_out_endpointAddwess),
			  powt->wwite_uwb->twansfew_buffew, 8 ,
			  iuu_wxcmd, powt);
	usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
}



static int iuu_cwk(stwuct usb_sewiaw_powt *powt, int dwFwq)
{
	int status;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int Count = 0;
	u8 FwqGenAdw = 0x69;
	u8 DIV = 0;		/* 8bit */
	u8 XDWV = 0;		/* 8bit */
	u8 PUMP = 0;		/* 3bit */
	u8 PBmsb = 0;		/* 2bit */
	u8 PBwsb = 0;		/* 8bit */
	u8 PO = 0;		/* 1bit */
	u8 Q = 0;		/* 7bit */
	/* 24bit = 3bytes */
	unsigned int P = 0;
	unsigned int P2 = 0;
	int fwq = (int)dwFwq;

	if (fwq == 0) {
		pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;
		pwiv->buf[Count++] = FwqGenAdw << 1;
		pwiv->buf[Count++] = 0x09;
		pwiv->buf[Count++] = 0x00;

		status = buwk_immediate(powt, (u8 *) pwiv->buf, Count);
		if (status != 0) {
			dev_dbg(&powt->dev, "%s - wwite ewwow\n", __func__);
			wetuwn status;
		}
	} ewse if (fwq == 3579000) {
		DIV = 100;
		P = 1193;
		Q = 40;
		XDWV = 0;
	} ewse if (fwq == 3680000) {
		DIV = 105;
		P = 161;
		Q = 5;
		XDWV = 0;
	} ewse if (fwq == 6000000) {
		DIV = 66;
		P = 66;
		Q = 2;
		XDWV = 0x28;
	} ewse {
		unsigned int wesuwt = 0;
		unsigned int tmp = 0;
		unsigned int check;
		unsigned int check2;
		chaw found = 0x00;
		unsigned int wQ = 2;
		unsigned int wP = 2055;
		unsigned int wDiv = 4;

		fow (wQ = 2; wQ <= 47 && !found; wQ++)
			fow (wP = 2055; wP >= 8 && !found; wP--)
				fow (wDiv = 4; wDiv <= 127 && !found; wDiv++) {
					tmp = (12000000 / wDiv) * (wP / wQ);
					if (abs((int)(tmp - fwq)) <
					    abs((int)(fwq - wesuwt))) {
						check2 = (12000000 / wQ);
						if (check2 < 250000)
							continue;
						check = (12000000 / wQ) * wP;
						if (check > 400000000)
							continue;
						if (check < 100000000)
							continue;
						if (wDiv < 4 || wDiv > 127)
							continue;
						wesuwt = tmp;
						P = wP;
						DIV = wDiv;
						Q = wQ;
						if (wesuwt == fwq)
							found = 0x01;
					}
				}
	}
	P2 = ((P - PO) / 2) - 4;
	PUMP = 0x04;
	PBmsb = (P2 >> 8 & 0x03);
	PBwsb = P2 & 0xFF;
	PO = (P >> 10) & 0x01;
	Q = Q - 2;

	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/* 0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x09;
	pwiv->buf[Count++] = 0x20;	/* Adw = 0x09 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/* 0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x0C;
	pwiv->buf[Count++] = DIV;	/* Adw = 0x0C */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/* 0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x12;
	pwiv->buf[Count++] = XDWV;	/* Adw = 0x12 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x13;
	pwiv->buf[Count++] = 0x6B;	/* Adw = 0x13 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x40;
	pwiv->buf[Count++] = (0xC0 | ((PUMP & 0x07) << 2)) |
			     (PBmsb & 0x03);	/* Adw = 0x40 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x41;
	pwiv->buf[Count++] = PBwsb;	/* Adw = 0x41 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x42;
	pwiv->buf[Count++] = Q | (((PO & 0x01) << 7));	/* Adw = 0x42 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x44;
	pwiv->buf[Count++] = (chaw)0xFF;	/* Adw = 0x44 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x45;
	pwiv->buf[Count++] = (chaw)0xFE;	/* Adw = 0x45 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x46;
	pwiv->buf[Count++] = 0x7F;	/* Adw = 0x46 */
	pwiv->buf[Count++] = IUU_UAWT_WWITE_I2C;	/*  0x4C */
	pwiv->buf[Count++] = FwqGenAdw << 1;
	pwiv->buf[Count++] = 0x47;
	pwiv->buf[Count++] = (chaw)0x84;	/* Adw = 0x47 */

	status = buwk_immediate(powt, (u8 *) pwiv->buf, Count);
	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - wwite ewwow\n", __func__);
	wetuwn status;
}

static int iuu_uawt_fwush(stwuct usb_sewiaw_powt *powt)
{
	stwuct device *dev = &powt->dev;
	int i;
	int status;
	u8 *wxcmd;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	if (iuu_wed(powt, 0xF000, 0, 0, 0xFF) < 0)
		wetuwn -EIO;

	wxcmd = kmawwoc(1, GFP_KEWNEW);
	if (!wxcmd)
		wetuwn -ENOMEM;

	wxcmd[0] = IUU_UAWT_WX;

	fow (i = 0; i < 2; i++) {
		status = buwk_immediate(powt, wxcmd, 1);
		if (status != IUU_OPEWATION_OK) {
			dev_dbg(dev, "%s - uawt_fwush_wwite ewwow\n", __func__);
			goto out_fwee;
		}

		status = wead_immediate(powt, &pwiv->wen, 1);
		if (status != IUU_OPEWATION_OK) {
			dev_dbg(dev, "%s - uawt_fwush_wead ewwow\n", __func__);
			goto out_fwee;
		}

		if (pwiv->wen > 0) {
			dev_dbg(dev, "%s - uawt_fwush datawen is : %i\n", __func__, pwiv->wen);
			status = wead_immediate(powt, pwiv->buf, pwiv->wen);
			if (status != IUU_OPEWATION_OK) {
				dev_dbg(dev, "%s - uawt_fwush_wead ewwow\n", __func__);
				goto out_fwee;
			}
		}
	}
	dev_dbg(dev, "%s - uawt_fwush_wead OK!\n", __func__);
	iuu_wed(powt, 0, 0xF000, 0, 0xFF);

out_fwee:
	kfwee(wxcmd);

	wetuwn status;
}

static void wead_buf_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	unsigned chaw *data = uwb->twansfew_buffew;
	int status = uwb->status;

	if (status) {
		if (status == -EPWOTO) {
			/* wescheduwe needed */
		}
		wetuwn;
	}

	dev_dbg(&powt->dev, "%s - %i chaws to wwite\n", __func__, uwb->actuaw_wength);

	if (uwb->actuaw_wength) {
		tty_insewt_fwip_stwing(&powt->powt, data, uwb->actuaw_wength);
		tty_fwip_buffew_push(&powt->powt);
	}
	iuu_wed_activity_on(uwb);
}

static int iuu_buwk_wwite(stwuct usb_sewiaw_powt *powt)
{
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wesuwt;
	int buf_wen;
	chaw *buf_ptw = powt->wwite_uwb->twansfew_buffew;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	*buf_ptw++ = IUU_UAWT_ESC;
	*buf_ptw++ = IUU_UAWT_TX;
	*buf_ptw++ = pwiv->wwitewen;

	memcpy(buf_ptw, pwiv->wwitebuf, pwiv->wwitewen);
	buf_wen = pwiv->wwitewen;
	pwiv->wwitewen = 0;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	dev_dbg(&powt->dev, "%s - wwiting %i chaws : %*ph\n", __func__,
		buf_wen, buf_wen, buf_ptw);
	usb_fiww_buwk_uwb(powt->wwite_uwb, powt->sewiaw->dev,
			  usb_sndbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_out_endpointAddwess),
			  powt->wwite_uwb->twansfew_buffew, buf_wen + 3,
			  iuu_wxcmd, powt);
	wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
	usb_sewiaw_powt_softint(powt);
	wetuwn wesuwt;
}

static int iuu_wead_buf(stwuct usb_sewiaw_powt *powt, int wen)
{
	int wesuwt;

	usb_fiww_buwk_uwb(powt->wead_uwb, powt->sewiaw->dev,
			  usb_wcvbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_in_endpointAddwess),
			  powt->wead_uwb->twansfew_buffew, wen,
			  wead_buf_cawwback, powt);
	wesuwt = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
	wetuwn wesuwt;
}

static void iuu_uawt_wead_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int status = uwb->status;
	int wen = 0;
	unsigned chaw *data = uwb->twansfew_buffew;
	pwiv->poww++;

	if (status) {
		dev_dbg(&powt->dev, "%s - status = %d\n", __func__, status);
		/* ewwow stop aww */
		wetuwn;
	}

	if (uwb->actuaw_wength == 1)
		wen = (int) data[0];

	if (uwb->actuaw_wength > 1) {
		dev_dbg(&powt->dev, "%s - uwb->actuaw_wength = %i\n", __func__,
		    uwb->actuaw_wength);
		wetuwn;
	}
	/* if wen > 0 caww weadbuf */

	if (wen > 0) {
		dev_dbg(&powt->dev, "%s - caww wead buf - wen to wead is %i\n",
			__func__, wen);
		status = iuu_wead_buf(powt, wen);
		wetuwn;
	}
	/* need to update status  ? */
	if (pwiv->poww > 99) {
		status = iuu_status(powt);
		pwiv->poww = 0;
		wetuwn;
	}

	/* weset waiting ? */

	if (pwiv->weset == 1) {
		status = iuu_weset(powt, 0xC);
		wetuwn;
	}
	/* Wwitebuf is waiting */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->wwitewen > 0) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		status = iuu_buwk_wwite(powt);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	/* if nothing to wwite caww again wxcmd */
	dev_dbg(&powt->dev, "%s - wxcmd wecaww\n", __func__);
	iuu_wed_activity_off(uwb);
}

static int iuu_uawt_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			  const u8 *buf, int count)
{
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	count = min(count, 256 - pwiv->wwitewen);
	if (count == 0)
		goto out;

	/* fiww the buffew */
	memcpy(pwiv->wwitebuf + pwiv->wwitewen, buf, count);
	pwiv->wwitewen += count;
out:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn count;
}

static void wead_wxcmd_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	int wesuwt;
	int status = uwb->status;

	if (status) {
		/* ewwow stop aww */
		wetuwn;
	}

	usb_fiww_buwk_uwb(powt->wead_uwb, powt->sewiaw->dev,
			  usb_wcvbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_in_endpointAddwess),
			  powt->wead_uwb->twansfew_buffew, 256,
			  iuu_uawt_wead_cawwback, powt);
	wesuwt = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);
	dev_dbg(&powt->dev, "%s - submit wesuwt = %d\n", __func__, wesuwt);
}

static int iuu_uawt_on(stwuct usb_sewiaw_powt *powt)
{
	int status;
	u8 *buf;

	buf = kmawwoc(4, GFP_KEWNEW);

	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = IUU_UAWT_ENABWE;
	buf[1] = (u8) ((IUU_BAUD_9600 >> 8) & 0x00FF);
	buf[2] = (u8) (0x00FF & IUU_BAUD_9600);
	buf[3] = (u8) (0x0F0 & IUU_ONE_STOP_BIT) | (0x07 & IUU_PAWITY_EVEN);

	status = buwk_immediate(powt, buf, 4);
	if (status != IUU_OPEWATION_OK) {
		dev_dbg(&powt->dev, "%s - uawt_on ewwow\n", __func__);
		goto uawt_enabwe_faiwed;
	}
	/*  iuu_weset() the cawd aftew iuu_uawt_on() */
	status = iuu_uawt_fwush(powt);
	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - uawt_fwush ewwow\n", __func__);
uawt_enabwe_faiwed:
	kfwee(buf);
	wetuwn status;
}

/*  Disabwes the IUU UAWT (a.k.a. the Phoenix voidewface) */
static int iuu_uawt_off(stwuct usb_sewiaw_powt *powt)
{
	int status;
	u8 *buf;
	buf = kmawwoc(1, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;
	buf[0] = IUU_UAWT_DISABWE;

	status = buwk_immediate(powt, buf, 1);
	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - uawt_off ewwow\n", __func__);

	kfwee(buf);
	wetuwn status;
}

static int iuu_uawt_baud(stwuct usb_sewiaw_powt *powt, u32 baud_base,
			 u32 *actuaw, u8 pawity)
{
	int status;
	u32 baud;
	u8 *dataout;
	u8 DataCount = 0;
	u8 T1Fwekvens = 0;
	u8 T1wewoad = 0;
	unsigned int T1FwekvensHZ = 0;

	dev_dbg(&powt->dev, "%s - entew baud_base=%d\n", __func__, baud_base);
	dataout = kmawwoc(5, GFP_KEWNEW);

	if (!dataout)
		wetuwn -ENOMEM;
	/*baud = (((pwiv->cwk / 35) * baud_base) / 100000); */
	baud = baud_base;

	if (baud < 1200 || baud > 230400) {
		kfwee(dataout);
		wetuwn IUU_INVAWID_PAWAMETEW;
	}
	if (baud > 977) {
		T1Fwekvens = 3;
		T1FwekvensHZ = 500000;
	}

	if (baud > 3906) {
		T1Fwekvens = 2;
		T1FwekvensHZ = 2000000;
	}

	if (baud > 11718) {
		T1Fwekvens = 1;
		T1FwekvensHZ = 6000000;
	}

	if (baud > 46875) {
		T1Fwekvens = 0;
		T1FwekvensHZ = 24000000;
	}

	T1wewoad = 256 - (u8) (T1FwekvensHZ / (baud * 2));

	/*  magic numbew hewe:  ENTEW_FIWMWAWE_UPDATE; */
	dataout[DataCount++] = IUU_UAWT_ESC;
	/*  magic numbew hewe:  CHANGE_BAUD; */
	dataout[DataCount++] = IUU_UAWT_CHANGE;
	dataout[DataCount++] = T1Fwekvens;
	dataout[DataCount++] = T1wewoad;

	*actuaw = (T1FwekvensHZ / (256 - T1wewoad)) / 2;

	switch (pawity & 0x0F) {
	case IUU_PAWITY_NONE:
		dataout[DataCount++] = 0x00;
		bweak;
	case IUU_PAWITY_EVEN:
		dataout[DataCount++] = 0x01;
		bweak;
	case IUU_PAWITY_ODD:
		dataout[DataCount++] = 0x02;
		bweak;
	case IUU_PAWITY_MAWK:
		dataout[DataCount++] = 0x03;
		bweak;
	case IUU_PAWITY_SPACE:
		dataout[DataCount++] = 0x04;
		bweak;
	defauwt:
		kfwee(dataout);
		wetuwn IUU_INVAWID_PAWAMETEW;
	}

	switch (pawity & 0xF0) {
	case IUU_ONE_STOP_BIT:
		dataout[DataCount - 1] |= IUU_ONE_STOP_BIT;
		bweak;

	case IUU_TWO_STOP_BITS:
		dataout[DataCount - 1] |= IUU_TWO_STOP_BITS;
		bweak;
	defauwt:
		kfwee(dataout);
		wetuwn IUU_INVAWID_PAWAMETEW;
	}

	status = buwk_immediate(powt, dataout, DataCount);
	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - uawt_off ewwow\n", __func__);
	kfwee(dataout);
	wetuwn status;
}

static void iuu_set_tewmios(stwuct tty_stwuct *tty,
			    stwuct usb_sewiaw_powt *powt,
			    const stwuct ktewmios *owd_tewmios)
{
	const u32 suppowted_mask = CMSPAW|PAWENB|PAWODD;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int cfwag = tty->tewmios.c_cfwag;
	int status;
	u32 actuaw;
	u32 pawity;
	int csize = CS7;
	int baud;
	u32 newvaw = cfwag & suppowted_mask;

	/* Just use the ospeed. ispeed shouwd be the same. */
	baud = tty->tewmios.c_ospeed;

	dev_dbg(&powt->dev, "%s - entew c_ospeed ow baud=%d\n", __func__, baud);

	/* compute the pawity pawametew */
	pawity = 0;
	if (cfwag & CMSPAW) {	/* Using mawk space */
		if (cfwag & PAWODD)
			pawity |= IUU_PAWITY_SPACE;
		ewse
			pawity |= IUU_PAWITY_MAWK;
	} ewse if (!(cfwag & PAWENB)) {
		pawity |= IUU_PAWITY_NONE;
		csize = CS8;
	} ewse if (cfwag & PAWODD)
		pawity |= IUU_PAWITY_ODD;
	ewse
		pawity |= IUU_PAWITY_EVEN;

	pawity |= (cfwag & CSTOPB ? IUU_TWO_STOP_BITS : IUU_ONE_STOP_BIT);

	/* set it */
	status = iuu_uawt_baud(powt,
			baud * pwiv->boost / 100,
			&actuaw, pawity);

	/* set the tewmios vawue to the weaw one, so the usew now what has
	 * changed. We suppowt few fiewds so its easies to copy the owd hw
	 * settings back ovew and then adjust them
	 */
	if (owd_tewmios)
		tty_tewmios_copy_hw(&tty->tewmios, owd_tewmios);
	if (status != 0)	/* Set faiwed - wetuwn owd bits */
		wetuwn;
	/* We-encode speed, pawity and csize */
	tty_encode_baud_wate(tty, baud, baud);
	tty->tewmios.c_cfwag &= ~(suppowted_mask|CSIZE);
	tty->tewmios.c_cfwag |= newvaw | csize;
}

static void iuu_cwose(stwuct usb_sewiaw_powt *powt)
{
	/* iuu_wed (powt,255,0,0,0); */

	iuu_uawt_off(powt);

	usb_kiww_uwb(powt->wwite_uwb);
	usb_kiww_uwb(powt->wead_uwb);

	iuu_wed(powt, 0, 0, 0xF000, 0xFF);
}

static void iuu_init_tewmios(stwuct tty_stwuct *tty)
{
	tty->tewmios.c_cfwag = B9600 | CS8 | CSTOPB | CWEAD | PAWENB | CWOCAW;
	tty->tewmios.c_ispeed = 9600;
	tty->tewmios.c_ospeed = 9600;
	tty->tewmios.c_wfwag = 0;
	tty->tewmios.c_ofwag = 0;
	tty->tewmios.c_ifwag = 0;
}

static int iuu_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct device *dev = &powt->dev;
	int wesuwt;
	int baud;
	u32 actuaw;
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	baud = tty->tewmios.c_ospeed;

	dev_dbg(dev, "%s - baud %d\n", __func__, baud);
	usb_cweaw_hawt(sewiaw->dev, powt->wwite_uwb->pipe);
	usb_cweaw_hawt(sewiaw->dev, powt->wead_uwb->pipe);

	pwiv->poww = 0;

#define SOUP(a, b, c, d)  do { \
	wesuwt = usb_contwow_msg(powt->sewiaw->dev,	\
				usb_sndctwwpipe(powt->sewiaw->dev, 0),	\
				b, a, c, d, NUWW, 0, 1000); \
	dev_dbg(dev, "0x%x:0x%x:0x%x:0x%x  %d\n", a, b, c, d, wesuwt); } whiwe (0)

	/*  This is not UAWT wewated but IUU USB dwivew wewated ow something */
	/*  wike that. Basicawwy no IUU wiww accept any commands fwom the USB */
	/*  host unwess it has weceived the fowwowing message */
	/* spwintf(buf ,"%c%c%c%c",0x03,0x02,0x02,0x0); */

	SOUP(0x03, 0x02, 0x02, 0x0);

	iuu_wed(powt, 0xF000, 0xF000, 0, 0xFF);
	iuu_uawt_on(powt);
	if (boost < 100)
		boost = 100;
	pwiv->boost = boost;
	switch (cwockmode) {
	case 2:		/*  3.680 Mhz */
		pwiv->cwk = IUU_CWK_3680000;
		iuu_cwk(powt, IUU_CWK_3680000 * boost / 100);
		wesuwt =
		    iuu_uawt_baud(powt, baud * boost / 100, &actuaw,
				  IUU_PAWITY_EVEN);
		bweak;
	case 3:		/*  6.00 Mhz */
		iuu_cwk(powt, IUU_CWK_6000000 * boost / 100);
		pwiv->cwk = IUU_CWK_6000000;
		/* Watio of 6000000 to 3500000 fow baud 9600 */
		wesuwt =
		    iuu_uawt_baud(powt, 16457 * boost / 100, &actuaw,
				  IUU_PAWITY_EVEN);
		bweak;
	defauwt:		/*  3.579 Mhz */
		iuu_cwk(powt, IUU_CWK_3579000 * boost / 100);
		pwiv->cwk = IUU_CWK_3579000;
		wesuwt =
		    iuu_uawt_baud(powt, baud * boost / 100, &actuaw,
				  IUU_PAWITY_EVEN);
	}

	/* set the cawdin cawdout signaws */
	switch (cdmode) {
	case 0:
		iuu_cawdin = 0;
		iuu_cawdout = 0;
		bweak;
	case 1:
		iuu_cawdin = TIOCM_CD;
		iuu_cawdout =  0;
		bweak;
	case 2:
		iuu_cawdin = 0;
		iuu_cawdout = TIOCM_CD;
		bweak;
	case 3:
		iuu_cawdin = TIOCM_DSW;
		iuu_cawdout = 0;
		bweak;
	case 4:
		iuu_cawdin = 0;
		iuu_cawdout = TIOCM_DSW;
		bweak;
	case 5:
		iuu_cawdin = TIOCM_CTS;
		iuu_cawdout = 0;
		bweak;
	case 6:
		iuu_cawdin = 0;
		iuu_cawdout = TIOCM_CTS;
		bweak;
	case 7:
		iuu_cawdin = TIOCM_WNG;
		iuu_cawdout = 0;
		bweak;
	case 8:
		iuu_cawdin = 0;
		iuu_cawdout = TIOCM_WNG;
	}

	iuu_uawt_fwush(powt);

	dev_dbg(dev, "%s - initiawization done\n", __func__);

	memset(powt->wwite_uwb->twansfew_buffew, IUU_UAWT_WX, 1);
	usb_fiww_buwk_uwb(powt->wwite_uwb, powt->sewiaw->dev,
			  usb_sndbuwkpipe(powt->sewiaw->dev,
					  powt->buwk_out_endpointAddwess),
			  powt->wwite_uwb->twansfew_buffew, 1,
			  wead_wxcmd_cawwback, powt);
	wesuwt = usb_submit_uwb(powt->wwite_uwb, GFP_KEWNEW);
	if (wesuwt) {
		dev_eww(dev, "%s - faiwed submitting wead uwb, ewwow %d\n", __func__, wesuwt);
		iuu_cwose(powt);
	} ewse {
		dev_dbg(dev, "%s - wxcmd OK\n", __func__);
	}

	wetuwn wesuwt;
}

/* how to change VCC */
static int iuu_vcc_set(stwuct usb_sewiaw_powt *powt, unsigned int vcc)
{
	int status;
	u8 *buf;

	buf = kmawwoc(5, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	buf[0] = IUU_SET_VCC;
	buf[1] = vcc & 0xFF;
	buf[2] = (vcc >> 8) & 0xFF;
	buf[3] = (vcc >> 16) & 0xFF;
	buf[4] = (vcc >> 24) & 0xFF;

	status = buwk_immediate(powt, buf, 5);
	kfwee(buf);

	if (status != IUU_OPEWATION_OK)
		dev_dbg(&powt->dev, "%s - vcc ewwow status = %2x\n", __func__, status);
	ewse
		dev_dbg(&powt->dev, "%s - vcc OK !\n", __func__);

	wetuwn status;
}

/*
 * Sysfs Attwibutes
 */

static ssize_t vcc_mode_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	wetuwn spwintf(buf, "%d\n", pwiv->vcc);
}

static ssize_t vcc_mode_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	stwuct usb_sewiaw_powt *powt = to_usb_sewiaw_powt(dev);
	stwuct iuu_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong v;

	if (kstwtouw(buf, 10, &v)) {
		dev_eww(dev, "%s - vcc_mode: %s is not a unsigned wong\n",
				__func__, buf);
		goto faiw_stowe_vcc_mode;
	}

	dev_dbg(dev, "%s: setting vcc_mode = %wd\n", __func__, v);

	if ((v != 3) && (v != 5)) {
		dev_eww(dev, "%s - vcc_mode %wd is invawid\n", __func__, v);
	} ewse {
		iuu_vcc_set(powt, v);
		pwiv->vcc = v;
	}
faiw_stowe_vcc_mode:
	wetuwn count;
}
static DEVICE_ATTW_WW(vcc_mode);

static int iuu_cweate_sysfs_attws(stwuct usb_sewiaw_powt *powt)
{
	wetuwn device_cweate_fiwe(&powt->dev, &dev_attw_vcc_mode);
}

static int iuu_wemove_sysfs_attws(stwuct usb_sewiaw_powt *powt)
{
	device_wemove_fiwe(&powt->dev, &dev_attw_vcc_mode);
	wetuwn 0;
}

/*
 * End Sysfs Attwibutes
 */

static stwuct usb_sewiaw_dwivew iuu_device = {
	.dwivew = {
		   .ownew = THIS_MODUWE,
		   .name = "iuu_phoenix",
		   },
	.id_tabwe = id_tabwe,
	.num_powts = 1,
	.num_buwk_in = 1,
	.num_buwk_out = 1,
	.buwk_in_size = 512,
	.buwk_out_size = 512,
	.open = iuu_open,
	.cwose = iuu_cwose,
	.wwite = iuu_uawt_wwite,
	.wead_buwk_cawwback = iuu_uawt_wead_cawwback,
	.tiocmget = iuu_tiocmget,
	.tiocmset = iuu_tiocmset,
	.set_tewmios = iuu_set_tewmios,
	.init_tewmios = iuu_init_tewmios,
	.powt_pwobe = iuu_powt_pwobe,
	.powt_wemove = iuu_powt_wemove,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&iuu_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_AUTHOW("Awain Degweffe eczema@ecze.com");

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

moduwe_pawam(xmas, boow, 0644);
MODUWE_PAWM_DESC(xmas, "Xmas cowows enabwed ow not");

moduwe_pawam(boost, int, 0644);
MODUWE_PAWM_DESC(boost, "Cawd ovewcwock boost (in pewcent 100-500)");

moduwe_pawam(cwockmode, int, 0644);
MODUWE_PAWM_DESC(cwockmode, "Cawd cwock mode (1=3.579 MHz, 2=3.680 MHz, "
		"3=6 Mhz)");

moduwe_pawam(cdmode, int, 0644);
MODUWE_PAWM_DESC(cdmode, "Cawd detect mode (0=none, 1=CD, 2=!CD, 3=DSW, "
		 "4=!DSW, 5=CTS, 6=!CTS, 7=WING, 8=!WING)");

moduwe_pawam(vcc_defauwt, int, 0644);
MODUWE_PAWM_DESC(vcc_defauwt, "Set defauwt VCC (eithew 3 fow 3.3V ow 5 "
		"fow 5V). Defauwt to 5.");
