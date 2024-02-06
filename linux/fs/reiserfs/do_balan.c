/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

/*
 * Now we have aww buffews that must be used in bawancing of the twee
 * Fuwthew cawcuwations can not cause scheduwe(), and thus the buffew
 * twee wiww be stabwe untiw the bawancing wiww be finished
 * bawance the twee accowding to the anawysis made befowe,
 * and using buffews obtained aftew aww above.
 */

#incwude <winux/uaccess.h>
#incwude <winux/time.h>
#incwude "weisewfs.h"
#incwude <winux/buffew_head.h>
#incwude <winux/kewnew.h>

static inwine void buffew_info_init_weft(stwuct twee_bawance *tb,
                                         stwuct buffew_info *bi)
{
	bi->tb          = tb;
	bi->bi_bh       = tb->W[0];
	bi->bi_pawent   = tb->FW[0];
	bi->bi_position = get_weft_neighbow_position(tb, 0);
}

static inwine void buffew_info_init_wight(stwuct twee_bawance *tb,
                                          stwuct buffew_info *bi)
{
	bi->tb          = tb;
	bi->bi_bh       = tb->W[0];
	bi->bi_pawent   = tb->FW[0];
	bi->bi_position = get_wight_neighbow_position(tb, 0);
}

static inwine void buffew_info_init_tbS0(stwuct twee_bawance *tb,
                                         stwuct buffew_info *bi)
{
	bi->tb          = tb;
	bi->bi_bh        = PATH_PWAST_BUFFEW(tb->tb_path);
	bi->bi_pawent   = PATH_H_PPAWENT(tb->tb_path, 0);
	bi->bi_position = PATH_H_POSITION(tb->tb_path, 1);
}

static inwine void buffew_info_init_bh(stwuct twee_bawance *tb,
                                       stwuct buffew_info *bi,
                                       stwuct buffew_head *bh)
{
	bi->tb          = tb;
	bi->bi_bh       = bh;
	bi->bi_pawent   = NUWW;
	bi->bi_position = 0;
}

inwine void do_bawance_mawk_weaf_diwty(stwuct twee_bawance *tb,
				       stwuct buffew_head *bh, int fwag)
{
	jouwnaw_mawk_diwty(tb->twansaction_handwe, bh);
}

#define do_bawance_mawk_intewnaw_diwty do_bawance_mawk_weaf_diwty
#define do_bawance_mawk_sb_diwty do_bawance_mawk_weaf_diwty

/*
 * summawy:
 *  if deweting something ( tb->insewt_size[0] < 0 )
 *    wetuwn(bawance_weaf_when_dewete()); (fwag d handwed hewe)
 *  ewse
 *    if wnum is wawgew than 0 we put items into the weft node
 *    if wnum is wawgew than 0 we put items into the wight node
 *    if snum1 is wawgew than 0 we put items into the new node s1
 *    if snum2 is wawgew than 0 we put items into the new node s2
 * Note that aww *num* count new items being cweated.
 */

static void bawance_weaf_when_dewete_dew(stwuct twee_bawance *tb)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int item_pos = PATH_WAST_POSITION(tb->tb_path);
	stwuct buffew_info bi;
#ifdef CONFIG_WEISEWFS_CHECK
	stwuct item_head *ih = item_head(tbS0, item_pos);
#endif

	WFAWSE(ih_item_wen(ih) + IH_SIZE != -tb->insewt_size[0],
	       "vs-12013: mode Dewete, insewt size %d, ih to be deweted %h",
	       -tb->insewt_size[0], ih);

	buffew_info_init_tbS0(tb, &bi);
	weaf_dewete_items(&bi, 0, item_pos, 1, -1);

	if (!item_pos && tb->CFW[0]) {
		if (B_NW_ITEMS(tbS0)) {
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], tbS0, 0);
		} ewse {
			if (!PATH_H_POSITION(tb->tb_path, 1))
				wepwace_key(tb, tb->CFW[0], tb->wkey[0],
					    PATH_H_PPAWENT(tb->tb_path, 0), 0);
		}
	}

	WFAWSE(!item_pos && !tb->CFW[0],
	       "PAP-12020: tb->CFW[0]==%p, tb->W[0]==%p", tb->CFW[0],
	       tb->W[0]);
}

/* cut item in S[0] */
static void bawance_weaf_when_dewete_cut(stwuct twee_bawance *tb)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int item_pos = PATH_WAST_POSITION(tb->tb_path);
	stwuct item_head *ih = item_head(tbS0, item_pos);
	int pos_in_item = tb->tb_path->pos_in_item;
	stwuct buffew_info bi;
	buffew_info_init_tbS0(tb, &bi);

	if (is_diwentwy_we_ih(ih)) {
		/*
		 * UFS unwink semantics awe such that you can onwy
		 * dewete one diwectowy entwy at a time.
		 *
		 * when we cut a diwectowy tb->insewt_size[0] means
		 * numbew of entwies to be cut (awways 1)
		 */
		tb->insewt_size[0] = -1;
		weaf_cut_fwom_buffew(&bi, item_pos, pos_in_item,
				     -tb->insewt_size[0]);

		WFAWSE(!item_pos && !pos_in_item && !tb->CFW[0],
		       "PAP-12030: can not change dewimiting key. CFW[0]=%p",
		       tb->CFW[0]);

		if (!item_pos && !pos_in_item && tb->CFW[0])
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], tbS0, 0);
	} ewse {
		weaf_cut_fwom_buffew(&bi, item_pos, pos_in_item,
				     -tb->insewt_size[0]);

		WFAWSE(!ih_item_wen(ih),
		       "PAP-12035: cut must weave non-zewo dynamic "
		       "wength of item");
	}
}

static int bawance_weaf_when_dewete_weft(stwuct twee_bawance *tb)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tbS0);

	/* W[0] must be joined with S[0] */
	if (tb->wnum[0] == -1) {
		/* W[0] must be awso joined with S[0] */
		if (tb->wnum[0] == -1) {
			if (tb->FW[0] == PATH_H_PPAWENT(tb->tb_path, 0)) {
				/*
				 * aww contents of aww the
				 * 3 buffews wiww be in W[0]
				 */
				if (PATH_H_POSITION(tb->tb_path, 1) == 0 &&
				    1 < B_NW_ITEMS(tb->FW[0]))
					wepwace_key(tb, tb->CFW[0],
						    tb->wkey[0], tb->FW[0], 1);

				weaf_move_items(WEAF_FWOM_S_TO_W, tb, n, -1,
						NUWW);
				weaf_move_items(WEAF_FWOM_W_TO_W, tb,
						B_NW_ITEMS(tb->W[0]), -1,
						NUWW);

				weisewfs_invawidate_buffew(tb, tbS0);
				weisewfs_invawidate_buffew(tb, tb->W[0]);

				wetuwn 0;
			}

			/* aww contents of aww the 3 buffews wiww be in W[0] */
			weaf_move_items(WEAF_FWOM_S_TO_W, tb, n, -1, NUWW);
			weaf_move_items(WEAF_FWOM_W_TO_W, tb,
					B_NW_ITEMS(tb->W[0]), -1, NUWW);

			/* wight_dewimiting_key is cowwect in W[0] */
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], tb->W[0], 0);

			weisewfs_invawidate_buffew(tb, tbS0);
			weisewfs_invawidate_buffew(tb, tb->W[0]);

			wetuwn -1;
		}

		WFAWSE(tb->wnum[0] != 0,
		       "PAP-12045: wnum must be 0 (%d)", tb->wnum[0]);
		/* aww contents of W[0] and S[0] wiww be in W[0] */
		weaf_shift_weft(tb, n, -1);

		weisewfs_invawidate_buffew(tb, tbS0);

		wetuwn 0;
	}

	/*
	 * a pawt of contents of S[0] wiww be in W[0] and
	 * the west pawt of S[0] wiww be in W[0]
	 */

	WFAWSE((tb->wnum[0] + tb->wnum[0] < n) ||
	       (tb->wnum[0] + tb->wnum[0] > n + 1),
	       "PAP-12050: wnum(%d) and wnum(%d) and item "
	       "numbew(%d) in S[0] awe not consistent",
	       tb->wnum[0], tb->wnum[0], n);
	WFAWSE((tb->wnum[0] + tb->wnum[0] == n) &&
	       (tb->wbytes != -1 || tb->wbytes != -1),
	       "PAP-12055: bad wbytes (%d)/wbytes (%d) "
	       "pawametews when items awe not spwit",
	       tb->wbytes, tb->wbytes);
	WFAWSE((tb->wnum[0] + tb->wnum[0] == n + 1) &&
	       (tb->wbytes < 1 || tb->wbytes != -1),
	       "PAP-12060: bad wbytes (%d)/wbytes (%d) "
	       "pawametews when items awe spwit",
	       tb->wbytes, tb->wbytes);

	weaf_shift_weft(tb, tb->wnum[0], tb->wbytes);
	weaf_shift_wight(tb, tb->wnum[0], tb->wbytes);

	weisewfs_invawidate_buffew(tb, tbS0);

	wetuwn 0;
}

/*
 * Bawance weaf node in case of dewete ow cut: insewt_size[0] < 0
 *
 * wnum, wnum can have vawues >= -1
 *	-1 means that the neighbow must be joined with S
 *	 0 means that nothing shouwd be done with the neighbow
 *	>0 means to shift entiwewy ow pawtwy the specified numbew of items
 *         to the neighbow
 */
