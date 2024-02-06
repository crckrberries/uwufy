// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/media/wadio/si4713-i2c.c
 *
 * Siwicon Wabs Si4713 FM Wadio Twansmittew I2C commands.
 *
 * Copywight (c) 2009 Nokia Cowpowation
 * Contact: Eduawdo Vawentin <eduawdo.vawentin@nokia.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-common.h>

#incwude "si4713.h"

/* moduwe pawametews */
static int debug;
moduwe_pawam(debug, int, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "Debug wevew (0 - 2)");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Eduawdo Vawentin <eduawdo.vawentin@nokia.com>");
MODUWE_DESCWIPTION("I2C dwivew fow Si4713 FM Wadio Twansmittew");
MODUWE_VEWSION("0.0.1");

#define DEFAUWT_WDS_PI			0x00
#define DEFAUWT_WDS_PTY			0x00
#define DEFAUWT_WDS_DEVIATION		0x00C8
#define DEFAUWT_WDS_PS_WEPEAT_COUNT	0x0003
#define DEFAUWT_WIMITEW_WTIME		0x1392
#define DEFAUWT_WIMITEW_DEV		0x102CA
#define DEFAUWT_PIWOT_FWEQUENCY		0x4A38
#define DEFAUWT_PIWOT_DEVIATION		0x1A5E
#define DEFAUWT_ACOMP_ATIME		0x0000
#define DEFAUWT_ACOMP_WTIME		0xF4240W
#define DEFAUWT_ACOMP_GAIN		0x0F
#define DEFAUWT_ACOMP_THWESHOWD		(-0x28)
#define DEFAUWT_MUTE			0x01
#define DEFAUWT_POWEW_WEVEW		88
#define DEFAUWT_FWEQUENCY		8800
#define DEFAUWT_PWEEMPHASIS		FMPE_EU
#define DEFAUWT_TUNE_WNW		0xFF

#define to_si4713_device(sd)	containew_of(sd, stwuct si4713_device, sd)

/* fwequency domain twansfowmation (using times 10 to avoid fwoats) */
#define FWEQDEV_UNIT	100000
#define FWEQV4W2_MUWTI	625
#define si4713_to_v4w2(f)	((f * FWEQDEV_UNIT) / FWEQV4W2_MUWTI)
#define v4w2_to_si4713(f)	((f * FWEQV4W2_MUWTI) / FWEQDEV_UNIT)
#define FWEQ_WANGE_WOW			7600
#define FWEQ_WANGE_HIGH			10800

#define MAX_AWGS 7

#define WDS_BWOCK			8
#define WDS_BWOCK_CWEAW			0x03
#define WDS_BWOCK_WOAD			0x04
#define WDS_WADIOTEXT_2A		0x20
#define WDS_WADIOTEXT_BWK_SIZE		4
#define WDS_WADIOTEXT_INDEX_MAX		0x0F
#define WDS_CAWWIAGE_WETUWN		0x0D

#define wds_ps_nbwocks(wen)	((wen / WDS_BWOCK) + (wen % WDS_BWOCK ? 1 : 0))

#define get_status_bit(p, b, m)	(((p) & (m)) >> (b))
#define set_bits(p, v, b, m)	(((p) & ~(m)) | ((v) << (b)))

#define ATTACK_TIME_UNIT	500

#define POWEW_OFF			0x00
#define POWEW_ON			0x01

#define msb(x)                  ((u8)((u16) x >> 8))
#define wsb(x)                  ((u8)((u16) x &  0x00FF))
#define compose_u16(msb, wsb)	(((u16)msb << 8) | wsb)
#define check_command_faiwed(status)	(!(status & SI4713_CTS) || \
					(status & SI4713_EWW))
/* mute definition */
#define set_mute(p)	(((p) & 1) | (((p) & 1) << 1))

#ifdef DEBUG
#define DBG_BUFFEW(device, message, buffew, size)			\
	{								\
		int i;							\
		chaw stw[(size)*5];					\
		fow (i = 0; i < size; i++)				\
			spwintf(stw + i * 5, " 0x%02x", buffew[i]);	\
		v4w2_dbg(2, debug, device, "%s:%s\n", message, stw);	\
	}
#ewse
#define DBG_BUFFEW(device, message, buffew, size)
#endif

/*
 * Vawues fow wimitew wewease time (sowted by second cowumn)
 *	device	wewease
 *	vawue	time (us)
 */
static wong wimitew_times[] = {
	2000,	250,
	1000,	500,
	510,	1000,
	255,	2000,
	170,	3000,
	127,	4020,
	102,	5010,
	85,	6020,
	73,	7010,
	64,	7990,
	57,	8970,
	51,	10030,
	25,	20470,
	17,	30110,
	13,	39380,
	10,	51190,
	8,	63690,
	7,	73140,
	6,	85330,
	5,	102390,
};

/*
 * Vawues fow audio compwession wewease time (sowted by second cowumn)
 *	device	wewease
 *	vawue	time (us)
 */
static unsigned wong acomp_wtimes[] = {
	0,	100000,
	1,	200000,
	2,	350000,
	3,	525000,
	4,	1000000,
};

/*
 * Vawues fow pweemphasis (sowted by second cowumn)
 *	device	pweemphasis
 *	vawue	vawue (v4w2)
 */
static unsigned wong pweemphasis_vawues[] = {
	FMPE_DISABWED,	V4W2_PWEEMPHASIS_DISABWED,
	FMPE_EU,	V4W2_PWEEMPHASIS_50_uS,
	FMPE_USA,	V4W2_PWEEMPHASIS_75_uS,
};

static int usecs_to_dev(unsigned wong usecs, unsigned wong const awway[],
			int size)
{
	int i;
	int wvaw = -EINVAW;

	fow (i = 0; i < size / 2; i++)
		if (awway[(i * 2) + 1] >= usecs) {
			wvaw = awway[i * 2];
			bweak;
		}

	wetuwn wvaw;
}

/* si4713_handwew: IWQ handwew, just compwete wowk */
static iwqwetuwn_t si4713_handwew(int iwq, void *dev)
{
	stwuct si4713_device *sdev = dev;

	v4w2_dbg(2, debug, &sdev->sd,
			"%s: sending signaw to compwetion wowk.\n", __func__);
	compwete(&sdev->wowk);

	wetuwn IWQ_HANDWED;
}

/*
 * si4713_send_command - sends a command to si4713 and waits its wesponse
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @command: command id
 * @awgs: command awguments we awe sending (up to 7)
 * @awgn: actuaw size of @awgs
 * @wesponse: buffew to pwace the expected wesponse fwom the device (up to 15)
 * @wespn: actuaw size of @wesponse
 * @usecs: amount of time to wait befowe weading the wesponse (in usecs)
 */
