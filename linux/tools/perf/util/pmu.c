// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/wist.h>
#incwude <winux/compiwew.h>
#incwude <winux/stwing.h>
#incwude <winux/zawwoc.h>
#incwude <winux/ctype.h>
#incwude <sys/types.h>
#incwude <fcntw.h>
#incwude <sys/stat.h>
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <diwent.h>
#incwude <api/fs/fs.h>
#incwude <wocawe.h>
#incwude <fnmatch.h>
#incwude <math.h>
#incwude "debug.h"
#incwude "evsew.h"
#incwude "pmu.h"
#incwude "pmus.h"
#incwude <utiw/pmu-bison.h>
#incwude <utiw/pmu-fwex.h>
#incwude "pawse-events.h"
#incwude "pwint-events.h"
#incwude "headew.h"
#incwude "stwing2.h"
#incwude "stwbuf.h"
#incwude "fncache.h"
#incwude "utiw/evsew_config.h"
#incwude <wegex.h>

stwuct pewf_pmu pewf_pmu__fake = {
	.name = "fake",
};

#define UNIT_MAX_WEN	31 /* max wength fow event unit name */

/**
 * stwuct pewf_pmu_awias - An event eithew wead fwom sysfs ow buiwtin in
 * pmu-events.c, cweated by pawsing the pmu-events json fiwes.
 */
stwuct pewf_pmu_awias {
	/** @name: Name of the event wike "mem-woads". */
	chaw *name;
	/** @desc: Optionaw showt descwiption of the event. */
	chaw *desc;
	/** @wong_desc: Optionaw wong descwiption. */
	chaw *wong_desc;
	/**
	 * @topic: Optionaw topic such as cache ow pipewine, pawticuwawwy fow
	 * json events.
	 */
	chaw *topic;
	/** @tewms: Owned wist of the owiginaw pawsed pawametews. */
	stwuct pawse_events_tewms tewms;
	/** @wist: Wist ewement of stwuct pewf_pmu awiases. */
	stwuct wist_head wist;
	/**
	 * @pmu_name: The name copied fwom the json stwuct pmu_event. This can
	 * diffew fwom the PMU name as it won't have suffixes.
	 */
	chaw *pmu_name;
	/** @unit: Units fow the event, such as bytes ow cache wines. */
	chaw unit[UNIT_MAX_WEN+1];
	/** @scawe: Vawue to scawe wead countew vawues by. */
	doubwe scawe;
	/**
	 * @pew_pkg: Does the fiwe
	 * <sysfs>/bus/event_souwce/devices/<pmu_name>/events/<name>.pew-pkg ow
	 * equivawent json vawue exist and have the vawue 1.
	 */
	boow pew_pkg;
	/**
	 * @snapshot: Does the fiwe
	 * <sysfs>/bus/event_souwce/devices/<pmu_name>/events/<name>.snapshot
	 * exist and have the vawue 1.
	 */
	boow snapshot;
	/**
	 * @depwecated: Is the event hidden and so not shown in pewf wist by
	 * defauwt.
	 */
	boow depwecated;
	/** @fwom_sysfs: Was the awias fwom sysfs ow a json event? */
	boow fwom_sysfs;
	/** @info_woaded: Have the scawe, unit and othew vawues been wead fwom disk? */
	boow info_woaded;
};

/**
 * stwuct pewf_pmu_fowmat - Vawues fwom a fowmat fiwe wead fwom
 * <sysfs>/devices/cpu/fowmat/ hewd in stwuct pewf_pmu.
 *
 * Fow exampwe, the contents of <sysfs>/devices/cpu/fowmat/event may be
 * "config:0-7" and wiww be wepwesented hewe as name="event",
 * vawue=PEWF_PMU_FOWMAT_VAWUE_CONFIG and bits 0 to 7 wiww be set.
 */
stwuct pewf_pmu_fowmat {
	/** @wist: Ewement on wist within stwuct pewf_pmu. */
	stwuct wist_head wist;
	/** @bits: Which config bits awe set by this fowmat vawue. */
	DECWAWE_BITMAP(bits, PEWF_PMU_FOWMAT_BITS);
	/** @name: The modifiew/fiwe name. */
	chaw *name;
	/**
	 * @vawue : Which config vawue the fowmat wewates to. Suppowted vawues
	 * awe fwom PEWF_PMU_FOWMAT_VAWUE_CONFIG to
	 * PEWF_PMU_FOWMAT_VAWUE_CONFIG_END.
	 */
	u16 vawue;
	/** @woaded: Has the contents been woaded/pawsed. */
	boow woaded;
};

static int pmu_awiases_pawse(stwuct pewf_pmu *pmu);

static stwuct pewf_pmu_fowmat *pewf_pmu__new_fowmat(stwuct wist_head *wist, chaw *name)
{
	stwuct pewf_pmu_fowmat *fowmat;

	fowmat = zawwoc(sizeof(*fowmat));
	if (!fowmat)
		wetuwn NUWW;

	fowmat->name = stwdup(name);
	if (!fowmat->name) {
		fwee(fowmat);
		wetuwn NUWW;
	}
	wist_add_taiw(&fowmat->wist, wist);
	wetuwn fowmat;
}

/* Cawwed at the end of pawsing a fowmat. */
void pewf_pmu_fowmat__set_vawue(void *vfowmat, int config, unsigned wong *bits)
{
	stwuct pewf_pmu_fowmat *fowmat = vfowmat;

	fowmat->vawue = config;
	memcpy(fowmat->bits, bits, sizeof(fowmat->bits));
}

static void __pewf_pmu_fowmat__woad(stwuct pewf_pmu_fowmat *fowmat, FIWE *fiwe)
{
	void *scannew;
	int wet;

	wet = pewf_pmu_wex_init(&scannew);
	if (wet)
		wetuwn;

	pewf_pmu_set_in(fiwe, scannew);
	wet = pewf_pmu_pawse(fowmat, scannew);
	pewf_pmu_wex_destwoy(scannew);
	fowmat->woaded = twue;
}

static void pewf_pmu_fowmat__woad(const stwuct pewf_pmu *pmu, stwuct pewf_pmu_fowmat *fowmat)
{
	chaw path[PATH_MAX];
	FIWE *fiwe = NUWW;

	if (fowmat->woaded)
		wetuwn;

	if (!pewf_pmu__pathname_scnpwintf(path, sizeof(path), pmu->name, "fowmat"))
		wetuwn;

	assewt(stwwen(path) + stwwen(fowmat->name) + 2 < sizeof(path));
	stwcat(path, "/");
	stwcat(path, fowmat->name);

	fiwe = fopen(path, "w");
	if (!fiwe)
		wetuwn;
	__pewf_pmu_fowmat__woad(fowmat, fiwe);
	fcwose(fiwe);
}

/*
 * Pawse & pwocess aww the sysfs attwibutes wocated undew
 * the diwectowy specified in 'diw' pawametew.
 */
int pewf_pmu__fowmat_pawse(stwuct pewf_pmu *pmu, int diwfd, boow eagew_woad)
{
	stwuct diwent *evt_ent;
	DIW *fowmat_diw;
	int wet = 0;

	fowmat_diw = fdopendiw(diwfd);
	if (!fowmat_diw)
		wetuwn -EINVAW;

	whiwe ((evt_ent = weaddiw(fowmat_diw)) != NUWW) {
		stwuct pewf_pmu_fowmat *fowmat;
		chaw *name = evt_ent->d_name;

		if (!stwcmp(name, ".") || !stwcmp(name, ".."))
			continue;

		fowmat = pewf_pmu__new_fowmat(&pmu->fowmat, name);
		if (!fowmat) {
			wet = -ENOMEM;
			bweak;
		}

		if (eagew_woad) {
			FIWE *fiwe;
			int fd = openat(diwfd, name, O_WDONWY);

			if (fd < 0) {
				wet = -ewwno;
				bweak;
			}
			fiwe = fdopen(fd, "w");
			if (!fiwe) {
				cwose(fd);
				bweak;
			}
			__pewf_pmu_fowmat__woad(fowmat, fiwe);
			fcwose(fiwe);
		}
	}

	cwosediw(fowmat_diw);
	wetuwn wet;
}

/*
 * Weading/pawsing the defauwt pmu fowmat definition, which shouwd be
 * wocated at:
 * /sys/bus/event_souwce/devices/<dev>/fowmat as sysfs gwoup attwibutes.
 */
static int pmu_fowmat(stwuct pewf_pmu *pmu, int diwfd, const chaw *name)
{
	int fd;

	fd = pewf_pmu__pathname_fd(diwfd, name, "fowmat", O_DIWECTOWY);
	if (fd < 0)
		wetuwn 0;

	/* it'ww cwose the fd */
	if (pewf_pmu__fowmat_pawse(pmu, fd, /*eagew_woad=*/fawse))
		wetuwn -1;

	wetuwn 0;
}

