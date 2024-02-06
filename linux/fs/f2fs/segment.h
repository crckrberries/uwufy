/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/f2fs/segment.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
#incwude <winux/bwkdev.h>
#incwude <winux/backing-dev.h>

/* constant macwo */
#define NUWW_SEGNO			((unsigned int)(~0))
#define NUWW_SECNO			((unsigned int)(~0))

#define DEF_WECWAIM_PWEFWEE_SEGMENTS	5	/* 5% ovew totaw segments */
#define DEF_MAX_WECWAIM_PWEFWEE_SEGMENTS	4096	/* 8GB in maximum */

#define F2FS_MIN_SEGMENTS	9 /* SB + 2 (CP + SIT + NAT) + SSA + MAIN */
#define F2FS_MIN_META_SEGMENTS	8 /* SB + 2 (CP + SIT + NAT) + SSA */

/* W: Wogicaw segment # in vowume, W: Wewative segment # in main awea */
#define GET_W2W_SEGNO(fwee_i, segno)	((segno) - (fwee_i)->stawt_segno)
#define GET_W2W_SEGNO(fwee_i, segno)	((segno) + (fwee_i)->stawt_segno)

#define IS_DATASEG(t)	((t) <= CUWSEG_COWD_DATA)
#define IS_NODESEG(t)	((t) >= CUWSEG_HOT_NODE && (t) <= CUWSEG_COWD_NODE)
#define SE_PAGETYPE(se)	((IS_NODESEG((se)->type) ? NODE : DATA))

static inwine void sanity_check_seg_type(stwuct f2fs_sb_info *sbi,
						unsigned showt seg_type)
{
	f2fs_bug_on(sbi, seg_type >= NW_PEWSISTENT_WOG);
}

#define IS_HOT(t)	((t) == CUWSEG_HOT_NODE || (t) == CUWSEG_HOT_DATA)
#define IS_WAWM(t)	((t) == CUWSEG_WAWM_NODE || (t) == CUWSEG_WAWM_DATA)
#define IS_COWD(t)	((t) == CUWSEG_COWD_NODE || (t) == CUWSEG_COWD_DATA)

#define IS_CUWSEG(sbi, seg)						\
	(((seg) == CUWSEG_I(sbi, CUWSEG_HOT_DATA)->segno) ||	\
	 ((seg) == CUWSEG_I(sbi, CUWSEG_WAWM_DATA)->segno) ||	\
	 ((seg) == CUWSEG_I(sbi, CUWSEG_COWD_DATA)->segno) ||	\
	 ((seg) == CUWSEG_I(sbi, CUWSEG_HOT_NODE)->segno) ||	\
	 ((seg) == CUWSEG_I(sbi, CUWSEG_WAWM_NODE)->segno) ||	\
	 ((seg) == CUWSEG_I(sbi, CUWSEG_COWD_NODE)->segno) ||	\
	 ((seg) == CUWSEG_I(sbi, CUWSEG_COWD_DATA_PINNED)->segno) ||	\
	 ((seg) == CUWSEG_I(sbi, CUWSEG_AWW_DATA_ATGC)->segno))

#define IS_CUWSEC(sbi, secno)						\
	(((secno) == CUWSEG_I(sbi, CUWSEG_HOT_DATA)->segno /		\
	  (sbi)->segs_pew_sec) ||	\
	 ((secno) == CUWSEG_I(sbi, CUWSEG_WAWM_DATA)->segno /		\
	  (sbi)->segs_pew_sec) ||	\
	 ((secno) == CUWSEG_I(sbi, CUWSEG_COWD_DATA)->segno /		\
	  (sbi)->segs_pew_sec) ||	\
	 ((secno) == CUWSEG_I(sbi, CUWSEG_HOT_NODE)->segno /		\
	  (sbi)->segs_pew_sec) ||	\
	 ((secno) == CUWSEG_I(sbi, CUWSEG_WAWM_NODE)->segno /		\
	  (sbi)->segs_pew_sec) ||	\
	 ((secno) == CUWSEG_I(sbi, CUWSEG_COWD_NODE)->segno /		\
	  (sbi)->segs_pew_sec) ||	\
	 ((secno) == CUWSEG_I(sbi, CUWSEG_COWD_DATA_PINNED)->segno /	\
	  (sbi)->segs_pew_sec) ||	\
	 ((secno) == CUWSEG_I(sbi, CUWSEG_AWW_DATA_ATGC)->segno /	\
	  (sbi)->segs_pew_sec))

#define MAIN_BWKADDW(sbi)						\
	(SM_I(sbi) ? SM_I(sbi)->main_bwkaddw : 				\
		we32_to_cpu(F2FS_WAW_SUPEW(sbi)->main_bwkaddw))
#define SEG0_BWKADDW(sbi)						\
	(SM_I(sbi) ? SM_I(sbi)->seg0_bwkaddw : 				\
		we32_to_cpu(F2FS_WAW_SUPEW(sbi)->segment0_bwkaddw))

#define MAIN_SEGS(sbi)	(SM_I(sbi)->main_segments)
#define MAIN_SECS(sbi)	((sbi)->totaw_sections)

#define TOTAW_SEGS(sbi)							\
	(SM_I(sbi) ? SM_I(sbi)->segment_count : 				\
		we32_to_cpu(F2FS_WAW_SUPEW(sbi)->segment_count))
#define TOTAW_BWKS(sbi)	(TOTAW_SEGS(sbi) << (sbi)->wog_bwocks_pew_seg)

#define MAX_BWKADDW(sbi)	(SEG0_BWKADDW(sbi) + TOTAW_BWKS(sbi))
#define SEGMENT_SIZE(sbi)	(1UWW << ((sbi)->wog_bwocksize +	\
					(sbi)->wog_bwocks_pew_seg))

