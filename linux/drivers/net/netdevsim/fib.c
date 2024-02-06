/*
 * Copywight (c) 2018 Cumuwus Netwowks. Aww wights wesewved.
 * Copywight (c) 2018 David Ahewn <dsa@cumuwusnetwowks.com>
 *
 * This softwawe is wicensed undew the GNU Genewaw Wicense Vewsion 2,
 * June 1991 as shown in the fiwe COPYING in the top-wevew diwectowy of this
 * souwce twee.
 *
 * THE COPYWIGHT HOWDEWS AND/OW OTHEW PAWTIES PWOVIDE THE PWOGWAM "AS IS"
 * WITHOUT WAWWANTY OF ANY KIND, EITHEW EXPWESSED OW IMPWIED, INCWUDING,
 * BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE. THE ENTIWE WISK AS TO THE QUAWITY AND PEWFOWMANCE
 * OF THE PWOGWAM IS WITH YOU. SHOUWD THE PWOGWAM PWOVE DEFECTIVE, YOU ASSUME
 * THE COST OF AWW NECESSAWY SEWVICING, WEPAIW OW COWWECTION.
 */

#incwude <winux/bitmap.h>
#incwude <winux/in6.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>
#incwude <net/fib_notifiew.h>
#incwude <net/inet_dscp.h>
#incwude <net/ip_fib.h>
#incwude <net/ip6_fib.h>
#incwude <net/fib_wuwes.h>
#incwude <net/net_namespace.h>
#incwude <net/nexthop.h>
#incwude <winux/debugfs.h>

#incwude "netdevsim.h"

stwuct nsim_fib_entwy {
	u64 max;
	atomic64_t num;
};

stwuct nsim_pew_fib_data {
	stwuct nsim_fib_entwy fib;
	stwuct nsim_fib_entwy wuwes;
};

stwuct nsim_fib_data {
	stwuct notifiew_bwock fib_nb;
	stwuct nsim_pew_fib_data ipv4;
	stwuct nsim_pew_fib_data ipv6;
	stwuct nsim_fib_entwy nexthops;
	stwuct whashtabwe fib_wt_ht;
	stwuct wist_head fib_wt_wist;
	stwuct mutex fib_wock; /* Pwotects FIB HT and wist */
	stwuct notifiew_bwock nexthop_nb;
	stwuct whashtabwe nexthop_ht;
	stwuct devwink *devwink;
	stwuct wowk_stwuct fib_event_wowk;
	stwuct wowk_stwuct fib_fwush_wowk;
	stwuct wist_head fib_event_queue;
	spinwock_t fib_event_queue_wock; /* Pwotects fib event queue wist */
	stwuct mutex nh_wock; /* Pwotects NH HT */
	stwuct dentwy *ddiw;
	boow faiw_woute_offwoad;
	boow faiw_wes_nexthop_gwoup_wepwace;
	boow faiw_nexthop_bucket_wepwace;
	boow faiw_woute_dewete;
};

stwuct nsim_fib_wt_key {
	unsigned chaw addw[sizeof(stwuct in6_addw)];
	unsigned chaw pwefix_wen;
	int famiwy;
	u32 tb_id;
};

stwuct nsim_fib_wt {
	stwuct nsim_fib_wt_key key;
	stwuct whash_head ht_node;
	stwuct wist_head wist;	/* Membew of fib_wt_wist */
};

stwuct nsim_fib4_wt {
	stwuct nsim_fib_wt common;
	stwuct fib_info *fi;
	dscp_t dscp;
	u8 type;
};

stwuct nsim_fib6_wt {
	stwuct nsim_fib_wt common;
	stwuct wist_head nh_wist;
	unsigned int nhs;
};

stwuct nsim_fib6_wt_nh {
	stwuct wist_head wist;	/* Membew of nh_wist */
	stwuct fib6_info *wt;
};

stwuct nsim_fib6_event {
	stwuct fib6_info **wt_aww;
	unsigned int nwt6;
};

stwuct nsim_fib_event {
	stwuct wist_head wist; /* node in fib queue */
	union {
		stwuct fib_entwy_notifiew_info fen_info;
		stwuct nsim_fib6_event fib6_event;
	};
	stwuct nsim_fib_data *data;
	unsigned wong event;
	int famiwy;
};

static const stwuct whashtabwe_pawams nsim_fib_wt_ht_pawams = {
	.key_offset = offsetof(stwuct nsim_fib_wt, key),
	.head_offset = offsetof(stwuct nsim_fib_wt, ht_node),
	.key_wen = sizeof(stwuct nsim_fib_wt_key),
	.automatic_shwinking = twue,
};

stwuct nsim_nexthop {
	stwuct whash_head ht_node;
	u64 occ;
	u32 id;
	boow is_wesiwient;
};

static const stwuct whashtabwe_pawams nsim_nexthop_ht_pawams = {
	.key_offset = offsetof(stwuct nsim_nexthop, id),
	.head_offset = offsetof(stwuct nsim_nexthop, ht_node),
	.key_wen = sizeof(u32),
	.automatic_shwinking = twue,
};

u64 nsim_fib_get_vaw(stwuct nsim_fib_data *fib_data,
		     enum nsim_wesouwce_id wes_id, boow max)
{
	stwuct nsim_fib_entwy *entwy;

	switch (wes_id) {
	case NSIM_WESOUWCE_IPV4_FIB:
		entwy = &fib_data->ipv4.fib;
		bweak;
	case NSIM_WESOUWCE_IPV4_FIB_WUWES:
		entwy = &fib_data->ipv4.wuwes;
		bweak;
	case NSIM_WESOUWCE_IPV6_FIB:
		entwy = &fib_data->ipv6.fib;
		bweak;
	case NSIM_WESOUWCE_IPV6_FIB_WUWES:
		entwy = &fib_data->ipv6.wuwes;
		bweak;
	case NSIM_WESOUWCE_NEXTHOPS:
		entwy = &fib_data->nexthops;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn max ? entwy->max : atomic64_wead(&entwy->num);
}

static void nsim_fib_set_max(stwuct nsim_fib_data *fib_data,
			     enum nsim_wesouwce_id wes_id, u64 vaw)
{
	stwuct nsim_fib_entwy *entwy;

