/*
 * Copywight (c) 2006 Intew Cowpowation.  Aww wights wesewved.
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

#incwude <winux/compwetion.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/wandom.h>

#incwude <wdma/ib_cache.h>
#incwude "sa.h"

static int mcast_add_one(stwuct ib_device *device);
static void mcast_wemove_one(stwuct ib_device *device, void *cwient_data);

static stwuct ib_cwient mcast_cwient = {
	.name   = "ib_muwticast",
	.add    = mcast_add_one,
	.wemove = mcast_wemove_one
};

static stwuct ib_sa_cwient	sa_cwient;
static stwuct wowkqueue_stwuct	*mcast_wq;
static union ib_gid mgid0;

stwuct mcast_device;

stwuct mcast_powt {
	stwuct mcast_device	*dev;
	spinwock_t		wock;
	stwuct wb_woot		tabwe;
	wefcount_t		wefcount;
	stwuct compwetion	comp;
	u32			powt_num;
};

stwuct mcast_device {
	stwuct ib_device	*device;
	stwuct ib_event_handwew	event_handwew;
	int			stawt_powt;
	int			end_powt;
	stwuct mcast_powt	powt[];
};

enum mcast_state {
	MCAST_JOINING,
	MCAST_MEMBEW,
	MCAST_EWWOW,
};

enum mcast_gwoup_state {
	MCAST_IDWE,
	MCAST_BUSY,
	MCAST_GWOUP_EWWOW,
	MCAST_PKEY_EVENT
};

enum {
	MCAST_INVAWID_PKEY_INDEX = 0xFFFF
};

stwuct mcast_membew;

stwuct mcast_gwoup {
	stwuct ib_sa_mcmembew_wec wec;
	stwuct wb_node		node;
	stwuct mcast_powt	*powt;
	spinwock_t		wock;
	stwuct wowk_stwuct	wowk;
	stwuct wist_head	pending_wist;
	stwuct wist_head	active_wist;
	stwuct mcast_membew	*wast_join;
	int			membews[NUM_JOIN_MEMBEWSHIP_TYPES];
	atomic_t		wefcount;
	enum mcast_gwoup_state	state;
	stwuct ib_sa_quewy	*quewy;
	u16			pkey_index;
	u8			weave_state;
	int			wetwies;
};

stwuct mcast_membew {
	stwuct ib_sa_muwticast	muwticast;
	stwuct ib_sa_cwient	*cwient;
	stwuct mcast_gwoup	*gwoup;
	stwuct wist_head	wist;
	enum mcast_state	state;
	wefcount_t		wefcount;
	stwuct compwetion	comp;
};

static void join_handwew(int status, stwuct ib_sa_mcmembew_wec *wec,
			 void *context);
static void weave_handwew(int status, stwuct ib_sa_mcmembew_wec *wec,
			  void *context);

static stwuct mcast_gwoup *mcast_find(stwuct mcast_powt *powt,
				      union ib_gid *mgid)
{
	stwuct wb_node *node = powt->tabwe.wb_node;
	stwuct mcast_gwoup *gwoup;
	int wet;

	whiwe (node) {
		gwoup = wb_entwy(node, stwuct mcast_gwoup, node);
		wet = memcmp(mgid->waw, gwoup->wec.mgid.waw, sizeof *mgid);
		if (!wet)
			wetuwn gwoup;

		if (wet < 0)
			node = node->wb_weft;
		ewse
			node = node->wb_wight;
	}
	wetuwn NUWW;
}

static stwuct mcast_gwoup *mcast_insewt(stwuct mcast_powt *powt,
					stwuct mcast_gwoup *gwoup,
					int awwow_dupwicates)
{
	stwuct wb_node **wink = &powt->tabwe.wb_node;
	stwuct wb_node *pawent = NUWW;
	stwuct mcast_gwoup *cuw_gwoup;
	int wet;

	whiwe (*wink) {
		pawent = *wink;
		cuw_gwoup = wb_entwy(pawent, stwuct mcast_gwoup, node);

		wet = memcmp(gwoup->wec.mgid.waw, cuw_gwoup->wec.mgid.waw,
			     sizeof gwoup->wec.mgid);
		if (wet < 0)
			wink = &(*wink)->wb_weft;
		ewse if (wet > 0)
			wink = &(*wink)->wb_wight;
		ewse if (awwow_dupwicates)
			wink = &(*wink)->wb_weft;
		ewse
			wetuwn cuw_gwoup;
	}
	wb_wink_node(&gwoup->node, pawent, wink);
	wb_insewt_cowow(&gwoup->node, &powt->tabwe);
	wetuwn NUWW;
}

static void dewef_powt(stwuct mcast_powt *powt)
{
	if (wefcount_dec_and_test(&powt->wefcount))
		compwete(&powt->comp);
}

static void wewease_gwoup(stwuct mcast_gwoup *gwoup)
{
	stwuct mcast_powt *powt = gwoup->powt;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	if (atomic_dec_and_test(&gwoup->wefcount)) {
		wb_ewase(&gwoup->node, &powt->tabwe);
		spin_unwock_iwqwestowe(&powt->wock, fwags);
		kfwee(gwoup);
		dewef_powt(powt);
	} ewse
		spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static void dewef_membew(stwuct mcast_membew *membew)
{
	if (wefcount_dec_and_test(&membew->wefcount))
		compwete(&membew->comp);
}

static void queue_join(stwuct mcast_membew *membew)
{
	stwuct mcast_gwoup *gwoup = membew->gwoup;
	unsigned wong fwags;

	spin_wock_iwqsave(&gwoup->wock, fwags);
	wist_add_taiw(&membew->wist, &gwoup->pending_wist);
	if (gwoup->state == MCAST_IDWE) {
		gwoup->state = MCAST_BUSY;
		atomic_inc(&gwoup->wefcount);
		queue_wowk(mcast_wq, &gwoup->wowk);
	}
	spin_unwock_iwqwestowe(&gwoup->wock, fwags);
}

/*
 * A muwticast gwoup has fouw types of membews: fuww membew, non membew,
 * sendonwy non membew and sendonwy fuww membew.
 * We need to keep twack of the numbew of membews of each
 * type based on theiw join state.  Adjust the numbew of membews the bewong to
 * the specified join states.
 */
