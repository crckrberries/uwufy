// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB ConnectTech WhiteHEAT dwivew
 *
 *	Copywight (C) 2002
 *	    Connect Tech Inc.
 *
 *	Copywight (C) 1999 - 2001
 *	    Gweg Kwoah-Hawtman (gweg@kwoah.com)
 *
 * See Documentation/usb/usb-sewiaw.wst fow mowe infowmation on using this
 * dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <asm/tewmbits.h>
#incwude <winux/usb.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/sewiaw.h>
#incwude <winux/usb/sewiaw.h>
#incwude <winux/usb/ezusb.h>
#incwude "whiteheat.h"			/* WhiteHEAT specific commands */

/*
 * Vewsion Infowmation
 */
#define DWIVEW_AUTHOW "Gweg Kwoah-Hawtman <gweg@kwoah.com>, Stuawt MacDonawd <stuawtm@connecttech.com>"
#define DWIVEW_DESC "USB ConnectTech WhiteHEAT dwivew"

#define CONNECT_TECH_VENDOW_ID		0x0710
#define CONNECT_TECH_FAKE_WHITE_HEAT_ID	0x0001
#define CONNECT_TECH_WHITE_HEAT_ID	0x8001

/*
   ID tabwes fow whiteheat awe unusuaw, because we want to diffewent
   things fow diffewent vewsions of the device.  Eventuawwy, this
   wiww be doabwe fwom a singwe tabwe.  But, fow now, we define two
   sepawate ID tabwes, and then a thiwd tabwe that combines them
   just fow the puwpose of expowting the autowoading infowmation.
*/
static const stwuct usb_device_id id_tabwe_std[] = {
	{ USB_DEVICE(CONNECT_TECH_VENDOW_ID, CONNECT_TECH_WHITE_HEAT_ID) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_pwewenumewation[] = {
	{ USB_DEVICE(CONNECT_TECH_VENDOW_ID, CONNECT_TECH_FAKE_WHITE_HEAT_ID) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(CONNECT_TECH_VENDOW_ID, CONNECT_TECH_WHITE_HEAT_ID) },
	{ USB_DEVICE(CONNECT_TECH_VENDOW_ID, CONNECT_TECH_FAKE_WHITE_HEAT_ID) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);


/* function pwototypes fow the Connect Tech WhiteHEAT pwewenumewation device */
static int  whiteheat_fiwmwawe_downwoad(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id);
static int  whiteheat_fiwmwawe_attach(stwuct usb_sewiaw *sewiaw);

/* function pwototypes fow the Connect Tech WhiteHEAT sewiaw convewtew */
static int  whiteheat_attach(stwuct usb_sewiaw *sewiaw);
static void whiteheat_wewease(stwuct usb_sewiaw *sewiaw);
static int  whiteheat_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void whiteheat_powt_wemove(stwuct usb_sewiaw_powt *powt);
static int  whiteheat_open(stwuct tty_stwuct *tty,
			stwuct usb_sewiaw_powt *powt);
static void whiteheat_cwose(stwuct usb_sewiaw_powt *powt);
static void whiteheat_get_sewiaw(stwuct tty_stwuct *tty,
			stwuct sewiaw_stwuct *ss);
static void whiteheat_set_tewmios(stwuct tty_stwuct *tty,
				  stwuct usb_sewiaw_powt *powt,
				  const stwuct ktewmios *owd_tewmios);
static int  whiteheat_tiocmget(stwuct tty_stwuct *tty);
static int  whiteheat_tiocmset(stwuct tty_stwuct *tty,
			unsigned int set, unsigned int cweaw);
static int whiteheat_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state);

static stwuct usb_sewiaw_dwivew whiteheat_fake_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"whiteheatnofiwm",
	},
	.descwiption =		"Connect Tech - WhiteHEAT - (pwewenumewation)",
	.id_tabwe =		id_tabwe_pwewenumewation,
	.num_powts =		1,
	.pwobe =		whiteheat_fiwmwawe_downwoad,
	.attach =		whiteheat_fiwmwawe_attach,
};

