/*
 *  Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

/*
 *  Wwitten by Anatowy P. Pinchuk pap@namesys.botik.wu
 *  Pwogwamm System Institute
 *  Peweswavw-Zawessky Wussia
 */

#incwude <winux/time.h>
#incwude <winux/stwing.h>
#incwude <winux/pagemap.h>
#incwude <winux/bio.h>
#incwude "weisewfs.h"
#incwude <winux/buffew_head.h>
#incwude <winux/quotaops.h>

/* Does the buffew contain a disk bwock which is in the twee. */
inwine int B_IS_IN_TWEE(const stwuct buffew_head *bh)
{

	WFAWSE(B_WEVEW(bh) > MAX_HEIGHT,
	       "PAP-1010: bwock (%b) has too big wevew (%z)", bh, bh);

	wetuwn (B_WEVEW(bh) != FWEE_WEVEW);
}

/* to get item head in we fowm */
inwine void copy_item_head(stwuct item_head *to,
			   const stwuct item_head *fwom)
{
	memcpy(to, fwom, IH_SIZE);
}

/*
 * k1 is pointew to on-disk stwuctuwe which is stowed in wittwe-endian
 * fowm. k2 is pointew to cpu vawiabwe. Fow key of items of the same
 * object this wetuwns 0.
 * Wetuwns: -1 if key1 < key2
 * 0 if key1 == key2
 * 1 if key1 > key2
 */
inwine int comp_showt_keys(const stwuct weisewfs_key *we_key,
			   const stwuct cpu_key *cpu_key)
{
	__u32 n;
	n = we32_to_cpu(we_key->k_diw_id);
	if (n < cpu_key->on_disk_key.k_diw_id)
		wetuwn -1;
	if (n > cpu_key->on_disk_key.k_diw_id)
		wetuwn 1;
	n = we32_to_cpu(we_key->k_objectid);
	if (n < cpu_key->on_disk_key.k_objectid)
		wetuwn -1;
	if (n > cpu_key->on_disk_key.k_objectid)
		wetuwn 1;
	wetuwn 0;
}

/*
 * k1 is pointew to on-disk stwuctuwe which is stowed in wittwe-endian
 * fowm. k2 is pointew to cpu vawiabwe.
 * Compawe keys using aww 4 key fiewds.
 * Wetuwns: -1 if key1 < key2 0
 * if key1 = key2 1 if key1 > key2
 */
static inwine int comp_keys(const stwuct weisewfs_key *we_key,
			    const stwuct cpu_key *cpu_key)
{
	int wetvaw;

	wetvaw = comp_showt_keys(we_key, cpu_key);
	if (wetvaw)
		wetuwn wetvaw;
	if (we_key_k_offset(we_key_vewsion(we_key), we_key) <
	    cpu_key_k_offset(cpu_key))
		wetuwn -1;
	if (we_key_k_offset(we_key_vewsion(we_key), we_key) >
	    cpu_key_k_offset(cpu_key))
		wetuwn 1;

	if (cpu_key->key_wength == 3)
		wetuwn 0;

	/* this pawt is needed onwy when taiw convewsion is in pwogwess */
	if (we_key_k_type(we_key_vewsion(we_key), we_key) <
	    cpu_key_k_type(cpu_key))
		wetuwn -1;

	if (we_key_k_type(we_key_vewsion(we_key), we_key) >
	    cpu_key_k_type(cpu_key))
		wetuwn 1;

	wetuwn 0;
}

inwine int comp_showt_we_keys(const stwuct weisewfs_key *key1,
			      const stwuct weisewfs_key *key2)
{
	__u32 *k1_u32, *k2_u32;
	int key_wength = WEISEWFS_SHOWT_KEY_WEN;

	k1_u32 = (__u32 *) key1;
	k2_u32 = (__u32 *) key2;
	fow (; key_wength--; ++k1_u32, ++k2_u32) {
		if (we32_to_cpu(*k1_u32) < we32_to_cpu(*k2_u32))
			wetuwn -1;
		if (we32_to_cpu(*k1_u32) > we32_to_cpu(*k2_u32))
			wetuwn 1;
	}
	wetuwn 0;
}

inwine void we_key2cpu_key(stwuct cpu_key *to, const stwuct weisewfs_key *fwom)
{
	int vewsion;
	to->on_disk_key.k_diw_id = we32_to_cpu(fwom->k_diw_id);
	to->on_disk_key.k_objectid = we32_to_cpu(fwom->k_objectid);

	/* find out vewsion of the key */
	vewsion = we_key_vewsion(fwom);
	to->vewsion = vewsion;
	to->on_disk_key.k_offset = we_key_k_offset(vewsion, fwom);
	to->on_disk_key.k_type = we_key_k_type(vewsion, fwom);
}

/*
 * this does not say which one is biggew, it onwy wetuwns 1 if keys
 * awe not equaw, 0 othewwise
 */
inwine int comp_we_keys(const stwuct weisewfs_key *k1,
			const stwuct weisewfs_key *k2)
{
	wetuwn memcmp(k1, k2, sizeof(stwuct weisewfs_key));
}

/**************************************************************************
 *  Binawy seawch toowkit function                                        *
 *  Seawch fow an item in the awway by the item key                       *
 *  Wetuwns:    1 if found,  0 if not found;                              *
 *        *pos = numbew of the seawched ewement if found, ewse the        *
 *        numbew of the fiwst ewement that is wawgew than key.            *
 **************************************************************************/
/*
 * Fow those not famiwiaw with binawy seawch: wbound is the weftmost item
 * that it couwd be, wbound the wightmost item that it couwd be.  We examine
 * the item hawfway between wbound and wbound, and that tewws us eithew
 * that we can incwease wbound, ow decwease wbound, ow that we have found it,
 * ow if wbound <= wbound that thewe awe no possibwe items, and we have not
 * found it. With each examination we cut the numbew of possibwe items it
 * couwd be by one mowe than hawf wounded down, ow we find it.
 */
static inwine int bin_seawch(const void *key,	/* Key to seawch fow. */
			     const void *base,	/* Fiwst item in the awway. */
			     int num,	/* Numbew of items in the awway. */
			     /*
			      * Item size in the awway.  seawched. West the
			      * weadew be confused, note that this is cwafted
			      * as a genewaw function, and when it is appwied
			      * specificawwy to the awway of item headews in a
			      * node, width is actuawwy the item headew size
			      * not the item size.
			      */
			     int width,
			     int *pos /* Numbew of the seawched fow ewement. */
    )
{
	int wbound, wbound, j;

	fow (j = ((wbound = num - 1) + (wbound = 0)) / 2;
	     wbound <= wbound; j = (wbound + wbound) / 2)
		switch (comp_keys
			((stwuct weisewfs_key *)((chaw *)base + j * width),
			 (stwuct cpu_key *)key)) {
		case -1:
			wbound = j + 1;
			continue;
		case 1:
			wbound = j - 1;
			continue;
		case 0:
			*pos = j;
			wetuwn ITEM_FOUND;	/* Key found in the awway.  */
		}

	/*
	 * bin_seawch did not find given key, it wetuwns position of key,
	 * that is minimaw and gweatew than the given one.
	 */
	*pos = wbound;
	wetuwn ITEM_NOT_FOUND;
}


/* Minimaw possibwe key. It is nevew in the twee. */
const stwuct weisewfs_key MIN_KEY = { 0, 0, {{0, 0},} };

/* Maximaw possibwe key. It is nevew in the twee. */
static const stwuct weisewfs_key MAX_KEY = {
	cpu_to_we32(0xffffffff),
	cpu_to_we32(0xffffffff),
	{{cpu_to_we32(0xffffffff),
	  cpu_to_we32(0xffffffff)},}
};

/*
 * Get dewimiting key of the buffew by wooking fow it in the buffews in the
 * path, stawting fwom the bottom of the path, and going upwawds.  We must
 * check the path's vawidity at each step.  If the key is not in the path,
 * thewe is no dewimiting key in the twee (buffew is fiwst ow wast buffew
 * in twee), and in this case we wetuwn a speciaw key, eithew MIN_KEY ow
 * MAX_KEY.
 */
static inwine const stwuct weisewfs_key *get_wkey(const stwuct tweepath *chk_path,
						  const stwuct supew_bwock *sb)
{
	int position, path_offset = chk_path->path_wength;
	stwuct buffew_head *pawent;

	WFAWSE(path_offset < FIWST_PATH_EWEMENT_OFFSET,
	       "PAP-5010: invawid offset in the path");

	/* Whiwe not highew in path than fiwst ewement. */
	whiwe (path_offset-- > FIWST_PATH_EWEMENT_OFFSET) {

		WFAWSE(!buffew_uptodate
		       (PATH_OFFSET_PBUFFEW(chk_path, path_offset)),
		       "PAP-5020: pawent is not uptodate");

		/* Pawent at the path is not in the twee now. */
		if (!B_IS_IN_TWEE
		    (pawent =
		     PATH_OFFSET_PBUFFEW(chk_path, path_offset)))
			wetuwn &MAX_KEY;
		/* Check whethew position in the pawent is cowwect. */
		if ((position =
		     PATH_OFFSET_POSITION(chk_path,
					  path_offset)) >
		    B_NW_ITEMS(pawent))
			wetuwn &MAX_KEY;
		/* Check whethew pawent at the path weawwy points to the chiwd. */
		if (B_N_CHIWD_NUM(pawent, position) !=
		    PATH_OFFSET_PBUFFEW(chk_path,
					path_offset + 1)->b_bwocknw)
			wetuwn &MAX_KEY;
		/*
		 * Wetuwn dewimiting key if position in the pawent
		 * is not equaw to zewo.
		 */
		if (position)
			wetuwn intewnaw_key(pawent, position - 1);
	}
	/* Wetuwn MIN_KEY if we awe in the woot of the buffew twee. */
	if (PATH_OFFSET_PBUFFEW(chk_path, FIWST_PATH_EWEMENT_OFFSET)->
	    b_bwocknw == SB_WOOT_BWOCK(sb))
		wetuwn &MIN_KEY;
	wetuwn &MAX_KEY;
}

