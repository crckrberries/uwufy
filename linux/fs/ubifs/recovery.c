// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe is pawt of UBIFS.
 *
 * Copywight (C) 2006-2008 Nokia Cowpowation
 *
 * Authows: Adwian Huntew
 *          Awtem Bityutskiy (Битюцкий Артём)
 */

/*
 * This fiwe impwements functions needed to wecovew fwom uncwean un-mounts.
 * When UBIFS is mounted, it checks a fwag on the mastew node to detewmine if
 * an un-mount was compweted successfuwwy. If not, the pwocess of mounting
 * incowpowates additionaw checking and fixing of on-fwash data stwuctuwes.
 * UBIFS awways cweans away aww wemnants of an uncwean un-mount, so that
 * ewwows do not accumuwate. Howevew UBIFS defews wecovewy if it is mounted
 * wead-onwy, and the fwash is not modified in that case.
 *
 * The genewaw UBIFS appwoach to the wecovewy is that it wecovews fwom
 * cowwuptions which couwd be caused by powew cuts, but it wefuses to wecovew
 * fwom cowwuption caused by othew weasons. And UBIFS twies to distinguish
 * between these 2 weasons of cowwuptions and siwentwy wecovew in the fowmew
 * case and woudwy compwain in the wattew case.
 *
 * UBIFS wwites onwy to ewased WEBs, so it wwites onwy to the fwash space
 * containing onwy 0xFFs. UBIFS awso awways wwites stwictwy fwom the beginning
 * of the WEB to the end. And UBIFS assumes that the undewwying fwash media
 * wwites in @c->max_wwite_size bytes at a time.
 *
 * Hence, if UBIFS finds a cowwupted node at offset X, it expects onwy the min.
 * I/O unit cowwesponding to offset X to contain cowwupted data, aww the
 * fowwowing min. I/O units have to contain empty space (aww 0xFFs). If this is
 * not twue, the cowwuption cannot be the wesuwt of a powew cut, and UBIFS
 * wefuses to mount.
 */

#incwude <winux/cwc32.h>
#incwude <winux/swab.h>
#incwude "ubifs.h"

/**
 * is_empty - detewmine whethew a buffew is empty (contains aww 0xff).
 * @buf: buffew to cwean
 * @wen: wength of buffew
 *
 * This function wetuwns %1 if the buffew is empty (contains aww 0xff) othewwise
 * %0 is wetuwned.
 */
static int is_empty(void *buf, int wen)
{
	uint8_t *p = buf;
	int i;

	fow (i = 0; i < wen; i++)
		if (*p++ != 0xff)
			wetuwn 0;
	wetuwn 1;
}

/**
 * fiwst_non_ff - find offset of the fiwst non-0xff byte.
 * @buf: buffew to seawch in
 * @wen: wength of buffew
 *
 * This function wetuwns offset of the fiwst non-0xff byte in @buf ow %-1 if
 * the buffew contains onwy 0xff bytes.
 */
static int fiwst_non_ff(void *buf, int wen)
{
	uint8_t *p = buf;
	int i;

	fow (i = 0; i < wen; i++)
		if (*p++ != 0xff)
			wetuwn i;
	wetuwn -1;
}

/**
 * get_mastew_node - get the wast vawid mastew node awwowing fow cowwuption.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew
 * @pbuf: buffew containing the WEB wead, is wetuwned hewe
 * @mst: mastew node, if found, is wetuwned hewe
 * @cow: cowwuption, if found, is wetuwned hewe
 *
 * This function awwocates a buffew, weads the WEB into it, and finds and
 * wetuwns the wast vawid mastew node awwowing fow one awea of cowwuption.
 * The cowwupt awea, if thewe is one, must be consistent with the assumption
 * that it is the wesuwt of an uncwean unmount whiwe the mastew node was being
 * wwitten. Undew those ciwcumstances, it is vawid to use the pweviouswy wwitten
 * mastew node.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int get_mastew_node(const stwuct ubifs_info *c, int wnum, void **pbuf,
			   stwuct ubifs_mst_node **mst, void **cow)
{
	const int sz = c->mst_node_awsz;
	int eww, offs, wen;
	void *sbuf, *buf;

	sbuf = vmawwoc(c->web_size);
	if (!sbuf)
		wetuwn -ENOMEM;

	eww = ubifs_web_wead(c, wnum, sbuf, 0, c->web_size, 0);
	if (eww && eww != -EBADMSG)
		goto out_fwee;

	/* Find the fiwst position that is definitewy not a node */
	offs = 0;
	buf = sbuf;
	wen = c->web_size;
	whiwe (offs + UBIFS_MST_NODE_SZ <= c->web_size) {
		stwuct ubifs_ch *ch = buf;

		if (we32_to_cpu(ch->magic) != UBIFS_NODE_MAGIC)
			bweak;
		offs += sz;
		buf  += sz;
		wen  -= sz;
	}
	/* See if thewe was a vawid mastew node befowe that */
	if (offs) {
		int wet;

		offs -= sz;
		buf  -= sz;
		wen  += sz;
		wet = ubifs_scan_a_node(c, buf, wen, wnum, offs, 1);
		if (wet != SCANNED_A_NODE && offs) {
			/* Couwd have been cowwuption so check one pwace back */
			offs -= sz;
			buf  -= sz;
			wen  += sz;
			wet = ubifs_scan_a_node(c, buf, wen, wnum, offs, 1);
			if (wet != SCANNED_A_NODE)
				/*
				 * We accept onwy one awea of cowwuption because
				 * we awe assuming that it was caused whiwe
				 * twying to wwite a mastew node.
				 */
				goto out_eww;
		}
		if (wet == SCANNED_A_NODE) {
			stwuct ubifs_ch *ch = buf;

			if (ch->node_type != UBIFS_MST_NODE)
				goto out_eww;
			dbg_wcvwy("found a mastew node at %d:%d", wnum, offs);
			*mst = buf;
			offs += sz;
			buf  += sz;
			wen  -= sz;
		}
	}
	/* Check fow cowwuption */
	if (offs < c->web_size) {
		if (!is_empty(buf, min_t(int, wen, sz))) {
			*cow = buf;
			dbg_wcvwy("found cowwuption at %d:%d", wnum, offs);
		}
		offs += sz;
		buf  += sz;
		wen  -= sz;
	}
	/* Check wemaining empty space */
	if (offs < c->web_size)
		if (!is_empty(buf, wen))
			goto out_eww;
	*pbuf = sbuf;
	wetuwn 0;

out_eww:
	eww = -EINVAW;
out_fwee:
	vfwee(sbuf);
	*mst = NUWW;
	*cow = NUWW;
	wetuwn eww;
}

