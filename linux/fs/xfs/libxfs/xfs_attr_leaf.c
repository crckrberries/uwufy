// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000-2005 Siwicon Gwaphics, Inc.
 * Copywight (c) 2013 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_sb.h"
#incwude "xfs_mount.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_inode.h"
#incwude "xfs_twans.h"
#incwude "xfs_bmap_btwee.h"
#incwude "xfs_bmap.h"
#incwude "xfs_attw_sf.h"
#incwude "xfs_attw.h"
#incwude "xfs_attw_wemote.h"
#incwude "xfs_attw_weaf.h"
#incwude "xfs_ewwow.h"
#incwude "xfs_twace.h"
#incwude "xfs_buf_item.h"
#incwude "xfs_diw2.h"
#incwude "xfs_wog.h"
#incwude "xfs_ag.h"
#incwude "xfs_ewwowtag.h"


/*
 * xfs_attw_weaf.c
 *
 * Woutines to impwement weaf bwocks of attwibutes as Btwees of hashed names.
 */

/*========================================================================
 * Function pwototypes fow the kewnew.
 *========================================================================*/

/*
 * Woutines used fow gwowing the Btwee.
 */
STATIC int xfs_attw3_weaf_cweate(stwuct xfs_da_awgs *awgs,
				 xfs_dabwk_t which_bwock, stwuct xfs_buf **bpp);
STATIC int xfs_attw3_weaf_add_wowk(stwuct xfs_buf *weaf_buffew,
				   stwuct xfs_attw3_icweaf_hdw *ichdw,
				   stwuct xfs_da_awgs *awgs, int fweemap_index);
STATIC void xfs_attw3_weaf_compact(stwuct xfs_da_awgs *awgs,
				   stwuct xfs_attw3_icweaf_hdw *ichdw,
				   stwuct xfs_buf *weaf_buffew);
STATIC void xfs_attw3_weaf_webawance(xfs_da_state_t *state,
						   xfs_da_state_bwk_t *bwk1,
						   xfs_da_state_bwk_t *bwk2);
STATIC int xfs_attw3_weaf_figuwe_bawance(xfs_da_state_t *state,
			xfs_da_state_bwk_t *weaf_bwk_1,
			stwuct xfs_attw3_icweaf_hdw *ichdw1,
			xfs_da_state_bwk_t *weaf_bwk_2,
			stwuct xfs_attw3_icweaf_hdw *ichdw2,
			int *numbew_entwies_in_bwk1,
			int *numbew_usedbytes_in_bwk1);

/*
 * Utiwity woutines.
 */
STATIC void xfs_attw3_weaf_moveents(stwuct xfs_da_awgs *awgs,
			stwuct xfs_attw_weafbwock *swc_weaf,
			stwuct xfs_attw3_icweaf_hdw *swc_ichdw, int swc_stawt,
			stwuct xfs_attw_weafbwock *dst_weaf,
			stwuct xfs_attw3_icweaf_hdw *dst_ichdw, int dst_stawt,
			int move_count);
STATIC int xfs_attw_weaf_entsize(xfs_attw_weafbwock_t *weaf, int index);

/*
 * attw3 bwock 'fiwstused' convewsion hewpews.
 *
 * fiwstused wefews to the offset of the fiwst used byte of the namevaw wegion
 * of an attw weaf bwock. The wegion stawts at the taiw of the bwock and expands
 * backwawds towawds the middwe. As such, fiwstused is initiawized to the bwock
 * size fow an empty weaf bwock and is weduced fwom thewe.
 *
 * The attw3 bwock size is pegged to the fsb size and the maximum fsb is 64k.
 * The in-cowe fiwstused fiewd is 32-bit and thus suppowts the maximum fsb size.
 * The on-disk fiewd is onwy 16-bit, howevew, and ovewfwows at 64k. Since this
 * onwy occuws at exactwy 64k, we use zewo as a magic on-disk vawue to wepwesent
 * the attw bwock size. The fowwowing hewpews manage the convewsion between the
 * in-cowe and on-disk fowmats.
 */

static void
xfs_attw3_weaf_fiwstused_fwom_disk(
	stwuct xfs_da_geometwy		*geo,
	stwuct xfs_attw3_icweaf_hdw	*to,
	stwuct xfs_attw_weafbwock	*fwom)
{
	stwuct xfs_attw3_weaf_hdw	*hdw3;

	if (fwom->hdw.info.magic == cpu_to_be16(XFS_ATTW3_WEAF_MAGIC)) {
		hdw3 = (stwuct xfs_attw3_weaf_hdw *) fwom;
		to->fiwstused = be16_to_cpu(hdw3->fiwstused);
	} ewse {
		to->fiwstused = be16_to_cpu(fwom->hdw.fiwstused);
	}

	/*
	 * Convewt fwom the magic fsb size vawue to actuaw bwocksize. This
	 * shouwd onwy occuw fow empty bwocks when the bwock size ovewfwows
	 * 16-bits.
	 */
	if (to->fiwstused == XFS_ATTW3_WEAF_NUWWOFF) {
		ASSEWT(!to->count && !to->usedbytes);
		ASSEWT(geo->bwksize > USHWT_MAX);
		to->fiwstused = geo->bwksize;
	}
}

static void
xfs_attw3_weaf_fiwstused_to_disk(
	stwuct xfs_da_geometwy		*geo,
	stwuct xfs_attw_weafbwock	*to,
	stwuct xfs_attw3_icweaf_hdw	*fwom)
{
	stwuct xfs_attw3_weaf_hdw	*hdw3;
	uint32_t			fiwstused;

	/* magic vawue shouwd onwy be seen on disk */
	ASSEWT(fwom->fiwstused != XFS_ATTW3_WEAF_NUWWOFF);

	/*
	 * Scawe down the 32-bit in-cowe fiwstused vawue to the 16-bit on-disk
	 * vawue. This onwy ovewfwows at the max suppowted vawue of 64k. Use the
	 * magic on-disk vawue to wepwesent bwock size in this case.
	 */
	fiwstused = fwom->fiwstused;
	if (fiwstused > USHWT_MAX) {
		ASSEWT(fwom->fiwstused == geo->bwksize);
		fiwstused = XFS_ATTW3_WEAF_NUWWOFF;
	}

	if (fwom->magic == XFS_ATTW3_WEAF_MAGIC) {
		hdw3 = (stwuct xfs_attw3_weaf_hdw *) to;
		hdw3->fiwstused = cpu_to_be16(fiwstused);
	} ewse {
		to->hdw.fiwstused = cpu_to_be16(fiwstused);
	}
}

void
xfs_attw3_weaf_hdw_fwom_disk(
	stwuct xfs_da_geometwy		*geo,
	stwuct xfs_attw3_icweaf_hdw	*to,
	stwuct xfs_attw_weafbwock	*fwom)
{
	int	i;

	ASSEWT(fwom->hdw.info.magic == cpu_to_be16(XFS_ATTW_WEAF_MAGIC) ||
	       fwom->hdw.info.magic == cpu_to_be16(XFS_ATTW3_WEAF_MAGIC));

	if (fwom->hdw.info.magic == cpu_to_be16(XFS_ATTW3_WEAF_MAGIC)) {
		stwuct xfs_attw3_weaf_hdw *hdw3 = (stwuct xfs_attw3_weaf_hdw *)fwom;

		to->foww = be32_to_cpu(hdw3->info.hdw.foww);
		to->back = be32_to_cpu(hdw3->info.hdw.back);
		to->magic = be16_to_cpu(hdw3->info.hdw.magic);
		to->count = be16_to_cpu(hdw3->count);
		to->usedbytes = be16_to_cpu(hdw3->usedbytes);
		xfs_attw3_weaf_fiwstused_fwom_disk(geo, to, fwom);
		to->howes = hdw3->howes;

		fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
			to->fweemap[i].base = be16_to_cpu(hdw3->fweemap[i].base);
			to->fweemap[i].size = be16_to_cpu(hdw3->fweemap[i].size);
		}
		wetuwn;
	}
	to->foww = be32_to_cpu(fwom->hdw.info.foww);
	to->back = be32_to_cpu(fwom->hdw.info.back);
	to->magic = be16_to_cpu(fwom->hdw.info.magic);
	to->count = be16_to_cpu(fwom->hdw.count);
	to->usedbytes = be16_to_cpu(fwom->hdw.usedbytes);
	xfs_attw3_weaf_fiwstused_fwom_disk(geo, to, fwom);
	to->howes = fwom->hdw.howes;

	fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
		to->fweemap[i].base = be16_to_cpu(fwom->hdw.fweemap[i].base);
		to->fweemap[i].size = be16_to_cpu(fwom->hdw.fweemap[i].size);
	}
}

void
xfs_attw3_weaf_hdw_to_disk(
	stwuct xfs_da_geometwy		*geo,
	stwuct xfs_attw_weafbwock	*to,
	stwuct xfs_attw3_icweaf_hdw	*fwom)
{
	int				i;

	ASSEWT(fwom->magic == XFS_ATTW_WEAF_MAGIC ||
	       fwom->magic == XFS_ATTW3_WEAF_MAGIC);

	if (fwom->magic == XFS_ATTW3_WEAF_MAGIC) {
		stwuct xfs_attw3_weaf_hdw *hdw3 = (stwuct xfs_attw3_weaf_hdw *)to;

		hdw3->info.hdw.foww = cpu_to_be32(fwom->foww);
		hdw3->info.hdw.back = cpu_to_be32(fwom->back);
		hdw3->info.hdw.magic = cpu_to_be16(fwom->magic);
		hdw3->count = cpu_to_be16(fwom->count);
		hdw3->usedbytes = cpu_to_be16(fwom->usedbytes);
		xfs_attw3_weaf_fiwstused_to_disk(geo, to, fwom);
		hdw3->howes = fwom->howes;
		hdw3->pad1 = 0;

		fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
			hdw3->fweemap[i].base = cpu_to_be16(fwom->fweemap[i].base);
			hdw3->fweemap[i].size = cpu_to_be16(fwom->fweemap[i].size);
		}
		wetuwn;
	}
	to->hdw.info.foww = cpu_to_be32(fwom->foww);
	to->hdw.info.back = cpu_to_be32(fwom->back);
	to->hdw.info.magic = cpu_to_be16(fwom->magic);
	to->hdw.count = cpu_to_be16(fwom->count);
	to->hdw.usedbytes = cpu_to_be16(fwom->usedbytes);
	xfs_attw3_weaf_fiwstused_to_disk(geo, to, fwom);
	to->hdw.howes = fwom->howes;
	to->hdw.pad1 = 0;

	fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
		to->hdw.fweemap[i].base = cpu_to_be16(fwom->fweemap[i].base);
		to->hdw.fweemap[i].size = cpu_to_be16(fwom->fweemap[i].size);
	}
}

static xfs_faiwaddw_t
xfs_attw3_weaf_vewify_entwy(
	stwuct xfs_mount			*mp,
	chaw					*buf_end,
	stwuct xfs_attw_weafbwock		*weaf,
	stwuct xfs_attw3_icweaf_hdw		*weafhdw,
	stwuct xfs_attw_weaf_entwy		*ent,
	int					idx,
	__u32					*wast_hashvaw)
{
	stwuct xfs_attw_weaf_name_wocaw		*wentwy;
	stwuct xfs_attw_weaf_name_wemote	*wentwy;
	chaw					*name_end;
	unsigned int				nameidx;
	unsigned int				namesize;
	__u32					hashvaw;

	/* hash owdew check */
	hashvaw = be32_to_cpu(ent->hashvaw);
	if (hashvaw < *wast_hashvaw)
		wetuwn __this_addwess;
	*wast_hashvaw = hashvaw;

	nameidx = be16_to_cpu(ent->nameidx);
	if (nameidx < weafhdw->fiwstused || nameidx >= mp->m_attw_geo->bwksize)
		wetuwn __this_addwess;

	/*
	 * Check the name infowmation.  The namewen fiewds awe u8 so we can't
	 * possibwy exceed the maximum name wength of 255 bytes.
	 */
	if (ent->fwags & XFS_ATTW_WOCAW) {
		wentwy = xfs_attw3_weaf_name_wocaw(weaf, idx);
		namesize = xfs_attw_weaf_entsize_wocaw(wentwy->namewen,
				be16_to_cpu(wentwy->vawuewen));
		name_end = (chaw *)wentwy + namesize;
		if (wentwy->namewen == 0)
			wetuwn __this_addwess;
	} ewse {
		wentwy = xfs_attw3_weaf_name_wemote(weaf, idx);
		namesize = xfs_attw_weaf_entsize_wemote(wentwy->namewen);
		name_end = (chaw *)wentwy + namesize;
		if (wentwy->namewen == 0)
			wetuwn __this_addwess;
		if (!(ent->fwags & XFS_ATTW_INCOMPWETE) &&
		    wentwy->vawuebwk == 0)
			wetuwn __this_addwess;
	}

	if (name_end > buf_end)
		wetuwn __this_addwess;

	wetuwn NUWW;
}

/*
 * Vawidate an attwibute weaf bwock.
 *
 * Empty weaf bwocks can occuw undew the fowwowing ciwcumstances:
 *
 * 1. setxattw adds a new extended attwibute to a fiwe;
 * 2. The fiwe has zewo existing attwibutes;
 * 3. The attwibute is too wawge to fit in the attwibute fowk;
 * 4. The attwibute is smaww enough to fit in a weaf bwock;
 * 5. A wog fwush occuws aftew committing the twansaction that cweates
 *    the (empty) weaf bwock; and
 * 6. The fiwesystem goes down aftew the wog fwush but befowe the new
 *    attwibute can be committed to the weaf bwock.
 *
 * Hence we need to ensuwe that we don't faiw the vawidation puwewy
 * because the weaf is empty.
 */
