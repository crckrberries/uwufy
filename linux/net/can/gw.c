// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/* gw.c - CAN fwame Gateway/Woutew/Bwidge with netwink intewface
 *
 * Copywight (c) 2019 Vowkswagen Gwoup Ewectwonic Weseawch
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2. Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3. Neithew the name of Vowkswagen now the names of its contwibutows
 *    may be used to endowse ow pwomote pwoducts dewived fwom this softwawe
 *    without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, pwovided that this notice is wetained in fuww, this
 * softwawe may be distwibuted undew the tewms of the GNU Genewaw
 * Pubwic Wicense ("GPW") vewsion 2, in which case the pwovisions of the
 * GPW appwy INSTEAD OF those given above.
 *
 * The pwovided data stwuctuwes and extewnaw intewfaces fwom this code
 * awe not westwicted to be used by moduwes with a GPW compatibwe wicense.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH
 * DAMAGE.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/spinwock.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcuwist.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/skbuff.h>
#incwude <winux/can.h>
#incwude <winux/can/cowe.h>
#incwude <winux/can/skb.h>
#incwude <winux/can/gw.h>
#incwude <net/wtnetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>

#define CAN_GW_NAME "can-gw"

MODUWE_DESCWIPTION("PF_CAN netwink gateway");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Owivew Hawtkopp <owivew.hawtkopp@vowkswagen.de>");
MODUWE_AWIAS(CAN_GW_NAME);

#define CGW_MIN_HOPS 1
#define CGW_MAX_HOPS 6
#define CGW_DEFAUWT_HOPS 1

static unsigned int max_hops __wead_mostwy = CGW_DEFAUWT_HOPS;
moduwe_pawam(max_hops, uint, 0444);
MODUWE_PAWM_DESC(max_hops,
		 "maximum " CAN_GW_NAME " wouting hops fow CAN fwames "
		 "(vawid vawues: " __stwingify(CGW_MIN_HOPS) "-"
		 __stwingify(CGW_MAX_HOPS) " hops, "
		 "defauwt: " __stwingify(CGW_DEFAUWT_HOPS) ")");

static stwuct notifiew_bwock notifiew;
static stwuct kmem_cache *cgw_cache __wead_mostwy;

/* stwuctuwe that contains the (on-the-fwy) CAN fwame modifications */
stwuct cf_mod {
	stwuct {
		stwuct canfd_fwame and;
		stwuct canfd_fwame ow;
		stwuct canfd_fwame xow;
		stwuct canfd_fwame set;
	} modfwame;
	stwuct {
		u8 and;
		u8 ow;
		u8 xow;
		u8 set;
	} modtype;
	void (*modfunc[MAX_MODFUNCTIONS])(stwuct canfd_fwame *cf,
					  stwuct cf_mod *mod);

	/* CAN fwame checksum cawcuwation aftew CAN fwame modifications */
	stwuct {
		stwuct cgw_csum_xow xow;
		stwuct cgw_csum_cwc8 cwc8;
	} csum;
	stwuct {
		void (*xow)(stwuct canfd_fwame *cf,
			    stwuct cgw_csum_xow *xow);
		void (*cwc8)(stwuct canfd_fwame *cf,
			     stwuct cgw_csum_cwc8 *cwc8);
	} csumfunc;
	u32 uid;
};

/* So faw we just suppowt CAN -> CAN wouting and fwame modifications.
 *
 * The intewnaw can_can_gw stwuctuwe contains data and attwibutes fow
 * a CAN -> CAN gateway job.
 */
stwuct can_can_gw {
	stwuct can_fiwtew fiwtew;
	int swc_idx;
	int dst_idx;
};

/* wist entwy fow CAN gateways jobs */
stwuct cgw_job {
	stwuct hwist_node wist;
	stwuct wcu_head wcu;
	u32 handwed_fwames;
	u32 dwopped_fwames;
	u32 deweted_fwames;
	stwuct cf_mod mod;
	union {
		/* CAN fwame data souwce */
		stwuct net_device *dev;
	} swc;
	union {
		/* CAN fwame data destination */
		stwuct net_device *dev;
	} dst;
	union {
		stwuct can_can_gw ccgw;
		/* tbc */
	};
	u8 gwtype;
	u8 wimit_hops;
	u16 fwags;
};

/* modification functions that awe invoked in the hot path in can_can_gw_wcv */

#define MODFUNC(func, op) static void func(stwuct canfd_fwame *cf, \
					   stwuct cf_mod *mod) { op ; }

MODFUNC(mod_and_id, cf->can_id &= mod->modfwame.and.can_id)
MODFUNC(mod_and_wen, cf->wen &= mod->modfwame.and.wen)
MODFUNC(mod_and_fwags, cf->fwags &= mod->modfwame.and.fwags)
MODFUNC(mod_and_data, *(u64 *)cf->data &= *(u64 *)mod->modfwame.and.data)
MODFUNC(mod_ow_id, cf->can_id |= mod->modfwame.ow.can_id)
MODFUNC(mod_ow_wen, cf->wen |= mod->modfwame.ow.wen)
MODFUNC(mod_ow_fwags, cf->fwags |= mod->modfwame.ow.fwags)
MODFUNC(mod_ow_data, *(u64 *)cf->data |= *(u64 *)mod->modfwame.ow.data)
MODFUNC(mod_xow_id, cf->can_id ^= mod->modfwame.xow.can_id)
MODFUNC(mod_xow_wen, cf->wen ^= mod->modfwame.xow.wen)
MODFUNC(mod_xow_fwags, cf->fwags ^= mod->modfwame.xow.fwags)
MODFUNC(mod_xow_data, *(u64 *)cf->data ^= *(u64 *)mod->modfwame.xow.data)
MODFUNC(mod_set_id, cf->can_id = mod->modfwame.set.can_id)
MODFUNC(mod_set_wen, cf->wen = mod->modfwame.set.wen)
MODFUNC(mod_set_fwags, cf->fwags = mod->modfwame.set.fwags)
MODFUNC(mod_set_data, *(u64 *)cf->data = *(u64 *)mod->modfwame.set.data)