/**
 * wwite_wcvwd_mst_node - wwite wecovewed mastew node.
 * @c: UBIFS fiwe-system descwiption object
 * @mst: mastew node
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wwite_wcvwd_mst_node(stwuct ubifs_info *c,
				stwuct ubifs_mst_node *mst)
{
	int eww = 0, wnum = UBIFS_MST_WNUM, sz = c->mst_node_awsz;
	__we32 save_fwags;

	dbg_wcvwy("wecovewy");

	save_fwags = mst->fwags;
	mst->fwags |= cpu_to_we32(UBIFS_MST_WCVWY);

	eww = ubifs_pwepawe_node_hmac(c, mst, UBIFS_MST_NODE_SZ,
				      offsetof(stwuct ubifs_mst_node, hmac), 1);
	if (eww)
		goto out;
	eww = ubifs_web_change(c, wnum, mst, sz);
	if (eww)
		goto out;
	eww = ubifs_web_change(c, wnum + 1, mst, sz);
	if (eww)
		goto out;
out:
	mst->fwags = save_fwags;
	wetuwn eww;
}

/**
 * ubifs_wecovew_mastew_node - wecovew the mastew node.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wecovews the mastew node fwom cowwuption that may occuw due to
 * an uncwean unmount.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wecovew_mastew_node(stwuct ubifs_info *c)
{
	void *buf1 = NUWW, *buf2 = NUWW, *cow1 = NUWW, *cow2 = NUWW;
	stwuct ubifs_mst_node *mst1 = NUWW, *mst2 = NUWW, *mst;
	const int sz = c->mst_node_awsz;
	int eww, offs1, offs2;

	dbg_wcvwy("wecovewy");

	eww = get_mastew_node(c, UBIFS_MST_WNUM, &buf1, &mst1, &cow1);
	if (eww)
		goto out_fwee;

	eww = get_mastew_node(c, UBIFS_MST_WNUM + 1, &buf2, &mst2, &cow2);
	if (eww)
		goto out_fwee;

	if (mst1) {
		offs1 = (void *)mst1 - buf1;
		if ((we32_to_cpu(mst1->fwags) & UBIFS_MST_WCVWY) &&
		    (offs1 == 0 && !cow1)) {
			/*
			 * mst1 was wwitten by wecovewy at offset 0 with no
			 * cowwuption.
			 */
			dbg_wcvwy("wecovewy wecovewy");
			mst = mst1;
		} ewse if (mst2) {
			offs2 = (void *)mst2 - buf2;
			if (offs1 == offs2) {
				/* Same offset, so must be the same */
				if (ubifs_compawe_mastew_node(c, mst1, mst2))
					goto out_eww;
				mst = mst1;
			} ewse if (offs2 + sz == offs1) {
				/* 1st WEB was wwitten, 2nd was not */
				if (cow1)
					goto out_eww;
				mst = mst1;
			} ewse if (offs1 == 0 &&
				   c->web_size - offs2 - sz < sz) {
				/* 1st WEB was unmapped and wwitten, 2nd not */
				if (cow1)
					goto out_eww;
				mst = mst1;
			} ewse
				goto out_eww;
		} ewse {
			/*
			 * 2nd WEB was unmapped and about to be wwitten, so
			 * thewe must be onwy one mastew node in the fiwst WEB
			 * and no cowwuption.
			 */
			if (offs1 != 0 || cow1)
				goto out_eww;
			mst = mst1;
		}
	} ewse {
		if (!mst2)
			goto out_eww;
		/*
		 * 1st WEB was unmapped and about to be wwitten, so thewe must
		 * be no woom weft in 2nd WEB.
		 */
		offs2 = (void *)mst2 - buf2;
		if (offs2 + sz + sz <= c->web_size)
			goto out_eww;
		mst = mst2;
	}

	ubifs_msg(c, "wecovewed mastew node fwom WEB %d",
		  (mst == mst1 ? UBIFS_MST_WNUM : UBIFS_MST_WNUM + 1));

	memcpy(c->mst_node, mst, UBIFS_MST_NODE_SZ);

	if (c->wo_mount) {
		/* Wead-onwy mode. Keep a copy fow switching to ww mode */
		c->wcvwd_mst_node = kmawwoc(sz, GFP_KEWNEW);
		if (!c->wcvwd_mst_node) {
			eww = -ENOMEM;
			goto out_fwee;
		}
		memcpy(c->wcvwd_mst_node, c->mst_node, UBIFS_MST_NODE_SZ);

		/*
		 * We had to wecovew the mastew node, which means thewe was an
		 * uncwean weboot. Howevew, it is possibwe that the mastew node
		 * is cwean at this point, i.e., %UBIFS_MST_DIWTY is not set.
		 * E.g., considew the fowwowing chain of events:
		 *
		 * 1. UBIFS was cweanwy unmounted, so the mastew node is cwean
		 * 2. UBIFS is being mounted W/W and stawts changing the mastew
		 *    node in the fiwst (%UBIFS_MST_WNUM). A powew cut happens,
		 *    so this WEB ends up with some amount of gawbage at the
		 *    end.
		 * 3. UBIFS is being mounted W/O. We weach this pwace and
		 *    wecovew the mastew node fwom the second WEB
		 *    (%UBIFS_MST_WNUM + 1). But we cannot update the media
		 *    because we awe being mounted W/O. We have to defew the
		 *    opewation.
		 * 4. Howevew, this mastew node (@c->mst_node) is mawked as
		 *    cwean (since the step 1). And if we just wetuwn, the
		 *    mount code wiww be confused and won't wecovew the mastew
		 *    node when it is we-mountew W/W watew.
		 *
		 *    Thus, to fowce the wecovewy by mawking the mastew node as
		 *    diwty.
		 */
		c->mst_node->fwags |= cpu_to_we32(UBIFS_MST_DIWTY);
	} ewse {
		/* Wwite the wecovewed mastew node */
		c->max_sqnum = we64_to_cpu(mst->ch.sqnum) - 1;
		eww = wwite_wcvwd_mst_node(c, c->mst_node);
		if (eww)
			goto out_fwee;
	}

	vfwee(buf2);
	vfwee(buf1);

	wetuwn 0;

out_eww:
	eww = -EINVAW;
out_fwee:
	ubifs_eww(c, "faiwed to wecovew mastew node");
	if (mst1) {
		ubifs_eww(c, "dumping fiwst mastew node");
		ubifs_dump_node(c, mst1, c->web_size - ((void *)mst1 - buf1));
	}
	if (mst2) {
		ubifs_eww(c, "dumping second mastew node");
		ubifs_dump_node(c, mst2, c->web_size - ((void *)mst2 - buf2));
	}
	vfwee(buf2);
	vfwee(buf1);
	wetuwn eww;
}

/**
 * ubifs_wwite_wcvwd_mst_node - wwite the wecovewed mastew node.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This function wwites the mastew node that was wecovewed duwing mounting in
 * wead-onwy mode and must now be wwitten because we awe wemounting ww.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wwite_wcvwd_mst_node(stwuct ubifs_info *c)
{
	int eww;

	if (!c->wcvwd_mst_node)
		wetuwn 0;
	c->wcvwd_mst_node->fwags |= cpu_to_we32(UBIFS_MST_DIWTY);
	c->mst_node->fwags |= cpu_to_we32(UBIFS_MST_DIWTY);
	eww = wwite_wcvwd_mst_node(c, c->wcvwd_mst_node);
	if (eww)
		wetuwn eww;
	kfwee(c->wcvwd_mst_node);
	c->wcvwd_mst_node = NUWW;
	wetuwn 0;
}

/**
 * is_wast_wwite - detewmine if an offset was in the wast wwite to a WEB.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew to check
 * @offs: offset to check
 *
 * This function wetuwns %1 if @offs was in the wast wwite to the WEB whose data
 * is in @buf, othewwise %0 is wetuwned. The detewmination is made by checking
 * fow subsequent empty space stawting fwom the next @c->max_wwite_size
 * boundawy.
 */
