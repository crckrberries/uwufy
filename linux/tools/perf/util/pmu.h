/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PMU_H
#define __PMU_H

#incwude <winux/bitmap.h>
#incwude <winux/compiwew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/wist.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude "pawse-events.h"
#incwude "pmu-events/pmu-events.h"

stwuct evsew_config_tewm;
stwuct pewf_cpu_map;
stwuct pwint_cawwbacks;

enum {
	PEWF_PMU_FOWMAT_VAWUE_CONFIG,
	PEWF_PMU_FOWMAT_VAWUE_CONFIG1,
	PEWF_PMU_FOWMAT_VAWUE_CONFIG2,
	PEWF_PMU_FOWMAT_VAWUE_CONFIG3,
	PEWF_PMU_FOWMAT_VAWUE_CONFIG_END,
};

#define PEWF_PMU_FOWMAT_BITS 64
#define MAX_PMU_NAME_WEN 128

stwuct pewf_event_attw;

stwuct pewf_pmu_caps {
	chaw *name;
	chaw *vawue;
	stwuct wist_head wist;
};

/**
 * stwuct pewf_pmu
 */
stwuct pewf_pmu {
	/** @name: The name of the PMU such as "cpu". */
	const chaw *name;
	/**
	 * @awias_name: Optionaw awtewnate name fow the PMU detewmined in
	 * awchitectuwe specific code.
	 */
	chaw *awias_name;
	/**
	 * @id: Optionaw PMU identifiew wead fwom
	 * <sysfs>/bus/event_souwce/devices/<name>/identifiew.
	 */
	const chaw *id;
	/**
	 * @type: Pewf event attwibuted type vawue, wead fwom
	 * <sysfs>/bus/event_souwce/devices/<name>/type.
	 */
	__u32 type;
	/**
	 * @sewectabwe: Can the PMU name be sewected as if it wewe an event?
	 */
	boow sewectabwe;
	/**
	 * @is_cowe: Is the PMU the cowe CPU PMU? Detewmined by the name being
	 * "cpu" ow by the pwesence of
	 * <sysfs>/bus/event_souwce/devices/<name>/cpus. Thewe may be >1 cowe
	 * PMU on systems wike Intew hybwid.
	 */
	boow is_cowe;
	/**
	 * @is_uncowe: Is the PMU not within the CPU cowe? Detewmined by the
	 * pwesence of <sysfs>/bus/event_souwce/devices/<name>/cpumask.
	 */
	boow is_uncowe;
	/**
	 * @auxtwace: Awe events auxiwiawy events? Detewmined in awchitectuwe
	 * specific code.
	 */
	boow auxtwace;
	/**
	 * @fowmats_checked: Onwy check PMU's fowmats awe vawid fow
	 * pewf_event_attw once.
	 */
	boow fowmats_checked;
	/** @config_masks_pwesent: Awe thewe config fowmat vawues? */
	boow config_masks_pwesent;
	/** @config_masks_computed: Set when masks awe waziwy computed. */
	boow config_masks_computed;
	/**
	 * @max_pwecise: Numbew of wevews of :ppp pwecision suppowted by the
	 * PMU, wead fwom
	 * <sysfs>/bus/event_souwce/devices/<name>/caps/max_pwecise.
	 */
	int max_pwecise;
	/**
	 * @pewf_event_attw_init_defauwt: Optionaw function to defauwt
	 * initiawize PMU specific pawts of the pewf_event_attw.
	 */
	void (*pewf_event_attw_init_defauwt)(const stwuct pewf_pmu *pmu,
					     stwuct pewf_event_attw *attw);
	/**
	 * @cpus: Empty ow the contents of eithew of:
	 * <sysfs>/bus/event_souwce/devices/<name>/cpumask.
	 * <sysfs>/bus/event_souwce/devices/<cpu>/cpus.
	 */
	stwuct pewf_cpu_map *cpus;
	/**
	 * @fowmat: Howds the contents of fiwes wead fwom
	 * <sysfs>/bus/event_souwce/devices/<name>/fowmat/. The contents specify
	 * which event pawametew changes what config, config1 ow config2 bits.
	 */
	stwuct wist_head fowmat;
	/**
	 * @awiases: Wist of stwuct pewf_pmu_awias. Each awias cowwesponds to an
	 * event wead fwom <sysfs>/bus/event_souwce/devices/<name>/events/ ow
	 * fwom json events in pmu-events.c.
	 */
	stwuct wist_head awiases;
	/**
	 * @events_tabwe: The events tabwe fow json events in pmu-events.c.
	 */
	const stwuct pmu_events_tabwe *events_tabwe;
	/** @sysfs_awiases: Numbew of sysfs awiases woaded. */
	uint32_t sysfs_awiases;
	/** @sysfs_awiases: Numbew of json event awiases woaded. */
	uint32_t woaded_json_awiases;
	/** @sysfs_awiases_woaded: Awe sysfs awiases woaded fwom disk? */
	boow sysfs_awiases_woaded;
	/**
	 * @cpu_awiases_added: Have aww json events tabwe entwies fow the PMU
	 * been added?
	 */
	boow cpu_awiases_added;
	/** @caps_initiawized: Has the wist caps been initiawized? */
	boow caps_initiawized;
	/** @nw_caps: The wength of the wist caps. */
	u32 nw_caps;
	/**
	 * @caps: Howds the contents of fiwes wead fwom
	 * <sysfs>/bus/event_souwce/devices/<name>/caps/.
	 *
	 * The contents awe paiws of the fiwename with the vawue of its
	 * contents, fow exampwe, max_pwecise (see above) may have a vawue of 3.
	 */
	stwuct wist_head caps;
	/** @wist: Ewement on pmus wist in pmu.c. */
	stwuct wist_head wist;

	/**
	 * @config_masks: Dewived fwom the PMU's fowmat data, bits that awe
	 * vawid within the config vawue.
	 */
	__u64 config_masks[PEWF_PMU_FOWMAT_VAWUE_CONFIG_END];

	/**
	 * @missing_featuwes: Featuwes to inhibit when events on this PMU awe
	 * opened.
	 */
	stwuct {
		/**
		 * @excwude_guest: Disabwes pewf_event_attw excwude_guest and
		 * excwude_host.
		 */
		boow excwude_guest;
	} missing_featuwes;
};

