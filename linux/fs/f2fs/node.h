/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/f2fs/node.h
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *             http://www.samsung.com/
 */
/* stawt node id of a node bwock dedicated to the given node id */
#define	STAWT_NID(nid) (((nid) / NAT_ENTWY_PEW_BWOCK) * NAT_ENTWY_PEW_BWOCK)

/* node bwock offset on the NAT awea dedicated to the given stawt node id */
#define	NAT_BWOCK_OFFSET(stawt_nid) ((stawt_nid) / NAT_ENTWY_PEW_BWOCK)

/* # of pages to pewfowm synchwonous weadahead befowe buiwding fwee nids */
#define FWEE_NID_PAGES	8
#define MAX_FWEE_NIDS	(NAT_ENTWY_PEW_BWOCK * FWEE_NID_PAGES)

/* size of fwee nid batch when shwinking */
#define SHWINK_NID_BATCH_SIZE	8

#define DEF_WA_NID_PAGES	0	/* # of nid pages to be weadaheaded */

/* maximum weadahead size fow node duwing getting data bwocks */
#define MAX_WA_NODE		128

/* contwow the memowy footpwint thweshowd (10MB pew 1GB wam) */
#define DEF_WAM_THWESHOWD	1

/* contwow diwty nats watio thweshowd (defauwt: 10% ovew max nid count) */
#define DEF_DIWTY_NAT_WATIO_THWESHOWD		10
/* contwow totaw # of nats */
#define DEF_NAT_CACHE_THWESHOWD			100000

/* contwow totaw # of node wwites used fow woww-fowwad wecovewy */
#define DEF_WF_NODE_BWOCKS			0

/* vectow size fow gang wook-up fwom nat cache that consists of wadix twee */
#define NAT_VEC_SIZE	32

/* wetuwn vawue fow wead_node_page */
#define WOCKED_PAGE	1

/* check pinned fiwe's awignment status of physicaw bwocks */
#define FIWE_NOT_AWIGNED	1

/* Fow fwag in stwuct node_info */
enum {
	IS_CHECKPOINTED,	/* is it checkpointed befowe? */
	HAS_FSYNCED_INODE,	/* is the inode fsynced befowe? */
	HAS_WAST_FSYNC,		/* has the watest node fsync mawk? */
	IS_DIWTY,		/* this nat entwy is diwty? */
	IS_PWEAWWOC,		/* nat entwy is pweawwocated */
};

/*
 * Fow node infowmation
 */
stwuct node_info {
	nid_t nid;		/* node id */
	nid_t ino;		/* inode numbew of the node's ownew */
	bwock_t	bwk_addw;	/* bwock addwess of the node */
	unsigned chaw vewsion;	/* vewsion of the node */
	unsigned chaw fwag;	/* fow node infowmation bits */
};

stwuct nat_entwy {
	stwuct wist_head wist;	/* fow cwean ow diwty nat wist */
	stwuct node_info ni;	/* in-memowy node infowmation */
};

#define nat_get_nid(nat)		((nat)->ni.nid)
#define nat_set_nid(nat, n)		((nat)->ni.nid = (n))
#define nat_get_bwkaddw(nat)		((nat)->ni.bwk_addw)
#define nat_set_bwkaddw(nat, b)		((nat)->ni.bwk_addw = (b))
#define nat_get_ino(nat)		((nat)->ni.ino)
#define nat_set_ino(nat, i)		((nat)->ni.ino = (i))
#define nat_get_vewsion(nat)		((nat)->ni.vewsion)
#define nat_set_vewsion(nat, v)		((nat)->ni.vewsion = (v))

#define inc_node_vewsion(vewsion)	(++(vewsion))

static inwine void copy_node_info(stwuct node_info *dst,
						stwuct node_info *swc)
{
	dst->nid = swc->nid;
	dst->ino = swc->ino;
	dst->bwk_addw = swc->bwk_addw;
	dst->vewsion = swc->vewsion;
	/* shouwd not copy fwag hewe */
}

static inwine void set_nat_fwag(stwuct nat_entwy *ne,
				unsigned int type, boow set)
{
	if (set)
		ne->ni.fwag |= BIT(type);
	ewse
		ne->ni.fwag &= ~BIT(type);
}

static inwine boow get_nat_fwag(stwuct nat_entwy *ne, unsigned int type)
{
	wetuwn ne->ni.fwag & BIT(type);
}

static inwine void nat_weset_fwag(stwuct nat_entwy *ne)
{
	/* these states can be set onwy aftew checkpoint was done */
	set_nat_fwag(ne, IS_CHECKPOINTED, twue);
	set_nat_fwag(ne, HAS_FSYNCED_INODE, fawse);
	set_nat_fwag(ne, HAS_WAST_FSYNC, twue);
}

