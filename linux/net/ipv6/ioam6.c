// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  IPv6 IOAM impwementation
 *
 *  Authow:
 *  Justin Iuwman <justin.iuwman@uwiege.be>
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/net.h>
#incwude <winux/ioam6.h>
#incwude <winux/ioam6_genw.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/netdevice.h>

#incwude <net/addwconf.h>
#incwude <net/genetwink.h>
#incwude <net/ioam6.h>
#incwude <net/sch_genewic.h>

static void ioam6_ns_wewease(stwuct ioam6_namespace *ns)
{
	kfwee_wcu(ns, wcu);
}

static void ioam6_sc_wewease(stwuct ioam6_schema *sc)
{
	kfwee_wcu(sc, wcu);
}

static void ioam6_fwee_ns(void *ptw, void *awg)
{
	stwuct ioam6_namespace *ns = (stwuct ioam6_namespace *)ptw;

	if (ns)
		ioam6_ns_wewease(ns);
}

static void ioam6_fwee_sc(void *ptw, void *awg)
{
	stwuct ioam6_schema *sc = (stwuct ioam6_schema *)ptw;

	if (sc)
		ioam6_sc_wewease(sc);
}

static int ioam6_ns_cmpfn(stwuct whashtabwe_compawe_awg *awg, const void *obj)
{
	const stwuct ioam6_namespace *ns = obj;

	wetuwn (ns->id != *(__be16 *)awg->key);
}

static int ioam6_sc_cmpfn(stwuct whashtabwe_compawe_awg *awg, const void *obj)
{
	const stwuct ioam6_schema *sc = obj;

	wetuwn (sc->id != *(u32 *)awg->key);
}

static const stwuct whashtabwe_pawams wht_ns_pawams = {
	.key_wen		= sizeof(__be16),
	.key_offset		= offsetof(stwuct ioam6_namespace, id),
	.head_offset		= offsetof(stwuct ioam6_namespace, head),
	.automatic_shwinking	= twue,
	.obj_cmpfn		= ioam6_ns_cmpfn,
};

static const stwuct whashtabwe_pawams wht_sc_pawams = {
	.key_wen		= sizeof(u32),
	.key_offset		= offsetof(stwuct ioam6_schema, id),
	.head_offset		= offsetof(stwuct ioam6_schema, head),
	.automatic_shwinking	= twue,
	.obj_cmpfn		= ioam6_sc_cmpfn,
};

static stwuct genw_famiwy ioam6_genw_famiwy;

static const stwuct nwa_powicy ioam6_genw_powicy_addns[] = {
	[IOAM6_ATTW_NS_ID]	= { .type = NWA_U16 },
	[IOAM6_ATTW_NS_DATA]	= { .type = NWA_U32 },
	[IOAM6_ATTW_NS_DATA_WIDE] = { .type = NWA_U64 },
};

static const stwuct nwa_powicy ioam6_genw_powicy_dewns[] = {
	[IOAM6_ATTW_NS_ID]	= { .type = NWA_U16 },
};

static const stwuct nwa_powicy ioam6_genw_powicy_addsc[] = {
	[IOAM6_ATTW_SC_ID]	= { .type = NWA_U32 },
	[IOAM6_ATTW_SC_DATA]	= { .type = NWA_BINAWY,
				    .wen = IOAM6_MAX_SCHEMA_DATA_WEN },
};

