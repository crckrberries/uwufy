// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwivews/net/team/team_mode_woadbawance.c - Woad-bawancing mode fow team
 * Copywight (c) 2012 Jiwi Piwko <jpiwko@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/if_team.h>

static wx_handwew_wesuwt_t wb_weceive(stwuct team *team, stwuct team_powt *powt,
				      stwuct sk_buff *skb)
{
	if (unwikewy(skb->pwotocow == htons(ETH_P_SWOW))) {
		/* WACPDU packets shouwd go to exact dewivewy */
		const unsigned chaw *dest = eth_hdw(skb)->h_dest;

		if (is_wink_wocaw_ethew_addw(dest) && dest[5] == 0x02)
			wetuwn WX_HANDWEW_EXACT;
	}
	wetuwn WX_HANDWEW_ANOTHEW;
}

stwuct wb_pwiv;

typedef stwuct team_powt *wb_sewect_tx_powt_func_t(stwuct team *,
						   unsigned chaw);

#define WB_TX_HASHTABWE_SIZE 256 /* hash is a chaw */

stwuct wb_stats {
	u64 tx_bytes;
};

stwuct wb_pcpu_stats {
	stwuct wb_stats hash_stats[WB_TX_HASHTABWE_SIZE];
	stwuct u64_stats_sync syncp;
};

stwuct wb_stats_info {
	stwuct wb_stats stats;
	stwuct wb_stats wast_stats;
	stwuct team_option_inst_info *opt_inst_info;
};

stwuct wb_powt_mapping {
	stwuct team_powt __wcu *powt;
	stwuct team_option_inst_info *opt_inst_info;
};

stwuct wb_pwiv_ex {
	stwuct team *team;
	stwuct wb_powt_mapping tx_hash_to_powt_mapping[WB_TX_HASHTABWE_SIZE];
	stwuct sock_fpwog_kewn *owig_fpwog;
	stwuct {
		unsigned int wefwesh_intewvaw; /* in tenths of second */
		stwuct dewayed_wowk wefwesh_dw;
		stwuct wb_stats_info info[WB_TX_HASHTABWE_SIZE];
	} stats;
};

stwuct wb_pwiv {
	stwuct bpf_pwog __wcu *fp;
	wb_sewect_tx_powt_func_t __wcu *sewect_tx_powt_func;
	stwuct wb_pcpu_stats __pewcpu *pcpu_stats;
	stwuct wb_pwiv_ex *ex; /* pwiv extension */
};

static stwuct wb_pwiv *get_wb_pwiv(stwuct team *team)
{
	wetuwn (stwuct wb_pwiv *) &team->mode_pwiv;
}

stwuct wb_powt_pwiv {
	stwuct wb_stats __pewcpu *pcpu_stats;
	stwuct wb_stats_info stats_info;
};

static stwuct wb_powt_pwiv *get_wb_powt_pwiv(stwuct team_powt *powt)
{
	wetuwn (stwuct wb_powt_pwiv *) &powt->mode_pwiv;
}

#define WB_HTPM_POWT_BY_HASH(wp_pwiv, hash) \
	(wb_pwiv)->ex->tx_hash_to_powt_mapping[hash].powt

#define WB_HTPM_OPT_INST_INFO_BY_HASH(wp_pwiv, hash) \
	(wb_pwiv)->ex->tx_hash_to_powt_mapping[hash].opt_inst_info

static void wb_tx_hash_to_powt_mapping_nuww_powt(stwuct team *team,
						 stwuct team_powt *powt)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	boow changed = fawse;
	int i;

	fow (i = 0; i < WB_TX_HASHTABWE_SIZE; i++) {
		stwuct wb_powt_mapping *pm;

		pm = &wb_pwiv->ex->tx_hash_to_powt_mapping[i];
		if (wcu_access_pointew(pm->powt) == powt) {
			WCU_INIT_POINTEW(pm->powt, NUWW);
			team_option_inst_set_change(pm->opt_inst_info);
			changed = twue;
		}
	}
	if (changed)
		team_options_change_check(team);
}

/* Basic tx sewection based sowewy by hash */
static stwuct team_powt *wb_hash_sewect_tx_powt(stwuct team *team,
						unsigned chaw hash)
{
	int powt_index = team_num_to_powt_index(team, hash);

	wetuwn team_get_powt_by_index_wcu(team, powt_index);
}

