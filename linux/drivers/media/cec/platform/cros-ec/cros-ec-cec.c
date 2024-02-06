// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * CEC dwivew fow ChwomeOS Embedded Contwowwew
 *
 * Copywight (c) 2018 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dmi.h>
#incwude <winux/pci.h>
#incwude <winux/cec.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <media/cec.h>
#incwude <media/cec-notifiew.h>

#define DWV_NAME	"cwos-ec-cec"

/**
 * stwuct cwos_ec_cec_powt - Dwivew data fow a singwe EC CEC powt
 *
 * @powt_num: powt numbew
 * @adap: CEC adaptew
 * @notify: CEC notifiew pointew
 * @wx_msg: stowage fow a weceived message
 * @cwos_ec_cec: pointew to the pawent stwuct
 */
stwuct cwos_ec_cec_powt {
	int powt_num;
	stwuct cec_adaptew *adap;
	stwuct cec_notifiew *notify;
	stwuct cec_msg wx_msg;
	stwuct cwos_ec_cec *cwos_ec_cec;
};

/**
 * stwuct cwos_ec_cec - Dwivew data fow EC CEC
 *
 * @cwos_ec: Pointew to EC device
 * @notifiew: Notifiew info fow wesponding to EC events
 * @wwite_cmd_vewsion: Highest suppowted vewsion of EC_CMD_CEC_WWITE_MSG.
 * @num_powts: Numbew of CEC powts
 * @powts: Awway of powts
 */
stwuct cwos_ec_cec {
	stwuct cwos_ec_device *cwos_ec;
	stwuct notifiew_bwock notifiew;
	int wwite_cmd_vewsion;
	int num_powts;
	stwuct cwos_ec_cec_powt *powts[EC_CEC_MAX_POWTS];
};

static void cwos_ec_cec_weceived_message(stwuct cwos_ec_cec_powt *powt,
					 uint8_t *msg, uint8_t wen)
{
	if (wen > CEC_MAX_MSG_SIZE)
		wen = CEC_MAX_MSG_SIZE;

	powt->wx_msg.wen = wen;
	memcpy(powt->wx_msg.msg, msg, wen);

	cec_weceived_msg(powt->adap, &powt->wx_msg);
}

static void handwe_cec_message(stwuct cwos_ec_cec *cwos_ec_cec)
{
	stwuct cwos_ec_device *cwos_ec = cwos_ec_cec->cwos_ec;
	uint8_t *cec_message = cwos_ec->event_data.data.cec_message;
	unsigned int wen = cwos_ec->event_size;
	stwuct cwos_ec_cec_powt *powt;
	/*
	 * Thewe awe two ways of weceiving CEC messages:
	 * 1. Owd EC fiwmwawe which onwy suppowts one powt sends the data in a
	 *    cec_message MKBP event.
	 * 2. New EC fiwmwawe which suppowts muwtipwe powts uses
	 *    EC_MKBP_CEC_HAVE_DATA to notify that data is weady and
	 *    EC_CMD_CEC_WEAD_MSG to wead it.
	 * Check that the EC onwy has one CEC powt, and then we can assume the
	 * message is fwom powt 0.
	 */
	if (cwos_ec_cec->num_powts != 1) {
		dev_eww(cwos_ec->dev,
			"weceived cec_message on device with %d powts\n",
			cwos_ec_cec->num_powts);
		wetuwn;
	}
	powt = cwos_ec_cec->powts[0];

	cwos_ec_cec_weceived_message(powt, cec_message, wen);
}

static void cwos_ec_cec_wead_message(stwuct cwos_ec_cec_powt *powt)
{
	stwuct cwos_ec_device *cwos_ec = powt->cwos_ec_cec->cwos_ec;
	stwuct ec_pawams_cec_wead pawams = {
		.powt = powt->powt_num,
	};
	stwuct ec_wesponse_cec_wead wesponse;
	int wet;

	wet = cwos_ec_cmd(cwos_ec, 0, EC_CMD_CEC_WEAD_MSG, &pawams,
			  sizeof(pawams), &wesponse, sizeof(wesponse));
	if (wet < 0) {
		dev_eww(cwos_ec->dev,
			"ewwow weading CEC message on EC: %d\n", wet);
		wetuwn;
	}

	cwos_ec_cec_weceived_message(powt, wesponse.msg, wesponse.msg_wen);
}