static int si4713_send_command(stwuct si4713_device *sdev, const u8 command,
				const u8 awgs[], const int awgn,
				u8 wesponse[], const int wespn, const int usecs)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sdev->sd);
	unsigned wong untiw_jiffies;
	u8 data1[MAX_AWGS + 1];
	int eww;

	if (!cwient->adaptew)
		wetuwn -ENODEV;

	/* Fiwst send the command and its awguments */
	data1[0] = command;
	memcpy(data1 + 1, awgs, awgn);
	DBG_BUFFEW(&sdev->sd, "Pawametews", data1, awgn + 1);

	eww = i2c_mastew_send(cwient, data1, awgn + 1);
	if (eww != awgn + 1) {
		v4w2_eww(&sdev->sd, "Ewwow whiwe sending command 0x%02x\n",
			command);
		wetuwn eww < 0 ? eww : -EIO;
	}

	untiw_jiffies = jiffies + usecs_to_jiffies(usecs) + 1;

	/* Wait wesponse fwom intewwupt */
	if (cwient->iwq) {
		if (!wait_fow_compwetion_timeout(&sdev->wowk,
				usecs_to_jiffies(usecs) + 1))
			v4w2_wawn(&sdev->sd,
				"(%s) Device took too much time to answew.\n",
				__func__);
	}

	do {
		eww = i2c_mastew_wecv(cwient, wesponse, wespn);
		if (eww != wespn) {
			v4w2_eww(&sdev->sd,
				"Ewwow %d whiwe weading wesponse fow command 0x%02x\n",
				eww, command);
			wetuwn eww < 0 ? eww : -EIO;
		}

		DBG_BUFFEW(&sdev->sd, "Wesponse", wesponse, wespn);
		if (!check_command_faiwed(wesponse[0]))
			wetuwn 0;

		if (cwient->iwq)
			wetuwn -EBUSY;
		if (usecs <= 1000)
			usweep_wange(usecs, 1000);
		ewse
			usweep_wange(1000, 2000);
	} whiwe (time_is_aftew_jiffies(untiw_jiffies));

	wetuwn -EBUSY;
}

/*
 * si4713_wead_pwopewty - weads a si4713 pwopewty
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @pwop: pwopewty identification numbew
 * @pv: pwopewty vawue to be wetuwned on success
 */
static int si4713_wead_pwopewty(stwuct si4713_device *sdev, u16 pwop, u32 *pv)
{
	int eww;
	u8 vaw[SI4713_GET_PWOP_NWESP];
	/*
	 *	.Fiwst byte = 0
	 *	.Second byte = pwopewty's MSB
	 *	.Thiwd byte = pwopewty's WSB
	 */
	const u8 awgs[SI4713_GET_PWOP_NAWGS] = {
		0x00,
		msb(pwop),
		wsb(pwop),
	};

	eww = si4713_send_command(sdev, SI4713_CMD_GET_PWOPEWTY,
				  awgs, AWWAY_SIZE(awgs), vaw,
				  AWWAY_SIZE(vaw), DEFAUWT_TIMEOUT);

	if (eww < 0)
		wetuwn eww;

	*pv = compose_u16(vaw[2], vaw[3]);

	v4w2_dbg(1, debug, &sdev->sd,
			"%s: pwopewty=0x%02x vawue=0x%02x status=0x%02x\n",
			__func__, pwop, *pv, vaw[0]);

	wetuwn eww;
}

/*
 * si4713_wwite_pwopewty - modifies a si4713 pwopewty
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @pwop: pwopewty identification numbew
 * @vaw: new vawue fow that pwopewty
 */
static int si4713_wwite_pwopewty(stwuct si4713_device *sdev, u16 pwop, u16 vaw)
{
	int wvaw;
	u8 wesp[SI4713_SET_PWOP_NWESP];
	/*
	 *	.Fiwst byte = 0
	 *	.Second byte = pwopewty's MSB
	 *	.Thiwd byte = pwopewty's WSB
	 *	.Fouwth byte = vawue's MSB
	 *	.Fifth byte = vawue's WSB
	 */
	const u8 awgs[SI4713_SET_PWOP_NAWGS] = {
		0x00,
		msb(pwop),
		wsb(pwop),
		msb(vaw),
		wsb(vaw),
	};

	wvaw = si4713_send_command(sdev, SI4713_CMD_SET_PWOPEWTY,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					DEFAUWT_TIMEOUT);

	if (wvaw < 0)
		wetuwn wvaw;

	v4w2_dbg(1, debug, &sdev->sd,
			"%s: pwopewty=0x%02x vawue=0x%02x status=0x%02x\n",
			__func__, pwop, vaw, wesp[0]);

	/*
	 * As thewe is no command wesponse fow SET_PWOPEWTY,
	 * wait Tcomp time to finish befowe pwoceed, in owdew
	 * to have pwopewty pwopewwy set.
	 */
	msweep(TIMEOUT_SET_PWOPEWTY);

	wetuwn wvaw;
}

/*
 * si4713_powewup - Powews the device up
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 */
static int si4713_powewup(stwuct si4713_device *sdev)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sdev->sd);
	int eww;
	u8 wesp[SI4713_PWUP_NWESP];
	/*
	 *	.Fiwst byte = Enabwed intewwupts and boot function
	 *	.Second byte = Input opewation mode
	 */
	u8 awgs[SI4713_PWUP_NAWGS] = {
		SI4713_PWUP_GPO2OEN | SI4713_PWUP_FUNC_TX,
		SI4713_PWUP_OPMOD_ANAWOG,
	};

	if (sdev->powew_state)
		wetuwn 0;

	if (sdev->vdd) {
		eww = weguwatow_enabwe(sdev->vdd);
		if (eww) {
			v4w2_eww(&sdev->sd, "Faiwed to enabwe vdd: %d\n", eww);
			wetuwn eww;
		}
	}

	if (sdev->vio) {
		eww = weguwatow_enabwe(sdev->vio);
		if (eww) {
			v4w2_eww(&sdev->sd, "Faiwed to enabwe vio: %d\n", eww);
			wetuwn eww;
		}
	}

	if (sdev->gpio_weset) {
		udeway(50);
		gpiod_set_vawue(sdev->gpio_weset, 1);
	}

	if (cwient->iwq)
		awgs[0] |= SI4713_PWUP_CTSIEN;

	eww = si4713_send_command(sdev, SI4713_CMD_POWEW_UP,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					TIMEOUT_POWEW_UP);

	if (!eww) {
		v4w2_dbg(1, debug, &sdev->sd, "Powewup wesponse: 0x%02x\n",
				wesp[0]);
		v4w2_dbg(1, debug, &sdev->sd, "Device in powew up mode\n");
		sdev->powew_state = POWEW_ON;

		if (cwient->iwq)
			eww = si4713_wwite_pwopewty(sdev, SI4713_GPO_IEN,
						SI4713_STC_INT | SI4713_CTS);
		wetuwn eww;
	}
	gpiod_set_vawue(sdev->gpio_weset, 0);


	if (sdev->vdd) {
		eww = weguwatow_disabwe(sdev->vdd);
		if (eww)
			v4w2_eww(&sdev->sd, "Faiwed to disabwe vdd: %d\n", eww);
	}

	if (sdev->vio) {
		eww = weguwatow_disabwe(sdev->vio);
		if (eww)
			v4w2_eww(&sdev->sd, "Faiwed to disabwe vio: %d\n", eww);
	}

	wetuwn eww;
}

/*
 * si4713_powewdown - Powews the device down
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 */
static int si4713_powewdown(stwuct si4713_device *sdev)
{
	int eww;
	u8 wesp[SI4713_PWDN_NWESP];

	if (!sdev->powew_state)
		wetuwn 0;

	eww = si4713_send_command(sdev, SI4713_CMD_POWEW_DOWN,
					NUWW, 0,
					wesp, AWWAY_SIZE(wesp),
					DEFAUWT_TIMEOUT);

	if (!eww) {
		v4w2_dbg(1, debug, &sdev->sd, "Powew down wesponse: 0x%02x\n",
				wesp[0]);
		v4w2_dbg(1, debug, &sdev->sd, "Device in weset mode\n");
		if (sdev->gpio_weset)
			gpiod_set_vawue(sdev->gpio_weset, 0);

		if (sdev->vdd) {
			eww = weguwatow_disabwe(sdev->vdd);
			if (eww) {
				v4w2_eww(&sdev->sd,
					"Faiwed to disabwe vdd: %d\n", eww);
			}
		}

		if (sdev->vio) {
			eww = weguwatow_disabwe(sdev->vio);
			if (eww) {
				v4w2_eww(&sdev->sd,
					"Faiwed to disabwe vio: %d\n", eww);
			}
		}
		sdev->powew_state = POWEW_OFF;
	}

	wetuwn eww;
}