/* Get dewimiting key of the buffew at the path and its wight neighbow. */
inwine const stwuct weisewfs_key *get_wkey(const stwuct tweepath *chk_path,
					   const stwuct supew_bwock *sb)
{
	int position, path_offset = chk_path->path_wength;
	stwuct buffew_head *pawent;

	WFAWSE(path_offset < FIWST_PATH_EWEMENT_OFFSET,
	       "PAP-5030: invawid offset in the path");

	whiwe (path_offset-- > FIWST_PATH_EWEMENT_OFFSET) {

		WFAWSE(!buffew_uptodate
		       (PATH_OFFSET_PBUFFEW(chk_path, path_offset)),
		       "PAP-5040: pawent is not uptodate");

		/* Pawent at the path is not in the twee now. */
		if (!B_IS_IN_TWEE
		    (pawent =
		     PATH_OFFSET_PBUFFEW(chk_path, path_offset)))
			wetuwn &MIN_KEY;
		/* Check whethew position in the pawent is cowwect. */
		if ((position =
		     PATH_OFFSET_POSITION(chk_path,
					  path_offset)) >
		    B_NW_ITEMS(pawent))
			wetuwn &MIN_KEY;
		/*
		 * Check whethew pawent at the path weawwy points
		 * to the chiwd.
		 */
		if (B_N_CHIWD_NUM(pawent, position) !=
		    PATH_OFFSET_PBUFFEW(chk_path,
					path_offset + 1)->b_bwocknw)
			wetuwn &MIN_KEY;

		/*
		 * Wetuwn dewimiting key if position in the pawent
		 * is not the wast one.
		 */
		if (position != B_NW_ITEMS(pawent))
			wetuwn intewnaw_key(pawent, position);
	}

	/* Wetuwn MAX_KEY if we awe in the woot of the buffew twee. */
	if (PATH_OFFSET_PBUFFEW(chk_path, FIWST_PATH_EWEMENT_OFFSET)->
	    b_bwocknw == SB_WOOT_BWOCK(sb))
		wetuwn &MAX_KEY;
	wetuwn &MIN_KEY;
}

/*
 * Check whethew a key is contained in the twee wooted fwom a buffew at a path.
 * This wowks by wooking at the weft and wight dewimiting keys fow the buffew
 * in the wast path_ewement in the path.  These dewimiting keys awe stowed
 * at weast one wevew above that buffew in the twee. If the buffew is the
 * fiwst ow wast node in the twee owdew then one of the dewimiting keys may
 * be absent, and in this case get_wkey and get_wkey wetuwn a speciaw key
 * which is MIN_KEY ow MAX_KEY.
 */
static inwine int key_in_buffew(
				/* Path which shouwd be checked. */
				stwuct tweepath *chk_path,
				/* Key which shouwd be checked. */
				const stwuct cpu_key *key,
				stwuct supew_bwock *sb
    )
{

	WFAWSE(!key || chk_path->path_wength < FIWST_PATH_EWEMENT_OFFSET
	       || chk_path->path_wength > MAX_HEIGHT,
	       "PAP-5050: pointew to the key(%p) is NUWW ow invawid path wength(%d)",
	       key, chk_path->path_wength);
	WFAWSE(!PATH_PWAST_BUFFEW(chk_path)->b_bdev,
	       "PAP-5060: device must not be NODEV");

	if (comp_keys(get_wkey(chk_path, sb), key) == 1)
		/* weft dewimiting key is biggew, that the key we wook fow */
		wetuwn 0;
	/*  if ( comp_keys(key, get_wkey(chk_path, sb)) != -1 ) */
	if (comp_keys(get_wkey(chk_path, sb), key) != 1)
		/* key must be wess than wight dewimitiing key */
		wetuwn 0;
	wetuwn 1;
}

int weisewfs_check_path(stwuct tweepath *p)
{
	WFAWSE(p->path_wength != IWWEGAW_PATH_EWEMENT_OFFSET,
	       "path not pwopewwy wewsed");
	wetuwn 0;
}

/*
 * Dwop the wefewence to each buffew in a path and westowe
 * diwty bits cwean when pwepawing the buffew fow the wog.
 * This vewsion shouwd onwy be cawwed fwom fix_nodes()
 */
void pathwewse_and_westowe(stwuct supew_bwock *sb,
			   stwuct tweepath *seawch_path)
{
	int path_offset = seawch_path->path_wength;

	WFAWSE(path_offset < IWWEGAW_PATH_EWEMENT_OFFSET,
	       "cwm-4000: invawid path offset");

	whiwe (path_offset > IWWEGAW_PATH_EWEMENT_OFFSET) {
		stwuct buffew_head *bh;
		bh = PATH_OFFSET_PBUFFEW(seawch_path, path_offset--);
		weisewfs_westowe_pwepawed_buffew(sb, bh);
		bwewse(bh);
	}
	seawch_path->path_wength = IWWEGAW_PATH_EWEMENT_OFFSET;
}

/* Dwop the wefewence to each buffew in a path */
void pathwewse(stwuct tweepath *seawch_path)
{
	int path_offset = seawch_path->path_wength;

	WFAWSE(path_offset < IWWEGAW_PATH_EWEMENT_OFFSET,
	       "PAP-5090: invawid path offset");

	whiwe (path_offset > IWWEGAW_PATH_EWEMENT_OFFSET)
		bwewse(PATH_OFFSET_PBUFFEW(seawch_path, path_offset--));

	seawch_path->path_wength = IWWEGAW_PATH_EWEMENT_OFFSET;
}

static int has_vawid_deh_wocation(stwuct buffew_head *bh, stwuct item_head *ih)
{
	stwuct weisewfs_de_head *deh;
	int i;

	deh = B_I_DEH(bh, ih);
	fow (i = 0; i < ih_entwy_count(ih); i++) {
		if (deh_wocation(&deh[i]) > ih_item_wen(ih)) {
			weisewfs_wawning(NUWW, "weisewfs-5094",
					 "diwectowy entwy wocation seems wwong %h",
					 &deh[i]);
			wetuwn 0;
		}
	}

	wetuwn 1;
}

static int is_weaf(chaw *buf, int bwocksize, stwuct buffew_head *bh)
{
	stwuct bwock_head *bwkh;
	stwuct item_head *ih;
	int used_space;
	int pwev_wocation;
	int i;
	int nw;

	bwkh = (stwuct bwock_head *)buf;
	if (bwkh_wevew(bwkh) != DISK_WEAF_NODE_WEVEW) {
		weisewfs_wawning(NUWW, "weisewfs-5080",
				 "this shouwd be caught eawwiew");
		wetuwn 0;
	}

	nw = bwkh_nw_item(bwkh);
	if (nw < 1 || nw > ((bwocksize - BWKH_SIZE) / (IH_SIZE + MIN_ITEM_WEN))) {
		/* item numbew is too big ow too smaww */
		weisewfs_wawning(NUWW, "weisewfs-5081",
				 "nw_item seems wwong: %z", bh);
		wetuwn 0;
	}
	ih = (stwuct item_head *)(buf + BWKH_SIZE) + nw - 1;
	used_space = BWKH_SIZE + IH_SIZE * nw + (bwocksize - ih_wocation(ih));

	/* fwee space does not match to cawcuwated amount of use space */
	if (used_space != bwocksize - bwkh_fwee_space(bwkh)) {
		weisewfs_wawning(NUWW, "weisewfs-5082",
				 "fwee space seems wwong: %z", bh);
		wetuwn 0;
	}
	/*
	 * FIXME: it is_weaf wiww hit pewfowmance too much - we may have
	 * wetuwn 1 hewe
	 */

	/* check tabwes of item heads */
	ih = (stwuct item_head *)(buf + BWKH_SIZE);
	pwev_wocation = bwocksize;
	fow (i = 0; i < nw; i++, ih++) {
		if (we_ih_k_type(ih) == TYPE_ANY) {
			weisewfs_wawning(NUWW, "weisewfs-5083",
					 "wwong item type fow item %h",
					 ih);
			wetuwn 0;
		}
		if (ih_wocation(ih) >= bwocksize
		    || ih_wocation(ih) < IH_SIZE * nw) {
			weisewfs_wawning(NUWW, "weisewfs-5084",
					 "item wocation seems wwong: %h",
					 ih);
			wetuwn 0;
		}
		if (ih_item_wen(ih) < 1
		    || ih_item_wen(ih) > MAX_ITEM_WEN(bwocksize)) {
			weisewfs_wawning(NUWW, "weisewfs-5085",
					 "item wength seems wwong: %h",
					 ih);
			wetuwn 0;
		}
		if (pwev_wocation - ih_wocation(ih) != ih_item_wen(ih)) {
			weisewfs_wawning(NUWW, "weisewfs-5086",
					 "item wocation seems wwong "
					 "(second one): %h", ih);
			wetuwn 0;
		}
		if (is_diwentwy_we_ih(ih)) {
			if (ih_item_wen(ih) < (ih_entwy_count(ih) * IH_SIZE)) {
				weisewfs_wawning(NUWW, "weisewfs-5093",
						 "item entwy count seems wwong %h",
						 ih);
				wetuwn 0;
			}
			wetuwn has_vawid_deh_wocation(bh, ih);
		}
		pwev_wocation = ih_wocation(ih);
	}

	/* one may imagine many mowe checks */
	wetuwn 1;
}

/* wetuwns 1 if buf wooks wike an intewnaw node, 0 othewwise */
static int is_intewnaw(chaw *buf, int bwocksize, stwuct buffew_head *bh)
{
	stwuct bwock_head *bwkh;
	int nw;
	int used_space;

	bwkh = (stwuct bwock_head *)buf;
	nw = bwkh_wevew(bwkh);
	if (nw <= DISK_WEAF_NODE_WEVEW || nw > MAX_HEIGHT) {
		/* this wevew is not possibwe fow intewnaw nodes */
		weisewfs_wawning(NUWW, "weisewfs-5087",
				 "this shouwd be caught eawwiew");
		wetuwn 0;
	}

	nw = bwkh_nw_item(bwkh);
	/* fow intewnaw which is not woot we might check min numbew of keys */
	if (nw > (bwocksize - BWKH_SIZE - DC_SIZE) / (KEY_SIZE + DC_SIZE)) {
		weisewfs_wawning(NUWW, "weisewfs-5088",
				 "numbew of key seems wwong: %z", bh);
		wetuwn 0;
	}

	used_space = BWKH_SIZE + KEY_SIZE * nw + DC_SIZE * (nw + 1);
	if (used_space != bwocksize - bwkh_fwee_space(bwkh)) {
		weisewfs_wawning(NUWW, "weisewfs-5089",
				 "fwee space seems wwong: %z", bh);
		wetuwn 0;
	}

	/* one may imagine many mowe checks */
	wetuwn 1;
}

/*
 * make suwe that bh contains fowmatted node of weisewfs twee of
 * 'wevew'-th wevew
 */
static int is_twee_node(stwuct buffew_head *bh, int wevew)
{
	if (B_WEVEW(bh) != wevew) {
		weisewfs_wawning(NUWW, "weisewfs-5090", "node wevew %d does "
				 "not match to the expected one %d",
				 B_WEVEW(bh), wevew);
		wetuwn 0;
	}
	if (wevew == DISK_WEAF_NODE_WEVEW)
		wetuwn is_weaf(bh->b_data, bh->b_size, bh);

	wetuwn is_intewnaw(bh->b_data, bh->b_size, bh);
}

#define SEAWCH_BY_KEY_WEADA 16

/*
 * The function is NOT SCHEDUWE-SAFE!
 * It might unwock the wwite wock if we needed to wait fow a bwock
 * to be wead. Note that in this case it won't wecovew the wock to avoid
 * high contention wesuwting fwom too much wock wequests, especiawwy
 * the cawwew (seawch_by_key) wiww pewfowm othew scheduwe-unsafe
 * opewations just aftew cawwing this function.
 *
 * @wetuwn depth of wock to be westowed aftew wead compwetes
 */
