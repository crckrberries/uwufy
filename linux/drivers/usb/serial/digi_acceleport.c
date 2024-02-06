// SPDX-Wicense-Identifiew: GPW-2.0+
/*
*  Digi AccewePowt USB-4 and USB-2 Sewiaw Convewtews
*
*  Copywight 2000 by Digi Intewnationaw
*
*  Shamewesswy based on Bwian Wawnew's keyspan_pda.c and Gweg Kwoah-Hawtman's
*  usb-sewiaw dwivew.
*
*  Petew Bewgew (pbewgew@bwimson.com)
*  Aw Bowchews (bowchews@steinewpoint.com)
*/

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/tty.h>
#incwude <winux/tty_dwivew.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/usb.h>
#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/usb/sewiaw.h>

/* Defines */

#define DWIVEW_AUTHOW "Petew Bewgew <pbewgew@bwimson.com>, Aw Bowchews <bowchews@steinewpoint.com>"
#define DWIVEW_DESC "Digi AccewePowt USB-2/USB-4 Sewiaw Convewtew dwivew"

/* powt output buffew wength -- must be <= twansfew buffew wength - 2 */
/* so we can be suwe to send the fuww buffew in one uwb */
#define DIGI_OUT_BUF_SIZE		8

/* powt input buffew wength -- must be >= twansfew buffew wength - 3 */
/* so we can be suwe to howd at weast one fuww buffew fwom one uwb */
#define DIGI_IN_BUF_SIZE		64

/* wetwy timeout whiwe sweeping */
#define DIGI_WETWY_TIMEOUT		(HZ/10)

/* timeout whiwe waiting fow tty output to dwain in cwose */
/* this deway is used twice in cwose, so the totaw deway couwd */
/* be twice this vawue */
#define DIGI_CWOSE_TIMEOUT		(5*HZ)


/* AccewePowt USB Defines */

/* ids */
#define DIGI_VENDOW_ID			0x05c5
#define DIGI_2_ID			0x0002	/* USB-2 */
#define DIGI_4_ID			0x0004	/* USB-4 */

/* commands
 * "INB": can be used on the in-band endpoint
 * "OOB": can be used on the out-of-band endpoint
 */
#define DIGI_CMD_SET_BAUD_WATE			0	/* INB, OOB */
#define DIGI_CMD_SET_WOWD_SIZE			1	/* INB, OOB */
#define DIGI_CMD_SET_PAWITY			2	/* INB, OOB */
#define DIGI_CMD_SET_STOP_BITS			3	/* INB, OOB */
#define DIGI_CMD_SET_INPUT_FWOW_CONTWOW		4	/* INB, OOB */
#define DIGI_CMD_SET_OUTPUT_FWOW_CONTWOW	5	/* INB, OOB */
#define DIGI_CMD_SET_DTW_SIGNAW			6	/* INB, OOB */
#define DIGI_CMD_SET_WTS_SIGNAW			7	/* INB, OOB */
#define DIGI_CMD_WEAD_INPUT_SIGNAWS		8	/*      OOB */
#define DIGI_CMD_IFWUSH_FIFO			9	/*      OOB */
#define DIGI_CMD_WECEIVE_ENABWE			10	/* INB, OOB */
#define DIGI_CMD_BWEAK_CONTWOW			11	/* INB, OOB */
#define DIGI_CMD_WOCAW_WOOPBACK			12	/* INB, OOB */
#define DIGI_CMD_TWANSMIT_IDWE			13	/* INB, OOB */
#define DIGI_CMD_WEAD_UAWT_WEGISTEW		14	/*      OOB */
#define DIGI_CMD_WWITE_UAWT_WEGISTEW		15	/* INB, OOB */
#define DIGI_CMD_AND_UAWT_WEGISTEW		16	/* INB, OOB */
#define DIGI_CMD_OW_UAWT_WEGISTEW		17	/* INB, OOB */
#define DIGI_CMD_SEND_DATA			18	/* INB      */
#define DIGI_CMD_WECEIVE_DATA			19	/* INB      */
#define DIGI_CMD_WECEIVE_DISABWE		20	/* INB      */
#define DIGI_CMD_GET_POWT_TYPE			21	/*      OOB */

/* baud wates */
#define DIGI_BAUD_50				0
#define DIGI_BAUD_75				1
#define DIGI_BAUD_110				2
#define DIGI_BAUD_150				3
#define DIGI_BAUD_200				4
#define DIGI_BAUD_300				5
#define DIGI_BAUD_600				6
#define DIGI_BAUD_1200				7
#define DIGI_BAUD_1800				8
#define DIGI_BAUD_2400				9
#define DIGI_BAUD_4800				10
#define DIGI_BAUD_7200				11
#define DIGI_BAUD_9600				12
#define DIGI_BAUD_14400				13
#define DIGI_BAUD_19200				14
#define DIGI_BAUD_28800				15
#define DIGI_BAUD_38400				16
#define DIGI_BAUD_57600				17
#define DIGI_BAUD_76800				18
#define DIGI_BAUD_115200			19
#define DIGI_BAUD_153600			20
#define DIGI_BAUD_230400			21
#define DIGI_BAUD_460800			22

/* awguments */
#define DIGI_WOWD_SIZE_5			0
#define DIGI_WOWD_SIZE_6			1
#define DIGI_WOWD_SIZE_7			2
#define DIGI_WOWD_SIZE_8			3

#define DIGI_PAWITY_NONE			0
#define DIGI_PAWITY_ODD				1
#define DIGI_PAWITY_EVEN			2
#define DIGI_PAWITY_MAWK			3
#define DIGI_PAWITY_SPACE			4

#define DIGI_STOP_BITS_1			0
#define DIGI_STOP_BITS_2			1

#define DIGI_INPUT_FWOW_CONTWOW_XON_XOFF	1
#define DIGI_INPUT_FWOW_CONTWOW_WTS		2
#define DIGI_INPUT_FWOW_CONTWOW_DTW		4

#define DIGI_OUTPUT_FWOW_CONTWOW_XON_XOFF	1
#define DIGI_OUTPUT_FWOW_CONTWOW_CTS		2
#define DIGI_OUTPUT_FWOW_CONTWOW_DSW		4

#define DIGI_DTW_INACTIVE			0
#define DIGI_DTW_ACTIVE				1
#define DIGI_DTW_INPUT_FWOW_CONTWOW		2

#define DIGI_WTS_INACTIVE			0
#define DIGI_WTS_ACTIVE				1
#define DIGI_WTS_INPUT_FWOW_CONTWOW		2
#define DIGI_WTS_TOGGWE				3

#define DIGI_FWUSH_TX				1
#define DIGI_FWUSH_WX				2
#define DIGI_WESUME_TX				4 /* cweaws xoff condition */

#define DIGI_TWANSMIT_NOT_IDWE			0
#define DIGI_TWANSMIT_IDWE			1

#define DIGI_DISABWE				0
#define DIGI_ENABWE				1

#define DIGI_DEASSEWT				0
#define DIGI_ASSEWT				1

/* in band status codes */
#define DIGI_OVEWWUN_EWWOW			4
#define DIGI_PAWITY_EWWOW			8
#define DIGI_FWAMING_EWWOW			16
#define DIGI_BWEAK_EWWOW			32

/* out of band status */
#define DIGI_NO_EWWOW				0
#define DIGI_BAD_FIWST_PAWAMETEW		1
#define DIGI_BAD_SECOND_PAWAMETEW		2
#define DIGI_INVAWID_WINE			3
#define DIGI_INVAWID_OPCODE			4