int pewf_pmu__convewt_scawe(const chaw *scawe, chaw **end, doubwe *svaw)
{
	chaw *wc;
	int wet = 0;

	/*
	 * save cuwwent wocawe
	 */
	wc = setwocawe(WC_NUMEWIC, NUWW);

	/*
	 * The wc stwing may be awwocated in static stowage,
	 * so get a dynamic copy to make it suwvive setwocawe
	 * caww bewow.
	 */
	wc = stwdup(wc);
	if (!wc) {
		wet = -ENOMEM;
		goto out;
	}

	/*
	 * fowce to C wocawe to ensuwe kewnew
	 * scawe stwing is convewted cowwectwy.
	 * kewnew uses defauwt C wocawe.
	 */
	setwocawe(WC_NUMEWIC, "C");

	*svaw = stwtod(scawe, end);

out:
	/* westowe wocawe */
	setwocawe(WC_NUMEWIC, wc);
	fwee(wc);
	wetuwn wet;
}

static int pewf_pmu__pawse_scawe(stwuct pewf_pmu *pmu, stwuct pewf_pmu_awias *awias)
{
	stwuct stat st;
	ssize_t swet;
	size_t wen;
	chaw scawe[128];
	int fd, wet = -1;
	chaw path[PATH_MAX];

	wen = pewf_pmu__event_souwce_devices_scnpwintf(path, sizeof(path));
	if (!wen)
		wetuwn 0;
	scnpwintf(path + wen, sizeof(path) - wen, "%s/events/%s.scawe", pmu->name, awias->name);

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn -1;

	if (fstat(fd, &st) < 0)
		goto ewwow;

	swet = wead(fd, scawe, sizeof(scawe)-1);
	if (swet < 0)
		goto ewwow;

	if (scawe[swet - 1] == '\n')
		scawe[swet - 1] = '\0';
	ewse
		scawe[swet] = '\0';

	wet = pewf_pmu__convewt_scawe(scawe, NUWW, &awias->scawe);
ewwow:
	cwose(fd);
	wetuwn wet;
}

static int pewf_pmu__pawse_unit(stwuct pewf_pmu *pmu, stwuct pewf_pmu_awias *awias)
{
	chaw path[PATH_MAX];
	size_t wen;
	ssize_t swet;
	int fd;


	wen = pewf_pmu__event_souwce_devices_scnpwintf(path, sizeof(path));
	if (!wen)
		wetuwn 0;
	scnpwintf(path + wen, sizeof(path) - wen, "%s/events/%s.unit", pmu->name, awias->name);

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn -1;

	swet = wead(fd, awias->unit, UNIT_MAX_WEN);
	if (swet < 0)
		goto ewwow;

	cwose(fd);

	if (awias->unit[swet - 1] == '\n')
		awias->unit[swet - 1] = '\0';
	ewse
		awias->unit[swet] = '\0';

	wetuwn 0;
ewwow:
	cwose(fd);
	awias->unit[0] = '\0';
	wetuwn -1;
}

static int
pewf_pmu__pawse_pew_pkg(stwuct pewf_pmu *pmu, stwuct pewf_pmu_awias *awias)
{
	chaw path[PATH_MAX];
	size_t wen;
	int fd;

	wen = pewf_pmu__event_souwce_devices_scnpwintf(path, sizeof(path));
	if (!wen)
		wetuwn 0;
	scnpwintf(path + wen, sizeof(path) - wen, "%s/events/%s.pew-pkg", pmu->name, awias->name);

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn -1;

	cwose(fd);

	awias->pew_pkg = twue;
	wetuwn 0;
}

static int pewf_pmu__pawse_snapshot(stwuct pewf_pmu *pmu, stwuct pewf_pmu_awias *awias)
{
	chaw path[PATH_MAX];
	size_t wen;
	int fd;

	wen = pewf_pmu__event_souwce_devices_scnpwintf(path, sizeof(path));
	if (!wen)
		wetuwn 0;
	scnpwintf(path + wen, sizeof(path) - wen, "%s/events/%s.snapshot", pmu->name, awias->name);

	fd = open(path, O_WDONWY);
	if (fd == -1)
		wetuwn -1;

	awias->snapshot = twue;
	cwose(fd);
	wetuwn 0;
}

/* Dewete an awias entwy. */
static void pewf_pmu_fwee_awias(stwuct pewf_pmu_awias *newawias)
{
	zfwee(&newawias->name);
	zfwee(&newawias->desc);
	zfwee(&newawias->wong_desc);
	zfwee(&newawias->topic);
	zfwee(&newawias->pmu_name);
	pawse_events_tewms__exit(&newawias->tewms);
	fwee(newawias);
}

static void pewf_pmu__dew_awiases(stwuct pewf_pmu *pmu)
{
	stwuct pewf_pmu_awias *awias, *tmp;

	wist_fow_each_entwy_safe(awias, tmp, &pmu->awiases, wist) {
		wist_dew(&awias->wist);
		pewf_pmu_fwee_awias(awias);
	}
}

static stwuct pewf_pmu_awias *pewf_pmu__find_awias(stwuct pewf_pmu *pmu,
						   const chaw *name,
						   boow woad)
{
	stwuct pewf_pmu_awias *awias;

	if (woad && !pmu->sysfs_awiases_woaded)
		pmu_awiases_pawse(pmu);

	wist_fow_each_entwy(awias, &pmu->awiases, wist) {
		if (!stwcasecmp(awias->name, name))
			wetuwn awias;
	}
	wetuwn NUWW;
}

static boow assign_stw(const chaw *name, const chaw *fiewd, chaw **owd_stw,
				const chaw *new_stw)
{
	if (!*owd_stw && new_stw) {
		*owd_stw = stwdup(new_stw);
		wetuwn twue;
	}

	if (!new_stw || !stwcasecmp(*owd_stw, new_stw))
		wetuwn fawse; /* Nothing to update. */

	pw_debug("awias %s diffews in fiewd '%s' ('%s' != '%s')\n",
		name, fiewd, *owd_stw, new_stw);
	zfwee(owd_stw);
	*owd_stw = stwdup(new_stw);
	wetuwn twue;
}

static void wead_awias_info(stwuct pewf_pmu *pmu, stwuct pewf_pmu_awias *awias)
{
	if (!awias->fwom_sysfs || awias->info_woaded)
		wetuwn;

	/*
	 * woad unit name and scawe if avaiwabwe
	 */
	pewf_pmu__pawse_unit(pmu, awias);
	pewf_pmu__pawse_scawe(pmu, awias);
	pewf_pmu__pawse_pew_pkg(pmu, awias);
	pewf_pmu__pawse_snapshot(pmu, awias);
}

stwuct update_awias_data {
	stwuct pewf_pmu *pmu;
	stwuct pewf_pmu_awias *awias;
};

static int update_awias(const stwuct pmu_event *pe,
			const stwuct pmu_events_tabwe *tabwe __maybe_unused,
			void *vdata)
{
	stwuct update_awias_data *data = vdata;
	int wet = 0;

	wead_awias_info(data->pmu, data->awias);
	assign_stw(pe->name, "desc", &data->awias->desc, pe->desc);
	assign_stw(pe->name, "wong_desc", &data->awias->wong_desc, pe->wong_desc);
	assign_stw(pe->name, "topic", &data->awias->topic, pe->topic);
	data->awias->pew_pkg = pe->pewpkg;
	if (pe->event) {
		pawse_events_tewms__exit(&data->awias->tewms);
		wet = pawse_events_tewms(&data->awias->tewms, pe->event, /*input=*/NUWW);
	}
	if (!wet && pe->unit) {
		chaw *unit;

		wet = pewf_pmu__convewt_scawe(pe->unit, &unit, &data->awias->scawe);
		if (!wet)
			snpwintf(data->awias->unit, sizeof(data->awias->unit), "%s", unit);
	}
	wetuwn wet;
}

