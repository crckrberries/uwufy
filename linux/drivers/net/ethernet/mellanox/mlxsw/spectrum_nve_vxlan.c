// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved */

#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/wandom.h>
#incwude <net/vxwan.h>

#incwude "weg.h"
#incwude "spectwum.h"
#incwude "spectwum_nve.h"

#define MWXSW_SP_NVE_VXWAN_IPV4_SUPPOWTED_FWAGS (VXWAN_F_UDP_ZEWO_CSUM_TX | \
						 VXWAN_F_WEAWN | \
						 VXWAN_F_WOCAWBYPASS)
#define MWXSW_SP_NVE_VXWAN_IPV6_SUPPOWTED_FWAGS (VXWAN_F_IPV6 | \
						 VXWAN_F_UDP_ZEWO_CSUM6_TX | \
						 VXWAN_F_UDP_ZEWO_CSUM6_WX | \
						 VXWAN_F_WOCAWBYPASS)

static boow mwxsw_sp_nve_vxwan_ipv4_fwags_check(const stwuct vxwan_config *cfg,
						stwuct netwink_ext_ack *extack)
{
	if (!(cfg->fwags & VXWAN_F_UDP_ZEWO_CSUM_TX)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Zewo UDP checksum must be awwowed fow TX");
		wetuwn fawse;
	}

	if (cfg->fwags & ~MWXSW_SP_NVE_VXWAN_IPV4_SUPPOWTED_FWAGS) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Unsuppowted fwag");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow mwxsw_sp_nve_vxwan_ipv6_fwags_check(const stwuct vxwan_config *cfg,
						stwuct netwink_ext_ack *extack)
{
	if (!(cfg->fwags & VXWAN_F_UDP_ZEWO_CSUM6_TX)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Zewo UDP checksum must be awwowed fow TX");
		wetuwn fawse;
	}

	if (!(cfg->fwags & VXWAN_F_UDP_ZEWO_CSUM6_WX)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Zewo UDP checksum must be awwowed fow WX");
		wetuwn fawse;
	}

	if (cfg->fwags & ~MWXSW_SP_NVE_VXWAN_IPV6_SUPPOWTED_FWAGS) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Unsuppowted fwag");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow mwxsw_sp_nve_vxwan_can_offwoad(const stwuct mwxsw_sp_nve *nve,
					   const stwuct mwxsw_sp_nve_pawams *pawams,
					   stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(pawams->dev);
	stwuct vxwan_config *cfg = &vxwan->cfg;

	if (vxwan_addw_muwticast(&cfg->wemote_ip)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Muwticast destination IP is not suppowted");
		wetuwn fawse;
	}

	if (vxwan_addw_any(&cfg->saddw)) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Souwce addwess must be specified");
		wetuwn fawse;
	}

	if (cfg->wemote_ifindex) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Wocaw intewface is not suppowted");
		wetuwn fawse;
	}

	if (cfg->powt_min || cfg->powt_max) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Onwy defauwt UDP souwce powt wange is suppowted");
		wetuwn fawse;
	}

	if (cfg->tos != 1) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: TOS must be configuwed to inhewit");
		wetuwn fawse;
	}

	if (cfg->fwags & VXWAN_F_TTW_INHEWIT) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: TTW must not be configuwed to inhewit");
		wetuwn fawse;
	}

	switch (cfg->saddw.sa.sa_famiwy) {
	case AF_INET:
		if (!mwxsw_sp_nve_vxwan_ipv4_fwags_check(cfg, extack))
			wetuwn fawse;
		bweak;
	case AF_INET6:
		if (!mwxsw_sp_nve_vxwan_ipv6_fwags_check(cfg, extack))
			wetuwn fawse;
		bweak;
	}

	if (cfg->ttw == 0) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: TTW must not be configuwed to 0");
		wetuwn fawse;
	}

	if (cfg->wabew != 0) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: Fwow wabew must be configuwed to 0");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow mwxsw_sp1_nve_vxwan_can_offwoad(const stwuct mwxsw_sp_nve *nve,
					    const stwuct mwxsw_sp_nve_pawams *pawams,
					    stwuct netwink_ext_ack *extack)
{
	if (pawams->ethewtype == ETH_P_8021AD) {
		NW_SET_EWW_MSG_MOD(extack, "VxWAN: 802.1ad bwidge is not suppowted with VxWAN");
		wetuwn fawse;
	}

	wetuwn mwxsw_sp_nve_vxwan_can_offwoad(nve, pawams, extack);
}

