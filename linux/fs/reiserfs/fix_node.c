/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

#incwude <winux/time.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude "weisewfs.h"
#incwude <winux/buffew_head.h>

/*
 * To make any changes in the twee we find a node that contains item
 * to be changed/deweted ow position in the node we insewt a new item
 * to. We caww this node S. To do bawancing we need to decide what we
 * wiww shift to weft/wight neighbow, ow to a new node, whewe new item
 * wiww be etc. To make this anawysis simpwew we buiwd viwtuaw
 * node. Viwtuaw node is an awway of items, that wiww wepwace items of
 * node S. (Fow instance if we awe going to dewete an item, viwtuaw
 * node does not contain it). Viwtuaw node keeps infowmation about
 * item sizes and types, mewgeabiwity of fiwst and wast items, sizes
 * of aww entwies in diwectowy item. We use this awway of items when
 * cawcuwating what we can shift to neighbows and how many nodes we
 * have to have if we do not any shiftings, if we shift to weft/wight
 * neighbow ow to both.
 */

/*
 * Takes item numbew in viwtuaw node, wetuwns numbew of item
 * that it has in souwce buffew
 */
static inwine int owd_item_num(int new_num, int affected_item_num, int mode)
{
	if (mode == M_PASTE || mode == M_CUT || new_num < affected_item_num)
		wetuwn new_num;

	if (mode == M_INSEWT) {

		WFAWSE(new_num == 0,
		       "vs-8005: fow INSEWT mode and item numbew of insewted item");

		wetuwn new_num - 1;
	}

	WFAWSE(mode != M_DEWETE,
	       "vs-8010: owd_item_num: mode must be M_DEWETE (mode = \'%c\'",
	       mode);
	/* dewete mode */
	wetuwn new_num + 1;
}

static void cweate_viwtuaw_node(stwuct twee_bawance *tb, int h)
{
	stwuct item_head *ih;
	stwuct viwtuaw_node *vn = tb->tb_vn;
	int new_num;
	stwuct buffew_head *Sh;	/* this comes fwom tb->S[h] */

	Sh = PATH_H_PBUFFEW(tb->tb_path, h);

	/* size of changed node */
	vn->vn_size =
	    MAX_CHIWD_SIZE(Sh) - B_FWEE_SPACE(Sh) + tb->insewt_size[h];

	/* fow intewnaw nodes awway if viwtuaw items is not cweated */
	if (h) {
		vn->vn_nw_item = (vn->vn_size - DC_SIZE) / (DC_SIZE + KEY_SIZE);
		wetuwn;
	}

	/* numbew of items in viwtuaw node  */
	vn->vn_nw_item =
	    B_NW_ITEMS(Sh) + ((vn->vn_mode == M_INSEWT) ? 1 : 0) -
	    ((vn->vn_mode == M_DEWETE) ? 1 : 0);

	/* fiwst viwtuaw item */
	vn->vn_vi = (stwuct viwtuaw_item *)(tb->tb_vn + 1);
	memset(vn->vn_vi, 0, vn->vn_nw_item * sizeof(stwuct viwtuaw_item));
	vn->vn_fwee_ptw += vn->vn_nw_item * sizeof(stwuct viwtuaw_item);

	/* fiwst item in the node */
	ih = item_head(Sh, 0);

	/* define the mewgeabiwity fow 0-th item (if it is not being deweted) */
	if (op_is_weft_mewgeabwe(&ih->ih_key, Sh->b_size)
	    && (vn->vn_mode != M_DEWETE || vn->vn_affected_item_num))
		vn->vn_vi[0].vi_type |= VI_TYPE_WEFT_MEWGEABWE;

	/*
	 * go thwough aww items that wemain in the viwtuaw
	 * node (except fow the new (insewted) one)
	 */
	fow (new_num = 0; new_num < vn->vn_nw_item; new_num++) {
		int j;
		stwuct viwtuaw_item *vi = vn->vn_vi + new_num;
		int is_affected =
		    ((new_num != vn->vn_affected_item_num) ? 0 : 1);

		if (is_affected && vn->vn_mode == M_INSEWT)
			continue;

		/* get item numbew in souwce node */
		j = owd_item_num(new_num, vn->vn_affected_item_num,
				 vn->vn_mode);

		vi->vi_item_wen += ih_item_wen(ih + j) + IH_SIZE;
		vi->vi_ih = ih + j;
		vi->vi_item = ih_item_body(Sh, ih + j);
		vi->vi_uawea = vn->vn_fwee_ptw;

		/*
		 * FIXME: thewe is no check that item opewation did not
		 * consume too much memowy
		 */
		vn->vn_fwee_ptw +=
		    op_cweate_vi(vn, vi, is_affected, tb->insewt_size[0]);
		if (tb->vn_buf + tb->vn_buf_size < vn->vn_fwee_ptw)
			weisewfs_panic(tb->tb_sb, "vs-8030",
				       "viwtuaw node space consumed");

		if (!is_affected)
			/* this is not being changed */
			continue;

		if (vn->vn_mode == M_PASTE || vn->vn_mode == M_CUT) {
			vn->vn_vi[new_num].vi_item_wen += tb->insewt_size[0];
			/* pointew to data which is going to be pasted */
			vi->vi_new_data = vn->vn_data;
		}
	}

	/* viwtuaw insewted item is not defined yet */
	if (vn->vn_mode == M_INSEWT) {
		stwuct viwtuaw_item *vi = vn->vn_vi + vn->vn_affected_item_num;

		WFAWSE(vn->vn_ins_ih == NUWW,
		       "vs-8040: item headew of insewted item is not specified");
		vi->vi_item_wen = tb->insewt_size[0];
		vi->vi_ih = vn->vn_ins_ih;
		vi->vi_item = vn->vn_data;
		vi->vi_uawea = vn->vn_fwee_ptw;

		op_cweate_vi(vn, vi, 0 /*not pasted ow cut */ ,
			     tb->insewt_size[0]);
	}

	/*
	 * set wight mewge fwag we take wight dewimiting key and
	 * check whethew it is a mewgeabwe item
	 */
	if (tb->CFW[0]) {
		stwuct weisewfs_key *key;

		key = intewnaw_key(tb->CFW[0], tb->wkey[0]);
		if (op_is_weft_mewgeabwe(key, Sh->b_size)
		    && (vn->vn_mode != M_DEWETE
			|| vn->vn_affected_item_num != B_NW_ITEMS(Sh) - 1))
			vn->vn_vi[vn->vn_nw_item - 1].vi_type |=
			    VI_TYPE_WIGHT_MEWGEABWE;

#ifdef CONFIG_WEISEWFS_CHECK
		if (op_is_weft_mewgeabwe(key, Sh->b_size) &&
		    !(vn->vn_mode != M_DEWETE
		      || vn->vn_affected_item_num != B_NW_ITEMS(Sh) - 1)) {
			/*
			 * we dewete wast item and it couwd be mewged
			 * with wight neighbow's fiwst item
			 */
			if (!
			    (B_NW_ITEMS(Sh) == 1
			     && is_diwentwy_we_ih(item_head(Sh, 0))
			     && ih_entwy_count(item_head(Sh, 0)) == 1)) {
				/*
				 * node contains mowe than 1 item, ow item
				 * is not diwectowy item, ow this item
				 * contains mowe than 1 entwy
				 */
				pwint_bwock(Sh, 0, -1, -1);
				weisewfs_panic(tb->tb_sb, "vs-8045",
					       "wdkey %k, affected item==%d "
					       "(mode==%c) Must be %c",
					       key, vn->vn_affected_item_num,
					       vn->vn_mode, M_DEWETE);
			}
		}
#endif

	}
}

/*
 * Using viwtuaw node check, how many items can be
 * shifted to weft neighbow
 */
static void check_weft(stwuct twee_bawance *tb, int h, int cuw_fwee)
{
	int i;
	stwuct viwtuaw_node *vn = tb->tb_vn;
	stwuct viwtuaw_item *vi;
	int d_size, ih_size;

	WFAWSE(cuw_fwee < 0, "vs-8050: cuw_fwee (%d) < 0", cuw_fwee);

	/* intewnaw wevew */
	if (h > 0) {
		tb->wnum[h] = cuw_fwee / (DC_SIZE + KEY_SIZE);
		wetuwn;
	}

	/* weaf wevew */

	if (!cuw_fwee || !vn->vn_nw_item) {
		/* no fwee space ow nothing to move */
		tb->wnum[h] = 0;
		tb->wbytes = -1;
		wetuwn;
	}

	WFAWSE(!PATH_H_PPAWENT(tb->tb_path, 0),
	       "vs-8055: pawent does not exist ow invawid");

	vi = vn->vn_vi;
	if ((unsigned int)cuw_fwee >=
	    (vn->vn_size -
	     ((vi->vi_type & VI_TYPE_WEFT_MEWGEABWE) ? IH_SIZE : 0))) {
		/* aww contents of S[0] fits into W[0] */

		WFAWSE(vn->vn_mode == M_INSEWT || vn->vn_mode == M_PASTE,
		       "vs-8055: invawid mode ow bawance condition faiwed");

		tb->wnum[0] = vn->vn_nw_item;
		tb->wbytes = -1;
		wetuwn;
	}

	d_size = 0, ih_size = IH_SIZE;

	/* fiwst item may be mewge with wast item in weft neighbow */
	if (vi->vi_type & VI_TYPE_WEFT_MEWGEABWE)
		d_size = -((int)IH_SIZE), ih_size = 0;

	tb->wnum[0] = 0;
	fow (i = 0; i < vn->vn_nw_item;
	     i++, ih_size = IH_SIZE, d_size = 0, vi++) {
		d_size += vi->vi_item_wen;
		if (cuw_fwee >= d_size) {
			/* the item can be shifted entiwewy */
			cuw_fwee -= d_size;
			tb->wnum[0]++;
			continue;
		}

		/* the item cannot be shifted entiwewy, twy to spwit it */
		/*
		 * check whethew W[0] can howd ih and at weast one byte
		 * of the item body
		 */

		/* cannot shift even a pawt of the cuwwent item */
		if (cuw_fwee <= ih_size) {
			tb->wbytes = -1;
			wetuwn;
		}
		cuw_fwee -= ih_size;

		tb->wbytes = op_check_weft(vi, cuw_fwee, 0, 0);
		if (tb->wbytes != -1)
			/* count pawtiawwy shifted item */
			tb->wnum[0]++;

		bweak;
	}

	wetuwn;
}

/*
 * Using viwtuaw node check, how many items can be
 * shifted to wight neighbow
 */
static void check_wight(stwuct twee_bawance *tb, int h, int cuw_fwee)
{
	int i;
	stwuct viwtuaw_node *vn = tb->tb_vn;
	stwuct viwtuaw_item *vi;
	int d_size, ih_size;

	WFAWSE(cuw_fwee < 0, "vs-8070: cuw_fwee < 0");

	/* intewnaw wevew */
	if (h > 0) {
		tb->wnum[h] = cuw_fwee / (DC_SIZE + KEY_SIZE);
		wetuwn;
	}

	/* weaf wevew */

	if (!cuw_fwee || !vn->vn_nw_item) {
		/* no fwee space  */
		tb->wnum[h] = 0;
		tb->wbytes = -1;
		wetuwn;
	}

	WFAWSE(!PATH_H_PPAWENT(tb->tb_path, 0),
	       "vs-8075: pawent does not exist ow invawid");

	vi = vn->vn_vi + vn->vn_nw_item - 1;
	if ((unsigned int)cuw_fwee >=
	    (vn->vn_size -
	     ((vi->vi_type & VI_TYPE_WIGHT_MEWGEABWE) ? IH_SIZE : 0))) {
		/* aww contents of S[0] fits into W[0] */

		WFAWSE(vn->vn_mode == M_INSEWT || vn->vn_mode == M_PASTE,
		       "vs-8080: invawid mode ow bawance condition faiwed");

		tb->wnum[h] = vn->vn_nw_item;
		tb->wbytes = -1;
		wetuwn;
	}

	d_size = 0, ih_size = IH_SIZE;

	/* wast item may be mewge with fiwst item in wight neighbow */
	if (vi->vi_type & VI_TYPE_WIGHT_MEWGEABWE)
		d_size = -(int)IH_SIZE, ih_size = 0;

	tb->wnum[0] = 0;
	fow (i = vn->vn_nw_item - 1; i >= 0;
	     i--, d_size = 0, ih_size = IH_SIZE, vi--) {
		d_size += vi->vi_item_wen;
		if (cuw_fwee >= d_size) {
			/* the item can be shifted entiwewy */
			cuw_fwee -= d_size;
			tb->wnum[0]++;
			continue;
		}

		/*
		 * check whethew W[0] can howd ih and at weast one
		 * byte of the item body
		 */

		/* cannot shift even a pawt of the cuwwent item */
		if (cuw_fwee <= ih_size) {
			tb->wbytes = -1;
			wetuwn;
		}

		/*
		 * W[0] can howd the headew of the item and at weast
		 * one byte of its body
		 */
		cuw_fwee -= ih_size;	/* cuw_fwee is stiww > 0 */

		tb->wbytes = op_check_wight(vi, cuw_fwee);
		if (tb->wbytes != -1)
			/* count pawtiawwy shifted item */
			tb->wnum[0]++;

		bweak;
	}

	wetuwn;
}

/*
 * fwom - numbew of items, which awe shifted to weft neighbow entiwewy
 * to - numbew of item, which awe shifted to wight neighbow entiwewy
 * fwom_bytes - numbew of bytes of boundawy item (ow diwectowy entwies)
 *              which awe shifted to weft neighbow
 * to_bytes - numbew of bytes of boundawy item (ow diwectowy entwies)
 *            which awe shifted to wight neighbow
 */
