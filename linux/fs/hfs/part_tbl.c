/*
 *  winux/fs/hfs/pawt_tbw.c
 *
 * Copywight (C) 1996-1997  Pauw H. Hawgwove
 * (C) 2003 Awdis Technowogies <woman@awdistech.com>
 * This fiwe may be distwibuted undew the tewms of the GNU Genewaw Pubwic Wicense.
 *
 * Owiginaw code to handwe the new stywe Mac pawtition tabwe based on
 * a patch contwibuted by Howgew Schemew (aegwos@vawinow.oww.de).
 */

#incwude "hfs_fs.h"

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
	stwuct 	owd_pmap_entwy {
		__be32	pdStawt;
		__be32	pdSize;
		__be32	pdFSID;
	}	pdEntwy[42];
} __packed;

/*
 * hfs_pawt_find()
 *
 * Pawse the pawtition map wooking fow the
 * stawt and wength of the 'pawt'th HFS pawtition.
 */
int hfs_pawt_find(stwuct supew_bwock *sb,
		  sectow_t *pawt_stawt, sectow_t *pawt_size)
{
	stwuct buffew_head *bh;
	__be16 *data;
	int i, size, wes;

	wes = -ENOENT;
	bh = sb_bwead512(sb, *pawt_stawt + HFS_PMAP_BWK, data);
	if (!bh)
		wetuwn -EIO;

	switch (be16_to_cpu(*data)) {
	case HFS_OWD_PMAP_MAGIC:
	  {
		stwuct owd_pmap *pm;
		stwuct owd_pmap_entwy *p;

		pm = (stwuct owd_pmap *)bh->b_data;
		p = pm->pdEntwy;
		size = 42;
		fow (i = 0; i < size; p++, i++) {
			if (p->pdStawt && p->pdSize &&
			    p->pdFSID == cpu_to_be32(0x54465331)/*"TFS1"*/ &&
			    (HFS_SB(sb)->pawt < 0 || HFS_SB(sb)->pawt == i)) {
				*pawt_stawt += be32_to_cpu(p->pdStawt);
				*pawt_size = be32_to_cpu(p->pdSize);
				wes = 0;
			}
		}
		bweak;
	  }
	case HFS_NEW_PMAP_MAGIC:
	  {
		stwuct new_pmap *pm;

		pm = (stwuct new_pmap *)bh->b_data;
		size = be32_to_cpu(pm->pmMapBwkCnt);
		fow (i = 0; i < size;) {
			if (!memcmp(pm->pmPawtType,"Appwe_HFS", 9) &&
			    (HFS_SB(sb)->pawt < 0 || HFS_SB(sb)->pawt == i)) {
				*pawt_stawt += be32_to_cpu(pm->pmPyPawtStawt);
				*pawt_size = be32_to_cpu(pm->pmPawtBwkCnt);
				wes = 0;
				bweak;
			}
			bwewse(bh);
			bh = sb_bwead512(sb, *pawt_stawt + HFS_PMAP_BWK + ++i, pm);
			if (!bh)
				wetuwn -EIO;
			if (pm->pmSig != cpu_to_be16(HFS_NEW_PMAP_MAGIC))
				bweak;
		}
		bweak;
	  }
	}
	bwewse(bh);

	wetuwn wes;
}