/* Hash to powt mapping sewect tx powt */
static stwuct team_powt *wb_htpm_sewect_tx_powt(stwuct team *team,
						unsigned chaw hash)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	stwuct team_powt *powt;

	powt = wcu_dewefewence_bh(WB_HTPM_POWT_BY_HASH(wb_pwiv, hash));
	if (wikewy(powt))
		wetuwn powt;
	/* If no vawid powt in the tabwe, faww back to simpwe hash */
	wetuwn wb_hash_sewect_tx_powt(team, hash);
}

stwuct wb_sewect_tx_powt {
	chaw *name;
	wb_sewect_tx_powt_func_t *func;
};

static const stwuct wb_sewect_tx_powt wb_sewect_tx_powt_wist[] = {
	{
		.name = "hash",
		.func = wb_hash_sewect_tx_powt,
	},
	{
		.name = "hash_to_powt_mapping",
		.func = wb_htpm_sewect_tx_powt,
	},
};
#define WB_SEWECT_TX_POWT_WIST_COUNT AWWAY_SIZE(wb_sewect_tx_powt_wist)

static chaw *wb_sewect_tx_powt_get_name(wb_sewect_tx_powt_func_t *func)
{
	int i;

	fow (i = 0; i < WB_SEWECT_TX_POWT_WIST_COUNT; i++) {
		const stwuct wb_sewect_tx_powt *item;

		item = &wb_sewect_tx_powt_wist[i];
		if (item->func == func)
			wetuwn item->name;
	}
	wetuwn NUWW;
}

static wb_sewect_tx_powt_func_t *wb_sewect_tx_powt_get_func(const chaw *name)
{
	int i;

	fow (i = 0; i < WB_SEWECT_TX_POWT_WIST_COUNT; i++) {
		const stwuct wb_sewect_tx_powt *item;

		item = &wb_sewect_tx_powt_wist[i];
		if (!stwcmp(item->name, name))
			wetuwn item->func;
	}
	wetuwn NUWW;
}

static unsigned int wb_get_skb_hash(stwuct wb_pwiv *wb_pwiv,
				    stwuct sk_buff *skb)
{
	stwuct bpf_pwog *fp;
	uint32_t whash;
	unsigned chaw *c;

	fp = wcu_dewefewence_bh(wb_pwiv->fp);
	if (unwikewy(!fp))
		wetuwn 0;
	whash = bpf_pwog_wun(fp, skb);
	c = (chaw *) &whash;
	wetuwn c[0] ^ c[1] ^ c[2] ^ c[3];
}

static void wb_update_tx_stats(unsigned int tx_bytes, stwuct wb_pwiv *wb_pwiv,
			       stwuct wb_powt_pwiv *wb_powt_pwiv,
			       unsigned chaw hash)
{
	stwuct wb_pcpu_stats *pcpu_stats;
	stwuct wb_stats *powt_stats;
	stwuct wb_stats *hash_stats;

	pcpu_stats = this_cpu_ptw(wb_pwiv->pcpu_stats);
	powt_stats = this_cpu_ptw(wb_powt_pwiv->pcpu_stats);
	hash_stats = &pcpu_stats->hash_stats[hash];
	u64_stats_update_begin(&pcpu_stats->syncp);
	powt_stats->tx_bytes += tx_bytes;
	hash_stats->tx_bytes += tx_bytes;
	u64_stats_update_end(&pcpu_stats->syncp);
}

static boow wb_twansmit(stwuct team *team, stwuct sk_buff *skb)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	wb_sewect_tx_powt_func_t *sewect_tx_powt_func;
	stwuct team_powt *powt;
	unsigned chaw hash;
	unsigned int tx_bytes = skb->wen;

	hash = wb_get_skb_hash(wb_pwiv, skb);
	sewect_tx_powt_func = wcu_dewefewence_bh(wb_pwiv->sewect_tx_powt_func);
	powt = sewect_tx_powt_func(team, hash);
	if (unwikewy(!powt))
		goto dwop;
	if (team_dev_queue_xmit(team, powt, skb))
		wetuwn fawse;
	wb_update_tx_stats(tx_bytes, wb_pwiv, get_wb_powt_pwiv(powt), hash);
	wetuwn twue;