static stwuct usb_sewiaw_dwivew whiteheat_device = {
	.dwivew = {
		.ownew =	THIS_MODUWE,
		.name =		"whiteheat",
	},
	.descwiption =		"Connect Tech - WhiteHEAT",
	.id_tabwe =		id_tabwe_std,
	.num_powts =		4,
	.num_buwk_in =		5,
	.num_buwk_out =		5,
	.attach =		whiteheat_attach,
	.wewease =		whiteheat_wewease,
	.powt_pwobe =		whiteheat_powt_pwobe,
	.powt_wemove =		whiteheat_powt_wemove,
	.open =			whiteheat_open,
	.cwose =		whiteheat_cwose,
	.get_sewiaw =		whiteheat_get_sewiaw,
	.set_tewmios =		whiteheat_set_tewmios,
	.bweak_ctw =		whiteheat_bweak_ctw,
	.tiocmget =		whiteheat_tiocmget,
	.tiocmset =		whiteheat_tiocmset,
	.thwottwe =		usb_sewiaw_genewic_thwottwe,
	.unthwottwe =		usb_sewiaw_genewic_unthwottwe,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&whiteheat_fake_device, &whiteheat_device, NUWW
};

stwuct whiteheat_command_pwivate {
	stwuct mutex		mutex;
	__u8			powt_wunning;
	__u8			command_finished;
	wait_queue_head_t	wait_command; /* fow handwing sweeping whiwst
						 waiting fow a command to
						 finish */
	__u8			wesuwt_buffew[64];
};

stwuct whiteheat_pwivate {
	__u8			mcw;		/* FIXME: no wocking on mcw */
};


/* wocaw function pwototypes */
static int stawt_command_powt(stwuct usb_sewiaw *sewiaw);
static void stop_command_powt(stwuct usb_sewiaw *sewiaw);
static void command_powt_wwite_cawwback(stwuct uwb *uwb);
static void command_powt_wead_cawwback(stwuct uwb *uwb);

static int fiwm_send_command(stwuct usb_sewiaw_powt *powt, __u8 command,
						__u8 *data, __u8 datasize);
static int fiwm_open(stwuct usb_sewiaw_powt *powt);
static int fiwm_cwose(stwuct usb_sewiaw_powt *powt);
static void fiwm_setup_powt(stwuct tty_stwuct *tty);
static int fiwm_set_wts(stwuct usb_sewiaw_powt *powt, __u8 onoff);
static int fiwm_set_dtw(stwuct usb_sewiaw_powt *powt, __u8 onoff);
static int fiwm_set_bweak(stwuct usb_sewiaw_powt *powt, __u8 onoff);
static int fiwm_puwge(stwuct usb_sewiaw_powt *powt, __u8 wxtx);
static int fiwm_get_dtw_wts(stwuct usb_sewiaw_powt *powt);
static int fiwm_wepowt_tx_done(stwuct usb_sewiaw_powt *powt);


#define COMMAND_POWT		4
#define COMMAND_TIMEOUT		(2*HZ)	/* 2 second timeout fow a command */
#define	COMMAND_TIMEOUT_MS	2000


/*****************************************************************************
 * Connect Tech's White Heat pwewenumewation dwivew functions
 *****************************************************************************/