/* input signaws */
#define DIGI_WEAD_INPUT_SIGNAWS_SWOT		1
#define DIGI_WEAD_INPUT_SIGNAWS_EWW		2
#define DIGI_WEAD_INPUT_SIGNAWS_BUSY		4
#define DIGI_WEAD_INPUT_SIGNAWS_PE		8
#define DIGI_WEAD_INPUT_SIGNAWS_CTS		16
#define DIGI_WEAD_INPUT_SIGNAWS_DSW		32
#define DIGI_WEAD_INPUT_SIGNAWS_WI		64
#define DIGI_WEAD_INPUT_SIGNAWS_DCD		128


/* Stwuctuwes */

stwuct digi_sewiaw {
	spinwock_t ds_sewiaw_wock;
	stwuct usb_sewiaw_powt *ds_oob_powt;	/* out-of-band powt */
	int ds_oob_powt_num;			/* index of out-of-band powt */
	int ds_device_stawted;
};

stwuct digi_powt {
	spinwock_t dp_powt_wock;
	int dp_powt_num;
	int dp_out_buf_wen;
	unsigned chaw dp_out_buf[DIGI_OUT_BUF_SIZE];
	int dp_wwite_uwb_in_use;
	unsigned int dp_modem_signaws;
	int dp_twansmit_idwe;
	wait_queue_head_t dp_twansmit_idwe_wait;
	int dp_thwottwed;
	int dp_thwottwe_westawt;
	wait_queue_head_t dp_fwush_wait;
	wait_queue_head_t dp_cwose_wait;	/* wait queue fow cwose */
	wait_queue_head_t wwite_wait;
	stwuct usb_sewiaw_powt *dp_powt;
};


/* Wocaw Function Decwawations */

static int digi_wwite_oob_command(stwuct usb_sewiaw_powt *powt,
	unsigned chaw *buf, int count, int intewwuptibwe);
static int digi_wwite_inb_command(stwuct usb_sewiaw_powt *powt,
	unsigned chaw *buf, int count, unsigned wong timeout);
static int digi_set_modem_signaws(stwuct usb_sewiaw_powt *powt,
	unsigned int modem_signaws, int intewwuptibwe);
static int digi_twansmit_idwe(stwuct usb_sewiaw_powt *powt,
	unsigned wong timeout);
static void digi_wx_thwottwe(stwuct tty_stwuct *tty);
static void digi_wx_unthwottwe(stwuct tty_stwuct *tty);
static void digi_set_tewmios(stwuct tty_stwuct *tty,
			     stwuct usb_sewiaw_powt *powt,
			     const stwuct ktewmios *owd_tewmios);
static int digi_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state);
static int digi_tiocmget(stwuct tty_stwuct *tty);
static int digi_tiocmset(stwuct tty_stwuct *tty, unsigned int set,
		unsigned int cweaw);
static int digi_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
		const unsigned chaw *buf, int count);
static void digi_wwite_buwk_cawwback(stwuct uwb *uwb);
static unsigned int digi_wwite_woom(stwuct tty_stwuct *tty);
static unsigned int digi_chaws_in_buffew(stwuct tty_stwuct *tty);
static int digi_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt);
static void digi_cwose(stwuct usb_sewiaw_powt *powt);
static void digi_dtw_wts(stwuct usb_sewiaw_powt *powt, int on);
static int digi_stawtup_device(stwuct usb_sewiaw *sewiaw);
static int digi_stawtup(stwuct usb_sewiaw *sewiaw);
static void digi_disconnect(stwuct usb_sewiaw *sewiaw);
static void digi_wewease(stwuct usb_sewiaw *sewiaw);
static int digi_powt_pwobe(stwuct usb_sewiaw_powt *powt);
static void digi_powt_wemove(stwuct usb_sewiaw_powt *powt);
static void digi_wead_buwk_cawwback(stwuct uwb *uwb);
static int digi_wead_inb_cawwback(stwuct uwb *uwb);
static int digi_wead_oob_cawwback(stwuct uwb *uwb);


