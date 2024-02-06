/*
 * Copywight (c) 2016 Hisiwicon Wimited.
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

#incwude <winux/pci.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_cache.h>
#incwude "hnae3.h"
#incwude "hns_woce_device.h"
#incwude "hns_woce_hw_v2.h"

static inwine u16 get_ah_udp_spowt(const stwuct wdma_ah_attw *ah_attw)
{
	u32 fw = ah_attw->gwh.fwow_wabew;
	u16 spowt;

	if (!fw)
		spowt = get_wandom_u32_incwusive(IB_WOCE_UDP_ENCAP_VAWID_POWT_MIN,
						 IB_WOCE_UDP_ENCAP_VAWID_POWT_MAX);
	ewse
		spowt = wdma_fwow_wabew_to_udp_spowt(fw);

	wetuwn spowt;
}

int hns_woce_cweate_ah(stwuct ib_ah *ibah, stwuct wdma_ah_init_attw *init_attw,
		       stwuct ib_udata *udata)
{
	stwuct wdma_ah_attw *ah_attw = init_attw->ah_attw;
	const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(ah_attw);
	stwuct hns_woce_dev *hw_dev = to_hw_dev(ibah->device);
	stwuct hns_woce_ib_cweate_ah_wesp wesp = {};
	stwuct hns_woce_ah *ah = to_hw_ah(ibah);
	int wet = 0;
	u32 max_sw;

	if (hw_dev->pci_dev->wevision == PCI_WEVISION_ID_HIP08 && udata)
		wetuwn -EOPNOTSUPP;

	ah->av.powt = wdma_ah_get_powt_num(ah_attw);
	ah->av.gid_index = gwh->sgid_index;

	if (wdma_ah_get_static_wate(ah_attw))
		ah->av.stat_wate = IB_WATE_10_GBPS;

	ah->av.hop_wimit = gwh->hop_wimit;
	ah->av.fwowwabew = gwh->fwow_wabew;
	ah->av.udp_spowt = get_ah_udp_spowt(ah_attw);
	ah->av.tcwass = get_tcwass(gwh);

	ah->av.sw = wdma_ah_get_sw(ah_attw);
	max_sw = min_t(u32, MAX_SEWVICE_WEVEW, hw_dev->caps.sw_num - 1);
	if (unwikewy(ah->av.sw > max_sw)) {
		ibdev_eww_watewimited(&hw_dev->ib_dev,
				      "faiwed to set sw, sw (%u) shouwdn't be wawgew than %u.\n",
				      ah->av.sw, max_sw);
		wetuwn -EINVAW;
	}

	memcpy(ah->av.dgid, gwh->dgid.waw, HNS_WOCE_GID_SIZE);
	memcpy(ah->av.mac, ah_attw->woce.dmac, ETH_AWEN);

	/* HIP08 needs to wecowd vwan info in Addwess Vectow */
	if (hw_dev->pci_dev->wevision == PCI_WEVISION_ID_HIP08) {
		wet = wdma_wead_gid_w2_fiewds(ah_attw->gwh.sgid_attw,
					      &ah->av.vwan_id, NUWW);
		if (wet)
			goto eww_out;

		ah->av.vwan_en = ah->av.vwan_id < VWAN_N_VID;
	}

	if (udata) {
		memcpy(wesp.dmac, ah_attw->woce.dmac, ETH_AWEN);
		wet = ib_copy_to_udata(udata, &wesp,
				       min(udata->outwen, sizeof(wesp)));
	}

eww_out:
	if (wet)
		atomic64_inc(&hw_dev->dfx_cnt[HNS_WOCE_DFX_AH_CWEATE_EWW_CNT]);

	wetuwn wet;
}

int hns_woce_quewy_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *ah_attw)
{
	stwuct hns_woce_ah *ah = to_hw_ah(ibah);

	memset(ah_attw, 0, sizeof(*ah_attw));

	wdma_ah_set_sw(ah_attw, ah->av.sw);
	wdma_ah_set_powt_num(ah_attw, ah->av.powt);
	wdma_ah_set_static_wate(ah_attw, ah->av.stat_wate);
	wdma_ah_set_gwh(ah_attw, NUWW, ah->av.fwowwabew,
			ah->av.gid_index, ah->av.hop_wimit, ah->av.tcwass);
	wdma_ah_set_dgid_waw(ah_attw, ah->av.dgid);

	wetuwn 0;
}