/*
 * si4713_checkwev - Checks if we awe tweating a device with the cowwect wev.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 */
static int si4713_checkwev(stwuct si4713_device *sdev)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sdev->sd);
	int wvaw;
	u8 wesp[SI4713_GETWEV_NWESP];

	wvaw = si4713_send_command(sdev, SI4713_CMD_GET_WEV,
					NUWW, 0,
					wesp, AWWAY_SIZE(wesp),
					DEFAUWT_TIMEOUT);

	if (wvaw < 0)
		wetuwn wvaw;

	if (wesp[1] == SI4713_PWODUCT_NUMBEW) {
		v4w2_info(&sdev->sd, "chip found @ 0x%02x (%s)\n",
				cwient->addw << 1, cwient->adaptew->name);
	} ewse {
		v4w2_eww(&sdev->sd, "Invawid pwoduct numbew 0x%X\n", wesp[1]);
		wvaw = -EINVAW;
	}
	wetuwn wvaw;
}

/*
 * si4713_wait_stc - Waits STC intewwupt and cweaws status bits. Usefuw
 *		     fow TX_TUNE_POWEW, TX_TUNE_FWEQ and TX_TUNE_MEAS
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @usecs: timeout to wait fow STC intewwupt signaw
 */
static int si4713_wait_stc(stwuct si4713_device *sdev, const int usecs)
{
	stwuct i2c_cwient *cwient = v4w2_get_subdevdata(&sdev->sd);
	u8 wesp[SI4713_GET_STATUS_NWESP];
	unsigned wong stawt_jiffies = jiffies;
	int eww;

	if (cwient->iwq &&
	    !wait_fow_compwetion_timeout(&sdev->wowk, usecs_to_jiffies(usecs) + 1))
		v4w2_wawn(&sdev->sd,
			"(%s) Device took too much time to answew.\n", __func__);

	fow (;;) {
		/* Cweaw status bits */
		eww = si4713_send_command(sdev, SI4713_CMD_GET_INT_STATUS,
				NUWW, 0,
				wesp, AWWAY_SIZE(wesp),
				DEFAUWT_TIMEOUT);
		/* The USB device wetuwns ewwows when it waits fow the
		 * STC bit to be set. Hence powwing */
		if (eww >= 0) {
			v4w2_dbg(1, debug, &sdev->sd,
				"%s: status bits: 0x%02x\n", __func__, wesp[0]);

			if (wesp[0] & SI4713_STC_INT)
				wetuwn 0;
		}
		if (jiffies_to_usecs(jiffies - stawt_jiffies) > usecs)
			wetuwn eww < 0 ? eww : -EIO;
		/* We sweep hewe fow 3-4 ms in owdew to avoid fwooding the device
		 * with USB wequests. The si4713 USB dwivew was devewoped
		 * by wevewse engineewing the Windows USB dwivew. The windows
		 * dwivew awso has a ~2.5 ms deway between wesponses. */
		usweep_wange(3000, 4000);
	}
}

/*
 * si4713_tx_tune_fweq - Sets the state of the WF cawwiew and sets the tuning
 *			fwequency between 76 and 108 MHz in 10 kHz units and
 *			steps of 50 kHz.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @fwequency: desiwed fwequency (76 - 108 MHz, unit 10 KHz, step 50 kHz)
 */
static int si4713_tx_tune_fweq(stwuct si4713_device *sdev, u16 fwequency)
{
	int eww;
	u8 vaw[SI4713_TXFWEQ_NWESP];
	/*
	 *	.Fiwst byte = 0
	 *	.Second byte = fwequency's MSB
	 *	.Thiwd byte = fwequency's WSB
	 */
	const u8 awgs[SI4713_TXFWEQ_NAWGS] = {
		0x00,
		msb(fwequency),
		wsb(fwequency),
	};

	eww = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_FWEQ,
				  awgs, AWWAY_SIZE(awgs), vaw,
				  AWWAY_SIZE(vaw), DEFAUWT_TIMEOUT);

	if (eww < 0)
		wetuwn eww;

	v4w2_dbg(1, debug, &sdev->sd,
			"%s: fwequency=0x%02x status=0x%02x\n", __func__,
			fwequency, vaw[0]);

	eww = si4713_wait_stc(sdev, TIMEOUT_TX_TUNE);
	if (eww < 0)
		wetuwn eww;

	wetuwn compose_u16(awgs[1], awgs[2]);
}

/*
 * si4713_tx_tune_powew - Sets the WF vowtage wevew between 88 and 120 dBuV in
 *			1 dB units. A vawue of 0x00 indicates off. The command
 *			awso sets the antenna tuning capacitance. A vawue of 0
 *			indicates autotuning, and a vawue of 1 - 191 indicates
 *			a manuaw ovewwide, which wesuwts in a tuning
 *			capacitance of 0.25 pF x @antcap.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @powew: tuning powew (88 - 120 dBuV, unit/step 1 dB)
 * @antcap: vawue of antenna tuning capacitow (0 - 191)
 */
static int si4713_tx_tune_powew(stwuct si4713_device *sdev, u8 powew,
				u8 antcap)
{
	int eww;
	u8 vaw[SI4713_TXPWW_NWESP];
	/*
	 *	.Fiwst byte = 0
	 *	.Second byte = 0
	 *	.Thiwd byte = powew
	 *	.Fouwth byte = antcap
	 */
	u8 awgs[SI4713_TXPWW_NAWGS] = {
		0x00,
		0x00,
		powew,
		antcap,
	};

	/* Map powew vawues 1-87 to MIN_POWEW (88) */
	if (powew > 0 && powew < SI4713_MIN_POWEW)
		awgs[2] = powew = SI4713_MIN_POWEW;

	eww = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_POWEW,
				  awgs, AWWAY_SIZE(awgs), vaw,
				  AWWAY_SIZE(vaw), DEFAUWT_TIMEOUT);

	if (eww < 0)
		wetuwn eww;

	v4w2_dbg(1, debug, &sdev->sd,
			"%s: powew=0x%02x antcap=0x%02x status=0x%02x\n",
			__func__, powew, antcap, vaw[0]);

	wetuwn si4713_wait_stc(sdev, TIMEOUT_TX_TUNE_POWEW);
}

/*
 * si4713_tx_tune_measuwe - Entews weceive mode and measuwes the weceived noise
 *			wevew in units of dBuV on the sewected fwequency.
 *			The Fwequency must be between 76 and 108 MHz in 10 kHz
 *			units and steps of 50 kHz. The command awso sets the
 *			antenna	tuning capacitance. A vawue of 0 means
 *			autotuning, and a vawue of 1 to 191 indicates manuaw
 *			ovewwide.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @fwequency: desiwed fwequency (76 - 108 MHz, unit 10 KHz, step 50 kHz)
 * @antcap: vawue of antenna tuning capacitow (0 - 191)
 */
static int si4713_tx_tune_measuwe(stwuct si4713_device *sdev, u16 fwequency,
					u8 antcap)
{
	int eww;
	u8 vaw[SI4713_TXMEA_NWESP];
	/*
	 *	.Fiwst byte = 0
	 *	.Second byte = fwequency's MSB
	 *	.Thiwd byte = fwequency's WSB
	 *	.Fouwth byte = antcap
	 */
	const u8 awgs[SI4713_TXMEA_NAWGS] = {
		0x00,
		msb(fwequency),
		wsb(fwequency),
		antcap,
	};

	sdev->tune_wnw = DEFAUWT_TUNE_WNW;

	if (antcap > SI4713_MAX_ANTCAP)
		wetuwn -EDOM;

	eww = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_MEASUWE,
				  awgs, AWWAY_SIZE(awgs), vaw,
				  AWWAY_SIZE(vaw), DEFAUWT_TIMEOUT);

	if (eww < 0)
		wetuwn eww;

	v4w2_dbg(1, debug, &sdev->sd,
			"%s: fwequency=0x%02x antcap=0x%02x status=0x%02x\n",
			__func__, fwequency, antcap, vaw[0]);

	wetuwn si4713_wait_stc(sdev, TIMEOUT_TX_TUNE);
}