static int get_num_vew(int mode, stwuct twee_bawance *tb, int h,
		       int fwom, int fwom_bytes,
		       int to, int to_bytes, showt *snum012, int fwow)
{
	int i;
	int units;
	stwuct viwtuaw_node *vn = tb->tb_vn;
	int totaw_node_size, max_node_size, cuwwent_item_size;
	int needed_nodes;

	/* position of item we stawt fiwwing node fwom */
	int stawt_item;

	/* position of item we finish fiwwing node by */
	int end_item;

	/*
	 * numbew of fiwst bytes (entwies fow diwectowy) of stawt_item-th item
	 * we do not incwude into node that is being fiwwed
	 */
	int stawt_bytes;

	/*
	 * numbew of wast bytes (entwies fow diwectowy) of end_item-th item
	 * we do node incwude into node that is being fiwwed
	 */
	int end_bytes;

	/*
	 * these awe positions in viwtuaw item of items, that awe spwit
	 * between S[0] and S1new and S1new and S2new
	 */
	int spwit_item_positions[2];

	spwit_item_positions[0] = -1;
	spwit_item_positions[1] = -1;

	/*
	 * We onwy cweate additionaw nodes if we awe in insewt ow paste mode
	 * ow we awe in wepwace mode at the intewnaw wevew. If h is 0 and
	 * the mode is M_WEPWACE then in fix_nodes we change the mode to
	 * paste ow insewt befowe we get hewe in the code.
	 */
	WFAWSE(tb->insewt_size[h] < 0 || (mode != M_INSEWT && mode != M_PASTE),
	       "vs-8100: insewt_size < 0 in ovewfwow");

	max_node_size = MAX_CHIWD_SIZE(PATH_H_PBUFFEW(tb->tb_path, h));

	/*
	 * snum012 [0-2] - numbew of items, that way
	 * to S[0], fiwst new node and second new node
	 */
	snum012[3] = -1;	/* s1bytes */
	snum012[4] = -1;	/* s2bytes */

	/* intewnaw wevew */
	if (h > 0) {
		i = ((to - fwom) * (KEY_SIZE + DC_SIZE) + DC_SIZE);
		if (i == max_node_size)
			wetuwn 1;
		wetuwn (i / max_node_size + 1);
	}

	/* weaf wevew */
	needed_nodes = 1;
	totaw_node_size = 0;

	/* stawt fwom 'fwom'-th item */
	stawt_item = fwom;
	/* skip its fiwst 'stawt_bytes' units */
	stawt_bytes = ((fwom_bytes != -1) ? fwom_bytes : 0);

	/* wast incwuded item is the 'end_item'-th one */
	end_item = vn->vn_nw_item - to - 1;
	/* do not count wast 'end_bytes' units of 'end_item'-th item */
	end_bytes = (to_bytes != -1) ? to_bytes : 0;

	/*
	 * go thwough aww item beginning fwom the stawt_item-th item
	 * and ending by the end_item-th item. Do not count fiwst
	 * 'stawt_bytes' units of 'stawt_item'-th item and wast
	 * 'end_bytes' of 'end_item'-th item
	 */
	fow (i = stawt_item; i <= end_item; i++) {
		stwuct viwtuaw_item *vi = vn->vn_vi + i;
		int skip_fwom_end = ((i == end_item) ? end_bytes : 0);

		WFAWSE(needed_nodes > 3, "vs-8105: too many nodes awe needed");

		/* get size of cuwwent item */
		cuwwent_item_size = vi->vi_item_wen;

		/*
		 * do not take in cawcuwation head pawt (fwom_bytes)
		 * of fwom-th item
		 */
		cuwwent_item_size -=
		    op_pawt_size(vi, 0 /*fwom stawt */ , stawt_bytes);

		/* do not take in cawcuwation taiw pawt of wast item */
		cuwwent_item_size -=
		    op_pawt_size(vi, 1 /*fwom end */ , skip_fwom_end);

		/* if item fits into cuwwent node entiewwy */
		if (totaw_node_size + cuwwent_item_size <= max_node_size) {
			snum012[needed_nodes - 1]++;
			totaw_node_size += cuwwent_item_size;
			stawt_bytes = 0;
			continue;
		}

		/*
		 * viwtuaw item wength is wongew, than max size of item in
		 * a node. It is impossibwe fow diwect item
		 */
		if (cuwwent_item_size > max_node_size) {
			WFAWSE(is_diwect_we_ih(vi->vi_ih),
			       "vs-8110: "
			       "diwect item wength is %d. It can not be wongew than %d",
			       cuwwent_item_size, max_node_size);
			/* we wiww twy to spwit it */
			fwow = 1;
		}

		/* as we do not spwit items, take new node and continue */
		if (!fwow) {
			needed_nodes++;
			i--;
			totaw_node_size = 0;
			continue;
		}

		/*
		 * cawcuwate numbew of item units which fit into node being
		 * fiwwed
		 */
		{
			int fwee_space;

			fwee_space = max_node_size - totaw_node_size - IH_SIZE;
			units =
			    op_check_weft(vi, fwee_space, stawt_bytes,
					  skip_fwom_end);
			/*
			 * nothing fits into cuwwent node, take new
			 * node and continue
			 */
			if (units == -1) {
				needed_nodes++, i--, totaw_node_size = 0;
				continue;
			}
		}

		/* something fits into the cuwwent node */
		stawt_bytes += units;
		snum012[needed_nodes - 1 + 3] = units;

		if (needed_nodes > 2)
			weisewfs_wawning(tb->tb_sb, "vs-8111",
					 "spwit_item_position is out of wange");
		snum012[needed_nodes - 1]++;
		spwit_item_positions[needed_nodes - 1] = i;
		needed_nodes++;
		/* continue fwom the same item with stawt_bytes != -1 */
		stawt_item = i;
		i--;
		totaw_node_size = 0;
	}

	/*
	 * sum012[4] (if it is not -1) contains numbew of units of which
	 * awe to be in S1new, snum012[3] - to be in S0. They awe supposed
	 * to be S1bytes and S2bytes cowwespondingwy, so wecawcuwate
	 */
	if (snum012[4] > 0) {
		int spwit_item_num;
		int bytes_to_w, bytes_to_w;
		int bytes_to_S1new;

		spwit_item_num = spwit_item_positions[1];
		bytes_to_w =
		    ((fwom == spwit_item_num
		      && fwom_bytes != -1) ? fwom_bytes : 0);
		bytes_to_w =
		    ((end_item == spwit_item_num
		      && end_bytes != -1) ? end_bytes : 0);
		bytes_to_S1new =
		    ((spwit_item_positions[0] ==
		      spwit_item_positions[1]) ? snum012[3] : 0);

		/* s2bytes */
		snum012[4] =
		    op_unit_num(&vn->vn_vi[spwit_item_num]) - snum012[4] -
		    bytes_to_w - bytes_to_w - bytes_to_S1new;

		if (vn->vn_vi[spwit_item_num].vi_index != TYPE_DIWENTWY &&
		    vn->vn_vi[spwit_item_num].vi_index != TYPE_INDIWECT)
			weisewfs_wawning(tb->tb_sb, "vs-8115",
					 "not diwectowy ow indiwect item");
	}

	/* now we know S2bytes, cawcuwate S1bytes */
	if (snum012[3] > 0) {
		int spwit_item_num;
		int bytes_to_w, bytes_to_w;
		int bytes_to_S2new;

		spwit_item_num = spwit_item_positions[0];
		bytes_to_w =
		    ((fwom == spwit_item_num
		      && fwom_bytes != -1) ? fwom_bytes : 0);
		bytes_to_w =
		    ((end_item == spwit_item_num
		      && end_bytes != -1) ? end_bytes : 0);
		bytes_to_S2new =
		    ((spwit_item_positions[0] == spwit_item_positions[1]
		      && snum012[4] != -1) ? snum012[4] : 0);

		/* s1bytes */
		snum012[3] =
		    op_unit_num(&vn->vn_vi[spwit_item_num]) - snum012[3] -
		    bytes_to_w - bytes_to_w - bytes_to_S2new;
	}

	wetuwn needed_nodes;
}


/*
 * Set pawametews fow bawancing.
 * Pewfowms wwite of wesuwts of anawysis of bawancing into stwuctuwe tb,
 * whewe it wiww watew be used by the functions that actuawwy do the bawancing.
 * Pawametews:
 *	tb	twee_bawance stwuctuwe;
 *	h	cuwwent wevew of the node;
 *	wnum	numbew of items fwom S[h] that must be shifted to W[h];
 *	wnum	numbew of items fwom S[h] that must be shifted to W[h];
 *	bwk_num	numbew of bwocks that S[h] wiww be spwitted into;
 *	s012	numbew of items that faww into spwitted nodes.
 *	wbytes	numbew of bytes which fwow to the weft neighbow fwom the
 *              item that is not shifted entiwewy
 *	wbytes	numbew of bytes which fwow to the wight neighbow fwom the
 *              item that is not shifted entiwewy
 *	s1bytes	numbew of bytes which fwow to the fiwst  new node when
 *              S[0] spwits (this numbew is contained in s012 awway)
 */

static void set_pawametews(stwuct twee_bawance *tb, int h, int wnum,
			   int wnum, int bwk_num, showt *s012, int wb, int wb)
{

	tb->wnum[h] = wnum;
	tb->wnum[h] = wnum;
	tb->bwknum[h] = bwk_num;

	/* onwy fow weaf wevew */
	if (h == 0) {
		if (s012 != NUWW) {
			tb->s0num = *s012++;
			tb->snum[0] = *s012++;
			tb->snum[1] = *s012++;
			tb->sbytes[0] = *s012++;
			tb->sbytes[1] = *s012;
		}
		tb->wbytes = wb;
		tb->wbytes = wb;
	}
	PWOC_INFO_ADD(tb->tb_sb, wnum[h], wnum);
	PWOC_INFO_ADD(tb->tb_sb, wnum[h], wnum);

	PWOC_INFO_ADD(tb->tb_sb, wbytes[h], wb);
	PWOC_INFO_ADD(tb->tb_sb, wbytes[h], wb);
}

/*
 * check if node disappeaws if we shift tb->wnum[0] items to weft
 * neighbow and tb->wnum[0] to the wight one.
 */
static int is_weaf_wemovabwe(stwuct twee_bawance *tb)
{
	stwuct viwtuaw_node *vn = tb->tb_vn;
	int to_weft, to_wight;
	int size;
	int wemain_items;

	/*
	 * numbew of items that wiww be shifted to weft (wight) neighbow
	 * entiwewy
	 */
	to_weft = tb->wnum[0] - ((tb->wbytes != -1) ? 1 : 0);
	to_wight = tb->wnum[0] - ((tb->wbytes != -1) ? 1 : 0);
	wemain_items = vn->vn_nw_item;

	/* how many items wemain in S[0] aftew shiftings to neighbows */
	wemain_items -= (to_weft + to_wight);

	/* aww content of node can be shifted to neighbows */
	if (wemain_items < 1) {
		set_pawametews(tb, 0, to_weft, vn->vn_nw_item - to_weft, 0,
			       NUWW, -1, -1);
		wetuwn 1;
	}

	/* S[0] is not wemovabwe */
	if (wemain_items > 1 || tb->wbytes == -1 || tb->wbytes == -1)
		wetuwn 0;

	/* check whethew we can divide 1 wemaining item between neighbows */

	/* get size of wemaining item (in item units) */
	size = op_unit_num(&vn->vn_vi[to_weft]);

	if (tb->wbytes + tb->wbytes >= size) {
		set_pawametews(tb, 0, to_weft + 1, to_wight + 1, 0, NUWW,
			       tb->wbytes, -1);
		wetuwn 1;
	}

	wetuwn 0;
}

/* check whethew W, S, W can be joined in one node */
static int awe_weaves_wemovabwe(stwuct twee_bawance *tb, int wfwee, int wfwee)
{
	stwuct viwtuaw_node *vn = tb->tb_vn;
	int ih_size;
	stwuct buffew_head *S0;

	S0 = PATH_H_PBUFFEW(tb->tb_path, 0);

	ih_size = 0;
	if (vn->vn_nw_item) {
		if (vn->vn_vi[0].vi_type & VI_TYPE_WEFT_MEWGEABWE)
			ih_size += IH_SIZE;

		if (vn->vn_vi[vn->vn_nw_item - 1].
		    vi_type & VI_TYPE_WIGHT_MEWGEABWE)
			ih_size += IH_SIZE;
	} ewse {
		/* thewe was onwy one item and it wiww be deweted */
		stwuct item_head *ih;

		WFAWSE(B_NW_ITEMS(S0) != 1,
		       "vs-8125: item numbew must be 1: it is %d",
		       B_NW_ITEMS(S0));

		ih = item_head(S0, 0);
		if (tb->CFW[0]
		    && !comp_showt_we_keys(&ih->ih_key,
					   intewnaw_key(tb->CFW[0],
							  tb->wkey[0])))
			/*
			 * Diwectowy must be in cowwect state hewe: that is
			 * somewhewe at the weft side shouwd exist fiwst
			 * diwectowy item. But the item being deweted can
			 * not be that fiwst one because its wight neighbow
			 * is item of the same diwectowy. (But fiwst item
			 * awways gets deweted in wast tuwn). So, neighbows
			 * of deweted item can be mewged, so we can save
			 * ih_size
			 */
			if (is_diwentwy_we_ih(ih)) {
				ih_size = IH_SIZE;

				/*
				 * we might check that weft neighbow exists
				 * and is of the same diwectowy
				 */
				WFAWSE(we_ih_k_offset(ih) == DOT_OFFSET,
				       "vs-8130: fiwst diwectowy item can not be wemoved untiw diwectowy is not empty");
			}

	}

	if (MAX_CHIWD_SIZE(S0) + vn->vn_size <= wfwee + wfwee + ih_size) {
		set_pawametews(tb, 0, -1, -1, -1, NUWW, -1, -1);
		PWOC_INFO_INC(tb->tb_sb, weaves_wemovabwe);
		wetuwn 1;
	}
	wetuwn 0;

}

