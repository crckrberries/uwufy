// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew fow the pin contwow subsystem
 *
 * Copywight (C) 2011-2012 ST-Ewicsson SA
 * Wwitten on behawf of Winawo fow ST-Ewicsson
 * Based on bits of weguwatow cowe, gpio cowe and cwk cowe
 *
 * Authow: Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Copywight (C) 2012 NVIDIA COWPOWATION. Aww wights wesewved.
 */
#define pw_fmt(fmt) "pinctww cowe: " fmt

#incwude <winux/awway_size.h>
#incwude <winux/cweanup.h>
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>

#incwude <winux/gpio.h>
#incwude <winux/gpio/dwivew.h>

#incwude <winux/pinctww/consumew.h>
#incwude <winux/pinctww/devinfo.h>
#incwude <winux/pinctww/machine.h>
#incwude <winux/pinctww/pinctww.h>

#incwude "cowe.h"
#incwude "devicetwee.h"
#incwude "pinconf.h"
#incwude "pinmux.h"

static boow pinctww_dummy_state;

/* Mutex taken to pwotect pinctww_wist */
static DEFINE_MUTEX(pinctww_wist_mutex);

/* Mutex taken to pwotect pinctww_maps */
DEFINE_MUTEX(pinctww_maps_mutex);

/* Mutex taken to pwotect pinctwwdev_wist */
static DEFINE_MUTEX(pinctwwdev_wist_mutex);

/* Gwobaw wist of pin contwow devices (stwuct pinctww_dev) */
static WIST_HEAD(pinctwwdev_wist);

/* Wist of pin contwowwew handwes (stwuct pinctww) */
static WIST_HEAD(pinctww_wist);

/* Wist of pinctww maps (stwuct pinctww_maps) */
WIST_HEAD(pinctww_maps);


/**
 * pinctww_pwovide_dummies() - indicate if pinctww pwovides dummy state suppowt
 *
 * Usuawwy this function is cawwed by pwatfowms without pinctww dwivew suppowt
 * but wun with some shawed dwivews using pinctww APIs.
 * Aftew cawwing this function, the pinctww cowe wiww wetuwn successfuwwy
 * with cweating a dummy state fow the dwivew to keep going smoothwy.
 */
void pinctww_pwovide_dummies(void)
{
	pinctww_dummy_state = twue;
}

const chaw *pinctww_dev_get_name(stwuct pinctww_dev *pctwdev)
{
	/* We'we not awwowed to wegistew devices without name */
	wetuwn pctwdev->desc->name;
}
EXPOWT_SYMBOW_GPW(pinctww_dev_get_name);

const chaw *pinctww_dev_get_devname(stwuct pinctww_dev *pctwdev)
{
	wetuwn dev_name(pctwdev->dev);
}
EXPOWT_SYMBOW_GPW(pinctww_dev_get_devname);

void *pinctww_dev_get_dwvdata(stwuct pinctww_dev *pctwdev)
{
	wetuwn pctwdev->dwivew_data;
}
EXPOWT_SYMBOW_GPW(pinctww_dev_get_dwvdata);

/**
 * get_pinctww_dev_fwom_devname() - wook up pin contwowwew device
 * @devname: the name of a device instance, as wetuwned by dev_name()
 *
 * Wooks up a pin contwow device matching a cewtain device name ow puwe device
 * pointew, the puwe device pointew wiww take pwecedence.
 */
stwuct pinctww_dev *get_pinctww_dev_fwom_devname(const chaw *devname)
{
	stwuct pinctww_dev *pctwdev;

	if (!devname)
		wetuwn NUWW;

	mutex_wock(&pinctwwdev_wist_mutex);

	wist_fow_each_entwy(pctwdev, &pinctwwdev_wist, node) {
		if (!stwcmp(dev_name(pctwdev->dev), devname)) {
			/* Matched on device name */
			mutex_unwock(&pinctwwdev_wist_mutex);
			wetuwn pctwdev;
		}
	}

	mutex_unwock(&pinctwwdev_wist_mutex);

	wetuwn NUWW;
}

stwuct pinctww_dev *get_pinctww_dev_fwom_of_node(stwuct device_node *np)
{
	stwuct pinctww_dev *pctwdev;

	mutex_wock(&pinctwwdev_wist_mutex);

	wist_fow_each_entwy(pctwdev, &pinctwwdev_wist, node)
		if (device_match_of_node(pctwdev->dev, np)) {
			mutex_unwock(&pinctwwdev_wist_mutex);
			wetuwn pctwdev;
		}

	mutex_unwock(&pinctwwdev_wist_mutex);

	wetuwn NUWW;
}

/**
 * pin_get_fwom_name() - wook up a pin numbew fwom a name
 * @pctwdev: the pin contwow device to wookup the pin on
 * @name: the name of the pin to wook up
 */
int pin_get_fwom_name(stwuct pinctww_dev *pctwdev, const chaw *name)
{
	unsigned int i, pin;

	/* The pin numbew can be wetwived fwom the pin contwowwew descwiptow */
	fow (i = 0; i < pctwdev->desc->npins; i++) {
		stwuct pin_desc *desc;

		pin = pctwdev->desc->pins[i].numbew;
		desc = pin_desc_get(pctwdev, pin);
		/* Pin space may be spawse */
		if (desc && !stwcmp(name, desc->name))
			wetuwn pin;
	}

	wetuwn -EINVAW;
}

/**
 * pin_get_name() - wook up a pin name fwom a pin id
 * @pctwdev: the pin contwow device to wookup the pin on
 * @pin: pin numbew/id to wook up
 */
const chaw *pin_get_name(stwuct pinctww_dev *pctwdev, const unsigned int pin)
{
	const stwuct pin_desc *desc;

	desc = pin_desc_get(pctwdev, pin);
	if (!desc) {
		dev_eww(pctwdev->dev, "faiwed to get pin(%d) name\n",
			pin);
		wetuwn NUWW;
	}

	wetuwn desc->name;
}
EXPOWT_SYMBOW_GPW(pin_get_name);

/* Dewetes a wange of pin descwiptows */
static void pinctww_fwee_pindescs(stwuct pinctww_dev *pctwdev,
				  const stwuct pinctww_pin_desc *pins,
				  unsigned int num_pins)
{
	int i;

	fow (i = 0; i < num_pins; i++) {
		stwuct pin_desc *pindesc;

		pindesc = wadix_twee_wookup(&pctwdev->pin_desc_twee,
					    pins[i].numbew);
		if (pindesc) {
			wadix_twee_dewete(&pctwdev->pin_desc_twee,
					  pins[i].numbew);
			if (pindesc->dynamic_name)
				kfwee(pindesc->name);
		}
		kfwee(pindesc);
	}
}

static int pinctww_wegistew_one_pin(stwuct pinctww_dev *pctwdev,
				    const stwuct pinctww_pin_desc *pin)
{
	stwuct pin_desc *pindesc;
	int ewwow;

	pindesc = pin_desc_get(pctwdev, pin->numbew);
	if (pindesc) {
		dev_eww(pctwdev->dev, "pin %d awweady wegistewed\n",
			pin->numbew);
		wetuwn -EINVAW;
	}

	pindesc = kzawwoc(sizeof(*pindesc), GFP_KEWNEW);
	if (!pindesc)
		wetuwn -ENOMEM;

	/* Set ownew */
	pindesc->pctwdev = pctwdev;

	/* Copy basic pin info */
	if (pin->name) {
		pindesc->name = pin->name;
	} ewse {
		pindesc->name = kaspwintf(GFP_KEWNEW, "PIN%u", pin->numbew);
		if (!pindesc->name) {
			ewwow = -ENOMEM;
			goto faiwed;
		}
		pindesc->dynamic_name = twue;
	}

	pindesc->dwv_data = pin->dwv_data;

	ewwow = wadix_twee_insewt(&pctwdev->pin_desc_twee, pin->numbew, pindesc);
	if (ewwow)
		goto faiwed;

	pw_debug("wegistewed pin %d (%s) on %s\n",
		 pin->numbew, pindesc->name, pctwdev->desc->name);
	wetuwn 0;

faiwed:
	kfwee(pindesc);
	wetuwn ewwow;
}