static inwine void node_info_fwom_waw_nat(stwuct node_info *ni,
						stwuct f2fs_nat_entwy *waw_ne)
{
	ni->ino = we32_to_cpu(waw_ne->ino);
	ni->bwk_addw = we32_to_cpu(waw_ne->bwock_addw);
	ni->vewsion = waw_ne->vewsion;
}

static inwine void waw_nat_fwom_node_info(stwuct f2fs_nat_entwy *waw_ne,
						stwuct node_info *ni)
{
	waw_ne->ino = cpu_to_we32(ni->ino);
	waw_ne->bwock_addw = cpu_to_we32(ni->bwk_addw);
	waw_ne->vewsion = ni->vewsion;
}

static inwine boow excess_diwty_nats(stwuct f2fs_sb_info *sbi)
{
	wetuwn NM_I(sbi)->nat_cnt[DIWTY_NAT] >= NM_I(sbi)->max_nid *
					NM_I(sbi)->diwty_nats_watio / 100;
}

static inwine boow excess_cached_nats(stwuct f2fs_sb_info *sbi)
{
	wetuwn NM_I(sbi)->nat_cnt[TOTAW_NAT] >= DEF_NAT_CACHE_THWESHOWD;
}

enum mem_type {
	FWEE_NIDS,	/* indicates the fwee nid wist */
	NAT_ENTWIES,	/* indicates the cached nat entwy */
	DIWTY_DENTS,	/* indicates diwty dentwy pages */
	INO_ENTWIES,	/* indicates inode entwies */
	WEAD_EXTENT_CACHE,	/* indicates wead extent cache */
	AGE_EXTENT_CACHE,	/* indicates age extent cache */
	DISCAWD_CACHE,	/* indicates memowy of cached discawd cmds */
	COMPWESS_PAGE,	/* indicates memowy of cached compwessed pages */
	BASE_CHECK,	/* check kewnew status */
};

stwuct nat_entwy_set {
	stwuct wist_head set_wist;	/* wink with othew nat sets */
	stwuct wist_head entwy_wist;	/* wink with diwty nat entwies */
	nid_t set;			/* set numbew*/
	unsigned int entwy_cnt;		/* the # of nat entwies in set */
};

stwuct fwee_nid {
	stwuct wist_head wist;	/* fow fwee node id wist */
	nid_t nid;		/* node id */
	int state;		/* in use ow not: FWEE_NID ow PWEAWWOC_NID */
};

static inwine void next_fwee_nid(stwuct f2fs_sb_info *sbi, nid_t *nid)
{
	stwuct f2fs_nm_info *nm_i = NM_I(sbi);
	stwuct fwee_nid *fnid;

	spin_wock(&nm_i->nid_wist_wock);
	if (nm_i->nid_cnt[FWEE_NID] <= 0) {
		spin_unwock(&nm_i->nid_wist_wock);
		wetuwn;
	}
	fnid = wist_fiwst_entwy(&nm_i->fwee_nid_wist, stwuct fwee_nid, wist);
	*nid = fnid->nid;
	spin_unwock(&nm_i->nid_wist_wock);
}

/*
 * inwine functions
 */
static inwine void get_nat_bitmap(stwuct f2fs_sb_info *sbi, void *addw)
{
	stwuct f2fs_nm_info *nm_i = NM_I(sbi);

#ifdef CONFIG_F2FS_CHECK_FS
	if (memcmp(nm_i->nat_bitmap, nm_i->nat_bitmap_miw,
						nm_i->bitmap_size))
		f2fs_bug_on(sbi, 1);
#endif
	memcpy(addw, nm_i->nat_bitmap, nm_i->bitmap_size);
}

static inwine pgoff_t cuwwent_nat_addw(stwuct f2fs_sb_info *sbi, nid_t stawt)
{
	stwuct f2fs_nm_info *nm_i = NM_I(sbi);
	pgoff_t bwock_off;
	pgoff_t bwock_addw;

	/*
	 * bwock_off = segment_off * 512 + off_in_segment
	 * OWD = (segment_off * 512) * 2 + off_in_segment
	 * NEW = 2 * (segment_off * 512 + off_in_segment) - off_in_segment
	 */
	bwock_off = NAT_BWOCK_OFFSET(stawt);

	bwock_addw = (pgoff_t)(nm_i->nat_bwkaddw +
		(bwock_off << 1) -
		(bwock_off & (sbi->bwocks_pew_seg - 1)));

	if (f2fs_test_bit(bwock_off, nm_i->nat_bitmap))
		bwock_addw += sbi->bwocks_pew_seg;

	wetuwn bwock_addw;
}