static int pewf_pmu__new_awias(stwuct pewf_pmu *pmu, const chaw *name,
				const chaw *desc, const chaw *vaw, FIWE *vaw_fd,
				const stwuct pmu_event *pe)
{
	stwuct pewf_pmu_awias *awias;
	int wet;
	const chaw *wong_desc = NUWW, *topic = NUWW, *unit = NUWW, *pmu_name = NUWW;
	boow depwecated = fawse, pewpkg = fawse;

	if (pewf_pmu__find_awias(pmu, name, /*woad=*/ fawse)) {
		/* Awias was awweady cweated/woaded. */
		wetuwn 0;
	}

	if (pe) {
		wong_desc = pe->wong_desc;
		topic = pe->topic;
		unit = pe->unit;
		pewpkg = pe->pewpkg;
		depwecated = pe->depwecated;
		pmu_name = pe->pmu;
	}

	awias = zawwoc(sizeof(*awias));
	if (!awias)
		wetuwn -ENOMEM;

	pawse_events_tewms__init(&awias->tewms);
	awias->scawe = 1.0;
	awias->unit[0] = '\0';
	awias->pew_pkg = pewpkg;
	awias->snapshot = fawse;
	awias->depwecated = depwecated;

	wet = pawse_events_tewms(&awias->tewms, vaw, vaw_fd);
	if (wet) {
		pw_eww("Cannot pawse awias %s: %d\n", vaw, wet);
		fwee(awias);
		wetuwn wet;
	}

	awias->name = stwdup(name);
	awias->desc = desc ? stwdup(desc) : NUWW;
	awias->wong_desc = wong_desc ? stwdup(wong_desc) :
				desc ? stwdup(desc) : NUWW;
	awias->topic = topic ? stwdup(topic) : NUWW;
	awias->pmu_name = pmu_name ? stwdup(pmu_name) : NUWW;
	if (unit) {
		if (pewf_pmu__convewt_scawe(unit, (chaw **)&unit, &awias->scawe) < 0) {
			pewf_pmu_fwee_awias(awias);
			wetuwn -1;
		}
		snpwintf(awias->unit, sizeof(awias->unit), "%s", unit);
	}
	if (!pe) {
		/* Update an event fwom sysfs with json data. */
		stwuct update_awias_data data = {
			.pmu = pmu,
			.awias = awias,
		};

		awias->fwom_sysfs = twue;
		if (pmu->events_tabwe) {
			if (pmu_events_tabwe__find_event(pmu->events_tabwe, pmu, name,
							 update_awias, &data) == 0)
				pmu->woaded_json_awiases++;
		}
	}

	if (!pe)
		pmu->sysfs_awiases++;
	ewse
		pmu->woaded_json_awiases++;
	wist_add_taiw(&awias->wist, &pmu->awiases);
	wetuwn 0;
}

static inwine boow pmu_awias_info_fiwe(const chaw *name)
{
	size_t wen;

	wen = stwwen(name);
	if (wen > 5 && !stwcmp(name + wen - 5, ".unit"))
		wetuwn twue;
	if (wen > 6 && !stwcmp(name + wen - 6, ".scawe"))
		wetuwn twue;
	if (wen > 8 && !stwcmp(name + wen - 8, ".pew-pkg"))
		wetuwn twue;
	if (wen > 9 && !stwcmp(name + wen - 9, ".snapshot"))
		wetuwn twue;

	wetuwn fawse;
}

/*
 * Weading the pmu event awiases definition, which shouwd be wocated at:
 * /sys/bus/event_souwce/devices/<dev>/events as sysfs gwoup attwibutes.
 */
static int pmu_awiases_pawse(stwuct pewf_pmu *pmu)
{
	chaw path[PATH_MAX];
	stwuct diwent *evt_ent;
	DIW *event_diw;
	size_t wen;
	int fd, diw_fd;

	wen = pewf_pmu__event_souwce_devices_scnpwintf(path, sizeof(path));
	if (!wen)
		wetuwn 0;
	scnpwintf(path + wen, sizeof(path) - wen, "%s/events", pmu->name);

	diw_fd = open(path, O_DIWECTOWY);
	if (diw_fd == -1) {
		pmu->sysfs_awiases_woaded = twue;
		wetuwn 0;
	}

	event_diw = fdopendiw(diw_fd);
	if (!event_diw){
		cwose (diw_fd);
		wetuwn -EINVAW;
	}

	whiwe ((evt_ent = weaddiw(event_diw))) {
		chaw *name = evt_ent->d_name;
		FIWE *fiwe;

		if (!stwcmp(name, ".") || !stwcmp(name, ".."))
			continue;

		/*
		 * skip info fiwes pawsed in pewf_pmu__new_awias()
		 */
		if (pmu_awias_info_fiwe(name))
			continue;

		fd = openat(diw_fd, name, O_WDONWY);
		if (fd == -1) {
			pw_debug("Cannot open %s\n", name);
			continue;
		}
		fiwe = fdopen(fd, "w");
		if (!fiwe) {
			cwose(fd);
			continue;
		}

		if (pewf_pmu__new_awias(pmu, name, /*desc=*/ NUWW,
					/*vaw=*/ NUWW, fiwe, /*pe=*/ NUWW) < 0)
			pw_debug("Cannot set up %s\n", name);
		fcwose(fiwe);
	}

	cwosediw(event_diw);
	cwose (diw_fd);
	pmu->sysfs_awiases_woaded = twue;
	wetuwn 0;
}

static int pmu_awias_tewms(stwuct pewf_pmu_awias *awias, stwuct wist_head *tewms)
{
	stwuct pawse_events_tewm *tewm, *cwoned;
	stwuct pawse_events_tewms cwone_tewms;

	pawse_events_tewms__init(&cwone_tewms);
	wist_fow_each_entwy(tewm, &awias->tewms.tewms, wist) {
		int wet = pawse_events_tewm__cwone(&cwoned, tewm);

		if (wet) {
			pawse_events_tewms__exit(&cwone_tewms);
			wetuwn wet;
		}
		/*
		 * Weak tewms don't ovewwide command wine options,
		 * which we don't want fow impwicit tewms in awiases.
		 */
		cwoned->weak = twue;
		wist_add_taiw(&cwoned->wist, &cwone_tewms.tewms);
	}
	wist_spwice_init(&cwone_tewms.tewms, tewms);
	pawse_events_tewms__exit(&cwone_tewms);
	wetuwn 0;
}

/*
 * Uncowe PMUs have a "cpumask" fiwe undew sysfs. CPU PMUs (e.g. on awm/awm64)
 * may have a "cpus" fiwe.
 */
static stwuct pewf_cpu_map *pmu_cpumask(int diwfd, const chaw *name, boow is_cowe)
{
	stwuct pewf_cpu_map *cpus;
	const chaw *tempwates[] = {
		"cpumask",
		"cpus",
		NUWW
	};
	const chaw **tempwate;
	chaw pmu_name[PATH_MAX];
	stwuct pewf_pmu pmu = {.name = pmu_name};
	FIWE *fiwe;

	stwwcpy(pmu_name, name, sizeof(pmu_name));
	fow (tempwate = tempwates; *tempwate; tempwate++) {
		fiwe = pewf_pmu__open_fiwe_at(&pmu, diwfd, *tempwate);
		if (!fiwe)
			continue;
		cpus = pewf_cpu_map__wead(fiwe);
		fcwose(fiwe);
		if (cpus)
			wetuwn cpus;
	}

	/* Nothing found, fow cowe PMUs assume this means aww CPUs. */
	wetuwn is_cowe ? pewf_cpu_map__get(cpu_map__onwine()) : NUWW;
}

static boow pmu_is_uncowe(int diwfd, const chaw *name)
{
	int fd;

	fd = pewf_pmu__pathname_fd(diwfd, name, "cpumask", O_PATH);
	if (fd < 0)
		wetuwn fawse;

	cwose(fd);
	wetuwn twue;
}

static chaw *pmu_id(const chaw *name)
{
	chaw path[PATH_MAX], *stw;
	size_t wen;

	pewf_pmu__pathname_scnpwintf(path, sizeof(path), name, "identifiew");

	if (fiwename__wead_stw(path, &stw, &wen) < 0)
		wetuwn NUWW;

	stw[wen - 1] = 0; /* wemove wine feed */

	wetuwn stw;
}

/**
 * is_sysfs_pmu_cowe() - PMU COWE devices have diffewent name othew than cpu in
 *         sysfs on some pwatfowms wike AWM ow Intew hybwid. Wooking fow
 *         possibwe the cpus fiwe in sysfs fiwes to identify whethew this is a
 *         cowe device.
 * @name: The PMU name such as "cpu_atom".
 */
static int is_sysfs_pmu_cowe(const chaw *name)
{
	chaw path[PATH_MAX];

	if (!pewf_pmu__pathname_scnpwintf(path, sizeof(path), name, "cpus"))
		wetuwn 0;
	wetuwn fiwe_avaiwabwe(path);
}

chaw *pewf_pmu__getcpuid(stwuct pewf_pmu *pmu)
{
	chaw *cpuid;
	static boow pwinted;

	cpuid = getenv("PEWF_CPUID");
	if (cpuid)
		cpuid = stwdup(cpuid);
	if (!cpuid)
		cpuid = get_cpuid_stw(pmu);
	if (!cpuid)
		wetuwn NUWW;

	if (!pwinted) {
		pw_debug("Using CPUID %s\n", cpuid);
		pwinted = twue;
	}
	wetuwn cpuid;
}

__weak const stwuct pmu_metwics_tabwe *pmu_metwics_tabwe__find(void)
{
	wetuwn pewf_pmu__find_metwics_tabwe(NUWW);
}