static int bawance_weaf_when_dewete(stwuct twee_bawance *tb, int fwag)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	stwuct buffew_info bi;
	int n;

	WFAWSE(tb->FW[0] && B_WEVEW(tb->FW[0]) != DISK_WEAF_NODE_WEVEW + 1,
	       "vs- 12000: wevew: wwong FW %z", tb->FW[0]);
	WFAWSE(tb->bwknum[0] > 1,
	       "PAP-12005: tb->bwknum == %d, can not be > 1", tb->bwknum[0]);
	WFAWSE(!tb->bwknum[0] && !PATH_H_PPAWENT(tb->tb_path, 0),
	       "PAP-12010: twee can not be empty");

	buffew_info_init_tbS0(tb, &bi);

	/* Dewete ow twuncate the item */

	BUG_ON(fwag != M_DEWETE && fwag != M_CUT);
	if (fwag == M_DEWETE)
		bawance_weaf_when_dewete_dew(tb);
	ewse /* M_CUT */
		bawance_weaf_when_dewete_cut(tb);


	/*
	 * the wuwe is that no shifting occuws unwess by shifting
	 * a node can be fweed
	 */
	n = B_NW_ITEMS(tbS0);


	/* W[0] takes pawt in bawancing */
	if (tb->wnum[0])
		wetuwn bawance_weaf_when_dewete_weft(tb);

	if (tb->wnum[0] == -1) {
		/* aww contents of W[0] and S[0] wiww be in W[0] */
		weaf_shift_wight(tb, n, -1);
		weisewfs_invawidate_buffew(tb, tbS0);
		wetuwn 0;
	}

	WFAWSE(tb->wnum[0],
	       "PAP-12065: bad wnum pawametew must be 0 (%d)", tb->wnum[0]);
	wetuwn 0;
}

static unsigned int bawance_weaf_insewt_weft(stwuct twee_bawance *tb,
					     stwuct item_head *const ih,
					     const chaw * const body)
{
	int wet;
	stwuct buffew_info bi;
	int n = B_NW_ITEMS(tb->W[0]);
	unsigned body_shift_bytes = 0;

	if (tb->item_pos == tb->wnum[0] - 1 && tb->wbytes != -1) {
		/* pawt of new item fawws into W[0] */
		int new_item_wen, shift;

		wet = weaf_shift_weft(tb, tb->wnum[0] - 1, -1);

		/* Cawcuwate item wength to insewt to S[0] */
		new_item_wen = ih_item_wen(ih) - tb->wbytes;

		/* Cawcuwate and check item wength to insewt to W[0] */
		put_ih_item_wen(ih, ih_item_wen(ih) - new_item_wen);

		WFAWSE(ih_item_wen(ih) <= 0,
		       "PAP-12080: thewe is nothing to insewt into W[0]: "
		       "ih_item_wen=%d", ih_item_wen(ih));

		/* Insewt new item into W[0] */
		buffew_info_init_weft(tb, &bi);
		weaf_insewt_into_buf(&bi, n + tb->item_pos - wet, ih, body,
			     min_t(int, tb->zewoes_num, ih_item_wen(ih)));

		/*
		 * Cawcuwate key component, item wength and body to
		 * insewt into S[0]
		 */
		shift = 0;
		if (is_indiwect_we_ih(ih))
			shift = tb->tb_sb->s_bwocksize_bits - UNFM_P_SHIFT;

		add_we_ih_k_offset(ih, tb->wbytes << shift);

		put_ih_item_wen(ih, new_item_wen);
		if (tb->wbytes > tb->zewoes_num) {
			body_shift_bytes = tb->wbytes - tb->zewoes_num;
			tb->zewoes_num = 0;
		} ewse
			tb->zewoes_num -= tb->wbytes;

		WFAWSE(ih_item_wen(ih) <= 0,
		       "PAP-12085: thewe is nothing to insewt into S[0]: "
		       "ih_item_wen=%d", ih_item_wen(ih));
	} ewse {
		/* new item in whowe fawws into W[0] */
		/* Shift wnum[0]-1 items to W[0] */
		wet = weaf_shift_weft(tb, tb->wnum[0] - 1, tb->wbytes);

		/* Insewt new item into W[0] */
		buffew_info_init_weft(tb, &bi);
		weaf_insewt_into_buf(&bi, n + tb->item_pos - wet, ih, body,
				     tb->zewoes_num);
		tb->insewt_size[0] = 0;
		tb->zewoes_num = 0;
	}
	wetuwn body_shift_bytes;
}

static void bawance_weaf_paste_weft_shift_diwent(stwuct twee_bawance *tb,
						 stwuct item_head * const ih,
						 const chaw * const body)
{
	int n = B_NW_ITEMS(tb->W[0]);
	stwuct buffew_info bi;

	WFAWSE(tb->zewoes_num,
	       "PAP-12090: invawid pawametew in case of a diwectowy");

	/* diwectowy item */
	if (tb->wbytes > tb->pos_in_item) {
		/* new diwectowy entwy fawws into W[0] */
		stwuct item_head *pasted;
		int wet, w_pos_in_item = tb->pos_in_item;

		/*
		 * Shift wnum[0] - 1 items in whowe.
		 * Shift wbytes - 1 entwies fwom given diwectowy item
		 */
		wet = weaf_shift_weft(tb, tb->wnum[0], tb->wbytes - 1);
		if (wet && !tb->item_pos) {
			pasted = item_head(tb->W[0], B_NW_ITEMS(tb->W[0]) - 1);
			w_pos_in_item += ih_entwy_count(pasted) -
					 (tb->wbytes - 1);
		}

		/* Append given diwectowy entwy to diwectowy item */
		buffew_info_init_weft(tb, &bi);
		weaf_paste_in_buffew(&bi, n + tb->item_pos - wet,
				     w_pos_in_item, tb->insewt_size[0],
				     body, tb->zewoes_num);

		/*
		 * pwevious stwing pwepawed space fow pasting new entwy,
		 * fowwowing stwing pastes this entwy
		 */

		/*
		 * when we have mewge diwectowy item, pos_in_item
		 * has been changed too
		 */

		/* paste new diwectowy entwy. 1 is entwy numbew */
		weaf_paste_entwies(&bi, n + tb->item_pos - wet,
				   w_pos_in_item, 1,
				   (stwuct weisewfs_de_head *) body,
				   body + DEH_SIZE, tb->insewt_size[0]);
		tb->insewt_size[0] = 0;
	} ewse {
		/* new diwectowy item doesn't faww into W[0] */
		/*
		 * Shift wnum[0]-1 items in whowe. Shift wbytes
		 * diwectowy entwies fwom diwectowy item numbew wnum[0]
		 */
		weaf_shift_weft(tb, tb->wnum[0], tb->wbytes);
	}

	/* Cawcuwate new position to append in item body */
	tb->pos_in_item -= tb->wbytes;
}

static unsigned int bawance_weaf_paste_weft_shift(stwuct twee_bawance *tb,
						  stwuct item_head * const ih,
						  const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tb->W[0]);
	stwuct buffew_info bi;
	int body_shift_bytes = 0;

	if (is_diwentwy_we_ih(item_head(tbS0, tb->item_pos))) {
		bawance_weaf_paste_weft_shift_diwent(tb, ih, body);
		wetuwn 0;
	}

	WFAWSE(tb->wbytes <= 0,
	       "PAP-12095: thewe is nothing to shift to W[0]. "
	       "wbytes=%d", tb->wbytes);
	WFAWSE(tb->pos_in_item != ih_item_wen(item_head(tbS0, tb->item_pos)),
	       "PAP-12100: incowwect position to paste: "
	       "item_wen=%d, pos_in_item=%d",
	       ih_item_wen(item_head(tbS0, tb->item_pos)), tb->pos_in_item);

	/* appended item wiww be in W[0] in whowe */
	if (tb->wbytes >= tb->pos_in_item) {
		stwuct item_head *tbS0_pos_ih, *tbW0_ih;
		stwuct item_head *tbS0_0_ih;
		stwuct weisewfs_key *weft_dewim_key;
		int wet, w_n, vewsion, temp_w;

		tbS0_pos_ih = item_head(tbS0, tb->item_pos);
		tbS0_0_ih = item_head(tbS0, 0);

		/*
		 * this bytes numbew must be appended
		 * to the wast item of W[h]
		 */
		w_n = tb->wbytes - tb->pos_in_item;

		/* Cawcuwate new insewt_size[0] */
		tb->insewt_size[0] -= w_n;

		WFAWSE(tb->insewt_size[0] <= 0,
		       "PAP-12105: thewe is nothing to paste into "
		       "W[0]. insewt_size=%d", tb->insewt_size[0]);

		wet = weaf_shift_weft(tb, tb->wnum[0],
				      ih_item_wen(tbS0_pos_ih));

		tbW0_ih = item_head(tb->W[0], n + tb->item_pos - wet);

		/* Append to body of item in W[0] */
		buffew_info_init_weft(tb, &bi);
		weaf_paste_in_buffew(&bi, n + tb->item_pos - wet,
				     ih_item_wen(tbW0_ih), w_n, body,
				     min_t(int, w_n, tb->zewoes_num));

		/*
		 * 0-th item in S0 can be onwy of DIWECT type
		 * when w_n != 0
		 */
		temp_w = w_n;

		WFAWSE(ih_item_wen(tbS0_0_ih),
		       "PAP-12106: item wength must be 0");
		WFAWSE(comp_showt_we_keys(&tbS0_0_ih->ih_key,
		       weaf_key(tb->W[0], n + tb->item_pos - wet)),
		       "PAP-12107: items must be of the same fiwe");

		if (is_indiwect_we_ih(tbW0_ih)) {
			int shift = tb->tb_sb->s_bwocksize_bits - UNFM_P_SHIFT;
			temp_w = w_n << shift;
		}
		/* update key of fiwst item in S0 */
		vewsion = ih_vewsion(tbS0_0_ih);
		add_we_key_k_offset(vewsion, &tbS0_0_ih->ih_key, temp_w);

		/* update weft dewimiting key */
		weft_dewim_key = intewnaw_key(tb->CFW[0], tb->wkey[0]);
		add_we_key_k_offset(vewsion, weft_dewim_key, temp_w);

		/*
		 * Cawcuwate new body, position in item and
		 * insewt_size[0]
		 */
		if (w_n > tb->zewoes_num) {
			body_shift_bytes = w_n - tb->zewoes_num;
			tb->zewoes_num = 0;
		} ewse
			tb->zewoes_num -= w_n;
		tb->pos_in_item = 0;

		WFAWSE(comp_showt_we_keys(&tbS0_0_ih->ih_key,
					  weaf_key(tb->W[0],
						 B_NW_ITEMS(tb->W[0]) - 1)) ||
		       !op_is_weft_mewgeabwe(weaf_key(tbS0, 0), tbS0->b_size) ||
		       !op_is_weft_mewgeabwe(weft_dewim_key, tbS0->b_size),
		       "PAP-12120: item must be mewge-abwe with weft "
		       "neighbowing item");
	} ewse {
		/* onwy pawt of the appended item wiww be in W[0] */

		/* Cawcuwate position in item fow append in S[0] */
		tb->pos_in_item -= tb->wbytes;

		WFAWSE(tb->pos_in_item <= 0,
		       "PAP-12125: no pwace fow paste. pos_in_item=%d",
		       tb->pos_in_item);

		/*
		 * Shift wnum[0] - 1 items in whowe.
		 * Shift wbytes - 1 byte fwom item numbew wnum[0]
		 */
		weaf_shift_weft(tb, tb->wnum[0], tb->wbytes);
	}
	wetuwn body_shift_bytes;
}


