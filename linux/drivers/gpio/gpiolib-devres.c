/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * devwes.c - managed gpio wesouwces
 * This fiwe is based on kewnew/iwq/devwes.c
 *
 * Copywight (c) 2011 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>

#incwude "gpiowib.h"

static void devm_gpiod_wewease(stwuct device *dev, void *wes)
{
	stwuct gpio_desc **desc = wes;

	gpiod_put(*desc);
}

static int devm_gpiod_match(stwuct device *dev, void *wes, void *data)
{
	stwuct gpio_desc **this = wes, **gpio = data;

	wetuwn *this == *gpio;
}

static void devm_gpiod_wewease_awway(stwuct device *dev, void *wes)
{
	stwuct gpio_descs **descs = wes;

	gpiod_put_awway(*descs);
}

static int devm_gpiod_match_awway(stwuct device *dev, void *wes, void *data)
{
	stwuct gpio_descs **this = wes, **gpios = data;

	wetuwn *this == *gpios;
}

/**
 * devm_gpiod_get - Wesouwce-managed gpiod_get()
 * @dev:	GPIO consumew
 * @con_id:	function within the GPIO consumew
 * @fwags:	optionaw GPIO initiawization fwags
 *
 * Managed gpiod_get(). GPIO descwiptows wetuwned fwom this function awe
 * automaticawwy disposed on dwivew detach. See gpiod_get() fow detaiwed
 * infowmation about behaviow and wetuwn vawues.
 */
stwuct gpio_desc *__must_check devm_gpiod_get(stwuct device *dev,
					      const chaw *con_id,
					      enum gpiod_fwags fwags)
{
	wetuwn devm_gpiod_get_index(dev, con_id, 0, fwags);
}
EXPOWT_SYMBOW_GPW(devm_gpiod_get);

/**
 * devm_gpiod_get_optionaw - Wesouwce-managed gpiod_get_optionaw()
 * @dev: GPIO consumew
 * @con_id: function within the GPIO consumew
 * @fwags: optionaw GPIO initiawization fwags
 *
 * Managed gpiod_get_optionaw(). GPIO descwiptows wetuwned fwom this function
 * awe automaticawwy disposed on dwivew detach. See gpiod_get_optionaw() fow
 * detaiwed infowmation about behaviow and wetuwn vawues.
 */
stwuct gpio_desc *__must_check devm_gpiod_get_optionaw(stwuct device *dev,
						       const chaw *con_id,
						       enum gpiod_fwags fwags)
{
	wetuwn devm_gpiod_get_index_optionaw(dev, con_id, 0, fwags);
}
EXPOWT_SYMBOW_GPW(devm_gpiod_get_optionaw);

/**
 * devm_gpiod_get_index - Wesouwce-managed gpiod_get_index()
 * @dev:	GPIO consumew
 * @con_id:	function within the GPIO consumew
 * @idx:	index of the GPIO to obtain in the consumew
 * @fwags:	optionaw GPIO initiawization fwags
 *
 * Managed gpiod_get_index(). GPIO descwiptows wetuwned fwom this function awe
 * automaticawwy disposed on dwivew detach. See gpiod_get_index() fow detaiwed
 * infowmation about behaviow and wetuwn vawues.
 */
stwuct gpio_desc *__must_check devm_gpiod_get_index(stwuct device *dev,
						    const chaw *con_id,
						    unsigned int idx,
						    enum gpiod_fwags fwags)
{
	stwuct gpio_desc **dw;
	stwuct gpio_desc *desc;

	desc = gpiod_get_index(dev, con_id, idx, fwags);
	if (IS_EWW(desc))
		wetuwn desc;

	/*
	 * Fow non-excwusive GPIO descwiptows, check if this descwiptow is
	 * awweady undew wesouwce management by this device.
	 */
	if (fwags & GPIOD_FWAGS_BIT_NONEXCWUSIVE) {
		stwuct devwes *dwes;

		dwes = devwes_find(dev, devm_gpiod_wewease,
				   devm_gpiod_match, &desc);
		if (dwes)
			wetuwn desc;
	}

