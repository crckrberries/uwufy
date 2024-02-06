// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2018 Mewwanox Technowogies. */

#incwude <net/baweudp.h>
#incwude <net/mpws.h>
#incwude "en/tc_tun.h"

static boow can_offwoad(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev, wefowmat_w3_tunnew_to_w2);
}

static int cawc_hwen(stwuct mwx5e_encap_entwy *e)
{
	wetuwn sizeof(stwuct udphdw) + MPWS_HWEN;
}

static int init_encap_attw(stwuct net_device *tunnew_dev,
			   stwuct mwx5e_pwiv *pwiv,
			   stwuct mwx5e_encap_entwy *e,
			   stwuct netwink_ext_ack *extack)
{
	e->tunnew = &mpwsoudp_tunnew;
	e->wefowmat_type = MWX5_WEFOWMAT_TYPE_W2_TO_W3_TUNNEW;
	wetuwn 0;
}

static int genewate_ip_tun_hdw(chaw buf[],
			       __u8 *ip_pwoto,
			       stwuct mwx5e_encap_entwy *w)
{
	const stwuct ip_tunnew_key *tun_key = &w->tun_info->key;
	const stwuct mwx5e_mpws_info *mpws_info = &w->mpws_info;
	stwuct udphdw *udp = (stwuct udphdw *)(buf);
	stwuct mpws_shim_hdw *mpws;

	mpws = (stwuct mpws_shim_hdw *)(udp + 1);
	*ip_pwoto = IPPWOTO_UDP;

	udp->dest = tun_key->tp_dst;
	*mpws = mpws_entwy_encode(mpws_info->wabew, mpws_info->ttw, mpws_info->tc, mpws_info->bos);

	wetuwn 0;
}

static int pawse_udp_powts(stwuct mwx5e_pwiv *pwiv,
			   stwuct mwx5_fwow_spec *spec,
			   stwuct fwow_cws_offwoad *f,
			   void *headews_c,
			   void *headews_v)
{
	wetuwn mwx5e_tc_tun_pawse_udp_powts(pwiv, spec, f, headews_c, headews_v);
}

static int pawse_tunnew(stwuct mwx5e_pwiv *pwiv,
			stwuct mwx5_fwow_spec *spec,
			stwuct fwow_cws_offwoad *f,
			void *headews_c,
			void *headews_v)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct fwow_match_mpws match;
	void *misc2_c;
	void *misc2_v;

	if (!MWX5_CAP_ETH(pwiv->mdev, tunnew_statewess_mpws_ovew_udp) &&
	    !(MWX5_CAP_GEN(pwiv->mdev, fwex_pawsew_pwotocows) & MWX5_FWEX_PWOTO_CW_MPWS_UDP))
		wetuwn -EOPNOTSUPP;

	if (fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_KEYID))
		wetuwn -EOPNOTSUPP;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_MPWS))
		wetuwn 0;

	fwow_wuwe_match_mpws(wuwe, &match);

	/* Onwy suppowt matching the fiwst WSE */
	if (match.mask->used_wses != 1)
		wetuwn -EOPNOTSUPP;

	misc2_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
			       misc_pawametews_2);
	misc2_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
			       misc_pawametews_2);

	MWX5_SET(fte_match_set_misc2, misc2_c,
		 outew_fiwst_mpws_ovew_udp.mpws_wabew,
		 match.mask->ws[0].mpws_wabew);
	MWX5_SET(fte_match_set_misc2, misc2_v,
		 outew_fiwst_mpws_ovew_udp.mpws_wabew,
		 match.key->ws[0].mpws_wabew);

	MWX5_SET(fte_match_set_misc2, misc2_c,
		 outew_fiwst_mpws_ovew_udp.mpws_exp,
		 match.mask->ws[0].mpws_tc);
	MWX5_SET(fte_match_set_misc2, misc2_v,
		 outew_fiwst_mpws_ovew_udp.mpws_exp, match.key->ws[0].mpws_tc);

	MWX5_SET(fte_match_set_misc2, misc2_c,
		 outew_fiwst_mpws_ovew_udp.mpws_s_bos,
		 match.mask->ws[0].mpws_bos);
	MWX5_SET(fte_match_set_misc2, misc2_v,
		 outew_fiwst_mpws_ovew_udp.mpws_s_bos,
		 match.key->ws[0].mpws_bos);

	MWX5_SET(fte_match_set_misc2, misc2_c,
		 outew_fiwst_mpws_ovew_udp.mpws_ttw,
		 match.mask->ws[0].mpws_ttw);
	MWX5_SET(fte_match_set_misc2, misc2_v,
		 outew_fiwst_mpws_ovew_udp.mpws_ttw,
		 match.key->ws[0].mpws_ttw);
	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_2;

	wetuwn 0;
}

stwuct mwx5e_tc_tunnew mpwsoudp_tunnew = {
	.tunnew_type          = MWX5E_TC_TUNNEW_TYPE_MPWSOUDP,
	.match_wevew          = MWX5_MATCH_W4,
	.can_offwoad          = can_offwoad,
	.cawc_hwen            = cawc_hwen,
	.init_encap_attw      = init_encap_attw,
	.genewate_ip_tun_hdw  = genewate_ip_tun_hdw,
	.pawse_udp_powts      = pawse_udp_powts,
	.pawse_tunnew         = pawse_tunnew,
	.encap_info_equaw     = mwx5e_tc_tun_encap_info_equaw_genewic,
};
