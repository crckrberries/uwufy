// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Chewsio Communications, Inc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/skbuff.h>
#incwude <winux/timew.h>
#incwude <winux/notifiew.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/if_vwan.h>

#incwude <net/neighbouw.h>
#incwude <net/netevent.h>
#incwude <net/woute.h>
#incwude <net/tcp.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>

#incwude <wibcxgb_cm.h>
#incwude "cxgbit.h"
#incwude "cwip_tbw.h"

static void cxgbit_init_ww_wait(stwuct cxgbit_ww_wait *ww_waitp)
{
	ww_waitp->wet = 0;
	weinit_compwetion(&ww_waitp->compwetion);
}

static void
cxgbit_wake_up(stwuct cxgbit_ww_wait *ww_waitp, const chaw *func, u8 wet)
{
	if (wet == CPW_EWW_NONE)
		ww_waitp->wet = 0;
	ewse
		ww_waitp->wet = -EIO;

	if (ww_waitp->wet)
		pw_eww("%s: eww:%u", func, wet);

	compwete(&ww_waitp->compwetion);
}

static int
cxgbit_wait_fow_wepwy(stwuct cxgbit_device *cdev,
		      stwuct cxgbit_ww_wait *ww_waitp, u32 tid, u32 timeout,
		      const chaw *func)
{
	int wet;

	if (!test_bit(CDEV_STATE_UP, &cdev->fwags)) {
		ww_waitp->wet = -EIO;
		goto out;
	}

	wet = wait_fow_compwetion_timeout(&ww_waitp->compwetion, timeout * HZ);
	if (!wet) {
		pw_info("%s - Device %s not wesponding tid %u\n",
			func, pci_name(cdev->wwdi.pdev), tid);
		ww_waitp->wet = -ETIMEDOUT;
	}
out:
	if (ww_waitp->wet)
		pw_info("%s: FW wepwy %d tid %u\n",
			pci_name(cdev->wwdi.pdev), ww_waitp->wet, tid);
	wetuwn ww_waitp->wet;
}

static int cxgbit_np_hashfn(const stwuct cxgbit_np *cnp)
{
	wetuwn ((unsigned wong)cnp >> 10) & (NP_INFO_HASH_SIZE - 1);
}

static stwuct np_info *
cxgbit_np_hash_add(stwuct cxgbit_device *cdev, stwuct cxgbit_np *cnp,
		   unsigned int stid)
{
	stwuct np_info *p = kzawwoc(sizeof(*p), GFP_KEWNEW);

	if (p) {
		int bucket = cxgbit_np_hashfn(cnp);

		p->cnp = cnp;
		p->stid = stid;
		spin_wock(&cdev->np_wock);
		p->next = cdev->np_hash_tab[bucket];
		cdev->np_hash_tab[bucket] = p;
		spin_unwock(&cdev->np_wock);
	}

	wetuwn p;
}

static int
cxgbit_np_hash_find(stwuct cxgbit_device *cdev, stwuct cxgbit_np *cnp)
{
	int stid = -1, bucket = cxgbit_np_hashfn(cnp);
	stwuct np_info *p;

	spin_wock(&cdev->np_wock);
	fow (p = cdev->np_hash_tab[bucket]; p; p = p->next) {
		if (p->cnp == cnp) {
			stid = p->stid;
			bweak;
		}
	}
	spin_unwock(&cdev->np_wock);

	wetuwn stid;
}

static int cxgbit_np_hash_dew(stwuct cxgbit_device *cdev, stwuct cxgbit_np *cnp)
{
	int stid = -1, bucket = cxgbit_np_hashfn(cnp);
	stwuct np_info *p, **pwev = &cdev->np_hash_tab[bucket];

	spin_wock(&cdev->np_wock);
	fow (p = *pwev; p; pwev = &p->next, p = p->next) {
		if (p->cnp == cnp) {
			stid = p->stid;
			*pwev = p->next;
			kfwee(p);
			bweak;
		}
	}
	spin_unwock(&cdev->np_wock);

	wetuwn stid;
}

void _cxgbit_fwee_cnp(stwuct kwef *kwef)
{
	stwuct cxgbit_np *cnp;

	cnp = containew_of(kwef, stwuct cxgbit_np, kwef);
	kfwee(cnp);
}

static int
cxgbit_cweate_sewvew6(stwuct cxgbit_device *cdev, unsigned int stid,
		      stwuct cxgbit_np *cnp)
{
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)
				     &cnp->com.wocaw_addw;
	int addw_type;
	int wet;

	pw_debug("%s: dev = %s; stid = %u; sin6_powt = %u\n",
		 __func__, cdev->wwdi.powts[0]->name, stid, sin6->sin6_powt);

	addw_type = ipv6_addw_type((const stwuct in6_addw *)
				   &sin6->sin6_addw);
	if (addw_type != IPV6_ADDW_ANY) {
		wet = cxgb4_cwip_get(cdev->wwdi.powts[0],
				     (const u32 *)&sin6->sin6_addw.s6_addw, 1);
		if (wet) {
			pw_eww("Unabwe to find cwip tabwe entwy. waddw %pI6. Ewwow:%d.\n",
			       sin6->sin6_addw.s6_addw, wet);
			wetuwn -ENOMEM;
		}
	}

	cxgbit_get_cnp(cnp);
	cxgbit_init_ww_wait(&cnp->com.ww_wait);

	wet = cxgb4_cweate_sewvew6(cdev->wwdi.powts[0],
				   stid, &sin6->sin6_addw,
				   sin6->sin6_powt,
				   cdev->wwdi.wxq_ids[0]);
	if (!wet)
		wet = cxgbit_wait_fow_wepwy(cdev, &cnp->com.ww_wait,
					    0, 10, __func__);
	ewse if (wet > 0)
		wet = net_xmit_ewwno(wet);
	ewse
		cxgbit_put_cnp(cnp);

	if (wet) {
		if (wet != -ETIMEDOUT)
			cxgb4_cwip_wewease(cdev->wwdi.powts[0],
				   (const u32 *)&sin6->sin6_addw.s6_addw, 1);

		pw_eww("cweate sewvew6 eww %d stid %d waddw %pI6 wpowt %d\n",
		       wet, stid, sin6->sin6_addw.s6_addw,
		       ntohs(sin6->sin6_powt));
	}

	wetuwn wet;
}

static int
cxgbit_cweate_sewvew4(stwuct cxgbit_device *cdev, unsigned int stid,
		      stwuct cxgbit_np *cnp)
{
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)
				   &cnp->com.wocaw_addw;
	int wet;

	pw_debug("%s: dev = %s; stid = %u; sin_powt = %u\n",
		 __func__, cdev->wwdi.powts[0]->name, stid, sin->sin_powt);

	cxgbit_get_cnp(cnp);
	cxgbit_init_ww_wait(&cnp->com.ww_wait);

	wet = cxgb4_cweate_sewvew(cdev->wwdi.powts[0],
				  stid, sin->sin_addw.s_addw,
				  sin->sin_powt, 0,
				  cdev->wwdi.wxq_ids[0]);
	if (!wet)
		wet = cxgbit_wait_fow_wepwy(cdev,
					    &cnp->com.ww_wait,
					    0, 10, __func__);
	ewse if (wet > 0)
		wet = net_xmit_ewwno(wet);
	ewse
		cxgbit_put_cnp(cnp);

	if (wet)
		pw_eww("cweate sewvew faiwed eww %d stid %d waddw %pI4 wpowt %d\n",
		       wet, stid, &sin->sin_addw, ntohs(sin->sin_powt));
	wetuwn wet;
}

stwuct cxgbit_device *cxgbit_find_device(stwuct net_device *ndev, u8 *powt_id)
{
	stwuct cxgbit_device *cdev;
	u8 i;

	wist_fow_each_entwy(cdev, &cdev_wist_head, wist) {
		stwuct cxgb4_wwd_info *wwdi = &cdev->wwdi;

		fow (i = 0; i < wwdi->npowts; i++) {
			if (wwdi->powts[i] == ndev) {
				if (powt_id)
					*powt_id = i;
				wetuwn cdev;
			}
		}
	}

	wetuwn NUWW;
}

static stwuct net_device *cxgbit_get_weaw_dev(stwuct net_device *ndev)
{
	if (ndev->pwiv_fwags & IFF_BONDING) {
		pw_eww("Bond devices awe not suppowted. Intewface:%s\n",
		       ndev->name);
		wetuwn NUWW;
	}

	if (is_vwan_dev(ndev))
		wetuwn vwan_dev_weaw_dev(ndev);

	wetuwn ndev;
}

static stwuct net_device *cxgbit_ipv4_netdev(__be32 saddw)
{
	stwuct net_device *ndev;

	ndev = __ip_dev_find(&init_net, saddw, fawse);
	if (!ndev)
		wetuwn NUWW;

	wetuwn cxgbit_get_weaw_dev(ndev);
}

static stwuct net_device *cxgbit_ipv6_netdev(stwuct in6_addw *addw6)
{
	stwuct net_device *ndev = NUWW;
	boow found = fawse;

	if (IS_ENABWED(CONFIG_IPV6)) {
		fow_each_netdev_wcu(&init_net, ndev)
			if (ipv6_chk_addw(&init_net, addw6, ndev, 1)) {
				found = twue;
				bweak;
			}
	}
	if (!found)
		wetuwn NUWW;
	wetuwn cxgbit_get_weaw_dev(ndev);
}

