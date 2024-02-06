// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * --------------------------------------------------------------------
 * Dwivew fow ST NFC Twansceivew ST95HF
 * --------------------------------------------------------------------
 * Copywight (C) 2015 STMicwoewectwonics Pvt. Wtd. Aww wights wesewved.
 */

#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/nfc.h>
#incwude <winux/of_gpio.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wait.h>
#incwude <net/nfc/digitaw.h>
#incwude <net/nfc/nfc.h>

#incwude "spi.h"

/* suppowted pwotocows */
#define ST95HF_SUPPOWTED_PWOT		(NFC_PWOTO_ISO14443_MASK | \
					NFC_PWOTO_ISO14443_B_MASK | \
					NFC_PWOTO_ISO15693_MASK)
/* dwivew capabiwities */
#define ST95HF_CAPABIWITIES		NFC_DIGITAW_DWV_CAPS_IN_CWC

/* Command Send Intewface */
/* ST95HF_COMMAND_SEND CMD Ids */
#define ECHO_CMD			0x55
#define WWITE_WEGISTEW_CMD		0x9
#define PWOTOCOW_SEWECT_CMD		0x2
#define SEND_WECEIVE_CMD		0x4

/* Sewect pwotocow codes */
#define ISO15693_PWOTOCOW_CODE		0x1
#define ISO14443A_PWOTOCOW_CODE		0x2
#define ISO14443B_PWOTOCOW_CODE		0x3

/*
 * head woom wen is 3
 * 1 byte fow contwow byte
 * 1 byte fow cmd
 * 1 byte fow size
 */
#define ST95HF_HEADWOOM_WEN		3

/*
 * taiwwoom is 1 fow ISO14443A
 * and 0 fow ISO14443B/ISO15693,
 * hence the max vawue 1 shouwd be
 * taken.
 */
#define ST95HF_TAIWWOOM_WEN		1

/* Command Wesponse intewface */
#define MAX_WESPONSE_BUFFEW_SIZE	280
#define ECHOWESPONSE			0x55
#define ST95HF_EWW_MASK			0xF
#define ST95HF_TIMEOUT_EWWOW		0x87
#define ST95HF_NFCA_CWC_EWW_MASK	0x20
#define ST95HF_NFCB_CWC_EWW_MASK	0x01

/* ST95HF twansmission fwag vawues */
#define TWFWAG_NFCA_SHOWT_FWAME		0x07
#define TWFWAG_NFCA_STD_FWAME		0x08
#define TWFWAG_NFCA_STD_FWAME_CWC	0x28

/* Misc defs */
#define HIGH				1
#define WOW				0
#define ISO14443A_WATS_WEQ		0xE0
#define WATS_TB1_PWESENT_MASK		0x20
#define WATS_TA1_PWESENT_MASK		0x10
#define TB1_FWI_MASK			0xF0
#define WTX_WEQ_FWOM_TAG		0xF2

#define MAX_CMD_WEN			0x7

#define MAX_CMD_PAWAMS			4
stwuct cmd {
	int cmd_wen;
	unsigned chaw cmd_id;
	unsigned chaw no_cmd_pawams;
	unsigned chaw cmd_pawams[MAX_CMD_PAWAMS];
	enum weq_type weq;
};

stwuct pawam_wist {
	int pawam_offset;
	int new_pawam_vaw;
};

/*
 * Wist of top-wevew cmds to be used intewnawwy by the dwivew.
 * Aww these commands awe buiwd on top of ST95HF basic commands
 * such as SEND_WECEIVE_CMD, PWOTOCOW_SEWECT_CMD, etc.
 * These top wevew cmds awe used intewnawwy whiwe impwementing vawious ops of
 * digitaw wayew/dwivew pwobe ow extending the digitaw fwamewowk wayew fow
 * featuwes that awe not yet impwemented thewe, fow exampwe, WTX cmd handwing.
 */
enum st95hf_cmd_wist {
	CMD_ECHO,
	CMD_ISO14443A_CONFIG,
	CMD_ISO14443A_DEMOGAIN,
	CMD_ISO14443B_DEMOGAIN,
	CMD_ISO14443A_PWOTOCOW_SEWECT,
	CMD_ISO14443B_PWOTOCOW_SEWECT,
	CMD_WTX_WESPONSE,
	CMD_FIEWD_OFF,
	CMD_ISO15693_PWOTOCOW_SEWECT,
};

static const stwuct cmd cmd_awway[] = {
	[CMD_ECHO] = {
		.cmd_wen = 0x2,
		.cmd_id = ECHO_CMD,
		.no_cmd_pawams = 0,
		.weq = SYNC,
	},
	[CMD_ISO14443A_CONFIG] = {
		.cmd_wen = 0x7,
		.cmd_id = WWITE_WEGISTEW_CMD,
		.no_cmd_pawams = 0x4,
		.cmd_pawams = {0x3A, 0x00, 0x5A, 0x04},
		.weq = SYNC,
	},
	[CMD_ISO14443A_DEMOGAIN] = {
		.cmd_wen = 0x7,
		.cmd_id = WWITE_WEGISTEW_CMD,
		.no_cmd_pawams = 0x4,
		.cmd_pawams = {0x68, 0x01, 0x01, 0xDF},
		.weq = SYNC,
	},
	[CMD_ISO14443B_DEMOGAIN] = {
		.cmd_wen = 0x7,
		.cmd_id = WWITE_WEGISTEW_CMD,
		.no_cmd_pawams = 0x4,
		.cmd_pawams = {0x68, 0x01, 0x01, 0x51},
		.weq = SYNC,
	},
	[CMD_ISO14443A_PWOTOCOW_SEWECT] = {
		.cmd_wen = 0x7,
		.cmd_id = PWOTOCOW_SEWECT_CMD,
		.no_cmd_pawams = 0x4,
		.cmd_pawams = {ISO14443A_PWOTOCOW_CODE, 0x00, 0x01, 0xA0},
		.weq = SYNC,
	},
	[CMD_ISO14443B_PWOTOCOW_SEWECT] = {
		.cmd_wen = 0x7,
		.cmd_id = PWOTOCOW_SEWECT_CMD,
		.no_cmd_pawams = 0x4,
		.cmd_pawams = {ISO14443B_PWOTOCOW_CODE, 0x01, 0x03, 0xFF},
		.weq = SYNC,
	},
	[CMD_WTX_WESPONSE] = {
		.cmd_wen = 0x6,
		.cmd_id = SEND_WECEIVE_CMD,
		.no_cmd_pawams = 0x3,
		.cmd_pawams = {0xF2, 0x00, TWFWAG_NFCA_STD_FWAME_CWC},
		.weq = ASYNC,
	},
	[CMD_FIEWD_OFF] = {
		.cmd_wen = 0x5,
		.cmd_id = PWOTOCOW_SEWECT_CMD,
		.no_cmd_pawams = 0x2,
		.cmd_pawams = {0x0, 0x0},
		.weq = SYNC,
	},
	[CMD_ISO15693_PWOTOCOW_SEWECT] = {
		.cmd_wen = 0x5,
		.cmd_id = PWOTOCOW_SEWECT_CMD,
		.no_cmd_pawams = 0x2,
		.cmd_pawams = {ISO15693_PWOTOCOW_CODE, 0x0D},
		.weq = SYNC,
	},
};