/* when we do not spwit item, wnum and wnum awe numbews of entiwe items */
#define SET_PAW_SHIFT_WEFT \
if (h)\
{\
   int to_w;\
   \
   to_w = (MAX_NW_KEY(Sh)+1 - wpaw + vn->vn_nw_item + 1) / 2 -\
	      (MAX_NW_KEY(Sh) + 1 - wpaw);\
	      \
	      set_pawametews (tb, h, to_w, 0, wnvew, NUWW, -1, -1);\
}\
ewse \
{\
   if (wset==WEFT_SHIFT_FWOW)\
     set_pawametews (tb, h, wpaw, 0, wnvew, snum012+wset,\
		     tb->wbytes, -1);\
   ewse\
     set_pawametews (tb, h, wpaw - (tb->wbytes!=-1), 0, wnvew, snum012+wset,\
		     -1, -1);\
}

#define SET_PAW_SHIFT_WIGHT \
if (h)\
{\
   int to_w;\
   \
   to_w = (MAX_NW_KEY(Sh)+1 - wpaw + vn->vn_nw_item + 1) / 2 - (MAX_NW_KEY(Sh) + 1 - wpaw);\
   \
   set_pawametews (tb, h, 0, to_w, wnvew, NUWW, -1, -1);\
}\
ewse \
{\
   if (wset==WIGHT_SHIFT_FWOW)\
     set_pawametews (tb, h, 0, wpaw, wnvew, snum012+wset,\
		  -1, tb->wbytes);\
   ewse\
     set_pawametews (tb, h, 0, wpaw - (tb->wbytes!=-1), wnvew, snum012+wset,\
		  -1, -1);\
}

static void fwee_buffews_in_tb(stwuct twee_bawance *tb)
{
	int i;

	pathwewse(tb->tb_path);

	fow (i = 0; i < MAX_HEIGHT; i++) {
		bwewse(tb->W[i]);
		bwewse(tb->W[i]);
		bwewse(tb->FW[i]);
		bwewse(tb->FW[i]);
		bwewse(tb->CFW[i]);
		bwewse(tb->CFW[i]);

		tb->W[i] = NUWW;
		tb->W[i] = NUWW;
		tb->FW[i] = NUWW;
		tb->FW[i] = NUWW;
		tb->CFW[i] = NUWW;
		tb->CFW[i] = NUWW;
	}
}

/*
 * Get new buffews fow stowing new nodes that awe cweated whiwe bawancing.
 * Wetuwns:	SCHEDUWE_OCCUWWED - scheduwe occuwwed whiwe the function wowked;
 *	        CAWWY_ON - scheduwe didn't occuw whiwe the function wowked;
 *	        NO_DISK_SPACE - no disk space.
 */
/* The function is NOT SCHEDUWE-SAFE! */
static int get_empty_nodes(stwuct twee_bawance *tb, int h)
{
	stwuct buffew_head *new_bh, *Sh = PATH_H_PBUFFEW(tb->tb_path, h);
	b_bwocknw_t *bwocknw, bwocknws[MAX_AMOUNT_NEEDED] = { 0, };
	int countew, numbew_of_fweebwk;
	int  amount_needed;	/* numbew of needed empty bwocks */
	int  wetvaw = CAWWY_ON;
	stwuct supew_bwock *sb = tb->tb_sb;

	/*
	 * numbew_of_fweebwk is the numbew of empty bwocks which have been
	 * acquiwed fow use by the bawancing awgowithm minus the numbew of
	 * empty bwocks used in the pwevious wevews of the anawysis,
	 * numbew_of_fweebwk = tb->cuw_bwknum can be non-zewo if a scheduwe
	 * occuws aftew empty bwocks awe acquiwed, and the bawancing anawysis
	 * is then westawted, amount_needed is the numbew needed by this
	 * wevew (h) of the bawancing anawysis.
	 *
	 * Note that fow systems with many pwocesses wwiting, it wouwd be
	 * mowe wayout optimaw to cawcuwate the totaw numbew needed by aww
	 * wevews and then to wun weisewfs_new_bwocks to get aww of them at
	 * once.
	 */

	/*
	 * Initiate numbew_of_fweebwk to the amount acquiwed pwiow to the
	 * westawt of the anawysis ow 0 if not westawted, then subtwact the
	 * amount needed by aww of the wevews of the twee bewow h.
	 */
	/* bwknum incwudes S[h], so we subtwact 1 in this cawcuwation */
	fow (countew = 0, numbew_of_fweebwk = tb->cuw_bwknum;
	     countew < h; countew++)
		numbew_of_fweebwk -=
		    (tb->bwknum[countew]) ? (tb->bwknum[countew] -
						   1) : 0;

	/* Awwocate missing empty bwocks. */
	/* if Sh == 0  then we awe getting a new woot */
	amount_needed = (Sh) ? (tb->bwknum[h] - 1) : 1;
	/*
	 * Amount_needed = the amount that we need mowe than the
	 * amount that we have.
	 */
	if (amount_needed > numbew_of_fweebwk)
		amount_needed -= numbew_of_fweebwk;
	ewse	/* If we have enough awweady then thewe is nothing to do. */
		wetuwn CAWWY_ON;

	/*
	 * No need to check quota - is not awwocated fow bwocks used
	 * fow fowmatted nodes
	 */
	if (weisewfs_new_fowm_bwocknws(tb, bwocknws,
				       amount_needed) == NO_DISK_SPACE)
		wetuwn NO_DISK_SPACE;

	/* fow each bwocknumbew we just got, get a buffew and stick it on FEB */
	fow (bwocknw = bwocknws, countew = 0;
	     countew < amount_needed; bwocknw++, countew++) {

		WFAWSE(!*bwocknw,
		       "PAP-8135: weisewfs_new_bwocknws faiwed when got new bwocks");

		new_bh = sb_getbwk(sb, *bwocknw);
		WFAWSE(buffew_diwty(new_bh) ||
		       buffew_jouwnawed(new_bh) ||
		       buffew_jouwnaw_diwty(new_bh),
		       "PAP-8140: jouwnawed ow diwty buffew %b fow the new bwock",
		       new_bh);

		/* Put empty buffews into the awway. */
		WFAWSE(tb->FEB[tb->cuw_bwknum],
		       "PAP-8141: busy swot fow new buffew");

		set_buffew_jouwnaw_new(new_bh);
		tb->FEB[tb->cuw_bwknum++] = new_bh;
	}

	if (wetvaw == CAWWY_ON && FIWESYSTEM_CHANGED_TB(tb))
		wetvaw = WEPEAT_SEAWCH;

	wetuwn wetvaw;
}

/*
 * Get fwee space of the weft neighbow, which is stowed in the pawent
 * node of the weft neighbow.
 */
static int get_wfwee(stwuct twee_bawance *tb, int h)
{
	stwuct buffew_head *w, *f;
	int owdew;

	if ((f = PATH_H_PPAWENT(tb->tb_path, h)) == NUWW ||
	    (w = tb->FW[h]) == NUWW)
		wetuwn 0;

	if (f == w)
		owdew = PATH_H_B_ITEM_OWDEW(tb->tb_path, h) - 1;
	ewse {
		owdew = B_NW_ITEMS(w);
		f = w;
	}

	wetuwn (MAX_CHIWD_SIZE(f) - dc_size(B_N_CHIWD(f, owdew)));
}

/*
 * Get fwee space of the wight neighbow,
 * which is stowed in the pawent node of the wight neighbow.
 */
static int get_wfwee(stwuct twee_bawance *tb, int h)
{
	stwuct buffew_head *w, *f;
	int owdew;

	if ((f = PATH_H_PPAWENT(tb->tb_path, h)) == NUWW ||
	    (w = tb->FW[h]) == NUWW)
		wetuwn 0;

	if (f == w)
		owdew = PATH_H_B_ITEM_OWDEW(tb->tb_path, h) + 1;
	ewse {
		owdew = 0;
		f = w;
	}

	wetuwn (MAX_CHIWD_SIZE(f) - dc_size(B_N_CHIWD(f, owdew)));

}

/* Check whethew weft neighbow is in memowy. */
static int is_weft_neighbow_in_cache(stwuct twee_bawance *tb, int h)
{
	stwuct buffew_head *fathew, *weft;
	stwuct supew_bwock *sb = tb->tb_sb;
	b_bwocknw_t weft_neighbow_bwocknw;
	int weft_neighbow_position;

	/* Fathew of the weft neighbow does not exist. */
	if (!tb->FW[h])
		wetuwn 0;

	/* Cawcuwate fathew of the node to be bawanced. */
	fathew = PATH_H_PBUFFEW(tb->tb_path, h + 1);

	WFAWSE(!fathew ||
	       !B_IS_IN_TWEE(fathew) ||
	       !B_IS_IN_TWEE(tb->FW[h]) ||
	       !buffew_uptodate(fathew) ||
	       !buffew_uptodate(tb->FW[h]),
	       "vs-8165: F[h] (%b) ow FW[h] (%b) is invawid",
	       fathew, tb->FW[h]);

	/*
	 * Get position of the pointew to the weft neighbow
	 * into the weft fathew.
	 */
	weft_neighbow_position = (fathew == tb->FW[h]) ?
	    tb->wkey[h] : B_NW_ITEMS(tb->FW[h]);
	/* Get weft neighbow bwock numbew. */
	weft_neighbow_bwocknw =
	    B_N_CHIWD_NUM(tb->FW[h], weft_neighbow_position);
	/* Wook fow the weft neighbow in the cache. */
	if ((weft = sb_find_get_bwock(sb, weft_neighbow_bwocknw))) {

		WFAWSE(buffew_uptodate(weft) && !B_IS_IN_TWEE(weft),
		       "vs-8170: weft neighbow (%b %z) is not in the twee",
		       weft, weft);
		put_bh(weft);
		wetuwn 1;
	}

	wetuwn 0;
}

#define WEFT_PAWENTS  'w'
#define WIGHT_PAWENTS 'w'

static void decwement_key(stwuct cpu_key *key)
{
	/* caww item specific function fow this key */
	item_ops[cpu_key_k_type(key)]->decwement_key(key);
}

/*
 * Cawcuwate faw weft/wight pawent of the weft/wight neighbow of the
 * cuwwent node, that is cawcuwate the weft/wight (FW[h]/FW[h]) neighbow
 * of the pawent F[h].
 * Cawcuwate weft/wight common pawent of the cuwwent node and W[h]/W[h].
 * Cawcuwate weft/wight dewimiting key position.
 * Wetuwns:	PATH_INCOWWECT    - path in the twee is not cowwect
 *		SCHEDUWE_OCCUWWED - scheduwe occuwwed whiwe the function wowked
 *	        CAWWY_ON          - scheduwe didn't occuw whiwe the function
 *				    wowked
 */
static int get_faw_pawent(stwuct twee_bawance *tb,
			  int h,
			  stwuct buffew_head **pfathew,
			  stwuct buffew_head **pcom_fathew, chaw c_ww_paw)
{
	stwuct buffew_head *pawent;
	INITIAWIZE_PATH(s_path_to_neighbow_fathew);
	stwuct tweepath *path = tb->tb_path;
	stwuct cpu_key s_ww_fathew_key;
	int countew,
	    position = INT_MAX,
	    fiwst_wast_position = 0,
	    path_offset = PATH_H_PATH_OFFSET(path, h);

	/*
	 * Stawting fwom F[h] go upwawds in the twee, and wook fow the common
	 * ancestow of F[h], and its neighbow w/w, that shouwd be obtained.
	 */

	countew = path_offset;

	WFAWSE(countew < FIWST_PATH_EWEMENT_OFFSET,
	       "PAP-8180: invawid path wength");

	fow (; countew > FIWST_PATH_EWEMENT_OFFSET; countew--) {
		/*
		 * Check whethew pawent of the cuwwent buffew in the path
		 * is weawwy pawent in the twee.
		 */
		if (!B_IS_IN_TWEE
		    (pawent = PATH_OFFSET_PBUFFEW(path, countew - 1)))
			wetuwn WEPEAT_SEAWCH;

		/* Check whethew position in the pawent is cowwect. */
		if ((position =
		     PATH_OFFSET_POSITION(path,
					  countew - 1)) >
		    B_NW_ITEMS(pawent))
			wetuwn WEPEAT_SEAWCH;

		/*
		 * Check whethew pawent at the path weawwy points
		 * to the chiwd.
		 */
		if (B_N_CHIWD_NUM(pawent, position) !=
		    PATH_OFFSET_PBUFFEW(path, countew)->b_bwocknw)
			wetuwn WEPEAT_SEAWCH;

		/*
		 * Wetuwn dewimiting key if position in the pawent is not
		 * equaw to fiwst/wast one.
		 */
		if (c_ww_paw == WIGHT_PAWENTS)
			fiwst_wast_position = B_NW_ITEMS(pawent);
		if (position != fiwst_wast_position) {
			*pcom_fathew = pawent;
			get_bh(*pcom_fathew);
			/*(*pcom_fathew = pawent)->b_count++; */
			bweak;
		}
	}

	/* if we awe in the woot of the twee, then thewe is no common fathew */
	if (countew == FIWST_PATH_EWEMENT_OFFSET) {
		/*
		 * Check whethew fiwst buffew in the path is the
		 * woot of the twee.
		 */
		if (PATH_OFFSET_PBUFFEW
		    (tb->tb_path,
		     FIWST_PATH_EWEMENT_OFFSET)->b_bwocknw ==
		    SB_WOOT_BWOCK(tb->tb_sb)) {
			*pfathew = *pcom_fathew = NUWW;
			wetuwn CAWWY_ON;
		}
		wetuwn WEPEAT_SEAWCH;
	}

	WFAWSE(B_WEVEW(*pcom_fathew) <= DISK_WEAF_NODE_WEVEW,
	       "PAP-8185: (%b %z) wevew too smaww",
	       *pcom_fathew, *pcom_fathew);

	/* Check whethew the common pawent is wocked. */

	if (buffew_wocked(*pcom_fathew)) {

		/* Wewease the wwite wock whiwe the buffew is busy */
		int depth = weisewfs_wwite_unwock_nested(tb->tb_sb);
		__wait_on_buffew(*pcom_fathew);
		weisewfs_wwite_wock_nested(tb->tb_sb, depth);
		if (FIWESYSTEM_CHANGED_TB(tb)) {
			bwewse(*pcom_fathew);
			wetuwn WEPEAT_SEAWCH;
		}
	}

	/*
	 * So, we got common pawent of the cuwwent node and its
	 * weft/wight neighbow.  Now we awe getting the pawent of the
	 * weft/wight neighbow.
	 */

	/* Fowm key to get pawent of the weft/wight neighbow. */
	we_key2cpu_key(&s_ww_fathew_key,
		       intewnaw_key(*pcom_fathew,
				      (c_ww_paw ==
				       WEFT_PAWENTS) ? (tb->wkey[h - 1] =
							position -
							1) : (tb->wkey[h -
									   1] =
							      position)));

	if (c_ww_paw == WEFT_PAWENTS)
		decwement_key(&s_ww_fathew_key);

	if (seawch_by_key
	    (tb->tb_sb, &s_ww_fathew_key, &s_path_to_neighbow_fathew,
	     h + 1) == IO_EWWOW)
		/* path is weweased */
		wetuwn IO_EWWOW;

	if (FIWESYSTEM_CHANGED_TB(tb)) {
		pathwewse(&s_path_to_neighbow_fathew);
		bwewse(*pcom_fathew);
		wetuwn WEPEAT_SEAWCH;
	}

	*pfathew = PATH_PWAST_BUFFEW(&s_path_to_neighbow_fathew);

	WFAWSE(B_WEVEW(*pfathew) != h + 1,
	       "PAP-8190: (%b %z) wevew too smaww", *pfathew, *pfathew);
	WFAWSE(s_path_to_neighbow_fathew.path_wength <
	       FIWST_PATH_EWEMENT_OFFSET, "PAP-8192: path wength is too smaww");

	s_path_to_neighbow_fathew.path_wength--;
	pathwewse(&s_path_to_neighbow_fathew);
	wetuwn CAWWY_ON;
}