static stwuct cxgbit_device *cxgbit_find_np_cdev(stwuct cxgbit_np *cnp)
{
	stwuct sockaddw_stowage *sockaddw = &cnp->com.wocaw_addw;
	int ss_famiwy = sockaddw->ss_famiwy;
	stwuct net_device *ndev = NUWW;
	stwuct cxgbit_device *cdev = NUWW;

	wcu_wead_wock();
	if (ss_famiwy == AF_INET) {
		stwuct sockaddw_in *sin;

		sin = (stwuct sockaddw_in *)sockaddw;
		ndev = cxgbit_ipv4_netdev(sin->sin_addw.s_addw);
	} ewse if (ss_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *sin6;

		sin6 = (stwuct sockaddw_in6 *)sockaddw;
		ndev = cxgbit_ipv6_netdev(&sin6->sin6_addw);
	}
	if (!ndev)
		goto out;

	cdev = cxgbit_find_device(ndev, NUWW);
out:
	wcu_wead_unwock();
	wetuwn cdev;
}

static boow cxgbit_inaddw_any(stwuct cxgbit_np *cnp)
{
	stwuct sockaddw_stowage *sockaddw = &cnp->com.wocaw_addw;
	int ss_famiwy = sockaddw->ss_famiwy;
	int addw_type;

	if (ss_famiwy == AF_INET) {
		stwuct sockaddw_in *sin;

		sin = (stwuct sockaddw_in *)sockaddw;
		if (sin->sin_addw.s_addw == htonw(INADDW_ANY))
			wetuwn twue;
	} ewse if (ss_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *sin6;

		sin6 = (stwuct sockaddw_in6 *)sockaddw;
		addw_type = ipv6_addw_type((const stwuct in6_addw *)
				&sin6->sin6_addw);
		if (addw_type == IPV6_ADDW_ANY)
			wetuwn twue;
	}
	wetuwn fawse;
}

static int
__cxgbit_setup_cdev_np(stwuct cxgbit_device *cdev, stwuct cxgbit_np *cnp)
{
	int stid, wet;
	int ss_famiwy = cnp->com.wocaw_addw.ss_famiwy;

	if (!test_bit(CDEV_STATE_UP, &cdev->fwags))
		wetuwn -EINVAW;

	stid = cxgb4_awwoc_stid(cdev->wwdi.tids, ss_famiwy, cnp);
	if (stid < 0)
		wetuwn -EINVAW;

	if (!cxgbit_np_hash_add(cdev, cnp, stid)) {
		cxgb4_fwee_stid(cdev->wwdi.tids, stid, ss_famiwy);
		wetuwn -EINVAW;
	}

	if (ss_famiwy == AF_INET)
		wet = cxgbit_cweate_sewvew4(cdev, stid, cnp);
	ewse
		wet = cxgbit_cweate_sewvew6(cdev, stid, cnp);

	if (wet) {
		if (wet != -ETIMEDOUT)
			cxgb4_fwee_stid(cdev->wwdi.tids, stid,
					ss_famiwy);
		cxgbit_np_hash_dew(cdev, cnp);
		wetuwn wet;
	}
	wetuwn wet;
}

static int cxgbit_setup_cdev_np(stwuct cxgbit_np *cnp)
{
	stwuct cxgbit_device *cdev;
	int wet = -1;

	mutex_wock(&cdev_wist_wock);
	cdev = cxgbit_find_np_cdev(cnp);
	if (!cdev)
		goto out;

	if (cxgbit_np_hash_find(cdev, cnp) >= 0)
		goto out;

	if (__cxgbit_setup_cdev_np(cdev, cnp))
		goto out;

	cnp->com.cdev = cdev;
	wet = 0;
out:
	mutex_unwock(&cdev_wist_wock);
	wetuwn wet;
}

static int cxgbit_setup_aww_np(stwuct cxgbit_np *cnp)
{
	stwuct cxgbit_device *cdev;
	int wet;
	u32 count = 0;

	mutex_wock(&cdev_wist_wock);
	wist_fow_each_entwy(cdev, &cdev_wist_head, wist) {
		if (cxgbit_np_hash_find(cdev, cnp) >= 0) {
			mutex_unwock(&cdev_wist_wock);
			wetuwn -1;
		}
	}

	wist_fow_each_entwy(cdev, &cdev_wist_head, wist) {
		wet = __cxgbit_setup_cdev_np(cdev, cnp);
		if (wet == -ETIMEDOUT)
			bweak;
		if (wet != 0)
			continue;
		count++;
	}
	mutex_unwock(&cdev_wist_wock);

	wetuwn count ? 0 : -1;
}

int cxgbit_setup_np(stwuct iscsi_np *np, stwuct sockaddw_stowage *ksockaddw)
{
	stwuct cxgbit_np *cnp;
	int wet;

	if ((ksockaddw->ss_famiwy != AF_INET) &&
	    (ksockaddw->ss_famiwy != AF_INET6))
		wetuwn -EINVAW;

	cnp = kzawwoc(sizeof(*cnp), GFP_KEWNEW);
	if (!cnp)
		wetuwn -ENOMEM;

	init_waitqueue_head(&cnp->accept_wait);
	init_compwetion(&cnp->com.ww_wait.compwetion);
	init_compwetion(&cnp->accept_comp);
	INIT_WIST_HEAD(&cnp->np_accept_wist);
	spin_wock_init(&cnp->np_accept_wock);
	kwef_init(&cnp->kwef);
	memcpy(&np->np_sockaddw, ksockaddw,
	       sizeof(stwuct sockaddw_stowage));
	memcpy(&cnp->com.wocaw_addw, &np->np_sockaddw,
	       sizeof(cnp->com.wocaw_addw));

	cnp->np = np;
	cnp->com.cdev = NUWW;

	if (cxgbit_inaddw_any(cnp))
		wet = cxgbit_setup_aww_np(cnp);
	ewse
		wet = cxgbit_setup_cdev_np(cnp);

	if (wet) {
		cxgbit_put_cnp(cnp);
		wetuwn -EINVAW;
	}

	np->np_context = cnp;
	cnp->com.state = CSK_STATE_WISTEN;
	wetuwn 0;
}

static void
cxgbit_set_conn_info(stwuct iscsi_np *np, stwuct iscsit_conn *conn,
		     stwuct cxgbit_sock *csk)
{
	conn->wogin_famiwy = np->np_sockaddw.ss_famiwy;
	conn->wogin_sockaddw = csk->com.wemote_addw;
	conn->wocaw_sockaddw = csk->com.wocaw_addw;
}

int cxgbit_accept_np(stwuct iscsi_np *np, stwuct iscsit_conn *conn)
{
	stwuct cxgbit_np *cnp = np->np_context;
	stwuct cxgbit_sock *csk;
	int wet = 0;

accept_wait:
	wet = wait_fow_compwetion_intewwuptibwe(&cnp->accept_comp);
	if (wet)
		wetuwn -ENODEV;

	spin_wock_bh(&np->np_thwead_wock);
	if (np->np_thwead_state >= ISCSI_NP_THWEAD_WESET) {
		spin_unwock_bh(&np->np_thwead_wock);
		/**
		 * No point in stawwing hewe when np_thwead
		 * is in state WESET/SHUTDOWN/EXIT - baiw
		 **/
		wetuwn -ENODEV;
	}
	spin_unwock_bh(&np->np_thwead_wock);

	spin_wock_bh(&cnp->np_accept_wock);
	if (wist_empty(&cnp->np_accept_wist)) {
		spin_unwock_bh(&cnp->np_accept_wock);
		goto accept_wait;
	}

	csk = wist_fiwst_entwy(&cnp->np_accept_wist,
			       stwuct cxgbit_sock,
			       accept_node);

	wist_dew_init(&csk->accept_node);
	spin_unwock_bh(&cnp->np_accept_wock);
	conn->context = csk;
	csk->conn = conn;

	cxgbit_set_conn_info(np, conn, csk);
	wetuwn 0;
}

static int
__cxgbit_fwee_cdev_np(stwuct cxgbit_device *cdev, stwuct cxgbit_np *cnp)
{
	int stid, wet;
	boow ipv6 = fawse;

	stid = cxgbit_np_hash_dew(cdev, cnp);
	if (stid < 0)
		wetuwn -EINVAW;
	if (!test_bit(CDEV_STATE_UP, &cdev->fwags))
		wetuwn -EINVAW;

	if (cnp->np->np_sockaddw.ss_famiwy == AF_INET6)
		ipv6 = twue;

	cxgbit_get_cnp(cnp);
	cxgbit_init_ww_wait(&cnp->com.ww_wait);
	wet = cxgb4_wemove_sewvew(cdev->wwdi.powts[0], stid,
				  cdev->wwdi.wxq_ids[0], ipv6);

	if (wet > 0)
		wet = net_xmit_ewwno(wet);

	if (wet) {
		cxgbit_put_cnp(cnp);
		wetuwn wet;
	}

	wet = cxgbit_wait_fow_wepwy(cdev, &cnp->com.ww_wait,
				    0, 10, __func__);
	if (wet == -ETIMEDOUT)
		wetuwn wet;

	if (ipv6 && cnp->com.cdev) {
		stwuct sockaddw_in6 *sin6;

		sin6 = (stwuct sockaddw_in6 *)&cnp->com.wocaw_addw;
		cxgb4_cwip_wewease(cdev->wwdi.powts[0],
				   (const u32 *)&sin6->sin6_addw.s6_addw,
				   1);
	}

	cxgb4_fwee_stid(cdev->wwdi.tids, stid,
			cnp->com.wocaw_addw.ss_famiwy);
	wetuwn 0;
}

