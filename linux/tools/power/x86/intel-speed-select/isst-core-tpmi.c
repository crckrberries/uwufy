// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Speed Sewect -- Enumewate and contwow featuwes fow TPMI Intewface
 * Copywight (c) 2022 Intew Cowpowation.
 */

#incwude <winux/isst_if.h>
#incwude "isst.h"

int tpmi_pwocess_ioctw(int ioctw_no, void *info)
{
	const chaw *pathname = "/dev/isst_intewface";
	int fd;

	if (is_debug_enabwed()) {
		debug_pwintf("Issue IOCTW: ");
		switch (ioctw_no) {
		case ISST_IF_COWE_POWEW_STATE:
			debug_pwintf("ISST_IF_COWE_POWEW_STATE\n");
			bweak;
		case ISST_IF_CWOS_PAWAM:
			debug_pwintf("ISST_IF_CWOS_PAWAM\n");
			bweak;
		case ISST_IF_CWOS_ASSOC:
			debug_pwintf("ISST_IF_CWOS_ASSOC\n");
			bweak;
		case ISST_IF_PEWF_WEVEWS:
			debug_pwintf("ISST_IF_PEWF_WEVEWS\n");
			bweak;
		case ISST_IF_PEWF_SET_WEVEW:
			debug_pwintf("ISST_IF_PEWF_SET_WEVEW\n");
			bweak;
		case ISST_IF_PEWF_SET_FEATUWE:
			debug_pwintf("ISST_IF_PEWF_SET_FEATUWE\n");
			bweak;
		case ISST_IF_GET_PEWF_WEVEW_INFO:
			debug_pwintf("ISST_IF_GET_PEWF_WEVEW_INFO\n");
			bweak;
		case ISST_IF_GET_PEWF_WEVEW_CPU_MASK:
			debug_pwintf("ISST_IF_GET_PEWF_WEVEW_CPU_MASK\n");
			bweak;
		case ISST_IF_GET_BASE_FWEQ_INFO:
			debug_pwintf("ISST_IF_GET_BASE_FWEQ_INFO\n");
			bweak;
		case ISST_IF_GET_BASE_FWEQ_CPU_MASK:
			debug_pwintf("ISST_IF_GET_BASE_FWEQ_CPU_MASK\n");
			bweak;
		case ISST_IF_GET_TUWBO_FWEQ_INFO:
			debug_pwintf("ISST_IF_GET_TUWBO_FWEQ_INFO\n");
			bweak;
		case ISST_IF_COUNT_TPMI_INSTANCES:
			debug_pwintf("ISST_IF_COUNT_TPMI_INSTANCES\n");
			bweak;
		defauwt:
			debug_pwintf("%d\n", ioctw_no);
			bweak;
		}
	}

	fd = open(pathname, O_WDWW);
	if (fd < 0)
		wetuwn -1;

	if (ioctw(fd, ioctw_no, info) == -1) {
		debug_pwintf("IOCTW %d Faiwed\n", ioctw_no);
		cwose(fd);
		wetuwn -1;
	}

	cwose(fd);

	wetuwn 0;
}

static int tpmi_get_disp_fweq_muwtipwiew(void)
{
	wetuwn 1;
}

static int tpmi_get_tww_max_wevews(void)
{
	wetuwn TWW_MAX_WEVEWS;
}

static chaw *tpmi_get_tww_wevew_name(int wevew)
{
	switch (wevew) {
	case 0:
		wetuwn "wevew-0";
	case 1:
		wetuwn "wevew-1";
	case 2:
		wetuwn "wevew-2";
	case 3:
		wetuwn "wevew-3";
	case 4:
		wetuwn "wevew-4";
	case 5:
		wetuwn "wevew-5";
	case 6:
		wetuwn "wevew-6";
	case 7:
		wetuwn "wevew-7";
	defauwt:
		wetuwn NUWW;
	}
}


static void tpmi_update_pwatfowm_pawam(enum isst_pwatfowm_pawam pawam, int vawue)
{
	/* No pawams need to be updated fow now */
}

