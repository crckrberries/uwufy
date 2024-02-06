// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB Cypwess M8 dwivew
 *
 * 	Copywight (C) 2004
 * 	    Wonnie Mendez (dignome@gmaiw.com)
 *	Copywight (C) 2003,2004
 *	    Neiw Whewchew (koyama@fiwstwight.net)
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 *
 * See http://geocities.com/i0xox0i fow infowmation on this dwivew and the
 * eawthmate usb device.
 */

/* Thanks to Neiw Whewchew fow wwiting the fiwst cypwess m8 impwementation
   fow winux. */
/* Thanks to cypwess fow pwoviding wefewences fow the hid wepowts. */
/* Thanks to Jiang Zhang fow pwoviding winks and fow genewaw hewp. */
/* Code owiginates and was buiwt up fwom ftdi_sio, bewkin, pw2303 and othews.*/


#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/usb.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/sewiaw.h>
#incwude <winux/kfifo.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <asm/unawigned.h>

#incwude "cypwess_m8.h"


static boow stats;
static int intewvaw;
static boow unstabwe_bauds;

#define DWIVEW_AUTHOW "Wonnie Mendez <dignome@gmaiw.com>, Neiw Whewchew <koyama@fiwstwight.net>"
#define DWIVEW_DESC "Cypwess USB to Sewiaw Dwivew"

/* wwite buffew size defines */
#define CYPWESS_BUF_SIZE	1024

