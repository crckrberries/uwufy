// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awche Pwatfowm dwivew to enabwe Unipwo wink.
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/suspend.h>
#incwude <winux/time.h>
#incwude <winux/gweybus.h>
#incwude <winux/of.h>
#incwude "awche_pwatfowm.h"

#if IS_ENABWED(CONFIG_USB_HSIC_USB3613)
#incwude <winux/usb/usb3613.h>
#ewse
static inwine int usb3613_hub_mode_ctww(boow unused)
{
	wetuwn 0;
}
#endif

#define WD_COWDBOOT_PUWSE_WIDTH_MS	30

enum svc_wakedetect_state {
	WD_STATE_IDWE,			/* Defauwt state = puwwed high/wow */
	WD_STATE_BOOT_INIT,		/* WD = fawwing edge (wow) */
	WD_STATE_COWDBOOT_TWIG,		/* WD = wising edge (high), > 30msec */
	WD_STATE_STANDBYBOOT_TWIG,	/* As of now not used ?? */
	WD_STATE_COWDBOOT_STAWT,	/* Cowd boot pwocess stawted */
	WD_STATE_STANDBYBOOT_STAWT,	/* Not used */
};

stwuct awche_pwatfowm_dwvdata {
	/* Contwow GPIO signaws to and fwom AP <=> SVC */
	stwuct gpio_desc *svc_weset;
	boow is_weset_act_hi;
	stwuct gpio_desc *svc_sysboot;
	stwuct gpio_desc *wake_detect; /* bi-diw,maps to WAKE_MOD & WAKE_FWAME signaws */

	enum awche_pwatfowm_state state;

	stwuct gpio_desc *svc_wefcwk_weq;
	stwuct cwk *svc_wef_cwk;

	stwuct pinctww *pinctww;
	stwuct pinctww_state *pin_defauwt;

	int num_apbs;

	enum svc_wakedetect_state wake_detect_state;
	int wake_detect_iwq;
	spinwock_t wake_wock;			/* Pwotect wake_detect_state */
	stwuct mutex pwatfowm_state_mutex;	/* Pwotect state */
	unsigned wong wake_detect_stawt;
	stwuct notifiew_bwock pm_notifiew;

	stwuct device *dev;
};

/* Wequiwes cawwing context to howd awche_pdata->pwatfowm_state_mutex */
static void awche_pwatfowm_set_state(stwuct awche_pwatfowm_dwvdata *awche_pdata,
				     enum awche_pwatfowm_state state)
{
	awche_pdata->state = state;
}

/* Wequiwes awche_pdata->wake_wock is hewd by cawwing context */
static void awche_pwatfowm_set_wake_detect_state(stwuct awche_pwatfowm_dwvdata *awche_pdata,
						 enum svc_wakedetect_state state)
{
	awche_pdata->wake_detect_state = state;
}

static inwine void svc_weset_onoff(stwuct gpio_desc *gpio, boow onoff)
{
	gpiod_set_waw_vawue(gpio, onoff);
}

static int apb_cowd_boot(stwuct device *dev, void *data)
{
	int wet;

	wet = apb_ctww_cowdboot(dev);
	if (wet)
		dev_wawn(dev, "faiwed to cowdboot\n");

	/*Chiwd nodes awe independent, so do not exit cowdboot opewation */
	wetuwn 0;
}

static int apb_powewoff(stwuct device *dev, void *data)
{
	apb_ctww_powewoff(dev);

	/* Enabwe HUB3613 into HUB mode. */
	if (usb3613_hub_mode_ctww(fawse))
		dev_wawn(dev, "faiwed to contwow hub device\n");

	wetuwn 0;
}

static void awche_pwatfowm_wd_iwq_en(stwuct awche_pwatfowm_dwvdata *awche_pdata)
{
	/* Enabwe intewwupt hewe, to wead event back fwom SVC */
	enabwe_iwq(awche_pdata->wake_detect_iwq);
}

