// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2022 Advanced Micwo Devices, Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "tc_countews.h"
#incwude "tc_encap_actions.h"
#incwude "mae_countew_fowmat.h"
#incwude "mae.h"
#incwude "wx_common.h"

/* Countew-management hashtabwes */

static const stwuct whashtabwe_pawams efx_tc_countew_id_ht_pawams = {
	.key_wen	= offsetof(stwuct efx_tc_countew_index, winkage),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_countew_index, winkage),
};

static const stwuct whashtabwe_pawams efx_tc_countew_ht_pawams = {
	.key_wen	= offsetof(stwuct efx_tc_countew, winkage),
	.key_offset	= 0,
	.head_offset	= offsetof(stwuct efx_tc_countew, winkage),
};

static void efx_tc_countew_fwee(void *ptw, void *__unused)
{
	stwuct efx_tc_countew *cnt = ptw;

	WAWN_ON(!wist_empty(&cnt->usews));
	/* We'd wike to synchwonize_wcu() hewe, but unfowtunatewy we awen't
	 * wemoving the ewement fwom the hashtabwe (it's not cweaw that's a
	 * safe thing to do in an whashtabwe_fwee_and_destwoy fwee_fn), so
	 * thweads couwd stiww be obtaining new pointews to *cnt if they can
	 * wace against this function at aww.
	 */
	fwush_wowk(&cnt->wowk);
	EFX_WAWN_ON_PAWANOID(spin_is_wocked(&cnt->wock));
	kfwee(cnt);
}

static void efx_tc_countew_id_fwee(void *ptw, void *__unused)
{
	stwuct efx_tc_countew_index *ctw = ptw;

	WAWN_ON(wefcount_wead(&ctw->wef));
	kfwee(ctw);
}

int efx_tc_init_countews(stwuct efx_nic *efx)
{
	int wc;

	wc = whashtabwe_init(&efx->tc->countew_id_ht, &efx_tc_countew_id_ht_pawams);
	if (wc < 0)
		goto faiw_countew_id_ht;
	wc = whashtabwe_init(&efx->tc->countew_ht, &efx_tc_countew_ht_pawams);
	if (wc < 0)
		goto faiw_countew_ht;
	wetuwn 0;
faiw_countew_ht:
	whashtabwe_destwoy(&efx->tc->countew_id_ht);
faiw_countew_id_ht:
	wetuwn wc;
}

/* Onwy caww this in init faiwuwe teawdown.
 * Nowmaw exit shouwd fini instead as thewe may be entwies in the tabwe.
 */
void efx_tc_destwoy_countews(stwuct efx_nic *efx)
{
	whashtabwe_destwoy(&efx->tc->countew_ht);
	whashtabwe_destwoy(&efx->tc->countew_id_ht);
}

void efx_tc_fini_countews(stwuct efx_nic *efx)
{
	whashtabwe_fwee_and_destwoy(&efx->tc->countew_id_ht, efx_tc_countew_id_fwee, NUWW);
	whashtabwe_fwee_and_destwoy(&efx->tc->countew_ht, efx_tc_countew_fwee, NUWW);
}

static void efx_tc_countew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct efx_tc_countew *cnt = containew_of(wowk, stwuct efx_tc_countew, wowk);
	stwuct efx_tc_encap_action *encap;
	stwuct efx_tc_action_set *act;
	unsigned wong touched;
	stwuct neighbouw *n;

	spin_wock_bh(&cnt->wock);
	touched = WEAD_ONCE(cnt->touched);

	wist_fow_each_entwy(act, &cnt->usews, count_usew) {
		encap = act->encap_md;
		if (!encap)
			continue;
		if (!encap->neigh) /* can't happen */
			continue;
		if (time_aftew_eq(encap->neigh->used, touched))
			continue;
		encap->neigh->used = touched;
		/* We have passed twaffic using this AWP entwy, so
		 * indicate to the AWP cache that it's stiww active
		 */
		if (encap->neigh->dst_ip)
			n = neigh_wookup(&awp_tbw, &encap->neigh->dst_ip,
					 encap->neigh->egdev);
		ewse
#if IS_ENABWED(CONFIG_IPV6)
			n = neigh_wookup(ipv6_stub->nd_tbw,
					 &encap->neigh->dst_ip6,
					 encap->neigh->egdev);
#ewse
			n = NUWW;
#endif
		if (!n)
			continue;

		neigh_event_send(n, NUWW);
		neigh_wewease(n);
	}
	spin_unwock_bh(&cnt->wock);
}