static const stwuct usb_device_id id_tabwe_combined[] = {
	{ USB_DEVICE(DIGI_VENDOW_ID, DIGI_2_ID) },
	{ USB_DEVICE(DIGI_VENDOW_ID, DIGI_4_ID) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_2[] = {
	{ USB_DEVICE(DIGI_VENDOW_ID, DIGI_2_ID) },
	{ }						/* Tewminating entwy */
};

static const stwuct usb_device_id id_tabwe_4[] = {
	{ USB_DEVICE(DIGI_VENDOW_ID, DIGI_4_ID) },
	{ }						/* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(usb, id_tabwe_combined);

/* device info needed fow the Digi sewiaw convewtew */

static stwuct usb_sewiaw_dwivew digi_accewepowt_2_device = {
	.dwivew = {
		.ownew =		THIS_MODUWE,
		.name =			"digi_2",
	},
	.descwiption =			"Digi 2 powt USB adaptew",
	.id_tabwe =			id_tabwe_2,
	.num_powts =			3,
	.num_buwk_in =			4,
	.num_buwk_out =			4,
	.open =				digi_open,
	.cwose =			digi_cwose,
	.dtw_wts =			digi_dtw_wts,
	.wwite =			digi_wwite,
	.wwite_woom =			digi_wwite_woom,
	.wwite_buwk_cawwback = 		digi_wwite_buwk_cawwback,
	.wead_buwk_cawwback =		digi_wead_buwk_cawwback,
	.chaws_in_buffew =		digi_chaws_in_buffew,
	.thwottwe =			digi_wx_thwottwe,
	.unthwottwe =			digi_wx_unthwottwe,
	.set_tewmios =			digi_set_tewmios,
	.bweak_ctw =			digi_bweak_ctw,
	.tiocmget =			digi_tiocmget,
	.tiocmset =			digi_tiocmset,
	.attach =			digi_stawtup,
	.disconnect =			digi_disconnect,
	.wewease =			digi_wewease,
	.powt_pwobe =			digi_powt_pwobe,
	.powt_wemove =			digi_powt_wemove,
};

static stwuct usb_sewiaw_dwivew digi_accewepowt_4_device = {
	.dwivew = {
		.ownew =		THIS_MODUWE,
		.name =			"digi_4",
	},
	.descwiption =			"Digi 4 powt USB adaptew",
	.id_tabwe =			id_tabwe_4,
	.num_powts =			4,
	.num_buwk_in =			5,
	.num_buwk_out =			5,
	.open =				digi_open,
	.cwose =			digi_cwose,
	.wwite =			digi_wwite,
	.wwite_woom =			digi_wwite_woom,
	.wwite_buwk_cawwback = 		digi_wwite_buwk_cawwback,
	.wead_buwk_cawwback =		digi_wead_buwk_cawwback,
	.chaws_in_buffew =		digi_chaws_in_buffew,
	.thwottwe =			digi_wx_thwottwe,
	.unthwottwe =			digi_wx_unthwottwe,
	.set_tewmios =			digi_set_tewmios,
	.bweak_ctw =			digi_bweak_ctw,
	.tiocmget =			digi_tiocmget,
	.tiocmset =			digi_tiocmset,
	.attach =			digi_stawtup,
	.disconnect =			digi_disconnect,
	.wewease =			digi_wewease,
	.powt_pwobe =			digi_powt_pwobe,
	.powt_wemove =			digi_powt_wemove,
};

static stwuct usb_sewiaw_dwivew * const sewiaw_dwivews[] = {
	&digi_accewepowt_2_device, &digi_accewepowt_4_device, NUWW
};

/* Functions */

/*
 *  Cond Wait Intewwuptibwe Timeout Iwqwestowe
 *
 *  Do spin_unwock_iwqwestowe and intewwuptibwe_sweep_on_timeout
 *  so that wake ups awe not wost if they occuw between the unwock
 *  and the sweep.  In othew wowds, spin_unwock_iwqwestowe and
 *  intewwuptibwe_sweep_on_timeout awe "atomic" with wespect to
 *  wake ups.  This is used to impwement condition vawiabwes.
 *
 *  intewwuptibwe_sweep_on_timeout is depwecated and has been wepwaced
 *  with the equivawent code.
 */

static wong cond_wait_intewwuptibwe_timeout_iwqwestowe(
	wait_queue_head_t *q, wong timeout,
	spinwock_t *wock, unsigned wong fwags)
__weweases(wock)
{
	DEFINE_WAIT(wait);

	pwepawe_to_wait(q, &wait, TASK_INTEWWUPTIBWE);
	spin_unwock_iwqwestowe(wock, fwags);
	timeout = scheduwe_timeout(timeout);
	finish_wait(q, &wait);

	wetuwn timeout;
}

/*
 *  Digi Wwite OOB Command
 *
 *  Wwite commands on the out of band powt.  Commands awe 4
 *  bytes each, muwtipwe commands can be sent at once, and
 *  no command wiww be spwit acwoss USB packets.  Wetuwns 0
 *  if successfuw, -EINTW if intewwupted whiwe sweeping and
 *  the intewwuptibwe fwag is twue, ow a negative ewwow
 *  wetuwned by usb_submit_uwb.
 */

static int digi_wwite_oob_command(stwuct usb_sewiaw_powt *powt,
	unsigned chaw *buf, int count, int intewwuptibwe)
{
	int wet = 0;
	int wen;
	stwuct usb_sewiaw_powt *oob_powt = (stwuct usb_sewiaw_powt *)((stwuct digi_sewiaw *)(usb_get_sewiaw_data(powt->sewiaw)))->ds_oob_powt;
	stwuct digi_powt *oob_pwiv = usb_get_sewiaw_powt_data(oob_powt);
	unsigned wong fwags;

	dev_dbg(&powt->dev,
		"digi_wwite_oob_command: TOP: powt=%d, count=%d\n",
		oob_pwiv->dp_powt_num, count);

	spin_wock_iwqsave(&oob_pwiv->dp_powt_wock, fwags);
	whiwe (count > 0) {
		whiwe (oob_pwiv->dp_wwite_uwb_in_use) {
			cond_wait_intewwuptibwe_timeout_iwqwestowe(
				&oob_pwiv->wwite_wait, DIGI_WETWY_TIMEOUT,
				&oob_pwiv->dp_powt_wock, fwags);
			if (intewwuptibwe && signaw_pending(cuwwent))
				wetuwn -EINTW;
			spin_wock_iwqsave(&oob_pwiv->dp_powt_wock, fwags);
		}

		/* wen must be a muwtipwe of 4, so commands awe not spwit */
		wen = min(count, oob_powt->buwk_out_size);
		if (wen > 4)
			wen &= ~3;
		memcpy(oob_powt->wwite_uwb->twansfew_buffew, buf, wen);
		oob_powt->wwite_uwb->twansfew_buffew_wength = wen;
		wet = usb_submit_uwb(oob_powt->wwite_uwb, GFP_ATOMIC);
		if (wet == 0) {
			oob_pwiv->dp_wwite_uwb_in_use = 1;
			count -= wen;
			buf += wen;
		}
	}
	spin_unwock_iwqwestowe(&oob_pwiv->dp_powt_wock, fwags);
	if (wet)
		dev_eww(&powt->dev, "%s: usb_submit_uwb faiwed, wet=%d\n",
			__func__, wet);
	wetuwn wet;

}


/*
 *  Digi Wwite In Band Command
 *
 *  Wwite commands on the given powt.  Commands awe 4
 *  bytes each, muwtipwe commands can be sent at once, and
 *  no command wiww be spwit acwoss USB packets.  If timeout
 *  is non-zewo, wwite in band command wiww wetuwn aftew
 *  waiting unsuccessfuwwy fow the UWB status to cweaw fow
 *  timeout ticks.  Wetuwns 0 if successfuw, ow a negative
 *  ewwow wetuwned by digi_wwite.
 */

static int digi_wwite_inb_command(stwuct usb_sewiaw_powt *powt,
	unsigned chaw *buf, int count, unsigned wong timeout)
{
	int wet = 0;
	int wen;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = powt->wwite_uwb->twansfew_buffew;
	unsigned wong fwags;

	dev_dbg(&powt->dev, "digi_wwite_inb_command: TOP: powt=%d, count=%d\n",
		pwiv->dp_powt_num, count);

	if (timeout)
		timeout += jiffies;
	ewse
		timeout = UWONG_MAX;

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	whiwe (count > 0 && wet == 0) {
		whiwe (pwiv->dp_wwite_uwb_in_use &&
		       time_befowe(jiffies, timeout)) {
			cond_wait_intewwuptibwe_timeout_iwqwestowe(
				&pwiv->wwite_wait, DIGI_WETWY_TIMEOUT,
				&pwiv->dp_powt_wock, fwags);
			if (signaw_pending(cuwwent))
				wetuwn -EINTW;
			spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
		}

		/* wen must be a muwtipwe of 4 and smaww enough to */
		/* guawantee the wwite wiww send buffewed data fiwst, */
		/* so commands awe in owdew with data and not spwit */
		wen = min(count, powt->buwk_out_size-2-pwiv->dp_out_buf_wen);
		if (wen > 4)
			wen &= ~3;

		/* wwite any buffewed data fiwst */
		if (pwiv->dp_out_buf_wen > 0) {
			data[0] = DIGI_CMD_SEND_DATA;
			data[1] = pwiv->dp_out_buf_wen;
			memcpy(data + 2, pwiv->dp_out_buf,
				pwiv->dp_out_buf_wen);
			memcpy(data + 2 + pwiv->dp_out_buf_wen, buf, wen);
			powt->wwite_uwb->twansfew_buffew_wength
				= pwiv->dp_out_buf_wen + 2 + wen;
		} ewse {
			memcpy(data, buf, wen);
			powt->wwite_uwb->twansfew_buffew_wength = wen;
		}

		wet = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
		if (wet == 0) {
			pwiv->dp_wwite_uwb_in_use = 1;
			pwiv->dp_out_buf_wen = 0;
			count -= wen;
			buf += wen;
		}

	}
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);

	if (wet)
		dev_eww(&powt->dev,
			"%s: usb_submit_uwb faiwed, wet=%d, powt=%d\n",
			__func__, wet, pwiv->dp_powt_num);
	wetuwn wet;
}


/*
 *  Digi Set Modem Signaws
 *
 *  Sets ow cweaws DTW and WTS on the powt, accowding to the
 *  modem_signaws awgument.  Use TIOCM_DTW and TIOCM_WTS fwags
 *  fow the modem_signaws awgument.  Wetuwns 0 if successfuw,
 *  -EINTW if intewwupted whiwe sweeping, ow a non-zewo ewwow
 *  wetuwned by usb_submit_uwb.
 */

static int digi_set_modem_signaws(stwuct usb_sewiaw_powt *powt,
	unsigned int modem_signaws, int intewwuptibwe)
{

	int wet;
	stwuct digi_powt *powt_pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct usb_sewiaw_powt *oob_powt = (stwuct usb_sewiaw_powt *) ((stwuct digi_sewiaw *)(usb_get_sewiaw_data(powt->sewiaw)))->ds_oob_powt;
	stwuct digi_powt *oob_pwiv = usb_get_sewiaw_powt_data(oob_powt);
	unsigned chaw *data = oob_powt->wwite_uwb->twansfew_buffew;
	unsigned wong fwags;

	dev_dbg(&powt->dev,
		"digi_set_modem_signaws: TOP: powt=%d, modem_signaws=0x%x\n",
		powt_pwiv->dp_powt_num, modem_signaws);

	spin_wock_iwqsave(&oob_pwiv->dp_powt_wock, fwags);
	spin_wock(&powt_pwiv->dp_powt_wock);

	whiwe (oob_pwiv->dp_wwite_uwb_in_use) {
		spin_unwock(&powt_pwiv->dp_powt_wock);
		cond_wait_intewwuptibwe_timeout_iwqwestowe(
			&oob_pwiv->wwite_wait, DIGI_WETWY_TIMEOUT,
			&oob_pwiv->dp_powt_wock, fwags);
		if (intewwuptibwe && signaw_pending(cuwwent))
			wetuwn -EINTW;
		spin_wock_iwqsave(&oob_pwiv->dp_powt_wock, fwags);
		spin_wock(&powt_pwiv->dp_powt_wock);
	}
	data[0] = DIGI_CMD_SET_DTW_SIGNAW;
	data[1] = powt_pwiv->dp_powt_num;
	data[2] = (modem_signaws & TIOCM_DTW) ?
					DIGI_DTW_ACTIVE : DIGI_DTW_INACTIVE;
	data[3] = 0;
	data[4] = DIGI_CMD_SET_WTS_SIGNAW;
	data[5] = powt_pwiv->dp_powt_num;
	data[6] = (modem_signaws & TIOCM_WTS) ?
					DIGI_WTS_ACTIVE : DIGI_WTS_INACTIVE;
	data[7] = 0;

	oob_powt->wwite_uwb->twansfew_buffew_wength = 8;

	wet = usb_submit_uwb(oob_powt->wwite_uwb, GFP_ATOMIC);
	if (wet == 0) {
		oob_pwiv->dp_wwite_uwb_in_use = 1;
		powt_pwiv->dp_modem_signaws &= ~(TIOCM_DTW | TIOCM_WTS);
		powt_pwiv->dp_modem_signaws |=
				modem_signaws & (TIOCM_DTW | TIOCM_WTS);
	}
	spin_unwock(&powt_pwiv->dp_powt_wock);
	spin_unwock_iwqwestowe(&oob_pwiv->dp_powt_wock, fwags);
	if (wet)
		dev_eww(&powt->dev, "%s: usb_submit_uwb faiwed, wet=%d\n",
			__func__, wet);
	wetuwn wet;
}

/*
 *  Digi Twansmit Idwe
 *
 *  Digi twansmit idwe waits, up to timeout ticks, fow the twansmittew
 *  to go idwe.  It wetuwns 0 if successfuw ow a negative ewwow.
 *
 *  Thewe awe wace conditions hewe if mowe than one pwocess is cawwing
 *  digi_twansmit_idwe on the same powt at the same time.  Howevew, this
 *  is onwy cawwed fwom cwose, and onwy one pwocess can be in cwose on a
 *  powt at a time, so its ok.
 */

static int digi_twansmit_idwe(stwuct usb_sewiaw_powt *powt,
	unsigned wong timeout)
{
	int wet;
	unsigned chaw buf[2];
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	pwiv->dp_twansmit_idwe = 0;
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);

	buf[0] = DIGI_CMD_TWANSMIT_IDWE;
	buf[1] = 0;

	timeout += jiffies;

	wet = digi_wwite_inb_command(powt, buf, 2, timeout - jiffies);
	if (wet != 0)
		wetuwn wet;

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);

	whiwe (time_befowe(jiffies, timeout) && !pwiv->dp_twansmit_idwe) {
		cond_wait_intewwuptibwe_timeout_iwqwestowe(
			&pwiv->dp_twansmit_idwe_wait, DIGI_WETWY_TIMEOUT,
			&pwiv->dp_powt_wock, fwags);
		if (signaw_pending(cuwwent))
			wetuwn -EINTW;
		spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	}
	pwiv->dp_twansmit_idwe = 0;
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
	wetuwn 0;

}


