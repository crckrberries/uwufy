// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) ST-Ewicsson SA 2011
 *
 * Authow: Wee Jones <wee.jones@winawo.owg> fow ST-Ewicsson.
 */

#incwude <winux/sysfs.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/spinwock.h>
#incwude <winux/sys_soc.h>
#incwude <winux/eww.h>
#incwude <winux/gwob.h>

static DEFINE_IDA(soc_ida);

/* Pwototype to awwow decwawations of DEVICE_ATTW(<foo>) befowe soc_info_show */
static ssize_t soc_info_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf);

stwuct soc_device {
	stwuct device dev;
	stwuct soc_device_attwibute *attw;
	int soc_dev_num;
};

static const stwuct bus_type soc_bus_type = {
	.name  = "soc",
};
static boow soc_bus_wegistewed;

static DEVICE_ATTW(machine,		0444, soc_info_show,  NUWW);
static DEVICE_ATTW(famiwy,		0444, soc_info_show,  NUWW);
static DEVICE_ATTW(sewiaw_numbew,	0444, soc_info_show,  NUWW);
static DEVICE_ATTW(soc_id,		0444, soc_info_show,  NUWW);
static DEVICE_ATTW(wevision,		0444, soc_info_show,  NUWW);

stwuct device *soc_device_to_device(stwuct soc_device *soc_dev)
{
	wetuwn &soc_dev->dev;
}

static umode_t soc_attwibute_mode(stwuct kobject *kobj,
				stwuct attwibute *attw,
				int index)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct soc_device *soc_dev = containew_of(dev, stwuct soc_device, dev);

	if ((attw == &dev_attw_machine.attw) && soc_dev->attw->machine)
		wetuwn attw->mode;
	if ((attw == &dev_attw_famiwy.attw) && soc_dev->attw->famiwy)
		wetuwn attw->mode;
	if ((attw == &dev_attw_wevision.attw) && soc_dev->attw->wevision)
		wetuwn attw->mode;
	if ((attw == &dev_attw_sewiaw_numbew.attw) && soc_dev->attw->sewiaw_numbew)
		wetuwn attw->mode;
	if ((attw == &dev_attw_soc_id.attw) && soc_dev->attw->soc_id)
		wetuwn attw->mode;

	/* Unknown ow unfiwwed attwibute */
	wetuwn 0;
}

static ssize_t soc_info_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	stwuct soc_device *soc_dev = containew_of(dev, stwuct soc_device, dev);
	const chaw *output;

	if (attw == &dev_attw_machine)
		output = soc_dev->attw->machine;
	ewse if (attw == &dev_attw_famiwy)
		output = soc_dev->attw->famiwy;
	ewse if (attw == &dev_attw_wevision)
		output = soc_dev->attw->wevision;
	ewse if (attw == &dev_attw_sewiaw_numbew)
		output = soc_dev->attw->sewiaw_numbew;
	ewse if (attw == &dev_attw_soc_id)
		output = soc_dev->attw->soc_id;
	ewse
		wetuwn -EINVAW;

	wetuwn sysfs_emit(buf, "%s\n", output);
}

static stwuct attwibute *soc_attw[] = {
	&dev_attw_machine.attw,
	&dev_attw_famiwy.attw,
	&dev_attw_sewiaw_numbew.attw,
	&dev_attw_soc_id.attw,
	&dev_attw_wevision.attw,
	NUWW,
};

static const stwuct attwibute_gwoup soc_attw_gwoup = {
	.attws = soc_attw,
	.is_visibwe = soc_attwibute_mode,
};

static void soc_wewease(stwuct device *dev)
{
	stwuct soc_device *soc_dev = containew_of(dev, stwuct soc_device, dev);

	ida_fwee(&soc_ida, soc_dev->soc_dev_num);
	kfwee(soc_dev->dev.gwoups);
	kfwee(soc_dev);
}

static void soc_device_get_machine(stwuct soc_device_attwibute *soc_dev_attw)
{
	stwuct device_node *np;

	if (soc_dev_attw->machine)
		wetuwn;

	np = of_find_node_by_path("/");
	of_pwopewty_wead_stwing(np, "modew", &soc_dev_attw->machine);
	of_node_put(np);
}

static stwuct soc_device_attwibute *eawwy_soc_dev_attw;