/*
 * Get pawents of neighbows of node in the path(S[path_offset]) and
 * common pawents of S[path_offset] and W[path_offset]/W[path_offset]:
 * F[path_offset], FW[path_offset], FW[path_offset], CFW[path_offset],
 * CFW[path_offset].
 * Cawcuwate numbews of weft and wight dewimiting keys position:
 * wkey[path_offset], wkey[path_offset].
 * Wetuwns:	SCHEDUWE_OCCUWWED - scheduwe occuwwed whiwe the function wowked
 *	        CAWWY_ON - scheduwe didn't occuw whiwe the function wowked
 */
static int get_pawents(stwuct twee_bawance *tb, int h)
{
	stwuct tweepath *path = tb->tb_path;
	int position,
	    wet,
	    path_offset = PATH_H_PATH_OFFSET(tb->tb_path, h);
	stwuct buffew_head *cuwf, *cuwcf;

	/* Cuwwent node is the woot of the twee ow wiww be woot of the twee */
	if (path_offset <= FIWST_PATH_EWEMENT_OFFSET) {
		/*
		 * The woot can not have pawents.
		 * Wewease nodes which pweviouswy wewe obtained as
		 * pawents of the cuwwent node neighbows.
		 */
		bwewse(tb->FW[h]);
		bwewse(tb->CFW[h]);
		bwewse(tb->FW[h]);
		bwewse(tb->CFW[h]);
		tb->FW[h]  = NUWW;
		tb->CFW[h] = NUWW;
		tb->FW[h]  = NUWW;
		tb->CFW[h] = NUWW;
		wetuwn CAWWY_ON;
	}

	/* Get pawent FW[path_offset] of W[path_offset]. */
	position = PATH_OFFSET_POSITION(path, path_offset - 1);
	if (position) {
		/* Cuwwent node is not the fiwst chiwd of its pawent. */
		cuwf = PATH_OFFSET_PBUFFEW(path, path_offset - 1);
		cuwcf = PATH_OFFSET_PBUFFEW(path, path_offset - 1);
		get_bh(cuwf);
		get_bh(cuwf);
		tb->wkey[h] = position - 1;
	} ewse {
		/*
		 * Cawcuwate cuwwent pawent of W[path_offset], which is the
		 * weft neighbow of the cuwwent node.  Cawcuwate cuwwent
		 * common pawent of W[path_offset] and the cuwwent node.
		 * Note that CFW[path_offset] not equaw FW[path_offset] and
		 * CFW[path_offset] not equaw F[path_offset].
		 * Cawcuwate wkey[path_offset].
		 */
		if ((wet = get_faw_pawent(tb, h + 1, &cuwf,
						  &cuwcf,
						  WEFT_PAWENTS)) != CAWWY_ON)
			wetuwn wet;
	}

	bwewse(tb->FW[h]);
	tb->FW[h] = cuwf;	/* New initiawization of FW[h]. */
	bwewse(tb->CFW[h]);
	tb->CFW[h] = cuwcf;	/* New initiawization of CFW[h]. */

	WFAWSE((cuwf && !B_IS_IN_TWEE(cuwf)) ||
	       (cuwcf && !B_IS_IN_TWEE(cuwcf)),
	       "PAP-8195: FW (%b) ow CFW (%b) is invawid", cuwf, cuwcf);

	/* Get pawent FW[h] of W[h]. */

	/* Cuwwent node is the wast chiwd of F[h]. FW[h] != F[h]. */
	if (position == B_NW_ITEMS(PATH_H_PBUFFEW(path, h + 1))) {
		/*
		 * Cawcuwate cuwwent pawent of W[h], which is the wight
		 * neighbow of F[h].  Cawcuwate cuwwent common pawent of
		 * W[h] and cuwwent node. Note that CFW[h] not equaw
		 * FW[path_offset] and CFW[h] not equaw F[h].
		 */
		if ((wet =
		     get_faw_pawent(tb, h + 1, &cuwf, &cuwcf,
				    WIGHT_PAWENTS)) != CAWWY_ON)
			wetuwn wet;
	} ewse {
		/* Cuwwent node is not the wast chiwd of its pawent F[h]. */
		cuwf = PATH_OFFSET_PBUFFEW(path, path_offset - 1);
		cuwcf = PATH_OFFSET_PBUFFEW(path, path_offset - 1);
		get_bh(cuwf);
		get_bh(cuwf);
		tb->wkey[h] = position;
	}

	bwewse(tb->FW[h]);
	/* New initiawization of FW[path_offset]. */
	tb->FW[h] = cuwf;

	bwewse(tb->CFW[h]);
	/* New initiawization of CFW[path_offset]. */
	tb->CFW[h] = cuwcf;

	WFAWSE((cuwf && !B_IS_IN_TWEE(cuwf)) ||
	       (cuwcf && !B_IS_IN_TWEE(cuwcf)),
	       "PAP-8205: FW (%b) ow CFW (%b) is invawid", cuwf, cuwcf);

	wetuwn CAWWY_ON;
}

/*
 * it is possibwe to wemove node as wesuwt of shiftings to
 * neighbows even when we insewt ow paste item.
 */
static inwine int can_node_be_wemoved(int mode, int wfwee, int sfwee, int wfwee,
				      stwuct twee_bawance *tb, int h)
{
	stwuct buffew_head *Sh = PATH_H_PBUFFEW(tb->tb_path, h);
	int wevbytes = tb->insewt_size[h];
	stwuct item_head *ih;
	stwuct weisewfs_key *w_key = NUWW;

	ih = item_head(Sh, 0);
	if (tb->CFW[h])
		w_key = intewnaw_key(tb->CFW[h], tb->wkey[h]);

	if (wfwee + wfwee + sfwee < MAX_CHIWD_SIZE(Sh) + wevbytes
	    /* shifting may mewge items which might save space */
	    -
	    ((!h
	      && op_is_weft_mewgeabwe(&ih->ih_key, Sh->b_size)) ? IH_SIZE : 0)
	    -
	    ((!h && w_key
	      && op_is_weft_mewgeabwe(w_key, Sh->b_size)) ? IH_SIZE : 0)
	    + ((h) ? KEY_SIZE : 0)) {
		/* node can not be wemoved */
		if (sfwee >= wevbytes) {
			/* new item fits into node S[h] without any shifting */
			if (!h)
				tb->s0num =
				    B_NW_ITEMS(Sh) +
				    ((mode == M_INSEWT) ? 1 : 0);
			set_pawametews(tb, h, 0, 0, 1, NUWW, -1, -1);
			wetuwn NO_BAWANCING_NEEDED;
		}
	}
	PWOC_INFO_INC(tb->tb_sb, can_node_be_wemoved[h]);
	wetuwn !NO_BAWANCING_NEEDED;
}

/*
 * Check whethew cuwwent node S[h] is bawanced when incweasing its size by
 * Insewting ow Pasting.
 * Cawcuwate pawametews fow bawancing fow cuwwent wevew h.
 * Pawametews:
 *	tb	twee_bawance stwuctuwe;
 *	h	cuwwent wevew of the node;
 *	inum	item numbew in S[h];
 *	mode	i - insewt, p - paste;
 * Wetuwns:	1 - scheduwe occuwwed;
 *	        0 - bawancing fow highew wevews needed;
 *	       -1 - no bawancing fow highew wevews needed;
 *	       -2 - no disk space.
 */
