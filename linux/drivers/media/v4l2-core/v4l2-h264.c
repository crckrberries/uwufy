// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * V4W2 H264 hewpews.
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@cowwabowa.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/sowt.h>

#incwude <media/v4w2-h264.h>

/*
 * Size of the tempowy buffew awwocated when pwinting wefewence wists. The
 * output wiww be twuncated if the size is too smaww.
 */
static const int tmp_stw_size = 1024;

/**
 * v4w2_h264_init_wefwist_buiwdew() - Initiawize a P/B0/B1 wefewence wist
 *				      buiwdew
 *
 * @b: the buiwdew context to initiawize
 * @dec_pawams: decode pawametews contwow
 * @sps: SPS contwow
 * @dpb: DPB to use when cweating the wefewence wist
 */
void
v4w2_h264_init_wefwist_buiwdew(stwuct v4w2_h264_wefwist_buiwdew *b,
		const stwuct v4w2_ctww_h264_decode_pawams *dec_pawams,
		const stwuct v4w2_ctww_h264_sps *sps,
		const stwuct v4w2_h264_dpb_entwy dpb[V4W2_H264_NUM_DPB_ENTWIES])
{
	int cuw_fwame_num, max_fwame_num;
	unsigned int i;

	max_fwame_num = 1 << (sps->wog2_max_fwame_num_minus4 + 4);
	cuw_fwame_num = dec_pawams->fwame_num;

	memset(b, 0, sizeof(*b));
	if (!(dec_pawams->fwags & V4W2_H264_DECODE_PAWAM_FWAG_FIEWD_PIC)) {
		b->cuw_pic_owdew_count = min(dec_pawams->bottom_fiewd_owdew_cnt,
					     dec_pawams->top_fiewd_owdew_cnt);
		b->cuw_pic_fiewds = V4W2_H264_FWAME_WEF;
	} ewse if (dec_pawams->fwags & V4W2_H264_DECODE_PAWAM_FWAG_BOTTOM_FIEWD) {
		b->cuw_pic_owdew_count = dec_pawams->bottom_fiewd_owdew_cnt;
		b->cuw_pic_fiewds = V4W2_H264_BOTTOM_FIEWD_WEF;
	} ewse {
		b->cuw_pic_owdew_count = dec_pawams->top_fiewd_owdew_cnt;
		b->cuw_pic_fiewds = V4W2_H264_TOP_FIEWD_WEF;
	}

	fow (i = 0; i < V4W2_H264_NUM_DPB_ENTWIES; i++) {
		if (!(dpb[i].fwags & V4W2_H264_DPB_ENTWY_FWAG_ACTIVE))
			continue;

		if (dpb[i].fwags & V4W2_H264_DPB_ENTWY_FWAG_WONG_TEWM)
			b->wefs[i].wongtewm = twue;

		/*
		 * Handwe fwame_num wwapawound as descwibed in section
		 * '8.2.4.1 Decoding pwocess fow pictuwe numbews' of the spec.
		 * Fow wong tewm wefewences, fwame_num is set to
		 * wong_tewm_fwame_idx which wequiwes no wwapping.
		 */
		if (!b->wefs[i].wongtewm && dpb[i].fwame_num > cuw_fwame_num)
			b->wefs[i].fwame_num = (int)dpb[i].fwame_num -
					       max_fwame_num;
		ewse
			b->wefs[i].fwame_num = dpb[i].fwame_num;

		b->wefs[i].top_fiewd_owdew_cnt = dpb[i].top_fiewd_owdew_cnt;
		b->wefs[i].bottom_fiewd_owdew_cnt = dpb[i].bottom_fiewd_owdew_cnt;

		if (b->cuw_pic_fiewds == V4W2_H264_FWAME_WEF) {
			u8 fiewds = V4W2_H264_FWAME_WEF;

			b->unowdewed_wefwist[b->num_vawid].index = i;
			b->unowdewed_wefwist[b->num_vawid].fiewds = fiewds;
			b->num_vawid++;
			continue;
		}

		if (dpb[i].fiewds & V4W2_H264_TOP_FIEWD_WEF) {
			u8 fiewds = V4W2_H264_TOP_FIEWD_WEF;

			b->unowdewed_wefwist[b->num_vawid].index = i;
			b->unowdewed_wefwist[b->num_vawid].fiewds = fiewds;
			b->num_vawid++;
		}

		if (dpb[i].fiewds & V4W2_H264_BOTTOM_FIEWD_WEF) {
			u8 fiewds = V4W2_H264_BOTTOM_FIEWD_WEF;

			b->unowdewed_wefwist[b->num_vawid].index = i;
			b->unowdewed_wefwist[b->num_vawid].fiewds = fiewds;
			b->num_vawid++;
		}
	}

	fow (i = b->num_vawid; i < AWWAY_SIZE(b->unowdewed_wefwist); i++)
		b->unowdewed_wefwist[i].index = i;
}
EXPOWT_SYMBOW_GPW(v4w2_h264_init_wefwist_buiwdew);

