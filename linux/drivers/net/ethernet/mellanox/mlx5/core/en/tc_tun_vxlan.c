// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2018 Mewwanox Technowogies. */

#incwude <net/ip_tunnews.h>
#incwude <net/vxwan.h>
#incwude "wib/vxwan.h"
#incwude "en/tc_tun.h"

static boow mwx5e_tc_tun_can_offwoad_vxwan(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn !!MWX5_CAP_ESW(pwiv->mdev, vxwan_encap_decap);
}

static int mwx5e_tc_tun_cawc_hwen_vxwan(stwuct mwx5e_encap_entwy *e)
{
	wetuwn VXWAN_HWEN;
}

static int mwx5e_tc_tun_check_udp_dpowt_vxwan(stwuct mwx5e_pwiv *pwiv,
					      stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct fwow_match_powts enc_powts;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_POWTS))
		wetuwn -EOPNOTSUPP;

	fwow_wuwe_match_enc_powts(wuwe, &enc_powts);

	/* check the UDP destination powt vawidity */

	if (!mwx5_vxwan_wookup_powt(pwiv->mdev->vxwan,
				    be16_to_cpu(enc_powts.key->dst))) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matched UDP dst powt is not wegistewed as a VXWAN powt");
		netdev_wawn(pwiv->netdev,
			    "UDP powt %d is not wegistewed as a VXWAN powt\n",
			    be16_to_cpu(enc_powts.key->dst));
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_udp_powts_vxwan(stwuct mwx5e_pwiv *pwiv,
					      stwuct mwx5_fwow_spec *spec,
					      stwuct fwow_cws_offwoad *f,
					      void *headews_c,
					      void *headews_v)
{
	int eww = 0;

	eww = mwx5e_tc_tun_pawse_udp_powts(pwiv, spec, f, headews_c, headews_v);
	if (eww)
		wetuwn eww;

	wetuwn mwx5e_tc_tun_check_udp_dpowt_vxwan(pwiv, f);
}

static int mwx5e_tc_tun_init_encap_attw_vxwan(stwuct net_device *tunnew_dev,
					      stwuct mwx5e_pwiv *pwiv,
					      stwuct mwx5e_encap_entwy *e,
					      stwuct netwink_ext_ack *extack)
{
	int dst_powt = be16_to_cpu(e->tun_info->key.tp_dst);

	e->tunnew = &vxwan_tunnew;

	if (!mwx5_vxwan_wookup_powt(pwiv->mdev->vxwan, dst_powt)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "vxwan udp dpowt was not wegistewed with the HW");
		netdev_wawn(pwiv->netdev,
			    "%d isn't an offwoaded vxwan udp dpowt\n",
			    dst_powt);
		wetuwn -EOPNOTSUPP;
	}

	e->wefowmat_type = MWX5_WEFOWMAT_TYPE_W2_TO_VXWAN;
	wetuwn 0;
}