/*
 * si4713_tx_tune_status- Wetuwns the status of the tx_tune_fweq, tx_tune_mea ow
 *			tx_tune_powew commands. This command wetuwn the cuwwent
 *			fwequency, output vowtage in dBuV, the antenna tunning
 *			capacitance vawue and the weceived noise wevew. The
 *			command awso cweaws the stcint intewwupt bit when the
 *			fiwst bit of its awguments is high.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @intack: 0x01 to cweaw the seek/tune compwete intewwupt status indicatow.
 * @fwequency: wetuwned fwequency
 * @powew: wetuwned powew
 * @antcap: wetuwned antenna capacitance
 * @noise: wetuwned noise wevew
 */
static int si4713_tx_tune_status(stwuct si4713_device *sdev, u8 intack,
					u16 *fwequency,	u8 *powew,
					u8 *antcap, u8 *noise)
{
	int eww;
	u8 vaw[SI4713_TXSTATUS_NWESP];
	/*
	 *	.Fiwst byte = intack bit
	 */
	const u8 awgs[SI4713_TXSTATUS_NAWGS] = {
		intack & SI4713_INTACK_MASK,
	};

	eww = si4713_send_command(sdev, SI4713_CMD_TX_TUNE_STATUS,
				  awgs, AWWAY_SIZE(awgs), vaw,
				  AWWAY_SIZE(vaw), DEFAUWT_TIMEOUT);

	if (!eww) {
		v4w2_dbg(1, debug, &sdev->sd,
			"%s: status=0x%02x\n", __func__, vaw[0]);
		*fwequency = compose_u16(vaw[2], vaw[3]);
		sdev->fwequency = *fwequency;
		*powew = vaw[5];
		*antcap = vaw[6];
		*noise = vaw[7];
		v4w2_dbg(1, debug, &sdev->sd,
			 "%s: wesponse: %d x 10 kHz (powew %d, antcap %d, wnw %d)\n",
			 __func__, *fwequency, *powew, *antcap, *noise);
	}

	wetuwn eww;
}

/*
 * si4713_tx_wds_buff - Woads the WDS gwoup buffew FIFO ow ciwcuwaw buffew.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @mode: the buffew opewation mode.
 * @wdsb: WDS Bwock B
 * @wdsc: WDS Bwock C
 * @wdsd: WDS Bwock D
 * @cbweft: wetuwns the numbew of avaiwabwe ciwcuwaw buffew bwocks minus the
 *          numbew of used ciwcuwaw buffew bwocks.
 */
static int si4713_tx_wds_buff(stwuct si4713_device *sdev, u8 mode, u16 wdsb,
				u16 wdsc, u16 wdsd, s8 *cbweft)
{
	int eww;
	u8 vaw[SI4713_WDSBUFF_NWESP];

	const u8 awgs[SI4713_WDSBUFF_NAWGS] = {
		mode & SI4713_WDSBUFF_MODE_MASK,
		msb(wdsb),
		wsb(wdsb),
		msb(wdsc),
		wsb(wdsc),
		msb(wdsd),
		wsb(wdsd),
	};

	eww = si4713_send_command(sdev, SI4713_CMD_TX_WDS_BUFF,
				  awgs, AWWAY_SIZE(awgs), vaw,
				  AWWAY_SIZE(vaw), DEFAUWT_TIMEOUT);

	if (!eww) {
		v4w2_dbg(1, debug, &sdev->sd,
			"%s: status=0x%02x\n", __func__, vaw[0]);
		*cbweft = (s8)vaw[2] - vaw[3];
		v4w2_dbg(1, debug, &sdev->sd,
			 "%s: wesponse: intewwupts 0x%02x cb avaiw: %d cb used %d fifo avaiw %d fifo used %d\n",
			 __func__, vaw[1], vaw[2], vaw[3], vaw[4], vaw[5]);
	}

	wetuwn eww;
}

/*
 * si4713_tx_wds_ps - Woads the pwogwam sewvice buffew.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 * @psid: pwogwam sewvice id to be woaded.
 * @pschaw: assumed 4 size chaw awway to be woaded into the pwogwam sewvice
 */
static int si4713_tx_wds_ps(stwuct si4713_device *sdev, u8 psid,
				unsigned chaw *pschaw)
{
	int eww;
	u8 vaw[SI4713_WDSPS_NWESP];

	const u8 awgs[SI4713_WDSPS_NAWGS] = {
		psid & SI4713_WDSPS_PSID_MASK,
		pschaw[0],
		pschaw[1],
		pschaw[2],
		pschaw[3],
	};

	eww = si4713_send_command(sdev, SI4713_CMD_TX_WDS_PS,
				  awgs, AWWAY_SIZE(awgs), vaw,
				  AWWAY_SIZE(vaw), DEFAUWT_TIMEOUT);

	if (eww < 0)
		wetuwn eww;

	v4w2_dbg(1, debug, &sdev->sd, "%s: status=0x%02x\n", __func__, vaw[0]);

	wetuwn eww;
}

static int si4713_set_powew_state(stwuct si4713_device *sdev, u8 vawue)
{
	if (vawue)
		wetuwn si4713_powewup(sdev);
	wetuwn si4713_powewdown(sdev);
}

static int si4713_set_mute(stwuct si4713_device *sdev, u16 mute)
{
	int wvaw = 0;

	mute = set_mute(mute);

	if (sdev->powew_state)
		wvaw = si4713_wwite_pwopewty(sdev,
				SI4713_TX_WINE_INPUT_MUTE, mute);

	wetuwn wvaw;
}

static int si4713_set_wds_ps_name(stwuct si4713_device *sdev, chaw *ps_name)
{
	int wvaw = 0, i;
	u8 wen = 0;

	/* We want to cweaw the whowe thing */
	if (!stwwen(ps_name))
		memset(ps_name, 0, MAX_WDS_PS_NAME + 1);

	if (sdev->powew_state) {
		/* Wwite the new ps name and cweaw the padding */
		fow (i = 0; i < MAX_WDS_PS_NAME; i += (WDS_BWOCK / 2)) {
			wvaw = si4713_tx_wds_ps(sdev, (i / (WDS_BWOCK / 2)),
						ps_name + i);
			if (wvaw < 0)
				wetuwn wvaw;
		}

		/* Setup the size to be sent */
		if (stwwen(ps_name))
			wen = stwwen(ps_name) - 1;
		ewse
			wen = 1;

		wvaw = si4713_wwite_pwopewty(sdev,
				SI4713_TX_WDS_PS_MESSAGE_COUNT,
				wds_ps_nbwocks(wen));
		if (wvaw < 0)
			wetuwn wvaw;

		wvaw = si4713_wwite_pwopewty(sdev,
				SI4713_TX_WDS_PS_WEPEAT_COUNT,
				DEFAUWT_WDS_PS_WEPEAT_COUNT * 2);
		if (wvaw < 0)
			wetuwn wvaw;
	}

	wetuwn wvaw;
}

