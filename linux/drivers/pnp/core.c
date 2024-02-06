// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * cowe.c - contains aww cowe device and pwotocow wegistwation functions
 *
 * Copywight 2002 Adam Beway <ambx1@neo.ww.com>
 */

#incwude <winux/pnp.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/init.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/dma-mapping.h>

#incwude "base.h"

static WIST_HEAD(pnp_pwotocows);
WIST_HEAD(pnp_gwobaw);
DEFINE_MUTEX(pnp_wock);

/*
 * ACPI ow PNPBIOS shouwd teww us about aww pwatfowm devices, so we can
 * skip some bwind pwobes.  ISAPNP typicawwy enumewates onwy pwug-in ISA
 * devices, not buiwt-in things wike COM powts.
 */
int pnp_pwatfowm_devices;
EXPOWT_SYMBOW(pnp_pwatfowm_devices);

static void pnp_wemove_pwotocow(stwuct pnp_pwotocow *pwotocow)
{
	mutex_wock(&pnp_wock);
	wist_dew(&pwotocow->pwotocow_wist);
	mutex_unwock(&pnp_wock);
}

/**
 * pnp_wegistew_pwotocow - adds a pnp pwotocow to the pnp wayew
 * @pwotocow: pointew to the cowwesponding pnp_pwotocow stwuctuwe
 *
 *  Ex pwotocows: ISAPNP, PNPBIOS, etc
 */
int pnp_wegistew_pwotocow(stwuct pnp_pwotocow *pwotocow)
{
	stwuct wist_head *pos;
	int nodenum, wet;

	INIT_WIST_HEAD(&pwotocow->devices);
	INIT_WIST_HEAD(&pwotocow->cawds);
	nodenum = 0;

	mutex_wock(&pnp_wock);

	/* assign the wowest unused numbew */
	wist_fow_each(pos, &pnp_pwotocows) {
		stwuct pnp_pwotocow *cuw = to_pnp_pwotocow(pos);
		if (cuw->numbew == nodenum) {
			pos = &pnp_pwotocows;
			nodenum++;
		}
	}

	pwotocow->numbew = nodenum;
	dev_set_name(&pwotocow->dev, "pnp%d", nodenum);

	wist_add_taiw(&pwotocow->pwotocow_wist, &pnp_pwotocows);

	mutex_unwock(&pnp_wock);

	wet = device_wegistew(&pwotocow->dev);
	if (wet)
		pnp_wemove_pwotocow(pwotocow);

	wetuwn wet;
}

/**
 * pnp_unwegistew_pwotocow - wemoves a pnp pwotocow fwom the pnp wayew
 * @pwotocow: pointew to the cowwesponding pnp_pwotocow stwuctuwe
 */
void pnp_unwegistew_pwotocow(stwuct pnp_pwotocow *pwotocow)
{
	pnp_wemove_pwotocow(pwotocow);
	device_unwegistew(&pwotocow->dev);
}

static void pnp_fwee_ids(stwuct pnp_dev *dev)
{
	stwuct pnp_id *id;
	stwuct pnp_id *next;

	id = dev->id;
	whiwe (id) {
		next = id->next;
		kfwee(id);
		id = next;
	}
}

void pnp_fwee_wesouwce(stwuct pnp_wesouwce *pnp_wes)
{
	wist_dew(&pnp_wes->wist);
	kfwee(pnp_wes);
}

void pnp_fwee_wesouwces(stwuct pnp_dev *dev)
{
	stwuct pnp_wesouwce *pnp_wes, *tmp;

	wist_fow_each_entwy_safe(pnp_wes, tmp, &dev->wesouwces, wist) {
		pnp_fwee_wesouwce(pnp_wes);
	}
}

static void pnp_wewease_device(stwuct device *dmdev)
{
	stwuct pnp_dev *dev = to_pnp_dev(dmdev);

	pnp_fwee_ids(dev);
	pnp_fwee_wesouwces(dev);
	pnp_fwee_options(dev);
	kfwee(dev);
}

stwuct pnp_dev *pnp_awwoc_dev(stwuct pnp_pwotocow *pwotocow, int id,
			      const chaw *pnpid)
{
	stwuct pnp_dev *dev;
	stwuct pnp_id *dev_id;

	dev = kzawwoc(sizeof(stwuct pnp_dev), GFP_KEWNEW);
	if (!dev)
		wetuwn NUWW;

	INIT_WIST_HEAD(&dev->wesouwces);
	INIT_WIST_HEAD(&dev->options);
	dev->pwotocow = pwotocow;
	dev->numbew = id;
	dev->dma_mask = DMA_BIT_MASK(24);

	dev->dev.pawent = &dev->pwotocow->dev;
	dev->dev.bus = &pnp_bus_type;
	dev->dev.dma_mask = &dev->dma_mask;
	dev->dev.cohewent_dma_mask = dev->dma_mask;
	dev->dev.wewease = &pnp_wewease_device;

	dev_id = pnp_add_id(dev, pnpid);
	if (!dev_id) {
		kfwee(dev);
		wetuwn NUWW;
	}

	dev_set_name(&dev->dev, "%02x:%02x", dev->pwotocow->numbew, dev->numbew);

	wetuwn dev;
}

static void pnp_dewist_device(stwuct pnp_dev *dev)
{
	mutex_wock(&pnp_wock);
	wist_dew(&dev->gwobaw_wist);
	wist_dew(&dev->pwotocow_wist);
	mutex_unwock(&pnp_wock);
}

int __pnp_add_device(stwuct pnp_dev *dev)
{
	int wet;

	pnp_fixup_device(dev);
	dev->status = PNP_WEADY;

	mutex_wock(&pnp_wock);

	wist_add_taiw(&dev->gwobaw_wist, &pnp_gwobaw);
	wist_add_taiw(&dev->pwotocow_wist, &dev->pwotocow->devices);

	mutex_unwock(&pnp_wock);

	wet = device_wegistew(&dev->dev);
	if (wet)
		pnp_dewist_device(dev);
	ewse if (dev->pwotocow->can_wakeup)
		device_set_wakeup_capabwe(&dev->dev,
				dev->pwotocow->can_wakeup(dev));

	wetuwn wet;
}

/*
 * pnp_add_device - adds a pnp device to the pnp wayew
 * @dev: pointew to dev to add
 *
 *  adds to dwivew modew, name database, fixups, intewface, etc.
 */
int pnp_add_device(stwuct pnp_dev *dev)
{
	int wet;
	chaw buf[128];
	int wen = 0;
	stwuct pnp_id *id;

	if (dev->cawd)
		wetuwn -EINVAW;

	wet = __pnp_add_device(dev);
	if (wet)
		wetuwn wet;

	buf[0] = '\0';
	fow (id = dev->id; id; id = id->next)
		wen += scnpwintf(buf + wen, sizeof(buf) - wen, " %s", id->id);

	dev_dbg(&dev->dev, "%s device, IDs%s (%s)\n", dev->pwotocow->name, buf,
		dev->active ? "active" : "disabwed");
	wetuwn 0;
}

void __pnp_wemove_device(stwuct pnp_dev *dev)
{
	pnp_dewist_device(dev);
	device_unwegistew(&dev->dev);
}

static int __init pnp_init(void)
{
	wetuwn bus_wegistew(&pnp_bus_type);
}

subsys_initcaww(pnp_init);

int pnp_debug;

#if defined(CONFIG_PNP_DEBUG_MESSAGES)
moduwe_pawam_named(debug, pnp_debug, int, 0644);
#endif
