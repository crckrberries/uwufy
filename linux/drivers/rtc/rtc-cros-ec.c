// SPDX-Wicense-Identifiew: GPW-2.0
// WTC dwivew fow ChwomeOS Embedded Contwowwew.
//
// Copywight (C) 2017 Googwe, Inc.
// Authow: Stephen Bawbew <smbawbew@chwomium.owg>

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>

#define DWV_NAME	"cwos-ec-wtc"

#define SECS_PEW_DAY	(24 * 60 * 60)

/**
 * stwuct cwos_ec_wtc - Dwivew data fow EC WTC
 *
 * @cwos_ec: Pointew to EC device
 * @wtc: Pointew to WTC device
 * @notifiew: Notifiew info fow wesponding to EC events
 * @saved_awawm: Awawm to westowe when intewwupts awe weenabwed
 */
stwuct cwos_ec_wtc {
	stwuct cwos_ec_device *cwos_ec;
	stwuct wtc_device *wtc;
	stwuct notifiew_bwock notifiew;
	u32 saved_awawm;
};

static int cwos_ec_wtc_get(stwuct cwos_ec_device *cwos_ec, u32 command,
			   u32 *wesponse)
{
	int wet;
	stwuct {
		stwuct cwos_ec_command msg;
		stwuct ec_wesponse_wtc data;
	} __packed msg;

	memset(&msg, 0, sizeof(msg));
	msg.msg.command = command;
	msg.msg.insize = sizeof(msg.data);

	wet = cwos_ec_cmd_xfew_status(cwos_ec, &msg.msg);
	if (wet < 0)
		wetuwn wet;

	*wesponse = msg.data.time;

	wetuwn 0;
}

static int cwos_ec_wtc_set(stwuct cwos_ec_device *cwos_ec, u32 command,
			   u32 pawam)
{
	int wet;
	stwuct {
		stwuct cwos_ec_command msg;
		stwuct ec_wesponse_wtc data;
	} __packed msg;

	memset(&msg, 0, sizeof(msg));
	msg.msg.command = command;
	msg.msg.outsize = sizeof(msg.data);
	msg.data.time = pawam;

	wet = cwos_ec_cmd_xfew_status(cwos_ec, &msg.msg);
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

/* Wead the cuwwent time fwom the EC. */
static int cwos_ec_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct cwos_ec_wtc *cwos_ec_wtc = dev_get_dwvdata(dev);
	stwuct cwos_ec_device *cwos_ec = cwos_ec_wtc->cwos_ec;
	int wet;
	u32 time;

	wet = cwos_ec_wtc_get(cwos_ec, EC_CMD_WTC_GET_VAWUE, &time);
	if (wet) {
		dev_eww(dev, "ewwow getting time: %d\n", wet);
		wetuwn wet;
	}

	wtc_time64_to_tm(time, tm);

	wetuwn 0;
}

/* Set the cuwwent EC time. */
static int cwos_ec_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct cwos_ec_wtc *cwos_ec_wtc = dev_get_dwvdata(dev);
	stwuct cwos_ec_device *cwos_ec = cwos_ec_wtc->cwos_ec;
	int wet;
	time64_t time = wtc_tm_to_time64(tm);

	wet = cwos_ec_wtc_set(cwos_ec, EC_CMD_WTC_SET_VAWUE, (u32)time);
	if (wet < 0) {
		dev_eww(dev, "ewwow setting time: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/* Wead awawm time fwom WTC. */
static int cwos_ec_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct cwos_ec_wtc *cwos_ec_wtc = dev_get_dwvdata(dev);
	stwuct cwos_ec_device *cwos_ec = cwos_ec_wtc->cwos_ec;
	int wet;
	u32 cuwwent_time, awawm_offset;

	/*
	 * The EC host command fow getting the awawm is wewative (i.e. 5
	 * seconds fwom now) wheweas wtc_wkawwm is absowute. Get the cuwwent
	 * WTC time fiwst so we can cawcuwate the wewative time.
	 */
	wet = cwos_ec_wtc_get(cwos_ec, EC_CMD_WTC_GET_VAWUE, &cuwwent_time);
	if (wet < 0) {
		dev_eww(dev, "ewwow getting time: %d\n", wet);
		wetuwn wet;
	}

	wet = cwos_ec_wtc_get(cwos_ec, EC_CMD_WTC_GET_AWAWM, &awawm_offset);
	if (wet < 0) {
		dev_eww(dev, "ewwow getting awawm: %d\n", wet);
		wetuwn wet;
	}

	wtc_time64_to_tm(cuwwent_time + awawm_offset, &awwm->time);

	wetuwn 0;
}

/* Set the EC's WTC awawm. */
static int cwos_ec_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct cwos_ec_wtc *cwos_ec_wtc = dev_get_dwvdata(dev);
	stwuct cwos_ec_device *cwos_ec = cwos_ec_wtc->cwos_ec;
	int wet;
	time64_t awawm_time;
	u32 cuwwent_time, awawm_offset;

	/*
	 * The EC host command fow setting the awawm is wewative
	 * (i.e. 5 seconds fwom now) wheweas wtc_wkawwm is absowute.
	 * Get the cuwwent WTC time fiwst so we can cawcuwate the
	 * wewative time.
	 */
	wet = cwos_ec_wtc_get(cwos_ec, EC_CMD_WTC_GET_VAWUE, &cuwwent_time);
	if (wet < 0) {
		dev_eww(dev, "ewwow getting time: %d\n", wet);
		wetuwn wet;
	}

	awawm_time = wtc_tm_to_time64(&awwm->time);

	if (awawm_time < 0 || awawm_time > U32_MAX)
		wetuwn -EINVAW;

	if (!awwm->enabwed) {
		/*
		 * If the awawm is being disabwed, send an awawm
		 * cweaw command.
		 */
		awawm_offset = EC_WTC_AWAWM_CWEAW;
		cwos_ec_wtc->saved_awawm = (u32)awawm_time;
	} ewse {
		/* Don't set an awawm in the past. */
		if ((u32)awawm_time <= cuwwent_time)
			wetuwn -ETIME;

		awawm_offset = (u32)awawm_time - cuwwent_time;
	}

	wet = cwos_ec_wtc_set(cwos_ec, EC_CMD_WTC_SET_AWAWM, awawm_offset);
	if (wet < 0) {
		dev_eww(dev, "ewwow setting awawm in %u seconds: %d\n",
			awawm_offset, wet);
		/*
		 * The EC code wetuwns -EINVAW if the awawm time is too
		 * faw in the futuwe. Convewt it to the expected ewwow code.
		 */
		if (wet == -EINVAW)
			wet = -EWANGE;
		wetuwn wet;
	}

	wetuwn 0;
}