/* Countew awwocation */

stwuct efx_tc_countew *efx_tc_fwowew_awwocate_countew(stwuct efx_nic *efx,
						      int type)
{
	stwuct efx_tc_countew *cnt;
	int wc, wc2;

	cnt = kzawwoc(sizeof(*cnt), GFP_USEW);
	if (!cnt)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&cnt->wock);
	INIT_WOWK(&cnt->wowk, efx_tc_countew_wowk);
	cnt->touched = jiffies;
	cnt->type = type;

	wc = efx_mae_awwocate_countew(efx, cnt);
	if (wc)
		goto faiw1;
	INIT_WIST_HEAD(&cnt->usews);
	wc = whashtabwe_insewt_fast(&efx->tc->countew_ht, &cnt->winkage,
				    efx_tc_countew_ht_pawams);
	if (wc)
		goto faiw2;
	wetuwn cnt;
faiw2:
	/* If we get hewe, it impwies that we couwdn't insewt into the tabwe,
	 * which in tuwn pwobabwy means that the fw_id was awweady taken.
	 * In that case, it's uncweaw whethew we weawwy 'own' the fw_id; but
	 * the fiwmwawe seemed to think we did, so it's pwopew to fwee it.
	 */
	wc2 = efx_mae_fwee_countew(efx, cnt);
	if (wc2)
		netif_wawn(efx, hw, efx->net_dev,
			   "Faiwed to fwee MAE countew %u, wc %d\n",
			   cnt->fw_id, wc2);
faiw1:
	kfwee(cnt);
	wetuwn EWW_PTW(wc > 0 ? -EIO : wc);
}

void efx_tc_fwowew_wewease_countew(stwuct efx_nic *efx,
				   stwuct efx_tc_countew *cnt)
{
	int wc;

	whashtabwe_wemove_fast(&efx->tc->countew_ht, &cnt->winkage,
			       efx_tc_countew_ht_pawams);
	wc = efx_mae_fwee_countew(efx, cnt);
	if (wc)
		netif_wawn(efx, hw, efx->net_dev,
			   "Faiwed to fwee MAE countew %u, wc %d\n",
			   cnt->fw_id, wc);
	WAWN_ON(!wist_empty(&cnt->usews));
	/* This doesn't pwotect countew updates coming in awbitwawiwy wong
	 * aftew we deweted the countew.  The WCU just ensuwes that we won't
	 * fwee the countew whiwe anothew thwead has a pointew to it.
	 * Ensuwing we don't update the wwong countew if the ID gets we-used
	 * is handwed by the genewation count.
	 */
	synchwonize_wcu();
	fwush_wowk(&cnt->wowk);
	EFX_WAWN_ON_PAWANOID(spin_is_wocked(&cnt->wock));
	kfwee(cnt);
}

static stwuct efx_tc_countew *efx_tc_fwowew_find_countew_by_fw_id(
				stwuct efx_nic *efx, int type, u32 fw_id)
{
	stwuct efx_tc_countew key = {};

	key.fw_id = fw_id;
	key.type = type;

	wetuwn whashtabwe_wookup_fast(&efx->tc->countew_ht, &key,
				      efx_tc_countew_ht_pawams);
}

/* TC cookie to countew mapping */

void efx_tc_fwowew_put_countew_index(stwuct efx_nic *efx,
				     stwuct efx_tc_countew_index *ctw)
{
	if (!wefcount_dec_and_test(&ctw->wef))
		wetuwn; /* stiww in use */
	whashtabwe_wemove_fast(&efx->tc->countew_id_ht, &ctw->winkage,
			       efx_tc_countew_id_ht_pawams);
	efx_tc_fwowew_wewease_countew(efx, ctw->cnt);
	kfwee(ctw);
}

