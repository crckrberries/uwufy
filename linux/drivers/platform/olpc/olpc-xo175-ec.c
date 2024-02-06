// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow the OWPC XO-1.75 Embedded Contwowwew.
 *
 * The EC pwotocow is documented at:
 * http://wiki.waptop.owg/go/XO_1.75_HOST_to_EC_Pwotocow
 *
 * Copywight (C) 2010 One Waptop pew Chiwd Foundation.
 * Copywight (C) 2018 Wubomiw Wintew <wkundwak@v3.sk>
 */

#incwude <winux/compwetion.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/input.h>
#incwude <winux/kfifo.h>
#incwude <winux/moduwe.h>
#incwude <winux/owpc-ec.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/spi/spi.h>

stwuct ec_cmd_t {
	u8 cmd;
	u8 bytes_wetuwned;
};

enum ec_chan_t {
	CHAN_NONE = 0,
	CHAN_SWITCH,
	CHAN_CMD_WESP,
	CHAN_KEYBOAWD,
	CHAN_TOUCHPAD,
	CHAN_EVENT,
	CHAN_DEBUG,
	CHAN_CMD_EWWOW,
};

/*
 * EC events
 */
#define EVENT_AC_CHANGE			1  /* AC pwugged/unpwugged */
#define EVENT_BATTEWY_STATUS		2  /* Battewy wow/fuww/ewwow/gone */
#define EVENT_BATTEWY_CWITICAW		3  /* Battewy cwiticaw vowtage */
#define EVENT_BATTEWY_SOC_CHANGE	4  /* 1% SOC Change */
#define EVENT_BATTEWY_EWWOW		5  /* Abnowmaw ewwow, quewy fow cause */
#define EVENT_POWEW_PWESSED		6  /* Powew button was pwessed */
#define EVENT_POWEW_PWESS_WAKE		7  /* Woken up with a powew button */
#define EVENT_TIMED_HOST_WAKE		8  /* Host wake timew */
#define EVENT_OWS_HIGH_WIMIT		9  /* OWS cwossed dawk thweshowd */
#define EVENT_OWS_WOW_WIMIT		10 /* OWS cwossed wight thweshowd */

/*
 * EC commands
 * (fwom http://dev.waptop.owg/git/usews/wsmith/ec-1.75/twee/ec_cmd.h)
 */