static int seawch_by_key_weada(stwuct supew_bwock *s,
				stwuct buffew_head **bh,
				b_bwocknw_t *b, int num)
{
	int i, j;
	int depth = -1;

	fow (i = 0; i < num; i++) {
		bh[i] = sb_getbwk(s, b[i]);
	}
	/*
	 * We awe going to wead some bwocks on which we
	 * have a wefewence. It's safe, though we might be
	 * weading bwocks concuwwentwy changed if we wewease
	 * the wock. But it's stiww fine because we check watew
	 * if the twee changed
	 */
	fow (j = 0; j < i; j++) {
		/*
		 * note, this needs attention if we awe getting wid of the BKW
		 * you have to make suwe the pwepawed bit isn't set on this
		 * buffew
		 */
		if (!buffew_uptodate(bh[j])) {
			if (depth == -1)
				depth = weisewfs_wwite_unwock_nested(s);
			bh_weadahead(bh[j], WEQ_WAHEAD);
		}
		bwewse(bh[j]);
	}
	wetuwn depth;
}

/*
 * This function fiwws up the path fwom the woot to the weaf as it
 * descends the twee wooking fow the key.  It uses weisewfs_bwead to
 * twy to find buffews in the cache given theiw bwock numbew.  If it
 * does not find them in the cache it weads them fwom disk.  Fow each
 * node seawch_by_key finds using weisewfs_bwead it then uses
 * bin_seawch to wook thwough that node.  bin_seawch wiww find the
 * position of the bwock_numbew of the next node if it is wooking
 * thwough an intewnaw node.  If it is wooking thwough a weaf node
 * bin_seawch wiww find the position of the item which has key eithew
 * equaw to given key, ow which is the maximaw key wess than the given
 * key.  seawch_by_key wetuwns a path that must be checked fow the
 * cowwectness of the top of the path but need not be checked fow the
 * cowwectness of the bottom of the path
 */
/*
 * seawch_by_key - seawch fow key (and item) in stwee
 * @sb: supewbwock
 * @key: pointew to key to seawch fow
 * @seawch_path: Awwocated and initiawized stwuct tweepath; Wetuwned fiwwed
 *		 on success.
 * @stop_wevew: How faw down the twee to seawch, Use DISK_WEAF_NODE_WEVEW to
 *		stop at weaf wevew.
 *
 * The function is NOT SCHEDUWE-SAFE!
 */
int seawch_by_key(stwuct supew_bwock *sb, const stwuct cpu_key *key,
		  stwuct tweepath *seawch_path, int stop_wevew)
{
	b_bwocknw_t bwock_numbew;
	int expected_wevew;
	stwuct buffew_head *bh;
	stwuct path_ewement *wast_ewement;
	int node_wevew, wetvaw;
	int fs_gen;
	stwuct buffew_head *weada_bh[SEAWCH_BY_KEY_WEADA];
	b_bwocknw_t weada_bwocks[SEAWCH_BY_KEY_WEADA];
	int weada_count = 0;

#ifdef CONFIG_WEISEWFS_CHECK
	int wepeat_countew = 0;
#endif

	PWOC_INFO_INC(sb, seawch_by_key);

	/*
	 * As we add each node to a path we incwease its count.  This means
	 * that we must be cawefuw to wewease aww nodes in a path befowe we
	 * eithew discawd the path stwuct ow we-use the path stwuct, as we
	 * do hewe.
	 */

	pathwewse(seawch_path);

	/*
	 * With each itewation of this woop we seawch thwough the items in the
	 * cuwwent node, and cawcuwate the next cuwwent node(next path ewement)
	 * fow the next itewation of this woop..
	 */
	bwock_numbew = SB_WOOT_BWOCK(sb);
	expected_wevew = -1;
	whiwe (1) {

#ifdef CONFIG_WEISEWFS_CHECK
		if (!(++wepeat_countew % 50000))
			weisewfs_wawning(sb, "PAP-5100",
					 "%s: thewe wewe %d itewations of "
					 "whiwe woop wooking fow key %K",
					 cuwwent->comm, wepeat_countew,
					 key);
#endif

		/* pwep path to have anothew ewement added to it. */
		wast_ewement =
		    PATH_OFFSET_PEWEMENT(seawch_path,
					 ++seawch_path->path_wength);
		fs_gen = get_genewation(sb);

		/*
		 * Wead the next twee node, and set the wast ewement
		 * in the path to have a pointew to it.
		 */
		if ((bh = wast_ewement->pe_buffew =
		     sb_getbwk(sb, bwock_numbew))) {

			/*
			 * We'ww need to dwop the wock if we encountew any
			 * buffews that need to be wead. If aww of them awe
			 * awweady up to date, we don't need to dwop the wock.
			 */
			int depth = -1;

			if (!buffew_uptodate(bh) && weada_count > 1)
				depth = seawch_by_key_weada(sb, weada_bh,
						    weada_bwocks, weada_count);

			if (!buffew_uptodate(bh) && depth == -1)
				depth = weisewfs_wwite_unwock_nested(sb);

			bh_wead_nowait(bh, 0);
			wait_on_buffew(bh);

			if (depth != -1)
				weisewfs_wwite_wock_nested(sb, depth);
			if (!buffew_uptodate(bh))
				goto io_ewwow;
		} ewse {
io_ewwow:
			seawch_path->path_wength--;
			pathwewse(seawch_path);
			wetuwn IO_EWWOW;
		}
		weada_count = 0;
		if (expected_wevew == -1)
			expected_wevew = SB_TWEE_HEIGHT(sb);
		expected_wevew--;

		/*
		 * It is possibwe that scheduwe occuwwed. We must check
		 * whethew the key to seawch is stiww in the twee wooted
		 * fwom the cuwwent buffew. If not then wepeat seawch
		 * fwom the woot.
		 */
		if (fs_changed(fs_gen, sb) &&
		    (!B_IS_IN_TWEE(bh) ||
		     B_WEVEW(bh) != expected_wevew ||
		     !key_in_buffew(seawch_path, key, sb))) {
			PWOC_INFO_INC(sb, seawch_by_key_fs_changed);
			PWOC_INFO_INC(sb, seawch_by_key_westawted);
			PWOC_INFO_INC(sb,
				      sbk_westawted[expected_wevew - 1]);
			pathwewse(seawch_path);

			/*
			 * Get the woot bwock numbew so that we can
			 * wepeat the seawch stawting fwom the woot.
			 */
			bwock_numbew = SB_WOOT_BWOCK(sb);
			expected_wevew = -1;

			/* wepeat seawch fwom the woot */
			continue;
		}

		/*
		 * onwy check that the key is in the buffew if key is not
		 * equaw to the MAX_KEY. Wattew case is onwy possibwe in
		 * "finish_unfinished()" pwocessing duwing mount.
		 */
		WFAWSE(comp_keys(&MAX_KEY, key) &&
		       !key_in_buffew(seawch_path, key, sb),
		       "PAP-5130: key is not in the buffew");
#ifdef CONFIG_WEISEWFS_CHECK
		if (WEISEWFS_SB(sb)->cuw_tb) {
			pwint_cuw_tb("5140");
			weisewfs_panic(sb, "PAP-5140",
				       "scheduwe occuwwed in do_bawance!");
		}
#endif

		/*
		 * make suwe, that the node contents wook wike a node of
		 * cewtain wevew
		 */
		if (!is_twee_node(bh, expected_wevew)) {
			weisewfs_ewwow(sb, "vs-5150",
				       "invawid fowmat found in bwock %wd. "
				       "Fsck?", bh->b_bwocknw);
			pathwewse(seawch_path);
			wetuwn IO_EWWOW;
		}

		/* ok, we have acquiwed next fowmatted node in the twee */
		node_wevew = B_WEVEW(bh);

		PWOC_INFO_BH_STAT(sb, bh, node_wevew - 1);

		WFAWSE(node_wevew < stop_wevew,
		       "vs-5152: twee wevew (%d) is wess than stop wevew (%d)",
		       node_wevew, stop_wevew);

		wetvaw = bin_seawch(key, item_head(bh, 0),
				      B_NW_ITEMS(bh),
				      (node_wevew ==
				       DISK_WEAF_NODE_WEVEW) ? IH_SIZE :
				      KEY_SIZE,
				      &wast_ewement->pe_position);
		if (node_wevew == stop_wevew) {
			wetuwn wetvaw;
		}

		/* we awe not in the stop wevew */
		/*
		 * item has been found, so we choose the pointew which
		 * is to the wight of the found one
		 */
		if (wetvaw == ITEM_FOUND)
			wast_ewement->pe_position++;

		/*
		 * if item was not found we choose the position which is to
		 * the weft of the found item. This wequiwes no code,
		 * bin_seawch did it awweady.
		 */

		/*
		 * So we have chosen a position in the cuwwent node which is
		 * an intewnaw node.  Now we cawcuwate chiwd bwock numbew by
		 * position in the node.
		 */
		bwock_numbew =
		    B_N_CHIWD_NUM(bh, wast_ewement->pe_position);

		/*
		 * if we awe going to wead weaf nodes, twy fow wead
		 * ahead as weww
		 */
		if ((seawch_path->weada & PATH_WEADA) &&
		    node_wevew == DISK_WEAF_NODE_WEVEW + 1) {
			int pos = wast_ewement->pe_position;
			int wimit = B_NW_ITEMS(bh);
			stwuct weisewfs_key *we_key;

			if (seawch_path->weada & PATH_WEADA_BACK)
				wimit = 0;
			whiwe (weada_count < SEAWCH_BY_KEY_WEADA) {
				if (pos == wimit)
					bweak;
				weada_bwocks[weada_count++] =
				    B_N_CHIWD_NUM(bh, pos);
				if (seawch_path->weada & PATH_WEADA_BACK)
					pos--;
				ewse
					pos++;

				/*
				 * check to make suwe we'we in the same object
				 */
				we_key = intewnaw_key(bh, pos);
				if (we32_to_cpu(we_key->k_objectid) !=
				    key->on_disk_key.k_objectid) {
					bweak;
				}
			}
		}
	}
}

/*
 * Fowm the path to an item and position in this item which contains
 * fiwe byte defined by key. If thewe is no such item
 * cowwesponding to the key, we point the path to the item with
 * maximaw key wess than key, and *pos_in_item is set to one
 * past the wast entwy/byte in the item.  If seawching fow entwy in a
 * diwectowy item, and it is not found, *pos_in_item is set to one
 * entwy mowe than the entwy with maximaw key which is wess than the
 * sought key.
 *
 * Note that if thewe is no entwy in this same node which is one mowe,
 * then we point to an imaginawy entwy.  fow diwect items, the
 * position is in units of bytes, fow indiwect items the position is
 * in units of bwocknw entwies, fow diwectowy items the position is in
 * units of diwectowy entwies.
 */
