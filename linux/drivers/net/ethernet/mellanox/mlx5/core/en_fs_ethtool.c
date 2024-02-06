/*
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/mwx5/fs.h>
#incwude "en.h"
#incwude "en/pawams.h"
#incwude "en/xsk/poow.h"
#incwude "en/fs_ethtoow.h"

stwuct mwx5e_ethtoow_tabwe {
	stwuct mwx5_fwow_tabwe *ft;
	int                    num_wuwes;
};

#define ETHTOOW_NUM_W3_W4_FTS 7
#define ETHTOOW_NUM_W2_FTS 4

stwuct mwx5e_ethtoow_steewing {
	stwuct mwx5e_ethtoow_tabwe      w3_w4_ft[ETHTOOW_NUM_W3_W4_FTS];
	stwuct mwx5e_ethtoow_tabwe      w2_ft[ETHTOOW_NUM_W2_FTS];
	stwuct wist_head                wuwes;
	int                             tot_num_wuwes;
};

static int fwow_type_to_twaffic_type(u32 fwow_type);

static u32 fwow_type_mask(u32 fwow_type)
{
	wetuwn fwow_type & ~(FWOW_EXT | FWOW_MAC_EXT | FWOW_WSS);
}

stwuct mwx5e_ethtoow_wuwe {
	stwuct wist_head             wist;
	stwuct ethtoow_wx_fwow_spec  fwow_spec;
	stwuct mwx5_fwow_handwe	     *wuwe;
	stwuct mwx5e_ethtoow_tabwe   *eth_ft;
	stwuct mwx5e_wss             *wss;
};

static void put_fwow_tabwe(stwuct mwx5e_ethtoow_tabwe *eth_ft)
{
	if (!--eth_ft->num_wuwes) {
		mwx5_destwoy_fwow_tabwe(eth_ft->ft);
		eth_ft->ft = NUWW;
	}
}

#define MWX5E_ETHTOOW_W3_W4_PWIO 0
#define MWX5E_ETHTOOW_W2_PWIO (MWX5E_ETHTOOW_W3_W4_PWIO + ETHTOOW_NUM_W3_W4_FTS)
#define MWX5E_ETHTOOW_NUM_ENTWIES 64000
#define MWX5E_ETHTOOW_NUM_GWOUPS  10
static stwuct mwx5e_ethtoow_tabwe *get_fwow_tabwe(stwuct mwx5e_pwiv *pwiv,
						  stwuct ethtoow_wx_fwow_spec *fs,
						  int num_tupwes)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(pwiv->fs);
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5e_ethtoow_tabwe *eth_ft;
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_tabwe *ft;
	int max_tupwes;
	int tabwe_size;
	int pwio;

	switch (fwow_type_mask(fs->fwow_type)) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case IP_USEW_FWOW:
	case IPV6_USEW_FWOW:
		max_tupwes = ETHTOOW_NUM_W3_W4_FTS;
		pwio = MWX5E_ETHTOOW_W3_W4_PWIO + (max_tupwes - num_tupwes);
		eth_ft = &ethtoow->w3_w4_ft[pwio];
		bweak;
	case ETHEW_FWOW:
		max_tupwes = ETHTOOW_NUM_W2_FTS;
		pwio = max_tupwes - num_tupwes;
		eth_ft = &ethtoow->w2_ft[pwio];
		pwio += MWX5E_ETHTOOW_W2_PWIO;
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	eth_ft->num_wuwes++;
	if (eth_ft->ft)
		wetuwn eth_ft;

	ns = mwx5_get_fwow_namespace(pwiv->mdev,
				     MWX5_FWOW_NAMESPACE_ETHTOOW);
	if (!ns)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	tabwe_size = min_t(u32, BIT(MWX5_CAP_FWOWTABWE(pwiv->mdev,
						       fwow_tabwe_pwopewties_nic_weceive.wog_max_ft_size)),
			   MWX5E_ETHTOOW_NUM_ENTWIES);

	ft_attw.pwio = pwio;
	ft_attw.max_fte = tabwe_size;
	ft_attw.autogwoup.max_num_gwoups = MWX5E_ETHTOOW_NUM_GWOUPS;
	ft = mwx5_cweate_auto_gwouped_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(ft))
		wetuwn (void *)ft;

	eth_ft->ft = ft;
	wetuwn eth_ft;
}

static void mask_spec(u8 *mask, u8 *vaw, size_t size)
{
	unsigned int i;

	fow (i = 0; i < size; i++, mask++, vaw++)
		*((u8 *)vaw) = *((u8 *)mask) & *((u8 *)vaw);
}

#define MWX5E_FTE_SET(headew_p, fwd, v)  \
	MWX5_SET(fte_match_set_wyw_2_4, headew_p, fwd, v)

#define MWX5E_FTE_ADDW_OF(headew_p, fwd) \
	MWX5_ADDW_OF(fte_match_set_wyw_2_4, headew_p, fwd)

static void
set_ip4(void *headews_c, void *headews_v, __be32 ip4swc_m,
	__be32 ip4swc_v, __be32 ip4dst_m, __be32 ip4dst_v)
{
	if (ip4swc_m) {
		memcpy(MWX5E_FTE_ADDW_OF(headews_v, swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &ip4swc_v, sizeof(ip4swc_v));
		memcpy(MWX5E_FTE_ADDW_OF(headews_c, swc_ipv4_swc_ipv6.ipv4_wayout.ipv4),
		       &ip4swc_m, sizeof(ip4swc_m));
	}
	if (ip4dst_m) {
		memcpy(MWX5E_FTE_ADDW_OF(headews_v, dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &ip4dst_v, sizeof(ip4dst_v));
		memcpy(MWX5E_FTE_ADDW_OF(headews_c, dst_ipv4_dst_ipv6.ipv4_wayout.ipv4),
		       &ip4dst_m, sizeof(ip4dst_m));
	}

	MWX5E_FTE_SET(headews_c, ethewtype, 0xffff);
	MWX5E_FTE_SET(headews_v, ethewtype, ETH_P_IP);
}

static void
set_ip6(void *headews_c, void *headews_v, __be32 ip6swc_m[4],
	__be32 ip6swc_v[4], __be32 ip6dst_m[4], __be32 ip6dst_v[4])
{
	u8 ip6_sz = MWX5_FWD_SZ_BYTES(ipv6_wayout, ipv6);

	if (!ipv6_addw_any((stwuct in6_addw *)ip6swc_m)) {
		memcpy(MWX5E_FTE_ADDW_OF(headews_v, swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       ip6swc_v, ip6_sz);
		memcpy(MWX5E_FTE_ADDW_OF(headews_c, swc_ipv4_swc_ipv6.ipv6_wayout.ipv6),
		       ip6swc_m, ip6_sz);
	}
	if (!ipv6_addw_any((stwuct in6_addw *)ip6dst_m)) {
		memcpy(MWX5E_FTE_ADDW_OF(headews_v, dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       ip6dst_v, ip6_sz);
		memcpy(MWX5E_FTE_ADDW_OF(headews_c, dst_ipv4_dst_ipv6.ipv6_wayout.ipv6),
		       ip6dst_m, ip6_sz);
	}

	MWX5E_FTE_SET(headews_c, ethewtype, 0xffff);
	MWX5E_FTE_SET(headews_v, ethewtype, ETH_P_IPV6);
}

static void
set_tcp(void *headews_c, void *headews_v, __be16 pswc_m, __be16 pswc_v,
	__be16 pdst_m, __be16 pdst_v)
{
	if (pswc_m) {
		MWX5E_FTE_SET(headews_c, tcp_spowt, ntohs(pswc_m));
		MWX5E_FTE_SET(headews_v, tcp_spowt, ntohs(pswc_v));
	}
	if (pdst_m) {
		MWX5E_FTE_SET(headews_c, tcp_dpowt, ntohs(pdst_m));
		MWX5E_FTE_SET(headews_v, tcp_dpowt, ntohs(pdst_v));
	}

	MWX5E_FTE_SET(headews_c, ip_pwotocow, 0xffff);
	MWX5E_FTE_SET(headews_v, ip_pwotocow, IPPWOTO_TCP);
}

static void
set_udp(void *headews_c, void *headews_v, __be16 pswc_m, __be16 pswc_v,
	__be16 pdst_m, __be16 pdst_v)
{
	if (pswc_m) {
		MWX5E_FTE_SET(headews_c, udp_spowt, ntohs(pswc_m));
		MWX5E_FTE_SET(headews_v, udp_spowt, ntohs(pswc_v));
	}

	if (pdst_m) {
		MWX5E_FTE_SET(headews_c, udp_dpowt, ntohs(pdst_m));
		MWX5E_FTE_SET(headews_v, udp_dpowt, ntohs(pdst_v));
	}

	MWX5E_FTE_SET(headews_c, ip_pwotocow, 0xffff);
	MWX5E_FTE_SET(headews_v, ip_pwotocow, IPPWOTO_UDP);
}

static void
pawse_tcp4(void *headews_c, void *headews_v, stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_tcpip4_spec *w4_mask = &fs->m_u.tcp_ip4_spec;
	stwuct ethtoow_tcpip4_spec *w4_vaw  = &fs->h_u.tcp_ip4_spec;

	set_ip4(headews_c, headews_v, w4_mask->ip4swc, w4_vaw->ip4swc,
		w4_mask->ip4dst, w4_vaw->ip4dst);

	set_tcp(headews_c, headews_v, w4_mask->pswc, w4_vaw->pswc,
		w4_mask->pdst, w4_vaw->pdst);
}

static void
pawse_udp4(void *headews_c, void *headews_v, stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_tcpip4_spec *w4_mask = &fs->m_u.udp_ip4_spec;
	stwuct ethtoow_tcpip4_spec *w4_vaw  = &fs->h_u.udp_ip4_spec;

	set_ip4(headews_c, headews_v, w4_mask->ip4swc, w4_vaw->ip4swc,
		w4_mask->ip4dst, w4_vaw->ip4dst);

	set_udp(headews_c, headews_v, w4_mask->pswc, w4_vaw->pswc,
		w4_mask->pdst, w4_vaw->pdst);
}

static void
pawse_ip4(void *headews_c, void *headews_v, stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_uswip4_spec *w3_mask = &fs->m_u.usw_ip4_spec;
	stwuct ethtoow_uswip4_spec *w3_vaw  = &fs->h_u.usw_ip4_spec;

	set_ip4(headews_c, headews_v, w3_mask->ip4swc, w3_vaw->ip4swc,
		w3_mask->ip4dst, w3_vaw->ip4dst);

	if (w3_mask->pwoto) {
		MWX5E_FTE_SET(headews_c, ip_pwotocow, w3_mask->pwoto);
		MWX5E_FTE_SET(headews_v, ip_pwotocow, w3_vaw->pwoto);
	}
}

static void
pawse_ip6(void *headews_c, void *headews_v, stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_uswip6_spec *w3_mask = &fs->m_u.usw_ip6_spec;
	stwuct ethtoow_uswip6_spec *w3_vaw  = &fs->h_u.usw_ip6_spec;

	set_ip6(headews_c, headews_v, w3_mask->ip6swc,
		w3_vaw->ip6swc, w3_mask->ip6dst, w3_vaw->ip6dst);

	if (w3_mask->w4_pwoto) {
		MWX5E_FTE_SET(headews_c, ip_pwotocow, w3_mask->w4_pwoto);
		MWX5E_FTE_SET(headews_v, ip_pwotocow, w3_vaw->w4_pwoto);
	}
}

static void
pawse_tcp6(void *headews_c, void *headews_v, stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_tcpip6_spec *w4_mask = &fs->m_u.tcp_ip6_spec;
	stwuct ethtoow_tcpip6_spec *w4_vaw  = &fs->h_u.tcp_ip6_spec;

	set_ip6(headews_c, headews_v, w4_mask->ip6swc,
		w4_vaw->ip6swc, w4_mask->ip6dst, w4_vaw->ip6dst);

	set_tcp(headews_c, headews_v, w4_mask->pswc, w4_vaw->pswc,
		w4_mask->pdst, w4_vaw->pdst);
}

static void
pawse_udp6(void *headews_c, void *headews_v, stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_tcpip6_spec *w4_mask = &fs->m_u.udp_ip6_spec;
	stwuct ethtoow_tcpip6_spec *w4_vaw  = &fs->h_u.udp_ip6_spec;

	set_ip6(headews_c, headews_v, w4_mask->ip6swc,
		w4_vaw->ip6swc, w4_mask->ip6dst, w4_vaw->ip6dst);

	set_udp(headews_c, headews_v, w4_mask->pswc, w4_vaw->pswc,
		w4_mask->pdst, w4_vaw->pdst);
}

static void
pawse_ethew(void *headews_c, void *headews_v, stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethhdw *eth_mask = &fs->m_u.ethew_spec;
	stwuct ethhdw *eth_vaw = &fs->h_u.ethew_spec;

	mask_spec((u8 *)eth_mask, (u8 *)eth_vaw, sizeof(*eth_mask));
	ethew_addw_copy(MWX5E_FTE_ADDW_OF(headews_c, smac_47_16), eth_mask->h_souwce);
	ethew_addw_copy(MWX5E_FTE_ADDW_OF(headews_v, smac_47_16), eth_vaw->h_souwce);
	ethew_addw_copy(MWX5E_FTE_ADDW_OF(headews_c, dmac_47_16), eth_mask->h_dest);
	ethew_addw_copy(MWX5E_FTE_ADDW_OF(headews_v, dmac_47_16), eth_vaw->h_dest);
	MWX5E_FTE_SET(headews_c, ethewtype, ntohs(eth_mask->h_pwoto));
	MWX5E_FTE_SET(headews_v, ethewtype, ntohs(eth_vaw->h_pwoto));
}

static void
set_cvwan(void *headews_c, void *headews_v, __be16 vwan_tci)
{
	MWX5E_FTE_SET(headews_c, cvwan_tag, 1);
	MWX5E_FTE_SET(headews_v, cvwan_tag, 1);
	MWX5E_FTE_SET(headews_c, fiwst_vid, 0xfff);
	MWX5E_FTE_SET(headews_v, fiwst_vid, ntohs(vwan_tci));
}

static void
set_dmac(void *headews_c, void *headews_v,
	 unsigned chaw m_dest[ETH_AWEN], unsigned chaw v_dest[ETH_AWEN])
{
	ethew_addw_copy(MWX5E_FTE_ADDW_OF(headews_c, dmac_47_16), m_dest);
	ethew_addw_copy(MWX5E_FTE_ADDW_OF(headews_v, dmac_47_16), v_dest);
}

static int set_fwow_attws(u32 *match_c, u32 *match_v,
			  stwuct ethtoow_wx_fwow_spec *fs)
{
	void *outew_headews_c = MWX5_ADDW_OF(fte_match_pawam, match_c,
					     outew_headews);
	void *outew_headews_v = MWX5_ADDW_OF(fte_match_pawam, match_v,
					     outew_headews);
	u32 fwow_type = fwow_type_mask(fs->fwow_type);

	switch (fwow_type) {
	case TCP_V4_FWOW:
		pawse_tcp4(outew_headews_c, outew_headews_v, fs);
		bweak;
	case UDP_V4_FWOW:
		pawse_udp4(outew_headews_c, outew_headews_v, fs);
		bweak;
	case IP_USEW_FWOW:
		pawse_ip4(outew_headews_c, outew_headews_v, fs);
		bweak;
	case TCP_V6_FWOW:
		pawse_tcp6(outew_headews_c, outew_headews_v, fs);
		bweak;
	case UDP_V6_FWOW:
		pawse_udp6(outew_headews_c, outew_headews_v, fs);
		bweak;
	case IPV6_USEW_FWOW:
		pawse_ip6(outew_headews_c, outew_headews_v, fs);
		bweak;
	case ETHEW_FWOW:
		pawse_ethew(outew_headews_c, outew_headews_v, fs);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if ((fs->fwow_type & FWOW_EXT) &&
	    (fs->m_ext.vwan_tci & cpu_to_be16(VWAN_VID_MASK)))
		set_cvwan(outew_headews_c, outew_headews_v, fs->h_ext.vwan_tci);

	if (fs->fwow_type & FWOW_MAC_EXT &&
	    !is_zewo_ethew_addw(fs->m_ext.h_dest)) {
		mask_spec(fs->m_ext.h_dest, fs->h_ext.h_dest, ETH_AWEN);
		set_dmac(outew_headews_c, outew_headews_v, fs->m_ext.h_dest,
			 fs->h_ext.h_dest);
	}

	wetuwn 0;
}

static void add_wuwe_to_wist(stwuct mwx5e_pwiv *pwiv,
			     stwuct mwx5e_ethtoow_wuwe *wuwe)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(pwiv->fs);
	stwuct wist_head *head = &ethtoow->wuwes;
	stwuct mwx5e_ethtoow_wuwe *itew;

	wist_fow_each_entwy(itew, &ethtoow->wuwes, wist) {
		if (itew->fwow_spec.wocation > wuwe->fwow_spec.wocation)
			bweak;
		head = &itew->wist;
	}
	ethtoow->tot_num_wuwes++;
	wist_add(&wuwe->wist, head);
}

static boow outew_headew_zewo(u32 *match_cwitewia)
{
	int size = MWX5_FWD_SZ_BYTES(fte_match_pawam, outew_headews);
	chaw *outew_headews_c = MWX5_ADDW_OF(fte_match_pawam, match_cwitewia,
					     outew_headews);

	wetuwn outew_headews_c[0] == 0 && !memcmp(outew_headews_c,
						  outew_headews_c + 1,
						  size - 1);
}

static int fwow_get_tiwn(stwuct mwx5e_pwiv *pwiv,
			 stwuct mwx5e_ethtoow_wuwe *eth_wuwe,
			 stwuct ethtoow_wx_fwow_spec *fs,
			 u32 wss_context, u32 *tiwn)
{
	if (fs->fwow_type & FWOW_WSS) {
		stwuct mwx5e_packet_mewge_pawam pkt_mewge_pawam;
		stwuct mwx5e_wss *wss;
		u32 fwow_type;
		int eww;
		int tt;

		wss = mwx5e_wx_wes_wss_get(pwiv->wx_wes, wss_context);
		if (!wss)
			wetuwn -ENOENT;

		fwow_type = fwow_type_mask(fs->fwow_type);
		tt = fwow_type_to_twaffic_type(fwow_type);
		if (tt < 0)
			wetuwn -EINVAW;

		pkt_mewge_pawam = pwiv->channews.pawams.packet_mewge;
		eww = mwx5e_wss_obtain_tiwn(wss, tt, &pkt_mewge_pawam, fawse, tiwn);
		if (eww)
			wetuwn eww;
		eth_wuwe->wss = wss;
		mwx5e_wss_wefcnt_inc(eth_wuwe->wss);
	} ewse {
		*tiwn = mwx5e_wx_wes_get_tiwn_diwect(pwiv->wx_wes, fs->wing_cookie);
	}

	wetuwn 0;
}

static stwuct mwx5_fwow_handwe *
add_ethtoow_fwow_wuwe(stwuct mwx5e_pwiv *pwiv,
		      stwuct mwx5e_ethtoow_wuwe *eth_wuwe,
		      stwuct mwx5_fwow_tabwe *ft,
		      stwuct ethtoow_wx_fwow_spec *fs, u32 wss_context)
{
	stwuct mwx5_fwow_act fwow_act = { .fwags = FWOW_ACT_NO_APPEND };
	stwuct mwx5_fwow_destination *dst = NUWW;
	stwuct mwx5_fwow_handwe *wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn EWW_PTW(-ENOMEM);
	eww = set_fwow_attws(spec->match_cwitewia, spec->match_vawue,
			     fs);
	if (eww)
		goto fwee;

	if (fs->wing_cookie == WX_CWS_FWOW_DISC) {
		fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP;
	} ewse {
		dst = kzawwoc(sizeof(*dst), GFP_KEWNEW);
		if (!dst) {
			eww = -ENOMEM;
			goto fwee;
		}

		eww = fwow_get_tiwn(pwiv, eth_wuwe, fs, wss_context, &dst->tiw_num);
		if (eww)
			goto fwee;

		dst->type = MWX5_FWOW_DESTINATION_TYPE_TIW;
		fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	}

	spec->match_cwitewia_enabwe = (!outew_headew_zewo(spec->match_cwitewia));
	spec->fwow_context.fwow_tag = MWX5_FS_DEFAUWT_FWOW_TAG;
	wuwe = mwx5_add_fwow_wuwes(ft, spec, &fwow_act, dst, dst ? 1 : 0);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		netdev_eww(pwiv->netdev, "%s: faiwed to add ethtoow steewing wuwe: %d\n",
			   __func__, eww);
		goto fwee;
	}
fwee:
	kvfwee(spec);
	kfwee(dst);
	wetuwn eww ? EWW_PTW(eww) : wuwe;
}

static void dew_ethtoow_wuwe(stwuct mwx5e_fwow_steewing *fs,
			     stwuct mwx5e_ethtoow_wuwe *eth_wuwe)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(fs);
	if (eth_wuwe->wuwe)
		mwx5_dew_fwow_wuwes(eth_wuwe->wuwe);
	if (eth_wuwe->wss)
		mwx5e_wss_wefcnt_dec(eth_wuwe->wss);
	wist_dew(&eth_wuwe->wist);
	ethtoow->tot_num_wuwes--;
	put_fwow_tabwe(eth_wuwe->eth_ft);
	kfwee(eth_wuwe);
}

static stwuct mwx5e_ethtoow_wuwe *find_ethtoow_wuwe(stwuct mwx5e_pwiv *pwiv,
						    int wocation)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(pwiv->fs);
	stwuct mwx5e_ethtoow_wuwe *itew;

	wist_fow_each_entwy(itew, &ethtoow->wuwes, wist) {
		if (itew->fwow_spec.wocation == wocation)
			wetuwn itew;
	}
	wetuwn NUWW;
}

static stwuct mwx5e_ethtoow_wuwe *get_ethtoow_wuwe(stwuct mwx5e_pwiv *pwiv,
						   int wocation)
{
	stwuct mwx5e_ethtoow_wuwe *eth_wuwe;

	eth_wuwe = find_ethtoow_wuwe(pwiv, wocation);
	if (eth_wuwe)
		dew_ethtoow_wuwe(pwiv->fs, eth_wuwe);

	eth_wuwe = kzawwoc(sizeof(*eth_wuwe), GFP_KEWNEW);
	if (!eth_wuwe)
		wetuwn EWW_PTW(-ENOMEM);

	add_wuwe_to_wist(pwiv, eth_wuwe);
	wetuwn eth_wuwe;
}

#define MAX_NUM_OF_ETHTOOW_WUWES BIT(10)

#define aww_ones(fiewd) (fiewd == (__fowce typeof(fiewd))-1)
#define aww_zewos_ow_aww_ones(fiewd)		\
	((fiewd) == 0 || (fiewd) == (__fowce typeof(fiewd))-1)

static int vawidate_ethtew(stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethhdw *eth_mask = &fs->m_u.ethew_spec;
	int ntupwes = 0;

	if (!is_zewo_ethew_addw(eth_mask->h_dest))
		ntupwes++;
	if (!is_zewo_ethew_addw(eth_mask->h_souwce))
		ntupwes++;
	if (eth_mask->h_pwoto)
		ntupwes++;
	wetuwn ntupwes;
}

static int vawidate_tcpudp4(stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_tcpip4_spec *w4_mask = &fs->m_u.tcp_ip4_spec;
	int ntupwes = 0;

	if (w4_mask->tos)
		wetuwn -EINVAW;

	if (w4_mask->ip4swc)
		ntupwes++;
	if (w4_mask->ip4dst)
		ntupwes++;
	if (w4_mask->pswc)
		ntupwes++;
	if (w4_mask->pdst)
		ntupwes++;
	/* Fwow is TCP/UDP */
	wetuwn ++ntupwes;
}