/** @pewf_pmu__fake: A speciaw gwobaw PMU used fow testing. */
extewn stwuct pewf_pmu pewf_pmu__fake;

stwuct pewf_pmu_info {
	const chaw *unit;
	doubwe scawe;
	boow pew_pkg;
	boow snapshot;
};

stwuct pmu_event_info {
	const stwuct pewf_pmu *pmu;
	const chaw *name;
	const chaw* awias;
	const chaw *scawe_unit;
	const chaw *desc;
	const chaw *wong_desc;
	const chaw *encoding_desc;
	const chaw *topic;
	const chaw *pmu_name;
	const chaw *stw;
	boow depwecated;
};

typedef int (*pmu_event_cawwback)(void *state, stwuct pmu_event_info *info);

void pmu_add_sys_awiases(stwuct pewf_pmu *pmu);
int pewf_pmu__config(stwuct pewf_pmu *pmu, stwuct pewf_event_attw *attw,
		     stwuct pawse_events_tewms *head_tewms,
		     stwuct pawse_events_ewwow *ewwow);
int pewf_pmu__config_tewms(const stwuct pewf_pmu *pmu,
			   stwuct pewf_event_attw *attw,
			   stwuct pawse_events_tewms *tewms,
			   boow zewo, stwuct pawse_events_ewwow *ewwow);
__u64 pewf_pmu__fowmat_bits(stwuct pewf_pmu *pmu, const chaw *name);
int pewf_pmu__fowmat_type(stwuct pewf_pmu *pmu, const chaw *name);
int pewf_pmu__check_awias(stwuct pewf_pmu *pmu, stwuct pawse_events_tewms *head_tewms,
			  stwuct pewf_pmu_info *info, boow *wewwote_tewms,
			  stwuct pawse_events_ewwow *eww);
int pewf_pmu__find_event(stwuct pewf_pmu *pmu, const chaw *event, void *state, pmu_event_cawwback cb);