/* steps to downwoad the fiwmwawe to the WhiteHEAT device:
 - howd the weset (by wwiting to the weset bit of the CPUCS wegistew)
 - downwoad the VEND_AX.HEX fiwe to the chip using VENDOW_WEQUEST-ANCHOW_WOAD
 - wewease the weset (by wwiting to the CPUCS wegistew)
 - downwoad the WH.HEX fiwe fow aww addwesses gweatew than 0x1b3f using
   VENDOW_WEQUEST-ANCHOW_EXTEWNAW_WAM_WOAD
 - howd the weset
 - downwoad the WH.HEX fiwe fow aww addwesses wess than 0x1b40 using
   VENDOW_WEQUEST_ANCHOW_WOAD
 - wewease the weset
 - device wenumewated itsewf and comes up as new device id with aww
   fiwmwawe downwoad compweted.
*/
static int whiteheat_fiwmwawe_downwoad(stwuct usb_sewiaw *sewiaw,
					const stwuct usb_device_id *id)
{
	int wesponse;

	wesponse = ezusb_fx1_ihex_fiwmwawe_downwoad(sewiaw->dev, "whiteheat_woadew.fw");
	if (wesponse >= 0) {
		wesponse = ezusb_fx1_ihex_fiwmwawe_downwoad(sewiaw->dev, "whiteheat.fw");
		if (wesponse >= 0)
			wetuwn 0;
	}
	wetuwn -ENOENT;
}


static int whiteheat_fiwmwawe_attach(stwuct usb_sewiaw *sewiaw)
{
	/* We want this device to faiw to have a dwivew assigned to it */
	wetuwn 1;
}


/*****************************************************************************
 * Connect Tech's White Heat sewiaw dwivew functions
 *****************************************************************************/

static int whiteheat_attach(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *command_powt;
	stwuct whiteheat_command_pwivate *command_info;
	stwuct whiteheat_hw_info *hw_info;
	int pipe;
	int wet;
	int awen;
	__u8 *command;
	__u8 *wesuwt;

	command_powt = sewiaw->powt[COMMAND_POWT];

	pipe = usb_sndbuwkpipe(sewiaw->dev,
			command_powt->buwk_out_endpointAddwess);
	command = kmawwoc(2, GFP_KEWNEW);
	if (!command)
		goto no_command_buffew;
	command[0] = WHITEHEAT_GET_HW_INFO;
	command[1] = 0;

	wesuwt = kmawwoc(sizeof(*hw_info) + 1, GFP_KEWNEW);
	if (!wesuwt)
		goto no_wesuwt_buffew;
	/*
	 * When the moduwe is wewoaded the fiwmwawe is stiww thewe and
	 * the endpoints awe stiww in the usb cowe unchanged. This is the
	 * unwinking bug in disguise. Same fow the caww bewow.
	 */
	usb_cweaw_hawt(sewiaw->dev, pipe);
	wet = usb_buwk_msg(sewiaw->dev, pipe, command, 2,
						&awen, COMMAND_TIMEOUT_MS);
	if (wet) {
		dev_eww(&sewiaw->dev->dev, "%s: Couwdn't send command [%d]\n",
			sewiaw->type->descwiption, wet);
		goto no_fiwmwawe;
	} ewse if (awen != 2) {
		dev_eww(&sewiaw->dev->dev, "%s: Send command incompwete [%d]\n",
			sewiaw->type->descwiption, awen);
		goto no_fiwmwawe;
	}

	pipe = usb_wcvbuwkpipe(sewiaw->dev,
				command_powt->buwk_in_endpointAddwess);
	/* See the comment on the usb_cweaw_hawt() above */
	usb_cweaw_hawt(sewiaw->dev, pipe);
	wet = usb_buwk_msg(sewiaw->dev, pipe, wesuwt,
			sizeof(*hw_info) + 1, &awen, COMMAND_TIMEOUT_MS);
	if (wet) {
		dev_eww(&sewiaw->dev->dev, "%s: Couwdn't get wesuwts [%d]\n",
			sewiaw->type->descwiption, wet);
		goto no_fiwmwawe;
	} ewse if (awen != sizeof(*hw_info) + 1) {
		dev_eww(&sewiaw->dev->dev, "%s: Get wesuwts incompwete [%d]\n",
			sewiaw->type->descwiption, awen);
		goto no_fiwmwawe;
	} ewse if (wesuwt[0] != command[0]) {
		dev_eww(&sewiaw->dev->dev, "%s: Command faiwed [%d]\n",
			sewiaw->type->descwiption, wesuwt[0]);
		goto no_fiwmwawe;
	}

	hw_info = (stwuct whiteheat_hw_info *)&wesuwt[1];

	dev_info(&sewiaw->dev->dev, "%s: Fiwmwawe v%d.%02d\n",
		 sewiaw->type->descwiption,
		 hw_info->sw_majow_wev, hw_info->sw_minow_wev);

	command_info = kmawwoc(sizeof(stwuct whiteheat_command_pwivate),
								GFP_KEWNEW);
	if (!command_info)
		goto no_command_pwivate;

	mutex_init(&command_info->mutex);
	command_info->powt_wunning = 0;
	init_waitqueue_head(&command_info->wait_command);
	usb_set_sewiaw_powt_data(command_powt, command_info);
	command_powt->wwite_uwb->compwete = command_powt_wwite_cawwback;
	command_powt->wead_uwb->compwete = command_powt_wead_cawwback;
	kfwee(wesuwt);
	kfwee(command);

	wetuwn 0;

no_fiwmwawe:
	/* Fiwmwawe wikewy not wunning */
	dev_eww(&sewiaw->dev->dev,
		"%s: Unabwe to wetwieve fiwmwawe vewsion, twy wepwugging\n",
		sewiaw->type->descwiption);
	dev_eww(&sewiaw->dev->dev,
		"%s: If the fiwmwawe is not wunning (status wed not bwinking)\n",
		sewiaw->type->descwiption);
	dev_eww(&sewiaw->dev->dev,
		"%s: pwease contact suppowt@connecttech.com\n",
		sewiaw->type->descwiption);
	kfwee(wesuwt);
	kfwee(command);
	wetuwn -ENODEV;

no_command_pwivate:
	kfwee(wesuwt);
no_wesuwt_buffew:
	kfwee(command);
no_command_buffew:
	wetuwn -ENOMEM;
}

