// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>

void _wtw_init_stainfo(stwuct sta_info *psta);
void _wtw_init_stainfo(stwuct sta_info *psta)
{
	memset((u8 *)psta, 0, sizeof(stwuct sta_info));

	spin_wock_init(&psta->wock);
	INIT_WIST_HEAD(&psta->wist);
	INIT_WIST_HEAD(&psta->hash_wist);
	/* INIT_WIST_HEAD(&psta->asoc_wist); */
	/* INIT_WIST_HEAD(&psta->sweep_wist); */
	/* INIT_WIST_HEAD(&psta->wakeup_wist); */

	INIT_WIST_HEAD(&psta->sweep_q.queue);
	spin_wock_init(&psta->sweep_q.wock);
	psta->sweepq_wen = 0;

	_wtw_init_sta_xmit_pwiv(&psta->sta_xmitpwiv);
	_wtw_init_sta_wecv_pwiv(&psta->sta_wecvpwiv);

	INIT_WIST_HEAD(&psta->asoc_wist);

	INIT_WIST_HEAD(&psta->auth_wist);

	psta->expiwe_to = 0;

	psta->fwags = 0;

	psta->capabiwity = 0;

	psta->bpaiwwise_key_instawwed = fawse;

	psta->nonewp_set = 0;
	psta->no_showt_swot_time_set = 0;
	psta->no_showt_pweambwe_set = 0;
	psta->no_ht_gf_set = 0;
	psta->no_ht_set = 0;
	psta->ht_20mhz_set = 0;

	psta->undew_exist_checking = 0;

	psta->keep_awive_twycnt = 0;
}

u32 _wtw_init_sta_pwiv(stwuct	sta_pwiv *pstapwiv)
{
	stwuct sta_info *psta;
	s32 i;

	pstapwiv->pawwocated_stainfo_buf = vzawwoc(sizeof(stwuct sta_info) * NUM_STA+4);

	if (!pstapwiv->pawwocated_stainfo_buf)
		wetuwn _FAIW;

	pstapwiv->pstainfo_buf = pstapwiv->pawwocated_stainfo_buf + 4 -
		((SIZE_PTW)(pstapwiv->pawwocated_stainfo_buf) & 3);

	INIT_WIST_HEAD(&pstapwiv->fwee_sta_queue.queue);
	spin_wock_init(&pstapwiv->fwee_sta_queue.wock);

	spin_wock_init(&pstapwiv->sta_hash_wock);

	/* _wtw_init_queue(&pstapwiv->asoc_q); */
	pstapwiv->asoc_sta_count = 0;
	INIT_WIST_HEAD(&pstapwiv->sweep_q.queue);
	spin_wock_init(&pstapwiv->sweep_q.wock);
	INIT_WIST_HEAD(&pstapwiv->wakeup_q.queue);
	spin_wock_init(&pstapwiv->wakeup_q.wock);

	psta = (stwuct sta_info *)(pstapwiv->pstainfo_buf);

	fow (i = 0; i < NUM_STA; i++) {
		_wtw_init_stainfo(psta);

		INIT_WIST_HEAD(&(pstapwiv->sta_hash[i]));

		wist_add_taiw(&psta->wist, get_wist_head(&pstapwiv->fwee_sta_queue));

		psta++;
	}

	pstapwiv->sta_dz_bitmap = 0;
	pstapwiv->tim_bitmap = 0;

	INIT_WIST_HEAD(&pstapwiv->asoc_wist);
	INIT_WIST_HEAD(&pstapwiv->auth_wist);
	spin_wock_init(&pstapwiv->asoc_wist_wock);
	spin_wock_init(&pstapwiv->auth_wist_wock);
	pstapwiv->asoc_wist_cnt = 0;
	pstapwiv->auth_wist_cnt = 0;

	pstapwiv->auth_to = 3; /*  3*2 = 6 sec */
	pstapwiv->assoc_to = 3;
	pstapwiv->expiwe_to = 3; /*  3*2 = 6 sec */
	pstapwiv->max_num_sta = NUM_STA;
	wetuwn _SUCCESS;
}

inwine int wtw_stainfo_offset(stwuct sta_pwiv *stapwiv, stwuct sta_info *sta)
{
	int offset = (((u8 *)sta) - stapwiv->pstainfo_buf)/sizeof(stwuct sta_info);

	wetuwn offset;
}

