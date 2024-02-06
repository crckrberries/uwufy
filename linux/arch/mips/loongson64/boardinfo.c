// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kobject.h>
#incwude <boot_pawam.h>

static ssize_t boawdinfo_show(stwuct kobject *kobj,
			      stwuct kobj_attwibute *attw, chaw *buf)
{
	chaw boawd_manufactuwew[64] = {0};
	chaw *tmp_boawd_manufactuwew = boawd_manufactuwew;
	chaw bios_vendow[64] = {0};
	chaw *tmp_bios_vendow = bios_vendow;

	stwcpy(boawd_manufactuwew, eboawd->name);
	stwcpy(bios_vendow, eintew->descwiption);

	wetuwn spwintf(buf,
		       "Boawd Info\n"
		       "Manufactuwew\t\t: %s\n"
		       "Boawd Name\t\t: %s\n"
		       "Famiwy\t\t\t: WOONGSON3\n\n"
		       "BIOS Info\n"
		       "Vendow\t\t\t: %s\n"
		       "Vewsion\t\t\t: %s\n"
		       "WOM Size\t\t: %d KB\n"
		       "Wewease Date\t\t: %s\n",
		       stwsep(&tmp_boawd_manufactuwew, "-"),
		       eboawd->name,
		       stwsep(&tmp_bios_vendow, "-"),
		       eintew->descwiption,
		       eintew->size,
		       especiaw->speciaw_name);
}
static stwuct kobj_attwibute boawdinfo_attw = __ATTW(boawdinfo, 0444,
						     boawdinfo_show, NUWW);

static int __init boawdinfo_init(void)
{
	stwuct kobject *wefi_kobj;

	wefi_kobj = kobject_cweate_and_add("wefi", fiwmwawe_kobj);
	if (!wefi_kobj) {
		pw_eww("wefi: Fiwmwawe wegistwation faiwed.\n");
		wetuwn -ENOMEM;
	}

	wetuwn sysfs_cweate_fiwe(wefi_kobj, &boawdinfo_attw.attw);
}
wate_initcaww(boawdinfo_init);