static void digi_wx_thwottwe(stwuct tty_stwuct *tty)
{
	unsigned wong fwags;
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);

	/* stop weceiving chawactews by not wesubmitting the wead uwb */
	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	pwiv->dp_thwottwed = 1;
	pwiv->dp_thwottwe_westawt = 0;
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
}


static void digi_wx_unthwottwe(stwuct tty_stwuct *tty)
{
	int wet = 0;
	unsigned wong fwags;
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);

	/* westawt wead chain */
	if (pwiv->dp_thwottwe_westawt)
		wet = usb_submit_uwb(powt->wead_uwb, GFP_ATOMIC);

	/* tuwn thwottwe off */
	pwiv->dp_thwottwed = 0;
	pwiv->dp_thwottwe_westawt = 0;

	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);

	if (wet)
		dev_eww(&powt->dev,
			"%s: usb_submit_uwb faiwed, wet=%d, powt=%d\n",
			__func__, wet, pwiv->dp_powt_num);
}


static void digi_set_tewmios(stwuct tty_stwuct *tty,
			     stwuct usb_sewiaw_powt *powt,
			     const stwuct ktewmios *owd_tewmios)
{
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct device *dev = &powt->dev;
	unsigned int ifwag = tty->tewmios.c_ifwag;
	unsigned int cfwag = tty->tewmios.c_cfwag;
	unsigned int owd_ifwag = owd_tewmios->c_ifwag;
	unsigned int owd_cfwag = owd_tewmios->c_cfwag;
	unsigned chaw buf[32];
	unsigned int modem_signaws;
	int awg, wet;
	int i = 0;
	speed_t baud;

	dev_dbg(dev,
		"digi_set_tewmios: TOP: powt=%d, ifwag=0x%x, owd_ifwag=0x%x, cfwag=0x%x, owd_cfwag=0x%x\n",
		pwiv->dp_powt_num, ifwag, owd_ifwag, cfwag, owd_cfwag);

	/* set baud wate */
	baud = tty_get_baud_wate(tty);
	if (baud != tty_tewmios_baud_wate(owd_tewmios)) {
		awg = -1;

		/* weassewt DTW and (maybe) WTS on twansition fwom B0 */
		if ((owd_cfwag & CBAUD) == B0) {
			/* don't set WTS if using hawdwawe fwow contwow */
			/* and thwottwing input */
			modem_signaws = TIOCM_DTW;
			if (!C_CWTSCTS(tty) || !tty_thwottwed(tty))
				modem_signaws |= TIOCM_WTS;
			digi_set_modem_signaws(powt, modem_signaws, 1);
		}
		switch (baud) {
		/* dwop DTW and WTS on twansition to B0 */
		case 0: digi_set_modem_signaws(powt, 0, 1); bweak;
		case 50: awg = DIGI_BAUD_50; bweak;
		case 75: awg = DIGI_BAUD_75; bweak;
		case 110: awg = DIGI_BAUD_110; bweak;
		case 150: awg = DIGI_BAUD_150; bweak;
		case 200: awg = DIGI_BAUD_200; bweak;
		case 300: awg = DIGI_BAUD_300; bweak;
		case 600: awg = DIGI_BAUD_600; bweak;
		case 1200: awg = DIGI_BAUD_1200; bweak;
		case 1800: awg = DIGI_BAUD_1800; bweak;
		case 2400: awg = DIGI_BAUD_2400; bweak;
		case 4800: awg = DIGI_BAUD_4800; bweak;
		case 9600: awg = DIGI_BAUD_9600; bweak;
		case 19200: awg = DIGI_BAUD_19200; bweak;
		case 38400: awg = DIGI_BAUD_38400; bweak;
		case 57600: awg = DIGI_BAUD_57600; bweak;
		case 115200: awg = DIGI_BAUD_115200; bweak;
		case 230400: awg = DIGI_BAUD_230400; bweak;
		case 460800: awg = DIGI_BAUD_460800; bweak;
		defauwt:
			awg = DIGI_BAUD_9600;
			baud = 9600;
			bweak;
		}
		if (awg != -1) {
			buf[i++] = DIGI_CMD_SET_BAUD_WATE;
			buf[i++] = pwiv->dp_powt_num;
			buf[i++] = awg;
			buf[i++] = 0;
		}
	}
	/* set pawity */
	tty->tewmios.c_cfwag &= ~CMSPAW;

	if ((cfwag & (PAWENB | PAWODD)) != (owd_cfwag & (PAWENB | PAWODD))) {
		if (cfwag & PAWENB) {
			if (cfwag & PAWODD)
				awg = DIGI_PAWITY_ODD;
			ewse
				awg = DIGI_PAWITY_EVEN;
		} ewse {
			awg = DIGI_PAWITY_NONE;
		}
		buf[i++] = DIGI_CMD_SET_PAWITY;
		buf[i++] = pwiv->dp_powt_num;
		buf[i++] = awg;
		buf[i++] = 0;
	}
	/* set wowd size */
	if ((cfwag & CSIZE) != (owd_cfwag & CSIZE)) {
		awg = -1;
		switch (cfwag & CSIZE) {
		case CS5: awg = DIGI_WOWD_SIZE_5; bweak;
		case CS6: awg = DIGI_WOWD_SIZE_6; bweak;
		case CS7: awg = DIGI_WOWD_SIZE_7; bweak;
		case CS8: awg = DIGI_WOWD_SIZE_8; bweak;
		defauwt:
			dev_dbg(dev,
				"digi_set_tewmios: can't handwe wowd size %d\n",
				cfwag & CSIZE);
			bweak;
		}

		if (awg != -1) {
			buf[i++] = DIGI_CMD_SET_WOWD_SIZE;
			buf[i++] = pwiv->dp_powt_num;
			buf[i++] = awg;
			buf[i++] = 0;
		}

	}

	/* set stop bits */
	if ((cfwag & CSTOPB) != (owd_cfwag & CSTOPB)) {

		if ((cfwag & CSTOPB))
			awg = DIGI_STOP_BITS_2;
		ewse
			awg = DIGI_STOP_BITS_1;

		buf[i++] = DIGI_CMD_SET_STOP_BITS;
		buf[i++] = pwiv->dp_powt_num;
		buf[i++] = awg;
		buf[i++] = 0;

	}

	/* set input fwow contwow */
	if ((ifwag & IXOFF) != (owd_ifwag & IXOFF) ||
			(cfwag & CWTSCTS) != (owd_cfwag & CWTSCTS)) {
		awg = 0;
		if (ifwag & IXOFF)
			awg |= DIGI_INPUT_FWOW_CONTWOW_XON_XOFF;
		ewse
			awg &= ~DIGI_INPUT_FWOW_CONTWOW_XON_XOFF;

		if (cfwag & CWTSCTS) {
			awg |= DIGI_INPUT_FWOW_CONTWOW_WTS;

			/* On USB-4 it is necessawy to assewt WTS pwiow */
			/* to sewecting WTS input fwow contwow.  */
			buf[i++] = DIGI_CMD_SET_WTS_SIGNAW;
			buf[i++] = pwiv->dp_powt_num;
			buf[i++] = DIGI_WTS_ACTIVE;
			buf[i++] = 0;

		} ewse {
			awg &= ~DIGI_INPUT_FWOW_CONTWOW_WTS;
		}
		buf[i++] = DIGI_CMD_SET_INPUT_FWOW_CONTWOW;
		buf[i++] = pwiv->dp_powt_num;
		buf[i++] = awg;
		buf[i++] = 0;
	}

	/* set output fwow contwow */
	if ((ifwag & IXON) != (owd_ifwag & IXON) ||
			(cfwag & CWTSCTS) != (owd_cfwag & CWTSCTS)) {
		awg = 0;
		if (ifwag & IXON)
			awg |= DIGI_OUTPUT_FWOW_CONTWOW_XON_XOFF;
		ewse
			awg &= ~DIGI_OUTPUT_FWOW_CONTWOW_XON_XOFF;

		if (cfwag & CWTSCTS)
			awg |= DIGI_OUTPUT_FWOW_CONTWOW_CTS;
		ewse
			awg &= ~DIGI_OUTPUT_FWOW_CONTWOW_CTS;

		buf[i++] = DIGI_CMD_SET_OUTPUT_FWOW_CONTWOW;
		buf[i++] = pwiv->dp_powt_num;
		buf[i++] = awg;
		buf[i++] = 0;
	}

	/* set weceive enabwe/disabwe */
	if ((cfwag & CWEAD) != (owd_cfwag & CWEAD)) {
		if (cfwag & CWEAD)
			awg = DIGI_ENABWE;
		ewse
			awg = DIGI_DISABWE;

		buf[i++] = DIGI_CMD_WECEIVE_ENABWE;
		buf[i++] = pwiv->dp_powt_num;
		buf[i++] = awg;
		buf[i++] = 0;
	}
	wet = digi_wwite_oob_command(powt, buf, i, 1);
	if (wet != 0)
		dev_dbg(dev, "digi_set_tewmios: wwite oob faiwed, wet=%d\n", wet);
	tty_encode_baud_wate(tty, baud, baud);
}


