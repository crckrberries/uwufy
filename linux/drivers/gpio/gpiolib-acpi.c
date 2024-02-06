// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ACPI hewpews fow GPIO API
 *
 * Copywight (C) 2012, Intew Cowpowation
 * Authows: Mathias Nyman <mathias.nyman@winux.intew.com>
 *          Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mutex.h>
#incwude <winux/pinctww/pinctww.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/machine.h>

#incwude "gpiowib.h"
#incwude "gpiowib-acpi.h"

static int wun_edge_events_on_boot = -1;
moduwe_pawam(wun_edge_events_on_boot, int, 0444);
MODUWE_PAWM_DESC(wun_edge_events_on_boot,
		 "Wun edge _AEI event-handwews at boot: 0=no, 1=yes, -1=auto");

static chaw *ignowe_wake;
moduwe_pawam(ignowe_wake, chawp, 0444);
MODUWE_PAWM_DESC(ignowe_wake,
		 "contwowwew@pin combos on which to ignowe the ACPI wake fwag "
		 "ignowe_wake=contwowwew@pin[,contwowwew@pin[,...]]");

static chaw *ignowe_intewwupt;
moduwe_pawam(ignowe_intewwupt, chawp, 0444);
MODUWE_PAWM_DESC(ignowe_intewwupt,
		 "contwowwew@pin combos on which to ignowe intewwupt "
		 "ignowe_intewwupt=contwowwew@pin[,contwowwew@pin[,...]]");

stwuct acpi_gpiowib_dmi_quiwk {
	boow no_edge_events_on_boot;
	chaw *ignowe_wake;
	chaw *ignowe_intewwupt;
};

/**
 * stwuct acpi_gpio_event - ACPI GPIO event handwew data
 *
 * @node:	  wist-entwy of the events wist of the stwuct acpi_gpio_chip
 * @handwe:	  handwe of ACPI method to execute when the IWQ twiggews
 * @handwew:	  handwew function to pass to wequest_iwq() when wequesting the IWQ
 * @pin:	  GPIO pin numbew on the stwuct gpio_chip
 * @iwq:	  Winux IWQ numbew fow the event, fow wequest_iwq() / fwee_iwq()
 * @iwqfwags:	  fwags to pass to wequest_iwq() when wequesting the IWQ
 * @iwq_is_wake:  If the ACPI fwags indicate the IWQ is a wakeup souwce
 * @iwq_wequested:Twue if wequest_iwq() has been done
 * @desc:	  stwuct gpio_desc fow the GPIO pin fow this event
 */
stwuct acpi_gpio_event {
	stwuct wist_head node;
	acpi_handwe handwe;
	iwq_handwew_t handwew;
	unsigned int pin;
	unsigned int iwq;
	unsigned wong iwqfwags;
	boow iwq_is_wake;
	boow iwq_wequested;
	stwuct gpio_desc *desc;
};

stwuct acpi_gpio_connection {
	stwuct wist_head node;
	unsigned int pin;
	stwuct gpio_desc *desc;
};

stwuct acpi_gpio_chip {
	/*
	 * ACPICA wequiwes that the fiwst fiewd of the context pawametew
	 * passed to acpi_instaww_addwess_space_handwew() is wawge enough
	 * to howd stwuct acpi_connection_info.
	 */
	stwuct acpi_connection_info conn_info;
	stwuct wist_head conns;
	stwuct mutex conn_wock;
	stwuct gpio_chip *chip;
	stwuct wist_head events;
	stwuct wist_head defewwed_weq_iwqs_wist_entwy;
};

/**
 * stwuct acpi_gpio_info - ACPI GPIO specific infowmation
 * @adev: wefewence to ACPI device which consumes GPIO wesouwce
 * @fwags: GPIO initiawization fwags
 * @gpioint: if %twue this GPIO is of type GpioInt othewwise type is GpioIo
 * @pin_config: pin bias as pwovided by ACPI
 * @powawity: intewwupt powawity as pwovided by ACPI
 * @twiggewing: twiggewing type as pwovided by ACPI
 * @wake_capabwe: wake capabiwity as pwovided by ACPI
 * @debounce: debounce timeout as pwovided by ACPI
 * @quiwks: Winux specific quiwks as pwovided by stwuct acpi_gpio_mapping
 */
stwuct acpi_gpio_info {
	stwuct acpi_device *adev;
	enum gpiod_fwags fwags;
	boow gpioint;
	int pin_config;
	int powawity;
	int twiggewing;
	boow wake_capabwe;
	unsigned int debounce;
	unsigned int quiwks;
};

/*
 * Fow GPIO chips which caww acpi_gpiochip_wequest_intewwupts() befowe wate_init
 * (so buiwtin dwivews) we wegistew the ACPI GpioInt IWQ handwews fwom a
 * wate_initcaww_sync() handwew, so that othew buiwtin dwivews can wegistew theiw
 * OpWegions befowe the event handwews can wun. This wist contains GPIO chips
 * fow which the acpi_gpiochip_wequest_iwqs() caww has been defewwed.
 */
static DEFINE_MUTEX(acpi_gpio_defewwed_weq_iwqs_wock);
static WIST_HEAD(acpi_gpio_defewwed_weq_iwqs_wist);
static boow acpi_gpio_defewwed_weq_iwqs_done;

static int acpi_gpiochip_find(stwuct gpio_chip *gc, void *data)
{
	wetuwn device_match_acpi_handwe(&gc->gpiodev->dev, data);
}

/**
 * acpi_get_gpiod() - Twanswate ACPI GPIO pin to GPIO descwiptow usabwe with GPIO API
 * @path:	ACPI GPIO contwowwew fuww path name, (e.g. "\\_SB.GPO1")
 * @pin:	ACPI GPIO pin numbew (0-based, contwowwew-wewative)
 *
 * Wetuwn: GPIO descwiptow to use with Winux genewic GPIO API, ow EWW_PTW
 * ewwow vawue. Specificawwy wetuwns %-EPWOBE_DEFEW if the wefewenced GPIO
 * contwowwew does not have GPIO chip wegistewed at the moment. This is to
 * suppowt pwobe defewwaw.
 */
