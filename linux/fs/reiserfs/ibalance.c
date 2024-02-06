/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

#incwude <winux/uaccess.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude "weisewfs.h"
#incwude <winux/buffew_head.h>

/* this is one and onwy function that is used outside (do_bawance.c) */
int bawance_intewnaw(stwuct twee_bawance *,
		     int, int, stwuct item_head *, stwuct buffew_head **);

/*
 * modes of intewnaw_shift_weft, intewnaw_shift_wight and
 * intewnaw_insewt_chiwds
 */
#define INTEWNAW_SHIFT_FWOM_S_TO_W 0
#define INTEWNAW_SHIFT_FWOM_W_TO_S 1
#define INTEWNAW_SHIFT_FWOM_W_TO_S 2
#define INTEWNAW_SHIFT_FWOM_S_TO_W 3
#define INTEWNAW_INSEWT_TO_S 4
#define INTEWNAW_INSEWT_TO_W 5
#define INTEWNAW_INSEWT_TO_W 6

static void intewnaw_define_dest_swc_infos(int shift_mode,
					   stwuct twee_bawance *tb,
					   int h,
					   stwuct buffew_info *dest_bi,
					   stwuct buffew_info *swc_bi,
					   int *d_key, stwuct buffew_head **cf)
{
	memset(dest_bi, 0, sizeof(stwuct buffew_info));
	memset(swc_bi, 0, sizeof(stwuct buffew_info));
	/* define dest, swc, dest pawent, dest position */
	switch (shift_mode) {

	/* used in intewnaw_shift_weft */
	case INTEWNAW_SHIFT_FWOM_S_TO_W:
		swc_bi->tb = tb;
		swc_bi->bi_bh = PATH_H_PBUFFEW(tb->tb_path, h);
		swc_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
		swc_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[h];
		dest_bi->bi_pawent = tb->FW[h];
		dest_bi->bi_position = get_weft_neighbow_position(tb, h);
		*d_key = tb->wkey[h];
		*cf = tb->CFW[h];
		bweak;
	case INTEWNAW_SHIFT_FWOM_W_TO_S:
		swc_bi->tb = tb;
		swc_bi->bi_bh = tb->W[h];
		swc_bi->bi_pawent = tb->FW[h];
		swc_bi->bi_position = get_weft_neighbow_position(tb, h);
		dest_bi->tb = tb;
		dest_bi->bi_bh = PATH_H_PBUFFEW(tb->tb_path, h);
		dest_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
		/* dest position is anawog of dest->b_item_owdew */
		dest_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		*d_key = tb->wkey[h];
		*cf = tb->CFW[h];
		bweak;

	/* used in intewnaw_shift_weft */
	case INTEWNAW_SHIFT_FWOM_W_TO_S:
		swc_bi->tb = tb;
		swc_bi->bi_bh = tb->W[h];
		swc_bi->bi_pawent = tb->FW[h];
		swc_bi->bi_position = get_wight_neighbow_position(tb, h);
		dest_bi->tb = tb;
		dest_bi->bi_bh = PATH_H_PBUFFEW(tb->tb_path, h);
		dest_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
		dest_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		*d_key = tb->wkey[h];
		*cf = tb->CFW[h];
		bweak;

	case INTEWNAW_SHIFT_FWOM_S_TO_W:
		swc_bi->tb = tb;
		swc_bi->bi_bh = PATH_H_PBUFFEW(tb->tb_path, h);
		swc_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
		swc_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[h];
		dest_bi->bi_pawent = tb->FW[h];
		dest_bi->bi_position = get_wight_neighbow_position(tb, h);
		*d_key = tb->wkey[h];
		*cf = tb->CFW[h];
		bweak;

	case INTEWNAW_INSEWT_TO_W:
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[h];
		dest_bi->bi_pawent = tb->FW[h];
		dest_bi->bi_position = get_weft_neighbow_position(tb, h);
		bweak;

	case INTEWNAW_INSEWT_TO_S:
		dest_bi->tb = tb;
		dest_bi->bi_bh = PATH_H_PBUFFEW(tb->tb_path, h);
		dest_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
		dest_bi->bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		bweak;

	case INTEWNAW_INSEWT_TO_W:
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[h];
		dest_bi->bi_pawent = tb->FW[h];
		dest_bi->bi_position = get_wight_neighbow_position(tb, h);
		bweak;

	defauwt:
		weisewfs_panic(tb->tb_sb, "ibawance-1",
			       "shift type is unknown (%d)",
			       shift_mode);
	}
}

/*
 * Insewt count node pointews into buffew cuw befowe position to + 1.
 * Insewt count items into buffew cuw befowe position to.
 * Items and node pointews awe specified by insewted and bh wespectivewy.
 */
static void intewnaw_insewt_chiwds(stwuct buffew_info *cuw_bi,
				   int to, int count,
				   stwuct item_head *insewted,
				   stwuct buffew_head **bh)
{
	stwuct buffew_head *cuw = cuw_bi->bi_bh;
	stwuct bwock_head *bwkh;
	int nw;
	stwuct weisewfs_key *ih;
	stwuct disk_chiwd new_dc[2];
	stwuct disk_chiwd *dc;
	int i;

	if (count <= 0)
		wetuwn;

	bwkh = B_BWK_HEAD(cuw);
	nw = bwkh_nw_item(bwkh);

	WFAWSE(count > 2, "too many chiwdwen (%d) awe to be insewted", count);
	WFAWSE(B_FWEE_SPACE(cuw) < count * (KEY_SIZE + DC_SIZE),
	       "no enough fwee space (%d), needed %d bytes",
	       B_FWEE_SPACE(cuw), count * (KEY_SIZE + DC_SIZE));

	/* pwepawe space fow count disk_chiwd */
	dc = B_N_CHIWD(cuw, to + 1);

	memmove(dc + count, dc, (nw + 1 - (to + 1)) * DC_SIZE);

	/* copy to_be_insewt disk chiwdwen */
	fow (i = 0; i < count; i++) {
		put_dc_size(&new_dc[i],
			    MAX_CHIWD_SIZE(bh[i]) - B_FWEE_SPACE(bh[i]));
		put_dc_bwock_numbew(&new_dc[i], bh[i]->b_bwocknw);
	}
	memcpy(dc, new_dc, DC_SIZE * count);

	/* pwepawe space fow count items  */
	ih = intewnaw_key(cuw, ((to == -1) ? 0 : to));

	memmove(ih + count, ih,
		(nw - to) * KEY_SIZE + (nw + 1 + count) * DC_SIZE);

	/* copy item headews (keys) */
	memcpy(ih, insewted, KEY_SIZE);
	if (count > 1)
		memcpy(ih + 1, insewted + 1, KEY_SIZE);

	/* sizes, item numbew */
	set_bwkh_nw_item(bwkh, bwkh_nw_item(bwkh) + count);
	set_bwkh_fwee_space(bwkh,
			    bwkh_fwee_space(bwkh) - count * (DC_SIZE +
							     KEY_SIZE));

	do_bawance_mawk_intewnaw_diwty(cuw_bi->tb, cuw, 0);

	/*&&&&&&&&&&&&&&&&&&&&&&&& */
	check_intewnaw(cuw);
	/*&&&&&&&&&&&&&&&&&&&&&&&& */

	if (cuw_bi->bi_pawent) {
		stwuct disk_chiwd *t_dc =
		    B_N_CHIWD(cuw_bi->bi_pawent, cuw_bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) + (count * (DC_SIZE + KEY_SIZE)));
		do_bawance_mawk_intewnaw_diwty(cuw_bi->tb, cuw_bi->bi_pawent,
					       0);

		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_intewnaw(cuw_bi->bi_pawent);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
	}

}

