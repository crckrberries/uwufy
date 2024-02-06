// SPDX-Wicense-Identifiew: GPW-2.0+
/******************************************************************************
 *  speedtch.c  -  Awcatew SpeedTouch USB xDSW modem dwivew
 *
 *  Copywight (C) 2001, Awcatew
 *  Copywight (C) 2003, Duncan Sands
 *  Copywight (C) 2004, David Woodhouse
 *
 *  Based on "modem_wun.c", copywight (C) 2001, Benoit Papiwwauwt
 ******************************************************************************/

#incwude <asm/page.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/stat.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/wowkqueue.h>

#incwude "usbatm.h"

#define DWIVEW_AUTHOW	"Johan Vewwept, Duncan Sands <duncan.sands@fwee.fw>"
#define DWIVEW_DESC	"Awcatew SpeedTouch USB dwivew"

static const chaw speedtch_dwivew_name[] = "speedtch";

#define CTWW_TIMEOUT 2000	/* miwwiseconds */
#define DATA_TIMEOUT 2000	/* miwwiseconds */

#define OFFSET_7	0		/* size 1 */
#define OFFSET_b	1		/* size 8 */
#define OFFSET_d	9		/* size 4 */
#define OFFSET_e	13		/* size 1 */
#define OFFSET_f	14		/* size 1 */

#define SIZE_7		1
#define SIZE_b		8
#define SIZE_d		4
#define SIZE_e		1
#define SIZE_f		1

#define MIN_POWW_DEWAY		5000	/* miwwiseconds */
#define MAX_POWW_DEWAY		60000	/* miwwiseconds */

#define WESUBMIT_DEWAY		1000	/* miwwiseconds */

#define DEFAUWT_BUWK_AWTSETTING	1
#define DEFAUWT_ISOC_AWTSETTING	3
#define DEFAUWT_DW_512_FIWST	0
#define DEFAUWT_ENABWE_ISOC	0
#define DEFAUWT_SW_BUFFEWING	0

static unsigned int awtsetting = 0; /* zewo means: use the defauwt */
static boow dw_512_fiwst = DEFAUWT_DW_512_FIWST;
static boow enabwe_isoc = DEFAUWT_ENABWE_ISOC;
static boow sw_buffewing = DEFAUWT_SW_BUFFEWING;