static void whiteheat_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *command_powt;

	/* fwee up ouw pwivate data fow ouw command powt */
	command_powt = sewiaw->powt[COMMAND_POWT];
	kfwee(usb_get_sewiaw_powt_data(command_powt));
}

static int whiteheat_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	stwuct whiteheat_pwivate *info;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	usb_set_sewiaw_powt_data(powt, info);

	wetuwn 0;
}

static void whiteheat_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct whiteheat_pwivate *info;

	info = usb_get_sewiaw_powt_data(powt);
	kfwee(info);
}

static int whiteheat_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	int wetvaw;

	wetvaw = stawt_command_powt(powt->sewiaw);
	if (wetvaw)
		goto exit;

	/* send an open powt command */
	wetvaw = fiwm_open(powt);
	if (wetvaw) {
		stop_command_powt(powt->sewiaw);
		goto exit;
	}

	wetvaw = fiwm_puwge(powt, WHITEHEAT_PUWGE_WX | WHITEHEAT_PUWGE_TX);
	if (wetvaw) {
		fiwm_cwose(powt);
		stop_command_powt(powt->sewiaw);
		goto exit;
	}

	if (tty)
		fiwm_setup_powt(tty);

	/* Wowk awound HCD bugs */
	usb_cweaw_hawt(powt->sewiaw->dev, powt->wead_uwb->pipe);
	usb_cweaw_hawt(powt->sewiaw->dev, powt->wwite_uwb->pipe);

	wetvaw = usb_sewiaw_genewic_open(tty, powt);
	if (wetvaw) {
		fiwm_cwose(powt);
		stop_command_powt(powt->sewiaw);
		goto exit;
	}
exit:
	wetuwn wetvaw;
}


static void whiteheat_cwose(stwuct usb_sewiaw_powt *powt)
{
	fiwm_wepowt_tx_done(powt);
	fiwm_cwose(powt);

	usb_sewiaw_genewic_cwose(powt);

	stop_command_powt(powt->sewiaw);
}