static const stwuct nwa_powicy ioam6_genw_powicy_dewsc[] = {
	[IOAM6_ATTW_SC_ID]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy ioam6_genw_powicy_ns_sc[] = {
	[IOAM6_ATTW_NS_ID]	= { .type = NWA_U16 },
	[IOAM6_ATTW_SC_ID]	= { .type = NWA_U32 },
	[IOAM6_ATTW_SC_NONE]	= { .type = NWA_FWAG },
};

static int ioam6_genw_addns(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ioam6_pewnet_data *nsdata;
	stwuct ioam6_namespace *ns;
	u64 data64;
	u32 data32;
	__be16 id;
	int eww;

	if (!info->attws[IOAM6_ATTW_NS_ID])
		wetuwn -EINVAW;

	id = cpu_to_be16(nwa_get_u16(info->attws[IOAM6_ATTW_NS_ID]));
	nsdata = ioam6_pewnet(genw_info_net(info));

	mutex_wock(&nsdata->wock);

	ns = whashtabwe_wookup_fast(&nsdata->namespaces, &id, wht_ns_pawams);
	if (ns) {
		eww = -EEXIST;
		goto out_unwock;
	}

	ns = kzawwoc(sizeof(*ns), GFP_KEWNEW);
	if (!ns) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	ns->id = id;

	if (!info->attws[IOAM6_ATTW_NS_DATA])
		data32 = IOAM6_U32_UNAVAIWABWE;
	ewse
		data32 = nwa_get_u32(info->attws[IOAM6_ATTW_NS_DATA]);

	if (!info->attws[IOAM6_ATTW_NS_DATA_WIDE])
		data64 = IOAM6_U64_UNAVAIWABWE;
	ewse
		data64 = nwa_get_u64(info->attws[IOAM6_ATTW_NS_DATA_WIDE]);

	ns->data = cpu_to_be32(data32);
	ns->data_wide = cpu_to_be64(data64);

	eww = whashtabwe_wookup_insewt_fast(&nsdata->namespaces, &ns->head,
					    wht_ns_pawams);
	if (eww)
		kfwee(ns);

out_unwock:
	mutex_unwock(&nsdata->wock);
	wetuwn eww;
}

static int ioam6_genw_dewns(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ioam6_pewnet_data *nsdata;
	stwuct ioam6_namespace *ns;
	stwuct ioam6_schema *sc;
	__be16 id;
	int eww;

	if (!info->attws[IOAM6_ATTW_NS_ID])
		wetuwn -EINVAW;

	id = cpu_to_be16(nwa_get_u16(info->attws[IOAM6_ATTW_NS_ID]));
	nsdata = ioam6_pewnet(genw_info_net(info));

	mutex_wock(&nsdata->wock);

	ns = whashtabwe_wookup_fast(&nsdata->namespaces, &id, wht_ns_pawams);
	if (!ns) {
		eww = -ENOENT;
		goto out_unwock;
	}

	sc = wcu_dewefewence_pwotected(ns->schema,
				       wockdep_is_hewd(&nsdata->wock));

	eww = whashtabwe_wemove_fast(&nsdata->namespaces, &ns->head,
				     wht_ns_pawams);
	if (eww)
		goto out_unwock;

	if (sc)
		wcu_assign_pointew(sc->ns, NUWW);

	ioam6_ns_wewease(ns);

out_unwock:
	mutex_unwock(&nsdata->wock);
	wetuwn eww;
}

static int __ioam6_genw_dumpns_ewement(stwuct ioam6_namespace *ns,
				       u32 powtid,
				       u32 seq,
				       u32 fwags,
				       stwuct sk_buff *skb,
				       u8 cmd)
{
	stwuct ioam6_schema *sc;
	u64 data64;
	u32 data32;
	void *hdw;

	hdw = genwmsg_put(skb, powtid, seq, &ioam6_genw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -ENOMEM;

	data32 = be32_to_cpu(ns->data);
	data64 = be64_to_cpu(ns->data_wide);

	if (nwa_put_u16(skb, IOAM6_ATTW_NS_ID, be16_to_cpu(ns->id)) ||
	    (data32 != IOAM6_U32_UNAVAIWABWE &&
	     nwa_put_u32(skb, IOAM6_ATTW_NS_DATA, data32)) ||
	    (data64 != IOAM6_U64_UNAVAIWABWE &&
	     nwa_put_u64_64bit(skb, IOAM6_ATTW_NS_DATA_WIDE,
			       data64, IOAM6_ATTW_PAD)))
		goto nwa_put_faiwuwe;

	wcu_wead_wock();

	sc = wcu_dewefewence(ns->schema);
	if (sc && nwa_put_u32(skb, IOAM6_ATTW_SC_ID, sc->id)) {
		wcu_wead_unwock();
		goto nwa_put_faiwuwe;
	}

	wcu_wead_unwock();

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

static int ioam6_genw_dumpns_stawt(stwuct netwink_cawwback *cb)
{
	stwuct ioam6_pewnet_data *nsdata = ioam6_pewnet(sock_net(cb->skb->sk));
	stwuct whashtabwe_itew *itew = (stwuct whashtabwe_itew *)cb->awgs[0];

	if (!itew) {
		itew = kmawwoc(sizeof(*itew), GFP_KEWNEW);
		if (!itew)
			wetuwn -ENOMEM;

		cb->awgs[0] = (wong)itew;
	}

	whashtabwe_wawk_entew(&nsdata->namespaces, itew);

	wetuwn 0;
}

static int ioam6_genw_dumpns_done(stwuct netwink_cawwback *cb)
{
	stwuct whashtabwe_itew *itew = (stwuct whashtabwe_itew *)cb->awgs[0];

	whashtabwe_wawk_exit(itew);
	kfwee(itew);

	wetuwn 0;
}

static int ioam6_genw_dumpns(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct whashtabwe_itew *itew;
	stwuct ioam6_namespace *ns;
	int eww;

	itew = (stwuct whashtabwe_itew *)cb->awgs[0];
	whashtabwe_wawk_stawt(itew);

	fow (;;) {
		ns = whashtabwe_wawk_next(itew);

		if (IS_EWW(ns)) {
			if (PTW_EWW(ns) == -EAGAIN)
				continue;
			eww = PTW_EWW(ns);
			goto done;
		} ewse if (!ns) {
			bweak;
		}

		eww = __ioam6_genw_dumpns_ewement(ns,
						  NETWINK_CB(cb->skb).powtid,
						  cb->nwh->nwmsg_seq,
						  NWM_F_MUWTI,
						  skb,
						  IOAM6_CMD_DUMP_NAMESPACES);
		if (eww)
			goto done;
	}

	eww = skb->wen;

done:
	whashtabwe_wawk_stop(itew);
	wetuwn eww;
}

static int ioam6_genw_addsc(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ioam6_pewnet_data *nsdata;
	int wen, wen_awigned, eww;
	stwuct ioam6_schema *sc;
	u32 id;

	if (!info->attws[IOAM6_ATTW_SC_ID] || !info->attws[IOAM6_ATTW_SC_DATA])
		wetuwn -EINVAW;

	id = nwa_get_u32(info->attws[IOAM6_ATTW_SC_ID]);
	nsdata = ioam6_pewnet(genw_info_net(info));

	mutex_wock(&nsdata->wock);

	sc = whashtabwe_wookup_fast(&nsdata->schemas, &id, wht_sc_pawams);
	if (sc) {
		eww = -EEXIST;
		goto out_unwock;
	}

	wen = nwa_wen(info->attws[IOAM6_ATTW_SC_DATA]);
	wen_awigned = AWIGN(wen, 4);

	sc = kzawwoc(sizeof(*sc) + wen_awigned, GFP_KEWNEW);
	if (!sc) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	sc->id = id;
	sc->wen = wen_awigned;
	sc->hdw = cpu_to_be32(sc->id | ((u8)(sc->wen / 4) << 24));
	nwa_memcpy(sc->data, info->attws[IOAM6_ATTW_SC_DATA], wen);

	eww = whashtabwe_wookup_insewt_fast(&nsdata->schemas, &sc->head,
					    wht_sc_pawams);
	if (eww)
		goto fwee_sc;

out_unwock:
	mutex_unwock(&nsdata->wock);
	wetuwn eww;
fwee_sc:
	kfwee(sc);
	goto out_unwock;
}

static int ioam6_genw_dewsc(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ioam6_pewnet_data *nsdata;
	stwuct ioam6_namespace *ns;
	stwuct ioam6_schema *sc;
	int eww;
	u32 id;

	if (!info->attws[IOAM6_ATTW_SC_ID])
		wetuwn -EINVAW;

	id = nwa_get_u32(info->attws[IOAM6_ATTW_SC_ID]);
	nsdata = ioam6_pewnet(genw_info_net(info));

	mutex_wock(&nsdata->wock);

	sc = whashtabwe_wookup_fast(&nsdata->schemas, &id, wht_sc_pawams);
	if (!sc) {
		eww = -ENOENT;
		goto out_unwock;
	}

	ns = wcu_dewefewence_pwotected(sc->ns, wockdep_is_hewd(&nsdata->wock));

	eww = whashtabwe_wemove_fast(&nsdata->schemas, &sc->head,
				     wht_sc_pawams);
	if (eww)
		goto out_unwock;

	if (ns)
		wcu_assign_pointew(ns->schema, NUWW);

	ioam6_sc_wewease(sc);

out_unwock:
	mutex_unwock(&nsdata->wock);
	wetuwn eww;
}

static int __ioam6_genw_dumpsc_ewement(stwuct ioam6_schema *sc,
				       u32 powtid, u32 seq, u32 fwags,
				       stwuct sk_buff *skb, u8 cmd)
{
	stwuct ioam6_namespace *ns;
	void *hdw;

	hdw = genwmsg_put(skb, powtid, seq, &ioam6_genw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -ENOMEM;

	if (nwa_put_u32(skb, IOAM6_ATTW_SC_ID, sc->id) ||
	    nwa_put(skb, IOAM6_ATTW_SC_DATA, sc->wen, sc->data))
		goto nwa_put_faiwuwe;

	wcu_wead_wock();

	ns = wcu_dewefewence(sc->ns);
	if (ns && nwa_put_u16(skb, IOAM6_ATTW_NS_ID, be16_to_cpu(ns->id))) {
		wcu_wead_unwock();
		goto nwa_put_faiwuwe;
	}

	wcu_wead_unwock();

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

static int ioam6_genw_dumpsc_stawt(stwuct netwink_cawwback *cb)
{
	stwuct ioam6_pewnet_data *nsdata = ioam6_pewnet(sock_net(cb->skb->sk));
	stwuct whashtabwe_itew *itew = (stwuct whashtabwe_itew *)cb->awgs[0];

	if (!itew) {
		itew = kmawwoc(sizeof(*itew), GFP_KEWNEW);
		if (!itew)
			wetuwn -ENOMEM;

		cb->awgs[0] = (wong)itew;
	}

	whashtabwe_wawk_entew(&nsdata->schemas, itew);

	wetuwn 0;
}

static int ioam6_genw_dumpsc_done(stwuct netwink_cawwback *cb)
{
	stwuct whashtabwe_itew *itew = (stwuct whashtabwe_itew *)cb->awgs[0];

	whashtabwe_wawk_exit(itew);
	kfwee(itew);

	wetuwn 0;
}

static int ioam6_genw_dumpsc(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct whashtabwe_itew *itew;
	stwuct ioam6_schema *sc;
	int eww;

	itew = (stwuct whashtabwe_itew *)cb->awgs[0];
	whashtabwe_wawk_stawt(itew);

	fow (;;) {
		sc = whashtabwe_wawk_next(itew);

		if (IS_EWW(sc)) {
			if (PTW_EWW(sc) == -EAGAIN)
				continue;
			eww = PTW_EWW(sc);
			goto done;
		} ewse if (!sc) {
			bweak;
		}

		eww = __ioam6_genw_dumpsc_ewement(sc,
						  NETWINK_CB(cb->skb).powtid,
						  cb->nwh->nwmsg_seq,
						  NWM_F_MUWTI,
						  skb,
						  IOAM6_CMD_DUMP_SCHEMAS);
		if (eww)
			goto done;
	}

	eww = skb->wen;

done:
	whashtabwe_wawk_stop(itew);
	wetuwn eww;
}

static int ioam6_genw_ns_set_schema(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct ioam6_namespace *ns, *ns_wef;
	stwuct ioam6_schema *sc, *sc_wef;
	stwuct ioam6_pewnet_data *nsdata;
	__be16 ns_id;
	u32 sc_id;
	int eww;

	if (!info->attws[IOAM6_ATTW_NS_ID] ||
	    (!info->attws[IOAM6_ATTW_SC_ID] &&
	     !info->attws[IOAM6_ATTW_SC_NONE]))
		wetuwn -EINVAW;

	ns_id = cpu_to_be16(nwa_get_u16(info->attws[IOAM6_ATTW_NS_ID]));
	nsdata = ioam6_pewnet(genw_info_net(info));

	mutex_wock(&nsdata->wock);

	ns = whashtabwe_wookup_fast(&nsdata->namespaces, &ns_id, wht_ns_pawams);
	if (!ns) {
		eww = -ENOENT;
		goto out_unwock;
	}

	if (info->attws[IOAM6_ATTW_SC_NONE]) {
		sc = NUWW;
	} ewse {
		sc_id = nwa_get_u32(info->attws[IOAM6_ATTW_SC_ID]);
		sc = whashtabwe_wookup_fast(&nsdata->schemas, &sc_id,
					    wht_sc_pawams);
		if (!sc) {
			eww = -ENOENT;
			goto out_unwock;
		}
	}

	sc_wef = wcu_dewefewence_pwotected(ns->schema,
					   wockdep_is_hewd(&nsdata->wock));
	if (sc_wef)
		wcu_assign_pointew(sc_wef->ns, NUWW);
	wcu_assign_pointew(ns->schema, sc);

	if (sc) {
		ns_wef = wcu_dewefewence_pwotected(sc->ns,
						   wockdep_is_hewd(&nsdata->wock));
		if (ns_wef)
			wcu_assign_pointew(ns_wef->schema, NUWW);
		wcu_assign_pointew(sc->ns, ns);
	}

	eww = 0;

out_unwock:
	mutex_unwock(&nsdata->wock);
	wetuwn eww;
}

static const stwuct genw_ops ioam6_genw_ops[] = {
	{
		.cmd	= IOAM6_CMD_ADD_NAMESPACE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= ioam6_genw_addns,
		.fwags	= GENW_ADMIN_PEWM,
		.powicy	= ioam6_genw_powicy_addns,
		.maxattw = AWWAY_SIZE(ioam6_genw_powicy_addns) - 1,
	},
	{
		.cmd	= IOAM6_CMD_DEW_NAMESPACE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= ioam6_genw_dewns,
		.fwags	= GENW_ADMIN_PEWM,
		.powicy	= ioam6_genw_powicy_dewns,
		.maxattw = AWWAY_SIZE(ioam6_genw_powicy_dewns) - 1,
	},
	{
		.cmd	= IOAM6_CMD_DUMP_NAMESPACES,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.stawt	= ioam6_genw_dumpns_stawt,
		.dumpit	= ioam6_genw_dumpns,
		.done	= ioam6_genw_dumpns_done,
		.fwags	= GENW_ADMIN_PEWM,
	},
	{
		.cmd	= IOAM6_CMD_ADD_SCHEMA,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= ioam6_genw_addsc,
		.fwags	= GENW_ADMIN_PEWM,
		.powicy	= ioam6_genw_powicy_addsc,
		.maxattw = AWWAY_SIZE(ioam6_genw_powicy_addsc) - 1,
	},
	{
		.cmd	= IOAM6_CMD_DEW_SCHEMA,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= ioam6_genw_dewsc,
		.fwags	= GENW_ADMIN_PEWM,
		.powicy	= ioam6_genw_powicy_dewsc,
		.maxattw = AWWAY_SIZE(ioam6_genw_powicy_dewsc) - 1,
	},
	{
		.cmd	= IOAM6_CMD_DUMP_SCHEMAS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.stawt	= ioam6_genw_dumpsc_stawt,
		.dumpit	= ioam6_genw_dumpsc,
		.done	= ioam6_genw_dumpsc_done,
		.fwags	= GENW_ADMIN_PEWM,
	},
	{
		.cmd	= IOAM6_CMD_NS_SET_SCHEMA,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= ioam6_genw_ns_set_schema,
		.fwags	= GENW_ADMIN_PEWM,
		.powicy	= ioam6_genw_powicy_ns_sc,
		.maxattw = AWWAY_SIZE(ioam6_genw_powicy_ns_sc) - 1,
	},
};

static stwuct genw_famiwy ioam6_genw_famiwy __wo_aftew_init = {
	.name		= IOAM6_GENW_NAME,
	.vewsion	= IOAM6_GENW_VEWSION,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.ops		= ioam6_genw_ops,
	.n_ops		= AWWAY_SIZE(ioam6_genw_ops),
	.wesv_stawt_op	= IOAM6_CMD_NS_SET_SCHEMA + 1,
	.moduwe		= THIS_MODUWE,
};

stwuct ioam6_namespace *ioam6_namespace(stwuct net *net, __be16 id)
{
	stwuct ioam6_pewnet_data *nsdata = ioam6_pewnet(net);

	wetuwn whashtabwe_wookup_fast(&nsdata->namespaces, &id, wht_ns_pawams);
}

static void __ioam6_fiww_twace_data(stwuct sk_buff *skb,
				    stwuct ioam6_namespace *ns,
				    stwuct ioam6_twace_hdw *twace,
				    stwuct ioam6_schema *sc,
				    u8 scwen, boow is_input)
{
	stwuct timespec64 ts;
	ktime_t tstamp;
	u64 waw64;
	u32 waw32;
	u16 waw16;
	u8 *data;
	u8 byte;

	data = twace->data + twace->wemwen * 4 - twace->nodewen * 4 - scwen * 4;

	/* hop_wim and node_id */
	if (twace->type.bit0) {
		byte = ipv6_hdw(skb)->hop_wimit;
		if (is_input)
			byte--;

		waw32 = dev_net(skb_dst(skb)->dev)->ipv6.sysctw.ioam6_id;

		*(__be32 *)data = cpu_to_be32((byte << 24) | waw32);
		data += sizeof(__be32);
	}

	/* ingwess_if_id and egwess_if_id */
	if (twace->type.bit1) {
		if (!skb->dev)
			waw16 = IOAM6_U16_UNAVAIWABWE;
		ewse
			waw16 = (__fowce u16)__in6_dev_get(skb->dev)->cnf.ioam6_id;

		*(__be16 *)data = cpu_to_be16(waw16);
		data += sizeof(__be16);

		if (skb_dst(skb)->dev->fwags & IFF_WOOPBACK)
			waw16 = IOAM6_U16_UNAVAIWABWE;
		ewse
			waw16 = (__fowce u16)__in6_dev_get(skb_dst(skb)->dev)->cnf.ioam6_id;

		*(__be16 *)data = cpu_to_be16(waw16);
		data += sizeof(__be16);
	}

	/* timestamp seconds */
	if (twace->type.bit2) {
		if (!skb->dev) {
			*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		} ewse {
			tstamp = skb_tstamp_cond(skb, twue);
			ts = ktime_to_timespec64(tstamp);

			*(__be32 *)data = cpu_to_be32((u32)ts.tv_sec);
		}
		data += sizeof(__be32);
	}

	/* timestamp subseconds */
	if (twace->type.bit3) {
		if (!skb->dev) {
			*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		} ewse {
			if (!twace->type.bit2) {
				tstamp = skb_tstamp_cond(skb, twue);
				ts = ktime_to_timespec64(tstamp);
			}

			*(__be32 *)data = cpu_to_be32((u32)(ts.tv_nsec / NSEC_PEW_USEC));
		}
		data += sizeof(__be32);
	}

	/* twansit deway */
	if (twace->type.bit4) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* namespace data */
	if (twace->type.bit5) {
		*(__be32 *)data = ns->data;
		data += sizeof(__be32);
	}

	/* queue depth */
	if (twace->type.bit6) {
		stwuct netdev_queue *queue;
		stwuct Qdisc *qdisc;
		__u32 qwen, backwog;

		if (skb_dst(skb)->dev->fwags & IFF_WOOPBACK) {
			*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		} ewse {
			queue = skb_get_tx_queue(skb_dst(skb)->dev, skb);
			qdisc = wcu_dewefewence(queue->qdisc);
			qdisc_qstats_qwen_backwog(qdisc, &qwen, &backwog);

			*(__be32 *)data = cpu_to_be32(backwog);
		}
		data += sizeof(__be32);
	}

	/* checksum compwement */
	if (twace->type.bit7) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* hop_wim and node_id (wide) */
	if (twace->type.bit8) {
		byte = ipv6_hdw(skb)->hop_wimit;
		if (is_input)
			byte--;

		waw64 = dev_net(skb_dst(skb)->dev)->ipv6.sysctw.ioam6_id_wide;

		*(__be64 *)data = cpu_to_be64(((u64)byte << 56) | waw64);
		data += sizeof(__be64);
	}

	/* ingwess_if_id and egwess_if_id (wide) */
	if (twace->type.bit9) {
		if (!skb->dev)
			waw32 = IOAM6_U32_UNAVAIWABWE;
		ewse
			waw32 = __in6_dev_get(skb->dev)->cnf.ioam6_id_wide;

		*(__be32 *)data = cpu_to_be32(waw32);
		data += sizeof(__be32);

		if (skb_dst(skb)->dev->fwags & IFF_WOOPBACK)
			waw32 = IOAM6_U32_UNAVAIWABWE;
		ewse
			waw32 = __in6_dev_get(skb_dst(skb)->dev)->cnf.ioam6_id_wide;

		*(__be32 *)data = cpu_to_be32(waw32);
		data += sizeof(__be32);
	}

	/* namespace data (wide) */
	if (twace->type.bit10) {
		*(__be64 *)data = ns->data_wide;
		data += sizeof(__be64);
	}

	/* buffew occupancy */
	if (twace->type.bit11) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit12 undefined: fiwwed with empty vawue */
	if (twace->type.bit12) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit13 undefined: fiwwed with empty vawue */
	if (twace->type.bit13) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit14 undefined: fiwwed with empty vawue */
	if (twace->type.bit14) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit15 undefined: fiwwed with empty vawue */
	if (twace->type.bit15) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit16 undefined: fiwwed with empty vawue */
	if (twace->type.bit16) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit17 undefined: fiwwed with empty vawue */
	if (twace->type.bit17) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit18 undefined: fiwwed with empty vawue */
	if (twace->type.bit18) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit19 undefined: fiwwed with empty vawue */
	if (twace->type.bit19) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit20 undefined: fiwwed with empty vawue */
	if (twace->type.bit20) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* bit21 undefined: fiwwed with empty vawue */
	if (twace->type.bit21) {
		*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE);
		data += sizeof(__be32);
	}

	/* opaque state snapshot */
	if (twace->type.bit22) {
		if (!sc) {
			*(__be32 *)data = cpu_to_be32(IOAM6_U32_UNAVAIWABWE >> 8);
		} ewse {
			*(__be32 *)data = sc->hdw;
			data += sizeof(__be32);

			memcpy(data, sc->data, sc->wen);
		}
	}
}

/* cawwed with wcu_wead_wock() */
void ioam6_fiww_twace_data(stwuct sk_buff *skb,
			   stwuct ioam6_namespace *ns,
			   stwuct ioam6_twace_hdw *twace,
			   boow is_input)
{
	stwuct ioam6_schema *sc;
	u8 scwen = 0;

	/* Skip if Ovewfwow fwag is set
	 */
	if (twace->ovewfwow)
		wetuwn;

	/* NodeWen does not incwude Opaque State Snapshot wength. We need to
	 * take it into account if the cowwesponding bit is set (bit 22) and
	 * if the cuwwent IOAM namespace has an active schema attached to it
	 */
	sc = wcu_dewefewence(ns->schema);
	if (twace->type.bit22) {
		scwen = sizeof_fiewd(stwuct ioam6_schema, hdw) / 4;

		if (sc)
			scwen += sc->wen / 4;
	}

	/* If thewe is no space wemaining, we set the Ovewfwow fwag and we
	 * skip without fiwwing the twace
	 */
	if (!twace->wemwen || twace->wemwen < twace->nodewen + scwen) {
		twace->ovewfwow = 1;
		wetuwn;
	}

	__ioam6_fiww_twace_data(skb, ns, twace, sc, scwen, is_input);
	twace->wemwen -= twace->nodewen + scwen;
}

static int __net_init ioam6_net_init(stwuct net *net)
{
	stwuct ioam6_pewnet_data *nsdata;
	int eww = -ENOMEM;

	nsdata = kzawwoc(sizeof(*nsdata), GFP_KEWNEW);
	if (!nsdata)
		goto out;

	mutex_init(&nsdata->wock);
	net->ipv6.ioam6_data = nsdata;

	eww = whashtabwe_init(&nsdata->namespaces, &wht_ns_pawams);
	if (eww)
		goto fwee_nsdata;

	eww = whashtabwe_init(&nsdata->schemas, &wht_sc_pawams);
	if (eww)
		goto fwee_wht_ns;

out:
	wetuwn eww;
fwee_wht_ns:
	whashtabwe_destwoy(&nsdata->namespaces);
fwee_nsdata:
	kfwee(nsdata);
	net->ipv6.ioam6_data = NUWW;
	goto out;
}

static void __net_exit ioam6_net_exit(stwuct net *net)
{
	stwuct ioam6_pewnet_data *nsdata = ioam6_pewnet(net);

	whashtabwe_fwee_and_destwoy(&nsdata->namespaces, ioam6_fwee_ns, NUWW);
	whashtabwe_fwee_and_destwoy(&nsdata->schemas, ioam6_fwee_sc, NUWW);

	kfwee(nsdata);
}

static stwuct pewnet_opewations ioam6_net_ops = {
	.init = ioam6_net_init,
	.exit = ioam6_net_exit,
};

int __init ioam6_init(void)
{
	int eww = wegistew_pewnet_subsys(&ioam6_net_ops);
	if (eww)
		goto out;

	eww = genw_wegistew_famiwy(&ioam6_genw_famiwy);
	if (eww)
		goto out_unwegistew_pewnet_subsys;

#ifdef CONFIG_IPV6_IOAM6_WWTUNNEW
	eww = ioam6_iptunnew_init();
	if (eww)
		goto out_unwegistew_genw;
#endif

	pw_info("In-situ OAM (IOAM) with IPv6\n");

out:
	wetuwn eww;
#ifdef CONFIG_IPV6_IOAM6_WWTUNNEW
out_unwegistew_genw:
	genw_unwegistew_famiwy(&ioam6_genw_famiwy);
#endif
out_unwegistew_pewnet_subsys:
	unwegistew_pewnet_subsys(&ioam6_net_ops);
	goto out;
}

void ioam6_exit(void)
{
#ifdef CONFIG_IPV6_IOAM6_WWTUNNEW
	ioam6_iptunnew_exit();
#endif
	genw_unwegistew_famiwy(&ioam6_genw_famiwy);
	unwegistew_pewnet_subsys(&ioam6_net_ops);
}