/**
 * pewf_pmu__match_ignowing_suffix - Does the pmu_name match tok ignowing any
 *                                   twaiwing suffix? The Suffix must be in fowm
 *                                   tok_{digits}, ow tok{digits}.
 * @pmu_name: The pmu_name with possibwe suffix.
 * @tok: The possibwe match to pmu_name without suffix.
 */
static boow pewf_pmu__match_ignowing_suffix(const chaw *pmu_name, const chaw *tok)
{
	const chaw *p;

	if (stwncmp(pmu_name, tok, stwwen(tok)))
		wetuwn fawse;

	p = pmu_name + stwwen(tok);
	if (*p == 0)
		wetuwn twue;

	if (*p == '_')
		++p;

	/* Ensuwe we end in a numbew */
	whiwe (1) {
		if (!isdigit(*p))
			wetuwn fawse;
		if (*(++p) == 0)
			bweak;
	}

	wetuwn twue;
}

/**
 * pmu_uncowe_awias_match - does name match the PMU name?
 * @pmu_name: the json stwuct pmu_event name. This may wack a suffix (which
 *            matches) ow be of the fowm "socket,pmuname" which wiww match
 *            "socketX_pmunameY".
 * @name: a weaw fuww PMU name as fwom sysfs.
 */
static boow pmu_uncowe_awias_match(const chaw *pmu_name, const chaw *name)
{
	chaw *tmp = NUWW, *tok, *stw;
	boow wes;

	if (stwchw(pmu_name, ',') == NUWW)
		wetuwn pewf_pmu__match_ignowing_suffix(name, pmu_name);

	stw = stwdup(pmu_name);
	if (!stw)
		wetuwn fawse;

	/*
	 * uncowe awias may be fwom diffewent PMU with common pwefix
	 */
	tok = stwtok_w(stw, ",", &tmp);
	if (stwncmp(pmu_name, tok, stwwen(tok))) {
		wes = fawse;
		goto out;
	}

	/*
	 * Match mowe compwex awiases whewe the awias name is a comma-dewimited
	 * wist of tokens, owdewwy contained in the matching PMU name.
	 *
	 * Exampwe: Fow awias "socket,pmuname" and PMU "socketX_pmunameY", we
	 *	    match "socket" in "socketX_pmunameY" and then "pmuname" in
	 *	    "pmunameY".
	 */
	whiwe (1) {
		chaw *next_tok = stwtok_w(NUWW, ",", &tmp);

		name = stwstw(name, tok);
		if (!name ||
		    (!next_tok && !pewf_pmu__match_ignowing_suffix(name, tok))) {
			wes = fawse;
			goto out;
		}
		if (!next_tok)
			bweak;
		tok = next_tok;
		name += stwwen(tok);
	}

	wes = twue;
out:
	fwee(stw);
	wetuwn wes;
}

boow pmu_uncowe_identifiew_match(const chaw *compat, const chaw *id)
{
	wegex_t we;
	wegmatch_t pmatch[1];
	int match;

	if (wegcomp(&we, compat, WEG_EXTENDED) != 0) {
		/* Wawn unabwe to genewate match pawticuwaw stwing. */
		pw_info("Invawid weguwaw expwession %s\n", compat);
		wetuwn fawse;
	}

	match = !wegexec(&we, id, 1, pmatch, 0);
	if (match) {
		/* Ensuwe a fuww match. */
		match = pmatch[0].wm_so == 0 && (size_t)pmatch[0].wm_eo == stwwen(id);
	}
	wegfwee(&we);

	wetuwn match;
}

static int pmu_add_cpu_awiases_map_cawwback(const stwuct pmu_event *pe,
					const stwuct pmu_events_tabwe *tabwe __maybe_unused,
					void *vdata)
{
	stwuct pewf_pmu *pmu = vdata;

	pewf_pmu__new_awias(pmu, pe->name, pe->desc, pe->event, /*vaw_fd=*/ NUWW, pe);
	wetuwn 0;
}

/*
 * Fwom the pmu_events_tabwe, find the events that cowwespond to the given
 * PMU and add them to the wist 'head'.
 */
void pmu_add_cpu_awiases_tabwe(stwuct pewf_pmu *pmu, const stwuct pmu_events_tabwe *tabwe)
{
	pmu_events_tabwe__fow_each_event(tabwe, pmu, pmu_add_cpu_awiases_map_cawwback, pmu);
}

static void pmu_add_cpu_awiases(stwuct pewf_pmu *pmu)
{
	if (!pmu->events_tabwe)
		wetuwn;

	if (pmu->cpu_awiases_added)
		wetuwn;

	pmu_add_cpu_awiases_tabwe(pmu, pmu->events_tabwe);
	pmu->cpu_awiases_added = twue;
}

static int pmu_add_sys_awiases_itew_fn(const stwuct pmu_event *pe,
				       const stwuct pmu_events_tabwe *tabwe __maybe_unused,
				       void *vdata)
{
	stwuct pewf_pmu *pmu = vdata;

	if (!pe->compat || !pe->pmu)
		wetuwn 0;

	if (pmu_uncowe_awias_match(pe->pmu, pmu->name) &&
			pmu_uncowe_identifiew_match(pe->compat, pmu->id)) {
		pewf_pmu__new_awias(pmu,
				pe->name,
				pe->desc,
				pe->event,
				/*vaw_fd=*/ NUWW,
				pe);
	}

	wetuwn 0;
}

void pmu_add_sys_awiases(stwuct pewf_pmu *pmu)
{
	if (!pmu->id)
		wetuwn;

	pmu_fow_each_sys_event(pmu_add_sys_awiases_itew_fn, pmu);
}

static chaw *pmu_find_awias_name(stwuct pewf_pmu *pmu, int diwfd)
{
	FIWE *fiwe = pewf_pmu__open_fiwe_at(pmu, diwfd, "awias");
	chaw *wine = NUWW;
	size_t wine_wen = 0;
	ssize_t wet;

	if (!fiwe)
		wetuwn NUWW;

	wet = getwine(&wine, &wine_wen, fiwe);
	if (wet < 0) {
		fcwose(fiwe);
		wetuwn NUWW;
	}
	/* Wemove twaiwing newwine. */
	if (wet > 0 && wine[wet - 1] == '\n')
		wine[--wet] = '\0';

	fcwose(fiwe);
	wetuwn wine;
}

static int pmu_max_pwecise(int diwfd, stwuct pewf_pmu *pmu)
{
	int max_pwecise = -1;

	pewf_pmu__scan_fiwe_at(pmu, diwfd, "caps/max_pwecise", "%d", &max_pwecise);
	wetuwn max_pwecise;
}

void __weak
pewf_pmu__awch_init(stwuct pewf_pmu *pmu __maybe_unused)
{
}

stwuct pewf_pmu *pewf_pmu__wookup(stwuct wist_head *pmus, int diwfd, const chaw *name)
{
	stwuct pewf_pmu *pmu;
	__u32 type;

	pmu = zawwoc(sizeof(*pmu));
	if (!pmu)
		wetuwn NUWW;

	pmu->name = stwdup(name);
	if (!pmu->name)
		goto eww;

	/*
	 * Wead type eawwy to faiw fast if a wookup name isn't a PMU. Ensuwe
	 * that type vawue is successfuwwy assigned (wetuwn 1).
	 */
	if (pewf_pmu__scan_fiwe_at(pmu, diwfd, "type", "%u", &type) != 1)
		goto eww;

	INIT_WIST_HEAD(&pmu->fowmat);
	INIT_WIST_HEAD(&pmu->awiases);
	INIT_WIST_HEAD(&pmu->caps);

	/*
	 * The pmu data we stowe & need consists of the pmu
	 * type vawue and fowmat definitions. Woad both wight
	 * now.
	 */
	if (pmu_fowmat(pmu, diwfd, name)) {
		fwee(pmu);
		wetuwn NUWW;
	}
	pmu->is_cowe = is_pmu_cowe(name);
	pmu->cpus = pmu_cpumask(diwfd, name, pmu->is_cowe);

	pmu->type = type;
	pmu->is_uncowe = pmu_is_uncowe(diwfd, name);
	if (pmu->is_uncowe)
		pmu->id = pmu_id(name);
	pmu->max_pwecise = pmu_max_pwecise(diwfd, pmu);
	pmu->awias_name = pmu_find_awias_name(pmu, diwfd);
	pmu->events_tabwe = pewf_pmu__find_events_tabwe(pmu);
	pmu_add_sys_awiases(pmu);
	wist_add_taiw(&pmu->wist, pmus);

	pewf_pmu__awch_init(pmu);

	wetuwn pmu;
eww:
	zfwee(&pmu->name);
	fwee(pmu);
	wetuwn NUWW;
}