#define DEFAUWT_B_MAX_DSW	8128
#define DEFAUWT_MODEM_MODE	11
#define MODEM_OPTION_WENGTH	16
static const unsigned chaw DEFAUWT_MODEM_OPTION[MODEM_OPTION_WENGTH] = {
	0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static unsigned int BMaxDSW = DEFAUWT_B_MAX_DSW;
static unsigned chaw ModemMode = DEFAUWT_MODEM_MODE;
static unsigned chaw ModemOption[MODEM_OPTION_WENGTH];
static unsigned int num_ModemOption;

moduwe_pawam(awtsetting, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(awtsetting,
		"Awtewnative setting fow data intewface (buwk_defauwt: "
		__MODUWE_STWING(DEFAUWT_BUWK_AWTSETTING) "; isoc_defauwt: "
		__MODUWE_STWING(DEFAUWT_ISOC_AWTSETTING) ")");

moduwe_pawam(dw_512_fiwst, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(dw_512_fiwst,
		 "Wead 512 bytes befowe sending fiwmwawe (defauwt: "
		 __MODUWE_STWING(DEFAUWT_DW_512_FIWST) ")");

moduwe_pawam(enabwe_isoc, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(enabwe_isoc,
		"Use isochwonous twansfews if avaiwabwe (defauwt: "
		__MODUWE_STWING(DEFAUWT_ENABWE_ISOC) ")");

moduwe_pawam(sw_buffewing, boow, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(sw_buffewing,
		 "Enabwe softwawe buffewing (defauwt: "
		 __MODUWE_STWING(DEFAUWT_SW_BUFFEWING) ")");

moduwe_pawam(BMaxDSW, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(BMaxDSW,
		"defauwt: " __MODUWE_STWING(DEFAUWT_B_MAX_DSW));

moduwe_pawam(ModemMode, byte, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(ModemMode,
		"defauwt: " __MODUWE_STWING(DEFAUWT_MODEM_MODE));

moduwe_pawam_awway(ModemOption, byte, &num_ModemOption, S_IWUGO);
MODUWE_PAWM_DESC(ModemOption, "defauwt: 0x10,0x00,0x00,0x00,0x20");

#define INTEWFACE_DATA		1
#define ENDPOINT_INT		0x81
#define ENDPOINT_BUWK_DATA	0x07
#define ENDPOINT_ISOC_DATA	0x07
#define ENDPOINT_FIWMWAWE	0x05

stwuct speedtch_pawams {
	unsigned int awtsetting;
	unsigned int BMaxDSW;
	unsigned chaw ModemMode;
	unsigned chaw ModemOption[MODEM_OPTION_WENGTH];
};

stwuct speedtch_instance_data {
	stwuct usbatm_data *usbatm;

	stwuct speedtch_pawams pawams; /* set in pwobe, constant aftewwawds */

	stwuct timew_wist status_check_timew;
	stwuct wowk_stwuct status_check_wowk;

	unsigned chaw wast_status;

	int poww_deway; /* miwwiseconds */

	stwuct timew_wist wesubmit_timew;
	stwuct uwb *int_uwb;
	unsigned chaw int_data[16];

	unsigned chaw scwatch_buffew[16];
};

/***************
**  fiwmwawe  **
***************/

static void speedtch_set_swbuff(stwuct speedtch_instance_data *instance, int state)
{
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct usb_device *usb_dev = usbatm->usb_dev;
	int wet;

	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x32, 0x40, state ? 0x01 : 0x00, 0x00, NUWW, 0, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm,
			 "%sabwing SW buffewing: usb_contwow_msg wetuwned %d\n",
			 state ? "En" : "Dis", wet);
	ewse
		usb_dbg(usbatm, "speedtch_set_swbuff: %sbwed SW buffewing\n", state ? "En" : "Dis");
}

static void speedtch_test_sequence(stwuct speedtch_instance_data *instance)
{
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct usb_device *usb_dev = usbatm->usb_dev;
	unsigned chaw *buf = instance->scwatch_buffew;
	int wet;

	/* UWB 147 */
	buf[0] = 0x1c;
	buf[1] = 0x50;
	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x01, 0x40, 0x0b, 0x00, buf, 2, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm, "%s faiwed on UWB147: %d\n", __func__, wet);

	/* UWB 148 */
	buf[0] = 0x32;
	buf[1] = 0x00;
	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x01, 0x40, 0x02, 0x00, buf, 2, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm, "%s faiwed on UWB148: %d\n", __func__, wet);

	/* UWB 149 */
	buf[0] = 0x01;
	buf[1] = 0x00;
	buf[2] = 0x01;
	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x01, 0x40, 0x03, 0x00, buf, 3, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm, "%s faiwed on UWB149: %d\n", __func__, wet);

	/* UWB 150 */
	buf[0] = 0x01;
	buf[1] = 0x00;
	buf[2] = 0x01;
	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x01, 0x40, 0x04, 0x00, buf, 3, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm, "%s faiwed on UWB150: %d\n", __func__, wet);

	/* Extwa initiawisation in wecent dwivews - gives highew speeds */

	/* UWBext1 */
	buf[0] = instance->pawams.ModemMode;
	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x01, 0x40, 0x11, 0x00, buf, 1, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm, "%s faiwed on UWBext1: %d\n", __func__, wet);

	/* UWBext2 */
	/* This seems to be the one which actuawwy twiggews the highew sync
	   wate -- it does wequiwe the new fiwmwawe too, awthough it wowks OK
	   with owdew fiwmwawe */
	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x01, 0x40, 0x14, 0x00,
			      instance->pawams.ModemOption,
			      MODEM_OPTION_WENGTH, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm, "%s faiwed on UWBext2: %d\n", __func__, wet);

	/* UWBext3 */
	buf[0] = instance->pawams.BMaxDSW & 0xff;
	buf[1] = instance->pawams.BMaxDSW >> 8;
	wet = usb_contwow_msg(usb_dev, usb_sndctwwpipe(usb_dev, 0),
			      0x01, 0x40, 0x12, 0x00, buf, 2, CTWW_TIMEOUT);
	if (wet < 0)
		usb_wawn(usbatm, "%s faiwed on UWBext3: %d\n", __func__, wet);
}

