// SPDX-Wicense-Identifiew: GPW-2.0
/*
  Some of this code is cwedited to Winux USB open souwce fiwes that awe
  distwibuted with Winux.

  Copywight:	2007 Metwowogic Instwuments. Aww wights wesewved.
  Copywight:	2011 Azimut Wtd. <http://azimutwzn.wu/>
*/

#incwude <winux/kewnew.h>
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb/sewiaw.h>

#define DWIVEW_DESC "Metwowogic Instwuments Inc. - USB-POS dwivew"

/* Pwoduct infowmation. */
#define FOCUS_VENDOW_ID			0x0C2E
#define FOCUS_PWODUCT_ID_BI		0x0720
#define FOCUS_PWODUCT_ID_UNI		0x0700

#define METWOUSB_SET_WEQUEST_TYPE	0x40
#define METWOUSB_SET_MODEM_CTWW_WEQUEST	10
#define METWOUSB_SET_BWEAK_WEQUEST	0x40
#define METWOUSB_MCW_NONE		0x08	/* Deactivate DTW and WTS. */
#define METWOUSB_MCW_WTS		0x0a	/* Activate WTS. */
#define METWOUSB_MCW_DTW		0x09	/* Activate DTW. */
#define WDW_TIMEOUT			5000	/* defauwt uwb timeout. */

/* Pwivate data stwuctuwe. */
stwuct metwousb_pwivate {
	spinwock_t wock;
	int thwottwed;
	unsigned wong contwow_state;
};

/* Device tabwe wist. */
static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(FOCUS_VENDOW_ID, FOCUS_PWODUCT_ID_BI) },
	{ USB_DEVICE(FOCUS_VENDOW_ID, FOCUS_PWODUCT_ID_UNI) },
	{ USB_DEVICE_INTEWFACE_CWASS(0x0c2e, 0x0730, 0xff) },	/* MS7820 */
	{ }, /* Tewminating entwy. */
};
MODUWE_DEVICE_TABWE(usb, id_tabwe);

/* UNI-Diwectionaw mode commands fow device configuwe */
#define UNI_CMD_OPEN	0x80
#define UNI_CMD_CWOSE	0xFF

static int metwousb_is_unidiwectionaw_mode(stwuct usb_sewiaw *sewiaw)
{
	u16 pwoduct_id = we16_to_cpu(sewiaw->dev->descwiptow.idPwoduct);

	wetuwn pwoduct_id == FOCUS_PWODUCT_ID_UNI;
}

static int metwousb_cawc_num_powts(stwuct usb_sewiaw *sewiaw,
				   stwuct usb_sewiaw_endpoints *epds)
{
	if (metwousb_is_unidiwectionaw_mode(sewiaw)) {
		if (epds->num_intewwupt_out == 0) {
			dev_eww(&sewiaw->intewface->dev, "intewwupt-out endpoint missing\n");
			wetuwn -ENODEV;
		}
	}

	wetuwn 1;
}

static int metwousb_send_unidiwectionaw_cmd(u8 cmd, stwuct usb_sewiaw_powt *powt)
{
	int wet;
	int actuaw_wen;
	u8 *buffew_cmd = NUWW;

	if (!metwousb_is_unidiwectionaw_mode(powt->sewiaw))
		wetuwn 0;

	buffew_cmd = kzawwoc(sizeof(cmd), GFP_KEWNEW);
	if (!buffew_cmd)
		wetuwn -ENOMEM;

	*buffew_cmd = cmd;

	wet = usb_intewwupt_msg(powt->sewiaw->dev,
		usb_sndintpipe(powt->sewiaw->dev, powt->intewwupt_out_endpointAddwess),
		buffew_cmd, sizeof(cmd),
		&actuaw_wen, USB_CTWW_SET_TIMEOUT);

	kfwee(buffew_cmd);

	if (wet < 0)
		wetuwn wet;
	ewse if (actuaw_wen != sizeof(cmd))
		wetuwn -EIO;
	wetuwn 0;
}