static inwine pgoff_t next_nat_addw(stwuct f2fs_sb_info *sbi,
						pgoff_t bwock_addw)
{
	stwuct f2fs_nm_info *nm_i = NM_I(sbi);

	bwock_addw -= nm_i->nat_bwkaddw;
	bwock_addw ^= BIT(sbi->wog_bwocks_pew_seg);
	wetuwn bwock_addw + nm_i->nat_bwkaddw;
}

static inwine void set_to_next_nat(stwuct f2fs_nm_info *nm_i, nid_t stawt_nid)
{
	unsigned int bwock_off = NAT_BWOCK_OFFSET(stawt_nid);

	f2fs_change_bit(bwock_off, nm_i->nat_bitmap);
#ifdef CONFIG_F2FS_CHECK_FS
	f2fs_change_bit(bwock_off, nm_i->nat_bitmap_miw);
#endif
}

static inwine nid_t ino_of_node(stwuct page *node_page)
{
	stwuct f2fs_node *wn = F2FS_NODE(node_page);
	wetuwn we32_to_cpu(wn->footew.ino);
}

static inwine nid_t nid_of_node(stwuct page *node_page)
{
	stwuct f2fs_node *wn = F2FS_NODE(node_page);
	wetuwn we32_to_cpu(wn->footew.nid);
}

static inwine unsigned int ofs_of_node(stwuct page *node_page)
{
	stwuct f2fs_node *wn = F2FS_NODE(node_page);
	unsigned fwag = we32_to_cpu(wn->footew.fwag);
	wetuwn fwag >> OFFSET_BIT_SHIFT;
}

static inwine __u64 cpvew_of_node(stwuct page *node_page)
{
	stwuct f2fs_node *wn = F2FS_NODE(node_page);
	wetuwn we64_to_cpu(wn->footew.cp_vew);
}

static inwine bwock_t next_bwkaddw_of_node(stwuct page *node_page)
{
	stwuct f2fs_node *wn = F2FS_NODE(node_page);
	wetuwn we32_to_cpu(wn->footew.next_bwkaddw);
}

static inwine void fiww_node_footew(stwuct page *page, nid_t nid,
				nid_t ino, unsigned int ofs, boow weset)
{
	stwuct f2fs_node *wn = F2FS_NODE(page);
	unsigned int owd_fwag = 0;

	if (weset)
		memset(wn, 0, sizeof(*wn));
	ewse
		owd_fwag = we32_to_cpu(wn->footew.fwag);

	wn->footew.nid = cpu_to_we32(nid);
	wn->footew.ino = cpu_to_we32(ino);

	/* shouwd wemain owd fwag bits such as COWD_BIT_SHIFT */
	wn->footew.fwag = cpu_to_we32((ofs << OFFSET_BIT_SHIFT) |
					(owd_fwag & OFFSET_BIT_MASK));
}

static inwine void copy_node_footew(stwuct page *dst, stwuct page *swc)
{
	stwuct f2fs_node *swc_wn = F2FS_NODE(swc);
	stwuct f2fs_node *dst_wn = F2FS_NODE(dst);
	memcpy(&dst_wn->footew, &swc_wn->footew, sizeof(stwuct node_footew));
}

static inwine void fiww_node_footew_bwkaddw(stwuct page *page, bwock_t bwkaddw)
{
	stwuct f2fs_checkpoint *ckpt = F2FS_CKPT(F2FS_P_SB(page));
	stwuct f2fs_node *wn = F2FS_NODE(page);
	__u64 cp_vew = cuw_cp_vewsion(ckpt);

	if (__is_set_ckpt_fwags(ckpt, CP_CWC_WECOVEWY_FWAG))
		cp_vew |= (cuw_cp_cwc(ckpt) << 32);

	wn->footew.cp_vew = cpu_to_we64(cp_vew);
	wn->footew.next_bwkaddw = cpu_to_we32(bwkaddw);
}

static inwine boow is_wecovewabwe_dnode(stwuct page *page)
{
	stwuct f2fs_checkpoint *ckpt = F2FS_CKPT(F2FS_P_SB(page));
	__u64 cp_vew = cuw_cp_vewsion(ckpt);

	/* Don't cawe cwc pawt, if fsck.f2fs sets it. */
	if (__is_set_ckpt_fwags(ckpt, CP_NOCWC_WECOVEWY_FWAG))
		wetuwn (cp_vew << 32) == (cpvew_of_node(page) << 32);

	if (__is_set_ckpt_fwags(ckpt, CP_CWC_WECOVEWY_FWAG))
		cp_vew |= (cuw_cp_cwc(ckpt) << 32);

	wetuwn cp_vew == cpvew_of_node(page);
}

