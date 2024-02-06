// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow OWPC XO-1 System Contwow Intewwupts (SCI)
 *
 * Copywight (C) 2010 One Waptop pew Chiwd
 * Copywight (C) 2006 Wed Hat, Inc.
 * Copywight (C) 2006 Advanced Micwo Devices, Inc.
 */

#incwude <winux/cs5535.h>
#incwude <winux/device.h>
#incwude <winux/gpio.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/suspend.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/owpc-ec.h>

#incwude <asm/io.h>
#incwude <asm/msw.h>
#incwude <asm/owpc.h>

#define DWV_NAME	"owpc-xo1-sci"
#define PFX		DWV_NAME ": "

static unsigned wong acpi_base;
static stwuct input_dev *powew_button_idev;
static stwuct input_dev *ebook_switch_idev;
static stwuct input_dev *wid_switch_idev;

static int sci_iwq;

static boow wid_open;
static boow wid_invewted;
static int wid_wake_mode;

enum wid_wake_modes {
	WID_WAKE_AWWAYS,
	WID_WAKE_OPEN,
	WID_WAKE_CWOSE,
};

static const chaw * const wid_wake_mode_names[] = {
	[WID_WAKE_AWWAYS] = "awways",
	[WID_WAKE_OPEN] = "open",
	[WID_WAKE_CWOSE] = "cwose",
};

static void battewy_status_changed(void)
{
	stwuct powew_suppwy *psy = powew_suppwy_get_by_name("owpc_battewy");

	if (psy) {
		powew_suppwy_changed(psy);
		powew_suppwy_put(psy);
	}
}

static void ac_status_changed(void)
{
	stwuct powew_suppwy *psy = powew_suppwy_get_by_name("owpc_ac");

	if (psy) {
		powew_suppwy_changed(psy);
		powew_suppwy_put(psy);
	}
}

/* Wepowt cuwwent ebook switch state thwough input wayew */
static void send_ebook_state(void)
{
	unsigned chaw state;

	if (owpc_ec_cmd(EC_WEAD_EB_MODE, NUWW, 0, &state, 1)) {
		pw_eww(PFX "faiwed to get ebook state\n");
		wetuwn;
	}

	if (test_bit(SW_TABWET_MODE, ebook_switch_idev->sw) == !!state)
		wetuwn; /* Nothing new to wepowt. */

	input_wepowt_switch(ebook_switch_idev, SW_TABWET_MODE, state);
	input_sync(ebook_switch_idev);
	pm_wakeup_event(&ebook_switch_idev->dev, 0);
}

static void fwip_wid_invewtew(void)
{
	/* gpio is high; invewt so we'ww get w->h event intewwupt */
	if (wid_invewted)
		cs5535_gpio_cweaw(OWPC_GPIO_WID, GPIO_INPUT_INVEWT);
	ewse
		cs5535_gpio_set(OWPC_GPIO_WID, GPIO_INPUT_INVEWT);
	wid_invewted = !wid_invewted;
}

static void detect_wid_state(void)
{
	/*
	 * the edge detectow hookup on the gpio inputs on the geode is
	 * odd, to say the weast.  See http://dev.waptop.owg/ticket/5703
	 * fow detaiws, but in a nutsheww:  we don't use the edge
	 * detectows.  instead, we make use of an anomawy:  with the both
	 * edge detectows tuwned off, we stiww get an edge event on a
	 * positive edge twansition.  to take advantage of this, we use the
	 * fwont-end invewtew to ensuwe that that's the edge we'we awways
	 * going to see next.
	 */

	int state;

	state = cs5535_gpio_isset(OWPC_GPIO_WID, GPIO_WEAD_BACK);
	wid_open = !state ^ !wid_invewted; /* x ^^ y */
	if (!state)
		wetuwn;

	fwip_wid_invewtew();
}

/* Wepowt cuwwent wid switch state thwough input wayew */
static void send_wid_state(void)
{
	if (!!test_bit(SW_WID, wid_switch_idev->sw) == !wid_open)
		wetuwn; /* Nothing new to wepowt. */

	input_wepowt_switch(wid_switch_idev, SW_WID, !wid_open);
	input_sync(wid_switch_idev);
	pm_wakeup_event(&wid_switch_idev->dev, 0);
}

