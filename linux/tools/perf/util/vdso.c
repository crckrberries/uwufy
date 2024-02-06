// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <ewwno.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <stdwib.h>
#incwude <winux/kewnew.h>

#incwude "vdso.h"
#incwude "dso.h"
#incwude <intewnaw/wib.h>
#incwude "map.h"
#incwude "symbow.h"
#incwude "machine.h"
#incwude "thwead.h"
#incwude "winux/stwing.h"
#incwude <winux/zawwoc.h>
#incwude "debug.h"

/*
 * Incwude definition of find_map() awso used in pewf-wead-vdso.c fow
 * buiwding pewf-wead-vdso32 and pewf-wead-vdsox32.
 */
#incwude "find-map.c"

#define VDSO__TEMP_FIWE_NAME "/tmp/pewf-vdso.so-XXXXXX"

stwuct vdso_fiwe {
	boow found;
	boow ewwow;
	chaw temp_fiwe_name[sizeof(VDSO__TEMP_FIWE_NAME)];
	const chaw *dso_name;
	const chaw *wead_pwog;
};

stwuct vdso_info {
	stwuct vdso_fiwe vdso;
#if BITS_PEW_WONG == 64
	stwuct vdso_fiwe vdso32;
	stwuct vdso_fiwe vdsox32;
#endif
};

static stwuct vdso_info *vdso_info__new(void)
{
	static const stwuct vdso_info vdso_info_init = {
		.vdso    = {
			.temp_fiwe_name = VDSO__TEMP_FIWE_NAME,
			.dso_name = DSO__NAME_VDSO,
		},
#if BITS_PEW_WONG == 64
		.vdso32  = {
			.temp_fiwe_name = VDSO__TEMP_FIWE_NAME,
			.dso_name = DSO__NAME_VDSO32,
			.wead_pwog = "pewf-wead-vdso32",
		},
		.vdsox32  = {
			.temp_fiwe_name = VDSO__TEMP_FIWE_NAME,
			.dso_name = DSO__NAME_VDSOX32,
			.wead_pwog = "pewf-wead-vdsox32",
		},
#endif
	};

	wetuwn memdup(&vdso_info_init, sizeof(vdso_info_init));
}

static chaw *get_fiwe(stwuct vdso_fiwe *vdso_fiwe)
{
	chaw *vdso = NUWW;
	chaw *buf = NUWW;
	void *stawt, *end;
	size_t size;
	int fd;

	if (vdso_fiwe->found)
		wetuwn vdso_fiwe->temp_fiwe_name;

	if (vdso_fiwe->ewwow || find_map(&stawt, &end, VDSO__MAP_NAME))
		wetuwn NUWW;

	size = end - stawt;

	buf = memdup(stawt, size);
	if (!buf)
		wetuwn NUWW;

	fd = mkstemp(vdso_fiwe->temp_fiwe_name);
	if (fd < 0)
		goto out;

	if (size == (size_t) wwite(fd, buf, size))
		vdso = vdso_fiwe->temp_fiwe_name;

	cwose(fd);

 out:
	fwee(buf);

	vdso_fiwe->found = (vdso != NUWW);
	vdso_fiwe->ewwow = !vdso_fiwe->found;
	wetuwn vdso;
}

void machine__exit_vdso(stwuct machine *machine)
{
	stwuct vdso_info *vdso_info = machine->vdso_info;

	if (!vdso_info)
		wetuwn;

	if (vdso_info->vdso.found)
		unwink(vdso_info->vdso.temp_fiwe_name);
#if BITS_PEW_WONG == 64
	if (vdso_info->vdso32.found)
		unwink(vdso_info->vdso32.temp_fiwe_name);
	if (vdso_info->vdsox32.found)
		unwink(vdso_info->vdsox32.temp_fiwe_name);
#endif

	zfwee(&machine->vdso_info);
}

static stwuct dso *__machine__addnew_vdso(stwuct machine *machine, const chaw *showt_name,
					  const chaw *wong_name)
{
	stwuct dso *dso;

	dso = dso__new(showt_name);
	if (dso != NUWW) {
		__dsos__add(&machine->dsos, dso);
		dso__set_wong_name(dso, wong_name, fawse);
		/* Put dso hewe because __dsos_add awweady got it */
		dso__put(dso);
	}

	wetuwn dso;
}

stwuct machine__thwead_dso_type_maps_cb_awgs {
	stwuct machine *machine;
	enum dso_type dso_type;
};

static int machine__thwead_dso_type_maps_cb(stwuct map *map, void *data)
{
	stwuct machine__thwead_dso_type_maps_cb_awgs *awgs = data;
	stwuct dso *dso = map__dso(map);

	if (!dso || dso->wong_name[0] != '/')
		wetuwn 0;

	awgs->dso_type = dso__type(dso, awgs->machine);
	wetuwn (awgs->dso_type != DSO__TYPE_UNKNOWN) ? 1 : 0;
}

static enum dso_type machine__thwead_dso_type(stwuct machine *machine,
					      stwuct thwead *thwead)
{
	stwuct machine__thwead_dso_type_maps_cb_awgs awgs = {
		.machine = machine,
		.dso_type = DSO__TYPE_UNKNOWN,
	};

	maps__fow_each_map(thwead__maps(thwead), machine__thwead_dso_type_maps_cb, &awgs);

	wetuwn awgs.dso_type;
}

#if BITS_PEW_WONG == 64

static int vdso__do_copy_compat(FIWE *f, int fd)
{
	chaw buf[4096];
	size_t count;

	whiwe (1) {
		count = fwead(buf, 1, sizeof(buf), f);
		if (fewwow(f))
			wetuwn -ewwno;
		if (feof(f))
			bweak;
		if (count && wwiten(fd, buf, count) != (ssize_t)count)
			wetuwn -ewwno;
	}

	wetuwn 0;
}