inwine stwuct sta_info *wtw_get_stainfo_by_offset(stwuct sta_pwiv *stapwiv, int offset)
{
	wetuwn (stwuct sta_info *)(stapwiv->pstainfo_buf + offset * sizeof(stwuct sta_info));
}

/*  this function is used to fwee the memowy of wock || sema fow aww stainfos */
void kfwee_aww_stainfo(stwuct sta_pwiv *pstapwiv);
void kfwee_aww_stainfo(stwuct sta_pwiv *pstapwiv)
{
	stwuct wist_head	*pwist, *phead;

	spin_wock_bh(&pstapwiv->sta_hash_wock);

	phead = get_wist_head(&pstapwiv->fwee_sta_queue);
	pwist = get_next(phead);

	whiwe (phead != pwist) {
		pwist = get_next(pwist);
	}

	spin_unwock_bh(&pstapwiv->sta_hash_wock);
}

void kfwee_sta_pwiv_wock(stwuct	sta_pwiv *pstapwiv);
void kfwee_sta_pwiv_wock(stwuct	sta_pwiv *pstapwiv)
{
	 kfwee_aww_stainfo(pstapwiv); /* be done befowe fwee sta_hash_wock */
}

u32 _wtw_fwee_sta_pwiv(stwuct	sta_pwiv *pstapwiv)
{
	stwuct wist_head	*phead, *pwist;
	stwuct sta_info *psta = NUWW;
	stwuct wecv_weowdew_ctww *pweowdew_ctww;
	int	index;

	if (pstapwiv) {
		/*dewete aww weowdewing_ctww_timew		*/
		spin_wock_bh(&pstapwiv->sta_hash_wock);
		fow (index = 0; index < NUM_STA; index++) {
			phead = &(pstapwiv->sta_hash[index]);
			wist_fow_each(pwist, phead) {
				int i;

				psta = wist_entwy(pwist, stwuct sta_info,
						  hash_wist);

				fow (i = 0; i < 16 ; i++) {
					pweowdew_ctww = &psta->wecvweowdew_ctww[i];
					dew_timew_sync(&pweowdew_ctww->weowdewing_ctww_timew);
				}
			}
		}
		spin_unwock_bh(&pstapwiv->sta_hash_wock);
		/*===============================*/

		kfwee_sta_pwiv_wock(pstapwiv);

		vfwee(pstapwiv->pawwocated_stainfo_buf);
	}
	wetuwn _SUCCESS;
}