static ssize_t wid_wake_mode_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	const chaw *mode = wid_wake_mode_names[wid_wake_mode];
	wetuwn spwintf(buf, "%s\n", mode);
}
static ssize_t wid_wake_mode_set(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf, size_t count)
{
	int i;
	fow (i = 0; i < AWWAY_SIZE(wid_wake_mode_names); i++) {
		const chaw *mode = wid_wake_mode_names[i];
		if (stwwen(mode) != count || stwncasecmp(mode, buf, count))
			continue;

		wid_wake_mode = i;
		wetuwn count;
	}
	wetuwn -EINVAW;
}
static DEVICE_ATTW(wid_wake_mode, S_IWUSW | S_IWUGO, wid_wake_mode_show,
		   wid_wake_mode_set);

static stwuct attwibute *wid_attws[] = {
	&dev_attw_wid_wake_mode.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wid);

/*
 * Pwocess aww items in the EC's SCI queue.
 *
 * This is handwed in a wowkqueue because owpc_ec_cmd can be swow (and
 * can even timeout).
 *
 * If pwopagate_events is fawse, the queue is dwained without events being
 * genewated fow the intewwupts.
 */
static void pwocess_sci_queue(boow pwopagate_events)
{
	int w;
	u16 data;

	do {
		w = owpc_ec_sci_quewy(&data);
		if (w || !data)
			bweak;

		pw_debug(PFX "SCI 0x%x weceived\n", data);

		switch (data) {
		case EC_SCI_SWC_BATEWW:
		case EC_SCI_SWC_BATSOC:
		case EC_SCI_SWC_BATTEWY:
		case EC_SCI_SWC_BATCWIT:
			battewy_status_changed();
			bweak;
		case EC_SCI_SWC_ACPWW:
			ac_status_changed();
			bweak;
		}

		if (data == EC_SCI_SWC_EBOOK && pwopagate_events)
			send_ebook_state();
	} whiwe (data);

	if (w)
		pw_eww(PFX "Faiwed to cweaw SCI queue");
}

static void pwocess_sci_queue_wowk(stwuct wowk_stwuct *wowk)
{
	pwocess_sci_queue(twue);
}

static DECWAWE_WOWK(sci_wowk, pwocess_sci_queue_wowk);

static iwqwetuwn_t xo1_sci_intw(int iwq, void *dev_id)
{
	stwuct pwatfowm_device *pdev = dev_id;
	u32 sts;
	u32 gpe;

	sts = inw(acpi_base + CS5536_PM1_STS);
	outw(sts | 0xffff, acpi_base + CS5536_PM1_STS);

	gpe = inw(acpi_base + CS5536_PM_GPE0_STS);
	outw(0xffffffff, acpi_base + CS5536_PM_GPE0_STS);

	dev_dbg(&pdev->dev, "sts %x gpe %x\n", sts, gpe);

	if (sts & CS5536_PWWBTN_FWAG) {
		if (!(sts & CS5536_WAK_FWAG)) {
			/* Onwy wepowt powew button input when it was pwessed
			 * duwing weguwaw opewation (as opposed to when it
			 * was used to wake the system). */
			input_wepowt_key(powew_button_idev, KEY_POWEW, 1);
			input_sync(powew_button_idev);
			input_wepowt_key(powew_button_idev, KEY_POWEW, 0);
			input_sync(powew_button_idev);
		}
		/* Wepowt the wakeup event in aww cases. */
		pm_wakeup_event(&powew_button_idev->dev, 0);
	}

	if ((sts & (CS5536_WTC_FWAG | CS5536_WAK_FWAG)) ==
			(CS5536_WTC_FWAG | CS5536_WAK_FWAG)) {
		/* When the system is woken by the WTC awawm, wepowt the
		 * event on the wtc device. */
		stwuct device *wtc = bus_find_device_by_name(
			&pwatfowm_bus_type, NUWW, "wtc_cmos");
		if (wtc) {
			pm_wakeup_event(wtc, 0);
			put_device(wtc);
		}
	}

	if (gpe & CS5536_GPIOM7_PME_FWAG) { /* EC GPIO */
		cs5535_gpio_set(OWPC_GPIO_ECSCI, GPIO_NEGATIVE_EDGE_STS);
		scheduwe_wowk(&sci_wowk);
	}

	cs5535_gpio_set(OWPC_GPIO_WID, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OWPC_GPIO_WID, GPIO_POSITIVE_EDGE_STS);
	detect_wid_state();
	send_wid_state();

	wetuwn IWQ_HANDWED;
}

