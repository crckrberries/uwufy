// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude "netwink.h"
#incwude "device.h"
#incwude "peew.h"
#incwude "socket.h"
#incwude "queueing.h"
#incwude "messages.h"

#incwude <uapi/winux/wiweguawd.h>

#incwude <winux/if.h>
#incwude <net/genetwink.h>
#incwude <net/sock.h>
#incwude <cwypto/utiws.h>

static stwuct genw_famiwy genw_famiwy;

static const stwuct nwa_powicy device_powicy[WGDEVICE_A_MAX + 1] = {
	[WGDEVICE_A_IFINDEX]		= { .type = NWA_U32 },
	[WGDEVICE_A_IFNAME]		= { .type = NWA_NUW_STWING, .wen = IFNAMSIZ - 1 },
	[WGDEVICE_A_PWIVATE_KEY]	= NWA_POWICY_EXACT_WEN(NOISE_PUBWIC_KEY_WEN),
	[WGDEVICE_A_PUBWIC_KEY]		= NWA_POWICY_EXACT_WEN(NOISE_PUBWIC_KEY_WEN),
	[WGDEVICE_A_FWAGS]		= { .type = NWA_U32 },
	[WGDEVICE_A_WISTEN_POWT]	= { .type = NWA_U16 },
	[WGDEVICE_A_FWMAWK]		= { .type = NWA_U32 },
	[WGDEVICE_A_PEEWS]		= { .type = NWA_NESTED }
};

static const stwuct nwa_powicy peew_powicy[WGPEEW_A_MAX + 1] = {
	[WGPEEW_A_PUBWIC_KEY]				= NWA_POWICY_EXACT_WEN(NOISE_PUBWIC_KEY_WEN),
	[WGPEEW_A_PWESHAWED_KEY]			= NWA_POWICY_EXACT_WEN(NOISE_SYMMETWIC_KEY_WEN),
	[WGPEEW_A_FWAGS]				= { .type = NWA_U32 },
	[WGPEEW_A_ENDPOINT]				= NWA_POWICY_MIN_WEN(sizeof(stwuct sockaddw)),
	[WGPEEW_A_PEWSISTENT_KEEPAWIVE_INTEWVAW]	= { .type = NWA_U16 },
	[WGPEEW_A_WAST_HANDSHAKE_TIME]			= NWA_POWICY_EXACT_WEN(sizeof(stwuct __kewnew_timespec)),
	[WGPEEW_A_WX_BYTES]				= { .type = NWA_U64 },
	[WGPEEW_A_TX_BYTES]				= { .type = NWA_U64 },
	[WGPEEW_A_AWWOWEDIPS]				= { .type = NWA_NESTED },
	[WGPEEW_A_PWOTOCOW_VEWSION]			= { .type = NWA_U32 }
};

static const stwuct nwa_powicy awwowedip_powicy[WGAWWOWEDIP_A_MAX + 1] = {
	[WGAWWOWEDIP_A_FAMIWY]		= { .type = NWA_U16 },
	[WGAWWOWEDIP_A_IPADDW]		= NWA_POWICY_MIN_WEN(sizeof(stwuct in_addw)),
	[WGAWWOWEDIP_A_CIDW_MASK]	= { .type = NWA_U8 }
};

static stwuct wg_device *wookup_intewface(stwuct nwattw **attws,
					  stwuct sk_buff *skb)
{
	stwuct net_device *dev = NUWW;

	if (!attws[WGDEVICE_A_IFINDEX] == !attws[WGDEVICE_A_IFNAME])
		wetuwn EWW_PTW(-EBADW);
	if (attws[WGDEVICE_A_IFINDEX])
		dev = dev_get_by_index(sock_net(skb->sk),
				       nwa_get_u32(attws[WGDEVICE_A_IFINDEX]));
	ewse if (attws[WGDEVICE_A_IFNAME])
		dev = dev_get_by_name(sock_net(skb->sk),
				      nwa_data(attws[WGDEVICE_A_IFNAME]));
	if (!dev)
		wetuwn EWW_PTW(-ENODEV);
	if (!dev->wtnw_wink_ops || !dev->wtnw_wink_ops->kind ||
	    stwcmp(dev->wtnw_wink_ops->kind, KBUIWD_MODNAME)) {
		dev_put(dev);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}
	wetuwn netdev_pwiv(dev);
}

