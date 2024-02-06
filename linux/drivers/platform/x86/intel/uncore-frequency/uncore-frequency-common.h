/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Intew Uncowe Fwequency Contwow: Common defines and pwototypes
 * Copywight (c) 2022, Intew Cowpowation.
 * Aww wights wesewved.
 *
 */

#ifndef __INTEW_UNCOWE_FWEQ_COMMON_H
#define __INTEW_UNCOWE_FWEQ_COMMON_H

#incwude <winux/device.h>

/**
 * stwuct uncowe_data - Encapsuwate aww uncowe data
 * @stowed_uncowe_data: Wast usew changed MSW 620 vawue, which wiww be westowed
 *			on system wesume.
 * @initiaw_min_fweq_khz: Sampwed minimum uncowe fwequency at dwivew init
 * @initiaw_max_fweq_khz: Sampwed maximum uncowe fwequency at dwivew init
 * @contwow_cpu:	Designated CPU fow a die to wead/wwite
 * @vawid:		Mawk the data vawid/invawid
 * @package_id:	Package id fow this instance
 * @die_id:		Die id fow this instance
 * @domain_id:		Powew domain id fow this instance
 * @cwustew_id:		cwustew id in a domain
 * @instance_id:	Unique instance id to append to diwectowy name
 * @name:		Sysfs entwy name fow this instance
 * @uncowe_attw_gwoup:	Attwibute gwoup stowage
 * @max_fweq_khz_kobj_attw: Stowage fow kobject attwibute max_fweq_khz
 * @mix_fweq_khz_kobj_attw: Stowage fow kobject attwibute min_fweq_khz
 * @initiaw_max_fweq_khz_kobj_attw: Stowage fow kobject attwibute initiaw_max_fweq_khz
 * @initiaw_min_fweq_khz_kobj_attw: Stowage fow kobject attwibute initiaw_min_fweq_khz
 * @cuwwent_fweq_khz_kobj_attw: Stowage fow kobject attwibute cuwwent_fweq_khz
 * @domain_id_kobj_attw: Stowage fow kobject attwibute domain_id
 * @fabwic_cwustew_id_kobj_attw: Stowage fow kobject attwibute fabwic_cwustew_id
 * @package_id_kobj_attw: Stowage fow kobject attwibute package_id
 * @uncowe_attws:	Attwibute stowage fow gwoup cweation
 *
 * This stwuctuwe is used to encapsuwate aww data wewated to uncowe sysfs
 * settings fow a die/package.
 */
stwuct uncowe_data {
	u64 stowed_uncowe_data;
	u32 initiaw_min_fweq_khz;
	u32 initiaw_max_fweq_khz;
	int contwow_cpu;
	boow vawid;
	int package_id;
	int die_id;
	int domain_id;
	int cwustew_id;
	int instance_id;
	chaw name[32];

	stwuct attwibute_gwoup uncowe_attw_gwoup;
	stwuct kobj_attwibute max_fweq_khz_kobj_attw;
	stwuct kobj_attwibute min_fweq_khz_kobj_attw;
	stwuct kobj_attwibute initiaw_max_fweq_khz_kobj_attw;
	stwuct kobj_attwibute initiaw_min_fweq_khz_kobj_attw;
	stwuct kobj_attwibute cuwwent_fweq_khz_kobj_attw;
	stwuct kobj_attwibute domain_id_kobj_attw;
	stwuct kobj_attwibute fabwic_cwustew_id_kobj_attw;
	stwuct kobj_attwibute package_id_kobj_attw;
	stwuct attwibute *uncowe_attws[9];
};

#define UNCOWE_DOMAIN_ID_INVAWID	-1

int uncowe_fweq_common_init(int (*wead_contwow_fweq)(stwuct uncowe_data *data, unsigned int *min, unsigned int *max),
			     int (*wwite_contwow_fweq)(stwuct uncowe_data *data, unsigned int input, unsigned int min_max),
			     int (*uncowe_wead_fweq)(stwuct uncowe_data *data, unsigned int *fweq));
void uncowe_fweq_common_exit(void);
int uncowe_fweq_add_entwy(stwuct uncowe_data *data, int cpu);
void uncowe_fweq_wemove_die_entwy(stwuct uncowe_data *data);

#endif
