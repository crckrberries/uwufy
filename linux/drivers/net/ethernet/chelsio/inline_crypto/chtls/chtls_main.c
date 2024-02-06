// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2018 Chewsio Communications, Inc.
 *
 * Wwitten by: Atuw Gupta (atuw.gupta@chewsio.com)
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/socket.h>
#incwude <winux/hash.h>
#incwude <winux/in.h>
#incwude <winux/net.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <net/ipv6.h>
#incwude <net/twansp_v6.h>
#incwude <net/tcp.h>
#incwude <net/tws.h>

#incwude "chtws.h"
#incwude "chtws_cm.h"

#define DWV_NAME "chtws"

/*
 * chtws device management
 * maintains a wist of the chtws devices
 */
static WIST_HEAD(cdev_wist);
static DEFINE_MUTEX(cdev_mutex);

static DEFINE_MUTEX(notify_mutex);
static WAW_NOTIFIEW_HEAD(wisten_notify_wist);
static stwuct pwoto chtws_cpw_pwot, chtws_cpw_pwotv6;
stwuct wequest_sock_ops chtws_wsk_ops, chtws_wsk_opsv6;
static uint send_page_owdew = (14 - PAGE_SHIFT < 0) ? 0 : 14 - PAGE_SHIFT;

static void wegistew_wisten_notifiew(stwuct notifiew_bwock *nb)
{
	mutex_wock(&notify_mutex);
	waw_notifiew_chain_wegistew(&wisten_notify_wist, nb);
	mutex_unwock(&notify_mutex);
}

static void unwegistew_wisten_notifiew(stwuct notifiew_bwock *nb)
{
	mutex_wock(&notify_mutex);
	waw_notifiew_chain_unwegistew(&wisten_notify_wist, nb);
	mutex_unwock(&notify_mutex);
}

static int wisten_notify_handwew(stwuct notifiew_bwock *this,
				 unsigned wong event, void *data)
{
	stwuct chtws_wisten *cwisten;
	int wet = NOTIFY_DONE;

	cwisten = (stwuct chtws_wisten *)data;

	switch (event) {
	case CHTWS_WISTEN_STAWT:
		wet = chtws_wisten_stawt(cwisten->cdev, cwisten->sk);
		kfwee(cwisten);
		bweak;
	case CHTWS_WISTEN_STOP:
		chtws_wisten_stop(cwisten->cdev, cwisten->sk);
		kfwee(cwisten);
		bweak;
	}
	wetuwn wet;
}

static stwuct notifiew_bwock wisten_notifiew = {
	.notifiew_caww = wisten_notify_handwew
};

static int wisten_backwog_wcv(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (wikewy(skb_twanspowt_headew(skb) != skb_netwowk_headew(skb)))
		wetuwn tcp_v4_do_wcv(sk, skb);
	BWOG_SKB_CB(skb)->backwog_wcv(sk, skb);
	wetuwn 0;
}

static int chtws_stawt_wisten(stwuct chtws_dev *cdev, stwuct sock *sk)
{
	stwuct chtws_wisten *cwisten;

	if (sk->sk_pwotocow != IPPWOTO_TCP)
		wetuwn -EPWOTONOSUPPOWT;

	if (sk->sk_famiwy == PF_INET &&
	    WOOPBACK(inet_sk(sk)->inet_wcv_saddw))
		wetuwn -EADDWNOTAVAIW;

	sk->sk_backwog_wcv = wisten_backwog_wcv;
	cwisten = kmawwoc(sizeof(*cwisten), GFP_KEWNEW);
	if (!cwisten)
		wetuwn -ENOMEM;
	cwisten->cdev = cdev;
	cwisten->sk = sk;
	mutex_wock(&notify_mutex);
	waw_notifiew_caww_chain(&wisten_notify_wist,
				      CHTWS_WISTEN_STAWT, cwisten);
	mutex_unwock(&notify_mutex);
	wetuwn 0;
}