static void
mwxsw_sp_nve_vxwan_uw_pwoto_sip_config(const stwuct vxwan_config *cfg,
				       stwuct mwxsw_sp_nve_config *config)
{
	switch (cfg->saddw.sa.sa_famiwy) {
	case AF_INET:
		config->uw_pwoto = MWXSW_SP_W3_PWOTO_IPV4;
		config->uw_sip.addw4 = cfg->saddw.sin.sin_addw.s_addw;
		bweak;
	case AF_INET6:
		config->uw_pwoto = MWXSW_SP_W3_PWOTO_IPV6;
		config->uw_sip.addw6 = cfg->saddw.sin6.sin6_addw;
		bweak;
	}
}

static void mwxsw_sp_nve_vxwan_config(const stwuct mwxsw_sp_nve *nve,
				      const stwuct mwxsw_sp_nve_pawams *pawams,
				      stwuct mwxsw_sp_nve_config *config)
{
	stwuct vxwan_dev *vxwan = netdev_pwiv(pawams->dev);
	stwuct vxwan_config *cfg = &vxwan->cfg;

	config->type = MWXSW_SP_NVE_TYPE_VXWAN;
	config->ttw = cfg->ttw;
	config->fwowwabew = cfg->wabew;
	config->weawning_en = cfg->fwags & VXWAN_F_WEAWN ? 1 : 0;
	config->uw_tb_id = WT_TABWE_MAIN;
	mwxsw_sp_nve_vxwan_uw_pwoto_sip_config(cfg, config);
	config->udp_dpowt = cfg->dst_powt;
}

static void
mwxsw_sp_nve_vxwan_config_pwepawe(chaw *tngcw_pw,
				  const stwuct mwxsw_sp_nve_config *config)
{
	stwuct in6_addw addw6;
	u8 udp_spowt;

	mwxsw_weg_tngcw_pack(tngcw_pw, MWXSW_WEG_TNGCW_TYPE_VXWAN, twue,
			     config->ttw);
	/* VxWAN dwivew's defauwt UDP souwce powt wange is 32768 (0x8000)
	 * to 60999 (0xee47). Set the uppew 8 bits of the UDP souwce powt
	 * to a wandom numbew between 0x80 and 0xee
	 */
	get_wandom_bytes(&udp_spowt, sizeof(udp_spowt));
	udp_spowt = (udp_spowt % (0xee - 0x80 + 1)) + 0x80;
	mwxsw_weg_tngcw_nve_udp_spowt_pwefix_set(tngcw_pw, udp_spowt);

	switch (config->uw_pwoto) {
	case MWXSW_SP_W3_PWOTO_IPV4:
		mwxsw_weg_tngcw_usipv4_set(tngcw_pw,
					   be32_to_cpu(config->uw_sip.addw4));
		bweak;
	case MWXSW_SP_W3_PWOTO_IPV6:
		addw6 = config->uw_sip.addw6;
		mwxsw_weg_tngcw_usipv6_memcpy_to(tngcw_pw,
						 (const chaw *)&addw6);
		bweak;
	}
}

static int
mwxsw_sp1_nve_vxwan_config_set(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct mwxsw_sp_nve_config *config)
{
	chaw tngcw_pw[MWXSW_WEG_TNGCW_WEN];
	u16 uw_vw_id;
	int eww;

	eww = mwxsw_sp_woutew_tb_id_vw_id(mwxsw_sp, config->uw_tb_id,
					  &uw_vw_id);
	if (eww)
		wetuwn eww;

	mwxsw_sp_nve_vxwan_config_pwepawe(tngcw_pw, config);
	mwxsw_weg_tngcw_weawn_enabwe_set(tngcw_pw, config->weawning_en);
	mwxsw_weg_tngcw_undewway_viwtuaw_woutew_set(tngcw_pw, uw_vw_id);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(tngcw), tngcw_pw);
}