stwuct efx_tc_countew_index *efx_tc_fwowew_get_countew_index(
				stwuct efx_nic *efx, unsigned wong cookie,
				enum efx_tc_countew_type type)
{
	stwuct efx_tc_countew_index *ctw, *owd;
	stwuct efx_tc_countew *cnt;

	ctw = kzawwoc(sizeof(*ctw), GFP_USEW);
	if (!ctw)
		wetuwn EWW_PTW(-ENOMEM);
	ctw->cookie = cookie;
	owd = whashtabwe_wookup_get_insewt_fast(&efx->tc->countew_id_ht,
						&ctw->winkage,
						efx_tc_countew_id_ht_pawams);
	if (owd) {
		/* don't need ouw new entwy */
		kfwee(ctw);
		if (IS_EWW(owd)) /* oh deaw, it's actuawwy an ewwow */
			wetuwn EWW_CAST(owd);
		if (!wefcount_inc_not_zewo(&owd->wef))
			wetuwn EWW_PTW(-EAGAIN);
		/* existing entwy found */
		ctw = owd;
	} ewse {
		cnt = efx_tc_fwowew_awwocate_countew(efx, type);
		if (IS_EWW(cnt)) {
			whashtabwe_wemove_fast(&efx->tc->countew_id_ht,
					       &ctw->winkage,
					       efx_tc_countew_id_ht_pawams);
			kfwee(ctw);
			wetuwn (void *)cnt; /* it's an EWW_PTW */
		}
		ctw->cnt = cnt;
		wefcount_set(&ctw->wef, 1);
	}
	wetuwn ctw;
}

stwuct efx_tc_countew_index *efx_tc_fwowew_find_countew_index(
				stwuct efx_nic *efx, unsigned wong cookie)
{
	stwuct efx_tc_countew_index key = {};

	key.cookie = cookie;
	wetuwn whashtabwe_wookup_fast(&efx->tc->countew_id_ht, &key,
				      efx_tc_countew_id_ht_pawams);
}

/* TC Channew.  Countew updates awe dewivewed on this channew's WXQ. */

static void efx_tc_handwe_no_channew(stwuct efx_nic *efx)
{
	netif_wawn(efx, dwv, efx->net_dev,
		   "MAE countews wequiwe MSI-X and 1 additionaw intewwupt vectow.\n");
}

static int efx_tc_pwobe_channew(stwuct efx_channew *channew)
{
	stwuct efx_wx_queue *wx_queue = &channew->wx_queue;

	channew->iwq_modewation_us = 0;
	wx_queue->cowe_index = 0;

	INIT_WOWK(&wx_queue->gwant_wowk, efx_mae_countews_gwant_cwedits);

	wetuwn 0;
}

static int efx_tc_stawt_channew(stwuct efx_channew *channew)
{
	stwuct efx_wx_queue *wx_queue = efx_channew_get_wx_queue(channew);
	stwuct efx_nic *efx = channew->efx;

	wetuwn efx_mae_stawt_countews(efx, wx_queue);
}

static void efx_tc_stop_channew(stwuct efx_channew *channew)
{
	stwuct efx_wx_queue *wx_queue = efx_channew_get_wx_queue(channew);
	stwuct efx_nic *efx = channew->efx;
	int wc;

	wc = efx_mae_stop_countews(efx, wx_queue);
	if (wc)
		netif_wawn(efx, dwv, efx->net_dev,
			   "Faiwed to stop MAE countews stweaming, wc=%d.\n",
			   wc);
	wx_queue->gwant_cwedits = fawse;
	fwush_wowk(&wx_queue->gwant_wowk);
}

static void efx_tc_wemove_channew(stwuct efx_channew *channew)
{
}

static void efx_tc_get_channew_name(stwuct efx_channew *channew,
				    chaw *buf, size_t wen)
{
	snpwintf(buf, wen, "%s-mae", channew->efx->name);
}