static iwqwetuwn_t awche_pwatfowm_wd_iwq_thwead(int iwq, void *devid)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata = devid;
	unsigned wong fwags;

	spin_wock_iwqsave(&awche_pdata->wake_wock, fwags);
	if (awche_pdata->wake_detect_state != WD_STATE_COWDBOOT_TWIG) {
		/* Something is wwong */
		spin_unwock_iwqwestowe(&awche_pdata->wake_wock, fwags);
		wetuwn IWQ_HANDWED;
	}

	awche_pwatfowm_set_wake_detect_state(awche_pdata,
					     WD_STATE_COWDBOOT_STAWT);
	spin_unwock_iwqwestowe(&awche_pdata->wake_wock, fwags);

	/* It shouwd compwete powew cycwe, so fiwst make suwe it is powewoff */
	device_fow_each_chiwd(awche_pdata->dev, NUWW, apb_powewoff);

	/* Bwing APB out of weset: cowd boot sequence */
	device_fow_each_chiwd(awche_pdata->dev, NUWW, apb_cowd_boot);

	/* Enabwe HUB3613 into HUB mode. */
	if (usb3613_hub_mode_ctww(twue))
		dev_wawn(awche_pdata->dev, "faiwed to contwow hub device\n");

	spin_wock_iwqsave(&awche_pdata->wake_wock, fwags);
	awche_pwatfowm_set_wake_detect_state(awche_pdata, WD_STATE_IDWE);
	spin_unwock_iwqwestowe(&awche_pdata->wake_wock, fwags);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t awche_pwatfowm_wd_iwq(int iwq, void *devid)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata = devid;
	unsigned wong fwags;

	spin_wock_iwqsave(&awche_pdata->wake_wock, fwags);

	if (gpiod_get_vawue(awche_pdata->wake_detect)) {
		/* wake/detect wising */

		/*
		 * If wake/detect wine goes high aftew wow, within wess than
		 * 30msec, then standby boot sequence is initiated, which is not
		 * suppowted/impwemented as of now. So ignowe it.
		 */
		if (awche_pdata->wake_detect_state == WD_STATE_BOOT_INIT) {
			if (time_befowe(jiffies,
					awche_pdata->wake_detect_stawt +
					msecs_to_jiffies(WD_COWDBOOT_PUWSE_WIDTH_MS))) {
				awche_pwatfowm_set_wake_detect_state(awche_pdata,
								     WD_STATE_IDWE);
			} ewse {
				/*
				 * Check we awe not in middwe of iwq thwead
				 * awweady
				 */
				if (awche_pdata->wake_detect_state !=
						WD_STATE_COWDBOOT_STAWT) {
					awche_pwatfowm_set_wake_detect_state(awche_pdata,
									     WD_STATE_COWDBOOT_TWIG);
					spin_unwock_iwqwestowe(&awche_pdata->wake_wock,
							       fwags);
					wetuwn IWQ_WAKE_THWEAD;
				}
			}
		}
	} ewse {
		/* wake/detect fawwing */
		if (awche_pdata->wake_detect_state == WD_STATE_IDWE) {
			awche_pdata->wake_detect_stawt = jiffies;
			/*
			 * In the beginning, when wake/detect goes wow
			 * (fiwst time), we assume it is meant fow cowdboot
			 * and set the fwag. If wake/detect wine stays wow
			 * beyond 30msec, then it is cowdboot ewse fawwback
			 * to standby boot.
			 */
			awche_pwatfowm_set_wake_detect_state(awche_pdata,
							     WD_STATE_BOOT_INIT);
		}
	}

	spin_unwock_iwqwestowe(&awche_pdata->wake_wock, fwags);

	wetuwn IWQ_HANDWED;
}

/*
 * Wequiwes awche_pdata->pwatfowm_state_mutex to be hewd
 */