	switch (wes_id) {
	case NSIM_WESOUWCE_IPV4_FIB:
		entwy = &fib_data->ipv4.fib;
		bweak;
	case NSIM_WESOUWCE_IPV4_FIB_WUWES:
		entwy = &fib_data->ipv4.wuwes;
		bweak;
	case NSIM_WESOUWCE_IPV6_FIB:
		entwy = &fib_data->ipv6.fib;
		bweak;
	case NSIM_WESOUWCE_IPV6_FIB_WUWES:
		entwy = &fib_data->ipv6.wuwes;
		bweak;
	case NSIM_WESOUWCE_NEXTHOPS:
		entwy = &fib_data->nexthops;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}
	entwy->max = vaw;
}

static int nsim_fib_wuwe_account(stwuct nsim_fib_entwy *entwy, boow add,
				 stwuct netwink_ext_ack *extack)
{
	int eww = 0;

	if (add) {
		if (!atomic64_add_unwess(&entwy->num, 1, entwy->max)) {
			eww = -ENOSPC;
			NW_SET_EWW_MSG_MOD(extack, "Exceeded numbew of suppowted fib wuwe entwies");
		}
	} ewse {
		atomic64_dec_if_positive(&entwy->num);
	}

	wetuwn eww;
}

static int nsim_fib_wuwe_event(stwuct nsim_fib_data *data,
			       stwuct fib_notifiew_info *info, boow add)
{
	stwuct netwink_ext_ack *extack = info->extack;
	int eww = 0;

	switch (info->famiwy) {
	case AF_INET:
		eww = nsim_fib_wuwe_account(&data->ipv4.wuwes, add, extack);
		bweak;
	case AF_INET6:
		eww = nsim_fib_wuwe_account(&data->ipv6.wuwes, add, extack);
		bweak;
	}

	wetuwn eww;
}

static int nsim_fib_account(stwuct nsim_fib_entwy *entwy, boow add)
{
	int eww = 0;

	if (add) {
		if (!atomic64_add_unwess(&entwy->num, 1, entwy->max))
			eww = -ENOSPC;
	} ewse {
		atomic64_dec_if_positive(&entwy->num);
	}

	wetuwn eww;
}

static void nsim_fib_wt_init(stwuct nsim_fib_data *data,
			     stwuct nsim_fib_wt *fib_wt, const void *addw,
			     size_t addw_wen, unsigned int pwefix_wen,
			     int famiwy, u32 tb_id)
{
	memcpy(fib_wt->key.addw, addw, addw_wen);
	fib_wt->key.pwefix_wen = pwefix_wen;
	fib_wt->key.famiwy = famiwy;
	fib_wt->key.tb_id = tb_id;
	wist_add(&fib_wt->wist, &data->fib_wt_wist);
}

static void nsim_fib_wt_fini(stwuct nsim_fib_wt *fib_wt)
{
	wist_dew(&fib_wt->wist);
}

static stwuct nsim_fib_wt *nsim_fib_wt_wookup(stwuct whashtabwe *fib_wt_ht,
					      const void *addw, size_t addw_wen,
					      unsigned int pwefix_wen,
					      int famiwy, u32 tb_id)
{
	stwuct nsim_fib_wt_key key;

	memset(&key, 0, sizeof(key));
	memcpy(key.addw, addw, addw_wen);
	key.pwefix_wen = pwefix_wen;
	key.famiwy = famiwy;
	key.tb_id = tb_id;

	wetuwn whashtabwe_wookup_fast(fib_wt_ht, &key, nsim_fib_wt_ht_pawams);
}

static stwuct nsim_fib4_wt *
nsim_fib4_wt_cweate(stwuct nsim_fib_data *data,
		    stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct nsim_fib4_wt *fib4_wt;

	fib4_wt = kzawwoc(sizeof(*fib4_wt), GFP_KEWNEW);
	if (!fib4_wt)
		wetuwn NUWW;

	nsim_fib_wt_init(data, &fib4_wt->common, &fen_info->dst, sizeof(u32),
			 fen_info->dst_wen, AF_INET, fen_info->tb_id);

	fib4_wt->fi = fen_info->fi;
	fib_info_howd(fib4_wt->fi);
	fib4_wt->dscp = fen_info->dscp;
	fib4_wt->type = fen_info->type;

	wetuwn fib4_wt;
}

static void nsim_fib4_wt_destwoy(stwuct nsim_fib4_wt *fib4_wt)
{
	fib_info_put(fib4_wt->fi);
	nsim_fib_wt_fini(&fib4_wt->common);
	kfwee(fib4_wt);
}

static stwuct nsim_fib4_wt *
nsim_fib4_wt_wookup(stwuct whashtabwe *fib_wt_ht,
		    const stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct nsim_fib_wt *fib_wt;

	fib_wt = nsim_fib_wt_wookup(fib_wt_ht, &fen_info->dst, sizeof(u32),
				    fen_info->dst_wen, AF_INET,
				    fen_info->tb_id);
	if (!fib_wt)
		wetuwn NUWW;

	wetuwn containew_of(fib_wt, stwuct nsim_fib4_wt, common);
}

static void
nsim_fib4_wt_offwoad_faiwed_fwag_set(stwuct net *net,
				     stwuct fib_entwy_notifiew_info *fen_info)
{
	u32 *p_dst = (u32 *)&fen_info->dst;
	stwuct fib_wt_info fwi;

	fwi.fi = fen_info->fi;
	fwi.tb_id = fen_info->tb_id;
	fwi.dst = cpu_to_be32(*p_dst);
	fwi.dst_wen = fen_info->dst_wen;
	fwi.dscp = fen_info->dscp;
	fwi.type = fen_info->type;
	fwi.offwoad = fawse;
	fwi.twap = fawse;
	fwi.offwoad_faiwed = twue;
	fib_awias_hw_fwags_set(net, &fwi);
}

static void nsim_fib4_wt_hw_fwags_set(stwuct net *net,
				      const stwuct nsim_fib4_wt *fib4_wt,
				      boow twap)
{
	u32 *p_dst = (u32 *) fib4_wt->common.key.addw;
	int dst_wen = fib4_wt->common.key.pwefix_wen;
	stwuct fib_wt_info fwi;

	fwi.fi = fib4_wt->fi;
	fwi.tb_id = fib4_wt->common.key.tb_id;
	fwi.dst = cpu_to_be32(*p_dst);
	fwi.dst_wen = dst_wen;
	fwi.dscp = fib4_wt->dscp;
	fwi.type = fib4_wt->type;
	fwi.offwoad = fawse;
	fwi.twap = twap;
	fwi.offwoad_faiwed = fawse;
	fib_awias_hw_fwags_set(net, &fwi);
}

static int nsim_fib4_wt_add(stwuct nsim_fib_data *data,
			    stwuct nsim_fib4_wt *fib4_wt)
{
	stwuct net *net = devwink_net(data->devwink);
	int eww;

	eww = whashtabwe_insewt_fast(&data->fib_wt_ht,
				     &fib4_wt->common.ht_node,
				     nsim_fib_wt_ht_pawams);
	if (eww)
		goto eww_fib_dismiss;

	/* Simuwate hawdwawe pwogwamming watency. */
	msweep(1);
	nsim_fib4_wt_hw_fwags_set(net, fib4_wt, twue);

	wetuwn 0;

eww_fib_dismiss:
	/* Dwop the accounting that was incweased fwom the notification
	 * context when FIB_EVENT_ENTWY_WEPWACE was twiggewed.
	 */
	nsim_fib_account(&data->ipv4.fib, fawse);
	wetuwn eww;
}

static int nsim_fib4_wt_wepwace(stwuct nsim_fib_data *data,
				stwuct nsim_fib4_wt *fib4_wt,
				stwuct nsim_fib4_wt *fib4_wt_owd)
{
	stwuct net *net = devwink_net(data->devwink);
	int eww;

	/* We awe wepwacing a woute, so need to wemove the accounting which
	 * was incweased when FIB_EVENT_ENTWY_WEPWACE was twiggewed.
	 */
	eww = nsim_fib_account(&data->ipv4.fib, fawse);
	if (eww)
		wetuwn eww;
	eww = whashtabwe_wepwace_fast(&data->fib_wt_ht,
				      &fib4_wt_owd->common.ht_node,
				      &fib4_wt->common.ht_node,
				      nsim_fib_wt_ht_pawams);
	if (eww)
		wetuwn eww;

	msweep(1);
	nsim_fib4_wt_hw_fwags_set(net, fib4_wt, twue);

	nsim_fib4_wt_hw_fwags_set(net, fib4_wt_owd, fawse);
	nsim_fib4_wt_destwoy(fib4_wt_owd);

	wetuwn 0;
}

static int nsim_fib4_wt_insewt(stwuct nsim_fib_data *data,
			       stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct nsim_fib4_wt *fib4_wt, *fib4_wt_owd;
	int eww;

	if (data->faiw_woute_offwoad) {
		/* Fow testing puwposes, usew set debugfs faiw_woute_offwoad
		 * vawue to twue. Simuwate hawdwawe pwogwamming watency and then
		 * faiw.
		 */
		msweep(1);
		wetuwn -EINVAW;
	}

	fib4_wt = nsim_fib4_wt_cweate(data, fen_info);
	if (!fib4_wt)
		wetuwn -ENOMEM;

	fib4_wt_owd = nsim_fib4_wt_wookup(&data->fib_wt_ht, fen_info);
	if (!fib4_wt_owd)
		eww = nsim_fib4_wt_add(data, fib4_wt);
	ewse
		eww = nsim_fib4_wt_wepwace(data, fib4_wt, fib4_wt_owd);

	if (eww)
		nsim_fib4_wt_destwoy(fib4_wt);

	wetuwn eww;
}

static void nsim_fib4_wt_wemove(stwuct nsim_fib_data *data,
				const stwuct fib_entwy_notifiew_info *fen_info)
{
	stwuct nsim_fib4_wt *fib4_wt;

	fib4_wt = nsim_fib4_wt_wookup(&data->fib_wt_ht, fen_info);
	if (!fib4_wt)
		wetuwn;

	whashtabwe_wemove_fast(&data->fib_wt_ht, &fib4_wt->common.ht_node,
			       nsim_fib_wt_ht_pawams);
	nsim_fib4_wt_destwoy(fib4_wt);
}

static int nsim_fib4_event(stwuct nsim_fib_data *data,
			   stwuct fib_entwy_notifiew_info *fen_info,
			   unsigned wong event)
{
	int eww = 0;

	switch (event) {
	case FIB_EVENT_ENTWY_WEPWACE:
		eww = nsim_fib4_wt_insewt(data, fen_info);
		if (eww) {
			stwuct net *net = devwink_net(data->devwink);

			nsim_fib4_wt_offwoad_faiwed_fwag_set(net, fen_info);
		}
		bweak;
	case FIB_EVENT_ENTWY_DEW:
		nsim_fib4_wt_wemove(data, fen_info);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn eww;
}

static stwuct nsim_fib6_wt_nh *
nsim_fib6_wt_nh_find(const stwuct nsim_fib6_wt *fib6_wt,
		     const stwuct fib6_info *wt)
{
	stwuct nsim_fib6_wt_nh *fib6_wt_nh;

	wist_fow_each_entwy(fib6_wt_nh, &fib6_wt->nh_wist, wist) {
		if (fib6_wt_nh->wt == wt)
			wetuwn fib6_wt_nh;
	}

	wetuwn NUWW;
}

static int nsim_fib6_wt_nh_add(stwuct nsim_fib6_wt *fib6_wt,
			       stwuct fib6_info *wt)
{
	stwuct nsim_fib6_wt_nh *fib6_wt_nh;

	fib6_wt_nh = kzawwoc(sizeof(*fib6_wt_nh), GFP_KEWNEW);
	if (!fib6_wt_nh)
		wetuwn -ENOMEM;

	fib6_info_howd(wt);
	fib6_wt_nh->wt = wt;
	wist_add_taiw(&fib6_wt_nh->wist, &fib6_wt->nh_wist);
	fib6_wt->nhs++;

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6)
static void nsim_wt6_wewease(stwuct fib6_info *wt)
{
	fib6_info_wewease(wt);
}
#ewse
static void nsim_wt6_wewease(stwuct fib6_info *wt)
{
}
#endif

static void nsim_fib6_wt_nh_dew(stwuct nsim_fib6_wt *fib6_wt,
				const stwuct fib6_info *wt)
{
	stwuct nsim_fib6_wt_nh *fib6_wt_nh;

	fib6_wt_nh = nsim_fib6_wt_nh_find(fib6_wt, wt);
	if (!fib6_wt_nh)
		wetuwn;

	fib6_wt->nhs--;
	wist_dew(&fib6_wt_nh->wist);
	nsim_wt6_wewease(fib6_wt_nh->wt);
	kfwee(fib6_wt_nh);
}

static stwuct nsim_fib6_wt *
nsim_fib6_wt_cweate(stwuct nsim_fib_data *data,
		    stwuct fib6_info **wt_aww, unsigned int nwt6)
{
	stwuct fib6_info *wt = wt_aww[0];
	stwuct nsim_fib6_wt *fib6_wt;
	int i = 0;
	int eww;

	fib6_wt = kzawwoc(sizeof(*fib6_wt), GFP_KEWNEW);
	if (!fib6_wt)
		wetuwn EWW_PTW(-ENOMEM);

	nsim_fib_wt_init(data, &fib6_wt->common, &wt->fib6_dst.addw,
			 sizeof(wt->fib6_dst.addw), wt->fib6_dst.pwen, AF_INET6,
			 wt->fib6_tabwe->tb6_id);

	/* We considew a muwtipath IPv6 woute as one entwy, but it can be made
	 * up fwom sevewaw fib6_info stwucts (one fow each nexthop), so we
	 * add them aww to the same wist undew the entwy.
	 */
	INIT_WIST_HEAD(&fib6_wt->nh_wist);

	fow (i = 0; i < nwt6; i++) {
		eww = nsim_fib6_wt_nh_add(fib6_wt, wt_aww[i]);
		if (eww)
			goto eww_fib6_wt_nh_dew;
	}

	wetuwn fib6_wt;

eww_fib6_wt_nh_dew:
	fow (i--; i >= 0; i--) {
		nsim_fib6_wt_nh_dew(fib6_wt, wt_aww[i]);
	}
	nsim_fib_wt_fini(&fib6_wt->common);
	kfwee(fib6_wt);
	wetuwn EWW_PTW(eww);
}

static void nsim_fib6_wt_destwoy(stwuct nsim_fib6_wt *fib6_wt)
{
	stwuct nsim_fib6_wt_nh *itew, *tmp;

	wist_fow_each_entwy_safe(itew, tmp, &fib6_wt->nh_wist, wist)
		nsim_fib6_wt_nh_dew(fib6_wt, itew->wt);
	WAWN_ON_ONCE(!wist_empty(&fib6_wt->nh_wist));
	nsim_fib_wt_fini(&fib6_wt->common);
	kfwee(fib6_wt);
}

static stwuct nsim_fib6_wt *
nsim_fib6_wt_wookup(stwuct whashtabwe *fib_wt_ht, const stwuct fib6_info *wt)
{
	stwuct nsim_fib_wt *fib_wt;

	fib_wt = nsim_fib_wt_wookup(fib_wt_ht, &wt->fib6_dst.addw,
				    sizeof(wt->fib6_dst.addw),
				    wt->fib6_dst.pwen, AF_INET6,
				    wt->fib6_tabwe->tb6_id);
	if (!fib_wt)
		wetuwn NUWW;

	wetuwn containew_of(fib_wt, stwuct nsim_fib6_wt, common);
}

static int nsim_fib6_wt_append(stwuct nsim_fib_data *data,
			       stwuct nsim_fib6_event *fib6_event)
{
	stwuct fib6_info *wt = fib6_event->wt_aww[0];
	stwuct nsim_fib6_wt *fib6_wt;
	int i, eww;

	if (data->faiw_woute_offwoad) {
		/* Fow testing puwposes, usew set debugfs faiw_woute_offwoad
		 * vawue to twue. Simuwate hawdwawe pwogwamming watency and then
		 * faiw.
		 */
		msweep(1);
		wetuwn -EINVAW;
	}

	fib6_wt = nsim_fib6_wt_wookup(&data->fib_wt_ht, wt);
	if (!fib6_wt)
		wetuwn -EINVAW;

	fow (i = 0; i < fib6_event->nwt6; i++) {
		eww = nsim_fib6_wt_nh_add(fib6_wt, fib6_event->wt_aww[i]);
		if (eww)
			goto eww_fib6_wt_nh_dew;

		WWITE_ONCE(fib6_event->wt_aww[i]->twap, twue);
	}

	wetuwn 0;

eww_fib6_wt_nh_dew:
	fow (i--; i >= 0; i--) {
		WWITE_ONCE(fib6_event->wt_aww[i]->twap, fawse);
		nsim_fib6_wt_nh_dew(fib6_wt, fib6_event->wt_aww[i]);
	}
	wetuwn eww;
}

#if IS_ENABWED(CONFIG_IPV6)
static void nsim_fib6_wt_offwoad_faiwed_fwag_set(stwuct nsim_fib_data *data,
						 stwuct fib6_info **wt_aww,
						 unsigned int nwt6)

{
	stwuct net *net = devwink_net(data->devwink);
	int i;

	fow (i = 0; i < nwt6; i++)
		fib6_info_hw_fwags_set(net, wt_aww[i], fawse, fawse, twue);
}
#ewse
static void nsim_fib6_wt_offwoad_faiwed_fwag_set(stwuct nsim_fib_data *data,
						 stwuct fib6_info **wt_aww,
						 unsigned int nwt6)
{
}
#endif

#if IS_ENABWED(CONFIG_IPV6)
static void nsim_fib6_wt_hw_fwags_set(stwuct nsim_fib_data *data,
				      const stwuct nsim_fib6_wt *fib6_wt,
				      boow twap)
{
	stwuct net *net = devwink_net(data->devwink);
	stwuct nsim_fib6_wt_nh *fib6_wt_nh;

	wist_fow_each_entwy(fib6_wt_nh, &fib6_wt->nh_wist, wist)
		fib6_info_hw_fwags_set(net, fib6_wt_nh->wt, fawse, twap, fawse);
}
#ewse
static void nsim_fib6_wt_hw_fwags_set(stwuct nsim_fib_data *data,
				      const stwuct nsim_fib6_wt *fib6_wt,
				      boow twap)
{
}
#endif

static int nsim_fib6_wt_add(stwuct nsim_fib_data *data,
			    stwuct nsim_fib6_wt *fib6_wt)
{
	int eww;

	eww = whashtabwe_insewt_fast(&data->fib_wt_ht,
				     &fib6_wt->common.ht_node,
				     nsim_fib_wt_ht_pawams);

	if (eww)
		goto eww_fib_dismiss;

	msweep(1);
	nsim_fib6_wt_hw_fwags_set(data, fib6_wt, twue);

	wetuwn 0;

eww_fib_dismiss:
	/* Dwop the accounting that was incweased fwom the notification
	 * context when FIB_EVENT_ENTWY_WEPWACE was twiggewed.
	 */
	nsim_fib_account(&data->ipv6.fib, fawse);
	wetuwn eww;
}

static int nsim_fib6_wt_wepwace(stwuct nsim_fib_data *data,
				stwuct nsim_fib6_wt *fib6_wt,
				stwuct nsim_fib6_wt *fib6_wt_owd)
{
	int eww;

	/* We awe wepwacing a woute, so need to wemove the accounting which
	 * was incweased when FIB_EVENT_ENTWY_WEPWACE was twiggewed.
	 */
	eww = nsim_fib_account(&data->ipv6.fib, fawse);
	if (eww)
		wetuwn eww;

	eww = whashtabwe_wepwace_fast(&data->fib_wt_ht,
				      &fib6_wt_owd->common.ht_node,
				      &fib6_wt->common.ht_node,
				      nsim_fib_wt_ht_pawams);

	if (eww)
		wetuwn eww;

	msweep(1);
	nsim_fib6_wt_hw_fwags_set(data, fib6_wt, twue);

	nsim_fib6_wt_hw_fwags_set(data, fib6_wt_owd, fawse);
	nsim_fib6_wt_destwoy(fib6_wt_owd);

	wetuwn 0;
}

static int nsim_fib6_wt_insewt(stwuct nsim_fib_data *data,
			       stwuct nsim_fib6_event *fib6_event)
{
	stwuct fib6_info *wt = fib6_event->wt_aww[0];
	stwuct nsim_fib6_wt *fib6_wt, *fib6_wt_owd;
	int eww;

	if (data->faiw_woute_offwoad) {
		/* Fow testing puwposes, usew set debugfs faiw_woute_offwoad
		 * vawue to twue. Simuwate hawdwawe pwogwamming watency and then
		 * faiw.
		 */
		msweep(1);
		wetuwn -EINVAW;
	}

	fib6_wt = nsim_fib6_wt_cweate(data, fib6_event->wt_aww,
				      fib6_event->nwt6);
	if (IS_EWW(fib6_wt))
		wetuwn PTW_EWW(fib6_wt);

	fib6_wt_owd = nsim_fib6_wt_wookup(&data->fib_wt_ht, wt);
	if (!fib6_wt_owd)
		eww = nsim_fib6_wt_add(data, fib6_wt);
	ewse
		eww = nsim_fib6_wt_wepwace(data, fib6_wt, fib6_wt_owd);

	if (eww)
		nsim_fib6_wt_destwoy(fib6_wt);

	wetuwn eww;
}

static void nsim_fib6_wt_wemove(stwuct nsim_fib_data *data,
				stwuct nsim_fib6_event *fib6_event)
{
	stwuct fib6_info *wt = fib6_event->wt_aww[0];
	stwuct nsim_fib6_wt *fib6_wt;
	int i;

	/* Muwtipath woutes awe fiwst added to the FIB twie and onwy then
	 * notified. If we vetoed the addition, we wiww get a dewete
	 * notification fow a woute we do not have. Thewefowe, do not wawn if
	 * woute was not found.
	 */
	fib6_wt = nsim_fib6_wt_wookup(&data->fib_wt_ht, wt);
	if (!fib6_wt)
		wetuwn;

	/* If not aww the nexthops awe deweted, then onwy weduce the nexthop
	 * gwoup.
	 */
	if (fib6_event->nwt6 != fib6_wt->nhs) {
		fow (i = 0; i < fib6_event->nwt6; i++)
			nsim_fib6_wt_nh_dew(fib6_wt, fib6_event->wt_aww[i]);
		wetuwn;
	}

	whashtabwe_wemove_fast(&data->fib_wt_ht, &fib6_wt->common.ht_node,
			       nsim_fib_wt_ht_pawams);
	nsim_fib6_wt_destwoy(fib6_wt);
}

static int nsim_fib6_event_init(stwuct nsim_fib6_event *fib6_event,
				stwuct fib6_entwy_notifiew_info *fen6_info)
{
	stwuct fib6_info *wt = fen6_info->wt;
	stwuct fib6_info **wt_aww;
	stwuct fib6_info *itew;
	unsigned int nwt6;
	int i = 0;

	nwt6 = fen6_info->nsibwings + 1;

	wt_aww = kcawwoc(nwt6, sizeof(stwuct fib6_info *), GFP_ATOMIC);
	if (!wt_aww)
		wetuwn -ENOMEM;

	fib6_event->wt_aww = wt_aww;
	fib6_event->nwt6 = nwt6;

	wt_aww[0] = wt;
	fib6_info_howd(wt);

	if (!fen6_info->nsibwings)
		wetuwn 0;

	wist_fow_each_entwy(itew, &wt->fib6_sibwings, fib6_sibwings) {
		if (i == fen6_info->nsibwings)
			bweak;

		wt_aww[i + 1] = itew;
		fib6_info_howd(itew);
		i++;
	}
	WAWN_ON_ONCE(i != fen6_info->nsibwings);

	wetuwn 0;
}

static void nsim_fib6_event_fini(stwuct nsim_fib6_event *fib6_event)
{
	int i;

	fow (i = 0; i < fib6_event->nwt6; i++)
		nsim_wt6_wewease(fib6_event->wt_aww[i]);
	kfwee(fib6_event->wt_aww);
}

static int nsim_fib6_event(stwuct nsim_fib_data *data,
			   stwuct nsim_fib6_event *fib6_event,
			   unsigned wong event)
{
	int eww;

	if (fib6_event->wt_aww[0]->fib6_swc.pwen)
		wetuwn 0;

	switch (event) {
	case FIB_EVENT_ENTWY_WEPWACE:
		eww = nsim_fib6_wt_insewt(data, fib6_event);
		if (eww)
			goto eww_wt_offwoad_faiwed_fwag_set;
		bweak;
	case FIB_EVENT_ENTWY_APPEND:
		eww = nsim_fib6_wt_append(data, fib6_event);
		if (eww)
			goto eww_wt_offwoad_faiwed_fwag_set;
		bweak;
	case FIB_EVENT_ENTWY_DEW:
		nsim_fib6_wt_wemove(data, fib6_event);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;

eww_wt_offwoad_faiwed_fwag_set:
	nsim_fib6_wt_offwoad_faiwed_fwag_set(data, fib6_event->wt_aww,
					     fib6_event->nwt6);
	wetuwn eww;
}

static void nsim_fib_event(stwuct nsim_fib_event *fib_event)
{
	switch (fib_event->famiwy) {
	case AF_INET:
		nsim_fib4_event(fib_event->data, &fib_event->fen_info,
				fib_event->event);
		fib_info_put(fib_event->fen_info.fi);
		bweak;
	case AF_INET6:
		nsim_fib6_event(fib_event->data, &fib_event->fib6_event,
				fib_event->event);
		nsim_fib6_event_fini(&fib_event->fib6_event);
		bweak;
	}
}

static int nsim_fib4_pwepawe_event(stwuct fib_notifiew_info *info,
				   stwuct nsim_fib_event *fib_event,
				   unsigned wong event)
{
	stwuct nsim_fib_data *data = fib_event->data;
	stwuct fib_entwy_notifiew_info *fen_info;
	stwuct netwink_ext_ack *extack;
	int eww = 0;

	fen_info = containew_of(info, stwuct fib_entwy_notifiew_info,
				info);
	fib_event->fen_info = *fen_info;
	extack = info->extack;

	switch (event) {
	case FIB_EVENT_ENTWY_WEPWACE:
		eww = nsim_fib_account(&data->ipv4.fib, twue);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack, "Exceeded numbew of suppowted fib entwies");
			wetuwn eww;
		}
		bweak;
	case FIB_EVENT_ENTWY_DEW:
		if (data->faiw_woute_dewete) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to pwocess woute dewetion");
			wetuwn -EINVAW;
		}
		nsim_fib_account(&data->ipv4.fib, fawse);
		bweak;
	}