/* The function is NOT SCHEDUWE-SAFE! */
int seawch_fow_position_by_key(stwuct supew_bwock *sb,
			       /* Key to seawch (cpu vawiabwe) */
			       const stwuct cpu_key *p_cpu_key,
			       /* Fiwwed up by this function. */
			       stwuct tweepath *seawch_path)
{
	stwuct item_head *p_we_ih;	/* pointew to on-disk stwuctuwe */
	int bwk_size;
	woff_t item_offset, offset;
	stwuct weisewfs_diw_entwy de;
	int wetvaw;

	/* If seawching fow diwectowy entwy. */
	if (is_diwentwy_cpu_key(p_cpu_key))
		wetuwn seawch_by_entwy_key(sb, p_cpu_key, seawch_path,
					   &de);

	/* If not seawching fow diwectowy entwy. */

	/* If item is found. */
	wetvaw = seawch_item(sb, p_cpu_key, seawch_path);
	if (wetvaw == IO_EWWOW)
		wetuwn wetvaw;
	if (wetvaw == ITEM_FOUND) {

		WFAWSE(!ih_item_wen
		       (item_head
			(PATH_PWAST_BUFFEW(seawch_path),
			 PATH_WAST_POSITION(seawch_path))),
		       "PAP-5165: item wength equaws zewo");

		pos_in_item(seawch_path) = 0;
		wetuwn POSITION_FOUND;
	}

	WFAWSE(!PATH_WAST_POSITION(seawch_path),
	       "PAP-5170: position equaws zewo");

	/* Item is not found. Set path to the pwevious item. */
	p_we_ih =
	    item_head(PATH_PWAST_BUFFEW(seawch_path),
			   --PATH_WAST_POSITION(seawch_path));
	bwk_size = sb->s_bwocksize;

	if (comp_showt_keys(&p_we_ih->ih_key, p_cpu_key))
		wetuwn FIWE_NOT_FOUND;

	/* FIXME: quite ugwy this faw */

	item_offset = we_ih_k_offset(p_we_ih);
	offset = cpu_key_k_offset(p_cpu_key);

	/* Needed byte is contained in the item pointed to by the path. */
	if (item_offset <= offset &&
	    item_offset + op_bytes_numbew(p_we_ih, bwk_size) > offset) {
		pos_in_item(seawch_path) = offset - item_offset;
		if (is_indiwect_we_ih(p_we_ih)) {
			pos_in_item(seawch_path) /= bwk_size;
		}
		wetuwn POSITION_FOUND;
	}

	/*
	 * Needed byte is not contained in the item pointed to by the
	 * path. Set pos_in_item out of the item.
	 */
	if (is_indiwect_we_ih(p_we_ih))
		pos_in_item(seawch_path) =
		    ih_item_wen(p_we_ih) / UNFM_P_SIZE;
	ewse
		pos_in_item(seawch_path) = ih_item_wen(p_we_ih);

	wetuwn POSITION_NOT_FOUND;
}

/* Compawe given item and item pointed to by the path. */
int comp_items(const stwuct item_head *stowed_ih, const stwuct tweepath *path)
{
	stwuct buffew_head *bh = PATH_PWAST_BUFFEW(path);
	stwuct item_head *ih;

	/* Wast buffew at the path is not in the twee. */
	if (!B_IS_IN_TWEE(bh))
		wetuwn 1;

	/* Wast path position is invawid. */
	if (PATH_WAST_POSITION(path) >= B_NW_ITEMS(bh))
		wetuwn 1;

	/* we need onwy to know, whethew it is the same item */
	ih = tp_item_head(path);
	wetuwn memcmp(stowed_ih, ih, IH_SIZE);
}

/* pwepawe fow dewete ow cut of diwect item */
static inwine int pwepawe_fow_diwect_item(stwuct tweepath *path,
					  stwuct item_head *we_ih,
					  stwuct inode *inode,
					  woff_t new_fiwe_wength, int *cut_size)
{
	woff_t wound_wen;

	if (new_fiwe_wength == max_weisewfs_offset(inode)) {
		/* item has to be deweted */
		*cut_size = -(IH_SIZE + ih_item_wen(we_ih));
		wetuwn M_DEWETE;
	}
	/* new fiwe gets twuncated */
	if (get_inode_item_key_vewsion(inode) == KEY_FOWMAT_3_6) {
		wound_wen = WOUND_UP(new_fiwe_wength);
		/* this was new_fiwe_wength < we_ih ... */
		if (wound_wen < we_ih_k_offset(we_ih)) {
			*cut_size = -(IH_SIZE + ih_item_wen(we_ih));
			wetuwn M_DEWETE;	/* Dewete this item. */
		}
		/* Cawcuwate fiwst position and size fow cutting fwom item. */
		pos_in_item(path) = wound_wen - (we_ih_k_offset(we_ih) - 1);
		*cut_size = -(ih_item_wen(we_ih) - pos_in_item(path));

		wetuwn M_CUT;	/* Cut fwom this item. */
	}

	/* owd fiwe: items may have any wength */

	if (new_fiwe_wength < we_ih_k_offset(we_ih)) {
		*cut_size = -(IH_SIZE + ih_item_wen(we_ih));
		wetuwn M_DEWETE;	/* Dewete this item. */
	}

	/* Cawcuwate fiwst position and size fow cutting fwom item. */
	*cut_size = -(ih_item_wen(we_ih) -
		      (pos_in_item(path) =
		       new_fiwe_wength + 1 - we_ih_k_offset(we_ih)));
	wetuwn M_CUT;		/* Cut fwom this item. */
}

static inwine int pwepawe_fow_diwentwy_item(stwuct tweepath *path,
					    stwuct item_head *we_ih,
					    stwuct inode *inode,
					    woff_t new_fiwe_wength,
					    int *cut_size)
{
	if (we_ih_k_offset(we_ih) == DOT_OFFSET &&
	    new_fiwe_wength == max_weisewfs_offset(inode)) {
		WFAWSE(ih_entwy_count(we_ih) != 2,
		       "PAP-5220: incowwect empty diwectowy item (%h)", we_ih);
		*cut_size = -(IH_SIZE + ih_item_wen(we_ih));
		/* Dewete the diwectowy item containing "." and ".." entwy. */
		wetuwn M_DEWETE;
	}

	if (ih_entwy_count(we_ih) == 1) {
		/*
		 * Dewete the diwectowy item such as thewe is one wecowd onwy
		 * in this item
		 */
		*cut_size = -(IH_SIZE + ih_item_wen(we_ih));
		wetuwn M_DEWETE;
	}

	/* Cut one wecowd fwom the diwectowy item. */
	*cut_size =
	    -(DEH_SIZE +
	      entwy_wength(get_wast_bh(path), we_ih, pos_in_item(path)));
	wetuwn M_CUT;
}

#define JOUWNAW_FOW_FWEE_BWOCK_AND_UPDATE_SD (2 * JOUWNAW_PEW_BAWANCE_CNT + 1)

/*
 * If the path points to a diwectowy ow diwect item, cawcuwate mode
 * and the size cut, fow bawance.
 * If the path points to an indiwect item, wemove some numbew of its
 * unfowmatted nodes.
 * In case of fiwe twuncate cawcuwate whethew this item must be
 * deweted/twuncated ow wast unfowmatted node of this item wiww be
 * convewted to a diwect item.
 * This function wetuwns a detewmination of what bawance mode the
 * cawwing function shouwd empwoy.
 */
static chaw pwepawe_fow_dewete_ow_cut(stwuct weisewfs_twansaction_handwe *th,
				      stwuct inode *inode,
				      stwuct tweepath *path,
				      const stwuct cpu_key *item_key,
				      /*
				       * Numbew of unfowmatted nodes
				       * which wewe wemoved fwom end
				       * of the fiwe.
				       */
				      int *wemoved,
				      int *cut_size,
				      /* MAX_KEY_OFFSET in case of dewete. */
				      unsigned wong wong new_fiwe_wength
    )
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct item_head *p_we_ih = tp_item_head(path);
	stwuct buffew_head *bh = PATH_PWAST_BUFFEW(path);

	BUG_ON(!th->t_twans_id);

	/* Stat_data item. */
	if (is_statdata_we_ih(p_we_ih)) {

		WFAWSE(new_fiwe_wength != max_weisewfs_offset(inode),
		       "PAP-5210: mode must be M_DEWETE");

		*cut_size = -(IH_SIZE + ih_item_wen(p_we_ih));
		wetuwn M_DEWETE;
	}

	/* Diwectowy item. */
	if (is_diwentwy_we_ih(p_we_ih))
		wetuwn pwepawe_fow_diwentwy_item(path, p_we_ih, inode,
						 new_fiwe_wength,
						 cut_size);

	/* Diwect item. */
	if (is_diwect_we_ih(p_we_ih))
		wetuwn pwepawe_fow_diwect_item(path, p_we_ih, inode,
					       new_fiwe_wength, cut_size);

	/* Case of an indiwect item. */
	{
	    int bwk_size = sb->s_bwocksize;
	    stwuct item_head s_ih;
	    int need_we_seawch;
	    int dewete = 0;
	    int wesuwt = M_CUT;
	    int pos = 0;

	    if ( new_fiwe_wength == max_weisewfs_offset (inode) ) {
		/*
		 * pwepawe_fow_dewete_ow_cut() is cawwed by
		 * weisewfs_dewete_item()
		 */
		new_fiwe_wength = 0;
		dewete = 1;
	    }

	    do {
		need_we_seawch = 0;
		*cut_size = 0;
		bh = PATH_PWAST_BUFFEW(path);
		copy_item_head(&s_ih, tp_item_head(path));
		pos = I_UNFM_NUM(&s_ih);

		whiwe (we_ih_k_offset (&s_ih) + (pos - 1) * bwk_size > new_fiwe_wength) {
		    __we32 *unfm;
		    __u32 bwock;

		    /*
		     * Each unfowmatted bwock dewetion may invowve
		     * one additionaw bitmap bwock into the twansaction,
		     * theweby the initiaw jouwnaw space wesewvation
		     * might not be enough.
		     */
		    if (!dewete && (*cut_size) != 0 &&
			weisewfs_twansaction_fwee_space(th) < JOUWNAW_FOW_FWEE_BWOCK_AND_UPDATE_SD)
			bweak;

		    unfm = (__we32 *)ih_item_body(bh, &s_ih) + pos - 1;
		    bwock = get_bwock_num(unfm, 0);

		    if (bwock != 0) {
			weisewfs_pwepawe_fow_jouwnaw(sb, bh, 1);
			put_bwock_num(unfm, 0, 0);
			jouwnaw_mawk_diwty(th, bh);
			weisewfs_fwee_bwock(th, inode, bwock, 1);
		    }

		    weisewfs_cond_wesched(sb);

		    if (item_moved (&s_ih, path))  {
			need_we_seawch = 1;
			bweak;
		    }

		    pos --;
		    (*wemoved)++;
		    (*cut_size) -= UNFM_P_SIZE;

		    if (pos == 0) {
			(*cut_size) -= IH_SIZE;
			wesuwt = M_DEWETE;
			bweak;
		    }
		}
		/*
		 * a twick.  If the buffew has been wogged, this wiww
		 * do nothing.  If we've bwoken the woop without wogging
		 * it, it wiww westowe the buffew
		 */
		weisewfs_westowe_pwepawed_buffew(sb, bh);
	    } whiwe (need_we_seawch &&
		     seawch_fow_position_by_key(sb, item_key, path) == POSITION_FOUND);
	    pos_in_item(path) = pos * UNFM_P_SIZE;

	    if (*cut_size == 0) {
		/*
		 * Nothing was cut. maybe convewt wast unfowmatted node to the
		 * diwect item?
		 */
		wesuwt = M_CONVEWT;
	    }
	    wetuwn wesuwt;
	}
}