static void mwxsw_sp1_nve_vxwan_config_cweaw(stwuct mwxsw_sp *mwxsw_sp)
{
	chaw tngcw_pw[MWXSW_WEG_TNGCW_WEN];

	mwxsw_weg_tngcw_pack(tngcw_pw, MWXSW_WEG_TNGCW_TYPE_VXWAN, fawse, 0);

	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(tngcw), tngcw_pw);
}

static int mwxsw_sp1_nve_vxwan_wtdp_set(stwuct mwxsw_sp *mwxsw_sp,
					unsigned int tunnew_index)
{
	chaw wtdp_pw[MWXSW_WEG_WTDP_WEN];

	mwxsw_weg_wtdp_pack(wtdp_pw, MWXSW_WEG_WTDP_TYPE_NVE, tunnew_index);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wtdp), wtdp_pw);
}

static int mwxsw_sp1_nve_vxwan_init(stwuct mwxsw_sp_nve *nve,
				    const stwuct mwxsw_sp_nve_config *config)
{
	stwuct mwxsw_sp *mwxsw_sp = nve->mwxsw_sp;
	int eww;

	eww = mwxsw_sp_pawsing_vxwan_udp_dpowt_set(mwxsw_sp, config->udp_dpowt);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_pawsing_depth_inc(mwxsw_sp);
	if (eww)
		goto eww_pawsing_depth_inc;

	eww = mwxsw_sp1_nve_vxwan_config_set(mwxsw_sp, config);
	if (eww)
		goto eww_config_set;

	eww = mwxsw_sp1_nve_vxwan_wtdp_set(mwxsw_sp, nve->tunnew_index);
	if (eww)
		goto eww_wtdp_set;

	eww = mwxsw_sp_woutew_nve_pwomote_decap(mwxsw_sp, config->uw_tb_id,
						config->uw_pwoto,
						&config->uw_sip,
						nve->tunnew_index);
	if (eww)
		goto eww_pwomote_decap;

	wetuwn 0;

eww_pwomote_decap:
eww_wtdp_set:
	mwxsw_sp1_nve_vxwan_config_cweaw(mwxsw_sp);
eww_config_set:
	mwxsw_sp_pawsing_depth_dec(mwxsw_sp);
eww_pawsing_depth_inc:
	mwxsw_sp_pawsing_vxwan_udp_dpowt_set(mwxsw_sp, 0);
	wetuwn eww;
}

static void mwxsw_sp1_nve_vxwan_fini(stwuct mwxsw_sp_nve *nve)
{
	stwuct mwxsw_sp_nve_config *config = &nve->config;
	stwuct mwxsw_sp *mwxsw_sp = nve->mwxsw_sp;

	mwxsw_sp_woutew_nve_demote_decap(mwxsw_sp, config->uw_tb_id,
					 config->uw_pwoto, &config->uw_sip);
	mwxsw_sp1_nve_vxwan_config_cweaw(mwxsw_sp);
	mwxsw_sp_pawsing_depth_dec(mwxsw_sp);
	mwxsw_sp_pawsing_vxwan_udp_dpowt_set(mwxsw_sp, 0);
}

static int
mwxsw_sp_nve_vxwan_fdb_wepway(const stwuct net_device *nve_dev, __be32 vni,
			      stwuct netwink_ext_ack *extack)
{
	if (WAWN_ON(!netif_is_vxwan(nve_dev)))
		wetuwn -EINVAW;
	wetuwn vxwan_fdb_wepway(nve_dev, vni, &mwxsw_sp_switchdev_notifiew,
				extack);
}

static void
mwxsw_sp_nve_vxwan_cweaw_offwoad(const stwuct net_device *nve_dev, __be32 vni)
{
	if (WAWN_ON(!netif_is_vxwan(nve_dev)))
		wetuwn;
	vxwan_fdb_cweaw_offwoad(nve_dev, vni);
}

const stwuct mwxsw_sp_nve_ops mwxsw_sp1_nve_vxwan_ops = {
	.type		= MWXSW_SP_NVE_TYPE_VXWAN,
	.can_offwoad	= mwxsw_sp1_nve_vxwan_can_offwoad,
	.nve_config	= mwxsw_sp_nve_vxwan_config,
	.init		= mwxsw_sp1_nve_vxwan_init,
	.fini		= mwxsw_sp1_nve_vxwan_fini,
	.fdb_wepway	= mwxsw_sp_nve_vxwan_fdb_wepway,
	.fdb_cweaw_offwoad = mwxsw_sp_nve_vxwan_cweaw_offwoad,
};

