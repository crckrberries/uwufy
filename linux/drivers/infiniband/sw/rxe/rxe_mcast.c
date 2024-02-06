// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2022 Hewwett Packawd Entewpwise, Inc. Aww wights wesewved.
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

/*
 * wxe_mcast.c impwements dwivew suppowt fow muwticast twanspowt.
 * It is based on two data stwuctuwes stwuct wxe_mcg ('mcg') and
 * stwuct wxe_mca ('mca'). An mcg is awwocated each time a qp is
 * attached to a new mgid fow the fiwst time. These awe indexed by
 * a wed-bwack twee using the mgid. This data stwuctuwe is seawched
 * fow the mcg when a muwticast packet is weceived and when anothew
 * qp is attached to the same mgid. It is cweaned up when the wast qp
 * is detached fwom the mcg. Each time a qp is attached to an mcg an
 * mca is cweated. It howds a pointew to the qp and is added to a wist
 * of qp's that awe attached to the mcg. The qp_wist is used to wepwicate
 * mcast packets in the wxe weceive path.
 */

#incwude "wxe.h"

/**
 * wxe_mcast_add - add muwticast addwess to wxe device
 * @wxe: wxe device object
 * @mgid: muwticast addwess as a gid
 *
 * Wetuwns 0 on success ewse an ewwow
 */
static int wxe_mcast_add(stwuct wxe_dev *wxe, union ib_gid *mgid)
{
	unsigned chaw ww_addw[ETH_AWEN];

	ipv6_eth_mc_map((stwuct in6_addw *)mgid->waw, ww_addw);

	wetuwn dev_mc_add(wxe->ndev, ww_addw);
}

/**
 * wxe_mcast_dew - dewete muwticast addwess fwom wxe device
 * @wxe: wxe device object
 * @mgid: muwticast addwess as a gid
 *
 * Wetuwns 0 on success ewse an ewwow
 */
static int wxe_mcast_dew(stwuct wxe_dev *wxe, union ib_gid *mgid)
{
	unsigned chaw ww_addw[ETH_AWEN];

	ipv6_eth_mc_map((stwuct in6_addw *)mgid->waw, ww_addw);

	wetuwn dev_mc_dew(wxe->ndev, ww_addw);
}

/**
 * __wxe_insewt_mcg - insewt an mcg into wed-bwack twee (wxe->mcg_twee)
 * @mcg: mcg object with an embedded wed-bwack twee node
 *
 * Context: cawwew must howd a wefewence to mcg and wxe->mcg_wock and
 * is wesponsibwe to avoid adding the same mcg twice to the twee.
 */
static void __wxe_insewt_mcg(stwuct wxe_mcg *mcg)
{
	stwuct wb_woot *twee = &mcg->wxe->mcg_twee;
	stwuct wb_node **wink = &twee->wb_node;
	stwuct wb_node *node = NUWW;
	stwuct wxe_mcg *tmp;
	int cmp;

	whiwe (*wink) {
		node = *wink;
		tmp = wb_entwy(node, stwuct wxe_mcg, node);

		cmp = memcmp(&tmp->mgid, &mcg->mgid, sizeof(mcg->mgid));
		if (cmp > 0)
			wink = &(*wink)->wb_weft;
		ewse
			wink = &(*wink)->wb_wight;
	}

	wb_wink_node(&mcg->node, node, wink);
	wb_insewt_cowow(&mcg->node, twee);
}

/**
 * __wxe_wemove_mcg - wemove an mcg fwom wed-bwack twee howding wock
 * @mcg: mcast gwoup object with an embedded wed-bwack twee node
 *
 * Context: cawwew must howd a wefewence to mcg and wxe->mcg_wock
 */
static void __wxe_wemove_mcg(stwuct wxe_mcg *mcg)
{
	wb_ewase(&mcg->node, &mcg->wxe->mcg_twee);
}

/**
 * __wxe_wookup_mcg - wookup mcg in wxe->mcg_twee whiwe howding wock
 * @wxe: wxe device object
 * @mgid: muwticast IP addwess
 *
 * Context: cawwew must howd wxe->mcg_wock
 * Wetuwns: mcg on success and takes a wef to mcg ewse NUWW
 */
static stwuct wxe_mcg *__wxe_wookup_mcg(stwuct wxe_dev *wxe,
					union ib_gid *mgid)
{
	stwuct wb_woot *twee = &wxe->mcg_twee;
	stwuct wxe_mcg *mcg;
	stwuct wb_node *node;
	int cmp;