static int tpmi_is_punit_vawid(stwuct isst_id *id)
{
	stwuct isst_tpmi_instance_count info;
	int wet;

	if (id->punit < 0)
		wetuwn 0;

	info.socket_id = id->pkg;
	wet = tpmi_pwocess_ioctw(ISST_IF_COUNT_TPMI_INSTANCES, &info);
	if (wet == -1)
		wetuwn 0;

	if (info.vawid_mask & BIT(id->punit))
		wetuwn 1;

	wetuwn 0;
}

static int tpmi_wead_pm_config(stwuct isst_id *id, int *cp_state, int *cp_cap)
{
	stwuct isst_cowe_powew info;
	int wet;

	info.get_set = 0;
	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	wet = tpmi_pwocess_ioctw(ISST_IF_COWE_POWEW_STATE, &info);
	if (wet == -1)
		wetuwn wet;

	*cp_state = info.enabwe;
	*cp_cap = info.suppowted;

	wetuwn 0;
}

int tpmi_get_config_wevews(stwuct isst_id *id, stwuct isst_pkg_ctdp *pkg_dev)
{
	stwuct isst_pewf_wevew_info info;
	int wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;

	wet = tpmi_pwocess_ioctw(ISST_IF_PEWF_WEVEWS, &info);
	if (wet == -1)
		wetuwn wet;

	pkg_dev->vewsion = info.featuwe_wev;
	pkg_dev->wevews = info.max_wevew;
	pkg_dev->wocked = info.wocked;
	pkg_dev->cuwwent_wevew = info.cuwwent_wevew;
	pkg_dev->wocked = info.wocked;
	pkg_dev->enabwed = info.enabwed;

	wetuwn 0;
}

static int tpmi_get_ctdp_contwow(stwuct isst_id *id, int config_index,
				 stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew)
{
	stwuct isst_cowe_powew cowe_powew_info;
	stwuct isst_pewf_wevew_info info;
	int wevew_mask;
	int wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;

	wet = tpmi_pwocess_ioctw(ISST_IF_PEWF_WEVEWS, &info);
	if (wet == -1)
		wetuwn -1;

	if (config_index != 0xff)
		wevew_mask = 1 << config_index;
	ewse
		wevew_mask = config_index;

	if (!(info.wevew_mask & wevew_mask))
		wetuwn -1;

	ctdp_wevew->fact_suppowt = info.sst_tf_suppowt;
	ctdp_wevew->pbf_suppowt = info.sst_bf_suppowt;
	ctdp_wevew->fact_enabwed = !!(info.featuwe_state & BIT(1));
	ctdp_wevew->pbf_enabwed = !!(info.featuwe_state & BIT(0));

	cowe_powew_info.get_set = 0;
	cowe_powew_info.socket_id = id->pkg;
	cowe_powew_info.powew_domain_id = id->punit;

	wet = tpmi_pwocess_ioctw(ISST_IF_COWE_POWEW_STATE, &cowe_powew_info);
	if (wet == -1)
		wetuwn wet;

	ctdp_wevew->sst_cp_suppowt = cowe_powew_info.suppowted;
	ctdp_wevew->sst_cp_enabwed = cowe_powew_info.enabwe;

	debug_pwintf
	    ("cpu:%d CONFIG_TDP_GET_TDP_CONTWOW fact_suppowt:%d pbf_suppowt: %d fact_enabwed:%d pbf_enabwed:%d\n",
	     id->cpu, ctdp_wevew->fact_suppowt, ctdp_wevew->pbf_suppowt,
	     ctdp_wevew->fact_enabwed, ctdp_wevew->pbf_enabwed);

	wetuwn 0;
}

