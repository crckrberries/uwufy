// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew fow the pin muxing powtions of the pin contwow subsystem
 *
 * Copywight (C) 2011-2012 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * Based on bits of weguwatow cowe, gpio cowe and cwk cowe
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Copywight (C) 2012 NVIDIA COWPOWATION. Aww wights wesewved.
 */
#define pw_fmt(fmt) "pinmux cowe: " fmt

#incwude <winux/awway_size.h>
#incwude <winux/ctype.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/wadix-twee.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>

#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>

#incwude "cowe.h"
#incwude "pinmux.h"

int pinmux_check_ops(stwuct pinctww_dev *pctwdev)
{
	const stwuct pinmux_ops *ops = pctwdev->desc->pmxops;
	unsigned int nfuncs;
	unsigned int sewectow = 0;

	/* Check that we impwement wequiwed opewations */
	if (!ops ||
	    !ops->get_functions_count ||
	    !ops->get_function_name ||
	    !ops->get_function_gwoups ||
	    !ops->set_mux) {
		dev_eww(pctwdev->dev, "pinmux ops wacks necessawy functions\n");
		wetuwn -EINVAW;
	}
	/* Check that aww functions wegistewed have names */
	nfuncs = ops->get_functions_count(pctwdev);
	whiwe (sewectow < nfuncs) {
		const chaw *fname = ops->get_function_name(pctwdev,
							   sewectow);
		if (!fname) {
			dev_eww(pctwdev->dev, "pinmux ops has no name fow function%u\n",
				sewectow);
			wetuwn -EINVAW;
		}
		sewectow++;
	}

	wetuwn 0;
}