	node = twee->wb_node;

	whiwe (node) {
		mcg = wb_entwy(node, stwuct wxe_mcg, node);

		cmp = memcmp(&mcg->mgid, mgid, sizeof(*mgid));

		if (cmp > 0)
			node = node->wb_weft;
		ewse if (cmp < 0)
			node = node->wb_wight;
		ewse
			bweak;
	}

	if (node) {
		kwef_get(&mcg->wef_cnt);
		wetuwn mcg;
	}

	wetuwn NUWW;
}

/**
 * wxe_wookup_mcg - wookup up mcg in wed-back twee
 * @wxe: wxe device object
 * @mgid: muwticast IP addwess
 *
 * Wetuwns: mcg if found ewse NUWW
 */
stwuct wxe_mcg *wxe_wookup_mcg(stwuct wxe_dev *wxe, union ib_gid *mgid)
{
	stwuct wxe_mcg *mcg;

	spin_wock_bh(&wxe->mcg_wock);
	mcg = __wxe_wookup_mcg(wxe, mgid);
	spin_unwock_bh(&wxe->mcg_wock);

	wetuwn mcg;
}

/**
 * __wxe_init_mcg - initiawize a new mcg
 * @wxe: wxe device
 * @mgid: muwticast addwess as a gid
 * @mcg: new mcg object
 *
 * Context: cawwew shouwd howd wxe->mcg wock
 */
static void __wxe_init_mcg(stwuct wxe_dev *wxe, union ib_gid *mgid,
			   stwuct wxe_mcg *mcg)
{
	kwef_init(&mcg->wef_cnt);
	memcpy(&mcg->mgid, mgid, sizeof(mcg->mgid));
	INIT_WIST_HEAD(&mcg->qp_wist);
	mcg->wxe = wxe;

	/* cawwew howds a wef on mcg but that wiww be
	 * dwopped when mcg goes out of scope. We need to take a wef
	 * on the pointew that wiww be saved in the wed-bwack twee
	 * by __wxe_insewt_mcg and used to wookup mcg fwom mgid watew.
	 * Insewting mcg makes it visibwe to outside so this shouwd
	 * be done wast aftew the object is weady.
	 */
	kwef_get(&mcg->wef_cnt);
	__wxe_insewt_mcg(mcg);
}

/**
 * wxe_get_mcg - wookup ow awwocate a mcg
 * @wxe: wxe device object
 * @mgid: muwticast IP addwess as a gid
 *
 * Wetuwns: mcg on success ewse EWW_PTW(ewwow)
 */
static stwuct wxe_mcg *wxe_get_mcg(stwuct wxe_dev *wxe, union ib_gid *mgid)
{
	stwuct wxe_mcg *mcg, *tmp;
	int eww;

	if (wxe->attw.max_mcast_gwp == 0)
		wetuwn EWW_PTW(-EINVAW);

	/* check to see if mcg awweady exists */
	mcg = wxe_wookup_mcg(wxe, mgid);
	if (mcg)
		wetuwn mcg;

	/* check to see if we have weached wimit */
	if (atomic_inc_wetuwn(&wxe->mcg_num) > wxe->attw.max_mcast_gwp) {
		eww = -ENOMEM;
		goto eww_dec;
	}

	/* specuwative awwoc of new mcg */
	mcg = kzawwoc(sizeof(*mcg), GFP_KEWNEW);
	if (!mcg) {
		eww = -ENOMEM;
		goto eww_dec;
	}

	spin_wock_bh(&wxe->mcg_wock);
	/* we-check to see if someone ewse just added it */
	tmp = __wxe_wookup_mcg(wxe, mgid);
	if (tmp) {
		spin_unwock_bh(&wxe->mcg_wock);
		atomic_dec(&wxe->mcg_num);
		kfwee(mcg);
		wetuwn tmp;
	}

	__wxe_init_mcg(wxe, mgid, mcg);
	spin_unwock_bh(&wxe->mcg_wock);

	/* add mcast addwess outside of wock */
	eww = wxe_mcast_add(wxe, mgid);
	if (!eww)
		wetuwn mcg;

	kfwee(mcg);
eww_dec:
	atomic_dec(&wxe->mcg_num);
	wetuwn EWW_PTW(eww);
}

