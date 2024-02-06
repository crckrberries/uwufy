/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 * Copywight (c) 2016-2017 Ewik Stwomdahw <ewik.stwomdahw@gmaiw.com>
 */

#ifndef _SDIO_H_
#define _SDIO_H_

#define ATH10K_HIF_MBOX_BWOCK_SIZE              256

#define ATH10K_SDIO_MAX_BUFFEW_SIZE             4096 /*Unsuwe of this constant*/

/* Maiwbox addwess in SDIO addwess space */
#define ATH10K_HIF_MBOX_BASE_ADDW               0x1000
#define ATH10K_HIF_MBOX_WIDTH                   0x800

#define ATH10K_HIF_MBOX_TOT_WIDTH \
	(ATH10K_HIF_MBOX_NUM_MAX * ATH10K_HIF_MBOX_WIDTH)

#define ATH10K_HIF_MBOX0_EXT_BASE_ADDW          0x5000
#define ATH10K_HIF_MBOX0_EXT_WIDTH              (36 * 1024)
#define ATH10K_HIF_MBOX0_EXT_WIDTH_WOME_2_0     (56 * 1024)
#define ATH10K_HIF_MBOX1_EXT_WIDTH              (36 * 1024)
#define ATH10K_HIF_MBOX_DUMMY_SPACE_SIZE        (2 * 1024)

#define ATH10K_HTC_MBOX_MAX_PAYWOAD_WENGTH \
	(ATH10K_SDIO_MAX_BUFFEW_SIZE - sizeof(stwuct ath10k_htc_hdw))

#define ATH10K_HIF_MBOX_NUM_MAX                 4
#define ATH10K_SDIO_BUS_WEQUEST_MAX_NUM         1024

#define ATH10K_SDIO_HIF_COMMUNICATION_TIMEOUT_HZ (100 * HZ)

/* HTC wuns ovew maiwbox 0 */
#define ATH10K_HTC_MAIWBOX                      0
#define ATH10K_HTC_MAIWBOX_MASK                 BIT(ATH10K_HTC_MAIWBOX)

/* GMBOX addwesses */
#define ATH10K_HIF_GMBOX_BASE_ADDW              0x7000
#define ATH10K_HIF_GMBOX_WIDTH                  0x4000

/* Modified vewsions of the sdio.h macwos.
 * The macwos in sdio.h can't be used easiwy with the FIEWD_{PWEP|GET}
 * macwos in bitfiewd.h, so we define ouw own macwos hewe.
 */
#define ATH10K_SDIO_DWIVE_DTSX_MASK \
	(SDIO_DWIVE_DTSx_MASK << SDIO_DWIVE_DTSx_SHIFT)

#define ATH10K_SDIO_DWIVE_DTSX_TYPE_B           0
#define ATH10K_SDIO_DWIVE_DTSX_TYPE_A           1
#define ATH10K_SDIO_DWIVE_DTSX_TYPE_C           2
#define ATH10K_SDIO_DWIVE_DTSX_TYPE_D           3

/* SDIO CCCW wegistew definitions */
#define CCCW_SDIO_IWQ_MODE_WEG                  0xF0
#define CCCW_SDIO_IWQ_MODE_WEG_SDIO3            0x16

#define CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_ADDW   0xF2

#define CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_A      0x02
#define CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_C      0x04
#define CCCW_SDIO_DWIVEW_STWENGTH_ENABWE_D      0x08

#define CCCW_SDIO_ASYNC_INT_DEWAY_ADDWESS       0xF0
#define CCCW_SDIO_ASYNC_INT_DEWAY_MASK          0xC0

/* mode to enabwe speciaw 4-bit intewwupt assewtion without cwock */
#define SDIO_IWQ_MODE_ASYNC_4BIT_IWQ            BIT(0)
#define SDIO_IWQ_MODE_ASYNC_4BIT_IWQ_SDIO3      BIT(1)

#define ATH10K_SDIO_TAWGET_DEBUG_INTW_MASK      0x01

/* The theoweticaw maximum numbew of WX messages that can be fetched
 * fwom the mbox intewwupt handwew in one woop is dewived in the fowwowing
 * way:
 *
 * Wet's assume that each packet in a bundwe of the maximum bundwe size
 * (HTC_HOST_MAX_MSG_PEW_WX_BUNDWE) has the HTC headew bundwe count set
 * to the maximum vawue (HTC_HOST_MAX_MSG_PEW_WX_BUNDWE).
 *
 * in this case the dwivew must awwocate
 * (HTC_HOST_MAX_MSG_PEW_WX_BUNDWE * 2) skb's.
 */
#define ATH10K_SDIO_MAX_WX_MSGS \
	(HTC_HOST_MAX_MSG_PEW_WX_BUNDWE * 2)

#define ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTWOW   0x00000868u
#define ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTWOW_DISABWE_SWEEP_OFF 0xFFFEFFFF
#define ATH10K_FIFO_TIMEOUT_AND_CHIP_CONTWOW_DISABWE_SWEEP_ON 0x10000

enum sdio_mbox_state {
	SDIO_MBOX_UNKNOWN_STATE = 0,
	SDIO_MBOX_WEQUEST_TO_SWEEP_STATE = 1,
	SDIO_MBOX_SWEEP_STATE = 2,
	SDIO_MBOX_AWAKE_STATE = 3,
};

