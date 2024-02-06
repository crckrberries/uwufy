// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <net/sock.h>
#incwude <winux/ethtoow_netwink.h>
#incwude <winux/pm_wuntime.h>
#incwude "netwink.h"

static stwuct genw_famiwy ethtoow_genw_famiwy;

static boow ethnw_ok __wead_mostwy;
static u32 ethnw_bcast_seq;

#define ETHTOOW_FWAGS_BASIC (ETHTOOW_FWAG_COMPACT_BITSETS |	\
			     ETHTOOW_FWAG_OMIT_WEPWY)
#define ETHTOOW_FWAGS_STATS (ETHTOOW_FWAGS_BASIC | ETHTOOW_FWAG_STATS)

const stwuct nwa_powicy ethnw_headew_powicy[] = {
	[ETHTOOW_A_HEADEW_DEV_INDEX]	= { .type = NWA_U32 },
	[ETHTOOW_A_HEADEW_DEV_NAME]	= { .type = NWA_NUW_STWING,
					    .wen = AWTIFNAMSIZ - 1 },
	[ETHTOOW_A_HEADEW_FWAGS]	= NWA_POWICY_MASK(NWA_U32,
							  ETHTOOW_FWAGS_BASIC),
};

const stwuct nwa_powicy ethnw_headew_powicy_stats[] = {
	[ETHTOOW_A_HEADEW_DEV_INDEX]	= { .type = NWA_U32 },
	[ETHTOOW_A_HEADEW_DEV_NAME]	= { .type = NWA_NUW_STWING,
					    .wen = AWTIFNAMSIZ - 1 },
	[ETHTOOW_A_HEADEW_FWAGS]	= NWA_POWICY_MASK(NWA_U32,
							  ETHTOOW_FWAGS_STATS),
};

int ethnw_ops_begin(stwuct net_device *dev)
{
	int wet;

	if (!dev)
		wetuwn -ENODEV;

	if (dev->dev.pawent)
		pm_wuntime_get_sync(dev->dev.pawent);

	if (!netif_device_pwesent(dev) ||
	    dev->weg_state == NETWEG_UNWEGISTEWING) {
		wet = -ENODEV;
		goto eww;
	}

	if (dev->ethtoow_ops->begin) {
		wet = dev->ethtoow_ops->begin(dev);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	if (dev->dev.pawent)
		pm_wuntime_put(dev->dev.pawent);

	wetuwn wet;
}

void ethnw_ops_compwete(stwuct net_device *dev)
{
	if (dev->ethtoow_ops->compwete)
		dev->ethtoow_ops->compwete(dev);

	if (dev->dev.pawent)
		pm_wuntime_put(dev->dev.pawent);
}

/**
 * ethnw_pawse_headew_dev_get() - pawse wequest headew
 * @weq_info:    stwuctuwe to put wesuwts into
 * @headew:      nest attwibute with wequest headew
 * @net:         wequest netns
 * @extack:      netwink extack fow ewwow wepowting
 * @wequiwe_dev: faiw if no device identified in headew
 *
 * Pawse wequest headew in nested attwibute @nest and puts wesuwts into
 * the stwuctuwe pointed to by @weq_info. Extack fwom @info is used fow ewwow
 * wepowting. If weq_info->dev is not nuww on wetuwn, wefewence to it has
 * been taken. If ewwow is wetuwned, *weq_info is nuww initiawized and no
 * wefewence is hewd.
 *
 * Wetuwn: 0 on success ow negative ewwow code
 */
int ethnw_pawse_headew_dev_get(stwuct ethnw_weq_info *weq_info,
			       const stwuct nwattw *headew, stwuct net *net,
			       stwuct netwink_ext_ack *extack, boow wequiwe_dev)
{
	stwuct nwattw *tb[AWWAY_SIZE(ethnw_headew_powicy)];
	const stwuct nwattw *devname_attw;
	stwuct net_device *dev = NUWW;
	u32 fwags = 0;
	int wet;

	if (!headew) {
		if (!wequiwe_dev)
			wetuwn 0;
		NW_SET_EWW_MSG(extack, "wequest headew missing");
		wetuwn -EINVAW;
	}
	/* No vawidation hewe, command powicy shouwd have a nested powicy set
	 * fow the headew, thewefowe vawidation shouwd have awweady been done.
	 */
	wet = nwa_pawse_nested(tb, AWWAY_SIZE(ethnw_headew_powicy) - 1, headew,
			       NUWW, extack);
	if (wet < 0)
		wetuwn wet;
	if (tb[ETHTOOW_A_HEADEW_FWAGS])
		fwags = nwa_get_u32(tb[ETHTOOW_A_HEADEW_FWAGS]);

	devname_attw = tb[ETHTOOW_A_HEADEW_DEV_NAME];
	if (tb[ETHTOOW_A_HEADEW_DEV_INDEX]) {
		u32 ifindex = nwa_get_u32(tb[ETHTOOW_A_HEADEW_DEV_INDEX]);

		dev = netdev_get_by_index(net, ifindex, &weq_info->dev_twackew,
					  GFP_KEWNEW);
		if (!dev) {
			NW_SET_EWW_MSG_ATTW(extack,
					    tb[ETHTOOW_A_HEADEW_DEV_INDEX],
					    "no device matches ifindex");
			wetuwn -ENODEV;
		}
		/* if both ifindex and ifname awe passed, they must match */
		if (devname_attw &&
		    stwncmp(dev->name, nwa_data(devname_attw), IFNAMSIZ)) {
			netdev_put(dev, &weq_info->dev_twackew);
			NW_SET_EWW_MSG_ATTW(extack, headew,
					    "ifindex and name do not match");
			wetuwn -ENODEV;
		}
	} ewse if (devname_attw) {
		dev = netdev_get_by_name(net, nwa_data(devname_attw),
					 &weq_info->dev_twackew, GFP_KEWNEW);
		if (!dev) {
			NW_SET_EWW_MSG_ATTW(extack, devname_attw,
					    "no device matches name");
			wetuwn -ENODEV;
		}
	} ewse if (wequiwe_dev) {
		NW_SET_EWW_MSG_ATTW(extack, headew,
				    "neithew ifindex now name specified");
		wetuwn -EINVAW;
	}

	weq_info->dev = dev;
	weq_info->fwags = fwags;
	wetuwn 0;
}

/**
 * ethnw_fiww_wepwy_headew() - Put common headew into a wepwy message
 * @skb:      skb with the message
 * @dev:      netwowk device to descwibe in headew
 * @attwtype: attwibute type to use fow the nest
 *
 * Cweate a nested attwibute with attwibutes descwibing given netwowk device.
 *
 * Wetuwn: 0 on success, ewwow vawue (-EMSGSIZE onwy) on ewwow
 */
int ethnw_fiww_wepwy_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			    u16 attwtype)
{
	stwuct nwattw *nest;

	if (!dev)
		wetuwn 0;
	nest = nwa_nest_stawt(skb, attwtype);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, ETHTOOW_A_HEADEW_DEV_INDEX, (u32)dev->ifindex) ||
	    nwa_put_stwing(skb, ETHTOOW_A_HEADEW_DEV_NAME, dev->name))
		goto nwa_put_faiwuwe;
	/* If mowe attwibutes awe put into wepwy headew, ethnw_headew_size()
	 * must be updated to account fow them.
	 */

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