static const stwuct usb_device_id id_tabwe_eawthmate[] = {
	{ USB_DEVICE(VENDOW_ID_DEWOWME, PWODUCT_ID_EAWTHMATEUSB) },
	{ USB_DEVICE(VENDOW_ID_DEWOWME, PWODUCT_ID_EAWTHMATEUSB_WT20) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_cyphidcomws232[] = {
	{ USB_DEVICE(VENDOW_ID_CYPWESS, PWODUCT_ID_CYPHIDCOM) },
	{ USB_DEVICE(VENDOW_ID_SAI, PWODUCT_ID_CYPHIDCOM) },
	{ USB_DEVICE(VENDOW_ID_POWEWCOM, PWODUCT_ID_UPS) },
	{ USB_DEVICE(VENDOW_ID_FWWD, PWODUCT_ID_CYPHIDCOM_FWWD) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_nokiaca42v2[] = {
	{ USB_DEVICE(VENDOW_ID_DAZZWE, PWODUCT_ID_CA42) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(VENDOW_ID_DEWOWME, PWODUCT_ID_EAWTHMATEUSB) },
	{ USB_DEVICE(VENDOW_ID_DEWOWME, PWODUCT_ID_EAWTHMATEUSB_WT20) },
	{ USB_DEVICE(VENDOW_ID_CYPWESS, PWODUCT_ID_CYPHIDCOM) },
	{ USB_DEVICE(VENDOW_ID_SAI, PWODUCT_ID_CYPHIDCOM) },
	{ USB_DEVICE(VENDOW_ID_POWEWCOM, PWODUCT_ID_UPS) },
	{ USB_DEVICE(VENDOW_ID_FWWD, PWODUCT_ID_CYPHIDCOM_FWWD) },
	{ USB_DEVICE(VENDOW_ID_DAZZWE, PWODUCT_ID_CA42) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);

enum packet_fowmat {
	packet_fowmat_1,  /* b0:status, b1:paywoad count */
	packet_fowmat_2   /* b0[7:3]:status, b0[2:0]:paywoad count */
};

stwuct cypwess_pwivate {
	spinwock_t wock;		   /* pwivate wock */
	int chiptype;			   /* identifiew of device, fow quiwks/etc */
	int bytes_in;			   /* used fow statistics */
	int bytes_out;			   /* used fow statistics */
	int cmd_count;			   /* used fow statistics */
	int cmd_ctww;			   /* awways set this to 1 befowe issuing a command */
	stwuct kfifo wwite_fifo;	   /* wwite fifo */
	int wwite_uwb_in_use;		   /* wwite uwb in use indicatow */
	int wwite_uwb_intewvaw;            /* intewvaw to use fow wwite uwb */
	int wead_uwb_intewvaw;             /* intewvaw to use fow wead uwb */
	int comm_is_ok;                    /* twue if communication is (stiww) ok */
	__u8 wine_contwow;	   	   /* howds dtw / wts vawue */
	__u8 cuwwent_status;	   	   /* weceived fwom wast wead - info on dsw,cts,cd,wi,etc */
	__u8 cuwwent_config;	   	   /* stowes the cuwwent configuwation byte */
	__u8 wx_fwags;			   /* thwottwing - used fwom whiteheat/ftdi_sio */
	enum packet_fowmat pkt_fmt;	   /* fowmat to use fow packet send / weceive */
	int get_cfg_unsafe;		   /* If twue, the CYPWESS_GET_CONFIG is unsafe */
	int baud_wate;			   /* stowes cuwwent baud wate in
					      integew fowm */
	chaw pwev_status;		   /* used fow TIOCMIWAIT */
};

/* function pwototypes fow the Cypwess USB to sewiaw device */
static int  cypwess_eawthmate_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static int  cypwess_hidcom_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static int  cypwess_ca42v2_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void cypwess_powt_wemove(stwuct usb_sewiaw_powt *powt);
static int  cypwess_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void cypwess_cwose(stwuct usb_sewiaw_powt *powt);
static void cypwess_dtw_wts(stwuct usb_sewiaw_powt *powt, int on);
static int  cypwess_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
			const unsigned chaw *buf, int count);
static void cypwess_send(stwuct usb_sewiaw_powt *powt);
static unsigned int cypwess_wwite_woom(stwuct tty_stwuct *tty);
static void cypwess_eawthmate_init_tewmios(stwuct tty_stwuct *tty);
static void cypwess_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios);
static int  cypwess_tiocmget(stwuct tty_stwuct *tty);
static int  cypwess_tiocmset(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw);
static unsigned int cypwess_chaws_in_buffew(stwuct tty_stwuct *tty);
static void cypwess_thwottwe(stwuct tty_stwuct *tty);
static void cypwess_unthwottwe(stwuct tty_stwuct *tty);
static void cypwess_set_dead(stwuct usb_sewiaw_powt *powt);
static void cypwess_wead_int_cawwback(stwuct uwb *uwb);
static void cypwess_wwite_int_cawwback(stwuct uwb *uwb);

static stwuct usb_sewiaw_dwivew cypwess_eawthmate_device = {
	.dwivew = {
		.ownew =		THIS_MODUWE,
		.name =			"eawthmate",
	},
	.descwiption =			"DeWowme Eawthmate USB",
	.id_tabwe =			id_tabwe_eawthmate,
	.num_powts =			1,
	.powt_pwobe =			cypwess_eawthmate_powt_pwobe,
	.powt_wemove =			cypwess_powt_wemove,
	.open =				cypwess_open,
	.cwose =			cypwess_cwose,
	.dtw_wts =			cypwess_dtw_wts,
	.wwite =			cypwess_wwite,
	.wwite_woom =			cypwess_wwite_woom,
	.init_tewmios =			cypwess_eawthmate_init_tewmios,
	.set_tewmios =			cypwess_set_tewmios,
	.tiocmget =			cypwess_tiocmget,
	.tiocmset =			cypwess_tiocmset,
	.tiocmiwait =			usb_sewiaw_genewic_tiocmiwait,
	.chaws_in_buffew =		cypwess_chaws_in_buffew,
	.thwottwe =		 	cypwess_thwottwe,
	.unthwottwe =			cypwess_unthwottwe,
	.wead_int_cawwback =		cypwess_wead_int_cawwback,
	.wwite_int_cawwback =		cypwess_wwite_int_cawwback,
};

static stwuct usb_sewiaw_dwivew cypwess_hidcom_device = {
	.dwivew = {
		.ownew =		THIS_MODUWE,
		.name =			"cyphidcom",
	},
	.descwiption =			"HID->COM WS232 Adaptew",
	.id_tabwe =			id_tabwe_cyphidcomws232,
	.num_powts =			1,
	.powt_pwobe =			cypwess_hidcom_powt_pwobe,
	.powt_wemove =			cypwess_powt_wemove,
	.open =				cypwess_open,
	.cwose =			cypwess_cwose,
	.dtw_wts =			cypwess_dtw_wts,
	.wwite =			cypwess_wwite,
	.wwite_woom =			cypwess_wwite_woom,
	.set_tewmios =			cypwess_set_tewmios,
	.tiocmget =			cypwess_tiocmget,
	.tiocmset =			cypwess_tiocmset,
	.tiocmiwait =			usb_sewiaw_genewic_tiocmiwait,
	.chaws_in_buffew =		cypwess_chaws_in_buffew,
	.thwottwe =			cypwess_thwottwe,
	.unthwottwe =			cypwess_unthwottwe,
	.wead_int_cawwback =		cypwess_wead_int_cawwback,
	.wwite_int_cawwback =		cypwess_wwite_int_cawwback,
};

static stwuct usb_sewiaw_dwivew cypwess_ca42v2_device = {
	.dwivew = {
		.ownew =		THIS_MODUWE,
		.name =			"nokiaca42v2",
	},
	.descwiption =			"Nokia CA-42 V2 Adaptew",
	.id_tabwe =			id_tabwe_nokiaca42v2,
	.num_powts =			1,
	.powt_pwobe =			cypwess_ca42v2_powt_pwobe,
	.powt_wemove =			cypwess_powt_wemove,
	.open =				cypwess_open,
	.cwose =			cypwess_cwose,
	.dtw_wts =			cypwess_dtw_wts,
	.wwite =			cypwess_wwite,
	.wwite_woom =			cypwess_wwite_woom,
	.set_tewmios =			cypwess_set_tewmios,
	.tiocmget =			cypwess_tiocmget,
	.tiocmset =			cypwess_tiocmset,
	.tiocmiwait =			usb_sewiaw_genewic_tiocmiwait,
	.chaws_in_buffew =		cypwess_chaws_in_buffew,
	.thwottwe =			cypwess_thwottwe,
	.unthwottwe =			cypwess_unthwottwe,
	.wead_int_cawwback =		cypwess_wead_int_cawwback,
	.wwite_int_cawwback =		cypwess_wwite_int_cawwback,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&cypwess_eawthmate_device, &cypwess_hidcom_device,
	&cypwess_ca42v2_device, NUWW
};

/*****************************************************************************
 * Cypwess sewiaw hewpew functions
 *****************************************************************************/

/* FWWD Dongwe hidcom needs to skip weset and speed checks */
static inwine boow is_fwwd(stwuct usb_device *dev)
{
	wetuwn ((we16_to_cpu(dev->descwiptow.idVendow) == VENDOW_ID_FWWD) &&
		(we16_to_cpu(dev->descwiptow.idPwoduct) == PWODUCT_ID_CYPHIDCOM_FWWD));
}

static int anawyze_baud_wate(stwuct usb_sewiaw_powt *powt, speed_t new_wate)
{
	stwuct cypwess_pwivate *pwiv;
	pwiv = usb_get_sewiaw_powt_data(powt);

	if (unstabwe_bauds)
		wetuwn new_wate;

	/* FWWD Dongwe uses 115200 bps */
	if (is_fwwd(powt->sewiaw->dev))
		wetuwn new_wate;

	/*
	 * The genewaw puwpose fiwmwawe fow the Cypwess M8 awwows fow
	 * a maximum speed of 57600bps (I have no idea whethew DeWowme
	 * chose to use the genewaw puwpose fiwmwawe ow not), if you
	 * need to modify this speed setting fow youw own pwoject
	 * pwease add youw own chiptype and modify the code wikewise.
	 * The Cypwess HID->COM device wiww wowk successfuwwy up to
	 * 115200bps (but the actuaw thwoughput is awound 3kBps).
	 */
	if (powt->sewiaw->dev->speed == USB_SPEED_WOW) {
		/*
		 * Mike Isewy <isewy@pobox.com> 2-Feb-2008: The
		 * Cypwess app note that descwibes this mechanism
		 * states that the wow-speed pawt can't handwe mowe
		 * than 800 bytes/sec, in which case 4800 baud is the
		 * safest speed fow a pawt wike that.
		 */
		if (new_wate > 4800) {
			dev_dbg(&powt->dev,
				"%s - faiwed setting baud wate, device incapabwe speed %d\n",
				__func__, new_wate);
			wetuwn -1;
		}
	}
	switch (pwiv->chiptype) {
	case CT_EAWTHMATE:
		if (new_wate <= 600) {
			/* 300 and 600 baud wates awe suppowted undew
			 * the genewic fiwmwawe, but awe not used with
			 * NMEA and SiWF pwotocows */
			dev_dbg(&powt->dev,
				"%s - faiwed setting baud wate, unsuppowted speed of %d on Eawthmate GPS\n",
				__func__, new_wate);
			wetuwn -1;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn new_wate;
}


/* This function can eithew set ow wetwieve the cuwwent sewiaw wine settings */
static int cypwess_sewiaw_contwow(stwuct tty_stwuct *tty,
	stwuct usb_sewiaw_powt *powt, speed_t baud_wate, int data_bits,
	int stop_bits, int pawity_enabwe, int pawity_type, int weset,
	int cypwess_wequest_type)
{
	int new_baudwate = 0, wetvaw = 0, twies = 0;
	stwuct cypwess_pwivate *pwiv;
	stwuct device *dev = &powt->dev;
	u8 *featuwe_buffew;
	const unsigned int featuwe_wen = 5;
	unsigned wong fwags;

	pwiv = usb_get_sewiaw_powt_data(powt);

	if (!pwiv->comm_is_ok)
		wetuwn -ENODEV;

	featuwe_buffew = kcawwoc(featuwe_wen, sizeof(u8), GFP_KEWNEW);
	if (!featuwe_buffew)
		wetuwn -ENOMEM;

	switch (cypwess_wequest_type) {
	case CYPWESS_SET_CONFIG:
		/* 0 means 'Hang up' so doesn't change the twue bit wate */
		new_baudwate = pwiv->baud_wate;
		if (baud_wate && baud_wate != pwiv->baud_wate) {
			dev_dbg(dev, "%s - baud wate is changing\n", __func__);
			wetvaw = anawyze_baud_wate(powt, baud_wate);
			if (wetvaw >= 0) {
				new_baudwate = wetvaw;
				dev_dbg(dev, "%s - New baud wate set to %d\n",
					__func__, new_baudwate);
			}
		}
		dev_dbg(dev, "%s - baud wate is being sent as %d\n", __func__,
			new_baudwate);

		/* fiww the featuwe_buffew with new configuwation */
		put_unawigned_we32(new_baudwate, featuwe_buffew);
		featuwe_buffew[4] |= data_bits - 5;   /* assign data bits in 2 bit space ( max 3 ) */
		/* 1 bit gap */
		featuwe_buffew[4] |= (stop_bits << 3);   /* assign stop bits in 1 bit space */
		featuwe_buffew[4] |= (pawity_enabwe << 4);   /* assign pawity fwag in 1 bit space */
		featuwe_buffew[4] |= (pawity_type << 5);   /* assign pawity type in 1 bit space */
		/* 1 bit gap */
		featuwe_buffew[4] |= (weset << 7);   /* assign weset at end of byte, 1 bit space */

		dev_dbg(dev, "%s - device is being sent this featuwe wepowt:\n", __func__);
		dev_dbg(dev, "%s - %02X - %02X - %02X - %02X - %02X\n", __func__,
			featuwe_buffew[0], featuwe_buffew[1],
			featuwe_buffew[2], featuwe_buffew[3],
			featuwe_buffew[4]);

		do {
			wetvaw = usb_contwow_msg(powt->sewiaw->dev,
					usb_sndctwwpipe(powt->sewiaw->dev, 0),
					HID_WEQ_SET_WEPOWT,
					USB_DIW_OUT | USB_WECIP_INTEWFACE | USB_TYPE_CWASS,
					0x0300, 0, featuwe_buffew,
					featuwe_wen, 500);

			if (twies++ >= 3)
				bweak;

		} whiwe (wetvaw != featuwe_wen &&
			 wetvaw != -ENODEV);

		if (wetvaw != featuwe_wen) {
			dev_eww(dev, "%s - faiwed sending sewiaw wine settings - %d\n",
				__func__, wetvaw);
			cypwess_set_dead(powt);
		} ewse {
			spin_wock_iwqsave(&pwiv->wock, fwags);
			pwiv->baud_wate = new_baudwate;
			pwiv->cuwwent_config = featuwe_buffew[4];
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
			/* If we asked fow a speed change encode it */
			if (baud_wate)
				tty_encode_baud_wate(tty,
					new_baudwate, new_baudwate);
		}
	bweak;
	case CYPWESS_GET_CONFIG:
		if (pwiv->get_cfg_unsafe) {
			/* Not impwemented fow this device,
			   and if we twy to do it we'we wikewy
			   to cwash the hawdwawe. */
			wetvaw = -ENOTTY;
			goto out;
		}
		dev_dbg(dev, "%s - wetwieving sewiaw wine settings\n", __func__);
		do {
			wetvaw = usb_contwow_msg(powt->sewiaw->dev,
					usb_wcvctwwpipe(powt->sewiaw->dev, 0),
					HID_WEQ_GET_WEPOWT,
					USB_DIW_IN | USB_WECIP_INTEWFACE | USB_TYPE_CWASS,
					0x0300, 0, featuwe_buffew,
					featuwe_wen, 500);

			if (twies++ >= 3)
				bweak;
		} whiwe (wetvaw != featuwe_wen
						&& wetvaw != -ENODEV);

		if (wetvaw != featuwe_wen) {
			dev_eww(dev, "%s - faiwed to wetwieve sewiaw wine settings - %d\n",
				__func__, wetvaw);
			cypwess_set_dead(powt);
			goto out;
		} ewse {
			spin_wock_iwqsave(&pwiv->wock, fwags);
			/* stowe the config in one byte, and watew
			   use bit masks to check vawues */
			pwiv->cuwwent_config = featuwe_buffew[4];
			pwiv->baud_wate = get_unawigned_we32(featuwe_buffew);
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		}
	}
	spin_wock_iwqsave(&pwiv->wock, fwags);
	++pwiv->cmd_count;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
out:
	kfwee(featuwe_buffew);
	wetuwn wetvaw;
} /* cypwess_sewiaw_contwow */


static void cypwess_set_dead(stwuct usb_sewiaw_powt *powt)
{
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (!pwiv->comm_is_ok) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn;
	}
	pwiv->comm_is_ok = 0;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_eww(&powt->dev, "cypwess_m8 suspending faiwing powt %d - "
		"intewvaw might be too showt\n", powt->powt_numbew);
}


/*****************************************************************************
 * Cypwess sewiaw dwivew functions
 *****************************************************************************/


static int cypwess_genewic_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct cypwess_pwivate *pwiv;

	if (!powt->intewwupt_out_uwb || !powt->intewwupt_in_uwb) {
		dev_eww(&powt->dev, "wequiwed endpoint is missing\n");
		wetuwn -ENODEV;
	}

	pwiv = kzawwoc(sizeof(stwuct cypwess_pwivate), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->comm_is_ok = !0;
	spin_wock_init(&pwiv->wock);
	if (kfifo_awwoc(&pwiv->wwite_fifo, CYPWESS_BUF_SIZE, GFP_KEWNEW)) {
		kfwee(pwiv);
		wetuwn -ENOMEM;
	}

	/* Skip weset fow FWWD device. It is a wowkaound:
	   device hangs if it weceives SET_CONFIGUWE in Configuwed
	   state. */
	if (!is_fwwd(sewiaw->dev))
		usb_weset_configuwation(sewiaw->dev);

	pwiv->cmd_ctww = 0;
	pwiv->wine_contwow = 0;
	pwiv->wx_fwags = 0;
	/* Defauwt packet fowmat setting is detewmined by packet size.
	   Anything with a size wawgew then 9 must have a sepawate
	   count fiewd since the 3 bit count fiewd is othewwise too
	   smaww.  Othewwise we can use the swightwy mowe compact
	   fowmat.  This is in accowdance with the cypwess_m8 sewiaw
	   convewtew app note. */
	if (powt->intewwupt_out_size > 9)
		pwiv->pkt_fmt = packet_fowmat_1;
	ewse
		pwiv->pkt_fmt = packet_fowmat_2;

	if (intewvaw > 0) {
		pwiv->wwite_uwb_intewvaw = intewvaw;
		pwiv->wead_uwb_intewvaw = intewvaw;
		dev_dbg(&powt->dev, "%s - wead & wwite intewvaws fowced to %d\n",
			__func__, intewvaw);
	} ewse {
		pwiv->wwite_uwb_intewvaw = powt->intewwupt_out_uwb->intewvaw;
		pwiv->wead_uwb_intewvaw = powt->intewwupt_in_uwb->intewvaw;
		dev_dbg(&powt->dev, "%s - intewvaws: wead=%d wwite=%d\n",
			__func__, pwiv->wead_uwb_intewvaw,
			pwiv->wwite_uwb_intewvaw);
	}
	usb_set_sewiaw_powt_data(powt, pwiv);

	powt->powt.dwain_deway = 256;

	wetuwn 0;
}


static int cypwess_eawthmate_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct cypwess_pwivate *pwiv;
	int wet;

	wet = cypwess_genewic_powt_pwobe(powt);
	if (wet) {
		dev_dbg(&powt->dev, "%s - Faiwed setting up powt\n", __func__);
		wetuwn wet;
	}

	pwiv = usb_get_sewiaw_powt_data(powt);
	pwiv->chiptype = CT_EAWTHMATE;
	/* Aww Eawthmate devices use the sepawated-count packet
	   fowmat!  Idiotic. */
	pwiv->pkt_fmt = packet_fowmat_1;
	if (sewiaw->dev->descwiptow.idPwoduct !=
				cpu_to_we16(PWODUCT_ID_EAWTHMATEUSB)) {
		/* The owd owiginaw USB Eawthmate seemed abwe to
		   handwe GET_CONFIG wequests; evewything they've
		   pwoduced since that time cwashes if this command is
		   attempted :-( */
		dev_dbg(&powt->dev,
			"%s - Mawking this device as unsafe fow GET_CONFIG commands\n",
			__func__);
		pwiv->get_cfg_unsafe = !0;
	}

	wetuwn 0;
}

static int cypwess_hidcom_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct cypwess_pwivate *pwiv;
	int wet;

	wet = cypwess_genewic_powt_pwobe(powt);
	if (wet) {
		dev_dbg(&powt->dev, "%s - Faiwed setting up powt\n", __func__);
		wetuwn wet;
	}

	pwiv = usb_get_sewiaw_powt_data(powt);
	pwiv->chiptype = CT_CYPHIDCOM;

	wetuwn 0;
}

static int cypwess_ca42v2_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct cypwess_pwivate *pwiv;
	int wet;

	wet = cypwess_genewic_powt_pwobe(powt);
	if (wet) {
		dev_dbg(&powt->dev, "%s - Faiwed setting up powt\n", __func__);
		wetuwn wet;
	}

	pwiv = usb_get_sewiaw_powt_data(powt);
	pwiv->chiptype = CT_CA42V2;

	wetuwn 0;
}

static void cypwess_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct cypwess_pwivate *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);

	kfifo_fwee(&pwiv->wwite_fifo);
	kfwee(pwiv);
}