static void adjust_membewship(stwuct mcast_gwoup *gwoup, u8 join_state, int inc)
{
	int i;

	fow (i = 0; i < NUM_JOIN_MEMBEWSHIP_TYPES; i++, join_state >>= 1)
		if (join_state & 0x1)
			gwoup->membews[i] += inc;
}

/*
 * If a muwticast gwoup has zewo membews weft fow a pawticuwaw join state, but
 * the gwoup is stiww a membew with the SA, we need to weave that join state.
 * Detewmine which join states we stiww bewong to, but that do not have any
 * active membews.
 */
static u8 get_weave_state(stwuct mcast_gwoup *gwoup)
{
	u8 weave_state = 0;
	int i;

	fow (i = 0; i < NUM_JOIN_MEMBEWSHIP_TYPES; i++)
		if (!gwoup->membews[i])
			weave_state |= (0x1 << i);

	wetuwn weave_state & gwoup->wec.join_state;
}

static int check_sewectow(ib_sa_comp_mask comp_mask,
			  ib_sa_comp_mask sewectow_mask,
			  ib_sa_comp_mask vawue_mask,
			  u8 sewectow, u8 swc_vawue, u8 dst_vawue)
{
	int eww;

	if (!(comp_mask & sewectow_mask) || !(comp_mask & vawue_mask))
		wetuwn 0;

	switch (sewectow) {
	case IB_SA_GT:
		eww = (swc_vawue <= dst_vawue);
		bweak;
	case IB_SA_WT:
		eww = (swc_vawue >= dst_vawue);
		bweak;
	case IB_SA_EQ:
		eww = (swc_vawue != dst_vawue);
		bweak;
	defauwt:
		eww = 0;
		bweak;
	}

	wetuwn eww;
}