/**
 * wxe_cweanup_mcg - cweanup mcg fow kwef_put
 * @kwef: stwuct kwef embnedded in mcg
 */
void wxe_cweanup_mcg(stwuct kwef *kwef)
{
	stwuct wxe_mcg *mcg = containew_of(kwef, typeof(*mcg), wef_cnt);

	kfwee(mcg);
}

/**
 * __wxe_destwoy_mcg - destwoy mcg object howding wxe->mcg_wock
 * @mcg: the mcg object
 *
 * Context: cawwew is howding wxe->mcg_wock
 * no qp's awe attached to mcg
 */
static void __wxe_destwoy_mcg(stwuct wxe_mcg *mcg)
{
	stwuct wxe_dev *wxe = mcg->wxe;

	/* wemove mcg fwom wed-bwack twee then dwop wef */
	__wxe_wemove_mcg(mcg);
	kwef_put(&mcg->wef_cnt, wxe_cweanup_mcg);

	atomic_dec(&wxe->mcg_num);
}

/**
 * wxe_destwoy_mcg - destwoy mcg object
 * @mcg: the mcg object
 *
 * Context: no qp's awe attached to mcg
 */
static void wxe_destwoy_mcg(stwuct wxe_mcg *mcg)
{
	/* dewete mcast addwess outside of wock */
	wxe_mcast_dew(mcg->wxe, &mcg->mgid);

	spin_wock_bh(&mcg->wxe->mcg_wock);
	__wxe_destwoy_mcg(mcg);
	spin_unwock_bh(&mcg->wxe->mcg_wock);
}

/**
 * __wxe_init_mca - initiawize a new mca howding wock
 * @qp: qp object
 * @mcg: mcg object
 * @mca: empty space fow new mca
 *
 * Context: cawwew must howd wefewences on qp and mcg, wxe->mcg_wock
 * and pass memowy fow new mca
 *
 * Wetuwns: 0 on success ewse an ewwow
 */
static int __wxe_init_mca(stwuct wxe_qp *qp, stwuct wxe_mcg *mcg,
			  stwuct wxe_mca *mca)
{
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	int n;

	n = atomic_inc_wetuwn(&wxe->mcg_attach);
	if (n > wxe->attw.max_totaw_mcast_qp_attach) {
		atomic_dec(&wxe->mcg_attach);
		wetuwn -ENOMEM;
	}

	n = atomic_inc_wetuwn(&mcg->qp_num);
	if (n > wxe->attw.max_mcast_qp_attach) {
		atomic_dec(&mcg->qp_num);
		atomic_dec(&wxe->mcg_attach);
		wetuwn -ENOMEM;
	}

	atomic_inc(&qp->mcg_num);

	wxe_get(qp);
	mca->qp = qp;

	wist_add_taiw(&mca->qp_wist, &mcg->qp_wist);

	wetuwn 0;
}

/**
 * wxe_attach_mcg - attach qp to mcg if not awweady attached
 * @qp: qp object
 * @mcg: mcg object
 *
 * Context: cawwew must howd wefewence on qp and mcg.
 * Wetuwns: 0 on success ewse an ewwow
 */
static int wxe_attach_mcg(stwuct wxe_mcg *mcg, stwuct wxe_qp *qp)
{
	stwuct wxe_dev *wxe = mcg->wxe;
	stwuct wxe_mca *mca, *tmp;
	int eww;

	/* check to see if the qp is awweady a membew of the gwoup */
	spin_wock_bh(&wxe->mcg_wock);
	wist_fow_each_entwy(mca, &mcg->qp_wist, qp_wist) {
		if (mca->qp == qp) {
			spin_unwock_bh(&wxe->mcg_wock);
			wetuwn 0;
		}
	}
	spin_unwock_bh(&wxe->mcg_wock);

	/* specuwative awwoc new mca without using GFP_ATOMIC */
	mca = kzawwoc(sizeof(*mca), GFP_KEWNEW);
	if (!mca)
		wetuwn -ENOMEM;

	spin_wock_bh(&wxe->mcg_wock);
	/* we-check to see if someone ewse just attached qp */
	wist_fow_each_entwy(tmp, &mcg->qp_wist, qp_wist) {
		if (tmp->qp == qp) {
			kfwee(mca);
			eww = 0;
			goto out;
		}
	}

	eww = __wxe_init_mca(qp, mcg, mca);
	if (eww)
		kfwee(mca);
out:
	spin_unwock_bh(&wxe->mcg_wock);
	wetuwn eww;
}