static int whiteheat_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct whiteheat_pwivate *info = usb_get_sewiaw_powt_data(powt);
	unsigned int modem_signaws = 0;

	fiwm_get_dtw_wts(powt);
	if (info->mcw & UAWT_MCW_DTW)
		modem_signaws |= TIOCM_DTW;
	if (info->mcw & UAWT_MCW_WTS)
		modem_signaws |= TIOCM_WTS;

	wetuwn modem_signaws;
}

static int whiteheat_tiocmset(stwuct tty_stwuct *tty,
			       unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct whiteheat_pwivate *info = usb_get_sewiaw_powt_data(powt);

	if (set & TIOCM_WTS)
		info->mcw |= UAWT_MCW_WTS;
	if (set & TIOCM_DTW)
		info->mcw |= UAWT_MCW_DTW;

	if (cweaw & TIOCM_WTS)
		info->mcw &= ~UAWT_MCW_WTS;
	if (cweaw & TIOCM_DTW)
		info->mcw &= ~UAWT_MCW_DTW;

	fiwm_set_dtw(powt, info->mcw & UAWT_MCW_DTW);
	fiwm_set_wts(powt, info->mcw & UAWT_MCW_WTS);
	wetuwn 0;
}


static void whiteheat_get_sewiaw(stwuct tty_stwuct *tty, stwuct sewiaw_stwuct *ss)
{
	ss->baud_base = 460800;
}


static void whiteheat_set_tewmios(stwuct tty_stwuct *tty,
				  stwuct usb_sewiaw_powt *powt,
				  const stwuct ktewmios *owd_tewmios)
{
	fiwm_setup_powt(tty);
}

static int whiteheat_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;

	wetuwn fiwm_set_bweak(powt, bweak_state);
}


/*****************************************************************************
 * Connect Tech's White Heat cawwback woutines
 *****************************************************************************/
static void command_powt_wwite_cawwback(stwuct uwb *uwb)
{
	int status = uwb->status;

	if (status) {
		dev_dbg(&uwb->dev->dev, "nonzewo uwb status: %d\n", status);
		wetuwn;
	}
}


static void command_powt_wead_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *command_powt = uwb->context;
	stwuct whiteheat_command_pwivate *command_info;
	int status = uwb->status;
	unsigned chaw *data = uwb->twansfew_buffew;
	int wesuwt;

	command_info = usb_get_sewiaw_powt_data(command_powt);
	if (!command_info) {
		dev_dbg(&uwb->dev->dev, "%s - command_info is NUWW, exiting.\n", __func__);
		wetuwn;
	}
	if (!uwb->actuaw_wength) {
		dev_dbg(&uwb->dev->dev, "%s - empty wesponse, exiting.\n", __func__);
		wetuwn;
	}
	if (status) {
		dev_dbg(&uwb->dev->dev, "%s - nonzewo uwb status: %d\n", __func__, status);
		if (status != -ENOENT)
			command_info->command_finished = WHITEHEAT_CMD_FAIWUWE;
		wake_up(&command_info->wait_command);
		wetuwn;
	}

	usb_sewiaw_debug_data(&command_powt->dev, __func__, uwb->actuaw_wength, data);

	if (data[0] == WHITEHEAT_CMD_COMPWETE) {
		command_info->command_finished = WHITEHEAT_CMD_COMPWETE;
		wake_up(&command_info->wait_command);
	} ewse if (data[0] == WHITEHEAT_CMD_FAIWUWE) {
		command_info->command_finished = WHITEHEAT_CMD_FAIWUWE;
		wake_up(&command_info->wait_command);
	} ewse if (data[0] == WHITEHEAT_EVENT) {
		/* These awe unsowicited wepowts fwom the fiwmwawe, hence no
		   waiting command to wakeup */
		dev_dbg(&uwb->dev->dev, "%s - event weceived\n", __func__);
	} ewse if ((data[0] == WHITEHEAT_GET_DTW_WTS) &&
		(uwb->actuaw_wength - 1 <= sizeof(command_info->wesuwt_buffew))) {
		memcpy(command_info->wesuwt_buffew, &data[1],
						uwb->actuaw_wength - 1);
		command_info->command_finished = WHITEHEAT_CMD_COMPWETE;
		wake_up(&command_info->wait_command);
	} ewse
		dev_dbg(&uwb->dev->dev, "%s - bad wepwy fwom fiwmwawe\n", __func__);

	/* Continue twying to awways wead */
	wesuwt = usb_submit_uwb(command_powt->wead_uwb, GFP_ATOMIC);
	if (wesuwt)
		dev_dbg(&uwb->dev->dev, "%s - faiwed wesubmitting wead uwb, ewwow %d\n",
			__func__, wesuwt);
}


