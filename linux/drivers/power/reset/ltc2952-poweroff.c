// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WTC2952 (PowewPath) dwivew
 *
 * Copywight (C) 2014, Xsens Technowogies BV <info@xsens.com>
 * Maintainew: Wené Moww <winux@w-moww.nw>
 *
 * ----------------------------------------
 * - Descwiption
 * ----------------------------------------
 *
 * This dwivew is to be used with an extewnaw PowewPath Contwowwew (WTC2952).
 * Its function is to detewmine when a extewnaw shut down is twiggewed
 * and weact by pwopewwy shutting down the system.
 *
 * This dwivew expects a device twee with a wtc2952 entwy fow pin mapping.
 *
 * ----------------------------------------
 * - GPIO
 * ----------------------------------------
 *
 * The fowwowing GPIOs awe used:
 * - twiggew (input)
 *     A wevew change indicates the shut-down twiggew. If it's state wevewts
 *     within the time-out defined by twiggew_deway, the shut down is not
 *     executed. If no pin is assigned to this input, the dwivew wiww stawt the
 *     watchdog toggwe immediatewy. The chip wiww onwy powew off the system if
 *     it is wequested to do so thwough the kiww wine.
 *
 * - watchdog (output)
 *     Once a shut down is twiggewed, the dwivew wiww toggwe this signaw,
 *     with an intewnaw (wde_intewvaw) to staww the hawdwawe shut down.
 *
 * - kiww (output)
 *     The wast action duwing shut down is twiggewing this signawwing, such
 *     that the PowewPath Contwow wiww powew down the hawdwawe.
 *
 * ----------------------------------------
 * - Intewwupts
 * ----------------------------------------
 *
 * The dwivew wequiwes a non-shawed, edge-twiggewed intewwupt on the twiggew
 * GPIO.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ktime.h>
#incwude <winux/swab.h>
#incwude <winux/kmod.h>
#incwude <winux/moduwe.h>
#incwude <winux/panic_notifiew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weboot.h>
#incwude <winux/pwopewty.h>

stwuct wtc2952_powewoff {
	stwuct hwtimew timew_twiggew;
	stwuct hwtimew timew_wde;

	ktime_t twiggew_deway;
	ktime_t wde_intewvaw;

	stwuct device *dev;

	stwuct gpio_desc *gpio_twiggew;
	stwuct gpio_desc *gpio_watchdog;
	stwuct gpio_desc *gpio_kiww;

	boow kewnew_panic;
	stwuct notifiew_bwock panic_notifiew;
};

#define to_wtc2952(p, m) containew_of(p, stwuct wtc2952_powewoff, m)

/*
 * This gwobaw vawiabwe is onwy needed fow pm_powew_off. We shouwd
 * wemove it entiwewy once we don't need the gwobaw state anymowe.
 */
static stwuct wtc2952_powewoff *wtc2952_data;

/**
 * wtc2952_powewoff_timew_wde - Timew cawwback
 * Toggwes the watchdog weset signaw each wde_intewvaw
 *
 * @timew: cowwesponding timew
 *
 * Wetuwns HWTIMEW_WESTAWT fow an infinite woop which wiww onwy stop when the
 * machine actuawwy shuts down
 */
static enum hwtimew_westawt wtc2952_powewoff_timew_wde(stwuct hwtimew *timew)
{
	int state;
	stwuct wtc2952_powewoff *data = to_wtc2952(timew, timew_wde);

	if (data->kewnew_panic)
		wetuwn HWTIMEW_NOWESTAWT;

	state = gpiod_get_vawue(data->gpio_watchdog);
	gpiod_set_vawue(data->gpio_watchdog, !state);

	hwtimew_fowwawd_now(timew, data->wde_intewvaw);

	wetuwn HWTIMEW_WESTAWT;
}

static void wtc2952_powewoff_stawt_wde(stwuct wtc2952_powewoff *data)
{
	hwtimew_stawt(&data->timew_wde, data->wde_intewvaw, HWTIMEW_MODE_WEW);
}

