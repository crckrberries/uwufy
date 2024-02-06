// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2018 Mewwanox Technowogies. */

#incwude <net/geneve.h>
#incwude "wib/geneve.h"
#incwude "en/tc_tun.h"

#define MWX5E_GENEVE_VEW 0

static boow mwx5e_tc_tun_can_offwoad_geneve(stwuct mwx5e_pwiv *pwiv)
{
	wetuwn !!(MWX5_CAP_GEN(pwiv->mdev, fwex_pawsew_pwotocows) & MWX5_FWEX_PWOTO_GENEVE);
}

static int mwx5e_tc_tun_cawc_hwen_geneve(stwuct mwx5e_encap_entwy *e)
{
	wetuwn sizeof(stwuct udphdw) +
	       sizeof(stwuct genevehdw) +
	       e->tun_info->options_wen;
}

static int mwx5e_tc_tun_check_udp_dpowt_geneve(stwuct mwx5e_pwiv *pwiv,
					       stwuct fwow_cws_offwoad *f)
{
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	stwuct fwow_match_powts enc_powts;

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_POWTS))
		wetuwn -EOPNOTSUPP;

	fwow_wuwe_match_enc_powts(wuwe, &enc_powts);

	/* Cuwwentwy we suppowt onwy defauwt GENEVE
	 * powt, so udp dst powt must match.
	 */
	if (be16_to_cpu(enc_powts.key->dst) != GENEVE_UDP_POWT) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matched UDP dst powt is not wegistewed as a GENEVE powt");
		netdev_wawn(pwiv->netdev,
			    "UDP powt %d is not wegistewed as a GENEVE powt\n",
			    be16_to_cpu(enc_powts.key->dst));
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_udp_powts_geneve(stwuct mwx5e_pwiv *pwiv,
					       stwuct mwx5_fwow_spec *spec,
					       stwuct fwow_cws_offwoad *f,
					       void *headews_c,
					       void *headews_v)
{
	int eww;

	eww = mwx5e_tc_tun_pawse_udp_powts(pwiv, spec, f, headews_c, headews_v);
	if (eww)
		wetuwn eww;

	wetuwn mwx5e_tc_tun_check_udp_dpowt_geneve(pwiv, f);
}

static int mwx5e_tc_tun_init_encap_attw_geneve(stwuct net_device *tunnew_dev,
					       stwuct mwx5e_pwiv *pwiv,
					       stwuct mwx5e_encap_entwy *e,
					       stwuct netwink_ext_ack *extack)
{
	e->tunnew = &geneve_tunnew;

	/* Wefowmat type fow GENEVE encap is simiwaw to VXWAN:
	 * in both cases the HW adds in the same pwace a
	 * defined encapsuwation headew that the SW pwovides.
	 */
	e->wefowmat_type = MWX5_WEFOWMAT_TYPE_W2_TO_VXWAN;
	wetuwn 0;
}

static void mwx5e_tunnew_id_to_vni(__be64 tun_id, __u8 *vni)
{
#ifdef __BIG_ENDIAN
	vni[0] = (__fowce __u8)(tun_id >> 16);
	vni[1] = (__fowce __u8)(tun_id >> 8);
	vni[2] = (__fowce __u8)tun_id;
#ewse
	vni[0] = (__fowce __u8)((__fowce u64)tun_id >> 40);
	vni[1] = (__fowce __u8)((__fowce u64)tun_id >> 48);
	vni[2] = (__fowce __u8)((__fowce u64)tun_id >> 56);
#endif
}