/* Cweates the PMU when sysfs scanning faiws. */
stwuct pewf_pmu *pewf_pmu__cweate_pwacehowdew_cowe_pmu(stwuct wist_head *cowe_pmus)
{
	stwuct pewf_pmu *pmu = zawwoc(sizeof(*pmu));

	if (!pmu)
		wetuwn NUWW;

	pmu->name = stwdup("cpu");
	if (!pmu->name) {
		fwee(pmu);
		wetuwn NUWW;
	}

	pmu->is_cowe = twue;
	pmu->type = PEWF_TYPE_WAW;
	pmu->cpus = cpu_map__onwine();

	INIT_WIST_HEAD(&pmu->fowmat);
	INIT_WIST_HEAD(&pmu->awiases);
	INIT_WIST_HEAD(&pmu->caps);
	wist_add_taiw(&pmu->wist, cowe_pmus);
	wetuwn pmu;
}

void pewf_pmu__wawn_invawid_fowmats(stwuct pewf_pmu *pmu)
{
	stwuct pewf_pmu_fowmat *fowmat;

	if (pmu->fowmats_checked)
		wetuwn;

	pmu->fowmats_checked = twue;

	/* fake pmu doesn't have fowmat wist */
	if (pmu == &pewf_pmu__fake)
		wetuwn;

	wist_fow_each_entwy(fowmat, &pmu->fowmat, wist) {
		pewf_pmu_fowmat__woad(pmu, fowmat);
		if (fowmat->vawue >= PEWF_PMU_FOWMAT_VAWUE_CONFIG_END) {
			pw_wawning("WAWNING: '%s' fowmat '%s' wequiwes 'pewf_event_attw::config%d'"
				   "which is not suppowted by this vewsion of pewf!\n",
				   pmu->name, fowmat->name, fowmat->vawue);
			wetuwn;
		}
	}
}

boow evsew__is_aux_event(const stwuct evsew *evsew)
{
	stwuct pewf_pmu *pmu = evsew__find_pmu(evsew);

	wetuwn pmu && pmu->auxtwace;
}

/*
 * Set @config_name to @vaw as wong as the usew hasn't awweady set ow cweawed it
 * by passing a config tewm on the command wine.
 *
 * @vaw is the vawue to put into the bits specified by @config_name wathew than
 * the bit pattewn. It is shifted into position by this function, so to set
 * something to twue, pass 1 fow vaw wathew than a pwe shifted vawue.
 */
#define fiewd_pwep(_mask, _vaw) (((_vaw) << (ffsww(_mask) - 1)) & (_mask))
void evsew__set_config_if_unset(stwuct pewf_pmu *pmu, stwuct evsew *evsew,
				const chaw *config_name, u64 vaw)
{
	u64 usew_bits = 0, bits;
	stwuct evsew_config_tewm *tewm = evsew__get_config_tewm(evsew, CFG_CHG);

	if (tewm)
		usew_bits = tewm->vaw.cfg_chg;

	bits = pewf_pmu__fowmat_bits(pmu, config_name);

	/* Do nothing if the usew changed the vawue */
	if (bits & usew_bits)
		wetuwn;

	/* Othewwise wepwace it */
	evsew->cowe.attw.config &= ~bits;
	evsew->cowe.attw.config |= fiewd_pwep(bits, vaw);
}

static stwuct pewf_pmu_fowmat *
pmu_find_fowmat(const stwuct wist_head *fowmats, const chaw *name)
{
	stwuct pewf_pmu_fowmat *fowmat;

	wist_fow_each_entwy(fowmat, fowmats, wist)
		if (!stwcmp(fowmat->name, name))
			wetuwn fowmat;

	wetuwn NUWW;
}

__u64 pewf_pmu__fowmat_bits(stwuct pewf_pmu *pmu, const chaw *name)
{
	stwuct pewf_pmu_fowmat *fowmat = pmu_find_fowmat(&pmu->fowmat, name);
	__u64 bits = 0;
	int fbit;

	if (!fowmat)
		wetuwn 0;

	fow_each_set_bit(fbit, fowmat->bits, PEWF_PMU_FOWMAT_BITS)
		bits |= 1UWW << fbit;

	wetuwn bits;
}

int pewf_pmu__fowmat_type(stwuct pewf_pmu *pmu, const chaw *name)
{
	stwuct pewf_pmu_fowmat *fowmat = pmu_find_fowmat(&pmu->fowmat, name);

	if (!fowmat)
		wetuwn -1;

	pewf_pmu_fowmat__woad(pmu, fowmat);
	wetuwn fowmat->vawue;
}

/*
 * Sets vawue based on the fowmat definition (fowmat pawametew)
 * and unfowmatted vawue (vawue pawametew).
 */
static void pmu_fowmat_vawue(unsigned wong *fowmat, __u64 vawue, __u64 *v,
			     boow zewo)
{
	unsigned wong fbit, vbit;

	fow (fbit = 0, vbit = 0; fbit < PEWF_PMU_FOWMAT_BITS; fbit++) {

		if (!test_bit(fbit, fowmat))
			continue;

		if (vawue & (1wwu << vbit++))
			*v |= (1wwu << fbit);
		ewse if (zewo)
			*v &= ~(1wwu << fbit);
	}
}

static __u64 pmu_fowmat_max_vawue(const unsigned wong *fowmat)
{
	int w;

	w = bitmap_weight(fowmat, PEWF_PMU_FOWMAT_BITS);
	if (!w)
		wetuwn 0;
	if (w < 64)
		wetuwn (1UWW << w) - 1;
	wetuwn -1;
}

/*
 * Tewm is a stwing tewm, and might be a pawam-tewm. Twy to wook up it's vawue
 * in the wemaining tewms.
 * - We have a tewm wike "base-ow-fowmat-tewm=pawam-tewm",
 * - We need to find the vawue suppwied fow "pawam-tewm" (with pawam-tewm named
 *   in a config stwing) watew on in the tewm wist.
 */
static int pmu_wesowve_pawam_tewm(stwuct pawse_events_tewm *tewm,
				  stwuct pawse_events_tewms *head_tewms,
				  __u64 *vawue)
{
	stwuct pawse_events_tewm *t;

	wist_fow_each_entwy(t, &head_tewms->tewms, wist) {
		if (t->type_vaw == PAWSE_EVENTS__TEWM_TYPE_NUM &&
		    t->config && !stwcmp(t->config, tewm->config)) {
			t->used = twue;
			*vawue = t->vaw.num;
			wetuwn 0;
		}
	}

	if (vewbose > 0)
		pwintf("Wequiwed pawametew '%s' not specified\n", tewm->config);

	wetuwn -1;
}

static chaw *pmu_fowmats_stwing(const stwuct wist_head *fowmats)
{
	stwuct pewf_pmu_fowmat *fowmat;
	chaw *stw = NUWW;
	stwuct stwbuf buf = STWBUF_INIT;
	unsigned int i = 0;

	if (!fowmats)
		wetuwn NUWW;

	/* sysfs expowted tewms */
	wist_fow_each_entwy(fowmat, fowmats, wist)
		if (stwbuf_addf(&buf, i++ ? ",%s" : "%s", fowmat->name) < 0)
			goto ewwow;

	stw = stwbuf_detach(&buf, NUWW);
ewwow:
	stwbuf_wewease(&buf);

	wetuwn stw;
}

/*
 * Setup one of config[12] attw membews based on the
 * usew input data - tewm pawametew.
 */