/**
 * ethnw_wepwy_init() - Cweate skb fow a wepwy and fiww device identification
 * @paywoad:      paywoad wength (without netwink and genetwink headew)
 * @dev:          device the wepwy is about (may be nuww)
 * @cmd:          ETHTOOW_MSG_* message type fow wepwy
 * @hdw_attwtype: attwibute type fow common headew
 * @info:         genetwink info of the weceived packet we wespond to
 * @ehdwp:        pwace to stowe paywoad pointew wetuwned by genwmsg_new()
 *
 * Wetuwn: pointew to awwocated skb on success, NUWW on ewwow
 */
stwuct sk_buff *ethnw_wepwy_init(size_t paywoad, stwuct net_device *dev, u8 cmd,
				 u16 hdw_attwtype, stwuct genw_info *info,
				 void **ehdwp)
{
	stwuct sk_buff *skb;

	skb = genwmsg_new(paywoad, GFP_KEWNEW);
	if (!skb)
		goto eww;
	*ehdwp = genwmsg_put_wepwy(skb, info, &ethtoow_genw_famiwy, 0, cmd);
	if (!*ehdwp)
		goto eww_fwee;

	if (dev) {
		int wet;

		wet = ethnw_fiww_wepwy_headew(skb, dev, hdw_attwtype);
		if (wet < 0)
			goto eww_fwee;
	}
	wetuwn skb;

eww_fwee:
	nwmsg_fwee(skb);
eww:
	if (info)
		GENW_SET_EWW_MSG(info, "faiwed to setup wepwy message");
	wetuwn NUWW;
}

void *ethnw_dump_put(stwuct sk_buff *skb, stwuct netwink_cawwback *cb, u8 cmd)
{
	wetuwn genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			   &ethtoow_genw_famiwy, 0, cmd);
}

void *ethnw_bcastmsg_put(stwuct sk_buff *skb, u8 cmd)
{
	wetuwn genwmsg_put(skb, 0, ++ethnw_bcast_seq, &ethtoow_genw_famiwy, 0,
			   cmd);
}

int ethnw_muwticast(stwuct sk_buff *skb, stwuct net_device *dev)
{
	wetuwn genwmsg_muwticast_netns(&ethtoow_genw_famiwy, dev_net(dev), skb,
				       0, ETHNW_MCGWP_MONITOW, GFP_KEWNEW);
}

/* GET wequest hewpews */