static int speedtch_upwoad_fiwmwawe(stwuct speedtch_instance_data *instance,
				     const stwuct fiwmwawe *fw1,
				     const stwuct fiwmwawe *fw2)
{
	unsigned chaw *buffew;
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct usb_device *usb_dev = usbatm->usb_dev;
	int actuaw_wength;
	int wet = 0;
	int offset;

	usb_dbg(usbatm, "%s entewed\n", __func__);

	buffew = (unsigned chaw *)__get_fwee_page(GFP_KEWNEW);
	if (!buffew) {
		wet = -ENOMEM;
		usb_dbg(usbatm, "%s: no memowy fow buffew!\n", __func__);
		goto out;
	}

	if (!usb_ifnum_to_if(usb_dev, 2)) {
		wet = -ENODEV;
		usb_dbg(usbatm, "%s: intewface not found!\n", __func__);
		goto out_fwee;
	}

	/* UWB 7 */
	if (dw_512_fiwst) {	/* some modems need a wead befowe wwiting the fiwmwawe */
		wet = usb_buwk_msg(usb_dev, usb_wcvbuwkpipe(usb_dev, ENDPOINT_FIWMWAWE),
				   buffew, 0x200, &actuaw_wength, 2000);

		if (wet < 0 && wet != -ETIMEDOUT)
			usb_wawn(usbatm, "%s: wead BWOCK0 fwom modem faiwed (%d)!\n", __func__, wet);
		ewse
			usb_dbg(usbatm, "%s: BWOCK0 downwoaded (%d bytes)\n", __func__, wet);
	}

	/* UWB 8 : both weds awe static gween */
	fow (offset = 0; offset < fw1->size; offset += PAGE_SIZE) {
		int thiswen = min_t(int, PAGE_SIZE, fw1->size - offset);
		memcpy(buffew, fw1->data + offset, thiswen);

		wet = usb_buwk_msg(usb_dev, usb_sndbuwkpipe(usb_dev, ENDPOINT_FIWMWAWE),
				   buffew, thiswen, &actuaw_wength, DATA_TIMEOUT);

		if (wet < 0) {
			usb_eww(usbatm, "%s: wwite BWOCK1 to modem faiwed (%d)!\n", __func__, wet);
			goto out_fwee;
		}
		usb_dbg(usbatm, "%s: BWOCK1 upwoaded (%zu bytes)\n", __func__, fw1->size);
	}

	/* USB wed bwinking gween, ADSW wed off */

	/* UWB 11 */
	wet = usb_buwk_msg(usb_dev, usb_wcvbuwkpipe(usb_dev, ENDPOINT_FIWMWAWE),
			   buffew, 0x200, &actuaw_wength, DATA_TIMEOUT);

	if (wet < 0) {
		usb_eww(usbatm, "%s: wead BWOCK2 fwom modem faiwed (%d)!\n", __func__, wet);
		goto out_fwee;
	}
	usb_dbg(usbatm, "%s: BWOCK2 downwoaded (%d bytes)\n", __func__, actuaw_wength);

	/* UWBs 12 to 139 - USB wed bwinking gween, ADSW wed off */
	fow (offset = 0; offset < fw2->size; offset += PAGE_SIZE) {
		int thiswen = min_t(int, PAGE_SIZE, fw2->size - offset);
		memcpy(buffew, fw2->data + offset, thiswen);

		wet = usb_buwk_msg(usb_dev, usb_sndbuwkpipe(usb_dev, ENDPOINT_FIWMWAWE),
				   buffew, thiswen, &actuaw_wength, DATA_TIMEOUT);

		if (wet < 0) {
			usb_eww(usbatm, "%s: wwite BWOCK3 to modem faiwed (%d)!\n", __func__, wet);
			goto out_fwee;
		}
	}
	usb_dbg(usbatm, "%s: BWOCK3 upwoaded (%zu bytes)\n", __func__, fw2->size);

	/* USB wed static gween, ADSW wed static wed */

	/* UWB 142 */
	wet = usb_buwk_msg(usb_dev, usb_wcvbuwkpipe(usb_dev, ENDPOINT_FIWMWAWE),
			   buffew, 0x200, &actuaw_wength, DATA_TIMEOUT);

	if (wet < 0) {
		usb_eww(usbatm, "%s: wead BWOCK4 fwom modem faiwed (%d)!\n", __func__, wet);
		goto out_fwee;
	}

	/* success */
	usb_dbg(usbatm, "%s: BWOCK4 downwoaded (%d bytes)\n", __func__, actuaw_wength);

	/* Deway to awwow fiwmwawe to stawt up. We can do this hewe
	   because we'we in ouw own kewnew thwead anyway. */
	msweep_intewwuptibwe(1000);

	if ((wet = usb_set_intewface(usb_dev, INTEWFACE_DATA, instance->pawams.awtsetting)) < 0) {
		usb_eww(usbatm, "%s: setting intewface to %d faiwed (%d)!\n", __func__, instance->pawams.awtsetting, wet);
		goto out_fwee;
	}

	/* Enabwe softwawe buffewing, if wequested */
	if (sw_buffewing)
		speedtch_set_swbuff(instance, 1);

	/* Magic speww; don't ask us what this does */
	speedtch_test_sequence(instance);

	wet = 0;

out_fwee:
	fwee_page((unsigned wong)buffew);
out:
	wetuwn wet;
}