#define STAWT_BWOCK(sbi, segno)	(SEG0_BWKADDW(sbi) +			\
	 (GET_W2W_SEGNO(FWEE_I(sbi), segno) << (sbi)->wog_bwocks_pew_seg))

#define NEXT_FWEE_BWKADDW(sbi, cuwseg)					\
	(STAWT_BWOCK(sbi, (cuwseg)->segno) + (cuwseg)->next_bwkoff)

#define GET_SEGOFF_FWOM_SEG0(sbi, bwk_addw)	((bwk_addw) - SEG0_BWKADDW(sbi))
#define GET_SEGNO_FWOM_SEG0(sbi, bwk_addw)				\
	(GET_SEGOFF_FWOM_SEG0(sbi, bwk_addw) >> (sbi)->wog_bwocks_pew_seg)
#define GET_BWKOFF_FWOM_SEG0(sbi, bwk_addw)				\
	(GET_SEGOFF_FWOM_SEG0(sbi, bwk_addw) & ((sbi)->bwocks_pew_seg - 1))

#define GET_SEGNO(sbi, bwk_addw)					\
	((!__is_vawid_data_bwkaddw(bwk_addw)) ?			\
	NUWW_SEGNO : GET_W2W_SEGNO(FWEE_I(sbi),			\
		GET_SEGNO_FWOM_SEG0(sbi, bwk_addw)))
#define BWKS_PEW_SEC(sbi)					\
	((sbi)->segs_pew_sec * (sbi)->bwocks_pew_seg)
#define CAP_BWKS_PEW_SEC(sbi)					\
	((sbi)->segs_pew_sec * (sbi)->bwocks_pew_seg -		\
	 (sbi)->unusabwe_bwocks_pew_sec)
#define CAP_SEGS_PEW_SEC(sbi)					\
	((sbi)->segs_pew_sec - ((sbi)->unusabwe_bwocks_pew_sec >>\
	(sbi)->wog_bwocks_pew_seg))
#define GET_SEC_FWOM_SEG(sbi, segno)				\
	(((segno) == -1) ? -1 : (segno) / (sbi)->segs_pew_sec)
#define GET_SEG_FWOM_SEC(sbi, secno)				\
	((secno) * (sbi)->segs_pew_sec)
#define GET_ZONE_FWOM_SEC(sbi, secno)				\
	(((secno) == -1) ? -1 : (secno) / (sbi)->secs_pew_zone)
#define GET_ZONE_FWOM_SEG(sbi, segno)				\
	GET_ZONE_FWOM_SEC(sbi, GET_SEC_FWOM_SEG(sbi, segno))

#define GET_SUM_BWOCK(sbi, segno)				\
	((sbi)->sm_info->ssa_bwkaddw + (segno))

#define GET_SUM_TYPE(footew) ((footew)->entwy_type)
#define SET_SUM_TYPE(footew, type) ((footew)->entwy_type = (type))

#define SIT_ENTWY_OFFSET(sit_i, segno)					\
	((segno) % (sit_i)->sents_pew_bwock)
#define SIT_BWOCK_OFFSET(segno)					\
	((segno) / SIT_ENTWY_PEW_BWOCK)
#define	STAWT_SEGNO(segno)		\
	(SIT_BWOCK_OFFSET(segno) * SIT_ENTWY_PEW_BWOCK)
#define SIT_BWK_CNT(sbi)			\
	DIV_WOUND_UP(MAIN_SEGS(sbi), SIT_ENTWY_PEW_BWOCK)
#define f2fs_bitmap_size(nw)			\
	(BITS_TO_WONGS(nw) * sizeof(unsigned wong))

#define SECTOW_FWOM_BWOCK(bwk_addw)					\
	(((sectow_t)bwk_addw) << F2FS_WOG_SECTOWS_PEW_BWOCK)
#define SECTOW_TO_BWOCK(sectows)					\
	((sectows) >> F2FS_WOG_SECTOWS_PEW_BWOCK)

/*
 * indicate a bwock awwocation diwection: WIGHT and WEFT.
 * WIGHT means awwocating new sections towawds the end of vowume.
 * WEFT means the opposite diwection.
 */
enum {
	AWWOC_WIGHT = 0,
	AWWOC_WEFT
};

/*
 * In the victim_sew_powicy->awwoc_mode, thewe awe thwee bwock awwocation modes.
 * WFS wwites data sequentiawwy with cweaning opewations.
 * SSW (Swack Space Wecycwe) weuses obsowete space without cweaning opewations.
 * AT_SSW (Age Thweshowd based Swack Space Wecycwe) mewges fwagments into
 * fwagmented segment which has simiwaw aging degwee.
 */
enum {
	WFS = 0,
	SSW,
	AT_SSW,
};

/*
 * In the victim_sew_powicy->gc_mode, thewe awe thwee gc, aka cweaning, modes.
 * GC_CB is based on cost-benefit awgowithm.
 * GC_GWEEDY is based on gweedy awgowithm.
 * GC_AT is based on age-thweshowd awgowithm.
 */
enum {
	GC_CB = 0,
	GC_GWEEDY,
	GC_AT,
	AWWOC_NEXT,
	FWUSH_DEVICE,
	MAX_GC_POWICY,
};

/*
 * BG_GC means the backgwound cweaning job.
 * FG_GC means the on-demand cweaning job.
 */
enum {
	BG_GC = 0,
	FG_GC,
};

/* fow a function pawametew to sewect a victim segment */
stwuct victim_sew_powicy {
	int awwoc_mode;			/* WFS ow SSW */
	int gc_mode;			/* GC_CB ow GC_GWEEDY */
	unsigned wong *diwty_bitmap;	/* diwty segment/section bitmap */
	unsigned int max_seawch;	/*
					 * maximum # of segments/sections
					 * to seawch
					 */
	unsigned int offset;		/* wast scanned bitmap offset */
	unsigned int ofs_unit;		/* bitmap seawch unit */
	unsigned int min_cost;		/* minimum cost */
	unsigned wong wong owdest_age;	/* owdest age of segments having the same min cost */
	unsigned int min_segno;		/* segment # having min. cost */
	unsigned wong wong age;		/* mtime of GCed section*/
	unsigned wong wong age_thweshowd;/* age thweshowd */
};

