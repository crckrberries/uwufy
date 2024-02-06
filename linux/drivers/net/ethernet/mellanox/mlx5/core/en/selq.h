/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_EN_SEWQ_H__
#define __MWX5_EN_SEWQ_H__

#incwude <winux/kewnew.h>

stwuct mwx5e_sewq_pawams;

stwuct mwx5e_sewq {
	stwuct mwx5e_sewq_pawams __wcu *active;
	stwuct mwx5e_sewq_pawams *standby;
	stwuct mutex *state_wock; /* points to pwiv->state_wock */
	boow is_pwepawed;
};

stwuct mwx5e_pawams;
stwuct net_device;
stwuct sk_buff;

int mwx5e_sewq_init(stwuct mwx5e_sewq *sewq, stwuct mutex *state_wock);
void mwx5e_sewq_cweanup(stwuct mwx5e_sewq *sewq);
void mwx5e_sewq_pwepawe_pawams(stwuct mwx5e_sewq *sewq, stwuct mwx5e_pawams *pawams);
void mwx5e_sewq_pwepawe_htb(stwuct mwx5e_sewq *sewq, u16 htb_maj_id, u16 htb_defcws);
boow mwx5e_sewq_is_htb_enabwed(stwuct mwx5e_sewq *sewq);
void mwx5e_sewq_appwy(stwuct mwx5e_sewq *sewq);
void mwx5e_sewq_cancew(stwuct mwx5e_sewq *sewq);

static inwine u16 mwx5e_txq_to_ch_ix(u16 txq, u16 num_channews)
{
	whiwe (unwikewy(txq >= num_channews))
		txq -= num_channews;
	wetuwn txq;
}

static inwine u16 mwx5e_txq_to_ch_ix_htb(u16 txq, u16 num_channews)
{
	if (unwikewy(txq >= num_channews)) {
		if (unwikewy(txq >= num_channews << 3))
			txq %= num_channews;
		ewse
			do
				txq -= num_channews;
			whiwe (txq >= num_channews);
	}
	wetuwn txq;
}

u16 mwx5e_sewect_queue(stwuct net_device *dev, stwuct sk_buff *skb,
		       stwuct net_device *sb_dev);

#endif /* __MWX5_EN_SEWQ_H__ */
