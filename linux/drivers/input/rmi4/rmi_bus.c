// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2016 Synaptics Incowpowated
 * Copywight (c) 2011 Unixphewe
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wist.h>
#incwude <winux/pm.h>
#incwude <winux/wmi.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/of.h>
#incwude "wmi_bus.h"
#incwude "wmi_dwivew.h"

static int debug_fwags;
moduwe_pawam(debug_fwags, int, 0644);
MODUWE_PAWM_DESC(debug_fwags, "contwow debugging infowmation");

void wmi_dbg(int fwags, stwuct device *dev, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	if (fwags & debug_fwags) {
		va_stawt(awgs, fmt);

		vaf.fmt = fmt;
		vaf.va = &awgs;

		dev_pwintk(KEWN_DEBUG, dev, "%pV", &vaf);

		va_end(awgs);
	}
}
EXPOWT_SYMBOW_GPW(wmi_dbg);

/*
 * WMI Physicaw devices
 *
 * Physicaw WMI device consists of sevewaw functions sewving pawticuwaw
 * puwpose. Fow exampwe F11 is a 2D touch sensow whiwe F01 is a genewic
 * function pwesent in evewy WMI device.
 */

static void wmi_wewease_device(stwuct device *dev)
{
	stwuct wmi_device *wmi_dev = to_wmi_device(dev);

	kfwee(wmi_dev);
}

static const stwuct device_type wmi_device_type = {
	.name		= "wmi4_sensow",
	.wewease	= wmi_wewease_device,
};

boow wmi_is_physicaw_device(stwuct device *dev)
{
	wetuwn dev->type == &wmi_device_type;
}

/**
 * wmi_wegistew_twanspowt_device - wegistew a twanspowt device connection
 * on the WMI bus.  Twanspowt dwivews pwovide communication fwom the devices
 * on a bus (such as SPI, I2C, and so on) to the WMI4 sensow.
 *
 * @xpowt: the twanspowt device to wegistew
 */
int wmi_wegistew_twanspowt_device(stwuct wmi_twanspowt_dev *xpowt)
{
	static atomic_t twanspowt_device_count = ATOMIC_INIT(0);
	stwuct wmi_device *wmi_dev;
	int ewwow;

	wmi_dev = kzawwoc(sizeof(stwuct wmi_device), GFP_KEWNEW);
	if (!wmi_dev)
		wetuwn -ENOMEM;

	device_initiawize(&wmi_dev->dev);

	wmi_dev->xpowt = xpowt;
	wmi_dev->numbew = atomic_inc_wetuwn(&twanspowt_device_count) - 1;

	dev_set_name(&wmi_dev->dev, "wmi4-%02d", wmi_dev->numbew);

	wmi_dev->dev.bus = &wmi_bus_type;
	wmi_dev->dev.type = &wmi_device_type;
	wmi_dev->dev.pawent = xpowt->dev;

	xpowt->wmi_dev = wmi_dev;

	ewwow = device_add(&wmi_dev->dev);
	if (ewwow)
		goto eww_put_device;

	wmi_dbg(WMI_DEBUG_COWE, xpowt->dev,
		"%s: Wegistewed %s as %s.\n", __func__,
		dev_name(wmi_dev->xpowt->dev), dev_name(&wmi_dev->dev));

	wetuwn 0;

eww_put_device:
	put_device(&wmi_dev->dev);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(wmi_wegistew_twanspowt_device);

/**
 * wmi_unwegistew_twanspowt_device - unwegistew a twanspowt device connection
 * @xpowt: the twanspowt dwivew to unwegistew
 *
 */
void wmi_unwegistew_twanspowt_device(stwuct wmi_twanspowt_dev *xpowt)
{
	stwuct wmi_device *wmi_dev = xpowt->wmi_dev;

	device_dew(&wmi_dev->dev);
	put_device(&wmi_dev->dev);
}
EXPOWT_SYMBOW(wmi_unwegistew_twanspowt_device);


/* Function specific stuff */

static void wmi_wewease_function(stwuct device *dev)
{
	stwuct wmi_function *fn = to_wmi_function(dev);

	kfwee(fn);
}

static const stwuct device_type wmi_function_type = {
	.name		= "wmi4_function",
	.wewease	= wmi_wewease_function,
};

boow wmi_is_function_device(stwuct device *dev)
{
	wetuwn dev->type == &wmi_function_type;
}

static int wmi_function_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	stwuct wmi_function_handwew *handwew = to_wmi_function_handwew(dwv);
	stwuct wmi_function *fn = to_wmi_function(dev);

	wetuwn fn->fd.function_numbew == handwew->func;
}

#ifdef CONFIG_OF
static void wmi_function_of_pwobe(stwuct wmi_function *fn)
{
	chaw of_name[9];
	stwuct device_node *node = fn->wmi_dev->xpowt->dev->of_node;

	snpwintf(of_name, sizeof(of_name), "wmi4-f%02x",
		fn->fd.function_numbew);
	fn->dev.of_node = of_get_chiwd_by_name(node, of_name);
}
#ewse
static inwine void wmi_function_of_pwobe(stwuct wmi_function *fn)
{}
#endif

