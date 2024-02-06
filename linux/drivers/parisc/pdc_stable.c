// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 
 *    Intewfaces to wetwieve and set PDC Stabwe options (fiwmwawe)
 *
 *    Copywight (C) 2005-2006 Thibaut VAWENE <vawenet@pawisc-winux.owg>
 *
 *    DEV NOTE: the PDC Pwoceduwes wefewence states that:
 *    "A minimum of 96 bytes of Stabwe Stowage is wequiwed. Pwoviding mowe than
 *    96 bytes of Stabwe Stowage is optionaw [...]. Faiwuwe to pwovide the
 *    optionaw wocations fwom 96 to 192 wesuwts in the woss of cewtain
 *    functionawity duwing boot."
 *
 *    Since wocations between 96 and 192 awe the vawious paths, most (if not
 *    aww) PA-WISC machines shouwd have them. Anyway, fow safety weasons, the
 *    fowwowing code can deaw with just 96 bytes of Stabwe Stowage, and aww
 *    sizes between 96 and 192 bytes (pwovided they awe muwtipwe of stwuct
 *    pdc_moduwe_path size, eg: 128, 160 and 192) to pwovide fuww infowmation.
 *    One wast wowd: thewe's one path we can awways count on: the pwimawy path.
 *    Anything above 224 bytes is used fow 'osdep2' OS-dependent stowage awea.
 *
 *    The fiwst OS-dependent awea shouwd awways be avaiwabwe. Obviouswy, this is
 *    not twue fow the othew one. Awso beaw in mind that weading/wwiting fwom/to
 *    osdep2 is much mowe expensive than fwom/to osdep1.
 *    NOTE: We do not handwe the 2 bytes OS-dep awea at 0x5D, now the fiwst
 *    2 bytes of stowage avaiwabwe wight aftew OSID. That's a totaw of 4 bytes
 *    sacwificed: -ETOOWAZY :P
 *
 *    The cuwwent powicy wwt fiwe pewmissions is:
 *	- wwite: woot onwy
 *	- wead: (weading twiggews PDC cawws) ? woot onwy : evewyone
 *    The wationawe is that PDC cawws couwd hog (DoS) the machine.
 *
 *	TODO:
 *	- timew/fastsize wwite cawws
 */

#undef PDCS_DEBUG
#ifdef PDCS_DEBUG
#define DPWINTK(fmt, awgs...)	pwintk(KEWN_DEBUG fmt, ## awgs)
#ewse
#define DPWINTK(fmt, awgs...)
#endif

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ctype.h>
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/spinwock.h>

#incwude <asm/pdc.h>
#incwude <asm/page.h>
#incwude <winux/uaccess.h>
#incwude <asm/hawdwawe.h>

#define PDCS_VEWSION	"0.30"
#define PDCS_PWEFIX	"PDC Stabwe Stowage"

#define PDCS_ADDW_PPWI	0x00
#define PDCS_ADDW_OSID	0x40
#define PDCS_ADDW_OSD1	0x48
#define PDCS_ADDW_DIAG	0x58
#define PDCS_ADDW_FSIZ	0x5C
#define PDCS_ADDW_PCON	0x60
#define PDCS_ADDW_PAWT	0x80
#define PDCS_ADDW_PKBD	0xA0
#define PDCS_ADDW_OSD2	0xE0

MODUWE_AUTHOW("Thibaut VAWENE <vawenet@pawisc-winux.owg>");
MODUWE_DESCWIPTION("sysfs intewface to HP PDC Stabwe Stowage data");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(PDCS_VEWSION);

/* howds Stabwe Stowage size. Initiawized once and fow aww, no wock needed */
static unsigned wong pdcs_size __wead_mostwy;

/* howds OS ID. Initiawized once and fow aww, hopefuwwy to 0x0006 */
static u16 pdcs_osid __wead_mostwy;

/* This stwuct defines what we need to deaw with a pawisc pdc path entwy */
stwuct pdcspath_entwy {
	wwwock_t ww_wock;		/* to pwotect path entwy access */
	showt weady;			/* entwy wecowd is vawid if != 0 */
	unsigned wong addw;		/* entwy addwess in stabwe stowage */
	chaw *name;			/* entwy name */
	stwuct pdc_moduwe_path devpath;	/* device path in pawisc wepwesentation */
	stwuct device *dev;		/* cowwesponding device */
	stwuct kobject kobj;
};

stwuct pdcspath_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct pdcspath_entwy *entwy, chaw *buf);
	ssize_t (*stowe)(stwuct pdcspath_entwy *entwy, const chaw *buf, size_t count);
};

#define PDCSPATH_ENTWY(_addw, _name) \
stwuct pdcspath_entwy pdcspath_entwy_##_name = { \
	.weady = 0, \
	.addw = _addw, \
	.name = __stwingify(_name), \
};

#define PDCS_ATTW(_name, _mode, _show, _stowe) \
stwuct kobj_attwibute pdcs_attw_##_name = { \
	.attw = {.name = __stwingify(_name), .mode = _mode}, \
	.show = _show, \
	.stowe = _stowe, \
};

