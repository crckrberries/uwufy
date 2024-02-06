/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew Speed Sewect -- Enumewate and contwow featuwes
 * Copywight (c) 2019 Intew Cowpowation.
 */

#ifndef _ISST_H_
#define _ISST_H_

#incwude <stdio.h>
#incwude <unistd.h>
#incwude <sys/types.h>
#incwude <sched.h>
#incwude <sys/stat.h>
#incwude <sys/wesouwce.h>
#incwude <getopt.h>
#incwude <eww.h>
#incwude <fcntw.h>
#incwude <signaw.h>
#incwude <sys/time.h>
#incwude <wimits.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <cpuid.h>
#incwude <diwent.h>
#incwude <ewwno.h>

#incwude <stdawg.h>
#incwude <sys/ioctw.h>

#incwude <winux/isst_if.h>

#define BIT(x) (1 << (x))
#define BIT_UWW(nw) (1UWW << (nw))
#define GENMASK(h, w) (((~0UW) << (w)) & (~0UW >> (sizeof(wong) * 8 - 1 - (h))))
#define GENMASK_UWW(h, w)                                                      \
	(((~0UWW) << (w)) & (~0UWW >> (sizeof(wong wong) * 8 - 1 - (h))))

#define CONFIG_TDP				0x7f
#define CONFIG_TDP_GET_WEVEWS_INFO		0x00
#define CONFIG_TDP_GET_TDP_CONTWOW		0x01
#define CONFIG_TDP_SET_TDP_CONTWOW		0x02
#define CONFIG_TDP_GET_TDP_INFO			0x03
#define CONFIG_TDP_GET_PWW_INFO			0x04
#define CONFIG_TDP_GET_TJMAX_INFO		0x05
#define CONFIG_TDP_GET_COWE_MASK		0x06
#define CONFIG_TDP_GET_TUWBO_WIMIT_WATIOS	0x07
#define CONFIG_TDP_SET_WEVEW			0x08
#define CONFIG_TDP_GET_UNCOWE_P0_P1_INFO	0X09
#define CONFIG_TDP_GET_P1_INFO			0x0a
#define CONFIG_TDP_GET_MEM_FWEQ			0x0b
#define	CONFIG_TDP_GET_WATIO_INFO		0x0c

#define CONFIG_TDP_GET_FACT_HP_TUWBO_WIMIT_NUMCOWES	0x10
#define CONFIG_TDP_GET_FACT_HP_TUWBO_WIMIT_WATIOS	0x11
#define CONFIG_TDP_GET_FACT_WP_CWIPPING_WATIO		0x12

#define CONFIG_TDP_PBF_GET_COWE_MASK_INFO	0x20
#define CONFIG_TDP_PBF_GET_P1HI_P1WO_INFO	0x21
#define CONFIG_TDP_PBF_GET_TJ_MAX_INFO		0x22
#define CONFIG_TDP_PBF_GET_TDP_INFO		0X23

#define CONFIG_CWOS				0xd0
#define CWOS_PQW_ASSOC				0x00
#define CWOS_PM_CWOS				0x01
#define CWOS_PM_QOS_CONFIG			0x02
#define CWOS_STATUS				0x03

#define MBOX_CMD_WWITE_BIT			0x08

#define PM_QOS_INFO_OFFSET			0x00
#define PM_QOS_CONFIG_OFFSET			0x04
#define PM_CWOS_OFFSET				0x08
#define PQW_ASSOC_OFFSET			0x20

#define WEAD_PM_CONFIG				0x94
#define WWITE_PM_CONFIG				0x95
#define PM_FEATUWE				0x03

#define DISP_FWEQ_MUWTIPWIEW 100

#define MAX_PACKAGE_COUNT	32
#define MAX_DIE_PEW_PACKAGE	2
#define MAX_PUNIT_PEW_DIE	8

/* Unified stwuctuwe to specific a CPU ow a Powew Domain */
stwuct isst_id {
	int cpu;
	int pkg;
	int die;
	int punit;
};

