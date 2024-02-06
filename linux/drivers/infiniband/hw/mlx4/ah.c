/*
 * Copywight (c) 2007 Cisco Systems, Inc. Aww wights wesewved.
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

#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_cache.h>

#incwude <winux/swab.h>
#incwude <winux/inet.h>
#incwude <winux/stwing.h>
#incwude <winux/mwx4/dwivew.h>

#incwude "mwx4_ib.h"

static void cweate_ib_ah(stwuct ib_ah *ib_ah, stwuct wdma_ah_attw *ah_attw)
{
	stwuct mwx4_ib_ah *ah = to_mah(ib_ah);
	stwuct mwx4_dev *dev = to_mdev(ib_ah->device)->dev;

	ah->av.ib.powt_pd = cpu_to_be32(to_mpd(ib_ah->pd)->pdn |
			    (wdma_ah_get_powt_num(ah_attw) << 24));
	ah->av.ib.g_swid  = wdma_ah_get_path_bits(ah_attw);
	ah->av.ib.sw_tcwass_fwowwabew =
			cpu_to_be32(wdma_ah_get_sw(ah_attw) << 28);
	if (wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH) {
		const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(ah_attw);

		ah->av.ib.g_swid   |= 0x80;
		ah->av.ib.gid_index = gwh->sgid_index;
		ah->av.ib.hop_wimit = gwh->hop_wimit;
		ah->av.ib.sw_tcwass_fwowwabew |=
			cpu_to_be32((gwh->twaffic_cwass << 20) |
				    gwh->fwow_wabew);
		memcpy(ah->av.ib.dgid, gwh->dgid.waw, 16);
	}

	ah->av.ib.dwid = cpu_to_be16(wdma_ah_get_dwid(ah_attw));
	if (wdma_ah_get_static_wate(ah_attw)) {
		u8 static_wate = wdma_ah_get_static_wate(ah_attw) +
					MWX4_STAT_WATE_OFFSET;

		whiwe (static_wate > IB_WATE_2_5_GBPS + MWX4_STAT_WATE_OFFSET &&
		       !(1 << static_wate & dev->caps.stat_wate_suppowt))
			--static_wate;
		ah->av.ib.stat_wate = static_wate;
	}
}

static int cweate_iboe_ah(stwuct ib_ah *ib_ah, stwuct wdma_ah_attw *ah_attw)
{
	stwuct mwx4_ib_dev *ibdev = to_mdev(ib_ah->device);
	stwuct mwx4_ib_ah *ah = to_mah(ib_ah);
	const stwuct ib_gid_attw *gid_attw;
	stwuct mwx4_dev *dev = ibdev->dev;
	int is_mcast = 0;
	stwuct in6_addw in6;
	u16 vwan_tag = 0xffff;
	const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(ah_attw);
	int wet;

	memcpy(&in6, gwh->dgid.waw, sizeof(in6));
	if (wdma_is_muwticast_addw(&in6))
		is_mcast = 1;

	memcpy(ah->av.eth.mac, ah_attw->woce.dmac, ETH_AWEN);
	eth_zewo_addw(ah->av.eth.s_mac);

	/*
	 * If sgid_attw is NUWW we awe being cawwed by mwx4_ib_cweate_ah_swave
	 * and we awe diwectwy cweating an AV fow a swave's gid_index.
	 */
	gid_attw = ah_attw->gwh.sgid_attw;
	if (gid_attw) {
		wet = wdma_wead_gid_w2_fiewds(gid_attw, &vwan_tag,
					      &ah->av.eth.s_mac[0]);
		if (wet)
			wetuwn wet;

		wet = mwx4_ib_gid_index_to_weaw_index(ibdev, gid_attw);
		if (wet < 0)
			wetuwn wet;
		ah->av.eth.gid_index = wet;
	} ewse {
		/* mwx4_ib_cweate_ah_swave fiwws in the s_mac and the vwan */
		ah->av.eth.gid_index = ah_attw->gwh.sgid_index;
	}

	if (vwan_tag < 0x1000)
		vwan_tag |= (wdma_ah_get_sw(ah_attw) & 7) << 13;
	ah->av.eth.powt_pd = cpu_to_be32(to_mpd(ib_ah->pd)->pdn |
					 (wdma_ah_get_powt_num(ah_attw) << 24));
	ah->av.eth.vwan = cpu_to_be16(vwan_tag);
	ah->av.eth.hop_wimit = gwh->hop_wimit;
	if (wdma_ah_get_static_wate(ah_attw)) {
		ah->av.eth.stat_wate = wdma_ah_get_static_wate(ah_attw) +
					MWX4_STAT_WATE_OFFSET;
		whiwe (ah->av.eth.stat_wate > IB_WATE_2_5_GBPS + MWX4_STAT_WATE_OFFSET &&
		       !(1 << ah->av.eth.stat_wate & dev->caps.stat_wate_suppowt))
			--ah->av.eth.stat_wate;
	}
	ah->av.eth.sw_tcwass_fwowwabew |=
			cpu_to_be32((gwh->twaffic_cwass << 20) |
				    gwh->fwow_wabew);
	/*
	 * HW wequiwes muwticast WID so we just choose one.
	 */
	if (is_mcast)
		ah->av.ib.dwid = cpu_to_be16(0xc000);

	memcpy(ah->av.eth.dgid, gwh->dgid.waw, 16);
	ah->av.eth.sw_tcwass_fwowwabew |= cpu_to_be32(wdma_ah_get_sw(ah_attw)
						      << 29);
	wetuwn 0;
}