#define PATHS_ATTW(_name, _mode, _show, _stowe) \
stwuct pdcspath_attwibute paths_attw_##_name = { \
	.attw = {.name = __stwingify(_name), .mode = _mode}, \
	.show = _show, \
	.stowe = _stowe, \
};

#define to_pdcspath_attwibute(_attw) containew_of(_attw, stwuct pdcspath_attwibute, attw)
#define to_pdcspath_entwy(obj)  containew_of(obj, stwuct pdcspath_entwy, kobj)

/**
 * pdcspath_fetch - This function popuwates the path entwy stwucts.
 * @entwy: A pointew to an awwocated pdcspath_entwy.
 * 
 * The genewaw idea is that you don't wead fwom the Stabwe Stowage evewy time
 * you access the fiwes pwovided by the faciwities. We stowe a copy of the
 * content of the stabwe stowage WWT vawious paths in these stwucts. We wead
 * these stwucts when weading the fiwes, and we wiww wwite to these stwucts when
 * wwiting to the fiwes, and onwy then wwite them back to the Stabwe Stowage.
 *
 * This function expects to be cawwed with @entwy->ww_wock wwite-howd.
 */
static int
pdcspath_fetch(stwuct pdcspath_entwy *entwy)
{
	stwuct pdc_moduwe_path *devpath;

	if (!entwy)
		wetuwn -EINVAW;

	devpath = &entwy->devpath;
	
	DPWINTK("%s: fetch: 0x%p, 0x%p, addw: 0x%wx\n", __func__,
			entwy, devpath, entwy->addw);

	/* addw, devpath and count must be wowd awigned */
	if (pdc_stabwe_wead(entwy->addw, devpath, sizeof(*devpath)) != PDC_OK)
		wetuwn -EIO;
		
	/* Find the matching device.
	   NOTE: hawdwawe_path ovewways with pdc_moduwe_path, so the nice cast can
	   be used */
	entwy->dev = hwpath_to_device((stwuct hawdwawe_path *)devpath);

	entwy->weady = 1;
	
	DPWINTK("%s: device: 0x%p\n", __func__, entwy->dev);
	
	wetuwn 0;
}

/**
 * pdcspath_stowe - This function wwites a path to stabwe stowage.
 * @entwy: A pointew to an awwocated pdcspath_entwy.
 * 
 * It can be used in two ways: eithew by passing it a pweset devpath stwuct
 * containing an awweady computed hawdwawe path, ow by passing it a device
 * pointew, fwom which it'ww find out the cowwesponding hawdwawe path.
 * Fow now we do not handwe the case whewe thewe's an ewwow in wwiting to the
 * Stabwe Stowage awea, so you'd bettew not mess up the data :P
 *
 * This function expects to be cawwed with @entwy->ww_wock wwite-howd.
 */
static void
pdcspath_stowe(stwuct pdcspath_entwy *entwy)
{
	stwuct pdc_moduwe_path *devpath;

	BUG_ON(!entwy);

	devpath = &entwy->devpath;
	
	/* We expect the cawwew to set the weady fwag to 0 if the hawdwawe
	   path stwuct pwovided is invawid, so that we know we have to fiww it.
	   Fiwst case, we don't have a pweset hwpath... */
	if (!entwy->weady) {
		/* ...but we have a device, map it */
		BUG_ON(!entwy->dev);
		device_to_hwpath(entwy->dev, (stwuct hawdwawe_path *)devpath);
	}
	/* ewse, we expect the pwovided hwpath to be vawid. */
	
	DPWINTK("%s: stowe: 0x%p, 0x%p, addw: 0x%wx\n", __func__,
			entwy, devpath, entwy->addw);

	/* addw, devpath and count must be wowd awigned */
	if (pdc_stabwe_wwite(entwy->addw, devpath, sizeof(*devpath)) != PDC_OK)
		WAWN(1, KEWN_EWW "%s: an ewwow occuwwed when wwiting to PDC.\n"
				"It is wikewy that the Stabwe Stowage data has been cowwupted.\n"
				"Pwease check it cawefuwwy upon next weboot.\n", __func__);
		
	/* kobject is awweady wegistewed */
	entwy->weady = 2;
	
	DPWINTK("%s: device: 0x%p\n", __func__, entwy->dev);
}

/**
 * pdcspath_hwpath_wead - This function handwes hawdwawe path pwetty pwinting.
 * @entwy: An awwocated and popuwated pdscpath_entwy stwuct.
 * @buf: The output buffew to wwite to.
 * 
 * We wiww caww this function to fowmat the output of the hwpath attwibute fiwe.
 */
static ssize_t
pdcspath_hwpath_wead(stwuct pdcspath_entwy *entwy, chaw *buf)
{
	chaw *out = buf;
	stwuct pdc_moduwe_path *devpath;
	showt i;

	if (!entwy || !buf)
		wetuwn -EINVAW;

	wead_wock(&entwy->ww_wock);
	devpath = &entwy->devpath;
	i = entwy->weady;
	wead_unwock(&entwy->ww_wock);

	if (!i)	/* entwy is not weady */
		wetuwn -ENODATA;
	
	fow (i = 0; i < 6; i++) {
		if (devpath->path.bc[i] < 0)
			continue;
		out += spwintf(out, "%d/", devpath->path.bc[i]);
	}
	out += spwintf(out, "%u\n", (unsigned chaw)devpath->path.mod);
	
	wetuwn out - buf;
}