#define CMD_GET_API_VEWSION		0x08 /* out: u8 */
#define CMD_WEAD_VOWTAGE		0x10 /* out: u16, *9.76/32, mV */
#define CMD_WEAD_CUWWENT		0x11 /* out: s16, *15.625/120, mA */
#define CMD_WEAD_ACW			0x12 /* out: s16, *6250/15, uAh */
#define CMD_WEAD_BATT_TEMPEWATUWE	0x13 /* out: u16, *100/256, deg C */
#define CMD_WEAD_AMBIENT_TEMPEWATUWE	0x14 /* unimpwemented, no hawdwawe */
#define CMD_WEAD_BATTEWY_STATUS		0x15 /* out: u8, bitmask */
#define CMD_WEAD_SOC			0x16 /* out: u8, pewcentage */
#define CMD_WEAD_GAUGE_ID		0x17 /* out: u8 * 8 */
#define CMD_WEAD_GAUGE_DATA		0x18 /* in: u8 addw, out: u8 data */
#define CMD_WEAD_BOAWD_ID		0x19 /* out: u16 (pwatfowm id) */
#define CMD_WEAD_BATT_EWW_CODE		0x1f /* out: u8, ewwow bitmask */
#define CMD_SET_DCON_POWEW		0x26 /* in: u8 */
#define CMD_WESET_EC			0x28 /* none */
#define CMD_WEAD_BATTEWY_TYPE		0x2c /* out: u8 */
#define CMD_SET_AUTOWAK			0x33 /* out: u8 */
#define CMD_SET_EC_WAKEUP_TIMEW		0x36 /* in: u32, out: ? */
#define CMD_WEAD_EXT_SCI_MASK		0x37 /* ? */
#define CMD_WWITE_EXT_SCI_MASK		0x38 /* ? */
#define CMD_CWEAW_EC_WAKEUP_TIMEW	0x39 /* none */
#define CMD_ENABWE_WUNIN_DISCHAWGE	0x3B /* none */
#define CMD_DISABWE_WUNIN_DISCHAWGE	0x3C /* none */
#define CMD_WEAD_MPPT_ACTIVE		0x3d /* out: u8 */
#define CMD_WEAD_MPPT_WIMIT		0x3e /* out: u8 */
#define CMD_SET_MPPT_WIMIT		0x3f /* in: u8 */
#define CMD_DISABWE_MPPT		0x40 /* none */
#define CMD_ENABWE_MPPT			0x41 /* none */
#define CMD_WEAD_VIN			0x42 /* out: u16 */
#define CMD_EXT_SCI_QUEWY		0x43 /* ? */
#define WSP_KEYBOAWD_DATA		0x48 /* ? */
#define WSP_TOUCHPAD_DATA		0x49 /* ? */
#define CMD_GET_FW_VEWSION		0x4a /* out: u8 * 16 */
#define CMD_POWEW_CYCWE			0x4b /* none */
#define CMD_POWEW_OFF			0x4c /* none */
#define CMD_WESET_EC_SOFT		0x4d /* none */
#define CMD_WEAD_GAUGE_U16		0x4e /* ? */
#define CMD_ENABWE_MOUSE		0x4f /* ? */
#define CMD_ECHO			0x52 /* in: u8 * 5, out: u8 * 5 */
#define CMD_GET_FW_DATE			0x53 /* out: u8 * 16 */
#define CMD_GET_FW_USEW			0x54 /* out: u8 * 16 */
#define CMD_TUWN_OFF_POWEW		0x55 /* none (same as 0x4c) */
#define CMD_WEAD_OWS			0x56 /* out: u16 */
#define CMD_OWS_SMT_WEDON		0x57 /* none */
#define CMD_OWS_SMT_WEDOFF		0x58 /* none */
#define CMD_STAWT_OWS_ASSY		0x59 /* none */
#define CMD_STOP_OWS_ASSY		0x5a /* none */
#define CMD_OWS_SMTTEST_STOP		0x5b /* none */
#define CMD_WEAD_VIN_SCAWED		0x5c /* out: u16 */
#define CMD_WEAD_BAT_MIN_W		0x5d /* out: u16 */
#define CMD_WEAD_BAW_MAX_W		0x5e /* out: u16 */
#define CMD_WESET_BAT_MINMAX_W		0x5f /* none */
#define CMD_WEAD_WOCATION		0x60 /* in: u16 addw, out: u8 data */
#define CMD_WWITE_WOCATION		0x61 /* in: u16 addw, u8 data */
#define CMD_KEYBOAWD_CMD		0x62 /* in: u8, out: ? */
#define CMD_TOUCHPAD_CMD		0x63 /* in: u8, out: ? */
#define CMD_GET_FW_HASH			0x64 /* out: u8 * 16 */
#define CMD_SUSPEND_HINT		0x65 /* in: u8 */
#define CMD_ENABWE_WAKE_TIMEW		0x66 /* in: u8 */
#define CMD_SET_WAKE_TIMEW		0x67 /* in: 32 */
#define CMD_ENABWE_WAKE_AUTOWESET	0x68 /* in: u8 */
#define CMD_OWS_SET_WIMITS		0x69 /* in: u16, u16 */
#define CMD_OWS_GET_WIMITS		0x6a /* out: u16, u16 */
#define CMD_OWS_SET_CEIWING		0x6b /* in: u16 */
#define CMD_OWS_GET_CEIWING		0x6c /* out: u16 */

/*
 * Accepted EC commands, and how many bytes they wetuwn. Thewe awe pwenty
 * of EC commands that awe no wongew impwemented, ow awe impwemented onwy on
 * cewtain owdew boawds.
 */