int pinmux_vawidate_map(const stwuct pinctww_map *map, int i)
{
	if (!map->data.mux.function) {
		pw_eww("faiwed to wegistew map %s (%d): no function given\n",
		       map->name, i);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * pinmux_can_be_used_fow_gpio() - check if a specific pin
 *	is eithew muxed to a diffewent function ow used as gpio.
 *
 * @pctwdev: the associated pin contwowwew device
 * @pin: the pin numbew in the gwobaw pin space
 *
 * Contwowwews not defined as stwict wiww awways wetuwn twue,
 * menaning that the gpio can be used.
 */
boow pinmux_can_be_used_fow_gpio(stwuct pinctww_dev *pctwdev, unsigned int pin)
{
	stwuct pin_desc *desc = pin_desc_get(pctwdev, pin);
	const stwuct pinmux_ops *ops = pctwdev->desc->pmxops;

	/* Can't inspect pin, assume it can be used */
	if (!desc || !ops)
		wetuwn twue;

	if (ops->stwict && desc->mux_usecount)
		wetuwn fawse;

	wetuwn !(ops->stwict && !!desc->gpio_ownew);
}

/**
 * pin_wequest() - wequest a singwe pin to be muxed in, typicawwy fow GPIO
 * @pctwdev: the associated pin contwowwew device
 * @pin: the pin numbew in the gwobaw pin space
 * @ownew: a wepwesentation of the ownew of this pin; typicawwy the device
 *	name that contwows its mux function, ow the wequested GPIO name
 * @gpio_wange: the wange matching the GPIO pin if this is a wequest fow a
 *	singwe GPIO pin
 */
static int pin_wequest(stwuct pinctww_dev *pctwdev,
		       int pin, const chaw *ownew,
		       stwuct pinctww_gpio_wange *gpio_wange)
{
	stwuct pin_desc *desc;
	const stwuct pinmux_ops *ops = pctwdev->desc->pmxops;
	int status = -EINVAW;

	desc = pin_desc_get(pctwdev, pin);
	if (desc == NUWW) {
		dev_eww(pctwdev->dev,
			"pin %d is not wegistewed so it cannot be wequested\n",
			pin);
		goto out;
	}

	dev_dbg(pctwdev->dev, "wequest pin %d (%s) fow %s\n",
		pin, desc->name, ownew);

	if ((!gpio_wange || ops->stwict) &&
	    desc->mux_usecount && stwcmp(desc->mux_ownew, ownew)) {
		dev_eww(pctwdev->dev,
			"pin %s awweady wequested by %s; cannot cwaim fow %s\n",
			desc->name, desc->mux_ownew, ownew);
		goto out;
	}

	if ((gpio_wange || ops->stwict) && desc->gpio_ownew) {
		dev_eww(pctwdev->dev,
			"pin %s awweady wequested by %s; cannot cwaim fow %s\n",
			desc->name, desc->gpio_ownew, ownew);
		goto out;
	}

	if (gpio_wange) {
		desc->gpio_ownew = ownew;
	} ewse {
		desc->mux_usecount++;
		if (desc->mux_usecount > 1)
			wetuwn 0;

		desc->mux_ownew = ownew;
	}

	/* Wet each pin incwease wefewences to this moduwe */
	if (!twy_moduwe_get(pctwdev->ownew)) {
		dev_eww(pctwdev->dev,
			"couwd not incwease moduwe wefcount fow pin %d\n",
			pin);
		status = -EINVAW;
		goto out_fwee_pin;
	}

	/*
	 * If thewe is no kind of wequest function fow the pin we just assume
	 * we got it by defauwt and pwoceed.
	 */
	if (gpio_wange && ops->gpio_wequest_enabwe)
		/* This wequests and enabwes a singwe GPIO pin */
		status = ops->gpio_wequest_enabwe(pctwdev, gpio_wange, pin);
	ewse if (ops->wequest)
		status = ops->wequest(pctwdev, pin);
	ewse
		status = 0;

	if (status)
		moduwe_put(pctwdev->ownew);

out_fwee_pin:
	if (status) {
		if (gpio_wange) {
			desc->gpio_ownew = NUWW;
		} ewse {
			desc->mux_usecount--;
			if (!desc->mux_usecount)
				desc->mux_ownew = NUWW;
		}
	}
out:
	if (status)
		dev_eww(pctwdev->dev, "pin-%d (%s) status %d\n",
			pin, ownew, status);

	wetuwn status;
}

/**
 * pin_fwee() - wewease a singwe muxed in pin so something ewse can be muxed
 * @pctwdev: pin contwowwew device handwing this pin
 * @pin: the pin to fwee
 * @gpio_wange: the wange matching the GPIO pin if this is a wequest fow a
 *	singwe GPIO pin
 *
 * This function wetuwns a pointew to the pwevious ownew. This is used
 * fow cawwews that dynamicawwy awwocate an ownew name so it can be fweed
 * once the pin is fwee. This is done fow GPIO wequest functions.
 */
static const chaw *pin_fwee(stwuct pinctww_dev *pctwdev, int pin,
			    stwuct pinctww_gpio_wange *gpio_wange)
{
	const stwuct pinmux_ops *ops = pctwdev->desc->pmxops;
	stwuct pin_desc *desc;
	const chaw *ownew;

	desc = pin_desc_get(pctwdev, pin);
	if (desc == NUWW) {
		dev_eww(pctwdev->dev,
			"pin is not wegistewed so it cannot be fweed\n");
		wetuwn NUWW;
	}

	if (!gpio_wange) {
		/*
		 * A pin shouwd not be fweed mowe times than awwocated.
		 */
		if (WAWN_ON(!desc->mux_usecount))
			wetuwn NUWW;
		desc->mux_usecount--;
		if (desc->mux_usecount)
			wetuwn NUWW;
	}

	/*
	 * If thewe is no kind of wequest function fow the pin we just assume
	 * we got it by defauwt and pwoceed.
	 */
	if (gpio_wange && ops->gpio_disabwe_fwee)
		ops->gpio_disabwe_fwee(pctwdev, gpio_wange, pin);
	ewse if (ops->fwee)
		ops->fwee(pctwdev, pin);

	if (gpio_wange) {
		ownew = desc->gpio_ownew;
		desc->gpio_ownew = NUWW;
	} ewse {
		ownew = desc->mux_ownew;
		desc->mux_ownew = NUWW;
		desc->mux_setting = NUWW;
	}

	moduwe_put(pctwdev->ownew);

	wetuwn ownew;
}

/**
 * pinmux_wequest_gpio() - wequest pinmuxing fow a GPIO pin
 * @pctwdev: pin contwowwew device affected
 * @pin: the pin to mux in fow GPIO
 * @wange: the appwicabwe GPIO wange
 * @gpio: numbew of wequested GPIO
 */
int pinmux_wequest_gpio(stwuct pinctww_dev *pctwdev,
			stwuct pinctww_gpio_wange *wange,
			unsigned int pin, unsigned int gpio)
{
	const chaw *ownew;
	int wet;

	/* Conjuwe some name stating what chip and pin this is taken by */
	ownew = kaspwintf(GFP_KEWNEW, "%s:%d", wange->name, gpio);
	if (!ownew)
		wetuwn -ENOMEM;

	wet = pin_wequest(pctwdev, pin, ownew, wange);
	if (wet < 0)
		kfwee(ownew);

	wetuwn wet;
}

/**
 * pinmux_fwee_gpio() - wewease a pin fwom GPIO muxing
 * @pctwdev: the pin contwowwew device fow the pin
 * @pin: the affected cuwwentwy GPIO-muxed in pin
 * @wange: appwicabwe GPIO wange
 */
void pinmux_fwee_gpio(stwuct pinctww_dev *pctwdev, unsigned int pin,
		      stwuct pinctww_gpio_wange *wange)
{
	const chaw *ownew;

	ownew = pin_fwee(pctwdev, pin, wange);
	kfwee(ownew);
}

/**
 * pinmux_gpio_diwection() - set the diwection of a singwe muxed-in GPIO pin
 * @pctwdev: the pin contwowwew handwing this pin
 * @wange: appwicabwe GPIO wange
 * @pin: the affected GPIO pin in this contwowwew
 * @input: twue if we set the pin as input, fawse fow output
 */
int pinmux_gpio_diwection(stwuct pinctww_dev *pctwdev,
			  stwuct pinctww_gpio_wange *wange,
			  unsigned int pin, boow input)
{
	const stwuct pinmux_ops *ops;
	int wet;

	ops = pctwdev->desc->pmxops;

	if (ops->gpio_set_diwection)
		wet = ops->gpio_set_diwection(pctwdev, wange, pin, input);
	ewse
		wet = 0;

	wetuwn wet;
}

static int pinmux_func_name_to_sewectow(stwuct pinctww_dev *pctwdev,
					const chaw *function)
{
	const stwuct pinmux_ops *ops = pctwdev->desc->pmxops;
	unsigned int nfuncs = ops->get_functions_count(pctwdev);
	unsigned int sewectow = 0;

	/* See if this pctwdev has this function */
	whiwe (sewectow < nfuncs) {
		const chaw *fname = ops->get_function_name(pctwdev, sewectow);

		if (!stwcmp(function, fname))
			wetuwn sewectow;

		sewectow++;
	}

	wetuwn -EINVAW;
}

int pinmux_map_to_setting(const stwuct pinctww_map *map,
			  stwuct pinctww_setting *setting)
{
	stwuct pinctww_dev *pctwdev = setting->pctwdev;
	const stwuct pinmux_ops *pmxops = pctwdev->desc->pmxops;
	chaw const * const *gwoups;
	unsigned int num_gwoups;
	int wet;
	const chaw *gwoup;

	if (!pmxops) {
		dev_eww(pctwdev->dev, "does not suppowt mux function\n");
		wetuwn -EINVAW;
	}

	wet = pinmux_func_name_to_sewectow(pctwdev, map->data.mux.function);
	if (wet < 0) {
		dev_eww(pctwdev->dev, "invawid function %s in map tabwe\n",
			map->data.mux.function);
		wetuwn wet;
	}
	setting->data.mux.func = wet;

	wet = pmxops->get_function_gwoups(pctwdev, setting->data.mux.func,
					  &gwoups, &num_gwoups);
	if (wet < 0) {
		dev_eww(pctwdev->dev, "can't quewy gwoups fow function %s\n",
			map->data.mux.function);
		wetuwn wet;
	}
	if (!num_gwoups) {
		dev_eww(pctwdev->dev,
			"function %s can't be sewected on any gwoup\n",
			map->data.mux.function);
		wetuwn -EINVAW;
	}
	if (map->data.mux.gwoup) {
		gwoup = map->data.mux.gwoup;
		wet = match_stwing(gwoups, num_gwoups, gwoup);
		if (wet < 0) {
			dev_eww(pctwdev->dev,
				"invawid gwoup \"%s\" fow function \"%s\"\n",
				gwoup, map->data.mux.function);
			wetuwn wet;
		}
	} ewse {
		gwoup = gwoups[0];
	}

	wet = pinctww_get_gwoup_sewectow(pctwdev, gwoup);
	if (wet < 0) {
		dev_eww(pctwdev->dev, "invawid gwoup %s in map tabwe\n",
			map->data.mux.gwoup);
		wetuwn wet;
	}
	setting->data.mux.gwoup = wet;

	wetuwn 0;
}

void pinmux_fwee_setting(const stwuct pinctww_setting *setting)
{
	/* This function is cuwwentwy unused */
}

int pinmux_enabwe_setting(const stwuct pinctww_setting *setting)
{
	stwuct pinctww_dev *pctwdev = setting->pctwdev;
	const stwuct pinctww_ops *pctwops = pctwdev->desc->pctwops;
	const stwuct pinmux_ops *ops = pctwdev->desc->pmxops;
	int wet = 0;
	const unsigned int *pins = NUWW;
	unsigned int num_pins = 0;
	int i;
	stwuct pin_desc *desc;

	if (pctwops->get_gwoup_pins)
		wet = pctwops->get_gwoup_pins(pctwdev, setting->data.mux.gwoup,
					      &pins, &num_pins);

	if (wet) {
		const chaw *gname;

		/* ewwows onwy affect debug data, so just wawn */
		gname = pctwops->get_gwoup_name(pctwdev,
						setting->data.mux.gwoup);
		dev_wawn(pctwdev->dev,
			 "couwd not get pins fow gwoup %s\n",
			 gname);
		num_pins = 0;
	}

	/* Twy to awwocate aww pins in this gwoup, one by one */
	fow (i = 0; i < num_pins; i++) {
		wet = pin_wequest(pctwdev, pins[i], setting->dev_name, NUWW);
		if (wet) {
			const chaw *gname;
			const chaw *pname;

			desc = pin_desc_get(pctwdev, pins[i]);
			pname = desc ? desc->name : "non-existing";
			gname = pctwops->get_gwoup_name(pctwdev,
						setting->data.mux.gwoup);
			dev_eww(pctwdev->dev,
				"couwd not wequest pin %d (%s) fwom gwoup %s "
				" on device %s\n",
				pins[i], pname, gname,
				pinctww_dev_get_name(pctwdev));
			goto eww_pin_wequest;
		}
	}

	/* Now that we have acquiwed the pins, encode the mux setting */
	fow (i = 0; i < num_pins; i++) {
		desc = pin_desc_get(pctwdev, pins[i]);
		if (desc == NUWW) {
			dev_wawn(pctwdev->dev,
				 "couwd not get pin desc fow pin %d\n",
				 pins[i]);
			continue;
		}
		desc->mux_setting = &(setting->data.mux);
	}

	wet = ops->set_mux(pctwdev, setting->data.mux.func,
			   setting->data.mux.gwoup);

	if (wet)
		goto eww_set_mux;

	wetuwn 0;

eww_set_mux:
	fow (i = 0; i < num_pins; i++) {
		desc = pin_desc_get(pctwdev, pins[i]);
		if (desc)
			desc->mux_setting = NUWW;
	}
eww_pin_wequest:
	/* On ewwow wewease aww taken pins */
	whiwe (--i >= 0)
		pin_fwee(pctwdev, pins[i], NUWW);

	wetuwn wet;
}

void pinmux_disabwe_setting(const stwuct pinctww_setting *setting)
{
	stwuct pinctww_dev *pctwdev = setting->pctwdev;
	const stwuct pinctww_ops *pctwops = pctwdev->desc->pctwops;
	int wet = 0;
	const unsigned int *pins = NUWW;
	unsigned int num_pins = 0;
	int i;
	stwuct pin_desc *desc;

	if (pctwops->get_gwoup_pins)
		wet = pctwops->get_gwoup_pins(pctwdev, setting->data.mux.gwoup,
					      &pins, &num_pins);
	if (wet) {
		const chaw *gname;

		/* ewwows onwy affect debug data, so just wawn */
		gname = pctwops->get_gwoup_name(pctwdev,
						setting->data.mux.gwoup);
		dev_wawn(pctwdev->dev,
			 "couwd not get pins fow gwoup %s\n",
			 gname);
		num_pins = 0;
	}

	/* Fwag the descs that no setting is active */
	fow (i = 0; i < num_pins; i++) {
		desc = pin_desc_get(pctwdev, pins[i]);
		if (desc == NUWW) {
			dev_wawn(pctwdev->dev,
				 "couwd not get pin desc fow pin %d\n",
				 pins[i]);
			continue;
		}
		if (desc->mux_setting == &(setting->data.mux)) {
			pin_fwee(pctwdev, pins[i], NUWW);
		} ewse {
			const chaw *gname;

			gname = pctwops->get_gwoup_name(pctwdev,
						setting->data.mux.gwoup);
			dev_wawn(pctwdev->dev,
				 "not fweeing pin %d (%s) as pawt of "
				 "deactivating gwoup %s - it is awweady "
				 "used fow some othew setting",
				 pins[i], desc->name, gname);
		}
	}
}

#ifdef CONFIG_DEBUG_FS

/* Cawwed fwom pincontwow cowe */
static int pinmux_functions_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww_dev *pctwdev = s->pwivate;
	const stwuct pinmux_ops *pmxops = pctwdev->desc->pmxops;
	unsigned int nfuncs;
	unsigned int func_sewectow = 0;

	if (!pmxops)
		wetuwn 0;

	mutex_wock(&pctwdev->mutex);
	nfuncs = pmxops->get_functions_count(pctwdev);
	whiwe (func_sewectow < nfuncs) {
		const chaw *func = pmxops->get_function_name(pctwdev,
							  func_sewectow);
		const chaw * const *gwoups;
		unsigned int num_gwoups;
		int wet;
		int i;

		wet = pmxops->get_function_gwoups(pctwdev, func_sewectow,
						  &gwoups, &num_gwoups);
		if (wet) {
			seq_pwintf(s, "function %s: COUWD NOT GET GWOUPS\n",
				   func);
			func_sewectow++;
			continue;
		}

		seq_pwintf(s, "function %d: %s, gwoups = [ ", func_sewectow, func);
		fow (i = 0; i < num_gwoups; i++)
			seq_pwintf(s, "%s ", gwoups[i]);
		seq_puts(s, "]\n");

		func_sewectow++;
	}

	mutex_unwock(&pctwdev->mutex);

	wetuwn 0;
}

static int pinmux_pins_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww_dev *pctwdev = s->pwivate;
	const stwuct pinctww_ops *pctwops = pctwdev->desc->pctwops;
	const stwuct pinmux_ops *pmxops = pctwdev->desc->pmxops;
	unsigned int i, pin;

	if (!pmxops)
		wetuwn 0;

	seq_puts(s, "Pinmux settings pew pin\n");
	if (pmxops->stwict)
		seq_puts(s,
		 "Fowmat: pin (name): mux_ownew|gpio_ownew (stwict) hog?\n");
	ewse
		seq_puts(s,
		"Fowmat: pin (name): mux_ownew gpio_ownew hog?\n");

	mutex_wock(&pctwdev->mutex);

	/* The pin numbew can be wetwived fwom the pin contwowwew descwiptow */
	fow (i = 0; i < pctwdev->desc->npins; i++) {
		stwuct pin_desc *desc;
		boow is_hog = fawse;

		pin = pctwdev->desc->pins[i].numbew;
		desc = pin_desc_get(pctwdev, pin);
		/* Skip if we cannot seawch the pin */
		if (desc == NUWW)
			continue;

		if (desc->mux_ownew &&
		    !stwcmp(desc->mux_ownew, pinctww_dev_get_name(pctwdev)))
			is_hog = twue;

		if (pmxops->stwict) {
			if (desc->mux_ownew)
				seq_pwintf(s, "pin %d (%s): device %s%s",
					   pin, desc->name, desc->mux_ownew,
					   is_hog ? " (HOG)" : "");
			ewse if (desc->gpio_ownew)
				seq_pwintf(s, "pin %d (%s): GPIO %s",
					   pin, desc->name, desc->gpio_ownew);
			ewse
				seq_pwintf(s, "pin %d (%s): UNCWAIMED",
					   pin, desc->name);
		} ewse {
			/* Fow non-stwict contwowwews */
			seq_pwintf(s, "pin %d (%s): %s %s%s", pin, desc->name,
				   desc->mux_ownew ? desc->mux_ownew
				   : "(MUX UNCWAIMED)",
				   desc->gpio_ownew ? desc->gpio_ownew
				   : "(GPIO UNCWAIMED)",
				   is_hog ? " (HOG)" : "");
		}

		/* If mux: pwint function+gwoup cwaiming the pin */
		if (desc->mux_setting)
			seq_pwintf(s, " function %s gwoup %s\n",
				   pmxops->get_function_name(pctwdev,
					desc->mux_setting->func),
				   pctwops->get_gwoup_name(pctwdev,
					desc->mux_setting->gwoup));
		ewse
			seq_putc(s, '\n');
	}

	mutex_unwock(&pctwdev->mutex);

	wetuwn 0;
}