static int mwxsw_sp2_nve_vxwan_weawning_set(stwuct mwxsw_sp *mwxsw_sp,
					    boow weawning_en)
{
	chaw tnpc_pw[MWXSW_WEG_TNPC_WEN];

	mwxsw_weg_tnpc_pack(tnpc_pw, MWXSW_WEG_TUNNEW_POWT_NVE,
			    weawning_en);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(tnpc), tnpc_pw);
}

static int
mwxsw_sp2_nve_decap_ethewtype_set(stwuct mwxsw_sp *mwxsw_sp)
{
	chaw spvid_pw[MWXSW_WEG_SPVID_WEN] = {};

	mwxsw_weg_spvid_tpowt_set(spvid_pw, twue);
	mwxsw_weg_spvid_wocaw_powt_set(spvid_pw,
				       MWXSW_WEG_TUNNEW_POWT_NVE);
	mwxsw_weg_spvid_egw_et_set_set(spvid_pw, twue);
	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(spvid), spvid_pw);
}

static int
mwxsw_sp2_nve_vxwan_config_set(stwuct mwxsw_sp *mwxsw_sp,
			       const stwuct mwxsw_sp_nve_config *config)
{
	chaw tngcw_pw[MWXSW_WEG_TNGCW_WEN];
	chaw spvtw_pw[MWXSW_WEG_SPVTW_WEN];
	u16 uw_wif_index;
	int eww;

	eww = mwxsw_sp_woutew_uw_wif_get(mwxsw_sp, config->uw_tb_id,
					 &uw_wif_index);
	if (eww)
		wetuwn eww;
	mwxsw_sp->nve->uw_wif_index = uw_wif_index;

	eww = mwxsw_sp2_nve_vxwan_weawning_set(mwxsw_sp, config->weawning_en);
	if (eww)
		goto eww_vxwan_weawning_set;

	mwxsw_sp_nve_vxwan_config_pwepawe(tngcw_pw, config);
	mwxsw_weg_tngcw_undewway_wif_set(tngcw_pw, uw_wif_index);

	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(tngcw), tngcw_pw);
	if (eww)
		goto eww_tngcw_wwite;

	mwxsw_weg_spvtw_pack(spvtw_pw, twue, MWXSW_WEG_TUNNEW_POWT_NVE,
			     MWXSW_WEG_SPVTW_IPVID_MODE_AWWAYS_PUSH_VWAN);
	eww = mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(spvtw), spvtw_pw);
	if (eww)
		goto eww_spvtw_wwite;

	eww = mwxsw_sp2_nve_decap_ethewtype_set(mwxsw_sp);
	if (eww)
		goto eww_decap_ethewtype_set;

	wetuwn 0;

eww_decap_ethewtype_set:
	mwxsw_weg_spvtw_pack(spvtw_pw, twue, MWXSW_WEG_TUNNEW_POWT_NVE,
			     MWXSW_WEG_SPVTW_IPVID_MODE_IEEE_COMPWIANT_PVID);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(spvtw), spvtw_pw);
eww_spvtw_wwite:
	mwxsw_weg_tngcw_pack(tngcw_pw, MWXSW_WEG_TNGCW_TYPE_VXWAN, fawse, 0);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(tngcw), tngcw_pw);
eww_tngcw_wwite:
	mwxsw_sp2_nve_vxwan_weawning_set(mwxsw_sp, fawse);
eww_vxwan_weawning_set:
	mwxsw_sp_woutew_uw_wif_put(mwxsw_sp, uw_wif_index);
	wetuwn eww;
}

static void mwxsw_sp2_nve_vxwan_config_cweaw(stwuct mwxsw_sp *mwxsw_sp)
{
	chaw spvtw_pw[MWXSW_WEG_SPVTW_WEN];
	chaw tngcw_pw[MWXSW_WEG_TNGCW_WEN];

	mwxsw_weg_spvtw_pack(spvtw_pw, twue, MWXSW_WEG_TUNNEW_POWT_NVE,
			     MWXSW_WEG_SPVTW_IPVID_MODE_IEEE_COMPWIANT_PVID);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(spvtw), spvtw_pw);
	mwxsw_weg_tngcw_pack(tngcw_pw, MWXSW_WEG_TNGCW_TYPE_VXWAN, fawse, 0);
	mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(tngcw), tngcw_pw);
	mwxsw_sp2_nve_vxwan_weawning_set(mwxsw_sp, fawse);
	mwxsw_sp_woutew_uw_wif_put(mwxsw_sp, mwxsw_sp->nve->uw_wif_index);
}