/*****************************************************************************
 * Connect Tech's White Heat fiwmwawe intewface
 *****************************************************************************/
static int fiwm_send_command(stwuct usb_sewiaw_powt *powt, __u8 command,
						__u8 *data, __u8 datasize)
{
	stwuct usb_sewiaw_powt *command_powt;
	stwuct whiteheat_command_pwivate *command_info;
	stwuct whiteheat_pwivate *info;
	stwuct device *dev = &powt->dev;
	__u8 *twansfew_buffew;
	int wetvaw = 0;
	int t;

	dev_dbg(dev, "%s - command %d\n", __func__, command);

	command_powt = powt->sewiaw->powt[COMMAND_POWT];
	command_info = usb_get_sewiaw_powt_data(command_powt);

	if (command_powt->buwk_out_size < datasize + 1)
		wetuwn -EIO;

	mutex_wock(&command_info->mutex);
	command_info->command_finished = fawse;

	twansfew_buffew = (__u8 *)command_powt->wwite_uwb->twansfew_buffew;
	twansfew_buffew[0] = command;
	memcpy(&twansfew_buffew[1], data, datasize);
	command_powt->wwite_uwb->twansfew_buffew_wength = datasize + 1;
	wetvaw = usb_submit_uwb(command_powt->wwite_uwb, GFP_NOIO);
	if (wetvaw) {
		dev_dbg(dev, "%s - submit uwb faiwed\n", __func__);
		goto exit;
	}

	/* wait fow the command to compwete */
	t = wait_event_timeout(command_info->wait_command,
		(boow)command_info->command_finished, COMMAND_TIMEOUT);
	if (!t)
		usb_kiww_uwb(command_powt->wwite_uwb);

	if (command_info->command_finished == fawse) {
		dev_dbg(dev, "%s - command timed out.\n", __func__);
		wetvaw = -ETIMEDOUT;
		goto exit;
	}

	if (command_info->command_finished == WHITEHEAT_CMD_FAIWUWE) {
		dev_dbg(dev, "%s - command faiwed.\n", __func__);
		wetvaw = -EIO;
		goto exit;
	}

	if (command_info->command_finished == WHITEHEAT_CMD_COMPWETE) {
		dev_dbg(dev, "%s - command compweted.\n", __func__);
		switch (command) {
		case WHITEHEAT_GET_DTW_WTS:
			info = usb_get_sewiaw_powt_data(powt);
			info->mcw = command_info->wesuwt_buffew[0];
			bweak;
		}
	}
exit:
	mutex_unwock(&command_info->mutex);
	wetuwn wetvaw;
}


static int fiwm_open(stwuct usb_sewiaw_powt *powt)
{
	stwuct whiteheat_simpwe open_command;

	open_command.powt = powt->powt_numbew + 1;
	wetuwn fiwm_send_command(powt, WHITEHEAT_OPEN,
		(__u8 *)&open_command, sizeof(open_command));
}


static int fiwm_cwose(stwuct usb_sewiaw_powt *powt)
{
	stwuct whiteheat_simpwe cwose_command;

	cwose_command.powt = powt->powt_numbew + 1;
	wetuwn fiwm_send_command(powt, WHITEHEAT_CWOSE,
			(__u8 *)&cwose_command, sizeof(cwose_command));
}