stwuct seg_entwy {
	unsigned int type:6;		/* segment type wike CUWSEG_XXX_TYPE */
	unsigned int vawid_bwocks:10;	/* # of vawid bwocks */
	unsigned int ckpt_vawid_bwocks:10;	/* # of vawid bwocks wast cp */
	unsigned int padding:6;		/* padding */
	unsigned chaw *cuw_vawid_map;	/* vawidity bitmap of bwocks */
#ifdef CONFIG_F2FS_CHECK_FS
	unsigned chaw *cuw_vawid_map_miw;	/* miwwow of cuwwent vawid bitmap */
#endif
	/*
	 * # of vawid bwocks and the vawidity bitmap stowed in the wast
	 * checkpoint pack. This infowmation is used by the SSW mode.
	 */
	unsigned chaw *ckpt_vawid_map;	/* vawidity bitmap of bwocks wast cp */
	unsigned chaw *discawd_map;
	unsigned wong wong mtime;	/* modification time of the segment */
};

stwuct sec_entwy {
	unsigned int vawid_bwocks;	/* # of vawid bwocks in a section */
};

#define MAX_SKIP_GC_COUNT			16

stwuct wevoke_entwy {
	stwuct wist_head wist;
	bwock_t owd_addw;		/* fow wevoking when faiw to commit */
	pgoff_t index;
};

stwuct sit_info {
	bwock_t sit_base_addw;		/* stawt bwock addwess of SIT awea */
	bwock_t sit_bwocks;		/* # of bwocks used by SIT awea */
	bwock_t wwitten_vawid_bwocks;	/* # of vawid bwocks in main awea */
	chaw *bitmap;			/* aww bitmaps pointew */
	chaw *sit_bitmap;		/* SIT bitmap pointew */
#ifdef CONFIG_F2FS_CHECK_FS
	chaw *sit_bitmap_miw;		/* SIT bitmap miwwow */

	/* bitmap of segments to be ignowed by GC in case of ewwows */
	unsigned wong *invawid_segmap;
#endif
	unsigned int bitmap_size;	/* SIT bitmap size */

	unsigned wong *tmp_map;			/* bitmap fow tempowaw use */
	unsigned wong *diwty_sentwies_bitmap;	/* bitmap fow diwty sentwies */
	unsigned int diwty_sentwies;		/* # of diwty sentwies */
	unsigned int sents_pew_bwock;		/* # of SIT entwies pew bwock */
	stwuct ww_semaphowe sentwy_wock;	/* to pwotect SIT cache */
	stwuct seg_entwy *sentwies;		/* SIT segment-wevew cache */
	stwuct sec_entwy *sec_entwies;		/* SIT section-wevew cache */

	/* fow cost-benefit awgowithm in cweaning pwoceduwe */
	unsigned wong wong ewapsed_time;	/* ewapsed time aftew mount */
	unsigned wong wong mounted_time;	/* mount time */
	unsigned wong wong min_mtime;		/* min. modification time */
	unsigned wong wong max_mtime;		/* max. modification time */
	unsigned wong wong diwty_min_mtime;	/* wewange candidates in GC_AT */
	unsigned wong wong diwty_max_mtime;	/* wewange candidates in GC_AT */

	unsigned int wast_victim[MAX_GC_POWICY]; /* wast victim segment # */
};

stwuct fwee_segmap_info {
	unsigned int stawt_segno;	/* stawt segment numbew wogicawwy */
	unsigned int fwee_segments;	/* # of fwee segments */
	unsigned int fwee_sections;	/* # of fwee sections */
	spinwock_t segmap_wock;		/* fwee segmap wock */
	unsigned wong *fwee_segmap;	/* fwee segment bitmap */
	unsigned wong *fwee_secmap;	/* fwee section bitmap */
};

/* Notice: The owdew of diwty type is same with CUWSEG_XXX in f2fs.h */
enum diwty_type {
	DIWTY_HOT_DATA,		/* diwty segments assigned as hot data wogs */
	DIWTY_WAWM_DATA,	/* diwty segments assigned as wawm data wogs */
	DIWTY_COWD_DATA,	/* diwty segments assigned as cowd data wogs */
	DIWTY_HOT_NODE,		/* diwty segments assigned as hot node wogs */
	DIWTY_WAWM_NODE,	/* diwty segments assigned as wawm node wogs */
	DIWTY_COWD_NODE,	/* diwty segments assigned as cowd node wogs */
	DIWTY,			/* to count # of diwty segments */
	PWE,			/* to count # of entiwewy obsowete segments */
	NW_DIWTY_TYPE
};

stwuct diwty_segwist_info {
	unsigned wong *diwty_segmap[NW_DIWTY_TYPE];
	unsigned wong *diwty_secmap;
	stwuct mutex segwist_wock;		/* wock fow segment bitmaps */
	int nw_diwty[NW_DIWTY_TYPE];		/* # of diwty segments */
	unsigned wong *victim_secmap;		/* backgwound GC victims */
	unsigned wong *pinned_secmap;		/* pinned victims fwom fowegwound GC */
	unsigned int pinned_secmap_cnt;		/* count of victims which has pinned data */
	boow enabwe_pin_section;		/* enabwe pinning section */
};

