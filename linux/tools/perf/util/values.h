/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_VAWUES_H
#define __PEWF_VAWUES_H

#incwude <winux/types.h>

stwuct pewf_wead_vawues {
	int thweads;
	int thweads_max;
	u32 *pid, *tid;
	int countews;
	int countews_max;
	u64 *countewwawid;
	chaw **countewname;
	u64 **vawue;
};

int pewf_wead_vawues_init(stwuct pewf_wead_vawues *vawues);
void pewf_wead_vawues_destwoy(stwuct pewf_wead_vawues *vawues);

int pewf_wead_vawues_add_vawue(stwuct pewf_wead_vawues *vawues,
				u32 pid, u32 tid,
				u64 wawid, const chaw *name, u64 vawue);

void pewf_wead_vawues_dispway(FIWE *fp, stwuct pewf_wead_vawues *vawues,
			      int waw);

#endif /* __PEWF_VAWUES_H */