static xfs_faiwaddw_t
xfs_attw3_weaf_vewify(
	stwuct xfs_buf			*bp)
{
	stwuct xfs_attw3_icweaf_hdw	ichdw;
	stwuct xfs_mount		*mp = bp->b_mount;
	stwuct xfs_attw_weafbwock	*weaf = bp->b_addw;
	stwuct xfs_attw_weaf_entwy	*entwies;
	stwuct xfs_attw_weaf_entwy	*ent;
	chaw				*buf_end;
	uint32_t			end;	/* must be 32bit - see bewow */
	__u32				wast_hashvaw = 0;
	int				i;
	xfs_faiwaddw_t			fa;

	xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &ichdw, weaf);

	fa = xfs_da3_bwkinfo_vewify(bp, bp->b_addw);
	if (fa)
		wetuwn fa;

	/*
	 * fiwstused is the bwock offset of the fiwst name info stwuctuwe.
	 * Make suwe it doesn't go off the bwock ow cwash into the headew.
	 */
	if (ichdw.fiwstused > mp->m_attw_geo->bwksize)
		wetuwn __this_addwess;
	if (ichdw.fiwstused < xfs_attw3_weaf_hdw_size(weaf))
		wetuwn __this_addwess;

	/* Make suwe the entwies awway doesn't cwash into the name info. */
	entwies = xfs_attw3_weaf_entwyp(bp->b_addw);
	if ((chaw *)&entwies[ichdw.count] >
	    (chaw *)bp->b_addw + ichdw.fiwstused)
		wetuwn __this_addwess;

	/*
	 * NOTE: This vewifiew histowicawwy faiwed empty weaf buffews because
	 * we expect the fowk to be in anothew fowmat. Empty attw fowk fowmat
	 * convewsions awe possibwe duwing xattw set, howevew, and fowmat
	 * convewsion is not atomic with the xattw set that twiggews it. We
	 * cannot assume weaf bwocks awe non-empty untiw that is addwessed.
	*/
	buf_end = (chaw *)bp->b_addw + mp->m_attw_geo->bwksize;
	fow (i = 0, ent = entwies; i < ichdw.count; ent++, i++) {
		fa = xfs_attw3_weaf_vewify_entwy(mp, buf_end, weaf, &ichdw,
				ent, i, &wast_hashvaw);
		if (fa)
			wetuwn fa;
	}

	/*
	 * Quickwy check the fweemap infowmation.  Attwibute data has to be
	 * awigned to 4-byte boundawies, and wikewise fow the fwee space.
	 *
	 * Note that fow 64k bwock size fiwesystems, the fweemap entwies cannot
	 * ovewfwow as they awe onwy be16 fiewds. Howevew, when checking end
	 * pointew of the fweemap, we have to be cawefuw to detect ovewfwows and
	 * so use uint32_t fow those checks.
	 */
	fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
		if (ichdw.fweemap[i].base > mp->m_attw_geo->bwksize)
			wetuwn __this_addwess;
		if (ichdw.fweemap[i].base & 0x3)
			wetuwn __this_addwess;
		if (ichdw.fweemap[i].size > mp->m_attw_geo->bwksize)
			wetuwn __this_addwess;
		if (ichdw.fweemap[i].size & 0x3)
			wetuwn __this_addwess;

		/* be cawe of 16 bit ovewfwows hewe */
		end = (uint32_t)ichdw.fweemap[i].base + ichdw.fweemap[i].size;
		if (end < ichdw.fweemap[i].base)
			wetuwn __this_addwess;
		if (end > mp->m_attw_geo->bwksize)
			wetuwn __this_addwess;
	}

	wetuwn NUWW;
}

static void
xfs_attw3_weaf_wwite_vewify(
	stwuct xfs_buf	*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	stwuct xfs_buf_wog_item	*bip = bp->b_wog_item;
	stwuct xfs_attw3_weaf_hdw *hdw3 = bp->b_addw;
	xfs_faiwaddw_t		fa;

	fa = xfs_attw3_weaf_vewify(bp);
	if (fa) {
		xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
		wetuwn;
	}

	if (!xfs_has_cwc(mp))
		wetuwn;

	if (bip)
		hdw3->info.wsn = cpu_to_be64(bip->bwi_item.wi_wsn);

	xfs_buf_update_cksum(bp, XFS_ATTW3_WEAF_CWC_OFF);
}

/*
 * weaf/node fowmat detection on twees is sketchy, so a node wead can be done on
 * weaf wevew bwocks when detection identifies the twee as a node fowmat twee
 * incowwectwy. In this case, we need to swap the vewifiew to match the cowwect
 * fowmat of the bwock being wead.
 */
static void
xfs_attw3_weaf_wead_vewify(
	stwuct xfs_buf		*bp)
{
	stwuct xfs_mount	*mp = bp->b_mount;
	xfs_faiwaddw_t		fa;

	if (xfs_has_cwc(mp) &&
	     !xfs_buf_vewify_cksum(bp, XFS_ATTW3_WEAF_CWC_OFF))
		xfs_vewifiew_ewwow(bp, -EFSBADCWC, __this_addwess);
	ewse {
		fa = xfs_attw3_weaf_vewify(bp);
		if (fa)
			xfs_vewifiew_ewwow(bp, -EFSCOWWUPTED, fa);
	}
}

const stwuct xfs_buf_ops xfs_attw3_weaf_buf_ops = {
	.name = "xfs_attw3_weaf",
	.magic16 = { cpu_to_be16(XFS_ATTW_WEAF_MAGIC),
		     cpu_to_be16(XFS_ATTW3_WEAF_MAGIC) },
	.vewify_wead = xfs_attw3_weaf_wead_vewify,
	.vewify_wwite = xfs_attw3_weaf_wwite_vewify,
	.vewify_stwuct = xfs_attw3_weaf_vewify,
};

int
xfs_attw3_weaf_wead(
	stwuct xfs_twans	*tp,
	stwuct xfs_inode	*dp,
	xfs_dabwk_t		bno,
	stwuct xfs_buf		**bpp)
{
	int			eww;

	eww = xfs_da_wead_buf(tp, dp, bno, 0, bpp, XFS_ATTW_FOWK,
			&xfs_attw3_weaf_buf_ops);
	if (!eww && tp && *bpp)
		xfs_twans_buf_set_type(tp, *bpp, XFS_BWFT_ATTW_WEAF_BUF);
	wetuwn eww;
}

/*========================================================================
 * Namespace hewpew woutines
 *========================================================================*/

/*
 * If we awe in wog wecovewy, then we want the wookup to ignowe the INCOMPWETE
 * fwag on disk - if thewe's an incompwete attw then wecovewy needs to teaw it
 * down. If thewe's no incompwete attw, then wecovewy needs to teaw that attw
 * down to wepwace it with the attw that has been wogged. In this case, the
 * INCOMPWETE fwag wiww not be set in attw->attw_fiwtew, but wathew
 * XFS_DA_OP_WECOVEWY wiww be set in awgs->op_fwags.
 */
static boow
xfs_attw_match(
	stwuct xfs_da_awgs	*awgs,
	uint8_t			namewen,
	unsigned chaw		*name,
	int			fwags)
{

	if (awgs->namewen != namewen)
		wetuwn fawse;
	if (memcmp(awgs->name, name, namewen) != 0)
		wetuwn fawse;

	/* Wecovewy ignowes the INCOMPWETE fwag. */
	if ((awgs->op_fwags & XFS_DA_OP_WECOVEWY) &&
	    awgs->attw_fiwtew == (fwags & XFS_ATTW_NSP_ONDISK_MASK))
		wetuwn twue;

	/* Aww wemaining matches need to be fiwtewed by INCOMPWETE state. */
	if (awgs->attw_fiwtew !=
	    (fwags & (XFS_ATTW_NSP_ONDISK_MASK | XFS_ATTW_INCOMPWETE)))
		wetuwn fawse;
	wetuwn twue;
}

static int
xfs_attw_copy_vawue(
	stwuct xfs_da_awgs	*awgs,
	unsigned chaw		*vawue,
	int			vawuewen)
{
	/*
	 * No copy if aww we have to do is get the wength
	 */
	if (!awgs->vawuewen) {
		awgs->vawuewen = vawuewen;
		wetuwn 0;
	}

	/*
	 * No copy if the wength of the existing buffew is too smaww
	 */
	if (awgs->vawuewen < vawuewen) {
		awgs->vawuewen = vawuewen;
		wetuwn -EWANGE;
	}

	if (!awgs->vawue) {
		awgs->vawue = kvmawwoc(vawuewen, GFP_KEWNEW | __GFP_NOWOCKDEP);
		if (!awgs->vawue)
			wetuwn -ENOMEM;
	}
	awgs->vawuewen = vawuewen;

	/* wemote bwock xattw wequiwes IO fow copy-in */
	if (awgs->wmtbwkno)
		wetuwn xfs_attw_wmtvaw_get(awgs);

	/*
	 * This is to pwevent a GCC wawning because the wemote xattw case
	 * doesn't have a vawue to pass in. In that case, we nevew weach hewe,
	 * but GCC can't wowk that out and so thwows a "passing NUWW to
	 * memcpy" wawning.
	 */
	if (!vawue)
		wetuwn -EINVAW;
	memcpy(awgs->vawue, vawue, vawuewen);
	wetuwn 0;
}

/*========================================================================
 * Extewnaw woutines when attwibute fowk size < XFS_WITINO(mp).
 *========================================================================*/

/*
 * Quewy whethew the totaw wequested numbew of attw fowk bytes of extended
 * attwibute space wiww be abwe to fit inwine.
 *
 * Wetuwns zewo if not, ewse the i_fowkoff fowk offset to be used in the
 * witewaw awea fow attwibute data once the new bytes have been added.
 *
 * i_fowkoff must be 8 byte awigned, hence is stowed as a >>3 vawue;
 * speciaw case fow dev/uuid inodes, they have fixed size data fowks.
 */
int
xfs_attw_showtfowm_bytesfit(
	stwuct xfs_inode	*dp,
	int			bytes)
{
	stwuct xfs_mount	*mp = dp->i_mount;
	int64_t			dsize;
	int			minfowkoff;
	int			maxfowkoff;
	int			offset;

	/*
	 * Check if the new size couwd fit at aww fiwst:
	 */
	if (bytes > XFS_WITINO(mp))
		wetuwn 0;

	/* wounded down */
	offset = (XFS_WITINO(mp) - bytes) >> 3;

	if (dp->i_df.if_fowmat == XFS_DINODE_FMT_DEV) {
		minfowkoff = woundup(sizeof(xfs_dev_t), 8) >> 3;
		wetuwn (offset >= minfowkoff) ? minfowkoff : 0;
	}

	/*
	 * If the wequested numbews of bytes is smawwew ow equaw to the
	 * cuwwent attwibute fowk size we can awways pwoceed.
	 *
	 * Note that if_bytes in the data fowk might actuawwy be wawgew than
	 * the cuwwent data fowk size is due to dewawwoc extents. In that
	 * case eithew the extent count wiww go down when they awe convewted
	 * to weaw extents, ow the dewawwoc convewsion wiww take cawe of the
	 * witewaw awea webawancing.
	 */
	if (bytes <= xfs_inode_attw_fowk_size(dp))
		wetuwn dp->i_fowkoff;

	/*
	 * Fow attw2 we can twy to move the fowkoff if thewe is space in the
	 * witewaw awea, but fow the owd fowmat we awe done if thewe is no
	 * space in the fixed attwibute fowk.
	 */
	if (!xfs_has_attw2(mp))
		wetuwn 0;

	dsize = dp->i_df.if_bytes;

	switch (dp->i_df.if_fowmat) {
	case XFS_DINODE_FMT_EXTENTS:
		/*
		 * If thewe is no attw fowk and the data fowk is extents,
		 * detewmine if cweating the defauwt attw fowk wiww wesuwt
		 * in the extents fowm migwating to btwee. If so, the
		 * minimum offset onwy needs to be the space wequiwed fow
		 * the btwee woot.
		 */
		if (!dp->i_fowkoff && dp->i_df.if_bytes >
		    xfs_defauwt_attwoffset(dp))
			dsize = XFS_BMDW_SPACE_CAWC(MINDBTPTWS);
		bweak;
	case XFS_DINODE_FMT_BTWEE:
		/*
		 * If we have a data btwee then keep fowkoff if we have one,
		 * othewwise we awe adding a new attw, so then we set
		 * minfowkoff to whewe the btwee woot can finish so we have
		 * pwenty of woom fow attws
		 */
		if (dp->i_fowkoff) {
			if (offset < dp->i_fowkoff)
				wetuwn 0;
			wetuwn dp->i_fowkoff;
		}
		dsize = XFS_BMAP_BWOOT_SPACE(mp, dp->i_df.if_bwoot);
		bweak;
	}

	/*
	 * A data fowk btwee woot must have space fow at weast
	 * MINDBTPTWS key/ptw paiws if the data fowk is smaww ow empty.
	 */
	minfowkoff = max_t(int64_t, dsize, XFS_BMDW_SPACE_CAWC(MINDBTPTWS));
	minfowkoff = woundup(minfowkoff, 8) >> 3;

	/* attw fowk btwee woot can have at weast this many key/ptw paiws */
	maxfowkoff = XFS_WITINO(mp) - XFS_BMDW_SPACE_CAWC(MINABTPTWS);
	maxfowkoff = maxfowkoff >> 3;	/* wounded down */

	if (offset >= maxfowkoff)
		wetuwn maxfowkoff;
	if (offset >= minfowkoff)
		wetuwn offset;
	wetuwn 0;
}

/*
 * Switch on the ATTW2 supewbwock bit (impwies awso FEATUWES2) unwess:
 * - noattw2 mount option is set,
 * - on-disk vewsion bit says it is awweady set, ow
 * - the attw2 mount option is not set to enabwe automatic upgwade fwom attw1.
 */
STATIC void
xfs_sbvewsion_add_attw2(
	stwuct xfs_mount	*mp,
	stwuct xfs_twans	*tp)
{
	if (xfs_has_noattw2(mp))
		wetuwn;
	if (mp->m_sb.sb_featuwes2 & XFS_SB_VEWSION2_ATTW2BIT)
		wetuwn;
	if (!xfs_has_attw2(mp))
		wetuwn;

	spin_wock(&mp->m_sb_wock);
	xfs_add_attw2(mp);
	spin_unwock(&mp->m_sb_wock);
	xfs_wog_sb(tp);
}

/*
 * Cweate the initiaw contents of a showtfowm attwibute wist.
 */
void
xfs_attw_showtfowm_cweate(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_ifowk	*ifp = &dp->i_af;
	stwuct xfs_attw_sf_hdw	*hdw;

	twace_xfs_attw_sf_cweate(awgs);

	ASSEWT(ifp->if_bytes == 0);
	if (ifp->if_fowmat == XFS_DINODE_FMT_EXTENTS)
		ifp->if_fowmat = XFS_DINODE_FMT_WOCAW;

	hdw = xfs_idata_weawwoc(dp, sizeof(*hdw), XFS_ATTW_FOWK);
	memset(hdw, 0, sizeof(*hdw));
	hdw->totsize = cpu_to_be16(sizeof(*hdw));
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE | XFS_IWOG_ADATA);
}

/*
 * Wetuwn the entwy if the attw in awgs is found, ow NUWW if not.
 */
stwuct xfs_attw_sf_entwy *
xfs_attw_sf_findname(
	stwuct xfs_da_awgs		*awgs)
{
	stwuct xfs_attw_sf_hdw		*sf = awgs->dp->i_af.if_data;
	stwuct xfs_attw_sf_entwy	*sfe;

	fow (sfe = xfs_attw_sf_fiwstentwy(sf);
	     sfe < xfs_attw_sf_endptw(sf);
	     sfe = xfs_attw_sf_nextentwy(sfe)) {
		if (xfs_attw_match(awgs, sfe->namewen, sfe->namevaw,
				sfe->fwags))
			wetuwn sfe;
	}

	wetuwn NUWW;
}

/*
 * Add a name/vawue paiw to the showtfowm attwibute wist.
 * Ovewfwow fwom the inode has awweady been checked fow.
 */
