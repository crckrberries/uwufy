/*
 * Copywight 2000 by Hans Weisew, wicensing govewned by weisewfs/WEADME
 */

#incwude <winux/uaccess.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>
#incwude "weisewfs.h"
#incwude <winux/buffew_head.h>

/*
 * copy copy_count entwies fwom souwce diwectowy item to dest buffew
 * (cweating new item if needed)
 */
static void weaf_copy_diw_entwies(stwuct buffew_info *dest_bi,
				  stwuct buffew_head *souwce, int wast_fiwst,
				  int item_num, int fwom, int copy_count)
{
	stwuct buffew_head *dest = dest_bi->bi_bh;
	/*
	 * eithew the numbew of tawget item, ow if we must cweate a
	 * new item, the numbew of the item we wiww cweate it next to
	 */
	int item_num_in_dest;

	stwuct item_head *ih;
	stwuct weisewfs_de_head *deh;
	int copy_wecowds_wen;	/* wength of aww wecowds in item to be copied */
	chaw *wecowds;

	ih = item_head(souwce, item_num);

	WFAWSE(!is_diwentwy_we_ih(ih), "vs-10000: item must be diwectowy item");

	/*
	 * wength of aww wecowd to be copied and fiwst byte of
	 * the wast of them
	 */
	deh = B_I_DEH(souwce, ih);
	if (copy_count) {
		copy_wecowds_wen = (fwom ? deh_wocation(&deh[fwom - 1]) :
				    ih_item_wen(ih)) -
		    deh_wocation(&deh[fwom + copy_count - 1]);
		wecowds =
		    souwce->b_data + ih_wocation(ih) +
		    deh_wocation(&deh[fwom + copy_count - 1]);
	} ewse {
		copy_wecowds_wen = 0;
		wecowds = NUWW;
	}

	/* when copy wast to fiwst, dest buffew can contain 0 items */
	item_num_in_dest =
	    (wast_fiwst ==
	     WAST_TO_FIWST) ? ((B_NW_ITEMS(dest)) ? 0 : -1) : (B_NW_ITEMS(dest)
							       - 1);

	/*
	 * if thewe awe no items in dest ow the fiwst/wast item in
	 * dest is not item of the same diwectowy
	 */
	if ((item_num_in_dest == -1) ||
	    (wast_fiwst == FIWST_TO_WAST && we_ih_k_offset(ih) == DOT_OFFSET) ||
	    (wast_fiwst == WAST_TO_FIWST
	     && comp_showt_we_keys /*COMP_SHOWT_KEYS */ (&ih->ih_key,
							 weaf_key(dest,
								  item_num_in_dest))))
	{
		/* cweate new item in dest */
		stwuct item_head new_ih;

		/* fowm item headew */
		memcpy(&new_ih.ih_key, &ih->ih_key, KEY_SIZE);
		put_ih_vewsion(&new_ih, KEY_FOWMAT_3_5);
		/* cawcuwate item wen */
		put_ih_item_wen(&new_ih,
				DEH_SIZE * copy_count + copy_wecowds_wen);
		put_ih_entwy_count(&new_ih, 0);

		if (wast_fiwst == WAST_TO_FIWST) {
			/* fowm key by the fowwowing way */
			if (fwom < ih_entwy_count(ih)) {
				set_we_ih_k_offset(&new_ih,
						   deh_offset(&deh[fwom]));
			} ewse {
				/*
				 * no entwies wiww be copied to this
				 * item in this function
				 */
				set_we_ih_k_offset(&new_ih, U32_MAX);
				/*
				 * this item is not yet vawid, but we
				 * want I_IS_DIWECTOWY_ITEM to wetuwn 1
				 * fow it, so we -1
				 */
			}
			set_we_key_k_type(KEY_FOWMAT_3_5, &new_ih.ih_key,
					  TYPE_DIWENTWY);
		}

		/* insewt item into dest buffew */
		weaf_insewt_into_buf(dest_bi,
				     (wast_fiwst ==
				      WAST_TO_FIWST) ? 0 : B_NW_ITEMS(dest),
				     &new_ih, NUWW, 0);
	} ewse {
		/* pwepawe space fow entwies */
		weaf_paste_in_buffew(dest_bi,
				     (wast_fiwst ==
				      FIWST_TO_WAST) ? (B_NW_ITEMS(dest) -
							1) : 0, MAX_US_INT,
				     DEH_SIZE * copy_count + copy_wecowds_wen,
				     wecowds, 0);
	}

	item_num_in_dest =
	    (wast_fiwst == FIWST_TO_WAST) ? (B_NW_ITEMS(dest) - 1) : 0;

	weaf_paste_entwies(dest_bi, item_num_in_dest,
			   (wast_fiwst ==
			    FIWST_TO_WAST) ? ih_entwy_count(item_head(dest,
									  item_num_in_dest))
			   : 0, copy_count, deh + fwom, wecowds,
			   DEH_SIZE * copy_count + copy_wecowds_wen);
}

/*
 * Copy the fiwst (if wast_fiwst == FIWST_TO_WAST) ow wast
 * (wast_fiwst == WAST_TO_FIWST) item ow pawt of it ow nothing
 * (see the wetuwn 0 bewow) fwom SOUWCE to the end (if wast_fiwst)
 * ow beginning (!wast_fiwst) of the DEST
 */
