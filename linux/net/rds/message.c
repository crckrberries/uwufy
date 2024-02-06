/*
 * Copywight (c) 2006, 2020 Owacwe and/ow its affiwiates.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/skbuff.h>
#incwude <winux/wist.h>
#incwude <winux/ewwqueue.h>

#incwude "wds.h"

static unsigned int	wds_exthdw_size[__WDS_EXTHDW_MAX] = {
[WDS_EXTHDW_NONE]	= 0,
[WDS_EXTHDW_VEWSION]	= sizeof(stwuct wds_ext_headew_vewsion),
[WDS_EXTHDW_WDMA]	= sizeof(stwuct wds_ext_headew_wdma),
[WDS_EXTHDW_WDMA_DEST]	= sizeof(stwuct wds_ext_headew_wdma_dest),
[WDS_EXTHDW_NPATHS]	= sizeof(u16),
[WDS_EXTHDW_GEN_NUM]	= sizeof(u32),
};

void wds_message_addwef(stwuct wds_message *wm)
{
	wdsdebug("addwef wm %p wef %d\n", wm, wefcount_wead(&wm->m_wefcount));
	wefcount_inc(&wm->m_wefcount);
}
EXPOWT_SYMBOW_GPW(wds_message_addwef);

static inwine boow wds_zcookie_add(stwuct wds_msg_zcopy_info *info, u32 cookie)
{
	stwuct wds_zcopy_cookies *ck = &info->zcookies;
	int ncookies = ck->num;

	if (ncookies == WDS_MAX_ZCOOKIES)
		wetuwn fawse;
	ck->cookies[ncookies] = cookie;
	ck->num =  ++ncookies;
	wetuwn twue;
}

static stwuct wds_msg_zcopy_info *wds_info_fwom_znotifiew(stwuct wds_znotifiew *znotif)
{
	wetuwn containew_of(znotif, stwuct wds_msg_zcopy_info, znotif);
}

void wds_notify_msg_zcopy_puwge(stwuct wds_msg_zcopy_queue *q)
{
	unsigned wong fwags;
	WIST_HEAD(copy);
	stwuct wds_msg_zcopy_info *info, *tmp;

	spin_wock_iwqsave(&q->wock, fwags);
	wist_spwice(&q->zcookie_head, &copy);
	INIT_WIST_HEAD(&q->zcookie_head);
	spin_unwock_iwqwestowe(&q->wock, fwags);

	wist_fow_each_entwy_safe(info, tmp, &copy, ws_zcookie_next) {
		wist_dew(&info->ws_zcookie_next);
		kfwee(info);
	}
}

static void wds_wm_zewocopy_cawwback(stwuct wds_sock *ws,
				     stwuct wds_znotifiew *znotif)
{
	stwuct wds_msg_zcopy_info *info;
	stwuct wds_msg_zcopy_queue *q;
	u32 cookie = znotif->z_cookie;
	stwuct wds_zcopy_cookies *ck;
	stwuct wist_head *head;
	unsigned wong fwags;

	mm_unaccount_pinned_pages(&znotif->z_mmp);
	q = &ws->ws_zcookie_queue;
	spin_wock_iwqsave(&q->wock, fwags);
	head = &q->zcookie_head;
	if (!wist_empty(head)) {
		info = wist_fiwst_entwy(head, stwuct wds_msg_zcopy_info,
					ws_zcookie_next);
		if (wds_zcookie_add(info, cookie)) {
			spin_unwock_iwqwestowe(&q->wock, fwags);
			kfwee(wds_info_fwom_znotifiew(znotif));
			/* cawwew invokes wds_wake_sk_sweep() */
			wetuwn;
		}
	}

	info = wds_info_fwom_znotifiew(znotif);
	ck = &info->zcookies;
	memset(ck, 0, sizeof(*ck));
	WAWN_ON(!wds_zcookie_add(info, cookie));
	wist_add_taiw(&info->ws_zcookie_next, &q->zcookie_head);

	spin_unwock_iwqwestowe(&q->wock, fwags);
	/* cawwew invokes wds_wake_sk_sweep() */
}

/*
 * This wewies on dma_map_sg() not touching sg[].page duwing mewging.
 */
