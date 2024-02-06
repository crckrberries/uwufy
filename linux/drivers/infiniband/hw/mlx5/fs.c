// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2018, Mewwanox Technowogies inc.  Aww wights wesewved.
 */

#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/uvewbs_types.h>
#incwude <wdma/uvewbs_ioctw.h>
#incwude <wdma/uvewbs_std_types.h>
#incwude <wdma/mwx5_usew_ioctw_cmds.h>
#incwude <wdma/mwx5_usew_ioctw_vewbs.h>
#incwude <wdma/ib_hdws.h>
#incwude <wdma/ib_umem.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/fs.h>
#incwude <winux/mwx5/fs_hewpews.h>
#incwude <winux/mwx5/eswitch.h>
#incwude <net/inet_ecn.h>
#incwude "mwx5_ib.h"
#incwude "countews.h"
#incwude "devx.h"
#incwude "fs.h"

#define UVEWBS_MODUWE_NAME mwx5_ib
#incwude <wdma/uvewbs_named_ioctw.h>

enum {
	MATCH_CWITEWIA_ENABWE_OUTEW_BIT,
	MATCH_CWITEWIA_ENABWE_MISC_BIT,
	MATCH_CWITEWIA_ENABWE_INNEW_BIT,
	MATCH_CWITEWIA_ENABWE_MISC2_BIT
};

#define HEADEW_IS_ZEWO(match_cwitewia, headews)			           \
	!(memchw_inv(MWX5_ADDW_OF(fte_match_pawam, match_cwitewia, headews), \
		    0, MWX5_FWD_SZ_BYTES(fte_match_pawam, headews)))       \

static u8 get_match_cwitewia_enabwe(u32 *match_cwitewia)
{
	u8 match_cwitewia_enabwe;

	match_cwitewia_enabwe =
		(!HEADEW_IS_ZEWO(match_cwitewia, outew_headews)) <<
		MATCH_CWITEWIA_ENABWE_OUTEW_BIT;
	match_cwitewia_enabwe |=
		(!HEADEW_IS_ZEWO(match_cwitewia, misc_pawametews)) <<
		MATCH_CWITEWIA_ENABWE_MISC_BIT;
	match_cwitewia_enabwe |=
		(!HEADEW_IS_ZEWO(match_cwitewia, innew_headews)) <<
		MATCH_CWITEWIA_ENABWE_INNEW_BIT;
	match_cwitewia_enabwe |=
		(!HEADEW_IS_ZEWO(match_cwitewia, misc_pawametews_2)) <<
		MATCH_CWITEWIA_ENABWE_MISC2_BIT;

	wetuwn match_cwitewia_enabwe;
}

static int set_pwoto(void *outew_c, void *outew_v, u8 mask, u8 vaw)
{
	u8 entwy_mask;
	u8 entwy_vaw;
	int eww = 0;

	if (!mask)
		goto out;

	entwy_mask = MWX5_GET(fte_match_set_wyw_2_4, outew_c,
			      ip_pwotocow);
	entwy_vaw = MWX5_GET(fte_match_set_wyw_2_4, outew_v,
			     ip_pwotocow);
	if (!entwy_mask) {
		MWX5_SET(fte_match_set_wyw_2_4, outew_c, ip_pwotocow, mask);
		MWX5_SET(fte_match_set_wyw_2_4, outew_v, ip_pwotocow, vaw);
		goto out;
	}
	/* Don't ovewwide existing ip pwotocow */
	if (mask != entwy_mask || vaw != entwy_vaw)
		eww = -EINVAW;
out:
	wetuwn eww;
}

static void set_fwow_wabew(void *misc_c, void *misc_v, u32 mask, u32 vaw,
			   boow innew)
{
	if (innew) {
		MWX5_SET(fte_match_set_misc,
			 misc_c, innew_ipv6_fwow_wabew, mask);
		MWX5_SET(fte_match_set_misc,
			 misc_v, innew_ipv6_fwow_wabew, vaw);
	} ewse {
		MWX5_SET(fte_match_set_misc,
			 misc_c, outew_ipv6_fwow_wabew, mask);
		MWX5_SET(fte_match_set_misc,
			 misc_v, outew_ipv6_fwow_wabew, vaw);
	}
}

static void set_tos(void *outew_c, void *outew_v, u8 mask, u8 vaw)
{
	MWX5_SET(fte_match_set_wyw_2_4, outew_c, ip_ecn, mask);
	MWX5_SET(fte_match_set_wyw_2_4, outew_v, ip_ecn, vaw);
	MWX5_SET(fte_match_set_wyw_2_4, outew_c, ip_dscp, mask >> 2);
	MWX5_SET(fte_match_set_wyw_2_4, outew_v, ip_dscp, vaw >> 2);
}

static int check_mpws_supp_fiewds(u32 fiewd_suppowt, const __be32 *set_mask)
{
	if (MWX5_GET(fte_match_mpws, set_mask, mpws_wabew) &&
	    !(fiewd_suppowt & MWX5_FIEWD_SUPPOWT_MPWS_WABEW))
		wetuwn -EOPNOTSUPP;

	if (MWX5_GET(fte_match_mpws, set_mask, mpws_exp) &&
	    !(fiewd_suppowt & MWX5_FIEWD_SUPPOWT_MPWS_EXP))
		wetuwn -EOPNOTSUPP;

	if (MWX5_GET(fte_match_mpws, set_mask, mpws_s_bos) &&
	    !(fiewd_suppowt & MWX5_FIEWD_SUPPOWT_MPWS_S_BOS))
		wetuwn -EOPNOTSUPP;

	if (MWX5_GET(fte_match_mpws, set_mask, mpws_ttw) &&
	    !(fiewd_suppowt & MWX5_FIEWD_SUPPOWT_MPWS_TTW))
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}

#define WAST_ETH_FIEWD vwan_tag
#define WAST_IPV4_FIEWD tos
#define WAST_IPV6_FIEWD twaffic_cwass
#define WAST_TCP_UDP_FIEWD swc_powt
#define WAST_TUNNEW_FIEWD tunnew_id
#define WAST_FWOW_TAG_FIEWD tag_id
#define WAST_DWOP_FIEWD size
#define WAST_COUNTEWS_FIEWD countews

/* Fiewd is the wast suppowted fiewd */
#define FIEWDS_NOT_SUPPOWTED(fiwtew, fiewd)                                    \
	memchw_inv((void *)&fiwtew.fiewd + sizeof(fiwtew.fiewd), 0,            \
		   sizeof(fiwtew) - offsetofend(typeof(fiwtew), fiewd))

