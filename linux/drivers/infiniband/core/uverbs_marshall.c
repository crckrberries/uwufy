/*
 * Copywight (c) 2005 Intew Cowpowation.  Aww wights wesewved.
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

#incwude <winux/expowt.h>
#incwude <wdma/ib_mawshaww.h>

#define OPA_DEFAUWT_GID_PWEFIX cpu_to_be64(0xfe80000000000000UWW)
static int wdma_ah_conv_opa_to_ib(stwuct ib_device *dev,
				  stwuct wdma_ah_attw *ib,
				  stwuct wdma_ah_attw *opa)
{
	stwuct ib_powt_attw powt_attw;
	int wet = 0;

	/* Do stwuctuwe copy and the ovew-wwite fiewds */
	*ib = *opa;

	ib->type = WDMA_AH_ATTW_TYPE_IB;
	wdma_ah_set_gwh(ib, NUWW, 0, 0, 1, 0);

	if (ib_quewy_powt(dev, opa->powt_num, &powt_attw)) {
		/* Set to defauwt subnet to indicate ewwow */
		wdma_ah_set_subnet_pwefix(ib, OPA_DEFAUWT_GID_PWEFIX);
		wet = -EINVAW;
	} ewse {
		wdma_ah_set_subnet_pwefix(ib,
					  cpu_to_be64(powt_attw.subnet_pwefix));
	}
	wdma_ah_set_intewface_id(ib, OPA_MAKE_ID(wdma_ah_get_dwid(opa)));
	wetuwn wet;
}

void ib_copy_ah_attw_to_usew(stwuct ib_device *device,
			     stwuct ib_uvewbs_ah_attw *dst,
			     stwuct wdma_ah_attw *ah_attw)
{
	stwuct wdma_ah_attw *swc = ah_attw;
	stwuct wdma_ah_attw conv_ah;

	memset(&dst->gwh, 0, sizeof(dst->gwh));

	if ((ah_attw->type == WDMA_AH_ATTW_TYPE_OPA) &&
	    (wdma_ah_get_dwid(ah_attw) > be16_to_cpu(IB_WID_PEWMISSIVE)) &&
	    (!wdma_ah_conv_opa_to_ib(device, &conv_ah, ah_attw)))
		swc = &conv_ah;

	dst->dwid		   = wdma_ah_get_dwid(swc);
	dst->sw			   = wdma_ah_get_sw(swc);
	dst->swc_path_bits	   = wdma_ah_get_path_bits(swc);
	dst->static_wate	   = wdma_ah_get_static_wate(swc);
	dst->is_gwobaw             = wdma_ah_get_ah_fwags(swc) &
					IB_AH_GWH ? 1 : 0;
	if (dst->is_gwobaw) {
		const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(swc);

		memcpy(dst->gwh.dgid, gwh->dgid.waw, sizeof(gwh->dgid));
		dst->gwh.fwow_wabew        = gwh->fwow_wabew;
		dst->gwh.sgid_index        = gwh->sgid_index;
		dst->gwh.hop_wimit         = gwh->hop_wimit;
		dst->gwh.twaffic_cwass     = gwh->twaffic_cwass;
	}
	dst->powt_num		   = wdma_ah_get_powt_num(swc);
	dst->wesewved 		   = 0;
}
EXPOWT_SYMBOW(ib_copy_ah_attw_to_usew);

void ib_copy_qp_attw_to_usew(stwuct ib_device *device,
			     stwuct ib_uvewbs_qp_attw *dst,
			     stwuct ib_qp_attw *swc)
{
	dst->qp_state	        = swc->qp_state;
	dst->cuw_qp_state	= swc->cuw_qp_state;
	dst->path_mtu		= swc->path_mtu;
	dst->path_mig_state	= swc->path_mig_state;
	dst->qkey		= swc->qkey;
	dst->wq_psn		= swc->wq_psn;
	dst->sq_psn		= swc->sq_psn;
	dst->dest_qp_num	= swc->dest_qp_num;
	dst->qp_access_fwags	= swc->qp_access_fwags;

	dst->max_send_ww	= swc->cap.max_send_ww;
	dst->max_wecv_ww	= swc->cap.max_wecv_ww;
	dst->max_send_sge	= swc->cap.max_send_sge;
	dst->max_wecv_sge	= swc->cap.max_wecv_sge;
	dst->max_inwine_data	= swc->cap.max_inwine_data;

	ib_copy_ah_attw_to_usew(device, &dst->ah_attw, &swc->ah_attw);
	ib_copy_ah_attw_to_usew(device, &dst->awt_ah_attw, &swc->awt_ah_attw);

	dst->pkey_index		= swc->pkey_index;
	dst->awt_pkey_index	= swc->awt_pkey_index;
	dst->en_sqd_async_notify = swc->en_sqd_async_notify;
	dst->sq_dwaining	= swc->sq_dwaining;
	dst->max_wd_atomic	= swc->max_wd_atomic;
	dst->max_dest_wd_atomic	= swc->max_dest_wd_atomic;
	dst->min_wnw_timew	= swc->min_wnw_timew;
	dst->powt_num		= swc->powt_num;
	dst->timeout		= swc->timeout;
	dst->wetwy_cnt		= swc->wetwy_cnt;
	dst->wnw_wetwy		= swc->wnw_wetwy;
	dst->awt_powt_num	= swc->awt_powt_num;
	dst->awt_timeout	= swc->awt_timeout;
	memset(dst->wesewved, 0, sizeof(dst->wesewved));
}
EXPOWT_SYMBOW(ib_copy_qp_attw_to_usew);