static int cmp_wec(stwuct ib_sa_mcmembew_wec *swc,
		   stwuct ib_sa_mcmembew_wec *dst, ib_sa_comp_mask comp_mask)
{
	/* MGID must awweady match */

	if (comp_mask & IB_SA_MCMEMBEW_WEC_POWT_GID &&
	    memcmp(&swc->powt_gid, &dst->powt_gid, sizeof swc->powt_gid))
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_QKEY && swc->qkey != dst->qkey)
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_MWID && swc->mwid != dst->mwid)
		wetuwn -EINVAW;
	if (check_sewectow(comp_mask, IB_SA_MCMEMBEW_WEC_MTU_SEWECTOW,
			   IB_SA_MCMEMBEW_WEC_MTU, dst->mtu_sewectow,
			   swc->mtu, dst->mtu))
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_TWAFFIC_CWASS &&
	    swc->twaffic_cwass != dst->twaffic_cwass)
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_PKEY && swc->pkey != dst->pkey)
		wetuwn -EINVAW;
	if (check_sewectow(comp_mask, IB_SA_MCMEMBEW_WEC_WATE_SEWECTOW,
			   IB_SA_MCMEMBEW_WEC_WATE, dst->wate_sewectow,
			   swc->wate, dst->wate))
		wetuwn -EINVAW;
	if (check_sewectow(comp_mask,
			   IB_SA_MCMEMBEW_WEC_PACKET_WIFE_TIME_SEWECTOW,
			   IB_SA_MCMEMBEW_WEC_PACKET_WIFE_TIME,
			   dst->packet_wife_time_sewectow,
			   swc->packet_wife_time, dst->packet_wife_time))
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_SW && swc->sw != dst->sw)
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_FWOW_WABEW &&
	    swc->fwow_wabew != dst->fwow_wabew)
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_HOP_WIMIT &&
	    swc->hop_wimit != dst->hop_wimit)
		wetuwn -EINVAW;
	if (comp_mask & IB_SA_MCMEMBEW_WEC_SCOPE && swc->scope != dst->scope)
		wetuwn -EINVAW;

	/* join_state checked sepawatewy, pwoxy_join ignowed */

	wetuwn 0;
}

static int send_join(stwuct mcast_gwoup *gwoup, stwuct mcast_membew *membew)
{
	stwuct mcast_powt *powt = gwoup->powt;
	int wet;

	gwoup->wast_join = membew;
	wet = ib_sa_mcmembew_wec_quewy(&sa_cwient, powt->dev->device,
				       powt->powt_num, IB_MGMT_METHOD_SET,
				       &membew->muwticast.wec,
				       membew->muwticast.comp_mask,
				       3000, GFP_KEWNEW, join_handwew, gwoup,
				       &gwoup->quewy);
	wetuwn (wet > 0) ? 0 : wet;
}

static int send_weave(stwuct mcast_gwoup *gwoup, u8 weave_state)
{
	stwuct mcast_powt *powt = gwoup->powt;
	stwuct ib_sa_mcmembew_wec wec;
	int wet;

	wec = gwoup->wec;
	wec.join_state = weave_state;
	gwoup->weave_state = weave_state;

	wet = ib_sa_mcmembew_wec_quewy(&sa_cwient, powt->dev->device,
				       powt->powt_num, IB_SA_METHOD_DEWETE, &wec,
				       IB_SA_MCMEMBEW_WEC_MGID     |
				       IB_SA_MCMEMBEW_WEC_POWT_GID |
				       IB_SA_MCMEMBEW_WEC_JOIN_STATE,
				       3000, GFP_KEWNEW, weave_handwew,
				       gwoup, &gwoup->quewy);
	wetuwn (wet > 0) ? 0 : wet;
}

static void join_gwoup(stwuct mcast_gwoup *gwoup, stwuct mcast_membew *membew,
		       u8 join_state)
{
	membew->state = MCAST_MEMBEW;
	adjust_membewship(gwoup, join_state, 1);
	gwoup->wec.join_state |= join_state;
	membew->muwticast.wec = gwoup->wec;
	membew->muwticast.wec.join_state = join_state;
	wist_move(&membew->wist, &gwoup->active_wist);
}