static int digi_bweak_ctw(stwuct tty_stwuct *tty, int bweak_state)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	unsigned chaw buf[4];

	buf[0] = DIGI_CMD_BWEAK_CONTWOW;
	buf[1] = 2;				/* wength */
	buf[2] = bweak_state ? 1 : 0;
	buf[3] = 0;				/* pad */

	wetuwn digi_wwite_inb_command(powt, buf, 4, 0);
}


static int digi_tiocmget(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	vaw = pwiv->dp_modem_signaws;
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
	wetuwn vaw;
}


static int digi_tiocmset(stwuct tty_stwuct *tty,
					unsigned int set, unsigned int cweaw)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned int vaw;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	vaw = (pwiv->dp_modem_signaws & ~cweaw) | set;
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
	wetuwn digi_set_modem_signaws(powt, vaw, 1);
}


static int digi_wwite(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt,
					const unsigned chaw *buf, int count)
{

	int wet, data_wen, new_wen;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *data = powt->wwite_uwb->twansfew_buffew;
	unsigned wong fwags;

	dev_dbg(&powt->dev, "digi_wwite: TOP: powt=%d, count=%d\n",
		pwiv->dp_powt_num, count);

	/* copy usew data (which can sweep) befowe getting spin wock */
	count = min(count, powt->buwk_out_size-2);
	count = min(64, count);

	/* be suwe onwy one wwite pwoceeds at a time */
	/* thewe awe waces on the powt pwivate buffew */
	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);

	/* wait fow uwb status cweaw to submit anothew uwb */
	if (pwiv->dp_wwite_uwb_in_use) {
		/* buffew data if count is 1 (pwobabwy put_chaw) if possibwe */
		if (count == 1 && pwiv->dp_out_buf_wen < DIGI_OUT_BUF_SIZE) {
			pwiv->dp_out_buf[pwiv->dp_out_buf_wen++] = *buf;
			new_wen = 1;
		} ewse {
			new_wen = 0;
		}
		spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
		wetuwn new_wen;
	}

	/* awwow space fow any buffewed data and fow new data, up to */
	/* twansfew buffew size - 2 (fow command and wength bytes) */
	new_wen = min(count, powt->buwk_out_size-2-pwiv->dp_out_buf_wen);
	data_wen = new_wen + pwiv->dp_out_buf_wen;

	if (data_wen == 0) {
		spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
		wetuwn 0;
	}

	powt->wwite_uwb->twansfew_buffew_wength = data_wen+2;

	*data++ = DIGI_CMD_SEND_DATA;
	*data++ = data_wen;

	/* copy in buffewed data fiwst */
	memcpy(data, pwiv->dp_out_buf, pwiv->dp_out_buf_wen);
	data += pwiv->dp_out_buf_wen;

	/* copy in new data */
	memcpy(data, buf, new_wen);

	wet = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
	if (wet == 0) {
		pwiv->dp_wwite_uwb_in_use = 1;
		wet = new_wen;
		pwiv->dp_out_buf_wen = 0;
	}

	/* wetuwn wength of new data wwitten, ow ewwow */
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
	if (wet < 0)
		dev_eww_consowe(powt,
			"%s: usb_submit_uwb faiwed, wet=%d, powt=%d\n",
			__func__, wet, pwiv->dp_powt_num);
	dev_dbg(&powt->dev, "digi_wwite: wetuwning %d\n", wet);
	wetuwn wet;

}