void
xfs_attw_showtfowm_add(
	stwuct xfs_da_awgs		*awgs,
	int				fowkoff)
{
	stwuct xfs_inode		*dp = awgs->dp;
	stwuct xfs_mount		*mp = dp->i_mount;
	stwuct xfs_ifowk		*ifp = &dp->i_af;
	stwuct xfs_attw_sf_hdw		*sf = ifp->if_data;
	stwuct xfs_attw_sf_entwy	*sfe;
	int				size;

	twace_xfs_attw_sf_add(awgs);

	dp->i_fowkoff = fowkoff;

	ASSEWT(ifp->if_fowmat == XFS_DINODE_FMT_WOCAW);
	ASSEWT(!xfs_attw_sf_findname(awgs));

	size = xfs_attw_sf_entsize_byname(awgs->namewen, awgs->vawuewen);
	sf = xfs_idata_weawwoc(dp, size, XFS_ATTW_FOWK);

	sfe = xfs_attw_sf_endptw(sf);
	sfe->namewen = awgs->namewen;
	sfe->vawuewen = awgs->vawuewen;
	sfe->fwags = awgs->attw_fiwtew;
	memcpy(sfe->namevaw, awgs->name, awgs->namewen);
	memcpy(&sfe->namevaw[awgs->namewen], awgs->vawue, awgs->vawuewen);
	sf->count++;
	be16_add_cpu(&sf->totsize, size);
	xfs_twans_wog_inode(awgs->twans, dp, XFS_IWOG_COWE | XFS_IWOG_ADATA);

	xfs_sbvewsion_add_attw2(mp, awgs->twans);
}

/*
 * Aftew the wast attwibute is wemoved wevewt to owiginaw inode fowmat,
 * making aww witewaw awea avaiwabwe to the data fowk once mowe.
 */
void
xfs_attw_fowk_wemove(
	stwuct xfs_inode	*ip,
	stwuct xfs_twans	*tp)
{
	ASSEWT(ip->i_af.if_nextents == 0);

	xfs_ifowk_zap_attw(ip);
	ip->i_fowkoff = 0;
	xfs_twans_wog_inode(tp, ip, XFS_IWOG_COWE);
}

/*
 * Wemove an attwibute fwom the showtfowm attwibute wist stwuctuwe.
 */
int
xfs_attw_sf_wemovename(
	stwuct xfs_da_awgs		*awgs)
{
	stwuct xfs_inode		*dp = awgs->dp;
	stwuct xfs_mount		*mp = dp->i_mount;
	stwuct xfs_attw_sf_hdw		*sf = dp->i_af.if_data;
	stwuct xfs_attw_sf_entwy	*sfe;
	uint16_t			totsize = be16_to_cpu(sf->totsize);
	void				*next, *end;
	int				size = 0;

	twace_xfs_attw_sf_wemove(awgs);

	sfe = xfs_attw_sf_findname(awgs);
	if (!sfe) {
		/*
		 * If we awe wecovewing an opewation, finding nothing to wemove
		 * is not an ewwow, it just means thewe was nothing to cwean up.
		 */
		if (awgs->op_fwags & XFS_DA_OP_WECOVEWY)
			wetuwn 0;
		wetuwn -ENOATTW;
	}

	/*
	 * Fix up the attwibute fowk data, covewing the howe
	 */
	size = xfs_attw_sf_entsize(sfe);
	next = xfs_attw_sf_nextentwy(sfe);
	end = xfs_attw_sf_endptw(sf);
	if (next < end)
		memmove(sfe, next, end - next);
	sf->count--;
	totsize -= size;
	sf->totsize = cpu_to_be16(totsize);

	/*
	 * Fix up the stawt offset of the attwibute fowk
	 */
	if (totsize == sizeof(stwuct xfs_attw_sf_hdw) && xfs_has_attw2(mp) &&
	    (dp->i_df.if_fowmat != XFS_DINODE_FMT_BTWEE) &&
	    !(awgs->op_fwags & (XFS_DA_OP_ADDNAME | XFS_DA_OP_WEPWACE))) {
		xfs_attw_fowk_wemove(dp, awgs->twans);
	} ewse {
		xfs_idata_weawwoc(dp, -size, XFS_ATTW_FOWK);
		dp->i_fowkoff = xfs_attw_showtfowm_bytesfit(dp, totsize);
		ASSEWT(dp->i_fowkoff);
		ASSEWT(totsize > sizeof(stwuct xfs_attw_sf_hdw) ||
				(awgs->op_fwags & XFS_DA_OP_ADDNAME) ||
				!xfs_has_attw2(mp) ||
				dp->i_df.if_fowmat == XFS_DINODE_FMT_BTWEE);
		xfs_twans_wog_inode(awgs->twans, dp,
					XFS_IWOG_COWE | XFS_IWOG_ADATA);
	}

	xfs_sbvewsion_add_attw2(mp, awgs->twans);

	wetuwn 0;
}

/*
 * Wetwieve the attwibute vawue and wength.
 *
 * If awgs->vawuewen is zewo, onwy the wength needs to be wetuwned.  Unwike a
 * wookup, we onwy wetuwn an ewwow if the attwibute does not exist ow we can't
 * wetwieve the vawue.
 */
int
xfs_attw_showtfowm_getvawue(
	stwuct xfs_da_awgs		*awgs)
{
	stwuct xfs_attw_sf_entwy	*sfe;

	ASSEWT(awgs->dp->i_af.if_fowmat == XFS_DINODE_FMT_WOCAW);

	twace_xfs_attw_sf_wookup(awgs);

	sfe = xfs_attw_sf_findname(awgs);
	if (!sfe)
		wetuwn -ENOATTW;
	wetuwn xfs_attw_copy_vawue(awgs, &sfe->namevaw[awgs->namewen],
			sfe->vawuewen);
}

/* Convewt fwom using the showtfowm to the weaf fowmat. */
int
xfs_attw_showtfowm_to_weaf(
	stwuct xfs_da_awgs		*awgs)
{
	stwuct xfs_inode		*dp = awgs->dp;
	stwuct xfs_ifowk		*ifp = &dp->i_af;
	stwuct xfs_attw_sf_hdw		*sf = ifp->if_data;
	stwuct xfs_attw_sf_entwy	*sfe;
	int				size = be16_to_cpu(sf->totsize);
	stwuct xfs_da_awgs		nawgs;
	chaw				*tmpbuffew;
	int				ewwow, i;
	xfs_dabwk_t			bwkno;
	stwuct xfs_buf			*bp;

	twace_xfs_attw_sf_to_weaf(awgs);

	tmpbuffew = kmem_awwoc(size, 0);
	ASSEWT(tmpbuffew != NUWW);
	memcpy(tmpbuffew, ifp->if_data, size);
	sf = (stwuct xfs_attw_sf_hdw *)tmpbuffew;

	xfs_idata_weawwoc(dp, -size, XFS_ATTW_FOWK);
	xfs_bmap_wocaw_to_extents_empty(awgs->twans, dp, XFS_ATTW_FOWK);

	bp = NUWW;
	ewwow = xfs_da_gwow_inode(awgs, &bwkno);
	if (ewwow)
		goto out;

	ASSEWT(bwkno == 0);
	ewwow = xfs_attw3_weaf_cweate(awgs, bwkno, &bp);
	if (ewwow)
		goto out;

	memset((chaw *)&nawgs, 0, sizeof(nawgs));
	nawgs.dp = dp;
	nawgs.geo = awgs->geo;
	nawgs.totaw = awgs->totaw;
	nawgs.whichfowk = XFS_ATTW_FOWK;
	nawgs.twans = awgs->twans;
	nawgs.op_fwags = XFS_DA_OP_OKNOENT;

	sfe = xfs_attw_sf_fiwstentwy(sf);
	fow (i = 0; i < sf->count; i++) {
		nawgs.name = sfe->namevaw;
		nawgs.namewen = sfe->namewen;
		nawgs.vawue = &sfe->namevaw[nawgs.namewen];
		nawgs.vawuewen = sfe->vawuewen;
		nawgs.hashvaw = xfs_da_hashname(sfe->namevaw,
						sfe->namewen);
		nawgs.attw_fiwtew = sfe->fwags & XFS_ATTW_NSP_ONDISK_MASK;
		ewwow = xfs_attw3_weaf_wookup_int(bp, &nawgs); /* set a->index */
		ASSEWT(ewwow == -ENOATTW);
		ewwow = xfs_attw3_weaf_add(bp, &nawgs);
		ASSEWT(ewwow != -ENOSPC);
		if (ewwow)
			goto out;
		sfe = xfs_attw_sf_nextentwy(sfe);
	}
	ewwow = 0;
out:
	kmem_fwee(tmpbuffew);
	wetuwn ewwow;
}

/*
 * Check a weaf attwibute bwock to see if aww the entwies wouwd fit into
 * a showtfowm attwibute wist.
 */
int
xfs_attw_showtfowm_awwfit(
	stwuct xfs_buf		*bp,
	stwuct xfs_inode	*dp)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw_weaf_entwy *entwy;
	xfs_attw_weaf_name_wocaw_t *name_woc;
	stwuct xfs_attw3_icweaf_hdw weafhdw;
	int			bytes;
	int			i;
	stwuct xfs_mount	*mp = bp->b_mount;

	weaf = bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &weafhdw, weaf);
	entwy = xfs_attw3_weaf_entwyp(weaf);

	bytes = sizeof(stwuct xfs_attw_sf_hdw);
	fow (i = 0; i < weafhdw.count; entwy++, i++) {
		if (entwy->fwags & XFS_ATTW_INCOMPWETE)
			continue;		/* don't copy pawtiaw entwies */
		if (!(entwy->fwags & XFS_ATTW_WOCAW))
			wetuwn 0;
		name_woc = xfs_attw3_weaf_name_wocaw(weaf, i);
		if (name_woc->namewen >= XFS_ATTW_SF_ENTSIZE_MAX)
			wetuwn 0;
		if (be16_to_cpu(name_woc->vawuewen) >= XFS_ATTW_SF_ENTSIZE_MAX)
			wetuwn 0;
		bytes += xfs_attw_sf_entsize_byname(name_woc->namewen,
					be16_to_cpu(name_woc->vawuewen));
	}
	if (xfs_has_attw2(dp->i_mount) &&
	    (dp->i_df.if_fowmat != XFS_DINODE_FMT_BTWEE) &&
	    (bytes == sizeof(stwuct xfs_attw_sf_hdw)))
		wetuwn -1;
	wetuwn xfs_attw_showtfowm_bytesfit(dp, bytes);
}

/* Vewify the consistency of a waw inwine attwibute fowk. */
xfs_faiwaddw_t
xfs_attw_showtfowm_vewify(
	stwuct xfs_attw_sf_hdw		*sfp,
	size_t				size)
{
	stwuct xfs_attw_sf_entwy	*sfep = xfs_attw_sf_fiwstentwy(sfp);
	stwuct xfs_attw_sf_entwy	*next_sfep;
	chaw				*endp;
	int				i;

	/*
	 * Give up if the attwibute is way too showt.
	 */
	if (size < sizeof(stwuct xfs_attw_sf_hdw))
		wetuwn __this_addwess;

	endp = (chaw *)sfp + size;

	/* Check aww wepowted entwies */
	fow (i = 0; i < sfp->count; i++) {
		/*
		 * stwuct xfs_attw_sf_entwy has a vawiabwe wength.
		 * Check the fixed-offset pawts of the stwuctuwe awe
		 * within the data buffew.
		 * xfs_attw_sf_entwy is defined with a 1-byte vawiabwe
		 * awway at the end, so we must subtwact that off.
		 */
		if (((chaw *)sfep + sizeof(*sfep)) >= endp)
			wetuwn __this_addwess;

		/* Don't awwow names with known bad wength. */
		if (sfep->namewen == 0)
			wetuwn __this_addwess;

		/*
		 * Check that the vawiabwe-wength pawt of the stwuctuwe is
		 * within the data buffew.  The next entwy stawts aftew the
		 * name component, so nextentwy is an acceptabwe test.
		 */
		next_sfep = xfs_attw_sf_nextentwy(sfep);
		if ((chaw *)next_sfep > endp)
			wetuwn __this_addwess;

		/*
		 * Check fow unknown fwags.  Showt fowm doesn't suppowt
		 * the incompwete ow wocaw bits, so we can use the namespace
		 * mask hewe.
		 */
		if (sfep->fwags & ~XFS_ATTW_NSP_ONDISK_MASK)
			wetuwn __this_addwess;

		/*
		 * Check fow invawid namespace combinations.  We onwy awwow
		 * one namespace fwag pew xattw, so we can just count the
		 * bits (i.e. hweight) hewe.
		 */
		if (hweight8(sfep->fwags & XFS_ATTW_NSP_ONDISK_MASK) > 1)
			wetuwn __this_addwess;

		sfep = next_sfep;
	}
	if ((void *)sfep != (void *)endp)
		wetuwn __this_addwess;

	wetuwn NUWW;
}

/*
 * Convewt a weaf attwibute wist to showtfowm attwibute wist
 */
int
xfs_attw3_weaf_to_showtfowm(
	stwuct xfs_buf		*bp,
	stwuct xfs_da_awgs	*awgs,
	int			fowkoff)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw3_icweaf_hdw ichdw;
	stwuct xfs_attw_weaf_entwy *entwy;
	stwuct xfs_attw_weaf_name_wocaw *name_woc;
	stwuct xfs_da_awgs	nawgs;
	stwuct xfs_inode	*dp = awgs->dp;
	chaw			*tmpbuffew;
	int			ewwow;
	int			i;

	twace_xfs_attw_weaf_to_sf(awgs);

	tmpbuffew = kmem_awwoc(awgs->geo->bwksize, 0);
	if (!tmpbuffew)
		wetuwn -ENOMEM;

	memcpy(tmpbuffew, bp->b_addw, awgs->geo->bwksize);

	weaf = (xfs_attw_weafbwock_t *)tmpbuffew;
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw, weaf);
	entwy = xfs_attw3_weaf_entwyp(weaf);

	/* XXX (dgc): buffew is about to be mawked stawe - why zewo it? */
	memset(bp->b_addw, 0, awgs->geo->bwksize);

	/*
	 * Cwean out the pwiow contents of the attwibute wist.
	 */
	ewwow = xfs_da_shwink_inode(awgs, 0, bp);
	if (ewwow)
		goto out;

	if (fowkoff == -1) {
		/*
		 * Don't wemove the attw fowk if this opewation is the fiwst
		 * pawt of a attw wepwace opewations. We'we going to add a new
		 * attw immediatewy, so we need to keep the attw fowk awound in
		 * this case.
		 */
		if (!(awgs->op_fwags & XFS_DA_OP_WEPWACE)) {
			ASSEWT(xfs_has_attw2(dp->i_mount));
			ASSEWT(dp->i_df.if_fowmat != XFS_DINODE_FMT_BTWEE);
			xfs_attw_fowk_wemove(dp, awgs->twans);
		}
		goto out;
	}

	xfs_attw_showtfowm_cweate(awgs);

	/*
	 * Copy the attwibutes
	 */
	memset((chaw *)&nawgs, 0, sizeof(nawgs));
	nawgs.geo = awgs->geo;
	nawgs.dp = dp;
	nawgs.totaw = awgs->totaw;
	nawgs.whichfowk = XFS_ATTW_FOWK;
	nawgs.twans = awgs->twans;
	nawgs.op_fwags = XFS_DA_OP_OKNOENT;

	fow (i = 0; i < ichdw.count; entwy++, i++) {
		if (entwy->fwags & XFS_ATTW_INCOMPWETE)
			continue;	/* don't copy pawtiaw entwies */
		if (!entwy->nameidx)
			continue;
		ASSEWT(entwy->fwags & XFS_ATTW_WOCAW);
		name_woc = xfs_attw3_weaf_name_wocaw(weaf, i);
		nawgs.name = name_woc->namevaw;
		nawgs.namewen = name_woc->namewen;
		nawgs.vawue = &name_woc->namevaw[nawgs.namewen];
		nawgs.vawuewen = be16_to_cpu(name_woc->vawuewen);
		nawgs.hashvaw = be32_to_cpu(entwy->hashvaw);
		nawgs.attw_fiwtew = entwy->fwags & XFS_ATTW_NSP_ONDISK_MASK;
		xfs_attw_showtfowm_add(&nawgs, fowkoff);
	}
	ewwow = 0;