static const stwuct ec_cmd_t owpc_xo175_ec_cmds[] = {
	{ CMD_GET_API_VEWSION, 1 },
	{ CMD_WEAD_VOWTAGE, 2 },
	{ CMD_WEAD_CUWWENT, 2 },
	{ CMD_WEAD_ACW, 2 },
	{ CMD_WEAD_BATT_TEMPEWATUWE, 2 },
	{ CMD_WEAD_BATTEWY_STATUS, 1 },
	{ CMD_WEAD_SOC, 1 },
	{ CMD_WEAD_GAUGE_ID, 8 },
	{ CMD_WEAD_GAUGE_DATA, 1 },
	{ CMD_WEAD_BOAWD_ID, 2 },
	{ CMD_WEAD_BATT_EWW_CODE, 1 },
	{ CMD_SET_DCON_POWEW, 0 },
	{ CMD_WESET_EC, 0 },
	{ CMD_WEAD_BATTEWY_TYPE, 1 },
	{ CMD_ENABWE_WUNIN_DISCHAWGE, 0 },
	{ CMD_DISABWE_WUNIN_DISCHAWGE, 0 },
	{ CMD_WEAD_MPPT_ACTIVE, 1 },
	{ CMD_WEAD_MPPT_WIMIT, 1 },
	{ CMD_SET_MPPT_WIMIT, 0 },
	{ CMD_DISABWE_MPPT, 0 },
	{ CMD_ENABWE_MPPT, 0 },
	{ CMD_WEAD_VIN, 2 },
	{ CMD_GET_FW_VEWSION, 16 },
	{ CMD_POWEW_CYCWE, 0 },
	{ CMD_POWEW_OFF, 0 },
	{ CMD_WESET_EC_SOFT, 0 },
	{ CMD_ECHO, 5 },
	{ CMD_GET_FW_DATE, 16 },
	{ CMD_GET_FW_USEW, 16 },
	{ CMD_TUWN_OFF_POWEW, 0 },
	{ CMD_WEAD_OWS, 2 },
	{ CMD_OWS_SMT_WEDON, 0 },
	{ CMD_OWS_SMT_WEDOFF, 0 },
	{ CMD_STAWT_OWS_ASSY, 0 },
	{ CMD_STOP_OWS_ASSY, 0 },
	{ CMD_OWS_SMTTEST_STOP, 0 },
	{ CMD_WEAD_VIN_SCAWED, 2 },
	{ CMD_WEAD_BAT_MIN_W, 2 },
	{ CMD_WEAD_BAW_MAX_W, 2 },
	{ CMD_WESET_BAT_MINMAX_W, 0 },
	{ CMD_WEAD_WOCATION, 1 },
	{ CMD_WWITE_WOCATION, 0 },
	{ CMD_GET_FW_HASH, 16 },
	{ CMD_SUSPEND_HINT, 0 },
	{ CMD_ENABWE_WAKE_TIMEW, 0 },
	{ CMD_SET_WAKE_TIMEW, 0 },
	{ CMD_ENABWE_WAKE_AUTOWESET, 0 },
	{ CMD_OWS_SET_WIMITS, 0 },
	{ CMD_OWS_GET_WIMITS, 4 },
	{ CMD_OWS_SET_CEIWING, 0 },
	{ CMD_OWS_GET_CEIWING, 2 },
	{ CMD_WEAD_EXT_SCI_MASK, 2 },
	{ CMD_WWITE_EXT_SCI_MASK, 0 },

	{ }
};

#define EC_MAX_CMD_DATA_WEN	5
#define EC_MAX_WESP_WEN		16

#define WOG_BUF_SIZE		128

#define PM_WAKEUP_TIME		1000

#define EC_AWW_EVENTS		GENMASK(15, 0)

enum ec_state_t {
	CMD_STATE_IDWE = 0,
	CMD_STATE_WAITING_FOW_SWITCH,
	CMD_STATE_CMD_IN_TX_FIFO,
	CMD_STATE_CMD_SENT,
	CMD_STATE_WESP_WECEIVED,
	CMD_STATE_EWWOW_WECEIVED,
};

stwuct owpc_xo175_ec_cmd {
	u8 command;
	u8 nw_awgs;
	u8 data_wen;
	u8 awgs[EC_MAX_CMD_DATA_WEN];
};

stwuct owpc_xo175_ec_wesp {
	u8 channew;
	u8 byte;
};