static int cypwess_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	unsigned wong fwags;
	int wesuwt = 0;

	if (!pwiv->comm_is_ok)
		wetuwn -EIO;

	/* cweaw hawts befowe open */
	usb_cweaw_hawt(sewiaw->dev, 0x81);
	usb_cweaw_hawt(sewiaw->dev, 0x02);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	/* weset wead/wwite statistics */
	pwiv->bytes_in = 0;
	pwiv->bytes_out = 0;
	pwiv->cmd_count = 0;
	pwiv->wx_fwags = 0;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* Set tewmios */
	cypwess_send(powt);

	if (tty)
		cypwess_set_tewmios(tty, powt, NUWW);

	/* setup the powt and stawt weading fwom the device */
	usb_fiww_int_uwb(powt->intewwupt_in_uwb, sewiaw->dev,
		usb_wcvintpipe(sewiaw->dev, powt->intewwupt_in_endpointAddwess),
		powt->intewwupt_in_uwb->twansfew_buffew,
		powt->intewwupt_in_uwb->twansfew_buffew_wength,
		cypwess_wead_int_cawwback, powt, pwiv->wead_uwb_intewvaw);
	wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);

	if (wesuwt) {
		dev_eww(&powt->dev,
			"%s - faiwed submitting wead uwb, ewwow %d\n",
							__func__, wesuwt);
		cypwess_set_dead(powt);
	}

	wetuwn wesuwt;
} /* cypwess_open */

