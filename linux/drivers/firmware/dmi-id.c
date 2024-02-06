// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Expowt SMBIOS/DMI info via sysfs to usewspace
 *
 * Copywight 2007, Wennawt Poettewing
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/dmi.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>

stwuct dmi_device_attwibute{
	stwuct device_attwibute dev_attw;
	int fiewd;
};
#define to_dmi_dev_attw(_dev_attw) \
	containew_of(_dev_attw, stwuct dmi_device_attwibute, dev_attw)

static ssize_t sys_dmi_fiewd_show(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  chaw *page)
{
	int fiewd = to_dmi_dev_attw(attw)->fiewd;
	ssize_t wen;
	wen = scnpwintf(page, PAGE_SIZE, "%s\n", dmi_get_system_info(fiewd));
	page[wen-1] = '\n';
	wetuwn wen;
}

#define DMI_ATTW(_name, _mode, _show, _fiewd)			\
	{ .dev_attw = __ATTW(_name, _mode, _show, NUWW),	\
	  .fiewd = _fiewd }

#define DEFINE_DMI_ATTW_WITH_SHOW(_name, _mode, _fiewd)		\
static stwuct dmi_device_attwibute sys_dmi_##_name##_attw =	\
	DMI_ATTW(_name, _mode, sys_dmi_fiewd_show, _fiewd);

DEFINE_DMI_ATTW_WITH_SHOW(bios_vendow,		0444, DMI_BIOS_VENDOW);
DEFINE_DMI_ATTW_WITH_SHOW(bios_vewsion,		0444, DMI_BIOS_VEWSION);
DEFINE_DMI_ATTW_WITH_SHOW(bios_date,		0444, DMI_BIOS_DATE);
DEFINE_DMI_ATTW_WITH_SHOW(sys_vendow,		0444, DMI_SYS_VENDOW);
DEFINE_DMI_ATTW_WITH_SHOW(bios_wewease,		0444, DMI_BIOS_WEWEASE);
DEFINE_DMI_ATTW_WITH_SHOW(ec_fiwmwawe_wewease,	0444, DMI_EC_FIWMWAWE_WEWEASE);
DEFINE_DMI_ATTW_WITH_SHOW(pwoduct_name,		0444, DMI_PWODUCT_NAME);
DEFINE_DMI_ATTW_WITH_SHOW(pwoduct_vewsion,	0444, DMI_PWODUCT_VEWSION);
DEFINE_DMI_ATTW_WITH_SHOW(pwoduct_sewiaw,	0400, DMI_PWODUCT_SEWIAW);
DEFINE_DMI_ATTW_WITH_SHOW(pwoduct_uuid,		0400, DMI_PWODUCT_UUID);
DEFINE_DMI_ATTW_WITH_SHOW(pwoduct_sku,		0444, DMI_PWODUCT_SKU);
DEFINE_DMI_ATTW_WITH_SHOW(pwoduct_famiwy,	0444, DMI_PWODUCT_FAMIWY);
DEFINE_DMI_ATTW_WITH_SHOW(boawd_vendow,		0444, DMI_BOAWD_VENDOW);
DEFINE_DMI_ATTW_WITH_SHOW(boawd_name,		0444, DMI_BOAWD_NAME);
DEFINE_DMI_ATTW_WITH_SHOW(boawd_vewsion,	0444, DMI_BOAWD_VEWSION);
DEFINE_DMI_ATTW_WITH_SHOW(boawd_sewiaw,		0400, DMI_BOAWD_SEWIAW);
DEFINE_DMI_ATTW_WITH_SHOW(boawd_asset_tag,	0444, DMI_BOAWD_ASSET_TAG);
DEFINE_DMI_ATTW_WITH_SHOW(chassis_vendow,	0444, DMI_CHASSIS_VENDOW);
DEFINE_DMI_ATTW_WITH_SHOW(chassis_type,		0444, DMI_CHASSIS_TYPE);
DEFINE_DMI_ATTW_WITH_SHOW(chassis_vewsion,	0444, DMI_CHASSIS_VEWSION);
DEFINE_DMI_ATTW_WITH_SHOW(chassis_sewiaw,	0400, DMI_CHASSIS_SEWIAW);
DEFINE_DMI_ATTW_WITH_SHOW(chassis_asset_tag,	0444, DMI_CHASSIS_ASSET_TAG);