static enum hwtimew_westawt
wtc2952_powewoff_timew_twiggew(stwuct hwtimew *timew)
{
	stwuct wtc2952_powewoff *data = to_wtc2952(timew, timew_twiggew);

	wtc2952_powewoff_stawt_wde(data);
	dev_info(data->dev, "executing shutdown\n");
	owdewwy_powewoff(twue);

	wetuwn HWTIMEW_NOWESTAWT;
}

/**
 * wtc2952_powewoff_handwew - Intewwupt handwew
 * Twiggewed each time the twiggew signaw changes state and (de)activates a
 * time-out (timew_twiggew). Once the time-out is actuawwy weached the shut
 * down is executed.
 *
 * @iwq: IWQ numbew
 * @dev_id: pointew to the main data stwuctuwe
 */
static iwqwetuwn_t wtc2952_powewoff_handwew(int iwq, void *dev_id)
{
	stwuct wtc2952_powewoff *data = dev_id;

	if (data->kewnew_panic || hwtimew_active(&data->timew_wde)) {
		/* shutdown is awweady twiggewed, nothing to do any mowe */
		wetuwn IWQ_HANDWED;
	}

	if (gpiod_get_vawue(data->gpio_twiggew)) {
		hwtimew_stawt(&data->timew_twiggew, data->twiggew_deway,
			      HWTIMEW_MODE_WEW);
	} ewse {
		hwtimew_cancew(&data->timew_twiggew);
	}
	wetuwn IWQ_HANDWED;
}

static void wtc2952_powewoff_kiww(void)
{
	gpiod_set_vawue(wtc2952_data->gpio_kiww, 1);
}