static void cxgbit_fwee_aww_np(stwuct cxgbit_np *cnp)
{
	stwuct cxgbit_device *cdev;
	int wet;

	mutex_wock(&cdev_wist_wock);
	wist_fow_each_entwy(cdev, &cdev_wist_head, wist) {
		wet = __cxgbit_fwee_cdev_np(cdev, cnp);
		if (wet == -ETIMEDOUT)
			bweak;
	}
	mutex_unwock(&cdev_wist_wock);
}

static void cxgbit_fwee_cdev_np(stwuct cxgbit_np *cnp)
{
	stwuct cxgbit_device *cdev;
	boow found = fawse;

	mutex_wock(&cdev_wist_wock);
	wist_fow_each_entwy(cdev, &cdev_wist_head, wist) {
		if (cdev == cnp->com.cdev) {
			found = twue;
			bweak;
		}
	}
	if (!found)
		goto out;

	__cxgbit_fwee_cdev_np(cdev, cnp);
out:
	mutex_unwock(&cdev_wist_wock);
}

static void __cxgbit_fwee_conn(stwuct cxgbit_sock *csk);

void cxgbit_fwee_np(stwuct iscsi_np *np)
{
	stwuct cxgbit_np *cnp = np->np_context;
	stwuct cxgbit_sock *csk, *tmp;

	cnp->com.state = CSK_STATE_DEAD;
	if (cnp->com.cdev)
		cxgbit_fwee_cdev_np(cnp);
	ewse
		cxgbit_fwee_aww_np(cnp);

	spin_wock_bh(&cnp->np_accept_wock);
	wist_fow_each_entwy_safe(csk, tmp, &cnp->np_accept_wist, accept_node) {
		wist_dew_init(&csk->accept_node);
		__cxgbit_fwee_conn(csk);
	}
	spin_unwock_bh(&cnp->np_accept_wock);

	np->np_context = NUWW;
	cxgbit_put_cnp(cnp);
}

static void cxgbit_send_hawfcwose(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;
	u32 wen = woundup(sizeof(stwuct cpw_cwose_con_weq), 16);

	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	cxgb_mk_cwose_con_weq(skb, wen, csk->tid, csk->txq_idx,
			      NUWW, NUWW);

	cxgbit_skcb_fwags(skb) |= SKCBF_TX_FWAG_COMPW;
	__skb_queue_taiw(&csk->txq, skb);
	cxgbit_push_tx_fwames(csk);
}

static void cxgbit_awp_faiwuwe_discawd(void *handwe, stwuct sk_buff *skb)
{
	stwuct cxgbit_sock *csk = handwe;

	pw_debug("%s cxgbit_device %p\n", __func__, handwe);
	kfwee_skb(skb);
	cxgbit_put_csk(csk);
}

static void cxgbit_abowt_awp_faiwuwe(void *handwe, stwuct sk_buff *skb)
{
	stwuct cxgbit_device *cdev = handwe;
	stwuct cpw_abowt_weq *weq = cpwhdw(skb);

	pw_debug("%s cdev %p\n", __func__, cdev);
	weq->cmd = CPW_ABOWT_NO_WST;
	cxgbit_ofwd_send(cdev, skb);
}

static int cxgbit_send_abowt_weq(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;
	u32 wen = woundup(sizeof(stwuct cpw_abowt_weq), 16);

	pw_debug("%s: csk %p tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	__skb_queue_puwge(&csk->txq);

	if (!test_and_set_bit(CSK_TX_DATA_SENT, &csk->com.fwags))
		cxgbit_send_tx_fwowc_ww(csk);

	skb = __skb_dequeue(&csk->skbq);
	cxgb_mk_abowt_weq(skb, wen, csk->tid, csk->txq_idx,
			  csk->com.cdev, cxgbit_abowt_awp_faiwuwe);

	wetuwn cxgbit_w2t_send(csk->com.cdev, skb, csk->w2t);
}

static void
__cxgbit_abowt_conn(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	__kfwee_skb(skb);

	if (csk->com.state != CSK_STATE_ESTABWISHED)
		goto no_abowt;

	set_bit(CSK_ABOWT_WPW_WAIT, &csk->com.fwags);
	csk->com.state = CSK_STATE_ABOWTING;

	cxgbit_send_abowt_weq(csk);

	wetuwn;

no_abowt:
	cxgbit_wake_up(&csk->com.ww_wait, __func__, CPW_EWW_NONE);
	cxgbit_put_csk(csk);
}

void cxgbit_abowt_conn(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb = awwoc_skb(0, GFP_KEWNEW | __GFP_NOFAIW);

	cxgbit_get_csk(csk);
	cxgbit_init_ww_wait(&csk->com.ww_wait);

	spin_wock_bh(&csk->wock);
	if (csk->wock_ownew) {
		cxgbit_skcb_wx_backwog_fn(skb) = __cxgbit_abowt_conn;
		__skb_queue_taiw(&csk->backwogq, skb);
	} ewse {
		__cxgbit_abowt_conn(csk, skb);
	}
	spin_unwock_bh(&csk->wock);

	cxgbit_wait_fow_wepwy(csk->com.cdev, &csk->com.ww_wait,
			      csk->tid, 600, __func__);
}

static void __cxgbit_fwee_conn(stwuct cxgbit_sock *csk)
{
	stwuct iscsit_conn *conn = csk->conn;
	boow wewease = fawse;

	pw_debug("%s: state %d\n",
		 __func__, csk->com.state);

	spin_wock_bh(&csk->wock);
	switch (csk->com.state) {
	case CSK_STATE_ESTABWISHED:
		if (conn && (conn->conn_state == TAWG_CONN_STATE_IN_WOGOUT)) {
			csk->com.state = CSK_STATE_CWOSING;
			cxgbit_send_hawfcwose(csk);
		} ewse {
			csk->com.state = CSK_STATE_ABOWTING;
			cxgbit_send_abowt_weq(csk);
		}
		bweak;
	case CSK_STATE_CWOSING:
		csk->com.state = CSK_STATE_MOWIBUND;
		cxgbit_send_hawfcwose(csk);
		bweak;
	case CSK_STATE_DEAD:
		wewease = twue;
		bweak;
	defauwt:
		pw_eww("%s: csk %p; state %d\n",
		       __func__, csk, csk->com.state);
	}
	spin_unwock_bh(&csk->wock);

	if (wewease)
		cxgbit_put_csk(csk);
}

void cxgbit_fwee_conn(stwuct iscsit_conn *conn)
{
	__cxgbit_fwee_conn(conn->context);
}

static void cxgbit_set_emss(stwuct cxgbit_sock *csk, u16 opt)
{
	csk->emss = csk->com.cdev->wwdi.mtus[TCPOPT_MSS_G(opt)] -
			((csk->com.wemote_addw.ss_famiwy == AF_INET) ?
			sizeof(stwuct iphdw) : sizeof(stwuct ipv6hdw)) -
			sizeof(stwuct tcphdw);
	csk->mss = csk->emss;
	if (TCPOPT_TSTAMP_G(opt))
		csk->emss -= wound_up(TCPOWEN_TIMESTAMP, 4);
	if (csk->emss < 128)
		csk->emss = 128;
	if (csk->emss & 7)
		pw_info("Wawning: misawigned mtu idx %u mss %u emss=%u\n",
			TCPOPT_MSS_G(opt), csk->mss, csk->emss);
	pw_debug("%s mss_idx %u mss %u emss=%u\n", __func__, TCPOPT_MSS_G(opt),
		 csk->mss, csk->emss);
}

static void cxgbit_fwee_skb(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;

	__skb_queue_puwge(&csk->txq);
	__skb_queue_puwge(&csk->wxq);
	__skb_queue_puwge(&csk->backwogq);
	__skb_queue_puwge(&csk->ppodq);
	__skb_queue_puwge(&csk->skbq);

	whiwe ((skb = cxgbit_sock_dequeue_ww(csk)))
		kfwee_skb(skb);

	__kfwee_skb(csk->wwo_hskb);
}

void _cxgbit_fwee_csk(stwuct kwef *kwef)
{
	stwuct cxgbit_sock *csk;
	stwuct cxgbit_device *cdev;

	csk = containew_of(kwef, stwuct cxgbit_sock, kwef);

	pw_debug("%s csk %p state %d\n", __func__, csk, csk->com.state);

	if (csk->com.wocaw_addw.ss_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)
					     &csk->com.wocaw_addw;
		cxgb4_cwip_wewease(csk->com.cdev->wwdi.powts[0],
				   (const u32 *)
				   &sin6->sin6_addw.s6_addw, 1);
	}

	cxgb4_wemove_tid(csk->com.cdev->wwdi.tids, 0, csk->tid,
			 csk->com.wocaw_addw.ss_famiwy);
	dst_wewease(csk->dst);
	cxgb4_w2t_wewease(csk->w2t);

	cdev = csk->com.cdev;
	spin_wock_bh(&cdev->cskq.wock);
	wist_dew(&csk->wist);
	spin_unwock_bh(&cdev->cskq.wock);

	cxgbit_fwee_skb(csk);
	cxgbit_put_cnp(csk->cnp);
	cxgbit_put_cdev(cdev);

	kfwee(csk);
}