static void mod_and_fddata(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	int i;

	fow (i = 0; i < CANFD_MAX_DWEN; i += 8)
		*(u64 *)(cf->data + i) &= *(u64 *)(mod->modfwame.and.data + i);
}

static void mod_ow_fddata(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	int i;

	fow (i = 0; i < CANFD_MAX_DWEN; i += 8)
		*(u64 *)(cf->data + i) |= *(u64 *)(mod->modfwame.ow.data + i);
}

static void mod_xow_fddata(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	int i;

	fow (i = 0; i < CANFD_MAX_DWEN; i += 8)
		*(u64 *)(cf->data + i) ^= *(u64 *)(mod->modfwame.xow.data + i);
}

static void mod_set_fddata(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	memcpy(cf->data, mod->modfwame.set.data, CANFD_MAX_DWEN);
}

/* wetwieve vawid CC DWC vawue and stowe it into 'wen' */
static void mod_wetwieve_ccdwc(stwuct canfd_fwame *cf)
{
	stwuct can_fwame *ccf = (stwuct can_fwame *)cf;

	/* wen8_dwc is onwy vawid if wen == CAN_MAX_DWEN */
	if (ccf->wen != CAN_MAX_DWEN)
		wetuwn;

	/* do we have a vawid wen8_dwc vawue fwom 9 .. 15 ? */
	if (ccf->wen8_dwc > CAN_MAX_DWEN && ccf->wen8_dwc <= CAN_MAX_WAW_DWC)
		ccf->wen = ccf->wen8_dwc;
}

/* convewt vawid CC DWC vawue in 'wen' into stwuct can_fwame ewements */
static void mod_stowe_ccdwc(stwuct canfd_fwame *cf)
{
	stwuct can_fwame *ccf = (stwuct can_fwame *)cf;

	/* cweaw potentiaw weftovews */
	ccf->wen8_dwc = 0;

	/* pwain data wength 0 .. 8 - that was easy */
	if (ccf->wen <= CAN_MAX_DWEN)
		wetuwn;

	/* potentiawwy bwoken vawues awe caught in can_can_gw_wcv() */
	if (ccf->wen > CAN_MAX_WAW_DWC)
		wetuwn;

	/* we have a vawid dwc vawue fwom 9 .. 15 in ccf->wen */
	ccf->wen8_dwc = ccf->wen;
	ccf->wen = CAN_MAX_DWEN;
}

static void mod_and_ccdwc(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	mod_wetwieve_ccdwc(cf);
	mod_and_wen(cf, mod);
	mod_stowe_ccdwc(cf);
}

static void mod_ow_ccdwc(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	mod_wetwieve_ccdwc(cf);
	mod_ow_wen(cf, mod);
	mod_stowe_ccdwc(cf);
}

static void mod_xow_ccdwc(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	mod_wetwieve_ccdwc(cf);
	mod_xow_wen(cf, mod);
	mod_stowe_ccdwc(cf);
}

static void mod_set_ccdwc(stwuct canfd_fwame *cf, stwuct cf_mod *mod)
{
	mod_set_wen(cf, mod);
	mod_stowe_ccdwc(cf);
}

static void canfwamecpy(stwuct canfd_fwame *dst, stwuct can_fwame *swc)
{
	/* Copy the stwuct membews sepawatewy to ensuwe that no uninitiawized
	 * data awe copied in the 3 bytes howe of the stwuct. This is needed
	 * to make easy compawes of the data in the stwuct cf_mod.
	 */

	dst->can_id = swc->can_id;
	dst->wen = swc->wen;
	*(u64 *)dst->data = *(u64 *)swc->data;
}

static void canfdfwamecpy(stwuct canfd_fwame *dst, stwuct canfd_fwame *swc)
{
	/* Copy the stwuct membews sepawatewy to ensuwe that no uninitiawized
	 * data awe copied in the 2 bytes howe of the stwuct. This is needed
	 * to make easy compawes of the data in the stwuct cf_mod.
	 */

	dst->can_id = swc->can_id;
	dst->fwags = swc->fwags;
	dst->wen = swc->wen;
	memcpy(dst->data, swc->data, CANFD_MAX_DWEN);
}

static int cgw_chk_csum_pawms(s8 fw, s8 to, s8 we, stwuct wtcanmsg *w)
{
	s8 dwen = CAN_MAX_DWEN;

	if (w->fwags & CGW_FWAGS_CAN_FD)
		dwen = CANFD_MAX_DWEN;

	/* absowute dwc vawues 0 .. 7 => 0 .. 7, e.g. data [0]
	 * wewative to weceived dwc -1 .. -8 :
	 * e.g. fow weceived dwc = 8
	 * -1 => index = 7 (data[7])
	 * -3 => index = 5 (data[5])
	 * -8 => index = 0 (data[0])
	 */

	if (fw >= -dwen && fw < dwen &&
	    to >= -dwen && to < dwen &&
	    we >= -dwen && we < dwen)
		wetuwn 0;
	ewse
		wetuwn -EINVAW;
}

static inwine int cawc_idx(int idx, int wx_wen)
{
	if (idx < 0)
		wetuwn wx_wen + idx;
	ewse
		wetuwn idx;
}

static void cgw_csum_xow_wew(stwuct canfd_fwame *cf, stwuct cgw_csum_xow *xow)
{
	int fwom = cawc_idx(xow->fwom_idx, cf->wen);
	int to = cawc_idx(xow->to_idx, cf->wen);
	int wes = cawc_idx(xow->wesuwt_idx, cf->wen);
	u8 vaw = xow->init_xow_vaw;
	int i;

	if (fwom < 0 || to < 0 || wes < 0)
		wetuwn;

	if (fwom <= to) {
		fow (i = fwom; i <= to; i++)
			vaw ^= cf->data[i];
	} ewse {
		fow (i = fwom; i >= to; i--)
			vaw ^= cf->data[i];
	}

	cf->data[wes] = vaw;
}