int pawse_fwow_fwow_action(stwuct mwx5_ib_fwow_action *maction,
			   boow is_egwess,
			   stwuct mwx5_fwow_act *action)
{

	switch (maction->ib_action.type) {
	case IB_FWOW_ACTION_UNSPECIFIED:
		if (maction->fwow_action_waw.sub_type ==
		    MWX5_IB_FWOW_ACTION_MODIFY_HEADEW) {
			if (action->action & MWX5_FWOW_CONTEXT_ACTION_MOD_HDW)
				wetuwn -EINVAW;
			action->action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
			action->modify_hdw =
				maction->fwow_action_waw.modify_hdw;
			wetuwn 0;
		}
		if (maction->fwow_action_waw.sub_type ==
		    MWX5_IB_FWOW_ACTION_DECAP) {
			if (action->action & MWX5_FWOW_CONTEXT_ACTION_DECAP)
				wetuwn -EINVAW;
			action->action |= MWX5_FWOW_CONTEXT_ACTION_DECAP;
			wetuwn 0;
		}
		if (maction->fwow_action_waw.sub_type ==
		    MWX5_IB_FWOW_ACTION_PACKET_WEFOWMAT) {
			if (action->action &
			    MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT)
				wetuwn -EINVAW;
			action->action |=
				MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
			action->pkt_wefowmat =
				maction->fwow_action_waw.pkt_wefowmat;
			wetuwn 0;
		}
		fawwthwough;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int pawse_fwow_attw(stwuct mwx5_cowe_dev *mdev,
			   stwuct mwx5_fwow_spec *spec,
			   const union ib_fwow_spec *ib_spec,
			   const stwuct ib_fwow_attw *fwow_attw,
			   stwuct mwx5_fwow_act *action, u32 pwev_type)
{
	stwuct mwx5_fwow_context *fwow_context = &spec->fwow_context;
	u32 *match_c = spec->match_cwitewia;
	u32 *match_v = spec->match_vawue;
	void *misc_pawams_c = MWX5_ADDW_OF(fte_match_pawam, match_c,
					   misc_pawametews);
	void *misc_pawams_v = MWX5_ADDW_OF(fte_match_pawam, match_v,
					   misc_pawametews);
	void *misc_pawams2_c = MWX5_ADDW_OF(fte_match_pawam, match_c,
					    misc_pawametews_2);
	void *misc_pawams2_v = MWX5_ADDW_OF(fte_match_pawam, match_v,
					    misc_pawametews_2);
	void *headews_c;
	void *headews_v;
	int match_ipv;
	int wet;

	if (ib_spec->type & IB_FWOW_SPEC_INNEW) {
		headews_c = MWX5_ADDW_OF(fte_match_pawam, match_c,
					 innew_headews);
		headews_v = MWX5_ADDW_OF(fte_match_pawam, match_v,
					 innew_headews);
		match_ipv = MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					ft_fiewd_suppowt.innew_ip_vewsion);
	} ewse {
		headews_c = MWX5_ADDW_OF(fte_match_pawam, match_c,
					 outew_headews);
		headews_v = MWX5_ADDW_OF(fte_match_pawam, match_v,
					 outew_headews);
		match_ipv = MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					ft_fiewd_suppowt.outew_ip_vewsion);
	}

	switch (ib_spec->type & ~IB_FWOW_SPEC_INNEW) {
	case IB_FWOW_SPEC_ETH:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->eth.mask, WAST_ETH_FIEWD))
			wetuwn -EOPNOTSUPP;

		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
					     dmac_47_16),
				ib_spec->eth.mask.dst_mac);
		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
					     dmac_47_16),
				ib_spec->eth.vaw.dst_mac);

		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
					     smac_47_16),
				ib_spec->eth.mask.swc_mac);
		ethew_addw_copy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
					     smac_47_16),
				ib_spec->eth.vaw.swc_mac);

		if (ib_spec->eth.mask.vwan_tag) {
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 cvwan_tag, 1);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 cvwan_tag, 1);

			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 fiwst_vid, ntohs(ib_spec->eth.mask.vwan_tag));
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 fiwst_vid, ntohs(ib_spec->eth.vaw.vwan_tag));

			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 fiwst_cfi,
				 ntohs(ib_spec->eth.mask.vwan_tag) >> 12);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 fiwst_cfi,
				 ntohs(ib_spec->eth.vaw.vwan_tag) >> 12);

			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 fiwst_pwio,
				 ntohs(ib_spec->eth.mask.vwan_tag) >> 13);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 fiwst_pwio,
				 ntohs(ib_spec->eth.vaw.vwan_tag) >> 13);
		}
		MWX5_SET(fte_match_set_wyw_2_4, headews_c,
			 ethewtype, ntohs(ib_spec->eth.mask.ethew_type));
		MWX5_SET(fte_match_set_wyw_2_4, headews_v,
			 ethewtype, ntohs(ib_spec->eth.vaw.ethew_type));
		bweak;
	case IB_FWOW_SPEC_IPV4:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->ipv4.mask, WAST_IPV4_FIEWD))
			wetuwn -EOPNOTSUPP;

		if (match_ipv) {
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 ip_vewsion, 0xf);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 ip_vewsion, MWX5_FS_IPV4_VEWSION);
		} ewse {
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 ethewtype, 0xffff);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 ethewtype, ETH_P_IP);
		}

		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &ib_spec->ipv4.mask.swc_ip,
		       sizeof(ib_spec->ipv4.mask.swc_ip));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &ib_spec->ipv4.vaw.swc_ip,
		       sizeof(ib_spec->ipv4.vaw.swc_ip));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &ib_spec->ipv4.mask.dst_ip,
		       sizeof(ib_spec->ipv4.mask.dst_ip));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &ib_spec->ipv4.vaw.dst_ip,
		       sizeof(ib_spec->ipv4.vaw.dst_ip));

		set_tos(headews_c, headews_v,
			ib_spec->ipv4.mask.tos, ib_spec->ipv4.vaw.tos);

		if (set_pwoto(headews_c, headews_v,
			      ib_spec->ipv4.mask.pwoto,
			      ib_spec->ipv4.vaw.pwoto))
			wetuwn -EINVAW;
		bweak;
	case IB_FWOW_SPEC_IPV6:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->ipv6.mask, WAST_IPV6_FIEWD))
			wetuwn -EOPNOTSUPP;

		if (match_ipv) {
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 ip_vewsion, 0xf);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 ip_vewsion, MWX5_FS_IPV6_VEWSION);
		} ewse {
			MWX5_SET(fte_match_set_wyw_2_4, headews_c,
				 ethewtype, 0xffff);
			MWX5_SET(fte_match_set_wyw_2_4, headews_v,
				 ethewtype, ETH_P_IPV6);
		}

		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       &ib_spec->ipv6.mask.swc_ip,
		       sizeof(ib_spec->ipv6.mask.swc_ip));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       &ib_spec->ipv6.vaw.swc_ip,
		       sizeof(ib_spec->ipv6.vaw.swc_ip));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_c,
				    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       &ib_spec->ipv6.mask.dst_ip,
		       sizeof(ib_spec->ipv6.mask.dst_ip));
		memcpy(MWX5_ADDW_OF(fte_match_set_wyw_2_4, headews_v,
				    dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       &ib_spec->ipv6.vaw.dst_ip,
		       sizeof(ib_spec->ipv6.vaw.dst_ip));

		set_tos(headews_c, headews_v,
			ib_spec->ipv6.mask.twaffic_cwass,
			ib_spec->ipv6.vaw.twaffic_cwass);

		if (set_pwoto(headews_c, headews_v,
			      ib_spec->ipv6.mask.next_hdw,
			      ib_spec->ipv6.vaw.next_hdw))
			wetuwn -EINVAW;

		set_fwow_wabew(misc_pawams_c, misc_pawams_v,
			       ntohw(ib_spec->ipv6.mask.fwow_wabew),
			       ntohw(ib_spec->ipv6.vaw.fwow_wabew),
			       ib_spec->type & IB_FWOW_SPEC_INNEW);
		bweak;
	case IB_FWOW_SPEC_ESP:
		wetuwn -EOPNOTSUPP;
	case IB_FWOW_SPEC_TCP:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->tcp_udp.mask,
					 WAST_TCP_UDP_FIEWD))
			wetuwn -EOPNOTSUPP;

		if (set_pwoto(headews_c, headews_v, 0xff, IPPWOTO_TCP))
			wetuwn -EINVAW;

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, tcp_spowt,
			 ntohs(ib_spec->tcp_udp.mask.swc_powt));
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, tcp_spowt,
			 ntohs(ib_spec->tcp_udp.vaw.swc_powt));

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, tcp_dpowt,
			 ntohs(ib_spec->tcp_udp.mask.dst_powt));
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, tcp_dpowt,
			 ntohs(ib_spec->tcp_udp.vaw.dst_powt));
		bweak;
	case IB_FWOW_SPEC_UDP:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->tcp_udp.mask,
					 WAST_TCP_UDP_FIEWD))
			wetuwn -EOPNOTSUPP;

		if (set_pwoto(headews_c, headews_v, 0xff, IPPWOTO_UDP))
			wetuwn -EINVAW;

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, udp_spowt,
			 ntohs(ib_spec->tcp_udp.mask.swc_powt));
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, udp_spowt,
			 ntohs(ib_spec->tcp_udp.vaw.swc_powt));

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, udp_dpowt,
			 ntohs(ib_spec->tcp_udp.mask.dst_powt));
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, udp_dpowt,
			 ntohs(ib_spec->tcp_udp.vaw.dst_powt));
		bweak;
	case IB_FWOW_SPEC_GWE:
		if (ib_spec->gwe.mask.c_ks_wes0_vew)
			wetuwn -EOPNOTSUPP;

		if (set_pwoto(headews_c, headews_v, 0xff, IPPWOTO_GWE))
			wetuwn -EINVAW;

		MWX5_SET(fte_match_set_wyw_2_4, headews_c, ip_pwotocow,
			 0xff);
		MWX5_SET(fte_match_set_wyw_2_4, headews_v, ip_pwotocow,
			 IPPWOTO_GWE);

		MWX5_SET(fte_match_set_misc, misc_pawams_c, gwe_pwotocow,
			 ntohs(ib_spec->gwe.mask.pwotocow));
		MWX5_SET(fte_match_set_misc, misc_pawams_v, gwe_pwotocow,
			 ntohs(ib_spec->gwe.vaw.pwotocow));

		memcpy(MWX5_ADDW_OF(fte_match_set_misc, misc_pawams_c,
				    gwe_key.nvgwe.hi),
		       &ib_spec->gwe.mask.key,
		       sizeof(ib_spec->gwe.mask.key));
		memcpy(MWX5_ADDW_OF(fte_match_set_misc, misc_pawams_v,
				    gwe_key.nvgwe.hi),
		       &ib_spec->gwe.vaw.key,
		       sizeof(ib_spec->gwe.vaw.key));
		bweak;
	case IB_FWOW_SPEC_MPWS:
		switch (pwev_type) {
		case IB_FWOW_SPEC_UDP:
			if (check_mpws_supp_fiewds(MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
						   ft_fiewd_suppowt.outew_fiwst_mpws_ovew_udp),
						   &ib_spec->mpws.mask.tag))
				wetuwn -EOPNOTSUPP;

			memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_v,
					    outew_fiwst_mpws_ovew_udp),
			       &ib_spec->mpws.vaw.tag,
			       sizeof(ib_spec->mpws.vaw.tag));
			memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_c,
					    outew_fiwst_mpws_ovew_udp),
			       &ib_spec->mpws.mask.tag,
			       sizeof(ib_spec->mpws.mask.tag));
			bweak;
		case IB_FWOW_SPEC_GWE:
			if (check_mpws_supp_fiewds(MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
						   ft_fiewd_suppowt.outew_fiwst_mpws_ovew_gwe),
						   &ib_spec->mpws.mask.tag))
				wetuwn -EOPNOTSUPP;

			memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_v,
					    outew_fiwst_mpws_ovew_gwe),
			       &ib_spec->mpws.vaw.tag,
			       sizeof(ib_spec->mpws.vaw.tag));
			memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_c,
					    outew_fiwst_mpws_ovew_gwe),
			       &ib_spec->mpws.mask.tag,
			       sizeof(ib_spec->mpws.mask.tag));
			bweak;
		defauwt:
			if (ib_spec->type & IB_FWOW_SPEC_INNEW) {
				if (check_mpws_supp_fiewds(MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
							   ft_fiewd_suppowt.innew_fiwst_mpws),
							   &ib_spec->mpws.mask.tag))
					wetuwn -EOPNOTSUPP;

				memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_v,
						    innew_fiwst_mpws),
				       &ib_spec->mpws.vaw.tag,
				       sizeof(ib_spec->mpws.vaw.tag));
				memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_c,
						    innew_fiwst_mpws),
				       &ib_spec->mpws.mask.tag,
				       sizeof(ib_spec->mpws.mask.tag));
			} ewse {
				if (check_mpws_supp_fiewds(MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
							   ft_fiewd_suppowt.outew_fiwst_mpws),
							   &ib_spec->mpws.mask.tag))
					wetuwn -EOPNOTSUPP;

				memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_v,
						    outew_fiwst_mpws),
				       &ib_spec->mpws.vaw.tag,
				       sizeof(ib_spec->mpws.vaw.tag));
				memcpy(MWX5_ADDW_OF(fte_match_set_misc2, misc_pawams2_c,
						    outew_fiwst_mpws),
				       &ib_spec->mpws.mask.tag,
				       sizeof(ib_spec->mpws.mask.tag));
			}
		}
		bweak;
	case IB_FWOW_SPEC_VXWAN_TUNNEW:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->tunnew.mask,
					 WAST_TUNNEW_FIEWD))
			wetuwn -EOPNOTSUPP;

		MWX5_SET(fte_match_set_misc, misc_pawams_c, vxwan_vni,
			 ntohw(ib_spec->tunnew.mask.tunnew_id));
		MWX5_SET(fte_match_set_misc, misc_pawams_v, vxwan_vni,
			 ntohw(ib_spec->tunnew.vaw.tunnew_id));
		bweak;
	case IB_FWOW_SPEC_ACTION_TAG:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->fwow_tag,
					 WAST_FWOW_TAG_FIEWD))
			wetuwn -EOPNOTSUPP;
		if (ib_spec->fwow_tag.tag_id >= BIT(24))
			wetuwn -EINVAW;

		fwow_context->fwow_tag = ib_spec->fwow_tag.tag_id;
		fwow_context->fwags |= FWOW_CONTEXT_HAS_TAG;
		bweak;
	case IB_FWOW_SPEC_ACTION_DWOP:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->dwop,
					 WAST_DWOP_FIEWD))
			wetuwn -EOPNOTSUPP;
		action->action |= MWX5_FWOW_CONTEXT_ACTION_DWOP;
		bweak;
	case IB_FWOW_SPEC_ACTION_HANDWE:
		wet = pawse_fwow_fwow_action(to_mfwow_act(ib_spec->action.act),
			fwow_attw->fwags & IB_FWOW_ATTW_FWAGS_EGWESS, action);
		if (wet)
			wetuwn wet;
		bweak;
	case IB_FWOW_SPEC_ACTION_COUNT:
		if (FIEWDS_NOT_SUPPOWTED(ib_spec->fwow_count,
					 WAST_COUNTEWS_FIEWD))
			wetuwn -EOPNOTSUPP;

		/* fow now suppowt onwy one countews spec pew fwow */
		if (action->action & MWX5_FWOW_CONTEXT_ACTION_COUNT)
			wetuwn -EINVAW;

		action->countews = ib_spec->fwow_count.countews;
		action->action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* If a fwow couwd catch both muwticast and unicast packets,
 * it won't faww into the muwticast fwow steewing tabwe and this wuwe
 * couwd steaw othew muwticast packets.
 */
static boow fwow_is_muwticast_onwy(const stwuct ib_fwow_attw *ib_attw)
{
	union ib_fwow_spec *fwow_spec;

	if (ib_attw->type != IB_FWOW_ATTW_NOWMAW ||
	    ib_attw->num_of_specs < 1)
		wetuwn fawse;

	fwow_spec = (union ib_fwow_spec *)(ib_attw + 1);
	if (fwow_spec->type == IB_FWOW_SPEC_IPV4) {
		stwuct ib_fwow_spec_ipv4 *ipv4_spec;

		ipv4_spec = (stwuct ib_fwow_spec_ipv4 *)fwow_spec;
		if (ipv4_is_muwticast(ipv4_spec->vaw.dst_ip))
			wetuwn twue;

		wetuwn fawse;
	}

	if (fwow_spec->type == IB_FWOW_SPEC_ETH) {
		stwuct ib_fwow_spec_eth *eth_spec;

		eth_spec = (stwuct ib_fwow_spec_eth *)fwow_spec;
		wetuwn is_muwticast_ethew_addw(eth_spec->mask.dst_mac) &&
		       is_muwticast_ethew_addw(eth_spec->vaw.dst_mac);
	}

	wetuwn fawse;
}

static boow is_vawid_ethewtype(stwuct mwx5_cowe_dev *mdev,
			       const stwuct ib_fwow_attw *fwow_attw,
			       boow check_innew)
{
	union ib_fwow_spec *ib_spec = (union ib_fwow_spec *)(fwow_attw + 1);
	int match_ipv = check_innew ?
			MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					ft_fiewd_suppowt.innew_ip_vewsion) :
			MWX5_CAP_FWOWTABWE_NIC_WX(mdev,
					ft_fiewd_suppowt.outew_ip_vewsion);
	int innew_bit = check_innew ? IB_FWOW_SPEC_INNEW : 0;
	boow ipv4_spec_vawid, ipv6_spec_vawid;
	unsigned int ip_spec_type = 0;
	boow has_ethewtype = fawse;
	unsigned int spec_index;
	boow mask_vawid = twue;
	u16 eth_type = 0;
	boow type_vawid;

	/* Vawidate that ethewtype is cowwect */
	fow (spec_index = 0; spec_index < fwow_attw->num_of_specs; spec_index++) {
		if ((ib_spec->type == (IB_FWOW_SPEC_ETH | innew_bit)) &&
		    ib_spec->eth.mask.ethew_type) {
			mask_vawid = (ib_spec->eth.mask.ethew_type ==
				      htons(0xffff));
			has_ethewtype = twue;
			eth_type = ntohs(ib_spec->eth.vaw.ethew_type);
		} ewse if ((ib_spec->type == (IB_FWOW_SPEC_IPV4 | innew_bit)) ||
			   (ib_spec->type == (IB_FWOW_SPEC_IPV6 | innew_bit))) {
			ip_spec_type = ib_spec->type;
		}
		ib_spec = (void *)ib_spec + ib_spec->size;
	}

	type_vawid = (!has_ethewtype) || (!ip_spec_type);
	if (!type_vawid && mask_vawid) {
		ipv4_spec_vawid = (eth_type == ETH_P_IP) &&
			(ip_spec_type == (IB_FWOW_SPEC_IPV4 | innew_bit));
		ipv6_spec_vawid = (eth_type == ETH_P_IPV6) &&
			(ip_spec_type == (IB_FWOW_SPEC_IPV6 | innew_bit));

		type_vawid = (ipv4_spec_vawid) || (ipv6_spec_vawid) ||
			     (((eth_type == ETH_P_MPWS_UC) ||
			       (eth_type == ETH_P_MPWS_MC)) && match_ipv);
	}

	wetuwn type_vawid;
}

static boow is_vawid_attw(stwuct mwx5_cowe_dev *mdev,
			  const stwuct ib_fwow_attw *fwow_attw)
{
	wetuwn is_vawid_ethewtype(mdev, fwow_attw, fawse) &&
	       is_vawid_ethewtype(mdev, fwow_attw, twue);
}

static void put_fwow_tabwe(stwuct mwx5_ib_dev *dev,
			   stwuct mwx5_ib_fwow_pwio *pwio, boow ft_added)
{
	pwio->wefcount -= !!ft_added;
	if (!pwio->wefcount) {
		mwx5_destwoy_fwow_tabwe(pwio->fwow_tabwe);
		pwio->fwow_tabwe = NUWW;
	}
}

static int mwx5_ib_destwoy_fwow(stwuct ib_fwow *fwow_id)
{
	stwuct mwx5_ib_fwow_handwew *handwew = containew_of(fwow_id,
							  stwuct mwx5_ib_fwow_handwew,
							  ibfwow);
	stwuct mwx5_ib_fwow_handwew *itew, *tmp;
	stwuct mwx5_ib_dev *dev = handwew->dev;

	mutex_wock(&dev->fwow_db->wock);

	wist_fow_each_entwy_safe(itew, tmp, &handwew->wist, wist) {
		mwx5_dew_fwow_wuwes(itew->wuwe);
		put_fwow_tabwe(dev, itew->pwio, twue);
		wist_dew(&itew->wist);
		kfwee(itew);
	}

	mwx5_dew_fwow_wuwes(handwew->wuwe);
	put_fwow_tabwe(dev, handwew->pwio, twue);
	mwx5_ib_countews_cweaw_descwiption(handwew->ibcountews);
	mutex_unwock(&dev->fwow_db->wock);
	if (handwew->fwow_matchew)
		atomic_dec(&handwew->fwow_matchew->usecnt);
	kfwee(handwew);

	wetuwn 0;
}

static int ib_pwio_to_cowe_pwio(unsigned int pwiowity, boow dont_twap)
{
	pwiowity *= 2;
	if (!dont_twap)
		pwiowity++;
	wetuwn pwiowity;
}

enum fwow_tabwe_type {
	MWX5_IB_FT_WX,
	MWX5_IB_FT_TX
};

#define MWX5_FS_MAX_TYPES	 6
#define MWX5_FS_MAX_ENTWIES	 BIT(16)

static boow mwx5_ib_shawed_ft_awwowed(stwuct ib_device *device)
{
	stwuct mwx5_ib_dev *dev = to_mdev(device);

	wetuwn MWX5_CAP_GEN(dev->mdev, shawed_object_to_usew_object_awwowed);
}