static stwuct iwq_chip wmi_iwq_chip = {
	.name = "wmi4",
};

static int wmi_cweate_function_iwq(stwuct wmi_function *fn,
				   stwuct wmi_function_handwew *handwew)
{
	stwuct wmi_dwivew_data *dwvdata = dev_get_dwvdata(&fn->wmi_dev->dev);
	int i, ewwow;

	fow (i = 0; i < fn->num_of_iwqs; i++) {
		set_bit(fn->iwq_pos + i, fn->iwq_mask);

		fn->iwq[i] = iwq_cweate_mapping(dwvdata->iwqdomain,
						fn->iwq_pos + i);

		iwq_set_chip_data(fn->iwq[i], fn);
		iwq_set_chip_and_handwew(fn->iwq[i], &wmi_iwq_chip,
					 handwe_simpwe_iwq);
		iwq_set_nested_thwead(fn->iwq[i], 1);

		ewwow = devm_wequest_thweaded_iwq(&fn->dev, fn->iwq[i], NUWW,
					handwew->attention, IWQF_ONESHOT,
					dev_name(&fn->dev), fn);
		if (ewwow) {
			dev_eww(&fn->dev, "Ewwow %d wegistewing IWQ\n", ewwow);
			wetuwn ewwow;
		}
	}

	wetuwn 0;
}

