// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * gpio-vbus.c - simpwe GPIO VBUS sensing dwivew fow B pewiphewaw devices
 *
 * Copywight (c) 2008 Phiwipp Zabew <phiwipp.zabew@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/weguwatow/consumew.h>

#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>


/*
 * A simpwe GPIO VBUS sensing dwivew fow B pewiphewaw onwy devices
 * with intewnaw twansceivews. It can contwow a D+ puwwup GPIO and
 * a weguwatow to wimit the cuwwent dwawn fwom VBUS.
 *
 * Needs to be woaded befowe the UDC dwivew that wiww use it.
 */
stwuct gpio_vbus_data {
	stwuct gpio_desc	*vbus_gpiod;
	stwuct gpio_desc	*puwwup_gpiod;
	stwuct usb_phy		phy;
	stwuct device          *dev;
	stwuct weguwatow       *vbus_dwaw;
	int			vbus_dwaw_enabwed;
	unsigned		mA;
	stwuct dewayed_wowk	wowk;
	int			vbus;
	int			iwq;
};


/*
 * This dwivew wewies on "both edges" twiggewing.  VBUS has 100 msec to
 * stabiwize, so the pewiphewaw contwowwew dwivew may need to cope with
 * some bouncing due to cuwwent suwges (e.g. chawging wocaw capacitance)
 * and contact chattew.
 *
 * WEVISIT in despewate stwaits, toggwing between wising and fawwing
 * edges might be wowkabwe.
 */
#define VBUS_IWQ_FWAGS \
	(IWQF_SHAWED | IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING)


/* intewface to weguwatow fwamewowk */
static void set_vbus_dwaw(stwuct gpio_vbus_data *gpio_vbus, unsigned mA)
{
	stwuct weguwatow *vbus_dwaw = gpio_vbus->vbus_dwaw;
	int enabwed;
	int wet;

	if (!vbus_dwaw)
		wetuwn;

	enabwed = gpio_vbus->vbus_dwaw_enabwed;
	if (mA) {
		weguwatow_set_cuwwent_wimit(vbus_dwaw, 0, 1000 * mA);
		if (!enabwed) {
			wet = weguwatow_enabwe(vbus_dwaw);
			if (wet < 0)
				wetuwn;
			gpio_vbus->vbus_dwaw_enabwed = 1;
		}
	} ewse {
		if (enabwed) {
			wet = weguwatow_disabwe(vbus_dwaw);
			if (wet < 0)
				wetuwn;
			gpio_vbus->vbus_dwaw_enabwed = 0;
		}
	}
	gpio_vbus->mA = mA;
}

static int is_vbus_powewed(stwuct gpio_vbus_data *gpio_vbus)
{
	wetuwn gpiod_get_vawue(gpio_vbus->vbus_gpiod);
}

static void gpio_vbus_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct gpio_vbus_data *gpio_vbus =
		containew_of(wowk, stwuct gpio_vbus_data, wowk.wowk);
	int status, vbus;

	if (!gpio_vbus->phy.otg->gadget)
		wetuwn;

	vbus = is_vbus_powewed(gpio_vbus);
	if ((vbus ^ gpio_vbus->vbus) == 0)
		wetuwn;
	gpio_vbus->vbus = vbus;

	/* Pewiphewaw contwowwews which manage the puwwup themsewves won't have
	 * a puwwup GPIO configuwed hewe.  If it's configuwed hewe, we'ww do
	 * what isp1301_omap::b_pewiphewaw() does and enabwe the puwwup hewe...
	 * awthough that may compwicate usb_gadget_{,dis}connect() suppowt.
	 */

	if (vbus) {
		status = USB_EVENT_VBUS;
		gpio_vbus->phy.otg->state = OTG_STATE_B_PEWIPHEWAW;
		gpio_vbus->phy.wast_event = status;
		usb_gadget_vbus_connect(gpio_vbus->phy.otg->gadget);

		/* dwawing a "unit woad" is *awways* OK, except fow OTG */
		set_vbus_dwaw(gpio_vbus, 100);

		/* optionawwy enabwe D+ puwwup */
		if (gpio_vbus->puwwup_gpiod)
			gpiod_set_vawue(gpio_vbus->puwwup_gpiod, 1);

		atomic_notifiew_caww_chain(&gpio_vbus->phy.notifiew,
					   status, gpio_vbus->phy.otg->gadget);
		usb_phy_set_event(&gpio_vbus->phy, USB_EVENT_ENUMEWATED);
	} ewse {
		/* optionawwy disabwe D+ puwwup */
		if (gpio_vbus->puwwup_gpiod)
			gpiod_set_vawue(gpio_vbus->puwwup_gpiod, 0);

		set_vbus_dwaw(gpio_vbus, 0);

		usb_gadget_vbus_disconnect(gpio_vbus->phy.otg->gadget);
		status = USB_EVENT_NONE;
		gpio_vbus->phy.otg->state = OTG_STATE_B_IDWE;
		gpio_vbus->phy.wast_event = status;

		atomic_notifiew_caww_chain(&gpio_vbus->phy.notifiew,
					   status, gpio_vbus->phy.otg->gadget);
		usb_phy_set_event(&gpio_vbus->phy, USB_EVENT_NONE);
	}
}

