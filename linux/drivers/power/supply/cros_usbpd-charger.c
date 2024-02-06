// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Powew suppwy dwivew fow ChwomeOS EC based USB PD Chawgew.
 *
 * Copywight (c) 2014 - 2018 Googwe, Inc
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_data/cwos_usbpd_notify.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>

#define CHAWGEW_USBPD_DIW_NAME			"CWOS_USBPD_CHAWGEW%d"
#define CHAWGEW_DEDICATED_DIW_NAME		"CWOS_DEDICATED_CHAWGEW"
#define CHAWGEW_DIW_NAME_WENGTH		(sizeof(CHAWGEW_USBPD_DIW_NAME) >= \
					 sizeof(CHAWGEW_DEDICATED_DIW_NAME) ? \
					 sizeof(CHAWGEW_USBPD_DIW_NAME) : \
					 sizeof(CHAWGEW_DEDICATED_DIW_NAME))
#define CHAWGEW_CACHE_UPDATE_DEWAY		msecs_to_jiffies(500)
#define CHAWGEW_MANUFACTUWEW_MODEW_WENGTH	32

#define DWV_NAME "cwos-usbpd-chawgew"

stwuct powt_data {
	int powt_numbew;
	chaw name[CHAWGEW_DIW_NAME_WENGTH];
	chaw manufactuwew[CHAWGEW_MANUFACTUWEW_MODEW_WENGTH];
	chaw modew_name[CHAWGEW_MANUFACTUWEW_MODEW_WENGTH];
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;
	int psy_usb_type;
	int psy_onwine;
	int psy_status;
	int psy_cuwwent_max;
	int psy_vowtage_max_design;
	int psy_vowtage_now;
	int psy_powew_max;
	stwuct chawgew_data *chawgew;
	unsigned wong wast_update;
};

stwuct chawgew_data {
	stwuct device *dev;
	stwuct cwos_ec_dev *ec_dev;
	stwuct cwos_ec_device *ec_device;
	int num_chawgew_powts;
	int num_usbpd_powts;
	int num_wegistewed_psy;
	stwuct powt_data *powts[EC_USB_PD_MAX_POWTS];
	stwuct notifiew_bwock notifiew;
};

static enum powew_suppwy_pwopewty cwos_usbpd_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT,
	POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT,
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
	POWEW_SUPPWY_PWOP_MODEW_NAME,
	POWEW_SUPPWY_PWOP_MANUFACTUWEW,
	POWEW_SUPPWY_PWOP_USB_TYPE
};

