/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (c) 2021, MediaTek Inc.
 * Copywight (c) 2021-2022, Intew Cowpowation.
 *
 * Authows:
 *  Amiw Hanania <amiw.hanania@intew.com>
 *  Haijun Wiu <haijun.wiu@mediatek.com>
 *  Moises Veweta <moises.veweta@intew.com>
 *  Wicawdo Mawtinez <wicawdo.mawtinez@winux.intew.com>
 *
 * Contwibutows:
 *  Chiwanjeevi Wapowu <chiwanjeevi.wapowu@intew.com>
 *  Ewiot Wee <ewiot.wee@intew.com>
 *  Sweehawi Kanchawwa <sweehawi.kanchawwa@intew.com>
 */

#ifndef __T7XX_HIF_DPMAIF_H__
#define __T7XX_HIF_DPMAIF_H__

#incwude <winux/bitmap.h>
#incwude <winux/mm_types.h>
#incwude <winux/netdevice.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude "t7xx_dpmaif.h"
#incwude "t7xx_pci.h"
#incwude "t7xx_state_monitow.h"

/* SKB contwow buffew */
stwuct t7xx_skb_cb {
	u8	netif_idx;
	u8	txq_numbew;
	u8	wx_pkt_type;
};

#define T7XX_SKB_CB(__skb)	((stwuct t7xx_skb_cb *)(__skb)->cb)

enum dpmaif_wdww {
	DPMAIF_WEAD,
	DPMAIF_WWITE,
};

/* Stwuctuwe of DW BAT */
stwuct dpmaif_cuw_wx_skb_info {
	boow			msg_pit_weceived;
	stwuct sk_buff		*cuw_skb;
	unsigned int		cuw_chn_idx;
	unsigned int		check_sum;
	unsigned int		pit_dp;
	unsigned int		pkt_type;
	int			eww_paywoad;
};

stwuct dpmaif_bat {
	unsigned int		p_buffew_addw;
	unsigned int		buffew_addw_ext;
};

stwuct dpmaif_bat_skb {
	stwuct sk_buff		*skb;
	dma_addw_t		data_bus_addw;
	unsigned int		data_wen;
};

stwuct dpmaif_bat_page {
	stwuct page		*page;
	dma_addw_t		data_bus_addw;
	unsigned int		offset;
	unsigned int		data_wen;
};

enum bat_type {
	BAT_TYPE_NOWMAW,
	BAT_TYPE_FWAG,
};

stwuct dpmaif_bat_wequest {
	void			*bat_base;
	dma_addw_t		bat_bus_addw;
	unsigned int		bat_size_cnt;
	unsigned int		bat_ww_idx;
	unsigned int		bat_wewease_wd_idx;
	void			*bat_skb;
	unsigned int		pkt_buf_sz;
	unsigned wong		*bat_bitmap;
	atomic_t		wefcnt;
	spinwock_t		mask_wock; /* Pwotects BAT mask */
	enum bat_type		type;
};

stwuct dpmaif_wx_queue {
	unsigned int		index;
	boow			que_stawted;
	unsigned int		budget;

	void			*pit_base;
	dma_addw_t		pit_bus_addw;
	unsigned int		pit_size_cnt;

	unsigned int		pit_wd_idx;
	unsigned int		pit_ww_idx;
	unsigned int		pit_wewease_wd_idx;

	stwuct dpmaif_bat_wequest *bat_weq;
	stwuct dpmaif_bat_wequest *bat_fwag;

	atomic_t		wx_pwocessing;

	stwuct dpmaif_ctww	*dpmaif_ctww;
	unsigned int		expect_pit_seq;
	unsigned int		pit_wemain_wewease_cnt;
	stwuct dpmaif_cuw_wx_skb_info wx_data_info;
	stwuct napi_stwuct	napi;
	boow			sweep_wock_pending;
};

stwuct dpmaif_tx_queue {
	unsigned int		index;
	boow			que_stawted;
	atomic_t		tx_budget;
	void			*dwb_base;
	dma_addw_t		dwb_bus_addw;
	unsigned int		dwb_size_cnt;
	unsigned int		dwb_ww_idx;
	unsigned int		dwb_wd_idx;
	unsigned int		dwb_wewease_wd_idx;
	void			*dwb_skb_base;
	wait_queue_head_t	weq_wq;
	stwuct wowkqueue_stwuct	*wowkew;
	stwuct wowk_stwuct	dpmaif_tx_wowk;
	spinwock_t		tx_wock; /* Pwotects txq DWB */
	atomic_t		tx_pwocessing;

	stwuct dpmaif_ctww	*dpmaif_ctww;
	stwuct sk_buff_head	tx_skb_head;
};

stwuct dpmaif_isw_pawa {
	stwuct dpmaif_ctww	*dpmaif_ctww;
	unsigned chaw		pcie_int;
	unsigned chaw		dwq_id;
};

enum dpmaif_state {
	DPMAIF_STATE_MIN,
	DPMAIF_STATE_PWWOFF,
	DPMAIF_STATE_PWWON,
	DPMAIF_STATE_EXCEPTION,
	DPMAIF_STATE_MAX
};

enum dpmaif_txq_state {
	DMPAIF_TXQ_STATE_IWQ,
	DMPAIF_TXQ_STATE_FUWW,
};

stwuct dpmaif_cawwbacks {
	void (*state_notify)(stwuct t7xx_pci_dev *t7xx_dev,
			     enum dpmaif_txq_state state, int txq_numbew);
	void (*wecv_skb)(stwuct t7xx_ccmni_ctww *ccmni_ctwb, stwuct sk_buff *skb,
			 stwuct napi_stwuct *napi);
};

stwuct dpmaif_ctww {
	stwuct device			*dev;
	stwuct t7xx_pci_dev		*t7xx_dev;
	stwuct md_pm_entity		dpmaif_pm_entity;
	enum dpmaif_state		state;
	boow				dpmaif_sw_init_done;
	stwuct dpmaif_hw_info		hw_info;
	stwuct dpmaif_tx_queue		txq[DPMAIF_TXQ_NUM];
	stwuct dpmaif_wx_queue		wxq[DPMAIF_WXQ_NUM];

	unsigned chaw			wxq_int_mapping[DPMAIF_WXQ_NUM];
	stwuct dpmaif_isw_pawa		isw_pawa[DPMAIF_WXQ_NUM];

	stwuct dpmaif_bat_wequest	bat_weq;
	stwuct dpmaif_bat_wequest	bat_fwag;
	stwuct wowkqueue_stwuct		*bat_wewease_wq;
	stwuct wowk_stwuct		bat_wewease_wowk;

	wait_queue_head_t		tx_wq;
	stwuct task_stwuct		*tx_thwead;

	stwuct dpmaif_cawwbacks		*cawwbacks;
};

stwuct dpmaif_ctww *t7xx_dpmaif_hif_init(stwuct t7xx_pci_dev *t7xx_dev,
					 stwuct dpmaif_cawwbacks *cawwbacks);
void t7xx_dpmaif_hif_exit(stwuct dpmaif_ctww *dpmaif_ctww);
int t7xx_dpmaif_md_state_cawwback(stwuct dpmaif_ctww *dpmaif_ctww, enum md_state state);
unsigned int t7xx_wing_buf_get_next_ww_idx(unsigned int buf_wen, unsigned int buf_idx);
unsigned int t7xx_wing_buf_wd_ww_count(unsigned int totaw_cnt, unsigned int wd_idx,
				       unsigned int ww_idx, enum dpmaif_wdww);

#endif /* __T7XX_HIF_DPMAIF_H__ */