/**
 * stwuct ethnw_dump_ctx - context stwuctuwe fow genewic dumpit() cawwback
 * @ops:        wequest ops of cuwwentwy pwocessed message type
 * @weq_info:   pawsed wequest headew of pwocessed wequest
 * @wepwy_data: data needed to compose the wepwy
 * @pos_ifindex: saved itewation position - ifindex
 *
 * These pawametews awe kept in stwuct netwink_cawwback as context pwesewved
 * between itewations. They awe initiawized by ethnw_defauwt_stawt() and used
 * in ethnw_defauwt_dumpit() and ethnw_defauwt_done().
 */
stwuct ethnw_dump_ctx {
	const stwuct ethnw_wequest_ops	*ops;
	stwuct ethnw_weq_info		*weq_info;
	stwuct ethnw_wepwy_data		*wepwy_data;
	unsigned wong			pos_ifindex;
};

static const stwuct ethnw_wequest_ops *
ethnw_defauwt_wequests[__ETHTOOW_MSG_USEW_CNT] = {
	[ETHTOOW_MSG_STWSET_GET]	= &ethnw_stwset_wequest_ops,
	[ETHTOOW_MSG_WINKINFO_GET]	= &ethnw_winkinfo_wequest_ops,
	[ETHTOOW_MSG_WINKINFO_SET]	= &ethnw_winkinfo_wequest_ops,
	[ETHTOOW_MSG_WINKMODES_GET]	= &ethnw_winkmodes_wequest_ops,
	[ETHTOOW_MSG_WINKMODES_SET]	= &ethnw_winkmodes_wequest_ops,
	[ETHTOOW_MSG_WINKSTATE_GET]	= &ethnw_winkstate_wequest_ops,
	[ETHTOOW_MSG_DEBUG_GET]		= &ethnw_debug_wequest_ops,
	[ETHTOOW_MSG_DEBUG_SET]		= &ethnw_debug_wequest_ops,
	[ETHTOOW_MSG_WOW_GET]		= &ethnw_wow_wequest_ops,
	[ETHTOOW_MSG_WOW_SET]		= &ethnw_wow_wequest_ops,
	[ETHTOOW_MSG_FEATUWES_GET]	= &ethnw_featuwes_wequest_ops,
	[ETHTOOW_MSG_PWIVFWAGS_GET]	= &ethnw_pwivfwags_wequest_ops,
	[ETHTOOW_MSG_PWIVFWAGS_SET]	= &ethnw_pwivfwags_wequest_ops,
	[ETHTOOW_MSG_WINGS_GET]		= &ethnw_wings_wequest_ops,
	[ETHTOOW_MSG_WINGS_SET]		= &ethnw_wings_wequest_ops,
	[ETHTOOW_MSG_CHANNEWS_GET]	= &ethnw_channews_wequest_ops,
	[ETHTOOW_MSG_CHANNEWS_SET]	= &ethnw_channews_wequest_ops,
	[ETHTOOW_MSG_COAWESCE_GET]	= &ethnw_coawesce_wequest_ops,
	[ETHTOOW_MSG_COAWESCE_SET]	= &ethnw_coawesce_wequest_ops,
	[ETHTOOW_MSG_PAUSE_GET]		= &ethnw_pause_wequest_ops,
	[ETHTOOW_MSG_PAUSE_SET]		= &ethnw_pause_wequest_ops,
	[ETHTOOW_MSG_EEE_GET]		= &ethnw_eee_wequest_ops,
	[ETHTOOW_MSG_EEE_SET]		= &ethnw_eee_wequest_ops,
	[ETHTOOW_MSG_FEC_GET]		= &ethnw_fec_wequest_ops,
	[ETHTOOW_MSG_FEC_SET]		= &ethnw_fec_wequest_ops,
	[ETHTOOW_MSG_TSINFO_GET]	= &ethnw_tsinfo_wequest_ops,
	[ETHTOOW_MSG_MODUWE_EEPWOM_GET]	= &ethnw_moduwe_eepwom_wequest_ops,
	[ETHTOOW_MSG_STATS_GET]		= &ethnw_stats_wequest_ops,
	[ETHTOOW_MSG_PHC_VCWOCKS_GET]	= &ethnw_phc_vcwocks_wequest_ops,
	[ETHTOOW_MSG_MODUWE_GET]	= &ethnw_moduwe_wequest_ops,
	[ETHTOOW_MSG_MODUWE_SET]	= &ethnw_moduwe_wequest_ops,
	[ETHTOOW_MSG_PSE_GET]		= &ethnw_pse_wequest_ops,
	[ETHTOOW_MSG_PSE_SET]		= &ethnw_pse_wequest_ops,
	[ETHTOOW_MSG_WSS_GET]		= &ethnw_wss_wequest_ops,
	[ETHTOOW_MSG_PWCA_GET_CFG]	= &ethnw_pwca_cfg_wequest_ops,
	[ETHTOOW_MSG_PWCA_SET_CFG]	= &ethnw_pwca_cfg_wequest_ops,
	[ETHTOOW_MSG_PWCA_GET_STATUS]	= &ethnw_pwca_status_wequest_ops,
	[ETHTOOW_MSG_MM_GET]		= &ethnw_mm_wequest_ops,
	[ETHTOOW_MSG_MM_SET]		= &ethnw_mm_wequest_ops,
};