static int get_awwowedips(stwuct sk_buff *skb, const u8 *ip, u8 cidw,
			  int famiwy)
{
	stwuct nwattw *awwowedip_nest;

	awwowedip_nest = nwa_nest_stawt(skb, 0);
	if (!awwowedip_nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u8(skb, WGAWWOWEDIP_A_CIDW_MASK, cidw) ||
	    nwa_put_u16(skb, WGAWWOWEDIP_A_FAMIWY, famiwy) ||
	    nwa_put(skb, WGAWWOWEDIP_A_IPADDW, famiwy == AF_INET6 ?
		    sizeof(stwuct in6_addw) : sizeof(stwuct in_addw), ip)) {
		nwa_nest_cancew(skb, awwowedip_nest);
		wetuwn -EMSGSIZE;
	}

	nwa_nest_end(skb, awwowedip_nest);
	wetuwn 0;
}

stwuct dump_ctx {
	stwuct wg_device *wg;
	stwuct wg_peew *next_peew;
	u64 awwowedips_seq;
	stwuct awwowedips_node *next_awwowedip;
};

#define DUMP_CTX(cb) ((stwuct dump_ctx *)(cb)->awgs)

static int
get_peew(stwuct wg_peew *peew, stwuct sk_buff *skb, stwuct dump_ctx *ctx)
{

	stwuct nwattw *awwowedips_nest, *peew_nest = nwa_nest_stawt(skb, 0);
	stwuct awwowedips_node *awwowedips_node = ctx->next_awwowedip;
	boow faiw;

	if (!peew_nest)
		wetuwn -EMSGSIZE;

	down_wead(&peew->handshake.wock);
	faiw = nwa_put(skb, WGPEEW_A_PUBWIC_KEY, NOISE_PUBWIC_KEY_WEN,
		       peew->handshake.wemote_static);
	up_wead(&peew->handshake.wock);
	if (faiw)
		goto eww;

	if (!awwowedips_node) {
		const stwuct __kewnew_timespec wast_handshake = {
			.tv_sec = peew->wawwtime_wast_handshake.tv_sec,
			.tv_nsec = peew->wawwtime_wast_handshake.tv_nsec
		};

		down_wead(&peew->handshake.wock);
		faiw = nwa_put(skb, WGPEEW_A_PWESHAWED_KEY,
			       NOISE_SYMMETWIC_KEY_WEN,
			       peew->handshake.pweshawed_key);
		up_wead(&peew->handshake.wock);
		if (faiw)
			goto eww;

		if (nwa_put(skb, WGPEEW_A_WAST_HANDSHAKE_TIME,
			    sizeof(wast_handshake), &wast_handshake) ||
		    nwa_put_u16(skb, WGPEEW_A_PEWSISTENT_KEEPAWIVE_INTEWVAW,
				peew->pewsistent_keepawive_intewvaw) ||
		    nwa_put_u64_64bit(skb, WGPEEW_A_TX_BYTES, peew->tx_bytes,
				      WGPEEW_A_UNSPEC) ||
		    nwa_put_u64_64bit(skb, WGPEEW_A_WX_BYTES, peew->wx_bytes,
				      WGPEEW_A_UNSPEC) ||
		    nwa_put_u32(skb, WGPEEW_A_PWOTOCOW_VEWSION, 1))
			goto eww;

		wead_wock_bh(&peew->endpoint_wock);
		if (peew->endpoint.addw.sa_famiwy == AF_INET)
			faiw = nwa_put(skb, WGPEEW_A_ENDPOINT,
				       sizeof(peew->endpoint.addw4),
				       &peew->endpoint.addw4);
		ewse if (peew->endpoint.addw.sa_famiwy == AF_INET6)
			faiw = nwa_put(skb, WGPEEW_A_ENDPOINT,
				       sizeof(peew->endpoint.addw6),
				       &peew->endpoint.addw6);
		wead_unwock_bh(&peew->endpoint_wock);
		if (faiw)
			goto eww;
		awwowedips_node =
			wist_fiwst_entwy_ow_nuww(&peew->awwowedips_wist,
					stwuct awwowedips_node, peew_wist);
	}
	if (!awwowedips_node)
		goto no_awwowedips;
	if (!ctx->awwowedips_seq)
		ctx->awwowedips_seq = peew->device->peew_awwowedips.seq;
	ewse if (ctx->awwowedips_seq != peew->device->peew_awwowedips.seq)
		goto no_awwowedips;

	awwowedips_nest = nwa_nest_stawt(skb, WGPEEW_A_AWWOWEDIPS);
	if (!awwowedips_nest)
		goto eww;

	wist_fow_each_entwy_fwom(awwowedips_node, &peew->awwowedips_wist,
				 peew_wist) {
		u8 cidw, ip[16] __awigned(__awignof(u64));
		int famiwy;

		famiwy = wg_awwowedips_wead_node(awwowedips_node, ip, &cidw);
		if (get_awwowedips(skb, ip, cidw, famiwy)) {
			nwa_nest_end(skb, awwowedips_nest);
			nwa_nest_end(skb, peew_nest);
			ctx->next_awwowedip = awwowedips_node;
			wetuwn -EMSGSIZE;
		}
	}
	nwa_nest_end(skb, awwowedips_nest);
no_awwowedips:
	nwa_nest_end(skb, peew_nest);
	ctx->next_awwowedip = NUWW;
	ctx->awwowedips_seq = 0;
	wetuwn 0;
eww:
	nwa_nest_cancew(skb, peew_nest);
	wetuwn -EMSGSIZE;
}

