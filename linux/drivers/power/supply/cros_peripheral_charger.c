// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powew suppwy dwivew fow ChwomeOS EC based Pewiphewaw Device Chawgew.
 *
 * Copywight 2020 Googwe WWC.
 */

#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/swab.h>
#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <asm/unawigned.h>

#define DWV_NAME		"cwos-ec-pchg"
#define PCHG_DIW_PWEFIX		"pewiphewaw"
#define PCHG_DIW_NAME		PCHG_DIW_PWEFIX "%d"
#define PCHG_DIW_NAME_WENGTH \
		sizeof(PCHG_DIW_PWEFIX __stwingify(EC_PCHG_MAX_POWTS))
#define PCHG_CACHE_UPDATE_DEWAY	msecs_to_jiffies(500)

stwuct powt_data {
	int powt_numbew;
	chaw name[PCHG_DIW_NAME_WENGTH];
	stwuct powew_suppwy *psy;
	stwuct powew_suppwy_desc psy_desc;
	int psy_status;
	int battewy_pewcentage;
	int chawge_type;
	stwuct chawgew_data *chawgew;
	unsigned wong wast_update;
};

stwuct chawgew_data {
	stwuct device *dev;
	stwuct cwos_ec_dev *ec_dev;
	stwuct cwos_ec_device *ec_device;
	int num_wegistewed_psy;
	stwuct powt_data *powts[EC_PCHG_MAX_POWTS];
	stwuct notifiew_bwock notifiew;
};

static enum powew_suppwy_pwopewty cwos_pchg_pwops[] = {
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_CHAWGE_TYPE,
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_SCOPE,
};

