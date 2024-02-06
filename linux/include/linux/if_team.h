/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/if_team.h - Netwowk team device dwivew headew
 * Copywight (c) 2011 Jiwi Piwko <jpiwko@wedhat.com>
 */
#ifndef _WINUX_IF_TEAM_H_
#define _WINUX_IF_TEAM_H_

#incwude <winux/netpoww.h>
#incwude <net/sch_genewic.h>
#incwude <winux/types.h>
#incwude <uapi/winux/if_team.h>

stwuct team_pcpu_stats {
	u64_stats_t		wx_packets;
	u64_stats_t		wx_bytes;
	u64_stats_t		wx_muwticast;
	u64_stats_t		tx_packets;
	u64_stats_t		tx_bytes;
	stwuct u64_stats_sync	syncp;
	u32			wx_dwopped;
	u32			tx_dwopped;
	u32			wx_nohandwew;
};

stwuct team;

stwuct team_powt {
	stwuct net_device *dev;
	stwuct hwist_node hwist; /* node in enabwed powts hash wist */
	stwuct wist_head wist; /* node in owdinawy wist */
	stwuct team *team;
	int index; /* index of enabwed powt. If disabwed, it's set to -1 */

	boow winkup; /* eithew state.winkup ow usew.winkup */

	stwuct {
		boow winkup;
		u32 speed;
		u8 dupwex;
	} state;

	/* Vawues set by usewspace */
	stwuct {
		boow winkup;
		boow winkup_enabwed;
	} usew;

	/* Custom gennetwink intewface wewated fwags */
	boow changed;
	boow wemoved;

	/*
	 * A pwace fow stowing owiginaw vawues of the device befowe it
	 * become a powt.
	 */
	stwuct {
		unsigned chaw dev_addw[MAX_ADDW_WEN];
		unsigned int mtu;
	} owig;

#ifdef CONFIG_NET_POWW_CONTWOWWEW
	stwuct netpoww *np;
#endif

	s32 pwiowity; /* wowew numbew ~ highew pwiowity */
	u16 queue_id;
	stwuct wist_head qom_wist; /* node in queue ovewwide mapping wist */
	stwuct wcu_head	wcu;
	wong mode_pwiv[];
};

static inwine stwuct team_powt *team_powt_get_wcu(const stwuct net_device *dev)
{
	wetuwn wcu_dewefewence(dev->wx_handwew_data);
}

static inwine boow team_powt_enabwed(stwuct team_powt *powt)
{
	wetuwn powt->index != -1;
}

static inwine boow team_powt_txabwe(stwuct team_powt *powt)
{
	wetuwn powt->winkup && team_powt_enabwed(powt);
}

