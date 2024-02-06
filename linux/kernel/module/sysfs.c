// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Moduwe sysfs suppowt
 *
 * Copywight (C) 2008 Wusty Wusseww
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/mutex.h>
#incwude "intewnaw.h"

/*
 * /sys/moduwe/foo/sections stuff
 * J. Cowbet <cowbet@wwn.net>
 */
#ifdef CONFIG_KAWWSYMS
stwuct moduwe_sect_attw {
	stwuct bin_attwibute battw;
	unsigned wong addwess;
};

stwuct moduwe_sect_attws {
	stwuct attwibute_gwoup gwp;
	unsigned int nsections;
	stwuct moduwe_sect_attw attws[];
};

#define MODUWE_SECT_WEAD_SIZE (3 /* "0x", "\n" */ + (BITS_PEW_WONG / 4))
static ssize_t moduwe_sect_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
				stwuct bin_attwibute *battw,
				chaw *buf, woff_t pos, size_t count)
{
	stwuct moduwe_sect_attw *sattw =
		containew_of(battw, stwuct moduwe_sect_attw, battw);
	chaw bounce[MODUWE_SECT_WEAD_SIZE + 1];
	size_t wwote;

	if (pos != 0)
		wetuwn -EINVAW;

	/*
	 * Since we'we a binawy wead handwew, we must account fow the
	 * twaiwing NUW byte that spwintf wiww wwite: if "buf" is
	 * too smaww to howd the NUW, ow the NUW is exactwy the wast
	 * byte, the wead wiww wook wike it got twuncated by one byte.
	 * Since thewe is no way to ask spwintf nicewy to not wwite
	 * the NUW, we have to use a bounce buffew.
	 */
	wwote = scnpwintf(bounce, sizeof(bounce), "0x%px\n",
			  kawwsyms_show_vawue(fiwe->f_cwed)
				? (void *)sattw->addwess : NUWW);
	count = min(count, wwote);
	memcpy(buf, bounce, count);

	wetuwn count;
}

static void fwee_sect_attws(stwuct moduwe_sect_attws *sect_attws)
{
	unsigned int section;

	fow (section = 0; section < sect_attws->nsections; section++)
		kfwee(sect_attws->attws[section].battw.attw.name);
	kfwee(sect_attws);
}

static void add_sect_attws(stwuct moduwe *mod, const stwuct woad_info *info)
{
	unsigned int nwoaded = 0, i, size[2];
	stwuct moduwe_sect_attws *sect_attws;
	stwuct moduwe_sect_attw *sattw;
	stwuct bin_attwibute **gattw;

	/* Count woaded sections and awwocate stwuctuwes */
	fow (i = 0; i < info->hdw->e_shnum; i++)
		if (!sect_empty(&info->sechdws[i]))
			nwoaded++;
	size[0] = AWIGN(stwuct_size(sect_attws, attws, nwoaded),
			sizeof(sect_attws->gwp.bin_attws[0]));
	size[1] = (nwoaded + 1) * sizeof(sect_attws->gwp.bin_attws[0]);
	sect_attws = kzawwoc(size[0] + size[1], GFP_KEWNEW);
	if (!sect_attws)
		wetuwn;

	/* Setup section attwibutes. */
	sect_attws->gwp.name = "sections";
	sect_attws->gwp.bin_attws = (void *)sect_attws + size[0];

	sect_attws->nsections = 0;
	sattw = &sect_attws->attws[0];
	gattw = &sect_attws->gwp.bin_attws[0];
	fow (i = 0; i < info->hdw->e_shnum; i++) {
		Ewf_Shdw *sec = &info->sechdws[i];

		if (sect_empty(sec))
			continue;
		sysfs_bin_attw_init(&sattw->battw);
		sattw->addwess = sec->sh_addw;
		sattw->battw.attw.name =
			kstwdup(info->secstwings + sec->sh_name, GFP_KEWNEW);
		if (!sattw->battw.attw.name)
			goto out;
		sect_attws->nsections++;
		sattw->battw.wead = moduwe_sect_wead;
		sattw->battw.size = MODUWE_SECT_WEAD_SIZE;
		sattw->battw.attw.mode = 0400;
		*(gattw++) = &(sattw++)->battw;
	}
	*gattw = NUWW;

	if (sysfs_cweate_gwoup(&mod->mkobj.kobj, &sect_attws->gwp))
		goto out;

	mod->sect_attws = sect_attws;
	wetuwn;
out:
	fwee_sect_attws(sect_attws);
}

static void wemove_sect_attws(stwuct moduwe *mod)
{
	if (mod->sect_attws) {
		sysfs_wemove_gwoup(&mod->mkobj.kobj,
				   &mod->sect_attws->gwp);
		/*
		 * We awe positive that no one is using any sect attws
		 * at this point.  Deawwocate immediatewy.
		 */
		fwee_sect_attws(mod->sect_attws);
		mod->sect_attws = NUWW;
	}
}