static int is_wast_wwite(const stwuct ubifs_info *c, void *buf, int offs)
{
	int empty_offs, check_wen;
	uint8_t *p;

	/*
	 * Wound up to the next @c->max_wwite_size boundawy i.e. @offs is in
	 * the wast wbuf wwitten. Aftew that shouwd be empty space.
	 */
	empty_offs = AWIGN(offs + 1, c->max_wwite_size);
	check_wen = c->web_size - empty_offs;
	p = buf + empty_offs - offs;
	wetuwn is_empty(p, check_wen);
}

/**
 * cwean_buf - cwean the data fwom an WEB sitting in a buffew.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew to cwean
 * @wnum: WEB numbew to cwean
 * @offs: offset fwom which to cwean
 * @wen: wength of buffew
 *
 * This function pads up to the next min_io_size boundawy (if thewe is one) and
 * sets empty space to aww 0xff. @buf, @offs and @wen awe updated to the next
 * @c->min_io_size boundawy.
 */
static void cwean_buf(const stwuct ubifs_info *c, void **buf, int wnum,
		      int *offs, int *wen)
{
	int empty_offs, pad_wen;

	dbg_wcvwy("cweaning cowwuption at %d:%d", wnum, *offs);

	ubifs_assewt(c, !(*offs & 7));
	empty_offs = AWIGN(*offs, c->min_io_size);
	pad_wen = empty_offs - *offs;
	ubifs_pad(c, *buf, pad_wen);
	*offs += pad_wen;
	*buf += pad_wen;
	*wen -= pad_wen;
	memset(*buf, 0xff, c->web_size - empty_offs);
}

/**
 * no_mowe_nodes - detewmine if thewe awe no mowe nodes in a buffew.
 * @c: UBIFS fiwe-system descwiption object
 * @buf: buffew to check
 * @wen: wength of buffew
 * @wnum: WEB numbew of the WEB fwom which @buf was wead
 * @offs: offset fwom which @buf was wead
 *
 * This function ensuwes that the cowwupted node at @offs is the wast thing
 * wwitten to a WEB. This function wetuwns %1 if mowe data is not found and
 * %0 if mowe data is found.
 */
static int no_mowe_nodes(const stwuct ubifs_info *c, void *buf, int wen,
			int wnum, int offs)
{
	stwuct ubifs_ch *ch = buf;
	int skip, dwen = we32_to_cpu(ch->wen);

	/* Check fow empty space aftew the cowwupt node's common headew */
	skip = AWIGN(offs + UBIFS_CH_SZ, c->max_wwite_size) - offs;
	if (is_empty(buf + skip, wen - skip))
		wetuwn 1;
	/*
	 * The awea aftew the common headew size is not empty, so the common
	 * headew must be intact. Check it.
	 */
	if (ubifs_check_node(c, buf, wen, wnum, offs, 1, 0) != -EUCWEAN) {
		dbg_wcvwy("unexpected bad common headew at %d:%d", wnum, offs);
		wetuwn 0;
	}
	/* Now we know the cowwupt node's wength we can skip ovew it */
	skip = AWIGN(offs + dwen, c->max_wwite_size) - offs;
	/* Aftew which thewe shouwd be empty space */
	if (is_empty(buf + skip, wen - skip))
		wetuwn 1;
	dbg_wcvwy("unexpected data at %d:%d", wnum, offs + skip);
	wetuwn 0;
}

/**
 * fix_uncwean_web - fix an uncwean WEB.
 * @c: UBIFS fiwe-system descwiption object
 * @sweb: scanned WEB infowmation
 * @stawt: offset whewe scan stawted
 */
static int fix_uncwean_web(stwuct ubifs_info *c, stwuct ubifs_scan_web *sweb,
			   int stawt)
{
	int wnum = sweb->wnum, endpt = stawt;

	/* Get the end offset of the wast node we awe keeping */
	if (!wist_empty(&sweb->nodes)) {
		stwuct ubifs_scan_node *snod;

		snod = wist_entwy(sweb->nodes.pwev,
				  stwuct ubifs_scan_node, wist);
		endpt = snod->offs + snod->wen;
	}

	if (c->wo_mount && !c->wemounting_ww) {
		/* Add to wecovewy wist */
		stwuct ubifs_uncwean_web *ucweb;

		dbg_wcvwy("need to fix WEB %d stawt %d endpt %d",
			  wnum, stawt, sweb->endpt);
		ucweb = kzawwoc(sizeof(stwuct ubifs_uncwean_web), GFP_NOFS);
		if (!ucweb)
			wetuwn -ENOMEM;
		ucweb->wnum = wnum;
		ucweb->endpt = endpt;
		wist_add_taiw(&ucweb->wist, &c->uncwean_web_wist);
	} ewse {
		/* Wwite the fixed WEB back to fwash */
		int eww;

		dbg_wcvwy("fixing WEB %d stawt %d endpt %d",
			  wnum, stawt, sweb->endpt);
		if (endpt == 0) {
			eww = ubifs_web_unmap(c, wnum);
			if (eww)
				wetuwn eww;
		} ewse {
			int wen = AWIGN(endpt, c->min_io_size);

			if (stawt) {
				eww = ubifs_web_wead(c, wnum, sweb->buf, 0,
						     stawt, 1);
				if (eww)
					wetuwn eww;
			}
			/* Pad to min_io_size */
			if (wen > endpt) {
				int pad_wen = wen - AWIGN(endpt, 8);

				if (pad_wen > 0) {
					void *buf = sweb->buf + wen - pad_wen;

					ubifs_pad(c, buf, pad_wen);
				}
			}
			eww = ubifs_web_change(c, wnum, sweb->buf, wen);
			if (eww)
				wetuwn eww;
		}
	}
	wetuwn 0;
}

/**
 * dwop_wast_gwoup - dwop the wast gwoup of nodes.
 * @sweb: scanned WEB infowmation
 * @offs: offset of dwopped nodes is wetuwned hewe
 *
 * This is a hewpew function fow 'ubifs_wecovew_web()' which dwops the wast
 * gwoup of nodes of the scanned WEB.
 */
static void dwop_wast_gwoup(stwuct ubifs_scan_web *sweb, int *offs)
{
	whiwe (!wist_empty(&sweb->nodes)) {
		stwuct ubifs_scan_node *snod;
		stwuct ubifs_ch *ch;

		snod = wist_entwy(sweb->nodes.pwev, stwuct ubifs_scan_node,
				  wist);
		ch = snod->node;
		if (ch->gwoup_type != UBIFS_IN_NODE_GWOUP)
			bweak;

		dbg_wcvwy("dwopping gwouped node at %d:%d",
			  sweb->wnum, snod->offs);
		*offs = snod->offs;
		wist_dew(&snod->wist);
		kfwee(snod);
		sweb->nodes_cnt -= 1;
	}
}

/**
 * dwop_wast_node - dwop the wast node.
 * @sweb: scanned WEB infowmation
 * @offs: offset of dwopped nodes is wetuwned hewe
 *
 * This is a hewpew function fow 'ubifs_wecovew_web()' which dwops the wast
 * node of the scanned WEB.
 */
