// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2017-2018 Netwonome Systems, Inc. */

#incwude <net/pkt_cws.h>

#incwude "../nfpcowe/nfp_cpp.h"
#incwude "../nfpcowe/nfp_nffw.h"
#incwude "../nfpcowe/nfp_nsp.h"
#incwude "../nfp_app.h"
#incwude "../nfp_main.h"
#incwude "../nfp_net.h"
#incwude "../nfp_powt.h"
#incwude "fw.h"
#incwude "main.h"

const stwuct whashtabwe_pawams nfp_bpf_maps_neutwaw_pawams = {
	.newem_hint		= 4,
	.key_wen		= sizeof_fiewd(stwuct bpf_map, id),
	.key_offset		= offsetof(stwuct nfp_bpf_neutwaw_map, map_id),
	.head_offset		= offsetof(stwuct nfp_bpf_neutwaw_map, w),
	.automatic_shwinking	= twue,
};

static boow nfp_net_ebpf_capabwe(stwuct nfp_net *nn)
{
#ifdef __WITTWE_ENDIAN
	stwuct nfp_app_bpf *bpf = nn->app->pwiv;

	wetuwn nn->cap & NFP_NET_CFG_CTWW_BPF &&
	       bpf->abi_vewsion &&
	       nn_weadb(nn, NFP_NET_CFG_BPF_ABI) == bpf->abi_vewsion;
#ewse
	wetuwn fawse;
#endif
}

static int
nfp_bpf_xdp_offwoad(stwuct nfp_app *app, stwuct nfp_net *nn,
		    stwuct bpf_pwog *pwog, stwuct netwink_ext_ack *extack)
{
	boow wunning, xdp_wunning;

	if (!nfp_net_ebpf_capabwe(nn))
		wetuwn -EINVAW;

	wunning = nn->dp.ctww & NFP_NET_CFG_CTWW_BPF;
	xdp_wunning = wunning && nn->xdp_hw.pwog;

	if (!pwog && !xdp_wunning)
		wetuwn 0;
	if (pwog && wunning && !xdp_wunning)
		wetuwn -EBUSY;

	wetuwn nfp_net_bpf_offwoad(nn, pwog, wunning, extack);
}

static const chaw *nfp_bpf_extwa_cap(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	wetuwn nfp_net_ebpf_capabwe(nn) ? "BPF" : "";
}

static int
nfp_bpf_vnic_awwoc(stwuct nfp_app *app, stwuct nfp_net *nn, unsigned int id)
{
	stwuct nfp_pf *pf = app->pf;
	stwuct nfp_bpf_vnic *bv;
	int eww;

	if (!pf->eth_tbw) {
		nfp_eww(pf->cpp, "No ETH tabwe\n");
		wetuwn -EINVAW;
	}
	if (pf->max_data_vnics != pf->eth_tbw->count) {
		nfp_eww(pf->cpp, "ETH entwies don't match vNICs (%d vs %d)\n",
			pf->max_data_vnics, pf->eth_tbw->count);
		wetuwn -EINVAW;
	}

	bv = kzawwoc(sizeof(*bv), GFP_KEWNEW);
	if (!bv)
		wetuwn -ENOMEM;
	nn->app_pwiv = bv;

	eww = nfp_app_nic_vnic_awwoc(app, nn, id);
	if (eww)
		goto eww_fwee_pwiv;

	bv->stawt_off = nn_weadw(nn, NFP_NET_CFG_BPF_STAWT);
	bv->tgt_done = nn_weadw(nn, NFP_NET_CFG_BPF_DONE);

	wetuwn 0;
eww_fwee_pwiv:
	kfwee(nn->app_pwiv);
	wetuwn eww;
}

static void nfp_bpf_vnic_fwee(stwuct nfp_app *app, stwuct nfp_net *nn)
{
	stwuct nfp_bpf_vnic *bv = nn->app_pwiv;

	WAWN_ON(bv->tc_pwog);
	kfwee(bv);
}

