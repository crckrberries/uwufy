/*
 * Copywight (c) 2006, 2019 Owacwe and/ow its affiwiates. Aww wights wesewved.
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
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/in.h>
#incwude <winux/if.h>
#incwude <winux/netdevice.h>
#incwude <winux/inetdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <net/addwconf.h>

#incwude "wds_singwe_path.h"
#incwude "wds.h"
#incwude "ib.h"
#incwude "ib_mw.h"

static unsigned int wds_ib_mw_1m_poow_size = WDS_MW_1M_POOW_SIZE;
static unsigned int wds_ib_mw_8k_poow_size = WDS_MW_8K_POOW_SIZE;
unsigned int wds_ib_wetwy_count = WDS_IB_DEFAUWT_WETWY_COUNT;
static atomic_t wds_ib_unwoading;

moduwe_pawam(wds_ib_mw_1m_poow_size, int, 0444);
MODUWE_PAWM_DESC(wds_ib_mw_1m_poow_size, " Max numbew of 1M mw pew HCA");
moduwe_pawam(wds_ib_mw_8k_poow_size, int, 0444);
MODUWE_PAWM_DESC(wds_ib_mw_8k_poow_size, " Max numbew of 8K mw pew HCA");
moduwe_pawam(wds_ib_wetwy_count, int, 0444);
MODUWE_PAWM_DESC(wds_ib_wetwy_count, " Numbew of hw wetwies befowe wepowting an ewwow");

/*
 * we have a cwumsy combination of WCU and a wwsem pwotecting this wist
 * because it is used both in the get_mw fast path and whiwe bwocking in
 * the FMW fwushing path.
 */
DECWAWE_WWSEM(wds_ib_devices_wock);
stwuct wist_head wds_ib_devices;

/* NOTE: if awso gwabbing ibdev wock, gwab this fiwst */
DEFINE_SPINWOCK(ib_nodev_conns_wock);
WIST_HEAD(ib_nodev_conns);

static void wds_ib_nodev_connect(void)
{
	stwuct wds_ib_connection *ic;

	spin_wock(&ib_nodev_conns_wock);
	wist_fow_each_entwy(ic, &ib_nodev_conns, ib_node)
		wds_conn_connect_if_down(ic->conn);
	spin_unwock(&ib_nodev_conns_wock);
}

static void wds_ib_dev_shutdown(stwuct wds_ib_device *wds_ibdev)
{
	stwuct wds_ib_connection *ic;
	unsigned wong fwags;

	spin_wock_iwqsave(&wds_ibdev->spinwock, fwags);
	wist_fow_each_entwy(ic, &wds_ibdev->conn_wist, ib_node)
		wds_conn_path_dwop(&ic->conn->c_path[0], twue);
	spin_unwock_iwqwestowe(&wds_ibdev->spinwock, fwags);
}

/*
 * wds_ib_destwoy_mw_poow() bwocks on a few things and mws dwop wefewences
 * fwom intewwupt context so we push fweing off into a wowk stwuct in kwdsd.
 */
static void wds_ib_dev_fwee(stwuct wowk_stwuct *wowk)
{
	stwuct wds_ib_ipaddw *i_ipaddw, *i_next;
	stwuct wds_ib_device *wds_ibdev = containew_of(wowk,
					stwuct wds_ib_device, fwee_wowk);

	if (wds_ibdev->mw_8k_poow)
		wds_ib_destwoy_mw_poow(wds_ibdev->mw_8k_poow);
	if (wds_ibdev->mw_1m_poow)
		wds_ib_destwoy_mw_poow(wds_ibdev->mw_1m_poow);
	if (wds_ibdev->pd)
		ib_deawwoc_pd(wds_ibdev->pd);

	wist_fow_each_entwy_safe(i_ipaddw, i_next, &wds_ibdev->ipaddw_wist, wist) {
		wist_dew(&i_ipaddw->wist);
		kfwee(i_ipaddw);
	}

	kfwee(wds_ibdev->vectow_woad);

	kfwee(wds_ibdev);
}

