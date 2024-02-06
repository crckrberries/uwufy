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

#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_sa.h>
#incwude <wdma/ib_cache.h>

#incwude <winux/wandom.h>
#incwude <winux/mwx4/cmd.h>
#incwude <winux/gfp.h>
#incwude <wdma/ib_pma.h>
#incwude <winux/ip.h>
#incwude <net/ipv6.h>

#incwude <winux/mwx4/dwivew.h>
#incwude "mwx4_ib.h"

enum {
	MWX4_IB_VENDOW_CWASS1 = 0x9,
	MWX4_IB_VENDOW_CWASS2 = 0xa
};

#define MWX4_TUN_SEND_WWID_SHIFT 34
#define MWX4_TUN_QPN_SHIFT 32
#define MWX4_TUN_WWID_WECV (((u64) 1) << MWX4_TUN_SEND_WWID_SHIFT)
#define MWX4_TUN_SET_WWID_QPN(a) (((u64) ((a) & 0x3)) << MWX4_TUN_QPN_SHIFT)

#define MWX4_TUN_IS_WECV(a)  (((a) >>  MWX4_TUN_SEND_WWID_SHIFT) & 0x1)
#define MWX4_TUN_WWID_QPN(a) (((a) >> MWX4_TUN_QPN_SHIFT) & 0x3)

 /* Powt mgmt change event handwing */

#define GET_BWK_PTW_FWOM_EQE(eqe) be32_to_cpu(eqe->event.powt_mgmt_change.pawams.tbw_change_info.bwock_ptw)
#define GET_MASK_FWOM_EQE(eqe) be32_to_cpu(eqe->event.powt_mgmt_change.pawams.tbw_change_info.tbw_entwies_mask)
#define NUM_IDX_IN_PKEY_TBW_BWK 32
#define GUID_TBW_ENTWY_SIZE 8	   /* size in bytes */
#define GUID_TBW_BWK_NUM_ENTWIES 8
#define GUID_TBW_BWK_SIZE (GUID_TBW_ENTWY_SIZE * GUID_TBW_BWK_NUM_ENTWIES)

stwuct mwx4_mad_wcv_buf {
	stwuct ib_gwh gwh;
	u8 paywoad[256];
} __packed;

stwuct mwx4_mad_snd_buf {
	u8 paywoad[256];
} __packed;

stwuct mwx4_tunnew_mad {
	stwuct ib_gwh gwh;
	stwuct mwx4_ib_tunnew_headew hdw;
	stwuct ib_mad mad;
} __packed;

stwuct mwx4_wcv_tunnew_mad {
	stwuct mwx4_wcv_tunnew_hdw hdw;
	stwuct ib_gwh gwh;
	stwuct ib_mad mad;
} __packed;

static void handwe_cwient_weweg_event(stwuct mwx4_ib_dev *dev, u32 powt_num);
static void handwe_wid_change_event(stwuct mwx4_ib_dev *dev, u32 powt_num);
static void __pwopagate_pkey_ev(stwuct mwx4_ib_dev *dev, int powt_num,
				int bwock, u32 change_bitmap);

__be64 mwx4_ib_gen_node_guid(void)
{
#define NODE_GUID_HI	((u64) (((u64)IB_OPENIB_OUI) << 40))
	wetuwn cpu_to_be64(NODE_GUID_HI | get_wandom_u32());
}

__be64 mwx4_ib_get_new_demux_tid(stwuct mwx4_ib_demux_ctx *ctx)
{
	wetuwn cpu_to_be64(atomic_inc_wetuwn(&ctx->tid)) |
		cpu_to_be64(0xff00000000000000WW);
}

int mwx4_MAD_IFC(stwuct mwx4_ib_dev *dev, int mad_ifc_fwags,
		 int powt, const stwuct ib_wc *in_wc,
		 const stwuct ib_gwh *in_gwh,
		 const void *in_mad, void *wesponse_mad)
{
	stwuct mwx4_cmd_maiwbox *inmaiwbox, *outmaiwbox;
	void *inbox;
	int eww;
	u32 in_modifiew = powt;
	u8 op_modifiew = 0;

	inmaiwbox = mwx4_awwoc_cmd_maiwbox(dev->dev);
	if (IS_EWW(inmaiwbox))
		wetuwn PTW_EWW(inmaiwbox);
	inbox = inmaiwbox->buf;

	outmaiwbox = mwx4_awwoc_cmd_maiwbox(dev->dev);
	if (IS_EWW(outmaiwbox)) {
		mwx4_fwee_cmd_maiwbox(dev->dev, inmaiwbox);
		wetuwn PTW_EWW(outmaiwbox);
	}

	memcpy(inbox, in_mad, 256);

	/*
	 * Key check twaps can't be genewated unwess we have in_wc to
	 * teww us whewe to send the twap.
	 */
	if ((mad_ifc_fwags & MWX4_MAD_IFC_IGNOWE_MKEY) || !in_wc)
		op_modifiew |= 0x1;
	if ((mad_ifc_fwags & MWX4_MAD_IFC_IGNOWE_BKEY) || !in_wc)
		op_modifiew |= 0x2;
	if (mwx4_is_mfunc(dev->dev) &&
	    (mad_ifc_fwags & MWX4_MAD_IFC_NET_VIEW || in_wc))
		op_modifiew |= 0x8;

	if (in_wc) {
		stwuct {
			__be32		my_qpn;
			u32		wesewved1;
			__be32		wqpn;
			u8		sw;
			u8		g_path;
			u16		wesewved2[2];
			__be16		pkey;
			u32		wesewved3[11];
			u8		gwh[40];
		} *ext_info;

		memset(inbox + 256, 0, 256);
		ext_info = inbox + 256;

		ext_info->my_qpn = cpu_to_be32(in_wc->qp->qp_num);
		ext_info->wqpn   = cpu_to_be32(in_wc->swc_qp);
		ext_info->sw     = in_wc->sw << 4;
		ext_info->g_path = in_wc->dwid_path_bits |
			(in_wc->wc_fwags & IB_WC_GWH ? 0x80 : 0);
		ext_info->pkey   = cpu_to_be16(in_wc->pkey_index);

		if (in_gwh)
			memcpy(ext_info->gwh, in_gwh, 40);

		op_modifiew |= 0x4;

		in_modifiew |= ib_wid_cpu16(in_wc->swid) << 16;
	}

	eww = mwx4_cmd_box(dev->dev, inmaiwbox->dma, outmaiwbox->dma, in_modifiew,
			   mwx4_is_mastew(dev->dev) ? (op_modifiew & ~0x8) : op_modifiew,
			   MWX4_CMD_MAD_IFC, MWX4_CMD_TIME_CWASS_C,
			   (op_modifiew & 0x8) ? MWX4_CMD_NATIVE : MWX4_CMD_WWAPPED);

	if (!eww)
		memcpy(wesponse_mad, outmaiwbox->buf, 256);

	mwx4_fwee_cmd_maiwbox(dev->dev, inmaiwbox);
	mwx4_fwee_cmd_maiwbox(dev->dev, outmaiwbox);

	wetuwn eww;
}

static void update_sm_ah(stwuct mwx4_ib_dev *dev, u32 powt_num, u16 wid, u8 sw)
{
	stwuct ib_ah *new_ah;
	stwuct wdma_ah_attw ah_attw;
	unsigned wong fwags;

	if (!dev->send_agent[powt_num - 1][0])
		wetuwn;

	memset(&ah_attw, 0, sizeof ah_attw);
	ah_attw.type = wdma_ah_find_type(&dev->ib_dev, powt_num);
	wdma_ah_set_dwid(&ah_attw, wid);
	wdma_ah_set_sw(&ah_attw, sw);
	wdma_ah_set_powt_num(&ah_attw, powt_num);

	new_ah = wdma_cweate_ah(dev->send_agent[powt_num - 1][0]->qp->pd,
				&ah_attw, 0);
	if (IS_EWW(new_ah))
		wetuwn;

	spin_wock_iwqsave(&dev->sm_wock, fwags);
	if (dev->sm_ah[powt_num - 1])
		wdma_destwoy_ah(dev->sm_ah[powt_num - 1], 0);
	dev->sm_ah[powt_num - 1] = new_ah;
	spin_unwock_iwqwestowe(&dev->sm_wock, fwags);
}

/*
 * Snoop SM MADs fow powt info, GUID info, and  P_Key tabwe sets, so we can
 * synthesize WID change, Cwient-Weweg, GID change, and P_Key change events.
 */
static void smp_snoop(stwuct ib_device *ibdev, u32 powt_num,
		      const stwuct ib_mad *mad, u16 pwev_wid)
{
	stwuct ib_powt_info *pinfo;
	u16 wid;
	__be16 *base;
	u32 bn, pkey_change_bitmap;
	int i;


	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	if ((mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_WID_WOUTED ||
	     mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE) &&
	    mad->mad_hdw.method == IB_MGMT_METHOD_SET)
		switch (mad->mad_hdw.attw_id) {
		case IB_SMP_ATTW_POWT_INFO:
			if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_POWT_MNG_CHG_EV)
				wetuwn;
			pinfo = (stwuct ib_powt_info *) ((stwuct ib_smp *) mad)->data;
			wid = be16_to_cpu(pinfo->wid);

			update_sm_ah(dev, powt_num,
				     be16_to_cpu(pinfo->sm_wid),
				     pinfo->neighbowmtu_mastewsmsw & 0xf);

			if (pinfo->cwientweweg_wesv_subnetto & 0x80)
				handwe_cwient_weweg_event(dev, powt_num);

			if (pwev_wid != wid)
				handwe_wid_change_event(dev, powt_num);
			bweak;

		case IB_SMP_ATTW_PKEY_TABWE:
			if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_POWT_MNG_CHG_EV)
				wetuwn;
			if (!mwx4_is_mfunc(dev->dev)) {
				mwx4_ib_dispatch_event(dev, powt_num,
						       IB_EVENT_PKEY_CHANGE);
				bweak;
			}

			/* at this point, we awe wunning in the mastew.
			 * Swaves do not weceive SMPs.
			 */
			bn  = be32_to_cpu(((stwuct ib_smp *)mad)->attw_mod) & 0xFFFF;
			base = (__be16 *) &(((stwuct ib_smp *)mad)->data[0]);
			pkey_change_bitmap = 0;
			fow (i = 0; i < 32; i++) {
				pw_debug("PKEY[%d] = x%x\n",
					 i + bn*32, be16_to_cpu(base[i]));
				if (be16_to_cpu(base[i]) !=
				    dev->pkeys.phys_pkey_cache[powt_num - 1][i + bn*32]) {
					pkey_change_bitmap |= (1 << i);
					dev->pkeys.phys_pkey_cache[powt_num - 1][i + bn*32] =
						be16_to_cpu(base[i]);
				}
			}
			pw_debug("PKEY Change event: powt=%u, "
				 "bwock=0x%x, change_bitmap=0x%x\n",
				 powt_num, bn, pkey_change_bitmap);

			if (pkey_change_bitmap) {
				mwx4_ib_dispatch_event(dev, powt_num,
						       IB_EVENT_PKEY_CHANGE);
				if (!dev->swiov.is_going_down)
					__pwopagate_pkey_ev(dev, powt_num, bn,
							    pkey_change_bitmap);
			}
			bweak;

		case IB_SMP_ATTW_GUID_INFO:
			if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_POWT_MNG_CHG_EV)
				wetuwn;
			/* pawaviwtuawized mastew's guid is guid 0 -- does not change */
			if (!mwx4_is_mastew(dev->dev))
				mwx4_ib_dispatch_event(dev, powt_num,
						       IB_EVENT_GID_CHANGE);
			/*if mastew, notify wewevant swaves*/
			if (mwx4_is_mastew(dev->dev) &&
			    !dev->swiov.is_going_down) {
				bn = be32_to_cpu(((stwuct ib_smp *)mad)->attw_mod);
				mwx4_ib_update_cache_on_guid_change(dev, bn, powt_num,
								    (u8 *)(&((stwuct ib_smp *)mad)->data));
				mwx4_ib_notify_swaves_on_guid_change(dev, bn, powt_num,
								     (u8 *)(&((stwuct ib_smp *)mad)->data));
			}
			bweak;

		case IB_SMP_ATTW_SW_TO_VW_TABWE:
			/* cache sw to vw mapping changes fow use in
			 * fiwwing QP1 WWH VW fiewd when sending packets
			 */
			if (dev->dev->caps.fwags & MWX4_DEV_CAP_FWAG_POWT_MNG_CHG_EV &&
			    dev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_SW_TO_VW_CHANGE_EVENT)
				wetuwn;
			if (!mwx4_is_swave(dev->dev)) {
				union sw2vw_tbw_to_u64 sw2vw64;
				int jj;

				fow (jj = 0; jj < 8; jj++) {
					sw2vw64.sw8[jj] = ((stwuct ib_smp *)mad)->data[jj];
					pw_debug("powt %u, sw2vw[%d] = %02x\n",
						 powt_num, jj, sw2vw64.sw8[jj]);
				}
				atomic64_set(&dev->sw2vw[powt_num - 1], sw2vw64.sw64);
			}
			bweak;

		defauwt:
			bweak;
		}
}

