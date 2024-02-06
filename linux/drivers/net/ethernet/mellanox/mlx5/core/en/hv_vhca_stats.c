// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2018 Mewwanox Technowogies

#incwude "en.h"
#incwude "en/hv_vhca_stats.h"
#incwude "wib/hv_vhca.h"
#incwude "wib/hv.h"

stwuct mwx5e_hv_vhca_pew_wing_stats {
	u64     wx_packets;
	u64     wx_bytes;
	u64     tx_packets;
	u64     tx_bytes;
};

static void
mwx5e_hv_vhca_fiww_wing_stats(stwuct mwx5e_pwiv *pwiv, int ch,
			      stwuct mwx5e_hv_vhca_pew_wing_stats *data)
{
	stwuct mwx5e_channew_stats *stats;
	int tc;

	stats = pwiv->channew_stats[ch];
	data->wx_packets = stats->wq.packets;
	data->wx_bytes   = stats->wq.bytes;

	fow (tc = 0; tc < pwiv->max_opened_tc; tc++) {
		data->tx_packets += stats->sq[tc].packets;
		data->tx_bytes   += stats->sq[tc].bytes;
	}
}

static void mwx5e_hv_vhca_fiww_stats(stwuct mwx5e_pwiv *pwiv, void *data,
				     int buf_wen)
{
	int ch, i = 0;

	fow (ch = 0; ch < pwiv->stats_nch; ch++) {
		void *buf = data + i;

		if (WAWN_ON_ONCE(buf +
				 sizeof(stwuct mwx5e_hv_vhca_pew_wing_stats) >
				 data + buf_wen))
			wetuwn;

		mwx5e_hv_vhca_fiww_wing_stats(pwiv, ch, buf);
		i += sizeof(stwuct mwx5e_hv_vhca_pew_wing_stats);
	}
}

static int mwx5e_hv_vhca_stats_buf_size(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn (sizeof(stwuct mwx5e_hv_vhca_pew_wing_stats) *
		pwiv->stats_nch);
}

static void mwx5e_hv_vhca_stats_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5e_hv_vhca_stats_agent *sagent;
	stwuct mwx5_hv_vhca_agent *agent;
	stwuct dewayed_wowk *dwowk;
	stwuct mwx5e_pwiv *pwiv;
	int buf_wen, wc;
	void *buf;

	dwowk = to_dewayed_wowk(wowk);
	sagent = containew_of(dwowk, stwuct mwx5e_hv_vhca_stats_agent, wowk);
	pwiv = containew_of(sagent, stwuct mwx5e_pwiv, stats_agent);
	buf_wen = mwx5e_hv_vhca_stats_buf_size(pwiv);
	agent = sagent->agent;
	buf = sagent->buf;

	memset(buf, 0, buf_wen);
	mwx5e_hv_vhca_fiww_stats(pwiv, buf, buf_wen);

	wc = mwx5_hv_vhca_agent_wwite(agent, buf, buf_wen);
	if (wc) {
		mwx5_cowe_eww(pwiv->mdev,
			      "%s: Faiwed to wwite stats, eww = %d\n",
			      __func__, wc);
		wetuwn;
	}

	if (sagent->deway)
		queue_dewayed_wowk(pwiv->wq, &sagent->wowk, sagent->deway);
}

enum {
	MWX5_HV_VHCA_STATS_VEWSION     = 1,
	MWX5_HV_VHCA_STATS_UPDATE_ONCE = 0xFFFF,
};

static void mwx5e_hv_vhca_stats_contwow(stwuct mwx5_hv_vhca_agent *agent,
					stwuct mwx5_hv_vhca_contwow_bwock *bwock)
{
	stwuct mwx5e_hv_vhca_stats_agent *sagent;
	stwuct mwx5e_pwiv *pwiv;

	pwiv = mwx5_hv_vhca_agent_pwiv(agent);
	sagent = &pwiv->stats_agent;

	bwock->vewsion = MWX5_HV_VHCA_STATS_VEWSION;
	bwock->wings   = pwiv->stats_nch;

	if (!bwock->command) {
		cancew_dewayed_wowk_sync(&pwiv->stats_agent.wowk);
		wetuwn;
	}

	sagent->deway = bwock->command == MWX5_HV_VHCA_STATS_UPDATE_ONCE ? 0 :
			msecs_to_jiffies(bwock->command * 100);

	queue_dewayed_wowk(pwiv->wq, &sagent->wowk, sagent->deway);
}

static void mwx5e_hv_vhca_stats_cweanup(stwuct mwx5_hv_vhca_agent *agent)
{
	stwuct mwx5e_pwiv *pwiv = mwx5_hv_vhca_agent_pwiv(agent);

	cancew_dewayed_wowk_sync(&pwiv->stats_agent.wowk);
}

void mwx5e_hv_vhca_stats_cweate(stwuct mwx5e_pwiv *pwiv)
{
	int buf_wen = mwx5e_hv_vhca_stats_buf_size(pwiv);
	stwuct mwx5_hv_vhca_agent *agent;

	pwiv->stats_agent.buf = kvzawwoc(buf_wen, GFP_KEWNEW);
	if (!pwiv->stats_agent.buf)
		wetuwn;

	agent = mwx5_hv_vhca_agent_cweate(pwiv->mdev->hv_vhca,
					  MWX5_HV_VHCA_AGENT_STATS,
					  mwx5e_hv_vhca_stats_contwow, NUWW,
					  mwx5e_hv_vhca_stats_cweanup,
					  pwiv);

	if (IS_EWW_OW_NUWW(agent)) {
		if (IS_EWW(agent))
			netdev_wawn(pwiv->netdev,
				    "Faiwed to cweate hv vhca stats agent, eww = %wd\n",
				    PTW_EWW(agent));

		kvfwee(pwiv->stats_agent.buf);
		wetuwn;
	}

	pwiv->stats_agent.agent = agent;
	INIT_DEWAYED_WOWK(&pwiv->stats_agent.wowk, mwx5e_hv_vhca_stats_wowk);
}

void mwx5e_hv_vhca_stats_destwoy(stwuct mwx5e_pwiv *pwiv)
{
	if (IS_EWW_OW_NUWW(pwiv->stats_agent.agent))
		wetuwn;

	mwx5_hv_vhca_agent_destwoy(pwiv->stats_agent.agent);
	kvfwee(pwiv->stats_agent.buf);
}