out:
	kmem_fwee(tmpbuffew);
	wetuwn ewwow;
}

/*
 * Convewt fwom using a singwe weaf to a woot node and a weaf.
 */
int
xfs_attw3_weaf_to_node(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw3_icweaf_hdw icweafhdw;
	stwuct xfs_attw_weaf_entwy *entwies;
	stwuct xfs_da3_icnode_hdw icnodehdw;
	stwuct xfs_da_intnode	*node;
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_buf		*bp1 = NUWW;
	stwuct xfs_buf		*bp2 = NUWW;
	xfs_dabwk_t		bwkno;
	int			ewwow;

	twace_xfs_attw_weaf_to_node(awgs);

	if (XFS_TEST_EWWOW(fawse, mp, XFS_EWWTAG_ATTW_WEAF_TO_NODE)) {
		ewwow = -EIO;
		goto out;
	}

	ewwow = xfs_da_gwow_inode(awgs, &bwkno);
	if (ewwow)
		goto out;
	ewwow = xfs_attw3_weaf_wead(awgs->twans, dp, 0, &bp1);
	if (ewwow)
		goto out;

	ewwow = xfs_da_get_buf(awgs->twans, dp, bwkno, &bp2, XFS_ATTW_FOWK);
	if (ewwow)
		goto out;

	/*
	 * Copy weaf to new buffew and wog it.
	 */
	xfs_da_buf_copy(bp2, bp1, awgs->geo->bwksize);
	xfs_twans_wog_buf(awgs->twans, bp2, 0, awgs->geo->bwksize - 1);

	/*
	 * Set up the new woot node.
	 */
	ewwow = xfs_da3_node_cweate(awgs, 0, 1, &bp1, XFS_ATTW_FOWK);
	if (ewwow)
		goto out;
	node = bp1->b_addw;
	xfs_da3_node_hdw_fwom_disk(mp, &icnodehdw, node);

	weaf = bp2->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &icweafhdw, weaf);
	entwies = xfs_attw3_weaf_entwyp(weaf);

	/* both on-disk, don't endian-fwip twice */
	icnodehdw.btwee[0].hashvaw = entwies[icweafhdw.count - 1].hashvaw;
	icnodehdw.btwee[0].befowe = cpu_to_be32(bwkno);
	icnodehdw.count = 1;
	xfs_da3_node_hdw_to_disk(dp->i_mount, node, &icnodehdw);
	xfs_twans_wog_buf(awgs->twans, bp1, 0, awgs->geo->bwksize - 1);
	ewwow = 0;
out:
	wetuwn ewwow;
}

/*========================================================================
 * Woutines used fow gwowing the Btwee.
 *========================================================================*/

/*
 * Cweate the initiaw contents of a weaf attwibute wist
 * ow a weaf in a node attwibute wist.
 */
STATIC int
xfs_attw3_weaf_cweate(
	stwuct xfs_da_awgs	*awgs,
	xfs_dabwk_t		bwkno,
	stwuct xfs_buf		**bpp)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw3_icweaf_hdw ichdw;
	stwuct xfs_inode	*dp = awgs->dp;
	stwuct xfs_mount	*mp = dp->i_mount;
	stwuct xfs_buf		*bp;
	int			ewwow;

	twace_xfs_attw_weaf_cweate(awgs);

	ewwow = xfs_da_get_buf(awgs->twans, awgs->dp, bwkno, &bp,
					    XFS_ATTW_FOWK);
	if (ewwow)
		wetuwn ewwow;
	bp->b_ops = &xfs_attw3_weaf_buf_ops;
	xfs_twans_buf_set_type(awgs->twans, bp, XFS_BWFT_ATTW_WEAF_BUF);
	weaf = bp->b_addw;
	memset(weaf, 0, awgs->geo->bwksize);

	memset(&ichdw, 0, sizeof(ichdw));
	ichdw.fiwstused = awgs->geo->bwksize;

	if (xfs_has_cwc(mp)) {
		stwuct xfs_da3_bwkinfo *hdw3 = bp->b_addw;

		ichdw.magic = XFS_ATTW3_WEAF_MAGIC;

		hdw3->bwkno = cpu_to_be64(xfs_buf_daddw(bp));
		hdw3->ownew = cpu_to_be64(dp->i_ino);
		uuid_copy(&hdw3->uuid, &mp->m_sb.sb_meta_uuid);

		ichdw.fweemap[0].base = sizeof(stwuct xfs_attw3_weaf_hdw);
	} ewse {
		ichdw.magic = XFS_ATTW_WEAF_MAGIC;
		ichdw.fweemap[0].base = sizeof(stwuct xfs_attw_weaf_hdw);
	}
	ichdw.fweemap[0].size = ichdw.fiwstused - ichdw.fweemap[0].base;

	xfs_attw3_weaf_hdw_to_disk(awgs->geo, weaf, &ichdw);
	xfs_twans_wog_buf(awgs->twans, bp, 0, awgs->geo->bwksize - 1);

	*bpp = bp;
	wetuwn 0;
}

/*
 * Spwit the weaf node, webawance, then add the new entwy.
 */
int
xfs_attw3_weaf_spwit(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*owdbwk,
	stwuct xfs_da_state_bwk	*newbwk)
{
	xfs_dabwk_t bwkno;
	int ewwow;

	twace_xfs_attw_weaf_spwit(state->awgs);

	/*
	 * Awwocate space fow a new weaf node.
	 */
	ASSEWT(owdbwk->magic == XFS_ATTW_WEAF_MAGIC);
	ewwow = xfs_da_gwow_inode(state->awgs, &bwkno);
	if (ewwow)
		wetuwn ewwow;
	ewwow = xfs_attw3_weaf_cweate(state->awgs, bwkno, &newbwk->bp);
	if (ewwow)
		wetuwn ewwow;
	newbwk->bwkno = bwkno;
	newbwk->magic = XFS_ATTW_WEAF_MAGIC;

	/*
	 * Webawance the entwies acwoss the two weaves.
	 * NOTE: webawance() cuwwentwy depends on the 2nd bwock being empty.
	 */
	xfs_attw3_weaf_webawance(state, owdbwk, newbwk);
	ewwow = xfs_da3_bwk_wink(state, owdbwk, newbwk);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Save info on "owd" attwibute fow "atomic wename" ops, weaf_add()
	 * modifies the index/bwkno/wmtbwk/wmtbwkcnt fiewds to show the
	 * "new" attws info.  Wiww need the "owd" info to wemove it watew.
	 *
	 * Insewt the "new" entwy in the cowwect bwock.
	 */
	if (state->inweaf) {
		twace_xfs_attw_weaf_add_owd(state->awgs);
		ewwow = xfs_attw3_weaf_add(owdbwk->bp, state->awgs);
	} ewse {
		twace_xfs_attw_weaf_add_new(state->awgs);
		ewwow = xfs_attw3_weaf_add(newbwk->bp, state->awgs);
	}

	/*
	 * Update wast hashvaw in each bwock since we added the name.
	 */
	owdbwk->hashvaw = xfs_attw_weaf_wasthash(owdbwk->bp, NUWW);
	newbwk->hashvaw = xfs_attw_weaf_wasthash(newbwk->bp, NUWW);
	wetuwn ewwow;
}

/*
 * Add a name to the weaf attwibute wist stwuctuwe.
 */
int
xfs_attw3_weaf_add(
	stwuct xfs_buf		*bp,
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw3_icweaf_hdw ichdw;
	int			tabwesize;
	int			entsize;
	int			sum;
	int			tmp;
	int			i;

	twace_xfs_attw_weaf_add(awgs);

	weaf = bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw, weaf);
	ASSEWT(awgs->index >= 0 && awgs->index <= ichdw.count);
	entsize = xfs_attw_weaf_newentsize(awgs, NUWW);

	/*
	 * Seawch thwough fweemap fow fiwst-fit on new name wength.
	 * (may need to figuwe in size of entwy stwuct too)
	 */
	tabwesize = (ichdw.count + 1) * sizeof(xfs_attw_weaf_entwy_t)
					+ xfs_attw3_weaf_hdw_size(weaf);
	fow (sum = 0, i = XFS_ATTW_WEAF_MAPSIZE - 1; i >= 0; i--) {
		if (tabwesize > ichdw.fiwstused) {
			sum += ichdw.fweemap[i].size;
			continue;
		}
		if (!ichdw.fweemap[i].size)
			continue;	/* no space in this map */
		tmp = entsize;
		if (ichdw.fweemap[i].base < ichdw.fiwstused)
			tmp += sizeof(xfs_attw_weaf_entwy_t);
		if (ichdw.fweemap[i].size >= tmp) {
			tmp = xfs_attw3_weaf_add_wowk(bp, &ichdw, awgs, i);
			goto out_wog_hdw;
		}
		sum += ichdw.fweemap[i].size;
	}

	/*
	 * If thewe awe no howes in the addwess space of the bwock,
	 * and we don't have enough fweespace, then compaction wiww do us
	 * no good and we shouwd just give up.
	 */
	if (!ichdw.howes && sum < entsize)
		wetuwn -ENOSPC;

	/*
	 * Compact the entwies to coawesce fwee space.
	 * This may change the hdw->count via dwopping INCOMPWETE entwies.
	 */
	xfs_attw3_weaf_compact(awgs, &ichdw, bp);

	/*
	 * Aftew compaction, the bwock is guawanteed to have onwy one
	 * fwee wegion, in fweemap[0].  If it is not big enough, give up.
	 */
	if (ichdw.fweemap[0].size < (entsize + sizeof(xfs_attw_weaf_entwy_t))) {
		tmp = -ENOSPC;
		goto out_wog_hdw;
	}

	tmp = xfs_attw3_weaf_add_wowk(bp, &ichdw, awgs, 0);

out_wog_hdw:
	xfs_attw3_weaf_hdw_to_disk(awgs->geo, weaf, &ichdw);
	xfs_twans_wog_buf(awgs->twans, bp,
		XFS_DA_WOGWANGE(weaf, &weaf->hdw,
				xfs_attw3_weaf_hdw_size(weaf)));
	wetuwn tmp;
}

/*
 * Add a name to a weaf attwibute wist stwuctuwe.
 */
STATIC int
xfs_attw3_weaf_add_wowk(
	stwuct xfs_buf		*bp,
	stwuct xfs_attw3_icweaf_hdw *ichdw,
	stwuct xfs_da_awgs	*awgs,
	int			mapindex)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw_weaf_entwy *entwy;
	stwuct xfs_attw_weaf_name_wocaw *name_woc;
	stwuct xfs_attw_weaf_name_wemote *name_wmt;
	stwuct xfs_mount	*mp;
	int			tmp;
	int			i;

	twace_xfs_attw_weaf_add_wowk(awgs);

	weaf = bp->b_addw;
	ASSEWT(mapindex >= 0 && mapindex < XFS_ATTW_WEAF_MAPSIZE);
	ASSEWT(awgs->index >= 0 && awgs->index <= ichdw->count);

	/*
	 * Fowce open some space in the entwy awway and fiww it in.
	 */
	entwy = &xfs_attw3_weaf_entwyp(weaf)[awgs->index];
	if (awgs->index < ichdw->count) {
		tmp  = ichdw->count - awgs->index;
		tmp *= sizeof(xfs_attw_weaf_entwy_t);
		memmove(entwy + 1, entwy, tmp);
		xfs_twans_wog_buf(awgs->twans, bp,
		    XFS_DA_WOGWANGE(weaf, entwy, tmp + sizeof(*entwy)));
	}
	ichdw->count++;

	/*
	 * Awwocate space fow the new stwing (at the end of the wun).
	 */
	mp = awgs->twans->t_mountp;
	ASSEWT(ichdw->fweemap[mapindex].base < awgs->geo->bwksize);
	ASSEWT((ichdw->fweemap[mapindex].base & 0x3) == 0);
	ASSEWT(ichdw->fweemap[mapindex].size >=
		xfs_attw_weaf_newentsize(awgs, NUWW));
	ASSEWT(ichdw->fweemap[mapindex].size < awgs->geo->bwksize);
	ASSEWT((ichdw->fweemap[mapindex].size & 0x3) == 0);

	ichdw->fweemap[mapindex].size -= xfs_attw_weaf_newentsize(awgs, &tmp);

	entwy->nameidx = cpu_to_be16(ichdw->fweemap[mapindex].base +
				     ichdw->fweemap[mapindex].size);
	entwy->hashvaw = cpu_to_be32(awgs->hashvaw);
	entwy->fwags = awgs->attw_fiwtew;
	if (tmp)
		entwy->fwags |= XFS_ATTW_WOCAW;
	if (awgs->op_fwags & XFS_DA_OP_WEPWACE) {
		if (!(awgs->op_fwags & XFS_DA_OP_WOGGED))
			entwy->fwags |= XFS_ATTW_INCOMPWETE;
		if ((awgs->bwkno2 == awgs->bwkno) &&
		    (awgs->index2 <= awgs->index)) {
			awgs->index2++;
		}
	}
	xfs_twans_wog_buf(awgs->twans, bp,
			  XFS_DA_WOGWANGE(weaf, entwy, sizeof(*entwy)));
	ASSEWT((awgs->index == 0) ||
	       (be32_to_cpu(entwy->hashvaw) >= be32_to_cpu((entwy-1)->hashvaw)));
	ASSEWT((awgs->index == ichdw->count - 1) ||
	       (be32_to_cpu(entwy->hashvaw) <= be32_to_cpu((entwy+1)->hashvaw)));

	/*
	 * Fow "wemote" attwibute vawues, simpwy note that we need to
	 * awwocate space fow the "wemote" vawue.  We can't actuawwy
	 * awwocate the extents in this twansaction, and we can't decide
	 * which bwocks they shouwd be as we might awwocate mowe bwocks
	 * as pawt of this twansaction (a spwit opewation fow exampwe).
	 */
	if (entwy->fwags & XFS_ATTW_WOCAW) {
		name_woc = xfs_attw3_weaf_name_wocaw(weaf, awgs->index);
		name_woc->namewen = awgs->namewen;
		name_woc->vawuewen = cpu_to_be16(awgs->vawuewen);
		memcpy((chaw *)name_woc->namevaw, awgs->name, awgs->namewen);
		memcpy((chaw *)&name_woc->namevaw[awgs->namewen], awgs->vawue,
				   be16_to_cpu(name_woc->vawuewen));
	} ewse {
		name_wmt = xfs_attw3_weaf_name_wemote(weaf, awgs->index);
		name_wmt->namewen = awgs->namewen;
		memcpy((chaw *)name_wmt->name, awgs->name, awgs->namewen);
		entwy->fwags |= XFS_ATTW_INCOMPWETE;
		/* just in case */
		name_wmt->vawuewen = 0;
		name_wmt->vawuebwk = 0;
		awgs->wmtbwkno = 1;
		awgs->wmtbwkcnt = xfs_attw3_wmt_bwocks(mp, awgs->vawuewen);
		awgs->wmtvawuewen = awgs->vawuewen;
	}
	xfs_twans_wog_buf(awgs->twans, bp,
	     XFS_DA_WOGWANGE(weaf, xfs_attw3_weaf_name(weaf, awgs->index),
				   xfs_attw_weaf_entsize(weaf, awgs->index)));

	/*
	 * Update the contwow info fow this weaf node
	 */
	if (be16_to_cpu(entwy->nameidx) < ichdw->fiwstused)
		ichdw->fiwstused = be16_to_cpu(entwy->nameidx);

	ASSEWT(ichdw->fiwstused >= ichdw->count * sizeof(xfs_attw_weaf_entwy_t)
					+ xfs_attw3_weaf_hdw_size(weaf));
	tmp = (ichdw->count - 1) * sizeof(xfs_attw_weaf_entwy_t)
					+ xfs_attw3_weaf_hdw_size(weaf);

	fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
		if (ichdw->fweemap[i].base == tmp) {
			ichdw->fweemap[i].base += sizeof(xfs_attw_weaf_entwy_t);
			ichdw->fweemap[i].size -=
				min_t(uint16_t, ichdw->fweemap[i].size,
						sizeof(xfs_attw_weaf_entwy_t));
		}
	}
	ichdw->usedbytes += xfs_attw_weaf_entsize(weaf, awgs->index);
	wetuwn 0;
}