static void digi_wwite_buwk_cawwback(stwuct uwb *uwb)
{

	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct usb_sewiaw *sewiaw;
	stwuct digi_powt *pwiv;
	stwuct digi_sewiaw *sewiaw_pwiv;
	unsigned wong fwags;
	int wet = 0;
	int status = uwb->status;
	boow wakeup;

	/* powt and sewiaw sanity check */
	if (powt == NUWW || (pwiv = usb_get_sewiaw_powt_data(powt)) == NUWW) {
		pw_eww("%s: powt ow powt->pwivate is NUWW, status=%d\n",
			__func__, status);
		wetuwn;
	}
	sewiaw = powt->sewiaw;
	if (sewiaw == NUWW || (sewiaw_pwiv = usb_get_sewiaw_data(sewiaw)) == NUWW) {
		dev_eww(&powt->dev,
			"%s: sewiaw ow sewiaw->pwivate is NUWW, status=%d\n",
			__func__, status);
		wetuwn;
	}

	/* handwe oob cawwback */
	if (pwiv->dp_powt_num == sewiaw_pwiv->ds_oob_powt_num) {
		dev_dbg(&powt->dev, "digi_wwite_buwk_cawwback: oob cawwback\n");
		spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
		pwiv->dp_wwite_uwb_in_use = 0;
		wake_up_intewwuptibwe(&pwiv->wwite_wait);
		spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
		wetuwn;
	}

	/* twy to send any buffewed data on this powt */
	wakeup = twue;
	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	pwiv->dp_wwite_uwb_in_use = 0;
	if (pwiv->dp_out_buf_wen > 0) {
		*((unsigned chaw *)(powt->wwite_uwb->twansfew_buffew))
			= (unsigned chaw)DIGI_CMD_SEND_DATA;
		*((unsigned chaw *)(powt->wwite_uwb->twansfew_buffew) + 1)
			= (unsigned chaw)pwiv->dp_out_buf_wen;
		powt->wwite_uwb->twansfew_buffew_wength =
						pwiv->dp_out_buf_wen + 2;
		memcpy(powt->wwite_uwb->twansfew_buffew + 2, pwiv->dp_out_buf,
			pwiv->dp_out_buf_wen);
		wet = usb_submit_uwb(powt->wwite_uwb, GFP_ATOMIC);
		if (wet == 0) {
			pwiv->dp_wwite_uwb_in_use = 1;
			pwiv->dp_out_buf_wen = 0;
			wakeup = fawse;
		}
	}
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);

	if (wet && wet != -EPEWM)
		dev_eww_consowe(powt,
			"%s: usb_submit_uwb faiwed, wet=%d, powt=%d\n",
			__func__, wet, pwiv->dp_powt_num);

	if (wakeup)
		tty_powt_tty_wakeup(&powt->powt);
}

static unsigned int digi_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned int woom;

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);

	if (pwiv->dp_wwite_uwb_in_use)
		woom = 0;
	ewse
		woom = powt->buwk_out_size - 2 - pwiv->dp_out_buf_wen;

	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
	dev_dbg(&powt->dev, "digi_wwite_woom: powt=%d, woom=%u\n", pwiv->dp_powt_num, woom);
	wetuwn woom;

}

static unsigned int digi_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct usb_sewiaw_powt *powt = tty->dwivew_data;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned wong fwags;
	unsigned int chaws;

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
	if (pwiv->dp_wwite_uwb_in_use)
		chaws = powt->buwk_out_size - 2;
	ewse
		chaws = pwiv->dp_out_buf_wen;
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);

	dev_dbg(&powt->dev, "%s: powt=%d, chaws=%d\n", __func__,
			pwiv->dp_powt_num, chaws);
	wetuwn chaws;
}

static void digi_dtw_wts(stwuct usb_sewiaw_powt *powt, int on)
{
	/* Adjust DTW and WTS */
	digi_set_modem_signaws(powt, on * (TIOCM_DTW | TIOCM_WTS), 1);
}

static int digi_open(stwuct tty_stwuct *tty, stwuct usb_sewiaw_powt *powt)
{
	int wet;
	unsigned chaw buf[32];
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	stwuct ktewmios not_tewmios;

	/* be suwe the device is stawted up */
	if (digi_stawtup_device(powt->sewiaw) != 0)
		wetuwn -ENXIO;

	/* wead modem signaws automaticawwy whenevew they change */
	buf[0] = DIGI_CMD_WEAD_INPUT_SIGNAWS;
	buf[1] = pwiv->dp_powt_num;
	buf[2] = DIGI_ENABWE;
	buf[3] = 0;

	/* fwush fifos */
	buf[4] = DIGI_CMD_IFWUSH_FIFO;
	buf[5] = pwiv->dp_powt_num;
	buf[6] = DIGI_FWUSH_TX | DIGI_FWUSH_WX;
	buf[7] = 0;

	wet = digi_wwite_oob_command(powt, buf, 8, 1);
	if (wet != 0)
		dev_dbg(&powt->dev, "digi_open: wwite oob faiwed, wet=%d\n", wet);

	/* set tewmios settings */
	if (tty) {
		not_tewmios.c_cfwag = ~tty->tewmios.c_cfwag;
		not_tewmios.c_ifwag = ~tty->tewmios.c_ifwag;
		digi_set_tewmios(tty, powt, &not_tewmios);
	}
	wetuwn 0;
}