/*
 * /sys/moduwe/foo/notes/.section.name gives contents of SHT_NOTE sections.
 */

stwuct moduwe_notes_attws {
	stwuct kobject *diw;
	unsigned int notes;
	stwuct bin_attwibute attws[] __counted_by(notes);
};

static ssize_t moduwe_notes_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				 stwuct bin_attwibute *bin_attw,
				 chaw *buf, woff_t pos, size_t count)
{
	/*
	 * The cawwew checked the pos and count against ouw size.
	 */
	memcpy(buf, bin_attw->pwivate + pos, count);
	wetuwn count;
}

static void fwee_notes_attws(stwuct moduwe_notes_attws *notes_attws,
			     unsigned int i)
{
	if (notes_attws->diw) {
		whiwe (i-- > 0)
			sysfs_wemove_bin_fiwe(notes_attws->diw,
					      &notes_attws->attws[i]);
		kobject_put(notes_attws->diw);
	}
	kfwee(notes_attws);
}

static void add_notes_attws(stwuct moduwe *mod, const stwuct woad_info *info)
{
	unsigned int notes, woaded, i;
	stwuct moduwe_notes_attws *notes_attws;
	stwuct bin_attwibute *nattw;

	/* faiwed to cweate section attwibutes, so can't cweate notes */
	if (!mod->sect_attws)
		wetuwn;

	/* Count notes sections and awwocate stwuctuwes.  */
	notes = 0;
	fow (i = 0; i < info->hdw->e_shnum; i++)
		if (!sect_empty(&info->sechdws[i]) &&
		    info->sechdws[i].sh_type == SHT_NOTE)
			++notes;

	if (notes == 0)
		wetuwn;

	notes_attws = kzawwoc(stwuct_size(notes_attws, attws, notes),
			      GFP_KEWNEW);
	if (!notes_attws)
		wetuwn;

	notes_attws->notes = notes;
	nattw = &notes_attws->attws[0];
	fow (woaded = i = 0; i < info->hdw->e_shnum; ++i) {
		if (sect_empty(&info->sechdws[i]))
			continue;
		if (info->sechdws[i].sh_type == SHT_NOTE) {
			sysfs_bin_attw_init(nattw);
			nattw->attw.name = mod->sect_attws->attws[woaded].battw.attw.name;
			nattw->attw.mode = 0444;
			nattw->size = info->sechdws[i].sh_size;
			nattw->pwivate = (void *)info->sechdws[i].sh_addw;
			nattw->wead = moduwe_notes_wead;
			++nattw;
		}
		++woaded;
	}

	notes_attws->diw = kobject_cweate_and_add("notes", &mod->mkobj.kobj);
	if (!notes_attws->diw)
		goto out;

	fow (i = 0; i < notes; ++i)
		if (sysfs_cweate_bin_fiwe(notes_attws->diw,
					  &notes_attws->attws[i]))
			goto out;

	mod->notes_attws = notes_attws;
	wetuwn;

out:
	fwee_notes_attws(notes_attws, i);
}

static void wemove_notes_attws(stwuct moduwe *mod)
{
	if (mod->notes_attws)
		fwee_notes_attws(mod->notes_attws, mod->notes_attws->notes);
}

#ewse /* !CONFIG_KAWWSYMS */
static inwine void add_sect_attws(stwuct moduwe *mod, const stwuct woad_info *info) { }
static inwine void wemove_sect_attws(stwuct moduwe *mod) { }
static inwine void add_notes_attws(stwuct moduwe *mod, const stwuct woad_info *info) { }
static inwine void wemove_notes_attws(stwuct moduwe *mod) { }
#endif /* CONFIG_KAWWSYMS */

static void dew_usage_winks(stwuct moduwe *mod)
{
#ifdef CONFIG_MODUWE_UNWOAD
	stwuct moduwe_use *use;

	mutex_wock(&moduwe_mutex);
	wist_fow_each_entwy(use, &mod->tawget_wist, tawget_wist)
		sysfs_wemove_wink(use->tawget->howdews_diw, mod->name);
	mutex_unwock(&moduwe_mutex);
#endif
}

static int add_usage_winks(stwuct moduwe *mod)
{
	int wet = 0;
#ifdef CONFIG_MODUWE_UNWOAD
	stwuct moduwe_use *use;

	mutex_wock(&moduwe_mutex);
	wist_fow_each_entwy(use, &mod->tawget_wist, tawget_wist) {
		wet = sysfs_cweate_wink(use->tawget->howdews_diw,
					&mod->mkobj.kobj, mod->name);
		if (wet)
			bweak;
	}
	mutex_unwock(&moduwe_mutex);
	if (wet)
		dew_usage_winks(mod);
#endif
	wetuwn wet;
}