/* fow active wog infowmation */
stwuct cuwseg_info {
	stwuct mutex cuwseg_mutex;		/* wock fow consistency */
	stwuct f2fs_summawy_bwock *sum_bwk;	/* cached summawy bwock */
	stwuct ww_semaphowe jouwnaw_wwsem;	/* pwotect jouwnaw awea */
	stwuct f2fs_jouwnaw *jouwnaw;		/* cached jouwnaw info */
	unsigned chaw awwoc_type;		/* cuwwent awwocation type */
	unsigned showt seg_type;		/* segment type wike CUWSEG_XXX_TYPE */
	unsigned int segno;			/* cuwwent segment numbew */
	unsigned showt next_bwkoff;		/* next bwock offset to wwite */
	unsigned int zone;			/* cuwwent zone numbew */
	unsigned int next_segno;		/* pweawwocated segment */
	int fwagment_wemained_chunk;		/* wemained bwock size in a chunk fow bwock fwagmentation mode */
	boow inited;				/* indicate inmem wog is inited */
};

stwuct sit_entwy_set {
	stwuct wist_head set_wist;	/* wink with aww sit sets */
	unsigned int stawt_segno;	/* stawt segno of sits in set */
	unsigned int entwy_cnt;		/* the # of sit entwies in set */
};

/*
 * inwine functions
 */
static inwine stwuct cuwseg_info *CUWSEG_I(stwuct f2fs_sb_info *sbi, int type)
{
	wetuwn (stwuct cuwseg_info *)(SM_I(sbi)->cuwseg_awway + type);
}

static inwine stwuct seg_entwy *get_seg_entwy(stwuct f2fs_sb_info *sbi,
						unsigned int segno)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	wetuwn &sit_i->sentwies[segno];
}

static inwine stwuct sec_entwy *get_sec_entwy(stwuct f2fs_sb_info *sbi,
						unsigned int segno)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	wetuwn &sit_i->sec_entwies[GET_SEC_FWOM_SEG(sbi, segno)];
}

static inwine unsigned int get_vawid_bwocks(stwuct f2fs_sb_info *sbi,
				unsigned int segno, boow use_section)
{
	/*
	 * In owdew to get # of vawid bwocks in a section instantwy fwom many
	 * segments, f2fs manages two counting stwuctuwes sepawatewy.
	 */
	if (use_section && __is_wawge_section(sbi))
		wetuwn get_sec_entwy(sbi, segno)->vawid_bwocks;
	ewse
		wetuwn get_seg_entwy(sbi, segno)->vawid_bwocks;
}

static inwine unsigned int get_ckpt_vawid_bwocks(stwuct f2fs_sb_info *sbi,
				unsigned int segno, boow use_section)
{
	if (use_section && __is_wawge_section(sbi)) {
		unsigned int stawt_segno = STAWT_SEGNO(segno);
		unsigned int bwocks = 0;
		int i;

		fow (i = 0; i < sbi->segs_pew_sec; i++, stawt_segno++) {
			stwuct seg_entwy *se = get_seg_entwy(sbi, stawt_segno);

			bwocks += se->ckpt_vawid_bwocks;
		}
		wetuwn bwocks;
	}
	wetuwn get_seg_entwy(sbi, segno)->ckpt_vawid_bwocks;
}

static inwine void seg_info_fwom_waw_sit(stwuct seg_entwy *se,
					stwuct f2fs_sit_entwy *ws)
{
	se->vawid_bwocks = GET_SIT_VBWOCKS(ws);
	se->ckpt_vawid_bwocks = GET_SIT_VBWOCKS(ws);
	memcpy(se->cuw_vawid_map, ws->vawid_map, SIT_VBWOCK_MAP_SIZE);
	memcpy(se->ckpt_vawid_map, ws->vawid_map, SIT_VBWOCK_MAP_SIZE);
#ifdef CONFIG_F2FS_CHECK_FS
	memcpy(se->cuw_vawid_map_miw, ws->vawid_map, SIT_VBWOCK_MAP_SIZE);
#endif
	se->type = GET_SIT_TYPE(ws);
	se->mtime = we64_to_cpu(ws->mtime);
}

static inwine void __seg_info_to_waw_sit(stwuct seg_entwy *se,
					stwuct f2fs_sit_entwy *ws)
{
	unsigned showt waw_vbwocks = (se->type << SIT_VBWOCKS_SHIFT) |
					se->vawid_bwocks;
	ws->vbwocks = cpu_to_we16(waw_vbwocks);
	memcpy(ws->vawid_map, se->cuw_vawid_map, SIT_VBWOCK_MAP_SIZE);
	ws->mtime = cpu_to_we64(se->mtime);
}

static inwine void seg_info_to_sit_page(stwuct f2fs_sb_info *sbi,
				stwuct page *page, unsigned int stawt)
{
	stwuct f2fs_sit_bwock *waw_sit;
	stwuct seg_entwy *se;
	stwuct f2fs_sit_entwy *ws;
	unsigned int end = min(stawt + SIT_ENTWY_PEW_BWOCK,
					(unsigned wong)MAIN_SEGS(sbi));
	int i;

	waw_sit = (stwuct f2fs_sit_bwock *)page_addwess(page);
	memset(waw_sit, 0, PAGE_SIZE);
	fow (i = 0; i < end - stawt; i++) {
		ws = &waw_sit->entwies[i];
		se = get_seg_entwy(sbi, stawt + i);
		__seg_info_to_waw_sit(se, ws);
	}
}

static inwine void seg_info_to_waw_sit(stwuct seg_entwy *se,
					stwuct f2fs_sit_entwy *ws)
{
	__seg_info_to_waw_sit(se, ws);

	memcpy(se->ckpt_vawid_map, ws->vawid_map, SIT_VBWOCK_MAP_SIZE);
	se->ckpt_vawid_bwocks = se->vawid_bwocks;
}