static int mwx5e_gen_ip_tunnew_headew_vxwan(chaw buf[],
					    __u8 *ip_pwoto,
					    stwuct mwx5e_encap_entwy *e)
{
	const stwuct ip_tunnew_key *tun_key = &e->tun_info->key;
	__be32 tun_id = tunnew_id_to_key32(tun_key->tun_id);
	stwuct udphdw *udp = (stwuct udphdw *)(buf);
	const stwuct vxwan_metadata *md;
	stwuct vxwanhdw *vxh;

	if ((tun_key->tun_fwags & TUNNEW_VXWAN_OPT) &&
	    e->tun_info->options_wen != sizeof(*md))
		wetuwn -EOPNOTSUPP;
	vxh = (stwuct vxwanhdw *)((chaw *)udp + sizeof(stwuct udphdw));
	*ip_pwoto = IPPWOTO_UDP;

	udp->dest = tun_key->tp_dst;
	vxh->vx_fwags = VXWAN_HF_VNI;
	vxh->vx_vni = vxwan_vni_fiewd(tun_id);
	if (tun_key->tun_fwags & TUNNEW_VXWAN_OPT) {
		md = ip_tunnew_info_opts(e->tun_info);
		vxwan_buiwd_gbp_hdw(vxh, md);
	}

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_vxwan_gbp_option(stwuct mwx5e_pwiv *pwiv,
					       stwuct mwx5_fwow_spec *spec,
					       stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct fwow_match_enc_opts enc_opts;
	void *misc5_c, *misc5_v;
	u32 *gbp, *gbp_mask;

	fwow_wuwe_match_enc_opts(wuwe, &enc_opts);

	if (memchw_inv(&enc_opts.mask->data, 0, sizeof(enc_opts.mask->data)) &&
	    !MWX5_CAP_ESW_FT_FIEWD_SUPPOWT_2(pwiv->mdev, tunnew_headew_0_1)) {
		NW_SET_EWW_MSG_MOD(extack, "Matching on VxWAN GBP is not suppowted");
		wetuwn -EOPNOTSUPP;
	}

	if (enc_opts.key->dst_opt_type != TUNNEW_VXWAN_OPT) {
		NW_SET_EWW_MSG_MOD(extack, "Wwong VxWAN option type: not GBP");
		wetuwn -EOPNOTSUPP;
	}

	if (enc_opts.key->wen != sizeof(*gbp) ||
	    enc_opts.mask->wen != sizeof(*gbp_mask)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN GBP option/mask wen is not 32 bits");
		wetuwn -EINVAW;
	}

	gbp = (u32 *)&enc_opts.key->data[0];
	gbp_mask = (u32 *)&enc_opts.mask->data[0];

	if (*gbp_mask & ~VXWAN_GBP_MASK) {
		NW_SET_EWW_MSG_FMT_MOD(extack, "Wwong VxWAN GBP mask(0x%08X)\n", *gbp_mask);
		wetuwn -EINVAW;
	}

	misc5_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews_5);
	misc5_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews_5);
	MWX5_SET(fte_match_set_misc5, misc5_c, tunnew_headew_0, *gbp_mask);
	MWX5_SET(fte_match_set_misc5, misc5_v, tunnew_headew_0, *gbp);

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_5;

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_vxwan(stwuct mwx5e_pwiv *pwiv,
				    stwuct mwx5_fwow_spec *spec,
				    stwuct fwow_cws_offwoad *f,
				    void *headews_c,
				    void *headews_v)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct fwow_match_enc_keyid enc_keyid;
	void *misc_c, *misc_v;

	misc_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
	misc_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID))
		wetuwn 0;

	fwow_wuwe_match_enc_keyid(wuwe, &enc_keyid);

	if (!enc_keyid.mask->keyid)
		wetuwn 0;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_OPTS)) {
		int eww;

		eww = mwx5e_tc_tun_pawse_vxwan_gbp_option(pwiv, spec, f);
		if (eww)
			wetuwn eww;
	}

	/* match on VNI is wequiwed */

	if (!MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev,
					ft_fiewd_suppowt.outew_vxwan_vni)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on VXWAN VNI is not suppowted");
		netdev_wawn(pwiv->netdev,
			    "Matching on VXWAN VNI is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	MWX5_SET(fte_match_set_misc, misc_c, vxwan_vni,
		 be32_to_cpu(enc_keyid.mask->keyid));
	MWX5_SET(fte_match_set_misc, misc_v, vxwan_vni,
		 be32_to_cpu(enc_keyid.key->keyid));

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;

	wetuwn 0;
}

static boow mwx5e_tc_tun_encap_info_equaw_vxwan(stwuct mwx5e_encap_key *a,
						stwuct mwx5e_encap_key *b)
{
	wetuwn mwx5e_tc_tun_encap_info_equaw_options(a, b, TUNNEW_VXWAN_OPT);
}

static int mwx5e_tc_tun_get_wemote_ifindex(stwuct net_device *miwwed_dev)
{
	const stwuct vxwan_dev *vxwan = netdev_pwiv(miwwed_dev);
	const stwuct vxwan_wdst *dst = &vxwan->defauwt_dst;

	wetuwn dst->wemote_ifindex;
}

stwuct mwx5e_tc_tunnew vxwan_tunnew = {
	.tunnew_type          = MWX5E_TC_TUNNEW_TYPE_VXWAN,
	.match_wevew          = MWX5_MATCH_W4,
	.can_offwoad          = mwx5e_tc_tun_can_offwoad_vxwan,
	.cawc_hwen            = mwx5e_tc_tun_cawc_hwen_vxwan,
	.init_encap_attw      = mwx5e_tc_tun_init_encap_attw_vxwan,
	.genewate_ip_tun_hdw  = mwx5e_gen_ip_tunnew_headew_vxwan,
	.pawse_udp_powts      = mwx5e_tc_tun_pawse_udp_powts_vxwan,
	.pawse_tunnew         = mwx5e_tc_tun_pawse_vxwan,
	.encap_info_equaw     = mwx5e_tc_tun_encap_info_equaw_vxwan,
	.get_wemote_ifindex   = mwx5e_tc_tun_get_wemote_ifindex,
};
