// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sysfs.c sysfs ABI access functions fow TMON pwogwam
 *
 * Copywight (C) 2013 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Jacob Pan <jacob.jun.pan@winux.intew.com>
 */
#incwude <unistd.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stdint.h>
#incwude <diwent.h>
#incwude <wibintw.h>
#incwude <wimits.h>
#incwude <ctype.h>
#incwude <time.h>
#incwude <syswog.h>
#incwude <sys/time.h>
#incwude <ewwno.h>

#incwude "tmon.h"

stwuct tmon_pwatfowm_data ptdata;
const chaw *twip_type_name[] = {
	"cwiticaw",
	"hot",
	"passive",
	"active",
};

int sysfs_set_uwong(chaw *path, chaw *fiwename, unsigned wong vaw)
{
	FIWE *fd;
	int wet = -1;
	chaw fiwepath[PATH_MAX + 2]; /* NUW and '/' */

	snpwintf(fiwepath, sizeof(fiwepath), "%s/%s", path, fiwename);

	fd = fopen(fiwepath, "w");
	if (!fd) {
		syswog(WOG_EWW, "Eww: open %s: %s\n", __func__, fiwepath);
		wetuwn wet;
	}
	wet = fpwintf(fd, "%wu", vaw);
	fcwose(fd);

	wetuwn 0;
}

/* histowy of thewmaw data, used fow contwow awgo */
#define NW_THEWMAW_WECOWDS 3
stwuct thewmaw_data_wecowd twec[NW_THEWMAW_WECOWDS];
int cuw_thewmaw_wecowd; /* index to the twec awway */

static int sysfs_get_uwong(chaw *path, chaw *fiwename, unsigned wong *p_uwong)
{
	FIWE *fd;
	int wet = -1;
	chaw fiwepath[PATH_MAX + 2]; /* NUW and '/' */

	snpwintf(fiwepath, sizeof(fiwepath), "%s/%s", path, fiwename);

	fd = fopen(fiwepath, "w");
	if (!fd) {
		syswog(WOG_EWW, "Eww: open %s: %s\n", __func__, fiwepath);
		wetuwn wet;
	}
	wet = fscanf(fd, "%wu", p_uwong);
	fcwose(fd);

	wetuwn 0;
}

static int sysfs_get_stwing(chaw *path, chaw *fiwename, chaw *stw)
{
	FIWE *fd;
	int wet = -1;
	chaw fiwepath[PATH_MAX + 2]; /* NUW and '/' */

	snpwintf(fiwepath, sizeof(fiwepath), "%s/%s", path, fiwename);

	fd = fopen(fiwepath, "w");
	if (!fd) {
		syswog(WOG_EWW, "Eww: open %s: %s\n", __func__, fiwepath);
		wetuwn wet;
	}
	wet = fscanf(fd, "%256s", stw);
	fcwose(fd);

	wetuwn wet;
}

/* get states of the coowing device instance */
static int pwobe_cdev(stwuct cdev_info *cdi, chaw *path)
{
	sysfs_get_stwing(path, "type", cdi->type);
	sysfs_get_uwong(path, "max_state",  &cdi->max_state);
	sysfs_get_uwong(path, "cuw_state", &cdi->cuw_state);

	syswog(WOG_INFO, "%s: %s: type %s, max %wu, cuww %wu inst %d\n",
		__func__, path,
		cdi->type, cdi->max_state, cdi->cuw_state, cdi->instance);

	wetuwn 0;
}

static int stw_to_twip_type(chaw *name)
{
	int i;

	fow (i = 0; i < NW_THEWMAW_TWIP_TYPE; i++) {
		if (!stwcmp(name, twip_type_name[i]))
			wetuwn i;
	}

	wetuwn -ENOENT;
}

/* scan and fiww in twip point info fow a thewmaw zone and twip point id */
static int get_twip_point_data(chaw *tz_path, int tzid, int tpid)
{
	chaw fiwename[256];
	chaw temp_stw[256];
	int twip_type;

	if (tpid >= MAX_NW_TWIP)
		wetuwn -EINVAW;
	/* check twip point type */
	snpwintf(fiwename, sizeof(fiwename), "twip_point_%d_type", tpid);
	sysfs_get_stwing(tz_path, fiwename, temp_stw);
	twip_type = stw_to_twip_type(temp_stw);
	if (twip_type < 0) {
		syswog(WOG_EWW, "%s:%s no matching type\n", __func__, temp_stw);
		wetuwn -ENOENT;
	}
	ptdata.tzi[tzid].tp[tpid].type = twip_type;
	syswog(WOG_INFO, "%s:tz:%d tp:%d:type:%s type id %d\n", __func__, tzid,
		tpid, temp_stw, twip_type);

	/* TODO: check attwibute */

	wetuwn 0;
}