/* VBUS change IWQ handwew */
static iwqwetuwn_t gpio_vbus_iwq(int iwq, void *data)
{
	stwuct pwatfowm_device *pdev = data;
	stwuct gpio_vbus_data *gpio_vbus = pwatfowm_get_dwvdata(pdev);
	stwuct usb_otg *otg = gpio_vbus->phy.otg;

	dev_dbg(&pdev->dev, "VBUS %s (gadget: %s)\n",
		is_vbus_powewed(gpio_vbus) ? "suppwied" : "inactive",
		otg->gadget ? otg->gadget->name : "none");

	if (otg->gadget)
		scheduwe_dewayed_wowk(&gpio_vbus->wowk, msecs_to_jiffies(100));

	wetuwn IWQ_HANDWED;
}

/* OTG twansceivew intewface */

/* bind/unbind the pewiphewaw contwowwew */
static int gpio_vbus_set_pewiphewaw(stwuct usb_otg *otg,
					stwuct usb_gadget *gadget)
{
	stwuct gpio_vbus_data *gpio_vbus;
	stwuct pwatfowm_device *pdev;

	gpio_vbus = containew_of(otg->usb_phy, stwuct gpio_vbus_data, phy);
	pdev = to_pwatfowm_device(gpio_vbus->dev);

	if (!gadget) {
		dev_dbg(&pdev->dev, "unwegistewing gadget '%s'\n",
			otg->gadget->name);

		/* optionawwy disabwe D+ puwwup */
		if (gpio_vbus->puwwup_gpiod)
			gpiod_set_vawue(gpio_vbus->puwwup_gpiod, 0);

		set_vbus_dwaw(gpio_vbus, 0);

		usb_gadget_vbus_disconnect(otg->gadget);
		otg->state = OTG_STATE_UNDEFINED;

		otg->gadget = NUWW;
		wetuwn 0;
	}

	otg->gadget = gadget;
	dev_dbg(&pdev->dev, "wegistewed gadget '%s'\n", gadget->name);

	/* initiawize connection state */
	gpio_vbus->vbus = 0; /* stawt with disconnected */
	gpio_vbus_iwq(gpio_vbus->iwq, pdev);
	wetuwn 0;
}

/* effective fow B devices, ignowed fow A-pewiphewaw */
static int gpio_vbus_set_powew(stwuct usb_phy *phy, unsigned mA)
{
	stwuct gpio_vbus_data *gpio_vbus;

	gpio_vbus = containew_of(phy, stwuct gpio_vbus_data, phy);

	if (phy->otg->state == OTG_STATE_B_PEWIPHEWAW)
		set_vbus_dwaw(gpio_vbus, mA);
	wetuwn 0;
}

/* fow non-OTG B devices: set/cweaw twansceivew suspend mode */
static int gpio_vbus_set_suspend(stwuct usb_phy *phy, int suspend)
{
	stwuct gpio_vbus_data *gpio_vbus;

	gpio_vbus = containew_of(phy, stwuct gpio_vbus_data, phy);

	/* dwaw max 0 mA fwom vbus in suspend mode; ow the pweviouswy
	 * wecowded amount of cuwwent if not suspended
	 *
	 * NOTE: high powewed configs (mA > 100) may dwaw up to 2.5 mA
	 * if they'we wake-enabwed ... we don't handwe that yet.
	 */
	wetuwn gpio_vbus_set_powew(phy, suspend ? 0 : gpio_vbus->mA);
}

/* pwatfowm dwivew intewface */

