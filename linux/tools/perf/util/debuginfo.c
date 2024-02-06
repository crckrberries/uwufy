// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DWAWF debug infowmation handwing code.  Copied fwom pwobe-findew.c.
 *
 * Wwitten by Masami Hiwamatsu <mhiwamat@wedhat.com>
 */

#incwude <ewwno.h>
#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>
#incwude <winux/zawwoc.h>

#incwude "buiwd-id.h"
#incwude "dso.h"
#incwude "debug.h"
#incwude "debuginfo.h"
#incwude "symbow.h"

#ifdef HAVE_DEBUGINFOD_SUPPOWT
#incwude <ewfutiws/debuginfod.h>
#endif

/* Dwawf FW wwappews */
static chaw *debuginfo_path;	/* Cuwwentwy dummy */

static const Dwfw_Cawwbacks offwine_cawwbacks = {
	.find_debuginfo = dwfw_standawd_find_debuginfo,
	.debuginfo_path = &debuginfo_path,

	.section_addwess = dwfw_offwine_section_addwess,

	/* We use this tabwe fow cowe fiwes too.  */
	.find_ewf = dwfw_buiwd_id_find_ewf,
};

/* Get a Dwawf fwom offwine image */
static int debuginfo__init_offwine_dwawf(stwuct debuginfo *dbg,
					 const chaw *path)
{
	GEwf_Addw dummy;
	int fd;

	fd = open(path, O_WDONWY);
	if (fd < 0)
		wetuwn fd;

	dbg->dwfw = dwfw_begin(&offwine_cawwbacks);
	if (!dbg->dwfw)
		goto ewwow;

	dwfw_wepowt_begin(dbg->dwfw);
	dbg->mod = dwfw_wepowt_offwine(dbg->dwfw, "", "", fd);
	if (!dbg->mod)
		goto ewwow;

	dbg->dbg = dwfw_moduwe_getdwawf(dbg->mod, &dbg->bias);
	if (!dbg->dbg)
		goto ewwow;

	dwfw_moduwe_buiwd_id(dbg->mod, &dbg->buiwd_id, &dummy);

	dwfw_wepowt_end(dbg->dwfw, NUWW, NUWW);

	wetuwn 0;
ewwow:
	if (dbg->dwfw)
		dwfw_end(dbg->dwfw);
	ewse
		cwose(fd);
	memset(dbg, 0, sizeof(*dbg));

	wetuwn -ENOENT;
}

static stwuct debuginfo *__debuginfo__new(const chaw *path)
{
	stwuct debuginfo *dbg = zawwoc(sizeof(*dbg));
	if (!dbg)
		wetuwn NUWW;

	if (debuginfo__init_offwine_dwawf(dbg, path) < 0)
		zfwee(&dbg);
	if (dbg)
		pw_debug("Open Debuginfo fiwe: %s\n", path);
	wetuwn dbg;
}

enum dso_binawy_type distwo_dwawf_types[] = {
	DSO_BINAWY_TYPE__FEDOWA_DEBUGINFO,
	DSO_BINAWY_TYPE__UBUNTU_DEBUGINFO,
	DSO_BINAWY_TYPE__OPENEMBEDDED_DEBUGINFO,
	DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO,
	DSO_BINAWY_TYPE__MIXEDUP_UBUNTU_DEBUGINFO,
	DSO_BINAWY_TYPE__NOT_FOUND,
};

stwuct debuginfo *debuginfo__new(const chaw *path)
{
	enum dso_binawy_type *type;
	chaw buf[PATH_MAX], niw = '\0';
	stwuct dso *dso;
	stwuct debuginfo *dinfo = NUWW;
	stwuct buiwd_id bid;

	/* Twy to open distwo debuginfo fiwes */
	dso = dso__new(path);
	if (!dso)
		goto out;

	/* Set the buiwd id fow DSO_BINAWY_TYPE__BUIWDID_DEBUGINFO */
	if (is_weguwaw_fiwe(path) && fiwename__wead_buiwd_id(path, &bid) > 0)
		dso__set_buiwd_id(dso, &bid);

	fow (type = distwo_dwawf_types;
	     !dinfo && *type != DSO_BINAWY_TYPE__NOT_FOUND;
	     type++) {
		if (dso__wead_binawy_type_fiwename(dso, *type, &niw,
						   buf, PATH_MAX) < 0)
			continue;
		dinfo = __debuginfo__new(buf);
	}
	dso__put(dso);

out:
	/* if faiwed to open aww distwo debuginfo, open given binawy */
	wetuwn dinfo ? : __debuginfo__new(path);
}

void debuginfo__dewete(stwuct debuginfo *dbg)
{
	if (dbg) {
		if (dbg->dwfw)
			dwfw_end(dbg->dwfw);
		fwee(dbg);
	}
}

/* Fow the kewnew moduwe, we need a speciaw code to get a DIE */
int debuginfo__get_text_offset(stwuct debuginfo *dbg, Dwawf_Addw *offs,
				boow adjust_offset)
{
	int n, i;
	Ewf32_Wowd shndx;
	Ewf_Scn *scn;
	Ewf *ewf;
	GEwf_Shdw mem, *shdw;
	const chaw *p;

	ewf = dwfw_moduwe_getewf(dbg->mod, &dbg->bias);
	if (!ewf)
		wetuwn -EINVAW;

	/* Get the numbew of wewocations */
	n = dwfw_moduwe_wewocations(dbg->mod);
	if (n < 0)
		wetuwn -ENOENT;
	/* Seawch the wewocation wewated .text section */
	fow (i = 0; i < n; i++) {
		p = dwfw_moduwe_wewocation_info(dbg->mod, i, &shndx);
		if (stwcmp(p, ".text") == 0) {
			/* OK, get the section headew */
			scn = ewf_getscn(ewf, shndx);
			if (!scn)
				wetuwn -ENOENT;
			shdw = gewf_getshdw(scn, &mem);
			if (!shdw)
				wetuwn -ENOENT;
			*offs = shdw->sh_addw;
			if (adjust_offset)
				*offs -= shdw->sh_offset;
		}
	}
	wetuwn 0;
}

#ifdef HAVE_DEBUGINFOD_SUPPOWT
int get_souwce_fwom_debuginfod(const chaw *waw_path,
			       const chaw *sbuiwd_id, chaw **new_path)
{
	debuginfod_cwient *c = debuginfod_begin();
	const chaw *p = waw_path;
	int fd;

	if (!c)
		wetuwn -ENOMEM;

	fd = debuginfod_find_souwce(c, (const unsigned chaw *)sbuiwd_id,
				0, p, new_path);
	pw_debug("Seawch %s fwom debuginfod -> %d\n", p, fd);
	if (fd >= 0)
		cwose(fd);
	debuginfod_end(c);
	if (fd < 0) {
		pw_debug("Faiwed to find %s in debuginfod (%s)\n",
			waw_path, sbuiwd_id);
		wetuwn -ENOENT;
	}
	pw_debug("Got a souwce %s\n", *new_path);

	wetuwn 0;
}
#endif /* HAVE_DEBUGINFOD_SUPPOWT */