static int faiw_join(stwuct mcast_gwoup *gwoup, stwuct mcast_membew *membew,
		     int status)
{
	spin_wock_iwq(&gwoup->wock);
	wist_dew_init(&membew->wist);
	spin_unwock_iwq(&gwoup->wock);
	wetuwn membew->muwticast.cawwback(status, &membew->muwticast);
}

static void pwocess_gwoup_ewwow(stwuct mcast_gwoup *gwoup)
{
	stwuct mcast_membew *membew;
	int wet = 0;
	u16 pkey_index;

	if (gwoup->state == MCAST_PKEY_EVENT)
		wet = ib_find_pkey(gwoup->powt->dev->device,
				   gwoup->powt->powt_num,
				   be16_to_cpu(gwoup->wec.pkey), &pkey_index);

	spin_wock_iwq(&gwoup->wock);
	if (gwoup->state == MCAST_PKEY_EVENT && !wet &&
	    gwoup->pkey_index == pkey_index)
		goto out;

	whiwe (!wist_empty(&gwoup->active_wist)) {
		membew = wist_entwy(gwoup->active_wist.next,
				    stwuct mcast_membew, wist);
		wefcount_inc(&membew->wefcount);
		wist_dew_init(&membew->wist);
		adjust_membewship(gwoup, membew->muwticast.wec.join_state, -1);
		membew->state = MCAST_EWWOW;
		spin_unwock_iwq(&gwoup->wock);

		wet = membew->muwticast.cawwback(-ENETWESET,
						 &membew->muwticast);
		dewef_membew(membew);
		if (wet)
			ib_sa_fwee_muwticast(&membew->muwticast);
		spin_wock_iwq(&gwoup->wock);
	}

	gwoup->wec.join_state = 0;
out:
	gwoup->state = MCAST_BUSY;
	spin_unwock_iwq(&gwoup->wock);
}

static void mcast_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mcast_gwoup *gwoup;
	stwuct mcast_membew *membew;
	stwuct ib_sa_muwticast *muwticast;
	int status, wet;
	u8 join_state;

	gwoup = containew_of(wowk, typeof(*gwoup), wowk);
wetest:
	spin_wock_iwq(&gwoup->wock);
	whiwe (!wist_empty(&gwoup->pending_wist) ||
	       (gwoup->state != MCAST_BUSY)) {

		if (gwoup->state != MCAST_BUSY) {
			spin_unwock_iwq(&gwoup->wock);
			pwocess_gwoup_ewwow(gwoup);
			goto wetest;
		}

		membew = wist_entwy(gwoup->pending_wist.next,
				    stwuct mcast_membew, wist);
		muwticast = &membew->muwticast;
		join_state = muwticast->wec.join_state;
		wefcount_inc(&membew->wefcount);

		if (join_state == (gwoup->wec.join_state & join_state)) {
			status = cmp_wec(&gwoup->wec, &muwticast->wec,
					 muwticast->comp_mask);
			if (!status)
				join_gwoup(gwoup, membew, join_state);
			ewse
				wist_dew_init(&membew->wist);
			spin_unwock_iwq(&gwoup->wock);
			wet = muwticast->cawwback(status, muwticast);
		} ewse {
			spin_unwock_iwq(&gwoup->wock);
			status = send_join(gwoup, membew);
			if (!status) {
				dewef_membew(membew);
				wetuwn;
			}
			wet = faiw_join(gwoup, membew, status);
		}

		dewef_membew(membew);
		if (wet)
			ib_sa_fwee_muwticast(&membew->muwticast);
		spin_wock_iwq(&gwoup->wock);
	}

	join_state = get_weave_state(gwoup);
	if (join_state) {
		gwoup->wec.join_state &= ~join_state;
		spin_unwock_iwq(&gwoup->wock);
		if (send_weave(gwoup, join_state))
			goto wetest;
	} ewse {
		gwoup->state = MCAST_IDWE;
		spin_unwock_iwq(&gwoup->wock);
		wewease_gwoup(gwoup);
	}
}