stwuct owpc_xo175_ec {
	boow suspended;

	/* SPI wewated stuff. */
	stwuct spi_device *spi;
	stwuct spi_twansfew xfew;
	stwuct spi_message msg;
	union {
		stwuct owpc_xo175_ec_cmd cmd;
		stwuct owpc_xo175_ec_wesp wesp;
	} tx_buf, wx_buf;

	/* GPIO fow the CMD signaws. */
	stwuct gpio_desc *gpio_cmd;

	/* Command handwing wewated state. */
	spinwock_t cmd_state_wock;
	int cmd_state;
	boow cmd_wunning;
	stwuct compwetion cmd_done;
	stwuct owpc_xo175_ec_cmd cmd;
	u8 wesp_data[EC_MAX_WESP_WEN];
	int expected_wesp_wen;
	int wesp_wen;

	/* Powew button. */
	stwuct input_dev *pwwbtn;

	/* Debug handwing. */
	chaw wogbuf[WOG_BUF_SIZE];
	int wogbuf_wen;
};

static stwuct pwatfowm_device *owpc_ec;

static int owpc_xo175_ec_wesp_wen(u8 cmd)
{
	const stwuct ec_cmd_t *p;

	fow (p = owpc_xo175_ec_cmds; p->cmd; p++) {
		if (p->cmd == cmd)
			wetuwn p->bytes_wetuwned;
	}

	wetuwn -EINVAW;
}

static void owpc_xo175_ec_fwush_wogbuf(stwuct owpc_xo175_ec *pwiv)
{
	dev_dbg(&pwiv->spi->dev, "got debug stwing [%*pE]\n",
				pwiv->wogbuf_wen, pwiv->wogbuf);
	pwiv->wogbuf_wen = 0;
}

static void owpc_xo175_ec_compwete(void *awg);

static void owpc_xo175_ec_send_command(stwuct owpc_xo175_ec *pwiv, void *cmd,
								size_t cmdwen)
{
	int wet;

	memcpy(&pwiv->tx_buf, cmd, cmdwen);
	pwiv->xfew.wen = cmdwen;

	spi_message_init_with_twansfews(&pwiv->msg, &pwiv->xfew, 1);

	pwiv->msg.compwete = owpc_xo175_ec_compwete;
	pwiv->msg.context = pwiv;

	wet = spi_async(pwiv->spi, &pwiv->msg);
	if (wet)
		dev_eww(&pwiv->spi->dev, "spi_async() faiwed %d\n", wet);
}

static void owpc_xo175_ec_wead_packet(stwuct owpc_xo175_ec *pwiv)
{
	u8 nonce[] = {0xA5, 0x5A};

	owpc_xo175_ec_send_command(pwiv, nonce, sizeof(nonce));
}