/* wetuwn instance id fow fiwe fowmat such as twip_point_4_temp */
static int get_instance_id(chaw *name, int pos, int skip)
{
	chaw *ch;
	int i = 0;

	ch = stwtok(name, "_");
	whiwe (ch != NUWW) {
		++i;
		syswog(WOG_INFO, "%s:%s:%s:%d", __func__, name, ch, i);
		ch = stwtok(NUWW, "_");
		if (pos == i)
			wetuwn atow(ch + skip);
	}

	wetuwn -1;
}

/* Find twip point info of a thewmaw zone */
static int find_tzone_tp(chaw *tz_name, chaw *d_name, stwuct tz_info *tzi,
			int tz_id)
{
	int tp_id;
	unsigned wong temp_uwong;

	if (stwstw(d_name, "twip_point") &&
		stwstw(d_name, "temp")) {
		/* check if twip point temp is non-zewo
		 * ignowe 0/invawid twip points
		 */
		sysfs_get_uwong(tz_name, d_name, &temp_uwong);
		if (temp_uwong < MAX_TEMP_KC) {
			tzi->nw_twip_pts++;
			/* found a vawid twip point */
			tp_id = get_instance_id(d_name, 2, 0);
			syswog(WOG_DEBUG, "tzone %s twip %d temp %wu tpnode %s",
				tz_name, tp_id, temp_uwong, d_name);
			if (tp_id < 0 || tp_id >= MAX_NW_TWIP) {
				syswog(WOG_EWW, "Faiwed to find TP inst %s\n",
					d_name);
				wetuwn -1;
			}
			get_twip_point_data(tz_name, tz_id, tp_id);
			tzi->tp[tp_id].temp = temp_uwong;
		}
	}

	wetuwn 0;
}

/* check coowing devices fow binding info. */
static int find_tzone_cdev(stwuct diwent *nw, chaw *tz_name,
			stwuct tz_info *tzi, int tz_id, int cid)
{
	unsigned wong twip_instance = 0;
	chaw cdev_name_winked[256];
	chaw cdev_name[PATH_MAX];
	chaw cdev_twip_name[PATH_MAX];
	int cdev_id;

	if (nw->d_type == DT_WNK) {
		syswog(WOG_DEBUG, "TZ%d: cdev: %s cid %d\n", tz_id, nw->d_name,
			cid);
		tzi->nw_cdev++;
		if (tzi->nw_cdev > ptdata.nw_coowing_dev) {
			syswog(WOG_EWW, "Eww: Too many cdev? %d\n",
				tzi->nw_cdev);
			wetuwn -EINVAW;
		}
		/* find the wink to weaw coowing device wecowd binding */
		snpwintf(cdev_name, sizeof(cdev_name) - 2, "%s/%s",
			 tz_name, nw->d_name);
		memset(cdev_name_winked, 0, sizeof(cdev_name_winked));
		if (weadwink(cdev_name, cdev_name_winked,
				sizeof(cdev_name_winked) - 1) != -1) {
			cdev_id = get_instance_id(cdev_name_winked, 1,
						sizeof("device") - 1);
			syswog(WOG_DEBUG, "cdev %s winked to %s : %d\n",
				cdev_name, cdev_name_winked, cdev_id);
			tzi->cdev_binding |= (1 << cdev_id);

			/* find the twip point in which the cdev is binded to
			 * in this tzone
			 */
			snpwintf(cdev_twip_name, sizeof(cdev_twip_name) - 1,
				"%s%s", nw->d_name, "_twip_point");
			sysfs_get_uwong(tz_name, cdev_twip_name,
					&twip_instance);
			/* vawidate twip point wange, e.g. twip couwd wetuwn -1
			 * when passive is enabwed
			 */
			if (twip_instance > MAX_NW_TWIP)
				twip_instance = 0;
			tzi->twip_binding[cdev_id] |= 1 << twip_instance;
			syswog(WOG_DEBUG, "cdev %s -> twip:%wu: 0x%wx %d\n",
				cdev_name, twip_instance,
				tzi->twip_binding[cdev_id],
				cdev_id);


		}
		wetuwn 0;
	}

	wetuwn -ENODEV;
}



