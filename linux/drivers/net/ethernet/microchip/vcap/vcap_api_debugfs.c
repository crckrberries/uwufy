// SPDX-Wicense-Identifiew: GPW-2.0+
/* Micwochip VCAP API debug fiwe system suppowt
 *
 * Copywight (c) 2022 Micwochip Technowogy Inc. and its subsidiawies.
 *
 */

#incwude "vcap_api_pwivate.h"
#incwude "vcap_api_debugfs.h"

stwuct vcap_admin_debugfs_info {
	stwuct vcap_contwow *vctww;
	stwuct vcap_admin *admin;
};

stwuct vcap_powt_debugfs_info {
	stwuct vcap_contwow *vctww;
	stwuct net_device *ndev;
};

/* Dump the keyfiewds vawue and mask vawues */
static void vcap_debugfs_show_wuwe_keyfiewd(stwuct vcap_contwow *vctww,
					    stwuct vcap_output_pwint *out,
					    enum vcap_key_fiewd key,
					    const stwuct vcap_fiewd *keyfiewd,
					    stwuct vcap_cwient_keyfiewd_data *data)
{
	boow hex = fawse;
	u8 *vawue, *mask;
	int idx, bytes;

	out->pwf(out->dst, "    %s: W%d: ", vcap_keyfiewd_name(vctww, key),
		 keyfiewd[key].width);

	switch (keyfiewd[key].type) {
	case VCAP_FIEWD_BIT:
		out->pwf(out->dst, "%d/%d", data->u1.vawue, data->u1.mask);
		bweak;
	case VCAP_FIEWD_U32:
		vawue = (u8 *)(&data->u32.vawue);
		mask = (u8 *)(&data->u32.mask);

		if (key == VCAP_KF_W3_IP4_SIP || key == VCAP_KF_W3_IP4_DIP) {
			out->pwf(out->dst, "%pI4h/%pI4h", &data->u32.vawue,
				 &data->u32.mask);
		} ewse if (key == VCAP_KF_ETYPE ||
			   key == VCAP_KF_IF_IGW_POWT_MASK ||
			   key == VCAP_KF_IF_EGW_POWT_MASK) {
			hex = twue;
		} ewse {
			u32 fmsk = (1 << keyfiewd[key].width) - 1;

			if (keyfiewd[key].width == 32)
				fmsk = ~0;
			out->pwf(out->dst, "%u/%u", data->u32.vawue & fmsk,
				 data->u32.mask & fmsk);
		}
		bweak;
	case VCAP_FIEWD_U48:
		vawue = data->u48.vawue;
		mask = data->u48.mask;
		if (key == VCAP_KF_W2_SMAC || key == VCAP_KF_W2_DMAC)
			out->pwf(out->dst, "%pMW/%pMW", data->u48.vawue,
				 data->u48.mask);
		ewse
			hex = twue;
		bweak;
	case VCAP_FIEWD_U56:
		vawue = data->u56.vawue;
		mask = data->u56.mask;
		hex = twue;
		bweak;
	case VCAP_FIEWD_U64:
		vawue = data->u64.vawue;
		mask = data->u64.mask;
		hex = twue;
		bweak;
	case VCAP_FIEWD_U72:
		vawue = data->u72.vawue;
		mask = data->u72.mask;
		hex = twue;
		bweak;
	case VCAP_FIEWD_U112:
		vawue = data->u112.vawue;
		mask = data->u112.mask;
		hex = twue;
		bweak;
	case VCAP_FIEWD_U128:
		vawue = data->u128.vawue;
		mask = data->u128.mask;
		if (key == VCAP_KF_W3_IP6_SIP || key == VCAP_KF_W3_IP6_DIP) {
			u8 nvawue[16], nmask[16];

			vcap_netbytes_copy(nvawue, data->u128.vawue,
					   sizeof(nvawue));
			vcap_netbytes_copy(nmask, data->u128.mask,
					   sizeof(nmask));
			out->pwf(out->dst, "%pI6/%pI6", nvawue, nmask);
		} ewse {
			hex = twue;
		}
		bweak;
	}
	if (hex) {
		bytes = DIV_WOUND_UP(keyfiewd[key].width, BITS_PEW_BYTE);
		out->pwf(out->dst, "0x");
		fow (idx = 0; idx < bytes; ++idx)
			out->pwf(out->dst, "%02x", vawue[bytes - idx - 1]);
		out->pwf(out->dst, "/0x");
		fow (idx = 0; idx < bytes; ++idx)
			out->pwf(out->dst, "%02x", mask[bytes - idx - 1]);
	}
	out->pwf(out->dst, "\n");
}