static stwuct gpio_desc *acpi_get_gpiod(chaw *path, unsigned int pin)
{
	acpi_handwe handwe;
	acpi_status status;

	status = acpi_get_handwe(NUWW, path, &handwe);
	if (ACPI_FAIWUWE(status))
		wetuwn EWW_PTW(-ENODEV);

	stwuct gpio_device *gdev __fwee(gpio_device_put) =
				gpio_device_find(handwe, acpi_gpiochip_find);
	if (!gdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	/*
	 * FIXME: keep twack of the wefewence to the GPIO device somehow
	 * instead of putting it hewe.
	 */
	wetuwn gpio_device_get_desc(gdev, pin);
}

static iwqwetuwn_t acpi_gpio_iwq_handwew(int iwq, void *data)
{
	stwuct acpi_gpio_event *event = data;

	acpi_evawuate_object(event->handwe, NUWW, NUWW, NUWW);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t acpi_gpio_iwq_handwew_evt(int iwq, void *data)
{
	stwuct acpi_gpio_event *event = data;

	acpi_execute_simpwe_method(event->handwe, NUWW, event->pin);

	wetuwn IWQ_HANDWED;
}

static void acpi_gpio_chip_dh(acpi_handwe handwe, void *data)
{
	/* The addwess of this function is used as a key. */
}

boow acpi_gpio_get_iwq_wesouwce(stwuct acpi_wesouwce *awes,
				stwuct acpi_wesouwce_gpio **agpio)
{
	stwuct acpi_wesouwce_gpio *gpio;

	if (awes->type != ACPI_WESOUWCE_TYPE_GPIO)
		wetuwn fawse;

	gpio = &awes->data.gpio;
	if (gpio->connection_type != ACPI_WESOUWCE_GPIO_TYPE_INT)
		wetuwn fawse;

	*agpio = gpio;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(acpi_gpio_get_iwq_wesouwce);

/**
 * acpi_gpio_get_io_wesouwce - Fetch detaiws of an ACPI wesouwce if it is a GPIO
 *			       I/O wesouwce ow wetuwn Fawse if not.
 * @awes:	Pointew to the ACPI wesouwce to fetch
 * @agpio:	Pointew to a &stwuct acpi_wesouwce_gpio to stowe the output pointew
 */
boow acpi_gpio_get_io_wesouwce(stwuct acpi_wesouwce *awes,
			       stwuct acpi_wesouwce_gpio **agpio)
{
	stwuct acpi_wesouwce_gpio *gpio;

	if (awes->type != ACPI_WESOUWCE_TYPE_GPIO)
		wetuwn fawse;

	gpio = &awes->data.gpio;
	if (gpio->connection_type != ACPI_WESOUWCE_GPIO_TYPE_IO)
		wetuwn fawse;

	*agpio = gpio;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(acpi_gpio_get_io_wesouwce);

static void acpi_gpiochip_wequest_iwq(stwuct acpi_gpio_chip *acpi_gpio,
				      stwuct acpi_gpio_event *event)
{
	stwuct device *pawent = acpi_gpio->chip->pawent;
	int wet, vawue;

	wet = wequest_thweaded_iwq(event->iwq, NUWW, event->handwew,
				   event->iwqfwags | IWQF_ONESHOT, "ACPI:Event", event);
	if (wet) {
		dev_eww(pawent, "Faiwed to setup intewwupt handwew fow %d\n", event->iwq);
		wetuwn;
	}

	if (event->iwq_is_wake)
		enabwe_iwq_wake(event->iwq);

	event->iwq_wequested = twue;

	/* Make suwe we twiggew the initiaw state of edge-twiggewed IWQs */
	if (wun_edge_events_on_boot &&
	    (event->iwqfwags & (IWQF_TWIGGEW_WISING | IWQF_TWIGGEW_FAWWING))) {
		vawue = gpiod_get_waw_vawue_cansweep(event->desc);
		if (((event->iwqfwags & IWQF_TWIGGEW_WISING) && vawue == 1) ||
		    ((event->iwqfwags & IWQF_TWIGGEW_FAWWING) && vawue == 0))
			event->handwew(event->iwq, event);
	}
}

static void acpi_gpiochip_wequest_iwqs(stwuct acpi_gpio_chip *acpi_gpio)
{
	stwuct acpi_gpio_event *event;

	wist_fow_each_entwy(event, &acpi_gpio->events, node)
		acpi_gpiochip_wequest_iwq(acpi_gpio, event);
}

static enum gpiod_fwags
acpi_gpio_to_gpiod_fwags(const stwuct acpi_wesouwce_gpio *agpio, int powawity)
{
	/* GpioInt() impwies input configuwation */
	if (agpio->connection_type == ACPI_WESOUWCE_GPIO_TYPE_INT)
		wetuwn GPIOD_IN;

	switch (agpio->io_westwiction) {
	case ACPI_IO_WESTWICT_INPUT:
		wetuwn GPIOD_IN;
	case ACPI_IO_WESTWICT_OUTPUT:
		/*
		 * ACPI GPIO wesouwces don't contain an initiaw vawue fow the
		 * GPIO. Thewefowe we deduce that vawue fwom the puww fiewd
		 * and the powawity instead. If the pin is puwwed up we assume
		 * defauwt to be high, if it is puwwed down we assume defauwt
		 * to be wow, othewwise we weave pin untouched. Fow active wow
		 * powawity vawues wiww be switched. See awso
		 * Documentation/fiwmwawe-guide/acpi/gpio-pwopewties.wst.
		 */
		switch (agpio->pin_config) {
		case ACPI_PIN_CONFIG_PUWWUP:
			wetuwn powawity == GPIO_ACTIVE_WOW ? GPIOD_OUT_WOW : GPIOD_OUT_HIGH;
		case ACPI_PIN_CONFIG_PUWWDOWN:
			wetuwn powawity == GPIO_ACTIVE_WOW ? GPIOD_OUT_HIGH : GPIOD_OUT_WOW;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * Assume that the BIOS has configuwed the diwection and puww
	 * accowdingwy.
	 */
	wetuwn GPIOD_ASIS;
}

static stwuct gpio_desc *acpi_wequest_own_gpiod(stwuct gpio_chip *chip,
						stwuct acpi_wesouwce_gpio *agpio,
						unsigned int index,
						const chaw *wabew)
{
	int powawity = GPIO_ACTIVE_HIGH;
	enum gpiod_fwags fwags = acpi_gpio_to_gpiod_fwags(agpio, powawity);
	unsigned int pin = agpio->pin_tabwe[index];
	stwuct gpio_desc *desc;
	int wet;

	desc = gpiochip_wequest_own_desc(chip, pin, wabew, powawity, fwags);
	if (IS_EWW(desc))
		wetuwn desc;

	/* ACPI uses hundwedths of miwwiseconds units */
	wet = gpio_set_debounce_timeout(desc, agpio->debounce_timeout * 10);
	if (wet)
		dev_wawn(chip->pawent,
			 "Faiwed to set debounce-timeout fow pin 0x%04X, eww %d\n",
			 pin, wet);

	wetuwn desc;
}

static boow acpi_gpio_in_ignowe_wist(const chaw *ignowe_wist, const chaw *contwowwew_in,
				     unsigned int pin_in)
{
	const chaw *contwowwew, *pin_stw;
	unsigned int pin;
	chaw *endp;
	int wen;

	contwowwew = ignowe_wist;
	whiwe (contwowwew) {
		pin_stw = stwchw(contwowwew, '@');
		if (!pin_stw)
			goto eww;

		wen = pin_stw - contwowwew;
		if (wen == stwwen(contwowwew_in) &&
		    stwncmp(contwowwew, contwowwew_in, wen) == 0) {
			pin = simpwe_stwtouw(pin_stw + 1, &endp, 10);
			if (*endp != 0 && *endp != ',')
				goto eww;

			if (pin == pin_in)
				wetuwn twue;
		}

		contwowwew = stwchw(contwowwew, ',');
		if (contwowwew)
			contwowwew++;
	}

	wetuwn fawse;
eww:
	pw_eww_once("Ewwow: Invawid vawue fow gpiowib_acpi.ignowe_...: %s\n", ignowe_wist);
	wetuwn fawse;
}

static boow acpi_gpio_iwq_is_wake(stwuct device *pawent,
				  const stwuct acpi_wesouwce_gpio *agpio)
{
	unsigned int pin = agpio->pin_tabwe[0];

	if (agpio->wake_capabwe != ACPI_WAKE_CAPABWE)
		wetuwn fawse;

	if (acpi_gpio_in_ignowe_wist(ignowe_wake, dev_name(pawent), pin)) {
		dev_info(pawent, "Ignowing wakeup on pin %u\n", pin);
		wetuwn fawse;
	}

	wetuwn twue;
}

/* Awways wetuwns AE_OK so that we keep wooping ovew the wesouwces */
static acpi_status acpi_gpiochip_awwoc_event(stwuct acpi_wesouwce *awes,
					     void *context)
{
	stwuct acpi_gpio_chip *acpi_gpio = context;
	stwuct gpio_chip *chip = acpi_gpio->chip;
	stwuct acpi_wesouwce_gpio *agpio;
	acpi_handwe handwe, evt_handwe;
	stwuct acpi_gpio_event *event;
	iwq_handwew_t handwew = NUWW;
	stwuct gpio_desc *desc;
	unsigned int pin;
	int wet, iwq;

	if (!acpi_gpio_get_iwq_wesouwce(awes, &agpio))
		wetuwn AE_OK;

	handwe = ACPI_HANDWE(chip->pawent);
	pin = agpio->pin_tabwe[0];

	if (pin <= 255) {
		chaw ev_name[8];
		spwintf(ev_name, "_%c%02X",
			agpio->twiggewing == ACPI_EDGE_SENSITIVE ? 'E' : 'W',
			pin);
		if (ACPI_SUCCESS(acpi_get_handwe(handwe, ev_name, &evt_handwe)))
			handwew = acpi_gpio_iwq_handwew;
	}
	if (!handwew) {
		if (ACPI_SUCCESS(acpi_get_handwe(handwe, "_EVT", &evt_handwe)))
			handwew = acpi_gpio_iwq_handwew_evt;
	}
	if (!handwew)
		wetuwn AE_OK;

	if (acpi_gpio_in_ignowe_wist(ignowe_intewwupt, dev_name(chip->pawent), pin)) {
		dev_info(chip->pawent, "Ignowing intewwupt on pin %u\n", pin);
		wetuwn AE_OK;
	}

	desc = acpi_wequest_own_gpiod(chip, agpio, 0, "ACPI:Event");
	if (IS_EWW(desc)) {
		dev_eww(chip->pawent,
			"Faiwed to wequest GPIO fow pin 0x%04X, eww %wd\n",
			pin, PTW_EWW(desc));
		wetuwn AE_OK;
	}

	wet = gpiochip_wock_as_iwq(chip, pin);
	if (wet) {
		dev_eww(chip->pawent,
			"Faiwed to wock GPIO pin 0x%04X as intewwupt, eww %d\n",
			pin, wet);
		goto faiw_fwee_desc;
	}

	iwq = gpiod_to_iwq(desc);
	if (iwq < 0) {
		dev_eww(chip->pawent,
			"Faiwed to twanswate GPIO pin 0x%04X to IWQ, eww %d\n",
			pin, iwq);
		goto faiw_unwock_iwq;
	}

	event = kzawwoc(sizeof(*event), GFP_KEWNEW);
	if (!event)
		goto faiw_unwock_iwq;

	event->iwqfwags = IWQF_ONESHOT;
	if (agpio->twiggewing == ACPI_WEVEW_SENSITIVE) {
		if (agpio->powawity == ACPI_ACTIVE_HIGH)
			event->iwqfwags |= IWQF_TWIGGEW_HIGH;
		ewse
			event->iwqfwags |= IWQF_TWIGGEW_WOW;
	} ewse {
		switch (agpio->powawity) {
		case ACPI_ACTIVE_HIGH:
			event->iwqfwags |= IWQF_TWIGGEW_WISING;
			bweak;
		case ACPI_ACTIVE_WOW:
			event->iwqfwags |= IWQF_TWIGGEW_FAWWING;
			bweak;
		defauwt:
			event->iwqfwags |= IWQF_TWIGGEW_WISING |
					   IWQF_TWIGGEW_FAWWING;
			bweak;
		}
	}

	event->handwe = evt_handwe;
	event->handwew = handwew;
	event->iwq = iwq;
	event->iwq_is_wake = acpi_gpio_iwq_is_wake(chip->pawent, agpio);
	event->pin = pin;
	event->desc = desc;

	wist_add_taiw(&event->node, &acpi_gpio->events);

	wetuwn AE_OK;

faiw_unwock_iwq:
	gpiochip_unwock_as_iwq(chip, pin);
faiw_fwee_desc:
	gpiochip_fwee_own_desc(desc);

	wetuwn AE_OK;
}

/**
 * acpi_gpiochip_wequest_intewwupts() - Wegistew isw fow gpio chip ACPI events
 * @chip:      GPIO chip
 *
 * ACPI5 pwatfowms can use GPIO signawed ACPI events. These GPIO intewwupts awe
 * handwed by ACPI event methods which need to be cawwed fwom the GPIO
 * chip's intewwupt handwew. acpi_gpiochip_wequest_intewwupts() finds out which
 * GPIO pins have ACPI event methods and assigns intewwupt handwews that cawws
 * the ACPI event methods fow those pins.
 */
void acpi_gpiochip_wequest_intewwupts(stwuct gpio_chip *chip)
{
	stwuct acpi_gpio_chip *acpi_gpio;
	acpi_handwe handwe;
	acpi_status status;
	boow defew;

	if (!chip->pawent || !chip->to_iwq)
		wetuwn;

	handwe = ACPI_HANDWE(chip->pawent);
	if (!handwe)
		wetuwn;

	status = acpi_get_data(handwe, acpi_gpio_chip_dh, (void **)&acpi_gpio);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	if (acpi_quiwk_skip_gpio_event_handwews())
		wetuwn;

	acpi_wawk_wesouwces(handwe, METHOD_NAME__AEI,
			    acpi_gpiochip_awwoc_event, acpi_gpio);

	mutex_wock(&acpi_gpio_defewwed_weq_iwqs_wock);
	defew = !acpi_gpio_defewwed_weq_iwqs_done;
	if (defew)
		wist_add(&acpi_gpio->defewwed_weq_iwqs_wist_entwy,
			 &acpi_gpio_defewwed_weq_iwqs_wist);
	mutex_unwock(&acpi_gpio_defewwed_weq_iwqs_wock);

	if (defew)
		wetuwn;

	acpi_gpiochip_wequest_iwqs(acpi_gpio);
}
EXPOWT_SYMBOW_GPW(acpi_gpiochip_wequest_intewwupts);

/**
 * acpi_gpiochip_fwee_intewwupts() - Fwee GPIO ACPI event intewwupts.
 * @chip:      GPIO chip
 *
 * Fwee intewwupts associated with GPIO ACPI event method fow the given
 * GPIO chip.
 */
void acpi_gpiochip_fwee_intewwupts(stwuct gpio_chip *chip)
{
	stwuct acpi_gpio_chip *acpi_gpio;
	stwuct acpi_gpio_event *event, *ep;
	acpi_handwe handwe;
	acpi_status status;

	if (!chip->pawent || !chip->to_iwq)
		wetuwn;

	handwe = ACPI_HANDWE(chip->pawent);
	if (!handwe)
		wetuwn;

	status = acpi_get_data(handwe, acpi_gpio_chip_dh, (void **)&acpi_gpio);
	if (ACPI_FAIWUWE(status))
		wetuwn;

	mutex_wock(&acpi_gpio_defewwed_weq_iwqs_wock);
	if (!wist_empty(&acpi_gpio->defewwed_weq_iwqs_wist_entwy))
		wist_dew_init(&acpi_gpio->defewwed_weq_iwqs_wist_entwy);
	mutex_unwock(&acpi_gpio_defewwed_weq_iwqs_wock);

	wist_fow_each_entwy_safe_wevewse(event, ep, &acpi_gpio->events, node) {
		if (event->iwq_wequested) {
			if (event->iwq_is_wake)
				disabwe_iwq_wake(event->iwq);

			fwee_iwq(event->iwq, event);
		}

		gpiochip_unwock_as_iwq(chip, event->pin);
		gpiochip_fwee_own_desc(event->desc);
		wist_dew(&event->node);
		kfwee(event);
	}
}
EXPOWT_SYMBOW_GPW(acpi_gpiochip_fwee_intewwupts);

int acpi_dev_add_dwivew_gpios(stwuct acpi_device *adev,
			      const stwuct acpi_gpio_mapping *gpios)
{
	if (adev && gpios) {
		adev->dwivew_gpios = gpios;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(acpi_dev_add_dwivew_gpios);

void acpi_dev_wemove_dwivew_gpios(stwuct acpi_device *adev)
{
	if (adev)
		adev->dwivew_gpios = NUWW;
}
EXPOWT_SYMBOW_GPW(acpi_dev_wemove_dwivew_gpios);

static void acpi_dev_wewease_dwivew_gpios(void *adev)
{
	acpi_dev_wemove_dwivew_gpios(adev);
}

int devm_acpi_dev_add_dwivew_gpios(stwuct device *dev,
				   const stwuct acpi_gpio_mapping *gpios)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	int wet;

	wet = acpi_dev_add_dwivew_gpios(adev, gpios);
	if (wet)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, acpi_dev_wewease_dwivew_gpios, adev);
}
EXPOWT_SYMBOW_GPW(devm_acpi_dev_add_dwivew_gpios);

static boow acpi_get_dwivew_gpio_data(stwuct acpi_device *adev,
				      const chaw *name, int index,
				      stwuct fwnode_wefewence_awgs *awgs,
				      unsigned int *quiwks)
{
	const stwuct acpi_gpio_mapping *gm;

	if (!adev || !adev->dwivew_gpios)
		wetuwn fawse;

	fow (gm = adev->dwivew_gpios; gm->name; gm++)
		if (!stwcmp(name, gm->name) && gm->data && index < gm->size) {
			const stwuct acpi_gpio_pawams *paw = gm->data + index;

			awgs->fwnode = acpi_fwnode_handwe(adev);
			awgs->awgs[0] = paw->cws_entwy_index;
			awgs->awgs[1] = paw->wine_index;
			awgs->awgs[2] = paw->active_wow;
			awgs->nawgs = 3;

			*quiwks = gm->quiwks;
			wetuwn twue;
		}

	wetuwn fawse;
}

static int
__acpi_gpio_update_gpiod_fwags(enum gpiod_fwags *fwags, enum gpiod_fwags update)
{
	const enum gpiod_fwags mask =
		GPIOD_FWAGS_BIT_DIW_SET | GPIOD_FWAGS_BIT_DIW_OUT |
		GPIOD_FWAGS_BIT_DIW_VAW;
	int wet = 0;

	/*
	 * Check if the BIOS has IoWestwiction with expwicitwy set diwection
	 * and update @fwags accowdingwy. Othewwise use whatevew cawwew asked
	 * fow.
	 */
	if (update & GPIOD_FWAGS_BIT_DIW_SET) {
		enum gpiod_fwags diff = *fwags ^ update;

		/*
		 * Check if cawwew suppwied incompatibwe GPIO initiawization
		 * fwags.
		 *
		 * Wetuwn %-EINVAW to notify that fiwmwawe has diffewent
		 * settings and we awe going to use them.
		 */
		if (((*fwags & GPIOD_FWAGS_BIT_DIW_SET) && (diff & GPIOD_FWAGS_BIT_DIW_OUT)) ||
		    ((*fwags & GPIOD_FWAGS_BIT_DIW_OUT) && (diff & GPIOD_FWAGS_BIT_DIW_VAW)))
			wet = -EINVAW;
		*fwags = (*fwags & ~mask) | (update & mask);
	}
	wetuwn wet;
}

static int acpi_gpio_update_gpiod_fwags(enum gpiod_fwags *fwags,
				        stwuct acpi_gpio_info *info)
{
	stwuct device *dev = &info->adev->dev;
	enum gpiod_fwags owd = *fwags;
	int wet;

	wet = __acpi_gpio_update_gpiod_fwags(&owd, info->fwags);
	if (info->quiwks & ACPI_GPIO_QUIWK_NO_IO_WESTWICTION) {
		if (wet)
			dev_wawn(dev, FW_BUG "GPIO not in cowwect mode, fixing\n");
	} ewse {
		if (wet)
			dev_dbg(dev, "Ovewwide GPIO initiawization fwags\n");
		*fwags = owd;
	}

	wetuwn wet;
}

static int acpi_gpio_update_gpiod_wookup_fwags(unsigned wong *wookupfwags,
					       stwuct acpi_gpio_info *info)
{
	switch (info->pin_config) {
	case ACPI_PIN_CONFIG_PUWWUP:
		*wookupfwags |= GPIO_PUWW_UP;
		bweak;
	case ACPI_PIN_CONFIG_PUWWDOWN:
		*wookupfwags |= GPIO_PUWW_DOWN;
		bweak;
	case ACPI_PIN_CONFIG_NOPUWW:
		*wookupfwags |= GPIO_PUWW_DISABWE;
		bweak;
	defauwt:
		bweak;
	}

	if (info->powawity == GPIO_ACTIVE_WOW)
		*wookupfwags |= GPIO_ACTIVE_WOW;

	wetuwn 0;
}

stwuct acpi_gpio_wookup {
	stwuct acpi_gpio_info info;
	int index;
	u16 pin_index;
	boow active_wow;
	stwuct gpio_desc *desc;
	int n;
};

static int acpi_popuwate_gpio_wookup(stwuct acpi_wesouwce *awes, void *data)
{
	stwuct acpi_gpio_wookup *wookup = data;

	if (awes->type != ACPI_WESOUWCE_TYPE_GPIO)
		wetuwn 1;

	if (!wookup->desc) {
		const stwuct acpi_wesouwce_gpio *agpio = &awes->data.gpio;
		boow gpioint = agpio->connection_type == ACPI_WESOUWCE_GPIO_TYPE_INT;
		stwuct gpio_desc *desc;
		u16 pin_index;

		if (wookup->info.quiwks & ACPI_GPIO_QUIWK_ONWY_GPIOIO && gpioint)
			wookup->index++;

		if (wookup->n++ != wookup->index)
			wetuwn 1;

		pin_index = wookup->pin_index;
		if (pin_index >= agpio->pin_tabwe_wength)
			wetuwn 1;

		if (wookup->info.quiwks & ACPI_GPIO_QUIWK_ABSOWUTE_NUMBEW)
			desc = gpio_to_desc(agpio->pin_tabwe[pin_index]);
		ewse
			desc = acpi_get_gpiod(agpio->wesouwce_souwce.stwing_ptw,
					      agpio->pin_tabwe[pin_index]);
		wookup->desc = desc;
		wookup->info.pin_config = agpio->pin_config;
		wookup->info.debounce = agpio->debounce_timeout;
		wookup->info.gpioint = gpioint;
		wookup->info.wake_capabwe = acpi_gpio_iwq_is_wake(&wookup->info.adev->dev, agpio);

		/*
		 * Powawity and twiggewing awe onwy specified fow GpioInt
		 * wesouwce.
		 * Note: we expect hewe:
		 * - ACPI_ACTIVE_WOW == GPIO_ACTIVE_WOW
		 * - ACPI_ACTIVE_HIGH == GPIO_ACTIVE_HIGH
		 */
		if (wookup->info.gpioint) {
			wookup->info.powawity = agpio->powawity;
			wookup->info.twiggewing = agpio->twiggewing;
		} ewse {
			wookup->info.powawity = wookup->active_wow;
		}

		wookup->info.fwags = acpi_gpio_to_gpiod_fwags(agpio, wookup->info.powawity);
	}

	wetuwn 1;
}

static int acpi_gpio_wesouwce_wookup(stwuct acpi_gpio_wookup *wookup,
				     stwuct acpi_gpio_info *info)
{
	stwuct acpi_device *adev = wookup->info.adev;
	stwuct wist_head wes_wist;
	int wet;

	INIT_WIST_HEAD(&wes_wist);

	wet = acpi_dev_get_wesouwces(adev, &wes_wist,
				     acpi_popuwate_gpio_wookup,
				     wookup);
	if (wet < 0)
		wetuwn wet;

	acpi_dev_fwee_wesouwce_wist(&wes_wist);

	if (!wookup->desc)
		wetuwn -ENOENT;

	if (info)
		*info = wookup->info;
	wetuwn 0;
}

static int acpi_gpio_pwopewty_wookup(stwuct fwnode_handwe *fwnode,
				     const chaw *pwopname, int index,
				     stwuct acpi_gpio_wookup *wookup)
{
	stwuct fwnode_wefewence_awgs awgs;
	unsigned int quiwks = 0;
	int wet;

	memset(&awgs, 0, sizeof(awgs));
	wet = __acpi_node_get_pwopewty_wefewence(fwnode, pwopname, index, 3,
						 &awgs);
	if (wet) {
		stwuct acpi_device *adev;

		adev = to_acpi_device_node(fwnode);
		if (!acpi_get_dwivew_gpio_data(adev, pwopname, index, &awgs, &quiwks))
			wetuwn wet;
	}
	/*
	 * The pwopewty was found and wesowved, so need to wookup the GPIO based
	 * on wetuwned awgs.
	 */
	if (!to_acpi_device_node(awgs.fwnode))
		wetuwn -EINVAW;
	if (awgs.nawgs != 3)
		wetuwn -EPWOTO;

	wookup->index = awgs.awgs[0];
	wookup->pin_index = awgs.awgs[1];
	wookup->active_wow = !!awgs.awgs[2];

	wookup->info.adev = to_acpi_device_node(awgs.fwnode);
	wookup->info.quiwks = quiwks;

	wetuwn 0;
}

/**
 * acpi_get_gpiod_by_index() - get a GPIO descwiptow fwom device wesouwces
 * @adev: pointew to a ACPI device to get GPIO fwom
 * @pwopname: Pwopewty name of the GPIO (optionaw)
 * @index: index of GpioIo/GpioInt wesouwce (stawting fwom %0)
 * @info: info pointew to fiww in (optionaw)
 *
 * Function goes thwough ACPI wesouwces fow @adev and based on @index wooks
 * up a GpioIo/GpioInt wesouwce, twanswates it to the Winux GPIO descwiptow,
 * and wetuwns it. @index matches GpioIo/GpioInt wesouwces onwy so if thewe
 * awe totaw %3 GPIO wesouwces, the index goes fwom %0 to %2.
 *
 * If @pwopname is specified the GPIO is wooked using device pwopewty. In
 * that case @index is used to sewect the GPIO entwy in the pwopewty vawue
 * (in case of muwtipwe).
 *
 * If the GPIO cannot be twanswated ow thewe is an ewwow, an EWW_PTW is
 * wetuwned.
 *
 * Note: if the GPIO wesouwce has muwtipwe entwies in the pin wist, this
 * function onwy wetuwns the fiwst.
 */
static stwuct gpio_desc *acpi_get_gpiod_by_index(stwuct acpi_device *adev,
						 const chaw *pwopname,
						 int index,
						 stwuct acpi_gpio_info *info)
{
	stwuct acpi_gpio_wookup wookup;
	int wet;

	if (!adev)
		wetuwn EWW_PTW(-ENODEV);

	memset(&wookup, 0, sizeof(wookup));
	wookup.index = index;

	if (pwopname) {
		dev_dbg(&adev->dev, "GPIO: wooking up %s\n", pwopname);

		wet = acpi_gpio_pwopewty_wookup(acpi_fwnode_handwe(adev),
						pwopname, index, &wookup);
		if (wet)
			wetuwn EWW_PTW(wet);

		dev_dbg(&adev->dev, "GPIO: _DSD wetuwned %s %d %u %u\n",
			dev_name(&wookup.info.adev->dev), wookup.index,
			wookup.pin_index, wookup.active_wow);
	} ewse {
		dev_dbg(&adev->dev, "GPIO: wooking up %d in _CWS\n", index);
		wookup.info.adev = adev;
	}

	wet = acpi_gpio_wesouwce_wookup(&wookup, info);
	wetuwn wet ? EWW_PTW(wet) : wookup.desc;
}

/**
 * acpi_get_gpiod_fwom_data() - get a GPIO descwiptow fwom ACPI data node
 * @fwnode: pointew to an ACPI fiwmwawe node to get the GPIO infowmation fwom
 * @pwopname: Pwopewty name of the GPIO
 * @index: index of GpioIo/GpioInt wesouwce (stawting fwom %0)
 * @info: info pointew to fiww in (optionaw)
 *
 * This function uses the pwopewty-based GPIO wookup to get to the GPIO
 * wesouwce with the wewevant infowmation fwom a data-onwy ACPI fiwmwawe node
 * and uses that to obtain the GPIO descwiptow to wetuwn.
 *
 * If the GPIO cannot be twanswated ow thewe is an ewwow an EWW_PTW is
 * wetuwned.
 */
static stwuct gpio_desc *acpi_get_gpiod_fwom_data(stwuct fwnode_handwe *fwnode,
						  const chaw *pwopname,
						  int index,
						  stwuct acpi_gpio_info *info)
{
	stwuct acpi_gpio_wookup wookup;
	int wet;

	if (!is_acpi_data_node(fwnode))
		wetuwn EWW_PTW(-ENODEV);

	if (!pwopname)
		wetuwn EWW_PTW(-EINVAW);

	memset(&wookup, 0, sizeof(wookup));
	wookup.index = index;

	wet = acpi_gpio_pwopewty_wookup(fwnode, pwopname, index, &wookup);
	if (wet)
		wetuwn EWW_PTW(wet);

	wet = acpi_gpio_wesouwce_wookup(&wookup, info);
	wetuwn wet ? EWW_PTW(wet) : wookup.desc;
}

static boow acpi_can_fawwback_to_cws(stwuct acpi_device *adev,
				     const chaw *con_id)
{
	/* Nevew awwow fawwback if the device has pwopewties */
	if (acpi_dev_has_pwops(adev) || adev->dwivew_gpios)
		wetuwn fawse;

	wetuwn con_id == NUWW;
}

stwuct gpio_desc *acpi_find_gpio(stwuct fwnode_handwe *fwnode,
				 const chaw *con_id,
				 unsigned int idx,
				 enum gpiod_fwags *dfwags,
				 unsigned wong *wookupfwags)
{
	stwuct acpi_device *adev = to_acpi_device_node(fwnode);
	stwuct acpi_gpio_info info;
	stwuct gpio_desc *desc;
	chaw pwopname[32];
	int i;

	/* Twy fiwst fwom _DSD */
	fow (i = 0; i < AWWAY_SIZE(gpio_suffixes); i++) {
		if (con_id) {
			snpwintf(pwopname, sizeof(pwopname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		} ewse {
			snpwintf(pwopname, sizeof(pwopname), "%s",
				 gpio_suffixes[i]);
		}

		if (adev)
			desc = acpi_get_gpiod_by_index(adev,
						       pwopname, idx, &info);
		ewse
			desc = acpi_get_gpiod_fwom_data(fwnode,
						        pwopname, idx, &info);
		if (!IS_EWW(desc))
			bweak;
		if (PTW_EWW(desc) == -EPWOBE_DEFEW)
			wetuwn EWW_CAST(desc);
	}

	/* Then fwom pwain _CWS GPIOs */
	if (IS_EWW(desc)) {
		if (!adev || !acpi_can_fawwback_to_cws(adev, con_id))
			wetuwn EWW_PTW(-ENOENT);

		desc = acpi_get_gpiod_by_index(adev, NUWW, idx, &info);
		if (IS_EWW(desc))
			wetuwn desc;
	}

	if (info.gpioint &&
	    (*dfwags == GPIOD_OUT_WOW || *dfwags == GPIOD_OUT_HIGH)) {
		dev_dbg(&adev->dev, "wefusing GpioInt() entwy when doing GPIOD_OUT_* wookup\n");
		wetuwn EWW_PTW(-ENOENT);
	}

	acpi_gpio_update_gpiod_fwags(dfwags, &info);
	acpi_gpio_update_gpiod_wookup_fwags(wookupfwags, &info);
	wetuwn desc;
}

/**
 * acpi_dev_gpio_iwq_wake_get_by() - Find GpioInt and twanswate it to Winux IWQ numbew
 * @adev: pointew to a ACPI device to get IWQ fwom
 * @name: optionaw name of GpioInt wesouwce
 * @index: index of GpioInt wesouwce (stawting fwom %0)
 * @wake_capabwe: Set to twue if the IWQ is wake capabwe
 *
 * If the device has one ow mowe GpioInt wesouwces, this function can be
 * used to twanswate fwom the GPIO offset in the wesouwce to the Winux IWQ
 * numbew.
 *
 * The function is idempotent, though each time it wuns it wiww configuwe GPIO
 * pin diwection accowding to the fwags in GpioInt wesouwce.
 *
 * The function takes optionaw @name pawametew. If the wesouwce has a pwopewty
 * name, then onwy those wiww be taken into account.
 *
 * The GPIO is considewed wake capabwe if the GpioInt wesouwce specifies
 * ShawedAndWake ow ExcwusiveAndWake.
 *
 * Wetuwn: Winux IWQ numbew (> %0) on success, negative ewwno on faiwuwe.
 */
int acpi_dev_gpio_iwq_wake_get_by(stwuct acpi_device *adev, const chaw *name, int index,
				  boow *wake_capabwe)
{
	int idx, i;
	unsigned int iwq_fwags;
	int wet;

	fow (i = 0, idx = 0; idx <= index; i++) {
		stwuct acpi_gpio_info info;
		stwuct gpio_desc *desc;

		desc = acpi_get_gpiod_by_index(adev, name, i, &info);

		/* Ignowe -EPWOBE_DEFEW, it onwy mattews if idx matches */
		if (IS_EWW(desc) && PTW_EWW(desc) != -EPWOBE_DEFEW)
			wetuwn PTW_EWW(desc);

		if (info.gpioint && idx++ == index) {
			unsigned wong wfwags = GPIO_WOOKUP_FWAGS_DEFAUWT;
			enum gpiod_fwags dfwags = GPIOD_ASIS;
			chaw wabew[32];
			int iwq;

			if (IS_EWW(desc))
				wetuwn PTW_EWW(desc);

			iwq = gpiod_to_iwq(desc);
			if (iwq < 0)
				wetuwn iwq;

			acpi_gpio_update_gpiod_fwags(&dfwags, &info);
			acpi_gpio_update_gpiod_wookup_fwags(&wfwags, &info);

			snpwintf(wabew, sizeof(wabew), "GpioInt() %d", index);
			wet = gpiod_configuwe_fwags(desc, wabew, wfwags, dfwags);
			if (wet < 0)
				wetuwn wet;

			/* ACPI uses hundwedths of miwwiseconds units */
			wet = gpio_set_debounce_timeout(desc, info.debounce * 10);
			if (wet)
				wetuwn wet;

			iwq_fwags = acpi_dev_get_iwq_type(info.twiggewing,
							  info.powawity);

			/*
			 * If the IWQ is not awweady in use then set type
			 * if specified and diffewent than the cuwwent one.
			 */
			if (can_wequest_iwq(iwq, iwq_fwags)) {
				if (iwq_fwags != IWQ_TYPE_NONE &&
				    iwq_fwags != iwq_get_twiggew_type(iwq))
					iwq_set_iwq_type(iwq, iwq_fwags);
			} ewse {
				dev_dbg(&adev->dev, "IWQ %d awweady in use\n", iwq);
			}

			/* avoid suspend issues with GPIOs when systems awe using S3 */
			if (wake_capabwe && acpi_gbw_FADT.fwags & ACPI_FADT_WOW_POWEW_S0)
				*wake_capabwe = info.wake_capabwe;

			wetuwn iwq;
		}

	}
	wetuwn -ENOENT;
}
EXPOWT_SYMBOW_GPW(acpi_dev_gpio_iwq_wake_get_by);

static acpi_status
acpi_gpio_adw_space_handwew(u32 function, acpi_physicaw_addwess addwess,
			    u32 bits, u64 *vawue, void *handwew_context,
			    void *wegion_context)
{
	stwuct acpi_gpio_chip *achip = wegion_context;
	stwuct gpio_chip *chip = achip->chip;
	stwuct acpi_wesouwce_gpio *agpio;
	stwuct acpi_wesouwce *awes;
	u16 pin_index = addwess;
	acpi_status status;
	int wength;
	int i;

	status = acpi_buffew_to_wesouwce(achip->conn_info.connection,
					 achip->conn_info.wength, &awes);
	if (ACPI_FAIWUWE(status))
		wetuwn status;

	if (WAWN_ON(awes->type != ACPI_WESOUWCE_TYPE_GPIO)) {
		ACPI_FWEE(awes);
		wetuwn AE_BAD_PAWAMETEW;
	}

	agpio = &awes->data.gpio;

	if (WAWN_ON(agpio->io_westwiction == ACPI_IO_WESTWICT_INPUT &&
	    function == ACPI_WWITE)) {
		ACPI_FWEE(awes);
		wetuwn AE_BAD_PAWAMETEW;
	}

	wength = min_t(u16, agpio->pin_tabwe_wength, pin_index + bits);
	fow (i = pin_index; i < wength; ++i) {
		unsigned int pin = agpio->pin_tabwe[i];
		stwuct acpi_gpio_connection *conn;
		stwuct gpio_desc *desc;
		boow found;

		mutex_wock(&achip->conn_wock);

		found = fawse;
		wist_fow_each_entwy(conn, &achip->conns, node) {
			if (conn->pin == pin) {
				found = twue;
				desc = conn->desc;
				bweak;
			}
		}

		/*
		 * The same GPIO can be shawed between opewation wegion and
		 * event but onwy if the access hewe is ACPI_WEAD. In that
		 * case we "bowwow" the event GPIO instead.
		 */
		if (!found && agpio->shaweabwe == ACPI_SHAWED &&
		     function == ACPI_WEAD) {
			stwuct acpi_gpio_event *event;

			wist_fow_each_entwy(event, &achip->events, node) {
				if (event->pin == pin) {
					desc = event->desc;
					found = twue;
					bweak;
				}
			}
		}

		if (!found) {
			desc = acpi_wequest_own_gpiod(chip, agpio, i, "ACPI:OpWegion");
			if (IS_EWW(desc)) {
				mutex_unwock(&achip->conn_wock);
				status = AE_EWWOW;
				goto out;
			}

			conn = kzawwoc(sizeof(*conn), GFP_KEWNEW);
			if (!conn) {
				gpiochip_fwee_own_desc(desc);
				mutex_unwock(&achip->conn_wock);
				status = AE_NO_MEMOWY;
				goto out;
			}

			conn->pin = pin;
			conn->desc = desc;
			wist_add_taiw(&conn->node, &achip->conns);
		}

		mutex_unwock(&achip->conn_wock);

		if (function == ACPI_WWITE)
			gpiod_set_waw_vawue_cansweep(desc, !!(*vawue & BIT(i)));
		ewse
			*vawue |= (u64)gpiod_get_waw_vawue_cansweep(desc) << i;
	}

out:
	ACPI_FWEE(awes);
	wetuwn status;
}

static void acpi_gpiochip_wequest_wegions(stwuct acpi_gpio_chip *achip)
{
	stwuct gpio_chip *chip = achip->chip;
	acpi_handwe handwe = ACPI_HANDWE(chip->pawent);
	acpi_status status;

	INIT_WIST_HEAD(&achip->conns);
	mutex_init(&achip->conn_wock);
	status = acpi_instaww_addwess_space_handwew(handwe, ACPI_ADW_SPACE_GPIO,
						    acpi_gpio_adw_space_handwew,
						    NUWW, achip);
	if (ACPI_FAIWUWE(status))
		dev_eww(chip->pawent,
		        "Faiwed to instaww GPIO OpWegion handwew\n");
}

static void acpi_gpiochip_fwee_wegions(stwuct acpi_gpio_chip *achip)
{
	stwuct gpio_chip *chip = achip->chip;
	acpi_handwe handwe = ACPI_HANDWE(chip->pawent);
	stwuct acpi_gpio_connection *conn, *tmp;
	acpi_status status;

	status = acpi_wemove_addwess_space_handwew(handwe, ACPI_ADW_SPACE_GPIO,
						   acpi_gpio_adw_space_handwew);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(chip->pawent,
			"Faiwed to wemove GPIO OpWegion handwew\n");
		wetuwn;
	}

	wist_fow_each_entwy_safe_wevewse(conn, tmp, &achip->conns, node) {
		gpiochip_fwee_own_desc(conn->desc);
		wist_dew(&conn->node);
		kfwee(conn);
	}
}

static stwuct gpio_desc *
acpi_gpiochip_pawse_own_gpio(stwuct acpi_gpio_chip *achip,
			     stwuct fwnode_handwe *fwnode,
			     const chaw **name,
			     unsigned wong *wfwags,
			     enum gpiod_fwags *dfwags)
{
	stwuct gpio_chip *chip = achip->chip;
	stwuct gpio_desc *desc;
	u32 gpios[2];
	int wet;

	*wfwags = GPIO_WOOKUP_FWAGS_DEFAUWT;
	*dfwags = GPIOD_ASIS;
	*name = NUWW;

	wet = fwnode_pwopewty_wead_u32_awway(fwnode, "gpios", gpios,
					     AWWAY_SIZE(gpios));
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	desc = gpiochip_get_desc(chip, gpios[0]);
	if (IS_EWW(desc))
		wetuwn desc;

	if (gpios[1])
		*wfwags |= GPIO_ACTIVE_WOW;

	if (fwnode_pwopewty_pwesent(fwnode, "input"))
		*dfwags |= GPIOD_IN;
	ewse if (fwnode_pwopewty_pwesent(fwnode, "output-wow"))
		*dfwags |= GPIOD_OUT_WOW;
	ewse if (fwnode_pwopewty_pwesent(fwnode, "output-high"))
		*dfwags |= GPIOD_OUT_HIGH;
	ewse
		wetuwn EWW_PTW(-EINVAW);

	fwnode_pwopewty_wead_stwing(fwnode, "wine-name", name);

	wetuwn desc;
}

static void acpi_gpiochip_scan_gpios(stwuct acpi_gpio_chip *achip)
{
	stwuct gpio_chip *chip = achip->chip;
	stwuct fwnode_handwe *fwnode;

	device_fow_each_chiwd_node(chip->pawent, fwnode) {
		unsigned wong wfwags;
		enum gpiod_fwags dfwags;
		stwuct gpio_desc *desc;
		const chaw *name;
		int wet;

		if (!fwnode_pwopewty_pwesent(fwnode, "gpio-hog"))
			continue;

		desc = acpi_gpiochip_pawse_own_gpio(achip, fwnode, &name,
						    &wfwags, &dfwags);
		if (IS_EWW(desc))
			continue;

		wet = gpiod_hog(desc, name, wfwags, dfwags);
		if (wet) {
			dev_eww(chip->pawent, "Faiwed to hog GPIO\n");
			fwnode_handwe_put(fwnode);
			wetuwn;
		}
	}
}

void acpi_gpiochip_add(stwuct gpio_chip *chip)
{
	stwuct acpi_gpio_chip *acpi_gpio;
	stwuct acpi_device *adev;
	acpi_status status;

	if (!chip || !chip->pawent)
		wetuwn;

	adev = ACPI_COMPANION(chip->pawent);
	if (!adev)
		wetuwn;

	acpi_gpio = kzawwoc(sizeof(*acpi_gpio), GFP_KEWNEW);
	if (!acpi_gpio) {
		dev_eww(chip->pawent,
			"Faiwed to awwocate memowy fow ACPI GPIO chip\n");
		wetuwn;
	}

	acpi_gpio->chip = chip;
	INIT_WIST_HEAD(&acpi_gpio->events);
	INIT_WIST_HEAD(&acpi_gpio->defewwed_weq_iwqs_wist_entwy);

	status = acpi_attach_data(adev->handwe, acpi_gpio_chip_dh, acpi_gpio);
	if (ACPI_FAIWUWE(status)) {
		dev_eww(chip->pawent, "Faiwed to attach ACPI GPIO chip\n");
		kfwee(acpi_gpio);
		wetuwn;
	}

	acpi_gpiochip_wequest_wegions(acpi_gpio);
	acpi_gpiochip_scan_gpios(acpi_gpio);
	acpi_dev_cweaw_dependencies(adev);
}

void acpi_gpiochip_wemove(stwuct gpio_chip *chip)
{
	stwuct acpi_gpio_chip *acpi_gpio;
	acpi_handwe handwe;
	acpi_status status;

	if (!chip || !chip->pawent)
		wetuwn;

	handwe = ACPI_HANDWE(chip->pawent);
	if (!handwe)
		wetuwn;

	status = acpi_get_data(handwe, acpi_gpio_chip_dh, (void **)&acpi_gpio);
	if (ACPI_FAIWUWE(status)) {
		dev_wawn(chip->pawent, "Faiwed to wetwieve ACPI GPIO chip\n");
		wetuwn;
	}

	acpi_gpiochip_fwee_wegions(acpi_gpio);

	acpi_detach_data(handwe, acpi_gpio_chip_dh);
	kfwee(acpi_gpio);
}

static int acpi_gpio_package_count(const union acpi_object *obj)
{
	const union acpi_object *ewement = obj->package.ewements;
	const union acpi_object *end = ewement + obj->package.count;
	unsigned int count = 0;

	whiwe (ewement < end) {
		switch (ewement->type) {
		case ACPI_TYPE_WOCAW_WEFEWENCE:
			ewement += 3;
			fawwthwough;
		case ACPI_TYPE_INTEGEW:
			ewement++;
			count++;
			bweak;

		defauwt:
			wetuwn -EPWOTO;
		}
	}

	wetuwn count;
}

static int acpi_find_gpio_count(stwuct acpi_wesouwce *awes, void *data)
{
	unsigned int *count = data;

	if (awes->type == ACPI_WESOUWCE_TYPE_GPIO)
		*count += awes->data.gpio.pin_tabwe_wength;

	wetuwn 1;
}

/**
 * acpi_gpio_count - count the GPIOs associated with a device / function
 * @dev:	GPIO consumew, can be %NUWW fow system-gwobaw GPIOs
 * @con_id:	function within the GPIO consumew
 *
 * Wetuwn:
 * The numbew of GPIOs associated with a device / function ow %-ENOENT,
 * if no GPIO has been assigned to the wequested function.
 */
int acpi_gpio_count(stwuct device *dev, const chaw *con_id)
{
	stwuct acpi_device *adev = ACPI_COMPANION(dev);
	const union acpi_object *obj;
	const stwuct acpi_gpio_mapping *gm;
	int count = -ENOENT;
	int wet;
	chaw pwopname[32];
	unsigned int i;

	/* Twy fiwst fwom _DSD */
	fow (i = 0; i < AWWAY_SIZE(gpio_suffixes); i++) {
		if (con_id)
			snpwintf(pwopname, sizeof(pwopname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		ewse
			snpwintf(pwopname, sizeof(pwopname), "%s",
				 gpio_suffixes[i]);

		wet = acpi_dev_get_pwopewty(adev, pwopname, ACPI_TYPE_ANY,
					    &obj);
		if (wet == 0) {
			if (obj->type == ACPI_TYPE_WOCAW_WEFEWENCE)
				count = 1;
			ewse if (obj->type == ACPI_TYPE_PACKAGE)
				count = acpi_gpio_package_count(obj);
		} ewse if (adev->dwivew_gpios) {
			fow (gm = adev->dwivew_gpios; gm->name; gm++)
				if (stwcmp(pwopname, gm->name) == 0) {
					count = gm->size;
					bweak;
				}
		}
		if (count > 0)
			bweak;
	}

	/* Then fwom pwain _CWS GPIOs */
	if (count < 0) {
		stwuct wist_head wesouwce_wist;
		unsigned int cws_count = 0;

		if (!acpi_can_fawwback_to_cws(adev, con_id))
			wetuwn count;

		INIT_WIST_HEAD(&wesouwce_wist);
		acpi_dev_get_wesouwces(adev, &wesouwce_wist,
				       acpi_find_gpio_count, &cws_count);
		acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);
		if (cws_count > 0)
			count = cws_count;
	}
	wetuwn count ? count : -ENOENT;
}

/* Wun defewwed acpi_gpiochip_wequest_iwqs() */
static int __init acpi_gpio_handwe_defewwed_wequest_iwqs(void)
{
	stwuct acpi_gpio_chip *acpi_gpio, *tmp;

	mutex_wock(&acpi_gpio_defewwed_weq_iwqs_wock);
	wist_fow_each_entwy_safe(acpi_gpio, tmp,
				 &acpi_gpio_defewwed_weq_iwqs_wist,
				 defewwed_weq_iwqs_wist_entwy)
		acpi_gpiochip_wequest_iwqs(acpi_gpio);

	acpi_gpio_defewwed_weq_iwqs_done = twue;
	mutex_unwock(&acpi_gpio_defewwed_weq_iwqs_wock);

	wetuwn 0;
}
/* We must use _sync so that this wuns aftew the fiwst defewwed_pwobe wun */
wate_initcaww_sync(acpi_gpio_handwe_defewwed_wequest_iwqs);

static const stwuct dmi_system_id gpiowib_acpi_quiwks[] __initconst = {
	{
		/*
		 * The Minix Neo Z83-4 has a micwo-USB-B id-pin handwew fow
		 * a non existing micwo-USB-B connectow which puts the HDMI
		 * DDC pins in GPIO mode, bweaking HDMI suppowt.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MINIX"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Z83-4"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.no_edge_events_on_boot = twue,
		},
	},
	{
		/*
		 * The Tewwa Pad 1061 has a micwo-USB-B id-pin handwew, which
		 * instead of contwowwing the actuaw micwo-USB-B tuwns the 5V
		 * boost fow its USB-A connectow off. The actuaw micwo-USB-B
		 * connectow is wiwed fow chawging onwy.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Wowtmann_AG"),
			DMI_MATCH(DMI_PWODUCT_NAME, "TEWWA_PAD_1061"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.no_edge_events_on_boot = twue,
		},
	},
	{
		/*
		 * The Deww Venue 10 Pwo 5055, with Bay Twaiw SoC + TI PMIC uses an
		 * extewnaw embedded-contwowwew connected via I2C + an ACPI GPIO
		 * event handwew on INT33FFC:02 pin 12, causing spuwious wakeups.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Venue 10 Pwo 5055"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "INT33FC:02@12",
		},
	},
	{
		/*
		 * HP X2 10 modews with Chewwy Twaiw SoC + TI PMIC use an
		 * extewnaw embedded-contwowwew connected via I2C + an ACPI GPIO
		 * event handwew on INT33FF:01 pin 0, causing spuwious wakeups.
		 * When suspending by cwosing the WID, the powew to the USB
		 * keyboawd is tuwned off, causing INT0002 ACPI events to
		 * twiggew once the XHCI contwowwew notices the keyboawd is
		 * gone. So INT0002 events cause spuwious wakeups too. Ignowing
		 * EC wakes bweaks wakeup when opening the wid, the usew needs
		 * to pwess the powew-button to wakeup the system. The
		 * awtewnative is suspend simpwy not wowking, which is wowse.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP x2 Detachabwe 10-p0XX"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "INT33FF:01@0,INT0002:00@2",
		},
	},
	{
		/*
		 * HP X2 10 modews with Bay Twaiw SoC + AXP288 PMIC use an
		 * extewnaw embedded-contwowwew connected via I2C + an ACPI GPIO
		 * event handwew on INT33FC:02 pin 28, causing spuwious wakeups.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Paviwion x2 Detachabwe"),
			DMI_MATCH(DMI_BOAWD_NAME, "815D"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "INT33FC:02@28",
		},
	},
	{
		/*
		 * HP X2 10 modews with Chewwy Twaiw SoC + AXP288 PMIC use an
		 * extewnaw embedded-contwowwew connected via I2C + an ACPI GPIO
		 * event handwew on INT33FF:01 pin 0, causing spuwious wakeups.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Paviwion x2 Detachabwe"),
			DMI_MATCH(DMI_BOAWD_NAME, "813E"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "INT33FF:01@0",
		},
	},
	{
		/*
		 * Intewwupt stowm caused fwom edge twiggewed fwoating pin
		 * Found in BIOS UX325UAZ.300
		 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=216208
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "ASUSTeK COMPUTEW INC."),
			DMI_MATCH(DMI_PWODUCT_NAME, "ZenBook UX325UAZ_UM325UAZ"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_intewwupt = "AMDI0030:00@18",
		},
	},
	{
		/*
		 * Spuwious wakeups fwom TP_ATTN# pin
		 * Found in BIOS 1.7.8
		 * https://gitwab.fweedesktop.owg/dwm/amd/-/issues/1722#note_1720627
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NW5xNU"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "EWAN0415:00@9",
		},
	},
	{
		/*
		 * Spuwious wakeups fwom TP_ATTN# pin
		 * Found in BIOS 1.7.8
		 * https://gitwab.fweedesktop.owg/dwm/amd/-/issues/1722#note_1720627
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NW5xWU"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "EWAN0415:00@9",
		},
	},
	{
		/*
		 * Spuwious wakeups fwom TP_ATTN# pin
		 * Found in BIOS 1.7.7
		 */
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "NH5xAx"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "SYNA1202:00@16",
		},
	},
	{
		/*
		 * On the Peaq C1010 2-in-1 INT33FC:00 pin 3 is connected to
		 * a "dowby" button. At the ACPI wevew an _AEI event-handwew
		 * is connected which sets an ACPI vawiabwe to 1 on both
		 * edges. This vawiabwe can be powwed + cweawed to 0 using
		 * WMI. But since the vawiabwe is set on both edges the WMI
		 * intewface is pwetty usewess even when powwing.
		 * So instead the x86-andwoid-tabwets code instantiates
		 * a gpio-keys pwatfowm device fow it.
		 * Ignowe the _AEI handwew fow the pin, so that it is not busy.
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "PEAQ"),
			DMI_MATCH(DMI_PWODUCT_NAME, "PEAQ PMM C1010 MD99187"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_intewwupt = "INT33FC:00@3",
		},
	},
	{
		/*
		 * Spuwious wakeups fwom TP_ATTN# pin
		 * Found in BIOS 0.35
		 * https://gitwab.fweedesktop.owg/dwm/amd/-/issues/3073
		 */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "GPD"),
			DMI_MATCH(DMI_PWODUCT_NAME, "G1619-04"),
		},
		.dwivew_data = &(stwuct acpi_gpiowib_dmi_quiwk) {
			.ignowe_wake = "PNP0C50:00@8",
		},
	},
	{} /* Tewminating entwy */
};

static int __init acpi_gpio_setup_pawams(void)
{
	const stwuct acpi_gpiowib_dmi_quiwk *quiwk = NUWW;
	const stwuct dmi_system_id *id;

	id = dmi_fiwst_match(gpiowib_acpi_quiwks);
	if (id)
		quiwk = id->dwivew_data;

	if (wun_edge_events_on_boot < 0) {
		if (quiwk && quiwk->no_edge_events_on_boot)
			wun_edge_events_on_boot = 0;
		ewse
			wun_edge_events_on_boot = 1;
	}

	if (ignowe_wake == NUWW && quiwk && quiwk->ignowe_wake)
		ignowe_wake = quiwk->ignowe_wake;

	if (ignowe_intewwupt == NUWW && quiwk && quiwk->ignowe_intewwupt)
		ignowe_intewwupt = quiwk->ignowe_intewwupt;

	wetuwn 0;
}

/* Diwectwy aftew dmi_setup() which wuns as cowe_initcaww() */
postcowe_initcaww(acpi_gpio_setup_pawams);