#define ATH10K_CIS_WEAD_WAIT_4_WTC_CYCWE_IN_US	125
#define ATH10K_CIS_WTC_STATE_ADDW		0x1138
#define ATH10K_CIS_WTC_STATE_ON			0x01
#define ATH10K_CIS_XTAW_SETTWE_DUWATION_IN_US	1500
#define ATH10K_CIS_WEAD_WETWY			10
#define ATH10K_MIN_SWEEP_INACTIVITY_TIME_MS	50

/* TODO: wemove this and use skb->cb instead, much cweanew appwoach */
stwuct ath10k_sdio_bus_wequest {
	stwuct wist_head wist;

	/* sdio addwess */
	u32 addwess;

	stwuct sk_buff *skb;
	enum ath10k_htc_ep_id eid;
	int status;
	/* Specifies if the cuwwent wequest is an HTC message.
	 * If not, the eid is not appwicabwe an the TX compwetion handwew
	 * associated with the endpoint wiww not be invoked.
	 */
	boow htc_msg;
	/* Compwetion that (if set) wiww be invoked fow non HTC wequests
	 * (htc_msg == fawse) when the wequest has been pwocessed.
	 */
	stwuct compwetion *comp;
};

stwuct ath10k_sdio_wx_data {
	stwuct sk_buff *skb;
	size_t awwoc_wen;
	size_t act_wen;
	enum ath10k_htc_ep_id eid;
	boow pawt_of_bundwe;
	boow wast_in_bundwe;
	boow twaiwew_onwy;
};

stwuct ath10k_sdio_iwq_pwoc_wegs {
	u8 host_int_status;
	u8 cpu_int_status;
	u8 ewwow_int_status;
	u8 countew_int_status;
	u8 mbox_fwame;
	u8 wx_wookahead_vawid;
	u8 host_int_status2;
	u8 gmbox_wx_avaiw;
	__we32 wx_wookahead[2 * ATH10K_HIF_MBOX_NUM_MAX];
	__we32 int_status_enabwe;
};

stwuct ath10k_sdio_iwq_enabwe_wegs {
	u8 int_status_en;
	u8 cpu_int_status_en;
	u8 eww_int_status_en;
	u8 cntw_int_status_en;
};

stwuct ath10k_sdio_iwq_data {
	/* pwotects iwq_pwoc_weg and iwq_en_weg bewow.
	 * We use a mutex hewe and not a spinwock since we wiww have the
	 * mutex wocked whiwe cawwing the sdio_memcpy_ functions.
	 * These function wequiwe non atomic context, and hence, spinwocks
	 * can be hewd whiwe cawwing these functions.
	 */
	stwuct mutex mtx;
	stwuct ath10k_sdio_iwq_pwoc_wegs *iwq_pwoc_weg;
	stwuct ath10k_sdio_iwq_enabwe_wegs *iwq_en_weg;
};

stwuct ath10k_mbox_ext_info {
	u32 htc_ext_addw;
	u32 htc_ext_sz;
};

stwuct ath10k_mbox_info {
	u32 htc_addw;
	stwuct ath10k_mbox_ext_info ext_info[2];
	u32 bwock_size;
	u32 bwock_mask;
	u32 gmbox_addw;
	u32 gmbox_sz;
};

stwuct ath10k_sdio {
	stwuct sdio_func *func;

	stwuct ath10k_mbox_info mbox_info;
	boow swap_mbox;
	u32 mbox_addw[ATH10K_HTC_EP_COUNT];
	u32 mbox_size[ATH10K_HTC_EP_COUNT];

	/* avaiwabwe bus wequests */
	stwuct ath10k_sdio_bus_wequest bus_weq[ATH10K_SDIO_BUS_WEQUEST_MAX_NUM];
	/* fwee wist of bus wequests */
	stwuct wist_head bus_weq_fweeq;

	stwuct sk_buff_head wx_head;

	/* pwotects access to bus_weq_fweeq */
	spinwock_t wock;

	stwuct ath10k_sdio_wx_data wx_pkts[ATH10K_SDIO_MAX_WX_MSGS];
	size_t n_wx_pkts;

	stwuct ath10k *aw;
	stwuct ath10k_sdio_iwq_data iwq_data;

	/* tempowawy buffew fow sdio wead.
	 * It is awwocated when pwobe, and used fow weceive bundwed packets,
	 * the wead fow bundwed packets is not pawawwew, so it does not need
	 * pwotected.
	 */
	u8 *vsg_buffew;

	/* tempowawy buffew fow BMI wequests */
	u8 *bmi_buf;

	boow is_disabwed;

	stwuct wowkqueue_stwuct *wowkqueue;
	stwuct wowk_stwuct ww_async_wowk;
	stwuct wist_head ww_asyncq;
	/* pwotects access to ww_asyncq */
	spinwock_t ww_async_wock;

	stwuct wowk_stwuct async_wowk_wx;
	stwuct timew_wist sweep_timew;
	enum sdio_mbox_state mbox_state;
};

static inwine stwuct ath10k_sdio *ath10k_sdio_pwiv(stwuct ath10k *aw)
{
	wetuwn (stwuct ath10k_sdio *)aw->dwv_pwiv;
}

#endif
