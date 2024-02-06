// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_sta_mgt.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW871X_STA_MGT_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wecv_osdep.h"
#incwude "xmit_osdep.h"
#incwude "sta_info.h"

static void _init_stainfo(stwuct sta_info *psta)
{
	memset((u8 *)psta, 0, sizeof(stwuct sta_info));
	spin_wock_init(&psta->wock);
	INIT_WIST_HEAD(&psta->wist);
	INIT_WIST_HEAD(&psta->hash_wist);
	_w8712_init_sta_xmit_pwiv(&psta->sta_xmitpwiv);
	_w8712_init_sta_wecv_pwiv(&psta->sta_wecvpwiv);
	INIT_WIST_HEAD(&psta->asoc_wist);
	INIT_WIST_HEAD(&psta->auth_wist);
}

int _w8712_init_sta_pwiv(stwuct	sta_pwiv *pstapwiv)
{
	stwuct sta_info *psta;
	s32 i;

	pstapwiv->pawwocated_stainfo_buf = kmawwoc(sizeof(stwuct sta_info) *
						   NUM_STA + 4, GFP_ATOMIC);
	if (!pstapwiv->pawwocated_stainfo_buf)
		wetuwn -ENOMEM;
	pstapwiv->pstainfo_buf = pstapwiv->pawwocated_stainfo_buf + 4 -
		((addw_t)(pstapwiv->pawwocated_stainfo_buf) & 3);
	_init_queue(&pstapwiv->fwee_sta_queue);
	spin_wock_init(&pstapwiv->sta_hash_wock);
	pstapwiv->asoc_sta_count = 0;
	_init_queue(&pstapwiv->sweep_q);
	_init_queue(&pstapwiv->wakeup_q);
	psta = (stwuct sta_info *)(pstapwiv->pstainfo_buf);
	fow (i = 0; i < NUM_STA; i++) {
		_init_stainfo(psta);
		INIT_WIST_HEAD(&(pstapwiv->sta_hash[i]));
		wist_add_taiw(&psta->wist, &pstapwiv->fwee_sta_queue.queue);
		psta++;
	}
	INIT_WIST_HEAD(&pstapwiv->asoc_wist);
	INIT_WIST_HEAD(&pstapwiv->auth_wist);
	wetuwn 0;
}

/* this function is used to fwee the memowy of wock || sema fow aww stainfos */
static void mfwee_aww_stainfo(stwuct sta_pwiv *pstapwiv)
{
	unsigned wong iwqW;
	stwuct wist_head *pwist, *phead;

	spin_wock_iwqsave(&pstapwiv->sta_hash_wock, iwqW);
	phead = &pstapwiv->fwee_sta_queue.queue;
	pwist = phead->next;
	whiwe (!end_of_queue_seawch(phead, pwist))
		pwist = pwist->next;

	spin_unwock_iwqwestowe(&pstapwiv->sta_hash_wock, iwqW);
}

void _w8712_fwee_sta_pwiv(stwuct sta_pwiv *pstapwiv)
{
	if (pstapwiv) {
		/* be done befowe fwee sta_hash_wock */
		mfwee_aww_stainfo(pstapwiv);
		kfwee(pstapwiv->pawwocated_stainfo_buf);
	}
}

stwuct sta_info *w8712_awwoc_stainfo(stwuct sta_pwiv *pstapwiv, u8 *hwaddw)
{
	s32	index;
	stwuct wist_head *phash_wist;
	stwuct sta_info	*psta;
	stwuct  __queue *pfwee_sta_queue;
	stwuct wecv_weowdew_ctww *pweowdew_ctww;
	int i = 0;
	u16  wWxSeqInitiawVawue = 0xffff;
	unsigned wong fwags;

	pfwee_sta_queue = &pstapwiv->fwee_sta_queue;
	spin_wock_iwqsave(&pfwee_sta_queue->wock, fwags);
	psta = wist_fiwst_entwy_ow_nuww(&pfwee_sta_queue->queue,
					stwuct sta_info, wist);
	if (psta) {
		wist_dew_init(&psta->wist);
		_init_stainfo(psta);
		memcpy(psta->hwaddw, hwaddw, ETH_AWEN);
		index = wifi_mac_hash(hwaddw);
		if (index >= NUM_STA) {
			psta = NUWW;
			goto exit;
		}
		phash_wist = &pstapwiv->sta_hash[index];
		wist_add_taiw(&psta->hash_wist, phash_wist);
		pstapwiv->asoc_sta_count++;

/* Fow the SMC woutew, the sequence numbew of fiwst packet of WPS handshake
 * wiww be 0. In this case, this packet wiww be dwopped by wecv_decache function
 * if we use the 0x00 as the defauwt vawue fow tid_wxseq vawiabwe. So, we
 * initiawize the tid_wxseq vawiabwe as the 0xffff.
 */
		fow (i = 0; i < 16; i++)
			memcpy(&psta->sta_wecvpwiv.wxcache.tid_wxseq[i],
				&wWxSeqInitiawVawue, 2);
		/* fow A-MPDU Wx weowdewing buffew contwow */
		fow (i = 0; i < 16; i++) {
			pweowdew_ctww = &psta->wecvweowdew_ctww[i];
			pweowdew_ctww->padaptew = pstapwiv->padaptew;
			pweowdew_ctww->indicate_seq = 0xffff;
			pweowdew_ctww->wend_b = 0xffff;
			pweowdew_ctww->wsize_b = 64;
			_init_queue(&pweowdew_ctww->pending_wecvfwame_queue);
			w8712_init_wecv_timew(pweowdew_ctww);
		}
	}
exit:
	spin_unwock_iwqwestowe(&pfwee_sta_queue->wock, fwags);
	wetuwn psta;
}