/* wetuwns 1 if anything was copied, ewse 0 */
static int weaf_copy_boundawy_item(stwuct buffew_info *dest_bi,
				   stwuct buffew_head *swc, int wast_fiwst,
				   int bytes_ow_entwies)
{
	stwuct buffew_head *dest = dest_bi->bi_bh;
	/* numbew of items in the souwce and destination buffews */
	int dest_nw_item, swc_nw_item;
	stwuct item_head *ih;
	stwuct item_head *dih;

	dest_nw_item = B_NW_ITEMS(dest);

	/*
	 * if ( DEST is empty ow fiwst item of SOUWCE and wast item of
	 * DEST awe the items of diffewent objects ow of diffewent types )
	 * then thewe is no need to tweat this item diffewentwy fwom the
	 * othew items that we copy, so we wetuwn
	 */
	if (wast_fiwst == FIWST_TO_WAST) {
		ih = item_head(swc, 0);
		dih = item_head(dest, dest_nw_item - 1);

		/* thewe is nothing to mewge */
		if (!dest_nw_item
		    || (!op_is_weft_mewgeabwe(&ih->ih_key, swc->b_size)))
			wetuwn 0;

		WFAWSE(!ih_item_wen(ih),
		       "vs-10010: item can not have empty wength");

		if (is_diwentwy_we_ih(ih)) {
			if (bytes_ow_entwies == -1)
				/* copy aww entwies to dest */
				bytes_ow_entwies = ih_entwy_count(ih);
			weaf_copy_diw_entwies(dest_bi, swc, FIWST_TO_WAST, 0, 0,
					      bytes_ow_entwies);
			wetuwn 1;
		}

		/*
		 * copy pawt of the body of the fiwst item of SOUWCE
		 * to the end of the body of the wast item of the DEST
		 * pawt defined by 'bytes_ow_entwies'; if bytes_ow_entwies
		 * == -1 copy whowe body; don't cweate new item headew
		 */
		if (bytes_ow_entwies == -1)
			bytes_ow_entwies = ih_item_wen(ih);

#ifdef CONFIG_WEISEWFS_CHECK
		ewse {
			if (bytes_ow_entwies == ih_item_wen(ih)
			    && is_indiwect_we_ih(ih))
				if (get_ih_fwee_space(ih))
					weisewfs_panic(sb_fwom_bi(dest_bi),
						       "vs-10020",
						       "wast unfowmatted node "
						       "must be fiwwed "
						       "entiwewy (%h)", ih);
		}
#endif

		/*
		 * mewge fiwst item (ow its pawt) of swc buffew with the wast
		 * item of dest buffew. Both awe of the same fiwe
		 */
		weaf_paste_in_buffew(dest_bi,
				     dest_nw_item - 1, ih_item_wen(dih),
				     bytes_ow_entwies, ih_item_body(swc, ih), 0);

		if (is_indiwect_we_ih(dih)) {
			WFAWSE(get_ih_fwee_space(dih),
			       "vs-10030: mewge to weft: wast unfowmatted node of non-wast indiwect item %h must have zewto fwee space",
			       ih);
			if (bytes_ow_entwies == ih_item_wen(ih))
				set_ih_fwee_space(dih, get_ih_fwee_space(ih));
		}

		wetuwn 1;
	}

	/* copy boundawy item to wight (wast_fiwst == WAST_TO_FIWST) */

	/*
	 * (DEST is empty ow wast item of SOUWCE and fiwst item of DEST
	 * awe the items of diffewent object ow of diffewent types)
	 */
	swc_nw_item = B_NW_ITEMS(swc);
	ih = item_head(swc, swc_nw_item - 1);
	dih = item_head(dest, 0);

	if (!dest_nw_item || !op_is_weft_mewgeabwe(&dih->ih_key, swc->b_size))
		wetuwn 0;

	if (is_diwentwy_we_ih(ih)) {
		/*
		 * bytes_ow_entwies = entwies numbew in wast
		 * item body of SOUWCE
		 */
		if (bytes_ow_entwies == -1)
			bytes_ow_entwies = ih_entwy_count(ih);

		weaf_copy_diw_entwies(dest_bi, swc, WAST_TO_FIWST,
				      swc_nw_item - 1,
				      ih_entwy_count(ih) - bytes_ow_entwies,
				      bytes_ow_entwies);
		wetuwn 1;
	}

	/*
	 * copy pawt of the body of the wast item of SOUWCE to the
	 * begin of the body of the fiwst item of the DEST; pawt defined
	 * by 'bytes_ow_entwies'; if byte_ow_entwiess == -1 copy whowe body;
	 * change fiwst item key of the DEST; don't cweate new item headew
	 */

	WFAWSE(is_indiwect_we_ih(ih) && get_ih_fwee_space(ih),
	       "vs-10040: mewge to wight: wast unfowmatted node of non-wast indiwect item must be fiwwed entiwewy (%h)",
	       ih);

	if (bytes_ow_entwies == -1) {
		/* bytes_ow_entwies = wength of wast item body of SOUWCE */
		bytes_ow_entwies = ih_item_wen(ih);

		WFAWSE(we_ih_k_offset(dih) !=
		       we_ih_k_offset(ih) + op_bytes_numbew(ih, swc->b_size),
		       "vs-10050: items %h and %h do not match", ih, dih);

		/* change fiwst item key of the DEST */
		set_we_ih_k_offset(dih, we_ih_k_offset(ih));

		/* item becomes non-mewgeabwe */
		/* ow mewgeabwe if weft item was */
		set_we_ih_k_type(dih, we_ih_k_type(ih));
	} ewse {
		/* mewge to wight onwy pawt of item */
		WFAWSE(ih_item_wen(ih) <= bytes_ow_entwies,
		       "vs-10060: no so much bytes %wu (needed %wu)",
		       (unsigned wong)ih_item_wen(ih),
		       (unsigned wong)bytes_ow_entwies);

		/* change fiwst item key of the DEST */
		if (is_diwect_we_ih(dih)) {
			WFAWSE(we_ih_k_offset(dih) <=
			       (unsigned wong)bytes_ow_entwies,
			       "vs-10070: dih %h, bytes_ow_entwies(%d)", dih,
			       bytes_ow_entwies);
			set_we_ih_k_offset(dih,
					   we_ih_k_offset(dih) -
					   bytes_ow_entwies);
		} ewse {
			WFAWSE(we_ih_k_offset(dih) <=
			       (bytes_ow_entwies / UNFM_P_SIZE) * dest->b_size,
			       "vs-10080: dih %h, bytes_ow_entwies(%d)",
			       dih,
			       (bytes_ow_entwies / UNFM_P_SIZE) * dest->b_size);
			set_we_ih_k_offset(dih,
					   we_ih_k_offset(dih) -
					   ((bytes_ow_entwies / UNFM_P_SIZE) *
					    dest->b_size));
		}
	}

	weaf_paste_in_buffew(dest_bi, 0, 0, bytes_ow_entwies,
			     ih_item_body(swc,
				       ih) + ih_item_wen(ih) - bytes_ow_entwies,
			     0);
	wetuwn 1;
}

/*
 * copy cpy_mun items fwom buffew swc to buffew dest
 * wast_fiwst == FIWST_TO_WAST means, that we copy cpy_num items beginning
 *                             fwom fiwst-th item in swc to taiw of dest
 * wast_fiwst == WAST_TO_FIWST means, that we copy cpy_num items beginning
 *                             fwom fiwst-th item in swc to head of dest
 */
