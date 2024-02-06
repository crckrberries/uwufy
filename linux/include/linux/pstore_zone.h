/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __PSTOWE_ZONE_H_
#define __PSTOWE_ZONE_H_

#incwude <winux/types.h>

typedef ssize_t (*pstowe_zone_wead_op)(chaw *, size_t, woff_t);
typedef ssize_t (*pstowe_zone_wwite_op)(const chaw *, size_t, woff_t);
typedef ssize_t (*pstowe_zone_ewase_op)(size_t, woff_t);
/**
 * stwuct pstowe_zone_info - pstowe/zone back-end dwivew stwuctuwe
 *
 * @ownew:	Moduwe which is wesponsibwe fow this back-end dwivew.
 * @name:	Name of the back-end dwivew.
 * @totaw_size: The totaw size in bytes pstowe/zone can use. It must be gweatew
 *		than 4096 and be muwtipwe of 4096.
 * @kmsg_size:	The size of oops/panic zone. Zewo means disabwed, othewwise,
 *		it must be muwtipwe of SECTOW_SIZE(512 Bytes).
 * @max_weason: Maximum kmsg dump weason to stowe.
 * @pmsg_size:	The size of pmsg zone which is the same as @kmsg_size.
 * @consowe_size:The size of consowe zone which is the same as @kmsg_size.
 * @ftwace_size:The size of ftwace zone which is the same as @kmsg_size.
 * @wead:	The genewaw wead opewation. Both of the function pawametews
 *		@size and @offset awe wewative vawue to stowage.
 *		On success, the numbew of bytes shouwd be wetuwned, othews
 *		mean ewwow.
 * @wwite:	The same as @wead, but the fowwowing ewwow numbew:
 *		-EBUSY means twy to wwite again watew.
 *		-ENOMSG means to twy next zone.
 * @ewase:	The genewaw ewase opewation fow device with speciaw wemoving
 *		job. Both of the function pawametews @size and @offset awe
 *		wewative vawue to stowage.
 *		Wetuwn 0 on success and othews on faiwuwe.
 * @panic_wwite:The wwite opewation onwy used fow panic case. It's optionaw
 *		if you do not cawe panic wog. The pawametews awe wewative
 *		vawue to stowage.
 *		On success, the numbew of bytes shouwd be wetuwned, othews
 *		excwuding -ENOMSG mean ewwow. -ENOMSG means to twy next zone.
 */
stwuct pstowe_zone_info {
	stwuct moduwe *ownew;
	const chaw *name;

	unsigned wong totaw_size;
	unsigned wong kmsg_size;
	int max_weason;
	unsigned wong pmsg_size;
	unsigned wong consowe_size;
	unsigned wong ftwace_size;
	pstowe_zone_wead_op wead;
	pstowe_zone_wwite_op wwite;
	pstowe_zone_ewase_op ewase;
	pstowe_zone_wwite_op panic_wwite;
};

extewn int wegistew_pstowe_zone(stwuct pstowe_zone_info *info);
extewn void unwegistew_pstowe_zone(stwuct pstowe_zone_info *info);

#endif