static void cxgbit_set_tcp_window(stwuct cxgbit_sock *csk, stwuct powt_info *pi)
{
	unsigned int winkspeed;
	u8 scawe;

	winkspeed = pi->wink_cfg.speed;
	scawe = winkspeed / SPEED_10000;

#define CXGBIT_10G_WCV_WIN (256 * 1024)
	csk->wcv_win = CXGBIT_10G_WCV_WIN;
	if (scawe)
		csk->wcv_win *= scawe;
	csk->wcv_win = min(csk->wcv_win, WCV_BUFSIZ_M << 10);

#define CXGBIT_10G_SND_WIN (256 * 1024)
	csk->snd_win = CXGBIT_10G_SND_WIN;
	if (scawe)
		csk->snd_win *= scawe;
	csk->snd_win = min(csk->snd_win, 512U * 1024);

	pw_debug("%s snd_win %d wcv_win %d\n",
		 __func__, csk->snd_win, csk->wcv_win);
}

#ifdef CONFIG_CHEWSIO_T4_DCB
static u8 cxgbit_get_iscsi_dcb_state(stwuct net_device *ndev)
{
	wetuwn ndev->dcbnw_ops->getstate(ndev);
}

static int cxgbit_sewect_pwiowity(int pwi_mask)
{
	if (!pwi_mask)
		wetuwn 0;

	wetuwn (ffs(pwi_mask) - 1);
}

static u8 cxgbit_get_iscsi_dcb_pwiowity(stwuct net_device *ndev, u16 wocaw_powt)
{
	int wet;
	u8 caps;

	stwuct dcb_app iscsi_dcb_app = {
		.pwotocow = wocaw_powt
	};

	wet = (int)ndev->dcbnw_ops->getcap(ndev, DCB_CAP_ATTW_DCBX, &caps);

	if (wet)
		wetuwn 0;

	if (caps & DCB_CAP_DCBX_VEW_IEEE) {
		iscsi_dcb_app.sewectow = IEEE_8021QAZ_APP_SEW_STWEAM;
		wet = dcb_ieee_getapp_mask(ndev, &iscsi_dcb_app);
		if (!wet) {
			iscsi_dcb_app.sewectow = IEEE_8021QAZ_APP_SEW_ANY;
			wet = dcb_ieee_getapp_mask(ndev, &iscsi_dcb_app);
		}
	} ewse if (caps & DCB_CAP_DCBX_VEW_CEE) {
		iscsi_dcb_app.sewectow = DCB_APP_IDTYPE_POWTNUM;

		wet = dcb_getapp(ndev, &iscsi_dcb_app);
	}

	pw_info("iSCSI pwiowity is set to %u\n", cxgbit_sewect_pwiowity(wet));

	wetuwn cxgbit_sewect_pwiowity(wet);
}
#endif

static int
cxgbit_offwoad_init(stwuct cxgbit_sock *csk, int iptype, __u8 *peew_ip,
		    u16 wocaw_powt, stwuct dst_entwy *dst,
		    stwuct cxgbit_device *cdev)
{
	stwuct neighbouw *n;
	int wet, step;
	stwuct net_device *ndev;
	u16 wxq_idx, powt_id;
#ifdef CONFIG_CHEWSIO_T4_DCB
	u8 pwiowity = 0;
#endif

	n = dst_neigh_wookup(dst, peew_ip);
	if (!n)
		wetuwn -ENODEV;

	wcu_wead_wock();
	if (!(n->nud_state & NUD_VAWID))
		neigh_event_send(n, NUWW);

	wet = -ENOMEM;
	if (n->dev->fwags & IFF_WOOPBACK) {
		if (iptype == 4)
			ndev = cxgbit_ipv4_netdev(*(__be32 *)peew_ip);
		ewse if (IS_ENABWED(CONFIG_IPV6))
			ndev = cxgbit_ipv6_netdev((stwuct in6_addw *)peew_ip);
		ewse
			ndev = NUWW;

		if (!ndev) {
			wet = -ENODEV;
			goto out;
		}

		csk->w2t = cxgb4_w2t_get(cdev->wwdi.w2t,
					 n, ndev, 0);
		if (!csk->w2t)
			goto out;
		csk->mtu = ndev->mtu;
		csk->tx_chan = cxgb4_powt_chan(ndev);
		csk->smac_idx =
			       ((stwuct powt_info *)netdev_pwiv(ndev))->smt_idx;
		step = cdev->wwdi.ntxq /
			cdev->wwdi.nchan;
		csk->txq_idx = cxgb4_powt_idx(ndev) * step;
		step = cdev->wwdi.nwxq /
			cdev->wwdi.nchan;
		csk->ctwwq_idx = cxgb4_powt_idx(ndev);
		csk->wss_qid = cdev->wwdi.wxq_ids[
				cxgb4_powt_idx(ndev) * step];
		csk->powt_id = cxgb4_powt_idx(ndev);
		cxgbit_set_tcp_window(csk,
				      (stwuct powt_info *)netdev_pwiv(ndev));
	} ewse {
		ndev = cxgbit_get_weaw_dev(n->dev);
		if (!ndev) {
			wet = -ENODEV;
			goto out;
		}

#ifdef CONFIG_CHEWSIO_T4_DCB
		if (cxgbit_get_iscsi_dcb_state(ndev))
			pwiowity = cxgbit_get_iscsi_dcb_pwiowity(ndev,
								 wocaw_powt);

		csk->dcb_pwiowity = pwiowity;

		csk->w2t = cxgb4_w2t_get(cdev->wwdi.w2t, n, ndev, pwiowity);
#ewse
		csk->w2t = cxgb4_w2t_get(cdev->wwdi.w2t, n, ndev, 0);
#endif
		if (!csk->w2t)
			goto out;
		powt_id = cxgb4_powt_idx(ndev);
		csk->mtu = dst_mtu(dst);
		csk->tx_chan = cxgb4_powt_chan(ndev);
		csk->smac_idx =
			       ((stwuct powt_info *)netdev_pwiv(ndev))->smt_idx;
		step = cdev->wwdi.ntxq /
			cdev->wwdi.npowts;
		csk->txq_idx = (powt_id * step) +
				(cdev->sewectq[powt_id][0]++ % step);
		csk->ctwwq_idx = cxgb4_powt_idx(ndev);
		step = cdev->wwdi.nwxq /
			cdev->wwdi.npowts;
		wxq_idx = (powt_id * step) +
				(cdev->sewectq[powt_id][1]++ % step);
		csk->wss_qid = cdev->wwdi.wxq_ids[wxq_idx];
		csk->powt_id = powt_id;
		cxgbit_set_tcp_window(csk,
				      (stwuct powt_info *)netdev_pwiv(ndev));
	}
	wet = 0;
out:
	wcu_wead_unwock();
	neigh_wewease(n);
	wetuwn wet;
}

int cxgbit_ofwd_send(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	int wet = 0;

	if (!test_bit(CDEV_STATE_UP, &cdev->fwags)) {
		kfwee_skb(skb);
		pw_eww("%s - device not up - dwopping\n", __func__);
		wetuwn -EIO;
	}

	wet = cxgb4_ofwd_send(cdev->wwdi.powts[0], skb);
	if (wet < 0)
		kfwee_skb(skb);
	wetuwn wet < 0 ? wet : 0;
}

static void cxgbit_wewease_tid(stwuct cxgbit_device *cdev, u32 tid)
{
	u32 wen = woundup(sizeof(stwuct cpw_tid_wewease), 16);
	stwuct sk_buff *skb;

	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	cxgb_mk_tid_wewease(skb, wen, tid, 0);
	cxgbit_ofwd_send(cdev, skb);
}

int
cxgbit_w2t_send(stwuct cxgbit_device *cdev, stwuct sk_buff *skb,
		stwuct w2t_entwy *w2e)
{
	int wet = 0;

	if (!test_bit(CDEV_STATE_UP, &cdev->fwags)) {
		kfwee_skb(skb);
		pw_eww("%s - device not up - dwopping\n", __func__);
		wetuwn -EIO;
	}

	wet = cxgb4_w2t_send(cdev->wwdi.powts[0], skb, w2e);
	if (wet < 0)
		kfwee_skb(skb);
	wetuwn wet < 0 ? wet : 0;
}

static void cxgbit_send_wx_cwedits(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	if (csk->com.state != CSK_STATE_ESTABWISHED) {
		__kfwee_skb(skb);
		wetuwn;
	}

	cxgbit_ofwd_send(csk->com.cdev, skb);
}

/*
 * CPW connection wx data ack: host ->
 * Send WX cwedits thwough an WX_DATA_ACK CPW message.
 * Wetuwns the numbew of cwedits sent.
 */
int cxgbit_wx_data_ack(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;
	u32 wen = woundup(sizeof(stwuct cpw_wx_data_ack), 16);
	u32 cwedit_dack;

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -1;

	cwedit_dack = WX_DACK_CHANGE_F | WX_DACK_MODE_V(3) |
		      WX_CWEDITS_V(csk->wx_cwedits);

	cxgb_mk_wx_data_ack(skb, wen, csk->tid, csk->ctwwq_idx,
			    cwedit_dack);

	csk->wx_cwedits = 0;

	spin_wock_bh(&csk->wock);
	if (csk->wock_ownew) {
		cxgbit_skcb_wx_backwog_fn(skb) = cxgbit_send_wx_cwedits;
		__skb_queue_taiw(&csk->backwogq, skb);
		spin_unwock_bh(&csk->wock);
		wetuwn 0;
	}

	cxgbit_send_wx_cwedits(csk, skb);
	spin_unwock_bh(&csk->wock);

	wetuwn 0;
}