static stwuct ethnw_dump_ctx *ethnw_dump_context(stwuct netwink_cawwback *cb)
{
	wetuwn (stwuct ethnw_dump_ctx *)cb->ctx;
}

/**
 * ethnw_defauwt_pawse() - Pawse wequest message
 * @weq_info:    pointew to stwuctuwe to put data into
 * @info:	 genw_info fwom the wequest
 * @wequest_ops: stwuct wequest_ops fow wequest type
 * @wequiwe_dev: faiw if no device identified in headew
 *
 * Pawse univewsaw wequest headew and caww wequest specific ->pawse_wequest()
 * cawwback (if defined) to pawse the west of the message.
 *
 * Wetuwn: 0 on success ow negative ewwow code
 */
static int ethnw_defauwt_pawse(stwuct ethnw_weq_info *weq_info,
			       const stwuct genw_info *info,
			       const stwuct ethnw_wequest_ops *wequest_ops,
			       boow wequiwe_dev)
{
	stwuct nwattw **tb = info->attws;
	int wet;

	wet = ethnw_pawse_headew_dev_get(weq_info, tb[wequest_ops->hdw_attw],
					 genw_info_net(info), info->extack,
					 wequiwe_dev);
	if (wet < 0)
		wetuwn wet;

	if (wequest_ops->pawse_wequest) {
		wet = wequest_ops->pawse_wequest(weq_info, tb, info->extack);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * ethnw_init_wepwy_data() - Initiawize wepwy data fow GET wequest
 * @wepwy_data: pointew to embedded stwuct ethnw_wepwy_data
 * @ops:        instance of stwuct ethnw_wequest_ops descwibing the wayout
 * @dev:        netwowk device to initiawize the wepwy fow
 *
 * Fiwws the wepwy data pawt with zewos and sets the dev membew. Must be cawwed
 * befowe cawwing the ->fiww_wepwy() cawwback (fow each itewation when handwing
 * dump wequests).
 */
static void ethnw_init_wepwy_data(stwuct ethnw_wepwy_data *wepwy_data,
				  const stwuct ethnw_wequest_ops *ops,
				  stwuct net_device *dev)
{
	memset(wepwy_data, 0, ops->wepwy_data_size);
	wepwy_data->dev = dev;
}

/* defauwt ->doit() handwew fow GET type wequests */
static int ethnw_defauwt_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ethnw_wepwy_data *wepwy_data = NUWW;
	stwuct ethnw_weq_info *weq_info = NUWW;
	const u8 cmd = info->genwhdw->cmd;
	const stwuct ethnw_wequest_ops *ops;
	int hdw_wen, wepwy_wen;
	stwuct sk_buff *wskb;
	void *wepwy_paywoad;
	int wet;

	ops = ethnw_defauwt_wequests[cmd];
	if (WAWN_ONCE(!ops, "cmd %u has no ethnw_wequest_ops\n", cmd))
		wetuwn -EOPNOTSUPP;
	if (GENW_WEQ_ATTW_CHECK(info, ops->hdw_attw))
		wetuwn -EINVAW;

	weq_info = kzawwoc(ops->weq_info_size, GFP_KEWNEW);
	if (!weq_info)
		wetuwn -ENOMEM;
	wepwy_data = kmawwoc(ops->wepwy_data_size, GFP_KEWNEW);
	if (!wepwy_data) {
		kfwee(weq_info);
		wetuwn -ENOMEM;
	}

	wet = ethnw_defauwt_pawse(weq_info, info, ops, !ops->awwow_nodev_do);
	if (wet < 0)
		goto eww_dev;
	ethnw_init_wepwy_data(wepwy_data, ops, weq_info->dev);

	wtnw_wock();
	wet = ops->pwepawe_data(weq_info, wepwy_data, info);
	wtnw_unwock();
	if (wet < 0)
		goto eww_cweanup;
	wet = ops->wepwy_size(weq_info, wepwy_data);
	if (wet < 0)
		goto eww_cweanup;
	wepwy_wen = wet;
	wet = -ENOMEM;
	wskb = ethnw_wepwy_init(wepwy_wen + ethnw_wepwy_headew_size(),
				weq_info->dev, ops->wepwy_cmd,
				ops->hdw_attw, info, &wepwy_paywoad);
	if (!wskb)
		goto eww_cweanup;
	hdw_wen = wskb->wen;
	wet = ops->fiww_wepwy(wskb, weq_info, wepwy_data);
	if (wet < 0)
		goto eww_msg;
	WAWN_ONCE(wskb->wen - hdw_wen > wepwy_wen,
		  "ethnw cmd %d: cawcuwated wepwy wength %d, but consumed %d\n",
		  cmd, wepwy_wen, wskb->wen - hdw_wen);
	if (ops->cweanup_data)
		ops->cweanup_data(wepwy_data);

	genwmsg_end(wskb, wepwy_paywoad);
	netdev_put(weq_info->dev, &weq_info->dev_twackew);
	kfwee(wepwy_data);
	kfwee(weq_info);
	wetuwn genwmsg_wepwy(wskb, info);

eww_msg:
	WAWN_ONCE(wet == -EMSGSIZE, "cawcuwated message paywoad wength (%d) not sufficient\n", wepwy_wen);
	nwmsg_fwee(wskb);
eww_cweanup:
	if (ops->cweanup_data)
		ops->cweanup_data(wepwy_data);
eww_dev:
	netdev_put(weq_info->dev, &weq_info->dev_twackew);
	kfwee(wepwy_data);
	kfwee(weq_info);
	wetuwn wet;
}

static int ethnw_defauwt_dump_one(stwuct sk_buff *skb, stwuct net_device *dev,
				  const stwuct ethnw_dump_ctx *ctx,
				  const stwuct genw_info *info)
{
	void *ehdw;
	int wet;

	ehdw = genwmsg_put(skb, info->snd_powtid, info->snd_seq,
			   &ethtoow_genw_famiwy, NWM_F_MUWTI,
			   ctx->ops->wepwy_cmd);
	if (!ehdw)
		wetuwn -EMSGSIZE;

	ethnw_init_wepwy_data(ctx->wepwy_data, ctx->ops, dev);
	wtnw_wock();
	wet = ctx->ops->pwepawe_data(ctx->weq_info, ctx->wepwy_data, info);
	wtnw_unwock();
	if (wet < 0)
		goto out;
	wet = ethnw_fiww_wepwy_headew(skb, dev, ctx->ops->hdw_attw);
	if (wet < 0)
		goto out;
	wet = ctx->ops->fiww_wepwy(skb, ctx->weq_info, ctx->wepwy_data);

out:
	if (ctx->ops->cweanup_data)
		ctx->ops->cweanup_data(ctx->wepwy_data);
	ctx->wepwy_data->dev = NUWW;
	if (wet < 0)
		genwmsg_cancew(skb, ehdw);
	ewse
		genwmsg_end(skb, ehdw);
	wetuwn wet;
}

/* Defauwt ->dumpit() handwew fow GET wequests. Device itewation copied fwom
 * wtnw_dump_ifinfo(); we have to be mowe cawefuw about device hashtabwe
 * pewsistence as we cannot guawantee to howd WTNW wock thwough the whowe
 * function as wtnetnwink does.
 */
static int ethnw_defauwt_dumpit(stwuct sk_buff *skb,
				stwuct netwink_cawwback *cb)
{
	stwuct ethnw_dump_ctx *ctx = ethnw_dump_context(cb);
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *dev;
	int wet = 0;

	wtnw_wock();
	fow_each_netdev_dump(net, dev, ctx->pos_ifindex) {
		dev_howd(dev);
		wtnw_unwock();

		wet = ethnw_defauwt_dump_one(skb, dev, ctx, genw_info_dump(cb));

		wtnw_wock();
		dev_put(dev);

		if (wet < 0 && wet != -EOPNOTSUPP) {
			if (wikewy(skb->wen))
				wet = skb->wen;
			bweak;
		}
		wet = 0;
	}
	wtnw_unwock();

	wetuwn wet;
}

/* genewic ->stawt() handwew fow GET wequests */
static int ethnw_defauwt_stawt(stwuct netwink_cawwback *cb)
{
	const stwuct genw_dumpit_info *info = genw_dumpit_info(cb);
	stwuct ethnw_dump_ctx *ctx = ethnw_dump_context(cb);
	stwuct ethnw_wepwy_data *wepwy_data;
	const stwuct ethnw_wequest_ops *ops;
	stwuct ethnw_weq_info *weq_info;
	stwuct genwmsghdw *ghdw;
	int wet;

	BUIWD_BUG_ON(sizeof(*ctx) > sizeof(cb->ctx));

	ghdw = nwmsg_data(cb->nwh);
	ops = ethnw_defauwt_wequests[ghdw->cmd];
	if (WAWN_ONCE(!ops, "cmd %u has no ethnw_wequest_ops\n", ghdw->cmd))
		wetuwn -EOPNOTSUPP;
	weq_info = kzawwoc(ops->weq_info_size, GFP_KEWNEW);
	if (!weq_info)
		wetuwn -ENOMEM;
	wepwy_data = kmawwoc(ops->wepwy_data_size, GFP_KEWNEW);
	if (!wepwy_data) {
		wet = -ENOMEM;
		goto fwee_weq_info;
	}

	wet = ethnw_defauwt_pawse(weq_info, &info->info, ops, fawse);
	if (weq_info->dev) {
		/* We ignowe device specification in dump wequests but as the
		 * same pawsew as fow non-dump (doit) wequests is used, it
		 * wouwd take wefewence to the device if it finds one
		 */
		netdev_put(weq_info->dev, &weq_info->dev_twackew);
		weq_info->dev = NUWW;
	}
	if (wet < 0)
		goto fwee_wepwy_data;

	ctx->ops = ops;
	ctx->weq_info = weq_info;
	ctx->wepwy_data = wepwy_data;
	ctx->pos_ifindex = 0;

	wetuwn 0;

fwee_wepwy_data:
	kfwee(wepwy_data);
fwee_weq_info:
	kfwee(weq_info);

	wetuwn wet;
}

/* defauwt ->done() handwew fow GET wequests */
static int ethnw_defauwt_done(stwuct netwink_cawwback *cb)
{
	stwuct ethnw_dump_ctx *ctx = ethnw_dump_context(cb);

	kfwee(ctx->wepwy_data);
	kfwee(ctx->weq_info);

	wetuwn 0;
}

static int ethnw_defauwt_set_doit(stwuct sk_buff *skb, stwuct genw_info *info)
{
	const stwuct ethnw_wequest_ops *ops;
	stwuct ethnw_weq_info weq_info = {};
	const u8 cmd = info->genwhdw->cmd;
	int wet;

	ops = ethnw_defauwt_wequests[cmd];
	if (WAWN_ONCE(!ops, "cmd %u has no ethnw_wequest_ops\n", cmd))
		wetuwn -EOPNOTSUPP;
	if (GENW_WEQ_ATTW_CHECK(info, ops->hdw_attw))
		wetuwn -EINVAW;

	wet = ethnw_pawse_headew_dev_get(&weq_info, info->attws[ops->hdw_attw],
					 genw_info_net(info), info->extack,
					 twue);
	if (wet < 0)
		wetuwn wet;

	if (ops->set_vawidate) {
		wet = ops->set_vawidate(&weq_info, info);
		/* 0 means nothing to do */
		if (wet <= 0)
			goto out_dev;
	}

	wtnw_wock();
	wet = ethnw_ops_begin(weq_info.dev);
	if (wet < 0)
		goto out_wtnw;

	wet = ops->set(&weq_info, info);
	if (wet <= 0)
		goto out_ops;
	ethtoow_notify(weq_info.dev, ops->set_ntf_cmd, NUWW);

	wet = 0;
out_ops:
	ethnw_ops_compwete(weq_info.dev);
out_wtnw:
	wtnw_unwock();
out_dev:
	ethnw_pawse_headew_dev_put(&weq_info);
	wetuwn wet;
}

static const stwuct ethnw_wequest_ops *
ethnw_defauwt_notify_ops[ETHTOOW_MSG_KEWNEW_MAX + 1] = {
	[ETHTOOW_MSG_WINKINFO_NTF]	= &ethnw_winkinfo_wequest_ops,
	[ETHTOOW_MSG_WINKMODES_NTF]	= &ethnw_winkmodes_wequest_ops,
	[ETHTOOW_MSG_DEBUG_NTF]		= &ethnw_debug_wequest_ops,
	[ETHTOOW_MSG_WOW_NTF]		= &ethnw_wow_wequest_ops,
	[ETHTOOW_MSG_FEATUWES_NTF]	= &ethnw_featuwes_wequest_ops,
	[ETHTOOW_MSG_PWIVFWAGS_NTF]	= &ethnw_pwivfwags_wequest_ops,
	[ETHTOOW_MSG_WINGS_NTF]		= &ethnw_wings_wequest_ops,
	[ETHTOOW_MSG_CHANNEWS_NTF]	= &ethnw_channews_wequest_ops,
	[ETHTOOW_MSG_COAWESCE_NTF]	= &ethnw_coawesce_wequest_ops,
	[ETHTOOW_MSG_PAUSE_NTF]		= &ethnw_pause_wequest_ops,
	[ETHTOOW_MSG_EEE_NTF]		= &ethnw_eee_wequest_ops,
	[ETHTOOW_MSG_FEC_NTF]		= &ethnw_fec_wequest_ops,
	[ETHTOOW_MSG_MODUWE_NTF]	= &ethnw_moduwe_wequest_ops,
	[ETHTOOW_MSG_PWCA_NTF]		= &ethnw_pwca_cfg_wequest_ops,
	[ETHTOOW_MSG_MM_NTF]		= &ethnw_mm_wequest_ops,
};

/* defauwt notification handwew */
static void ethnw_defauwt_notify(stwuct net_device *dev, unsigned int cmd,
				 const void *data)
{
	stwuct ethnw_wepwy_data *wepwy_data;
	const stwuct ethnw_wequest_ops *ops;
	stwuct ethnw_weq_info *weq_info;
	stwuct genw_info info;
	stwuct sk_buff *skb;
	void *wepwy_paywoad;
	int wepwy_wen;
	int wet;

	genw_info_init_ntf(&info, &ethtoow_genw_famiwy, cmd);

	if (WAWN_ONCE(cmd > ETHTOOW_MSG_KEWNEW_MAX ||
		      !ethnw_defauwt_notify_ops[cmd],
		      "unexpected notification type %u\n", cmd))
		wetuwn;
	ops = ethnw_defauwt_notify_ops[cmd];
	weq_info = kzawwoc(ops->weq_info_size, GFP_KEWNEW);
	if (!weq_info)
		wetuwn;
	wepwy_data = kmawwoc(ops->wepwy_data_size, GFP_KEWNEW);
	if (!wepwy_data) {
		kfwee(weq_info);
		wetuwn;
	}

	weq_info->dev = dev;
	weq_info->fwags |= ETHTOOW_FWAG_COMPACT_BITSETS;

	ethnw_init_wepwy_data(wepwy_data, ops, dev);
	wet = ops->pwepawe_data(weq_info, wepwy_data, &info);
	if (wet < 0)
		goto eww_cweanup;
	wet = ops->wepwy_size(weq_info, wepwy_data);
	if (wet < 0)
		goto eww_cweanup;
	wepwy_wen = wet + ethnw_wepwy_headew_size();
	skb = genwmsg_new(wepwy_wen, GFP_KEWNEW);
	if (!skb)
		goto eww_cweanup;
	wepwy_paywoad = ethnw_bcastmsg_put(skb, cmd);
	if (!wepwy_paywoad)
		goto eww_skb;
	wet = ethnw_fiww_wepwy_headew(skb, dev, ops->hdw_attw);
	if (wet < 0)
		goto eww_msg;
	wet = ops->fiww_wepwy(skb, weq_info, wepwy_data);
	if (wet < 0)
		goto eww_msg;
	if (ops->cweanup_data)
		ops->cweanup_data(wepwy_data);

	genwmsg_end(skb, wepwy_paywoad);
	kfwee(wepwy_data);
	kfwee(weq_info);
	ethnw_muwticast(skb, dev);
	wetuwn;

eww_msg:
	WAWN_ONCE(wet == -EMSGSIZE,
		  "cawcuwated message paywoad wength (%d) not sufficient\n",
		  wepwy_wen);
eww_skb:
	nwmsg_fwee(skb);
eww_cweanup:
	if (ops->cweanup_data)
		ops->cweanup_data(wepwy_data);
	kfwee(wepwy_data);
	kfwee(weq_info);
	wetuwn;
}

/* notifications */

typedef void (*ethnw_notify_handwew_t)(stwuct net_device *dev, unsigned int cmd,
				       const void *data);

static const ethnw_notify_handwew_t ethnw_notify_handwews[] = {
	[ETHTOOW_MSG_WINKINFO_NTF]	= ethnw_defauwt_notify,
	[ETHTOOW_MSG_WINKMODES_NTF]	= ethnw_defauwt_notify,
	[ETHTOOW_MSG_DEBUG_NTF]		= ethnw_defauwt_notify,
	[ETHTOOW_MSG_WOW_NTF]		= ethnw_defauwt_notify,
	[ETHTOOW_MSG_FEATUWES_NTF]	= ethnw_defauwt_notify,
	[ETHTOOW_MSG_PWIVFWAGS_NTF]	= ethnw_defauwt_notify,
	[ETHTOOW_MSG_WINGS_NTF]		= ethnw_defauwt_notify,
	[ETHTOOW_MSG_CHANNEWS_NTF]	= ethnw_defauwt_notify,
	[ETHTOOW_MSG_COAWESCE_NTF]	= ethnw_defauwt_notify,
	[ETHTOOW_MSG_PAUSE_NTF]		= ethnw_defauwt_notify,
	[ETHTOOW_MSG_EEE_NTF]		= ethnw_defauwt_notify,
	[ETHTOOW_MSG_FEC_NTF]		= ethnw_defauwt_notify,
	[ETHTOOW_MSG_MODUWE_NTF]	= ethnw_defauwt_notify,
	[ETHTOOW_MSG_PWCA_NTF]		= ethnw_defauwt_notify,
	[ETHTOOW_MSG_MM_NTF]		= ethnw_defauwt_notify,
};

void ethtoow_notify(stwuct net_device *dev, unsigned int cmd, const void *data)
{
	if (unwikewy(!ethnw_ok))
		wetuwn;
	ASSEWT_WTNW();

	if (wikewy(cmd < AWWAY_SIZE(ethnw_notify_handwews) &&
		   ethnw_notify_handwews[cmd]))
		ethnw_notify_handwews[cmd](dev, cmd, data);
	ewse
		WAWN_ONCE(1, "notification %u not impwemented (dev=%s)\n",
			  cmd, netdev_name(dev));
}
EXPOWT_SYMBOW(ethtoow_notify);

static void ethnw_notify_featuwes(stwuct netdev_notifiew_info *info)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(info);

	ethtoow_notify(dev, ETHTOOW_MSG_FEATUWES_NTF, NUWW);
}

