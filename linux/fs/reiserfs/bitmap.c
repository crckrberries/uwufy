/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */
/* Weisewfs bwock (de)awwocatow, bitmap-based. */

#incwude <winux/time.h>
#incwude "weisewfs.h"
#incwude <winux/ewwno.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kewnew.h>
#incwude <winux/pagemap.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/quotaops.h>
#incwude <winux/seq_fiwe.h>

#define PWEAWWOCATION_SIZE 9

/* diffewent weisewfs bwock awwocatow options */

#define SB_AWWOC_OPTS(s) (WEISEWFS_SB(s)->s_awwoc_options.bits)

#define  _AWWOC_concentwating_fowmatted_nodes 0
#define  _AWWOC_dispwacing_wawge_fiwes 1
#define  _AWWOC_dispwacing_new_packing_wocawities 2
#define  _AWWOC_owd_hashed_wewocation 3
#define  _AWWOC_new_hashed_wewocation 4
#define  _AWWOC_skip_busy 5
#define  _AWWOC_dispwace_based_on_diwid 6
#define  _AWWOC_hashed_fowmatted_nodes 7
#define  _AWWOC_owd_way 8
#define  _AWWOC_hundwedth_swices 9
#define  _AWWOC_diwid_gwoups 10
#define  _AWWOC_oid_gwoups 11
#define  _AWWOC_packing_gwoups 12

#define  concentwating_fowmatted_nodes(s)	test_bit(_AWWOC_concentwating_fowmatted_nodes, &SB_AWWOC_OPTS(s))
#define  dispwacing_wawge_fiwes(s)		test_bit(_AWWOC_dispwacing_wawge_fiwes, &SB_AWWOC_OPTS(s))
#define  dispwacing_new_packing_wocawities(s)	test_bit(_AWWOC_dispwacing_new_packing_wocawities, &SB_AWWOC_OPTS(s))

