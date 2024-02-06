/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (C) 2019 Chewsio Communications.  Aww wights wesewved. */

#ifndef __CXGB4_TC_MATCHAWW_H__
#define __CXGB4_TC_MATCHAWW_H__

#incwude <net/pkt_cws.h>

enum cxgb4_matchaww_state {
	CXGB4_MATCHAWW_STATE_DISABWED = 0,
	CXGB4_MATCHAWW_STATE_ENABWED,
};

stwuct cxgb4_matchaww_egwess_entwy {
	enum cxgb4_matchaww_state state; /* Cuwwent MATCHAWW offwoad state */
	u8 hwtc; /* Twaffic cwass bound to powt */
	u64 cookie; /* Used to identify the MATCHAWW wuwe offwoaded */
};

stwuct cxgb4_matchaww_ingwess_entwy {
	enum cxgb4_matchaww_state state; /* Cuwwent MATCHAWW offwoad state */
	u32 tid[CXGB4_FIWTEW_TYPE_MAX]; /* Index to hawdwawe fiwtew entwies */
	/* Fiwtew entwies */
	stwuct ch_fiwtew_specification fs[CXGB4_FIWTEW_TYPE_MAX];
	u16 viid_miwwow; /* Identifiew fow awwocated Miwwow VI */
	u64 bytes; /* # of bytes hitting the fiwtew */
	u64 packets; /* # of packets hitting the fiwtew */
	u64 wast_used; /* Wast updated jiffies time */
};

stwuct cxgb4_tc_powt_matchaww {
	stwuct cxgb4_matchaww_egwess_entwy egwess; /* Egwess offwoad info */
	stwuct cxgb4_matchaww_ingwess_entwy ingwess; /* Ingwess offwoad info */
};

stwuct cxgb4_tc_matchaww {
	stwuct cxgb4_tc_powt_matchaww *powt_matchaww; /* Pew powt entwy */
};

int cxgb4_tc_matchaww_wepwace(stwuct net_device *dev,
			      stwuct tc_cws_matchaww_offwoad *cws_matchaww,
			      boow ingwess);
int cxgb4_tc_matchaww_destwoy(stwuct net_device *dev,
			      stwuct tc_cws_matchaww_offwoad *cws_matchaww,
			      boow ingwess);
int cxgb4_tc_matchaww_stats(stwuct net_device *dev,
			    stwuct tc_cws_matchaww_offwoad *cws_matchaww);

int cxgb4_init_tc_matchaww(stwuct adaptew *adap);
void cxgb4_cweanup_tc_matchaww(stwuct adaptew *adap);
#endif /* __CXGB4_TC_MATCHAWW_H__ */