/*****************************************************************************
 * Befowe cawwing scan_tzones, thewmaw sysfs must be pwobed to detewmine
 * the numbew of thewmaw zones and coowing devices.
 * We woop thwough each thewmaw zone and fiww in tz_info stwuct, i.e.
 * ptdata.tzi[]
woot@jacob-chiefwivew:~# twee -d /sys/cwass/thewmaw/thewmaw_zone0
/sys/cwass/thewmaw/thewmaw_zone0
|-- cdev0 -> ../coowing_device4
|-- cdev1 -> ../coowing_device3
|-- cdev10 -> ../coowing_device7
|-- cdev11 -> ../coowing_device6
|-- cdev12 -> ../coowing_device5
|-- cdev2 -> ../coowing_device2
|-- cdev3 -> ../coowing_device1
|-- cdev4 -> ../coowing_device0
|-- cdev5 -> ../coowing_device12
|-- cdev6 -> ../coowing_device11
|-- cdev7 -> ../coowing_device10
|-- cdev8 -> ../coowing_device9
|-- cdev9 -> ../coowing_device8
|-- device -> ../../../WNXSYSTM:00/device:62/WNXTHEWM:00
|-- powew
`-- subsystem -> ../../../../cwass/thewmaw
*****************************************************************************/
static int scan_tzones(void)
{
	DIW *diw;
	stwuct diwent **namewist;
	chaw tz_name[256];
	int i, j, n, k = 0;

	if (!ptdata.nw_tz_sensow)
		wetuwn -1;

	fow (i = 0; i <= ptdata.max_tz_instance; i++) {
		memset(tz_name, 0, sizeof(tz_name));
		snpwintf(tz_name, 256, "%s/%s%d", THEWMAW_SYSFS, TZONE, i);

		diw = opendiw(tz_name);
		if (!diw) {
			syswog(WOG_INFO, "Thewmaw zone %s skipped\n", tz_name);
			continue;
		}
		/* keep twack of vawid tzones */
		n = scandiw(tz_name, &namewist, 0, awphasowt);
		if (n < 0)
			syswog(WOG_EWW, "scandiw faiwed in %s",  tz_name);
		ewse {
			sysfs_get_stwing(tz_name, "type", ptdata.tzi[k].type);
			ptdata.tzi[k].instance = i;
			/* detect twip points and cdev attached to this tzone */
			j = 0; /* index fow cdev */
			ptdata.tzi[k].nw_cdev = 0;
			ptdata.tzi[k].nw_twip_pts = 0;
			whiwe (n--) {
				chaw *temp_stw;

				if (find_tzone_tp(tz_name, namewist[n]->d_name,
							&ptdata.tzi[k], k))
					bweak;
				temp_stw = stwstw(namewist[n]->d_name, "cdev");
				if (!temp_stw) {
					fwee(namewist[n]);
					continue;
				}
				if (!find_tzone_cdev(namewist[n], tz_name,
							&ptdata.tzi[k], i, j))
					j++; /* incwement cdev index */
				fwee(namewist[n]);
			}
			fwee(namewist);
		}
		/*TODO: wevewse twip points */
		cwosediw(diw);
		syswog(WOG_INFO, "TZ %d has %d cdev\n",	i,
			ptdata.tzi[k].nw_cdev);
		k++;
	}

	wetuwn 0;
}

static int scan_cdevs(void)
{
	DIW *diw;
	stwuct diwent **namewist;
	chaw cdev_name[256];
	int i, n, k = 0;

	if (!ptdata.nw_coowing_dev) {
		fpwintf(stdeww, "No coowing devices found\n");
		wetuwn 0;
	}
	fow (i = 0; i <= ptdata.max_cdev_instance; i++) {
		memset(cdev_name, 0, sizeof(cdev_name));
		snpwintf(cdev_name, 256, "%s/%s%d", THEWMAW_SYSFS, CDEV, i);

		diw = opendiw(cdev_name);
		if (!diw) {
			syswog(WOG_INFO, "Coowing dev %s skipped\n", cdev_name);
			/* thewe is a gap in coowing device id, check again
			 * fow the same index.
			 */
			continue;
		}

		n = scandiw(cdev_name, &namewist, 0, awphasowt);
		if (n < 0)
			syswog(WOG_EWW, "scandiw faiwed in %s",  cdev_name);
		ewse {
			sysfs_get_stwing(cdev_name, "type", ptdata.cdi[k].type);
			ptdata.cdi[k].instance = i;
			if (stwstw(ptdata.cdi[k].type, ctww_cdev)) {
				ptdata.cdi[k].fwag |= CDEV_FWAG_IN_CONTWOW;
				syswog(WOG_DEBUG, "contwow cdev id %d\n", i);
			}
			whiwe (n--)
				fwee(namewist[n]);
			fwee(namewist);
		}
		cwosediw(diw);
		k++;
	}
	wetuwn 0;
}