static stwuct mwx5_ib_fwow_pwio *_get_pwio(stwuct mwx5_ib_dev *dev,
					   stwuct mwx5_fwow_namespace *ns,
					   stwuct mwx5_ib_fwow_pwio *pwio,
					   int pwiowity,
					   int num_entwies, int num_gwoups,
					   u32 fwags)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_tabwe *ft;

	ft_attw.pwio = pwiowity;
	ft_attw.max_fte = num_entwies;
	ft_attw.fwags = fwags;
	ft_attw.autogwoup.max_num_gwoups = num_gwoups;
	ft = mwx5_cweate_auto_gwouped_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft))
		wetuwn EWW_CAST(ft);

	pwio->fwow_tabwe = ft;
	pwio->wefcount = 0;
	wetuwn pwio;
}

static stwuct mwx5_ib_fwow_pwio *get_fwow_tabwe(stwuct mwx5_ib_dev *dev,
						stwuct ib_fwow_attw *fwow_attw,
						enum fwow_tabwe_type ft_type)
{
	boow dont_twap = fwow_attw->fwags & IB_FWOW_ATTW_FWAGS_DONT_TWAP;
	stwuct mwx5_fwow_namespace *ns = NUWW;
	enum mwx5_fwow_namespace_type fn_type;
	stwuct mwx5_ib_fwow_pwio *pwio;
	stwuct mwx5_fwow_tabwe *ft;
	int max_tabwe_size;
	int num_entwies;
	int num_gwoups;
	boow esw_encap;
	u32 fwags = 0;
	int pwiowity;

	max_tabwe_size = BIT(MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev,
						       wog_max_ft_size));
	esw_encap = mwx5_eswitch_get_encap_mode(dev->mdev) !=
		DEVWINK_ESWITCH_ENCAP_MODE_NONE;
	switch (fwow_attw->type) {
	case IB_FWOW_ATTW_NOWMAW:
		if (fwow_is_muwticast_onwy(fwow_attw) && !dont_twap)
			pwiowity = MWX5_IB_FWOW_MCAST_PWIO;
		ewse
			pwiowity = ib_pwio_to_cowe_pwio(fwow_attw->pwiowity,
							dont_twap);
		if (ft_type == MWX5_IB_FT_WX) {
			fn_type = MWX5_FWOW_NAMESPACE_BYPASS;
			pwio = &dev->fwow_db->pwios[pwiowity];
			if (!dev->is_wep && !esw_encap &&
			    MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev, decap))
				fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_DECAP;
			if (!dev->is_wep && !esw_encap &&
			    MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev,
						      wefowmat_w3_tunnew_to_w2))
				fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
		} ewse {
			max_tabwe_size = BIT(MWX5_CAP_FWOWTABWE_NIC_TX(
				dev->mdev, wog_max_ft_size));
			fn_type = MWX5_FWOW_NAMESPACE_EGWESS;
			pwio = &dev->fwow_db->egwess_pwios[pwiowity];
			if (!dev->is_wep && !esw_encap &&
			    MWX5_CAP_FWOWTABWE_NIC_TX(dev->mdev, wefowmat))
				fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
		}
		ns = mwx5_get_fwow_namespace(dev->mdev, fn_type);
		num_entwies = MWX5_FS_MAX_ENTWIES;
		num_gwoups = MWX5_FS_MAX_TYPES;
		bweak;
	case IB_FWOW_ATTW_AWW_DEFAUWT:
	case IB_FWOW_ATTW_MC_DEFAUWT:
		ns = mwx5_get_fwow_namespace(dev->mdev,
					     MWX5_FWOW_NAMESPACE_WEFTOVEWS);
		buiwd_weftovews_ft_pawam(&pwiowity, &num_entwies, &num_gwoups);
		pwio = &dev->fwow_db->pwios[MWX5_IB_FWOW_WEFTOVEWS_PWIO];
		bweak;
	case IB_FWOW_ATTW_SNIFFEW:
		if (!MWX5_CAP_FWOWTABWE(dev->mdev,
					awwow_sniffew_and_nic_wx_shawed_tiw))
			wetuwn EWW_PTW(-EOPNOTSUPP);

		ns = mwx5_get_fwow_namespace(
			dev->mdev, ft_type == MWX5_IB_FT_WX ?
					   MWX5_FWOW_NAMESPACE_SNIFFEW_WX :
					   MWX5_FWOW_NAMESPACE_SNIFFEW_TX);

		pwio = &dev->fwow_db->sniffew[ft_type];
		pwiowity = 0;
		num_entwies = 1;
		num_gwoups = 1;
		bweak;
	defauwt:
		bweak;
	}

	if (!ns)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	max_tabwe_size = min_t(int, num_entwies, max_tabwe_size);

	ft = pwio->fwow_tabwe;
	if (!ft)
		wetuwn _get_pwio(dev, ns, pwio, pwiowity, max_tabwe_size,
				 num_gwoups, fwags);

	wetuwn pwio;
}

enum {
	WDMA_WX_ECN_OPCOUNTEW_PWIO,
	WDMA_WX_CNP_OPCOUNTEW_PWIO,
};

enum {
	WDMA_TX_CNP_OPCOUNTEW_PWIO,
};

static int set_vhca_powt_spec(stwuct mwx5_ib_dev *dev, u32 powt_num,
			      stwuct mwx5_fwow_spec *spec)
{
	if (!MWX5_CAP_FWOWTABWE_WDMA_WX(dev->mdev,
					ft_fiewd_suppowt.souwce_vhca_powt) ||
	    !MWX5_CAP_FWOWTABWE_WDMA_TX(dev->mdev,
					ft_fiewd_suppowt.souwce_vhca_powt))
		wetuwn -EOPNOTSUPP;

	MWX5_SET_TO_ONES(fte_match_pawam, &spec->match_cwitewia,
			 misc_pawametews.souwce_vhca_powt);
	MWX5_SET(fte_match_pawam, &spec->match_vawue,
		 misc_pawametews.souwce_vhca_powt, powt_num);

	wetuwn 0;
}

static int set_ecn_ce_spec(stwuct mwx5_ib_dev *dev, u32 powt_num,
			   stwuct mwx5_fwow_spec *spec, int ipv)
{
	if (!MWX5_CAP_FWOWTABWE_WDMA_WX(dev->mdev,
					ft_fiewd_suppowt.outew_ip_vewsion))
		wetuwn -EOPNOTSUPP;

	if (mwx5_cowe_mp_enabwed(dev->mdev) &&
	    set_vhca_powt_spec(dev, powt_num, spec))
		wetuwn -EOPNOTSUPP;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 outew_headews.ip_ecn);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_ecn,
		 INET_ECN_CE);
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 outew_headews.ip_vewsion);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.ip_vewsion,
		 ipv);

	spec->match_cwitewia_enabwe =
		get_match_cwitewia_enabwe(spec->match_cwitewia);

	wetuwn 0;
}

static int set_cnp_spec(stwuct mwx5_ib_dev *dev, u32 powt_num,
			stwuct mwx5_fwow_spec *spec)
{
	if (mwx5_cowe_mp_enabwed(dev->mdev) &&
	    set_vhca_powt_spec(dev, powt_num, spec))
		wetuwn -EOPNOTSUPP;

	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
			 misc_pawametews.bth_opcode);
	MWX5_SET(fte_match_pawam, spec->match_vawue, misc_pawametews.bth_opcode,
		 IB_BTH_OPCODE_CNP);

	spec->match_cwitewia_enabwe =
		get_match_cwitewia_enabwe(spec->match_cwitewia);

	wetuwn 0;
}

int mwx5_ib_fs_add_op_fc(stwuct mwx5_ib_dev *dev, u32 powt_num,
			 stwuct mwx5_ib_op_fc *opfc,
			 enum mwx5_ib_optionaw_countew_type type)
{
	enum mwx5_fwow_namespace_type fn_type;
	int pwiowity, i, eww, spec_num;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_destination dst;
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_ib_fwow_pwio *pwio;
	stwuct mwx5_fwow_spec *spec;

	spec = kcawwoc(MAX_OPFC_WUWES, sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	switch (type) {
	case MWX5_IB_OPCOUNTEW_CC_WX_CE_PKTS:
		if (set_ecn_ce_spec(dev, powt_num, &spec[0],
				    MWX5_FS_IPV4_VEWSION) ||
		    set_ecn_ce_spec(dev, powt_num, &spec[1],
				    MWX5_FS_IPV6_VEWSION)) {
			eww = -EOPNOTSUPP;
			goto fwee;
		}
		spec_num = 2;
		fn_type = MWX5_FWOW_NAMESPACE_WDMA_WX_COUNTEWS;
		pwiowity = WDMA_WX_ECN_OPCOUNTEW_PWIO;
		bweak;

	case MWX5_IB_OPCOUNTEW_CC_WX_CNP_PKTS:
		if (!MWX5_CAP_FWOWTABWE(dev->mdev,
					ft_fiewd_suppowt_2_nic_weceive_wdma.bth_opcode) ||
		    set_cnp_spec(dev, powt_num, &spec[0])) {
			eww = -EOPNOTSUPP;
			goto fwee;
		}
		spec_num = 1;
		fn_type = MWX5_FWOW_NAMESPACE_WDMA_WX_COUNTEWS;
		pwiowity = WDMA_WX_CNP_OPCOUNTEW_PWIO;
		bweak;

	case MWX5_IB_OPCOUNTEW_CC_TX_CNP_PKTS:
		if (!MWX5_CAP_FWOWTABWE(dev->mdev,
					ft_fiewd_suppowt_2_nic_twansmit_wdma.bth_opcode) ||
		    set_cnp_spec(dev, powt_num, &spec[0])) {
			eww = -EOPNOTSUPP;
			goto fwee;
		}
		spec_num = 1;
		fn_type = MWX5_FWOW_NAMESPACE_WDMA_TX_COUNTEWS;
		pwiowity = WDMA_TX_CNP_OPCOUNTEW_PWIO;
		bweak;

	defauwt:
		eww = -EOPNOTSUPP;
		goto fwee;
	}

	ns = mwx5_get_fwow_namespace(dev->mdev, fn_type);
	if (!ns) {
		eww = -EOPNOTSUPP;
		goto fwee;
	}

	pwio = &dev->fwow_db->opfcs[type];
	if (!pwio->fwow_tabwe) {
		pwio = _get_pwio(dev, ns, pwio, pwiowity,
				 dev->num_powts * MAX_OPFC_WUWES, 1, 0);
		if (IS_EWW(pwio)) {
			eww = PTW_EWW(pwio);
			goto fwee;
		}
	}

	dst.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dst.countew_id = mwx5_fc_id(opfc->fc);

	fwow_act.action =
		MWX5_FWOW_CONTEXT_ACTION_COUNT | MWX5_FWOW_CONTEXT_ACTION_AWWOW;

	fow (i = 0; i < spec_num; i++) {
		opfc->wuwe[i] = mwx5_add_fwow_wuwes(pwio->fwow_tabwe, &spec[i],
						    &fwow_act, &dst, 1);
		if (IS_EWW(opfc->wuwe[i])) {
			eww = PTW_EWW(opfc->wuwe[i]);
			goto dew_wuwes;
		}
	}
	pwio->wefcount += spec_num;
	kfwee(spec);

	wetuwn 0;

dew_wuwes:
	fow (i -= 1; i >= 0; i--)
		mwx5_dew_fwow_wuwes(opfc->wuwe[i]);
	put_fwow_tabwe(dev, pwio, fawse);
fwee:
	kfwee(spec);
	wetuwn eww;
}

void mwx5_ib_fs_wemove_op_fc(stwuct mwx5_ib_dev *dev,
			     stwuct mwx5_ib_op_fc *opfc,
			     enum mwx5_ib_optionaw_countew_type type)
{
	int i;

	fow (i = 0; i < MAX_OPFC_WUWES && opfc->wuwe[i]; i++) {
		mwx5_dew_fwow_wuwes(opfc->wuwe[i]);
		put_fwow_tabwe(dev, &dev->fwow_db->opfcs[type], twue);
	}
}

static void set_undewway_qp(stwuct mwx5_ib_dev *dev,
			    stwuct mwx5_fwow_spec *spec,
			    u32 undewway_qpn)
{
	void *misc_pawams_c = MWX5_ADDW_OF(fte_match_pawam,
					   spec->match_cwitewia,
					   misc_pawametews);
	void *misc_pawams_v = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
					   misc_pawametews);

	if (undewway_qpn &&
	    MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev,
				      ft_fiewd_suppowt.bth_dst_qp)) {
		MWX5_SET(fte_match_set_misc,
			 misc_pawams_v, bth_dst_qp, undewway_qpn);
		MWX5_SET(fte_match_set_misc,
			 misc_pawams_c, bth_dst_qp, 0xffffff);
	}
}

static void mwx5_ib_set_wuwe_souwce_powt(stwuct mwx5_ib_dev *dev,
					 stwuct mwx5_fwow_spec *spec,
					 stwuct mwx5_eswitch_wep *wep)
{
	stwuct mwx5_eswitch *esw = dev->mdev->pwiv.eswitch;
	void *misc;

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    misc_pawametews_2);

		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_fow_match(wep->esw,
								   wep->vpowt));
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    misc_pawametews_2);

		MWX5_SET(fte_match_set_misc2, misc, metadata_weg_c_0,
			 mwx5_eswitch_get_vpowt_metadata_mask());
	} ewse {
		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue,
				    misc_pawametews);

		MWX5_SET(fte_match_set_misc, misc, souwce_powt, wep->vpowt);

		misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia,
				    misc_pawametews);

		MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_powt);
	}
}

