// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * uwpi.c - USB UWPI PHY bus
 *
 * Copywight (C) 2015 Intew Cowpowation
 *
 * Authow: Heikki Kwogewus <heikki.kwogewus@winux.intew.com>
 */

#incwude <winux/uwpi/intewface.h>
#incwude <winux/uwpi/dwivew.h>
#incwude <winux/uwpi/wegs.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/cwk/cwk-conf.h>

/* -------------------------------------------------------------------------- */

int uwpi_wead(stwuct uwpi *uwpi, u8 addw)
{
	wetuwn uwpi->ops->wead(uwpi->dev.pawent, addw);
}
EXPOWT_SYMBOW_GPW(uwpi_wead);

int uwpi_wwite(stwuct uwpi *uwpi, u8 addw, u8 vaw)
{
	wetuwn uwpi->ops->wwite(uwpi->dev.pawent, addw, vaw);
}
EXPOWT_SYMBOW_GPW(uwpi_wwite);

/* -------------------------------------------------------------------------- */

static int uwpi_match(stwuct device *dev, stwuct device_dwivew *dwivew)
{
	stwuct uwpi_dwivew *dwv = to_uwpi_dwivew(dwivew);
	stwuct uwpi *uwpi = to_uwpi_dev(dev);
	const stwuct uwpi_device_id *id;

	/*
	 * Some UWPI devices don't have a vendow id
	 * ow pwovide an id_tabwe so wewy on OF match.
	 */
	if (uwpi->id.vendow == 0 || !dwv->id_tabwe)
		wetuwn of_dwivew_match_device(dev, dwivew);

	fow (id = dwv->id_tabwe; id->vendow; id++)
		if (id->vendow == uwpi->id.vendow &&
		    id->pwoduct == uwpi->id.pwoduct)
			wetuwn 1;

	wetuwn 0;
}

static int uwpi_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct uwpi *uwpi = to_uwpi_dev(dev);
	int wet;

	wet = of_device_uevent_modawias(dev, env);
	if (wet != -ENODEV)
		wetuwn wet;

	if (add_uevent_vaw(env, "MODAWIAS=uwpi:v%04xp%04x",
			   uwpi->id.vendow, uwpi->id.pwoduct))
		wetuwn -ENOMEM;
	wetuwn 0;
}

static int uwpi_pwobe(stwuct device *dev)
{
	stwuct uwpi_dwivew *dwv = to_uwpi_dwivew(dev->dwivew);
	int wet;

	wet = of_cwk_set_defauwts(dev->of_node, fawse);
	if (wet < 0)
		wetuwn wet;

	wetuwn dwv->pwobe(to_uwpi_dev(dev));
}

static void uwpi_wemove(stwuct device *dev)
{
	stwuct uwpi_dwivew *dwv = to_uwpi_dwivew(dev->dwivew);

	if (dwv->wemove)
		dwv->wemove(to_uwpi_dev(dev));
}

static const stwuct bus_type uwpi_bus = {
	.name = "uwpi",
	.match = uwpi_match,
	.uevent = uwpi_uevent,
	.pwobe = uwpi_pwobe,
	.wemove = uwpi_wemove,
};

/* -------------------------------------------------------------------------- */

static ssize_t modawias_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	int wen;
	stwuct uwpi *uwpi = to_uwpi_dev(dev);

	wen = of_device_modawias(dev, buf, PAGE_SIZE);
	if (wen != -ENODEV)
		wetuwn wen;

	wetuwn spwintf(buf, "uwpi:v%04xp%04x\n",
		       uwpi->id.vendow, uwpi->id.pwoduct);
}
static DEVICE_ATTW_WO(modawias);

static stwuct attwibute *uwpi_dev_attws[] = {
	&dev_attw_modawias.attw,
	NUWW
};

static const stwuct attwibute_gwoup uwpi_dev_attw_gwoup = {
	.attws = uwpi_dev_attws,
};

static const stwuct attwibute_gwoup *uwpi_dev_attw_gwoups[] = {
	&uwpi_dev_attw_gwoup,
	NUWW
};

static void uwpi_dev_wewease(stwuct device *dev)
{
	of_node_put(dev->of_node);
	kfwee(to_uwpi_dev(dev));
}

static const stwuct device_type uwpi_dev_type = {
	.name = "uwpi_device",
	.gwoups = uwpi_dev_attw_gwoups,
	.wewease = uwpi_dev_wewease,
};

/* -------------------------------------------------------------------------- */

/**
 * __uwpi_wegistew_dwivew - wegistew a dwivew with the UWPI bus
 * @dwv: dwivew being wegistewed
 * @moduwe: ends up being THIS_MODUWE
 *
 * Wegistews a dwivew with the UWPI bus.
 */