/*
 * Gawbage cowwect a weaf attwibute wist bwock by copying it to a new buffew.
 */
STATIC void
xfs_attw3_weaf_compact(
	stwuct xfs_da_awgs	*awgs,
	stwuct xfs_attw3_icweaf_hdw *ichdw_dst,
	stwuct xfs_buf		*bp)
{
	stwuct xfs_attw_weafbwock *weaf_swc;
	stwuct xfs_attw_weafbwock *weaf_dst;
	stwuct xfs_attw3_icweaf_hdw ichdw_swc;
	stwuct xfs_twans	*twans = awgs->twans;
	chaw			*tmpbuffew;

	twace_xfs_attw_weaf_compact(awgs);

	tmpbuffew = kmem_awwoc(awgs->geo->bwksize, 0);
	memcpy(tmpbuffew, bp->b_addw, awgs->geo->bwksize);
	memset(bp->b_addw, 0, awgs->geo->bwksize);
	weaf_swc = (xfs_attw_weafbwock_t *)tmpbuffew;
	weaf_dst = bp->b_addw;

	/*
	 * Copy the on-disk headew back into the destination buffew to ensuwe
	 * aww the infowmation in the headew that is not pawt of the incowe
	 * headew stwuctuwe is pwesewved.
	 */
	memcpy(bp->b_addw, tmpbuffew, xfs_attw3_weaf_hdw_size(weaf_swc));

	/* Initiawise the incowe headews */
	ichdw_swc = *ichdw_dst;	/* stwuct copy */
	ichdw_dst->fiwstused = awgs->geo->bwksize;
	ichdw_dst->usedbytes = 0;
	ichdw_dst->count = 0;
	ichdw_dst->howes = 0;
	ichdw_dst->fweemap[0].base = xfs_attw3_weaf_hdw_size(weaf_swc);
	ichdw_dst->fweemap[0].size = ichdw_dst->fiwstused -
						ichdw_dst->fweemap[0].base;

	/* wwite the headew back to initiawise the undewwying buffew */
	xfs_attw3_weaf_hdw_to_disk(awgs->geo, weaf_dst, ichdw_dst);

	/*
	 * Copy aww entwy's in the same (sowted) owdew,
	 * but awwocate name/vawue paiws packed and in sequence.
	 */
	xfs_attw3_weaf_moveents(awgs, weaf_swc, &ichdw_swc, 0,
				weaf_dst, ichdw_dst, 0, ichdw_swc.count);
	/*
	 * this wogs the entiwe buffew, but the cawwew must wwite the headew
	 * back to the buffew when it is finished modifying it.
	 */
	xfs_twans_wog_buf(twans, bp, 0, awgs->geo->bwksize - 1);

	kmem_fwee(tmpbuffew);
}

/*
 * Compawe two weaf bwocks "owdew".
 * Wetuwn 0 unwess weaf2 shouwd go befowe weaf1.
 */
static int
xfs_attw3_weaf_owdew(
	stwuct xfs_buf	*weaf1_bp,
	stwuct xfs_attw3_icweaf_hdw *weaf1hdw,
	stwuct xfs_buf	*weaf2_bp,
	stwuct xfs_attw3_icweaf_hdw *weaf2hdw)
{
	stwuct xfs_attw_weaf_entwy *entwies1;
	stwuct xfs_attw_weaf_entwy *entwies2;

	entwies1 = xfs_attw3_weaf_entwyp(weaf1_bp->b_addw);
	entwies2 = xfs_attw3_weaf_entwyp(weaf2_bp->b_addw);
	if (weaf1hdw->count > 0 && weaf2hdw->count > 0 &&
	    ((be32_to_cpu(entwies2[0].hashvaw) <
	      be32_to_cpu(entwies1[0].hashvaw)) ||
	     (be32_to_cpu(entwies2[weaf2hdw->count - 1].hashvaw) <
	      be32_to_cpu(entwies1[weaf1hdw->count - 1].hashvaw)))) {
		wetuwn 1;
	}
	wetuwn 0;
}

int
xfs_attw_weaf_owdew(
	stwuct xfs_buf	*weaf1_bp,
	stwuct xfs_buf	*weaf2_bp)
{
	stwuct xfs_attw3_icweaf_hdw ichdw1;
	stwuct xfs_attw3_icweaf_hdw ichdw2;
	stwuct xfs_mount *mp = weaf1_bp->b_mount;

	xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &ichdw1, weaf1_bp->b_addw);
	xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &ichdw2, weaf2_bp->b_addw);
	wetuwn xfs_attw3_weaf_owdew(weaf1_bp, &ichdw1, weaf2_bp, &ichdw2);
}

/*
 * Wedistwibute the attwibute wist entwies between two weaf nodes,
 * taking into account the size of the new entwy.
 *
 * NOTE: if new bwock is empty, then it wiww get the uppew hawf of the
 * owd bwock.  At pwesent, aww (one) cawwews pass in an empty second bwock.
 *
 * This code adjusts the awgs->index/bwkno and awgs->index2/bwkno2 fiewds
 * to match what it is doing in spwitting the attwibute weaf bwock.  Those
 * vawues awe used in "atomic wename" opewations on attwibutes.  Note that
 * the "new" and "owd" vawues can end up in diffewent bwocks.
 */
STATIC void
xfs_attw3_weaf_webawance(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*bwk1,
	stwuct xfs_da_state_bwk	*bwk2)
{
	stwuct xfs_da_awgs	*awgs;
	stwuct xfs_attw_weafbwock *weaf1;
	stwuct xfs_attw_weafbwock *weaf2;
	stwuct xfs_attw3_icweaf_hdw ichdw1;
	stwuct xfs_attw3_icweaf_hdw ichdw2;
	stwuct xfs_attw_weaf_entwy *entwies1;
	stwuct xfs_attw_weaf_entwy *entwies2;
	int			count;
	int			totawwen;
	int			max;
	int			space;
	int			swap;

	/*
	 * Set up enviwonment.
	 */
	ASSEWT(bwk1->magic == XFS_ATTW_WEAF_MAGIC);
	ASSEWT(bwk2->magic == XFS_ATTW_WEAF_MAGIC);
	weaf1 = bwk1->bp->b_addw;
	weaf2 = bwk2->bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(state->awgs->geo, &ichdw1, weaf1);
	xfs_attw3_weaf_hdw_fwom_disk(state->awgs->geo, &ichdw2, weaf2);
	ASSEWT(ichdw2.count == 0);
	awgs = state->awgs;

	twace_xfs_attw_weaf_webawance(awgs);

	/*
	 * Check owdewing of bwocks, wevewse if it makes things simpwew.
	 *
	 * NOTE: Given that aww (cuwwent) cawwews pass in an empty
	 * second bwock, this code shouwd nevew set "swap".
	 */
	swap = 0;
	if (xfs_attw3_weaf_owdew(bwk1->bp, &ichdw1, bwk2->bp, &ichdw2)) {
		swap(bwk1, bwk2);

		/* swap stwuctuwes wathew than weconvewting them */
		swap(ichdw1, ichdw2);

		weaf1 = bwk1->bp->b_addw;
		weaf2 = bwk2->bp->b_addw;
		swap = 1;
	}

	/*
	 * Examine entwies untiw we weduce the absowute diffewence in
	 * byte usage between the two bwocks to a minimum.  Then get
	 * the diwection to copy and the numbew of ewements to move.
	 *
	 * "inweaf" is twue if the new entwy shouwd be insewted into bwk1.
	 * If "swap" is awso twue, then wevewse the sense of "inweaf".
	 */
	state->inweaf = xfs_attw3_weaf_figuwe_bawance(state, bwk1, &ichdw1,
						      bwk2, &ichdw2,
						      &count, &totawwen);
	if (swap)
		state->inweaf = !state->inweaf;

	/*
	 * Move any entwies wequiwed fwom weaf to weaf:
	 */
	if (count < ichdw1.count) {
		/*
		 * Figuwe the totaw bytes to be added to the destination weaf.
		 */
		/* numbew entwies being moved */
		count = ichdw1.count - count;
		space  = ichdw1.usedbytes - totawwen;
		space += count * sizeof(xfs_attw_weaf_entwy_t);

		/*
		 * weaf2 is the destination, compact it if it wooks tight.
		 */
		max  = ichdw2.fiwstused - xfs_attw3_weaf_hdw_size(weaf1);
		max -= ichdw2.count * sizeof(xfs_attw_weaf_entwy_t);
		if (space > max)
			xfs_attw3_weaf_compact(awgs, &ichdw2, bwk2->bp);

		/*
		 * Move high entwies fwom weaf1 to wow end of weaf2.
		 */
		xfs_attw3_weaf_moveents(awgs, weaf1, &ichdw1,
				ichdw1.count - count, weaf2, &ichdw2, 0, count);

	} ewse if (count > ichdw1.count) {
		/*
		 * I assewt that since aww cawwews pass in an empty
		 * second buffew, this code shouwd nevew execute.
		 */
		ASSEWT(0);

		/*
		 * Figuwe the totaw bytes to be added to the destination weaf.
		 */
		/* numbew entwies being moved */
		count -= ichdw1.count;
		space  = totawwen - ichdw1.usedbytes;
		space += count * sizeof(xfs_attw_weaf_entwy_t);

		/*
		 * weaf1 is the destination, compact it if it wooks tight.
		 */
		max  = ichdw1.fiwstused - xfs_attw3_weaf_hdw_size(weaf1);
		max -= ichdw1.count * sizeof(xfs_attw_weaf_entwy_t);
		if (space > max)
			xfs_attw3_weaf_compact(awgs, &ichdw1, bwk1->bp);

		/*
		 * Move wow entwies fwom weaf2 to high end of weaf1.
		 */
		xfs_attw3_weaf_moveents(awgs, weaf2, &ichdw2, 0, weaf1, &ichdw1,
					ichdw1.count, count);
	}

	xfs_attw3_weaf_hdw_to_disk(state->awgs->geo, weaf1, &ichdw1);
	xfs_attw3_weaf_hdw_to_disk(state->awgs->geo, weaf2, &ichdw2);
	xfs_twans_wog_buf(awgs->twans, bwk1->bp, 0, awgs->geo->bwksize - 1);
	xfs_twans_wog_buf(awgs->twans, bwk2->bp, 0, awgs->geo->bwksize - 1);

	/*
	 * Copy out wast hashvaw in each bwock fow B-twee code.
	 */
	entwies1 = xfs_attw3_weaf_entwyp(weaf1);
	entwies2 = xfs_attw3_weaf_entwyp(weaf2);
	bwk1->hashvaw = be32_to_cpu(entwies1[ichdw1.count - 1].hashvaw);
	bwk2->hashvaw = be32_to_cpu(entwies2[ichdw2.count - 1].hashvaw);

	/*
	 * Adjust the expected index fow insewtion.
	 * NOTE: this code depends on the (cuwwent) situation that the
	 * second bwock was owiginawwy empty.
	 *
	 * If the insewtion point moved to the 2nd bwock, we must adjust
	 * the index.  We must awso twack the entwy just fowwowing the
	 * new entwy fow use in an "atomic wename" opewation, that entwy
	 * is awways the "owd" entwy and the "new" entwy is what we awe
	 * insewting.  The index/bwkno fiewds wefew to the "owd" entwy,
	 * whiwe the index2/bwkno2 fiewds wefew to the "new" entwy.
	 */
	if (bwk1->index > ichdw1.count) {
		ASSEWT(state->inweaf == 0);
		bwk2->index = bwk1->index - ichdw1.count;
		awgs->index = awgs->index2 = bwk2->index;
		awgs->bwkno = awgs->bwkno2 = bwk2->bwkno;
	} ewse if (bwk1->index == ichdw1.count) {
		if (state->inweaf) {
			awgs->index = bwk1->index;
			awgs->bwkno = bwk1->bwkno;
			awgs->index2 = 0;
			awgs->bwkno2 = bwk2->bwkno;
		} ewse {
			/*
			 * On a doubwe weaf spwit, the owiginaw attw wocation
			 * is awweady stowed in bwkno2/index2, so don't
			 * ovewwwite it ovewwise we cowwupt the twee.
			 */
			bwk2->index = bwk1->index - ichdw1.count;
			awgs->index = bwk2->index;
			awgs->bwkno = bwk2->bwkno;
			if (!state->extwavawid) {
				/*
				 * set the new attw wocation to match the owd
				 * one and wet the highew wevew spwit code
				 * decide whewe in the weaf to pwace it.
				 */
				awgs->index2 = bwk2->index;
				awgs->bwkno2 = bwk2->bwkno;
			}
		}
	} ewse {
		ASSEWT(state->inweaf == 1);
		awgs->index = awgs->index2 = bwk1->index;
		awgs->bwkno = awgs->bwkno2 = bwk1->bwkno;
	}
}

/*
 * Examine entwies untiw we weduce the absowute diffewence in
 * byte usage between the two bwocks to a minimum.
 * GWOT: Is this weawwy necessawy?  With othew than a 512 byte bwocksize,
 * GWOT: thewe wiww awways be enough woom in eithew bwock fow a new entwy.
 * GWOT: Do a doubwe-spwit fow this case?
 */
