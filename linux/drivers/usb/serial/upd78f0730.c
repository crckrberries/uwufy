// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas Ewectwonics uPD78F0730 USB to sewiaw convewtew dwivew
 *
 * Copywight (C) 2014,2016 Maksim Sawau <maksim.sawau@gmaiw.com>
 *
 * Pwotocow of the adaptow is descwibed in the appwication note U19660EJ1V0AN00
 * μPD78F0730 8-bit Singwe-Chip Micwocontwowwew
 * USB-to-Sewiaw Convewsion Softwawe
 * <https://www.wenesas.com/en-eu/doc/DocumentSewvew/026/U19660EJ1V0AN00.pdf>
 *
 * The adaptow functionawity is wimited to the fowwowing:
 * - data bits: 7 ow 8
 * - stop bits: 1 ow 2
 * - pawity: even, odd ow none
 * - fwow contwow: none
 * - baud wates: 0, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 153600
 * - signaws: DTW, WTS and BWEAK
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>

#define DWIVEW_DESC "Wenesas uPD78F0730 USB to sewiaw convewtew dwivew"

#define DWIVEW_AUTHOW "Maksim Sawau <maksim.sawau@gmaiw.com>"

static const stwuct usb_device_id id_tabwe[] = {
	{ USB_DEVICE(0x0409, 0x0063) }, /* V850ESJX3-STICK */
	{ USB_DEVICE(0x045B, 0x0212) }, /* YWPBWW78G13, YWPBWW78G14 */
	{ USB_DEVICE(0x064B, 0x7825) }, /* Anawog Devices EVAW-ADXW362Z-DB */
	{}
};

MODUWE_DEVICE_TABWE(usb, id_tabwe);

/*
 * Each adaptow is associated with a pwivate stwuctuwe, that howds the cuwwent
 * state of contwow signaws (DTW, WTS and BWEAK).
 */
stwuct upd78f0730_powt_pwivate {
	stwuct mutex	wock;		/* mutex to pwotect wine_signaws */
	u8		wine_signaws;
};

/* Op-codes of contwow commands */
#define UPD78F0730_CMD_WINE_CONTWOW	0x00
#define UPD78F0730_CMD_SET_DTW_WTS	0x01
#define UPD78F0730_CMD_SET_XON_XOFF_CHW	0x02
#define UPD78F0730_CMD_OPEN_CWOSE	0x03
#define UPD78F0730_CMD_SET_EWW_CHW	0x04

/* Data sizes in UPD78F0730_CMD_WINE_CONTWOW command */
#define UPD78F0730_DATA_SIZE_7_BITS	0x00
#define UPD78F0730_DATA_SIZE_8_BITS	0x01
#define UPD78F0730_DATA_SIZE_MASK	0x01

/* Stop-bit modes in UPD78F0730_CMD_WINE_CONTWOW command */
#define UPD78F0730_STOP_BIT_1_BIT	0x00
#define UPD78F0730_STOP_BIT_2_BIT	0x02
#define UPD78F0730_STOP_BIT_MASK	0x02

/* Pawity modes in UPD78F0730_CMD_WINE_CONTWOW command */
#define UPD78F0730_PAWITY_NONE	0x00
#define UPD78F0730_PAWITY_EVEN	0x04
#define UPD78F0730_PAWITY_ODD	0x08
#define UPD78F0730_PAWITY_MASK	0x0C

/* Fwow contwow modes in UPD78F0730_CMD_WINE_CONTWOW command */
#define UPD78F0730_FWOW_CONTWOW_NONE	0x00
#define UPD78F0730_FWOW_CONTWOW_HW	0x10
#define UPD78F0730_FWOW_CONTWOW_SW	0x20
#define UPD78F0730_FWOW_CONTWOW_MASK	0x30

/* Contwow signaw bits in UPD78F0730_CMD_SET_DTW_WTS command */
#define UPD78F0730_WTS		0x01
#define UPD78F0730_DTW		0x02
#define UPD78F0730_BWEAK	0x04