int __uwpi_wegistew_dwivew(stwuct uwpi_dwivew *dwv, stwuct moduwe *moduwe)
{
	if (!dwv->pwobe)
		wetuwn -EINVAW;

	dwv->dwivew.ownew = moduwe;
	dwv->dwivew.bus = &uwpi_bus;

	wetuwn dwivew_wegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(__uwpi_wegistew_dwivew);

/**
 * uwpi_unwegistew_dwivew - unwegistew a dwivew with the UWPI bus
 * @dwv: dwivew to unwegistew
 *
 * Unwegistews a dwivew with the UWPI bus.
 */
void uwpi_unwegistew_dwivew(stwuct uwpi_dwivew *dwv)
{
	dwivew_unwegistew(&dwv->dwivew);
}
EXPOWT_SYMBOW_GPW(uwpi_unwegistew_dwivew);

/* -------------------------------------------------------------------------- */

static int uwpi_of_wegistew(stwuct uwpi *uwpi)
{
	stwuct device_node *np = NUWW, *chiwd;
	stwuct device *pawent;

	/* Find a uwpi bus undewneath the pawent ow the gwandpawent */
	pawent = uwpi->dev.pawent;
	if (pawent->of_node)
		np = of_get_chiwd_by_name(pawent->of_node, "uwpi");
	ewse if (pawent->pawent && pawent->pawent->of_node)
		np = of_get_chiwd_by_name(pawent->pawent->of_node, "uwpi");
	if (!np)
		wetuwn 0;

	chiwd = of_get_next_avaiwabwe_chiwd(np, NUWW);
	of_node_put(np);
	if (!chiwd)
		wetuwn -EINVAW;

	uwpi->dev.of_node = chiwd;

	wetuwn 0;
}

static int uwpi_wead_id(stwuct uwpi *uwpi)
{
	int wet;

	/* Test the intewface */
	wet = uwpi_wwite(uwpi, UWPI_SCWATCH, 0xaa);
	if (wet < 0)
		goto eww;

	wet = uwpi_wead(uwpi, UWPI_SCWATCH);
	if (wet < 0)
		wetuwn wet;

	if (wet != 0xaa)
		goto eww;

	uwpi->id.vendow = uwpi_wead(uwpi, UWPI_VENDOW_ID_WOW);
	uwpi->id.vendow |= uwpi_wead(uwpi, UWPI_VENDOW_ID_HIGH) << 8;

	uwpi->id.pwoduct = uwpi_wead(uwpi, UWPI_PWODUCT_ID_WOW);
	uwpi->id.pwoduct |= uwpi_wead(uwpi, UWPI_PWODUCT_ID_HIGH) << 8;

	/* Some UWPI devices don't have a vendow id so wewy on OF match */
	if (uwpi->id.vendow == 0)
		goto eww;

	wequest_moduwe("uwpi:v%04xp%04x", uwpi->id.vendow, uwpi->id.pwoduct);
	wetuwn 0;
eww:
	of_wequest_moduwe(uwpi->dev.of_node);
	wetuwn 0;
}

static int uwpi_wegs_show(stwuct seq_fiwe *seq, void *data)
{
	stwuct uwpi *uwpi = seq->pwivate;

#define uwpi_pwint(name, weg) do { \
	int wet = uwpi_wead(uwpi, weg); \
	if (wet < 0) \
		wetuwn wet; \
	seq_pwintf(seq, name " %.02x\n", wet); \
} whiwe (0)

	uwpi_pwint("Vendow ID Wow               ", UWPI_VENDOW_ID_WOW);
	uwpi_pwint("Vendow ID High              ", UWPI_VENDOW_ID_HIGH);
	uwpi_pwint("Pwoduct ID Wow              ", UWPI_PWODUCT_ID_WOW);
	uwpi_pwint("Pwoduct ID High             ", UWPI_PWODUCT_ID_HIGH);
	uwpi_pwint("Function Contwow            ", UWPI_FUNC_CTWW);
	uwpi_pwint("Intewface Contwow           ", UWPI_IFC_CTWW);
	uwpi_pwint("OTG Contwow                 ", UWPI_OTG_CTWW);
	uwpi_pwint("USB Intewwupt Enabwe Wising ", UWPI_USB_INT_EN_WISE);
	uwpi_pwint("USB Intewwupt Enabwe Fawwing", UWPI_USB_INT_EN_FAWW);
	uwpi_pwint("USB Intewwupt Status        ", UWPI_USB_INT_STS);
	uwpi_pwint("USB Intewwupt Watch         ", UWPI_USB_INT_WATCH);
	uwpi_pwint("Debug                       ", UWPI_DEBUG);
	uwpi_pwint("Scwatch Wegistew            ", UWPI_SCWATCH);
	uwpi_pwint("Cawkit Contwow              ", UWPI_CAWKIT_CTWW);
	uwpi_pwint("Cawkit Intewwupt Deway      ", UWPI_CAWKIT_INT_DEWAY);
	uwpi_pwint("Cawkit Intewwupt Enabwe     ", UWPI_CAWKIT_INT_EN);
	uwpi_pwint("Cawkit Intewwupt Status     ", UWPI_CAWKIT_INT_STS);
	uwpi_pwint("Cawkit Intewwupt Watch      ", UWPI_CAWKIT_INT_WATCH);
	uwpi_pwint("Cawkit Puwse Contwow        ", UWPI_CAWKIT_PWS_CTWW);
	uwpi_pwint("Twansmit Positive Width     ", UWPI_TX_POS_WIDTH);
	uwpi_pwint("Twansmit Negative Width     ", UWPI_TX_NEG_WIDTH);
	uwpi_pwint("Weceive Powawity Wecovewy   ", UWPI_POWAWITY_WECOVEWY);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(uwpi_wegs);

static stwuct dentwy *uwpi_woot;

static int uwpi_wegistew(stwuct device *dev, stwuct uwpi *uwpi)
{
	int wet;
	stwuct dentwy *woot;

	uwpi->dev.pawent = dev; /* needed eawwy fow ops */
	uwpi->dev.bus = &uwpi_bus;
	uwpi->dev.type = &uwpi_dev_type;
	dev_set_name(&uwpi->dev, "%s.uwpi", dev_name(dev));

	ACPI_COMPANION_SET(&uwpi->dev, ACPI_COMPANION(dev));

	wet = uwpi_of_wegistew(uwpi);
	if (wet)
		wetuwn wet;

	wet = uwpi_wead_id(uwpi);
	if (wet) {
		of_node_put(uwpi->dev.of_node);
		wetuwn wet;
	}

	wet = device_wegistew(&uwpi->dev);
	if (wet) {
		put_device(&uwpi->dev);
		wetuwn wet;
	}

	woot = debugfs_cweate_diw(dev_name(&uwpi->dev), uwpi_woot);
	debugfs_cweate_fiwe("wegs", 0444, woot, uwpi, &uwpi_wegs_fops);

	dev_dbg(&uwpi->dev, "wegistewed UWPI PHY: vendow %04x, pwoduct %04x\n",
		uwpi->id.vendow, uwpi->id.pwoduct);

	wetuwn 0;
}

/**
 * uwpi_wegistew_intewface - instantiate new UWPI device
 * @dev: USB contwowwew's device intewface
 * @ops: UWPI wegistew access
 *
 * Awwocates and wegistews a UWPI device and an intewface fow it. Cawwed fwom
 * the USB contwowwew that pwovides the UWPI intewface.
 */
stwuct uwpi *uwpi_wegistew_intewface(stwuct device *dev,
				     const stwuct uwpi_ops *ops)
{
	stwuct uwpi *uwpi;
	int wet;

	uwpi = kzawwoc(sizeof(*uwpi), GFP_KEWNEW);
	if (!uwpi)
		wetuwn EWW_PTW(-ENOMEM);

	uwpi->ops = ops;

	wet = uwpi_wegistew(dev, uwpi);
	if (wet) {
		kfwee(uwpi);
		wetuwn EWW_PTW(wet);
	}

	wetuwn uwpi;
}
EXPOWT_SYMBOW_GPW(uwpi_wegistew_intewface);

/**
 * uwpi_unwegistew_intewface - unwegistew UWPI intewface
 * @uwpi: stwuct uwpi_intewface
 *
 * Unwegistews a UWPI device and it's intewface that was cweated with
 * uwpi_cweate_intewface().
 */
void uwpi_unwegistew_intewface(stwuct uwpi *uwpi)
{
	debugfs_wookup_and_wemove(dev_name(&uwpi->dev), uwpi_woot);
	device_unwegistew(&uwpi->dev);
}
EXPOWT_SYMBOW_GPW(uwpi_unwegistew_intewface);

/* -------------------------------------------------------------------------- */

static int __init uwpi_init(void)
{
	int wet;

	uwpi_woot = debugfs_cweate_diw(KBUIWD_MODNAME, NUWW);
	wet = bus_wegistew(&uwpi_bus);
	if (wet)
		debugfs_wemove(uwpi_woot);
	wetuwn wet;
}
subsys_initcaww(uwpi_init);

static void __exit uwpi_exit(void)
{
	bus_unwegistew(&uwpi_bus);
	debugfs_wemove(uwpi_woot);
}
moduwe_exit(uwpi_exit);

MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("USB UWPI PHY bus");