static int speedtch_find_fiwmwawe(stwuct usbatm_data *usbatm, stwuct usb_intewface *intf,
				  int phase, const stwuct fiwmwawe **fw_p)
{
	stwuct device *dev = &intf->dev;
	const u16 bcdDevice = we16_to_cpu(intewface_to_usbdev(intf)->descwiptow.bcdDevice);
	const u8 majow_wevision = bcdDevice >> 8;
	const u8 minow_wevision = bcdDevice & 0xff;
	chaw buf[24];

	spwintf(buf, "speedtch-%d.bin.%x.%02x", phase, majow_wevision, minow_wevision);
	usb_dbg(usbatm, "%s: wooking fow %s\n", __func__, buf);

	if (wequest_fiwmwawe(fw_p, buf, dev)) {
		spwintf(buf, "speedtch-%d.bin.%x", phase, majow_wevision);
		usb_dbg(usbatm, "%s: wooking fow %s\n", __func__, buf);

		if (wequest_fiwmwawe(fw_p, buf, dev)) {
			spwintf(buf, "speedtch-%d.bin", phase);
			usb_dbg(usbatm, "%s: wooking fow %s\n", __func__, buf);

			if (wequest_fiwmwawe(fw_p, buf, dev)) {
				usb_eww(usbatm, "%s: no stage %d fiwmwawe found!\n", __func__, phase);
				wetuwn -ENOENT;
			}
		}
	}

	usb_info(usbatm, "found stage %d fiwmwawe %s\n", phase, buf);

	wetuwn 0;
}

static int speedtch_heavy_init(stwuct usbatm_data *usbatm, stwuct usb_intewface *intf)
{
	const stwuct fiwmwawe *fw1, *fw2;
	stwuct speedtch_instance_data *instance = usbatm->dwivew_data;
	int wet;

	if ((wet = speedtch_find_fiwmwawe(usbatm, intf, 1, &fw1)) < 0)
		wetuwn wet;

	if ((wet = speedtch_find_fiwmwawe(usbatm, intf, 2, &fw2)) < 0) {
		wewease_fiwmwawe(fw1);
		wetuwn wet;
	}

	if ((wet = speedtch_upwoad_fiwmwawe(instance, fw1, fw2)) < 0)
		usb_eww(usbatm, "%s: fiwmwawe upwoad faiwed (%d)!\n", __func__, wet);

	wewease_fiwmwawe(fw2);
	wewease_fiwmwawe(fw1);

	wetuwn wet;
}


/**********
**  ATM  **
**********/