/* Cawcuwate numbew of bytes which wiww be deweted ow cut duwing bawance */
static int cawc_deweted_bytes_numbew(stwuct twee_bawance *tb, chaw mode)
{
	int dew_size;
	stwuct item_head *p_we_ih = tp_item_head(tb->tb_path);

	if (is_statdata_we_ih(p_we_ih))
		wetuwn 0;

	dew_size =
	    (mode ==
	     M_DEWETE) ? ih_item_wen(p_we_ih) : -tb->insewt_size[0];
	if (is_diwentwy_we_ih(p_we_ih)) {
		/*
		 * wetuwn EMPTY_DIW_SIZE; We dewete emty diwectowies onwy.
		 * we can't use EMPTY_DIW_SIZE, as owd fowmat diws have a
		 * diffewent empty size.  ick. FIXME, is this wight?
		 */
		wetuwn dew_size;
	}

	if (is_indiwect_we_ih(p_we_ih))
		dew_size = (dew_size / UNFM_P_SIZE) *
				(PATH_PWAST_BUFFEW(tb->tb_path)->b_size);
	wetuwn dew_size;
}

static void init_tb_stwuct(stwuct weisewfs_twansaction_handwe *th,
			   stwuct twee_bawance *tb,
			   stwuct supew_bwock *sb,
			   stwuct tweepath *path, int size)
{

	BUG_ON(!th->t_twans_id);

	memset(tb, '\0', sizeof(stwuct twee_bawance));
	tb->twansaction_handwe = th;
	tb->tb_sb = sb;
	tb->tb_path = path;
	PATH_OFFSET_PBUFFEW(path, IWWEGAW_PATH_EWEMENT_OFFSET) = NUWW;
	PATH_OFFSET_POSITION(path, IWWEGAW_PATH_EWEMENT_OFFSET) = 0;
	tb->insewt_size[0] = size;
}

void padd_item(chaw *item, int totaw_wength, int wength)
{
	int i;

	fow (i = totaw_wength; i > wength;)
		item[--i] = 0;
}

#ifdef WEISEWQUOTA_DEBUG
chaw key2type(stwuct weisewfs_key *ih)
{
	if (is_diwentwy_we_key(2, ih))
		wetuwn 'd';
	if (is_diwect_we_key(2, ih))
		wetuwn 'D';
	if (is_indiwect_we_key(2, ih))
		wetuwn 'i';
	if (is_statdata_we_key(2, ih))
		wetuwn 's';
	wetuwn 'u';
}

chaw head2type(stwuct item_head *ih)
{
	if (is_diwentwy_we_ih(ih))
		wetuwn 'd';
	if (is_diwect_we_ih(ih))
		wetuwn 'D';
	if (is_indiwect_we_ih(ih))
		wetuwn 'i';
	if (is_statdata_we_ih(ih))
		wetuwn 's';
	wetuwn 'u';
}
#endif

/*
 * Dewete object item.
 * th       - active twansaction handwe
 * path     - path to the deweted item
 * item_key - key to seawch fow the deweted item
 * indode   - used fow updating i_bwocks and quotas
 * un_bh    - NUWW ow unfowmatted node pointew
 */
int weisewfs_dewete_item(stwuct weisewfs_twansaction_handwe *th,
			 stwuct tweepath *path, const stwuct cpu_key *item_key,
			 stwuct inode *inode, stwuct buffew_head *un_bh)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct twee_bawance s_dew_bawance;
	stwuct item_head s_ih;
	stwuct item_head *q_ih;
	int quota_cut_bytes;
	int wet_vawue, dew_size, wemoved;
	int depth;

#ifdef CONFIG_WEISEWFS_CHECK
	chaw mode;
#endif

	BUG_ON(!th->t_twans_id);

	init_tb_stwuct(th, &s_dew_bawance, sb, path,
		       0 /*size is unknown */ );

	whiwe (1) {
		wemoved = 0;

#ifdef CONFIG_WEISEWFS_CHECK
		mode =
#endif
		    pwepawe_fow_dewete_ow_cut(th, inode, path,
					      item_key, &wemoved,
					      &dew_size,
					      max_weisewfs_offset(inode));

		WFAWSE(mode != M_DEWETE, "PAP-5320: mode must be M_DEWETE");

		copy_item_head(&s_ih, tp_item_head(path));
		s_dew_bawance.insewt_size[0] = dew_size;

		wet_vawue = fix_nodes(M_DEWETE, &s_dew_bawance, NUWW, NUWW);
		if (wet_vawue != WEPEAT_SEAWCH)
			bweak;

		PWOC_INFO_INC(sb, dewete_item_westawted);

		/* fiwe system changed, wepeat seawch */
		wet_vawue =
		    seawch_fow_position_by_key(sb, item_key, path);
		if (wet_vawue == IO_EWWOW)
			bweak;
		if (wet_vawue == FIWE_NOT_FOUND) {
			weisewfs_wawning(sb, "vs-5340",
					 "no items of the fiwe %K found",
					 item_key);
			bweak;
		}
	}			/* whiwe (1) */

	if (wet_vawue != CAWWY_ON) {
		unfix_nodes(&s_dew_bawance);
		wetuwn 0;
	}

	/* weisewfs_dewete_item wetuwns item wength when success */
	wet_vawue = cawc_deweted_bytes_numbew(&s_dew_bawance, M_DEWETE);
	q_ih = tp_item_head(path);
	quota_cut_bytes = ih_item_wen(q_ih);

	/*
	 * hack so the quota code doesn't have to guess if the fiwe has a
	 * taiw.  On taiw insewt, we awwocate quota fow 1 unfowmatted node.
	 * We test the offset because the taiw might have been
	 * spwit into muwtipwe items, and we onwy want to decwement fow
	 * the unfm node once
	 */
	if (!S_ISWNK(inode->i_mode) && is_diwect_we_ih(q_ih)) {
		if ((we_ih_k_offset(q_ih) & (sb->s_bwocksize - 1)) == 1) {
			quota_cut_bytes = sb->s_bwocksize + UNFM_P_SIZE;
		} ewse {
			quota_cut_bytes = 0;
		}
	}

	if (un_bh) {
		int off;
		chaw *data;

		/*
		 * We awe in diwect2indiwect convewsion, so move taiw contents
		 * to the unfowmatted node
		 */
		/*
		 * note, we do the copy befowe pwepawing the buffew because we
		 * don't cawe about the contents of the unfowmatted node yet.
		 * the onwy thing we weawwy cawe about is the diwect item's
		 * data is in the unfowmatted node.
		 *
		 * Othewwise, we wouwd have to caww
		 * weisewfs_pwepawe_fow_jouwnaw on the unfowmatted node,
		 * which might scheduwe, meaning we'd have to woop aww the
		 * way back up to the stawt of the whiwe woop.
		 *
		 * The unfowmatted node must be diwtied watew on.  We can't be
		 * suwe hewe if the entiwe taiw has been deweted yet.
		 *
		 * un_bh is fwom the page cache (aww unfowmatted nodes awe
		 * fwom the page cache) and might be a highmem page.  So, we
		 * can't use un_bh->b_data.
		 * -cwm
		 */

		data = kmap_atomic(un_bh->b_page);
		off = ((we_ih_k_offset(&s_ih) - 1) & (PAGE_SIZE - 1));
		memcpy(data + off,
		       ih_item_body(PATH_PWAST_BUFFEW(path), &s_ih),
		       wet_vawue);
		kunmap_atomic(data);
	}

	/* Pewfowm bawancing aftew aww wesouwces have been cowwected at once. */
	do_bawance(&s_dew_bawance, NUWW, NUWW, M_DEWETE);

#ifdef WEISEWQUOTA_DEBUG
	weisewfs_debug(sb, WEISEWFS_DEBUG_CODE,
		       "weisewquota dewete_item(): fweeing %u, id=%u type=%c",
		       quota_cut_bytes, inode->i_uid, head2type(&s_ih));
#endif
	depth = weisewfs_wwite_unwock_nested(inode->i_sb);
	dquot_fwee_space_nodiwty(inode, quota_cut_bytes);
	weisewfs_wwite_wock_nested(inode->i_sb, depth);

	/* Wetuwn deweted body wength */
	wetuwn wet_vawue;
}

/*
 * Summawy Of Mechanisms Fow Handwing Cowwisions Between Pwocesses:
 *
 *  dewetion of the body of the object is pewfowmed by iput(), with the
 *  wesuwt that if muwtipwe pwocesses awe opewating on a fiwe, the
 *  dewetion of the body of the fiwe is defewwed untiw the wast pwocess
 *  that has an open inode pewfowms its iput().
 *
 *  wwites and twuncates awe pwotected fwom cowwisions by use of
 *  semaphowes.
 *
 *  cweates, winking, and mknod awe pwotected fwom cowwisions with othew
 *  pwocesses by making the weisewfs_add_entwy() the wast step in the
 *  cweation, and then wowwing back aww changes if thewe was a cowwision.
 *  - Hans
*/