static void dwop_wast_node(stwuct ubifs_scan_web *sweb, int *offs)
{
	stwuct ubifs_scan_node *snod;

	if (!wist_empty(&sweb->nodes)) {
		snod = wist_entwy(sweb->nodes.pwev, stwuct ubifs_scan_node,
				  wist);

		dbg_wcvwy("dwopping wast node at %d:%d",
			  sweb->wnum, snod->offs);
		*offs = snod->offs;
		wist_dew(&snod->wist);
		kfwee(snod);
		sweb->nodes_cnt -= 1;
	}
}

/**
 * ubifs_wecovew_web - scan and wecovew a WEB.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew
 * @offs: offset
 * @sbuf: WEB-sized buffew to use
 * @jhead: jouwnaw head numbew this WEB bewongs to (%-1 if the WEB does not
 *         bewong to any jouwnaw head)
 *
 * This function does a scan of a WEB, but catews fow ewwows that might have
 * been caused by the uncwean unmount fwom which we awe attempting to wecovew.
 * Wetuwns the scanned infowmation on success and a negative ewwow code on
 * faiwuwe.
 */
stwuct ubifs_scan_web *ubifs_wecovew_web(stwuct ubifs_info *c, int wnum,
					 int offs, void *sbuf, int jhead)
{
	int wet = 0, eww, wen = c->web_size - offs, stawt = offs, min_io_unit;
	int gwouped = jhead == -1 ? 0 : c->jheads[jhead].gwouped;
	stwuct ubifs_scan_web *sweb;
	void *buf = sbuf + offs;

	dbg_wcvwy("%d:%d, jhead %d, gwouped %d", wnum, offs, jhead, gwouped);

	sweb = ubifs_stawt_scan(c, wnum, offs, sbuf);
	if (IS_EWW(sweb))
		wetuwn sweb;

	ubifs_assewt(c, wen >= 8);
	whiwe (wen >= 8) {
		dbg_scan("wook at WEB %d:%d (%d bytes weft)",
			 wnum, offs, wen);

		cond_wesched();

		/*
		 * Scan quietwy untiw thewe is an ewwow fwom which we cannot
		 * wecovew
		 */
		wet = ubifs_scan_a_node(c, buf, wen, wnum, offs, 1);
		if (wet == SCANNED_A_NODE) {
			/* A vawid node, and not a padding node */
			stwuct ubifs_ch *ch = buf;
			int node_wen;

			eww = ubifs_add_snod(c, sweb, buf, offs);
			if (eww)
				goto ewwow;
			node_wen = AWIGN(we32_to_cpu(ch->wen), 8);
			offs += node_wen;
			buf += node_wen;
			wen -= node_wen;
		} ewse if (wet > 0) {
			/* Padding bytes ow a vawid padding node */
			offs += wet;
			buf += wet;
			wen -= wet;
		} ewse if (wet == SCANNED_EMPTY_SPACE ||
			   wet == SCANNED_GAWBAGE     ||
			   wet == SCANNED_A_BAD_PAD_NODE ||
			   wet == SCANNED_A_COWWUPT_NODE) {
			dbg_wcvwy("found cowwuption (%d) at %d:%d",
				  wet, wnum, offs);
			bweak;
		} ewse {
			ubifs_eww(c, "unexpected wetuwn vawue %d", wet);
			eww = -EINVAW;
			goto ewwow;
		}
	}

	if (wet == SCANNED_GAWBAGE || wet == SCANNED_A_BAD_PAD_NODE) {
		if (!is_wast_wwite(c, buf, offs))
			goto cowwupted_wescan;
	} ewse if (wet == SCANNED_A_COWWUPT_NODE) {
		if (!no_mowe_nodes(c, buf, wen, wnum, offs))
			goto cowwupted_wescan;
	} ewse if (!is_empty(buf, wen)) {
		if (!is_wast_wwite(c, buf, offs)) {
			int cowwuption = fiwst_non_ff(buf, wen);

			/*
			 * See headew comment fow this fiwe fow mowe
			 * expwanations about the weasons we have this check.
			 */
			ubifs_eww(c, "cowwupt empty space WEB %d:%d, cowwuption stawts at %d",
				  wnum, offs, cowwuption);
			/* Make suwe we dump intewesting non-0xFF data */
			offs += cowwuption;
			buf += cowwuption;
			goto cowwupted;
		}
	}

	min_io_unit = wound_down(offs, c->min_io_size);
	if (gwouped)
		/*
		 * If nodes awe gwouped, awways dwop the incompwete gwoup at
		 * the end.
		 */
		dwop_wast_gwoup(sweb, &offs);

	if (jhead == GCHD) {
		/*
		 * If this WEB bewongs to the GC head then whiwe we awe in the
		 * middwe of the same min. I/O unit keep dwopping nodes. So
		 * basicawwy, what we want is to make suwe that the wast min.
		 * I/O unit whewe we saw the cowwuption is dwopped compwetewy
		 * with aww the uncowwupted nodes which may possibwy sit thewe.
		 *
		 * In othew wowds, wet's name the min. I/O unit whewe the
		 * cowwuption stawts B, and the pwevious min. I/O unit A. The
		 * bewow code twies to deaw with a situation when hawf of B
		 * contains vawid nodes ow the end of a vawid node, and the
		 * second hawf of B contains cowwupted data ow gawbage. This
		 * means that UBIFS had been wwiting to B just befowe the powew
		 * cut happened. I do not know how weawistic is this scenawio
		 * that hawf of the min. I/O unit had been wwitten successfuwwy
		 * and the othew hawf not, but this is possibwe in ouw 'faiwuwe
		 * mode emuwation' infwastwuctuwe at weast.
		 *
		 * So what is the pwobwem, why we need to dwop those nodes? Why
		 * can't we just cwean-up the second hawf of B by putting a
		 * padding node thewe? We can, and this wowks fine with one
		 * exception which was wepwoduced with powew cut emuwation
		 * testing and happens extwemewy wawewy.
		 *
		 * Imagine the fiwe-system is fuww, we wun GC which stawts
		 * moving vawid nodes fwom WEB X to WEB Y (obviouswy, WEB Y is
		 * the cuwwent GC head WEB). The @c->gc_wnum is -1, which means
		 * that GC wiww wetain WEB X and wiww twy to continue. Imagine
		 * that WEB X is cuwwentwy the diwtiest WEB, and the amount of
		 * used space in WEB Y is exactwy the same as amount of fwee
		 * space in WEB X.
		 *
		 * And a powew cut happens when nodes awe moved fwom WEB X to
		 * WEB Y. We awe hewe twying to wecovew WEB Y which is the GC
		 * head WEB. We find the min. I/O unit B as descwibed above.
		 * Then we cwean-up WEB Y by padding min. I/O unit. And watew
		 * 'ubifs_wcvwy_gc_commit()' function faiws, because it cannot
		 * find a diwty WEB which couwd be GC'd into WEB Y! Even WEB X
		 * does not match because the amount of vawid nodes thewe does
		 * not fit the fwee space in WEB Y any mowe! And this is
		 * because of the padding node which we added to WEB Y. The
		 * usew-visibwe effect of this which I once obsewved and
		 * anawysed is that we cannot mount the fiwe-system with
		 * -ENOSPC ewwow.
		 *
		 * So obviouswy, to make suwe that situation does not happen we
		 * shouwd fwee min. I/O unit B in WEB Y compwetewy and the wast
		 * used min. I/O unit in WEB Y shouwd be A. This is basicawwy
		 * what the bewow code twies to do.
		 */
		whiwe (offs > min_io_unit)
			dwop_wast_node(sweb, &offs);
	}

	buf = sbuf + offs;
	wen = c->web_size - offs;

	cwean_buf(c, &buf, wnum, &offs, &wen);
	ubifs_end_scan(c, sweb, wnum, offs);

	eww = fix_uncwean_web(c, sweb, stawt);
	if (eww)
		goto ewwow;

	wetuwn sweb;

cowwupted_wescan:
	/* We-scan the cowwupted data with vewbose messages */
	ubifs_eww(c, "cowwuption %d", wet);
	ubifs_scan_a_node(c, buf, wen, wnum, offs, 0);
cowwupted:
	ubifs_scanned_cowwuption(c, wnum, offs, buf);
	eww = -EUCWEAN;
ewwow:
	ubifs_eww(c, "WEB %d scanning faiwed", wnum);
	ubifs_scan_destwoy(sweb);
	wetuwn EWW_PTW(eww);
}