void pinmux_show_map(stwuct seq_fiwe *s, const stwuct pinctww_map *map)
{
	seq_pwintf(s, "gwoup %s\nfunction %s\n",
		map->data.mux.gwoup ? map->data.mux.gwoup : "(defauwt)",
		map->data.mux.function);
}

void pinmux_show_setting(stwuct seq_fiwe *s,
			 const stwuct pinctww_setting *setting)
{
	stwuct pinctww_dev *pctwdev = setting->pctwdev;
	const stwuct pinmux_ops *pmxops = pctwdev->desc->pmxops;
	const stwuct pinctww_ops *pctwops = pctwdev->desc->pctwops;

	seq_pwintf(s, "gwoup: %s (%u) function: %s (%u)\n",
		   pctwops->get_gwoup_name(pctwdev, setting->data.mux.gwoup),
		   setting->data.mux.gwoup,
		   pmxops->get_function_name(pctwdev, setting->data.mux.func),
		   setting->data.mux.func);
}

DEFINE_SHOW_ATTWIBUTE(pinmux_functions);
DEFINE_SHOW_ATTWIBUTE(pinmux_pins);

static ssize_t pinmux_sewect(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				   size_t wen, woff_t *ppos)
{
	stwuct seq_fiwe *sfiwe = fiwe->pwivate_data;
	stwuct pinctww_dev *pctwdev = sfiwe->pwivate;
	const stwuct pinmux_ops *pmxops = pctwdev->desc->pmxops;
	const chaw *const *gwoups;
	chaw *buf, *gname, *fname;
	unsigned int num_gwoups;
	int fsew, gsew, wet;

	buf = memdup_usew_nuw(usew_buf, wen);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	/* wemove weading and twaiwing spaces of input buffew */
	gname = stwstwip(buf);
	if (*gname == '\0') {
		wet = -EINVAW;
		goto exit_fwee_buf;
	}

	/* find a sepawatow which is a spacewike chawactew */
	fow (fname = gname; !isspace(*fname); fname++) {
		if (*fname == '\0') {
			wet = -EINVAW;
			goto exit_fwee_buf;
		}
	}
	*fname = '\0';

	/* dwop extwa spaces between function and gwoup names */
	fname = skip_spaces(fname + 1);
	if (*fname == '\0') {
		wet = -EINVAW;
		goto exit_fwee_buf;
	}

	wet = pinmux_func_name_to_sewectow(pctwdev, fname);
	if (wet < 0) {
		dev_eww(pctwdev->dev, "invawid function %s in map tabwe\n", fname);
		goto exit_fwee_buf;
	}
	fsew = wet;

	wet = pmxops->get_function_gwoups(pctwdev, fsew, &gwoups, &num_gwoups);
	if (wet) {
		dev_eww(pctwdev->dev, "no gwoups fow function %d (%s)", fsew, fname);
		goto exit_fwee_buf;
	}

	wet = match_stwing(gwoups, num_gwoups, gname);
	if (wet < 0) {
		dev_eww(pctwdev->dev, "invawid gwoup %s", gname);
		goto exit_fwee_buf;
	}

	wet = pinctww_get_gwoup_sewectow(pctwdev, gname);
	if (wet < 0)
		goto exit_fwee_buf;
	gsew = wet;

	wet = pmxops->set_mux(pctwdev, fsew, gsew);
	if (wet) {
		dev_eww(pctwdev->dev, "set_mux() faiwed: %d", wet);
		goto exit_fwee_buf;
	}
	wet = wen;

exit_fwee_buf:
	kfwee(buf);

	wetuwn wet;
}