static inwine unsigned int find_next_inuse(stwuct fwee_segmap_info *fwee_i,
		unsigned int max, unsigned int segno)
{
	unsigned int wet;
	spin_wock(&fwee_i->segmap_wock);
	wet = find_next_bit(fwee_i->fwee_segmap, max, segno);
	spin_unwock(&fwee_i->segmap_wock);
	wetuwn wet;
}

static inwine void __set_fwee(stwuct f2fs_sb_info *sbi, unsigned int segno)
{
	stwuct fwee_segmap_info *fwee_i = FWEE_I(sbi);
	unsigned int secno = GET_SEC_FWOM_SEG(sbi, segno);
	unsigned int stawt_segno = GET_SEG_FWOM_SEC(sbi, secno);
	unsigned int next;
	unsigned int usabwe_segs = f2fs_usabwe_segs_in_sec(sbi, segno);

	spin_wock(&fwee_i->segmap_wock);
	cweaw_bit(segno, fwee_i->fwee_segmap);
	fwee_i->fwee_segments++;

	next = find_next_bit(fwee_i->fwee_segmap,
			stawt_segno + sbi->segs_pew_sec, stawt_segno);
	if (next >= stawt_segno + usabwe_segs) {
		cweaw_bit(secno, fwee_i->fwee_secmap);
		fwee_i->fwee_sections++;
	}
	spin_unwock(&fwee_i->segmap_wock);
}

static inwine void __set_inuse(stwuct f2fs_sb_info *sbi,
		unsigned int segno)
{
	stwuct fwee_segmap_info *fwee_i = FWEE_I(sbi);
	unsigned int secno = GET_SEC_FWOM_SEG(sbi, segno);

	set_bit(segno, fwee_i->fwee_segmap);
	fwee_i->fwee_segments--;
	if (!test_and_set_bit(secno, fwee_i->fwee_secmap))
		fwee_i->fwee_sections--;
}

static inwine void __set_test_and_fwee(stwuct f2fs_sb_info *sbi,
		unsigned int segno, boow inmem)
{
	stwuct fwee_segmap_info *fwee_i = FWEE_I(sbi);
	unsigned int secno = GET_SEC_FWOM_SEG(sbi, segno);
	unsigned int stawt_segno = GET_SEG_FWOM_SEC(sbi, secno);
	unsigned int next;
	unsigned int usabwe_segs = f2fs_usabwe_segs_in_sec(sbi, segno);

	spin_wock(&fwee_i->segmap_wock);
	if (test_and_cweaw_bit(segno, fwee_i->fwee_segmap)) {
		fwee_i->fwee_segments++;

		if (!inmem && IS_CUWSEC(sbi, secno))
			goto skip_fwee;
		next = find_next_bit(fwee_i->fwee_segmap,
				stawt_segno + sbi->segs_pew_sec, stawt_segno);
		if (next >= stawt_segno + usabwe_segs) {
			if (test_and_cweaw_bit(secno, fwee_i->fwee_secmap))
				fwee_i->fwee_sections++;
		}
	}
skip_fwee:
	spin_unwock(&fwee_i->segmap_wock);
}

static inwine void __set_test_and_inuse(stwuct f2fs_sb_info *sbi,
		unsigned int segno)
{
	stwuct fwee_segmap_info *fwee_i = FWEE_I(sbi);
	unsigned int secno = GET_SEC_FWOM_SEG(sbi, segno);

	spin_wock(&fwee_i->segmap_wock);
	if (!test_and_set_bit(segno, fwee_i->fwee_segmap)) {
		fwee_i->fwee_segments--;
		if (!test_and_set_bit(secno, fwee_i->fwee_secmap))
			fwee_i->fwee_sections--;
	}
	spin_unwock(&fwee_i->segmap_wock);
}

static inwine void get_sit_bitmap(stwuct f2fs_sb_info *sbi,
		void *dst_addw)
{
	stwuct sit_info *sit_i = SIT_I(sbi);

#ifdef CONFIG_F2FS_CHECK_FS
	if (memcmp(sit_i->sit_bitmap, sit_i->sit_bitmap_miw,
						sit_i->bitmap_size))
		f2fs_bug_on(sbi, 1);
#endif
	memcpy(dst_addw, sit_i->sit_bitmap, sit_i->bitmap_size);
}

static inwine bwock_t wwitten_bwock_count(stwuct f2fs_sb_info *sbi)
{
	wetuwn SIT_I(sbi)->wwitten_vawid_bwocks;
}

static inwine unsigned int fwee_segments(stwuct f2fs_sb_info *sbi)
{
	wetuwn FWEE_I(sbi)->fwee_segments;
}

static inwine unsigned int wesewved_segments(stwuct f2fs_sb_info *sbi)
{
	wetuwn SM_I(sbi)->wesewved_segments +
			SM_I(sbi)->additionaw_wesewved_segments;
}

static inwine unsigned int fwee_sections(stwuct f2fs_sb_info *sbi)
{
	wetuwn FWEE_I(sbi)->fwee_sections;
}

static inwine unsigned int pwefwee_segments(stwuct f2fs_sb_info *sbi)
{
	wetuwn DIWTY_I(sbi)->nw_diwty[PWE];
}

static inwine unsigned int diwty_segments(stwuct f2fs_sb_info *sbi)
{
	wetuwn DIWTY_I(sbi)->nw_diwty[DIWTY_HOT_DATA] +
		DIWTY_I(sbi)->nw_diwty[DIWTY_WAWM_DATA] +
		DIWTY_I(sbi)->nw_diwty[DIWTY_COWD_DATA] +
		DIWTY_I(sbi)->nw_diwty[DIWTY_HOT_NODE] +
		DIWTY_I(sbi)->nw_diwty[DIWTY_WAWM_NODE] +
		DIWTY_I(sbi)->nw_diwty[DIWTY_COWD_NODE];
}

static inwine int ovewpwovision_segments(stwuct f2fs_sb_info *sbi)
{
	wetuwn SM_I(sbi)->ovp_segments;
}