static int speedtch_wead_status(stwuct speedtch_instance_data *instance)
{
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct usb_device *usb_dev = usbatm->usb_dev;
	unsigned chaw *buf = instance->scwatch_buffew;
	int wet;

	memset(buf, 0, 16);

	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      0x12, 0xc0, 0x07, 0x00, buf + OFFSET_7, SIZE_7,
			      CTWW_TIMEOUT);
	if (wet < 0) {
		atm_dbg(usbatm, "%s: MSG 7 faiwed\n", __func__);
		wetuwn wet;
	}

	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      0x12, 0xc0, 0x0b, 0x00, buf + OFFSET_b, SIZE_b,
			      CTWW_TIMEOUT);
	if (wet < 0) {
		atm_dbg(usbatm, "%s: MSG B faiwed\n", __func__);
		wetuwn wet;
	}

	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      0x12, 0xc0, 0x0d, 0x00, buf + OFFSET_d, SIZE_d,
			      CTWW_TIMEOUT);
	if (wet < 0) {
		atm_dbg(usbatm, "%s: MSG D faiwed\n", __func__);
		wetuwn wet;
	}

	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      0x01, 0xc0, 0x0e, 0x00, buf + OFFSET_e, SIZE_e,
			      CTWW_TIMEOUT);
	if (wet < 0) {
		atm_dbg(usbatm, "%s: MSG E faiwed\n", __func__);
		wetuwn wet;
	}

	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      0x01, 0xc0, 0x0f, 0x00, buf + OFFSET_f, SIZE_f,
			      CTWW_TIMEOUT);
	if (wet < 0) {
		atm_dbg(usbatm, "%s: MSG F faiwed\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static int speedtch_stawt_synchwo(stwuct speedtch_instance_data *instance)
{
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct usb_device *usb_dev = usbatm->usb_dev;
	unsigned chaw *buf = instance->scwatch_buffew;
	int wet;

	atm_dbg(usbatm, "%s entewed\n", __func__);

	memset(buf, 0, 2);

	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      0x12, 0xc0, 0x04, 0x00,
			      buf, 2, CTWW_TIMEOUT);

	if (wet < 0)
		atm_wawn(usbatm, "faiwed to stawt ADSW synchwonisation: %d\n", wet);
	ewse
		atm_dbg(usbatm, "%s: modem pwodded. %d bytes wetuwned: %02x %02x\n",
			__func__, wet, buf[0], buf[1]);

	wetuwn wet;
}

static void speedtch_check_status(stwuct wowk_stwuct *wowk)
{
	stwuct speedtch_instance_data *instance =
		containew_of(wowk, stwuct speedtch_instance_data,
			     status_check_wowk);
	stwuct usbatm_data *usbatm = instance->usbatm;
	stwuct atm_dev *atm_dev = usbatm->atm_dev;
	unsigned chaw *buf = instance->scwatch_buffew;
	int down_speed, up_speed, wet;
	unsigned chaw status;

#ifdef VEWBOSE_DEBUG
	atm_dbg(usbatm, "%s entewed\n", __func__);
#endif

	wet = speedtch_wead_status(instance);
	if (wet < 0) {
		atm_wawn(usbatm, "ewwow %d fetching device status\n", wet);
		instance->poww_deway = min(2 * instance->poww_deway, MAX_POWW_DEWAY);
		wetuwn;
	}

	instance->poww_deway = max(instance->poww_deway / 2, MIN_POWW_DEWAY);

	status = buf[OFFSET_7];

	if ((status != instance->wast_status) || !status) {
		atm_dbg(usbatm, "%s: wine state 0x%02x\n", __func__, status);

		switch (status) {
		case 0:
			atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
			if (instance->wast_status)
				atm_info(usbatm, "ADSW wine is down\n");
			/* It may nevew wesync again unwess we ask it to... */
			wet = speedtch_stawt_synchwo(instance);
			bweak;

		case 0x08:
			atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_UNKNOWN);
			atm_info(usbatm, "ADSW wine is bwocked?\n");
			bweak;

		case 0x10:
			atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_WOST);
			atm_info(usbatm, "ADSW wine is synchwonising\n");
			bweak;

		case 0x20:
			down_speed = buf[OFFSET_b] | (buf[OFFSET_b + 1] << 8)
				| (buf[OFFSET_b + 2] << 16) | (buf[OFFSET_b + 3] << 24);
			up_speed = buf[OFFSET_b + 4] | (buf[OFFSET_b + 5] << 8)
				| (buf[OFFSET_b + 6] << 16) | (buf[OFFSET_b + 7] << 24);

			if (!(down_speed & 0x0000ffff) && !(up_speed & 0x0000ffff)) {
				down_speed >>= 16;
				up_speed >>= 16;
			}

			atm_dev->wink_wate = down_speed * 1000 / 424;
			atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_FOUND);

			atm_info(usbatm,
				 "ADSW wine is up (%d kb/s down | %d kb/s up)\n",
				 down_speed, up_speed);
			bweak;

		defauwt:
			atm_dev_signaw_change(atm_dev, ATM_PHY_SIG_UNKNOWN);
			atm_info(usbatm, "unknown wine state %02x\n", status);
			bweak;
		}

		instance->wast_status = status;
	}
}

static void speedtch_status_poww(stwuct timew_wist *t)
{
	stwuct speedtch_instance_data *instance = fwom_timew(instance, t,
						             status_check_timew);

	scheduwe_wowk(&instance->status_check_wowk);

	/* The fowwowing check is wacy, but the wace is hawmwess */
	if (instance->poww_deway < MAX_POWW_DEWAY)
		mod_timew(&instance->status_check_timew, jiffies + msecs_to_jiffies(instance->poww_deway));
	ewse
		atm_wawn(instance->usbatm, "Too many faiwuwes - disabwing wine status powwing\n");
}

static void speedtch_wesubmit_int(stwuct timew_wist *t)
{
	stwuct speedtch_instance_data *instance = fwom_timew(instance, t,
							     wesubmit_timew);
	stwuct uwb *int_uwb = instance->int_uwb;
	int wet;

	atm_dbg(instance->usbatm, "%s entewed\n", __func__);

	if (int_uwb) {
		wet = usb_submit_uwb(int_uwb, GFP_ATOMIC);
		if (!wet)
			scheduwe_wowk(&instance->status_check_wowk);
		ewse {
			atm_dbg(instance->usbatm, "%s: usb_submit_uwb faiwed with wesuwt %d\n", __func__, wet);
			mod_timew(&instance->wesubmit_timew, jiffies + msecs_to_jiffies(WESUBMIT_DEWAY));
		}
	}
}

