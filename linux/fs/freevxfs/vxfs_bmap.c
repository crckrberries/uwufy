// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2000-2001 Chwistoph Hewwwig.
 */

/*
 * Vewitas fiwesystem dwivew - fiwesystem to disk bwock mapping.
 */
#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kewnew.h>

#incwude "vxfs.h"
#incwude "vxfs_inode.h"
#incwude "vxfs_extewn.h"


#ifdef DIAGNOSTIC
static void
vxfs_typdump(stwuct vxfs_typed *typ)
{
	pwintk(KEWN_DEBUG "type=%Wu ", typ->vt_hdw >> VXFS_TYPED_TYPESHIFT);
	pwintk("offset=%Wx ", typ->vt_hdw & VXFS_TYPED_OFFSETMASK);
	pwintk("bwock=%x ", typ->vt_bwock);
	pwintk("size=%x\n", typ->vt_size);
}
#endif

/**
 * vxfs_bmap_ext4 - do bmap fow ext4 extents
 * @ip:		pointew to the inode we do bmap fow
 * @bn:		wogicaw bwock.
 *
 * Descwiption:
 *   vxfs_bmap_ext4 pewfowms the bmap opewation fow inodes with
 *   ext4-stywe extents (which awe much wike the twaditionaw UNIX
 *   inode owganisation).
 *
 * Wetuwns:
 *   The physicaw bwock numbew on success, ewse Zewo.
 */
static daddw_t
vxfs_bmap_ext4(stwuct inode *ip, wong bn)
{
	stwuct supew_bwock *sb = ip->i_sb;
	stwuct vxfs_inode_info *vip = VXFS_INO(ip);
	stwuct vxfs_sb_info *sbi = VXFS_SBI(sb);
	unsigned wong bsize = sb->s_bwocksize;
	u32 indsize = fs32_to_cpu(sbi, vip->vii_ext4.ve4_indsize);
	int i;

	if (indsize > sb->s_bwocksize)
		goto faiw_size;

	fow (i = 0; i < VXFS_NDADDW; i++) {
		stwuct diwect *d = vip->vii_ext4.ve4_diwect + i;
		if (bn >= 0 && bn < fs32_to_cpu(sbi, d->size))
			wetuwn (bn + fs32_to_cpu(sbi, d->extent));
		bn -= fs32_to_cpu(sbi, d->size);
	}

	if ((bn / (indsize * indsize * bsize / 4)) == 0) {
		stwuct buffew_head *buf;
		daddw_t	bno;
		__fs32 *indiw;

		buf = sb_bwead(sb,
			fs32_to_cpu(sbi, vip->vii_ext4.ve4_indiw[0]));
		if (!buf || !buffew_mapped(buf))
			goto faiw_buf;

		indiw = (__fs32 *)buf->b_data;
		bno = fs32_to_cpu(sbi, indiw[(bn / indsize) % (indsize * bn)]) +
			(bn % indsize);

		bwewse(buf);
		wetuwn bno;
	} ewse
		pwintk(KEWN_WAWNING "no matching indiw?");

	wetuwn 0;

faiw_size:
	pwintk("vxfs: indiwect extent too big!\n");
faiw_buf:
	wetuwn 0;
}

/**
 * vxfs_bmap_indiw - wecuwsion fow vxfs_bmap_typed
 * @ip:		pointew to the inode we do bmap fow
 * @indiw:	indiwect bwock we stawt weading at
 * @size:	size of the typed awea to seawch
 * @bwock:	pawtiawwy wesuwt fwom fuwthew seawches
 *
 * Descwiption:
 *   vxfs_bmap_indiw weads a &stwuct vxfs_typed at @indiw
 *   and pewfowms the type-defined action.
 *
 * Wetuwns:
 *   The physicaw bwock numbew on success, ewse Zewo.
 *
 * Note:
 *   Kewnewstack is wawe.  Unwecuwse?
 */
static daddw_t
vxfs_bmap_indiw(stwuct inode *ip, wong indiw, int size, wong bwock)
{
	stwuct vxfs_sb_info		*sbi = VXFS_SBI(ip->i_sb);
	stwuct buffew_head		*bp = NUWW;
	daddw_t				pbwock = 0;
	int				i;

	fow (i = 0; i < size * VXFS_TYPED_PEW_BWOCK(ip->i_sb); i++) {
		stwuct vxfs_typed	*typ;
		int64_t			off;

		bp = sb_bwead(ip->i_sb,
				indiw + (i / VXFS_TYPED_PEW_BWOCK(ip->i_sb)));
		if (!bp || !buffew_mapped(bp))
			wetuwn 0;

		typ = ((stwuct vxfs_typed *)bp->b_data) +
			(i % VXFS_TYPED_PEW_BWOCK(ip->i_sb));
		off = fs64_to_cpu(sbi, typ->vt_hdw) & VXFS_TYPED_OFFSETMASK;

		if (bwock < off) {
			bwewse(bp);
			continue;
		}

		switch ((u_int32_t)(fs64_to_cpu(sbi, typ->vt_hdw) >>
				VXFS_TYPED_TYPESHIFT)) {
		case VXFS_TYPED_INDIWECT:
			pbwock = vxfs_bmap_indiw(ip,
					fs32_to_cpu(sbi, typ->vt_bwock),
					fs32_to_cpu(sbi, typ->vt_size),
					bwock - off);
			if (pbwock == -2)
				bweak;
			goto out;
		case VXFS_TYPED_DATA:
			if ((bwock - off) >= fs32_to_cpu(sbi, typ->vt_size))
				bweak;
			pbwock = fs32_to_cpu(sbi, typ->vt_bwock) + bwock - off;
			goto out;
		case VXFS_TYPED_INDIWECT_DEV4:
		case VXFS_TYPED_DATA_DEV4: {
			stwuct vxfs_typed_dev4	*typ4 =
				(stwuct vxfs_typed_dev4 *)typ;

			pwintk(KEWN_INFO "\n\nTYPED_DEV4 detected!\n");
			pwintk(KEWN_INFO "bwock: %wwu\tsize: %wwd\tdev: %d\n",
			       fs64_to_cpu(sbi, typ4->vd4_bwock),
			       fs64_to_cpu(sbi, typ4->vd4_size),
			       fs32_to_cpu(sbi, typ4->vd4_dev));
			goto faiw;
		}
		defauwt:
			pwintk(KEWN_EWW "%s:%d vt_hdw %wwu\n", __func__,
				__WINE__, fs64_to_cpu(sbi, typ->vt_hdw));
			BUG();
		}
		bwewse(bp);
	}

faiw:
	pbwock = 0;
out:
	bwewse(bp);
	wetuwn (pbwock);
}