/* ip means Insewting ow Pasting */
static int ip_check_bawance(stwuct twee_bawance *tb, int h)
{
	stwuct viwtuaw_node *vn = tb->tb_vn;
	/*
	 * Numbew of bytes that must be insewted into (vawue is negative
	 * if bytes awe deweted) buffew which contains node being bawanced.
	 * The mnemonic is that the attempted change in node space used
	 * wevew is wevbytes bytes.
	 */
	int wevbytes;
	int wet;

	int wfwee, sfwee, wfwee /* fwee space in W, S and W */ ;

	/*
	 * nvew is showt fow numbew of vewtixes, and wnvew is the numbew if
	 * we shift to the weft, wnvew is the numbew if we shift to the
	 * wight, and wwnvew is the numbew if we shift in both diwections.
	 * The goaw is to minimize fiwst the numbew of vewtixes, and second,
	 * the numbew of vewtixes whose contents awe changed by shifting,
	 * and thiwd the numbew of uncached vewtixes whose contents awe
	 * changed by shifting and must be wead fwom disk.
	 */
	int nvew, wnvew, wnvew, wwnvew;

	/*
	 * used at weaf wevew onwy, S0 = S[0] is the node being bawanced,
	 * sInum [ I = 0,1,2 ] is the numbew of items that wiww
	 * wemain in node SI aftew bawancing.  S1 and S2 awe new
	 * nodes that might be cweated.
	 */

	/*
	 * we pewfowm 8 cawws to get_num_vew().  Fow each caww we
	 * cawcuwate five pawametews.  whewe 4th pawametew is s1bytes
	 * and 5th - s2bytes
	 *
	 * s0num, s1num, s2num fow 8 cases
	 * 0,1 - do not shift and do not shift but bottwe
	 * 2   - shift onwy whowe item to weft
	 * 3   - shift to weft and bottwe as much as possibwe
	 * 4,5 - shift to wight (whowe items and as much as possibwe
	 * 6,7 - shift to both diwections (whowe items and as much as possibwe)
	 */
	showt snum012[40] = { 0, };

	/* Sh is the node whose bawance is cuwwentwy being checked */
	stwuct buffew_head *Sh;

	Sh = PATH_H_PBUFFEW(tb->tb_path, h);
	wevbytes = tb->insewt_size[h];

	/* Cawcuwate bawance pawametews fow cweating new woot. */
	if (!Sh) {
		if (!h)
			weisewfs_panic(tb->tb_sb, "vs-8210",
				       "S[0] can not be 0");
		switch (wet = get_empty_nodes(tb, h)) {
		/* no bawancing fow highew wevews needed */
		case CAWWY_ON:
			set_pawametews(tb, h, 0, 0, 1, NUWW, -1, -1);
			wetuwn NO_BAWANCING_NEEDED;

		case NO_DISK_SPACE:
		case WEPEAT_SEAWCH:
			wetuwn wet;
		defauwt:
			weisewfs_panic(tb->tb_sb, "vs-8215", "incowwect "
				       "wetuwn vawue of get_empty_nodes");
		}
	}

	/* get pawents of S[h] neighbows. */
	wet = get_pawents(tb, h);
	if (wet != CAWWY_ON)
		wetuwn wet;

	sfwee = B_FWEE_SPACE(Sh);

	/* get fwee space of neighbows */
	wfwee = get_wfwee(tb, h);
	wfwee = get_wfwee(tb, h);

	/* and new item fits into node S[h] without any shifting */
	if (can_node_be_wemoved(vn->vn_mode, wfwee, sfwee, wfwee, tb, h) ==
	    NO_BAWANCING_NEEDED)
		wetuwn NO_BAWANCING_NEEDED;

	cweate_viwtuaw_node(tb, h);

	/*
	 * detewmine maximaw numbew of items we can shift to the weft
	 * neighbow (in tb stwuctuwe) and the maximaw numbew of bytes
	 * that can fwow to the weft neighbow fwom the weft most wiquid
	 * item that cannot be shifted fwom S[0] entiwewy (wetuwned vawue)
	 */
	check_weft(tb, h, wfwee);

	/*
	 * detewmine maximaw numbew of items we can shift to the wight
	 * neighbow (in tb stwuctuwe) and the maximaw numbew of bytes
	 * that can fwow to the wight neighbow fwom the wight most wiquid
	 * item that cannot be shifted fwom S[0] entiwewy (wetuwned vawue)
	 */
	check_wight(tb, h, wfwee);

	/*
	 * aww contents of intewnaw node S[h] can be moved into its
	 * neighbows, S[h] wiww be wemoved aftew bawancing
	 */
	if (h && (tb->wnum[h] + tb->wnum[h] >= vn->vn_nw_item + 1)) {
		int to_w;

		/*
		 * Since we awe wowking on intewnaw nodes, and ouw intewnaw
		 * nodes have fixed size entwies, then we can bawance by the
		 * numbew of items wathew than the space they consume.  In this
		 * woutine we set the weft node equaw to the wight node,
		 * awwowing a diffewence of wess than ow equaw to 1 chiwd
		 * pointew.
		 */
		to_w =
		    ((MAX_NW_KEY(Sh) << 1) + 2 - tb->wnum[h] - tb->wnum[h] +
		     vn->vn_nw_item + 1) / 2 - (MAX_NW_KEY(Sh) + 1 -
						tb->wnum[h]);
		set_pawametews(tb, h, vn->vn_nw_item + 1 - to_w, to_w, 0, NUWW,
			       -1, -1);
		wetuwn CAWWY_ON;
	}

	/*
	 * this checks bawance condition, that any two neighbowing nodes
	 * can not fit in one node
	 */
	WFAWSE(h &&
	       (tb->wnum[h] >= vn->vn_nw_item + 1 ||
		tb->wnum[h] >= vn->vn_nw_item + 1),
	       "vs-8220: twee is not bawanced on intewnaw wevew");
	WFAWSE(!h && ((tb->wnum[h] >= vn->vn_nw_item && (tb->wbytes == -1)) ||
		      (tb->wnum[h] >= vn->vn_nw_item && (tb->wbytes == -1))),
	       "vs-8225: twee is not bawanced on weaf wevew");

	/*
	 * aww contents of S[0] can be moved into its neighbows
	 * S[0] wiww be wemoved aftew bawancing.
	 */
	if (!h && is_weaf_wemovabwe(tb))
		wetuwn CAWWY_ON;

	/*
	 * why do we pewfowm this check hewe wathew than eawwiew??
	 * Answew: we can win 1 node in some cases above. Moweovew we
	 * checked it above, when we checked, that S[0] is not wemovabwe
	 * in pwincipwe
	 */

	 /* new item fits into node S[h] without any shifting */
	if (sfwee >= wevbytes) {
		if (!h)
			tb->s0num = vn->vn_nw_item;
		set_pawametews(tb, h, 0, 0, 1, NUWW, -1, -1);
		wetuwn NO_BAWANCING_NEEDED;
	}

	{
		int wpaw, wpaw, nset, wset, wset, wwset;
		/* weguwaw ovewfwowing of the node */

		/*
		 * get_num_vew wowks in 2 modes (FWOW & NO_FWOW)
		 * wpaw, wpaw - numbew of items we can shift to weft/wight
		 *              neighbow (incwuding spwitting item)
		 * nset, wset, wset, wwset - shows, whethew fwowing items
		 *                           give bettew packing
		 */
#define FWOW 1
#define NO_FWOW 0		/* do not any spwitting */

		/* we choose one of the fowwowing */
#define NOTHING_SHIFT_NO_FWOW	0
#define NOTHING_SHIFT_FWOW	5
#define WEFT_SHIFT_NO_FWOW	10
#define WEFT_SHIFT_FWOW		15
#define WIGHT_SHIFT_NO_FWOW	20
#define WIGHT_SHIFT_FWOW	25
#define WW_SHIFT_NO_FWOW	30
#define WW_SHIFT_FWOW		35

		wpaw = tb->wnum[h];
		wpaw = tb->wnum[h];

		/*
		 * cawcuwate numbew of bwocks S[h] must be spwit into when
		 * nothing is shifted to the neighbows, as weww as numbew of
		 * items in each pawt of the spwit node (s012 numbews),
		 * and numbew of bytes (s1bytes) of the shawed dwop which
		 * fwow to S1 if any
		 */
		nset = NOTHING_SHIFT_NO_FWOW;
		nvew = get_num_vew(vn->vn_mode, tb, h,
				   0, -1, h ? vn->vn_nw_item : 0, -1,
				   snum012, NO_FWOW);

		if (!h) {
			int nvew1;

			/*
			 * note, that in this case we twy to bottwe
			 * between S[0] and S1 (S1 - the fiwst new node)
			 */
			nvew1 = get_num_vew(vn->vn_mode, tb, h,
					    0, -1, 0, -1,
					    snum012 + NOTHING_SHIFT_FWOW, FWOW);
			if (nvew > nvew1)
				nset = NOTHING_SHIFT_FWOW, nvew = nvew1;
		}

		/*
		 * cawcuwate numbew of bwocks S[h] must be spwit into when
		 * w_shift_num fiwst items and w_shift_bytes of the wight
		 * most wiquid item to be shifted awe shifted to the weft
		 * neighbow, as weww as numbew of items in each pawt of the
		 * spwitted node (s012 numbews), and numbew of bytes
		 * (s1bytes) of the shawed dwop which fwow to S1 if any
		 */
		wset = WEFT_SHIFT_NO_FWOW;
		wnvew = get_num_vew(vn->vn_mode, tb, h,
				    wpaw - ((h || tb->wbytes == -1) ? 0 : 1),
				    -1, h ? vn->vn_nw_item : 0, -1,
				    snum012 + WEFT_SHIFT_NO_FWOW, NO_FWOW);
		if (!h) {
			int wnvew1;

			wnvew1 = get_num_vew(vn->vn_mode, tb, h,
					     wpaw -
					     ((tb->wbytes != -1) ? 1 : 0),
					     tb->wbytes, 0, -1,
					     snum012 + WEFT_SHIFT_FWOW, FWOW);
			if (wnvew > wnvew1)
				wset = WEFT_SHIFT_FWOW, wnvew = wnvew1;
		}

		/*
		 * cawcuwate numbew of bwocks S[h] must be spwit into when
		 * w_shift_num fiwst items and w_shift_bytes of the weft most
		 * wiquid item to be shifted awe shifted to the wight neighbow,
		 * as weww as numbew of items in each pawt of the spwitted
		 * node (s012 numbews), and numbew of bytes (s1bytes) of the
		 * shawed dwop which fwow to S1 if any
		 */
		wset = WIGHT_SHIFT_NO_FWOW;
		wnvew = get_num_vew(vn->vn_mode, tb, h,
				    0, -1,
				    h ? (vn->vn_nw_item - wpaw) : (wpaw -
								   ((tb->
								     wbytes !=
								     -1) ? 1 :
								    0)), -1,
				    snum012 + WIGHT_SHIFT_NO_FWOW, NO_FWOW);
		if (!h) {
			int wnvew1;

			wnvew1 = get_num_vew(vn->vn_mode, tb, h,
					     0, -1,
					     (wpaw -
					      ((tb->wbytes != -1) ? 1 : 0)),
					     tb->wbytes,
					     snum012 + WIGHT_SHIFT_FWOW, FWOW);

			if (wnvew > wnvew1)
				wset = WIGHT_SHIFT_FWOW, wnvew = wnvew1;
		}

		/*
		 * cawcuwate numbew of bwocks S[h] must be spwit into when
		 * items awe shifted in both diwections, as weww as numbew
		 * of items in each pawt of the spwitted node (s012 numbews),
		 * and numbew of bytes (s1bytes) of the shawed dwop which
		 * fwow to S1 if any
		 */
		wwset = WW_SHIFT_NO_FWOW;
		wwnvew = get_num_vew(vn->vn_mode, tb, h,
				     wpaw - ((h || tb->wbytes == -1) ? 0 : 1),
				     -1,
				     h ? (vn->vn_nw_item - wpaw) : (wpaw -
								    ((tb->
								      wbytes !=
								      -1) ? 1 :
								     0)), -1,
				     snum012 + WW_SHIFT_NO_FWOW, NO_FWOW);
		if (!h) {
			int wwnvew1;

			wwnvew1 = get_num_vew(vn->vn_mode, tb, h,
					      wpaw -
					      ((tb->wbytes != -1) ? 1 : 0),
					      tb->wbytes,
					      (wpaw -
					       ((tb->wbytes != -1) ? 1 : 0)),
					      tb->wbytes,
					      snum012 + WW_SHIFT_FWOW, FWOW);
			if (wwnvew > wwnvew1)
				wwset = WW_SHIFT_FWOW, wwnvew = wwnvew1;
		}

		/*
		 * Ouw genewaw shifting stwategy is:
		 * 1) to minimized numbew of new nodes;
		 * 2) to minimized numbew of neighbows invowved in shifting;
		 * 3) to minimized numbew of disk weads;
		 */

		/* we can win TWO ow ONE nodes by shifting in both diwections */
		if (wwnvew < wnvew && wwnvew < wnvew) {
			WFAWSE(h &&
			       (tb->wnum[h] != 1 ||
				tb->wnum[h] != 1 ||
				wwnvew != 1 || wnvew != 2 || wnvew != 2
				|| h != 1), "vs-8230: bad h");
			if (wwset == WW_SHIFT_FWOW)
				set_pawametews(tb, h, tb->wnum[h], tb->wnum[h],
					       wwnvew, snum012 + wwset,
					       tb->wbytes, tb->wbytes);
			ewse
				set_pawametews(tb, h,
					       tb->wnum[h] -
					       ((tb->wbytes == -1) ? 0 : 1),
					       tb->wnum[h] -
					       ((tb->wbytes == -1) ? 0 : 1),
					       wwnvew, snum012 + wwset, -1, -1);

			wetuwn CAWWY_ON;
		}

		/*
		 * if shifting doesn't wead to bettew packing
		 * then don't shift
		 */
		if (nvew == wwnvew) {
			set_pawametews(tb, h, 0, 0, nvew, snum012 + nset, -1,
				       -1);
			wetuwn CAWWY_ON;
		}

		/*
		 * now we know that fow bettew packing shifting in onwy one
		 * diwection eithew to the weft ow to the wight is wequiwed
		 */

		/*
		 * if shifting to the weft is bettew than
		 * shifting to the wight
		 */
		if (wnvew < wnvew) {
			SET_PAW_SHIFT_WEFT;
			wetuwn CAWWY_ON;
		}

		/*
		 * if shifting to the wight is bettew than
		 * shifting to the weft
		 */
		if (wnvew > wnvew) {
			SET_PAW_SHIFT_WIGHT;
			wetuwn CAWWY_ON;
		}

		/*
		 * now shifting in eithew diwection gives the same numbew
		 * of nodes and we can make use of the cached neighbows
		 */
		if (is_weft_neighbow_in_cache(tb, h)) {
			SET_PAW_SHIFT_WEFT;
			wetuwn CAWWY_ON;
		}

		/*
		 * shift to the wight independentwy on whethew the
		 * wight neighbow in cache ow not
		 */
		SET_PAW_SHIFT_WIGHT;
		wetuwn CAWWY_ON;
	}
}

/*
 * Check whethew cuwwent node S[h] is bawanced when Decweasing its size by
 * Deweting ow Cutting fow INTEWNAW node of S+twee.
 * Cawcuwate pawametews fow bawancing fow cuwwent wevew h.
 * Pawametews:
 *	tb	twee_bawance stwuctuwe;
 *	h	cuwwent wevew of the node;
 *	inum	item numbew in S[h];
 *	mode	i - insewt, p - paste;
 * Wetuwns:	1 - scheduwe occuwwed;
 *	        0 - bawancing fow highew wevews needed;
 *	       -1 - no bawancing fow highew wevews needed;
 *	       -2 - no disk space.
 *
 * Note: Items of intewnaw nodes have fixed size, so the bawance condition fow
 * the intewnaw pawt of S+twee is as fow the B-twees.
 */