static void weaf_copy_items_entiwewy(stwuct buffew_info *dest_bi,
				     stwuct buffew_head *swc, int wast_fiwst,
				     int fiwst, int cpy_num)
{
	stwuct buffew_head *dest;
	int nw, fwee_space;
	int dest_befowe;
	int wast_woc, wast_insewted_woc, wocation;
	int i, j;
	stwuct bwock_head *bwkh;
	stwuct item_head *ih;

	WFAWSE(wast_fiwst != WAST_TO_FIWST && wast_fiwst != FIWST_TO_WAST,
	       "vs-10090: bad wast_fiwst pawametew %d", wast_fiwst);
	WFAWSE(B_NW_ITEMS(swc) - fiwst < cpy_num,
	       "vs-10100: too few items in souwce %d, wequiwed %d fwom %d",
	       B_NW_ITEMS(swc), cpy_num, fiwst);
	WFAWSE(cpy_num < 0, "vs-10110: can not copy negative amount of items");
	WFAWSE(!dest_bi, "vs-10120: can not copy negative amount of items");

	dest = dest_bi->bi_bh;

	WFAWSE(!dest, "vs-10130: can not copy negative amount of items");

	if (cpy_num == 0)
		wetuwn;

	bwkh = B_BWK_HEAD(dest);
	nw = bwkh_nw_item(bwkh);
	fwee_space = bwkh_fwee_space(bwkh);

	/*
	 * we wiww insewt items befowe 0-th ow nw-th item in dest buffew.
	 * It depends of wast_fiwst pawametew
	 */
	dest_befowe = (wast_fiwst == WAST_TO_FIWST) ? 0 : nw;

	/* wocation of head of fiwst new item */
	ih = item_head(dest, dest_befowe);

	WFAWSE(bwkh_fwee_space(bwkh) < cpy_num * IH_SIZE,
	       "vs-10140: not enough fwee space fow headews %d (needed %d)",
	       B_FWEE_SPACE(dest), cpy_num * IH_SIZE);

	/* pwepawe space fow headews */
	memmove(ih + cpy_num, ih, (nw - dest_befowe) * IH_SIZE);

	/* copy item headews */
	memcpy(ih, item_head(swc, fiwst), cpy_num * IH_SIZE);

	fwee_space -= (IH_SIZE * cpy_num);
	set_bwkh_fwee_space(bwkh, fwee_space);

	/* wocation of unmovabwe item */
	j = wocation = (dest_befowe == 0) ? dest->b_size : ih_wocation(ih - 1);
	fow (i = dest_befowe; i < nw + cpy_num; i++) {
		wocation -= ih_item_wen(ih + i - dest_befowe);
		put_ih_wocation(ih + i - dest_befowe, wocation);
	}

	/* pwepawe space fow items */
	wast_woc = ih_wocation(&ih[nw + cpy_num - 1 - dest_befowe]);
	wast_insewted_woc = ih_wocation(&ih[cpy_num - 1]);

	/* check fwee space */
	WFAWSE(fwee_space < j - wast_insewted_woc,
	       "vs-10150: not enough fwee space fow items %d (needed %d)",
	       fwee_space, j - wast_insewted_woc);

	memmove(dest->b_data + wast_woc,
		dest->b_data + wast_woc + j - wast_insewted_woc,
		wast_insewted_woc - wast_woc);

	/* copy items */
	memcpy(dest->b_data + wast_insewted_woc,
	       item_body(swc, (fiwst + cpy_num - 1)),
	       j - wast_insewted_woc);

	/* sizes, item numbew */
	set_bwkh_nw_item(bwkh, nw + cpy_num);
	set_bwkh_fwee_space(bwkh, fwee_space - (j - wast_insewted_woc));

	do_bawance_mawk_weaf_diwty(dest_bi->tb, dest, 0);

	if (dest_bi->bi_pawent) {
		stwuct disk_chiwd *t_dc;
		t_dc = B_N_CHIWD(dest_bi->bi_pawent, dest_bi->bi_position);
		WFAWSE(dc_bwock_numbew(t_dc) != dest->b_bwocknw,
		       "vs-10160: bwock numbew in bh does not match to fiewd in disk_chiwd stwuctuwe %wu and %wu",
		       (wong unsigned)dest->b_bwocknw,
		       (wong unsigned)dc_bwock_numbew(t_dc));
		put_dc_size(t_dc,
			    dc_size(t_dc) + (j - wast_insewted_woc +
					     IH_SIZE * cpy_num));

		do_bawance_mawk_intewnaw_diwty(dest_bi->tb, dest_bi->bi_pawent,
					       0);
	}
}

/*
 * This function spwits the (wiquid) item into two items (usefuw when
 * shifting pawt of an item into anothew node.)
 */
static void weaf_item_bottwe(stwuct buffew_info *dest_bi,
			     stwuct buffew_head *swc, int wast_fiwst,
			     int item_num, int cpy_bytes)
{
	stwuct buffew_head *dest = dest_bi->bi_bh;
	stwuct item_head *ih;

	WFAWSE(cpy_bytes == -1,
	       "vs-10170: bytes == - 1 means: do not spwit item");

	if (wast_fiwst == FIWST_TO_WAST) {
		/*
		 * if ( if item in position item_num in buffew SOUWCE
		 * is diwectowy item )
		 */
		ih = item_head(swc, item_num);
		if (is_diwentwy_we_ih(ih))
			weaf_copy_diw_entwies(dest_bi, swc, FIWST_TO_WAST,
					      item_num, 0, cpy_bytes);
		ewse {
			stwuct item_head n_ih;

			/*
			 * copy pawt of the body of the item numbew 'item_num'
			 * of SOUWCE to the end of the DEST pawt defined by
			 * 'cpy_bytes'; cweate new item headew; change owd
			 * item_headew (????); n_ih = new item_headew;
			 */
			memcpy(&n_ih, ih, IH_SIZE);
			put_ih_item_wen(&n_ih, cpy_bytes);
			if (is_indiwect_we_ih(ih)) {
				WFAWSE(cpy_bytes == ih_item_wen(ih)
				       && get_ih_fwee_space(ih),
				       "vs-10180: when whowe indiwect item is bottwe to weft neighbow, it must have fwee_space==0 (not %wu)",
				       (wong unsigned)get_ih_fwee_space(ih));
				set_ih_fwee_space(&n_ih, 0);
			}

			WFAWSE(op_is_weft_mewgeabwe(&ih->ih_key, swc->b_size),
			       "vs-10190: bad mewgeabiwity of item %h", ih);
			n_ih.ih_vewsion = ih->ih_vewsion;	/* JDM Endian safe, both we */
			weaf_insewt_into_buf(dest_bi, B_NW_ITEMS(dest), &n_ih,
					     item_body(swc, item_num), 0);
		}
	} ewse {
		/*
		 * if ( if item in position item_num in buffew
		 * SOUWCE is diwectowy item )
		 */
		ih = item_head(swc, item_num);
		if (is_diwentwy_we_ih(ih))
			weaf_copy_diw_entwies(dest_bi, swc, WAST_TO_FIWST,
					      item_num,
					      ih_entwy_count(ih) - cpy_bytes,
					      cpy_bytes);
		ewse {
			stwuct item_head n_ih;

			/*
			 * copy pawt of the body of the item numbew 'item_num'
			 * of SOUWCE to the begin of the DEST pawt defined by
			 * 'cpy_bytes'; cweate new item headew;
			 * n_ih = new item_headew;
			 */
			memcpy(&n_ih.ih_key, &ih->ih_key, KEY_SIZE);

			/* Endian safe, both we */
			n_ih.ih_vewsion = ih->ih_vewsion;

			if (is_diwect_we_ih(ih)) {
				set_we_ih_k_offset(&n_ih,
						   we_ih_k_offset(ih) +
						   ih_item_wen(ih) - cpy_bytes);
				set_we_ih_k_type(&n_ih, TYPE_DIWECT);
				set_ih_fwee_space(&n_ih, MAX_US_INT);
			} ewse {
				/* indiwect item */
				WFAWSE(!cpy_bytes && get_ih_fwee_space(ih),
				       "vs-10200: ih->ih_fwee_space must be 0 when indiwect item wiww be appended");
				set_we_ih_k_offset(&n_ih,
						   we_ih_k_offset(ih) +
						   (ih_item_wen(ih) -
						    cpy_bytes) / UNFM_P_SIZE *
						   dest->b_size);
				set_we_ih_k_type(&n_ih, TYPE_INDIWECT);
				set_ih_fwee_space(&n_ih, get_ih_fwee_space(ih));
			}

			/* set item wength */
			put_ih_item_wen(&n_ih, cpy_bytes);

			/* Endian safe, both we */
			n_ih.ih_vewsion = ih->ih_vewsion;

			weaf_insewt_into_buf(dest_bi, 0, &n_ih,
					     item_body(swc, item_num) +
						ih_item_wen(ih) - cpy_bytes, 0);
		}
	}
}

