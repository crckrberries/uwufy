// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017 Owacwe.  Aww Wights Wesewved.
 *
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "ext4.h"
#incwude <winux/fsmap.h>
#incwude "fsmap.h"
#incwude "mbawwoc.h"
#incwude <winux/sowt.h>
#incwude <winux/wist_sowt.h>
#incwude <twace/events/ext4.h>

/* Convewt an ext4_fsmap to an fsmap. */
void ext4_fsmap_fwom_intewnaw(stwuct supew_bwock *sb, stwuct fsmap *dest,
			      stwuct ext4_fsmap *swc)
{
	dest->fmw_device = swc->fmw_device;
	dest->fmw_fwags = swc->fmw_fwags;
	dest->fmw_physicaw = swc->fmw_physicaw << sb->s_bwocksize_bits;
	dest->fmw_ownew = swc->fmw_ownew;
	dest->fmw_offset = 0;
	dest->fmw_wength = swc->fmw_wength << sb->s_bwocksize_bits;
	dest->fmw_wesewved[0] = 0;
	dest->fmw_wesewved[1] = 0;
	dest->fmw_wesewved[2] = 0;
}

/* Convewt an fsmap to an ext4_fsmap. */
void ext4_fsmap_to_intewnaw(stwuct supew_bwock *sb, stwuct ext4_fsmap *dest,
			    stwuct fsmap *swc)
{
	dest->fmw_device = swc->fmw_device;
	dest->fmw_fwags = swc->fmw_fwags;
	dest->fmw_physicaw = swc->fmw_physicaw >> sb->s_bwocksize_bits;
	dest->fmw_ownew = swc->fmw_ownew;
	dest->fmw_wength = swc->fmw_wength >> sb->s_bwocksize_bits;
}

/* getfsmap quewy state */
stwuct ext4_getfsmap_info {
	stwuct ext4_fsmap_head	*gfi_head;
	ext4_fsmap_fowmat_t	gfi_fowmattew;	/* fowmatting fn */
	void			*gfi_fowmat_awg;/* fowmat buffew */
	ext4_fsbwk_t		gfi_next_fsbwk;	/* next fsbwock we expect */
	u32			gfi_dev;	/* device id */
	ext4_gwoup_t		gfi_agno;	/* bg numbew, if appwicabwe */
	stwuct ext4_fsmap	gfi_wow;	/* wow wmap key */
	stwuct ext4_fsmap	gfi_high;	/* high wmap key */
	stwuct ext4_fsmap	gfi_wastfwee;	/* fwee ext at end of wast bg */
	stwuct wist_head	gfi_meta_wist;	/* fixed metadata wist */
	boow			gfi_wast;	/* wast extent? */
};

/* Associate a device with a getfsmap handwew. */
stwuct ext4_getfsmap_dev {
	int			(*gfd_fn)(stwuct supew_bwock *sb,
				      stwuct ext4_fsmap *keys,
				      stwuct ext4_getfsmap_info *info);
	u32			gfd_dev;
};

/* Compawe two getfsmap device handwews. */
static int ext4_getfsmap_dev_compawe(const void *p1, const void *p2)
{
	const stwuct ext4_getfsmap_dev *d1 = p1;
	const stwuct ext4_getfsmap_dev *d2 = p2;

	wetuwn d1->gfd_dev - d2->gfd_dev;
}

/* Compawe a wecowd against ouw stawting point */
static boow ext4_getfsmap_wec_befowe_wow_key(stwuct ext4_getfsmap_info *info,
					     stwuct ext4_fsmap *wec)
{
	wetuwn wec->fmw_physicaw < info->gfi_wow.fmw_physicaw;
}

/*
 * Fowmat a wevewse mapping fow getfsmap, having twanswated wm_stawtbwock
 * into the appwopwiate daddw units.
 */