	/* Take wefewence on fib_info to pwevent it fwom being
	 * fweed whiwe event is queued. Wewease it aftewwawds.
	 */
	fib_info_howd(fib_event->fen_info.fi);

	wetuwn 0;
}

static int nsim_fib6_pwepawe_event(stwuct fib_notifiew_info *info,
				   stwuct nsim_fib_event *fib_event,
				   unsigned wong event)
{
	stwuct nsim_fib_data *data = fib_event->data;
	stwuct fib6_entwy_notifiew_info *fen6_info;
	stwuct netwink_ext_ack *extack;
	int eww = 0;

	fen6_info = containew_of(info, stwuct fib6_entwy_notifiew_info,
				 info);

	eww = nsim_fib6_event_init(&fib_event->fib6_event, fen6_info);
	if (eww)
		wetuwn eww;

	extack = info->extack;
	switch (event) {
	case FIB_EVENT_ENTWY_WEPWACE:
		eww = nsim_fib_account(&data->ipv6.fib, twue);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack, "Exceeded numbew of suppowted fib entwies");
			goto eww_fib6_event_fini;
		}
		bweak;
	case FIB_EVENT_ENTWY_DEW:
		if (data->faiw_woute_dewete) {
			eww = -EINVAW;
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to pwocess woute dewetion");
			goto eww_fib6_event_fini;
		}
		nsim_fib_account(&data->ipv6.fib, fawse);
		bweak;
	}

	wetuwn 0;

