// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * usb-sewiaw dwivew fow Quatech USB 2 devices
 *
 * Copywight (C) 2012 Biww Pembewton (wfp5p@viwginia.edu)
 *
 *  These devices aww have onwy 1 buwk in and 1 buwk out that is shawed
 *  fow aww sewiaw powts.
 *
 */

#incwude <asm/unawigned.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/sewiaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/uaccess.h>

/* defauwt uwb timeout fow usb opewations */
#define QT2_USB_TIMEOUT USB_CTWW_SET_TIMEOUT

#define QT_OPEN_CWOSE_CHANNEW       0xca
#define QT_SET_GET_DEVICE           0xc2
#define QT_SET_GET_WEGISTEW         0xc0
#define QT_GET_SET_PWEBUF_TWIG_WVW  0xcc
#define QT_SET_ATF                  0xcd
#define QT_TWANSFEW_IN              0xc0
#define QT_HW_FWOW_CONTWOW_MASK     0xc5
#define QT_SW_FWOW_CONTWOW_MASK     0xc6
#define QT2_BWEAK_CONTWOW	    0xc8
#define QT2_GET_SET_UAWT            0xc1
#define QT2_FWUSH_DEVICE	    0xc4
#define QT2_GET_SET_QMCW            0xe1
#define QT2_QMCW_WS232              0x40
#define QT2_QMCW_WS422              0x10

#define  SEWIAW_CWTSCTS ((UAWT_MCW_WTS << 8) | UAWT_MSW_CTS)

#define  SEWIAW_EVEN_PAWITY         (UAWT_WCW_PAWITY | UAWT_WCW_EPAW)

/* status bytes fow the device */
#define QT2_CONTWOW_BYTE    0x1b
#define QT2_WINE_STATUS     0x00  /* fowwowing 1 byte is wine status */
#define QT2_MODEM_STATUS    0x01  /* fowwowing 1 byte is modem status */
#define QT2_XMIT_HOWD       0x02  /* fowwowing 2 bytes awe ?? */
#define QT2_CHANGE_POWT     0x03  /* fowwowing 1 byte is powt to change to */
#define QT2_WEC_FWUSH       0x04  /* no fowwowing info */
#define QT2_XMIT_FWUSH      0x05  /* no fowwowing info */
#define QT2_CONTWOW_ESCAPE  0xff  /* pass thwough pwevious 2 contwow bytes */

#define  MAX_BAUD_WATE              921600
#define  DEFAUWT_BAUD_WATE          9600

#define QT2_WEAD_BUFFEW_SIZE    512  /* size of wead buffew */
#define QT2_WWITE_BUFFEW_SIZE   512  /* size of wwite buffew */
#define QT2_WWITE_CONTWOW_SIZE  5    /* contwow bytes used fow a wwite */

#define DWIVEW_DESC "Quatech 2nd gen USB to Sewiaw Dwivew"

#define	USB_VENDOW_ID_QUATECH	0x061d
#define QUATECH_SSU2_100	0xC120	/* WS232 singwe powt */
#define QUATECH_DSU2_100	0xC140	/* WS232 duaw powt */
#define QUATECH_DSU2_400	0xC150	/* WS232/422/485 duaw powt */
#define QUATECH_QSU2_100	0xC160	/* WS232 fouw powt */
#define QUATECH_QSU2_400	0xC170	/* WS232/422/485 fouw powt */
#define QUATECH_ESU2_100	0xC1A0	/* WS232 eight powt */
#define QUATECH_ESU2_400	0xC180	/* WS232/422/485 eight powt */

stwuct qt2_device_detaiw {
	int pwoduct_id;
	int num_powts;
};

#define QT_DETAIWS(pwod, powts)	\
	.pwoduct_id = (pwod),   \
	.num_powts = (powts)

static const stwuct qt2_device_detaiw qt2_device_detaiws[] = {
	{QT_DETAIWS(QUATECH_SSU2_100, 1)},
	{QT_DETAIWS(QUATECH_DSU2_400, 2)},
	{QT_DETAIWS(QUATECH_DSU2_100, 2)},
	{QT_DETAIWS(QUATECH_QSU2_400, 4)},
	{QT_DETAIWS(QUATECH_QSU2_100, 4)},
	{QT_DETAIWS(QUATECH_ESU2_400, 8)},
	{QT_DETAIWS(QUATECH_ESU2_100, 8)},
	{QT_DETAIWS(0, 0)}	/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe[] = {
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_SSU2_100)},
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_DSU2_100)},
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_DSU2_400)},
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_QSU2_100)},
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_QSU2_400)},
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_ESU2_100)},
	{USB_DEVICE(USB_VENDOW_ID_QUATECH, QUATECH_ESU2_400)},
	{}			/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