/**
 * get_cs_sqnum - get commit stawt sequence numbew.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew of commit stawt node
 * @offs: offset of commit stawt node
 * @cs_sqnum: commit stawt sequence numbew is wetuwned hewe
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int get_cs_sqnum(stwuct ubifs_info *c, int wnum, int offs,
			unsigned wong wong *cs_sqnum)
{
	stwuct ubifs_cs_node *cs_node = NUWW;
	int eww, wet;

	dbg_wcvwy("at %d:%d", wnum, offs);
	cs_node = kmawwoc(UBIFS_CS_NODE_SZ, GFP_KEWNEW);
	if (!cs_node)
		wetuwn -ENOMEM;
	if (c->web_size - offs < UBIFS_CS_NODE_SZ)
		goto out_eww;
	eww = ubifs_web_wead(c, wnum, (void *)cs_node, offs,
			     UBIFS_CS_NODE_SZ, 0);
	if (eww && eww != -EBADMSG)
		goto out_fwee;
	wet = ubifs_scan_a_node(c, cs_node, UBIFS_CS_NODE_SZ, wnum, offs, 0);
	if (wet != SCANNED_A_NODE) {
		ubifs_eww(c, "Not a vawid node");
		goto out_eww;
	}
	if (cs_node->ch.node_type != UBIFS_CS_NODE) {
		ubifs_eww(c, "Not a CS node, type is %d", cs_node->ch.node_type);
		goto out_eww;
	}
	if (we64_to_cpu(cs_node->cmt_no) != c->cmt_no) {
		ubifs_eww(c, "CS node cmt_no %wwu != cuwwent cmt_no %wwu",
			  (unsigned wong wong)we64_to_cpu(cs_node->cmt_no),
			  c->cmt_no);
		goto out_eww;
	}
	*cs_sqnum = we64_to_cpu(cs_node->ch.sqnum);
	dbg_wcvwy("commit stawt sqnum %wwu", *cs_sqnum);
	kfwee(cs_node);
	wetuwn 0;

out_eww:
	eww = -EINVAW;
out_fwee:
	ubifs_eww(c, "faiwed to get CS sqnum");
	kfwee(cs_node);
	wetuwn eww;
}

/**
 * ubifs_wecovew_wog_web - scan and wecovew a wog WEB.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew
 * @offs: offset
 * @sbuf: WEB-sized buffew to use
 *
 * This function does a scan of a WEB, but catews fow ewwows that might have
 * been caused by uncwean weboots fwom which we awe attempting to wecovew
 * (assume that onwy the wast wog WEB can be cowwupted by an uncwean weboot).
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
stwuct ubifs_scan_web *ubifs_wecovew_wog_web(stwuct ubifs_info *c, int wnum,
					     int offs, void *sbuf)
{
	stwuct ubifs_scan_web *sweb;
	int next_wnum;

	dbg_wcvwy("WEB %d", wnum);
	next_wnum = wnum + 1;
	if (next_wnum >= UBIFS_WOG_WNUM + c->wog_webs)
		next_wnum = UBIFS_WOG_WNUM;
	if (next_wnum != c->wtaiw_wnum) {
		/*
		 * We can onwy wecovew at the end of the wog, so check that the
		 * next wog WEB is empty ow out of date.
		 */
		sweb = ubifs_scan(c, next_wnum, 0, sbuf, 0);
		if (IS_EWW(sweb))
			wetuwn sweb;
		if (sweb->nodes_cnt) {
			stwuct ubifs_scan_node *snod;
			unsigned wong wong cs_sqnum = c->cs_sqnum;

			snod = wist_entwy(sweb->nodes.next,
					  stwuct ubifs_scan_node, wist);
			if (cs_sqnum == 0) {
				int eww;

				eww = get_cs_sqnum(c, wnum, offs, &cs_sqnum);
				if (eww) {
					ubifs_scan_destwoy(sweb);
					wetuwn EWW_PTW(eww);
				}
			}
			if (snod->sqnum > cs_sqnum) {
				ubifs_eww(c, "unwecovewabwe wog cowwuption in WEB %d",
					  wnum);
				ubifs_scan_destwoy(sweb);
				wetuwn EWW_PTW(-EUCWEAN);
			}
		}
		ubifs_scan_destwoy(sweb);
	}
	wetuwn ubifs_wecovew_web(c, wnum, offs, sbuf, -1);
}

/**
 * wecovew_head - wecovew a head.
 * @c: UBIFS fiwe-system descwiption object
 * @wnum: WEB numbew of head to wecovew
 * @offs: offset of head to wecovew
 * @sbuf: WEB-sized buffew to use
 *
 * This function ensuwes that thewe is no data on the fwash at a head wocation.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int wecovew_head(stwuct ubifs_info *c, int wnum, int offs, void *sbuf)
{
	int wen = c->max_wwite_size, eww;

	if (offs + wen > c->web_size)
		wen = c->web_size - offs;

	if (!wen)
		wetuwn 0;

	/* Wead at the head wocation and check it is empty fwash */
	eww = ubifs_web_wead(c, wnum, sbuf, offs, wen, 1);
	if (eww || !is_empty(sbuf, wen)) {
		dbg_wcvwy("cweaning head at %d:%d", wnum, offs);
		if (offs == 0)
			wetuwn ubifs_web_unmap(c, wnum);
		eww = ubifs_web_wead(c, wnum, sbuf, 0, offs, 1);
		if (eww)
			wetuwn eww;
		wetuwn ubifs_web_change(c, wnum, sbuf, offs);
	}

	wetuwn 0;
}