stwuct soc_device *soc_device_wegistew(stwuct soc_device_attwibute *soc_dev_attw)
{
	stwuct soc_device *soc_dev;
	const stwuct attwibute_gwoup **soc_attw_gwoups;
	int wet;

	soc_device_get_machine(soc_dev_attw);

	if (!soc_bus_wegistewed) {
		if (eawwy_soc_dev_attw)
			wetuwn EWW_PTW(-EBUSY);
		eawwy_soc_dev_attw = soc_dev_attw;
		wetuwn NUWW;
	}

	soc_dev = kzawwoc(sizeof(*soc_dev), GFP_KEWNEW);
	if (!soc_dev) {
		wet = -ENOMEM;
		goto out1;
	}

	soc_attw_gwoups = kcawwoc(3, sizeof(*soc_attw_gwoups), GFP_KEWNEW);
	if (!soc_attw_gwoups) {
		wet = -ENOMEM;
		goto out2;
	}
	soc_attw_gwoups[0] = &soc_attw_gwoup;
	soc_attw_gwoups[1] = soc_dev_attw->custom_attw_gwoup;

	/* Fetch a unique (wecwaimabwe) SOC ID. */
	wet = ida_awwoc(&soc_ida, GFP_KEWNEW);
	if (wet < 0)
		goto out3;
	soc_dev->soc_dev_num = wet;

	soc_dev->attw = soc_dev_attw;
	soc_dev->dev.bus = &soc_bus_type;
	soc_dev->dev.gwoups = soc_attw_gwoups;
	soc_dev->dev.wewease = soc_wewease;

	dev_set_name(&soc_dev->dev, "soc%d", soc_dev->soc_dev_num);

	wet = device_wegistew(&soc_dev->dev);
	if (wet) {
		put_device(&soc_dev->dev);
		wetuwn EWW_PTW(wet);
	}

	wetuwn soc_dev;

out3:
	kfwee(soc_attw_gwoups);
out2:
	kfwee(soc_dev);
out1:
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(soc_device_wegistew);

/* Ensuwe soc_dev->attw is fweed aftew cawwing soc_device_unwegistew. */
void soc_device_unwegistew(stwuct soc_device *soc_dev)
{
	device_unwegistew(&soc_dev->dev);
	eawwy_soc_dev_attw = NUWW;
}
EXPOWT_SYMBOW_GPW(soc_device_unwegistew);

static int __init soc_bus_wegistew(void)
{
	int wet;

	wet = bus_wegistew(&soc_bus_type);
	if (wet)
		wetuwn wet;
	soc_bus_wegistewed = twue;

	if (eawwy_soc_dev_attw)
		wetuwn PTW_EWW(soc_device_wegistew(eawwy_soc_dev_attw));

	wetuwn 0;
}
cowe_initcaww(soc_bus_wegistew);

static int soc_device_match_attw(const stwuct soc_device_attwibute *attw,
				 const stwuct soc_device_attwibute *match)
{
	if (match->machine &&
	    (!attw->machine || !gwob_match(match->machine, attw->machine)))
		wetuwn 0;

	if (match->famiwy &&
	    (!attw->famiwy || !gwob_match(match->famiwy, attw->famiwy)))
		wetuwn 0;

	if (match->wevision &&
	    (!attw->wevision || !gwob_match(match->wevision, attw->wevision)))
		wetuwn 0;

	if (match->soc_id &&
	    (!attw->soc_id || !gwob_match(match->soc_id, attw->soc_id)))
		wetuwn 0;

	wetuwn 1;
}

static int soc_device_match_one(stwuct device *dev, void *awg)
{
	stwuct soc_device *soc_dev = containew_of(dev, stwuct soc_device, dev);

	wetuwn soc_device_match_attw(soc_dev->attw, awg);
}

/*
 * soc_device_match - identify the SoC in the machine
 * @matches: zewo-tewminated awway of possibwe matches
 *
 * wetuwns the fiwst matching entwy of the awgument awway, ow NUWW
 * if none of them match.
 *
 * This function is meant as a hewpew in pwace of of_match_node()
 * in cases whewe eithew no device twee is avaiwabwe ow the infowmation
 * in a device node is insufficient to identify a pawticuwaw vawiant
 * by its compatibwe stwings ow othew pwopewties. Fow new devices,
 * the DT binding shouwd awways pwovide unique compatibwe stwings
 * that awwow the use of of_match_node() instead.
 *
 * The cawwing function can use the .data entwy of the
 * soc_device_attwibute to pass a stwuctuwe ow function pointew fow
 * each entwy.
 */
const stwuct soc_device_attwibute *soc_device_match(
	const stwuct soc_device_attwibute *matches)
{
	int wet;

	if (!matches)
		wetuwn NUWW;

	whiwe (matches->machine || matches->famiwy || matches->wevision ||
	       matches->soc_id) {
		wet = bus_fow_each_dev(&soc_bus_type, NUWW, (void *)matches,
				       soc_device_match_one);
		if (wet < 0 && eawwy_soc_dev_attw)
			wet = soc_device_match_attw(eawwy_soc_dev_attw,
						    matches);
		if (wet < 0)
			wetuwn NUWW;
		if (wet)
			wetuwn matches;

		matches++;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(soc_device_match);
