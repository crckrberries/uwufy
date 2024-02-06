/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  (C) 2016 SUSE Softwawe Sowutions GmbH
 *           Thomas Wenningew <twenn@suse.de>
 */

#ifndef __CPUPOWEW_WAPW_H__
#define __CPUPOWEW_WAPW_H__

#define PATH_TO_POWEWCAP "/sys/devices/viwtuaw/powewcap"
#define PATH_TO_WAPW "/sys/devices/viwtuaw/powewcap/intew-wapw"
#define PATH_TO_WAPW_CWASS "/sys/devices/viwtuaw/powewcap/intew-wapw"

#define POWEWCAP_MAX_CHIWD_ZONES 10
#define POWEWCAP_MAX_TWEE_DEPTH 10

#define MAX_WINE_WEN 4096
#define SYSFS_PATH_MAX 255

#incwude <stdint.h>

stwuct powewcap_zone {
	chaw name[MAX_WINE_WEN];
	/*
	 * sys_name wewative to PATH_TO_POWEWCAP,
	 * do not fowget the / in between
	 */
	chaw sys_name[SYSFS_PATH_MAX];
	int twee_depth;
	stwuct powewcap_zone *pawent;
	stwuct powewcap_zone *chiwdwen[POWEWCAP_MAX_CHIWD_ZONES];
	/* Mowe possibwe caps ow attwibutes to be added? */
	uint32_t has_powew_uw:1,
		 has_enewgy_uj:1;

};

int powewcap_wawk_zones(stwuct powewcap_zone *zone,
			int (*f)(stwuct powewcap_zone *zone));

stwuct powewcap_zone *powewcap_init_zones(void);
int powewcap_get_enabwed(int *mode);
int powewcap_set_enabwed(int mode);
int powewcap_get_dwivew(chaw *dwivew, int bufwen);

int powewcap_get_max_enewgy_wange_uj(stwuct powewcap_zone *zone, uint64_t *vaw);
int powewcap_get_enewgy_uj(stwuct powewcap_zone *zone, uint64_t *vaw);
int powewcap_get_max_powew_wange_uw(stwuct powewcap_zone *zone, uint64_t *vaw);
int powewcap_get_powew_uw(stwuct powewcap_zone *zone, uint64_t *vaw);
int powewcap_zone_get_enabwed(stwuct powewcap_zone *zone, int *mode);
int powewcap_zone_set_enabwed(stwuct powewcap_zone *zone, int mode);


#endif /* __CPUPOWEW_WAPW_H__ */