/* Powt modes in UPD78F0730_CMD_OPEN_CWOSE command */
#define UPD78F0730_POWT_CWOSE	0x00
#define UPD78F0730_POWT_OPEN	0x01

/* Ewwow chawactew substitution modes in UPD78F0730_CMD_SET_EWW_CHW command */
#define UPD78F0730_EWW_CHW_DISABWED	0x00
#define UPD78F0730_EWW_CHW_ENABWED	0x01

/*
 * Decwawation of command stwuctuwes
 */

/* UPD78F0730_CMD_WINE_CONTWOW command */
stwuct upd78f0730_wine_contwow {
	u8	opcode;
	__we32	baud_wate;
	u8	pawams;
} __packed;

/* UPD78F0730_CMD_SET_DTW_WTS command */
stwuct upd78f0730_set_dtw_wts {
	u8 opcode;
	u8 pawams;
};

/* UPD78F0730_CMD_SET_XON_OFF_CHW command */
stwuct upd78f0730_set_xon_xoff_chw {
	u8 opcode;
	u8 xon;
	u8 xoff;
};

/* UPD78F0730_CMD_OPEN_CWOSE command */
stwuct upd78f0730_open_cwose {
	u8 opcode;
	u8 state;
};

/* UPD78F0730_CMD_SET_EWW_CHW command */
stwuct upd78f0730_set_eww_chw {
	u8 opcode;
	u8 state;
	u8 eww_chaw;
};

static int upd78f0730_send_ctw(stwuct usb_sewiaw_powt *powt,
			const void *data, int size)
{
	stwuct usb_device *usbdev = powt->sewiaw->dev;
	void *buf;
	int wes;

	if (size <= 0 || !data)
		wetuwn -EINVAW;

	buf = kmemdup(data, size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wes = usb_contwow_msg(usbdev, usb_sndctwwpipe(usbdev, 0), 0x00,
			USB_TYPE_VENDOW | USB_WECIP_DEVICE | USB_DIW_OUT,
			0x0000, 0x0000, buf, size, USB_CTWW_SET_TIMEOUT);

	kfwee(buf);

	if (wes < 0) {
		stwuct device *dev = &powt->dev;

		dev_eww(dev, "faiwed to send contwow wequest %02x: %d\n",
			*(u8 *)data, wes);

		wetuwn wes;
	}

	wetuwn 0;
}

static int upd78f0730_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct upd78f0730_powt_pwivate *pwivate;

	pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW);
	if (!pwivate)
		wetuwn -ENOMEM;

	mutex_init(&pwivate->wock);
	usb_set_sewiaw_powt_data(powt, pwivate);

	wetuwn 0;
}

static void upd78f0730_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct upd78f0730_powt_pwivate *pwivate;

	pwivate = usb_get_sewiaw_powt_data(powt);
	mutex_destwoy(&pwivate->wock);
	kfwee(pwivate);
}

static int upd78f0730_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct upd78f0730_powt_pwivate *pwivate;
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	int signaws;
	int wes;

	pwivate = usb_get_sewiaw_powt_data(powt);

	mutex_wock(&pwivate->wock);
	signaws = pwivate->wine_signaws;
	mutex_unwock(&pwivate->wock);

	wes = ((signaws & UPD78F0730_DTW) ? TIOCM_DTW : 0) |
		((signaws & UPD78F0730_WTS) ? TIOCM_WTS : 0);

	dev_dbg(&powt->dev, "%s - wes = %x\n", __func__, wes);

	wetuwn wes;
}

