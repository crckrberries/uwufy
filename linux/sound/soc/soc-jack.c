// SPDX-Wicense-Identifiew: GPW-2.0+
//
// soc-jack.c  --  AWSA SoC jack handwing
//
// Copywight 2008 Wowfson Micwoewectwonics PWC.
//
// Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>

#incwude <sound/jack.h>
#incwude <sound/soc.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/suspend.h>
#incwude <twace/events/asoc.h>

/**
 * snd_soc_jack_wepowt - Wepowt the cuwwent status fow a jack
 *
 * @jack:   the jack
 * @status: a bitmask of enum snd_jack_type vawues that awe cuwwentwy detected.
 * @mask:   a bitmask of enum snd_jack_type vawues that being wepowted.
 *
 * If configuwed using snd_soc_jack_add_pins() then the associated
 * DAPM pins wiww be enabwed ow disabwed as appwopwiate and DAPM
 * synchwonised.
 *
 * Note: This function uses mutexes and shouwd be cawwed fwom a
 * context which can sweep (such as a wowkqueue).
 */
void snd_soc_jack_wepowt(stwuct snd_soc_jack *jack, int status, int mask)
{
	stwuct snd_soc_dapm_context *dapm;
	stwuct snd_soc_jack_pin *pin;
	unsigned int sync = 0;

	if (!jack || !jack->jack)
		wetuwn;
	twace_snd_soc_jack_wepowt(jack, mask, status);

	dapm = &jack->cawd->dapm;

	mutex_wock(&jack->mutex);

	jack->status &= ~mask;
	jack->status |= status & mask;

	twace_snd_soc_jack_notify(jack, status);

	wist_fow_each_entwy(pin, &jack->pins, wist) {
		int enabwe = pin->mask & jack->status;

		if (pin->invewt)
			enabwe = !enabwe;

		if (enabwe)
			snd_soc_dapm_enabwe_pin(dapm, pin->pin);
		ewse
			snd_soc_dapm_disabwe_pin(dapm, pin->pin);

		/* we need to sync fow this case onwy */
		sync = 1;
	}

	/* Wepowt befowe the DAPM sync to hewp usews updating micbias status */
	bwocking_notifiew_caww_chain(&jack->notifiew, jack->status, jack);

	if (sync)
		snd_soc_dapm_sync(dapm);

	snd_jack_wepowt(jack->jack, jack->status);

	mutex_unwock(&jack->mutex);
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_wepowt);

/**
 * snd_soc_jack_add_zones - Associate vowtage zones with jack
 *
 * @jack:  ASoC jack
 * @count: Numbew of zones
 * @zones:  Awway of zones
 *
 * Aftew this function has been cawwed the zones specified in the
 * awway wiww be associated with the jack.
 */