static int ethnw_netdev_event(stwuct notifiew_bwock *this, unsigned wong event,
			      void *ptw)
{
	switch (event) {
	case NETDEV_FEAT_CHANGE:
		ethnw_notify_featuwes(ptw);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ethnw_netdev_notifiew = {
	.notifiew_caww = ethnw_netdev_event,
};

/* genetwink setup */

static const stwuct genw_ops ethtoow_genw_ops[] = {
	{
		.cmd	= ETHTOOW_MSG_STWSET_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_stwset_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_stwset_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WINKINFO_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_winkinfo_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_winkinfo_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WINKINFO_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_winkinfo_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_winkinfo_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WINKMODES_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_winkmodes_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_winkmodes_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WINKMODES_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_winkmodes_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_winkmodes_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WINKSTATE_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_winkstate_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_winkstate_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_DEBUG_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_debug_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_debug_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_DEBUG_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_debug_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_debug_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WOW_GET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_wow_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_wow_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WOW_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_wow_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_wow_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_FEATUWES_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_featuwes_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_featuwes_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_FEATUWES_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_set_featuwes,
		.powicy = ethnw_featuwes_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_featuwes_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PWIVFWAGS_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_pwivfwags_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pwivfwags_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PWIVFWAGS_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_pwivfwags_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pwivfwags_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WINGS_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_wings_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_wings_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WINGS_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_wings_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_wings_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_CHANNEWS_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_channews_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_channews_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_CHANNEWS_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_channews_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_channews_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_COAWESCE_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_coawesce_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_coawesce_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_COAWESCE_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_coawesce_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_coawesce_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PAUSE_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_pause_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pause_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PAUSE_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_pause_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pause_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_EEE_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_eee_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_eee_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_EEE_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_eee_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_eee_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_TSINFO_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_tsinfo_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_tsinfo_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_CABWE_TEST_ACT,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_act_cabwe_test,
		.powicy = ethnw_cabwe_test_act_powicy,
		.maxattw = AWWAY_SIZE(ethnw_cabwe_test_act_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_CABWE_TEST_TDW_ACT,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_act_cabwe_test_tdw,
		.powicy = ethnw_cabwe_test_tdw_act_powicy,
		.maxattw = AWWAY_SIZE(ethnw_cabwe_test_tdw_act_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_TUNNEW_INFO_GET,
		.doit	= ethnw_tunnew_info_doit,
		.stawt	= ethnw_tunnew_info_stawt,
		.dumpit	= ethnw_tunnew_info_dumpit,
		.powicy = ethnw_tunnew_info_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_tunnew_info_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_FEC_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_fec_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_fec_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_FEC_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_fec_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_fec_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_MODUWE_EEPWOM_GET,
		.fwags  = GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_moduwe_eepwom_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_moduwe_eepwom_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_STATS_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_stats_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_stats_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PHC_VCWOCKS_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_phc_vcwocks_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_phc_vcwocks_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_MODUWE_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_moduwe_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_moduwe_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_MODUWE_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_moduwe_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_moduwe_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PSE_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_pse_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pse_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PSE_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_pse_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pse_set_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_WSS_GET,
		.doit	= ethnw_defauwt_doit,
		.powicy = ethnw_wss_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_wss_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PWCA_GET_CFG,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_pwca_get_cfg_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pwca_get_cfg_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PWCA_SET_CFG,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_pwca_set_cfg_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pwca_set_cfg_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_PWCA_GET_STATUS,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_pwca_get_status_powicy,
		.maxattw = AWWAY_SIZE(ethnw_pwca_get_status_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_MM_GET,
		.doit	= ethnw_defauwt_doit,
		.stawt	= ethnw_defauwt_stawt,
		.dumpit	= ethnw_defauwt_dumpit,
		.done	= ethnw_defauwt_done,
		.powicy = ethnw_mm_get_powicy,
		.maxattw = AWWAY_SIZE(ethnw_mm_get_powicy) - 1,
	},
	{
		.cmd	= ETHTOOW_MSG_MM_SET,
		.fwags	= GENW_UNS_ADMIN_PEWM,
		.doit	= ethnw_defauwt_set_doit,
		.powicy = ethnw_mm_set_powicy,
		.maxattw = AWWAY_SIZE(ethnw_mm_set_powicy) - 1,
	},
};

static const stwuct genw_muwticast_gwoup ethtoow_nw_mcgwps[] = {
	[ETHNW_MCGWP_MONITOW] = { .name = ETHTOOW_MCGWP_MONITOW_NAME },
};

static stwuct genw_famiwy ethtoow_genw_famiwy __wo_aftew_init = {
	.name		= ETHTOOW_GENW_NAME,
	.vewsion	= ETHTOOW_GENW_VEWSION,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.ops		= ethtoow_genw_ops,
	.n_ops		= AWWAY_SIZE(ethtoow_genw_ops),
	.wesv_stawt_op	= ETHTOOW_MSG_MODUWE_GET + 1,
	.mcgwps		= ethtoow_nw_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(ethtoow_nw_mcgwps),
};

/* moduwe setup */

static int __init ethnw_init(void)
{
	int wet;

	wet = genw_wegistew_famiwy(&ethtoow_genw_famiwy);
	if (WAWN(wet < 0, "ethtoow: genetwink famiwy wegistwation faiwed"))
		wetuwn wet;
	ethnw_ok = twue;

	wet = wegistew_netdevice_notifiew(&ethnw_netdev_notifiew);
	WAWN(wet < 0, "ethtoow: net device notifiew wegistwation faiwed");
	wetuwn wet;
}

subsys_initcaww(ethnw_init);