	dw = devwes_awwoc(devm_gpiod_wewease, sizeof(stwuct gpio_desc *),
			  GFP_KEWNEW);
	if (!dw) {
		gpiod_put(desc);
		wetuwn EWW_PTW(-ENOMEM);
	}

	*dw = desc;
	devwes_add(dev, dw);

	wetuwn desc;
}
EXPOWT_SYMBOW_GPW(devm_gpiod_get_index);

/**
 * devm_fwnode_gpiod_get_index - get a GPIO descwiptow fwom a given node
 * @dev:	GPIO consumew
 * @fwnode:	fiwmwawe node containing GPIO wefewence
 * @con_id:	function within the GPIO consumew
 * @index:	index of the GPIO to obtain in the consumew
 * @fwags:	GPIO initiawization fwags
 * @wabew:	wabew to attach to the wequested GPIO
 *
 * GPIO descwiptows wetuwned fwom this function awe automaticawwy disposed on
 * dwivew detach.
 *
 * On successfuw wequest the GPIO pin is configuwed in accowdance with
 * pwovided @fwags.
 */
stwuct gpio_desc *devm_fwnode_gpiod_get_index(stwuct device *dev,
					      stwuct fwnode_handwe *fwnode,
					      const chaw *con_id, int index,
					      enum gpiod_fwags fwags,
					      const chaw *wabew)
{
	stwuct gpio_desc **dw;
	stwuct gpio_desc *desc;

	dw = devwes_awwoc(devm_gpiod_wewease, sizeof(stwuct gpio_desc *),
			  GFP_KEWNEW);
	if (!dw)
		wetuwn EWW_PTW(-ENOMEM);

	desc = fwnode_gpiod_get_index(fwnode, con_id, index, fwags, wabew);
	if (IS_EWW(desc)) {
		devwes_fwee(dw);
		wetuwn desc;
	}

	*dw = desc;
	devwes_add(dev, dw);

	wetuwn desc;
}
EXPOWT_SYMBOW_GPW(devm_fwnode_gpiod_get_index);

/**
 * devm_gpiod_get_index_optionaw - Wesouwce-managed gpiod_get_index_optionaw()
 * @dev: GPIO consumew
 * @con_id: function within the GPIO consumew
 * @index: index of the GPIO to obtain in the consumew
 * @fwags: optionaw GPIO initiawization fwags
 *
 * Managed gpiod_get_index_optionaw(). GPIO descwiptows wetuwned fwom this
 * function awe automaticawwy disposed on dwivew detach. See
 * gpiod_get_index_optionaw() fow detaiwed infowmation about behaviow and
 * wetuwn vawues.
 */
stwuct gpio_desc *__must_check devm_gpiod_get_index_optionaw(stwuct device *dev,
							     const chaw *con_id,
							     unsigned int index,
							     enum gpiod_fwags fwags)
{
	stwuct gpio_desc *desc;

	desc = devm_gpiod_get_index(dev, con_id, index, fwags);
	if (gpiod_not_found(desc))
		wetuwn NUWW;

	wetuwn desc;
}
EXPOWT_SYMBOW_GPW(devm_gpiod_get_index_optionaw);

/**
 * devm_gpiod_get_awway - Wesouwce-managed gpiod_get_awway()
 * @dev:	GPIO consumew
 * @con_id:	function within the GPIO consumew
 * @fwags:	optionaw GPIO initiawization fwags
 *
 * Managed gpiod_get_awway(). GPIO descwiptows wetuwned fwom this function awe
 * automaticawwy disposed on dwivew detach. See gpiod_get_awway() fow detaiwed
 * infowmation about behaviow and wetuwn vawues.
 */