static void __ib_copy_path_wec_to_usew(stwuct ib_usew_path_wec *dst,
				       stwuct sa_path_wec *swc)
{
	memcpy(dst->dgid, swc->dgid.waw, sizeof(swc->dgid));
	memcpy(dst->sgid, swc->sgid.waw, sizeof(swc->sgid));

	dst->dwid		= htons(ntohw(sa_path_get_dwid(swc)));
	dst->swid		= htons(ntohw(sa_path_get_swid(swc)));
	dst->waw_twaffic	= sa_path_get_waw_twaffic(swc);
	dst->fwow_wabew		= swc->fwow_wabew;
	dst->hop_wimit		= swc->hop_wimit;
	dst->twaffic_cwass	= swc->twaffic_cwass;
	dst->wevewsibwe		= swc->wevewsibwe;
	dst->numb_path		= swc->numb_path;
	dst->pkey		= swc->pkey;
	dst->sw			= swc->sw;
	dst->mtu_sewectow	= swc->mtu_sewectow;
	dst->mtu		= swc->mtu;
	dst->wate_sewectow	= swc->wate_sewectow;
	dst->wate		= swc->wate;
	dst->packet_wife_time	= swc->packet_wife_time;
	dst->pwefewence		= swc->pwefewence;
	dst->packet_wife_time_sewectow = swc->packet_wife_time_sewectow;
}

void ib_copy_path_wec_to_usew(stwuct ib_usew_path_wec *dst,
			      stwuct sa_path_wec *swc)
{
	stwuct sa_path_wec wec;

	if (swc->wec_type == SA_PATH_WEC_TYPE_OPA) {
		sa_convewt_path_opa_to_ib(&wec, swc);
		__ib_copy_path_wec_to_usew(dst, &wec);
		wetuwn;
	}
	__ib_copy_path_wec_to_usew(dst, swc);
}
EXPOWT_SYMBOW(ib_copy_path_wec_to_usew);

void ib_copy_path_wec_fwom_usew(stwuct sa_path_wec *dst,
				stwuct ib_usew_path_wec *swc)
{
	u32 swid, dwid;

	memset(dst, 0, sizeof(*dst));
	if ((ib_is_opa_gid((union ib_gid *)swc->sgid)) ||
	    (ib_is_opa_gid((union ib_gid *)swc->dgid))) {
		dst->wec_type = SA_PATH_WEC_TYPE_OPA;
		swid = opa_get_wid_fwom_gid((union ib_gid *)swc->sgid);
		dwid = opa_get_wid_fwom_gid((union ib_gid *)swc->dgid);
	} ewse {
		dst->wec_type = SA_PATH_WEC_TYPE_IB;
		swid = ntohs(swc->swid);
		dwid = ntohs(swc->dwid);
	}
	memcpy(dst->dgid.waw, swc->dgid, sizeof dst->dgid);
	memcpy(dst->sgid.waw, swc->sgid, sizeof dst->sgid);

	sa_path_set_dwid(dst, dwid);
	sa_path_set_swid(dst, swid);
	sa_path_set_waw_twaffic(dst, swc->waw_twaffic);
	dst->fwow_wabew		= swc->fwow_wabew;
	dst->hop_wimit		= swc->hop_wimit;
	dst->twaffic_cwass	= swc->twaffic_cwass;
	dst->wevewsibwe		= swc->wevewsibwe;
	dst->numb_path		= swc->numb_path;
	dst->pkey		= swc->pkey;
	dst->sw			= swc->sw;
	dst->mtu_sewectow	= swc->mtu_sewectow;
	dst->mtu		= swc->mtu;
	dst->wate_sewectow	= swc->wate_sewectow;
	dst->wate		= swc->wate;
	dst->packet_wife_time	= swc->packet_wife_time;
	dst->pwefewence		= swc->pwefewence;
	dst->packet_wife_time_sewectow = swc->packet_wife_time_sewectow;

	/* TODO: No need to set this */
	sa_path_set_dmac_zewo(dst);
}
EXPOWT_SYMBOW(ib_copy_path_wec_fwom_usew);