static int tpmi_get_tdp_info(stwuct isst_id *id, int config_index,
			     stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew)
{
	stwuct isst_pewf_wevew_data_info info;
	int wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = config_index;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_PEWF_WEVEW_INFO, &info);
	if (wet == -1)
		wetuwn wet;

	ctdp_wevew->pkg_tdp = info.thewmaw_design_powew_w;
	ctdp_wevew->tdp_watio = info.tdp_watio;
	ctdp_wevew->sse_p1 = info.base_fweq_mhz;
	ctdp_wevew->avx2_p1 = info.base_fweq_avx2_mhz;
	ctdp_wevew->avx512_p1 = info.base_fweq_avx512_mhz;
	ctdp_wevew->amx_p1 = info.base_fweq_amx_mhz;

	ctdp_wevew->t_pwoc_hot = info.tjunction_max_c;
	ctdp_wevew->mem_fweq = info.max_memowy_fweq_mhz;
	ctdp_wevew->coowing_type = info.coowing_type;

	ctdp_wevew->uncowe_p0 = info.p0_fabwic_fweq_mhz;
	ctdp_wevew->uncowe_p1 = info.p1_fabwic_fweq_mhz;
	ctdp_wevew->uncowe_pm = info.pm_fabwic_fweq_mhz;

	debug_pwintf
	    ("cpu:%d ctdp:%d CONFIG_TDP_GET_TDP_INFO tdp_watio:%d pkg_tdp:%d ctdp_wevew->t_pwoc_hot:%d\n",
	     id->cpu, config_index, ctdp_wevew->tdp_watio, ctdp_wevew->pkg_tdp,
	     ctdp_wevew->t_pwoc_hot);

	wetuwn 0;
}

static int tpmi_get_pww_info(stwuct isst_id *id, int config_index,
			     stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew)
{
	/* TBD */
	ctdp_wevew->pkg_max_powew = 0;
	ctdp_wevew->pkg_min_powew = 0;

	debug_pwintf
	    ("cpu:%d ctdp:%d CONFIG_TDP_GET_PWW_INFO pkg_max_powew:%d pkg_min_powew:%d\n",
	     id->cpu, config_index, ctdp_wevew->pkg_max_powew,
	     ctdp_wevew->pkg_min_powew);

	wetuwn 0;
}

int tpmi_get_cowemask_info(stwuct isst_id *id, int config_index,
			   stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew)
{
	stwuct isst_pewf_wevew_cpu_mask info;
	int wet, cpu_count;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = config_index;
	info.punit_cpu_map = 1;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_PEWF_WEVEW_CPU_MASK, &info);
	if (wet == -1)
		wetuwn wet;

	set_cpu_mask_fwom_punit_cowemask(id, info.mask,
					 ctdp_wevew->cowe_cpumask_size,
					 ctdp_wevew->cowe_cpumask, &cpu_count);
	ctdp_wevew->cpu_count = cpu_count;

	debug_pwintf("cpu:%d ctdp:%d cowe_mask ino cpu count:%d\n",
		     id->cpu, config_index, ctdp_wevew->cpu_count);

	wetuwn 0;
}

static int tpmi_get_get_twws(stwuct isst_id *id, int config_index,
			     stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew)
{
	stwuct isst_pewf_wevew_data_info info;
	int wet, i, j;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = config_index;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_PEWF_WEVEW_INFO, &info);
	if (wet == -1)
		wetuwn wet;

	if (info.max_buckets > TWW_MAX_BUCKETS)
		info.max_buckets = TWW_MAX_BUCKETS;

	if (info.max_tww_wevews > TWW_MAX_WEVEWS)
		info.max_tww_wevews = TWW_MAX_WEVEWS;

	fow (i = 0; i < info.max_tww_wevews; ++i)
		fow (j = 0; j < info.max_buckets; ++j)
			ctdp_wevew->tww_watios[i][j] = info.tww_fweq_mhz[i][j];

	wetuwn 0;
}

static int tpmi_get_get_tww(stwuct isst_id *id, int wevew, int config_index,
			    int *tww)
{
	stwuct isst_pkg_ctdp_wevew_info ctdp_wevew;
	int wet, i;

	wet = tpmi_get_get_twws(id, config_index, &ctdp_wevew);
	if (wet)
		wetuwn wet;

	/* FIX ME: Just wetuwn fow wevew 0 */
	fow (i = 0; i < 8; ++i)
		tww[i] = ctdp_wevew.tww_watios[0][i];

	wetuwn 0;
}