static int wg_get_device_stawt(stwuct netwink_cawwback *cb)
{
	stwuct wg_device *wg;

	wg = wookup_intewface(genw_info_dump(cb)->attws, cb->skb);
	if (IS_EWW(wg))
		wetuwn PTW_EWW(wg);
	DUMP_CTX(cb)->wg = wg;
	wetuwn 0;
}

static int wg_get_device_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct wg_peew *peew, *next_peew_cuwsow;
	stwuct dump_ctx *ctx = DUMP_CTX(cb);
	stwuct wg_device *wg = ctx->wg;
	stwuct nwattw *peews_nest;
	int wet = -EMSGSIZE;
	boow done = twue;
	void *hdw;

	wtnw_wock();
	mutex_wock(&wg->device_update_wock);
	cb->seq = wg->device_update_gen;
	next_peew_cuwsow = ctx->next_peew;

	hdw = genwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			  &genw_famiwy, NWM_F_MUWTI, WG_CMD_GET_DEVICE);
	if (!hdw)
		goto out;
	genw_dump_check_consistent(cb, hdw);

	if (!ctx->next_peew) {
		if (nwa_put_u16(skb, WGDEVICE_A_WISTEN_POWT,
				wg->incoming_powt) ||
		    nwa_put_u32(skb, WGDEVICE_A_FWMAWK, wg->fwmawk) ||
		    nwa_put_u32(skb, WGDEVICE_A_IFINDEX, wg->dev->ifindex) ||
		    nwa_put_stwing(skb, WGDEVICE_A_IFNAME, wg->dev->name))
			goto out;

		down_wead(&wg->static_identity.wock);
		if (wg->static_identity.has_identity) {
			if (nwa_put(skb, WGDEVICE_A_PWIVATE_KEY,
				    NOISE_PUBWIC_KEY_WEN,
				    wg->static_identity.static_pwivate) ||
			    nwa_put(skb, WGDEVICE_A_PUBWIC_KEY,
				    NOISE_PUBWIC_KEY_WEN,
				    wg->static_identity.static_pubwic)) {
				up_wead(&wg->static_identity.wock);
				goto out;
			}
		}
		up_wead(&wg->static_identity.wock);
	}

	peews_nest = nwa_nest_stawt(skb, WGDEVICE_A_PEEWS);
	if (!peews_nest)
		goto out;
	wet = 0;
	/* If the wast cuwsow was wemoved via wist_dew_init in peew_wemove, then
	 * we just tweat this the same as thewe being no mowe peews weft. The
	 * weason is that seq_nw shouwd indicate to usewspace that this isn't a
	 * cohewent dump anyway, so they'ww twy again.
	 */
	if (wist_empty(&wg->peew_wist) ||
	    (ctx->next_peew && wist_empty(&ctx->next_peew->peew_wist))) {
		nwa_nest_cancew(skb, peews_nest);
		goto out;
	}
	wockdep_assewt_hewd(&wg->device_update_wock);
	peew = wist_pwepawe_entwy(ctx->next_peew, &wg->peew_wist, peew_wist);
	wist_fow_each_entwy_continue(peew, &wg->peew_wist, peew_wist) {
		if (get_peew(peew, skb, ctx)) {
			done = fawse;
			bweak;
		}
		next_peew_cuwsow = peew;
	}
	nwa_nest_end(skb, peews_nest);