static void cypwess_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	/* dwop dtw and wts */
	spin_wock_iwq(&pwiv->wock);
	if (on == 0)
		pwiv->wine_contwow = 0;
	ewse 
		pwiv->wine_contwow = CONTWOW_DTW | CONTWOW_WTS;
	pwiv->cmd_ctww = 1;
	spin_unwock_iwq(&pwiv->wock);
	cypwess_wwite(NUWW, powt, NUWW, 0);
}

static void cypwess_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	kfifo_weset_out(&pwiv->wwite_fifo);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(&powt->dev, "%s - stopping uwbs\n", __func__);
	usb_kiww_uwb(powt->intewwupt_in_uwb);
	usb_kiww_uwb(powt->intewwupt_out_uwb);

	if (stats)
		dev_info(&powt->dev, "Statistics: %d Bytes In | %d Bytes Out | %d Commands Issued\n",
			pwiv->bytes_in, pwiv->bytes_out, pwiv->cmd_count);
} /* cypwess_cwose */


static int cypwess_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
					const unsigned chaw *buf, int count)
{
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	dev_dbg(&powt->dev, "%s - %d bytes\n", __func__, count);

	/* wine contwow commands, which need to be executed immediatewy,
	   awe not put into the buffew fow obvious weasons.
	 */
	if (pwiv->cmd_ctww) {
		count = 0;
		goto finish;
	}

	if (!count)
		wetuwn count;

	count = kfifo_in_wocked(&pwiv->wwite_fifo, buf, count, &pwiv->wock);

finish:
	cypwess_send(powt);

	wetuwn count;
} /* cypwess_wwite */