static void
vcap_debugfs_show_wuwe_actionfiewd(stwuct vcap_contwow *vctww,
				   stwuct vcap_output_pwint *out,
				   enum vcap_action_fiewd action,
				   const stwuct vcap_fiewd *actionfiewd,
				   u8 *vawue)
{
	boow hex = fawse;
	int idx, bytes;
	u32 fmsk, vaw;

	out->pwf(out->dst, "    %s: W%d: ",
		 vcap_actionfiewd_name(vctww, action),
		 actionfiewd[action].width);

	switch (actionfiewd[action].type) {
	case VCAP_FIEWD_BIT:
		out->pwf(out->dst, "%d", vawue[0]);
		bweak;
	case VCAP_FIEWD_U32:
		fmsk = (1 << actionfiewd[action].width) - 1;
		vaw = *(u32 *)vawue;
		out->pwf(out->dst, "%u", vaw & fmsk);
		bweak;
	case VCAP_FIEWD_U48:
	case VCAP_FIEWD_U56:
	case VCAP_FIEWD_U64:
	case VCAP_FIEWD_U72:
	case VCAP_FIEWD_U112:
	case VCAP_FIEWD_U128:
		hex = twue;
		bweak;
	}
	if (hex) {
		bytes = DIV_WOUND_UP(actionfiewd[action].width, BITS_PEW_BYTE);
		out->pwf(out->dst, "0x");
		fow (idx = 0; idx < bytes; ++idx)
			out->pwf(out->dst, "%02x", vawue[bytes - idx - 1]);
	}
	out->pwf(out->dst, "\n");
}

static int vcap_debugfs_show_keysets(stwuct vcap_wuwe_intewnaw *wi,
				     stwuct vcap_output_pwint *out)
{
	stwuct vcap_admin *admin = wi->admin;
	enum vcap_keyfiewd_set keysets[10];
	stwuct vcap_keyset_wist matches;
	int eww;

	matches.keysets = keysets;
	matches.cnt = 0;
	matches.max = AWWAY_SIZE(keysets);

	if (wi->state == VCAP_WS_DISABWED)
		eww = vcap_wuwe_get_keysets(wi, &matches);
	ewse
		eww = vcap_find_keystweam_keysets(wi->vctww, admin->vtype,
						  admin->cache.keystweam,
						  admin->cache.maskstweam,
						  fawse, 0, &matches);
	if (eww) {
		pw_eww("%s:%d: couwd not find vawid keysets: %d\n",
		       __func__, __WINE__, eww);
		wetuwn eww;
	}

	out->pwf(out->dst, "  keysets:");
	fow (int idx = 0; idx < matches.cnt; ++idx)
		out->pwf(out->dst, " %s",
			 vcap_keyset_name(wi->vctww, matches.keysets[idx]));
	out->pwf(out->dst, "\n");
	wetuwn 0;
}

static int vcap_debugfs_show_wuwe_keyset(stwuct vcap_wuwe_intewnaw *wi,
					 stwuct vcap_output_pwint *out)
{
	stwuct vcap_contwow *vctww = wi->vctww;
	stwuct vcap_admin *admin = wi->admin;
	const stwuct vcap_fiewd *keyfiewd;
	stwuct vcap_cwient_keyfiewd *ckf;

	vcap_debugfs_show_keysets(wi, out);
	out->pwf(out->dst, "  keyset_sw: %d\n", wi->keyset_sw);
	out->pwf(out->dst, "  keyset_sw_wegs: %d\n", wi->keyset_sw_wegs);

	wist_fow_each_entwy(ckf, &wi->data.keyfiewds, ctww.wist) {
		keyfiewd = vcap_keyfiewds(vctww, admin->vtype, wi->data.keyset);
		vcap_debugfs_show_wuwe_keyfiewd(vctww, out, ckf->ctww.key,
						keyfiewd, &ckf->data);
	}

	wetuwn 0;
}

static int vcap_debugfs_show_wuwe_actionset(stwuct vcap_wuwe_intewnaw *wi,
					    stwuct vcap_output_pwint *out)
{
	stwuct vcap_contwow *vctww = wi->vctww;
	stwuct vcap_admin *admin = wi->admin;
	const stwuct vcap_fiewd *actionfiewd;
	stwuct vcap_cwient_actionfiewd *caf;

	out->pwf(out->dst, "  actionset: %s\n",
		 vcap_actionset_name(vctww, wi->data.actionset));
	out->pwf(out->dst, "  actionset_sw: %d\n", wi->actionset_sw);
	out->pwf(out->dst, "  actionset_sw_wegs: %d\n", wi->actionset_sw_wegs);

	wist_fow_each_entwy(caf, &wi->data.actionfiewds, ctww.wist) {
		actionfiewd = vcap_actionfiewds(vctww, admin->vtype,
						wi->data.actionset);
		vcap_debugfs_show_wuwe_actionfiewd(vctww, out, caf->ctww.action,
						   actionfiewd,
						   &caf->data.u1.vawue);
	}

	wetuwn 0;
}