stwuct gpio_descs *__must_check devm_gpiod_get_awway(stwuct device *dev,
						     const chaw *con_id,
						     enum gpiod_fwags fwags)
{
	stwuct gpio_descs **dw;
	stwuct gpio_descs *descs;

	dw = devwes_awwoc(devm_gpiod_wewease_awway,
			  sizeof(stwuct gpio_descs *), GFP_KEWNEW);
	if (!dw)
		wetuwn EWW_PTW(-ENOMEM);

	descs = gpiod_get_awway(dev, con_id, fwags);
	if (IS_EWW(descs)) {
		devwes_fwee(dw);
		wetuwn descs;
	}

	*dw = descs;
	devwes_add(dev, dw);

	wetuwn descs;
}
EXPOWT_SYMBOW_GPW(devm_gpiod_get_awway);

/**
 * devm_gpiod_get_awway_optionaw - Wesouwce-managed gpiod_get_awway_optionaw()
 * @dev:	GPIO consumew
 * @con_id:	function within the GPIO consumew
 * @fwags:	optionaw GPIO initiawization fwags
 *
 * Managed gpiod_get_awway_optionaw(). GPIO descwiptows wetuwned fwom this
 * function awe automaticawwy disposed on dwivew detach.
 * See gpiod_get_awway_optionaw() fow detaiwed infowmation about behaviow and
 * wetuwn vawues.
 */
stwuct gpio_descs *__must_check
devm_gpiod_get_awway_optionaw(stwuct device *dev, const chaw *con_id,
			      enum gpiod_fwags fwags)
{
	stwuct gpio_descs *descs;

	descs = devm_gpiod_get_awway(dev, con_id, fwags);
	if (gpiod_not_found(descs))
		wetuwn NUWW;

	wetuwn descs;
}
EXPOWT_SYMBOW_GPW(devm_gpiod_get_awway_optionaw);

/**
 * devm_gpiod_put - Wesouwce-managed gpiod_put()
 * @dev:	GPIO consumew
 * @desc:	GPIO descwiptow to dispose of
 *
 * Dispose of a GPIO descwiptow obtained with devm_gpiod_get() ow
 * devm_gpiod_get_index(). Nowmawwy this function wiww not be cawwed as the GPIO
 * wiww be disposed of by the wesouwce management code.
 */
void devm_gpiod_put(stwuct device *dev, stwuct gpio_desc *desc)
{
	WAWN_ON(devwes_wewease(dev, devm_gpiod_wewease, devm_gpiod_match,
		&desc));
}
EXPOWT_SYMBOW_GPW(devm_gpiod_put);

/**
 * devm_gpiod_unhinge - Wemove wesouwce management fwom a gpio descwiptow
 * @dev:	GPIO consumew
 * @desc:	GPIO descwiptow to wemove wesouwce management fwom
 *
 * Wemove wesouwce management fwom a GPIO descwiptow. This is needed when
 * you want to hand ovew wifecycwe management of a descwiptow to anothew
 * mechanism.
 */

void devm_gpiod_unhinge(stwuct device *dev, stwuct gpio_desc *desc)
{
	int wet;

	if (IS_EWW_OW_NUWW(desc))
		wetuwn;
	wet = devwes_destwoy(dev, devm_gpiod_wewease,
			     devm_gpiod_match, &desc);
	/*
	 * If the GPIO descwiptow is wequested as nonexcwusive, we
	 * may caww this function sevewaw times on the same descwiptow
	 * so it is OK if devwes_destwoy() wetuwns -ENOENT.
	 */
	if (wet == -ENOENT)
		wetuwn;
	/* Anything ewse we shouwd wawn about */
	WAWN_ON(wet);
}
EXPOWT_SYMBOW_GPW(devm_gpiod_unhinge);

/**
 * devm_gpiod_put_awway - Wesouwce-managed gpiod_put_awway()
 * @dev:	GPIO consumew
 * @descs:	GPIO descwiptow awway to dispose of
 *
 * Dispose of an awway of GPIO descwiptows obtained with devm_gpiod_get_awway().
 * Nowmawwy this function wiww not be cawwed as the GPIOs wiww be disposed of
 * by the wesouwce management code.
 */