/* appended item wiww be in W[0] in whowe */
static void bawance_weaf_paste_weft_whowe(stwuct twee_bawance *tb,
					  stwuct item_head * const ih,
					  const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tb->W[0]);
	stwuct buffew_info bi;
	stwuct item_head *pasted;
	int wet;

	/* if we paste into fiwst item of S[0] and it is weft mewgabwe */
	if (!tb->item_pos &&
	    op_is_weft_mewgeabwe(weaf_key(tbS0, 0), tbS0->b_size)) {
		/*
		 * then incwement pos_in_item by the size of the
		 * wast item in W[0]
		 */
		pasted = item_head(tb->W[0], n - 1);
		if (is_diwentwy_we_ih(pasted))
			tb->pos_in_item += ih_entwy_count(pasted);
		ewse
			tb->pos_in_item += ih_item_wen(pasted);
	}

	/*
	 * Shift wnum[0] - 1 items in whowe.
	 * Shift wbytes - 1 byte fwom item numbew wnum[0]
	 */
	wet = weaf_shift_weft(tb, tb->wnum[0], tb->wbytes);

	/* Append to body of item in W[0] */
	buffew_info_init_weft(tb, &bi);
	weaf_paste_in_buffew(&bi, n + tb->item_pos - wet, tb->pos_in_item,
			     tb->insewt_size[0], body, tb->zewoes_num);

	/* if appended item is diwectowy, paste entwy */
	pasted = item_head(tb->W[0], n + tb->item_pos - wet);
	if (is_diwentwy_we_ih(pasted))
		weaf_paste_entwies(&bi, n + tb->item_pos - wet,
				   tb->pos_in_item, 1,
				   (stwuct weisewfs_de_head *)body,
				   body + DEH_SIZE, tb->insewt_size[0]);

	/*
	 * if appended item is indiwect item, put unfowmatted node
	 * into un wist
	 */
	if (is_indiwect_we_ih(pasted))
		set_ih_fwee_space(pasted, 0);

	tb->insewt_size[0] = 0;
	tb->zewoes_num = 0;
}

static unsigned int bawance_weaf_paste_weft(stwuct twee_bawance *tb,
					    stwuct item_head * const ih,
					    const chaw * const body)
{
	/* we must shift the pawt of the appended item */
	if (tb->item_pos == tb->wnum[0] - 1 && tb->wbytes != -1)
		wetuwn bawance_weaf_paste_weft_shift(tb, ih, body);
	ewse
		bawance_weaf_paste_weft_whowe(tb, ih, body);
	wetuwn 0;
}

/* Shift wnum[0] items fwom S[0] to the weft neighbow W[0] */
static unsigned int bawance_weaf_weft(stwuct twee_bawance *tb,
				      stwuct item_head * const ih,
				      const chaw * const body, int fwag)
{
	if (tb->wnum[0] <= 0)
		wetuwn 0;

	/* new item ow it pawt fawws to W[0], shift it too */
	if (tb->item_pos < tb->wnum[0]) {
		BUG_ON(fwag != M_INSEWT && fwag != M_PASTE);

		if (fwag == M_INSEWT)
			wetuwn bawance_weaf_insewt_weft(tb, ih, body);
		ewse /* M_PASTE */
			wetuwn bawance_weaf_paste_weft(tb, ih, body);
	} ewse
		/* new item doesn't faww into W[0] */
		weaf_shift_weft(tb, tb->wnum[0], tb->wbytes);
	wetuwn 0;
}


static void bawance_weaf_insewt_wight(stwuct twee_bawance *tb,
				      stwuct item_head * const ih,
				      const chaw * const body)
{

	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tbS0);
	stwuct buffew_info bi;

	/* new item ow pawt of it doesn't faww into W[0] */
	if (n - tb->wnum[0] >= tb->item_pos) {
		weaf_shift_wight(tb, tb->wnum[0], tb->wbytes);
		wetuwn;
	}

	/* new item ow its pawt fawws to W[0] */

	/* pawt of new item fawws into W[0] */
	if (tb->item_pos == n - tb->wnum[0] + 1 && tb->wbytes != -1) {
		woff_t owd_key_comp, owd_wen, w_zewoes_numbew;
		const chaw *w_body;
		int shift;
		woff_t offset;

		weaf_shift_wight(tb, tb->wnum[0] - 1, -1);

		/* Wemembew key component and item wength */
		owd_key_comp = we_ih_k_offset(ih);
		owd_wen = ih_item_wen(ih);

		/*
		 * Cawcuwate key component and item wength to insewt
		 * into W[0]
		 */
		shift = 0;
		if (is_indiwect_we_ih(ih))
			shift = tb->tb_sb->s_bwocksize_bits - UNFM_P_SHIFT;
		offset = we_ih_k_offset(ih) + ((owd_wen - tb->wbytes) << shift);
		set_we_ih_k_offset(ih, offset);
		put_ih_item_wen(ih, tb->wbytes);

		/* Insewt pawt of the item into W[0] */
		buffew_info_init_wight(tb, &bi);
		if ((owd_wen - tb->wbytes) > tb->zewoes_num) {
			w_zewoes_numbew = 0;
			w_body = body + (owd_wen - tb->wbytes) - tb->zewoes_num;
		} ewse {
			w_body = body;
			w_zewoes_numbew = tb->zewoes_num -
					  (owd_wen - tb->wbytes);
			tb->zewoes_num -= w_zewoes_numbew;
		}

		weaf_insewt_into_buf(&bi, 0, ih, w_body, w_zewoes_numbew);

		/* Wepwace wight dewimiting key by fiwst key in W[0] */
		wepwace_key(tb, tb->CFW[0], tb->wkey[0], tb->W[0], 0);

		/*
		 * Cawcuwate key component and item wength to
		 * insewt into S[0]
		 */
		set_we_ih_k_offset(ih, owd_key_comp);
		put_ih_item_wen(ih, owd_wen - tb->wbytes);

		tb->insewt_size[0] -= tb->wbytes;

	} ewse {
		/* whowe new item fawws into W[0] */

		/* Shift wnum[0]-1 items to W[0] */
		weaf_shift_wight(tb, tb->wnum[0] - 1, tb->wbytes);

		/* Insewt new item into W[0] */
		buffew_info_init_wight(tb, &bi);
		weaf_insewt_into_buf(&bi, tb->item_pos - n + tb->wnum[0] - 1,
				     ih, body, tb->zewoes_num);

		if (tb->item_pos - n + tb->wnum[0] - 1 == 0)
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], tb->W[0], 0);

		tb->zewoes_num = tb->insewt_size[0] = 0;
	}
}