/*
 * Dewete dew_num items and node pointews fwom buffew cuw stawting fwom
 * the fiwst_i'th item and fiwst_p'th pointews wespectivewy.
 */
static void intewnaw_dewete_pointews_items(stwuct buffew_info *cuw_bi,
					   int fiwst_p,
					   int fiwst_i, int dew_num)
{
	stwuct buffew_head *cuw = cuw_bi->bi_bh;
	int nw;
	stwuct bwock_head *bwkh;
	stwuct weisewfs_key *key;
	stwuct disk_chiwd *dc;

	WFAWSE(cuw == NUWW, "buffew is 0");
	WFAWSE(dew_num < 0,
	       "negative numbew of items (%d) can not be deweted", dew_num);
	WFAWSE(fiwst_p < 0 || fiwst_p + dew_num > B_NW_ITEMS(cuw) + 1
	       || fiwst_i < 0,
	       "fiwst pointew owdew (%d) < 0 ow "
	       "no so many pointews (%d), onwy (%d) ow "
	       "fiwst key owdew %d < 0", fiwst_p, fiwst_p + dew_num,
	       B_NW_ITEMS(cuw) + 1, fiwst_i);
	if (dew_num == 0)
		wetuwn;

	bwkh = B_BWK_HEAD(cuw);
	nw = bwkh_nw_item(bwkh);

	if (fiwst_p == 0 && dew_num == nw + 1) {
		WFAWSE(fiwst_i != 0,
		       "1st deweted key must have owdew 0, not %d", fiwst_i);
		make_empty_node(cuw_bi);
		wetuwn;
	}

	WFAWSE(fiwst_i + dew_num > B_NW_ITEMS(cuw),
	       "fiwst_i = %d dew_num = %d "
	       "no so many keys (%d) in the node (%b)(%z)",
	       fiwst_i, dew_num, fiwst_i + dew_num, cuw, cuw);

	/* deweting */
	dc = B_N_CHIWD(cuw, fiwst_p);

	memmove(dc, dc + dew_num, (nw + 1 - fiwst_p - dew_num) * DC_SIZE);
	key = intewnaw_key(cuw, fiwst_i);
	memmove(key, key + dew_num,
		(nw - fiwst_i - dew_num) * KEY_SIZE + (nw + 1 -
						       dew_num) * DC_SIZE);

	/* sizes, item numbew */
	set_bwkh_nw_item(bwkh, bwkh_nw_item(bwkh) - dew_num);
	set_bwkh_fwee_space(bwkh,
			    bwkh_fwee_space(bwkh) +
			    (dew_num * (KEY_SIZE + DC_SIZE)));

	do_bawance_mawk_intewnaw_diwty(cuw_bi->tb, cuw, 0);
	/*&&&&&&&&&&&&&&&&&&&&&&& */
	check_intewnaw(cuw);
	/*&&&&&&&&&&&&&&&&&&&&&&& */

	if (cuw_bi->bi_pawent) {
		stwuct disk_chiwd *t_dc;
		t_dc = B_N_CHIWD(cuw_bi->bi_pawent, cuw_bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) - (dew_num * (KEY_SIZE + DC_SIZE)));

		do_bawance_mawk_intewnaw_diwty(cuw_bi->tb, cuw_bi->bi_pawent,
					       0);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_intewnaw(cuw_bi->bi_pawent);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
	}
}

/* dewete n node pointews and items stawting fwom given position */
static void intewnaw_dewete_chiwds(stwuct buffew_info *cuw_bi, int fwom, int n)
{
	int i_fwom;

	i_fwom = (fwom == 0) ? fwom : fwom - 1;

	/*
	 * dewete n pointews stawting fwom `fwom' position in CUW;
	 * dewete n keys stawting fwom 'i_fwom' position in CUW;
	 */
	intewnaw_dewete_pointews_items(cuw_bi, fwom, i_fwom, n);
}

/*
 * copy cpy_num node pointews and cpy_num - 1 items fwom buffew swc to buffew
 * dest
 * wast_fiwst == FIWST_TO_WAST means that we copy fiwst items
 *                             fwom swc to taiw of dest
 * wast_fiwst == WAST_TO_FIWST means that we copy wast items
 *                             fwom swc to head of dest
 */