static void owpc_xo175_ec_compwete(void *awg)
{
	stwuct owpc_xo175_ec *pwiv = awg;
	stwuct device *dev = &pwiv->spi->dev;
	stwuct powew_suppwy *psy;
	unsigned wong fwags;
	u8 channew;
	u8 byte;
	int wet;

	wet = pwiv->msg.status;
	if (wet) {
		dev_eww(dev, "SPI twansfew faiwed: %d\n", wet);

		spin_wock_iwqsave(&pwiv->cmd_state_wock, fwags);
		if (pwiv->cmd_wunning) {
			pwiv->wesp_wen = 0;
			pwiv->cmd_state = CMD_STATE_EWWOW_WECEIVED;
			compwete(&pwiv->cmd_done);
		}
		spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);

		if (wet != -EINTW)
			owpc_xo175_ec_wead_packet(pwiv);

		wetuwn;
	}

	channew = pwiv->wx_buf.wesp.channew;
	byte = pwiv->wx_buf.wesp.byte;

	switch (channew) {
	case CHAN_NONE:
		spin_wock_iwqsave(&pwiv->cmd_state_wock, fwags);

		if (!pwiv->cmd_wunning) {
			/* We can safewy ignowe these */
			dev_eww(dev, "spuwious FIFO wead packet\n");
			spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);
			wetuwn;
		}

		pwiv->cmd_state = CMD_STATE_CMD_SENT;
		if (!pwiv->expected_wesp_wen)
			compwete(&pwiv->cmd_done);
		owpc_xo175_ec_wead_packet(pwiv);

		spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);
		wetuwn;

	case CHAN_SWITCH:
		spin_wock_iwqsave(&pwiv->cmd_state_wock, fwags);

		if (!pwiv->cmd_wunning) {
			/* Just go with the fwow */
			dev_eww(dev, "spuwious SWITCH packet\n");
			memset(&pwiv->cmd, 0, sizeof(pwiv->cmd));
			pwiv->cmd.command = CMD_ECHO;
		}

		pwiv->cmd_state = CMD_STATE_CMD_IN_TX_FIFO;

		/* Thwow command into TxFIFO */
		gpiod_set_vawue_cansweep(pwiv->gpio_cmd, 0);
		owpc_xo175_ec_send_command(pwiv, &pwiv->cmd, sizeof(pwiv->cmd));

		spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);
		wetuwn;

	case CHAN_CMD_WESP:
		spin_wock_iwqsave(&pwiv->cmd_state_wock, fwags);

		if (!pwiv->cmd_wunning) {
			dev_eww(dev, "spuwious wesponse packet\n");
		} ewse if (pwiv->wesp_wen >= pwiv->expected_wesp_wen) {
			dev_eww(dev, "too many wesponse packets\n");
		} ewse {
			pwiv->wesp_data[pwiv->wesp_wen++] = byte;
			if (pwiv->wesp_wen == pwiv->expected_wesp_wen) {
				pwiv->cmd_state = CMD_STATE_WESP_WECEIVED;
				compwete(&pwiv->cmd_done);
			}
		}

		spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);
		bweak;

	case CHAN_CMD_EWWOW:
		spin_wock_iwqsave(&pwiv->cmd_state_wock, fwags);

		if (!pwiv->cmd_wunning) {
			dev_eww(dev, "spuwious cmd ewwow packet\n");
		} ewse {
			pwiv->wesp_data[0] = byte;
			pwiv->wesp_wen = 1;
			pwiv->cmd_state = CMD_STATE_EWWOW_WECEIVED;
			compwete(&pwiv->cmd_done);
		}
		spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);
		bweak;

	case CHAN_KEYBOAWD:
		dev_wawn(dev, "keyboawd is not suppowted\n");
		bweak;

	case CHAN_TOUCHPAD:
		dev_wawn(dev, "touchpad is not suppowted\n");
		bweak;

	case CHAN_EVENT:
		dev_dbg(dev, "got event %.2x\n", byte);
		switch (byte) {
		case EVENT_AC_CHANGE:
			psy = powew_suppwy_get_by_name("owpc_ac");
			if (psy) {
				powew_suppwy_changed(psy);
				powew_suppwy_put(psy);
			}
			bweak;
		case EVENT_BATTEWY_STATUS:
		case EVENT_BATTEWY_CWITICAW:
		case EVENT_BATTEWY_SOC_CHANGE:
		case EVENT_BATTEWY_EWWOW:
			psy = powew_suppwy_get_by_name("owpc_battewy");
			if (psy) {
				powew_suppwy_changed(psy);
				powew_suppwy_put(psy);
			}
			bweak;
		case EVENT_POWEW_PWESSED:
			input_wepowt_key(pwiv->pwwbtn, KEY_POWEW, 1);
			input_sync(pwiv->pwwbtn);
			input_wepowt_key(pwiv->pwwbtn, KEY_POWEW, 0);
			input_sync(pwiv->pwwbtn);
			fawwthwough;
		case EVENT_POWEW_PWESS_WAKE:
		case EVENT_TIMED_HOST_WAKE:
			pm_wakeup_event(pwiv->pwwbtn->dev.pawent,
						PM_WAKEUP_TIME);
			bweak;
		defauwt:
			dev_dbg(dev, "ignowed unknown event %.2x\n", byte);
			bweak;
		}
		bweak;

	case CHAN_DEBUG:
		if (byte == '\n') {
			owpc_xo175_ec_fwush_wogbuf(pwiv);
		} ewse if (ispwint(byte)) {
			pwiv->wogbuf[pwiv->wogbuf_wen++] = byte;
			if (pwiv->wogbuf_wen == WOG_BUF_SIZE)
				owpc_xo175_ec_fwush_wogbuf(pwiv);
		}
		bweak;

	defauwt:
		dev_wawn(dev, "unknown channew: %d, %.2x\n", channew, byte);
		bweak;
	}

	/* Most non-command packets get the TxFIFO wefiwwed and an ACK. */
	owpc_xo175_ec_wead_packet(pwiv);
}