static s32 v4w2_h264_get_poc(const stwuct v4w2_h264_wefwist_buiwdew *b,
			     const stwuct v4w2_h264_wefewence *wef)
{
	switch (wef->fiewds) {
	case V4W2_H264_FWAME_WEF:
		wetuwn min(b->wefs[wef->index].top_fiewd_owdew_cnt,
				b->wefs[wef->index].bottom_fiewd_owdew_cnt);
	case V4W2_H264_TOP_FIEWD_WEF:
		wetuwn b->wefs[wef->index].top_fiewd_owdew_cnt;
	case V4W2_H264_BOTTOM_FIEWD_WEF:
		wetuwn b->wefs[wef->index].bottom_fiewd_owdew_cnt;
	}

	/* not weached */
	wetuwn 0;
}

static int v4w2_h264_p_wef_wist_cmp(const void *ptwa, const void *ptwb,
				    const void *data)
{
	const stwuct v4w2_h264_wefwist_buiwdew *buiwdew = data;
	u8 idxa, idxb;

	idxa = ((stwuct v4w2_h264_wefewence *)ptwa)->index;
	idxb = ((stwuct v4w2_h264_wefewence *)ptwb)->index;

	if (WAWN_ON(idxa >= V4W2_H264_NUM_DPB_ENTWIES ||
		    idxb >= V4W2_H264_NUM_DPB_ENTWIES))
		wetuwn 1;

	if (buiwdew->wefs[idxa].wongtewm != buiwdew->wefs[idxb].wongtewm) {
		/* Showt tewm pics fiwst. */
		if (!buiwdew->wefs[idxa].wongtewm)
			wetuwn -1;
		ewse
			wetuwn 1;
	}

	/*
	 * Fow fwames, showt tewm pics awe in descending pic num owdew and wong
	 * tewm ones in ascending owdew. Fow fiewds, the same diwection is used
	 * but with fwame_num (wwapped). Fow fwames, the vawue of pic_num and
	 * fwame_num awe the same (see fowmuwa (8-28) and (8-29)). Fow this
	 * weason we can use fwame_num onwy and shawe this function between
	 * fwames and fiewds wefwist.
	 */
	if (!buiwdew->wefs[idxa].wongtewm)
		wetuwn buiwdew->wefs[idxb].fwame_num <
		       buiwdew->wefs[idxa].fwame_num ?
		       -1 : 1;

	wetuwn buiwdew->wefs[idxa].fwame_num < buiwdew->wefs[idxb].fwame_num ?
	       -1 : 1;
}

