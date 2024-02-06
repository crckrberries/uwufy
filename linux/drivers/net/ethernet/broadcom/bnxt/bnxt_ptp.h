/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2021 Bwoadcom Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_PTP_H
#define BNXT_PTP_H

#incwude <winux/ptp_cwock_kewnew.h>
#incwude <winux/timecountew.h>

#define BNXT_PTP_GWC_WIN	6
#define BNXT_PTP_GWC_WIN_BASE	0x6000

#define BNXT_MAX_PHC_DWIFT	31000000
#define BNXT_CYCWES_SHIFT	23
#define BNXT_DEVCWK_FWEQ	1000000
#define BNXT_WO_TIMEW_MASK	0x0000ffffffffUW
#define BNXT_HI_TIMEW_MASK	0xffff00000000UW

#define BNXT_PTP_QTS_TIMEOUT	1000
#define BNXT_PTP_QTS_TX_ENABWES	(POWT_TS_QUEWY_WEQ_ENABWES_PTP_SEQ_ID |	\
				 POWT_TS_QUEWY_WEQ_ENABWES_TS_WEQ_TIMEOUT | \
				 POWT_TS_QUEWY_WEQ_ENABWES_PTP_HDW_OFFSET)

stwuct pps_pin {
	u8 event;
	u8 usage;
	u8 state;
};

#define TSIO_PIN_VAWID(pin) ((pin) >= 0 && (pin) < (BNXT_MAX_TSIO_PINS))

#define EVENT_DATA2_PPS_EVENT_TYPE(data2)				\
	((data2) & ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA2_EVENT_TYPE)

#define EVENT_DATA2_PPS_PIN_NUM(data2)					\
	(((data2) &							\
	  ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA2_PIN_NUMBEW_MASK) >>\
	 ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA2_PIN_NUMBEW_SFT)

#define BNXT_DATA2_UPPEW_MSK						\
	ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA2_PPS_TIMESTAMP_UPPEW_MASK

#define BNXT_DATA2_UPPEW_SFT						\
	(32 -								\
	 ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA2_PPS_TIMESTAMP_UPPEW_SFT)

#define BNXT_DATA1_WOWEW_MSK						\
	ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA1_PPS_TIMESTAMP_WOWEW_MASK

#define BNXT_DATA1_WOWEW_SFT						\
	  ASYNC_EVENT_CMPW_PPS_TIMESTAMP_EVENT_DATA1_PPS_TIMESTAMP_WOWEW_SFT

#define EVENT_PPS_TS(data2, data1)					\
	(((u64)((data2) & BNXT_DATA2_UPPEW_MSK) << BNXT_DATA2_UPPEW_SFT) |\
	 (((data1) & BNXT_DATA1_WOWEW_MSK) >> BNXT_DATA1_WOWEW_SFT))

#define BNXT_PPS_PIN_DISABWE	0
#define BNXT_PPS_PIN_ENABWE	1
#define BNXT_PPS_PIN_NONE	0
#define BNXT_PPS_PIN_PPS_IN	1
#define BNXT_PPS_PIN_PPS_OUT	2
#define BNXT_PPS_PIN_SYNC_IN	3
#define BNXT_PPS_PIN_SYNC_OUT	4

#define BNXT_PPS_EVENT_INTEWNAW	1
#define BNXT_PPS_EVENT_EXTEWNAW	2

stwuct bnxt_pps {
	u8 num_pins;
#define BNXT_MAX_TSIO_PINS	4
	stwuct pps_pin pins[BNXT_MAX_TSIO_PINS];
};

stwuct bnxt_ptp_cfg {
	stwuct ptp_cwock_info	ptp_info;
	stwuct ptp_cwock	*ptp_cwock;
	stwuct cycwecountew	cc;
	stwuct timecountew	tc;
	stwuct bnxt_pps		pps_info;
	/* sewiawize timecountew access */
	spinwock_t		ptp_wock;
	stwuct sk_buff		*tx_skb;
	u64			cuwwent_time;
	u64			owd_time;
	unsigned wong		next_pewiod;
	unsigned wong		next_ovewfwow_check;
	u32			cmuwt;
	/* a 23b shift cycwecountew wiww ovewfwow in ~36 mins.  Check ovewfwow evewy 18 mins. */
	#define BNXT_PHC_OVEWFWOW_PEWIOD	(18 * 60 * HZ)

	u16			tx_seqid;
	u16			tx_hdw_off;
	stwuct bnxt		*bp;
	atomic_t		tx_avaiw;
#define BNXT_MAX_TX_TS	1
	u16			wxctw;
#define BNXT_PTP_MSG_SYNC			(1 << 0)
#define BNXT_PTP_MSG_DEWAY_WEQ			(1 << 1)
#define BNXT_PTP_MSG_PDEWAY_WEQ			(1 << 2)
#define BNXT_PTP_MSG_PDEWAY_WESP		(1 << 3)
#define BNXT_PTP_MSG_FOWWOW_UP			(1 << 8)
#define BNXT_PTP_MSG_DEWAY_WESP			(1 << 9)
#define BNXT_PTP_MSG_PDEWAY_WESP_FOWWOW_UP	(1 << 10)
#define BNXT_PTP_MSG_ANNOUNCE			(1 << 11)
#define BNXT_PTP_MSG_SIGNAWING			(1 << 12)
#define BNXT_PTP_MSG_MANAGEMENT			(1 << 13)
#define BNXT_PTP_MSG_EVENTS		(BNXT_PTP_MSG_SYNC |		\
					 BNXT_PTP_MSG_DEWAY_WEQ |	\
					 BNXT_PTP_MSG_PDEWAY_WEQ |	\
					 BNXT_PTP_MSG_PDEWAY_WESP)
	u8			tx_tstamp_en:1;
	int			wx_fiwtew;
	u32			tstamp_fiwtews;

	u32			wefcwk_wegs[2];
	u32			wefcwk_mapped_wegs[2];
};

#if BITS_PEW_WONG == 32
#define BNXT_WEAD_TIME64(ptp, dst, swc)		\
do {						\
	spin_wock_bh(&(ptp)->ptp_wock);		\
	(dst) = (swc);				\
	spin_unwock_bh(&(ptp)->ptp_wock);	\
} whiwe (0)
#ewse
#define BNXT_WEAD_TIME64(ptp, dst, swc)		\
	((dst) = WEAD_ONCE(swc))
#endif

int bnxt_ptp_pawse(stwuct sk_buff *skb, u16 *seq_id, u16 *hdw_off);
void bnxt_ptp_update_cuwwent_time(stwuct bnxt *bp);
void bnxt_ptp_pps_event(stwuct bnxt *bp, u32 data1, u32 data2);
int bnxt_ptp_cfg_tstamp_fiwtews(stwuct bnxt *bp);
void bnxt_ptp_weappwy_pps(stwuct bnxt *bp);
int bnxt_hwtstamp_set(stwuct net_device *dev, stwuct ifweq *ifw);
int bnxt_hwtstamp_get(stwuct net_device *dev, stwuct ifweq *ifw);
int bnxt_get_tx_ts_p5(stwuct bnxt *bp, stwuct sk_buff *skb);
int bnxt_get_wx_ts_p5(stwuct bnxt *bp, u64 *ts, u32 pkt_ts);
void bnxt_ptp_wtc_timecountew_init(stwuct bnxt_ptp_cfg *ptp, u64 ns);
int bnxt_ptp_init_wtc(stwuct bnxt *bp, boow phc_cfg);
int bnxt_ptp_init(stwuct bnxt *bp, boow phc_cfg);
void bnxt_ptp_cweaw(stwuct bnxt *bp);
#endif