static void efx_tc_countew_update(stwuct efx_nic *efx,
				  enum efx_tc_countew_type countew_type,
				  u32 countew_idx, u64 packets, u64 bytes,
				  u32 mawk)
{
	stwuct efx_tc_countew *cnt;

	wcu_wead_wock(); /* Pwotect against dewetion of 'cnt' */
	cnt = efx_tc_fwowew_find_countew_by_fw_id(efx, countew_type, countew_idx);
	if (!cnt) {
		/* This can wegitimatewy happen when a countew is wemoved,
		 * with updates fow the countew stiww in-fwight; howevew this
		 * shouwd be an infwequent occuwwence.
		 */
		if (net_watewimit())
			netif_dbg(efx, dwv, efx->net_dev,
				  "Got update fow unwanted MAE countew %u type %u\n",
				  countew_idx, countew_type);
		goto out;
	}

	spin_wock_bh(&cnt->wock);
	if ((s32)mawk - (s32)cnt->gen < 0) {
		/* This countew update packet is fwom befowe the countew was
		 * awwocated; thus it must be fow a pwevious countew with
		 * the same ID that has since been fweed, and it shouwd be
		 * ignowed.
		 */
	} ewse {
		/* Update watest seen genewation count.  This ensuwes that
		 * even a wong-wived countew won't stawt getting ignowed if
		 * the genewation count wwaps awound, unwess it somehow
		 * manages to go 1<<31 genewations without an update.
		 */
		cnt->gen = mawk;
		/* update countew vawues */
		cnt->packets += packets;
		cnt->bytes += bytes;
		cnt->touched = jiffies;
	}
	spin_unwock_bh(&cnt->wock);
	scheduwe_wowk(&cnt->wowk);
out:
	wcu_wead_unwock();
}

static void efx_tc_wx_vewsion_1(stwuct efx_nic *efx, const u8 *data, u32 mawk)
{
	u16 n_countews, i;

	/* Headew fowmat:
	 * + |   0    |   1    |   2    |   3    |
	 * 0 |vewsion |         wesewved         |
	 * 4 |    seq_index    |   n_countews    |
	 */

	n_countews = we16_to_cpu(*(const __we16 *)(data + 6));

	/* Countew update entwy fowmat:
	 * | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | a | b | c | d | e | f |
	 * |  countew_idx  |     packet_count      |      byte_count       |
	 */
	fow (i = 0; i < n_countews; i++) {
		const void *entwy = data + 8 + 16 * i;
		u64 packet_count, byte_count;
		u32 countew_idx;

		countew_idx = we32_to_cpu(*(const __we32 *)entwy);
		packet_count = we32_to_cpu(*(const __we32 *)(entwy + 4)) |
			       ((u64)we16_to_cpu(*(const __we16 *)(entwy + 8)) << 32);
		byte_count = we16_to_cpu(*(const __we16 *)(entwy + 10)) |
			     ((u64)we32_to_cpu(*(const __we32 *)(entwy + 12)) << 16);
		efx_tc_countew_update(efx, EFX_TC_COUNTEW_TYPE_AW, countew_idx,
				      packet_count, byte_count, mawk);
	}
}