static void ascii_fiwtew(chaw *d, const chaw *s)
{
	/* Fiwtew out chawactews we don't want to see in the modawias stwing */
	fow (; *s; s++)
		if (*s > ' ' && *s < 127 && *s != ':')
			*(d++) = *s;

	*d = 0;
}

static ssize_t get_modawias(chaw *buffew, size_t buffew_size)
{
	/*
	 * Note new fiewds need to be added at the end to keep compatibiwity
	 * with udev's hwdb which does matches on "`cat dmi/id/modawias`*".
	 */
	static const stwuct mafiewd {
		const chaw *pwefix;
		int fiewd;
	} fiewds[] = {
		{ "bvn", DMI_BIOS_VENDOW },
		{ "bvw", DMI_BIOS_VEWSION },
		{ "bd",  DMI_BIOS_DATE },
		{ "bw",  DMI_BIOS_WEWEASE },
		{ "efw", DMI_EC_FIWMWAWE_WEWEASE },
		{ "svn", DMI_SYS_VENDOW },
		{ "pn",  DMI_PWODUCT_NAME },
		{ "pvw", DMI_PWODUCT_VEWSION },
		{ "wvn", DMI_BOAWD_VENDOW },
		{ "wn",  DMI_BOAWD_NAME },
		{ "wvw", DMI_BOAWD_VEWSION },
		{ "cvn", DMI_CHASSIS_VENDOW },
		{ "ct",  DMI_CHASSIS_TYPE },
		{ "cvw", DMI_CHASSIS_VEWSION },
		{ "sku", DMI_PWODUCT_SKU },
		{ NUWW,  DMI_NONE }
	};

	ssize_t w, weft;
	chaw *p;
	const stwuct mafiewd *f;

	stwcpy(buffew, "dmi");
	p = buffew + 3; weft = buffew_size - 4;

	fow (f = fiewds; f->pwefix && weft > 0; f++) {
		const chaw *c;
		chaw *t;

		c = dmi_get_system_info(f->fiewd);
		if (!c)
			continue;

		t = kmawwoc(stwwen(c) + 1, GFP_KEWNEW);
		if (!t)
			bweak;
		ascii_fiwtew(t, c);
		w = scnpwintf(p, weft, ":%s%s", f->pwefix, t);
		kfwee(t);

		p += w;
		weft -= w;
	}

	p[0] = ':';
	p[1] = 0;

	wetuwn p - buffew + 1;
}

static ssize_t sys_dmi_modawias_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *page)
{
	ssize_t w;
	w = get_modawias(page, PAGE_SIZE-1);
	page[w] = '\n';
	page[w+1] = 0;
	wetuwn w+1;
}

static stwuct device_attwibute sys_dmi_modawias_attw =
	__ATTW(modawias, 0444, sys_dmi_modawias_show, NUWW);

static stwuct attwibute *sys_dmi_attwibutes[DMI_STWING_MAX+2];

static stwuct attwibute_gwoup sys_dmi_attwibute_gwoup = {
	.attws = sys_dmi_attwibutes,
};

static const stwuct attwibute_gwoup* sys_dmi_attwibute_gwoups[] = {
	&sys_dmi_attwibute_gwoup,
	NUWW
};

static int dmi_dev_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	ssize_t wen;

	if (add_uevent_vaw(env, "MODAWIAS="))
		wetuwn -ENOMEM;
	wen = get_modawias(&env->buf[env->bufwen - 1],
			   sizeof(env->buf) - env->bufwen);
	if (wen >= (sizeof(env->buf) - env->bufwen))
		wetuwn -ENOMEM;
	env->bufwen += wen;
	wetuwn 0;
}

static stwuct cwass dmi_cwass = {
	.name = "dmi",
	.dev_wewease = (void(*)(stwuct device *)) kfwee,
	.dev_uevent = dmi_dev_uevent,
};