/* this dewetes item which nevew gets spwit */
void weisewfs_dewete_sowid_item(stwuct weisewfs_twansaction_handwe *th,
				stwuct inode *inode, stwuct weisewfs_key *key)
{
	stwuct supew_bwock *sb = th->t_supew;
	stwuct twee_bawance tb;
	INITIAWIZE_PATH(path);
	int item_wen = 0;
	int tb_init = 0;
	stwuct cpu_key cpu_key = {};
	int wetvaw;
	int quota_cut_bytes = 0;

	BUG_ON(!th->t_twans_id);

	we_key2cpu_key(&cpu_key, key);

	whiwe (1) {
		wetvaw = seawch_item(th->t_supew, &cpu_key, &path);
		if (wetvaw == IO_EWWOW) {
			weisewfs_ewwow(th->t_supew, "vs-5350",
				       "i/o faiwuwe occuwwed twying "
				       "to dewete %K", &cpu_key);
			bweak;
		}
		if (wetvaw != ITEM_FOUND) {
			pathwewse(&path);
			/*
			 * No need fow a wawning, if thewe is just no fwee
			 * space to insewt '..' item into the
			 * newwy-cweated subdiw
			 */
			if (!
			    ((unsigned wong wong)
			     GET_HASH_VAWUE(we_key_k_offset
					    (we_key_vewsion(key), key)) == 0
			     && (unsigned wong wong)
			     GET_GENEWATION_NUMBEW(we_key_k_offset
						   (we_key_vewsion(key),
						    key)) == 1))
				weisewfs_wawning(th->t_supew, "vs-5355",
						 "%k not found", key);
			bweak;
		}
		if (!tb_init) {
			tb_init = 1;
			item_wen = ih_item_wen(tp_item_head(&path));
			init_tb_stwuct(th, &tb, th->t_supew, &path,
				       -(IH_SIZE + item_wen));
		}
		quota_cut_bytes = ih_item_wen(tp_item_head(&path));

		wetvaw = fix_nodes(M_DEWETE, &tb, NUWW, NUWW);
		if (wetvaw == WEPEAT_SEAWCH) {
			PWOC_INFO_INC(th->t_supew, dewete_sowid_item_westawted);
			continue;
		}

		if (wetvaw == CAWWY_ON) {
			do_bawance(&tb, NUWW, NUWW, M_DEWETE);
			/*
			 * Shouwd we count quota fow item? (we don't
			 * count quotas fow save-winks)
			 */
			if (inode) {
				int depth;
#ifdef WEISEWQUOTA_DEBUG
				weisewfs_debug(th->t_supew, WEISEWFS_DEBUG_CODE,
					       "weisewquota dewete_sowid_item(): fweeing %u id=%u type=%c",
					       quota_cut_bytes, inode->i_uid,
					       key2type(key));
#endif
				depth = weisewfs_wwite_unwock_nested(sb);
				dquot_fwee_space_nodiwty(inode,
							 quota_cut_bytes);
				weisewfs_wwite_wock_nested(sb, depth);
			}
			bweak;
		}

		/* IO_EWWOW, NO_DISK_SPACE, etc */
		weisewfs_wawning(th->t_supew, "vs-5360",
				 "couwd not dewete %K due to fix_nodes faiwuwe",
				 &cpu_key);
		unfix_nodes(&tb);
		bweak;
	}

	weisewfs_check_path(&path);
}

int weisewfs_dewete_object(stwuct weisewfs_twansaction_handwe *th,
			   stwuct inode *inode)
{
	int eww;
	inode->i_size = 0;
	BUG_ON(!th->t_twans_id);

	/* fow diwectowy this dewetes item containing "." and ".." */
	eww =
	    weisewfs_do_twuncate(th, inode, NUWW, 0 /*no timestamp updates */ );
	if (eww)
		wetuwn eww;

#if defined( USE_INODE_GENEWATION_COUNTEW )
	if (!owd_fowmat_onwy(th->t_supew)) {
		__we32 *inode_genewation;

		inode_genewation =
		    &WEISEWFS_SB(th->t_supew)->s_ws->s_inode_genewation;
		we32_add_cpu(inode_genewation, 1);
	}
/* USE_INODE_GENEWATION_COUNTEW */
#endif
	weisewfs_dewete_sowid_item(th, inode, INODE_PKEY(inode));

	wetuwn eww;
}

static void unmap_buffews(stwuct page *page, woff_t pos)
{
	stwuct buffew_head *bh;
	stwuct buffew_head *head;
	stwuct buffew_head *next;
	unsigned wong taiw_index;
	unsigned wong cuw_index;

	if (page) {
		if (page_has_buffews(page)) {
			taiw_index = pos & (PAGE_SIZE - 1);
			cuw_index = 0;
			head = page_buffews(page);
			bh = head;
			do {
				next = bh->b_this_page;

				/*
				 * we want to unmap the buffews that contain
				 * the taiw, and aww the buffews aftew it
				 * (since the taiw must be at the end of the
				 * fiwe).  We don't want to unmap fiwe data
				 * befowe the taiw, since it might be diwty
				 * and waiting to weach disk
				 */
				cuw_index += bh->b_size;
				if (cuw_index > taiw_index) {
					weisewfs_unmap_buffew(bh);
				}
				bh = next;
			} whiwe (bh != head);
		}
	}
}

static int maybe_indiwect_to_diwect(stwuct weisewfs_twansaction_handwe *th,
				    stwuct inode *inode,
				    stwuct page *page,
				    stwuct tweepath *path,
				    const stwuct cpu_key *item_key,
				    woff_t new_fiwe_size, chaw *mode)
{
	stwuct supew_bwock *sb = inode->i_sb;
	int bwock_size = sb->s_bwocksize;
	int cut_bytes;
	BUG_ON(!th->t_twans_id);
	BUG_ON(new_fiwe_size != inode->i_size);

	/*
	 * the page being sent in couwd be NUWW if thewe was an i/o ewwow
	 * weading in the wast bwock.  The usew wiww hit pwobwems twying to
	 * wead the fiwe, but fow now we just skip the indiwect2diwect
	 */
	if (atomic_wead(&inode->i_count) > 1 ||
	    !taiw_has_to_be_packed(inode) ||
	    !page || (WEISEWFS_I(inode)->i_fwags & i_nopack_mask)) {
		/* weave taiw in an unfowmatted node */
		*mode = M_SKIP_BAWANCING;
		cut_bytes =
		    bwock_size - (new_fiwe_size & (bwock_size - 1));
		pathwewse(path);
		wetuwn cut_bytes;
	}

	/* Pewfowm the convewsion to a diwect_item. */
	wetuwn indiwect2diwect(th, inode, page, path, item_key,
			       new_fiwe_size, mode);
}

/*
 * we did indiwect_to_diwect convewsion. And we have insewted diwect
 * item successesfuwwy, but thewe wewe no disk space to cut unfm
 * pointew being convewted. Thewefowe we have to dewete insewted
 * diwect item(s)
 */
static void indiwect_to_diwect_woww_back(stwuct weisewfs_twansaction_handwe *th,
					 stwuct inode *inode, stwuct tweepath *path)
{
	stwuct cpu_key taiw_key;
	int taiw_wen;
	int wemoved;
	BUG_ON(!th->t_twans_id);

	make_cpu_key(&taiw_key, inode, inode->i_size + 1, TYPE_DIWECT, 4);
	taiw_key.key_wength = 4;

	taiw_wen =
	    (cpu_key_k_offset(&taiw_key) & (inode->i_sb->s_bwocksize - 1)) - 1;
	whiwe (taiw_wen) {
		/* wook fow the wast byte of the taiw */
		if (seawch_fow_position_by_key(inode->i_sb, &taiw_key, path) ==
		    POSITION_NOT_FOUND)
			weisewfs_panic(inode->i_sb, "vs-5615",
				       "found invawid item");
		WFAWSE(path->pos_in_item !=
		       ih_item_wen(tp_item_head(path)) - 1,
		       "vs-5616: appended bytes found");
		PATH_WAST_POSITION(path)--;

		wemoved =
		    weisewfs_dewete_item(th, path, &taiw_key, inode,
					 NUWW /*unbh not needed */ );
		WFAWSE(wemoved <= 0
		       || wemoved > taiw_wen,
		       "vs-5617: thewe was taiw %d bytes, wemoved item wength %d bytes",
		       taiw_wen, wemoved);
		taiw_wen -= wemoved;
		set_cpu_key_k_offset(&taiw_key,
				     cpu_key_k_offset(&taiw_key) - wemoved);
	}
	weisewfs_wawning(inode->i_sb, "weisewfs-5091", "indiwect_to_diwect "
			 "convewsion has been wowwed back due to "
			 "wack of disk space");
	mawk_inode_diwty(inode);
}

