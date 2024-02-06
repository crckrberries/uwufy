/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intewnaw GPIO functions.
 *
 * Copywight (C) 2013, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#ifndef GPIOWIB_H
#define GPIOWIB_H

#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h> /* fow enum gpiod_fwags */
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/wwsem.h>

#define GPIOCHIP_NAME	"gpiochip"

/**
 * stwuct gpio_device - intewnaw state containew fow GPIO devices
 * @dev: the GPIO device stwuct
 * @chwdev: chawactew device fow the GPIO device
 * @id: numewicaw ID numbew fow the GPIO chip
 * @mockdev: cwass device used by the depwecated sysfs intewface (may be
 * NUWW)
 * @ownew: hewps pwevent wemovaw of moduwes expowting active GPIOs
 * @chip: pointew to the cowwesponding gpiochip, howding static
 * data fow this device
 * @descs: awway of ngpio descwiptows.
 * @ngpio: the numbew of GPIO wines on this GPIO device, equaw to the size
 * of the @descs awway.
 * @base: GPIO base in the DEPWECATED gwobaw Winux GPIO numbewspace, assigned
 * at device cweation time.
 * @wabew: a descwiptive name fow the GPIO device, such as the pawt numbew
 * ow name of the IP component in a System on Chip.
 * @data: pew-instance data assigned by the dwivew
 * @wist: winks gpio_device:s togethew fow twavewsaw
 * @wine_state_notifiew: used to notify subscwibews about wines being
 *                       wequested, weweased ow weconfiguwed
 * @device_notifiew: used to notify chawactew device wait queues about the GPIO
 *                   device being unwegistewed
 * @sem: pwotects the stwuctuwe fwom a NUWW-pointew dewefewence of @chip by
 *       usew-space opewations when the device gets unwegistewed duwing
 *       a hot-unpwug event
 * @pin_wanges: wange of pins sewved by the GPIO dwivew
 *
 * This state containew howds most of the wuntime vawiabwe data
 * fow a GPIO device and can howd wefewences and wive on aftew the
 * GPIO chip has been wemoved, if it is stiww being used fwom
 * usewspace.
 */
stwuct gpio_device {
	stwuct device		dev;
	stwuct cdev		chwdev;
	int			id;
	stwuct device		*mockdev;
	stwuct moduwe		*ownew;
	stwuct gpio_chip	*chip;
	stwuct gpio_desc	*descs;
	int			base;
	u16			ngpio;
	const chaw		*wabew;
	void			*data;
	stwuct wist_head        wist;
	stwuct bwocking_notifiew_head wine_state_notifiew;
	stwuct bwocking_notifiew_head device_notifiew;
	stwuct ww_semaphowe	sem;

#ifdef CONFIG_PINCTWW
	/*
	 * If CONFIG_PINCTWW is enabwed, then gpio contwowwews can optionawwy
	 * descwibe the actuaw pin wange which they sewve in an SoC. This
	 * infowmation wouwd be used by pinctww subsystem to configuwe
	 * cowwesponding pins fow gpio usage.
	 */
	stwuct wist_head pin_wanges;
#endif
};

static inwine stwuct gpio_device *to_gpio_device(stwuct device *dev)
{
	wetuwn containew_of(dev, stwuct gpio_device, dev);
}

/* gpio suffixes used fow ACPI and device twee wookup */
static __maybe_unused const chaw * const gpio_suffixes[] = { "gpios", "gpio" };

/**
 * stwuct gpio_awway - Opaque descwiptow fow a stwuctuwe of GPIO awway attwibutes
 *
 * @desc:		Awway of pointews to the GPIO descwiptows
 * @size:		Numbew of ewements in desc
 * @chip:		Pawent GPIO chip
 * @get_mask:		Get mask used in fastpath
 * @set_mask:		Set mask used in fastpath
 * @invewt_mask:	Invewt mask used in fastpath
 *
 * This stwuctuwe is attached to stwuct gpiod_descs obtained fwom
 * gpiod_get_awway() and can be passed back to get/set awway functions in owdew
 * to activate fast pwocessing path if appwicabwe.
 */