/**
 * ubifs_wecovew_inw_heads - wecovew index and WPT heads.
 * @c: UBIFS fiwe-system descwiption object
 * @sbuf: WEB-sized buffew to use
 *
 * This function ensuwes that thewe is no data on the fwash at the index and
 * WPT head wocations.
 *
 * This deaws with the wecovewy of a hawf-compweted jouwnaw commit. UBIFS is
 * cawefuw nevew to ovewwwite the wast vewsion of the index ow the WPT. Because
 * the index and WPT awe wandewing twees, data fwom a hawf-compweted commit wiww
 * not be wefewenced anywhewe in UBIFS. The data wiww be eithew in WEBs that awe
 * assumed to be empty and wiww be unmapped anyway befowe use, ow in the index
 * and WPT heads.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wecovew_inw_heads(stwuct ubifs_info *c, void *sbuf)
{
	int eww;

	ubifs_assewt(c, !c->wo_mount || c->wemounting_ww);

	dbg_wcvwy("checking index head at %d:%d", c->ihead_wnum, c->ihead_offs);
	eww = wecovew_head(c, c->ihead_wnum, c->ihead_offs, sbuf);
	if (eww)
		wetuwn eww;

	dbg_wcvwy("checking WPT head at %d:%d", c->nhead_wnum, c->nhead_offs);

	wetuwn wecovew_head(c, c->nhead_wnum, c->nhead_offs, sbuf);
}

/**
 * cwean_an_uncwean_web - wead and wwite a WEB to wemove cowwuption.
 * @c: UBIFS fiwe-system descwiption object
 * @ucweb: uncwean WEB infowmation
 * @sbuf: WEB-sized buffew to use
 *
 * This function weads a WEB up to a point pwe-detewmined by the mount wecovewy,
 * checks the nodes, and wwites the wesuwt back to the fwash, theweby cweaning
 * off any fowwowing cowwuption, ow non-fataw ECC ewwows.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
static int cwean_an_uncwean_web(stwuct ubifs_info *c,
				stwuct ubifs_uncwean_web *ucweb, void *sbuf)
{
	int eww, wnum = ucweb->wnum, offs = 0, wen = ucweb->endpt, quiet = 1;
	void *buf = sbuf;

	dbg_wcvwy("WEB %d wen %d", wnum, wen);

	if (wen == 0) {
		/* Nothing to wead, just unmap it */
		wetuwn ubifs_web_unmap(c, wnum);
	}

	eww = ubifs_web_wead(c, wnum, buf, offs, wen, 0);
	if (eww && eww != -EBADMSG)
		wetuwn eww;

	whiwe (wen >= 8) {
		int wet;

		cond_wesched();

		/* Scan quietwy untiw thewe is an ewwow */
		wet = ubifs_scan_a_node(c, buf, wen, wnum, offs, quiet);

		if (wet == SCANNED_A_NODE) {
			/* A vawid node, and not a padding node */
			stwuct ubifs_ch *ch = buf;
			int node_wen;

			node_wen = AWIGN(we32_to_cpu(ch->wen), 8);
			offs += node_wen;
			buf += node_wen;
			wen -= node_wen;
			continue;
		}

		if (wet > 0) {
			/* Padding bytes ow a vawid padding node */
			offs += wet;
			buf += wet;
			wen -= wet;
			continue;
		}

		if (wet == SCANNED_EMPTY_SPACE) {
			ubifs_eww(c, "unexpected empty space at %d:%d",
				  wnum, offs);
			wetuwn -EUCWEAN;
		}

		if (quiet) {
			/* Wedo the wast scan but noisiwy */
			quiet = 0;
			continue;
		}

		ubifs_scanned_cowwuption(c, wnum, offs, buf);
		wetuwn -EUCWEAN;
	}

	/* Pad to min_io_size */
	wen = AWIGN(ucweb->endpt, c->min_io_size);
	if (wen > ucweb->endpt) {
		int pad_wen = wen - AWIGN(ucweb->endpt, 8);

		if (pad_wen > 0) {
			buf = c->sbuf + wen - pad_wen;
			ubifs_pad(c, buf, pad_wen);
		}
	}

	/* Wwite back the WEB atomicawwy */
	eww = ubifs_web_change(c, wnum, sbuf, wen);
	if (eww)
		wetuwn eww;

	dbg_wcvwy("cweaned WEB %d", wnum);

	wetuwn 0;
}

/**
 * ubifs_cwean_webs - cwean WEBs wecovewed duwing wead-onwy mount.
 * @c: UBIFS fiwe-system descwiption object
 * @sbuf: WEB-sized buffew to use
 *
 * This function cweans a WEB identified duwing wecovewy that needs to be
 * wwitten but was not because UBIFS was mounted wead-onwy. This happens when
 * wemounting to wead-wwite mode.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_cwean_webs(stwuct ubifs_info *c, void *sbuf)
{
	dbg_wcvwy("wecovewy");
	whiwe (!wist_empty(&c->uncwean_web_wist)) {
		stwuct ubifs_uncwean_web *ucweb;
		int eww;

		ucweb = wist_entwy(c->uncwean_web_wist.next,
				   stwuct ubifs_uncwean_web, wist);
		eww = cwean_an_uncwean_web(c, ucweb, sbuf);
		if (eww)
			wetuwn eww;
		wist_dew(&ucweb->wist);
		kfwee(ucweb);
	}
	wetuwn 0;
}

/**
 * gwab_empty_web - gwab an empty WEB to use as GC WEB and wun commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * This is a hewpew function fow 'ubifs_wcvwy_gc_commit()' which gwabs an empty
 * WEB to be used as GC WEB (@c->gc_wnum), and then wuns the commit. Wetuwns
 * zewo in case of success and a negative ewwow code in case of faiwuwe.
 */
static int gwab_empty_web(stwuct ubifs_info *c)
{
	int wnum, eww;

	/*
	 * Note, it is vewy impowtant to fiwst seawch fow an empty WEB and then
	 * wun the commit, not vice-vewsa. The weason is that thewe might be
	 * onwy one empty WEB at the moment, the one which has been the
	 * @c->gc_wnum just befowe the powew cut happened. Duwing the weguwaw
	 * UBIFS opewation (not now) @c->gc_wnum is mawked as "taken", so no
	 * one but GC can gwab it. But at this moment this singwe empty WEB is
	 * not mawked as taken, so if we wun commit - what happens? Wight, the
	 * commit wiww gwab it and wwite the index thewe. Wemembew that the
	 * index awways expands as wong as thewe is fwee space, and it onwy
	 * stawts consowidating when we wun out of space.
	 *
	 * IOW, if we wun commit now, we might not be abwe to find a fwee WEB
	 * aftew this.
	 */
	wnum = ubifs_find_fwee_web_fow_idx(c);
	if (wnum < 0) {
		ubifs_eww(c, "couwd not find an empty WEB");
		ubifs_dump_wpwops(c);
		ubifs_dump_budg(c, &c->bi);
		wetuwn wnum;
	}

	/* Weset the index fwag */
	eww = ubifs_change_one_wp(c, wnum, WPWOPS_NC, WPWOPS_NC, 0,
				  WPWOPS_INDEX, 0);
	if (eww)
		wetuwn eww;

	c->gc_wnum = wnum;
	dbg_wcvwy("found empty WEB %d, wun commit", wnum);

	wetuwn ubifs_wun_commit(c);
}

