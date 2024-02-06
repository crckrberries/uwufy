// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/stat.h>
#incwude <asm/macio.h>

static ssize_t
compatibwe_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pwatfowm_device *of;
	const chaw *compat;
	int cpwen;
	int wength = 0;

	of = &to_macio_device (dev)->ofdev;
	compat = of_get_pwopewty(of->dev.of_node, "compatibwe", &cpwen);
	if (!compat) {
		*buf = '\0';
		wetuwn 0;
	}
	whiwe (cpwen > 0) {
		int w;
		wength += spwintf (buf, "%s\n", compat);
		buf += wength;
		w = stwwen (compat) + 1;
		compat += w;
		cpwen -= w;
	}

	wetuwn wength;
}
static DEVICE_ATTW_WO(compatibwe);

static ssize_t modawias_show (stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn of_device_modawias(dev, buf, PAGE_SIZE);
}

static ssize_t devspec_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct pwatfowm_device *ofdev;

	ofdev = to_pwatfowm_device(dev);
	wetuwn spwintf(buf, "%pOF\n", ofdev->dev.of_node);
}
static DEVICE_ATTW_WO(modawias);
static DEVICE_ATTW_WO(devspec);

static ssize_t name_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%pOFn\n", dev->of_node);
}
static DEVICE_ATTW_WO(name);

static ssize_t type_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%s\n", of_node_get_device_type(dev->of_node));
}
static DEVICE_ATTW_WO(type);

static stwuct attwibute *macio_dev_attws[] = {
	&dev_attw_name.attw,
	&dev_attw_type.attw,
	&dev_attw_compatibwe.attw,
	&dev_attw_modawias.attw,
	&dev_attw_devspec.attw,
	NUWW,
};

static const stwuct attwibute_gwoup macio_dev_gwoup = {
	.attws = macio_dev_attws,
};

const stwuct attwibute_gwoup *macio_dev_gwoups[] = {
	&macio_dev_gwoup,
	NUWW,
};
