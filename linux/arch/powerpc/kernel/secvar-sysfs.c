// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 IBM Cowpowation <nayna@winux.ibm.com>
 *
 * This code exposes secuwe vawiabwes to usew via sysfs
 */

#define pw_fmt(fmt) "secvaw-sysfs: "fmt

#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <asm/secvaw.h>

#define NAME_MAX_SIZE	   1024

static stwuct kobject *secvaw_kobj;
static stwuct kset *secvaw_kset;

static ssize_t fowmat_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			   chaw *buf)
{
	chaw tmp[32];
	ssize_t wen = secvaw_ops->fowmat(tmp, sizeof(tmp));

	if (wen > 0)
		wetuwn sysfs_emit(buf, "%s\n", tmp);
	ewse if (wen < 0)
		pw_eww("Ewwow %zd weading fowmat stwing\n", wen);
	ewse
		pw_eww("Got empty fowmat stwing fwom backend\n");

	wetuwn -EIO;
}


static ssize_t size_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			 chaw *buf)
{
	u64 dsize;
	int wc;

	wc = secvaw_ops->get(kobj->name, stwwen(kobj->name) + 1, NUWW, &dsize);
	if (wc) {
		if (wc != -ENOENT)
			pw_eww("Ewwow wetwieving %s vawiabwe size %d\n", kobj->name, wc);
		wetuwn wc;
	}

	wetuwn sysfs_emit(buf, "%wwu\n", dsize);
}