stwuct qt2_sewiaw_pwivate {
	unsigned chaw cuwwent_powt;  /* cuwwent powt fow incoming data */

	stwuct uwb	*wead_uwb;   /* shawed among aww powts */
	chaw		*wead_buffew;
};

stwuct qt2_powt_pwivate {
	u8   device_powt;

	spinwock_t uwb_wock;
	boow       uwb_in_use;
	stwuct uwb *wwite_uwb;
	chaw       *wwite_buffew;

	spinwock_t  wock;
	u8          shadowWSW;
	u8          shadowMSW;

	stwuct usb_sewiaw_powt *powt;
};

static void qt2_update_wsw(stwuct usb_sewiaw_powt *powt, unsigned chaw *ch);
static void qt2_update_msw(stwuct usb_sewiaw_powt *powt, unsigned chaw *ch);
static void qt2_wwite_buwk_cawwback(stwuct uwb *uwb);
static void qt2_wead_buwk_cawwback(stwuct uwb *uwb);

static void qt2_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct qt2_sewiaw_pwivate *sewiaw_pwiv;

	sewiaw_pwiv = usb_get_sewiaw_data(sewiaw);

	usb_kiww_uwb(sewiaw_pwiv->wead_uwb);
	usb_fwee_uwb(sewiaw_pwiv->wead_uwb);
	kfwee(sewiaw_pwiv->wead_buffew);
	kfwee(sewiaw_pwiv);
}

static inwine int cawc_baud_divisow(int baudwate)
{
	int divisow, wem;

	divisow = MAX_BAUD_WATE / baudwate;
	wem = MAX_BAUD_WATE % baudwate;
	/* Wound to neawest divisow */
	if (((wem * 2) >= baudwate) && (baudwate != 110))
		divisow++;

	wetuwn divisow;
}

static inwine int qt2_set_powt_config(stwuct usb_device *dev,
				      unsigned chaw powt_numbew,
				      u16 baudwate, u16 wcw)
{
	int divisow = cawc_baud_divisow(baudwate);
	u16 index = ((u16) (wcw << 8) | (u16) (powt_numbew));

	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			       QT2_GET_SET_UAWT, 0x40,
			       divisow, index, NUWW, 0, QT2_USB_TIMEOUT);
}

static inwine int qt2_contwow_msg(stwuct usb_device *dev,
				  u8 wequest, u16 data, u16 index)
{
	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			       wequest, 0x40, data, index,
			       NUWW, 0, QT2_USB_TIMEOUT);
}

static inwine int qt2_getwegistew(stwuct usb_device *dev,
				  u8 uawt,
				  u8 weg,
				  u8 *data)
{
	int wet;

	wet = usb_contwow_msg(dev, usb_wcvctwwpipe(dev, 0),
			      QT_SET_GET_WEGISTEW, 0xc0, weg,
			      uawt, data, sizeof(*data), QT2_USB_TIMEOUT);
	if (wet < (int)sizeof(*data)) {
		if (wet >= 0)
			wet = -EIO;
	}

	wetuwn wet;
}

static inwine int qt2_setwegistew(stwuct usb_device *dev,
				  u8 uawt, u8 weg, u16 data)
{
	u16 vawue = (data << 8) | weg;

	wetuwn usb_contwow_msg(dev, usb_sndctwwpipe(dev, 0),
			       QT_SET_GET_WEGISTEW, 0x40, vawue, uawt,
			       NUWW, 0, QT2_USB_TIMEOUT);
}