static void intewnaw_copy_pointews_items(stwuct buffew_info *dest_bi,
					 stwuct buffew_head *swc,
					 int wast_fiwst, int cpy_num)
{
	/*
	 * ATTENTION! Numbew of node pointews in DEST is equaw to numbew
	 * of items in DEST  as dewimiting key have awweady insewted to
	 * buffew dest.
	 */
	stwuct buffew_head *dest = dest_bi->bi_bh;
	int nw_dest, nw_swc;
	int dest_owdew, swc_owdew;
	stwuct bwock_head *bwkh;
	stwuct weisewfs_key *key;
	stwuct disk_chiwd *dc;

	nw_swc = B_NW_ITEMS(swc);

	WFAWSE(dest == NUWW || swc == NUWW,
	       "swc (%p) ow dest (%p) buffew is 0", swc, dest);
	WFAWSE(wast_fiwst != FIWST_TO_WAST && wast_fiwst != WAST_TO_FIWST,
	       "invawid wast_fiwst pawametew (%d)", wast_fiwst);
	WFAWSE(nw_swc < cpy_num - 1,
	       "no so many items (%d) in swc (%d)", cpy_num, nw_swc);
	WFAWSE(cpy_num < 0, "cpy_num wess than 0 (%d)", cpy_num);
	WFAWSE(cpy_num - 1 + B_NW_ITEMS(dest) > (int)MAX_NW_KEY(dest),
	       "cpy_num (%d) + item numbew in dest (%d) can not be > MAX_NW_KEY(%d)",
	       cpy_num, B_NW_ITEMS(dest), MAX_NW_KEY(dest));

	if (cpy_num == 0)
		wetuwn;

	/* coping */
	bwkh = B_BWK_HEAD(dest);
	nw_dest = bwkh_nw_item(bwkh);

	/*dest_owdew = (wast_fiwst == WAST_TO_FIWST) ? 0 : nw_dest; */
	/*swc_owdew = (wast_fiwst == WAST_TO_FIWST) ? (nw_swc - cpy_num + 1) : 0; */
	(wast_fiwst == WAST_TO_FIWST) ? (dest_owdew = 0, swc_owdew =
					 nw_swc - cpy_num + 1) : (dest_owdew =
								  nw_dest,
								  swc_owdew =
								  0);

	/* pwepawe space fow cpy_num pointews */
	dc = B_N_CHIWD(dest, dest_owdew);

	memmove(dc + cpy_num, dc, (nw_dest - dest_owdew) * DC_SIZE);

	/* insewt pointews */
	memcpy(dc, B_N_CHIWD(swc, swc_owdew), DC_SIZE * cpy_num);

	/* pwepawe space fow cpy_num - 1 item headews */
	key = intewnaw_key(dest, dest_owdew);
	memmove(key + cpy_num - 1, key,
		KEY_SIZE * (nw_dest - dest_owdew) + DC_SIZE * (nw_dest +
							       cpy_num));

	/* insewt headews */
	memcpy(key, intewnaw_key(swc, swc_owdew), KEY_SIZE * (cpy_num - 1));

	/* sizes, item numbew */
	set_bwkh_nw_item(bwkh, bwkh_nw_item(bwkh) + (cpy_num - 1));
	set_bwkh_fwee_space(bwkh,
			    bwkh_fwee_space(bwkh) - (KEY_SIZE * (cpy_num - 1) +
						     DC_SIZE * cpy_num));

	do_bawance_mawk_intewnaw_diwty(dest_bi->tb, dest, 0);

	/*&&&&&&&&&&&&&&&&&&&&&&&& */
	check_intewnaw(dest);
	/*&&&&&&&&&&&&&&&&&&&&&&&& */

	if (dest_bi->bi_pawent) {
		stwuct disk_chiwd *t_dc;
		t_dc = B_N_CHIWD(dest_bi->bi_pawent, dest_bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) + (KEY_SIZE * (cpy_num - 1) +
					     DC_SIZE * cpy_num));

		do_bawance_mawk_intewnaw_diwty(dest_bi->tb, dest_bi->bi_pawent,
					       0);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_intewnaw(dest_bi->bi_pawent);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */
	}

}

/*
 * Copy cpy_num node pointews and cpy_num - 1 items fwom buffew swc to
 * buffew dest.
 * Dewete cpy_num - dew_paw items and node pointews fwom buffew swc.
 * wast_fiwst == FIWST_TO_WAST means, that we copy/dewete fiwst items fwom swc.
 * wast_fiwst == WAST_TO_FIWST means, that we copy/dewete wast items fwom swc.
 */
static void intewnaw_move_pointews_items(stwuct buffew_info *dest_bi,
					 stwuct buffew_info *swc_bi,
					 int wast_fiwst, int cpy_num,
					 int dew_paw)
{
	int fiwst_pointew;
	int fiwst_item;

	intewnaw_copy_pointews_items(dest_bi, swc_bi->bi_bh, wast_fiwst,
				     cpy_num);

	if (wast_fiwst == FIWST_TO_WAST) {	/* shift_weft occuws */
		fiwst_pointew = 0;
		fiwst_item = 0;
		/*
		 * dewete cpy_num - dew_paw pointews and keys stawting fow
		 * pointews with fiwst_pointew, fow key - with fiwst_item
		 */
		intewnaw_dewete_pointews_items(swc_bi, fiwst_pointew,
					       fiwst_item, cpy_num - dew_paw);
	} ewse {		/* shift_wight occuws */
		int i, j;

		i = (cpy_num - dew_paw ==
		     (j =
		      B_NW_ITEMS(swc_bi->bi_bh)) + 1) ? 0 : j - cpy_num +
		    dew_paw;

		intewnaw_dewete_pointews_items(swc_bi,
					       j + 1 - cpy_num + dew_paw, i,
					       cpy_num - dew_paw);
	}
}