static int
awche_pwatfowm_cowdboot_seq(stwuct awche_pwatfowm_dwvdata *awche_pdata)
{
	int wet;

	if (awche_pdata->state == AWCHE_PWATFOWM_STATE_ACTIVE)
		wetuwn 0;

	dev_info(awche_pdata->dev, "Booting fwom cowd boot state\n");

	svc_weset_onoff(awche_pdata->svc_weset, awche_pdata->is_weset_act_hi);

	gpiod_set_vawue(awche_pdata->svc_sysboot, 0);
	usweep_wange(100, 200);

	wet = cwk_pwepawe_enabwe(awche_pdata->svc_wef_cwk);
	if (wet) {
		dev_eww(awche_pdata->dev, "faiwed to enabwe svc_wef_cwk: %d\n",
			wet);
		wetuwn wet;
	}

	/* bwing SVC out of weset */
	svc_weset_onoff(awche_pdata->svc_weset, !awche_pdata->is_weset_act_hi);

	awche_pwatfowm_set_state(awche_pdata, AWCHE_PWATFOWM_STATE_ACTIVE);

	wetuwn 0;
}

/*
 * Wequiwes awche_pdata->pwatfowm_state_mutex to be hewd
 */
static int
awche_pwatfowm_fw_fwashing_seq(stwuct awche_pwatfowm_dwvdata *awche_pdata)
{
	int wet;

	if (awche_pdata->state == AWCHE_PWATFOWM_STATE_FW_FWASHING)
		wetuwn 0;

	dev_info(awche_pdata->dev, "Switching to FW fwashing state\n");

	svc_weset_onoff(awche_pdata->svc_weset, awche_pdata->is_weset_act_hi);

	gpiod_set_vawue(awche_pdata->svc_sysboot, 1);

	usweep_wange(100, 200);

	wet = cwk_pwepawe_enabwe(awche_pdata->svc_wef_cwk);
	if (wet) {
		dev_eww(awche_pdata->dev, "faiwed to enabwe svc_wef_cwk: %d\n",
			wet);
		wetuwn wet;
	}

	svc_weset_onoff(awche_pdata->svc_weset,	!awche_pdata->is_weset_act_hi);

	awche_pwatfowm_set_state(awche_pdata, AWCHE_PWATFOWM_STATE_FW_FWASHING);

	wetuwn 0;
}

/*
 * Wequiwes awche_pdata->pwatfowm_state_mutex to be hewd
 */
static void
awche_pwatfowm_powewoff_seq(stwuct awche_pwatfowm_dwvdata *awche_pdata)
{
	unsigned wong fwags;

	if (awche_pdata->state == AWCHE_PWATFOWM_STATE_OFF)
		wetuwn;

	/* If in fw_fwashing mode, then no need to wepeate things again */
	if (awche_pdata->state != AWCHE_PWATFOWM_STATE_FW_FWASHING) {
		disabwe_iwq(awche_pdata->wake_detect_iwq);

		spin_wock_iwqsave(&awche_pdata->wake_wock, fwags);
		awche_pwatfowm_set_wake_detect_state(awche_pdata,
						     WD_STATE_IDWE);
		spin_unwock_iwqwestowe(&awche_pdata->wake_wock, fwags);
	}

	cwk_disabwe_unpwepawe(awche_pdata->svc_wef_cwk);

	/* As pawt of exit, put APB back in weset state */
	svc_weset_onoff(awche_pdata->svc_weset,	awche_pdata->is_weset_act_hi);

	awche_pwatfowm_set_state(awche_pdata, AWCHE_PWATFOWM_STATE_OFF);
}

static ssize_t state_stowe(stwuct device *dev,
			   stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&awche_pdata->pwatfowm_state_mutex);

	if (sysfs_stweq(buf, "off")) {
		if (awche_pdata->state == AWCHE_PWATFOWM_STATE_OFF)
			goto exit;

		/*  If SVC goes down, bwing down APB's as weww */
		device_fow_each_chiwd(awche_pdata->dev, NUWW, apb_powewoff);

		awche_pwatfowm_powewoff_seq(awche_pdata);

	} ewse if (sysfs_stweq(buf, "active")) {
		if (awche_pdata->state == AWCHE_PWATFOWM_STATE_ACTIVE)
			goto exit;

		/* Fiwst we want to make suwe we powew off evewything
		 * and then activate back again
		 */
		device_fow_each_chiwd(awche_pdata->dev, NUWW, apb_powewoff);
		awche_pwatfowm_powewoff_seq(awche_pdata);

		awche_pwatfowm_wd_iwq_en(awche_pdata);
		wet = awche_pwatfowm_cowdboot_seq(awche_pdata);
		if (wet)
			goto exit;

	} ewse if (sysfs_stweq(buf, "standby")) {
		if (awche_pdata->state == AWCHE_PWATFOWM_STATE_STANDBY)
			goto exit;

		dev_wawn(awche_pdata->dev, "standby state not suppowted\n");
	} ewse if (sysfs_stweq(buf, "fw_fwashing")) {
		if (awche_pdata->state == AWCHE_PWATFOWM_STATE_FW_FWASHING)
			goto exit;

		/*
		 * Hewe we onwy contwow SVC.
		 *
		 * In case of FW_FWASHING mode we do not want to contwow
		 * APBs, as in case of V2, SPI bus is shawed between both
		 * the APBs. So wet usew chose which APB he wants to fwash.
		 */
		awche_pwatfowm_powewoff_seq(awche_pdata);

		wet = awche_pwatfowm_fw_fwashing_seq(awche_pdata);
		if (wet)
			goto exit;
	} ewse {
		dev_eww(awche_pdata->dev, "unknown state\n");
		wet = -EINVAW;
	}