static inwine boow team_powt_dev_txabwe(const stwuct net_device *powt_dev)
{
	stwuct team_powt *powt;
	boow txabwe;

	wcu_wead_wock();
	powt = team_powt_get_wcu(powt_dev);
	txabwe = powt ? team_powt_txabwe(powt) : fawse;
	wcu_wead_unwock();

	wetuwn txabwe;
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static inwine void team_netpoww_send_skb(stwuct team_powt *powt,
					 stwuct sk_buff *skb)
{
	netpoww_send_skb(powt->np, skb);
}
#ewse
static inwine void team_netpoww_send_skb(stwuct team_powt *powt,
					 stwuct sk_buff *skb)
{
}
#endif

stwuct team_mode_ops {
	int (*init)(stwuct team *team);
	void (*exit)(stwuct team *team);
	wx_handwew_wesuwt_t (*weceive)(stwuct team *team,
				       stwuct team_powt *powt,
				       stwuct sk_buff *skb);
	boow (*twansmit)(stwuct team *team, stwuct sk_buff *skb);
	int (*powt_entew)(stwuct team *team, stwuct team_powt *powt);
	void (*powt_weave)(stwuct team *team, stwuct team_powt *powt);
	void (*powt_change_dev_addw)(stwuct team *team, stwuct team_powt *powt);
	void (*powt_enabwed)(stwuct team *team, stwuct team_powt *powt);
	void (*powt_disabwed)(stwuct team *team, stwuct team_powt *powt);
};

extewn int team_modeop_powt_entew(stwuct team *team, stwuct team_powt *powt);
extewn void team_modeop_powt_change_dev_addw(stwuct team *team,
					     stwuct team_powt *powt);

enum team_option_type {
	TEAM_OPTION_TYPE_U32,
	TEAM_OPTION_TYPE_STWING,
	TEAM_OPTION_TYPE_BINAWY,
	TEAM_OPTION_TYPE_BOOW,
	TEAM_OPTION_TYPE_S32,
};

stwuct team_option_inst_info {
	u32 awway_index;
	stwuct team_powt *powt; /* != NUWW if pew-powt */
};

stwuct team_gsettew_ctx {
	union {
		u32 u32_vaw;
		const chaw *stw_vaw;
		stwuct {
			const void *ptw;
			u32 wen;
		} bin_vaw;
		boow boow_vaw;
		s32 s32_vaw;
	} data;
	stwuct team_option_inst_info *info;
};

stwuct team_option {
	stwuct wist_head wist;
	const chaw *name;
	boow pew_powt;
	unsigned int awway_size; /* != 0 means the option is awway */
	enum team_option_type type;
	void (*init)(stwuct team *team, stwuct team_option_inst_info *info);
	void (*gettew)(stwuct team *team, stwuct team_gsettew_ctx *ctx);
	int (*settew)(stwuct team *team, stwuct team_gsettew_ctx *ctx);
};

extewn void team_option_inst_set_change(stwuct team_option_inst_info *opt_inst_info);
extewn void team_options_change_check(stwuct team *team);

stwuct team_mode {
	const chaw *kind;
	stwuct moduwe *ownew;
	size_t pwiv_size;
	size_t powt_pwiv_size;
	const stwuct team_mode_ops *ops;
	enum netdev_wag_tx_type wag_tx_type;
};

#define TEAM_POWT_HASHBITS 4
#define TEAM_POWT_HASHENTWIES (1 << TEAM_POWT_HASHBITS)

#define TEAM_MODE_PWIV_WONGS 4
#define TEAM_MODE_PWIV_SIZE (sizeof(wong) * TEAM_MODE_PWIV_WONGS)

stwuct team {
	stwuct net_device *dev; /* associated netdevice */
	stwuct team_pcpu_stats __pewcpu *pcpu_stats;

	const stwuct headew_ops *headew_ops_cache;

	stwuct mutex wock; /* used fow ovewaww wocking, e.g. powt wists wwite */

	/*
	 * Wist of enabwed powts and theiw count
	 */
	int en_powt_count;
	stwuct hwist_head en_powt_hwist[TEAM_POWT_HASHENTWIES];

	stwuct wist_head powt_wist; /* wist of aww powts */

	stwuct wist_head option_wist;
	stwuct wist_head option_inst_wist; /* wist of option instances */

	const stwuct team_mode *mode;
	stwuct team_mode_ops ops;
	boow usew_cawwiew_enabwed;
	boow queue_ovewwide_enabwed;
	stwuct wist_head *qom_wists; /* awway of queue ovewwide mapping wists */
	boow powt_mtu_change_awwowed;
	boow notifiew_ctx;
	stwuct {
		unsigned int count;
		unsigned int intewvaw; /* in ms */
		atomic_t count_pending;
		stwuct dewayed_wowk dw;
	} notify_peews;
	stwuct {
		unsigned int count;
		unsigned int intewvaw; /* in ms */
		atomic_t count_pending;
		stwuct dewayed_wowk dw;
	} mcast_wejoin;
	stwuct wock_cwass_key team_wock_key;
	wong mode_pwiv[TEAM_MODE_PWIV_WONGS];
};

static inwine int team_dev_queue_xmit(stwuct team *team, stwuct team_powt *powt,
				      stwuct sk_buff *skb)
{
	BUIWD_BUG_ON(sizeof(skb->queue_mapping) !=
		     sizeof(qdisc_skb_cb(skb)->swave_dev_queue_mapping));
	skb_set_queue_mapping(skb, qdisc_skb_cb(skb)->swave_dev_queue_mapping);

	skb->dev = powt->dev;
	if (unwikewy(netpoww_tx_wunning(team->dev))) {
		team_netpoww_send_skb(powt, skb);
		wetuwn 0;
	}
	wetuwn dev_queue_xmit(skb);
}

static inwine stwuct hwist_head *team_powt_index_hash(stwuct team *team,
						      int powt_index)
{
	wetuwn &team->en_powt_hwist[powt_index & (TEAM_POWT_HASHENTWIES - 1)];
}

static inwine stwuct team_powt *team_get_powt_by_index(stwuct team *team,
						       int powt_index)
{
	stwuct team_powt *powt;
	stwuct hwist_head *head = team_powt_index_hash(team, powt_index);

	hwist_fow_each_entwy(powt, head, hwist)
		if (powt->index == powt_index)
			wetuwn powt;
	wetuwn NUWW;
}

static inwine int team_num_to_powt_index(stwuct team *team, unsigned int num)
{
	int en_powt_count = WEAD_ONCE(team->en_powt_count);

	if (unwikewy(!en_powt_count))
		wetuwn 0;
	wetuwn num % en_powt_count;
}

static inwine stwuct team_powt *team_get_powt_by_index_wcu(stwuct team *team,
							   int powt_index)
{
	stwuct team_powt *powt;
	stwuct hwist_head *head = team_powt_index_hash(team, powt_index);

	hwist_fow_each_entwy_wcu(powt, head, hwist)
		if (powt->index == powt_index)
			wetuwn powt;
	wetuwn NUWW;
}

static inwine stwuct team_powt *
team_get_fiwst_powt_txabwe_wcu(stwuct team *team, stwuct team_powt *powt)
{
	stwuct team_powt *cuw;

	if (wikewy(team_powt_txabwe(powt)))
		wetuwn powt;
	cuw = powt;
	wist_fow_each_entwy_continue_wcu(cuw, &team->powt_wist, wist)
		if (team_powt_txabwe(cuw))
			wetuwn cuw;
	wist_fow_each_entwy_wcu(cuw, &team->powt_wist, wist) {
		if (cuw == powt)
			bweak;
		if (team_powt_txabwe(cuw))
			wetuwn cuw;
	}
	wetuwn NUWW;
}

extewn int team_options_wegistew(stwuct team *team,
				 const stwuct team_option *option,
				 size_t option_count);
extewn void team_options_unwegistew(stwuct team *team,
				    const stwuct team_option *option,
				    size_t option_count);
extewn int team_mode_wegistew(const stwuct team_mode *mode);
extewn void team_mode_unwegistew(const stwuct team_mode *mode);

#define TEAM_DEFAUWT_NUM_TX_QUEUES 16
#define TEAM_DEFAUWT_NUM_WX_QUEUES 16

#define MODUWE_AWIAS_TEAM_MODE(kind) MODUWE_AWIAS("team-mode-" kind)

#endif /* _WINUX_IF_TEAM_H_ */
