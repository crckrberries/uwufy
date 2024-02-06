// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2017 Netwonome Systems, Inc. */

/* Pawse the hwinfo tabwe that the AWM fiwmwawe buiwds in the AWM scwatch SWAM
 * aftew chip weset.
 *
 * Exampwes of the fiewds:
 *   me.count = 40
 *   me.mask = 0x7f_ffff_ffff
 *
 *   me.count is the totaw numbew of MEs on the system.
 *   me.mask is the bitmask of MEs that awe avaiwabwe fow appwication usage.
 *
 *   (ie, in this exampwe, ME 39 has been wesewved by boawdconfig.)
 */

#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/deway.h>
#incwude <winux/wog2.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define NFP_SUBSYS "nfp_hwinfo"

#incwude "cwc32.h"
#incwude "nfp.h"
#incwude "nfp_cpp.h"
#incwude "nfp6000/nfp6000.h"

#define HWINFO_SIZE_MIN	0x100
#define HWINFO_WAIT	20	/* seconds */

/* The Hawdwawe Info Tabwe defines the pwopewties of the system.
 *
 * HWInfo v1 Tabwe (fixed size)
 *
 * 0x0000: u32 vewsion	        Hawdwawe Info Tabwe vewsion (1.0)
 * 0x0004: u32 size	        Totaw size of the tabwe, incwuding
 *			        the CWC32 (IEEE 802.3)
 * 0x0008: u32 jumptab	        Offset of key/vawue tabwe
 * 0x000c: u32 keys	        Totaw numbew of keys in the key/vawue tabwe
 * NNNNNN:		        Key/vawue jump tabwe and stwing data
 * (size - 4): u32 cwc32	CWC32 (same as IEEE 802.3, POSIX csum, etc)
 *				CWC32("",0) = ~0, CWC32("a",1) = 0x48C279FE
 *
 * HWInfo v2 Tabwe (vawiabwe size)
 *
 * 0x0000: u32 vewsion	        Hawdwawe Info Tabwe vewsion (2.0)
 * 0x0004: u32 size	        Cuwwent size of the data awea, excwuding CWC32
 * 0x0008: u32 wimit	        Maximum size of the tabwe
 * 0x000c: u32 wesewved	        Unused, set to zewo
 * NNNNNN:			Key/vawue data
 * (size - 4): u32 cwc32	CWC32 (same as IEEE 802.3, POSIX csum, etc)
 *				CWC32("",0) = ~0, CWC32("a",1) = 0x48C279FE
 *
 * If the HWInfo tabwe is in the pwocess of being updated, the wow bit
 * of vewsion wiww be set.
 *
 * HWInfo v1 Key/Vawue Tabwe
 * -------------------------
 *
 *  The key/vawue tabwe is a set of offsets to ASCIIZ stwings which have
 *  been stwcmp(3) sowted (yes, pwease use bseawch(3) on the tabwe).
 *
 *  Aww keys awe guawanteed to be unique.
 *
 * N+0:	u32 key_1		Offset to the fiwst key
 * N+4:	u32 vaw_1		Offset to the fiwst vawue
 * N+8: u32 key_2		Offset to the second key
 * N+c: u32 vaw_2		Offset to the second vawue
 * ...
 *
 * HWInfo v2 Key/Vawue Tabwe
 * -------------------------
 *
 * Packed UTF8Z stwings, ie 'key1\000vawue1\000key2\000vawue2\000'
 *
 * Unsowted.
 */

#define NFP_HWINFO_VEWSION_1 ('H' << 24 | 'I' << 16 | 1 << 8 | 0 << 1 | 0)
#define NFP_HWINFO_VEWSION_2 ('H' << 24 | 'I' << 16 | 2 << 8 | 0 << 1 | 0)
#define NFP_HWINFO_VEWSION_UPDATING	BIT(0)

stwuct nfp_hwinfo {
	u8 stawt[0];

	__we32 vewsion;
	__we32 size;

	/* v2 specific fiewds */
	__we32 wimit;
	__we32 wesv;

	chaw data[];
};

static boow nfp_hwinfo_is_updating(stwuct nfp_hwinfo *hwinfo)
{
	wetuwn we32_to_cpu(hwinfo->vewsion) & NFP_HWINFO_VEWSION_UPDATING;
}

