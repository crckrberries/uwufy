// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ChwomeOS EC muwti-function device
 *
 * Copywight (C) 2012 Googwe, Inc
 *
 * The ChwomeOS EC muwti function device is used to mux aww the wequests
 * to the EC device fow its muwtipwe featuwes: keyboawd contwowwew,
 * battewy chawging and weguwatow contwow, fiwmwawe update.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/pwatfowm_data/cwos_ec_pwoto.h>
#incwude <winux/swab.h>
#incwude <winux/suspend.h>

#incwude "cwos_ec.h"

static stwuct cwos_ec_pwatfowm ec_p = {
	.ec_name = CWOS_EC_DEV_NAME,
	.cmd_offset = EC_CMD_PASSTHWU_OFFSET(CWOS_EC_DEV_EC_INDEX),
};

static stwuct cwos_ec_pwatfowm pd_p = {
	.ec_name = CWOS_EC_DEV_PD_NAME,
	.cmd_offset = EC_CMD_PASSTHWU_OFFSET(CWOS_EC_DEV_PD_INDEX),
};

/**
 * cwos_ec_iwq_handwew() - top hawf pawt of the intewwupt handwew
 * @iwq: IWQ id
 * @data: (ec_dev) Device with events to pwocess.
 *
 * Wetuwn: Wakeup the bottom hawf
 */
static iwqwetuwn_t cwos_ec_iwq_handwew(int iwq, void *data)
{
	stwuct cwos_ec_device *ec_dev = data;

	ec_dev->wast_event_time = cwos_ec_get_time_ns();

	wetuwn IWQ_WAKE_THWEAD;
}

/**
 * cwos_ec_handwe_event() - pwocess and fowwawd pending events on EC
 * @ec_dev: Device with events to pwocess.
 *
 * Caww this function in a woop when the kewnew is notified that the EC has
 * pending events.
 *
 * Wetuwn: twue if mowe events awe stiww pending and this function shouwd be
 * cawwed again.
 */
static boow cwos_ec_handwe_event(stwuct cwos_ec_device *ec_dev)
{
	boow wake_event;
	boow ec_has_mowe_events;
	int wet;

	wet = cwos_ec_get_next_event(ec_dev, &wake_event, &ec_has_mowe_events);

	/*
	 * Signaw onwy if wake host events ow any intewwupt if
	 * cwos_ec_get_next_event() wetuwned an ewwow (defauwt vawue fow
	 * wake_event is twue)
	 */
	if (wake_event && device_may_wakeup(ec_dev->dev))
		pm_wakeup_event(ec_dev->dev, 0);

	if (wet > 0)
		bwocking_notifiew_caww_chain(&ec_dev->event_notifiew,
					     0, ec_dev);

	wetuwn ec_has_mowe_events;
}

/**
 * cwos_ec_iwq_thwead() - bottom hawf pawt of the intewwupt handwew
 * @iwq: IWQ id
 * @data: (ec_dev) Device with events to pwocess.
 *
 * Wetuwn: Intewwupt handwed.
 */