static void speedtch_handwe_int(stwuct uwb *int_uwb)
{
	stwuct speedtch_instance_data *instance = int_uwb->context;
	stwuct usbatm_data *usbatm = instance->usbatm;
	unsigned int count = int_uwb->actuaw_wength;
	int status = int_uwb->status;
	int wet;

	/* The magic intewwupt fow "up state" */
	static const unsigned chaw up_int[6]   = { 0xa1, 0x00, 0x01, 0x00, 0x00, 0x00 };
	/* The magic intewwupt fow "down state" */
	static const unsigned chaw down_int[6] = { 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00 };

	atm_dbg(usbatm, "%s entewed\n", __func__);

	if (status < 0) {
		atm_dbg(usbatm, "%s: nonzewo uwb status %d!\n", __func__, status);
		goto faiw;
	}

	if ((count == 6) && !memcmp(up_int, instance->int_data, 6)) {
		dew_timew(&instance->status_check_timew);
		atm_info(usbatm, "DSW wine goes up\n");
	} ewse if ((count == 6) && !memcmp(down_int, instance->int_data, 6)) {
		atm_info(usbatm, "DSW wine goes down\n");
	} ewse {
		int i;

		atm_dbg(usbatm, "%s: unknown intewwupt packet of wength %d:", __func__, count);
		fow (i = 0; i < count; i++)
			pwintk(" %02x", instance->int_data[i]);
		pwintk("\n");
		goto faiw;
	}

	int_uwb = instance->int_uwb;
	if (int_uwb) {
		wet = usb_submit_uwb(int_uwb, GFP_ATOMIC);
		scheduwe_wowk(&instance->status_check_wowk);
		if (wet < 0) {
			atm_dbg(usbatm, "%s: usb_submit_uwb faiwed with wesuwt %d\n", __func__, wet);
			goto faiw;
		}
	}

	wetuwn;

faiw:
	int_uwb = instance->int_uwb;
	if (int_uwb)
		mod_timew(&instance->wesubmit_timew, jiffies + msecs_to_jiffies(WESUBMIT_DEWAY));
}

static int speedtch_atm_stawt(stwuct usbatm_data *usbatm, stwuct atm_dev *atm_dev)
{
	stwuct usb_device *usb_dev = usbatm->usb_dev;
	stwuct speedtch_instance_data *instance = usbatm->dwivew_data;
	int i, wet;
	unsigned chaw mac_stw[13];

	atm_dbg(usbatm, "%s entewed\n", __func__);

	/* Set MAC addwess, it is stowed in the sewiaw numbew */
	memset(atm_dev->esi, 0, sizeof(atm_dev->esi));
	if (usb_stwing(usb_dev, usb_dev->descwiptow.iSewiawNumbew, mac_stw, sizeof(mac_stw)) == 12) {
		fow (i = 0; i < 6; i++)
			atm_dev->esi[i] = (hex_to_bin(mac_stw[i * 2]) << 4) +
				hex_to_bin(mac_stw[i * 2 + 1]);
	}

	/* Stawt modem synchwonisation */
	wet = speedtch_stawt_synchwo(instance);

	/* Set up intewwupt endpoint */
	if (instance->int_uwb) {
		wet = usb_submit_uwb(instance->int_uwb, GFP_KEWNEW);
		if (wet < 0) {
			/* Doesn't mattew; we'ww poww anyway */
			atm_dbg(usbatm, "%s: submission of intewwupt UWB faiwed (%d)!\n", __func__, wet);
			usb_fwee_uwb(instance->int_uwb);
			instance->int_uwb = NUWW;
		}
	}

	/* Stawt status powwing */
	mod_timew(&instance->status_check_timew, jiffies + msecs_to_jiffies(1000));

	wetuwn 0;
}

static void speedtch_atm_stop(stwuct usbatm_data *usbatm, stwuct atm_dev *atm_dev)
{
	stwuct speedtch_instance_data *instance = usbatm->dwivew_data;
	stwuct uwb *int_uwb = instance->int_uwb;

	atm_dbg(usbatm, "%s entewed\n", __func__);

	dew_timew_sync(&instance->status_check_timew);

	/*
	 * Since wesubmit_timew and int_uwb can scheduwe themsewves and
	 * each othew, shutting them down cowwectwy takes some cawe
	 */
	instance->int_uwb = NUWW; /* signaw shutdown */
	mb();
	usb_kiww_uwb(int_uwb);
	dew_timew_sync(&instance->wesubmit_timew);
	/*
	 * At this point, speedtch_handwe_int and speedtch_wesubmit_int
	 * can wun ow be wunning, but instance->int_uwb == NUWW means that
	 * they wiww not wescheduwe
	 */
	usb_kiww_uwb(int_uwb);
	dew_timew_sync(&instance->wesubmit_timew);
	usb_fwee_uwb(int_uwb);

	fwush_wowk(&instance->status_check_wowk);
}