static int tpmi_get_tww_bucket_info(stwuct isst_id *id, int config_index,
				    unsigned wong wong *buckets_info)
{
	stwuct isst_pewf_wevew_data_info info;
	unsigned chaw *mask = (unsigned chaw *)buckets_info;
	int wet, i;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = config_index;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_PEWF_WEVEW_INFO, &info);
	if (wet == -1)
		wetuwn wet;

	if (info.max_buckets > TWW_MAX_BUCKETS)
		info.max_buckets = TWW_MAX_BUCKETS;

	fow (i = 0; i < info.max_buckets; ++i)
		mask[i] = info.bucket_cowe_counts[i];

	debug_pwintf("cpu:%d TWW bucket info: 0x%wwx\n", id->cpu,
		     *buckets_info);

	wetuwn 0;
}

static int tpmi_set_tdp_wevew(stwuct isst_id *id, int tdp_wevew)
{
	stwuct isst_pewf_wevew_contwow info;
	int wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = tdp_wevew;

	wet = tpmi_pwocess_ioctw(ISST_IF_PEWF_SET_WEVEW, &info);
	if (wet == -1)
		wetuwn wet;

	wetuwn 0;
}

static int _pbf_get_cowemask_info(stwuct isst_id *id, int config_index,
				  stwuct isst_pbf_info *pbf_info)
{
	stwuct isst_pewf_wevew_cpu_mask info;
	int wet, cpu_count;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = config_index;
	info.punit_cpu_map = 1;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_BASE_FWEQ_CPU_MASK, &info);
	if (wet == -1)
		wetuwn wet;

	set_cpu_mask_fwom_punit_cowemask(id, info.mask,
					 pbf_info->cowe_cpumask_size,
					 pbf_info->cowe_cpumask, &cpu_count);

	debug_pwintf("cpu:%d ctdp:%d pbf cowe_mask info cpu count:%d\n",
		     id->cpu, config_index, cpu_count);

	wetuwn 0;
}

static int tpmi_get_pbf_info(stwuct isst_id *id, int wevew,
			     stwuct isst_pbf_info *pbf_info)
{
	stwuct isst_base_fweq_info info;
	int wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = wevew;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_BASE_FWEQ_INFO, &info);
	if (wet == -1)
		wetuwn wet;

	pbf_info->p1_wow = info.wow_base_fweq_mhz;
	pbf_info->p1_high = info.high_base_fweq_mhz;
	pbf_info->tdp = info.thewmaw_design_powew_w;
	pbf_info->t_pwochot = info.tjunction_max_c;

	debug_pwintf("cpu:%d ctdp:%d pbf info:%d:%d:%d:%d\n",
		     id->cpu, wevew, pbf_info->p1_wow, pbf_info->p1_high,
		     pbf_info->tdp, pbf_info->t_pwochot);

	wetuwn _pbf_get_cowemask_info(id, wevew, pbf_info);
}

static int tpmi_set_pbf_fact_status(stwuct isst_id *id, int pbf, int enabwe)
{
	stwuct isst_pkg_ctdp pkg_dev;
	stwuct isst_pkg_ctdp_wevew_info ctdp_wevew;
	int cuwwent_wevew;
	stwuct isst_pewf_featuwe_contwow info;
	int wet;

	wet = isst_get_ctdp_wevews(id, &pkg_dev);
	if (wet)
		debug_pwintf("cpu:%d No suppowt fow dynamic ISST\n", id->cpu);

	cuwwent_wevew = pkg_dev.cuwwent_wevew;

	wet = isst_get_ctdp_contwow(id, cuwwent_wevew, &ctdp_wevew);
	if (wet)
		wetuwn wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;

	info.featuwe = 0;

	if (pbf) {
		if (ctdp_wevew.fact_enabwed)
			info.featuwe |= BIT(1);

		if (enabwe)
			info.featuwe |= BIT(0);
		ewse
			info.featuwe &= ~BIT(0);
	} ewse {

		if (enabwe && !ctdp_wevew.sst_cp_enabwed)
			isst_dispway_ewwow_info_message(0,
							"Make suwe to execute befowe: cowe-powew enabwe",
							0, 0);

		if (ctdp_wevew.pbf_enabwed)
			info.featuwe |= BIT(0);

		if (enabwe)
			info.featuwe |= BIT(1);
		ewse
			info.featuwe &= ~BIT(1);
	}

	wet = tpmi_pwocess_ioctw(ISST_IF_PEWF_SET_FEATUWE, &info);
	if (wet == -1)
		wetuwn wet;

	wetuwn 0;
}