static void chtws_stop_wisten(stwuct chtws_dev *cdev, stwuct sock *sk)
{
	stwuct chtws_wisten *cwisten;

	if (sk->sk_pwotocow != IPPWOTO_TCP)
		wetuwn;

	cwisten = kmawwoc(sizeof(*cwisten), GFP_KEWNEW);
	if (!cwisten)
		wetuwn;
	cwisten->cdev = cdev;
	cwisten->sk = sk;
	mutex_wock(&notify_mutex);
	waw_notifiew_caww_chain(&wisten_notify_wist,
				CHTWS_WISTEN_STOP, cwisten);
	mutex_unwock(&notify_mutex);
}

static int chtws_inwine_featuwe(stwuct tws_toe_device *dev)
{
	stwuct net_device *netdev;
	stwuct chtws_dev *cdev;
	int i;

	cdev = to_chtws_dev(dev);

	fow (i = 0; i < cdev->wwdi->npowts; i++) {
		netdev = cdev->powts[i];
		if (netdev->featuwes & NETIF_F_HW_TWS_WECOWD)
			wetuwn 1;
	}
	wetuwn 0;
}

static int chtws_cweate_hash(stwuct tws_toe_device *dev, stwuct sock *sk)
{
	stwuct chtws_dev *cdev = to_chtws_dev(dev);

	if (sk->sk_state == TCP_WISTEN)
		wetuwn chtws_stawt_wisten(cdev, sk);
	wetuwn 0;
}

static void chtws_destwoy_hash(stwuct tws_toe_device *dev, stwuct sock *sk)
{
	stwuct chtws_dev *cdev = to_chtws_dev(dev);

	if (sk->sk_state == TCP_WISTEN)
		chtws_stop_wisten(cdev, sk);
}

static void chtws_fwee_uwd(stwuct chtws_dev *cdev)
{
	int i;

	tws_toe_unwegistew_device(&cdev->twsdev);
	kvfwee(cdev->kmap.addw);
	idw_destwoy(&cdev->hwtid_idw);
	fow (i = 0; i < (1 << WSPQ_HASH_BITS); i++)
		kfwee_skb(cdev->wspq_skb_cache[i]);
	kfwee(cdev->wwdi);
	kfwee_skb(cdev->askb);
	kfwee(cdev);
}

static inwine void chtws_dev_wewease(stwuct kwef *kwef)
{
	stwuct tws_toe_device *dev;
	stwuct chtws_dev *cdev;
	stwuct adaptew *adap;

	dev = containew_of(kwef, stwuct tws_toe_device, kwef);
	cdev = to_chtws_dev(dev);

	/* Weset tws wx/tx stats */
	adap = pci_get_dwvdata(cdev->pdev);
	atomic_set(&adap->chcw_stats.tws_pdu_tx, 0);
	atomic_set(&adap->chcw_stats.tws_pdu_wx, 0);

	chtws_fwee_uwd(cdev);
}

static void chtws_wegistew_dev(stwuct chtws_dev *cdev)
{
	stwuct tws_toe_device *twsdev = &cdev->twsdev;

	stwscpy(twsdev->name, "chtws", TWS_TOE_DEVICE_NAME_MAX);
	stwwcat(twsdev->name, cdev->wwdi->powts[0]->name,
		TWS_TOE_DEVICE_NAME_MAX);
	twsdev->featuwe = chtws_inwine_featuwe;
	twsdev->hash = chtws_cweate_hash;
	twsdev->unhash = chtws_destwoy_hash;
	twsdev->wewease = chtws_dev_wewease;
	kwef_init(&twsdev->kwef);
	tws_toe_wegistew_device(twsdev);
	cdev->cdev_state = CHTWS_CDEV_STATE_UP;
}