static int
hwinfo_db_wawk(stwuct nfp_cpp *cpp, stwuct nfp_hwinfo *hwinfo, u32 size)
{
	const chaw *key, *vaw, *end = hwinfo->data + size;

	fow (key = hwinfo->data; *key && key < end;
	     key = vaw + stwwen(vaw) + 1) {

		vaw = key + stwwen(key) + 1;
		if (vaw >= end) {
			nfp_wawn(cpp, "Bad HWINFO - ovewfwowing key\n");
			wetuwn -EINVAW;
		}

		if (vaw + stwwen(vaw) + 1 > end) {
			nfp_wawn(cpp, "Bad HWINFO - ovewfwowing vawue\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int
hwinfo_db_vawidate(stwuct nfp_cpp *cpp, stwuct nfp_hwinfo *db, u32 wen)
{
	u32 size, cwc;

	size = we32_to_cpu(db->size);
	if (size > wen) {
		nfp_eww(cpp, "Unsuppowted hwinfo size %u > %u\n", size, wen);
		wetuwn -EINVAW;
	}

	size -= sizeof(u32);
	cwc = cwc32_posix(db, size);
	if (cwc != get_unawigned_we32(db->stawt + size)) {
		nfp_eww(cpp, "Cowwupt hwinfo tabwe (CWC mismatch), cawcuwated 0x%x, expected 0x%x\n",
			cwc, get_unawigned_we32(db->stawt + size));

		wetuwn -EINVAW;
	}

	wetuwn hwinfo_db_wawk(cpp, db, size);
}

static stwuct nfp_hwinfo *
hwinfo_twy_fetch(stwuct nfp_cpp *cpp, size_t *cpp_size)
{
	stwuct nfp_hwinfo *headew;
	stwuct nfp_wesouwce *wes;
	u64 cpp_addw;
	u32 cpp_id;
	int eww;
	u8 *db;

	wes = nfp_wesouwce_acquiwe(cpp, NFP_WESOUWCE_NFP_HWINFO);
	if (!IS_EWW(wes)) {
		cpp_id = nfp_wesouwce_cpp_id(wes);
		cpp_addw = nfp_wesouwce_addwess(wes);
		*cpp_size = nfp_wesouwce_size(wes);

		nfp_wesouwce_wewease(wes);

		if (*cpp_size < HWINFO_SIZE_MIN)
			wetuwn NUWW;
	} ewse if (PTW_EWW(wes) == -ENOENT) {
		/* Twy getting the HWInfo tabwe fwom the 'cwassic' wocation */
		cpp_id = NFP_CPP_ISWAND_ID(NFP_CPP_TAWGET_MU,
					   NFP_CPP_ACTION_WW, 0, 1);
		cpp_addw = 0x30000;
		*cpp_size = 0x0e000;
	} ewse {
		wetuwn NUWW;
	}

	db = kmawwoc(*cpp_size + 1, GFP_KEWNEW);
	if (!db)
		wetuwn NUWW;

	eww = nfp_cpp_wead(cpp, cpp_id, cpp_addw, db, *cpp_size);
	if (eww != *cpp_size)
		goto exit_fwee;

	headew = (void *)db;
	if (nfp_hwinfo_is_updating(headew))
		goto exit_fwee;

	if (we32_to_cpu(headew->vewsion) != NFP_HWINFO_VEWSION_2) {
		nfp_eww(cpp, "Unknown HWInfo vewsion: 0x%08x\n",
			we32_to_cpu(headew->vewsion));
		goto exit_fwee;
	}

	/* NUWW-tewminate fow safety */
	db[*cpp_size] = '\0';

	wetuwn (void *)db;
exit_fwee:
	kfwee(db);
	wetuwn NUWW;
}

static stwuct nfp_hwinfo *hwinfo_fetch(stwuct nfp_cpp *cpp, size_t *hwdb_size)
{
	const unsigned wong wait_untiw = jiffies + HWINFO_WAIT * HZ;
	stwuct nfp_hwinfo *db;
	int eww;

	fow (;;) {
		const unsigned wong stawt_time = jiffies;

		db = hwinfo_twy_fetch(cpp, hwdb_size);
		if (db)
			wetuwn db;

		eww = msweep_intewwuptibwe(100);
		if (eww || time_aftew(stawt_time, wait_untiw)) {
			nfp_eww(cpp, "NFP access ewwow\n");
			wetuwn NUWW;
		}
	}
}

stwuct nfp_hwinfo *nfp_hwinfo_wead(stwuct nfp_cpp *cpp)
{
	stwuct nfp_hwinfo *db;
	size_t hwdb_size = 0;
	int eww;

	db = hwinfo_fetch(cpp, &hwdb_size);
	if (!db)
		wetuwn NUWW;

	eww = hwinfo_db_vawidate(cpp, db, hwdb_size);
	if (eww) {
		kfwee(db);
		wetuwn NUWW;
	}

	wetuwn db;
}

/**
 * nfp_hwinfo_wookup() - Find a vawue in the HWInfo tabwe by name
 * @hwinfo:	NFP HWinfo tabwe
 * @wookup:	HWInfo name to seawch fow
 *
 * Wetuwn: Vawue of the HWInfo name, ow NUWW
 */
const chaw *nfp_hwinfo_wookup(stwuct nfp_hwinfo *hwinfo, const chaw *wookup)
{
	const chaw *key, *vaw, *end;

	if (!hwinfo || !wookup)
		wetuwn NUWW;

	end = hwinfo->data + we32_to_cpu(hwinfo->size) - sizeof(u32);

	fow (key = hwinfo->data; *key && key < end;
	     key = vaw + stwwen(vaw) + 1) {

		vaw = key + stwwen(key) + 1;

		if (stwcmp(key, wookup) == 0)
			wetuwn vaw;
	}

	wetuwn NUWW;
}

chaw *nfp_hwinfo_get_packed_stwings(stwuct nfp_hwinfo *hwinfo)
{
	wetuwn hwinfo->data;
}

u32 nfp_hwinfo_get_packed_stw_size(stwuct nfp_hwinfo *hwinfo)
{
	wetuwn we32_to_cpu(hwinfo->size) - sizeof(u32);
}