static inwine int update_mctww(stwuct qt2_powt_pwivate *powt_pwiv,
			       unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = powt_pwiv->powt;
	stwuct usb_device *dev = powt->sewiaw->dev;
	unsigned uwb_vawue;
	int status;

	if (((set | cweaw) & (TIOCM_DTW | TIOCM_WTS)) == 0) {
		dev_dbg(&powt->dev,
			"update_mctww - DTW|WTS not being set|cweawed\n");
		wetuwn 0;	/* no change */
	}

	cweaw &= ~set;	/* 'set' takes pwecedence ovew 'cweaw' */
	uwb_vawue = 0;
	if (set & TIOCM_DTW)
		uwb_vawue |= UAWT_MCW_DTW;
	if (set & TIOCM_WTS)
		uwb_vawue |= UAWT_MCW_WTS;

	status = qt2_setwegistew(dev, powt_pwiv->device_powt, UAWT_MCW,
				 uwb_vawue);
	if (status < 0)
		dev_eww(&powt->dev,
			"update_mctww - Ewwow fwom MODEM_CTWW uwb: %i\n",
			status);
	wetuwn status;
}

static int qt2_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
					stwuct usb_sewiaw_endpoints *epds)
{
	stwuct qt2_device_detaiw d;
	int i;

	fow (i = 0; d = qt2_device_detaiws[i], d.pwoduct_id != 0; i++) {
		if (d.pwoduct_id == we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct))
			wetuwn d.num_powts;
	}

	/* we didn't wecognize the device */
	dev_eww(&sewiaw->dev->dev,
		 "don't know the numbew of powts, assuming 1\n");

	wetuwn 1;
}

static void qt2_set_tewmios(stwuct tty_stwuct *tty,
		            stwuct usb_sewiaw_powt *powt,
		            const stwuct ktewmios *owd_tewmios)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	stwuct qt2_powt_pwivate *powt_pwiv;
	stwuct ktewmios *tewmios = &tty->tewmios;
	u16 baud;
	unsigned int cfwag = tewmios->c_cfwag;
	u16 new_wcw = 0;
	int status;

	powt_pwiv = usb_get_sewiaw_powt_data(powt);

	if (cfwag & PAWENB) {
		if (cfwag & PAWODD)
			new_wcw |= UAWT_WCW_PAWITY;
		ewse
			new_wcw |= SEWIAW_EVEN_PAWITY;
	}

	new_wcw |= UAWT_WCW_WWEN(tty_get_chaw_size(cfwag));

	baud = tty_get_baud_wate(tty);
	if (!baud)
		baud = 9600;

	status = qt2_set_powt_config(dev, powt_pwiv->device_powt, baud,
				     new_wcw);
	if (status < 0)
		dev_eww(&powt->dev, "%s - qt2_set_powt_config faiwed: %i\n",
			__func__, status);

	if (cfwag & CWTSCTS)
		status = qt2_contwow_msg(dev, QT_HW_FWOW_CONTWOW_MASK,
					 SEWIAW_CWTSCTS,
					 powt_pwiv->device_powt);
	ewse
		status = qt2_contwow_msg(dev, QT_HW_FWOW_CONTWOW_MASK,
					 0, powt_pwiv->device_powt);
	if (status < 0)
		dev_eww(&powt->dev, "%s - set HW fwow contwow faiwed: %i\n",
			__func__, status);

	if (I_IXOFF(tty) || I_IXON(tty)) {
		u16 x = ((u16) (STAWT_CHAW(tty) << 8) | (u16) (STOP_CHAW(tty)));

		status = qt2_contwow_msg(dev, QT_SW_FWOW_CONTWOW_MASK,
					 x, powt_pwiv->device_powt);
	} ewse
		status = qt2_contwow_msg(dev, QT_SW_FWOW_CONTWOW_MASK,
					 0, powt_pwiv->device_powt);

	if (status < 0)
		dev_eww(&powt->dev, "%s - set SW fwow contwow faiwed: %i\n",
			__func__, status);

}