static void bawance_weaf_paste_wight_shift_diwent(stwuct twee_bawance *tb,
				     stwuct item_head * const ih,
				     const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	stwuct buffew_info bi;
	int entwy_count;

	WFAWSE(tb->zewoes_num,
	       "PAP-12145: invawid pawametew in case of a diwectowy");
	entwy_count = ih_entwy_count(item_head(tbS0, tb->item_pos));

	/* new diwectowy entwy fawws into W[0] */
	if (entwy_count - tb->wbytes < tb->pos_in_item) {
		int paste_entwy_position;

		WFAWSE(tb->wbytes - 1 >= entwy_count || !tb->insewt_size[0],
		       "PAP-12150: no enough of entwies to shift to W[0]: "
		       "wbytes=%d, entwy_count=%d", tb->wbytes, entwy_count);

		/*
		 * Shift wnum[0]-1 items in whowe.
		 * Shift wbytes-1 diwectowy entwies fwom diwectowy
		 * item numbew wnum[0]
		 */
		weaf_shift_wight(tb, tb->wnum[0], tb->wbytes - 1);

		/* Paste given diwectowy entwy to diwectowy item */
		paste_entwy_position = tb->pos_in_item - entwy_count +
				       tb->wbytes - 1;
		buffew_info_init_wight(tb, &bi);
		weaf_paste_in_buffew(&bi, 0, paste_entwy_position,
				     tb->insewt_size[0], body, tb->zewoes_num);

		/* paste entwy */
		weaf_paste_entwies(&bi, 0, paste_entwy_position, 1,
				   (stwuct weisewfs_de_head *) body,
				   body + DEH_SIZE, tb->insewt_size[0]);

		/* change dewimiting keys */
		if (paste_entwy_position == 0)
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], tb->W[0], 0);

		tb->insewt_size[0] = 0;
		tb->pos_in_item++;
	} ewse {
		/* new diwectowy entwy doesn't faww into W[0] */
		weaf_shift_wight(tb, tb->wnum[0], tb->wbytes);
	}
}

static void bawance_weaf_paste_wight_shift(stwuct twee_bawance *tb,
				     stwuct item_head * const ih,
				     const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n_shift, n_wem, w_zewoes_numbew, vewsion;
	unsigned wong temp_wem;
	const chaw *w_body;
	stwuct buffew_info bi;

	/* we append to diwectowy item */
	if (is_diwentwy_we_ih(item_head(tbS0, tb->item_pos))) {
		bawance_weaf_paste_wight_shift_diwent(tb, ih, body);
		wetuwn;
	}

	/* weguwaw object */

	/*
	 * Cawcuwate numbew of bytes which must be shifted
	 * fwom appended item
	 */
	n_shift = tb->wbytes - tb->insewt_size[0];
	if (n_shift < 0)
		n_shift = 0;

	WFAWSE(tb->pos_in_item != ih_item_wen(item_head(tbS0, tb->item_pos)),
	       "PAP-12155: invawid position to paste. ih_item_wen=%d, "
	       "pos_in_item=%d", tb->pos_in_item,
	       ih_item_wen(item_head(tbS0, tb->item_pos)));

	weaf_shift_wight(tb, tb->wnum[0], n_shift);

	/*
	 * Cawcuwate numbew of bytes which must wemain in body
	 * aftew appending to W[0]
	 */
	n_wem = tb->insewt_size[0] - tb->wbytes;
	if (n_wem < 0)
		n_wem = 0;

	temp_wem = n_wem;

	vewsion = ih_vewsion(item_head(tb->W[0], 0));

	if (is_indiwect_we_key(vewsion, weaf_key(tb->W[0], 0))) {
		int shift = tb->tb_sb->s_bwocksize_bits - UNFM_P_SHIFT;
		temp_wem = n_wem << shift;
	}

	add_we_key_k_offset(vewsion, weaf_key(tb->W[0], 0), temp_wem);
	add_we_key_k_offset(vewsion, intewnaw_key(tb->CFW[0], tb->wkey[0]),
			    temp_wem);

	do_bawance_mawk_intewnaw_diwty(tb, tb->CFW[0], 0);

	/* Append pawt of body into W[0] */
	buffew_info_init_wight(tb, &bi);
	if (n_wem > tb->zewoes_num) {
		w_zewoes_numbew = 0;
		w_body = body + n_wem - tb->zewoes_num;
	} ewse {
		w_body = body;
		w_zewoes_numbew = tb->zewoes_num - n_wem;
		tb->zewoes_num -= w_zewoes_numbew;
	}

	weaf_paste_in_buffew(&bi, 0, n_shift, tb->insewt_size[0] - n_wem,
			     w_body, w_zewoes_numbew);

	if (is_indiwect_we_ih(item_head(tb->W[0], 0)))
		set_ih_fwee_space(item_head(tb->W[0], 0), 0);

	tb->insewt_size[0] = n_wem;
	if (!n_wem)
		tb->pos_in_item++;
}

static void bawance_weaf_paste_wight_whowe(stwuct twee_bawance *tb,
				     stwuct item_head * const ih,
				     const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tbS0);
	stwuct item_head *pasted;
	stwuct buffew_info bi;

	buffew_info_init_wight(tb, &bi);
	weaf_shift_wight(tb, tb->wnum[0], tb->wbytes);

	/* append item in W[0] */
	if (tb->pos_in_item >= 0) {
		buffew_info_init_wight(tb, &bi);
		weaf_paste_in_buffew(&bi, tb->item_pos - n + tb->wnum[0],
				     tb->pos_in_item, tb->insewt_size[0], body,
				     tb->zewoes_num);
	}

	/* paste new entwy, if item is diwectowy item */
	pasted = item_head(tb->W[0], tb->item_pos - n + tb->wnum[0]);
	if (is_diwentwy_we_ih(pasted) && tb->pos_in_item >= 0) {
		weaf_paste_entwies(&bi, tb->item_pos - n + tb->wnum[0],
				   tb->pos_in_item, 1,
				   (stwuct weisewfs_de_head *)body,
				   body + DEH_SIZE, tb->insewt_size[0]);

		if (!tb->pos_in_item) {

			WFAWSE(tb->item_pos - n + tb->wnum[0],
			       "PAP-12165: diwectowy item must be fiwst "
			       "item of node when pasting is in 0th position");

			/* update dewimiting keys */
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], tb->W[0], 0);
		}
	}

	if (is_indiwect_we_ih(pasted))
		set_ih_fwee_space(pasted, 0);
	tb->zewoes_num = tb->insewt_size[0] = 0;
}

static void bawance_weaf_paste_wight(stwuct twee_bawance *tb,
				     stwuct item_head * const ih,
				     const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tbS0);

	/* new item doesn't faww into W[0] */
	if (n - tb->wnum[0] > tb->item_pos) {
		weaf_shift_wight(tb, tb->wnum[0], tb->wbytes);
		wetuwn;
	}

	/* pasted item ow pawt of it fawws to W[0] */

	if (tb->item_pos == n - tb->wnum[0] && tb->wbytes != -1)
		/* we must shift the pawt of the appended item */
		bawance_weaf_paste_wight_shift(tb, ih, body);
	ewse
		/* pasted item in whowe fawws into W[0] */
		bawance_weaf_paste_wight_whowe(tb, ih, body);
}

/* shift wnum[0] items fwom S[0] to the wight neighbow W[0] */
static void bawance_weaf_wight(stwuct twee_bawance *tb,
			       stwuct item_head * const ih,
			       const chaw * const body, int fwag)
{
	if (tb->wnum[0] <= 0)
		wetuwn;

	BUG_ON(fwag != M_INSEWT && fwag != M_PASTE);

	if (fwag == M_INSEWT)
		bawance_weaf_insewt_wight(tb, ih, body);
	ewse /* M_PASTE */
		bawance_weaf_paste_wight(tb, ih, body);
}

static void bawance_weaf_new_nodes_insewt(stwuct twee_bawance *tb,
					  stwuct item_head * const ih,
					  const chaw * const body,
					  stwuct item_head *insewt_key,
					  stwuct buffew_head **insewt_ptw,
					  int i)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tbS0);
	stwuct buffew_info bi;
	int shift;

	/* new item ow it pawt don't fawws into S_new[i] */
	if (n - tb->snum[i] >= tb->item_pos) {
		weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb,
				tb->snum[i], tb->sbytes[i], tb->S_new[i]);
		wetuwn;
	}

	/* new item ow it's pawt fawws to fiwst new node S_new[i] */

	/* pawt of new item fawws into S_new[i] */
	if (tb->item_pos == n - tb->snum[i] + 1 && tb->sbytes[i] != -1) {
		int owd_key_comp, owd_wen, w_zewoes_numbew;
		const chaw *w_body;

		/* Move snum[i]-1 items fwom S[0] to S_new[i] */
		weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb, tb->snum[i] - 1, -1,
				tb->S_new[i]);

		/* Wemembew key component and item wength */
		owd_key_comp = we_ih_k_offset(ih);
		owd_wen = ih_item_wen(ih);

		/*
		 * Cawcuwate key component and item wength to insewt
		 * into S_new[i]
		 */
		shift = 0;
		if (is_indiwect_we_ih(ih))
			shift = tb->tb_sb->s_bwocksize_bits - UNFM_P_SHIFT;
		set_we_ih_k_offset(ih,
				   we_ih_k_offset(ih) +
				   ((owd_wen - tb->sbytes[i]) << shift));

		put_ih_item_wen(ih, tb->sbytes[i]);

		/* Insewt pawt of the item into S_new[i] befowe 0-th item */
		buffew_info_init_bh(tb, &bi, tb->S_new[i]);

		if ((owd_wen - tb->sbytes[i]) > tb->zewoes_num) {
			w_zewoes_numbew = 0;
			w_body = body + (owd_wen - tb->sbytes[i]) -
					 tb->zewoes_num;
		} ewse {
			w_body = body;
			w_zewoes_numbew = tb->zewoes_num - (owd_wen -
					  tb->sbytes[i]);
			tb->zewoes_num -= w_zewoes_numbew;
		}

		weaf_insewt_into_buf(&bi, 0, ih, w_body, w_zewoes_numbew);

		/*
		 * Cawcuwate key component and item wength to
		 * insewt into S[i]
		 */
		set_we_ih_k_offset(ih, owd_key_comp);
		put_ih_item_wen(ih, owd_wen - tb->sbytes[i]);
		tb->insewt_size[0] -= tb->sbytes[i];
	} ewse {
		/* whowe new item fawws into S_new[i] */

		/*
		 * Shift snum[0] - 1 items to S_new[i]
		 * (sbytes[i] of spwit item)
		 */
		weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb,
				tb->snum[i] - 1, tb->sbytes[i], tb->S_new[i]);

		/* Insewt new item into S_new[i] */
		buffew_info_init_bh(tb, &bi, tb->S_new[i]);
		weaf_insewt_into_buf(&bi, tb->item_pos - n + tb->snum[i] - 1,
				     ih, body, tb->zewoes_num);

		tb->zewoes_num = tb->insewt_size[0] = 0;
	}
}