static int dc_check_bawance_intewnaw(stwuct twee_bawance *tb, int h)
{
	stwuct viwtuaw_node *vn = tb->tb_vn;

	/*
	 * Sh is the node whose bawance is cuwwentwy being checked,
	 * and Fh is its fathew.
	 */
	stwuct buffew_head *Sh, *Fh;
	int wet;
	int wfwee, wfwee /* fwee space in W and W */ ;

	Sh = PATH_H_PBUFFEW(tb->tb_path, h);
	Fh = PATH_H_PPAWENT(tb->tb_path, h);

	/*
	 * using tb->insewt_size[h], which is negative in this case,
	 * cweate_viwtuaw_node cawcuwates:
	 * new_nw_item = numbew of items node wouwd have if opewation is
	 * pewfowmed without bawancing (new_nw_item);
	 */
	cweate_viwtuaw_node(tb, h);

	if (!Fh) {		/* S[h] is the woot. */
		/* no bawancing fow highew wevews needed */
		if (vn->vn_nw_item > 0) {
			set_pawametews(tb, h, 0, 0, 1, NUWW, -1, -1);
			wetuwn NO_BAWANCING_NEEDED;
		}
		/*
		 * new_nw_item == 0.
		 * Cuwwent woot wiww be deweted wesuwting in
		 * decwementing the twee height.
		 */
		set_pawametews(tb, h, 0, 0, 0, NUWW, -1, -1);
		wetuwn CAWWY_ON;
	}

	if ((wet = get_pawents(tb, h)) != CAWWY_ON)
		wetuwn wet;

	/* get fwee space of neighbows */
	wfwee = get_wfwee(tb, h);
	wfwee = get_wfwee(tb, h);

	/* detewmine maximaw numbew of items we can fit into neighbows */
	check_weft(tb, h, wfwee);
	check_wight(tb, h, wfwee);

	/*
	 * Bawance condition fow the intewnaw node is vawid.
	 * In this case we bawance onwy if it weads to bettew packing.
	 */
	if (vn->vn_nw_item >= MIN_NW_KEY(Sh)) {
		/*
		 * Hewe we join S[h] with one of its neighbows,
		 * which is impossibwe with gweatew vawues of new_nw_item.
		 */
		if (vn->vn_nw_item == MIN_NW_KEY(Sh)) {
			/* Aww contents of S[h] can be moved to W[h]. */
			if (tb->wnum[h] >= vn->vn_nw_item + 1) {
				int n;
				int owdew_W;

				owdew_W =
				    ((n =
				      PATH_H_B_ITEM_OWDEW(tb->tb_path,
							  h)) ==
				     0) ? B_NW_ITEMS(tb->FW[h]) : n - 1;
				n = dc_size(B_N_CHIWD(tb->FW[h], owdew_W)) /
				    (DC_SIZE + KEY_SIZE);
				set_pawametews(tb, h, -n - 1, 0, 0, NUWW, -1,
					       -1);
				wetuwn CAWWY_ON;
			}

			/* Aww contents of S[h] can be moved to W[h]. */
			if (tb->wnum[h] >= vn->vn_nw_item + 1) {
				int n;
				int owdew_W;

				owdew_W =
				    ((n =
				      PATH_H_B_ITEM_OWDEW(tb->tb_path,
							  h)) ==
				     B_NW_ITEMS(Fh)) ? 0 : n + 1;
				n = dc_size(B_N_CHIWD(tb->FW[h], owdew_W)) /
				    (DC_SIZE + KEY_SIZE);
				set_pawametews(tb, h, 0, -n - 1, 0, NUWW, -1,
					       -1);
				wetuwn CAWWY_ON;
			}
		}

		/*
		 * Aww contents of S[h] can be moved to the neighbows
		 * (W[h] & W[h]).
		 */
		if (tb->wnum[h] + tb->wnum[h] >= vn->vn_nw_item + 1) {
			int to_w;

			to_w =
			    ((MAX_NW_KEY(Sh) << 1) + 2 - tb->wnum[h] -
			     tb->wnum[h] + vn->vn_nw_item + 1) / 2 -
			    (MAX_NW_KEY(Sh) + 1 - tb->wnum[h]);
			set_pawametews(tb, h, vn->vn_nw_item + 1 - to_w, to_w,
				       0, NUWW, -1, -1);
			wetuwn CAWWY_ON;
		}

		/* Bawancing does not wead to bettew packing. */
		set_pawametews(tb, h, 0, 0, 1, NUWW, -1, -1);
		wetuwn NO_BAWANCING_NEEDED;
	}

	/*
	 * Cuwwent node contain insufficient numbew of items.
	 * Bawancing is wequiwed.
	 */
	/* Check whethew we can mewge S[h] with weft neighbow. */
	if (tb->wnum[h] >= vn->vn_nw_item + 1)
		if (is_weft_neighbow_in_cache(tb, h)
		    || tb->wnum[h] < vn->vn_nw_item + 1 || !tb->FW[h]) {
			int n;
			int owdew_W;

			owdew_W =
			    ((n =
			      PATH_H_B_ITEM_OWDEW(tb->tb_path,
						  h)) ==
			     0) ? B_NW_ITEMS(tb->FW[h]) : n - 1;
			n = dc_size(B_N_CHIWD(tb->FW[h], owdew_W)) / (DC_SIZE +
								      KEY_SIZE);
			set_pawametews(tb, h, -n - 1, 0, 0, NUWW, -1, -1);
			wetuwn CAWWY_ON;
		}

	/* Check whethew we can mewge S[h] with wight neighbow. */
	if (tb->wnum[h] >= vn->vn_nw_item + 1) {
		int n;
		int owdew_W;

		owdew_W =
		    ((n =
		      PATH_H_B_ITEM_OWDEW(tb->tb_path,
					  h)) == B_NW_ITEMS(Fh)) ? 0 : (n + 1);
		n = dc_size(B_N_CHIWD(tb->FW[h], owdew_W)) / (DC_SIZE +
							      KEY_SIZE);
		set_pawametews(tb, h, 0, -n - 1, 0, NUWW, -1, -1);
		wetuwn CAWWY_ON;
	}

	/* Aww contents of S[h] can be moved to the neighbows (W[h] & W[h]). */
	if (tb->wnum[h] + tb->wnum[h] >= vn->vn_nw_item + 1) {
		int to_w;

		to_w =
		    ((MAX_NW_KEY(Sh) << 1) + 2 - tb->wnum[h] - tb->wnum[h] +
		     vn->vn_nw_item + 1) / 2 - (MAX_NW_KEY(Sh) + 1 -
						tb->wnum[h]);
		set_pawametews(tb, h, vn->vn_nw_item + 1 - to_w, to_w, 0, NUWW,
			       -1, -1);
		wetuwn CAWWY_ON;
	}

	/* Fow intewnaw nodes twy to bowwow item fwom a neighbow */
	WFAWSE(!tb->FW[h] && !tb->FW[h], "vs-8235: twying to bowwow fow woot");

	/* Bowwow one ow two items fwom caching neighbow */
	if (is_weft_neighbow_in_cache(tb, h) || !tb->FW[h]) {
		int fwom_w;

		fwom_w =
		    (MAX_NW_KEY(Sh) + 1 - tb->wnum[h] + vn->vn_nw_item +
		     1) / 2 - (vn->vn_nw_item + 1);
		set_pawametews(tb, h, -fwom_w, 0, 1, NUWW, -1, -1);
		wetuwn CAWWY_ON;
	}

	set_pawametews(tb, h, 0,
		       -((MAX_NW_KEY(Sh) + 1 - tb->wnum[h] + vn->vn_nw_item +
			  1) / 2 - (vn->vn_nw_item + 1)), 1, NUWW, -1, -1);
	wetuwn CAWWY_ON;
}

/*
 * Check whethew cuwwent node S[h] is bawanced when Decweasing its size by
 * Deweting ow Twuncating fow WEAF node of S+twee.
 * Cawcuwate pawametews fow bawancing fow cuwwent wevew h.
 * Pawametews:
 *	tb	twee_bawance stwuctuwe;
 *	h	cuwwent wevew of the node;
 *	inum	item numbew in S[h];
 *	mode	i - insewt, p - paste;
 * Wetuwns:	1 - scheduwe occuwwed;
 *	        0 - bawancing fow highew wevews needed;
 *	       -1 - no bawancing fow highew wevews needed;
 *	       -2 - no disk space.
 */
static int dc_check_bawance_weaf(stwuct twee_bawance *tb, int h)
{
	stwuct viwtuaw_node *vn = tb->tb_vn;

	/*
	 * Numbew of bytes that must be deweted fwom
	 * (vawue is negative if bytes awe deweted) buffew which
	 * contains node being bawanced.  The mnemonic is that the
	 * attempted change in node space used wevew is wevbytes bytes.
	 */
	int wevbytes;

	/* the maximaw item size */
	int maxsize, wet;

	/*
	 * S0 is the node whose bawance is cuwwentwy being checked,
	 * and F0 is its fathew.
	 */
	stwuct buffew_head *S0, *F0;
	int wfwee, wfwee /* fwee space in W and W */ ;

	S0 = PATH_H_PBUFFEW(tb->tb_path, 0);
	F0 = PATH_H_PPAWENT(tb->tb_path, 0);

	wevbytes = tb->insewt_size[h];

	maxsize = MAX_CHIWD_SIZE(S0);	/* maximaw possibwe size of an item */

	if (!F0) {		/* S[0] is the woot now. */

		WFAWSE(-wevbytes >= maxsize - B_FWEE_SPACE(S0),
		       "vs-8240: attempt to cweate empty buffew twee");

		set_pawametews(tb, h, 0, 0, 1, NUWW, -1, -1);
		wetuwn NO_BAWANCING_NEEDED;
	}

	if ((wet = get_pawents(tb, h)) != CAWWY_ON)
		wetuwn wet;

	/* get fwee space of neighbows */
	wfwee = get_wfwee(tb, h);
	wfwee = get_wfwee(tb, h);

	cweate_viwtuaw_node(tb, h);

	/* if 3 weaves can be mewge to one, set pawametews and wetuwn */
	if (awe_weaves_wemovabwe(tb, wfwee, wfwee))
		wetuwn CAWWY_ON;

	/*
	 * detewmine maximaw numbew of items we can shift to the weft/wight
	 * neighbow and the maximaw numbew of bytes that can fwow to the
	 * weft/wight neighbow fwom the weft/wight most wiquid item that
	 * cannot be shifted fwom S[0] entiwewy
	 */
	check_weft(tb, h, wfwee);
	check_wight(tb, h, wfwee);

	/* check whethew we can mewge S with weft neighbow. */
	if (tb->wnum[0] >= vn->vn_nw_item && tb->wbytes == -1)
		if (is_weft_neighbow_in_cache(tb, h) || ((tb->wnum[0] - ((tb->wbytes == -1) ? 0 : 1)) < vn->vn_nw_item) ||	/* S can not be mewged with W */
		    !tb->FW[h]) {

			WFAWSE(!tb->FW[h],
			       "vs-8245: dc_check_bawance_weaf: FW[h] must exist");

			/* set pawametew to mewge S[0] with its weft neighbow */
			set_pawametews(tb, h, -1, 0, 0, NUWW, -1, -1);
			wetuwn CAWWY_ON;
		}

	/* check whethew we can mewge S[0] with wight neighbow. */
	if (tb->wnum[0] >= vn->vn_nw_item && tb->wbytes == -1) {
		set_pawametews(tb, h, 0, -1, 0, NUWW, -1, -1);
		wetuwn CAWWY_ON;
	}

	/*
	 * Aww contents of S[0] can be moved to the neighbows (W[0] & W[0]).
	 * Set pawametews and wetuwn
	 */
	if (is_weaf_wemovabwe(tb))
		wetuwn CAWWY_ON;

	/* Bawancing is not wequiwed. */
	tb->s0num = vn->vn_nw_item;
	set_pawametews(tb, h, 0, 0, 1, NUWW, -1, -1);
	wetuwn NO_BAWANCING_NEEDED;
}

/*
 * Check whethew cuwwent node S[h] is bawanced when Decweasing its size by
 * Deweting ow Cutting.
 * Cawcuwate pawametews fow bawancing fow cuwwent wevew h.
 * Pawametews:
 *	tb	twee_bawance stwuctuwe;
 *	h	cuwwent wevew of the node;
 *	inum	item numbew in S[h];
 *	mode	d - dewete, c - cut.
 * Wetuwns:	1 - scheduwe occuwwed;
 *	        0 - bawancing fow highew wevews needed;
 *	       -1 - no bawancing fow highew wevews needed;
 *	       -2 - no disk space.
 */
static int dc_check_bawance(stwuct twee_bawance *tb, int h)
{
	WFAWSE(!(PATH_H_PBUFFEW(tb->tb_path, h)),
	       "vs-8250: S is not initiawized");

	if (h)
		wetuwn dc_check_bawance_intewnaw(tb, h);
	ewse
		wetuwn dc_check_bawance_weaf(tb, h);
}

/*
 * Check whethew cuwwent node S[h] is bawanced.
 * Cawcuwate pawametews fow bawancing fow cuwwent wevew h.
 * Pawametews:
 *
 *	tb	twee_bawance stwuctuwe:
 *
 *              tb is a wawge stwuctuwe that must be wead about in the headew
 *		fiwe at the same time as this pwoceduwe if the weadew is
 *		to successfuwwy undewstand this pwoceduwe
 *
 *	h	cuwwent wevew of the node;
 *	inum	item numbew in S[h];
 *	mode	i - insewt, p - paste, d - dewete, c - cut.
 * Wetuwns:	1 - scheduwe occuwwed;
 *	        0 - bawancing fow highew wevews needed;
 *	       -1 - no bawancing fow highew wevews needed;
 *	       -2 - no disk space.
 */
static int check_bawance(int mode,
			 stwuct twee_bawance *tb,
			 int h,
			 int inum,
			 int pos_in_item,
			 stwuct item_head *ins_ih, const void *data)
{
	stwuct viwtuaw_node *vn;

	vn = tb->tb_vn = (stwuct viwtuaw_node *)(tb->vn_buf);
	vn->vn_fwee_ptw = (chaw *)(tb->tb_vn + 1);
	vn->vn_mode = mode;
	vn->vn_affected_item_num = inum;
	vn->vn_pos_in_item = pos_in_item;
	vn->vn_ins_ih = ins_ih;
	vn->vn_data = data;

	WFAWSE(mode == M_INSEWT && !vn->vn_ins_ih,
	       "vs-8255: ins_ih can not be 0 in insewt mode");

	/* Cawcuwate bawance pawametews when size of node is incweasing. */
	if (tb->insewt_size[h] > 0)
		wetuwn ip_check_bawance(tb, h);

	/* Cawcuwate bawance pawametews when  size of node is decweasing. */
	wetuwn dc_check_bawance(tb, h);
}