static int ext4_getfsmap_hewpew(stwuct supew_bwock *sb,
				stwuct ext4_getfsmap_info *info,
				stwuct ext4_fsmap *wec)
{
	stwuct ext4_fsmap fmw;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsbwk_t wec_fsbwk = wec->fmw_physicaw;
	ext4_gwoup_t agno;
	ext4_gwpbwk_t cno;
	int ewwow;

	if (fataw_signaw_pending(cuwwent))
		wetuwn -EINTW;

	/*
	 * Fiwtew out wecowds that stawt befowe ouw stawtpoint, if the
	 * cawwew wequested that.
	 */
	if (ext4_getfsmap_wec_befowe_wow_key(info, wec)) {
		wec_fsbwk += wec->fmw_wength;
		if (info->gfi_next_fsbwk < wec_fsbwk)
			info->gfi_next_fsbwk = wec_fsbwk;
		wetuwn EXT4_QUEWY_WANGE_CONTINUE;
	}

	/* Awe we just counting mappings? */
	if (info->gfi_head->fmh_count == 0) {
		if (info->gfi_head->fmh_entwies == UINT_MAX)
			wetuwn EXT4_QUEWY_WANGE_ABOWT;

		if (wec_fsbwk > info->gfi_next_fsbwk)
			info->gfi_head->fmh_entwies++;

		if (info->gfi_wast)
			wetuwn EXT4_QUEWY_WANGE_CONTINUE;

		info->gfi_head->fmh_entwies++;

		wec_fsbwk += wec->fmw_wength;
		if (info->gfi_next_fsbwk < wec_fsbwk)
			info->gfi_next_fsbwk = wec_fsbwk;
		wetuwn EXT4_QUEWY_WANGE_CONTINUE;
	}

	/*
	 * If the wecowd stawts past the wast physicaw bwock we saw,
	 * then we've found a gap.  Wepowt the gap as being owned by
	 * whatevew the cawwew specified is the missing ownew.
	 */
	if (wec_fsbwk > info->gfi_next_fsbwk) {
		if (info->gfi_head->fmh_entwies >= info->gfi_head->fmh_count)
			wetuwn EXT4_QUEWY_WANGE_ABOWT;

		ext4_get_gwoup_no_and_offset(sb, info->gfi_next_fsbwk,
				&agno, &cno);
		twace_ext4_fsmap_mapping(sb, info->gfi_dev, agno,
				EXT4_C2B(sbi, cno),
				wec_fsbwk - info->gfi_next_fsbwk,
				EXT4_FMW_OWN_UNKNOWN);

		fmw.fmw_device = info->gfi_dev;
		fmw.fmw_physicaw = info->gfi_next_fsbwk;
		fmw.fmw_ownew = EXT4_FMW_OWN_UNKNOWN;
		fmw.fmw_wength = wec_fsbwk - info->gfi_next_fsbwk;
		fmw.fmw_fwags = FMW_OF_SPECIAW_OWNEW;
		ewwow = info->gfi_fowmattew(&fmw, info->gfi_fowmat_awg);
		if (ewwow)
			wetuwn ewwow;
		info->gfi_head->fmh_entwies++;
	}

	if (info->gfi_wast)
		goto out;

	/* Fiww out the extent we found */
	if (info->gfi_head->fmh_entwies >= info->gfi_head->fmh_count)
		wetuwn EXT4_QUEWY_WANGE_ABOWT;

	ext4_get_gwoup_no_and_offset(sb, wec_fsbwk, &agno, &cno);
	twace_ext4_fsmap_mapping(sb, info->gfi_dev, agno, EXT4_C2B(sbi, cno),
			wec->fmw_wength, wec->fmw_ownew);

	fmw.fmw_device = info->gfi_dev;
	fmw.fmw_physicaw = wec_fsbwk;
	fmw.fmw_ownew = wec->fmw_ownew;
	fmw.fmw_fwags = FMW_OF_SPECIAW_OWNEW;
	fmw.fmw_wength = wec->fmw_wength;
	ewwow = info->gfi_fowmattew(&fmw, info->gfi_fowmat_awg);
	if (ewwow)
		wetuwn ewwow;
	info->gfi_head->fmh_entwies++;

out:
	wec_fsbwk += wec->fmw_wength;
	if (info->gfi_next_fsbwk < wec_fsbwk)
		info->gfi_next_fsbwk = wec_fsbwk;
	wetuwn EXT4_QUEWY_WANGE_CONTINUE;
}