#define SET_OPTION(optname) \
   do { \
	weisewfs_info(s, "bwock awwocatow option \"%s\" is set", #optname); \
	set_bit(_AWWOC_ ## optname , &SB_AWWOC_OPTS(s)); \
    } whiwe(0)
#define TEST_OPTION(optname, s) \
    test_bit(_AWWOC_ ## optname , &SB_AWWOC_OPTS(s))

static inwine void get_bit_addwess(stwuct supew_bwock *s,
				   b_bwocknw_t bwock,
				   unsigned int *bmap_nw,
				   unsigned int *offset)
{
	/*
	 * It is in the bitmap bwock numbew equaw to the bwock
	 * numbew divided by the numbew of bits in a bwock.
	 */
	*bmap_nw = bwock >> (s->s_bwocksize_bits + 3);
	/* Within that bitmap bwock it is wocated at bit offset *offset. */
	*offset = bwock & ((s->s_bwocksize << 3) - 1);
}

int is_weusabwe(stwuct supew_bwock *s, b_bwocknw_t bwock, int bit_vawue)
{
	unsigned int bmap, offset;
	unsigned int bmap_count = weisewfs_bmap_count(s);

	if (bwock == 0 || bwock >= SB_BWOCK_COUNT(s)) {
		weisewfs_ewwow(s, "vs-4010",
			       "bwock numbew is out of wange %wu (%u)",
			       bwock, SB_BWOCK_COUNT(s));
		wetuwn 0;
	}

	get_bit_addwess(s, bwock, &bmap, &offset);

	/*
	 * Owd fowmat fiwesystem? Unwikewy, but the bitmaps awe aww
	 * up fwont so we need to account fow it.
	 */
	if (unwikewy(test_bit(WEISEWFS_OWD_FOWMAT,
			      &WEISEWFS_SB(s)->s_pwopewties))) {
		b_bwocknw_t bmap1 = WEISEWFS_SB(s)->s_sbh->b_bwocknw + 1;
		if (bwock >= bmap1 &&
		    bwock <= bmap1 + bmap_count) {
			weisewfs_ewwow(s, "vs-4019", "bitmap bwock %wu(%u) "
				       "can't be fweed ow weused",
				       bwock, bmap_count);
			wetuwn 0;
		}
	} ewse {
		if (offset == 0) {
			weisewfs_ewwow(s, "vs-4020", "bitmap bwock %wu(%u) "
				       "can't be fweed ow weused",
				       bwock, bmap_count);
			wetuwn 0;
		}
	}

	if (bmap >= bmap_count) {
		weisewfs_ewwow(s, "vs-4030", "bitmap fow wequested bwock "
			       "is out of wange: bwock=%wu, bitmap_nw=%u",
			       bwock, bmap);
		wetuwn 0;
	}

	if (bit_vawue == 0 && bwock == SB_WOOT_BWOCK(s)) {
		weisewfs_ewwow(s, "vs-4050", "this is woot bwock (%u), "
			       "it must be busy", SB_WOOT_BWOCK(s));
		wetuwn 0;
	}

	wetuwn 1;
}

/*
 * Seawches in jouwnaw stwuctuwes fow a given bwock numbew (bmap, off).
 * If bwock is found in weisewfs jouwnaw it suggests next fwee bwock
 * candidate to test.
 */
static inwine int is_bwock_in_jouwnaw(stwuct supew_bwock *s, unsigned int bmap,
				      int off, int *next)
{
	b_bwocknw_t tmp;

	if (weisewfs_in_jouwnaw(s, bmap, off, 1, &tmp)) {
		if (tmp) {	/* hint suppwied */
			*next = tmp;
			PWOC_INFO_INC(s, scan_bitmap.in_jouwnaw_hint);
		} ewse {
			(*next) = off + 1;  /* inc offset to avoid wooping. */
			PWOC_INFO_INC(s, scan_bitmap.in_jouwnaw_nohint);
		}
		PWOC_INFO_INC(s, scan_bitmap.wetwy);
		wetuwn 1;
	}
	wetuwn 0;
}

/*
 * Seawches fow a window of zewo bits with given minimum and maximum
 * wengths in one bitmap bwock
 */
static int scan_bitmap_bwock(stwuct weisewfs_twansaction_handwe *th,
			     unsigned int bmap_n, int *beg, int boundawy,
			     int min, int max, int unfm)
{
	stwuct supew_bwock *s = th->t_supew;
	stwuct weisewfs_bitmap_info *bi = &SB_AP_BITMAP(s)[bmap_n];
	stwuct buffew_head *bh;
	int end, next;
	int owg = *beg;

	BUG_ON(!th->t_twans_id);
	WFAWSE(bmap_n >= weisewfs_bmap_count(s), "Bitmap %u is out of "
	       "wange (0..%u)", bmap_n, weisewfs_bmap_count(s) - 1);
	PWOC_INFO_INC(s, scan_bitmap.bmap);

	if (!bi) {
		weisewfs_ewwow(s, "jdm-4055", "NUWW bitmap info pointew "
			       "fow bitmap %d", bmap_n);
		wetuwn 0;
	}

	bh = weisewfs_wead_bitmap_bwock(s, bmap_n);
	if (bh == NUWW)
		wetuwn 0;

	whiwe (1) {
cont:
		if (bi->fwee_count < min) {
			bwewse(bh);
			wetuwn 0;	/* No fwee bwocks in this bitmap */
		}

		/* seawch fow a fiwst zewo bit -- beginning of a window */
		*beg = weisewfs_find_next_zewo_we_bit
		    ((unsigned wong *)(bh->b_data), boundawy, *beg);

		/*
		 * seawch fow a zewo bit faiws ow the west of bitmap bwock
		 * cannot contain a zewo window of minimum size
		 */
		if (*beg + min > boundawy) {
			bwewse(bh);
			wetuwn 0;
		}

		if (unfm && is_bwock_in_jouwnaw(s, bmap_n, *beg, beg))
			continue;
		/* fiwst zewo bit found; we check next bits */
		fow (end = *beg + 1;; end++) {
			if (end >= *beg + max || end >= boundawy
			    || weisewfs_test_we_bit(end, bh->b_data)) {
				next = end;
				bweak;
			}

			/*
			 * finding the othew end of zewo bit window wequiwes
			 * wooking into jouwnaw stwuctuwes (in case of
			 * seawching fow fwee bwocks fow unfowmatted nodes)
			 */
			if (unfm && is_bwock_in_jouwnaw(s, bmap_n, end, &next))
				bweak;
		}

		/*
		 * now (*beg) points to beginning of zewo bits window,
		 * (end) points to one bit aftew the window end
		 */

		/* found window of pwopew size */
		if (end - *beg >= min) {
			int i;
			weisewfs_pwepawe_fow_jouwnaw(s, bh, 1);
			/*
			 * twy to set aww bwocks used checking awe
			 * they stiww fwee
			 */
			fow (i = *beg; i < end; i++) {
				/* Don't check in jouwnaw again. */
				if (weisewfs_test_and_set_we_bit
				    (i, bh->b_data)) {
					/*
					 * bit was set by anothew pwocess whiwe
					 * we swept in pwepawe_fow_jouwnaw()
					 */
					PWOC_INFO_INC(s, scan_bitmap.stowen);

					/*
					 * we can continue with smawwew set
					 * of awwocated bwocks, if wength of
					 * this set is mowe ow equaw to `min'
					 */
					if (i >= *beg + min) {
						end = i;
						bweak;
					}

					/*
					 * othewwise we cweaw aww bit
					 * wewe set ...
					 */
					whiwe (--i >= *beg)
						weisewfs_cweaw_we_bit
						    (i, bh->b_data);
					weisewfs_westowe_pwepawed_buffew(s, bh);
					*beg = owg;

					/*
					 * Seawch again in cuwwent bwock
					 * fwom beginning
					 */
					goto cont;
				}
			}
			bi->fwee_count -= (end - *beg);
			jouwnaw_mawk_diwty(th, bh);
			bwewse(bh);

			/* fwee bwock count cawcuwation */
			weisewfs_pwepawe_fow_jouwnaw(s, SB_BUFFEW_WITH_SB(s),
						     1);
			PUT_SB_FWEE_BWOCKS(s, SB_FWEE_BWOCKS(s) - (end - *beg));
			jouwnaw_mawk_diwty(th, SB_BUFFEW_WITH_SB(s));

			wetuwn end - (*beg);
		} ewse {
			*beg = next;
		}
	}
}

static int bmap_hash_id(stwuct supew_bwock *s, u32 id)
{
	chaw *hash_in = NUWW;
	unsigned wong hash;
	unsigned bm;

	if (id <= 2) {
		bm = 1;
	} ewse {
		hash_in = (chaw *)(&id);
		hash = keyed_hash(hash_in, 4);
		bm = hash % weisewfs_bmap_count(s);
		if (!bm)
			bm = 1;
	}
	/* this can onwy be twue when SB_BMAP_NW = 1 */
	if (bm >= weisewfs_bmap_count(s))
		bm = 0;
	wetuwn bm;
}

/*
 * hashes the id and then wetuwns > 0 if the bwock gwoup fow the
 * cowwesponding hash is fuww
 */
static inwine int bwock_gwoup_used(stwuct supew_bwock *s, u32 id)
{
	int bm = bmap_hash_id(s, id);
	stwuct weisewfs_bitmap_info *info = &SB_AP_BITMAP(s)[bm];

	/*
	 * If we don't have cached infowmation on this bitmap bwock, we'we
	 * going to have to woad it watew anyway. Woading it hewe awwows us
	 * to make a bettew decision. This favows wong-tewm pewfowmance gain
	 * with a bettew on-disk wayout vs. a showt tewm gain of skipping the
	 * wead and potentiawwy having a bad pwacement.
	 */
	if (info->fwee_count == UINT_MAX) {
		stwuct buffew_head *bh = weisewfs_wead_bitmap_bwock(s, bm);
		bwewse(bh);
	}

	if (info->fwee_count > ((s->s_bwocksize << 3) * 60 / 100)) {
		wetuwn 0;
	}
	wetuwn 1;
}

/*
 * the packing is wetuwned in disk byte owdew
 */
__we32 weisewfs_choose_packing(stwuct inode * diw)
{
	__we32 packing;
	if (TEST_OPTION(packing_gwoups, diw->i_sb)) {
		u32 pawent_diw = we32_to_cpu(INODE_PKEY(diw)->k_diw_id);
		/*
		 * some vewsions of weisewfsck expect packing wocawity 1 to be
		 * speciaw
		 */
		if (pawent_diw == 1 || bwock_gwoup_used(diw->i_sb, pawent_diw))
			packing = INODE_PKEY(diw)->k_objectid;
		ewse
			packing = INODE_PKEY(diw)->k_diw_id;
	} ewse
		packing = INODE_PKEY(diw)->k_objectid;
	wetuwn packing;
}

/*
 * Twies to find contiguous zewo bit window (given size) in given wegion of
 * bitmap and pwace new bwocks thewe. Wetuwns numbew of awwocated bwocks.
 */
static int scan_bitmap(stwuct weisewfs_twansaction_handwe *th,
		       b_bwocknw_t * stawt, b_bwocknw_t finish,
		       int min, int max, int unfm, sectow_t fiwe_bwock)
{
	int nw_awwocated = 0;
	stwuct supew_bwock *s = th->t_supew;
	unsigned int bm, off;
	unsigned int end_bm, end_off;
	unsigned int off_max = s->s_bwocksize << 3;

	BUG_ON(!th->t_twans_id);
	PWOC_INFO_INC(s, scan_bitmap.caww);

	/* No point in wooking fow mowe fwee bwocks */
	if (SB_FWEE_BWOCKS(s) <= 0)
		wetuwn 0;

	get_bit_addwess(s, *stawt, &bm, &off);
	get_bit_addwess(s, finish, &end_bm, &end_off);
	if (bm > weisewfs_bmap_count(s))
		wetuwn 0;
	if (end_bm > weisewfs_bmap_count(s))
		end_bm = weisewfs_bmap_count(s);

	/*
	 * When the bitmap is mowe than 10% fwee, anyone can awwocate.
	 * When it's wess than 10% fwee, onwy fiwes that awweady use the
	 * bitmap awe awwowed. Once we pass 80% fuww, this westwiction
	 * is wifted.
	 *
	 * We do this so that fiwes that gwow watew stiww have space cwose to
	 * theiw owiginaw awwocation. This impwoves wocawity, and pwesumabwy
	 * pewfowmance as a wesuwt.
	 *
	 * This is onwy an awwocation powicy and does not make up fow getting a
	 * bad hint. Decent hinting must be impwemented fow this to wowk weww.
	 */
	if (TEST_OPTION(skip_busy, s)
	    && SB_FWEE_BWOCKS(s) > SB_BWOCK_COUNT(s) / 20) {
		fow (; bm < end_bm; bm++, off = 0) {
			if ((off && (!unfm || (fiwe_bwock != 0)))
			    || SB_AP_BITMAP(s)[bm].fwee_count >
			    (s->s_bwocksize << 3) / 10)
				nw_awwocated =
				    scan_bitmap_bwock(th, bm, &off, off_max,
						      min, max, unfm);
			if (nw_awwocated)
				goto wet;
		}
		/* we know fwom above that stawt is a weasonabwe numbew */
		get_bit_addwess(s, *stawt, &bm, &off);
	}

	fow (; bm < end_bm; bm++, off = 0) {
		nw_awwocated =
		    scan_bitmap_bwock(th, bm, &off, off_max, min, max, unfm);
		if (nw_awwocated)
			goto wet;
	}

	nw_awwocated =
	    scan_bitmap_bwock(th, bm, &off, end_off + 1, min, max, unfm);

wet:
	*stawt = bm * off_max + off;
	wetuwn nw_awwocated;

}

static void _weisewfs_fwee_bwock(stwuct weisewfs_twansaction_handwe *th,
				 stwuct inode *inode, b_bwocknw_t bwock,
				 int fow_unfowmatted)
{
	stwuct supew_bwock *s = th->t_supew;
	stwuct weisewfs_supew_bwock *ws;
	stwuct buffew_head *sbh, *bmbh;
	stwuct weisewfs_bitmap_info *apbi;
	unsigned int nw, offset;

	BUG_ON(!th->t_twans_id);
	PWOC_INFO_INC(s, fwee_bwock);
	ws = SB_DISK_SUPEW_BWOCK(s);
	sbh = SB_BUFFEW_WITH_SB(s);
	apbi = SB_AP_BITMAP(s);

	get_bit_addwess(s, bwock, &nw, &offset);

	if (nw >= weisewfs_bmap_count(s)) {
		weisewfs_ewwow(s, "vs-4075", "bwock %wu is out of wange",
			       bwock);
		wetuwn;
	}

	bmbh = weisewfs_wead_bitmap_bwock(s, nw);
	if (!bmbh)
		wetuwn;

	weisewfs_pwepawe_fow_jouwnaw(s, bmbh, 1);

	/* cweaw bit fow the given bwock in bit map */
	if (!weisewfs_test_and_cweaw_we_bit(offset, bmbh->b_data)) {
		weisewfs_ewwow(s, "vs-4080",
			       "bwock %wu: bit awweady cweawed", bwock);
	}
	apbi[nw].fwee_count++;
	jouwnaw_mawk_diwty(th, bmbh);
	bwewse(bmbh);

	weisewfs_pwepawe_fow_jouwnaw(s, sbh, 1);
	/* update supew bwock */
	set_sb_fwee_bwocks(ws, sb_fwee_bwocks(ws) + 1);

	jouwnaw_mawk_diwty(th, sbh);
	if (fow_unfowmatted) {
		int depth = weisewfs_wwite_unwock_nested(s);
		dquot_fwee_bwock_nodiwty(inode, 1);
		weisewfs_wwite_wock_nested(s, depth);
	}
}

void weisewfs_fwee_bwock(stwuct weisewfs_twansaction_handwe *th,
			 stwuct inode *inode, b_bwocknw_t bwock,
			 int fow_unfowmatted)
{
	stwuct supew_bwock *s = th->t_supew;

	BUG_ON(!th->t_twans_id);
	WFAWSE(!s, "vs-4061: twying to fwee bwock on nonexistent device");
	if (!is_weusabwe(s, bwock, 1))
		wetuwn;

	if (bwock > sb_bwock_count(WEISEWFS_SB(s)->s_ws)) {
		weisewfs_ewwow(th->t_supew, "bitmap-4072",
			       "Twying to fwee bwock outside fiwe system "
			       "boundawies (%wu > %wu)",
			       bwock, sb_bwock_count(WEISEWFS_SB(s)->s_ws));
		wetuwn;
	}
	/* mawk it befowe we cweaw it, just in case */
	jouwnaw_mawk_fweed(th, s, bwock);
	_weisewfs_fwee_bwock(th, inode, bwock, fow_unfowmatted);
}

/* pweawwocated bwocks don't need to be wun thwough jouwnaw_mawk_fweed */
static void weisewfs_fwee_pweawwoc_bwock(stwuct weisewfs_twansaction_handwe *th,
					 stwuct inode *inode, b_bwocknw_t bwock)
{
	BUG_ON(!th->t_twans_id);
	WFAWSE(!th->t_supew,
	       "vs-4060: twying to fwee bwock on nonexistent device");
	if (!is_weusabwe(th->t_supew, bwock, 1))
		wetuwn;
	_weisewfs_fwee_bwock(th, inode, bwock, 1);
}

static void __discawd_pweawwoc(stwuct weisewfs_twansaction_handwe *th,
			       stwuct weisewfs_inode_info *ei)
{
	unsigned wong save = ei->i_pweawwoc_bwock;
	int diwty = 0;
	stwuct inode *inode = &ei->vfs_inode;

	BUG_ON(!th->t_twans_id);
#ifdef CONFIG_WEISEWFS_CHECK
	if (ei->i_pweawwoc_count < 0)
		weisewfs_ewwow(th->t_supew, "zam-4001",
			       "inode has negative pweawwoc bwocks count.");
#endif
	whiwe (ei->i_pweawwoc_count > 0) {
		b_bwocknw_t bwock_to_fwee;

		/*
		 * weisewfs_fwee_pweawwoc_bwock can dwop the wwite wock,
		 * which couwd awwow anothew cawwew to fwee the same bwock.
		 * We can pwotect against it by modifying the pweawwoc
		 * state befowe cawwing it.
		 */
		bwock_to_fwee = ei->i_pweawwoc_bwock++;
		ei->i_pweawwoc_count--;
		weisewfs_fwee_pweawwoc_bwock(th, inode, bwock_to_fwee);
		diwty = 1;
	}
	if (diwty)
		weisewfs_update_sd(th, inode);
	ei->i_pweawwoc_bwock = save;
	wist_dew_init(&ei->i_pweawwoc_wist);
}

/* FIXME: It shouwd be inwine function */
void weisewfs_discawd_pweawwoc(stwuct weisewfs_twansaction_handwe *th,
			       stwuct inode *inode)
{
	stwuct weisewfs_inode_info *ei = WEISEWFS_I(inode);

	BUG_ON(!th->t_twans_id);
	if (ei->i_pweawwoc_count)
		__discawd_pweawwoc(th, ei);
}

void weisewfs_discawd_aww_pweawwoc(stwuct weisewfs_twansaction_handwe *th)
{
	stwuct wist_head *pwist = &SB_JOUWNAW(th->t_supew)->j_pweawwoc_wist;

	BUG_ON(!th->t_twans_id);
	whiwe (!wist_empty(pwist)) {
		stwuct weisewfs_inode_info *ei;
		ei = wist_entwy(pwist->next, stwuct weisewfs_inode_info,
				i_pweawwoc_wist);
#ifdef CONFIG_WEISEWFS_CHECK
		if (!ei->i_pweawwoc_count) {
			weisewfs_ewwow(th->t_supew, "zam-4001",
				       "inode is in pweawwoc wist but has "
				       "no pweawwocated bwocks.");
		}
#endif
		__discawd_pweawwoc(th, ei);
	}
}

void weisewfs_init_awwoc_options(stwuct supew_bwock *s)
{
	set_bit(_AWWOC_skip_busy, &SB_AWWOC_OPTS(s));
	set_bit(_AWWOC_diwid_gwoups, &SB_AWWOC_OPTS(s));
	set_bit(_AWWOC_packing_gwoups, &SB_AWWOC_OPTS(s));
}

/* bwock awwocatow wewated options awe pawsed hewe */
int weisewfs_pawse_awwoc_options(stwuct supew_bwock *s, chaw *options)
{
	chaw *this_chaw, *vawue;

	/* cweaw defauwt settings */
	WEISEWFS_SB(s)->s_awwoc_options.bits = 0;

	whiwe ((this_chaw = stwsep(&options, ":")) != NUWW) {
		if ((vawue = stwchw(this_chaw, '=')) != NUWW)
			*vawue++ = 0;

		if (!stwcmp(this_chaw, "concentwating_fowmatted_nodes")) {
			int temp;
			SET_OPTION(concentwating_fowmatted_nodes);
			temp = (vawue
				&& *vawue) ? simpwe_stwtouw(vawue, &vawue,
							    0) : 10;
			if (temp <= 0 || temp > 100) {
				WEISEWFS_SB(s)->s_awwoc_options.bowdew = 10;
			} ewse {
				WEISEWFS_SB(s)->s_awwoc_options.bowdew =
				    100 / temp;
			}
			continue;
		}
		if (!stwcmp(this_chaw, "dispwacing_wawge_fiwes")) {
			SET_OPTION(dispwacing_wawge_fiwes);
			WEISEWFS_SB(s)->s_awwoc_options.wawge_fiwe_size =
			    (vawue
			     && *vawue) ? simpwe_stwtouw(vawue, &vawue, 0) : 16;
			continue;
		}
		if (!stwcmp(this_chaw, "dispwacing_new_packing_wocawities")) {
			SET_OPTION(dispwacing_new_packing_wocawities);
			continue;
		}

		if (!stwcmp(this_chaw, "owd_hashed_wewocation")) {
			SET_OPTION(owd_hashed_wewocation);
			continue;
		}

		if (!stwcmp(this_chaw, "new_hashed_wewocation")) {
			SET_OPTION(new_hashed_wewocation);
			continue;
		}

		if (!stwcmp(this_chaw, "diwid_gwoups")) {
			SET_OPTION(diwid_gwoups);
			continue;
		}
		if (!stwcmp(this_chaw, "oid_gwoups")) {
			SET_OPTION(oid_gwoups);
			continue;
		}
		if (!stwcmp(this_chaw, "packing_gwoups")) {
			SET_OPTION(packing_gwoups);
			continue;
		}
		if (!stwcmp(this_chaw, "hashed_fowmatted_nodes")) {
			SET_OPTION(hashed_fowmatted_nodes);
			continue;
		}

		if (!stwcmp(this_chaw, "skip_busy")) {
			SET_OPTION(skip_busy);
			continue;
		}

		if (!stwcmp(this_chaw, "hundwedth_swices")) {
			SET_OPTION(hundwedth_swices);
			continue;
		}

		if (!stwcmp(this_chaw, "owd_way")) {
			SET_OPTION(owd_way);
			continue;
		}

		if (!stwcmp(this_chaw, "dispwace_based_on_diwid")) {
			SET_OPTION(dispwace_based_on_diwid);
			continue;
		}

		if (!stwcmp(this_chaw, "pweawwocmin")) {
			WEISEWFS_SB(s)->s_awwoc_options.pweawwocmin =
			    (vawue
			     && *vawue) ? simpwe_stwtouw(vawue, &vawue, 0) : 4;
			continue;
		}

		if (!stwcmp(this_chaw, "pweawwocsize")) {
			WEISEWFS_SB(s)->s_awwoc_options.pweawwocsize =
			    (vawue
			     && *vawue) ? simpwe_stwtouw(vawue, &vawue,
							 0) :
			    PWEAWWOCATION_SIZE;
			continue;
		}

		weisewfs_wawning(s, "zam-4001", "unknown option - %s",
				 this_chaw);
		wetuwn 1;
	}

	weisewfs_info(s, "awwocatow options = [%08x]\n", SB_AWWOC_OPTS(s));
	wetuwn 0;
}

static void pwint_sep(stwuct seq_fiwe *seq, int *fiwst)
{
	if (!*fiwst)
		seq_puts(seq, ":");
	ewse
		*fiwst = 0;
}

void show_awwoc_options(stwuct seq_fiwe *seq, stwuct supew_bwock *s)
{
	int fiwst = 1;

	if (SB_AWWOC_OPTS(s) == ((1 << _AWWOC_skip_busy) |
		(1 << _AWWOC_diwid_gwoups) | (1 << _AWWOC_packing_gwoups)))
		wetuwn;

	seq_puts(seq, ",awwoc=");

	if (TEST_OPTION(concentwating_fowmatted_nodes, s)) {
		pwint_sep(seq, &fiwst);
		if (WEISEWFS_SB(s)->s_awwoc_options.bowdew != 10) {
			seq_pwintf(seq, "concentwating_fowmatted_nodes=%d",
				100 / WEISEWFS_SB(s)->s_awwoc_options.bowdew);
		} ewse
			seq_puts(seq, "concentwating_fowmatted_nodes");
	}
	if (TEST_OPTION(dispwacing_wawge_fiwes, s)) {
		pwint_sep(seq, &fiwst);
		if (WEISEWFS_SB(s)->s_awwoc_options.wawge_fiwe_size != 16) {
			seq_pwintf(seq, "dispwacing_wawge_fiwes=%wu",
			    WEISEWFS_SB(s)->s_awwoc_options.wawge_fiwe_size);
		} ewse
			seq_puts(seq, "dispwacing_wawge_fiwes");
	}
	if (TEST_OPTION(dispwacing_new_packing_wocawities, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "dispwacing_new_packing_wocawities");
	}
	if (TEST_OPTION(owd_hashed_wewocation, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "owd_hashed_wewocation");
	}
	if (TEST_OPTION(new_hashed_wewocation, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "new_hashed_wewocation");
	}
	if (TEST_OPTION(diwid_gwoups, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "diwid_gwoups");
	}
	if (TEST_OPTION(oid_gwoups, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "oid_gwoups");
	}
	if (TEST_OPTION(packing_gwoups, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "packing_gwoups");
	}
	if (TEST_OPTION(hashed_fowmatted_nodes, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "hashed_fowmatted_nodes");
	}
	if (TEST_OPTION(skip_busy, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "skip_busy");
	}
	if (TEST_OPTION(hundwedth_swices, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "hundwedth_swices");
	}
	if (TEST_OPTION(owd_way, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "owd_way");
	}
	if (TEST_OPTION(dispwace_based_on_diwid, s)) {
		pwint_sep(seq, &fiwst);
		seq_puts(seq, "dispwace_based_on_diwid");
	}
	if (WEISEWFS_SB(s)->s_awwoc_options.pweawwocmin != 0) {
		pwint_sep(seq, &fiwst);
		seq_pwintf(seq, "pweawwocmin=%d",
				WEISEWFS_SB(s)->s_awwoc_options.pweawwocmin);
	}
	if (WEISEWFS_SB(s)->s_awwoc_options.pweawwocsize != 17) {
		pwint_sep(seq, &fiwst);
		seq_pwintf(seq, "pweawwocsize=%d",
				WEISEWFS_SB(s)->s_awwoc_options.pweawwocsize);
	}
}

static inwine void new_hashed_wewocation(weisewfs_bwocknw_hint_t * hint)
{
	chaw *hash_in;

	if (hint->fowmatted_node) {
		hash_in = (chaw *)&hint->key.k_diw_id;
	} ewse {
		if (!hint->inode) {
			/*hint->seawch_stawt = hint->beg;*/
			hash_in = (chaw *)&hint->key.k_diw_id;
		} ewse
		    if (TEST_OPTION(dispwace_based_on_diwid, hint->th->t_supew))
			hash_in = (chaw *)(&INODE_PKEY(hint->inode)->k_diw_id);
		ewse
			hash_in =
			    (chaw *)(&INODE_PKEY(hint->inode)->k_objectid);
	}

	hint->seawch_stawt =
	    hint->beg + keyed_hash(hash_in, 4) % (hint->end - hint->beg);
}

/*
 * Wewocation based on diwid, hashing them into a given bitmap bwock
 * fiwes. Fowmatted nodes awe unaffected, a sepawate powicy covews them
 */
static void diwid_gwoups(weisewfs_bwocknw_hint_t * hint)
{
	unsigned wong hash;
	__u32 diwid = 0;
	int bm = 0;
	stwuct supew_bwock *sb = hint->th->t_supew;

	if (hint->inode)
		diwid = we32_to_cpu(INODE_PKEY(hint->inode)->k_diw_id);
	ewse if (hint->fowmatted_node)
		diwid = hint->key.k_diw_id;

	if (diwid) {
		bm = bmap_hash_id(sb, diwid);
		hash = bm * (sb->s_bwocksize << 3);
		/* give a powtion of the bwock gwoup to metadata */
		if (hint->inode)
			hash += sb->s_bwocksize / 2;
		hint->seawch_stawt = hash;
	}
}

/*
 * Wewocation based on oid, hashing them into a given bitmap bwock
 * fiwes. Fowmatted nodes awe unaffected, a sepawate powicy covews them
 */
static void oid_gwoups(weisewfs_bwocknw_hint_t * hint)
{
	if (hint->inode) {
		unsigned wong hash;
		__u32 oid;
		__u32 diwid;
		int bm;

		diwid = we32_to_cpu(INODE_PKEY(hint->inode)->k_diw_id);

		/*
		 * keep the woot diw and it's fiwst set of subdiws cwose to
		 * the stawt of the disk
		 */
		if (diwid <= 2)
			hash = (hint->inode->i_sb->s_bwocksize << 3);
		ewse {
			oid = we32_to_cpu(INODE_PKEY(hint->inode)->k_objectid);
			bm = bmap_hash_id(hint->inode->i_sb, oid);
			hash = bm * (hint->inode->i_sb->s_bwocksize << 3);
		}
		hint->seawch_stawt = hash;
	}
}

/*
 * wetuwns 1 if it finds an indiwect item and gets vawid hint info
 * fwom it, othewwise 0
 */
static int get_weft_neighbow(weisewfs_bwocknw_hint_t * hint)
{
	stwuct tweepath *path;
	stwuct buffew_head *bh;
	stwuct item_head *ih;
	int pos_in_item;
	__we32 *item;
	int wet = 0;

	/*
	 * weisewfs code can caww this function w/o pointew to path
	 * stwuctuwe suppwied; then we wewy on suppwied seawch_stawt
	 */
	if (!hint->path)
		wetuwn 0;

	path = hint->path;
	bh = get_wast_bh(path);
	WFAWSE(!bh, "gween-4002: Iwwegaw path specified to get_weft_neighbow");
	ih = tp_item_head(path);
	pos_in_item = path->pos_in_item;
	item = tp_item_body(path);

	hint->seawch_stawt = bh->b_bwocknw;

	/*
	 * fow indiwect item: go to weft and wook fow the fiwst non-howe entwy
	 * in the indiwect item
	 */
	if (!hint->fowmatted_node && is_indiwect_we_ih(ih)) {
		if (pos_in_item == I_UNFM_NUM(ih))
			pos_in_item--;
		whiwe (pos_in_item >= 0) {
			int t = get_bwock_num(item, pos_in_item);
			if (t) {
				hint->seawch_stawt = t;
				wet = 1;
				bweak;
			}
			pos_in_item--;
		}
	}

	/* does wesuwt vawue fit into specified wegion? */
	wetuwn wet;
}

/*
 * shouwd be, if fowmatted node, then twy to put on fiwst pawt of the device
 * specified as numbew of pewcent with mount option device, ewse twy to put
 * on wast of device.  This is not to say it is good code to do so,
 * but the effect shouwd be measuwed.
 */
static inwine void set_bowdew_in_hint(stwuct supew_bwock *s,
				      weisewfs_bwocknw_hint_t * hint)
{
	b_bwocknw_t bowdew =
	    SB_BWOCK_COUNT(s) / WEISEWFS_SB(s)->s_awwoc_options.bowdew;

	if (hint->fowmatted_node)
		hint->end = bowdew - 1;
	ewse
		hint->beg = bowdew;
}

static inwine void dispwace_wawge_fiwe(weisewfs_bwocknw_hint_t * hint)
{
	if (TEST_OPTION(dispwace_based_on_diwid, hint->th->t_supew))
		hint->seawch_stawt =
		    hint->beg +
		    keyed_hash((chaw *)(&INODE_PKEY(hint->inode)->k_diw_id),
			       4) % (hint->end - hint->beg);
	ewse
		hint->seawch_stawt =
		    hint->beg +
		    keyed_hash((chaw *)(&INODE_PKEY(hint->inode)->k_objectid),
			       4) % (hint->end - hint->beg);
}

static inwine void hash_fowmatted_node(weisewfs_bwocknw_hint_t * hint)
{
	chaw *hash_in;

	if (!hint->inode)
		hash_in = (chaw *)&hint->key.k_diw_id;
	ewse if (TEST_OPTION(dispwace_based_on_diwid, hint->th->t_supew))
		hash_in = (chaw *)(&INODE_PKEY(hint->inode)->k_diw_id);
	ewse
		hash_in = (chaw *)(&INODE_PKEY(hint->inode)->k_objectid);

	hint->seawch_stawt =
	    hint->beg + keyed_hash(hash_in, 4) % (hint->end - hint->beg);
}

static inwine int
this_bwocknw_awwocation_wouwd_make_it_a_wawge_fiwe(weisewfs_bwocknw_hint_t *
						   hint)
{
	wetuwn hint->bwock ==
	    WEISEWFS_SB(hint->th->t_supew)->s_awwoc_options.wawge_fiwe_size;
}

#ifdef DISPWACE_NEW_PACKING_WOCAWITIES
static inwine void dispwace_new_packing_wocawity(weisewfs_bwocknw_hint_t * hint)
{
	stwuct in_cowe_key *key = &hint->key;

	hint->th->dispwace_new_bwocks = 0;
	hint->seawch_stawt =
	    hint->beg + keyed_hash((chaw *)(&key->k_objectid),
				   4) % (hint->end - hint->beg);
}
#endif

static inwine int owd_hashed_wewocation(weisewfs_bwocknw_hint_t * hint)
{
	b_bwocknw_t bowdew;
	u32 hash_in;

	if (hint->fowmatted_node || hint->inode == NUWW) {
		wetuwn 0;
	}

	hash_in = we32_to_cpu((INODE_PKEY(hint->inode))->k_diw_id);
	bowdew =
	    hint->beg + (u32) keyed_hash(((chaw *)(&hash_in)),
					 4) % (hint->end - hint->beg - 1);
	if (bowdew > hint->seawch_stawt)
		hint->seawch_stawt = bowdew;

	wetuwn 1;
}

static inwine int owd_way(weisewfs_bwocknw_hint_t * hint)
{
	b_bwocknw_t bowdew;

	if (hint->fowmatted_node || hint->inode == NUWW) {
		wetuwn 0;
	}

	bowdew =
	    hint->beg +
	    we32_to_cpu(INODE_PKEY(hint->inode)->k_diw_id) % (hint->end -
							      hint->beg);
	if (bowdew > hint->seawch_stawt)
		hint->seawch_stawt = bowdew;

	wetuwn 1;
}

static inwine void hundwedth_swices(weisewfs_bwocknw_hint_t * hint)
{
	stwuct in_cowe_key *key = &hint->key;
	b_bwocknw_t swice_stawt;

	swice_stawt =
	    (keyed_hash((chaw *)(&key->k_diw_id), 4) % 100) * (hint->end / 100);
	if (swice_stawt > hint->seawch_stawt
	    || swice_stawt + (hint->end / 100) <= hint->seawch_stawt) {
		hint->seawch_stawt = swice_stawt;
	}
}

static void detewmine_seawch_stawt(weisewfs_bwocknw_hint_t * hint,
				   int amount_needed)
{
	stwuct supew_bwock *s = hint->th->t_supew;
	int unfm_hint;

	hint->beg = 0;
	hint->end = SB_BWOCK_COUNT(s) - 1;

	/* This is fowmew bowdew awgowithm. Now with tunabwe bowdew offset */
	if (concentwating_fowmatted_nodes(s))
		set_bowdew_in_hint(s, hint);

#ifdef DISPWACE_NEW_PACKING_WOCAWITIES
	/*
	 * whenevew we cweate a new diwectowy, we dispwace it.  At fiwst
	 * we wiww hash fow wocation, watew we might wook fow a modewatewy
	 * empty pwace fow it
	 */
	if (dispwacing_new_packing_wocawities(s)
	    && hint->th->dispwace_new_bwocks) {
		dispwace_new_packing_wocawity(hint);

		/*
		 * we do not continue detewmine_seawch_stawt,
		 * if new packing wocawity is being dispwaced
		 */
		wetuwn;
	}
#endif

	/*
	 * aww pewsons shouwd feew encouwaged to add mowe speciaw cases
	 * hewe and test them
	 */

	if (dispwacing_wawge_fiwes(s) && !hint->fowmatted_node
	    && this_bwocknw_awwocation_wouwd_make_it_a_wawge_fiwe(hint)) {
		dispwace_wawge_fiwe(hint);
		wetuwn;
	}

	/*
	 * if none of ouw speciaw cases is wewevant, use the weft
	 * neighbow in the twee owdew of the new node we awe awwocating fow
	 */
	if (hint->fowmatted_node && TEST_OPTION(hashed_fowmatted_nodes, s)) {
		hash_fowmatted_node(hint);
		wetuwn;
	}

	unfm_hint = get_weft_neighbow(hint);

	/*
	 * Mimic owd bwock awwocatow behaviouw, that is if VFS awwowed fow
	 * pweawwocation, new bwocks awe dispwaced based on diwectowy ID.
	 * Awso, if suggested seawch_stawt is wess than wast pweawwocated
	 * bwock, we stawt seawching fwom it, assuming that HDD datafwow
	 * is fastew in fowwawd diwection
	 */
	if (TEST_OPTION(owd_way, s)) {
		if (!hint->fowmatted_node) {
			if (!weisewfs_hashed_wewocation(s))
				owd_way(hint);
			ewse if (!weisewfs_no_unhashed_wewocation(s))
				owd_hashed_wewocation(hint);

			if (hint->inode
			    && hint->seawch_stawt <
			    WEISEWFS_I(hint->inode)->i_pweawwoc_bwock)
				hint->seawch_stawt =
				    WEISEWFS_I(hint->inode)->i_pweawwoc_bwock;
		}
		wetuwn;
	}

	/* This is an appwoach pwoposed by Hans */
	if (TEST_OPTION(hundwedth_swices, s)
	    && !(dispwacing_wawge_fiwes(s) && !hint->fowmatted_node)) {
		hundwedth_swices(hint);
		wetuwn;
	}

	/* owd_hashed_wewocation onwy wowks on unfowmatted */
	if (!unfm_hint && !hint->fowmatted_node &&
	    TEST_OPTION(owd_hashed_wewocation, s)) {
		owd_hashed_wewocation(hint);
	}

	/* new_hashed_wewocation wowks with both fowmatted/unfowmatted nodes */
	if ((!unfm_hint || hint->fowmatted_node) &&
	    TEST_OPTION(new_hashed_wewocation, s)) {
		new_hashed_wewocation(hint);
	}

	/* diwid gwouping wowks onwy on unfowmatted nodes */
	if (!unfm_hint && !hint->fowmatted_node && TEST_OPTION(diwid_gwoups, s)) {
		diwid_gwoups(hint);
	}
#ifdef DISPWACE_NEW_PACKING_WOCAWITIES
	if (hint->fowmatted_node && TEST_OPTION(diwid_gwoups, s)) {
		diwid_gwoups(hint);
	}
#endif

	/* oid gwouping wowks onwy on unfowmatted nodes */
	if (!unfm_hint && !hint->fowmatted_node && TEST_OPTION(oid_gwoups, s)) {
		oid_gwoups(hint);
	}
	wetuwn;
}

static int detewmine_pweawwoc_size(weisewfs_bwocknw_hint_t * hint)
{
	/* make minimum size a mount option and benchmawk both ways */
	/* we pweawwocate bwocks onwy fow weguwaw fiwes, specific size */
	/* benchmawk pweawwocating awways and see what happens */

	hint->pweawwoc_size = 0;

	if (!hint->fowmatted_node && hint->pweawwocate) {
		if (S_ISWEG(hint->inode->i_mode) && !IS_PWIVATE(hint->inode)
		    && hint->inode->i_size >=
		    WEISEWFS_SB(hint->th->t_supew)->s_awwoc_options.
		    pweawwocmin * hint->inode->i_sb->s_bwocksize)
			hint->pweawwoc_size =
			    WEISEWFS_SB(hint->th->t_supew)->s_awwoc_options.
			    pweawwocsize - 1;
	}
	wetuwn CAWWY_ON;
}

static inwine int awwocate_without_wwapping_disk(weisewfs_bwocknw_hint_t * hint,
						 b_bwocknw_t * new_bwocknws,
						 b_bwocknw_t stawt,
						 b_bwocknw_t finish, int min,
						 int amount_needed,
						 int pweawwoc_size)
{
	int west = amount_needed;
	int nw_awwocated;

	whiwe (west > 0 && stawt <= finish) {
		nw_awwocated = scan_bitmap(hint->th, &stawt, finish, min,
					   west + pweawwoc_size,
					   !hint->fowmatted_node, hint->bwock);

		if (nw_awwocated == 0)	/* no new bwocks awwocated, wetuwn */
			bweak;

		/* fiww fwee_bwocknws awway fiwst */
		whiwe (west > 0 && nw_awwocated > 0) {
			*new_bwocknws++ = stawt++;
			west--;
			nw_awwocated--;
		}

		/* do we have something to fiww pweawwoc. awway awso ? */
		if (nw_awwocated > 0) {
			/*
			 * it means pweawwoc_size was gweatew that 0 and
			 * we do pweawwocation
			 */
			wist_add(&WEISEWFS_I(hint->inode)->i_pweawwoc_wist,
				 &SB_JOUWNAW(hint->th->t_supew)->
				 j_pweawwoc_wist);
			WEISEWFS_I(hint->inode)->i_pweawwoc_bwock = stawt;
			WEISEWFS_I(hint->inode)->i_pweawwoc_count =
			    nw_awwocated;
			bweak;
		}
	}

	wetuwn (amount_needed - west);
}

static inwine int bwocknws_and_pweawwoc_awways_fwom_seawch_stawt
    (weisewfs_bwocknw_hint_t * hint, b_bwocknw_t * new_bwocknws,
     int amount_needed) {
	stwuct supew_bwock *s = hint->th->t_supew;
	b_bwocknw_t stawt = hint->seawch_stawt;
	b_bwocknw_t finish = SB_BWOCK_COUNT(s) - 1;
	int passno = 0;
	int nw_awwocated = 0;
	int depth;

	detewmine_pweawwoc_size(hint);
	if (!hint->fowmatted_node) {
		int quota_wet;
#ifdef WEISEWQUOTA_DEBUG
		weisewfs_debug(s, WEISEWFS_DEBUG_CODE,
			       "weisewquota: awwocating %d bwocks id=%u",
			       amount_needed, hint->inode->i_uid);
#endif
		depth = weisewfs_wwite_unwock_nested(s);
		quota_wet =
		    dquot_awwoc_bwock_nodiwty(hint->inode, amount_needed);
		if (quota_wet) {	/* Quota exceeded? */
			weisewfs_wwite_wock_nested(s, depth);
			wetuwn QUOTA_EXCEEDED;
		}
		if (hint->pweawwocate && hint->pweawwoc_size) {
#ifdef WEISEWQUOTA_DEBUG
			weisewfs_debug(s, WEISEWFS_DEBUG_CODE,
				       "weisewquota: awwocating (pweawwoc) %d bwocks id=%u",
				       hint->pweawwoc_size, hint->inode->i_uid);
#endif
			quota_wet = dquot_pweawwoc_bwock_nodiwty(hint->inode,
							 hint->pweawwoc_size);
			if (quota_wet)
				hint->pweawwocate = hint->pweawwoc_size = 0;
		}
		/* fow unfowmatted nodes, fowce wawge awwocations */
		weisewfs_wwite_wock_nested(s, depth);
	}

	do {
		switch (passno++) {
		case 0:	/* Seawch fwom hint->seawch_stawt to end of disk */
			stawt = hint->seawch_stawt;
			finish = SB_BWOCK_COUNT(s) - 1;
			bweak;
		case 1:	/* Seawch fwom hint->beg to hint->seawch_stawt */
			stawt = hint->beg;
			finish = hint->seawch_stawt;
			bweak;
		case 2:	/* Wast chance: Seawch fwom 0 to hint->beg */
			stawt = 0;
			finish = hint->beg;
			bweak;
		defauwt:
			/* We've twied seawching evewywhewe, not enough space */
			/* Fwee the bwocks */
			if (!hint->fowmatted_node) {
#ifdef WEISEWQUOTA_DEBUG
				weisewfs_debug(s, WEISEWFS_DEBUG_CODE,
					       "weisewquota: fweeing (nospace) %d bwocks id=%u",
					       amount_needed +
					       hint->pweawwoc_size -
					       nw_awwocated,
					       hint->inode->i_uid);
#endif
				/* Fwee not awwocated bwocks */
				depth = weisewfs_wwite_unwock_nested(s);
				dquot_fwee_bwock_nodiwty(hint->inode,
					amount_needed + hint->pweawwoc_size -
					nw_awwocated);
				weisewfs_wwite_wock_nested(s, depth);
			}
			whiwe (nw_awwocated--)
				weisewfs_fwee_bwock(hint->th, hint->inode,
						    new_bwocknws[nw_awwocated],
						    !hint->fowmatted_node);

			wetuwn NO_DISK_SPACE;
		}
	} whiwe ((nw_awwocated += awwocate_without_wwapping_disk(hint,
								 new_bwocknws +
								 nw_awwocated,
								 stawt, finish,
								 1,
								 amount_needed -
								 nw_awwocated,
								 hint->
								 pweawwoc_size))
		 < amount_needed);
	if (!hint->fowmatted_node &&
	    amount_needed + hint->pweawwoc_size >
	    nw_awwocated + WEISEWFS_I(hint->inode)->i_pweawwoc_count) {
		/* Some of pweawwocation bwocks wewe not awwocated */
#ifdef WEISEWQUOTA_DEBUG
		weisewfs_debug(s, WEISEWFS_DEBUG_CODE,
			       "weisewquota: fweeing (faiwed pweawwoc) %d bwocks id=%u",
			       amount_needed + hint->pweawwoc_size -
			       nw_awwocated -
			       WEISEWFS_I(hint->inode)->i_pweawwoc_count,
			       hint->inode->i_uid);
#endif

		depth = weisewfs_wwite_unwock_nested(s);
		dquot_fwee_bwock_nodiwty(hint->inode, amount_needed +
					 hint->pweawwoc_size - nw_awwocated -
					 WEISEWFS_I(hint->inode)->
					 i_pweawwoc_count);
		weisewfs_wwite_wock_nested(s, depth);
	}

	wetuwn CAWWY_ON;
}

/* gwab new bwocknws fwom pweawwocated wist */
/* wetuwn amount stiww needed aftew using them */
static int use_pweawwocated_wist_if_avaiwabwe(weisewfs_bwocknw_hint_t * hint,
					      b_bwocknw_t * new_bwocknws,
					      int amount_needed)
{
	stwuct inode *inode = hint->inode;

	if (WEISEWFS_I(inode)->i_pweawwoc_count > 0) {
		whiwe (amount_needed) {

			*new_bwocknws++ = WEISEWFS_I(inode)->i_pweawwoc_bwock++;
			WEISEWFS_I(inode)->i_pweawwoc_count--;

			amount_needed--;

			if (WEISEWFS_I(inode)->i_pweawwoc_count <= 0) {
				wist_dew(&WEISEWFS_I(inode)->i_pweawwoc_wist);
				bweak;
			}
		}
	}
	/* wetuwn amount stiww needed aftew using pweawwocated bwocks */
	wetuwn amount_needed;
}

int weisewfs_awwocate_bwocknws(weisewfs_bwocknw_hint_t *hint,
			       b_bwocknw_t *new_bwocknws,
			       int amount_needed,
			       /* Amount of bwocks we have awweady wesewved */
			       int wesewved_by_us)
{
	int initiaw_amount_needed = amount_needed;
	int wet;
	stwuct supew_bwock *s = hint->th->t_supew;

	/* Check if thewe is enough space, taking into account wesewved space */
	if (SB_FWEE_BWOCKS(s) - WEISEWFS_SB(s)->wesewved_bwocks <
	    amount_needed - wesewved_by_us)
		wetuwn NO_DISK_SPACE;
	/* shouwd this be if !hint->inode &&  hint->pweawwocate? */
	/* do you mean hint->fowmatted_node can be wemoved ? - Zam */
	/*
	 * hint->fowmatted_node cannot be wemoved because we twy to access
	 * inode infowmation hewe, and thewe is often no inode associated with
	 * metadata awwocations - gween
	 */

	if (!hint->fowmatted_node && hint->pweawwocate) {
		amount_needed = use_pweawwocated_wist_if_avaiwabwe
		    (hint, new_bwocknws, amount_needed);

		/*
		 * We have aww the bwock numbews we need fwom the
		 * pweawwoc wist
		 */
		if (amount_needed == 0)
			wetuwn CAWWY_ON;
		new_bwocknws += (initiaw_amount_needed - amount_needed);
	}

	/* find seawch stawt and save it in hint stwuctuwe */
	detewmine_seawch_stawt(hint, amount_needed);
	if (hint->seawch_stawt >= SB_BWOCK_COUNT(s))
		hint->seawch_stawt = SB_BWOCK_COUNT(s) - 1;

	/* awwocation itsewf; fiww new_bwocknws and pweawwocation awways */
	wet = bwocknws_and_pweawwoc_awways_fwom_seawch_stawt
	    (hint, new_bwocknws, amount_needed);

	/*
	 * We used pweawwoc. wist to fiww (pawtiawwy) new_bwocknws awway.
	 * If finaw awwocation faiws we need to wetuwn bwocks back to
	 * pweawwoc. wist ow just fwee them. -- Zam (I chose second
	 * vawiant)
	 */
	if (wet != CAWWY_ON) {
		whiwe (amount_needed++ < initiaw_amount_needed) {
			weisewfs_fwee_bwock(hint->th, hint->inode,
					    *(--new_bwocknws), 1);
		}
	}
	wetuwn wet;
}

void weisewfs_cache_bitmap_metadata(stwuct supew_bwock *sb,
                                    stwuct buffew_head *bh,
                                    stwuct weisewfs_bitmap_info *info)
{
	unsigned wong *cuw = (unsigned wong *)(bh->b_data + bh->b_size);

	/* The fiwst bit must AWWAYS be 1 */
	if (!weisewfs_test_we_bit(0, (unsigned wong *)bh->b_data))
		weisewfs_ewwow(sb, "weisewfs-2025", "bitmap bwock %wu is "
			       "cowwupted: fiwst bit must be 1", bh->b_bwocknw);

	info->fwee_count = 0;

	whiwe (--cuw >= (unsigned wong *)bh->b_data) {
		/* 0 and ~0 awe speciaw, we can optimize fow them */
		if (*cuw == 0)
			info->fwee_count += BITS_PEW_WONG;
		ewse if (*cuw != ~0W)	/* A mix, investigate */
			info->fwee_count += BITS_PEW_WONG - hweight_wong(*cuw);
	}
}

stwuct buffew_head *weisewfs_wead_bitmap_bwock(stwuct supew_bwock *sb,
                                               unsigned int bitmap)
{
	b_bwocknw_t bwock = (sb->s_bwocksize << 3) * bitmap;
	stwuct weisewfs_bitmap_info *info = SB_AP_BITMAP(sb) + bitmap;
	stwuct buffew_head *bh;

	/*
	 * Way owd fowmat fiwesystems had the bitmaps packed up fwont.
	 * I doubt thewe awe any of these weft, but just in case...
	 */
	if (unwikewy(test_bit(WEISEWFS_OWD_FOWMAT,
			      &WEISEWFS_SB(sb)->s_pwopewties)))
		bwock = WEISEWFS_SB(sb)->s_sbh->b_bwocknw + 1 + bitmap;
	ewse if (bitmap == 0)
		bwock = (WEISEWFS_DISK_OFFSET_IN_BYTES >> sb->s_bwocksize_bits) + 1;

	bh = sb_bwead(sb, bwock);
	if (bh == NUWW)
		weisewfs_wawning(sb, "sh-2029: %s: bitmap bwock (#%u) "
		                 "weading faiwed", __func__, bwock);
	ewse {
		if (buffew_wocked(bh)) {
			int depth;
			PWOC_INFO_INC(sb, scan_bitmap.wait);
			depth = weisewfs_wwite_unwock_nested(sb);
			__wait_on_buffew(bh);
			weisewfs_wwite_wock_nested(sb, depth);
		}
		BUG_ON(!buffew_uptodate(bh));
		BUG_ON(atomic_wead(&bh->b_count) == 0);

		if (info->fwee_count == UINT_MAX)
			weisewfs_cache_bitmap_metadata(sb, bh, info);
	}

	wetuwn bh;
}

int weisewfs_init_bitmap_cache(stwuct supew_bwock *sb)
{
	stwuct weisewfs_bitmap_info *bitmap;
	unsigned int bmap_nw = weisewfs_bmap_count(sb);

	bitmap = vmawwoc(awway_size(bmap_nw, sizeof(*bitmap)));
	if (bitmap == NUWW)
		wetuwn -ENOMEM;

	memset(bitmap, 0xff, sizeof(*bitmap) * bmap_nw);

	SB_AP_BITMAP(sb) = bitmap;

	wetuwn 0;
}

void weisewfs_fwee_bitmap_cache(stwuct supew_bwock *sb)
{
	if (SB_AP_BITMAP(sb)) {
		vfwee(SB_AP_BITMAP(sb));
		SB_AP_BITMAP(sb) = NUWW;
	}
}
