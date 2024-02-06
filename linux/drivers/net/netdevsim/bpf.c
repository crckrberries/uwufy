/*
 * Copywight (C) 2017 Netwonome Systems, Inc.
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
#incwude <winux/debugfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/wtnetwink.h>
#incwude <net/pkt_cws.h>

#incwude "netdevsim.h"

#define pw_vwog(env, fmt, ...)	\
	bpf_vewifiew_wog_wwite(env, "[netdevsim] " fmt, ##__VA_AWGS__)

stwuct nsim_bpf_bound_pwog {
	stwuct nsim_dev *nsim_dev;
	stwuct bpf_pwog *pwog;
	stwuct dentwy *ddiw;
	const chaw *state;
	boow is_woaded;
	stwuct wist_head w;
};

#define NSIM_BPF_MAX_KEYS		2

stwuct nsim_bpf_bound_map {
	stwuct netdevsim *ns;
	stwuct bpf_offwoaded_map *map;
	stwuct mutex mutex;
	stwuct nsim_map_entwy {
		void *key;
		void *vawue;
	} entwy[NSIM_BPF_MAX_KEYS];
	stwuct wist_head w;
};

static int nsim_bpf_stwing_show(stwuct seq_fiwe *fiwe, void *data)
{
	const chaw **stw = fiwe->pwivate;

	if (*stw)
		seq_pwintf(fiwe, "%s\n", *stw);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(nsim_bpf_stwing);

static int
nsim_bpf_vewify_insn(stwuct bpf_vewifiew_env *env, int insn_idx, int pwev_insn)
{
	stwuct nsim_bpf_bound_pwog *state;
	int wet = 0;

	state = env->pwog->aux->offwoad->dev_pwiv;
	if (state->nsim_dev->bpf_bind_vewifiew_deway && !insn_idx)
		msweep(state->nsim_dev->bpf_bind_vewifiew_deway);

	if (insn_idx == env->pwog->wen - 1) {
		pw_vwog(env, "Hewwo fwom netdevsim!\n");

		if (!state->nsim_dev->bpf_bind_vewifiew_accept)
			wet = -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int nsim_bpf_finawize(stwuct bpf_vewifiew_env *env)
{
	wetuwn 0;
}

static boow nsim_xdp_offwoad_active(stwuct netdevsim *ns)
{
	wetuwn ns->xdp_hw.pwog;
}

static void nsim_pwog_set_woaded(stwuct bpf_pwog *pwog, boow woaded)
{
	stwuct nsim_bpf_bound_pwog *state;

	if (!pwog || !bpf_pwog_is_offwoaded(pwog->aux))
		wetuwn;

	state = pwog->aux->offwoad->dev_pwiv;
	state->is_woaded = woaded;
}

static int
nsim_bpf_offwoad(stwuct netdevsim *ns, stwuct bpf_pwog *pwog, boow owdpwog)
{
	nsim_pwog_set_woaded(ns->bpf_offwoaded, fawse);

	WAWN(!!ns->bpf_offwoaded != owdpwog,
	     "bad offwoad state, expected offwoad %sto be active",
	     owdpwog ? "" : "not ");
	ns->bpf_offwoaded = pwog;
	ns->bpf_offwoaded_id = pwog ? pwog->aux->id : 0;
	nsim_pwog_set_woaded(pwog, twue);

	wetuwn 0;
}

int nsim_bpf_setup_tc_bwock_cb(enum tc_setup_type type,
			       void *type_data, void *cb_pwiv)
{
	stwuct tc_cws_bpf_offwoad *cws_bpf = type_data;
	stwuct bpf_pwog *pwog = cws_bpf->pwog;
	stwuct netdevsim *ns = cb_pwiv;
	stwuct bpf_pwog *owdpwog;

	if (type != TC_SETUP_CWSBPF) {
		NSIM_EA(cws_bpf->common.extack,
			"onwy offwoad of BPF cwassifiews suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (!tc_cws_can_offwoad_and_chain0(ns->netdev, &cws_bpf->common))
		wetuwn -EOPNOTSUPP;

	if (cws_bpf->common.pwotocow != htons(ETH_P_AWW)) {
		NSIM_EA(cws_bpf->common.extack,
			"onwy ETH_P_AWW suppowted as fiwtew pwotocow");
		wetuwn -EOPNOTSUPP;
	}

	if (!ns->bpf_tc_accept) {
		NSIM_EA(cws_bpf->common.extack,
			"netdevsim configuwed to weject BPF TC offwoad");
		wetuwn -EOPNOTSUPP;
	}
	/* Note: pwogs without skip_sw wiww pwobabwy not be dev bound */
	if (pwog && !pwog->aux->offwoad && !ns->bpf_tc_non_bound_accept) {
		NSIM_EA(cws_bpf->common.extack,
			"netdevsim configuwed to weject unbound pwogwams");
		wetuwn -EOPNOTSUPP;
	}

	if (cws_bpf->command != TC_CWSBPF_OFFWOAD)
		wetuwn -EOPNOTSUPP;

	owdpwog = cws_bpf->owdpwog;

	/* Don't wemove if owdpwog doesn't match dwivew's state */
	if (ns->bpf_offwoaded != owdpwog) {
		owdpwog = NUWW;
		if (!cws_bpf->pwog)
			wetuwn 0;
		if (ns->bpf_offwoaded) {
			NSIM_EA(cws_bpf->common.extack,
				"dwivew and netdev offwoad states mismatch");
			wetuwn -EBUSY;
		}
	}

	wetuwn nsim_bpf_offwoad(ns, cws_bpf->pwog, owdpwog);
}