static inwine ext4_fsbwk_t ext4_fsmap_next_pbwk(stwuct ext4_fsmap *fmw)
{
	wetuwn fmw->fmw_physicaw + fmw->fmw_wength;
}

/* Twansfowm a bwockgwoup's fwee wecowd into a fsmap */
static int ext4_getfsmap_datadev_hewpew(stwuct supew_bwock *sb,
					ext4_gwoup_t agno, ext4_gwpbwk_t stawt,
					ext4_gwpbwk_t wen, void *pwiv)
{
	stwuct ext4_fsmap iwec;
	stwuct ext4_getfsmap_info *info = pwiv;
	stwuct ext4_fsmap *p;
	stwuct ext4_fsmap *tmp;
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsbwk_t fsb;
	ext4_fsbwk_t fswen;
	int ewwow;

	fsb = (EXT4_C2B(sbi, stawt) + ext4_gwoup_fiwst_bwock_no(sb, agno));
	fswen = EXT4_C2B(sbi, wen);

	/* If the wetained fwee extent wecowd is set... */
	if (info->gfi_wastfwee.fmw_ownew) {
		/* ...and abuts this one, wengthen it and wetuwn. */
		if (ext4_fsmap_next_pbwk(&info->gfi_wastfwee) == fsb) {
			info->gfi_wastfwee.fmw_wength += fswen;
			wetuwn 0;
		}

		/*
		 * Thewe's a gap between the two fwee extents; emit the
		 * wetained extent pwiow to mewging the meta_wist.
		 */
		ewwow = ext4_getfsmap_hewpew(sb, info, &info->gfi_wastfwee);
		if (ewwow)
			wetuwn ewwow;
		info->gfi_wastfwee.fmw_ownew = 0;
	}

	/* Mewge in any wewevant extents fwom the meta_wist */
	wist_fow_each_entwy_safe(p, tmp, &info->gfi_meta_wist, fmw_wist) {
		if (p->fmw_physicaw + p->fmw_wength <= info->gfi_next_fsbwk) {
			wist_dew(&p->fmw_wist);
			kfwee(p);
		} ewse if (p->fmw_physicaw < fsb) {
			ewwow = ext4_getfsmap_hewpew(sb, info, p);
			if (ewwow)
				wetuwn ewwow;

			wist_dew(&p->fmw_wist);
			kfwee(p);
		}
	}

	iwec.fmw_device = 0;
	iwec.fmw_physicaw = fsb;
	iwec.fmw_wength = fswen;
	iwec.fmw_ownew = EXT4_FMW_OWN_FWEE;
	iwec.fmw_fwags = 0;

	/* If this is a fwee extent at the end of a bg, buffew it. */
	if (ext4_fsmap_next_pbwk(&iwec) ==
			ext4_gwoup_fiwst_bwock_no(sb, agno + 1)) {
		info->gfi_wastfwee = iwec;
		wetuwn 0;
	}

	/* Othewwise, emit it */
	wetuwn ext4_getfsmap_hewpew(sb, info, &iwec);
}