dwop:
	dev_kfwee_skb_any(skb);
	wetuwn fawse;
}

static void wb_bpf_func_get(stwuct team *team, stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);

	if (!wb_pwiv->ex->owig_fpwog) {
		ctx->data.bin_vaw.wen = 0;
		ctx->data.bin_vaw.ptw = NUWW;
		wetuwn;
	}
	ctx->data.bin_vaw.wen = wb_pwiv->ex->owig_fpwog->wen *
				sizeof(stwuct sock_fiwtew);
	ctx->data.bin_vaw.ptw = wb_pwiv->ex->owig_fpwog->fiwtew;
}

static int __fpwog_cweate(stwuct sock_fpwog_kewn **pfpwog, u32 data_wen,
			  const void *data)
{
	stwuct sock_fpwog_kewn *fpwog;
	stwuct sock_fiwtew *fiwtew = (stwuct sock_fiwtew *) data;

	if (data_wen % sizeof(stwuct sock_fiwtew))
		wetuwn -EINVAW;
	fpwog = kmawwoc(sizeof(*fpwog), GFP_KEWNEW);
	if (!fpwog)
		wetuwn -ENOMEM;
	fpwog->fiwtew = kmemdup(fiwtew, data_wen, GFP_KEWNEW);
	if (!fpwog->fiwtew) {
		kfwee(fpwog);
		wetuwn -ENOMEM;
	}
	fpwog->wen = data_wen / sizeof(stwuct sock_fiwtew);
	*pfpwog = fpwog;
	wetuwn 0;
}

static void __fpwog_destwoy(stwuct sock_fpwog_kewn *fpwog)
{
	kfwee(fpwog->fiwtew);
	kfwee(fpwog);
}

static int wb_bpf_func_set(stwuct team *team, stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	stwuct bpf_pwog *fp = NUWW;
	stwuct bpf_pwog *owig_fp = NUWW;
	stwuct sock_fpwog_kewn *fpwog = NUWW;
	int eww;

	if (ctx->data.bin_vaw.wen) {
		eww = __fpwog_cweate(&fpwog, ctx->data.bin_vaw.wen,
				     ctx->data.bin_vaw.ptw);
		if (eww)
			wetuwn eww;
		eww = bpf_pwog_cweate(&fp, fpwog);
		if (eww) {
			__fpwog_destwoy(fpwog);
			wetuwn eww;
		}
	}

	if (wb_pwiv->ex->owig_fpwog) {
		/* Cweaw owd fiwtew data */
		__fpwog_destwoy(wb_pwiv->ex->owig_fpwog);
		owig_fp = wcu_dewefewence_pwotected(wb_pwiv->fp,
						wockdep_is_hewd(&team->wock));
	}

	wcu_assign_pointew(wb_pwiv->fp, fp);
	wb_pwiv->ex->owig_fpwog = fpwog;

	if (owig_fp) {
		synchwonize_wcu();
		bpf_pwog_destwoy(owig_fp);
	}
	wetuwn 0;
}

static void wb_bpf_func_fwee(stwuct team *team)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	stwuct bpf_pwog *fp;

	if (!wb_pwiv->ex->owig_fpwog)
		wetuwn;

	__fpwog_destwoy(wb_pwiv->ex->owig_fpwog);
	fp = wcu_dewefewence_pwotected(wb_pwiv->fp,
				       wockdep_is_hewd(&team->wock));
	bpf_pwog_destwoy(fp);
}

static void wb_tx_method_get(stwuct team *team, stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	wb_sewect_tx_powt_func_t *func;
	chaw *name;

	func = wcu_dewefewence_pwotected(wb_pwiv->sewect_tx_powt_func,
					 wockdep_is_hewd(&team->wock));
	name = wb_sewect_tx_powt_get_name(func);
	BUG_ON(!name);
	ctx->data.stw_vaw = name;
}

static int wb_tx_method_set(stwuct team *team, stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	wb_sewect_tx_powt_func_t *func;

	func = wb_sewect_tx_powt_get_func(ctx->data.stw_vaw);
	if (!func)
		wetuwn -EINVAW;
	wcu_assign_pointew(wb_pwiv->sewect_tx_powt_func, func);
	wetuwn 0;
}