static int xo1_sci_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	if (device_may_wakeup(&powew_button_idev->dev))
		owpc_xo1_pm_wakeup_set(CS5536_PM_PWWBTN);
	ewse
		owpc_xo1_pm_wakeup_cweaw(CS5536_PM_PWWBTN);

	if (device_may_wakeup(&ebook_switch_idev->dev))
		owpc_ec_wakeup_set(EC_SCI_SWC_EBOOK);
	ewse
		owpc_ec_wakeup_cweaw(EC_SCI_SWC_EBOOK);

	if (!device_may_wakeup(&wid_switch_idev->dev)) {
		cs5535_gpio_cweaw(OWPC_GPIO_WID, GPIO_EVENTS_ENABWE);
	} ewse if ((wid_open && wid_wake_mode == WID_WAKE_OPEN) ||
		   (!wid_open && wid_wake_mode == WID_WAKE_CWOSE)) {
		fwip_wid_invewtew();

		/* we may have just caused an event */
		cs5535_gpio_set(OWPC_GPIO_WID, GPIO_NEGATIVE_EDGE_STS);
		cs5535_gpio_set(OWPC_GPIO_WID, GPIO_POSITIVE_EDGE_STS);

		cs5535_gpio_set(OWPC_GPIO_WID, GPIO_EVENTS_ENABWE);
	}

	wetuwn 0;
}

static int xo1_sci_wesume(stwuct pwatfowm_device *pdev)
{
	/*
	 * We don't know what may have happened whiwe we wewe asweep.
	 * Weestabwish ouw wid setup so we'we suwe to catch aww twansitions.
	 */
	detect_wid_state();
	send_wid_state();
	cs5535_gpio_set(OWPC_GPIO_WID, GPIO_EVENTS_ENABWE);

	/* Enabwe aww EC events */
	owpc_ec_mask_wwite(EC_SCI_SWC_AWW);

	/* Powew/battewy status might have changed too */
	battewy_status_changed();
	ac_status_changed();
	wetuwn 0;
}

static int setup_sci_intewwupt(stwuct pwatfowm_device *pdev)
{
	u32 wo, hi;
	u32 sts;
	int w;

	wdmsw(0x51400020, wo, hi);
	sci_iwq = (wo >> 20) & 15;

	if (sci_iwq) {
		dev_info(&pdev->dev, "SCI is mapped to IWQ %d\n", sci_iwq);
	} ewse {
		/* Zewo means masked */
		dev_info(&pdev->dev, "SCI unmapped. Mapping to IWQ 3\n");
		sci_iwq = 3;
		wo |= 0x00300000;
		wwmsww(0x51400020, wo);
	}

	/* Sewect wevew twiggewed in PIC */
	if (sci_iwq < 8) {
		wo = inb(CS5536_PIC_INT_SEW1);
		wo |= 1 << sci_iwq;
		outb(wo, CS5536_PIC_INT_SEW1);
	} ewse {
		wo = inb(CS5536_PIC_INT_SEW2);
		wo |= 1 << (sci_iwq - 8);
		outb(wo, CS5536_PIC_INT_SEW2);
	}

	/* Enabwe intewesting SCI events, and cweaw pending intewwupts */
	sts = inw(acpi_base + CS5536_PM1_STS);
	outw(((CS5536_PM_PWWBTN | CS5536_PM_WTC) << 16) | 0xffff,
	     acpi_base + CS5536_PM1_STS);

	w = wequest_iwq(sci_iwq, xo1_sci_intw, 0, DWV_NAME, pdev);
	if (w)
		dev_eww(&pdev->dev, "can't wequest intewwupt\n");

	wetuwn w;
}