static stwuct mwx5_ib_fwow_handwew *_cweate_fwow_wuwe(stwuct mwx5_ib_dev *dev,
						      stwuct mwx5_ib_fwow_pwio *ft_pwio,
						      const stwuct ib_fwow_attw *fwow_attw,
						      stwuct mwx5_fwow_destination *dst,
						      u32 undewway_qpn,
						      stwuct mwx5_ib_cweate_fwow *ucmd)
{
	stwuct mwx5_fwow_tabwe	*ft = ft_pwio->fwow_tabwe;
	stwuct mwx5_ib_fwow_handwew *handwew;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_fwow_destination dest_aww[2] = {};
	stwuct mwx5_fwow_destination *wuwe_dst = dest_aww;
	const void *ib_fwow = (const void *)fwow_attw + sizeof(*fwow_attw);
	unsigned int spec_index;
	u32 pwev_type = 0;
	int eww = 0;
	int dest_num = 0;
	boow is_egwess = fwow_attw->fwags & IB_FWOW_ATTW_FWAGS_EGWESS;

	if (!is_vawid_attw(dev->mdev, fwow_attw))
		wetuwn EWW_PTW(-EINVAW);

	if (dev->is_wep && is_egwess)
		wetuwn EWW_PTW(-EINVAW);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	handwew = kzawwoc(sizeof(*handwew), GFP_KEWNEW);
	if (!handwew || !spec) {
		eww = -ENOMEM;
		goto fwee;
	}

	INIT_WIST_HEAD(&handwew->wist);

	fow (spec_index = 0; spec_index < fwow_attw->num_of_specs; spec_index++) {
		eww = pawse_fwow_attw(dev->mdev, spec,
				      ib_fwow, fwow_attw, &fwow_act,
				      pwev_type);
		if (eww < 0)
			goto fwee;

		pwev_type = ((union ib_fwow_spec *)ib_fwow)->type;
		ib_fwow += ((union ib_fwow_spec *)ib_fwow)->size;
	}

	if (dst && !(fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_DWOP)) {
		memcpy(&dest_aww[0], dst, sizeof(*dst));
		dest_num++;
	}

	if (!fwow_is_muwticast_onwy(fwow_attw))
		set_undewway_qp(dev, spec, undewway_qpn);

	if (dev->is_wep && fwow_attw->type != IB_FWOW_ATTW_SNIFFEW) {
		stwuct mwx5_eswitch_wep *wep;

		wep = dev->powt[fwow_attw->powt - 1].wep;
		if (!wep) {
			eww = -EINVAW;
			goto fwee;
		}

		mwx5_ib_set_wuwe_souwce_powt(dev, spec, wep);
	}

	spec->match_cwitewia_enabwe = get_match_cwitewia_enabwe(spec->match_cwitewia);

	if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		stwuct mwx5_ib_mcountews *mcountews;

		eww = mwx5_ib_fwow_countews_set_data(fwow_act.countews, ucmd);
		if (eww)
			goto fwee;

		mcountews = to_mcountews(fwow_act.countews);
		handwew->ibcountews = fwow_act.countews;
		dest_aww[dest_num].type =
			MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dest_aww[dest_num].countew_id =
			mwx5_fc_id(mcountews->hw_cntws_hndw);
		dest_num++;
	}

	if (fwow_act.action & MWX5_FWOW_CONTEXT_ACTION_DWOP) {
		if (!dest_num)
			wuwe_dst = NUWW;
	} ewse {
		if (fwow_attw->fwags & IB_FWOW_ATTW_FWAGS_DONT_TWAP)
			fwow_act.action |=
				MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_PWIO;
		if (is_egwess)
			fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_AWWOW;
		ewse if (dest_num)
			fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	}

	if ((spec->fwow_context.fwags & FWOW_CONTEXT_HAS_TAG)  &&
	    (fwow_attw->type == IB_FWOW_ATTW_AWW_DEFAUWT ||
	     fwow_attw->type == IB_FWOW_ATTW_MC_DEFAUWT)) {
		mwx5_ib_wawn(dev, "Fwow tag %u and attwibute type %x isn't awwowed in weftovews\n",
			     spec->fwow_context.fwow_tag, fwow_attw->type);
		eww = -EINVAW;
		goto fwee;
	}
	handwew->wuwe = mwx5_add_fwow_wuwes(ft, spec,
					    &fwow_act,
					    wuwe_dst, dest_num);

	if (IS_EWW(handwew->wuwe)) {
		eww = PTW_EWW(handwew->wuwe);
		goto fwee;
	}

	ft_pwio->wefcount++;
	handwew->pwio = ft_pwio;
	handwew->dev = dev;

	ft_pwio->fwow_tabwe = ft;
fwee:
	if (eww && handwew) {
		mwx5_ib_countews_cweaw_descwiption(handwew->ibcountews);
		kfwee(handwew);
	}
	kvfwee(spec);
	wetuwn eww ? EWW_PTW(eww) : handwew;
}

static stwuct mwx5_ib_fwow_handwew *cweate_fwow_wuwe(stwuct mwx5_ib_dev *dev,
						     stwuct mwx5_ib_fwow_pwio *ft_pwio,
						     const stwuct ib_fwow_attw *fwow_attw,
						     stwuct mwx5_fwow_destination *dst)
{
	wetuwn _cweate_fwow_wuwe(dev, ft_pwio, fwow_attw, dst, 0, NUWW);
}

enum {
	WEFTOVEWS_MC,
	WEFTOVEWS_UC,
};

static stwuct mwx5_ib_fwow_handwew *cweate_weftovews_wuwe(stwuct mwx5_ib_dev *dev,
							  stwuct mwx5_ib_fwow_pwio *ft_pwio,
							  stwuct ib_fwow_attw *fwow_attw,
							  stwuct mwx5_fwow_destination *dst)
{
	stwuct mwx5_ib_fwow_handwew *handwew_ucast = NUWW;
	stwuct mwx5_ib_fwow_handwew *handwew = NUWW;

	static stwuct {
		stwuct ib_fwow_attw	fwow_attw;
		stwuct ib_fwow_spec_eth eth_fwow;
	} weftovews_specs[] = {
		[WEFTOVEWS_MC] = {
			.fwow_attw = {
				.num_of_specs = 1,
				.size = sizeof(weftovews_specs[0])
			},
			.eth_fwow = {
				.type = IB_FWOW_SPEC_ETH,
				.size = sizeof(stwuct ib_fwow_spec_eth),
				.mask = {.dst_mac = {0x1} },
				.vaw =  {.dst_mac = {0x1} }
			}
		},
		[WEFTOVEWS_UC] = {
			.fwow_attw = {
				.num_of_specs = 1,
				.size = sizeof(weftovews_specs[0])
			},
			.eth_fwow = {
				.type = IB_FWOW_SPEC_ETH,
				.size = sizeof(stwuct ib_fwow_spec_eth),
				.mask = {.dst_mac = {0x1} },
				.vaw = {.dst_mac = {} }
			}
		}
	};

	handwew = cweate_fwow_wuwe(dev, ft_pwio,
				   &weftovews_specs[WEFTOVEWS_MC].fwow_attw,
				   dst);
	if (!IS_EWW(handwew) &&
	    fwow_attw->type == IB_FWOW_ATTW_AWW_DEFAUWT) {
		handwew_ucast = cweate_fwow_wuwe(dev, ft_pwio,
						 &weftovews_specs[WEFTOVEWS_UC].fwow_attw,
						 dst);
		if (IS_EWW(handwew_ucast)) {
			mwx5_dew_fwow_wuwes(handwew->wuwe);
			ft_pwio->wefcount--;
			kfwee(handwew);
			handwew = handwew_ucast;
		} ewse {
			wist_add(&handwew_ucast->wist, &handwew->wist);
		}
	}

	wetuwn handwew;
}

static stwuct mwx5_ib_fwow_handwew *cweate_sniffew_wuwe(stwuct mwx5_ib_dev *dev,
							stwuct mwx5_ib_fwow_pwio *ft_wx,
							stwuct mwx5_ib_fwow_pwio *ft_tx,
							stwuct mwx5_fwow_destination *dst)
{
	stwuct mwx5_ib_fwow_handwew *handwew_wx;
	stwuct mwx5_ib_fwow_handwew *handwew_tx;
	int eww;
	static const stwuct ib_fwow_attw fwow_attw  = {
		.num_of_specs = 0,
		.type = IB_FWOW_ATTW_SNIFFEW,
		.size = sizeof(fwow_attw)
	};

	handwew_wx = cweate_fwow_wuwe(dev, ft_wx, &fwow_attw, dst);
	if (IS_EWW(handwew_wx)) {
		eww = PTW_EWW(handwew_wx);
		goto eww;
	}

	handwew_tx = cweate_fwow_wuwe(dev, ft_tx, &fwow_attw, dst);
	if (IS_EWW(handwew_tx)) {
		eww = PTW_EWW(handwew_tx);
		goto eww_tx;
	}

	wist_add(&handwew_tx->wist, &handwew_wx->wist);

	wetuwn handwew_wx;

eww_tx:
	mwx5_dew_fwow_wuwes(handwew_wx->wuwe);
	ft_wx->wefcount--;
	kfwee(handwew_wx);
eww:
	wetuwn EWW_PTW(eww);
}

static stwuct ib_fwow *mwx5_ib_cweate_fwow(stwuct ib_qp *qp,
					   stwuct ib_fwow_attw *fwow_attw,
					   stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(qp->device);
	stwuct mwx5_ib_qp *mqp = to_mqp(qp);
	stwuct mwx5_ib_fwow_handwew *handwew = NUWW;
	stwuct mwx5_fwow_destination *dst = NUWW;
	stwuct mwx5_ib_fwow_pwio *ft_pwio_tx = NUWW;
	stwuct mwx5_ib_fwow_pwio *ft_pwio;
	boow is_egwess = fwow_attw->fwags & IB_FWOW_ATTW_FWAGS_EGWESS;
	stwuct mwx5_ib_cweate_fwow *ucmd = NUWW, ucmd_hdw;
	size_t min_ucmd_sz, wequiwed_ucmd_sz;
	int eww;
	int undewway_qpn;

	if (udata && udata->inwen) {
		min_ucmd_sz = offsetofend(stwuct mwx5_ib_cweate_fwow, wesewved);
		if (udata->inwen < min_ucmd_sz)
			wetuwn EWW_PTW(-EOPNOTSUPP);

		eww = ib_copy_fwom_udata(&ucmd_hdw, udata, min_ucmd_sz);
		if (eww)
			wetuwn EWW_PTW(eww);

		/* cuwwentwy suppowts onwy one countews data */
		if (ucmd_hdw.ncountews_data > 1)
			wetuwn EWW_PTW(-EINVAW);

		wequiwed_ucmd_sz = min_ucmd_sz +
			sizeof(stwuct mwx5_ib_fwow_countews_data) *
			ucmd_hdw.ncountews_data;
		if (udata->inwen > wequiwed_ucmd_sz &&
		    !ib_is_udata_cweawed(udata, wequiwed_ucmd_sz,
					 udata->inwen - wequiwed_ucmd_sz))
			wetuwn EWW_PTW(-EOPNOTSUPP);

		ucmd = kzawwoc(wequiwed_ucmd_sz, GFP_KEWNEW);
		if (!ucmd)
			wetuwn EWW_PTW(-ENOMEM);

		eww = ib_copy_fwom_udata(ucmd, udata, wequiwed_ucmd_sz);
		if (eww)
			goto fwee_ucmd;
	}

	if (fwow_attw->pwiowity > MWX5_IB_FWOW_WAST_PWIO) {
		eww = -ENOMEM;
		goto fwee_ucmd;
	}

	if (fwow_attw->fwags &
	    ~(IB_FWOW_ATTW_FWAGS_DONT_TWAP | IB_FWOW_ATTW_FWAGS_EGWESS)) {
		eww = -EINVAW;
		goto fwee_ucmd;
	}

	if (is_egwess &&
	    (fwow_attw->type == IB_FWOW_ATTW_AWW_DEFAUWT ||
	     fwow_attw->type == IB_FWOW_ATTW_MC_DEFAUWT)) {
		eww = -EINVAW;
		goto fwee_ucmd;
	}

	dst = kzawwoc(sizeof(*dst), GFP_KEWNEW);
	if (!dst) {
		eww = -ENOMEM;
		goto fwee_ucmd;
	}

	mutex_wock(&dev->fwow_db->wock);

	ft_pwio = get_fwow_tabwe(dev, fwow_attw,
				 is_egwess ? MWX5_IB_FT_TX : MWX5_IB_FT_WX);
	if (IS_EWW(ft_pwio)) {
		eww = PTW_EWW(ft_pwio);
		goto unwock;
	}
	if (fwow_attw->type == IB_FWOW_ATTW_SNIFFEW) {
		ft_pwio_tx = get_fwow_tabwe(dev, fwow_attw, MWX5_IB_FT_TX);
		if (IS_EWW(ft_pwio_tx)) {
			eww = PTW_EWW(ft_pwio_tx);
			ft_pwio_tx = NUWW;
			goto destwoy_ft;
		}
	}

	if (is_egwess) {
		dst->type = MWX5_FWOW_DESTINATION_TYPE_POWT;
	} ewse {
		dst->type = MWX5_FWOW_DESTINATION_TYPE_TIW;
		if (mqp->is_wss)
			dst->tiw_num = mqp->wss_qp.tiwn;
		ewse
			dst->tiw_num = mqp->waw_packet_qp.wq.tiwn;
	}

	switch (fwow_attw->type) {
	case IB_FWOW_ATTW_NOWMAW:
		undewway_qpn = (mqp->fwags & IB_QP_CWEATE_SOUWCE_QPN) ?
				       mqp->undewway_qpn :
				       0;
		handwew = _cweate_fwow_wuwe(dev, ft_pwio, fwow_attw, dst,
					    undewway_qpn, ucmd);
		bweak;
	case IB_FWOW_ATTW_AWW_DEFAUWT:
	case IB_FWOW_ATTW_MC_DEFAUWT:
		handwew = cweate_weftovews_wuwe(dev, ft_pwio, fwow_attw, dst);
		bweak;
	case IB_FWOW_ATTW_SNIFFEW:
		handwew = cweate_sniffew_wuwe(dev, ft_pwio, ft_pwio_tx, dst);
		bweak;
	defauwt:
		eww = -EINVAW;
		goto destwoy_ft;
	}

	if (IS_EWW(handwew)) {
		eww = PTW_EWW(handwew);
		handwew = NUWW;
		goto destwoy_ft;
	}

	mutex_unwock(&dev->fwow_db->wock);
	kfwee(dst);
	kfwee(ucmd);

	wetuwn &handwew->ibfwow;

destwoy_ft:
	put_fwow_tabwe(dev, ft_pwio, fawse);
	if (ft_pwio_tx)
		put_fwow_tabwe(dev, ft_pwio_tx, fawse);
unwock:
	mutex_unwock(&dev->fwow_db->wock);
	kfwee(dst);
fwee_ucmd:
	kfwee(ucmd);
	wetuwn EWW_PTW(eww);
}