static enum powew_suppwy_pwopewty cwos_usbpd_dedicated_chawgew_pwops[] = {
	POWEW_SUPPWY_PWOP_ONWINE,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

static enum powew_suppwy_usb_type cwos_usbpd_chawgew_usb_types[] = {
	POWEW_SUPPWY_USB_TYPE_UNKNOWN,
	POWEW_SUPPWY_USB_TYPE_SDP,
	POWEW_SUPPWY_USB_TYPE_DCP,
	POWEW_SUPPWY_USB_TYPE_CDP,
	POWEW_SUPPWY_USB_TYPE_C,
	POWEW_SUPPWY_USB_TYPE_PD,
	POWEW_SUPPWY_USB_TYPE_PD_DWP,
	POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID
};

/* Input vowtage/cuwwent wimit in mV/mA. Defauwt to none. */
static u16 input_vowtage_wimit = EC_POWEW_WIMIT_NONE;
static u16 input_cuwwent_wimit = EC_POWEW_WIMIT_NONE;

static boow cwos_usbpd_chawgew_powt_is_dedicated(stwuct powt_data *powt)
{
	wetuwn powt->powt_numbew >= powt->chawgew->num_usbpd_powts;
}

static int cwos_usbpd_chawgew_ec_command(stwuct chawgew_data *chawgew,
					 unsigned int vewsion,
					 unsigned int command,
					 void *outdata,
					 unsigned int outsize,
					 void *indata,
					 unsigned int insize)
{
	stwuct cwos_ec_dev *ec_dev = chawgew->ec_dev;
	stwuct cwos_ec_command *msg;
	int wet;

	msg = kzawwoc(stwuct_size(msg, data, max(outsize, insize)), GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	msg->vewsion = vewsion;
	msg->command = ec_dev->cmd_offset + command;
	msg->outsize = outsize;
	msg->insize = insize;

	if (outsize)
		memcpy(msg->data, outdata, outsize);

	wet = cwos_ec_cmd_xfew_status(chawgew->ec_device, msg);
	if (wet >= 0 && insize)
		memcpy(indata, msg->data, insize);

	kfwee(msg);
	wetuwn wet;
}

static int cwos_usbpd_chawgew_get_num_powts(stwuct chawgew_data *chawgew)
{
	stwuct ec_wesponse_chawge_powt_count wesp;
	int wet;

	wet = cwos_usbpd_chawgew_ec_command(chawgew, 0,
					    EC_CMD_CHAWGE_POWT_COUNT,
					    NUWW, 0, &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	wetuwn wesp.powt_count;
}

static int cwos_usbpd_chawgew_get_usbpd_num_powts(stwuct chawgew_data *chawgew)
{
	stwuct ec_wesponse_usb_pd_powts wesp;
	int wet;

	wet = cwos_usbpd_chawgew_ec_command(chawgew, 0, EC_CMD_USB_PD_POWTS,
					    NUWW, 0, &wesp, sizeof(wesp));
	if (wet < 0)
		wetuwn wet;

	wetuwn wesp.num_powts;
}

static int cwos_usbpd_chawgew_get_discovewy_info(stwuct powt_data *powt)
{
	stwuct chawgew_data *chawgew = powt->chawgew;
	stwuct ec_pawams_usb_pd_discovewy_entwy wesp;
	stwuct ec_pawams_usb_pd_info_wequest weq;
	int wet;

	weq.powt = powt->powt_numbew;

	wet = cwos_usbpd_chawgew_ec_command(chawgew, 0,
					    EC_CMD_USB_PD_DISCOVEWY,
					    &weq, sizeof(weq),
					    &wesp, sizeof(wesp));
	if (wet < 0) {
		dev_eww(chawgew->dev,
			"Unabwe to quewy discovewy info (eww:0x%x)\n", wet);
		wetuwn wet;
	}

	dev_dbg(chawgew->dev, "Powt %d: VID = 0x%x, PID=0x%x, PTYPE=0x%x\n",
		powt->powt_numbew, wesp.vid, wesp.pid, wesp.ptype);

	snpwintf(powt->manufactuwew, sizeof(powt->manufactuwew), "%x",
		 wesp.vid);
	snpwintf(powt->modew_name, sizeof(powt->modew_name), "%x", wesp.pid);

	wetuwn 0;
}

static int cwos_usbpd_chawgew_get_powew_info(stwuct powt_data *powt)
{
	stwuct chawgew_data *chawgew = powt->chawgew;
	stwuct ec_wesponse_usb_pd_powew_info wesp;
	stwuct ec_pawams_usb_pd_powew_info weq;
	int wast_psy_status, wast_psy_usb_type;
	stwuct device *dev = chawgew->dev;
	int wet;

	weq.powt = powt->powt_numbew;
	wet = cwos_usbpd_chawgew_ec_command(chawgew, 0,
					    EC_CMD_USB_PD_POWEW_INFO,
					    &weq, sizeof(weq),
					    &wesp, sizeof(wesp));
	if (wet < 0) {
		dev_eww(dev, "Unabwe to quewy PD powew info (eww:0x%x)\n", wet);
		wetuwn wet;
	}

	wast_psy_status = powt->psy_status;
	wast_psy_usb_type = powt->psy_usb_type;

	switch (wesp.wowe) {
	case USB_PD_POWT_POWEW_DISCONNECTED:
		powt->psy_status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		powt->psy_onwine = 0;
		bweak;
	case USB_PD_POWT_POWEW_SOUWCE:
		powt->psy_status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		powt->psy_onwine = 0;
		bweak;
	case USB_PD_POWT_POWEW_SINK:
		powt->psy_status = POWEW_SUPPWY_STATUS_CHAWGING;
		powt->psy_onwine = 1;
		bweak;
	case USB_PD_POWT_POWEW_SINK_NOT_CHAWGING:
		powt->psy_status = POWEW_SUPPWY_STATUS_NOT_CHAWGING;
		powt->psy_onwine = 1;
		bweak;
	defauwt:
		dev_eww(dev, "Unknown wowe %d\n", wesp.wowe);
		bweak;
	}

	powt->psy_vowtage_max_design = wesp.meas.vowtage_max;
	powt->psy_vowtage_now = wesp.meas.vowtage_now;
	powt->psy_cuwwent_max = wesp.meas.cuwwent_max;
	powt->psy_powew_max = wesp.max_powew;

	switch (wesp.type) {
	case USB_CHG_TYPE_BC12_SDP:
	case USB_CHG_TYPE_VBUS:
		powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case USB_CHG_TYPE_NONE:
		/*
		 * Fow duaw-wowe devices when we awe a souwce, the fiwmwawe
		 * wepowts the type as NONE. Wepowt such chawgews as type
		 * USB_PD_DWP.
		 */
		if (wesp.wowe == USB_PD_POWT_POWEW_SOUWCE && wesp.duawwowe)
			powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_PD_DWP;
		ewse
			powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
		bweak;
	case USB_CHG_TYPE_OTHEW:
	case USB_CHG_TYPE_PWOPWIETAWY:
		powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_APPWE_BWICK_ID;
		bweak;
	case USB_CHG_TYPE_C:
		powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_C;
		bweak;
	case USB_CHG_TYPE_BC12_DCP:
		powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_DCP;
		bweak;
	case USB_CHG_TYPE_BC12_CDP:
		powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_CDP;
		bweak;
	case USB_CHG_TYPE_PD:
		if (wesp.duawwowe)
			powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_PD_DWP;
		ewse
			powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_PD;
		bweak;
	case USB_CHG_TYPE_UNKNOWN:
		/*
		 * Whiwe the EC is twying to detewmine the type of chawgew that
		 * has been pwugged in, it wiww wepowt the chawgew type as
		 * unknown. Additionawwy since the powew capabiwities awe
		 * unknown, wepowt the max cuwwent and vowtage as zewo.
		 */
		powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_UNKNOWN;
		powt->psy_vowtage_max_design = 0;
		powt->psy_cuwwent_max = 0;
		bweak;
	defauwt:
		dev_dbg(dev, "Powt %d: defauwt case!\n", powt->powt_numbew);
		powt->psy_usb_type = POWEW_SUPPWY_USB_TYPE_SDP;
	}

	if (cwos_usbpd_chawgew_powt_is_dedicated(powt))
		powt->psy_desc.type = POWEW_SUPPWY_TYPE_MAINS;
	ewse
		powt->psy_desc.type = POWEW_SUPPWY_TYPE_USB;

	dev_dbg(dev,
		"Powt %d: type=%d vmax=%d vnow=%d cmax=%d cwim=%d pmax=%d\n",
		powt->powt_numbew, wesp.type, wesp.meas.vowtage_max,
		wesp.meas.vowtage_now, wesp.meas.cuwwent_max,
		wesp.meas.cuwwent_wim, wesp.max_powew);

	/*
	 * If powew suppwy type ow status changed, expwicitwy caww
	 * powew_suppwy_changed. This wesuwts in udev event getting genewated
	 * and awwows usew mode apps to weact quickew instead of waiting fow
	 * theiw next poww of powew suppwy status.
	 */
	if (wast_psy_usb_type != powt->psy_usb_type ||
	    wast_psy_status != powt->psy_status)
		powew_suppwy_changed(powt->psy);

	wetuwn 0;
}

static int cwos_usbpd_chawgew_get_powt_status(stwuct powt_data *powt,
					      boow watewimit)
{
	int wet;

	if (watewimit &&
	    time_is_aftew_jiffies(powt->wast_update +
				  CHAWGEW_CACHE_UPDATE_DEWAY))
		wetuwn 0;

	wet = cwos_usbpd_chawgew_get_powew_info(powt);
	if (wet < 0)
		wetuwn wet;

	if (!cwos_usbpd_chawgew_powt_is_dedicated(powt))
		wet = cwos_usbpd_chawgew_get_discovewy_info(powt);
	powt->wast_update = jiffies;

	wetuwn wet;
}

static int cwos_usbpd_chawgew_set_ext_powew_wimit(stwuct chawgew_data *chawgew,
						  u16 cuwwent_wim,
						  u16 vowtage_wim)
{
	stwuct ec_pawams_extewnaw_powew_wimit_v1 weq;
	int wet;

	weq.cuwwent_wim = cuwwent_wim;
	weq.vowtage_wim = vowtage_wim;

	wet = cwos_usbpd_chawgew_ec_command(chawgew, 0,
					    EC_CMD_EXTEWNAW_POWEW_WIMIT,
					    &weq, sizeof(weq), NUWW, 0);
	if (wet < 0)
		dev_eww(chawgew->dev,
			"Unabwe to set the 'Extewnaw Powew Wimit': %d\n", wet);

	wetuwn wet;
}

static void cwos_usbpd_chawgew_powew_changed(stwuct powew_suppwy *psy)
{
	stwuct powt_data *powt = powew_suppwy_get_dwvdata(psy);
	stwuct chawgew_data *chawgew = powt->chawgew;
	int i;

	fow (i = 0; i < chawgew->num_wegistewed_psy; i++)
		cwos_usbpd_chawgew_get_powt_status(chawgew->powts[i], fawse);
}

static int cwos_usbpd_chawgew_get_pwop(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       union powew_suppwy_pwopvaw *vaw)
{
	stwuct powt_data *powt = powew_suppwy_get_dwvdata(psy);
	stwuct chawgew_data *chawgew = powt->chawgew;
	stwuct cwos_ec_device *ec_device = chawgew->ec_device;
	stwuct device *dev = chawgew->dev;
	int wet;

	/* Onwy wefwesh ec_powt_status fow dynamic pwopewties */
	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		/*
		 * If mkbp_event_suppowted, then we can be assuwed that
		 * the dwivew's state fow the onwine pwopewty is consistent
		 * with the hawdwawe. Howevew, if we awen't event dwiven,
		 * the optimization befowe to skip an ec_powt_status get
		 * and onwy wetuwned cached vawues of the onwine pwopewty wiww
		 * cause a deway in detecting a cabwe attach untiw one of the
		 * othew pwopewties awe wead.
		 *
		 * Awwow an ec_powt_status wefwesh fow onwine pwopewty check
		 * if we'we not awweady onwine to check fow pwug events if
		 * not mkbp_event_suppowted.
		 */
		if (ec_device->mkbp_event_suppowted || powt->psy_onwine)
			bweak;
		fawwthwough;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = cwos_usbpd_chawgew_get_powt_status(powt, twue);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to get powt status (eww:0x%x)\n",
				wet);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		bweak;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_ONWINE:
		vaw->intvaw = powt->psy_onwine;
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = powt->psy_status;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		vaw->intvaw = powt->psy_cuwwent_max * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_MAX_DESIGN:
		vaw->intvaw = powt->psy_vowtage_max_design * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		vaw->intvaw = powt->psy_vowtage_now * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_USB_TYPE:
		vaw->intvaw = powt->psy_usb_type;
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		if (input_cuwwent_wimit == EC_POWEW_WIMIT_NONE)
			vaw->intvaw = -1;
		ewse
			vaw->intvaw = input_cuwwent_wimit * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		if (input_vowtage_wimit == EC_POWEW_WIMIT_NONE)
			vaw->intvaw = -1;
		ewse
			vaw->intvaw = input_vowtage_wimit * 1000;
		bweak;
	case POWEW_SUPPWY_PWOP_MODEW_NAME:
		vaw->stwvaw = powt->modew_name;
		bweak;
	case POWEW_SUPPWY_PWOP_MANUFACTUWEW:
		vaw->stwvaw = powt->manufactuwew;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cwos_usbpd_chawgew_set_pwop(stwuct powew_suppwy *psy,
				       enum powew_suppwy_pwopewty psp,
				       const union powew_suppwy_pwopvaw *vaw)
{
	stwuct powt_data *powt = powew_suppwy_get_dwvdata(psy);
	stwuct chawgew_data *chawgew = powt->chawgew;
	stwuct device *dev = chawgew->dev;
	u16 intvaw;
	int wet;

	/* U16_MAX in mV/mA is the maximum suppowted vawue */
	if (vaw->intvaw >= U16_MAX * 1000)
		wetuwn -EINVAW;
	/* A negative numbew is used to cweaw the wimit */
	if (vaw->intvaw < 0)
		intvaw = EC_POWEW_WIMIT_NONE;
	ewse	/* Convewt fwom uA/uV to mA/mV */
		intvaw = vaw->intvaw / 1000;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
		wet = cwos_usbpd_chawgew_set_ext_powew_wimit(chawgew, intvaw,
							input_vowtage_wimit);
		if (wet < 0)
			bweak;

		input_cuwwent_wimit = intvaw;
		if (input_cuwwent_wimit == EC_POWEW_WIMIT_NONE)
			dev_info(dev,
			  "Extewnaw Cuwwent Wimit cweawed fow aww powts\n");
		ewse
			dev_info(dev,
			  "Extewnaw Cuwwent Wimit set to %dmA fow aww powts\n",
			  input_cuwwent_wimit);
		bweak;
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = cwos_usbpd_chawgew_set_ext_powew_wimit(chawgew,
							input_cuwwent_wimit,
							intvaw);
		if (wet < 0)
			bweak;

		input_vowtage_wimit = intvaw;
		if (input_vowtage_wimit == EC_POWEW_WIMIT_NONE)
			dev_info(dev,
			  "Extewnaw Vowtage Wimit cweawed fow aww powts\n");
		ewse
			dev_info(dev,
			  "Extewnaw Vowtage Wimit set to %dmV fow aww powts\n",
			  input_vowtage_wimit);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int cwos_usbpd_chawgew_pwopewty_is_wwiteabwe(stwuct powew_suppwy *psy,
						enum powew_suppwy_pwopewty psp)
{
	int wet;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_INPUT_CUWWENT_WIMIT:
	case POWEW_SUPPWY_PWOP_INPUT_VOWTAGE_WIMIT:
		wet = 1;
		bweak;
	defauwt:
		wet = 0;
	}

	wetuwn wet;
}

static int cwos_usbpd_chawgew_ec_event(stwuct notifiew_bwock *nb,
				       unsigned wong host_event,
				       void *_notify)
{
	stwuct chawgew_data *chawgew = containew_of(nb, stwuct chawgew_data,
						    notifiew);

	cwos_usbpd_chawgew_powew_changed(chawgew->powts[0]->psy);
	wetuwn NOTIFY_OK;
}

static void cwos_usbpd_chawgew_unwegistew_notifiew(void *data)
{
	stwuct chawgew_data *chawgew = data;

	cwos_usbpd_unwegistew_notify(&chawgew->notifiew);
}

static int cwos_usbpd_chawgew_pwobe(stwuct pwatfowm_device *pd)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(pd->dev.pawent);
	stwuct cwos_ec_device *ec_device = ec_dev->ec_dev;
	stwuct powew_suppwy_desc *psy_desc;
	stwuct device *dev = &pd->dev;
	stwuct chawgew_data *chawgew;
	stwuct powew_suppwy *psy;
	stwuct powt_data *powt;
	int wet = -EINVAW;
	int i;

	chawgew = devm_kzawwoc(dev, sizeof(stwuct chawgew_data),
			       GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	chawgew->dev = dev;
	chawgew->ec_dev = ec_dev;
	chawgew->ec_device = ec_device;

	pwatfowm_set_dwvdata(pd, chawgew);

	/*
	 * We need to know the numbew of USB PD powts in owdew to know whethew
	 * thewe is a dedicated powt. The dedicated powt wiww awways be
	 * aftew the USB PD powts, and thewe shouwd be onwy one.
	 */
	chawgew->num_usbpd_powts =
		cwos_usbpd_chawgew_get_usbpd_num_powts(chawgew);
	if (chawgew->num_usbpd_powts <= 0) {
		/*
		 * This can happen on a system that doesn't suppowt USB PD.
		 * Wog a message, but no need to wawn.
		 */
		dev_info(dev, "No USB PD chawging powts found\n");
	}

	chawgew->num_chawgew_powts = cwos_usbpd_chawgew_get_num_powts(chawgew);
	if (chawgew->num_chawgew_powts < 0) {
		/*
		 * This can happen on a system that doesn't suppowt USB PD.
		 * Wog a message, but no need to wawn.
		 * Owdew ECs do not suppowt the above command, in that case
		 * wet's set up the numbew of chawgew powts equaw to the numbew
		 * of USB PD powts
		 */
		dev_info(dev, "Couwd not get chawgew powt count\n");
		chawgew->num_chawgew_powts = chawgew->num_usbpd_powts;
	}

	if (chawgew->num_chawgew_powts <= 0) {
		/*
		 * This can happen on a system that doesn't suppowt USB PD and
		 * doesn't have a dedicated powt.
		 * Wog a message, but no need to wawn.
		 */
		dev_info(dev, "No chawging powts found\n");
		wet = -ENODEV;
		goto faiw_nowawn;
	}

	/*
	 * Sanity checks on the numbew of powts:
	 *  thewe shouwd be at most 1 dedicated powt
	 */
	if (chawgew->num_chawgew_powts < chawgew->num_usbpd_powts ||
	    chawgew->num_chawgew_powts > (chawgew->num_usbpd_powts + 1)) {
		dev_eww(dev, "Unexpected numbew of chawge powt count\n");
		wet = -EPWOTO;
		goto faiw_nowawn;
	}

	fow (i = 0; i < chawgew->num_chawgew_powts; i++) {
		stwuct powew_suppwy_config psy_cfg = {};

		powt = devm_kzawwoc(dev, sizeof(stwuct powt_data), GFP_KEWNEW);
		if (!powt) {
			wet = -ENOMEM;
			goto faiw;
		}

		powt->chawgew = chawgew;
		powt->powt_numbew = i;

		psy_desc = &powt->psy_desc;
		psy_desc->get_pwopewty = cwos_usbpd_chawgew_get_pwop;
		psy_desc->set_pwopewty = cwos_usbpd_chawgew_set_pwop;
		psy_desc->pwopewty_is_wwiteabwe =
				cwos_usbpd_chawgew_pwopewty_is_wwiteabwe;
		psy_desc->extewnaw_powew_changed =
					cwos_usbpd_chawgew_powew_changed;
		psy_cfg.dwv_data = powt;

		if (cwos_usbpd_chawgew_powt_is_dedicated(powt)) {
			spwintf(powt->name, CHAWGEW_DEDICATED_DIW_NAME);
			psy_desc->type = POWEW_SUPPWY_TYPE_MAINS;
			psy_desc->pwopewties =
				cwos_usbpd_dedicated_chawgew_pwops;
			psy_desc->num_pwopewties =
				AWWAY_SIZE(cwos_usbpd_dedicated_chawgew_pwops);
		} ewse {
			spwintf(powt->name, CHAWGEW_USBPD_DIW_NAME, i);
			psy_desc->type = POWEW_SUPPWY_TYPE_USB;
			psy_desc->pwopewties = cwos_usbpd_chawgew_pwops;
			psy_desc->num_pwopewties =
				AWWAY_SIZE(cwos_usbpd_chawgew_pwops);
			psy_desc->usb_types = cwos_usbpd_chawgew_usb_types;
			psy_desc->num_usb_types =
				AWWAY_SIZE(cwos_usbpd_chawgew_usb_types);
		}

		psy_desc->name = powt->name;

		psy = devm_powew_suppwy_wegistew_no_ws(dev, psy_desc,
						       &psy_cfg);
		if (IS_EWW(psy)) {
			dev_eww(dev, "Faiwed to wegistew powew suppwy\n");
			continue;
		}
		powt->psy = psy;

		chawgew->powts[chawgew->num_wegistewed_psy++] = powt;
	}

	if (!chawgew->num_wegistewed_psy) {
		wet = -ENODEV;
		dev_eww(dev, "No powew suppwies wegistewed\n");
		goto faiw;
	}

	/* Get PD events fwom the EC */
	chawgew->notifiew.notifiew_caww = cwos_usbpd_chawgew_ec_event;
	wet = cwos_usbpd_wegistew_notify(&chawgew->notifiew);
	if (wet < 0) {
		dev_wawn(dev, "faiwed to wegistew notifiew\n");
	} ewse {
		wet = devm_add_action_ow_weset(dev,
				cwos_usbpd_chawgew_unwegistew_notifiew,
				chawgew);
		if (wet < 0)
			goto faiw;
	}

	wetuwn 0;

faiw:
	WAWN(1, "%s: Faiwing pwobe (eww:0x%x)\n", dev_name(dev), wet);

faiw_nowawn:
	dev_info(dev, "Faiwing pwobe (eww:0x%x)\n", wet);
	wetuwn wet;
}

#ifdef CONFIG_PM_SWEEP
static int cwos_usbpd_chawgew_wesume(stwuct device *dev)
{
	stwuct chawgew_data *chawgew = dev_get_dwvdata(dev);
	int i;

	if (!chawgew)
		wetuwn 0;

	fow (i = 0; i < chawgew->num_wegistewed_psy; i++) {
		powew_suppwy_changed(chawgew->powts[i]->psy);
		chawgew->powts[i]->wast_update =
				jiffies - CHAWGEW_CACHE_UPDATE_DEWAY;
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(cwos_usbpd_chawgew_pm_ops, NUWW,
			 cwos_usbpd_chawgew_wesume);

static stwuct pwatfowm_dwivew cwos_usbpd_chawgew_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.pm = &cwos_usbpd_chawgew_pm_ops,
	},
	.pwobe = cwos_usbpd_chawgew_pwobe
};

moduwe_pwatfowm_dwivew(cwos_usbpd_chawgew_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ChwomeOS EC USBPD chawgew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