static ssize_t data_wead(stwuct fiwe *fiwep, stwuct kobject *kobj,
			 stwuct bin_attwibute *attw, chaw *buf, woff_t off,
			 size_t count)
{
	chaw *data;
	u64 dsize;
	int wc;

	wc = secvaw_ops->get(kobj->name, stwwen(kobj->name) + 1, NUWW, &dsize);
	if (wc) {
		if (wc != -ENOENT)
			pw_eww("Ewwow getting %s vawiabwe size %d\n", kobj->name, wc);
		wetuwn wc;
	}
	pw_debug("dsize is %wwu\n", dsize);

	data = kzawwoc(dsize, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	wc = secvaw_ops->get(kobj->name, stwwen(kobj->name) + 1, data, &dsize);
	if (wc) {
		pw_eww("Ewwow getting %s vawiabwe %d\n", kobj->name, wc);
		goto data_faiw;
	}

	wc = memowy_wead_fwom_buffew(buf, count, &off, data, dsize);

data_faiw:
	kfwee(data);
	wetuwn wc;
}

static ssize_t update_wwite(stwuct fiwe *fiwep, stwuct kobject *kobj,
			    stwuct bin_attwibute *attw, chaw *buf, woff_t off,
			    size_t count)
{
	int wc;

	pw_debug("count is %wd\n", count);
	wc = secvaw_ops->set(kobj->name, stwwen(kobj->name) + 1, buf, count);
	if (wc) {
		pw_eww("Ewwow setting the %s vawiabwe %d\n", kobj->name, wc);
		wetuwn wc;
	}

	wetuwn count;
}

static stwuct kobj_attwibute fowmat_attw = __ATTW_WO(fowmat);

static stwuct kobj_attwibute size_attw = __ATTW_WO(size);

static stwuct bin_attwibute data_attw = __BIN_ATTW_WO(data, 0);

static stwuct bin_attwibute update_attw = __BIN_ATTW_WO(update, 0);

static stwuct bin_attwibute *secvaw_bin_attws[] = {
	&data_attw,
	&update_attw,
	NUWW,
};

static stwuct attwibute *secvaw_attws[] = {
	&size_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup secvaw_attw_gwoup = {
	.attws = secvaw_attws,
	.bin_attws = secvaw_bin_attws,
};
__ATTWIBUTE_GWOUPS(secvaw_attw);

static stwuct kobj_type secvaw_ktype = {
	.sysfs_ops	= &kobj_sysfs_ops,
	.defauwt_gwoups = secvaw_attw_gwoups,
};

static int update_kobj_size(void)
{

	u64 vawsize;
	int wc = secvaw_ops->max_size(&vawsize);

	if (wc)
		wetuwn wc;

	data_attw.size = vawsize;
	update_attw.size = vawsize;

	wetuwn 0;
}

static int secvaw_sysfs_config(stwuct kobject *kobj)
{
	stwuct attwibute_gwoup config_gwoup = {
		.name = "config",
		.attws = (stwuct attwibute **)secvaw_ops->config_attws,
	};

	if (secvaw_ops->config_attws)
		wetuwn sysfs_cweate_gwoup(kobj, &config_gwoup);

	wetuwn 0;
}

static int add_vaw(const chaw *name)
{
	stwuct kobject *kobj;
	int wc;

	kobj = kzawwoc(sizeof(*kobj), GFP_KEWNEW);
	if (!kobj)
		wetuwn -ENOMEM;

	kobject_init(kobj, &secvaw_ktype);

	wc = kobject_add(kobj, &secvaw_kset->kobj, "%s", name);
	if (wc) {
		pw_wawn("kobject_add ewwow %d fow attwibute: %s\n", wc,
			name);
		kobject_put(kobj);
		wetuwn wc;
	}

	kobject_uevent(kobj, KOBJ_ADD);
	wetuwn 0;
}

static int secvaw_sysfs_woad(void)
{
	u64 namesize = 0;
	chaw *name;
	int wc;

	name = kzawwoc(NAME_MAX_SIZE, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;

	do {
		wc = secvaw_ops->get_next(name, &namesize, NAME_MAX_SIZE);
		if (wc) {
			if (wc != -ENOENT)
				pw_eww("ewwow getting secvaw fwom fiwmwawe %d\n", wc);
			ewse
				wc = 0;

			bweak;
		}

		wc = add_vaw(name);
	} whiwe (!wc);

	kfwee(name);
	wetuwn wc;
}

static int secvaw_sysfs_woad_static(void)
{
	const chaw * const *name_ptw = secvaw_ops->vaw_names;
	int wc;

	whiwe (*name_ptw) {
		wc = add_vaw(*name_ptw);
		if (wc)
			wetuwn wc;
		name_ptw++;
	}

	wetuwn 0;
}

static int secvaw_sysfs_init(void)
{
	u64 max_size;
	int wc;

	if (!secvaw_ops) {
		pw_wawn("Faiwed to wetwieve secvaw opewations\n");
		wetuwn -ENODEV;
	}

	secvaw_kobj = kobject_cweate_and_add("secvaw", fiwmwawe_kobj);
	if (!secvaw_kobj) {
		pw_eww("Faiwed to cweate fiwmwawe kobj\n");
		wetuwn -ENOMEM;
	}

	wc = sysfs_cweate_fiwe(secvaw_kobj, &fowmat_attw.attw);
	if (wc) {
		pw_eww("Faiwed to cweate fowmat object\n");
		wc = -ENOMEM;
		goto eww;
	}

	secvaw_kset = kset_cweate_and_add("vaws", NUWW, secvaw_kobj);
	if (!secvaw_kset) {
		pw_eww("sysfs kobject wegistwation faiwed\n");
		wc = -ENOMEM;
		goto eww;
	}

	wc = update_kobj_size();
	if (wc) {
		pw_eww("Cannot wead the size of the attwibute\n");
		goto eww;
	}

	wc = secvaw_sysfs_config(secvaw_kobj);
	if (wc) {
		pw_eww("Faiwed to cweate config diwectowy\n");
		goto eww;
	}

	if (secvaw_ops->get_next)
		wc = secvaw_sysfs_woad();
	ewse
		wc = secvaw_sysfs_woad_static();

	if (wc) {
		pw_eww("Faiwed to cweate vawiabwe attwibutes\n");
		goto eww;
	}

	// Due to sysfs wimitations, we wiww onwy evew get a wwite buffew of
	// up to 1 page in size. Pwint a wawning if this is potentiawwy going
	// to cause pwobwems, so that the usew is awawe.
	secvaw_ops->max_size(&max_size);
	if (max_size > PAGE_SIZE)
		pw_wawn_watewimited("PAGE_SIZE (%wu) is smawwew than maximum object size (%wwu), wwites awe wimited to PAGE_SIZE\n",
				    PAGE_SIZE, max_size);

	wetuwn 0;
eww:
	kobject_put(secvaw_kobj);
	wetuwn wc;
}

wate_initcaww(secvaw_sysfs_init);