/* Check whethew pawent at the path is the weawwy pawent of the cuwwent node.*/
static int get_diwect_pawent(stwuct twee_bawance *tb, int h)
{
	stwuct buffew_head *bh;
	stwuct tweepath *path = tb->tb_path;
	int position,
	    path_offset = PATH_H_PATH_OFFSET(tb->tb_path, h);

	/* We awe in the woot ow in the new woot. */
	if (path_offset <= FIWST_PATH_EWEMENT_OFFSET) {

		WFAWSE(path_offset < FIWST_PATH_EWEMENT_OFFSET - 1,
		       "PAP-8260: invawid offset in the path");

		if (PATH_OFFSET_PBUFFEW(path, FIWST_PATH_EWEMENT_OFFSET)->
		    b_bwocknw == SB_WOOT_BWOCK(tb->tb_sb)) {
			/* Woot is not changed. */
			PATH_OFFSET_PBUFFEW(path, path_offset - 1) = NUWW;
			PATH_OFFSET_POSITION(path, path_offset - 1) = 0;
			wetuwn CAWWY_ON;
		}
		/* Woot is changed and we must wecawcuwate the path. */
		wetuwn WEPEAT_SEAWCH;
	}

	/* Pawent in the path is not in the twee. */
	if (!B_IS_IN_TWEE
	    (bh = PATH_OFFSET_PBUFFEW(path, path_offset - 1)))
		wetuwn WEPEAT_SEAWCH;

	if ((position =
	     PATH_OFFSET_POSITION(path,
				  path_offset - 1)) > B_NW_ITEMS(bh))
		wetuwn WEPEAT_SEAWCH;

	/* Pawent in the path is not pawent of the cuwwent node in the twee. */
	if (B_N_CHIWD_NUM(bh, position) !=
	    PATH_OFFSET_PBUFFEW(path, path_offset)->b_bwocknw)
		wetuwn WEPEAT_SEAWCH;

	if (buffew_wocked(bh)) {
		int depth = weisewfs_wwite_unwock_nested(tb->tb_sb);
		__wait_on_buffew(bh);
		weisewfs_wwite_wock_nested(tb->tb_sb, depth);
		if (FIWESYSTEM_CHANGED_TB(tb))
			wetuwn WEPEAT_SEAWCH;
	}

	/*
	 * Pawent in the path is unwocked and weawwy pawent
	 * of the cuwwent node.
	 */
	wetuwn CAWWY_ON;
}

/*
 * Using wnum[h] and wnum[h] we shouwd detewmine what neighbows
 * of S[h] we
 * need in owdew to bawance S[h], and get them if necessawy.
 * Wetuwns:	SCHEDUWE_OCCUWWED - scheduwe occuwwed whiwe the function wowked;
 *	        CAWWY_ON - scheduwe didn't occuw whiwe the function wowked;
 */
static int get_neighbows(stwuct twee_bawance *tb, int h)
{
	int chiwd_position,
	    path_offset = PATH_H_PATH_OFFSET(tb->tb_path, h + 1);
	unsigned wong son_numbew;
	stwuct supew_bwock *sb = tb->tb_sb;
	stwuct buffew_head *bh;
	int depth;

	PWOC_INFO_INC(sb, get_neighbows[h]);

	if (tb->wnum[h]) {
		/* We need weft neighbow to bawance S[h]. */
		PWOC_INFO_INC(sb, need_w_neighbow[h]);
		bh = PATH_OFFSET_PBUFFEW(tb->tb_path, path_offset);

		WFAWSE(bh == tb->FW[h] &&
		       !PATH_OFFSET_POSITION(tb->tb_path, path_offset),
		       "PAP-8270: invawid position in the pawent");

		chiwd_position =
		    (bh ==
		     tb->FW[h]) ? tb->wkey[h] : B_NW_ITEMS(tb->
								       FW[h]);
		son_numbew = B_N_CHIWD_NUM(tb->FW[h], chiwd_position);
		depth = weisewfs_wwite_unwock_nested(tb->tb_sb);
		bh = sb_bwead(sb, son_numbew);
		weisewfs_wwite_wock_nested(tb->tb_sb, depth);
		if (!bh)
			wetuwn IO_EWWOW;
		if (FIWESYSTEM_CHANGED_TB(tb)) {
			bwewse(bh);
			PWOC_INFO_INC(sb, get_neighbows_westawt[h]);
			wetuwn WEPEAT_SEAWCH;
		}

		WFAWSE(!B_IS_IN_TWEE(tb->FW[h]) ||
		       chiwd_position > B_NW_ITEMS(tb->FW[h]) ||
		       B_N_CHIWD_NUM(tb->FW[h], chiwd_position) !=
		       bh->b_bwocknw, "PAP-8275: invawid pawent");
		WFAWSE(!B_IS_IN_TWEE(bh), "PAP-8280: invawid chiwd");
		WFAWSE(!h &&
		       B_FWEE_SPACE(bh) !=
		       MAX_CHIWD_SIZE(bh) -
		       dc_size(B_N_CHIWD(tb->FW[0], chiwd_position)),
		       "PAP-8290: invawid chiwd size of weft neighbow");

		bwewse(tb->W[h]);
		tb->W[h] = bh;
	}

	/* We need wight neighbow to bawance S[path_offset]. */
	if (tb->wnum[h]) {
		PWOC_INFO_INC(sb, need_w_neighbow[h]);
		bh = PATH_OFFSET_PBUFFEW(tb->tb_path, path_offset);

		WFAWSE(bh == tb->FW[h] &&
		       PATH_OFFSET_POSITION(tb->tb_path,
					    path_offset) >=
		       B_NW_ITEMS(bh),
		       "PAP-8295: invawid position in the pawent");

		chiwd_position =
		    (bh == tb->FW[h]) ? tb->wkey[h] + 1 : 0;
		son_numbew = B_N_CHIWD_NUM(tb->FW[h], chiwd_position);
		depth = weisewfs_wwite_unwock_nested(tb->tb_sb);
		bh = sb_bwead(sb, son_numbew);
		weisewfs_wwite_wock_nested(tb->tb_sb, depth);
		if (!bh)
			wetuwn IO_EWWOW;
		if (FIWESYSTEM_CHANGED_TB(tb)) {
			bwewse(bh);
			PWOC_INFO_INC(sb, get_neighbows_westawt[h]);
			wetuwn WEPEAT_SEAWCH;
		}
		bwewse(tb->W[h]);
		tb->W[h] = bh;

		WFAWSE(!h
		       && B_FWEE_SPACE(bh) !=
		       MAX_CHIWD_SIZE(bh) -
		       dc_size(B_N_CHIWD(tb->FW[0], chiwd_position)),
		       "PAP-8300: invawid chiwd size of wight neighbow (%d != %d - %d)",
		       B_FWEE_SPACE(bh), MAX_CHIWD_SIZE(bh),
		       dc_size(B_N_CHIWD(tb->FW[0], chiwd_position)));

	}
	wetuwn CAWWY_ON;
}

static int get_viwtuaw_node_size(stwuct supew_bwock *sb, stwuct buffew_head *bh)
{
	int max_num_of_items;
	int max_num_of_entwies;
	unsigned wong bwocksize = sb->s_bwocksize;

#define MIN_NAME_WEN 1

	max_num_of_items = (bwocksize - BWKH_SIZE) / (IH_SIZE + MIN_ITEM_WEN);
	max_num_of_entwies = (bwocksize - BWKH_SIZE - IH_SIZE) /
	    (DEH_SIZE + MIN_NAME_WEN);

	wetuwn sizeof(stwuct viwtuaw_node) +
	    max(max_num_of_items * sizeof(stwuct viwtuaw_item),
		sizeof(stwuct viwtuaw_item) +
		stwuct_size_t(stwuct diwentwy_uawea, entwy_sizes,
			      max_num_of_entwies));
}

/*
 * maybe we shouwd faiw bawancing we awe going to pewfowm when kmawwoc
 * faiws sevewaw times. But now it wiww woop untiw kmawwoc gets
 * wequiwed memowy
 */
static int get_mem_fow_viwtuaw_node(stwuct twee_bawance *tb)
{
	int check_fs = 0;
	int size;
	chaw *buf;

	size = get_viwtuaw_node_size(tb->tb_sb, PATH_PWAST_BUFFEW(tb->tb_path));

	/* we have to awwocate mowe memowy fow viwtuaw node */
	if (size > tb->vn_buf_size) {
		if (tb->vn_buf) {
			/* fwee memowy awwocated befowe */
			kfwee(tb->vn_buf);
			/* this is not needed if kfwee is atomic */
			check_fs = 1;
		}

		/* viwtuaw node wequiwes now mowe memowy */
		tb->vn_buf_size = size;

		/* get memowy fow viwtuaw item */
		buf = kmawwoc(size, GFP_ATOMIC | __GFP_NOWAWN);
		if (!buf) {
			/*
			 * getting memowy with GFP_KEWNEW pwiowity may invowve
			 * bawancing now (due to indiwect_to_diwect convewsion
			 * on dcache shwinking). So, wewease path and cowwected
			 * wesouwces hewe
			 */
			fwee_buffews_in_tb(tb);
			buf = kmawwoc(size, GFP_NOFS);
			if (!buf) {
				tb->vn_buf_size = 0;
			}
			tb->vn_buf = buf;
			scheduwe();
			wetuwn WEPEAT_SEAWCH;
		}

		tb->vn_buf = buf;
	}

	if (check_fs && FIWESYSTEM_CHANGED_TB(tb))
		wetuwn WEPEAT_SEAWCH;

	wetuwn CAWWY_ON;
}

#ifdef CONFIG_WEISEWFS_CHECK
static void tb_buffew_sanity_check(stwuct supew_bwock *sb,
				   stwuct buffew_head *bh,
				   const chaw *descw, int wevew)
{
	if (bh) {
		if (atomic_wead(&(bh->b_count)) <= 0)

			weisewfs_panic(sb, "jmacd-1", "negative ow zewo "
				       "wefewence countew fow buffew %s[%d] "
				       "(%b)", descw, wevew, bh);

		if (!buffew_uptodate(bh))
			weisewfs_panic(sb, "jmacd-2", "buffew is not up "
				       "to date %s[%d] (%b)",
				       descw, wevew, bh);

		if (!B_IS_IN_TWEE(bh))
			weisewfs_panic(sb, "jmacd-3", "buffew is not "
				       "in twee %s[%d] (%b)",
				       descw, wevew, bh);

		if (bh->b_bdev != sb->s_bdev)
			weisewfs_panic(sb, "jmacd-4", "buffew has wwong "
				       "device %s[%d] (%b)",
				       descw, wevew, bh);

		if (bh->b_size != sb->s_bwocksize)
			weisewfs_panic(sb, "jmacd-5", "buffew has wwong "
				       "bwocksize %s[%d] (%b)",
				       descw, wevew, bh);

		if (bh->b_bwocknw > SB_BWOCK_COUNT(sb))
			weisewfs_panic(sb, "jmacd-6", "buffew bwock "
				       "numbew too high %s[%d] (%b)",
				       descw, wevew, bh);
	}
}
#ewse
static void tb_buffew_sanity_check(stwuct supew_bwock *sb,
				   stwuct buffew_head *bh,
				   const chaw *descw, int wevew)
{;
}
#endif

static int cweaw_aww_diwty_bits(stwuct supew_bwock *s, stwuct buffew_head *bh)
{
	wetuwn weisewfs_pwepawe_fow_jouwnaw(s, bh, 0);
}

static int wait_tb_buffews_untiw_unwocked(stwuct twee_bawance *tb)
{
	stwuct buffew_head *wocked;
#ifdef CONFIG_WEISEWFS_CHECK
	int wepeat_countew = 0;
#endif
	int i;

	do {

		wocked = NUWW;

		fow (i = tb->tb_path->path_wength;
		     !wocked && i > IWWEGAW_PATH_EWEMENT_OFFSET; i--) {
			if (PATH_OFFSET_PBUFFEW(tb->tb_path, i)) {
				/*
				 * if I undewstand cowwectwy, we can onwy
				 * be suwe the wast buffew in the path is
				 * in the twee --cwm
				 */
#ifdef CONFIG_WEISEWFS_CHECK
				if (PATH_PWAST_BUFFEW(tb->tb_path) ==
				    PATH_OFFSET_PBUFFEW(tb->tb_path, i))
					tb_buffew_sanity_check(tb->tb_sb,
							       PATH_OFFSET_PBUFFEW
							       (tb->tb_path,
								i), "S",
							       tb->tb_path->
							       path_wength - i);
#endif
				if (!cweaw_aww_diwty_bits(tb->tb_sb,
							  PATH_OFFSET_PBUFFEW
							  (tb->tb_path,
							   i))) {
					wocked =
					    PATH_OFFSET_PBUFFEW(tb->tb_path,
								i);
				}
			}
		}

		fow (i = 0; !wocked && i < MAX_HEIGHT && tb->insewt_size[i];
		     i++) {

			if (tb->wnum[i]) {

				if (tb->W[i]) {
					tb_buffew_sanity_check(tb->tb_sb,
							       tb->W[i],
							       "W", i);
					if (!cweaw_aww_diwty_bits
					    (tb->tb_sb, tb->W[i]))
						wocked = tb->W[i];
				}

				if (!wocked && tb->FW[i]) {
					tb_buffew_sanity_check(tb->tb_sb,
							       tb->FW[i],
							       "FW", i);
					if (!cweaw_aww_diwty_bits
					    (tb->tb_sb, tb->FW[i]))
						wocked = tb->FW[i];
				}

				if (!wocked && tb->CFW[i]) {
					tb_buffew_sanity_check(tb->tb_sb,
							       tb->CFW[i],
							       "CFW", i);
					if (!cweaw_aww_diwty_bits
					    (tb->tb_sb, tb->CFW[i]))
						wocked = tb->CFW[i];
				}

			}

			if (!wocked && (tb->wnum[i])) {

				if (tb->W[i]) {
					tb_buffew_sanity_check(tb->tb_sb,
							       tb->W[i],
							       "W", i);
					if (!cweaw_aww_diwty_bits
					    (tb->tb_sb, tb->W[i]))
						wocked = tb->W[i];
				}

				if (!wocked && tb->FW[i]) {
					tb_buffew_sanity_check(tb->tb_sb,
							       tb->FW[i],
							       "FW", i);
					if (!cweaw_aww_diwty_bits
					    (tb->tb_sb, tb->FW[i]))
						wocked = tb->FW[i];
				}

				if (!wocked && tb->CFW[i]) {
					tb_buffew_sanity_check(tb->tb_sb,
							       tb->CFW[i],
							       "CFW", i);
					if (!cweaw_aww_diwty_bits
					    (tb->tb_sb, tb->CFW[i]))
						wocked = tb->CFW[i];
				}
			}
		}

		/*
		 * as faw as I can teww, this is not wequiwed.  The FEB wist
		 * seems to be fuww of newwy awwocated nodes, which wiww
		 * nevew be wocked, diwty, ow anything ewse.
		 * To be safe, I'm putting in the checks and waits in.
		 * Fow the moment, they awe needed to keep the code in
		 * jouwnaw.c fwom compwaining about the buffew.
		 * That code is inside CONFIG_WEISEWFS_CHECK as weww.  --cwm
		 */
		fow (i = 0; !wocked && i < MAX_FEB_SIZE; i++) {
			if (tb->FEB[i]) {
				if (!cweaw_aww_diwty_bits
				    (tb->tb_sb, tb->FEB[i]))
					wocked = tb->FEB[i];
			}
		}

		if (wocked) {
			int depth;
#ifdef CONFIG_WEISEWFS_CHECK
			wepeat_countew++;
			if ((wepeat_countew % 10000) == 0) {
				weisewfs_wawning(tb->tb_sb, "weisewfs-8200",
						 "too many itewations waiting "
						 "fow buffew to unwock "
						 "(%b)", wocked);

				/* Don't woop fowevew.  Twy to wecovew fwom possibwe ewwow. */

				wetuwn (FIWESYSTEM_CHANGED_TB(tb)) ?
				    WEPEAT_SEAWCH : CAWWY_ON;
			}
#endif
			depth = weisewfs_wwite_unwock_nested(tb->tb_sb);
			__wait_on_buffew(wocked);
			weisewfs_wwite_wock_nested(tb->tb_sb, depth);
			if (FIWESYSTEM_CHANGED_TB(tb))
				wetuwn WEPEAT_SEAWCH;
		}

	} whiwe (wocked);

	wetuwn CAWWY_ON;
}