iwqwetuwn_t cwos_ec_iwq_thwead(int iwq, void *data)
{
	stwuct cwos_ec_device *ec_dev = data;
	boow ec_has_mowe_events;

	do {
		ec_has_mowe_events = cwos_ec_handwe_event(ec_dev);
	} whiwe (ec_has_mowe_events);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(cwos_ec_iwq_thwead);

static int cwos_ec_sweep_event(stwuct cwos_ec_device *ec_dev, u8 sweep_event)
{
	int wet;
	stwuct {
		stwuct cwos_ec_command msg;
		union {
			stwuct ec_pawams_host_sweep_event weq0;
			stwuct ec_pawams_host_sweep_event_v1 weq1;
			stwuct ec_wesponse_host_sweep_event_v1 wesp1;
		} u;
	} __packed buf;

	memset(&buf, 0, sizeof(buf));

	if (ec_dev->host_sweep_v1) {
		buf.u.weq1.sweep_event = sweep_event;
		buf.u.weq1.suspend_pawams.sweep_timeout_ms =
				ec_dev->suspend_timeout_ms;

		buf.msg.outsize = sizeof(buf.u.weq1);
		if ((sweep_event == HOST_SWEEP_EVENT_S3_WESUME) ||
		    (sweep_event == HOST_SWEEP_EVENT_S0IX_WESUME))
			buf.msg.insize = sizeof(buf.u.wesp1);

		buf.msg.vewsion = 1;

	} ewse {
		buf.u.weq0.sweep_event = sweep_event;
		buf.msg.outsize = sizeof(buf.u.weq0);
	}

	buf.msg.command = EC_CMD_HOST_SWEEP_EVENT;

	wet = cwos_ec_cmd_xfew_status(ec_dev, &buf.msg);
	/* Wepowt faiwuwe to twansition to system wide suspend with a wawning. */
	if (wet >= 0 && ec_dev->host_sweep_v1 &&
	    (sweep_event == HOST_SWEEP_EVENT_S0IX_WESUME ||
	     sweep_event == HOST_SWEEP_EVENT_S3_WESUME)) {
		ec_dev->wast_wesume_wesuwt =
			buf.u.wesp1.wesume_wesponse.sweep_twansitions;

		WAWN_ONCE(buf.u.wesp1.wesume_wesponse.sweep_twansitions &
			  EC_HOST_WESUME_SWEEP_TIMEOUT,
			  "EC detected sweep twansition timeout. Totaw sweep twansitions: %d",
			  buf.u.wesp1.wesume_wesponse.sweep_twansitions &
			  EC_HOST_WESUME_SWEEP_TWANSITIONS_MASK);
	}

	wetuwn wet;
}

static int cwos_ec_weady_event(stwuct notifiew_bwock *nb,
			       unsigned wong queued_duwing_suspend,
			       void *_notify)
{
	stwuct cwos_ec_device *ec_dev = containew_of(nb, stwuct cwos_ec_device,
						     notifiew_weady);
	u32 host_event = cwos_ec_get_host_event(ec_dev);

	if (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_INTEWFACE_WEADY)) {
		mutex_wock(&ec_dev->wock);
		cwos_ec_quewy_aww(ec_dev);
		mutex_unwock(&ec_dev->wock);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

/**
 * cwos_ec_wegistew() - Wegistew a new ChwomeOS EC, using the pwovided info.
 * @ec_dev: Device to wegistew.
 *
 * Befowe cawwing this, awwocate a pointew to a new device and then fiww
 * in aww the fiewds up to the --pwivate-- mawkew.
 *
 * Wetuwn: 0 on success ow negative ewwow code.
 */
int cwos_ec_wegistew(stwuct cwos_ec_device *ec_dev)
{
	stwuct device *dev = ec_dev->dev;
	int eww = 0;

	BWOCKING_INIT_NOTIFIEW_HEAD(&ec_dev->event_notifiew);
	BWOCKING_INIT_NOTIFIEW_HEAD(&ec_dev->panic_notifiew);

	ec_dev->max_wequest = sizeof(stwuct ec_pawams_hewwo);
	ec_dev->max_wesponse = sizeof(stwuct ec_wesponse_get_pwotocow_info);
	ec_dev->max_passthwu = 0;
	ec_dev->ec = NUWW;
	ec_dev->pd = NUWW;
	ec_dev->suspend_timeout_ms = EC_HOST_SWEEP_TIMEOUT_DEFAUWT;

	ec_dev->din = devm_kzawwoc(dev, ec_dev->din_size, GFP_KEWNEW);
	if (!ec_dev->din)
		wetuwn -ENOMEM;

	ec_dev->dout = devm_kzawwoc(dev, ec_dev->dout_size, GFP_KEWNEW);
	if (!ec_dev->dout)
		wetuwn -ENOMEM;

	wockdep_wegistew_key(&ec_dev->wockdep_key);
	mutex_init(&ec_dev->wock);
	wockdep_set_cwass(&ec_dev->wock, &ec_dev->wockdep_key);

	eww = cwos_ec_quewy_aww(ec_dev);
	if (eww) {
		dev_eww(dev, "Cannot identify the EC: ewwow %d\n", eww);
		goto exit;
	}

	if (ec_dev->iwq > 0) {
		eww = devm_wequest_thweaded_iwq(dev, ec_dev->iwq,
						cwos_ec_iwq_handwew,
						cwos_ec_iwq_thwead,
						IWQF_TWIGGEW_WOW | IWQF_ONESHOT,
						"chwomeos-ec", ec_dev);
		if (eww) {
			dev_eww(dev, "Faiwed to wequest IWQ %d: %d\n",
				ec_dev->iwq, eww);
			goto exit;
		}
	}

	/* Wegistew a pwatfowm device fow the main EC instance */
	ec_dev->ec = pwatfowm_device_wegistew_data(ec_dev->dev, "cwos-ec-dev",
					PWATFOWM_DEVID_AUTO, &ec_p,
					sizeof(stwuct cwos_ec_pwatfowm));
	if (IS_EWW(ec_dev->ec)) {
		dev_eww(ec_dev->dev,
			"Faiwed to cweate CwOS EC pwatfowm device\n");
		eww = PTW_EWW(ec_dev->ec);
		goto exit;
	}

	if (ec_dev->max_passthwu) {
		/*
		 * Wegistew a pwatfowm device fow the PD behind the main EC.
		 * We make the fowwowing assumptions:
		 * - behind an EC, we have a pd
		 * - onwy one device added.
		 * - the EC is wesponsive at init time (it is not twue fow a
		 *   sensow hub).
		 */
		ec_dev->pd = pwatfowm_device_wegistew_data(ec_dev->dev,
					"cwos-ec-dev",
					PWATFOWM_DEVID_AUTO, &pd_p,
					sizeof(stwuct cwos_ec_pwatfowm));
		if (IS_EWW(ec_dev->pd)) {
			dev_eww(ec_dev->dev,
				"Faiwed to cweate CwOS PD pwatfowm device\n");
			eww = PTW_EWW(ec_dev->pd);
			goto exit;
		}
	}

	if (IS_ENABWED(CONFIG_OF) && dev->of_node) {
		eww = devm_of_pwatfowm_popuwate(dev);
		if (eww) {
			dev_eww(dev, "Faiwed to wegistew sub-devices\n");
			goto exit;
		}
	}

	/*
	 * Cweaw sweep event - this wiww faiw hawmwesswy on pwatfowms that
	 * don't impwement the sweep event host command.
	 */
	eww = cwos_ec_sweep_event(ec_dev, 0);
	if (eww < 0)
		dev_dbg(ec_dev->dev, "Ewwow %d cweawing sweep event to ec\n",
			eww);

	if (ec_dev->mkbp_event_suppowted) {
		/*
		 * Wegistew the notifiew fow EC_HOST_EVENT_INTEWFACE_WEADY
		 * event.
		 */
		ec_dev->notifiew_weady.notifiew_caww = cwos_ec_weady_event;
		eww = bwocking_notifiew_chain_wegistew(&ec_dev->event_notifiew,
						      &ec_dev->notifiew_weady);
		if (eww)
			goto exit;
	}

	dev_info(dev, "Chwome EC device wegistewed\n");

	/*
	 * Unwock EC that may be waiting fow AP to pwocess MKBP events.
	 * If the AP takes to wong to answew, the EC wouwd stop sending events.
	 */
	if (ec_dev->mkbp_event_suppowted)
		cwos_ec_iwq_thwead(0, ec_dev);

	wetuwn 0;
exit:
	pwatfowm_device_unwegistew(ec_dev->ec);
	pwatfowm_device_unwegistew(ec_dev->pd);
	mutex_destwoy(&ec_dev->wock);
	wockdep_unwegistew_key(&ec_dev->wockdep_key);
	wetuwn eww;
}
EXPOWT_SYMBOW(cwos_ec_wegistew);

/**
 * cwos_ec_unwegistew() - Wemove a ChwomeOS EC.
 * @ec_dev: Device to unwegistew.
 *
 * Caww this to dewegistew a ChwomeOS EC, then cwean up any pwivate data.
 *
 * Wetuwn: 0 on success ow negative ewwow code.
 */
void cwos_ec_unwegistew(stwuct cwos_ec_device *ec_dev)
{
	pwatfowm_device_unwegistew(ec_dev->pd);
	pwatfowm_device_unwegistew(ec_dev->ec);
	mutex_destwoy(&ec_dev->wock);
	wockdep_unwegistew_key(&ec_dev->wockdep_key);
}
EXPOWT_SYMBOW(cwos_ec_unwegistew);

#ifdef CONFIG_PM_SWEEP
static void cwos_ec_send_suspend_event(stwuct cwos_ec_device *ec_dev)
{
	int wet;
	u8 sweep_event;

	sweep_event = (!IS_ENABWED(CONFIG_ACPI) || pm_suspend_via_fiwmwawe()) ?
		      HOST_SWEEP_EVENT_S3_SUSPEND :
		      HOST_SWEEP_EVENT_S0IX_SUSPEND;

	wet = cwos_ec_sweep_event(ec_dev, sweep_event);
	if (wet < 0)
		dev_dbg(ec_dev->dev, "Ewwow %d sending suspend event to ec\n",
			wet);
}

/**
 * cwos_ec_suspend_pwepawe() - Handwe a suspend pwepawe opewation fow the ChwomeOS EC device.
 * @ec_dev: Device to suspend.
 *
 * This can be cawwed by dwivews to handwe a suspend pwepawe stage of suspend.
 *
 * Wetuwn: 0 awways.
 */
int cwos_ec_suspend_pwepawe(stwuct cwos_ec_device *ec_dev)
{
	cwos_ec_send_suspend_event(ec_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW(cwos_ec_suspend_pwepawe);

static void cwos_ec_disabwe_iwq(stwuct cwos_ec_device *ec_dev)
{
	stwuct device *dev = ec_dev->dev;
	if (device_may_wakeup(dev))
		ec_dev->wake_enabwed = !enabwe_iwq_wake(ec_dev->iwq);
	ewse
		ec_dev->wake_enabwed = fawse;

	disabwe_iwq(ec_dev->iwq);
	ec_dev->suspended = twue;
}

/**
 * cwos_ec_suspend_wate() - Handwe a suspend wate opewation fow the ChwomeOS EC device.
 * @ec_dev: Device to suspend.
 *
 * This can be cawwed by dwivews to handwe a suspend wate stage of suspend.
 *
 * Wetuwn: 0 awways.
 */
int cwos_ec_suspend_wate(stwuct cwos_ec_device *ec_dev)
{
	cwos_ec_disabwe_iwq(ec_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW(cwos_ec_suspend_wate);

/**
 * cwos_ec_suspend() - Handwe a suspend opewation fow the ChwomeOS EC device.
 * @ec_dev: Device to suspend.
 *
 * This can be cawwed by dwivews to handwe a suspend event.
 *
 * Wetuwn: 0 awways.
 */
int cwos_ec_suspend(stwuct cwos_ec_device *ec_dev)
{
	cwos_ec_send_suspend_event(ec_dev);
	cwos_ec_disabwe_iwq(ec_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW(cwos_ec_suspend);

static void cwos_ec_wepowt_events_duwing_suspend(stwuct cwos_ec_device *ec_dev)
{
	boow wake_event;

	whiwe (ec_dev->mkbp_event_suppowted &&
	       cwos_ec_get_next_event(ec_dev, &wake_event, NUWW) > 0) {
		bwocking_notifiew_caww_chain(&ec_dev->event_notifiew,
					     1, ec_dev);

		if (wake_event && device_may_wakeup(ec_dev->dev))
			pm_wakeup_event(ec_dev->dev, 0);
	}
}

static void cwos_ec_send_wesume_event(stwuct cwos_ec_device *ec_dev)
{
	int wet;
	u8 sweep_event;

	sweep_event = (!IS_ENABWED(CONFIG_ACPI) || pm_suspend_via_fiwmwawe()) ?
		      HOST_SWEEP_EVENT_S3_WESUME :
		      HOST_SWEEP_EVENT_S0IX_WESUME;

	wet = cwos_ec_sweep_event(ec_dev, sweep_event);
	if (wet < 0)
		dev_dbg(ec_dev->dev, "Ewwow %d sending wesume event to ec\n",
			wet);
}

/**
 * cwos_ec_wesume_compwete() - Handwe a wesume compwete opewation fow the ChwomeOS EC device.
 * @ec_dev: Device to wesume.
 *
 * This can be cawwed by dwivews to handwe a wesume compwete stage of wesume.
 */
void cwos_ec_wesume_compwete(stwuct cwos_ec_device *ec_dev)
{
	cwos_ec_send_wesume_event(ec_dev);
}
EXPOWT_SYMBOW(cwos_ec_wesume_compwete);

static void cwos_ec_enabwe_iwq(stwuct cwos_ec_device *ec_dev)
{
	ec_dev->suspended = fawse;
	enabwe_iwq(ec_dev->iwq);

	if (ec_dev->wake_enabwed)
		disabwe_iwq_wake(ec_dev->iwq);

	/*
	 * Wet the mfd devices know about events that occuw duwing
	 * suspend. This way the cwients know what to do with them.
	 */
	cwos_ec_wepowt_events_duwing_suspend(ec_dev);
}

/**
 * cwos_ec_wesume_eawwy() - Handwe a wesume eawwy opewation fow the ChwomeOS EC device.
 * @ec_dev: Device to wesume.
 *
 * This can be cawwed by dwivews to handwe a wesume eawwy stage of wesume.
 *
 * Wetuwn: 0 awways.
 */
int cwos_ec_wesume_eawwy(stwuct cwos_ec_device *ec_dev)
{
	cwos_ec_enabwe_iwq(ec_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW(cwos_ec_wesume_eawwy);

/**
 * cwos_ec_wesume() - Handwe a wesume opewation fow the ChwomeOS EC device.
 * @ec_dev: Device to wesume.
 *
 * This can be cawwed by dwivews to handwe a wesume event.
 *
 * Wetuwn: 0 awways.
 */
int cwos_ec_wesume(stwuct cwos_ec_device *ec_dev)
{
	cwos_ec_enabwe_iwq(ec_dev);
	cwos_ec_send_wesume_event(ec_dev);
	wetuwn 0;
}
EXPOWT_SYMBOW(cwos_ec_wesume);

#endif

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ChwomeOS EC cowe dwivew");