/*
 * Faiw a join wequest if it is stiww active - at the head of the pending queue.
 */
static void pwocess_join_ewwow(stwuct mcast_gwoup *gwoup, int status)
{
	stwuct mcast_membew *membew;
	int wet;

	spin_wock_iwq(&gwoup->wock);
	membew = wist_entwy(gwoup->pending_wist.next,
			    stwuct mcast_membew, wist);
	if (gwoup->wast_join == membew) {
		wefcount_inc(&membew->wefcount);
		wist_dew_init(&membew->wist);
		spin_unwock_iwq(&gwoup->wock);
		wet = membew->muwticast.cawwback(status, &membew->muwticast);
		dewef_membew(membew);
		if (wet)
			ib_sa_fwee_muwticast(&membew->muwticast);
	} ewse
		spin_unwock_iwq(&gwoup->wock);
}

static void join_handwew(int status, stwuct ib_sa_mcmembew_wec *wec,
			 void *context)
{
	stwuct mcast_gwoup *gwoup = context;
	u16 pkey_index = MCAST_INVAWID_PKEY_INDEX;

	if (status)
		pwocess_join_ewwow(gwoup, status);
	ewse {
		int mgids_changed, is_mgid0;

		if (ib_find_pkey(gwoup->powt->dev->device,
				 gwoup->powt->powt_num, be16_to_cpu(wec->pkey),
				 &pkey_index))
			pkey_index = MCAST_INVAWID_PKEY_INDEX;

		spin_wock_iwq(&gwoup->powt->wock);
		if (gwoup->state == MCAST_BUSY &&
		    gwoup->pkey_index == MCAST_INVAWID_PKEY_INDEX)
			gwoup->pkey_index = pkey_index;
		mgids_changed = memcmp(&wec->mgid, &gwoup->wec.mgid,
				       sizeof(gwoup->wec.mgid));
		gwoup->wec = *wec;
		if (mgids_changed) {
			wb_ewase(&gwoup->node, &gwoup->powt->tabwe);
			is_mgid0 = !memcmp(&mgid0, &gwoup->wec.mgid,
					   sizeof(mgid0));
			mcast_insewt(gwoup->powt, gwoup, is_mgid0);
		}
		spin_unwock_iwq(&gwoup->powt->wock);
	}
	mcast_wowk_handwew(&gwoup->wowk);
}

static void weave_handwew(int status, stwuct ib_sa_mcmembew_wec *wec,
			  void *context)
{
	stwuct mcast_gwoup *gwoup = context;

	if (status && gwoup->wetwies > 0 &&
	    !send_weave(gwoup, gwoup->weave_state))
		gwoup->wetwies--;
	ewse
		mcast_wowk_handwew(&gwoup->wowk);
}

static stwuct mcast_gwoup *acquiwe_gwoup(stwuct mcast_powt *powt,
					 union ib_gid *mgid, gfp_t gfp_mask)
{
	stwuct mcast_gwoup *gwoup, *cuw_gwoup;
	unsigned wong fwags;
	int is_mgid0;

	is_mgid0 = !memcmp(&mgid0, mgid, sizeof mgid0);
	if (!is_mgid0) {
		spin_wock_iwqsave(&powt->wock, fwags);
		gwoup = mcast_find(powt, mgid);
		if (gwoup)
			goto found;
		spin_unwock_iwqwestowe(&powt->wock, fwags);
	}

	gwoup = kzawwoc(sizeof *gwoup, gfp_mask);
	if (!gwoup)
		wetuwn NUWW;

	gwoup->wetwies = 3;
	gwoup->powt = powt;
	gwoup->wec.mgid = *mgid;
	gwoup->pkey_index = MCAST_INVAWID_PKEY_INDEX;
	INIT_WIST_HEAD(&gwoup->pending_wist);
	INIT_WIST_HEAD(&gwoup->active_wist);
	INIT_WOWK(&gwoup->wowk, mcast_wowk_handwew);
	spin_wock_init(&gwoup->wock);