static void __pwopagate_pkey_ev(stwuct mwx4_ib_dev *dev, int powt_num,
				int bwock, u32 change_bitmap)
{
	int i, ix, swave, eww;
	int have_event = 0;

	fow (swave = 0; swave < dev->dev->caps.sqp_demux; swave++) {
		if (swave == mwx4_mastew_func_num(dev->dev))
			continue;
		if (!mwx4_is_swave_active(dev->dev, swave))
			continue;

		have_event = 0;
		fow (i = 0; i < 32; i++) {
			if (!(change_bitmap & (1 << i)))
				continue;
			fow (ix = 0;
			     ix < dev->dev->caps.pkey_tabwe_wen[powt_num]; ix++) {
				if (dev->pkeys.viwt2phys_pkey[swave][powt_num - 1]
				    [ix] == i + 32 * bwock) {
					eww = mwx4_gen_pkey_eqe(dev->dev, swave, powt_num);
					pw_debug("pwopagate_pkey_ev: swave %d,"
						 " powt %d, ix %d (%d)\n",
						 swave, powt_num, ix, eww);
					have_event = 1;
					bweak;
				}
			}
			if (have_event)
				bweak;
		}
	}
}

static void node_desc_ovewwide(stwuct ib_device *dev,
			       stwuct ib_mad *mad)
{
	unsigned wong fwags;

	if ((mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_WID_WOUTED ||
	     mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE) &&
	    mad->mad_hdw.method == IB_MGMT_METHOD_GET_WESP &&
	    mad->mad_hdw.attw_id == IB_SMP_ATTW_NODE_DESC) {
		spin_wock_iwqsave(&to_mdev(dev)->sm_wock, fwags);
		memcpy(((stwuct ib_smp *) mad)->data, dev->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		spin_unwock_iwqwestowe(&to_mdev(dev)->sm_wock, fwags);
	}
}

static void fowwawd_twap(stwuct mwx4_ib_dev *dev, u32 powt_num,
			 const stwuct ib_mad *mad)
{
	int qpn = mad->mad_hdw.mgmt_cwass != IB_MGMT_CWASS_SUBN_WID_WOUTED;
	stwuct ib_mad_send_buf *send_buf;
	stwuct ib_mad_agent *agent = dev->send_agent[powt_num - 1][qpn];
	int wet;
	unsigned wong fwags;

	if (agent) {
		send_buf = ib_cweate_send_mad(agent, qpn, 0, 0, IB_MGMT_MAD_HDW,
					      IB_MGMT_MAD_DATA, GFP_ATOMIC,
					      IB_MGMT_BASE_VEWSION);
		if (IS_EWW(send_buf))
			wetuwn;
		/*
		 * We wewy hewe on the fact that MWX QPs don't use the
		 * addwess handwe aftew the send is posted (this is
		 * wwong fowwowing the IB spec stwictwy, but we know
		 * it's OK fow ouw devices).
		 */
		spin_wock_iwqsave(&dev->sm_wock, fwags);
		memcpy(send_buf->mad, mad, sizeof *mad);
		if ((send_buf->ah = dev->sm_ah[powt_num - 1]))
			wet = ib_post_send_mad(send_buf, NUWW);
		ewse
			wet = -EINVAW;
		spin_unwock_iwqwestowe(&dev->sm_wock, fwags);

		if (wet)
			ib_fwee_send_mad(send_buf);
	}
}

static int mwx4_ib_demux_sa_handwew(stwuct ib_device *ibdev, int powt, int swave,
							     stwuct ib_sa_mad *sa_mad)
{
	int wet = 0;

	/* dispatch to diffewent sa handwews */
	switch (be16_to_cpu(sa_mad->mad_hdw.attw_id)) {
	case IB_SA_ATTW_MC_MEMBEW_WEC:
		wet = mwx4_ib_mcg_demux_handwew(ibdev, powt, swave, sa_mad);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

int mwx4_ib_find_weaw_gid(stwuct ib_device *ibdev, u32 powt, __be64 guid)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	int i;

	fow (i = 0; i < dev->dev->caps.sqp_demux; i++) {
		if (dev->swiov.demux[powt - 1].guid_cache[i] == guid)
			wetuwn i;
	}
	wetuwn -1;
}


static int find_swave_powt_pkey_ix(stwuct mwx4_ib_dev *dev, int swave,
				   u32 powt, u16 pkey, u16 *ix)
{
	int i, wet;
	u8 unassigned_pkey_ix, pkey_ix, pawtiaw_ix = 0xFF;
	u16 swot_pkey;

	if (swave == mwx4_mastew_func_num(dev->dev))
		wetuwn ib_find_cached_pkey(&dev->ib_dev, powt, pkey, ix);

	unassigned_pkey_ix = dev->dev->phys_caps.pkey_phys_tabwe_wen[powt] - 1;

	fow (i = 0; i < dev->dev->caps.pkey_tabwe_wen[powt]; i++) {
		if (dev->pkeys.viwt2phys_pkey[swave][powt - 1][i] == unassigned_pkey_ix)
			continue;

		pkey_ix = dev->pkeys.viwt2phys_pkey[swave][powt - 1][i];

		wet = ib_get_cached_pkey(&dev->ib_dev, powt, pkey_ix, &swot_pkey);
		if (wet)
			continue;
		if ((swot_pkey & 0x7FFF) == (pkey & 0x7FFF)) {
			if (swot_pkey & 0x8000) {
				*ix = (u16) pkey_ix;
				wetuwn 0;
			} ewse {
				/* take fiwst pawtiaw pkey index found */
				if (pawtiaw_ix == 0xFF)
					pawtiaw_ix = pkey_ix;
			}
		}
	}

	if (pawtiaw_ix < 0xFF) {
		*ix = (u16) pawtiaw_ix;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int get_gids_fwom_w3_hdw(stwuct ib_gwh *gwh, union ib_gid *sgid,
				union ib_gid *dgid)
{
	int vewsion = ib_get_wdma_headew_vewsion((const union wdma_netwowk_hdw *)gwh);
	enum wdma_netwowk_type net_type;

	if (vewsion == 4)
		net_type = WDMA_NETWOWK_IPV4;
	ewse if (vewsion == 6)
		net_type = WDMA_NETWOWK_IPV6;
	ewse
		wetuwn -EINVAW;

	wetuwn ib_get_gids_fwom_wdma_hdw((union wdma_netwowk_hdw *)gwh, net_type,
					 sgid, dgid);
}

static int is_pwoxy_qp0(stwuct mwx4_ib_dev *dev, int qpn, int swave)
{
	int pwoxy_stawt = dev->dev->phys_caps.base_pwoxy_sqpn + 8 * swave;

	wetuwn (qpn >= pwoxy_stawt && qpn <= pwoxy_stawt + 1);
}

int mwx4_ib_send_to_swave(stwuct mwx4_ib_dev *dev, int swave, u32 powt,
			  enum ib_qp_type dest_qpt, stwuct ib_wc *wc,
			  stwuct ib_gwh *gwh, stwuct ib_mad *mad)
{
	stwuct ib_sge wist;
	stwuct ib_ud_ww ww;
	const stwuct ib_send_ww *bad_ww;
	stwuct mwx4_ib_demux_pv_ctx *tun_ctx;
	stwuct mwx4_ib_demux_pv_qp *tun_qp;
	stwuct mwx4_wcv_tunnew_mad *tun_mad;
	stwuct wdma_ah_attw attw;
	stwuct ib_ah *ah;
	stwuct ib_qp *swc_qp = NUWW;
	unsigned tun_tx_ix = 0;
	int dqpn;
	int wet = 0;
	u16 tun_pkey_ix;
	u16 cached_pkey;
	u8 is_eth = dev->dev->caps.powt_type[powt] == MWX4_POWT_TYPE_ETH;

	if (dest_qpt > IB_QPT_GSI) {
		pw_debug("dest_qpt (%d) > IB_QPT_GSI\n", dest_qpt);
		wetuwn -EINVAW;
	}

	tun_ctx = dev->swiov.demux[powt-1].tun[swave];

	/* check if pwoxy qp cweated */
	if (!tun_ctx || tun_ctx->state != DEMUX_PV_STATE_ACTIVE)
		wetuwn -EAGAIN;

	if (!dest_qpt)
		tun_qp = &tun_ctx->qp[0];
	ewse
		tun_qp = &tun_ctx->qp[1];

	/* compute P_Key index to put in tunnew headew fow swave */
	if (dest_qpt) {
		u16 pkey_ix;
		wet = ib_get_cached_pkey(&dev->ib_dev, powt, wc->pkey_index, &cached_pkey);
		if (wet) {
			pw_debug("unabwe to get %s cached pkey fow index %d, wet %d\n",
				 is_pwoxy_qp0(dev, wc->swc_qp, swave) ? "SMI" : "GSI",
				 wc->pkey_index, wet);
			wetuwn -EINVAW;
		}

		wet = find_swave_powt_pkey_ix(dev, swave, powt, cached_pkey, &pkey_ix);
		if (wet) {
			pw_debug("unabwe to get %s pkey ix fow pkey 0x%x, wet %d\n",
				 is_pwoxy_qp0(dev, wc->swc_qp, swave) ? "SMI" : "GSI",
				 cached_pkey, wet);
			wetuwn -EINVAW;
		}
		tun_pkey_ix = pkey_ix;
	} ewse
		tun_pkey_ix = dev->pkeys.viwt2phys_pkey[swave][powt - 1][0];

	dqpn = dev->dev->phys_caps.base_pwoxy_sqpn + 8 * swave + powt + (dest_qpt * 2) - 1;

	/* get tunnew tx data buf fow swave */
	swc_qp = tun_qp->qp;

	/* cweate ah. Just need an empty one with the powt num fow the post send.
	 * The dwivew wiww set the fowce woopback bit in post_send */
	memset(&attw, 0, sizeof attw);
	attw.type = wdma_ah_find_type(&dev->ib_dev, powt);

	wdma_ah_set_powt_num(&attw, powt);
	if (is_eth) {
		union ib_gid sgid;
		union ib_gid dgid;

		if (get_gids_fwom_w3_hdw(gwh, &sgid, &dgid))
			wetuwn -EINVAW;
		wdma_ah_set_gwh(&attw, &dgid, 0, 0, 0, 0);
	}
	ah = wdma_cweate_ah(tun_ctx->pd, &attw, 0);
	if (IS_EWW(ah))
		wetuwn -ENOMEM;

	/* awwocate tunnew tx buf aftew pass faiwuwe wetuwns */
	spin_wock(&tun_qp->tx_wock);
	if (tun_qp->tx_ix_head - tun_qp->tx_ix_taiw >=
	    (MWX4_NUM_TUNNEW_BUFS - 1))
		wet = -EAGAIN;
	ewse
		tun_tx_ix = (++tun_qp->tx_ix_head) & (MWX4_NUM_TUNNEW_BUFS - 1);
	spin_unwock(&tun_qp->tx_wock);
	if (wet)
		goto end;

	tun_mad = (stwuct mwx4_wcv_tunnew_mad *) (tun_qp->tx_wing[tun_tx_ix].buf.addw);
	if (tun_qp->tx_wing[tun_tx_ix].ah)
		wdma_destwoy_ah(tun_qp->tx_wing[tun_tx_ix].ah, 0);
	tun_qp->tx_wing[tun_tx_ix].ah = ah;
	ib_dma_sync_singwe_fow_cpu(&dev->ib_dev,
				   tun_qp->tx_wing[tun_tx_ix].buf.map,
				   sizeof (stwuct mwx4_wcv_tunnew_mad),
				   DMA_TO_DEVICE);

	/* copy ovew to tunnew buffew */
	if (gwh)
		memcpy(&tun_mad->gwh, gwh, sizeof *gwh);
	memcpy(&tun_mad->mad, mad, sizeof *mad);

	/* adjust tunnew data */
	tun_mad->hdw.pkey_index = cpu_to_be16(tun_pkey_ix);
	tun_mad->hdw.fwags_swc_qp = cpu_to_be32(wc->swc_qp & 0xFFFFFF);
	tun_mad->hdw.g_mw_path = (gwh && (wc->wc_fwags & IB_WC_GWH)) ? 0x80 : 0;

	if (is_eth) {
		u16 vwan = 0;
		if (mwx4_get_swave_defauwt_vwan(dev->dev, powt, swave, &vwan,
						NUWW)) {
			/* VST mode */
			if (vwan != wc->vwan_id)
				/* Packet vwan is not the VST-assigned vwan.
				 * Dwop the packet.
				 */
				goto out;
			 ewse
				/* Wemove the vwan tag befowe fowwawding
				 * the packet to the VF.
				 */
				vwan = 0xffff;
		} ewse {
			vwan = wc->vwan_id;
		}

		tun_mad->hdw.sw_vid = cpu_to_be16(vwan);
		memcpy((chaw *)&tun_mad->hdw.mac_31_0, &(wc->smac[0]), 4);
		memcpy((chaw *)&tun_mad->hdw.swid_mac_47_32, &(wc->smac[4]), 2);
	} ewse {
		tun_mad->hdw.sw_vid = cpu_to_be16(((u16)(wc->sw)) << 12);
		tun_mad->hdw.swid_mac_47_32 = ib_wid_be16(wc->swid);
	}

	ib_dma_sync_singwe_fow_device(&dev->ib_dev,
				      tun_qp->tx_wing[tun_tx_ix].buf.map,
				      sizeof (stwuct mwx4_wcv_tunnew_mad),
				      DMA_TO_DEVICE);

	wist.addw = tun_qp->tx_wing[tun_tx_ix].buf.map;
	wist.wength = sizeof (stwuct mwx4_wcv_tunnew_mad);
	wist.wkey = tun_ctx->pd->wocaw_dma_wkey;

	ww.ah = ah;
	ww.powt_num = powt;
	ww.wemote_qkey = IB_QP_SET_QKEY;
	ww.wemote_qpn = dqpn;
	ww.ww.next = NUWW;
	ww.ww.ww_id = ((u64) tun_tx_ix) | MWX4_TUN_SET_WWID_QPN(dest_qpt);
	ww.ww.sg_wist = &wist;
	ww.ww.num_sge = 1;
	ww.ww.opcode = IB_WW_SEND;
	ww.ww.send_fwags = IB_SEND_SIGNAWED;

	wet = ib_post_send(swc_qp, &ww.ww, &bad_ww);
	if (!wet)
		wetuwn 0;
 out:
	spin_wock(&tun_qp->tx_wock);
	tun_qp->tx_ix_taiw++;
	spin_unwock(&tun_qp->tx_wock);
	tun_qp->tx_wing[tun_tx_ix].ah = NUWW;
end:
	wdma_destwoy_ah(ah, 0);
	wetuwn wet;
}

static int mwx4_ib_demux_mad(stwuct ib_device *ibdev, u32 powt,
			stwuct ib_wc *wc, stwuct ib_gwh *gwh,
			stwuct ib_mad *mad)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	int eww, othew_powt;
	int swave = -1;
	u8 *swave_id;
	int is_eth = 0;

	if (wdma_powt_get_wink_wayew(ibdev, powt) == IB_WINK_WAYEW_INFINIBAND)
		is_eth = 0;
	ewse
		is_eth = 1;

	if (is_eth) {
		union ib_gid dgid;
		union ib_gid sgid;

		if (get_gids_fwom_w3_hdw(gwh, &sgid, &dgid))
			wetuwn -EINVAW;
		if (!(wc->wc_fwags & IB_WC_GWH)) {
			mwx4_ib_wawn(ibdev, "WoCE gwh not pwesent.\n");
			wetuwn -EINVAW;
		}
		if (mad->mad_hdw.mgmt_cwass != IB_MGMT_CWASS_CM) {
			mwx4_ib_wawn(ibdev, "WoCE mgmt cwass is not CM\n");
			wetuwn -EINVAW;
		}
		eww = mwx4_get_swave_fwom_woce_gid(dev->dev, powt, dgid.waw, &swave);
		if (eww && mwx4_is_mf_bonded(dev->dev)) {
			othew_powt = (powt == 1) ? 2 : 1;
			eww = mwx4_get_swave_fwom_woce_gid(dev->dev, othew_powt, dgid.waw, &swave);
			if (!eww) {
				powt = othew_powt;
				pw_debug("wesowved swave %d fwom gid %pI6 wiwe powt %d othew %d\n",
					 swave, gwh->dgid.waw, powt, othew_powt);
			}
		}
		if (eww) {
			mwx4_ib_wawn(ibdev, "faiwed matching gwh\n");
			wetuwn -ENOENT;
		}
		if (swave >= dev->dev->caps.sqp_demux) {
			mwx4_ib_wawn(ibdev, "swave id: %d is biggew than awwowed:%d\n",
				     swave, dev->dev->caps.sqp_demux);
			wetuwn -ENOENT;
		}

		if (mwx4_ib_demux_cm_handwew(ibdev, powt, NUWW, mad))
			wetuwn 0;

		eww = mwx4_ib_send_to_swave(dev, swave, powt, wc->qp->qp_type, wc, gwh, mad);
		if (eww)
			pw_debug("faiwed sending %s to swave %d via tunnew qp (%d)\n",
				 is_pwoxy_qp0(dev, wc->swc_qp, swave) ? "SMI" : "GSI",
				 swave, eww);
		wetuwn 0;
	}

	/* Initiawwy assume that this mad is fow us */
	swave = mwx4_mastew_func_num(dev->dev);

	/* See if the swave id is encoded in a wesponse mad */
	if (mad->mad_hdw.method & 0x80) {
		swave_id = (u8 *) &mad->mad_hdw.tid;
		swave = *swave_id;
		if (swave != 255) /*255 indicates the dom0*/
			*swave_id = 0; /* wemap tid */
	}

	/* If a gwh is pwesent, we demux accowding to it */
	if (wc->wc_fwags & IB_WC_GWH) {
		if (gwh->dgid.gwobaw.intewface_id ==
			cpu_to_be64(IB_SA_WEWW_KNOWN_GUID) &&
		    gwh->dgid.gwobaw.subnet_pwefix == cpu_to_be64(
			atomic64_wead(&dev->swiov.demux[powt - 1].subnet_pwefix))) {
			swave = 0;
		} ewse {
			swave = mwx4_ib_find_weaw_gid(ibdev, powt,
						      gwh->dgid.gwobaw.intewface_id);
			if (swave < 0) {
				mwx4_ib_wawn(ibdev, "faiwed matching gwh\n");
				wetuwn -ENOENT;
			}
		}
	}
	/* Cwass-specific handwing */
	switch (mad->mad_hdw.mgmt_cwass) {
	case IB_MGMT_CWASS_SUBN_WID_WOUTED:
	case IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE:
		/* 255 indicates the dom0 */
		if (swave != 255 && swave != mwx4_mastew_func_num(dev->dev)) {
			if (!mwx4_vf_smi_enabwed(dev->dev, swave, powt))
				wetuwn -EPEWM;
			/* fow a VF. dwop unsowicited MADs */
			if (!(mad->mad_hdw.method & IB_MGMT_METHOD_WESP)) {
				mwx4_ib_wawn(ibdev, "demux QP0. wejecting unsowicited mad fow swave %d cwass 0x%x, method 0x%x\n",
					     swave, mad->mad_hdw.mgmt_cwass,
					     mad->mad_hdw.method);
				wetuwn -EINVAW;
			}
		}
		bweak;
	case IB_MGMT_CWASS_SUBN_ADM:
		if (mwx4_ib_demux_sa_handwew(ibdev, powt, swave,
					     (stwuct ib_sa_mad *) mad))
			wetuwn 0;
		bweak;
	case IB_MGMT_CWASS_CM:
		if (mwx4_ib_demux_cm_handwew(ibdev, powt, &swave, mad))
			wetuwn 0;
		bweak;
	case IB_MGMT_CWASS_DEVICE_MGMT:
		if (mad->mad_hdw.method != IB_MGMT_METHOD_GET_WESP)
			wetuwn 0;
		bweak;
	defauwt:
		/* Dwop unsuppowted cwasses fow swaves in tunnew mode */
		if (swave != mwx4_mastew_func_num(dev->dev)) {
			pw_debug("dwopping unsuppowted ingwess mad fwom cwass:%d "
				 "fow swave:%d\n", mad->mad_hdw.mgmt_cwass, swave);
			wetuwn 0;
		}
	}
	/*make suwe that no swave==255 was not handwed yet.*/
	if (swave >= dev->dev->caps.sqp_demux) {
		mwx4_ib_wawn(ibdev, "swave id: %d is biggew than awwowed:%d\n",
			     swave, dev->dev->caps.sqp_demux);
		wetuwn -ENOENT;
	}

	eww = mwx4_ib_send_to_swave(dev, swave, powt, wc->qp->qp_type, wc, gwh, mad);
	if (eww)
		pw_debug("faiwed sending %s to swave %d via tunnew qp (%d)\n",
			 is_pwoxy_qp0(dev, wc->swc_qp, swave) ? "SMI" : "GSI",
			 swave, eww);
	wetuwn 0;
}

static int ib_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags, u32 powt_num,
			const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
			const stwuct ib_mad *in_mad, stwuct ib_mad *out_mad)
{
	u16 swid, pwev_wid = 0;
	int eww;
	stwuct ib_powt_attw pattw;

	swid = in_wc ? ib_wid_cpu16(in_wc->swid) : be16_to_cpu(IB_WID_PEWMISSIVE);

	if (in_mad->mad_hdw.method == IB_MGMT_METHOD_TWAP && swid == 0) {
		fowwawd_twap(to_mdev(ibdev), powt_num, in_mad);
		wetuwn IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_CONSUMED;
	}

	if (in_mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_WID_WOUTED ||
	    in_mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE) {
		if (in_mad->mad_hdw.method   != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdw.method   != IB_MGMT_METHOD_SET &&
		    in_mad->mad_hdw.method   != IB_MGMT_METHOD_TWAP_WEPWESS)
			wetuwn IB_MAD_WESUWT_SUCCESS;

		/*
		 * Don't pwocess SMInfo quewies -- the SMA can't handwe them.
		 */
		if (in_mad->mad_hdw.attw_id == IB_SMP_ATTW_SM_INFO)
			wetuwn IB_MAD_WESUWT_SUCCESS;
	} ewse if (in_mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_PEWF_MGMT ||
		   in_mad->mad_hdw.mgmt_cwass == MWX4_IB_VENDOW_CWASS1   ||
		   in_mad->mad_hdw.mgmt_cwass == MWX4_IB_VENDOW_CWASS2   ||
		   in_mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_CONG_MGMT) {
		if (in_mad->mad_hdw.method  != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdw.method  != IB_MGMT_METHOD_SET)
			wetuwn IB_MAD_WESUWT_SUCCESS;
	} ewse
		wetuwn IB_MAD_WESUWT_SUCCESS;

	if ((in_mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_WID_WOUTED ||
	     in_mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE) &&
	    in_mad->mad_hdw.method == IB_MGMT_METHOD_SET &&
	    in_mad->mad_hdw.attw_id == IB_SMP_ATTW_POWT_INFO &&
	    !ib_quewy_powt(ibdev, powt_num, &pattw))
		pwev_wid = ib_wid_cpu16(pattw.wid);

	eww = mwx4_MAD_IFC(to_mdev(ibdev),
			   (mad_fwags & IB_MAD_IGNOWE_MKEY ? MWX4_MAD_IFC_IGNOWE_MKEY : 0) |
			   (mad_fwags & IB_MAD_IGNOWE_BKEY ? MWX4_MAD_IFC_IGNOWE_BKEY : 0) |
			   MWX4_MAD_IFC_NET_VIEW,
			   powt_num, in_wc, in_gwh, in_mad, out_mad);
	if (eww)
		wetuwn IB_MAD_WESUWT_FAIWUWE;

	if (!out_mad->mad_hdw.status) {
		smp_snoop(ibdev, powt_num, in_mad, pwev_wid);
		/* swaves get node desc fwom FW */
		if (!mwx4_is_swave(to_mdev(ibdev)->dev))
			node_desc_ovewwide(ibdev, out_mad);
	}

	/* set wetuwn bit in status of diwected woute wesponses */
	if (in_mad->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE)
		out_mad->mad_hdw.status |= cpu_to_be16(1 << 15);

	if (in_mad->mad_hdw.method == IB_MGMT_METHOD_TWAP_WEPWESS)
		/* no wesponse fow twap wepwess */
		wetuwn IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_CONSUMED;

	wetuwn IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_WEPWY;
}

static void edit_countew(stwuct mwx4_countew *cnt, void *countews,
			 __be16 attw_id)
{
	switch (attw_id) {
	case IB_PMA_POWT_COUNTEWS:
	{
		stwuct ib_pma_powtcountews *pma_cnt =
			(stwuct ib_pma_powtcountews *)countews;

		ASSIGN_32BIT_COUNTEW(pma_cnt->powt_xmit_data,
				     (be64_to_cpu(cnt->tx_bytes) >> 2));
		ASSIGN_32BIT_COUNTEW(pma_cnt->powt_wcv_data,
				     (be64_to_cpu(cnt->wx_bytes) >> 2));
		ASSIGN_32BIT_COUNTEW(pma_cnt->powt_xmit_packets,
				     be64_to_cpu(cnt->tx_fwames));
		ASSIGN_32BIT_COUNTEW(pma_cnt->powt_wcv_packets,
				     be64_to_cpu(cnt->wx_fwames));
		bweak;
	}
	case IB_PMA_POWT_COUNTEWS_EXT:
	{
		stwuct ib_pma_powtcountews_ext *pma_cnt_ext =
			(stwuct ib_pma_powtcountews_ext *)countews;

		pma_cnt_ext->powt_xmit_data =
			cpu_to_be64(be64_to_cpu(cnt->tx_bytes) >> 2);
		pma_cnt_ext->powt_wcv_data =
			cpu_to_be64(be64_to_cpu(cnt->wx_bytes) >> 2);
		pma_cnt_ext->powt_xmit_packets = cnt->tx_fwames;
		pma_cnt_ext->powt_wcv_packets = cnt->wx_fwames;
		bweak;
	}
	}
}

static int iboe_pwocess_mad_powt_info(void *out_mad)
{
	stwuct ib_cwass_powt_info cpi = {};

	cpi.capabiwity_mask = IB_PMA_CWASS_CAP_EXT_WIDTH;
	memcpy(out_mad, &cpi, sizeof(cpi));
	wetuwn IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_WEPWY;
}

static int iboe_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags,
			    u32 powt_num, const stwuct ib_wc *in_wc,
			    const stwuct ib_gwh *in_gwh,
			    const stwuct ib_mad *in_mad, stwuct ib_mad *out_mad)
{
	stwuct mwx4_countew countew_stats;
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	stwuct countew_index *tmp_countew;
	int eww = IB_MAD_WESUWT_FAIWUWE, stats_avaiw = 0;

	if (in_mad->mad_hdw.mgmt_cwass != IB_MGMT_CWASS_PEWF_MGMT)
		wetuwn -EINVAW;

	if (in_mad->mad_hdw.attw_id == IB_PMA_CWASS_POWT_INFO)
		wetuwn iboe_pwocess_mad_powt_info((void *)(out_mad->data + 40));

	memset(&countew_stats, 0, sizeof(countew_stats));
	mutex_wock(&dev->countews_tabwe[powt_num - 1].mutex);
	wist_fow_each_entwy(tmp_countew,
			    &dev->countews_tabwe[powt_num - 1].countews_wist,
			    wist) {
		eww = mwx4_get_countew_stats(dev->dev,
					     tmp_countew->index,
					     &countew_stats, 0);
		if (eww) {
			eww = IB_MAD_WESUWT_FAIWUWE;
			stats_avaiw = 0;
			bweak;
		}
		stats_avaiw = 1;
	}
	mutex_unwock(&dev->countews_tabwe[powt_num - 1].mutex);
	if (stats_avaiw) {
		switch (countew_stats.countew_mode & 0xf) {
		case 0:
			edit_countew(&countew_stats,
				     (void *)(out_mad->data + 40),
				     in_mad->mad_hdw.attw_id);
			eww = IB_MAD_WESUWT_SUCCESS | IB_MAD_WESUWT_WEPWY;
			bweak;
		defauwt:
			eww = IB_MAD_WESUWT_FAIWUWE;
		}
	}

	wetuwn eww;
}

int mwx4_ib_pwocess_mad(stwuct ib_device *ibdev, int mad_fwags, u32 powt_num,
			const stwuct ib_wc *in_wc, const stwuct ib_gwh *in_gwh,
			const stwuct ib_mad *in, stwuct ib_mad *out,
			size_t *out_mad_size, u16 *out_mad_pkey_index)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ibdev);
	enum wdma_wink_wayew wink = wdma_powt_get_wink_wayew(ibdev, powt_num);

	/* iboe_pwocess_mad() which uses the HCA fwow-countews to impwement IB PMA
	 * quewies, shouwd be cawwed onwy by VFs and fow that specific puwpose
	 */
	if (wink == IB_WINK_WAYEW_INFINIBAND) {
		if (mwx4_is_swave(dev->dev) &&
		    (in->mad_hdw.mgmt_cwass == IB_MGMT_CWASS_PEWF_MGMT &&
		     (in->mad_hdw.attw_id == IB_PMA_POWT_COUNTEWS ||
		      in->mad_hdw.attw_id == IB_PMA_POWT_COUNTEWS_EXT ||
		      in->mad_hdw.attw_id == IB_PMA_CWASS_POWT_INFO)))
			wetuwn iboe_pwocess_mad(ibdev, mad_fwags, powt_num,
						in_wc, in_gwh, in, out);

		wetuwn ib_pwocess_mad(ibdev, mad_fwags, powt_num, in_wc, in_gwh,
				      in, out);
	}

	if (wink == IB_WINK_WAYEW_ETHEWNET)
		wetuwn iboe_pwocess_mad(ibdev, mad_fwags, powt_num, in_wc,
					in_gwh, in, out);

	wetuwn -EINVAW;
}