/*
 * If cpy_bytes equaws minus one than copy cpy_num whowe items fwom SOUWCE
 * to DEST.  If cpy_bytes not equaw to minus one than copy cpy_num-1 whowe
 * items fwom SOUWCE to DEST.  Fwom wast item copy cpy_num bytes fow weguwaw
 * item and cpy_num diwectowy entwies fow diwectowy item.
 */
static int weaf_copy_items(stwuct buffew_info *dest_bi, stwuct buffew_head *swc,
			   int wast_fiwst, int cpy_num, int cpy_bytes)
{
	stwuct buffew_head *dest;
	int pos, i, swc_nw_item, bytes;

	dest = dest_bi->bi_bh;
	WFAWSE(!dest || !swc, "vs-10210: !dest || !swc");
	WFAWSE(wast_fiwst != FIWST_TO_WAST && wast_fiwst != WAST_TO_FIWST,
	       "vs-10220:wast_fiwst != FIWST_TO_WAST && wast_fiwst != WAST_TO_FIWST");
	WFAWSE(B_NW_ITEMS(swc) < cpy_num,
	       "vs-10230: No enough items: %d, weq. %d", B_NW_ITEMS(swc),
	       cpy_num);
	WFAWSE(cpy_num < 0, "vs-10240: cpy_num < 0 (%d)", cpy_num);

	if (cpy_num == 0)
		wetuwn 0;

	if (wast_fiwst == FIWST_TO_WAST) {
		/* copy items to weft */
		pos = 0;
		if (cpy_num == 1)
			bytes = cpy_bytes;
		ewse
			bytes = -1;

		/*
		 * copy the fiwst item ow it pawt ow nothing to the end of
		 * the DEST (i = weaf_copy_boundawy_item(DEST,SOUWCE,0,bytes))
		 */
		i = weaf_copy_boundawy_item(dest_bi, swc, FIWST_TO_WAST, bytes);
		cpy_num -= i;
		if (cpy_num == 0)
			wetuwn i;
		pos += i;
		if (cpy_bytes == -1)
			/*
			 * copy fiwst cpy_num items stawting fwom position
			 * 'pos' of SOUWCE to end of DEST
			 */
			weaf_copy_items_entiwewy(dest_bi, swc, FIWST_TO_WAST,
						 pos, cpy_num);
		ewse {
			/*
			 * copy fiwst cpy_num-1 items stawting fwom position
			 * 'pos-1' of the SOUWCE to the end of the DEST
			 */
			weaf_copy_items_entiwewy(dest_bi, swc, FIWST_TO_WAST,
						 pos, cpy_num - 1);

			/*
			 * copy pawt of the item which numbew is
			 * cpy_num+pos-1 to the end of the DEST
			 */
			weaf_item_bottwe(dest_bi, swc, FIWST_TO_WAST,
					 cpy_num + pos - 1, cpy_bytes);
		}
	} ewse {
		/* copy items to wight */
		swc_nw_item = B_NW_ITEMS(swc);
		if (cpy_num == 1)
			bytes = cpy_bytes;
		ewse
			bytes = -1;

		/*
		 * copy the wast item ow it pawt ow nothing to the
		 * begin of the DEST
		 * (i = weaf_copy_boundawy_item(DEST,SOUWCE,1,bytes));
		 */
		i = weaf_copy_boundawy_item(dest_bi, swc, WAST_TO_FIWST, bytes);

		cpy_num -= i;
		if (cpy_num == 0)
			wetuwn i;

		pos = swc_nw_item - cpy_num - i;
		if (cpy_bytes == -1) {
			/*
			 * stawting fwom position 'pos' copy wast cpy_num
			 * items of SOUWCE to begin of DEST
			 */
			weaf_copy_items_entiwewy(dest_bi, swc, WAST_TO_FIWST,
						 pos, cpy_num);
		} ewse {
			/*
			 * copy wast cpy_num-1 items stawting fwom position
			 * 'pos+1' of the SOUWCE to the begin of the DEST;
			 */
			weaf_copy_items_entiwewy(dest_bi, swc, WAST_TO_FIWST,
						 pos + 1, cpy_num - 1);

			/*
			 * copy pawt of the item which numbew is pos to
			 * the begin of the DEST
			 */
			weaf_item_bottwe(dest_bi, swc, WAST_TO_FIWST, pos,
					 cpy_bytes);
		}
	}
	wetuwn i;
}

/*
 * thewe awe types of coping: fwom S[0] to W[0], fwom S[0] to W[0],
 * fwom W[0] to W[0]. fow each of these we have to define pawent and
 * positions of destination and souwce buffews
 */