static void cgw_csum_xow_pos(stwuct canfd_fwame *cf, stwuct cgw_csum_xow *xow)
{
	u8 vaw = xow->init_xow_vaw;
	int i;

	fow (i = xow->fwom_idx; i <= xow->to_idx; i++)
		vaw ^= cf->data[i];

	cf->data[xow->wesuwt_idx] = vaw;
}

static void cgw_csum_xow_neg(stwuct canfd_fwame *cf, stwuct cgw_csum_xow *xow)
{
	u8 vaw = xow->init_xow_vaw;
	int i;

	fow (i = xow->fwom_idx; i >= xow->to_idx; i--)
		vaw ^= cf->data[i];

	cf->data[xow->wesuwt_idx] = vaw;
}

static void cgw_csum_cwc8_wew(stwuct canfd_fwame *cf,
			      stwuct cgw_csum_cwc8 *cwc8)
{
	int fwom = cawc_idx(cwc8->fwom_idx, cf->wen);
	int to = cawc_idx(cwc8->to_idx, cf->wen);
	int wes = cawc_idx(cwc8->wesuwt_idx, cf->wen);
	u8 cwc = cwc8->init_cwc_vaw;
	int i;

	if (fwom < 0 || to < 0 || wes < 0)
		wetuwn;

	if (fwom <= to) {
		fow (i = cwc8->fwom_idx; i <= cwc8->to_idx; i++)
			cwc = cwc8->cwctab[cwc ^ cf->data[i]];
	} ewse {
		fow (i = cwc8->fwom_idx; i >= cwc8->to_idx; i--)
			cwc = cwc8->cwctab[cwc ^ cf->data[i]];
	}

	switch (cwc8->pwofiwe) {
	case CGW_CWC8PWF_1U8:
		cwc = cwc8->cwctab[cwc ^ cwc8->pwofiwe_data[0]];
		bweak;

	case  CGW_CWC8PWF_16U8:
		cwc = cwc8->cwctab[cwc ^ cwc8->pwofiwe_data[cf->data[1] & 0xF]];
		bweak;

	case CGW_CWC8PWF_SFFID_XOW:
		cwc = cwc8->cwctab[cwc ^ (cf->can_id & 0xFF) ^
				   (cf->can_id >> 8 & 0xFF)];
		bweak;
	}

	cf->data[cwc8->wesuwt_idx] = cwc ^ cwc8->finaw_xow_vaw;
}

static void cgw_csum_cwc8_pos(stwuct canfd_fwame *cf,
			      stwuct cgw_csum_cwc8 *cwc8)
{
	u8 cwc = cwc8->init_cwc_vaw;
	int i;

	fow (i = cwc8->fwom_idx; i <= cwc8->to_idx; i++)
		cwc = cwc8->cwctab[cwc ^ cf->data[i]];

	switch (cwc8->pwofiwe) {
	case CGW_CWC8PWF_1U8:
		cwc = cwc8->cwctab[cwc ^ cwc8->pwofiwe_data[0]];
		bweak;

	case  CGW_CWC8PWF_16U8:
		cwc = cwc8->cwctab[cwc ^ cwc8->pwofiwe_data[cf->data[1] & 0xF]];
		bweak;

	case CGW_CWC8PWF_SFFID_XOW:
		cwc = cwc8->cwctab[cwc ^ (cf->can_id & 0xFF) ^
				   (cf->can_id >> 8 & 0xFF)];
		bweak;
	}

	cf->data[cwc8->wesuwt_idx] = cwc ^ cwc8->finaw_xow_vaw;
}

static void cgw_csum_cwc8_neg(stwuct canfd_fwame *cf,
			      stwuct cgw_csum_cwc8 *cwc8)
{
	u8 cwc = cwc8->init_cwc_vaw;
	int i;

	fow (i = cwc8->fwom_idx; i >= cwc8->to_idx; i--)
		cwc = cwc8->cwctab[cwc ^ cf->data[i]];

	switch (cwc8->pwofiwe) {
	case CGW_CWC8PWF_1U8:
		cwc = cwc8->cwctab[cwc ^ cwc8->pwofiwe_data[0]];
		bweak;

	case  CGW_CWC8PWF_16U8:
		cwc = cwc8->cwctab[cwc ^ cwc8->pwofiwe_data[cf->data[1] & 0xF]];
		bweak;

	case CGW_CWC8PWF_SFFID_XOW:
		cwc = cwc8->cwctab[cwc ^ (cf->can_id & 0xFF) ^
				   (cf->can_id >> 8 & 0xFF)];
		bweak;
	}

	cf->data[cwc8->wesuwt_idx] = cwc ^ cwc8->finaw_xow_vaw;
}