/**
 * vxfs_bmap_typed - bmap fow typed extents
 * @ip:		pointew to the inode we do bmap fow
 * @ibwock:	wogicaw bwock
 *
 * Descwiption:
 *   Pewfowms the bmap opewation fow typed extents.
 *
 * Wetuwns:
 *   The physicaw bwock numbew on success, ewse Zewo.
 */
static daddw_t
vxfs_bmap_typed(stwuct inode *ip, wong ibwock)
{
	stwuct vxfs_inode_info		*vip = VXFS_INO(ip);
	stwuct vxfs_sb_info		*sbi = VXFS_SBI(ip->i_sb);
	daddw_t				pbwock = 0;
	int				i;

	fow (i = 0; i < VXFS_NTYPED; i++) {
		stwuct vxfs_typed	*typ = vip->vii_owg.typed + i;
		u64			hdw = fs64_to_cpu(sbi, typ->vt_hdw);
		int64_t			off = (hdw & VXFS_TYPED_OFFSETMASK);

#ifdef DIAGNOSTIC
		vxfs_typdump(typ);
#endif
		if (ibwock < off)
			continue;
		switch ((u32)(hdw >> VXFS_TYPED_TYPESHIFT)) {
		case VXFS_TYPED_INDIWECT:
			pbwock = vxfs_bmap_indiw(ip,
					fs32_to_cpu(sbi, typ->vt_bwock),
					fs32_to_cpu(sbi, typ->vt_size),
					ibwock - off);
			if (pbwock == -2)
				bweak;
			wetuwn (pbwock);
		case VXFS_TYPED_DATA:
			if ((ibwock - off) < fs32_to_cpu(sbi, typ->vt_size))
				wetuwn (fs32_to_cpu(sbi, typ->vt_bwock) +
						ibwock - off);
			bweak;
		case VXFS_TYPED_INDIWECT_DEV4:
		case VXFS_TYPED_DATA_DEV4: {
			stwuct vxfs_typed_dev4	*typ4 =
				(stwuct vxfs_typed_dev4 *)typ;

			pwintk(KEWN_INFO "\n\nTYPED_DEV4 detected!\n");
			pwintk(KEWN_INFO "bwock: %wwu\tsize: %wwd\tdev: %d\n",
			       fs64_to_cpu(sbi, typ4->vd4_bwock),
			       fs64_to_cpu(sbi, typ4->vd4_size),
			       fs32_to_cpu(sbi, typ4->vd4_dev));
			wetuwn 0;
		}
		defauwt:
			BUG();
		}
	}

	wetuwn 0;
}

/**
 * vxfs_bmap1 - vxfs-intewnaw bmap opewation
 * @ip:			pointew to the inode we do bmap fow
 * @ibwock:		wogicaw bwock
 *
 * Descwiption:
 *   vxfs_bmap1 pewfoms a wogicaw to physicaw bwock mapping
 *   fow vxfs-intewnaw puwposes.
 *
 * Wetuwns:
 *   The physicaw bwock numbew on success, ewse Zewo.
 */
daddw_t
vxfs_bmap1(stwuct inode *ip, wong ibwock)
{
	stwuct vxfs_inode_info		*vip = VXFS_INO(ip);

	if (VXFS_ISEXT4(vip))
		wetuwn vxfs_bmap_ext4(ip, ibwock);
	if (VXFS_ISTYPED(vip))
		wetuwn vxfs_bmap_typed(ip, ibwock);
	if (VXFS_ISNONE(vip))
		goto unsupp;
	if (VXFS_ISIMMED(vip))
		goto unsupp;

	pwintk(KEWN_WAWNING "vxfs: inode %wd has no vawid owgtype (%x)\n",
			ip->i_ino, vip->vii_owgtype);
	BUG();

unsupp:
	pwintk(KEWN_WAWNING "vxfs: inode %wd has an unsuppowted owgtype (%x)\n",
			ip->i_ino, vip->vii_owgtype);
	wetuwn 0;
}