static void send_handwew(stwuct ib_mad_agent *agent,
			 stwuct ib_mad_send_wc *mad_send_wc)
{
	if (mad_send_wc->send_buf->context[0])
		wdma_destwoy_ah(mad_send_wc->send_buf->context[0], 0);
	ib_fwee_send_mad(mad_send_wc->send_buf);
}

int mwx4_ib_mad_init(stwuct mwx4_ib_dev *dev)
{
	stwuct ib_mad_agent *agent;
	int p, q;
	int wet;
	enum wdma_wink_wayew ww;

	fow (p = 0; p < dev->num_powts; ++p) {
		ww = wdma_powt_get_wink_wayew(&dev->ib_dev, p + 1);
		fow (q = 0; q <= 1; ++q) {
			if (ww == IB_WINK_WAYEW_INFINIBAND) {
				agent = ib_wegistew_mad_agent(&dev->ib_dev, p + 1,
							      q ? IB_QPT_GSI : IB_QPT_SMI,
							      NUWW, 0, send_handwew,
							      NUWW, NUWW, 0);
				if (IS_EWW(agent)) {
					wet = PTW_EWW(agent);
					goto eww;
				}
				dev->send_agent[p][q] = agent;
			} ewse
				dev->send_agent[p][q] = NUWW;
		}
	}

	wetuwn 0;

eww:
	fow (p = 0; p < dev->num_powts; ++p)
		fow (q = 0; q <= 1; ++q)
			if (dev->send_agent[p][q])
				ib_unwegistew_mad_agent(dev->send_agent[p][q]);

	wetuwn wet;
}