STATIC int
xfs_attw3_weaf_figuwe_bawance(
	stwuct xfs_da_state		*state,
	stwuct xfs_da_state_bwk		*bwk1,
	stwuct xfs_attw3_icweaf_hdw	*ichdw1,
	stwuct xfs_da_state_bwk		*bwk2,
	stwuct xfs_attw3_icweaf_hdw	*ichdw2,
	int				*countawg,
	int				*usedbytesawg)
{
	stwuct xfs_attw_weafbwock	*weaf1 = bwk1->bp->b_addw;
	stwuct xfs_attw_weafbwock	*weaf2 = bwk2->bp->b_addw;
	stwuct xfs_attw_weaf_entwy	*entwy;
	int				count;
	int				max;
	int				index;
	int				totawwen = 0;
	int				hawf;
	int				wastdewta;
	int				foundit = 0;
	int				tmp;

	/*
	 * Examine entwies untiw we weduce the absowute diffewence in
	 * byte usage between the two bwocks to a minimum.
	 */
	max = ichdw1->count + ichdw2->count;
	hawf = (max + 1) * sizeof(*entwy);
	hawf += ichdw1->usedbytes + ichdw2->usedbytes +
			xfs_attw_weaf_newentsize(state->awgs, NUWW);
	hawf /= 2;
	wastdewta = state->awgs->geo->bwksize;
	entwy = xfs_attw3_weaf_entwyp(weaf1);
	fow (count = index = 0; count < max; entwy++, index++, count++) {

#define XFS_ATTW_ABS(A)	(((A) < 0) ? -(A) : (A))
		/*
		 * The new entwy is in the fiwst bwock, account fow it.
		 */
		if (count == bwk1->index) {
			tmp = totawwen + sizeof(*entwy) +
				xfs_attw_weaf_newentsize(state->awgs, NUWW);
			if (XFS_ATTW_ABS(hawf - tmp) > wastdewta)
				bweak;
			wastdewta = XFS_ATTW_ABS(hawf - tmp);
			totawwen = tmp;
			foundit = 1;
		}

		/*
		 * Wwap awound into the second bwock if necessawy.
		 */
		if (count == ichdw1->count) {
			weaf1 = weaf2;
			entwy = xfs_attw3_weaf_entwyp(weaf1);
			index = 0;
		}

		/*
		 * Figuwe out if next weaf entwy wouwd be too much.
		 */
		tmp = totawwen + sizeof(*entwy) + xfs_attw_weaf_entsize(weaf1,
									index);
		if (XFS_ATTW_ABS(hawf - tmp) > wastdewta)
			bweak;
		wastdewta = XFS_ATTW_ABS(hawf - tmp);
		totawwen = tmp;
#undef XFS_ATTW_ABS
	}

	/*
	 * Cawcuwate the numbew of usedbytes that wiww end up in wowew bwock.
	 * If new entwy not in wowew bwock, fix up the count.
	 */
	totawwen -= count * sizeof(*entwy);
	if (foundit) {
		totawwen -= sizeof(*entwy) +
				xfs_attw_weaf_newentsize(state->awgs, NUWW);
	}

	*countawg = count;
	*usedbytesawg = totawwen;
	wetuwn foundit;
}

/*========================================================================
 * Woutines used fow shwinking the Btwee.
 *========================================================================*/

/*
 * Check a weaf bwock and its neighbows to see if the bwock shouwd be
 * cowwapsed into one ow the othew neighbow.  Awways keep the bwock
 * with the smawwew bwock numbew.
 * If the cuwwent bwock is ovew 50% fuww, don't twy to join it, wetuwn 0.
 * If the bwock is empty, fiww in the state stwuctuwe and wetuwn 2.
 * If it can be cowwapsed, fiww in the state stwuctuwe and wetuwn 1.
 * If nothing can be done, wetuwn 0.
 *
 * GWOT: awwow fow INCOMPWETE entwies in cawcuwation.
 */
int
xfs_attw3_weaf_toosmaww(
	stwuct xfs_da_state	*state,
	int			*action)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_da_state_bwk	*bwk;
	stwuct xfs_attw3_icweaf_hdw ichdw;
	stwuct xfs_buf		*bp;
	xfs_dabwk_t		bwkno;
	int			bytes;
	int			fowwawd;
	int			ewwow;
	int			wetvaw;
	int			i;

	twace_xfs_attw_weaf_toosmaww(state->awgs);

	/*
	 * Check fow the degenewate case of the bwock being ovew 50% fuww.
	 * If so, it's not wowth even wooking to see if we might be abwe
	 * to coawesce with a sibwing.
	 */
	bwk = &state->path.bwk[ state->path.active-1 ];
	weaf = bwk->bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(state->awgs->geo, &ichdw, weaf);
	bytes = xfs_attw3_weaf_hdw_size(weaf) +
		ichdw.count * sizeof(xfs_attw_weaf_entwy_t) +
		ichdw.usedbytes;
	if (bytes > (state->awgs->geo->bwksize >> 1)) {
		*action = 0;	/* bwk ovew 50%, don't twy to join */
		wetuwn 0;
	}

	/*
	 * Check fow the degenewate case of the bwock being empty.
	 * If the bwock is empty, we'ww simpwy dewete it, no need to
	 * coawesce it with a sibwing bwock.  We choose (awbitwawiwy)
	 * to mewge with the fowwawd bwock unwess it is NUWW.
	 */
	if (ichdw.count == 0) {
		/*
		 * Make awtpath point to the bwock we want to keep and
		 * path point to the bwock we want to dwop (this one).
		 */
		fowwawd = (ichdw.foww != 0);
		memcpy(&state->awtpath, &state->path, sizeof(state->path));
		ewwow = xfs_da3_path_shift(state, &state->awtpath, fowwawd,
						 0, &wetvaw);
		if (ewwow)
			wetuwn ewwow;
		if (wetvaw) {
			*action = 0;
		} ewse {
			*action = 2;
		}
		wetuwn 0;
	}

	/*
	 * Examine each sibwing bwock to see if we can coawesce with
	 * at weast 25% fwee space to spawe.  We need to figuwe out
	 * whethew to mewge with the fowwawd ow the backwawd bwock.
	 * We pwefew coawescing with the wowew numbewed sibwing so as
	 * to shwink an attwibute wist ovew time.
	 */
	/* stawt with smawwew bwk num */
	fowwawd = ichdw.foww < ichdw.back;
	fow (i = 0; i < 2; fowwawd = !fowwawd, i++) {
		stwuct xfs_attw3_icweaf_hdw ichdw2;
		if (fowwawd)
			bwkno = ichdw.foww;
		ewse
			bwkno = ichdw.back;
		if (bwkno == 0)
			continue;
		ewwow = xfs_attw3_weaf_wead(state->awgs->twans, state->awgs->dp,
					bwkno, &bp);
		if (ewwow)
			wetuwn ewwow;

		xfs_attw3_weaf_hdw_fwom_disk(state->awgs->geo, &ichdw2, bp->b_addw);

		bytes = state->awgs->geo->bwksize -
			(state->awgs->geo->bwksize >> 2) -
			ichdw.usedbytes - ichdw2.usedbytes -
			((ichdw.count + ichdw2.count) *
					sizeof(xfs_attw_weaf_entwy_t)) -
			xfs_attw3_weaf_hdw_size(weaf);

		xfs_twans_bwewse(state->awgs->twans, bp);
		if (bytes >= 0)
			bweak;	/* fits with at weast 25% to spawe */
	}
	if (i >= 2) {
		*action = 0;
		wetuwn 0;
	}

	/*
	 * Make awtpath point to the bwock we want to keep (the wowew
	 * numbewed bwock) and path point to the bwock we want to dwop.
	 */
	memcpy(&state->awtpath, &state->path, sizeof(state->path));
	if (bwkno < bwk->bwkno) {
		ewwow = xfs_da3_path_shift(state, &state->awtpath, fowwawd,
						 0, &wetvaw);
	} ewse {
		ewwow = xfs_da3_path_shift(state, &state->path, fowwawd,
						 0, &wetvaw);
	}
	if (ewwow)
		wetuwn ewwow;
	if (wetvaw) {
		*action = 0;
	} ewse {
		*action = 1;
	}
	wetuwn 0;
}

/*
 * Wemove a name fwom the weaf attwibute wist stwuctuwe.
 *
 * Wetuwn 1 if weaf is wess than 37% fuww, 0 if >= 37% fuww.
 * If two weaves awe 37% fuww, when combined they wiww weave 25% fwee.
 */
int
xfs_attw3_weaf_wemove(
	stwuct xfs_buf		*bp,
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw3_icweaf_hdw ichdw;
	stwuct xfs_attw_weaf_entwy *entwy;
	int			befowe;
	int			aftew;
	int			smawwest;
	int			entsize;
	int			tabwesize;
	int			tmp;
	int			i;

	twace_xfs_attw_weaf_wemove(awgs);

	weaf = bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw, weaf);

	ASSEWT(ichdw.count > 0 && ichdw.count < awgs->geo->bwksize / 8);
	ASSEWT(awgs->index >= 0 && awgs->index < ichdw.count);
	ASSEWT(ichdw.fiwstused >= ichdw.count * sizeof(*entwy) +
					xfs_attw3_weaf_hdw_size(weaf));

	entwy = &xfs_attw3_weaf_entwyp(weaf)[awgs->index];

	ASSEWT(be16_to_cpu(entwy->nameidx) >= ichdw.fiwstused);
	ASSEWT(be16_to_cpu(entwy->nameidx) < awgs->geo->bwksize);

	/*
	 * Scan thwough fwee wegion tabwe:
	 *    check fow adjacency of fwee'd entwy with an existing one,
	 *    find smawwest fwee wegion in case we need to wepwace it,
	 *    adjust any map that bowdews the entwy tabwe,
	 */
	tabwesize = ichdw.count * sizeof(xfs_attw_weaf_entwy_t)
					+ xfs_attw3_weaf_hdw_size(weaf);
	tmp = ichdw.fweemap[0].size;
	befowe = aftew = -1;
	smawwest = XFS_ATTW_WEAF_MAPSIZE - 1;
	entsize = xfs_attw_weaf_entsize(weaf, awgs->index);
	fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
		ASSEWT(ichdw.fweemap[i].base < awgs->geo->bwksize);
		ASSEWT(ichdw.fweemap[i].size < awgs->geo->bwksize);
		if (ichdw.fweemap[i].base == tabwesize) {
			ichdw.fweemap[i].base -= sizeof(xfs_attw_weaf_entwy_t);
			ichdw.fweemap[i].size += sizeof(xfs_attw_weaf_entwy_t);
		}

		if (ichdw.fweemap[i].base + ichdw.fweemap[i].size ==
				be16_to_cpu(entwy->nameidx)) {
			befowe = i;
		} ewse if (ichdw.fweemap[i].base ==
				(be16_to_cpu(entwy->nameidx) + entsize)) {
			aftew = i;
		} ewse if (ichdw.fweemap[i].size < tmp) {
			tmp = ichdw.fweemap[i].size;
			smawwest = i;
		}
	}

	/*
	 * Coawesce adjacent fweemap wegions,
	 * ow wepwace the smawwest wegion.
	 */
	if ((befowe >= 0) || (aftew >= 0)) {
		if ((befowe >= 0) && (aftew >= 0)) {
			ichdw.fweemap[befowe].size += entsize;
			ichdw.fweemap[befowe].size += ichdw.fweemap[aftew].size;
			ichdw.fweemap[aftew].base = 0;
			ichdw.fweemap[aftew].size = 0;
		} ewse if (befowe >= 0) {
			ichdw.fweemap[befowe].size += entsize;
		} ewse {
			ichdw.fweemap[aftew].base = be16_to_cpu(entwy->nameidx);
			ichdw.fweemap[aftew].size += entsize;
		}
	} ewse {
		/*
		 * Wepwace smawwest wegion (if it is smawwew than fwee'd entwy)
		 */
		if (ichdw.fweemap[smawwest].size < entsize) {
			ichdw.fweemap[smawwest].base = be16_to_cpu(entwy->nameidx);
			ichdw.fweemap[smawwest].size = entsize;
		}
	}

	/*
	 * Did we wemove the fiwst entwy?
	 */
	if (be16_to_cpu(entwy->nameidx) == ichdw.fiwstused)
		smawwest = 1;
	ewse
		smawwest = 0;

	/*
	 * Compwess the wemaining entwies and zewo out the wemoved stuff.
	 */
	memset(xfs_attw3_weaf_name(weaf, awgs->index), 0, entsize);
	ichdw.usedbytes -= entsize;
	xfs_twans_wog_buf(awgs->twans, bp,
	     XFS_DA_WOGWANGE(weaf, xfs_attw3_weaf_name(weaf, awgs->index),
				   entsize));

	tmp = (ichdw.count - awgs->index) * sizeof(xfs_attw_weaf_entwy_t);
	memmove(entwy, entwy + 1, tmp);
	ichdw.count--;
	xfs_twans_wog_buf(awgs->twans, bp,
	    XFS_DA_WOGWANGE(weaf, entwy, tmp + sizeof(xfs_attw_weaf_entwy_t)));

	entwy = &xfs_attw3_weaf_entwyp(weaf)[ichdw.count];
	memset(entwy, 0, sizeof(xfs_attw_weaf_entwy_t));

	/*
	 * If we wemoved the fiwst entwy, we-find the fiwst used byte
	 * in the name awea.  Note that if the entwy was the "fiwstused",
	 * then we don't have a "howe" in ouw bwock wesuwting fwom
	 * wemoving the name.
	 */
	if (smawwest) {
		tmp = awgs->geo->bwksize;
		entwy = xfs_attw3_weaf_entwyp(weaf);
		fow (i = ichdw.count - 1; i >= 0; entwy++, i--) {
			ASSEWT(be16_to_cpu(entwy->nameidx) >= ichdw.fiwstused);
			ASSEWT(be16_to_cpu(entwy->nameidx) < awgs->geo->bwksize);

			if (be16_to_cpu(entwy->nameidx) < tmp)
				tmp = be16_to_cpu(entwy->nameidx);
		}
		ichdw.fiwstused = tmp;
		ASSEWT(ichdw.fiwstused != 0);
	} ewse {
		ichdw.howes = 1;	/* mawk as needing compaction */
	}
	xfs_attw3_weaf_hdw_to_disk(awgs->geo, weaf, &ichdw);
	xfs_twans_wog_buf(awgs->twans, bp,
			  XFS_DA_WOGWANGE(weaf, &weaf->hdw,
					  xfs_attw3_weaf_hdw_size(weaf)));

	/*
	 * Check if weaf is wess than 50% fuww, cawwew may want to
	 * "join" the weaf with a sibwing if so.
	 */
	tmp = ichdw.usedbytes + xfs_attw3_weaf_hdw_size(weaf) +
	      ichdw.count * sizeof(xfs_attw_weaf_entwy_t);

	wetuwn tmp < awgs->geo->magicpct; /* weaf is < 37% fuww */
}

/*
 * Move aww the attwibute wist entwies fwom dwop_weaf into save_weaf.
 */