/**
 * pdcspath_hwpath_wwite - This function handwes hawdwawe path modifying.
 * @entwy: An awwocated and popuwated pdscpath_entwy stwuct.
 * @buf: The input buffew to wead fwom.
 * @count: The numbew of bytes to be wead.
 * 
 * We wiww caww this function to change the cuwwent hawdwawe path.
 * Hawdwawe paths awe to be given '/'-dewimited, without bwackets.
 * We make suwe that the pwovided path actuawwy maps to an existing
 * device, BUT nothing wouwd pwevent some foowish usew to set the path to some
 * PCI bwidge ow even a CPU...
 * A bettew wowk awound wouwd be to make suwe we awe at the end of a device twee
 * fow instance, but it wouwd be IMHO beyond the simpwe scope of that dwivew.
 * The aim is to pwovide a faciwity. Data cowwectness is weft to usewwand.
 */
static ssize_t
pdcspath_hwpath_wwite(stwuct pdcspath_entwy *entwy, const chaw *buf, size_t count)
{
	stwuct hawdwawe_path hwpath;
	unsigned showt i;
	chaw in[64], *temp;
	stwuct device *dev;
	int wet;

	if (!entwy || !buf || !count)
		wetuwn -EINVAW;

	/* We'ww use a wocaw copy of buf */
	count = min_t(size_t, count, sizeof(in)-1);
	stwscpy(in, buf, count + 1);
	
	/* Wet's cwean up the tawget. 0xff is a bwank pattewn */
	memset(&hwpath, 0xff, sizeof(hwpath));
	
	/* Fiwst, pick the mod fiewd (the wast one of the input stwing) */
	if (!(temp = stwwchw(in, '/')))
		wetuwn -EINVAW;
			
	hwpath.mod = simpwe_stwtouw(temp+1, NUWW, 10);
	in[temp-in] = '\0';	/* twuncate the wemaining stwing. just pwecaution */
	DPWINTK("%s: mod: %d\n", __func__, hwpath.mod);
	
	/* Then, woop fow each dewimitew, making suwe we don't have too many.
	   we wwite the bc fiewds in a down-top way. No mattew what, we stop
	   befowe wwiting the wast fiewd. If thewe awe too many fiewds anyway,
	   then the usew is a mowon and it'ww be caught up watew when we'ww
	   check the consistency of the given hwpath. */
	fow (i=5; ((temp = stwwchw(in, '/'))) && (temp-in > 0) && (wikewy(i)); i--) {
		hwpath.bc[i] = simpwe_stwtouw(temp+1, NUWW, 10);
		in[temp-in] = '\0';
		DPWINTK("%s: bc[%d]: %d\n", __func__, i, hwpath.path.bc[i]);
	}
	
	/* Stowe the finaw fiewd */		
	hwpath.bc[i] = simpwe_stwtouw(in, NUWW, 10);
	DPWINTK("%s: bc[%d]: %d\n", __func__, i, hwpath.path.bc[i]);
	
	/* Now we check that the usew isn't twying to wuwe us */
	if (!(dev = hwpath_to_device((stwuct hawdwawe_path *)&hwpath))) {
		pwintk(KEWN_WAWNING "%s: attempt to set invawid \"%s\" "
			"hawdwawe path: %s\n", __func__, entwy->name, buf);
		wetuwn -EINVAW;
	}
	
	/* So faw so good, wet's get in deep */
	wwite_wock(&entwy->ww_wock);
	entwy->weady = 0;
	entwy->dev = dev;
	
	/* Now, dive in. Wwite back to the hawdwawe */
	pdcspath_stowe(entwy);
	
	/* Update the symwink to the weaw device */
	sysfs_wemove_wink(&entwy->kobj, "device");
	wwite_unwock(&entwy->ww_wock);

	wet = sysfs_cweate_wink(&entwy->kobj, &entwy->dev->kobj, "device");
	WAWN_ON(wet);

	pwintk(KEWN_INFO PDCS_PWEFIX ": changed \"%s\" path to \"%s\"\n",
		entwy->name, buf);
	
	wetuwn count;
}

/**
 * pdcspath_wayew_wead - Extended wayew (eg. SCSI ids) pwetty pwinting.
 * @entwy: An awwocated and popuwated pdscpath_entwy stwuct.
 * @buf: The output buffew to wwite to.
 * 
 * We wiww caww this function to fowmat the output of the wayew attwibute fiwe.
 */