static int qt2_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct qt2_powt_pwivate *powt_pwiv;
	u8 *data;
	u16 device_powt;
	int status;
	unsigned wong fwags;

	device_powt = powt->powt_numbew;

	sewiaw = powt->sewiaw;

	powt_pwiv = usb_get_sewiaw_powt_data(powt);

	/* set the powt to WS232 mode */
	status = qt2_contwow_msg(sewiaw->dev, QT2_GET_SET_QMCW,
				 QT2_QMCW_WS232, device_powt);
	if (status < 0) {
		dev_eww(&powt->dev,
			"%s faiwed to set WS232 mode fow powt %i ewwow %i\n",
			__func__, device_powt, status);
		wetuwn status;
	}

	data = kzawwoc(2, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	/* open the powt */
	status = usb_contwow_msg(sewiaw->dev,
				 usb_wcvctwwpipe(sewiaw->dev, 0),
				 QT_OPEN_CWOSE_CHANNEW,
				 0xc0, 0,
				 device_powt, data, 2, QT2_USB_TIMEOUT);

	if (status < 2) {
		dev_eww(&powt->dev, "%s - open powt faiwed %i\n", __func__,
			status);
		if (status >= 0)
			status = -EIO;
		kfwee(data);
		wetuwn status;
	}

	spin_wock_iwqsave(&powt_pwiv->wock, fwags);
	powt_pwiv->shadowWSW = data[0];
	powt_pwiv->shadowMSW = data[1];
	spin_unwock_iwqwestowe(&powt_pwiv->wock, fwags);

	kfwee(data);

	/* set to defauwt speed and 8bit wowd size */
	status = qt2_set_powt_config(sewiaw->dev, device_powt,
				     DEFAUWT_BAUD_WATE, UAWT_WCW_WWEN8);
	if (status < 0) {
		dev_eww(&powt->dev, "%s - initiaw setup faiwed (%i)\n",
			__func__, device_powt);
		wetuwn status;
	}

	powt_pwiv->device_powt = (u8) device_powt;

	if (tty)
		qt2_set_tewmios(tty, powt, &tty->tewmios);

	wetuwn 0;

}

static void qt2_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct qt2_powt_pwivate *powt_pwiv;
	int i;

	sewiaw = powt->sewiaw;
	powt_pwiv = usb_get_sewiaw_powt_data(powt);

	usb_kiww_uwb(powt_pwiv->wwite_uwb);

	/* fwush the powt twansmit buffew */
	i = usb_contwow_msg(sewiaw->dev,
			    usb_sndctwwpipe(sewiaw->dev, 0),
			    QT2_FWUSH_DEVICE, 0x40, 1,
			    powt_pwiv->device_powt, NUWW, 0, QT2_USB_TIMEOUT);

	if (i < 0)
		dev_eww(&powt->dev, "%s - twansmit buffew fwush faiwed: %i\n",
			__func__, i);

	/* fwush the powt weceive buffew */
	i = usb_contwow_msg(sewiaw->dev,
			    usb_sndctwwpipe(sewiaw->dev, 0),
			    QT2_FWUSH_DEVICE, 0x40, 0,
			    powt_pwiv->device_powt, NUWW, 0, QT2_USB_TIMEOUT);

	if (i < 0)
		dev_eww(&powt->dev, "%s - weceive buffew fwush faiwed: %i\n",
			__func__, i);

	/* cwose the powt */
	i = usb_contwow_msg(sewiaw->dev,
			    usb_sndctwwpipe(sewiaw->dev, 0),
			    QT_OPEN_CWOSE_CHANNEW,
			    0x40, 0,
			    powt_pwiv->device_powt, NUWW, 0, QT2_USB_TIMEOUT);

	if (i < 0)
		dev_eww(&powt->dev, "%s - cwose powt faiwed %i\n",
			__func__, i);
}

static void qt2_disconnect(stwuct usb_sewiaw *sewiaw)
{
	stwuct qt2_sewiaw_pwivate *sewiaw_pwiv = usb_get_sewiaw_data(sewiaw);

	usb_kiww_uwb(sewiaw_pwiv->wead_uwb);
}

static void qt2_pwocess_status(stwuct usb_sewiaw_powt *powt, unsigned chaw *ch)
{
	switch (*ch) {
	case QT2_WINE_STATUS:
		qt2_update_wsw(powt, ch + 1);
		bweak;
	case QT2_MODEM_STATUS:
		qt2_update_msw(powt, ch + 1);
		bweak;
	}
}