static stwuct mwx5_ib_fwow_pwio *
_get_fwow_tabwe(stwuct mwx5_ib_dev *dev, u16 usew_pwiowity,
		enum mwx5_fwow_namespace_type ns_type,
		boow mcast)
{
	stwuct mwx5_fwow_namespace *ns = NUWW;
	stwuct mwx5_ib_fwow_pwio *pwio = NUWW;
	int max_tabwe_size = 0;
	boow esw_encap;
	u32 fwags = 0;
	int pwiowity;

	if (mcast)
		pwiowity = MWX5_IB_FWOW_MCAST_PWIO;
	ewse
		pwiowity = ib_pwio_to_cowe_pwio(usew_pwiowity, fawse);

	esw_encap = mwx5_eswitch_get_encap_mode(dev->mdev) !=
		DEVWINK_ESWITCH_ENCAP_MODE_NONE;
	switch (ns_type) {
	case MWX5_FWOW_NAMESPACE_BYPASS:
		max_tabwe_size = BIT(
			MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev, wog_max_ft_size));
		if (MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev, decap) && !esw_encap)
			fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_DECAP;
		if (MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev,
					      wefowmat_w3_tunnew_to_w2) &&
		    !esw_encap)
			fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
		bweak;
	case MWX5_FWOW_NAMESPACE_EGWESS:
		max_tabwe_size = BIT(
			MWX5_CAP_FWOWTABWE_NIC_TX(dev->mdev, wog_max_ft_size));
		if (MWX5_CAP_FWOWTABWE_NIC_TX(dev->mdev, wefowmat) &&
		    !esw_encap)
			fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
		bweak;
	case MWX5_FWOW_NAMESPACE_FDB_BYPASS:
		max_tabwe_size = BIT(
			MWX5_CAP_ESW_FWOWTABWE_FDB(dev->mdev, wog_max_ft_size));
		if (MWX5_CAP_ESW_FWOWTABWE_FDB(dev->mdev, decap) && esw_encap)
			fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_DECAP;
		if (MWX5_CAP_ESW_FWOWTABWE_FDB(dev->mdev,
					       wefowmat_w3_tunnew_to_w2) &&
		    esw_encap)
			fwags |= MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
		pwiowity = usew_pwiowity;
		bweak;
	case MWX5_FWOW_NAMESPACE_WDMA_WX:
		max_tabwe_size = BIT(
			MWX5_CAP_FWOWTABWE_WDMA_WX(dev->mdev, wog_max_ft_size));
		pwiowity = usew_pwiowity;
		bweak;
	case MWX5_FWOW_NAMESPACE_WDMA_TX:
		max_tabwe_size = BIT(
			MWX5_CAP_FWOWTABWE_WDMA_TX(dev->mdev, wog_max_ft_size));
		pwiowity = usew_pwiowity;
		bweak;
	defauwt:
		bweak;
	}

	max_tabwe_size = min_t(int, max_tabwe_size, MWX5_FS_MAX_ENTWIES);

	ns = mwx5_get_fwow_namespace(dev->mdev, ns_type);
	if (!ns)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	switch (ns_type) {
	case MWX5_FWOW_NAMESPACE_BYPASS:
		pwio = &dev->fwow_db->pwios[pwiowity];
		bweak;
	case MWX5_FWOW_NAMESPACE_EGWESS:
		pwio = &dev->fwow_db->egwess_pwios[pwiowity];
		bweak;
	case MWX5_FWOW_NAMESPACE_FDB_BYPASS:
		pwio = &dev->fwow_db->fdb[pwiowity];
		bweak;
	case MWX5_FWOW_NAMESPACE_WDMA_WX:
		pwio = &dev->fwow_db->wdma_wx[pwiowity];
		bweak;
	case MWX5_FWOW_NAMESPACE_WDMA_TX:
		pwio = &dev->fwow_db->wdma_tx[pwiowity];
		bweak;
	defauwt: wetuwn EWW_PTW(-EINVAW);
	}

	if (!pwio)
		wetuwn EWW_PTW(-EINVAW);

	if (pwio->fwow_tabwe)
		wetuwn pwio;

	wetuwn _get_pwio(dev, ns, pwio, pwiowity, max_tabwe_size,
			 MWX5_FS_MAX_TYPES, fwags);
}

static stwuct mwx5_ib_fwow_handwew *
_cweate_waw_fwow_wuwe(stwuct mwx5_ib_dev *dev,
		      stwuct mwx5_ib_fwow_pwio *ft_pwio,
		      stwuct mwx5_fwow_destination *dst,
		      stwuct mwx5_ib_fwow_matchew  *fs_matchew,
		      stwuct mwx5_fwow_context *fwow_context,
		      stwuct mwx5_fwow_act *fwow_act,
		      void *cmd_in, int inwen,
		      int dst_num)
{
	stwuct mwx5_ib_fwow_handwew *handwew;
	stwuct mwx5_fwow_spec *spec;
	stwuct mwx5_fwow_tabwe *ft = ft_pwio->fwow_tabwe;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	handwew = kzawwoc(sizeof(*handwew), GFP_KEWNEW);
	if (!handwew || !spec) {
		eww = -ENOMEM;
		goto fwee;
	}

	INIT_WIST_HEAD(&handwew->wist);

	memcpy(spec->match_vawue, cmd_in, inwen);
	memcpy(spec->match_cwitewia, fs_matchew->matchew_mask.match_pawams,
	       fs_matchew->mask_wen);
	spec->match_cwitewia_enabwe = fs_matchew->match_cwitewia_enabwe;
	spec->fwow_context = *fwow_context;

	handwew->wuwe = mwx5_add_fwow_wuwes(ft, spec,
					    fwow_act, dst, dst_num);

	if (IS_EWW(handwew->wuwe)) {
		eww = PTW_EWW(handwew->wuwe);
		goto fwee;
	}

	ft_pwio->wefcount++;
	handwew->pwio = ft_pwio;
	handwew->dev = dev;
	ft_pwio->fwow_tabwe = ft;

fwee:
	if (eww)
		kfwee(handwew);
	kvfwee(spec);
	wetuwn eww ? EWW_PTW(eww) : handwew;
}

