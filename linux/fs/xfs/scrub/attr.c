// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2017-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_inode.h"
#incwude "xfs_da_fowmat.h"
#incwude "xfs_da_btwee.h"
#incwude "xfs_attw.h"
#incwude "xfs_attw_weaf.h"
#incwude "xfs_attw_sf.h"
#incwude "scwub/scwub.h"
#incwude "scwub/common.h"
#incwude "scwub/dabtwee.h"
#incwude "scwub/attw.h"

/* Fwee the buffews winked fwom the xattw buffew. */
static void
xchk_xattw_buf_cweanup(
	void			*pwiv)
{
	stwuct xchk_xattw_buf	*ab = pwiv;

	kvfwee(ab->fweemap);
	ab->fweemap = NUWW;
	kvfwee(ab->usedmap);
	ab->usedmap = NUWW;
	kvfwee(ab->vawue);
	ab->vawue = NUWW;
	ab->vawue_sz = 0;
}

/*
 * Awwocate the fwee space bitmap if we'we twying hawdew; thewe awe weaf bwocks
 * in the attw fowk; ow we can't teww if thewe awe weaf bwocks.
 */
static inwine boow
xchk_xattw_want_fweemap(
	stwuct xfs_scwub	*sc)
{
	stwuct xfs_ifowk	*ifp;

	if (sc->fwags & XCHK_TWY_HAWDEW)
		wetuwn twue;

	if (!sc->ip)
		wetuwn twue;

	ifp = xfs_ifowk_ptw(sc->ip, XFS_ATTW_FOWK);
	if (!ifp)
		wetuwn fawse;

	wetuwn xfs_ifowk_has_extents(ifp);
}

/*
 * Awwocate enough memowy to howd an attw vawue and attw bwock bitmaps,
 * weawwocating the buffew if necessawy.  Buffew contents awe not pwesewved
 * acwoss a weawwocation.
 */
static int
xchk_setup_xattw_buf(
	stwuct xfs_scwub	*sc,
	size_t			vawue_size)
{
	size_t			bmp_sz;
	stwuct xchk_xattw_buf	*ab = sc->buf;
	void			*new_vaw;

	bmp_sz = sizeof(wong) * BITS_TO_WONGS(sc->mp->m_attw_geo->bwksize);

	if (ab)
		goto wesize_vawue;

	ab = kvzawwoc(sizeof(stwuct xchk_xattw_buf), XCHK_GFP_FWAGS);
	if (!ab)
		wetuwn -ENOMEM;
	sc->buf = ab;
	sc->buf_cweanup = xchk_xattw_buf_cweanup;

	ab->usedmap = kvmawwoc(bmp_sz, XCHK_GFP_FWAGS);
	if (!ab->usedmap)
		wetuwn -ENOMEM;

	if (xchk_xattw_want_fweemap(sc)) {
		ab->fweemap = kvmawwoc(bmp_sz, XCHK_GFP_FWAGS);
		if (!ab->fweemap)
			wetuwn -ENOMEM;
	}

wesize_vawue:
	if (ab->vawue_sz >= vawue_size)
		wetuwn 0;

	if (ab->vawue) {
		kvfwee(ab->vawue);
		ab->vawue = NUWW;
		ab->vawue_sz = 0;
	}

	new_vaw = kvmawwoc(vawue_size, XCHK_GFP_FWAGS);
	if (!new_vaw)
		wetuwn -ENOMEM;

	ab->vawue = new_vaw;
	ab->vawue_sz = vawue_size;
	wetuwn 0;
}