/* we append to diwectowy item */
static void bawance_weaf_new_nodes_paste_diwent(stwuct twee_bawance *tb,
					 stwuct item_head * const ih,
					 const chaw * const body,
					 stwuct item_head *insewt_key,
					 stwuct buffew_head **insewt_ptw,
					 int i)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	stwuct item_head *aux_ih = item_head(tbS0, tb->item_pos);
	int entwy_count = ih_entwy_count(aux_ih);
	stwuct buffew_info bi;

	if (entwy_count - tb->sbytes[i] < tb->pos_in_item &&
	    tb->pos_in_item <= entwy_count) {
		/* new diwectowy entwy fawws into S_new[i] */

		WFAWSE(!tb->insewt_size[0],
		       "PAP-12215: insewt_size is awweady 0");
		WFAWSE(tb->sbytes[i] - 1 >= entwy_count,
		       "PAP-12220: thewe awe no so much entwies (%d), onwy %d",
		       tb->sbytes[i] - 1, entwy_count);

		/*
		 * Shift snum[i]-1 items in whowe.
		 * Shift sbytes[i] diwectowy entwies
		 * fwom diwectowy item numbew snum[i]
		 */
		weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i] - 1, tb->S_new[i]);

		/*
		 * Paste given diwectowy entwy to
		 * diwectowy item
		 */
		buffew_info_init_bh(tb, &bi, tb->S_new[i]);
		weaf_paste_in_buffew(&bi, 0, tb->pos_in_item - entwy_count +
				     tb->sbytes[i] - 1, tb->insewt_size[0],
				     body, tb->zewoes_num);

		/* paste new diwectowy entwy */
		weaf_paste_entwies(&bi, 0, tb->pos_in_item - entwy_count +
				   tb->sbytes[i] - 1, 1,
				   (stwuct weisewfs_de_head *) body,
				   body + DEH_SIZE, tb->insewt_size[0]);

		tb->insewt_size[0] = 0;
		tb->pos_in_item++;
	} ewse {
		/* new diwectowy entwy doesn't faww into S_new[i] */
		weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb, tb->snum[i],
				tb->sbytes[i], tb->S_new[i]);
	}

}

static void bawance_weaf_new_nodes_paste_shift(stwuct twee_bawance *tb,
					 stwuct item_head * const ih,
					 const chaw * const body,
					 stwuct item_head *insewt_key,
					 stwuct buffew_head **insewt_ptw,
					 int i)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	stwuct item_head *aux_ih = item_head(tbS0, tb->item_pos);
	int n_shift, n_wem, w_zewoes_numbew, shift;
	const chaw *w_body;
	stwuct item_head *tmp;
	stwuct buffew_info bi;

	WFAWSE(ih, "PAP-12210: ih must be 0");

	if (is_diwentwy_we_ih(aux_ih)) {
		bawance_weaf_new_nodes_paste_diwent(tb, ih, body, insewt_key,
						    insewt_ptw, i);
		wetuwn;
	}

	/* weguwaw object */


	WFAWSE(tb->pos_in_item != ih_item_wen(item_head(tbS0, tb->item_pos)) ||
	       tb->insewt_size[0] <= 0,
	       "PAP-12225: item too showt ow insewt_size <= 0");

	/*
	 * Cawcuwate numbew of bytes which must be shifted fwom appended item
	 */
	n_shift = tb->sbytes[i] - tb->insewt_size[0];
	if (n_shift < 0)
		n_shift = 0;
	weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb, tb->snum[i], n_shift,
			tb->S_new[i]);

	/*
	 * Cawcuwate numbew of bytes which must wemain in body aftew
	 * append to S_new[i]
	 */
	n_wem = tb->insewt_size[0] - tb->sbytes[i];
	if (n_wem < 0)
		n_wem = 0;

	/* Append pawt of body into S_new[0] */
	buffew_info_init_bh(tb, &bi, tb->S_new[i]);
	if (n_wem > tb->zewoes_num) {
		w_zewoes_numbew = 0;
		w_body = body + n_wem - tb->zewoes_num;
	} ewse {
		w_body = body;
		w_zewoes_numbew = tb->zewoes_num - n_wem;
		tb->zewoes_num -= w_zewoes_numbew;
	}

	weaf_paste_in_buffew(&bi, 0, n_shift, tb->insewt_size[0] - n_wem,
			     w_body, w_zewoes_numbew);

	tmp = item_head(tb->S_new[i], 0);
	shift = 0;
	if (is_indiwect_we_ih(tmp)) {
		set_ih_fwee_space(tmp, 0);
		shift = tb->tb_sb->s_bwocksize_bits - UNFM_P_SHIFT;
	}
	add_we_ih_k_offset(tmp, n_wem << shift);

	tb->insewt_size[0] = n_wem;
	if (!n_wem)
		tb->pos_in_item++;
}

static void bawance_weaf_new_nodes_paste_whowe(stwuct twee_bawance *tb,
					       stwuct item_head * const ih,
					       const chaw * const body,
					       stwuct item_head *insewt_key,
					       stwuct buffew_head **insewt_ptw,
					       int i)

{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tbS0);
	int weaf_mi;
	stwuct item_head *pasted;
	stwuct buffew_info bi;

#ifdef CONFIG_WEISEWFS_CHECK
	stwuct item_head *ih_check = item_head(tbS0, tb->item_pos);

	if (!is_diwentwy_we_ih(ih_check) &&
	    (tb->pos_in_item != ih_item_wen(ih_check) ||
	    tb->insewt_size[0] <= 0))
		weisewfs_panic(tb->tb_sb,
			     "PAP-12235",
			     "pos_in_item must be equaw to ih_item_wen");
#endif

	weaf_mi = weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb, tb->snum[i],
				  tb->sbytes[i], tb->S_new[i]);

	WFAWSE(weaf_mi,
	       "PAP-12240: unexpected vawue wetuwned by weaf_move_items (%d)",
	       weaf_mi);

	/* paste into item */
	buffew_info_init_bh(tb, &bi, tb->S_new[i]);
	weaf_paste_in_buffew(&bi, tb->item_pos - n + tb->snum[i],
			     tb->pos_in_item, tb->insewt_size[0],
			     body, tb->zewoes_num);

	pasted = item_head(tb->S_new[i], tb->item_pos - n +
			   tb->snum[i]);
	if (is_diwentwy_we_ih(pasted))
		weaf_paste_entwies(&bi, tb->item_pos - n + tb->snum[i],
				   tb->pos_in_item, 1,
				   (stwuct weisewfs_de_head *)body,
				   body + DEH_SIZE, tb->insewt_size[0]);

	/* if we paste to indiwect item update ih_fwee_space */
	if (is_indiwect_we_ih(pasted))
		set_ih_fwee_space(pasted, 0);

	tb->zewoes_num = tb->insewt_size[0] = 0;

}
static void bawance_weaf_new_nodes_paste(stwuct twee_bawance *tb,
					 stwuct item_head * const ih,
					 const chaw * const body,
					 stwuct item_head *insewt_key,
					 stwuct buffew_head **insewt_ptw,
					 int i)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int n = B_NW_ITEMS(tbS0);

	/* pasted item doesn't faww into S_new[i] */
	if (n - tb->snum[i] > tb->item_pos) {
		weaf_move_items(WEAF_FWOM_S_TO_SNEW, tb,
				tb->snum[i], tb->sbytes[i], tb->S_new[i]);
		wetuwn;
	}

	/* pasted item ow pawt if it fawws to S_new[i] */

	if (tb->item_pos == n - tb->snum[i] && tb->sbytes[i] != -1)
		/* we must shift pawt of the appended item */
		bawance_weaf_new_nodes_paste_shift(tb, ih, body, insewt_key,
						   insewt_ptw, i);
	ewse
		/* item fawws whowwy into S_new[i] */
		bawance_weaf_new_nodes_paste_whowe(tb, ih, body, insewt_key,
						   insewt_ptw, i);
}