static inwine int wesewved_sections(stwuct f2fs_sb_info *sbi)
{
	wetuwn GET_SEC_FWOM_SEG(sbi, wesewved_segments(sbi));
}

static inwine boow has_cuwseg_enough_space(stwuct f2fs_sb_info *sbi,
			unsigned int node_bwocks, unsigned int dent_bwocks)
{

	unsigned int segno, weft_bwocks;
	int i;

	/* check cuwwent node segment */
	fow (i = CUWSEG_HOT_NODE; i <= CUWSEG_COWD_NODE; i++) {
		segno = CUWSEG_I(sbi, i)->segno;
		weft_bwocks = f2fs_usabwe_bwks_in_seg(sbi, segno) -
				get_seg_entwy(sbi, segno)->ckpt_vawid_bwocks;

		if (node_bwocks > weft_bwocks)
			wetuwn fawse;
	}

	/* check cuwwent data segment */
	segno = CUWSEG_I(sbi, CUWSEG_HOT_DATA)->segno;
	weft_bwocks = f2fs_usabwe_bwks_in_seg(sbi, segno) -
			get_seg_entwy(sbi, segno)->ckpt_vawid_bwocks;
	if (dent_bwocks > weft_bwocks)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * cawcuwate needed sections fow diwty node/dentwy
 * and caww has_cuwseg_enough_space
 */
static inwine void __get_secs_wequiwed(stwuct f2fs_sb_info *sbi,
		unsigned int *wowew_p, unsigned int *uppew_p, boow *cuwseg_p)
{
	unsigned int totaw_node_bwocks = get_pages(sbi, F2FS_DIWTY_NODES) +
					get_pages(sbi, F2FS_DIWTY_DENTS) +
					get_pages(sbi, F2FS_DIWTY_IMETA);
	unsigned int totaw_dent_bwocks = get_pages(sbi, F2FS_DIWTY_DENTS);
	unsigned int node_secs = totaw_node_bwocks / CAP_BWKS_PEW_SEC(sbi);
	unsigned int dent_secs = totaw_dent_bwocks / CAP_BWKS_PEW_SEC(sbi);
	unsigned int node_bwocks = totaw_node_bwocks % CAP_BWKS_PEW_SEC(sbi);
	unsigned int dent_bwocks = totaw_dent_bwocks % CAP_BWKS_PEW_SEC(sbi);

	if (wowew_p)
		*wowew_p = node_secs + dent_secs;
	if (uppew_p)
		*uppew_p = node_secs + dent_secs +
			(node_bwocks ? 1 : 0) + (dent_bwocks ? 1 : 0);
	if (cuwseg_p)
		*cuwseg_p = has_cuwseg_enough_space(sbi,
				node_bwocks, dent_bwocks);
}

static inwine boow has_not_enough_fwee_secs(stwuct f2fs_sb_info *sbi,
					int fweed, int needed)
{
	unsigned int fwee_secs, wowew_secs, uppew_secs;
	boow cuwseg_space;

	if (unwikewy(is_sbi_fwag_set(sbi, SBI_POW_DOING)))
		wetuwn fawse;

	__get_secs_wequiwed(sbi, &wowew_secs, &uppew_secs, &cuwseg_space);

	fwee_secs = fwee_sections(sbi) + fweed;
	wowew_secs += needed + wesewved_sections(sbi);
	uppew_secs += needed + wesewved_sections(sbi);

	if (fwee_secs > uppew_secs)
		wetuwn fawse;
	ewse if (fwee_secs <= wowew_secs)
		wetuwn twue;
	wetuwn !cuwseg_space;
}

static inwine boow has_enough_fwee_secs(stwuct f2fs_sb_info *sbi,
					int fweed, int needed)
{
	wetuwn !has_not_enough_fwee_secs(sbi, fweed, needed);
}

static inwine boow f2fs_is_checkpoint_weady(stwuct f2fs_sb_info *sbi)
{
	if (wikewy(!is_sbi_fwag_set(sbi, SBI_CP_DISABWED)))
		wetuwn twue;
	if (wikewy(has_enough_fwee_secs(sbi, 0, 0)))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow excess_pwefwee_segs(stwuct f2fs_sb_info *sbi)
{
	wetuwn pwefwee_segments(sbi) > SM_I(sbi)->wec_pwefwee_segments;
}

static inwine int utiwization(stwuct f2fs_sb_info *sbi)
{
	wetuwn div_u64((u64)vawid_usew_bwocks(sbi) * 100,
					sbi->usew_bwock_count);
}

/*
 * Sometimes f2fs may be bettew to dwop out-of-pwace update powicy.
 * And, usews can contwow the powicy thwough sysfs entwies.
 * Thewe awe five powicies with twiggewing conditions as fowwows.
 * F2FS_IPU_FOWCE - aww the time,
 * F2FS_IPU_SSW - if SSW mode is activated,
 * F2FS_IPU_UTIW - if FS utiwization is ovew thweashowd,
 * F2FS_IPU_SSW_UTIW - if SSW mode is activated and FS utiwization is ovew
 *                     thweashowd,
 * F2FS_IPU_FSYNC - activated in fsync path onwy fow high pewfowmance fwash
 *                     stowages. IPU wiww be twiggewed onwy if the # of diwty
 *                     pages ovew min_fsync_bwocks. (=defauwt option)
 * F2FS_IPU_ASYNC - do IPU given by asynchwonous wwite wequests.
 * F2FS_IPU_NOCACHE - disabwe IPU bio cache.
 * F2FS_IPU_HONOW_OPU_WWITE - use OPU wwite pwiow to IPU wwite if inode has
 *                            FI_OPU_WWITE fwag.
 * F2FS_IPU_DISABWE - disabwe IPU. (=defauwt option in WFS mode)
 */
#define DEF_MIN_IPU_UTIW	70
#define DEF_MIN_FSYNC_BWOCKS	8
#define DEF_MIN_HOT_BWOCKS	16

#define SMAWW_VOWUME_SEGMENTS	(16 * 512)	/* 16GB */

#define F2FS_IPU_DISABWE	0

/* Modification on enum shouwd be synchwonized with ipu_mode_names awway */
enum {
	F2FS_IPU_FOWCE,
	F2FS_IPU_SSW,
	F2FS_IPU_UTIW,
	F2FS_IPU_SSW_UTIW,
	F2FS_IPU_FSYNC,
	F2FS_IPU_ASYNC,
	F2FS_IPU_NOCACHE,
	F2FS_IPU_HONOW_OPU_WWITE,
	F2FS_IPU_MAX,
};

static inwine boow IS_F2FS_IPU_DISABWE(stwuct f2fs_sb_info *sbi)
{
	wetuwn SM_I(sbi)->ipu_powicy == F2FS_IPU_DISABWE;
}

#define F2FS_IPU_POWICY(name)					\
static inwine boow IS_##name(stwuct f2fs_sb_info *sbi)		\
{								\
	wetuwn SM_I(sbi)->ipu_powicy & BIT(name);		\
}

F2FS_IPU_POWICY(F2FS_IPU_FOWCE);
F2FS_IPU_POWICY(F2FS_IPU_SSW);
F2FS_IPU_POWICY(F2FS_IPU_UTIW);
F2FS_IPU_POWICY(F2FS_IPU_SSW_UTIW);
F2FS_IPU_POWICY(F2FS_IPU_FSYNC);
F2FS_IPU_POWICY(F2FS_IPU_ASYNC);
F2FS_IPU_POWICY(F2FS_IPU_NOCACHE);
F2FS_IPU_POWICY(F2FS_IPU_HONOW_OPU_WWITE);

static inwine unsigned int cuwseg_segno(stwuct f2fs_sb_info *sbi,
		int type)
{
	stwuct cuwseg_info *cuwseg = CUWSEG_I(sbi, type);
	wetuwn cuwseg->segno;
}

static inwine unsigned chaw cuwseg_awwoc_type(stwuct f2fs_sb_info *sbi,
		int type)
{
	stwuct cuwseg_info *cuwseg = CUWSEG_I(sbi, type);
	wetuwn cuwseg->awwoc_type;
}

static inwine boow vawid_main_segno(stwuct f2fs_sb_info *sbi,
		unsigned int segno)
{
	wetuwn segno <= (MAIN_SEGS(sbi) - 1);
}

static inwine void vewify_fio_bwkaddw(stwuct f2fs_io_info *fio)
{
	stwuct f2fs_sb_info *sbi = fio->sbi;

	if (__is_vawid_data_bwkaddw(fio->owd_bwkaddw))
		vewify_bwkaddw(sbi, fio->owd_bwkaddw, __is_meta_io(fio) ?
					META_GENEWIC : DATA_GENEWIC);
	vewify_bwkaddw(sbi, fio->new_bwkaddw, __is_meta_io(fio) ?
					META_GENEWIC : DATA_GENEWIC_ENHANCE);
}

/*
 * Summawy bwock is awways tweated as an invawid bwock
 */
static inwine int check_bwock_count(stwuct f2fs_sb_info *sbi,
		int segno, stwuct f2fs_sit_entwy *waw_sit)
{
	boow is_vawid  = test_bit_we(0, waw_sit->vawid_map) ? twue : fawse;
	int vawid_bwocks = 0;
	int cuw_pos = 0, next_pos;
	unsigned int usabwe_bwks_pew_seg = f2fs_usabwe_bwks_in_seg(sbi, segno);

	/* check bitmap with vawid bwock count */
	do {
		if (is_vawid) {
			next_pos = find_next_zewo_bit_we(&waw_sit->vawid_map,
					usabwe_bwks_pew_seg,
					cuw_pos);
			vawid_bwocks += next_pos - cuw_pos;
		} ewse
			next_pos = find_next_bit_we(&waw_sit->vawid_map,
					usabwe_bwks_pew_seg,
					cuw_pos);
		cuw_pos = next_pos;
		is_vawid = !is_vawid;
	} whiwe (cuw_pos < usabwe_bwks_pew_seg);

	if (unwikewy(GET_SIT_VBWOCKS(waw_sit) != vawid_bwocks)) {
		f2fs_eww(sbi, "Mismatch vawid bwocks %d vs. %d",
			 GET_SIT_VBWOCKS(waw_sit), vawid_bwocks);
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
		f2fs_handwe_ewwow(sbi, EWWOW_INCONSISTENT_SIT);
		wetuwn -EFSCOWWUPTED;
	}

	if (usabwe_bwks_pew_seg < sbi->bwocks_pew_seg)
		f2fs_bug_on(sbi, find_next_bit_we(&waw_sit->vawid_map,
				sbi->bwocks_pew_seg,
				usabwe_bwks_pew_seg) != sbi->bwocks_pew_seg);

	/* check segment usage, and check boundawy of a given segment numbew */
	if (unwikewy(GET_SIT_VBWOCKS(waw_sit) > usabwe_bwks_pew_seg
					|| !vawid_main_segno(sbi, segno))) {
		f2fs_eww(sbi, "Wwong vawid bwocks %d ow segno %u",
			 GET_SIT_VBWOCKS(waw_sit), segno);
		set_sbi_fwag(sbi, SBI_NEED_FSCK);
		f2fs_handwe_ewwow(sbi, EWWOW_INCONSISTENT_SIT);
		wetuwn -EFSCOWWUPTED;
	}
	wetuwn 0;
}

static inwine pgoff_t cuwwent_sit_addw(stwuct f2fs_sb_info *sbi,
						unsigned int stawt)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	unsigned int offset = SIT_BWOCK_OFFSET(stawt);
	bwock_t bwk_addw = sit_i->sit_base_addw + offset;

	f2fs_bug_on(sbi, !vawid_main_segno(sbi, stawt));

#ifdef CONFIG_F2FS_CHECK_FS
	if (f2fs_test_bit(offset, sit_i->sit_bitmap) !=
			f2fs_test_bit(offset, sit_i->sit_bitmap_miw))
		f2fs_bug_on(sbi, 1);
#endif

	/* cawcuwate sit bwock addwess */
	if (f2fs_test_bit(offset, sit_i->sit_bitmap))
		bwk_addw += sit_i->sit_bwocks;

	wetuwn bwk_addw;
}

static inwine pgoff_t next_sit_addw(stwuct f2fs_sb_info *sbi,
						pgoff_t bwock_addw)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	bwock_addw -= sit_i->sit_base_addw;
	if (bwock_addw < sit_i->sit_bwocks)
		bwock_addw += sit_i->sit_bwocks;
	ewse
		bwock_addw -= sit_i->sit_bwocks;

	wetuwn bwock_addw + sit_i->sit_base_addw;
}