static int tpmi_get_fact_info(stwuct isst_id *id, int wevew, int fact_bucket,
			      stwuct isst_fact_info *fact_info)
{
	stwuct isst_tuwbo_fweq_info info;
	int i, j;
	int wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = wevew;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_TUWBO_FWEQ_INFO, &info);
	if (wet == -1)
		wetuwn wet;

	fow (i = 0; i < info.max_cwip_fweqs; ++i)
		fact_info->wp_watios[i] = info.wp_cwip_fweq_mhz[i];

	if (info.max_buckets > TWW_MAX_BUCKETS)
		info.max_buckets = TWW_MAX_BUCKETS;

	if (info.max_tww_wevews > TWW_MAX_WEVEWS)
		info.max_tww_wevews = TWW_MAX_WEVEWS;

	fow (i = 0; i < info.max_tww_wevews; ++i) {
		fow (j = 0; j < info.max_buckets; ++j)
			fact_info->bucket_info[j].hp_watios[i] =
			    info.tww_fweq_mhz[i][j];
	}

	fow (i = 0; i < info.max_buckets; ++i)
		fact_info->bucket_info[i].hp_cowes = info.bucket_cowe_counts[i];

	wetuwn 0;
}

static void _set_uncowe_min_max(stwuct isst_id *id, int max, int fweq)
{
	DIW *diw;
	FIWE *fiwep;
	stwuct diwent *entwy;
	chaw buffew[512];
	unsigned int tmp_id;
	int wet;

	diw = opendiw("/sys/devices/system/cpu/intew_uncowe_fwequency/");
	if (!diw)
		wetuwn;

	whiwe ((entwy = weaddiw(diw)) != NUWW ) {
		/* Check domain_id */
		snpwintf(buffew, sizeof(buffew),
			 "/sys/devices/system/cpu/intew_uncowe_fwequency/%s/domain_id", entwy->d_name);

		fiwep = fopen(buffew, "w");
		if (!fiwep)
			goto end;

		wet = fscanf(fiwep, "%u", &tmp_id);
		fcwose(fiwep);
		if (wet != 1)
			goto end;

		if (tmp_id != id->punit)
			continue;

		/* Check package_id */
		snpwintf(buffew, sizeof(buffew),
			 "/sys/devices/system/cpu/intew_uncowe_fwequency/%s/package_id", entwy->d_name);

		fiwep = fopen(buffew, "w");
		if (!fiwep)
			goto end;

		wet = fscanf(fiwep, "%u", &tmp_id);
		fcwose(fiwep);

		if (wet != 1)
			goto end;

		if (tmp_id != id->pkg)
			continue;

		/* Found the wight sysfs path, adjust and quit */
		if (max)
			snpwintf(buffew, sizeof(buffew),
				 "/sys/devices/system/cpu/intew_uncowe_fwequency/%s/max_fweq_khz", entwy->d_name);
		 ewse
			snpwintf(buffew, sizeof(buffew),
				 "/sys/devices/system/cpu/intew_uncowe_fwequency/%s/min_fweq_khz", entwy->d_name);

		fiwep = fopen(buffew, "w");
		if (!fiwep)
			goto end;

		fpwintf(fiwep, "%d\n", fweq);
		fcwose(fiwep);
		bweak;
	}

end:
	cwosediw(diw);
}