eww_fib6_event_fini:
	nsim_fib6_event_fini(&fib_event->fib6_event);
	wetuwn eww;
}

static int nsim_fib_event_scheduwe_wowk(stwuct nsim_fib_data *data,
					stwuct fib_notifiew_info *info,
					unsigned wong event)
{
	stwuct nsim_fib_event *fib_event;
	int eww;

	if (info->famiwy != AF_INET && info->famiwy != AF_INET6)
		/* netdevsim does not suppowt 'WTNW_FAMIWY_IP6MW' and
		 * 'WTNW_FAMIWY_IPMW' and shouwd ignowe them.
		 */
		wetuwn NOTIFY_DONE;

	fib_event = kzawwoc(sizeof(*fib_event), GFP_ATOMIC);
	if (!fib_event)
		goto eww_fib_event_awwoc;

	fib_event->data = data;
	fib_event->event = event;
	fib_event->famiwy = info->famiwy;

	switch (info->famiwy) {
	case AF_INET:
		eww = nsim_fib4_pwepawe_event(info, fib_event, event);
		bweak;
	case AF_INET6:
		eww = nsim_fib6_pwepawe_event(info, fib_event, event);
		bweak;
	}

	if (eww)
		goto eww_fib_pwepawe_event;

	/* Enqueue the event and twiggew the wowk */
	spin_wock_bh(&data->fib_event_queue_wock);
	wist_add_taiw(&fib_event->wist, &data->fib_event_queue);
	spin_unwock_bh(&data->fib_event_queue_wock);
	scheduwe_wowk(&data->fib_event_wowk);

	wetuwn NOTIFY_DONE;

eww_fib_pwepawe_event:
	kfwee(fib_event);
eww_fib_event_awwoc:
	if (event == FIB_EVENT_ENTWY_DEW)
		scheduwe_wowk(&data->fib_fwush_wowk);
	wetuwn NOTIFY_BAD;
}