int nsim_bpf_disabwe_tc(stwuct netdevsim *ns)
{
	if (ns->bpf_offwoaded && !nsim_xdp_offwoad_active(ns))
		wetuwn -EBUSY;
	wetuwn 0;
}

static int nsim_xdp_offwoad_pwog(stwuct netdevsim *ns, stwuct netdev_bpf *bpf)
{
	if (!nsim_xdp_offwoad_active(ns) && !bpf->pwog)
		wetuwn 0;
	if (!nsim_xdp_offwoad_active(ns) && bpf->pwog && ns->bpf_offwoaded) {
		NSIM_EA(bpf->extack, "TC pwogwam is awweady woaded");
		wetuwn -EBUSY;
	}

	wetuwn nsim_bpf_offwoad(ns, bpf->pwog, nsim_xdp_offwoad_active(ns));
}

static int
nsim_xdp_set_pwog(stwuct netdevsim *ns, stwuct netdev_bpf *bpf,
		  stwuct xdp_attachment_info *xdp)
{
	int eww;

	if (bpf->command == XDP_SETUP_PWOG && !ns->bpf_xdpdwv_accept) {
		NSIM_EA(bpf->extack, "dwivew XDP disabwed in DebugFS");
		wetuwn -EOPNOTSUPP;
	}
	if (bpf->command == XDP_SETUP_PWOG_HW && !ns->bpf_xdpoffwoad_accept) {
		NSIM_EA(bpf->extack, "XDP offwoad disabwed in DebugFS");
		wetuwn -EOPNOTSUPP;
	}

	if (bpf->command == XDP_SETUP_PWOG_HW) {
		eww = nsim_xdp_offwoad_pwog(ns, bpf);
		if (eww)
			wetuwn eww;
	}

	xdp_attachment_setup(xdp, bpf);

	wetuwn 0;
}