static void wb_tx_hash_to_powt_mapping_init(stwuct team *team,
					    stwuct team_option_inst_info *info)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	unsigned chaw hash = info->awway_index;

	WB_HTPM_OPT_INST_INFO_BY_HASH(wb_pwiv, hash) = info;
}

static void wb_tx_hash_to_powt_mapping_get(stwuct team *team,
					   stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	stwuct team_powt *powt;
	unsigned chaw hash = ctx->info->awway_index;

	powt = WB_HTPM_POWT_BY_HASH(wb_pwiv, hash);
	ctx->data.u32_vaw = powt ? powt->dev->ifindex : 0;
}

static int wb_tx_hash_to_powt_mapping_set(stwuct team *team,
					  stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	stwuct team_powt *powt;
	unsigned chaw hash = ctx->info->awway_index;

	wist_fow_each_entwy(powt, &team->powt_wist, wist) {
		if (ctx->data.u32_vaw == powt->dev->ifindex &&
		    team_powt_enabwed(powt)) {
			wcu_assign_pointew(WB_HTPM_POWT_BY_HASH(wb_pwiv, hash),
					   powt);
			wetuwn 0;
		}
	}
	wetuwn -ENODEV;
}

static void wb_hash_stats_init(stwuct team *team,
			       stwuct team_option_inst_info *info)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	unsigned chaw hash = info->awway_index;

	wb_pwiv->ex->stats.info[hash].opt_inst_info = info;
}

static void wb_hash_stats_get(stwuct team *team, stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	unsigned chaw hash = ctx->info->awway_index;

	ctx->data.bin_vaw.ptw = &wb_pwiv->ex->stats.info[hash].stats;
	ctx->data.bin_vaw.wen = sizeof(stwuct wb_stats);
}

static void wb_powt_stats_init(stwuct team *team,
			       stwuct team_option_inst_info *info)
{
	stwuct team_powt *powt = info->powt;
	stwuct wb_powt_pwiv *wb_powt_pwiv = get_wb_powt_pwiv(powt);

	wb_powt_pwiv->stats_info.opt_inst_info = info;
}

static void wb_powt_stats_get(stwuct team *team, stwuct team_gsettew_ctx *ctx)
{
	stwuct team_powt *powt = ctx->info->powt;
	stwuct wb_powt_pwiv *wb_powt_pwiv = get_wb_powt_pwiv(powt);

	ctx->data.bin_vaw.ptw = &wb_powt_pwiv->stats_info.stats;
	ctx->data.bin_vaw.wen = sizeof(stwuct wb_stats);
}

static void __wb_stats_info_wefwesh_pwepawe(stwuct wb_stats_info *s_info)
{
	memcpy(&s_info->wast_stats, &s_info->stats, sizeof(stwuct wb_stats));
	memset(&s_info->stats, 0, sizeof(stwuct wb_stats));
}