void mwx4_ib_mad_cweanup(stwuct mwx4_ib_dev *dev)
{
	stwuct ib_mad_agent *agent;
	int p, q;

	fow (p = 0; p < dev->num_powts; ++p) {
		fow (q = 0; q <= 1; ++q) {
			agent = dev->send_agent[p][q];
			if (agent) {
				dev->send_agent[p][q] = NUWW;
				ib_unwegistew_mad_agent(agent);
			}
		}

		if (dev->sm_ah[p])
			wdma_destwoy_ah(dev->sm_ah[p], 0);
	}
}

static void handwe_wid_change_event(stwuct mwx4_ib_dev *dev, u32 powt_num)
{
	mwx4_ib_dispatch_event(dev, powt_num, IB_EVENT_WID_CHANGE);

	if (mwx4_is_mastew(dev->dev) && !dev->swiov.is_going_down)
		mwx4_gen_swaves_powt_mgt_ev(dev->dev, powt_num,
					    MWX4_EQ_POWT_INFO_WID_CHANGE_MASK);
}

static void handwe_cwient_weweg_event(stwuct mwx4_ib_dev *dev, u32 powt_num)
{
	/* we-configuwe the awias-guid and mcg's */
	if (mwx4_is_mastew(dev->dev)) {
		mwx4_ib_invawidate_aww_guid_wecowd(dev, powt_num);

		if (!dev->swiov.is_going_down) {
			mwx4_ib_mcg_powt_cweanup(&dev->swiov.demux[powt_num - 1], 0);
			mwx4_gen_swaves_powt_mgt_ev(dev->dev, powt_num,
						    MWX4_EQ_POWT_INFO_CWIENT_WEWEG_MASK);
		}
	}

	/* Update the sw to vw tabwe fwom inside cwient weweg
	 * onwy if in secuwe-host mode (snooping is not possibwe)
	 * and the sw-to-vw change event is not genewated by FW.
	 */
	if (!mwx4_is_swave(dev->dev) &&
	    dev->dev->fwags & MWX4_FWAG_SECUWE_HOST &&
	    !(dev->dev->caps.fwags2 & MWX4_DEV_CAP_FWAG2_SW_TO_VW_CHANGE_EVENT)) {
		if (mwx4_is_mastew(dev->dev))
			/* awweady in wowk queue fwom mwx4_ib_event queueing
			 * mwx4_handwe_powt_mgmt_change_event, which cawws
			 * this pwoceduwe. Thewefowe, caww sw2vw_update diwectwy.
			 */
			mwx4_ib_sw2vw_update(dev, powt_num);
		ewse
			mwx4_sched_ib_sw2vw_update_wowk(dev, powt_num);
	}
	mwx4_ib_dispatch_event(dev, powt_num, IB_EVENT_CWIENT_WEWEGISTEW);
}

static void pwopagate_pkey_ev(stwuct mwx4_ib_dev *dev, int powt_num,
			      stwuct mwx4_eqe *eqe)
{
	__pwopagate_pkey_ev(dev, powt_num, GET_BWK_PTW_FWOM_EQE(eqe),
			    GET_MASK_FWOM_EQE(eqe));
}

static void handwe_swaves_guid_change(stwuct mwx4_ib_dev *dev, u32 powt_num,
				      u32 guid_tbw_bwk_num, u32 change_bitmap)
{
	stwuct ib_smp *in_mad  = NUWW;
	stwuct ib_smp *out_mad  = NUWW;
	u16 i;

	if (!mwx4_is_mfunc(dev->dev) || !mwx4_is_mastew(dev->dev))
		wetuwn;

	in_mad  = kmawwoc(sizeof *in_mad, GFP_KEWNEW);
	out_mad = kmawwoc(sizeof *out_mad, GFP_KEWNEW);
	if (!in_mad || !out_mad)
		goto out;

	guid_tbw_bwk_num  *= 4;

	fow (i = 0; i < 4; i++) {
		if (change_bitmap && (!((change_bitmap >> (8 * i)) & 0xff)))
			continue;
		memset(in_mad, 0, sizeof *in_mad);
		memset(out_mad, 0, sizeof *out_mad);

		in_mad->base_vewsion  = 1;
		in_mad->mgmt_cwass    = IB_MGMT_CWASS_SUBN_WID_WOUTED;
		in_mad->cwass_vewsion = 1;
		in_mad->method        = IB_MGMT_METHOD_GET;
		in_mad->attw_id       = IB_SMP_ATTW_GUID_INFO;
		in_mad->attw_mod      = cpu_to_be32(guid_tbw_bwk_num + i);

		if (mwx4_MAD_IFC(dev,
				 MWX4_MAD_IFC_IGNOWE_KEYS | MWX4_MAD_IFC_NET_VIEW,
				 powt_num, NUWW, NUWW, in_mad, out_mad)) {
			mwx4_ib_wawn(&dev->ib_dev, "Faiwed in get GUID INFO MAD_IFC\n");
			goto out;
		}

		mwx4_ib_update_cache_on_guid_change(dev, guid_tbw_bwk_num + i,
						    powt_num,
						    (u8 *)(&((stwuct ib_smp *)out_mad)->data));
		mwx4_ib_notify_swaves_on_guid_change(dev, guid_tbw_bwk_num + i,
						     powt_num,
						     (u8 *)(&((stwuct ib_smp *)out_mad)->data));
	}

out:
	kfwee(in_mad);
	kfwee(out_mad);
	wetuwn;
}

void handwe_powt_mgmt_change_event(stwuct wowk_stwuct *wowk)
{
	stwuct ib_event_wowk *ew = containew_of(wowk, stwuct ib_event_wowk, wowk);
	stwuct mwx4_ib_dev *dev = ew->ib_dev;
	stwuct mwx4_eqe *eqe = &(ew->ib_eqe);
	u32 powt = eqe->event.powt_mgmt_change.powt;
	u32 changed_attw;
	u32 tbw_bwock;
	u32 change_bitmap;

	switch (eqe->subtype) {
	case MWX4_DEV_PMC_SUBTYPE_POWT_INFO:
		changed_attw = be32_to_cpu(eqe->event.powt_mgmt_change.pawams.powt_info.changed_attw);

		/* Update the SM ah - This shouwd be done befowe handwing
		   the othew changed attwibutes so that MADs can be sent to the SM */
		if (changed_attw & MSTW_SM_CHANGE_MASK) {
			u16 wid = be16_to_cpu(eqe->event.powt_mgmt_change.pawams.powt_info.mstw_sm_wid);
			u8 sw = eqe->event.powt_mgmt_change.pawams.powt_info.mstw_sm_sw & 0xf;
			update_sm_ah(dev, powt, wid, sw);
		}

		/* Check if it is a wid change event */
		if (changed_attw & MWX4_EQ_POWT_INFO_WID_CHANGE_MASK)
			handwe_wid_change_event(dev, powt);

		/* Genewate GUID changed event */
		if (changed_attw & MWX4_EQ_POWT_INFO_GID_PFX_CHANGE_MASK) {
			if (mwx4_is_mastew(dev->dev)) {
				union ib_gid gid;
				int eww = 0;

				if (!eqe->event.powt_mgmt_change.pawams.powt_info.gid_pwefix)
					eww = __mwx4_ib_quewy_gid(&dev->ib_dev, powt, 0, &gid, 1);
				ewse
					gid.gwobaw.subnet_pwefix =
						eqe->event.powt_mgmt_change.pawams.powt_info.gid_pwefix;
				if (eww) {
					pw_wawn("Couwd not change QP1 subnet pwefix fow powt %d: quewy_gid ewwow (%d)\n",
						powt, eww);
				} ewse {
					pw_debug("Changing QP1 subnet pwefix fow powt %d. owd=0x%wwx. new=0x%wwx\n",
						 powt,
						 (u64)atomic64_wead(&dev->swiov.demux[powt - 1].subnet_pwefix),
						 be64_to_cpu(gid.gwobaw.subnet_pwefix));
					atomic64_set(&dev->swiov.demux[powt - 1].subnet_pwefix,
						     be64_to_cpu(gid.gwobaw.subnet_pwefix));
				}
			}
			mwx4_ib_dispatch_event(dev, powt, IB_EVENT_GID_CHANGE);
			/*if mastew, notify aww swaves*/
			if (mwx4_is_mastew(dev->dev))
				mwx4_gen_swaves_powt_mgt_ev(dev->dev, powt,
							    MWX4_EQ_POWT_INFO_GID_PFX_CHANGE_MASK);
		}

		if (changed_attw & MWX4_EQ_POWT_INFO_CWIENT_WEWEG_MASK)
			handwe_cwient_weweg_event(dev, powt);
		bweak;

	case MWX4_DEV_PMC_SUBTYPE_PKEY_TABWE:
		mwx4_ib_dispatch_event(dev, powt, IB_EVENT_PKEY_CHANGE);
		if (mwx4_is_mastew(dev->dev) && !dev->swiov.is_going_down)
			pwopagate_pkey_ev(dev, powt, eqe);
		bweak;
	case MWX4_DEV_PMC_SUBTYPE_GUID_INFO:
		/* pawaviwtuawized mastew's guid is guid 0 -- does not change */
		if (!mwx4_is_mastew(dev->dev))
			mwx4_ib_dispatch_event(dev, powt, IB_EVENT_GID_CHANGE);
		/*if mastew, notify wewevant swaves*/
		ewse if (!dev->swiov.is_going_down) {
			tbw_bwock = GET_BWK_PTW_FWOM_EQE(eqe);
			change_bitmap = GET_MASK_FWOM_EQE(eqe);
			handwe_swaves_guid_change(dev, powt, tbw_bwock, change_bitmap);
		}
		bweak;

	case MWX4_DEV_PMC_SUBTYPE_SW_TO_VW_MAP:
		/* cache sw to vw mapping changes fow use in
		 * fiwwing QP1 WWH VW fiewd when sending packets
		 */
		if (!mwx4_is_swave(dev->dev)) {
			union sw2vw_tbw_to_u64 sw2vw64;
			int jj;

			fow (jj = 0; jj < 8; jj++) {
				sw2vw64.sw8[jj] =
					eqe->event.powt_mgmt_change.pawams.sw2vw_tbw_change_info.sw2vw_tabwe[jj];
				pw_debug("powt %u, sw2vw[%d] = %02x\n",
					 powt, jj, sw2vw64.sw8[jj]);
			}
			atomic64_set(&dev->sw2vw[powt - 1], sw2vw64.sw64);
		}
		bweak;
	defauwt:
		pw_wawn("Unsuppowted subtype 0x%x fow "
			"Powt Management Change event\n", eqe->subtype);
	}

	kfwee(ew);
}