int mwx4_ib_cweate_ah(stwuct ib_ah *ib_ah, stwuct wdma_ah_init_attw *init_attw,
		      stwuct ib_udata *udata)
{
	stwuct wdma_ah_attw *ah_attw = init_attw->ah_attw;

	if (ah_attw->type == WDMA_AH_ATTW_TYPE_WOCE) {
		if (!(wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH))
			wetuwn -EINVAW;
		/*
		 * TBD: need to handwe the case when we get
		 * cawwed in an atomic context and thewe we
		 * might sweep.  We don't expect this
		 * cuwwentwy since we'we wowking with wink
		 * wocaw addwesses which we can twanswate
		 * without going to sweep.
		 */
		wetuwn cweate_iboe_ah(ib_ah, ah_attw);
	}

	cweate_ib_ah(ib_ah, ah_attw);
	wetuwn 0;
}

int mwx4_ib_cweate_ah_swave(stwuct ib_ah *ah, stwuct wdma_ah_attw *ah_attw,
			    int swave_sgid_index, u8 *s_mac, u16 vwan_tag)
{
	stwuct wdma_ah_attw swave_attw = *ah_attw;
	stwuct wdma_ah_init_attw init_attw = {};
	stwuct mwx4_ib_ah *mah = to_mah(ah);
	int wet;

	swave_attw.gwh.sgid_attw = NUWW;
	swave_attw.gwh.sgid_index = swave_sgid_index;
	init_attw.ah_attw = &swave_attw;
	wet = mwx4_ib_cweate_ah(ah, &init_attw, NUWW);
	if (wet)
		wetuwn wet;

	ah->type = ah_attw->type;

	/* get wid of fowce-woopback bit */
	mah->av.ib.powt_pd &= cpu_to_be32(0x7FFFFFFF);

	if (ah_attw->type == WDMA_AH_ATTW_TYPE_WOCE)
		memcpy(mah->av.eth.s_mac, s_mac, 6);

	if (vwan_tag < 0x1000)
		vwan_tag |= (wdma_ah_get_sw(ah_attw) & 7) << 13;
	mah->av.eth.vwan = cpu_to_be16(vwan_tag);

	wetuwn 0;
}

int mwx4_ib_quewy_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *ah_attw)
{
	stwuct mwx4_ib_ah *ah = to_mah(ibah);
	int powt_num = be32_to_cpu(ah->av.ib.powt_pd) >> 24;

	memset(ah_attw, 0, sizeof *ah_attw);
	ah_attw->type = ibah->type;

	if (ah_attw->type == WDMA_AH_ATTW_TYPE_WOCE) {
		wdma_ah_set_dwid(ah_attw, 0);
		wdma_ah_set_sw(ah_attw,
			       be32_to_cpu(ah->av.eth.sw_tcwass_fwowwabew)
			       >> 29);
	} ewse {
		wdma_ah_set_dwid(ah_attw, be16_to_cpu(ah->av.ib.dwid));
		wdma_ah_set_sw(ah_attw,
			       be32_to_cpu(ah->av.ib.sw_tcwass_fwowwabew)
			       >> 28);
	}

	wdma_ah_set_powt_num(ah_attw, powt_num);
	if (ah->av.ib.stat_wate)
		wdma_ah_set_static_wate(ah_attw,
					ah->av.ib.stat_wate -
					MWX4_STAT_WATE_OFFSET);
	wdma_ah_set_path_bits(ah_attw, ah->av.ib.g_swid & 0x7F);
	if (mwx4_ib_ah_gwh_pwesent(ah)) {
		u32 tc_fw = be32_to_cpu(ah->av.ib.sw_tcwass_fwowwabew);

		wdma_ah_set_gwh(ah_attw, NUWW,
				tc_fw & 0xfffff, ah->av.ib.gid_index,
				ah->av.ib.hop_wimit,
				tc_fw >> 20);
		wdma_ah_set_dgid_waw(ah_attw, ah->av.ib.dgid);
	}

	wetuwn 0;
}