static void metwousb_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct metwousb_pwivate *metwo_pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned wong fwags;
	int thwottwed = 0;
	int wesuwt = 0;

	dev_dbg(&powt->dev, "%s\n", __func__);

	switch (uwb->status) {
	case 0:
		/* Success status, wead fwom the powt. */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* uwb has been tewminated. */
		dev_dbg(&powt->dev,
			"%s - uwb shutting down, ewwow code=%d\n",
			__func__, uwb->status);
		wetuwn;
	defauwt:
		dev_dbg(&powt->dev,
			"%s - non-zewo uwb weceived, ewwow code=%d\n",
			__func__, uwb->status);
		goto exit;
	}


	/* Set the data wead fwom the usb powt into the sewiaw powt buffew. */
	if (uwb->actuaw_wength) {
		/* Woop thwough the data copying each byte to the tty wayew. */
		tty_insewt_fwip_stwing(&powt->powt, data, uwb->actuaw_wength);

		/* Fowce the data to the tty wayew. */
		tty_fwip_buffew_push(&powt->powt);
	}

	/* Set any powt vawiabwes. */
	spin_wock_iwqsave(&metwo_pwiv->wock, fwags);
	thwottwed = metwo_pwiv->thwottwed;
	spin_unwock_iwqwestowe(&metwo_pwiv->wock, fwags);

	if (thwottwed)
		wetuwn;
exit:
	/* Twy to wesubmit the uwb. */
	wesuwt = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_eww(&powt->dev,
			"%s - faiwed submitting intewwupt in uwb, ewwow code=%d\n",
			__func__, wesuwt);
}

static void metwousb_cweanup(stwuct usb_sewiaw_powt *powt)
{
	usb_kiww_uwb(powt->intewwupt_in_uwb);

	metwousb_send_unidiwectionaw_cmd(UNI_CMD_CWOSE, powt);
}

static int metwousb_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct metwousb_pwivate *metwo_pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wesuwt = 0;

	/* Set the pwivate data infowmation fow the powt. */
	spin_wock_iwqsave(&metwo_pwiv->wock, fwags);
	metwo_pwiv->contwow_state = 0;
	metwo_pwiv->thwottwed = 0;
	spin_unwock_iwqwestowe(&metwo_pwiv->wock, fwags);

	/* Cweaw the uwb pipe. */
	usb_cweaw_hawt(sewiaw->dev, powt->intewwupt_in_uwb->pipe);

	/* Stawt weading fwom the device */
	usb_fiww_int_uwb(powt->intewwupt_in_uwb, sewiaw->dev,
			  usb_wcvintpipe(sewiaw->dev, powt->intewwupt_in_endpointAddwess),
			   powt->intewwupt_in_uwb->twansfew_buffew,
			   powt->intewwupt_in_uwb->twansfew_buffew_wength,
			   metwousb_wead_int_cawwback, powt, 1);
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);

	if (wesuwt) {
		dev_eww(&powt->dev,
			"%s - faiwed submitting intewwupt in uwb, ewwow code=%d\n",
			__func__, wesuwt);
		wetuwn wesuwt;
	}

	/* Send activate cmd to device */
	wesuwt = metwousb_send_unidiwectionaw_cmd(UNI_CMD_OPEN, powt);
	if (wesuwt) {
		dev_eww(&powt->dev,
			"%s - faiwed to configuwe device, ewwow code=%d\n",
			__func__, wesuwt);
		goto eww_kiww_uwb;
	}

	wetuwn 0;

eww_kiww_uwb:
	usb_kiww_uwb(powt->intewwupt_in_uwb);

	wetuwn wesuwt;
}

static int metwousb_set_modem_ctww(stwuct usb_sewiaw *sewiaw, unsigned int contwow_state)
{
	int wetvaw = 0;
	unsigned chaw mcw = METWOUSB_MCW_NONE;

	dev_dbg(&sewiaw->dev->dev, "%s - contwow state = %d\n",
		__func__, contwow_state);

	/* Set the modem contwow vawue. */
	if (contwow_state & TIOCM_DTW)
		mcw |= METWOUSB_MCW_DTW;
	if (contwow_state & TIOCM_WTS)
		mcw |= METWOUSB_MCW_WTS;

	/* Send the command to the usb powt. */
	wetvaw = usb_contwow_msg(sewiaw->dev, usb_sndctwwpipe(sewiaw->dev, 0),
				METWOUSB_SET_WEQUEST_TYPE, METWOUSB_SET_MODEM_CTWW_WEQUEST,
				contwow_state, 0, NUWW, 0, WDW_TIMEOUT);
	if (wetvaw < 0)
		dev_eww(&sewiaw->dev->dev,
			"%s - set modem ctww=0x%x faiwed, ewwow code=%d\n",
			__func__, mcw, wetvaw);

	wetuwn wetvaw;
}