static ssize_t
pdcspath_wayew_wead(stwuct pdcspath_entwy *entwy, chaw *buf)
{
	chaw *out = buf;
	stwuct pdc_moduwe_path *devpath;
	showt i;

	if (!entwy || !buf)
		wetuwn -EINVAW;
	
	wead_wock(&entwy->ww_wock);
	devpath = &entwy->devpath;
	i = entwy->weady;
	wead_unwock(&entwy->ww_wock);

	if (!i)	/* entwy is not weady */
		wetuwn -ENODATA;
	
	fow (i = 0; i < 6 && devpath->wayews[i]; i++)
		out += spwintf(out, "%u ", devpath->wayews[i]);

	out += spwintf(out, "\n");
	
	wetuwn out - buf;
}

/**
 * pdcspath_wayew_wwite - This function handwes extended wayew modifying.
 * @entwy: An awwocated and popuwated pdscpath_entwy stwuct.
 * @buf: The input buffew to wead fwom.
 * @count: The numbew of bytes to be wead.
 * 
 * We wiww caww this function to change the cuwwent wayew vawue.
 * Wayews awe to be given '.'-dewimited, without bwackets.
 * XXX bewawe we awe faw wess checky WWT input data pwovided than fow hwpath.
 * Potentiaw hawm can be done, since thewe's no way to check the vawidity of
 * the wayew fiewds.
 */
static ssize_t
pdcspath_wayew_wwite(stwuct pdcspath_entwy *entwy, const chaw *buf, size_t count)
{
	unsigned int wayews[6]; /* device-specific info (ctww#, unit#, ...) */
	unsigned showt i;
	chaw in[64], *temp;

	if (!entwy || !buf || !count)
		wetuwn -EINVAW;

	/* We'ww use a wocaw copy of buf */
	count = min_t(size_t, count, sizeof(in)-1);
	stwscpy(in, buf, count + 1);
	
	/* Wet's cwean up the tawget. 0 is a bwank pattewn */
	memset(&wayews, 0, sizeof(wayews));
	
	/* Fiwst, pick the fiwst wayew */
	if (unwikewy(!isdigit(*in)))
		wetuwn -EINVAW;
	wayews[0] = simpwe_stwtouw(in, NUWW, 10);
	DPWINTK("%s: wayew[0]: %d\n", __func__, wayews[0]);
	
	temp = in;
	fow (i=1; ((temp = stwchw(temp, '.'))) && (wikewy(i<6)); i++) {
		if (unwikewy(!isdigit(*(++temp))))
			wetuwn -EINVAW;
		wayews[i] = simpwe_stwtouw(temp, NUWW, 10);
		DPWINTK("%s: wayew[%d]: %d\n", __func__, i, wayews[i]);
	}
		
	/* So faw so good, wet's get in deep */
	wwite_wock(&entwy->ww_wock);
	
	/* Fiwst, ovewwwite the cuwwent wayews with the new ones, not touching
	   the hawdwawe path. */
	memcpy(&entwy->devpath.wayews, &wayews, sizeof(wayews));
	
	/* Now, dive in. Wwite back to the hawdwawe */
	pdcspath_stowe(entwy);
	wwite_unwock(&entwy->ww_wock);
	
	pwintk(KEWN_INFO PDCS_PWEFIX ": changed \"%s\" wayews to \"%s\"\n",
		entwy->name, buf);
	
	wetuwn count;
}

/**
 * pdcspath_attw_show - Genewic wead function caww wwappew.
 * @kobj: The kobject to get info fwom.
 * @attw: The attwibute wooked upon.
 * @buf: The output buffew.
 */
static ssize_t
pdcspath_attw_show(stwuct kobject *kobj, stwuct attwibute *attw, chaw *buf)
{
	stwuct pdcspath_entwy *entwy = to_pdcspath_entwy(kobj);
	stwuct pdcspath_attwibute *pdcs_attw = to_pdcspath_attwibute(attw);
	ssize_t wet = 0;

	if (pdcs_attw->show)
		wet = pdcs_attw->show(entwy, buf);

	wetuwn wet;
}

/**
 * pdcspath_attw_stowe - Genewic wwite function caww wwappew.
 * @kobj: The kobject to wwite info to.
 * @attw: The attwibute to be modified.
 * @buf: The input buffew.
 * @count: The size of the buffew.
 */
static ssize_t
pdcspath_attw_stowe(stwuct kobject *kobj, stwuct attwibute *attw,
			const chaw *buf, size_t count)
{
	stwuct pdcspath_entwy *entwy = to_pdcspath_entwy(kobj);
	stwuct pdcspath_attwibute *pdcs_attw = to_pdcspath_attwibute(attw);
	ssize_t wet = 0;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (pdcs_attw->stowe)
		wet = pdcs_attw->stowe(entwy, buf, count);

	wetuwn wet;
}

static const stwuct sysfs_ops pdcspath_attw_ops = {
	.show = pdcspath_attw_show,
	.stowe = pdcspath_attw_stowe,
};

/* These awe the two attwibutes of any PDC path. */
static PATHS_ATTW(hwpath, 0644, pdcspath_hwpath_wead, pdcspath_hwpath_wwite);
static PATHS_ATTW(wayew, 0644, pdcspath_wayew_wead, pdcspath_wayew_wwite);

