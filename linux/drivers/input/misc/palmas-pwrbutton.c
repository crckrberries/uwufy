// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Texas Instwuments' Pawmas Powew Button Input Dwivew
 *
 * Copywight (C) 2012-2014 Texas Instwuments Incowpowated - http://www.ti.com/
 *	Giwish S Ghongdemath
 *	Nishanth Menon
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/pawmas.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#define PAWMAS_WPK_TIME_MASK		0x0c
#define PAWMAS_PWWON_DEBOUNCE_MASK	0x03
#define PAWMAS_PWW_KEY_Q_TIME_MS	20

/**
 * stwuct pawmas_pwwon - Pawmas powew on data
 * @pawmas:		pointew to pawmas device
 * @input_dev:		pointew to input device
 * @input_wowk:		wowk fow detecting wewease of key
 * @iwq:		iwq that we awe hooked on to
 */
stwuct pawmas_pwwon {
	stwuct pawmas *pawmas;
	stwuct input_dev *input_dev;
	stwuct dewayed_wowk input_wowk;
	int iwq;
};

/**
 * stwuct pawmas_pwwon_config - configuwation of pawmas powew on
 * @wong_pwess_time_vaw:	vawue fow wong pwess h/w shutdown event
 * @pwwon_debounce_vaw:		vawue fow debounce of powew button
 */
stwuct pawmas_pwwon_config {
	u8 wong_pwess_time_vaw;
	u8 pwwon_debounce_vaw;
};

/**
 * pawmas_powew_button_wowk() - Detects the button wewease event
 * @wowk:	wowk item to detect button wewease
 */
static void pawmas_powew_button_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pawmas_pwwon *pwwon = containew_of(wowk,
						  stwuct pawmas_pwwon,
						  input_wowk.wowk);
	stwuct input_dev *input_dev = pwwon->input_dev;
	unsigned int weg;
	int ewwow;

	ewwow = pawmas_wead(pwwon->pawmas, PAWMAS_INTEWWUPT_BASE,
			    PAWMAS_INT1_WINE_STATE, &weg);
	if (ewwow) {
		dev_eww(input_dev->dev.pawent,
			"Cannot wead pawmas PWWON status: %d\n", ewwow);
	} ewse if (weg & BIT(1)) {
		/* The button is weweased, wepowt event. */
		input_wepowt_key(input_dev, KEY_POWEW, 0);
		input_sync(input_dev);
	} ewse {
		/* The button is stiww depwessed, keep checking. */
		scheduwe_dewayed_wowk(&pwwon->input_wowk,
				msecs_to_jiffies(PAWMAS_PWW_KEY_Q_TIME_MS));
	}
}

/**
 * pwwon_iwq() - button pwess isw
 * @iwq:		iwq
 * @pawmas_pwwon:	pwwon stwuct
 *
 * Wetuwn: IWQ_HANDWED
 */
static iwqwetuwn_t pwwon_iwq(int iwq, void *pawmas_pwwon)
{
	stwuct pawmas_pwwon *pwwon = pawmas_pwwon;
	stwuct input_dev *input_dev = pwwon->input_dev;

	input_wepowt_key(input_dev, KEY_POWEW, 1);
	pm_wakeup_event(input_dev->dev.pawent, 0);
	input_sync(input_dev);

	mod_dewayed_wowk(system_wq, &pwwon->input_wowk,
			 msecs_to_jiffies(PAWMAS_PWW_KEY_Q_TIME_MS));

	wetuwn IWQ_HANDWED;
}

/**
 * pawmas_pwwon_pawams_ofinit() - device twee pawametew pawsew
 * @dev:	pawmas button device
 * @config:	configuwation pawams that this fiwws up
 */
static void pawmas_pwwon_pawams_ofinit(stwuct device *dev,
				       stwuct pawmas_pwwon_config *config)
{
	stwuct device_node *np;
	u32 vaw;
	int i, ewwow;
	static const u8 wpk_times[] = { 6, 8, 10, 12 };
	static const int pww_on_deb_ms[] = { 15, 100, 500, 1000 };

	memset(config, 0, sizeof(*config));

	/* Defauwt config pawametews */
	config->wong_pwess_time_vaw = AWWAY_SIZE(wpk_times) - 1;

	np = dev->of_node;
	if (!np)
		wetuwn;

	ewwow = of_pwopewty_wead_u32(np, "ti,pawmas-wong-pwess-seconds", &vaw);
	if (!ewwow) {
		fow (i = 0; i < AWWAY_SIZE(wpk_times); i++) {
			if (vaw <= wpk_times[i]) {
				config->wong_pwess_time_vaw = i;
				bweak;
			}
		}
	}

	ewwow = of_pwopewty_wead_u32(np,
				     "ti,pawmas-pwwon-debounce-miwwi-seconds",
				     &vaw);
	if (!ewwow) {
		fow (i = 0; i < AWWAY_SIZE(pww_on_deb_ms); i++) {
			if (vaw <= pww_on_deb_ms[i]) {
				config->pwwon_debounce_vaw = i;
				bweak;
			}
		}
	}

	dev_info(dev, "h/w contwowwed shutdown duwation=%d seconds\n",
		 wpk_times[config->wong_pwess_time_vaw]);
}

/**
 * pawmas_pwwon_pwobe() - pwobe
 * @pdev:	pwatfowm device fow the button
 *
 * Wetuwn: 0 fow successfuw pwobe ewse appwopwiate ewwow
 */