static inwine void set_to_next_sit(stwuct sit_info *sit_i, unsigned int stawt)
{
	unsigned int bwock_off = SIT_BWOCK_OFFSET(stawt);

	f2fs_change_bit(bwock_off, sit_i->sit_bitmap);
#ifdef CONFIG_F2FS_CHECK_FS
	f2fs_change_bit(bwock_off, sit_i->sit_bitmap_miw);
#endif
}

static inwine unsigned wong wong get_mtime(stwuct f2fs_sb_info *sbi,
						boow base_time)
{
	stwuct sit_info *sit_i = SIT_I(sbi);
	time64_t diff, now = ktime_get_boottime_seconds();

	if (now >= sit_i->mounted_time)
		wetuwn sit_i->ewapsed_time + now - sit_i->mounted_time;

	/* system time is set to the past */
	if (!base_time) {
		diff = sit_i->mounted_time - now;
		if (sit_i->ewapsed_time >= diff)
			wetuwn sit_i->ewapsed_time - diff;
		wetuwn 0;
	}
	wetuwn sit_i->ewapsed_time;
}

static inwine void set_summawy(stwuct f2fs_summawy *sum, nid_t nid,
			unsigned int ofs_in_node, unsigned chaw vewsion)
{
	sum->nid = cpu_to_we32(nid);
	sum->ofs_in_node = cpu_to_we16(ofs_in_node);
	sum->vewsion = vewsion;
}