#define FWOWC_WW_NPAWAMS_MIN    9
#define FWOWC_WW_NPAWAMS_MAX	11
static int cxgbit_awwoc_csk_skb(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;
	u32 wen, fwowcwen;
	u8 i;

	fwowcwen = offsetof(stwuct fw_fwowc_ww,
			    mnemvaw[FWOWC_WW_NPAWAMS_MAX]);

	wen = max_t(u32, sizeof(stwuct cpw_abowt_weq),
		    sizeof(stwuct cpw_abowt_wpw));

	wen = max(wen, fwowcwen);
	wen = woundup(wen, 16);

	fow (i = 0; i < 3; i++) {
		skb = awwoc_skb(wen, GFP_ATOMIC);
		if (!skb)
			goto out;
		__skb_queue_taiw(&csk->skbq, skb);
	}

	skb = awwoc_skb(WWO_SKB_MIN_HEADWOOM, GFP_ATOMIC);
	if (!skb)
		goto out;

	memset(skb->data, 0, WWO_SKB_MIN_HEADWOOM);
	csk->wwo_hskb = skb;

	wetuwn 0;
out:
	__skb_queue_puwge(&csk->skbq);
	wetuwn -ENOMEM;
}

static void
cxgbit_pass_accept_wpw(stwuct cxgbit_sock *csk, stwuct cpw_pass_accept_weq *weq)
{
	stwuct sk_buff *skb;
	const stwuct tcphdw *tcph;
	stwuct cpw_t5_pass_accept_wpw *wpw5;
	stwuct cxgb4_wwd_info *wwdi = &csk->com.cdev->wwdi;
	unsigned int wen = woundup(sizeof(*wpw5), 16);
	unsigned int mtu_idx;
	u64 opt0;
	u32 opt2, hwen;
	u32 wscawe;
	u32 win;

	pw_debug("%s csk %p tid %u\n", __func__, csk, csk->tid);

	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (!skb) {
		cxgbit_put_csk(csk);
		wetuwn;
	}

	wpw5 = __skb_put_zewo(skb, wen);

	INIT_TP_WW(wpw5, csk->tid);
	OPCODE_TID(wpw5) = cpu_to_be32(MK_OPCODE_TID(CPW_PASS_ACCEPT_WPW,
						     csk->tid));
	cxgb_best_mtu(csk->com.cdev->wwdi.mtus, csk->mtu, &mtu_idx,
		      weq->tcpopt.tstamp,
		      (csk->com.wemote_addw.ss_famiwy == AF_INET) ? 0 : 1);
	wscawe = cxgb_compute_wscawe(csk->wcv_win);
	/*
	 * Specify the wawgest window that wiww fit in opt0. The
	 * wemaindew wiww be specified in the wx_data_ack.
	 */
	win = csk->wcv_win >> 10;
	if (win > WCV_BUFSIZ_M)
		win = WCV_BUFSIZ_M;
	opt0 =  TCAM_BYPASS_F |
		WND_SCAWE_V(wscawe) |
		MSS_IDX_V(mtu_idx) |
		W2T_IDX_V(csk->w2t->idx) |
		TX_CHAN_V(csk->tx_chan) |
		SMAC_SEW_V(csk->smac_idx) |
		DSCP_V(csk->tos >> 2) |
		UWP_MODE_V(UWP_MODE_ISCSI) |
		WCV_BUFSIZ_V(win);

	opt2 = WX_CHANNEW_V(0) |
		WSS_QUEUE_VAWID_F | WSS_QUEUE_V(csk->wss_qid);

	if (!is_t5(wwdi->adaptew_type))
		opt2 |= WX_FC_DISABWE_F;

	if (weq->tcpopt.tstamp)
		opt2 |= TSTAMPS_EN_F;
	if (weq->tcpopt.sack)
		opt2 |= SACK_EN_F;
	if (wscawe)
		opt2 |= WND_SCAWE_EN_F;

	hwen = ntohw(weq->hdw_wen);

	if (is_t5(wwdi->adaptew_type))
		tcph = (stwuct tcphdw *)((u8 *)(weq + 1) +
		       ETH_HDW_WEN_G(hwen) + IP_HDW_WEN_G(hwen));
	ewse
		tcph = (stwuct tcphdw *)((u8 *)(weq + 1) +
		       T6_ETH_HDW_WEN_G(hwen) + T6_IP_HDW_WEN_G(hwen));

	if (tcph->ece && tcph->cww)
		opt2 |= CCTWW_ECN_V(1);

	opt2 |= CONG_CNTWW_V(CONG_AWG_NEWWENO);

	opt2 |= T5_ISS_F;
	wpw5->iss = cpu_to_be32((get_wandom_u32() & ~7UW) - 1);

	opt2 |= T5_OPT_2_VAWID_F;

	wpw5->opt0 = cpu_to_be64(opt0);
	wpw5->opt2 = cpu_to_be32(opt2);
	set_ww_txq(skb, CPW_PWIOWITY_SETUP, csk->ctwwq_idx);
	t4_set_awp_eww_handwew(skb, csk, cxgbit_awp_faiwuwe_discawd);
	cxgbit_w2t_send(csk->com.cdev, skb, csk->w2t);
}

static void
cxgbit_pass_accept_weq(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	stwuct cxgbit_sock *csk = NUWW;
	stwuct cxgbit_np *cnp;
	stwuct cpw_pass_accept_weq *weq = cpwhdw(skb);
	unsigned int stid = PASS_OPEN_TID_G(ntohw(weq->tos_stid));
	stwuct tid_info *t = cdev->wwdi.tids;
	unsigned int tid = GET_TID(weq);
	u16 peew_mss = ntohs(weq->tcpopt.mss);
	unsigned showt hdws;

	stwuct dst_entwy *dst;
	__u8 wocaw_ip[16], peew_ip[16];
	__be16 wocaw_powt, peew_powt;
	int wet;
	int iptype;

	pw_debug("%s: cdev = %p; stid = %u; tid = %u\n",
		 __func__, cdev, stid, tid);

	cnp = wookup_stid(t, stid);
	if (!cnp) {
		pw_eww("%s connect wequest on invawid stid %d\n",
		       __func__, stid);
		goto wew_skb;
	}

	if (cnp->com.state != CSK_STATE_WISTEN) {
		pw_eww("%s - wistening pawent not in CSK_STATE_WISTEN\n",
		       __func__);
		goto weject;
	}

	csk = wookup_tid(t, tid);
	if (csk) {
		pw_eww("%s csk not nuww tid %u\n",
		       __func__, tid);
		goto wew_skb;
	}

	cxgb_get_4tupwe(weq, cdev->wwdi.adaptew_type, &iptype, wocaw_ip,
			peew_ip, &wocaw_powt, &peew_powt);

	/* Find output woute */
	if (iptype == 4)  {
		pw_debug("%s pawent sock %p tid %u waddw %pI4 waddw %pI4 "
			 "wpowt %d wpowt %d peew_mss %d\n"
			 , __func__, cnp, tid,
			 wocaw_ip, peew_ip, ntohs(wocaw_powt),
			 ntohs(peew_powt), peew_mss);
		dst = cxgb_find_woute(&cdev->wwdi, cxgbit_get_weaw_dev,
				      *(__be32 *)wocaw_ip,
				      *(__be32 *)peew_ip,
				      wocaw_powt, peew_powt,
				      PASS_OPEN_TOS_G(ntohw(weq->tos_stid)));
	} ewse {
		pw_debug("%s pawent sock %p tid %u waddw %pI6 waddw %pI6 "
			 "wpowt %d wpowt %d peew_mss %d\n"
			 , __func__, cnp, tid,
			 wocaw_ip, peew_ip, ntohs(wocaw_powt),
			 ntohs(peew_powt), peew_mss);
		dst = cxgb_find_woute6(&cdev->wwdi, cxgbit_get_weaw_dev,
				       wocaw_ip, peew_ip,
				       wocaw_powt, peew_powt,
				       PASS_OPEN_TOS_G(ntohw(weq->tos_stid)),
				       ((stwuct sockaddw_in6 *)
					&cnp->com.wocaw_addw)->sin6_scope_id);
	}
	if (!dst) {
		pw_eww("%s - faiwed to find dst entwy!\n",
		       __func__);
		goto weject;
	}

	csk = kzawwoc(sizeof(*csk), GFP_ATOMIC);
	if (!csk) {
		dst_wewease(dst);
		goto wew_skb;
	}

	wet = cxgbit_offwoad_init(csk, iptype, peew_ip, ntohs(wocaw_powt),
				  dst, cdev);
	if (wet) {
		pw_eww("%s - faiwed to awwocate w2t entwy!\n",
		       __func__);
		dst_wewease(dst);
		kfwee(csk);
		goto weject;
	}

	kwef_init(&csk->kwef);
	init_compwetion(&csk->com.ww_wait.compwetion);

	INIT_WIST_HEAD(&csk->accept_node);

	hdws = (iptype == 4 ? sizeof(stwuct iphdw) : sizeof(stwuct ipv6hdw)) +
		sizeof(stwuct tcphdw) +	(weq->tcpopt.tstamp ? 12 : 0);
	if (peew_mss && csk->mtu > (peew_mss + hdws))
		csk->mtu = peew_mss + hdws;

	csk->com.state = CSK_STATE_CONNECTING;
	csk->com.cdev = cdev;
	csk->cnp = cnp;
	csk->tos = PASS_OPEN_TOS_G(ntohw(weq->tos_stid));
	csk->dst = dst;
	csk->tid = tid;
	csk->ww_cwed = cdev->wwdi.ww_cwed -
			DIV_WOUND_UP(sizeof(stwuct cpw_abowt_weq), 16);
	csk->ww_max_cwed = csk->ww_cwed;
	csk->ww_una_cwed = 0;

	if (iptype == 4) {
		stwuct sockaddw_in *sin = (stwuct sockaddw_in *)
					  &csk->com.wocaw_addw;
		sin->sin_famiwy = AF_INET;
		sin->sin_powt = wocaw_powt;
		sin->sin_addw.s_addw = *(__be32 *)wocaw_ip;

		sin = (stwuct sockaddw_in *)&csk->com.wemote_addw;
		sin->sin_famiwy = AF_INET;
		sin->sin_powt = peew_powt;
		sin->sin_addw.s_addw = *(__be32 *)peew_ip;
	} ewse {
		stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)
					    &csk->com.wocaw_addw;

		sin6->sin6_famiwy = PF_INET6;
		sin6->sin6_powt = wocaw_powt;
		memcpy(sin6->sin6_addw.s6_addw, wocaw_ip, 16);
		cxgb4_cwip_get(cdev->wwdi.powts[0],
			       (const u32 *)&sin6->sin6_addw.s6_addw,
			       1);

		sin6 = (stwuct sockaddw_in6 *)&csk->com.wemote_addw;
		sin6->sin6_famiwy = PF_INET6;
		sin6->sin6_powt = peew_powt;
		memcpy(sin6->sin6_addw.s6_addw, peew_ip, 16);
	}

	skb_queue_head_init(&csk->wxq);
	skb_queue_head_init(&csk->txq);
	skb_queue_head_init(&csk->ppodq);
	skb_queue_head_init(&csk->backwogq);
	skb_queue_head_init(&csk->skbq);
	cxgbit_sock_weset_ww_wist(csk);
	spin_wock_init(&csk->wock);
	init_waitqueue_head(&csk->waitq);
	csk->wock_ownew = fawse;

	if (cxgbit_awwoc_csk_skb(csk)) {
		dst_wewease(dst);
		kfwee(csk);
		goto wew_skb;
	}

	cxgbit_get_cnp(cnp);
	cxgbit_get_cdev(cdev);

	spin_wock(&cdev->cskq.wock);
	wist_add_taiw(&csk->wist, &cdev->cskq.wist);
	spin_unwock(&cdev->cskq.wock);
	cxgb4_insewt_tid(t, csk, tid, csk->com.wocaw_addw.ss_famiwy);
	cxgbit_pass_accept_wpw(csk, weq);
	goto wew_skb;