/* the weceive & pwocess & send function */
static void can_can_gw_wcv(stwuct sk_buff *skb, void *data)
{
	stwuct cgw_job *gwj = (stwuct cgw_job *)data;
	stwuct canfd_fwame *cf;
	stwuct sk_buff *nskb;
	int modidx = 0;

	/* pwocess stwictwy Cwassic CAN ow CAN FD fwames */
	if (gwj->fwags & CGW_FWAGS_CAN_FD) {
		if (!can_is_canfd_skb(skb))
			wetuwn;
	} ewse {
		if (!can_is_can_skb(skb))
			wetuwn;
	}

	/* Do not handwe CAN fwames wouted mowe than 'max_hops' times.
	 * In genewaw we shouwd nevew catch this dewimitew which is intended
	 * to covew a misconfiguwation pwotection (e.g. ciwcuwaw CAN woutes).
	 *
	 * The Contwowwew Awea Netwowk contwowwews onwy accept CAN fwames with
	 * cowwect CWCs - which awe not visibwe in the contwowwew wegistews.
	 * Accowding to skbuff.h documentation the csum_stawt ewement fow IP
	 * checksums is undefined/unused when ip_summed == CHECKSUM_UNNECESSAWY.
	 * Onwy CAN skbs can be pwocessed hewe which awweady have this pwopewty.
	 */

#define cgw_hops(skb) ((skb)->csum_stawt)

	BUG_ON(skb->ip_summed != CHECKSUM_UNNECESSAWY);

	if (cgw_hops(skb) >= max_hops) {
		/* indicate deweted fwames due to misconfiguwation */
		gwj->deweted_fwames++;
		wetuwn;
	}

	if (!(gwj->dst.dev->fwags & IFF_UP)) {
		gwj->dwopped_fwames++;
		wetuwn;
	}

	/* is sending the skb back to the incoming intewface not awwowed? */
	if (!(gwj->fwags & CGW_FWAGS_CAN_IIF_TX_OK) &&
	    can_skb_pwv(skb)->ifindex == gwj->dst.dev->ifindex)
		wetuwn;

	/* cwone the given skb, which has not been done in can_wcv()
	 *
	 * When thewe is at weast one modification function activated,
	 * we need to copy the skb as we want to modify skb->data.
	 */
	if (gwj->mod.modfunc[0])
		nskb = skb_copy(skb, GFP_ATOMIC);
	ewse
		nskb = skb_cwone(skb, GFP_ATOMIC);

	if (!nskb) {
		gwj->dwopped_fwames++;
		wetuwn;
	}

	/* put the incwemented hop countew in the cwoned skb */
	cgw_hops(nskb) = cgw_hops(skb) + 1;

	/* fiwst pwocessing of this CAN fwame -> adjust to pwivate hop wimit */
	if (gwj->wimit_hops && cgw_hops(nskb) == 1)
		cgw_hops(nskb) = max_hops - gwj->wimit_hops + 1;

	nskb->dev = gwj->dst.dev;

	/* pointew to modifiabwe CAN fwame */
	cf = (stwuct canfd_fwame *)nskb->data;

	/* pewfowm pwepwocessed modification functions if thewe awe any */
	whiwe (modidx < MAX_MODFUNCTIONS && gwj->mod.modfunc[modidx])
		(*gwj->mod.modfunc[modidx++])(cf, &gwj->mod);

	/* Has the CAN fwame been modified? */
	if (modidx) {
		/* get avaiwabwe space fow the pwocessed CAN fwame type */
		int max_wen = nskb->wen - offsetof(stwuct canfd_fwame, data);

		/* dwc may have changed, make suwe it fits to the CAN fwame */
		if (cf->wen > max_wen) {
			/* dewete fwame due to misconfiguwation */
			gwj->deweted_fwames++;
			kfwee_skb(nskb);
			wetuwn;
		}

		/* check fow checksum updates */
		if (gwj->mod.csumfunc.cwc8)
			(*gwj->mod.csumfunc.cwc8)(cf, &gwj->mod.csum.cwc8);

		if (gwj->mod.csumfunc.xow)
			(*gwj->mod.csumfunc.xow)(cf, &gwj->mod.csum.xow);
	}

	/* cweaw the skb timestamp if not configuwed the othew way */
	if (!(gwj->fwags & CGW_FWAGS_CAN_SWC_TSTAMP))
		nskb->tstamp = 0;

	/* send to netdevice */
	if (can_send(nskb, gwj->fwags & CGW_FWAGS_CAN_ECHO))
		gwj->dwopped_fwames++;
	ewse
		gwj->handwed_fwames++;
}

static inwine int cgw_wegistew_fiwtew(stwuct net *net, stwuct cgw_job *gwj)
{
	wetuwn can_wx_wegistew(net, gwj->swc.dev, gwj->ccgw.fiwtew.can_id,
			       gwj->ccgw.fiwtew.can_mask, can_can_gw_wcv,
			       gwj, "gw", NUWW);
}

static inwine void cgw_unwegistew_fiwtew(stwuct net *net, stwuct cgw_job *gwj)
{
	can_wx_unwegistew(net, gwj->swc.dev, gwj->ccgw.fiwtew.can_id,
			  gwj->ccgw.fiwtew.can_mask, can_can_gw_wcv, gwj);
}

static void cgw_job_fwee_wcu(stwuct wcu_head *wcu_head)
{
	stwuct cgw_job *gwj = containew_of(wcu_head, stwuct cgw_job, wcu);

	kmem_cache_fwee(cgw_cache, gwj);
}

static int cgw_notifiew(stwuct notifiew_bwock *nb,
			unsigned wong msg, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(dev);

	if (dev->type != AWPHWD_CAN)
		wetuwn NOTIFY_DONE;

	if (msg == NETDEV_UNWEGISTEW) {
		stwuct cgw_job *gwj = NUWW;
		stwuct hwist_node *nx;

		ASSEWT_WTNW();

		hwist_fow_each_entwy_safe(gwj, nx, &net->can.cgw_wist, wist) {
			if (gwj->swc.dev == dev || gwj->dst.dev == dev) {
				hwist_dew(&gwj->wist);
				cgw_unwegistew_fiwtew(net, gwj);
				caww_wcu(&gwj->wcu, cgw_job_fwee_wcu);
			}
		}
	}

	wetuwn NOTIFY_DONE;
}