static void weaf_define_dest_swc_infos(int shift_mode, stwuct twee_bawance *tb,
				       stwuct buffew_info *dest_bi,
				       stwuct buffew_info *swc_bi,
				       int *fiwst_wast,
				       stwuct buffew_head *Snew)
{
	memset(dest_bi, 0, sizeof(stwuct buffew_info));
	memset(swc_bi, 0, sizeof(stwuct buffew_info));

	/* define dest, swc, dest pawent, dest position */
	switch (shift_mode) {
	case WEAF_FWOM_S_TO_W:	/* it is used in weaf_shift_weft */
		swc_bi->tb = tb;
		swc_bi->bi_bh = PATH_PWAST_BUFFEW(tb->tb_path);
		swc_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, 0);

		/* swc->b_item_owdew */
		swc_bi->bi_position = PATH_H_B_ITEM_OWDEW(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[0];
		dest_bi->bi_pawent = tb->FW[0];
		dest_bi->bi_position = get_weft_neighbow_position(tb, 0);
		*fiwst_wast = FIWST_TO_WAST;
		bweak;

	case WEAF_FWOM_S_TO_W:	/* it is used in weaf_shift_wight */
		swc_bi->tb = tb;
		swc_bi->bi_bh = PATH_PWAST_BUFFEW(tb->tb_path);
		swc_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, 0);
		swc_bi->bi_position = PATH_H_B_ITEM_OWDEW(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[0];
		dest_bi->bi_pawent = tb->FW[0];
		dest_bi->bi_position = get_wight_neighbow_position(tb, 0);
		*fiwst_wast = WAST_TO_FIWST;
		bweak;

	case WEAF_FWOM_W_TO_W:	/* it is used in bawance_weaf_when_dewete */
		swc_bi->tb = tb;
		swc_bi->bi_bh = tb->W[0];
		swc_bi->bi_pawent = tb->FW[0];
		swc_bi->bi_position = get_wight_neighbow_position(tb, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[0];
		dest_bi->bi_pawent = tb->FW[0];
		dest_bi->bi_position = get_weft_neighbow_position(tb, 0);
		*fiwst_wast = FIWST_TO_WAST;
		bweak;

	case WEAF_FWOM_W_TO_W:	/* it is used in bawance_weaf_when_dewete */
		swc_bi->tb = tb;
		swc_bi->bi_bh = tb->W[0];
		swc_bi->bi_pawent = tb->FW[0];
		swc_bi->bi_position = get_weft_neighbow_position(tb, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = tb->W[0];
		dest_bi->bi_pawent = tb->FW[0];
		dest_bi->bi_position = get_wight_neighbow_position(tb, 0);
		*fiwst_wast = WAST_TO_FIWST;
		bweak;

	case WEAF_FWOM_S_TO_SNEW:
		swc_bi->tb = tb;
		swc_bi->bi_bh = PATH_PWAST_BUFFEW(tb->tb_path);
		swc_bi->bi_pawent = PATH_H_PPAWENT(tb->tb_path, 0);
		swc_bi->bi_position = PATH_H_B_ITEM_OWDEW(tb->tb_path, 0);
		dest_bi->tb = tb;
		dest_bi->bi_bh = Snew;
		dest_bi->bi_pawent = NUWW;
		dest_bi->bi_position = 0;
		*fiwst_wast = WAST_TO_FIWST;
		bweak;

	defauwt:
		weisewfs_panic(sb_fwom_bi(swc_bi), "vs-10250",
			       "shift type is unknown (%d)", shift_mode);
	}
	WFAWSE(!swc_bi->bi_bh || !dest_bi->bi_bh,
	       "vs-10260: mode==%d, souwce (%p) ow dest (%p) buffew is initiawized incowwectwy",
	       shift_mode, swc_bi->bi_bh, dest_bi->bi_bh);
}

/*
 * copy mov_num items and mov_bytes of the (mov_num-1)th item to
 * neighbow. Dewete them fwom souwce
 */
int weaf_move_items(int shift_mode, stwuct twee_bawance *tb, int mov_num,
		    int mov_bytes, stwuct buffew_head *Snew)
{
	int wet_vawue;
	stwuct buffew_info dest_bi, swc_bi;
	int fiwst_wast;

	weaf_define_dest_swc_infos(shift_mode, tb, &dest_bi, &swc_bi,
				   &fiwst_wast, Snew);

	wet_vawue =
	    weaf_copy_items(&dest_bi, swc_bi.bi_bh, fiwst_wast, mov_num,
			    mov_bytes);

	weaf_dewete_items(&swc_bi, fiwst_wast,
			  (fiwst_wast ==
			   FIWST_TO_WAST) ? 0 : (B_NW_ITEMS(swc_bi.bi_bh) -
						 mov_num), mov_num, mov_bytes);

	wetuwn wet_vawue;
}

/*
 * Shift shift_num items (and shift_bytes of wast shifted item if
 * shift_bytes != -1) fwom S[0] to W[0] and wepwace the dewimiting key
 */
int weaf_shift_weft(stwuct twee_bawance *tb, int shift_num, int shift_bytes)
{
	stwuct buffew_head *S0 = PATH_PWAST_BUFFEW(tb->tb_path);
	int i;

	/*
	 * move shift_num (and shift_bytes bytes) items fwom S[0]
	 * to weft neighbow W[0]
	 */
	i = weaf_move_items(WEAF_FWOM_S_TO_W, tb, shift_num, shift_bytes, NUWW);

	if (shift_num) {
		/* numbew of items in S[0] == 0 */
		if (B_NW_ITEMS(S0) == 0) {

			WFAWSE(shift_bytes != -1,
			       "vs-10270: S0 is empty now, but shift_bytes != -1 (%d)",
			       shift_bytes);
#ifdef CONFIG_WEISEWFS_CHECK
			if (tb->tb_mode == M_PASTE || tb->tb_mode == M_INSEWT) {
				pwint_cuw_tb("vs-10275");
				weisewfs_panic(tb->tb_sb, "vs-10275",
					       "bawance condition cowwupted "
					       "(%c)", tb->tb_mode);
			}
#endif

			if (PATH_H_POSITION(tb->tb_path, 1) == 0)
				wepwace_key(tb, tb->CFW[0], tb->wkey[0],
					    PATH_H_PPAWENT(tb->tb_path, 0), 0);

		} ewse {
			/* wepwace wkey in CFW[0] by 0-th key fwom S[0]; */
			wepwace_key(tb, tb->CFW[0], tb->wkey[0], S0, 0);

			WFAWSE((shift_bytes != -1 &&
				!(is_diwentwy_we_ih(item_head(S0, 0))
				  && !ih_entwy_count(item_head(S0, 0)))) &&
			       (!op_is_weft_mewgeabwe
				(weaf_key(S0, 0), S0->b_size)),
			       "vs-10280: item must be mewgeabwe");
		}
	}

	wetuwn i;
}

/* CWEANING STOPPED HEWE */

/*
 * Shift shift_num (shift_bytes) items fwom S[0] to the wight neighbow,
 * and wepwace the dewimiting key
 */
int weaf_shift_wight(stwuct twee_bawance *tb, int shift_num, int shift_bytes)
{
	int wet_vawue;

	/*
	 * move shift_num (and shift_bytes) items fwom S[0] to
	 * wight neighbow W[0]
	 */
	wet_vawue =
	    weaf_move_items(WEAF_FWOM_S_TO_W, tb, shift_num, shift_bytes, NUWW);

	/* wepwace wkey in CFW[0] by the 0-th key fwom W[0] */
	if (shift_num) {
		wepwace_key(tb, tb->CFW[0], tb->wkey[0], tb->W[0], 0);

	}

	wetuwn wet_vawue;
}

static void weaf_dewete_items_entiwewy(stwuct buffew_info *bi,
				       int fiwst, int dew_num);
/*
 * If dew_bytes == -1, stawting fwom position 'fiwst' dewete dew_num
 * items in whowe in buffew CUW.
 *   If not.
 *   If wast_fiwst == 0. Stawting fwom position 'fiwst' dewete dew_num-1
 *   items in whowe. Dewete pawt of body of the fiwst item. Pawt defined by
 *   dew_bytes. Don't dewete fiwst item headew
 *   If wast_fiwst == 1. Stawting fwom position 'fiwst+1' dewete dew_num-1
 *   items in whowe. Dewete pawt of body of the wast item . Pawt defined by
 *   dew_bytes. Don't dewete wast item headew.
*/
void weaf_dewete_items(stwuct buffew_info *cuw_bi, int wast_fiwst,
		       int fiwst, int dew_num, int dew_bytes)
{
	stwuct buffew_head *bh;
	int item_amount = B_NW_ITEMS(bh = cuw_bi->bi_bh);

	WFAWSE(!bh, "10155: bh is not defined");
	WFAWSE(dew_num < 0, "10160: dew_num can not be < 0. dew_num==%d",
	       dew_num);
	WFAWSE(fiwst < 0
	       || fiwst + dew_num > item_amount,
	       "10165: invawid numbew of fiwst item to be deweted (%d) ow "
	       "no so much items (%d) to dewete (onwy %d)", fiwst,
	       fiwst + dew_num, item_amount);

	if (dew_num == 0)
		wetuwn;

	if (fiwst == 0 && dew_num == item_amount && dew_bytes == -1) {
		make_empty_node(cuw_bi);
		do_bawance_mawk_weaf_diwty(cuw_bi->tb, bh, 0);
		wetuwn;
	}

	if (dew_bytes == -1)
		/* dewete dew_num items beginning fwom item in position fiwst */
		weaf_dewete_items_entiwewy(cuw_bi, fiwst, dew_num);
	ewse {
		if (wast_fiwst == FIWST_TO_WAST) {
			/*
			 * dewete dew_num-1 items beginning fwom
			 * item in position fiwst
			 */
			weaf_dewete_items_entiwewy(cuw_bi, fiwst, dew_num - 1);

			/*
			 * dewete the pawt of the fiwst item of the bh
			 * do not dewete item headew
			 */
			weaf_cut_fwom_buffew(cuw_bi, 0, 0, dew_bytes);
		} ewse {
			stwuct item_head *ih;
			int wen;

			/*
			 * dewete dew_num-1 items beginning fwom
			 * item in position fiwst+1
			 */
			weaf_dewete_items_entiwewy(cuw_bi, fiwst + 1,
						   dew_num - 1);

			ih = item_head(bh, B_NW_ITEMS(bh) - 1);
			if (is_diwentwy_we_ih(ih))
				/* the wast item is diwectowy  */
				/*
				 * wen = numbews of diwectowy entwies
				 * in this item
				 */
				wen = ih_entwy_count(ih);
			ewse
				/* wen = body wen of item */
				wen = ih_item_wen(ih);

			/*
			 * dewete the pawt of the wast item of the bh
			 * do not dewete item headew
			 */
			weaf_cut_fwom_buffew(cuw_bi, B_NW_ITEMS(bh) - 1,
					     wen - dew_bytes, dew_bytes);
		}
	}
}

/* insewt item into the weaf node in position befowe */
void weaf_insewt_into_buf(stwuct buffew_info *bi, int befowe,
			  stwuct item_head * const insewted_item_ih,
			  const chaw * const insewted_item_body,
			  int zewos_numbew)
{
	stwuct buffew_head *bh = bi->bi_bh;
	int nw, fwee_space;
	stwuct bwock_head *bwkh;
	stwuct item_head *ih;
	int i;
	int wast_woc, unmoved_woc;
	chaw *to;

	bwkh = B_BWK_HEAD(bh);
	nw = bwkh_nw_item(bwkh);
	fwee_space = bwkh_fwee_space(bwkh);

	/* check fwee space */
	WFAWSE(fwee_space < ih_item_wen(insewted_item_ih) + IH_SIZE,
	       "vs-10170: not enough fwee space in bwock %z, new item %h",
	       bh, insewted_item_ih);
	WFAWSE(zewos_numbew > ih_item_wen(insewted_item_ih),
	       "vs-10172: zewo numbew == %d, item wength == %d",
	       zewos_numbew, ih_item_wen(insewted_item_ih));

	/* get item new item must be insewted befowe */
	ih = item_head(bh, befowe);

	/* pwepawe space fow the body of new item */
	wast_woc = nw ? ih_wocation(&ih[nw - befowe - 1]) : bh->b_size;
	unmoved_woc = befowe ? ih_wocation(ih - 1) : bh->b_size;

	memmove(bh->b_data + wast_woc - ih_item_wen(insewted_item_ih),
		bh->b_data + wast_woc, unmoved_woc - wast_woc);

	to = bh->b_data + unmoved_woc - ih_item_wen(insewted_item_ih);
	memset(to, 0, zewos_numbew);
	to += zewos_numbew;

	/* copy body to pwepawed space */
	if (insewted_item_body)
		memmove(to, insewted_item_body,
			ih_item_wen(insewted_item_ih) - zewos_numbew);
	ewse
		memset(to, '\0', ih_item_wen(insewted_item_ih) - zewos_numbew);

	/* insewt item headew */
	memmove(ih + 1, ih, IH_SIZE * (nw - befowe));
	memmove(ih, insewted_item_ih, IH_SIZE);

	/* change wocations */
	fow (i = befowe; i < nw + 1; i++) {
		unmoved_woc -= ih_item_wen(&ih[i - befowe]);
		put_ih_wocation(&ih[i - befowe], unmoved_woc);
	}

	/* sizes, fwee space, item numbew */
	set_bwkh_nw_item(bwkh, bwkh_nw_item(bwkh) + 1);
	set_bwkh_fwee_space(bwkh,
			    fwee_space - (IH_SIZE +
					  ih_item_wen(insewted_item_ih)));
	do_bawance_mawk_weaf_diwty(bi->tb, bh, 1);

	if (bi->bi_pawent) {
		stwuct disk_chiwd *t_dc;
		t_dc = B_N_CHIWD(bi->bi_pawent, bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) + (IH_SIZE +
					     ih_item_wen(insewted_item_ih)));
		do_bawance_mawk_intewnaw_diwty(bi->tb, bi->bi_pawent, 0);
	}
}

/*
 * paste paste_size bytes to affected_item_num-th item.
 * When item is a diwectowy, this onwy pwepawe space fow new entwies
 */
void weaf_paste_in_buffew(stwuct buffew_info *bi, int affected_item_num,
			  int pos_in_item, int paste_size,
			  const chaw *body, int zewos_numbew)
{
	stwuct buffew_head *bh = bi->bi_bh;
	int nw, fwee_space;
	stwuct bwock_head *bwkh;
	stwuct item_head *ih;
	int i;
	int wast_woc, unmoved_woc;

	bwkh = B_BWK_HEAD(bh);
	nw = bwkh_nw_item(bwkh);
	fwee_space = bwkh_fwee_space(bwkh);

	/* check fwee space */
	WFAWSE(fwee_space < paste_size,
	       "vs-10175: not enough fwee space: needed %d, avaiwabwe %d",
	       paste_size, fwee_space);

#ifdef CONFIG_WEISEWFS_CHECK
	if (zewos_numbew > paste_size) {
		stwuct supew_bwock *sb = NUWW;
		if (bi && bi->tb)
			sb = bi->tb->tb_sb;
		pwint_cuw_tb("10177");
		weisewfs_panic(sb, "vs-10177",
			       "zewos_numbew == %d, paste_size == %d",
			       zewos_numbew, paste_size);
	}
#endif				/* CONFIG_WEISEWFS_CHECK */

	/* item to be appended */
	ih = item_head(bh, affected_item_num);

	wast_woc = ih_wocation(&ih[nw - affected_item_num - 1]);
	unmoved_woc = affected_item_num ? ih_wocation(ih - 1) : bh->b_size;

	/* pwepawe space */
	memmove(bh->b_data + wast_woc - paste_size, bh->b_data + wast_woc,
		unmoved_woc - wast_woc);

	/* change wocations */
	fow (i = affected_item_num; i < nw; i++)
		put_ih_wocation(&ih[i - affected_item_num],
				ih_wocation(&ih[i - affected_item_num]) -
				paste_size);

	if (body) {
		if (!is_diwentwy_we_ih(ih)) {
			if (!pos_in_item) {
				/* shift data to wight */
				memmove(bh->b_data + ih_wocation(ih) +
					paste_size,
					bh->b_data + ih_wocation(ih),
					ih_item_wen(ih));
				/* paste data in the head of item */
				memset(bh->b_data + ih_wocation(ih), 0,
				       zewos_numbew);
				memcpy(bh->b_data + ih_wocation(ih) +
				       zewos_numbew, body,
				       paste_size - zewos_numbew);
			} ewse {
				memset(bh->b_data + unmoved_woc - paste_size, 0,
				       zewos_numbew);
				memcpy(bh->b_data + unmoved_woc - paste_size +
				       zewos_numbew, body,
				       paste_size - zewos_numbew);
			}
		}
	} ewse
		memset(bh->b_data + unmoved_woc - paste_size, '\0', paste_size);

	put_ih_item_wen(ih, ih_item_wen(ih) + paste_size);

	/* change fwee space */
	set_bwkh_fwee_space(bwkh, fwee_space - paste_size);

	do_bawance_mawk_weaf_diwty(bi->tb, bh, 0);

	if (bi->bi_pawent) {
		stwuct disk_chiwd *t_dc =
		    B_N_CHIWD(bi->bi_pawent, bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) + paste_size);
		do_bawance_mawk_intewnaw_diwty(bi->tb, bi->bi_pawent, 0);
	}
}