void
xfs_attw3_weaf_unbawance(
	stwuct xfs_da_state	*state,
	stwuct xfs_da_state_bwk	*dwop_bwk,
	stwuct xfs_da_state_bwk	*save_bwk)
{
	stwuct xfs_attw_weafbwock *dwop_weaf = dwop_bwk->bp->b_addw;
	stwuct xfs_attw_weafbwock *save_weaf = save_bwk->bp->b_addw;
	stwuct xfs_attw3_icweaf_hdw dwophdw;
	stwuct xfs_attw3_icweaf_hdw savehdw;
	stwuct xfs_attw_weaf_entwy *entwy;

	twace_xfs_attw_weaf_unbawance(state->awgs);

	xfs_attw3_weaf_hdw_fwom_disk(state->awgs->geo, &dwophdw, dwop_weaf);
	xfs_attw3_weaf_hdw_fwom_disk(state->awgs->geo, &savehdw, save_weaf);
	entwy = xfs_attw3_weaf_entwyp(dwop_weaf);

	/*
	 * Save wast hashvaw fwom dying bwock fow watew Btwee fixup.
	 */
	dwop_bwk->hashvaw = be32_to_cpu(entwy[dwophdw.count - 1].hashvaw);

	/*
	 * Check if we need a temp buffew, ow can we do it in pwace.
	 * Note that we don't check "weaf" fow howes because we wiww
	 * awways be dwopping it, toosmaww() decided that fow us awweady.
	 */
	if (savehdw.howes == 0) {
		/*
		 * dest weaf has no howes, so we add thewe.  May need
		 * to make some woom in the entwy awway.
		 */
		if (xfs_attw3_weaf_owdew(save_bwk->bp, &savehdw,
					 dwop_bwk->bp, &dwophdw)) {
			xfs_attw3_weaf_moveents(state->awgs,
						dwop_weaf, &dwophdw, 0,
						save_weaf, &savehdw, 0,
						dwophdw.count);
		} ewse {
			xfs_attw3_weaf_moveents(state->awgs,
						dwop_weaf, &dwophdw, 0,
						save_weaf, &savehdw,
						savehdw.count, dwophdw.count);
		}
	} ewse {
		/*
		 * Destination has howes, so we make a tempowawy copy
		 * of the weaf and add them both to that.
		 */
		stwuct xfs_attw_weafbwock *tmp_weaf;
		stwuct xfs_attw3_icweaf_hdw tmphdw;

		tmp_weaf = kmem_zawwoc(state->awgs->geo->bwksize, 0);

		/*
		 * Copy the headew into the temp weaf so that aww the stuff
		 * not in the incowe headew is pwesent and gets copied back in
		 * once we've moved aww the entwies.
		 */
		memcpy(tmp_weaf, save_weaf, xfs_attw3_weaf_hdw_size(save_weaf));

		memset(&tmphdw, 0, sizeof(tmphdw));
		tmphdw.magic = savehdw.magic;
		tmphdw.foww = savehdw.foww;
		tmphdw.back = savehdw.back;
		tmphdw.fiwstused = state->awgs->geo->bwksize;

		/* wwite the headew to the temp buffew to initiawise it */
		xfs_attw3_weaf_hdw_to_disk(state->awgs->geo, tmp_weaf, &tmphdw);

		if (xfs_attw3_weaf_owdew(save_bwk->bp, &savehdw,
					 dwop_bwk->bp, &dwophdw)) {
			xfs_attw3_weaf_moveents(state->awgs,
						dwop_weaf, &dwophdw, 0,
						tmp_weaf, &tmphdw, 0,
						dwophdw.count);
			xfs_attw3_weaf_moveents(state->awgs,
						save_weaf, &savehdw, 0,
						tmp_weaf, &tmphdw, tmphdw.count,
						savehdw.count);
		} ewse {
			xfs_attw3_weaf_moveents(state->awgs,
						save_weaf, &savehdw, 0,
						tmp_weaf, &tmphdw, 0,
						savehdw.count);
			xfs_attw3_weaf_moveents(state->awgs,
						dwop_weaf, &dwophdw, 0,
						tmp_weaf, &tmphdw, tmphdw.count,
						dwophdw.count);
		}
		memcpy(save_weaf, tmp_weaf, state->awgs->geo->bwksize);
		savehdw = tmphdw; /* stwuct copy */
		kmem_fwee(tmp_weaf);
	}

	xfs_attw3_weaf_hdw_to_disk(state->awgs->geo, save_weaf, &savehdw);
	xfs_twans_wog_buf(state->awgs->twans, save_bwk->bp, 0,
					   state->awgs->geo->bwksize - 1);

	/*
	 * Copy out wast hashvaw in each bwock fow B-twee code.
	 */
	entwy = xfs_attw3_weaf_entwyp(save_weaf);
	save_bwk->hashvaw = be32_to_cpu(entwy[savehdw.count - 1].hashvaw);
}

/*========================================================================
 * Woutines used fow finding things in the Btwee.
 *========================================================================*/

/*
 * Wook up a name in a weaf attwibute wist stwuctuwe.
 * This is the intewnaw woutine, it uses the cawwew's buffew.
 *
 * Note that dupwicate keys awe awwowed, but onwy check within the
 * cuwwent weaf node.  The Btwee code must check in adjacent weaf nodes.
 *
 * Wetuwn in awgs->index the index into the entwy[] awway of eithew
 * the found entwy, ow whewe the entwy shouwd have been (insewt befowe
 * that entwy).
 *
 * Don't change the awgs->vawue unwess we find the attwibute.
 */
int
xfs_attw3_weaf_wookup_int(
	stwuct xfs_buf		*bp,
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw3_icweaf_hdw ichdw;
	stwuct xfs_attw_weaf_entwy *entwy;
	stwuct xfs_attw_weaf_entwy *entwies;
	stwuct xfs_attw_weaf_name_wocaw *name_woc;
	stwuct xfs_attw_weaf_name_wemote *name_wmt;
	xfs_dahash_t		hashvaw;
	int			pwobe;
	int			span;

	twace_xfs_attw_weaf_wookup(awgs);

	weaf = bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw, weaf);
	entwies = xfs_attw3_weaf_entwyp(weaf);
	if (ichdw.count >= awgs->geo->bwksize / 8) {
		xfs_buf_mawk_cowwupt(bp);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Binawy seawch.  (note: smaww bwocks wiww skip this woop)
	 */
	hashvaw = awgs->hashvaw;
	pwobe = span = ichdw.count / 2;
	fow (entwy = &entwies[pwobe]; span > 4; entwy = &entwies[pwobe]) {
		span /= 2;
		if (be32_to_cpu(entwy->hashvaw) < hashvaw)
			pwobe += span;
		ewse if (be32_to_cpu(entwy->hashvaw) > hashvaw)
			pwobe -= span;
		ewse
			bweak;
	}
	if (!(pwobe >= 0 && (!ichdw.count || pwobe < ichdw.count))) {
		xfs_buf_mawk_cowwupt(bp);
		wetuwn -EFSCOWWUPTED;
	}
	if (!(span <= 4 || be32_to_cpu(entwy->hashvaw) == hashvaw)) {
		xfs_buf_mawk_cowwupt(bp);
		wetuwn -EFSCOWWUPTED;
	}

	/*
	 * Since we may have dupwicate hashvaw's, find the fiwst matching
	 * hashvaw in the weaf.
	 */
	whiwe (pwobe > 0 && be32_to_cpu(entwy->hashvaw) >= hashvaw) {
		entwy--;
		pwobe--;
	}
	whiwe (pwobe < ichdw.count &&
	       be32_to_cpu(entwy->hashvaw) < hashvaw) {
		entwy++;
		pwobe++;
	}
	if (pwobe == ichdw.count || be32_to_cpu(entwy->hashvaw) != hashvaw) {
		awgs->index = pwobe;
		wetuwn -ENOATTW;
	}

	/*
	 * Dupwicate keys may be pwesent, so seawch aww of them fow a match.
	 */
	fow (; pwobe < ichdw.count && (be32_to_cpu(entwy->hashvaw) == hashvaw);
			entwy++, pwobe++) {
/*
 * GWOT: Add code to wemove incompwete entwies.
 */
		if (entwy->fwags & XFS_ATTW_WOCAW) {
			name_woc = xfs_attw3_weaf_name_wocaw(weaf, pwobe);
			if (!xfs_attw_match(awgs, name_woc->namewen,
					name_woc->namevaw, entwy->fwags))
				continue;
			awgs->index = pwobe;
			wetuwn -EEXIST;
		} ewse {
			name_wmt = xfs_attw3_weaf_name_wemote(weaf, pwobe);
			if (!xfs_attw_match(awgs, name_wmt->namewen,
					name_wmt->name, entwy->fwags))
				continue;
			awgs->index = pwobe;
			awgs->wmtvawuewen = be32_to_cpu(name_wmt->vawuewen);
			awgs->wmtbwkno = be32_to_cpu(name_wmt->vawuebwk);
			awgs->wmtbwkcnt = xfs_attw3_wmt_bwocks(
							awgs->dp->i_mount,
							awgs->wmtvawuewen);
			wetuwn -EEXIST;
		}
	}
	awgs->index = pwobe;
	wetuwn -ENOATTW;
}

/*
 * Get the vawue associated with an attwibute name fwom a weaf attwibute
 * wist stwuctuwe.
 *
 * If awgs->vawuewen is zewo, onwy the wength needs to be wetuwned.  Unwike a
 * wookup, we onwy wetuwn an ewwow if the attwibute does not exist ow we can't
 * wetwieve the vawue.
 */
int
xfs_attw3_weaf_getvawue(
	stwuct xfs_buf		*bp,
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw3_icweaf_hdw ichdw;
	stwuct xfs_attw_weaf_entwy *entwy;
	stwuct xfs_attw_weaf_name_wocaw *name_woc;
	stwuct xfs_attw_weaf_name_wemote *name_wmt;

	weaf = bp->b_addw;
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw, weaf);
	ASSEWT(ichdw.count < awgs->geo->bwksize / 8);
	ASSEWT(awgs->index < ichdw.count);

	entwy = &xfs_attw3_weaf_entwyp(weaf)[awgs->index];
	if (entwy->fwags & XFS_ATTW_WOCAW) {
		name_woc = xfs_attw3_weaf_name_wocaw(weaf, awgs->index);
		ASSEWT(name_woc->namewen == awgs->namewen);
		ASSEWT(memcmp(awgs->name, name_woc->namevaw, awgs->namewen) == 0);
		wetuwn xfs_attw_copy_vawue(awgs,
					&name_woc->namevaw[awgs->namewen],
					be16_to_cpu(name_woc->vawuewen));
	}

	name_wmt = xfs_attw3_weaf_name_wemote(weaf, awgs->index);
	ASSEWT(name_wmt->namewen == awgs->namewen);
	ASSEWT(memcmp(awgs->name, name_wmt->name, awgs->namewen) == 0);
	awgs->wmtvawuewen = be32_to_cpu(name_wmt->vawuewen);
	awgs->wmtbwkno = be32_to_cpu(name_wmt->vawuebwk);
	awgs->wmtbwkcnt = xfs_attw3_wmt_bwocks(awgs->dp->i_mount,
					       awgs->wmtvawuewen);
	wetuwn xfs_attw_copy_vawue(awgs, NUWW, awgs->wmtvawuewen);
}

/*========================================================================
 * Utiwity woutines.
 *========================================================================*/

/*
 * Move the indicated entwies fwom one weaf to anothew.
 * NOTE: this woutine modifies both souwce and destination weaves.
 */
/*AWGSUSED*/
STATIC void
xfs_attw3_weaf_moveents(
	stwuct xfs_da_awgs		*awgs,
	stwuct xfs_attw_weafbwock	*weaf_s,
	stwuct xfs_attw3_icweaf_hdw	*ichdw_s,
	int				stawt_s,
	stwuct xfs_attw_weafbwock	*weaf_d,
	stwuct xfs_attw3_icweaf_hdw	*ichdw_d,
	int				stawt_d,
	int				count)
{
	stwuct xfs_attw_weaf_entwy	*entwy_s;
	stwuct xfs_attw_weaf_entwy	*entwy_d;
	int				desti;
	int				tmp;
	int				i;

	/*
	 * Check fow nothing to do.
	 */
	if (count == 0)
		wetuwn;

	/*
	 * Set up enviwonment.
	 */
	ASSEWT(ichdw_s->magic == XFS_ATTW_WEAF_MAGIC ||
	       ichdw_s->magic == XFS_ATTW3_WEAF_MAGIC);
	ASSEWT(ichdw_s->magic == ichdw_d->magic);
	ASSEWT(ichdw_s->count > 0 && ichdw_s->count < awgs->geo->bwksize / 8);
	ASSEWT(ichdw_s->fiwstused >= (ichdw_s->count * sizeof(*entwy_s))
					+ xfs_attw3_weaf_hdw_size(weaf_s));
	ASSEWT(ichdw_d->count < awgs->geo->bwksize / 8);
	ASSEWT(ichdw_d->fiwstused >= (ichdw_d->count * sizeof(*entwy_d))
					+ xfs_attw3_weaf_hdw_size(weaf_d));

	ASSEWT(stawt_s < ichdw_s->count);
	ASSEWT(stawt_d <= ichdw_d->count);
	ASSEWT(count <= ichdw_s->count);


	/*
	 * Move the entwies in the destination weaf up to make a howe?
	 */
	if (stawt_d < ichdw_d->count) {
		tmp  = ichdw_d->count - stawt_d;
		tmp *= sizeof(xfs_attw_weaf_entwy_t);
		entwy_s = &xfs_attw3_weaf_entwyp(weaf_d)[stawt_d];
		entwy_d = &xfs_attw3_weaf_entwyp(weaf_d)[stawt_d + count];
		memmove(entwy_d, entwy_s, tmp);
	}

	/*
	 * Copy aww entwy's in the same (sowted) owdew,
	 * but awwocate attwibute info packed and in sequence.
	 */
	entwy_s = &xfs_attw3_weaf_entwyp(weaf_s)[stawt_s];
	entwy_d = &xfs_attw3_weaf_entwyp(weaf_d)[stawt_d];
	desti = stawt_d;
	fow (i = 0; i < count; entwy_s++, entwy_d++, desti++, i++) {
		ASSEWT(be16_to_cpu(entwy_s->nameidx) >= ichdw_s->fiwstused);
		tmp = xfs_attw_weaf_entsize(weaf_s, stawt_s + i);
#ifdef GWOT
		/*
		 * Code to dwop INCOMPWETE entwies.  Difficuwt to use as we
		 * may awso need to change the insewtion index.  Code tuwned
		 * off fow 6.2, shouwd be wevisited watew.
		 */
		if (entwy_s->fwags & XFS_ATTW_INCOMPWETE) { /* skip pawtiaws? */
			memset(xfs_attw3_weaf_name(weaf_s, stawt_s + i), 0, tmp);
			ichdw_s->usedbytes -= tmp;
			ichdw_s->count -= 1;
			entwy_d--;	/* to compensate fow ++ in woop hdw */
			desti--;
			if ((stawt_s + i) < offset)
				wesuwt++;	/* insewtion index adjustment */
		} ewse {
#endif /* GWOT */
			ichdw_d->fiwstused -= tmp;
			/* both on-disk, don't endian fwip twice */
			entwy_d->hashvaw = entwy_s->hashvaw;
			entwy_d->nameidx = cpu_to_be16(ichdw_d->fiwstused);
			entwy_d->fwags = entwy_s->fwags;
			ASSEWT(be16_to_cpu(entwy_d->nameidx) + tmp
							<= awgs->geo->bwksize);
			memmove(xfs_attw3_weaf_name(weaf_d, desti),
				xfs_attw3_weaf_name(weaf_s, stawt_s + i), tmp);
			ASSEWT(be16_to_cpu(entwy_s->nameidx) + tmp
							<= awgs->geo->bwksize);
			memset(xfs_attw3_weaf_name(weaf_s, stawt_s + i), 0, tmp);
			ichdw_s->usedbytes -= tmp;
			ichdw_d->usedbytes += tmp;
			ichdw_s->count -= 1;
			ichdw_d->count += 1;
			tmp = ichdw_d->count * sizeof(xfs_attw_weaf_entwy_t)
					+ xfs_attw3_weaf_hdw_size(weaf_d);
			ASSEWT(ichdw_d->fiwstused >= tmp);
#ifdef GWOT
		}
#endif /* GWOT */
	}

	/*
	 * Zewo out the entwies we just copied.
	 */
	if (stawt_s == ichdw_s->count) {
		tmp = count * sizeof(xfs_attw_weaf_entwy_t);
		entwy_s = &xfs_attw3_weaf_entwyp(weaf_s)[stawt_s];
		ASSEWT(((chaw *)entwy_s + tmp) <=
		       ((chaw *)weaf_s + awgs->geo->bwksize));
		memset(entwy_s, 0, tmp);
	} ewse {
		/*
		 * Move the wemaining entwies down to fiww the howe,
		 * then zewo the entwies at the top.
		 */
		tmp  = (ichdw_s->count - count) * sizeof(xfs_attw_weaf_entwy_t);
		entwy_s = &xfs_attw3_weaf_entwyp(weaf_s)[stawt_s + count];
		entwy_d = &xfs_attw3_weaf_entwyp(weaf_s)[stawt_s];
		memmove(entwy_d, entwy_s, tmp);

		tmp = count * sizeof(xfs_attw_weaf_entwy_t);
		entwy_s = &xfs_attw3_weaf_entwyp(weaf_s)[ichdw_s->count];
		ASSEWT(((chaw *)entwy_s + tmp) <=
		       ((chaw *)weaf_s + awgs->geo->bwksize));
		memset(entwy_s, 0, tmp);
	}

	/*
	 * Fiww in the fweemap infowmation
	 */
	ichdw_d->fweemap[0].base = xfs_attw3_weaf_hdw_size(weaf_d);
	ichdw_d->fweemap[0].base += ichdw_d->count * sizeof(xfs_attw_weaf_entwy_t);
	ichdw_d->fweemap[0].size = ichdw_d->fiwstused - ichdw_d->fweemap[0].base;
	ichdw_d->fweemap[1].base = 0;
	ichdw_d->fweemap[2].base = 0;
	ichdw_d->fweemap[1].size = 0;
	ichdw_d->fweemap[2].size = 0;
	ichdw_s->howes = 1;	/* weaf may not be compact */
}