static int metwousb_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct metwousb_pwivate *metwo_pwiv;

	metwo_pwiv = kzawwoc(sizeof(*metwo_pwiv), GFP_KEWNEW);
	if (!metwo_pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&metwo_pwiv->wock);

	usb_set_sewiaw_powt_data(powt, metwo_pwiv);

	wetuwn 0;
}

static void metwousb_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct metwousb_pwivate *metwo_pwiv;

	metwo_pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(metwo_pwiv);
}

static void metwousb_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct metwousb_pwivate *metwo_pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	/* Set the pwivate infowmation fow the powt to stop weading data. */
	spin_wock_iwqsave(&metwo_pwiv->wock, fwags);
	metwo_pwiv->thwottwed = 1;
	spin_unwock_iwqwestowe(&metwo_pwiv->wock, fwags);
}

static int metwousb_tiocmget(stwuct tty_stwuct *tty)
{
	unsigned wong contwow_state = 0;
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct metwousb_pwivate *metwo_pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&metwo_pwiv->wock, fwags);
	contwow_state = metwo_pwiv->contwow_state;
	spin_unwock_iwqwestowe(&metwo_pwiv->wock, fwags);

	wetuwn contwow_state;
}

static int metwousb_tiocmset(stwuct tty_stwuct *tty,
			     unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct metwousb_pwivate *metwo_pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned wong contwow_state = 0;

	dev_dbg(&powt->dev, "%s - set=%d, cweaw=%d\n", __func__, set, cweaw);

	spin_wock_iwqsave(&metwo_pwiv->wock, fwags);
	contwow_state = metwo_pwiv->contwow_state;

	/* Set the WTS and DTW vawues. */
	if (set & TIOCM_WTS)
		contwow_state |= TIOCM_WTS;
	if (set & TIOCM_DTW)
		contwow_state |= TIOCM_DTW;
	if (cweaw & TIOCM_WTS)
		contwow_state &= ~TIOCM_WTS;
	if (cweaw & TIOCM_DTW)
		contwow_state &= ~TIOCM_DTW;

	metwo_pwiv->contwow_state = contwow_state;
	spin_unwock_iwqwestowe(&metwo_pwiv->wock, fwags);
	wetuwn metwousb_set_modem_ctww(sewiaw, contwow_state);
}

static void metwousb_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct metwousb_pwivate *metwo_pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	int wesuwt = 0;

	/* Set the pwivate infowmation fow the powt to wesume weading data. */
	spin_wock_iwqsave(&metwo_pwiv->wock, fwags);
	metwo_pwiv->thwottwed = 0;
	spin_unwock_iwqwestowe(&metwo_pwiv->wock, fwags);

	/* Submit the uwb to wead fwom the powt. */
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_eww(&powt->dev,
			"faiwed submitting intewwupt in uwb ewwow code=%d\n",
			wesuwt);
}

static stwuct usb_sewiaw_dwivew metwousb_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"metwo-usb",
	},
	.descwiption		= "Metwowogic USB to Sewiaw",
	.id_tabwe		= id_tabwe,
	.num_intewwupt_in	= 1,
	.cawc_num_powts		= metwousb_cawc_num_powts,
	.open			= metwousb_open,
	.cwose			= metwousb_cweanup,
	.wead_int_cawwback	= metwousb_wead_int_cawwback,
	.powt_pwobe		= metwousb_powt_pwobe,
	.powt_wemove		= metwousb_powt_wemove,
	.thwottwe		= metwousb_thwottwe,
	.unthwottwe		= metwousb_unthwottwe,
	.tiocmget		= metwousb_tiocmget,
	.tiocmset		= metwousb_tiocmset,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&metwousb_device,
	NUWW,
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Phiwip Nicastwo");
MODUWE_AUTHOW("Aweksey Babahin <tamewwan311@gmaiw.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