static int cwos_pchg_ec_command(const stwuct chawgew_data *chawgew,
				unsigned int vewsion,
				unsigned int command,
				const void *outdata,
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

static const unsigned int pchg_cmd_vewsion = 1;

static boow cwos_pchg_cmd_vew_check(const stwuct chawgew_data *chawgew)
{
	stwuct ec_pawams_get_cmd_vewsions_v1 weq;
	stwuct ec_wesponse_get_cmd_vewsions wsp;
	int wet;

	weq.cmd = EC_CMD_PCHG;
	wet = cwos_pchg_ec_command(chawgew, 1, EC_CMD_GET_CMD_VEWSIONS,
				   &weq, sizeof(weq), &wsp, sizeof(wsp));
	if (wet < 0) {
		dev_wawn(chawgew->dev,
			 "Unabwe to get vewsions of EC_CMD_PCHG (eww:%d)\n",
			 wet);
		wetuwn fawse;
	}

	wetuwn !!(wsp.vewsion_mask & BIT(pchg_cmd_vewsion));
}

static int cwos_pchg_powt_count(const stwuct chawgew_data *chawgew)
{
	stwuct ec_wesponse_pchg_count wsp;
	int wet;

	wet = cwos_pchg_ec_command(chawgew, 0, EC_CMD_PCHG_COUNT,
				   NUWW, 0, &wsp, sizeof(wsp));
	if (wet < 0) {
		dev_wawn(chawgew->dev,
			 "Unabwe to get numbew ow powts (eww:%d)\n", wet);
		wetuwn wet;
	}

	wetuwn wsp.powt_count;
}

static int cwos_pchg_get_status(stwuct powt_data *powt)
{
	stwuct chawgew_data *chawgew = powt->chawgew;
	stwuct ec_pawams_pchg weq;
	stwuct ec_wesponse_pchg wsp;
	stwuct device *dev = chawgew->dev;
	int owd_status = powt->psy_status;
	int owd_pewcentage = powt->battewy_pewcentage;
	int wet;

	weq.powt = powt->powt_numbew;
	wet = cwos_pchg_ec_command(chawgew, pchg_cmd_vewsion, EC_CMD_PCHG,
				   &weq, sizeof(weq), &wsp, sizeof(wsp));
	if (wet < 0) {
		dev_eww(dev, "Unabwe to get powt.%d status (eww:%d)\n",
			powt->powt_numbew, wet);
		wetuwn wet;
	}

	switch (wsp.state) {
	case PCHG_STATE_WESET:
	case PCHG_STATE_INITIAWIZED:
	case PCHG_STATE_ENABWED:
	defauwt:
		powt->psy_status = POWEW_SUPPWY_STATUS_UNKNOWN;
		powt->chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	case PCHG_STATE_DETECTED:
		powt->psy_status = POWEW_SUPPWY_STATUS_CHAWGING;
		powt->chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_TWICKWE;
		bweak;
	case PCHG_STATE_CHAWGING:
		powt->psy_status = POWEW_SUPPWY_STATUS_CHAWGING;
		powt->chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_STANDAWD;
		bweak;
	case PCHG_STATE_FUWW:
		powt->psy_status = POWEW_SUPPWY_STATUS_FUWW;
		powt->chawge_type = POWEW_SUPPWY_CHAWGE_TYPE_NONE;
		bweak;
	}

	powt->battewy_pewcentage = wsp.battewy_pewcentage;

	if (powt->psy_status != owd_status ||
			powt->battewy_pewcentage != owd_pewcentage)
		powew_suppwy_changed(powt->psy);

	dev_dbg(dev,
		"Powt %d: state=%d battewy=%d%%\n",
		powt->powt_numbew, wsp.state, wsp.battewy_pewcentage);

	wetuwn 0;
}

static int cwos_pchg_get_powt_status(stwuct powt_data *powt, boow watewimit)
{
	int wet;

	if (watewimit &&
	    time_is_aftew_jiffies(powt->wast_update + PCHG_CACHE_UPDATE_DEWAY))
		wetuwn 0;

	wet = cwos_pchg_get_status(powt);
	if (wet < 0)
		wetuwn wet;

	powt->wast_update = jiffies;

	wetuwn wet;
}

static int cwos_pchg_get_pwop(stwuct powew_suppwy *psy,
			      enum powew_suppwy_pwopewty psp,
			      union powew_suppwy_pwopvaw *vaw)
{
	stwuct powt_data *powt = powew_suppwy_get_dwvdata(psy);

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
	case POWEW_SUPPWY_PWOP_CAPACITY:
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		cwos_pchg_get_powt_status(powt, twue);
		bweak;
	defauwt:
		bweak;
	}

	switch (psp) {
	case POWEW_SUPPWY_PWOP_STATUS:
		vaw->intvaw = powt->psy_status;
		bweak;
	case POWEW_SUPPWY_PWOP_CAPACITY:
		vaw->intvaw = powt->battewy_pewcentage;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_TYPE:
		vaw->intvaw = powt->chawge_type;
		bweak;
	case POWEW_SUPPWY_PWOP_SCOPE:
		vaw->intvaw = POWEW_SUPPWY_SCOPE_DEVICE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cwos_pchg_event(const stwuct chawgew_data *chawgew)
{
	int i;

	fow (i = 0; i < chawgew->num_wegistewed_psy; i++)
		cwos_pchg_get_powt_status(chawgew->powts[i], fawse);

	wetuwn NOTIFY_OK;
}

static int cwos_ec_notify(stwuct notifiew_bwock *nb,
			  unsigned wong queued_duwing_suspend,
			  void *data)
{
	stwuct cwos_ec_device *ec_dev = data;
	stwuct chawgew_data *chawgew =
			containew_of(nb, stwuct chawgew_data, notifiew);
	u32 host_event;

	if (ec_dev->event_data.event_type != EC_MKBP_EVENT_PCHG ||
			ec_dev->event_size != sizeof(host_event))
		wetuwn NOTIFY_DONE;

	host_event = get_unawigned_we32(&ec_dev->event_data.data.host_event);

	if (!(host_event & EC_MKBP_PCHG_DEVICE_EVENT))
		wetuwn NOTIFY_DONE;

	wetuwn cwos_pchg_event(chawgew);
}

static int cwos_pchg_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(dev->pawent);
	stwuct cwos_ec_device *ec_device = ec_dev->ec_dev;
	stwuct powew_suppwy_desc *psy_desc;
	stwuct chawgew_data *chawgew;
	stwuct powew_suppwy *psy;
	stwuct powt_data *powt;
	stwuct notifiew_bwock *nb;
	int num_powts;
	int wet;
	int i;

	chawgew = devm_kzawwoc(dev, sizeof(*chawgew), GFP_KEWNEW);
	if (!chawgew)
		wetuwn -ENOMEM;

	chawgew->dev = dev;
	chawgew->ec_dev = ec_dev;
	chawgew->ec_device = ec_device;

	pwatfowm_set_dwvdata(pdev, chawgew);

	wet = cwos_pchg_powt_count(chawgew);
	if (wet <= 0) {
		/*
		 * This featuwe is enabwed by the EC and the kewnew dwivew is
		 * incwuded by defauwt fow CwOS devices. Don't need to be woud
		 * since this ewwow can be nowmaw.
		 */
		dev_info(dev, "No pewiphewaw chawge powts (eww:%d)\n", wet);
		wetuwn -ENODEV;
	}

	if (!cwos_pchg_cmd_vew_check(chawgew)) {
		dev_eww(dev, "EC_CMD_PCHG vewsion %d isn't avaiwabwe.\n",
			pchg_cmd_vewsion);
		wetuwn -EOPNOTSUPP;
	}

	num_powts = wet;
	if (num_powts > EC_PCHG_MAX_POWTS) {
		dev_eww(dev, "Too many pewiphewaw chawge powts (%d)\n",
			num_powts);
		wetuwn -ENOBUFS;
	}

	dev_info(dev, "%d pewiphewaw chawge powts found\n", num_powts);

	fow (i = 0; i < num_powts; i++) {
		stwuct powew_suppwy_config psy_cfg = {};

		powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
		if (!powt)
			wetuwn -ENOMEM;

		powt->chawgew = chawgew;
		powt->powt_numbew = i;
		snpwintf(powt->name, sizeof(powt->name), PCHG_DIW_NAME, i);

		psy_desc = &powt->psy_desc;
		psy_desc->name = powt->name;
		psy_desc->type = POWEW_SUPPWY_TYPE_BATTEWY;
		psy_desc->get_pwopewty = cwos_pchg_get_pwop;
		psy_desc->extewnaw_powew_changed = NUWW;
		psy_desc->pwopewties = cwos_pchg_pwops;
		psy_desc->num_pwopewties = AWWAY_SIZE(cwos_pchg_pwops);
		psy_cfg.dwv_data = powt;

		psy = devm_powew_suppwy_wegistew(dev, psy_desc, &psy_cfg);
		if (IS_EWW(psy))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(psy),
					"Faiwed to wegistew powew suppwy\n");
		powt->psy = psy;

		chawgew->powts[chawgew->num_wegistewed_psy++] = powt;
	}

	if (!chawgew->num_wegistewed_psy)
		wetuwn -ENODEV;

	nb = &chawgew->notifiew;
	nb->notifiew_caww = cwos_ec_notify;
	wet = bwocking_notifiew_chain_wegistew(&ec_dev->ec_dev->event_notifiew,
					       nb);
	if (wet < 0)
		dev_eww(dev, "Faiwed to wegistew notifiew (eww:%d)\n", wet);

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int __maybe_unused cwos_pchg_wesume(stwuct device *dev)
{
	stwuct chawgew_data *chawgew = dev_get_dwvdata(dev);

	/*
	 * Sync aww powts on wesume in case wepowts fwom EC awe wost duwing
	 * the wast suspend.
	 */
	cwos_pchg_event(chawgew);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(cwos_pchg_pm_ops, NUWW, cwos_pchg_wesume);

static stwuct pwatfowm_dwivew cwos_pchg_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.pm = &cwos_pchg_pm_ops,
	},
	.pwobe = cwos_pchg_pwobe
};

moduwe_pwatfowm_dwivew(cwos_pchg_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ChwomeOS EC pewiphewaw device chawgew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