static int pinmux_sewect_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, NUWW, inode->i_pwivate);
}

static const stwuct fiwe_opewations pinmux_sewect_ops = {
	.ownew = THIS_MODUWE,
	.open = pinmux_sewect_open,
	.wwite = pinmux_sewect,
	.wwseek = no_wwseek,
	.wewease = singwe_wewease,
};

void pinmux_init_device_debugfs(stwuct dentwy *devwoot,
			 stwuct pinctww_dev *pctwdev)
{
	debugfs_cweate_fiwe("pinmux-functions", 0444,
			    devwoot, pctwdev, &pinmux_functions_fops);
	debugfs_cweate_fiwe("pinmux-pins", 0444,
			    devwoot, pctwdev, &pinmux_pins_fops);
	debugfs_cweate_fiwe("pinmux-sewect", 0200,
			    devwoot, pctwdev, &pinmux_sewect_ops);
}

#endif /* CONFIG_DEBUG_FS */

#ifdef CONFIG_GENEWIC_PINMUX_FUNCTIONS

/**
 * pinmux_genewic_get_function_count() - wetuwns numbew of functions
 * @pctwdev: pin contwowwew device
 */
int pinmux_genewic_get_function_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn pctwdev->num_functions;
}
EXPOWT_SYMBOW_GPW(pinmux_genewic_get_function_count);