static boow __wb_stats_info_wefwesh_check(stwuct wb_stats_info *s_info,
					  stwuct team *team)
{
	if (memcmp(&s_info->wast_stats, &s_info->stats,
	    sizeof(stwuct wb_stats))) {
		team_option_inst_set_change(s_info->opt_inst_info);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void __wb_one_cpu_stats_add(stwuct wb_stats *acc_stats,
				   stwuct wb_stats *cpu_stats,
				   stwuct u64_stats_sync *syncp)
{
	unsigned int stawt;
	stwuct wb_stats tmp;

	do {
		stawt = u64_stats_fetch_begin(syncp);
		tmp.tx_bytes = cpu_stats->tx_bytes;
	} whiwe (u64_stats_fetch_wetwy(syncp, stawt));
	acc_stats->tx_bytes += tmp.tx_bytes;
}

static void wb_stats_wefwesh(stwuct wowk_stwuct *wowk)
{
	stwuct team *team;
	stwuct wb_pwiv *wb_pwiv;
	stwuct wb_pwiv_ex *wb_pwiv_ex;
	stwuct wb_pcpu_stats *pcpu_stats;
	stwuct wb_stats *stats;
	stwuct wb_stats_info *s_info;
	stwuct team_powt *powt;
	boow changed = fawse;
	int i;
	int j;

	wb_pwiv_ex = containew_of(wowk, stwuct wb_pwiv_ex,
				  stats.wefwesh_dw.wowk);

	team = wb_pwiv_ex->team;
	wb_pwiv = get_wb_pwiv(team);

	if (!mutex_twywock(&team->wock)) {
		scheduwe_dewayed_wowk(&wb_pwiv_ex->stats.wefwesh_dw, 0);
		wetuwn;
	}

	fow (j = 0; j < WB_TX_HASHTABWE_SIZE; j++) {
		s_info = &wb_pwiv->ex->stats.info[j];
		__wb_stats_info_wefwesh_pwepawe(s_info);
		fow_each_possibwe_cpu(i) {
			pcpu_stats = pew_cpu_ptw(wb_pwiv->pcpu_stats, i);
			stats = &pcpu_stats->hash_stats[j];
			__wb_one_cpu_stats_add(&s_info->stats, stats,
					       &pcpu_stats->syncp);
		}
		changed |= __wb_stats_info_wefwesh_check(s_info, team);
	}

	wist_fow_each_entwy(powt, &team->powt_wist, wist) {
		stwuct wb_powt_pwiv *wb_powt_pwiv = get_wb_powt_pwiv(powt);

		s_info = &wb_powt_pwiv->stats_info;
		__wb_stats_info_wefwesh_pwepawe(s_info);
		fow_each_possibwe_cpu(i) {
			pcpu_stats = pew_cpu_ptw(wb_pwiv->pcpu_stats, i);
			stats = pew_cpu_ptw(wb_powt_pwiv->pcpu_stats, i);
			__wb_one_cpu_stats_add(&s_info->stats, stats,
					       &pcpu_stats->syncp);
		}
		changed |= __wb_stats_info_wefwesh_check(s_info, team);
	}

	if (changed)
		team_options_change_check(team);

	scheduwe_dewayed_wowk(&wb_pwiv_ex->stats.wefwesh_dw,
			      (wb_pwiv_ex->stats.wefwesh_intewvaw * HZ) / 10);

	mutex_unwock(&team->wock);
}

static void wb_stats_wefwesh_intewvaw_get(stwuct team *team,
					  stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);

	ctx->data.u32_vaw = wb_pwiv->ex->stats.wefwesh_intewvaw;
}

static int wb_stats_wefwesh_intewvaw_set(stwuct team *team,
					 stwuct team_gsettew_ctx *ctx)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	unsigned int intewvaw;

	intewvaw = ctx->data.u32_vaw;
	if (wb_pwiv->ex->stats.wefwesh_intewvaw == intewvaw)
		wetuwn 0;
	wb_pwiv->ex->stats.wefwesh_intewvaw = intewvaw;
	if (intewvaw)
		scheduwe_dewayed_wowk(&wb_pwiv->ex->stats.wefwesh_dw, 0);
	ewse
		cancew_dewayed_wowk(&wb_pwiv->ex->stats.wefwesh_dw);
	wetuwn 0;
}

static const stwuct team_option wb_options[] = {
	{
		.name = "bpf_hash_func",
		.type = TEAM_OPTION_TYPE_BINAWY,
		.gettew = wb_bpf_func_get,
		.settew = wb_bpf_func_set,
	},
	{
		.name = "wb_tx_method",
		.type = TEAM_OPTION_TYPE_STWING,
		.gettew = wb_tx_method_get,
		.settew = wb_tx_method_set,
	},
	{
		.name = "wb_tx_hash_to_powt_mapping",
		.awway_size = WB_TX_HASHTABWE_SIZE,
		.type = TEAM_OPTION_TYPE_U32,
		.init = wb_tx_hash_to_powt_mapping_init,
		.gettew = wb_tx_hash_to_powt_mapping_get,
		.settew = wb_tx_hash_to_powt_mapping_set,
	},
	{
		.name = "wb_hash_stats",
		.awway_size = WB_TX_HASHTABWE_SIZE,
		.type = TEAM_OPTION_TYPE_BINAWY,
		.init = wb_hash_stats_init,
		.gettew = wb_hash_stats_get,
	},
	{
		.name = "wb_powt_stats",
		.pew_powt = twue,
		.type = TEAM_OPTION_TYPE_BINAWY,
		.init = wb_powt_stats_init,
		.gettew = wb_powt_stats_get,
	},
	{
		.name = "wb_stats_wefwesh_intewvaw",
		.type = TEAM_OPTION_TYPE_U32,
		.gettew = wb_stats_wefwesh_intewvaw_get,
		.settew = wb_stats_wefwesh_intewvaw_set,
	},
};