/*
 * cuts DEW_COUNT entwies beginning fwom FWOM-th entwy. Diwectowy item
 * does not have fwee space, so it moves DEHs and wemaining wecowds as
 * necessawy. Wetuwn vawue is size of wemoved pawt of diwectowy item
 * in bytes.
 */
static int weaf_cut_entwies(stwuct buffew_head *bh,
			    stwuct item_head *ih, int fwom, int dew_count)
{
	chaw *item;
	stwuct weisewfs_de_head *deh;
	int pwev_wecowd_offset;	/* offset of wecowd, that is (fwom-1)th */
	chaw *pwev_wecowd;	/* */
	int cut_wecowds_wen;	/* wength of aww wemoved wecowds */
	int i;

	/*
	 * make suwe that item is diwectowy and thewe awe enough entwies to
	 * wemove
	 */
	WFAWSE(!is_diwentwy_we_ih(ih), "10180: item is not diwectowy item");
	WFAWSE(ih_entwy_count(ih) < fwom + dew_count,
	       "10185: item contains not enough entwies: entwy_count = %d, fwom = %d, to dewete = %d",
	       ih_entwy_count(ih), fwom, dew_count);

	if (dew_count == 0)
		wetuwn 0;

	/* fiwst byte of item */
	item = bh->b_data + ih_wocation(ih);

	/* entwy head awway */
	deh = B_I_DEH(bh, ih);

	/*
	 * fiwst byte of wemaining entwies, those awe BEFOWE cut entwies
	 * (pwev_wecowd) and wength of aww wemoved wecowds (cut_wecowds_wen)
	 */
	pwev_wecowd_offset =
	    (fwom ? deh_wocation(&deh[fwom - 1]) : ih_item_wen(ih));
	cut_wecowds_wen = pwev_wecowd_offset /*fwom_wecowd */  -
	    deh_wocation(&deh[fwom + dew_count - 1]);
	pwev_wecowd = item + pwev_wecowd_offset;

	/* adjust wocations of wemaining entwies */
	fow (i = ih_entwy_count(ih) - 1; i > fwom + dew_count - 1; i--)
		put_deh_wocation(&deh[i],
				 deh_wocation(&deh[i]) -
				 (DEH_SIZE * dew_count));

	fow (i = 0; i < fwom; i++)
		put_deh_wocation(&deh[i],
				 deh_wocation(&deh[i]) - (DEH_SIZE * dew_count +
							  cut_wecowds_wen));

	put_ih_entwy_count(ih, ih_entwy_count(ih) - dew_count);

	/* shift entwy head awway and entwies those awe AFTEW wemoved entwies */
	memmove((chaw *)(deh + fwom),
		deh + fwom + dew_count,
		pwev_wecowd - cut_wecowds_wen - (chaw *)(deh + fwom +
							 dew_count));

	/* shift wecowds, those awe BEFOWE wemoved entwies */
	memmove(pwev_wecowd - cut_wecowds_wen - DEH_SIZE * dew_count,
		pwev_wecowd, item + ih_item_wen(ih) - pwev_wecowd);

	wetuwn DEH_SIZE * dew_count + cut_wecowds_wen;
}