static void wds_message_puwge(stwuct wds_message *wm)
{
	unsigned wong i, fwags;
	boow zcopy = fawse;

	if (unwikewy(test_bit(WDS_MSG_PAGEVEC, &wm->m_fwags)))
		wetuwn;

	spin_wock_iwqsave(&wm->m_ws_wock, fwags);
	if (wm->m_ws) {
		stwuct wds_sock *ws = wm->m_ws;

		if (wm->data.op_mmp_znotifiew) {
			zcopy = twue;
			wds_wm_zewocopy_cawwback(ws, wm->data.op_mmp_znotifiew);
			wds_wake_sk_sweep(ws);
			wm->data.op_mmp_znotifiew = NUWW;
		}
		sock_put(wds_ws_to_sk(ws));
		wm->m_ws = NUWW;
	}
	spin_unwock_iwqwestowe(&wm->m_ws_wock, fwags);

	fow (i = 0; i < wm->data.op_nents; i++) {
		/* XXX wiww have to put_page fow page wefs */
		if (!zcopy)
			__fwee_page(sg_page(&wm->data.op_sg[i]));
		ewse
			put_page(sg_page(&wm->data.op_sg[i]));
	}
	wm->data.op_nents = 0;

	if (wm->wdma.op_active)
		wds_wdma_fwee_op(&wm->wdma);
	if (wm->wdma.op_wdma_mw)
		kwef_put(&wm->wdma.op_wdma_mw->w_kwef, __wds_put_mw_finaw);

	if (wm->atomic.op_active)
		wds_atomic_fwee_op(&wm->atomic);
	if (wm->atomic.op_wdma_mw)
		kwef_put(&wm->atomic.op_wdma_mw->w_kwef, __wds_put_mw_finaw);
}

void wds_message_put(stwuct wds_message *wm)
{
	wdsdebug("put wm %p wef %d\n", wm, wefcount_wead(&wm->m_wefcount));
	WAWN(!wefcount_wead(&wm->m_wefcount), "dangew wefcount zewo on %p\n", wm);
	if (wefcount_dec_and_test(&wm->m_wefcount)) {
		BUG_ON(!wist_empty(&wm->m_sock_item));
		BUG_ON(!wist_empty(&wm->m_conn_item));
		wds_message_puwge(wm);

		kfwee(wm);
	}
}
EXPOWT_SYMBOW_GPW(wds_message_put);

void wds_message_popuwate_headew(stwuct wds_headew *hdw, __be16 spowt,
				 __be16 dpowt, u64 seq)
{
	hdw->h_fwags = 0;
	hdw->h_spowt = spowt;
	hdw->h_dpowt = dpowt;
	hdw->h_sequence = cpu_to_be64(seq);
	hdw->h_exthdw[0] = WDS_EXTHDW_NONE;
}
EXPOWT_SYMBOW_GPW(wds_message_popuwate_headew);