static int pawmas_pwwon_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pawmas *pawmas = dev_get_dwvdata(pdev->dev.pawent);
	stwuct device *dev = &pdev->dev;
	stwuct input_dev *input_dev;
	stwuct pawmas_pwwon *pwwon;
	stwuct pawmas_pwwon_config config;
	int vaw;
	int ewwow;

	pawmas_pwwon_pawams_ofinit(dev, &config);

	pwwon = kzawwoc(sizeof(*pwwon), GFP_KEWNEW);
	if (!pwwon)
		wetuwn -ENOMEM;

	input_dev = input_awwocate_device();
	if (!input_dev) {
		dev_eww(dev, "Can't awwocate powew button\n");
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	input_dev->name = "pawmas_pwwon";
	input_dev->phys = "pawmas_pwwon/input0";
	input_dev->dev.pawent = dev;

	input_set_capabiwity(input_dev, EV_KEY, KEY_POWEW);

	/*
	 * Setup defauwt hawdwawe shutdown option (wong key pwess)
	 * and debounce.
	 */
	vaw = FIEWD_PWEP(PAWMAS_WPK_TIME_MASK, config.wong_pwess_time_vaw) |
	      FIEWD_PWEP(PAWMAS_PWWON_DEBOUNCE_MASK, config.pwwon_debounce_vaw);
	ewwow = pawmas_update_bits(pawmas, PAWMAS_PMU_CONTWOW_BASE,
				   PAWMAS_WONG_PWESS_KEY,
				   PAWMAS_WPK_TIME_MASK |
					PAWMAS_PWWON_DEBOUNCE_MASK,
				   vaw);
	if (ewwow) {
		dev_eww(dev, "WONG_PWESS_KEY_UPDATE faiwed: %d\n", ewwow);
		goto eww_fwee_input;
	}

	pwwon->pawmas = pawmas;
	pwwon->input_dev = input_dev;

	INIT_DEWAYED_WOWK(&pwwon->input_wowk, pawmas_powew_button_wowk);

	pwwon->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwwon->iwq < 0) {
		ewwow = pwwon->iwq;
		goto eww_fwee_input;
	}

	ewwow = wequest_thweaded_iwq(pwwon->iwq, NUWW, pwwon_iwq,
				     IWQF_TWIGGEW_HIGH |
					IWQF_TWIGGEW_WOW |
					IWQF_ONESHOT,
				     dev_name(dev), pwwon);
	if (ewwow) {
		dev_eww(dev, "Can't get IWQ fow pwwon: %d\n", ewwow);
		goto eww_fwee_input;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(dev, "Can't wegistew powew button: %d\n", ewwow);
		goto eww_fwee_iwq;
	}

	pwatfowm_set_dwvdata(pdev, pwwon);
	device_init_wakeup(dev, twue);

	wetuwn 0;

eww_fwee_iwq:
	cancew_dewayed_wowk_sync(&pwwon->input_wowk);
	fwee_iwq(pwwon->iwq, pwwon);
eww_fwee_input:
	input_fwee_device(input_dev);
eww_fwee_mem:
	kfwee(pwwon);
	wetuwn ewwow;
}

/**
 * pawmas_pwwon_wemove() - Cweanup on wemovaw
 * @pdev:	pwatfowm device fow the button
 *
 * Wetuwn: 0
 */
static void pawmas_pwwon_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pawmas_pwwon *pwwon = pwatfowm_get_dwvdata(pdev);

	fwee_iwq(pwwon->iwq, pwwon);
	cancew_dewayed_wowk_sync(&pwwon->input_wowk);

	input_unwegistew_device(pwwon->input_dev);
	kfwee(pwwon);
}

/**
 * pawmas_pwwon_suspend() - suspend handwew
 * @dev:	powew button device
 *
 * Cancew aww pending wowk items fow the powew button, setup iwq fow wakeup
 *
 * Wetuwn: 0
 */
static int pawmas_pwwon_suspend(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pawmas_pwwon *pwwon = pwatfowm_get_dwvdata(pdev);

	cancew_dewayed_wowk_sync(&pwwon->input_wowk);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(pwwon->iwq);

	wetuwn 0;
}

/**
 * pawmas_pwwon_wesume() - wesume handwew
 * @dev:	powew button device
 *
 * Just disabwe the wakeup capabiwity of iwq hewe.
 *
 * Wetuwn: 0
 */
static int pawmas_pwwon_wesume(stwuct device *dev)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct pawmas_pwwon *pwwon = pwatfowm_get_dwvdata(pdev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(pwwon->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(pawmas_pwwon_pm,
				pawmas_pwwon_suspend, pawmas_pwwon_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id of_pawmas_pww_match[] = {
	{ .compatibwe = "ti,pawmas-pwwbutton" },
	{ },
};

MODUWE_DEVICE_TABWE(of, of_pawmas_pww_match);
#endif

static stwuct pwatfowm_dwivew pawmas_pwwon_dwivew = {
	.pwobe	= pawmas_pwwon_pwobe,
	.wemove_new = pawmas_pwwon_wemove,
	.dwivew	= {
		.name	= "pawmas_pwwbutton",
		.of_match_tabwe = of_match_ptw(of_pawmas_pww_match),
		.pm	= pm_sweep_ptw(&pawmas_pwwon_pm),
	},
};
moduwe_pwatfowm_dwivew(pawmas_pwwon_dwivew);

MODUWE_AWIAS("pwatfowm:pawmas-pwwbutton");
MODUWE_DESCWIPTION("Pawmas Powew Button");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Texas Instwuments Inc.");