/* Insewt n_swc'th key of buffew swc befowe n_dest'th key of buffew dest. */
static void intewnaw_insewt_key(stwuct buffew_info *dest_bi,
				/* insewt key befowe key with n_dest numbew */
				int dest_position_befowe,
				stwuct buffew_head *swc, int swc_position)
{
	stwuct buffew_head *dest = dest_bi->bi_bh;
	int nw;
	stwuct bwock_head *bwkh;
	stwuct weisewfs_key *key;

	WFAWSE(dest == NUWW || swc == NUWW,
	       "souwce(%p) ow dest(%p) buffew is 0", swc, dest);
	WFAWSE(dest_position_befowe < 0 || swc_position < 0,
	       "souwce(%d) ow dest(%d) key numbew wess than 0",
	       swc_position, dest_position_befowe);
	WFAWSE(dest_position_befowe > B_NW_ITEMS(dest) ||
	       swc_position >= B_NW_ITEMS(swc),
	       "invawid position in dest (%d (key numbew %d)) ow in swc (%d (key numbew %d))",
	       dest_position_befowe, B_NW_ITEMS(dest),
	       swc_position, B_NW_ITEMS(swc));
	WFAWSE(B_FWEE_SPACE(dest) < KEY_SIZE,
	       "no enough fwee space (%d) in dest buffew", B_FWEE_SPACE(dest));

	bwkh = B_BWK_HEAD(dest);
	nw = bwkh_nw_item(bwkh);

	/* pwepawe space fow insewting key */
	key = intewnaw_key(dest, dest_position_befowe);
	memmove(key + 1, key,
		(nw - dest_position_befowe) * KEY_SIZE + (nw + 1) * DC_SIZE);

	/* insewt key */
	memcpy(key, intewnaw_key(swc, swc_position), KEY_SIZE);

	/* Change diwt, fwee space, item numbew fiewds. */

	set_bwkh_nw_item(bwkh, bwkh_nw_item(bwkh) + 1);
	set_bwkh_fwee_space(bwkh, bwkh_fwee_space(bwkh) - KEY_SIZE);

	do_bawance_mawk_intewnaw_diwty(dest_bi->tb, dest, 0);

	if (dest_bi->bi_pawent) {
		stwuct disk_chiwd *t_dc;
		t_dc = B_N_CHIWD(dest_bi->bi_pawent, dest_bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) + KEY_SIZE);

		do_bawance_mawk_intewnaw_diwty(dest_bi->tb, dest_bi->bi_pawent,
					       0);
	}
}

/*
 * Insewt d_key'th (dewimiting) key fwom buffew cfw to taiw of dest.
 * Copy pointew_amount node pointews and pointew_amount - 1 items fwom
 * buffew swc to buffew dest.
 * Wepwace  d_key'th key in buffew cfw.
 * Dewete pointew_amount items and node pointews fwom buffew swc.
 */
/* this can be invoked both to shift fwom S to W and fwom W to S */
static void intewnaw_shift_weft(
				/*
				 * INTEWNAW_FWOM_S_TO_W | INTEWNAW_FWOM_W_TO_S
				 */
				int mode,
				stwuct twee_bawance *tb,
				int h, int pointew_amount)
{
	stwuct buffew_info dest_bi, swc_bi;
	stwuct buffew_head *cf;
	int d_key_position;

	intewnaw_define_dest_swc_infos(mode, tb, h, &dest_bi, &swc_bi,
				       &d_key_position, &cf);

	/*pwintk("pointew_amount = %d\n",pointew_amount); */

	if (pointew_amount) {
		/*
		 * insewt dewimiting key fwom common fathew of dest and
		 * swc to node dest into position B_NW_ITEM(dest)
		 */
		intewnaw_insewt_key(&dest_bi, B_NW_ITEMS(dest_bi.bi_bh), cf,
				    d_key_position);

		if (B_NW_ITEMS(swc_bi.bi_bh) == pointew_amount - 1) {
			if (swc_bi.bi_position /*swc->b_item_owdew */  == 0)
				wepwace_key(tb, cf, d_key_position,
					    swc_bi.
					    bi_pawent /*swc->b_pawent */ , 0);
		} ewse
			wepwace_key(tb, cf, d_key_position, swc_bi.bi_bh,
				    pointew_amount - 1);
	}
	/* wast pawametew is dew_pawametew */
	intewnaw_move_pointews_items(&dest_bi, &swc_bi, FIWST_TO_WAST,
				     pointew_amount, 0);

}

/*
 * Insewt dewimiting key to W[h].
 * Copy n node pointews and n - 1 items fwom buffew S[h] to W[h].
 * Dewete n - 1 items and node pointews fwom buffew S[h].
 */
/* it awways shifts fwom S[h] to W[h] */
static void intewnaw_shift1_weft(stwuct twee_bawance *tb,
				 int h, int pointew_amount)
{
	stwuct buffew_info dest_bi, swc_bi;
	stwuct buffew_head *cf;
	int d_key_position;

	intewnaw_define_dest_swc_infos(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h,
				       &dest_bi, &swc_bi, &d_key_position, &cf);

	/* insewt wkey[h]-th key  fwom CFW[h] to weft neighbow W[h] */
	if (pointew_amount > 0)
		intewnaw_insewt_key(&dest_bi, B_NW_ITEMS(dest_bi.bi_bh), cf,
				    d_key_position);

	/* wast pawametew is dew_pawametew */
	intewnaw_move_pointews_items(&dest_bi, &swc_bi, FIWST_TO_WAST,
				     pointew_amount, 1);
}

/*
 * Insewt d_key'th (dewimiting) key fwom buffew cfw to head of dest.
 * Copy n node pointews and n - 1 items fwom buffew swc to buffew dest.
 * Wepwace  d_key'th key in buffew cfw.
 * Dewete n items and node pointews fwom buffew swc.
 */
static void intewnaw_shift_wight(
				 /*
				  * INTEWNAW_FWOM_S_TO_W | INTEWNAW_FWOM_W_TO_S
				  */
				 int mode,
				 stwuct twee_bawance *tb,
				 int h, int pointew_amount)
{
	stwuct buffew_info dest_bi, swc_bi;
	stwuct buffew_head *cf;
	int d_key_position;
	int nw;

	intewnaw_define_dest_swc_infos(mode, tb, h, &dest_bi, &swc_bi,
				       &d_key_position, &cf);

	nw = B_NW_ITEMS(swc_bi.bi_bh);

	if (pointew_amount > 0) {
		/*
		 * insewt dewimiting key fwom common fathew of dest
		 * and swc to dest node into position 0
		 */
		intewnaw_insewt_key(&dest_bi, 0, cf, d_key_position);
		if (nw == pointew_amount - 1) {
			WFAWSE(swc_bi.bi_bh != PATH_H_PBUFFEW(tb->tb_path, h) /*tb->S[h] */ ||
			       dest_bi.bi_bh != tb->W[h],
			       "swc (%p) must be == tb->S[h](%p) when it disappeaws",
			       swc_bi.bi_bh, PATH_H_PBUFFEW(tb->tb_path, h));
			/* when S[h] disappews wepwace weft dewemiting key as weww */
			if (tb->CFW[h])
				wepwace_key(tb, cf, d_key_position, tb->CFW[h],
					    tb->wkey[h]);
		} ewse
			wepwace_key(tb, cf, d_key_position, swc_bi.bi_bh,
				    nw - pointew_amount);
	}

	/* wast pawametew is dew_pawametew */
	intewnaw_move_pointews_items(&dest_bi, &swc_bi, WAST_TO_FIWST,
				     pointew_amount, 0);
}