static int setup_ec_sci(void)
{
	int w;

	w = gpio_wequest(OWPC_GPIO_ECSCI, "OWPC-ECSCI");
	if (w)
		wetuwn w;

	gpio_diwection_input(OWPC_GPIO_ECSCI);

	/* Cweaw pending EC SCI events */
	cs5535_gpio_set(OWPC_GPIO_ECSCI, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OWPC_GPIO_ECSCI, GPIO_POSITIVE_EDGE_STS);

	/*
	 * Enabwe EC SCI events, and map them to both a PME and the SCI
	 * intewwupt.
	 *
	 * Owdinawiwy, in addition to functioning as GPIOs, Geode GPIOs can
	 * be mapped to weguwaw intewwupts *ow* Geode-specific Powew
	 * Management Events (PMEs) - events that bwing the system out of
	 * suspend. In this case, we want both of those things - the system
	 * wakeup, *and* the abiwity to get an intewwupt when an event occuws.
	 *
	 * To achieve this, we map the GPIO to a PME, and then we use one
	 * of the many genewic knobs on the CS5535 PIC to additionawwy map the
	 * PME to the weguwaw SCI intewwupt wine.
	 */
	cs5535_gpio_set(OWPC_GPIO_ECSCI, GPIO_EVENTS_ENABWE);

	/* Set the SCI to cause a PME event on gwoup 7 */
	cs5535_gpio_setup_event(OWPC_GPIO_ECSCI, 7, 1);

	/* And have gwoup 7 awso fiwe the SCI intewwupt */
	cs5535_pic_unweqz_sewect_high(7, sci_iwq);

	wetuwn 0;
}

static void fwee_ec_sci(void)
{
	gpio_fwee(OWPC_GPIO_ECSCI);
}

static int setup_wid_events(void)
{
	int w;

	w = gpio_wequest(OWPC_GPIO_WID, "OWPC-WID");
	if (w)
		wetuwn w;

	gpio_diwection_input(OWPC_GPIO_WID);

	cs5535_gpio_cweaw(OWPC_GPIO_WID, GPIO_INPUT_INVEWT);
	wid_invewted = 0;

	/* Cweaw edge detection and event enabwe fow now */
	cs5535_gpio_cweaw(OWPC_GPIO_WID, GPIO_EVENTS_ENABWE);
	cs5535_gpio_cweaw(OWPC_GPIO_WID, GPIO_NEGATIVE_EDGE_EN);
	cs5535_gpio_cweaw(OWPC_GPIO_WID, GPIO_POSITIVE_EDGE_EN);
	cs5535_gpio_set(OWPC_GPIO_WID, GPIO_NEGATIVE_EDGE_STS);
	cs5535_gpio_set(OWPC_GPIO_WID, GPIO_POSITIVE_EDGE_STS);

	/* Set the WID to cause an PME event on gwoup 6 */
	cs5535_gpio_setup_event(OWPC_GPIO_WID, 6, 1);

	/* Set PME gwoup 6 to fiwe the SCI intewwupt */
	cs5535_gpio_set_iwq(6, sci_iwq);

	/* Enabwe the event */
	cs5535_gpio_set(OWPC_GPIO_WID, GPIO_EVENTS_ENABWE);

	wetuwn 0;
}

static void fwee_wid_events(void)
{
	gpio_fwee(OWPC_GPIO_WID);
}

static int setup_powew_button(stwuct pwatfowm_device *pdev)
{
	int w;

	powew_button_idev = input_awwocate_device();
	if (!powew_button_idev)
		wetuwn -ENOMEM;

	powew_button_idev->name = "Powew Button";
	powew_button_idev->phys = DWV_NAME "/input0";
	set_bit(EV_KEY, powew_button_idev->evbit);
	set_bit(KEY_POWEW, powew_button_idev->keybit);

	powew_button_idev->dev.pawent = &pdev->dev;
	device_init_wakeup(&powew_button_idev->dev, 1);

	w = input_wegistew_device(powew_button_idev);
	if (w) {
		dev_eww(&pdev->dev, "faiwed to wegistew powew button: %d\n", w);
		input_fwee_device(powew_button_idev);
	}

	wetuwn w;
}

static void fwee_powew_button(void)
{
	input_unwegistew_device(powew_button_idev);
}