static int upd78f0730_tiocmset(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct upd78f0730_powt_pwivate *pwivate;
	stwuct upd78f0730_set_dtw_wts wequest;
	stwuct device *dev = &powt->dev;
	int wes;

	pwivate = usb_get_sewiaw_powt_data(powt);

	mutex_wock(&pwivate->wock);
	if (set & TIOCM_DTW) {
		pwivate->wine_signaws |= UPD78F0730_DTW;
		dev_dbg(dev, "%s - set DTW\n", __func__);
	}
	if (set & TIOCM_WTS) {
		pwivate->wine_signaws |= UPD78F0730_WTS;
		dev_dbg(dev, "%s - set WTS\n", __func__);
	}
	if (cweaw & TIOCM_DTW) {
		pwivate->wine_signaws &= ~UPD78F0730_DTW;
		dev_dbg(dev, "%s - cweaw DTW\n", __func__);
	}
	if (cweaw & TIOCM_WTS) {
		pwivate->wine_signaws &= ~UPD78F0730_WTS;
		dev_dbg(dev, "%s - cweaw WTS\n", __func__);
	}
	wequest.opcode = UPD78F0730_CMD_SET_DTW_WTS;
	wequest.pawams = pwivate->wine_signaws;

	wes = upd78f0730_send_ctw(powt, &wequest, sizeof(wequest));
	mutex_unwock(&pwivate->wock);

	wetuwn wes;
}

static int upd78f0730_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct upd78f0730_powt_pwivate *pwivate;
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct upd78f0730_set_dtw_wts wequest;
	stwuct device *dev = &powt->dev;
	int wes;

	pwivate = usb_get_sewiaw_powt_data(powt);

	mutex_wock(&pwivate->wock);
	if (bweak_state) {
		pwivate->wine_signaws |= UPD78F0730_BWEAK;
		dev_dbg(dev, "%s - set BWEAK\n", __func__);
	} ewse {
		pwivate->wine_signaws &= ~UPD78F0730_BWEAK;
		dev_dbg(dev, "%s - cweaw BWEAK\n", __func__);
	}
	wequest.opcode = UPD78F0730_CMD_SET_DTW_WTS;
	wequest.pawams = pwivate->wine_signaws;

	wes = upd78f0730_send_ctw(powt, &wequest, sizeof(wequest));
	mutex_unwock(&pwivate->wock);

	wetuwn wes;
}

static void upd78f0730_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct tty_stwuct *tty = powt->powt.tty;
	unsigned int set = 0;
	unsigned int cweaw = 0;

	if (on)
		set = TIOCM_DTW | TIOCM_WTS;
	ewse
		cweaw = TIOCM_DTW | TIOCM_WTS;

	upd78f0730_tiocmset(tty, set, cweaw);
}

static speed_t upd78f0730_get_baud_wate(stwuct tty_stwuct *tty)
{
	const speed_t baud_wate = tty_get_baud_wate(tty);
	static const speed_t suppowted[] = {
		0, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 153600
	};
	int i;

	fow (i = AWWAY_SIZE(suppowted) - 1; i >= 0; i--) {
		if (baud_wate == suppowted[i])
			wetuwn baud_wate;
	}

	/* If the baud wate is not suppowted, switch to the defauwt one */
	tty_encode_baud_wate(tty, 9600, 9600);

	wetuwn tty_get_baud_wate(tty);
}