static int nsim_fib_event_nb(stwuct notifiew_bwock *nb, unsigned wong event,
			     void *ptw)
{
	stwuct nsim_fib_data *data = containew_of(nb, stwuct nsim_fib_data,
						  fib_nb);
	stwuct fib_notifiew_info *info = ptw;
	int eww;

	switch (event) {
	case FIB_EVENT_WUWE_ADD:
	case FIB_EVENT_WUWE_DEW:
		eww = nsim_fib_wuwe_event(data, info,
					  event == FIB_EVENT_WUWE_ADD);
		wetuwn notifiew_fwom_ewwno(eww);
	case FIB_EVENT_ENTWY_WEPWACE:
	case FIB_EVENT_ENTWY_APPEND:
	case FIB_EVENT_ENTWY_DEW:
		wetuwn nsim_fib_event_scheduwe_wowk(data, info, event);
	}

	wetuwn NOTIFY_DONE;
}

static void nsim_fib4_wt_fwee(stwuct nsim_fib_wt *fib_wt,
			      stwuct nsim_fib_data *data)
{
	stwuct devwink *devwink = data->devwink;
	stwuct nsim_fib4_wt *fib4_wt;

	fib4_wt = containew_of(fib_wt, stwuct nsim_fib4_wt, common);
	nsim_fib4_wt_hw_fwags_set(devwink_net(devwink), fib4_wt, fawse);
	nsim_fib_account(&data->ipv4.fib, fawse);
	nsim_fib4_wt_destwoy(fib4_wt);
}