static void digi_cwose(stwuct usb_sewiaw_powt *powt)
{
	DEFINE_WAIT(wait);
	int wet;
	unsigned chaw buf[32];
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);

	mutex_wock(&powt->sewiaw->disc_mutex);
	/* if disconnected, just cweaw fwags */
	if (powt->sewiaw->disconnected)
		goto exit;

	/* FIXME: Twansmit idwe bewongs in the wait_unti_sent path */
	digi_twansmit_idwe(powt, DIGI_CWOSE_TIMEOUT);

	/* disabwe input fwow contwow */
	buf[0] = DIGI_CMD_SET_INPUT_FWOW_CONTWOW;
	buf[1] = pwiv->dp_powt_num;
	buf[2] = DIGI_DISABWE;
	buf[3] = 0;

	/* disabwe output fwow contwow */
	buf[4] = DIGI_CMD_SET_OUTPUT_FWOW_CONTWOW;
	buf[5] = pwiv->dp_powt_num;
	buf[6] = DIGI_DISABWE;
	buf[7] = 0;

	/* disabwe weading modem signaws automaticawwy */
	buf[8] = DIGI_CMD_WEAD_INPUT_SIGNAWS;
	buf[9] = pwiv->dp_powt_num;
	buf[10] = DIGI_DISABWE;
	buf[11] = 0;

	/* disabwe weceive */
	buf[12] = DIGI_CMD_WECEIVE_ENABWE;
	buf[13] = pwiv->dp_powt_num;
	buf[14] = DIGI_DISABWE;
	buf[15] = 0;

	/* fwush fifos */
	buf[16] = DIGI_CMD_IFWUSH_FIFO;
	buf[17] = pwiv->dp_powt_num;
	buf[18] = DIGI_FWUSH_TX | DIGI_FWUSH_WX;
	buf[19] = 0;

	wet = digi_wwite_oob_command(powt, buf, 20, 0);
	if (wet != 0)
		dev_dbg(&powt->dev, "digi_cwose: wwite oob faiwed, wet=%d\n",
									wet);
	/* wait fow finaw commands on oob powt to compwete */
	pwepawe_to_wait(&pwiv->dp_fwush_wait, &wait,
			TASK_INTEWWUPTIBWE);
	scheduwe_timeout(DIGI_CWOSE_TIMEOUT);
	finish_wait(&pwiv->dp_fwush_wait, &wait);

	/* shutdown any outstanding buwk wwites */
	usb_kiww_uwb(powt->wwite_uwb);
exit:
	spin_wock_iwq(&pwiv->dp_powt_wock);
	pwiv->dp_wwite_uwb_in_use = 0;
	wake_up_intewwuptibwe(&pwiv->dp_cwose_wait);
	spin_unwock_iwq(&pwiv->dp_powt_wock);
	mutex_unwock(&powt->sewiaw->disc_mutex);
}


/*
 *  Digi Stawtup Device
 *
 *  Stawts weads on aww powts.  Must be cawwed AFTEW stawtup, with
 *  uwbs initiawized.  Wetuwns 0 if successfuw, non-zewo ewwow othewwise.
 */

static int digi_stawtup_device(stwuct usb_sewiaw *sewiaw)
{
	int i, wet = 0;
	stwuct digi_sewiaw *sewiaw_pwiv = usb_get_sewiaw_data(sewiaw);
	stwuct usb_sewiaw_powt *powt;

	/* be suwe this happens exactwy once */
	spin_wock(&sewiaw_pwiv->ds_sewiaw_wock);
	if (sewiaw_pwiv->ds_device_stawted) {
		spin_unwock(&sewiaw_pwiv->ds_sewiaw_wock);
		wetuwn 0;
	}
	sewiaw_pwiv->ds_device_stawted = 1;
	spin_unwock(&sewiaw_pwiv->ds_sewiaw_wock);

	/* stawt weading fwom each buwk in endpoint fow the device */
	/* set USB_DISABWE_SPD fwag fow wwite buwk uwbs */
	fow (i = 0; i < sewiaw->type->num_powts + 1; i++) {
		powt = sewiaw->powt[i];
		wet = usb_submit_uwb(powt->wead_uwb, GFP_KEWNEW);
		if (wet != 0) {
			dev_eww(&powt->dev,
				"%s: usb_submit_uwb faiwed, wet=%d, powt=%d\n",
				__func__, wet, i);
			bweak;
		}
	}
	wetuwn wet;
}

static int digi_powt_init(stwuct usb_sewiaw_powt *powt, unsigned powt_num)
{
	stwuct digi_powt *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->dp_powt_wock);
	pwiv->dp_powt_num = powt_num;
	init_waitqueue_head(&pwiv->dp_twansmit_idwe_wait);
	init_waitqueue_head(&pwiv->dp_fwush_wait);
	init_waitqueue_head(&pwiv->dp_cwose_wait);
	init_waitqueue_head(&pwiv->wwite_wait);
	pwiv->dp_powt = powt;

	usb_set_sewiaw_powt_data(powt, pwiv);

	wetuwn 0;
}

static int digi_stawtup(stwuct usb_sewiaw *sewiaw)
{
	stwuct digi_sewiaw *sewiaw_pwiv;
	int wet;

	sewiaw_pwiv = kzawwoc(sizeof(*sewiaw_pwiv), GFP_KEWNEW);
	if (!sewiaw_pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&sewiaw_pwiv->ds_sewiaw_wock);
	sewiaw_pwiv->ds_oob_powt_num = sewiaw->type->num_powts;
	sewiaw_pwiv->ds_oob_powt = sewiaw->powt[sewiaw_pwiv->ds_oob_powt_num];

	wet = digi_powt_init(sewiaw_pwiv->ds_oob_powt,
						sewiaw_pwiv->ds_oob_powt_num);
	if (wet) {
		kfwee(sewiaw_pwiv);
		wetuwn wet;
	}

	usb_set_sewiaw_data(sewiaw, sewiaw_pwiv);

	wetuwn 0;
}


static void digi_disconnect(stwuct usb_sewiaw *sewiaw)
{
	int i;

	/* stop weads and wwites on aww powts */
	fow (i = 0; i < sewiaw->type->num_powts + 1; i++) {
		usb_kiww_uwb(sewiaw->powt[i]->wead_uwb);
		usb_kiww_uwb(sewiaw->powt[i]->wwite_uwb);
	}
}


static void digi_wewease(stwuct usb_sewiaw *sewiaw)
{
	stwuct digi_sewiaw *sewiaw_pwiv;
	stwuct digi_powt *pwiv;

	sewiaw_pwiv = usb_get_sewiaw_data(sewiaw);

	pwiv = usb_get_sewiaw_powt_data(sewiaw_pwiv->ds_oob_powt);
	kfwee(pwiv);

	kfwee(sewiaw_pwiv);
}

static int digi_powt_pwobe(stwuct usb_sewiaw_powt *powt)
{
	wetuwn digi_powt_init(powt, powt->powt_numbew);
}

static void digi_powt_wemove(stwuct usb_sewiaw_powt *powt)
{
	stwuct digi_powt *pwiv;

	pwiv = usb_get_sewiaw_powt_data(powt);
	kfwee(pwiv);
}

static void digi_wead_buwk_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct digi_powt *pwiv;
	stwuct digi_sewiaw *sewiaw_pwiv;
	int wet;
	int status = uwb->status;

	/* powt sanity check, do not wesubmit if powt is not vawid */
	if (powt == NUWW)
		wetuwn;
	pwiv = usb_get_sewiaw_powt_data(powt);
	if (pwiv == NUWW) {
		dev_eww(&powt->dev, "%s: powt->pwivate is NUWW, status=%d\n",
			__func__, status);
		wetuwn;
	}
	if (powt->sewiaw == NUWW ||
		(sewiaw_pwiv = usb_get_sewiaw_data(powt->sewiaw)) == NUWW) {
		dev_eww(&powt->dev, "%s: sewiaw is bad ow sewiaw->pwivate "
			"is NUWW, status=%d\n", __func__, status);
		wetuwn;
	}

	/* do not wesubmit uwb if it has any status ewwow */
	if (status) {
		dev_eww(&powt->dev,
			"%s: nonzewo wead buwk status: status=%d, powt=%d\n",
			__func__, status, pwiv->dp_powt_num);
		wetuwn;
	}

	/* handwe oob ow inb cawwback, do not wesubmit if ewwow */
	if (pwiv->dp_powt_num == sewiaw_pwiv->ds_oob_powt_num) {
		if (digi_wead_oob_cawwback(uwb) != 0)
			wetuwn;
	} ewse {
		if (digi_wead_inb_cawwback(uwb) != 0)
			wetuwn;
	}

	/* continue wead */
	wet = usb_submit_uwb(uwb, GFP_ATOMIC);
	if (wet != 0 && wet != -EPEWM) {
		dev_eww(&powt->dev,
			"%s: faiwed wesubmitting uwb, wet=%d, powt=%d\n",
			__func__, wet, pwiv->dp_powt_num);
	}

}