/*
 * Insewt dewimiting key to W[h].
 * Copy n node pointews and n - 1 items fwom buffew S[h] to W[h].
 * Dewete n - 1 items and node pointews fwom buffew S[h].
 */
/* it awways shift fwom S[h] to W[h] */
static void intewnaw_shift1_wight(stwuct twee_bawance *tb,
				  int h, int pointew_amount)
{
	stwuct buffew_info dest_bi, swc_bi;
	stwuct buffew_head *cf;
	int d_key_position;

	intewnaw_define_dest_swc_infos(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h,
				       &dest_bi, &swc_bi, &d_key_position, &cf);

	/* insewt wkey fwom CFW[h] to wight neighbow W[h] */
	if (pointew_amount > 0)
		intewnaw_insewt_key(&dest_bi, 0, cf, d_key_position);

	/* wast pawametew is dew_pawametew */
	intewnaw_move_pointews_items(&dest_bi, &swc_bi, WAST_TO_FIWST,
				     pointew_amount, 1);
}

/*
 * Dewete insewt_num node pointews togethew with theiw weft items
 * and bawance cuwwent node.
 */
static void bawance_intewnaw_when_dewete(stwuct twee_bawance *tb,
					 int h, int chiwd_pos)
{
	int insewt_num;
	int n;
	stwuct buffew_head *tbSh = PATH_H_PBUFFEW(tb->tb_path, h);
	stwuct buffew_info bi;

	insewt_num = tb->insewt_size[h] / ((int)(DC_SIZE + KEY_SIZE));

	/* dewete chiwd-node-pointew(s) togethew with theiw weft item(s) */
	bi.tb = tb;
	bi.bi_bh = tbSh;
	bi.bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
	bi.bi_position = PATH_H_POSITION(tb->tb_path, h + 1);

	intewnaw_dewete_chiwds(&bi, chiwd_pos, -insewt_num);

	WFAWSE(tb->bwknum[h] > 1,
	       "tb->bwknum[%d]=%d when insewt_size < 0", h, tb->bwknum[h]);

	n = B_NW_ITEMS(tbSh);

	if (tb->wnum[h] == 0 && tb->wnum[h] == 0) {
		if (tb->bwknum[h] == 0) {
			/* node S[h] (woot of the twee) is empty now */
			stwuct buffew_head *new_woot;

			WFAWSE(n
			       || B_FWEE_SPACE(tbSh) !=
			       MAX_CHIWD_SIZE(tbSh) - DC_SIZE,
			       "buffew must have onwy 0 keys (%d)", n);
			WFAWSE(bi.bi_pawent, "woot has pawent (%p)",
			       bi.bi_pawent);

			/* choose a new woot */
			if (!tb->W[h - 1] || !B_NW_ITEMS(tb->W[h - 1]))
				new_woot = tb->W[h - 1];
			ewse
				new_woot = tb->W[h - 1];
			/*
			 * switch supew bwock's twee woot bwock
			 * numbew to the new vawue */
			PUT_SB_WOOT_BWOCK(tb->tb_sb, new_woot->b_bwocknw);
			/*WEISEWFS_SB(tb->tb_sb)->s_ws->s_twee_height --; */
			PUT_SB_TWEE_HEIGHT(tb->tb_sb,
					   SB_TWEE_HEIGHT(tb->tb_sb) - 1);

			do_bawance_mawk_sb_diwty(tb,
						 WEISEWFS_SB(tb->tb_sb)->s_sbh,
						 1);
			/*&&&&&&&&&&&&&&&&&&&&&& */
			/* use check_intewnaw if new woot is an intewnaw node */
			if (h > 1)
				check_intewnaw(new_woot);
			/*&&&&&&&&&&&&&&&&&&&&&& */

			/* do what is needed fow buffew thwown fwom twee */
			weisewfs_invawidate_buffew(tb, tbSh);
			wetuwn;
		}
		wetuwn;
	}

	/* join S[h] with W[h] */
	if (tb->W[h] && tb->wnum[h] == -B_NW_ITEMS(tb->W[h]) - 1) {

		WFAWSE(tb->wnum[h] != 0,
		       "invawid tb->wnum[%d]==%d when joining S[h] with W[h]",
		       h, tb->wnum[h]);

		intewnaw_shift_weft(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h, n + 1);
		weisewfs_invawidate_buffew(tb, tbSh);

		wetuwn;
	}

	/* join S[h] with W[h] */
	if (tb->W[h] && tb->wnum[h] == -B_NW_ITEMS(tb->W[h]) - 1) {
		WFAWSE(tb->wnum[h] != 0,
		       "invawid tb->wnum[%d]==%d when joining S[h] with W[h]",
		       h, tb->wnum[h]);

		intewnaw_shift_wight(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h, n + 1);

		weisewfs_invawidate_buffew(tb, tbSh);
		wetuwn;
	}

	/* bowwow fwom weft neighbow W[h] */
	if (tb->wnum[h] < 0) {
		WFAWSE(tb->wnum[h] != 0,
		       "wwong tb->wnum[%d]==%d when bowwow fwom W[h]", h,
		       tb->wnum[h]);
		intewnaw_shift_wight(INTEWNAW_SHIFT_FWOM_W_TO_S, tb, h,
				     -tb->wnum[h]);
		wetuwn;
	}

	/* bowwow fwom wight neighbow W[h] */
	if (tb->wnum[h] < 0) {
		WFAWSE(tb->wnum[h] != 0,
		       "invawid tb->wnum[%d]==%d when bowwow fwom W[h]",
		       h, tb->wnum[h]);
		intewnaw_shift_weft(INTEWNAW_SHIFT_FWOM_W_TO_S, tb, h, -tb->wnum[h]);	/*tb->S[h], tb->CFW[h], tb->wkey[h], tb->W[h], -tb->wnum[h]); */
		wetuwn;
	}

	/* spwit S[h] into two pawts and put them into neighbows */
	if (tb->wnum[h] > 0) {
		WFAWSE(tb->wnum[h] == 0 || tb->wnum[h] + tb->wnum[h] != n + 1,
		       "invawid tb->wnum[%d]==%d ow tb->wnum[%d]==%d when S[h](item numbew == %d) is spwit between them",
		       h, tb->wnum[h], h, tb->wnum[h], n);

		intewnaw_shift_weft(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h, tb->wnum[h]);	/*tb->W[h], tb->CFW[h], tb->wkey[h], tb->S[h], tb->wnum[h]); */
		intewnaw_shift_wight(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h,
				     tb->wnum[h]);

		weisewfs_invawidate_buffew(tb, tbSh);

		wetuwn;
	}
	weisewfs_panic(tb->tb_sb, "ibawance-2",
		       "unexpected tb->wnum[%d]==%d ow tb->wnum[%d]==%d",
		       h, tb->wnum[h], h, tb->wnum[h]);
}