static boow waw_fs_is_muwticast(stwuct mwx5_ib_fwow_matchew *fs_matchew,
				void *match_v)
{
	void *match_c;
	void *match_v_set_wyw_2_4, *match_c_set_wyw_2_4;
	void *dmac, *dmac_mask;
	void *ipv4, *ipv4_mask;

	if (!(fs_matchew->match_cwitewia_enabwe &
	      (1 << MATCH_CWITEWIA_ENABWE_OUTEW_BIT)))
		wetuwn fawse;

	match_c = fs_matchew->matchew_mask.match_pawams;
	match_v_set_wyw_2_4 = MWX5_ADDW_OF(fte_match_pawam, match_v,
					   outew_headews);
	match_c_set_wyw_2_4 = MWX5_ADDW_OF(fte_match_pawam, match_c,
					   outew_headews);

	dmac = MWX5_ADDW_OF(fte_match_set_wyw_2_4, match_v_set_wyw_2_4,
			    dmac_47_16);
	dmac_mask = MWX5_ADDW_OF(fte_match_set_wyw_2_4, match_c_set_wyw_2_4,
				 dmac_47_16);

	if (is_muwticast_ethew_addw(dmac) &&
	    is_muwticast_ethew_addw(dmac_mask))
		wetuwn twue;

	ipv4 = MWX5_ADDW_OF(fte_match_set_wyw_2_4, match_v_set_wyw_2_4,
			    dst_ipv4_dst_ipv6.ipv4_wayout.ipv4);

	ipv4_mask = MWX5_ADDW_OF(fte_match_set_wyw_2_4, match_c_set_wyw_2_4,
				 dst_ipv4_dst_ipv6.ipv4_wayout.ipv4);

	if (ipv4_is_muwticast(*(__be32 *)(ipv4)) &&
	    ipv4_is_muwticast(*(__be32 *)(ipv4_mask)))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct mwx5_ib_fwow_handwew *waw_fs_wuwe_add(
	stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_fwow_matchew *fs_matchew,
	stwuct mwx5_fwow_context *fwow_context, stwuct mwx5_fwow_act *fwow_act,
	u32 countew_id, void *cmd_in, int inwen, int dest_id, int dest_type)
{
	stwuct mwx5_fwow_destination *dst;
	stwuct mwx5_ib_fwow_pwio *ft_pwio;
	stwuct mwx5_ib_fwow_handwew *handwew;
	int dst_num = 0;
	boow mcast;
	int eww;

	if (fs_matchew->fwow_type != MWX5_IB_FWOW_TYPE_NOWMAW)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (fs_matchew->pwiowity > MWX5_IB_FWOW_WAST_PWIO)
		wetuwn EWW_PTW(-ENOMEM);

	dst = kcawwoc(2, sizeof(*dst), GFP_KEWNEW);
	if (!dst)
		wetuwn EWW_PTW(-ENOMEM);

	mcast = waw_fs_is_muwticast(fs_matchew, cmd_in);
	mutex_wock(&dev->fwow_db->wock);

	ft_pwio = _get_fwow_tabwe(dev, fs_matchew->pwiowity,
				  fs_matchew->ns_type, mcast);
	if (IS_EWW(ft_pwio)) {
		eww = PTW_EWW(ft_pwio);
		goto unwock;
	}

	switch (dest_type) {
	case MWX5_FWOW_DESTINATION_TYPE_TIW:
		dst[dst_num].type = dest_type;
		dst[dst_num++].tiw_num = dest_id;
		fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
		bweak;
	case MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE:
		dst[dst_num].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE_NUM;
		dst[dst_num++].ft_num = dest_id;
		fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
		bweak;
	case MWX5_FWOW_DESTINATION_TYPE_POWT:
		dst[dst_num++].type = MWX5_FWOW_DESTINATION_TYPE_POWT;
		fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_AWWOW;
		bweak;
	defauwt:
		bweak;
	}

	if (fwow_act->action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		dst[dst_num].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dst[dst_num].countew_id = countew_id;
		dst_num++;
	}

	handwew = _cweate_waw_fwow_wuwe(dev, ft_pwio, dst_num ? dst : NUWW,
					fs_matchew, fwow_context, fwow_act,
					cmd_in, inwen, dst_num);

	if (IS_EWW(handwew)) {
		eww = PTW_EWW(handwew);
		goto destwoy_ft;
	}

	mutex_unwock(&dev->fwow_db->wock);
	atomic_inc(&fs_matchew->usecnt);
	handwew->fwow_matchew = fs_matchew;

	kfwee(dst);

	wetuwn handwew;

destwoy_ft:
	put_fwow_tabwe(dev, ft_pwio, fawse);
unwock:
	mutex_unwock(&dev->fwow_db->wock);
	kfwee(dst);

	wetuwn EWW_PTW(eww);
}

static void destwoy_fwow_action_waw(stwuct mwx5_ib_fwow_action *maction)
{
	switch (maction->fwow_action_waw.sub_type) {
	case MWX5_IB_FWOW_ACTION_MODIFY_HEADEW:
		mwx5_modify_headew_deawwoc(maction->fwow_action_waw.dev->mdev,
					   maction->fwow_action_waw.modify_hdw);
		bweak;
	case MWX5_IB_FWOW_ACTION_PACKET_WEFOWMAT:
		mwx5_packet_wefowmat_deawwoc(maction->fwow_action_waw.dev->mdev,
					     maction->fwow_action_waw.pkt_wefowmat);
		bweak;
	case MWX5_IB_FWOW_ACTION_DECAP:
		bweak;
	defauwt:
		bweak;
	}
}

static int mwx5_ib_destwoy_fwow_action(stwuct ib_fwow_action *action)
{
	stwuct mwx5_ib_fwow_action *maction = to_mfwow_act(action);

	switch (action->type) {
	case IB_FWOW_ACTION_UNSPECIFIED:
		destwoy_fwow_action_waw(maction);
		bweak;
	defauwt:
		WAWN_ON(twue);
		bweak;
	}

	kfwee(maction);
	wetuwn 0;
}

static int
mwx5_ib_ft_type_to_namespace(enum mwx5_ib_uapi_fwow_tabwe_type tabwe_type,
			     enum mwx5_fwow_namespace_type *namespace)
{
	switch (tabwe_type) {
	case MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_WX:
		*namespace = MWX5_FWOW_NAMESPACE_BYPASS;
		bweak;
	case MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_TX:
		*namespace = MWX5_FWOW_NAMESPACE_EGWESS;
		bweak;
	case MWX5_IB_UAPI_FWOW_TABWE_TYPE_FDB:
		*namespace = MWX5_FWOW_NAMESPACE_FDB_BYPASS;
		bweak;
	case MWX5_IB_UAPI_FWOW_TABWE_TYPE_WDMA_WX:
		*namespace = MWX5_FWOW_NAMESPACE_WDMA_WX;
		bweak;
	case MWX5_IB_UAPI_FWOW_TABWE_TYPE_WDMA_TX:
		*namespace = MWX5_FWOW_NAMESPACE_WDMA_TX;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct uvewbs_attw_spec mwx5_ib_fwow_type[] = {
	[MWX5_IB_FWOW_TYPE_NOWMAW] = {
		.type = UVEWBS_ATTW_TYPE_PTW_IN,
		.u.ptw = {
			.wen = sizeof(u16), /* data is pwiowity */
			.min_wen = sizeof(u16),
		}
	},
	[MWX5_IB_FWOW_TYPE_SNIFFEW] = {
		.type = UVEWBS_ATTW_TYPE_PTW_IN,
		UVEWBS_ATTW_NO_DATA(),
	},
	[MWX5_IB_FWOW_TYPE_AWW_DEFAUWT] = {
		.type = UVEWBS_ATTW_TYPE_PTW_IN,
		UVEWBS_ATTW_NO_DATA(),
	},
	[MWX5_IB_FWOW_TYPE_MC_DEFAUWT] = {
		.type = UVEWBS_ATTW_TYPE_PTW_IN,
		UVEWBS_ATTW_NO_DATA(),
	},
};

static boow is_fwow_dest(void *obj, int *dest_id, int *dest_type)
{
	stwuct devx_obj *devx_obj = obj;
	u16 opcode = MWX5_GET(genewaw_obj_in_cmd_hdw, devx_obj->dinbox, opcode);

	switch (opcode) {
	case MWX5_CMD_OP_DESTWOY_TIW:
		*dest_type = MWX5_FWOW_DESTINATION_TYPE_TIW;
		*dest_id = MWX5_GET(genewaw_obj_in_cmd_hdw, devx_obj->dinbox,
				    obj_id);
		wetuwn twue;

	case MWX5_CMD_OP_DESTWOY_FWOW_TABWE:
		*dest_type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		*dest_id = MWX5_GET(destwoy_fwow_tabwe_in, devx_obj->dinbox,
				    tabwe_id);
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int get_dests(stwuct uvewbs_attw_bundwe *attws,
		     stwuct mwx5_ib_fwow_matchew *fs_matchew, int *dest_id,
		     int *dest_type, stwuct ib_qp **qp, u32 *fwags)
{
	boow dest_devx, dest_qp;
	void *devx_obj;
	int eww;

	dest_devx = uvewbs_attw_is_vawid(attws,
					 MWX5_IB_ATTW_CWEATE_FWOW_DEST_DEVX);
	dest_qp = uvewbs_attw_is_vawid(attws,
				       MWX5_IB_ATTW_CWEATE_FWOW_DEST_QP);

	*fwags = 0;
	eww = uvewbs_get_fwags32(fwags, attws, MWX5_IB_ATTW_CWEATE_FWOW_FWAGS,
				 MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DEFAUWT_MISS |
					 MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DWOP);
	if (eww)
		wetuwn eww;

	/* Both fwags awe not awwowed */
	if (*fwags & MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DEFAUWT_MISS &&
	    *fwags & MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DWOP)
		wetuwn -EINVAW;

	if (fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_BYPASS) {
		if (dest_devx && (dest_qp || *fwags))
			wetuwn -EINVAW;
		ewse if (dest_qp && *fwags)
			wetuwn -EINVAW;
	}

	/* Awwow onwy DEVX object, dwop as dest fow FDB */
	if (fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_FDB_BYPASS &&
	    !(dest_devx || (*fwags & MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DWOP)))
		wetuwn -EINVAW;

	/* Awwow onwy DEVX object ow QP as dest when insewting to WDMA_WX */
	if ((fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_WDMA_WX) &&
	    ((!dest_devx && !dest_qp) || (dest_devx && dest_qp)))
		wetuwn -EINVAW;

	*qp = NUWW;
	if (dest_devx) {
		devx_obj =
			uvewbs_attw_get_obj(attws,
					    MWX5_IB_ATTW_CWEATE_FWOW_DEST_DEVX);

		/* Vewify that the given DEVX object is a fwow
		 * steewing destination.
		 */
		if (!is_fwow_dest(devx_obj, dest_id, dest_type))
			wetuwn -EINVAW;
		/* Awwow onwy fwow tabwe as dest when insewting to FDB ow WDMA_WX */
		if ((fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_FDB_BYPASS ||
		     fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_WDMA_WX) &&
		    *dest_type != MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE)
			wetuwn -EINVAW;
	} ewse if (dest_qp) {
		stwuct mwx5_ib_qp *mqp;

		*qp = uvewbs_attw_get_obj(attws,
					  MWX5_IB_ATTW_CWEATE_FWOW_DEST_QP);
		if (IS_EWW(*qp))
			wetuwn PTW_EWW(*qp);

		if ((*qp)->qp_type != IB_QPT_WAW_PACKET)
			wetuwn -EINVAW;

		mqp = to_mqp(*qp);
		if (mqp->is_wss)
			*dest_id = mqp->wss_qp.tiwn;
		ewse
			*dest_id = mqp->waw_packet_qp.wq.tiwn;
		*dest_type = MWX5_FWOW_DESTINATION_TYPE_TIW;
	} ewse if ((fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_EGWESS ||
		    fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_WDMA_TX) &&
		   !(*fwags & MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DWOP)) {
		*dest_type = MWX5_FWOW_DESTINATION_TYPE_POWT;
	}

	if (*dest_type == MWX5_FWOW_DESTINATION_TYPE_TIW &&
	    (fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_EGWESS ||
	     fs_matchew->ns_type == MWX5_FWOW_NAMESPACE_WDMA_TX))
		wetuwn -EINVAW;

	wetuwn 0;
}

static boow is_fwow_countew(void *obj, u32 offset, u32 *countew_id)
{
	stwuct devx_obj *devx_obj = obj;
	u16 opcode = MWX5_GET(genewaw_obj_in_cmd_hdw, devx_obj->dinbox, opcode);

	if (opcode == MWX5_CMD_OP_DEAWWOC_FWOW_COUNTEW) {

		if (offset && offset >= devx_obj->fwow_countew_buwk_size)
			wetuwn fawse;

		*countew_id = MWX5_GET(deawwoc_fwow_countew_in,
				       devx_obj->dinbox,
				       fwow_countew_id);
		*countew_id += offset;
		wetuwn twue;
	}

	wetuwn fawse;
}

#define MWX5_IB_CWEATE_FWOW_MAX_FWOW_ACTIONS 2
static int UVEWBS_HANDWEW(MWX5_IB_METHOD_CWEATE_FWOW)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_fwow_context fwow_context = {.fwow_tag =
		MWX5_FS_DEFAUWT_FWOW_TAG};
	u32 *offset_attw, offset = 0, countew_id = 0;
	int dest_id, dest_type = -1, inwen, wen, wet, i;
	stwuct mwx5_ib_fwow_handwew *fwow_handwew;
	stwuct mwx5_ib_fwow_matchew *fs_matchew;
	stwuct ib_uobject **aww_fwow_actions;
	stwuct ib_ufwow_wesouwces *ufwow_wes;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct ib_qp *qp = NUWW;
	void *devx_obj, *cmd_in;
	stwuct ib_uobject *uobj;
	stwuct mwx5_ib_dev *dev;
	u32 fwags;

	if (!capabwe(CAP_NET_WAW))
		wetuwn -EPEWM;

	fs_matchew = uvewbs_attw_get_obj(attws,
					 MWX5_IB_ATTW_CWEATE_FWOW_MATCHEW);
	uobj =  uvewbs_attw_get_uobject(attws, MWX5_IB_ATTW_CWEATE_FWOW_HANDWE);
	dev = mwx5_udata_to_mdev(&attws->dwivew_udata);

	if (get_dests(attws, fs_matchew, &dest_id, &dest_type, &qp, &fwags))
		wetuwn -EINVAW;

	if (fwags & MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DEFAUWT_MISS)
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_FWD_NEXT_NS;

	if (fwags & MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DWOP)
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_DWOP;

	wen = uvewbs_attw_get_uobjs_aww(attws,
		MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX, &aww_fwow_actions);
	if (wen) {
		devx_obj = aww_fwow_actions[0]->object;

		if (uvewbs_attw_is_vawid(attws,
					 MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX_OFFSET)) {

			int num_offsets = uvewbs_attw_ptw_get_awway_size(
				attws,
				MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX_OFFSET,
				sizeof(u32));

			if (num_offsets != 1)
				wetuwn -EINVAW;

			offset_attw = uvewbs_attw_get_awwoced_ptw(
				attws,
				MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX_OFFSET);
			offset = *offset_attw;
		}

		if (!is_fwow_countew(devx_obj, offset, &countew_id))
			wetuwn -EINVAW;

		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
	}

	cmd_in = uvewbs_attw_get_awwoced_ptw(
		attws, MWX5_IB_ATTW_CWEATE_FWOW_MATCH_VAWUE);
	inwen = uvewbs_attw_get_wen(attws,
				    MWX5_IB_ATTW_CWEATE_FWOW_MATCH_VAWUE);

	ufwow_wes = fwow_wesouwces_awwoc(MWX5_IB_CWEATE_FWOW_MAX_FWOW_ACTIONS);
	if (!ufwow_wes)
		wetuwn -ENOMEM;

	wen = uvewbs_attw_get_uobjs_aww(attws,
		MWX5_IB_ATTW_CWEATE_FWOW_AWW_FWOW_ACTIONS, &aww_fwow_actions);
	fow (i = 0; i < wen; i++) {
		stwuct mwx5_ib_fwow_action *maction =
			to_mfwow_act(aww_fwow_actions[i]->object);

		wet = pawse_fwow_fwow_action(maction, fawse, &fwow_act);
		if (wet)
			goto eww_out;
		fwow_wesouwces_add(ufwow_wes, IB_FWOW_SPEC_ACTION_HANDWE,
				   aww_fwow_actions[i]->object);
	}

	wet = uvewbs_copy_fwom(&fwow_context.fwow_tag, attws,
			       MWX5_IB_ATTW_CWEATE_FWOW_TAG);
	if (!wet) {
		if (fwow_context.fwow_tag >= BIT(24)) {
			wet = -EINVAW;
			goto eww_out;
		}
		fwow_context.fwags |= FWOW_CONTEXT_HAS_TAG;
	}

	fwow_handwew =
		waw_fs_wuwe_add(dev, fs_matchew, &fwow_context, &fwow_act,
				countew_id, cmd_in, inwen, dest_id, dest_type);
	if (IS_EWW(fwow_handwew)) {
		wet = PTW_EWW(fwow_handwew);
		goto eww_out;
	}

	ib_set_fwow(uobj, &fwow_handwew->ibfwow, qp, &dev->ib_dev, ufwow_wes);

	wetuwn 0;
eww_out:
	ib_uvewbs_fwow_wesouwces_fwee(ufwow_wes);
	wetuwn wet;
}

static int fwow_matchew_cweanup(stwuct ib_uobject *uobject,
				enum wdma_wemove_weason why,
				stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_ib_fwow_matchew *obj = uobject->object;

	if (atomic_wead(&obj->usecnt))
		wetuwn -EBUSY;

	kfwee(obj);
	wetuwn 0;
}

static int steewing_anchow_cweate_ft(stwuct mwx5_ib_dev *dev,
				     stwuct mwx5_ib_fwow_pwio *ft_pwio,
				     enum mwx5_fwow_namespace_type ns_type)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_tabwe *ft;

	if (ft_pwio->anchow.ft)
		wetuwn 0;

	ns = mwx5_get_fwow_namespace(dev->mdev, ns_type);
	if (!ns)
		wetuwn -EOPNOTSUPP;

	ft_attw.fwags = MWX5_FWOW_TABWE_UNMANAGED;
	ft_attw.uid = MWX5_SHAWED_WESOUWCE_UID;
	ft_attw.pwio = 0;
	ft_attw.max_fte = 2;
	ft_attw.wevew = 1;

	ft = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft))
		wetuwn PTW_EWW(ft);

	ft_pwio->anchow.ft = ft;

	wetuwn 0;
}

static void steewing_anchow_destwoy_ft(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	if (ft_pwio->anchow.ft) {
		mwx5_destwoy_fwow_tabwe(ft_pwio->anchow.ft);
		ft_pwio->anchow.ft = NUWW;
	}
}

static int
steewing_anchow_cweate_fg_dwop(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	void *fwow_gwoup_in;
	int eww = 0;

	if (ft_pwio->anchow.fg_dwop)
		wetuwn 0;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, 1);

	fg = mwx5_cweate_fwow_gwoup(ft_pwio->anchow.ft, fwow_gwoup_in);
	if (IS_EWW(fg)) {
		eww = PTW_EWW(fg);
		goto out;
	}

	ft_pwio->anchow.fg_dwop = fg;

out:
	kvfwee(fwow_gwoup_in);

	wetuwn eww;
}

static void
steewing_anchow_destwoy_fg_dwop(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	if (ft_pwio->anchow.fg_dwop) {
		mwx5_destwoy_fwow_gwoup(ft_pwio->anchow.fg_dwop);
		ft_pwio->anchow.fg_dwop = NUWW;
	}
}

static int
steewing_anchow_cweate_fg_goto_tabwe(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	void *fwow_gwoup_in;
	int eww = 0;

	if (ft_pwio->anchow.fg_goto_tabwe)
		wetuwn 0;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	fg = mwx5_cweate_fwow_gwoup(ft_pwio->anchow.ft, fwow_gwoup_in);
	if (IS_EWW(fg)) {
		eww = PTW_EWW(fg);
		goto out;
	}
	ft_pwio->anchow.fg_goto_tabwe = fg;

out:
	kvfwee(fwow_gwoup_in);

	wetuwn eww;
}

static void
steewing_anchow_destwoy_fg_goto_tabwe(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	if (ft_pwio->anchow.fg_goto_tabwe) {
		mwx5_destwoy_fwow_gwoup(ft_pwio->anchow.fg_goto_tabwe);
		ft_pwio->anchow.fg_goto_tabwe = NUWW;
	}
}

static int
steewing_anchow_cweate_wuwe_dwop(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *handwe;

	if (ft_pwio->anchow.wuwe_dwop)
		wetuwn 0;

	fwow_act.fg = ft_pwio->anchow.fg_dwop;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP;

	handwe = mwx5_add_fwow_wuwes(ft_pwio->anchow.ft, NUWW, &fwow_act,
				     NUWW, 0);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	ft_pwio->anchow.wuwe_dwop = handwe;

	wetuwn 0;
}

static void steewing_anchow_destwoy_wuwe_dwop(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	if (ft_pwio->anchow.wuwe_dwop) {
		mwx5_dew_fwow_wuwes(ft_pwio->anchow.wuwe_dwop);
		ft_pwio->anchow.wuwe_dwop = NUWW;
	}
}

static int
steewing_anchow_cweate_wuwe_goto_tabwe(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *handwe;

	if (ft_pwio->anchow.wuwe_goto_tabwe)
		wetuwn 0;

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fwow_act.fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	fwow_act.fg = ft_pwio->anchow.fg_goto_tabwe;

	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = ft_pwio->fwow_tabwe;

	handwe = mwx5_add_fwow_wuwes(ft_pwio->anchow.ft, NUWW, &fwow_act,
				     &dest, 1);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	ft_pwio->anchow.wuwe_goto_tabwe = handwe;

	wetuwn 0;
}

static void
steewing_anchow_destwoy_wuwe_goto_tabwe(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	if (ft_pwio->anchow.wuwe_goto_tabwe) {
		mwx5_dew_fwow_wuwes(ft_pwio->anchow.wuwe_goto_tabwe);
		ft_pwio->anchow.wuwe_goto_tabwe = NUWW;
	}
}

