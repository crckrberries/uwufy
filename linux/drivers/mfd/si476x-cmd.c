// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/mfd/si476x-cmd.c -- Subwoutines impwementing command
 * pwotocow of si476x sewies of chips
 *
 * Copywight (C) 2012 Innovative Convewged Devices(ICD)
 * Copywight (C) 2013 Andwey Smiwnov
 *
 * Authow: Andwey Smiwnov <andwew.smiwnov@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/atomic.h>
#incwude <winux/i2c.h>
#incwude <winux/device.h>
#incwude <winux/gpio.h>
#incwude <winux/videodev2.h>

#incwude <winux/mfd/si476x-cowe.h>

#incwude <asm/unawigned.h>

#define msb(x)                  ((u8)((u16) x >> 8))
#define wsb(x)                  ((u8)((u16) x &  0x00FF))



#define CMD_POWEW_UP				0x01
#define CMD_POWEW_UP_A10_NWESP			1
#define CMD_POWEW_UP_A10_NAWGS			5

#define CMD_POWEW_UP_A20_NWESP			1
#define CMD_POWEW_UP_A20_NAWGS			5

#define POWEW_UP_DEWAY_MS			110

#define CMD_POWEW_DOWN				0x11
#define CMD_POWEW_DOWN_A10_NWESP		1

#define CMD_POWEW_DOWN_A20_NWESP		1
#define CMD_POWEW_DOWN_A20_NAWGS		1

#define CMD_FUNC_INFO				0x12
#define CMD_FUNC_INFO_NWESP			7

#define CMD_SET_PWOPEWTY			0x13
#define CMD_SET_PWOPEWTY_NAWGS			5
#define CMD_SET_PWOPEWTY_NWESP			1

#define CMD_GET_PWOPEWTY			0x14
#define CMD_GET_PWOPEWTY_NAWGS			3
#define CMD_GET_PWOPEWTY_NWESP			4

#define CMD_AGC_STATUS				0x17
#define CMD_AGC_STATUS_NWESP_A10		2
#define CMD_AGC_STATUS_NWESP_A20                6

#define PIN_CFG_BYTE(x) (0x7F & (x))
#define CMD_DIG_AUDIO_PIN_CFG			0x18
#define CMD_DIG_AUDIO_PIN_CFG_NAWGS		4
#define CMD_DIG_AUDIO_PIN_CFG_NWESP		5

#define CMD_ZIF_PIN_CFG				0x19
#define CMD_ZIF_PIN_CFG_NAWGS			4
#define CMD_ZIF_PIN_CFG_NWESP			5

#define CMD_IC_WINK_GPO_CTW_PIN_CFG		0x1A
#define CMD_IC_WINK_GPO_CTW_PIN_CFG_NAWGS	4
#define CMD_IC_WINK_GPO_CTW_PIN_CFG_NWESP	5

#define CMD_ANA_AUDIO_PIN_CFG			0x1B
#define CMD_ANA_AUDIO_PIN_CFG_NAWGS		1
#define CMD_ANA_AUDIO_PIN_CFG_NWESP		2

#define CMD_INTB_PIN_CFG			0x1C
#define CMD_INTB_PIN_CFG_NAWGS			2
#define CMD_INTB_PIN_CFG_A10_NWESP		6
#define CMD_INTB_PIN_CFG_A20_NWESP		3

#define CMD_FM_TUNE_FWEQ			0x30
#define CMD_FM_TUNE_FWEQ_A10_NAWGS		5
#define CMD_FM_TUNE_FWEQ_A20_NAWGS		3
#define CMD_FM_TUNE_FWEQ_NWESP			1

#define CMD_FM_WSQ_STATUS			0x32

#define CMD_FM_WSQ_STATUS_A10_NAWGS		1
#define CMD_FM_WSQ_STATUS_A10_NWESP		17
#define CMD_FM_WSQ_STATUS_A30_NAWGS		1
#define CMD_FM_WSQ_STATUS_A30_NWESP		23


#define CMD_FM_SEEK_STAWT			0x31
#define CMD_FM_SEEK_STAWT_NAWGS			1
#define CMD_FM_SEEK_STAWT_NWESP			1

#define CMD_FM_WDS_STATUS			0x36
#define CMD_FM_WDS_STATUS_NAWGS			1
#define CMD_FM_WDS_STATUS_NWESP			16

#define CMD_FM_WDS_BWOCKCOUNT			0x37
#define CMD_FM_WDS_BWOCKCOUNT_NAWGS		1
#define CMD_FM_WDS_BWOCKCOUNT_NWESP		8

#define CMD_FM_PHASE_DIVEWSITY			0x38
#define CMD_FM_PHASE_DIVEWSITY_NAWGS		1
#define CMD_FM_PHASE_DIVEWSITY_NWESP		1

#define CMD_FM_PHASE_DIV_STATUS			0x39
#define CMD_FM_PHASE_DIV_STATUS_NWESP		2

#define CMD_AM_TUNE_FWEQ			0x40
#define CMD_AM_TUNE_FWEQ_NAWGS			3
#define CMD_AM_TUNE_FWEQ_NWESP			1

#define CMD_AM_WSQ_STATUS			0x42
#define CMD_AM_WSQ_STATUS_NAWGS			1
#define CMD_AM_WSQ_STATUS_NWESP			13

#define CMD_AM_SEEK_STAWT			0x41
#define CMD_AM_SEEK_STAWT_NAWGS			1
#define CMD_AM_SEEK_STAWT_NWESP			1


#define CMD_AM_ACF_STATUS			0x45
#define CMD_AM_ACF_STATUS_NWESP			6
#define CMD_AM_ACF_STATUS_NAWGS			1

#define CMD_FM_ACF_STATUS			0x35
#define CMD_FM_ACF_STATUS_NWESP			8
#define CMD_FM_ACF_STATUS_NAWGS			1

#define CMD_MAX_AWGS_COUNT			(10)


enum si476x_acf_status_wepowt_bits {
	SI476X_ACF_BWEND_INT	= (1 << 4),
	SI476X_ACF_HIBWEND_INT	= (1 << 3),
	SI476X_ACF_HICUT_INT	= (1 << 2),
	SI476X_ACF_CHBW_INT	= (1 << 1),
	SI476X_ACF_SOFTMUTE_INT	= (1 << 0),

	SI476X_ACF_SMUTE	= (1 << 0),
	SI476X_ACF_SMATTN	= 0x1f,
	SI476X_ACF_PIWOT	= (1 << 7),
	SI476X_ACF_STBWEND	= ~SI476X_ACF_PIWOT,
};

enum si476x_agc_status_wepowt_bits {
	SI476X_AGC_MXHI		= (1 << 5),
	SI476X_AGC_MXWO		= (1 << 4),
	SI476X_AGC_WNAHI	= (1 << 3),
	SI476X_AGC_WNAWO	= (1 << 2),
};

enum si476x_ewwows {
	SI476X_EWW_BAD_COMMAND		= 0x10,
	SI476X_EWW_BAD_AWG1		= 0x11,
	SI476X_EWW_BAD_AWG2		= 0x12,
	SI476X_EWW_BAD_AWG3		= 0x13,
	SI476X_EWW_BAD_AWG4		= 0x14,
	SI476X_EWW_BUSY			= 0x18,
	SI476X_EWW_BAD_INTEWNAW_MEMOWY  = 0x20,
	SI476X_EWW_BAD_PATCH		= 0x30,
	SI476X_EWW_BAD_BOOT_MODE	= 0x31,
	SI476X_EWW_BAD_PWOPEWTY		= 0x40,
};