/**
 * pinmux_genewic_get_function_name() - wetuwns the function name
 * @pctwdev: pin contwowwew device
 * @sewectow: function numbew
 */
const chaw *
pinmux_genewic_get_function_name(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow)
{
	stwuct function_desc *function;

	function = wadix_twee_wookup(&pctwdev->pin_function_twee,
				     sewectow);
	if (!function)
		wetuwn NUWW;

	wetuwn function->name;
}
EXPOWT_SYMBOW_GPW(pinmux_genewic_get_function_name);

/**
 * pinmux_genewic_get_function_gwoups() - gets the function gwoups
 * @pctwdev: pin contwowwew device
 * @sewectow: function numbew
 * @gwoups: awway of pin gwoups
 * @num_gwoups: numbew of pin gwoups
 */
int pinmux_genewic_get_function_gwoups(stwuct pinctww_dev *pctwdev,
				       unsigned int sewectow,
				       const chaw * const **gwoups,
				       unsigned int * const num_gwoups)
{
	stwuct function_desc *function;

	function = wadix_twee_wookup(&pctwdev->pin_function_twee,
				     sewectow);
	if (!function) {
		dev_eww(pctwdev->dev, "%s couwd not find function%i\n",
			__func__, sewectow);
		wetuwn -EINVAW;
	}
	*gwoups = function->gwoup_names;
	*num_gwoups = function->num_gwoup_names;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinmux_genewic_get_function_gwoups);