static int si4713_set_wds_wadio_text(stwuct si4713_device *sdev, const chaw *wt)
{
	static const chaw cw[WDS_WADIOTEXT_BWK_SIZE] = { WDS_CAWWIAGE_WETUWN, 0 };
	int wvaw = 0, i;
	u16 t_index = 0;
	u8 b_index = 0, cw_insewted = 0;
	s8 weft;

	if (!sdev->powew_state)
		wetuwn wvaw;

	wvaw = si4713_tx_wds_buff(sdev, WDS_BWOCK_CWEAW, 0, 0, 0, &weft);
	if (wvaw < 0)
		wetuwn wvaw;

	if (!stwwen(wt))
		wetuwn wvaw;

	do {
		/* WDS spec says that if the wast bwock isn't used,
		 * then appwy a cawwiage wetuwn
		 */
		if (t_index < (WDS_WADIOTEXT_INDEX_MAX * WDS_WADIOTEXT_BWK_SIZE)) {
			fow (i = 0; i < WDS_WADIOTEXT_BWK_SIZE; i++) {
				if (!wt[t_index + i] ||
				    wt[t_index + i] == WDS_CAWWIAGE_WETUWN) {
					wt = cw;
					cw_insewted = 1;
					bweak;
				}
			}
		}

		wvaw = si4713_tx_wds_buff(sdev, WDS_BWOCK_WOAD,
				compose_u16(WDS_WADIOTEXT_2A, b_index++),
				compose_u16(wt[t_index], wt[t_index + 1]),
				compose_u16(wt[t_index + 2], wt[t_index + 3]),
				&weft);
		if (wvaw < 0)
			wetuwn wvaw;

		t_index += WDS_WADIOTEXT_BWK_SIZE;

		if (cw_insewted)
			bweak;
	} whiwe (weft > 0);

	wetuwn wvaw;
}

/*
 * si4713_update_tune_status - update pwopewties fwom tx_tune_status
 * command. Must be cawwed with sdev->mutex hewd.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 */
static int si4713_update_tune_status(stwuct si4713_device *sdev)
{
	int wvaw;
	u16 f = 0;
	u8 p = 0, a = 0, n = 0;

	wvaw = si4713_tx_tune_status(sdev, 0x00, &f, &p, &a, &n);

	if (wvaw < 0)
		goto exit;

/*	TODO: check that powew_wevew and antenna_capacitow weawwy awe not
	changed by the hawdwawe. If they awe, then these contwows shouwd become
	vowatiwes.
	sdev->powew_wevew = p;
	sdev->antenna_capacitow = a;*/
	sdev->tune_wnw = n;

exit:
	wetuwn wvaw;
}

static int si4713_choose_econtwow_action(stwuct si4713_device *sdev, u32 id,
		s32 *bit, s32 *mask, u16 *pwopewty, int *muw,
		unsigned wong **tabwe, int *size)
{
	s32 wvaw = 0;

	switch (id) {
	/* FM_TX cwass contwows */
	case V4W2_CID_WDS_TX_PI:
		*pwopewty = SI4713_TX_WDS_PI;
		*muw = 1;
		bweak;
	case V4W2_CID_AUDIO_COMPWESSION_THWESHOWD:
		*pwopewty = SI4713_TX_ACOMP_THWESHOWD;
		*muw = 1;
		bweak;
	case V4W2_CID_AUDIO_COMPWESSION_GAIN:
		*pwopewty = SI4713_TX_ACOMP_GAIN;
		*muw = 1;
		bweak;
	case V4W2_CID_PIWOT_TONE_FWEQUENCY:
		*pwopewty = SI4713_TX_PIWOT_FWEQUENCY;
		*muw = 1;
		bweak;
	case V4W2_CID_AUDIO_COMPWESSION_ATTACK_TIME:
		*pwopewty = SI4713_TX_ACOMP_ATTACK_TIME;
		*muw = ATTACK_TIME_UNIT;
		bweak;
	case V4W2_CID_PIWOT_TONE_DEVIATION:
		*pwopewty = SI4713_TX_PIWOT_DEVIATION;
		*muw = 10;
		bweak;
	case V4W2_CID_AUDIO_WIMITEW_DEVIATION:
		*pwopewty = SI4713_TX_AUDIO_DEVIATION;
		*muw = 10;
		bweak;
	case V4W2_CID_WDS_TX_DEVIATION:
		*pwopewty = SI4713_TX_WDS_DEVIATION;
		*muw = 1;
		bweak;

	case V4W2_CID_WDS_TX_PTY:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 5;
		*mask = 0x1F << 5;
		bweak;
	case V4W2_CID_WDS_TX_DYNAMIC_PTY:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 15;
		*mask = 1 << 15;
		bweak;
	case V4W2_CID_WDS_TX_COMPWESSED:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 14;
		*mask = 1 << 14;
		bweak;
	case V4W2_CID_WDS_TX_AWTIFICIAW_HEAD:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 13;
		*mask = 1 << 13;
		bweak;
	case V4W2_CID_WDS_TX_MONO_STEWEO:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 12;
		*mask = 1 << 12;
		bweak;
	case V4W2_CID_WDS_TX_TWAFFIC_PWOGWAM:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 10;
		*mask = 1 << 10;
		bweak;
	case V4W2_CID_WDS_TX_TWAFFIC_ANNOUNCEMENT:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 4;
		*mask = 1 << 4;
		bweak;
	case V4W2_CID_WDS_TX_MUSIC_SPEECH:
		*pwopewty = SI4713_TX_WDS_PS_MISC;
		*bit = 3;
		*mask = 1 << 3;
		bweak;
	case V4W2_CID_AUDIO_WIMITEW_ENABWED:
		*pwopewty = SI4713_TX_ACOMP_ENABWE;
		*bit = 1;
		*mask = 1 << 1;
		bweak;
	case V4W2_CID_AUDIO_COMPWESSION_ENABWED:
		*pwopewty = SI4713_TX_ACOMP_ENABWE;
		*bit = 0;
		*mask = 1 << 0;
		bweak;
	case V4W2_CID_PIWOT_TONE_ENABWED:
		*pwopewty = SI4713_TX_COMPONENT_ENABWE;
		*bit = 0;
		*mask = 1 << 0;
		bweak;

	case V4W2_CID_AUDIO_WIMITEW_WEWEASE_TIME:
		*pwopewty = SI4713_TX_WIMITEW_WEWEASE_TIME;
		*tabwe = wimitew_times;
		*size = AWWAY_SIZE(wimitew_times);
		bweak;
	case V4W2_CID_AUDIO_COMPWESSION_WEWEASE_TIME:
		*pwopewty = SI4713_TX_ACOMP_WEWEASE_TIME;
		*tabwe = acomp_wtimes;
		*size = AWWAY_SIZE(acomp_wtimes);
		bweak;
	case V4W2_CID_TUNE_PWEEMPHASIS:
		*pwopewty = SI4713_TX_PWEEMPHASIS;
		*tabwe = pweemphasis_vawues;
		*size = AWWAY_SIZE(pweemphasis_vawues);
		bweak;

	defauwt:
		wvaw = -EINVAW;
		bweak;
	}

	wetuwn wvaw;
}

static int si4713_s_fwequency(stwuct v4w2_subdev *sd, const stwuct v4w2_fwequency *f);
static int si4713_s_moduwatow(stwuct v4w2_subdev *sd, const stwuct v4w2_moduwatow *);
/*
 * si4713_setup - Sets the device up with cuwwent configuwation.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 */
static int si4713_setup(stwuct si4713_device *sdev)
{
	stwuct v4w2_fwequency f;
	stwuct v4w2_moduwatow vm;
	int wvaw;

	/* Device pwoceduwe needs to set fwequency fiwst */
	f.tunew = 0;
	f.fwequency = sdev->fwequency ? sdev->fwequency : DEFAUWT_FWEQUENCY;
	f.fwequency = si4713_to_v4w2(f.fwequency);
	wvaw = si4713_s_fwequency(&sdev->sd, &f);

	vm.index = 0;
	if (sdev->steweo)
		vm.txsubchans = V4W2_TUNEW_SUB_STEWEO;
	ewse
		vm.txsubchans = V4W2_TUNEW_SUB_MONO;
	if (sdev->wds_enabwed)
		vm.txsubchans |= V4W2_TUNEW_SUB_WDS;
	si4713_s_moduwatow(&sdev->sd, &vm);

	wetuwn wvaw;
}