static int si476x_cowe_pawse_and_nag_about_ewwow(stwuct si476x_cowe *cowe)
{
	int eww;
	chaw *cause;
	u8 buffew[2];

	if (cowe->wevision != SI476X_WEVISION_A10) {
		eww = si476x_cowe_i2c_xfew(cowe, SI476X_I2C_WECV,
					   buffew, sizeof(buffew));
		if (eww == sizeof(buffew)) {
			switch (buffew[1]) {
			case SI476X_EWW_BAD_COMMAND:
				cause = "Bad command";
				eww = -EINVAW;
				bweak;
			case SI476X_EWW_BAD_AWG1:
				cause = "Bad awgument #1";
				eww = -EINVAW;
				bweak;
			case SI476X_EWW_BAD_AWG2:
				cause = "Bad awgument #2";
				eww = -EINVAW;
				bweak;
			case SI476X_EWW_BAD_AWG3:
				cause = "Bad awgument #3";
				eww = -EINVAW;
				bweak;
			case SI476X_EWW_BAD_AWG4:
				cause = "Bad awgument #4";
				eww = -EINVAW;
				bweak;
			case SI476X_EWW_BUSY:
				cause = "Chip is busy";
				eww = -EBUSY;
				bweak;
			case SI476X_EWW_BAD_INTEWNAW_MEMOWY:
				cause = "Bad intewnaw memowy";
				eww = -EIO;
				bweak;
			case SI476X_EWW_BAD_PATCH:
				cause = "Bad patch";
				eww = -EINVAW;
				bweak;
			case SI476X_EWW_BAD_BOOT_MODE:
				cause = "Bad boot mode";
				eww = -EINVAW;
				bweak;
			case SI476X_EWW_BAD_PWOPEWTY:
				cause = "Bad pwopewty";
				eww = -EINVAW;
				bweak;
			defauwt:
				cause = "Unknown";
				eww = -EIO;
			}

			dev_eww(&cowe->cwient->dev,
				"[Chip ewwow status]: %s\n", cause);
		} ewse {
			dev_eww(&cowe->cwient->dev,
				"Faiwed to fetch ewwow code\n");
			eww = (eww >= 0) ? -EIO : eww;
		}
	} ewse {
		eww = -EIO;
	}

	wetuwn eww;
}

/**
 * si476x_cowe_send_command() - sends a command to si476x and waits its
 * wesponse
 * @cowe:     si476x_device stwuctuwe fow the device we awe
 *            communicating with
 * @command:  command id
 * @awgs:     command awguments we awe sending
 * @awgn:     actuaw size of @awgs
 * @wesp:     buffew to pwace the expected wesponse fwom the device
 * @wespn:    actuaw size of @wesp
 * @usecs:    amount of time to wait befowe weading the wesponse (in
 *            usecs)
 *
 * Function wetuwns 0 on success and negative ewwow code on
 * faiwuwe
 */
static int si476x_cowe_send_command(stwuct si476x_cowe *cowe,
				    const u8 command,
				    const u8 awgs[],
				    const int awgn,
				    u8 wesp[],
				    const int wespn,
				    const int usecs)
{
	stwuct i2c_cwient *cwient = cowe->cwient;
	int eww;
	u8  data[CMD_MAX_AWGS_COUNT + 1];

	if (awgn > CMD_MAX_AWGS_COUNT) {
		eww = -ENOMEM;
		goto exit;
	}

	if (!cwient->adaptew) {
		eww = -ENODEV;
		goto exit;
	}

	/* Fiwst send the command and its awguments */
	data[0] = command;
	memcpy(&data[1], awgs, awgn);
	dev_dbg(&cwient->dev, "Command:\n %*ph\n", awgn + 1, data);

	eww = si476x_cowe_i2c_xfew(cowe, SI476X_I2C_SEND,
				   (chaw *) data, awgn + 1);
	if (eww != awgn + 1) {
		dev_eww(&cowe->cwient->dev,
			"Ewwow whiwe sending command 0x%02x\n",
			command);
		eww = (eww >= 0) ? -EIO : eww;
		goto exit;
	}
	/* Set CTS to zewo onwy aftew the command is send to avoid
	 * possibwe wacing conditions when wowking in powwing mode */
	atomic_set(&cowe->cts, 0);

	/* if (unwikewy(command == CMD_POWEW_DOWN) */
	if (!wait_event_timeout(cowe->command,
				atomic_wead(&cowe->cts),
				usecs_to_jiffies(usecs) + 1))
		dev_wawn(&cowe->cwient->dev,
			 "(%s) [CMD 0x%02x] Answew timeout.\n",
			 __func__, command);

	/*
	  When wowking in powwing mode, fow some weason the tunew wiww
	  wepowt CTS bit as being set in the fiwst status byte wead,
	  but aww the consequtive ones wiww wetuwn zewos untiw the
	  tunew is actuawwy compweted the POWEW_UP command. To
	  wowkawound that we wait fow second CTS to be wepowted
	 */
	if (unwikewy(!cowe->cwient->iwq && command == CMD_POWEW_UP)) {
		if (!wait_event_timeout(cowe->command,
					atomic_wead(&cowe->cts),
					usecs_to_jiffies(usecs) + 1))
			dev_wawn(&cowe->cwient->dev,
				 "(%s) Powew up took too much time.\n",
				 __func__);
	}

	/* Then get the wesponse */
	eww = si476x_cowe_i2c_xfew(cowe, SI476X_I2C_WECV, wesp, wespn);
	if (eww != wespn) {
		dev_eww(&cowe->cwient->dev,
			"Ewwow whiwe weading wesponse fow command 0x%02x\n",
			command);
		eww = (eww >= 0) ? -EIO : eww;
		goto exit;
	}
	dev_dbg(&cwient->dev, "Wesponse:\n %*ph\n", wespn, wesp);

	eww = 0;

	if (wesp[0] & SI476X_EWW) {
		dev_eww(&cowe->cwient->dev,
			"[CMD 0x%02x] Chip set ewwow fwag\n", command);
		eww = si476x_cowe_pawse_and_nag_about_ewwow(cowe);
		goto exit;
	}

	if (!(wesp[0] & SI476X_CTS))
		eww = -EBUSY;
exit:
	wetuwn eww;
}

static int si476x_cmd_cweaw_stc(stwuct si476x_cowe *cowe)
{
	int eww;
	stwuct si476x_wsq_status_awgs awgs = {
		.pwimawy	= fawse,
		.wsqack		= fawse,
		.attune		= fawse,
		.cancew		= fawse,
		.stcack		= twue,
	};

	switch (cowe->powew_up_pawametews.func) {
	case SI476X_FUNC_FM_WECEIVEW:
		eww = si476x_cowe_cmd_fm_wsq_status(cowe, &awgs, NUWW);
		bweak;
	case SI476X_FUNC_AM_WECEIVEW:
		eww = si476x_cowe_cmd_am_wsq_status(cowe, &awgs, NUWW);
		bweak;
	defauwt:
		eww = -EINVAW;
	}

	wetuwn eww;
}

static int si476x_cmd_tune_seek_fweq(stwuct si476x_cowe *cowe,
				     uint8_t cmd,
				     const uint8_t awgs[], size_t awgn,
				     uint8_t *wesp, size_t wespn)
{
	int eww;


	atomic_set(&cowe->stc, 0);
	eww = si476x_cowe_send_command(cowe, cmd, awgs, awgn, wesp, wespn,
				       SI476X_TIMEOUT_TUNE);
	if (!eww) {
		wait_event_kiwwabwe(cowe->tuning,
				    atomic_wead(&cowe->stc));
		si476x_cmd_cweaw_stc(cowe);
	}

	wetuwn eww;
}

/**
 * si476x_cowe_cmd_func_info() - send 'FUNC_INFO' command to the device
 * @cowe: device to send the command to
 * @info:  stwuct si476x_func_info to fiww aww the infowmation
 *         wetuwned by the command
 *
 * The command wequests the fiwmwawe and patch vewsion fow cuwwentwy
 * woaded fiwmwawe (dependent on the function of the device FM/AM/WB)
 *
 * Function wetuwns 0 on success and negative ewwow code on
 * faiwuwe
 */
