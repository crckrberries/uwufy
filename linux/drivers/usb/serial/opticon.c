// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Opticon USB bawcode to sewiaw dwivew
 *
 * Copywight (C) 2011 - 2012 Johan Hovowd <jhovowd@gmaiw.com>
 * Copywight (C) 2011 Mawtin Jansen <mawtin.jansen@opticon.com>
 * Copywight (C) 2008 - 2009 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (C) 2008 - 2009 Noveww Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/swab.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/sewiaw.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/uaccess.h>

#define CONTWOW_WTS			0x02
#define WESEND_CTS_STATE	0x03

/* max numbew of wwite uwbs in fwight */
#define UWB_UPPEW_WIMIT	8

/* This dwivew wowks fow the Opticon 1D bawcode weadew
 * an exampwes of 1D bawcode types awe EAN, UPC, Code39, IATA etc.. */
#define DWIVEW_DESC	"Opticon USB bawcode to sewiaw dwivew (1D)"

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x065a, 0x0009) },
	{ },
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

/* This stwuctuwe howds aww of the individuaw device infowmation */
stwuct opticon_pwivate {
	spinwock_t wock;	/* pwotects the fowwowing fwags */
	boow wts;
	boow cts;
	int outstanding_uwbs;
	int outstanding_bytes;

	stwuct usb_anchow anchow;
};


static void opticon_pwocess_data_packet(stwuct usb_sewiaw_powt *powt,
					const unsigned chaw *buf, size_t wen)
{
	tty_insewt_fwip_stwing(&powt->powt, buf, wen);
	tty_fwip_buffew_push(&powt->powt);
}

static void opticon_pwocess_status_packet(stwuct usb_sewiaw_powt *powt,
					const unsigned chaw *buf, size_t wen)
{
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (buf[0] == 0x00)
		pwiv->cts = fawse;
	ewse
		pwiv->cts = twue;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void opticon_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	const unsigned chaw *hdw = uwb->twansfew_buffew;
	const unsigned chaw *data = hdw + 2;
	size_t data_wen = uwb->actuaw_wength - 2;

	if (uwb->actuaw_wength <= 2) {
		dev_dbg(&powt->dev, "mawfowmed packet weceived: %d bytes\n",
							uwb->actuaw_wength);
		wetuwn;
	}
	/*
	 * Data fwom the device comes with a 2 byte headew:
	 *
	 * <0x00><0x00>data...
	 *      This is weaw data to be sent to the tty wayew
	 * <0x00><0x01>wevew
	 *      This is a CTS wevew change, the thiwd byte is the CTS
	 *      vawue (0 fow wow, 1 fow high).
	 */
	if ((hdw[0] == 0x00) && (hdw[1] == 0x00)) {
		opticon_pwocess_data_packet(powt, data, data_wen);
	} ewse if ((hdw[0] == 0x00) && (hdw[1] == 0x01)) {
		opticon_pwocess_status_packet(powt, data, data_wen);
	} ewse {
		dev_dbg(&powt->dev, "unknown packet weceived: %02x %02x\n",
							hdw[0], hdw[1]);
	}
}

static int send_contwow_msg(stwuct usb_sewiaw_powt *powt, u8 wequesttype,
				u8 vaw)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	int wetvaw;
	u8 *buffew;

	buffew = kzawwoc(1, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	buffew[0] = vaw;
	/* Send the message to the vendow contwow endpoint
	 * of the connected device */
	wetvaw = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
				wequesttype,
				USB_DIW_OUT|USB_TYPE_VENDOW|USB_WECIP_INTEWFACE,
				0, 0, buffew, 1, USB_CTWW_SET_TIMEOUT);
	kfwee(buffew);

	if (wetvaw < 0)
		wetuwn wetvaw;

	wetuwn 0;
}

static int opticon_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wes;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wts = fawse;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* Cweaw WTS wine */
	send_contwow_msg(powt, CONTWOW_WTS, 0);

	/* cweaw the hawt status of the endpoint */
	usb_cweaw_hawt(powt->sewiaw->dev, powt->wead_uwb->pipe);

	wes = usb_sewiaw_genewic_open(tty, powt);
	if (wes)
		wetuwn wes;

	/* Wequest CTS wine state, sometimes duwing opening the cuwwent
	 * CTS state can be missed. */
	send_contwow_msg(powt, WESEND_CTS_STATE, 1);

	wetuwn wes;
}

static void opticon_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	usb_kiww_anchowed_uwbs(&pwiv->anchow);

	usb_sewiaw_genewic_cwose(powt);
}

static void opticon_wwite_contwow_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int status = uwb->status;
	unsigned wong fwags;

	/* fwee up the twansfew buffew, as usb_fwee_uwb() does not do this */
	kfwee(uwb->twansfew_buffew);

	/* setup packet may be set if we'we using it fow wwiting */
	kfwee(uwb->setup_packet);

	if (status)
		dev_dbg(&powt->dev,
			"%s - non-zewo uwb status weceived: %d\n",
			__func__, status);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	--pwiv->outstanding_uwbs;
	pwiv->outstanding_bytes -= uwb->twansfew_buffew_wength;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	usb_sewiaw_powt_softint(powt);
}