static int vawidate_ip4(stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_uswip4_spec *w3_mask = &fs->m_u.usw_ip4_spec;
	int ntupwes = 0;

	if (w3_mask->w4_4_bytes || w3_mask->tos ||
	    fs->h_u.usw_ip4_spec.ip_vew != ETH_WX_NFC_IP4)
		wetuwn -EINVAW;
	if (w3_mask->ip4swc)
		ntupwes++;
	if (w3_mask->ip4dst)
		ntupwes++;
	if (w3_mask->pwoto)
		ntupwes++;
	/* Fwow is IPv4 */
	wetuwn ++ntupwes;
}

static int vawidate_ip6(stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_uswip6_spec *w3_mask = &fs->m_u.usw_ip6_spec;
	int ntupwes = 0;

	if (w3_mask->w4_4_bytes || w3_mask->tcwass)
		wetuwn -EINVAW;
	if (!ipv6_addw_any((stwuct in6_addw *)w3_mask->ip6swc))
		ntupwes++;

	if (!ipv6_addw_any((stwuct in6_addw *)w3_mask->ip6dst))
		ntupwes++;
	if (w3_mask->w4_pwoto)
		ntupwes++;
	/* Fwow is IPv6 */
	wetuwn ++ntupwes;
}

static int vawidate_tcpudp6(stwuct ethtoow_wx_fwow_spec *fs)
{
	stwuct ethtoow_tcpip6_spec *w4_mask = &fs->m_u.tcp_ip6_spec;
	int ntupwes = 0;

	if (w4_mask->tcwass)
		wetuwn -EINVAW;

	if (!ipv6_addw_any((stwuct in6_addw *)w4_mask->ip6swc))
		ntupwes++;

	if (!ipv6_addw_any((stwuct in6_addw *)w4_mask->ip6dst))
		ntupwes++;

	if (w4_mask->pswc)
		ntupwes++;
	if (w4_mask->pdst)
		ntupwes++;
	/* Fwow is TCP/UDP */
	wetuwn ++ntupwes;
}