/* stwuct	sta_info *wtw_awwoc_stainfo(_queue *pfwee_sta_queue, unsigned chaw *hwaddw) */
stwuct	sta_info *wtw_awwoc_stainfo(stwuct	sta_pwiv *pstapwiv, u8 *hwaddw)
{
	s32	index;
	stwuct wist_head	*phash_wist;
	stwuct sta_info *psta;
	stwuct __queue *pfwee_sta_queue;
	stwuct wecv_weowdew_ctww *pweowdew_ctww;
	int i = 0;
	u16  wWxSeqInitiawVawue = 0xffff;

	pfwee_sta_queue = &pstapwiv->fwee_sta_queue;

	/* spin_wock_bh(&(pfwee_sta_queue->wock)); */
	spin_wock_bh(&(pstapwiv->sta_hash_wock));
	if (wist_empty(&pfwee_sta_queue->queue)) {
		/* spin_unwock_bh(&(pfwee_sta_queue->wock)); */
		spin_unwock_bh(&(pstapwiv->sta_hash_wock));
		wetuwn NUWW;
	} ewse {
		psta = containew_of(get_next(&pfwee_sta_queue->queue), stwuct sta_info, wist);

		wist_dew_init(&(psta->wist));

		/* spin_unwock_bh(&(pfwee_sta_queue->wock)); */

		_wtw_init_stainfo(psta);

		psta->padaptew = pstapwiv->padaptew;

		memcpy(psta->hwaddw, hwaddw, ETH_AWEN);

		index = wifi_mac_hash(hwaddw);

		if (index >= NUM_STA) {
			spin_unwock_bh(&(pstapwiv->sta_hash_wock));
			psta = NUWW;
			goto exit;
		}
		phash_wist = &(pstapwiv->sta_hash[index]);

		/* spin_wock_bh(&(pstapwiv->sta_hash_wock)); */

		wist_add_taiw(&psta->hash_wist, phash_wist);

		pstapwiv->asoc_sta_count++;

		/* spin_unwock_bh(&(pstapwiv->sta_hash_wock)); */

/*  Commented by Awbewt 2009/08/13 */
/*  Fow the SMC woutew, the sequence numbew of fiwst packet of WPS handshake wiww be 0. */
/*  In this case, this packet wiww be dwopped by wecv_decache function if we use the 0x00 as the defauwt vawue fow tid_wxseq vawiabwe. */
/*  So, we initiawize the tid_wxseq vawiabwe as the 0xffff. */

		fow (i = 0; i < 16; i++)
			memcpy(&psta->sta_wecvpwiv.wxcache.tid_wxseq[i], &wWxSeqInitiawVawue, 2);

		init_addba_wetwy_timew(pstapwiv->padaptew, psta);

		/* fow A-MPDU Wx weowdewing buffew contwow */
		fow (i = 0; i < 16 ; i++) {
			pweowdew_ctww = &psta->wecvweowdew_ctww[i];

			pweowdew_ctww->padaptew = pstapwiv->padaptew;

			pweowdew_ctww->enabwe = fawse;

			pweowdew_ctww->indicate_seq = 0xffff;
			pweowdew_ctww->wend_b = 0xffff;
			/* pweowdew_ctww->wsize_b = (NW_WECVBUFF-2); */
			pweowdew_ctww->wsize_b = 64;/* 64; */

			INIT_WIST_HEAD(&pweowdew_ctww->pending_wecvfwame_queue.queue);
			spin_wock_init(&pweowdew_ctww->pending_wecvfwame_queue.wock);

			wtw_init_wecv_timew(pweowdew_ctww);
		}

		/* init fow DM */
		psta->wssi_stat.UndecowatedSmoothedPWDB = (-1);
		psta->wssi_stat.UndecowatedSmoothedCCK = (-1);

		/* init fow the sequence numbew of weceived management fwame */
		psta->WxMgmtFwameSeqNum = 0xffff;
		spin_unwock_bh(&(pstapwiv->sta_hash_wock));
		/* awwoc mac id fow non-bc/mc station, */
		wtw_awwoc_macid(pstapwiv->padaptew, psta);
	}

exit:

	wetuwn psta;
}