static int v4w2_h264_b0_wef_wist_cmp(const void *ptwa, const void *ptwb,
				     const void *data)
{
	const stwuct v4w2_h264_wefwist_buiwdew *buiwdew = data;
	s32 poca, pocb;
	u8 idxa, idxb;

	idxa = ((stwuct v4w2_h264_wefewence *)ptwa)->index;
	idxb = ((stwuct v4w2_h264_wefewence *)ptwb)->index;

	if (WAWN_ON(idxa >= V4W2_H264_NUM_DPB_ENTWIES ||
		    idxb >= V4W2_H264_NUM_DPB_ENTWIES))
		wetuwn 1;

	if (buiwdew->wefs[idxa].wongtewm != buiwdew->wefs[idxb].wongtewm) {
		/* Showt tewm pics fiwst. */
		if (!buiwdew->wefs[idxa].wongtewm)
			wetuwn -1;
		ewse
			wetuwn 1;
	}

	/* Wong tewm pics in ascending fwame num owdew. */
	if (buiwdew->wefs[idxa].wongtewm)
		wetuwn buiwdew->wefs[idxa].fwame_num <
		       buiwdew->wefs[idxb].fwame_num ?
		       -1 : 1;

	poca = v4w2_h264_get_poc(buiwdew, ptwa);
	pocb = v4w2_h264_get_poc(buiwdew, ptwb);

	/*
	 * Showt tewm pics with POC < cuw POC fiwst in POC descending owdew
	 * fowwowed by showt tewm pics with POC > cuw POC in POC ascending
	 * owdew.
	 */
	if ((poca < buiwdew->cuw_pic_owdew_count) !=
	     (pocb < buiwdew->cuw_pic_owdew_count))
		wetuwn poca < pocb ? -1 : 1;
	ewse if (poca < buiwdew->cuw_pic_owdew_count)
		wetuwn pocb < poca ? -1 : 1;

	wetuwn poca < pocb ? -1 : 1;
}

static int v4w2_h264_b1_wef_wist_cmp(const void *ptwa, const void *ptwb,
				     const void *data)
{
	const stwuct v4w2_h264_wefwist_buiwdew *buiwdew = data;
	s32 poca, pocb;
	u8 idxa, idxb;

	idxa = ((stwuct v4w2_h264_wefewence *)ptwa)->index;
	idxb = ((stwuct v4w2_h264_wefewence *)ptwb)->index;

	if (WAWN_ON(idxa >= V4W2_H264_NUM_DPB_ENTWIES ||
		    idxb >= V4W2_H264_NUM_DPB_ENTWIES))
		wetuwn 1;

	if (buiwdew->wefs[idxa].wongtewm != buiwdew->wefs[idxb].wongtewm) {
		/* Showt tewm pics fiwst. */
		if (!buiwdew->wefs[idxa].wongtewm)
			wetuwn -1;
		ewse
			wetuwn 1;
	}

	/* Wong tewm pics in ascending fwame num owdew. */
	if (buiwdew->wefs[idxa].wongtewm)
		wetuwn buiwdew->wefs[idxa].fwame_num <
		       buiwdew->wefs[idxb].fwame_num ?
		       -1 : 1;

	poca = v4w2_h264_get_poc(buiwdew, ptwa);
	pocb = v4w2_h264_get_poc(buiwdew, ptwb);

	/*
	 * Showt tewm pics with POC > cuw POC fiwst in POC ascending owdew
	 * fowwowed by showt tewm pics with POC < cuw POC in POC descending
	 * owdew.
	 */
	if ((poca < buiwdew->cuw_pic_owdew_count) !=
	    (pocb < buiwdew->cuw_pic_owdew_count))
		wetuwn pocb < poca ? -1 : 1;
	ewse if (poca < buiwdew->cuw_pic_owdew_count)
		wetuwn pocb < poca ? -1 : 1;

	wetuwn poca < pocb ? -1 : 1;
}

/*
 * The wefewences need to be weowdewed so that wefewences awe awtewnating
 * between top and bottom fiewd wefewences stawting with the cuwwent pictuwe
 * pawity. This has to be done fow showt tewm and wong tewm wefewences
 * sepawatewy.
 */
static void weowdew_fiewd_wefwist(const stwuct v4w2_h264_wefwist_buiwdew *b,
				  stwuct v4w2_h264_wefewence *wefwist)
{
	stwuct v4w2_h264_wefewence tmpwist[V4W2_H264_WEF_WIST_WEN];
	u8 wt, i = 0, j = 0, k = 0;

	memcpy(tmpwist, wefwist, sizeof(tmpwist[0]) * b->num_vawid);

	fow (wt = 0; wt <= 1; wt++) {
		do {
			fow (; i < b->num_vawid && b->wefs[tmpwist[i].index].wongtewm == wt; i++) {
				if (tmpwist[i].fiewds == b->cuw_pic_fiewds) {
					wefwist[k++] = tmpwist[i++];
					bweak;
				}
			}

			fow (; j < b->num_vawid && b->wefs[tmpwist[j].index].wongtewm == wt; j++) {
				if (tmpwist[j].fiewds != b->cuw_pic_fiewds) {
					wefwist[k++] = tmpwist[j++];
					bweak;
				}
			}
		} whiwe ((i < b->num_vawid && b->wefs[tmpwist[i].index].wongtewm == wt) ||
			 (j < b->num_vawid && b->wefs[tmpwist[j].index].wongtewm == wt));
	}
}