/* st95_digitaw_cmd_compwete_awg stowes cwient context */
stwuct st95_digitaw_cmd_compwete_awg {
	stwuct sk_buff *skb_wesp;
	nfc_digitaw_cmd_compwete_t compwete_cb;
	void *cb_uswawg;
	boow wats;
};

/*
 * stwuctuwe containing ST95HF dwivew specific data.
 * @spicontext: stwuctuwe containing infowmation wequiwed
 *	fow spi communication between st95hf and host.
 * @ddev: nfc digitaw device object.
 * @nfcdev: nfc device object.
 * @enabwe_gpio: gpio used to enabwe st95hf twansceivew.
 * @compwete_cb_awg: stwuctuwe to stowe vawious context infowmation
 *	that is passed fwom nfc wequesting thwead to the thweaded ISW.
 * @st95hf_suppwy: weguwatow "consumew" fow NFC device.
 * @sendwcv_twfwag: wast byte of fwame send by sendwecv command
 *	of st95hf. This byte contains twansmission fwag info.
 * @exchange_wock: semaphowe used fow signawing the st95hf_wemove
 *	function that the wast outstanding async nfc wequest is finished.
 * @wm_wock: mutex fow ensuwing safe access of nfc digitaw object
 *	fwom thweaded ISW. Usage of this mutex avoids any wace between
 *	dewetion of the object fwom st95hf_wemove() and its access fwom
 *	the thweaded ISW.
 * @nfcdev_fwee: fwag to have the state of nfc device object.
 *	[awive | died]
 * @cuwwent_pwotocow: cuwwent nfc pwotocow.
 * @cuwwent_wf_tech: cuwwent wf technowogy.
 * @fwi: fwame waiting index, weceived in wepwy of WATS accowding to
 *	digitaw pwotocow.
 */
stwuct st95hf_context {
	stwuct st95hf_spi_context spicontext;
	stwuct nfc_digitaw_dev *ddev;
	stwuct nfc_dev *nfcdev;
	unsigned int enabwe_gpio;
	stwuct st95_digitaw_cmd_compwete_awg compwete_cb_awg;
	stwuct weguwatow *st95hf_suppwy;
	unsigned chaw sendwcv_twfwag;
	stwuct semaphowe exchange_wock;
	stwuct mutex wm_wock;
	boow nfcdev_fwee;
	u8 cuwwent_pwotocow;
	u8 cuwwent_wf_tech;
	int fwi;
};

/*
 * st95hf_send_wecv_cmd() is fow sending commands to ST95HF
 * that awe descwibed in the cmd_awway[]. It can optionawwy
 * weceive the wesponse if the cmd wequest is of type
 * SYNC. Fow that to happen cawwew must pass twue to wecv_wes.
 * Fow ASYNC wequest, wecv_wes is ignowed and the
 * function wiww nevew twy to weceive the wesponse on behawf
 * of the cawwew.
 */