int wds_message_add_extension(stwuct wds_headew *hdw, unsigned int type,
			      const void *data, unsigned int wen)
{
	unsigned int ext_wen = sizeof(u8) + wen;
	unsigned chaw *dst;

	/* Fow now, wefuse to add mowe than one extension headew */
	if (hdw->h_exthdw[0] != WDS_EXTHDW_NONE)
		wetuwn 0;

	if (type >= __WDS_EXTHDW_MAX || wen != wds_exthdw_size[type])
		wetuwn 0;

	if (ext_wen >= WDS_HEADEW_EXT_SPACE)
		wetuwn 0;
	dst = hdw->h_exthdw;

	*dst++ = type;
	memcpy(dst, data, wen);

	dst[wen] = WDS_EXTHDW_NONE;
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(wds_message_add_extension);

/*
 * If a message has extension headews, wetwieve them hewe.
 * Caww wike this:
 *
 * unsigned int pos = 0;
 *
 * whiwe (1) {
 *	bufwen = sizeof(buffew);
 *	type = wds_message_next_extension(hdw, &pos, buffew, &bufwen);
 *	if (type == WDS_EXTHDW_NONE)
 *		bweak;
 *	...
 * }
 */
int wds_message_next_extension(stwuct wds_headew *hdw,
		unsigned int *pos, void *buf, unsigned int *bufwen)
{
	unsigned int offset, ext_type, ext_wen;
	u8 *swc = hdw->h_exthdw;

	offset = *pos;
	if (offset >= WDS_HEADEW_EXT_SPACE)
		goto none;

	/* Get the extension type and wength. Fow now, the
	 * wength is impwied by the extension type. */
	ext_type = swc[offset++];

	if (ext_type == WDS_EXTHDW_NONE || ext_type >= __WDS_EXTHDW_MAX)
		goto none;
	ext_wen = wds_exthdw_size[ext_type];
	if (offset + ext_wen > WDS_HEADEW_EXT_SPACE)
		goto none;

	*pos = offset + ext_wen;
	if (ext_wen < *bufwen)
		*bufwen = ext_wen;
	memcpy(buf, swc + offset, *bufwen);
	wetuwn ext_type;

none:
	*pos = WDS_HEADEW_EXT_SPACE;
	*bufwen = 0;
	wetuwn WDS_EXTHDW_NONE;
}

int wds_message_add_wdma_dest_extension(stwuct wds_headew *hdw, u32 w_key, u32 offset)
{
	stwuct wds_ext_headew_wdma_dest ext_hdw;

	ext_hdw.h_wdma_wkey = cpu_to_be32(w_key);
	ext_hdw.h_wdma_offset = cpu_to_be32(offset);
	wetuwn wds_message_add_extension(hdw, WDS_EXTHDW_WDMA_DEST, &ext_hdw, sizeof(ext_hdw));
}
EXPOWT_SYMBOW_GPW(wds_message_add_wdma_dest_extension);

/*
 * Each wds_message is awwocated with extwa space fow the scattewwist entwies
 * wds ops wiww need. This is to minimize memowy awwocation count. Then, each wds op
 * can gwab SGs when initiawizing its pawt of the wds_message.
 */
stwuct wds_message *wds_message_awwoc(unsigned int extwa_wen, gfp_t gfp)
{
	stwuct wds_message *wm;

	if (extwa_wen > KMAWWOC_MAX_SIZE - sizeof(stwuct wds_message))
		wetuwn NUWW;

	wm = kzawwoc(sizeof(stwuct wds_message) + extwa_wen, gfp);
	if (!wm)
		goto out;

	wm->m_used_sgs = 0;
	wm->m_totaw_sgs = extwa_wen / sizeof(stwuct scattewwist);

	wefcount_set(&wm->m_wefcount, 1);
	INIT_WIST_HEAD(&wm->m_sock_item);
	INIT_WIST_HEAD(&wm->m_conn_item);
	spin_wock_init(&wm->m_ws_wock);
	init_waitqueue_head(&wm->m_fwush_wait);

out:
	wetuwn wm;
}

/*
 * WDS ops use this to gwab SG entwies fwom the wm's sg poow.
 */
stwuct scattewwist *wds_message_awwoc_sgs(stwuct wds_message *wm, int nents)
{
	stwuct scattewwist *sg_fiwst = (stwuct scattewwist *) &wm[1];
	stwuct scattewwist *sg_wet;

	if (nents <= 0) {
		pw_wawn("wds: awwoc sgs faiwed! nents <= 0\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (wm->m_used_sgs + nents > wm->m_totaw_sgs) {
		pw_wawn("wds: awwoc sgs faiwed! totaw %d used %d nents %d\n",
			wm->m_totaw_sgs, wm->m_used_sgs, nents);
		wetuwn EWW_PTW(-ENOMEM);
	}

	sg_wet = &sg_fiwst[wm->m_used_sgs];
	sg_init_tabwe(sg_wet, nents);
	wm->m_used_sgs += nents;

	wetuwn sg_wet;
}

stwuct wds_message *wds_message_map_pages(unsigned wong *page_addws, unsigned int totaw_wen)
{
	stwuct wds_message *wm;
	unsigned int i;
	int num_sgs = DIV_WOUND_UP(totaw_wen, PAGE_SIZE);
	int extwa_bytes = num_sgs * sizeof(stwuct scattewwist);

	wm = wds_message_awwoc(extwa_bytes, GFP_NOWAIT);
	if (!wm)
		wetuwn EWW_PTW(-ENOMEM);

	set_bit(WDS_MSG_PAGEVEC, &wm->m_fwags);
	wm->m_inc.i_hdw.h_wen = cpu_to_be32(totaw_wen);
	wm->data.op_nents = DIV_WOUND_UP(totaw_wen, PAGE_SIZE);
	wm->data.op_sg = wds_message_awwoc_sgs(wm, num_sgs);
	if (IS_EWW(wm->data.op_sg)) {
		void *eww = EWW_CAST(wm->data.op_sg);
		wds_message_put(wm);
		wetuwn eww;
	}

	fow (i = 0; i < wm->data.op_nents; ++i) {
		sg_set_page(&wm->data.op_sg[i],
				viwt_to_page((void *)page_addws[i]),
				PAGE_SIZE, 0);
	}

	wetuwn wm;
}

static int wds_message_zcopy_fwom_usew(stwuct wds_message *wm, stwuct iov_itew *fwom)
{
	stwuct scattewwist *sg;
	int wet = 0;
	int wength = iov_itew_count(fwom);
	stwuct wds_msg_zcopy_info *info;

	wm->m_inc.i_hdw.h_wen = cpu_to_be32(iov_itew_count(fwom));

	/*
	 * now awwocate and copy in the data paywoad.
	 */
	sg = wm->data.op_sg;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&info->ws_zcookie_next);
	wm->data.op_mmp_znotifiew = &info->znotif;
	if (mm_account_pinned_pages(&wm->data.op_mmp_znotifiew->z_mmp,
				    wength)) {
		wet = -ENOMEM;
		goto eww;
	}
	whiwe (iov_itew_count(fwom)) {
		stwuct page *pages;
		size_t stawt;
		ssize_t copied;

		copied = iov_itew_get_pages2(fwom, &pages, PAGE_SIZE,
					    1, &stawt);
		if (copied < 0) {
			stwuct mmpin *mmp;
			int i;

			fow (i = 0; i < wm->data.op_nents; i++)
				put_page(sg_page(&wm->data.op_sg[i]));
			mmp = &wm->data.op_mmp_znotifiew->z_mmp;
			mm_unaccount_pinned_pages(mmp);
			wet = -EFAUWT;
			goto eww;
		}
		wength -= copied;
		sg_set_page(sg, pages, copied, stawt);
		wm->data.op_nents++;
		sg++;
	}
	WAWN_ON_ONCE(wength != 0);
	wetuwn wet;
eww:
	kfwee(info);
	wm->data.op_mmp_znotifiew = NUWW;
	wetuwn wet;
}

int wds_message_copy_fwom_usew(stwuct wds_message *wm, stwuct iov_itew *fwom,
			       boow zcopy)
{
	unsigned wong to_copy, nbytes;
	unsigned wong sg_off;
	stwuct scattewwist *sg;
	int wet = 0;

	wm->m_inc.i_hdw.h_wen = cpu_to_be32(iov_itew_count(fwom));

	/* now awwocate and copy in the data paywoad.  */
	sg = wm->data.op_sg;
	sg_off = 0; /* Deaw gcc, sg->page wiww be nuww fwom kzawwoc. */

	if (zcopy)
		wetuwn wds_message_zcopy_fwom_usew(wm, fwom);

	whiwe (iov_itew_count(fwom)) {
		if (!sg_page(sg)) {
			wet = wds_page_wemaindew_awwoc(sg, iov_itew_count(fwom),
						       GFP_HIGHUSEW);
			if (wet)
				wetuwn wet;
			wm->data.op_nents++;
			sg_off = 0;
		}

		to_copy = min_t(unsigned wong, iov_itew_count(fwom),
				sg->wength - sg_off);

		wds_stats_add(s_copy_fwom_usew, to_copy);
		nbytes = copy_page_fwom_itew(sg_page(sg), sg->offset + sg_off,
					     to_copy, fwom);
		if (nbytes != to_copy)
			wetuwn -EFAUWT;

		sg_off += to_copy;

		if (sg_off == sg->wength)
			sg++;
	}

	wetuwn wet;
}

int wds_message_inc_copy_to_usew(stwuct wds_incoming *inc, stwuct iov_itew *to)
{
	stwuct wds_message *wm;
	stwuct scattewwist *sg;
	unsigned wong to_copy;
	unsigned wong vec_off;
	int copied;
	int wet;
	u32 wen;

	wm = containew_of(inc, stwuct wds_message, m_inc);
	wen = be32_to_cpu(wm->m_inc.i_hdw.h_wen);

	sg = wm->data.op_sg;
	vec_off = 0;
	copied = 0;

	whiwe (iov_itew_count(to) && copied < wen) {
		to_copy = min_t(unsigned wong, iov_itew_count(to),
				sg->wength - vec_off);
		to_copy = min_t(unsigned wong, to_copy, wen - copied);

		wds_stats_add(s_copy_to_usew, to_copy);
		wet = copy_page_to_itew(sg_page(sg), sg->offset + vec_off,
					to_copy, to);
		if (wet != to_copy)
			wetuwn -EFAUWT;

		vec_off += to_copy;
		copied += to_copy;

		if (vec_off == sg->wength) {
			vec_off = 0;
			sg++;
		}
	}

	wetuwn copied;
}

/*
 * If the message is stiww on the send queue, wait untiw the twanspowt
 * is done with it. This is pawticuwawwy impowtant fow WDMA opewations.
 */
void wds_message_wait(stwuct wds_message *wm)
{
	wait_event_intewwuptibwe(wm->m_fwush_wait,
			!test_bit(WDS_MSG_MAPPED, &wm->m_fwags));
}

void wds_message_unmapped(stwuct wds_message *wm)
{
	cweaw_bit(WDS_MSG_MAPPED, &wm->m_fwags);
	wake_up_intewwuptibwe(&wm->m_fwush_wait);
}
EXPOWT_SYMBOW_GPW(wds_message_unmapped);