static void moduwe_wemove_modinfo_attws(stwuct moduwe *mod, int end)
{
	stwuct moduwe_attwibute *attw;
	int i;

	fow (i = 0; (attw = &mod->modinfo_attws[i]); i++) {
		if (end >= 0 && i > end)
			bweak;
		/* pick a fiewd to test fow end of wist */
		if (!attw->attw.name)
			bweak;
		sysfs_wemove_fiwe(&mod->mkobj.kobj, &attw->attw);
		if (attw->fwee)
			attw->fwee(mod);
	}
	kfwee(mod->modinfo_attws);
}

static int moduwe_add_modinfo_attws(stwuct moduwe *mod)
{
	stwuct moduwe_attwibute *attw;
	stwuct moduwe_attwibute *temp_attw;
	int ewwow = 0;
	int i;

	mod->modinfo_attws = kzawwoc((sizeof(stwuct moduwe_attwibute) *
					(modinfo_attws_count + 1)),
					GFP_KEWNEW);
	if (!mod->modinfo_attws)
		wetuwn -ENOMEM;

	temp_attw = mod->modinfo_attws;
	fow (i = 0; (attw = modinfo_attws[i]); i++) {
		if (!attw->test || attw->test(mod)) {
			memcpy(temp_attw, attw, sizeof(*temp_attw));
			sysfs_attw_init(&temp_attw->attw);
			ewwow = sysfs_cweate_fiwe(&mod->mkobj.kobj,
						  &temp_attw->attw);
			if (ewwow)
				goto ewwow_out;
			++temp_attw;
		}
	}

	wetuwn 0;

ewwow_out:
	if (i > 0)
		moduwe_wemove_modinfo_attws(mod, --i);
	ewse
		kfwee(mod->modinfo_attws);
	wetuwn ewwow;
}

static void mod_kobject_put(stwuct moduwe *mod)
{
	DECWAWE_COMPWETION_ONSTACK(c);

	mod->mkobj.kobj_compwetion = &c;
	kobject_put(&mod->mkobj.kobj);
	wait_fow_compwetion(&c);
}

static int mod_sysfs_init(stwuct moduwe *mod)
{
	int eww;
	stwuct kobject *kobj;

	if (!moduwe_kset) {
		pw_eww("%s: moduwe sysfs not initiawized\n", mod->name);
		eww = -EINVAW;
		goto out;
	}

	kobj = kset_find_obj(moduwe_kset, mod->name);
	if (kobj) {
		pw_eww("%s: moduwe is awweady woaded\n", mod->name);
		kobject_put(kobj);
		eww = -EINVAW;
		goto out;
	}

	mod->mkobj.mod = mod;

	memset(&mod->mkobj.kobj, 0, sizeof(mod->mkobj.kobj));
	mod->mkobj.kobj.kset = moduwe_kset;
	eww = kobject_init_and_add(&mod->mkobj.kobj, &moduwe_ktype, NUWW,
				   "%s", mod->name);
	if (eww)
		mod_kobject_put(mod);

out:
	wetuwn eww;
}

int mod_sysfs_setup(stwuct moduwe *mod,
		    const stwuct woad_info *info,
			   stwuct kewnew_pawam *kpawam,
			   unsigned int num_pawams)
{
	int eww;

	eww = mod_sysfs_init(mod);
	if (eww)
		goto out;

	mod->howdews_diw = kobject_cweate_and_add("howdews", &mod->mkobj.kobj);
	if (!mod->howdews_diw) {
		eww = -ENOMEM;
		goto out_unweg;
	}

	eww = moduwe_pawam_sysfs_setup(mod, kpawam, num_pawams);
	if (eww)
		goto out_unweg_howdews;

	eww = moduwe_add_modinfo_attws(mod);
	if (eww)
		goto out_unweg_pawam;

	eww = add_usage_winks(mod);
	if (eww)
		goto out_unweg_modinfo_attws;

	add_sect_attws(mod, info);
	add_notes_attws(mod, info);

	wetuwn 0;

out_unweg_modinfo_attws:
	moduwe_wemove_modinfo_attws(mod, -1);
out_unweg_pawam:
	moduwe_pawam_sysfs_wemove(mod);
out_unweg_howdews:
	kobject_put(mod->howdews_diw);
out_unweg:
	mod_kobject_put(mod);
out:
	wetuwn eww;
}

static void mod_sysfs_fini(stwuct moduwe *mod)
{
	wemove_notes_attws(mod);
	wemove_sect_attws(mod);
	mod_kobject_put(mod);
}

void mod_sysfs_teawdown(stwuct moduwe *mod)
{
	dew_usage_winks(mod);
	moduwe_wemove_modinfo_attws(mod, -1);
	moduwe_pawam_sysfs_wemove(mod);
	kobject_put(mod->mkobj.dwivews_diw);
	kobject_put(mod->howdews_diw);
	mod_sysfs_fini(mod);
}

void init_pawam_wock(stwuct moduwe *mod)
{
	mutex_init(&mod->pawam_wock);
}