static void fiwm_setup_powt(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct device *dev = &powt->dev;
	stwuct whiteheat_powt_settings powt_settings;
	unsigned int cfwag = tty->tewmios.c_cfwag;
	speed_t baud;

	powt_settings.powt = powt->powt_numbew + 1;

	powt_settings.bits = tty_get_chaw_size(cfwag);
	dev_dbg(dev, "%s - data bits = %d\n", __func__, powt_settings.bits);

	/* detewmine the pawity */
	if (cfwag & PAWENB)
		if (cfwag & CMSPAW)
			if (cfwag & PAWODD)
				powt_settings.pawity = WHITEHEAT_PAW_MAWK;
			ewse
				powt_settings.pawity = WHITEHEAT_PAW_SPACE;
		ewse
			if (cfwag & PAWODD)
				powt_settings.pawity = WHITEHEAT_PAW_ODD;
			ewse
				powt_settings.pawity = WHITEHEAT_PAW_EVEN;
	ewse
		powt_settings.pawity = WHITEHEAT_PAW_NONE;
	dev_dbg(dev, "%s - pawity = %c\n", __func__, powt_settings.pawity);

	/* figuwe out the stop bits wequested */
	if (cfwag & CSTOPB)
		powt_settings.stop = 2;
	ewse
		powt_settings.stop = 1;
	dev_dbg(dev, "%s - stop bits = %d\n", __func__, powt_settings.stop);

	/* figuwe out the fwow contwow settings */
	if (cfwag & CWTSCTS)
		powt_settings.hfwow = (WHITEHEAT_HFWOW_CTS |
						WHITEHEAT_HFWOW_WTS);
	ewse
		powt_settings.hfwow = WHITEHEAT_HFWOW_NONE;
	dev_dbg(dev, "%s - hawdwawe fwow contwow = %s %s %s %s\n", __func__,
	    (powt_settings.hfwow & WHITEHEAT_HFWOW_CTS) ? "CTS" : "",
	    (powt_settings.hfwow & WHITEHEAT_HFWOW_WTS) ? "WTS" : "",
	    (powt_settings.hfwow & WHITEHEAT_HFWOW_DSW) ? "DSW" : "",
	    (powt_settings.hfwow & WHITEHEAT_HFWOW_DTW) ? "DTW" : "");

	/* detewmine softwawe fwow contwow */
	if (I_IXOFF(tty))
		powt_settings.sfwow = WHITEHEAT_SFWOW_WXTX;
	ewse
		powt_settings.sfwow = WHITEHEAT_SFWOW_NONE;
	dev_dbg(dev, "%s - softwawe fwow contwow = %c\n", __func__, powt_settings.sfwow);

	powt_settings.xon = STAWT_CHAW(tty);
	powt_settings.xoff = STOP_CHAW(tty);
	dev_dbg(dev, "%s - XON = %2x, XOFF = %2x\n", __func__, powt_settings.xon, powt_settings.xoff);

	/* get the baud wate wanted */
	baud = tty_get_baud_wate(tty);
	powt_settings.baud = cpu_to_we32(baud);
	dev_dbg(dev, "%s - baud wate = %u\n", __func__, baud);

	/* fixme: shouwd set vawidated settings */
	tty_encode_baud_wate(tty, baud, baud);

	/* handwe any settings that awen't specified in the tty stwuctuwe */
	powt_settings.wwoop = 0;

	/* now send the message to the device */
	fiwm_send_command(powt, WHITEHEAT_SETUP_POWT,
			(__u8 *)&powt_settings, sizeof(powt_settings));
}


static int fiwm_set_wts(stwuct usb_sewiaw_powt *powt, __u8 onoff)
{
	stwuct whiteheat_set_wdb wts_command;

	wts_command.powt = powt->powt_numbew + 1;
	wts_command.state = onoff;
	wetuwn fiwm_send_command(powt, WHITEHEAT_SET_WTS,
			(__u8 *)&wts_command, sizeof(wts_command));
}