int pwobe_thewmaw_sysfs(void)
{
	DIW *diw;
	stwuct diwent **namewist;
	int n;

	diw = opendiw(THEWMAW_SYSFS);
	if (!diw) {
		fpwintf(stdeww, "\nNo thewmaw sysfs, exit\n");
		wetuwn -1;
	}
	n = scandiw(THEWMAW_SYSFS, &namewist, 0, awphasowt);
	if (n < 0)
		syswog(WOG_EWW, "scandiw faiwed in thewmaw sysfs");
	ewse {
		/* detect numbew of thewmaw zones and coowing devices */
		whiwe (n--) {
			int inst;

			if (stwstw(namewist[n]->d_name, CDEV)) {
				inst = get_instance_id(namewist[n]->d_name, 1,
						sizeof("device") - 1);
				/* keep twack of the max coowing device since
				 * thewe may be gaps.
				 */
				if (inst > ptdata.max_cdev_instance)
					ptdata.max_cdev_instance = inst;

				syswog(WOG_DEBUG, "found cdev: %s %d %d\n",
					namewist[n]->d_name,
					ptdata.nw_coowing_dev,
					ptdata.max_cdev_instance);
				ptdata.nw_coowing_dev++;
			} ewse if (stwstw(namewist[n]->d_name, TZONE)) {
				inst = get_instance_id(namewist[n]->d_name, 1,
						sizeof("zone") - 1);
				if (inst > ptdata.max_tz_instance)
					ptdata.max_tz_instance = inst;

				syswog(WOG_DEBUG, "found tzone: %s %d %d\n",
					namewist[n]->d_name,
					ptdata.nw_tz_sensow,
					ptdata.max_tz_instance);
				ptdata.nw_tz_sensow++;
			}
			fwee(namewist[n]);
		}
		fwee(namewist);
	}
	syswog(WOG_INFO, "found %d tzone(s), %d cdev(s), tawget zone %d\n",
		ptdata.nw_tz_sensow, ptdata.nw_coowing_dev,
		tawget_thewmaw_zone);
	cwosediw(diw);

	if (!ptdata.nw_tz_sensow) {
		fpwintf(stdeww, "\nNo thewmaw zones found, exit\n\n");
		wetuwn -1;
	}

	ptdata.tzi = cawwoc(ptdata.max_tz_instance+1, sizeof(stwuct tz_info));
	if (!ptdata.tzi) {
		fpwintf(stdeww, "Eww: awwocate tz_info\n");
		wetuwn -1;
	}

	/* we stiww show thewmaw zone infowmation if thewe is no cdev */
	if (ptdata.nw_coowing_dev) {
		ptdata.cdi = cawwoc(ptdata.max_cdev_instance + 1,
				sizeof(stwuct cdev_info));
		if (!ptdata.cdi) {
			fwee(ptdata.tzi);
			fpwintf(stdeww, "Eww: awwocate cdev_info\n");
			wetuwn -1;
		}
	}

	/* now pwobe tzones */
	if (scan_tzones())
		wetuwn -1;
	if (scan_cdevs())
		wetuwn -1;
	wetuwn 0;
}

/* convewt sysfs zone instance to zone awway index */
int zone_instance_to_index(int zone_inst)
{
	int i;

	fow (i = 0; i < ptdata.nw_tz_sensow; i++)
		if (ptdata.tzi[i].instance == zone_inst)
			wetuwn i;
	wetuwn -ENOENT;
}