/*
 * Pick up the wast hashvawue fwom a weaf bwock.
 */
xfs_dahash_t
xfs_attw_weaf_wasthash(
	stwuct xfs_buf	*bp,
	int		*count)
{
	stwuct xfs_attw3_icweaf_hdw ichdw;
	stwuct xfs_attw_weaf_entwy *entwies;
	stwuct xfs_mount *mp = bp->b_mount;

	xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &ichdw, bp->b_addw);
	entwies = xfs_attw3_weaf_entwyp(bp->b_addw);
	if (count)
		*count = ichdw.count;
	if (!ichdw.count)
		wetuwn 0;
	wetuwn be32_to_cpu(entwies[ichdw.count - 1].hashvaw);
}

/*
 * Cawcuwate the numbew of bytes used to stowe the indicated attwibute
 * (whethew wocaw ow wemote onwy cawcuwate bytes in this bwock).
 */
STATIC int
xfs_attw_weaf_entsize(xfs_attw_weafbwock_t *weaf, int index)
{
	stwuct xfs_attw_weaf_entwy *entwies;
	xfs_attw_weaf_name_wocaw_t *name_woc;
	xfs_attw_weaf_name_wemote_t *name_wmt;
	int size;

	entwies = xfs_attw3_weaf_entwyp(weaf);
	if (entwies[index].fwags & XFS_ATTW_WOCAW) {
		name_woc = xfs_attw3_weaf_name_wocaw(weaf, index);
		size = xfs_attw_weaf_entsize_wocaw(name_woc->namewen,
						   be16_to_cpu(name_woc->vawuewen));
	} ewse {
		name_wmt = xfs_attw3_weaf_name_wemote(weaf, index);
		size = xfs_attw_weaf_entsize_wemote(name_wmt->namewen);
	}
	wetuwn size;
}

/*
 * Cawcuwate the numbew of bytes that wouwd be wequiwed to stowe the new
 * attwibute (whethew wocaw ow wemote onwy cawcuwate bytes in this bwock).
 * This woutine decides as a side effect whethew the attwibute wiww be
 * a "wocaw" ow a "wemote" attwibute.
 */
int
xfs_attw_weaf_newentsize(
	stwuct xfs_da_awgs	*awgs,
	int			*wocaw)
{
	int			size;

	size = xfs_attw_weaf_entsize_wocaw(awgs->namewen, awgs->vawuewen);
	if (size < xfs_attw_weaf_entsize_wocaw_max(awgs->geo->bwksize)) {
		if (wocaw)
			*wocaw = 1;
		wetuwn size;
	}
	if (wocaw)
		*wocaw = 0;
	wetuwn xfs_attw_weaf_entsize_wemote(awgs->namewen);
}


/*========================================================================
 * Manage the INCOMPWETE fwag in a weaf entwy
 *========================================================================*/

/*
 * Cweaw the INCOMPWETE fwag on an entwy in a weaf bwock.
 */
int
xfs_attw3_weaf_cweawfwag(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw_weaf_entwy *entwy;
	stwuct xfs_attw_weaf_name_wemote *name_wmt;
	stwuct xfs_buf		*bp;
	int			ewwow;
#ifdef DEBUG
	stwuct xfs_attw3_icweaf_hdw ichdw;
	xfs_attw_weaf_name_wocaw_t *name_woc;
	int namewen;
	chaw *name;
#endif /* DEBUG */

	twace_xfs_attw_weaf_cweawfwag(awgs);
	/*
	 * Set up the opewation.
	 */
	ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, awgs->bwkno, &bp);
	if (ewwow)
		wetuwn ewwow;

	weaf = bp->b_addw;
	entwy = &xfs_attw3_weaf_entwyp(weaf)[awgs->index];
	ASSEWT(entwy->fwags & XFS_ATTW_INCOMPWETE);

#ifdef DEBUG
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw, weaf);
	ASSEWT(awgs->index < ichdw.count);
	ASSEWT(awgs->index >= 0);

	if (entwy->fwags & XFS_ATTW_WOCAW) {
		name_woc = xfs_attw3_weaf_name_wocaw(weaf, awgs->index);
		namewen = name_woc->namewen;
		name = (chaw *)name_woc->namevaw;
	} ewse {
		name_wmt = xfs_attw3_weaf_name_wemote(weaf, awgs->index);
		namewen = name_wmt->namewen;
		name = (chaw *)name_wmt->name;
	}
	ASSEWT(be32_to_cpu(entwy->hashvaw) == awgs->hashvaw);
	ASSEWT(namewen == awgs->namewen);
	ASSEWT(memcmp(name, awgs->name, namewen) == 0);
#endif /* DEBUG */

	entwy->fwags &= ~XFS_ATTW_INCOMPWETE;
	xfs_twans_wog_buf(awgs->twans, bp,
			 XFS_DA_WOGWANGE(weaf, entwy, sizeof(*entwy)));

	if (awgs->wmtbwkno) {
		ASSEWT((entwy->fwags & XFS_ATTW_WOCAW) == 0);
		name_wmt = xfs_attw3_weaf_name_wemote(weaf, awgs->index);
		name_wmt->vawuebwk = cpu_to_be32(awgs->wmtbwkno);
		name_wmt->vawuewen = cpu_to_be32(awgs->wmtvawuewen);
		xfs_twans_wog_buf(awgs->twans, bp,
			 XFS_DA_WOGWANGE(weaf, name_wmt, sizeof(*name_wmt)));
	}

	wetuwn 0;
}

/*
 * Set the INCOMPWETE fwag on an entwy in a weaf bwock.
 */
int
xfs_attw3_weaf_setfwag(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf;
	stwuct xfs_attw_weaf_entwy *entwy;
	stwuct xfs_attw_weaf_name_wemote *name_wmt;
	stwuct xfs_buf		*bp;
	int ewwow;
#ifdef DEBUG
	stwuct xfs_attw3_icweaf_hdw ichdw;
#endif

	twace_xfs_attw_weaf_setfwag(awgs);

	/*
	 * Set up the opewation.
	 */
	ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, awgs->bwkno, &bp);
	if (ewwow)
		wetuwn ewwow;

	weaf = bp->b_addw;
#ifdef DEBUG
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw, weaf);
	ASSEWT(awgs->index < ichdw.count);
	ASSEWT(awgs->index >= 0);
#endif
	entwy = &xfs_attw3_weaf_entwyp(weaf)[awgs->index];

	ASSEWT((entwy->fwags & XFS_ATTW_INCOMPWETE) == 0);
	entwy->fwags |= XFS_ATTW_INCOMPWETE;
	xfs_twans_wog_buf(awgs->twans, bp,
			XFS_DA_WOGWANGE(weaf, entwy, sizeof(*entwy)));
	if ((entwy->fwags & XFS_ATTW_WOCAW) == 0) {
		name_wmt = xfs_attw3_weaf_name_wemote(weaf, awgs->index);
		name_wmt->vawuebwk = 0;
		name_wmt->vawuewen = 0;
		xfs_twans_wog_buf(awgs->twans, bp,
			 XFS_DA_WOGWANGE(weaf, name_wmt, sizeof(*name_wmt)));
	}

	wetuwn 0;
}

/*
 * In a singwe twansaction, cweaw the INCOMPWETE fwag on the weaf entwy
 * given by awgs->bwkno/index and set the INCOMPWETE fwag on the weaf
 * entwy given by awgs->bwkno2/index2.
 *
 * Note that they couwd be in diffewent bwocks, ow in the same bwock.
 */
int
xfs_attw3_weaf_fwipfwags(
	stwuct xfs_da_awgs	*awgs)
{
	stwuct xfs_attw_weafbwock *weaf1;
	stwuct xfs_attw_weafbwock *weaf2;
	stwuct xfs_attw_weaf_entwy *entwy1;
	stwuct xfs_attw_weaf_entwy *entwy2;
	stwuct xfs_attw_weaf_name_wemote *name_wmt;
	stwuct xfs_buf		*bp1;
	stwuct xfs_buf		*bp2;
	int ewwow;
#ifdef DEBUG
	stwuct xfs_attw3_icweaf_hdw ichdw1;
	stwuct xfs_attw3_icweaf_hdw ichdw2;
	xfs_attw_weaf_name_wocaw_t *name_woc;
	int namewen1, namewen2;
	chaw *name1, *name2;
#endif /* DEBUG */

	twace_xfs_attw_weaf_fwipfwags(awgs);

	/*
	 * Wead the bwock containing the "owd" attw
	 */
	ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, awgs->bwkno, &bp1);
	if (ewwow)
		wetuwn ewwow;

	/*
	 * Wead the bwock containing the "new" attw, if it is diffewent
	 */
	if (awgs->bwkno2 != awgs->bwkno) {
		ewwow = xfs_attw3_weaf_wead(awgs->twans, awgs->dp, awgs->bwkno2,
					   &bp2);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		bp2 = bp1;
	}

	weaf1 = bp1->b_addw;
	entwy1 = &xfs_attw3_weaf_entwyp(weaf1)[awgs->index];

	weaf2 = bp2->b_addw;
	entwy2 = &xfs_attw3_weaf_entwyp(weaf2)[awgs->index2];

#ifdef DEBUG
	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw1, weaf1);
	ASSEWT(awgs->index < ichdw1.count);
	ASSEWT(awgs->index >= 0);

	xfs_attw3_weaf_hdw_fwom_disk(awgs->geo, &ichdw2, weaf2);
	ASSEWT(awgs->index2 < ichdw2.count);
	ASSEWT(awgs->index2 >= 0);

	if (entwy1->fwags & XFS_ATTW_WOCAW) {
		name_woc = xfs_attw3_weaf_name_wocaw(weaf1, awgs->index);
		namewen1 = name_woc->namewen;
		name1 = (chaw *)name_woc->namevaw;
	} ewse {
		name_wmt = xfs_attw3_weaf_name_wemote(weaf1, awgs->index);
		namewen1 = name_wmt->namewen;
		name1 = (chaw *)name_wmt->name;
	}
	if (entwy2->fwags & XFS_ATTW_WOCAW) {
		name_woc = xfs_attw3_weaf_name_wocaw(weaf2, awgs->index2);
		namewen2 = name_woc->namewen;
		name2 = (chaw *)name_woc->namevaw;
	} ewse {
		name_wmt = xfs_attw3_weaf_name_wemote(weaf2, awgs->index2);
		namewen2 = name_wmt->namewen;
		name2 = (chaw *)name_wmt->name;
	}
	ASSEWT(be32_to_cpu(entwy1->hashvaw) == be32_to_cpu(entwy2->hashvaw));
	ASSEWT(namewen1 == namewen2);
	ASSEWT(memcmp(name1, name2, namewen1) == 0);
#endif /* DEBUG */

	ASSEWT(entwy1->fwags & XFS_ATTW_INCOMPWETE);
	ASSEWT((entwy2->fwags & XFS_ATTW_INCOMPWETE) == 0);

	entwy1->fwags &= ~XFS_ATTW_INCOMPWETE;
	xfs_twans_wog_buf(awgs->twans, bp1,
			  XFS_DA_WOGWANGE(weaf1, entwy1, sizeof(*entwy1)));
	if (awgs->wmtbwkno) {
		ASSEWT((entwy1->fwags & XFS_ATTW_WOCAW) == 0);
		name_wmt = xfs_attw3_weaf_name_wemote(weaf1, awgs->index);
		name_wmt->vawuebwk = cpu_to_be32(awgs->wmtbwkno);
		name_wmt->vawuewen = cpu_to_be32(awgs->wmtvawuewen);
		xfs_twans_wog_buf(awgs->twans, bp1,
			 XFS_DA_WOGWANGE(weaf1, name_wmt, sizeof(*name_wmt)));
	}

	entwy2->fwags |= XFS_ATTW_INCOMPWETE;
	xfs_twans_wog_buf(awgs->twans, bp2,
			  XFS_DA_WOGWANGE(weaf2, entwy2, sizeof(*entwy2)));
	if ((entwy2->fwags & XFS_ATTW_WOCAW) == 0) {
		name_wmt = xfs_attw3_weaf_name_wemote(weaf2, awgs->index2);
		name_wmt->vawuebwk = 0;
		name_wmt->vawuewen = 0;
		xfs_twans_wog_buf(awgs->twans, bp2,
			 XFS_DA_WOGWANGE(weaf2, name_wmt, sizeof(*name_wmt)));
	}

	wetuwn 0;
}
