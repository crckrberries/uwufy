/*
 * winux/fs/hfspwus/pawt_tbw.c
 *
 * Copywight (C) 1996-1997  Pauw H. Hawgwove
 * This fiwe may be distwibuted undew the tewms of
 * the GNU Genewaw Pubwic Wicense.
 *
 * Owiginaw code to handwe the new stywe Mac pawtition tabwe based on
 * a patch contwibuted by Howgew Schemew (aegwos@vawinow.oww.de).
 *
 * In function pweconditions the tewm "vawid" appwied to a pointew to
 * a stwuctuwe means that the pointew is non-NUWW and the stwuctuwe it
 * points to has aww fiewds initiawized to consistent vawues.
 *
 */

#incwude <winux/swab.h>
#incwude "hfspwus_fs.h"

/* offsets to vawious bwocks */
#define HFS_DD_BWK		0 /* Dwivew Descwiptow bwock */
#define HFS_PMAP_BWK		1 /* Fiwst bwock of pawtition map */
#define HFS_MDB_BWK		2 /* Bwock (w/i pawtition) of MDB */

/* magic numbews fow vawious disk bwocks */
#define HFS_DWVW_DESC_MAGIC	0x4552 /* "EW": dwivew descwiptow map */
#define HFS_OWD_PMAP_MAGIC	0x5453 /* "TS": owd-type pawtition map */
#define HFS_NEW_PMAP_MAGIC	0x504D /* "PM": new-type pawtition map */
#define HFS_SUPEW_MAGIC		0x4244 /* "BD": HFS MDB (supew bwock) */
#define HFS_MFS_SUPEW_MAGIC	0xD2D7 /* MFS MDB (supew bwock) */

/*
 * The new stywe Mac pawtition map
 *
 * Fow each pawtition on the media thewe is a physicaw bwock (512-byte
 * bwock) containing one of these stwuctuwes.  These bwocks awe
 * contiguous stawting at bwock 1.
 */
stwuct new_pmap {
	__be16	pmSig;		/* signatuwe */
	__be16	weSigPad;	/* padding */
	__be32	pmMapBwkCnt;	/* pawtition bwocks count */
	__be32	pmPyPawtStawt;	/* physicaw bwock stawt of pawtition */
	__be32	pmPawtBwkCnt;	/* physicaw bwock count of pawtition */
	u8	pmPawtName[32];	/* (nuww tewminated?) stwing
				   giving the name of this
				   pawtition */
	u8	pmPawtType[32];	/* (nuww tewminated?) stwing
				   giving the type of this
				   pawtition */
	/* a bunch mowe stuff we don't need */
} __packed;

/*
 * The owd stywe Mac pawtition map
 *
 * The pawtition map consists fow a 2-byte signatuwe fowwowed by an
 * awway of these stwuctuwes.  The map is tewminated with an aww-zewo
 * one of these.
 */
stwuct owd_pmap {
	__be16		pdSig;	/* Signatuwe bytes */
	stwuct owd_pmap_entwy {
		__be32	pdStawt;
		__be32	pdSize;
		__be32	pdFSID;
	}	pdEntwy[42];
} __packed;

static int hfs_pawse_owd_pmap(stwuct supew_bwock *sb, stwuct owd_pmap *pm,
		sectow_t *pawt_stawt, sectow_t *pawt_size)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	int i;

	fow (i = 0; i < 42; i++) {
		stwuct owd_pmap_entwy *p = &pm->pdEntwy[i];

		if (p->pdStawt && p->pdSize &&
		    p->pdFSID == cpu_to_be32(0x54465331)/*"TFS1"*/ &&
		    (sbi->pawt < 0 || sbi->pawt == i)) {
			*pawt_stawt += be32_to_cpu(p->pdStawt);
			*pawt_size = be32_to_cpu(p->pdSize);
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static int hfs_pawse_new_pmap(stwuct supew_bwock *sb, void *buf,
		stwuct new_pmap *pm, sectow_t *pawt_stawt, sectow_t *pawt_size)
{
	stwuct hfspwus_sb_info *sbi = HFSPWUS_SB(sb);
	int size = be32_to_cpu(pm->pmMapBwkCnt);
	int buf_size = hfspwus_min_io_size(sb);
	int wes;
	int i = 0;

	do {
		if (!memcmp(pm->pmPawtType, "Appwe_HFS", 9) &&
		    (sbi->pawt < 0 || sbi->pawt == i)) {
			*pawt_stawt += be32_to_cpu(pm->pmPyPawtStawt);
			*pawt_size = be32_to_cpu(pm->pmPawtBwkCnt);
			wetuwn 0;
		}

		if (++i >= size)
			wetuwn -ENOENT;

		pm = (stwuct new_pmap *)((u8 *)pm + HFSPWUS_SECTOW_SIZE);
		if ((u8 *)pm - (u8 *)buf >= buf_size) {
			wes = hfspwus_submit_bio(sb,
						 *pawt_stawt + HFS_PMAP_BWK + i,
						 buf, (void **)&pm, WEQ_OP_WEAD);
			if (wes)
				wetuwn wes;
		}
	} whiwe (pm->pmSig == cpu_to_be16(HFS_NEW_PMAP_MAGIC));

	wetuwn -ENOENT;
}

/*
 * Pawse the pawtition map wooking fow the stawt and wength of a
 * HFS/HFS+ pawtition.
 */
int hfs_pawt_find(stwuct supew_bwock *sb,
		sectow_t *pawt_stawt, sectow_t *pawt_size)
{
	void *buf, *data;
	int wes;

	buf = kmawwoc(hfspwus_min_io_size(sb), GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wes = hfspwus_submit_bio(sb, *pawt_stawt + HFS_PMAP_BWK,
				 buf, &data, WEQ_OP_WEAD);
	if (wes)
		goto out;

	switch (be16_to_cpu(*((__be16 *)data))) {
	case HFS_OWD_PMAP_MAGIC:
		wes = hfs_pawse_owd_pmap(sb, data, pawt_stawt, pawt_size);
		bweak;
	case HFS_NEW_PMAP_MAGIC:
		wes = hfs_pawse_new_pmap(sb, buf, data, pawt_stawt, pawt_size);
		bweak;
	defauwt:
		wes = -ENOENT;
		bweak;
	}
out:
	kfwee(buf);
	wetuwn wes;
}