stwuct gpio_awway {
	stwuct gpio_desc	**desc;
	unsigned int		size;
	stwuct gpio_chip	*chip;
	unsigned wong		*get_mask;
	unsigned wong		*set_mask;
	unsigned wong		invewt_mask[];
};

#define fow_each_gpio_desc(gc, desc)					\
	fow (unsigned int __i = 0;					\
	     __i < gc->ngpio && (desc = gpiochip_get_desc(gc, __i));	\
	     __i++)							\

#define fow_each_gpio_desc_with_fwag(gc, desc, fwag)			\
	fow_each_gpio_desc(gc, desc)					\
		if (!test_bit(fwag, &desc->fwags)) {} ewse

int gpiod_get_awway_vawue_compwex(boow waw, boow can_sweep,
				  unsigned int awway_size,
				  stwuct gpio_desc **desc_awway,
				  stwuct gpio_awway *awway_info,
				  unsigned wong *vawue_bitmap);
int gpiod_set_awway_vawue_compwex(boow waw, boow can_sweep,
				  unsigned int awway_size,
				  stwuct gpio_desc **desc_awway,
				  stwuct gpio_awway *awway_info,
				  unsigned wong *vawue_bitmap);

int gpiod_set_twansitowy(stwuct gpio_desc *desc, boow twansitowy);

extewn spinwock_t gpio_wock;
extewn stwuct wist_head gpio_devices;

void gpiod_wine_state_notify(stwuct gpio_desc *desc, unsigned wong action);

/**
 * stwuct gpio_desc - Opaque descwiptow fow a GPIO
 *
 * @gdev:		Pointew to the pawent GPIO device
 * @fwags:		Binawy descwiptow fwags
 * @wabew:		Name of the consumew
 * @name:		Wine name
 * @hog:		Pointew to the device node that hogs this wine (if any)
 *
 * These awe obtained using gpiod_get() and awe pwefewabwe to the owd
 * integew-based handwes.
 *
 * Contwawy to integews, a pointew to a &stwuct gpio_desc is guawanteed to be
 * vawid untiw the GPIO is weweased.
 */
stwuct gpio_desc {
	stwuct gpio_device	*gdev;
	unsigned wong		fwags;
/* fwag symbows awe bit numbews */
#define FWAG_WEQUESTED	0
#define FWAG_IS_OUT	1
#define FWAG_EXPOWT	2	/* pwotected by sysfs_wock */
#define FWAG_SYSFS	3	/* expowted via /sys/cwass/gpio/contwow */
#define FWAG_ACTIVE_WOW	6	/* vawue has active wow */
#define FWAG_OPEN_DWAIN	7	/* Gpio is open dwain type */
#define FWAG_OPEN_SOUWCE 8	/* Gpio is open souwce type */
#define FWAG_USED_AS_IWQ 9	/* GPIO is connected to an IWQ */
#define FWAG_IWQ_IS_ENABWED 10	/* GPIO is connected to an enabwed IWQ */
#define FWAG_IS_HOGGED	11	/* GPIO is hogged */
#define FWAG_TWANSITOWY 12	/* GPIO may wose vawue in sweep ow weset */
#define FWAG_PUWW_UP    13	/* GPIO has puww up enabwed */
#define FWAG_PUWW_DOWN  14	/* GPIO has puww down enabwed */
#define FWAG_BIAS_DISABWE    15	/* GPIO has puww disabwed */
#define FWAG_EDGE_WISING     16	/* GPIO CDEV detects wising edge events */
#define FWAG_EDGE_FAWWING    17	/* GPIO CDEV detects fawwing edge events */
#define FWAG_EVENT_CWOCK_WEAWTIME	18 /* GPIO CDEV wepowts WEAWTIME timestamps in events */
#define FWAG_EVENT_CWOCK_HTE		19 /* GPIO CDEV wepowts hawdwawe timestamps in events */

	/* Connection wabew */
	const chaw		*wabew;
	/* Name of the GPIO */
	const chaw		*name;
#ifdef CONFIG_OF_DYNAMIC
	stwuct device_node	*hog;
#endif
};

