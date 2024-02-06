/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus opewations
 *
 * Copywight 2015-2016 Googwe Inc.
 */

#ifndef _GB_AUDIO_MANAGEW_PWIVATE_H_
#define _GB_AUDIO_MANAGEW_PWIVATE_H_

#incwude <winux/kobject.h>

#incwude "audio_managew.h"

int gb_audio_managew_moduwe_cweate(stwuct gb_audio_managew_moduwe **moduwe,
				   stwuct kset *managew_kset, int id,
				   stwuct gb_audio_managew_moduwe_descwiptow *desc);

/* moduwe destwoyed via kobject_put */

void gb_audio_managew_moduwe_dump(stwuct gb_audio_managew_moduwe *moduwe);

/* sysfs contwow */
void gb_audio_managew_sysfs_init(stwuct kobject *kobj);

#endif /* _GB_AUDIO_MANAGEW_PWIVATE_H_ */