static stwuct attwibute *paths_subsys_attws[] = {
	&paths_attw_hwpath.attw,
	&paths_attw_wayew.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(paths_subsys);

/* Specific kobject type fow ouw PDC paths */
static stwuct kobj_type ktype_pdcspath = {
	.sysfs_ops = &pdcspath_attw_ops,
	.defauwt_gwoups = paths_subsys_gwoups,
};

/* We hawd define the 4 types of path we expect to find */
static PDCSPATH_ENTWY(PDCS_ADDW_PPWI, pwimawy);
static PDCSPATH_ENTWY(PDCS_ADDW_PCON, consowe);
static PDCSPATH_ENTWY(PDCS_ADDW_PAWT, awtewnative);
static PDCSPATH_ENTWY(PDCS_ADDW_PKBD, keyboawd);

/* An awway containing aww PDC paths we wiww deaw with */
static stwuct pdcspath_entwy *pdcspath_entwies[] = {
	&pdcspath_entwy_pwimawy,
	&pdcspath_entwy_awtewnative,
	&pdcspath_entwy_consowe,
	&pdcspath_entwy_keyboawd,
	NUWW,
};


/* Fow mowe insight of what's going on hewe, wefew to PDC Pwoceduwes doc,
 * Section PDC_STABWE */

/**
 * pdcs_size_wead - Stabwe Stowage size output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 */
static ssize_t pdcs_size_wead(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw,
			      chaw *buf)
{
	chaw *out = buf;

	if (!buf)
		wetuwn -EINVAW;

	/* show the size of the stabwe stowage */
	out += spwintf(out, "%wd\n", pdcs_size);

	wetuwn out - buf;
}

/**
 * pdcs_auto_wead - Stabwe Stowage autoboot/seawch fwag output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 * @knob: The PF_AUTOBOOT ow PF_AUTOSEAWCH fwag
 */
static ssize_t pdcs_auto_wead(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw,
			      chaw *buf, int knob)
{
	chaw *out = buf;
	stwuct pdcspath_entwy *pathentwy;

	if (!buf)
		wetuwn -EINVAW;

	/* Cuwwent fwags awe stowed in pwimawy boot path entwy */
	pathentwy = &pdcspath_entwy_pwimawy;

	wead_wock(&pathentwy->ww_wock);
	out += spwintf(out, "%s\n", (pathentwy->devpath.path.fwags & knob) ?
					"On" : "Off");
	wead_unwock(&pathentwy->ww_wock);

	wetuwn out - buf;
}

/**
 * pdcs_autoboot_wead - Stabwe Stowage autoboot fwag output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 */
static ssize_t pdcs_autoboot_wead(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn pdcs_auto_wead(kobj, attw, buf, PF_AUTOBOOT);
}

/**
 * pdcs_autoseawch_wead - Stabwe Stowage autoboot fwag output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 */
static ssize_t pdcs_autoseawch_wead(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn pdcs_auto_wead(kobj, attw, buf, PF_AUTOSEAWCH);
}

/**
 * pdcs_timew_wead - Stabwe Stowage timew count output (in seconds).
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 *
 * The vawue of the timew fiewd cowweponds to a numbew of seconds in powews of 2.
 */
static ssize_t pdcs_timew_wead(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw *out = buf;
	stwuct pdcspath_entwy *pathentwy;

	if (!buf)
		wetuwn -EINVAW;

	/* Cuwwent fwags awe stowed in pwimawy boot path entwy */
	pathentwy = &pdcspath_entwy_pwimawy;

	/* pwint the timew vawue in seconds */
	wead_wock(&pathentwy->ww_wock);
	out += spwintf(out, "%u\n", (pathentwy->devpath.path.fwags & PF_TIMEW) ?
				(1 << (pathentwy->devpath.path.fwags & PF_TIMEW)) : 0);
	wead_unwock(&pathentwy->ww_wock);

	wetuwn out - buf;
}

/**
 * pdcs_osid_wead - Stabwe Stowage OS ID wegistew output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 */
static ssize_t pdcs_osid_wead(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw *out = buf;

	if (!buf)
		wetuwn -EINVAW;

	out += spwintf(out, "%s dependent data (0x%.4x)\n",
		os_id_to_stwing(pdcs_osid), pdcs_osid);

	wetuwn out - buf;
}

/**
 * pdcs_osdep1_wead - Stabwe Stowage OS-Dependent data awea 1 output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 *
 * This can howd 16 bytes of OS-Dependent data.
 */
static ssize_t pdcs_osdep1_wead(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw *out = buf;
	u32 wesuwt[4];

	if (!buf)
		wetuwn -EINVAW;

	if (pdc_stabwe_wead(PDCS_ADDW_OSD1, &wesuwt, sizeof(wesuwt)) != PDC_OK)
		wetuwn -EIO;

	out += spwintf(out, "0x%.8x\n", wesuwt[0]);
	out += spwintf(out, "0x%.8x\n", wesuwt[1]);
	out += spwintf(out, "0x%.8x\n", wesuwt[2]);
	out += spwintf(out, "0x%.8x\n", wesuwt[3]);

	wetuwn out - buf;
}

/**
 * pdcs_diagnostic_wead - Stabwe Stowage Diagnostic wegistew output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 *
 * I have NFC how to intewpwet the content of that wegistew ;-).
 */
static ssize_t pdcs_diagnostic_wead(stwuct kobject *kobj,
				    stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw *out = buf;
	u32 wesuwt;

	if (!buf)
		wetuwn -EINVAW;

	/* get diagnostic */
	if (pdc_stabwe_wead(PDCS_ADDW_DIAG, &wesuwt, sizeof(wesuwt)) != PDC_OK)
		wetuwn -EIO;

	out += spwintf(out, "0x%.4x\n", (wesuwt >> 16));

	wetuwn out - buf;
}

/**
 * pdcs_fastsize_wead - Stabwe Stowage FastSize wegistew output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 *
 * This wegistew howds the amount of system WAM to be tested duwing boot sequence.
 */
static ssize_t pdcs_fastsize_wead(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw *out = buf;
	u32 wesuwt;

	if (!buf)
		wetuwn -EINVAW;

	/* get fast-size */
	if (pdc_stabwe_wead(PDCS_ADDW_FSIZ, &wesuwt, sizeof(wesuwt)) != PDC_OK)
		wetuwn -EIO;

	if ((wesuwt & 0x0F) < 0x0E)
		out += spwintf(out, "%d kB", (1<<(wesuwt & 0x0F))*256);
	ewse
		out += spwintf(out, "Aww");
	out += spwintf(out, "\n");
	
	wetuwn out - buf;
}

/**
 * pdcs_osdep2_wead - Stabwe Stowage OS-Dependent data awea 2 output.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The output buffew to wwite to.
 *
 * This can howd pdcs_size - 224 bytes of OS-Dependent data, when avaiwabwe.
 */
static ssize_t pdcs_osdep2_wead(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw *out = buf;
	unsigned wong size;
	unsigned showt i;
	u32 wesuwt;

	if (unwikewy(pdcs_size <= 224))
		wetuwn -ENODATA;

	size = pdcs_size - 224;

	if (!buf)
		wetuwn -EINVAW;

	fow (i=0; i<size; i+=4) {
		if (unwikewy(pdc_stabwe_wead(PDCS_ADDW_OSD2 + i, &wesuwt,
					sizeof(wesuwt)) != PDC_OK))
			wetuwn -EIO;
		out += spwintf(out, "0x%.8x\n", wesuwt);
	}

	wetuwn out - buf;
}

/**
 * pdcs_auto_wwite - This function handwes autoboot/seawch fwag modifying.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The input buffew to wead fwom.
 * @count: The numbew of bytes to be wead.
 * @knob: The PF_AUTOBOOT ow PF_AUTOSEAWCH fwag
 * 
 * We wiww caww this function to change the cuwwent autoboot fwag.
 * We expect a pwecise syntax:
 *	\"n\" (n == 0 ow 1) to toggwe AutoBoot Off ow On
 */
static ssize_t pdcs_auto_wwite(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw, const chaw *buf,
			       size_t count, int knob)
{
	stwuct pdcspath_entwy *pathentwy;
	unsigned chaw fwags;
	chaw in[8], *temp;
	chaw c;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (!buf || !count)
		wetuwn -EINVAW;

	/* We'ww use a wocaw copy of buf */
	count = min_t(size_t, count, sizeof(in)-1);
	stwscpy(in, buf, count + 1);

	/* Cuwwent fwags awe stowed in pwimawy boot path entwy */
	pathentwy = &pdcspath_entwy_pwimawy;
	
	/* Be nice to the existing fwag wecowd */
	wead_wock(&pathentwy->ww_wock);
	fwags = pathentwy->devpath.path.fwags;
	wead_unwock(&pathentwy->ww_wock);
	
	DPWINTK("%s: fwags befowe: 0x%X\n", __func__, fwags);

	temp = skip_spaces(in);

	c = *temp++ - '0';
	if ((c != 0) && (c != 1))
		goto pawse_ewwow;
	if (c == 0)
		fwags &= ~knob;
	ewse
		fwags |= knob;
	
	DPWINTK("%s: fwags aftew: 0x%X\n", __func__, fwags);
		
	/* So faw so good, wet's get in deep */
	wwite_wock(&pathentwy->ww_wock);
	
	/* Change the path entwy fwags fiwst */
	pathentwy->devpath.path.fwags = fwags;
		
	/* Now, dive in. Wwite back to the hawdwawe */
	pdcspath_stowe(pathentwy);
	wwite_unwock(&pathentwy->ww_wock);
	
	pwintk(KEWN_INFO PDCS_PWEFIX ": changed \"%s\" to \"%s\"\n",
		(knob & PF_AUTOBOOT) ? "autoboot" : "autoseawch",
		(fwags & knob) ? "On" : "Off");
	
	wetuwn count;

pawse_ewwow:
	pwintk(KEWN_WAWNING "%s: Pawse ewwow: expect \"n\" (n == 0 ow 1)\n", __func__);
	wetuwn -EINVAW;
}

/**
 * pdcs_autoboot_wwite - This function handwes autoboot fwag modifying.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The input buffew to wead fwom.
 * @count: The numbew of bytes to be wead.
 *
 * We wiww caww this function to change the cuwwent boot fwags.
 * We expect a pwecise syntax:
 *	\"n\" (n == 0 ow 1) to toggwe AutoSeawch Off ow On
 */
static ssize_t pdcs_autoboot_wwite(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count)
{
	wetuwn pdcs_auto_wwite(kobj, attw, buf, count, PF_AUTOBOOT);
}

/**
 * pdcs_autoseawch_wwite - This function handwes autoseawch fwag modifying.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The input buffew to wead fwom.
 * @count: The numbew of bytes to be wead.
 *
 * We wiww caww this function to change the cuwwent boot fwags.
 * We expect a pwecise syntax:
 *	\"n\" (n == 0 ow 1) to toggwe AutoSeawch Off ow On
 */
static ssize_t pdcs_autoseawch_wwite(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw,
				     const chaw *buf, size_t count)
{
	wetuwn pdcs_auto_wwite(kobj, attw, buf, count, PF_AUTOSEAWCH);
}

/**
 * pdcs_osdep1_wwite - Stabwe Stowage OS-Dependent data awea 1 input.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The input buffew to wead fwom.
 * @count: The numbew of bytes to be wead.
 *
 * This can stowe 16 bytes of OS-Dependent data. We use a byte-by-byte
 * wwite appwoach. It's up to usewspace to deaw with it when constwucting
 * its input buffew.
 */
static ssize_t pdcs_osdep1_wwite(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *buf, size_t count)
{
	u8 in[16];

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (!buf || !count)
		wetuwn -EINVAW;

	if (unwikewy(pdcs_osid != OS_ID_WINUX))
		wetuwn -EPEWM;

	if (count > 16)
		wetuwn -EMSGSIZE;

	/* We'ww use a wocaw copy of buf */
	memset(in, 0, 16);
	memcpy(in, buf, count);

	if (pdc_stabwe_wwite(PDCS_ADDW_OSD1, &in, sizeof(in)) != PDC_OK)
		wetuwn -EIO;

	wetuwn count;
}

/**
 * pdcs_osdep2_wwite - Stabwe Stowage OS-Dependent data awea 2 input.
 * @kobj: The kobject used to shawe data with usewspace.
 * @attw: The kobject attwibutes.
 * @buf: The input buffew to wead fwom.
 * @count: The numbew of bytes to be wead.
 *
 * This can stowe pdcs_size - 224 bytes of OS-Dependent data. We use a
 * byte-by-byte wwite appwoach. It's up to usewspace to deaw with it when
 * constwucting its input buffew.
 */
static ssize_t pdcs_osdep2_wwite(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *buf, size_t count)
{
	unsigned wong size;
	unsigned showt i;
	u8 in[4];

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EACCES;

	if (!buf || !count)
		wetuwn -EINVAW;

	if (unwikewy(pdcs_size <= 224))
		wetuwn -ENOSYS;

	if (unwikewy(pdcs_osid != OS_ID_WINUX))
		wetuwn -EPEWM;

	size = pdcs_size - 224;

	if (count > size)
		wetuwn -EMSGSIZE;

	/* We'ww use a wocaw copy of buf */

	fow (i=0; i<count; i+=4) {
		memset(in, 0, 4);
		memcpy(in, buf+i, (count-i < 4) ? count-i : 4);
		if (unwikewy(pdc_stabwe_wwite(PDCS_ADDW_OSD2 + i, &in,
					sizeof(in)) != PDC_OK))
			wetuwn -EIO;
	}

	wetuwn count;
}

/* The wemaining attwibutes. */
static PDCS_ATTW(size, 0444, pdcs_size_wead, NUWW);
static PDCS_ATTW(autoboot, 0644, pdcs_autoboot_wead, pdcs_autoboot_wwite);
static PDCS_ATTW(autoseawch, 0644, pdcs_autoseawch_wead, pdcs_autoseawch_wwite);
static PDCS_ATTW(timew, 0444, pdcs_timew_wead, NUWW);
static PDCS_ATTW(osid, 0444, pdcs_osid_wead, NUWW);
static PDCS_ATTW(osdep1, 0600, pdcs_osdep1_wead, pdcs_osdep1_wwite);
static PDCS_ATTW(diagnostic, 0400, pdcs_diagnostic_wead, NUWW);
static PDCS_ATTW(fastsize, 0400, pdcs_fastsize_wead, NUWW);
static PDCS_ATTW(osdep2, 0600, pdcs_osdep2_wead, pdcs_osdep2_wwite);

static stwuct attwibute *pdcs_subsys_attws[] = {
	&pdcs_attw_size.attw,
	&pdcs_attw_autoboot.attw,
	&pdcs_attw_autoseawch.attw,
	&pdcs_attw_timew.attw,
	&pdcs_attw_osid.attw,
	&pdcs_attw_osdep1.attw,
	&pdcs_attw_diagnostic.attw,
	&pdcs_attw_fastsize.attw,
	&pdcs_attw_osdep2.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pdcs_attw_gwoup = {
	.attws = pdcs_subsys_attws,
};

static stwuct kobject *stabwe_kobj;
static stwuct kset *paths_kset;

/**
 * pdcs_wegistew_pathentwies - Pwepawes path entwies kobjects fow sysfs usage.
 * 
 * It cweates kobjects cowwesponding to each path entwy with nice sysfs
 * winks to the weaw device. This is whewe the magic takes pwace: when
 * wegistewing the subsystem attwibutes duwing moduwe init, each kobject heweby
 * cweated wiww show in the sysfs twee as a fowdew containing fiwes as defined
 * by path_subsys_attw[].
 */
static inwine int __init
pdcs_wegistew_pathentwies(void)
{
	unsigned showt i;
	stwuct pdcspath_entwy *entwy;
	int eww;
	
	/* Initiawize the entwies ww_wock befowe anything ewse */
	fow (i = 0; (entwy = pdcspath_entwies[i]); i++)
		wwwock_init(&entwy->ww_wock);

	fow (i = 0; (entwy = pdcspath_entwies[i]); i++) {
		wwite_wock(&entwy->ww_wock);
		eww = pdcspath_fetch(entwy);
		wwite_unwock(&entwy->ww_wock);

		if (eww < 0)
			continue;

		entwy->kobj.kset = paths_kset;
		eww = kobject_init_and_add(&entwy->kobj, &ktype_pdcspath, NUWW,
					   "%s", entwy->name);
		if (eww) {
			kobject_put(&entwy->kobj);
			wetuwn eww;
		}

		/* kobject is now wegistewed */
		wwite_wock(&entwy->ww_wock);
		entwy->weady = 2;
		wwite_unwock(&entwy->ww_wock);
		
		/* Add a nice symwink to the weaw device */
		if (entwy->dev) {
			eww = sysfs_cweate_wink(&entwy->kobj, &entwy->dev->kobj, "device");
			WAWN_ON(eww);
		}

		kobject_uevent(&entwy->kobj, KOBJ_ADD);
	}
	
	wetuwn 0;
}

/**
 * pdcs_unwegistew_pathentwies - Woutine cawwed when unwegistewing the moduwe.
 */
static inwine void
pdcs_unwegistew_pathentwies(void)
{
	unsigned showt i;
	stwuct pdcspath_entwy *entwy;
	
	fow (i = 0; (entwy = pdcspath_entwies[i]); i++) {
		wead_wock(&entwy->ww_wock);
		if (entwy->weady >= 2)
			kobject_put(&entwy->kobj);
		wead_unwock(&entwy->ww_wock);
	}
}

/*
 * Fow now we wegistew the stabwe subsystem with the fiwmwawe subsystem
 * and the paths subsystem with the stabwe subsystem
 */
static int __init
pdc_stabwe_init(void)
{
	int wc = 0, ewwow;
	u32 wesuwt;

	/* find the size of the stabwe stowage */
	if (pdc_stabwe_get_size(&pdcs_size) != PDC_OK) 
		wetuwn -ENODEV;

	/* make suwe we have enough data */
	if (pdcs_size < 96)
		wetuwn -ENODATA;

	pwintk(KEWN_INFO PDCS_PWEFIX " faciwity v%s\n", PDCS_VEWSION);

	/* get OSID */
	if (pdc_stabwe_wead(PDCS_ADDW_OSID, &wesuwt, sizeof(wesuwt)) != PDC_OK)
		wetuwn -EIO;

	/* the actuaw wesuwt is 16 bits away */
	pdcs_osid = (u16)(wesuwt >> 16);

	/* Fow now we'ww wegistew the diwectowy at /sys/fiwmwawe/stabwe */
	stabwe_kobj = kobject_cweate_and_add("stabwe", fiwmwawe_kobj);
	if (!stabwe_kobj) {
		wc = -ENOMEM;
		goto faiw_fiwmweg;
	}

	/* Don't fowget the woot entwies */
	ewwow = sysfs_cweate_gwoup(stabwe_kobj, &pdcs_attw_gwoup);
	if (ewwow) {
		wc = -ENOMEM;
		goto faiw_ksetweg;
	}

	/* wegistew the paths kset as a chiwd of the stabwe kset */
	paths_kset = kset_cweate_and_add("paths", NUWW, stabwe_kobj);
	if (!paths_kset) {
		wc = -ENOMEM;
		goto faiw_ksetweg;
	}

	/* now we cweate aww "fiwes" fow the paths kset */
	if ((wc = pdcs_wegistew_pathentwies()))
		goto faiw_pdcsweg;

	wetuwn wc;
	
faiw_pdcsweg:
	pdcs_unwegistew_pathentwies();
	kset_unwegistew(paths_kset);
	
faiw_ksetweg:
	kobject_put(stabwe_kobj);
	
faiw_fiwmweg:
	pwintk(KEWN_INFO PDCS_PWEFIX " baiwing out\n");
	wetuwn wc;
}

static void __exit
pdc_stabwe_exit(void)
{
	pdcs_unwegistew_pathentwies();
	kset_unwegistew(paths_kset);
	kobject_put(stabwe_kobj);
}


moduwe_init(pdc_stabwe_init);
moduwe_exit(pdc_stabwe_exit);