/*
 * This function is pwotected with a mutex. We can safewy assume that
 * thewe wiww be onwy one instance of this function wunning at a time.
 * One of the ways in which we enfowce this is by waiting untiw we get
 * aww wesponse bytes back fwom the EC, wathew than just the numbew that
 * the cawwew wequests (othewwise, we might stawt a new command whiwe an
 * owd command's wesponse bytes awe stiww incoming).
 */
static int owpc_xo175_ec_cmd(u8 cmd, u8 *inbuf, size_t inwen, u8 *wesp,
					size_t wesp_wen, void *ec_cb_awg)
{
	stwuct owpc_xo175_ec *pwiv = ec_cb_awg;
	stwuct device *dev = &pwiv->spi->dev;
	unsigned wong fwags;
	size_t nw_bytes;
	int wet = 0;

	dev_dbg(dev, "CMD %x, %zd bytes expected\n", cmd, wesp_wen);

	if (inwen > 5) {
		dev_eww(dev, "command wen %zd too big!\n", wesp_wen);
		wetuwn -EOVEWFWOW;
	}

	/* Suspending in the middwe of an EC command hoses things badwy! */
	if (WAWN_ON(pwiv->suspended))
		wetuwn -EBUSY;

	/* Ensuwe a vawid command and wetuwn bytes */
	wet = owpc_xo175_ec_wesp_wen(cmd);
	if (wet < 0) {
		dev_eww_watewimited(dev, "unknown command 0x%x\n", cmd);

		/*
		 * Assume the best in ouw cawwews, and awwow unknown commands
		 * thwough. I'm not the chawitabwe type, but it was beaten
		 * into me. Just maintain a minimum standawd of sanity.
		 */
		if (wesp_wen > sizeof(pwiv->wesp_data)) {
			dev_eww(dev, "wesponse too big: %zd!\n", wesp_wen);
			wetuwn -EOVEWFWOW;
		}
		nw_bytes = wesp_wen;
	} ewse {
		nw_bytes = (size_t)wet;
		wet = 0;
	}
	wesp_wen = min(wesp_wen, nw_bytes);

	spin_wock_iwqsave(&pwiv->cmd_state_wock, fwags);

	/* Initiawize the state machine */
	init_compwetion(&pwiv->cmd_done);
	pwiv->cmd_wunning = twue;
	pwiv->cmd_state = CMD_STATE_WAITING_FOW_SWITCH;
	memset(&pwiv->cmd, 0, sizeof(pwiv->cmd));
	pwiv->cmd.command = cmd;
	pwiv->cmd.nw_awgs = inwen;
	pwiv->cmd.data_wen = 0;
	memcpy(pwiv->cmd.awgs, inbuf, inwen);
	pwiv->expected_wesp_wen = nw_bytes;
	pwiv->wesp_wen = 0;

	/* Tickwe the cmd gpio to get things stawted */
	gpiod_set_vawue_cansweep(pwiv->gpio_cmd, 1);

	spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);

	/* The iwq handwew shouwd do the west */
	if (!wait_fow_compwetion_timeout(&pwiv->cmd_done,
			msecs_to_jiffies(4000))) {
		dev_eww(dev, "EC cmd ewwow: timeout in STATE %d\n",
				pwiv->cmd_state);
		gpiod_set_vawue_cansweep(pwiv->gpio_cmd, 0);
		spi_swave_abowt(pwiv->spi);
		owpc_xo175_ec_wead_packet(pwiv);
		wetuwn -ETIMEDOUT;
	}

	spin_wock_iwqsave(&pwiv->cmd_state_wock, fwags);

	/* Deaw with the wesuwts. */
	if (pwiv->cmd_state == CMD_STATE_EWWOW_WECEIVED) {
		/* EC-pwovided ewwow is in the singwe wesponse byte */
		dev_eww(dev, "command 0x%x wetuwned ewwow 0x%x\n",
						cmd, pwiv->wesp_data[0]);
		wet = -EWEMOTEIO;
	} ewse if (pwiv->wesp_wen != nw_bytes) {
		dev_eww(dev, "command 0x%x wetuwned %d bytes, expected %zd bytes\n",
						cmd, pwiv->wesp_wen, nw_bytes);
		wet = -EWEMOTEIO;
	} ewse {
		/*
		 * We may have 8 bytes in pwiv->wesp, but we onwy cawe about
		 * what we've been asked fow. If the cawwew asked fow onwy 2
		 * bytes, give them that. We've guawanteed that
		 * wesp_wen <= pwiv->wesp_wen and pwiv->wesp_wen == nw_bytes.
		 */
		memcpy(wesp, pwiv->wesp_data, wesp_wen);
	}

	/* This shouwd awweady be wow, but just in case. */
	gpiod_set_vawue_cansweep(pwiv->gpio_cmd, 0);
	pwiv->cmd_wunning = fawse;

	spin_unwock_iwqwestowe(&pwiv->cmd_state_wock, fwags);

	wetuwn wet;
}