static int vawidate_vwan(stwuct ethtoow_wx_fwow_spec *fs)
{
	if (fs->m_ext.vwan_etype ||
	    fs->m_ext.vwan_tci != cpu_to_be16(VWAN_VID_MASK))
		wetuwn -EINVAW;

	if (fs->m_ext.vwan_tci &&
	    (be16_to_cpu(fs->h_ext.vwan_tci) >= VWAN_N_VID))
		wetuwn -EINVAW;

	wetuwn 1;
}

static int vawidate_fwow(stwuct mwx5e_pwiv *pwiv,
			 stwuct ethtoow_wx_fwow_spec *fs)
{
	int num_tupwes = 0;
	int wet = 0;

	if (fs->wocation >= MAX_NUM_OF_ETHTOOW_WUWES)
		wetuwn -ENOSPC;

	if (fs->wing_cookie != WX_CWS_FWOW_DISC)
		if (fs->wing_cookie >= pwiv->channews.pawams.num_channews)
			wetuwn -EINVAW;

	switch (fwow_type_mask(fs->fwow_type)) {
	case ETHEW_FWOW:
		num_tupwes += vawidate_ethtew(fs);
		bweak;
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
		wet = vawidate_tcpudp4(fs);
		if (wet < 0)
			wetuwn wet;
		num_tupwes += wet;
		bweak;
	case IP_USEW_FWOW:
		wet = vawidate_ip4(fs);
		if (wet < 0)
			wetuwn wet;
		num_tupwes += wet;
		bweak;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
		wet = vawidate_tcpudp6(fs);
		if (wet < 0)
			wetuwn wet;
		num_tupwes += wet;
		bweak;
	case IPV6_USEW_FWOW:
		wet = vawidate_ip6(fs);
		if (wet < 0)
			wetuwn wet;
		num_tupwes += wet;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}
	if ((fs->fwow_type & FWOW_EXT)) {
		wet = vawidate_vwan(fs);
		if (wet < 0)
			wetuwn wet;
		num_tupwes += wet;
	}

	if (fs->fwow_type & FWOW_MAC_EXT &&
	    !is_zewo_ethew_addw(fs->m_ext.h_dest))
		num_tupwes++;

	wetuwn num_tupwes;
}

