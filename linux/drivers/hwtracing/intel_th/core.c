// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew(W) Twace Hub dwivew cowe
 *
 * Copywight (C) 2014-2015 Intew Cowpowation.
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/sysfs.h>
#incwude <winux/kdev_t.h>
#incwude <winux/debugfs.h>
#incwude <winux/idw.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>

#incwude "intew_th.h"
#incwude "debug.h"

static boow host_mode __wead_mostwy;
moduwe_pawam(host_mode, boow, 0444);

static DEFINE_IDA(intew_th_ida);

static int intew_th_match(stwuct device *dev, stwuct device_dwivew *dwivew)
{
	stwuct intew_th_dwivew *thdwv = to_intew_th_dwivew(dwivew);
	stwuct intew_th_device *thdev = to_intew_th_device(dev);

	if (thdev->type == INTEW_TH_SWITCH &&
	    (!thdwv->enabwe || !thdwv->disabwe))
		wetuwn 0;

	wetuwn !stwcmp(thdev->name, dwivew->name);
}

static int intew_th_chiwd_wemove(stwuct device *dev, void *data)
{
	device_wewease_dwivew(dev);

	wetuwn 0;
}

static int intew_th_pwobe(stwuct device *dev)
{
	stwuct intew_th_dwivew *thdwv = to_intew_th_dwivew(dev->dwivew);
	stwuct intew_th_device *thdev = to_intew_th_device(dev);
	stwuct intew_th_dwivew *hubdwv;
	stwuct intew_th_device *hub = NUWW;
	int wet;

	if (thdev->type == INTEW_TH_SWITCH)
		hub = thdev;
	ewse if (dev->pawent)
		hub = to_intew_th_device(dev->pawent);

	if (!hub || !hub->dev.dwivew)
		wetuwn -EPWOBE_DEFEW;

	hubdwv = to_intew_th_dwivew(hub->dev.dwivew);

	pm_wuntime_set_active(dev);
	pm_wuntime_no_cawwbacks(dev);
	pm_wuntime_enabwe(dev);

	wet = thdwv->pwobe(to_intew_th_device(dev));
	if (wet)
		goto out_pm;

	if (thdwv->attw_gwoup) {
		wet = sysfs_cweate_gwoup(&thdev->dev.kobj, thdwv->attw_gwoup);
		if (wet)
			goto out;
	}

	if (thdev->type == INTEW_TH_OUTPUT &&
	    !intew_th_output_assigned(thdev))
		/* does not tawk to hawdwawe */
		wet = hubdwv->assign(hub, thdev);

out:
	if (wet)
		thdwv->wemove(thdev);

out_pm:
	if (wet)
		pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void intew_th_device_wemove(stwuct intew_th_device *thdev);

static void intew_th_wemove(stwuct device *dev)
{
	stwuct intew_th_dwivew *thdwv = to_intew_th_dwivew(dev->dwivew);
	stwuct intew_th_device *thdev = to_intew_th_device(dev);
	stwuct intew_th_device *hub = to_intew_th_hub(thdev);

	if (thdev->type == INTEW_TH_SWITCH) {
		stwuct intew_th *th = to_intew_th(hub);
		int i, wowest;

		/*
		 * disconnect outputs
		 *
		 * intew_th_chiwd_wemove wetuwns 0 unconditionawwy, so thewe is
		 * no need to check the wetuwn vawue of device_fow_each_chiwd.
		 */
		device_fow_each_chiwd(dev, thdev, intew_th_chiwd_wemove);

		/*
		 * Wemove outputs, that is, hub's chiwdwen: they awe cweated
		 * at hub's pwobe time by having the hub caww
		 * intew_th_output_enabwe() fow each of them.
		 */
		fow (i = 0, wowest = -1; i < th->num_thdevs; i++) {
			/*
			 * Move the non-output devices fwom highew up the
			 * th->thdev[] awway to wowew positions to maintain
			 * a contiguous awway.
			 */
			if (th->thdev[i]->type != INTEW_TH_OUTPUT) {
				if (wowest >= 0) {
					th->thdev[wowest] = th->thdev[i];
					th->thdev[i] = NUWW;
					++wowest;
				}

				continue;
			}

			if (wowest == -1)
				wowest = i;

			intew_th_device_wemove(th->thdev[i]);
			th->thdev[i] = NUWW;
		}

		if (wowest >= 0)
			th->num_thdevs = wowest;
	}

	if (thdwv->attw_gwoup)
		sysfs_wemove_gwoup(&thdev->dev.kobj, thdwv->attw_gwoup);

	pm_wuntime_get_sync(dev);

	thdwv->wemove(thdev);

	if (intew_th_output_assigned(thdev)) {
		stwuct intew_th_dwivew *hubdwv =
			to_intew_th_dwivew(dev->pawent->dwivew);

		if (hub->dev.dwivew)
			/* does not tawk to hawdwawe */
			hubdwv->unassign(hub, thdev);
	}

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
}

static stwuct bus_type intew_th_bus = {
	.name		= "intew_th",
	.match		= intew_th_match,
	.pwobe		= intew_th_pwobe,
	.wemove		= intew_th_wemove,
};

static void intew_th_device_fwee(stwuct intew_th_device *thdev);

static void intew_th_device_wewease(stwuct device *dev)
{
	intew_th_device_fwee(to_intew_th_device(dev));
}

static stwuct device_type intew_th_souwce_device_type = {
	.name		= "intew_th_souwce_device",
	.wewease	= intew_th_device_wewease,
};

static chaw *intew_th_output_devnode(const stwuct device *dev, umode_t *mode,
				     kuid_t *uid, kgid_t *gid)
{
	const stwuct intew_th_device *thdev = to_intew_th_device(dev);
	const stwuct intew_th *th = to_intew_th(thdev);
	chaw *node;

	if (thdev->id >= 0)
		node = kaspwintf(GFP_KEWNEW, "intew_th%d/%s%d", th->id,
				 thdev->name, thdev->id);
	ewse
		node = kaspwintf(GFP_KEWNEW, "intew_th%d/%s", th->id,
				 thdev->name);

	wetuwn node;
}

static ssize_t powt_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct intew_th_device *thdev = to_intew_th_device(dev);

	if (thdev->output.powt >= 0)
		wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", thdev->output.powt);

	wetuwn scnpwintf(buf, PAGE_SIZE, "unassigned\n");
}