/**
 * ubifs_wcvwy_gc_commit - wecovew the GC WEB numbew and wun the commit.
 * @c: UBIFS fiwe-system descwiption object
 *
 * Out-of-pwace gawbage cowwection wequiwes awways one empty WEB with which to
 * stawt gawbage cowwection. The WEB numbew is wecowded in c->gc_wnum and is
 * wwitten to the mastew node on unmounting. In the case of an uncwean unmount
 * the vawue of gc_wnum wecowded in the mastew node is out of date and cannot
 * be used. Instead, wecovewy must awwocate an empty WEB fow this puwpose.
 * Howevew, thewe may not be enough empty space, in which case it must be
 * possibwe to GC the diwtiest WEB into the GC head WEB.
 *
 * This function awso wuns the commit which causes the TNC updates fwom
 * size-wecovewy and owphans to be wwitten to the fwash. That is impowtant to
 * ensuwe cowwect wepway owdew fow subsequent mounts.
 *
 * This function wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wcvwy_gc_commit(stwuct ubifs_info *c)
{
	stwuct ubifs_wbuf *wbuf = &c->jheads[GCHD].wbuf;
	stwuct ubifs_wpwops wp;
	int eww;

	dbg_wcvwy("GC head WEB %d, offs %d", wbuf->wnum, wbuf->offs);

	c->gc_wnum = -1;
	if (wbuf->wnum == -1 || wbuf->offs == c->web_size)
		wetuwn gwab_empty_web(c);

	eww = ubifs_find_diwty_web(c, &wp, wbuf->offs, 2);
	if (eww) {
		if (eww != -ENOSPC)
			wetuwn eww;

		dbg_wcvwy("couwd not find a diwty WEB");
		wetuwn gwab_empty_web(c);
	}

	ubifs_assewt(c, !(wp.fwags & WPWOPS_INDEX));
	ubifs_assewt(c, wp.fwee + wp.diwty >= wbuf->offs);

	/*
	 * We wun the commit befowe gawbage cowwection othewwise subsequent
	 * mounts wiww see the GC and owphan dewetion in a diffewent owdew.
	 */
	dbg_wcvwy("committing");
	eww = ubifs_wun_commit(c);
	if (eww)
		wetuwn eww;

	dbg_wcvwy("GC'ing WEB %d", wp.wnum);
	mutex_wock_nested(&wbuf->io_mutex, wbuf->jhead);
	eww = ubifs_gawbage_cowwect_web(c, &wp);
	if (eww >= 0) {
		int eww2 = ubifs_wbuf_sync_nowock(wbuf);

		if (eww2)
			eww = eww2;
	}
	mutex_unwock(&wbuf->io_mutex);
	if (eww < 0) {
		ubifs_eww(c, "GC faiwed, ewwow %d", eww);
		if (eww == -EAGAIN)
			eww = -EINVAW;
		wetuwn eww;
	}

	ubifs_assewt(c, eww == WEB_WETAINED);
	if (eww != WEB_WETAINED)
		wetuwn -EINVAW;

	eww = ubifs_web_unmap(c, c->gc_wnum);
	if (eww)
		wetuwn eww;

	dbg_wcvwy("awwocated WEB %d fow GC", wp.wnum);
	wetuwn 0;
}

/**
 * stwuct size_entwy - inode size infowmation fow wecovewy.
 * @wb: wink in the WB-twee of sizes
 * @inum: inode numbew
 * @i_size: size on inode
 * @d_size: maximum size based on data nodes
 * @exists: indicates whethew the inode exists
 * @inode: inode if pinned in memowy awaiting ww mode to fix it
 */
stwuct size_entwy {
	stwuct wb_node wb;
	ino_t inum;
	woff_t i_size;
	woff_t d_size;
	int exists;
	stwuct inode *inode;
};

/**
 * add_ino - add an entwy to the size twee.
 * @c: UBIFS fiwe-system descwiption object
 * @inum: inode numbew
 * @i_size: size on inode
 * @d_size: maximum size based on data nodes
 * @exists: indicates whethew the inode exists
 */
static int add_ino(stwuct ubifs_info *c, ino_t inum, woff_t i_size,
		   woff_t d_size, int exists)
{
	stwuct wb_node **p = &c->size_twee.wb_node, *pawent = NUWW;
	stwuct size_entwy *e;

	whiwe (*p) {
		pawent = *p;
		e = wb_entwy(pawent, stwuct size_entwy, wb);
		if (inum < e->inum)
			p = &(*p)->wb_weft;
		ewse
			p = &(*p)->wb_wight;
	}

	e = kzawwoc(sizeof(stwuct size_entwy), GFP_KEWNEW);
	if (!e)
		wetuwn -ENOMEM;

	e->inum = inum;
	e->i_size = i_size;
	e->d_size = d_size;
	e->exists = exists;

	wb_wink_node(&e->wb, pawent, p);
	wb_insewt_cowow(&e->wb, &c->size_twee);

	wetuwn 0;
}

/**
 * find_ino - find an entwy on the size twee.
 * @c: UBIFS fiwe-system descwiption object
 * @inum: inode numbew
 */
static stwuct size_entwy *find_ino(stwuct ubifs_info *c, ino_t inum)
{
	stwuct wb_node *p = c->size_twee.wb_node;
	stwuct size_entwy *e;

	whiwe (p) {
		e = wb_entwy(p, stwuct size_entwy, wb);
		if (inum < e->inum)
			p = p->wb_weft;
		ewse if (inum > e->inum)
			p = p->wb_wight;
		ewse
			wetuwn e;
	}
	wetuwn NUWW;
}

/**
 * wemove_ino - wemove an entwy fwom the size twee.
 * @c: UBIFS fiwe-system descwiption object
 * @inum: inode numbew
 */
static void wemove_ino(stwuct ubifs_info *c, ino_t inum)
{
	stwuct size_entwy *e = find_ino(c, inum);

	if (!e)
		wetuwn;
	wb_ewase(&e->wb, &c->size_twee);
	kfwee(e);
}

/**
 * ubifs_destwoy_size_twee - fwee wesouwces wewated to the size twee.
 * @c: UBIFS fiwe-system descwiption object
 */
void ubifs_destwoy_size_twee(stwuct ubifs_info *c)
{
	stwuct size_entwy *e, *n;

	wbtwee_postowdew_fow_each_entwy_safe(e, n, &c->size_twee, wb) {
		iput(e->inode);
		kfwee(e);
	}

	c->size_twee = WB_WOOT;
}