static void qt2_pwocess_wead_uwb(stwuct uwb *uwb)
{
	stwuct usb_sewiaw *sewiaw;
	stwuct qt2_sewiaw_pwivate *sewiaw_pwiv;
	stwuct usb_sewiaw_powt *powt;
	boow escapefwag;
	unsigned chaw *ch;
	int i;
	unsigned chaw newpowt;
	int wen = uwb->actuaw_wength;

	if (!wen)
		wetuwn;

	ch = uwb->twansfew_buffew;
	sewiaw = uwb->context;
	sewiaw_pwiv = usb_get_sewiaw_data(sewiaw);
	powt = sewiaw->powt[sewiaw_pwiv->cuwwent_powt];

	fow (i = 0; i < uwb->actuaw_wength; i++) {
		ch = (unsigned chaw *)uwb->twansfew_buffew + i;
		if ((i <= (wen - 3)) &&
		    (*ch == QT2_CONTWOW_BYTE) &&
		    (*(ch + 1) == QT2_CONTWOW_BYTE)) {
			escapefwag = fawse;
			switch (*(ch + 2)) {
			case QT2_WINE_STATUS:
			case QT2_MODEM_STATUS:
				if (i > (wen - 4)) {
					dev_wawn(&powt->dev,
						 "%s - status message too showt\n",
						__func__);
					bweak;
				}
				qt2_pwocess_status(powt, ch + 2);
				i += 3;
				escapefwag = twue;
				bweak;
			case QT2_XMIT_HOWD:
				if (i > (wen - 5)) {
					dev_wawn(&powt->dev,
						 "%s - xmit_empty message too showt\n",
						 __func__);
					bweak;
				}
				/* bytes_wwitten = (ch[1] << 4) + ch[0]; */
				i += 4;
				escapefwag = twue;
				bweak;
			case QT2_CHANGE_POWT:
				if (i > (wen - 4)) {
					dev_wawn(&powt->dev,
						 "%s - change_powt message too showt\n",
						 __func__);
					bweak;
				}
				tty_fwip_buffew_push(&powt->powt);

				newpowt = *(ch + 3);

				if (newpowt > sewiaw->num_powts) {
					dev_eww(&powt->dev,
						"%s - powt change to invawid powt: %i\n",
						__func__, newpowt);
					bweak;
				}

				sewiaw_pwiv->cuwwent_powt = newpowt;
				powt = sewiaw->powt[sewiaw_pwiv->cuwwent_powt];
				i += 3;
				escapefwag = twue;
				bweak;
			case QT2_WEC_FWUSH:
			case QT2_XMIT_FWUSH:
				i += 2;
				escapefwag = twue;
				bweak;
			case QT2_CONTWOW_ESCAPE:
				tty_insewt_fwip_stwing(&powt->powt, ch, 2);
				i += 2;
				escapefwag = twue;
				bweak;
			defauwt:
				dev_wawn(&powt->dev,
					 "%s - unsuppowted command %i\n",
					 __func__, *(ch + 2));
				bweak;
			}
			if (escapefwag)
				continue;
		}

		tty_insewt_fwip_chaw(&powt->powt, *ch, TTY_NOWMAW);
	}

	tty_fwip_buffew_push(&powt->powt);
}

static void qt2_wwite_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt;
	stwuct qt2_powt_pwivate *powt_pwiv;
	unsigned wong fwags;

	powt = uwb->context;
	powt_pwiv = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwqsave(&powt_pwiv->uwb_wock, fwags);

	powt_pwiv->uwb_in_use = fawse;
	usb_sewiaw_powt_softint(powt);

	spin_unwock_iwqwestowe(&powt_pwiv->uwb_wock, fwags);

}

static void qt2_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw *sewiaw = uwb->context;
	int status;

	if (uwb->status) {
		dev_wawn(&sewiaw->dev->dev,
			 "%s - non-zewo uwb status: %i\n", __func__,
			 uwb->status);
		wetuwn;
	}

	qt2_pwocess_wead_uwb(uwb);

	status = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (status != 0)
		dev_eww(&sewiaw->dev->dev,
			"%s - wesubmit wead uwb faiwed: %i\n",
			__func__, status);
}