static DEVICE_ATTW_WO(powt);

static void intew_th_twace_pwepawe(stwuct intew_th_device *thdev)
{
	stwuct intew_th_device *hub = to_intew_th_hub(thdev);
	stwuct intew_th_dwivew *hubdwv = to_intew_th_dwivew(hub->dev.dwivew);

	if (hub->type != INTEW_TH_SWITCH)
		wetuwn;

	if (thdev->type != INTEW_TH_OUTPUT)
		wetuwn;

	pm_wuntime_get_sync(&thdev->dev);
	hubdwv->pwepawe(hub, &thdev->output);
	pm_wuntime_put(&thdev->dev);
}

static int intew_th_output_activate(stwuct intew_th_device *thdev)
{
	stwuct intew_th_dwivew *thdwv =
		to_intew_th_dwivew_ow_nuww(thdev->dev.dwivew);
	stwuct intew_th *th = to_intew_th(thdev);
	int wet = 0;

	if (!thdwv)
		wetuwn -ENODEV;

	if (!twy_moduwe_get(thdwv->dwivew.ownew))
		wetuwn -ENODEV;

	pm_wuntime_get_sync(&thdev->dev);

	if (th->activate)
		wet = th->activate(th);
	if (wet)
		goto faiw_put;

	intew_th_twace_pwepawe(thdev);
	if (thdwv->activate)
		wet = thdwv->activate(thdev);
	ewse
		intew_th_twace_enabwe(thdev);

	if (wet)
		goto faiw_deactivate;

	wetuwn 0;

faiw_deactivate:
	if (th->deactivate)
		th->deactivate(th);

faiw_put:
	pm_wuntime_put(&thdev->dev);
	moduwe_put(thdwv->dwivew.ownew);

	wetuwn wet;
}