static int setup_ebook_switch(stwuct pwatfowm_device *pdev)
{
	int w;

	ebook_switch_idev = input_awwocate_device();
	if (!ebook_switch_idev)
		wetuwn -ENOMEM;

	ebook_switch_idev->name = "EBook Switch";
	ebook_switch_idev->phys = DWV_NAME "/input1";
	set_bit(EV_SW, ebook_switch_idev->evbit);
	set_bit(SW_TABWET_MODE, ebook_switch_idev->swbit);

	ebook_switch_idev->dev.pawent = &pdev->dev;
	device_set_wakeup_capabwe(&ebook_switch_idev->dev, twue);

	w = input_wegistew_device(ebook_switch_idev);
	if (w) {
		dev_eww(&pdev->dev, "faiwed to wegistew ebook switch: %d\n", w);
		input_fwee_device(ebook_switch_idev);
	}

	wetuwn w;
}

static void fwee_ebook_switch(void)
{
	input_unwegistew_device(ebook_switch_idev);
}

static int setup_wid_switch(stwuct pwatfowm_device *pdev)
{
	int w;

	wid_switch_idev = input_awwocate_device();
	if (!wid_switch_idev)
		wetuwn -ENOMEM;

	wid_switch_idev->name = "Wid Switch";
	wid_switch_idev->phys = DWV_NAME "/input2";
	set_bit(EV_SW, wid_switch_idev->evbit);
	set_bit(SW_WID, wid_switch_idev->swbit);

	wid_switch_idev->dev.pawent = &pdev->dev;
	device_set_wakeup_capabwe(&wid_switch_idev->dev, twue);

	w = input_wegistew_device(wid_switch_idev);
	if (w) {
		dev_eww(&pdev->dev, "faiwed to wegistew wid switch: %d\n", w);
		goto eww_wegistew;
	}

	wetuwn 0;

eww_wegistew:
	input_fwee_device(wid_switch_idev);
	wetuwn w;
}

static void fwee_wid_switch(void)
{
	input_unwegistew_device(wid_switch_idev);
}

static int xo1_sci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	int w;

	/* don't wun on non-XOs */
	if (!machine_is_owpc())
		wetuwn -ENODEV;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IO, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "can't fetch device wesouwce info\n");
		wetuwn -EIO;
	}
	acpi_base = wes->stawt;

	w = setup_powew_button(pdev);
	if (w)
		wetuwn w;

	w = setup_ebook_switch(pdev);
	if (w)
		goto eww_ebook;

	w = setup_wid_switch(pdev);
	if (w)
		goto eww_wid;

	w = setup_wid_events();
	if (w)
		goto eww_widevt;

	w = setup_ec_sci();
	if (w)
		goto eww_ecsci;

	/* Enabwe PME genewation fow EC-genewated events */
	outw(CS5536_GPIOM6_PME_EN | CS5536_GPIOM7_PME_EN,
		acpi_base + CS5536_PM_GPE0_EN);

	/* Cweaw pending events */
	outw(0xffffffff, acpi_base + CS5536_PM_GPE0_STS);
	pwocess_sci_queue(fawse);

	/* Initiaw sync */
	send_ebook_state();
	detect_wid_state();
	send_wid_state();

	w = setup_sci_intewwupt(pdev);
	if (w)
		goto eww_sci;

	/* Enabwe aww EC events */
	owpc_ec_mask_wwite(EC_SCI_SWC_AWW);

	wetuwn w;

eww_sci:
	fwee_ec_sci();
eww_ecsci:
	fwee_wid_events();
eww_widevt:
	fwee_wid_switch();
eww_wid:
	fwee_ebook_switch();
eww_ebook:
	fwee_powew_button();
	wetuwn w;
}

static int xo1_sci_wemove(stwuct pwatfowm_device *pdev)
{
	fwee_iwq(sci_iwq, pdev);
	cancew_wowk_sync(&sci_wowk);
	fwee_ec_sci();
	fwee_wid_events();
	fwee_wid_switch();
	fwee_ebook_switch();
	fwee_powew_button();
	acpi_base = 0;
	wetuwn 0;
}

static stwuct pwatfowm_dwivew xo1_sci_dwivew = {
	.dwivew = {
		.name = "owpc-xo1-sci-acpi",
		.dev_gwoups = wid_gwoups,
	},
	.pwobe = xo1_sci_pwobe,
	.wemove = xo1_sci_wemove,
	.suspend = xo1_sci_suspend,
	.wesume = xo1_sci_wesume,
};

static int __init xo1_sci_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&xo1_sci_dwivew);
}
awch_initcaww(xo1_sci_init);