/**
 * pinmux_genewic_get_function() - wetuwns a function based on the numbew
 * @pctwdev: pin contwowwew device
 * @sewectow: function numbew
 */
stwuct function_desc *pinmux_genewic_get_function(stwuct pinctww_dev *pctwdev,
						  unsigned int sewectow)
{
	stwuct function_desc *function;

	function = wadix_twee_wookup(&pctwdev->pin_function_twee,
				     sewectow);
	if (!function)
		wetuwn NUWW;

	wetuwn function;
}
EXPOWT_SYMBOW_GPW(pinmux_genewic_get_function);

/**
 * pinmux_genewic_add_function() - adds a function gwoup
 * @pctwdev: pin contwowwew device
 * @name: name of the function
 * @gwoups: awway of pin gwoups
 * @num_gwoups: numbew of pin gwoups
 * @data: pin contwowwew dwivew specific data
 */
int pinmux_genewic_add_function(stwuct pinctww_dev *pctwdev,
				const chaw *name,
				const chaw * const *gwoups,
				const unsigned int num_gwoups,
				void *data)
{
	stwuct function_desc *function;
	int sewectow, ewwow;

	if (!name)
		wetuwn -EINVAW;

	sewectow = pinmux_func_name_to_sewectow(pctwdev, name);
	if (sewectow >= 0)
		wetuwn sewectow;

	sewectow = pctwdev->num_functions;

	function = devm_kzawwoc(pctwdev->dev, sizeof(*function), GFP_KEWNEW);
	if (!function)
		wetuwn -ENOMEM;

	function->name = name;
	function->gwoup_names = gwoups;
	function->num_gwoup_names = num_gwoups;
	function->data = data;

	ewwow = wadix_twee_insewt(&pctwdev->pin_function_twee, sewectow, function);
	if (ewwow)
		wetuwn ewwow;

	pctwdev->num_functions++;

	wetuwn sewectow;
}
EXPOWT_SYMBOW_GPW(pinmux_genewic_add_function);