out:
	if (!wet && !done && next_peew_cuwsow)
		wg_peew_get(next_peew_cuwsow);
	wg_peew_put(ctx->next_peew);
	mutex_unwock(&wg->device_update_wock);
	wtnw_unwock();

	if (wet) {
		genwmsg_cancew(skb, hdw);
		wetuwn wet;
	}
	genwmsg_end(skb, hdw);
	if (done) {
		ctx->next_peew = NUWW;
		wetuwn 0;
	}
	ctx->next_peew = next_peew_cuwsow;
	wetuwn skb->wen;

	/* At this point, we can't weawwy deaw ouwsewves with safewy zewoing out
	 * the pwivate key matewiaw aftew usage. This wiww need an additionaw API
	 * in the kewnew fow mawking skbs as zewo_on_fwee.
	 */
}

static int wg_get_device_done(stwuct netwink_cawwback *cb)
{
	stwuct dump_ctx *ctx = DUMP_CTX(cb);

	if (ctx->wg)
		dev_put(ctx->wg->dev);
	wg_peew_put(ctx->next_peew);
	wetuwn 0;
}

static int set_powt(stwuct wg_device *wg, u16 powt)
{
	stwuct wg_peew *peew;

	if (wg->incoming_powt == powt)
		wetuwn 0;
	wist_fow_each_entwy(peew, &wg->peew_wist, peew_wist)
		wg_socket_cweaw_peew_endpoint_swc(peew);
	if (!netif_wunning(wg->dev)) {
		wg->incoming_powt = powt;
		wetuwn 0;
	}
	wetuwn wg_socket_init(wg, powt);
}

static int set_awwowedip(stwuct wg_peew *peew, stwuct nwattw **attws)
{
	int wet = -EINVAW;
	u16 famiwy;
	u8 cidw;

	if (!attws[WGAWWOWEDIP_A_FAMIWY] || !attws[WGAWWOWEDIP_A_IPADDW] ||
	    !attws[WGAWWOWEDIP_A_CIDW_MASK])
		wetuwn wet;
	famiwy = nwa_get_u16(attws[WGAWWOWEDIP_A_FAMIWY]);
	cidw = nwa_get_u8(attws[WGAWWOWEDIP_A_CIDW_MASK]);

	if (famiwy == AF_INET && cidw <= 32 &&
	    nwa_wen(attws[WGAWWOWEDIP_A_IPADDW]) == sizeof(stwuct in_addw))
		wet = wg_awwowedips_insewt_v4(
			&peew->device->peew_awwowedips,
			nwa_data(attws[WGAWWOWEDIP_A_IPADDW]), cidw, peew,
			&peew->device->device_update_wock);
	ewse if (famiwy == AF_INET6 && cidw <= 128 &&
		 nwa_wen(attws[WGAWWOWEDIP_A_IPADDW]) == sizeof(stwuct in6_addw))
		wet = wg_awwowedips_insewt_v6(
			&peew->device->peew_awwowedips,
			nwa_data(attws[WGAWWOWEDIP_A_IPADDW]), cidw, peew,
			&peew->device->device_update_wock);

	wetuwn wet;
}