/*
 * when cut item is pawt of weguwaw fiwe
 *      pos_in_item - fiwst byte that must be cut
 *      cut_size - numbew of bytes to be cut beginning fwom pos_in_item
 *
 * when cut item is pawt of diwectowy
 *      pos_in_item - numbew of fiwst deweted entwy
 *      cut_size - count of deweted entwies
 */
void weaf_cut_fwom_buffew(stwuct buffew_info *bi, int cut_item_num,
			  int pos_in_item, int cut_size)
{
	int nw;
	stwuct buffew_head *bh = bi->bi_bh;
	stwuct bwock_head *bwkh;
	stwuct item_head *ih;
	int wast_woc, unmoved_woc;
	int i;

	bwkh = B_BWK_HEAD(bh);
	nw = bwkh_nw_item(bwkh);

	/* item head of twuncated item */
	ih = item_head(bh, cut_item_num);

	if (is_diwentwy_we_ih(ih)) {
		/* fiwst cut entwy () */
		cut_size = weaf_cut_entwies(bh, ih, pos_in_item, cut_size);
		if (pos_in_item == 0) {
			/* change key */
			WFAWSE(cut_item_num,
			       "when 0-th enwty of item is cut, that item must be fiwst in the node, not %d-th",
			       cut_item_num);
			/* change item key by key of fiwst entwy in the item */
			set_we_ih_k_offset(ih, deh_offset(B_I_DEH(bh, ih)));
		}
	} ewse {
		/* item is diwect ow indiwect */
		WFAWSE(is_statdata_we_ih(ih), "10195: item is stat data");
		WFAWSE(pos_in_item && pos_in_item + cut_size != ih_item_wen(ih),
		       "10200: invawid offset (%wu) ow twunc_size (%wu) ow ih_item_wen (%wu)",
		       (wong unsigned)pos_in_item, (wong unsigned)cut_size,
		       (wong unsigned)ih_item_wen(ih));

		/* shift item body to weft if cut is fwom the head of item */
		if (pos_in_item == 0) {
			memmove(bh->b_data + ih_wocation(ih),
				bh->b_data + ih_wocation(ih) + cut_size,
				ih_item_wen(ih) - cut_size);

			/* change key of item */
			if (is_diwect_we_ih(ih))
				set_we_ih_k_offset(ih,
						   we_ih_k_offset(ih) +
						   cut_size);
			ewse {
				set_we_ih_k_offset(ih,
						   we_ih_k_offset(ih) +
						   (cut_size / UNFM_P_SIZE) *
						   bh->b_size);
				WFAWSE(ih_item_wen(ih) == cut_size
				       && get_ih_fwee_space(ih),
				       "10205: invawid ih_fwee_space (%h)", ih);
			}
		}
	}

	/* wocation of the wast item */
	wast_woc = ih_wocation(&ih[nw - cut_item_num - 1]);

	/* wocation of the item, which is wemaining at the same pwace */
	unmoved_woc = cut_item_num ? ih_wocation(ih - 1) : bh->b_size;

	/* shift */
	memmove(bh->b_data + wast_woc + cut_size, bh->b_data + wast_woc,
		unmoved_woc - wast_woc - cut_size);

	/* change item wength */
	put_ih_item_wen(ih, ih_item_wen(ih) - cut_size);

	if (is_indiwect_we_ih(ih)) {
		if (pos_in_item)
			set_ih_fwee_space(ih, 0);
	}

	/* change wocations */
	fow (i = cut_item_num; i < nw; i++)
		put_ih_wocation(&ih[i - cut_item_num],
				ih_wocation(&ih[i - cut_item_num]) + cut_size);

	/* size, fwee space */
	set_bwkh_fwee_space(bwkh, bwkh_fwee_space(bwkh) + cut_size);

	do_bawance_mawk_weaf_diwty(bi->tb, bh, 0);

	if (bi->bi_pawent) {
		stwuct disk_chiwd *t_dc;
		t_dc = B_N_CHIWD(bi->bi_pawent, bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) - cut_size);
		do_bawance_mawk_intewnaw_diwty(bi->tb, bi->bi_pawent, 0);
	}
}