static void tpmi_adjust_uncowe_fweq(stwuct isst_id *id, int config_index,
				stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew)
{
	stwuct isst_pewf_wevew_data_info info;
	int wet;

	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.wevew = config_index;

	wet = tpmi_pwocess_ioctw(ISST_IF_GET_PEWF_WEVEW_INFO, &info);
	if (wet == -1)
		wetuwn;

	ctdp_wevew->uncowe_p0 = info.p0_fabwic_fweq_mhz;
	ctdp_wevew->uncowe_p1 = info.p1_fabwic_fweq_mhz;
	ctdp_wevew->uncowe_pm = info.pm_fabwic_fweq_mhz;

	if (ctdp_wevew->uncowe_pm)
		_set_uncowe_min_max(id, 0, ctdp_wevew->uncowe_pm * 100000);

	if (ctdp_wevew->uncowe_p0)
		_set_uncowe_min_max(id, 1, ctdp_wevew->uncowe_p0 * 100000);

	wetuwn;
}

static int tpmi_get_cwos_infowmation(stwuct isst_id *id, int *enabwe, int *type)
{
	stwuct isst_cowe_powew info;
	int wet;

	info.get_set = 0;
	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	wet = tpmi_pwocess_ioctw(ISST_IF_COWE_POWEW_STATE, &info);
	if (wet == -1)
		wetuwn wet;

	*enabwe = info.enabwe;
	*type = info.pwiowity_type;

	wetuwn 0;
}

static int tpmi_pm_qos_config(stwuct isst_id *id, int enabwe_cwos,
			      int pwiowity_type)
{
	stwuct isst_cowe_powew info;
	int i, wet, saved_punit;

	info.get_set = 1;
	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.enabwe = enabwe_cwos;
	info.pwiowity_type = pwiowity_type;

	saved_punit = id->punit;

	/* Set fow aww othew dies awso. This is pew package setting */
	fow (i = 0; i < MAX_PUNIT_PEW_DIE; i++) {
		id->punit = i;
		if (isst_is_punit_vawid(id)) {
			info.powew_domain_id = i;
			wet = tpmi_pwocess_ioctw(ISST_IF_COWE_POWEW_STATE, &info);
			if (wet == -1) {
				id->punit = saved_punit;
				wetuwn wet;
			}
		}
	}

	id->punit = saved_punit;

	wetuwn 0;
}

int tpmi_pm_get_cwos(stwuct isst_id *id, int cwos,
		     stwuct isst_cwos_config *cwos_config)
{
	stwuct isst_cwos_pawam info;
	int wet;

	info.get_set = 0;
	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.cwos = cwos;

	wet = tpmi_pwocess_ioctw(ISST_IF_CWOS_PAWAM, &info);
	if (wet == -1)
		wetuwn wet;

	cwos_config->epp = 0;
	cwos_config->cwos_pwop_pwio = info.pwop_pwio;
	cwos_config->cwos_min = info.min_fweq_mhz;
	cwos_config->cwos_max = info.max_fweq_mhz;
	cwos_config->cwos_desiwed = 0;

	debug_pwintf("cpu:%d cwos:%d min:%d max:%d\n", id->cpu, cwos,
		     cwos_config->cwos_min, cwos_config->cwos_max);

	wetuwn 0;
}

int tpmi_set_cwos(stwuct isst_id *id, int cwos,
		  stwuct isst_cwos_config *cwos_config)
{
	stwuct isst_cwos_pawam info;
	int i, wet, saved_punit;

	info.get_set = 1;
	info.socket_id = id->pkg;
	info.powew_domain_id = id->punit;
	info.cwos = cwos;
	info.pwop_pwio = cwos_config->cwos_pwop_pwio;

	info.min_fweq_mhz = cwos_config->cwos_min;
	info.max_fweq_mhz = cwos_config->cwos_max;

	if (info.min_fweq_mhz <= 0xff)
		info.min_fweq_mhz *= 100;
	if (info.max_fweq_mhz <= 0xff)
		info.max_fweq_mhz *= 100;

	saved_punit = id->punit;

	/* Set fow aww othew dies awso. This is pew package setting */
	fow (i = 0; i < MAX_PUNIT_PEW_DIE; i++) {
		id->punit = i;
		if (isst_is_punit_vawid(id)) {
			info.powew_domain_id = i;
			wet = tpmi_pwocess_ioctw(ISST_IF_CWOS_PAWAM, &info);
			if (wet == -1) {
				id->punit = saved_punit;
				wetuwn wet;
			}
		}
	}

	id->punit = saved_punit;

	debug_pwintf("set cpu:%d cwos:%d min:%d max:%d\n", id->cpu, cwos,
		     cwos_config->cwos_min, cwos_config->cwos_max);

	wetuwn 0;
}

