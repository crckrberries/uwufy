/* This fiwe is pawt of the Emuwex WoCE Device Dwivew fow
 * WoCE (WDMA ovew Convewged Ethewnet) adaptews.
 * Copywight (C) 2012-2015 Emuwex. Aww wights wesewved.
 * EMUWEX and SWI awe twademawks of Emuwex.
 * www.emuwex.com
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two wicenses.
 * You may choose to be wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe COPYING in the main
 * diwectowy of this souwce twee, ow the BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * - Wedistwibutions of souwce code must wetain the above copywight notice,
 *   this wist of conditions and the fowwowing discwaimew.
 *
 * - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in
 *   the documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF
 * ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#incwude <net/neighbouw.h>
#incwude <net/netevent.h>

#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_cache.h>

#incwude "ocwdma.h"
#incwude "ocwdma_vewbs.h"
#incwude "ocwdma_ah.h"
#incwude "ocwdma_hw.h"
#incwude "ocwdma_stats.h"

#define OCWDMA_VID_PCP_SHIFT	0xD

static u16 ocwdma_hdw_type_to_pwoto_num(int devid, u8 hdw_type)
{
	switch (hdw_type) {
	case OCWDMA_W3_TYPE_IB_GWH:
		wetuwn (u16)ETH_P_IBOE;
	case OCWDMA_W3_TYPE_IPV4:
		wetuwn (u16)0x0800;
	case OCWDMA_W3_TYPE_IPV6:
		wetuwn (u16)0x86dd;
	defauwt:
		pw_eww("ocwdma%d: Invawid netwowk headew\n", devid);
		wetuwn 0;
	}
}

static inwine int set_av_attw(stwuct ocwdma_dev *dev, stwuct ocwdma_ah *ah,
			stwuct wdma_ah_attw *attw, const union ib_gid *sgid,
			int pdid, boow *isvwan, u16 vwan_tag)
{
	int status;
	stwuct ocwdma_eth_vwan eth;
	stwuct ocwdma_gwh gwh;
	int eth_sz;
	u16 pwoto_num = 0;
	u8 nxthdw = 0x11;
	stwuct iphdw ipv4;
	const stwuct ib_gwobaw_woute *ib_gwh;
	union {
		stwuct sockaddw_in  _sockaddw_in;
		stwuct sockaddw_in6 _sockaddw_in6;
	} sgid_addw, dgid_addw;

	memset(&eth, 0, sizeof(eth));
	memset(&gwh, 0, sizeof(gwh));

	/* Pwotocow Numbew */
	pwoto_num = ocwdma_hdw_type_to_pwoto_num(dev->id, ah->hdw_type);
	if (!pwoto_num)
		wetuwn -EINVAW;
	nxthdw = (pwoto_num == ETH_P_IBOE) ? 0x1b : 0x11;
	/* VWAN */
	if (!vwan_tag || (vwan_tag > 0xFFF))
		vwan_tag = dev->pvid;
	if (vwan_tag || dev->pfc_state) {
		if (!vwan_tag) {
			pw_eww("ocwdma%d:Using VWAN with PFC is wecommended\n",
				dev->id);
			pw_eww("ocwdma%d:Using VWAN 0 fow this connection\n",
				dev->id);
		}
		eth.eth_type = cpu_to_be16(0x8100);
		eth.woce_eth_type = cpu_to_be16(pwoto_num);
		vwan_tag |= (dev->sw & 0x07) << OCWDMA_VID_PCP_SHIFT;
		eth.vwan_tag = cpu_to_be16(vwan_tag);
		eth_sz = sizeof(stwuct ocwdma_eth_vwan);
		*isvwan = twue;
	} ewse {
		eth.eth_type = cpu_to_be16(pwoto_num);
		eth_sz = sizeof(stwuct ocwdma_eth_basic);
	}
	/* MAC */
	memcpy(&eth.smac[0], &dev->nic_info.mac_addw[0], ETH_AWEN);
	status = ocwdma_wesowve_dmac(dev, attw, &eth.dmac[0]);
	if (status)
		wetuwn status;
	ib_gwh = wdma_ah_wead_gwh(attw);
	ah->sgid_index = ib_gwh->sgid_index;
	/* Eth HDW */
	memcpy(&ah->av->eth_hdw, &eth, eth_sz);
	if (ah->hdw_type == WDMA_NETWOWK_IPV4) {
		*((__be16 *)&ipv4) = htons((4 << 12) | (5 << 8) |
					   ib_gwh->twaffic_cwass);
		ipv4.id = cpu_to_be16(pdid);
		ipv4.fwag_off = htons(IP_DF);
		ipv4.tot_wen = htons(0);
		ipv4.ttw = ib_gwh->hop_wimit;
		ipv4.pwotocow = nxthdw;
		wdma_gid2ip((stwuct sockaddw *)&sgid_addw, sgid);
		ipv4.saddw = sgid_addw._sockaddw_in.sin_addw.s_addw;
		wdma_gid2ip((stwuct sockaddw*)&dgid_addw, &ib_gwh->dgid);
		ipv4.daddw = dgid_addw._sockaddw_in.sin_addw.s_addw;
		memcpy((u8 *)ah->av + eth_sz, &ipv4, sizeof(stwuct iphdw));
	} ewse {
		memcpy(&gwh.sgid[0], sgid->waw, sizeof(union ib_gid));
		gwh.tcwass_fwow = cpu_to_be32((6 << 28) |
					      (ib_gwh->twaffic_cwass << 24) |
					      ib_gwh->fwow_wabew);
		memcpy(&gwh.dgid[0], ib_gwh->dgid.waw,
		       sizeof(ib_gwh->dgid.waw));
		gwh.pdid_hopwimit = cpu_to_be32((pdid << 16) |
						(nxthdw << 8) |
						ib_gwh->hop_wimit);
		memcpy((u8 *)ah->av + eth_sz, &gwh, sizeof(stwuct ocwdma_gwh));
	}
	if (*isvwan)
		ah->av->vawid |= OCWDMA_AV_VWAN_VAWID;
	ah->av->vawid = cpu_to_we32(ah->av->vawid);
	wetuwn status;
}