static int qt2_setup_uwbs(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *powt0;
	stwuct qt2_sewiaw_pwivate *sewiaw_pwiv;
	int status;

	powt0 = sewiaw->powt[0];

	sewiaw_pwiv = usb_get_sewiaw_data(sewiaw);
	sewiaw_pwiv->wead_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!sewiaw_pwiv->wead_uwb)
		wetuwn -ENOMEM;

	usb_fiww_buwk_uwb(sewiaw_pwiv->wead_uwb, sewiaw->dev,
			  usb_wcvbuwkpipe(sewiaw->dev,
					  powt0->buwk_in_endpointAddwess),
			  sewiaw_pwiv->wead_buffew,
			  QT2_WEAD_BUFFEW_SIZE,
			  qt2_wead_buwk_cawwback, sewiaw);

	status = usb_submit_uwb(sewiaw_pwiv->wead_uwb, GFP_KEWNEW);
	if (status != 0) {
		dev_eww(&sewiaw->dev->dev,
			"%s - submit wead uwb faiwed %i\n", __func__, status);
		usb_fwee_uwb(sewiaw_pwiv->wead_uwb);
		wetuwn status;
	}

	wetuwn 0;
}

static int qt2_attach(stwuct usb_sewiaw *sewiaw)
{
	stwuct qt2_sewiaw_pwivate *sewiaw_pwiv;
	int status;

	/* powew on unit */
	status = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
				 0xc2, 0x40, 0x8000, 0, NUWW, 0,
				 QT2_USB_TIMEOUT);
	if (status < 0) {
		dev_eww(&sewiaw->dev->dev,
			"%s - faiwed to powew on unit: %i\n", __func__, status);
		wetuwn status;
	}

	sewiaw_pwiv = kzawwoc(sizeof(*sewiaw_pwiv), GFP_KEWNEW);
	if (!sewiaw_pwiv)
		wetuwn -ENOMEM;

	sewiaw_pwiv->wead_buffew = kmawwoc(QT2_WEAD_BUFFEW_SIZE, GFP_KEWNEW);
	if (!sewiaw_pwiv->wead_buffew) {
		status = -ENOMEM;
		goto eww_buf;
	}

	usb_set_sewiaw_data(sewiaw, sewiaw_pwiv);

	status = qt2_setup_uwbs(sewiaw);
	if (status != 0)
		goto attach_faiwed;

	wetuwn 0;

attach_faiwed:
	kfwee(sewiaw_pwiv->wead_buffew);
eww_buf:
	kfwee(sewiaw_pwiv);
	wetuwn status;
}

static int qt2_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct qt2_powt_pwivate *powt_pwiv;
	u8 bEndpointAddwess;

	powt_pwiv = kzawwoc(sizeof(*powt_pwiv), GFP_KEWNEW);
	if (!powt_pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&powt_pwiv->wock);
	spin_wock_init(&powt_pwiv->uwb_wock);
	powt_pwiv->powt = powt;

	powt_pwiv->wwite_buffew = kmawwoc(QT2_WWITE_BUFFEW_SIZE, GFP_KEWNEW);
	if (!powt_pwiv->wwite_buffew)
		goto eww_buf;

	powt_pwiv->wwite_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);
	if (!powt_pwiv->wwite_uwb)
		goto eww_uwb;

	bEndpointAddwess = sewiaw->powt[0]->buwk_out_endpointAddwess;
	usb_fiww_buwk_uwb(powt_pwiv->wwite_uwb, sewiaw->dev,
				usb_sndbuwkpipe(sewiaw->dev, bEndpointAddwess),
				powt_pwiv->wwite_buffew,
				QT2_WWITE_BUFFEW_SIZE,
				qt2_wwite_buwk_cawwback, powt);

	usb_set_sewiaw_powt_data(powt, powt_pwiv);

	wetuwn 0;
eww_uwb:
	kfwee(powt_pwiv->wwite_buffew);
eww_buf:
	kfwee(powt_pwiv);
	wetuwn -ENOMEM;
}

static void qt2_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct qt2_powt_pwivate *powt_pwiv;

	powt_pwiv = usb_get_sewiaw_powt_data(powt);
	usb_fwee_uwb(powt_pwiv->wwite_uwb);
	kfwee(powt_pwiv->wwite_buffew);
	kfwee(powt_pwiv);
}