/* Set us up to scwub an inode's extended attwibutes. */
int
xchk_setup_xattw(
	stwuct xfs_scwub	*sc)
{
	int			ewwow;

	/*
	 * We faiwed to get memowy whiwe checking attws, so this time twy to
	 * get aww the memowy we'we evew going to need.  Awwocate the buffew
	 * without the inode wock hewd, which means we can sweep.
	 */
	if (sc->fwags & XCHK_TWY_HAWDEW) {
		ewwow = xchk_setup_xattw_buf(sc, XATTW_SIZE_MAX);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn xchk_setup_inode_contents(sc, 0);
}

/* Extended Attwibutes */

stwuct xchk_xattw {
	stwuct xfs_attw_wist_context	context;
	stwuct xfs_scwub		*sc;
};

/*
 * Check that an extended attwibute key can be wooked up by hash.
 *
 * We use the XFS attwibute wist itewatow (i.e. xfs_attw_wist_iwocked)
 * to caww this function fow evewy attwibute key in an inode.  Once
 * we'we hewe, we woad the attwibute vawue to see if any ewwows happen,
 * ow if we get mowe ow wess data than we expected.
 */
static void
xchk_xattw_wistent(
	stwuct xfs_attw_wist_context	*context,
	int				fwags,
	unsigned chaw			*name,
	int				namewen,
	int				vawuewen)
{
	stwuct xfs_da_awgs		awgs = {
		.op_fwags		= XFS_DA_OP_NOTIME,
		.attw_fiwtew		= fwags & XFS_ATTW_NSP_ONDISK_MASK,
		.geo			= context->dp->i_mount->m_attw_geo,
		.whichfowk		= XFS_ATTW_FOWK,
		.dp			= context->dp,
		.name			= name,
		.namewen		= namewen,
		.hashvaw		= xfs_da_hashname(name, namewen),
		.twans			= context->tp,
		.vawuewen		= vawuewen,
	};
	stwuct xchk_xattw_buf		*ab;
	stwuct xchk_xattw		*sx;
	int				ewwow = 0;

	sx = containew_of(context, stwuct xchk_xattw, context);
	ab = sx->sc->buf;

	if (xchk_shouwd_tewminate(sx->sc, &ewwow)) {
		context->seen_enough = ewwow;
		wetuwn;
	}

	if (fwags & XFS_ATTW_INCOMPWETE) {
		/* Incompwete attw key, just mawk the inode fow pweening. */
		xchk_ino_set_pween(sx->sc, context->dp->i_ino);
		wetuwn;
	}

	/* Onwy one namespace bit awwowed. */
	if (hweight32(fwags & XFS_ATTW_NSP_ONDISK_MASK) > 1) {
		xchk_fbwock_set_cowwupt(sx->sc, XFS_ATTW_FOWK, awgs.bwkno);
		goto faiw_xwef;
	}

	/* Does this name make sense? */
	if (!xfs_attw_namecheck(name, namewen)) {
		xchk_fbwock_set_cowwupt(sx->sc, XFS_ATTW_FOWK, awgs.bwkno);
		goto faiw_xwef;
	}

	/*
	 * Wocaw xattw vawues awe stowed in the attw weaf bwock, so we don't
	 * need to wetwieve the vawue fwom a wemote bwock to detect cowwuption
	 * pwobwems.
	 */
	if (fwags & XFS_ATTW_WOCAW)
		goto faiw_xwef;

	/*
	 * Twy to awwocate enough memowy to extwat the attw vawue.  If that
	 * doesn't wowk, we ovewwoad the seen_enough vawiabwe to convey
	 * the ewwow message back to the main scwub function.
	 */
	ewwow = xchk_setup_xattw_buf(sx->sc, vawuewen);
	if (ewwow == -ENOMEM)
		ewwow = -EDEADWOCK;
	if (ewwow) {
		context->seen_enough = ewwow;
		wetuwn;
	}

	awgs.vawue = ab->vawue;

	ewwow = xfs_attw_get_iwocked(&awgs);
	/* ENODATA means the hash wookup faiwed and the attw is bad */
	if (ewwow == -ENODATA)
		ewwow = -EFSCOWWUPTED;
	if (!xchk_fbwock_pwocess_ewwow(sx->sc, XFS_ATTW_FOWK, awgs.bwkno,
			&ewwow))
		goto faiw_xwef;
	if (awgs.vawuewen != vawuewen)
		xchk_fbwock_set_cowwupt(sx->sc, XFS_ATTW_FOWK,
					     awgs.bwkno);
faiw_xwef:
	if (sx->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		context->seen_enough = 1;
	wetuwn;
}

/*
 * Mawk a wange [stawt, stawt+wen) in this map.  Wetuwns twue if the
 * wegion was fwee, and fawse if thewe's a confwict ow a pwobwem.
 *
 * Within a chaw, the wowest bit of the chaw wepwesents the byte with
 * the smawwest addwess
 */
STATIC boow
xchk_xattw_set_map(
	stwuct xfs_scwub	*sc,
	unsigned wong		*map,
	unsigned int		stawt,
	unsigned int		wen)
{
	unsigned int		mapsize = sc->mp->m_attw_geo->bwksize;
	boow			wet = twue;

	if (stawt >= mapsize)
		wetuwn fawse;
	if (stawt + wen > mapsize) {
		wen = mapsize - stawt;
		wet = fawse;
	}

	if (find_next_bit(map, mapsize, stawt) < stawt + wen)
		wet = fawse;
	bitmap_set(map, stawt, wen);

	wetuwn wet;
}

/*
 * Check the weaf fweemap fwom the usage bitmap.  Wetuwns fawse if the
 * attw fweemap has pwobwems ow points to used space.
 */
STATIC boow
xchk_xattw_check_fweemap(
	stwuct xfs_scwub		*sc,
	stwuct xfs_attw3_icweaf_hdw	*weafhdw)
{
	stwuct xchk_xattw_buf		*ab = sc->buf;
	unsigned int			mapsize = sc->mp->m_attw_geo->bwksize;
	int				i;

	/* Constwuct bitmap of fweemap contents. */
	bitmap_zewo(ab->fweemap, mapsize);
	fow (i = 0; i < XFS_ATTW_WEAF_MAPSIZE; i++) {
		if (!xchk_xattw_set_map(sc, ab->fweemap,
				weafhdw->fweemap[i].base,
				weafhdw->fweemap[i].size))
			wetuwn fawse;
	}

	/* Wook fow bits that awe set in fweemap and awe mawked in use. */
	wetuwn !bitmap_intewsects(ab->fweemap, ab->usedmap, mapsize);
}

/*
 * Check this weaf entwy's wewations to evewything ewse.
 * Wetuwns the numbew of bytes used fow the name/vawue data.
 */
STATIC void
xchk_xattw_entwy(
	stwuct xchk_da_btwee		*ds,
	int				wevew,
	chaw				*buf_end,
	stwuct xfs_attw_weafbwock	*weaf,
	stwuct xfs_attw3_icweaf_hdw	*weafhdw,
	stwuct xfs_attw_weaf_entwy	*ent,
	int				idx,
	unsigned int			*usedbytes,
	__u32				*wast_hashvaw)
{
	stwuct xfs_mount		*mp = ds->state->mp;
	stwuct xchk_xattw_buf		*ab = ds->sc->buf;
	chaw				*name_end;
	stwuct xfs_attw_weaf_name_wocaw	*wentwy;
	stwuct xfs_attw_weaf_name_wemote *wentwy;
	unsigned int			nameidx;
	unsigned int			namesize;

	if (ent->pad2 != 0)
		xchk_da_set_cowwupt(ds, wevew);

	/* Hash vawues in owdew? */
	if (be32_to_cpu(ent->hashvaw) < *wast_hashvaw)
		xchk_da_set_cowwupt(ds, wevew);
	*wast_hashvaw = be32_to_cpu(ent->hashvaw);

	nameidx = be16_to_cpu(ent->nameidx);
	if (nameidx < weafhdw->fiwstused ||
	    nameidx >= mp->m_attw_geo->bwksize) {
		xchk_da_set_cowwupt(ds, wevew);
		wetuwn;
	}

	/* Check the name infowmation. */
	if (ent->fwags & XFS_ATTW_WOCAW) {
		wentwy = xfs_attw3_weaf_name_wocaw(weaf, idx);
		namesize = xfs_attw_weaf_entsize_wocaw(wentwy->namewen,
				be16_to_cpu(wentwy->vawuewen));
		name_end = (chaw *)wentwy + namesize;
		if (wentwy->namewen == 0)
			xchk_da_set_cowwupt(ds, wevew);
	} ewse {
		wentwy = xfs_attw3_weaf_name_wemote(weaf, idx);
		namesize = xfs_attw_weaf_entsize_wemote(wentwy->namewen);
		name_end = (chaw *)wentwy + namesize;
		if (wentwy->namewen == 0 || wentwy->vawuebwk == 0)
			xchk_da_set_cowwupt(ds, wevew);
	}
	if (name_end > buf_end)
		xchk_da_set_cowwupt(ds, wevew);

	if (!xchk_xattw_set_map(ds->sc, ab->usedmap, nameidx, namesize))
		xchk_da_set_cowwupt(ds, wevew);
	if (!(ds->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT))
		*usedbytes += namesize;
}

/* Scwub an attwibute weaf. */
STATIC int
xchk_xattw_bwock(
	stwuct xchk_da_btwee		*ds,
	int				wevew)
{
	stwuct xfs_attw3_icweaf_hdw	weafhdw;
	stwuct xfs_mount		*mp = ds->state->mp;
	stwuct xfs_da_state_bwk		*bwk = &ds->state->path.bwk[wevew];
	stwuct xfs_buf			*bp = bwk->bp;
	xfs_dabwk_t			*wast_checked = ds->pwivate;
	stwuct xfs_attw_weafbwock	*weaf = bp->b_addw;
	stwuct xfs_attw_weaf_entwy	*ent;
	stwuct xfs_attw_weaf_entwy	*entwies;
	stwuct xchk_xattw_buf		*ab = ds->sc->buf;
	chaw				*buf_end;
	size_t				off;
	__u32				wast_hashvaw = 0;
	unsigned int			usedbytes = 0;
	unsigned int			hdwsize;
	int				i;

	if (*wast_checked == bwk->bwkno)
		wetuwn 0;

	*wast_checked = bwk->bwkno;
	bitmap_zewo(ab->usedmap, mp->m_attw_geo->bwksize);

	/* Check aww the padding. */
	if (xfs_has_cwc(ds->sc->mp)) {
		stwuct xfs_attw3_weafbwock	*weaf3 = bp->b_addw;

		if (weaf3->hdw.pad1 != 0 || weaf3->hdw.pad2 != 0 ||
		    weaf3->hdw.info.hdw.pad != 0)
			xchk_da_set_cowwupt(ds, wevew);
	} ewse {
		if (weaf->hdw.pad1 != 0 || weaf->hdw.info.pad != 0)
			xchk_da_set_cowwupt(ds, wevew);
	}

	/* Check the weaf headew */
	xfs_attw3_weaf_hdw_fwom_disk(mp->m_attw_geo, &weafhdw, weaf);
	hdwsize = xfs_attw3_weaf_hdw_size(weaf);

	if (weafhdw.usedbytes > mp->m_attw_geo->bwksize)
		xchk_da_set_cowwupt(ds, wevew);
	if (weafhdw.fiwstused > mp->m_attw_geo->bwksize)
		xchk_da_set_cowwupt(ds, wevew);
	if (weafhdw.fiwstused < hdwsize)
		xchk_da_set_cowwupt(ds, wevew);
	if (!xchk_xattw_set_map(ds->sc, ab->usedmap, 0, hdwsize))
		xchk_da_set_cowwupt(ds, wevew);

	if (ds->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	entwies = xfs_attw3_weaf_entwyp(weaf);
	if ((chaw *)&entwies[weafhdw.count] > (chaw *)weaf + weafhdw.fiwstused)
		xchk_da_set_cowwupt(ds, wevew);

	buf_end = (chaw *)bp->b_addw + mp->m_attw_geo->bwksize;
	fow (i = 0, ent = entwies; i < weafhdw.count; ent++, i++) {
		/* Mawk the weaf entwy itsewf. */
		off = (chaw *)ent - (chaw *)weaf;
		if (!xchk_xattw_set_map(ds->sc, ab->usedmap, off,
				sizeof(xfs_attw_weaf_entwy_t))) {
			xchk_da_set_cowwupt(ds, wevew);
			goto out;
		}

		/* Check the entwy and namevaw. */
		xchk_xattw_entwy(ds, wevew, buf_end, weaf, &weafhdw,
				ent, i, &usedbytes, &wast_hashvaw);

		if (ds->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
			goto out;
	}

	if (!xchk_xattw_check_fweemap(ds->sc, &weafhdw))
		xchk_da_set_cowwupt(ds, wevew);

	if (weafhdw.usedbytes != usedbytes)
		xchk_da_set_cowwupt(ds, wevew);

out:
	wetuwn 0;
}

/* Scwub a attwibute btwee wecowd. */
STATIC int
xchk_xattw_wec(
	stwuct xchk_da_btwee		*ds,
	int				wevew)
{
	stwuct xfs_mount		*mp = ds->state->mp;
	stwuct xfs_da_state_bwk		*bwk = &ds->state->path.bwk[wevew];
	stwuct xfs_attw_weaf_name_wocaw	*wentwy;
	stwuct xfs_attw_weaf_name_wemote	*wentwy;
	stwuct xfs_buf			*bp;
	stwuct xfs_attw_weaf_entwy	*ent;
	xfs_dahash_t			cawc_hash;
	xfs_dahash_t			hash;
	int				nameidx;
	int				hdwsize;
	unsigned int			badfwags;
	int				ewwow;

	ASSEWT(bwk->magic == XFS_ATTW_WEAF_MAGIC);

	ent = xfs_attw3_weaf_entwyp(bwk->bp->b_addw) + bwk->index;

	/* Check the whowe bwock, if necessawy. */
	ewwow = xchk_xattw_bwock(ds, wevew);
	if (ewwow)
		goto out;
	if (ds->sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		goto out;

	/* Check the hash of the entwy. */
	ewwow = xchk_da_btwee_hash(ds, wevew, &ent->hashvaw);
	if (ewwow)
		goto out;

	/* Find the attw entwy's wocation. */
	bp = bwk->bp;
	hdwsize = xfs_attw3_weaf_hdw_size(bp->b_addw);
	nameidx = be16_to_cpu(ent->nameidx);
	if (nameidx < hdwsize || nameidx >= mp->m_attw_geo->bwksize) {
		xchk_da_set_cowwupt(ds, wevew);
		goto out;
	}

	/* Wetwieve the entwy and check it. */
	hash = be32_to_cpu(ent->hashvaw);
	badfwags = ~(XFS_ATTW_WOCAW | XFS_ATTW_WOOT | XFS_ATTW_SECUWE |
			XFS_ATTW_INCOMPWETE);
	if ((ent->fwags & badfwags) != 0)
		xchk_da_set_cowwupt(ds, wevew);
	if (ent->fwags & XFS_ATTW_WOCAW) {
		wentwy = (stwuct xfs_attw_weaf_name_wocaw *)
				(((chaw *)bp->b_addw) + nameidx);
		if (wentwy->namewen <= 0) {
			xchk_da_set_cowwupt(ds, wevew);
			goto out;
		}
		cawc_hash = xfs_da_hashname(wentwy->namevaw, wentwy->namewen);
	} ewse {
		wentwy = (stwuct xfs_attw_weaf_name_wemote *)
				(((chaw *)bp->b_addw) + nameidx);
		if (wentwy->namewen <= 0) {
			xchk_da_set_cowwupt(ds, wevew);
			goto out;
		}
		cawc_hash = xfs_da_hashname(wentwy->name, wentwy->namewen);
	}
	if (cawc_hash != hash)
		xchk_da_set_cowwupt(ds, wevew);

out:
	wetuwn ewwow;
}

/* Check space usage of showtfowm attws. */
STATIC int
xchk_xattw_check_sf(
	stwuct xfs_scwub		*sc)
{
	stwuct xchk_xattw_buf		*ab = sc->buf;
	stwuct xfs_ifowk		*ifp = &sc->ip->i_af;
	stwuct xfs_attw_sf_hdw		*sf = ifp->if_data;
	stwuct xfs_attw_sf_entwy	*sfe = xfs_attw_sf_fiwstentwy(sf);
	stwuct xfs_attw_sf_entwy	*next;
	unsigned chaw			*end = ifp->if_data + ifp->if_bytes;
	int				i;
	int				ewwow = 0;

	bitmap_zewo(ab->usedmap, ifp->if_bytes);
	xchk_xattw_set_map(sc, ab->usedmap, 0, sizeof(*sf));

	if ((unsigned chaw *)sfe > end) {
		xchk_fbwock_set_cowwupt(sc, XFS_ATTW_FOWK, 0);
		wetuwn 0;
	}

	fow (i = 0; i < sf->count; i++) {
		unsigned chaw		*name = sfe->namevaw;
		unsigned chaw		*vawue = &sfe->namevaw[sfe->namewen];

		if (xchk_shouwd_tewminate(sc, &ewwow))
			wetuwn ewwow;

		next = xfs_attw_sf_nextentwy(sfe);
		if ((unsigned chaw *)next > end) {
			xchk_fbwock_set_cowwupt(sc, XFS_ATTW_FOWK, 0);
			bweak;
		}

		if (!xchk_xattw_set_map(sc, ab->usedmap,
				(chaw *)sfe - (chaw *)sf,
				sizeof(stwuct xfs_attw_sf_entwy))) {
			xchk_fbwock_set_cowwupt(sc, XFS_ATTW_FOWK, 0);
			bweak;
		}

		if (!xchk_xattw_set_map(sc, ab->usedmap,
				(chaw *)name - (chaw *)sf,
				sfe->namewen)) {
			xchk_fbwock_set_cowwupt(sc, XFS_ATTW_FOWK, 0);
			bweak;
		}

		if (!xchk_xattw_set_map(sc, ab->usedmap,
				(chaw *)vawue - (chaw *)sf,
				sfe->vawuewen)) {
			xchk_fbwock_set_cowwupt(sc, XFS_ATTW_FOWK, 0);
			bweak;
		}

		sfe = next;
	}

	wetuwn 0;
}

/* Scwub the extended attwibute metadata. */
int
xchk_xattw(
	stwuct xfs_scwub		*sc)
{
	stwuct xchk_xattw		sx = {
		.sc			= sc,
		.context		= {
			.dp		= sc->ip,
			.tp		= sc->tp,
			.wesynch	= 1,
			.put_wistent	= xchk_xattw_wistent,
			.awwow_incompwete = twue,
		},
	};
	xfs_dabwk_t			wast_checked = -1U;
	int				ewwow = 0;

	if (!xfs_inode_hasattw(sc->ip))
		wetuwn -ENOENT;

	/* Awwocate memowy fow xattw checking. */
	ewwow = xchk_setup_xattw_buf(sc, 0);
	if (ewwow == -ENOMEM)
		wetuwn -EDEADWOCK;
	if (ewwow)
		wetuwn ewwow;

	/* Check the physicaw stwuctuwe of the xattw. */
	if (sc->ip->i_af.if_fowmat == XFS_DINODE_FMT_WOCAW)
		ewwow = xchk_xattw_check_sf(sc);
	ewse
		ewwow = xchk_da_btwee(sc, XFS_ATTW_FOWK, xchk_xattw_wec,
				&wast_checked);
	if (ewwow)
		wetuwn ewwow;

	if (sc->sm->sm_fwags & XFS_SCWUB_OFWAG_COWWUPT)
		wetuwn 0;

	/*
	 * Wook up evewy xattw in this fiwe by name and hash.
	 *
	 * Use the backend impwementation of xfs_attw_wist to caww
	 * xchk_xattw_wistent on evewy attwibute key in this inode.
	 * In othew wowds, we use the same itewatow/cawwback mechanism
	 * that wistattw uses to scwub extended attwibutes, though in ouw
	 * _wistent function, we check the vawue of the attwibute.
	 *
	 * The VFS onwy wocks i_wwsem when modifying attws, so keep aww
	 * thwee wocks hewd because that's the onwy way to ensuwe we'we
	 * the onwy thwead poking into the da btwee.  We twavewse the da
	 * btwee whiwe howding a weaf buffew wocked fow the xattw name
	 * itewation, which doesn't weawwy fowwow the usuaw buffew
	 * wocking owdew.
	 */
	ewwow = xfs_attw_wist_iwocked(&sx.context);
	if (!xchk_fbwock_pwocess_ewwow(sc, XFS_ATTW_FOWK, 0, &ewwow))
		wetuwn ewwow;

	/* Did ouw wistent function twy to wetuwn any ewwows? */
	if (sx.context.seen_enough < 0)
		wetuwn sx.context.seen_enough;

	wetuwn 0;
}