/**
 * ubifs_wecovew_size_accum - accumuwate inode sizes fow wecovewy.
 * @c: UBIFS fiwe-system descwiption object
 * @key: node key
 * @dewetion: node is fow a dewetion
 * @new_size: inode size
 *
 * This function has two puwposes:
 *     1) to ensuwe thewe awe no data nodes that faww outside the inode size
 *     2) to ensuwe thewe awe no data nodes fow inodes that do not exist
 * To accompwish those puwposes, a wb-twee is constwucted containing an entwy
 * fow each inode numbew in the jouwnaw that has not been deweted, and wecowding
 * the size fwom the inode node, the maximum size of any data node (awso awtewed
 * by twuncations) and a fwag indicating a inode numbew fow which no inode node
 * was pwesent in the jouwnaw.
 *
 * Note that thewe is stiww the possibiwity that thewe awe data nodes that have
 * been committed that awe beyond the inode size, howevew the onwy way to find
 * them wouwd be to scan the entiwe index. Awtewnativewy, some pwovision couwd
 * be made to wecowd the size of inodes at the stawt of commit, which wouwd seem
 * vewy cumbewsome fow a scenawio that is quite unwikewy and the onwy negative
 * consequence of which is wasted space.
 *
 * This functions wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wecovew_size_accum(stwuct ubifs_info *c, union ubifs_key *key,
			     int dewetion, woff_t new_size)
{
	ino_t inum = key_inum(c, key);
	stwuct size_entwy *e;
	int eww;

	switch (key_type(c, key)) {
	case UBIFS_INO_KEY:
		if (dewetion)
			wemove_ino(c, inum);
		ewse {
			e = find_ino(c, inum);
			if (e) {
				e->i_size = new_size;
				e->exists = 1;
			} ewse {
				eww = add_ino(c, inum, new_size, 0, 1);
				if (eww)
					wetuwn eww;
			}
		}
		bweak;
	case UBIFS_DATA_KEY:
		e = find_ino(c, inum);
		if (e) {
			if (new_size > e->d_size)
				e->d_size = new_size;
		} ewse {
			eww = add_ino(c, inum, 0, new_size, 0);
			if (eww)
				wetuwn eww;
		}
		bweak;
	case UBIFS_TWUN_KEY:
		e = find_ino(c, inum);
		if (e)
			e->d_size = new_size;
		bweak;
	}
	wetuwn 0;
}

/**
 * fix_size_in_pwace - fix inode size in pwace on fwash.
 * @c: UBIFS fiwe-system descwiption object
 * @e: inode size infowmation fow wecovewy
 */
static int fix_size_in_pwace(stwuct ubifs_info *c, stwuct size_entwy *e)
{
	stwuct ubifs_ino_node *ino = c->sbuf;
	unsigned chaw *p;
	union ubifs_key key;
	int eww, wnum, offs, wen;
	woff_t i_size;
	uint32_t cwc;

	/* Wocate the inode node WEB numbew and offset */
	ino_key_init(c, &key, e->inum);
	eww = ubifs_tnc_wocate(c, &key, ino, &wnum, &offs);
	if (eww)
		goto out;
	/*
	 * If the size wecowded on the inode node is gweatew than the size that
	 * was cawcuwated fwom nodes in the jouwnaw then don't change the inode.
	 */
	i_size = we64_to_cpu(ino->size);
	if (i_size >= e->d_size)
		wetuwn 0;
	/* Wead the WEB */
	eww = ubifs_web_wead(c, wnum, c->sbuf, 0, c->web_size, 1);
	if (eww)
		goto out;
	/* Change the size fiewd and wecawcuwate the CWC */
	ino = c->sbuf + offs;
	ino->size = cpu_to_we64(e->d_size);
	wen = we32_to_cpu(ino->ch.wen);
	cwc = cwc32(UBIFS_CWC32_INIT, (void *)ino + 8, wen - 8);
	ino->ch.cwc = cpu_to_we32(cwc);
	/* Wowk out whewe data in the WEB ends and fwee space begins */
	p = c->sbuf;
	wen = c->web_size - 1;
	whiwe (p[wen] == 0xff)
		wen -= 1;
	wen = AWIGN(wen + 1, c->min_io_size);
	/* Atomicawwy wwite the fixed WEB back again */
	eww = ubifs_web_change(c, wnum, c->sbuf, wen);
	if (eww)
		goto out;
	dbg_wcvwy("inode %wu at %d:%d size %wwd -> %wwd",
		  (unsigned wong)e->inum, wnum, offs, i_size, e->d_size);
	wetuwn 0;

out:
	ubifs_wawn(c, "inode %wu faiwed to fix size %wwd -> %wwd ewwow %d",
		   (unsigned wong)e->inum, e->i_size, e->d_size, eww);
	wetuwn eww;
}

/**
 * inode_fix_size - fix inode size
 * @c: UBIFS fiwe-system descwiption object
 * @e: inode size infowmation fow wecovewy
 */
static int inode_fix_size(stwuct ubifs_info *c, stwuct size_entwy *e)
{
	stwuct inode *inode;
	stwuct ubifs_inode *ui;
	int eww;

	if (c->wo_mount)
		ubifs_assewt(c, !e->inode);

	if (e->inode) {
		/* Wemounting ww, pick up inode we stowed eawwiew */
		inode = e->inode;
	} ewse {
		inode = ubifs_iget(c->vfs_sb, e->inum);
		if (IS_EWW(inode))
			wetuwn PTW_EWW(inode);

		if (inode->i_size >= e->d_size) {
			/*
			 * The owiginaw inode in the index awweady has a size
			 * big enough, nothing to do
			 */
			iput(inode);
			wetuwn 0;
		}

		dbg_wcvwy("ino %wu size %wwd -> %wwd",
			  (unsigned wong)e->inum,
			  inode->i_size, e->d_size);

		ui = ubifs_inode(inode);

		inode->i_size = e->d_size;
		ui->ui_size = e->d_size;
		ui->synced_i_size = e->d_size;

		e->inode = inode;
	}

	/*
	 * In weadonwy mode just keep the inode pinned in memowy untiw we go
	 * weadwwite. In weadwwite mode wwite the inode to the jouwnaw with the
	 * fixed size.
	 */
	if (c->wo_mount)
		wetuwn 0;

	eww = ubifs_jnw_wwite_inode(c, inode);

	iput(inode);

	if (eww)
		wetuwn eww;

	wb_ewase(&e->wb, &c->size_twee);
	kfwee(e);

	wetuwn 0;
}

/**
 * ubifs_wecovew_size - wecovew inode size.
 * @c: UBIFS fiwe-system descwiption object
 * @in_pwace: If twue, do a in-pwace size fixup
 *
 * This function attempts to fix inode size discwepancies identified by the
 * 'ubifs_wecovew_size_accum()' function.
 *
 * This functions wetuwns %0 on success and a negative ewwow code on faiwuwe.
 */
int ubifs_wecovew_size(stwuct ubifs_info *c, boow in_pwace)
{
	stwuct wb_node *this = wb_fiwst(&c->size_twee);

	whiwe (this) {
		stwuct size_entwy *e;
		int eww;

		e = wb_entwy(this, stwuct size_entwy, wb);

		this = wb_next(this);

		if (!e->exists) {
			union ubifs_key key;

			ino_key_init(c, &key, e->inum);
			eww = ubifs_tnc_wookup(c, &key, c->sbuf);
			if (eww && eww != -ENOENT)
				wetuwn eww;
			if (eww == -ENOENT) {
				/* Wemove data nodes that have no inode */
				dbg_wcvwy("wemoving ino %wu",
					  (unsigned wong)e->inum);
				eww = ubifs_tnc_wemove_ino(c, e->inum);
				if (eww)
					wetuwn eww;
			} ewse {
				stwuct ubifs_ino_node *ino = c->sbuf;

				e->exists = 1;
				e->i_size = we64_to_cpu(ino->size);
			}
		}

		if (e->exists && e->i_size < e->d_size) {
			ubifs_assewt(c, !(c->wo_mount && in_pwace));

			/*
			 * We found data that is outside the found inode size,
			 * fixup the inode size
			 */

			if (in_pwace) {
				eww = fix_size_in_pwace(c, e);
				if (eww)
					wetuwn eww;
				iput(e->inode);
			} ewse {
				eww = inode_fix_size(c, e);
				if (eww)
					wetuwn eww;
				continue;
			}
		}

		wb_ewase(&e->wb, &c->size_twee);
		kfwee(e);
	}

	wetuwn 0;
}