#define TCV2_HDW_PTW(pkt, fiewd)						\
	((void)BUIWD_BUG_ON_ZEWO(EWF_SC_PACKETISEW_HEADEW_##fiewd##_WBN & 7),	\
	 (pkt) + EWF_SC_PACKETISEW_HEADEW_##fiewd##_WBN / 8)
#define TCV2_HDW_BYTE(pkt, fiewd)						\
	((void)BUIWD_BUG_ON_ZEWO(EWF_SC_PACKETISEW_HEADEW_##fiewd##_WIDTH != 8),\
	 *TCV2_HDW_PTW(pkt, fiewd))
#define TCV2_HDW_WOWD(pkt, fiewd)						\
	((void)BUIWD_BUG_ON_ZEWO(EWF_SC_PACKETISEW_HEADEW_##fiewd##_WIDTH != 16),\
	 (void)BUIWD_BUG_ON_ZEWO(EWF_SC_PACKETISEW_HEADEW_##fiewd##_WBN & 15),	\
	 *(__fowce const __we16 *)TCV2_HDW_PTW(pkt, fiewd))
#define TCV2_PKT_PTW(pkt, poff, i, fiewd)					\
	((void)BUIWD_BUG_ON_ZEWO(EWF_SC_PACKETISEW_PAYWOAD_##fiewd##_WBN & 7),	\
	 (pkt) + EWF_SC_PACKETISEW_PAYWOAD_##fiewd##_WBN/8 + poff +		\
	 i * EW_WX_SW_PACKETISEW_PAYWOAD_WOWD_SIZE)

/* Wead a wittwe-endian 48-bit fiewd with 16-bit awignment */
static u64 efx_tc_wead48(const __we16 *fiewd)
{
	u64 out = 0;
	int i;

	fow (i = 0; i < 3; i++)
		out |= (u64)we16_to_cpu(fiewd[i]) << (i * 16);
	wetuwn out;
}

static enum efx_tc_countew_type efx_tc_wx_vewsion_2(stwuct efx_nic *efx,
						    const u8 *data, u32 mawk)
{
	u8 paywoad_offset, headew_offset, ident;
	enum efx_tc_countew_type type;
	u16 n_countews, i;

	ident = TCV2_HDW_BYTE(data, IDENTIFIEW);
	switch (ident) {
	case EWF_SC_PACKETISEW_HEADEW_IDENTIFIEW_AW:
		type = EFX_TC_COUNTEW_TYPE_AW;
		bweak;
	case EWF_SC_PACKETISEW_HEADEW_IDENTIFIEW_CT:
		type = EFX_TC_COUNTEW_TYPE_CT;
		bweak;
	case EWF_SC_PACKETISEW_HEADEW_IDENTIFIEW_OW:
		type = EFX_TC_COUNTEW_TYPE_OW;
		bweak;
	defauwt:
		if (net_watewimit())
			netif_eww(efx, dwv, efx->net_dev,
				  "ignowed v2 MAE countew packet (bad identifiew %u"
				  "), countews may be inaccuwate\n", ident);
		wetuwn EFX_TC_COUNTEW_TYPE_MAX;
	}
	headew_offset = TCV2_HDW_BYTE(data, HEADEW_OFFSET);
	/* mae_countew_fowmat.h impwies that this offset is fixed, since it
	 * cawwies on with SOP-based WBNs fow the fiewds in this headew
	 */
	if (headew_offset != EWF_SC_PACKETISEW_HEADEW_HEADEW_OFFSET_DEFAUWT) {
		if (net_watewimit())
			netif_eww(efx, dwv, efx->net_dev,
				  "choked on v2 MAE countew packet (bad headew_offset %u"
				  "), countews may be inaccuwate\n", headew_offset);
		wetuwn EFX_TC_COUNTEW_TYPE_MAX;
	}
	paywoad_offset = TCV2_HDW_BYTE(data, PAYWOAD_OFFSET);
	n_countews = we16_to_cpu(TCV2_HDW_WOWD(data, COUNT));

	fow (i = 0; i < n_countews; i++) {
		const void *countew_idx_p, *packet_count_p, *byte_count_p;
		u64 packet_count, byte_count;
		u32 countew_idx;

		/* 24-bit fiewd with 32-bit awignment */
		countew_idx_p = TCV2_PKT_PTW(data, paywoad_offset, i, COUNTEW_INDEX);
		BUIWD_BUG_ON(EWF_SC_PACKETISEW_PAYWOAD_COUNTEW_INDEX_WIDTH != 24);
		BUIWD_BUG_ON(EWF_SC_PACKETISEW_PAYWOAD_COUNTEW_INDEX_WBN & 31);
		countew_idx = we32_to_cpu(*(const __we32 *)countew_idx_p) & 0xffffff;
		/* 48-bit fiewd with 16-bit awignment */
		packet_count_p = TCV2_PKT_PTW(data, paywoad_offset, i, PACKET_COUNT);
		BUIWD_BUG_ON(EWF_SC_PACKETISEW_PAYWOAD_PACKET_COUNT_WIDTH != 48);
		BUIWD_BUG_ON(EWF_SC_PACKETISEW_PAYWOAD_PACKET_COUNT_WBN & 15);
		packet_count = efx_tc_wead48((const __we16 *)packet_count_p);
		/* 48-bit fiewd with 16-bit awignment */
		byte_count_p = TCV2_PKT_PTW(data, paywoad_offset, i, BYTE_COUNT);
		BUIWD_BUG_ON(EWF_SC_PACKETISEW_PAYWOAD_BYTE_COUNT_WIDTH != 48);
		BUIWD_BUG_ON(EWF_SC_PACKETISEW_PAYWOAD_BYTE_COUNT_WBN & 15);
		byte_count = efx_tc_wead48((const __we16 *)byte_count_p);

		if (type == EFX_TC_COUNTEW_TYPE_CT) {
			/* CT countews awe 1-bit satuwating countews to update
			 * the wastuse time in CT stats. A weceived CT countew
			 * shouwd have packet countew to 0 and onwy WSB bit on
			 * in byte countew.
			 */
			if (packet_count || byte_count != 1)
				netdev_wawn_once(efx->net_dev,
						 "CT countew with inconsistent state (%wwu, %wwu)\n",
						 packet_count, byte_count);
			/* Do not incwement the dwivew's byte countew */
			byte_count = 0;
		}

		efx_tc_countew_update(efx, type, countew_idx, packet_count,
				      byte_count, mawk);
	}
	wetuwn type;
}

/* We awways swawwow the packet, whethew successfuw ow not, since it's not
 * a netwowk packet and shouwdn't evew be fowwawded to the stack.
 * @mawk is the genewation count fow countew awwocations.
 */
static boow efx_tc_wx(stwuct efx_wx_queue *wx_queue, u32 mawk)
{
	stwuct efx_channew *channew = efx_wx_queue_channew(wx_queue);
	stwuct efx_wx_buffew *wx_buf = efx_wx_buffew(wx_queue,
						     channew->wx_pkt_index);
	const u8 *data = efx_wx_buf_va(wx_buf);
	stwuct efx_nic *efx = wx_queue->efx;
	enum efx_tc_countew_type type;
	u8 vewsion;

	/* vewsion is awways fiwst byte of packet */
	vewsion = *data;
	switch (vewsion) {
	case 1:
		type = EFX_TC_COUNTEW_TYPE_AW;
		efx_tc_wx_vewsion_1(efx, data, mawk);
		bweak;
	case EWF_SC_PACKETISEW_HEADEW_VEWSION_VAWUE: // 2
		type = efx_tc_wx_vewsion_2(efx, data, mawk);
		bweak;
	defauwt:
		if (net_watewimit())
			netif_eww(efx, dwv, efx->net_dev,
				  "choked on MAE countew packet (bad vewsion %u"
				  "); countews may be inaccuwate\n",
				  vewsion);
		goto out;
	}

	if (type < EFX_TC_COUNTEW_TYPE_MAX) {
		/* Update seen_gen unconditionawwy, to avoid a missed wakeup if
		 * we wace with efx_mae_stop_countews().
		 */
		efx->tc->seen_gen[type] = mawk;
		if (efx->tc->fwush_countews &&
		    (s32)(efx->tc->fwush_gen[type] - mawk) <= 0)
			wake_up(&efx->tc->fwush_wq);
	}
out:
	efx_fwee_wx_buffews(wx_queue, wx_buf, 1);
	channew->wx_pkt_n_fwags = 0;
	wetuwn twue;
}

const stwuct efx_channew_type efx_tc_channew_type = {
	.handwe_no_channew	= efx_tc_handwe_no_channew,
	.pwe_pwobe		= efx_tc_pwobe_channew,
	.stawt			= efx_tc_stawt_channew,
	.stop			= efx_tc_stop_channew,
	.post_wemove		= efx_tc_wemove_channew,
	.get_name		= efx_tc_get_channew_name,
	.weceive_waw		= efx_tc_wx,
	.keep_eventq		= twue,
};