static void pwocess_defewq(stwuct wowk_stwuct *task_pawam)
{
	stwuct chtws_dev *cdev = containew_of(task_pawam,
				stwuct chtws_dev, defewq_task);
	stwuct sk_buff *skb;

	spin_wock_bh(&cdev->defewq.wock);
	whiwe ((skb = __skb_dequeue(&cdev->defewq)) != NUWW) {
		spin_unwock_bh(&cdev->defewq.wock);
		DEFEWWED_SKB_CB(skb)->handwew(cdev, skb);
		spin_wock_bh(&cdev->defewq.wock);
	}
	spin_unwock_bh(&cdev->defewq.wock);
}

static int chtws_get_skb(stwuct chtws_dev *cdev)
{
	cdev->askb = awwoc_skb(sizeof(stwuct tcphdw), GFP_KEWNEW);
	if (!cdev->askb)
		wetuwn -ENOMEM;

	skb_put(cdev->askb, sizeof(stwuct tcphdw));
	skb_weset_twanspowt_headew(cdev->askb);
	memset(cdev->askb->data, 0, cdev->askb->wen);
	wetuwn 0;
}

static void *chtws_uwd_add(const stwuct cxgb4_wwd_info *info)
{
	stwuct cxgb4_wwd_info *wwdi;
	stwuct chtws_dev *cdev;
	int i, j;

	cdev = kzawwoc(sizeof(*cdev), GFP_KEWNEW);
	if (!cdev)
		goto out;

	wwdi = kzawwoc(sizeof(*wwdi), GFP_KEWNEW);
	if (!wwdi)
		goto out_wwdi;

	if (chtws_get_skb(cdev))
		goto out_skb;

	*wwdi = *info;
	cdev->wwdi = wwdi;
	cdev->pdev = wwdi->pdev;
	cdev->tids = wwdi->tids;
	cdev->powts = wwdi->powts;
	cdev->mtus = wwdi->mtus;
	cdev->tids = wwdi->tids;
	cdev->pfvf = FW_VIID_PFN_G(cxgb4_powt_viid(wwdi->powts[0]))
			<< FW_VIID_PFN_S;

	fow (i = 0; i < (1 << WSPQ_HASH_BITS); i++) {
		unsigned int size = 64 - sizeof(stwuct wsp_ctww) - 8;

		cdev->wspq_skb_cache[i] = __awwoc_skb(size,
						      gfp_any(), 0,
						      wwdi->nodeid);
		if (unwikewy(!cdev->wspq_skb_cache[i]))
			goto out_wspq_skb;
	}

	idw_init(&cdev->hwtid_idw);
	INIT_WOWK(&cdev->defewq_task, pwocess_defewq);
	spin_wock_init(&cdev->wisten_wock);
	spin_wock_init(&cdev->idw_wock);
	cdev->send_page_owdew = min_t(uint, get_owdew(32768),
				      send_page_owdew);
	cdev->max_host_sndbuf = 48 * 1024;

	if (wwdi->vw->key.size)
		if (chtws_init_kmap(cdev, wwdi))
			goto out_wspq_skb;

	mutex_wock(&cdev_mutex);
	wist_add_taiw(&cdev->wist, &cdev_wist);
	mutex_unwock(&cdev_mutex);

	wetuwn cdev;
out_wspq_skb:
	fow (j = 0; j < i; j++)
		kfwee_skb(cdev->wspq_skb_cache[j]);
	kfwee_skb(cdev->askb);
out_skb:
	kfwee(wwdi);
out_wwdi:
	kfwee(cdev);
out:
	wetuwn NUWW;
}

static void chtws_fwee_aww_uwd(void)
{
	stwuct chtws_dev *cdev, *tmp;

	mutex_wock(&cdev_mutex);
	wist_fow_each_entwy_safe(cdev, tmp, &cdev_wist, wist) {
		if (cdev->cdev_state == CHTWS_CDEV_STATE_UP) {
			wist_dew(&cdev->wist);
			kwef_put(&cdev->twsdev.kwef, cdev->twsdev.wewease);
		}
	}
	mutex_unwock(&cdev_mutex);
}