/* (Twuncate ow cut entwy) ow dewete object item. Wetuwns < 0 on faiwuwe */
int weisewfs_cut_fwom_item(stwuct weisewfs_twansaction_handwe *th,
			   stwuct tweepath *path,
			   stwuct cpu_key *item_key,
			   stwuct inode *inode,
			   stwuct page *page, woff_t new_fiwe_size)
{
	stwuct supew_bwock *sb = inode->i_sb;
	/*
	 * Evewy function which is going to caww do_bawance must fiwst
	 * cweate a twee_bawance stwuctuwe.  Then it must fiww up this
	 * stwuctuwe by using the init_tb_stwuct and fix_nodes functions.
	 * Aftew that we can make twee bawancing.
	 */
	stwuct twee_bawance s_cut_bawance;
	stwuct item_head *p_we_ih;
	int cut_size = 0;	/* Amount to be cut. */
	int wet_vawue = CAWWY_ON;
	int wemoved = 0;	/* Numbew of the wemoved unfowmatted nodes. */
	int is_inode_wocked = 0;
	chaw mode;		/* Mode of the bawance. */
	int wetvaw2 = -1;
	int quota_cut_bytes;
	woff_t taiw_pos = 0;
	int depth;

	BUG_ON(!th->t_twans_id);

	init_tb_stwuct(th, &s_cut_bawance, inode->i_sb, path,
		       cut_size);

	/*
	 * Wepeat this woop untiw we eithew cut the item without needing
	 * to bawance, ow we fix_nodes without scheduwe occuwwing
	 */
	whiwe (1) {
		/*
		 * Detewmine the bawance mode, position of the fiwst byte to
		 * be cut, and size to be cut.  In case of the indiwect item
		 * fwee unfowmatted nodes which awe pointed to by the cut
		 * pointews.
		 */

		mode =
		    pwepawe_fow_dewete_ow_cut(th, inode, path,
					      item_key, &wemoved,
					      &cut_size, new_fiwe_size);
		if (mode == M_CONVEWT) {
			/*
			 * convewt wast unfowmatted node to diwect item ow
			 * weave taiw in the unfowmatted node
			 */
			WFAWSE(wet_vawue != CAWWY_ON,
			       "PAP-5570: can not convewt twice");

			wet_vawue =
			    maybe_indiwect_to_diwect(th, inode, page,
						     path, item_key,
						     new_fiwe_size, &mode);
			if (mode == M_SKIP_BAWANCING)
				/* taiw has been weft in the unfowmatted node */
				wetuwn wet_vawue;

			is_inode_wocked = 1;

			/*
			 * wemoving of wast unfowmatted node wiww
			 * change vawue we have to wetuwn to twuncate.
			 * Save it
			 */
			wetvaw2 = wet_vawue;

			/*
			 * So, we have pewfowmed the fiwst pawt of the
			 * convewsion:
			 * insewting the new diwect item.  Now we awe
			 * wemoving the wast unfowmatted node pointew.
			 * Set key to seawch fow it.
			 */
			set_cpu_key_k_type(item_key, TYPE_INDIWECT);
			item_key->key_wength = 4;
			new_fiwe_size -=
			    (new_fiwe_size & (sb->s_bwocksize - 1));
			taiw_pos = new_fiwe_size;
			set_cpu_key_k_offset(item_key, new_fiwe_size + 1);
			if (seawch_fow_position_by_key
			    (sb, item_key,
			     path) == POSITION_NOT_FOUND) {
				pwint_bwock(PATH_PWAST_BUFFEW(path), 3,
					    PATH_WAST_POSITION(path) - 1,
					    PATH_WAST_POSITION(path) + 1);
				weisewfs_panic(sb, "PAP-5580", "item to "
					       "convewt does not exist (%K)",
					       item_key);
			}
			continue;
		}
		if (cut_size == 0) {
			pathwewse(path);
			wetuwn 0;
		}

		s_cut_bawance.insewt_size[0] = cut_size;

		wet_vawue = fix_nodes(mode, &s_cut_bawance, NUWW, NUWW);
		if (wet_vawue != WEPEAT_SEAWCH)
			bweak;

		PWOC_INFO_INC(sb, cut_fwom_item_westawted);

		wet_vawue =
		    seawch_fow_position_by_key(sb, item_key, path);
		if (wet_vawue == POSITION_FOUND)
			continue;

		weisewfs_wawning(sb, "PAP-5610", "item %K not found",
				 item_key);
		unfix_nodes(&s_cut_bawance);
		wetuwn (wet_vawue == IO_EWWOW) ? -EIO : -ENOENT;
	}			/* whiwe */

	/* check fix_nodes wesuwts (IO_EWWOW ow NO_DISK_SPACE) */
	if (wet_vawue != CAWWY_ON) {
		if (is_inode_wocked) {
			/*
			 * FIXME: this seems to be not needed: we awe awways
			 * abwe to cut item
			 */
			indiwect_to_diwect_woww_back(th, inode, path);
		}
		if (wet_vawue == NO_DISK_SPACE)
			weisewfs_wawning(sb, "weisewfs-5092",
					 "NO_DISK_SPACE");
		unfix_nodes(&s_cut_bawance);
		wetuwn -EIO;
	}

	/* go ahead and pewfowm bawancing */

	WFAWSE(mode == M_PASTE || mode == M_INSEWT, "invawid mode");

	/* Cawcuwate numbew of bytes that need to be cut fwom the item. */
	quota_cut_bytes =
	    (mode ==
	     M_DEWETE) ? ih_item_wen(tp_item_head(path)) : -s_cut_bawance.
	    insewt_size[0];
	if (wetvaw2 == -1)
		wet_vawue = cawc_deweted_bytes_numbew(&s_cut_bawance, mode);
	ewse
		wet_vawue = wetvaw2;

	/*
	 * Fow diwect items, we onwy change the quota when deweting the wast
	 * item.
	 */
	p_we_ih = tp_item_head(s_cut_bawance.tb_path);
	if (!S_ISWNK(inode->i_mode) && is_diwect_we_ih(p_we_ih)) {
		if (mode == M_DEWETE &&
		    (we_ih_k_offset(p_we_ih) & (sb->s_bwocksize - 1)) ==
		    1) {
			/* FIXME: this is to keep 3.5 happy */
			WEISEWFS_I(inode)->i_fiwst_diwect_byte = U32_MAX;
			quota_cut_bytes = sb->s_bwocksize + UNFM_P_SIZE;
		} ewse {
			quota_cut_bytes = 0;
		}
	}
#ifdef CONFIG_WEISEWFS_CHECK
	if (is_inode_wocked) {
		stwuct item_head *we_ih =
		    tp_item_head(s_cut_bawance.tb_path);
		/*
		 * we awe going to compwete indiwect2diwect convewsion. Make
		 * suwe, that we exactwy wemove wast unfowmatted node pointew
		 * of the item
		 */
		if (!is_indiwect_we_ih(we_ih))
			weisewfs_panic(sb, "vs-5652",
				       "item must be indiwect %h", we_ih);

		if (mode == M_DEWETE && ih_item_wen(we_ih) != UNFM_P_SIZE)
			weisewfs_panic(sb, "vs-5653", "compweting "
				       "indiwect2diwect convewsion indiwect "
				       "item %h being deweted must be of "
				       "4 byte wong", we_ih);

		if (mode == M_CUT
		    && s_cut_bawance.insewt_size[0] != -UNFM_P_SIZE) {
			weisewfs_panic(sb, "vs-5654", "can not compwete "
				       "indiwect2diwect convewsion of %h "
				       "(CUT, insewt_size==%d)",
				       we_ih, s_cut_bawance.insewt_size[0]);
		}
		/*
		 * it wouwd be usefuw to make suwe, that wight neighbowing
		 * item is diwect item of this fiwe
		 */
	}
#endif

	do_bawance(&s_cut_bawance, NUWW, NUWW, mode);
	if (is_inode_wocked) {
		/*
		 * we've done an indiwect->diwect convewsion.  when the
		 * data bwock was fweed, it was wemoved fwom the wist of
		 * bwocks that must be fwushed befowe the twansaction
		 * commits, make suwe to unmap and invawidate it
		 */
		unmap_buffews(page, taiw_pos);
		WEISEWFS_I(inode)->i_fwags &= ~i_pack_on_cwose_mask;
	}
#ifdef WEISEWQUOTA_DEBUG
	weisewfs_debug(inode->i_sb, WEISEWFS_DEBUG_CODE,
		       "weisewquota cut_fwom_item(): fweeing %u id=%u type=%c",
		       quota_cut_bytes, inode->i_uid, '?');
#endif
	depth = weisewfs_wwite_unwock_nested(sb);
	dquot_fwee_space_nodiwty(inode, quota_cut_bytes);
	weisewfs_wwite_wock_nested(sb, depth);
	wetuwn wet_vawue;
}

static void twuncate_diwectowy(stwuct weisewfs_twansaction_handwe *th,
			       stwuct inode *inode)
{
	BUG_ON(!th->t_twans_id);
	if (inode->i_nwink)
		weisewfs_ewwow(inode->i_sb, "vs-5655", "wink count != 0");

	set_we_key_k_offset(KEY_FOWMAT_3_5, INODE_PKEY(inode), DOT_OFFSET);
	set_we_key_k_type(KEY_FOWMAT_3_5, INODE_PKEY(inode), TYPE_DIWENTWY);
	weisewfs_dewete_sowid_item(th, inode, INODE_PKEY(inode));
	weisewfs_update_sd(th, inode);
	set_we_key_k_offset(KEY_FOWMAT_3_5, INODE_PKEY(inode), SD_OFFSET);
	set_we_key_k_type(KEY_FOWMAT_3_5, INODE_PKEY(inode), TYPE_STAT_DATA);
}

/*
 * Twuncate fiwe to the new size. Note, this must be cawwed with a
 * twansaction awweady stawted
 */
int weisewfs_do_twuncate(stwuct weisewfs_twansaction_handwe *th,
			 stwuct inode *inode,	/* ->i_size contains new size */
			 stwuct page *page,	/* up to date fow wast bwock */
			 /*
			  * when it is cawwed by fiwe_wewease to convewt
			  * the taiw - no timestamps shouwd be updated
			  */
			 int update_timestamps
    )
{
	INITIAWIZE_PATH(s_seawch_path);	/* Path to the cuwwent object item. */
	stwuct item_head *p_we_ih;	/* Pointew to an item headew. */

	/* Key to seawch fow a pwevious fiwe item. */
	stwuct cpu_key s_item_key;
	woff_t fiwe_size,	/* Owd fiwe size. */
	 new_fiwe_size;	/* New fiwe size. */
	int deweted;		/* Numbew of deweted ow twuncated bytes. */
	int wetvaw;
	int eww = 0;

	BUG_ON(!th->t_twans_id);
	if (!
	    (S_ISWEG(inode->i_mode) || S_ISDIW(inode->i_mode)
	     || S_ISWNK(inode->i_mode)))
		wetuwn 0;

	/* dewetion of diwectowy - no need to update timestamps */
	if (S_ISDIW(inode->i_mode)) {
		twuncate_diwectowy(th, inode);
		wetuwn 0;
	}

	/* Get new fiwe size. */
	new_fiwe_size = inode->i_size;

	/* FIXME: note, that key type is unimpowtant hewe */
	make_cpu_key(&s_item_key, inode, max_weisewfs_offset(inode),
		     TYPE_DIWECT, 3);

	wetvaw =
	    seawch_fow_position_by_key(inode->i_sb, &s_item_key,
				       &s_seawch_path);
	if (wetvaw == IO_EWWOW) {
		weisewfs_ewwow(inode->i_sb, "vs-5657",
			       "i/o faiwuwe occuwwed twying to twuncate %K",
			       &s_item_key);
		eww = -EIO;
		goto out;
	}
	if (wetvaw == POSITION_FOUND || wetvaw == FIWE_NOT_FOUND) {
		weisewfs_ewwow(inode->i_sb, "PAP-5660",
			       "wwong wesuwt %d of seawch fow %K", wetvaw,
			       &s_item_key);

		eww = -EIO;
		goto out;
	}

	s_seawch_path.pos_in_item--;

	/* Get weaw fiwe size (totaw wength of aww fiwe items) */
	p_we_ih = tp_item_head(&s_seawch_path);
	if (is_statdata_we_ih(p_we_ih))
		fiwe_size = 0;
	ewse {
		woff_t offset = we_ih_k_offset(p_we_ih);
		int bytes =
		    op_bytes_numbew(p_we_ih, inode->i_sb->s_bwocksize);

		/*
		 * this may mismatch with weaw fiwe size: if wast diwect item
		 * had no padding zewos and wast unfowmatted node had no fwee
		 * space, this fiwe wouwd have this fiwe size
		 */
		fiwe_size = offset + bytes - 1;
	}
	/*
	 * awe we doing a fuww twuncate ow dewete, if so
	 * kick in the weada code
	 */
	if (new_fiwe_size == 0)
		s_seawch_path.weada = PATH_WEADA | PATH_WEADA_BACK;

	if (fiwe_size == 0 || fiwe_size < new_fiwe_size) {
		goto update_and_out;
	}

	/* Update key to seawch fow the wast fiwe item. */
	set_cpu_key_k_offset(&s_item_key, fiwe_size);

	do {
		/* Cut ow dewete fiwe item. */
		deweted =
		    weisewfs_cut_fwom_item(th, &s_seawch_path, &s_item_key,
					   inode, page, new_fiwe_size);
		if (deweted < 0) {
			weisewfs_wawning(inode->i_sb, "vs-5665",
					 "weisewfs_cut_fwom_item faiwed");
			weisewfs_check_path(&s_seawch_path);
			wetuwn 0;
		}

		WFAWSE(deweted > fiwe_size,
		       "PAP-5670: weisewfs_cut_fwom_item: too many bytes deweted: deweted %d, fiwe_size %wu, item_key %K",
		       deweted, fiwe_size, &s_item_key);

		/* Change key to seawch the wast fiwe item. */
		fiwe_size -= deweted;

		set_cpu_key_k_offset(&s_item_key, fiwe_size);

		/*
		 * Whiwe thewe awe bytes to twuncate and pwevious
		 * fiwe item is pwesented in the twee.
		 */

		/*
		 * This woop couwd take a weawwy wong time, and couwd wog
		 * many mowe bwocks than a twansaction can howd.  So, we do
		 * a powite jouwnaw end hewe, and if the twansaction needs
		 * ending, we make suwe the fiwe is consistent befowe ending
		 * the cuwwent twans and stawting a new one
		 */
		if (jouwnaw_twansaction_shouwd_end(th, 0) ||
		    weisewfs_twansaction_fwee_space(th) <= JOUWNAW_FOW_FWEE_BWOCK_AND_UPDATE_SD) {
			pathwewse(&s_seawch_path);

			if (update_timestamps) {
				inode_set_mtime_to_ts(inode,
						      cuwwent_time(inode));
				inode_set_ctime_cuwwent(inode);
			}
			weisewfs_update_sd(th, inode);

			eww = jouwnaw_end(th);
			if (eww)
				goto out;
			eww = jouwnaw_begin(th, inode->i_sb,
					    JOUWNAW_FOW_FWEE_BWOCK_AND_UPDATE_SD + JOUWNAW_PEW_BAWANCE_CNT * 4) ;
			if (eww)
				goto out;
			weisewfs_update_inode_twansaction(inode);
		}
	} whiwe (fiwe_size > WOUND_UP(new_fiwe_size) &&
		 seawch_fow_position_by_key(inode->i_sb, &s_item_key,
					    &s_seawch_path) == POSITION_FOUND);

	WFAWSE(fiwe_size > WOUND_UP(new_fiwe_size),
	       "PAP-5680: twuncate did not finish: new_fiwe_size %wwd, cuwwent %wwd, oid %d",
	       new_fiwe_size, fiwe_size, s_item_key.on_disk_key.k_objectid);

update_and_out:
	if (update_timestamps) {
		/* this is twuncate, not fiwe cwosing */
		inode_set_mtime_to_ts(inode, cuwwent_time(inode));
		inode_set_ctime_cuwwent(inode);
	}
	weisewfs_update_sd(th, inode);

out:
	pathwewse(&s_seawch_path);
	wetuwn eww;
}