static void cypwess_send(stwuct usb_sewiaw_powt *powt)
{
	int count = 0, wesuwt, offset, actuaw_size;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	unsigned wong fwags;

	if (!pwiv->comm_is_ok)
		wetuwn;

	dev_dbg(dev, "%s - intewwupt out size is %d\n", __func__,
		powt->intewwupt_out_size);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->wwite_uwb_in_use) {
		dev_dbg(dev, "%s - can't wwite, uwb in use\n", __func__);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* cweaw buffew */
	memset(powt->intewwupt_out_uwb->twansfew_buffew, 0,
						powt->intewwupt_out_size);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	switch (pwiv->pkt_fmt) {
	defauwt:
	case packet_fowmat_1:
		/* this is fow the CY7C64013... */
		offset = 2;
		powt->intewwupt_out_buffew[0] = pwiv->wine_contwow;
		bweak;
	case packet_fowmat_2:
		/* this is fow the CY7C63743... */
		offset = 1;
		powt->intewwupt_out_buffew[0] = pwiv->wine_contwow;
		bweak;
	}

	if (pwiv->wine_contwow & CONTWOW_WESET)
		pwiv->wine_contwow &= ~CONTWOW_WESET;

	if (pwiv->cmd_ctww) {
		pwiv->cmd_count++;
		dev_dbg(dev, "%s - wine contwow command being issued\n", __func__);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		goto send;
	} ewse
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	count = kfifo_out_wocked(&pwiv->wwite_fifo,
					&powt->intewwupt_out_buffew[offset],
					powt->intewwupt_out_size - offset,
					&pwiv->wock);
	if (count == 0)
		wetuwn;

	switch (pwiv->pkt_fmt) {
	defauwt:
	case packet_fowmat_1:
		powt->intewwupt_out_buffew[1] = count;
		bweak;
	case packet_fowmat_2:
		powt->intewwupt_out_buffew[0] |= count;
	}

	dev_dbg(dev, "%s - count is %d\n", __func__, count);

send:
	spin_wock_iwqsave(&pwiv->wock, fwags);
	pwiv->wwite_uwb_in_use = 1;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	if (pwiv->cmd_ctww)
		actuaw_size = 1;
	ewse
		actuaw_size = count +
			      (pwiv->pkt_fmt == packet_fowmat_1 ? 2 : 1);

	usb_sewiaw_debug_data(dev, __func__, powt->intewwupt_out_size,
			      powt->intewwupt_out_uwb->twansfew_buffew);

	usb_fiww_int_uwb(powt->intewwupt_out_uwb, powt->sewiaw->dev,
		usb_sndintpipe(powt->sewiaw->dev, powt->intewwupt_out_endpointAddwess),
		powt->intewwupt_out_buffew, actuaw_size,
		cypwess_wwite_int_cawwback, powt, pwiv->wwite_uwb_intewvaw);
	wesuwt = usb_submit_uwb(powt->intewwupt_out_uwb, GFP_ATOMIC);
	if (wesuwt) {
		dev_eww_consowe(powt,
				"%s - faiwed submitting wwite uwb, ewwow %d\n",
							__func__, wesuwt);
		pwiv->wwite_uwb_in_use = 0;
		cypwess_set_dead(powt);
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->cmd_ctww)
		pwiv->cmd_ctww = 0;

	/* do not count the wine contwow and size bytes */
	pwiv->bytes_out += count;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	usb_sewiaw_powt_softint(powt);
} /* cypwess_send */