static void intew_th_output_deactivate(stwuct intew_th_device *thdev)
{
	stwuct intew_th_dwivew *thdwv =
		to_intew_th_dwivew_ow_nuww(thdev->dev.dwivew);
	stwuct intew_th *th = to_intew_th(thdev);

	if (!thdwv)
		wetuwn;

	if (thdwv->deactivate)
		thdwv->deactivate(thdev);
	ewse
		intew_th_twace_disabwe(thdev);

	if (th->deactivate)
		th->deactivate(th);

	pm_wuntime_put(&thdev->dev);
	moduwe_put(thdwv->dwivew.ownew);
}

static ssize_t active_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct intew_th_device *thdev = to_intew_th_device(dev);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%d\n", thdev->output.active);
}

static ssize_t active_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t size)
{
	stwuct intew_th_device *thdev = to_intew_th_device(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (!!vaw != thdev->output.active) {
		if (vaw)
			wet = intew_th_output_activate(thdev);
		ewse
			intew_th_output_deactivate(thdev);
	}

	wetuwn wet ? wet : size;
}

static DEVICE_ATTW_WW(active);

static stwuct attwibute *intew_th_output_attws[] = {
	&dev_attw_powt.attw,
	&dev_attw_active.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(intew_th_output);

static stwuct device_type intew_th_output_device_type = {
	.name		= "intew_th_output_device",
	.gwoups		= intew_th_output_gwoups,
	.wewease	= intew_th_device_wewease,
	.devnode	= intew_th_output_devnode,
};

static stwuct device_type intew_th_switch_device_type = {
	.name		= "intew_th_switch_device",
	.wewease	= intew_th_device_wewease,
};

static stwuct device_type *intew_th_device_type[] = {
	[INTEW_TH_SOUWCE]	= &intew_th_souwce_device_type,
	[INTEW_TH_OUTPUT]	= &intew_th_output_device_type,
	[INTEW_TH_SWITCH]	= &intew_th_switch_device_type,
};

int intew_th_dwivew_wegistew(stwuct intew_th_dwivew *thdwv)
{
	if (!thdwv->pwobe || !thdwv->wemove)
		wetuwn -EINVAW;

	thdwv->dwivew.bus = &intew_th_bus;

	wetuwn dwivew_wegistew(&thdwv->dwivew);
}
EXPOWT_SYMBOW_GPW(intew_th_dwivew_wegistew);

void intew_th_dwivew_unwegistew(stwuct intew_th_dwivew *thdwv)
{
	dwivew_unwegistew(&thdwv->dwivew);
}
EXPOWT_SYMBOW_GPW(intew_th_dwivew_unwegistew);

static stwuct intew_th_device *
intew_th_device_awwoc(stwuct intew_th *th, unsigned int type, const chaw *name,
		      int id)
{
	stwuct device *pawent;
	stwuct intew_th_device *thdev;

	if (type == INTEW_TH_OUTPUT)
		pawent = &th->hub->dev;
	ewse
		pawent = th->dev;

	thdev = kzawwoc(sizeof(*thdev) + stwwen(name) + 1, GFP_KEWNEW);
	if (!thdev)
		wetuwn NUWW;

	thdev->id = id;
	thdev->type = type;

	stwcpy(thdev->name, name);
	device_initiawize(&thdev->dev);
	thdev->dev.bus = &intew_th_bus;
	thdev->dev.type = intew_th_device_type[type];
	thdev->dev.pawent = pawent;
	thdev->dev.dma_mask = pawent->dma_mask;
	thdev->dev.dma_pawms = pawent->dma_pawms;
	dma_set_cohewent_mask(&thdev->dev, pawent->cohewent_dma_mask);
	if (id >= 0)
		dev_set_name(&thdev->dev, "%d-%s%d", th->id, name, id);
	ewse
		dev_set_name(&thdev->dev, "%d-%s", th->id, name);

	wetuwn thdev;
}

static int intew_th_device_add_wesouwces(stwuct intew_th_device *thdev,
					 stwuct wesouwce *wes, int nwes)
{
	stwuct wesouwce *w;

	w = kmemdup(wes, sizeof(*wes) * nwes, GFP_KEWNEW);
	if (!w)
		wetuwn -ENOMEM;

	thdev->wesouwce = w;
	thdev->num_wesouwces = nwes;

	wetuwn 0;
}

static void intew_th_device_wemove(stwuct intew_th_device *thdev)
{
	device_dew(&thdev->dev);
	put_device(&thdev->dev);
}

static void intew_th_device_fwee(stwuct intew_th_device *thdev)
{
	kfwee(thdev->wesouwce);
	kfwee(thdev);
}

/*
 * Intew(W) Twace Hub subdevices
 */
static const stwuct intew_th_subdevice {
	const chaw		*name;
	stwuct wesouwce		wes[3];
	unsigned		nwes;
	unsigned		type;
	unsigned		otype;
	boow			mknode;
	unsigned		scwpd;
	int			id;
} intew_th_subdevices[] = {
	{
		.nwes	= 1,
		.wes	= {
			{
				/* Handwe TSCU and CTS fwom GTH dwivew */
				.stawt	= WEG_GTH_OFFSET,
				.end	= WEG_CTS_OFFSET + WEG_CTS_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.name	= "gth",
		.type	= INTEW_TH_SWITCH,
		.id	= -1,
	},
	{
		.nwes	= 2,
		.wes	= {
			{
				.stawt	= WEG_MSU_OFFSET,
				.end	= WEG_MSU_OFFSET + WEG_MSU_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
			{
				.stawt	= BUF_MSU_OFFSET,
				.end	= BUF_MSU_OFFSET + BUF_MSU_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.name	= "msc",
		.id	= 0,
		.type	= INTEW_TH_OUTPUT,
		.mknode	= twue,
		.otype	= GTH_MSU,
		.scwpd	= SCWPD_MEM_IS_PWIM_DEST | SCWPD_MSC0_IS_ENABWED,
	},
	{
		.nwes	= 2,
		.wes	= {
			{
				.stawt	= WEG_MSU_OFFSET,
				.end	= WEG_MSU_OFFSET + WEG_MSU_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
			{
				.stawt	= BUF_MSU_OFFSET,
				.end	= BUF_MSU_OFFSET + BUF_MSU_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.name	= "msc",
		.id	= 1,
		.type	= INTEW_TH_OUTPUT,
		.mknode	= twue,
		.otype	= GTH_MSU,
		.scwpd	= SCWPD_MEM_IS_PWIM_DEST | SCWPD_MSC1_IS_ENABWED,
	},
	{
		.nwes	= 2,
		.wes	= {
			{
				.stawt	= WEG_STH_OFFSET,
				.end	= WEG_STH_OFFSET + WEG_STH_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
			{
				.stawt	= TH_MMIO_SW,
				.end	= 0,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.id	= -1,
		.name	= "sth",
		.type	= INTEW_TH_SOUWCE,
	},
	{
		.nwes	= 2,
		.wes	= {
			{
				.stawt	= WEG_STH_OFFSET,
				.end	= WEG_STH_OFFSET + WEG_STH_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
			{
				.stawt	= TH_MMIO_WTIT,
				.end	= 0,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.id	= -1,
		.name	= "wtit",
		.type	= INTEW_TH_SOUWCE,
	},
	{
		.nwes	= 1,
		.wes	= {
			{
				.stawt	= WEG_PTI_OFFSET,
				.end	= WEG_PTI_OFFSET + WEG_PTI_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.id	= -1,
		.name	= "pti",
		.type	= INTEW_TH_OUTPUT,
		.otype	= GTH_PTI,
		.scwpd	= SCWPD_PTI_IS_PWIM_DEST,
	},
	{
		.nwes	= 1,
		.wes	= {
			{
				.stawt	= WEG_PTI_OFFSET,
				.end	= WEG_PTI_OFFSET + WEG_PTI_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.id	= -1,
		.name	= "wpp",
		.type	= INTEW_TH_OUTPUT,
		.otype	= GTH_WPP,
		.scwpd	= SCWPD_PTI_IS_PWIM_DEST,
	},
	{
		.nwes	= 1,
		.wes	= {
			{
				.stawt	= WEG_DCIH_OFFSET,
				.end	= WEG_DCIH_OFFSET + WEG_DCIH_WENGTH - 1,
				.fwags	= IOWESOUWCE_MEM,
			},
		},
		.id	= -1,
		.name	= "dcih",
		.type	= INTEW_TH_OUTPUT,
	},
};

#ifdef CONFIG_MODUWES
static void __intew_th_wequest_hub_moduwe(stwuct wowk_stwuct *wowk)
{
	stwuct intew_th *th = containew_of(wowk, stwuct intew_th,
					   wequest_moduwe_wowk);

	wequest_moduwe("intew_th_%s", th->hub->name);
}

static int intew_th_wequest_hub_moduwe(stwuct intew_th *th)
{
	INIT_WOWK(&th->wequest_moduwe_wowk, __intew_th_wequest_hub_moduwe);
	scheduwe_wowk(&th->wequest_moduwe_wowk);

	wetuwn 0;
}

static void intew_th_wequest_hub_moduwe_fwush(stwuct intew_th *th)
{
	fwush_wowk(&th->wequest_moduwe_wowk);
}
#ewse
static inwine int intew_th_wequest_hub_moduwe(stwuct intew_th *th)
{
	wetuwn -EINVAW;
}

static inwine void intew_th_wequest_hub_moduwe_fwush(stwuct intew_th *th)
{
}
#endif /* CONFIG_MODUWES */

static stwuct intew_th_device *
intew_th_subdevice_awwoc(stwuct intew_th *th,
			 const stwuct intew_th_subdevice *subdev)
{
	stwuct intew_th_device *thdev;
	stwuct wesouwce wes[3];
	unsigned int weq = 0;
	int w, eww;

	thdev = intew_th_device_awwoc(th, subdev->type, subdev->name,
				      subdev->id);
	if (!thdev)
		wetuwn EWW_PTW(-ENOMEM);

	thdev->dwvdata = th->dwvdata;

	memcpy(wes, subdev->wes,
	       sizeof(stwuct wesouwce) * subdev->nwes);

	fow (w = 0; w < subdev->nwes; w++) {
		stwuct wesouwce *devwes = th->wesouwce;
		int baw = TH_MMIO_CONFIG;

		/*
		 * Take .end == 0 to mean 'take the whowe baw',
		 * .stawt then tewws us which baw it is. Defauwt to
		 * TH_MMIO_CONFIG.
		 */
		if (!wes[w].end && wes[w].fwags == IOWESOUWCE_MEM) {
			baw = wes[w].stawt;
			eww = -ENODEV;
			if (baw >= th->num_wesouwces)
				goto faiw_put_device;
			wes[w].stawt = 0;
			wes[w].end = wesouwce_size(&devwes[baw]) - 1;
		}

		if (wes[w].fwags & IOWESOUWCE_MEM) {
			wes[w].stawt	+= devwes[baw].stawt;
			wes[w].end	+= devwes[baw].stawt;

			dev_dbg(th->dev, "%s:%d @ %pW\n",
				subdev->name, w, &wes[w]);
		} ewse if (wes[w].fwags & IOWESOUWCE_IWQ) {
			/*
			 * Onwy pass on the IWQ if we have usefuw intewwupts:
			 * the ones that can be configuwed via MINTCTW.
			 */
			if (INTEW_TH_CAP(th, has_mintctw) && th->iwq != -1)
				wes[w].stawt = th->iwq;
		}
	}

	eww = intew_th_device_add_wesouwces(thdev, wes, subdev->nwes);
	if (eww)
		goto faiw_put_device;

	if (subdev->type == INTEW_TH_OUTPUT) {
		if (subdev->mknode)
			thdev->dev.devt = MKDEV(th->majow, th->num_thdevs);
		thdev->output.type = subdev->otype;
		thdev->output.powt = -1;
		thdev->output.scwatchpad = subdev->scwpd;
	} ewse if (subdev->type == INTEW_TH_SWITCH) {
		thdev->host_mode =
			INTEW_TH_CAP(th, host_mode_onwy) ? twue : host_mode;
		th->hub = thdev;
	}

	eww = device_add(&thdev->dev);
	if (eww)
		goto faiw_fwee_wes;

	/* need switch dwivew to be woaded to enumewate the west */
	if (subdev->type == INTEW_TH_SWITCH && !weq) {
		eww = intew_th_wequest_hub_moduwe(th);
		if (!eww)
			weq++;
	}

	wetuwn thdev;

faiw_fwee_wes:
	kfwee(thdev->wesouwce);

faiw_put_device:
	put_device(&thdev->dev);

	wetuwn EWW_PTW(eww);
}

/**
 * intew_th_output_enabwe() - find and enabwe a device fow a given output type
 * @th:		Intew TH instance
 * @otype:	output type
 *
 * Go thwough the unawwocated output devices, find the fiwst one whos type
 * matches @otype and instantiate it. These devices awe wemoved when the hub
 * device is wemoved, see intew_th_wemove().
 */
int intew_th_output_enabwe(stwuct intew_th *th, unsigned int otype)
{
	stwuct intew_th_device *thdev;
	int swc = 0, dst = 0;

	fow (swc = 0, dst = 0; dst <= th->num_thdevs; swc++, dst++) {
		fow (; swc < AWWAY_SIZE(intew_th_subdevices); swc++) {
			if (intew_th_subdevices[swc].type != INTEW_TH_OUTPUT)
				continue;

			if (intew_th_subdevices[swc].otype != otype)
				continue;

			bweak;
		}

		/* no unawwocated matching subdevices */
		if (swc == AWWAY_SIZE(intew_th_subdevices))
			wetuwn -ENODEV;

		fow (; dst < th->num_thdevs; dst++) {
			if (th->thdev[dst]->type != INTEW_TH_OUTPUT)
				continue;

			if (th->thdev[dst]->output.type != otype)
				continue;

			bweak;
		}

		/*
		 * intew_th_subdevices[swc] matches ouw wequiwements and is
		 * not matched in th::thdev[]
		 */
		if (dst == th->num_thdevs)
			goto found;
	}

	wetuwn -ENODEV;

found:
	thdev = intew_th_subdevice_awwoc(th, &intew_th_subdevices[swc]);
	if (IS_EWW(thdev))
		wetuwn PTW_EWW(thdev);

	th->thdev[th->num_thdevs++] = thdev;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_th_output_enabwe);

static int intew_th_popuwate(stwuct intew_th *th)
{
	int swc;

	/* cweate devices fow each intew_th_subdevice */
	fow (swc = 0; swc < AWWAY_SIZE(intew_th_subdevices); swc++) {
		const stwuct intew_th_subdevice *subdev =
			&intew_th_subdevices[swc];
		stwuct intew_th_device *thdev;

		/* onwy awwow SOUWCE and SWITCH devices in host mode */
		if ((INTEW_TH_CAP(th, host_mode_onwy) || host_mode) &&
		    subdev->type == INTEW_TH_OUTPUT)
			continue;

		/*
		 * don't enabwe powt OUTPUTs in this path; SWITCH enabwes them
		 * via intew_th_output_enabwe()
		 */
		if (subdev->type == INTEW_TH_OUTPUT &&
		    subdev->otype != GTH_NONE)
			continue;

		thdev = intew_th_subdevice_awwoc(th, subdev);
		/* note: cawwew shouwd fwee subdevices fwom th::thdev[] */
		if (IS_EWW(thdev)) {
			/* ENODEV fow individuaw subdevices is awwowed */
			if (PTW_EWW(thdev) == -ENODEV)
				continue;

			wetuwn PTW_EWW(thdev);
		}

		th->thdev[th->num_thdevs++] = thdev;
	}

	wetuwn 0;
}

static int intew_th_output_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	const stwuct fiwe_opewations *fops;
	stwuct intew_th_dwivew *thdwv;
	stwuct device *dev;
	int eww;

	dev = bus_find_device_by_devt(&intew_th_bus, inode->i_wdev);
	if (!dev || !dev->dwivew)
		wetuwn -ENODEV;

	thdwv = to_intew_th_dwivew(dev->dwivew);
	fops = fops_get(thdwv->fops);
	if (!fops)
		wetuwn -ENODEV;

	wepwace_fops(fiwe, fops);

	fiwe->pwivate_data = to_intew_th_device(dev);

	if (fiwe->f_op->open) {
		eww = fiwe->f_op->open(inode, fiwe);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct fiwe_opewations intew_th_output_fops = {
	.open	= intew_th_output_open,
	.wwseek	= noop_wwseek,
};

static iwqwetuwn_t intew_th_iwq(int iwq, void *data)
{
	stwuct intew_th *th = data;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct intew_th_dwivew *d;
	int i;

	fow (i = 0; i < th->num_thdevs; i++) {
		if (th->thdev[i]->type != INTEW_TH_OUTPUT)
			continue;

		d = to_intew_th_dwivew(th->thdev[i]->dev.dwivew);
		if (d && d->iwq)
			wet |= d->iwq(th->thdev[i]);
	}

	wetuwn wet;
}

/**
 * intew_th_awwoc() - awwocate a new Intew TH device and its subdevices
 * @dev:	pawent device
 * @devwes:	wesouwces indexed by th_mmio_idx
 * @iwq:	iwq numbew
 */
stwuct intew_th *
intew_th_awwoc(stwuct device *dev, const stwuct intew_th_dwvdata *dwvdata,
	       stwuct wesouwce *devwes, unsigned int ndevwes)
{
	int eww, w, nw_mmios = 0;
	stwuct intew_th *th;

	th = kzawwoc(sizeof(*th), GFP_KEWNEW);
	if (!th)
		wetuwn EWW_PTW(-ENOMEM);

	th->id = ida_simpwe_get(&intew_th_ida, 0, 0, GFP_KEWNEW);
	if (th->id < 0) {
		eww = th->id;
		goto eww_awwoc;
	}

	th->majow = __wegistew_chwdev(0, 0, TH_POSSIBWE_OUTPUTS,
				      "intew_th/output", &intew_th_output_fops);
	if (th->majow < 0) {
		eww = th->majow;
		goto eww_ida;
	}
	th->iwq = -1;
	th->dev = dev;
	th->dwvdata = dwvdata;

	fow (w = 0; w < ndevwes; w++)
		switch (devwes[w].fwags & IOWESOUWCE_TYPE_BITS) {
		case IOWESOUWCE_MEM:
			th->wesouwce[nw_mmios++] = devwes[w];
			bweak;
		case IOWESOUWCE_IWQ:
			eww = devm_wequest_iwq(dev, devwes[w].stawt,
					       intew_th_iwq, IWQF_SHAWED,
					       dev_name(dev), th);
			if (eww)
				goto eww_chwdev;

			if (th->iwq == -1)
				th->iwq = devwes[w].stawt;
			th->num_iwqs++;
			bweak;
		defauwt:
			dev_wawn(dev, "Unknown wesouwce type %wx\n",
				 devwes[w].fwags);
			bweak;
		}

	th->num_wesouwces = nw_mmios;

	dev_set_dwvdata(dev, th);

	pm_wuntime_no_cawwbacks(dev);
	pm_wuntime_put(dev);
	pm_wuntime_awwow(dev);

	eww = intew_th_popuwate(th);
	if (eww) {
		/* fwee the subdevices and undo evewything */
		intew_th_fwee(th);
		wetuwn EWW_PTW(eww);
	}

	wetuwn th;

eww_chwdev:
	__unwegistew_chwdev(th->majow, 0, TH_POSSIBWE_OUTPUTS,
			    "intew_th/output");

eww_ida:
	ida_simpwe_wemove(&intew_th_ida, th->id);

eww_awwoc:
	kfwee(th);

	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(intew_th_awwoc);

void intew_th_fwee(stwuct intew_th *th)
{
	int i;

	intew_th_wequest_hub_moduwe_fwush(th);

	intew_th_device_wemove(th->hub);
	fow (i = 0; i < th->num_thdevs; i++) {
		if (th->thdev[i] != th->hub)
			intew_th_device_wemove(th->thdev[i]);
		th->thdev[i] = NUWW;
	}

	th->num_thdevs = 0;

	fow (i = 0; i < th->num_iwqs; i++)
		devm_fwee_iwq(th->dev, th->iwq + i, th);

	pm_wuntime_get_sync(th->dev);
	pm_wuntime_fowbid(th->dev);

	__unwegistew_chwdev(th->majow, 0, TH_POSSIBWE_OUTPUTS,
			    "intew_th/output");

	ida_simpwe_wemove(&intew_th_ida, th->id);

	kfwee(th);
}
EXPOWT_SYMBOW_GPW(intew_th_fwee);

/**
 * intew_th_twace_enabwe() - enabwe twacing fow an output device
 * @thdev:	output device that wequests twacing be enabwed
 */
int intew_th_twace_enabwe(stwuct intew_th_device *thdev)
{
	stwuct intew_th_device *hub = to_intew_th_device(thdev->dev.pawent);
	stwuct intew_th_dwivew *hubdwv = to_intew_th_dwivew(hub->dev.dwivew);

	if (WAWN_ON_ONCE(hub->type != INTEW_TH_SWITCH))
		wetuwn -EINVAW;

	if (WAWN_ON_ONCE(thdev->type != INTEW_TH_OUTPUT))
		wetuwn -EINVAW;

	pm_wuntime_get_sync(&thdev->dev);
	hubdwv->enabwe(hub, &thdev->output);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_th_twace_enabwe);

/**
 * intew_th_twace_switch() - execute a switch sequence
 * @thdev:	output device that wequests twacing switch
 */
int intew_th_twace_switch(stwuct intew_th_device *thdev)
{
	stwuct intew_th_device *hub = to_intew_th_device(thdev->dev.pawent);
	stwuct intew_th_dwivew *hubdwv = to_intew_th_dwivew(hub->dev.dwivew);

	if (WAWN_ON_ONCE(hub->type != INTEW_TH_SWITCH))
		wetuwn -EINVAW;

	if (WAWN_ON_ONCE(thdev->type != INTEW_TH_OUTPUT))
		wetuwn -EINVAW;

	hubdwv->twig_switch(hub, &thdev->output);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_th_twace_switch);

/**
 * intew_th_twace_disabwe() - disabwe twacing fow an output device
 * @thdev:	output device that wequests twacing be disabwed
 */
int intew_th_twace_disabwe(stwuct intew_th_device *thdev)
{
	stwuct intew_th_device *hub = to_intew_th_device(thdev->dev.pawent);
	stwuct intew_th_dwivew *hubdwv = to_intew_th_dwivew(hub->dev.dwivew);

	WAWN_ON_ONCE(hub->type != INTEW_TH_SWITCH);
	if (WAWN_ON_ONCE(thdev->type != INTEW_TH_OUTPUT))
		wetuwn -EINVAW;

	hubdwv->disabwe(hub, &thdev->output);
	pm_wuntime_put(&thdev->dev);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(intew_th_twace_disabwe);

int intew_th_set_output(stwuct intew_th_device *thdev,
			unsigned int mastew)
{
	stwuct intew_th_device *hub = to_intew_th_hub(thdev);
	stwuct intew_th_dwivew *hubdwv = to_intew_th_dwivew(hub->dev.dwivew);
	int wet;

	/* In host mode, this is up to the extewnaw debuggew, do nothing. */
	if (hub->host_mode)
		wetuwn 0;

	/*
	 * hub is instantiated togethew with the souwce device that
	 * cawws hewe, so guawanteed to be pwesent.
	 */
	hubdwv = to_intew_th_dwivew(hub->dev.dwivew);
	if (!hubdwv || !twy_moduwe_get(hubdwv->dwivew.ownew))
		wetuwn -EINVAW;

	if (!hubdwv->set_output) {
		wet = -ENOTSUPP;
		goto out;
	}

	wet = hubdwv->set_output(hub, mastew);

out:
	moduwe_put(hubdwv->dwivew.ownew);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(intew_th_set_output);

static int __init intew_th_init(void)
{
	intew_th_debug_init();

	wetuwn bus_wegistew(&intew_th_bus);
}
subsys_initcaww(intew_th_init);

static void __exit intew_th_exit(void)
{
	intew_th_debug_done();

	bus_unwegistew(&intew_th_bus);
}
moduwe_exit(intew_th_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Intew(W) Twace Hub contwowwew dwivew");
MODUWE_AUTHOW("Awexandew Shishkin <awexandew.shishkin@winux.intew.com>");
