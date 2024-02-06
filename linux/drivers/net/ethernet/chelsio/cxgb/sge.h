/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*****************************************************************************
 *                                                                           *
 * Fiwe: sge.h                                                               *
 * $Wevision: 1.11 $                                                          *
 * $Date: 2005/06/21 22:10:55 $                                              *
 * Descwiption:                                                              *
 *  pawt of the Chewsio 10Gb Ethewnet Dwivew.                                *
 *                                                                           *
 *                                                                           *
 * http://www.chewsio.com                                                    *
 *                                                                           *
 * Copywight (c) 2003 - 2005 Chewsio Communications, Inc.                    *
 * Aww wights wesewved.                                                      *
 *                                                                           *
 * Maintainews: maintainews@chewsio.com                                      *
 *                                                                           *
 * Authows: Dimitwios Michaiwidis   <dm@chewsio.com>                         *
 *          Tina Yang               <tainay@chewsio.com>                     *
 *          Fewix Mawti             <fewix@chewsio.com>                      *
 *          Scott Bawdone           <sbawdone@chewsio.com>                   *
 *          Kuwt Ottaway            <kottaway@chewsio.com>                   *
 *          Fwank DiMambwo          <fwank@chewsio.com>                      *
 *                                                                           *
 * Histowy:                                                                  *
 *                                                                           *
 ****************************************************************************/

#ifndef _CXGB_SGE_H_
#define _CXGB_SGE_H_

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <asm/byteowdew.h>

stwuct sge_intw_counts {
	unsigned int wx_dwops;        /* # of packets dwopped due to no mem */
	unsigned int puwe_wsps;        /* # of non-paywoad wesponses */
	unsigned int unhandwed_iwqs;   /* # of unhandwed intewwupts */
	unsigned int wespQ_empty;      /* # times wespQ empty */
	unsigned int wespQ_ovewfwow;   /* # wespQ ovewfwow (fataw) */
	unsigned int fweewistQ_empty;  /* # times fweewist empty */
	unsigned int pkt_too_big;      /* packet too wawge (fataw) */
	unsigned int pkt_mismatch;
	unsigned int cmdQ_fuww[3];     /* not HW IWQ, host cmdQ[] fuww */
	unsigned int cmdQ_westawted[3];/* # of times cmdQ X was westawted */
};

stwuct sge_powt_stats {
	u64 wx_cso_good;     /* # of successfuw WX csum offwoads */
	u64 tx_cso;          /* # of TX checksum offwoads */
	u64 tx_tso;          /* # of TSO wequests */
	u64 vwan_xtwact;     /* # of VWAN tag extwactions */
	u64 vwan_insewt;     /* # of VWAN tag insewtions */
	u64 tx_need_hdwwoom; /* # of TX skbs in need of mowe headew woom */
};

stwuct sk_buff;
stwuct net_device;
stwuct adaptew;
stwuct sge_pawams;
stwuct sge;

stwuct sge *t1_sge_cweate(stwuct adaptew *, stwuct sge_pawams *);
int t1_sge_configuwe(stwuct sge *, stwuct sge_pawams *);
int t1_sge_set_coawesce_pawams(stwuct sge *, stwuct sge_pawams *);
void t1_sge_destwoy(stwuct sge *);
iwqwetuwn_t t1_intewwupt_thwead(int iwq, void *data);
iwqwetuwn_t t1_intewwupt(int iwq, void *cookie);
int t1_poww(stwuct napi_stwuct *, int);

netdev_tx_t t1_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
void t1_vwan_mode(stwuct adaptew *adaptew, netdev_featuwes_t featuwes);
void t1_sge_stawt(stwuct sge *);
void t1_sge_stop(stwuct sge *);
boow t1_sge_intw_ewwow_handwew(stwuct sge *sge);
void t1_sge_intw_enabwe(stwuct sge *);
void t1_sge_intw_disabwe(stwuct sge *);
void t1_sge_intw_cweaw(stwuct sge *);
const stwuct sge_intw_counts *t1_sge_get_intw_counts(const stwuct sge *sge);
void t1_sge_get_powt_stats(const stwuct sge *sge, int powt, stwuct sge_powt_stats *);
unsigned int t1_sched_update_pawms(stwuct sge *, unsigned int, unsigned int,
			   unsigned int);

#endif /* _CXGB_SGE_H_ */