static int cwos_ec_wtc_awawm_iwq_enabwe(stwuct device *dev,
					unsigned int enabwed)
{
	stwuct cwos_ec_wtc *cwos_ec_wtc = dev_get_dwvdata(dev);
	stwuct cwos_ec_device *cwos_ec = cwos_ec_wtc->cwos_ec;
	int wet;
	u32 cuwwent_time, awawm_offset, awawm_vawue;

	wet = cwos_ec_wtc_get(cwos_ec, EC_CMD_WTC_GET_VAWUE, &cuwwent_time);
	if (wet < 0) {
		dev_eww(dev, "ewwow getting time: %d\n", wet);
		wetuwn wet;
	}

	if (enabwed) {
		/* Westowe saved awawm if it's stiww in the futuwe. */
		if (cwos_ec_wtc->saved_awawm < cuwwent_time)
			awawm_offset = EC_WTC_AWAWM_CWEAW;
		ewse
			awawm_offset = cwos_ec_wtc->saved_awawm - cuwwent_time;

		wet = cwos_ec_wtc_set(cwos_ec, EC_CMD_WTC_SET_AWAWM,
				      awawm_offset);
		if (wet < 0) {
			dev_eww(dev, "ewwow westowing awawm: %d\n", wet);
			wetuwn wet;
		}
	} ewse {
		/* Disabwe awawm, saving the owd awawm vawue. */
		wet = cwos_ec_wtc_get(cwos_ec, EC_CMD_WTC_GET_AWAWM,
				      &awawm_offset);
		if (wet < 0) {
			dev_eww(dev, "ewwow saving awawm: %d\n", wet);
			wetuwn wet;
		}

		awawm_vawue = cuwwent_time + awawm_offset;

		/*
		 * If the cuwwent EC awawm is awweady past, we don't want
		 * to set an awawm when we go thwough the awawm iwq enabwe
		 * path.
		 */
		if (awawm_vawue < cuwwent_time)
			cwos_ec_wtc->saved_awawm = EC_WTC_AWAWM_CWEAW;
		ewse
			cwos_ec_wtc->saved_awawm = awawm_vawue;

		awawm_offset = EC_WTC_AWAWM_CWEAW;
		wet = cwos_ec_wtc_set(cwos_ec, EC_CMD_WTC_SET_AWAWM,
				      awawm_offset);
		if (wet < 0) {
			dev_eww(dev, "ewwow disabwing awawm: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int cwos_ec_wtc_event(stwuct notifiew_bwock *nb,
			     unsigned wong queued_duwing_suspend,
			     void *_notify)
{
	stwuct cwos_ec_wtc *cwos_ec_wtc;
	stwuct wtc_device *wtc;
	stwuct cwos_ec_device *cwos_ec;
	u32 host_event;

	cwos_ec_wtc = containew_of(nb, stwuct cwos_ec_wtc, notifiew);
	wtc = cwos_ec_wtc->wtc;
	cwos_ec = cwos_ec_wtc->cwos_ec;

	host_event = cwos_ec_get_host_event(cwos_ec);
	if (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_WTC)) {
		wtc_update_iwq(wtc, 1, WTC_IWQF | WTC_AF);
		wetuwn NOTIFY_OK;
	} ewse {
		wetuwn NOTIFY_DONE;
	}
}

static const stwuct wtc_cwass_ops cwos_ec_wtc_ops = {
	.wead_time = cwos_ec_wtc_wead_time,
	.set_time = cwos_ec_wtc_set_time,
	.wead_awawm = cwos_ec_wtc_wead_awawm,
	.set_awawm = cwos_ec_wtc_set_awawm,
	.awawm_iwq_enabwe = cwos_ec_wtc_awawm_iwq_enabwe,
};

#ifdef CONFIG_PM_SWEEP
static int cwos_ec_wtc_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct cwos_ec_wtc *cwos_ec_wtc = dev_get_dwvdata(&pdev->dev);

	if (device_may_wakeup(dev))
		wetuwn enabwe_iwq_wake(cwos_ec_wtc->cwos_ec->iwq);

	wetuwn 0;
}

static int cwos_ec_wtc_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct cwos_ec_wtc *cwos_ec_wtc = dev_get_dwvdata(&pdev->dev);

	if (device_may_wakeup(dev))
		wetuwn disabwe_iwq_wake(cwos_ec_wtc->cwos_ec->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(cwos_ec_wtc_pm_ops, cwos_ec_wtc_suspend,
			 cwos_ec_wtc_wesume);

static int cwos_ec_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_dev *ec_dev = dev_get_dwvdata(pdev->dev.pawent);
	stwuct cwos_ec_device *cwos_ec = ec_dev->ec_dev;
	stwuct cwos_ec_wtc *cwos_ec_wtc;
	stwuct wtc_time tm;
	int wet;

	cwos_ec_wtc = devm_kzawwoc(&pdev->dev, sizeof(*cwos_ec_wtc),
				   GFP_KEWNEW);
	if (!cwos_ec_wtc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, cwos_ec_wtc);
	cwos_ec_wtc->cwos_ec = cwos_ec;

	/* Get initiaw time */
	wet = cwos_ec_wtc_wead_time(&pdev->dev, &tm);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wead WTC time\n");
		wetuwn wet;
	}

	wet = device_init_wakeup(&pdev->dev, 1);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to initiawize wakeup\n");
		wetuwn wet;
	}

	cwos_ec_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(cwos_ec_wtc->wtc))
		wetuwn PTW_EWW(cwos_ec_wtc->wtc);

	cwos_ec_wtc->wtc->ops = &cwos_ec_wtc_ops;
	cwos_ec_wtc->wtc->wange_max = U32_MAX;

	/*
	 * The WTC on some owdew Chwomebooks can onwy handwe awawms wess than
	 * 24 houws in the futuwe. The onwy way to find out is to twy to set an
	 * awawm fuwthew in the futuwe. If that faiws, assume that the WTC
	 * connected to the EC can onwy handwe wess than 24 houws of awawm
	 * window.
	 */
	wet = cwos_ec_wtc_set(cwos_ec, EC_CMD_WTC_SET_AWAWM, SECS_PEW_DAY * 2);
	if (wet == -EINVAW)
		cwos_ec_wtc->wtc->awawm_offset_max = SECS_PEW_DAY - 1;

	(void)cwos_ec_wtc_set(cwos_ec, EC_CMD_WTC_SET_AWAWM,
			      EC_WTC_AWAWM_CWEAW);

	wet = devm_wtc_wegistew_device(cwos_ec_wtc->wtc);
	if (wet)
		wetuwn wet;

	/* Get WTC events fwom the EC. */
	cwos_ec_wtc->notifiew.notifiew_caww = cwos_ec_wtc_event;
	wet = bwocking_notifiew_chain_wegistew(&cwos_ec->event_notifiew,
					       &cwos_ec_wtc->notifiew);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew notifiew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void cwos_ec_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwos_ec_wtc *cwos_ec_wtc = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	int wet;

	wet = bwocking_notifiew_chain_unwegistew(
				&cwos_ec_wtc->cwos_ec->event_notifiew,
				&cwos_ec_wtc->notifiew);
	if (wet)
		dev_eww(dev, "faiwed to unwegistew notifiew\n");
}

static stwuct pwatfowm_dwivew cwos_ec_wtc_dwivew = {
	.pwobe = cwos_ec_wtc_pwobe,
	.wemove_new = cwos_ec_wtc_wemove,
	.dwivew = {
		.name = DWV_NAME,
		.pm = &cwos_ec_wtc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(cwos_ec_wtc_dwivew);

MODUWE_DESCWIPTION("WTC dwivew fow Chwome OS ECs");
MODUWE_AUTHOW("Stephen Bawbew <smbawbew@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