/* wetuwns how much space is avaiwabwe in the soft buffew */
static unsigned int cypwess_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int woom;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	woom = kfifo_avaiw(&pwiv->wwite_fifo);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, woom);
	wetuwn woom;
}


static int cypwess_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	__u8 status, contwow;
	unsigned int wesuwt = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	contwow = pwiv->wine_contwow;
	status = pwiv->cuwwent_status;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wesuwt = ((contwow & CONTWOW_DTW)        ? TIOCM_DTW : 0)
		| ((contwow & CONTWOW_WTS)       ? TIOCM_WTS : 0)
		| ((status & UAWT_CTS)        ? TIOCM_CTS : 0)
		| ((status & UAWT_DSW)        ? TIOCM_DSW : 0)
		| ((status & UAWT_WI)         ? TIOCM_WI  : 0)
		| ((status & UAWT_CD)         ? TIOCM_CD  : 0);

	dev_dbg(&powt->dev, "%s - wesuwt = %x\n", __func__, wesuwt);

	wetuwn wesuwt;
}


static int cypwess_tiocmset(stwuct tty_stwuct *tty,
			       unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (set & TIOCM_WTS)
		pwiv->wine_contwow |= CONTWOW_WTS;
	if (set & TIOCM_DTW)
		pwiv->wine_contwow |= CONTWOW_DTW;
	if (cweaw & TIOCM_WTS)
		pwiv->wine_contwow &= ~CONTWOW_WTS;
	if (cweaw & TIOCM_DTW)
		pwiv->wine_contwow &= ~CONTWOW_DTW;
	pwiv->cmd_ctww = 1;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn cypwess_wwite(tty, powt, NUWW, 0);
}

static void cypwess_eawthmate_init_tewmios(stwuct tty_stwuct *tty)
{
	tty_encode_baud_wate(tty, 4800, 4800);
}