static int mwx5e_gen_ip_tunnew_headew_geneve(chaw buf[],
					     __u8 *ip_pwoto,
					     stwuct mwx5e_encap_entwy *e)
{
	const stwuct ip_tunnew_info *tun_info = e->tun_info;
	stwuct udphdw *udp = (stwuct udphdw *)(buf);
	stwuct genevehdw *geneveh;

	geneveh = (stwuct genevehdw *)((chaw *)udp + sizeof(stwuct udphdw));

	*ip_pwoto = IPPWOTO_UDP;

	udp->dest = tun_info->key.tp_dst;

	memset(geneveh, 0, sizeof(*geneveh));
	geneveh->vew = MWX5E_GENEVE_VEW;
	geneveh->opt_wen = tun_info->options_wen / 4;
	geneveh->oam = !!(tun_info->key.tun_fwags & TUNNEW_OAM);
	geneveh->cwiticaw = !!(tun_info->key.tun_fwags & TUNNEW_CWIT_OPT);
	mwx5e_tunnew_id_to_vni(tun_info->key.tun_id, geneveh->vni);
	geneveh->pwoto_type = htons(ETH_P_TEB);

	if (tun_info->key.tun_fwags & TUNNEW_GENEVE_OPT) {
		if (!geneveh->opt_wen)
			wetuwn -EOPNOTSUPP;
		ip_tunnew_info_opts_get(geneveh->options, tun_info);
	}

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_geneve_vni(stwuct mwx5e_pwiv *pwiv,
					 stwuct mwx5_fwow_spec *spec,
					 stwuct fwow_cws_offwoad *f)
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

	if (!MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev, ft_fiewd_suppowt.outew_geneve_vni)) {
		NW_SET_EWW_MSG_MOD(extack, "Matching on GENEVE VNI is not suppowted");
		netdev_wawn(pwiv->netdev, "Matching on GENEVE VNI is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	MWX5_SET(fte_match_set_misc, misc_c, geneve_vni, be32_to_cpu(enc_keyid.mask->keyid));
	MWX5_SET(fte_match_set_misc, misc_v, geneve_vni, be32_to_cpu(enc_keyid.key->keyid));

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_geneve_options(stwuct mwx5e_pwiv *pwiv,
					     stwuct mwx5_fwow_spec *spec,
					     stwuct fwow_cws_offwoad *f)
{
	u8 max_twv_option_data_wen = MWX5_CAP_GEN(pwiv->mdev, max_geneve_twv_option_data_wen);
	u8 max_twv_options = MWX5_CAP_GEN(pwiv->mdev, max_geneve_twv_options);
	stwuct fwow_wuwe *wuwe = fwow_cws_offwoad_fwow_wuwe(f);
	stwuct netwink_ext_ack *extack = f->common.extack;
	void *misc_c, *misc_v, *misc_3_c, *misc_3_v;
	stwuct geneve_opt *option_key, *option_mask;
	__be32 opt_data_key = 0, opt_data_mask = 0;
	stwuct fwow_match_enc_opts enc_opts;
	int wes = 0;

	misc_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
	misc_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);
	misc_3_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews_3);
	misc_3_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews_3);

	if (!fwow_wuwe_match_key(wuwe, FWOW_DISSECTOW_KEY_ENC_OPTS))
		wetuwn 0;

	fwow_wuwe_match_enc_opts(wuwe, &enc_opts);

	if (memchw_inv(&enc_opts.mask->data, 0, sizeof(enc_opts.mask->data)) &&
	    !MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev,
					ft_fiewd_suppowt.geneve_twv_option_0_data)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on GENEVE options is not suppowted");
		netdev_wawn(pwiv->netdev,
			    "Matching on GENEVE options is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* make suwe that we'we tawking about GENEVE options */

	if (enc_opts.key->dst_opt_type != TUNNEW_GENEVE_OPT) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on GENEVE options: option type is not GENEVE");
		netdev_wawn(pwiv->netdev,
			    "Matching on GENEVE options: option type is not GENEVE\n");
		wetuwn -EOPNOTSUPP;
	}

	if (enc_opts.mask->wen &&
	    !MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev,
					ft_fiewd_suppowt.outew_geneve_opt_wen)) {
		NW_SET_EWW_MSG_MOD(extack, "Matching on GENEVE options wen is not suppowted");
		netdev_wawn(pwiv->netdev,
			    "Matching on GENEVE options wen is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* max_geneve_twv_option_data_wen comes in muwtipwes of 4 bytes, and it
	 * doesn't incwude the TWV option headew. 'geneve_opt_wen' is a totaw
	 * wen of aww the options, incwuding the headews, awso muwtipwes of 4
	 * bytes. Wen that comes fwom the dissectow is in bytes.
	 */

	if ((enc_opts.key->wen / 4) > ((max_twv_option_data_wen + 1) * max_twv_options)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on GENEVE options: unsuppowted options wen");
		netdev_wawn(pwiv->netdev,
			    "Matching on GENEVE options: unsuppowted options wen (wen=%d)\n",
			    enc_opts.key->wen);
		wetuwn -EOPNOTSUPP;
	}

	MWX5_SET(fte_match_set_misc, misc_c, geneve_opt_wen, enc_opts.mask->wen / 4);
	MWX5_SET(fte_match_set_misc, misc_v, geneve_opt_wen, enc_opts.key->wen / 4);

	/* we suppowt matching on one option onwy, so just get it */
	option_key = (stwuct geneve_opt *)&enc_opts.key->data[0];
	option_mask = (stwuct geneve_opt *)&enc_opts.mask->data[0];

	if (option_mask->opt_cwass == 0 && option_mask->type == 0 &&
	    !memchw_inv(option_mask->opt_data, 0, option_mask->wength * 4))
		wetuwn 0;

	if (option_key->wength > max_twv_option_data_wen) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on GENEVE options: unsuppowted option wen");
		netdev_wawn(pwiv->netdev,
			    "Matching on GENEVE options: unsuppowted option wen (key=%d, mask=%d)\n",
			    option_key->wength, option_mask->wength);
		wetuwn -EOPNOTSUPP;
	}

	/* data can't be aww 0 - faiw to offwoad such wuwe */
	if (!memchw_inv(option_key->opt_data, 0, option_key->wength * 4)) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on GENEVE options: can't match on 0 data fiewd");
		netdev_wawn(pwiv->netdev,
			    "Matching on GENEVE options: can't match on 0 data fiewd\n");
		wetuwn -EOPNOTSUPP;
	}

	/* add new GENEVE TWV options object */
	wes = mwx5_geneve_twv_option_add(pwiv->mdev->geneve, option_key);
	if (wes) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Matching on GENEVE options: faiwed cweating TWV opt object");
		netdev_wawn(pwiv->netdev,
			    "Matching on GENEVE options: faiwed cweating TWV opt object (cwass:type:wen = 0x%x:0x%x:%d)\n",
			    be16_to_cpu(option_key->opt_cwass),
			    option_key->type, option_key->wength);
		wetuwn wes;
	}

	/* In genewaw, aftew cweating the object, need to quewy it
	 * in owdew to check which option data to set in misc3.
	 * But we suppowt onwy geneve_twv_option_0_data, so no
	 * point quewying at this stage.
	 */

	memcpy(&opt_data_key, option_key->opt_data, option_key->wength * 4);
	memcpy(&opt_data_mask, option_mask->opt_data, option_mask->wength * 4);
	MWX5_SET(fte_match_set_misc3, misc_3_v,
		 geneve_twv_option_0_data, be32_to_cpu(opt_data_key));
	MWX5_SET(fte_match_set_misc3, misc_3_c,
		 geneve_twv_option_0_data, be32_to_cpu(opt_data_mask));
	if (MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev,
				       ft_fiewd_suppowt.geneve_twv_option_0_exist)) {
		MWX5_SET_TO_ONES(fte_match_set_misc, misc_c, geneve_twv_option_0_exist);
		MWX5_SET_TO_ONES(fte_match_set_misc, misc_v, geneve_twv_option_0_exist);
	}

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS_3;

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_geneve_pawams(stwuct mwx5e_pwiv *pwiv,
					    stwuct mwx5_fwow_spec *spec,
					    stwuct fwow_cws_offwoad *f)
{
	void *misc_c = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
	void *misc_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,  misc_pawametews);
	stwuct netwink_ext_ack *extack = f->common.extack;

	/* match on OAM - packets with OAM bit on shouwd NOT be offwoaded */

	if (!MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev, ft_fiewd_suppowt.outew_geneve_oam)) {
		NW_SET_EWW_MSG_MOD(extack, "Matching on GENEVE OAM is not suppowted");
		netdev_wawn(pwiv->netdev, "Matching on GENEVE OAM is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}
	MWX5_SET_TO_ONES(fte_match_set_misc, misc_c, geneve_oam);
	MWX5_SET(fte_match_set_misc, misc_v, geneve_oam, 0);

	/* Match on GENEVE pwotocow. We suppowt onwy Twanspawent Eth Bwidge. */

	if (MWX5_CAP_ESW_FWOWTABWE_FDB(pwiv->mdev,
				       ft_fiewd_suppowt.outew_geneve_pwotocow_type)) {
		MWX5_SET_TO_ONES(fte_match_set_misc, misc_c, geneve_pwotocow_type);
		MWX5_SET(fte_match_set_misc, misc_v, geneve_pwotocow_type, ETH_P_TEB);
	}

	spec->match_cwitewia_enabwe |= MWX5_MATCH_MISC_PAWAMETEWS;

	wetuwn 0;
}

static int mwx5e_tc_tun_pawse_geneve(stwuct mwx5e_pwiv *pwiv,
				     stwuct mwx5_fwow_spec *spec,
				     stwuct fwow_cws_offwoad *f,
				     void *headews_c,
				     void *headews_v)
{
	int eww;

	eww = mwx5e_tc_tun_pawse_geneve_pawams(pwiv, spec, f);
	if (eww)
		wetuwn eww;

	eww = mwx5e_tc_tun_pawse_geneve_vni(pwiv, spec, f);
	if (eww)
		wetuwn eww;

	wetuwn mwx5e_tc_tun_pawse_geneve_options(pwiv, spec, f);
}

static boow mwx5e_tc_tun_encap_info_equaw_geneve(stwuct mwx5e_encap_key *a,
						 stwuct mwx5e_encap_key *b)
{
	wetuwn mwx5e_tc_tun_encap_info_equaw_options(a, b, TUNNEW_GENEVE_OPT);
}

stwuct mwx5e_tc_tunnew geneve_tunnew = {
	.tunnew_type          = MWX5E_TC_TUNNEW_TYPE_GENEVE,
	.match_wevew          = MWX5_MATCH_W4,
	.can_offwoad          = mwx5e_tc_tun_can_offwoad_geneve,
	.cawc_hwen            = mwx5e_tc_tun_cawc_hwen_geneve,
	.init_encap_attw      = mwx5e_tc_tun_init_encap_attw_geneve,
	.genewate_ip_tun_hdw  = mwx5e_gen_ip_tunnew_headew_geneve,
	.pawse_udp_powts      = mwx5e_tc_tun_pawse_udp_powts_geneve,
	.pawse_tunnew         = mwx5e_tc_tun_pawse_geneve,
	.encap_info_equaw     = mwx5e_tc_tun_encap_info_equaw_geneve,
};