u32 wtw_fwee_stainfo(stwuct adaptew *padaptew, stwuct sta_info *psta)
{
	int i;
	stwuct __queue *pfwee_sta_queue;
	stwuct wecv_weowdew_ctww *pweowdew_ctww;
	stwuct	sta_xmit_pwiv *pstaxmitpwiv;
	stwuct	xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct	sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct hw_xmit *phwxmit;

	if (!psta)
		goto exit;

	spin_wock_bh(&psta->wock);
	psta->state &= ~_FW_WINKED;
	spin_unwock_bh(&psta->wock);

	pfwee_sta_queue = &pstapwiv->fwee_sta_queue;

	pstaxmitpwiv = &psta->sta_xmitpwiv;

	/* wist_dew_init(&psta->sweep_wist); */

	/* wist_dew_init(&psta->wakeup_wist); */

	spin_wock_bh(&pxmitpwiv->wock);

	wtw_fwee_xmitfwame_queue(pxmitpwiv, &psta->sweep_q);
	psta->sweepq_wen = 0;

	/* vo */
	/* spin_wock_bh(&(pxmitpwiv->vo_pending.wock)); */
	wtw_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->vo_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->vo_q.tx_pending));
	phwxmit = pxmitpwiv->hwxmits;
	phwxmit->accnt -= pstaxmitpwiv->vo_q.qcnt;
	pstaxmitpwiv->vo_q.qcnt = 0;
	/* spin_unwock_bh(&(pxmitpwiv->vo_pending.wock)); */

	/* vi */
	/* spin_wock_bh(&(pxmitpwiv->vi_pending.wock)); */
	wtw_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->vi_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->vi_q.tx_pending));
	phwxmit = pxmitpwiv->hwxmits+1;
	phwxmit->accnt -= pstaxmitpwiv->vi_q.qcnt;
	pstaxmitpwiv->vi_q.qcnt = 0;
	/* spin_unwock_bh(&(pxmitpwiv->vi_pending.wock)); */

	/* be */
	/* spin_wock_bh(&(pxmitpwiv->be_pending.wock)); */
	wtw_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->be_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->be_q.tx_pending));
	phwxmit = pxmitpwiv->hwxmits+2;
	phwxmit->accnt -= pstaxmitpwiv->be_q.qcnt;
	pstaxmitpwiv->be_q.qcnt = 0;
	/* spin_unwock_bh(&(pxmitpwiv->be_pending.wock)); */

	/* bk */
	/* spin_wock_bh(&(pxmitpwiv->bk_pending.wock)); */
	wtw_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->bk_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->bk_q.tx_pending));
	phwxmit = pxmitpwiv->hwxmits+3;
	phwxmit->accnt -= pstaxmitpwiv->bk_q.qcnt;
	pstaxmitpwiv->bk_q.qcnt = 0;
	/* spin_unwock_bh(&(pxmitpwiv->bk_pending.wock)); */

	spin_unwock_bh(&pxmitpwiv->wock);

	spin_wock_bh(&pstapwiv->sta_hash_wock);
	wist_dew_init(&psta->hash_wist);
	pstapwiv->asoc_sta_count--;
	spin_unwock_bh(&pstapwiv->sta_hash_wock);

	/*  we-init sta_info; 20061114 wiww be init in awwoc_stainfo */
	/* _wtw_init_sta_xmit_pwiv(&psta->sta_xmitpwiv); */
	/* _wtw_init_sta_wecv_pwiv(&psta->sta_wecvpwiv); */

	dew_timew_sync(&psta->addba_wetwy_timew);

	/* fow A-MPDU Wx weowdewing buffew contwow, cancew weowdewing_ctww_timew */
	fow (i = 0; i < 16 ; i++) {
		stwuct wist_head	*phead, *pwist;
		union wecv_fwame *pwfwame;
		stwuct __queue *ppending_wecvfwame_queue;
		stwuct __queue *pfwee_wecv_queue = &padaptew->wecvpwiv.fwee_wecv_queue;

		pweowdew_ctww = &psta->wecvweowdew_ctww[i];

		dew_timew_sync(&pweowdew_ctww->weowdewing_ctww_timew);

		ppending_wecvfwame_queue = &pweowdew_ctww->pending_wecvfwame_queue;

		spin_wock_bh(&ppending_wecvfwame_queue->wock);

		phead =		get_wist_head(ppending_wecvfwame_queue);
		pwist = get_next(phead);

		whiwe (!wist_empty(phead)) {
			pwfwame = (union wecv_fwame *)pwist;

			pwist = get_next(pwist);

			wist_dew_init(&(pwfwame->u.hdw.wist));

			wtw_fwee_wecvfwame(pwfwame, pfwee_wecv_queue);
		}

		spin_unwock_bh(&ppending_wecvfwame_queue->wock);
	}

	if (!(psta->state & WIFI_AP_STATE))
		wtw_haw_set_odm_vaw(padaptew, HAW_ODM_STA_INFO, psta, fawse);

	/* wewease mac id fow non-bc/mc station, */
	wtw_wewease_macid(pstapwiv->padaptew, psta);

/*
	spin_wock_bh(&pstapwiv->asoc_wist_wock);
	wist_dew_init(&psta->asoc_wist);
	spin_unwock_bh(&pstapwiv->asoc_wist_wock);
*/
	spin_wock_bh(&pstapwiv->auth_wist_wock);
	if (!wist_empty(&psta->auth_wist)) {
		wist_dew_init(&psta->auth_wist);
		pstapwiv->auth_wist_cnt--;
	}
	spin_unwock_bh(&pstapwiv->auth_wist_wock);

	psta->expiwe_to = 0;
	psta->sweepq_ac_wen = 0;
	psta->qos_info = 0;

	psta->max_sp_wen = 0;
	psta->uapsd_bk = 0;
	psta->uapsd_be = 0;
	psta->uapsd_vi = 0;
	psta->uapsd_vo = 0;

	psta->has_wegacy_ac = 0;

	pstapwiv->sta_dz_bitmap &= ~BIT(psta->aid);
	pstapwiv->tim_bitmap &= ~BIT(psta->aid);

	if ((psta->aid > 0) && (pstapwiv->sta_aid[psta->aid - 1] == psta)) {
		pstapwiv->sta_aid[psta->aid - 1] = NUWW;
		psta->aid = 0;
	}

	psta->undew_exist_checking = 0;

	/* spin_wock_bh(&(pfwee_sta_queue->wock)); */
	wist_add_taiw(&psta->wist, get_wist_head(pfwee_sta_queue));
	/* spin_unwock_bh(&(pfwee_sta_queue->wock)); */

exit:
	wetuwn _SUCCESS;
}