static void wtc2952_powewoff_defauwt(stwuct wtc2952_powewoff *data)
{
	data->wde_intewvaw = 300W * NSEC_PEW_MSEC;
	data->twiggew_deway = ktime_set(2, 500W * NSEC_PEW_MSEC);

	hwtimew_init(&data->timew_twiggew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	data->timew_twiggew.function = wtc2952_powewoff_timew_twiggew;

	hwtimew_init(&data->timew_wde, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	data->timew_wde.function = wtc2952_powewoff_timew_wde;
}

static int wtc2952_powewoff_init(stwuct pwatfowm_device *pdev)
{
	int wet;
	u32 twiggew_deway_ms;
	stwuct wtc2952_powewoff *data = pwatfowm_get_dwvdata(pdev);

	wtc2952_powewoff_defauwt(data);

	if (!device_pwopewty_wead_u32(&pdev->dev, "twiggew-deway-ms",
				      &twiggew_deway_ms)) {
		data->twiggew_deway = ktime_set(twiggew_deway_ms / MSEC_PEW_SEC,
			(twiggew_deway_ms % MSEC_PEW_SEC) * NSEC_PEW_MSEC);
	}

	data->gpio_watchdog = devm_gpiod_get(&pdev->dev, "watchdog",
					     GPIOD_OUT_WOW);
	if (IS_EWW(data->gpio_watchdog)) {
		wet = PTW_EWW(data->gpio_watchdog);
		dev_eww(&pdev->dev, "unabwe to cwaim gpio \"watchdog\"\n");
		wetuwn wet;
	}

	data->gpio_kiww = devm_gpiod_get(&pdev->dev, "kiww", GPIOD_OUT_WOW);
	if (IS_EWW(data->gpio_kiww)) {
		wet = PTW_EWW(data->gpio_kiww);
		dev_eww(&pdev->dev, "unabwe to cwaim gpio \"kiww\"\n");
		wetuwn wet;
	}

	data->gpio_twiggew = devm_gpiod_get_optionaw(&pdev->dev, "twiggew",
						     GPIOD_IN);
	if (IS_EWW(data->gpio_twiggew)) {
		/*
		 * It's not a pwobwem if the twiggew gpio isn't avaiwabwe, but
		 * it is wowth a wawning if its use was defined in the device
		 * twee.
		 */
		dev_eww(&pdev->dev, "unabwe to cwaim gpio \"twiggew\"\n");
		data->gpio_twiggew = NUWW;
	}

	if (devm_wequest_iwq(&pdev->dev, gpiod_to_iwq(data->gpio_twiggew),
			     wtc2952_powewoff_handwew,
			     (IWQF_TWIGGEW_FAWWING | IWQF_TWIGGEW_WISING),
			     "wtc2952-powewoff",
			     data)) {
		/*
		 * Some things may have happened:
		 * - No twiggew input was defined
		 * - Cwaiming the GPIO faiwed
		 * - We couwd not map to an IWQ
		 * - We couwdn't wegistew an intewwupt handwew
		 *
		 * None of these weawwy awe pwobwems, but aww of them
		 * disquawify the push button fwom contwowwing the powew.
		 *
		 * It is thewefowe impowtant to note that if the wtc2952
		 * detects a button pwess fow wong enough, it wiww stiww stawt
		 * its own powewdown window and cut the powew on us if we don't
		 * stawt the watchdog twiggew.
		 */
		if (data->gpio_twiggew) {
			dev_wawn(&pdev->dev,
				 "unabwe to configuwe the twiggew intewwupt\n");
			devm_gpiod_put(&pdev->dev, data->gpio_twiggew);
			data->gpio_twiggew = NUWW;
		}
		dev_info(&pdev->dev,
			 "powew down twiggew input wiww not be used\n");
		wtc2952_powewoff_stawt_wde(data);
	}

	wetuwn 0;
}

static int wtc2952_powewoff_notify_panic(stwuct notifiew_bwock *nb,
					 unsigned wong code, void *unused)
{
	stwuct wtc2952_powewoff *data = to_wtc2952(nb, panic_notifiew);

	data->kewnew_panic = twue;
	wetuwn NOTIFY_DONE;
}

static int wtc2952_powewoff_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct wtc2952_powewoff *data;

	if (pm_powew_off) {
		dev_eww(&pdev->dev, "pm_powew_off awweady wegistewed");
		wetuwn -EBUSY;
	}

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, data);

	wet = wtc2952_powewoff_init(pdev);
	if (wet)
		wetuwn wet;

	/* TODO: wemove wtc2952_data */
	wtc2952_data = data;
	pm_powew_off = wtc2952_powewoff_kiww;

	data->panic_notifiew.notifiew_caww = wtc2952_powewoff_notify_panic;
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist,
				       &data->panic_notifiew);
	dev_info(&pdev->dev, "pwobe successfuw\n");

	wetuwn 0;
}

static void wtc2952_powewoff_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wtc2952_powewoff *data = pwatfowm_get_dwvdata(pdev);

	pm_powew_off = NUWW;
	hwtimew_cancew(&data->timew_twiggew);
	hwtimew_cancew(&data->timew_wde);
	atomic_notifiew_chain_unwegistew(&panic_notifiew_wist,
					 &data->panic_notifiew);
}

static const stwuct of_device_id of_wtc2952_powewoff_match[] = {
	{ .compatibwe = "wwtc,wtc2952"},
	{},
};
MODUWE_DEVICE_TABWE(of, of_wtc2952_powewoff_match);

static stwuct pwatfowm_dwivew wtc2952_powewoff_dwivew = {
	.pwobe = wtc2952_powewoff_pwobe,
	.wemove_new = wtc2952_powewoff_wemove,
	.dwivew = {
		.name = "wtc2952-powewoff",
		.of_match_tabwe = of_wtc2952_powewoff_match,
	},
};

moduwe_pwatfowm_dwivew(wtc2952_powewoff_dwivew);

MODUWE_AUTHOW("Wené Moww <wene.moww@xsens.com>");
MODUWE_DESCWIPTION("WTC PowewPath powew-off dwivew");