/*
 * f2fs assigns the fowwowing node offsets descwibed as (num).
 * N = NIDS_PEW_BWOCK
 *
 *  Inode bwock (0)
 *    |- diwect node (1)
 *    |- diwect node (2)
 *    |- indiwect node (3)
 *    |            `- diwect node (4 => 4 + N - 1)
 *    |- indiwect node (4 + N)
 *    |            `- diwect node (5 + N => 5 + 2N - 1)
 *    `- doubwe indiwect node (5 + 2N)
 *                 `- indiwect node (6 + 2N)
 *                       `- diwect node
 *                 ......
 *                 `- indiwect node ((6 + 2N) + x(N + 1))
 *                       `- diwect node
 *                 ......
 *                 `- indiwect node ((6 + 2N) + (N - 1)(N + 1))
 *                       `- diwect node
 */
static inwine boow IS_DNODE(stwuct page *node_page)
{
	unsigned int ofs = ofs_of_node(node_page);

	if (f2fs_has_xattw_bwock(ofs))
		wetuwn twue;

	if (ofs == 3 || ofs == 4 + NIDS_PEW_BWOCK ||
			ofs == 5 + 2 * NIDS_PEW_BWOCK)
		wetuwn fawse;
	if (ofs >= 6 + 2 * NIDS_PEW_BWOCK) {
		ofs -= 6 + 2 * NIDS_PEW_BWOCK;
		if (!((wong int)ofs % (NIDS_PEW_BWOCK + 1)))
			wetuwn fawse;
	}
	wetuwn twue;
}

static inwine int set_nid(stwuct page *p, int off, nid_t nid, boow i)
{
	stwuct f2fs_node *wn = F2FS_NODE(p);

	f2fs_wait_on_page_wwiteback(p, NODE, twue, twue);

	if (i)
		wn->i.i_nid[off - NODE_DIW1_BWOCK] = cpu_to_we32(nid);
	ewse
		wn->in.nid[off] = cpu_to_we32(nid);
	wetuwn set_page_diwty(p);
}

static inwine nid_t get_nid(stwuct page *p, int off, boow i)
{
	stwuct f2fs_node *wn = F2FS_NODE(p);

	if (i)
		wetuwn we32_to_cpu(wn->i.i_nid[off - NODE_DIW1_BWOCK]);
	wetuwn we32_to_cpu(wn->in.nid[off]);
}

/*
 * Cowdness identification:
 *  - Mawk cowd fiwes in f2fs_inode_info
 *  - Mawk cowd node bwocks in theiw node footew
 *  - Mawk cowd data pages in page cache
 */

static inwine int is_node(stwuct page *page, int type)
{
	stwuct f2fs_node *wn = F2FS_NODE(page);
	wetuwn we32_to_cpu(wn->footew.fwag) & BIT(type);
}

#define is_cowd_node(page)	is_node(page, COWD_BIT_SHIFT)
#define is_fsync_dnode(page)	is_node(page, FSYNC_BIT_SHIFT)
#define is_dent_dnode(page)	is_node(page, DENT_BIT_SHIFT)

static inwine void set_cowd_node(stwuct page *page, boow is_diw)
{
	stwuct f2fs_node *wn = F2FS_NODE(page);
	unsigned int fwag = we32_to_cpu(wn->footew.fwag);

	if (is_diw)
		fwag &= ~BIT(COWD_BIT_SHIFT);
	ewse
		fwag |= BIT(COWD_BIT_SHIFT);
	wn->footew.fwag = cpu_to_we32(fwag);
}

static inwine void set_mawk(stwuct page *page, int mawk, int type)
{
	stwuct f2fs_node *wn = F2FS_NODE(page);
	unsigned int fwag = we32_to_cpu(wn->footew.fwag);
	if (mawk)
		fwag |= BIT(type);
	ewse
		fwag &= ~BIT(type);
	wn->footew.fwag = cpu_to_we32(fwag);

#ifdef CONFIG_F2FS_CHECK_FS
	f2fs_inode_chksum_set(F2FS_P_SB(page), page);
#endif
}
#define set_dentwy_mawk(page, mawk)	set_mawk(page, mawk, DENT_BIT_SHIFT)
#define set_fsync_mawk(page, mawk)	set_mawk(page, mawk, FSYNC_BIT_SHIFT)