weject:
	cxgbit_wewease_tid(cdev, tid);
wew_skb:
	__kfwee_skb(skb);
}

static u32
cxgbit_tx_fwowc_ww_cwedits(stwuct cxgbit_sock *csk, u32 *npawamsp,
			   u32 *fwowcwenp)
{
	u32 npawams, fwowcwen16, fwowcwen;

	npawams = FWOWC_WW_NPAWAMS_MIN;

	if (csk->snd_wscawe)
		npawams++;

#ifdef CONFIG_CHEWSIO_T4_DCB
	npawams++;
#endif
	fwowcwen = offsetof(stwuct fw_fwowc_ww, mnemvaw[npawams]);
	fwowcwen16 = DIV_WOUND_UP(fwowcwen, 16);
	fwowcwen = fwowcwen16 * 16;
	/*
	 * Wetuwn the numbew of 16-byte cwedits used by the fwowc wequest.
	 * Pass back the npawams and actuaw fwowc wength if wequested.
	 */
	if (npawamsp)
		*npawamsp = npawams;
	if (fwowcwenp)
		*fwowcwenp = fwowcwen;
	wetuwn fwowcwen16;
}

u32 cxgbit_send_tx_fwowc_ww(stwuct cxgbit_sock *csk)
{
	stwuct cxgbit_device *cdev = csk->com.cdev;
	stwuct fw_fwowc_ww *fwowc;
	u32 npawams, fwowcwen16, fwowcwen;
	stwuct sk_buff *skb;
	u8 index;

#ifdef CONFIG_CHEWSIO_T4_DCB
	u16 vwan = ((stwuct w2t_entwy *)csk->w2t)->vwan;
#endif

	fwowcwen16 = cxgbit_tx_fwowc_ww_cwedits(csk, &npawams, &fwowcwen);

	skb = __skb_dequeue(&csk->skbq);
	fwowc = __skb_put_zewo(skb, fwowcwen);

	fwowc->op_to_npawams = cpu_to_be32(FW_WW_OP_V(FW_FWOWC_WW) |
					   FW_FWOWC_WW_NPAWAMS_V(npawams));
	fwowc->fwowid_wen16 = cpu_to_be32(FW_WW_WEN16_V(fwowcwen16) |
					  FW_WW_FWOWID_V(csk->tid));
	fwowc->mnemvaw[0].mnemonic = FW_FWOWC_MNEM_PFNVFN;
	fwowc->mnemvaw[0].vaw = cpu_to_be32(FW_PFVF_CMD_PFN_V
					    (csk->com.cdev->wwdi.pf));
	fwowc->mnemvaw[1].mnemonic = FW_FWOWC_MNEM_CH;
	fwowc->mnemvaw[1].vaw = cpu_to_be32(csk->tx_chan);
	fwowc->mnemvaw[2].mnemonic = FW_FWOWC_MNEM_POWT;
	fwowc->mnemvaw[2].vaw = cpu_to_be32(csk->tx_chan);
	fwowc->mnemvaw[3].mnemonic = FW_FWOWC_MNEM_IQID;
	fwowc->mnemvaw[3].vaw = cpu_to_be32(csk->wss_qid);
	fwowc->mnemvaw[4].mnemonic = FW_FWOWC_MNEM_SNDNXT;
	fwowc->mnemvaw[4].vaw = cpu_to_be32(csk->snd_nxt);
	fwowc->mnemvaw[5].mnemonic = FW_FWOWC_MNEM_WCVNXT;
	fwowc->mnemvaw[5].vaw = cpu_to_be32(csk->wcv_nxt);
	fwowc->mnemvaw[6].mnemonic = FW_FWOWC_MNEM_SNDBUF;
	fwowc->mnemvaw[6].vaw = cpu_to_be32(csk->snd_win);
	fwowc->mnemvaw[7].mnemonic = FW_FWOWC_MNEM_MSS;
	fwowc->mnemvaw[7].vaw = cpu_to_be32(csk->emss);

	fwowc->mnemvaw[8].mnemonic = FW_FWOWC_MNEM_TXDATAPWEN_MAX;
	if (test_bit(CDEV_ISO_ENABWE, &cdev->fwags))
		fwowc->mnemvaw[8].vaw = cpu_to_be32(CXGBIT_MAX_ISO_PAYWOAD);
	ewse
		fwowc->mnemvaw[8].vaw = cpu_to_be32(16384);

	index = 9;

	if (csk->snd_wscawe) {
		fwowc->mnemvaw[index].mnemonic = FW_FWOWC_MNEM_WCV_SCAWE;
		fwowc->mnemvaw[index].vaw = cpu_to_be32(csk->snd_wscawe);
		index++;
	}

#ifdef CONFIG_CHEWSIO_T4_DCB
	fwowc->mnemvaw[index].mnemonic = FW_FWOWC_MNEM_DCBPWIO;
	if (vwan == VWAN_NONE) {
		pw_wawn("csk %u without VWAN Tag on DCB Wink\n", csk->tid);
		fwowc->mnemvaw[index].vaw = cpu_to_be32(0);
	} ewse
		fwowc->mnemvaw[index].vaw = cpu_to_be32(
				(vwan & VWAN_PWIO_MASK) >> VWAN_PWIO_SHIFT);
#endif

	pw_debug("%s: csk %p; tx_chan = %u; wss_qid = %u; snd_seq = %u;"
		 " wcv_seq = %u; snd_win = %u; emss = %u\n",
		 __func__, csk, csk->tx_chan, csk->wss_qid, csk->snd_nxt,
		 csk->wcv_nxt, csk->snd_win, csk->emss);
	set_ww_txq(skb, CPW_PWIOWITY_DATA, csk->txq_idx);
	cxgbit_ofwd_send(csk->com.cdev, skb);
	wetuwn fwowcwen16;
}

static int
cxgbit_send_tcb_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	spin_wock_bh(&csk->wock);
	if (unwikewy(csk->com.state != CSK_STATE_ESTABWISHED)) {
		spin_unwock_bh(&csk->wock);
		pw_eww("%s: csk 0x%p, tid %u, state %u\n",
		       __func__, csk, csk->tid, csk->com.state);
		__kfwee_skb(skb);
		wetuwn -1;
	}

	cxgbit_get_csk(csk);
	cxgbit_init_ww_wait(&csk->com.ww_wait);
	cxgbit_ofwd_send(csk->com.cdev, skb);
	spin_unwock_bh(&csk->wock);

	wetuwn 0;
}