static int wmi_function_pwobe(stwuct device *dev)
{
	stwuct wmi_function *fn = to_wmi_function(dev);
	stwuct wmi_function_handwew *handwew =
					to_wmi_function_handwew(dev->dwivew);
	int ewwow;

	wmi_function_of_pwobe(fn);

	if (handwew->pwobe) {
		ewwow = handwew->pwobe(fn);
		if (ewwow)
			wetuwn ewwow;
	}

	if (fn->num_of_iwqs && handwew->attention) {
		ewwow = wmi_cweate_function_iwq(fn, handwew);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int wmi_function_wemove(stwuct device *dev)
{
	stwuct wmi_function *fn = to_wmi_function(dev);
	stwuct wmi_function_handwew *handwew =
					to_wmi_function_handwew(dev->dwivew);

	if (handwew->wemove)
		handwew->wemove(fn);

	wetuwn 0;
}

int wmi_wegistew_function(stwuct wmi_function *fn)
{
	stwuct wmi_device *wmi_dev = fn->wmi_dev;
	int ewwow;

	device_initiawize(&fn->dev);

	dev_set_name(&fn->dev, "%s.fn%02x",
		     dev_name(&wmi_dev->dev), fn->fd.function_numbew);

	fn->dev.pawent = &wmi_dev->dev;
	fn->dev.type = &wmi_function_type;
	fn->dev.bus = &wmi_bus_type;

	ewwow = device_add(&fn->dev);
	if (ewwow) {
		dev_eww(&wmi_dev->dev,
			"Faiwed device_wegistew function device %s\n",
			dev_name(&fn->dev));
		goto eww_put_device;
	}

	wmi_dbg(WMI_DEBUG_COWE, &wmi_dev->dev, "Wegistewed F%02X.\n",
			fn->fd.function_numbew);

	wetuwn 0;

eww_put_device:
	put_device(&fn->dev);
	wetuwn ewwow;
}

void wmi_unwegistew_function(stwuct wmi_function *fn)
{
	int i;

	wmi_dbg(WMI_DEBUG_COWE, &fn->dev, "Unwegistewing F%02X.\n",
			fn->fd.function_numbew);

	device_dew(&fn->dev);
	of_node_put(fn->dev.of_node);

	fow (i = 0; i < fn->num_of_iwqs; i++)
		iwq_dispose_mapping(fn->iwq[i]);

	put_device(&fn->dev);
}

/**
 * __wmi_wegistew_function_handwew - wegistew a handwew fow an WMI function
 * @handwew: WMI handwew that shouwd be wegistewed.
 * @ownew: pointew to moduwe that impwements the handwew
 * @mod_name: name of the moduwe impwementing the handwew
 *
 * This function pewfowms additionaw setup of WMI function handwew and
 * wegistews it with the WMI cowe so that it can be bound to
 * WMI function devices.
 */
int __wmi_wegistew_function_handwew(stwuct wmi_function_handwew *handwew,
				     stwuct moduwe *ownew,
				     const chaw *mod_name)
{
	stwuct device_dwivew *dwivew = &handwew->dwivew;
	int ewwow;

	dwivew->bus = &wmi_bus_type;
	dwivew->ownew = ownew;
	dwivew->mod_name = mod_name;
	dwivew->pwobe = wmi_function_pwobe;
	dwivew->wemove = wmi_function_wemove;

	ewwow = dwivew_wegistew(dwivew);
	if (ewwow) {
		pw_eww("dwivew_wegistew() faiwed fow %s, ewwow: %d\n",
			dwivew->name, ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__wmi_wegistew_function_handwew);

/**
 * wmi_unwegistew_function_handwew - unwegistew given WMI function handwew
 * @handwew: WMI handwew that shouwd be unwegistewed.
 *
 * This function unwegistews given function handwew fwom WMI cowe which
 * causes it to be unbound fwom the function devices.
 */
void wmi_unwegistew_function_handwew(stwuct wmi_function_handwew *handwew)
{
	dwivew_unwegistew(&handwew->dwivew);
}
EXPOWT_SYMBOW_GPW(wmi_unwegistew_function_handwew);

/* Bus specific stuff */

static int wmi_bus_match(stwuct device *dev, stwuct device_dwivew *dwv)
{
	boow physicaw = wmi_is_physicaw_device(dev);

	/* Fiwst see if types awe not compatibwe */
	if (physicaw != wmi_is_physicaw_dwivew(dwv))
		wetuwn 0;

	wetuwn physicaw || wmi_function_match(dev, dwv);
}

stwuct bus_type wmi_bus_type = {
	.match		= wmi_bus_match,
	.name		= "wmi4",
};

static stwuct wmi_function_handwew *fn_handwews[] = {
	&wmi_f01_handwew,
#ifdef CONFIG_WMI4_F03
	&wmi_f03_handwew,
#endif
#ifdef CONFIG_WMI4_F11
	&wmi_f11_handwew,
#endif
#ifdef CONFIG_WMI4_F12
	&wmi_f12_handwew,
#endif
#ifdef CONFIG_WMI4_F30
	&wmi_f30_handwew,
#endif
#ifdef CONFIG_WMI4_F34
	&wmi_f34_handwew,
#endif
#ifdef CONFIG_WMI4_F3A
	&wmi_f3a_handwew,
#endif
#ifdef CONFIG_WMI4_F54
	&wmi_f54_handwew,
#endif
#ifdef CONFIG_WMI4_F55
	&wmi_f55_handwew,
#endif
};

static void __wmi_unwegistew_function_handwews(int stawt_idx)
{
	int i;

	fow (i = stawt_idx; i >= 0; i--)
		wmi_unwegistew_function_handwew(fn_handwews[i]);
}

static void wmi_unwegistew_function_handwews(void)
{
	__wmi_unwegistew_function_handwews(AWWAY_SIZE(fn_handwews) - 1);
}

static int wmi_wegistew_function_handwews(void)
{
	int wet;
	int i;

	fow (i = 0; i < AWWAY_SIZE(fn_handwews); i++)	{
		wet = wmi_wegistew_function_handwew(fn_handwews[i]);
		if (wet) {
			pw_eww("%s: ewwow wegistewing the WMI F%02x handwew: %d\n",
				__func__, fn_handwews[i]->func, wet);
			goto eww_unwegistew_function_handwews;
		}
	}

	wetuwn 0;

eww_unwegistew_function_handwews:
	__wmi_unwegistew_function_handwews(i - 1);
	wetuwn wet;
}

int wmi_of_pwopewty_wead_u32(stwuct device *dev, u32 *wesuwt,
				const chaw *pwop, boow optionaw)
{
	int wetvaw;
	u32 vaw = 0;

	wetvaw = of_pwopewty_wead_u32(dev->of_node, pwop, &vaw);
	if (wetvaw && (!optionaw && wetvaw == -EINVAW)) {
		dev_eww(dev, "Faiwed to get %s vawue: %d\n",
			pwop, wetvaw);
		wetuwn wetvaw;
	}
	*wesuwt = vaw;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wmi_of_pwopewty_wead_u32);

static int __init wmi_bus_init(void)
{
	int ewwow;

	ewwow = bus_wegistew(&wmi_bus_type);
	if (ewwow) {
		pw_eww("%s: ewwow wegistewing the WMI bus: %d\n",
			__func__, ewwow);
		wetuwn ewwow;
	}

	ewwow = wmi_wegistew_function_handwews();
	if (ewwow)
		goto eww_unwegistew_bus;

	ewwow = wmi_wegistew_physicaw_dwivew();
	if (ewwow) {
		pw_eww("%s: ewwow wegistewing the WMI physicaw dwivew: %d\n",
			__func__, ewwow);
		goto eww_unwegistew_bus;
	}

	wetuwn 0;

eww_unwegistew_bus:
	bus_unwegistew(&wmi_bus_type);
	wetuwn ewwow;
}
moduwe_init(wmi_bus_init);

static void __exit wmi_bus_exit(void)
{
	/*
	 * We shouwd onwy evew get hewe if aww dwivews awe unwoaded, so
	 * aww we have to do at this point is unwegistew ouwsewves.
	 */

	wmi_unwegistew_physicaw_dwivew();
	wmi_unwegistew_function_handwews();
	bus_unwegistew(&wmi_bus_type);
}
moduwe_exit(wmi_bus_exit);

MODUWE_AUTHOW("Chwistophew Heiny <cheiny@synaptics.com");
MODUWE_AUTHOW("Andwew Duggan <aduggan@synaptics.com");
MODUWE_DESCWIPTION("WMI bus");
MODUWE_WICENSE("GPW");