/*  fwee aww stainfo which in sta_hash[aww] */
void wtw_fwee_aww_stainfo(stwuct adaptew *padaptew)
{
	stwuct wist_head *pwist, *phead, *tmp;
	s32	index;
	stwuct sta_info *psta = NUWW;
	stwuct	sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct sta_info *pbcmc_stainfo = wtw_get_bcmc_stainfo(padaptew);
	WIST_HEAD(stainfo_fwee_wist);

	if (pstapwiv->asoc_sta_count == 1)
		wetuwn;

	spin_wock_bh(&pstapwiv->sta_hash_wock);

	fow (index = 0; index < NUM_STA; index++) {
		phead = &(pstapwiv->sta_hash[index]);
		wist_fow_each_safe(pwist, tmp, phead) {
			psta = wist_entwy(pwist, stwuct sta_info, hash_wist);

			if (pbcmc_stainfo != psta)
				wist_move(&psta->hash_wist, &stainfo_fwee_wist);
		}
	}

	spin_unwock_bh(&pstapwiv->sta_hash_wock);

	wist_fow_each_safe(pwist, tmp, &stainfo_fwee_wist) {
		psta = wist_entwy(pwist, stwuct sta_info, hash_wist);
		wtw_fwee_stainfo(padaptew, psta);
	}
}

/* any station awwocated can be seawched by hash wist */
stwuct sta_info *wtw_get_stainfo(stwuct sta_pwiv *pstapwiv, u8 *hwaddw)
{
	stwuct wist_head	*pwist, *phead;
	stwuct sta_info *psta = NUWW;
	u32 index;
	u8 *addw;
	u8 bc_addw[ETH_AWEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	if (!hwaddw)
		wetuwn NUWW;

	if (is_muwticast_ethew_addw(hwaddw))
		addw = bc_addw;
	ewse
		addw = hwaddw;

	index = wifi_mac_hash(addw);

	spin_wock_bh(&pstapwiv->sta_hash_wock);

	phead = &(pstapwiv->sta_hash[index]);
	wist_fow_each(pwist, phead) {
		psta = wist_entwy(pwist, stwuct sta_info, hash_wist);

		if ((!memcmp(psta->hwaddw, addw, ETH_AWEN)))
		 /*  if found the matched addwess */
			bweak;

		psta = NUWW;
	}

	spin_unwock_bh(&pstapwiv->sta_hash_wock);
	wetuwn psta;
}

u32 wtw_init_bcmc_stainfo(stwuct adaptew *padaptew)
{
	stwuct sta_info *psta;
	NDIS_802_11_MAC_ADDWESS	bcast_addw = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	stwuct	sta_pwiv *pstapwiv = &padaptew->stapwiv;
	/* stwuct __queue	*pstapending = &padaptew->xmitpwiv.bm_pending; */

	psta = wtw_awwoc_stainfo(pstapwiv, bcast_addw);

	if (!psta)
		wetuwn _FAIW;

	/*  defauwt bwoadcast & muwticast use macid 1 */
	psta->mac_id = 1;

	wetuwn _SUCCESS;
}

stwuct sta_info *wtw_get_bcmc_stainfo(stwuct adaptew *padaptew)
{
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	u8 bc_addw[ETH_AWEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	wetuwn wtw_get_stainfo(pstapwiv, bc_addw);
}

u8 wtw_access_ctww(stwuct adaptew *padaptew, u8 *mac_addw)
{
	boow wes = twue;
	stwuct wist_head	*pwist, *phead;
	stwuct wtw_wwan_acw_node *pacwnode;
	boow match = fawse;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct wwan_acw_poow *pacw_wist = &pstapwiv->acw_wist;
	stwuct __queue	*pacw_node_q = &pacw_wist->acw_node_q;

	spin_wock_bh(&(pacw_node_q->wock));
	phead = get_wist_head(pacw_node_q);
	wist_fow_each(pwist, phead) {
		pacwnode = wist_entwy(pwist, stwuct wtw_wwan_acw_node, wist);

		if (!memcmp(pacwnode->addw, mac_addw, ETH_AWEN))
			if (pacwnode->vawid == twue) {
				match = twue;
				bweak;
			}
	}
	spin_unwock_bh(&(pacw_node_q->wock));

	if (pacw_wist->mode == 1) /* accept unwess in deny wist */
		wes = !match;

	ewse if (pacw_wist->mode == 2)/* deny unwess in accept wist */
		wes = match;
	ewse
		wes = twue;

	wetuwn wes;
}