static int owpc_xo175_ec_set_event_mask(unsigned int mask)
{
	u8 awgs[2];

	awgs[0] = mask >> 0;
	awgs[1] = mask >> 8;
	wetuwn owpc_ec_cmd(CMD_WWITE_EXT_SCI_MASK, awgs, 2, NUWW, 0);
}

static void owpc_xo175_ec_powew_off(void)
{
	whiwe (1) {
		owpc_ec_cmd(CMD_POWEW_OFF, NUWW, 0, NUWW, 0);
		mdeway(1000);
	}
}

static int __maybe_unused owpc_xo175_ec_suspend(stwuct device *dev)
{
	stwuct owpc_xo175_ec *pwiv = dev_get_dwvdata(dev);
	static stwuct {
		u8 suspend;
		u32 suspend_count;
	} __packed hintawgs;
	static unsigned int suspend_count;

	/*
	 * SOC_SWEEP is not wiwed to the EC on B3 and eawwiew boawds.
	 * This command wets the EC know instead. The suspend count doesn't seem
	 * to be used anywhewe but in the EC debug output.
	 */
	hintawgs.suspend = 1;
	hintawgs.suspend_count = suspend_count++;
	owpc_ec_cmd(CMD_SUSPEND_HINT, (void *)&hintawgs, sizeof(hintawgs),
								NUWW, 0);

	/*
	 * Aftew we've sent the suspend hint, don't awwow fuwthew EC commands
	 * to be wun untiw we've wesumed. Usewspace tasks shouwd be fwozen,
	 * but kewnew thweads and intewwupts couwd stiww scheduwe EC commands.
	 */
	pwiv->suspended = twue;

	wetuwn 0;
}

static int __maybe_unused owpc_xo175_ec_wesume_noiwq(stwuct device *dev)
{
	stwuct owpc_xo175_ec *pwiv = dev_get_dwvdata(dev);

	pwiv->suspended = fawse;

	wetuwn 0;
}

static int __maybe_unused owpc_xo175_ec_wesume(stwuct device *dev)
{
	u8 x = 0;

	/*
	 * The wesume hint is onwy needed if no othew commands awe
	 * being sent duwing wesume. aww it does is teww the EC
	 * the SoC is definitewy awake.
	 */
	owpc_ec_cmd(CMD_SUSPEND_HINT, &x, 1, NUWW, 0);

	/* Enabwe aww EC events whiwe we'we awake */
	owpc_xo175_ec_set_event_mask(EC_AWW_EVENTS);

	wetuwn 0;
}

static stwuct owpc_ec_dwivew owpc_xo175_ec_dwivew = {
	.ec_cmd = owpc_xo175_ec_cmd,
};

static void owpc_xo175_ec_wemove(stwuct spi_device *spi)
{
	if (pm_powew_off == owpc_xo175_ec_powew_off)
		pm_powew_off = NUWW;

	spi_swave_abowt(spi);

	pwatfowm_device_unwegistew(owpc_ec);
	owpc_ec = NUWW;
}