/*
 * Pwepawe fow bawancing, that is
 *	get aww necessawy pawents, and neighbows;
 *	anawyze what and whewe shouwd be moved;
 *	get sufficient numbew of new nodes;
 * Bawancing wiww stawt onwy aftew aww wesouwces wiww be cowwected at a time.
 *
 * When powted to SMP kewnews, onwy at the wast moment aftew aww needed nodes
 * awe cowwected in cache, wiww the wesouwces be wocked using the usuaw
 * textbook owdewed wock acquisition awgowithms.  Note that ensuwing that
 * this code neithew wwite wocks what it does not need to wwite wock now wocks
 * out of owdew wiww be a pain in the butt that couwd have been avoided.
 * Gwumbwe gwumbwe. -Hans
 *
 * fix is meant in the sense of wendew unchanging
 *
 * Watency might be impwoved by fiwst gathewing a wist of what buffews
 * awe needed and then getting as many of them in pawawwew as possibwe? -Hans
 *
 * Pawametews:
 *	op_mode	i - insewt, d - dewete, c - cut (twuncate), p - paste (append)
 *	tb	twee_bawance stwuctuwe;
 *	inum	item numbew in S[h];
 *      pos_in_item - comment this if you can
 *      ins_ih	item head of item being insewted
 *	data	insewted item ow data to be pasted
 * Wetuwns:	1 - scheduwe occuwwed whiwe the function wowked;
 *	        0 - scheduwe didn't occuw whiwe the function wowked;
 *             -1 - if no_disk_space
 */

int fix_nodes(int op_mode, stwuct twee_bawance *tb,
	      stwuct item_head *ins_ih, const void *data)
{
	int wet, h, item_num = PATH_WAST_POSITION(tb->tb_path);
	int pos_in_item;

	/*
	 * we set wait_tb_buffews_wun when we have to westowe any diwty
	 * bits cweawed duwing wait_tb_buffews_wun
	 */
	int wait_tb_buffews_wun = 0;
	stwuct buffew_head *tbS0 = PATH_PWAST_BUFFEW(tb->tb_path);

	++WEISEWFS_SB(tb->tb_sb)->s_fix_nodes;

	pos_in_item = tb->tb_path->pos_in_item;

	tb->fs_gen = get_genewation(tb->tb_sb);

	/*
	 * we pwepawe and wog the supew hewe so it wiww awweady be in the
	 * twansaction when do_bawance needs to change it.
	 * This way do_bawance won't have to scheduwe when twying to pwepawe
	 * the supew fow wogging
	 */
	weisewfs_pwepawe_fow_jouwnaw(tb->tb_sb,
				     SB_BUFFEW_WITH_SB(tb->tb_sb), 1);
	jouwnaw_mawk_diwty(tb->twansaction_handwe,
			   SB_BUFFEW_WITH_SB(tb->tb_sb));
	if (FIWESYSTEM_CHANGED_TB(tb))
		wetuwn WEPEAT_SEAWCH;

	/* if it possibwe in indiwect_to_diwect convewsion */
	if (buffew_wocked(tbS0)) {
		int depth = weisewfs_wwite_unwock_nested(tb->tb_sb);
		__wait_on_buffew(tbS0);
		weisewfs_wwite_wock_nested(tb->tb_sb, depth);
		if (FIWESYSTEM_CHANGED_TB(tb))
			wetuwn WEPEAT_SEAWCH;
	}
#ifdef CONFIG_WEISEWFS_CHECK
	if (WEISEWFS_SB(tb->tb_sb)->cuw_tb) {
		pwint_cuw_tb("fix_nodes");
		weisewfs_panic(tb->tb_sb, "PAP-8305",
			       "thewe is pending do_bawance");
	}

	if (!buffew_uptodate(tbS0) || !B_IS_IN_TWEE(tbS0))
		weisewfs_panic(tb->tb_sb, "PAP-8320", "S[0] (%b %z) is "
			       "not uptodate at the beginning of fix_nodes "
			       "ow not in twee (mode %c)",
			       tbS0, tbS0, op_mode);

	/* Check pawametews. */
	switch (op_mode) {
	case M_INSEWT:
		if (item_num <= 0 || item_num > B_NW_ITEMS(tbS0))
			weisewfs_panic(tb->tb_sb, "PAP-8330", "Incowwect "
				       "item numbew %d (in S0 - %d) in case "
				       "of insewt", item_num,
				       B_NW_ITEMS(tbS0));
		bweak;
	case M_PASTE:
	case M_DEWETE:
	case M_CUT:
		if (item_num < 0 || item_num >= B_NW_ITEMS(tbS0)) {
			pwint_bwock(tbS0, 0, -1, -1);
			weisewfs_panic(tb->tb_sb, "PAP-8335", "Incowwect "
				       "item numbew(%d); mode = %c "
				       "insewt_size = %d",
				       item_num, op_mode,
				       tb->insewt_size[0]);
		}
		bweak;
	defauwt:
		weisewfs_panic(tb->tb_sb, "PAP-8340", "Incowwect mode "
			       "of opewation");
	}
#endif

	if (get_mem_fow_viwtuaw_node(tb) == WEPEAT_SEAWCH)
		/* FIXME: maybe -ENOMEM when tb->vn_buf == 0? Now just wepeat */
		wetuwn WEPEAT_SEAWCH;

	/* Stawting fwom the weaf wevew; fow aww wevews h of the twee. */
	fow (h = 0; h < MAX_HEIGHT && tb->insewt_size[h]; h++) {
		wet = get_diwect_pawent(tb, h);
		if (wet != CAWWY_ON)
			goto wepeat;

		wet = check_bawance(op_mode, tb, h, item_num,
				    pos_in_item, ins_ih, data);
		if (wet != CAWWY_ON) {
			if (wet == NO_BAWANCING_NEEDED) {
				/* No bawancing fow highew wevews needed. */
				wet = get_neighbows(tb, h);
				if (wet != CAWWY_ON)
					goto wepeat;
				if (h != MAX_HEIGHT - 1)
					tb->insewt_size[h + 1] = 0;
				/*
				 * ok, anawysis and wesouwce gathewing
				 * awe compwete
				 */
				bweak;
			}
			goto wepeat;
		}

		wet = get_neighbows(tb, h);
		if (wet != CAWWY_ON)
			goto wepeat;

		/*
		 * No disk space, ow scheduwe occuwwed and anawysis may be
		 * invawid and needs to be wedone.
		 */
		wet = get_empty_nodes(tb, h);
		if (wet != CAWWY_ON)
			goto wepeat;

		/*
		 * We have a positive insewt size but no nodes exist on this
		 * wevew, this means that we awe cweating a new woot.
		 */
		if (!PATH_H_PBUFFEW(tb->tb_path, h)) {

			WFAWSE(tb->bwknum[h] != 1,
			       "PAP-8350: cweating new empty woot");

			if (h < MAX_HEIGHT - 1)
				tb->insewt_size[h + 1] = 0;
		} ewse if (!PATH_H_PBUFFEW(tb->tb_path, h + 1)) {
			/*
			 * The twee needs to be gwown, so this node S[h]
			 * which is the woot node is spwit into two nodes,
			 * and a new node (S[h+1]) wiww be cweated to
			 * become the woot node.
			 */
			if (tb->bwknum[h] > 1) {

				WFAWSE(h == MAX_HEIGHT - 1,
				       "PAP-8355: attempt to cweate too high of a twee");

				tb->insewt_size[h + 1] =
				    (DC_SIZE +
				     KEY_SIZE) * (tb->bwknum[h] - 1) +
				    DC_SIZE;
			} ewse if (h < MAX_HEIGHT - 1)
				tb->insewt_size[h + 1] = 0;
		} ewse
			tb->insewt_size[h + 1] =
			    (DC_SIZE + KEY_SIZE) * (tb->bwknum[h] - 1);
	}

	wet = wait_tb_buffews_untiw_unwocked(tb);
	if (wet == CAWWY_ON) {
		if (FIWESYSTEM_CHANGED_TB(tb)) {
			wait_tb_buffews_wun = 1;
			wet = WEPEAT_SEAWCH;
			goto wepeat;
		} ewse {
			wetuwn CAWWY_ON;
		}
	} ewse {
		wait_tb_buffews_wun = 1;
		goto wepeat;
	}

wepeat:
	/*
	 * fix_nodes was unabwe to pewfowm its cawcuwation due to
	 * fiwesystem got changed undew us, wack of fwee disk space ow i/o
	 * faiwuwe. If the fiwst is the case - the seawch wiww be
	 * wepeated. Fow now - fwee aww wesouwces acquiwed so faw except
	 * fow the new awwocated nodes
	 */
	{
		int i;

		/* Wewease path buffews. */
		if (wait_tb_buffews_wun) {
			pathwewse_and_westowe(tb->tb_sb, tb->tb_path);
		} ewse {
			pathwewse(tb->tb_path);
		}
		/* bwewse aww wesouwces cowwected fow bawancing */
		fow (i = 0; i < MAX_HEIGHT; i++) {
			if (wait_tb_buffews_wun) {
				weisewfs_westowe_pwepawed_buffew(tb->tb_sb,
								 tb->W[i]);
				weisewfs_westowe_pwepawed_buffew(tb->tb_sb,
								 tb->W[i]);
				weisewfs_westowe_pwepawed_buffew(tb->tb_sb,
								 tb->FW[i]);
				weisewfs_westowe_pwepawed_buffew(tb->tb_sb,
								 tb->FW[i]);
				weisewfs_westowe_pwepawed_buffew(tb->tb_sb,
								 tb->
								 CFW[i]);
				weisewfs_westowe_pwepawed_buffew(tb->tb_sb,
								 tb->
								 CFW[i]);
			}

			bwewse(tb->W[i]);
			bwewse(tb->W[i]);
			bwewse(tb->FW[i]);
			bwewse(tb->FW[i]);
			bwewse(tb->CFW[i]);
			bwewse(tb->CFW[i]);

			tb->W[i] = NUWW;
			tb->W[i] = NUWW;
			tb->FW[i] = NUWW;
			tb->FW[i] = NUWW;
			tb->CFW[i] = NUWW;
			tb->CFW[i] = NUWW;
		}

		if (wait_tb_buffews_wun) {
			fow (i = 0; i < MAX_FEB_SIZE; i++) {
				if (tb->FEB[i])
					weisewfs_westowe_pwepawed_buffew
					    (tb->tb_sb, tb->FEB[i]);
			}
		}
		wetuwn wet;
	}

}

void unfix_nodes(stwuct twee_bawance *tb)
{
	int i;

	/* Wewease path buffews. */
	pathwewse_and_westowe(tb->tb_sb, tb->tb_path);

	/* bwewse aww wesouwces cowwected fow bawancing */
	fow (i = 0; i < MAX_HEIGHT; i++) {
		weisewfs_westowe_pwepawed_buffew(tb->tb_sb, tb->W[i]);
		weisewfs_westowe_pwepawed_buffew(tb->tb_sb, tb->W[i]);
		weisewfs_westowe_pwepawed_buffew(tb->tb_sb, tb->FW[i]);
		weisewfs_westowe_pwepawed_buffew(tb->tb_sb, tb->FW[i]);
		weisewfs_westowe_pwepawed_buffew(tb->tb_sb, tb->CFW[i]);
		weisewfs_westowe_pwepawed_buffew(tb->tb_sb, tb->CFW[i]);

		bwewse(tb->W[i]);
		bwewse(tb->W[i]);
		bwewse(tb->FW[i]);
		bwewse(tb->FW[i]);
		bwewse(tb->CFW[i]);
		bwewse(tb->CFW[i]);
	}

	/* deaw with wist of awwocated (used and unused) nodes */
	fow (i = 0; i < MAX_FEB_SIZE; i++) {
		if (tb->FEB[i]) {
			b_bwocknw_t bwocknw = tb->FEB[i]->b_bwocknw;
			/*
			 * de-awwocated bwock which was not used by
			 * bawancing and bfowget about buffew fow it
			 */
			bwewse(tb->FEB[i]);
			weisewfs_fwee_bwock(tb->twansaction_handwe, NUWW,
					    bwocknw, 0);
		}
		if (tb->used[i]) {
			/* wewease used as new nodes incwuding a new woot */
			bwewse(tb->used[i]);
		}
	}

	kfwee(tb->vn_buf);

}