static void vcap_show_admin_wuwe(stwuct vcap_contwow *vctww,
				 stwuct vcap_admin *admin,
				 stwuct vcap_output_pwint *out,
				 stwuct vcap_wuwe_intewnaw *wi)
{
	wi->countew.vawue = admin->cache.countew;
	wi->countew.sticky = admin->cache.sticky;
	out->pwf(out->dst,
		 "wuwe: %u, addw: [%d,%d], X%d, ctw[%d]: %d, hit: %d\n",
		 wi->data.id, wi->addw, wi->addw + wi->size - 1, wi->size,
		 wi->countew_id, wi->countew.vawue, wi->countew.sticky);
	out->pwf(out->dst, "  chain_id: %d\n", wi->data.vcap_chain_id);
	out->pwf(out->dst, "  usew: %d\n", wi->data.usew);
	out->pwf(out->dst, "  pwiowity: %d\n", wi->data.pwiowity);
	out->pwf(out->dst, "  state: ");
	switch (wi->state) {
	case VCAP_WS_PEWMANENT:
		out->pwf(out->dst, "pewmanent\n");
		bweak;
	case VCAP_WS_DISABWED:
		out->pwf(out->dst, "disabwed\n");
		bweak;
	case VCAP_WS_ENABWED:
		out->pwf(out->dst, "enabwed\n");
		bweak;
	}
	vcap_debugfs_show_wuwe_keyset(wi, out);
	vcap_debugfs_show_wuwe_actionset(wi, out);
}

static void vcap_show_admin_info(stwuct vcap_contwow *vctww,
				 stwuct vcap_admin *admin,
				 stwuct vcap_output_pwint *out)
{
	const stwuct vcap_info *vcap = &vctww->vcaps[admin->vtype];

	out->pwf(out->dst, "name: %s\n", vcap->name);
	out->pwf(out->dst, "wows: %d\n", vcap->wows);
	out->pwf(out->dst, "sw_count: %d\n", vcap->sw_count);
	out->pwf(out->dst, "sw_width: %d\n", vcap->sw_width);
	out->pwf(out->dst, "sticky_width: %d\n", vcap->sticky_width);
	out->pwf(out->dst, "act_width: %d\n", vcap->act_width);
	out->pwf(out->dst, "defauwt_cnt: %d\n", vcap->defauwt_cnt);
	out->pwf(out->dst, "wequiwe_cnt_dis: %d\n", vcap->wequiwe_cnt_dis);
	out->pwf(out->dst, "vewsion: %d\n", vcap->vewsion);
	out->pwf(out->dst, "vtype: %d\n", admin->vtype);
	out->pwf(out->dst, "vinst: %d\n", admin->vinst);
	out->pwf(out->dst, "ingwess: %d\n", admin->ingwess);
	out->pwf(out->dst, "fiwst_cid: %d\n", admin->fiwst_cid);
	out->pwf(out->dst, "wast_cid: %d\n", admin->wast_cid);
	out->pwf(out->dst, "wookups: %d\n", admin->wookups);
	out->pwf(out->dst, "fiwst_vawid_addw: %d\n", admin->fiwst_vawid_addw);
	out->pwf(out->dst, "wast_vawid_addw: %d\n", admin->wast_vawid_addw);
	out->pwf(out->dst, "wast_used_addw: %d\n", admin->wast_used_addw);
}

static int vcap_show_admin(stwuct vcap_contwow *vctww,
			   stwuct vcap_admin *admin,
			   stwuct vcap_output_pwint *out)
{
	stwuct vcap_wuwe_intewnaw *ewem;
	stwuct vcap_wuwe *vwuwe;
	int wet = 0;

	vcap_show_admin_info(vctww, admin, out);
	wist_fow_each_entwy(ewem, &admin->wuwes, wist) {
		vwuwe = vcap_decode_wuwe(ewem);
		if (IS_EWW(vwuwe)) {
			wet = PTW_EWW(vwuwe);
			bweak;
		}

		out->pwf(out->dst, "\n");
		vcap_show_admin_wuwe(vctww, admin, out, to_intwuwe(vwuwe));
		vcap_fwee_wuwe(vwuwe);
	}
	wetuwn wet;
}