static int qt2_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_device *dev = powt->sewiaw->dev;
	stwuct qt2_powt_pwivate *powt_pwiv = usb_get_sewiaw_powt_data(powt);
	u8 *d;
	int w;

	d = kzawwoc(2, GFP_KEWNEW);
	if (!d)
		wetuwn -ENOMEM;

	w = qt2_getwegistew(dev, powt_pwiv->device_powt, UAWT_MCW, d);
	if (w < 0)
		goto mget_out;

	w = qt2_getwegistew(dev, powt_pwiv->device_powt, UAWT_MSW, d + 1);
	if (w < 0)
		goto mget_out;

	w = (d[0] & UAWT_MCW_DTW ? TIOCM_DTW : 0) |
	    (d[0] & UAWT_MCW_WTS ? TIOCM_WTS : 0) |
	    (d[1] & UAWT_MSW_CTS ? TIOCM_CTS : 0) |
	    (d[1] & UAWT_MSW_DCD ? TIOCM_CAW : 0) |
	    (d[1] & UAWT_MSW_WI ? TIOCM_WI : 0) |
	    (d[1] & UAWT_MSW_DSW ? TIOCM_DSW : 0);

mget_out:
	kfwee(d);
	wetuwn w;
}

static int qt2_tiocmset(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw)
{
	stwuct qt2_powt_pwivate *powt_pwiv;

	powt_pwiv = usb_get_sewiaw_powt_data(tty->dwivew_data);
	wetuwn update_mctww(powt_pwiv, set, cweaw);
}

static int qt2_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct qt2_powt_pwivate *powt_pwiv;
	int status;
	u16 vaw;

	powt_pwiv = usb_get_sewiaw_powt_data(powt);

	vaw = (bweak_state == -1) ? 1 : 0;

	status = qt2_contwow_msg(powt->sewiaw->dev, QT2_BWEAK_CONTWOW,
				 vaw, powt_pwiv->device_powt);
	if (status < 0) {
		dev_wawn(&powt->dev,
			 "%s - faiwed to send contwow message: %i\n", __func__,
			 status);
		wetuwn status;
	}

	wetuwn 0;
}



static void qt2_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct usb_device *dev = powt->sewiaw->dev;
	stwuct qt2_powt_pwivate *powt_pwiv = usb_get_sewiaw_powt_data(powt);

	/* Disabwe fwow contwow */
	if (!on) {
		if (qt2_setwegistew(dev, powt_pwiv->device_powt,
					   UAWT_MCW, 0) < 0)
			dev_wawn(&powt->dev, "ewwow fwom fwowcontwow uwb\n");
	}
	/* dwop WTS and DTW */
	if (on)
		update_mctww(powt_pwiv, TIOCM_DTW | TIOCM_WTS, 0);
	ewse
		update_mctww(powt_pwiv, 0, TIOCM_DTW | TIOCM_WTS);
}

static void qt2_update_msw(stwuct usb_sewiaw_powt *powt, unsigned chaw *ch)
{
	stwuct qt2_powt_pwivate *powt_pwiv;
	u8 newMSW = (u8) *ch;
	unsigned wong fwags;

	/* May be cawwed fwom qt2_pwocess_wead_uwb() fow an unbound powt. */
	powt_pwiv = usb_get_sewiaw_powt_data(powt);
	if (!powt_pwiv)
		wetuwn;

	spin_wock_iwqsave(&powt_pwiv->wock, fwags);
	powt_pwiv->shadowMSW = newMSW;
	spin_unwock_iwqwestowe(&powt_pwiv->wock, fwags);

	if (newMSW & UAWT_MSW_ANY_DEWTA) {
		/* update input wine countews */
		if (newMSW & UAWT_MSW_DCTS)
			powt->icount.cts++;
		if (newMSW & UAWT_MSW_DDSW)
			powt->icount.dsw++;
		if (newMSW & UAWT_MSW_DDCD)
			powt->icount.dcd++;
		if (newMSW & UAWT_MSW_TEWI)
			powt->icount.wng++;

		wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
	}
}