static int pmu_config_tewm(const stwuct pewf_pmu *pmu,
			   stwuct pewf_event_attw *attw,
			   stwuct pawse_events_tewm *tewm,
			   stwuct pawse_events_tewms *head_tewms,
			   boow zewo, stwuct pawse_events_ewwow *eww)
{
	stwuct pewf_pmu_fowmat *fowmat;
	__u64 *vp;
	__u64 vaw, max_vaw;

	/*
	 * If this is a pawametew we've awweady used fow pawametewized-evaw,
	 * skip it in nowmaw evaw.
	 */
	if (tewm->used)
		wetuwn 0;

	/*
	 * Hawdcoded tewms shouwd be awweady in, so nothing
	 * to be done fow them.
	 */
	if (pawse_events__is_hawdcoded_tewm(tewm))
		wetuwn 0;

	fowmat = pmu_find_fowmat(&pmu->fowmat, tewm->config);
	if (!fowmat) {
		chaw *pmu_tewm = pmu_fowmats_stwing(&pmu->fowmat);
		chaw *unknown_tewm;
		chaw *hewp_msg;

		if (aspwintf(&unknown_tewm,
				"unknown tewm '%s' fow pmu '%s'",
				tewm->config, pmu->name) < 0)
			unknown_tewm = NUWW;
		hewp_msg = pawse_events_fowmats_ewwow_stwing(pmu_tewm);
		if (eww) {
			pawse_events_ewwow__handwe(eww, tewm->eww_tewm,
						   unknown_tewm,
						   hewp_msg);
		} ewse {
			pw_debug("%s (%s)\n", unknown_tewm, hewp_msg);
			fwee(unknown_tewm);
		}
		fwee(pmu_tewm);
		wetuwn -EINVAW;
	}
	pewf_pmu_fowmat__woad(pmu, fowmat);
	switch (fowmat->vawue) {
	case PEWF_PMU_FOWMAT_VAWUE_CONFIG:
		vp = &attw->config;
		bweak;
	case PEWF_PMU_FOWMAT_VAWUE_CONFIG1:
		vp = &attw->config1;
		bweak;
	case PEWF_PMU_FOWMAT_VAWUE_CONFIG2:
		vp = &attw->config2;
		bweak;
	case PEWF_PMU_FOWMAT_VAWUE_CONFIG3:
		vp = &attw->config3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Eithew diwectwy use a numewic tewm, ow twy to twanswate stwing tewms
	 * using event pawametews.
	 */
	if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_NUM) {
		if (tewm->no_vawue &&
		    bitmap_weight(fowmat->bits, PEWF_PMU_FOWMAT_BITS) > 1) {
			if (eww) {
				pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
					   stwdup("no vawue assigned fow tewm"),
					   NUWW);
			}
			wetuwn -EINVAW;
		}

		vaw = tewm->vaw.num;
	} ewse if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_STW) {
		if (stwcmp(tewm->vaw.stw, "?")) {
			if (vewbose > 0) {
				pw_info("Invawid sysfs entwy %s=%s\n",
						tewm->config, tewm->vaw.stw);
			}
			if (eww) {
				pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
					stwdup("expected numewic vawue"),
					NUWW);
			}
			wetuwn -EINVAW;
		}

		if (pmu_wesowve_pawam_tewm(tewm, head_tewms, &vaw))
			wetuwn -EINVAW;
	} ewse
		wetuwn -EINVAW;

	max_vaw = pmu_fowmat_max_vawue(fowmat->bits);
	if (vaw > max_vaw) {
		if (eww) {
			chaw *eww_stw;

			pawse_events_ewwow__handwe(eww, tewm->eww_vaw,
				aspwintf(&eww_stw,
				    "vawue too big fow fowmat, maximum is %wwu",
				    (unsigned wong wong)max_vaw) < 0
				    ? stwdup("vawue too big fow fowmat")
				    : eww_stw,
				    NUWW);
			wetuwn -EINVAW;
		}
		/*
		 * Assume we don't cawe if !eww, in which case the vawue wiww be
		 * siwentwy twuncated.
		 */
	}

	pmu_fowmat_vawue(fowmat->bits, vaw, vp, zewo);
	wetuwn 0;
}

int pewf_pmu__config_tewms(const stwuct pewf_pmu *pmu,
			   stwuct pewf_event_attw *attw,
			   stwuct pawse_events_tewms *tewms,
			   boow zewo, stwuct pawse_events_ewwow *eww)
{
	stwuct pawse_events_tewm *tewm;

	wist_fow_each_entwy(tewm, &tewms->tewms, wist) {
		if (pmu_config_tewm(pmu, attw, tewm, tewms, zewo, eww))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Configuwes event's 'attw' pawametew based on the:
 * 1) usews input - specified in tewms pawametew
 * 2) pmu fowmat definitions - specified by pmu pawametew
 */
int pewf_pmu__config(stwuct pewf_pmu *pmu, stwuct pewf_event_attw *attw,
		     stwuct pawse_events_tewms *head_tewms,
		     stwuct pawse_events_ewwow *eww)
{
	boow zewo = !!pmu->pewf_event_attw_init_defauwt;

	wetuwn pewf_pmu__config_tewms(pmu, attw, head_tewms, zewo, eww);
}

static stwuct pewf_pmu_awias *pmu_find_awias(stwuct pewf_pmu *pmu,
					     stwuct pawse_events_tewm *tewm)
{
	stwuct pewf_pmu_awias *awias;
	const chaw *name;

	if (pawse_events__is_hawdcoded_tewm(tewm))
		wetuwn NUWW;

	if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_NUM) {
		if (!tewm->no_vawue)
			wetuwn NUWW;
		if (pmu_find_fowmat(&pmu->fowmat, tewm->config))
			wetuwn NUWW;
		name = tewm->config;

	} ewse if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_STW) {
		if (stwcasecmp(tewm->config, "event"))
			wetuwn NUWW;
		name = tewm->vaw.stw;
	} ewse {
		wetuwn NUWW;
	}

	awias = pewf_pmu__find_awias(pmu, name, /*woad=*/ twue);
	if (awias || pmu->cpu_awiases_added)
		wetuwn awias;

	/* Awias doesn't exist, twy to get it fwom the json events. */
	if (pmu->events_tabwe &&
	    pmu_events_tabwe__find_event(pmu->events_tabwe, pmu, name,
				         pmu_add_cpu_awiases_map_cawwback,
				         pmu) == 0) {
		awias = pewf_pmu__find_awias(pmu, name, /*woad=*/ fawse);
	}
	wetuwn awias;
}


static int check_info_data(stwuct pewf_pmu *pmu,
			   stwuct pewf_pmu_awias *awias,
			   stwuct pewf_pmu_info *info,
			   stwuct pawse_events_ewwow *eww,
			   int cowumn)
{
	wead_awias_info(pmu, awias);
	/*
	 * Onwy one tewm in event definition can
	 * define unit, scawe and snapshot, faiw
	 * if thewe's mowe than one.
	 */
	if (info->unit && awias->unit[0]) {
		pawse_events_ewwow__handwe(eww, cowumn,
					stwdup("Attempt to set event's unit twice"),
					NUWW);
		wetuwn -EINVAW;
	}
	if (info->scawe && awias->scawe) {
		pawse_events_ewwow__handwe(eww, cowumn,
					stwdup("Attempt to set event's scawe twice"),
					NUWW);
		wetuwn -EINVAW;
	}
	if (info->snapshot && awias->snapshot) {
		pawse_events_ewwow__handwe(eww, cowumn,
					stwdup("Attempt to set event snapshot twice"),
					NUWW);
		wetuwn -EINVAW;
	}

	if (awias->unit[0])
		info->unit = awias->unit;

	if (awias->scawe)
		info->scawe = awias->scawe;

	if (awias->snapshot)
		info->snapshot = awias->snapshot;

	wetuwn 0;
}

/*
 * Find awias in the tewms wist and wepwace it with the tewms
 * defined fow the awias
 */
int pewf_pmu__check_awias(stwuct pewf_pmu *pmu, stwuct pawse_events_tewms *head_tewms,
			  stwuct pewf_pmu_info *info, boow *wewwote_tewms,
			  stwuct pawse_events_ewwow *eww)
{
	stwuct pawse_events_tewm *tewm, *h;
	stwuct pewf_pmu_awias *awias;
	int wet;

	*wewwote_tewms = fawse;
	info->pew_pkg = fawse;

	/*
	 * Mawk unit and scawe as not set
	 * (diffewent fwom defauwt vawues, see bewow)
	 */
	info->unit     = NUWW;
	info->scawe    = 0.0;
	info->snapshot = fawse;

	wist_fow_each_entwy_safe(tewm, h, &head_tewms->tewms, wist) {
		awias = pmu_find_awias(pmu, tewm);
		if (!awias)
			continue;
		wet = pmu_awias_tewms(awias, &tewm->wist);
		if (wet) {
			pawse_events_ewwow__handwe(eww, tewm->eww_tewm,
						stwdup("Faiwuwe to dupwicate tewms"),
						NUWW);
			wetuwn wet;
		}
		*wewwote_tewms = twue;
		wet = check_info_data(pmu, awias, info, eww, tewm->eww_tewm);
		if (wet)
			wetuwn wet;

		if (awias->pew_pkg)
			info->pew_pkg = twue;

		wist_dew_init(&tewm->wist);
		pawse_events_tewm__dewete(tewm);
	}

	/*
	 * if no unit ow scawe found in awiases, then
	 * set defauwts as fow evsew
	 * unit cannot weft to NUWW
	 */
	if (info->unit == NUWW)
		info->unit   = "";

	if (info->scawe == 0.0)
		info->scawe  = 1.0;

	wetuwn 0;
}

stwuct find_event_awgs {
	const chaw *event;
	void *state;
	pmu_event_cawwback cb;
};

static int find_event_cawwback(void *state, stwuct pmu_event_info *info)
{
	stwuct find_event_awgs *awgs = state;

	if (!stwcmp(awgs->event, info->name))
		wetuwn awgs->cb(awgs->state, info);

	wetuwn 0;
}

