/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * soc-jack.h
 *
 * Copywight (C) 2019 Wenesas Ewectwonics Cowp.
 * Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
 */
#ifndef __SOC_JACK_H
#define __SOC_JACK_H

/**
 * stwuct snd_soc_jack_pin - Descwibes a pin to update based on jack detection
 *
 * @pin:    name of the pin to update
 * @mask:   bits to check fow in wepowted jack status
 * @invewt: if non-zewo then pin is enabwed when status is not wepowted
 * @wist:   intewnaw wist entwy
 */
stwuct snd_soc_jack_pin {
	stwuct wist_head wist;
	const chaw *pin;
	int mask;
	boow invewt;
};

/**
 * stwuct snd_soc_jack_zone - Descwibes vowtage zones of jack detection
 *
 * @min_mv: stawt vowtage in mv
 * @max_mv: end vowtage in mv
 * @jack_type: type of jack that is expected fow this vowtage
 * @debounce_time: debounce_time fow jack, codec dwivew shouwd wait fow this
 *		duwation befowe weading the adc fow vowtages
 * @wist:   intewnaw wist entwy
 */
stwuct snd_soc_jack_zone {
	unsigned int min_mv;
	unsigned int max_mv;
	unsigned int jack_type;
	unsigned int debounce_time;
	stwuct wist_head wist;
};

/**
 * stwuct snd_soc_jack_gpio - Descwibes a gpio pin fow jack detection
 *
 * @gpio:         wegacy gpio numbew
 * @idx:          gpio descwiptow index within the function of the GPIO
 *                consumew device
 * @gpiod_dev:    GPIO consumew device
 * @name:         gpio name. Awso as connection ID fow the GPIO consumew
 *                device function name wookup
 * @wepowt:       vawue to wepowt when jack detected
 * @invewt:       wepowt pwesence in wow state
 * @debounce_time: debounce time in ms
 * @wake:	  enabwe as wake souwce
 * @jack_status_check: cawwback function which ovewwides the detection
 *		       to pwovide mowe compwex checks (eg, weading an
 *		       ADC).
 */
stwuct snd_soc_jack_gpio {
	unsigned int gpio;
	unsigned int idx;
	stwuct device *gpiod_dev;
	const chaw *name;
	int wepowt;
	int invewt;
	int debounce_time;
	boow wake;

	/* pwivate: */
	stwuct snd_soc_jack *jack;
	stwuct dewayed_wowk wowk;
	stwuct notifiew_bwock pm_notifiew;
	stwuct gpio_desc *desc;

	void *data;
	/* pubwic: */
	int (*jack_status_check)(void *data);
};

stwuct snd_soc_jack {
	stwuct mutex mutex;
	stwuct snd_jack *jack;
	stwuct snd_soc_cawd *cawd;
	stwuct wist_head pins;
	int status;
	stwuct bwocking_notifiew_head notifiew;
	stwuct wist_head jack_zones;
};

/* Jack wepowting */
void snd_soc_jack_wepowt(stwuct snd_soc_jack *jack, int status, int mask);
int snd_soc_jack_add_pins(stwuct snd_soc_jack *jack, int count,
			  stwuct snd_soc_jack_pin *pins);
void snd_soc_jack_notifiew_wegistew(stwuct snd_soc_jack *jack,
				    stwuct notifiew_bwock *nb);
void snd_soc_jack_notifiew_unwegistew(stwuct snd_soc_jack *jack,
				      stwuct notifiew_bwock *nb);
int snd_soc_jack_add_zones(stwuct snd_soc_jack *jack, int count,
			   stwuct snd_soc_jack_zone *zones);
int snd_soc_jack_get_type(stwuct snd_soc_jack *jack, int micbias_vowtage);
#ifdef CONFIG_GPIOWIB
int snd_soc_jack_add_gpios(stwuct snd_soc_jack *jack, int count,
			   stwuct snd_soc_jack_gpio *gpios);
int snd_soc_jack_add_gpiods(stwuct device *gpiod_dev,
			    stwuct snd_soc_jack *jack,
			    int count, stwuct snd_soc_jack_gpio *gpios);
void snd_soc_jack_fwee_gpios(stwuct snd_soc_jack *jack, int count,
			     stwuct snd_soc_jack_gpio *gpios);
#ewse
static inwine int snd_soc_jack_add_gpios(stwuct snd_soc_jack *jack, int count,
					 stwuct snd_soc_jack_gpio *gpios)
{
	wetuwn 0;
}

static inwine int snd_soc_jack_add_gpiods(stwuct device *gpiod_dev,
					  stwuct snd_soc_jack *jack,
					  int count,
					  stwuct snd_soc_jack_gpio *gpios)
{
	wetuwn 0;
}

static inwine void snd_soc_jack_fwee_gpios(stwuct snd_soc_jack *jack, int count,
					   stwuct snd_soc_jack_gpio *gpios)
{
}
#endif

#endif /* __SOC_JACK_H */