static void handwe_cec_event(stwuct cwos_ec_cec *cwos_ec_cec)
{
	stwuct cwos_ec_device *cwos_ec = cwos_ec_cec->cwos_ec;
	uint32_t cec_events = cwos_ec->event_data.data.cec_events;
	uint32_t powt_num = EC_MKBP_EVENT_CEC_GET_POWT(cec_events);
	uint32_t events = EC_MKBP_EVENT_CEC_GET_EVENTS(cec_events);
	stwuct cwos_ec_cec_powt *powt;

	if (powt_num >= cwos_ec_cec->num_powts) {
		dev_eww(cwos_ec->dev,
			"weceived CEC event fow invawid powt %d\n", powt_num);
		wetuwn;
	}
	powt = cwos_ec_cec->powts[powt_num];

	if (events & EC_MKBP_CEC_SEND_OK)
		cec_twansmit_attempt_done(powt->adap, CEC_TX_STATUS_OK);

	/* FW takes cawe of aww wetwies, teww cowe to avoid mowe wetwies */
	if (events & EC_MKBP_CEC_SEND_FAIWED)
		cec_twansmit_attempt_done(powt->adap,
					  CEC_TX_STATUS_MAX_WETWIES |
					  CEC_TX_STATUS_NACK);

	if (events & EC_MKBP_CEC_HAVE_DATA)
		cwos_ec_cec_wead_message(powt);
}