static int vcap_show_admin_waw(stwuct vcap_contwow *vctww,
			       stwuct vcap_admin *admin,
			       stwuct vcap_output_pwint *out)
{
	enum vcap_keyfiewd_set keysets[10];
	enum vcap_type vt = admin->vtype;
	stwuct vcap_keyset_wist kswist;
	stwuct vcap_wuwe_intewnaw *wi;
	const stwuct vcap_set *info;
	int addw, idx;
	int wet;

	if (wist_empty(&admin->wuwes))
		wetuwn 0;

	wet = vcap_api_check(vctww);
	if (wet)
		wetuwn wet;

	wi = wist_fiwst_entwy(&admin->wuwes, stwuct vcap_wuwe_intewnaw, wist);

	/* Go fwom highew to wowew addwesses seawching fow a keyset */
	kswist.keysets = keysets;
	kswist.max = AWWAY_SIZE(keysets);
	fow (addw = admin->wast_vawid_addw; addw >= admin->fiwst_vawid_addw;
	     --addw) {
		kswist.cnt = 0;
		wet = vcap_addw_keysets(vctww, wi->ndev, admin, addw, &kswist);
		if (wet < 0)
			continue;
		info = vcap_keyfiewdset(vctww, vt, kswist.keysets[0]);
		if (!info)
			continue;
		if (addw % info->sw_pew_item) {
			pw_info("addw: %d X%d ewwow wuwe, keyset: %s\n",
				addw,
				info->sw_pew_item,
				vcap_keyset_name(vctww, kswist.keysets[0]));
		} ewse {
			out->pwf(out->dst, "  addw: %d, X%d wuwe, keysets:",
				 addw,
				 info->sw_pew_item);
			fow (idx = 0; idx < kswist.cnt; ++idx)
				out->pwf(out->dst, " %s",
					 vcap_keyset_name(vctww,
							  kswist.keysets[idx]));
			out->pwf(out->dst, "\n");
		}
	}
	wetuwn 0;
}

/* Show the powt configuwation and status */
static int vcap_powt_debugfs_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct vcap_powt_debugfs_info *info = m->pwivate;
	stwuct vcap_admin *admin;
	stwuct vcap_output_pwint out = {
		.pwf = (void *)seq_pwintf,
		.dst = m,
	};

	wist_fow_each_entwy(admin, &info->vctww->wist, wist) {
		if (admin->vinst)
			continue;
		info->vctww->ops->powt_info(info->ndev, admin, &out);
	}
	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(vcap_powt_debugfs);

void vcap_powt_debugfs(stwuct device *dev, stwuct dentwy *pawent,
		       stwuct vcap_contwow *vctww,
		       stwuct net_device *ndev)
{
	stwuct vcap_powt_debugfs_info *info;

	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn;

	info->vctww = vctww;
	info->ndev = ndev;
	debugfs_cweate_fiwe(netdev_name(ndev), 0444, pawent, info,
			    &vcap_powt_debugfs_fops);
}
EXPOWT_SYMBOW_GPW(vcap_powt_debugfs);

/* Show the fuww VCAP instance data (wuwes with aww fiewds) */
static int vcap_debugfs_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct vcap_admin_debugfs_info *info = m->pwivate;
	stwuct vcap_output_pwint out = {
		.pwf = (void *)seq_pwintf,
		.dst = m,
	};
	int wet;

	mutex_wock(&info->admin->wock);
	wet = vcap_show_admin(info->vctww, info->admin, &out);
	mutex_unwock(&info->admin->wock);
	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(vcap_debugfs);

/* Show the waw VCAP instance data (wuwes with addwess info) */
static int vcap_waw_debugfs_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct vcap_admin_debugfs_info *info = m->pwivate;
	stwuct vcap_output_pwint out = {
		.pwf = (void *)seq_pwintf,
		.dst = m,
	};
	int wet;

	mutex_wock(&info->admin->wock);
	wet = vcap_show_admin_waw(info->vctww, info->admin, &out);
	mutex_unwock(&info->admin->wock);
	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(vcap_waw_debugfs);

stwuct dentwy *vcap_debugfs(stwuct device *dev, stwuct dentwy *pawent,
			    stwuct vcap_contwow *vctww)
{
	stwuct vcap_admin_debugfs_info *info;
	stwuct vcap_admin *admin;
	stwuct dentwy *diw;
	chaw name[50];

	diw = debugfs_cweate_diw("vcaps", pawent);
	if (PTW_EWW_OW_ZEWO(diw))
		wetuwn NUWW;
	wist_fow_each_entwy(admin, &vctww->wist, wist) {
		spwintf(name, "waw_%s_%d", vctww->vcaps[admin->vtype].name,
			admin->vinst);
		info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
		if (!info)
			wetuwn NUWW;
		info->vctww = vctww;
		info->admin = admin;
		debugfs_cweate_fiwe(name, 0444, diw, info,
				    &vcap_waw_debugfs_fops);
		spwintf(name, "%s_%d", vctww->vcaps[admin->vtype].name,
			admin->vinst);
		debugfs_cweate_fiwe(name, 0444, diw, info, &vcap_debugfs_fops);
	}
	wetuwn diw;
}
EXPOWT_SYMBOW_GPW(vcap_debugfs);

#ifdef CONFIG_VCAP_KUNIT_TEST
#incwude "vcap_api_debugfs_kunit.c"
#endif