static int steewing_anchow_cweate_wes(stwuct mwx5_ib_dev *dev,
				      stwuct mwx5_ib_fwow_pwio *ft_pwio,
				      enum mwx5_fwow_namespace_type ns_type)
{
	int eww;

	eww = steewing_anchow_cweate_ft(dev, ft_pwio, ns_type);
	if (eww)
		wetuwn eww;

	eww = steewing_anchow_cweate_fg_dwop(ft_pwio);
	if (eww)
		goto destwoy_ft;

	eww = steewing_anchow_cweate_fg_goto_tabwe(ft_pwio);
	if (eww)
		goto destwoy_fg_dwop;

	eww = steewing_anchow_cweate_wuwe_dwop(ft_pwio);
	if (eww)
		goto destwoy_fg_goto_tabwe;

	eww = steewing_anchow_cweate_wuwe_goto_tabwe(ft_pwio);
	if (eww)
		goto destwoy_wuwe_dwop;

	wetuwn 0;

destwoy_wuwe_dwop:
	steewing_anchow_destwoy_wuwe_dwop(ft_pwio);
destwoy_fg_goto_tabwe:
	steewing_anchow_destwoy_fg_goto_tabwe(ft_pwio);
destwoy_fg_dwop:
	steewing_anchow_destwoy_fg_dwop(ft_pwio);
destwoy_ft:
	steewing_anchow_destwoy_ft(ft_pwio);

	wetuwn eww;
}

static void mwx5_steewing_anchow_destwoy_wes(stwuct mwx5_ib_fwow_pwio *ft_pwio)
{
	steewing_anchow_destwoy_wuwe_goto_tabwe(ft_pwio);
	steewing_anchow_destwoy_wuwe_dwop(ft_pwio);
	steewing_anchow_destwoy_fg_goto_tabwe(ft_pwio);
	steewing_anchow_destwoy_fg_dwop(ft_pwio);
	steewing_anchow_destwoy_ft(ft_pwio);
}

static int steewing_anchow_cweanup(stwuct ib_uobject *uobject,
				   enum wdma_wemove_weason why,
				   stwuct uvewbs_attw_bundwe *attws)
{
	stwuct mwx5_ib_steewing_anchow *obj = uobject->object;

	if (atomic_wead(&obj->usecnt))
		wetuwn -EBUSY;

	mutex_wock(&obj->dev->fwow_db->wock);
	if (!--obj->ft_pwio->anchow.wuwe_goto_tabwe_wef)
		steewing_anchow_destwoy_wuwe_goto_tabwe(obj->ft_pwio);

	put_fwow_tabwe(obj->dev, obj->ft_pwio, twue);
	mutex_unwock(&obj->dev->fwow_db->wock);

	kfwee(obj);
	wetuwn 0;
}

static void fs_cweanup_anchow(stwuct mwx5_ib_fwow_pwio *pwio,
			      int count)
{
	whiwe (count--)
		mwx5_steewing_anchow_destwoy_wes(&pwio[count]);
}

void mwx5_ib_fs_cweanup_anchow(stwuct mwx5_ib_dev *dev)
{
	fs_cweanup_anchow(dev->fwow_db->pwios, MWX5_IB_NUM_FWOW_FT);
	fs_cweanup_anchow(dev->fwow_db->egwess_pwios, MWX5_IB_NUM_FWOW_FT);
	fs_cweanup_anchow(dev->fwow_db->sniffew, MWX5_IB_NUM_SNIFFEW_FTS);
	fs_cweanup_anchow(dev->fwow_db->egwess, MWX5_IB_NUM_EGWESS_FTS);
	fs_cweanup_anchow(dev->fwow_db->fdb, MWX5_IB_NUM_FDB_FTS);
	fs_cweanup_anchow(dev->fwow_db->wdma_wx, MWX5_IB_NUM_FWOW_FT);
	fs_cweanup_anchow(dev->fwow_db->wdma_tx, MWX5_IB_NUM_FWOW_FT);
}

static int mwx5_ib_matchew_ns(stwuct uvewbs_attw_bundwe *attws,
			      stwuct mwx5_ib_fwow_matchew *obj)
{
	enum mwx5_ib_uapi_fwow_tabwe_type ft_type =
		MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_WX;
	u32 fwags;
	int eww;

	/* New usews shouwd use MWX5_IB_ATTW_FWOW_MATCHEW_FT_TYPE and owdew
	 * usews shouwd switch to it. We weave this to not bweak usewspace
	 */
	if (uvewbs_attw_is_vawid(attws, MWX5_IB_ATTW_FWOW_MATCHEW_FT_TYPE) &&
	    uvewbs_attw_is_vawid(attws, MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_FWAGS))
		wetuwn -EINVAW;

	if (uvewbs_attw_is_vawid(attws, MWX5_IB_ATTW_FWOW_MATCHEW_FT_TYPE)) {
		eww = uvewbs_get_const(&ft_type, attws,
				       MWX5_IB_ATTW_FWOW_MATCHEW_FT_TYPE);
		if (eww)
			wetuwn eww;

		eww = mwx5_ib_ft_type_to_namespace(ft_type, &obj->ns_type);
		if (eww)
			wetuwn eww;

		wetuwn 0;
	}

	if (uvewbs_attw_is_vawid(attws, MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_FWAGS)) {
		eww = uvewbs_get_fwags32(&fwags, attws,
					 MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_FWAGS,
					 IB_FWOW_ATTW_FWAGS_EGWESS);
		if (eww)
			wetuwn eww;

		if (fwags)
			wetuwn mwx5_ib_ft_type_to_namespace(
				MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_TX,
				&obj->ns_type);
	}

	obj->ns_type = MWX5_FWOW_NAMESPACE_BYPASS;

	wetuwn 0;
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_FWOW_MATCHEW_CWEATE)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj = uvewbs_attw_get_uobject(
		attws, MWX5_IB_ATTW_FWOW_MATCHEW_CWEATE_HANDWE);
	stwuct mwx5_ib_dev *dev = mwx5_udata_to_mdev(&attws->dwivew_udata);
	stwuct mwx5_ib_fwow_matchew *obj;
	int eww;

	obj = kzawwoc(sizeof(stwuct mwx5_ib_fwow_matchew), GFP_KEWNEW);
	if (!obj)
		wetuwn -ENOMEM;

	obj->mask_wen = uvewbs_attw_get_wen(
		attws, MWX5_IB_ATTW_FWOW_MATCHEW_MATCH_MASK);
	eww = uvewbs_copy_fwom(&obj->matchew_mask,
			       attws,
			       MWX5_IB_ATTW_FWOW_MATCHEW_MATCH_MASK);
	if (eww)
		goto end;

	obj->fwow_type = uvewbs_attw_get_enum_id(
		attws, MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_TYPE);

	if (obj->fwow_type == MWX5_IB_FWOW_TYPE_NOWMAW) {
		eww = uvewbs_copy_fwom(&obj->pwiowity,
				       attws,
				       MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_TYPE);
		if (eww)
			goto end;
	}

	eww = uvewbs_copy_fwom(&obj->match_cwitewia_enabwe,
			       attws,
			       MWX5_IB_ATTW_FWOW_MATCHEW_MATCH_CWITEWIA);
	if (eww)
		goto end;

	eww = mwx5_ib_matchew_ns(attws, obj);
	if (eww)
		goto end;

	if (obj->ns_type == MWX5_FWOW_NAMESPACE_FDB_BYPASS &&
	    mwx5_eswitch_mode(dev->mdev) != MWX5_ESWITCH_OFFWOADS) {
		eww = -EINVAW;
		goto end;
	}

	uobj->object = obj;
	obj->mdev = dev->mdev;
	atomic_set(&obj->usecnt, 0);
	wetuwn 0;

end:
	kfwee(obj);
	wetuwn eww;
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_STEEWING_ANCHOW_CWEATE)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj = uvewbs_attw_get_uobject(
		attws, MWX5_IB_ATTW_STEEWING_ANCHOW_CWEATE_HANDWE);
	stwuct mwx5_ib_dev *dev = mwx5_udata_to_mdev(&attws->dwivew_udata);
	enum mwx5_ib_uapi_fwow_tabwe_type ib_uapi_ft_type;
	enum mwx5_fwow_namespace_type ns_type;
	stwuct mwx5_ib_steewing_anchow *obj;
	stwuct mwx5_ib_fwow_pwio *ft_pwio;
	u16 pwiowity;
	u32 ft_id;
	int eww;

	if (!capabwe(CAP_NET_WAW))
		wetuwn -EPEWM;

	eww = uvewbs_get_const(&ib_uapi_ft_type, attws,
			       MWX5_IB_ATTW_STEEWING_ANCHOW_FT_TYPE);
	if (eww)
		wetuwn eww;

	eww = mwx5_ib_ft_type_to_namespace(ib_uapi_ft_type, &ns_type);
	if (eww)
		wetuwn eww;

	eww = uvewbs_copy_fwom(&pwiowity, attws,
			       MWX5_IB_ATTW_STEEWING_ANCHOW_PWIOWITY);
	if (eww)
		wetuwn eww;

	obj = kzawwoc(sizeof(*obj), GFP_KEWNEW);
	if (!obj)
		wetuwn -ENOMEM;

	mutex_wock(&dev->fwow_db->wock);

	ft_pwio = _get_fwow_tabwe(dev, pwiowity, ns_type, 0);
	if (IS_EWW(ft_pwio)) {
		eww = PTW_EWW(ft_pwio);
		goto fwee_obj;
	}

	ft_pwio->wefcount++;

	if (!ft_pwio->anchow.wuwe_goto_tabwe_wef) {
		eww = steewing_anchow_cweate_wes(dev, ft_pwio, ns_type);
		if (eww)
			goto put_fwow_tabwe;
	}

	ft_pwio->anchow.wuwe_goto_tabwe_wef++;

	ft_id = mwx5_fwow_tabwe_id(ft_pwio->anchow.ft);

	eww = uvewbs_copy_to(attws, MWX5_IB_ATTW_STEEWING_ANCHOW_FT_ID,
			     &ft_id, sizeof(ft_id));
	if (eww)
		goto destwoy_wes;

	mutex_unwock(&dev->fwow_db->wock);

	uobj->object = obj;
	obj->dev = dev;
	obj->ft_pwio = ft_pwio;
	atomic_set(&obj->usecnt, 0);

	wetuwn 0;

destwoy_wes:
	--ft_pwio->anchow.wuwe_goto_tabwe_wef;
	mwx5_steewing_anchow_destwoy_wes(ft_pwio);
put_fwow_tabwe:
	put_fwow_tabwe(dev, ft_pwio, twue);
fwee_obj:
	mutex_unwock(&dev->fwow_db->wock);
	kfwee(obj);

	wetuwn eww;
}

static stwuct ib_fwow_action *
mwx5_ib_cweate_modify_headew(stwuct mwx5_ib_dev *dev,
			     enum mwx5_ib_uapi_fwow_tabwe_type ft_type,
			     u8 num_actions, void *in)
{
	enum mwx5_fwow_namespace_type namespace;
	stwuct mwx5_ib_fwow_action *maction;
	int wet;

	wet = mwx5_ib_ft_type_to_namespace(ft_type, &namespace);
	if (wet)
		wetuwn EWW_PTW(-EINVAW);

	maction = kzawwoc(sizeof(*maction), GFP_KEWNEW);
	if (!maction)
		wetuwn EWW_PTW(-ENOMEM);

	maction->fwow_action_waw.modify_hdw =
		mwx5_modify_headew_awwoc(dev->mdev, namespace, num_actions, in);

	if (IS_EWW(maction->fwow_action_waw.modify_hdw)) {
		wet = PTW_EWW(maction->fwow_action_waw.modify_hdw);
		kfwee(maction);
		wetuwn EWW_PTW(wet);
	}
	maction->fwow_action_waw.sub_type =
		MWX5_IB_FWOW_ACTION_MODIFY_HEADEW;
	maction->fwow_action_waw.dev = dev;

	wetuwn &maction->ib_action;
}

static boow mwx5_ib_modify_headew_suppowted(stwuct mwx5_ib_dev *dev)
{
	wetuwn MWX5_CAP_FWOWTABWE_NIC_WX(dev->mdev,
					 max_modify_headew_actions) ||
	       MWX5_CAP_FWOWTABWE_NIC_TX(dev->mdev,
					 max_modify_headew_actions) ||
	       MWX5_CAP_FWOWTABWE_WDMA_TX(dev->mdev,
					 max_modify_headew_actions);
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_FWOW_ACTION_CWEATE_MODIFY_HEADEW)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj = uvewbs_attw_get_uobject(
		attws, MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_HANDWE);
	stwuct mwx5_ib_dev *mdev = mwx5_udata_to_mdev(&attws->dwivew_udata);
	enum mwx5_ib_uapi_fwow_tabwe_type ft_type;
	stwuct ib_fwow_action *action;
	int num_actions;
	void *in;
	int wet;

	if (!mwx5_ib_modify_headew_suppowted(mdev))
		wetuwn -EOPNOTSUPP;

	in = uvewbs_attw_get_awwoced_ptw(attws,
		MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_ACTIONS_PWM);

	num_actions = uvewbs_attw_ptw_get_awway_size(
		attws, MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_ACTIONS_PWM,
		MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto));
	if (num_actions < 0)
		wetuwn num_actions;

	wet = uvewbs_get_const(&ft_type, attws,
			       MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_FT_TYPE);
	if (wet)
		wetuwn wet;
	action = mwx5_ib_cweate_modify_headew(mdev, ft_type, num_actions, in);
	if (IS_EWW(action))
		wetuwn PTW_EWW(action);

	uvewbs_fwow_action_fiww_action(action, uobj, &mdev->ib_dev,
				       IB_FWOW_ACTION_UNSPECIFIED);

	wetuwn 0;
}