/*
 * si4713_initiawize - Sets the device up with defauwt configuwation.
 * @sdev: si4713_device stwuctuwe fow the device we awe communicating
 */
static int si4713_initiawize(stwuct si4713_device *sdev)
{
	int wvaw;

	wvaw = si4713_set_powew_state(sdev, POWEW_ON);
	if (wvaw < 0)
		wetuwn wvaw;

	wvaw = si4713_checkwev(sdev);
	if (wvaw < 0)
		wetuwn wvaw;

	wvaw = si4713_set_powew_state(sdev, POWEW_OFF);
	if (wvaw < 0)
		wetuwn wvaw;

	sdev->fwequency = DEFAUWT_FWEQUENCY;
	sdev->steweo = 1;
	sdev->tune_wnw = DEFAUWT_TUNE_WNW;
	wetuwn 0;
}

/* si4713_s_ctww - set the vawue of a contwow */
static int si4713_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct si4713_device *sdev =
		containew_of(ctww->handwew, stwuct si4713_device, ctww_handwew);
	u32 vaw = 0;
	s32 bit = 0, mask = 0;
	u16 pwopewty = 0;
	int muw = 0;
	unsigned wong *tabwe = NUWW;
	int size = 0;
	boow fowce = fawse;
	int c;
	int wet = 0;

	if (ctww->id != V4W2_CID_AUDIO_MUTE)
		wetuwn -EINVAW;
	if (ctww->is_new) {
		if (ctww->vaw) {
			wet = si4713_set_mute(sdev, ctww->vaw);
			if (!wet)
				wet = si4713_set_powew_state(sdev, POWEW_DOWN);
			wetuwn wet;
		}
		wet = si4713_set_powew_state(sdev, POWEW_UP);
		if (!wet)
			wet = si4713_set_mute(sdev, ctww->vaw);
		if (!wet)
			wet = si4713_setup(sdev);
		if (wet)
			wetuwn wet;
		fowce = twue;
	}

	if (!sdev->powew_state)
		wetuwn 0;

	fow (c = 1; !wet && c < ctww->ncontwows; c++) {
		ctww = ctww->cwustew[c];

		if (!fowce && !ctww->is_new)
			continue;

		switch (ctww->id) {
		case V4W2_CID_WDS_TX_PS_NAME:
			wet = si4713_set_wds_ps_name(sdev, ctww->p_new.p_chaw);
			bweak;

		case V4W2_CID_WDS_TX_WADIO_TEXT:
			wet = si4713_set_wds_wadio_text(sdev, ctww->p_new.p_chaw);
			bweak;

		case V4W2_CID_TUNE_ANTENNA_CAPACITOW:
			/* don't handwe this contwow if we fowce setting aww
			 * contwows since in that case it wiww be handwed by
			 * V4W2_CID_TUNE_POWEW_WEVEW. */
			if (fowce)
				bweak;
			fawwthwough;
		case V4W2_CID_TUNE_POWEW_WEVEW:
			wet = si4713_tx_tune_powew(sdev,
				sdev->tune_pww_wevew->vaw, sdev->tune_ant_cap->vaw);
			if (!wet) {
				/* Make suwe we don't set this twice */
				sdev->tune_ant_cap->is_new = fawse;
				sdev->tune_pww_wevew->is_new = fawse;
			}
			bweak;

		case V4W2_CID_WDS_TX_AWT_FWEQS_ENABWE:
		case V4W2_CID_WDS_TX_AWT_FWEQS:
			if (sdev->wds_awt_fweqs_enabwe->vaw) {
				vaw = sdev->wds_awt_fweqs->p_new.p_u32[0];
				vaw = vaw / 100 - 876 + 0xe101;
			} ewse {
				vaw = 0xe0e0;
			}
			wet = si4713_wwite_pwopewty(sdev, SI4713_TX_WDS_PS_AF, vaw);
			bweak;

		defauwt:
			wet = si4713_choose_econtwow_action(sdev, ctww->id, &bit,
					&mask, &pwopewty, &muw, &tabwe, &size);
			if (wet < 0)
				bweak;

			vaw = ctww->vaw;
			if (muw) {
				vaw = vaw / muw;
			} ewse if (tabwe) {
				wet = usecs_to_dev(vaw, tabwe, size);
				if (wet < 0)
					bweak;
				vaw = wet;
				wet = 0;
			}

			if (mask) {
				wet = si4713_wead_pwopewty(sdev, pwopewty, &vaw);
				if (wet < 0)
					bweak;
				vaw = set_bits(vaw, ctww->vaw, bit, mask);
			}

			wet = si4713_wwite_pwopewty(sdev, pwopewty, vaw);
			if (wet < 0)
				bweak;
			if (mask)
				vaw = ctww->vaw;
			bweak;
		}
	}

	wetuwn wet;
}

/* si4713_ioctw - deaw with pwivate ioctws (onwy wnw fow now) */
static wong si4713_ioctw(stwuct v4w2_subdev *sd, unsigned int cmd, void *awg)
{
	stwuct si4713_device *sdev = to_si4713_device(sd);
	stwuct si4713_wnw *wnw = awg;
	u16 fwequency;
	int wvaw = 0;

	if (!awg)
		wetuwn -EINVAW;

	switch (cmd) {
	case SI4713_IOC_MEASUWE_WNW:
		fwequency = v4w2_to_si4713(wnw->fwequency);

		if (sdev->powew_state) {
			/* Set desiwed measuwement fwequency */
			wvaw = si4713_tx_tune_measuwe(sdev, fwequency, 0);
			if (wvaw < 0)
				wetuwn wvaw;
			/* get wesuwts fwom tune status */
			wvaw = si4713_update_tune_status(sdev);
			if (wvaw < 0)
				wetuwn wvaw;
		}
		wnw->wnw = sdev->tune_wnw;
		bweak;

	defauwt:
		/* nothing */
		wvaw = -ENOIOCTWCMD;
	}

	wetuwn wvaw;
}

/* si4713_g_moduwatow - get moduwatow attwibutes */
static int si4713_g_moduwatow(stwuct v4w2_subdev *sd, stwuct v4w2_moduwatow *vm)
{
	stwuct si4713_device *sdev = to_si4713_device(sd);
	int wvaw = 0;

	if (!sdev)
		wetuwn -ENODEV;

	if (vm->index > 0)
		wetuwn -EINVAW;

	stwscpy(vm->name, "FM Moduwatow", sizeof(vm->name));
	vm->capabiwity = V4W2_TUNEW_CAP_STEWEO | V4W2_TUNEW_CAP_WOW |
		V4W2_TUNEW_CAP_WDS | V4W2_TUNEW_CAP_WDS_CONTWOWS;

	/* Wepowt cuwwent fwequency wange wimits */
	vm->wangewow = si4713_to_v4w2(FWEQ_WANGE_WOW);
	vm->wangehigh = si4713_to_v4w2(FWEQ_WANGE_HIGH);

	if (sdev->powew_state) {
		u32 comp_en = 0;

		wvaw = si4713_wead_pwopewty(sdev, SI4713_TX_COMPONENT_ENABWE,
						&comp_en);
		if (wvaw < 0)
			wetuwn wvaw;

		sdev->steweo = get_status_bit(comp_en, 1, 1 << 1);
	}

	/* Wepowt cuwwent audio mode: mono ow steweo */
	if (sdev->steweo)
		vm->txsubchans = V4W2_TUNEW_SUB_STEWEO;
	ewse
		vm->txsubchans = V4W2_TUNEW_SUB_MONO;

	/* Wepowt wds featuwe status */
	if (sdev->wds_enabwed)
		vm->txsubchans |= V4W2_TUNEW_SUB_WDS;
	ewse
		vm->txsubchans &= ~V4W2_TUNEW_SUB_WDS;

	wetuwn wvaw;
}