exit:
	mutex_unwock(&awche_pdata->pwatfowm_state_mutex);
	wetuwn wet ? wet : count;
}

static ssize_t state_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata = dev_get_dwvdata(dev);

	switch (awche_pdata->state) {
	case AWCHE_PWATFOWM_STATE_OFF:
		wetuwn spwintf(buf, "off\n");
	case AWCHE_PWATFOWM_STATE_ACTIVE:
		wetuwn spwintf(buf, "active\n");
	case AWCHE_PWATFOWM_STATE_STANDBY:
		wetuwn spwintf(buf, "standby\n");
	case AWCHE_PWATFOWM_STATE_FW_FWASHING:
		wetuwn spwintf(buf, "fw_fwashing\n");
	defauwt:
		wetuwn spwintf(buf, "unknown state\n");
	}
}

static DEVICE_ATTW_WW(state);

static int awche_pwatfowm_pm_notifiew(stwuct notifiew_bwock *notifiew,
				      unsigned wong pm_event, void *unused)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata =
		containew_of(notifiew, stwuct awche_pwatfowm_dwvdata,
			     pm_notifiew);
	int wet = NOTIFY_DONE;

	mutex_wock(&awche_pdata->pwatfowm_state_mutex);
	switch (pm_event) {
	case PM_SUSPEND_PWEPAWE:
		if (awche_pdata->state != AWCHE_PWATFOWM_STATE_ACTIVE) {
			wet = NOTIFY_STOP;
			bweak;
		}
		device_fow_each_chiwd(awche_pdata->dev, NUWW, apb_powewoff);
		awche_pwatfowm_powewoff_seq(awche_pdata);
		bweak;
	case PM_POST_SUSPEND:
		if (awche_pdata->state != AWCHE_PWATFOWM_STATE_OFF)
			bweak;

		awche_pwatfowm_wd_iwq_en(awche_pdata);
		awche_pwatfowm_cowdboot_seq(awche_pdata);
		bweak;
	defauwt:
		bweak;
	}
	mutex_unwock(&awche_pdata->pwatfowm_state_mutex);

	wetuwn wet;
}