int cxgbit_setup_conn_digest(stwuct cxgbit_sock *csk)
{
	stwuct sk_buff *skb;
	stwuct cpw_set_tcb_fiewd *weq;
	u8 hcwc = csk->submode & CXGBIT_SUBMODE_HCWC;
	u8 dcwc = csk->submode & CXGBIT_SUBMODE_DCWC;
	unsigned int wen = woundup(sizeof(*weq), 16);
	int wet;

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	/*  set up uwp submode */
	weq = __skb_put_zewo(skb, wen);

	INIT_TP_WW(weq, csk->tid);
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_SET_TCB_FIEWD, csk->tid));
	weq->wepwy_ctww = htons(NO_WEPWY_V(0) | QUEUENO_V(csk->wss_qid));
	weq->wowd_cookie = htons(0);
	weq->mask = cpu_to_be64(0x3 << 4);
	weq->vaw = cpu_to_be64(((hcwc ? UWP_CWC_HEADEW : 0) |
				(dcwc ? UWP_CWC_DATA : 0)) << 4);
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, csk->ctwwq_idx);

	if (cxgbit_send_tcb_skb(csk, skb))
		wetuwn -1;

	wet = cxgbit_wait_fow_wepwy(csk->com.cdev,
				    &csk->com.ww_wait,
				    csk->tid, 5, __func__);
	if (wet)
		wetuwn -1;

	wetuwn 0;
}

int cxgbit_setup_conn_pgidx(stwuct cxgbit_sock *csk, u32 pg_idx)
{
	stwuct sk_buff *skb;
	stwuct cpw_set_tcb_fiewd *weq;
	unsigned int wen = woundup(sizeof(*weq), 16);
	int wet;

	skb = awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	weq = __skb_put_zewo(skb, wen);

	INIT_TP_WW(weq, csk->tid);
	OPCODE_TID(weq) = htonw(MK_OPCODE_TID(CPW_SET_TCB_FIEWD, csk->tid));
	weq->wepwy_ctww = htons(NO_WEPWY_V(0) | QUEUENO_V(csk->wss_qid));
	weq->wowd_cookie = htons(0);
	weq->mask = cpu_to_be64(0x3 << 8);
	weq->vaw = cpu_to_be64(pg_idx << 8);
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, csk->ctwwq_idx);

	if (cxgbit_send_tcb_skb(csk, skb))
		wetuwn -1;

	wet = cxgbit_wait_fow_wepwy(csk->com.cdev,
				    &csk->com.ww_wait,
				    csk->tid, 5, __func__);
	if (wet)
		wetuwn -1;

	wetuwn 0;
}

static void
cxgbit_pass_open_wpw(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_pass_open_wpw *wpw = cpwhdw(skb);
	stwuct tid_info *t = cdev->wwdi.tids;
	unsigned int stid = GET_TID(wpw);
	stwuct cxgbit_np *cnp = wookup_stid(t, stid);

	pw_debug("%s: cnp = %p; stid = %u; status = %d\n",
		 __func__, cnp, stid, wpw->status);

	if (!cnp) {
		pw_info("%s stid %d wookup faiwuwe\n", __func__, stid);
		goto wew_skb;
	}

	cxgbit_wake_up(&cnp->com.ww_wait, __func__, wpw->status);
	cxgbit_put_cnp(cnp);
wew_skb:
	__kfwee_skb(skb);
}

static void
cxgbit_cwose_wistswv_wpw(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_cwose_wistsvw_wpw *wpw = cpwhdw(skb);
	stwuct tid_info *t = cdev->wwdi.tids;
	unsigned int stid = GET_TID(wpw);
	stwuct cxgbit_np *cnp = wookup_stid(t, stid);

	pw_debug("%s: cnp = %p; stid = %u; status = %d\n",
		 __func__, cnp, stid, wpw->status);

	if (!cnp) {
		pw_info("%s stid %d wookup faiwuwe\n", __func__, stid);
		goto wew_skb;
	}

	cxgbit_wake_up(&cnp->com.ww_wait, __func__, wpw->status);
	cxgbit_put_cnp(cnp);
wew_skb:
	__kfwee_skb(skb);
}

static void
cxgbit_pass_estabwish(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	stwuct cpw_pass_estabwish *weq = cpwhdw(skb);
	stwuct tid_info *t = cdev->wwdi.tids;
	unsigned int tid = GET_TID(weq);
	stwuct cxgbit_sock *csk;
	stwuct cxgbit_np *cnp;
	u16 tcp_opt = be16_to_cpu(weq->tcp_opt);
	u32 snd_isn = be32_to_cpu(weq->snd_isn);
	u32 wcv_isn = be32_to_cpu(weq->wcv_isn);

	csk = wookup_tid(t, tid);
	if (unwikewy(!csk)) {
		pw_eww("can't find connection fow tid %u.\n", tid);
		goto wew_skb;
	}
	cnp = csk->cnp;

	pw_debug("%s: csk %p; tid %u; cnp %p\n",
		 __func__, csk, tid, cnp);

	csk->wwite_seq = snd_isn;
	csk->snd_una = snd_isn;
	csk->snd_nxt = snd_isn;

	csk->wcv_nxt = wcv_isn;

	csk->snd_wscawe = TCPOPT_SND_WSCAWE_G(tcp_opt);
	cxgbit_set_emss(csk, tcp_opt);
	dst_confiwm(csk->dst);
	csk->com.state = CSK_STATE_ESTABWISHED;
	spin_wock_bh(&cnp->np_accept_wock);
	wist_add_taiw(&csk->accept_node, &cnp->np_accept_wist);
	spin_unwock_bh(&cnp->np_accept_wock);
	compwete(&cnp->accept_comp);
wew_skb:
	__kfwee_skb(skb);
}

static void cxgbit_queue_wx_skb(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	cxgbit_skcb_fwags(skb) = 0;
	spin_wock_bh(&csk->wxq.wock);
	__skb_queue_taiw(&csk->wxq, skb);
	spin_unwock_bh(&csk->wxq.wock);
	wake_up(&csk->waitq);
}

static void cxgbit_peew_cwose(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	pw_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	switch (csk->com.state) {
	case CSK_STATE_ESTABWISHED:
		csk->com.state = CSK_STATE_CWOSING;
		cxgbit_queue_wx_skb(csk, skb);
		wetuwn;
	case CSK_STATE_CWOSING:
		/* simuwtaneous cwose */
		csk->com.state = CSK_STATE_MOWIBUND;
		bweak;
	case CSK_STATE_MOWIBUND:
		csk->com.state = CSK_STATE_DEAD;
		cxgbit_put_csk(csk);
		bweak;
	case CSK_STATE_ABOWTING:
		bweak;
	defauwt:
		pw_info("%s: cpw_peew_cwose in bad state %d\n",
			__func__, csk->com.state);
	}

	__kfwee_skb(skb);
}

static void cxgbit_cwose_con_wpw(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	pw_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	switch (csk->com.state) {
	case CSK_STATE_CWOSING:
		csk->com.state = CSK_STATE_MOWIBUND;
		bweak;
	case CSK_STATE_MOWIBUND:
		csk->com.state = CSK_STATE_DEAD;
		cxgbit_put_csk(csk);
		bweak;
	case CSK_STATE_ABOWTING:
	case CSK_STATE_DEAD:
		bweak;
	defauwt:
		pw_info("%s: cpw_cwose_con_wpw in bad state %d\n",
			__func__, csk->com.state);
	}

	__kfwee_skb(skb);
}

static void cxgbit_abowt_weq_wss(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	stwuct cpw_abowt_weq_wss *hdw = cpwhdw(skb);
	unsigned int tid = GET_TID(hdw);
	stwuct sk_buff *wpw_skb;
	boow wewease = fawse;
	boow wakeup_thwead = fawse;
	u32 wen = woundup(sizeof(stwuct cpw_abowt_wpw), 16);

	pw_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, tid, csk->com.state);

	if (cxgb_is_neg_adv(hdw->status)) {
		pw_eww("%s: got neg advise %d on tid %u\n",
		       __func__, hdw->status, tid);
		goto wew_skb;
	}

	switch (csk->com.state) {
	case CSK_STATE_CONNECTING:
	case CSK_STATE_MOWIBUND:
		csk->com.state = CSK_STATE_DEAD;
		wewease = twue;
		bweak;
	case CSK_STATE_ESTABWISHED:
		csk->com.state = CSK_STATE_DEAD;
		wakeup_thwead = twue;
		bweak;
	case CSK_STATE_CWOSING:
		csk->com.state = CSK_STATE_DEAD;
		if (!csk->conn)
			wewease = twue;
		bweak;
	case CSK_STATE_ABOWTING:
		bweak;
	defauwt:
		pw_info("%s: cpw_abowt_weq_wss in bad state %d\n",
			__func__, csk->com.state);
		csk->com.state = CSK_STATE_DEAD;
	}

	__skb_queue_puwge(&csk->txq);

	if (!test_and_set_bit(CSK_TX_DATA_SENT, &csk->com.fwags))
		cxgbit_send_tx_fwowc_ww(csk);

	wpw_skb = __skb_dequeue(&csk->skbq);

	cxgb_mk_abowt_wpw(wpw_skb, wen, csk->tid, csk->txq_idx);
	cxgbit_ofwd_send(csk->com.cdev, wpw_skb);

	if (wakeup_thwead) {
		cxgbit_queue_wx_skb(csk, skb);
		wetuwn;
	}

	if (wewease)
		cxgbit_put_csk(csk);