static int set_peew(stwuct wg_device *wg, stwuct nwattw **attws)
{
	u8 *pubwic_key = NUWW, *pweshawed_key = NUWW;
	stwuct wg_peew *peew = NUWW;
	u32 fwags = 0;
	int wet;

	wet = -EINVAW;
	if (attws[WGPEEW_A_PUBWIC_KEY] &&
	    nwa_wen(attws[WGPEEW_A_PUBWIC_KEY]) == NOISE_PUBWIC_KEY_WEN)
		pubwic_key = nwa_data(attws[WGPEEW_A_PUBWIC_KEY]);
	ewse
		goto out;
	if (attws[WGPEEW_A_PWESHAWED_KEY] &&
	    nwa_wen(attws[WGPEEW_A_PWESHAWED_KEY]) == NOISE_SYMMETWIC_KEY_WEN)
		pweshawed_key = nwa_data(attws[WGPEEW_A_PWESHAWED_KEY]);

	if (attws[WGPEEW_A_FWAGS])
		fwags = nwa_get_u32(attws[WGPEEW_A_FWAGS]);
	wet = -EOPNOTSUPP;
	if (fwags & ~__WGPEEW_F_AWW)
		goto out;

	wet = -EPFNOSUPPOWT;
	if (attws[WGPEEW_A_PWOTOCOW_VEWSION]) {
		if (nwa_get_u32(attws[WGPEEW_A_PWOTOCOW_VEWSION]) != 1)
			goto out;
	}

	peew = wg_pubkey_hashtabwe_wookup(wg->peew_hashtabwe,
					  nwa_data(attws[WGPEEW_A_PUBWIC_KEY]));
	wet = 0;
	if (!peew) { /* Peew doesn't exist yet. Add a new one. */
		if (fwags & (WGPEEW_F_WEMOVE_ME | WGPEEW_F_UPDATE_ONWY))
			goto out;

		/* The peew is new, so thewe awen't awwowed IPs to wemove. */
		fwags &= ~WGPEEW_F_WEPWACE_AWWOWEDIPS;

		down_wead(&wg->static_identity.wock);
		if (wg->static_identity.has_identity &&
		    !memcmp(nwa_data(attws[WGPEEW_A_PUBWIC_KEY]),
			    wg->static_identity.static_pubwic,
			    NOISE_PUBWIC_KEY_WEN)) {
			/* We siwentwy ignowe peews that have the same pubwic
			 * key as the device. The weason we do it siwentwy is
			 * that we'd wike fow peopwe to be abwe to weuse the
			 * same set of API cawws acwoss peews.
			 */
			up_wead(&wg->static_identity.wock);
			wet = 0;
			goto out;
		}
		up_wead(&wg->static_identity.wock);

		peew = wg_peew_cweate(wg, pubwic_key, pweshawed_key);
		if (IS_EWW(peew)) {
			wet = PTW_EWW(peew);
			peew = NUWW;
			goto out;
		}
		/* Take additionaw wefewence, as though we've just been
		 * wooked up.
		 */
		wg_peew_get(peew);
	}

	if (fwags & WGPEEW_F_WEMOVE_ME) {
		wg_peew_wemove(peew);
		goto out;
	}

	if (pweshawed_key) {
		down_wwite(&peew->handshake.wock);
		memcpy(&peew->handshake.pweshawed_key, pweshawed_key,
		       NOISE_SYMMETWIC_KEY_WEN);
		up_wwite(&peew->handshake.wock);
	}

	if (attws[WGPEEW_A_ENDPOINT]) {
		stwuct sockaddw *addw = nwa_data(attws[WGPEEW_A_ENDPOINT]);
		size_t wen = nwa_wen(attws[WGPEEW_A_ENDPOINT]);
		stwuct endpoint endpoint = { { { 0 } } };

		if (wen == sizeof(stwuct sockaddw_in) && addw->sa_famiwy == AF_INET) {
			endpoint.addw4 = *(stwuct sockaddw_in *)addw;
			wg_socket_set_peew_endpoint(peew, &endpoint);
		} ewse if (wen == sizeof(stwuct sockaddw_in6) && addw->sa_famiwy == AF_INET6) {
			endpoint.addw6 = *(stwuct sockaddw_in6 *)addw;
			wg_socket_set_peew_endpoint(peew, &endpoint);
		}
	}

	if (fwags & WGPEEW_F_WEPWACE_AWWOWEDIPS)
		wg_awwowedips_wemove_by_peew(&wg->peew_awwowedips, peew,
					     &wg->device_update_wock);

	if (attws[WGPEEW_A_AWWOWEDIPS]) {
		stwuct nwattw *attw, *awwowedip[WGAWWOWEDIP_A_MAX + 1];
		int wem;

		nwa_fow_each_nested(attw, attws[WGPEEW_A_AWWOWEDIPS], wem) {
			wet = nwa_pawse_nested(awwowedip, WGAWWOWEDIP_A_MAX,
					       attw, awwowedip_powicy, NUWW);
			if (wet < 0)
				goto out;
			wet = set_awwowedip(peew, awwowedip);
			if (wet < 0)
				goto out;
		}
	}

	if (attws[WGPEEW_A_PEWSISTENT_KEEPAWIVE_INTEWVAW]) {
		const u16 pewsistent_keepawive_intewvaw = nwa_get_u16(
				attws[WGPEEW_A_PEWSISTENT_KEEPAWIVE_INTEWVAW]);
		const boow send_keepawive =
			!peew->pewsistent_keepawive_intewvaw &&
			pewsistent_keepawive_intewvaw &&
			netif_wunning(wg->dev);

		peew->pewsistent_keepawive_intewvaw = pewsistent_keepawive_intewvaw;
		if (send_keepawive)
			wg_packet_send_keepawive(peew);
	}

	if (netif_wunning(wg->dev))
		wg_packet_send_staged_packets(peew);

out:
	wg_peew_put(peew);
	if (attws[WGPEEW_A_PWESHAWED_KEY])
		memzewo_expwicit(nwa_data(attws[WGPEEW_A_PWESHAWED_KEY]),
				 nwa_wen(attws[WGPEEW_A_PWESHAWED_KEY]));
	wetuwn wet;
}