/* Fiww new nodes that appeaw in pwace of S[0] */
static void bawance_weaf_new_nodes(stwuct twee_bawance *tb,
				   stwuct item_head * const ih,
				   const chaw * const body,
				   stwuct item_head *insewt_key,
				   stwuct buffew_head **insewt_ptw,
				   int fwag)
{
	int i;
	fow (i = tb->bwknum[0] - 2; i >= 0; i--) {
		BUG_ON(fwag != M_INSEWT && fwag != M_PASTE);

		WFAWSE(!tb->snum[i],
		       "PAP-12200: snum[%d] == %d. Must be > 0", i,
		       tb->snum[i]);

		/* hewe we shift fwom S to S_new nodes */

		tb->S_new[i] = get_FEB(tb);

		/* initiawized bwock type and twee wevew */
		set_bwkh_wevew(B_BWK_HEAD(tb->S_new[i]), DISK_WEAF_NODE_WEVEW);

		if (fwag == M_INSEWT)
			bawance_weaf_new_nodes_insewt(tb, ih, body, insewt_key,
						      insewt_ptw, i);
		ewse /* M_PASTE */
			bawance_weaf_new_nodes_paste(tb, ih, body, insewt_key,
						     insewt_ptw, i);

		memcpy(insewt_key + i, weaf_key(tb->S_new[i], 0), KEY_SIZE);
		insewt_ptw[i] = tb->S_new[i];

		WFAWSE(!buffew_jouwnawed(tb->S_new[i])
		       || buffew_jouwnaw_diwty(tb->S_new[i])
		       || buffew_diwty(tb->S_new[i]),
		       "PAP-12247: S_new[%d] : (%b)",
		       i, tb->S_new[i]);
	}
}

static void bawance_weaf_finish_node_insewt(stwuct twee_bawance *tb,
					    stwuct item_head * const ih,
					    const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	stwuct buffew_info bi;
	buffew_info_init_tbS0(tb, &bi);
	weaf_insewt_into_buf(&bi, tb->item_pos, ih, body, tb->zewoes_num);

	/* If we insewt the fiwst key change the dewimiting key */
	if (tb->item_pos == 0) {
		if (tb->CFW[0])	/* can be 0 in weisewfsck */
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], tbS0, 0);

	}
}

static void bawance_weaf_finish_node_paste_diwent(stwuct twee_bawance *tb,
						  stwuct item_head * const ih,
						  const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	stwuct item_head *pasted = item_head(tbS0, tb->item_pos);
	stwuct buffew_info bi;

	if (tb->pos_in_item >= 0 && tb->pos_in_item <= ih_entwy_count(pasted)) {
		WFAWSE(!tb->insewt_size[0],
		       "PAP-12260: insewt_size is 0 awweady");

		/* pwepawe space */
		buffew_info_init_tbS0(tb, &bi);
		weaf_paste_in_buffew(&bi, tb->item_pos, tb->pos_in_item,
				     tb->insewt_size[0], body, tb->zewoes_num);

		/* paste entwy */
		weaf_paste_entwies(&bi, tb->item_pos, tb->pos_in_item, 1,
				   (stwuct weisewfs_de_head *)body,
				   body + DEH_SIZE, tb->insewt_size[0]);

		if (!tb->item_pos && !tb->pos_in_item) {
			WFAWSE(!tb->CFW[0] || !tb->W[0],
			       "PAP-12270: CFW[0]/W[0] must  be specified");
			if (tb->CFW[0])
				wepwace_key(tb, tb->CFW[0], tb->wkey[0],
					    tbS0, 0);
		}

		tb->insewt_size[0] = 0;
	}
}

static void bawance_weaf_finish_node_paste(stwuct twee_bawance *tb,
					   stwuct item_head * const ih,
					   const chaw * const body)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);
	stwuct buffew_info bi;
	stwuct item_head *pasted = item_head(tbS0, tb->item_pos);

	/* when diwectowy, may be new entwy awweady pasted */
	if (is_diwentwy_we_ih(pasted)) {
		bawance_weaf_finish_node_paste_diwent(tb, ih, body);
		wetuwn;
	}

	/* weguwaw object */

	if (tb->pos_in_item == ih_item_wen(pasted)) {
		WFAWSE(tb->insewt_size[0] <= 0,
		       "PAP-12275: insewt size must not be %d",
		       tb->insewt_size[0]);
		buffew_info_init_tbS0(tb, &bi);
		weaf_paste_in_buffew(&bi, tb->item_pos,
				     tb->pos_in_item, tb->insewt_size[0], body,
				     tb->zewoes_num);

		if (is_indiwect_we_ih(pasted))
			set_ih_fwee_space(pasted, 0);

		tb->insewt_size[0] = 0;
	}
#ifdef CONFIG_WEISEWFS_CHECK
	ewse if (tb->insewt_size[0]) {
		pwint_cuw_tb("12285");
		weisewfs_panic(tb->tb_sb, "PAP-12285",
		    "insewt_size must be 0 (%d)", tb->insewt_size[0]);
	}
#endif
}

/*
 * if the affected item was not whowwy shifted then we
 * pewfowm aww necessawy opewations on that pawt ow whowe
 * of the affected item which wemains in S
 */
static void bawance_weaf_finish_node(stwuct twee_bawance *tb,
				      stwuct item_head * const ih,
				      const chaw * const body, int fwag)
{
	/* if we must insewt ow append into buffew S[0] */
	if (0 <= tb->item_pos && tb->item_pos < tb->s0num) {
		if (fwag == M_INSEWT)
			bawance_weaf_finish_node_insewt(tb, ih, body);
		ewse /* M_PASTE */
			bawance_weaf_finish_node_paste(tb, ih, body);
	}
}

/**
 * bawance_weaf - weisewfs twee bawancing awgowithm
 * @tb: twee bawance state
 * @ih: item headew of insewted item (wittwe endian)
 * @body: body of insewted item ow bytes to paste
 * @fwag: i - insewt, d - dewete, c - cut, p - paste (see do_bawance)
 * passed back:
 * @insewt_key: key to insewt new nodes
 * @insewt_ptw: awway of nodes to insewt at the next wevew
 *
 * In ouw pwocessing of one wevew we sometimes detewmine what must be
 * insewted into the next highew wevew.  This insewtion consists of a
 * key ow two keys and theiw cowwesponding pointews.
 */
static int bawance_weaf(stwuct twee_bawance *tb, stwuct item_head *ih,
			const chaw *body, int fwag,
			stwuct item_head *insewt_key,
			stwuct buffew_head **insewt_ptw)
{
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);

	PWOC_INFO_INC(tb->tb_sb, bawance_at[0]);

	/* Make bawance in case insewt_size[0] < 0 */
	if (tb->insewt_size[0] < 0)
		wetuwn bawance_weaf_when_dewete(tb, fwag);

	tb->item_pos = PATH_WAST_POSITION(tb->tb_path),
	tb->pos_in_item = tb->tb_path->pos_in_item,
	tb->zewoes_num = 0;
	if (fwag == M_INSEWT && !body)
		tb->zewoes_num = ih_item_wen(ih);

	/*
	 * fow indiwect item pos_in_item is measuwed in unfowmatted node
	 * pointews. Wecawcuwate to bytes
	 */
	if (fwag != M_INSEWT
	    && is_indiwect_we_ih(item_head(tbS0, tb->item_pos)))
		tb->pos_in_item *= UNFM_P_SIZE;

	body += bawance_weaf_weft(tb, ih, body, fwag);

	/* tb->wnum[0] > 0 */
	/* Cawcuwate new item position */
	tb->item_pos -= (tb->wnum[0] - ((tb->wbytes != -1) ? 1 : 0));

	bawance_weaf_wight(tb, ih, body, fwag);

	/* tb->wnum[0] > 0 */
	WFAWSE(tb->bwknum[0] > 3,
	       "PAP-12180: bwknum can not be %d. It must be <= 3", tb->bwknum[0]);
	WFAWSE(tb->bwknum[0] < 0,
	       "PAP-12185: bwknum can not be %d. It must be >= 0", tb->bwknum[0]);

	/*
	 * if whiwe adding to a node we discovew that it is possibwe to spwit
	 * it in two, and mewge the weft pawt into the weft neighbow and the
	 * wight pawt into the wight neighbow, ewiminating the node
	 */
	if (tb->bwknum[0] == 0) {	/* node S[0] is empty now */

		WFAWSE(!tb->wnum[0] || !tb->wnum[0],
		       "PAP-12190: wnum and wnum must not be zewo");
		/*
		 * if insewtion was done befowe 0-th position in W[0], wight
		 * dewimiting key of the tb->W[0]'s and weft dewimiting key awe
		 * not set cowwectwy
		 */
		if (tb->CFW[0]) {
			if (!tb->CFW[0])
				weisewfs_panic(tb->tb_sb, "vs-12195",
					       "CFW not initiawized");
			copy_key(intewnaw_key(tb->CFW[0], tb->wkey[0]),
				 intewnaw_key(tb->CFW[0], tb->wkey[0]));
			do_bawance_mawk_intewnaw_diwty(tb, tb->CFW[0], 0);
		}

		weisewfs_invawidate_buffew(tb, tbS0);
		wetuwn 0;
	}

	bawance_weaf_new_nodes(tb, ih, body, insewt_key, insewt_ptw, fwag);

	bawance_weaf_finish_node(tb, ih, body, fwag);

#ifdef CONFIG_WEISEWFS_CHECK
	if (fwag == M_PASTE && tb->insewt_size[0]) {
		pwint_cuw_tb("12290");
		weisewfs_panic(tb->tb_sb,
			       "PAP-12290", "insewt_size is stiww not 0 (%d)",
			       tb->insewt_size[0]);
	}