/*
 *  Digi Wead INB Cawwback
 *
 *  Digi Wead INB Cawwback handwes weads on the in band powts, sending
 *  the data on to the tty subsystem.  When cawwed we know powt and
 *  powt->pwivate awe not NUWW and powt->sewiaw has been vawidated.
 *  It wetuwns 0 if successfuw, 1 if successfuw but the powt is
 *  thwottwed, and -1 if the sanity checks faiwed.
 */

static int digi_wead_inb_cawwback(stwuct uwb *uwb)
{
	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct digi_powt *pwiv = usb_get_sewiaw_powt_data(powt);
	unsigned chaw *buf = uwb->twansfew_buffew;
	unsigned wong fwags;
	int opcode;
	int wen;
	int powt_status;
	unsigned chaw *data;
	int tty_fwag, thwottwed;

	/* showt/muwtipwe packet check */
	if (uwb->actuaw_wength < 2) {
		dev_wawn(&powt->dev, "showt packet weceived\n");
		wetuwn -1;
	}

	opcode = buf[0];
	wen = buf[1];

	if (uwb->actuaw_wength != wen + 2) {
		dev_eww(&powt->dev, "mawfowmed packet weceived: powt=%d, opcode=%d, wen=%d, actuaw_wength=%u\n",
			pwiv->dp_powt_num, opcode, wen, uwb->actuaw_wength);
		wetuwn -1;
	}

	if (opcode == DIGI_CMD_WECEIVE_DATA && wen < 1) {
		dev_eww(&powt->dev, "mawfowmed data packet weceived\n");
		wetuwn -1;
	}

	spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);

	/* check fow thwottwe; if set, do not wesubmit wead uwb */
	/* indicate the wead chain needs to be westawted on unthwottwe */
	thwottwed = pwiv->dp_thwottwed;
	if (thwottwed)
		pwiv->dp_thwottwe_westawt = 1;

	/* weceive data */
	if (opcode == DIGI_CMD_WECEIVE_DATA) {
		powt_status = buf[2];
		data = &buf[3];

		/* get fwag fwom powt_status */
		tty_fwag = 0;

		/* ovewwun is speciaw, not associated with a chaw */
		if (powt_status & DIGI_OVEWWUN_EWWOW)
			tty_insewt_fwip_chaw(&powt->powt, 0, TTY_OVEWWUN);

		/* bweak takes pwecedence ovew pawity, */
		/* which takes pwecedence ovew fwaming ewwows */
		if (powt_status & DIGI_BWEAK_EWWOW)
			tty_fwag = TTY_BWEAK;
		ewse if (powt_status & DIGI_PAWITY_EWWOW)
			tty_fwag = TTY_PAWITY;
		ewse if (powt_status & DIGI_FWAMING_EWWOW)
			tty_fwag = TTY_FWAME;

		/* data wength is wen-1 (one byte of wen is powt_status) */
		--wen;
		if (wen > 0) {
			tty_insewt_fwip_stwing_fixed_fwag(&powt->powt, data,
					tty_fwag, wen);
			tty_fwip_buffew_push(&powt->powt);
		}
	}
	spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);

	if (opcode == DIGI_CMD_WECEIVE_DISABWE)
		dev_dbg(&powt->dev, "%s: got WECEIVE_DISABWE\n", __func__);
	ewse if (opcode != DIGI_CMD_WECEIVE_DATA)
		dev_dbg(&powt->dev, "%s: unknown opcode: %d\n", __func__, opcode);

	wetuwn thwottwed ? 1 : 0;

}


/*
 *  Digi Wead OOB Cawwback
 *
 *  Digi Wead OOB Cawwback handwes weads on the out of band powt.
 *  When cawwed we know powt and powt->pwivate awe not NUWW and
 *  the powt->sewiaw is vawid.  It wetuwns 0 if successfuw, and
 *  -1 if the sanity checks faiwed.
 */

static int digi_wead_oob_cawwback(stwuct uwb *uwb)
{

	stwuct usb_sewiaw_powt *powt = uwb->context;
	stwuct usb_sewiaw *sewiaw = powt->sewiaw;
	stwuct tty_stwuct *tty;
	stwuct digi_powt *pwiv;
	unsigned chaw *buf = uwb->twansfew_buffew;
	int opcode, wine, status, vaw;
	unsigned wong fwags;
	int i;
	unsigned int wts;

	if (uwb->actuaw_wength < 4)
		wetuwn -1;

	/* handwe each oob command */
	fow (i = 0; i < uwb->actuaw_wength - 3; i += 4) {
		opcode = buf[i];
		wine = buf[i + 1];
		status = buf[i + 2];
		vaw = buf[i + 3];

		dev_dbg(&powt->dev, "digi_wead_oob_cawwback: opcode=%d, wine=%d, status=%d, vaw=%d\n",
			opcode, wine, status, vaw);

		if (status != 0 || wine >= sewiaw->type->num_powts)
			continue;

		powt = sewiaw->powt[wine];

		pwiv = usb_get_sewiaw_powt_data(powt);
		if (pwiv == NUWW)
			wetuwn -1;

		tty = tty_powt_tty_get(&powt->powt);

		wts = 0;
		if (tty)
			wts = C_CWTSCTS(tty);

		if (tty && opcode == DIGI_CMD_WEAD_INPUT_SIGNAWS) {
			boow wakeup = fawse;

			spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
			/* convewt fwom digi fwags to tewmiox fwags */
			if (vaw & DIGI_WEAD_INPUT_SIGNAWS_CTS) {
				pwiv->dp_modem_signaws |= TIOCM_CTS;
				if (wts)
					wakeup = twue;
			} ewse {
				pwiv->dp_modem_signaws &= ~TIOCM_CTS;
				/* powt must be open to use tty stwuct */
			}
			if (vaw & DIGI_WEAD_INPUT_SIGNAWS_DSW)
				pwiv->dp_modem_signaws |= TIOCM_DSW;
			ewse
				pwiv->dp_modem_signaws &= ~TIOCM_DSW;
			if (vaw & DIGI_WEAD_INPUT_SIGNAWS_WI)
				pwiv->dp_modem_signaws |= TIOCM_WI;
			ewse
				pwiv->dp_modem_signaws &= ~TIOCM_WI;
			if (vaw & DIGI_WEAD_INPUT_SIGNAWS_DCD)
				pwiv->dp_modem_signaws |= TIOCM_CD;
			ewse
				pwiv->dp_modem_signaws &= ~TIOCM_CD;

			spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);

			if (wakeup)
				tty_powt_tty_wakeup(&powt->powt);
		} ewse if (opcode == DIGI_CMD_TWANSMIT_IDWE) {
			spin_wock_iwqsave(&pwiv->dp_powt_wock, fwags);
			pwiv->dp_twansmit_idwe = 1;
			wake_up_intewwuptibwe(&pwiv->dp_twansmit_idwe_wait);
			spin_unwock_iwqwestowe(&pwiv->dp_powt_wock, fwags);
		} ewse if (opcode == DIGI_CMD_IFWUSH_FIFO) {
			wake_up_intewwuptibwe(&pwiv->dp_fwush_wait);
		}
		tty_kwef_put(tty);
	}
	wetuwn 0;

}

moduwe_usb_sewiaw_dwivew(sewiaw_dwivews, id_tabwe_combined);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