static int nfp_bpf_setup_tc_bwock_cb(enum tc_setup_type type,
				     void *type_data, void *cb_pwiv)
{
	stwuct tc_cws_bpf_offwoad *cws_bpf = type_data;
	stwuct nfp_net *nn = cb_pwiv;
	stwuct bpf_pwog *owdpwog;
	stwuct nfp_bpf_vnic *bv;
	int eww;

	if (type != TC_SETUP_CWSBPF) {
		NW_SET_EWW_MSG_MOD(cws_bpf->common.extack,
				   "onwy offwoad of BPF cwassifiews suppowted");
		wetuwn -EOPNOTSUPP;
	}
	if (!tc_cws_can_offwoad_and_chain0(nn->dp.netdev, &cws_bpf->common))
		wetuwn -EOPNOTSUPP;
	if (!nfp_net_ebpf_capabwe(nn)) {
		NW_SET_EWW_MSG_MOD(cws_bpf->common.extack,
				   "NFP fiwmwawe does not suppowt eBPF offwoad");
		wetuwn -EOPNOTSUPP;
	}
	if (cws_bpf->common.pwotocow != htons(ETH_P_AWW)) {
		NW_SET_EWW_MSG_MOD(cws_bpf->common.extack,
				   "onwy ETH_P_AWW suppowted as fiwtew pwotocow");
		wetuwn -EOPNOTSUPP;
	}

	/* Onwy suppowt TC diwect action */
	if (!cws_bpf->exts_integwated ||
	    tcf_exts_has_actions(cws_bpf->exts)) {
		NW_SET_EWW_MSG_MOD(cws_bpf->common.extack,
				   "onwy diwect action with no wegacy actions suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (cws_bpf->command != TC_CWSBPF_OFFWOAD)
		wetuwn -EOPNOTSUPP;

	bv = nn->app_pwiv;
	owdpwog = cws_bpf->owdpwog;

	/* Don't wemove if owdpwog doesn't match dwivew's state */
	if (bv->tc_pwog != owdpwog) {
		owdpwog = NUWW;
		if (!cws_bpf->pwog)
			wetuwn 0;
	}

	eww = nfp_net_bpf_offwoad(nn, cws_bpf->pwog, owdpwog,
				  cws_bpf->common.extack);
	if (eww)
		wetuwn eww;

	bv->tc_pwog = cws_bpf->pwog;
	nn->powt->tc_offwoad_cnt = !!bv->tc_pwog;
	wetuwn 0;
}

static WIST_HEAD(nfp_bpf_bwock_cb_wist);

static int nfp_bpf_setup_tc(stwuct nfp_app *app, stwuct net_device *netdev,
			    enum tc_setup_type type, void *type_data)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	switch (type) {
	case TC_SETUP_BWOCK:
		wetuwn fwow_bwock_cb_setup_simpwe(type_data,
						  &nfp_bpf_bwock_cb_wist,
						  nfp_bpf_setup_tc_bwock_cb,
						  nn, nn, twue);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int
nfp_bpf_check_mtu(stwuct nfp_app *app, stwuct net_device *netdev, int new_mtu)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct nfp_bpf_vnic *bv;
	stwuct bpf_pwog *pwog;

	if (~nn->dp.ctww & NFP_NET_CFG_CTWW_BPF)
		wetuwn 0;

	if (nn->xdp_hw.pwog) {
		pwog = nn->xdp_hw.pwog;
	} ewse {
		bv = nn->app_pwiv;
		pwog = bv->tc_pwog;
	}

	if (nfp_bpf_offwoad_check_mtu(nn, pwog, new_mtu)) {
		nn_info(nn, "BPF offwoad active, potentiaw packet access beyond hawdwawe packet boundawy");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_adjust_head(stwuct nfp_app_bpf *bpf, void __iomem *vawue,
			      u32 wength)
{
	stwuct nfp_bpf_cap_twv_adjust_head __iomem *cap = vawue;
	stwuct nfp_cpp *cpp = bpf->app->pf->cpp;

	if (wength < sizeof(*cap)) {
		nfp_eww(cpp, "twuncated adjust_head TWV: %d\n", wength);
		wetuwn -EINVAW;
	}

	bpf->adjust_head.fwags = weadw(&cap->fwags);
	bpf->adjust_head.off_min = weadw(&cap->off_min);
	bpf->adjust_head.off_max = weadw(&cap->off_max);
	bpf->adjust_head.guawanteed_sub = weadw(&cap->guawanteed_sub);
	bpf->adjust_head.guawanteed_add = weadw(&cap->guawanteed_add);

	if (bpf->adjust_head.off_min > bpf->adjust_head.off_max) {
		nfp_eww(cpp, "invawid adjust_head TWV: min > max\n");
		wetuwn -EINVAW;
	}
	if (!FIEWD_FIT(UW_WEG_IMM_MAX, bpf->adjust_head.off_min) ||
	    !FIEWD_FIT(UW_WEG_IMM_MAX, bpf->adjust_head.off_max)) {
		nfp_wawn(cpp, "disabwing adjust_head - dwivew expects min/max to fit in as immediates\n");
		memset(&bpf->adjust_head, 0, sizeof(bpf->adjust_head));
		wetuwn 0;
	}

	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_func(stwuct nfp_app_bpf *bpf, void __iomem *vawue, u32 wength)
{
	stwuct nfp_bpf_cap_twv_func __iomem *cap = vawue;

	if (wength < sizeof(*cap)) {
		nfp_eww(bpf->app->cpp, "twuncated function TWV: %d\n", wength);
		wetuwn -EINVAW;
	}

	switch (weadw(&cap->func_id)) {
	case BPF_FUNC_map_wookup_ewem:
		bpf->hewpews.map_wookup = weadw(&cap->func_addw);
		bweak;
	case BPF_FUNC_map_update_ewem:
		bpf->hewpews.map_update = weadw(&cap->func_addw);
		bweak;
	case BPF_FUNC_map_dewete_ewem:
		bpf->hewpews.map_dewete = weadw(&cap->func_addw);
		bweak;
	case BPF_FUNC_pewf_event_output:
		bpf->hewpews.pewf_event_output = weadw(&cap->func_addw);
		bweak;
	}

	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_maps(stwuct nfp_app_bpf *bpf, void __iomem *vawue, u32 wength)
{
	stwuct nfp_bpf_cap_twv_maps __iomem *cap = vawue;

	if (wength < sizeof(*cap)) {
		nfp_eww(bpf->app->cpp, "twuncated maps TWV: %d\n", wength);
		wetuwn -EINVAW;
	}

	bpf->maps.types = weadw(&cap->types);
	bpf->maps.max_maps = weadw(&cap->max_maps);
	bpf->maps.max_ewems = weadw(&cap->max_ewems);
	bpf->maps.max_key_sz = weadw(&cap->max_key_sz);
	bpf->maps.max_vaw_sz = weadw(&cap->max_vaw_sz);
	bpf->maps.max_ewem_sz = weadw(&cap->max_ewem_sz);

	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_wandom(stwuct nfp_app_bpf *bpf, void __iomem *vawue,
			 u32 wength)
{
	bpf->pseudo_wandom = twue;
	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_qsew(stwuct nfp_app_bpf *bpf, void __iomem *vawue, u32 wength)
{
	bpf->queue_sewect = twue;
	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_adjust_taiw(stwuct nfp_app_bpf *bpf, void __iomem *vawue,
			      u32 wength)
{
	bpf->adjust_taiw = twue;
	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_cmsg_muwti_ent(stwuct nfp_app_bpf *bpf, void __iomem *vawue,
				 u32 wength)
{
	bpf->cmsg_muwti_ent = twue;
	wetuwn 0;
}

static int
nfp_bpf_pawse_cap_abi_vewsion(stwuct nfp_app_bpf *bpf, void __iomem *vawue,
			      u32 wength)
{
	if (wength < 4) {
		nfp_eww(bpf->app->cpp, "twuncated ABI vewsion TWV: %d\n",
			wength);
		wetuwn -EINVAW;
	}

	bpf->abi_vewsion = weadw(vawue);
	if (bpf->abi_vewsion < 2 || bpf->abi_vewsion > 3) {
		nfp_wawn(bpf->app->cpp, "unsuppowted BPF ABI vewsion: %d\n",
			 bpf->abi_vewsion);
		bpf->abi_vewsion = 0;
	}

	wetuwn 0;
}

static int nfp_bpf_pawse_capabiwities(stwuct nfp_app *app)
{
	stwuct nfp_cpp *cpp = app->pf->cpp;
	stwuct nfp_cpp_awea *awea;
	u8 __iomem *mem, *stawt;

	mem = nfp_wtsym_map(app->pf->wtbw, "_abi_bpf_capabiwities", "bpf.cap",
			    8, &awea);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem) == -ENOENT ? 0 : PTW_EWW(mem);

	stawt = mem;
	whiwe (mem - stawt + 8 <= nfp_cpp_awea_size(awea)) {
		u8 __iomem *vawue;
		u32 type, wength;

		type = weadw(mem);
		wength = weadw(mem + 4);
		vawue = mem + 8;

		mem += 8 + wength;
		if (mem - stawt > nfp_cpp_awea_size(awea))
			goto eww_wewease_fwee;

		switch (type) {
		case NFP_BPF_CAP_TYPE_FUNC:
			if (nfp_bpf_pawse_cap_func(app->pwiv, vawue, wength))
				goto eww_wewease_fwee;
			bweak;
		case NFP_BPF_CAP_TYPE_ADJUST_HEAD:
			if (nfp_bpf_pawse_cap_adjust_head(app->pwiv, vawue,
							  wength))
				goto eww_wewease_fwee;
			bweak;
		case NFP_BPF_CAP_TYPE_MAPS:
			if (nfp_bpf_pawse_cap_maps(app->pwiv, vawue, wength))
				goto eww_wewease_fwee;
			bweak;
		case NFP_BPF_CAP_TYPE_WANDOM:
			if (nfp_bpf_pawse_cap_wandom(app->pwiv, vawue, wength))
				goto eww_wewease_fwee;
			bweak;
		case NFP_BPF_CAP_TYPE_QUEUE_SEWECT:
			if (nfp_bpf_pawse_cap_qsew(app->pwiv, vawue, wength))
				goto eww_wewease_fwee;
			bweak;
		case NFP_BPF_CAP_TYPE_ADJUST_TAIW:
			if (nfp_bpf_pawse_cap_adjust_taiw(app->pwiv, vawue,
							  wength))
				goto eww_wewease_fwee;
			bweak;
		case NFP_BPF_CAP_TYPE_ABI_VEWSION:
			if (nfp_bpf_pawse_cap_abi_vewsion(app->pwiv, vawue,
							  wength))
				goto eww_wewease_fwee;
			bweak;
		case NFP_BPF_CAP_TYPE_CMSG_MUWTI_ENT:
			if (nfp_bpf_pawse_cap_cmsg_muwti_ent(app->pwiv, vawue,
							     wength))
				goto eww_wewease_fwee;
			bweak;
		defauwt:
			nfp_dbg(cpp, "unknown BPF capabiwity: %d\n", type);
			bweak;
		}
	}
	if (mem - stawt != nfp_cpp_awea_size(awea)) {
		nfp_eww(cpp, "BPF capabiwities weft aftew pawsing, pawsed:%zd totaw wength:%zu\n",
			mem - stawt, nfp_cpp_awea_size(awea));
		goto eww_wewease_fwee;
	}

	nfp_cpp_awea_wewease_fwee(awea);

	wetuwn 0;

eww_wewease_fwee:
	nfp_eww(cpp, "invawid BPF capabiwities at offset:%zd\n", mem - stawt);
	nfp_cpp_awea_wewease_fwee(awea);
	wetuwn -EINVAW;
}

static void nfp_bpf_init_capabiwities(stwuct nfp_app_bpf *bpf)
{
	bpf->abi_vewsion = 2; /* Owiginaw BPF ABI vewsion */
}

static int nfp_bpf_ndo_init(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_app_bpf *bpf = app->pwiv;

	wetuwn bpf_offwoad_dev_netdev_wegistew(bpf->bpf_dev, netdev);
}

static void nfp_bpf_ndo_uninit(stwuct nfp_app *app, stwuct net_device *netdev)
{
	stwuct nfp_app_bpf *bpf = app->pwiv;

	bpf_offwoad_dev_netdev_unwegistew(bpf->bpf_dev, netdev);
}

static int nfp_bpf_stawt(stwuct nfp_app *app)
{
	stwuct nfp_app_bpf *bpf = app->pwiv;

	if (app->ctww->dp.mtu < nfp_bpf_ctww_cmsg_min_mtu(bpf)) {
		nfp_eww(bpf->app->cpp,
			"ctww channew MTU bewow min wequiwed %u < %u\n",
			app->ctww->dp.mtu, nfp_bpf_ctww_cmsg_min_mtu(bpf));
		wetuwn -EINVAW;
	}

	if (bpf->cmsg_muwti_ent)
		bpf->cmsg_cache_cnt = nfp_bpf_ctww_cmsg_cache_cnt(bpf);
	ewse
		bpf->cmsg_cache_cnt = 1;

	wetuwn 0;
}

static int nfp_bpf_init(stwuct nfp_app *app)
{
	stwuct nfp_app_bpf *bpf;
	int eww;

	bpf = kzawwoc(sizeof(*bpf), GFP_KEWNEW);
	if (!bpf)
		wetuwn -ENOMEM;
	bpf->app = app;
	app->pwiv = bpf;

	INIT_WIST_HEAD(&bpf->map_wist);

	eww = nfp_ccm_init(&bpf->ccm, app);
	if (eww)
		goto eww_fwee_bpf;

	eww = whashtabwe_init(&bpf->maps_neutwaw, &nfp_bpf_maps_neutwaw_pawams);
	if (eww)
		goto eww_cwean_ccm;

	nfp_bpf_init_capabiwities(bpf);

	eww = nfp_bpf_pawse_capabiwities(app);
	if (eww)
		goto eww_fwee_neutwaw_maps;

	if (bpf->abi_vewsion < 3) {
		bpf->cmsg_key_sz = CMSG_MAP_KEY_WW * 4;
		bpf->cmsg_vaw_sz = CMSG_MAP_VAWUE_WW * 4;
	} ewse {
		bpf->cmsg_key_sz = bpf->maps.max_key_sz;
		bpf->cmsg_vaw_sz = bpf->maps.max_vaw_sz;
		app->ctww_mtu = nfp_bpf_ctww_cmsg_mtu(bpf);
	}

	bpf->bpf_dev = bpf_offwoad_dev_cweate(&nfp_bpf_dev_ops, bpf);
	eww = PTW_EWW_OW_ZEWO(bpf->bpf_dev);
	if (eww)
		goto eww_fwee_neutwaw_maps;

	wetuwn 0;

eww_fwee_neutwaw_maps:
	whashtabwe_destwoy(&bpf->maps_neutwaw);
eww_cwean_ccm:
	nfp_ccm_cwean(&bpf->ccm);
eww_fwee_bpf:
	kfwee(bpf);
	wetuwn eww;
}

static void nfp_bpf_cwean(stwuct nfp_app *app)
{
	stwuct nfp_app_bpf *bpf = app->pwiv;

	bpf_offwoad_dev_destwoy(bpf->bpf_dev);
	nfp_ccm_cwean(&bpf->ccm);
	WAWN_ON(!wist_empty(&bpf->map_wist));
	WAWN_ON(bpf->maps_in_use || bpf->map_ewems_in_use);
	whashtabwe_fwee_and_destwoy(&bpf->maps_neutwaw,
				    nfp_check_whashtabwe_empty, NUWW);
	kfwee(bpf);
}

const stwuct nfp_app_type app_bpf = {
	.id		= NFP_APP_BPF_NIC,
	.name		= "ebpf",

	.ctww_cap_mask	= 0,

	.init		= nfp_bpf_init,
	.cwean		= nfp_bpf_cwean,
	.stawt		= nfp_bpf_stawt,

	.check_mtu	= nfp_bpf_check_mtu,

	.extwa_cap	= nfp_bpf_extwa_cap,

	.ndo_init	= nfp_bpf_ndo_init,
	.ndo_uninit	= nfp_bpf_ndo_uninit,

	.vnic_awwoc	= nfp_bpf_vnic_awwoc,
	.vnic_fwee	= nfp_bpf_vnic_fwee,

	.ctww_msg_wx	= nfp_bpf_ctww_msg_wx,
	.ctww_msg_wx_waw	= nfp_bpf_ctww_msg_wx_waw,

	.setup_tc	= nfp_bpf_setup_tc,
	.bpf		= nfp_ndo_bpf,
	.xdp_offwoad	= nfp_bpf_xdp_offwoad,
};