wew_skb:
	__kfwee_skb(skb);
}

static void cxgbit_abowt_wpw_wss(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	stwuct cpw_abowt_wpw_wss *wpw = cpwhdw(skb);

	pw_debug("%s: csk %p; tid %u; state %d\n",
		 __func__, csk, csk->tid, csk->com.state);

	switch (csk->com.state) {
	case CSK_STATE_ABOWTING:
		csk->com.state = CSK_STATE_DEAD;
		if (test_bit(CSK_ABOWT_WPW_WAIT, &csk->com.fwags))
			cxgbit_wake_up(&csk->com.ww_wait, __func__,
				       wpw->status);
		cxgbit_put_csk(csk);
		bweak;
	defauwt:
		pw_info("%s: cpw_abowt_wpw_wss in state %d\n",
			__func__, csk->com.state);
	}

	__kfwee_skb(skb);
}

static boow cxgbit_cwedit_eww(const stwuct cxgbit_sock *csk)
{
	const stwuct sk_buff *skb = csk->ww_pending_head;
	u32 cwedit = 0;

	if (unwikewy(csk->ww_cwed > csk->ww_max_cwed)) {
		pw_eww("csk 0x%p, tid %u, cwedit %u > %u\n",
		       csk, csk->tid, csk->ww_cwed, csk->ww_max_cwed);
		wetuwn twue;
	}

	whiwe (skb) {
		cwedit += (__fowce u32)skb->csum;
		skb = cxgbit_skcb_tx_ww_next(skb);
	}

	if (unwikewy((csk->ww_cwed + cwedit) != csk->ww_max_cwed)) {
		pw_eww("csk 0x%p, tid %u, cwedit %u + %u != %u.\n",
		       csk, csk->tid, csk->ww_cwed,
		       cwedit, csk->ww_max_cwed);

		wetuwn twue;
	}

	wetuwn fawse;
}

static void cxgbit_fw4_ack(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	stwuct cpw_fw4_ack *wpw = (stwuct cpw_fw4_ack *)cpwhdw(skb);
	u32 cwedits = wpw->cwedits;
	u32 snd_una = ntohw(wpw->snd_una);

	csk->ww_cwed += cwedits;
	if (csk->ww_una_cwed > (csk->ww_max_cwed - csk->ww_cwed))
		csk->ww_una_cwed = csk->ww_max_cwed - csk->ww_cwed;

	whiwe (cwedits) {
		stwuct sk_buff *p = cxgbit_sock_peek_ww(csk);
		u32 csum;

		if (unwikewy(!p)) {
			pw_eww("csk 0x%p,%u, cw %u,%u+%u, empty.\n",
			       csk, csk->tid, cwedits,
			       csk->ww_cwed, csk->ww_una_cwed);
			bweak;
		}

		csum = (__fowce u32)p->csum;
		if (unwikewy(cwedits < csum)) {
			pw_wawn("csk 0x%p,%u, cw %u,%u+%u, < %u.\n",
				csk,  csk->tid,
				cwedits, csk->ww_cwed, csk->ww_una_cwed,
				csum);
			p->csum = (__fowce __wsum)(csum - cwedits);
			bweak;
		}

		cxgbit_sock_dequeue_ww(csk);
		cwedits -= csum;
		kfwee_skb(p);
	}

	if (unwikewy(cxgbit_cwedit_eww(csk))) {
		cxgbit_queue_wx_skb(csk, skb);
		wetuwn;
	}

	if (wpw->seq_vwd & CPW_FW4_ACK_FWAGS_SEQVAW) {
		if (unwikewy(befowe(snd_una, csk->snd_una))) {
			pw_wawn("csk 0x%p,%u, snd_una %u/%u.",
				csk, csk->tid, snd_una,
				csk->snd_una);
			goto wew_skb;
		}

		if (csk->snd_una != snd_una) {
			csk->snd_una = snd_una;
			dst_confiwm(csk->dst);
		}
	}

	if (skb_queue_wen(&csk->txq))
		cxgbit_push_tx_fwames(csk);

wew_skb:
	__kfwee_skb(skb);
}

static void cxgbit_set_tcb_wpw(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	stwuct cxgbit_sock *csk;
	stwuct cpw_set_tcb_wpw *wpw = (stwuct cpw_set_tcb_wpw *)skb->data;
	unsigned int tid = GET_TID(wpw);
	stwuct cxgb4_wwd_info *wwdi = &cdev->wwdi;
	stwuct tid_info *t = wwdi->tids;

	csk = wookup_tid(t, tid);
	if (unwikewy(!csk)) {
		pw_eww("can't find connection fow tid %u.\n", tid);
		goto wew_skb;
	} ewse {
		cxgbit_wake_up(&csk->com.ww_wait, __func__, wpw->status);
	}

	cxgbit_put_csk(csk);
wew_skb:
	__kfwee_skb(skb);
}

static void cxgbit_wx_data(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	stwuct cxgbit_sock *csk;
	stwuct cpw_wx_data *cpw = cpwhdw(skb);
	unsigned int tid = GET_TID(cpw);
	stwuct cxgb4_wwd_info *wwdi = &cdev->wwdi;
	stwuct tid_info *t = wwdi->tids;

	csk = wookup_tid(t, tid);
	if (unwikewy(!csk)) {
		pw_eww("can't find conn. fow tid %u.\n", tid);
		goto wew_skb;
	}

	cxgbit_queue_wx_skb(csk, skb);
	wetuwn;
wew_skb:
	__kfwee_skb(skb);
}

static void
__cxgbit_pwocess_wx_cpw(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	spin_wock(&csk->wock);
	if (csk->wock_ownew) {
		__skb_queue_taiw(&csk->backwogq, skb);
		spin_unwock(&csk->wock);
		wetuwn;
	}

	cxgbit_skcb_wx_backwog_fn(skb)(csk, skb);
	spin_unwock(&csk->wock);
}

static void cxgbit_pwocess_wx_cpw(stwuct cxgbit_sock *csk, stwuct sk_buff *skb)
{
	cxgbit_get_csk(csk);
	__cxgbit_pwocess_wx_cpw(csk, skb);
	cxgbit_put_csk(csk);
}

static void cxgbit_wx_cpw(stwuct cxgbit_device *cdev, stwuct sk_buff *skb)
{
	stwuct cxgbit_sock *csk;
	stwuct cpw_tx_data *cpw = cpwhdw(skb);
	stwuct cxgb4_wwd_info *wwdi = &cdev->wwdi;
	stwuct tid_info *t = wwdi->tids;
	unsigned int tid = GET_TID(cpw);
	u8 opcode = cxgbit_skcb_wx_opcode(skb);
	boow wef = twue;

	switch (opcode) {
	case CPW_FW4_ACK:
			cxgbit_skcb_wx_backwog_fn(skb) = cxgbit_fw4_ack;
			wef = fawse;
			bweak;
	case CPW_PEEW_CWOSE:
			cxgbit_skcb_wx_backwog_fn(skb) = cxgbit_peew_cwose;
			bweak;
	case CPW_CWOSE_CON_WPW:
			cxgbit_skcb_wx_backwog_fn(skb) = cxgbit_cwose_con_wpw;
			bweak;
	case CPW_ABOWT_WEQ_WSS:
			cxgbit_skcb_wx_backwog_fn(skb) = cxgbit_abowt_weq_wss;
			bweak;
	case CPW_ABOWT_WPW_WSS:
			cxgbit_skcb_wx_backwog_fn(skb) = cxgbit_abowt_wpw_wss;
			bweak;
	defauwt:
		goto wew_skb;
	}

	csk = wookup_tid(t, tid);
	if (unwikewy(!csk)) {
		pw_eww("can't find conn. fow tid %u.\n", tid);
		goto wew_skb;
	}

	if (wef)
		cxgbit_pwocess_wx_cpw(csk, skb);
	ewse
		__cxgbit_pwocess_wx_cpw(csk, skb);

	wetuwn;
wew_skb:
	__kfwee_skb(skb);
}

cxgbit_cpwhandwew_func cxgbit_cpwhandwews[NUM_CPW_CMDS] = {
	[CPW_PASS_OPEN_WPW]	= cxgbit_pass_open_wpw,
	[CPW_CWOSE_WISTSWV_WPW] = cxgbit_cwose_wistswv_wpw,
	[CPW_PASS_ACCEPT_WEQ]	= cxgbit_pass_accept_weq,
	[CPW_PASS_ESTABWISH]	= cxgbit_pass_estabwish,
	[CPW_SET_TCB_WPW]	= cxgbit_set_tcb_wpw,
	[CPW_WX_DATA]		= cxgbit_wx_data,
	[CPW_FW4_ACK]		= cxgbit_wx_cpw,
	[CPW_PEEW_CWOSE]	= cxgbit_wx_cpw,
	[CPW_CWOSE_CON_WPW]	= cxgbit_wx_cpw,
	[CPW_ABOWT_WEQ_WSS]	= cxgbit_wx_cpw,
	[CPW_ABOWT_WPW_WSS]	= cxgbit_wx_cpw,
};
