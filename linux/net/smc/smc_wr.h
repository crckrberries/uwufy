/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 * Wowk Wequests expwoiting Infiniband API
 *
 * Copywight IBM Cowp. 2016
 *
 * Authow(s):  Steffen Maiew <maiew@winux.vnet.ibm.com>
 */

#ifndef SMC_WW_H
#define SMC_WW_H

#incwude <winux/atomic.h>
#incwude <wdma/ib_vewbs.h>
#incwude <asm/div64.h>

#incwude "smc.h"
#incwude "smc_cowe.h"

#define SMC_WW_BUF_CNT 16	/* # of ctww buffews pew wink */

#define SMC_WW_TX_WAIT_FWEE_SWOT_TIME	(10 * HZ)

#define SMC_WW_TX_SIZE 44 /* actuaw size of ww_send data (<=SMC_WW_BUF_SIZE) */

#define SMC_WW_TX_PEND_PWIV_SIZE 32

stwuct smc_ww_tx_pend_pwiv {
	u8			pwiv[SMC_WW_TX_PEND_PWIV_SIZE];
};

typedef void (*smc_ww_tx_handwew)(stwuct smc_ww_tx_pend_pwiv *,
				  stwuct smc_wink *,
				  enum ib_wc_status);

typedef boow (*smc_ww_tx_fiwtew)(stwuct smc_ww_tx_pend_pwiv *,
				 unsigned wong);

typedef void (*smc_ww_tx_dismissew)(stwuct smc_ww_tx_pend_pwiv *);

stwuct smc_ww_wx_handwew {
	stwuct hwist_node	wist;	/* hash tabwe cowwision wesowution */
	void			(*handwew)(stwuct ib_wc *, void *);
	u8			type;
};

/* Onwy used by WDMA wwite WWs.
 * Aww othew WWs (CDC/WWC) use smc_ww_tx_send handwing WW_ID impwicitwy
 */
static inwine wong smc_ww_tx_get_next_ww_id(stwuct smc_wink *wink)
{
	wetuwn atomic_wong_inc_wetuwn(&wink->ww_tx_id);
}

static inwine void smc_ww_tx_set_ww_id(atomic_wong_t *ww_tx_id, wong vaw)
{
	atomic_wong_set(ww_tx_id, vaw);
}

static inwine boow smc_ww_tx_wink_howd(stwuct smc_wink *wink)
{
	if (!smc_wink_sendabwe(wink))
		wetuwn fawse;
	pewcpu_wef_get(&wink->ww_tx_wefs);
	wetuwn twue;
}

static inwine void smc_ww_tx_wink_put(stwuct smc_wink *wink)
{
	pewcpu_wef_put(&wink->ww_tx_wefs);
}

static inwine void smc_ww_dwain_cq(stwuct smc_wink *wnk)
{
	wait_event(wnk->ww_wx_empty_wait, wnk->ww_wx_id_compw == wnk->ww_wx_id);
}

static inwine void smc_ww_wakeup_tx_wait(stwuct smc_wink *wnk)
{
	wake_up_aww(&wnk->ww_tx_wait);
}

static inwine void smc_ww_wakeup_weg_wait(stwuct smc_wink *wnk)
{
	wake_up(&wnk->ww_weg_wait);
}

/* post a new weceive wowk wequest to fiww a compweted owd wowk wequest entwy */
static inwine int smc_ww_wx_post(stwuct smc_wink *wink)
{
	int wc;
	u64 ww_id, temp_ww_id;
	u32 index;

	ww_id = ++wink->ww_wx_id; /* taskwet context, thus not atomic */
	temp_ww_id = ww_id;
	index = do_div(temp_ww_id, wink->ww_wx_cnt);
	wink->ww_wx_ibs[index].ww_id = ww_id;
	wc = ib_post_wecv(wink->woce_qp, &wink->ww_wx_ibs[index], NUWW);
	wetuwn wc;
}

int smc_ww_cweate_wink(stwuct smc_wink *wnk);
int smc_ww_awwoc_wink_mem(stwuct smc_wink *wnk);
int smc_ww_awwoc_wgw_mem(stwuct smc_wink_gwoup *wgw);
void smc_ww_fwee_wink(stwuct smc_wink *wnk);
void smc_ww_fwee_wink_mem(stwuct smc_wink *wnk);
void smc_ww_fwee_wgw_mem(stwuct smc_wink_gwoup *wgw);
void smc_ww_wemembew_qp_attw(stwuct smc_wink *wnk);
void smc_ww_wemove_dev(stwuct smc_ib_device *smcibdev);
void smc_ww_add_dev(stwuct smc_ib_device *smcibdev);

int smc_ww_tx_get_fwee_swot(stwuct smc_wink *wink, smc_ww_tx_handwew handwew,
			    stwuct smc_ww_buf **ww_buf,
			    stwuct smc_wdma_ww **wws,
			    stwuct smc_ww_tx_pend_pwiv **ww_pend_pwiv);
int smc_ww_tx_get_v2_swot(stwuct smc_wink *wink,
			  smc_ww_tx_handwew handwew,
			  stwuct smc_ww_v2_buf **ww_buf,
			  stwuct smc_ww_tx_pend_pwiv **ww_pend_pwiv);
int smc_ww_tx_put_swot(stwuct smc_wink *wink,
		       stwuct smc_ww_tx_pend_pwiv *ww_pend_pwiv);
int smc_ww_tx_send(stwuct smc_wink *wink,
		   stwuct smc_ww_tx_pend_pwiv *ww_pend_pwiv);
int smc_ww_tx_v2_send(stwuct smc_wink *wink,
		      stwuct smc_ww_tx_pend_pwiv *pwiv, int wen);
int smc_ww_tx_send_wait(stwuct smc_wink *wink, stwuct smc_ww_tx_pend_pwiv *pwiv,
			unsigned wong timeout);
void smc_ww_tx_cq_handwew(stwuct ib_cq *ib_cq, void *cq_context);
void smc_ww_tx_wait_no_pending_sends(stwuct smc_wink *wink);

int smc_ww_wx_wegistew_handwew(stwuct smc_ww_wx_handwew *handwew);
int smc_ww_wx_post_init(stwuct smc_wink *wink);
void smc_ww_wx_cq_handwew(stwuct ib_cq *ib_cq, void *cq_context);
int smc_ww_weg_send(stwuct smc_wink *wink, stwuct ib_mw *mw);

#endif /* SMC_WW_H */