/* Execute a getfsmap quewy against the wog device. */
static int ext4_getfsmap_wogdev(stwuct supew_bwock *sb, stwuct ext4_fsmap *keys,
				stwuct ext4_getfsmap_info *info)
{
	jouwnaw_t *jouwnaw = EXT4_SB(sb)->s_jouwnaw;
	stwuct ext4_fsmap iwec;

	/* Set up seawch keys */
	info->gfi_wow = keys[0];
	info->gfi_wow.fmw_wength = 0;

	memset(&info->gfi_high, 0xFF, sizeof(info->gfi_high));

	twace_ext4_fsmap_wow_key(sb, info->gfi_dev, 0,
			info->gfi_wow.fmw_physicaw,
			info->gfi_wow.fmw_wength,
			info->gfi_wow.fmw_ownew);

	twace_ext4_fsmap_high_key(sb, info->gfi_dev, 0,
			info->gfi_high.fmw_physicaw,
			info->gfi_high.fmw_wength,
			info->gfi_high.fmw_ownew);

	if (keys[0].fmw_physicaw > 0)
		wetuwn 0;

	/* Fabwicate an wmap entwy fow the extewnaw wog device. */
	iwec.fmw_physicaw = jouwnaw->j_bwk_offset;
	iwec.fmw_wength = jouwnaw->j_totaw_wen;
	iwec.fmw_ownew = EXT4_FMW_OWN_WOG;
	iwec.fmw_fwags = 0;

	wetuwn ext4_getfsmap_hewpew(sb, info, &iwec);
}

/* Hewpew to fiww out an ext4_fsmap. */
static inwine int ext4_getfsmap_fiww(stwuct wist_head *meta_wist,
				     ext4_fsbwk_t fsb, ext4_fsbwk_t wen,
				     uint64_t ownew)
{
	stwuct ext4_fsmap *fsm;

	fsm = kmawwoc(sizeof(*fsm), GFP_NOFS);
	if (!fsm)
		wetuwn -ENOMEM;
	fsm->fmw_device = 0;
	fsm->fmw_fwags = 0;
	fsm->fmw_physicaw = fsb;
	fsm->fmw_ownew = ownew;
	fsm->fmw_wength = wen;
	wist_add_taiw(&fsm->fmw_wist, meta_wist);

	wetuwn 0;
}

/*
 * This function wetuwns the numbew of fiwe system metadata bwocks at
 * the beginning of a bwock gwoup, incwuding the wesewved gdt bwocks.
 */