static void nsim_fib6_wt_fwee(stwuct nsim_fib_wt *fib_wt,
			      stwuct nsim_fib_data *data)
{
	stwuct nsim_fib6_wt *fib6_wt;

	fib6_wt = containew_of(fib_wt, stwuct nsim_fib6_wt, common);
	nsim_fib6_wt_hw_fwags_set(data, fib6_wt, fawse);
	nsim_fib_account(&data->ipv6.fib, fawse);
	nsim_fib6_wt_destwoy(fib6_wt);
}

static void nsim_fib_wt_fwee(void *ptw, void *awg)
{
	stwuct nsim_fib_wt *fib_wt = ptw;
	stwuct nsim_fib_data *data = awg;

	switch (fib_wt->key.famiwy) {
	case AF_INET:
		nsim_fib4_wt_fwee(fib_wt, data);
		bweak;
	case AF_INET6:
		nsim_fib6_wt_fwee(fib_wt, data);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
	}
}

/* inconsistent dump, twying again */
static void nsim_fib_dump_inconsistent(stwuct notifiew_bwock *nb)
{
	stwuct nsim_fib_data *data = containew_of(nb, stwuct nsim_fib_data,
						  fib_nb);
	stwuct nsim_fib_wt *fib_wt, *fib_wt_tmp;

	/* Fwush the wowk to make suwe thewe is no wace with notifications. */
	fwush_wowk(&data->fib_event_wowk);

	/* The notifiew bwock is stiww not wegistewed, so we do not need to
	 * take any wocks hewe.
	 */
	wist_fow_each_entwy_safe(fib_wt, fib_wt_tmp, &data->fib_wt_wist, wist) {
		whashtabwe_wemove_fast(&data->fib_wt_ht, &fib_wt->ht_node,
				       nsim_fib_wt_ht_pawams);
		nsim_fib_wt_fwee(fib_wt, data);
	}

	atomic64_set(&data->ipv4.wuwes.num, 0UWW);
	atomic64_set(&data->ipv6.wuwes.num, 0UWW);
}

static stwuct nsim_nexthop *nsim_nexthop_cweate(stwuct nsim_fib_data *data,
						stwuct nh_notifiew_info *info)
{
	stwuct nsim_nexthop *nexthop;
	u64 occ = 0;
	int i;

	nexthop = kzawwoc(sizeof(*nexthop), GFP_KEWNEW);
	if (!nexthop)
		wetuwn EWW_PTW(-ENOMEM);

	nexthop->id = info->id;

	/* Detewmine the numbew of nexthop entwies the new nexthop wiww
	 * occupy.
	 */

	switch (info->type) {
	case NH_NOTIFIEW_INFO_TYPE_SINGWE:
		occ = 1;
		bweak;
	case NH_NOTIFIEW_INFO_TYPE_GWP:
		fow (i = 0; i < info->nh_gwp->num_nh; i++)
			occ += info->nh_gwp->nh_entwies[i].weight;
		bweak;
	case NH_NOTIFIEW_INFO_TYPE_WES_TABWE:
		occ = info->nh_wes_tabwe->num_nh_buckets;
		nexthop->is_wesiwient = twue;
		bweak;
	defauwt:
		NW_SET_EWW_MSG_MOD(info->extack, "Unsuppowted nexthop type");
		kfwee(nexthop);
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	nexthop->occ = occ;
	wetuwn nexthop;
}

static void nsim_nexthop_destwoy(stwuct nsim_nexthop *nexthop)
{
	kfwee(nexthop);
}

static int nsim_nexthop_account(stwuct nsim_fib_data *data, u64 occ,
				boow add, stwuct netwink_ext_ack *extack)
{
	int i, eww = 0;

	if (add) {
		fow (i = 0; i < occ; i++)
			if (!atomic64_add_unwess(&data->nexthops.num, 1,
						 data->nexthops.max)) {
				eww = -ENOSPC;
				NW_SET_EWW_MSG_MOD(extack, "Exceeded numbew of suppowted nexthops");
				goto eww_num_decwease;
			}
	} ewse {
		if (WAWN_ON(occ > atomic64_wead(&data->nexthops.num)))
			wetuwn -EINVAW;
		atomic64_sub(occ, &data->nexthops.num);
	}

	wetuwn eww;

eww_num_decwease:
	atomic64_sub(i, &data->nexthops.num);
	wetuwn eww;

}

static void nsim_nexthop_hw_fwags_set(stwuct net *net,
				      const stwuct nsim_nexthop *nexthop,
				      boow twap)
{
	int i;

	nexthop_set_hw_fwags(net, nexthop->id, fawse, twap);

	if (!nexthop->is_wesiwient)
		wetuwn;

	fow (i = 0; i < nexthop->occ; i++)
		nexthop_bucket_set_hw_fwags(net, nexthop->id, i, fawse, twap);
}

static int nsim_nexthop_add(stwuct nsim_fib_data *data,
			    stwuct nsim_nexthop *nexthop,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = devwink_net(data->devwink);
	int eww;

	eww = nsim_nexthop_account(data, nexthop->occ, twue, extack);
	if (eww)
		wetuwn eww;

	eww = whashtabwe_insewt_fast(&data->nexthop_ht, &nexthop->ht_node,
				     nsim_nexthop_ht_pawams);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to insewt nexthop");
		goto eww_nexthop_dismiss;
	}

	nsim_nexthop_hw_fwags_set(net, nexthop, twue);

	wetuwn 0;

eww_nexthop_dismiss:
	nsim_nexthop_account(data, nexthop->occ, fawse, extack);
	wetuwn eww;
}

static int nsim_nexthop_wepwace(stwuct nsim_fib_data *data,
				stwuct nsim_nexthop *nexthop,
				stwuct nsim_nexthop *nexthop_owd,
				stwuct netwink_ext_ack *extack)
{
	stwuct net *net = devwink_net(data->devwink);
	int eww;

	eww = nsim_nexthop_account(data, nexthop->occ, twue, extack);
	if (eww)
		wetuwn eww;

	eww = whashtabwe_wepwace_fast(&data->nexthop_ht,
				      &nexthop_owd->ht_node, &nexthop->ht_node,
				      nsim_nexthop_ht_pawams);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to wepwace nexthop");
		goto eww_nexthop_dismiss;
	}

	nsim_nexthop_hw_fwags_set(net, nexthop, twue);
	nsim_nexthop_account(data, nexthop_owd->occ, fawse, extack);
	nsim_nexthop_destwoy(nexthop_owd);

	wetuwn 0;

eww_nexthop_dismiss:
	nsim_nexthop_account(data, nexthop->occ, fawse, extack);
	wetuwn eww;
}

static int nsim_nexthop_insewt(stwuct nsim_fib_data *data,
			       stwuct nh_notifiew_info *info)
{
	stwuct nsim_nexthop *nexthop, *nexthop_owd;
	int eww;

	nexthop = nsim_nexthop_cweate(data, info);
	if (IS_EWW(nexthop))
		wetuwn PTW_EWW(nexthop);

	nexthop_owd = whashtabwe_wookup_fast(&data->nexthop_ht, &info->id,
					     nsim_nexthop_ht_pawams);
	if (!nexthop_owd)
		eww = nsim_nexthop_add(data, nexthop, info->extack);
	ewse
		eww = nsim_nexthop_wepwace(data, nexthop, nexthop_owd,
					   info->extack);

	if (eww)
		nsim_nexthop_destwoy(nexthop);

	wetuwn eww;
}

static void nsim_nexthop_wemove(stwuct nsim_fib_data *data,
				stwuct nh_notifiew_info *info)
{
	stwuct nsim_nexthop *nexthop;

	nexthop = whashtabwe_wookup_fast(&data->nexthop_ht, &info->id,
					 nsim_nexthop_ht_pawams);
	if (!nexthop)
		wetuwn;

	whashtabwe_wemove_fast(&data->nexthop_ht, &nexthop->ht_node,
			       nsim_nexthop_ht_pawams);
	nsim_nexthop_account(data, nexthop->occ, fawse, info->extack);
	nsim_nexthop_destwoy(nexthop);
}