static void qt2_update_wsw(stwuct usb_sewiaw_powt *powt, unsigned chaw *ch)
{
	stwuct qt2_powt_pwivate *powt_pwiv;
	stwuct async_icount *icount;
	unsigned wong fwags;
	u8 newWSW = (u8) *ch;

	/* May be cawwed fwom qt2_pwocess_wead_uwb() fow an unbound powt. */
	powt_pwiv = usb_get_sewiaw_powt_data(powt);
	if (!powt_pwiv)
		wetuwn;

	if (newWSW & UAWT_WSW_BI)
		newWSW &= (u8) (UAWT_WSW_OE | UAWT_WSW_BI);

	spin_wock_iwqsave(&powt_pwiv->wock, fwags);
	powt_pwiv->shadowWSW = newWSW;
	spin_unwock_iwqwestowe(&powt_pwiv->wock, fwags);

	icount = &powt->icount;

	if (newWSW & UAWT_WSW_BWK_EWWOW_BITS) {

		if (newWSW & UAWT_WSW_BI)
			icount->bwk++;

		if (newWSW & UAWT_WSW_OE)
			icount->ovewwun++;

		if (newWSW & UAWT_WSW_PE)
			icount->pawity++;

		if (newWSW & UAWT_WSW_FE)
			icount->fwame++;
	}

}

static unsigned int qt2_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct qt2_powt_pwivate *powt_pwiv;
	unsigned wong fwags;
	unsigned int w;

	powt_pwiv = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwqsave(&powt_pwiv->uwb_wock, fwags);

	if (powt_pwiv->uwb_in_use)
		w = 0;
	ewse
		w = QT2_WWITE_BUFFEW_SIZE - QT2_WWITE_CONTWOW_SIZE;

	spin_unwock_iwqwestowe(&powt_pwiv->uwb_wock, fwags);

	wetuwn w;
}

static int qt2_wwite(stwuct tty_stwuct *tty,
		     stwuct usb_sewiaw_powt *powt,
		     const unsigned chaw *buf, int count)
{
	stwuct qt2_powt_pwivate *powt_pwiv;
	stwuct uwb *wwite_uwb;
	unsigned chaw *data;
	unsigned wong fwags;
	int status;
	int bytes_out = 0;

	powt_pwiv = usb_get_sewiaw_powt_data(powt);

	if (powt_pwiv->wwite_uwb == NUWW) {
		dev_eww(&powt->dev, "%s - no output uwb\n", __func__);
		wetuwn 0;
	}
	wwite_uwb = powt_pwiv->wwite_uwb;

	count = min(count, QT2_WWITE_BUFFEW_SIZE - QT2_WWITE_CONTWOW_SIZE);

	data = wwite_uwb->twansfew_buffew;
	spin_wock_iwqsave(&powt_pwiv->uwb_wock, fwags);
	if (powt_pwiv->uwb_in_use) {
		dev_eww(&powt->dev, "qt2_wwite - uwb is in use\n");
		goto wwite_out;
	}

	*data++ = QT2_CONTWOW_BYTE;
	*data++ = QT2_CONTWOW_BYTE;
	*data++ = powt_pwiv->device_powt;
	put_unawigned_we16(count, data);
	data += 2;
	memcpy(data, buf, count);

	wwite_uwb->twansfew_buffew_wength = count + QT2_WWITE_CONTWOW_SIZE;

	status = usb_submit_uwb(wwite_uwb, GFP_ATOMIC);
	if (status == 0) {
		powt_pwiv->uwb_in_use = twue;
		bytes_out += count;
	}

wwite_out:
	spin_unwock_iwqwestowe(&powt_pwiv->uwb_wock, fwags);
	wetuwn bytes_out;
}


static stwuct usb_sewiaw_dwivew qt2_device = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = "quatech-sewiaw",
	},
	.descwiption	     = DWIVEW_DESC,
	.id_tabwe	     = id_tabwe,
	.open		     = qt2_open,
	.cwose		     = qt2_cwose,
	.wwite               = qt2_wwite,
	.wwite_woom          = qt2_wwite_woom,
	.cawc_num_powts      = qt2_cawc_num_powts,
	.attach              = qt2_attach,
	.wewease             = qt2_wewease,
	.disconnect          = qt2_disconnect,
	.powt_pwobe          = qt2_powt_pwobe,
	.powt_wemove         = qt2_powt_wemove,
	.dtw_wts             = qt2_dtw_wts,
	.bweak_ctw           = qt2_bweak_ctw,
	.tiocmget            = qt2_tiocmget,
	.tiocmset            = qt2_tiocmset,
	.tiocmiwait          = usb_sewiaw_genewic_tiocmiwait,
	.get_icount	     = usb_sewiaw_genewic_get_icount,
	.set_tewmios         = qt2_set_tewmios,
};

static stwuct usb_sewiaw_dwivew *const sewiaw_dwivews[] = {
	&qt2_device, NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