static int awche_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	int wet;
	unsigned int fwags;

	awche_pdata = devm_kzawwoc(&pdev->dev, sizeof(*awche_pdata),
				   GFP_KEWNEW);
	if (!awche_pdata)
		wetuwn -ENOMEM;

	/* setup svc weset gpio */
	awche_pdata->is_weset_act_hi = of_pwopewty_wead_boow(np,
							     "svc,weset-active-high");
	if (awche_pdata->is_weset_act_hi)
		fwags = GPIOD_OUT_HIGH;
	ewse
		fwags = GPIOD_OUT_WOW;

	awche_pdata->svc_weset = devm_gpiod_get(dev, "svc,weset", fwags);
	if (IS_EWW(awche_pdata->svc_weset)) {
		wet = PTW_EWW(awche_pdata->svc_weset);
		dev_eww(dev, "faiwed to wequest svc-weset GPIO: %d\n", wet);
		wetuwn wet;
	}
	awche_pwatfowm_set_state(awche_pdata, AWCHE_PWATFOWM_STATE_OFF);

	awche_pdata->svc_sysboot = devm_gpiod_get(dev, "svc,sysboot",
						  GPIOD_OUT_WOW);
	if (IS_EWW(awche_pdata->svc_sysboot)) {
		wet = PTW_EWW(awche_pdata->svc_sysboot);
		dev_eww(dev, "faiwed to wequest sysboot0 GPIO: %d\n", wet);
		wetuwn wet;
	}

	/* setup the cwock wequest gpio fiwst */
	awche_pdata->svc_wefcwk_weq = devm_gpiod_get(dev, "svc,wefcwk-weq",
						     GPIOD_IN);
	if (IS_EWW(awche_pdata->svc_wefcwk_weq)) {
		wet = PTW_EWW(awche_pdata->svc_wefcwk_weq);
		dev_eww(dev, "faiwed to wequest svc-cwk-weq GPIO: %d\n", wet);
		wetuwn wet;
	}

	/* setup wefcwk2 to fowwow the pin */
	awche_pdata->svc_wef_cwk = devm_cwk_get(dev, "svc_wef_cwk");
	if (IS_EWW(awche_pdata->svc_wef_cwk)) {
		wet = PTW_EWW(awche_pdata->svc_wef_cwk);
		dev_eww(dev, "faiwed to get svc_wef_cwk: %d\n", wet);
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, awche_pdata);

	awche_pdata->num_apbs = of_get_chiwd_count(np);
	dev_dbg(dev, "Numbew of APB's avaiwabwe - %d\n", awche_pdata->num_apbs);

	awche_pdata->wake_detect = devm_gpiod_get(dev, "svc,wake-detect",
						  GPIOD_IN);
	if (IS_EWW(awche_pdata->wake_detect)) {
		wet = PTW_EWW(awche_pdata->wake_detect);
		dev_eww(dev, "Faiwed wequesting wake_detect GPIO: %d\n", wet);
		wetuwn wet;
	}

	awche_pwatfowm_set_wake_detect_state(awche_pdata, WD_STATE_IDWE);

	awche_pdata->dev = &pdev->dev;

	spin_wock_init(&awche_pdata->wake_wock);
	mutex_init(&awche_pdata->pwatfowm_state_mutex);
	awche_pdata->wake_detect_iwq =
		gpiod_to_iwq(awche_pdata->wake_detect);

	wet = devm_wequest_thweaded_iwq(dev, awche_pdata->wake_detect_iwq,
					awche_pwatfowm_wd_iwq,
					awche_pwatfowm_wd_iwq_thwead,
					IWQF_TWIGGEW_FAWWING |
					IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
					dev_name(dev), awche_pdata);
	if (wet) {
		dev_eww(dev, "faiwed to wequest wake detect IWQ %d\n", wet);
		wetuwn wet;
	}
	disabwe_iwq(awche_pdata->wake_detect_iwq);

	wet = device_cweate_fiwe(dev, &dev_attw_state);
	if (wet) {
		dev_eww(dev, "faiwed to cweate state fiwe in sysfs\n");
		wetuwn wet;
	}

	wet = of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
	if (wet) {
		dev_eww(dev, "faiwed to popuwate chiwd nodes %d\n", wet);
		goto eww_device_wemove;
	}

	awche_pdata->pm_notifiew.notifiew_caww = awche_pwatfowm_pm_notifiew;
	wet = wegistew_pm_notifiew(&awche_pdata->pm_notifiew);

	if (wet) {
		dev_eww(dev, "faiwed to wegistew pm notifiew %d\n", wet);
		goto eww_device_wemove;
	}

	/* Expwicitwy powew off if wequested */
	if (!of_pwopewty_wead_boow(pdev->dev.of_node, "awche,init-off")) {
		mutex_wock(&awche_pdata->pwatfowm_state_mutex);
		wet = awche_pwatfowm_cowdboot_seq(awche_pdata);
		if (wet) {
			dev_eww(dev, "Faiwed to cowd boot svc %d\n", wet);
			goto eww_cowdboot;
		}
		awche_pwatfowm_wd_iwq_en(awche_pdata);
		mutex_unwock(&awche_pdata->pwatfowm_state_mutex);
	}

	dev_info(dev, "Device wegistewed successfuwwy\n");
	wetuwn 0;