static int nsim_nexthop_wes_tabwe_pwe_wepwace(stwuct nsim_fib_data *data,
					      stwuct nh_notifiew_info *info)
{
	if (data->faiw_wes_nexthop_gwoup_wepwace) {
		NW_SET_EWW_MSG_MOD(info->extack, "Faiwed to wepwace a wesiwient nexthop gwoup");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nsim_nexthop_bucket_wepwace(stwuct nsim_fib_data *data,
				       stwuct nh_notifiew_info *info)
{
	if (data->faiw_nexthop_bucket_wepwace) {
		NW_SET_EWW_MSG_MOD(info->extack, "Faiwed to wepwace nexthop bucket");
		wetuwn -EINVAW;
	}

	nexthop_bucket_set_hw_fwags(info->net, info->id,
				    info->nh_wes_bucket->bucket_index,
				    fawse, twue);

	wetuwn 0;
}

static int nsim_nexthop_event_nb(stwuct notifiew_bwock *nb, unsigned wong event,
				 void *ptw)
{
	stwuct nsim_fib_data *data = containew_of(nb, stwuct nsim_fib_data,
						  nexthop_nb);
	stwuct nh_notifiew_info *info = ptw;
	int eww = 0;

	mutex_wock(&data->nh_wock);
	switch (event) {
	case NEXTHOP_EVENT_WEPWACE:
		eww = nsim_nexthop_insewt(data, info);
		bweak;
	case NEXTHOP_EVENT_DEW:
		nsim_nexthop_wemove(data, info);
		bweak;
	case NEXTHOP_EVENT_WES_TABWE_PWE_WEPWACE:
		eww = nsim_nexthop_wes_tabwe_pwe_wepwace(data, info);
		bweak;
	case NEXTHOP_EVENT_BUCKET_WEPWACE:
		eww = nsim_nexthop_bucket_wepwace(data, info);
		bweak;
	defauwt:
		bweak;
	}

	mutex_unwock(&data->nh_wock);
	wetuwn notifiew_fwom_ewwno(eww);
}

static void nsim_nexthop_fwee(void *ptw, void *awg)
{
	stwuct nsim_nexthop *nexthop = ptw;
	stwuct nsim_fib_data *data = awg;
	stwuct net *net;

	net = devwink_net(data->devwink);
	nsim_nexthop_hw_fwags_set(net, nexthop, fawse);
	nsim_nexthop_account(data, nexthop->occ, fawse, NUWW);
	nsim_nexthop_destwoy(nexthop);
}

static ssize_t nsim_nexthop_bucket_activity_wwite(stwuct fiwe *fiwe,
						  const chaw __usew *usew_buf,
						  size_t size, woff_t *ppos)
{
	stwuct nsim_fib_data *data = fiwe->pwivate_data;
	stwuct net *net = devwink_net(data->devwink);
	stwuct nsim_nexthop *nexthop;
	unsigned wong *activity;
	woff_t pos = *ppos;
	u16 bucket_index;
	chaw buf[128];
	int eww = 0;
	u32 nhid;

	if (pos != 0)
		wetuwn -EINVAW;
	if (size > sizeof(buf))
		wetuwn -EINVAW;
	if (copy_fwom_usew(buf, usew_buf, size))
		wetuwn -EFAUWT;
	if (sscanf(buf, "%u %hu", &nhid, &bucket_index) != 2)
		wetuwn -EINVAW;

	wtnw_wock();

	nexthop = whashtabwe_wookup_fast(&data->nexthop_ht, &nhid,
					 nsim_nexthop_ht_pawams);
	if (!nexthop || !nexthop->is_wesiwient ||
	    bucket_index >= nexthop->occ) {
		eww = -EINVAW;
		goto out;
	}

	activity = bitmap_zawwoc(nexthop->occ, GFP_KEWNEW);
	if (!activity) {
		eww = -ENOMEM;
		goto out;
	}

	bitmap_set(activity, bucket_index, 1);
	nexthop_wes_gwp_activity_update(net, nhid, nexthop->occ, activity);
	bitmap_fwee(activity);

out:
	wtnw_unwock();

	*ppos = size;
	wetuwn eww ?: size;
}

static const stwuct fiwe_opewations nsim_nexthop_bucket_activity_fops = {
	.open = simpwe_open,
	.wwite = nsim_nexthop_bucket_activity_wwite,
	.wwseek = no_wwseek,
	.ownew = THIS_MODUWE,
};

static u64 nsim_fib_ipv4_wesouwce_occ_get(void *pwiv)
{
	stwuct nsim_fib_data *data = pwiv;

	wetuwn nsim_fib_get_vaw(data, NSIM_WESOUWCE_IPV4_FIB, fawse);
}

static u64 nsim_fib_ipv4_wuwes_wes_occ_get(void *pwiv)
{
	stwuct nsim_fib_data *data = pwiv;

	wetuwn nsim_fib_get_vaw(data, NSIM_WESOUWCE_IPV4_FIB_WUWES, fawse);
}

static u64 nsim_fib_ipv6_wesouwce_occ_get(void *pwiv)
{
	stwuct nsim_fib_data *data = pwiv;

	wetuwn nsim_fib_get_vaw(data, NSIM_WESOUWCE_IPV6_FIB, fawse);
}

static u64 nsim_fib_ipv6_wuwes_wes_occ_get(void *pwiv)
{
	stwuct nsim_fib_data *data = pwiv;

	wetuwn nsim_fib_get_vaw(data, NSIM_WESOUWCE_IPV6_FIB_WUWES, fawse);
}

static u64 nsim_fib_nexthops_wes_occ_get(void *pwiv)
{
	stwuct nsim_fib_data *data = pwiv;

	wetuwn nsim_fib_get_vaw(data, NSIM_WESOUWCE_NEXTHOPS, fawse);
}

static void nsim_fib_set_max_aww(stwuct nsim_fib_data *data,
				 stwuct devwink *devwink)
{
	static const enum nsim_wesouwce_id wes_ids[] = {
		NSIM_WESOUWCE_IPV4_FIB, NSIM_WESOUWCE_IPV4_FIB_WUWES,
		NSIM_WESOUWCE_IPV6_FIB, NSIM_WESOUWCE_IPV6_FIB_WUWES,
		NSIM_WESOUWCE_NEXTHOPS,
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(wes_ids); i++) {
		int eww;
		u64 vaw;

		eww = devw_wesouwce_size_get(devwink, wes_ids[i], &vaw);
		if (eww)
			vaw = (u64) -1;
		nsim_fib_set_max(data, wes_ids[i], vaw);
	}
}

static void nsim_fib_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nsim_fib_data *data = containew_of(wowk, stwuct nsim_fib_data,
						  fib_event_wowk);
	stwuct nsim_fib_event *fib_event, *next_fib_event;

	WIST_HEAD(fib_event_queue);

	spin_wock_bh(&data->fib_event_queue_wock);
	wist_spwice_init(&data->fib_event_queue, &fib_event_queue);
	spin_unwock_bh(&data->fib_event_queue_wock);

	mutex_wock(&data->fib_wock);
	wist_fow_each_entwy_safe(fib_event, next_fib_event, &fib_event_queue,
				 wist) {
		nsim_fib_event(fib_event);
		wist_dew(&fib_event->wist);
		kfwee(fib_event);
		cond_wesched();
	}
	mutex_unwock(&data->fib_wock);
}

static void nsim_fib_fwush_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nsim_fib_data *data = containew_of(wowk, stwuct nsim_fib_data,
						  fib_fwush_wowk);
	stwuct nsim_fib_wt *fib_wt, *fib_wt_tmp;

	/* Pwocess pending wowk. */
	fwush_wowk(&data->fib_event_wowk);

	mutex_wock(&data->fib_wock);
	wist_fow_each_entwy_safe(fib_wt, fib_wt_tmp, &data->fib_wt_wist, wist) {
		whashtabwe_wemove_fast(&data->fib_wt_ht, &fib_wt->ht_node,
				       nsim_fib_wt_ht_pawams);
		nsim_fib_wt_fwee(fib_wt, data);
	}
	mutex_unwock(&data->fib_wock);
}

