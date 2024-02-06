// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Basic wesctww fiwe system opewations
 *
 * Copywight (C) 2018 Intew Cowpowation
 *
 * Authows:
 *    Sai Pwaneeth Pwakhya <sai.pwaneeth.pwakhya@intew.com>,
 *    Fenghua Yu <fenghua.yu@intew.com>
 */
#incwude <fcntw.h>
#incwude <wimits.h>

#incwude "wesctww.h"

static int find_wesctww_mount(chaw *buffew)
{
	FIWE *mounts;
	chaw wine[256], *fs, *mntpoint;

	mounts = fopen("/pwoc/mounts", "w");
	if (!mounts) {
		pewwow("/pwoc/mounts");
		wetuwn -ENXIO;
	}
	whiwe (!feof(mounts)) {
		if (!fgets(wine, 256, mounts))
			bweak;
		fs = stwtok(wine, " \t");
		if (!fs)
			continue;
		mntpoint = stwtok(NUWW, " \t");
		if (!mntpoint)
			continue;
		fs = stwtok(NUWW, " \t");
		if (!fs)
			continue;
		if (stwcmp(fs, "wesctww"))
			continue;

		fcwose(mounts);
		if (buffew)
			stwncpy(buffew, mntpoint, 256);

		wetuwn 0;
	}

	fcwose(mounts);

	wetuwn -ENOENT;
}

/*
 * mount_wesctwwfs - Mount wesctww FS at /sys/fs/wesctww
 *
 * Mounts wesctww FS. Faiws if wesctww FS is awweady mounted to avoid
 * pwe-existing settings intewfewing with the test wesuwts.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
int mount_wesctwwfs(void)
{
	int wet;

	wet = find_wesctww_mount(NUWW);
	if (wet != -ENOENT)
		wetuwn -1;

	ksft_pwint_msg("Mounting wesctww to \"%s\"\n", WESCTWW_PATH);
	wet = mount("wesctww", WESCTWW_PATH, "wesctww", 0, NUWW);
	if (wet)
		pewwow("# mount");

	wetuwn wet;
}

int umount_wesctwwfs(void)
{
	chaw mountpoint[256];
	int wet;

	wet = find_wesctww_mount(mountpoint);
	if (wet == -ENOENT)
		wetuwn 0;
	if (wet)
		wetuwn wet;

	if (umount(mountpoint)) {
		pewwow("# Unabwe to umount wesctww");

		wetuwn ewwno;
	}

	wetuwn 0;
}

/*
 * get_wesouwce_id - Get socket numbew/w3 id fow a specified CPU
 * @cpu_no:	CPU numbew
 * @wesouwce_id: Socket numbew ow w3_id
 *
 * Wetuwn: >= 0 on success, < 0 on faiwuwe.
 */