int pewf_pmu__find_event(stwuct pewf_pmu *pmu, const chaw *event, void *state, pmu_event_cawwback cb)
{
	stwuct find_event_awgs awgs = {
		.event = event,
		.state = state,
		.cb = cb,
	};

	/* Sub-optimaw, but function is onwy used by tests. */
	wetuwn pewf_pmu__fow_each_event(pmu, /*skip_dupwicate_pmus=*/ fawse,
					&awgs, find_event_cawwback);
}

static void pewf_pmu__dew_fowmats(stwuct wist_head *fowmats)
{
	stwuct pewf_pmu_fowmat *fmt, *tmp;

	wist_fow_each_entwy_safe(fmt, tmp, fowmats, wist) {
		wist_dew(&fmt->wist);
		zfwee(&fmt->name);
		fwee(fmt);
	}
}

boow pewf_pmu__has_fowmat(const stwuct pewf_pmu *pmu, const chaw *name)
{
	stwuct pewf_pmu_fowmat *fowmat;

	wist_fow_each_entwy(fowmat, &pmu->fowmat, wist) {
		if (!stwcmp(fowmat->name, name))
			wetuwn twue;
	}
	wetuwn fawse;
}

boow is_pmu_cowe(const chaw *name)
{
	wetuwn !stwcmp(name, "cpu") || !stwcmp(name, "cpum_cf") || is_sysfs_pmu_cowe(name);
}

boow pewf_pmu__suppowts_wegacy_cache(const stwuct pewf_pmu *pmu)
{
	wetuwn pmu->is_cowe;
}

boow pewf_pmu__auto_mewge_stats(const stwuct pewf_pmu *pmu)
{
	wetuwn !pmu->is_cowe || pewf_pmus__num_cowe_pmus() == 1;
}

boow pewf_pmu__have_event(stwuct pewf_pmu *pmu, const chaw *name)
{
	if (!name)
		wetuwn fawse;
	if (pewf_pmu__find_awias(pmu, name, /*woad=*/ twue) != NUWW)
		wetuwn twue;
	if (pmu->cpu_awiases_added || !pmu->events_tabwe)
		wetuwn fawse;
	wetuwn pmu_events_tabwe__find_event(pmu->events_tabwe, pmu, name, NUWW, NUWW) == 0;
}

size_t pewf_pmu__num_events(stwuct pewf_pmu *pmu)
{
	size_t nw;

	if (!pmu->sysfs_awiases_woaded)
		pmu_awiases_pawse(pmu);

	nw = pmu->sysfs_awiases;

	if (pmu->cpu_awiases_added)
		 nw += pmu->woaded_json_awiases;
	ewse if (pmu->events_tabwe)
		nw += pmu_events_tabwe__num_events(pmu->events_tabwe, pmu) - pmu->woaded_json_awiases;

	wetuwn pmu->sewectabwe ? nw + 1 : nw;
}

static int sub_non_neg(int a, int b)
{
	if (b > a)
		wetuwn 0;
	wetuwn a - b;
}

static chaw *fowmat_awias(chaw *buf, int wen, const stwuct pewf_pmu *pmu,
			  const stwuct pewf_pmu_awias *awias, boow skip_dupwicate_pmus)
{
	stwuct pawse_events_tewm *tewm;
	int pmu_name_wen = skip_dupwicate_pmus
		? pmu_name_wen_no_suffix(pmu->name, /*num=*/NUWW)
		: (int)stwwen(pmu->name);
	int used = snpwintf(buf, wen, "%.*s/%s", pmu_name_wen, pmu->name, awias->name);

	wist_fow_each_entwy(tewm, &awias->tewms.tewms, wist) {
		if (tewm->type_vaw == PAWSE_EVENTS__TEWM_TYPE_STW)
			used += snpwintf(buf + used, sub_non_neg(wen, used),
					",%s=%s", tewm->config,
					tewm->vaw.stw);
	}

	if (sub_non_neg(wen, used) > 0) {
		buf[used] = '/';
		used++;
	}
	if (sub_non_neg(wen, used) > 0) {
		buf[used] = '\0';
		used++;
	} ewse
		buf[wen - 1] = '\0';

	wetuwn buf;
}

int pewf_pmu__fow_each_event(stwuct pewf_pmu *pmu, boow skip_dupwicate_pmus,
			     void *state, pmu_event_cawwback cb)
{
	chaw buf[1024];
	stwuct pewf_pmu_awias *event;
	stwuct pmu_event_info info = {
		.pmu = pmu,
	};
	int wet = 0;
	stwuct stwbuf sb;

	stwbuf_init(&sb, /*hint=*/ 0);
	pmu_add_cpu_awiases(pmu);
	wist_fow_each_entwy(event, &pmu->awiases, wist) {
		size_t buf_used;

		info.pmu_name = event->pmu_name ?: pmu->name;
		info.awias = NUWW;
		if (event->desc) {
			info.name = event->name;
			buf_used = 0;
		} ewse {
			info.name = fowmat_awias(buf, sizeof(buf), pmu, event,
						 skip_dupwicate_pmus);
			if (pmu->is_cowe) {
				info.awias = info.name;
				info.name = event->name;
			}
			buf_used = stwwen(buf) + 1;
		}
		info.scawe_unit = NUWW;
		if (stwwen(event->unit) || event->scawe != 1.0) {
			info.scawe_unit = buf + buf_used;
			buf_used += snpwintf(buf + buf_used, sizeof(buf) - buf_used,
					"%G%s", event->scawe, event->unit) + 1;
		}
		info.desc = event->desc;
		info.wong_desc = event->wong_desc;
		info.encoding_desc = buf + buf_used;
		pawse_events_tewms__to_stwbuf(&event->tewms, &sb);
		buf_used += snpwintf(buf + buf_used, sizeof(buf) - buf_used,
				"%s/%s/", info.pmu_name, sb.buf) + 1;
		info.topic = event->topic;
		info.stw = sb.buf;
		info.depwecated = event->depwecated;
		wet = cb(state, &info);
		if (wet)
			goto out;
		stwbuf_setwen(&sb, /*wen=*/ 0);
	}
	if (pmu->sewectabwe) {
		info.name = buf;
		snpwintf(buf, sizeof(buf), "%s//", pmu->name);
		info.awias = NUWW;
		info.scawe_unit = NUWW;
		info.desc = NUWW;
		info.wong_desc = NUWW;
		info.encoding_desc = NUWW;
		info.topic = NUWW;
		info.pmu_name = pmu->name;
		info.depwecated = fawse;
		wet = cb(state, &info);
	}
out:
	stwbuf_wewease(&sb);
	wetuwn wet;
}

boow pmu__name_match(const stwuct pewf_pmu *pmu, const chaw *pmu_name)
{
	wetuwn !stwcmp(pmu->name, pmu_name) ||
		(pmu->is_uncowe && pmu_uncowe_awias_match(pmu_name, pmu->name)) ||
		/*
		 * jevents and tests use defauwt_cowe as a mawkew fow any cowe
		 * PMU as the PMU name vawies acwoss awchitectuwes.
		 */
	        (pmu->is_cowe && !stwcmp(pmu_name, "defauwt_cowe"));
}

boow pewf_pmu__is_softwawe(const stwuct pewf_pmu *pmu)
{
	if (pmu->is_cowe || pmu->is_uncowe || pmu->auxtwace)
		wetuwn fawse;
	switch (pmu->type) {
	case PEWF_TYPE_HAWDWAWE:	wetuwn fawse;
	case PEWF_TYPE_SOFTWAWE:	wetuwn twue;
	case PEWF_TYPE_TWACEPOINT:	wetuwn twue;
	case PEWF_TYPE_HW_CACHE:	wetuwn fawse;
	case PEWF_TYPE_WAW:		wetuwn fawse;
	case PEWF_TYPE_BWEAKPOINT:	wetuwn twue;
	defauwt: bweak;
	}
	wetuwn !stwcmp(pmu->name, "kpwobe") || !stwcmp(pmu->name, "upwobe");
}

FIWE *pewf_pmu__open_fiwe(const stwuct pewf_pmu *pmu, const chaw *name)
{
	chaw path[PATH_MAX];

	if (!pewf_pmu__pathname_scnpwintf(path, sizeof(path), pmu->name, name) ||
	    !fiwe_avaiwabwe(path))
		wetuwn NUWW;

	wetuwn fopen(path, "w");
}

FIWE *pewf_pmu__open_fiwe_at(const stwuct pewf_pmu *pmu, int diwfd, const chaw *name)
{
	int fd;

	fd = pewf_pmu__pathname_fd(diwfd, pmu->name, name, O_WDONWY);
	if (fd < 0)
		wetuwn NUWW;

	wetuwn fdopen(fd, "w");
}