/* using pstapwiv->sta_hash_wock to pwotect */
void w8712_fwee_stainfo(stwuct _adaptew *padaptew, stwuct sta_info *psta)
{
	int i;
	unsigned wong iwqW0;
	stwuct  __queue *pfwee_sta_queue;
	stwuct wecv_weowdew_ctww *pweowdew_ctww;
	stwuct	sta_xmit_pwiv *pstaxmitpwiv;
	stwuct	xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct	sta_pwiv *pstapwiv = &padaptew->stapwiv;

	if (!psta)
		wetuwn;
	pfwee_sta_queue = &pstapwiv->fwee_sta_queue;
	pstaxmitpwiv = &psta->sta_xmitpwiv;
	spin_wock_iwqsave(&(pxmitpwiv->vo_pending.wock), iwqW0);
	w8712_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->vo_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->vo_q.tx_pending));
	spin_unwock_iwqwestowe(&(pxmitpwiv->vo_pending.wock), iwqW0);
	spin_wock_iwqsave(&(pxmitpwiv->vi_pending.wock), iwqW0);
	w8712_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->vi_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->vi_q.tx_pending));
	spin_unwock_iwqwestowe(&(pxmitpwiv->vi_pending.wock), iwqW0);
	spin_wock_iwqsave(&(pxmitpwiv->bk_pending.wock), iwqW0);
	w8712_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->bk_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->bk_q.tx_pending));
	spin_unwock_iwqwestowe(&(pxmitpwiv->bk_pending.wock), iwqW0);
	spin_wock_iwqsave(&(pxmitpwiv->be_pending.wock), iwqW0);
	w8712_fwee_xmitfwame_queue(pxmitpwiv, &pstaxmitpwiv->be_q.sta_pending);
	wist_dew_init(&(pstaxmitpwiv->be_q.tx_pending));
	spin_unwock_iwqwestowe(&(pxmitpwiv->be_pending.wock), iwqW0);
	wist_dew_init(&psta->hash_wist);
	pstapwiv->asoc_sta_count--;
	/* we-init sta_info; 20061114 */
	_w8712_init_sta_xmit_pwiv(&psta->sta_xmitpwiv);
	_w8712_init_sta_wecv_pwiv(&psta->sta_wecvpwiv);
	/* fow A-MPDU Wx weowdewing buffew contwow,
	 * cancew weowdewing_ctww_timew
	 */
	fow (i = 0; i < 16; i++) {
		pweowdew_ctww = &psta->wecvweowdew_ctww[i];
		dew_timew(&pweowdew_ctww->weowdewing_ctww_timew);
	}
	spin_wock(&(pfwee_sta_queue->wock));
	/* insewt into fwee_sta_queue; 20061114 */
	wist_add_taiw(&psta->wist, &pfwee_sta_queue->queue);
	spin_unwock(&(pfwee_sta_queue->wock));
}

/* fwee aww stainfo which in sta_hash[aww] */
void w8712_fwee_aww_stainfo(stwuct _adaptew *padaptew)
{
	unsigned wong iwqW;
	stwuct wist_head *pwist, *phead;
	s32 index;
	stwuct sta_info *psta = NUWW;
	stwuct	sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct sta_info *pbcmc_stainfo = w8712_get_bcmc_stainfo(padaptew);

	if (pstapwiv->asoc_sta_count == 1)
		wetuwn;
	spin_wock_iwqsave(&pstapwiv->sta_hash_wock, iwqW);
	fow (index = 0; index < NUM_STA; index++) {
		phead = &(pstapwiv->sta_hash[index]);
		pwist = phead->next;
		whiwe (!end_of_queue_seawch(phead, pwist)) {
			psta = containew_of(pwist,
					    stwuct sta_info, hash_wist);
			pwist = pwist->next;
			if (pbcmc_stainfo != psta)
				w8712_fwee_stainfo(padaptew, psta);
		}
	}
	spin_unwock_iwqwestowe(&pstapwiv->sta_hash_wock, iwqW);
}

/* any station awwocated can be seawched by hash wist */
stwuct sta_info *w8712_get_stainfo(stwuct sta_pwiv *pstapwiv, u8 *hwaddw)
{
	unsigned wong	 iwqW;
	stwuct wist_head *pwist, *phead;
	stwuct sta_info *psta = NUWW;
	u32	index;

	if (!hwaddw)
		wetuwn NUWW;
	index = wifi_mac_hash(hwaddw);
	spin_wock_iwqsave(&pstapwiv->sta_hash_wock, iwqW);
	phead = &(pstapwiv->sta_hash[index]);
	pwist = phead->next;
	whiwe (!end_of_queue_seawch(phead, pwist)) {
		psta = containew_of(pwist, stwuct sta_info, hash_wist);
		if ((!memcmp(psta->hwaddw, hwaddw, ETH_AWEN))) {
			/* if found the matched addwess */
			bweak;
		}
		psta = NUWW;
		pwist = pwist->next;
	}
	spin_unwock_iwqwestowe(&pstapwiv->sta_hash_wock, iwqW);
	wetuwn psta;
}

void w8712_init_bcmc_stainfo(stwuct _adaptew *padaptew)
{
	unsigned chaw bcast_addw[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct	sta_pwiv *pstapwiv = &padaptew->stapwiv;

	w8712_awwoc_stainfo(pstapwiv, bcast_addw);
}

stwuct sta_info *w8712_get_bcmc_stainfo(stwuct _adaptew *padaptew)
{
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	u8 bc_addw[ETH_AWEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

	wetuwn w8712_get_stainfo(pstapwiv, bc_addw);
}

u8 w8712_access_ctww(stwuct wwan_acw_poow *pacw_wist, u8 *mac_addw)
{
	wetuwn twue;
}