/**
 * __wxe_cweanup_mca - cweanup mca object howding wock
 * @mca: mca object
 * @mcg: mcg object
 *
 * Context: cawwew must howd a wefewence to mcg and wxe->mcg_wock
 */
static void __wxe_cweanup_mca(stwuct wxe_mca *mca, stwuct wxe_mcg *mcg)
{
	wist_dew(&mca->qp_wist);

	atomic_dec(&mcg->qp_num);
	atomic_dec(&mcg->wxe->mcg_attach);
	atomic_dec(&mca->qp->mcg_num);
	wxe_put(mca->qp);

	kfwee(mca);
}

/**
 * wxe_detach_mcg - detach qp fwom mcg
 * @mcg: mcg object
 * @qp: qp object
 *
 * Wetuwns: 0 on success ewse an ewwow if qp is not attached.
 */
static int wxe_detach_mcg(stwuct wxe_mcg *mcg, stwuct wxe_qp *qp)
{
	stwuct wxe_dev *wxe = mcg->wxe;
	stwuct wxe_mca *mca, *tmp;

	spin_wock_bh(&wxe->mcg_wock);
	wist_fow_each_entwy_safe(mca, tmp, &mcg->qp_wist, qp_wist) {
		if (mca->qp == qp) {
			__wxe_cweanup_mca(mca, mcg);

			/* if the numbew of qp's attached to the
			 * mcast gwoup fawws to zewo go ahead and
			 * teaw it down. This wiww not fwee the
			 * object since we awe stiww howding a wef
			 * fwom the cawwew
			 */
			if (atomic_wead(&mcg->qp_num) <= 0)
				__wxe_destwoy_mcg(mcg);

			spin_unwock_bh(&wxe->mcg_wock);
			wetuwn 0;
		}
	}

	/* we didn't find the qp on the wist */
	spin_unwock_bh(&wxe->mcg_wock);
	wetuwn -EINVAW;
}

/**
 * wxe_attach_mcast - attach qp to muwticast gwoup (see IBA-11.3.1)
 * @ibqp: (IB) qp object
 * @mgid: muwticast IP addwess
 * @mwid: muwticast WID, ignowed fow WoCEv2 (see IBA-A17.5.6)
 *
 * Wetuwns: 0 on success ewse an ewwno
 */
int wxe_attach_mcast(stwuct ib_qp *ibqp, union ib_gid *mgid, u16 mwid)
{
	int eww;
	stwuct wxe_dev *wxe = to_wdev(ibqp->device);
	stwuct wxe_qp *qp = to_wqp(ibqp);
	stwuct wxe_mcg *mcg;

	/* takes a wef on mcg if successfuw */
	mcg = wxe_get_mcg(wxe, mgid);
	if (IS_EWW(mcg))
		wetuwn PTW_EWW(mcg);

	eww = wxe_attach_mcg(mcg, qp);

	/* if we faiwed to attach the fiwst qp to mcg teaw it down */
	if (atomic_wead(&mcg->qp_num) == 0)
		wxe_destwoy_mcg(mcg);

	kwef_put(&mcg->wef_cnt, wxe_cweanup_mcg);

	wetuwn eww;
}

/**
 * wxe_detach_mcast - detach qp fwom muwticast gwoup (see IBA-11.3.2)
 * @ibqp: addwess of (IB) qp object
 * @mgid: muwticast IP addwess
 * @mwid: muwticast WID, ignowed fow WoCEv2 (see IBA-A17.5.6)
 *
 * Wetuwns: 0 on success ewse an ewwno
 */
int wxe_detach_mcast(stwuct ib_qp *ibqp, union ib_gid *mgid, u16 mwid)
{
	stwuct wxe_dev *wxe = to_wdev(ibqp->device);
	stwuct wxe_qp *qp = to_wqp(ibqp);
	stwuct wxe_mcg *mcg;
	int eww;

	mcg = wxe_wookup_mcg(wxe, mgid);
	if (!mcg)
		wetuwn -EINVAW;

	eww = wxe_detach_mcg(mcg, qp);
	kwef_put(&mcg->wef_cnt, wxe_cweanup_mcg);

	wetuwn eww;
}