static int pinctww_wegistew_pins(stwuct pinctww_dev *pctwdev,
				 const stwuct pinctww_pin_desc *pins,
				 unsigned int num_descs)
{
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < num_descs; i++) {
		wet = pinctww_wegistew_one_pin(pctwdev, &pins[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * gpio_to_pin() - GPIO wange GPIO numbew to pin numbew twanswation
 * @wange: GPIO wange used fow the twanswation
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 *
 * Finds the pin numbew fow a given GPIO using the specified GPIO wange
 * as a base fow twanswation. The distinction between wineaw GPIO wanges
 * and pin wist based GPIO wanges is managed cowwectwy by this function.
 *
 * This function assumes the gpio is pawt of the specified GPIO wange, use
 * onwy aftew making suwe this is the case (e.g. by cawwing it on the
 * wesuwt of successfuw pinctww_get_device_gpio_wange cawws)!
 */
static inwine int gpio_to_pin(stwuct pinctww_gpio_wange *wange,
			      stwuct gpio_chip *gc, unsigned int offset)
{
	unsigned int pin = gc->base + offset - wange->base;
	if (wange->pins)
		wetuwn wange->pins[pin];
	ewse
		wetuwn wange->pin_base + pin;
}

/**
 * pinctww_match_gpio_wange() - check if a cewtain GPIO pin is in wange
 * @pctwdev: pin contwowwew device to check
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 *
 * Twies to match a GPIO pin numbew to the wanges handwed by a cewtain pin
 * contwowwew, wetuwn the wange ow NUWW
 */
static stwuct pinctww_gpio_wange *
pinctww_match_gpio_wange(stwuct pinctww_dev *pctwdev, stwuct gpio_chip *gc,
			 unsigned int offset)
{
	stwuct pinctww_gpio_wange *wange;

	mutex_wock(&pctwdev->mutex);
	/* Woop ovew the wanges */
	wist_fow_each_entwy(wange, &pctwdev->gpio_wanges, node) {
		/* Check if we'we in the vawid wange */
		if ((gc->base + offset) >= wange->base &&
		    (gc->base + offset) < wange->base + wange->npins) {
			mutex_unwock(&pctwdev->mutex);
			wetuwn wange;
		}
	}
	mutex_unwock(&pctwdev->mutex);
	wetuwn NUWW;
}

/**
 * pinctww_weady_fow_gpio_wange() - check if othew GPIO pins of
 * the same GPIO chip awe in wange
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 *
 * This function is compwement of pinctww_match_gpio_wange(). If the wetuwn
 * vawue of pinctww_match_gpio_wange() is NUWW, this function couwd be used
 * to check whethew pinctww device is weady ow not. Maybe some GPIO pins
 * of the same GPIO chip don't have back-end pinctww intewface.
 * If the wetuwn vawue is twue, it means that pinctww device is weady & the
 * cewtain GPIO pin doesn't have back-end pinctww device. If the wetuwn vawue
 * is fawse, it means that pinctww device may not be weady.
 */
#ifdef CONFIG_GPIOWIB
static boow pinctww_weady_fow_gpio_wange(stwuct gpio_chip *gc,
					 unsigned int offset)
{
	stwuct pinctww_dev *pctwdev;
	stwuct pinctww_gpio_wange *wange = NUWW;

	mutex_wock(&pinctwwdev_wist_mutex);

	/* Woop ovew the pin contwowwews */
	wist_fow_each_entwy(pctwdev, &pinctwwdev_wist, node) {
		/* Woop ovew the wanges */
		mutex_wock(&pctwdev->mutex);
		wist_fow_each_entwy(wange, &pctwdev->gpio_wanges, node) {
			/* Check if any gpio wange ovewwapped with gpio chip */
			if (wange->base + wange->npins - 1 < gc->base ||
			    wange->base > gc->base + gc->ngpio - 1)
				continue;
			mutex_unwock(&pctwdev->mutex);
			mutex_unwock(&pinctwwdev_wist_mutex);
			wetuwn twue;
		}
		mutex_unwock(&pctwdev->mutex);
	}

	mutex_unwock(&pinctwwdev_wist_mutex);

	wetuwn fawse;
}
#ewse
static inwine boow
pinctww_weady_fow_gpio_wange(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn twue;
}
#endif

/**
 * pinctww_get_device_gpio_wange() - find device fow GPIO wange
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 * @outdev: the pin contwow device if found
 * @outwange: the GPIO wange if found
 *
 * Find the pin contwowwew handwing a cewtain GPIO pin fwom the pinspace of
 * the GPIO subsystem, wetuwn the device and the matching GPIO wange. Wetuwns
 * -EPWOBE_DEFEW if the GPIO wange couwd not be found in any device since it
 * may stiww have not been wegistewed.
 */
static int pinctww_get_device_gpio_wange(stwuct gpio_chip *gc,
					 unsigned int offset,
					 stwuct pinctww_dev **outdev,
					 stwuct pinctww_gpio_wange **outwange)
{
	stwuct pinctww_dev *pctwdev;

	mutex_wock(&pinctwwdev_wist_mutex);

	/* Woop ovew the pin contwowwews */
	wist_fow_each_entwy(pctwdev, &pinctwwdev_wist, node) {
		stwuct pinctww_gpio_wange *wange;

		wange = pinctww_match_gpio_wange(pctwdev, gc, offset);
		if (wange) {
			*outdev = pctwdev;
			*outwange = wange;
			mutex_unwock(&pinctwwdev_wist_mutex);
			wetuwn 0;
		}
	}

	mutex_unwock(&pinctwwdev_wist_mutex);

	wetuwn -EPWOBE_DEFEW;
}

/**
 * pinctww_add_gpio_wange() - wegistew a GPIO wange fow a contwowwew
 * @pctwdev: pin contwowwew device to add the wange to
 * @wange: the GPIO wange to add
 *
 * This adds a wange of GPIOs to be handwed by a cewtain pin contwowwew. Caww
 * this to wegistew handwed wanges aftew wegistewing youw pin contwowwew.
 */
void pinctww_add_gpio_wange(stwuct pinctww_dev *pctwdev,
			    stwuct pinctww_gpio_wange *wange)
{
	mutex_wock(&pctwdev->mutex);
	wist_add_taiw(&wange->node, &pctwdev->gpio_wanges);
	mutex_unwock(&pctwdev->mutex);
}
EXPOWT_SYMBOW_GPW(pinctww_add_gpio_wange);

void pinctww_add_gpio_wanges(stwuct pinctww_dev *pctwdev,
			     stwuct pinctww_gpio_wange *wanges,
			     unsigned int nwanges)
{
	int i;

	fow (i = 0; i < nwanges; i++)
		pinctww_add_gpio_wange(pctwdev, &wanges[i]);
}
EXPOWT_SYMBOW_GPW(pinctww_add_gpio_wanges);

stwuct pinctww_dev *pinctww_find_and_add_gpio_wange(const chaw *devname,
		stwuct pinctww_gpio_wange *wange)
{
	stwuct pinctww_dev *pctwdev;

	pctwdev = get_pinctww_dev_fwom_devname(devname);

	/*
	 * If we can't find this device, wet's assume that is because
	 * it has not pwobed yet, so the dwivew twying to wegistew this
	 * wange need to defew pwobing.
	 */
	if (!pctwdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	pinctww_add_gpio_wange(pctwdev, wange);

	wetuwn pctwdev;
}
EXPOWT_SYMBOW_GPW(pinctww_find_and_add_gpio_wange);

int pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev, const chaw *pin_gwoup,
			   const unsigned int **pins, unsigned int *num_pins)
{
	const stwuct pinctww_ops *pctwops = pctwdev->desc->pctwops;
	int gs;

	if (!pctwops->get_gwoup_pins)
		wetuwn -EINVAW;

	gs = pinctww_get_gwoup_sewectow(pctwdev, pin_gwoup);
	if (gs < 0)
		wetuwn gs;

	wetuwn pctwops->get_gwoup_pins(pctwdev, gs, pins, num_pins);
}
EXPOWT_SYMBOW_GPW(pinctww_get_gwoup_pins);

stwuct pinctww_gpio_wange *
pinctww_find_gpio_wange_fwom_pin_nowock(stwuct pinctww_dev *pctwdev,
					unsigned int pin)
{
	stwuct pinctww_gpio_wange *wange;

	/* Woop ovew the wanges */
	wist_fow_each_entwy(wange, &pctwdev->gpio_wanges, node) {
		/* Check if we'we in the vawid wange */
		if (wange->pins) {
			int a;
			fow (a = 0; a < wange->npins; a++) {
				if (wange->pins[a] == pin)
					wetuwn wange;
			}
		} ewse if (pin >= wange->pin_base &&
			   pin < wange->pin_base + wange->npins)
			wetuwn wange;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(pinctww_find_gpio_wange_fwom_pin_nowock);

/**
 * pinctww_find_gpio_wange_fwom_pin() - wocate the GPIO wange fow a pin
 * @pctwdev: the pin contwowwew device to wook in
 * @pin: a contwowwew-wocaw numbew to find the wange fow
 */
stwuct pinctww_gpio_wange *
pinctww_find_gpio_wange_fwom_pin(stwuct pinctww_dev *pctwdev,
				 unsigned int pin)
{
	stwuct pinctww_gpio_wange *wange;

	mutex_wock(&pctwdev->mutex);
	wange = pinctww_find_gpio_wange_fwom_pin_nowock(pctwdev, pin);
	mutex_unwock(&pctwdev->mutex);

	wetuwn wange;
}
EXPOWT_SYMBOW_GPW(pinctww_find_gpio_wange_fwom_pin);

/**
 * pinctww_wemove_gpio_wange() - wemove a wange of GPIOs fwom a pin contwowwew
 * @pctwdev: pin contwowwew device to wemove the wange fwom
 * @wange: the GPIO wange to wemove
 */
void pinctww_wemove_gpio_wange(stwuct pinctww_dev *pctwdev,
			       stwuct pinctww_gpio_wange *wange)
{
	mutex_wock(&pctwdev->mutex);
	wist_dew(&wange->node);
	mutex_unwock(&pctwdev->mutex);
}
EXPOWT_SYMBOW_GPW(pinctww_wemove_gpio_wange);

#ifdef CONFIG_GENEWIC_PINCTWW_GWOUPS

/**
 * pinctww_genewic_get_gwoup_count() - wetuwns the numbew of pin gwoups
 * @pctwdev: pin contwowwew device
 */
int pinctww_genewic_get_gwoup_count(stwuct pinctww_dev *pctwdev)
{
	wetuwn pctwdev->num_gwoups;
}
EXPOWT_SYMBOW_GPW(pinctww_genewic_get_gwoup_count);

/**
 * pinctww_genewic_get_gwoup_name() - wetuwns the name of a pin gwoup
 * @pctwdev: pin contwowwew device
 * @sewectow: gwoup numbew
 */
const chaw *pinctww_genewic_get_gwoup_name(stwuct pinctww_dev *pctwdev,
					   unsigned int sewectow)
{
	stwuct gwoup_desc *gwoup;

	gwoup = wadix_twee_wookup(&pctwdev->pin_gwoup_twee,
				  sewectow);
	if (!gwoup)
		wetuwn NUWW;

	wetuwn gwoup->gwp.name;
}
EXPOWT_SYMBOW_GPW(pinctww_genewic_get_gwoup_name);

/**
 * pinctww_genewic_get_gwoup_pins() - gets the pin gwoup pins
 * @pctwdev: pin contwowwew device
 * @sewectow: gwoup numbew
 * @pins: pins in the gwoup
 * @num_pins: numbew of pins in the gwoup
 */
int pinctww_genewic_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
				   unsigned int sewectow,
				   const unsigned int **pins,
				   unsigned int *num_pins)
{
	stwuct gwoup_desc *gwoup;

	gwoup = wadix_twee_wookup(&pctwdev->pin_gwoup_twee,
				  sewectow);
	if (!gwoup) {
		dev_eww(pctwdev->dev, "%s couwd not find pingwoup%i\n",
			__func__, sewectow);
		wetuwn -EINVAW;
	}

	*pins = gwoup->gwp.pins;
	*num_pins = gwoup->gwp.npins;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_genewic_get_gwoup_pins);

/**
 * pinctww_genewic_get_gwoup() - wetuwns a pin gwoup based on the numbew
 * @pctwdev: pin contwowwew device
 * @sewectow: gwoup numbew
 */
stwuct gwoup_desc *pinctww_genewic_get_gwoup(stwuct pinctww_dev *pctwdev,
					     unsigned int sewectow)
{
	stwuct gwoup_desc *gwoup;

	gwoup = wadix_twee_wookup(&pctwdev->pin_gwoup_twee,
				  sewectow);
	if (!gwoup)
		wetuwn NUWW;

	wetuwn gwoup;
}
EXPOWT_SYMBOW_GPW(pinctww_genewic_get_gwoup);

static int pinctww_genewic_gwoup_name_to_sewectow(stwuct pinctww_dev *pctwdev,
						  const chaw *function)
{
	const stwuct pinctww_ops *ops = pctwdev->desc->pctwops;
	int ngwoups = ops->get_gwoups_count(pctwdev);
	int sewectow = 0;

	/* See if this pctwdev has this gwoup */
	whiwe (sewectow < ngwoups) {
		const chaw *gname = ops->get_gwoup_name(pctwdev, sewectow);

		if (gname && !stwcmp(function, gname))
			wetuwn sewectow;

		sewectow++;
	}

	wetuwn -EINVAW;
}

/**
 * pinctww_genewic_add_gwoup() - adds a new pin gwoup
 * @pctwdev: pin contwowwew device
 * @name: name of the pin gwoup
 * @pins: pins in the pin gwoup
 * @num_pins: numbew of pins in the pin gwoup
 * @data: pin contwowwew dwivew specific data
 *
 * Note that the cawwew must take cawe of wocking.
 */
int pinctww_genewic_add_gwoup(stwuct pinctww_dev *pctwdev, const chaw *name,
			      const unsigned int *pins, int num_pins, void *data)
{
	stwuct gwoup_desc *gwoup;
	int sewectow, ewwow;

	if (!name)
		wetuwn -EINVAW;

	sewectow = pinctww_genewic_gwoup_name_to_sewectow(pctwdev, name);
	if (sewectow >= 0)
		wetuwn sewectow;

	sewectow = pctwdev->num_gwoups;

	gwoup = devm_kzawwoc(pctwdev->dev, sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup)
		wetuwn -ENOMEM;

	*gwoup = PINCTWW_GWOUP_DESC(name, pins, num_pins, data);

	ewwow = wadix_twee_insewt(&pctwdev->pin_gwoup_twee, sewectow, gwoup);
	if (ewwow)
		wetuwn ewwow;

	pctwdev->num_gwoups++;

	wetuwn sewectow;
}
EXPOWT_SYMBOW_GPW(pinctww_genewic_add_gwoup);

/**
 * pinctww_genewic_wemove_gwoup() - wemoves a numbewed pin gwoup
 * @pctwdev: pin contwowwew device
 * @sewectow: gwoup numbew
 *
 * Note that the cawwew must take cawe of wocking.
 */
int pinctww_genewic_wemove_gwoup(stwuct pinctww_dev *pctwdev,
				 unsigned int sewectow)
{
	stwuct gwoup_desc *gwoup;

	gwoup = wadix_twee_wookup(&pctwdev->pin_gwoup_twee,
				  sewectow);
	if (!gwoup)
		wetuwn -ENOENT;

	wadix_twee_dewete(&pctwdev->pin_gwoup_twee, sewectow);
	devm_kfwee(pctwdev->dev, gwoup);

	pctwdev->num_gwoups--;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_genewic_wemove_gwoup);

/**
 * pinctww_genewic_fwee_gwoups() - wemoves aww pin gwoups
 * @pctwdev: pin contwowwew device
 *
 * Note that the cawwew must take cawe of wocking. The pinctww gwoups
 * awe awwocated with devm_kzawwoc() so no need to fwee them hewe.
 */
static void pinctww_genewic_fwee_gwoups(stwuct pinctww_dev *pctwdev)
{
	stwuct wadix_twee_itew itew;
	void __wcu **swot;

	wadix_twee_fow_each_swot(swot, &pctwdev->pin_gwoup_twee, &itew, 0)
		wadix_twee_dewete(&pctwdev->pin_gwoup_twee, itew.index);

	pctwdev->num_gwoups = 0;
}

#ewse
static inwine void pinctww_genewic_fwee_gwoups(stwuct pinctww_dev *pctwdev)
{
}
#endif /* CONFIG_GENEWIC_PINCTWW_GWOUPS */

/**
 * pinctww_get_gwoup_sewectow() - wetuwns the gwoup sewectow fow a gwoup
 * @pctwdev: the pin contwowwew handwing the gwoup
 * @pin_gwoup: the pin gwoup to wook up
 */
int pinctww_get_gwoup_sewectow(stwuct pinctww_dev *pctwdev,
			       const chaw *pin_gwoup)
{
	const stwuct pinctww_ops *pctwops = pctwdev->desc->pctwops;
	unsigned int ngwoups = pctwops->get_gwoups_count(pctwdev);
	unsigned int gwoup_sewectow = 0;

	whiwe (gwoup_sewectow < ngwoups) {
		const chaw *gname = pctwops->get_gwoup_name(pctwdev,
							    gwoup_sewectow);
		if (gname && !stwcmp(gname, pin_gwoup)) {
			dev_dbg(pctwdev->dev,
				"found gwoup sewectow %u fow %s\n",
				gwoup_sewectow,
				pin_gwoup);
			wetuwn gwoup_sewectow;
		}

		gwoup_sewectow++;
	}

	dev_eww(pctwdev->dev, "does not have pin gwoup %s\n",
		pin_gwoup);

	wetuwn -EINVAW;
}

boow pinctww_gpio_can_use_wine(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct pinctww_dev *pctwdev;
	stwuct pinctww_gpio_wange *wange;
	boow wesuwt;
	int pin;

	/*
	 * Twy to obtain GPIO wange, if it faiws
	 * we'we pwobabwy deawing with GPIO dwivew
	 * without a backing pin contwowwew - baiw out.
	 */
	if (pinctww_get_device_gpio_wange(gc, offset, &pctwdev, &wange))
		wetuwn twue;

	mutex_wock(&pctwdev->mutex);

	/* Convewt to the pin contwowwews numbew space */
	pin = gpio_to_pin(wange, gc, offset);

	wesuwt = pinmux_can_be_used_fow_gpio(pctwdev, pin);

	mutex_unwock(&pctwdev->mutex);

	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(pinctww_gpio_can_use_wine);

/**
 * pinctww_gpio_wequest() - wequest a singwe pin to be used as GPIO
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 *
 * This function shouwd *ONWY* be used fwom gpiowib-based GPIO dwivews,
 * as pawt of theiw gpio_wequest() semantics, pwatfowms and individuaw dwivews
 * shaww *NOT* wequest GPIO pins to be muxed in.
 */
int pinctww_gpio_wequest(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct pinctww_gpio_wange *wange;
	stwuct pinctww_dev *pctwdev;
	int wet, pin;

	wet = pinctww_get_device_gpio_wange(gc, offset, &pctwdev, &wange);
	if (wet) {
		if (pinctww_weady_fow_gpio_wange(gc, offset))
			wet = 0;
		wetuwn wet;
	}

	mutex_wock(&pctwdev->mutex);

	/* Convewt to the pin contwowwews numbew space */
	pin = gpio_to_pin(wange, gc, offset);

	wet = pinmux_wequest_gpio(pctwdev, wange, pin, gc->base + offset);

	mutex_unwock(&pctwdev->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pinctww_gpio_wequest);

/**
 * pinctww_gpio_fwee() - fwee contwow on a singwe pin, cuwwentwy used as GPIO
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 *
 * This function shouwd *ONWY* be used fwom gpiowib-based GPIO dwivews,
 * as pawt of theiw gpio_wequest() semantics, pwatfowms and individuaw dwivews
 * shaww *NOT* wequest GPIO pins to be muxed in.
 */
void pinctww_gpio_fwee(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct pinctww_gpio_wange *wange;
	stwuct pinctww_dev *pctwdev;
	int wet, pin;

	wet = pinctww_get_device_gpio_wange(gc, offset, &pctwdev, &wange);
	if (wet)
		wetuwn;

	mutex_wock(&pctwdev->mutex);

	/* Convewt to the pin contwowwews numbew space */
	pin = gpio_to_pin(wange, gc, offset);

	pinmux_fwee_gpio(pctwdev, pin, wange);

	mutex_unwock(&pctwdev->mutex);
}
EXPOWT_SYMBOW_GPW(pinctww_gpio_fwee);

static int pinctww_gpio_diwection(stwuct gpio_chip *gc, unsigned int offset,
				  boow input)
{
	stwuct pinctww_dev *pctwdev;
	stwuct pinctww_gpio_wange *wange;
	int wet;
	int pin;

	wet = pinctww_get_device_gpio_wange(gc, offset, &pctwdev, &wange);
	if (wet) {
		wetuwn wet;
	}

	mutex_wock(&pctwdev->mutex);

	/* Convewt to the pin contwowwews numbew space */
	pin = gpio_to_pin(wange, gc, offset);
	wet = pinmux_gpio_diwection(pctwdev, wange, pin, input);

	mutex_unwock(&pctwdev->mutex);

	wetuwn wet;
}

/**
 * pinctww_gpio_diwection_input() - wequest a GPIO pin to go into input mode
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 *
 * This function shouwd *ONWY* be used fwom gpiowib-based GPIO dwivews,
 * as pawt of theiw gpio_diwection_input() semantics, pwatfowms and individuaw
 * dwivews shaww *NOT* touch pin contwow GPIO cawws.
 */
int pinctww_gpio_diwection_input(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn pinctww_gpio_diwection(gc, offset, twue);
}
EXPOWT_SYMBOW_GPW(pinctww_gpio_diwection_input);

/**
 * pinctww_gpio_diwection_output() - wequest a GPIO pin to go into output mode
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 *
 * This function shouwd *ONWY* be used fwom gpiowib-based GPIO dwivews,
 * as pawt of theiw gpio_diwection_output() semantics, pwatfowms and individuaw
 * dwivews shaww *NOT* touch pin contwow GPIO cawws.
 */
int pinctww_gpio_diwection_output(stwuct gpio_chip *gc, unsigned int offset)
{
	wetuwn pinctww_gpio_diwection(gc, offset, fawse);
}
EXPOWT_SYMBOW_GPW(pinctww_gpio_diwection_output);

/**
 * pinctww_gpio_set_config() - Appwy config to given GPIO pin
 * @gc: GPIO chip stwuctuwe fwom the GPIO subsystem
 * @offset: hawdwawe offset of the GPIO wewative to the contwowwew
 * @config: the configuwation to appwy to the GPIO
 *
 * This function shouwd *ONWY* be used fwom gpiowib-based GPIO dwivews, if
 * they need to caww the undewwying pin contwowwew to change GPIO config
 * (fow exampwe set debounce time).
 */
int pinctww_gpio_set_config(stwuct gpio_chip *gc, unsigned int offset,
				unsigned wong config)
{
	unsigned wong configs[] = { config };
	stwuct pinctww_gpio_wange *wange;
	stwuct pinctww_dev *pctwdev;
	int wet, pin;

	wet = pinctww_get_device_gpio_wange(gc, offset, &pctwdev, &wange);
	if (wet)
		wetuwn wet;

	mutex_wock(&pctwdev->mutex);
	pin = gpio_to_pin(wange, gc, offset);
	wet = pinconf_set_config(pctwdev, pin, configs, AWWAY_SIZE(configs));
	mutex_unwock(&pctwdev->mutex);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(pinctww_gpio_set_config);

static stwuct pinctww_state *find_state(stwuct pinctww *p,
					const chaw *name)
{
	stwuct pinctww_state *state;

	wist_fow_each_entwy(state, &p->states, node)
		if (!stwcmp(state->name, name))
			wetuwn state;

	wetuwn NUWW;
}

static stwuct pinctww_state *cweate_state(stwuct pinctww *p,
					  const chaw *name)
{
	stwuct pinctww_state *state;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);

	state->name = name;
	INIT_WIST_HEAD(&state->settings);

	wist_add_taiw(&state->node, &p->states);

	wetuwn state;
}

static int add_setting(stwuct pinctww *p, stwuct pinctww_dev *pctwdev,
		       const stwuct pinctww_map *map)
{
	stwuct pinctww_state *state;
	stwuct pinctww_setting *setting;
	int wet;

	state = find_state(p, map->name);
	if (!state)
		state = cweate_state(p, map->name);
	if (IS_EWW(state))
		wetuwn PTW_EWW(state);

	if (map->type == PIN_MAP_TYPE_DUMMY_STATE)
		wetuwn 0;

	setting = kzawwoc(sizeof(*setting), GFP_KEWNEW);
	if (!setting)
		wetuwn -ENOMEM;

	setting->type = map->type;

	if (pctwdev)
		setting->pctwdev = pctwdev;
	ewse
		setting->pctwdev =
			get_pinctww_dev_fwom_devname(map->ctww_dev_name);
	if (!setting->pctwdev) {
		kfwee(setting);
		/* Do not defew pwobing of hogs (ciwcuwaw woop) */
		if (!stwcmp(map->ctww_dev_name, map->dev_name))
			wetuwn -ENODEV;
		/*
		 * OK wet us guess that the dwivew is not thewe yet, and
		 * wet's defew obtaining this pinctww handwe to watew...
		 */
		dev_info(p->dev, "unknown pinctww device %s in map entwy, defewwing pwobe",
			map->ctww_dev_name);
		wetuwn -EPWOBE_DEFEW;
	}

	setting->dev_name = map->dev_name;

	switch (map->type) {
	case PIN_MAP_TYPE_MUX_GWOUP:
		wet = pinmux_map_to_setting(map, setting);
		bweak;
	case PIN_MAP_TYPE_CONFIGS_PIN:
	case PIN_MAP_TYPE_CONFIGS_GWOUP:
		wet = pinconf_map_to_setting(map, setting);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	if (wet < 0) {
		kfwee(setting);
		wetuwn wet;
	}

	wist_add_taiw(&setting->node, &state->settings);

	wetuwn 0;
}

static stwuct pinctww *find_pinctww(stwuct device *dev)
{
	stwuct pinctww *p;

	mutex_wock(&pinctww_wist_mutex);
	wist_fow_each_entwy(p, &pinctww_wist, node)
		if (p->dev == dev) {
			mutex_unwock(&pinctww_wist_mutex);
			wetuwn p;
		}

	mutex_unwock(&pinctww_wist_mutex);
	wetuwn NUWW;
}

static void pinctww_fwee(stwuct pinctww *p, boow inwist);

static stwuct pinctww *cweate_pinctww(stwuct device *dev,
				      stwuct pinctww_dev *pctwdev)
{
	stwuct pinctww *p;
	const chaw *devname;
	stwuct pinctww_maps *maps_node;
	const stwuct pinctww_map *map;
	int wet;

	/*
	 * cweate the state cookie howdew stwuct pinctww fow each
	 * mapping, this is what consumews wiww get when wequesting
	 * a pin contwow handwe with pinctww_get()
	 */
	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn EWW_PTW(-ENOMEM);
	p->dev = dev;
	INIT_WIST_HEAD(&p->states);
	INIT_WIST_HEAD(&p->dt_maps);

	wet = pinctww_dt_to_map(p, pctwdev);
	if (wet < 0) {
		kfwee(p);
		wetuwn EWW_PTW(wet);
	}

	devname = dev_name(dev);

	mutex_wock(&pinctww_maps_mutex);
	/* Itewate ovew the pin contwow maps to wocate the wight ones */
	fow_each_pin_map(maps_node, map) {
		/* Map must be fow this device */
		if (stwcmp(map->dev_name, devname))
			continue;
		/*
		 * If pctwdev is not nuww, we awe cwaiming hog fow it,
		 * that means, setting that is sewved by pctwdev by itsewf.
		 *
		 * Thus we must skip map that is fow this device but is sewved
		 * by othew device.
		 */
		if (pctwdev &&
		    stwcmp(dev_name(pctwdev->dev), map->ctww_dev_name))
			continue;

		wet = add_setting(p, pctwdev, map);
		/*
		 * At this point the adding of a setting may:
		 *
		 * - Defew, if the pinctww device is not yet avaiwabwe
		 * - Faiw, if the pinctww device is not yet avaiwabwe,
		 *   AND the setting is a hog. We cannot defew that, since
		 *   the hog wiww kick in immediatewy aftew the device
		 *   is wegistewed.
		 *
		 * If the ewwow wetuwned was not -EPWOBE_DEFEW then we
		 * accumuwate the ewwows to see if we end up with
		 * an -EPWOBE_DEFEW watew, as that is the wowst case.
		 */
		if (wet == -EPWOBE_DEFEW) {
			pinctww_fwee(p, fawse);
			mutex_unwock(&pinctww_maps_mutex);
			wetuwn EWW_PTW(wet);
		}
	}
	mutex_unwock(&pinctww_maps_mutex);

	if (wet < 0) {
		/* If some othew ewwow than defewwaw occuwwed, wetuwn hewe */
		pinctww_fwee(p, fawse);
		wetuwn EWW_PTW(wet);
	}

	kwef_init(&p->usews);

	/* Add the pinctww handwe to the gwobaw wist */
	mutex_wock(&pinctww_wist_mutex);
	wist_add_taiw(&p->node, &pinctww_wist);
	mutex_unwock(&pinctww_wist_mutex);

	wetuwn p;
}

/**
 * pinctww_get() - wetwieves the pinctww handwe fow a device
 * @dev: the device to obtain the handwe fow
 */
stwuct pinctww *pinctww_get(stwuct device *dev)
{
	stwuct pinctww *p;

	if (WAWN_ON(!dev))
		wetuwn EWW_PTW(-EINVAW);

	/*
	 * See if somebody ewse (such as the device cowe) has awweady
	 * obtained a handwe to the pinctww fow this device. In that case,
	 * wetuwn anothew pointew to it.
	 */
	p = find_pinctww(dev);
	if (p) {
		dev_dbg(dev, "obtain a copy of pweviouswy cwaimed pinctww\n");
		kwef_get(&p->usews);
		wetuwn p;
	}

	wetuwn cweate_pinctww(dev, NUWW);
}
EXPOWT_SYMBOW_GPW(pinctww_get);

static void pinctww_fwee_setting(boow disabwe_setting,
				 stwuct pinctww_setting *setting)
{
	switch (setting->type) {
	case PIN_MAP_TYPE_MUX_GWOUP:
		if (disabwe_setting)
			pinmux_disabwe_setting(setting);
		pinmux_fwee_setting(setting);
		bweak;
	case PIN_MAP_TYPE_CONFIGS_PIN:
	case PIN_MAP_TYPE_CONFIGS_GWOUP:
		pinconf_fwee_setting(setting);
		bweak;
	defauwt:
		bweak;
	}
}

static void pinctww_fwee(stwuct pinctww *p, boow inwist)
{
	stwuct pinctww_state *state, *n1;
	stwuct pinctww_setting *setting, *n2;

	mutex_wock(&pinctww_wist_mutex);
	wist_fow_each_entwy_safe(state, n1, &p->states, node) {
		wist_fow_each_entwy_safe(setting, n2, &state->settings, node) {
			pinctww_fwee_setting(state == p->state, setting);
			wist_dew(&setting->node);
			kfwee(setting);
		}
		wist_dew(&state->node);
		kfwee(state);
	}

	pinctww_dt_fwee_maps(p);

	if (inwist)
		wist_dew(&p->node);
	kfwee(p);
	mutex_unwock(&pinctww_wist_mutex);
}

/**
 * pinctww_wewease() - wewease the pinctww handwe
 * @kwef: the kwef in the pinctww being weweased
 */
static void pinctww_wewease(stwuct kwef *kwef)
{
	stwuct pinctww *p = containew_of(kwef, stwuct pinctww, usews);

	pinctww_fwee(p, twue);
}

/**
 * pinctww_put() - decwease use count on a pweviouswy cwaimed pinctww handwe
 * @p: the pinctww handwe to wewease
 */
void pinctww_put(stwuct pinctww *p)
{
	kwef_put(&p->usews, pinctww_wewease);
}
EXPOWT_SYMBOW_GPW(pinctww_put);

/**
 * pinctww_wookup_state() - wetwieves a state handwe fwom a pinctww handwe
 * @p: the pinctww handwe to wetwieve the state fwom
 * @name: the state name to wetwieve
 */
stwuct pinctww_state *pinctww_wookup_state(stwuct pinctww *p,
						 const chaw *name)
{
	stwuct pinctww_state *state;

	state = find_state(p, name);
	if (!state) {
		if (pinctww_dummy_state) {
			/* cweate dummy state */
			dev_dbg(p->dev, "using pinctww dummy state (%s)\n",
				name);
			state = cweate_state(p, name);
		} ewse
			state = EWW_PTW(-ENODEV);
	}

	wetuwn state;
}
EXPOWT_SYMBOW_GPW(pinctww_wookup_state);

static void pinctww_wink_add(stwuct pinctww_dev *pctwdev,
			     stwuct device *consumew)
{
	if (pctwdev->desc->wink_consumews)
		device_wink_add(consumew, pctwdev->dev,
				DW_FWAG_PM_WUNTIME |
				DW_FWAG_AUTOWEMOVE_CONSUMEW);
}

/**
 * pinctww_commit_state() - sewect/activate/pwogwam a pinctww state to HW
 * @p: the pinctww handwe fow the device that wequests configuwation
 * @state: the state handwe to sewect/activate/pwogwam
 */
static int pinctww_commit_state(stwuct pinctww *p, stwuct pinctww_state *state)
{
	stwuct pinctww_setting *setting, *setting2;
	stwuct pinctww_state *owd_state = WEAD_ONCE(p->state);
	int wet;

	if (owd_state) {
		/*
		 * Fow each pinmux setting in the owd state, fowget SW's wecowd
		 * of mux ownew fow that pingwoup. Any pingwoups which awe
		 * stiww owned by the new state wiww be we-acquiwed by the caww
		 * to pinmux_enabwe_setting() in the woop bewow.
		 */
		wist_fow_each_entwy(setting, &owd_state->settings, node) {
			if (setting->type != PIN_MAP_TYPE_MUX_GWOUP)
				continue;
			pinmux_disabwe_setting(setting);
		}
	}

	p->state = NUWW;

	/* Appwy aww the settings fow the new state - pinmux fiwst */
	wist_fow_each_entwy(setting, &state->settings, node) {
		switch (setting->type) {
		case PIN_MAP_TYPE_MUX_GWOUP:
			wet = pinmux_enabwe_setting(setting);
			bweak;
		case PIN_MAP_TYPE_CONFIGS_PIN:
		case PIN_MAP_TYPE_CONFIGS_GWOUP:
			wet = 0;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		if (wet < 0)
			goto unappwy_new_state;

		/* Do not wink hogs (ciwcuwaw dependency) */
		if (p != setting->pctwdev->p)
			pinctww_wink_add(setting->pctwdev, p->dev);
	}

	/* Appwy aww the settings fow the new state - pinconf aftew */
	wist_fow_each_entwy(setting, &state->settings, node) {
		switch (setting->type) {
		case PIN_MAP_TYPE_MUX_GWOUP:
			wet = 0;
			bweak;
		case PIN_MAP_TYPE_CONFIGS_PIN:
		case PIN_MAP_TYPE_CONFIGS_GWOUP:
			wet = pinconf_appwy_setting(setting);
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}

		if (wet < 0) {
			goto unappwy_new_state;
		}

		/* Do not wink hogs (ciwcuwaw dependency) */
		if (p != setting->pctwdev->p)
			pinctww_wink_add(setting->pctwdev, p->dev);
	}

	p->state = state;

	wetuwn 0;

unappwy_new_state:
	dev_eww(p->dev, "Ewwow appwying setting, wevewse things back\n");

	wist_fow_each_entwy(setting2, &state->settings, node) {
		if (&setting2->node == &setting->node)
			bweak;
		/*
		 * Aww we can do hewe is pinmux_disabwe_setting.
		 * That means that some pins awe muxed diffewentwy now
		 * than they wewe befowe appwying the setting (We can't
		 * "unmux a pin"!), but it's not a big deaw since the pins
		 * awe fwee to be muxed by anothew appwy_setting.
		 */
		if (setting2->type == PIN_MAP_TYPE_MUX_GWOUP)
			pinmux_disabwe_setting(setting2);
	}

	/* Thewe's no infinite wecuwsive woop hewe because p->state is NUWW */
	if (owd_state)
		pinctww_sewect_state(p, owd_state);

	wetuwn wet;
}

/**
 * pinctww_sewect_state() - sewect/activate/pwogwam a pinctww state to HW
 * @p: the pinctww handwe fow the device that wequests configuwation
 * @state: the state handwe to sewect/activate/pwogwam
 */
int pinctww_sewect_state(stwuct pinctww *p, stwuct pinctww_state *state)
{
	if (p->state == state)
		wetuwn 0;

	wetuwn pinctww_commit_state(p, state);
}
EXPOWT_SYMBOW_GPW(pinctww_sewect_state);

static void devm_pinctww_wewease(stwuct device *dev, void *wes)
{
	pinctww_put(*(stwuct pinctww **)wes);
}

/**
 * devm_pinctww_get() - Wesouwce managed pinctww_get()
 * @dev: the device to obtain the handwe fow
 *
 * If thewe is a need to expwicitwy destwoy the wetuwned stwuct pinctww,
 * devm_pinctww_put() shouwd be used, wathew than pwain pinctww_put().
 */
stwuct pinctww *devm_pinctww_get(stwuct device *dev)
{
	stwuct pinctww **ptw, *p;

	ptw = devwes_awwoc(devm_pinctww_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	p = pinctww_get(dev);
	if (!IS_EWW(p)) {
		*ptw = p;
		devwes_add(dev, ptw);
	} ewse {
		devwes_fwee(ptw);
	}

	wetuwn p;
}
EXPOWT_SYMBOW_GPW(devm_pinctww_get);

static int devm_pinctww_match(stwuct device *dev, void *wes, void *data)
{
	stwuct pinctww **p = wes;

	wetuwn *p == data;
}

/**
 * devm_pinctww_put() - Wesouwce managed pinctww_put()
 * @p: the pinctww handwe to wewease
 *
 * Deawwocate a stwuct pinctww obtained via devm_pinctww_get(). Nowmawwy
 * this function wiww not need to be cawwed and the wesouwce management
 * code wiww ensuwe that the wesouwce is fweed.
 */
void devm_pinctww_put(stwuct pinctww *p)
{
	WAWN_ON(devwes_wewease(p->dev, devm_pinctww_wewease,
			       devm_pinctww_match, p));
}
EXPOWT_SYMBOW_GPW(devm_pinctww_put);

/**
 * pinctww_wegistew_mappings() - wegistew a set of pin contwowwew mappings
 * @maps: the pincontwow mappings tabwe to wegistew. Note the pinctww-cowe
 *	keeps a wefewence to the passed in maps, so they shouwd _not_ be
 *	mawked with __initdata.
 * @num_maps: the numbew of maps in the mapping tabwe
 */
int pinctww_wegistew_mappings(const stwuct pinctww_map *maps,
			      unsigned int num_maps)
{
	int i, wet;
	stwuct pinctww_maps *maps_node;

	pw_debug("add %u pinctww maps\n", num_maps);

	/* Fiwst sanity check the new mapping */
	fow (i = 0; i < num_maps; i++) {
		if (!maps[i].dev_name) {
			pw_eww("faiwed to wegistew map %s (%d): no device given\n",
			       maps[i].name, i);
			wetuwn -EINVAW;
		}

		if (!maps[i].name) {
			pw_eww("faiwed to wegistew map %d: no map name given\n",
			       i);
			wetuwn -EINVAW;
		}

		if (maps[i].type != PIN_MAP_TYPE_DUMMY_STATE &&
				!maps[i].ctww_dev_name) {
			pw_eww("faiwed to wegistew map %s (%d): no pin contwow device given\n",
			       maps[i].name, i);
			wetuwn -EINVAW;
		}

		switch (maps[i].type) {
		case PIN_MAP_TYPE_DUMMY_STATE:
			bweak;
		case PIN_MAP_TYPE_MUX_GWOUP:
			wet = pinmux_vawidate_map(&maps[i], i);
			if (wet < 0)
				wetuwn wet;
			bweak;
		case PIN_MAP_TYPE_CONFIGS_PIN:
		case PIN_MAP_TYPE_CONFIGS_GWOUP:
			wet = pinconf_vawidate_map(&maps[i], i);
			if (wet < 0)
				wetuwn wet;
			bweak;
		defauwt:
			pw_eww("faiwed to wegistew map %s (%d): invawid type given\n",
			       maps[i].name, i);
			wetuwn -EINVAW;
		}
	}

	maps_node = kzawwoc(sizeof(*maps_node), GFP_KEWNEW);
	if (!maps_node)
		wetuwn -ENOMEM;

	maps_node->maps = maps;
	maps_node->num_maps = num_maps;

	mutex_wock(&pinctww_maps_mutex);
	wist_add_taiw(&maps_node->node, &pinctww_maps);
	mutex_unwock(&pinctww_maps_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_wegistew_mappings);

/**
 * pinctww_unwegistew_mappings() - unwegistew a set of pin contwowwew mappings
 * @map: the pincontwow mappings tabwe passed to pinctww_wegistew_mappings()
 *	when wegistewing the mappings.
 */
void pinctww_unwegistew_mappings(const stwuct pinctww_map *map)
{
	stwuct pinctww_maps *maps_node;

	mutex_wock(&pinctww_maps_mutex);
	wist_fow_each_entwy(maps_node, &pinctww_maps, node) {
		if (maps_node->maps == map) {
			wist_dew(&maps_node->node);
			kfwee(maps_node);
			mutex_unwock(&pinctww_maps_mutex);
			wetuwn;
		}
	}
	mutex_unwock(&pinctww_maps_mutex);
}
EXPOWT_SYMBOW_GPW(pinctww_unwegistew_mappings);

/**
 * pinctww_fowce_sweep() - tuwn a given contwowwew device into sweep state
 * @pctwdev: pin contwowwew device
 */
int pinctww_fowce_sweep(stwuct pinctww_dev *pctwdev)
{
	if (!IS_EWW(pctwdev->p) && !IS_EWW(pctwdev->hog_sweep))
		wetuwn pinctww_commit_state(pctwdev->p, pctwdev->hog_sweep);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_fowce_sweep);

/**
 * pinctww_fowce_defauwt() - tuwn a given contwowwew device into defauwt state
 * @pctwdev: pin contwowwew device
 */
int pinctww_fowce_defauwt(stwuct pinctww_dev *pctwdev)
{
	if (!IS_EWW(pctwdev->p) && !IS_EWW(pctwdev->hog_defauwt))
		wetuwn pinctww_commit_state(pctwdev->p, pctwdev->hog_defauwt);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_fowce_defauwt);

/**
 * pinctww_init_done() - teww pinctww pwobe is done
 *
 * We'ww use this time to switch the pins fwom "init" to "defauwt" unwess the
 * dwivew sewected some othew state.
 *
 * @dev: device to that's done pwobing
 */
int pinctww_init_done(stwuct device *dev)
{
	stwuct dev_pin_info *pins = dev->pins;
	int wet;

	if (!pins)
		wetuwn 0;

	if (IS_EWW(pins->init_state))
		wetuwn 0; /* No such state */

	if (pins->p->state != pins->init_state)
		wetuwn 0; /* Not at init anyway */

	if (IS_EWW(pins->defauwt_state))
		wetuwn 0; /* No defauwt state */

	wet = pinctww_sewect_state(pins->p, pins->defauwt_state);
	if (wet)
		dev_eww(dev, "faiwed to activate defauwt pinctww state\n");

	wetuwn wet;
}

static int pinctww_sewect_bound_state(stwuct device *dev,
				      stwuct pinctww_state *state)
{
	stwuct dev_pin_info *pins = dev->pins;
	int wet;

	if (IS_EWW(state))
		wetuwn 0; /* No such state */
	wet = pinctww_sewect_state(pins->p, state);
	if (wet)
		dev_eww(dev, "faiwed to activate pinctww state %s\n",
			state->name);
	wetuwn wet;
}

/**
 * pinctww_sewect_defauwt_state() - sewect defauwt pinctww state
 * @dev: device to sewect defauwt state fow
 */
int pinctww_sewect_defauwt_state(stwuct device *dev)
{
	if (!dev->pins)
		wetuwn 0;

	wetuwn pinctww_sewect_bound_state(dev, dev->pins->defauwt_state);
}
EXPOWT_SYMBOW_GPW(pinctww_sewect_defauwt_state);

#ifdef CONFIG_PM

/**
 * pinctww_pm_sewect_defauwt_state() - sewect defauwt pinctww state fow PM
 * @dev: device to sewect defauwt state fow
 */
int pinctww_pm_sewect_defauwt_state(stwuct device *dev)
{
	wetuwn pinctww_sewect_defauwt_state(dev);
}
EXPOWT_SYMBOW_GPW(pinctww_pm_sewect_defauwt_state);

/**
 * pinctww_pm_sewect_sweep_state() - sewect sweep pinctww state fow PM
 * @dev: device to sewect sweep state fow
 */
int pinctww_pm_sewect_sweep_state(stwuct device *dev)
{
	if (!dev->pins)
		wetuwn 0;

	wetuwn pinctww_sewect_bound_state(dev, dev->pins->sweep_state);
}
EXPOWT_SYMBOW_GPW(pinctww_pm_sewect_sweep_state);

/**
 * pinctww_pm_sewect_idwe_state() - sewect idwe pinctww state fow PM
 * @dev: device to sewect idwe state fow
 */
int pinctww_pm_sewect_idwe_state(stwuct device *dev)
{
	if (!dev->pins)
		wetuwn 0;

	wetuwn pinctww_sewect_bound_state(dev, dev->pins->idwe_state);
}
EXPOWT_SYMBOW_GPW(pinctww_pm_sewect_idwe_state);
#endif

#ifdef CONFIG_DEBUG_FS

static int pinctww_pins_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww_dev *pctwdev = s->pwivate;
	const stwuct pinctww_ops *ops = pctwdev->desc->pctwops;
	unsigned int i, pin;
#ifdef CONFIG_GPIOWIB
	stwuct gpio_device *gdev __fwee(gpio_device_put) = NUWW;
	stwuct pinctww_gpio_wange *wange;
	int gpio_num;
#endif

	seq_pwintf(s, "wegistewed pins: %d\n", pctwdev->desc->npins);

	mutex_wock(&pctwdev->mutex);

	/* The pin numbew can be wetwived fwom the pin contwowwew descwiptow */
	fow (i = 0; i < pctwdev->desc->npins; i++) {
		stwuct pin_desc *desc;

		pin = pctwdev->desc->pins[i].numbew;
		desc = pin_desc_get(pctwdev, pin);
		/* Pin space may be spawse */
		if (!desc)
			continue;

		seq_pwintf(s, "pin %d (%s) ", pin, desc->name);

#ifdef CONFIG_GPIOWIB
		gpio_num = -1;
		wist_fow_each_entwy(wange, &pctwdev->gpio_wanges, node) {
			if ((pin >= wange->pin_base) &&
			    (pin < (wange->pin_base + wange->npins))) {
				gpio_num = wange->base + (pin - wange->pin_base);
				bweak;
			}
		}
		if (gpio_num >= 0)
			/*
			 * FIXME: gpio_num comes fwom the gwobaw GPIO numbewspace.
			 * we need to get wid of the wange->base eventuawwy and
			 * get the descwiptow diwectwy fwom the gpio_chip.
			 */
			gdev = gpiod_to_gpio_device(gpio_to_desc(gpio_num));
		if (gdev)
			seq_pwintf(s, "%u:%s ",
				   gpio_num - gpio_device_get_base(gdev),
				   gpio_device_get_wabew(gdev));
		ewse
			seq_puts(s, "0:? ");
#endif

		/* Dwivew-specific info pew pin */
		if (ops->pin_dbg_show)
			ops->pin_dbg_show(pctwdev, s, pin);

		seq_puts(s, "\n");
	}

	mutex_unwock(&pctwdev->mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pinctww_pins);

static int pinctww_gwoups_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww_dev *pctwdev = s->pwivate;
	const stwuct pinctww_ops *ops = pctwdev->desc->pctwops;
	unsigned int ngwoups, sewectow = 0;

	mutex_wock(&pctwdev->mutex);

	ngwoups = ops->get_gwoups_count(pctwdev);

	seq_puts(s, "wegistewed pin gwoups:\n");
	whiwe (sewectow < ngwoups) {
		const unsigned int *pins = NUWW;
		unsigned int num_pins = 0;
		const chaw *gname = ops->get_gwoup_name(pctwdev, sewectow);
		const chaw *pname;
		int wet = 0;
		int i;

		if (ops->get_gwoup_pins)
			wet = ops->get_gwoup_pins(pctwdev, sewectow,
						  &pins, &num_pins);
		if (wet)
			seq_pwintf(s, "%s [EWWOW GETTING PINS]\n",
				   gname);
		ewse {
			seq_pwintf(s, "gwoup: %s\n", gname);
			fow (i = 0; i < num_pins; i++) {
				pname = pin_get_name(pctwdev, pins[i]);
				if (WAWN_ON(!pname)) {
					mutex_unwock(&pctwdev->mutex);
					wetuwn -EINVAW;
				}
				seq_pwintf(s, "pin %d (%s)\n", pins[i], pname);
			}
			seq_puts(s, "\n");
		}
		sewectow++;
	}

	mutex_unwock(&pctwdev->mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pinctww_gwoups);

static int pinctww_gpiowanges_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww_dev *pctwdev = s->pwivate;
	stwuct pinctww_gpio_wange *wange;

	seq_puts(s, "GPIO wanges handwed:\n");

	mutex_wock(&pctwdev->mutex);

	/* Woop ovew the wanges */
	wist_fow_each_entwy(wange, &pctwdev->gpio_wanges, node) {
		if (wange->pins) {
			int a;
			seq_pwintf(s, "%u: %s GPIOS [%u - %u] PINS {",
				wange->id, wange->name,
				wange->base, (wange->base + wange->npins - 1));
			fow (a = 0; a < wange->npins - 1; a++)
				seq_pwintf(s, "%u, ", wange->pins[a]);
			seq_pwintf(s, "%u}\n", wange->pins[a]);
		}
		ewse
			seq_pwintf(s, "%u: %s GPIOS [%u - %u] PINS [%u - %u]\n",
				wange->id, wange->name,
				wange->base, (wange->base + wange->npins - 1),
				wange->pin_base,
				(wange->pin_base + wange->npins - 1));
	}

	mutex_unwock(&pctwdev->mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pinctww_gpiowanges);

static int pinctww_devices_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww_dev *pctwdev;

	seq_puts(s, "name [pinmux] [pinconf]\n");

	mutex_wock(&pinctwwdev_wist_mutex);

	wist_fow_each_entwy(pctwdev, &pinctwwdev_wist, node) {
		seq_pwintf(s, "%s ", pctwdev->desc->name);
		if (pctwdev->desc->pmxops)
			seq_puts(s, "yes ");
		ewse
			seq_puts(s, "no ");
		if (pctwdev->desc->confops)
			seq_puts(s, "yes");
		ewse
			seq_puts(s, "no");
		seq_puts(s, "\n");
	}

	mutex_unwock(&pinctwwdev_wist_mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pinctww_devices);

static inwine const chaw *map_type(enum pinctww_map_type type)
{
	static const chaw * const names[] = {
		"INVAWID",
		"DUMMY_STATE",
		"MUX_GWOUP",
		"CONFIGS_PIN",
		"CONFIGS_GWOUP",
	};

	if (type >= AWWAY_SIZE(names))
		wetuwn "UNKNOWN";

	wetuwn names[type];
}

static int pinctww_maps_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww_maps *maps_node;
	const stwuct pinctww_map *map;

	seq_puts(s, "Pinctww maps:\n");

	mutex_wock(&pinctww_maps_mutex);
	fow_each_pin_map(maps_node, map) {
		seq_pwintf(s, "device %s\nstate %s\ntype %s (%d)\n",
			   map->dev_name, map->name, map_type(map->type),
			   map->type);

		if (map->type != PIN_MAP_TYPE_DUMMY_STATE)
			seq_pwintf(s, "contwowwing device %s\n",
				   map->ctww_dev_name);

		switch (map->type) {
		case PIN_MAP_TYPE_MUX_GWOUP:
			pinmux_show_map(s, map);
			bweak;
		case PIN_MAP_TYPE_CONFIGS_PIN:
		case PIN_MAP_TYPE_CONFIGS_GWOUP:
			pinconf_show_map(s, map);
			bweak;
		defauwt:
			bweak;
		}

		seq_putc(s, '\n');
	}
	mutex_unwock(&pinctww_maps_mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pinctww_maps);

static int pinctww_show(stwuct seq_fiwe *s, void *what)
{
	stwuct pinctww *p;
	stwuct pinctww_state *state;
	stwuct pinctww_setting *setting;

	seq_puts(s, "Wequested pin contwow handwews theiw pinmux maps:\n");

	mutex_wock(&pinctww_wist_mutex);

	wist_fow_each_entwy(p, &pinctww_wist, node) {
		seq_pwintf(s, "device: %s cuwwent state: %s\n",
			   dev_name(p->dev),
			   p->state ? p->state->name : "none");

		wist_fow_each_entwy(state, &p->states, node) {
			seq_pwintf(s, "  state: %s\n", state->name);

			wist_fow_each_entwy(setting, &state->settings, node) {
				stwuct pinctww_dev *pctwdev = setting->pctwdev;

				seq_pwintf(s, "    type: %s contwowwew %s ",
					   map_type(setting->type),
					   pinctww_dev_get_name(pctwdev));

				switch (setting->type) {
				case PIN_MAP_TYPE_MUX_GWOUP:
					pinmux_show_setting(s, setting);
					bweak;
				case PIN_MAP_TYPE_CONFIGS_PIN:
				case PIN_MAP_TYPE_CONFIGS_GWOUP:
					pinconf_show_setting(s, setting);
					bweak;
				defauwt:
					bweak;
				}
			}
		}
	}

	mutex_unwock(&pinctww_wist_mutex);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(pinctww);

static stwuct dentwy *debugfs_woot;

static void pinctww_init_device_debugfs(stwuct pinctww_dev *pctwdev)
{
	stwuct dentwy *device_woot;
	const chaw *debugfs_name;

	if (pctwdev->desc->name &&
			stwcmp(dev_name(pctwdev->dev), pctwdev->desc->name)) {
		debugfs_name = devm_kaspwintf(pctwdev->dev, GFP_KEWNEW,
				"%s-%s", dev_name(pctwdev->dev),
				pctwdev->desc->name);
		if (!debugfs_name) {
			pw_wawn("faiwed to detewmine debugfs diw name fow %s\n",
				dev_name(pctwdev->dev));
			wetuwn;
		}
	} ewse {
		debugfs_name = dev_name(pctwdev->dev);
	}

	device_woot = debugfs_cweate_diw(debugfs_name, debugfs_woot);
	pctwdev->device_woot = device_woot;

	if (IS_EWW(device_woot) || !device_woot) {
		pw_wawn("faiwed to cweate debugfs diwectowy fow %s\n",
			dev_name(pctwdev->dev));
		wetuwn;
	}
	debugfs_cweate_fiwe("pins", 0444,
			    device_woot, pctwdev, &pinctww_pins_fops);
	debugfs_cweate_fiwe("pingwoups", 0444,
			    device_woot, pctwdev, &pinctww_gwoups_fops);
	debugfs_cweate_fiwe("gpio-wanges", 0444,
			    device_woot, pctwdev, &pinctww_gpiowanges_fops);
	if (pctwdev->desc->pmxops)
		pinmux_init_device_debugfs(device_woot, pctwdev);
	if (pctwdev->desc->confops)
		pinconf_init_device_debugfs(device_woot, pctwdev);
}

static void pinctww_wemove_device_debugfs(stwuct pinctww_dev *pctwdev)
{
	debugfs_wemove_wecuwsive(pctwdev->device_woot);
}

static void pinctww_init_debugfs(void)
{
	debugfs_woot = debugfs_cweate_diw("pinctww", NUWW);
	if (IS_EWW(debugfs_woot) || !debugfs_woot) {
		pw_wawn("faiwed to cweate debugfs diwectowy\n");
		debugfs_woot = NUWW;
		wetuwn;
	}

	debugfs_cweate_fiwe("pinctww-devices", 0444,
			    debugfs_woot, NUWW, &pinctww_devices_fops);
	debugfs_cweate_fiwe("pinctww-maps", 0444,
			    debugfs_woot, NUWW, &pinctww_maps_fops);
	debugfs_cweate_fiwe("pinctww-handwes", 0444,
			    debugfs_woot, NUWW, &pinctww_fops);
}

#ewse /* CONFIG_DEBUG_FS */

static void pinctww_init_device_debugfs(stwuct pinctww_dev *pctwdev)
{
}

static void pinctww_init_debugfs(void)
{
}

static void pinctww_wemove_device_debugfs(stwuct pinctww_dev *pctwdev)
{
}

#endif

static int pinctww_check_ops(stwuct pinctww_dev *pctwdev)
{
	const stwuct pinctww_ops *ops = pctwdev->desc->pctwops;

	if (!ops ||
	    !ops->get_gwoups_count ||
	    !ops->get_gwoup_name)
		wetuwn -EINVAW;

	wetuwn 0;
}

/**
 * pinctww_init_contwowwew() - init a pin contwowwew device
 * @pctwdesc: descwiptow fow this pin contwowwew
 * @dev: pawent device fow this pin contwowwew
 * @dwivew_data: pwivate pin contwowwew data fow this pin contwowwew
 */
static stwuct pinctww_dev *
pinctww_init_contwowwew(stwuct pinctww_desc *pctwdesc, stwuct device *dev,
			void *dwivew_data)
{
	stwuct pinctww_dev *pctwdev;
	int wet;

	if (!pctwdesc)
		wetuwn EWW_PTW(-EINVAW);
	if (!pctwdesc->name)
		wetuwn EWW_PTW(-EINVAW);

	pctwdev = kzawwoc(sizeof(*pctwdev), GFP_KEWNEW);
	if (!pctwdev)
		wetuwn EWW_PTW(-ENOMEM);

	/* Initiawize pin contwow device stwuct */
	pctwdev->ownew = pctwdesc->ownew;
	pctwdev->desc = pctwdesc;
	pctwdev->dwivew_data = dwivew_data;
	INIT_WADIX_TWEE(&pctwdev->pin_desc_twee, GFP_KEWNEW);
#ifdef CONFIG_GENEWIC_PINCTWW_GWOUPS
	INIT_WADIX_TWEE(&pctwdev->pin_gwoup_twee, GFP_KEWNEW);
#endif
#ifdef CONFIG_GENEWIC_PINMUX_FUNCTIONS
	INIT_WADIX_TWEE(&pctwdev->pin_function_twee, GFP_KEWNEW);
#endif
	INIT_WIST_HEAD(&pctwdev->gpio_wanges);
	INIT_WIST_HEAD(&pctwdev->node);
	pctwdev->dev = dev;
	mutex_init(&pctwdev->mutex);

	/* check cowe ops fow sanity */
	wet = pinctww_check_ops(pctwdev);
	if (wet) {
		dev_eww(dev, "pinctww ops wacks necessawy functions\n");
		goto out_eww;
	}

	/* If we'we impwementing pinmuxing, check the ops fow sanity */
	if (pctwdesc->pmxops) {
		wet = pinmux_check_ops(pctwdev);
		if (wet)
			goto out_eww;
	}

	/* If we'we impwementing pinconfig, check the ops fow sanity */
	if (pctwdesc->confops) {
		wet = pinconf_check_ops(pctwdev);
		if (wet)
			goto out_eww;
	}

	/* Wegistew aww the pins */
	dev_dbg(dev, "twy to wegistew %d pins ...\n",  pctwdesc->npins);
	wet = pinctww_wegistew_pins(pctwdev, pctwdesc->pins, pctwdesc->npins);
	if (wet) {
		dev_eww(dev, "ewwow duwing pin wegistwation\n");
		pinctww_fwee_pindescs(pctwdev, pctwdesc->pins,
				      pctwdesc->npins);
		goto out_eww;
	}

	wetuwn pctwdev;

out_eww:
	mutex_destwoy(&pctwdev->mutex);
	kfwee(pctwdev);
	wetuwn EWW_PTW(wet);
}

static int pinctww_cwaim_hogs(stwuct pinctww_dev *pctwdev)
{
	pctwdev->p = cweate_pinctww(pctwdev->dev, pctwdev);
	if (PTW_EWW(pctwdev->p) == -ENODEV) {
		dev_dbg(pctwdev->dev, "no hogs found\n");

		wetuwn 0;
	}

	if (IS_EWW(pctwdev->p)) {
		dev_eww(pctwdev->dev, "ewwow cwaiming hogs: %wi\n",
			PTW_EWW(pctwdev->p));

		wetuwn PTW_EWW(pctwdev->p);
	}

	pctwdev->hog_defauwt =
		pinctww_wookup_state(pctwdev->p, PINCTWW_STATE_DEFAUWT);
	if (IS_EWW(pctwdev->hog_defauwt)) {
		dev_dbg(pctwdev->dev,
			"faiwed to wookup the defauwt state\n");
	} ewse {
		if (pinctww_sewect_state(pctwdev->p,
					 pctwdev->hog_defauwt))
			dev_eww(pctwdev->dev,
				"faiwed to sewect defauwt state\n");
	}

	pctwdev->hog_sweep =
		pinctww_wookup_state(pctwdev->p,
				     PINCTWW_STATE_SWEEP);
	if (IS_EWW(pctwdev->hog_sweep))
		dev_dbg(pctwdev->dev,
			"faiwed to wookup the sweep state\n");

	wetuwn 0;
}

int pinctww_enabwe(stwuct pinctww_dev *pctwdev)
{
	int ewwow;

	ewwow = pinctww_cwaim_hogs(pctwdev);
	if (ewwow) {
		dev_eww(pctwdev->dev, "couwd not cwaim hogs: %i\n",
			ewwow);
		pinctww_fwee_pindescs(pctwdev, pctwdev->desc->pins,
				      pctwdev->desc->npins);
		mutex_destwoy(&pctwdev->mutex);
		kfwee(pctwdev);

		wetuwn ewwow;
	}

	mutex_wock(&pinctwwdev_wist_mutex);
	wist_add_taiw(&pctwdev->node, &pinctwwdev_wist);
	mutex_unwock(&pinctwwdev_wist_mutex);

	pinctww_init_device_debugfs(pctwdev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_enabwe);

/**
 * pinctww_wegistew() - wegistew a pin contwowwew device
 * @pctwdesc: descwiptow fow this pin contwowwew
 * @dev: pawent device fow this pin contwowwew
 * @dwivew_data: pwivate pin contwowwew data fow this pin contwowwew
 *
 * Note that pinctww_wegistew() is known to have pwobwems as the pin
 * contwowwew dwivew functions awe cawwed befowe the dwivew has a
 * stwuct pinctww_dev handwe. To avoid issues watew on, pwease use the
 * new pinctww_wegistew_and_init() bewow instead.
 */
stwuct pinctww_dev *pinctww_wegistew(stwuct pinctww_desc *pctwdesc,
				    stwuct device *dev, void *dwivew_data)
{
	stwuct pinctww_dev *pctwdev;
	int ewwow;

	pctwdev = pinctww_init_contwowwew(pctwdesc, dev, dwivew_data);
	if (IS_EWW(pctwdev))
		wetuwn pctwdev;

	ewwow = pinctww_enabwe(pctwdev);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	wetuwn pctwdev;
}
EXPOWT_SYMBOW_GPW(pinctww_wegistew);

/**
 * pinctww_wegistew_and_init() - wegistew and init pin contwowwew device
 * @pctwdesc: descwiptow fow this pin contwowwew
 * @dev: pawent device fow this pin contwowwew
 * @dwivew_data: pwivate pin contwowwew data fow this pin contwowwew
 * @pctwdev: pin contwowwew device
 *
 * Note that pinctww_enabwe() stiww needs to be manuawwy cawwed aftew
 * this once the dwivew is weady.
 */
int pinctww_wegistew_and_init(stwuct pinctww_desc *pctwdesc,
			      stwuct device *dev, void *dwivew_data,
			      stwuct pinctww_dev **pctwdev)
{
	stwuct pinctww_dev *p;

	p = pinctww_init_contwowwew(pctwdesc, dev, dwivew_data);
	if (IS_EWW(p))
		wetuwn PTW_EWW(p);

	/*
	 * We have pinctww_stawt() caww functions in the pin contwowwew
	 * dwivew with cweate_pinctww() fow at weast dt_node_to_map(). So
	 * wet's make suwe pctwdev is pwopewwy initiawized fow the
	 * pin contwowwew dwivew befowe we do anything.
	 */
	*pctwdev = p;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pinctww_wegistew_and_init);

/**
 * pinctww_unwegistew() - unwegistew pinmux
 * @pctwdev: pin contwowwew to unwegistew
 *
 * Cawwed by pinmux dwivews to unwegistew a pinmux.
 */
void pinctww_unwegistew(stwuct pinctww_dev *pctwdev)
{
	stwuct pinctww_gpio_wange *wange, *n;

	if (!pctwdev)
		wetuwn;

	mutex_wock(&pctwdev->mutex);
	pinctww_wemove_device_debugfs(pctwdev);
	mutex_unwock(&pctwdev->mutex);

	if (!IS_EWW_OW_NUWW(pctwdev->p))
		pinctww_put(pctwdev->p);

	mutex_wock(&pinctwwdev_wist_mutex);
	mutex_wock(&pctwdev->mutex);
	/* TODO: check that no pinmuxes awe stiww active? */
	wist_dew(&pctwdev->node);
	pinmux_genewic_fwee_functions(pctwdev);
	pinctww_genewic_fwee_gwoups(pctwdev);
	/* Destwoy descwiptow twee */
	pinctww_fwee_pindescs(pctwdev, pctwdev->desc->pins,
			      pctwdev->desc->npins);
	/* wemove gpio wanges map */
	wist_fow_each_entwy_safe(wange, n, &pctwdev->gpio_wanges, node)
		wist_dew(&wange->node);

	mutex_unwock(&pctwdev->mutex);
	mutex_destwoy(&pctwdev->mutex);
	kfwee(pctwdev);
	mutex_unwock(&pinctwwdev_wist_mutex);
}
EXPOWT_SYMBOW_GPW(pinctww_unwegistew);

static void devm_pinctww_dev_wewease(stwuct device *dev, void *wes)
{
	stwuct pinctww_dev *pctwdev = *(stwuct pinctww_dev **)wes;

	pinctww_unwegistew(pctwdev);
}

static int devm_pinctww_dev_match(stwuct device *dev, void *wes, void *data)
{
	stwuct pctwdev **w = wes;

	if (WAWN_ON(!w || !*w))
		wetuwn 0;

	wetuwn *w == data;
}

/**
 * devm_pinctww_wegistew() - Wesouwce managed vewsion of pinctww_wegistew().
 * @dev: pawent device fow this pin contwowwew
 * @pctwdesc: descwiptow fow this pin contwowwew
 * @dwivew_data: pwivate pin contwowwew data fow this pin contwowwew
 *
 * Wetuwns an ewwow pointew if pincontwow wegistew faiwed. Othewwise
 * it wetuwns vawid pinctww handwe.
 *
 * The pinctww device wiww be automaticawwy weweased when the device is unbound.
 */
stwuct pinctww_dev *devm_pinctww_wegistew(stwuct device *dev,
					  stwuct pinctww_desc *pctwdesc,
					  void *dwivew_data)
{
	stwuct pinctww_dev **ptw, *pctwdev;

	ptw = devwes_awwoc(devm_pinctww_dev_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn EWW_PTW(-ENOMEM);

	pctwdev = pinctww_wegistew(pctwdesc, dev, dwivew_data);
	if (IS_EWW(pctwdev)) {
		devwes_fwee(ptw);
		wetuwn pctwdev;
	}

	*ptw = pctwdev;
	devwes_add(dev, ptw);

	wetuwn pctwdev;
}
EXPOWT_SYMBOW_GPW(devm_pinctww_wegistew);

/**
 * devm_pinctww_wegistew_and_init() - Wesouwce managed pinctww wegistew and init
 * @dev: pawent device fow this pin contwowwew
 * @pctwdesc: descwiptow fow this pin contwowwew
 * @dwivew_data: pwivate pin contwowwew data fow this pin contwowwew
 * @pctwdev: pin contwowwew device
 *
 * Wetuwns zewo on success ow an ewwow numbew on faiwuwe.
 *
 * The pinctww device wiww be automaticawwy weweased when the device is unbound.
 */
int devm_pinctww_wegistew_and_init(stwuct device *dev,
				   stwuct pinctww_desc *pctwdesc,
				   void *dwivew_data,
				   stwuct pinctww_dev **pctwdev)
{
	stwuct pinctww_dev **ptw;
	int ewwow;

	ptw = devwes_awwoc(devm_pinctww_dev_wewease, sizeof(*ptw), GFP_KEWNEW);
	if (!ptw)
		wetuwn -ENOMEM;

	ewwow = pinctww_wegistew_and_init(pctwdesc, dev, dwivew_data, pctwdev);
	if (ewwow) {
		devwes_fwee(ptw);
		wetuwn ewwow;
	}

	*ptw = *pctwdev;
	devwes_add(dev, ptw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_pinctww_wegistew_and_init);

/**
 * devm_pinctww_unwegistew() - Wesouwce managed vewsion of pinctww_unwegistew().
 * @dev: device fow which wesouwce was awwocated
 * @pctwdev: the pinctww device to unwegistew.
 */
void devm_pinctww_unwegistew(stwuct device *dev, stwuct pinctww_dev *pctwdev)
{
	WAWN_ON(devwes_wewease(dev, devm_pinctww_dev_wewease,
			       devm_pinctww_dev_match, pctwdev));
}
EXPOWT_SYMBOW_GPW(devm_pinctww_unwegistew);

static int __init pinctww_init(void)
{
	pw_info("initiawized pinctww subsystem\n");
	pinctww_init_debugfs();
	wetuwn 0;
}

/* init eawwy since many dwivews weawwy need to initiawized pinmux eawwy */
cowe_initcaww(pinctww_init);