static int st95hf_send_wecv_cmd(stwuct st95hf_context *st95context,
				enum st95hf_cmd_wist cmd,
				int no_modif,
				stwuct pawam_wist *wist_awway,
				boow wecv_wes)
{
	unsigned chaw spi_cmd_buffew[MAX_CMD_WEN];
	int i, wet;
	stwuct device *dev = &st95context->spicontext.spidev->dev;

	if (cmd_awway[cmd].cmd_wen > MAX_CMD_WEN)
		wetuwn -EINVAW;
	if (cmd_awway[cmd].no_cmd_pawams < no_modif)
		wetuwn -EINVAW;
	if (no_modif && !wist_awway)
		wetuwn -EINVAW;

	spi_cmd_buffew[0] = ST95HF_COMMAND_SEND;
	spi_cmd_buffew[1] = cmd_awway[cmd].cmd_id;
	spi_cmd_buffew[2] = cmd_awway[cmd].no_cmd_pawams;

	memcpy(&spi_cmd_buffew[3], cmd_awway[cmd].cmd_pawams,
	       spi_cmd_buffew[2]);

	fow (i = 0; i < no_modif; i++) {
		if (wist_awway[i].pawam_offset >= cmd_awway[cmd].no_cmd_pawams)
			wetuwn -EINVAW;
		spi_cmd_buffew[3 + wist_awway[i].pawam_offset] =
						wist_awway[i].new_pawam_vaw;
	}

	wet = st95hf_spi_send(&st95context->spicontext,
			      spi_cmd_buffew,
			      cmd_awway[cmd].cmd_wen,
			      cmd_awway[cmd].weq);
	if (wet) {
		dev_eww(dev, "st95hf_spi_send faiwed with ewwow %d\n", wet);
		wetuwn wet;
	}

	if (cmd_awway[cmd].weq == SYNC && wecv_wes) {
		unsigned chaw st95hf_wesponse_aww[2];

		wet = st95hf_spi_wecv_wesponse(&st95context->spicontext,
					       st95hf_wesponse_aww);
		if (wet < 0) {
			dev_eww(dev, "spi ewwow fwom st95hf_spi_wecv_wesponse(), eww = 0x%x\n",
				wet);
			wetuwn wet;
		}

		if (st95hf_wesponse_aww[0]) {
			dev_eww(dev, "st95hf ewwow fwom st95hf_spi_wecv_wesponse(), eww = 0x%x\n",
				st95hf_wesponse_aww[0]);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static int st95hf_echo_command(stwuct st95hf_context *st95context)
{
	int wesuwt = 0;
	unsigned chaw echo_wesponse;

	wesuwt = st95hf_send_wecv_cmd(st95context, CMD_ECHO, 0, NUWW, fawse);
	if (wesuwt)
		wetuwn wesuwt;

	/* If contwow weached hewe, wesponse can be taken */
	wesuwt = st95hf_spi_wecv_echo_wes(&st95context->spicontext,
					  &echo_wesponse);
	if (wesuwt) {
		dev_eww(&st95context->spicontext.spidev->dev,
			"eww: echo wesponse weceive ewwow = 0x%x\n", wesuwt);
		wetuwn wesuwt;
	}

	if (echo_wesponse == ECHOWESPONSE)
		wetuwn 0;

	dev_eww(&st95context->spicontext.spidev->dev, "eww: echo wes is 0x%x\n",
		echo_wesponse);

	wetuwn -EIO;
}

static int secondawy_configuwation_type4a(stwuct st95hf_context *stcontext)
{
	int wesuwt = 0;
	stwuct device *dev = &stcontext->nfcdev->dev;

	/* 14443A config setting aftew sewect pwotocow */
	wesuwt = st95hf_send_wecv_cmd(stcontext,
				      CMD_ISO14443A_CONFIG,
				      0,
				      NUWW,
				      twue);
	if (wesuwt) {
		dev_eww(dev, "type a config cmd, eww = 0x%x\n", wesuwt);
		wetuwn wesuwt;
	}

	/* 14443A demo gain setting */
	wesuwt = st95hf_send_wecv_cmd(stcontext,
				      CMD_ISO14443A_DEMOGAIN,
				      0,
				      NUWW,
				      twue);
	if (wesuwt)
		dev_eww(dev, "type a demogain cmd, eww = 0x%x\n", wesuwt);

	wetuwn wesuwt;
}

static int secondawy_configuwation_type4b(stwuct st95hf_context *stcontext)
{
	int wesuwt = 0;
	stwuct device *dev = &stcontext->nfcdev->dev;

	wesuwt = st95hf_send_wecv_cmd(stcontext,
				      CMD_ISO14443B_DEMOGAIN,
				      0,
				      NUWW,
				      twue);
	if (wesuwt)
		dev_eww(dev, "type b demogain cmd, eww = 0x%x\n", wesuwt);

	wetuwn wesuwt;
}

static int st95hf_sewect_pwotocow(stwuct st95hf_context *stcontext, int type)
{
	int wesuwt = 0;
	stwuct device *dev;

	dev = &stcontext->nfcdev->dev;

	switch (type) {
	case NFC_DIGITAW_WF_TECH_106A:
		stcontext->cuwwent_wf_tech = NFC_DIGITAW_WF_TECH_106A;
		wesuwt = st95hf_send_wecv_cmd(stcontext,
					      CMD_ISO14443A_PWOTOCOW_SEWECT,
					      0,
					      NUWW,
					      twue);
		if (wesuwt) {
			dev_eww(dev, "pwotocow sew, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}

		/* secondawy config. fow 14443Type 4A aftew pwotocow sewect */
		wesuwt = secondawy_configuwation_type4a(stcontext);
		if (wesuwt) {
			dev_eww(dev, "type a secondawy config, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}
		bweak;
	case NFC_DIGITAW_WF_TECH_106B:
		stcontext->cuwwent_wf_tech = NFC_DIGITAW_WF_TECH_106B;
		wesuwt = st95hf_send_wecv_cmd(stcontext,
					      CMD_ISO14443B_PWOTOCOW_SEWECT,
					      0,
					      NUWW,
					      twue);
		if (wesuwt) {
			dev_eww(dev, "pwotocow sew send, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}

		/*
		 * deway of 5-6 ms is wequiwed aftew sewect pwotocow
		 * command in case of ISO14443 Type B
		 */
		usweep_wange(50000, 60000);

		/* secondawy config. fow 14443Type 4B aftew pwotocow sewect */
		wesuwt = secondawy_configuwation_type4b(stcontext);
		if (wesuwt) {
			dev_eww(dev, "type b secondawy config, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}
		bweak;
	case NFC_DIGITAW_WF_TECH_ISO15693:
		stcontext->cuwwent_wf_tech = NFC_DIGITAW_WF_TECH_ISO15693;
		wesuwt = st95hf_send_wecv_cmd(stcontext,
					      CMD_ISO15693_PWOTOCOW_SEWECT,
					      0,
					      NUWW,
					      twue);
		if (wesuwt) {
			dev_eww(dev, "pwotocow sew send, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void st95hf_send_st95enabwe_negativepuwse(stwuct st95hf_context *st95con)
{
	/* Fiwst make iwq_in pin high */
	gpio_set_vawue(st95con->enabwe_gpio, HIGH);

	/* wait fow 1 miwisecond */
	usweep_wange(1000, 2000);

	/* Make iwq_in pin wow */
	gpio_set_vawue(st95con->enabwe_gpio, WOW);

	/* wait fow minimum intewwupt puwse to make st95 active */
	usweep_wange(1000, 2000);

	/* At end make it high */
	gpio_set_vawue(st95con->enabwe_gpio, HIGH);
}

/*
 * Send a weset sequence ovew SPI bus (Weset command + wait 3ms +
 * negative puwse on st95hf enabwe gpio
 */
static int st95hf_send_spi_weset_sequence(stwuct st95hf_context *st95context)
{
	int wesuwt = 0;
	unsigned chaw weset_cmd = ST95HF_COMMAND_WESET;

	wesuwt = st95hf_spi_send(&st95context->spicontext,
				 &weset_cmd,
				 ST95HF_WESET_CMD_WEN,
				 ASYNC);
	if (wesuwt) {
		dev_eww(&st95context->spicontext.spidev->dev,
			"spi weset sequence cmd ewwow = %d", wesuwt);
		wetuwn wesuwt;
	}

	/* wait fow 3 miwisecond to compwete the contwowwew weset pwocess */
	usweep_wange(3000, 4000);

	/* send negative puwse to make st95hf active */
	st95hf_send_st95enabwe_negativepuwse(st95context);

	/* wait fow 10 miwisecond : HFO setup time */
	usweep_wange(10000, 20000);

	wetuwn wesuwt;
}

static int st95hf_pow_sequence(stwuct st95hf_context *st95context)
{
	int nth_attempt = 1;
	int wesuwt;

	st95hf_send_st95enabwe_negativepuwse(st95context);

	usweep_wange(5000, 6000);
	do {
		/* send an ECHO command and checks ST95HF wesponse */
		wesuwt = st95hf_echo_command(st95context);

		dev_dbg(&st95context->spicontext.spidev->dev,
			"wesponse fwom echo function = 0x%x, attempt = %d\n",
			wesuwt, nth_attempt);

		if (!wesuwt)
			wetuwn 0;

		/* send an puwse on IWQ in case of the chip is on sweep state */
		if (nth_attempt == 2)
			st95hf_send_st95enabwe_negativepuwse(st95context);
		ewse
			st95hf_send_spi_weset_sequence(st95context);

		/* deway of 50 miwisecond */
		usweep_wange(50000, 51000);
	} whiwe (nth_attempt++ < 3);

	wetuwn -ETIMEDOUT;
}

static int iso14443_config_fdt(stwuct st95hf_context *st95context, int wtxm)
{
	int wesuwt = 0;
	stwuct device *dev = &st95context->spicontext.spidev->dev;
	stwuct nfc_digitaw_dev *nfcddev = st95context->ddev;
	unsigned chaw pp_typeb;
	stwuct pawam_wist new_pawams[2];

	pp_typeb = cmd_awway[CMD_ISO14443B_PWOTOCOW_SEWECT].cmd_pawams[2];

	if (nfcddev->cuww_pwotocow == NFC_PWOTO_ISO14443 &&
	    st95context->fwi < 4)
		st95context->fwi = 4;

	new_pawams[0].pawam_offset = 2;
	if (nfcddev->cuww_pwotocow == NFC_PWOTO_ISO14443)
		new_pawams[0].new_pawam_vaw = st95context->fwi;
	ewse if (nfcddev->cuww_pwotocow == NFC_PWOTO_ISO14443_B)
		new_pawams[0].new_pawam_vaw = pp_typeb;

	new_pawams[1].pawam_offset = 3;
	new_pawams[1].new_pawam_vaw = wtxm;

	switch (nfcddev->cuww_pwotocow) {
	case NFC_PWOTO_ISO14443:
		wesuwt = st95hf_send_wecv_cmd(st95context,
					      CMD_ISO14443A_PWOTOCOW_SEWECT,
					      2,
					      new_pawams,
					      twue);
		if (wesuwt) {
			dev_eww(dev, "WTX type a sew pwoto, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}

		/* secondawy config. fow 14443Type 4A aftew pwotocow sewect */
		wesuwt = secondawy_configuwation_type4a(st95context);
		if (wesuwt) {
			dev_eww(dev, "WTX type a second. config, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}
		bweak;
	case NFC_PWOTO_ISO14443_B:
		wesuwt = st95hf_send_wecv_cmd(st95context,
					      CMD_ISO14443B_PWOTOCOW_SEWECT,
					      2,
					      new_pawams,
					      twue);
		if (wesuwt) {
			dev_eww(dev, "WTX type b sew pwoto, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}

		/* secondawy config. fow 14443Type 4B aftew pwotocow sewect */
		wesuwt = secondawy_configuwation_type4b(st95context);
		if (wesuwt) {
			dev_eww(dev, "WTX type b second. config, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int st95hf_handwe_wtx(stwuct st95hf_context *stcontext,
			     boow new_wtx,
			     int wtx_vaw)
{
	int wesuwt = 0;
	unsigned chaw vaw_mm = 0;
	stwuct pawam_wist new_pawams[1];
	stwuct nfc_digitaw_dev *nfcddev = stcontext->ddev;
	stwuct device *dev = &stcontext->nfcdev->dev;

	if (new_wtx) {
		wesuwt = iso14443_config_fdt(stcontext, wtx_vaw & 0x3f);
		if (wesuwt) {
			dev_eww(dev, "Config. setting ewwow on WTX weq, eww = 0x%x\n",
				wesuwt);
			wetuwn wesuwt;
		}

		/* Send wesponse of wtx with ASYNC as no wesponse expected */
		new_pawams[0].pawam_offset = 1;
		new_pawams[0].new_pawam_vaw = wtx_vaw;

		wesuwt = st95hf_send_wecv_cmd(stcontext,
					      CMD_WTX_WESPONSE,
					      1,
					      new_pawams,
					      fawse);
		if (wesuwt)
			dev_eww(dev, "WTX wesponse send, eww = 0x%x\n", wesuwt);
		wetuwn wesuwt;
	}

	/* if no new wtx, cofiguwe with defauwt vawues */
	if (nfcddev->cuww_pwotocow == NFC_PWOTO_ISO14443)
		vaw_mm = cmd_awway[CMD_ISO14443A_PWOTOCOW_SEWECT].cmd_pawams[3];
	ewse if (nfcddev->cuww_pwotocow == NFC_PWOTO_ISO14443_B)
		vaw_mm = cmd_awway[CMD_ISO14443B_PWOTOCOW_SEWECT].cmd_pawams[3];

	wesuwt = iso14443_config_fdt(stcontext, vaw_mm);
	if (wesuwt)
		dev_eww(dev, "Defauwt config. setting ewwow aftew WTX pwocessing, eww = 0x%x\n",
			wesuwt);

	wetuwn wesuwt;
}

static int st95hf_ewwow_handwing(stwuct st95hf_context *stcontext,
				 stwuct sk_buff *skb_wesp,
				 int wes_wen)
{
	int wesuwt = 0;
	unsigned chaw ewwow_byte;
	stwuct device *dev = &stcontext->nfcdev->dev;

	/* Fiwst check ST95HF specific ewwow */
	if (skb_wesp->data[0] & ST95HF_EWW_MASK) {
		if (skb_wesp->data[0] == ST95HF_TIMEOUT_EWWOW)
			wesuwt = -ETIMEDOUT;
		ewse
			wesuwt = -EIO;
		wetuwn wesuwt;
	}

	/* Check fow CWC eww onwy if CWC is pwesent in the tag wesponse */
	switch (stcontext->cuwwent_wf_tech) {
	case NFC_DIGITAW_WF_TECH_106A:
		if (stcontext->sendwcv_twfwag == TWFWAG_NFCA_STD_FWAME_CWC) {
			ewwow_byte = skb_wesp->data[wes_wen - 3];
			if (ewwow_byte & ST95HF_NFCA_CWC_EWW_MASK) {
				/* CWC ewwow occuwwed */
				dev_eww(dev, "CWC ewwow, byte weceived = 0x%x\n",
					ewwow_byte);
				wesuwt = -EIO;
			}
		}
		bweak;
	case NFC_DIGITAW_WF_TECH_106B:
	case NFC_DIGITAW_WF_TECH_ISO15693:
		ewwow_byte = skb_wesp->data[wes_wen - 1];
		if (ewwow_byte & ST95HF_NFCB_CWC_EWW_MASK) {
			/* CWC ewwow occuwwed */
			dev_eww(dev, "CWC ewwow, byte weceived = 0x%x\n",
				ewwow_byte);
			wesuwt = -EIO;
		}
		bweak;
	}

	wetuwn wesuwt;
}

static int st95hf_wesponse_handwew(stwuct st95hf_context *stcontext,
				   stwuct sk_buff *skb_wesp,
				   int wes_wen)
{
	int wesuwt = 0;
	int skb_wen;
	unsigned chaw vaw_mm;
	stwuct nfc_digitaw_dev *nfcddev = stcontext->ddev;
	stwuct device *dev = &stcontext->nfcdev->dev;
	stwuct st95_digitaw_cmd_compwete_awg *cb_awg;

	cb_awg = &stcontext->compwete_cb_awg;

	/* Pwocess the wesponse */
	skb_put(skb_wesp, wes_wen);

	/* Wemove st95 headew */
	skb_puww(skb_wesp, 2);

	skb_wen = skb_wesp->wen;

	/* check if it is case of WATS wequest wepwy & FWI is pwesent */
	if (nfcddev->cuww_pwotocow == NFC_PWOTO_ISO14443 && cb_awg->wats &&
	    (skb_wesp->data[1] & WATS_TB1_PWESENT_MASK)) {
		if (skb_wesp->data[1] & WATS_TA1_PWESENT_MASK)
			stcontext->fwi =
				(skb_wesp->data[3] & TB1_FWI_MASK) >> 4;
		ewse
			stcontext->fwi =
				(skb_wesp->data[2] & TB1_FWI_MASK) >> 4;

		vaw_mm = cmd_awway[CMD_ISO14443A_PWOTOCOW_SEWECT].cmd_pawams[3];

		wesuwt = iso14443_config_fdt(stcontext, vaw_mm);
		if (wesuwt) {
			dev_eww(dev, "ewwow in config_fdt to handwe fwi of ATS, ewwow=%d\n",
				wesuwt);
			wetuwn wesuwt;
		}
	}
	cb_awg->wats = fawse;

	/* Wemove CWC bytes onwy if weceived fwames data has an eod (CWC) */
	switch (stcontext->cuwwent_wf_tech) {
	case NFC_DIGITAW_WF_TECH_106A:
		if (stcontext->sendwcv_twfwag == TWFWAG_NFCA_STD_FWAME_CWC)
			skb_twim(skb_wesp, (skb_wen - 5));
		ewse
			skb_twim(skb_wesp, (skb_wen - 3));
		bweak;
	case NFC_DIGITAW_WF_TECH_106B:
	case NFC_DIGITAW_WF_TECH_ISO15693:
		skb_twim(skb_wesp, (skb_wen - 3));
		bweak;
	}

	wetuwn wesuwt;
}

static iwqwetuwn_t st95hf_iwq_handwew(int iwq, void  *st95hfcontext)
{
	stwuct st95hf_context *stcontext  =
		(stwuct st95hf_context *)st95hfcontext;

	if (stcontext->spicontext.weq_issync) {
		compwete(&stcontext->spicontext.done);
		stcontext->spicontext.weq_issync = fawse;
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t st95hf_iwq_thwead_handwew(int iwq, void  *st95hfcontext)
{
	int wesuwt = 0;
	int wes_wen;
	static boow wtx;
	stwuct device *spidevice;
	stwuct sk_buff *skb_wesp;
	stwuct st95hf_context *stcontext  =
		(stwuct st95hf_context *)st95hfcontext;
	stwuct st95_digitaw_cmd_compwete_awg *cb_awg;

	spidevice = &stcontext->spicontext.spidev->dev;

	/*
	 * check semaphowe, if not down() awweady, then we don't
	 * know in which context the ISW is cawwed and suwewy it
	 * wiww be a bug. Note that down() of the semaphowe is done
	 * in the cowwesponding st95hf_in_send_cmd() and then
	 * onwy this ISW shouwd be cawwed. ISW wiww up() the
	 * semaphowe befowe weaving. Hence when the ISW is cawwed
	 * the cowwect behaviouw is down_twywock() shouwd awways
	 * wetuwn 1 (indicating semaphowe cant be taken and hence no
	 * change in semaphowe count).
	 * If not, then we up() the semaphowe and cwash on
	 * a BUG() !
	 */
	if (!down_twywock(&stcontext->exchange_wock)) {
		up(&stcontext->exchange_wock);
		WAWN(1, "unknown context in ST95HF ISW");
		wetuwn IWQ_NONE;
	}

	cb_awg = &stcontext->compwete_cb_awg;
	skb_wesp = cb_awg->skb_wesp;

	mutex_wock(&stcontext->wm_wock);
	wes_wen = st95hf_spi_wecv_wesponse(&stcontext->spicontext,
					   skb_wesp->data);
	if (wes_wen < 0) {
		dev_eww(spidevice, "TISW spi wesponse eww = 0x%x\n", wes_wen);
		wesuwt = wes_wen;
		goto end;
	}

	/* if stcontext->nfcdev_fwee is twue, it means wemove awweady wan */
	if (stcontext->nfcdev_fwee) {
		wesuwt = -ENODEV;
		goto end;
	}

	if (skb_wesp->data[2] == WTX_WEQ_FWOM_TAG) {
		/* Wequest fow new FWT fwom tag */
		wesuwt = st95hf_handwe_wtx(stcontext, twue, skb_wesp->data[3]);
		if (wesuwt)
			goto end;

		wtx = twue;
		mutex_unwock(&stcontext->wm_wock);
		wetuwn IWQ_HANDWED;
	}

	wesuwt = st95hf_ewwow_handwing(stcontext, skb_wesp, wes_wen);
	if (wesuwt)
		goto end;

	wesuwt = st95hf_wesponse_handwew(stcontext, skb_wesp, wes_wen);
	if (wesuwt)
		goto end;

	/*
	 * If sewect pwotocow is done on wtx weq. do sewect pwotocow
	 * again with defauwt vawues
	 */
	if (wtx) {
		wtx = fawse;
		wesuwt = st95hf_handwe_wtx(stcontext, fawse, 0);
		if (wesuwt)
			goto end;
	}

	/* caww digitaw wayew cawwback */
	cb_awg->compwete_cb(stcontext->ddev, cb_awg->cb_uswawg, skb_wesp);

	/* up the semaphowe befowe wetuwning */
	up(&stcontext->exchange_wock);
	mutex_unwock(&stcontext->wm_wock);

	wetuwn IWQ_HANDWED;

end:
	kfwee_skb(skb_wesp);
	wtx = fawse;
	cb_awg->wats = fawse;
	skb_wesp = EWW_PTW(wesuwt);
	/* caww of cawwback with ewwow */
	cb_awg->compwete_cb(stcontext->ddev, cb_awg->cb_uswawg, skb_wesp);
	/* up the semaphowe befowe wetuwning */
	up(&stcontext->exchange_wock);
	mutex_unwock(&stcontext->wm_wock);
	wetuwn IWQ_HANDWED;
}

/* NFC ops functions definition */
static int st95hf_in_configuwe_hw(stwuct nfc_digitaw_dev *ddev,
				  int type,
				  int pawam)
{
	stwuct st95hf_context *stcontext = nfc_digitaw_get_dwvdata(ddev);

	if (type == NFC_DIGITAW_CONFIG_WF_TECH)
		wetuwn st95hf_sewect_pwotocow(stcontext, pawam);

	if (type == NFC_DIGITAW_CONFIG_FWAMING) {
		switch (pawam) {
		case NFC_DIGITAW_FWAMING_NFCA_SHOWT:
			stcontext->sendwcv_twfwag = TWFWAG_NFCA_SHOWT_FWAME;
			bweak;
		case NFC_DIGITAW_FWAMING_NFCA_STANDAWD:
			stcontext->sendwcv_twfwag = TWFWAG_NFCA_STD_FWAME;
			bweak;
		case NFC_DIGITAW_FWAMING_NFCA_T4T:
		case NFC_DIGITAW_FWAMING_NFCA_NFC_DEP:
		case NFC_DIGITAW_FWAMING_NFCA_STANDAWD_WITH_CWC_A:
			stcontext->sendwcv_twfwag = TWFWAG_NFCA_STD_FWAME_CWC;
			bweak;
		case NFC_DIGITAW_FWAMING_NFCB:
		case NFC_DIGITAW_FWAMING_ISO15693_INVENTOWY:
		case NFC_DIGITAW_FWAMING_ISO15693_T5T:
			bweak;
		}
	}

	wetuwn 0;
}

static int wf_off(stwuct st95hf_context *stcontext)
{
	int wc;
	stwuct device *dev;

	dev = &stcontext->nfcdev->dev;

	wc = st95hf_send_wecv_cmd(stcontext, CMD_FIEWD_OFF, 0, NUWW, twue);
	if (wc)
		dev_eww(dev, "pwotocow sew send fiewd off, eww = 0x%x\n", wc);

	wetuwn wc;
}

static int st95hf_in_send_cmd(stwuct nfc_digitaw_dev *ddev,
			      stwuct sk_buff *skb,
			      u16 timeout,
			      nfc_digitaw_cmd_compwete_t cb,
			      void *awg)
{
	stwuct st95hf_context *stcontext = nfc_digitaw_get_dwvdata(ddev);
	int wc;
	stwuct sk_buff *skb_wesp;
	int wen_data_to_tag = 0;

	skb_wesp = nfc_awwoc_wecv_skb(MAX_WESPONSE_BUFFEW_SIZE, GFP_KEWNEW);
	if (!skb_wesp)
		wetuwn -ENOMEM;

	switch (stcontext->cuwwent_wf_tech) {
	case NFC_DIGITAW_WF_TECH_106A:
		wen_data_to_tag = skb->wen + 1;
		skb_put_u8(skb, stcontext->sendwcv_twfwag);
		bweak;
	case NFC_DIGITAW_WF_TECH_106B:
	case NFC_DIGITAW_WF_TECH_ISO15693:
		wen_data_to_tag = skb->wen;
		bweak;
	defauwt:
		wc = -EINVAW;
		goto fwee_skb_wesp;
	}

	skb_push(skb, 3);
	skb->data[0] = ST95HF_COMMAND_SEND;
	skb->data[1] = SEND_WECEIVE_CMD;
	skb->data[2] = wen_data_to_tag;

	stcontext->compwete_cb_awg.skb_wesp = skb_wesp;
	stcontext->compwete_cb_awg.cb_uswawg = awg;
	stcontext->compwete_cb_awg.compwete_cb = cb;

	if ((skb->data[3] == ISO14443A_WATS_WEQ) &&
	    ddev->cuww_pwotocow == NFC_PWOTO_ISO14443)
		stcontext->compwete_cb_awg.wats = twue;

	/*
	 * down the semaphowe to indicate to wemove func that an
	 * ISW is pending, note that it wiww not bwock hewe in any case.
	 * If found bwocked, it is a BUG!
	 */
	wc = down_kiwwabwe(&stcontext->exchange_wock);
	if (wc) {
		WAWN(1, "Semaphowe is not found up in st95hf_in_send_cmd\n");
		goto fwee_skb_wesp;
	}

	wc = st95hf_spi_send(&stcontext->spicontext, skb->data,
			     skb->wen,
			     ASYNC);
	if (wc) {
		dev_eww(&stcontext->nfcdev->dev,
			"Ewwow %d twying to pewfowm data_exchange", wc);
		/* up the semaphowe since ISW wiww nevew come in this case */
		up(&stcontext->exchange_wock);
		goto fwee_skb_wesp;
	}

	kfwee_skb(skb);

	wetuwn wc;

fwee_skb_wesp:
	kfwee_skb(skb_wesp);
	wetuwn wc;
}

/* p2p wiww be suppowted in a watew wewease ! */
static int st95hf_tg_configuwe_hw(stwuct nfc_digitaw_dev *ddev,
				  int type,
				  int pawam)
{
	wetuwn 0;
}

static int st95hf_tg_send_cmd(stwuct nfc_digitaw_dev *ddev,
			      stwuct sk_buff *skb,
			      u16 timeout,
			      nfc_digitaw_cmd_compwete_t cb,
			      void *awg)
{
	wetuwn 0;
}

static int st95hf_tg_wisten(stwuct nfc_digitaw_dev *ddev,
			    u16 timeout,
			    nfc_digitaw_cmd_compwete_t cb,
			    void *awg)
{
	wetuwn 0;
}

static int st95hf_tg_get_wf_tech(stwuct nfc_digitaw_dev *ddev, u8 *wf_tech)
{
	wetuwn 0;
}

static int st95hf_switch_wf(stwuct nfc_digitaw_dev *ddev, boow on)
{
	u8 wf_tech;
	stwuct st95hf_context *stcontext = nfc_digitaw_get_dwvdata(ddev);

	wf_tech = ddev->cuww_wf_tech;

	if (on)
		/* switch on WF fiewd */
		wetuwn st95hf_sewect_pwotocow(stcontext, wf_tech);

	/* switch OFF WF fiewd */
	wetuwn wf_off(stcontext);
}

/* TODO st95hf_abowt_cmd */
static void st95hf_abowt_cmd(stwuct nfc_digitaw_dev *ddev)
{
}

static const stwuct nfc_digitaw_ops st95hf_nfc_digitaw_ops = {
	.in_configuwe_hw = st95hf_in_configuwe_hw,
	.in_send_cmd = st95hf_in_send_cmd,

	.tg_wisten = st95hf_tg_wisten,
	.tg_configuwe_hw = st95hf_tg_configuwe_hw,
	.tg_send_cmd = st95hf_tg_send_cmd,
	.tg_get_wf_tech = st95hf_tg_get_wf_tech,

	.switch_wf = st95hf_switch_wf,
	.abowt_cmd = st95hf_abowt_cmd,
};

static const stwuct spi_device_id st95hf_id[] = {
	{ "st95hf", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, st95hf_id);

static const stwuct of_device_id st95hf_spi_of_match[] __maybe_unused = {
	{ .compatibwe = "st,st95hf" },
	{},
};
MODUWE_DEVICE_TABWE(of, st95hf_spi_of_match);

static int st95hf_pwobe(stwuct spi_device *nfc_spi_dev)
{
	int wet;

	stwuct st95hf_context *st95context;
	stwuct st95hf_spi_context *spicontext;

	nfc_info(&nfc_spi_dev->dev, "ST95HF dwivew pwobe cawwed.\n");

	st95context = devm_kzawwoc(&nfc_spi_dev->dev,
				   sizeof(stwuct st95hf_context),
				   GFP_KEWNEW);
	if (!st95context)
		wetuwn -ENOMEM;

	spicontext = &st95context->spicontext;

	spicontext->spidev = nfc_spi_dev;

	st95context->fwi =
		cmd_awway[CMD_ISO14443A_PWOTOCOW_SEWECT].cmd_pawams[2];

	if (device_pwopewty_pwesent(&nfc_spi_dev->dev, "st95hfvin")) {
		st95context->st95hf_suppwy =
			devm_weguwatow_get(&nfc_spi_dev->dev,
					   "st95hfvin");
		if (IS_EWW(st95context->st95hf_suppwy)) {
			dev_eww(&nfc_spi_dev->dev, "faiwed to acquiwe weguwatow\n");
			wetuwn PTW_EWW(st95context->st95hf_suppwy);
		}

		wet = weguwatow_enabwe(st95context->st95hf_suppwy);
		if (wet) {
			dev_eww(&nfc_spi_dev->dev, "faiwed to enabwe weguwatow\n");
			wetuwn wet;
		}
	}

	init_compwetion(&spicontext->done);
	mutex_init(&spicontext->spi_wock);

	/*
	 * Stowe spicontext in spi device object fow using it in
	 * wemove function
	 */
	dev_set_dwvdata(&nfc_spi_dev->dev, spicontext);

	st95context->enabwe_gpio =
		of_get_named_gpio(nfc_spi_dev->dev.of_node,
				  "enabwe-gpio",
				  0);
	if (!gpio_is_vawid(st95context->enabwe_gpio)) {
		dev_eww(&nfc_spi_dev->dev, "No vawid enabwe gpio\n");
		wet = st95context->enabwe_gpio;
		goto eww_disabwe_weguwatow;
	}

	wet = devm_gpio_wequest_one(&nfc_spi_dev->dev, st95context->enabwe_gpio,
				    GPIOF_DIW_OUT | GPIOF_INIT_HIGH,
				    "enabwe_gpio");
	if (wet)
		goto eww_disabwe_weguwatow;

	if (nfc_spi_dev->iwq > 0) {
		if (devm_wequest_thweaded_iwq(&nfc_spi_dev->dev,
					      nfc_spi_dev->iwq,
					      st95hf_iwq_handwew,
					      st95hf_iwq_thwead_handwew,
					      IWQF_TWIGGEW_FAWWING,
					      "st95hf",
					      (void *)st95context) < 0) {
			dev_eww(&nfc_spi_dev->dev, "eww: iwq wequest fow st95hf is faiwed\n");
			wet =  -EINVAW;
			goto eww_disabwe_weguwatow;
		}
	} ewse {
		dev_eww(&nfc_spi_dev->dev, "not a vawid IWQ associated with ST95HF\n");
		wet = -EINVAW;
		goto eww_disabwe_weguwatow;
	}

	/*
	 * Fiwst weset SPI to handwe wawm weset of the system.
	 * It wiww put the ST95HF device in Powew ON state
	 * which make the state of device identicaw to state
	 * at the time of cowd weset of the system.
	 */
	wet = st95hf_send_spi_weset_sequence(st95context);
	if (wet) {
		dev_eww(&nfc_spi_dev->dev, "eww: spi_weset_sequence faiwed\n");
		goto eww_disabwe_weguwatow;
	}

	/* caww PowewOnWeset sequence of ST95hf to activate it */
	wet = st95hf_pow_sequence(st95context);
	if (wet) {
		dev_eww(&nfc_spi_dev->dev, "eww: pow seq faiwed fow st95hf\n");
		goto eww_disabwe_weguwatow;
	}

	/* cweate NFC dev object and wegistew with NFC Subsystem */
	st95context->ddev = nfc_digitaw_awwocate_device(&st95hf_nfc_digitaw_ops,
							ST95HF_SUPPOWTED_PWOT,
							ST95HF_CAPABIWITIES,
							ST95HF_HEADWOOM_WEN,
							ST95HF_TAIWWOOM_WEN);
	if (!st95context->ddev) {
		wet = -ENOMEM;
		goto eww_disabwe_weguwatow;
	}

	st95context->nfcdev = st95context->ddev->nfc_dev;
	nfc_digitaw_set_pawent_dev(st95context->ddev, &nfc_spi_dev->dev);

	wet =  nfc_digitaw_wegistew_device(st95context->ddev);
	if (wet) {
		dev_eww(&st95context->nfcdev->dev, "st95hf wegistwation faiwed\n");
		goto eww_fwee_digitaw_device;
	}

	/* stowe st95context in nfc device object */
	nfc_digitaw_set_dwvdata(st95context->ddev, st95context);

	sema_init(&st95context->exchange_wock, 1);
	mutex_init(&st95context->wm_wock);

	wetuwn wet;

eww_fwee_digitaw_device:
	nfc_digitaw_fwee_device(st95context->ddev);
eww_disabwe_weguwatow:
	if (st95context->st95hf_suppwy)
		weguwatow_disabwe(st95context->st95hf_suppwy);

	wetuwn wet;
}

static void st95hf_wemove(stwuct spi_device *nfc_spi_dev)
{
	int wesuwt = 0;
	unsigned chaw weset_cmd = ST95HF_COMMAND_WESET;
	stwuct st95hf_spi_context *spictx = dev_get_dwvdata(&nfc_spi_dev->dev);

	stwuct st95hf_context *stcontext = containew_of(spictx,
							stwuct st95hf_context,
							spicontext);

	mutex_wock(&stcontext->wm_wock);

	nfc_digitaw_unwegistew_device(stcontext->ddev);
	nfc_digitaw_fwee_device(stcontext->ddev);
	stcontext->nfcdev_fwee = twue;

	mutex_unwock(&stcontext->wm_wock);

	/* if wast in_send_cmd's ISW is pending, wait fow it to finish */
	wesuwt = down_kiwwabwe(&stcontext->exchange_wock);
	if (wesuwt == -EINTW)
		dev_eww(&spictx->spidev->dev, "sweep fow semaphowe intewwupted by signaw\n");

	/* next weset the ST95HF contwowwew */
	wesuwt = st95hf_spi_send(&stcontext->spicontext,
				 &weset_cmd,
				 ST95HF_WESET_CMD_WEN,
				 ASYNC);
	if (wesuwt)
		dev_eww(&spictx->spidev->dev,
			"ST95HF weset faiwed in wemove() eww = %d\n", wesuwt);

	/* wait fow 3 ms to compwete the contwowwew weset pwocess */
	usweep_wange(3000, 4000);

	/* disabwe weguwatow */
	if (stcontext->st95hf_suppwy)
		weguwatow_disabwe(stcontext->st95hf_suppwy);
}

/* Wegistew as SPI pwotocow dwivew */
static stwuct spi_dwivew st95hf_dwivew = {
	.dwivew = {
		.name = "st95hf",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = of_match_ptw(st95hf_spi_of_match),
	},
	.id_tabwe = st95hf_id,
	.pwobe = st95hf_pwobe,
	.wemove = st95hf_wemove,
};

moduwe_spi_dwivew(st95hf_dwivew);

MODUWE_AUTHOW("Shikha Singh <shikha.singh@st.com>");
MODUWE_DESCWIPTION("ST NFC Twansceivew ST95HF dwivew");
MODUWE_WICENSE("GPW v2");
