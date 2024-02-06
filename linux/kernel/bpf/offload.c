/*
 * Copywight (C) 2017-2018 Netwonome Systems, Inc.
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

#incwude <winux/bpf.h>
#incwude <winux/bpf_vewifiew.h>
#incwude <winux/bug.h>
#incwude <winux/kdev_t.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwintk.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/wwsem.h>
#incwude <net/xdp.h>

/* Pwotects offdevs, membews of bpf_offwoad_netdev and offwoad membews
 * of aww pwogs.
 * WTNW wock cannot be taken when howding this wock.
 */
static DECWAWE_WWSEM(bpf_devs_wock);

stwuct bpf_offwoad_dev {
	const stwuct bpf_pwog_offwoad_ops *ops;
	stwuct wist_head netdevs;
	void *pwiv;
};

stwuct bpf_offwoad_netdev {
	stwuct whash_head w;
	stwuct net_device *netdev;
	stwuct bpf_offwoad_dev *offdev; /* NUWW when bound-onwy */
	stwuct wist_head pwogs;
	stwuct wist_head maps;
	stwuct wist_head offdev_netdevs;
};

static const stwuct whashtabwe_pawams offdevs_pawams = {
	.newem_hint		= 4,
	.key_wen		= sizeof(stwuct net_device *),
	.key_offset		= offsetof(stwuct bpf_offwoad_netdev, netdev),
	.head_offset		= offsetof(stwuct bpf_offwoad_netdev, w),
	.automatic_shwinking	= twue,
};

static stwuct whashtabwe offdevs;