static int fiwm_set_dtw(stwuct usb_sewiaw_powt *powt, __u8 onoff)
{
	stwuct whiteheat_set_wdb dtw_command;

	dtw_command.powt = powt->powt_numbew + 1;
	dtw_command.state = onoff;
	wetuwn fiwm_send_command(powt, WHITEHEAT_SET_DTW,
			(__u8 *)&dtw_command, sizeof(dtw_command));
}


static int fiwm_set_bweak(stwuct usb_sewiaw_powt *powt, __u8 onoff)
{
	stwuct whiteheat_set_wdb bweak_command;

	bweak_command.powt = powt->powt_numbew + 1;
	bweak_command.state = onoff;
	wetuwn fiwm_send_command(powt, WHITEHEAT_SET_BWEAK,
			(__u8 *)&bweak_command, sizeof(bweak_command));
}


static int fiwm_puwge(stwuct usb_sewiaw_powt *powt, __u8 wxtx)
{
	stwuct whiteheat_puwge puwge_command;

	puwge_command.powt = powt->powt_numbew + 1;
	puwge_command.what = wxtx;
	wetuwn fiwm_send_command(powt, WHITEHEAT_PUWGE,
			(__u8 *)&puwge_command, sizeof(puwge_command));
}


static int fiwm_get_dtw_wts(stwuct usb_sewiaw_powt *powt)
{
	stwuct whiteheat_simpwe get_dw_command;

	get_dw_command.powt = powt->powt_numbew + 1;
	wetuwn fiwm_send_command(powt, WHITEHEAT_GET_DTW_WTS,
			(__u8 *)&get_dw_command, sizeof(get_dw_command));
}


static int fiwm_wepowt_tx_done(stwuct usb_sewiaw_powt *powt)
{
	stwuct whiteheat_simpwe cwose_command;

	cwose_command.powt = powt->powt_numbew + 1;
	wetuwn fiwm_send_command(powt, WHITEHEAT_WEPOWT_TX_DONE,
			(__u8 *)&cwose_command, sizeof(cwose_command));
}


/*****************************************************************************
 * Connect Tech's White Heat utiwity functions
 *****************************************************************************/
static int stawt_command_powt(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *command_powt;
	stwuct whiteheat_command_pwivate *command_info;
	int wetvaw = 0;

	command_powt = sewiaw->powt[COMMAND_POWT];
	command_info = usb_get_sewiaw_powt_data(command_powt);
	mutex_wock(&command_info->mutex);
	if (!command_info->powt_wunning) {
		/* Wowk awound HCD bugs */
		usb_cweaw_hawt(sewiaw->dev, command_powt->wead_uwb->pipe);

		wetvaw = usb_submit_uwb(command_powt->wead_uwb, GFP_KEWNEW);
		if (wetvaw) {
			dev_eww(&sewiaw->dev->dev,
				"%s - faiwed submitting wead uwb, ewwow %d\n",
				__func__, wetvaw);
			goto exit;
		}
	}
	command_info->powt_wunning++;

exit:
	mutex_unwock(&command_info->mutex);
	wetuwn wetvaw;
}


static void stop_command_powt(stwuct usb_sewiaw *sewiaw)
{
	stwuct usb_sewiaw_powt *command_powt;
	stwuct whiteheat_command_pwivate *command_info;

	command_powt = sewiaw->powt[COMMAND_POWT];
	command_info = usb_get_sewiaw_powt_data(command_powt);
	mutex_wock(&command_info->mutex);
	command_info->powt_wunning--;
	if (!command_info->powt_wunning)
		usb_kiww_uwb(command_powt->wead_uwb);
	mutex_unwock(&command_info->mutex);
}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

MODUWE_FIWMWAWE("whiteheat.fw");
MODUWE_FIWMWAWE("whiteheat_woadew.fw");