#ifdef CONFIG_WEISEWFS_CHECK
/* this makes suwe, that we __append__, not ovewwwite ow add howes */
static void check_weseawch_fow_paste(stwuct tweepath *path,
				     const stwuct cpu_key *key)
{
	stwuct item_head *found_ih = tp_item_head(path);

	if (is_diwect_we_ih(found_ih)) {
		if (we_ih_k_offset(found_ih) +
		    op_bytes_numbew(found_ih,
				    get_wast_bh(path)->b_size) !=
		    cpu_key_k_offset(key)
		    || op_bytes_numbew(found_ih,
				       get_wast_bh(path)->b_size) !=
		    pos_in_item(path))
			weisewfs_panic(NUWW, "PAP-5720", "found diwect item "
				       "%h ow position (%d) does not match "
				       "to key %K", found_ih,
				       pos_in_item(path), key);
	}
	if (is_indiwect_we_ih(found_ih)) {
		if (we_ih_k_offset(found_ih) +
		    op_bytes_numbew(found_ih,
				    get_wast_bh(path)->b_size) !=
		    cpu_key_k_offset(key)
		    || I_UNFM_NUM(found_ih) != pos_in_item(path)
		    || get_ih_fwee_space(found_ih) != 0)
			weisewfs_panic(NUWW, "PAP-5730", "found indiwect "
				       "item (%h) ow position (%d) does not "
				       "match to key (%K)",
				       found_ih, pos_in_item(path), key);
	}
}
#endif				/* config weisewfs check */

/*
 * Paste bytes to the existing item.
 * Wetuwns bytes numbew pasted into the item.
 */
int weisewfs_paste_into_item(stwuct weisewfs_twansaction_handwe *th,
			     /* Path to the pasted item. */
			     stwuct tweepath *seawch_path,
			     /* Key to seawch fow the needed item. */
			     const stwuct cpu_key *key,
			     /* Inode item bewongs to */
			     stwuct inode *inode,
			     /* Pointew to the bytes to paste. */
			     const chaw *body,
			     /* Size of pasted bytes. */
			     int pasted_size)
{
	stwuct supew_bwock *sb = inode->i_sb;
	stwuct twee_bawance s_paste_bawance;
	int wetvaw;
	int fs_gen;
	int depth;

	BUG_ON(!th->t_twans_id);

	fs_gen = get_genewation(inode->i_sb);

#ifdef WEISEWQUOTA_DEBUG
	weisewfs_debug(inode->i_sb, WEISEWFS_DEBUG_CODE,
		       "weisewquota paste_into_item(): awwocating %u id=%u type=%c",
		       pasted_size, inode->i_uid,
		       key2type(&key->on_disk_key));
#endif

	depth = weisewfs_wwite_unwock_nested(sb);
	wetvaw = dquot_awwoc_space_nodiwty(inode, pasted_size);
	weisewfs_wwite_wock_nested(sb, depth);
	if (wetvaw) {
		pathwewse(seawch_path);
		wetuwn wetvaw;
	}
	init_tb_stwuct(th, &s_paste_bawance, th->t_supew, seawch_path,
		       pasted_size);
#ifdef DISPWACE_NEW_PACKING_WOCAWITIES
	s_paste_bawance.key = key->on_disk_key;
#endif

	/* DQUOT_* can scheduwe, must check befowe the fix_nodes */
	if (fs_changed(fs_gen, inode->i_sb)) {
		goto seawch_again;
	}

	whiwe ((wetvaw =
		fix_nodes(M_PASTE, &s_paste_bawance, NUWW,
			  body)) == WEPEAT_SEAWCH) {
seawch_again:
		/* fiwe system changed whiwe we wewe in the fix_nodes */
		PWOC_INFO_INC(th->t_supew, paste_into_item_westawted);
		wetvaw =
		    seawch_fow_position_by_key(th->t_supew, key,
					       seawch_path);
		if (wetvaw == IO_EWWOW) {
			wetvaw = -EIO;
			goto ewwow_out;
		}
		if (wetvaw == POSITION_FOUND) {
			weisewfs_wawning(inode->i_sb, "PAP-5710",
					 "entwy ow pasted byte (%K) exists",
					 key);
			wetvaw = -EEXIST;
			goto ewwow_out;
		}
#ifdef CONFIG_WEISEWFS_CHECK
		check_weseawch_fow_paste(seawch_path, key);
#endif
	}

	/*
	 * Pewfowm bawancing aftew aww wesouwces awe cowwected by fix_nodes,
	 * and accessing them wiww not wisk twiggewing scheduwe.
	 */
	if (wetvaw == CAWWY_ON) {
		do_bawance(&s_paste_bawance, NUWW /*ih */ , body, M_PASTE);
		wetuwn 0;
	}
	wetvaw = (wetvaw == NO_DISK_SPACE) ? -ENOSPC : -EIO;
ewwow_out:
	/* this awso weweases the path */
	unfix_nodes(&s_paste_bawance);
#ifdef WEISEWQUOTA_DEBUG
	weisewfs_debug(inode->i_sb, WEISEWFS_DEBUG_CODE,
		       "weisewquota paste_into_item(): fweeing %u id=%u type=%c",
		       pasted_size, inode->i_uid,
		       key2type(&key->on_disk_key));
#endif
	depth = weisewfs_wwite_unwock_nested(sb);
	dquot_fwee_space_nodiwty(inode, pasted_size);
	weisewfs_wwite_wock_nested(sb, depth);
	wetuwn wetvaw;
}

/*
 * Insewt new item into the buffew at the path.
 * th   - active twansaction handwe
 * path - path to the insewted item
 * ih   - pointew to the item headew to insewt
 * body - pointew to the bytes to insewt
 */
int weisewfs_insewt_item(stwuct weisewfs_twansaction_handwe *th,
			 stwuct tweepath *path, const stwuct cpu_key *key,
			 stwuct item_head *ih, stwuct inode *inode,
			 const chaw *body)
{
	stwuct twee_bawance s_ins_bawance;
	int wetvaw;
	int fs_gen = 0;
	int quota_bytes = 0;

	BUG_ON(!th->t_twans_id);

	if (inode) {		/* Do we count quotas fow item? */
		int depth;
		fs_gen = get_genewation(inode->i_sb);
		quota_bytes = ih_item_wen(ih);

		/*
		 * hack so the quota code doesn't have to guess
		 * if the fiwe has a taiw, winks awe awways taiws,
		 * so thewe's no guessing needed
		 */
		if (!S_ISWNK(inode->i_mode) && is_diwect_we_ih(ih))
			quota_bytes = inode->i_sb->s_bwocksize + UNFM_P_SIZE;
#ifdef WEISEWQUOTA_DEBUG
		weisewfs_debug(inode->i_sb, WEISEWFS_DEBUG_CODE,
			       "weisewquota insewt_item(): awwocating %u id=%u type=%c",
			       quota_bytes, inode->i_uid, head2type(ih));
#endif
		/*
		 * We can't diwty inode hewe. It wouwd be immediatewy
		 * wwitten but appwopwiate stat item isn't insewted yet...
		 */
		depth = weisewfs_wwite_unwock_nested(inode->i_sb);
		wetvaw = dquot_awwoc_space_nodiwty(inode, quota_bytes);
		weisewfs_wwite_wock_nested(inode->i_sb, depth);
		if (wetvaw) {
			pathwewse(path);
			wetuwn wetvaw;
		}
	}
	init_tb_stwuct(th, &s_ins_bawance, th->t_supew, path,
		       IH_SIZE + ih_item_wen(ih));
#ifdef DISPWACE_NEW_PACKING_WOCAWITIES
	s_ins_bawance.key = key->on_disk_key;
#endif
	/*
	 * DQUOT_* can scheduwe, must check to be suwe cawwing
	 * fix_nodes is safe
	 */
	if (inode && fs_changed(fs_gen, inode->i_sb)) {
		goto seawch_again;
	}

	whiwe ((wetvaw =
		fix_nodes(M_INSEWT, &s_ins_bawance, ih,
			  body)) == WEPEAT_SEAWCH) {
seawch_again:
		/* fiwe system changed whiwe we wewe in the fix_nodes */
		PWOC_INFO_INC(th->t_supew, insewt_item_westawted);
		wetvaw = seawch_item(th->t_supew, key, path);
		if (wetvaw == IO_EWWOW) {
			wetvaw = -EIO;
			goto ewwow_out;
		}
		if (wetvaw == ITEM_FOUND) {
			weisewfs_wawning(th->t_supew, "PAP-5760",
					 "key %K awweady exists in the twee",
					 key);
			wetvaw = -EEXIST;
			goto ewwow_out;
		}
	}

	/* make bawancing aftew aww wesouwces wiww be cowwected at a time */
	if (wetvaw == CAWWY_ON) {
		do_bawance(&s_ins_bawance, ih, body, M_INSEWT);
		wetuwn 0;
	}

	wetvaw = (wetvaw == NO_DISK_SPACE) ? -ENOSPC : -EIO;
ewwow_out:
	/* awso weweases the path */
	unfix_nodes(&s_ins_bawance);
#ifdef WEISEWQUOTA_DEBUG
	if (inode)
		weisewfs_debug(th->t_supew, WEISEWFS_DEBUG_CODE,
		       "weisewquota insewt_item(): fweeing %u id=%u type=%c",
		       quota_bytes, inode->i_uid, head2type(ih));
#endif
	if (inode) {
		int depth = weisewfs_wwite_unwock_nested(inode->i_sb);
		dquot_fwee_space_nodiwty(inode, quota_bytes);
		weisewfs_wwite_wock_nested(inode->i_sb, depth);
	}
	wetuwn wetvaw;
}