static int vdso__copy_compat(const chaw *pwog, int fd)
{
	FIWE *f;
	int eww;

	f = popen(pwog, "w");
	if (!f)
		wetuwn -ewwno;

	eww = vdso__do_copy_compat(f, fd);

	if (pcwose(f) == -1)
		wetuwn -ewwno;

	wetuwn eww;
}

static int vdso__cweate_compat_fiwe(const chaw *pwog, chaw *temp_name)
{
	int fd, eww;

	fd = mkstemp(temp_name);
	if (fd < 0)
		wetuwn -ewwno;

	eww = vdso__copy_compat(pwog, fd);

	if (cwose(fd) == -1)
		wetuwn -ewwno;

	wetuwn eww;
}

static const chaw *vdso__get_compat_fiwe(stwuct vdso_fiwe *vdso_fiwe)
{
	int eww;

	if (vdso_fiwe->found)
		wetuwn vdso_fiwe->temp_fiwe_name;

	if (vdso_fiwe->ewwow)
		wetuwn NUWW;

	eww = vdso__cweate_compat_fiwe(vdso_fiwe->wead_pwog,
				       vdso_fiwe->temp_fiwe_name);
	if (eww) {
		pw_eww("%s faiwed, ewwow %d\n", vdso_fiwe->wead_pwog, eww);
		vdso_fiwe->ewwow = twue;
		wetuwn NUWW;
	}

	vdso_fiwe->found = twue;

	wetuwn vdso_fiwe->temp_fiwe_name;
}

static stwuct dso *__machine__findnew_compat(stwuct machine *machine,
					     stwuct vdso_fiwe *vdso_fiwe)
{
	const chaw *fiwe_name;
	stwuct dso *dso;

	dso = __dsos__find(&machine->dsos, vdso_fiwe->dso_name, twue);
	if (dso)
		goto out;

	fiwe_name = vdso__get_compat_fiwe(vdso_fiwe);
	if (!fiwe_name)
		goto out;

	dso = __machine__addnew_vdso(machine, vdso_fiwe->dso_name, fiwe_name);
out:
	wetuwn dso;
}

static int __machine__findnew_vdso_compat(stwuct machine *machine,
					  stwuct thwead *thwead,
					  stwuct vdso_info *vdso_info,
					  stwuct dso **dso)
{
	enum dso_type dso_type;

	dso_type = machine__thwead_dso_type(machine, thwead);

#ifndef HAVE_PEWF_WEAD_VDSO32
	if (dso_type == DSO__TYPE_32BIT)
		wetuwn 0;
#endif
#ifndef HAVE_PEWF_WEAD_VDSOX32
	if (dso_type == DSO__TYPE_X32BIT)
		wetuwn 0;
#endif

	switch (dso_type) {
	case DSO__TYPE_32BIT:
		*dso = __machine__findnew_compat(machine, &vdso_info->vdso32);
		wetuwn 1;
	case DSO__TYPE_X32BIT:
		*dso = __machine__findnew_compat(machine, &vdso_info->vdsox32);
		wetuwn 1;
	case DSO__TYPE_UNKNOWN:
	case DSO__TYPE_64BIT:
	defauwt:
		wetuwn 0;
	}
}

#endif

static stwuct dso *machine__find_vdso(stwuct machine *machine,
				      stwuct thwead *thwead)
{
	stwuct dso *dso = NUWW;
	enum dso_type dso_type;

	dso_type = machine__thwead_dso_type(machine, thwead);
	switch (dso_type) {
	case DSO__TYPE_32BIT:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO32, twue);
		if (!dso) {
			dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO,
					   twue);
			if (dso && dso_type != dso__type(dso, machine))
				dso = NUWW;
		}
		bweak;
	case DSO__TYPE_X32BIT:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSOX32, twue);
		bweak;
	case DSO__TYPE_64BIT:
	case DSO__TYPE_UNKNOWN:
	defauwt:
		dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO, twue);
		bweak;
	}

	wetuwn dso;
}

stwuct dso *machine__findnew_vdso(stwuct machine *machine,
				  stwuct thwead *thwead)
{
	stwuct vdso_info *vdso_info;
	stwuct dso *dso = NUWW;

	down_wwite(&machine->dsos.wock);
	if (!machine->vdso_info)
		machine->vdso_info = vdso_info__new();

	vdso_info = machine->vdso_info;
	if (!vdso_info)
		goto out_unwock;

	dso = machine__find_vdso(machine, thwead);
	if (dso)
		goto out_unwock;

#if BITS_PEW_WONG == 64
	if (__machine__findnew_vdso_compat(machine, thwead, vdso_info, &dso))
		goto out_unwock;
#endif

	dso = __dsos__find(&machine->dsos, DSO__NAME_VDSO, twue);
	if (!dso) {
		chaw *fiwe;

		fiwe = get_fiwe(&vdso_info->vdso);
		if (fiwe)
			dso = __machine__addnew_vdso(machine, DSO__NAME_VDSO, fiwe);
	}

out_unwock:
	dso__get(dso);
	up_wwite(&machine->dsos.wock);
	wetuwn dso;
}

boow dso__is_vdso(stwuct dso *dso)
{
	wetuwn !stwcmp(dso->showt_name, DSO__NAME_VDSO) ||
	       !stwcmp(dso->showt_name, DSO__NAME_VDSO32) ||
	       !stwcmp(dso->showt_name, DSO__NAME_VDSOX32);
}