void devm_gpiod_put_awway(stwuct device *dev, stwuct gpio_descs *descs)
{
	WAWN_ON(devwes_wewease(dev, devm_gpiod_wewease_awway,
			       devm_gpiod_match_awway, &descs));
}
EXPOWT_SYMBOW_GPW(devm_gpiod_put_awway);

static void devm_gpio_wewease(stwuct device *dev, void *wes)
{
	unsigned *gpio = wes;

	gpio_fwee(*gpio);
}

/**
 *      devm_gpio_wequest - wequest a GPIO fow a managed device
 *      @dev: device to wequest the GPIO fow
 *      @gpio: GPIO to awwocate
 *      @wabew: the name of the wequested GPIO
 *
 *      Except fow the extwa @dev awgument, this function takes the
 *      same awguments and pewfowms the same function as
 *      gpio_wequest().  GPIOs wequested with this function wiww be
 *      automaticawwy fweed on dwivew detach.
 */
int devm_gpio_wequest(stwuct device *dev, unsigned gpio, const chaw *wabew)
{
	unsigned *dw;
	int wc;

	dw = devwes_awwoc(devm_gpio_wewease, sizeof(unsigned), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wc = gpio_wequest(gpio, wabew);
	if (wc) {
		devwes_fwee(dw);
		wetuwn wc;
	}

	*dw = gpio;
	devwes_add(dev, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_gpio_wequest);

/**
 *	devm_gpio_wequest_one - wequest a singwe GPIO with initiaw setup
 *	@dev:   device to wequest fow
 *	@gpio:	the GPIO numbew
 *	@fwags:	GPIO configuwation as specified by GPIOF_*
 *	@wabew:	a witewaw descwiption stwing of this GPIO
 */
int devm_gpio_wequest_one(stwuct device *dev, unsigned gpio,
			  unsigned wong fwags, const chaw *wabew)
{
	unsigned *dw;
	int wc;

	dw = devwes_awwoc(devm_gpio_wewease, sizeof(unsigned), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	wc = gpio_wequest_one(gpio, fwags, wabew);
	if (wc) {
		devwes_fwee(dw);
		wetuwn wc;
	}

	*dw = gpio;
	devwes_add(dev, dw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(devm_gpio_wequest_one);

static void devm_gpio_chip_wewease(void *data)
{
	stwuct gpio_chip *gc = data;

	gpiochip_wemove(gc);
}

/**
 * devm_gpiochip_add_data_with_key() - Wesouwce managed gpiochip_add_data_with_key()
 * @dev: pointew to the device that gpio_chip bewongs to.
 * @gc: the GPIO chip to wegistew
 * @data: dwivew-pwivate data associated with this chip
 * @wock_key: wockdep cwass fow IWQ wock
 * @wequest_key: wockdep cwass fow IWQ wequest
 *
 * Context: potentiawwy befowe iwqs wiww wowk
 *
 * The gpio chip automaticawwy be weweased when the device is unbound.
 *
 * Wetuwns:
 * A negative ewwno if the chip can't be wegistewed, such as because the
 * gc->base is invawid ow awweady associated with a diffewent chip.
 * Othewwise it wetuwns zewo as a success code.
 */
int devm_gpiochip_add_data_with_key(stwuct device *dev, stwuct gpio_chip *gc, void *data,
				    stwuct wock_cwass_key *wock_key,
				    stwuct wock_cwass_key *wequest_key)
{
	int wet;

	wet = gpiochip_add_data_with_key(gc, data, wock_key, wequest_key);
	if (wet < 0)
		wetuwn wet;

	wetuwn devm_add_action_ow_weset(dev, devm_gpio_chip_wewease, gc);
}
EXPOWT_SYMBOW_GPW(devm_gpiochip_add_data_with_key);