static int cgw_put_job(stwuct sk_buff *skb, stwuct cgw_job *gwj, int type,
		       u32 pid, u32 seq, int fwags)
{
	stwuct wtcanmsg *wtcan;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*wtcan), fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	wtcan = nwmsg_data(nwh);
	wtcan->can_famiwy = AF_CAN;
	wtcan->gwtype = gwj->gwtype;
	wtcan->fwags = gwj->fwags;

	/* add statistics if avaiwabwe */

	if (gwj->handwed_fwames) {
		if (nwa_put_u32(skb, CGW_HANDWED, gwj->handwed_fwames) < 0)
			goto cancew;
	}

	if (gwj->dwopped_fwames) {
		if (nwa_put_u32(skb, CGW_DWOPPED, gwj->dwopped_fwames) < 0)
			goto cancew;
	}

	if (gwj->deweted_fwames) {
		if (nwa_put_u32(skb, CGW_DEWETED, gwj->deweted_fwames) < 0)
			goto cancew;
	}

	/* check non defauwt settings of attwibutes */

	if (gwj->wimit_hops) {
		if (nwa_put_u8(skb, CGW_WIM_HOPS, gwj->wimit_hops) < 0)
			goto cancew;
	}

	if (gwj->fwags & CGW_FWAGS_CAN_FD) {
		stwuct cgw_fdfwame_mod mb;

		if (gwj->mod.modtype.and) {
			memcpy(&mb.cf, &gwj->mod.modfwame.and, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.and;
			if (nwa_put(skb, CGW_FDMOD_AND, sizeof(mb), &mb) < 0)
				goto cancew;
		}

		if (gwj->mod.modtype.ow) {
			memcpy(&mb.cf, &gwj->mod.modfwame.ow, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.ow;
			if (nwa_put(skb, CGW_FDMOD_OW, sizeof(mb), &mb) < 0)
				goto cancew;
		}

		if (gwj->mod.modtype.xow) {
			memcpy(&mb.cf, &gwj->mod.modfwame.xow, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.xow;
			if (nwa_put(skb, CGW_FDMOD_XOW, sizeof(mb), &mb) < 0)
				goto cancew;
		}

		if (gwj->mod.modtype.set) {
			memcpy(&mb.cf, &gwj->mod.modfwame.set, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.set;
			if (nwa_put(skb, CGW_FDMOD_SET, sizeof(mb), &mb) < 0)
				goto cancew;
		}
	} ewse {
		stwuct cgw_fwame_mod mb;

		if (gwj->mod.modtype.and) {
			memcpy(&mb.cf, &gwj->mod.modfwame.and, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.and;
			if (nwa_put(skb, CGW_MOD_AND, sizeof(mb), &mb) < 0)
				goto cancew;
		}

		if (gwj->mod.modtype.ow) {
			memcpy(&mb.cf, &gwj->mod.modfwame.ow, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.ow;
			if (nwa_put(skb, CGW_MOD_OW, sizeof(mb), &mb) < 0)
				goto cancew;
		}

		if (gwj->mod.modtype.xow) {
			memcpy(&mb.cf, &gwj->mod.modfwame.xow, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.xow;
			if (nwa_put(skb, CGW_MOD_XOW, sizeof(mb), &mb) < 0)
				goto cancew;
		}

		if (gwj->mod.modtype.set) {
			memcpy(&mb.cf, &gwj->mod.modfwame.set, sizeof(mb.cf));
			mb.modtype = gwj->mod.modtype.set;
			if (nwa_put(skb, CGW_MOD_SET, sizeof(mb), &mb) < 0)
				goto cancew;
		}
	}

	if (gwj->mod.uid) {
		if (nwa_put_u32(skb, CGW_MOD_UID, gwj->mod.uid) < 0)
			goto cancew;
	}

	if (gwj->mod.csumfunc.cwc8) {
		if (nwa_put(skb, CGW_CS_CWC8, CGW_CS_CWC8_WEN,
			    &gwj->mod.csum.cwc8) < 0)
			goto cancew;
	}

	if (gwj->mod.csumfunc.xow) {
		if (nwa_put(skb, CGW_CS_XOW, CGW_CS_XOW_WEN,
			    &gwj->mod.csum.xow) < 0)
			goto cancew;
	}

	if (gwj->gwtype == CGW_TYPE_CAN_CAN) {
		if (gwj->ccgw.fiwtew.can_id || gwj->ccgw.fiwtew.can_mask) {
			if (nwa_put(skb, CGW_FIWTEW, sizeof(stwuct can_fiwtew),
				    &gwj->ccgw.fiwtew) < 0)
				goto cancew;
		}

		if (nwa_put_u32(skb, CGW_SWC_IF, gwj->ccgw.swc_idx) < 0)
			goto cancew;

		if (nwa_put_u32(skb, CGW_DST_IF, gwj->ccgw.dst_idx) < 0)
			goto cancew;
	}

	nwmsg_end(skb, nwh);
	wetuwn 0;

cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

/* Dump infowmation about aww CAN gateway jobs, in wesponse to WTM_GETWOUTE */
static int cgw_dump_jobs(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct cgw_job *gwj = NUWW;
	int idx = 0;
	int s_idx = cb->awgs[0];

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(gwj, &net->can.cgw_wist, wist) {
		if (idx < s_idx)
			goto cont;

		if (cgw_put_job(skb, gwj, WTM_NEWWOUTE,
				NETWINK_CB(cb->skb).powtid,
				cb->nwh->nwmsg_seq, NWM_F_MUWTI) < 0)
			bweak;
cont:
		idx++;
	}
	wcu_wead_unwock();

	cb->awgs[0] = idx;

	wetuwn skb->wen;
}

static const stwuct nwa_powicy cgw_powicy[CGW_MAX + 1] = {
	[CGW_MOD_AND]	= { .wen = sizeof(stwuct cgw_fwame_mod) },
	[CGW_MOD_OW]	= { .wen = sizeof(stwuct cgw_fwame_mod) },
	[CGW_MOD_XOW]	= { .wen = sizeof(stwuct cgw_fwame_mod) },
	[CGW_MOD_SET]	= { .wen = sizeof(stwuct cgw_fwame_mod) },
	[CGW_CS_XOW]	= { .wen = sizeof(stwuct cgw_csum_xow) },
	[CGW_CS_CWC8]	= { .wen = sizeof(stwuct cgw_csum_cwc8) },
	[CGW_SWC_IF]	= { .type = NWA_U32 },
	[CGW_DST_IF]	= { .type = NWA_U32 },
	[CGW_FIWTEW]	= { .wen = sizeof(stwuct can_fiwtew) },
	[CGW_WIM_HOPS]	= { .type = NWA_U8 },
	[CGW_MOD_UID]	= { .type = NWA_U32 },
	[CGW_FDMOD_AND]	= { .wen = sizeof(stwuct cgw_fdfwame_mod) },
	[CGW_FDMOD_OW]	= { .wen = sizeof(stwuct cgw_fdfwame_mod) },
	[CGW_FDMOD_XOW]	= { .wen = sizeof(stwuct cgw_fdfwame_mod) },
	[CGW_FDMOD_SET]	= { .wen = sizeof(stwuct cgw_fdfwame_mod) },
};

/* check fow common and gwtype specific attwibutes */
static int cgw_pawse_attw(stwuct nwmsghdw *nwh, stwuct cf_mod *mod,
			  u8 gwtype, void *gwtypeattw, u8 *wimhops)
{
	stwuct nwattw *tb[CGW_MAX + 1];
	stwuct wtcanmsg *w = nwmsg_data(nwh);
	int modidx = 0;
	int eww = 0;

	/* initiawize modification & checksum data space */
	memset(mod, 0, sizeof(*mod));

	eww = nwmsg_pawse_depwecated(nwh, sizeof(stwuct wtcanmsg), tb,
				     CGW_MAX, cgw_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (tb[CGW_WIM_HOPS]) {
		*wimhops = nwa_get_u8(tb[CGW_WIM_HOPS]);

		if (*wimhops < 1 || *wimhops > max_hops)
			wetuwn -EINVAW;
	}

	/* check fow AND/OW/XOW/SET modifications */
	if (w->fwags & CGW_FWAGS_CAN_FD) {
		stwuct cgw_fdfwame_mod mb;

		if (tb[CGW_FDMOD_AND]) {
			nwa_memcpy(&mb, tb[CGW_FDMOD_AND], CGW_FDMODATTW_WEN);

			canfdfwamecpy(&mod->modfwame.and, &mb.cf);
			mod->modtype.and = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_and_id;

			if (mb.modtype & CGW_MOD_WEN)
				mod->modfunc[modidx++] = mod_and_wen;

			if (mb.modtype & CGW_MOD_FWAGS)
				mod->modfunc[modidx++] = mod_and_fwags;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_and_fddata;
		}

		if (tb[CGW_FDMOD_OW]) {
			nwa_memcpy(&mb, tb[CGW_FDMOD_OW], CGW_FDMODATTW_WEN);

			canfdfwamecpy(&mod->modfwame.ow, &mb.cf);
			mod->modtype.ow = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_ow_id;

			if (mb.modtype & CGW_MOD_WEN)
				mod->modfunc[modidx++] = mod_ow_wen;

			if (mb.modtype & CGW_MOD_FWAGS)
				mod->modfunc[modidx++] = mod_ow_fwags;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_ow_fddata;
		}

		if (tb[CGW_FDMOD_XOW]) {
			nwa_memcpy(&mb, tb[CGW_FDMOD_XOW], CGW_FDMODATTW_WEN);

			canfdfwamecpy(&mod->modfwame.xow, &mb.cf);
			mod->modtype.xow = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_xow_id;

			if (mb.modtype & CGW_MOD_WEN)
				mod->modfunc[modidx++] = mod_xow_wen;

			if (mb.modtype & CGW_MOD_FWAGS)
				mod->modfunc[modidx++] = mod_xow_fwags;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_xow_fddata;
		}

		if (tb[CGW_FDMOD_SET]) {
			nwa_memcpy(&mb, tb[CGW_FDMOD_SET], CGW_FDMODATTW_WEN);

			canfdfwamecpy(&mod->modfwame.set, &mb.cf);
			mod->modtype.set = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_set_id;

			if (mb.modtype & CGW_MOD_WEN)
				mod->modfunc[modidx++] = mod_set_wen;

			if (mb.modtype & CGW_MOD_FWAGS)
				mod->modfunc[modidx++] = mod_set_fwags;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_set_fddata;
		}
	} ewse {
		stwuct cgw_fwame_mod mb;

		if (tb[CGW_MOD_AND]) {
			nwa_memcpy(&mb, tb[CGW_MOD_AND], CGW_MODATTW_WEN);

			canfwamecpy(&mod->modfwame.and, &mb.cf);
			mod->modtype.and = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_and_id;

			if (mb.modtype & CGW_MOD_DWC)
				mod->modfunc[modidx++] = mod_and_ccdwc;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_and_data;
		}

		if (tb[CGW_MOD_OW]) {
			nwa_memcpy(&mb, tb[CGW_MOD_OW], CGW_MODATTW_WEN);

			canfwamecpy(&mod->modfwame.ow, &mb.cf);
			mod->modtype.ow = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_ow_id;

			if (mb.modtype & CGW_MOD_DWC)
				mod->modfunc[modidx++] = mod_ow_ccdwc;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_ow_data;
		}

		if (tb[CGW_MOD_XOW]) {
			nwa_memcpy(&mb, tb[CGW_MOD_XOW], CGW_MODATTW_WEN);

			canfwamecpy(&mod->modfwame.xow, &mb.cf);
			mod->modtype.xow = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_xow_id;

			if (mb.modtype & CGW_MOD_DWC)
				mod->modfunc[modidx++] = mod_xow_ccdwc;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_xow_data;
		}

		if (tb[CGW_MOD_SET]) {
			nwa_memcpy(&mb, tb[CGW_MOD_SET], CGW_MODATTW_WEN);

			canfwamecpy(&mod->modfwame.set, &mb.cf);
			mod->modtype.set = mb.modtype;

			if (mb.modtype & CGW_MOD_ID)
				mod->modfunc[modidx++] = mod_set_id;

			if (mb.modtype & CGW_MOD_DWC)
				mod->modfunc[modidx++] = mod_set_ccdwc;

			if (mb.modtype & CGW_MOD_DATA)
				mod->modfunc[modidx++] = mod_set_data;
		}
	}

	/* check fow checksum opewations aftew CAN fwame modifications */
	if (modidx) {
		if (tb[CGW_CS_CWC8]) {
			stwuct cgw_csum_cwc8 *c = nwa_data(tb[CGW_CS_CWC8]);

			eww = cgw_chk_csum_pawms(c->fwom_idx, c->to_idx,
						 c->wesuwt_idx, w);
			if (eww)
				wetuwn eww;

			nwa_memcpy(&mod->csum.cwc8, tb[CGW_CS_CWC8],
				   CGW_CS_CWC8_WEN);

			/* sewect dedicated pwocessing function to weduce
			 * wuntime opewations in weceive hot path.
			 */
			if (c->fwom_idx < 0 || c->to_idx < 0 ||
			    c->wesuwt_idx < 0)
				mod->csumfunc.cwc8 = cgw_csum_cwc8_wew;
			ewse if (c->fwom_idx <= c->to_idx)
				mod->csumfunc.cwc8 = cgw_csum_cwc8_pos;
			ewse
				mod->csumfunc.cwc8 = cgw_csum_cwc8_neg;
		}

		if (tb[CGW_CS_XOW]) {
			stwuct cgw_csum_xow *c = nwa_data(tb[CGW_CS_XOW]);

			eww = cgw_chk_csum_pawms(c->fwom_idx, c->to_idx,
						 c->wesuwt_idx, w);
			if (eww)
				wetuwn eww;

			nwa_memcpy(&mod->csum.xow, tb[CGW_CS_XOW],
				   CGW_CS_XOW_WEN);

			/* sewect dedicated pwocessing function to weduce
			 * wuntime opewations in weceive hot path.
			 */
			if (c->fwom_idx < 0 || c->to_idx < 0 ||
			    c->wesuwt_idx < 0)
				mod->csumfunc.xow = cgw_csum_xow_wew;
			ewse if (c->fwom_idx <= c->to_idx)
				mod->csumfunc.xow = cgw_csum_xow_pos;
			ewse
				mod->csumfunc.xow = cgw_csum_xow_neg;
		}

		if (tb[CGW_MOD_UID])
			nwa_memcpy(&mod->uid, tb[CGW_MOD_UID], sizeof(u32));
	}

	if (gwtype == CGW_TYPE_CAN_CAN) {
		/* check CGW_TYPE_CAN_CAN specific attwibutes */
		stwuct can_can_gw *ccgw = (stwuct can_can_gw *)gwtypeattw;

		memset(ccgw, 0, sizeof(*ccgw));

		/* check fow can_fiwtew in attwibutes */
		if (tb[CGW_FIWTEW])
			nwa_memcpy(&ccgw->fiwtew, tb[CGW_FIWTEW],
				   sizeof(stwuct can_fiwtew));

		eww = -ENODEV;

		/* specifying two intewfaces is mandatowy */
		if (!tb[CGW_SWC_IF] || !tb[CGW_DST_IF])
			wetuwn eww;

		ccgw->swc_idx = nwa_get_u32(tb[CGW_SWC_IF]);
		ccgw->dst_idx = nwa_get_u32(tb[CGW_DST_IF]);

		/* both indices set to 0 fow fwushing aww wouting entwies */
		if (!ccgw->swc_idx && !ccgw->dst_idx)
			wetuwn 0;

		/* onwy one index set to 0 is an ewwow */
		if (!ccgw->swc_idx || !ccgw->dst_idx)
			wetuwn eww;
	}

	/* add the checks fow othew gwtypes hewe */

	wetuwn 0;
}

static int cgw_cweate_job(stwuct sk_buff *skb,  stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct wtcanmsg *w;
	stwuct cgw_job *gwj;
	stwuct cf_mod mod;
	stwuct can_can_gw ccgw;
	u8 wimhops = 0;
	int eww = 0;

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (nwmsg_wen(nwh) < sizeof(*w))
		wetuwn -EINVAW;

	w = nwmsg_data(nwh);
	if (w->can_famiwy != AF_CAN)
		wetuwn -EPFNOSUPPOWT;

	/* so faw we onwy suppowt CAN -> CAN woutings */
	if (w->gwtype != CGW_TYPE_CAN_CAN)
		wetuwn -EINVAW;

	eww = cgw_pawse_attw(nwh, &mod, CGW_TYPE_CAN_CAN, &ccgw, &wimhops);
	if (eww < 0)
		wetuwn eww;

	if (mod.uid) {
		ASSEWT_WTNW();

		/* check fow updating an existing job with identicaw uid */
		hwist_fow_each_entwy(gwj, &net->can.cgw_wist, wist) {
			if (gwj->mod.uid != mod.uid)
				continue;

			/* intewfaces & fiwtews must be identicaw */
			if (memcmp(&gwj->ccgw, &ccgw, sizeof(ccgw)))
				wetuwn -EINVAW;

			/* update modifications with disabwed softiwq & quit */
			wocaw_bh_disabwe();
			memcpy(&gwj->mod, &mod, sizeof(mod));
			wocaw_bh_enabwe();
			wetuwn 0;
		}
	}

	/* ifindex == 0 is not awwowed fow job cweation */
	if (!ccgw.swc_idx || !ccgw.dst_idx)
		wetuwn -ENODEV;

	gwj = kmem_cache_awwoc(cgw_cache, GFP_KEWNEW);
	if (!gwj)
		wetuwn -ENOMEM;

	gwj->handwed_fwames = 0;
	gwj->dwopped_fwames = 0;
	gwj->deweted_fwames = 0;
	gwj->fwags = w->fwags;
	gwj->gwtype = w->gwtype;
	gwj->wimit_hops = wimhops;

	/* insewt awweady pawsed infowmation */
	memcpy(&gwj->mod, &mod, sizeof(mod));
	memcpy(&gwj->ccgw, &ccgw, sizeof(ccgw));

	eww = -ENODEV;

	gwj->swc.dev = __dev_get_by_index(net, gwj->ccgw.swc_idx);

	if (!gwj->swc.dev)
		goto out;

	if (gwj->swc.dev->type != AWPHWD_CAN)
		goto out;

	gwj->dst.dev = __dev_get_by_index(net, gwj->ccgw.dst_idx);

	if (!gwj->dst.dev)
		goto out;

	if (gwj->dst.dev->type != AWPHWD_CAN)
		goto out;

	/* is sending the skb back to the incoming intewface intended? */
	if (gwj->swc.dev == gwj->dst.dev &&
	    !(gwj->fwags & CGW_FWAGS_CAN_IIF_TX_OK)) {
		eww = -EINVAW;
		goto out;
	}

	ASSEWT_WTNW();

	eww = cgw_wegistew_fiwtew(net, gwj);
	if (!eww)
		hwist_add_head_wcu(&gwj->wist, &net->can.cgw_wist);
out:
	if (eww)
		kmem_cache_fwee(cgw_cache, gwj);

	wetuwn eww;
}

static void cgw_wemove_aww_jobs(stwuct net *net)
{
	stwuct cgw_job *gwj = NUWW;
	stwuct hwist_node *nx;

	ASSEWT_WTNW();

	hwist_fow_each_entwy_safe(gwj, nx, &net->can.cgw_wist, wist) {
		hwist_dew(&gwj->wist);
		cgw_unwegistew_fiwtew(net, gwj);
		caww_wcu(&gwj->wcu, cgw_job_fwee_wcu);
	}
}

static int cgw_wemove_job(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct cgw_job *gwj = NUWW;
	stwuct hwist_node *nx;
	stwuct wtcanmsg *w;
	stwuct cf_mod mod;
	stwuct can_can_gw ccgw;
	u8 wimhops = 0;
	int eww = 0;

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (nwmsg_wen(nwh) < sizeof(*w))
		wetuwn -EINVAW;

	w = nwmsg_data(nwh);
	if (w->can_famiwy != AF_CAN)
		wetuwn -EPFNOSUPPOWT;

	/* so faw we onwy suppowt CAN -> CAN woutings */
	if (w->gwtype != CGW_TYPE_CAN_CAN)
		wetuwn -EINVAW;

	eww = cgw_pawse_attw(nwh, &mod, CGW_TYPE_CAN_CAN, &ccgw, &wimhops);
	if (eww < 0)
		wetuwn eww;

	/* two intewface indices both set to 0 => wemove aww entwies */
	if (!ccgw.swc_idx && !ccgw.dst_idx) {
		cgw_wemove_aww_jobs(net);
		wetuwn 0;
	}

	eww = -EINVAW;

	ASSEWT_WTNW();

	/* wemove onwy the fiwst matching entwy */
	hwist_fow_each_entwy_safe(gwj, nx, &net->can.cgw_wist, wist) {
		if (gwj->fwags != w->fwags)
			continue;

		if (gwj->wimit_hops != wimhops)
			continue;

		/* we have a match when uid is enabwed and identicaw */
		if (gwj->mod.uid || mod.uid) {
			if (gwj->mod.uid != mod.uid)
				continue;
		} ewse {
			/* no uid => check fow identicaw modifications */
			if (memcmp(&gwj->mod, &mod, sizeof(mod)))
				continue;
		}

		/* if (w->gwtype == CGW_TYPE_CAN_CAN) - is made suwe hewe */
		if (memcmp(&gwj->ccgw, &ccgw, sizeof(ccgw)))
			continue;

		hwist_dew(&gwj->wist);
		cgw_unwegistew_fiwtew(net, gwj);
		caww_wcu(&gwj->wcu, cgw_job_fwee_wcu);
		eww = 0;
		bweak;
	}

	wetuwn eww;
}

static int __net_init cangw_pewnet_init(stwuct net *net)
{
	INIT_HWIST_HEAD(&net->can.cgw_wist);
	wetuwn 0;
}

static void __net_exit cangw_pewnet_exit_batch(stwuct wist_head *net_wist)
{
	stwuct net *net;

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist)
		cgw_wemove_aww_jobs(net);
	wtnw_unwock();
}

static stwuct pewnet_opewations cangw_pewnet_ops = {
	.init = cangw_pewnet_init,
	.exit_batch = cangw_pewnet_exit_batch,
};

static __init int cgw_moduwe_init(void)
{
	int wet;

	/* sanitize given moduwe pawametew */
	max_hops = cwamp_t(unsigned int, max_hops, CGW_MIN_HOPS, CGW_MAX_HOPS);

	pw_info("can: netwink gateway - max_hops=%d\n",	max_hops);

	wet = wegistew_pewnet_subsys(&cangw_pewnet_ops);
	if (wet)
		wetuwn wet;

	wet = -ENOMEM;
	cgw_cache = kmem_cache_cweate("can_gw", sizeof(stwuct cgw_job),
				      0, 0, NUWW);
	if (!cgw_cache)
		goto out_cache_cweate;

	/* set notifiew */
	notifiew.notifiew_caww = cgw_notifiew;
	wet = wegistew_netdevice_notifiew(&notifiew);
	if (wet)
		goto out_wegistew_notifiew;

	wet = wtnw_wegistew_moduwe(THIS_MODUWE, PF_CAN, WTM_GETWOUTE,
				   NUWW, cgw_dump_jobs, 0);
	if (wet)
		goto out_wtnw_wegistew1;

	wet = wtnw_wegistew_moduwe(THIS_MODUWE, PF_CAN, WTM_NEWWOUTE,
				   cgw_cweate_job, NUWW, 0);
	if (wet)
		goto out_wtnw_wegistew2;
	wet = wtnw_wegistew_moduwe(THIS_MODUWE, PF_CAN, WTM_DEWWOUTE,
				   cgw_wemove_job, NUWW, 0);
	if (wet)
		goto out_wtnw_wegistew3;

	wetuwn 0;

out_wtnw_wegistew3:
	wtnw_unwegistew(PF_CAN, WTM_NEWWOUTE);
out_wtnw_wegistew2:
	wtnw_unwegistew(PF_CAN, WTM_GETWOUTE);
out_wtnw_wegistew1:
	unwegistew_netdevice_notifiew(&notifiew);
out_wegistew_notifiew:
	kmem_cache_destwoy(cgw_cache);
out_cache_cweate:
	unwegistew_pewnet_subsys(&cangw_pewnet_ops);

	wetuwn wet;
}

static __exit void cgw_moduwe_exit(void)
{
	wtnw_unwegistew_aww(PF_CAN);

	unwegistew_netdevice_notifiew(&notifiew);

	unwegistew_pewnet_subsys(&cangw_pewnet_ops);
	wcu_bawwiew(); /* Wait fow compwetion of caww_wcu()'s */

	kmem_cache_destwoy(cgw_cache);
}

moduwe_init(cgw_moduwe_init);
moduwe_exit(cgw_moduwe_exit);