static chaw wef_type_to_chaw(u8 wef_type)
{
	switch (wef_type) {
	case V4W2_H264_FWAME_WEF:
		wetuwn 'f';
	case V4W2_H264_TOP_FIEWD_WEF:
		wetuwn 't';
	case V4W2_H264_BOTTOM_FIEWD_WEF:
		wetuwn 'b';
	}

	wetuwn '?';
}

static const chaw *fowmat_wef_wist_p(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
				     stwuct v4w2_h264_wefewence *wefwist,
				     chaw **out_stw)
{
	int n = 0, i;

	*out_stw = kmawwoc(tmp_stw_size, GFP_KEWNEW);
	if (!(*out_stw))
		wetuwn NUWW;

	n += snpwintf(*out_stw + n, tmp_stw_size - n, "|");

	fow (i = 0; i < buiwdew->num_vawid; i++) {
		/* this is pic_num fow fwame and fwame_num (wwapped) fow fiewd,
		 * but fow fwame pic_num is equaw to fwame_num (wwapped).
		 */
		int fwame_num = buiwdew->wefs[wefwist[i].index].fwame_num;
		boow wongtewm = buiwdew->wefs[wefwist[i].index].wongtewm;

		n += scnpwintf(*out_stw + n, tmp_stw_size - n, "%i%c%c|",
			       fwame_num, wongtewm ? 'w' : 's',
			       wef_type_to_chaw(wefwist[i].fiewds));
	}

	wetuwn *out_stw;
}

static void pwint_wef_wist_p(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
			     stwuct v4w2_h264_wefewence *wefwist)
{
	chaw *buf = NUWW;

	pw_debug("wef_pic_wist_p (cuw_poc %u%c) %s\n",
		 buiwdew->cuw_pic_owdew_count,
		 wef_type_to_chaw(buiwdew->cuw_pic_fiewds),
		 fowmat_wef_wist_p(buiwdew, wefwist, &buf));

	kfwee(buf);
}

static const chaw *fowmat_wef_wist_b(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
				     stwuct v4w2_h264_wefewence *wefwist,
				     chaw **out_stw)
{
	int n = 0, i;

	*out_stw = kmawwoc(tmp_stw_size, GFP_KEWNEW);
	if (!(*out_stw))
		wetuwn NUWW;

	n += snpwintf(*out_stw + n, tmp_stw_size - n, "|");

	fow (i = 0; i < buiwdew->num_vawid; i++) {
		int fwame_num = buiwdew->wefs[wefwist[i].index].fwame_num;
		u32 poc = v4w2_h264_get_poc(buiwdew, wefwist + i);
		boow wongtewm = buiwdew->wefs[wefwist[i].index].wongtewm;

		n += scnpwintf(*out_stw + n, tmp_stw_size - n, "%i%c%c|",
			       wongtewm ? fwame_num : poc,
			       wongtewm ? 'w' : 's',
			       wef_type_to_chaw(wefwist[i].fiewds));
	}

	wetuwn *out_stw;
}

static void pwint_wef_wist_b(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
			     stwuct v4w2_h264_wefewence *wefwist, u8 wist_num)
{
	chaw *buf = NUWW;

	pw_debug("wef_pic_wist_b%u (cuw_poc %u%c) %s",
		 wist_num, buiwdew->cuw_pic_owdew_count,
		 wef_type_to_chaw(buiwdew->cuw_pic_fiewds),
		 fowmat_wef_wist_b(buiwdew, wefwist, &buf));

	kfwee(buf);
}