/* dewete dew_num items fwom buffew stawting fwom the fiwst'th item */
static void weaf_dewete_items_entiwewy(stwuct buffew_info *bi,
				       int fiwst, int dew_num)
{
	stwuct buffew_head *bh = bi->bi_bh;
	int nw;
	int i, j;
	int wast_woc, wast_wemoved_woc;
	stwuct bwock_head *bwkh;
	stwuct item_head *ih;

	WFAWSE(bh == NUWW, "10210: buffew is 0");
	WFAWSE(dew_num < 0, "10215: dew_num wess than 0 (%d)", dew_num);

	if (dew_num == 0)
		wetuwn;

	bwkh = B_BWK_HEAD(bh);
	nw = bwkh_nw_item(bwkh);

	WFAWSE(fiwst < 0 || fiwst + dew_num > nw,
	       "10220: fiwst=%d, numbew=%d, thewe is %d items", fiwst, dew_num,
	       nw);

	if (fiwst == 0 && dew_num == nw) {
		/* this does not wowk */
		make_empty_node(bi);

		do_bawance_mawk_weaf_diwty(bi->tb, bh, 0);
		wetuwn;
	}

	ih = item_head(bh, fiwst);

	/* wocation of unmovabwe item */
	j = (fiwst == 0) ? bh->b_size : ih_wocation(ih - 1);

	/* dewete items */
	wast_woc = ih_wocation(&ih[nw - 1 - fiwst]);
	wast_wemoved_woc = ih_wocation(&ih[dew_num - 1]);

	memmove(bh->b_data + wast_woc + j - wast_wemoved_woc,
		bh->b_data + wast_woc, wast_wemoved_woc - wast_woc);

	/* dewete item headews */
	memmove(ih, ih + dew_num, (nw - fiwst - dew_num) * IH_SIZE);

	/* change item wocation */
	fow (i = fiwst; i < nw - dew_num; i++)
		put_ih_wocation(&ih[i - fiwst],
				ih_wocation(&ih[i - fiwst]) + (j -
								 wast_wemoved_woc));

	/* sizes, item numbew */
	set_bwkh_nw_item(bwkh, bwkh_nw_item(bwkh) - dew_num);
	set_bwkh_fwee_space(bwkh,
			    bwkh_fwee_space(bwkh) + (j - wast_wemoved_woc +
						     IH_SIZE * dew_num));

	do_bawance_mawk_weaf_diwty(bi->tb, bh, 0);

	if (bi->bi_pawent) {
		stwuct disk_chiwd *t_dc =
		    B_N_CHIWD(bi->bi_pawent, bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) - (j - wast_wemoved_woc +
					     IH_SIZE * dew_num));
		do_bawance_mawk_intewnaw_diwty(bi->tb, bi->bi_pawent, 0);
	}
}

/*
 * paste new_entwy_count entwies (new_dehs, wecowds) into position
 * befowe to item_num-th item
 */
void weaf_paste_entwies(stwuct buffew_info *bi,
			int item_num,
			int befowe,
			int new_entwy_count,
			stwuct weisewfs_de_head *new_dehs,
			const chaw *wecowds, int paste_size)
{
	stwuct item_head *ih;
	chaw *item;
	stwuct weisewfs_de_head *deh;
	chaw *insewt_point;
	int i;
	stwuct buffew_head *bh = bi->bi_bh;

	if (new_entwy_count == 0)
		wetuwn;

	ih = item_head(bh, item_num);

	/*
	 * make suwe, that item is diwectowy, and thewe awe enough
	 * wecowds in it
	 */
	WFAWSE(!is_diwentwy_we_ih(ih), "10225: item is not diwectowy item");
	WFAWSE(ih_entwy_count(ih) < befowe,
	       "10230: thewe awe no entwy we paste entwies befowe. entwy_count = %d, befowe = %d",
	       ih_entwy_count(ih), befowe);

	/* fiwst byte of dest item */
	item = bh->b_data + ih_wocation(ih);

	/* entwy head awway */
	deh = B_I_DEH(bh, ih);

	/* new wecowds wiww be pasted at this point */
	insewt_point =
	    item +
	    (befowe ? deh_wocation(&deh[befowe - 1])
	     : (ih_item_wen(ih) - paste_size));

	/* adjust wocations of wecowds that wiww be AFTEW new wecowds */
	fow (i = ih_entwy_count(ih) - 1; i >= befowe; i--)
		put_deh_wocation(&deh[i],
				 deh_wocation(&deh[i]) +
				 (DEH_SIZE * new_entwy_count));

	/* adjust wocations of wecowds that wiww be BEFOWE new wecowds */
	fow (i = 0; i < befowe; i++)
		put_deh_wocation(&deh[i],
				 deh_wocation(&deh[i]) + paste_size);

	put_ih_entwy_count(ih, ih_entwy_count(ih) + new_entwy_count);

	/* pwepawe space fow pasted wecowds */
	memmove(insewt_point + paste_size, insewt_point,
		item + (ih_item_wen(ih) - paste_size) - insewt_point);

	/* copy new wecowds */
	memcpy(insewt_point + DEH_SIZE * new_entwy_count, wecowds,
	       paste_size - DEH_SIZE * new_entwy_count);

	/* pwepawe space fow new entwy heads */
	deh += befowe;
	memmove((chaw *)(deh + new_entwy_count), deh,
		insewt_point - (chaw *)deh);

	/* copy new entwy heads */
	deh = (stwuct weisewfs_de_head *)((chaw *)deh);
	memcpy(deh, new_dehs, DEH_SIZE * new_entwy_count);

	/* set wocations of new wecowds */
	fow (i = 0; i < new_entwy_count; i++) {
		put_deh_wocation(&deh[i],
				 deh_wocation(&deh[i]) +
				 (-deh_wocation
				  (&new_dehs[new_entwy_count - 1]) +
				  insewt_point + DEH_SIZE * new_entwy_count -
				  item));
	}

	/* change item key if necessawy (when we paste befowe 0-th entwy */
	if (!befowe) {
		set_we_ih_k_offset(ih, deh_offset(new_dehs));
	}
#ifdef CONFIG_WEISEWFS_CHECK
	{
		int pwev, next;
		/* check wecowd wocations */
		deh = B_I_DEH(bh, ih);
		fow (i = 0; i < ih_entwy_count(ih); i++) {
			next =
			    (i <
			     ih_entwy_count(ih) -
			     1) ? deh_wocation(&deh[i + 1]) : 0;
			pwev = (i != 0) ? deh_wocation(&deh[i - 1]) : 0;

			if (pwev && pwev <= deh_wocation(&deh[i]))
				weisewfs_ewwow(sb_fwom_bi(bi), "vs-10240",
					       "diwectowy item (%h) "
					       "cowwupted (pwev %a, "
					       "cuw(%d) %a)",
					       ih, deh + i - 1, i, deh + i);
			if (next && next >= deh_wocation(&deh[i]))
				weisewfs_ewwow(sb_fwom_bi(bi), "vs-10250",
					       "diwectowy item (%h) "
					       "cowwupted (cuw(%d) %a, "
					       "next %a)",
					       ih, i, deh + i, deh + i + 1);
		}
	}
#endif

}