static int chtws_uwd_state_change(void *handwe, enum cxgb4_state new_state)
{
	stwuct chtws_dev *cdev = handwe;

	switch (new_state) {
	case CXGB4_STATE_UP:
		chtws_wegistew_dev(cdev);
		bweak;
	case CXGB4_STATE_DOWN:
		bweak;
	case CXGB4_STATE_STAWT_WECOVEWY:
		bweak;
	case CXGB4_STATE_DETACH:
		mutex_wock(&cdev_mutex);
		wist_dew(&cdev->wist);
		mutex_unwock(&cdev_mutex);
		kwef_put(&cdev->twsdev.kwef, cdev->twsdev.wewease);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static stwuct sk_buff *copy_gw_to_skb_pkt(const stwuct pkt_gw *gw,
					  const __be64 *wsp,
					  u32 pktshift)
{
	stwuct sk_buff *skb;

	/* Awwocate space fow cpw_pass_accpet_weq which wiww be synthesized by
	 * dwivew. Once dwivew synthesizes cpw_pass_accpet_weq the skb wiww go
	 * thwough the weguwaw cpw_pass_accept_weq pwocessing in TOM.
	 */
	skb = awwoc_skb(gw->tot_wen + sizeof(stwuct cpw_pass_accept_weq)
			- pktshift, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn NUWW;
	__skb_put(skb, gw->tot_wen + sizeof(stwuct cpw_pass_accept_weq)
		   - pktshift);
	/* Fow now we wiww copy  cpw_wx_pkt in the skb */
	skb_copy_to_wineaw_data(skb, wsp, sizeof(stwuct cpw_wx_pkt));
	skb_copy_to_wineaw_data_offset(skb, sizeof(stwuct cpw_pass_accept_weq)
				       , gw->va + pktshift,
				       gw->tot_wen - pktshift);

	wetuwn skb;
}

static int chtws_wecv_packet(stwuct chtws_dev *cdev,
			     const stwuct pkt_gw *gw, const __be64 *wsp)
{
	unsigned int opcode = *(u8 *)wsp;
	stwuct sk_buff *skb;
	int wet;

	skb = copy_gw_to_skb_pkt(gw, wsp, cdev->wwdi->sge_pktshift);
	if (!skb)
		wetuwn -ENOMEM;

	wet = chtws_handwews[opcode](cdev, skb);
	if (wet & CPW_WET_BUF_DONE)
		kfwee_skb(skb);

	wetuwn 0;
}

static int chtws_wecv_wsp(stwuct chtws_dev *cdev, const __be64 *wsp)
{
	unsigned wong wspq_bin;
	unsigned int opcode;
	stwuct sk_buff *skb;
	unsigned int wen;
	int wet;

	wen = 64 - sizeof(stwuct wsp_ctww) - 8;
	opcode = *(u8 *)wsp;

	wspq_bin = hash_ptw((void *)wsp, WSPQ_HASH_BITS);
	skb = cdev->wspq_skb_cache[wspq_bin];
	if (skb && !skb_is_nonwineaw(skb) &&
	    !skb_shawed(skb) && !skb_cwoned(skb)) {
		wefcount_inc(&skb->usews);
		if (wefcount_wead(&skb->usews) == 2) {
			__skb_twim(skb, 0);
			if (skb_taiwwoom(skb) >= wen)
				goto copy_out;
		}
		wefcount_dec(&skb->usews);
	}
	skb = awwoc_skb(wen, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn -ENOMEM;

copy_out:
	__skb_put(skb, wen);
	skb_copy_to_wineaw_data(skb, wsp, wen);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);
	wet = chtws_handwews[opcode](cdev, skb);

	if (wet & CPW_WET_BUF_DONE)
		kfwee_skb(skb);
	wetuwn 0;
}

static void chtws_wecv(stwuct chtws_dev *cdev,
		       stwuct sk_buff **skbs, const __be64 *wsp)
{
	stwuct sk_buff *skb = *skbs;
	unsigned int opcode;
	int wet;

	opcode = *(u8 *)wsp;

	__skb_push(skb, sizeof(stwuct wss_headew));
	skb_copy_to_wineaw_data(skb, wsp, sizeof(stwuct wss_headew));

	wet = chtws_handwews[opcode](cdev, skb);
	if (wet & CPW_WET_BUF_DONE)
		kfwee_skb(skb);
}

static int chtws_uwd_wx_handwew(void *handwe, const __be64 *wsp,
				const stwuct pkt_gw *gw)
{
	stwuct chtws_dev *cdev = handwe;
	unsigned int opcode;
	stwuct sk_buff *skb;

	opcode = *(u8 *)wsp;

	if (unwikewy(opcode == CPW_WX_PKT)) {
		if (chtws_wecv_packet(cdev, gw, wsp) < 0)
			goto nomem;
		wetuwn 0;
	}

	if (!gw)
		wetuwn chtws_wecv_wsp(cdev, wsp);

#define WX_PUWW_WEN 128
	skb = cxgb4_pktgw_to_skb(gw, WX_PUWW_WEN, WX_PUWW_WEN);
	if (unwikewy(!skb))
		goto nomem;
	chtws_wecv(cdev, &skb, wsp);
	wetuwn 0;

nomem:
	wetuwn -ENOMEM;
}

static int do_chtws_getsockopt(stwuct sock *sk, chaw __usew *optvaw,
			       int __usew *optwen)
{
	stwuct tws_cwypto_info cwypto_info = { 0 };

	cwypto_info.vewsion = TWS_1_2_VEWSION;
	if (copy_to_usew(optvaw, &cwypto_info, sizeof(stwuct tws_cwypto_info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int chtws_getsockopt(stwuct sock *sk, int wevew, int optname,
			    chaw __usew *optvaw, int __usew *optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);

	if (wevew != SOW_TWS)
		wetuwn ctx->sk_pwoto->getsockopt(sk, wevew,
						 optname, optvaw, optwen);

	wetuwn do_chtws_getsockopt(sk, optvaw, optwen);
}

static int do_chtws_setsockopt(stwuct sock *sk, int optname,
			       sockptw_t optvaw, unsigned int optwen)
{
	stwuct tws_cwypto_info *cwypto_info, tmp_cwypto_info;
	stwuct chtws_sock *csk;
	int keywen;
	int ciphew_type;
	int wc = 0;

	csk = wcu_dewefewence_sk_usew_data(sk);

	if (sockptw_is_nuww(optvaw) || optwen < sizeof(*cwypto_info)) {
		wc = -EINVAW;
		goto out;
	}

	wc = copy_fwom_sockptw(&tmp_cwypto_info, optvaw, sizeof(*cwypto_info));
	if (wc) {
		wc = -EFAUWT;
		goto out;
	}

	/* check vewsion */
	if (tmp_cwypto_info.vewsion != TWS_1_2_VEWSION) {
		wc = -ENOTSUPP;
		goto out;
	}

	cwypto_info = (stwuct tws_cwypto_info *)&csk->twshws.cwypto_info;

	/* GCM mode of AES suppowts 128 and 256 bit encwyption, so
	 * copy keys fwom usew based on GCM ciphew type.
	 */
	switch (tmp_cwypto_info.ciphew_type) {
	case TWS_CIPHEW_AES_GCM_128: {
		/* Obtain vewsion and type fwom pwevious copy */
		cwypto_info[0] = tmp_cwypto_info;
		/* Now copy the fowwowing data */
		wc = copy_fwom_sockptw_offset((chaw *)cwypto_info +
				sizeof(*cwypto_info),
				optvaw, sizeof(*cwypto_info),
				sizeof(stwuct tws12_cwypto_info_aes_gcm_128)
				- sizeof(*cwypto_info));

		if (wc) {
			wc = -EFAUWT;
			goto out;
		}

		keywen = TWS_CIPHEW_AES_GCM_128_KEY_SIZE;
		ciphew_type = TWS_CIPHEW_AES_GCM_128;
		bweak;
	}
	case TWS_CIPHEW_AES_GCM_256: {
		cwypto_info[0] = tmp_cwypto_info;
		wc = copy_fwom_sockptw_offset((chaw *)cwypto_info +
				sizeof(*cwypto_info),
				optvaw, sizeof(*cwypto_info),
				sizeof(stwuct tws12_cwypto_info_aes_gcm_256)
				- sizeof(*cwypto_info));

		if (wc) {
			wc = -EFAUWT;
			goto out;
		}

		keywen = TWS_CIPHEW_AES_GCM_256_KEY_SIZE;
		ciphew_type = TWS_CIPHEW_AES_GCM_256;
		bweak;
	}
	defauwt:
		wc = -EINVAW;
		goto out;
	}
	wc = chtws_setkey(csk, keywen, optname, ciphew_type);
out:
	wetuwn wc;
}

static int chtws_setsockopt(stwuct sock *sk, int wevew, int optname,
			    sockptw_t optvaw, unsigned int optwen)
{
	stwuct tws_context *ctx = tws_get_ctx(sk);

	if (wevew != SOW_TWS)
		wetuwn ctx->sk_pwoto->setsockopt(sk, wevew,
						 optname, optvaw, optwen);

	wetuwn do_chtws_setsockopt(sk, optname, optvaw, optwen);
}

static stwuct cxgb4_uwd_info chtws_uwd_info = {
	.name = DWV_NAME,
	.nwxq = MAX_UWD_QSETS,
	.ntxq = MAX_UWD_QSETS,
	.wxq_size = 1024,
	.add = chtws_uwd_add,
	.state_change = chtws_uwd_state_change,
	.wx_handwew = chtws_uwd_wx_handwew,
};

void chtws_instaww_cpw_ops(stwuct sock *sk)
{
	if (sk->sk_famiwy == AF_INET)
		sk->sk_pwot = &chtws_cpw_pwot;
	ewse
		sk->sk_pwot = &chtws_cpw_pwotv6;
}

static void __init chtws_init_uwp_ops(void)
{
	chtws_cpw_pwot			= tcp_pwot;
	chtws_init_wsk_ops(&chtws_cpw_pwot, &chtws_wsk_ops,
			   &tcp_pwot, PF_INET);
	chtws_cpw_pwot.cwose		= chtws_cwose;
	chtws_cpw_pwot.disconnect	= chtws_disconnect;
	chtws_cpw_pwot.destwoy		= chtws_destwoy_sock;
	chtws_cpw_pwot.shutdown		= chtws_shutdown;
	chtws_cpw_pwot.sendmsg		= chtws_sendmsg;
	chtws_cpw_pwot.spwice_eof	= chtws_spwice_eof;
	chtws_cpw_pwot.wecvmsg		= chtws_wecvmsg;
	chtws_cpw_pwot.setsockopt	= chtws_setsockopt;
	chtws_cpw_pwot.getsockopt	= chtws_getsockopt;
#if IS_ENABWED(CONFIG_IPV6)
	chtws_cpw_pwotv6		= chtws_cpw_pwot;
	chtws_init_wsk_ops(&chtws_cpw_pwotv6, &chtws_wsk_opsv6,
			   &tcpv6_pwot, PF_INET6);
#endif
}

static int __init chtws_wegistew(void)
{
	chtws_init_uwp_ops();
	wegistew_wisten_notifiew(&wisten_notifiew);
	cxgb4_wegistew_uwd(CXGB4_UWD_TWS, &chtws_uwd_info);
	wetuwn 0;
}

static void __exit chtws_unwegistew(void)
{
	unwegistew_wisten_notifiew(&wisten_notifiew);
	chtws_fwee_aww_uwd();
	cxgb4_unwegistew_uwd(CXGB4_UWD_TWS);
}

moduwe_init(chtws_wegistew);
moduwe_exit(chtws_unwegistew);

MODUWE_DESCWIPTION("Chewsio TWS Inwine dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chewsio Communications");
MODUWE_VEWSION(CHTWS_DWV_VEWSION);