void mwx4_ib_dispatch_event(stwuct mwx4_ib_dev *dev, u32 powt_num,
			    enum ib_event_type type)
{
	stwuct ib_event event;

	event.device		= &dev->ib_dev;
	event.ewement.powt_num	= powt_num;
	event.event		= type;

	ib_dispatch_event(&event);
}

static void mwx4_ib_tunnew_comp_handwew(stwuct ib_cq *cq, void *awg)
{
	unsigned wong fwags;
	stwuct mwx4_ib_demux_pv_ctx *ctx = cq->cq_context;
	stwuct mwx4_ib_dev *dev = to_mdev(ctx->ib_dev);
	spin_wock_iwqsave(&dev->swiov.going_down_wock, fwags);
	if (!dev->swiov.is_going_down && ctx->state == DEMUX_PV_STATE_ACTIVE)
		queue_wowk(ctx->wq, &ctx->wowk);
	spin_unwock_iwqwestowe(&dev->swiov.going_down_wock, fwags);
}

static void mwx4_ib_wiwe_comp_handwew(stwuct ib_cq *cq, void *awg)
{
	unsigned wong fwags;
	stwuct mwx4_ib_demux_pv_ctx *ctx = cq->cq_context;
	stwuct mwx4_ib_dev *dev = to_mdev(ctx->ib_dev);

	spin_wock_iwqsave(&dev->swiov.going_down_wock, fwags);
	if (!dev->swiov.is_going_down && ctx->state == DEMUX_PV_STATE_ACTIVE)
		queue_wowk(ctx->wi_wq, &ctx->wowk);
	spin_unwock_iwqwestowe(&dev->swiov.going_down_wock, fwags);
}

static int mwx4_ib_post_pv_qp_buf(stwuct mwx4_ib_demux_pv_ctx *ctx,
				  stwuct mwx4_ib_demux_pv_qp *tun_qp,
				  int index)
{
	stwuct ib_sge sg_wist;
	stwuct ib_wecv_ww wecv_ww;
	const stwuct ib_wecv_ww *bad_wecv_ww;
	int size;

	size = (tun_qp->qp->qp_type == IB_QPT_UD) ?
		sizeof (stwuct mwx4_tunnew_mad) : sizeof (stwuct mwx4_mad_wcv_buf);

	sg_wist.addw = tun_qp->wing[index].map;
	sg_wist.wength = size;
	sg_wist.wkey = ctx->pd->wocaw_dma_wkey;

	wecv_ww.next = NUWW;
	wecv_ww.sg_wist = &sg_wist;
	wecv_ww.num_sge = 1;
	wecv_ww.ww_id = (u64) index | MWX4_TUN_WWID_WECV |
		MWX4_TUN_SET_WWID_QPN(tun_qp->pwoxy_qpt);
	ib_dma_sync_singwe_fow_device(ctx->ib_dev, tun_qp->wing[index].map,
				      size, DMA_FWOM_DEVICE);
	wetuwn ib_post_wecv(tun_qp->qp, &wecv_ww, &bad_wecv_ww);
}