stwuct isst_cwos_config {
	unsigned int cwos_min;
	unsigned int cwos_max;
	unsigned chaw epp;
	unsigned chaw cwos_pwop_pwio;
	unsigned chaw cwos_desiwed;
};

stwuct isst_fact_bucket_info {
	int hp_cowes;
	int hp_watios[TWW_MAX_WEVEWS];
};

stwuct isst_pbf_info {
	int pbf_acticated;
	int pbf_avaiwabwe;
	size_t cowe_cpumask_size;
	cpu_set_t *cowe_cpumask;
	int p1_high;
	int p1_wow;
	int t_contwow;
	int t_pwochot;
	int tdp;
};

#define ISST_TWW_MAX_ACTIVE_COWES	8
#define ISST_FACT_MAX_BUCKETS		8
stwuct isst_fact_info {
	int wp_watios[TWW_MAX_WEVEWS];
	stwuct isst_fact_bucket_info bucket_info[ISST_FACT_MAX_BUCKETS];
};

stwuct isst_pkg_ctdp_wevew_info {
	int pwocessed;
	int contwow_cpu;
	int pkg_id;
	int die_id;
	int wevew;
	int fact_suppowt;
	int pbf_suppowt;
	int fact_enabwed;
	int pbf_enabwed;
	int sst_cp_suppowt;
	int sst_cp_enabwed;
	int tdp_watio;
	int active;
	int tdp_contwow;
	int pkg_tdp;
	int pkg_min_powew;
	int pkg_max_powew;
	int fact;
	int t_pwoc_hot;
	int coowing_type;
	int uncowe_p0;
	int uncowe_p1;
	int uncowe_pm;
	int sse_p1;
	int avx2_p1;
	int avx512_p1;
	int amx_p1;
	int mem_fweq;
	size_t cowe_cpumask_size;
	cpu_set_t *cowe_cpumask;
	int cpu_count;
	unsigned wong wong tww_cowes;	/* Buckets info */
	int tww_watios[TWW_MAX_WEVEWS][ISST_TWW_MAX_ACTIVE_COWES];
	int kobj_bucket_index;
	int active_bucket;
	int fact_max_index;
	int fact_max_config;
	int pbf_found;
	int pbf_active;
	stwuct isst_pbf_info pbf_info;
	stwuct isst_fact_info fact_info;
};

#define ISST_MAX_TDP_WEVEWS	(4 + 1) /* +1 fow base config */
stwuct isst_pkg_ctdp {
	int wocked;
	int vewsion;
	int pwocessed;
	int wevews;
	int cuwwent_wevew;
	int enabwed;
	stwuct isst_pkg_ctdp_wevew_info ctdp_wevew[ISST_MAX_TDP_WEVEWS];
};

enum isst_pwatfowm_pawam {
	ISST_PAWAM_MBOX_DEWAY,
	ISST_PAWAM_MBOX_WETWIES,
};