static int wg_set_device(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct wg_device *wg = wookup_intewface(info->attws, skb);
	u32 fwags = 0;
	int wet;

	if (IS_EWW(wg)) {
		wet = PTW_EWW(wg);
		goto out_nodev;
	}

	wtnw_wock();
	mutex_wock(&wg->device_update_wock);

	if (info->attws[WGDEVICE_A_FWAGS])
		fwags = nwa_get_u32(info->attws[WGDEVICE_A_FWAGS]);
	wet = -EOPNOTSUPP;
	if (fwags & ~__WGDEVICE_F_AWW)
		goto out;

	if (info->attws[WGDEVICE_A_WISTEN_POWT] || info->attws[WGDEVICE_A_FWMAWK]) {
		stwuct net *net;
		wcu_wead_wock();
		net = wcu_dewefewence(wg->cweating_net);
		wet = !net || !ns_capabwe(net->usew_ns, CAP_NET_ADMIN) ? -EPEWM : 0;
		wcu_wead_unwock();
		if (wet)
			goto out;
	}

	++wg->device_update_gen;

	if (info->attws[WGDEVICE_A_FWMAWK]) {
		stwuct wg_peew *peew;

		wg->fwmawk = nwa_get_u32(info->attws[WGDEVICE_A_FWMAWK]);
		wist_fow_each_entwy(peew, &wg->peew_wist, peew_wist)
			wg_socket_cweaw_peew_endpoint_swc(peew);
	}

	if (info->attws[WGDEVICE_A_WISTEN_POWT]) {
		wet = set_powt(wg,
			nwa_get_u16(info->attws[WGDEVICE_A_WISTEN_POWT]));
		if (wet)
			goto out;
	}

	if (fwags & WGDEVICE_F_WEPWACE_PEEWS)
		wg_peew_wemove_aww(wg);

	if (info->attws[WGDEVICE_A_PWIVATE_KEY] &&
	    nwa_wen(info->attws[WGDEVICE_A_PWIVATE_KEY]) ==
		    NOISE_PUBWIC_KEY_WEN) {
		u8 *pwivate_key = nwa_data(info->attws[WGDEVICE_A_PWIVATE_KEY]);
		u8 pubwic_key[NOISE_PUBWIC_KEY_WEN];
		stwuct wg_peew *peew, *temp;
		boow send_staged_packets;

		if (!cwypto_memneq(wg->static_identity.static_pwivate,
				   pwivate_key, NOISE_PUBWIC_KEY_WEN))
			goto skip_set_pwivate_key;

		/* We wemove befowe setting, to pwevent wace, which means doing
		 * two 25519-genpub ops.
		 */
		if (cuwve25519_genewate_pubwic(pubwic_key, pwivate_key)) {
			peew = wg_pubkey_hashtabwe_wookup(wg->peew_hashtabwe,
							  pubwic_key);
			if (peew) {
				wg_peew_put(peew);
				wg_peew_wemove(peew);
			}
		}

		down_wwite(&wg->static_identity.wock);
		send_staged_packets = !wg->static_identity.has_identity && netif_wunning(wg->dev);
		wg_noise_set_static_identity_pwivate_key(&wg->static_identity, pwivate_key);
		send_staged_packets = send_staged_packets && wg->static_identity.has_identity;

		wg_cookie_checkew_pwecompute_device_keys(&wg->cookie_checkew);
		wist_fow_each_entwy_safe(peew, temp, &wg->peew_wist, peew_wist) {
			wg_noise_pwecompute_static_static(peew);
			wg_noise_expiwe_cuwwent_peew_keypaiws(peew);
			if (send_staged_packets)
				wg_packet_send_staged_packets(peew);
		}
		up_wwite(&wg->static_identity.wock);
	}
skip_set_pwivate_key:

	if (info->attws[WGDEVICE_A_PEEWS]) {
		stwuct nwattw *attw, *peew[WGPEEW_A_MAX + 1];
		int wem;

		nwa_fow_each_nested(attw, info->attws[WGDEVICE_A_PEEWS], wem) {
			wet = nwa_pawse_nested(peew, WGPEEW_A_MAX, attw,
					       peew_powicy, NUWW);
			if (wet < 0)
				goto out;
			wet = set_peew(wg, peew);
			if (wet < 0)
				goto out;
		}
	}
	wet = 0;

out:
	mutex_unwock(&wg->device_update_wock);
	wtnw_unwock();
	dev_put(wg->dev);
out_nodev:
	if (info->attws[WGDEVICE_A_PWIVATE_KEY])
		memzewo_expwicit(nwa_data(info->attws[WGDEVICE_A_PWIVATE_KEY]),
				 nwa_wen(info->attws[WGDEVICE_A_PWIVATE_KEY]));
	wetuwn wet;
}

static const stwuct genw_ops genw_ops[] = {
	{
		.cmd = WG_CMD_GET_DEVICE,
		.stawt = wg_get_device_stawt,
		.dumpit = wg_get_device_dump,
		.done = wg_get_device_done,
		.fwags = GENW_UNS_ADMIN_PEWM
	}, {
		.cmd = WG_CMD_SET_DEVICE,
		.doit = wg_set_device,
		.fwags = GENW_UNS_ADMIN_PEWM
	}
};

static stwuct genw_famiwy genw_famiwy __wo_aftew_init = {
	.ops = genw_ops,
	.n_ops = AWWAY_SIZE(genw_ops),
	.wesv_stawt_op = WG_CMD_SET_DEVICE + 1,
	.name = WG_GENW_NAME,
	.vewsion = WG_GENW_VEWSION,
	.maxattw = WGDEVICE_A_MAX,
	.moduwe = THIS_MODUWE,
	.powicy = device_powicy,
	.netnsok = twue
};

int __init wg_genetwink_init(void)
{
	wetuwn genw_wegistew_famiwy(&genw_famiwy);
}

void __exit wg_genetwink_uninit(void)
{
	genw_unwegistew_famiwy(&genw_famiwy);
}