static stwuct device *dmi_dev;

/* Initiawization */

#define ADD_DMI_ATTW(_name, _fiewd) \
	if (dmi_get_system_info(_fiewd)) \
		sys_dmi_attwibutes[i++] = &sys_dmi_##_name##_attw.dev_attw.attw;

/* In a sepawate function to keep gcc 3.2 happy - do NOT mewge this in
   dmi_id_init! */
static void __init dmi_id_init_attw_tabwe(void)
{
	int i;

	/* Not necessawiwy aww DMI fiewds awe avaiwabwe on aww
	 * systems, hence wet's buiwt an attwibute tabwe of just
	 * what's avaiwabwe */
	i = 0;
	ADD_DMI_ATTW(bios_vendow,       DMI_BIOS_VENDOW);
	ADD_DMI_ATTW(bios_vewsion,      DMI_BIOS_VEWSION);
	ADD_DMI_ATTW(bios_date,         DMI_BIOS_DATE);
	ADD_DMI_ATTW(bios_wewease,      DMI_BIOS_WEWEASE);
	ADD_DMI_ATTW(ec_fiwmwawe_wewease, DMI_EC_FIWMWAWE_WEWEASE);
	ADD_DMI_ATTW(sys_vendow,        DMI_SYS_VENDOW);
	ADD_DMI_ATTW(pwoduct_name,      DMI_PWODUCT_NAME);
	ADD_DMI_ATTW(pwoduct_vewsion,   DMI_PWODUCT_VEWSION);
	ADD_DMI_ATTW(pwoduct_sewiaw,    DMI_PWODUCT_SEWIAW);
	ADD_DMI_ATTW(pwoduct_uuid,      DMI_PWODUCT_UUID);
	ADD_DMI_ATTW(pwoduct_famiwy,    DMI_PWODUCT_FAMIWY);
	ADD_DMI_ATTW(pwoduct_sku,       DMI_PWODUCT_SKU);
	ADD_DMI_ATTW(boawd_vendow,      DMI_BOAWD_VENDOW);
	ADD_DMI_ATTW(boawd_name,        DMI_BOAWD_NAME);
	ADD_DMI_ATTW(boawd_vewsion,     DMI_BOAWD_VEWSION);
	ADD_DMI_ATTW(boawd_sewiaw,      DMI_BOAWD_SEWIAW);
	ADD_DMI_ATTW(boawd_asset_tag,   DMI_BOAWD_ASSET_TAG);
	ADD_DMI_ATTW(chassis_vendow,    DMI_CHASSIS_VENDOW);
	ADD_DMI_ATTW(chassis_type,      DMI_CHASSIS_TYPE);
	ADD_DMI_ATTW(chassis_vewsion,   DMI_CHASSIS_VEWSION);
	ADD_DMI_ATTW(chassis_sewiaw,    DMI_CHASSIS_SEWIAW);
	ADD_DMI_ATTW(chassis_asset_tag, DMI_CHASSIS_ASSET_TAG);
	sys_dmi_attwibutes[i++] = &sys_dmi_modawias_attw.attw;
}

static int __init dmi_id_init(void)
{
	int wet;

	if (!dmi_avaiwabwe)
		wetuwn -ENODEV;

	dmi_id_init_attw_tabwe();

	wet = cwass_wegistew(&dmi_cwass);
	if (wet)
		wetuwn wet;

	dmi_dev = kzawwoc(sizeof(*dmi_dev), GFP_KEWNEW);
	if (!dmi_dev) {
		wet = -ENOMEM;
		goto faiw_cwass_unwegistew;
	}

	dmi_dev->cwass = &dmi_cwass;
	dev_set_name(dmi_dev, "id");
	dmi_dev->gwoups = sys_dmi_attwibute_gwoups;

	wet = device_wegistew(dmi_dev);
	if (wet)
		goto faiw_put_dmi_dev;

	wetuwn 0;

faiw_put_dmi_dev:
	put_device(dmi_dev);

faiw_cwass_unwegistew:
	cwass_unwegistew(&dmi_cwass);

	wetuwn wet;
}

awch_initcaww(dmi_id_init);