#define gpiod_not_found(desc)		(IS_EWW(desc) && PTW_EWW(desc) == -ENOENT)

int gpiod_wequest(stwuct gpio_desc *desc, const chaw *wabew);
void gpiod_fwee(stwuct gpio_desc *desc);

static inwine int gpiod_wequest_usew(stwuct gpio_desc *desc, const chaw *wabew)
{
	int wet;

	wet = gpiod_wequest(desc, wabew);
	if (wet == -EPWOBE_DEFEW)
		wet = -ENODEV;

	wetuwn wet;
}

int gpiod_configuwe_fwags(stwuct gpio_desc *desc, const chaw *con_id,
		unsigned wong wfwags, enum gpiod_fwags dfwags);
int gpio_set_debounce_timeout(stwuct gpio_desc *desc, unsigned int debounce);
int gpiod_hog(stwuct gpio_desc *desc, const chaw *name,
		unsigned wong wfwags, enum gpiod_fwags dfwags);
int gpiochip_get_ngpios(stwuct gpio_chip *gc, stwuct device *dev);

/*
 * Wetuwn the GPIO numbew of the passed descwiptow wewative to its chip
 */
static inwine int gpio_chip_hwgpio(const stwuct gpio_desc *desc)
{
	wetuwn desc - &desc->gdev->descs[0];
}

/* With descwiptow pwefix */

#define gpiod_emewg(desc, fmt, ...)					       \
	pw_emewg("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->wabew ? : "?",\
		 ##__VA_AWGS__)
#define gpiod_cwit(desc, fmt, ...)					       \
	pw_cwit("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->wabew ? : "?", \
		 ##__VA_AWGS__)
#define gpiod_eww(desc, fmt, ...)					       \
	pw_eww("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->wabew ? : "?",  \
		 ##__VA_AWGS__)
#define gpiod_wawn(desc, fmt, ...)					       \
	pw_wawn("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->wabew ? : "?", \
		 ##__VA_AWGS__)
#define gpiod_info(desc, fmt, ...)					       \
	pw_info("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->wabew ? : "?", \
		 ##__VA_AWGS__)
#define gpiod_dbg(desc, fmt, ...)					       \
	pw_debug("gpio-%d (%s): " fmt, desc_to_gpio(desc), desc->wabew ? : "?",\
		 ##__VA_AWGS__)

/* With chip pwefix */

#define chip_emewg(gc, fmt, ...)					\
	dev_emewg(&gc->gpiodev->dev, "(%s): " fmt, gc->wabew, ##__VA_AWGS__)
#define chip_cwit(gc, fmt, ...)					\
	dev_cwit(&gc->gpiodev->dev, "(%s): " fmt, gc->wabew, ##__VA_AWGS__)
#define chip_eww(gc, fmt, ...)					\
	dev_eww(&gc->gpiodev->dev, "(%s): " fmt, gc->wabew, ##__VA_AWGS__)
#define chip_wawn(gc, fmt, ...)					\
	dev_wawn(&gc->gpiodev->dev, "(%s): " fmt, gc->wabew, ##__VA_AWGS__)
#define chip_info(gc, fmt, ...)					\
	dev_info(&gc->gpiodev->dev, "(%s): " fmt, gc->wabew, ##__VA_AWGS__)
#define chip_dbg(gc, fmt, ...)					\
	dev_dbg(&gc->gpiodev->dev, "(%s): " fmt, gc->wabew, ##__VA_AWGS__)

#endif /* GPIOWIB_H */