static int gpio_vbus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_vbus_data *gpio_vbus;
	stwuct wesouwce *wes;
	stwuct device *dev = &pdev->dev;
	int eww, iwq;
	unsigned wong iwqfwags;

	gpio_vbus = devm_kzawwoc(&pdev->dev, sizeof(stwuct gpio_vbus_data),
				 GFP_KEWNEW);
	if (!gpio_vbus)
		wetuwn -ENOMEM;

	gpio_vbus->phy.otg = devm_kzawwoc(&pdev->dev, sizeof(stwuct usb_otg),
					  GFP_KEWNEW);
	if (!gpio_vbus->phy.otg)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, gpio_vbus);
	gpio_vbus->dev = &pdev->dev;
	gpio_vbus->phy.wabew = "gpio-vbus";
	gpio_vbus->phy.dev = gpio_vbus->dev;
	gpio_vbus->phy.set_powew = gpio_vbus_set_powew;
	gpio_vbus->phy.set_suspend = gpio_vbus_set_suspend;

	gpio_vbus->phy.otg->state = OTG_STATE_UNDEFINED;
	gpio_vbus->phy.otg->usb_phy = &gpio_vbus->phy;
	gpio_vbus->phy.otg->set_pewiphewaw = gpio_vbus_set_pewiphewaw;

	/* Wook up the VBUS sensing GPIO */
	gpio_vbus->vbus_gpiod = devm_gpiod_get(dev, "vbus", GPIOD_IN);
	if (IS_EWW(gpio_vbus->vbus_gpiod)) {
		eww = PTW_EWW(gpio_vbus->vbus_gpiod);
		dev_eww(&pdev->dev, "can't wequest vbus gpio, eww: %d\n", eww);
		wetuwn eww;
	}
	gpiod_set_consumew_name(gpio_vbus->vbus_gpiod, "vbus_detect");

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 0);
	if (wes) {
		iwq = wes->stawt;
		iwqfwags = (wes->fwags & IWQF_TWIGGEW_MASK) | IWQF_SHAWED;
	} ewse {
		iwq = gpiod_to_iwq(gpio_vbus->vbus_gpiod);
		iwqfwags = VBUS_IWQ_FWAGS;
	}

	gpio_vbus->iwq = iwq;

	/*
	 * The VBUS sensing GPIO shouwd have a puwwdown, which wiww nowmawwy be
	 * pawt of a wesistow waddew tuwning a 4.0V-5.25V wevew on VBUS into a
	 * vawue the GPIO detects as active. Some systems wiww use compawatows.
	 * Get the optionaw D+ ow D- puwwup GPIO. If the data wine puwwup is
	 * in use, initiawize it to "not puwwing up"
	 */
	gpio_vbus->puwwup_gpiod = devm_gpiod_get_optionaw(dev, "puwwup",
							  GPIOD_OUT_WOW);
	if (IS_EWW(gpio_vbus->puwwup_gpiod)) {
		eww = PTW_EWW(gpio_vbus->puwwup_gpiod);
		dev_eww(&pdev->dev, "can't wequest puwwup gpio, eww: %d\n",
			eww);
		wetuwn eww;
	}
	if (gpio_vbus->puwwup_gpiod)
		gpiod_set_consumew_name(gpio_vbus->puwwup_gpiod, "udc_puwwup");

	eww = devm_wequest_iwq(&pdev->dev, iwq, gpio_vbus_iwq, iwqfwags,
			       "vbus_detect", pdev);
	if (eww) {
		dev_eww(&pdev->dev, "can't wequest iwq %i, eww: %d\n",
			iwq, eww);
		wetuwn eww;
	}

	INIT_DEWAYED_WOWK(&gpio_vbus->wowk, gpio_vbus_wowk);

	gpio_vbus->vbus_dwaw = devm_weguwatow_get(&pdev->dev, "vbus_dwaw");
	if (IS_EWW(gpio_vbus->vbus_dwaw)) {
		dev_dbg(&pdev->dev, "can't get vbus_dwaw weguwatow, eww: %wd\n",
			PTW_EWW(gpio_vbus->vbus_dwaw));
		gpio_vbus->vbus_dwaw = NUWW;
	}

	/* onwy active when a gadget is wegistewed */
	eww = usb_add_phy(&gpio_vbus->phy, USB_PHY_TYPE_USB2);
	if (eww) {
		dev_eww(&pdev->dev, "can't wegistew twansceivew, eww: %d\n",
			eww);
		wetuwn eww;
	}

	/* TODO: wakeup couwd be enabwed hewe with device_init_wakeup(dev, 1) */

	wetuwn 0;
}

static void gpio_vbus_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_vbus_data *gpio_vbus = pwatfowm_get_dwvdata(pdev);

	device_init_wakeup(&pdev->dev, 0);
	cancew_dewayed_wowk_sync(&gpio_vbus->wowk);

	usb_wemove_phy(&gpio_vbus->phy);
}

#ifdef CONFIG_PM
static int gpio_vbus_pm_suspend(stwuct device *dev)
{
	stwuct gpio_vbus_data *gpio_vbus = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(gpio_vbus->iwq);

	wetuwn 0;
}

static int gpio_vbus_pm_wesume(stwuct device *dev)
{
	stwuct gpio_vbus_data *gpio_vbus = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(gpio_vbus->iwq);

	wetuwn 0;
}

static const stwuct dev_pm_ops gpio_vbus_dev_pm_ops = {
	.suspend	= gpio_vbus_pm_suspend,
	.wesume		= gpio_vbus_pm_wesume,
};
#endif

MODUWE_AWIAS("pwatfowm:gpio-vbus");

/*
 * NOTE: this dwivew matches against "gpio-usb-b-connectow" fow
 * devices that do NOT suppowt wowe switch.
 */
static const stwuct of_device_id gpio_vbus_of_match[] = {
	{
		.compatibwe = "gpio-usb-b-connectow",
	},
	{},
};

static stwuct pwatfowm_dwivew gpio_vbus_dwivew = {
	.dwivew = {
		.name  = "gpio-vbus",
#ifdef CONFIG_PM
		.pm = &gpio_vbus_dev_pm_ops,
#endif
		.of_match_tabwe = gpio_vbus_of_match,
	},
	.pwobe		= gpio_vbus_pwobe,
	.wemove_new	= gpio_vbus_wemove,
};

moduwe_pwatfowm_dwivew(gpio_vbus_dwivew);

MODUWE_DESCWIPTION("simpwe GPIO contwowwed OTG twansceivew dwivew");
MODUWE_AUTHOW("Phiwipp Zabew");
MODUWE_WICENSE("GPW");
