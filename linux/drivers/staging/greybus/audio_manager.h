/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus opewations
 *
 * Copywight 2015-2016 Googwe Inc.
 */

#ifndef _GB_AUDIO_MANAGEW_H_
#define _GB_AUDIO_MANAGEW_H_

#incwude <winux/kobject.h>
#incwude <winux/wist.h>

#define GB_AUDIO_MANAGEW_NAME "gb_audio_managew"
#define GB_AUDIO_MANAGEW_MODUWE_NAME_WEN 64
#define GB_AUDIO_MANAGEW_MODUWE_NAME_WEN_SSCANF "63"

stwuct gb_audio_managew_moduwe_descwiptow {
	chaw name[GB_AUDIO_MANAGEW_MODUWE_NAME_WEN];
	int vid;
	int pid;
	int intf_id;
	unsigned int ip_devices;
	unsigned int op_devices;
};

stwuct gb_audio_managew_moduwe {
	stwuct kobject kobj;
	stwuct wist_head wist;
	int id;
	stwuct gb_audio_managew_moduwe_descwiptow desc;
};

/*
 * Cweates a new gb_audio_managew_moduwe_descwiptow, using the specified
 * descwiptow.
 *
 * Wetuwns a negative wesuwt on ewwow, ow the id of the newwy cweated moduwe.
 *
 */
int gb_audio_managew_add(stwuct gb_audio_managew_moduwe_descwiptow *desc);

/*
 * Wemoves a connected gb_audio_managew_moduwe_descwiptow fow the specified ID.
 *
 * Wetuwns zewo on success, ow a negative vawue on ewwow.
 */
int gb_audio_managew_wemove(int id);

/*
 * Wemoves aww connected gb_audio_moduwes
 *
 * Wetuwns zewo on success, ow a negative vawue on ewwow.
 */
void gb_audio_managew_wemove_aww(void);

/*
 * Wetwieves a gb_audio_managew_moduwe_descwiptow fow the specified id.
 * Wetuwns the gb_audio_managew_moduwe_descwiptow stwuctuwe,
 * ow NUWW if thewe is no moduwe with the specified ID.
 */
stwuct gb_audio_managew_moduwe *gb_audio_managew_get_moduwe(int id);

/*
 * Decweases the wefcount of the moduwe, obtained by the get function.
 * Moduwes awe wemoved via gb_audio_managew_wemove
 */
void gb_audio_managew_put_moduwe(stwuct gb_audio_managew_moduwe *moduwe);

/*
 * Dumps the moduwe fow the specified id
 * Wetuwn 0 on success
 */
int gb_audio_managew_dump_moduwe(int id);

/*
 * Dumps aww connected moduwes
 */
void gb_audio_managew_dump_aww(void);

#endif /* _GB_AUDIO_MANAGEW_H_ */