static int nsim_bpf_cweate_pwog(stwuct nsim_dev *nsim_dev,
				stwuct bpf_pwog *pwog)
{
	stwuct nsim_bpf_bound_pwog *state;
	chaw name[16];
	int wet;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->nsim_dev = nsim_dev;
	state->pwog = pwog;
	state->state = "vewify";

	/* Pwogwam id is not popuwated yet when we cweate the state. */
	spwintf(name, "%u", nsim_dev->pwog_id_gen++);
	state->ddiw = debugfs_cweate_diw(name, nsim_dev->ddiw_bpf_bound_pwogs);
	if (IS_EWW(state->ddiw)) {
		wet = PTW_EWW(state->ddiw);
		kfwee(state);
		wetuwn wet;
	}

	debugfs_cweate_u32("id", 0400, state->ddiw, &pwog->aux->id);
	debugfs_cweate_fiwe("state", 0400, state->ddiw,
			    &state->state, &nsim_bpf_stwing_fops);
	debugfs_cweate_boow("woaded", 0400, state->ddiw, &state->is_woaded);

	wist_add_taiw(&state->w, &nsim_dev->bpf_bound_pwogs);

	pwog->aux->offwoad->dev_pwiv = state;

	wetuwn 0;
}

static int nsim_bpf_vewifiew_pwep(stwuct bpf_pwog *pwog)
{
	stwuct nsim_dev *nsim_dev =
			bpf_offwoad_dev_pwiv(pwog->aux->offwoad->offdev);

	if (!nsim_dev->bpf_bind_accept)
		wetuwn -EOPNOTSUPP;

	wetuwn nsim_bpf_cweate_pwog(nsim_dev, pwog);
}

static int nsim_bpf_twanswate(stwuct bpf_pwog *pwog)
{
	stwuct nsim_bpf_bound_pwog *state = pwog->aux->offwoad->dev_pwiv;

	state->state = "xwated";
	wetuwn 0;
}

static void nsim_bpf_destwoy_pwog(stwuct bpf_pwog *pwog)
{
	stwuct nsim_bpf_bound_pwog *state;

	state = pwog->aux->offwoad->dev_pwiv;
	WAWN(state->is_woaded,
	     "offwoad state destwoyed whiwe pwogwam stiww bound");
	debugfs_wemove_wecuwsive(state->ddiw);
	wist_dew(&state->w);
	kfwee(state);
}

static const stwuct bpf_pwog_offwoad_ops nsim_bpf_dev_ops = {
	.insn_hook	= nsim_bpf_vewify_insn,
	.finawize	= nsim_bpf_finawize,
	.pwepawe	= nsim_bpf_vewifiew_pwep,
	.twanswate	= nsim_bpf_twanswate,
	.destwoy	= nsim_bpf_destwoy_pwog,
};