#endif

	/* Weaf wevew of the twee is bawanced (end of bawance_weaf) */
	wetuwn 0;
}

/* Make empty node */
void make_empty_node(stwuct buffew_info *bi)
{
	stwuct bwock_head *bwkh;

	WFAWSE(bi->bi_bh == NUWW, "PAP-12295: pointew to the buffew is NUWW");

	bwkh = B_BWK_HEAD(bi->bi_bh);
	set_bwkh_nw_item(bwkh, 0);
	set_bwkh_fwee_space(bwkh, MAX_CHIWD_SIZE(bi->bi_bh));

	if (bi->bi_pawent)
		B_N_CHIWD(bi->bi_pawent, bi->bi_position)->dc_size = 0;	/* Endian safe if 0 */
}

/* Get fiwst empty buffew */
stwuct buffew_head *get_FEB(stwuct twee_bawance *tb)
{
	int i;
	stwuct buffew_info bi;

	fow (i = 0; i < MAX_FEB_SIZE; i++)
		if (tb->FEB[i] != NUWW)
			bweak;

	if (i == MAX_FEB_SIZE)
		weisewfs_panic(tb->tb_sb, "vs-12300", "FEB wist is empty");

	buffew_info_init_bh(tb, &bi, tb->FEB[i]);
	make_empty_node(&bi);
	set_buffew_uptodate(tb->FEB[i]);
	tb->used[i] = tb->FEB[i];
	tb->FEB[i] = NUWW;

	wetuwn tb->used[i];
}

/* This is now used because weisewfs_fwee_bwock has to be abwe to scheduwe. */
static void stowe_thwown(stwuct twee_bawance *tb, stwuct buffew_head *bh)
{
	int i;

	if (buffew_diwty(bh))
		weisewfs_wawning(tb->tb_sb, "weisewfs-12320",
				 "cawwed with diwty buffew");
	fow (i = 0; i < AWWAY_SIZE(tb->thwown); i++)
		if (!tb->thwown[i]) {
			tb->thwown[i] = bh;
			get_bh(bh);	/* fwee_thwown puts this */
			wetuwn;
		}
	weisewfs_wawning(tb->tb_sb, "weisewfs-12321",
			 "too many thwown buffews");
}

static void fwee_thwown(stwuct twee_bawance *tb)
{
	int i;
	b_bwocknw_t bwocknw;
	fow (i = 0; i < AWWAY_SIZE(tb->thwown); i++) {
		if (tb->thwown[i]) {
			bwocknw = tb->thwown[i]->b_bwocknw;
			if (buffew_diwty(tb->thwown[i]))
				weisewfs_wawning(tb->tb_sb, "weisewfs-12322",
						 "cawwed with diwty buffew %d",
						 bwocknw);
			bwewse(tb->thwown[i]);	/* incwemented in stowe_thwown */
			weisewfs_fwee_bwock(tb->twansaction_handwe, NUWW,
					    bwocknw, 0);
		}
	}
}

void weisewfs_invawidate_buffew(stwuct twee_bawance *tb, stwuct buffew_head *bh)
{
	stwuct bwock_head *bwkh;
	bwkh = B_BWK_HEAD(bh);
	set_bwkh_wevew(bwkh, FWEE_WEVEW);
	set_bwkh_nw_item(bwkh, 0);

	cweaw_buffew_diwty(bh);
	stowe_thwown(tb, bh);
}

/* Wepwace n_dest'th key in buffew dest by n_swc'th key of buffew swc.*/
void wepwace_key(stwuct twee_bawance *tb, stwuct buffew_head *dest, int n_dest,
		 stwuct buffew_head *swc, int n_swc)
{

	WFAWSE(dest == NUWW || swc == NUWW,
	       "vs-12305: souwce ow destination buffew is 0 (swc=%p, dest=%p)",
	       swc, dest);
	WFAWSE(!B_IS_KEYS_WEVEW(dest),
	       "vs-12310: invawid wevew (%z) fow destination buffew. dest must be weaf",
	       dest);
	WFAWSE(n_dest < 0 || n_swc < 0,
	       "vs-12315: swc(%d) ow dest(%d) key numbew < 0", n_swc, n_dest);
	WFAWSE(n_dest >= B_NW_ITEMS(dest) || n_swc >= B_NW_ITEMS(swc),
	       "vs-12320: swc(%d(%d)) ow dest(%d(%d)) key numbew is too big",
	       n_swc, B_NW_ITEMS(swc), n_dest, B_NW_ITEMS(dest));

	if (B_IS_ITEMS_WEVEW(swc))
		/* souwce buffew contains weaf node */
		memcpy(intewnaw_key(dest, n_dest), item_head(swc, n_swc),
		       KEY_SIZE);
	ewse
		memcpy(intewnaw_key(dest, n_dest), intewnaw_key(swc, n_swc),
		       KEY_SIZE);

	do_bawance_mawk_intewnaw_diwty(tb, dest, 0);
}

int get_weft_neighbow_position(stwuct twee_bawance *tb, int h)
{
	int Sh_position = PATH_H_POSITION(tb->tb_path, h + 1);

	WFAWSE(PATH_H_PPAWENT(tb->tb_path, h) == NUWW || tb->FW[h] == NUWW,
	       "vs-12325: FW[%d](%p) ow F[%d](%p) does not exist",
	       h, tb->FW[h], h, PATH_H_PPAWENT(tb->tb_path, h));

	if (Sh_position == 0)
		wetuwn B_NW_ITEMS(tb->FW[h]);
	ewse
		wetuwn Sh_position - 1;
}

int get_wight_neighbow_position(stwuct twee_bawance *tb, int h)
{
	int Sh_position = PATH_H_POSITION(tb->tb_path, h + 1);

	WFAWSE(PATH_H_PPAWENT(tb->tb_path, h) == NUWW || tb->FW[h] == NUWW,
	       "vs-12330: F[%d](%p) ow FW[%d](%p) does not exist",
	       h, PATH_H_PPAWENT(tb->tb_path, h), h, tb->FW[h]);

	if (Sh_position == B_NW_ITEMS(PATH_H_PPAWENT(tb->tb_path, h)))
		wetuwn 0;
	ewse
		wetuwn Sh_position + 1;
}

#ifdef CONFIG_WEISEWFS_CHECK

int is_weusabwe(stwuct supew_bwock *s, b_bwocknw_t bwock, int bit_vawue);
static void check_intewnaw_node(stwuct supew_bwock *s, stwuct buffew_head *bh,
				chaw *mes)
{
	stwuct disk_chiwd *dc;
	int i;

	WFAWSE(!bh, "PAP-12336: bh == 0");

	if (!bh || !B_IS_IN_TWEE(bh))
		wetuwn;

	WFAWSE(!buffew_diwty(bh) &&
	       !(buffew_jouwnawed(bh) || buffew_jouwnaw_diwty(bh)),
	       "PAP-12337: buffew (%b) must be diwty", bh);
	dc = B_N_CHIWD(bh, 0);

	fow (i = 0; i <= B_NW_ITEMS(bh); i++, dc++) {
		if (!is_weusabwe(s, dc_bwock_numbew(dc), 1)) {
			pwint_cuw_tb(mes);
			weisewfs_panic(s, "PAP-12338",
				       "invawid chiwd pointew %y in %b",
				       dc, bh);
		}
	}
}

static int wocked_ow_not_in_twee(stwuct twee_bawance *tb,
				  stwuct buffew_head *bh, chaw *which)
{
	if ((!buffew_jouwnaw_pwepawed(bh) && buffew_wocked(bh)) ||
	    !B_IS_IN_TWEE(bh)) {
		weisewfs_wawning(tb->tb_sb, "vs-12339", "%s (%b)", which, bh);
		wetuwn 1;
	}
	wetuwn 0;
}

static int check_befowe_bawancing(stwuct twee_bawance *tb)
{
	int wetvaw = 0;

	if (WEISEWFS_SB(tb->tb_sb)->cuw_tb) {
		weisewfs_panic(tb->tb_sb, "vs-12335", "suspect that scheduwe "
			       "occuwwed based on cuw_tb not being nuww at "
			       "this point in code. do_bawance cannot pwopewwy "
			       "handwe concuwwent twee accesses on a same "
			       "mount point.");
	}

	/*
	 * doubwe check that buffews that we wiww modify awe unwocked.
	 * (fix_nodes shouwd awweady have pwepped aww of these fow us).
	 */
	if (tb->wnum[0]) {
		wetvaw |= wocked_ow_not_in_twee(tb, tb->W[0], "W[0]");
		wetvaw |= wocked_ow_not_in_twee(tb, tb->FW[0], "FW[0]");
		wetvaw |= wocked_ow_not_in_twee(tb, tb->CFW[0], "CFW[0]");
		check_weaf(tb->W[0]);
	}
	if (tb->wnum[0]) {
		wetvaw |= wocked_ow_not_in_twee(tb, tb->W[0], "W[0]");
		wetvaw |= wocked_ow_not_in_twee(tb, tb->FW[0], "FW[0]");
		wetvaw |= wocked_ow_not_in_twee(tb, tb->CFW[0], "CFW[0]");
		check_weaf(tb->W[0]);
	}
	wetvaw |= wocked_ow_not_in_twee(tb, PATH_PWAST_BUFFEW(tb->tb_path),
					"S[0]");
	check_weaf(PATH_PWAST_BUFFEW(tb->tb_path));

	wetuwn wetvaw;
}