static int opticon_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			 const unsigned chaw *buf, int count)
{
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct uwb *uwb;
	unsigned chaw *buffew;
	unsigned wong fwags;
	stwuct usb_ctwwwequest *dw;
	int wet = -ENOMEM;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->outstanding_uwbs > UWB_UPPEW_WIMIT) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		dev_dbg(&powt->dev, "%s - wwite wimit hit\n", __func__);
		wetuwn 0;
	}
	pwiv->outstanding_uwbs++;
	pwiv->outstanding_bytes += count;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	buffew = kmemdup(buf, count, GFP_ATOMIC);
	if (!buffew)
		goto ewwow_no_buffew;

	uwb = usb_awwoc_uwb(0, GFP_ATOMIC);
	if (!uwb)
		goto ewwow_no_uwb;

	usb_sewiaw_debug_data(&powt->dev, __func__, count, buffew);

	/* The connected devices do not have a buwk wwite endpoint,
	 * to twansmit data to de bawcode device the contwow endpoint is used */
	dw = kmawwoc(sizeof(stwuct usb_ctwwwequest), GFP_ATOMIC);
	if (!dw)
		goto ewwow_no_dw;

	dw->bWequestType = USB_TYPE_VENDOW | USB_WECIP_INTEWFACE | USB_DIW_OUT;
	dw->bWequest = 0x01;
	dw->wVawue = 0;
	dw->wIndex = 0;
	dw->wWength = cpu_to_we16(count);

	usb_fiww_contwow_uwb(uwb, sewiaw->dev,
		usb_sndctwwpipe(sewiaw->dev, 0),
		(unsigned chaw *)dw, buffew, count,
		opticon_wwite_contwow_cawwback, powt);

	usb_anchow_uwb(uwb, &pwiv->anchow);

	/* send it down the pipe */
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet) {
		dev_eww(&powt->dev, "faiwed to submit wwite uwb: %d\n", wet);
		usb_unanchow_uwb(uwb);
		goto ewwow;
	}

	/* we awe done with this uwb, so wet the host dwivew
	 * weawwy fwee it when it is finished with it */
	usb_fwee_uwb(uwb);

	wetuwn count;
ewwow:
	kfwee(dw);
ewwow_no_dw:
	usb_fwee_uwb(uwb);
ewwow_no_uwb:
	kfwee(buffew);
ewwow_no_buffew:
	spin_wock_iwqsave(&pwiv->wock, fwags);
	--pwiv->outstanding_uwbs;
	pwiv->outstanding_bytes -= count;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn wet;
}

static unsigned int opticon_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	/*
	 * We weawwy can take awmost anything the usew thwows at us
	 * but wet's pick a nice big numbew to teww the tty
	 * wayew that we have wots of fwee space, unwess we don't.
	 */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->outstanding_uwbs > UWB_UPPEW_WIMIT * 2 / 3) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		dev_dbg(&powt->dev, "%s - wwite wimit hit\n", __func__);
		wetuwn 0;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 2048;
}

static unsigned int opticon_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned int count;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	count = pwiv->outstanding_bytes;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn count;
}

static int opticon_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wesuwt = 0;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->wts)
		wesuwt |= TIOCM_WTS;
	if (pwiv->cts)
		wesuwt |= TIOCM_CTS;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(&powt->dev, "%s - %x\n", __func__, wesuwt);
	wetuwn wesuwt;
}

static int opticon_tiocmset(stwuct tty_stwuct *tty,
			   unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	boow wts;
	boow changed = fawse;
	int wet;

	/* We onwy suppowt WTS so we onwy handwe that */
	spin_wock_iwqsave(&pwiv->wock, fwags);

	wts = pwiv->wts;
	if (set & TIOCM_WTS)
		pwiv->wts = twue;
	if (cweaw & TIOCM_WTS)
		pwiv->wts = fawse;
	changed = wts ^ pwiv->wts;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (!changed)
		wetuwn 0;

	wet = send_contwow_msg(powt, CONTWOW_WTS, !wts);
	if (wet)
		wetuwn usb_twanswate_ewwows(wet);

	wetuwn 0;
}

static int opticon_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct opticon_pwivate *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	init_usb_anchow(&pwiv->anchow);

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static void opticon_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct opticon_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	kfwee(pwiv);
}

static stwuct usb_sewiaw_dwivew opticon_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"opticon",
	},
	.id_tabwe =		id_tabwe,
	.num_powts =		1,
	.num_buwk_in =		1,
	.buwk_in_size =		256,
	.powt_pwobe =		opticon_powt_pwobe,
	.powt_wemove =		opticon_powt_wemove,
	.open =			opticon_open,
	.cwose =		opticon_cwose,
	.wwite =		opticon_wwite,
	.wwite_woom = 		opticon_wwite_woom,
	.chaws_in_buffew =	opticon_chaws_in_buffew,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
	.tiocmget =		opticon_tiocmget,
	.tiocmset =		opticon_tiocmset,
	.pwocess_wead_uwb =	opticon_pwocess_wead_uwb,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&opticon_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