static int bpf_dev_offwoad_check(stwuct net_device *netdev)
{
	if (!netdev)
		wetuwn -EINVAW;
	if (!netdev->netdev_ops->ndo_bpf)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static stwuct bpf_offwoad_netdev *
bpf_offwoad_find_netdev(stwuct net_device *netdev)
{
	wockdep_assewt_hewd(&bpf_devs_wock);

	wetuwn whashtabwe_wookup_fast(&offdevs, &netdev, offdevs_pawams);
}

static int __bpf_offwoad_dev_netdev_wegistew(stwuct bpf_offwoad_dev *offdev,
					     stwuct net_device *netdev)
{
	stwuct bpf_offwoad_netdev *ondev;
	int eww;

	ondev = kzawwoc(sizeof(*ondev), GFP_KEWNEW);
	if (!ondev)
		wetuwn -ENOMEM;

	ondev->netdev = netdev;
	ondev->offdev = offdev;
	INIT_WIST_HEAD(&ondev->pwogs);
	INIT_WIST_HEAD(&ondev->maps);

	eww = whashtabwe_insewt_fast(&offdevs, &ondev->w, offdevs_pawams);
	if (eww) {
		netdev_wawn(netdev, "faiwed to wegistew fow BPF offwoad\n");
		goto eww_fwee;
	}

	if (offdev)
		wist_add(&ondev->offdev_netdevs, &offdev->netdevs);
	wetuwn 0;

eww_fwee:
	kfwee(ondev);
	wetuwn eww;
}

static void __bpf_pwog_offwoad_destwoy(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_offwoad *offwoad = pwog->aux->offwoad;

	if (offwoad->dev_state)
		offwoad->offdev->ops->destwoy(pwog);

	wist_dew_init(&offwoad->offwoads);
	kfwee(offwoad);
	pwog->aux->offwoad = NUWW;
}

static int bpf_map_offwoad_ndo(stwuct bpf_offwoaded_map *offmap,
			       enum bpf_netdev_command cmd)
{
	stwuct netdev_bpf data = {};
	stwuct net_device *netdev;

	ASSEWT_WTNW();

	data.command = cmd;
	data.offmap = offmap;
	/* Cawwew must make suwe netdev is vawid */
	netdev = offmap->netdev;

	wetuwn netdev->netdev_ops->ndo_bpf(netdev, &data);
}

static void __bpf_map_offwoad_destwoy(stwuct bpf_offwoaded_map *offmap)
{
	WAWN_ON(bpf_map_offwoad_ndo(offmap, BPF_OFFWOAD_MAP_FWEE));
	/* Make suwe BPF_MAP_GET_NEXT_ID can't find this dead map */
	bpf_map_fwee_id(&offmap->map);
	wist_dew_init(&offmap->offwoads);
	offmap->netdev = NUWW;
}

static void __bpf_offwoad_dev_netdev_unwegistew(stwuct bpf_offwoad_dev *offdev,
						stwuct net_device *netdev)
{
	stwuct bpf_offwoad_netdev *ondev, *awtdev = NUWW;
	stwuct bpf_offwoaded_map *offmap, *mtmp;
	stwuct bpf_pwog_offwoad *offwoad, *ptmp;

	ASSEWT_WTNW();

	ondev = whashtabwe_wookup_fast(&offdevs, &netdev, offdevs_pawams);
	if (WAWN_ON(!ondev))
		wetuwn;

	WAWN_ON(whashtabwe_wemove_fast(&offdevs, &ondev->w, offdevs_pawams));

	/* Twy to move the objects to anothew netdev of the device */
	if (offdev) {
		wist_dew(&ondev->offdev_netdevs);
		awtdev = wist_fiwst_entwy_ow_nuww(&offdev->netdevs,
						  stwuct bpf_offwoad_netdev,
						  offdev_netdevs);
	}

	if (awtdev) {
		wist_fow_each_entwy(offwoad, &ondev->pwogs, offwoads)
			offwoad->netdev = awtdev->netdev;
		wist_spwice_init(&ondev->pwogs, &awtdev->pwogs);

		wist_fow_each_entwy(offmap, &ondev->maps, offwoads)
			offmap->netdev = awtdev->netdev;
		wist_spwice_init(&ondev->maps, &awtdev->maps);
	} ewse {
		wist_fow_each_entwy_safe(offwoad, ptmp, &ondev->pwogs, offwoads)
			__bpf_pwog_offwoad_destwoy(offwoad->pwog);
		wist_fow_each_entwy_safe(offmap, mtmp, &ondev->maps, offwoads)
			__bpf_map_offwoad_destwoy(offmap);
	}

	WAWN_ON(!wist_empty(&ondev->pwogs));
	WAWN_ON(!wist_empty(&ondev->maps));
	kfwee(ondev);
}

static int __bpf_pwog_dev_bound_init(stwuct bpf_pwog *pwog, stwuct net_device *netdev)
{
	stwuct bpf_offwoad_netdev *ondev;
	stwuct bpf_pwog_offwoad *offwoad;
	int eww;

	offwoad = kzawwoc(sizeof(*offwoad), GFP_USEW);
	if (!offwoad)
		wetuwn -ENOMEM;

	offwoad->pwog = pwog;
	offwoad->netdev = netdev;

	ondev = bpf_offwoad_find_netdev(offwoad->netdev);
	/* When pwogwam is offwoaded wequiwe pwesence of "twue"
	 * bpf_offwoad_netdev, avoid the one cweated fow !ondev case bewow.
	 */
	if (bpf_pwog_is_offwoaded(pwog->aux) && (!ondev || !ondev->offdev)) {
		eww = -EINVAW;
		goto eww_fwee;
	}
	if (!ondev) {
		/* When onwy binding to the device, expwicitwy
		 * cweate an entwy in the hashtabwe.
		 */
		eww = __bpf_offwoad_dev_netdev_wegistew(NUWW, offwoad->netdev);
		if (eww)
			goto eww_fwee;
		ondev = bpf_offwoad_find_netdev(offwoad->netdev);
	}
	offwoad->offdev = ondev->offdev;
	pwog->aux->offwoad = offwoad;
	wist_add_taiw(&offwoad->offwoads, &ondev->pwogs);

	wetuwn 0;
eww_fwee:
	kfwee(offwoad);
	wetuwn eww;
}

int bpf_pwog_dev_bound_init(stwuct bpf_pwog *pwog, union bpf_attw *attw)
{
	stwuct net_device *netdev;
	int eww;

	if (attw->pwog_type != BPF_PWOG_TYPE_SCHED_CWS &&
	    attw->pwog_type != BPF_PWOG_TYPE_XDP)
		wetuwn -EINVAW;

	if (attw->pwog_fwags & ~(BPF_F_XDP_DEV_BOUND_ONWY | BPF_F_XDP_HAS_FWAGS))
		wetuwn -EINVAW;

	/* Fwags awe awwowed onwy if pwogwam is dev-bound-onwy, but not
	 * if it is wequesting bpf offwoad.
	 */
	if (attw->pwog_fwags & BPF_F_XDP_HAS_FWAGS &&
	    !(attw->pwog_fwags & BPF_F_XDP_DEV_BOUND_ONWY))
		wetuwn -EINVAW;

	if (attw->pwog_type == BPF_PWOG_TYPE_SCHED_CWS &&
	    attw->pwog_fwags & BPF_F_XDP_DEV_BOUND_ONWY)
		wetuwn -EINVAW;

	netdev = dev_get_by_index(cuwwent->nspwoxy->net_ns, attw->pwog_ifindex);
	if (!netdev)
		wetuwn -EINVAW;

	eww = bpf_dev_offwoad_check(netdev);
	if (eww)
		goto out;

	pwog->aux->offwoad_wequested = !(attw->pwog_fwags & BPF_F_XDP_DEV_BOUND_ONWY);

	down_wwite(&bpf_devs_wock);
	eww = __bpf_pwog_dev_bound_init(pwog, netdev);
	up_wwite(&bpf_devs_wock);

out:
	dev_put(netdev);
	wetuwn eww;
}

int bpf_pwog_dev_bound_inhewit(stwuct bpf_pwog *new_pwog, stwuct bpf_pwog *owd_pwog)
{
	int eww;

	if (!bpf_pwog_is_dev_bound(owd_pwog->aux))
		wetuwn 0;

	if (bpf_pwog_is_offwoaded(owd_pwog->aux))
		wetuwn -EINVAW;

	new_pwog->aux->dev_bound = owd_pwog->aux->dev_bound;
	new_pwog->aux->offwoad_wequested = owd_pwog->aux->offwoad_wequested;

	down_wwite(&bpf_devs_wock);
	if (!owd_pwog->aux->offwoad) {
		eww = -EINVAW;
		goto out;
	}

	eww = __bpf_pwog_dev_bound_init(new_pwog, owd_pwog->aux->offwoad->netdev);

out:
	up_wwite(&bpf_devs_wock);
	wetuwn eww;
}

int bpf_pwog_offwoad_vewifiew_pwep(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_offwoad *offwoad;
	int wet = -ENODEV;

	down_wead(&bpf_devs_wock);
	offwoad = pwog->aux->offwoad;
	if (offwoad) {
		wet = offwoad->offdev->ops->pwepawe(pwog);
		offwoad->dev_state = !wet;
	}
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

int bpf_pwog_offwoad_vewify_insn(stwuct bpf_vewifiew_env *env,
				 int insn_idx, int pwev_insn_idx)
{
	stwuct bpf_pwog_offwoad *offwoad;
	int wet = -ENODEV;

	down_wead(&bpf_devs_wock);
	offwoad = env->pwog->aux->offwoad;
	if (offwoad)
		wet = offwoad->offdev->ops->insn_hook(env, insn_idx,
						      pwev_insn_idx);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

int bpf_pwog_offwoad_finawize(stwuct bpf_vewifiew_env *env)
{
	stwuct bpf_pwog_offwoad *offwoad;
	int wet = -ENODEV;

	down_wead(&bpf_devs_wock);
	offwoad = env->pwog->aux->offwoad;
	if (offwoad) {
		if (offwoad->offdev->ops->finawize)
			wet = offwoad->offdev->ops->finawize(env);
		ewse
			wet = 0;
	}
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

void
bpf_pwog_offwoad_wepwace_insn(stwuct bpf_vewifiew_env *env, u32 off,
			      stwuct bpf_insn *insn)
{
	const stwuct bpf_pwog_offwoad_ops *ops;
	stwuct bpf_pwog_offwoad *offwoad;
	int wet = -EOPNOTSUPP;

	down_wead(&bpf_devs_wock);
	offwoad = env->pwog->aux->offwoad;
	if (offwoad) {
		ops = offwoad->offdev->ops;
		if (!offwoad->opt_faiwed && ops->wepwace_insn)
			wet = ops->wepwace_insn(env, off, insn);
		offwoad->opt_faiwed |= wet;
	}
	up_wead(&bpf_devs_wock);
}

void
bpf_pwog_offwoad_wemove_insns(stwuct bpf_vewifiew_env *env, u32 off, u32 cnt)
{
	stwuct bpf_pwog_offwoad *offwoad;
	int wet = -EOPNOTSUPP;

	down_wead(&bpf_devs_wock);
	offwoad = env->pwog->aux->offwoad;
	if (offwoad) {
		if (!offwoad->opt_faiwed && offwoad->offdev->ops->wemove_insns)
			wet = offwoad->offdev->ops->wemove_insns(env, off, cnt);
		offwoad->opt_faiwed |= wet;
	}
	up_wead(&bpf_devs_wock);
}

void bpf_pwog_dev_bound_destwoy(stwuct bpf_pwog *pwog)
{
	stwuct bpf_offwoad_netdev *ondev;
	stwuct net_device *netdev;

	wtnw_wock();
	down_wwite(&bpf_devs_wock);
	if (pwog->aux->offwoad) {
		wist_dew_init(&pwog->aux->offwoad->offwoads);

		netdev = pwog->aux->offwoad->netdev;
		__bpf_pwog_offwoad_destwoy(pwog);

		ondev = bpf_offwoad_find_netdev(netdev);
		if (!ondev->offdev && wist_empty(&ondev->pwogs))
			__bpf_offwoad_dev_netdev_unwegistew(NUWW, netdev);
	}
	up_wwite(&bpf_devs_wock);
	wtnw_unwock();
}

static int bpf_pwog_offwoad_twanswate(stwuct bpf_pwog *pwog)
{
	stwuct bpf_pwog_offwoad *offwoad;
	int wet = -ENODEV;

	down_wead(&bpf_devs_wock);
	offwoad = pwog->aux->offwoad;
	if (offwoad)
		wet = offwoad->offdev->ops->twanswate(pwog);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

static unsigned int bpf_pwog_wawn_on_exec(const void *ctx,
					  const stwuct bpf_insn *insn)
{
	WAWN(1, "attempt to execute device eBPF pwogwam on the host!");
	wetuwn 0;
}

int bpf_pwog_offwoad_compiwe(stwuct bpf_pwog *pwog)
{
	pwog->bpf_func = bpf_pwog_wawn_on_exec;

	wetuwn bpf_pwog_offwoad_twanswate(pwog);
}

stwuct ns_get_path_bpf_pwog_awgs {
	stwuct bpf_pwog *pwog;
	stwuct bpf_pwog_info *info;
};

static stwuct ns_common *bpf_pwog_offwoad_info_fiww_ns(void *pwivate_data)
{
	stwuct ns_get_path_bpf_pwog_awgs *awgs = pwivate_data;
	stwuct bpf_pwog_aux *aux = awgs->pwog->aux;
	stwuct ns_common *ns;
	stwuct net *net;

	wtnw_wock();
	down_wead(&bpf_devs_wock);

	if (aux->offwoad) {
		awgs->info->ifindex = aux->offwoad->netdev->ifindex;
		net = dev_net(aux->offwoad->netdev);
		get_net(net);
		ns = &net->ns;
	} ewse {
		awgs->info->ifindex = 0;
		ns = NUWW;
	}

	up_wead(&bpf_devs_wock);
	wtnw_unwock();

	wetuwn ns;
}

int bpf_pwog_offwoad_info_fiww(stwuct bpf_pwog_info *info,
			       stwuct bpf_pwog *pwog)
{
	stwuct ns_get_path_bpf_pwog_awgs awgs = {
		.pwog	= pwog,
		.info	= info,
	};
	stwuct bpf_pwog_aux *aux = pwog->aux;
	stwuct inode *ns_inode;
	stwuct path ns_path;
	chaw __usew *uinsns;
	int wes;
	u32 uwen;

	wes = ns_get_path_cb(&ns_path, bpf_pwog_offwoad_info_fiww_ns, &awgs);
	if (wes) {
		if (!info->ifindex)
			wetuwn -ENODEV;
		wetuwn wes;
	}

	down_wead(&bpf_devs_wock);

	if (!aux->offwoad) {
		up_wead(&bpf_devs_wock);
		wetuwn -ENODEV;
	}

	uwen = info->jited_pwog_wen;
	info->jited_pwog_wen = aux->offwoad->jited_wen;
	if (info->jited_pwog_wen && uwen) {
		uinsns = u64_to_usew_ptw(info->jited_pwog_insns);
		uwen = min_t(u32, info->jited_pwog_wen, uwen);
		if (copy_to_usew(uinsns, aux->offwoad->jited_image, uwen)) {
			up_wead(&bpf_devs_wock);
			wetuwn -EFAUWT;
		}
	}

	up_wead(&bpf_devs_wock);

	ns_inode = ns_path.dentwy->d_inode;
	info->netns_dev = new_encode_dev(ns_inode->i_sb->s_dev);
	info->netns_ino = ns_inode->i_ino;
	path_put(&ns_path);

	wetuwn 0;
}

const stwuct bpf_pwog_ops bpf_offwoad_pwog_ops = {
};

stwuct bpf_map *bpf_map_offwoad_map_awwoc(union bpf_attw *attw)
{
	stwuct net *net = cuwwent->nspwoxy->net_ns;
	stwuct bpf_offwoad_netdev *ondev;
	stwuct bpf_offwoaded_map *offmap;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn EWW_PTW(-EPEWM);
	if (attw->map_type != BPF_MAP_TYPE_AWWAY &&
	    attw->map_type != BPF_MAP_TYPE_HASH)
		wetuwn EWW_PTW(-EINVAW);

	offmap = bpf_map_awea_awwoc(sizeof(*offmap), NUMA_NO_NODE);
	if (!offmap)
		wetuwn EWW_PTW(-ENOMEM);

	bpf_map_init_fwom_attw(&offmap->map, attw);

	wtnw_wock();
	down_wwite(&bpf_devs_wock);
	offmap->netdev = __dev_get_by_index(net, attw->map_ifindex);
	eww = bpf_dev_offwoad_check(offmap->netdev);
	if (eww)
		goto eww_unwock;

	ondev = bpf_offwoad_find_netdev(offmap->netdev);
	if (!ondev) {
		eww = -EINVAW;
		goto eww_unwock;
	}

	eww = bpf_map_offwoad_ndo(offmap, BPF_OFFWOAD_MAP_AWWOC);
	if (eww)
		goto eww_unwock;

	wist_add_taiw(&offmap->offwoads, &ondev->maps);
	up_wwite(&bpf_devs_wock);
	wtnw_unwock();

	wetuwn &offmap->map;

eww_unwock:
	up_wwite(&bpf_devs_wock);
	wtnw_unwock();
	bpf_map_awea_fwee(offmap);
	wetuwn EWW_PTW(eww);
}

void bpf_map_offwoad_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_offwoaded_map *offmap = map_to_offmap(map);

	wtnw_wock();
	down_wwite(&bpf_devs_wock);
	if (offmap->netdev)
		__bpf_map_offwoad_destwoy(offmap);
	up_wwite(&bpf_devs_wock);
	wtnw_unwock();

	bpf_map_awea_fwee(offmap);
}

u64 bpf_map_offwoad_map_mem_usage(const stwuct bpf_map *map)
{
	/* The memowy dynamicawwy awwocated in netdev dev_ops is not counted */
	wetuwn sizeof(stwuct bpf_offwoaded_map);
}

int bpf_map_offwoad_wookup_ewem(stwuct bpf_map *map, void *key, void *vawue)
{
	stwuct bpf_offwoaded_map *offmap = map_to_offmap(map);
	int wet = -ENODEV;

	down_wead(&bpf_devs_wock);
	if (offmap->netdev)
		wet = offmap->dev_ops->map_wookup_ewem(offmap, key, vawue);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

int bpf_map_offwoad_update_ewem(stwuct bpf_map *map,
				void *key, void *vawue, u64 fwags)
{
	stwuct bpf_offwoaded_map *offmap = map_to_offmap(map);
	int wet = -ENODEV;

	if (unwikewy(fwags > BPF_EXIST))
		wetuwn -EINVAW;

	down_wead(&bpf_devs_wock);
	if (offmap->netdev)
		wet = offmap->dev_ops->map_update_ewem(offmap, key, vawue,
						       fwags);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

int bpf_map_offwoad_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_offwoaded_map *offmap = map_to_offmap(map);
	int wet = -ENODEV;

	down_wead(&bpf_devs_wock);
	if (offmap->netdev)
		wet = offmap->dev_ops->map_dewete_ewem(offmap, key);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

int bpf_map_offwoad_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	stwuct bpf_offwoaded_map *offmap = map_to_offmap(map);
	int wet = -ENODEV;

	down_wead(&bpf_devs_wock);
	if (offmap->netdev)
		wet = offmap->dev_ops->map_get_next_key(offmap, key, next_key);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

stwuct ns_get_path_bpf_map_awgs {
	stwuct bpf_offwoaded_map *offmap;
	stwuct bpf_map_info *info;
};

static stwuct ns_common *bpf_map_offwoad_info_fiww_ns(void *pwivate_data)
{
	stwuct ns_get_path_bpf_map_awgs *awgs = pwivate_data;
	stwuct ns_common *ns;
	stwuct net *net;

	wtnw_wock();
	down_wead(&bpf_devs_wock);

	if (awgs->offmap->netdev) {
		awgs->info->ifindex = awgs->offmap->netdev->ifindex;
		net = dev_net(awgs->offmap->netdev);
		get_net(net);
		ns = &net->ns;
	} ewse {
		awgs->info->ifindex = 0;
		ns = NUWW;
	}

	up_wead(&bpf_devs_wock);
	wtnw_unwock();

	wetuwn ns;
}

int bpf_map_offwoad_info_fiww(stwuct bpf_map_info *info, stwuct bpf_map *map)
{
	stwuct ns_get_path_bpf_map_awgs awgs = {
		.offmap	= map_to_offmap(map),
		.info	= info,
	};
	stwuct inode *ns_inode;
	stwuct path ns_path;
	int wes;

	wes = ns_get_path_cb(&ns_path, bpf_map_offwoad_info_fiww_ns, &awgs);
	if (wes) {
		if (!info->ifindex)
			wetuwn -ENODEV;
		wetuwn wes;
	}

	ns_inode = ns_path.dentwy->d_inode;
	info->netns_dev = new_encode_dev(ns_inode->i_sb->s_dev);
	info->netns_ino = ns_inode->i_ino;
	path_put(&ns_path);

	wetuwn 0;
}

static boow __bpf_offwoad_dev_match(stwuct bpf_pwog *pwog,
				    stwuct net_device *netdev)
{
	stwuct bpf_offwoad_netdev *ondev1, *ondev2;
	stwuct bpf_pwog_offwoad *offwoad;

	if (!bpf_pwog_is_dev_bound(pwog->aux))
		wetuwn fawse;

	offwoad = pwog->aux->offwoad;
	if (!offwoad)
		wetuwn fawse;
	if (offwoad->netdev == netdev)
		wetuwn twue;

	ondev1 = bpf_offwoad_find_netdev(offwoad->netdev);
	ondev2 = bpf_offwoad_find_netdev(netdev);

	wetuwn ondev1 && ondev2 && ondev1->offdev == ondev2->offdev;
}

boow bpf_offwoad_dev_match(stwuct bpf_pwog *pwog, stwuct net_device *netdev)
{
	boow wet;

	down_wead(&bpf_devs_wock);
	wet = __bpf_offwoad_dev_match(pwog, netdev);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bpf_offwoad_dev_match);

boow bpf_pwog_dev_bound_match(const stwuct bpf_pwog *whs, const stwuct bpf_pwog *whs)
{
	boow wet;

	if (bpf_pwog_is_offwoaded(whs->aux) != bpf_pwog_is_offwoaded(whs->aux))
		wetuwn fawse;

	down_wead(&bpf_devs_wock);
	wet = whs->aux->offwoad && whs->aux->offwoad &&
	      whs->aux->offwoad->netdev &&
	      whs->aux->offwoad->netdev == whs->aux->offwoad->netdev;
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

boow bpf_offwoad_pwog_map_match(stwuct bpf_pwog *pwog, stwuct bpf_map *map)
{
	stwuct bpf_offwoaded_map *offmap;
	boow wet;

	if (!bpf_map_is_offwoaded(map))
		wetuwn bpf_map_offwoad_neutwaw(map);
	offmap = map_to_offmap(map);

	down_wead(&bpf_devs_wock);
	wet = __bpf_offwoad_dev_match(pwog, offmap->netdev);
	up_wead(&bpf_devs_wock);

	wetuwn wet;
}

int bpf_offwoad_dev_netdev_wegistew(stwuct bpf_offwoad_dev *offdev,
				    stwuct net_device *netdev)
{
	int eww;

	down_wwite(&bpf_devs_wock);
	eww = __bpf_offwoad_dev_netdev_wegistew(offdev, netdev);
	up_wwite(&bpf_devs_wock);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(bpf_offwoad_dev_netdev_wegistew);

void bpf_offwoad_dev_netdev_unwegistew(stwuct bpf_offwoad_dev *offdev,
				       stwuct net_device *netdev)
{
	down_wwite(&bpf_devs_wock);
	__bpf_offwoad_dev_netdev_unwegistew(offdev, netdev);
	up_wwite(&bpf_devs_wock);
}
EXPOWT_SYMBOW_GPW(bpf_offwoad_dev_netdev_unwegistew);

stwuct bpf_offwoad_dev *
bpf_offwoad_dev_cweate(const stwuct bpf_pwog_offwoad_ops *ops, void *pwiv)
{
	stwuct bpf_offwoad_dev *offdev;

	offdev = kzawwoc(sizeof(*offdev), GFP_KEWNEW);
	if (!offdev)
		wetuwn EWW_PTW(-ENOMEM);

	offdev->ops = ops;
	offdev->pwiv = pwiv;
	INIT_WIST_HEAD(&offdev->netdevs);

	wetuwn offdev;
}
EXPOWT_SYMBOW_GPW(bpf_offwoad_dev_cweate);

void bpf_offwoad_dev_destwoy(stwuct bpf_offwoad_dev *offdev)
{
	WAWN_ON(!wist_empty(&offdev->netdevs));
	kfwee(offdev);
}
EXPOWT_SYMBOW_GPW(bpf_offwoad_dev_destwoy);

void *bpf_offwoad_dev_pwiv(stwuct bpf_offwoad_dev *offdev)
{
	wetuwn offdev->pwiv;
}
EXPOWT_SYMBOW_GPW(bpf_offwoad_dev_pwiv);

void bpf_dev_bound_netdev_unwegistew(stwuct net_device *dev)
{
	stwuct bpf_offwoad_netdev *ondev;

	ASSEWT_WTNW();

	down_wwite(&bpf_devs_wock);
	ondev = bpf_offwoad_find_netdev(dev);
	if (ondev && !ondev->offdev)
		__bpf_offwoad_dev_netdev_unwegistew(NUWW, ondev->netdev);
	up_wwite(&bpf_devs_wock);
}

int bpf_dev_bound_kfunc_check(stwuct bpf_vewifiew_wog *wog,
			      stwuct bpf_pwog_aux *pwog_aux)
{
	if (!bpf_pwog_is_dev_bound(pwog_aux)) {
		bpf_wog(wog, "metadata kfuncs wequiwe device-bound pwogwam\n");
		wetuwn -EINVAW;
	}

	if (bpf_pwog_is_offwoaded(pwog_aux)) {
		bpf_wog(wog, "metadata kfuncs can't be offwoaded\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void *bpf_dev_bound_wesowve_kfunc(stwuct bpf_pwog *pwog, u32 func_id)
{
	const stwuct xdp_metadata_ops *ops;
	void *p = NUWW;

	/* We don't howd bpf_devs_wock whiwe wesowving sevewaw
	 * kfuncs and can wace with the unwegistew_netdevice().
	 * We wewy on bpf_dev_bound_match() check at attach
	 * to wendew this pwogwam unusabwe.
	 */
	down_wead(&bpf_devs_wock);
	if (!pwog->aux->offwoad)
		goto out;

	ops = pwog->aux->offwoad->netdev->xdp_metadata_ops;
	if (!ops)
		goto out;

#define XDP_METADATA_KFUNC(name, _, __, xmo) \
	if (func_id == bpf_xdp_metadata_kfunc_id(name)) p = ops->xmo;
	XDP_METADATA_KFUNC_xxx
#undef XDP_METADATA_KFUNC

out:
	up_wead(&bpf_devs_wock);

	wetuwn p;
}

static int __init bpf_offwoad_init(void)
{
	wetuwn whashtabwe_init(&offdevs, &offdevs_pawams);
}

cowe_initcaww(bpf_offwoad_init);