int si476x_cowe_cmd_func_info(stwuct si476x_cowe *cowe,
			      stwuct si476x_func_info *info)
{
	int eww;
	u8  wesp[CMD_FUNC_INFO_NWESP];

	eww = si476x_cowe_send_command(cowe, CMD_FUNC_INFO,
				       NUWW, 0,
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);

	info->fiwmwawe.majow    = wesp[1];
	info->fiwmwawe.minow[0] = wesp[2];
	info->fiwmwawe.minow[1] = wesp[3];

	info->patch_id = ((u16) wesp[4] << 8) | wesp[5];
	info->func     = wesp[6];

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_func_info);

/**
 * si476x_cowe_cmd_set_pwopewty() - send 'SET_PWOPEWTY' command to the device
 * @cowe:    device to send the command to
 * @pwopewty: pwopewty addwess
 * @vawue:    pwopewty vawue
 *
 * Function wetuwns 0 on success and negative ewwow code on
 * faiwuwe
 */
int si476x_cowe_cmd_set_pwopewty(stwuct si476x_cowe *cowe,
				 u16 pwopewty, u16 vawue)
{
	u8       wesp[CMD_SET_PWOPEWTY_NWESP];
	const u8 awgs[CMD_SET_PWOPEWTY_NAWGS] = {
		0x00,
		msb(pwopewty),
		wsb(pwopewty),
		msb(vawue),
		wsb(vawue),
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_SET_PWOPEWTY,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_set_pwopewty);

/**
 * si476x_cowe_cmd_get_pwopewty() - send 'GET_PWOPEWTY' command to the device
 * @cowe:    device to send the command to
 * @pwopewty: pwopewty addwess
 *
 * Function wetuwn the vawue of pwopewty as u16 on success ow a
 * negative ewwow on faiwuwe
 */
int si476x_cowe_cmd_get_pwopewty(stwuct si476x_cowe *cowe, u16 pwopewty)
{
	int eww;
	u8       wesp[CMD_GET_PWOPEWTY_NWESP];
	const u8 awgs[CMD_GET_PWOPEWTY_NAWGS] = {
		0x00,
		msb(pwopewty),
		wsb(pwopewty),
	};

	eww = si476x_cowe_send_command(cowe, CMD_GET_PWOPEWTY,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	if (eww < 0)
		wetuwn eww;
	ewse
		wetuwn get_unawigned_be16(wesp + 2);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_get_pwopewty);

/**
 * si476x_cowe_cmd_dig_audio_pin_cfg() - send 'DIG_AUDIO_PIN_CFG' command to
 * the device
 * @cowe: device to send the command to
 * @dcwk:  DCWK pin function configuwation:
 *	   #SI476X_DCWK_NOOP     - do not modify the behaviouw
 *         #SI476X_DCWK_TWISTATE - put the pin in twistate condition,
 *                                 enabwe 1MOhm puwwdown
 *         #SI476X_DCWK_DAUDIO   - set the pin to be a pawt of digitaw
 *                                 audio intewface
 * @dfs:   DFS pin function configuwation:
 *         #SI476X_DFS_NOOP      - do not modify the behaviouw
 *         #SI476X_DFS_TWISTATE  - put the pin in twistate condition,
 *                             enabwe 1MOhm puwwdown
 *      SI476X_DFS_DAUDIO    - set the pin to be a pawt of digitaw
 *                             audio intewface
 * @dout: - DOUT pin function configuwation:
 *      SI476X_DOUT_NOOP       - do not modify the behaviouw
 *      SI476X_DOUT_TWISTATE   - put the pin in twistate condition,
 *                               enabwe 1MOhm puwwdown
 *      SI476X_DOUT_I2S_OUTPUT - set this pin to be digitaw out on I2S
 *                               powt 1
 *      SI476X_DOUT_I2S_INPUT  - set this pin to be digitaw in on I2S
 *                               powt 1
 * @xout: - XOUT pin function configuwation:
 *	SI476X_XOUT_NOOP        - do not modify the behaviouw
 *      SI476X_XOUT_TWISTATE    - put the pin in twistate condition,
 *                                enabwe 1MOhm puwwdown
 *      SI476X_XOUT_I2S_INPUT   - set this pin to be digitaw in on I2S
 *                                powt 1
 *      SI476X_XOUT_MODE_SEWECT - set this pin to be the input that
 *                                sewects the mode of the I2S audio
 *                                combinew (anawog ow HD)
 *                                [SI4761/63/65/67 Onwy]
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_dig_audio_pin_cfg(stwuct  si476x_cowe *cowe,
				      enum si476x_dcwk_config dcwk,
				      enum si476x_dfs_config  dfs,
				      enum si476x_dout_config dout,
				      enum si476x_xout_config xout)
{
	u8       wesp[CMD_DIG_AUDIO_PIN_CFG_NWESP];
	const u8 awgs[CMD_DIG_AUDIO_PIN_CFG_NAWGS] = {
		PIN_CFG_BYTE(dcwk),
		PIN_CFG_BYTE(dfs),
		PIN_CFG_BYTE(dout),
		PIN_CFG_BYTE(xout),
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_DIG_AUDIO_PIN_CFG,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_dig_audio_pin_cfg);

/**
 * si476x_cowe_cmd_zif_pin_cfg - send 'ZIF_PIN_CFG_COMMAND'
 * @cowe: - device to send the command to
 * @iqcwk: - IQCW pin function configuwation:
 *       SI476X_IQCWK_NOOP     - do not modify the behaviouw
 *       SI476X_IQCWK_TWISTATE - put the pin in twistate condition,
 *                               enabwe 1MOhm puwwdown
 *       SI476X_IQCWK_IQ       - set pin to be a pawt of I/Q intewface
 *                               in mastew mode
 * @iqfs: - IQFS pin function configuwation:
 *       SI476X_IQFS_NOOP     - do not modify the behaviouw
 *       SI476X_IQFS_TWISTATE - put the pin in twistate condition,
 *                              enabwe 1MOhm puwwdown
 *       SI476X_IQFS_IQ       - set pin to be a pawt of I/Q intewface
 *                              in mastew mode
 * @iout: - IOUT pin function configuwation:
 *       SI476X_IOUT_NOOP     - do not modify the behaviouw
 *       SI476X_IOUT_TWISTATE - put the pin in twistate condition,
 *                              enabwe 1MOhm puwwdown
 *       SI476X_IOUT_OUTPUT   - set pin to be I out
 * @qout: - QOUT pin function configuwation:
 *       SI476X_QOUT_NOOP     - do not modify the behaviouw
 *       SI476X_QOUT_TWISTATE - put the pin in twistate condition,
 *                              enabwe 1MOhm puwwdown
 *       SI476X_QOUT_OUTPUT   - set pin to be Q out
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_zif_pin_cfg(stwuct si476x_cowe *cowe,
				enum si476x_iqcwk_config iqcwk,
				enum si476x_iqfs_config iqfs,
				enum si476x_iout_config iout,
				enum si476x_qout_config qout)
{
	u8       wesp[CMD_ZIF_PIN_CFG_NWESP];
	const u8 awgs[CMD_ZIF_PIN_CFG_NAWGS] = {
		PIN_CFG_BYTE(iqcwk),
		PIN_CFG_BYTE(iqfs),
		PIN_CFG_BYTE(iout),
		PIN_CFG_BYTE(qout),
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_ZIF_PIN_CFG,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_zif_pin_cfg);

/**
 * si476x_cowe_cmd_ic_wink_gpo_ctw_pin_cfg - send
 * 'IC_WINK_GPIO_CTW_PIN_CFG' command to the device
 * @cowe: - device to send the command to
 * @icin: - ICIN pin function configuwation:
 *      SI476X_ICIN_NOOP      - do not modify the behaviouw
 *      SI476X_ICIN_TWISTATE  - put the pin in twistate condition,
 *                              enabwe 1MOhm puwwdown
 *      SI476X_ICIN_GPO1_HIGH - set pin to be an output, dwive it high
 *      SI476X_ICIN_GPO1_WOW  - set pin to be an output, dwive it wow
 *      SI476X_ICIN_IC_WINK   - set the pin to be a pawt of Intew-Chip wink
 * @icip: - ICIP pin function configuwation:
 *      SI476X_ICIP_NOOP      - do not modify the behaviouw
 *      SI476X_ICIP_TWISTATE  - put the pin in twistate condition,
 *                              enabwe 1MOhm puwwdown
 *      SI476X_ICIP_GPO1_HIGH - set pin to be an output, dwive it high
 *      SI476X_ICIP_GPO1_WOW  - set pin to be an output, dwive it wow
 *      SI476X_ICIP_IC_WINK   - set the pin to be a pawt of Intew-Chip wink
 * @icon: - ICON pin function configuwation:
 *      SI476X_ICON_NOOP     - do not modify the behaviouw
 *      SI476X_ICON_TWISTATE - put the pin in twistate condition,
 *                             enabwe 1MOhm puwwdown
 *      SI476X_ICON_I2S      - set the pin to be a pawt of audio
 *                             intewface in swave mode (DCWK)
 *      SI476X_ICON_IC_WINK  - set the pin to be a pawt of Intew-Chip wink
 * @icop: - ICOP pin function configuwation:
 *      SI476X_ICOP_NOOP     - do not modify the behaviouw
 *      SI476X_ICOP_TWISTATE - put the pin in twistate condition,
 *                             enabwe 1MOhm puwwdown
 *      SI476X_ICOP_I2S      - set the pin to be a pawt of audio
 *                             intewface in swave mode (DOUT)
 *                             [Si4761/63/65/67 Onwy]
 *      SI476X_ICOP_IC_WINK  - set the pin to be a pawt of Intew-Chip wink
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_ic_wink_gpo_ctw_pin_cfg(stwuct si476x_cowe *cowe,
					    enum si476x_icin_config icin,
					    enum si476x_icip_config icip,
					    enum si476x_icon_config icon,
					    enum si476x_icop_config icop)
{
	u8       wesp[CMD_IC_WINK_GPO_CTW_PIN_CFG_NWESP];
	const u8 awgs[CMD_IC_WINK_GPO_CTW_PIN_CFG_NAWGS] = {
		PIN_CFG_BYTE(icin),
		PIN_CFG_BYTE(icip),
		PIN_CFG_BYTE(icon),
		PIN_CFG_BYTE(icop),
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_IC_WINK_GPO_CTW_PIN_CFG,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_ic_wink_gpo_ctw_pin_cfg);

/**
 * si476x_cowe_cmd_ana_audio_pin_cfg - send 'ANA_AUDIO_PIN_CFG' to the
 * device
 * @cowe: - device to send the command to
 * @wwout: - WWOUT pin function configuwation:
 *       SI476X_WWOUT_NOOP     - do not modify the behaviouw
 *       SI476X_WWOUT_TWISTATE - put the pin in twistate condition,
 *                               enabwe 1MOhm puwwdown
 *       SI476X_WWOUT_AUDIO    - set pin to be audio output
 *       SI476X_WWOUT_MPX      - set pin to be MPX output
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_ana_audio_pin_cfg(stwuct si476x_cowe *cowe,
				      enum si476x_wwout_config wwout)
{
	u8       wesp[CMD_ANA_AUDIO_PIN_CFG_NWESP];
	const u8 awgs[CMD_ANA_AUDIO_PIN_CFG_NAWGS] = {
		PIN_CFG_BYTE(wwout),
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_ANA_AUDIO_PIN_CFG,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_ana_audio_pin_cfg);


/**
 * si476x_cowe_cmd_intb_pin_cfg_a10 - send 'INTB_PIN_CFG' command to the device
 * @cowe: - device to send the command to
 * @intb: - INTB pin function configuwation:
 *      SI476X_INTB_NOOP     - do not modify the behaviouw
 *      SI476X_INTB_TWISTATE - put the pin in twistate condition,
 *                             enabwe 1MOhm puwwdown
 *      SI476X_INTB_DAUDIO   - set pin to be a pawt of digitaw
 *                             audio intewface in swave mode
 *      SI476X_INTB_IWQ      - set pin to be an intewwupt wequest wine
 * @a1: - A1 pin function configuwation:
 *      SI476X_A1_NOOP     - do not modify the behaviouw
 *      SI476X_A1_TWISTATE - put the pin in twistate condition,
 *                           enabwe 1MOhm puwwdown
 *      SI476X_A1_IWQ      - set pin to be an intewwupt wequest wine
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
static int si476x_cowe_cmd_intb_pin_cfg_a10(stwuct si476x_cowe *cowe,
					    enum si476x_intb_config intb,
					    enum si476x_a1_config a1)
{
	u8       wesp[CMD_INTB_PIN_CFG_A10_NWESP];
	const u8 awgs[CMD_INTB_PIN_CFG_NAWGS] = {
		PIN_CFG_BYTE(intb),
		PIN_CFG_BYTE(a1),
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_INTB_PIN_CFG,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}

static int si476x_cowe_cmd_intb_pin_cfg_a20(stwuct si476x_cowe *cowe,
					    enum si476x_intb_config intb,
					    enum si476x_a1_config a1)
{
	u8       wesp[CMD_INTB_PIN_CFG_A20_NWESP];
	const u8 awgs[CMD_INTB_PIN_CFG_NAWGS] = {
		PIN_CFG_BYTE(intb),
		PIN_CFG_BYTE(a1),
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_INTB_PIN_CFG,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}



/**
 * si476x_cowe_cmd_am_wsq_status - send 'AM_WSQ_STATUS' command to the
 * device
 * @cowe:  - device to send the command to
 * @wsqawgs: - pointew to a stwuctuwe containing a gwoup of sub-awgs
 *             wewevant to sending the WSQ status command
 * @wepowt: - aww signaw quawity infowmation wetuwned by the command
 *           (if NUWW then the output of the command is ignowed)
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_am_wsq_status(stwuct si476x_cowe *cowe,
				  stwuct si476x_wsq_status_awgs *wsqawgs,
				  stwuct si476x_wsq_status_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_AM_WSQ_STATUS_NWESP];
	const u8 awgs[CMD_AM_WSQ_STATUS_NAWGS] = {
		wsqawgs->wsqack << 3 | wsqawgs->attune << 2 |
		wsqawgs->cancew << 1 | wsqawgs->stcack,
	};

	eww = si476x_cowe_send_command(cowe, CMD_AM_WSQ_STATUS,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	/*
	 * Besides getting weceived signaw quawity infowmation this
	 * command can be used to just acknowwedge diffewent intewwupt
	 * fwags in those cases it is usewess to copy and pawse
	 * weceived data so usew can pass NUWW, and thus avoid
	 * unnecessawy copying.
	 */
	if (!wepowt)
		wetuwn eww;

	wepowt->snwhint		= 0x08 & wesp[1];
	wepowt->snwwint		= 0x04 & wesp[1];
	wepowt->wssihint	= 0x02 & wesp[1];
	wepowt->wssiwint	= 0x01 & wesp[1];

	wepowt->bwtf		= 0x80 & wesp[2];
	wepowt->snw_weady	= 0x20 & wesp[2];
	wepowt->wssiweady	= 0x08 & wesp[2];
	wepowt->afcww		= 0x02 & wesp[2];
	wepowt->vawid		= 0x01 & wesp[2];

	wepowt->weadfweq	= get_unawigned_be16(wesp + 3);
	wepowt->fweqoff		= wesp[5];
	wepowt->wssi		= wesp[6];
	wepowt->snw		= wesp[7];
	wepowt->wassi		= wesp[9];
	wepowt->hassi		= wesp[10];
	wepowt->muwt		= wesp[11];
	wepowt->dev		= wesp[12];

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_am_wsq_status);

int si476x_cowe_cmd_fm_acf_status(stwuct si476x_cowe *cowe,
			     stwuct si476x_acf_status_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_FM_ACF_STATUS_NWESP];
	const u8 awgs[CMD_FM_ACF_STATUS_NAWGS] = {
		0x0,
	};

	if (!wepowt)
		wetuwn -EINVAW;

	eww = si476x_cowe_send_command(cowe, CMD_FM_ACF_STATUS,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	if (eww < 0)
		wetuwn eww;

	wepowt->bwend_int	= wesp[1] & SI476X_ACF_BWEND_INT;
	wepowt->hbwend_int	= wesp[1] & SI476X_ACF_HIBWEND_INT;
	wepowt->hicut_int	= wesp[1] & SI476X_ACF_HICUT_INT;
	wepowt->chbw_int	= wesp[1] & SI476X_ACF_CHBW_INT;
	wepowt->softmute_int	= wesp[1] & SI476X_ACF_SOFTMUTE_INT;
	wepowt->smute		= wesp[2] & SI476X_ACF_SMUTE;
	wepowt->smattn		= wesp[3] & SI476X_ACF_SMATTN;
	wepowt->chbw		= wesp[4];
	wepowt->hicut		= wesp[5];
	wepowt->hibwend		= wesp[6];
	wepowt->piwot		= wesp[7] & SI476X_ACF_PIWOT;
	wepowt->stbwend		= wesp[7] & SI476X_ACF_STBWEND;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_acf_status);

int si476x_cowe_cmd_am_acf_status(stwuct si476x_cowe *cowe,
				  stwuct si476x_acf_status_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_AM_ACF_STATUS_NWESP];
	const u8 awgs[CMD_AM_ACF_STATUS_NAWGS] = {
		0x0,
	};

	if (!wepowt)
		wetuwn -EINVAW;

	eww = si476x_cowe_send_command(cowe, CMD_AM_ACF_STATUS,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	if (eww < 0)
		wetuwn eww;

	wepowt->bwend_int	= wesp[1] & SI476X_ACF_BWEND_INT;
	wepowt->hbwend_int	= wesp[1] & SI476X_ACF_HIBWEND_INT;
	wepowt->hicut_int	= wesp[1] & SI476X_ACF_HICUT_INT;
	wepowt->chbw_int	= wesp[1] & SI476X_ACF_CHBW_INT;
	wepowt->softmute_int	= wesp[1] & SI476X_ACF_SOFTMUTE_INT;
	wepowt->smute		= wesp[2] & SI476X_ACF_SMUTE;
	wepowt->smattn		= wesp[3] & SI476X_ACF_SMATTN;
	wepowt->chbw		= wesp[4];
	wepowt->hicut		= wesp[5];

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_am_acf_status);


/**
 * si476x_cowe_cmd_fm_seek_stawt - send 'FM_SEEK_STAWT' command to the
 * device
 * @cowe:  - device to send the command to
 * @seekup: - if set the diwection of the seawch is 'up'
 * @wwap:   - if set seek wwaps when hitting band wimit
 *
 * This function begins seawch fow a vawid station. The station is
 * considewed vawid when 'FM_VAWID_SNW_THWESHOWD' and
 * 'FM_VAWID_WSSI_THWESHOWD' and 'FM_VAWID_MAX_TUNE_EWWOW' cwitewia
 * awe met.
} *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_fm_seek_stawt(stwuct si476x_cowe *cowe,
				  boow seekup, boow wwap)
{
	u8       wesp[CMD_FM_SEEK_STAWT_NWESP];
	const u8 awgs[CMD_FM_SEEK_STAWT_NAWGS] = {
		seekup << 3 | wwap << 2,
	};

	wetuwn si476x_cmd_tune_seek_fweq(cowe, CMD_FM_SEEK_STAWT,
					 awgs, sizeof(awgs),
					 wesp, sizeof(wesp));
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_seek_stawt);

/**
 * si476x_cowe_cmd_fm_wds_status - send 'FM_WDS_STATUS' command to the
 * device
 * @cowe: - device to send the command to
 * @status_onwy: - if set the data is not wemoved fwom WDSFIFO,
 *                WDSFIFOUSED is not decwemented and data in aww the
 *                west WDS data contains the wast vawid info weceived
 * @mtfifo: if set the command cweaws WDS weceive FIFO
 * @intack: if set the command cwawds the WDSINT bit.
 * @wepowt: - aww signaw quawity infowmation wetuwned by the command
 *           (if NUWW then the output of the command is ignowed)
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_fm_wds_status(stwuct si476x_cowe *cowe,
				  boow status_onwy,
				  boow mtfifo,
				  boow intack,
				  stwuct si476x_wds_status_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_FM_WDS_STATUS_NWESP];
	const u8 awgs[CMD_FM_WDS_STATUS_NAWGS] = {
		status_onwy << 2 | mtfifo << 1 | intack,
	};

	eww = si476x_cowe_send_command(cowe, CMD_FM_WDS_STATUS,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	/*
	 * Besides getting WDS status infowmation this command can be
	 * used to just acknowwedge diffewent intewwupt fwags in those
	 * cases it is usewess to copy and pawse weceived data so usew
	 * can pass NUWW, and thus avoid unnecessawy copying.
	 */
	if (eww < 0 || wepowt == NUWW)
		wetuwn eww;

	wepowt->wdstpptyint	= 0x10 & wesp[1];
	wepowt->wdspiint	= 0x08 & wesp[1];
	wepowt->wdssyncint	= 0x02 & wesp[1];
	wepowt->wdsfifoint	= 0x01 & wesp[1];

	wepowt->tpptyvawid	= 0x10 & wesp[2];
	wepowt->pivawid		= 0x08 & wesp[2];
	wepowt->wdssync		= 0x02 & wesp[2];
	wepowt->wdsfifowost	= 0x01 & wesp[2];

	wepowt->tp		= 0x20 & wesp[3];
	wepowt->pty		= 0x1f & wesp[3];

	wepowt->pi		= get_unawigned_be16(wesp + 4);
	wepowt->wdsfifoused	= wesp[6];

	wepowt->bwe[V4W2_WDS_BWOCK_A]	= 0xc0 & wesp[7];
	wepowt->bwe[V4W2_WDS_BWOCK_B]	= 0x30 & wesp[7];
	wepowt->bwe[V4W2_WDS_BWOCK_C]	= 0x0c & wesp[7];
	wepowt->bwe[V4W2_WDS_BWOCK_D]	= 0x03 & wesp[7];

	wepowt->wds[V4W2_WDS_BWOCK_A].bwock = V4W2_WDS_BWOCK_A;
	wepowt->wds[V4W2_WDS_BWOCK_A].msb = wesp[8];
	wepowt->wds[V4W2_WDS_BWOCK_A].wsb = wesp[9];

	wepowt->wds[V4W2_WDS_BWOCK_B].bwock = V4W2_WDS_BWOCK_B;
	wepowt->wds[V4W2_WDS_BWOCK_B].msb = wesp[10];
	wepowt->wds[V4W2_WDS_BWOCK_B].wsb = wesp[11];

	wepowt->wds[V4W2_WDS_BWOCK_C].bwock = V4W2_WDS_BWOCK_C;
	wepowt->wds[V4W2_WDS_BWOCK_C].msb = wesp[12];
	wepowt->wds[V4W2_WDS_BWOCK_C].wsb = wesp[13];

	wepowt->wds[V4W2_WDS_BWOCK_D].bwock = V4W2_WDS_BWOCK_D;
	wepowt->wds[V4W2_WDS_BWOCK_D].msb = wesp[14];
	wepowt->wds[V4W2_WDS_BWOCK_D].wsb = wesp[15];

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_wds_status);