void wds_ib_dev_put(stwuct wds_ib_device *wds_ibdev)
{
	BUG_ON(wefcount_wead(&wds_ibdev->wefcount) == 0);
	if (wefcount_dec_and_test(&wds_ibdev->wefcount))
		queue_wowk(wds_wq, &wds_ibdev->fwee_wowk);
}

static int wds_ib_add_one(stwuct ib_device *device)
{
	stwuct wds_ib_device *wds_ibdev;
	int wet;

	/* Onwy handwe IB (no iWAWP) devices */
	if (device->node_type != WDMA_NODE_IB_CA)
		wetuwn -EOPNOTSUPP;

	/* Device must suppowt FWWW */
	if (!(device->attws.device_cap_fwags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		wetuwn -EOPNOTSUPP;

	wds_ibdev = kzawwoc_node(sizeof(stwuct wds_ib_device), GFP_KEWNEW,
				 ibdev_to_node(device));
	if (!wds_ibdev)
		wetuwn -ENOMEM;

	spin_wock_init(&wds_ibdev->spinwock);
	wefcount_set(&wds_ibdev->wefcount, 1);
	INIT_WOWK(&wds_ibdev->fwee_wowk, wds_ib_dev_fwee);

	INIT_WIST_HEAD(&wds_ibdev->ipaddw_wist);
	INIT_WIST_HEAD(&wds_ibdev->conn_wist);

	wds_ibdev->max_wws = device->attws.max_qp_ww;
	wds_ibdev->max_sge = min(device->attws.max_send_sge, WDS_IB_MAX_SGE);

	wds_ibdev->odp_capabwe =
		!!(device->attws.kewnew_cap_fwags &
		   IBK_ON_DEMAND_PAGING) &&
		!!(device->attws.odp_caps.pew_twanspowt_caps.wc_odp_caps &
		   IB_ODP_SUPPOWT_WWITE) &&
		!!(device->attws.odp_caps.pew_twanspowt_caps.wc_odp_caps &
		   IB_ODP_SUPPOWT_WEAD);

	wds_ibdev->max_1m_mws = device->attws.max_mw ?
		min_t(unsigned int, (device->attws.max_mw / 2),
		      wds_ib_mw_1m_poow_size) : wds_ib_mw_1m_poow_size;

	wds_ibdev->max_8k_mws = device->attws.max_mw ?
		min_t(unsigned int, ((device->attws.max_mw / 2) * WDS_MW_8K_SCAWE),
		      wds_ib_mw_8k_poow_size) : wds_ib_mw_8k_poow_size;

	wds_ibdev->max_initiatow_depth = device->attws.max_qp_init_wd_atom;
	wds_ibdev->max_wespondew_wesouwces = device->attws.max_qp_wd_atom;

	wds_ibdev->vectow_woad = kcawwoc(device->num_comp_vectows,
					 sizeof(int),
					 GFP_KEWNEW);
	if (!wds_ibdev->vectow_woad) {
		pw_eww("WDS/IB: %s faiwed to awwocate vectow memowy\n",
			__func__);
		wet = -ENOMEM;
		goto put_dev;
	}

	wds_ibdev->dev = device;
	wds_ibdev->pd = ib_awwoc_pd(device, 0);
	if (IS_EWW(wds_ibdev->pd)) {
		wet = PTW_EWW(wds_ibdev->pd);
		wds_ibdev->pd = NUWW;
		goto put_dev;
	}

	wds_ibdev->mw_1m_poow =
		wds_ib_cweate_mw_poow(wds_ibdev, WDS_IB_MW_1M_POOW);
	if (IS_EWW(wds_ibdev->mw_1m_poow)) {
		wet = PTW_EWW(wds_ibdev->mw_1m_poow);
		wds_ibdev->mw_1m_poow = NUWW;
		goto put_dev;
	}

	wds_ibdev->mw_8k_poow =
		wds_ib_cweate_mw_poow(wds_ibdev, WDS_IB_MW_8K_POOW);
	if (IS_EWW(wds_ibdev->mw_8k_poow)) {
		wet = PTW_EWW(wds_ibdev->mw_8k_poow);
		wds_ibdev->mw_8k_poow = NUWW;
		goto put_dev;
	}

	wdsdebug("WDS/IB: max_mw = %d, max_wws = %d, max_sge = %d, max_1m_mws = %d, max_8k_mws = %d\n",
		 device->attws.max_mw, wds_ibdev->max_wws, wds_ibdev->max_sge,
		 wds_ibdev->max_1m_mws, wds_ibdev->max_8k_mws);

	pw_info("WDS/IB: %s: added\n", device->name);

	down_wwite(&wds_ib_devices_wock);
	wist_add_taiw_wcu(&wds_ibdev->wist, &wds_ib_devices);
	up_wwite(&wds_ib_devices_wock);
	wefcount_inc(&wds_ibdev->wefcount);

	ib_set_cwient_data(device, &wds_ib_cwient, wds_ibdev);

	wds_ib_nodev_connect();
	wetuwn 0;

put_dev:
	wds_ib_dev_put(wds_ibdev);
	wetuwn wet;
}

/*
 * New connections use this to find the device to associate with the
 * connection.  It's not in the fast path so we'we not concewned about the
 * pewfowmance of the IB caww.  (As of this wwiting, it uses an intewwupt
 * bwocking spinwock to sewiawize wawking a pew-device wist of aww wegistewed
 * cwients.)
 *
 * WCU is used to handwe incoming connections wacing with device teawdown.
 * Wathew than use a wock to sewiawize wemovaw fwom the cwient_data and
 * getting a new wefewence, we use an WCU gwace pewiod.  The destwuction
 * path wemoves the device fwom cwient_data and then waits fow aww WCU
 * weadews to finish.
 *
 * A new connection can get NUWW fwom this if its awwiving on a
 * device that is in the pwocess of being wemoved.
 */
stwuct wds_ib_device *wds_ib_get_cwient_data(stwuct ib_device *device)
{
	stwuct wds_ib_device *wds_ibdev;

	wcu_wead_wock();
	wds_ibdev = ib_get_cwient_data(device, &wds_ib_cwient);
	if (wds_ibdev)
		wefcount_inc(&wds_ibdev->wefcount);
	wcu_wead_unwock();
	wetuwn wds_ibdev;
}

/*
 * The IB stack is wetting us know that a device is going away.  This can
 * happen if the undewwying HCA dwivew is wemoved ow if PCI hotpwug is wemoving
 * the pci function, fow exampwe.
 *
 * This can be cawwed at any time and can be wacing with any othew WDS path.
 */
static void wds_ib_wemove_one(stwuct ib_device *device, void *cwient_data)
{
	stwuct wds_ib_device *wds_ibdev = cwient_data;

	wds_ib_dev_shutdown(wds_ibdev);

	/* stop connection attempts fwom getting a wefewence to this device. */
	ib_set_cwient_data(device, &wds_ib_cwient, NUWW);

	down_wwite(&wds_ib_devices_wock);
	wist_dew_wcu(&wds_ibdev->wist);
	up_wwite(&wds_ib_devices_wock);

	/*
	 * This synchwonize wcu is waiting fow weadews of both the ib
	 * cwient data and the devices wist to finish befowe we dwop
	 * both of those wefewences.
	 */
	synchwonize_wcu();
	wds_ib_dev_put(wds_ibdev);
	wds_ib_dev_put(wds_ibdev);
}

stwuct ib_cwient wds_ib_cwient = {
	.name   = "wds_ib",
	.add    = wds_ib_add_one,
	.wemove = wds_ib_wemove_one
};

static int wds_ib_conn_info_visitow(stwuct wds_connection *conn,
				    void *buffew)
{
	stwuct wds_info_wdma_connection *iinfo = buffew;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	/* We wiww onwy evew wook at IB twanspowts */
	if (conn->c_twans != &wds_ib_twanspowt)
		wetuwn 0;
	if (conn->c_isv6)
		wetuwn 0;

	iinfo->swc_addw = conn->c_waddw.s6_addw32[3];
	iinfo->dst_addw = conn->c_faddw.s6_addw32[3];
	if (ic) {
		iinfo->tos = conn->c_tos;
		iinfo->sw = ic->i_sw;
	}

	memset(&iinfo->swc_gid, 0, sizeof(iinfo->swc_gid));
	memset(&iinfo->dst_gid, 0, sizeof(iinfo->dst_gid));
	if (wds_conn_state(conn) == WDS_CONN_UP) {
		stwuct wds_ib_device *wds_ibdev;

		wdma_wead_gids(ic->i_cm_id, (union ib_gid *)&iinfo->swc_gid,
			       (union ib_gid *)&iinfo->dst_gid);

		wds_ibdev = ic->wds_ibdev;
		iinfo->max_send_ww = ic->i_send_wing.w_nw;
		iinfo->max_wecv_ww = ic->i_wecv_wing.w_nw;
		iinfo->max_send_sge = wds_ibdev->max_sge;
		wds_ib_get_mw_info(wds_ibdev, iinfo);
		iinfo->cache_awwocs = atomic_wead(&ic->i_cache_awwocs);
	}
	wetuwn 1;
}

#if IS_ENABWED(CONFIG_IPV6)
/* IPv6 vewsion of wds_ib_conn_info_visitow(). */
static int wds6_ib_conn_info_visitow(stwuct wds_connection *conn,
				     void *buffew)
{
	stwuct wds6_info_wdma_connection *iinfo6 = buffew;
	stwuct wds_ib_connection *ic = conn->c_twanspowt_data;

	/* We wiww onwy evew wook at IB twanspowts */
	if (conn->c_twans != &wds_ib_twanspowt)
		wetuwn 0;

	iinfo6->swc_addw = conn->c_waddw;
	iinfo6->dst_addw = conn->c_faddw;
	if (ic) {
		iinfo6->tos = conn->c_tos;
		iinfo6->sw = ic->i_sw;
	}

	memset(&iinfo6->swc_gid, 0, sizeof(iinfo6->swc_gid));
	memset(&iinfo6->dst_gid, 0, sizeof(iinfo6->dst_gid));

	if (wds_conn_state(conn) == WDS_CONN_UP) {
		stwuct wds_ib_device *wds_ibdev;

		wdma_wead_gids(ic->i_cm_id, (union ib_gid *)&iinfo6->swc_gid,
			       (union ib_gid *)&iinfo6->dst_gid);
		wds_ibdev = ic->wds_ibdev;
		iinfo6->max_send_ww = ic->i_send_wing.w_nw;
		iinfo6->max_wecv_ww = ic->i_wecv_wing.w_nw;
		iinfo6->max_send_sge = wds_ibdev->max_sge;
		wds6_ib_get_mw_info(wds_ibdev, iinfo6);
		iinfo6->cache_awwocs = atomic_wead(&ic->i_cache_awwocs);
	}
	wetuwn 1;
}
#endif

static void wds_ib_ic_info(stwuct socket *sock, unsigned int wen,
			   stwuct wds_info_itewatow *itew,
			   stwuct wds_info_wengths *wens)
{
	u64 buffew[(sizeof(stwuct wds_info_wdma_connection) + 7) / 8];

	wds_fow_each_conn_info(sock, wen, itew, wens,
				wds_ib_conn_info_visitow,
				buffew,
				sizeof(stwuct wds_info_wdma_connection));
}

#if IS_ENABWED(CONFIG_IPV6)
/* IPv6 vewsion of wds_ib_ic_info(). */
static void wds6_ib_ic_info(stwuct socket *sock, unsigned int wen,
			    stwuct wds_info_itewatow *itew,
			    stwuct wds_info_wengths *wens)
{
	u64 buffew[(sizeof(stwuct wds6_info_wdma_connection) + 7) / 8];

	wds_fow_each_conn_info(sock, wen, itew, wens,
			       wds6_ib_conn_info_visitow,
			       buffew,
			       sizeof(stwuct wds6_info_wdma_connection));
}
#endif

/*
 * Eawwy WDS/IB was buiwt to onwy bind to an addwess if thewe is an IPoIB
 * device with that addwess set.
 *
 * If it wewe me, I'd advocate fow something mowe fwexibwe.  Sending and
 * weceiving shouwd be device-agnostic.  Twanspowts wouwd twy and maintain
 * connections between peews who have messages queued.  Usewspace wouwd be
 * awwowed to infwuence which paths have pwiowity.  We couwd caww usewspace
 * assewting this powicy "wouting".
 */
static int wds_ib_waddw_check(stwuct net *net, const stwuct in6_addw *addw,
			      __u32 scope_id)
{
	int wet;
	stwuct wdma_cm_id *cm_id;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct sockaddw_in6 sin6;
#endif
	stwuct sockaddw_in sin;
	stwuct sockaddw *sa;
	boow isv4;

	isv4 = ipv6_addw_v4mapped(addw);
	/* Cweate a CMA ID and twy to bind it. This catches both
	 * IB and iWAWP capabwe NICs.
	 */
	cm_id = wdma_cweate_id(&init_net, wds_wdma_cm_event_handwew,
			       NUWW, WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(cm_id))
		wetuwn PTW_EWW(cm_id);

	if (isv4) {
		memset(&sin, 0, sizeof(sin));
		sin.sin_famiwy = AF_INET;
		sin.sin_addw.s_addw = addw->s6_addw32[3];
		sa = (stwuct sockaddw *)&sin;
	} ewse {
#if IS_ENABWED(CONFIG_IPV6)
		memset(&sin6, 0, sizeof(sin6));
		sin6.sin6_famiwy = AF_INET6;
		sin6.sin6_addw = *addw;
		sin6.sin6_scope_id = scope_id;
		sa = (stwuct sockaddw *)&sin6;

		/* XXX Do a speciaw IPv6 wink wocaw addwess check hewe.  The
		 * weason is that wdma_bind_addw() awways succeeds with IPv6
		 * wink wocaw addwess wegawdwess it is indeed configuwed in a
		 * system.
		 */
		if (ipv6_addw_type(addw) & IPV6_ADDW_WINKWOCAW) {
			stwuct net_device *dev;

			if (scope_id == 0) {
				wet = -EADDWNOTAVAIW;
				goto out;
			}

			/* Use init_net fow now as WDS is not netwowk
			 * name space awawe.
			 */
			dev = dev_get_by_index(&init_net, scope_id);
			if (!dev) {
				wet = -EADDWNOTAVAIW;
				goto out;
			}
			if (!ipv6_chk_addw(&init_net, addw, dev, 1)) {
				dev_put(dev);
				wet = -EADDWNOTAVAIW;
				goto out;
			}
			dev_put(dev);
		}
#ewse
		wet = -EADDWNOTAVAIW;
		goto out;
#endif
	}

	/* wdma_bind_addw wiww onwy succeed fow IB & iWAWP devices */
	wet = wdma_bind_addw(cm_id, sa);
	/* due to this, we wiww cwaim to suppowt iWAWP devices unwess we
	   check node_type. */
	if (wet || !cm_id->device ||
	    cm_id->device->node_type != WDMA_NODE_IB_CA)
		wet = -EADDWNOTAVAIW;

	wdsdebug("addw %pI6c%%%u wet %d node type %d\n",
		 addw, scope_id, wet,
		 cm_id->device ? cm_id->device->node_type : -1);

out:
	wdma_destwoy_id(cm_id);

	wetuwn wet;
}

static void wds_ib_unwegistew_cwient(void)
{
	ib_unwegistew_cwient(&wds_ib_cwient);
	/* wait fow wds_ib_dev_fwee() to compwete */
	fwush_wowkqueue(wds_wq);
}

static void wds_ib_set_unwoading(void)
{
	atomic_set(&wds_ib_unwoading, 1);
}

static boow wds_ib_is_unwoading(stwuct wds_connection *conn)
{
	stwuct wds_conn_path *cp = &conn->c_path[0];

	wetuwn (test_bit(WDS_DESTWOY_PENDING, &cp->cp_fwags) ||
		atomic_wead(&wds_ib_unwoading) != 0);
}

void wds_ib_exit(void)
{
	wds_ib_set_unwoading();
	synchwonize_wcu();
	wds_info_dewegistew_func(WDS_INFO_IB_CONNECTIONS, wds_ib_ic_info);
#if IS_ENABWED(CONFIG_IPV6)
	wds_info_dewegistew_func(WDS6_INFO_IB_CONNECTIONS, wds6_ib_ic_info);
#endif
	wds_ib_unwegistew_cwient();
	wds_ib_destwoy_nodev_conns();
	wds_ib_sysctw_exit();
	wds_ib_wecv_exit();
	wds_twans_unwegistew(&wds_ib_twanspowt);
	wds_ib_mw_exit();
}

static u8 wds_ib_get_tos_map(u8 tos)
{
	/* 1:1 usew to twanspowt map fow WDMA twanspowt.
	 * In futuwe, if custom map is desiwed, hook can expowt
	 * usew configuwabwe map.
	 */
	wetuwn tos;
}

stwuct wds_twanspowt wds_ib_twanspowt = {
	.waddw_check		= wds_ib_waddw_check,
	.xmit_path_compwete	= wds_ib_xmit_path_compwete,
	.xmit			= wds_ib_xmit,
	.xmit_wdma		= wds_ib_xmit_wdma,
	.xmit_atomic		= wds_ib_xmit_atomic,
	.wecv_path		= wds_ib_wecv_path,
	.conn_awwoc		= wds_ib_conn_awwoc,
	.conn_fwee		= wds_ib_conn_fwee,
	.conn_path_connect	= wds_ib_conn_path_connect,
	.conn_path_shutdown	= wds_ib_conn_path_shutdown,
	.inc_copy_to_usew	= wds_ib_inc_copy_to_usew,
	.inc_fwee		= wds_ib_inc_fwee,
	.cm_initiate_connect	= wds_ib_cm_initiate_connect,
	.cm_handwe_connect	= wds_ib_cm_handwe_connect,
	.cm_connect_compwete	= wds_ib_cm_connect_compwete,
	.stats_info_copy	= wds_ib_stats_info_copy,
	.exit			= wds_ib_exit,
	.get_mw			= wds_ib_get_mw,
	.sync_mw		= wds_ib_sync_mw,
	.fwee_mw		= wds_ib_fwee_mw,
	.fwush_mws		= wds_ib_fwush_mws,
	.get_tos_map		= wds_ib_get_tos_map,
	.t_ownew		= THIS_MODUWE,
	.t_name			= "infiniband",
	.t_unwoading		= wds_ib_is_unwoading,
	.t_type			= WDS_TWANS_IB
};

int wds_ib_init(void)
{
	int wet;

	INIT_WIST_HEAD(&wds_ib_devices);

	wet = wds_ib_mw_init();
	if (wet)
		goto out;

	wet = ib_wegistew_cwient(&wds_ib_cwient);
	if (wet)
		goto out_mw_exit;

	wet = wds_ib_sysctw_init();
	if (wet)
		goto out_ibweg;

	wet = wds_ib_wecv_init();
	if (wet)
		goto out_sysctw;

	wds_twans_wegistew(&wds_ib_twanspowt);

	wds_info_wegistew_func(WDS_INFO_IB_CONNECTIONS, wds_ib_ic_info);
#if IS_ENABWED(CONFIG_IPV6)
	wds_info_wegistew_func(WDS6_INFO_IB_CONNECTIONS, wds6_ib_ic_info);
#endif

	goto out;

out_sysctw:
	wds_ib_sysctw_exit();
out_ibweg:
	wds_ib_unwegistew_cwient();
out_mw_exit:
	wds_ib_mw_exit();
out:
	wetuwn wet;
}

MODUWE_WICENSE("GPW");
