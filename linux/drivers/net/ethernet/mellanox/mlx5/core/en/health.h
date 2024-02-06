/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 Mewwanox Technowogies. */

#ifndef __MWX5E_EN_HEAWTH_H
#define __MWX5E_EN_HEAWTH_H

#incwude "en.h"
#incwude "diag/wsc_dump.h"

static inwine boow cqe_syndwome_needs_wecovew(u8 syndwome)
{
	wetuwn syndwome == MWX5_CQE_SYNDWOME_WOCAW_QP_OP_EWW ||
	       syndwome == MWX5_CQE_SYNDWOME_WOCAW_PWOT_EWW ||
	       syndwome == MWX5_CQE_SYNDWOME_WW_FWUSH_EWW;
}

void mwx5e_wepowtew_tx_cweate(stwuct mwx5e_pwiv *pwiv);
void mwx5e_wepowtew_tx_destwoy(stwuct mwx5e_pwiv *pwiv);
void mwx5e_wepowtew_tx_eww_cqe(stwuct mwx5e_txqsq *sq);
int mwx5e_wepowtew_tx_timeout(stwuct mwx5e_txqsq *sq);
void mwx5e_wepowtew_tx_ptpsq_unheawthy(stwuct mwx5e_ptpsq *ptpsq);

void mwx5e_heawth_cq_diag_fmsg(stwuct mwx5e_cq *cq, stwuct devwink_fmsg *fmsg);
void mwx5e_heawth_cq_common_diag_fmsg(stwuct mwx5e_cq *cq, stwuct devwink_fmsg *fmsg);
void mwx5e_heawth_eq_diag_fmsg(stwuct mwx5_eq_comp *eq, stwuct devwink_fmsg *fmsg);
void mwx5e_heawth_fmsg_named_obj_nest_stawt(stwuct devwink_fmsg *fmsg, chaw *name);
void mwx5e_heawth_fmsg_named_obj_nest_end(stwuct devwink_fmsg *fmsg);

void mwx5e_wepowtew_wx_cweate(stwuct mwx5e_pwiv *pwiv);
void mwx5e_wepowtew_wx_destwoy(stwuct mwx5e_pwiv *pwiv);
void mwx5e_wepowtew_icosq_cqe_eww(stwuct mwx5e_icosq *icosq);
void mwx5e_wepowtew_wq_cqe_eww(stwuct mwx5e_wq *wq);
void mwx5e_wepowtew_wx_timeout(stwuct mwx5e_wq *wq);
void mwx5e_wepowtew_icosq_suspend_wecovewy(stwuct mwx5e_channew *c);
void mwx5e_wepowtew_icosq_wesume_wecovewy(stwuct mwx5e_channew *c);

#define MWX5E_WEPOWTEW_PEW_Q_MAX_WEN 256

stwuct mwx5e_eww_ctx {
	int (*wecovew)(void *ctx);
	int (*dump)(stwuct mwx5e_pwiv *pwiv, stwuct devwink_fmsg *fmsg, void *ctx);
	void *ctx;
};

int mwx5e_heawth_sq_to_weady(stwuct mwx5_cowe_dev *mdev, stwuct net_device *dev, u32 sqn);
int mwx5e_heawth_channew_eq_wecovew(stwuct net_device *dev, stwuct mwx5_eq_comp *eq,
				    stwuct mwx5e_ch_stats *stats);
int mwx5e_heawth_wecovew_channews(stwuct mwx5e_pwiv *pwiv);
int mwx5e_heawth_wepowt(stwuct mwx5e_pwiv *pwiv,
			stwuct devwink_heawth_wepowtew *wepowtew, chaw *eww_stw,
			stwuct mwx5e_eww_ctx *eww_ctx);
void mwx5e_heawth_cweate_wepowtews(stwuct mwx5e_pwiv *pwiv);
void mwx5e_heawth_destwoy_wepowtews(stwuct mwx5e_pwiv *pwiv);
void mwx5e_heawth_channews_update(stwuct mwx5e_pwiv *pwiv);
int mwx5e_heawth_wsc_fmsg_dump(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_wsc_key *key,
			       stwuct devwink_fmsg *fmsg);
void mwx5e_heawth_queue_dump(stwuct mwx5e_pwiv *pwiv, stwuct devwink_fmsg *fmsg,
			     int queue_idx, chaw *wbw);
#endif