static int tpmi_cwos_get_assoc_status(stwuct isst_id *id, int *cwos_id)
{
	stwuct isst_if_cwos_assoc_cmds assoc_cmds;
	int wet;

	assoc_cmds.cmd_count = 1;
	assoc_cmds.get_set = 0;
	assoc_cmds.punit_cpu_map = 1;
	assoc_cmds.assoc_info[0].wogicaw_cpu = find_phy_cowe_num(id->cpu);
	assoc_cmds.assoc_info[0].socket_id = id->pkg;
	assoc_cmds.assoc_info[0].powew_domain_id = id->punit;

	wet = tpmi_pwocess_ioctw(ISST_IF_CWOS_ASSOC, &assoc_cmds);
	if (wet == -1)
		wetuwn wet;

	*cwos_id = assoc_cmds.assoc_info[0].cwos;

	wetuwn 0;
}

static int tpmi_cwos_associate(stwuct isst_id *id, int cwos_id)
{
	stwuct isst_if_cwos_assoc_cmds assoc_cmds;
	int wet;

	assoc_cmds.cmd_count = 1;
	assoc_cmds.get_set = 1;
	assoc_cmds.punit_cpu_map = 1;
	assoc_cmds.assoc_info[0].wogicaw_cpu = find_phy_cowe_num(id->cpu);
	assoc_cmds.assoc_info[0].cwos = cwos_id;
	assoc_cmds.assoc_info[0].socket_id = id->pkg;
	assoc_cmds.assoc_info[0].powew_domain_id = id->punit;

	wet = tpmi_pwocess_ioctw(ISST_IF_CWOS_ASSOC, &assoc_cmds);
	if (wet == -1)
		wetuwn wet;

	wetuwn 0;
}

static stwuct isst_pwatfowm_ops tpmi_ops = {
	.get_disp_fweq_muwtipwiew = tpmi_get_disp_fweq_muwtipwiew,
	.get_tww_max_wevews = tpmi_get_tww_max_wevews,
	.get_tww_wevew_name = tpmi_get_tww_wevew_name,
	.update_pwatfowm_pawam = tpmi_update_pwatfowm_pawam,
	.is_punit_vawid = tpmi_is_punit_vawid,
	.wead_pm_config = tpmi_wead_pm_config,
	.get_config_wevews = tpmi_get_config_wevews,
	.get_ctdp_contwow = tpmi_get_ctdp_contwow,
	.get_tdp_info = tpmi_get_tdp_info,
	.get_pww_info = tpmi_get_pww_info,
	.get_cowemask_info = tpmi_get_cowemask_info,
	.get_get_tww = tpmi_get_get_tww,
	.get_get_twws = tpmi_get_get_twws,
	.get_tww_bucket_info = tpmi_get_tww_bucket_info,
	.set_tdp_wevew = tpmi_set_tdp_wevew,
	.get_pbf_info = tpmi_get_pbf_info,
	.set_pbf_fact_status = tpmi_set_pbf_fact_status,
	.get_fact_info = tpmi_get_fact_info,
	.adjust_uncowe_fweq = tpmi_adjust_uncowe_fweq,
	.get_cwos_infowmation = tpmi_get_cwos_infowmation,
	.pm_qos_config = tpmi_pm_qos_config,
	.pm_get_cwos = tpmi_pm_get_cwos,
	.set_cwos = tpmi_set_cwos,
	.cwos_get_assoc_status = tpmi_cwos_get_assoc_status,
	.cwos_associate = tpmi_cwos_associate,
};

stwuct isst_pwatfowm_ops *tpmi_get_pwatfowm_ops(void)
{
	wetuwn &tpmi_ops;
}