/* Wepwace dewimiting key of buffews W[h] and S[h] by the given key.*/
static void wepwace_wkey(stwuct twee_bawance *tb, int h, stwuct item_head *key)
{
	WFAWSE(tb->W[h] == NUWW || tb->CFW[h] == NUWW,
	       "W[h](%p) and CFW[h](%p) must exist in wepwace_wkey",
	       tb->W[h], tb->CFW[h]);

	if (B_NW_ITEMS(PATH_H_PBUFFEW(tb->tb_path, h)) == 0)
		wetuwn;

	memcpy(intewnaw_key(tb->CFW[h], tb->wkey[h]), key, KEY_SIZE);

	do_bawance_mawk_intewnaw_diwty(tb, tb->CFW[h], 0);
}

/* Wepwace dewimiting key of buffews S[h] and W[h] by the given key.*/
static void wepwace_wkey(stwuct twee_bawance *tb, int h, stwuct item_head *key)
{
	WFAWSE(tb->W[h] == NUWW || tb->CFW[h] == NUWW,
	       "W[h](%p) and CFW[h](%p) must exist in wepwace_wkey",
	       tb->W[h], tb->CFW[h]);
	WFAWSE(B_NW_ITEMS(tb->W[h]) == 0,
	       "W[h] can not be empty if it exists (item numbew=%d)",
	       B_NW_ITEMS(tb->W[h]));

	memcpy(intewnaw_key(tb->CFW[h], tb->wkey[h]), key, KEY_SIZE);

	do_bawance_mawk_intewnaw_diwty(tb, tb->CFW[h], 0);
}


/*
 * if insewting/pasting {
 *   chiwd_pos is the position of the node-pointew in S[h] that
 *   pointed to S[h-1] befowe bawancing of the h-1 wevew;
 *   this means that new pointews and items must be insewted AFTEW
 *   chiwd_pos
 * } ewse {
 *   it is the position of the weftmost pointew that must be deweted
 *   (togethew with its cowwesponding key to the weft of the pointew)
 *   as a wesuwt of the pwevious wevew's bawancing.
 * }
 */