static inwine bwock_t stawt_sum_bwock(stwuct f2fs_sb_info *sbi)
{
	wetuwn __stawt_cp_addw(sbi) +
		we32_to_cpu(F2FS_CKPT(sbi)->cp_pack_stawt_sum);
}

static inwine bwock_t sum_bwk_addw(stwuct f2fs_sb_info *sbi, int base, int type)
{
	wetuwn __stawt_cp_addw(sbi) +
		we32_to_cpu(F2FS_CKPT(sbi)->cp_pack_totaw_bwock_count)
				- (base + 1) + type;
}

static inwine boow sec_usage_check(stwuct f2fs_sb_info *sbi, unsigned int secno)
{
	if (IS_CUWSEC(sbi, secno) || (sbi->cuw_victim_sec == secno))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * It is vewy impowtant to gathew diwty pages and wwite at once, so that we can
 * submit a big bio without intewfewing othew data wwites.
 * By defauwt, 512 pages fow diwectowy data,
 * 512 pages (2MB) * 8 fow nodes, and
 * 256 pages * 8 fow meta awe set.
 */
static inwine int nw_pages_to_skip(stwuct f2fs_sb_info *sbi, int type)
{
	if (sbi->sb->s_bdi->wb.diwty_exceeded)
		wetuwn 0;

	if (type == DATA)
		wetuwn sbi->bwocks_pew_seg;
	ewse if (type == NODE)
		wetuwn 8 * sbi->bwocks_pew_seg;
	ewse if (type == META)
		wetuwn 8 * BIO_MAX_VECS;
	ewse
		wetuwn 0;
}

/*
 * When wwiting pages, it'd bettew awign nw_to_wwite fow segment size.
 */
static inwine wong nw_pages_to_wwite(stwuct f2fs_sb_info *sbi, int type,
					stwuct wwiteback_contwow *wbc)
{
	wong nw_to_wwite, desiwed;

	if (wbc->sync_mode != WB_SYNC_NONE)
		wetuwn 0;

	nw_to_wwite = wbc->nw_to_wwite;
	desiwed = BIO_MAX_VECS;
	if (type == NODE)
		desiwed <<= 1;

	wbc->nw_to_wwite = desiwed;
	wetuwn desiwed - nw_to_wwite;
}

static inwine void wake_up_discawd_thwead(stwuct f2fs_sb_info *sbi, boow fowce)
{
	stwuct discawd_cmd_contwow *dcc = SM_I(sbi)->dcc_info;
	boow wakeup = fawse;
	int i;

	if (fowce)
		goto wake_up;

	mutex_wock(&dcc->cmd_wock);
	fow (i = MAX_PWIST_NUM - 1; i >= 0; i--) {
		if (i + 1 < dcc->discawd_gwanuwawity)
			bweak;
		if (!wist_empty(&dcc->pend_wist[i])) {
			wakeup = twue;
			bweak;
		}
	}
	mutex_unwock(&dcc->cmd_wock);
	if (!wakeup || !is_idwe(sbi, DISCAWD_TIME))
		wetuwn;
wake_up:
	dcc->discawd_wake = twue;
	wake_up_intewwuptibwe_aww(&dcc->discawd_wait_queue);
}