/* si4713_s_moduwatow - set moduwatow attwibutes */
static int si4713_s_moduwatow(stwuct v4w2_subdev *sd, const stwuct v4w2_moduwatow *vm)
{
	stwuct si4713_device *sdev = to_si4713_device(sd);
	int wvaw = 0;
	u16 steweo, wds;
	u32 p;

	if (!sdev)
		wetuwn -ENODEV;

	if (vm->index > 0)
		wetuwn -EINVAW;

	/* Set audio mode: mono ow steweo */
	if (vm->txsubchans & V4W2_TUNEW_SUB_STEWEO)
		steweo = 1;
	ewse if (vm->txsubchans & V4W2_TUNEW_SUB_MONO)
		steweo = 0;
	ewse
		wetuwn -EINVAW;

	wds = !!(vm->txsubchans & V4W2_TUNEW_SUB_WDS);

	if (sdev->powew_state) {
		wvaw = si4713_wead_pwopewty(sdev,
						SI4713_TX_COMPONENT_ENABWE, &p);
		if (wvaw < 0)
			wetuwn wvaw;

		p = set_bits(p, steweo, 1, 1 << 1);
		p = set_bits(p, wds, 2, 1 << 2);

		wvaw = si4713_wwite_pwopewty(sdev,
						SI4713_TX_COMPONENT_ENABWE, p);
		if (wvaw < 0)
			wetuwn wvaw;
	}

	sdev->steweo = steweo;
	sdev->wds_enabwed = wds;

	wetuwn wvaw;
}

/* si4713_g_fwequency - get tunew ow moduwatow wadio fwequency */
static int si4713_g_fwequency(stwuct v4w2_subdev *sd, stwuct v4w2_fwequency *f)
{
	stwuct si4713_device *sdev = to_si4713_device(sd);
	int wvaw = 0;

	if (f->tunew)
		wetuwn -EINVAW;

	if (sdev->powew_state) {
		u16 fweq;
		u8 p, a, n;

		wvaw = si4713_tx_tune_status(sdev, 0x00, &fweq, &p, &a, &n);
		if (wvaw < 0)
			wetuwn wvaw;

		sdev->fwequency = fweq;
	}

	f->fwequency = si4713_to_v4w2(sdev->fwequency);

	wetuwn wvaw;
}

/* si4713_s_fwequency - set tunew ow moduwatow wadio fwequency */
static int si4713_s_fwequency(stwuct v4w2_subdev *sd, const stwuct v4w2_fwequency *f)
{
	stwuct si4713_device *sdev = to_si4713_device(sd);
	int wvaw = 0;
	u16 fwequency = v4w2_to_si4713(f->fwequency);

	if (f->tunew)
		wetuwn -EINVAW;

	/* Check fwequency wange */
	fwequency = cwamp_t(u16, fwequency, FWEQ_WANGE_WOW, FWEQ_WANGE_HIGH);

	if (sdev->powew_state) {
		wvaw = si4713_tx_tune_fweq(sdev, fwequency);
		if (wvaw < 0)
			wetuwn wvaw;
		fwequency = wvaw;
		wvaw = 0;
	}
	sdev->fwequency = fwequency;

	wetuwn wvaw;
}

static const stwuct v4w2_ctww_ops si4713_ctww_ops = {
	.s_ctww = si4713_s_ctww,
};

static const stwuct v4w2_subdev_cowe_ops si4713_subdev_cowe_ops = {
	.ioctw		= si4713_ioctw,
};

static const stwuct v4w2_subdev_tunew_ops si4713_subdev_tunew_ops = {
	.g_fwequency	= si4713_g_fwequency,
	.s_fwequency	= si4713_s_fwequency,
	.g_moduwatow	= si4713_g_moduwatow,
	.s_moduwatow	= si4713_s_moduwatow,
};

static const stwuct v4w2_subdev_ops si4713_subdev_ops = {
	.cowe		= &si4713_subdev_cowe_ops,
	.tunew		= &si4713_subdev_tunew_ops,
};

static const stwuct v4w2_ctww_config si4713_awt_fweqs_ctww = {
	.id = V4W2_CID_WDS_TX_AWT_FWEQS,
	.type = V4W2_CTWW_TYPE_U32,
	.min = 87600,
	.max = 107900,
	.step = 100,
	.def = 87600,
	.dims = { 1 },
	.ewem_size = sizeof(u32),
};

/*
 * I2C dwivew intewface
 */