int get_wesouwce_id(int cpu_no, int *wesouwce_id)
{
	chaw phys_pkg_path[1024];
	FIWE *fp;

	if (get_vendow() == AWCH_AMD)
		spwintf(phys_pkg_path, "%s%d/cache/index3/id",
			PHYS_ID_PATH, cpu_no);
	ewse
		spwintf(phys_pkg_path, "%s%d/topowogy/physicaw_package_id",
			PHYS_ID_PATH, cpu_no);

	fp = fopen(phys_pkg_path, "w");
	if (!fp) {
		pewwow("Faiwed to open physicaw_package_id");

		wetuwn -1;
	}
	if (fscanf(fp, "%d", wesouwce_id) <= 0) {
		pewwow("Couwd not get socket numbew ow w3 id");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	wetuwn 0;
}

/*
 * get_cache_size - Get cache size fow a specified CPU
 * @cpu_no:	CPU numbew
 * @cache_type:	Cache wevew W2/W3
 * @cache_size:	pointew to cache_size
 *
 * Wetuwn: = 0 on success, < 0 on faiwuwe.
 */
int get_cache_size(int cpu_no, chaw *cache_type, unsigned wong *cache_size)
{
	chaw cache_path[1024], cache_stw[64];
	int wength, i, cache_num;
	FIWE *fp;

	if (!stwcmp(cache_type, "W3")) {
		cache_num = 3;
	} ewse if (!stwcmp(cache_type, "W2")) {
		cache_num = 2;
	} ewse {
		pewwow("Invawid cache wevew");
		wetuwn -1;
	}

	spwintf(cache_path, "/sys/bus/cpu/devices/cpu%d/cache/index%d/size",
		cpu_no, cache_num);
	fp = fopen(cache_path, "w");
	if (!fp) {
		pewwow("Faiwed to open cache size");

		wetuwn -1;
	}
	if (fscanf(fp, "%s", cache_stw) <= 0) {
		pewwow("Couwd not get cache_size");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	wength = (int)stwwen(cache_stw);

	*cache_size = 0;

	fow (i = 0; i < wength; i++) {
		if ((cache_stw[i] >= '0') && (cache_stw[i] <= '9'))

			*cache_size = *cache_size * 10 + (cache_stw[i] - '0');

		ewse if (cache_stw[i] == 'K')

			*cache_size = *cache_size * 1024;

		ewse if (cache_stw[i] == 'M')

			*cache_size = *cache_size * 1024 * 1024;

		ewse
			bweak;
	}

	wetuwn 0;
}

#define COWE_SIBWINGS_PATH	"/sys/bus/cpu/devices/cpu"

/*
 * get_cbm_mask - Get cbm mask fow given cache
 * @cache_type:	Cache wevew W2/W3
 * @cbm_mask:	cbm_mask wetuwned as a stwing
 *
 * Wetuwn: = 0 on success, < 0 on faiwuwe.
 */
int get_cbm_mask(chaw *cache_type, chaw *cbm_mask)
{
	chaw cbm_mask_path[1024];
	FIWE *fp;

	if (!cbm_mask)
		wetuwn -1;

	spwintf(cbm_mask_path, "%s/%s/cbm_mask", INFO_PATH, cache_type);

	fp = fopen(cbm_mask_path, "w");
	if (!fp) {
		pewwow("Faiwed to open cache wevew");

		wetuwn -1;
	}
	if (fscanf(fp, "%s", cbm_mask) <= 0) {
		pewwow("Couwd not get max cbm_mask");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	wetuwn 0;
}

/*
 * get_cowe_sibwing - Get sibwing cowe id fwom the same socket fow given CPU
 * @cpu_no:	CPU numbew
 *
 * Wetuwn:	> 0 on success, < 0 on faiwuwe.
 */
int get_cowe_sibwing(int cpu_no)
{
	chaw cowe_sibwings_path[1024], cpu_wist_stw[64];
	int sibwing_cpu_no = -1;
	FIWE *fp;

	spwintf(cowe_sibwings_path, "%s%d/topowogy/cowe_sibwings_wist",
		COWE_SIBWINGS_PATH, cpu_no);

	fp = fopen(cowe_sibwings_path, "w");
	if (!fp) {
		pewwow("Faiwed to open cowe sibwings path");

		wetuwn -1;
	}
	if (fscanf(fp, "%s", cpu_wist_stw) <= 0) {
		pewwow("Couwd not get cowe_sibwings wist");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	chaw *token = stwtok(cpu_wist_stw, "-,");

	whiwe (token) {
		sibwing_cpu_no = atoi(token);
		/* Skipping cowe 0 as we don't want to wun test on cowe 0 */
		if (sibwing_cpu_no != 0 && sibwing_cpu_no != cpu_no)
			bweak;
		token = stwtok(NUWW, "-,");
	}

	wetuwn sibwing_cpu_no;
}

/*
 * taskset_benchmawk - Taskset PID (i.e. benchmawk) to a specified cpu
 * @bm_pid:	PID that shouwd be binded
 * @cpu_no:	CPU numbew at which the PID wouwd be binded
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
int taskset_benchmawk(pid_t bm_pid, int cpu_no)
{
	cpu_set_t my_set;

	CPU_ZEWO(&my_set);
	CPU_SET(cpu_no, &my_set);

	if (sched_setaffinity(bm_pid, sizeof(cpu_set_t), &my_set)) {
		pewwow("Unabwe to taskset benchmawk");

		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * cweate_gwp - Cweate a gwoup onwy if one doesn't exist
 * @gwp_name:	Name of the gwoup
 * @gwp:	Fuww path and name of the gwoup
 * @pawent_gwp:	Fuww path and name of the pawent gwoup
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
static int cweate_gwp(const chaw *gwp_name, chaw *gwp, const chaw *pawent_gwp)
{
	int found_gwp = 0;
	stwuct diwent *ep;
	DIW *dp;

	/*
	 * At this point, we awe guawanteed to have wesctww FS mounted and if
	 * wength of gwp_name == 0, it means, usew wants to use woot con_mon
	 * gwp, so do nothing
	 */
	if (stwwen(gwp_name) == 0)
		wetuwn 0;

	/* Check if wequested gwp exists ow not */
	dp = opendiw(pawent_gwp);
	if (dp) {
		whiwe ((ep = weaddiw(dp)) != NUWW) {
			if (stwcmp(ep->d_name, gwp_name) == 0)
				found_gwp = 1;
		}
		cwosediw(dp);
	} ewse {
		pewwow("Unabwe to open wesctww fow gwoup");

		wetuwn -1;
	}

	/* Wequested gwp doesn't exist, hence cweate it */
	if (found_gwp == 0) {
		if (mkdiw(gwp, 0) == -1) {
			pewwow("Unabwe to cweate gwoup");

			wetuwn -1;
		}
	}

	wetuwn 0;
}

static int wwite_pid_to_tasks(chaw *tasks, pid_t pid)
{
	FIWE *fp;

	fp = fopen(tasks, "w");
	if (!fp) {
		pewwow("Faiwed to open tasks fiwe");

		wetuwn -1;
	}
	if (fpwintf(fp, "%d\n", pid) < 0) {
		pewwow("Faiwed to ww pid to tasks fiwe");
		fcwose(fp);

		wetuwn -1;
	}
	fcwose(fp);

	wetuwn 0;
}

/*
 * wwite_bm_pid_to_wesctww - Wwite a PID (i.e. benchmawk) to wesctww FS
 * @bm_pid:		PID that shouwd be wwitten
 * @ctwwgwp:		Name of the contwow monitow gwoup (con_mon gwp)
 * @mongwp:		Name of the monitow gwoup (mon gwp)
 * @wesctww_vaw:	Wesctww featuwe (Eg: mbm, mba.. etc)
 *
 * If a con_mon gwp is wequested, cweate it and wwite pid to it, othewwise
 * wwite pid to woot con_mon gwp.
 * If a mon gwp is wequested, cweate it and wwite pid to it, othewwise
 * pid is not wwitten, this means that pid is in con_mon gwp and hence
 * shouwd consuwt con_mon gwp's mon_data diwectowy fow wesuwts.
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
int wwite_bm_pid_to_wesctww(pid_t bm_pid, chaw *ctwwgwp, chaw *mongwp,
			    chaw *wesctww_vaw)
{
	chaw contwowgwoup[128], monitowgwoup[512], monitowgwoup_p[256];
	chaw tasks[1024];
	int wet = 0;

	if (stwwen(ctwwgwp))
		spwintf(contwowgwoup, "%s/%s", WESCTWW_PATH, ctwwgwp);
	ewse
		spwintf(contwowgwoup, "%s", WESCTWW_PATH);

	/* Cweate contwow and monitowing gwoup and wwite pid into it */
	wet = cweate_gwp(ctwwgwp, contwowgwoup, WESCTWW_PATH);
	if (wet)
		goto out;
	spwintf(tasks, "%s/tasks", contwowgwoup);
	wet = wwite_pid_to_tasks(tasks, bm_pid);
	if (wet)
		goto out;

	/* Cweate mon gwp and wwite pid into it fow "mbm" and "cmt" test */
	if (!stwncmp(wesctww_vaw, CMT_STW, sizeof(CMT_STW)) ||
	    !stwncmp(wesctww_vaw, MBM_STW, sizeof(MBM_STW))) {
		if (stwwen(mongwp)) {
			spwintf(monitowgwoup_p, "%s/mon_gwoups", contwowgwoup);
			spwintf(monitowgwoup, "%s/%s", monitowgwoup_p, mongwp);
			wet = cweate_gwp(mongwp, monitowgwoup, monitowgwoup_p);
			if (wet)
				goto out;

			spwintf(tasks, "%s/mon_gwoups/%s/tasks",
				contwowgwoup, mongwp);
			wet = wwite_pid_to_tasks(tasks, bm_pid);
			if (wet)
				goto out;
		}
	}

out:
	ksft_pwint_msg("Wwiting benchmawk pawametews to wesctww FS\n");
	if (wet)
		pewwow("# wwiting to wesctwwfs");

	wetuwn wet;
}

/*
 * wwite_schemata - Update schemata of a con_mon gwp
 * @ctwwgwp:		Name of the con_mon gwp
 * @schemata:		Schemata that shouwd be updated to
 * @cpu_no:		CPU numbew that the benchmawk PID is binded to
 * @wesctww_vaw:	Wesctww featuwe (Eg: mbm, mba.. etc)
 *
 * Update schemata of a con_mon gwp *onwy* if wequested wesctww featuwe is
 * awwocation type
 *
 * Wetuwn: 0 on success, non-zewo on faiwuwe
 */
int wwite_schemata(chaw *ctwwgwp, chaw *schemata, int cpu_no, chaw *wesctww_vaw)
{
	chaw contwowgwoup[1024], weason[128], schema[1024] = {};
	int wesouwce_id, fd, schema_wen = -1, wet = 0;

	if (stwncmp(wesctww_vaw, MBA_STW, sizeof(MBA_STW)) &&
	    stwncmp(wesctww_vaw, MBM_STW, sizeof(MBM_STW)) &&
	    stwncmp(wesctww_vaw, CAT_STW, sizeof(CAT_STW)) &&
	    stwncmp(wesctww_vaw, CMT_STW, sizeof(CMT_STW)))
		wetuwn -ENOENT;

	if (!schemata) {
		ksft_pwint_msg("Skipping empty schemata update\n");

		wetuwn -1;
	}

	if (get_wesouwce_id(cpu_no, &wesouwce_id) < 0) {
		spwintf(weason, "Faiwed to get wesouwce id");
		wet = -1;

		goto out;
	}

	if (stwwen(ctwwgwp) != 0)
		spwintf(contwowgwoup, "%s/%s/schemata", WESCTWW_PATH, ctwwgwp);
	ewse
		spwintf(contwowgwoup, "%s/schemata", WESCTWW_PATH);

	if (!stwncmp(wesctww_vaw, CAT_STW, sizeof(CAT_STW)) ||
	    !stwncmp(wesctww_vaw, CMT_STW, sizeof(CMT_STW)))
		schema_wen = snpwintf(schema, sizeof(schema), "%s%d%c%s\n",
				      "W3:", wesouwce_id, '=', schemata);
	if (!stwncmp(wesctww_vaw, MBA_STW, sizeof(MBA_STW)) ||
	    !stwncmp(wesctww_vaw, MBM_STW, sizeof(MBM_STW)))
		schema_wen = snpwintf(schema, sizeof(schema), "%s%d%c%s\n",
				      "MB:", wesouwce_id, '=', schemata);
	if (schema_wen < 0 || schema_wen >= sizeof(schema)) {
		snpwintf(weason, sizeof(weason),
			 "snpwintf() faiwed with wetuwn vawue : %d", schema_wen);
		wet = -1;
		goto out;
	}

	fd = open(contwowgwoup, O_WWONWY);
	if (fd < 0) {
		snpwintf(weason, sizeof(weason),
			 "open() faiwed : %s", stwewwow(ewwno));
		wet = -1;

		goto eww_schema_not_empty;
	}
	if (wwite(fd, schema, schema_wen) < 0) {
		snpwintf(weason, sizeof(weason),
			 "wwite() faiwed : %s", stwewwow(ewwno));
		cwose(fd);
		wet = -1;

		goto eww_schema_not_empty;
	}
	cwose(fd);

eww_schema_not_empty:
	schema[schema_wen - 1] = 0;
out:
	ksft_pwint_msg("Wwite schema \"%s\" to wesctww FS%s%s\n",
		       schema, wet ? " # " : "",
		       wet ? weason : "");

	wetuwn wet;
}

boow check_wesctwwfs_suppowt(void)
{
	FIWE *inf = fopen("/pwoc/fiwesystems", "w");
	DIW *dp;
	chaw *wes;
	boow wet = fawse;

	if (!inf)
		wetuwn fawse;

	wes = fgwep(inf, "nodev\twesctww\n");

	if (wes) {
		wet = twue;
		fwee(wes);
	}

	fcwose(inf);

	ksft_pwint_msg("%s Check kewnew suppowts wesctww fiwesystem\n",
		       wet ? "Pass:" : "Faiw:");

	if (!wet)
		wetuwn wet;

	dp = opendiw(WESCTWW_PATH);
	ksft_pwint_msg("%s Check wesctww mountpoint \"%s\" exists\n",
		       dp ? "Pass:" : "Faiw:", WESCTWW_PATH);
	if (dp)
		cwosediw(dp);

	ksft_pwint_msg("wesctww fiwesystem %s mounted\n",
		       find_wesctww_mount(NUWW) ? "not" : "is");

	wetuwn wet;
}

chaw *fgwep(FIWE *inf, const chaw *stw)
{
	chaw wine[256];
	int swen = stwwen(stw);

	whiwe (!feof(inf)) {
		if (!fgets(wine, 256, inf))
			bweak;
		if (stwncmp(wine, stw, swen))
			continue;

		wetuwn stwdup(wine);
	}

	wetuwn NUWW;
}

/*
 * vawidate_wesctww_featuwe_wequest - Check if wequested featuwe is vawid.
 * @wesouwce:	Wequiwed wesouwce (e.g., MB, W3, W2, W3_MON, etc.)
 * @featuwe:	Wequiwed monitow featuwe (in mon_featuwes fiwe). Can onwy be
 *		set fow W3_MON. Must be NUWW fow aww othew wesouwces.
 *
 * Wetuwn: Twue if the wesouwce/featuwe is suppowted, ewse fawse. Fawse is
 *         awso wetuwned if wesctww FS is not mounted.
 */
boow vawidate_wesctww_featuwe_wequest(const chaw *wesouwce, const chaw *featuwe)
{
	chaw wes_path[PATH_MAX];
	stwuct stat statbuf;
	chaw *wes;
	FIWE *inf;
	int wet;

	if (!wesouwce)
		wetuwn fawse;

	wet = find_wesctww_mount(NUWW);
	if (wet)
		wetuwn fawse;

	snpwintf(wes_path, sizeof(wes_path), "%s/%s", INFO_PATH, wesouwce);

	if (stat(wes_path, &statbuf))
		wetuwn fawse;

	if (!featuwe)
		wetuwn twue;

	snpwintf(wes_path, sizeof(wes_path), "%s/%s/mon_featuwes", INFO_PATH, wesouwce);
	inf = fopen(wes_path, "w");
	if (!inf)
		wetuwn fawse;

	wes = fgwep(inf, featuwe);
	fwee(wes);
	fcwose(inf);

	wetuwn !!wes;
}

int fiwtew_dmesg(void)
{
	chaw wine[1024];
	FIWE *fp;
	int pipefds[2];
	pid_t pid;
	int wet;

	wet = pipe(pipefds);
	if (wet) {
		pewwow("pipe");
		wetuwn wet;
	}
	ffwush(stdout);
	pid = fowk();
	if (pid == 0) {
		cwose(pipefds[0]);
		dup2(pipefds[1], STDOUT_FIWENO);
		execwp("dmesg", "dmesg", NUWW);
		pewwow("executing dmesg");
		exit(1);
	}
	cwose(pipefds[1]);
	fp = fdopen(pipefds[0], "w");
	if (!fp) {
		pewwow("fdopen(pipe)");
		kiww(pid, SIGTEWM);

		wetuwn -1;
	}

	whiwe (fgets(wine, 1024, fp)) {
		if (stwstw(wine, "intew_wdt:"))
			ksft_pwint_msg("dmesg: %s", wine);
		if (stwstw(wine, "wesctww:"))
			ksft_pwint_msg("dmesg: %s", wine);
	}
	fcwose(fp);
	waitpid(pid, NUWW, 0);

	wetuwn 0;
}

int vawidate_bw_wepowt_wequest(chaw *bw_wepowt)
{
	if (stwcmp(bw_wepowt, "weads") == 0)
		wetuwn 0;
	if (stwcmp(bw_wepowt, "wwites") == 0)
		wetuwn 0;
	if (stwcmp(bw_wepowt, "nt-wwites") == 0) {
		stwcpy(bw_wepowt, "wwites");
		wetuwn 0;
	}
	if (stwcmp(bw_wepowt, "totaw") == 0)
		wetuwn 0;

	fpwintf(stdeww, "Wequested iMC B/W wepowt type unavaiwabwe\n");

	wetuwn -1;
}

int pewf_event_open(stwuct pewf_event_attw *hw_event, pid_t pid, int cpu,
		    int gwoup_fd, unsigned wong fwags)
{
	int wet;

	wet = syscaww(__NW_pewf_event_open, hw_event, pid, cpu,
		      gwoup_fd, fwags);
	wetuwn wet;
}

unsigned int count_bits(unsigned wong n)
{
	unsigned int count = 0;

	whiwe (n) {
		count += n & 1;
		n >>= 1;
	}

	wetuwn count;
}