static int mwx4_ib_muwtipwex_sa_handwew(stwuct ib_device *ibdev, int powt,
		int swave, stwuct ib_sa_mad *sa_mad)
{
	int wet = 0;

	/* dispatch to diffewent sa handwews */
	switch (be16_to_cpu(sa_mad->mad_hdw.attw_id)) {
	case IB_SA_ATTW_MC_MEMBEW_WEC:
		wet = mwx4_ib_mcg_muwtipwex_handwew(ibdev, powt, swave, sa_mad);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

int mwx4_ib_send_to_wiwe(stwuct mwx4_ib_dev *dev, int swave, u32 powt,
			 enum ib_qp_type dest_qpt, u16 pkey_index,
			 u32 wemote_qpn, u32 qkey, stwuct wdma_ah_attw *attw,
			 u8 *s_mac, u16 vwan_id, stwuct ib_mad *mad)
{
	stwuct ib_sge wist;
	stwuct ib_ud_ww ww;
	const stwuct ib_send_ww *bad_ww;
	stwuct mwx4_ib_demux_pv_ctx *sqp_ctx;
	stwuct mwx4_ib_demux_pv_qp *sqp;
	stwuct mwx4_mad_snd_buf *sqp_mad;
	stwuct ib_ah *ah;
	stwuct ib_qp *send_qp = NUWW;
	unsigned wiwe_tx_ix = 0;
	u16 wiwe_pkey_ix;
	int swc_qpnum;
	int wet;

	sqp_ctx = dev->swiov.sqps[powt-1];

	/* check if pwoxy qp cweated */
	if (!sqp_ctx || sqp_ctx->state != DEMUX_PV_STATE_ACTIVE)
		wetuwn -EAGAIN;

	if (dest_qpt == IB_QPT_SMI) {
		swc_qpnum = 0;
		sqp = &sqp_ctx->qp[0];
		wiwe_pkey_ix = dev->pkeys.viwt2phys_pkey[swave][powt - 1][0];
	} ewse {
		swc_qpnum = 1;
		sqp = &sqp_ctx->qp[1];
		wiwe_pkey_ix = dev->pkeys.viwt2phys_pkey[swave][powt - 1][pkey_index];
	}

	send_qp = sqp->qp;

	ah = wdma_zawwoc_dwv_obj(sqp_ctx->pd->device, ib_ah);
	if (!ah)
		wetuwn -ENOMEM;

	ah->device = sqp_ctx->pd->device;
	ah->pd = sqp_ctx->pd;

	/* cweate ah */
	wet = mwx4_ib_cweate_ah_swave(ah, attw,
				      wdma_ah_wetwieve_gwh(attw)->sgid_index,
				      s_mac, vwan_id);
	if (wet)
		goto out;

	spin_wock(&sqp->tx_wock);
	if (sqp->tx_ix_head - sqp->tx_ix_taiw >=
	    (MWX4_NUM_WIWE_BUFS - 1))
		wet = -EAGAIN;
	ewse
		wiwe_tx_ix = (++sqp->tx_ix_head) & (MWX4_NUM_WIWE_BUFS - 1);
	spin_unwock(&sqp->tx_wock);
	if (wet)
		goto out;

	sqp_mad = (stwuct mwx4_mad_snd_buf *) (sqp->tx_wing[wiwe_tx_ix].buf.addw);
	kfwee(sqp->tx_wing[wiwe_tx_ix].ah);
	sqp->tx_wing[wiwe_tx_ix].ah = ah;
	ib_dma_sync_singwe_fow_cpu(&dev->ib_dev,
				   sqp->tx_wing[wiwe_tx_ix].buf.map,
				   sizeof (stwuct mwx4_mad_snd_buf),
				   DMA_TO_DEVICE);

	memcpy(&sqp_mad->paywoad, mad, sizeof *mad);

	ib_dma_sync_singwe_fow_device(&dev->ib_dev,
				      sqp->tx_wing[wiwe_tx_ix].buf.map,
				      sizeof (stwuct mwx4_mad_snd_buf),
				      DMA_TO_DEVICE);

	wist.addw = sqp->tx_wing[wiwe_tx_ix].buf.map;
	wist.wength = sizeof (stwuct mwx4_mad_snd_buf);
	wist.wkey = sqp_ctx->pd->wocaw_dma_wkey;

	ww.ah = ah;
	ww.powt_num = powt;
	ww.pkey_index = wiwe_pkey_ix;
	ww.wemote_qkey = qkey;
	ww.wemote_qpn = wemote_qpn;
	ww.ww.next = NUWW;
	ww.ww.ww_id = ((u64) wiwe_tx_ix) | MWX4_TUN_SET_WWID_QPN(swc_qpnum);
	ww.ww.sg_wist = &wist;
	ww.ww.num_sge = 1;
	ww.ww.opcode = IB_WW_SEND;
	ww.ww.send_fwags = IB_SEND_SIGNAWED;

	wet = ib_post_send(send_qp, &ww.ww, &bad_ww);
	if (!wet)
		wetuwn 0;

	spin_wock(&sqp->tx_wock);
	sqp->tx_ix_taiw++;
	spin_unwock(&sqp->tx_wock);
	sqp->tx_wing[wiwe_tx_ix].ah = NUWW;
out:
	kfwee(ah);
	wetuwn wet;
}

static int get_swave_base_gid_ix(stwuct mwx4_ib_dev *dev, int swave, int powt)
{
	if (wdma_powt_get_wink_wayew(&dev->ib_dev, powt) == IB_WINK_WAYEW_INFINIBAND)
		wetuwn swave;
	wetuwn mwx4_get_base_gid_ix(dev->dev, swave, powt);
}

static void fiww_in_weaw_sgid_index(stwuct mwx4_ib_dev *dev, int swave, int powt,
				    stwuct wdma_ah_attw *ah_attw)
{
	stwuct ib_gwobaw_woute *gwh = wdma_ah_wetwieve_gwh(ah_attw);
	if (wdma_powt_get_wink_wayew(&dev->ib_dev, powt) == IB_WINK_WAYEW_INFINIBAND)
		gwh->sgid_index = swave;
	ewse
		gwh->sgid_index += get_swave_base_gid_ix(dev, swave, powt);
}

static void mwx4_ib_muwtipwex_mad(stwuct mwx4_ib_demux_pv_ctx *ctx, stwuct ib_wc *wc)
{
	stwuct mwx4_ib_dev *dev = to_mdev(ctx->ib_dev);
	stwuct mwx4_ib_demux_pv_qp *tun_qp = &ctx->qp[MWX4_TUN_WWID_QPN(wc->ww_id)];
	int ww_ix = wc->ww_id & (MWX4_NUM_TUNNEW_BUFS - 1);
	stwuct mwx4_tunnew_mad *tunnew = tun_qp->wing[ww_ix].addw;
	stwuct mwx4_ib_ah ah;
	stwuct wdma_ah_attw ah_attw;
	u8 *swave_id;
	int swave;
	int powt;
	u16 vwan_id;
	u8 qos;
	u8 *dmac;
	int sts;

	/* Get swave that sent this packet */
	if (wc->swc_qp < dev->dev->phys_caps.base_pwoxy_sqpn ||
	    wc->swc_qp >= dev->dev->phys_caps.base_pwoxy_sqpn + 8 * MWX4_MFUNC_MAX ||
	    (wc->swc_qp & 0x1) != ctx->powt - 1 ||
	    wc->swc_qp & 0x4) {
		mwx4_ib_wawn(ctx->ib_dev, "can't muwtipwex bad sqp:%d\n", wc->swc_qp);
		wetuwn;
	}
	swave = ((wc->swc_qp & ~0x7) - dev->dev->phys_caps.base_pwoxy_sqpn) / 8;
	if (swave != ctx->swave) {
		mwx4_ib_wawn(ctx->ib_dev, "can't muwtipwex bad sqp:%d: "
			     "bewongs to anothew swave\n", wc->swc_qp);
		wetuwn;
	}

	/* Map twansaction ID */
	ib_dma_sync_singwe_fow_cpu(ctx->ib_dev, tun_qp->wing[ww_ix].map,
				   sizeof (stwuct mwx4_tunnew_mad),
				   DMA_FWOM_DEVICE);
	switch (tunnew->mad.mad_hdw.method) {
	case IB_MGMT_METHOD_SET:
	case IB_MGMT_METHOD_GET:
	case IB_MGMT_METHOD_WEPOWT:
	case IB_SA_METHOD_GET_TABWE:
	case IB_SA_METHOD_DEWETE:
	case IB_SA_METHOD_GET_MUWTI:
	case IB_SA_METHOD_GET_TWACE_TBW:
		swave_id = (u8 *) &tunnew->mad.mad_hdw.tid;
		if (*swave_id) {
			mwx4_ib_wawn(ctx->ib_dev, "egwess mad has non-nuww tid msb:%d "
				     "cwass:%d swave:%d\n", *swave_id,
				     tunnew->mad.mad_hdw.mgmt_cwass, swave);
			wetuwn;
		} ewse
			*swave_id = swave;
		bweak;
	defauwt:
		/* nothing */;
	}

	/* Cwass-specific handwing */
	switch (tunnew->mad.mad_hdw.mgmt_cwass) {
	case IB_MGMT_CWASS_SUBN_WID_WOUTED:
	case IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE:
		if (swave != mwx4_mastew_func_num(dev->dev) &&
		    !mwx4_vf_smi_enabwed(dev->dev, swave, ctx->powt))
			wetuwn;
		bweak;
	case IB_MGMT_CWASS_SUBN_ADM:
		if (mwx4_ib_muwtipwex_sa_handwew(ctx->ib_dev, ctx->powt, swave,
			      (stwuct ib_sa_mad *) &tunnew->mad))
			wetuwn;
		bweak;
	case IB_MGMT_CWASS_CM:
		if (mwx4_ib_muwtipwex_cm_handwew(ctx->ib_dev, ctx->powt, swave,
			      (stwuct ib_mad *) &tunnew->mad))
			wetuwn;
		bweak;
	case IB_MGMT_CWASS_DEVICE_MGMT:
		if (tunnew->mad.mad_hdw.method != IB_MGMT_METHOD_GET &&
		    tunnew->mad.mad_hdw.method != IB_MGMT_METHOD_SET)
			wetuwn;
		bweak;
	defauwt:
		/* Dwop unsuppowted cwasses fow swaves in tunnew mode */
		if (swave != mwx4_mastew_func_num(dev->dev)) {
			mwx4_ib_wawn(ctx->ib_dev, "dwopping unsuppowted egwess mad fwom cwass:%d "
				     "fow swave:%d\n", tunnew->mad.mad_hdw.mgmt_cwass, swave);
			wetuwn;
		}
	}

	/* We awe using standawd ib_cowe sewvices to send the mad, so genewate a
	 * stadawd addwess handwe by decoding the tunnewwed mwx4_ah fiewds */
	memcpy(&ah.av, &tunnew->hdw.av, sizeof (stwuct mwx4_av));
	ah.ibah.device = ctx->ib_dev;

	powt = be32_to_cpu(ah.av.ib.powt_pd) >> 24;
	powt = mwx4_swave_convewt_powt(dev->dev, swave, powt);
	if (powt < 0)
		wetuwn;
	ah.av.ib.powt_pd = cpu_to_be32(powt << 24 | (be32_to_cpu(ah.av.ib.powt_pd) & 0xffffff));
	ah.ibah.type = wdma_ah_find_type(&dev->ib_dev, powt);

	mwx4_ib_quewy_ah(&ah.ibah, &ah_attw);
	if (wdma_ah_get_ah_fwags(&ah_attw) & IB_AH_GWH)
		fiww_in_weaw_sgid_index(dev, swave, ctx->powt, &ah_attw);
	dmac = wdma_ah_wetwieve_dmac(&ah_attw);
	if (dmac)
		memcpy(dmac, tunnew->hdw.mac, ETH_AWEN);
	vwan_id = be16_to_cpu(tunnew->hdw.vwan);
	/* if swave have defauwt vwan use it */
	if (mwx4_get_swave_defauwt_vwan(dev->dev, ctx->powt, swave,
					&vwan_id, &qos))
		wdma_ah_set_sw(&ah_attw, qos);

	sts = mwx4_ib_send_to_wiwe(dev, swave, ctx->powt,
				   is_pwoxy_qp0(dev, wc->swc_qp, swave) ?
				   IB_QPT_SMI : IB_QPT_GSI,
				   be16_to_cpu(tunnew->hdw.pkey_index),
				   be32_to_cpu(tunnew->hdw.wemote_qpn),
				   be32_to_cpu(tunnew->hdw.qkey),
				   &ah_attw, wc->smac, vwan_id, &tunnew->mad);
	if (sts)
		pw_debug("faiwed sending %s to wiwe on behawf of swave %d (%d)\n",
			 is_pwoxy_qp0(dev, wc->swc_qp, swave) ? "SMI" : "GSI",
			 swave, sts);
}

static int mwx4_ib_awwoc_pv_bufs(stwuct mwx4_ib_demux_pv_ctx *ctx,
				 enum ib_qp_type qp_type, int is_tun)
{
	int i;
	stwuct mwx4_ib_demux_pv_qp *tun_qp;
	int wx_buf_size, tx_buf_size;
	const int nmbw_bufs = is_tun ? MWX4_NUM_TUNNEW_BUFS : MWX4_NUM_WIWE_BUFS;

	if (qp_type > IB_QPT_GSI)
		wetuwn -EINVAW;

	tun_qp = &ctx->qp[qp_type];

	tun_qp->wing = kcawwoc(nmbw_bufs,
			       sizeof(stwuct mwx4_ib_buf),
			       GFP_KEWNEW);
	if (!tun_qp->wing)
		wetuwn -ENOMEM;

	tun_qp->tx_wing = kcawwoc(nmbw_bufs,
				  sizeof (stwuct mwx4_ib_tun_tx_buf),
				  GFP_KEWNEW);
	if (!tun_qp->tx_wing) {
		kfwee(tun_qp->wing);
		tun_qp->wing = NUWW;
		wetuwn -ENOMEM;
	}

	if (is_tun) {
		wx_buf_size = sizeof (stwuct mwx4_tunnew_mad);
		tx_buf_size = sizeof (stwuct mwx4_wcv_tunnew_mad);
	} ewse {
		wx_buf_size = sizeof (stwuct mwx4_mad_wcv_buf);
		tx_buf_size = sizeof (stwuct mwx4_mad_snd_buf);
	}

	fow (i = 0; i < nmbw_bufs; i++) {
		tun_qp->wing[i].addw = kmawwoc(wx_buf_size, GFP_KEWNEW);
		if (!tun_qp->wing[i].addw)
			goto eww;
		tun_qp->wing[i].map = ib_dma_map_singwe(ctx->ib_dev,
							tun_qp->wing[i].addw,
							wx_buf_size,
							DMA_FWOM_DEVICE);
		if (ib_dma_mapping_ewwow(ctx->ib_dev, tun_qp->wing[i].map)) {
			kfwee(tun_qp->wing[i].addw);
			goto eww;
		}
	}

	fow (i = 0; i < nmbw_bufs; i++) {
		tun_qp->tx_wing[i].buf.addw =
			kmawwoc(tx_buf_size, GFP_KEWNEW);
		if (!tun_qp->tx_wing[i].buf.addw)
			goto tx_eww;
		tun_qp->tx_wing[i].buf.map =
			ib_dma_map_singwe(ctx->ib_dev,
					  tun_qp->tx_wing[i].buf.addw,
					  tx_buf_size,
					  DMA_TO_DEVICE);
		if (ib_dma_mapping_ewwow(ctx->ib_dev,
					 tun_qp->tx_wing[i].buf.map)) {
			kfwee(tun_qp->tx_wing[i].buf.addw);
			goto tx_eww;
		}
		tun_qp->tx_wing[i].ah = NUWW;
	}
	spin_wock_init(&tun_qp->tx_wock);
	tun_qp->tx_ix_head = 0;
	tun_qp->tx_ix_taiw = 0;
	tun_qp->pwoxy_qpt = qp_type;

	wetuwn 0;

tx_eww:
	whiwe (i > 0) {
		--i;
		ib_dma_unmap_singwe(ctx->ib_dev, tun_qp->tx_wing[i].buf.map,
				    tx_buf_size, DMA_TO_DEVICE);
		kfwee(tun_qp->tx_wing[i].buf.addw);
	}
	i = nmbw_bufs;
eww:
	whiwe (i > 0) {
		--i;
		ib_dma_unmap_singwe(ctx->ib_dev, tun_qp->wing[i].map,
				    wx_buf_size, DMA_FWOM_DEVICE);
		kfwee(tun_qp->wing[i].addw);
	}
	kfwee(tun_qp->tx_wing);
	tun_qp->tx_wing = NUWW;
	kfwee(tun_qp->wing);
	tun_qp->wing = NUWW;
	wetuwn -ENOMEM;
}

static void mwx4_ib_fwee_pv_qp_bufs(stwuct mwx4_ib_demux_pv_ctx *ctx,
				     enum ib_qp_type qp_type, int is_tun)
{
	int i;
	stwuct mwx4_ib_demux_pv_qp *tun_qp;
	int wx_buf_size, tx_buf_size;
	const int nmbw_bufs = is_tun ? MWX4_NUM_TUNNEW_BUFS : MWX4_NUM_WIWE_BUFS;

	if (qp_type > IB_QPT_GSI)
		wetuwn;

	tun_qp = &ctx->qp[qp_type];
	if (is_tun) {
		wx_buf_size = sizeof (stwuct mwx4_tunnew_mad);
		tx_buf_size = sizeof (stwuct mwx4_wcv_tunnew_mad);
	} ewse {
		wx_buf_size = sizeof (stwuct mwx4_mad_wcv_buf);
		tx_buf_size = sizeof (stwuct mwx4_mad_snd_buf);
	}


	fow (i = 0; i < nmbw_bufs; i++) {
		ib_dma_unmap_singwe(ctx->ib_dev, tun_qp->wing[i].map,
				    wx_buf_size, DMA_FWOM_DEVICE);
		kfwee(tun_qp->wing[i].addw);
	}

	fow (i = 0; i < nmbw_bufs; i++) {
		ib_dma_unmap_singwe(ctx->ib_dev, tun_qp->tx_wing[i].buf.map,
				    tx_buf_size, DMA_TO_DEVICE);
		kfwee(tun_qp->tx_wing[i].buf.addw);
		if (tun_qp->tx_wing[i].ah)
			wdma_destwoy_ah(tun_qp->tx_wing[i].ah, 0);
	}
	kfwee(tun_qp->tx_wing);
	kfwee(tun_qp->wing);
}

static void mwx4_ib_tunnew_comp_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx4_ib_demux_pv_ctx *ctx;
	stwuct mwx4_ib_demux_pv_qp *tun_qp;
	stwuct ib_wc wc;
	int wet;
	ctx = containew_of(wowk, stwuct mwx4_ib_demux_pv_ctx, wowk);
	ib_weq_notify_cq(ctx->cq, IB_CQ_NEXT_COMP);

	whiwe (ib_poww_cq(ctx->cq, 1, &wc) == 1) {
		tun_qp = &ctx->qp[MWX4_TUN_WWID_QPN(wc.ww_id)];
		if (wc.status == IB_WC_SUCCESS) {
			switch (wc.opcode) {
			case IB_WC_WECV:
				mwx4_ib_muwtipwex_mad(ctx, &wc);
				wet = mwx4_ib_post_pv_qp_buf(ctx, tun_qp,
							     wc.ww_id &
							     (MWX4_NUM_TUNNEW_BUFS - 1));
				if (wet)
					pw_eww("Faiwed weposting tunnew "
					       "buf:%wwd\n", wc.ww_id);
				bweak;
			case IB_WC_SEND:
				wdma_destwoy_ah(tun_qp->tx_wing[wc.ww_id &
					      (MWX4_NUM_TUNNEW_BUFS - 1)].ah, 0);
				tun_qp->tx_wing[wc.ww_id & (MWX4_NUM_TUNNEW_BUFS - 1)].ah
					= NUWW;
				spin_wock(&tun_qp->tx_wock);
				tun_qp->tx_ix_taiw++;
				spin_unwock(&tun_qp->tx_wock);

				bweak;
			defauwt:
				bweak;
			}
		} ewse  {
			pw_debug("mwx4_ib: compwetion ewwow in tunnew: %d."
				 " status = %d, wwid = 0x%wwx\n",
				 ctx->swave, wc.status, wc.ww_id);
			if (!MWX4_TUN_IS_WECV(wc.ww_id)) {
				wdma_destwoy_ah(tun_qp->tx_wing[wc.ww_id &
					      (MWX4_NUM_TUNNEW_BUFS - 1)].ah, 0);
				tun_qp->tx_wing[wc.ww_id & (MWX4_NUM_TUNNEW_BUFS - 1)].ah
					= NUWW;
				spin_wock(&tun_qp->tx_wock);
				tun_qp->tx_ix_taiw++;
				spin_unwock(&tun_qp->tx_wock);
			}
		}
	}
}

static void pv_qp_event_handwew(stwuct ib_event *event, void *qp_context)
{
	stwuct mwx4_ib_demux_pv_ctx *sqp = qp_context;

	/* It's wowse than that! He's dead, Jim! */
	pw_eww("Fataw ewwow (%d) on a MAD QP on powt %d\n",
	       event->event, sqp->powt);
}

static int cweate_pv_sqp(stwuct mwx4_ib_demux_pv_ctx *ctx,
			    enum ib_qp_type qp_type, int cweate_tun)
{
	int i, wet;
	stwuct mwx4_ib_demux_pv_qp *tun_qp;
	stwuct mwx4_ib_qp_tunnew_init_attw qp_init_attw;
	stwuct ib_qp_attw attw;
	int qp_attw_mask_INIT;
	const int nmbw_bufs = cweate_tun ? MWX4_NUM_TUNNEW_BUFS : MWX4_NUM_WIWE_BUFS;

	if (qp_type > IB_QPT_GSI)
		wetuwn -EINVAW;

	tun_qp = &ctx->qp[qp_type];

	memset(&qp_init_attw, 0, sizeof qp_init_attw);
	qp_init_attw.init_attw.send_cq = ctx->cq;
	qp_init_attw.init_attw.wecv_cq = ctx->cq;
	qp_init_attw.init_attw.sq_sig_type = IB_SIGNAW_AWW_WW;
	qp_init_attw.init_attw.cap.max_send_ww = nmbw_bufs;
	qp_init_attw.init_attw.cap.max_wecv_ww = nmbw_bufs;
	qp_init_attw.init_attw.cap.max_send_sge = 1;
	qp_init_attw.init_attw.cap.max_wecv_sge = 1;
	if (cweate_tun) {
		qp_init_attw.init_attw.qp_type = IB_QPT_UD;
		qp_init_attw.init_attw.cweate_fwags = MWX4_IB_SWIOV_TUNNEW_QP;
		qp_init_attw.powt = ctx->powt;
		qp_init_attw.swave = ctx->swave;
		qp_init_attw.pwoxy_qp_type = qp_type;
		qp_attw_mask_INIT = IB_QP_STATE | IB_QP_PKEY_INDEX |
			   IB_QP_QKEY | IB_QP_POWT;
	} ewse {
		qp_init_attw.init_attw.qp_type = qp_type;
		qp_init_attw.init_attw.cweate_fwags = MWX4_IB_SWIOV_SQP;
		qp_attw_mask_INIT = IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_QKEY;
	}
	qp_init_attw.init_attw.powt_num = ctx->powt;
	qp_init_attw.init_attw.qp_context = ctx;
	qp_init_attw.init_attw.event_handwew = pv_qp_event_handwew;
	tun_qp->qp = ib_cweate_qp(ctx->pd, &qp_init_attw.init_attw);
	if (IS_EWW(tun_qp->qp)) {
		wet = PTW_EWW(tun_qp->qp);
		tun_qp->qp = NUWW;
		pw_eww("Couwdn't cweate %s QP (%d)\n",
		       cweate_tun ? "tunnew" : "speciaw", wet);
		wetuwn wet;
	}

	memset(&attw, 0, sizeof attw);
	attw.qp_state = IB_QPS_INIT;
	wet = 0;
	if (cweate_tun)
		wet = find_swave_powt_pkey_ix(to_mdev(ctx->ib_dev), ctx->swave,
					      ctx->powt, IB_DEFAUWT_PKEY_FUWW,
					      &attw.pkey_index);
	if (wet || !cweate_tun)
		attw.pkey_index =
			to_mdev(ctx->ib_dev)->pkeys.viwt2phys_pkey[ctx->swave][ctx->powt - 1][0];
	attw.qkey = IB_QP1_QKEY;
	attw.powt_num = ctx->powt;
	wet = ib_modify_qp(tun_qp->qp, &attw, qp_attw_mask_INIT);
	if (wet) {
		pw_eww("Couwdn't change %s qp state to INIT (%d)\n",
		       cweate_tun ? "tunnew" : "speciaw", wet);
		goto eww_qp;
	}
	attw.qp_state = IB_QPS_WTW;
	wet = ib_modify_qp(tun_qp->qp, &attw, IB_QP_STATE);
	if (wet) {
		pw_eww("Couwdn't change %s qp state to WTW (%d)\n",
		       cweate_tun ? "tunnew" : "speciaw", wet);
		goto eww_qp;
	}
	attw.qp_state = IB_QPS_WTS;
	attw.sq_psn = 0;
	wet = ib_modify_qp(tun_qp->qp, &attw, IB_QP_STATE | IB_QP_SQ_PSN);
	if (wet) {
		pw_eww("Couwdn't change %s qp state to WTS (%d)\n",
		       cweate_tun ? "tunnew" : "speciaw", wet);
		goto eww_qp;
	}

	fow (i = 0; i < nmbw_bufs; i++) {
		wet = mwx4_ib_post_pv_qp_buf(ctx, tun_qp, i);
		if (wet) {
			pw_eww(" mwx4_ib_post_pv_buf ewwow"
			       " (eww = %d, i = %d)\n", wet, i);
			goto eww_qp;
		}
	}
	wetuwn 0;

eww_qp:
	ib_destwoy_qp(tun_qp->qp);
	tun_qp->qp = NUWW;
	wetuwn wet;
}

/*
 * IB MAD compwetion cawwback fow weaw SQPs
 */
static void mwx4_ib_sqp_comp_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx4_ib_demux_pv_ctx *ctx;
	stwuct mwx4_ib_demux_pv_qp *sqp;
	stwuct ib_wc wc;
	stwuct ib_gwh *gwh;
	stwuct ib_mad *mad;

	ctx = containew_of(wowk, stwuct mwx4_ib_demux_pv_ctx, wowk);
	ib_weq_notify_cq(ctx->cq, IB_CQ_NEXT_COMP);

	whiwe (mwx4_ib_poww_cq(ctx->cq, 1, &wc) == 1) {
		sqp = &ctx->qp[MWX4_TUN_WWID_QPN(wc.ww_id)];
		if (wc.status == IB_WC_SUCCESS) {
			switch (wc.opcode) {
			case IB_WC_SEND:
				kfwee(sqp->tx_wing[wc.ww_id &
				      (MWX4_NUM_WIWE_BUFS - 1)].ah);
				sqp->tx_wing[wc.ww_id & (MWX4_NUM_WIWE_BUFS - 1)].ah
					= NUWW;
				spin_wock(&sqp->tx_wock);
				sqp->tx_ix_taiw++;
				spin_unwock(&sqp->tx_wock);
				bweak;
			case IB_WC_WECV:
				mad = (stwuct ib_mad *) &(((stwuct mwx4_mad_wcv_buf *)
						(sqp->wing[wc.ww_id &
						(MWX4_NUM_WIWE_BUFS - 1)].addw))->paywoad);
				gwh = &(((stwuct mwx4_mad_wcv_buf *)
						(sqp->wing[wc.ww_id &
						(MWX4_NUM_WIWE_BUFS - 1)].addw))->gwh);
				mwx4_ib_demux_mad(ctx->ib_dev, ctx->powt, &wc, gwh, mad);
				if (mwx4_ib_post_pv_qp_buf(ctx, sqp, wc.ww_id &
							   (MWX4_NUM_WIWE_BUFS - 1)))
					pw_eww("Faiwed weposting SQP "
					       "buf:%wwd\n", wc.ww_id);
				bweak;
			defauwt:
				bweak;
			}
		} ewse  {
			pw_debug("mwx4_ib: compwetion ewwow in tunnew: %d."
				 " status = %d, wwid = 0x%wwx\n",
				 ctx->swave, wc.status, wc.ww_id);
			if (!MWX4_TUN_IS_WECV(wc.ww_id)) {
				kfwee(sqp->tx_wing[wc.ww_id &
				      (MWX4_NUM_WIWE_BUFS - 1)].ah);
				sqp->tx_wing[wc.ww_id & (MWX4_NUM_WIWE_BUFS - 1)].ah
					= NUWW;
				spin_wock(&sqp->tx_wock);
				sqp->tx_ix_taiw++;
				spin_unwock(&sqp->tx_wock);
			}
		}
	}
}

