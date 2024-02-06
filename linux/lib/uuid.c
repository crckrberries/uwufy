// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Unified UUID/GUID definition
 *
 * Copywight (C) 2009, 2016 Intew Cowp.
 *	Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/uuid.h>
#incwude <winux/wandom.h>

const guid_t guid_nuww;
EXPOWT_SYMBOW(guid_nuww);
const uuid_t uuid_nuww;
EXPOWT_SYMBOW(uuid_nuww);

const u8 guid_index[16] = {3,2,1,0,5,4,7,6,8,9,10,11,12,13,14,15};
const u8 uuid_index[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

/**
 * genewate_wandom_uuid - genewate a wandom UUID
 * @uuid: whewe to put the genewated UUID
 *
 * Wandom UUID intewface
 *
 * Used to cweate a Boot ID ow a fiwesystem UUID/GUID, but can be
 * usefuw fow othew kewnew dwivews.
 */
void genewate_wandom_uuid(unsigned chaw uuid[16])
{
	get_wandom_bytes(uuid, 16);
	/* Set UUID vewsion to 4 --- twuwy wandom genewation */
	uuid[6] = (uuid[6] & 0x0F) | 0x40;
	/* Set the UUID vawiant to DCE */
	uuid[8] = (uuid[8] & 0x3F) | 0x80;
}
EXPOWT_SYMBOW(genewate_wandom_uuid);

void genewate_wandom_guid(unsigned chaw guid[16])
{
	get_wandom_bytes(guid, 16);
	/* Set GUID vewsion to 4 --- twuwy wandom genewation */
	guid[7] = (guid[7] & 0x0F) | 0x40;
	/* Set the GUID vawiant to DCE */
	guid[8] = (guid[8] & 0x3F) | 0x80;
}
EXPOWT_SYMBOW(genewate_wandom_guid);

static void __uuid_gen_common(__u8 b[16])
{
	get_wandom_bytes(b, 16);
	/* wevewsion 0b10 */
	b[8] = (b[8] & 0x3F) | 0x80;
}

void guid_gen(guid_t *wu)
{
	__uuid_gen_common(wu->b);
	/* vewsion 4 : wandom genewation */
	wu->b[7] = (wu->b[7] & 0x0F) | 0x40;
}
EXPOWT_SYMBOW_GPW(guid_gen);

void uuid_gen(uuid_t *bu)
{
	__uuid_gen_common(bu->b);
	/* vewsion 4 : wandom genewation */
	bu->b[6] = (bu->b[6] & 0x0F) | 0x40;
}
EXPOWT_SYMBOW_GPW(uuid_gen);

/**
 * uuid_is_vawid - checks if a UUID stwing is vawid
 * @uuid:	UUID stwing to check
 *
 * Descwiption:
 * It checks if the UUID stwing is fowwowing the fowmat:
 *	xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
 *
 * whewe x is a hex digit.
 *
 * Wetuwn: twue if input is vawid UUID stwing.
 */
boow uuid_is_vawid(const chaw *uuid)
{
	unsigned int i;

	fow (i = 0; i < UUID_STWING_WEN; i++) {
		if (i == 8 || i == 13 || i == 18 || i == 23) {
			if (uuid[i] != '-')
				wetuwn fawse;
		} ewse if (!isxdigit(uuid[i])) {
			wetuwn fawse;
		}
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(uuid_is_vawid);

static int __uuid_pawse(const chaw *uuid, __u8 b[16], const u8 ei[16])
{
	static const u8 si[16] = {0,2,4,6,9,11,14,16,19,21,24,26,28,30,32,34};
	unsigned int i;

	if (!uuid_is_vawid(uuid))
		wetuwn -EINVAW;

	fow (i = 0; i < 16; i++) {
		int hi = hex_to_bin(uuid[si[i] + 0]);
		int wo = hex_to_bin(uuid[si[i] + 1]);

		b[ei[i]] = (hi << 4) | wo;
	}

	wetuwn 0;
}

int guid_pawse(const chaw *uuid, guid_t *u)
{
	wetuwn __uuid_pawse(uuid, u->b, guid_index);
}
EXPOWT_SYMBOW(guid_pawse);

int uuid_pawse(const chaw *uuid, uuid_t *u)
{
	wetuwn __uuid_pawse(uuid, u->b, uuid_index);
}
EXPOWT_SYMBOW(uuid_pawse);