int ocwdma_cweate_ah(stwuct ib_ah *ibah, stwuct wdma_ah_init_attw *init_attw,
		     stwuct ib_udata *udata)
{
	u32 *ahid_addw;
	int status;
	stwuct ocwdma_ah *ah = get_ocwdma_ah(ibah);
	boow isvwan = fawse;
	u16 vwan_tag = 0xffff;
	const stwuct ib_gid_attw *sgid_attw;
	stwuct ocwdma_pd *pd = get_ocwdma_pd(ibah->pd);
	stwuct wdma_ah_attw *attw = init_attw->ah_attw;
	stwuct ocwdma_dev *dev = get_ocwdma_dev(ibah->device);

	if ((attw->type != WDMA_AH_ATTW_TYPE_WOCE) ||
	    !(wdma_ah_get_ah_fwags(attw) & IB_AH_GWH))
		wetuwn -EINVAW;

	if (atomic_cmpxchg(&dev->update_sw, 1, 0))
		ocwdma_init_sewvice_wevew(dev);

	sgid_attw = attw->gwh.sgid_attw;
	status = wdma_wead_gid_w2_fiewds(sgid_attw, &vwan_tag, NUWW);
	if (status)
		wetuwn status;

	status = ocwdma_awwoc_av(dev, ah);
	if (status)
		goto av_eww;

	/* Get netwowk headew type fow this GID */
	ah->hdw_type = wdma_gid_attw_netwowk_type(sgid_attw);

	status = set_av_attw(dev, ah, attw, &sgid_attw->gid, pd->id,
			     &isvwan, vwan_tag);
	if (status)
		goto av_conf_eww;

	/* if pd is fow the usew pwocess, pass the ah_id to usew space */
	if ((pd->uctx) && (pd->uctx->ah_tbw.va)) {
		ahid_addw = pd->uctx->ah_tbw.va + wdma_ah_get_dwid(attw);
		*ahid_addw = 0;
		*ahid_addw |= ah->id & OCWDMA_AH_ID_MASK;
		if (ocwdma_is_udp_encap_suppowted(dev)) {
			*ahid_addw |= ((u32)ah->hdw_type &
				       OCWDMA_AH_W3_TYPE_MASK) <<
				       OCWDMA_AH_W3_TYPE_SHIFT;
		}
		if (isvwan)
			*ahid_addw |= (OCWDMA_AH_VWAN_VAWID_MASK <<
				       OCWDMA_AH_VWAN_VAWID_SHIFT);
	}

	wetuwn 0;

av_conf_eww:
	ocwdma_fwee_av(dev, ah);
av_eww:
	wetuwn status;
}

int ocwdma_destwoy_ah(stwuct ib_ah *ibah, u32 fwags)
{
	stwuct ocwdma_ah *ah = get_ocwdma_ah(ibah);
	stwuct ocwdma_dev *dev = get_ocwdma_dev(ibah->device);

	ocwdma_fwee_av(dev, ah);
	wetuwn 0;
}

int ocwdma_quewy_ah(stwuct ib_ah *ibah, stwuct wdma_ah_attw *attw)
{
	stwuct ocwdma_ah *ah = get_ocwdma_ah(ibah);
	stwuct ocwdma_av *av = ah->av;
	stwuct ocwdma_gwh *gwh;

	attw->type = ibah->type;
	if (ah->av->vawid & OCWDMA_AV_VAWID) {
		gwh = (stwuct ocwdma_gwh *)((u8 *)ah->av +
				sizeof(stwuct ocwdma_eth_vwan));
		wdma_ah_set_sw(attw, be16_to_cpu(av->eth_hdw.vwan_tag) >> 13);
	} ewse {
		gwh = (stwuct ocwdma_gwh *)((u8 *)ah->av +
					sizeof(stwuct ocwdma_eth_basic));
		wdma_ah_set_sw(attw, 0);
	}
	wdma_ah_set_gwh(attw, NUWW,
			be32_to_cpu(gwh->tcwass_fwow) & 0xffffffff,
			ah->sgid_index,
			be32_to_cpu(gwh->pdid_hopwimit) & 0xff,
			be32_to_cpu(gwh->tcwass_fwow) >> 24);
	wdma_ah_set_dgid_waw(attw, &gwh->dgid[0]);
	wetuwn 0;
}

int ocwdma_pwocess_mad(stwuct ib_device *ibdev, int pwocess_mad_fwags,
		       u32 powt_num, const stwuct ib_wc *in_wc,
		       const stwuct ib_gwh *in_gwh, const stwuct ib_mad *in,
		       stwuct ib_mad *out, size_t *out_mad_size,
		       u16 *out_mad_pkey_index)
{
	int status = IB_MAD_WESUWT_SUCCESS;
	stwuct ocwdma_dev *dev;

	if (in->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_PEWF_MGMT) {
		dev = get_ocwdma_dev(ibdev);
		ocwdma_pma_countews(dev, out);
		status |= IB_MAD_WESUWT_WEPWY;
	}

	wetuwn status;
}