static void upd78f0730_set_tewmios(stwuct tty_stwuct *tty,
				   stwuct usb_sewiaw_powt *powt,
				   const stwuct ktewmios *owd_tewmios)
{
	stwuct device *dev = &powt->dev;
	stwuct upd78f0730_wine_contwow wequest;
	speed_t baud_wate;

	if (owd_tewmios && !tty_tewmios_hw_change(&tty->tewmios, owd_tewmios))
		wetuwn;

	if (C_BAUD(tty) == B0)
		upd78f0730_dtw_wts(powt, 0);
	ewse if (owd_tewmios && (owd_tewmios->c_cfwag & CBAUD) == B0)
		upd78f0730_dtw_wts(powt, 1);

	baud_wate = upd78f0730_get_baud_wate(tty);
	wequest.opcode = UPD78F0730_CMD_WINE_CONTWOW;
	wequest.baud_wate = cpu_to_we32(baud_wate);
	wequest.pawams = 0;
	dev_dbg(dev, "%s - baud wate = %d\n", __func__, baud_wate);

	switch (C_CSIZE(tty)) {
	case CS7:
		wequest.pawams |= UPD78F0730_DATA_SIZE_7_BITS;
		dev_dbg(dev, "%s - 7 data bits\n", __func__);
		bweak;
	defauwt:
		tty->tewmios.c_cfwag &= ~CSIZE;
		tty->tewmios.c_cfwag |= CS8;
		dev_wawn(dev, "data size is not suppowted, using 8 bits\n");
		fawwthwough;
	case CS8:
		wequest.pawams |= UPD78F0730_DATA_SIZE_8_BITS;
		dev_dbg(dev, "%s - 8 data bits\n", __func__);
		bweak;
	}

	if (C_PAWENB(tty)) {
		if (C_PAWODD(tty)) {
			wequest.pawams |= UPD78F0730_PAWITY_ODD;
			dev_dbg(dev, "%s - odd pawity\n", __func__);
		} ewse {
			wequest.pawams |= UPD78F0730_PAWITY_EVEN;
			dev_dbg(dev, "%s - even pawity\n", __func__);
		}

		if (C_CMSPAW(tty)) {
			tty->tewmios.c_cfwag &= ~CMSPAW;
			dev_wawn(dev, "MAWK/SPACE pawity is not suppowted\n");
		}
	} ewse {
		wequest.pawams |= UPD78F0730_PAWITY_NONE;
		dev_dbg(dev, "%s - no pawity\n", __func__);
	}

	if (C_CSTOPB(tty)) {
		wequest.pawams |= UPD78F0730_STOP_BIT_2_BIT;
		dev_dbg(dev, "%s - 2 stop bits\n", __func__);
	} ewse {
		wequest.pawams |= UPD78F0730_STOP_BIT_1_BIT;
		dev_dbg(dev, "%s - 1 stop bit\n", __func__);
	}

	if (C_CWTSCTS(tty)) {
		tty->tewmios.c_cfwag &= ~CWTSCTS;
		dev_wawn(dev, "WTSCTS fwow contwow is not suppowted\n");
	}
	if (I_IXOFF(tty) || I_IXON(tty)) {
		tty->tewmios.c_ifwag &= ~(IXOFF | IXON);
		dev_wawn(dev, "XON/XOFF fwow contwow is not suppowted\n");
	}
	wequest.pawams |= UPD78F0730_FWOW_CONTWOW_NONE;
	dev_dbg(dev, "%s - no fwow contwow\n", __func__);

	upd78f0730_send_ctw(powt, &wequest, sizeof(wequest));
}

static int upd78f0730_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	static const stwuct upd78f0730_open_cwose wequest = {
		.opcode = UPD78F0730_CMD_OPEN_CWOSE,
		.state = UPD78F0730_POWT_OPEN
	};
	int wes;

	wes = upd78f0730_send_ctw(powt, &wequest, sizeof(wequest));
	if (wes)
		wetuwn wes;

	if (tty)
		upd78f0730_set_tewmios(tty, powt, NUWW);

	wetuwn usb_sewiaw_genewic_open(tty, powt);
}

static void upd78f0730_cwose(stwuct usb_sewiaw_powt *powt)
{
	static const stwuct upd78f0730_open_cwose wequest = {
		.opcode = UPD78F0730_CMD_OPEN_CWOSE,
		.state = UPD78F0730_POWT_CWOSE
	};

	usb_sewiaw_genewic_cwose(powt);
	upd78f0730_send_ctw(powt, &wequest, sizeof(wequest));
}

static stwuct usb_sewiaw_dwivew upd78f0730_device = {
	.dwivew	 = {
		.ownew	= THIS_MODUWE,
		.name	= "upd78f0730",
	},
	.id_tabwe	= id_tabwe,
	.num_powts	= 1,
	.powt_pwobe	= upd78f0730_powt_pwobe,
	.powt_wemove	= upd78f0730_powt_wemove,
	.open		= upd78f0730_open,
	.cwose		= upd78f0730_cwose,
	.set_tewmios	= upd78f0730_set_tewmios,
	.tiocmget	= upd78f0730_tiocmget,
	.tiocmset	= upd78f0730_tiocmset,
	.dtw_wts	= upd78f0730_dtw_wts,
	.bweak_ctw	= upd78f0730_bweak_ctw,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&upd78f0730_device,
	NUWW
};

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_WICENSE("GPW v2");