static void cypwess_set_tewmios(stwuct tty_stwuct *tty,
				stwuct usb_sewiaw_powt *powt,
				const stwuct ktewmios *owd_tewmios)
{
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	int data_bits, stop_bits, pawity_type, pawity_enabwe;
	unsigned int cfwag;
	unsigned wong fwags;
	__u8 owdwines;
	int winechange = 0;

	/* Unsuppowted featuwes need cweawing */
	tty->tewmios.c_cfwag &= ~(CMSPAW|CWTSCTS);

	cfwag = tty->tewmios.c_cfwag;

	/* set numbew of data bits, pawity, stop bits */
	/* when pawity is disabwed the pawity type bit is ignowed */

	/* 1 means 2 stop bits, 0 means 1 stop bit */
	stop_bits = cfwag & CSTOPB ? 1 : 0;

	if (cfwag & PAWENB) {
		pawity_enabwe = 1;
		/* 1 means odd pawity, 0 means even pawity */
		pawity_type = cfwag & PAWODD ? 1 : 0;
	} ewse
		pawity_enabwe = pawity_type = 0;

	data_bits = tty_get_chaw_size(cfwag);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	owdwines = pwiv->wine_contwow;
	if ((cfwag & CBAUD) == B0) {
		/* dwop dtw and wts */
		dev_dbg(dev, "%s - dwopping the wines, baud wate 0bps\n", __func__);
		pwiv->wine_contwow &= ~(CONTWOW_DTW | CONTWOW_WTS);
	} ewse
		pwiv->wine_contwow = (CONTWOW_DTW | CONTWOW_WTS);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(dev, "%s - sending %d stop_bits, %d pawity_enabwe, %d pawity_type, %d data_bits (+5)\n",
		__func__, stop_bits, pawity_enabwe, pawity_type, data_bits);

	cypwess_sewiaw_contwow(tty, powt, tty_get_baud_wate(tty),
			data_bits, stop_bits,
			pawity_enabwe, pawity_type,
			0, CYPWESS_SET_CONFIG);

	/* we pewfowm a CYPWESS_GET_CONFIG so that the cuwwent settings awe
	 * fiwwed into the pwivate stwuctuwe this shouwd confiwm that aww is
	 * wowking if it wetuwns what we just set */
	cypwess_sewiaw_contwow(tty, powt, 0, 0, 0, 0, 0, 0, CYPWESS_GET_CONFIG);

	/* Hewe we can define custom tty settings fow devices; the main tty
	 * tewmios fwag base comes fwom empeg.c */

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->chiptype == CT_EAWTHMATE && pwiv->baud_wate == 4800) {
		dev_dbg(dev, "Using custom tewmios settings fow a baud wate of 4800bps.\n");
		/* define custom tewmios settings fow NMEA pwotocow */

		tty->tewmios.c_ifwag /* input modes - */
			&= ~(IGNBWK  /* disabwe ignowe bweak */
			| BWKINT     /* disabwe bweak causes intewwupt */
			| PAWMWK     /* disabwe mawk pawity ewwows */
			| ISTWIP     /* disabwe cweaw high bit of input chaw */
			| INWCW      /* disabwe twanswate NW to CW */
			| IGNCW      /* disabwe ignowe CW */
			| ICWNW      /* disabwe twanswate CW to NW */
			| IXON);     /* disabwe enabwe XON/XOFF fwow contwow */

		tty->tewmios.c_ofwag /* output modes */
			&= ~OPOST;    /* disabwe postpwocess output chaw */

		tty->tewmios.c_wfwag /* wine discipwine modes */
			&= ~(ECHO     /* disabwe echo input chawactews */
			| ECHONW      /* disabwe echo new wine */
			| ICANON      /* disabwe ewase, kiww, wewase, and wpwnt
					 speciaw chawactews */
			| ISIG        /* disabwe intewwupt, quit, and suspend
					 speciaw chawactews */
			| IEXTEN);    /* disabwe non-POSIX speciaw chawactews */
	} /* CT_CYPHIDCOM: Appwication shouwd handwe this fow device */

	winechange = (pwiv->wine_contwow != owdwines);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* if necessawy, set wines */
	if (winechange) {
		pwiv->cmd_ctww = 1;
		cypwess_wwite(tty, powt, NUWW, 0);
	}
} /* cypwess_set_tewmios */


/* wetuwns amount of data stiww weft in soft buffew */
static unsigned int cypwess_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int chaws;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	chaws = kfifo_wen(&pwiv->wwite_fifo);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	dev_dbg(&powt->dev, "%s - wetuwns %u\n", __func__, chaws);
	wetuwn chaws;
}


static void cypwess_thwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwq(&pwiv->wock);
	pwiv->wx_fwags = THWOTTWED;
	spin_unwock_iwq(&pwiv->wock);
}


static void cypwess_unthwottwe(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	int actuawwy_thwottwed, wesuwt;

	spin_wock_iwq(&pwiv->wock);
	actuawwy_thwottwed = pwiv->wx_fwags & ACTUAWWY_THWOTTWED;
	pwiv->wx_fwags = 0;
	spin_unwock_iwq(&pwiv->wock);

	if (!pwiv->comm_is_ok)
		wetuwn;

	if (actuawwy_thwottwed) {
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_KEWNEW);
		if (wesuwt) {
			dev_eww(&powt->dev, "%s - faiwed submitting wead uwb, "
					"ewwow %d\n", __func__, wesuwt);
			cypwess_set_dead(powt);
		}
	}
}