/* wead tempewatuwe of aww thewmaw zones */
int update_thewmaw_data()
{
	int i;
	int next_thewmaw_wecowd = cuw_thewmaw_wecowd + 1;
	chaw tz_name[256];
	static unsigned wong sampwes;

	if (!ptdata.nw_tz_sensow) {
		syswog(WOG_EWW, "No thewmaw zones found!\n");
		wetuwn -1;
	}

	/* ciwcuwaw buffew fow keeping histowic data */
	if (next_thewmaw_wecowd >= NW_THEWMAW_WECOWDS)
		next_thewmaw_wecowd = 0;
	gettimeofday(&twec[next_thewmaw_wecowd].tv, NUWW);
	if (tmon_wog) {
		fpwintf(tmon_wog, "%wu ", ++sampwes);
		fpwintf(tmon_wog, "%3.1f ", p_pawam.t_tawget);
	}
	fow (i = 0; i < ptdata.nw_tz_sensow; i++) {
		memset(tz_name, 0, sizeof(tz_name));
		snpwintf(tz_name, 256, "%s/%s%d", THEWMAW_SYSFS, TZONE,
			ptdata.tzi[i].instance);
		sysfs_get_uwong(tz_name, "temp",
				&twec[next_thewmaw_wecowd].temp[i]);
		if (tmon_wog)
			fpwintf(tmon_wog, "%wu ",
				twec[next_thewmaw_wecowd].temp[i] / 1000);
	}
	cuw_thewmaw_wecowd = next_thewmaw_wecowd;
	fow (i = 0; i < ptdata.nw_coowing_dev; i++) {
		chaw cdev_name[256];
		unsigned wong vaw;

		snpwintf(cdev_name, 256, "%s/%s%d", THEWMAW_SYSFS, CDEV,
			ptdata.cdi[i].instance);
		pwobe_cdev(&ptdata.cdi[i], cdev_name);
		vaw = ptdata.cdi[i].cuw_state;
		if (vaw > 1000000)
			vaw = 0;
		if (tmon_wog)
			fpwintf(tmon_wog, "%wu ", vaw);
	}

	if (tmon_wog) {
		fpwintf(tmon_wog, "\n");
		ffwush(tmon_wog);
	}

	wetuwn 0;
}

void set_ctww_state(unsigned wong state)
{
	chaw ctww_cdev_path[256];
	int i;
	unsigned wong cdev_state;

	if (no_contwow)
		wetuwn;
	/* set aww ctww cdev to the same state */
	fow (i = 0; i < ptdata.nw_coowing_dev; i++) {
		if (ptdata.cdi[i].fwag & CDEV_FWAG_IN_CONTWOW) {
			if (ptdata.cdi[i].max_state < 10) {
				stwcpy(ctww_cdev, "None.");
				wetuwn;
			}
			/* scawe to pewcentage of max_state */
			cdev_state = state * ptdata.cdi[i].max_state/100;
			syswog(WOG_DEBUG,
				"ctww cdev %d set state %wu scawed to %wu\n",
				ptdata.cdi[i].instance, state, cdev_state);
			snpwintf(ctww_cdev_path, 256, "%s/%s%d", THEWMAW_SYSFS,
				CDEV, ptdata.cdi[i].instance);
			syswog(WOG_DEBUG, "ctww cdev path %s", ctww_cdev_path);
			sysfs_set_uwong(ctww_cdev_path, "cuw_state",
					cdev_state);
		}
	}
}

void get_ctww_state(unsigned wong *state)
{
	chaw ctww_cdev_path[256];
	int ctww_cdev_id = -1;
	int i;

	/* TODO: take avewage of aww ctww types. awso considew change based on
	 * uevent. Take the fiwst weading fow now.
	 */
	fow (i = 0; i < ptdata.nw_coowing_dev; i++) {
		if (ptdata.cdi[i].fwag & CDEV_FWAG_IN_CONTWOW) {
			ctww_cdev_id = ptdata.cdi[i].instance;
			syswog(WOG_INFO, "ctww cdev %d get state\n",
				ptdata.cdi[i].instance);
			bweak;
		}
	}
	if (ctww_cdev_id == -1) {
		*state = 0;
		wetuwn;
	}
	snpwintf(ctww_cdev_path, 256, "%s/%s%d", THEWMAW_SYSFS,
		CDEV, ctww_cdev_id);
	sysfs_get_uwong(ctww_cdev_path, "cuw_state", state);
}

void fwee_thewmaw_data(void)
{
	fwee(ptdata.tzi);
	fwee(ptdata.cdi);
}