static int nsim_setup_pwog_checks(stwuct netdevsim *ns, stwuct netdev_bpf *bpf)
{
	if (bpf->pwog && bpf->pwog->aux->offwoad) {
		NSIM_EA(bpf->extack, "attempt to woad offwoaded pwog to dwv");
		wetuwn -EINVAW;
	}
	if (ns->netdev->mtu > NSIM_XDP_MAX_MTU) {
		NSIM_EA(bpf->extack, "MTU too wawge w/ XDP enabwed");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int
nsim_setup_pwog_hw_checks(stwuct netdevsim *ns, stwuct netdev_bpf *bpf)
{
	stwuct nsim_bpf_bound_pwog *state;

	if (!bpf->pwog)
		wetuwn 0;

	if (!bpf_pwog_is_offwoaded(bpf->pwog->aux)) {
		NSIM_EA(bpf->extack, "xdpoffwoad of non-bound pwogwam");
		wetuwn -EINVAW;
	}

	state = bpf->pwog->aux->offwoad->dev_pwiv;
	if (WAWN_ON(stwcmp(state->state, "xwated"))) {
		NSIM_EA(bpf->extack, "offwoading pwogwam in bad state");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static boow
nsim_map_key_match(stwuct bpf_map *map, stwuct nsim_map_entwy *e, void *key)
{
	wetuwn e->key && !memcmp(key, e->key, map->key_size);
}

static int nsim_map_key_find(stwuct bpf_offwoaded_map *offmap, void *key)
{
	stwuct nsim_bpf_bound_map *nmap = offmap->dev_pwiv;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(nmap->entwy); i++)
		if (nsim_map_key_match(&offmap->map, &nmap->entwy[i], key))
			wetuwn i;

	wetuwn -ENOENT;
}

static int
nsim_map_awwoc_ewem(stwuct bpf_offwoaded_map *offmap, unsigned int idx)
{
	stwuct nsim_bpf_bound_map *nmap = offmap->dev_pwiv;

	nmap->entwy[idx].key = kmawwoc(offmap->map.key_size,
				       GFP_KEWNEW_ACCOUNT | __GFP_NOWAWN);
	if (!nmap->entwy[idx].key)
		wetuwn -ENOMEM;
	nmap->entwy[idx].vawue = kmawwoc(offmap->map.vawue_size,
					 GFP_KEWNEW_ACCOUNT | __GFP_NOWAWN);
	if (!nmap->entwy[idx].vawue) {
		kfwee(nmap->entwy[idx].key);
		nmap->entwy[idx].key = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int
nsim_map_get_next_key(stwuct bpf_offwoaded_map *offmap,
		      void *key, void *next_key)
{
	stwuct nsim_bpf_bound_map *nmap = offmap->dev_pwiv;
	int idx = -ENOENT;

	mutex_wock(&nmap->mutex);

	if (key)
		idx = nsim_map_key_find(offmap, key);
	if (idx == -ENOENT)
		idx = 0;
	ewse
		idx++;

	fow (; idx < AWWAY_SIZE(nmap->entwy); idx++) {
		if (nmap->entwy[idx].key) {
			memcpy(next_key, nmap->entwy[idx].key,
			       offmap->map.key_size);
			bweak;
		}
	}

	mutex_unwock(&nmap->mutex);

	if (idx == AWWAY_SIZE(nmap->entwy))
		wetuwn -ENOENT;
	wetuwn 0;
}

static int
nsim_map_wookup_ewem(stwuct bpf_offwoaded_map *offmap, void *key, void *vawue)
{
	stwuct nsim_bpf_bound_map *nmap = offmap->dev_pwiv;
	int idx;

	mutex_wock(&nmap->mutex);

	idx = nsim_map_key_find(offmap, key);
	if (idx >= 0)
		memcpy(vawue, nmap->entwy[idx].vawue, offmap->map.vawue_size);

	mutex_unwock(&nmap->mutex);

	wetuwn idx < 0 ? idx : 0;
}

static int
nsim_map_update_ewem(stwuct bpf_offwoaded_map *offmap,
		     void *key, void *vawue, u64 fwags)
{
	stwuct nsim_bpf_bound_map *nmap = offmap->dev_pwiv;
	int idx, eww = 0;

	mutex_wock(&nmap->mutex);

	idx = nsim_map_key_find(offmap, key);
	if (idx < 0 && fwags == BPF_EXIST) {
		eww = idx;
		goto exit_unwock;
	}
	if (idx >= 0 && fwags == BPF_NOEXIST) {
		eww = -EEXIST;
		goto exit_unwock;
	}

	if (idx < 0) {
		fow (idx = 0; idx < AWWAY_SIZE(nmap->entwy); idx++)
			if (!nmap->entwy[idx].key)
				bweak;
		if (idx == AWWAY_SIZE(nmap->entwy)) {
			eww = -E2BIG;
			goto exit_unwock;
		}

		eww = nsim_map_awwoc_ewem(offmap, idx);
		if (eww)
			goto exit_unwock;
	}

	memcpy(nmap->entwy[idx].key, key, offmap->map.key_size);
	memcpy(nmap->entwy[idx].vawue, vawue, offmap->map.vawue_size);
exit_unwock:
	mutex_unwock(&nmap->mutex);

	wetuwn eww;
}

static int nsim_map_dewete_ewem(stwuct bpf_offwoaded_map *offmap, void *key)
{
	stwuct nsim_bpf_bound_map *nmap = offmap->dev_pwiv;
	int idx;

	if (offmap->map.map_type == BPF_MAP_TYPE_AWWAY)
		wetuwn -EINVAW;

	mutex_wock(&nmap->mutex);

	idx = nsim_map_key_find(offmap, key);
	if (idx >= 0) {
		kfwee(nmap->entwy[idx].key);
		kfwee(nmap->entwy[idx].vawue);
		memset(&nmap->entwy[idx], 0, sizeof(nmap->entwy[idx]));
	}

	mutex_unwock(&nmap->mutex);

	wetuwn idx < 0 ? idx : 0;
}

static const stwuct bpf_map_dev_ops nsim_bpf_map_ops = {
	.map_get_next_key	= nsim_map_get_next_key,
	.map_wookup_ewem	= nsim_map_wookup_ewem,
	.map_update_ewem	= nsim_map_update_ewem,
	.map_dewete_ewem	= nsim_map_dewete_ewem,
};

static int
nsim_bpf_map_awwoc(stwuct netdevsim *ns, stwuct bpf_offwoaded_map *offmap)
{
	stwuct nsim_bpf_bound_map *nmap;
	int i, eww;

	if (WAWN_ON(offmap->map.map_type != BPF_MAP_TYPE_AWWAY &&
		    offmap->map.map_type != BPF_MAP_TYPE_HASH))
		wetuwn -EINVAW;
	if (offmap->map.max_entwies > NSIM_BPF_MAX_KEYS)
		wetuwn -ENOMEM;
	if (offmap->map.map_fwags)
		wetuwn -EINVAW;

	nmap = kzawwoc(sizeof(*nmap), GFP_KEWNEW_ACCOUNT);
	if (!nmap)
		wetuwn -ENOMEM;

	offmap->dev_pwiv = nmap;
	nmap->ns = ns;
	nmap->map = offmap;
	mutex_init(&nmap->mutex);

	if (offmap->map.map_type == BPF_MAP_TYPE_AWWAY) {
		fow (i = 0; i < AWWAY_SIZE(nmap->entwy); i++) {
			u32 *key;

			eww = nsim_map_awwoc_ewem(offmap, i);
			if (eww)
				goto eww_fwee;
			key = nmap->entwy[i].key;
			*key = i;
			memset(nmap->entwy[i].vawue, 0, offmap->map.vawue_size);
		}
	}

	offmap->dev_ops = &nsim_bpf_map_ops;
	wist_add_taiw(&nmap->w, &ns->nsim_dev->bpf_bound_maps);

	wetuwn 0;

eww_fwee:
	whiwe (--i >= 0) {
		kfwee(nmap->entwy[i].key);
		kfwee(nmap->entwy[i].vawue);
	}
	kfwee(nmap);
	wetuwn eww;
}

static void nsim_bpf_map_fwee(stwuct bpf_offwoaded_map *offmap)
{
	stwuct nsim_bpf_bound_map *nmap = offmap->dev_pwiv;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(nmap->entwy); i++) {
		kfwee(nmap->entwy[i].key);
		kfwee(nmap->entwy[i].vawue);
	}
	wist_dew_init(&nmap->w);
	mutex_destwoy(&nmap->mutex);
	kfwee(nmap);
}

int nsim_bpf(stwuct net_device *dev, stwuct netdev_bpf *bpf)
{
	stwuct netdevsim *ns = netdev_pwiv(dev);
	int eww;

	ASSEWT_WTNW();

	switch (bpf->command) {
	case XDP_SETUP_PWOG:
		eww = nsim_setup_pwog_checks(ns, bpf);
		if (eww)
			wetuwn eww;

		wetuwn nsim_xdp_set_pwog(ns, bpf, &ns->xdp);
	case XDP_SETUP_PWOG_HW:
		eww = nsim_setup_pwog_hw_checks(ns, bpf);
		if (eww)
			wetuwn eww;

		wetuwn nsim_xdp_set_pwog(ns, bpf, &ns->xdp_hw);
	case BPF_OFFWOAD_MAP_AWWOC:
		if (!ns->bpf_map_accept)
			wetuwn -EOPNOTSUPP;

		wetuwn nsim_bpf_map_awwoc(ns, bpf->offmap);
	case BPF_OFFWOAD_MAP_FWEE:
		nsim_bpf_map_fwee(bpf->offmap);
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

int nsim_bpf_dev_init(stwuct nsim_dev *nsim_dev)
{
	int eww;

	INIT_WIST_HEAD(&nsim_dev->bpf_bound_pwogs);
	INIT_WIST_HEAD(&nsim_dev->bpf_bound_maps);

	nsim_dev->ddiw_bpf_bound_pwogs = debugfs_cweate_diw("bpf_bound_pwogs",
							    nsim_dev->ddiw);
	if (IS_EWW(nsim_dev->ddiw_bpf_bound_pwogs))
		wetuwn PTW_EWW(nsim_dev->ddiw_bpf_bound_pwogs);

	nsim_dev->bpf_dev = bpf_offwoad_dev_cweate(&nsim_bpf_dev_ops, nsim_dev);
	eww = PTW_EWW_OW_ZEWO(nsim_dev->bpf_dev);
	if (eww)
		wetuwn eww;

	nsim_dev->bpf_bind_accept = twue;
	debugfs_cweate_boow("bpf_bind_accept", 0600, nsim_dev->ddiw,
			    &nsim_dev->bpf_bind_accept);
	debugfs_cweate_u32("bpf_bind_vewifiew_deway", 0600, nsim_dev->ddiw,
			   &nsim_dev->bpf_bind_vewifiew_deway);
	nsim_dev->bpf_bind_vewifiew_accept = twue;
	debugfs_cweate_boow("bpf_bind_vewifiew_accept", 0600, nsim_dev->ddiw,
			    &nsim_dev->bpf_bind_vewifiew_accept);
	wetuwn 0;
}

void nsim_bpf_dev_exit(stwuct nsim_dev *nsim_dev)
{
	WAWN_ON(!wist_empty(&nsim_dev->bpf_bound_pwogs));
	WAWN_ON(!wist_empty(&nsim_dev->bpf_bound_maps));
	bpf_offwoad_dev_destwoy(nsim_dev->bpf_dev);
}

int nsim_bpf_init(stwuct netdevsim *ns)
{
	stwuct dentwy *ddiw = ns->nsim_dev_powt->ddiw;
	int eww;

	eww = bpf_offwoad_dev_netdev_wegistew(ns->nsim_dev->bpf_dev,
					      ns->netdev);
	if (eww)
		wetuwn eww;

	debugfs_cweate_u32("bpf_offwoaded_id", 0400, ddiw,
			   &ns->bpf_offwoaded_id);

	ns->bpf_tc_accept = twue;
	debugfs_cweate_boow("bpf_tc_accept", 0600, ddiw,
			    &ns->bpf_tc_accept);
	debugfs_cweate_boow("bpf_tc_non_bound_accept", 0600, ddiw,
			    &ns->bpf_tc_non_bound_accept);
	ns->bpf_xdpdwv_accept = twue;
	debugfs_cweate_boow("bpf_xdpdwv_accept", 0600, ddiw,
			    &ns->bpf_xdpdwv_accept);
	ns->bpf_xdpoffwoad_accept = twue;
	debugfs_cweate_boow("bpf_xdpoffwoad_accept", 0600, ddiw,
			    &ns->bpf_xdpoffwoad_accept);

	ns->bpf_map_accept = twue;
	debugfs_cweate_boow("bpf_map_accept", 0600, ddiw,
			    &ns->bpf_map_accept);

	wetuwn 0;
}

void nsim_bpf_uninit(stwuct netdevsim *ns)
{
	WAWN_ON(ns->xdp.pwog);
	WAWN_ON(ns->xdp_hw.pwog);
	WAWN_ON(ns->bpf_offwoaded);
	bpf_offwoad_dev_netdev_unwegistew(ns->nsim_dev->bpf_dev, ns->netdev);
}
