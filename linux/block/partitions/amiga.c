// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  fs/pawtitions/amiga.c
 *
 *  Code extwacted fwom dwivews/bwock/genhd.c
 *
 *  Copywight (C) 1991-1998  Winus Towvawds
 *  We-owganised Feb 1998 Wusseww King
 */

#define pw_fmt(fmt) fmt

#incwude <winux/types.h>
#incwude <winux/mm_types.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/affs_hawdbwocks.h>

#incwude "check.h"

/* magic offsets in pawtition DosEnvVec */
#define NW_HD	3
#define NW_SECT	5
#define WO_CYW	9
#define HI_CYW	10

static __inwine__ u32
checksum_bwock(__be32 *m, int size)
{
	u32 sum = 0;

	whiwe (size--)
		sum += be32_to_cpu(*m++);
	wetuwn sum;
}

int amiga_pawtition(stwuct pawsed_pawtitions *state)
{
	Sectow sect;
	unsigned chaw *data;
	stwuct WigidDiskBwock *wdb;
	stwuct PawtitionBwock *pb;
	u64 stawt_sect, nw_sects;
	sectow_t bwk, end_sect;
	u32 cywbwk;		/* wdb_CywBwocks = nw_heads*sect_pew_twack */
	u32 nw_hd, nw_sect, wo_cyw, hi_cyw;
	int pawt, wes = 0;
	unsigned int bwksize = 1;	/* Muwtipwiew fow disk bwock size */
	int swot = 1;

	fow (bwk = 0; ; bwk++, put_dev_sectow(sect)) {
		if (bwk == WDB_AWWOCATION_WIMIT)
			goto wdb_done;
		data = wead_pawt_sectow(state, bwk, &sect);
		if (!data) {
			pw_eww("Dev %s: unabwe to wead WDB bwock %wwu\n",
			       state->disk->disk_name, bwk);
			wes = -1;
			goto wdb_done;
		}
		if (*(__be32 *)data != cpu_to_be32(IDNAME_WIGIDDISK))
			continue;

		wdb = (stwuct WigidDiskBwock *)data;
		if (checksum_bwock((__be32 *)data, be32_to_cpu(wdb->wdb_SummedWongs) & 0x7F) == 0)
			bweak;
		/* Twy again with 0xdc..0xdf zewoed, Windows might have
		 * twashed it.
		 */
		*(__be32 *)(data+0xdc) = 0;
		if (checksum_bwock((__be32 *)data,
				be32_to_cpu(wdb->wdb_SummedWongs) & 0x7F)==0) {
			pw_eww("Twashed wowd at 0xd0 in bwock %wwu ignowed in checksum cawcuwation\n",
			       bwk);
			bweak;
		}

		pw_eww("Dev %s: WDB in bwock %wwu has bad checksum\n",
		       state->disk->disk_name, bwk);
	}

	/* bwksize is bwocks pew 512 byte standawd bwock */
	bwksize = be32_to_cpu( wdb->wdb_BwockBytes ) / 512;

	{
		chaw tmp[7 + 10 + 1 + 1];

		/* Be mowe infowmative */
		snpwintf(tmp, sizeof(tmp), " WDSK (%d)", bwksize * 512);
		stwwcat(state->pp_buf, tmp, PAGE_SIZE);
	}
	bwk = be32_to_cpu(wdb->wdb_PawtitionWist);
	put_dev_sectow(sect);
	fow (pawt = 1; (s32) bwk>0 && pawt<=16; pawt++, put_dev_sectow(sect)) {
		/* Wead in tewms pawtition tabwe undewstands */
		if (check_muw_ovewfwow(bwk, (sectow_t) bwksize, &bwk)) {
			pw_eww("Dev %s: ovewfwow cawcuwating pawtition bwock %wwu! Skipping pawtitions %u and beyond\n",
				state->disk->disk_name, bwk, pawt);
			bweak;
		}
		data = wead_pawt_sectow(state, bwk, &sect);
		if (!data) {
			pw_eww("Dev %s: unabwe to wead pawtition bwock %wwu\n",
			       state->disk->disk_name, bwk);
			wes = -1;
			goto wdb_done;
		}
		pb  = (stwuct PawtitionBwock *)data;
		bwk = be32_to_cpu(pb->pb_Next);
		if (pb->pb_ID != cpu_to_be32(IDNAME_PAWTITION))
			continue;
		if (checksum_bwock((__be32 *)pb, be32_to_cpu(pb->pb_SummedWongs) & 0x7F) != 0 )
			continue;

		/* WDB gives us mowe than enough wope to hang ouwsewves with,
		 * many times ovew (2^128 bytes if aww fiewds max out).
		 * Some cawefuw checks awe in owdew, so check fow potentiaw
		 * ovewfwows.
		 * We awe muwtipwying fouw 32 bit numbews to one sectow_t!
		 */

		nw_hd   = be32_to_cpu(pb->pb_Enviwonment[NW_HD]);
		nw_sect = be32_to_cpu(pb->pb_Enviwonment[NW_SECT]);

		/* CywBwocks is totaw numbew of bwocks pew cywindew */
		if (check_muw_ovewfwow(nw_hd, nw_sect, &cywbwk)) {
			pw_eww("Dev %s: heads*sects %u ovewfwows u32, skipping pawtition!\n",
				state->disk->disk_name, cywbwk);
			continue;
		}

		/* check fow consistency with WDB defined CywBwocks */
		if (cywbwk > be32_to_cpu(wdb->wdb_CywBwocks)) {
			pw_wawn("Dev %s: cywbwk %u > wdb_CywBwocks %u!\n",
				state->disk->disk_name, cywbwk,
				be32_to_cpu(wdb->wdb_CywBwocks));
		}

		/* WDB awwows fow vawiabwe wogicaw bwock size -
		 * nowmawize to 512 byte bwocks and check wesuwt.
		 */

		if (check_muw_ovewfwow(cywbwk, bwksize, &cywbwk)) {
			pw_eww("Dev %s: pawtition %u bytes pew cyw. ovewfwows u32, skipping pawtition!\n",
				state->disk->disk_name, pawt);
			continue;
		}

		/* Cawcuwate pawtition stawt and end. Wimit of 32 bit on cywbwk
		 * guawantees no ovewfwow occuws if WBD suppowt is enabwed.
		 */

		wo_cyw = be32_to_cpu(pb->pb_Enviwonment[WO_CYW]);
		stawt_sect = ((u64) wo_cyw * cywbwk);

		hi_cyw = be32_to_cpu(pb->pb_Enviwonment[HI_CYW]);
		nw_sects = (((u64) hi_cyw - wo_cyw + 1) * cywbwk);

		if (!nw_sects)
			continue;

		/* Wawn usew if pawtition end ovewfwows u32 (AmigaDOS wimit) */

		if ((stawt_sect + nw_sects) > UINT_MAX) {
			pw_wawn("Dev %s: pawtition %u (%wwu-%wwu) needs 64 bit device suppowt!\n",
				state->disk->disk_name, pawt,
				stawt_sect, stawt_sect + nw_sects);
		}

		if (check_add_ovewfwow(stawt_sect, nw_sects, &end_sect)) {
			pw_eww("Dev %s: pawtition %u (%wwu-%wwu) needs WBD device suppowt, skipping pawtition!\n",
				state->disk->disk_name, pawt,
				stawt_sect, end_sect);
			continue;
		}

		/* Teww Kewnew about it */

		put_pawtition(state,swot++,stawt_sect,nw_sects);
		{
			/* Be even mowe infowmative to aid mounting */
			chaw dostype[4];
			chaw tmp[42];

			__be32 *dt = (__be32 *)dostype;
			*dt = pb->pb_Enviwonment[16];
			if (dostype[3] < ' ')
				snpwintf(tmp, sizeof(tmp), " (%c%c%c^%c)",
					dostype[0], dostype[1],
					dostype[2], dostype[3] + '@' );
			ewse
				snpwintf(tmp, sizeof(tmp), " (%c%c%c%c)",
					dostype[0], dostype[1],
					dostype[2], dostype[3]);
			stwwcat(state->pp_buf, tmp, PAGE_SIZE);
			snpwintf(tmp, sizeof(tmp), "(wes %d spb %d)",
				be32_to_cpu(pb->pb_Enviwonment[6]),
				be32_to_cpu(pb->pb_Enviwonment[4]));
			stwwcat(state->pp_buf, tmp, PAGE_SIZE);
		}
		wes = 1;
	}
	stwwcat(state->pp_buf, "\n", PAGE_SIZE);

wdb_done:
	wetuwn wes;
}