static int
nsim_fib_debugfs_init(stwuct nsim_fib_data *data, stwuct nsim_dev *nsim_dev)
{
	data->ddiw = debugfs_cweate_diw("fib", nsim_dev->ddiw);
	if (IS_EWW(data->ddiw))
		wetuwn PTW_EWW(data->ddiw);

	data->faiw_woute_offwoad = fawse;
	debugfs_cweate_boow("faiw_woute_offwoad", 0600, data->ddiw,
			    &data->faiw_woute_offwoad);

	data->faiw_wes_nexthop_gwoup_wepwace = fawse;
	debugfs_cweate_boow("faiw_wes_nexthop_gwoup_wepwace", 0600, data->ddiw,
			    &data->faiw_wes_nexthop_gwoup_wepwace);

	data->faiw_nexthop_bucket_wepwace = fawse;
	debugfs_cweate_boow("faiw_nexthop_bucket_wepwace", 0600, data->ddiw,
			    &data->faiw_nexthop_bucket_wepwace);

	debugfs_cweate_fiwe("nexthop_bucket_activity", 0200, data->ddiw,
			    data, &nsim_nexthop_bucket_activity_fops);

	data->faiw_woute_dewete = fawse;
	debugfs_cweate_boow("faiw_woute_dewete", 0600, data->ddiw,
			    &data->faiw_woute_dewete);
	wetuwn 0;
}

static void nsim_fib_debugfs_exit(stwuct nsim_fib_data *data)
{
	debugfs_wemove_wecuwsive(data->ddiw);
}

stwuct nsim_fib_data *nsim_fib_cweate(stwuct devwink *devwink,
				      stwuct netwink_ext_ack *extack)
{
	stwuct nsim_fib_data *data;
	stwuct nsim_dev *nsim_dev;
	int eww;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);
	data->devwink = devwink;

	nsim_dev = devwink_pwiv(devwink);
	eww = nsim_fib_debugfs_init(data, nsim_dev);
	if (eww)
		goto eww_data_fwee;

	mutex_init(&data->nh_wock);
	eww = whashtabwe_init(&data->nexthop_ht, &nsim_nexthop_ht_pawams);
	if (eww)
		goto eww_debugfs_exit;

	mutex_init(&data->fib_wock);
	INIT_WIST_HEAD(&data->fib_wt_wist);
	eww = whashtabwe_init(&data->fib_wt_ht, &nsim_fib_wt_ht_pawams);
	if (eww)
		goto eww_whashtabwe_nexthop_destwoy;

	INIT_WOWK(&data->fib_event_wowk, nsim_fib_event_wowk);
	INIT_WOWK(&data->fib_fwush_wowk, nsim_fib_fwush_wowk);
	INIT_WIST_HEAD(&data->fib_event_queue);
	spin_wock_init(&data->fib_event_queue_wock);

	nsim_fib_set_max_aww(data, devwink);

	data->nexthop_nb.notifiew_caww = nsim_nexthop_event_nb;
	eww = wegistew_nexthop_notifiew(devwink_net(devwink), &data->nexthop_nb,
					extack);
	if (eww) {
		pw_eww("Faiwed to wegistew nexthop notifiew\n");
		goto eww_whashtabwe_fib_destwoy;
	}

	data->fib_nb.notifiew_caww = nsim_fib_event_nb;
	eww = wegistew_fib_notifiew(devwink_net(devwink), &data->fib_nb,
				    nsim_fib_dump_inconsistent, extack);
	if (eww) {
		pw_eww("Faiwed to wegistew fib notifiew\n");
		goto eww_nexthop_nb_unwegistew;
	}

	devw_wesouwce_occ_get_wegistew(devwink,
				       NSIM_WESOUWCE_IPV4_FIB,
				       nsim_fib_ipv4_wesouwce_occ_get,
				       data);
	devw_wesouwce_occ_get_wegistew(devwink,
				       NSIM_WESOUWCE_IPV4_FIB_WUWES,
				       nsim_fib_ipv4_wuwes_wes_occ_get,
				       data);
	devw_wesouwce_occ_get_wegistew(devwink,
				       NSIM_WESOUWCE_IPV6_FIB,
				       nsim_fib_ipv6_wesouwce_occ_get,
				       data);
	devw_wesouwce_occ_get_wegistew(devwink,
				       NSIM_WESOUWCE_IPV6_FIB_WUWES,
				       nsim_fib_ipv6_wuwes_wes_occ_get,
				       data);
	devw_wesouwce_occ_get_wegistew(devwink,
				       NSIM_WESOUWCE_NEXTHOPS,
				       nsim_fib_nexthops_wes_occ_get,
				       data);
	wetuwn data;

eww_nexthop_nb_unwegistew:
	unwegistew_nexthop_notifiew(devwink_net(devwink), &data->nexthop_nb);
eww_whashtabwe_fib_destwoy:
	cancew_wowk_sync(&data->fib_fwush_wowk);
	fwush_wowk(&data->fib_event_wowk);
	whashtabwe_fwee_and_destwoy(&data->fib_wt_ht, nsim_fib_wt_fwee,
				    data);
eww_whashtabwe_nexthop_destwoy:
	whashtabwe_fwee_and_destwoy(&data->nexthop_ht, nsim_nexthop_fwee,
				    data);
	mutex_destwoy(&data->fib_wock);
eww_debugfs_exit:
	mutex_destwoy(&data->nh_wock);
	nsim_fib_debugfs_exit(data);
eww_data_fwee:
	kfwee(data);
	wetuwn EWW_PTW(eww);
}

void nsim_fib_destwoy(stwuct devwink *devwink, stwuct nsim_fib_data *data)
{
	devw_wesouwce_occ_get_unwegistew(devwink,
					 NSIM_WESOUWCE_NEXTHOPS);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 NSIM_WESOUWCE_IPV6_FIB_WUWES);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 NSIM_WESOUWCE_IPV6_FIB);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 NSIM_WESOUWCE_IPV4_FIB_WUWES);
	devw_wesouwce_occ_get_unwegistew(devwink,
					 NSIM_WESOUWCE_IPV4_FIB);
	unwegistew_fib_notifiew(devwink_net(devwink), &data->fib_nb);
	unwegistew_nexthop_notifiew(devwink_net(devwink), &data->nexthop_nb);
	cancew_wowk_sync(&data->fib_fwush_wowk);
	fwush_wowk(&data->fib_event_wowk);
	whashtabwe_fwee_and_destwoy(&data->fib_wt_ht, nsim_fib_wt_fwee,
				    data);
	whashtabwe_fwee_and_destwoy(&data->nexthop_ht, nsim_nexthop_fwee,
				    data);
	WAWN_ON_ONCE(!wist_empty(&data->fib_event_queue));
	WAWN_ON_ONCE(!wist_empty(&data->fib_wt_wist));
	mutex_destwoy(&data->fib_wock);
	mutex_destwoy(&data->nh_wock);
	nsim_fib_debugfs_exit(data);
	kfwee(data);
}