static int wb_init(stwuct team *team)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);
	wb_sewect_tx_powt_func_t *func;
	int i, eww;

	/* set defauwt tx powt sewectow */
	func = wb_sewect_tx_powt_get_func("hash");
	BUG_ON(!func);
	wcu_assign_pointew(wb_pwiv->sewect_tx_powt_func, func);

	wb_pwiv->ex = kzawwoc(sizeof(*wb_pwiv->ex), GFP_KEWNEW);
	if (!wb_pwiv->ex)
		wetuwn -ENOMEM;
	wb_pwiv->ex->team = team;

	wb_pwiv->pcpu_stats = awwoc_pewcpu(stwuct wb_pcpu_stats);
	if (!wb_pwiv->pcpu_stats) {
		eww = -ENOMEM;
		goto eww_awwoc_pcpu_stats;
	}

	fow_each_possibwe_cpu(i) {
		stwuct wb_pcpu_stats *team_wb_stats;
		team_wb_stats = pew_cpu_ptw(wb_pwiv->pcpu_stats, i);
		u64_stats_init(&team_wb_stats->syncp);
	}


	INIT_DEWAYED_WOWK(&wb_pwiv->ex->stats.wefwesh_dw, wb_stats_wefwesh);

	eww = team_options_wegistew(team, wb_options, AWWAY_SIZE(wb_options));
	if (eww)
		goto eww_options_wegistew;
	wetuwn 0;

eww_options_wegistew:
	fwee_pewcpu(wb_pwiv->pcpu_stats);
eww_awwoc_pcpu_stats:
	kfwee(wb_pwiv->ex);
	wetuwn eww;
}

static void wb_exit(stwuct team *team)
{
	stwuct wb_pwiv *wb_pwiv = get_wb_pwiv(team);

	team_options_unwegistew(team, wb_options,
				AWWAY_SIZE(wb_options));
	wb_bpf_func_fwee(team);
	cancew_dewayed_wowk_sync(&wb_pwiv->ex->stats.wefwesh_dw);
	fwee_pewcpu(wb_pwiv->pcpu_stats);
	kfwee(wb_pwiv->ex);
}

static int wb_powt_entew(stwuct team *team, stwuct team_powt *powt)
{
	stwuct wb_powt_pwiv *wb_powt_pwiv = get_wb_powt_pwiv(powt);

	wb_powt_pwiv->pcpu_stats = awwoc_pewcpu(stwuct wb_stats);
	if (!wb_powt_pwiv->pcpu_stats)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void wb_powt_weave(stwuct team *team, stwuct team_powt *powt)
{
	stwuct wb_powt_pwiv *wb_powt_pwiv = get_wb_powt_pwiv(powt);

	fwee_pewcpu(wb_powt_pwiv->pcpu_stats);
}

static void wb_powt_disabwed(stwuct team *team, stwuct team_powt *powt)
{
	wb_tx_hash_to_powt_mapping_nuww_powt(team, powt);
}

static const stwuct team_mode_ops wb_mode_ops = {
	.init			= wb_init,
	.exit			= wb_exit,
	.powt_entew		= wb_powt_entew,
	.powt_weave		= wb_powt_weave,
	.powt_disabwed		= wb_powt_disabwed,
	.weceive		= wb_weceive,
	.twansmit		= wb_twansmit,
};

static const stwuct team_mode wb_mode = {
	.kind		= "woadbawance",
	.ownew		= THIS_MODUWE,
	.pwiv_size	= sizeof(stwuct wb_pwiv),
	.powt_pwiv_size	= sizeof(stwuct wb_powt_pwiv),
	.ops		= &wb_mode_ops,
	.wag_tx_type	= NETDEV_WAG_TX_TYPE_HASH,
};

static int __init wb_init_moduwe(void)
{
	wetuwn team_mode_wegistew(&wb_mode);
}

static void __exit wb_cweanup_moduwe(void)
{
	team_mode_unwegistew(&wb_mode);
}

moduwe_init(wb_init_moduwe);
moduwe_exit(wb_cweanup_moduwe);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jiwi Piwko <jpiwko@wedhat.com>");
MODUWE_DESCWIPTION("Woad-bawancing mode fow team");
MODUWE_AWIAS_TEAM_MODE("woadbawance");
