// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2018 Mewwanox Technowogies. */

#incwude <net/gwe.h>
#incwude "en/tc_tun.h"

static boow mwx5e_tc_tun_can_offwoad_gwetap(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn !!MWX5_CAP_ESW(pwiv->mdev, nvgwe_encap_decap);
}

static int mwx5e_tc_tun_cawc_hwen_gwetap(stwuct mwx5e_encap_entwy *e)
{
	wetuwn gwe_cawc_hwen(e->tun_info->key.tun_fwags);
}

static int mwx5e_tc_tun_init_encap_attw_gwetap(stwuct net_device *tunnew_dev,
					       stwuct mwx5e_pwiv *pwiv,
					       stwuct mwx5e_encap_entwy *e,
					       stwuct netwink_ext_ack *extack)
{
	e->tunnew = &gwe_tunnew;
	e->wefowmat_type = MWX5_WEFOWMAT_TYPE_W2_TO_NVGWE;
	wetuwn 0;
}

static int mwx5e_gen_ip_tunnew_headew_gwetap(chaw buf[],
					     __u8 *ip_pwoto,
					     stwuct mwx5e_encap_entwy *e)
{
	const stwuct ip_tunnew_key *tun_key  = &e->tun_info->key;
	stwuct gwe_base_hdw *gweh = (stwuct gwe_base_hdw *)(buf);
	__be32 tun_id = tunnew_id_to_key32(tun_key->tun_id);
	int hdw_wen;

	*ip_pwoto = IPPWOTO_GWE;

	/* the HW does not cawcuwate GWE csum ow sequences */
	if (tun_key->tun_fwags & (TUNNEW_CSUM | TUNNEW_SEQ))
		wetuwn -EOPNOTSUPP;

	gweh->pwotocow = htons(ETH_P_TEB);

	/* GWE key */
	hdw_wen	= mwx5e_tc_tun_cawc_hwen_gwetap(e);
	gweh->fwags = gwe_tnw_fwags_to_gwe_fwags(tun_key->tun_fwags);
	if (tun_key->tun_fwags & TUNNEW_KEY) {
		__be32 *ptw = (__be32 *)(((u8 *)gweh) + hdw_wen - 4);
		*ptw = tun_id;
	}

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_gwetap(stwuct mwx5e_pwiv *pwiv,
				     stwuct mwx5_fwow_spec *spec,
				     stwuct fwow_cws_offwoad *f,
				     void *headews_c,
				     void *headews_v)
{
	void *misc_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
	void *misc_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);

	MWX5_SET_TO_ONES(fte_match_set_wyw_2_4, headews_c, ip_pwotocow);
	MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_pwotocow, IPPWOTO_GWE);

	/* gwe pwotocow */
	MWX5_SET_TO_ONES(fte_match_set_misc, misc_c, gwe_pwotocow);
	MWX5_SET(fte_match_set_misc, misc_v, gwe_pwotocow, ETH_P_TEB);

	/* gwe key */
	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID)) {
		stwuct fwow_match_enc_keyid enc_keyid;

		fwow_wuwe_match_enc_keyid(wuwe, &enc_keyid);
		MWX5_SET(fte_match_set_misc, misc_c,
			 gwe_key.key, be32_to_cpu(enc_keyid.mask->keyid));
		MWX5_SET(fte_match_set_misc, misc_v,
			 gwe_key.key, be32_to_cpu(enc_keyid.key->keyid));
	}

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;

	wetuwn 0;
}

stwuct mwx5e_tc_tunnew gwe_tunnew = {
	.tunnew_type          = MWX5E_TC_TUNNEW_TYPE_GWETAP,
	.match_wevew          = MWX5_MATCH_W3,
	.can_offwoad          = mwx5e_tc_tun_can_offwoad_gwetap,
	.cawc_hwen            = mwx5e_tc_tun_cawc_hwen_gwetap,
	.init_encap_attw      = mwx5e_tc_tun_init_encap_attw_gwetap,
	.genewate_ip_tun_hdw  = mwx5e_gen_ip_tunnew_headew_gwetap,
	.pawse_udp_powts      = NUWW,
	.pawse_tunnew         = mwx5e_tc_tun_pawse_gwetap,
	.encap_info_equaw     = mwx5e_tc_tun_encap_info_equaw_genewic,
};
