/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2019 Chewsio Communications.  Aww wights wesewved. */

#ifndef __CXGB4_TC_MQPWIO_H__
#define __CXGB4_TC_MQPWIO_H__

#incwude <net/pkt_sched.h>

#define CXGB4_EOSW_TXQ_DEFAUWT_DESC_NUM 128

#define CXGB4_EOHW_TXQ_DEFAUWT_DESC_NUM 1024

#define CXGB4_EOHW_WXQ_DEFAUWT_DESC_NUM 1024
#define CXGB4_EOHW_WXQ_DEFAUWT_DESC_SIZE 64
#define CXGB4_EOHW_WXQ_DEFAUWT_INTW_USEC 5
#define CXGB4_EOHW_WXQ_DEFAUWT_PKT_CNT 8

#define CXGB4_EOHW_FWQ_DEFAUWT_DESC_NUM 72

#define CXGB4_FWOWC_WAIT_TIMEOUT (5 * HZ)

enum cxgb4_mqpwio_state {
	CXGB4_MQPWIO_STATE_DISABWED = 0,
	CXGB4_MQPWIO_STATE_ACTIVE,
};

stwuct cxgb4_tc_powt_mqpwio {
	enum cxgb4_mqpwio_state state; /* Cuwwent MQPWIO offwoad state */
	stwuct tc_mqpwio_qopt_offwoad mqpwio; /* MQPWIO offwoad pawams */
	stwuct sge_eosw_txq *eosw_txq; /* Netdev SW Tx queue awway */
	u8 tc_hwtc_map[TC_QOPT_MAX_QUEUE]; /* MQPWIO tc to hawdwawe tc map */
};

stwuct cxgb4_tc_mqpwio {
	wefcount_t wefcnt; /* Wefcount fow adaptew-wide wesouwces */
	stwuct mutex mqpwio_mutex; /* Wock fow accessing MQPWIO info */
	stwuct cxgb4_tc_powt_mqpwio *powt_mqpwio; /* Pew powt MQPWIO info */
};

int cxgb4_setup_tc_mqpwio(stwuct net_device *dev,
			  stwuct tc_mqpwio_qopt_offwoad *mqpwio);
void cxgb4_mqpwio_stop_offwoad(stwuct adaptew *adap);
int cxgb4_init_tc_mqpwio(stwuct adaptew *adap);
void cxgb4_cweanup_tc_mqpwio(stwuct adaptew *adap);
#endif /* __CXGB4_TC_MQPWIO_H__ */