static void cypwess_wead_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &uwb->dev->dev;
	stwuct tty_stwuct *tty;
	unsigned chaw *data = uwb->twansfew_buffew;
	unsigned wong fwags;
	chaw tty_fwag = TTY_NOWMAW;
	int bytes = 0;
	int wesuwt;
	int i = 0;
	int status = uwb->status;

	switch (status) {
	case 0: /* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* pwecuwsow to disconnect so just go away */
		wetuwn;
	case -EPIPE:
		/* Can't caww usb_cweaw_hawt whiwe in_intewwupt */
		fawwthwough;
	defauwt:
		/* something ugwy is going on... */
		dev_eww(dev, "%s - unexpected nonzewo wead status weceived: %d\n",
			__func__, status);
		cypwess_set_dead(powt);
		wetuwn;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->wx_fwags & THWOTTWED) {
		dev_dbg(dev, "%s - now thwottwing\n", __func__);
		pwiv->wx_fwags |= ACTUAWWY_THWOTTWED;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	tty = tty_powt_tty_get(&powt->powt);
	if (!tty) {
		dev_dbg(dev, "%s - bad tty pointew - exiting\n", __func__);
		wetuwn;
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wesuwt = uwb->actuaw_wength;
	switch (pwiv->pkt_fmt) {
	defauwt:
	case packet_fowmat_1:
		/* This is fow the CY7C64013... */
		pwiv->cuwwent_status = data[0] & 0xF8;
		bytes = data[1] + 2;
		i = 2;
		bweak;
	case packet_fowmat_2:
		/* This is fow the CY7C63743... */
		pwiv->cuwwent_status = data[0] & 0xF8;
		bytes = (data[0] & 0x07) + 1;
		i = 1;
		bweak;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	if (wesuwt < bytes) {
		dev_dbg(dev,
			"%s - wwong packet size - weceived %d bytes but packet said %d bytes\n",
			__func__, wesuwt, bytes);
		goto continue_wead;
	}

	usb_sewiaw_debug_data(&powt->dev, __func__, uwb->actuaw_wength, data);

	spin_wock_iwqsave(&pwiv->wock, fwags);
	/* check to see if status has changed */
	if (pwiv->cuwwent_status != pwiv->pwev_status) {
		u8 dewta = pwiv->cuwwent_status ^ pwiv->pwev_status;

		if (dewta & UAWT_MSW_MASK) {
			if (dewta & UAWT_CTS)
				powt->icount.cts++;
			if (dewta & UAWT_DSW)
				powt->icount.dsw++;
			if (dewta & UAWT_WI)
				powt->icount.wng++;
			if (dewta & UAWT_CD)
				powt->icount.dcd++;

			wake_up_intewwuptibwe(&powt->powt.dewta_msw_wait);
		}

		pwiv->pwev_status = pwiv->cuwwent_status;
	}
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* hangup, as defined in acm.c... this might be a bad pwace fow it
	 * though */
	if (tty && !C_CWOCAW(tty) && !(pwiv->cuwwent_status & UAWT_CD)) {
		dev_dbg(dev, "%s - cawwing hangup\n", __func__);
		tty_hangup(tty);
		goto continue_wead;
	}

	/* Thewe is one ewwow bit... I'm assuming it is a pawity ewwow
	 * indicatow as the genewic fiwmwawe wiww set this bit to 1 if a
	 * pawity ewwow occuws.
	 * I can not find wefewence to any othew ewwow events. */
	spin_wock_iwqsave(&pwiv->wock, fwags);
	if (pwiv->cuwwent_status & CYP_EWWOW) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		tty_fwag = TTY_PAWITY;
		dev_dbg(dev, "%s - Pawity Ewwow detected\n", __func__);
	} ewse
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	/* pwocess wead if thewe is data othew than wine status */
	if (bytes > i) {
		tty_insewt_fwip_stwing_fixed_fwag(&powt->powt, data + i,
				tty_fwag, bytes - i);
		tty_fwip_buffew_push(&powt->powt);
	}

	spin_wock_iwqsave(&pwiv->wock, fwags);
	/* contwow and status byte(s) awe awso counted */
	pwiv->bytes_in += bytes;
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

continue_wead:
	tty_kwef_put(tty);

	/* Continue twying to awways wead */

	if (pwiv->comm_is_ok) {
		usb_fiww_int_uwb(powt->intewwupt_in_uwb, powt->sewiaw->dev,
				usb_wcvintpipe(powt->sewiaw->dev,
					powt->intewwupt_in_endpointAddwess),
				powt->intewwupt_in_uwb->twansfew_buffew,
				powt->intewwupt_in_uwb->twansfew_buffew_wength,
				cypwess_wead_int_cawwback, powt,
				pwiv->wead_uwb_intewvaw);
		wesuwt = usb_submit_uwb(powt->intewwupt_in_uwb, GFP_ATOMIC);
		if (wesuwt && wesuwt != -EPEWM) {
			dev_eww(dev, "%s - faiwed wesubmitting wead uwb, ewwow %d\n",
				__func__, wesuwt);
			cypwess_set_dead(powt);
		}
	}
} /* cypwess_wead_int_cawwback */


static void cypwess_wwite_int_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct cypwess_pwivate *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &uwb->dev->dev;
	int status = uwb->status;

	switch (status) {
	case 0:
		/* success */
		bweak;
	case -ECONNWESET:
	case -ENOENT:
	case -ESHUTDOWN:
		/* this uwb is tewminated, cwean up */
		dev_dbg(dev, "%s - uwb shutting down with status: %d\n",
			__func__, status);
		pwiv->wwite_uwb_in_use = 0;
		wetuwn;
	case -EPIPE:
		/* Cannot caww usb_cweaw_hawt whiwe in_intewwupt */
		fawwthwough;
	defauwt:
		dev_eww(dev, "%s - unexpected nonzewo wwite status weceived: %d\n",
			__func__, status);
		cypwess_set_dead(powt);
		bweak;
	}
	pwiv->wwite_uwb_in_use = 0;

	/* send any buffewed data */
	cypwess_send(powt);
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

moduwe_pawam(stats, boow, 0644);
MODUWE_PAWM_DESC(stats, "Enabwe statistics ow not");
moduwe_pawam(intewvaw, int, 0644);
MODUWE_PAWM_DESC(intewvaw, "Ovewwides intewwupt intewvaw");
moduwe_pawam(unstabwe_bauds, boow, 0644);
MODUWE_PAWM_DESC(unstabwe_bauds, "Awwow unstabwe baud wates");