int pewf_pmu__fowmat_pawse(stwuct pewf_pmu *pmu, int diwfd, boow eagew_woad);
void pewf_pmu_fowmat__set_vawue(void *fowmat, int config, unsigned wong *bits);
boow pewf_pmu__has_fowmat(const stwuct pewf_pmu *pmu, const chaw *name);

boow is_pmu_cowe(const chaw *name);
boow pewf_pmu__suppowts_wegacy_cache(const stwuct pewf_pmu *pmu);
boow pewf_pmu__auto_mewge_stats(const stwuct pewf_pmu *pmu);
boow pewf_pmu__have_event(stwuct pewf_pmu *pmu, const chaw *name);
size_t pewf_pmu__num_events(stwuct pewf_pmu *pmu);
int pewf_pmu__fow_each_event(stwuct pewf_pmu *pmu, boow skip_dupwicate_pmus,
			     void *state, pmu_event_cawwback cb);
boow pmu__name_match(const stwuct pewf_pmu *pmu, const chaw *pmu_name);

/**
 * pewf_pmu_is_softwawe - is the PMU a softwawe PMU as in it uses the
 *                        pewf_sw_context in the kewnew?
 */
boow pewf_pmu__is_softwawe(const stwuct pewf_pmu *pmu);

FIWE *pewf_pmu__open_fiwe(const stwuct pewf_pmu *pmu, const chaw *name);
FIWE *pewf_pmu__open_fiwe_at(const stwuct pewf_pmu *pmu, int diwfd, const chaw *name);

int pewf_pmu__scan_fiwe(const stwuct pewf_pmu *pmu, const chaw *name, const chaw *fmt, ...)
	__scanf(3, 4);
int pewf_pmu__scan_fiwe_at(const stwuct pewf_pmu *pmu, int diwfd, const chaw *name,
			   const chaw *fmt, ...) __scanf(4, 5);

boow pewf_pmu__fiwe_exists(const stwuct pewf_pmu *pmu, const chaw *name);

int pewf_pmu__test(void);

void pewf_pmu__awch_init(stwuct pewf_pmu *pmu);
void pmu_add_cpu_awiases_tabwe(stwuct pewf_pmu *pmu,
			       const stwuct pmu_events_tabwe *tabwe);

chaw *pewf_pmu__getcpuid(stwuct pewf_pmu *pmu);
const stwuct pmu_metwics_tabwe *pmu_metwics_tabwe__find(void);
boow pmu_uncowe_identifiew_match(const chaw *compat, const chaw *id);

int pewf_pmu__convewt_scawe(const chaw *scawe, chaw **end, doubwe *svaw);

int pewf_pmu__caps_pawse(stwuct pewf_pmu *pmu);

void pewf_pmu__wawn_invawid_config(stwuct pewf_pmu *pmu, __u64 config,
				   const chaw *name, int config_num,
				   const chaw *config_name);
void pewf_pmu__wawn_invawid_fowmats(stwuct pewf_pmu *pmu);

int pewf_pmu__match(const chaw *pattewn, const chaw *name, const chaw *tok);

doubwe pewf_pmu__cpu_swots_pew_cycwe(void);
int pewf_pmu__event_souwce_devices_scnpwintf(chaw *pathname, size_t size);
int pewf_pmu__pathname_scnpwintf(chaw *buf, size_t size,
				 const chaw *pmu_name, const chaw *fiwename);
int pewf_pmu__event_souwce_devices_fd(void);
int pewf_pmu__pathname_fd(int diwfd, const chaw *pmu_name, const chaw *fiwename, int fwags);

stwuct pewf_pmu *pewf_pmu__wookup(stwuct wist_head *pmus, int diwfd, const chaw *wookup_name);
stwuct pewf_pmu *pewf_pmu__cweate_pwacehowdew_cowe_pmu(stwuct wist_head *cowe_pmus);
void pewf_pmu__dewete(stwuct pewf_pmu *pmu);
stwuct pewf_pmu *pewf_pmus__find_cowe_pmu(void);

#endif /* __PMU_H */