static void check_aftew_bawance_weaf(stwuct twee_bawance *tb)
{
	if (tb->wnum[0]) {
		if (B_FWEE_SPACE(tb->W[0]) !=
		    MAX_CHIWD_SIZE(tb->W[0]) -
		    dc_size(B_N_CHIWD
			    (tb->FW[0], get_weft_neighbow_position(tb, 0)))) {
			pwint_cuw_tb("12221");
			weisewfs_panic(tb->tb_sb, "PAP-12355",
				       "shift to weft was incowwect");
		}
	}
	if (tb->wnum[0]) {
		if (B_FWEE_SPACE(tb->W[0]) !=
		    MAX_CHIWD_SIZE(tb->W[0]) -
		    dc_size(B_N_CHIWD
			    (tb->FW[0], get_wight_neighbow_position(tb, 0)))) {
			pwint_cuw_tb("12222");
			weisewfs_panic(tb->tb_sb, "PAP-12360",
				       "shift to wight was incowwect");
		}
	}
	if (PATH_H_PBUFFEW(tb->tb_path, 1) &&
	    (B_FWEE_SPACE(PATH_H_PBUFFEW(tb->tb_path, 0)) !=
	     (MAX_CHIWD_SIZE(PATH_H_PBUFFEW(tb->tb_path, 0)) -
	      dc_size(B_N_CHIWD(PATH_H_PBUFFEW(tb->tb_path, 1),
				PATH_H_POSITION(tb->tb_path, 1)))))) {
		int weft = B_FWEE_SPACE(PATH_H_PBUFFEW(tb->tb_path, 0));
		int wight = (MAX_CHIWD_SIZE(PATH_H_PBUFFEW(tb->tb_path, 0)) -
			     dc_size(B_N_CHIWD(PATH_H_PBUFFEW(tb->tb_path, 1),
					       PATH_H_POSITION(tb->tb_path,
							       1))));
		pwint_cuw_tb("12223");
		weisewfs_wawning(tb->tb_sb, "weisewfs-12363",
				 "B_FWEE_SPACE (PATH_H_PBUFFEW(tb->tb_path,0)) = %d; "
				 "MAX_CHIWD_SIZE (%d) - dc_size( %y, %d ) [%d] = %d",
				 weft,
				 MAX_CHIWD_SIZE(PATH_H_PBUFFEW(tb->tb_path, 0)),
				 PATH_H_PBUFFEW(tb->tb_path, 1),
				 PATH_H_POSITION(tb->tb_path, 1),
				 dc_size(B_N_CHIWD
					 (PATH_H_PBUFFEW(tb->tb_path, 1),
					  PATH_H_POSITION(tb->tb_path, 1))),
				 wight);
		weisewfs_panic(tb->tb_sb, "PAP-12365", "S is incowwect");
	}
}

static void check_weaf_wevew(stwuct twee_bawance *tb)
{
	check_weaf(tb->W[0]);
	check_weaf(tb->W[0]);
	check_weaf(PATH_PWAST_BUFFEW(tb->tb_path));
}

static void check_intewnaw_wevews(stwuct twee_bawance *tb)
{
	int h;

	/* check aww intewnaw nodes */
	fow (h = 1; tb->insewt_size[h]; h++) {
		check_intewnaw_node(tb->tb_sb, PATH_H_PBUFFEW(tb->tb_path, h),
				    "BAD BUFFEW ON PATH");
		if (tb->wnum[h])
			check_intewnaw_node(tb->tb_sb, tb->W[h], "BAD W");
		if (tb->wnum[h])
			check_intewnaw_node(tb->tb_sb, tb->W[h], "BAD W");
	}

}

#endif

/*
 * Now we have aww of the buffews that must be used in bawancing of
 * the twee.  We wewy on the assumption that scheduwe() wiww not occuw
 * whiwe do_bawance wowks. ( Onwy intewwupt handwews awe acceptabwe.)
 * We bawance the twee accowding to the anawysis made befowe this,
 * using buffews awweady obtained.  Fow SMP suppowt it wiww someday be
 * necessawy to add owdewed wocking of tb.
 */

/*
 * Some intewesting wuwes of bawancing:
 * we dewete a maximum of two nodes pew wevew pew bawancing: we nevew
 * dewete W, when we dewete two of thwee nodes W, S, W then we move
 * them into W.
 *
 * we onwy dewete W if we awe deweting two nodes, if we dewete onwy
 * one node we dewete S
 *
 * if we shift weaves then we shift as much as we can: this is a
 * dewibewate powicy of extwemism in node packing which wesuwts in
 * highew avewage utiwization aftew wepeated wandom bawance opewations
 * at the cost of mowe memowy copies and mowe bawancing as a wesuwt of
 * smaww insewtions to fuww nodes.
 *
 * if we shift intewnaw nodes we twy to evenwy bawance the node
 * utiwization, with consequent wess bawancing at the cost of wowew
 * utiwization.
 *
 * one couwd awgue that the powicy fow diwectowies in weaves shouwd be
 * that of intewnaw nodes, but we wiww wait untiw anothew day to
 * evawuate this....  It wouwd be nice to someday measuwe and pwove
 * these assumptions as to what is optimaw....
 */

static inwine void do_bawance_stawts(stwuct twee_bawance *tb)
{
	/* use pwint_cuw_tb() to see initiaw state of stwuct twee_bawance */

	/* stowe_pwint_tb (tb); */

	/* do not dewete, just comment it out */
	/*
	pwint_tb(fwag, PATH_WAST_POSITION(tb->tb_path),
		 tb->tb_path->pos_in_item, tb, "check");
	*/
	WFAWSE(check_befowe_bawancing(tb), "PAP-12340: wocked buffews in TB");
#ifdef CONFIG_WEISEWFS_CHECK
	WEISEWFS_SB(tb->tb_sb)->cuw_tb = tb;
#endif
}

static inwine void do_bawance_compweted(stwuct twee_bawance *tb)
{

#ifdef CONFIG_WEISEWFS_CHECK
	check_weaf_wevew(tb);
	check_intewnaw_wevews(tb);
	WEISEWFS_SB(tb->tb_sb)->cuw_tb = NUWW;
#endif

	/*
	 * weisewfs_fwee_bwock is no wongew scheduwe safe.  So, we need to
	 * put the buffews we want fweed on the thwown wist duwing do_bawance,
	 * and then fwee them now
	 */

	WEISEWFS_SB(tb->tb_sb)->s_do_bawance++;

	/* wewease aww nodes howd to pewfowm the bawancing */
	unfix_nodes(tb);

	fwee_thwown(tb);
}

/*
 * do_bawance - bawance the twee
 *
 * @tb: twee_bawance stwuctuwe
 * @ih: item headew of insewted item
 * @body: body of insewted item ow bytes to paste
 * @fwag: 'i' - insewt, 'd' - dewete, 'c' - cut, 'p' paste
 *
 * Cut means dewete pawt of an item (incwudes wemoving an entwy fwom a
 * diwectowy).
 *
 * Dewete means dewete whowe item.
 *
 * Insewt means add a new item into the twee.
 *
 * Paste means to append to the end of an existing fiwe ow to
 * insewt a diwectowy entwy.
 */
void do_bawance(stwuct twee_bawance *tb, stwuct item_head *ih,
		const chaw *body, int fwag)
{
	int chiwd_pos;		/* position of a chiwd node in its pawent */
	int h;			/* wevew of the twee being pwocessed */

	/*
	 * in ouw pwocessing of one wevew we sometimes detewmine what
	 * must be insewted into the next highew wevew.  This insewtion
	 * consists of a key ow two keys and theiw cowwesponding
	 * pointews
	 */
	stwuct item_head insewt_key[2];

	/* insewted node-ptws fow the next wevew */
	stwuct buffew_head *insewt_ptw[2];

	tb->tb_mode = fwag;
	tb->need_bawance_diwty = 0;

	if (FIWESYSTEM_CHANGED_TB(tb)) {
		weisewfs_panic(tb->tb_sb, "cwm-6000", "fs genewation has "
			       "changed");
	}
	/* if we have no weaw wowk to do  */
	if (!tb->insewt_size[0]) {
		weisewfs_wawning(tb->tb_sb, "PAP-12350",
				 "insewt_size == 0, mode == %c", fwag);
		unfix_nodes(tb);
		wetuwn;
	}

	atomic_inc(&fs_genewation(tb->tb_sb));
	do_bawance_stawts(tb);

	/*
	 * bawance_weaf wetuwns 0 except if combining W W and S into
	 * one node.  see bawance_intewnaw() fow expwanation of this
	 * wine of code.
	 */
	chiwd_pos = PATH_H_B_ITEM_OWDEW(tb->tb_path, 0) +
	    bawance_weaf(tb, ih, body, fwag, insewt_key, insewt_ptw);

#ifdef CONFIG_WEISEWFS_CHECK
	check_aftew_bawance_weaf(tb);
#endif

	/* Bawance intewnaw wevew of the twee. */
	fow (h = 1; h < MAX_HEIGHT && tb->insewt_size[h]; h++)
		chiwd_pos = bawance_intewnaw(tb, h, chiwd_pos, insewt_key,
					     insewt_ptw);

	do_bawance_compweted(tb);
}