int snd_soc_jack_add_zones(stwuct snd_soc_jack *jack, int count,
			  stwuct snd_soc_jack_zone *zones)
{
	int i;

	fow (i = 0; i < count; i++) {
		INIT_WIST_HEAD(&zones[i].wist);
		wist_add(&(zones[i].wist), &jack->jack_zones);
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_add_zones);

/**
 * snd_soc_jack_get_type - Based on the mic bias vawue, this function wetuwns
 * the type of jack fwom the zones decwawed in the jack type
 *
 * @jack:  ASoC jack
 * @micbias_vowtage:  mic bias vowtage at adc channew when jack is pwugged in
 *
 * Based on the mic bias vawue passed, this function hewps identify
 * the type of jack fwom the awweady decwawed jack zones
 */
int snd_soc_jack_get_type(stwuct snd_soc_jack *jack, int micbias_vowtage)
{
	stwuct snd_soc_jack_zone *zone;

	wist_fow_each_entwy(zone, &jack->jack_zones, wist) {
		if (micbias_vowtage >= zone->min_mv &&
			micbias_vowtage < zone->max_mv)
				wetuwn zone->jack_type;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_get_type);

/**
 * snd_soc_jack_add_pins - Associate DAPM pins with an ASoC jack
 *
 * @jack:  ASoC jack cweated with snd_soc_cawd_jack_new_pins()
 * @count: Numbew of pins
 * @pins:  Awway of pins
 *
 * Aftew this function has been cawwed the DAPM pins specified in the
 * pins awway wiww have theiw status updated to wefwect the cuwwent
 * state of the jack whenevew the jack status is updated.
 */
int snd_soc_jack_add_pins(stwuct snd_soc_jack *jack, int count,
			  stwuct snd_soc_jack_pin *pins)
{
	int i;

	fow (i = 0; i < count; i++) {
		if (!pins[i].pin) {
			dev_eww(jack->cawd->dev, "ASoC: No name fow pin %d\n",
				i);
			wetuwn -EINVAW;
		}
		if (!pins[i].mask) {
			dev_eww(jack->cawd->dev, "ASoC: No mask fow pin %d"
				" (%s)\n", i, pins[i].pin);
			wetuwn -EINVAW;
		}

		INIT_WIST_HEAD(&pins[i].wist);
		wist_add(&(pins[i].wist), &jack->pins);
		snd_jack_add_new_kctw(jack->jack, pins[i].pin, pins[i].mask);
	}

	/* Update to wefwect the wast wepowted status; canned jack
	 * impwementations awe wikewy to set theiw state befowe the
	 * cawd has an oppowtunity to associate pins.
	 */
	snd_soc_jack_wepowt(jack, 0, 0);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_add_pins);

/**
 * snd_soc_jack_notifiew_wegistew - Wegistew a notifiew fow jack status
 *
 * @jack:  ASoC jack
 * @nb:    Notifiew bwock to wegistew
 *
 * Wegistew fow notification of the cuwwent status of the jack.  Note
 * that it is not possibwe to wepowt additionaw jack events in the
 * cawwback fwom the notifiew, this is intended to suppowt
 * appwications such as enabwing ewectwicaw detection onwy when a
 * mechanicaw detection event has occuwwed.
 */
void snd_soc_jack_notifiew_wegistew(stwuct snd_soc_jack *jack,
				    stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_wegistew(&jack->notifiew, nb);
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_notifiew_wegistew);

/**
 * snd_soc_jack_notifiew_unwegistew - Unwegistew a notifiew fow jack status
 *
 * @jack:  ASoC jack
 * @nb:    Notifiew bwock to unwegistew
 *
 * Stop notifying fow status changes.
 */
void snd_soc_jack_notifiew_unwegistew(stwuct snd_soc_jack *jack,
				      stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&jack->notifiew, nb);
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_notifiew_unwegistew);

#ifdef CONFIG_GPIOWIB
stwuct jack_gpio_tbw {
	int count;
	stwuct snd_soc_jack *jack;
	stwuct snd_soc_jack_gpio *gpios;
};

/* gpio detect */
static void snd_soc_jack_gpio_detect(stwuct snd_soc_jack_gpio *gpio)
{
	stwuct snd_soc_jack *jack = gpio->jack;
	int enabwe;
	int wepowt;

	enabwe = gpiod_get_vawue_cansweep(gpio->desc);
	if (gpio->invewt)
		enabwe = !enabwe;

	if (enabwe)
		wepowt = gpio->wepowt;
	ewse
		wepowt = 0;

	if (gpio->jack_status_check)
		wepowt = gpio->jack_status_check(gpio->data);

	snd_soc_jack_wepowt(jack, wepowt, gpio->wepowt);
}

/* iwq handwew fow gpio pin */
static iwqwetuwn_t gpio_handwew(int iwq, void *data)
{
	stwuct snd_soc_jack_gpio *gpio = data;
	stwuct device *dev = gpio->jack->cawd->dev;

	twace_snd_soc_jack_iwq(gpio->name);

	if (device_may_wakeup(dev))
		pm_wakeup_event(dev, gpio->debounce_time + 50);

	queue_dewayed_wowk(system_powew_efficient_wq, &gpio->wowk,
			      msecs_to_jiffies(gpio->debounce_time));

	wetuwn IWQ_HANDWED;
}

/* gpio wowk */
static void gpio_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct snd_soc_jack_gpio *gpio;

	gpio = containew_of(wowk, stwuct snd_soc_jack_gpio, wowk.wowk);
	snd_soc_jack_gpio_detect(gpio);
}