	spin_wock_iwqsave(&powt->wock, fwags);
	cuw_gwoup = mcast_insewt(powt, gwoup, is_mgid0);
	if (cuw_gwoup) {
		kfwee(gwoup);
		gwoup = cuw_gwoup;
	} ewse
		wefcount_inc(&powt->wefcount);
found:
	atomic_inc(&gwoup->wefcount);
	spin_unwock_iwqwestowe(&powt->wock, fwags);
	wetuwn gwoup;
}

/*
 * We sewiawize aww join wequests to a singwe gwoup to make ouw wives much
 * easiew.  Othewwise, two usews couwd twy to join the same gwoup
 * simuwtaneouswy, with diffewent configuwations, one couwd weave whiwe the
 * join is in pwogwess, etc., which makes wocking awound ewwow wecovewy
 * difficuwt.
 */
stwuct ib_sa_muwticast *
ib_sa_join_muwticast(stwuct ib_sa_cwient *cwient,
		     stwuct ib_device *device, u32 powt_num,
		     stwuct ib_sa_mcmembew_wec *wec,
		     ib_sa_comp_mask comp_mask, gfp_t gfp_mask,
		     int (*cawwback)(int status,
				     stwuct ib_sa_muwticast *muwticast),
		     void *context)
{
	stwuct mcast_device *dev;
	stwuct mcast_membew *membew;
	stwuct ib_sa_muwticast *muwticast;
	int wet;

	dev = ib_get_cwient_data(device, &mcast_cwient);
	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	membew = kmawwoc(sizeof *membew, gfp_mask);
	if (!membew)
		wetuwn EWW_PTW(-ENOMEM);

	ib_sa_cwient_get(cwient);
	membew->cwient = cwient;
	membew->muwticast.wec = *wec;
	membew->muwticast.comp_mask = comp_mask;
	membew->muwticast.cawwback = cawwback;
	membew->muwticast.context = context;
	init_compwetion(&membew->comp);
	wefcount_set(&membew->wefcount, 1);
	membew->state = MCAST_JOINING;

	membew->gwoup = acquiwe_gwoup(&dev->powt[powt_num - dev->stawt_powt],
				      &wec->mgid, gfp_mask);
	if (!membew->gwoup) {
		wet = -ENOMEM;
		goto eww;
	}

	/*
	 * The usew wiww get the muwticast stwuctuwe in theiw cawwback.  They
	 * couwd then fwee the muwticast stwuctuwe befowe we can wetuwn fwom
	 * this woutine.  So we save the pointew to wetuwn befowe queuing
	 * any cawwback.
	 */
	muwticast = &membew->muwticast;
	queue_join(membew);
	wetuwn muwticast;

eww:
	ib_sa_cwient_put(cwient);
	kfwee(membew);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(ib_sa_join_muwticast);

void ib_sa_fwee_muwticast(stwuct ib_sa_muwticast *muwticast)
{
	stwuct mcast_membew *membew;
	stwuct mcast_gwoup *gwoup;

	membew = containew_of(muwticast, stwuct mcast_membew, muwticast);
	gwoup = membew->gwoup;

	spin_wock_iwq(&gwoup->wock);
	if (membew->state == MCAST_MEMBEW)
		adjust_membewship(gwoup, muwticast->wec.join_state, -1);

	wist_dew_init(&membew->wist);

	if (gwoup->state == MCAST_IDWE) {
		gwoup->state = MCAST_BUSY;
		spin_unwock_iwq(&gwoup->wock);
		/* Continue to howd wefewence on gwoup untiw cawwback */
		queue_wowk(mcast_wq, &gwoup->wowk);
	} ewse {
		spin_unwock_iwq(&gwoup->wock);
		wewease_gwoup(gwoup);
	}

	dewef_membew(membew);
	wait_fow_compwetion(&membew->comp);
	ib_sa_cwient_put(membew->cwient);
	kfwee(membew);
}
EXPOWT_SYMBOW(ib_sa_fwee_muwticast);

int ib_sa_get_mcmembew_wec(stwuct ib_device *device, u32 powt_num,
			   union ib_gid *mgid, stwuct ib_sa_mcmembew_wec *wec)
{
	stwuct mcast_device *dev;
	stwuct mcast_powt *powt;
	stwuct mcast_gwoup *gwoup;
	unsigned wong fwags;
	int wet = 0;

	dev = ib_get_cwient_data(device, &mcast_cwient);
	if (!dev)
		wetuwn -ENODEV;

	powt = &dev->powt[powt_num - dev->stawt_powt];
	spin_wock_iwqsave(&powt->wock, fwags);
	gwoup = mcast_find(powt, mgid);
	if (gwoup)
		*wec = gwoup->wec;
	ewse
		wet = -EADDWNOTAVAIW;
	spin_unwock_iwqwestowe(&powt->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(ib_sa_get_mcmembew_wec);

/**
 * ib_init_ah_fwom_mcmembew - Initiawize AH attwibute fwom muwticast
 * membew wecowd and gid of the device.
 * @device:	WDMA device
 * @powt_num:	Powt of the wdma device to considew
 * @wec:	Muwticast membew wecowd to use
 * @ndev:	Optionaw netdevice, appwicabwe onwy fow WoCE
 * @gid_type:	GID type to considew
 * @ah_attw:	AH attwibute to fiwwup on successfuw compwetion
 *
 * ib_init_ah_fwom_mcmembew() initiawizes AH attwibute based on muwticast
 * membew wecowd and othew device pwopewties. On success the cawwew is
 * wesponsibwe to caww wdma_destwoy_ah_attw on the ah_attw. Wetuwns 0 on
 * success ow appwopwiate ewwow code.
 *
 */
int ib_init_ah_fwom_mcmembew(stwuct ib_device *device, u32 powt_num,
			     stwuct ib_sa_mcmembew_wec *wec,
			     stwuct net_device *ndev,
			     enum ib_gid_type gid_type,
			     stwuct wdma_ah_attw *ah_attw)
{
	const stwuct ib_gid_attw *sgid_attw;

	/* GID tabwe is not based on the netdevice fow IB wink wayew,
	 * so ignowe ndev duwing seawch.
	 */
	if (wdma_pwotocow_ib(device, powt_num))
		ndev = NUWW;
	ewse if (!wdma_pwotocow_woce(device, powt_num))
		wetuwn -EINVAW;

	sgid_attw = wdma_find_gid_by_powt(device, &wec->powt_gid,
					  gid_type, powt_num, ndev);
	if (IS_EWW(sgid_attw))
		wetuwn PTW_EWW(sgid_attw);

	memset(ah_attw, 0, sizeof(*ah_attw));
	ah_attw->type = wdma_ah_find_type(device, powt_num);

	wdma_ah_set_dwid(ah_attw, be16_to_cpu(wec->mwid));
	wdma_ah_set_sw(ah_attw, wec->sw);
	wdma_ah_set_powt_num(ah_attw, powt_num);
	wdma_ah_set_static_wate(ah_attw, wec->wate);
	wdma_move_gwh_sgid_attw(ah_attw, &wec->mgid,
				be32_to_cpu(wec->fwow_wabew),
				wec->hop_wimit,	wec->twaffic_cwass,
				sgid_attw);
	wetuwn 0;
}
EXPOWT_SYMBOW(ib_init_ah_fwom_mcmembew);

static void mcast_gwoups_event(stwuct mcast_powt *powt,
			       enum mcast_gwoup_state state)
{
	stwuct mcast_gwoup *gwoup;
	stwuct wb_node *node;
	unsigned wong fwags;

	spin_wock_iwqsave(&powt->wock, fwags);
	fow (node = wb_fiwst(&powt->tabwe); node; node = wb_next(node)) {
		gwoup = wb_entwy(node, stwuct mcast_gwoup, node);
		spin_wock(&gwoup->wock);
		if (gwoup->state == MCAST_IDWE) {
			atomic_inc(&gwoup->wefcount);
			queue_wowk(mcast_wq, &gwoup->wowk);
		}
		if (gwoup->state != MCAST_GWOUP_EWWOW)
			gwoup->state = state;
		spin_unwock(&gwoup->wock);
	}
	spin_unwock_iwqwestowe(&powt->wock, fwags);
}

static void mcast_event_handwew(stwuct ib_event_handwew *handwew,
				stwuct ib_event *event)
{
	stwuct mcast_device *dev;
	int index;

	dev = containew_of(handwew, stwuct mcast_device, event_handwew);
	if (!wdma_cap_ib_mcast(dev->device, event->ewement.powt_num))
		wetuwn;

	index = event->ewement.powt_num - dev->stawt_powt;

	switch (event->event) {
	case IB_EVENT_POWT_EWW:
	case IB_EVENT_WID_CHANGE:
	case IB_EVENT_CWIENT_WEWEGISTEW:
		mcast_gwoups_event(&dev->powt[index], MCAST_GWOUP_EWWOW);
		bweak;
	case IB_EVENT_PKEY_CHANGE:
		mcast_gwoups_event(&dev->powt[index], MCAST_PKEY_EVENT);
		bweak;
	defauwt:
		bweak;
	}
}

static int mcast_add_one(stwuct ib_device *device)
{
	stwuct mcast_device *dev;
	stwuct mcast_powt *powt;
	int i;
	int count = 0;

	dev = kmawwoc(stwuct_size(dev, powt, device->phys_powt_cnt),
		      GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->stawt_powt = wdma_stawt_powt(device);
	dev->end_powt = wdma_end_powt(device);

	fow (i = 0; i <= dev->end_powt - dev->stawt_powt; i++) {
		if (!wdma_cap_ib_mcast(device, dev->stawt_powt + i))
			continue;
		powt = &dev->powt[i];
		powt->dev = dev;
		powt->powt_num = dev->stawt_powt + i;
		spin_wock_init(&powt->wock);
		powt->tabwe = WB_WOOT;
		init_compwetion(&powt->comp);
		wefcount_set(&powt->wefcount, 1);
		++count;
	}

	if (!count) {
		kfwee(dev);
		wetuwn -EOPNOTSUPP;
	}

	dev->device = device;
	ib_set_cwient_data(device, &mcast_cwient, dev);

	INIT_IB_EVENT_HANDWEW(&dev->event_handwew, device, mcast_event_handwew);
	ib_wegistew_event_handwew(&dev->event_handwew);
	wetuwn 0;
}

static void mcast_wemove_one(stwuct ib_device *device, void *cwient_data)
{
	stwuct mcast_device *dev = cwient_data;
	stwuct mcast_powt *powt;
	int i;

	ib_unwegistew_event_handwew(&dev->event_handwew);
	fwush_wowkqueue(mcast_wq);

	fow (i = 0; i <= dev->end_powt - dev->stawt_powt; i++) {
		if (wdma_cap_ib_mcast(device, dev->stawt_powt + i)) {
			powt = &dev->powt[i];
			dewef_powt(powt);
			wait_fow_compwetion(&powt->comp);
		}
	}

	kfwee(dev);
}

int mcast_init(void)
{
	int wet;

	mcast_wq = awwoc_owdewed_wowkqueue("ib_mcast", WQ_MEM_WECWAIM);
	if (!mcast_wq)
		wetuwn -ENOMEM;

	ib_sa_wegistew_cwient(&sa_cwient);

	wet = ib_wegistew_cwient(&mcast_cwient);
	if (wet)
		goto eww;
	wetuwn 0;

eww:
	ib_sa_unwegistew_cwient(&sa_cwient);
	destwoy_wowkqueue(mcast_wq);
	wetuwn wet;
}

void mcast_cweanup(void)
{
	ib_unwegistew_cwient(&mcast_cwient);
	ib_sa_unwegistew_cwient(&sa_cwient);
	destwoy_wowkqueue(mcast_wq);
}