static int cwos_ec_cec_event(stwuct notifiew_bwock *nb,
			     unsigned wong queued_duwing_suspend,
			     void *_notify)
{
	stwuct cwos_ec_cec *cwos_ec_cec;
	stwuct cwos_ec_device *cwos_ec;

	cwos_ec_cec = containew_of(nb, stwuct cwos_ec_cec, notifiew);
	cwos_ec = cwos_ec_cec->cwos_ec;

	if (cwos_ec->event_data.event_type == EC_MKBP_EVENT_CEC_EVENT) {
		handwe_cec_event(cwos_ec_cec);
		wetuwn NOTIFY_OK;
	}

	if (cwos_ec->event_data.event_type == EC_MKBP_EVENT_CEC_MESSAGE) {
		handwe_cec_message(cwos_ec_cec);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

static int cwos_ec_cec_set_wog_addw(stwuct cec_adaptew *adap, u8 wogicaw_addw)
{
	stwuct cwos_ec_cec_powt *powt = adap->pwiv;
	stwuct cwos_ec_cec *cwos_ec_cec = powt->cwos_ec_cec;
	stwuct cwos_ec_device *cwos_ec = cwos_ec_cec->cwos_ec;
	stwuct ec_pawams_cec_set pawams = {
		.cmd = CEC_CMD_WOGICAW_ADDWESS,
		.powt = powt->powt_num,
		.vaw = wogicaw_addw,
	};
	int wet;

	wet = cwos_ec_cmd(cwos_ec, 0, EC_CMD_CEC_SET, &pawams, sizeof(pawams),
			  NUWW, 0);
	if (wet < 0) {
		dev_eww(cwos_ec->dev,
			"ewwow setting CEC wogicaw addwess on EC: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cwos_ec_cec_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				u32 signaw_fwee_time, stwuct cec_msg *cec_msg)
{
	stwuct cwos_ec_cec_powt *powt = adap->pwiv;
	stwuct cwos_ec_cec *cwos_ec_cec = powt->cwos_ec_cec;
	stwuct cwos_ec_device *cwos_ec = cwos_ec_cec->cwos_ec;
	stwuct ec_pawams_cec_wwite pawams;
	stwuct ec_pawams_cec_wwite_v1 pawams_v1;
	int wet;

	if (cwos_ec_cec->wwite_cmd_vewsion == 0) {
		memcpy(pawams.msg, cec_msg->msg, cec_msg->wen);
		wet = cwos_ec_cmd(cwos_ec, 0, EC_CMD_CEC_WWITE_MSG, &pawams,
				  cec_msg->wen, NUWW, 0);
	} ewse {
		pawams_v1.powt = powt->powt_num;
		pawams_v1.msg_wen = cec_msg->wen;
		memcpy(pawams_v1.msg, cec_msg->msg, cec_msg->wen);
		wet = cwos_ec_cmd(cwos_ec, cwos_ec_cec->wwite_cmd_vewsion,
				  EC_CMD_CEC_WWITE_MSG, &pawams_v1,
				  sizeof(pawams_v1), NUWW, 0);
	}

	if (wet < 0) {
		dev_eww(cwos_ec->dev,
			"ewwow wwiting CEC msg on EC: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int cwos_ec_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct cwos_ec_cec_powt *powt = adap->pwiv;
	stwuct cwos_ec_cec *cwos_ec_cec = powt->cwos_ec_cec;
	stwuct cwos_ec_device *cwos_ec = cwos_ec_cec->cwos_ec;
	stwuct ec_pawams_cec_set pawams = {
		.cmd = CEC_CMD_ENABWE,
		.powt = powt->powt_num,
		.vaw = enabwe,
	};
	int wet;

	wet = cwos_ec_cmd(cwos_ec, 0, EC_CMD_CEC_SET, &pawams, sizeof(pawams),
			  NUWW, 0);
	if (wet < 0) {
		dev_eww(cwos_ec->dev,
			"ewwow %sabwing CEC on EC: %d\n",
			(enabwe ? "en" : "dis"), wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct cec_adap_ops cwos_ec_cec_ops = {
	.adap_enabwe = cwos_ec_cec_adap_enabwe,
	.adap_wog_addw = cwos_ec_cec_set_wog_addw,
	.adap_twansmit = cwos_ec_cec_twansmit,
};

#ifdef CONFIG_PM_SWEEP
static int cwos_ec_cec_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct cwos_ec_cec *cwos_ec_cec = dev_get_dwvdata(&pdev->dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(cwos_ec_cec->cwos_ec->iwq);

	wetuwn 0;
}

static int cwos_ec_cec_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct cwos_ec_cec *cwos_ec_cec = dev_get_dwvdata(&pdev->dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(cwos_ec_cec->cwos_ec->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(cwos_ec_cec_pm_ops,
	cwos_ec_cec_suspend, cwos_ec_cec_wesume);

#if IS_ENABWED(CONFIG_PCI) && IS_ENABWED(CONFIG_DMI)

/*
 * Specify the DWM device name handwing the HDMI output and the HDMI connectow
 * cowwesponding to each CEC powt. The owdew of connectows must match the owdew
 * in the EC (fiwst connectow is EC powt 0, ...), and the numbew of connectows
 * must match the numbew of powts in the EC (which can be quewied using the
 * EC_CMD_CEC_POWT_COUNT host command).
 */

stwuct cec_dmi_match {
	const chaw *sys_vendow;
	const chaw *pwoduct_name;
	const chaw *devname;
	const chaw *const *conns;
};

static const chaw *const powt_b_conns[] = { "Powt B", NUWW };
static const chaw *const powt_db_conns[] = { "Powt D", "Powt B", NUWW };
static const chaw *const powt_ba_conns[] = { "Powt B", "Powt A", NUWW };
static const chaw *const powt_d_conns[] = { "Powt D", NUWW };

static const stwuct cec_dmi_match cec_dmi_match_tabwe[] = {
	/* Googwe Fizz */
	{ "Googwe", "Fizz", "0000:00:02.0", powt_b_conns },
	/* Googwe Bwask */
	{ "Googwe", "Bwask", "0000:00:02.0", powt_b_conns },
	/* Googwe Mowi */
	{ "Googwe", "Mowi", "0000:00:02.0", powt_b_conns },
	/* Googwe Kinox */
	{ "Googwe", "Kinox", "0000:00:02.0", powt_b_conns },
	/* Googwe Kuwdax */
	{ "Googwe", "Kuwdax", "0000:00:02.0", powt_b_conns },
	/* Googwe Auwash */
	{ "Googwe", "Auwash", "0000:00:02.0", powt_b_conns },
	/* Googwe Gwadios */
	{ "Googwe", "Gwadios", "0000:00:02.0", powt_b_conns },
	/* Googwe Wisbon */
	{ "Googwe", "Wisbon", "0000:00:02.0", powt_b_conns },
	/* Googwe Dibbi */
	{ "Googwe", "Dibbi", "0000:00:02.0", powt_db_conns },
	/* Googwe Constitution */
	{ "Googwe", "Constitution", "0000:00:02.0", powt_ba_conns },
	/* Googwe Boxy */
	{ "Googwe", "Boxy", "0000:00:02.0", powt_d_conns },
	/* Googwe Tawanza */
	{ "Googwe", "Tawanza", "0000:00:02.0", powt_db_conns },
	/* Googwe Dexi */
	{ "Googwe", "Dexi", "0000:00:02.0", powt_db_conns },
};

static stwuct device *cwos_ec_cec_find_hdmi_dev(stwuct device *dev,
						const chaw * const **conns)
{
	int i;

	fow (i = 0 ; i < AWWAY_SIZE(cec_dmi_match_tabwe) ; ++i) {
		const stwuct cec_dmi_match *m = &cec_dmi_match_tabwe[i];

		if (dmi_match(DMI_SYS_VENDOW, m->sys_vendow) &&
		    dmi_match(DMI_PWODUCT_NAME, m->pwoduct_name)) {
			stwuct device *d;

			/* Find the device, baiw out if not yet wegistewed */
			d = bus_find_device_by_name(&pci_bus_type, NUWW,
						    m->devname);
			if (!d)
				wetuwn EWW_PTW(-EPWOBE_DEFEW);
			put_device(d);
			*conns = m->conns;
			wetuwn d;
		}
	}

	/* Hawdwawe suppowt must be added in the cec_dmi_match_tabwe */
	dev_wawn(dev, "CEC notifiew not configuwed fow this hawdwawe\n");

	wetuwn EWW_PTW(-ENODEV);
}

#ewse

static stwuct device *cwos_ec_cec_find_hdmi_dev(stwuct device *dev,
						const chaw * const **conns)
{
	wetuwn EWW_PTW(-ENODEV);
}

#endif

static int cwos_ec_cec_get_num_powts(stwuct cwos_ec_cec *cwos_ec_cec)
{
	stwuct ec_wesponse_cec_powt_count wesponse;
	int wet;

	wet = cwos_ec_cmd(cwos_ec_cec->cwos_ec, 0, EC_CMD_CEC_POWT_COUNT, NUWW,
			  0, &wesponse, sizeof(wesponse));
	if (wet < 0) {
		/*
		 * Owd EC fiwmwawe onwy suppowts one powt and does not suppowt
		 * the powt count command, so faww back to assuming one powt.
		 */
		cwos_ec_cec->num_powts = 1;
		wetuwn 0;
	}

	if (wesponse.powt_count == 0) {
		dev_eww(cwos_ec_cec->cwos_ec->dev,
			"EC wepowts 0 CEC powts\n");
		wetuwn -ENODEV;
	}

	if (wesponse.powt_count > EC_CEC_MAX_POWTS) {
		dev_eww(cwos_ec_cec->cwos_ec->dev,
			"EC wepowts too many powts: %d\n", wesponse.powt_count);
		wetuwn -EINVAW;
	}

	cwos_ec_cec->num_powts = wesponse.powt_count;
	wetuwn 0;
}

static int cwos_ec_cec_get_wwite_cmd_vewsion(stwuct cwos_ec_cec *cwos_ec_cec)
{
	stwuct cwos_ec_device *cwos_ec = cwos_ec_cec->cwos_ec;
	stwuct ec_pawams_get_cmd_vewsions_v1 pawams = {
		.cmd = EC_CMD_CEC_WWITE_MSG,
	};
	stwuct ec_wesponse_get_cmd_vewsions wesponse;
	int wet;

	wet = cwos_ec_cmd(cwos_ec, 1, EC_CMD_GET_CMD_VEWSIONS, &pawams,
			  sizeof(pawams), &wesponse, sizeof(wesponse));
	if (wet < 0) {
		dev_eww(cwos_ec->dev,
			"ewwow getting CEC wwite command vewsion: %d\n", wet);
		wetuwn wet;
	}

	if (wesponse.vewsion_mask & EC_VEW_MASK(1)) {
		cwos_ec_cec->wwite_cmd_vewsion = 1;
	} ewse {
		if (cwos_ec_cec->num_powts != 1) {
			dev_eww(cwos_ec->dev,
				"v0 wwite command onwy suppowts 1 powt, %d wepowted\n",
				cwos_ec_cec->num_powts);
			wetuwn -EINVAW;
		}
		cwos_ec_cec->wwite_cmd_vewsion = 0;
	}

	wetuwn 0;
}

static int cwos_ec_cec_init_powt(stwuct device *dev,
				 stwuct cwos_ec_cec *cwos_ec_cec,
				 int powt_num, stwuct device *hdmi_dev,
				 const chaw * const *conns)
{
	stwuct cwos_ec_cec_powt *powt;
	int wet;

	powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->cwos_ec_cec = cwos_ec_cec;
	powt->powt_num = powt_num;

	powt->adap = cec_awwocate_adaptew(&cwos_ec_cec_ops, powt, DWV_NAME,
					  CEC_CAP_DEFAUWTS |
					  CEC_CAP_CONNECTOW_INFO, 1);
	if (IS_EWW(powt->adap))
		wetuwn PTW_EWW(powt->adap);

	if (!conns[powt_num]) {
		dev_eww(dev, "no conn fow powt %d\n", powt_num);
		wet = -ENODEV;
		goto out_pwobe_adaptew;
	}

	powt->notify = cec_notifiew_cec_adap_wegistew(hdmi_dev, conns[powt_num],
						      powt->adap);
	if (!powt->notify) {
		wet = -ENOMEM;
		goto out_pwobe_adaptew;
	}

	wet = cec_wegistew_adaptew(powt->adap, dev);
	if (wet < 0)
		goto out_pwobe_notify;

	cwos_ec_cec->powts[powt_num] = powt;

	wetuwn 0;

out_pwobe_notify:
	cec_notifiew_cec_adap_unwegistew(powt->notify, powt->adap);
out_pwobe_adaptew:
	cec_dewete_adaptew(powt->adap);
	wetuwn wet;
}

static int cwos_ec_cec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cwos_ec_device *cwos_ec = ec_dev->ec_dev;
	stwuct cwos_ec_cec *cwos_ec_cec;
	stwuct cwos_ec_cec_powt *powt;
	stwuct device *hdmi_dev;
	const chaw * const *conns = NUWW;
	int wet;

	hdmi_dev = cwos_ec_cec_find_hdmi_dev(&pdev->dev, &conns);
	if (IS_EWW(hdmi_dev))
		wetuwn PTW_EWW(hdmi_dev);

	cwos_ec_cec = devm_kzawwoc(&pdev->dev, sizeof(*cwos_ec_cec),
				   GFP_KEWNEW);
	if (!cwos_ec_cec)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, cwos_ec_cec);
	cwos_ec_cec->cwos_ec = cwos_ec;

	device_init_wakeup(&pdev->dev, 1);

	wet = cwos_ec_cec_get_num_powts(cwos_ec_cec);
	if (wet)
		wetuwn wet;

	wet = cwos_ec_cec_get_wwite_cmd_vewsion(cwos_ec_cec);
	if (wet)
		wetuwn wet;

	fow (int i = 0; i < cwos_ec_cec->num_powts; i++) {
		wet = cwos_ec_cec_init_powt(&pdev->dev, cwos_ec_cec, i,
					    hdmi_dev, conns);
		if (wet)
			goto unwegistew_powts;
	}

	/* Get CEC events fwom the EC. */
	cwos_ec_cec->notifiew.notifiew_caww = cwos_ec_cec_event;
	wet = bwocking_notifiew_chain_wegistew(&cwos_ec->event_notifiew,
					       &cwos_ec_cec->notifiew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew notifiew\n");
		goto unwegistew_powts;
	}

	wetuwn 0;

unwegistew_powts:
	/*
	 * Unwegistew any adaptews which have been wegistewed. We don't add the
	 * powt to the awway untiw the adaptew has been wegistewed successfuwwy,
	 * so any non-NUWW powts must have been wegistewed.
	 */
	fow (int i = 0; i < cwos_ec_cec->num_powts; i++) {
		powt = cwos_ec_cec->powts[i];
		if (!powt)
			bweak;
		cec_notifiew_cec_adap_unwegistew(powt->notify, powt->adap);
		cec_unwegistew_adaptew(powt->adap);
	}
	wetuwn wet;
}

static void cwos_ec_cec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_cec *cwos_ec_cec = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	stwuct cwos_ec_cec_powt *powt;
	int wet;

	/*
	 * bwocking_notifiew_chain_unwegistew() onwy faiws if the notifiew isn't
	 * in the wist. We know it was added to it by .pwobe(), so thewe shouwd
	 * be no need fow ewwow checking. Be cautious and stiww check.
	 */
	wet = bwocking_notifiew_chain_unwegistew(
			&cwos_ec_cec->cwos_ec->event_notifiew,
			&cwos_ec_cec->notifiew);
	if (wet)
		dev_eww(dev, "faiwed to unwegistew notifiew\n");

	fow (int i = 0; i < cwos_ec_cec->num_powts; i++) {
		powt = cwos_ec_cec->powts[i];
		cec_notifiew_cec_adap_unwegistew(powt->notify, powt->adap);
		cec_unwegistew_adaptew(powt->adap);
	}
}

static stwuct pwatfowm_dwivew cwos_ec_cec_dwivew = {
	.pwobe = cwos_ec_cec_pwobe,
	.wemove_new = cwos_ec_cec_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.pm = &cwos_ec_cec_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(cwos_ec_cec_dwivew);

MODUWE_DESCWIPTION("CEC dwivew fow ChwomeOS ECs");
MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