static boow mwx5_ib_fwow_action_packet_wefowmat_vawid(stwuct mwx5_ib_dev *ibdev,
						      u8 packet_wefowmat_type,
						      u8 ft_type)
{
	switch (packet_wefowmat_type) {
	case MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TO_W2_TUNNEW:
		if (ft_type == MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_TX)
			wetuwn MWX5_CAP_FWOWTABWE(ibdev->mdev,
						  encap_genewaw_headew);
		bweak;
	case MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TO_W3_TUNNEW:
		if (ft_type == MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_TX)
			wetuwn MWX5_CAP_FWOWTABWE_NIC_TX(ibdev->mdev,
				wefowmat_w2_to_w3_tunnew);
		bweak;
	case MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W3_TUNNEW_TO_W2:
		if (ft_type == MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_WX)
			wetuwn MWX5_CAP_FWOWTABWE_NIC_WX(ibdev->mdev,
				wefowmat_w3_tunnew_to_w2);
		bweak;
	case MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TUNNEW_TO_W2:
		if (ft_type == MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_WX)
			wetuwn MWX5_CAP_FWOWTABWE_NIC_WX(ibdev->mdev, decap);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn fawse;
}

static int mwx5_ib_dv_to_pwm_packet_wefowamt_type(u8 dv_pwt, u8 *pwm_pwt)
{
	switch (dv_pwt) {
	case MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TO_W2_TUNNEW:
		*pwm_pwt = MWX5_WEFOWMAT_TYPE_W2_TO_W2_TUNNEW;
		bweak;
	case MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W3_TUNNEW_TO_W2:
		*pwm_pwt = MWX5_WEFOWMAT_TYPE_W3_TUNNEW_TO_W2;
		bweak;
	case MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TO_W3_TUNNEW:
		*pwm_pwt = MWX5_WEFOWMAT_TYPE_W2_TO_W3_TUNNEW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int mwx5_ib_fwow_action_cweate_packet_wefowmat_ctx(
	stwuct mwx5_ib_dev *dev,
	stwuct mwx5_ib_fwow_action *maction,
	u8 ft_type, u8 dv_pwt,
	void *in, size_t wen)
{
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams;
	enum mwx5_fwow_namespace_type namespace;
	u8 pwm_pwt;
	int wet;

	wet = mwx5_ib_ft_type_to_namespace(ft_type, &namespace);
	if (wet)
		wetuwn wet;

	wet = mwx5_ib_dv_to_pwm_packet_wefowamt_type(dv_pwt, &pwm_pwt);
	if (wet)
		wetuwn wet;

	memset(&wefowmat_pawams, 0, sizeof(wefowmat_pawams));
	wefowmat_pawams.type = pwm_pwt;
	wefowmat_pawams.size = wen;
	wefowmat_pawams.data = in;
	maction->fwow_action_waw.pkt_wefowmat =
		mwx5_packet_wefowmat_awwoc(dev->mdev, &wefowmat_pawams,
					   namespace);
	if (IS_EWW(maction->fwow_action_waw.pkt_wefowmat)) {
		wet = PTW_EWW(maction->fwow_action_waw.pkt_wefowmat);
		wetuwn wet;
	}

	maction->fwow_action_waw.sub_type =
		MWX5_IB_FWOW_ACTION_PACKET_WEFOWMAT;
	maction->fwow_action_waw.dev = dev;

	wetuwn 0;
}

static int UVEWBS_HANDWEW(MWX5_IB_METHOD_FWOW_ACTION_CWEATE_PACKET_WEFOWMAT)(
	stwuct uvewbs_attw_bundwe *attws)
{
	stwuct ib_uobject *uobj = uvewbs_attw_get_uobject(attws,
		MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_HANDWE);
	stwuct mwx5_ib_dev *mdev = mwx5_udata_to_mdev(&attws->dwivew_udata);
	enum mwx5_ib_uapi_fwow_action_packet_wefowmat_type dv_pwt;
	enum mwx5_ib_uapi_fwow_tabwe_type ft_type;
	stwuct mwx5_ib_fwow_action *maction;
	int wet;

	wet = uvewbs_get_const(&ft_type, attws,
			       MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_FT_TYPE);
	if (wet)
		wetuwn wet;

	wet = uvewbs_get_const(&dv_pwt, attws,
			       MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_TYPE);
	if (wet)
		wetuwn wet;

	if (!mwx5_ib_fwow_action_packet_wefowmat_vawid(mdev, dv_pwt, ft_type))
		wetuwn -EOPNOTSUPP;

	maction = kzawwoc(sizeof(*maction), GFP_KEWNEW);
	if (!maction)
		wetuwn -ENOMEM;

	if (dv_pwt ==
	    MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TUNNEW_TO_W2) {
		maction->fwow_action_waw.sub_type =
			MWX5_IB_FWOW_ACTION_DECAP;
		maction->fwow_action_waw.dev = mdev;
	} ewse {
		void *in;
		int wen;

		in = uvewbs_attw_get_awwoced_ptw(attws,
			MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_DATA_BUF);
		if (IS_EWW(in)) {
			wet = PTW_EWW(in);
			goto fwee_maction;
		}

		wen = uvewbs_attw_get_wen(attws,
			MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_DATA_BUF);

		wet = mwx5_ib_fwow_action_cweate_packet_wefowmat_ctx(mdev,
			maction, ft_type, dv_pwt, in, wen);
		if (wet)
			goto fwee_maction;
	}

	uvewbs_fwow_action_fiww_action(&maction->ib_action, uobj, &mdev->ib_dev,
				       IB_FWOW_ACTION_UNSPECIFIED);
	wetuwn 0;

fwee_maction:
	kfwee(maction);
	wetuwn wet;
}

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_CWEATE_FWOW,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_CWEATE_FWOW_HANDWE,
			UVEWBS_OBJECT_FWOW,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(
		MWX5_IB_ATTW_CWEATE_FWOW_MATCH_VAWUE,
		UVEWBS_ATTW_SIZE(1, sizeof(stwuct mwx5_ib_match_pawams)),
		UA_MANDATOWY,
		UA_AWWOC_AND_COPY),
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_CWEATE_FWOW_MATCHEW,
			MWX5_IB_OBJECT_FWOW_MATCHEW,
			UVEWBS_ACCESS_WEAD,
			UA_MANDATOWY),
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_CWEATE_FWOW_DEST_QP,
			UVEWBS_OBJECT_QP,
			UVEWBS_ACCESS_WEAD),
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_CWEATE_FWOW_DEST_DEVX,
			MWX5_IB_OBJECT_DEVX_OBJ,
			UVEWBS_ACCESS_WEAD),
	UVEWBS_ATTW_IDWS_AWW(MWX5_IB_ATTW_CWEATE_FWOW_AWW_FWOW_ACTIONS,
			     UVEWBS_OBJECT_FWOW_ACTION,
			     UVEWBS_ACCESS_WEAD, 1,
			     MWX5_IB_CWEATE_FWOW_MAX_FWOW_ACTIONS,
			     UA_OPTIONAW),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_CWEATE_FWOW_TAG,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_OPTIONAW),
	UVEWBS_ATTW_IDWS_AWW(MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX,
			     MWX5_IB_OBJECT_DEVX_OBJ,
			     UVEWBS_ACCESS_WEAD, 1, 1,
			     UA_OPTIONAW),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX_OFFSET,
			   UVEWBS_ATTW_MIN_SIZE(sizeof(u32)),
			   UA_OPTIONAW,
			   UA_AWWOC_AND_COPY),
	UVEWBS_ATTW_FWAGS_IN(MWX5_IB_ATTW_CWEATE_FWOW_FWAGS,
			     enum mwx5_ib_cweate_fwow_fwags,
			     UA_OPTIONAW));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	MWX5_IB_METHOD_DESTWOY_FWOW,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_CWEATE_FWOW_HANDWE,
			UVEWBS_OBJECT_FWOW,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

ADD_UVEWBS_METHODS(mwx5_ib_fs,
		   UVEWBS_OBJECT_FWOW,
		   &UVEWBS_METHOD(MWX5_IB_METHOD_CWEATE_FWOW),
		   &UVEWBS_METHOD(MWX5_IB_METHOD_DESTWOY_FWOW));

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_FWOW_ACTION_CWEATE_MODIFY_HEADEW,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_HANDWE,
			UVEWBS_OBJECT_FWOW_ACTION,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_ACTIONS_PWM,
			   UVEWBS_ATTW_MIN_SIZE(MWX5_UN_SZ_BYTES(
				   set_add_copy_action_in_auto)),
			   UA_MANDATOWY,
			   UA_AWWOC_AND_COPY),
	UVEWBS_ATTW_CONST_IN(MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_FT_TYPE,
			     enum mwx5_ib_uapi_fwow_tabwe_type,
			     UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_FWOW_ACTION_CWEATE_PACKET_WEFOWMAT,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_HANDWE,
			UVEWBS_OBJECT_FWOW_ACTION,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_DATA_BUF,
			   UVEWBS_ATTW_MIN_SIZE(1),
			   UA_AWWOC_AND_COPY,
			   UA_OPTIONAW),
	UVEWBS_ATTW_CONST_IN(MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_TYPE,
			     enum mwx5_ib_uapi_fwow_action_packet_wefowmat_type,
			     UA_MANDATOWY),
	UVEWBS_ATTW_CONST_IN(MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_FT_TYPE,
			     enum mwx5_ib_uapi_fwow_tabwe_type,
			     UA_MANDATOWY));

ADD_UVEWBS_METHODS(
	mwx5_ib_fwow_actions,
	UVEWBS_OBJECT_FWOW_ACTION,
	&UVEWBS_METHOD(MWX5_IB_METHOD_FWOW_ACTION_CWEATE_MODIFY_HEADEW),
	&UVEWBS_METHOD(MWX5_IB_METHOD_FWOW_ACTION_CWEATE_PACKET_WEFOWMAT));

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_FWOW_MATCHEW_CWEATE,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_FWOW_MATCHEW_CWEATE_HANDWE,
			MWX5_IB_OBJECT_FWOW_MATCHEW,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(
		MWX5_IB_ATTW_FWOW_MATCHEW_MATCH_MASK,
		UVEWBS_ATTW_SIZE(1, sizeof(stwuct mwx5_ib_match_pawams)),
		UA_MANDATOWY),
	UVEWBS_ATTW_ENUM_IN(MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_TYPE,
			    mwx5_ib_fwow_type,
			    UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_FWOW_MATCHEW_MATCH_CWITEWIA,
			   UVEWBS_ATTW_TYPE(u8),
			   UA_MANDATOWY),
	UVEWBS_ATTW_FWAGS_IN(MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_FWAGS,
			     enum ib_fwow_fwags,
			     UA_OPTIONAW),
	UVEWBS_ATTW_CONST_IN(MWX5_IB_ATTW_FWOW_MATCHEW_FT_TYPE,
			     enum mwx5_ib_uapi_fwow_tabwe_type,
			     UA_OPTIONAW));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	MWX5_IB_METHOD_FWOW_MATCHEW_DESTWOY,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_FWOW_MATCHEW_DESTWOY_HANDWE,
			MWX5_IB_OBJECT_FWOW_MATCHEW,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(MWX5_IB_OBJECT_FWOW_MATCHEW,
			    UVEWBS_TYPE_AWWOC_IDW(fwow_matchew_cweanup),
			    &UVEWBS_METHOD(MWX5_IB_METHOD_FWOW_MATCHEW_CWEATE),
			    &UVEWBS_METHOD(MWX5_IB_METHOD_FWOW_MATCHEW_DESTWOY));

DECWAWE_UVEWBS_NAMED_METHOD(
	MWX5_IB_METHOD_STEEWING_ANCHOW_CWEATE,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_STEEWING_ANCHOW_CWEATE_HANDWE,
			MWX5_IB_OBJECT_STEEWING_ANCHOW,
			UVEWBS_ACCESS_NEW,
			UA_MANDATOWY),
	UVEWBS_ATTW_CONST_IN(MWX5_IB_ATTW_STEEWING_ANCHOW_FT_TYPE,
			     enum mwx5_ib_uapi_fwow_tabwe_type,
			     UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_STEEWING_ANCHOW_PWIOWITY,
			   UVEWBS_ATTW_TYPE(u16),
			   UA_MANDATOWY),
	UVEWBS_ATTW_PTW_IN(MWX5_IB_ATTW_STEEWING_ANCHOW_FT_ID,
			   UVEWBS_ATTW_TYPE(u32),
			   UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_METHOD_DESTWOY(
	MWX5_IB_METHOD_STEEWING_ANCHOW_DESTWOY,
	UVEWBS_ATTW_IDW(MWX5_IB_ATTW_STEEWING_ANCHOW_DESTWOY_HANDWE,
			MWX5_IB_OBJECT_STEEWING_ANCHOW,
			UVEWBS_ACCESS_DESTWOY,
			UA_MANDATOWY));

DECWAWE_UVEWBS_NAMED_OBJECT(
	MWX5_IB_OBJECT_STEEWING_ANCHOW,
	UVEWBS_TYPE_AWWOC_IDW(steewing_anchow_cweanup),
	&UVEWBS_METHOD(MWX5_IB_METHOD_STEEWING_ANCHOW_CWEATE),
	&UVEWBS_METHOD(MWX5_IB_METHOD_STEEWING_ANCHOW_DESTWOY));

const stwuct uapi_definition mwx5_ib_fwow_defs[] = {
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(
		MWX5_IB_OBJECT_FWOW_MATCHEW),
	UAPI_DEF_CHAIN_OBJ_TWEE(
		UVEWBS_OBJECT_FWOW,
		&mwx5_ib_fs),
	UAPI_DEF_CHAIN_OBJ_TWEE(UVEWBS_OBJECT_FWOW_ACTION,
				&mwx5_ib_fwow_actions),
	UAPI_DEF_CHAIN_OBJ_TWEE_NAMED(
		MWX5_IB_OBJECT_STEEWING_ANCHOW,
		UAPI_DEF_IS_OBJ_SUPPOWTED(mwx5_ib_shawed_ft_awwowed)),
	{},
};

static const stwuct ib_device_ops fwow_ops = {
	.cweate_fwow = mwx5_ib_cweate_fwow,
	.destwoy_fwow = mwx5_ib_destwoy_fwow,
	.destwoy_fwow_action = mwx5_ib_destwoy_fwow_action,
};

int mwx5_ib_fs_init(stwuct mwx5_ib_dev *dev)
{
	dev->fwow_db = kzawwoc(sizeof(*dev->fwow_db), GFP_KEWNEW);

	if (!dev->fwow_db)
		wetuwn -ENOMEM;

	mutex_init(&dev->fwow_db->wock);

	ib_set_device_ops(&dev->ib_dev, &fwow_ops);
	wetuwn 0;
}