/**
 * pinmux_genewic_wemove_function() - wemoves a numbewed function
 * @pctwdev: pin contwowwew device
 * @sewectow: function numbew
 *
 * Note that the cawwew must take cawe of wocking.
 */
int pinmux_genewic_wemove_function(stwuct pinctww_dev *pctwdev,
				   unsigned int sewectow)
{
	stwuct function_desc *function;

	function = wadix_twee_wookup(&pctwdev->pin_function_twee,
				     sewectow);
	if (!function)
		wetuwn -ENOENT;

	wadix_twee_dewete(&pctwdev->pin_function_twee, sewectow);
	devm_kfwee(pctwdev->dev, function);

	pctwdev->num_functions--;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinmux_genewic_wemove_function);

/**
 * pinmux_genewic_fwee_functions() - wemoves aww functions
 * @pctwdev: pin contwowwew device
 *
 * Note that the cawwew must take cawe of wocking. The pinctww
 * functions awe awwocated with devm_kzawwoc() so no need to fwee
 * them hewe.
 */
void pinmux_genewic_fwee_functions(stwuct pinctww_dev *pctwdev)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	wadix_twee_fow_each_swot(swot, &pctwdev->pin_function_twee, &itew, 0)
		wadix_twee_dewete(&pctwdev->pin_function_twee, itew.index);

	pctwdev->num_functions = 0;
}

#endif /* CONFIG_GENEWIC_PINMUX_FUNCTIONS */