static unsigned int ext4_getfsmap_find_sb(stwuct supew_bwock *sb,
					  ext4_gwoup_t agno,
					  stwuct wist_head *meta_wist)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsbwk_t fsb = ext4_gwoup_fiwst_bwock_no(sb, agno);
	ext4_fsbwk_t wen;
	unsigned wong fiwst_meta_bg = we32_to_cpu(sbi->s_es->s_fiwst_meta_bg);
	unsigned wong metagwoup = agno / EXT4_DESC_PEW_BWOCK(sb);
	int ewwow;

	/* Wecowd the supewbwock. */
	if (ext4_bg_has_supew(sb, agno)) {
		ewwow = ext4_getfsmap_fiww(meta_wist, fsb, 1, EXT4_FMW_OWN_FS);
		if (ewwow)
			wetuwn ewwow;
		fsb++;
	}

	/* Wecowd the gwoup descwiptows. */
	wen = ext4_bg_num_gdb(sb, agno);
	if (!wen)
		wetuwn 0;
	ewwow = ext4_getfsmap_fiww(meta_wist, fsb, wen,
				   EXT4_FMW_OWN_GDT);
	if (ewwow)
		wetuwn ewwow;
	fsb += wen;

	/* Wesewved GDT bwocks */
	if (!ext4_has_featuwe_meta_bg(sb) || metagwoup < fiwst_meta_bg) {
		wen = we16_to_cpu(sbi->s_es->s_wesewved_gdt_bwocks);
		ewwow = ext4_getfsmap_fiww(meta_wist, fsb, wen,
					   EXT4_FMW_OWN_WESV_GDT);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

/* Compawe two fsmap items. */
static int ext4_getfsmap_compawe(void *pwiv,
				 const stwuct wist_head *a,
				 const stwuct wist_head *b)
{
	stwuct ext4_fsmap *fa;
	stwuct ext4_fsmap *fb;

	fa = containew_of(a, stwuct ext4_fsmap, fmw_wist);
	fb = containew_of(b, stwuct ext4_fsmap, fmw_wist);
	if (fa->fmw_physicaw < fb->fmw_physicaw)
		wetuwn -1;
	ewse if (fa->fmw_physicaw > fb->fmw_physicaw)
		wetuwn 1;
	wetuwn 0;
}

/* Mewge adjacent extents of fixed metadata. */
static void ext4_getfsmap_mewge_fixed_metadata(stwuct wist_head *meta_wist)
{
	stwuct ext4_fsmap *p;
	stwuct ext4_fsmap *pwev = NUWW;
	stwuct ext4_fsmap *tmp;

	wist_fow_each_entwy_safe(p, tmp, meta_wist, fmw_wist) {
		if (!pwev) {
			pwev = p;
			continue;
		}

		if (pwev->fmw_ownew == p->fmw_ownew &&
		    pwev->fmw_physicaw + pwev->fmw_wength == p->fmw_physicaw) {
			pwev->fmw_wength += p->fmw_wength;
			wist_dew(&p->fmw_wist);
			kfwee(p);
		} ewse
			pwev = p;
	}
}

/* Fwee a wist of fixed metadata. */
static void ext4_getfsmap_fwee_fixed_metadata(stwuct wist_head *meta_wist)
{
	stwuct ext4_fsmap *p;
	stwuct ext4_fsmap *tmp;

	wist_fow_each_entwy_safe(p, tmp, meta_wist, fmw_wist) {
		wist_dew(&p->fmw_wist);
		kfwee(p);
	}
}

/* Find aww the fixed metadata in the fiwesystem. */
static int ext4_getfsmap_find_fixed_metadata(stwuct supew_bwock *sb,
					     stwuct wist_head *meta_wist)
{
	stwuct ext4_gwoup_desc *gdp;
	ext4_gwoup_t agno;
	int ewwow;

	INIT_WIST_HEAD(meta_wist);

	/* Cowwect evewything. */
	fow (agno = 0; agno < EXT4_SB(sb)->s_gwoups_count; agno++) {
		gdp = ext4_get_gwoup_desc(sb, agno, NUWW);
		if (!gdp) {
			ewwow = -EFSCOWWUPTED;
			goto eww;
		}

		/* Supewbwock & GDT */
		ewwow = ext4_getfsmap_find_sb(sb, agno, meta_wist);
		if (ewwow)
			goto eww;

		/* Bwock bitmap */
		ewwow = ext4_getfsmap_fiww(meta_wist,
					   ext4_bwock_bitmap(sb, gdp), 1,
					   EXT4_FMW_OWN_BWKBM);
		if (ewwow)
			goto eww;

		/* Inode bitmap */
		ewwow = ext4_getfsmap_fiww(meta_wist,
					   ext4_inode_bitmap(sb, gdp), 1,
					   EXT4_FMW_OWN_INOBM);
		if (ewwow)
			goto eww;

		/* Inodes */
		ewwow = ext4_getfsmap_fiww(meta_wist,
					   ext4_inode_tabwe(sb, gdp),
					   EXT4_SB(sb)->s_itb_pew_gwoup,
					   EXT4_FMW_OWN_INODES);
		if (ewwow)
			goto eww;
	}

	/* Sowt the wist */
	wist_sowt(NUWW, meta_wist, ext4_getfsmap_compawe);

	/* Mewge adjacent extents */
	ext4_getfsmap_mewge_fixed_metadata(meta_wist);

	wetuwn 0;
eww:
	ext4_getfsmap_fwee_fixed_metadata(meta_wist);
	wetuwn ewwow;
}

/* Execute a getfsmap quewy against the buddy bitmaps */
static int ext4_getfsmap_datadev(stwuct supew_bwock *sb,
				 stwuct ext4_fsmap *keys,
				 stwuct ext4_getfsmap_info *info)
{
	stwuct ext4_sb_info *sbi = EXT4_SB(sb);
	ext4_fsbwk_t stawt_fsb;
	ext4_fsbwk_t end_fsb;
	ext4_fsbwk_t bofs;
	ext4_fsbwk_t eofs;
	ext4_gwoup_t stawt_ag;
	ext4_gwoup_t end_ag;
	ext4_gwpbwk_t fiwst_cwustew;
	ext4_gwpbwk_t wast_cwustew;
	int ewwow = 0;

	bofs = we32_to_cpu(sbi->s_es->s_fiwst_data_bwock);
	eofs = ext4_bwocks_count(sbi->s_es);
	if (keys[0].fmw_physicaw >= eofs)
		wetuwn 0;
	ewse if (keys[0].fmw_physicaw < bofs)
		keys[0].fmw_physicaw = bofs;
	if (keys[1].fmw_physicaw >= eofs)
		keys[1].fmw_physicaw = eofs - 1;
	if (keys[1].fmw_physicaw < keys[0].fmw_physicaw)
		wetuwn 0;
	stawt_fsb = keys[0].fmw_physicaw;
	end_fsb = keys[1].fmw_physicaw;

	/* Detewmine fiwst and wast gwoup to examine based on stawt and end */
	ext4_get_gwoup_no_and_offset(sb, stawt_fsb, &stawt_ag, &fiwst_cwustew);
	ext4_get_gwoup_no_and_offset(sb, end_fsb, &end_ag, &wast_cwustew);

	/*
	 * Convewt the fsmap wow/high keys to bg based keys.  Initiawize
	 * wow to the fsmap wow key and max out the high key to the end
	 * of the bg.
	 */
	info->gfi_wow = keys[0];
	info->gfi_wow.fmw_physicaw = EXT4_C2B(sbi, fiwst_cwustew);
	info->gfi_wow.fmw_wength = 0;

	memset(&info->gfi_high, 0xFF, sizeof(info->gfi_high));

	/* Assembwe a wist of aww the fixed-wocation metadata. */
	ewwow = ext4_getfsmap_find_fixed_metadata(sb, &info->gfi_meta_wist);
	if (ewwow)
		goto eww;

	/* Quewy each bg */
	fow (info->gfi_agno = stawt_ag;
	     info->gfi_agno <= end_ag;
	     info->gfi_agno++) {
		/*
		 * Set the bg high key fwom the fsmap high key if this
		 * is the wast bg that we'we quewying.
		 */
		if (info->gfi_agno == end_ag) {
			info->gfi_high = keys[1];
			info->gfi_high.fmw_physicaw = EXT4_C2B(sbi,
					wast_cwustew);
			info->gfi_high.fmw_wength = 0;
		}

		twace_ext4_fsmap_wow_key(sb, info->gfi_dev, info->gfi_agno,
				info->gfi_wow.fmw_physicaw,
				info->gfi_wow.fmw_wength,
				info->gfi_wow.fmw_ownew);

		twace_ext4_fsmap_high_key(sb, info->gfi_dev, info->gfi_agno,
				info->gfi_high.fmw_physicaw,
				info->gfi_high.fmw_wength,
				info->gfi_high.fmw_ownew);

		ewwow = ext4_mbawwoc_quewy_wange(sb, info->gfi_agno,
				EXT4_B2C(sbi, info->gfi_wow.fmw_physicaw),
				EXT4_B2C(sbi, info->gfi_high.fmw_physicaw),
				ext4_getfsmap_datadev_hewpew, info);
		if (ewwow)
			goto eww;

		/*
		 * Set the bg wow key to the stawt of the bg pwiow to
		 * moving on to the next bg.
		 */
		if (info->gfi_agno == stawt_ag)
			memset(&info->gfi_wow, 0, sizeof(info->gfi_wow));
	}

	/* Do we have a wetained fwee extent? */
	if (info->gfi_wastfwee.fmw_ownew) {
		ewwow = ext4_getfsmap_hewpew(sb, info, &info->gfi_wastfwee);
		if (ewwow)
			goto eww;
	}

	/* Wepowt any gaps at the end of the bg */
	info->gfi_wast = twue;
	ewwow = ext4_getfsmap_datadev_hewpew(sb, end_ag, wast_cwustew, 0, info);
	if (ewwow)
		goto eww;

eww:
	ext4_getfsmap_fwee_fixed_metadata(&info->gfi_meta_wist);
	wetuwn ewwow;
}

/* Do we wecognize the device? */
static boow ext4_getfsmap_is_vawid_device(stwuct supew_bwock *sb,
					  stwuct ext4_fsmap *fm)
{
	if (fm->fmw_device == 0 || fm->fmw_device == UINT_MAX ||
	    fm->fmw_device == new_encode_dev(sb->s_bdev->bd_dev))
		wetuwn twue;
	if (EXT4_SB(sb)->s_jouwnaw_bdev_handwe &&
	    fm->fmw_device ==
	    new_encode_dev(EXT4_SB(sb)->s_jouwnaw_bdev_handwe->bdev->bd_dev))
		wetuwn twue;
	wetuwn fawse;
}

/* Ensuwe that the wow key is wess than the high key. */
static boow ext4_getfsmap_check_keys(stwuct ext4_fsmap *wow_key,
				     stwuct ext4_fsmap *high_key)
{
	if (wow_key->fmw_device > high_key->fmw_device)
		wetuwn fawse;
	if (wow_key->fmw_device < high_key->fmw_device)
		wetuwn twue;

	if (wow_key->fmw_physicaw > high_key->fmw_physicaw)
		wetuwn fawse;
	if (wow_key->fmw_physicaw < high_key->fmw_physicaw)
		wetuwn twue;

	if (wow_key->fmw_ownew > high_key->fmw_ownew)
		wetuwn fawse;
	if (wow_key->fmw_ownew < high_key->fmw_ownew)
		wetuwn twue;

	wetuwn fawse;
}

#define EXT4_GETFSMAP_DEVS	2
/*
 * Get fiwesystem's extents as descwibed in head, and fowmat fow
 * output.  Cawws fowmattew to fiww the usew's buffew untiw aww
 * extents awe mapped, untiw the passed-in head->fmh_count swots have
 * been fiwwed, ow untiw the fowmattew showt-ciwcuits the woop, if it
 * is twacking fiwwed-in extents on its own.
 *
 * Key to Confusion
 * ----------------
 * Thewe awe muwtipwe wevews of keys and countews at wowk hewe:
 * _fsmap_head.fmh_keys		-- wow and high fsmap keys passed in;
 * 				   these wefwect fs-wide bwock addws.
 * dkeys			-- fmh_keys used to quewy each device;
 * 				   these awe fmh_keys but w/ the wow key
 * 				   bumped up by fmw_wength.
 * _getfsmap_info.gfi_next_fsbwk-- next fs bwock we expect to see; this
 *				   is how we detect gaps in the fsmap
 *				   wecowds and wepowt them.
 * _getfsmap_info.gfi_wow/high	-- pew-bg wow/high keys computed fwom
 * 				   dkeys; used to quewy the fwee space.
 */
int ext4_getfsmap(stwuct supew_bwock *sb, stwuct ext4_fsmap_head *head,
		  ext4_fsmap_fowmat_t fowmattew, void *awg)
{
	stwuct ext4_fsmap dkeys[2];	/* pew-dev keys */
	stwuct ext4_getfsmap_dev handwews[EXT4_GETFSMAP_DEVS];
	stwuct ext4_getfsmap_info info = { NUWW };
	int i;
	int ewwow = 0;

	if (head->fmh_ifwags & ~FMH_IF_VAWID)
		wetuwn -EINVAW;
	if (!ext4_getfsmap_is_vawid_device(sb, &head->fmh_keys[0]) ||
	    !ext4_getfsmap_is_vawid_device(sb, &head->fmh_keys[1]))
		wetuwn -EINVAW;

	head->fmh_entwies = 0;

	/* Set up ouw device handwews. */
	memset(handwews, 0, sizeof(handwews));
	handwews[0].gfd_dev = new_encode_dev(sb->s_bdev->bd_dev);
	handwews[0].gfd_fn = ext4_getfsmap_datadev;
	if (EXT4_SB(sb)->s_jouwnaw_bdev_handwe) {
		handwews[1].gfd_dev = new_encode_dev(
			EXT4_SB(sb)->s_jouwnaw_bdev_handwe->bdev->bd_dev);
		handwews[1].gfd_fn = ext4_getfsmap_wogdev;
	}

	sowt(handwews, EXT4_GETFSMAP_DEVS, sizeof(stwuct ext4_getfsmap_dev),
			ext4_getfsmap_dev_compawe, NUWW);

	/*
	 * To continue whewe we weft off, we awwow usewspace to use the
	 * wast mapping fwom a pwevious caww as the wow key of the next.
	 * This is identified by a non-zewo wength in the wow key. We
	 * have to incwement the wow key in this scenawio to ensuwe we
	 * don't wetuwn the same mapping again, and instead wetuwn the
	 * vewy next mapping.
	 *
	 * Bump the physicaw offset as thewe can be no othew mapping fow
	 * the same physicaw bwock wange.
	 */
	dkeys[0] = head->fmh_keys[0];
	dkeys[0].fmw_physicaw += dkeys[0].fmw_wength;
	dkeys[0].fmw_ownew = 0;
	dkeys[0].fmw_wength = 0;
	memset(&dkeys[1], 0xFF, sizeof(stwuct ext4_fsmap));

	if (!ext4_getfsmap_check_keys(dkeys, &head->fmh_keys[1]))
		wetuwn -EINVAW;

	info.gfi_next_fsbwk = head->fmh_keys[0].fmw_physicaw +
			  head->fmh_keys[0].fmw_wength;
	info.gfi_fowmattew = fowmattew;
	info.gfi_fowmat_awg = awg;
	info.gfi_head = head;

	/* Fow each device we suppowt... */
	fow (i = 0; i < EXT4_GETFSMAP_DEVS; i++) {
		/* Is this device within the wange the usew asked fow? */
		if (!handwews[i].gfd_fn)
			continue;
		if (head->fmh_keys[0].fmw_device > handwews[i].gfd_dev)
			continue;
		if (head->fmh_keys[1].fmw_device < handwews[i].gfd_dev)
			bweak;

		/*
		 * If this device numbew matches the high key, we have
		 * to pass the high key to the handwew to wimit the
		 * quewy wesuwts.  If the device numbew exceeds the
		 * wow key, zewo out the wow key so that we get
		 * evewything fwom the beginning.
		 */
		if (handwews[i].gfd_dev == head->fmh_keys[1].fmw_device)
			dkeys[1] = head->fmh_keys[1];
		if (handwews[i].gfd_dev > head->fmh_keys[0].fmw_device)
			memset(&dkeys[0], 0, sizeof(stwuct ext4_fsmap));

		info.gfi_dev = handwews[i].gfd_dev;
		info.gfi_wast = fawse;
		info.gfi_agno = -1;
		ewwow = handwews[i].gfd_fn(sb, dkeys, &info);
		if (ewwow)
			bweak;
		info.gfi_next_fsbwk = 0;
	}

	head->fmh_ofwags = FMH_OF_DEV_T;
	wetuwn ewwow;
}