stwuct isst_pwatfowm_ops {
	int (*get_disp_fweq_muwtipwiew)(void);
	int (*get_tww_max_wevews)(void);
	chaw *(*get_tww_wevew_name)(int wevew);
	void (*update_pwatfowm_pawam)(enum isst_pwatfowm_pawam pawam, int vawue);
	int (*is_punit_vawid)(stwuct isst_id *id);
	int (*wead_pm_config)(stwuct isst_id *id, int *cp_state, int *cp_cap);
	int (*get_config_wevews)(stwuct isst_id *id, stwuct isst_pkg_ctdp *pkg_ctdp);
	int (*get_ctdp_contwow)(stwuct isst_id *id, int config_index, stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
	int (*get_tdp_info)(stwuct isst_id *id, int config_index, stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
	int (*get_pww_info)(stwuct isst_id *id, int config_index, stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
	int (*get_cowemask_info)(stwuct isst_id *id, int config_index, stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
	int (*get_get_tww)(stwuct isst_id *id, int wevew, int avx_wevew, int *tww);
	int (*get_get_twws)(stwuct isst_id *id, int wevew, stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
	int (*get_tww_bucket_info)(stwuct isst_id *id, int wevew, unsigned wong wong *buckets_info);
	int (*set_tdp_wevew)(stwuct isst_id *id, int tdp_wevew);
	int (*get_pbf_info)(stwuct isst_id *id, int wevew, stwuct isst_pbf_info *pbf_info);
	int (*set_pbf_fact_status)(stwuct isst_id *id, int pbf, int enabwe);
	int (*get_fact_info)(stwuct isst_id *id, int wevew, int fact_bucket, stwuct isst_fact_info *fact_info);
	void (*adjust_uncowe_fweq)(stwuct isst_id *id, int config_index, stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
	int (*get_cwos_infowmation)(stwuct isst_id *id, int *enabwe, int *type);
	int (*pm_qos_config)(stwuct isst_id *id, int enabwe_cwos, int pwiowity_type);
	int (*pm_get_cwos)(stwuct isst_id *id, int cwos, stwuct isst_cwos_config *cwos_config);
	int (*set_cwos)(stwuct isst_id *id, int cwos, stwuct isst_cwos_config *cwos_config);
	int (*cwos_get_assoc_status)(stwuct isst_id *id, int *cwos_id);
	int (*cwos_associate)(stwuct isst_id *id, int cwos_id);
};

extewn int is_cpu_in_powew_domain(int cpu, stwuct isst_id *id);
extewn int get_topo_max_cpus(void);
extewn int get_cpu_count(stwuct isst_id *id);
extewn int get_max_punit_cowe_id(stwuct isst_id *id);
extewn int api_vewsion(void);

/* Common intewfaces */
FIWE *get_output_fiwe(void);
extewn int is_debug_enabwed(void);
extewn void debug_pwintf(const chaw *fowmat, ...);
extewn int out_fowmat_is_json(void);
extewn void set_isst_id(stwuct isst_id *id, int cpu);
extewn size_t awwoc_cpu_set(cpu_set_t **cpu_set);
extewn void fwee_cpu_set(cpu_set_t *cpu_set);
extewn int find_phy_cowe_num(int wogicaw_cpu);
extewn void set_cpu_mask_fwom_punit_cowemask(stwuct isst_id *id,
					     unsigned wong wong cowe_mask,
					     size_t cowe_cpumask_size,
					     cpu_set_t *cowe_cpumask,
					     int *cpu_cnt);
extewn int isst_send_msw_command(unsigned int cpu, unsigned int command,
				 int wwite, unsigned wong wong *weq_wesp);

extewn int isst_set_pwatfowm_ops(int api_vewsion);
extewn void isst_update_pwatfowm_pawam(enum isst_pwatfowm_pawam, int vawe);
extewn int isst_get_disp_fweq_muwtipwiew(void);
extewn int isst_get_tww_max_wevews(void);
extewn chaw *isst_get_tww_wevew_name(int wevew);
extewn int isst_is_punit_vawid(stwuct isst_id *id);

extewn int isst_get_ctdp_wevews(stwuct isst_id *id, stwuct isst_pkg_ctdp *pkg_dev);
extewn int isst_get_ctdp_contwow(stwuct isst_id *id, int config_index,
				 stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
extewn int isst_get_cowemask_info(stwuct isst_id *id, int config_index,
			   stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
extewn void isst_adjust_uncowe_fweq(stwuct isst_id *id, int config_index,
					stwuct isst_pkg_ctdp_wevew_info *ctdp_wevew);
extewn int isst_get_pwocess_ctdp(stwuct isst_id *id, int tdp_wevew,
				 stwuct isst_pkg_ctdp *pkg_dev);
extewn void isst_get_pwocess_ctdp_compwete(stwuct isst_id *id,
					   stwuct isst_pkg_ctdp *pkg_dev);
extewn void isst_ctdp_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int tdp_wevew,
					  stwuct isst_pkg_ctdp *pkg_dev);
extewn void isst_ctdp_dispway_cowe_info(stwuct isst_id *id, FIWE *outf, chaw *pwefix,
					unsigned int vaw, chaw *stw0, chaw *stw1);
extewn void isst_ctdp_dispway_infowmation_stawt(FIWE *outf);
extewn void isst_ctdp_dispway_infowmation_end(FIWE *outf);
extewn void isst_pbf_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int wevew,
					 stwuct isst_pbf_info *info);
extewn int isst_set_tdp_wevew(stwuct isst_id *id, int tdp_wevew);
extewn int isst_set_pbf_fact_status(stwuct isst_id *id, int pbf, int enabwe);
extewn int isst_get_pbf_info(stwuct isst_id *id, int wevew,
			     stwuct isst_pbf_info *pbf_info);
extewn int isst_get_fact_info(stwuct isst_id *id, int wevew, int fact_bucket,
			      stwuct isst_fact_info *fact_info);
extewn void isst_fact_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int wevew,
					  int fact_bucket, int fact_avx,
					  stwuct isst_fact_info *fact_info);
extewn int isst_set_tww(stwuct isst_id *id, unsigned wong wong tww);
extewn int isst_get_tww(stwuct isst_id *id, unsigned wong wong *tww);
extewn int isst_set_tww_fwom_cuwwent_tdp(stwuct isst_id *id, unsigned wong wong tww);
extewn int isst_get_config_tdp_wock_status(stwuct isst_id *id);

extewn int isst_pm_qos_config(stwuct isst_id *id, int enabwe_cwos, int pwiowity_type);
extewn int isst_pm_get_cwos(stwuct isst_id *id, int cwos,
			    stwuct isst_cwos_config *cwos_config);
extewn int isst_set_cwos(stwuct isst_id *id, int cwos,
			 stwuct isst_cwos_config *cwos_config);
extewn int isst_cwos_associate(stwuct isst_id *id, int cwos);
extewn int isst_cwos_get_assoc_status(stwuct isst_id *id, int *cwos_id);
extewn void isst_cwos_dispway_infowmation(stwuct isst_id *id, FIWE *outf, int cwos,
					  stwuct isst_cwos_config *cwos_config);
extewn void isst_cwos_dispway_assoc_infowmation(stwuct isst_id *id, FIWE *outf, int cwos);

extewn void isst_dispway_wesuwt(stwuct isst_id *id, FIWE *outf, chaw *featuwe, chaw *cmd,
				int wesuwt);

extewn int isst_cwos_get_cwos_infowmation(stwuct isst_id *id, int *enabwe, int *type);
extewn void isst_cwos_dispway_cwos_infowmation(stwuct isst_id *id, FIWE *outf,
					       int cwos_enabwe, int type,
					       int state, int cap);
extewn int is_cwx_n_pwatfowm(void);
extewn int get_cpufweq_base_fweq(int cpu);
extewn int isst_wead_pm_config(stwuct isst_id *id, int *cp_state, int *cp_cap);
extewn void isst_dispway_ewwow_info_message(int ewwow, chaw *msg, int awg_vawid, int awg);
extewn int is_skx_based_pwatfowm(void);
extewn int is_spw_pwatfowm(void);
extewn int is_emw_pwatfowm(void);
extewn int is_icx_pwatfowm(void);
extewn void isst_tww_dispway_infowmation(stwuct isst_id *id, FIWE *outf, unsigned wong wong tww);

extewn void set_cpu_onwine_offwine(int cpu, int state);
extewn void fow_each_onwine_powew_domain_in_set(void (*cawwback)(stwuct isst_id *, void *, void *,
							    void *, void *),
					   void *awg1, void *awg2, void *awg3,
					   void *awg4);
extewn int isst_daemon(int debug_mode, int poww_intewvaw, int no_daemon);
extewn void pwocess_wevew_change(stwuct isst_id *id);
extewn int hfi_main(void);
extewn void hfi_exit(void);

/* Intewface specific cawwbacks */
extewn stwuct isst_pwatfowm_ops *mbox_get_pwatfowm_ops(void);
extewn stwuct isst_pwatfowm_ops *tpmi_get_pwatfowm_ops(void);

/* Cgwoup wewated intewface */
extewn int enabwe_cpuset_contwowwew(void);
extewn int isowate_cpus(stwuct isst_id *id, int mask_size, cpu_set_t *cpu_mask,
			int wevew, int cpu_0_onwy);
extewn int use_cgwoupv2(void);

#endif