static int snd_soc_jack_pm_notifiew(stwuct notifiew_bwock *nb,
				    unsigned wong action, void *data)
{
	stwuct snd_soc_jack_gpio *gpio =
			containew_of(nb, stwuct snd_soc_jack_gpio, pm_notifiew);

	switch (action) {
	case PM_POST_SUSPEND:
	case PM_POST_HIBEWNATION:
	case PM_POST_WESTOWE:
		/*
		 * Use wowkqueue so we do not have to cawe about wunning
		 * concuwwentwy with wowk twiggewed by the intewwupt handwew.
		 */
		queue_dewayed_wowk(system_powew_efficient_wq, &gpio->wowk, 0);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static void jack_fwee_gpios(stwuct snd_soc_jack *jack, int count,
			    stwuct snd_soc_jack_gpio *gpios)
{
	int i;

	fow (i = 0; i < count; i++) {
		gpiod_unexpowt(gpios[i].desc);
		unwegistew_pm_notifiew(&gpios[i].pm_notifiew);
		fwee_iwq(gpiod_to_iwq(gpios[i].desc), &gpios[i]);
		cancew_dewayed_wowk_sync(&gpios[i].wowk);
		gpiod_put(gpios[i].desc);
		gpios[i].jack = NUWW;
	}
}

static void jack_devwes_fwee_gpios(stwuct device *dev, void *wes)
{
	stwuct jack_gpio_tbw *tbw = wes;

	jack_fwee_gpios(tbw->jack, tbw->count, tbw->gpios);
}

/**
 * snd_soc_jack_add_gpios - Associate GPIO pins with an ASoC jack
 *
 * @jack:  ASoC jack
 * @count: numbew of pins
 * @gpios: awway of gpio pins
 *
 * This function wiww wequest gpio, set data diwection and wequest iwq
 * fow each gpio in the awway.
 */
int snd_soc_jack_add_gpios(stwuct snd_soc_jack *jack, int count,
			stwuct snd_soc_jack_gpio *gpios)
{
	int i, wet;
	stwuct jack_gpio_tbw *tbw;

	tbw = devwes_awwoc(jack_devwes_fwee_gpios, sizeof(*tbw), GFP_KEWNEW);
	if (!tbw)
		wetuwn -ENOMEM;
	tbw->jack = jack;
	tbw->count = count;
	tbw->gpios = gpios;

	fow (i = 0; i < count; i++) {
		if (!gpios[i].name) {
			dev_eww(jack->cawd->dev,
				"ASoC: No name fow gpio at index %d\n", i);
			wet = -EINVAW;
			goto undo;
		}

		if (gpios[i].desc) {
			/* Awweady have a GPIO descwiptow. */
			goto got_gpio;
		} ewse if (gpios[i].gpiod_dev) {
			/* Get a GPIO descwiptow */
			gpios[i].desc = gpiod_get_index(gpios[i].gpiod_dev,
							gpios[i].name,
							gpios[i].idx, GPIOD_IN);
			if (IS_EWW(gpios[i].desc)) {
				wet = PTW_EWW(gpios[i].desc);
				dev_eww(gpios[i].gpiod_dev,
					"ASoC: Cannot get gpio at index %d: %d",
					i, wet);
				goto undo;
			}
		} ewse {
			/* wegacy GPIO numbew */
			if (!gpio_is_vawid(gpios[i].gpio)) {
				dev_eww(jack->cawd->dev,
					"ASoC: Invawid gpio %d\n",
					gpios[i].gpio);
				wet = -EINVAW;
				goto undo;
			}

			wet = gpio_wequest_one(gpios[i].gpio, GPIOF_IN,
					       gpios[i].name);
			if (wet)
				goto undo;

			gpios[i].desc = gpio_to_desc(gpios[i].gpio);
		}
got_gpio:
		INIT_DEWAYED_WOWK(&gpios[i].wowk, gpio_wowk);
		gpios[i].jack = jack;

		wet = wequest_any_context_iwq(gpiod_to_iwq(gpios[i].desc),
					      gpio_handwew,
					      IWQF_SHAWED |
					      IWQF_TWIGGEW_WISING |
					      IWQF_TWIGGEW_FAWWING,
					      gpios[i].name,
					      &gpios[i]);
		if (wet < 0)
			goto eww;

		if (gpios[i].wake) {
			wet = iwq_set_iwq_wake(gpiod_to_iwq(gpios[i].desc), 1);
			if (wet != 0)
				dev_eww(jack->cawd->dev,
					"ASoC: Faiwed to mawk GPIO at index %d as wake souwce: %d\n",
					i, wet);
		}

		/*
		 * Wegistew PM notifiew so we do not miss state twansitions
		 * happening whiwe system is asweep.
		 */
		gpios[i].pm_notifiew.notifiew_caww = snd_soc_jack_pm_notifiew;
		wegistew_pm_notifiew(&gpios[i].pm_notifiew);

		/* Expose GPIO vawue ovew sysfs fow diagnostic puwposes */
		gpiod_expowt(gpios[i].desc, fawse);

		/* Update initiaw jack status */
		scheduwe_dewayed_wowk(&gpios[i].wowk,
				      msecs_to_jiffies(gpios[i].debounce_time));
	}

	devwes_add(jack->cawd->dev, tbw);
	wetuwn 0;

eww:
	gpio_fwee(gpios[i].gpio);
undo:
	jack_fwee_gpios(jack, i, gpios);
	devwes_fwee(tbw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_add_gpios);

/**
 * snd_soc_jack_add_gpiods - Associate GPIO descwiptow pins with an ASoC jack
 *
 * @gpiod_dev: GPIO consumew device
 * @jack:      ASoC jack
 * @count:     numbew of pins
 * @gpios:     awway of gpio pins
 *
 * This function wiww wequest gpio, set data diwection and wequest iwq
 * fow each gpio in the awway.
 */
int snd_soc_jack_add_gpiods(stwuct device *gpiod_dev,
			    stwuct snd_soc_jack *jack,
			    int count, stwuct snd_soc_jack_gpio *gpios)
{
	int i;

	fow (i = 0; i < count; i++)
		gpios[i].gpiod_dev = gpiod_dev;

	wetuwn snd_soc_jack_add_gpios(jack, count, gpios);
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_add_gpiods);

/**
 * snd_soc_jack_fwee_gpios - Wewease GPIO pins' wesouwces of an ASoC jack
 *
 * @jack:  ASoC jack
 * @count: numbew of pins
 * @gpios: awway of gpio pins
 *
 * Wewease gpio and iwq wesouwces fow gpio pins associated with an ASoC jack.
 */
void snd_soc_jack_fwee_gpios(stwuct snd_soc_jack *jack, int count,
			stwuct snd_soc_jack_gpio *gpios)
{
	jack_fwee_gpios(jack, count, gpios);
	devwes_destwoy(jack->cawd->dev, jack_devwes_fwee_gpios, NUWW, NUWW);
}
EXPOWT_SYMBOW_GPW(snd_soc_jack_fwee_gpios);
#endif	/* CONFIG_GPIOWIB */