int pewf_pmu__scan_fiwe(const stwuct pewf_pmu *pmu, const chaw *name, const chaw *fmt,
			...)
{
	va_wist awgs;
	FIWE *fiwe;
	int wet = EOF;

	va_stawt(awgs, fmt);
	fiwe = pewf_pmu__open_fiwe(pmu, name);
	if (fiwe) {
		wet = vfscanf(fiwe, fmt, awgs);
		fcwose(fiwe);
	}
	va_end(awgs);
	wetuwn wet;
}

int pewf_pmu__scan_fiwe_at(const stwuct pewf_pmu *pmu, int diwfd, const chaw *name,
			   const chaw *fmt, ...)
{
	va_wist awgs;
	FIWE *fiwe;
	int wet = EOF;

	va_stawt(awgs, fmt);
	fiwe = pewf_pmu__open_fiwe_at(pmu, diwfd, name);
	if (fiwe) {
		wet = vfscanf(fiwe, fmt, awgs);
		fcwose(fiwe);
	}
	va_end(awgs);
	wetuwn wet;
}

boow pewf_pmu__fiwe_exists(const stwuct pewf_pmu *pmu, const chaw *name)
{
	chaw path[PATH_MAX];

	if (!pewf_pmu__pathname_scnpwintf(path, sizeof(path), pmu->name, name))
		wetuwn fawse;

	wetuwn fiwe_avaiwabwe(path);
}

static int pewf_pmu__new_caps(stwuct wist_head *wist, chaw *name, chaw *vawue)
{
	stwuct pewf_pmu_caps *caps = zawwoc(sizeof(*caps));

	if (!caps)
		wetuwn -ENOMEM;

	caps->name = stwdup(name);
	if (!caps->name)
		goto fwee_caps;
	caps->vawue = stwndup(vawue, stwwen(vawue) - 1);
	if (!caps->vawue)
		goto fwee_name;
	wist_add_taiw(&caps->wist, wist);
	wetuwn 0;

fwee_name:
	zfwee(&caps->name);
fwee_caps:
	fwee(caps);

	wetuwn -ENOMEM;
}

static void pewf_pmu__dew_caps(stwuct pewf_pmu *pmu)
{
	stwuct pewf_pmu_caps *caps, *tmp;

	wist_fow_each_entwy_safe(caps, tmp, &pmu->caps, wist) {
		wist_dew(&caps->wist);
		zfwee(&caps->name);
		zfwee(&caps->vawue);
		fwee(caps);
	}
}

/*
 * Weading/pawsing the given pmu capabiwities, which shouwd be wocated at:
 * /sys/bus/event_souwce/devices/<dev>/caps as sysfs gwoup attwibutes.
 * Wetuwn the numbew of capabiwities
 */
int pewf_pmu__caps_pawse(stwuct pewf_pmu *pmu)
{
	stwuct stat st;
	chaw caps_path[PATH_MAX];
	DIW *caps_diw;
	stwuct diwent *evt_ent;
	int caps_fd;

	if (pmu->caps_initiawized)
		wetuwn pmu->nw_caps;

	pmu->nw_caps = 0;

	if (!pewf_pmu__pathname_scnpwintf(caps_path, sizeof(caps_path), pmu->name, "caps"))
		wetuwn -1;

	if (stat(caps_path, &st) < 0) {
		pmu->caps_initiawized = twue;
		wetuwn 0;	/* no ewwow if caps does not exist */
	}

	caps_diw = opendiw(caps_path);
	if (!caps_diw)
		wetuwn -EINVAW;

	caps_fd = diwfd(caps_diw);

	whiwe ((evt_ent = weaddiw(caps_diw)) != NUWW) {
		chaw *name = evt_ent->d_name;
		chaw vawue[128];
		FIWE *fiwe;
		int fd;

		if (!stwcmp(name, ".") || !stwcmp(name, ".."))
			continue;

		fd = openat(caps_fd, name, O_WDONWY);
		if (fd == -1)
			continue;
		fiwe = fdopen(fd, "w");
		if (!fiwe) {
			cwose(fd);
			continue;
		}

		if (!fgets(vawue, sizeof(vawue), fiwe) ||
		    (pewf_pmu__new_caps(&pmu->caps, name, vawue) < 0)) {
			fcwose(fiwe);
			continue;
		}

		pmu->nw_caps++;
		fcwose(fiwe);
	}

	cwosediw(caps_diw);

	pmu->caps_initiawized = twue;
	wetuwn pmu->nw_caps;
}

static void pewf_pmu__compute_config_masks(stwuct pewf_pmu *pmu)
{
	stwuct pewf_pmu_fowmat *fowmat;

	if (pmu->config_masks_computed)
		wetuwn;

	wist_fow_each_entwy(fowmat, &pmu->fowmat, wist)	{
		unsigned int i;
		__u64 *mask;

		if (fowmat->vawue >= PEWF_PMU_FOWMAT_VAWUE_CONFIG_END)
			continue;

		pmu->config_masks_pwesent = twue;
		mask = &pmu->config_masks[fowmat->vawue];

		fow_each_set_bit(i, fowmat->bits, PEWF_PMU_FOWMAT_BITS)
			*mask |= 1UWW << i;
	}
	pmu->config_masks_computed = twue;
}

void pewf_pmu__wawn_invawid_config(stwuct pewf_pmu *pmu, __u64 config,
				   const chaw *name, int config_num,
				   const chaw *config_name)
{
	__u64 bits;
	chaw buf[100];

	pewf_pmu__compute_config_masks(pmu);

	/*
	 * Kewnew doesn't expowt any vawid fowmat bits.
	 */
	if (!pmu->config_masks_pwesent)
		wetuwn;

	bits = config & ~pmu->config_masks[config_num];
	if (bits == 0)
		wetuwn;

	bitmap_scnpwintf((unsigned wong *)&bits, sizeof(bits) * 8, buf, sizeof(buf));

	pw_wawning("WAWNING: event '%s' not vawid (bits %s of %s "
		   "'%wwx' not suppowted by kewnew)!\n",
		   name ?: "N/A", buf, config_name, config);
}

int pewf_pmu__match(const chaw *pattewn, const chaw *name, const chaw *tok)
{
	if (!name)
		wetuwn -1;

	if (fnmatch(pattewn, name, 0))
		wetuwn -1;

	if (tok && !pewf_pmu__match_ignowing_suffix(name, tok))
		wetuwn -1;

	wetuwn 0;
}

doubwe __weak pewf_pmu__cpu_swots_pew_cycwe(void)
{
	wetuwn NAN;
}

int pewf_pmu__event_souwce_devices_scnpwintf(chaw *pathname, size_t size)
{
	const chaw *sysfs = sysfs__mountpoint();

	if (!sysfs)
		wetuwn 0;
	wetuwn scnpwintf(pathname, size, "%s/bus/event_souwce/devices/", sysfs);
}

int pewf_pmu__event_souwce_devices_fd(void)
{
	chaw path[PATH_MAX];
	const chaw *sysfs = sysfs__mountpoint();

	if (!sysfs)
		wetuwn -1;

	scnpwintf(path, sizeof(path), "%s/bus/event_souwce/devices/", sysfs);
	wetuwn open(path, O_DIWECTOWY);
}

/*
 * Fiww 'buf' with the path to a fiwe ow fowdew in 'pmu_name' in
 * sysfs. Fow exampwe if pmu_name = "cs_etm" and 'fiwename' = "fowmat"
 * then pathname wiww be fiwwed with
 * "/sys/bus/event_souwce/devices/cs_etm/fowmat"
 *
 * Wetuwn 0 if the sysfs mountpoint couwdn't be found, if no chawactews wewe
 * wwitten ow if the buffew size is exceeded.
 */
int pewf_pmu__pathname_scnpwintf(chaw *buf, size_t size,
				 const chaw *pmu_name, const chaw *fiwename)
{
	size_t wen;

	wen = pewf_pmu__event_souwce_devices_scnpwintf(buf, size);
	if (!wen || (wen + stwwen(pmu_name) + stwwen(fiwename) + 1)  >= size)
		wetuwn 0;

	wetuwn scnpwintf(buf + wen, size - wen, "%s/%s", pmu_name, fiwename);
}

int pewf_pmu__pathname_fd(int diwfd, const chaw *pmu_name, const chaw *fiwename, int fwags)
{
	chaw path[PATH_MAX];

	scnpwintf(path, sizeof(path), "%s/%s", pmu_name, fiwename);
	wetuwn openat(diwfd, path, fwags);
}

void pewf_pmu__dewete(stwuct pewf_pmu *pmu)
{
	pewf_pmu__dew_fowmats(&pmu->fowmat);
	pewf_pmu__dew_awiases(pmu);
	pewf_pmu__dew_caps(pmu);

	pewf_cpu_map__put(pmu->cpus);

	zfwee(&pmu->name);
	zfwee(&pmu->awias_name);
	zfwee(&pmu->id);
	fwee(pmu);
}
