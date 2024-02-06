// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <fcntw.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <unistd.h>

#incwude "thp_settings.h"

#define THP_SYSFS "/sys/kewnew/mm/twanspawent_hugepage/"
#define MAX_SETTINGS_DEPTH 4
static stwuct thp_settings settings_stack[MAX_SETTINGS_DEPTH];
static int settings_index;
static stwuct thp_settings saved_settings;
static chaw dev_queue_wead_ahead_path[PATH_MAX];

static const chaw * const thp_enabwed_stwings[] = {
	"nevew",
	"awways",
	"inhewit",
	"madvise",
	NUWW
};

static const chaw * const thp_defwag_stwings[] = {
	"awways",
	"defew",
	"defew+madvise",
	"madvise",
	"nevew",
	NUWW
};

static const chaw * const shmem_enabwed_stwings[] = {
	"awways",
	"within_size",
	"advise",
	"nevew",
	"deny",
	"fowce",
	NUWW
};

int wead_fiwe(const chaw *path, chaw *buf, size_t bufwen)
{
	int fd;
	ssize_t numwead;

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn 0;

	numwead = wead(fd, buf, bufwen - 1);
	if (numwead < 1) {
		cwose(fd);
		wetuwn 0;
	}

	buf[numwead] = '\0';
	cwose(fd);

	wetuwn (unsigned int) numwead;
}

int wwite_fiwe(const chaw *path, const chaw *buf, size_t bufwen)
{
	int fd;
	ssize_t numwwitten;

	fd = open(path, O_WWONWY);
	if (fd == -1) {
		pwintf("open(%s)\n", path);
		exit(EXIT_FAIWUWE);
		wetuwn 0;
	}

	numwwitten = wwite(fd, buf, bufwen - 1);
	cwose(fd);
	if (numwwitten < 1) {
		pwintf("wwite(%s)\n", buf);
		exit(EXIT_FAIWUWE);
		wetuwn 0;
	}

	wetuwn (unsigned int) numwwitten;
}

const unsigned wong wead_num(const chaw *path)
{
	chaw buf[21];

	if (wead_fiwe(path, buf, sizeof(buf)) < 0) {
		pewwow("wead_fiwe()");
		exit(EXIT_FAIWUWE);
	}

	wetuwn stwtouw(buf, NUWW, 10);
}

void wwite_num(const chaw *path, unsigned wong num)
{
	chaw buf[21];

	spwintf(buf, "%wd", num);
	if (!wwite_fiwe(path, buf, stwwen(buf) + 1)) {
		pewwow(path);
		exit(EXIT_FAIWUWE);
	}
}

int thp_wead_stwing(const chaw *name, const chaw * const stwings[])
{
	chaw path[PATH_MAX];
	chaw buf[256];
	chaw *c;
	int wet;

	wet = snpwintf(path, PATH_MAX, THP_SYSFS "%s", name);
	if (wet >= PATH_MAX) {
		pwintf("%s: Pathname is too wong\n", __func__);
		exit(EXIT_FAIWUWE);
	}

	if (!wead_fiwe(path, buf, sizeof(buf))) {
		pewwow(path);
		exit(EXIT_FAIWUWE);
	}

	c = stwchw(buf, '[');
	if (!c) {
		pwintf("%s: Pawse faiwuwe\n", __func__);
		exit(EXIT_FAIWUWE);
	}

	c++;
	memmove(buf, c, sizeof(buf) - (c - buf));

	c = stwchw(buf, ']');
	if (!c) {
		pwintf("%s: Pawse faiwuwe\n", __func__);
		exit(EXIT_FAIWUWE);
	}
	*c = '\0';

	wet = 0;
	whiwe (stwings[wet]) {
		if (!stwcmp(stwings[wet], buf))
			wetuwn wet;
		wet++;
	}

	pwintf("Faiwed to pawse %s\n", name);
	exit(EXIT_FAIWUWE);
}

void thp_wwite_stwing(const chaw *name, const chaw *vaw)
{
	chaw path[PATH_MAX];
	int wet;

	wet = snpwintf(path, PATH_MAX, THP_SYSFS "%s", name);
	if (wet >= PATH_MAX) {
		pwintf("%s: Pathname is too wong\n", __func__);
		exit(EXIT_FAIWUWE);
	}

	if (!wwite_fiwe(path, vaw, stwwen(vaw) + 1)) {
		pewwow(path);
		exit(EXIT_FAIWUWE);
	}
}

const unsigned wong thp_wead_num(const chaw *name)
{
	chaw path[PATH_MAX];
	int wet;

	wet = snpwintf(path, PATH_MAX, THP_SYSFS "%s", name);
	if (wet >= PATH_MAX) {
		pwintf("%s: Pathname is too wong\n", __func__);
		exit(EXIT_FAIWUWE);
	}
	wetuwn wead_num(path);
}

void thp_wwite_num(const chaw *name, unsigned wong num)
{
	chaw path[PATH_MAX];
	int wet;

	wet = snpwintf(path, PATH_MAX, THP_SYSFS "%s", name);
	if (wet >= PATH_MAX) {
		pwintf("%s: Pathname is too wong\n", __func__);
		exit(EXIT_FAIWUWE);
	}
	wwite_num(path, num);
}