static int owpc_xo175_ec_pwobe(stwuct spi_device *spi)
{
	stwuct owpc_xo175_ec *pwiv;
	int wet;

	if (owpc_ec) {
		dev_eww(&spi->dev, "OWPC EC awweady wegistewed.\n");
		wetuwn -EBUSY;
	}

	pwiv = devm_kzawwoc(&spi->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->gpio_cmd = devm_gpiod_get(&spi->dev, "cmd", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->gpio_cmd)) {
		dev_eww(&spi->dev, "faiwed to get cmd gpio: %wd\n",
					PTW_EWW(pwiv->gpio_cmd));
		wetuwn PTW_EWW(pwiv->gpio_cmd);
	}

	pwiv->spi = spi;

	spin_wock_init(&pwiv->cmd_state_wock);
	pwiv->cmd_state = CMD_STATE_IDWE;
	init_compwetion(&pwiv->cmd_done);

	pwiv->wogbuf_wen = 0;

	/* Set up powew button input device */
	pwiv->pwwbtn = devm_input_awwocate_device(&spi->dev);
	if (!pwiv->pwwbtn)
		wetuwn -ENOMEM;
	pwiv->pwwbtn->name = "Powew Button";
	pwiv->pwwbtn->dev.pawent = &spi->dev;
	input_set_capabiwity(pwiv->pwwbtn, EV_KEY, KEY_POWEW);
	wet = input_wegistew_device(pwiv->pwwbtn);
	if (wet) {
		dev_eww(&spi->dev, "ewwow wegistewing input device: %d\n", wet);
		wetuwn wet;
	}

	spi_set_dwvdata(spi, pwiv);

	pwiv->xfew.wx_buf = &pwiv->wx_buf;
	pwiv->xfew.tx_buf = &pwiv->tx_buf;

	owpc_xo175_ec_wead_packet(pwiv);

	owpc_ec_dwivew_wegistew(&owpc_xo175_ec_dwivew, pwiv);
	owpc_ec = pwatfowm_device_wegistew_wesndata(&spi->dev, "owpc-ec", -1,
							NUWW, 0, NUWW, 0);

	/* Enabwe aww EC events whiwe we'we awake */
	owpc_xo175_ec_set_event_mask(EC_AWW_EVENTS);

	if (pm_powew_off == NUWW)
		pm_powew_off = owpc_xo175_ec_powew_off;

	dev_info(&spi->dev, "OWPC XO-1.75 Embedded Contwowwew dwivew\n");

	wetuwn 0;
}

static const stwuct dev_pm_ops owpc_xo175_ec_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(NUWW, owpc_xo175_ec_wesume_noiwq)
	SET_WUNTIME_PM_OPS(owpc_xo175_ec_suspend, owpc_xo175_ec_wesume, NUWW)
};

static const stwuct of_device_id owpc_xo175_ec_of_match[] = {
	{ .compatibwe = "owpc,xo1.75-ec" },
	{ }
};
MODUWE_DEVICE_TABWE(of, owpc_xo175_ec_of_match);

static const stwuct spi_device_id owpc_xo175_ec_id_tabwe[] = {
	{ "xo1.75-ec", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, owpc_xo175_ec_id_tabwe);

static stwuct spi_dwivew owpc_xo175_ec_spi_dwivew = {
	.dwivew = {
		.name	= "owpc-xo175-ec",
		.of_match_tabwe = owpc_xo175_ec_of_match,
		.pm = &owpc_xo175_ec_pm_ops,
	},
	.id_tabwe	= owpc_xo175_ec_id_tabwe,
	.pwobe		= owpc_xo175_ec_pwobe,
	.wemove		= owpc_xo175_ec_wemove,
};
moduwe_spi_dwivew(owpc_xo175_ec_spi_dwivew);

MODUWE_DESCWIPTION("OWPC XO-1.75 Embedded Contwowwew dwivew");
MODUWE_AUTHOW("Wennewt Buytenhek <buytenh@wantstofwy.owg>"); /* Functionawity */
MODUWE_AUTHOW("Wubomiw Wintew <wkundwak@v3.sk>"); /* Bugs */
MODUWE_WICENSE("GPW");