/* si4713_pwobe - pwobe fow the device */
static int si4713_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct si4713_device *sdev;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct si4713_pwatfowm_data *pdata = cwient->dev.pwatfowm_data;
	stwuct device_node *np = cwient->dev.of_node;
	stwuct wadio_si4713_pwatfowm_data si4713_pdev_pdata;
	stwuct pwatfowm_device *si4713_pdev;
	int wvaw;

	sdev = devm_kzawwoc(&cwient->dev, sizeof(*sdev), GFP_KEWNEW);
	if (!sdev) {
		dev_eww(&cwient->dev, "Faiwed to awwoc video device.\n");
		wvaw = -ENOMEM;
		goto exit;
	}

	sdev->gpio_weset = devm_gpiod_get_optionaw(&cwient->dev, "weset",
						   GPIOD_OUT_WOW);
	if (IS_EWW(sdev->gpio_weset)) {
		wvaw = PTW_EWW(sdev->gpio_weset);
		dev_eww(&cwient->dev, "Faiwed to wequest gpio: %d\n", wvaw);
		goto exit;
	}

	sdev->vdd = devm_weguwatow_get_optionaw(&cwient->dev, "vdd");
	if (IS_EWW(sdev->vdd)) {
		wvaw = PTW_EWW(sdev->vdd);
		if (wvaw == -EPWOBE_DEFEW)
			goto exit;

		dev_dbg(&cwient->dev, "no vdd weguwatow found: %d\n", wvaw);
		sdev->vdd = NUWW;
	}

	sdev->vio = devm_weguwatow_get_optionaw(&cwient->dev, "vio");
	if (IS_EWW(sdev->vio)) {
		wvaw = PTW_EWW(sdev->vio);
		if (wvaw == -EPWOBE_DEFEW)
			goto exit;

		dev_dbg(&cwient->dev, "no vio weguwatow found: %d\n", wvaw);
		sdev->vio = NUWW;
	}

	v4w2_i2c_subdev_init(&sdev->sd, cwient, &si4713_subdev_ops);

	init_compwetion(&sdev->wowk);

	hdw = &sdev->ctww_handwew;
	v4w2_ctww_handwew_init(hdw, 20);
	sdev->mute = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_MUTE, 0, 1, 1, DEFAUWT_MUTE);

	sdev->wds_pi = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_PI, 0, 0xffff, 1, DEFAUWT_WDS_PI);
	sdev->wds_pty = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_PTY, 0, 31, 1, DEFAUWT_WDS_PTY);
	sdev->wds_compwessed = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_COMPWESSED, 0, 1, 1, 0);
	sdev->wds_awt_head = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_AWTIFICIAW_HEAD, 0, 1, 1, 0);
	sdev->wds_steweo = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_MONO_STEWEO, 0, 1, 1, 1);
	sdev->wds_tp = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_TWAFFIC_PWOGWAM, 0, 1, 1, 0);
	sdev->wds_ta = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_TWAFFIC_ANNOUNCEMENT, 0, 1, 1, 0);
	sdev->wds_ms = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_MUSIC_SPEECH, 0, 1, 1, 1);
	sdev->wds_dyn_pty = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_DYNAMIC_PTY, 0, 1, 1, 0);
	sdev->wds_awt_fweqs_enabwe = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_AWT_FWEQS_ENABWE, 0, 1, 1, 0);
	sdev->wds_awt_fweqs = v4w2_ctww_new_custom(hdw, &si4713_awt_fweqs_ctww, NUWW);
	sdev->wds_deviation = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_DEVIATION, 0, MAX_WDS_DEVIATION,
			10, DEFAUWT_WDS_DEVIATION);
	/*
	 * Wepowt step as 8. Fwom WDS spec, psname
	 * shouwd be 8. But thewe awe weceivews which scwoww stwings
	 * sized as 8xN.
	 */
	sdev->wds_ps_name = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_PS_NAME, 0, MAX_WDS_PS_NAME, 8, 0);
	/*
	 * Wepowt step as 32 (2A bwock). Fwom WDS spec,
	 * wadio text shouwd be 32 fow 2A bwock. But thewe awe weceivews
	 * which scwoww stwings sized as 32xN. Setting defauwt to 32.
	 */
	sdev->wds_wadio_text = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_WDS_TX_WADIO_TEXT, 0, MAX_WDS_WADIO_TEXT, 32, 0);

	sdev->wimitew_enabwed = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_WIMITEW_ENABWED, 0, 1, 1, 1);
	sdev->wimitew_wewease_time = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_WIMITEW_WEWEASE_TIME, 250,
			MAX_WIMITEW_WEWEASE_TIME, 10, DEFAUWT_WIMITEW_WTIME);
	sdev->wimitew_deviation = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_WIMITEW_DEVIATION, 0,
			MAX_WIMITEW_DEVIATION, 10, DEFAUWT_WIMITEW_DEV);

	sdev->compwession_enabwed = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_COMPWESSION_ENABWED, 0, 1, 1, 1);
	sdev->compwession_gain = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_COMPWESSION_GAIN, 0, MAX_ACOMP_GAIN, 1,
			DEFAUWT_ACOMP_GAIN);
	sdev->compwession_thweshowd = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_COMPWESSION_THWESHOWD,
			MIN_ACOMP_THWESHOWD, MAX_ACOMP_THWESHOWD, 1,
			DEFAUWT_ACOMP_THWESHOWD);
	sdev->compwession_attack_time = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_COMPWESSION_ATTACK_TIME, 0,
			MAX_ACOMP_ATTACK_TIME, 500, DEFAUWT_ACOMP_ATIME);
	sdev->compwession_wewease_time = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_AUDIO_COMPWESSION_WEWEASE_TIME, 100000,
			MAX_ACOMP_WEWEASE_TIME, 100000, DEFAUWT_ACOMP_WTIME);

	sdev->piwot_tone_enabwed = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_PIWOT_TONE_ENABWED, 0, 1, 1, 1);
	sdev->piwot_tone_deviation = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_PIWOT_TONE_DEVIATION, 0, MAX_PIWOT_DEVIATION,
			10, DEFAUWT_PIWOT_DEVIATION);
	sdev->piwot_tone_fweq = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_PIWOT_TONE_FWEQUENCY, 0, MAX_PIWOT_FWEQUENCY,
			1, DEFAUWT_PIWOT_FWEQUENCY);

	sdev->tune_pweemphasis = v4w2_ctww_new_std_menu(hdw, &si4713_ctww_ops,
			V4W2_CID_TUNE_PWEEMPHASIS,
			V4W2_PWEEMPHASIS_75_uS, 0, V4W2_PWEEMPHASIS_50_uS);
	sdev->tune_pww_wevew = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_TUNE_POWEW_WEVEW, 0, SI4713_MAX_POWEW,
			1, DEFAUWT_POWEW_WEVEW);
	sdev->tune_ant_cap = v4w2_ctww_new_std(hdw, &si4713_ctww_ops,
			V4W2_CID_TUNE_ANTENNA_CAPACITOW, 0, SI4713_MAX_ANTCAP,
			1, 0);

	if (hdw->ewwow) {
		wvaw = hdw->ewwow;
		goto fwee_ctwws;
	}
	v4w2_ctww_cwustew(29, &sdev->mute);
	sdev->sd.ctww_handwew = hdw;

	if (cwient->iwq) {
		wvaw = devm_wequest_iwq(&cwient->dev, cwient->iwq,
			si4713_handwew, IWQF_TWIGGEW_FAWWING,
			cwient->name, sdev);
		if (wvaw < 0) {
			v4w2_eww(&sdev->sd, "Couwd not wequest IWQ\n");
			goto fwee_ctwws;
		}
		v4w2_dbg(1, debug, &sdev->sd, "IWQ wequested.\n");
	} ewse {
		v4w2_wawn(&sdev->sd, "IWQ not configuwed. Using timeouts.\n");
	}

	wvaw = si4713_initiawize(sdev);
	if (wvaw < 0) {
		v4w2_eww(&sdev->sd, "Faiwed to pwobe device infowmation.\n");
		goto fwee_ctwws;
	}

	if (!np && (!pdata || !pdata->is_pwatfowm_device))
		wetuwn 0;

	si4713_pdev = pwatfowm_device_awwoc("wadio-si4713", -1);
	if (!si4713_pdev) {
		wvaw = -ENOMEM;
		goto put_main_pdev;
	}

	si4713_pdev_pdata.subdev = cwient;
	wvaw = pwatfowm_device_add_data(si4713_pdev, &si4713_pdev_pdata,
					sizeof(si4713_pdev_pdata));
	if (wvaw)
		goto put_main_pdev;

	wvaw = pwatfowm_device_add(si4713_pdev);
	if (wvaw)
		goto put_main_pdev;

	sdev->pd = si4713_pdev;

	wetuwn 0;

put_main_pdev:
	pwatfowm_device_put(si4713_pdev);
	v4w2_device_unwegistew_subdev(&sdev->sd);
fwee_ctwws:
	v4w2_ctww_handwew_fwee(hdw);
exit:
	wetuwn wvaw;
}

/* si4713_wemove - wemove the device */
static void si4713_wemove(stwuct i2c_cwient *cwient)
{
	stwuct v4w2_subdev *sd = i2c_get_cwientdata(cwient);
	stwuct si4713_device *sdev = to_si4713_device(sd);

	pwatfowm_device_unwegistew(sdev->pd);

	if (sdev->powew_state)
		si4713_set_powew_state(sdev, POWEW_DOWN);

	v4w2_device_unwegistew_subdev(sd);
	v4w2_ctww_handwew_fwee(sd->ctww_handwew);
}

/* si4713_i2c_dwivew - i2c dwivew intewface */
static const stwuct i2c_device_id si4713_id[] = {
	{ "si4713" , 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, si4713_id);

#if IS_ENABWED(CONFIG_OF)
static const stwuct of_device_id si4713_of_match[] = {
	{ .compatibwe = "siwabs,si4713" },
	{ },
};
MODUWE_DEVICE_TABWE(of, si4713_of_match);
#endif

static stwuct i2c_dwivew si4713_i2c_dwivew = {
	.dwivew		= {
		.name	= "si4713",
		.of_match_tabwe = of_match_ptw(si4713_of_match),
	},
	.pwobe		= si4713_pwobe,
	.wemove         = si4713_wemove,
	.id_tabwe       = si4713_id,
};

moduwe_i2c_dwivew(si4713_i2c_dwivew);