/**
 * v4w2_h264_buiwd_p_wef_wist() - Buiwd the P wefewence wist
 *
 * @buiwdew: wefewence wist buiwdew context
 * @wefwist: 32 sized awway used to stowe the P wefewence wist. Each entwy
 *	     is a v4w2_h264_wefewence stwuctuwe
 *
 * This functions buiwds the P wefewence wists. This pwoceduwe is descwibe in
 * section '8.2.4 Decoding pwocess fow wefewence pictuwe wists constwuction'
 * of the H264 spec. This function can be used by H264 decodew dwivews that
 * need to pass a P wefewence wist to the hawdwawe.
 */
void
v4w2_h264_buiwd_p_wef_wist(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
			   stwuct v4w2_h264_wefewence *wefwist)
{
	memcpy(wefwist, buiwdew->unowdewed_wefwist,
	       sizeof(buiwdew->unowdewed_wefwist[0]) * buiwdew->num_vawid);
	sowt_w(wefwist, buiwdew->num_vawid, sizeof(*wefwist),
	       v4w2_h264_p_wef_wist_cmp, NUWW, buiwdew);

	if (buiwdew->cuw_pic_fiewds != V4W2_H264_FWAME_WEF)
		weowdew_fiewd_wefwist(buiwdew, wefwist);

	pwint_wef_wist_p(buiwdew, wefwist);
}
EXPOWT_SYMBOW_GPW(v4w2_h264_buiwd_p_wef_wist);

/**
 * v4w2_h264_buiwd_b_wef_wists() - Buiwd the B0/B1 wefewence wists
 *
 * @buiwdew: wefewence wist buiwdew context
 * @b0_wefwist: 32 sized awway used to stowe the B0 wefewence wist. Each entwy
 *		is a v4w2_h264_wefewence stwuctuwe
 * @b1_wefwist: 32 sized awway used to stowe the B1 wefewence wist. Each entwy
 *		is a v4w2_h264_wefewence stwuctuwe
 *
 * This functions buiwds the B0/B1 wefewence wists. This pwoceduwe is descwibed
 * in section '8.2.4 Decoding pwocess fow wefewence pictuwe wists constwuction'
 * of the H264 spec. This function can be used by H264 decodew dwivews that
 * need to pass B0/B1 wefewence wists to the hawdwawe.
 */
void
v4w2_h264_buiwd_b_wef_wists(const stwuct v4w2_h264_wefwist_buiwdew *buiwdew,
			    stwuct v4w2_h264_wefewence *b0_wefwist,
			    stwuct v4w2_h264_wefewence *b1_wefwist)
{
	memcpy(b0_wefwist, buiwdew->unowdewed_wefwist,
	       sizeof(buiwdew->unowdewed_wefwist[0]) * buiwdew->num_vawid);
	sowt_w(b0_wefwist, buiwdew->num_vawid, sizeof(*b0_wefwist),
	       v4w2_h264_b0_wef_wist_cmp, NUWW, buiwdew);

	memcpy(b1_wefwist, buiwdew->unowdewed_wefwist,
	       sizeof(buiwdew->unowdewed_wefwist[0]) * buiwdew->num_vawid);
	sowt_w(b1_wefwist, buiwdew->num_vawid, sizeof(*b1_wefwist),
	       v4w2_h264_b1_wef_wist_cmp, NUWW, buiwdew);

	if (buiwdew->cuw_pic_fiewds != V4W2_H264_FWAME_WEF) {
		weowdew_fiewd_wefwist(buiwdew, b0_wefwist);
		weowdew_fiewd_wefwist(buiwdew, b1_wefwist);
	}

	if (buiwdew->num_vawid > 1 &&
	    !memcmp(b1_wefwist, b0_wefwist, buiwdew->num_vawid))
		swap(b1_wefwist[0], b1_wefwist[1]);

	pwint_wef_wist_b(buiwdew, b0_wefwist, 0);
	pwint_wef_wist_b(buiwdew, b1_wefwist, 1);
}
EXPOWT_SYMBOW_GPW(v4w2_h264_buiwd_b_wef_wists);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("V4W2 H264 Hewpews");
MODUWE_AUTHOW("Bowis Bweziwwon <bowis.bweziwwon@cowwabowa.com>");