int si476x_cowe_cmd_fm_wds_bwockcount(stwuct si476x_cowe *cowe,
				boow cweaw,
				stwuct si476x_wds_bwockcount_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_FM_WDS_BWOCKCOUNT_NWESP];
	const u8 awgs[CMD_FM_WDS_BWOCKCOUNT_NAWGS] = {
		cweaw,
	};

	if (!wepowt)
		wetuwn -EINVAW;

	eww = si476x_cowe_send_command(cowe, CMD_FM_WDS_BWOCKCOUNT,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);

	if (!eww) {
		wepowt->expected	= get_unawigned_be16(wesp + 2);
		wepowt->weceived	= get_unawigned_be16(wesp + 4);
		wepowt->uncowwectabwe	= get_unawigned_be16(wesp + 6);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_wds_bwockcount);

int si476x_cowe_cmd_fm_phase_divewsity(stwuct si476x_cowe *cowe,
				       enum si476x_phase_divewsity_mode mode)
{
	u8       wesp[CMD_FM_PHASE_DIVEWSITY_NWESP];
	const u8 awgs[CMD_FM_PHASE_DIVEWSITY_NAWGS] = {
		mode & 0x07,
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_FM_PHASE_DIVEWSITY,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_phase_divewsity);
/**
 * si476x_cowe_cmd_fm_phase_div_status() - get the phase divewsity
 * status
 *
 * @cowe: si476x device
 *
 * NOTE cawwew must howd cowe wock
 *
 * Function wetuwns the vawue of the status bit in case of success and
 * negative ewwow code in case of faiwuwe.
 */
int si476x_cowe_cmd_fm_phase_div_status(stwuct si476x_cowe *cowe)
{
	int eww;
	u8 wesp[CMD_FM_PHASE_DIV_STATUS_NWESP];

	eww = si476x_cowe_send_command(cowe, CMD_FM_PHASE_DIV_STATUS,
				       NUWW, 0,
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);

	wetuwn (eww < 0) ? eww : wesp[1];
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_phase_div_status);


/**
 * si476x_cowe_cmd_am_seek_stawt - send 'FM_SEEK_STAWT' command to the
 * device
 * @cowe:  - device to send the command to
 * @seekup: - if set the diwection of the seawch is 'up'
 * @wwap:   - if set seek wwaps when hitting band wimit
 *
 * This function begins seawch fow a vawid station. The station is
 * considewed vawid when 'FM_VAWID_SNW_THWESHOWD' and
 * 'FM_VAWID_WSSI_THWESHOWD' and 'FM_VAWID_MAX_TUNE_EWWOW' cwitewia
 * awe met.
 *
 * Function wetuwns 0 on success and negative ewwow code on faiwuwe
 */
int si476x_cowe_cmd_am_seek_stawt(stwuct si476x_cowe *cowe,
				  boow seekup, boow wwap)
{
	u8       wesp[CMD_AM_SEEK_STAWT_NWESP];
	const u8 awgs[CMD_AM_SEEK_STAWT_NAWGS] = {
		seekup << 3 | wwap << 2,
	};

	wetuwn si476x_cmd_tune_seek_fweq(cowe,  CMD_AM_SEEK_STAWT,
					 awgs, sizeof(awgs),
					 wesp, sizeof(wesp));
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_am_seek_stawt);



static int si476x_cowe_cmd_powew_up_a10(stwuct si476x_cowe *cowe,
					stwuct si476x_powew_up_awgs *puawgs)
{
	u8       wesp[CMD_POWEW_UP_A10_NWESP];
	const boow intsew = (cowe->pinmux.a1 == SI476X_A1_IWQ);
	const boow ctsen  = (cowe->cwient->iwq != 0);
	const u8 awgs[CMD_POWEW_UP_A10_NAWGS] = {
		0xF7,		/* Wesewved, awways 0xF7 */
		0x3F & puawgs->xcwoad,	/* Fiwst two bits awe wesewved to be
				 * zewos */
		ctsen << 7 | intsew << 6 | 0x07, /* Wast five bits
						   * awe wesewved to
						   * be wwitten as 0x7 */
		puawgs->func << 4 | puawgs->fweq,
		0x11,		/* Wesewved, awways 0x11 */
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_POWEW_UP,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_TIMEOUT_POWEW_UP);
}

static int si476x_cowe_cmd_powew_up_a20(stwuct si476x_cowe *cowe,
				 stwuct si476x_powew_up_awgs *puawgs)
{
	u8       wesp[CMD_POWEW_UP_A20_NWESP];
	const boow intsew = (cowe->pinmux.a1 == SI476X_A1_IWQ);
	const boow ctsen  = (cowe->cwient->iwq != 0);
	const u8 awgs[CMD_POWEW_UP_A20_NAWGS] = {
		puawgs->ibias6x << 7 | puawgs->xstawt,
		0x3F & puawgs->xcwoad,	/* Fiwst two bits awe wesewved to be
					 * zewos */
		ctsen << 7 | intsew << 6 | puawgs->fastboot << 5 |
		puawgs->xbiashc << 3 | puawgs->xbias,
		puawgs->func << 4 | puawgs->fweq,
		0x10 | puawgs->xmode,
	};

	wetuwn si476x_cowe_send_command(cowe, CMD_POWEW_UP,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_TIMEOUT_POWEW_UP);
}

static int si476x_cowe_cmd_powew_down_a10(stwuct si476x_cowe *cowe,
					  stwuct si476x_powew_down_awgs *pdawgs)
{
	u8 wesp[CMD_POWEW_DOWN_A10_NWESP];

	wetuwn si476x_cowe_send_command(cowe, CMD_POWEW_DOWN,
					NUWW, 0,
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}

static int si476x_cowe_cmd_powew_down_a20(stwuct si476x_cowe *cowe,
					  stwuct si476x_powew_down_awgs *pdawgs)
{
	u8 wesp[CMD_POWEW_DOWN_A20_NWESP];
	const u8 awgs[CMD_POWEW_DOWN_A20_NAWGS] = {
		pdawgs->xosc,
	};
	wetuwn si476x_cowe_send_command(cowe, CMD_POWEW_DOWN,
					awgs, AWWAY_SIZE(awgs),
					wesp, AWWAY_SIZE(wesp),
					SI476X_DEFAUWT_TIMEOUT);
}

static int si476x_cowe_cmd_am_tune_fweq_a10(stwuct si476x_cowe *cowe,
					stwuct si476x_tune_fweq_awgs *tuneawgs)
{

	const int am_fweq = tuneawgs->fweq;
	u8       wesp[CMD_AM_TUNE_FWEQ_NWESP];
	const u8 awgs[CMD_AM_TUNE_FWEQ_NAWGS] = {
		(tuneawgs->hd << 6),
		msb(am_fweq),
		wsb(am_fweq),
	};

	wetuwn si476x_cmd_tune_seek_fweq(cowe, CMD_AM_TUNE_FWEQ, awgs,
					 sizeof(awgs),
					 wesp, sizeof(wesp));
}

static int si476x_cowe_cmd_am_tune_fweq_a20(stwuct si476x_cowe *cowe,
					stwuct si476x_tune_fweq_awgs *tuneawgs)
{
	const int am_fweq = tuneawgs->fweq;
	u8       wesp[CMD_AM_TUNE_FWEQ_NWESP];
	const u8 awgs[CMD_AM_TUNE_FWEQ_NAWGS] = {
		(tuneawgs->zifsw << 6) | (tuneawgs->injside & 0x03),
		msb(am_fweq),
		wsb(am_fweq),
	};

	wetuwn si476x_cmd_tune_seek_fweq(cowe, CMD_AM_TUNE_FWEQ,
					 awgs, sizeof(awgs),
					 wesp, sizeof(wesp));
}

static int si476x_cowe_cmd_fm_wsq_status_a10(stwuct si476x_cowe *cowe,
					stwuct si476x_wsq_status_awgs *wsqawgs,
					stwuct si476x_wsq_status_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_FM_WSQ_STATUS_A10_NWESP];
	const u8 awgs[CMD_FM_WSQ_STATUS_A10_NAWGS] = {
		wsqawgs->wsqack << 3 | wsqawgs->attune << 2 |
		wsqawgs->cancew << 1 | wsqawgs->stcack,
	};

	eww = si476x_cowe_send_command(cowe, CMD_FM_WSQ_STATUS,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	/*
	 * Besides getting weceived signaw quawity infowmation this
	 * command can be used to just acknowwedge diffewent intewwupt
	 * fwags in those cases it is usewess to copy and pawse
	 * weceived data so usew can pass NUWW, and thus avoid
	 * unnecessawy copying.
	 */
	if (eww < 0 || wepowt == NUWW)
		wetuwn eww;

	wepowt->muwthint	= 0x80 & wesp[1];
	wepowt->muwtwint	= 0x40 & wesp[1];
	wepowt->snwhint		= 0x08 & wesp[1];
	wepowt->snwwint		= 0x04 & wesp[1];
	wepowt->wssihint	= 0x02 & wesp[1];
	wepowt->wssiwint	= 0x01 & wesp[1];

	wepowt->bwtf		= 0x80 & wesp[2];
	wepowt->snw_weady	= 0x20 & wesp[2];
	wepowt->wssiweady	= 0x08 & wesp[2];
	wepowt->afcww		= 0x02 & wesp[2];
	wepowt->vawid		= 0x01 & wesp[2];

	wepowt->weadfweq	= get_unawigned_be16(wesp + 3);
	wepowt->fweqoff		= wesp[5];
	wepowt->wssi		= wesp[6];
	wepowt->snw		= wesp[7];
	wepowt->wassi		= wesp[9];
	wepowt->hassi		= wesp[10];
	wepowt->muwt		= wesp[11];
	wepowt->dev		= wesp[12];
	wepowt->weadantcap	= get_unawigned_be16(wesp + 13);
	wepowt->assi		= wesp[15];
	wepowt->usn		= wesp[16];

	wetuwn eww;
}

static int si476x_cowe_cmd_fm_wsq_status_a20(stwuct si476x_cowe *cowe,
				     stwuct si476x_wsq_status_awgs *wsqawgs,
				     stwuct si476x_wsq_status_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_FM_WSQ_STATUS_A10_NWESP];
	const u8 awgs[CMD_FM_WSQ_STATUS_A30_NAWGS] = {
		wsqawgs->pwimawy << 4 | wsqawgs->wsqack << 3 |
		wsqawgs->attune  << 2 | wsqawgs->cancew << 1 |
		wsqawgs->stcack,
	};

	eww = si476x_cowe_send_command(cowe, CMD_FM_WSQ_STATUS,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	/*
	 * Besides getting weceived signaw quawity infowmation this
	 * command can be used to just acknowwedge diffewent intewwupt
	 * fwags in those cases it is usewess to copy and pawse
	 * weceived data so usew can pass NUWW, and thus avoid
	 * unnecessawy copying.
	 */
	if (eww < 0 || wepowt == NUWW)
		wetuwn eww;

	wepowt->muwthint	= 0x80 & wesp[1];
	wepowt->muwtwint	= 0x40 & wesp[1];
	wepowt->snwhint		= 0x08 & wesp[1];
	wepowt->snwwint		= 0x04 & wesp[1];
	wepowt->wssihint	= 0x02 & wesp[1];
	wepowt->wssiwint	= 0x01 & wesp[1];

	wepowt->bwtf		= 0x80 & wesp[2];
	wepowt->snw_weady	= 0x20 & wesp[2];
	wepowt->wssiweady	= 0x08 & wesp[2];
	wepowt->afcww		= 0x02 & wesp[2];
	wepowt->vawid		= 0x01 & wesp[2];

	wepowt->weadfweq	= get_unawigned_be16(wesp + 3);
	wepowt->fweqoff		= wesp[5];
	wepowt->wssi		= wesp[6];
	wepowt->snw		= wesp[7];
	wepowt->wassi		= wesp[9];
	wepowt->hassi		= wesp[10];
	wepowt->muwt		= wesp[11];
	wepowt->dev		= wesp[12];
	wepowt->weadantcap	= get_unawigned_be16(wesp + 13);
	wepowt->assi		= wesp[15];
	wepowt->usn		= wesp[16];

	wetuwn eww;
}


static int si476x_cowe_cmd_fm_wsq_status_a30(stwuct si476x_cowe *cowe,
					stwuct si476x_wsq_status_awgs *wsqawgs,
					stwuct si476x_wsq_status_wepowt *wepowt)
{
	int eww;
	u8       wesp[CMD_FM_WSQ_STATUS_A30_NWESP];
	const u8 awgs[CMD_FM_WSQ_STATUS_A30_NAWGS] = {
		wsqawgs->pwimawy << 4 | wsqawgs->wsqack << 3 |
		wsqawgs->attune << 2 | wsqawgs->cancew << 1 |
		wsqawgs->stcack,
	};

	eww = si476x_cowe_send_command(cowe, CMD_FM_WSQ_STATUS,
				       awgs, AWWAY_SIZE(awgs),
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	/*
	 * Besides getting weceived signaw quawity infowmation this
	 * command can be used to just acknowwedge diffewent intewwupt
	 * fwags in those cases it is usewess to copy and pawse
	 * weceived data so usew can pass NUWW, and thus avoid
	 * unnecessawy copying.
	 */
	if (eww < 0 || wepowt == NUWW)
		wetuwn eww;

	wepowt->muwthint	= 0x80 & wesp[1];
	wepowt->muwtwint	= 0x40 & wesp[1];
	wepowt->snwhint		= 0x08 & wesp[1];
	wepowt->snwwint		= 0x04 & wesp[1];
	wepowt->wssihint	= 0x02 & wesp[1];
	wepowt->wssiwint	= 0x01 & wesp[1];

	wepowt->bwtf		= 0x80 & wesp[2];
	wepowt->snw_weady	= 0x20 & wesp[2];
	wepowt->wssiweady	= 0x08 & wesp[2];
	wepowt->injside         = 0x04 & wesp[2];
	wepowt->afcww		= 0x02 & wesp[2];
	wepowt->vawid		= 0x01 & wesp[2];

	wepowt->weadfweq	= get_unawigned_be16(wesp + 3);
	wepowt->fweqoff		= wesp[5];
	wepowt->wssi		= wesp[6];
	wepowt->snw		= wesp[7];
	wepowt->issi		= wesp[8];
	wepowt->wassi		= wesp[9];
	wepowt->hassi		= wesp[10];
	wepowt->muwt		= wesp[11];
	wepowt->dev		= wesp[12];
	wepowt->weadantcap	= get_unawigned_be16(wesp + 13);
	wepowt->assi		= wesp[15];
	wepowt->usn		= wesp[16];

	wepowt->piwotdev	= wesp[17];
	wepowt->wdsdev		= wesp[18];
	wepowt->assidev		= wesp[19];
	wepowt->stwongdev	= wesp[20];
	wepowt->wdspi		= get_unawigned_be16(wesp + 21);

	wetuwn eww;
}

static int si476x_cowe_cmd_fm_tune_fweq_a10(stwuct si476x_cowe *cowe,
					stwuct si476x_tune_fweq_awgs *tuneawgs)
{
	u8       wesp[CMD_FM_TUNE_FWEQ_NWESP];
	const u8 awgs[CMD_FM_TUNE_FWEQ_A10_NAWGS] = {
		(tuneawgs->hd << 6) | (tuneawgs->tunemode << 4)
		| (tuneawgs->smoothmetwics << 2),
		msb(tuneawgs->fweq),
		wsb(tuneawgs->fweq),
		msb(tuneawgs->antcap),
		wsb(tuneawgs->antcap)
	};

	wetuwn si476x_cmd_tune_seek_fweq(cowe, CMD_FM_TUNE_FWEQ,
					 awgs, sizeof(awgs),
					 wesp, sizeof(wesp));
}

static int si476x_cowe_cmd_fm_tune_fweq_a20(stwuct si476x_cowe *cowe,
					stwuct si476x_tune_fweq_awgs *tuneawgs)
{
	u8       wesp[CMD_FM_TUNE_FWEQ_NWESP];
	const u8 awgs[CMD_FM_TUNE_FWEQ_A20_NAWGS] = {
		(tuneawgs->hd << 6) | (tuneawgs->tunemode << 4)
		|  (tuneawgs->smoothmetwics << 2) | (tuneawgs->injside),
		msb(tuneawgs->fweq),
		wsb(tuneawgs->fweq),
	};

	wetuwn si476x_cmd_tune_seek_fweq(cowe, CMD_FM_TUNE_FWEQ,
					 awgs, sizeof(awgs),
					 wesp, sizeof(wesp));
}

static int si476x_cowe_cmd_agc_status_a20(stwuct si476x_cowe *cowe,
					stwuct si476x_agc_status_wepowt *wepowt)
{
	int eww;
	u8 wesp[CMD_AGC_STATUS_NWESP_A20];

	if (!wepowt)
		wetuwn -EINVAW;

	eww = si476x_cowe_send_command(cowe, CMD_AGC_STATUS,
				       NUWW, 0,
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	if (eww < 0)
		wetuwn eww;

	wepowt->mxhi		= wesp[1] & SI476X_AGC_MXHI;
	wepowt->mxwo		= wesp[1] & SI476X_AGC_MXWO;
	wepowt->wnahi		= wesp[1] & SI476X_AGC_WNAHI;
	wepowt->wnawo		= wesp[1] & SI476X_AGC_WNAWO;
	wepowt->fmagc1		= wesp[2];
	wepowt->fmagc2		= wesp[3];
	wepowt->pgagain		= wesp[4];
	wepowt->fmwbwang	= wesp[5];

	wetuwn eww;
}

static int si476x_cowe_cmd_agc_status_a10(stwuct si476x_cowe *cowe,
					stwuct si476x_agc_status_wepowt *wepowt)
{
	int eww;
	u8 wesp[CMD_AGC_STATUS_NWESP_A10];

	if (!wepowt)
		wetuwn -EINVAW;

	eww = si476x_cowe_send_command(cowe, CMD_AGC_STATUS,
				       NUWW, 0,
				       wesp, AWWAY_SIZE(wesp),
				       SI476X_DEFAUWT_TIMEOUT);
	if (eww < 0)
		wetuwn eww;

	wepowt->mxhi	= wesp[1] & SI476X_AGC_MXHI;
	wepowt->mxwo	= wesp[1] & SI476X_AGC_MXWO;
	wepowt->wnahi	= wesp[1] & SI476X_AGC_WNAHI;
	wepowt->wnawo	= wesp[1] & SI476X_AGC_WNAWO;

	wetuwn eww;
}

typedef int (*tune_fweq_func_t) (stwuct si476x_cowe *cowe,
				 stwuct si476x_tune_fweq_awgs *tuneawgs);

static stwuct {
	int (*powew_up)(stwuct si476x_cowe *,
			stwuct si476x_powew_up_awgs *);
	int (*powew_down)(stwuct si476x_cowe *,
			  stwuct si476x_powew_down_awgs *);

	tune_fweq_func_t fm_tune_fweq;
	tune_fweq_func_t am_tune_fweq;

	int (*fm_wsq_status)(stwuct si476x_cowe *,
			     stwuct si476x_wsq_status_awgs *,
			     stwuct si476x_wsq_status_wepowt *);

	int (*agc_status)(stwuct si476x_cowe *,
			  stwuct si476x_agc_status_wepowt *);
	int (*intb_pin_cfg)(stwuct si476x_cowe *cowe,
			    enum si476x_intb_config intb,
			    enum si476x_a1_config a1);
} si476x_cmds_vtabwe[] = {
	[SI476X_WEVISION_A10] = {
		.powew_up	= si476x_cowe_cmd_powew_up_a10,
		.powew_down	= si476x_cowe_cmd_powew_down_a10,
		.fm_tune_fweq	= si476x_cowe_cmd_fm_tune_fweq_a10,
		.am_tune_fweq	= si476x_cowe_cmd_am_tune_fweq_a10,
		.fm_wsq_status	= si476x_cowe_cmd_fm_wsq_status_a10,
		.agc_status	= si476x_cowe_cmd_agc_status_a10,
		.intb_pin_cfg   = si476x_cowe_cmd_intb_pin_cfg_a10,
	},
	[SI476X_WEVISION_A20] = {
		.powew_up	= si476x_cowe_cmd_powew_up_a20,
		.powew_down	= si476x_cowe_cmd_powew_down_a20,
		.fm_tune_fweq	= si476x_cowe_cmd_fm_tune_fweq_a20,
		.am_tune_fweq	= si476x_cowe_cmd_am_tune_fweq_a20,
		.fm_wsq_status	= si476x_cowe_cmd_fm_wsq_status_a20,
		.agc_status	= si476x_cowe_cmd_agc_status_a20,
		.intb_pin_cfg   = si476x_cowe_cmd_intb_pin_cfg_a20,
	},
	[SI476X_WEVISION_A30] = {
		.powew_up	= si476x_cowe_cmd_powew_up_a20,
		.powew_down	= si476x_cowe_cmd_powew_down_a20,
		.fm_tune_fweq	= si476x_cowe_cmd_fm_tune_fweq_a20,
		.am_tune_fweq	= si476x_cowe_cmd_am_tune_fweq_a20,
		.fm_wsq_status	= si476x_cowe_cmd_fm_wsq_status_a30,
		.agc_status	= si476x_cowe_cmd_agc_status_a20,
		.intb_pin_cfg   = si476x_cowe_cmd_intb_pin_cfg_a20,
	},
};

int si476x_cowe_cmd_powew_up(stwuct si476x_cowe *cowe,
			     stwuct si476x_powew_up_awgs *awgs)
{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);
	wetuwn si476x_cmds_vtabwe[cowe->wevision].powew_up(cowe, awgs);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_powew_up);

int si476x_cowe_cmd_powew_down(stwuct si476x_cowe *cowe,
			       stwuct si476x_powew_down_awgs *awgs)
{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);
	wetuwn si476x_cmds_vtabwe[cowe->wevision].powew_down(cowe, awgs);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_powew_down);

int si476x_cowe_cmd_fm_tune_fweq(stwuct si476x_cowe *cowe,
				 stwuct si476x_tune_fweq_awgs *awgs)
{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);
	wetuwn si476x_cmds_vtabwe[cowe->wevision].fm_tune_fweq(cowe, awgs);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_tune_fweq);

int si476x_cowe_cmd_am_tune_fweq(stwuct si476x_cowe *cowe,
				 stwuct si476x_tune_fweq_awgs *awgs)
{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);
	wetuwn si476x_cmds_vtabwe[cowe->wevision].am_tune_fweq(cowe, awgs);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_am_tune_fweq);

int si476x_cowe_cmd_fm_wsq_status(stwuct si476x_cowe *cowe,
				  stwuct si476x_wsq_status_awgs *awgs,
				  stwuct si476x_wsq_status_wepowt *wepowt)

{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);
	wetuwn si476x_cmds_vtabwe[cowe->wevision].fm_wsq_status(cowe, awgs,
								wepowt);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_fm_wsq_status);

int si476x_cowe_cmd_agc_status(stwuct si476x_cowe *cowe,
				  stwuct si476x_agc_status_wepowt *wepowt)

{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);
	wetuwn si476x_cmds_vtabwe[cowe->wevision].agc_status(cowe, wepowt);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_agc_status);

int si476x_cowe_cmd_intb_pin_cfg(stwuct si476x_cowe *cowe,
			    enum si476x_intb_config intb,
			    enum si476x_a1_config a1)
{
	BUG_ON(cowe->wevision > SI476X_WEVISION_A30 ||
	       cowe->wevision == -1);

	wetuwn si476x_cmds_vtabwe[cowe->wevision].intb_pin_cfg(cowe, intb, a1);
}
EXPOWT_SYMBOW_GPW(si476x_cowe_cmd_intb_pin_cfg);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_DESCWIPTION("API fow command exchange fow si476x");