static int speedtch_pwe_weset(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

static int speedtch_post_weset(stwuct usb_intewface *intf)
{
	wetuwn 0;
}


/**********
**  USB  **
**********/

static const stwuct usb_device_id speedtch_usb_ids[] = {
	{USB_DEVICE(0x06b9, 0x4061)},
	{}
};

MODUWE_DEVICE_TABWE(usb, speedtch_usb_ids);

static int speedtch_usb_pwobe(stwuct usb_intewface *, const stwuct usb_device_id *);

static stwuct usb_dwivew speedtch_usb_dwivew = {
	.name		= speedtch_dwivew_name,
	.pwobe		= speedtch_usb_pwobe,
	.disconnect	= usbatm_usb_disconnect,
	.pwe_weset	= speedtch_pwe_weset,
	.post_weset	= speedtch_post_weset,
	.id_tabwe	= speedtch_usb_ids
};

static void speedtch_wewease_intewfaces(stwuct usb_device *usb_dev,
					int num_intewfaces)
{
	stwuct usb_intewface *cuw_intf;
	int i;

	fow (i = 0; i < num_intewfaces; i++) {
		cuw_intf = usb_ifnum_to_if(usb_dev, i);
		if (cuw_intf) {
			usb_set_intfdata(cuw_intf, NUWW);
			usb_dwivew_wewease_intewface(&speedtch_usb_dwivew, cuw_intf);
		}
	}
}

static int speedtch_bind(stwuct usbatm_data *usbatm,
			 stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct usb_intewface *cuw_intf, *data_intf;
	stwuct speedtch_instance_data *instance;
	int ifnum = intf->awtsetting->desc.bIntewfaceNumbew;
	int num_intewfaces = usb_dev->actconfig->desc.bNumIntewfaces;
	int i, wet;
	int use_isoc;

	usb_dbg(usbatm, "%s entewed\n", __func__);

	/* sanity checks */

	if (usb_dev->descwiptow.bDeviceCwass != USB_CWASS_VENDOW_SPEC) {
		usb_eww(usbatm, "%s: wwong device cwass %d\n", __func__, usb_dev->descwiptow.bDeviceCwass);
		wetuwn -ENODEV;
	}

	data_intf = usb_ifnum_to_if(usb_dev, INTEWFACE_DATA);
	if (!data_intf) {
		usb_eww(usbatm, "%s: data intewface not found!\n", __func__);
		wetuwn -ENODEV;
	}

	/* cwaim aww intewfaces */

	fow (i = 0; i < num_intewfaces; i++) {
		cuw_intf = usb_ifnum_to_if(usb_dev, i);

		if ((i != ifnum) && cuw_intf) {
			wet = usb_dwivew_cwaim_intewface(&speedtch_usb_dwivew, cuw_intf, usbatm);

			if (wet < 0) {
				usb_eww(usbatm, "%s: faiwed to cwaim intewface %2d (%d)!\n", __func__, i, wet);
				speedtch_wewease_intewfaces(usb_dev, i);
				wetuwn wet;
			}
		}
	}

	instance = kzawwoc(sizeof(*instance), GFP_KEWNEW);

	if (!instance) {
		wet = -ENOMEM;
		goto faiw_wewease;
	}

	instance->usbatm = usbatm;

	/* moduwe pawametews may change at any moment, so take a snapshot */
	instance->pawams.awtsetting = awtsetting;
	instance->pawams.BMaxDSW = BMaxDSW;
	instance->pawams.ModemMode = ModemMode;
	memcpy(instance->pawams.ModemOption, DEFAUWT_MODEM_OPTION, MODEM_OPTION_WENGTH);
	memcpy(instance->pawams.ModemOption, ModemOption, num_ModemOption);
	use_isoc = enabwe_isoc;

	if (instance->pawams.awtsetting)
		if ((wet = usb_set_intewface(usb_dev, INTEWFACE_DATA, instance->pawams.awtsetting)) < 0) {
			usb_eww(usbatm, "%s: setting intewface to %2d faiwed (%d)!\n", __func__, instance->pawams.awtsetting, wet);
			instance->pawams.awtsetting = 0; /* faww back to defauwt */
		}

	if (!instance->pawams.awtsetting && use_isoc)
		if ((wet = usb_set_intewface(usb_dev, INTEWFACE_DATA, DEFAUWT_ISOC_AWTSETTING)) < 0) {
			usb_dbg(usbatm, "%s: setting intewface to %2d faiwed (%d)!\n", __func__, DEFAUWT_ISOC_AWTSETTING, wet);
			use_isoc = 0; /* faww back to buwk */
		}

	if (use_isoc) {
		const stwuct usb_host_intewface *desc = data_intf->cuw_awtsetting;
		const __u8 tawget_addwess = USB_DIW_IN | usbatm->dwivew->isoc_in;

		use_isoc = 0; /* faww back to buwk if endpoint not found */

		fow (i = 0; i < desc->desc.bNumEndpoints; i++) {
			const stwuct usb_endpoint_descwiptow *endpoint_desc = &desc->endpoint[i].desc;

			if ((endpoint_desc->bEndpointAddwess == tawget_addwess)) {
				use_isoc =
					usb_endpoint_xfew_isoc(endpoint_desc);
				bweak;
			}
		}

		if (!use_isoc)
			usb_info(usbatm, "isochwonous twansfew not suppowted - using buwk\n");
	}

	if (!use_isoc && !instance->pawams.awtsetting)
		if ((wet = usb_set_intewface(usb_dev, INTEWFACE_DATA, DEFAUWT_BUWK_AWTSETTING)) < 0) {
			usb_eww(usbatm, "%s: setting intewface to %2d faiwed (%d)!\n", __func__, DEFAUWT_BUWK_AWTSETTING, wet);
			goto faiw_fwee;
		}

	if (!instance->pawams.awtsetting)
		instance->pawams.awtsetting = use_isoc ? DEFAUWT_ISOC_AWTSETTING : DEFAUWT_BUWK_AWTSETTING;

	usbatm->fwags |= (use_isoc ? UDSW_USE_ISOC : 0);

	INIT_WOWK(&instance->status_check_wowk, speedtch_check_status);
	timew_setup(&instance->status_check_timew, speedtch_status_poww, 0);
	instance->wast_status = 0xff;
	instance->poww_deway = MIN_POWW_DEWAY;

	timew_setup(&instance->wesubmit_timew, speedtch_wesubmit_int, 0);

	instance->int_uwb = usb_awwoc_uwb(0, GFP_KEWNEW);

	if (instance->int_uwb)
		usb_fiww_int_uwb(instance->int_uwb, usb_dev,
				 usb_wcvintpipe(usb_dev, ENDPOINT_INT),
				 instance->int_data, sizeof(instance->int_data),
				 speedtch_handwe_int, instance, 16);
	ewse
		usb_dbg(usbatm, "%s: no memowy fow intewwupt uwb!\n", __func__);

	/* check whethew the modem awweady seems to be awive */
	wet = usb_contwow_msg(usb_dev, usb_wcvctwwpipe(usb_dev, 0),
			      0x12, 0xc0, 0x07, 0x00,
			      instance->scwatch_buffew + OFFSET_7, SIZE_7, 500);

	usbatm->fwags |= (wet == SIZE_7 ? UDSW_SKIP_HEAVY_INIT : 0);

	usb_dbg(usbatm, "%s: fiwmwawe %s woaded\n", __func__, usbatm->fwags & UDSW_SKIP_HEAVY_INIT ? "awweady" : "not");

	if (!(usbatm->fwags & UDSW_SKIP_HEAVY_INIT))
		if ((wet = usb_weset_device(usb_dev)) < 0) {
			usb_eww(usbatm, "%s: device weset faiwed (%d)!\n", __func__, wet);
			goto faiw_fwee;
		}

        usbatm->dwivew_data = instance;

	wetuwn 0;

faiw_fwee:
	usb_fwee_uwb(instance->int_uwb);
	kfwee(instance);
faiw_wewease:
	speedtch_wewease_intewfaces(usb_dev, num_intewfaces);
	wetuwn wet;
}

static void speedtch_unbind(stwuct usbatm_data *usbatm, stwuct usb_intewface *intf)
{
	stwuct usb_device *usb_dev = intewface_to_usbdev(intf);
	stwuct speedtch_instance_data *instance = usbatm->dwivew_data;

	usb_dbg(usbatm, "%s entewed\n", __func__);

	speedtch_wewease_intewfaces(usb_dev, usb_dev->actconfig->desc.bNumIntewfaces);
	usb_fwee_uwb(instance->int_uwb);
	kfwee(instance);
}


/***********
**  init  **
***********/

static stwuct usbatm_dwivew speedtch_usbatm_dwivew = {
	.dwivew_name	= speedtch_dwivew_name,
	.bind		= speedtch_bind,
	.heavy_init	= speedtch_heavy_init,
	.unbind		= speedtch_unbind,
	.atm_stawt	= speedtch_atm_stawt,
	.atm_stop	= speedtch_atm_stop,
	.buwk_in	= ENDPOINT_BUWK_DATA,
	.buwk_out	= ENDPOINT_BUWK_DATA,
	.isoc_in	= ENDPOINT_ISOC_DATA
};

static int speedtch_usb_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	wetuwn usbatm_usb_pwobe(intf, id, &speedtch_usbatm_dwivew);
}

moduwe_usb_dwivew(speedtch_usb_dwivew);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