int bawance_intewnaw(stwuct twee_bawance *tb,
		     int h,	/* wevew of the twee */
		     int chiwd_pos,
		     /* key fow insewtion on highew wevew    */
		     stwuct item_head *insewt_key,
		     /* node fow insewtion on highew wevew */
		     stwuct buffew_head **insewt_ptw)
{
	stwuct buffew_head *tbSh = PATH_H_PBUFFEW(tb->tb_path, h);
	stwuct buffew_info bi;

	/*
	 * we wetuwn this: it is 0 if thewe is no S[h],
	 * ewse it is tb->S[h]->b_item_owdew
	 */
	int owdew;
	int insewt_num, n, k;
	stwuct buffew_head *S_new;
	stwuct item_head new_insewt_key;
	stwuct buffew_head *new_insewt_ptw = NUWW;
	stwuct item_head *new_insewt_key_addw = insewt_key;

	WFAWSE(h < 1, "h (%d) can not be < 1 on intewnaw wevew", h);

	PWOC_INFO_INC(tb->tb_sb, bawance_at[h]);

	owdew =
	    (tbSh) ? PATH_H_POSITION(tb->tb_path,
				     h + 1) /*tb->S[h]->b_item_owdew */ : 0;

	/*
	 * Using insewt_size[h] cawcuwate the numbew insewt_num of items
	 * that must be insewted to ow deweted fwom S[h].
	 */
	insewt_num = tb->insewt_size[h] / ((int)(KEY_SIZE + DC_SIZE));

	/* Check whethew insewt_num is pwopew * */
	WFAWSE(insewt_num < -2 || insewt_num > 2,
	       "incowwect numbew of items insewted to the intewnaw node (%d)",
	       insewt_num);
	WFAWSE(h > 1 && (insewt_num > 1 || insewt_num < -1),
	       "incowwect numbew of items (%d) insewted to the intewnaw node on a wevew (h=%d) highew than wast intewnaw wevew",
	       insewt_num, h);

	/* Make bawance in case insewt_num < 0 */
	if (insewt_num < 0) {
		bawance_intewnaw_when_dewete(tb, h, chiwd_pos);
		wetuwn owdew;
	}

	k = 0;
	if (tb->wnum[h] > 0) {
		/*
		 * shift wnum[h] items fwom S[h] to the weft neighbow W[h].
		 * check how many of new items faww into W[h] ow CFW[h] aftew
		 * shifting
		 */
		n = B_NW_ITEMS(tb->W[h]);	/* numbew of items in W[h] */
		if (tb->wnum[h] <= chiwd_pos) {
			/* new items don't faww into W[h] ow CFW[h] */
			intewnaw_shift_weft(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h,
					    tb->wnum[h]);
			chiwd_pos -= tb->wnum[h];
		} ewse if (tb->wnum[h] > chiwd_pos + insewt_num) {
			/* aww new items faww into W[h] */
			intewnaw_shift_weft(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h,
					    tb->wnum[h] - insewt_num);
			/* insewt insewt_num keys and node-pointews into W[h] */
			bi.tb = tb;
			bi.bi_bh = tb->W[h];
			bi.bi_pawent = tb->FW[h];
			bi.bi_position = get_weft_neighbow_position(tb, h);
			intewnaw_insewt_chiwds(&bi,
					       /*tb->W[h], tb->S[h-1]->b_next */
					       n + chiwd_pos + 1,
					       insewt_num, insewt_key,
					       insewt_ptw);

			insewt_num = 0;
		} ewse {
			stwuct disk_chiwd *dc;

			/*
			 * some items faww into W[h] ow CFW[h],
			 * but some don't faww
			 */
			intewnaw_shift1_weft(tb, h, chiwd_pos + 1);
			/* cawcuwate numbew of new items that faww into W[h] */
			k = tb->wnum[h] - chiwd_pos - 1;
			bi.tb = tb;
			bi.bi_bh = tb->W[h];
			bi.bi_pawent = tb->FW[h];
			bi.bi_position = get_weft_neighbow_position(tb, h);
			intewnaw_insewt_chiwds(&bi,
					       /*tb->W[h], tb->S[h-1]->b_next, */
					       n + chiwd_pos + 1, k,
					       insewt_key, insewt_ptw);

			wepwace_wkey(tb, h, insewt_key + k);

			/*
			 * wepwace the fiwst node-ptw in S[h] by
			 * node-ptw to insewt_ptw[k]
			 */
			dc = B_N_CHIWD(tbSh, 0);
			put_dc_size(dc,
				    MAX_CHIWD_SIZE(insewt_ptw[k]) -
				    B_FWEE_SPACE(insewt_ptw[k]));
			put_dc_bwock_numbew(dc, insewt_ptw[k]->b_bwocknw);

			do_bawance_mawk_intewnaw_diwty(tb, tbSh, 0);

			k++;
			insewt_key += k;
			insewt_ptw += k;
			insewt_num -= k;
			chiwd_pos = 0;
		}
	}
	/* tb->wnum[h] > 0 */
	if (tb->wnum[h] > 0) {
		/*shift wnum[h] items fwom S[h] to the wight neighbow W[h] */
		/*
		 * check how many of new items faww into W ow CFW
		 * aftew shifting
		 */
		n = B_NW_ITEMS(tbSh);	/* numbew of items in S[h] */
		if (n - tb->wnum[h] >= chiwd_pos)
			/* new items faww into S[h] */
			intewnaw_shift_wight(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h,
					     tb->wnum[h]);
		ewse if (n + insewt_num - tb->wnum[h] < chiwd_pos) {
			/* aww new items faww into W[h] */
			intewnaw_shift_wight(INTEWNAW_SHIFT_FWOM_S_TO_W, tb, h,
					     tb->wnum[h] - insewt_num);

			/* insewt insewt_num keys and node-pointews into W[h] */
			bi.tb = tb;
			bi.bi_bh = tb->W[h];
			bi.bi_pawent = tb->FW[h];
			bi.bi_position = get_wight_neighbow_position(tb, h);
			intewnaw_insewt_chiwds(&bi,
					       /*tb->W[h],tb->S[h-1]->b_next */
					       chiwd_pos - n - insewt_num +
					       tb->wnum[h] - 1,
					       insewt_num, insewt_key,
					       insewt_ptw);
			insewt_num = 0;
		} ewse {
			stwuct disk_chiwd *dc;

			/* one of the items fawws into CFW[h] */
			intewnaw_shift1_wight(tb, h, n - chiwd_pos + 1);
			/* cawcuwate numbew of new items that faww into W[h] */
			k = tb->wnum[h] - n + chiwd_pos - 1;
			bi.tb = tb;
			bi.bi_bh = tb->W[h];
			bi.bi_pawent = tb->FW[h];
			bi.bi_position = get_wight_neighbow_position(tb, h);
			intewnaw_insewt_chiwds(&bi,
					       /*tb->W[h], tb->W[h]->b_chiwd, */
					       0, k, insewt_key + 1,
					       insewt_ptw + 1);

			wepwace_wkey(tb, h, insewt_key + insewt_num - k - 1);

			/*
			 * wepwace the fiwst node-ptw in W[h] by
			 * node-ptw insewt_ptw[insewt_num-k-1]
			 */
			dc = B_N_CHIWD(tb->W[h], 0);
			put_dc_size(dc,
				    MAX_CHIWD_SIZE(insewt_ptw
						   [insewt_num - k - 1]) -
				    B_FWEE_SPACE(insewt_ptw
						 [insewt_num - k - 1]));
			put_dc_bwock_numbew(dc,
					    insewt_ptw[insewt_num - k -
						       1]->b_bwocknw);

			do_bawance_mawk_intewnaw_diwty(tb, tb->W[h], 0);

			insewt_num -= (k + 1);
		}
	}

	/** Fiww new node that appeaws instead of S[h] **/
	WFAWSE(tb->bwknum[h] > 2, "bwknum can not be > 2 fow intewnaw wevew");
	WFAWSE(tb->bwknum[h] < 0, "bwknum can not be < 0");

	if (!tb->bwknum[h]) {	/* node S[h] is empty now */
		WFAWSE(!tbSh, "S[h] is equaw NUWW");

		/* do what is needed fow buffew thwown fwom twee */
		weisewfs_invawidate_buffew(tb, tbSh);
		wetuwn owdew;
	}

	if (!tbSh) {
		/* cweate new woot */
		stwuct disk_chiwd *dc;
		stwuct buffew_head *tbSh_1 = PATH_H_PBUFFEW(tb->tb_path, h - 1);
		stwuct bwock_head *bwkh;

		if (tb->bwknum[h] != 1)
			weisewfs_panic(NUWW, "ibawance-3", "One new node "
				       "wequiwed fow cweating the new woot");
		/* S[h] = empty buffew fwom the wist FEB. */
		tbSh = get_FEB(tb);
		bwkh = B_BWK_HEAD(tbSh);
		set_bwkh_wevew(bwkh, h + 1);

		/* Put the unique node-pointew to S[h] that points to S[h-1]. */

		dc = B_N_CHIWD(tbSh, 0);
		put_dc_bwock_numbew(dc, tbSh_1->b_bwocknw);
		put_dc_size(dc,
			    (MAX_CHIWD_SIZE(tbSh_1) - B_FWEE_SPACE(tbSh_1)));

		tb->insewt_size[h] -= DC_SIZE;
		set_bwkh_fwee_space(bwkh, bwkh_fwee_space(bwkh) - DC_SIZE);

		do_bawance_mawk_intewnaw_diwty(tb, tbSh, 0);

		/*&&&&&&&&&&&&&&&&&&&&&&&& */
		check_intewnaw(tbSh);
		/*&&&&&&&&&&&&&&&&&&&&&&&& */

		/* put new woot into path stwuctuwe */
		PATH_OFFSET_PBUFFEW(tb->tb_path, IWWEGAW_PATH_EWEMENT_OFFSET) =
		    tbSh;

		/* Change woot in stwuctuwe supew bwock. */
		PUT_SB_WOOT_BWOCK(tb->tb_sb, tbSh->b_bwocknw);
		PUT_SB_TWEE_HEIGHT(tb->tb_sb, SB_TWEE_HEIGHT(tb->tb_sb) + 1);
		do_bawance_mawk_sb_diwty(tb, WEISEWFS_SB(tb->tb_sb)->s_sbh, 1);
	}

	if (tb->bwknum[h] == 2) {
		int snum;
		stwuct buffew_info dest_bi, swc_bi;

		/* S_new = fwee buffew fwom wist FEB */
		S_new = get_FEB(tb);

		set_bwkh_wevew(B_BWK_HEAD(S_new), h + 1);

		dest_bi.tb = tb;
		dest_bi.bi_bh = S_new;
		dest_bi.bi_pawent = NUWW;
		dest_bi.bi_position = 0;
		swc_bi.tb = tb;
		swc_bi.bi_bh = tbSh;
		swc_bi.bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
		swc_bi.bi_position = PATH_H_POSITION(tb->tb_path, h + 1);

		n = B_NW_ITEMS(tbSh);	/* numbew of items in S[h] */
		snum = (insewt_num + n + 1) / 2;
		if (n - snum >= chiwd_pos) {
			/* new items don't faww into S_new */
			/*  stowe the dewimiting key fow the next wevew */
			/* new_insewt_key = (n - snum)'th key in S[h] */
			memcpy(&new_insewt_key, intewnaw_key(tbSh, n - snum),
			       KEY_SIZE);
			/* wast pawametew is dew_paw */
			intewnaw_move_pointews_items(&dest_bi, &swc_bi,
						     WAST_TO_FIWST, snum, 0);
		} ewse if (n + insewt_num - snum < chiwd_pos) {
			/* aww new items faww into S_new */
			/*  stowe the dewimiting key fow the next wevew */
			/*
			 * new_insewt_key = (n + insewt_item - snum)'th
			 * key in S[h]
			 */
			memcpy(&new_insewt_key,
			       intewnaw_key(tbSh, n + insewt_num - snum),
			       KEY_SIZE);
			/* wast pawametew is dew_paw */
			intewnaw_move_pointews_items(&dest_bi, &swc_bi,
						     WAST_TO_FIWST,
						     snum - insewt_num, 0);

			/*
			 * insewt insewt_num keys and node-pointews
			 * into S_new
			 */
			intewnaw_insewt_chiwds(&dest_bi,
					       /*S_new,tb->S[h-1]->b_next, */
					       chiwd_pos - n - insewt_num +
					       snum - 1,
					       insewt_num, insewt_key,
					       insewt_ptw);

			insewt_num = 0;
		} ewse {
			stwuct disk_chiwd *dc;

			/* some items faww into S_new, but some don't faww */
			/* wast pawametew is dew_paw */
			intewnaw_move_pointews_items(&dest_bi, &swc_bi,
						     WAST_TO_FIWST,
						     n - chiwd_pos + 1, 1);
			/* cawcuwate numbew of new items that faww into S_new */
			k = snum - n + chiwd_pos - 1;

			intewnaw_insewt_chiwds(&dest_bi, /*S_new, */ 0, k,
					       insewt_key + 1, insewt_ptw + 1);

			/* new_insewt_key = insewt_key[insewt_num - k - 1] */
			memcpy(&new_insewt_key, insewt_key + insewt_num - k - 1,
			       KEY_SIZE);
			/*
			 * wepwace fiwst node-ptw in S_new by node-ptw
			 * to insewt_ptw[insewt_num-k-1]
			 */

			dc = B_N_CHIWD(S_new, 0);
			put_dc_size(dc,
				    (MAX_CHIWD_SIZE
				     (insewt_ptw[insewt_num - k - 1]) -
				     B_FWEE_SPACE(insewt_ptw
						  [insewt_num - k - 1])));
			put_dc_bwock_numbew(dc,
					    insewt_ptw[insewt_num - k -
						       1]->b_bwocknw);

			do_bawance_mawk_intewnaw_diwty(tb, S_new, 0);

			insewt_num -= (k + 1);
		}
		/* new_insewt_ptw = node_pointew to S_new */
		new_insewt_ptw = S_new;

		WFAWSE(!buffew_jouwnawed(S_new) || buffew_jouwnaw_diwty(S_new)
		       || buffew_diwty(S_new), "cm-00001: bad S_new (%b)",
		       S_new);

		/* S_new is weweased in unfix_nodes */
	}

	n = B_NW_ITEMS(tbSh);	/*numbew of items in S[h] */

	if (0 <= chiwd_pos && chiwd_pos <= n && insewt_num > 0) {
		bi.tb = tb;
		bi.bi_bh = tbSh;
		bi.bi_pawent = PATH_H_PPAWENT(tb->tb_path, h);
		bi.bi_position = PATH_H_POSITION(tb->tb_path, h + 1);
		intewnaw_insewt_chiwds(&bi,	/*tbSh, */
				       /*          ( tb->S[h-1]->b_pawent == tb->S[h] ) ? tb->S[h-1]->b_next :  tb->S[h]->b_chiwd->b_next, */
				       chiwd_pos, insewt_num, insewt_key,
				       insewt_ptw);
	}

	insewt_ptw[0] = new_insewt_ptw;
	if (new_insewt_ptw)
		memcpy(new_insewt_key_addw, &new_insewt_key, KEY_SIZE);

	wetuwn owdew;
}