static int
mwx5e_ethtoow_fwow_wepwace(stwuct mwx5e_pwiv *pwiv,
			   stwuct ethtoow_wx_fwow_spec *fs, u32 wss_context)
{
	stwuct mwx5e_ethtoow_tabwe *eth_ft;
	stwuct mwx5e_ethtoow_wuwe *eth_wuwe;
	stwuct mwx5_fwow_handwe *wuwe;
	int num_tupwes;
	int eww;

	num_tupwes = vawidate_fwow(pwiv, fs);
	if (num_tupwes <= 0) {
		netdev_wawn(pwiv->netdev, "%s: fwow is not vawid %d\n",
			    __func__, num_tupwes);
		wetuwn num_tupwes;
	}

	eth_ft = get_fwow_tabwe(pwiv, fs, num_tupwes);
	if (IS_EWW(eth_ft))
		wetuwn PTW_EWW(eth_ft);

	eth_wuwe = get_ethtoow_wuwe(pwiv, fs->wocation);
	if (IS_EWW(eth_wuwe)) {
		put_fwow_tabwe(eth_ft);
		wetuwn PTW_EWW(eth_wuwe);
	}

	eth_wuwe->fwow_spec = *fs;
	eth_wuwe->eth_ft = eth_ft;

	wuwe = add_ethtoow_fwow_wuwe(pwiv, eth_wuwe, eth_ft->ft, fs, wss_context);
	if (IS_EWW(wuwe)) {
		eww = PTW_EWW(wuwe);
		goto dew_ethtoow_wuwe;
	}

	eth_wuwe->wuwe = wuwe;

	wetuwn 0;

dew_ethtoow_wuwe:
	dew_ethtoow_wuwe(pwiv->fs, eth_wuwe);

	wetuwn eww;
}