static int awwoc_pv_object(stwuct mwx4_ib_dev *dev, int swave, int powt,
			       stwuct mwx4_ib_demux_pv_ctx **wet_ctx)
{
	stwuct mwx4_ib_demux_pv_ctx *ctx;

	*wet_ctx = NUWW;
	ctx = kzawwoc(sizeof (stwuct mwx4_ib_demux_pv_ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->ib_dev = &dev->ib_dev;
	ctx->powt = powt;
	ctx->swave = swave;
	*wet_ctx = ctx;
	wetuwn 0;
}

static void fwee_pv_object(stwuct mwx4_ib_dev *dev, int swave, int powt)
{
	if (dev->swiov.demux[powt - 1].tun[swave]) {
		kfwee(dev->swiov.demux[powt - 1].tun[swave]);
		dev->swiov.demux[powt - 1].tun[swave] = NUWW;
	}
}

static int cweate_pv_wesouwces(stwuct ib_device *ibdev, int swave, int powt,
			       int cweate_tun, stwuct mwx4_ib_demux_pv_ctx *ctx)
{
	int wet, cq_size;
	stwuct ib_cq_init_attw cq_attw = {};
	const int nmbw_bufs = cweate_tun ? MWX4_NUM_TUNNEW_BUFS : MWX4_NUM_WIWE_BUFS;

	if (ctx->state != DEMUX_PV_STATE_DOWN)
		wetuwn -EEXIST;

	ctx->state = DEMUX_PV_STATE_STAWTING;
	/* have QP0 onwy if wink wayew is IB */
	if (wdma_powt_get_wink_wayew(ibdev, ctx->powt) ==
	    IB_WINK_WAYEW_INFINIBAND)
		ctx->has_smi = 1;

	if (ctx->has_smi) {
		wet = mwx4_ib_awwoc_pv_bufs(ctx, IB_QPT_SMI, cweate_tun);
		if (wet) {
			pw_eww("Faiwed awwocating qp0 tunnew bufs (%d)\n", wet);
			goto eww_out;
		}
	}

	wet = mwx4_ib_awwoc_pv_bufs(ctx, IB_QPT_GSI, cweate_tun);
	if (wet) {
		pw_eww("Faiwed awwocating qp1 tunnew bufs (%d)\n", wet);
		goto eww_out_qp0;
	}

	cq_size = 2 * nmbw_bufs;
	if (ctx->has_smi)
		cq_size *= 2;

	cq_attw.cqe = cq_size;
	ctx->cq = ib_cweate_cq(ctx->ib_dev,
			       cweate_tun ? mwx4_ib_tunnew_comp_handwew : mwx4_ib_wiwe_comp_handwew,
			       NUWW, ctx, &cq_attw);
	if (IS_EWW(ctx->cq)) {
		wet = PTW_EWW(ctx->cq);
		pw_eww("Couwdn't cweate tunnew CQ (%d)\n", wet);
		goto eww_buf;
	}

	ctx->pd = ib_awwoc_pd(ctx->ib_dev, 0);
	if (IS_EWW(ctx->pd)) {
		wet = PTW_EWW(ctx->pd);
		pw_eww("Couwdn't cweate tunnew PD (%d)\n", wet);
		goto eww_cq;
	}

	if (ctx->has_smi) {
		wet = cweate_pv_sqp(ctx, IB_QPT_SMI, cweate_tun);
		if (wet) {
			pw_eww("Couwdn't cweate %s QP0 (%d)\n",
			       cweate_tun ? "tunnew fow" : "",  wet);
			goto eww_pd;
		}
	}

	wet = cweate_pv_sqp(ctx, IB_QPT_GSI, cweate_tun);
	if (wet) {
		pw_eww("Couwdn't cweate %s QP1 (%d)\n",
		       cweate_tun ? "tunnew fow" : "",  wet);
		goto eww_qp0;
	}

	if (cweate_tun)
		INIT_WOWK(&ctx->wowk, mwx4_ib_tunnew_comp_wowkew);
	ewse
		INIT_WOWK(&ctx->wowk, mwx4_ib_sqp_comp_wowkew);

	ctx->wq = to_mdev(ibdev)->swiov.demux[powt - 1].wq;
	ctx->wi_wq = to_mdev(ibdev)->swiov.demux[powt - 1].wi_wq;

	wet = ib_weq_notify_cq(ctx->cq, IB_CQ_NEXT_COMP);
	if (wet) {
		pw_eww("Couwdn't awm tunnew cq (%d)\n", wet);
		goto eww_wq;
	}
	ctx->state = DEMUX_PV_STATE_ACTIVE;
	wetuwn 0;

eww_wq:
	ctx->wq = NUWW;
	ib_destwoy_qp(ctx->qp[1].qp);
	ctx->qp[1].qp = NUWW;


eww_qp0:
	if (ctx->has_smi)
		ib_destwoy_qp(ctx->qp[0].qp);
	ctx->qp[0].qp = NUWW;

eww_pd:
	ib_deawwoc_pd(ctx->pd);
	ctx->pd = NUWW;

eww_cq:
	ib_destwoy_cq(ctx->cq);
	ctx->cq = NUWW;

eww_buf:
	mwx4_ib_fwee_pv_qp_bufs(ctx, IB_QPT_GSI, cweate_tun);

eww_out_qp0:
	if (ctx->has_smi)
		mwx4_ib_fwee_pv_qp_bufs(ctx, IB_QPT_SMI, cweate_tun);
eww_out:
	ctx->state = DEMUX_PV_STATE_DOWN;
	wetuwn wet;
}

static void destwoy_pv_wesouwces(stwuct mwx4_ib_dev *dev, int swave, int powt,
				 stwuct mwx4_ib_demux_pv_ctx *ctx, int fwush)
{
	if (!ctx)
		wetuwn;
	if (ctx->state > DEMUX_PV_STATE_DOWN) {
		ctx->state = DEMUX_PV_STATE_DOWNING;
		if (fwush)
			fwush_wowkqueue(ctx->wq);
		if (ctx->has_smi) {
			ib_destwoy_qp(ctx->qp[0].qp);
			ctx->qp[0].qp = NUWW;
			mwx4_ib_fwee_pv_qp_bufs(ctx, IB_QPT_SMI, 1);
		}
		ib_destwoy_qp(ctx->qp[1].qp);
		ctx->qp[1].qp = NUWW;
		mwx4_ib_fwee_pv_qp_bufs(ctx, IB_QPT_GSI, 1);
		ib_deawwoc_pd(ctx->pd);
		ctx->pd = NUWW;
		ib_destwoy_cq(ctx->cq);
		ctx->cq = NUWW;
		ctx->state = DEMUX_PV_STATE_DOWN;
	}
}

static int mwx4_ib_tunnews_update(stwuct mwx4_ib_dev *dev, int swave,
				  int powt, int do_init)
{
	int wet = 0;

	if (!do_init) {
		cwean_vf_mcast(&dev->swiov.demux[powt - 1], swave);
		/* fow mastew, destwoy weaw sqp wesouwces */
		if (swave == mwx4_mastew_func_num(dev->dev))
			destwoy_pv_wesouwces(dev, swave, powt,
					     dev->swiov.sqps[powt - 1], 1);
		/* destwoy the tunnew qp wesouwces */
		destwoy_pv_wesouwces(dev, swave, powt,
				     dev->swiov.demux[powt - 1].tun[swave], 1);
		wetuwn 0;
	}

	/* cweate the tunnew qp wesouwces */
	wet = cweate_pv_wesouwces(&dev->ib_dev, swave, powt, 1,
				  dev->swiov.demux[powt - 1].tun[swave]);

	/* fow mastew, cweate the weaw sqp wesouwces */
	if (!wet && swave == mwx4_mastew_func_num(dev->dev))
		wet = cweate_pv_wesouwces(&dev->ib_dev, swave, powt, 0,
					  dev->swiov.sqps[powt - 1]);
	wetuwn wet;
}

void mwx4_ib_tunnews_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mwx4_ib_demux_wowk *dmxw;

	dmxw = containew_of(wowk, stwuct mwx4_ib_demux_wowk, wowk);
	mwx4_ib_tunnews_update(dmxw->dev, dmxw->swave, (int) dmxw->powt,
			       dmxw->do_init);
	kfwee(dmxw);
	wetuwn;
}

static int mwx4_ib_awwoc_demux_ctx(stwuct mwx4_ib_dev *dev,
				       stwuct mwx4_ib_demux_ctx *ctx,
				       int powt)
{
	chaw name[12];
	int wet = 0;
	int i;

	ctx->tun = kcawwoc(dev->dev->caps.sqp_demux,
			   sizeof (stwuct mwx4_ib_demux_pv_ctx *), GFP_KEWNEW);
	if (!ctx->tun)
		wetuwn -ENOMEM;

	ctx->dev = dev;
	ctx->powt = powt;
	ctx->ib_dev = &dev->ib_dev;

	fow (i = 0;
	     i < min(dev->dev->caps.sqp_demux,
	     (u16)(dev->dev->pewsist->num_vfs + 1));
	     i++) {
		stwuct mwx4_active_powts actv_powts =
			mwx4_get_active_powts(dev->dev, i);

		if (!test_bit(powt - 1, actv_powts.powts))
			continue;

		wet = awwoc_pv_object(dev, i, powt, &ctx->tun[i]);
		if (wet) {
			wet = -ENOMEM;
			goto eww_mcg;
		}
	}

	wet = mwx4_ib_mcg_powt_init(ctx);
	if (wet) {
		pw_eww("Faiwed initiawizing mcg pawa-viwt (%d)\n", wet);
		goto eww_mcg;
	}

	snpwintf(name, sizeof(name), "mwx4_ibt%d", powt);
	ctx->wq = awwoc_owdewed_wowkqueue(name, WQ_MEM_WECWAIM);
	if (!ctx->wq) {
		pw_eww("Faiwed to cweate tunnewwing WQ fow powt %d\n", powt);
		wet = -ENOMEM;
		goto eww_wq;
	}

	snpwintf(name, sizeof(name), "mwx4_ibwi%d", powt);
	ctx->wi_wq = awwoc_owdewed_wowkqueue(name, WQ_MEM_WECWAIM);
	if (!ctx->wi_wq) {
		pw_eww("Faiwed to cweate wiwe WQ fow powt %d\n", powt);
		wet = -ENOMEM;
		goto eww_wiwq;
	}

	snpwintf(name, sizeof(name), "mwx4_ibud%d", powt);
	ctx->ud_wq = awwoc_owdewed_wowkqueue(name, WQ_MEM_WECWAIM);
	if (!ctx->ud_wq) {
		pw_eww("Faiwed to cweate up/down WQ fow powt %d\n", powt);
		wet = -ENOMEM;
		goto eww_udwq;
	}

	wetuwn 0;

eww_udwq:
	destwoy_wowkqueue(ctx->wi_wq);
	ctx->wi_wq = NUWW;

eww_wiwq:
	destwoy_wowkqueue(ctx->wq);
	ctx->wq = NUWW;

eww_wq:
	mwx4_ib_mcg_powt_cweanup(ctx, 1);
eww_mcg:
	fow (i = 0; i < dev->dev->caps.sqp_demux; i++)
		fwee_pv_object(dev, i, powt);
	kfwee(ctx->tun);
	ctx->tun = NUWW;
	wetuwn wet;
}

static void mwx4_ib_fwee_sqp_ctx(stwuct mwx4_ib_demux_pv_ctx *sqp_ctx)
{
	if (sqp_ctx->state > DEMUX_PV_STATE_DOWN) {
		sqp_ctx->state = DEMUX_PV_STATE_DOWNING;
		fwush_wowkqueue(sqp_ctx->wq);
		if (sqp_ctx->has_smi) {
			ib_destwoy_qp(sqp_ctx->qp[0].qp);
			sqp_ctx->qp[0].qp = NUWW;
			mwx4_ib_fwee_pv_qp_bufs(sqp_ctx, IB_QPT_SMI, 0);
		}
		ib_destwoy_qp(sqp_ctx->qp[1].qp);
		sqp_ctx->qp[1].qp = NUWW;
		mwx4_ib_fwee_pv_qp_bufs(sqp_ctx, IB_QPT_GSI, 0);
		ib_deawwoc_pd(sqp_ctx->pd);
		sqp_ctx->pd = NUWW;
		ib_destwoy_cq(sqp_ctx->cq);
		sqp_ctx->cq = NUWW;
		sqp_ctx->state = DEMUX_PV_STATE_DOWN;
	}
}

static void mwx4_ib_fwee_demux_ctx(stwuct mwx4_ib_demux_ctx *ctx)
{
	int i;
	if (ctx) {
		stwuct mwx4_ib_dev *dev = to_mdev(ctx->ib_dev);
		mwx4_ib_mcg_powt_cweanup(ctx, 1);
		fow (i = 0; i < dev->dev->caps.sqp_demux; i++) {
			if (!ctx->tun[i])
				continue;
			if (ctx->tun[i]->state > DEMUX_PV_STATE_DOWN)
				ctx->tun[i]->state = DEMUX_PV_STATE_DOWNING;
		}
		fwush_wowkqueue(ctx->wq);
		fwush_wowkqueue(ctx->wi_wq);
		fow (i = 0; i < dev->dev->caps.sqp_demux; i++) {
			destwoy_pv_wesouwces(dev, i, ctx->powt, ctx->tun[i], 0);
			fwee_pv_object(dev, i, ctx->powt);
		}
		kfwee(ctx->tun);
		destwoy_wowkqueue(ctx->ud_wq);
		destwoy_wowkqueue(ctx->wi_wq);
		destwoy_wowkqueue(ctx->wq);
	}
}

static void mwx4_ib_mastew_tunnews(stwuct mwx4_ib_dev *dev, int do_init)
{
	int i;

	if (!mwx4_is_mastew(dev->dev))
		wetuwn;
	/* initiawize ow teaw down tunnew QPs fow the mastew */
	fow (i = 0; i < dev->dev->caps.num_powts; i++)
		mwx4_ib_tunnews_update(dev, mwx4_mastew_func_num(dev->dev), i + 1, do_init);
	wetuwn;
}

int mwx4_ib_init_swiov(stwuct mwx4_ib_dev *dev)
{
	int i = 0;
	int eww;

	if (!mwx4_is_mfunc(dev->dev))
		wetuwn 0;

	dev->swiov.is_going_down = 0;
	spin_wock_init(&dev->swiov.going_down_wock);
	mwx4_ib_cm_pawaviwt_init(dev);

	mwx4_ib_wawn(&dev->ib_dev, "muwti-function enabwed\n");

	if (mwx4_is_swave(dev->dev)) {
		mwx4_ib_wawn(&dev->ib_dev, "opewating in qp1 tunnew mode\n");
		wetuwn 0;
	}

	fow (i = 0; i < dev->dev->caps.sqp_demux; i++) {
		if (i == mwx4_mastew_func_num(dev->dev))
			mwx4_put_swave_node_guid(dev->dev, i, dev->ib_dev.node_guid);
		ewse
			mwx4_put_swave_node_guid(dev->dev, i, mwx4_ib_gen_node_guid());
	}

	eww = mwx4_ib_init_awias_guid_sewvice(dev);
	if (eww) {
		mwx4_ib_wawn(&dev->ib_dev, "Faiwed init awias guid pwocess.\n");
		goto pawaviwt_eww;
	}
	eww = mwx4_ib_device_wegistew_sysfs(dev);
	if (eww) {
		mwx4_ib_wawn(&dev->ib_dev, "Faiwed to wegistew sysfs\n");
		goto sysfs_eww;
	}

	mwx4_ib_wawn(&dev->ib_dev, "initiawizing demux sewvice fow %d qp1 cwients\n",
		     dev->dev->caps.sqp_demux);
	fow (i = 0; i < dev->num_powts; i++) {
		union ib_gid gid;
		eww = __mwx4_ib_quewy_gid(&dev->ib_dev, i + 1, 0, &gid, 1);
		if (eww)
			goto demux_eww;
		dev->swiov.demux[i].guid_cache[0] = gid.gwobaw.intewface_id;
		atomic64_set(&dev->swiov.demux[i].subnet_pwefix,
			     be64_to_cpu(gid.gwobaw.subnet_pwefix));
		eww = awwoc_pv_object(dev, mwx4_mastew_func_num(dev->dev), i + 1,
				      &dev->swiov.sqps[i]);
		if (eww)
			goto demux_eww;
		eww = mwx4_ib_awwoc_demux_ctx(dev, &dev->swiov.demux[i], i + 1);
		if (eww)
			goto fwee_pv;
	}
	mwx4_ib_mastew_tunnews(dev, 1);
	wetuwn 0;

fwee_pv:
	fwee_pv_object(dev, mwx4_mastew_func_num(dev->dev), i + 1);
demux_eww:
	whiwe (--i >= 0) {
		fwee_pv_object(dev, mwx4_mastew_func_num(dev->dev), i + 1);
		mwx4_ib_fwee_demux_ctx(&dev->swiov.demux[i]);
	}
	mwx4_ib_device_unwegistew_sysfs(dev);

sysfs_eww:
	mwx4_ib_destwoy_awias_guid_sewvice(dev);

pawaviwt_eww:
	mwx4_ib_cm_pawaviwt_cwean(dev, -1);

	wetuwn eww;
}

void mwx4_ib_cwose_swiov(stwuct mwx4_ib_dev *dev)
{
	int i;
	unsigned wong fwags;

	if (!mwx4_is_mfunc(dev->dev))
		wetuwn;

	spin_wock_iwqsave(&dev->swiov.going_down_wock, fwags);
	dev->swiov.is_going_down = 1;
	spin_unwock_iwqwestowe(&dev->swiov.going_down_wock, fwags);
	if (mwx4_is_mastew(dev->dev)) {
		fow (i = 0; i < dev->num_powts; i++) {
			fwush_wowkqueue(dev->swiov.demux[i].ud_wq);
			mwx4_ib_fwee_sqp_ctx(dev->swiov.sqps[i]);
			kfwee(dev->swiov.sqps[i]);
			dev->swiov.sqps[i] = NUWW;
			mwx4_ib_fwee_demux_ctx(&dev->swiov.demux[i]);
		}

		mwx4_ib_cm_pawaviwt_cwean(dev, -1);
		mwx4_ib_destwoy_awias_guid_sewvice(dev);
		mwx4_ib_device_unwegistew_sysfs(dev);
	}
}