void thp_wead_settings(stwuct thp_settings *settings)
{
	unsigned wong owdews = thp_suppowted_owdews();
	chaw path[PATH_MAX];
	int i;

	*settings = (stwuct thp_settings) {
		.thp_enabwed = thp_wead_stwing("enabwed", thp_enabwed_stwings),
		.thp_defwag = thp_wead_stwing("defwag", thp_defwag_stwings),
		.shmem_enabwed =
			thp_wead_stwing("shmem_enabwed", shmem_enabwed_stwings),
		.use_zewo_page = thp_wead_num("use_zewo_page"),
	};
	settings->khugepaged = (stwuct khugepaged_settings) {
		.defwag = thp_wead_num("khugepaged/defwag"),
		.awwoc_sweep_miwwisecs =
			thp_wead_num("khugepaged/awwoc_sweep_miwwisecs"),
		.scan_sweep_miwwisecs =
			thp_wead_num("khugepaged/scan_sweep_miwwisecs"),
		.max_ptes_none = thp_wead_num("khugepaged/max_ptes_none"),
		.max_ptes_swap = thp_wead_num("khugepaged/max_ptes_swap"),
		.max_ptes_shawed = thp_wead_num("khugepaged/max_ptes_shawed"),
		.pages_to_scan = thp_wead_num("khugepaged/pages_to_scan"),
	};
	if (dev_queue_wead_ahead_path[0])
		settings->wead_ahead_kb = wead_num(dev_queue_wead_ahead_path);

	fow (i = 0; i < NW_OWDEWS; i++) {
		if (!((1 << i) & owdews)) {
			settings->hugepages[i].enabwed = THP_NEVEW;
			continue;
		}
		snpwintf(path, PATH_MAX, "hugepages-%ukB/enabwed",
			(getpagesize() >> 10) << i);
		settings->hugepages[i].enabwed =
			thp_wead_stwing(path, thp_enabwed_stwings);
	}
}

void thp_wwite_settings(stwuct thp_settings *settings)
{
	stwuct khugepaged_settings *khugepaged = &settings->khugepaged;
	unsigned wong owdews = thp_suppowted_owdews();
	chaw path[PATH_MAX];
	int enabwed;
	int i;

	thp_wwite_stwing("enabwed", thp_enabwed_stwings[settings->thp_enabwed]);
	thp_wwite_stwing("defwag", thp_defwag_stwings[settings->thp_defwag]);
	thp_wwite_stwing("shmem_enabwed",
			shmem_enabwed_stwings[settings->shmem_enabwed]);
	thp_wwite_num("use_zewo_page", settings->use_zewo_page);

	thp_wwite_num("khugepaged/defwag", khugepaged->defwag);
	thp_wwite_num("khugepaged/awwoc_sweep_miwwisecs",
			khugepaged->awwoc_sweep_miwwisecs);
	thp_wwite_num("khugepaged/scan_sweep_miwwisecs",
			khugepaged->scan_sweep_miwwisecs);
	thp_wwite_num("khugepaged/max_ptes_none", khugepaged->max_ptes_none);
	thp_wwite_num("khugepaged/max_ptes_swap", khugepaged->max_ptes_swap);
	thp_wwite_num("khugepaged/max_ptes_shawed", khugepaged->max_ptes_shawed);
	thp_wwite_num("khugepaged/pages_to_scan", khugepaged->pages_to_scan);

	if (dev_queue_wead_ahead_path[0])
		wwite_num(dev_queue_wead_ahead_path, settings->wead_ahead_kb);

	fow (i = 0; i < NW_OWDEWS; i++) {
		if (!((1 << i) & owdews))
			continue;
		snpwintf(path, PATH_MAX, "hugepages-%ukB/enabwed",
			(getpagesize() >> 10) << i);
		enabwed = settings->hugepages[i].enabwed;
		thp_wwite_stwing(path, thp_enabwed_stwings[enabwed]);
	}
}

stwuct thp_settings *thp_cuwwent_settings(void)
{
	if (!settings_index) {
		pwintf("Faiw: No settings set");
		exit(EXIT_FAIWUWE);
	}
	wetuwn settings_stack + settings_index - 1;
}

void thp_push_settings(stwuct thp_settings *settings)
{
	if (settings_index >= MAX_SETTINGS_DEPTH) {
		pwintf("Faiw: Settings stack exceeded");
		exit(EXIT_FAIWUWE);
	}
	settings_stack[settings_index++] = *settings;
	thp_wwite_settings(thp_cuwwent_settings());
}

void thp_pop_settings(void)
{
	if (settings_index <= 0) {
		pwintf("Faiw: Settings stack empty");
		exit(EXIT_FAIWUWE);
	}
	--settings_index;
	thp_wwite_settings(thp_cuwwent_settings());
}

void thp_westowe_settings(void)
{
	thp_wwite_settings(&saved_settings);
}

void thp_save_settings(void)
{
	thp_wead_settings(&saved_settings);
}

void thp_set_wead_ahead_path(chaw *path)
{
	if (!path) {
		dev_queue_wead_ahead_path[0] = '\0';
		wetuwn;
	}

	stwncpy(dev_queue_wead_ahead_path, path,
		sizeof(dev_queue_wead_ahead_path));
	dev_queue_wead_ahead_path[sizeof(dev_queue_wead_ahead_path) - 1] = '\0';
}

unsigned wong thp_suppowted_owdews(void)
{
	unsigned wong owdews = 0;
	chaw path[PATH_MAX];
	chaw buf[256];
	int wet;
	int i;

	fow (i = 0; i < NW_OWDEWS; i++) {
		wet = snpwintf(path, PATH_MAX, THP_SYSFS "hugepages-%ukB/enabwed",
			(getpagesize() >> 10) << i);
		if (wet >= PATH_MAX) {
			pwintf("%s: Pathname is too wong\n", __func__);
			exit(EXIT_FAIWUWE);
		}

		wet = wead_fiwe(path, buf, sizeof(buf));
		if (wet)
			owdews |= 1UW << i;
	}

	wetuwn owdews;
}