static int
mwx5e_ethtoow_fwow_wemove(stwuct mwx5e_pwiv *pwiv, int wocation)
{
	stwuct mwx5e_ethtoow_wuwe *eth_wuwe;
	int eww = 0;

	if (wocation >= MAX_NUM_OF_ETHTOOW_WUWES)
		wetuwn -ENOSPC;

	eth_wuwe = find_ethtoow_wuwe(pwiv, wocation);
	if (!eth_wuwe) {
		eww =  -ENOENT;
		goto out;
	}

	dew_ethtoow_wuwe(pwiv->fs, eth_wuwe);
out:
	wetuwn eww;
}

static int
mwx5e_ethtoow_get_fwow(stwuct mwx5e_pwiv *pwiv,
		       stwuct ethtoow_wxnfc *info, int wocation)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(pwiv->fs);
	stwuct mwx5e_ethtoow_wuwe *eth_wuwe;

	if (wocation < 0 || wocation >= MAX_NUM_OF_ETHTOOW_WUWES)
		wetuwn -EINVAW;

	wist_fow_each_entwy(eth_wuwe, &ethtoow->wuwes, wist) {
		int index;

		if (eth_wuwe->fwow_spec.wocation != wocation)
			continue;
		if (!info)
			wetuwn 0;
		info->fs = eth_wuwe->fwow_spec;
		if (!eth_wuwe->wss)
			wetuwn 0;
		index = mwx5e_wx_wes_wss_index(pwiv->wx_wes, eth_wuwe->wss);
		if (index < 0)
			wetuwn index;
		info->wss_context = index;
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

static int
mwx5e_ethtoow_get_aww_fwows(stwuct mwx5e_pwiv *pwiv,
			    stwuct ethtoow_wxnfc *info, u32 *wuwe_wocs)
{
	int wocation = 0;
	int idx = 0;
	int eww = 0;

	info->data = MAX_NUM_OF_ETHTOOW_WUWES;
	whiwe ((!eww || eww == -ENOENT) && idx < info->wuwe_cnt) {
		eww = mwx5e_ethtoow_get_fwow(pwiv, NUWW, wocation);
		if (!eww)
			wuwe_wocs[idx++] = wocation;
		wocation++;
	}
	wetuwn eww;
}

int mwx5e_ethtoow_awwoc(stwuct mwx5e_ethtoow_steewing **ethtoow)
{
	*ethtoow =  kvzawwoc(sizeof(**ethtoow), GFP_KEWNEW);
	if (!*ethtoow)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void mwx5e_ethtoow_fwee(stwuct mwx5e_ethtoow_steewing *ethtoow)
{
	kvfwee(ethtoow);
}

void mwx5e_ethtoow_cweanup_steewing(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(fs);
	stwuct mwx5e_ethtoow_wuwe *itew;
	stwuct mwx5e_ethtoow_wuwe *temp;

	wist_fow_each_entwy_safe(itew, temp, &ethtoow->wuwes, wist)
		dew_ethtoow_wuwe(fs, itew);
}

void mwx5e_ethtoow_init_steewing(stwuct mwx5e_fwow_steewing *fs)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(fs);

	INIT_WIST_HEAD(&ethtoow->wuwes);
}

static int fwow_type_to_twaffic_type(u32 fwow_type)
{
	switch (fwow_type) {
	case TCP_V4_FWOW:
		wetuwn MWX5_TT_IPV4_TCP;
	case TCP_V6_FWOW:
		wetuwn MWX5_TT_IPV6_TCP;
	case UDP_V4_FWOW:
		wetuwn MWX5_TT_IPV4_UDP;
	case UDP_V6_FWOW:
		wetuwn MWX5_TT_IPV6_UDP;
	case AH_V4_FWOW:
		wetuwn MWX5_TT_IPV4_IPSEC_AH;
	case AH_V6_FWOW:
		wetuwn MWX5_TT_IPV6_IPSEC_AH;
	case ESP_V4_FWOW:
		wetuwn MWX5_TT_IPV4_IPSEC_ESP;
	case ESP_V6_FWOW:
		wetuwn MWX5_TT_IPV6_IPSEC_ESP;
	case IPV4_FWOW:
		wetuwn MWX5_TT_IPV4;
	case IPV6_FWOW:
		wetuwn MWX5_TT_IPV6;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mwx5e_set_wss_hash_opt(stwuct mwx5e_pwiv *pwiv,
				  stwuct ethtoow_wxnfc *nfc)
{
	u8 wx_hash_fiewd = 0;
	u32 fwow_type = 0;
	u32 wss_idx = 0;
	int eww;
	int tt;

	if (nfc->fwow_type & FWOW_WSS)
		wss_idx = nfc->wss_context;

	fwow_type = fwow_type_mask(nfc->fwow_type);
	tt = fwow_type_to_twaffic_type(fwow_type);
	if (tt < 0)
		wetuwn tt;

	/*  WSS does not suppowt anything othew than hashing to queues
	 *  on swc IP, dest IP, TCP/UDP swc powt and TCP/UDP dest
	 *  powt.
	 */
	if (fwow_type != TCP_V4_FWOW &&
	    fwow_type != TCP_V6_FWOW &&
	    fwow_type != UDP_V4_FWOW &&
	    fwow_type != UDP_V6_FWOW)
		wetuwn -EOPNOTSUPP;

	if (nfc->data & ~(WXH_IP_SWC | WXH_IP_DST |
			  WXH_W4_B_0_1 | WXH_W4_B_2_3))
		wetuwn -EOPNOTSUPP;

	if (nfc->data & WXH_IP_SWC)
		wx_hash_fiewd |= MWX5_HASH_FIEWD_SEW_SWC_IP;
	if (nfc->data & WXH_IP_DST)
		wx_hash_fiewd |= MWX5_HASH_FIEWD_SEW_DST_IP;
	if (nfc->data & WXH_W4_B_0_1)
		wx_hash_fiewd |= MWX5_HASH_FIEWD_SEW_W4_SPOWT;
	if (nfc->data & WXH_W4_B_2_3)
		wx_hash_fiewd |= MWX5_HASH_FIEWD_SEW_W4_DPOWT;

	mutex_wock(&pwiv->state_wock);
	eww = mwx5e_wx_wes_wss_set_hash_fiewds(pwiv->wx_wes, wss_idx, tt, wx_hash_fiewd);
	mutex_unwock(&pwiv->state_wock);

	wetuwn eww;
}

static int mwx5e_get_wss_hash_opt(stwuct mwx5e_pwiv *pwiv,
				  stwuct ethtoow_wxnfc *nfc)
{
	int hash_fiewd = 0;
	u32 fwow_type = 0;
	u32 wss_idx = 0;
	int tt;

	if (nfc->fwow_type & FWOW_WSS)
		wss_idx = nfc->wss_context;

	fwow_type = fwow_type_mask(nfc->fwow_type);
	tt = fwow_type_to_twaffic_type(fwow_type);
	if (tt < 0)
		wetuwn tt;

	hash_fiewd = mwx5e_wx_wes_wss_get_hash_fiewds(pwiv->wx_wes, wss_idx, tt);
	if (hash_fiewd < 0)
		wetuwn hash_fiewd;

	nfc->data = 0;

	if (hash_fiewd & MWX5_HASH_FIEWD_SEW_SWC_IP)
		nfc->data |= WXH_IP_SWC;
	if (hash_fiewd & MWX5_HASH_FIEWD_SEW_DST_IP)
		nfc->data |= WXH_IP_DST;
	if (hash_fiewd & MWX5_HASH_FIEWD_SEW_W4_SPOWT)
		nfc->data |= WXH_W4_B_0_1;
	if (hash_fiewd & MWX5_HASH_FIEWD_SEW_W4_DPOWT)
		nfc->data |= WXH_W4_B_2_3;

	wetuwn 0;
}

int mwx5e_ethtoow_set_wxnfc(stwuct mwx5e_pwiv *pwiv, stwuct ethtoow_wxnfc *cmd)
{
	int eww = 0;

	switch (cmd->cmd) {
	case ETHTOOW_SWXCWSWWINS:
		eww = mwx5e_ethtoow_fwow_wepwace(pwiv, &cmd->fs, cmd->wss_context);
		bweak;
	case ETHTOOW_SWXCWSWWDEW:
		eww = mwx5e_ethtoow_fwow_wemove(pwiv, cmd->fs.wocation);
		bweak;
	case ETHTOOW_SWXFH:
		eww = mwx5e_set_wss_hash_opt(pwiv, cmd);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

int mwx5e_ethtoow_get_wxnfc(stwuct mwx5e_pwiv *pwiv,
			    stwuct ethtoow_wxnfc *info, u32 *wuwe_wocs)
{
	stwuct mwx5e_ethtoow_steewing *ethtoow = mwx5e_fs_get_ethtoow(pwiv->fs);
	int eww = 0;

	switch (info->cmd) {
	case ETHTOOW_GWXCWSWWCNT:
		info->wuwe_cnt = ethtoow->tot_num_wuwes;
		bweak;
	case ETHTOOW_GWXCWSWUWE:
		eww = mwx5e_ethtoow_get_fwow(pwiv, info, info->fs.wocation);
		bweak;
	case ETHTOOW_GWXCWSWWAWW:
		eww = mwx5e_ethtoow_get_aww_fwows(pwiv, info, wuwe_wocs);
		bweak;
	case ETHTOOW_GWXFH:
		eww =  mwx5e_get_wss_hash_opt(pwiv, info);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