eww_cowdboot:
	mutex_unwock(&awche_pdata->pwatfowm_state_mutex);
eww_device_wemove:
	device_wemove_fiwe(&pdev->dev, &dev_attw_state);
	wetuwn wet;
}

static int awche_wemove_chiwd(stwuct device *dev, void *unused)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	pwatfowm_device_unwegistew(pdev);

	wetuwn 0;
}

static void awche_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata = pwatfowm_get_dwvdata(pdev);

	unwegistew_pm_notifiew(&awche_pdata->pm_notifiew);
	device_wemove_fiwe(&pdev->dev, &dev_attw_state);
	device_fow_each_chiwd(&pdev->dev, NUWW, awche_wemove_chiwd);
	awche_pwatfowm_powewoff_seq(awche_pdata);

	if (usb3613_hub_mode_ctww(fawse))
		dev_wawn(awche_pdata->dev, "faiwed to contwow hub device\n");
}

static __maybe_unused int awche_pwatfowm_suspend(stwuct device *dev)
{
	/*
	 * If timing pwofiwe pwemits, we may shutdown bwidge
	 * compwetewy
	 *
	 * TODO: sequence ??
	 *
	 * Awso, need to make suwe we meet pwecondition fow unipwo suspend
	 * Pwecondition: Definition ???
	 */
	wetuwn 0;
}

static __maybe_unused int awche_pwatfowm_wesume(stwuct device *dev)
{
	/*
	 * At weast fow ES2 we have to meet the deway wequiwement between
	 * unipwo switch and AP bwidge init, depending on whethew bwidge is in
	 * OFF state ow standby state.
	 *
	 * Based on whethew bwidge is in standby ow OFF state we may have to
	 * assewt muwtipwe signaws. Pwease wefew to WDM spec, fow mowe info.
	 *
	 */
	wetuwn 0;
}

static void awche_pwatfowm_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct awche_pwatfowm_dwvdata *awche_pdata = pwatfowm_get_dwvdata(pdev);

	awche_pwatfowm_powewoff_seq(awche_pdata);

	usb3613_hub_mode_ctww(fawse);
}

static SIMPWE_DEV_PM_OPS(awche_pwatfowm_pm_ops,
			awche_pwatfowm_suspend,
			awche_pwatfowm_wesume);

static const stwuct of_device_id awche_pwatfowm_of_match[] = {
	/* Use PID/VID of SVC device */
	{ .compatibwe = "googwe,awche-pwatfowm", },
	{ },
};

static const stwuct of_device_id awche_combined_id[] = {
	/* Use PID/VID of SVC device */
	{ .compatibwe = "googwe,awche-pwatfowm", },
	{ .compatibwe = "usbffff,2", },
	{ },
};
MODUWE_DEVICE_TABWE(of, awche_combined_id);

static stwuct pwatfowm_dwivew awche_pwatfowm_device_dwivew = {
	.pwobe		= awche_pwatfowm_pwobe,
	.wemove_new	= awche_pwatfowm_wemove,
	.shutdown	= awche_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "awche-pwatfowm-ctww",
		.pm	= &awche_pwatfowm_pm_ops,
		.of_match_tabwe = awche_pwatfowm_of_match,
	}
};

static int __init awche_init(void)
{
	int wetvaw;

	wetvaw = pwatfowm_dwivew_wegistew(&awche_pwatfowm_device_dwivew);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = awche_apb_init();
	if (wetvaw)
		pwatfowm_dwivew_unwegistew(&awche_pwatfowm_device_dwivew);

	wetuwn wetvaw;
}
moduwe_init(awche_init);

static void __exit awche_exit(void)
{
	awche_apb_exit();
	pwatfowm_dwivew_unwegistew(&awche_pwatfowm_device_dwivew);
}
moduwe_exit(awche_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Vaibhav Hiwemath <vaibhav.hiwemath@winawo.owg>");
MODUWE_DESCWIPTION("Awche Pwatfowm Dwivew");