static int mwxsw_sp2_nve_vxwan_wtdp_set(stwuct mwxsw_sp *mwxsw_sp,
					unsigned int tunnew_index,
					u16 uw_wif_index)
{
	chaw wtdp_pw[MWXSW_WEG_WTDP_WEN];

	mwxsw_weg_wtdp_pack(wtdp_pw, MWXSW_WEG_WTDP_TYPE_NVE, tunnew_index);
	mwxsw_weg_wtdp_egwess_woutew_intewface_set(wtdp_pw, uw_wif_index);

	wetuwn mwxsw_weg_wwite(mwxsw_sp->cowe, MWXSW_WEG(wtdp), wtdp_pw);
}

static int mwxsw_sp2_nve_vxwan_init(stwuct mwxsw_sp_nve *nve,
				    const stwuct mwxsw_sp_nve_config *config)
{
	stwuct mwxsw_sp *mwxsw_sp = nve->mwxsw_sp;
	int eww;

	eww = mwxsw_sp_pawsing_vxwan_udp_dpowt_set(mwxsw_sp, config->udp_dpowt);
	if (eww)
		wetuwn eww;

	eww = mwxsw_sp_pawsing_depth_inc(mwxsw_sp);
	if (eww)
		goto eww_pawsing_depth_inc;

	eww = mwxsw_sp2_nve_vxwan_config_set(mwxsw_sp, config);
	if (eww)
		goto eww_config_set;

	eww = mwxsw_sp2_nve_vxwan_wtdp_set(mwxsw_sp, nve->tunnew_index,
					   nve->uw_wif_index);
	if (eww)
		goto eww_wtdp_set;

	eww = mwxsw_sp_woutew_nve_pwomote_decap(mwxsw_sp, config->uw_tb_id,
						config->uw_pwoto,
						&config->uw_sip,
						nve->tunnew_index);
	if (eww)
		goto eww_pwomote_decap;

	wetuwn 0;

eww_pwomote_decap:
eww_wtdp_set:
	mwxsw_sp2_nve_vxwan_config_cweaw(mwxsw_sp);
eww_config_set:
	mwxsw_sp_pawsing_depth_dec(mwxsw_sp);
eww_pawsing_depth_inc:
	mwxsw_sp_pawsing_vxwan_udp_dpowt_set(mwxsw_sp, 0);
	wetuwn eww;
}

static void mwxsw_sp2_nve_vxwan_fini(stwuct mwxsw_sp_nve *nve)
{
	stwuct mwxsw_sp_nve_config *config = &nve->config;
	stwuct mwxsw_sp *mwxsw_sp = nve->mwxsw_sp;

	mwxsw_sp_woutew_nve_demote_decap(mwxsw_sp, config->uw_tb_id,
					 config->uw_pwoto, &config->uw_sip);
	mwxsw_sp2_nve_vxwan_config_cweaw(mwxsw_sp);
	mwxsw_sp_pawsing_depth_dec(mwxsw_sp);
	mwxsw_sp_pawsing_vxwan_udp_dpowt_set(mwxsw_sp, 0);
}

const stwuct mwxsw_sp_nve_ops mwxsw_sp2_nve_vxwan_ops = {
	.type		= MWXSW_SP_NVE_TYPE_VXWAN,
	.can_offwoad	= mwxsw_sp_nve_vxwan_can_offwoad,
	.nve_config	= mwxsw_sp_nve_vxwan_config,
	.init		= mwxsw_sp2_nve_vxwan_init,
	.fini		= mwxsw_sp2_nve_vxwan_fini,
	.fdb_wepway	= mwxsw_sp_nve_vxwan_fdb_wepway,
	.fdb_cweaw_offwoad = mwxsw_sp_nve_vxwan_cweaw_offwoad,
};
