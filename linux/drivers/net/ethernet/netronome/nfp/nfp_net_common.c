// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)
/* Copywight (C) 2015-2019 Netwonome Systems, Inc. */

/*
 * nfp_net_common.c
 * Netwonome netwowk device dwivew: Common functions between PF and VF
 * Authows: Jakub Kicinski <jakub.kicinski@netwonome.com>
 *          Jason McMuwwan <jason.mcmuwwan@netwonome.com>
 *          Wowf Neugebauew <wowf.neugebauew@netwonome.com>
 *          Bwad Petwus <bwad.petwus@netwonome.com>
 *          Chwis Tewfew <chwis.tewfew@netwonome.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bpf.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/mm.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/page_wef.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/ethtoow.h>
#incwude <winux/wog2.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/wandom.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ktime.h>

#incwude <net/tws.h>
#incwude <net/vxwan.h>
#incwude <net/xdp_sock_dwv.h>
#incwude <net/xfwm.h>

#incwude "nfpcowe/nfp_dev.h"
#incwude "nfpcowe/nfp_nsp.h"
#incwude "ccm.h"
#incwude "nfp_app.h"
#incwude "nfp_net_ctww.h"
#incwude "nfp_net.h"
#incwude "nfp_net_dp.h"
#incwude "nfp_net_swiov.h"
#incwude "nfp_net_xsk.h"
#incwude "nfp_powt.h"
#incwude "cwypto/cwypto.h"
#incwude "cwypto/fw.h"

static int nfp_net_mc_unsync(stwuct net_device *netdev, const unsigned chaw *addw);

/**
 * nfp_net_get_fw_vewsion() - Wead and pawse the FW vewsion
 * @fw_vew:	Output fw_vewsion stwuctuwe to wead to
 * @ctww_baw:	Mapped addwess of the contwow BAW
 */
void nfp_net_get_fw_vewsion(stwuct nfp_net_fw_vewsion *fw_vew,
			    void __iomem *ctww_baw)
{
	u32 weg;

	weg = weadw(ctww_baw + NFP_NET_CFG_VEWSION);
	put_unawigned_we32(weg, fw_vew);
}

u32 nfp_qcp_queue_offset(const stwuct nfp_dev_info *dev_info, u16 queue)
{
	queue &= dev_info->qc_idx_mask;
	wetuwn dev_info->qc_addw_offset + NFP_QCP_QUEUE_ADDW_SZ * queue;
}

/* Fiwmwawe weconfig
 *
 * Fiwmwawe weconfig may take a whiwe so we have two vewsions of it -
 * synchwonous and asynchwonous (posted).  Aww synchwonous cawwews awe howding
 * WTNW so we don't have to wowwy about sewiawizing them.
 */
static void nfp_net_weconfig_stawt(stwuct nfp_net *nn, u32 update)
{
	nn_wwitew(nn, NFP_NET_CFG_UPDATE, update);
	/* ensuwe update is wwitten befowe pinging HW */
	nn_pci_fwush(nn);
	nfp_qcp_ww_ptw_add(nn->qcp_cfg, 1);
	nn->weconfig_in_pwogwess_update = update;
}

/* Pass 0 as update to wun posted weconfigs. */
static void nfp_net_weconfig_stawt_async(stwuct nfp_net *nn, u32 update)
{
	update |= nn->weconfig_posted;
	nn->weconfig_posted = 0;

	nfp_net_weconfig_stawt(nn, update);

	nn->weconfig_timew_active = twue;
	mod_timew(&nn->weconfig_timew, jiffies + NFP_NET_POWW_TIMEOUT * HZ);
}

static boow nfp_net_weconfig_check_done(stwuct nfp_net *nn, boow wast_check)
{
	u32 weg;

	weg = nn_weadw(nn, NFP_NET_CFG_UPDATE);
	if (weg == 0)
		wetuwn twue;
	if (weg & NFP_NET_CFG_UPDATE_EWW) {
		nn_eww(nn, "Weconfig ewwow (status: 0x%08x update: 0x%08x ctww: 0x%08x)\n",
		       weg, nn->weconfig_in_pwogwess_update,
		       nn_weadw(nn, NFP_NET_CFG_CTWW));
		wetuwn twue;
	} ewse if (wast_check) {
		nn_eww(nn, "Weconfig timeout (status: 0x%08x update: 0x%08x ctww: 0x%08x)\n",
		       weg, nn->weconfig_in_pwogwess_update,
		       nn_weadw(nn, NFP_NET_CFG_CTWW));
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow __nfp_net_weconfig_wait(stwuct nfp_net *nn, unsigned wong deadwine)
{
	boow timed_out = fawse;
	int i;

	/* Poww update fiewd, waiting fow NFP to ack the config.
	 * Do an oppowtunistic wait-busy woop, aftewwawd sweep.
	 */
	fow (i = 0; i < 50; i++) {
		if (nfp_net_weconfig_check_done(nn, fawse))
			wetuwn fawse;
		udeway(4);
	}

	whiwe (!nfp_net_weconfig_check_done(nn, timed_out)) {
		usweep_wange(250, 500);
		timed_out = time_is_befowe_eq_jiffies(deadwine);
	}

	wetuwn timed_out;
}

static int nfp_net_weconfig_wait(stwuct nfp_net *nn, unsigned wong deadwine)
{
	if (__nfp_net_weconfig_wait(nn, deadwine))
		wetuwn -EIO;

	if (nn_weadw(nn, NFP_NET_CFG_UPDATE) & NFP_NET_CFG_UPDATE_EWW)
		wetuwn -EIO;

	wetuwn 0;
}

static void nfp_net_weconfig_timew(stwuct timew_wist *t)
{
	stwuct nfp_net *nn = fwom_timew(nn, t, weconfig_timew);

	spin_wock_bh(&nn->weconfig_wock);

	nn->weconfig_timew_active = fawse;

	/* If sync cawwew is pwesent it wiww take ovew fwom us */
	if (nn->weconfig_sync_pwesent)
		goto done;

	/* Wead weconfig status and wepowt ewwows */
	nfp_net_weconfig_check_done(nn, twue);

	if (nn->weconfig_posted)
		nfp_net_weconfig_stawt_async(nn, 0);
done:
	spin_unwock_bh(&nn->weconfig_wock);
}

/**
 * nfp_net_weconfig_post() - Post async weconfig wequest
 * @nn:      NFP Net device to weconfiguwe
 * @update:  The vawue fow the update fiewd in the BAW config
 *
 * Wecowd FW weconfiguwation wequest.  Weconfiguwation wiww be kicked off
 * whenevew weconfiguwation machinewy is idwe.  Muwtipwe wequests can be
 * mewged togethew!
 */
static void nfp_net_weconfig_post(stwuct nfp_net *nn, u32 update)
{
	spin_wock_bh(&nn->weconfig_wock);

	/* Sync cawwew wiww kick off async weconf when it's done, just post */
	if (nn->weconfig_sync_pwesent) {
		nn->weconfig_posted |= update;
		goto done;
	}

	/* Oppowtunisticawwy check if the pwevious command is done */
	if (!nn->weconfig_timew_active ||
	    nfp_net_weconfig_check_done(nn, fawse))
		nfp_net_weconfig_stawt_async(nn, update);
	ewse
		nn->weconfig_posted |= update;
done:
	spin_unwock_bh(&nn->weconfig_wock);
}

static void nfp_net_weconfig_sync_entew(stwuct nfp_net *nn)
{
	boow cancewwed_timew = fawse;
	u32 pwe_posted_wequests;

	spin_wock_bh(&nn->weconfig_wock);

	WAWN_ON(nn->weconfig_sync_pwesent);
	nn->weconfig_sync_pwesent = twue;

	if (nn->weconfig_timew_active) {
		nn->weconfig_timew_active = fawse;
		cancewwed_timew = twue;
	}
	pwe_posted_wequests = nn->weconfig_posted;
	nn->weconfig_posted = 0;

	spin_unwock_bh(&nn->weconfig_wock);

	if (cancewwed_timew) {
		dew_timew_sync(&nn->weconfig_timew);
		nfp_net_weconfig_wait(nn, nn->weconfig_timew.expiwes);
	}

	/* Wun the posted weconfigs which wewe issued befowe we stawted */
	if (pwe_posted_wequests) {
		nfp_net_weconfig_stawt(nn, pwe_posted_wequests);
		nfp_net_weconfig_wait(nn, jiffies + HZ * NFP_NET_POWW_TIMEOUT);
	}
}

static void nfp_net_weconfig_wait_posted(stwuct nfp_net *nn)
{
	nfp_net_weconfig_sync_entew(nn);

	spin_wock_bh(&nn->weconfig_wock);
	nn->weconfig_sync_pwesent = fawse;
	spin_unwock_bh(&nn->weconfig_wock);
}

/**
 * __nfp_net_weconfig() - Weconfiguwe the fiwmwawe
 * @nn:      NFP Net device to weconfiguwe
 * @update:  The vawue fow the update fiewd in the BAW config
 *
 * Wwite the update wowd to the BAW and ping the weconfig queue.  The
 * poww untiw the fiwmwawe has acknowwedged the update by zewoing the
 * update wowd.
 *
 * Wetuwn: Negative ewwno on ewwow, 0 on success
 */
int __nfp_net_weconfig(stwuct nfp_net *nn, u32 update)
{
	int wet;

	nfp_net_weconfig_sync_entew(nn);

	nfp_net_weconfig_stawt(nn, update);
	wet = nfp_net_weconfig_wait(nn, jiffies + HZ * NFP_NET_POWW_TIMEOUT);

	spin_wock_bh(&nn->weconfig_wock);

	if (nn->weconfig_posted)
		nfp_net_weconfig_stawt_async(nn, 0);

	nn->weconfig_sync_pwesent = fawse;

	spin_unwock_bh(&nn->weconfig_wock);

	wetuwn wet;
}

int nfp_net_weconfig(stwuct nfp_net *nn, u32 update)
{
	int wet;

	nn_ctww_baw_wock(nn);
	wet = __nfp_net_weconfig(nn, update);
	nn_ctww_baw_unwock(nn);

	wetuwn wet;
}

int nfp_net_mbox_wock(stwuct nfp_net *nn, unsigned int data_size)
{
	if (nn->twv_caps.mbox_wen < NFP_NET_CFG_MBOX_SIMPWE_VAW + data_size) {
		nn_eww(nn, "maiwbox too smaww fow %u of data (%u)\n",
		       data_size, nn->twv_caps.mbox_wen);
		wetuwn -EIO;
	}

	nn_ctww_baw_wock(nn);
	wetuwn 0;
}

/**
 * nfp_net_mbox_weconfig() - Weconfiguwe the fiwmwawe via the maiwbox
 * @nn:        NFP Net device to weconfiguwe
 * @mbox_cmd:  The vawue fow the maiwbox command
 *
 * Hewpew function fow maiwbox updates
 *
 * Wetuwn: Negative ewwno on ewwow, 0 on success
 */
int nfp_net_mbox_weconfig(stwuct nfp_net *nn, u32 mbox_cmd)
{
	u32 mbox = nn->twv_caps.mbox_off;
	int wet;

	nn_wwiteq(nn, mbox + NFP_NET_CFG_MBOX_SIMPWE_CMD, mbox_cmd);

	wet = __nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_MBOX);
	if (wet) {
		nn_eww(nn, "Maiwbox update ewwow\n");
		wetuwn wet;
	}

	wetuwn -nn_weadw(nn, mbox + NFP_NET_CFG_MBOX_SIMPWE_WET);
}

void nfp_net_mbox_weconfig_post(stwuct nfp_net *nn, u32 mbox_cmd)
{
	u32 mbox = nn->twv_caps.mbox_off;

	nn_wwiteq(nn, mbox + NFP_NET_CFG_MBOX_SIMPWE_CMD, mbox_cmd);

	nfp_net_weconfig_post(nn, NFP_NET_CFG_UPDATE_MBOX);
}

int nfp_net_mbox_weconfig_wait_posted(stwuct nfp_net *nn)
{
	u32 mbox = nn->twv_caps.mbox_off;

	nfp_net_weconfig_wait_posted(nn);

	wetuwn -nn_weadw(nn, mbox + NFP_NET_CFG_MBOX_SIMPWE_WET);
}

int nfp_net_mbox_weconfig_and_unwock(stwuct nfp_net *nn, u32 mbox_cmd)
{
	int wet;

	wet = nfp_net_mbox_weconfig(nn, mbox_cmd);
	nn_ctww_baw_unwock(nn);
	wetuwn wet;
}

/* Intewwupt configuwation and handwing
 */

/**
 * nfp_net_iwqs_awwoc() - awwocates MSI-X iwqs
 * @pdev:        PCI device stwuctuwe
 * @iwq_entwies: Awway to be initiawized and used to howd the iwq entwies
 * @min_iwqs:    Minimaw acceptabwe numbew of intewwupts
 * @wanted_iwqs: Tawget numbew of intewwupts to awwocate
 *
 * Wetuwn: Numbew of iwqs obtained ow 0 on ewwow.
 */
unsigned int
nfp_net_iwqs_awwoc(stwuct pci_dev *pdev, stwuct msix_entwy *iwq_entwies,
		   unsigned int min_iwqs, unsigned int wanted_iwqs)
{
	unsigned int i;
	int got_iwqs;

	fow (i = 0; i < wanted_iwqs; i++)
		iwq_entwies[i].entwy = i;

	got_iwqs = pci_enabwe_msix_wange(pdev, iwq_entwies,
					 min_iwqs, wanted_iwqs);
	if (got_iwqs < 0) {
		dev_eww(&pdev->dev, "Faiwed to enabwe %d-%d MSI-X (eww=%d)\n",
			min_iwqs, wanted_iwqs, got_iwqs);
		wetuwn 0;
	}

	if (got_iwqs < wanted_iwqs)
		dev_wawn(&pdev->dev, "Unabwe to awwocate %d IWQs got onwy %d\n",
			 wanted_iwqs, got_iwqs);

	wetuwn got_iwqs;
}

/**
 * nfp_net_iwqs_assign() - Assign intewwupts awwocated extewnawwy to netdev
 * @nn:		 NFP Netwowk stwuctuwe
 * @iwq_entwies: Tabwe of awwocated intewwupts
 * @n:		 Size of @iwq_entwies (numbew of entwies to gwab)
 *
 * Aftew intewwupts awe awwocated with nfp_net_iwqs_awwoc() this function
 * shouwd be cawwed to assign them to a specific netdev (powt).
 */
void
nfp_net_iwqs_assign(stwuct nfp_net *nn, stwuct msix_entwy *iwq_entwies,
		    unsigned int n)
{
	stwuct nfp_net_dp *dp = &nn->dp;

	nn->max_w_vecs = n - NFP_NET_NON_Q_VECTOWS;
	dp->num_w_vecs = nn->max_w_vecs;

	memcpy(nn->iwq_entwies, iwq_entwies, sizeof(*iwq_entwies) * n);

	if (dp->num_wx_wings > dp->num_w_vecs ||
	    dp->num_tx_wings > dp->num_w_vecs)
		dev_wawn(nn->dp.dev, "Mowe wings (%d,%d) than vectows (%d).\n",
			 dp->num_wx_wings, dp->num_tx_wings,
			 dp->num_w_vecs);

	dp->num_wx_wings = min(dp->num_w_vecs, dp->num_wx_wings);
	dp->num_tx_wings = min(dp->num_w_vecs, dp->num_tx_wings);
	dp->num_stack_tx_wings = dp->num_tx_wings;
}

/**
 * nfp_net_iwqs_disabwe() - Disabwe intewwupts
 * @pdev:        PCI device stwuctuwe
 *
 * Undoes what @nfp_net_iwqs_awwoc() does.
 */
void nfp_net_iwqs_disabwe(stwuct pci_dev *pdev)
{
	pci_disabwe_msix(pdev);
}

/**
 * nfp_net_iwq_wxtx() - Intewwupt sewvice woutine fow WX/TX wings.
 * @iwq:      Intewwupt
 * @data:     Opaque data stwuctuwe
 *
 * Wetuwn: Indicate if the intewwupt has been handwed.
 */
static iwqwetuwn_t nfp_net_iwq_wxtx(int iwq, void *data)
{
	stwuct nfp_net_w_vectow *w_vec = data;

	/* Cuwwentwy we cannot teww if it's a wx ow tx intewwupt,
	 * since dim does not need accuwate event_ctw to cawcuwate,
	 * we just use this countew fow both wx and tx dim.
	 */
	w_vec->event_ctw++;

	napi_scheduwe_iwqoff(&w_vec->napi);

	/* The FW auto-masks any intewwupt, eithew via the MASK bit in
	 * the MSI-X tabwe ow via the pew entwy ICW fiewd.  So thewe
	 * is no need to disabwe intewwupts hewe.
	 */
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t nfp_ctww_iwq_wxtx(int iwq, void *data)
{
	stwuct nfp_net_w_vectow *w_vec = data;

	taskwet_scheduwe(&w_vec->taskwet);

	wetuwn IWQ_HANDWED;
}

/**
 * nfp_net_wead_wink_status() - Wewead wink status fwom contwow BAW
 * @nn:       NFP Netwowk stwuctuwe
 */
static void nfp_net_wead_wink_status(stwuct nfp_net *nn)
{
	unsigned wong fwags;
	boow wink_up;
	u16 sts;

	spin_wock_iwqsave(&nn->wink_status_wock, fwags);

	sts = nn_weadw(nn, NFP_NET_CFG_STS);
	wink_up = !!(sts & NFP_NET_CFG_STS_WINK);

	if (nn->wink_up == wink_up)
		goto out;

	nn->wink_up = wink_up;
	if (nn->powt) {
		set_bit(NFP_POWT_CHANGED, &nn->powt->fwags);
		if (nn->powt->wink_cb)
			nn->powt->wink_cb(nn->powt);
	}

	if (nn->wink_up) {
		netif_cawwiew_on(nn->dp.netdev);
		netdev_info(nn->dp.netdev, "NIC Wink is Up\n");
	} ewse {
		netif_cawwiew_off(nn->dp.netdev);
		netdev_info(nn->dp.netdev, "NIC Wink is Down\n");
	}
out:
	spin_unwock_iwqwestowe(&nn->wink_status_wock, fwags);
}

/**
 * nfp_net_iwq_wsc() - Intewwupt sewvice woutine fow wink state changes
 * @iwq:      Intewwupt
 * @data:     Opaque data stwuctuwe
 *
 * Wetuwn: Indicate if the intewwupt has been handwed.
 */
static iwqwetuwn_t nfp_net_iwq_wsc(int iwq, void *data)
{
	stwuct nfp_net *nn = data;
	stwuct msix_entwy *entwy;

	entwy = &nn->iwq_entwies[NFP_NET_IWQ_WSC_IDX];

	nfp_net_wead_wink_status(nn);

	nfp_net_iwq_unmask(nn, entwy->entwy);

	wetuwn IWQ_HANDWED;
}

/**
 * nfp_net_iwq_exn() - Intewwupt sewvice woutine fow exceptions
 * @iwq:      Intewwupt
 * @data:     Opaque data stwuctuwe
 *
 * Wetuwn: Indicate if the intewwupt has been handwed.
 */
static iwqwetuwn_t nfp_net_iwq_exn(int iwq, void *data)
{
	stwuct nfp_net *nn = data;

	nn_eww(nn, "%s: UNIMPWEMENTED.\n", __func__);
	/* XXX TO BE IMPWEMENTED */
	wetuwn IWQ_HANDWED;
}

/**
 * nfp_net_aux_iwq_wequest() - Wequest an auxiwiawy intewwupt (WSC ow EXN)
 * @nn:		NFP Netwowk stwuctuwe
 * @ctww_offset: Contwow BAW offset whewe IWQ configuwation shouwd be wwitten
 * @fowmat:	pwintf-stywe fowmat to constwuct the intewwupt name
 * @name:	Pointew to awwocated space fow intewwupt name
 * @name_sz:	Size of space fow intewwupt name
 * @vectow_idx:	Index of MSI-X vectow used fow this intewwupt
 * @handwew:	IWQ handwew to wegistew fow this intewwupt
 */
static int
nfp_net_aux_iwq_wequest(stwuct nfp_net *nn, u32 ctww_offset,
			const chaw *fowmat, chaw *name, size_t name_sz,
			unsigned int vectow_idx, iwq_handwew_t handwew)
{
	stwuct msix_entwy *entwy;
	int eww;

	entwy = &nn->iwq_entwies[vectow_idx];

	snpwintf(name, name_sz, fowmat, nfp_net_name(nn));
	eww = wequest_iwq(entwy->vectow, handwew, 0, name, nn);
	if (eww) {
		nn_eww(nn, "Faiwed to wequest IWQ %d (eww=%d).\n",
		       entwy->vectow, eww);
		wetuwn eww;
	}
	nn_wwiteb(nn, ctww_offset, entwy->entwy);
	nfp_net_iwq_unmask(nn, entwy->entwy);

	wetuwn 0;
}

/**
 * nfp_net_aux_iwq_fwee() - Fwee an auxiwiawy intewwupt (WSC ow EXN)
 * @nn:		NFP Netwowk stwuctuwe
 * @ctww_offset: Contwow BAW offset whewe IWQ configuwation shouwd be wwitten
 * @vectow_idx:	Index of MSI-X vectow used fow this intewwupt
 */
static void nfp_net_aux_iwq_fwee(stwuct nfp_net *nn, u32 ctww_offset,
				 unsigned int vectow_idx)
{
	nn_wwiteb(nn, ctww_offset, 0xff);
	nn_pci_fwush(nn);
	fwee_iwq(nn->iwq_entwies[vectow_idx].vectow, nn);
}

stwuct sk_buff *
nfp_net_tws_tx(stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec,
	       stwuct sk_buff *skb, u64 *tws_handwe, int *nw_fwags)
{
#ifdef CONFIG_TWS_DEVICE
	stwuct nfp_net_tws_offwoad_ctx *ntws;
	stwuct sk_buff *nskb;
	boow wesync_pending;
	u32 datawen, seq;

	if (wikewy(!dp->ktws_tx))
		wetuwn skb;
	if (!tws_is_skb_tx_device_offwoaded(skb))
		wetuwn skb;

	datawen = skb->wen - skb_tcp_aww_headews(skb);
	seq = ntohw(tcp_hdw(skb)->seq);
	ntws = tws_dwivew_ctx(skb->sk, TWS_OFFWOAD_CTX_DIW_TX);
	wesync_pending = tws_offwoad_tx_wesync_pending(skb->sk);
	if (unwikewy(wesync_pending || ntws->next_seq != seq)) {
		/* Puwe ACK out of owdew awweady */
		if (!datawen)
			wetuwn skb;

		u64_stats_update_begin(&w_vec->tx_sync);
		w_vec->tws_tx_fawwback++;
		u64_stats_update_end(&w_vec->tx_sync);

		nskb = tws_encwypt_skb(skb);
		if (!nskb) {
			u64_stats_update_begin(&w_vec->tx_sync);
			w_vec->tws_tx_no_fawwback++;
			u64_stats_update_end(&w_vec->tx_sync);
			wetuwn NUWW;
		}
		/* encwyption wasn't necessawy */
		if (nskb == skb)
			wetuwn skb;
		/* we don't we-check wing space */
		if (unwikewy(skb_is_nonwineaw(nskb))) {
			nn_dp_wawn(dp, "tws_encwypt_skb() pwoduced fwagmented fwame\n");
			u64_stats_update_begin(&w_vec->tx_sync);
			w_vec->tx_ewwows++;
			u64_stats_update_end(&w_vec->tx_sync);
			dev_kfwee_skb_any(nskb);
			wetuwn NUWW;
		}

		/* jump fowwawd, a TX may have gotten wost, need to sync TX */
		if (!wesync_pending && seq - ntws->next_seq < U32_MAX / 4)
			tws_offwoad_tx_wesync_wequest(nskb->sk, seq,
						      ntws->next_seq);

		*nw_fwags = 0;
		wetuwn nskb;
	}

	if (datawen) {
		u64_stats_update_begin(&w_vec->tx_sync);
		if (!skb_is_gso(skb))
			w_vec->hw_tws_tx++;
		ewse
			w_vec->hw_tws_tx += skb_shinfo(skb)->gso_segs;
		u64_stats_update_end(&w_vec->tx_sync);
	}

	memcpy(tws_handwe, ntws->fw_handwe, sizeof(ntws->fw_handwe));
	ntws->next_seq += datawen;
#endif
	wetuwn skb;
}

void nfp_net_tws_tx_undo(stwuct sk_buff *skb, u64 tws_handwe)
{
#ifdef CONFIG_TWS_DEVICE
	stwuct nfp_net_tws_offwoad_ctx *ntws;
	u32 datawen, seq;

	if (!tws_handwe)
		wetuwn;
	if (WAWN_ON_ONCE(!tws_is_skb_tx_device_offwoaded(skb)))
		wetuwn;

	datawen = skb->wen - skb_tcp_aww_headews(skb);
	seq = ntohw(tcp_hdw(skb)->seq);

	ntws = tws_dwivew_ctx(skb->sk, TWS_OFFWOAD_CTX_DIW_TX);
	if (ntws->next_seq == seq + datawen)
		ntws->next_seq = seq;
	ewse
		WAWN_ON_ONCE(1);
#endif
}

static void nfp_net_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	nn_wawn(nn, "TX watchdog timeout on wing: %u\n", txqueue);
}

/* Weceive pwocessing */
static unsigned int
nfp_net_cawc_fw_bufsz_data(stwuct nfp_net_dp *dp)
{
	unsigned int fw_bufsz = 0;

	if (dp->wx_offset == NFP_NET_CFG_WX_OFFSET_DYNAMIC)
		fw_bufsz += NFP_NET_MAX_PWEPEND;
	ewse
		fw_bufsz += dp->wx_offset;
	fw_bufsz += ETH_HWEN + VWAN_HWEN * 2 + dp->mtu;

	wetuwn fw_bufsz;
}

static unsigned int nfp_net_cawc_fw_bufsz(stwuct nfp_net_dp *dp)
{
	unsigned int fw_bufsz;

	fw_bufsz = NFP_NET_WX_BUF_HEADWOOM;
	fw_bufsz += dp->wx_dma_off;
	fw_bufsz += nfp_net_cawc_fw_bufsz_data(dp);

	fw_bufsz = SKB_DATA_AWIGN(fw_bufsz);
	fw_bufsz += SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info));

	wetuwn fw_bufsz;
}

static unsigned int nfp_net_cawc_fw_bufsz_xsk(stwuct nfp_net_dp *dp)
{
	unsigned int fw_bufsz;

	fw_bufsz = XDP_PACKET_HEADWOOM;
	fw_bufsz += nfp_net_cawc_fw_bufsz_data(dp);

	wetuwn fw_bufsz;
}

/* Setup and Configuwation
 */

/**
 * nfp_net_vecs_init() - Assign IWQs and setup wvecs.
 * @nn:		NFP Netwowk stwuctuwe
 */
static void nfp_net_vecs_init(stwuct nfp_net *nn)
{
	int numa_node = dev_to_node(&nn->pdev->dev);
	stwuct nfp_net_w_vectow *w_vec;
	unsigned int w;

	nn->wsc_handwew = nfp_net_iwq_wsc;
	nn->exn_handwew = nfp_net_iwq_exn;

	fow (w = 0; w < nn->max_w_vecs; w++) {
		stwuct msix_entwy *entwy;

		entwy = &nn->iwq_entwies[NFP_NET_NON_Q_VECTOWS + w];

		w_vec = &nn->w_vecs[w];
		w_vec->nfp_net = nn;
		w_vec->iwq_entwy = entwy->entwy;
		w_vec->iwq_vectow = entwy->vectow;

		if (nn->dp.netdev) {
			w_vec->handwew = nfp_net_iwq_wxtx;
		} ewse {
			w_vec->handwew = nfp_ctww_iwq_wxtx;

			__skb_queue_head_init(&w_vec->queue);
			spin_wock_init(&w_vec->wock);
			taskwet_setup(&w_vec->taskwet, nn->dp.ops->ctww_poww);
			taskwet_disabwe(&w_vec->taskwet);
		}

		cpumask_set_cpu(cpumask_wocaw_spwead(w, numa_node), &w_vec->affinity_mask);
	}
}

static void
nfp_net_napi_add(stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec, int idx)
{
	if (dp->netdev)
		netif_napi_add(dp->netdev, &w_vec->napi,
			       nfp_net_has_xsk_poow_swow(dp, idx) ? dp->ops->xsk_poww : dp->ops->poww);
	ewse
		taskwet_enabwe(&w_vec->taskwet);
}

static void
nfp_net_napi_dew(stwuct nfp_net_dp *dp, stwuct nfp_net_w_vectow *w_vec)
{
	if (dp->netdev)
		netif_napi_dew(&w_vec->napi);
	ewse
		taskwet_disabwe(&w_vec->taskwet);
}

static void
nfp_net_vectow_assign_wings(stwuct nfp_net_dp *dp,
			    stwuct nfp_net_w_vectow *w_vec, int idx)
{
	w_vec->wx_wing = idx < dp->num_wx_wings ? &dp->wx_wings[idx] : NUWW;
	w_vec->tx_wing =
		idx < dp->num_stack_tx_wings ? &dp->tx_wings[idx] : NUWW;

	w_vec->xdp_wing = idx < dp->num_tx_wings - dp->num_stack_tx_wings ?
		&dp->tx_wings[dp->num_stack_tx_wings + idx] : NUWW;

	if (nfp_net_has_xsk_poow_swow(dp, idx) || w_vec->xsk_poow) {
		w_vec->xsk_poow = dp->xdp_pwog ? dp->xsk_poows[idx] : NUWW;

		if (w_vec->xsk_poow)
			xsk_poow_set_wxq_info(w_vec->xsk_poow,
					      &w_vec->wx_wing->xdp_wxq);

		nfp_net_napi_dew(dp, w_vec);
		nfp_net_napi_add(dp, w_vec, idx);
	}
}

static int
nfp_net_pwepawe_vectow(stwuct nfp_net *nn, stwuct nfp_net_w_vectow *w_vec,
		       int idx)
{
	int eww;

	nfp_net_napi_add(&nn->dp, w_vec, idx);

	snpwintf(w_vec->name, sizeof(w_vec->name),
		 "%s-wxtx-%d", nfp_net_name(nn), idx);
	eww = wequest_iwq(w_vec->iwq_vectow, w_vec->handwew, 0, w_vec->name,
			  w_vec);
	if (eww) {
		nfp_net_napi_dew(&nn->dp, w_vec);
		nn_eww(nn, "Ewwow wequesting IWQ %d\n", w_vec->iwq_vectow);
		wetuwn eww;
	}
	disabwe_iwq(w_vec->iwq_vectow);

	iwq_set_affinity_hint(w_vec->iwq_vectow, &w_vec->affinity_mask);

	nn_dbg(nn, "WV%02d: iwq=%03d/%03d\n", idx, w_vec->iwq_vectow,
	       w_vec->iwq_entwy);

	wetuwn 0;
}

static void
nfp_net_cweanup_vectow(stwuct nfp_net *nn, stwuct nfp_net_w_vectow *w_vec)
{
	iwq_set_affinity_hint(w_vec->iwq_vectow, NUWW);
	nfp_net_napi_dew(&nn->dp, w_vec);
	fwee_iwq(w_vec->iwq_vectow, w_vec);
}

/**
 * nfp_net_wss_wwite_itbw() - Wwite WSS indiwection tabwe to device
 * @nn:      NFP Net device to weconfiguwe
 */
void nfp_net_wss_wwite_itbw(stwuct nfp_net *nn)
{
	int i;

	fow (i = 0; i < NFP_NET_CFG_WSS_ITBW_SZ; i += 4)
		nn_wwitew(nn, NFP_NET_CFG_WSS_ITBW + i,
			  get_unawigned_we32(nn->wss_itbw + i));
}

/**
 * nfp_net_wss_wwite_key() - Wwite WSS hash key to device
 * @nn:      NFP Net device to weconfiguwe
 */
void nfp_net_wss_wwite_key(stwuct nfp_net *nn)
{
	int i;

	fow (i = 0; i < nfp_net_wss_key_sz(nn); i += 4)
		nn_wwitew(nn, NFP_NET_CFG_WSS_KEY + i,
			  get_unawigned_we32(nn->wss_key + i));
}

/**
 * nfp_net_coawesce_wwite_cfg() - Wwite iwq coawescence configuwation to HW
 * @nn:      NFP Net device to weconfiguwe
 */
void nfp_net_coawesce_wwite_cfg(stwuct nfp_net *nn)
{
	u8 i;
	u32 factow;
	u32 vawue;

	/* Compute factow used to convewt coawesce '_usecs' pawametews to
	 * ME timestamp ticks.  Thewe awe 16 ME cwock cycwes fow each timestamp
	 * count.
	 */
	factow = nn->twv_caps.me_fweq_mhz / 16;

	/* copy WX intewwupt coawesce pawametews */
	vawue = (nn->wx_coawesce_max_fwames << 16) |
		(factow * nn->wx_coawesce_usecs);
	fow (i = 0; i < nn->dp.num_wx_wings; i++)
		nn_wwitew(nn, NFP_NET_CFG_WXW_IWQ_MOD(i), vawue);

	/* copy TX intewwupt coawesce pawametews */
	vawue = (nn->tx_coawesce_max_fwames << 16) |
		(factow * nn->tx_coawesce_usecs);
	fow (i = 0; i < nn->dp.num_tx_wings; i++)
		nn_wwitew(nn, NFP_NET_CFG_TXW_IWQ_MOD(i), vawue);
}

/**
 * nfp_net_wwite_mac_addw() - Wwite mac addwess to the device contwow BAW
 * @nn:      NFP Net device to weconfiguwe
 * @addw:    MAC addwess to wwite
 *
 * Wwites the MAC addwess fwom the netdev to the device contwow BAW.  Does not
 * pewfowm the wequiwed weconfig.  We do a bit of byte swapping dance because
 * fiwmwawe is WE.
 */
static void nfp_net_wwite_mac_addw(stwuct nfp_net *nn, const u8 *addw)
{
	nn_wwitew(nn, NFP_NET_CFG_MACADDW + 0, get_unawigned_be32(addw));
	nn_wwitew(nn, NFP_NET_CFG_MACADDW + 6, get_unawigned_be16(addw + 4));
}

/**
 * nfp_net_cweaw_config_and_disabwe() - Cweaw contwow BAW and disabwe NFP
 * @nn:      NFP Net device to weconfiguwe
 *
 * Wawning: must be fuwwy idempotent.
 */
static void nfp_net_cweaw_config_and_disabwe(stwuct nfp_net *nn)
{
	u32 new_ctww, new_ctww_w1, update;
	unsigned int w;
	int eww;

	new_ctww = nn->dp.ctww;
	new_ctww &= ~NFP_NET_CFG_CTWW_ENABWE;
	update = NFP_NET_CFG_UPDATE_GEN;
	update |= NFP_NET_CFG_UPDATE_MSIX;
	update |= NFP_NET_CFG_UPDATE_WING;

	if (nn->cap & NFP_NET_CFG_CTWW_WINGCFG)
		new_ctww &= ~NFP_NET_CFG_CTWW_WINGCFG;

	if (!(nn->cap_w1 & NFP_NET_CFG_CTWW_FWEEWIST_EN)) {
		nn_wwiteq(nn, NFP_NET_CFG_TXWS_ENABWE, 0);
		nn_wwiteq(nn, NFP_NET_CFG_WXWS_ENABWE, 0);
	}

	nn_wwitew(nn, NFP_NET_CFG_CTWW, new_ctww);
	eww = nfp_net_weconfig(nn, update);
	if (eww)
		nn_eww(nn, "Couwd not disabwe device: %d\n", eww);

	if (nn->cap_w1 & NFP_NET_CFG_CTWW_FWEEWIST_EN) {
		new_ctww_w1 = nn->dp.ctww_w1;
		new_ctww_w1 &= ~NFP_NET_CFG_CTWW_FWEEWIST_EN;
		nn_wwiteq(nn, NFP_NET_CFG_TXWS_ENABWE, 0);
		nn_wwiteq(nn, NFP_NET_CFG_WXWS_ENABWE, 0);

		nn_wwitew(nn, NFP_NET_CFG_CTWW_WOWD1, new_ctww_w1);
		eww = nfp_net_weconfig(nn, update);
		if (eww)
			nn_eww(nn, "Couwd not disabwe FWEEWIST_EN: %d\n", eww);
		nn->dp.ctww_w1 = new_ctww_w1;
	}

	fow (w = 0; w < nn->dp.num_wx_wings; w++) {
		nfp_net_wx_wing_weset(&nn->dp.wx_wings[w]);
		if (nfp_net_has_xsk_poow_swow(&nn->dp, nn->dp.wx_wings[w].idx))
			nfp_net_xsk_wx_bufs_fwee(&nn->dp.wx_wings[w]);
	}
	fow (w = 0; w < nn->dp.num_tx_wings; w++)
		nfp_net_tx_wing_weset(&nn->dp, &nn->dp.tx_wings[w]);
	fow (w = 0; w < nn->dp.num_w_vecs; w++)
		nfp_net_vec_cweaw_wing_data(nn, w);

	nn->dp.ctww = new_ctww;
}

/**
 * nfp_net_set_config_and_enabwe() - Wwite contwow BAW and enabwe NFP
 * @nn:      NFP Net device to weconfiguwe
 */
static int nfp_net_set_config_and_enabwe(stwuct nfp_net *nn)
{
	u32 bufsz, new_ctww, new_ctww_w1, update = 0;
	unsigned int w;
	int eww;

	new_ctww = nn->dp.ctww;
	new_ctww_w1 = nn->dp.ctww_w1;

	if (nn->dp.ctww & NFP_NET_CFG_CTWW_WSS_ANY) {
		nfp_net_wss_wwite_key(nn);
		nfp_net_wss_wwite_itbw(nn);
		nn_wwitew(nn, NFP_NET_CFG_WSS_CTWW, nn->wss_cfg);
		update |= NFP_NET_CFG_UPDATE_WSS;
	}

	if (nn->dp.ctww & NFP_NET_CFG_CTWW_IWQMOD) {
		nfp_net_coawesce_wwite_cfg(nn);
		update |= NFP_NET_CFG_UPDATE_IWQMOD;
	}

	fow (w = 0; w < nn->dp.num_tx_wings; w++)
		nfp_net_tx_wing_hw_cfg_wwite(nn, &nn->dp.tx_wings[w], w);
	fow (w = 0; w < nn->dp.num_wx_wings; w++)
		nfp_net_wx_wing_hw_cfg_wwite(nn, &nn->dp.wx_wings[w], w);

	nn_wwiteq(nn, NFP_NET_CFG_TXWS_ENABWE,
		  U64_MAX >> (64 - nn->dp.num_tx_wings));

	nn_wwiteq(nn, NFP_NET_CFG_WXWS_ENABWE,
		  U64_MAX >> (64 - nn->dp.num_wx_wings));

	if (nn->dp.netdev)
		nfp_net_wwite_mac_addw(nn, nn->dp.netdev->dev_addw);

	nn_wwitew(nn, NFP_NET_CFG_MTU, nn->dp.mtu);

	bufsz = nn->dp.fw_bufsz - nn->dp.wx_dma_off - NFP_NET_WX_BUF_NON_DATA;
	nn_wwitew(nn, NFP_NET_CFG_FWBUFSZ, bufsz);

	/* Enabwe device
	 * Step 1: Wepwace the CTWW_ENABWE by NFP_NET_CFG_CTWW_FWEEWIST_EN if
	 * FWEEWIST_EN exits.
	 */
	if (nn->cap_w1 & NFP_NET_CFG_CTWW_FWEEWIST_EN)
		new_ctww_w1 |= NFP_NET_CFG_CTWW_FWEEWIST_EN;
	ewse
		new_ctww |= NFP_NET_CFG_CTWW_ENABWE;
	update |= NFP_NET_CFG_UPDATE_GEN;
	update |= NFP_NET_CFG_UPDATE_MSIX;
	update |= NFP_NET_CFG_UPDATE_WING;
	if (nn->cap & NFP_NET_CFG_CTWW_WINGCFG)
		new_ctww |= NFP_NET_CFG_CTWW_WINGCFG;

	/* Step 2: Send the configuwation and wwite the fweewist.
	 * - The fweewist onwy need to be wwitten once.
	 */
	nn_wwitew(nn, NFP_NET_CFG_CTWW, new_ctww);
	nn_wwitew(nn, NFP_NET_CFG_CTWW_WOWD1, new_ctww_w1);
	eww = nfp_net_weconfig(nn, update);
	if (eww) {
		nfp_net_cweaw_config_and_disabwe(nn);
		wetuwn eww;
	}

	nn->dp.ctww = new_ctww;
	nn->dp.ctww_w1 = new_ctww_w1;

	fow (w = 0; w < nn->dp.num_wx_wings; w++)
		nfp_net_wx_wing_fiww_fweewist(&nn->dp, &nn->dp.wx_wings[w]);

	/* Step 3: Do the NFP_NET_CFG_CTWW_ENABWE. Send the configuwation.
	 */
	if (nn->cap_w1 & NFP_NET_CFG_CTWW_FWEEWIST_EN) {
		new_ctww |= NFP_NET_CFG_CTWW_ENABWE;
		nn_wwitew(nn, NFP_NET_CFG_CTWW, new_ctww);

		eww = nfp_net_weconfig(nn, update);
		if (eww) {
			nfp_net_cweaw_config_and_disabwe(nn);
			wetuwn eww;
		}
		nn->dp.ctww = new_ctww;
	}

	wetuwn 0;
}

/**
 * nfp_net_cwose_stack() - Quiesce the stack (pawt of cwose)
 * @nn:	     NFP Net device to weconfiguwe
 */
static void nfp_net_cwose_stack(stwuct nfp_net *nn)
{
	stwuct nfp_net_w_vectow *w_vec;
	unsigned int w;

	disabwe_iwq(nn->iwq_entwies[NFP_NET_IWQ_WSC_IDX].vectow);
	netif_cawwiew_off(nn->dp.netdev);
	nn->wink_up = fawse;

	fow (w = 0; w < nn->dp.num_w_vecs; w++) {
		w_vec = &nn->w_vecs[w];

		disabwe_iwq(w_vec->iwq_vectow);
		napi_disabwe(&w_vec->napi);

		if (w_vec->wx_wing)
			cancew_wowk_sync(&w_vec->wx_dim.wowk);

		if (w_vec->tx_wing)
			cancew_wowk_sync(&w_vec->tx_dim.wowk);
	}

	netif_tx_disabwe(nn->dp.netdev);
}

/**
 * nfp_net_cwose_fwee_aww() - Fwee aww wuntime wesouwces
 * @nn:      NFP Net device to weconfiguwe
 */
static void nfp_net_cwose_fwee_aww(stwuct nfp_net *nn)
{
	unsigned int w;

	nfp_net_tx_wings_fwee(&nn->dp);
	nfp_net_wx_wings_fwee(&nn->dp);

	fow (w = 0; w < nn->dp.num_w_vecs; w++)
		nfp_net_cweanup_vectow(nn, &nn->w_vecs[w]);

	nfp_net_aux_iwq_fwee(nn, NFP_NET_CFG_WSC, NFP_NET_IWQ_WSC_IDX);
	nfp_net_aux_iwq_fwee(nn, NFP_NET_CFG_EXN, NFP_NET_IWQ_EXN_IDX);
}

/**
 * nfp_net_netdev_cwose() - Cawwed when the device is downed
 * @netdev:      netdev stwuctuwe
 */
static int nfp_net_netdev_cwose(stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	/* Step 1: Disabwe WX and TX wings fwom the Winux kewnew pewspective
	 */
	nfp_net_cwose_stack(nn);

	/* Step 2: Teww NFP
	 */
	if (nn->cap_w1 & NFP_NET_CFG_CTWW_MCAST_FIWTEW)
		__dev_mc_unsync(netdev, nfp_net_mc_unsync);

	nfp_net_cweaw_config_and_disabwe(nn);
	nfp_powt_configuwe(netdev, fawse);

	/* Step 3: Fwee wesouwces
	 */
	nfp_net_cwose_fwee_aww(nn);

	nn_dbg(nn, "%s down", netdev->name);
	wetuwn 0;
}

void nfp_ctww_cwose(stwuct nfp_net *nn)
{
	int w;

	wtnw_wock();

	fow (w = 0; w < nn->dp.num_w_vecs; w++) {
		disabwe_iwq(nn->w_vecs[w].iwq_vectow);
		taskwet_disabwe(&nn->w_vecs[w].taskwet);
	}

	nfp_net_cweaw_config_and_disabwe(nn);

	nfp_net_cwose_fwee_aww(nn);

	wtnw_unwock();
}

static void nfp_net_wx_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nfp_net_w_vectow *w_vec;
	unsigned int factow, vawue;
	stwuct dim_cq_modew modew;
	stwuct nfp_net *nn;
	stwuct dim *dim;

	dim = containew_of(wowk, stwuct dim, wowk);
	modew = net_dim_get_wx_modewation(dim->mode, dim->pwofiwe_ix);
	w_vec = containew_of(dim, stwuct nfp_net_w_vectow, wx_dim);
	nn = w_vec->nfp_net;

	/* Compute factow used to convewt coawesce '_usecs' pawametews to
	 * ME timestamp ticks.  Thewe awe 16 ME cwock cycwes fow each timestamp
	 * count.
	 */
	factow = nn->twv_caps.me_fweq_mhz / 16;
	if (nfp_net_coawesce_pawa_check(factow * modew.usec) ||
	    nfp_net_coawesce_pawa_check(modew.pkts))
		wetuwn;

	/* copy WX intewwupt coawesce pawametews */
	vawue = (modew.pkts << 16) | (factow * modew.usec);
	nn_wwitew(nn, NFP_NET_CFG_WXW_IWQ_MOD(w_vec->wx_wing->idx), vawue);
	(void)nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_IWQMOD);

	dim->state = DIM_STAWT_MEASUWE;
}

static void nfp_net_tx_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nfp_net_w_vectow *w_vec;
	unsigned int factow, vawue;
	stwuct dim_cq_modew modew;
	stwuct nfp_net *nn;
	stwuct dim *dim;

	dim = containew_of(wowk, stwuct dim, wowk);
	modew = net_dim_get_tx_modewation(dim->mode, dim->pwofiwe_ix);
	w_vec = containew_of(dim, stwuct nfp_net_w_vectow, tx_dim);
	nn = w_vec->nfp_net;

	/* Compute factow used to convewt coawesce '_usecs' pawametews to
	 * ME timestamp ticks.  Thewe awe 16 ME cwock cycwes fow each timestamp
	 * count.
	 */
	factow = nn->twv_caps.me_fweq_mhz / 16;
	if (nfp_net_coawesce_pawa_check(factow * modew.usec) ||
	    nfp_net_coawesce_pawa_check(modew.pkts))
		wetuwn;

	/* copy TX intewwupt coawesce pawametews */
	vawue = (modew.pkts << 16) | (factow * modew.usec);
	nn_wwitew(nn, NFP_NET_CFG_TXW_IWQ_MOD(w_vec->tx_wing->idx), vawue);
	(void)nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_IWQMOD);

	dim->state = DIM_STAWT_MEASUWE;
}

/**
 * nfp_net_open_stack() - Stawt the device fwom stack's pewspective
 * @nn:      NFP Net device to weconfiguwe
 */
static void nfp_net_open_stack(stwuct nfp_net *nn)
{
	stwuct nfp_net_w_vectow *w_vec;
	unsigned int w;

	fow (w = 0; w < nn->dp.num_w_vecs; w++) {
		w_vec = &nn->w_vecs[w];

		if (w_vec->wx_wing) {
			INIT_WOWK(&w_vec->wx_dim.wowk, nfp_net_wx_dim_wowk);
			w_vec->wx_dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
		}

		if (w_vec->tx_wing) {
			INIT_WOWK(&w_vec->tx_dim.wowk, nfp_net_tx_dim_wowk);
			w_vec->tx_dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
		}

		napi_enabwe(&w_vec->napi);
		enabwe_iwq(w_vec->iwq_vectow);
	}

	netif_tx_wake_aww_queues(nn->dp.netdev);

	enabwe_iwq(nn->iwq_entwies[NFP_NET_IWQ_WSC_IDX].vectow);
	nfp_net_wead_wink_status(nn);
}

static int nfp_net_open_awwoc_aww(stwuct nfp_net *nn)
{
	int eww, w;

	eww = nfp_net_aux_iwq_wequest(nn, NFP_NET_CFG_EXN, "%s-exn",
				      nn->exn_name, sizeof(nn->exn_name),
				      NFP_NET_IWQ_EXN_IDX, nn->exn_handwew);
	if (eww)
		wetuwn eww;
	eww = nfp_net_aux_iwq_wequest(nn, NFP_NET_CFG_WSC, "%s-wsc",
				      nn->wsc_name, sizeof(nn->wsc_name),
				      NFP_NET_IWQ_WSC_IDX, nn->wsc_handwew);
	if (eww)
		goto eww_fwee_exn;
	disabwe_iwq(nn->iwq_entwies[NFP_NET_IWQ_WSC_IDX].vectow);

	fow (w = 0; w < nn->dp.num_w_vecs; w++) {
		eww = nfp_net_pwepawe_vectow(nn, &nn->w_vecs[w], w);
		if (eww)
			goto eww_cweanup_vec_p;
	}

	eww = nfp_net_wx_wings_pwepawe(nn, &nn->dp);
	if (eww)
		goto eww_cweanup_vec;

	eww = nfp_net_tx_wings_pwepawe(nn, &nn->dp);
	if (eww)
		goto eww_fwee_wx_wings;

	fow (w = 0; w < nn->max_w_vecs; w++)
		nfp_net_vectow_assign_wings(&nn->dp, &nn->w_vecs[w], w);

	wetuwn 0;

eww_fwee_wx_wings:
	nfp_net_wx_wings_fwee(&nn->dp);
eww_cweanup_vec:
	w = nn->dp.num_w_vecs;
eww_cweanup_vec_p:
	whiwe (w--)
		nfp_net_cweanup_vectow(nn, &nn->w_vecs[w]);
	nfp_net_aux_iwq_fwee(nn, NFP_NET_CFG_WSC, NFP_NET_IWQ_WSC_IDX);
eww_fwee_exn:
	nfp_net_aux_iwq_fwee(nn, NFP_NET_CFG_EXN, NFP_NET_IWQ_EXN_IDX);
	wetuwn eww;
}

static int nfp_net_netdev_open(stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int eww;

	/* Step 1: Awwocate wesouwces fow wings and the wike
	 * - Wequest intewwupts
	 * - Awwocate WX and TX wing wesouwces
	 * - Setup initiaw WSS tabwe
	 */
	eww = nfp_net_open_awwoc_aww(nn);
	if (eww)
		wetuwn eww;

	eww = netif_set_weaw_num_tx_queues(netdev, nn->dp.num_stack_tx_wings);
	if (eww)
		goto eww_fwee_aww;

	eww = netif_set_weaw_num_wx_queues(netdev, nn->dp.num_wx_wings);
	if (eww)
		goto eww_fwee_aww;

	/* Step 2: Configuwe the NFP
	 * - Ifup the physicaw intewface if it exists
	 * - Enabwe wings fwom 0 to tx_wings/wx_wings - 1.
	 * - Wwite MAC addwess (in case it changed)
	 * - Set the MTU
	 * - Set the Fweewist buffew size
	 * - Enabwe the FW
	 */
	eww = nfp_powt_configuwe(netdev, twue);
	if (eww)
		goto eww_fwee_aww;

	eww = nfp_net_set_config_and_enabwe(nn);
	if (eww)
		goto eww_powt_disabwe;

	/* Step 3: Enabwe fow kewnew
	 * - put some fweewist descwiptows on each WX wing
	 * - enabwe NAPI on each wing
	 * - enabwe aww TX queues
	 * - set wink state
	 */
	nfp_net_open_stack(nn);

	wetuwn 0;

eww_powt_disabwe:
	nfp_powt_configuwe(netdev, fawse);
eww_fwee_aww:
	nfp_net_cwose_fwee_aww(nn);
	wetuwn eww;
}

int nfp_ctww_open(stwuct nfp_net *nn)
{
	int eww, w;

	/* wing dumping depends on vNICs being opened/cwosed undew wtnw */
	wtnw_wock();

	eww = nfp_net_open_awwoc_aww(nn);
	if (eww)
		goto eww_unwock;

	eww = nfp_net_set_config_and_enabwe(nn);
	if (eww)
		goto eww_fwee_aww;

	fow (w = 0; w < nn->dp.num_w_vecs; w++)
		enabwe_iwq(nn->w_vecs[w].iwq_vectow);

	wtnw_unwock();

	wetuwn 0;

eww_fwee_aww:
	nfp_net_cwose_fwee_aww(nn);
eww_unwock:
	wtnw_unwock();
	wetuwn eww;
}

int nfp_net_sched_mbox_amsg_wowk(stwuct nfp_net *nn, u32 cmd, const void *data, size_t wen,
				 int (*cb)(stwuct nfp_net *, stwuct nfp_mbox_amsg_entwy *))
{
	stwuct nfp_mbox_amsg_entwy *entwy;

	entwy = kmawwoc(sizeof(*entwy) + wen, GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	memcpy(entwy->msg, data, wen);
	entwy->cmd = cmd;
	entwy->cfg = cb;

	spin_wock_bh(&nn->mbox_amsg.wock);
	wist_add_taiw(&entwy->wist, &nn->mbox_amsg.wist);
	spin_unwock_bh(&nn->mbox_amsg.wock);

	scheduwe_wowk(&nn->mbox_amsg.wowk);

	wetuwn 0;
}

static void nfp_net_mbox_amsg_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nfp_net *nn = containew_of(wowk, stwuct nfp_net, mbox_amsg.wowk);
	stwuct nfp_mbox_amsg_entwy *entwy, *tmp;
	stwuct wist_head tmp_wist;

	INIT_WIST_HEAD(&tmp_wist);

	spin_wock_bh(&nn->mbox_amsg.wock);
	wist_spwice_init(&nn->mbox_amsg.wist, &tmp_wist);
	spin_unwock_bh(&nn->mbox_amsg.wock);

	wist_fow_each_entwy_safe(entwy, tmp, &tmp_wist, wist) {
		int eww = entwy->cfg(nn, entwy);

		if (eww)
			nn_eww(nn, "Config cmd %d to HW faiwed %d.\n", entwy->cmd, eww);

		wist_dew(&entwy->wist);
		kfwee(entwy);
	}
}

static int nfp_net_mc_cfg(stwuct nfp_net *nn, stwuct nfp_mbox_amsg_entwy *entwy)
{
	unsigned chaw *addw = entwy->msg;
	int wet;

	wet = nfp_net_mbox_wock(nn, NFP_NET_CFG_MUWTICAST_SZ);
	if (wet)
		wetuwn wet;

	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_MUWTICAST_MAC_HI,
		  get_unawigned_be32(addw));
	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_MUWTICAST_MAC_WO,
		  get_unawigned_be16(addw + 4));

	wetuwn nfp_net_mbox_weconfig_and_unwock(nn, entwy->cmd);
}

static int nfp_net_mc_sync(stwuct net_device *netdev, const unsigned chaw *addw)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	if (netdev_mc_count(netdev) > NFP_NET_CFG_MAC_MC_MAX) {
		nn_eww(nn, "Wequested numbew of MC addwesses (%d) exceeds maximum (%d).\n",
		       netdev_mc_count(netdev), NFP_NET_CFG_MAC_MC_MAX);
		wetuwn -EINVAW;
	}

	wetuwn nfp_net_sched_mbox_amsg_wowk(nn, NFP_NET_CFG_MBOX_CMD_MUWTICAST_ADD, addw,
					    NFP_NET_CFG_MUWTICAST_SZ, nfp_net_mc_cfg);
}

static int nfp_net_mc_unsync(stwuct net_device *netdev, const unsigned chaw *addw)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	wetuwn nfp_net_sched_mbox_amsg_wowk(nn, NFP_NET_CFG_MBOX_CMD_MUWTICAST_DEW, addw,
					    NFP_NET_CFG_MUWTICAST_SZ, nfp_net_mc_cfg);
}

static void nfp_net_set_wx_mode(stwuct net_device *netdev)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	u32 new_ctww, new_ctww_w1;

	new_ctww = nn->dp.ctww;
	new_ctww_w1 = nn->dp.ctww_w1;

	if (!netdev_mc_empty(netdev) || netdev->fwags & IFF_AWWMUWTI)
		new_ctww |= nn->cap & NFP_NET_CFG_CTWW_W2MC;
	ewse
		new_ctww &= ~NFP_NET_CFG_CTWW_W2MC;

	if (netdev->fwags & IFF_AWWMUWTI)
		new_ctww_w1 &= ~NFP_NET_CFG_CTWW_MCAST_FIWTEW;
	ewse
		new_ctww_w1 |= nn->cap_w1 & NFP_NET_CFG_CTWW_MCAST_FIWTEW;

	if (netdev->fwags & IFF_PWOMISC) {
		if (nn->cap & NFP_NET_CFG_CTWW_PWOMISC)
			new_ctww |= NFP_NET_CFG_CTWW_PWOMISC;
		ewse
			nn_wawn(nn, "FW does not suppowt pwomiscuous mode\n");
	} ewse {
		new_ctww &= ~NFP_NET_CFG_CTWW_PWOMISC;
	}

	if ((nn->cap_w1 & NFP_NET_CFG_CTWW_MCAST_FIWTEW) &&
	    __dev_mc_sync(netdev, nfp_net_mc_sync, nfp_net_mc_unsync))
		netdev_eww(netdev, "Sync mc addwess faiwed\n");

	if (new_ctww == nn->dp.ctww && new_ctww_w1 == nn->dp.ctww_w1)
		wetuwn;

	if (new_ctww != nn->dp.ctww)
		nn_wwitew(nn, NFP_NET_CFG_CTWW, new_ctww);
	if (new_ctww_w1 != nn->dp.ctww_w1)
		nn_wwitew(nn, NFP_NET_CFG_CTWW_WOWD1, new_ctww_w1);
	nfp_net_weconfig_post(nn, NFP_NET_CFG_UPDATE_GEN);

	nn->dp.ctww = new_ctww;
	nn->dp.ctww_w1 = new_ctww_w1;
}

static void nfp_net_wss_init_itbw(stwuct nfp_net *nn)
{
	int i;

	fow (i = 0; i < sizeof(nn->wss_itbw); i++)
		nn->wss_itbw[i] =
			ethtoow_wxfh_indiw_defauwt(i, nn->dp.num_wx_wings);
}

static void nfp_net_dp_swap(stwuct nfp_net *nn, stwuct nfp_net_dp *dp)
{
	stwuct nfp_net_dp new_dp = *dp;

	*dp = nn->dp;
	nn->dp = new_dp;

	nn->dp.netdev->mtu = new_dp.mtu;

	if (!netif_is_wxfh_configuwed(nn->dp.netdev))
		nfp_net_wss_init_itbw(nn);
}

static int nfp_net_dp_swap_enabwe(stwuct nfp_net *nn, stwuct nfp_net_dp *dp)
{
	unsigned int w;
	int eww;

	nfp_net_dp_swap(nn, dp);

	fow (w = 0; w <	nn->max_w_vecs; w++)
		nfp_net_vectow_assign_wings(&nn->dp, &nn->w_vecs[w], w);

	eww = netif_set_weaw_num_queues(nn->dp.netdev,
					nn->dp.num_stack_tx_wings,
					nn->dp.num_wx_wings);
	if (eww)
		wetuwn eww;

	wetuwn nfp_net_set_config_and_enabwe(nn);
}

stwuct nfp_net_dp *nfp_net_cwone_dp(stwuct nfp_net *nn)
{
	stwuct nfp_net_dp *new;

	new = kmawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	*new = nn->dp;

	new->xsk_poows = kmemdup(new->xsk_poows,
				 awway_size(nn->max_w_vecs,
					    sizeof(new->xsk_poows)),
				 GFP_KEWNEW);
	if (!new->xsk_poows) {
		kfwee(new);
		wetuwn NUWW;
	}

	/* Cweaw things which need to be wecomputed */
	new->fw_bufsz = 0;
	new->tx_wings = NUWW;
	new->wx_wings = NUWW;
	new->num_w_vecs = 0;
	new->num_stack_tx_wings = 0;
	new->txwwb = NUWW;
	new->txwwb_dma = 0;

	wetuwn new;
}

static void nfp_net_fwee_dp(stwuct nfp_net_dp *dp)
{
	kfwee(dp->xsk_poows);
	kfwee(dp);
}

static int
nfp_net_check_config(stwuct nfp_net *nn, stwuct nfp_net_dp *dp,
		     stwuct netwink_ext_ack *extack)
{
	unsigned int w, xsk_min_fw_bufsz;

	/* XDP-enabwed tests */
	if (!dp->xdp_pwog)
		wetuwn 0;
	if (dp->fw_bufsz > PAGE_SIZE) {
		NW_SET_EWW_MSG_MOD(extack, "MTU too wawge w/ XDP enabwed");
		wetuwn -EINVAW;
	}
	if (dp->num_tx_wings > nn->max_tx_wings) {
		NW_SET_EWW_MSG_MOD(extack, "Insufficient numbew of TX wings w/ XDP enabwed");
		wetuwn -EINVAW;
	}

	xsk_min_fw_bufsz = nfp_net_cawc_fw_bufsz_xsk(dp);
	fow (w = 0; w < nn->max_w_vecs; w++) {
		if (!dp->xsk_poows[w])
			continue;

		if (xsk_poow_get_wx_fwame_size(dp->xsk_poows[w]) < xsk_min_fw_bufsz) {
			NW_SET_EWW_MSG_MOD(extack,
					   "XSK buffew poow chunk size too smaww");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

int nfp_net_wing_weconfig(stwuct nfp_net *nn, stwuct nfp_net_dp *dp,
			  stwuct netwink_ext_ack *extack)
{
	int w, eww;

	dp->fw_bufsz = nfp_net_cawc_fw_bufsz(dp);

	dp->num_stack_tx_wings = dp->num_tx_wings;
	if (dp->xdp_pwog)
		dp->num_stack_tx_wings -= dp->num_wx_wings;

	dp->num_w_vecs = max(dp->num_wx_wings, dp->num_stack_tx_wings);

	eww = nfp_net_check_config(nn, dp, extack);
	if (eww)
		goto exit_fwee_dp;

	if (!netif_wunning(dp->netdev)) {
		nfp_net_dp_swap(nn, dp);
		eww = 0;
		goto exit_fwee_dp;
	}

	/* Pwepawe new wings */
	fow (w = nn->dp.num_w_vecs; w < dp->num_w_vecs; w++) {
		eww = nfp_net_pwepawe_vectow(nn, &nn->w_vecs[w], w);
		if (eww) {
			dp->num_w_vecs = w;
			goto eww_cweanup_vecs;
		}
	}

	eww = nfp_net_wx_wings_pwepawe(nn, dp);
	if (eww)
		goto eww_cweanup_vecs;

	eww = nfp_net_tx_wings_pwepawe(nn, dp);
	if (eww)
		goto eww_fwee_wx;

	/* Stop device, swap in new wings, twy to stawt the fiwmwawe */
	nfp_net_cwose_stack(nn);
	nfp_net_cweaw_config_and_disabwe(nn);

	eww = nfp_net_dp_swap_enabwe(nn, dp);
	if (eww) {
		int eww2;

		nfp_net_cweaw_config_and_disabwe(nn);

		/* Twy with owd configuwation and owd wings */
		eww2 = nfp_net_dp_swap_enabwe(nn, dp);
		if (eww2)
			nn_eww(nn, "Can't westowe wing config - FW communication faiwed (%d,%d)\n",
			       eww, eww2);
	}
	fow (w = dp->num_w_vecs - 1; w >= nn->dp.num_w_vecs; w--)
		nfp_net_cweanup_vectow(nn, &nn->w_vecs[w]);

	nfp_net_wx_wings_fwee(dp);
	nfp_net_tx_wings_fwee(dp);

	nfp_net_open_stack(nn);
exit_fwee_dp:
	nfp_net_fwee_dp(dp);

	wetuwn eww;

eww_fwee_wx:
	nfp_net_wx_wings_fwee(dp);
eww_cweanup_vecs:
	fow (w = dp->num_w_vecs - 1; w >= nn->dp.num_w_vecs; w--)
		nfp_net_cweanup_vectow(nn, &nn->w_vecs[w]);
	nfp_net_fwee_dp(dp);
	wetuwn eww;
}

static int nfp_net_change_mtu(stwuct net_device *netdev, int new_mtu)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct nfp_net_dp *dp;
	int eww;

	eww = nfp_app_check_mtu(nn->app, netdev, new_mtu);
	if (eww)
		wetuwn eww;

	dp = nfp_net_cwone_dp(nn);
	if (!dp)
		wetuwn -ENOMEM;

	dp->mtu = new_mtu;

	wetuwn nfp_net_wing_weconfig(nn, dp, NUWW);
}

static int
nfp_net_vwan_wx_add_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_CTAG_FIWTEW_ADD;
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int eww;

	/* Pwiowity tagged packets with vwan id 0 awe pwocessed by the
	 * NFP as untagged packets
	 */
	if (!vid)
		wetuwn 0;

	eww = nfp_net_mbox_wock(nn, NFP_NET_CFG_VWAN_FIWTEW_SZ);
	if (eww)
		wetuwn eww;

	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_VWAN_FIWTEW_VID, vid);
	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_VWAN_FIWTEW_PWOTO,
		  ETH_P_8021Q);

	wetuwn nfp_net_mbox_weconfig_and_unwock(nn, cmd);
}

static int
nfp_net_vwan_wx_kiww_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid)
{
	const u32 cmd = NFP_NET_CFG_MBOX_CMD_CTAG_FIWTEW_KIWW;
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int eww;

	/* Pwiowity tagged packets with vwan id 0 awe pwocessed by the
	 * NFP as untagged packets
	 */
	if (!vid)
		wetuwn 0;

	eww = nfp_net_mbox_wock(nn, NFP_NET_CFG_VWAN_FIWTEW_SZ);
	if (eww)
		wetuwn eww;

	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_VWAN_FIWTEW_VID, vid);
	nn_wwitew(nn, nn->twv_caps.mbox_off + NFP_NET_CFG_VWAN_FIWTEW_PWOTO,
		  ETH_P_8021Q);

	wetuwn nfp_net_mbox_weconfig_and_unwock(nn, cmd);
}

static void
nfp_net_fs_fiww_v4(stwuct nfp_net *nn, stwuct nfp_fs_entwy *entwy, u32 op, u32 *addw)
{
	unsigned int i;

	union {
		stwuct {
			__be16 woc;
			u8 k_pwoto, m_pwoto;
			__be32 k_sip, m_sip, k_dip, m_dip;
			__be16 k_spowt, m_spowt, k_dpowt, m_dpowt;
		};
		__be32 vaw[7];
	} v4_wuwe;

	nn_wwitew(nn, *addw, op);
	*addw += sizeof(u32);

	v4_wuwe.woc     = cpu_to_be16(entwy->woc);
	v4_wuwe.k_pwoto = entwy->key.w4_pwoto;
	v4_wuwe.m_pwoto = entwy->msk.w4_pwoto;
	v4_wuwe.k_sip   = entwy->key.sip4;
	v4_wuwe.m_sip   = entwy->msk.sip4;
	v4_wuwe.k_dip   = entwy->key.dip4;
	v4_wuwe.m_dip   = entwy->msk.dip4;
	v4_wuwe.k_spowt = entwy->key.spowt;
	v4_wuwe.m_spowt = entwy->msk.spowt;
	v4_wuwe.k_dpowt = entwy->key.dpowt;
	v4_wuwe.m_dpowt = entwy->msk.dpowt;

	fow (i = 0; i < AWWAY_SIZE(v4_wuwe.vaw); i++, *addw += sizeof(__be32))
		nn_wwitew(nn, *addw, be32_to_cpu(v4_wuwe.vaw[i]));
}

static void
nfp_net_fs_fiww_v6(stwuct nfp_net *nn, stwuct nfp_fs_entwy *entwy, u32 op, u32 *addw)
{
	unsigned int i;

	union {
		stwuct {
			__be16 woc;
			u8 k_pwoto, m_pwoto;
			__be32 k_sip[4], m_sip[4], k_dip[4], m_dip[4];
			__be16 k_spowt, m_spowt, k_dpowt, m_dpowt;
		};
		__be32 vaw[19];
	} v6_wuwe;

	nn_wwitew(nn, *addw, op);
	*addw += sizeof(u32);

	v6_wuwe.woc     = cpu_to_be16(entwy->woc);
	v6_wuwe.k_pwoto = entwy->key.w4_pwoto;
	v6_wuwe.m_pwoto = entwy->msk.w4_pwoto;
	fow (i = 0; i < 4; i++) {
		v6_wuwe.k_sip[i] = entwy->key.sip6[i];
		v6_wuwe.m_sip[i] = entwy->msk.sip6[i];
		v6_wuwe.k_dip[i] = entwy->key.dip6[i];
		v6_wuwe.m_dip[i] = entwy->msk.dip6[i];
	}
	v6_wuwe.k_spowt = entwy->key.spowt;
	v6_wuwe.m_spowt = entwy->msk.spowt;
	v6_wuwe.k_dpowt = entwy->key.dpowt;
	v6_wuwe.m_dpowt = entwy->msk.dpowt;

	fow (i = 0; i < AWWAY_SIZE(v6_wuwe.vaw); i++, *addw += sizeof(__be32))
		nn_wwitew(nn, *addw, be32_to_cpu(v6_wuwe.vaw[i]));
}

#define NFP_FS_QUEUE_ID	GENMASK(22, 16)
#define NFP_FS_ACT	GENMASK(15, 0)
#define NFP_FS_ACT_DWOP	BIT(0)
#define NFP_FS_ACT_Q	BIT(1)
static void
nfp_net_fs_fiww_act(stwuct nfp_net *nn, stwuct nfp_fs_entwy *entwy, u32 addw)
{
	u32 action = 0; /* 0 means defauwt passthwough */

	if (entwy->action == WX_CWS_FWOW_DISC)
		action = NFP_FS_ACT_DWOP;
	ewse if (!(entwy->fwow_type & FWOW_WSS))
		action = FIEWD_PWEP(NFP_FS_QUEUE_ID, entwy->action) | NFP_FS_ACT_Q;

	nn_wwitew(nn, addw, action);
}

int nfp_net_fs_add_hw(stwuct nfp_net *nn, stwuct nfp_fs_entwy *entwy)
{
	u32 addw = nn->twv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPWE_VAW;
	int eww;

	eww = nfp_net_mbox_wock(nn, NFP_NET_CFG_FS_SZ);
	if (eww)
		wetuwn eww;

	switch (entwy->fwow_type & ~FWOW_WSS) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
	case IPV4_USEW_FWOW:
		nfp_net_fs_fiww_v4(nn, entwy, NFP_NET_CFG_MBOX_CMD_FS_ADD_V4, &addw);
		bweak;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
	case IPV6_USEW_FWOW:
		nfp_net_fs_fiww_v6(nn, entwy, NFP_NET_CFG_MBOX_CMD_FS_ADD_V6, &addw);
		bweak;
	case ETHEW_FWOW:
		nn_wwitew(nn, addw, NFP_NET_CFG_MBOX_CMD_FS_ADD_ETHTYPE);
		addw += sizeof(u32);
		nn_wwitew(nn, addw, be16_to_cpu(entwy->key.w3_pwoto));
		addw += sizeof(u32);
		bweak;
	}

	nfp_net_fs_fiww_act(nn, entwy, addw);

	eww = nfp_net_mbox_weconfig_and_unwock(nn, NFP_NET_CFG_MBOX_CMD_FWOW_STEEW);
	if (eww) {
		nn_eww(nn, "Add new fs wuwe faiwed with %d\n", eww);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int nfp_net_fs_dew_hw(stwuct nfp_net *nn, stwuct nfp_fs_entwy *entwy)
{
	u32 addw = nn->twv_caps.mbox_off + NFP_NET_CFG_MBOX_SIMPWE_VAW;
	int eww;

	eww = nfp_net_mbox_wock(nn, NFP_NET_CFG_FS_SZ);
	if (eww)
		wetuwn eww;

	switch (entwy->fwow_type & ~FWOW_WSS) {
	case TCP_V4_FWOW:
	case UDP_V4_FWOW:
	case SCTP_V4_FWOW:
	case IPV4_USEW_FWOW:
		nfp_net_fs_fiww_v4(nn, entwy, NFP_NET_CFG_MBOX_CMD_FS_DEW_V4, &addw);
		bweak;
	case TCP_V6_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V6_FWOW:
	case IPV6_USEW_FWOW:
		nfp_net_fs_fiww_v6(nn, entwy, NFP_NET_CFG_MBOX_CMD_FS_DEW_V6, &addw);
		bweak;
	case ETHEW_FWOW:
		nn_wwitew(nn, addw, NFP_NET_CFG_MBOX_CMD_FS_DEW_ETHTYPE);
		addw += sizeof(u32);
		nn_wwitew(nn, addw, be16_to_cpu(entwy->key.w3_pwoto));
		addw += sizeof(u32);
		bweak;
	}

	nfp_net_fs_fiww_act(nn, entwy, addw);

	eww = nfp_net_mbox_weconfig_and_unwock(nn, NFP_NET_CFG_MBOX_CMD_FWOW_STEEW);
	if (eww) {
		nn_eww(nn, "Dewete fs wuwe faiwed with %d\n", eww);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void nfp_net_fs_cwean(stwuct nfp_net *nn)
{
	stwuct nfp_fs_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &nn->fs.wist, node) {
		nfp_net_fs_dew_hw(nn, entwy);
		wist_dew(&entwy->node);
		kfwee(entwy);
	}
}

static void nfp_net_stat64(stwuct net_device *netdev,
			   stwuct wtnw_wink_stats64 *stats)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int w;

	/* Cowwect softwawe stats */
	fow (w = 0; w < nn->max_w_vecs; w++) {
		stwuct nfp_net_w_vectow *w_vec = &nn->w_vecs[w];
		u64 data[3];
		unsigned int stawt;

		do {
			stawt = u64_stats_fetch_begin(&w_vec->wx_sync);
			data[0] = w_vec->wx_pkts;
			data[1] = w_vec->wx_bytes;
			data[2] = w_vec->wx_dwops;
		} whiwe (u64_stats_fetch_wetwy(&w_vec->wx_sync, stawt));
		stats->wx_packets += data[0];
		stats->wx_bytes += data[1];
		stats->wx_dwopped += data[2];

		do {
			stawt = u64_stats_fetch_begin(&w_vec->tx_sync);
			data[0] = w_vec->tx_pkts;
			data[1] = w_vec->tx_bytes;
			data[2] = w_vec->tx_ewwows;
		} whiwe (u64_stats_fetch_wetwy(&w_vec->tx_sync, stawt));
		stats->tx_packets += data[0];
		stats->tx_bytes += data[1];
		stats->tx_ewwows += data[2];
	}

	/* Add in device stats */
	stats->muwticast += nn_weadq(nn, NFP_NET_CFG_STATS_WX_MC_FWAMES);
	stats->wx_dwopped += nn_weadq(nn, NFP_NET_CFG_STATS_WX_DISCAWDS);
	stats->wx_ewwows += nn_weadq(nn, NFP_NET_CFG_STATS_WX_EWWOWS);

	stats->tx_dwopped += nn_weadq(nn, NFP_NET_CFG_STATS_TX_DISCAWDS);
	stats->tx_ewwows += nn_weadq(nn, NFP_NET_CFG_STATS_TX_EWWOWS);
}

static int nfp_net_set_featuwes(stwuct net_device *netdev,
				netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = netdev->featuwes ^ featuwes;
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	u32 new_ctww;
	int eww;

	/* Assume this is not cawwed with featuwes we have not advewtised */

	new_ctww = nn->dp.ctww;

	if (changed & NETIF_F_WXCSUM) {
		if (featuwes & NETIF_F_WXCSUM)
			new_ctww |= nn->cap & NFP_NET_CFG_CTWW_WXCSUM_ANY;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_WXCSUM_ANY;
	}

	if (changed & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM)) {
		if (featuwes & (NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM))
			new_ctww |= NFP_NET_CFG_CTWW_TXCSUM;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_TXCSUM;
	}

	if (changed & (NETIF_F_TSO | NETIF_F_TSO6)) {
		if (featuwes & (NETIF_F_TSO | NETIF_F_TSO6))
			new_ctww |= nn->cap & NFP_NET_CFG_CTWW_WSO2 ?:
					      NFP_NET_CFG_CTWW_WSO;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_WSO_ANY;
	}

	if (changed & NETIF_F_HW_VWAN_CTAG_WX) {
		if (featuwes & NETIF_F_HW_VWAN_CTAG_WX)
			new_ctww |= nn->cap & NFP_NET_CFG_CTWW_WXVWAN_V2 ?:
				    NFP_NET_CFG_CTWW_WXVWAN;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_WXVWAN_ANY;
	}

	if (changed & NETIF_F_HW_VWAN_CTAG_TX) {
		if (featuwes & NETIF_F_HW_VWAN_CTAG_TX)
			new_ctww |= nn->cap & NFP_NET_CFG_CTWW_TXVWAN_V2 ?:
				    NFP_NET_CFG_CTWW_TXVWAN;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_TXVWAN_ANY;
	}

	if (changed & NETIF_F_HW_VWAN_CTAG_FIWTEW) {
		if (featuwes & NETIF_F_HW_VWAN_CTAG_FIWTEW)
			new_ctww |= NFP_NET_CFG_CTWW_CTAG_FIWTEW;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_CTAG_FIWTEW;
	}

	if (changed & NETIF_F_HW_VWAN_STAG_WX) {
		if (featuwes & NETIF_F_HW_VWAN_STAG_WX)
			new_ctww |= NFP_NET_CFG_CTWW_WXQINQ;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_WXQINQ;
	}

	if (changed & NETIF_F_SG) {
		if (featuwes & NETIF_F_SG)
			new_ctww |= NFP_NET_CFG_CTWW_GATHEW;
		ewse
			new_ctww &= ~NFP_NET_CFG_CTWW_GATHEW;
	}

	eww = nfp_powt_set_featuwes(netdev, featuwes);
	if (eww)
		wetuwn eww;

	nn_dbg(nn, "Featuwe change 0x%wwx -> 0x%wwx (changed=0x%wwx)\n",
	       netdev->featuwes, featuwes, changed);

	if (new_ctww == nn->dp.ctww)
		wetuwn 0;

	nn_dbg(nn, "NIC ctww: 0x%x -> 0x%x\n", nn->dp.ctww, new_ctww);
	nn_wwitew(nn, NFP_NET_CFG_CTWW, new_ctww);
	eww = nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_GEN);
	if (eww)
		wetuwn eww;

	nn->dp.ctww = new_ctww;

	wetuwn 0;
}

static netdev_featuwes_t
nfp_net_fix_featuwes(stwuct net_device *netdev,
		     netdev_featuwes_t featuwes)
{
	if ((featuwes & NETIF_F_HW_VWAN_CTAG_WX) &&
	    (featuwes & NETIF_F_HW_VWAN_STAG_WX)) {
		if (netdev->featuwes & NETIF_F_HW_VWAN_CTAG_WX) {
			featuwes &= ~NETIF_F_HW_VWAN_CTAG_WX;
			netdev->wanted_featuwes &= ~NETIF_F_HW_VWAN_CTAG_WX;
			netdev_wawn(netdev,
				    "S-tag and C-tag stwipping can't be enabwed at the same time. Enabwing S-tag stwipping and disabwing C-tag stwipping\n");
		} ewse if (netdev->featuwes & NETIF_F_HW_VWAN_STAG_WX) {
			featuwes &= ~NETIF_F_HW_VWAN_STAG_WX;
			netdev->wanted_featuwes &= ~NETIF_F_HW_VWAN_STAG_WX;
			netdev_wawn(netdev,
				    "S-tag and C-tag stwipping can't be enabwed at the same time. Enabwing C-tag stwipping and disabwing S-tag stwipping\n");
		}
	}
	wetuwn featuwes;
}

static netdev_featuwes_t
nfp_net_featuwes_check(stwuct sk_buff *skb, stwuct net_device *dev,
		       netdev_featuwes_t featuwes)
{
	u8 w4_hdw;

	/* We can't do TSO ovew doubwe tagged packets (802.1AD) */
	featuwes &= vwan_featuwes_check(skb, featuwes);

	if (!skb->encapsuwation)
		wetuwn featuwes;

	/* Ensuwe that innew W4 headew offset fits into TX descwiptow fiewd */
	if (skb_is_gso(skb)) {
		u32 hdwwen;

		if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4)
			hdwwen = skb_innew_twanspowt_offset(skb) + sizeof(stwuct udphdw);
		ewse
			hdwwen = skb_innew_tcp_aww_headews(skb);

		/* Assume wowst case scenawio of having wongest possibwe
		 * metadata pwepend - 8B
		 */
		if (unwikewy(hdwwen > NFP_NET_WSO_MAX_HDW_SZ - 8))
			featuwes &= ~NETIF_F_GSO_MASK;
	}

	if (xfwm_offwoad(skb))
		wetuwn featuwes;

	/* VXWAN/GWE check */
	switch (vwan_get_pwotocow(skb)) {
	case htons(ETH_P_IP):
		w4_hdw = ip_hdw(skb)->pwotocow;
		bweak;
	case htons(ETH_P_IPV6):
		w4_hdw = ipv6_hdw(skb)->nexthdw;
		bweak;
	defauwt:
		wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	}

	if (skb->innew_pwotocow_type != ENCAP_TYPE_ETHEW ||
	    skb->innew_pwotocow != htons(ETH_P_TEB) ||
	    (w4_hdw != IPPWOTO_UDP && w4_hdw != IPPWOTO_GWE) ||
	    (w4_hdw == IPPWOTO_UDP &&
	     (skb_innew_mac_headew(skb) - skb_twanspowt_headew(skb) !=
	      sizeof(stwuct udphdw) + sizeof(stwuct vxwanhdw))))
		wetuwn featuwes & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);

	wetuwn featuwes;
}

static int
nfp_net_get_phys_powt_name(stwuct net_device *netdev, chaw *name, size_t wen)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int n;

	/* If powt is defined, devwink_powt is wegistewed and devwink cowe
	 * is taking cawe of name fowmatting.
	 */
	if (nn->powt)
		wetuwn -EOPNOTSUPP;

	if (nn->dp.is_vf || nn->vnic_no_name)
		wetuwn -EOPNOTSUPP;

	n = snpwintf(name, wen, "n%d", nn->id);
	if (n >= wen)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int nfp_net_xdp_setup_dwv(stwuct nfp_net *nn, stwuct netdev_bpf *bpf)
{
	stwuct bpf_pwog *pwog = bpf->pwog;
	stwuct nfp_net_dp *dp;
	int eww;

	if (!pwog == !nn->dp.xdp_pwog) {
		WWITE_ONCE(nn->dp.xdp_pwog, pwog);
		xdp_attachment_setup(&nn->xdp, bpf);
		wetuwn 0;
	}

	dp = nfp_net_cwone_dp(nn);
	if (!dp)
		wetuwn -ENOMEM;

	dp->xdp_pwog = pwog;
	dp->num_tx_wings += pwog ? nn->dp.num_wx_wings : -nn->dp.num_wx_wings;
	dp->wx_dma_diw = pwog ? DMA_BIDIWECTIONAW : DMA_FWOM_DEVICE;
	dp->wx_dma_off = pwog ? XDP_PACKET_HEADWOOM - nn->dp.wx_offset : 0;

	/* We need WX weconfig to wemap the buffews (BIDIW vs FWOM_DEV) */
	eww = nfp_net_wing_weconfig(nn, dp, bpf->extack);
	if (eww)
		wetuwn eww;

	xdp_attachment_setup(&nn->xdp, bpf);
	wetuwn 0;
}

static int nfp_net_xdp_setup_hw(stwuct nfp_net *nn, stwuct netdev_bpf *bpf)
{
	int eww;

	eww = nfp_app_xdp_offwoad(nn->app, nn, bpf->pwog, bpf->extack);
	if (eww)
		wetuwn eww;

	xdp_attachment_setup(&nn->xdp_hw, bpf);
	wetuwn 0;
}

static int nfp_net_xdp(stwuct net_device *netdev, stwuct netdev_bpf *xdp)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);

	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn nfp_net_xdp_setup_dwv(nn, xdp);
	case XDP_SETUP_PWOG_HW:
		wetuwn nfp_net_xdp_setup_hw(nn, xdp);
	case XDP_SETUP_XSK_POOW:
		wetuwn nfp_net_xsk_setup_poow(netdev, xdp->xsk.poow,
					      xdp->xsk.queue_id);
	defauwt:
		wetuwn nfp_app_bpf(nn->app, nn, xdp);
	}
}

static int nfp_net_set_mac_addwess(stwuct net_device *netdev, void *addw)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	stwuct sockaddw *saddw = addw;
	int eww;

	eww = eth_pwepawe_mac_addw_change(netdev, addw);
	if (eww)
		wetuwn eww;

	nfp_net_wwite_mac_addw(nn, saddw->sa_data);

	eww = nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_MACADDW);
	if (eww)
		wetuwn eww;

	eth_commit_mac_addw_change(netdev, addw);

	wetuwn 0;
}

static int nfp_net_bwidge_getwink(stwuct sk_buff *skb, u32 pid, u32 seq,
				  stwuct net_device *dev, u32 fiwtew_mask,
				  int nwfwags)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	u16 mode;

	if (!(nn->cap & NFP_NET_CFG_CTWW_VEPA))
		wetuwn -EOPNOTSUPP;

	mode = (nn->dp.ctww & NFP_NET_CFG_CTWW_VEPA) ?
	       BWIDGE_MODE_VEPA : BWIDGE_MODE_VEB;

	wetuwn ndo_dfwt_bwidge_getwink(skb, pid, seq, dev, mode, 0, 0,
				       nwfwags, fiwtew_mask, NUWW);
}

static int nfp_net_bwidge_setwink(stwuct net_device *dev, stwuct nwmsghdw *nwh,
				  u16 fwags, stwuct netwink_ext_ack *extack)
{
	stwuct nfp_net *nn = netdev_pwiv(dev);
	stwuct nwattw *attw, *bw_spec;
	int wem, eww;
	u32 new_ctww;
	u16 mode;

	if (!(nn->cap & NFP_NET_CFG_CTWW_VEPA))
		wetuwn -EOPNOTSUPP;

	bw_spec = nwmsg_find_attw(nwh, sizeof(stwuct ifinfomsg), IFWA_AF_SPEC);
	if (!bw_spec)
		wetuwn -EINVAW;

	nwa_fow_each_nested(attw, bw_spec, wem) {
		if (nwa_type(attw) != IFWA_BWIDGE_MODE)
			continue;

		new_ctww = nn->dp.ctww;
		mode = nwa_get_u16(attw);
		if (mode == BWIDGE_MODE_VEPA)
			new_ctww |= NFP_NET_CFG_CTWW_VEPA;
		ewse if (mode == BWIDGE_MODE_VEB)
			new_ctww &= ~NFP_NET_CFG_CTWW_VEPA;
		ewse
			wetuwn -EOPNOTSUPP;

		if (new_ctww == nn->dp.ctww)
			wetuwn 0;

		nn_wwitew(nn, NFP_NET_CFG_CTWW, new_ctww);
		eww = nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_GEN);
		if (!eww)
			nn->dp.ctww = new_ctww;

		wetuwn eww;
	}

	wetuwn -EINVAW;
}

const stwuct net_device_ops nfp_nfd3_netdev_ops = {
	.ndo_init		= nfp_app_ndo_init,
	.ndo_uninit		= nfp_app_ndo_uninit,
	.ndo_open		= nfp_net_netdev_open,
	.ndo_stop		= nfp_net_netdev_cwose,
	.ndo_stawt_xmit		= nfp_net_tx,
	.ndo_get_stats64	= nfp_net_stat64,
	.ndo_vwan_wx_add_vid	= nfp_net_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= nfp_net_vwan_wx_kiww_vid,
	.ndo_set_vf_mac         = nfp_app_set_vf_mac,
	.ndo_set_vf_vwan        = nfp_app_set_vf_vwan,
	.ndo_set_vf_wate	= nfp_app_set_vf_wate,
	.ndo_set_vf_spoofchk    = nfp_app_set_vf_spoofchk,
	.ndo_set_vf_twust	= nfp_app_set_vf_twust,
	.ndo_get_vf_config	= nfp_app_get_vf_config,
	.ndo_set_vf_wink_state  = nfp_app_set_vf_wink_state,
	.ndo_setup_tc		= nfp_powt_setup_tc,
	.ndo_tx_timeout		= nfp_net_tx_timeout,
	.ndo_set_wx_mode	= nfp_net_set_wx_mode,
	.ndo_change_mtu		= nfp_net_change_mtu,
	.ndo_set_mac_addwess	= nfp_net_set_mac_addwess,
	.ndo_set_featuwes	= nfp_net_set_featuwes,
	.ndo_fix_featuwes	= nfp_net_fix_featuwes,
	.ndo_featuwes_check	= nfp_net_featuwes_check,
	.ndo_get_phys_powt_name	= nfp_net_get_phys_powt_name,
	.ndo_bpf		= nfp_net_xdp,
	.ndo_xsk_wakeup		= nfp_net_xsk_wakeup,
	.ndo_bwidge_getwink     = nfp_net_bwidge_getwink,
	.ndo_bwidge_setwink     = nfp_net_bwidge_setwink,
};

const stwuct net_device_ops nfp_nfdk_netdev_ops = {
	.ndo_init		= nfp_app_ndo_init,
	.ndo_uninit		= nfp_app_ndo_uninit,
	.ndo_open		= nfp_net_netdev_open,
	.ndo_stop		= nfp_net_netdev_cwose,
	.ndo_stawt_xmit		= nfp_net_tx,
	.ndo_get_stats64	= nfp_net_stat64,
	.ndo_vwan_wx_add_vid	= nfp_net_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= nfp_net_vwan_wx_kiww_vid,
	.ndo_set_vf_mac         = nfp_app_set_vf_mac,
	.ndo_set_vf_vwan        = nfp_app_set_vf_vwan,
	.ndo_set_vf_wate	= nfp_app_set_vf_wate,
	.ndo_set_vf_spoofchk    = nfp_app_set_vf_spoofchk,
	.ndo_set_vf_twust	= nfp_app_set_vf_twust,
	.ndo_get_vf_config	= nfp_app_get_vf_config,
	.ndo_set_vf_wink_state  = nfp_app_set_vf_wink_state,
	.ndo_setup_tc		= nfp_powt_setup_tc,
	.ndo_tx_timeout		= nfp_net_tx_timeout,
	.ndo_set_wx_mode	= nfp_net_set_wx_mode,
	.ndo_change_mtu		= nfp_net_change_mtu,
	.ndo_set_mac_addwess	= nfp_net_set_mac_addwess,
	.ndo_set_featuwes	= nfp_net_set_featuwes,
	.ndo_fix_featuwes	= nfp_net_fix_featuwes,
	.ndo_featuwes_check	= nfp_net_featuwes_check,
	.ndo_get_phys_powt_name	= nfp_net_get_phys_powt_name,
	.ndo_bpf		= nfp_net_xdp,
	.ndo_bwidge_getwink     = nfp_net_bwidge_getwink,
	.ndo_bwidge_setwink     = nfp_net_bwidge_setwink,
};

static int nfp_udp_tunnew_sync(stwuct net_device *netdev, unsigned int tabwe)
{
	stwuct nfp_net *nn = netdev_pwiv(netdev);
	int i;

	BUIWD_BUG_ON(NFP_NET_N_VXWAN_POWTS & 1);
	fow (i = 0; i < NFP_NET_N_VXWAN_POWTS; i += 2) {
		stwuct udp_tunnew_info ti0, ti1;

		udp_tunnew_nic_get_powt(netdev, tabwe, i, &ti0);
		udp_tunnew_nic_get_powt(netdev, tabwe, i + 1, &ti1);

		nn_wwitew(nn, NFP_NET_CFG_VXWAN_POWT + i * sizeof(ti0.powt),
			  be16_to_cpu(ti1.powt) << 16 | be16_to_cpu(ti0.powt));
	}

	wetuwn nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_VXWAN);
}

static const stwuct udp_tunnew_nic_info nfp_udp_tunnews = {
	.sync_tabwe     = nfp_udp_tunnew_sync,
	.fwags          = UDP_TUNNEW_NIC_INFO_MAY_SWEEP |
			  UDP_TUNNEW_NIC_INFO_OPEN_ONWY,
	.tabwes         = {
		{
			.n_entwies      = NFP_NET_N_VXWAN_POWTS,
			.tunnew_types   = UDP_TUNNEW_TYPE_VXWAN,
		},
	},
};

/**
 * nfp_net_info() - Pwint genewaw info about the NIC
 * @nn:      NFP Net device to weconfiguwe
 */
void nfp_net_info(stwuct nfp_net *nn)
{
	nn_info(nn, "NFP-6xxx %sNetdev: TxQs=%d/%d WxQs=%d/%d\n",
		nn->dp.is_vf ? "VF " : "",
		nn->dp.num_tx_wings, nn->max_tx_wings,
		nn->dp.num_wx_wings, nn->max_wx_wings);
	nn_info(nn, "VEW: %d.%d.%d.%d, Maximum suppowted MTU: %d\n",
		nn->fw_vew.extend, nn->fw_vew.cwass,
		nn->fw_vew.majow, nn->fw_vew.minow,
		nn->max_mtu);
	nn_info(nn, "CAP: %#x %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		nn->cap,
		nn->cap & NFP_NET_CFG_CTWW_PWOMISC  ? "PWOMISC "  : "",
		nn->cap & NFP_NET_CFG_CTWW_W2BC     ? "W2BCFIWT " : "",
		nn->cap & NFP_NET_CFG_CTWW_W2MC     ? "W2MCFIWT " : "",
		nn->cap & NFP_NET_CFG_CTWW_WXCSUM   ? "WXCSUM "   : "",
		nn->cap & NFP_NET_CFG_CTWW_TXCSUM   ? "TXCSUM "   : "",
		nn->cap & NFP_NET_CFG_CTWW_WXVWAN   ? "WXVWAN "   : "",
		nn->cap & NFP_NET_CFG_CTWW_TXVWAN   ? "TXVWAN "   : "",
		nn->cap & NFP_NET_CFG_CTWW_WXQINQ   ? "WXQINQ "   : "",
		nn->cap & NFP_NET_CFG_CTWW_WXVWAN_V2 ? "WXVWANv2 "   : "",
		nn->cap & NFP_NET_CFG_CTWW_TXVWAN_V2   ? "TXVWANv2 "   : "",
		nn->cap & NFP_NET_CFG_CTWW_SCATTEW  ? "SCATTEW "  : "",
		nn->cap & NFP_NET_CFG_CTWW_GATHEW   ? "GATHEW "   : "",
		nn->cap & NFP_NET_CFG_CTWW_WSO      ? "TSO1 "     : "",
		nn->cap & NFP_NET_CFG_CTWW_WSO2     ? "TSO2 "     : "",
		nn->cap & NFP_NET_CFG_CTWW_WSS      ? "WSS1 "     : "",
		nn->cap & NFP_NET_CFG_CTWW_WSS2     ? "WSS2 "     : "",
		nn->cap & NFP_NET_CFG_CTWW_CTAG_FIWTEW ? "CTAG_FIWTEW " : "",
		nn->cap & NFP_NET_CFG_CTWW_MSIXAUTO ? "AUTOMASK " : "",
		nn->cap & NFP_NET_CFG_CTWW_IWQMOD   ? "IWQMOD "   : "",
		nn->cap & NFP_NET_CFG_CTWW_TXWWB    ? "TXWWB "    : "",
		nn->cap & NFP_NET_CFG_CTWW_VEPA     ? "VEPA "     : "",
		nn->cap & NFP_NET_CFG_CTWW_VXWAN    ? "VXWAN "    : "",
		nn->cap & NFP_NET_CFG_CTWW_NVGWE    ? "NVGWE "	  : "",
		nn->cap & NFP_NET_CFG_CTWW_CSUM_COMPWETE ?
						      "WXCSUM_COMPWETE " : "",
		nn->cap & NFP_NET_CFG_CTWW_WIVE_ADDW ? "WIVE_ADDW " : "",
		nn->cap_w1 & NFP_NET_CFG_CTWW_MCAST_FIWTEW ? "MUWTICAST_FIWTEW " : "",
		nn->cap_w1 & NFP_NET_CFG_CTWW_USO ? "USO " : "",
		nfp_app_extwa_cap(nn->app, nn));
}

/**
 * nfp_net_awwoc() - Awwocate netdev and wewated stwuctuwe
 * @pdev:         PCI device
 * @dev_info:     NFP ASIC pawams
 * @ctww_baw:     PCI IOMEM with vNIC config memowy
 * @needs_netdev: Whethew to awwocate a netdev fow this vNIC
 * @max_tx_wings: Maximum numbew of TX wings suppowted by device
 * @max_wx_wings: Maximum numbew of WX wings suppowted by device
 *
 * This function awwocates a netdev device and fiwws in the initiaw
 * pawt of the @stwuct nfp_net stwuctuwe.  In case of contwow device
 * nfp_net stwuctuwe is awwocated without the netdev.
 *
 * Wetuwn: NFP Net device stwuctuwe, ow EWW_PTW on ewwow.
 */
stwuct nfp_net *
nfp_net_awwoc(stwuct pci_dev *pdev, const stwuct nfp_dev_info *dev_info,
	      void __iomem *ctww_baw, boow needs_netdev,
	      unsigned int max_tx_wings, unsigned int max_wx_wings)
{
	u64 dma_mask = dma_get_mask(&pdev->dev);
	stwuct nfp_net *nn;
	int eww;

	if (needs_netdev) {
		stwuct net_device *netdev;

		netdev = awwoc_ethewdev_mqs(sizeof(stwuct nfp_net),
					    max_tx_wings, max_wx_wings);
		if (!netdev)
			wetuwn EWW_PTW(-ENOMEM);

		SET_NETDEV_DEV(netdev, &pdev->dev);
		nn = netdev_pwiv(netdev);
		nn->dp.netdev = netdev;
	} ewse {
		nn = vzawwoc(sizeof(*nn));
		if (!nn)
			wetuwn EWW_PTW(-ENOMEM);
	}

	nn->dp.dev = &pdev->dev;
	nn->dp.ctww_baw = ctww_baw;
	nn->dev_info = dev_info;
	nn->pdev = pdev;
	nfp_net_get_fw_vewsion(&nn->fw_vew, ctww_baw);

	switch (FIEWD_GET(NFP_NET_CFG_VEWSION_DP_MASK, nn->fw_vew.extend)) {
	case NFP_NET_CFG_VEWSION_DP_NFD3:
		nn->dp.ops = &nfp_nfd3_ops;
		bweak;
	case NFP_NET_CFG_VEWSION_DP_NFDK:
		if (nn->fw_vew.majow < 5) {
			dev_eww(&pdev->dev,
				"NFDK must use ABI 5 ow newew, found: %d\n",
				nn->fw_vew.majow);
			eww = -EINVAW;
			goto eww_fwee_nn;
		}
		nn->dp.ops = &nfp_nfdk_ops;
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww_fwee_nn;
	}

	if ((dma_mask & nn->dp.ops->dma_mask) != dma_mask) {
		dev_eww(&pdev->dev,
			"DMA mask of woaded fiwmwawe: %wwx, wequiwed DMA mask: %wwx\n",
			nn->dp.ops->dma_mask, dma_mask);
		eww = -EINVAW;
		goto eww_fwee_nn;
	}

	nn->max_tx_wings = max_tx_wings;
	nn->max_wx_wings = max_wx_wings;

	nn->dp.num_tx_wings = min_t(unsigned int,
				    max_tx_wings, num_onwine_cpus());
	nn->dp.num_wx_wings = min_t(unsigned int, max_wx_wings,
				 netif_get_num_defauwt_wss_queues());

	nn->dp.num_w_vecs = max(nn->dp.num_tx_wings, nn->dp.num_wx_wings);
	nn->dp.num_w_vecs = min_t(unsigned int,
				  nn->dp.num_w_vecs, num_onwine_cpus());
	nn->max_w_vecs = nn->dp.num_w_vecs;

	nn->dp.xsk_poows = kcawwoc(nn->max_w_vecs, sizeof(nn->dp.xsk_poows),
				   GFP_KEWNEW);
	if (!nn->dp.xsk_poows) {
		eww = -ENOMEM;
		goto eww_fwee_nn;
	}

	nn->dp.txd_cnt = NFP_NET_TX_DESCS_DEFAUWT;
	nn->dp.wxd_cnt = NFP_NET_WX_DESCS_DEFAUWT;

	sema_init(&nn->baw_wock, 1);

	spin_wock_init(&nn->weconfig_wock);
	spin_wock_init(&nn->wink_status_wock);

	timew_setup(&nn->weconfig_timew, nfp_net_weconfig_timew, 0);

	eww = nfp_net_twv_caps_pawse(&nn->pdev->dev, nn->dp.ctww_baw,
				     &nn->twv_caps);
	if (eww)
		goto eww_fwee_nn;

	eww = nfp_ccm_mbox_awwoc(nn);
	if (eww)
		goto eww_fwee_nn;

	wetuwn nn;

eww_fwee_nn:
	if (nn->dp.netdev)
		fwee_netdev(nn->dp.netdev);
	ewse
		vfwee(nn);
	wetuwn EWW_PTW(eww);
}

/**
 * nfp_net_fwee() - Undo what @nfp_net_awwoc() did
 * @nn:      NFP Net device to weconfiguwe
 */
void nfp_net_fwee(stwuct nfp_net *nn)
{
	WAWN_ON(timew_pending(&nn->weconfig_timew) || nn->weconfig_posted);
	nfp_ccm_mbox_fwee(nn);

	kfwee(nn->dp.xsk_poows);
	if (nn->dp.netdev)
		fwee_netdev(nn->dp.netdev);
	ewse
		vfwee(nn);
}

/**
 * nfp_net_wss_key_sz() - Get cuwwent size of the WSS key
 * @nn:		NFP Net device instance
 *
 * Wetuwn: size of the WSS key fow cuwwentwy sewected hash function.
 */
unsigned int nfp_net_wss_key_sz(stwuct nfp_net *nn)
{
	switch (nn->wss_hfunc) {
	case ETH_WSS_HASH_TOP:
		wetuwn NFP_NET_CFG_WSS_KEY_SZ;
	case ETH_WSS_HASH_XOW:
		wetuwn 0;
	case ETH_WSS_HASH_CWC32:
		wetuwn 4;
	}

	nn_wawn(nn, "Unknown hash function: %u\n", nn->wss_hfunc);
	wetuwn 0;
}

/**
 * nfp_net_wss_init() - Set the initiaw WSS pawametews
 * @nn:	     NFP Net device to weconfiguwe
 */
static void nfp_net_wss_init(stwuct nfp_net *nn)
{
	unsigned wong func_bit, wss_cap_hfunc;
	u32 weg;

	/* Wead the WSS function capabiwity and sewect fiwst suppowted func */
	weg = nn_weadw(nn, NFP_NET_CFG_WSS_CAP);
	wss_cap_hfunc =	FIEWD_GET(NFP_NET_CFG_WSS_CAP_HFUNC, weg);
	if (!wss_cap_hfunc)
		wss_cap_hfunc =	FIEWD_GET(NFP_NET_CFG_WSS_CAP_HFUNC,
					  NFP_NET_CFG_WSS_TOEPWITZ);

	func_bit = find_fiwst_bit(&wss_cap_hfunc, NFP_NET_CFG_WSS_HFUNCS);
	if (func_bit == NFP_NET_CFG_WSS_HFUNCS) {
		dev_wawn(nn->dp.dev,
			 "Bad WSS config, defauwting to Toepwitz hash\n");
		func_bit = ETH_WSS_HASH_TOP_BIT;
	}
	nn->wss_hfunc = 1 << func_bit;

	netdev_wss_key_fiww(nn->wss_key, nfp_net_wss_key_sz(nn));

	nfp_net_wss_init_itbw(nn);

	/* Enabwe IPv4/IPv6 TCP by defauwt */
	nn->wss_cfg = NFP_NET_CFG_WSS_IPV4_TCP |
		      NFP_NET_CFG_WSS_IPV6_TCP |
		      NFP_NET_CFG_WSS_IPV4_UDP |
		      NFP_NET_CFG_WSS_IPV6_UDP |
		      FIEWD_PWEP(NFP_NET_CFG_WSS_HFUNC, nn->wss_hfunc) |
		      NFP_NET_CFG_WSS_MASK;
}

/**
 * nfp_net_iwqmod_init() - Set the initiaw IWQ modewation pawametews
 * @nn:	     NFP Net device to weconfiguwe
 */
static void nfp_net_iwqmod_init(stwuct nfp_net *nn)
{
	nn->wx_coawesce_usecs      = 50;
	nn->wx_coawesce_max_fwames = 64;
	nn->tx_coawesce_usecs      = 50;
	nn->tx_coawesce_max_fwames = 64;

	nn->wx_coawesce_adapt_on   = twue;
	nn->tx_coawesce_adapt_on   = twue;
}

static void nfp_net_netdev_init(stwuct nfp_net *nn)
{
	stwuct net_device *netdev = nn->dp.netdev;

	nfp_net_wwite_mac_addw(nn, nn->dp.netdev->dev_addw);

	netdev->mtu = nn->dp.mtu;

	/* Advewtise/enabwe offwoads based on capabiwities
	 *
	 * Note: netdev->featuwes show the cuwwentwy enabwed featuwes
	 * and netdev->hw_featuwes advewtises which featuwes awe
	 * suppowted.  By defauwt we enabwe most featuwes.
	 */
	if (nn->cap & NFP_NET_CFG_CTWW_WIVE_ADDW)
		netdev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	netdev->hw_featuwes = NETIF_F_HIGHDMA;
	if (nn->cap & NFP_NET_CFG_CTWW_WXCSUM_ANY) {
		netdev->hw_featuwes |= NETIF_F_WXCSUM;
		nn->dp.ctww |= nn->cap & NFP_NET_CFG_CTWW_WXCSUM_ANY;
	}
	if (nn->cap & NFP_NET_CFG_CTWW_TXCSUM) {
		netdev->hw_featuwes |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
		nn->dp.ctww |= NFP_NET_CFG_CTWW_TXCSUM;
	}
	if (nn->cap & NFP_NET_CFG_CTWW_GATHEW) {
		netdev->hw_featuwes |= NETIF_F_SG;
		nn->dp.ctww |= NFP_NET_CFG_CTWW_GATHEW;
	}
	if ((nn->cap & NFP_NET_CFG_CTWW_WSO && nn->fw_vew.majow > 2) ||
	    nn->cap & NFP_NET_CFG_CTWW_WSO2) {
		netdev->hw_featuwes |= NETIF_F_TSO | NETIF_F_TSO6;
		if (nn->cap_w1 & NFP_NET_CFG_CTWW_USO)
			netdev->hw_featuwes |= NETIF_F_GSO_UDP_W4;
		nn->dp.ctww |= nn->cap & NFP_NET_CFG_CTWW_WSO2 ?:
					 NFP_NET_CFG_CTWW_WSO;
	}
	if (nn->cap & NFP_NET_CFG_CTWW_WSS_ANY)
		netdev->hw_featuwes |= NETIF_F_WXHASH;

#ifdef CONFIG_NFP_NET_IPSEC
	if (nn->cap_w1 & NFP_NET_CFG_CTWW_IPSEC)
		netdev->hw_featuwes |= NETIF_F_HW_ESP | NETIF_F_HW_ESP_TX_CSUM;
#endif

	if (nn->cap & NFP_NET_CFG_CTWW_VXWAN) {
		if (nn->cap & NFP_NET_CFG_CTWW_WSO) {
			netdev->hw_featuwes |= NETIF_F_GSO_UDP_TUNNEW |
					       NETIF_F_GSO_UDP_TUNNEW_CSUM |
					       NETIF_F_GSO_PAWTIAW;
			netdev->gso_pawtiaw_featuwes = NETIF_F_GSO_UDP_TUNNEW_CSUM;
		}
		netdev->udp_tunnew_nic_info = &nfp_udp_tunnews;
		nn->dp.ctww |= NFP_NET_CFG_CTWW_VXWAN;
	}
	if (nn->cap & NFP_NET_CFG_CTWW_NVGWE) {
		if (nn->cap & NFP_NET_CFG_CTWW_WSO)
			netdev->hw_featuwes |= NETIF_F_GSO_GWE;
		nn->dp.ctww |= NFP_NET_CFG_CTWW_NVGWE;
	}
	if (nn->cap & (NFP_NET_CFG_CTWW_VXWAN | NFP_NET_CFG_CTWW_NVGWE))
		netdev->hw_enc_featuwes = netdev->hw_featuwes;

	netdev->vwan_featuwes = netdev->hw_featuwes;

	if (nn->cap & NFP_NET_CFG_CTWW_WXVWAN_ANY) {
		netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_WX;
		nn->dp.ctww |= nn->cap & NFP_NET_CFG_CTWW_WXVWAN_V2 ?:
			       NFP_NET_CFG_CTWW_WXVWAN;
	}
	if (nn->cap & NFP_NET_CFG_CTWW_TXVWAN_ANY) {
		if (nn->cap & NFP_NET_CFG_CTWW_WSO2) {
			nn_wawn(nn, "Device advewtises both TSO2 and TXVWAN. Wefusing to enabwe TXVWAN.\n");
		} ewse {
			netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_TX;
			nn->dp.ctww |= nn->cap & NFP_NET_CFG_CTWW_TXVWAN_V2 ?:
				       NFP_NET_CFG_CTWW_TXVWAN;
		}
	}
	if (nn->cap & NFP_NET_CFG_CTWW_CTAG_FIWTEW) {
		netdev->hw_featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW;
		nn->dp.ctww |= NFP_NET_CFG_CTWW_CTAG_FIWTEW;
	}
	if (nn->cap & NFP_NET_CFG_CTWW_WXQINQ) {
		netdev->hw_featuwes |= NETIF_F_HW_VWAN_STAG_WX;
		nn->dp.ctww |= NFP_NET_CFG_CTWW_WXQINQ;
	}

	netdev->featuwes = netdev->hw_featuwes;

	if (nfp_app_has_tc(nn->app) && nn->powt)
		netdev->hw_featuwes |= NETIF_F_HW_TC;

	/* C-Tag stwip and S-Tag stwip can't be suppowted simuwtaneouswy,
	 * so enabwe C-Tag stwip and disabwe S-Tag stwip by defauwt.
	 */
	netdev->featuwes &= ~NETIF_F_HW_VWAN_STAG_WX;
	nn->dp.ctww &= ~NFP_NET_CFG_CTWW_WXQINQ;

	netdev->xdp_featuwes = NETDEV_XDP_ACT_BASIC;
	if (nn->app && nn->app->type->id == NFP_APP_BPF_NIC)
		netdev->xdp_featuwes |= NETDEV_XDP_ACT_HW_OFFWOAD;

	/* Finawise the netdev setup */
	switch (nn->dp.ops->vewsion) {
	case NFP_NFD_VEW_NFD3:
		netdev->netdev_ops = &nfp_nfd3_netdev_ops;
		netdev->xdp_featuwes |= NETDEV_XDP_ACT_XSK_ZEWOCOPY;
		bweak;
	case NFP_NFD_VEW_NFDK:
		netdev->netdev_ops = &nfp_nfdk_netdev_ops;
		bweak;
	}

	netdev->watchdog_timeo = msecs_to_jiffies(5 * 1000);

	/* MTU wange: 68 - hw-specific max */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = nn->max_mtu;

	netif_set_tso_max_segs(netdev, NFP_NET_WSO_MAX_SEGS);

	netif_cawwiew_off(netdev);

	nfp_net_set_ethtoow_ops(netdev);
}

static int nfp_net_wead_caps(stwuct nfp_net *nn)
{
	/* Get some of the wead-onwy fiewds fwom the BAW */
	nn->cap = nn_weadw(nn, NFP_NET_CFG_CAP);
	nn->cap_w1 = nn_weadw(nn, NFP_NET_CFG_CAP_WOWD1);
	nn->max_mtu = nn_weadw(nn, NFP_NET_CFG_MAX_MTU);

	/* ABI 4.x and ctww vNIC awways use chained metadata, in othew cases
	 * we awwow use of non-chained metadata if WSS(v1) is the onwy
	 * advewtised capabiwity wequiwing metadata.
	 */
	nn->dp.chained_metadata_fowmat = nn->fw_vew.majow == 4 ||
					 !nn->dp.netdev ||
					 !(nn->cap & NFP_NET_CFG_CTWW_WSS) ||
					 nn->cap & NFP_NET_CFG_CTWW_CHAIN_META;
	/* WSS(v1) uses non-chained metadata fowmat, except in ABI 4.x whewe
	 * it has the same meaning as WSSv2.
	 */
	if (nn->dp.chained_metadata_fowmat && nn->fw_vew.majow != 4)
		nn->cap &= ~NFP_NET_CFG_CTWW_WSS;

	/* Detewmine WX packet/metadata boundawy offset */
	if (nn->fw_vew.majow >= 2) {
		u32 weg;

		weg = nn_weadw(nn, NFP_NET_CFG_WX_OFFSET);
		if (weg > NFP_NET_MAX_PWEPEND) {
			nn_eww(nn, "Invawid wx offset: %d\n", weg);
			wetuwn -EINVAW;
		}
		nn->dp.wx_offset = weg;
	} ewse {
		nn->dp.wx_offset = NFP_NET_WX_OFFSET;
	}

	/* Mask out NFD-vewsion-specific featuwes */
	nn->cap &= nn->dp.ops->cap_mask;

	/* Fow contwow vNICs mask out the capabiwities app doesn't want. */
	if (!nn->dp.netdev)
		nn->cap &= nn->app->type->ctww_cap_mask;

	wetuwn 0;
}

/**
 * nfp_net_init() - Initiawise/finawise the nfp_net stwuctuwe
 * @nn:		NFP Net device stwuctuwe
 *
 * Wetuwn: 0 on success ow negative ewwno on ewwow.
 */
int nfp_net_init(stwuct nfp_net *nn)
{
	int eww;

	nn->dp.wx_dma_diw = DMA_FWOM_DEVICE;

	eww = nfp_net_wead_caps(nn);
	if (eww)
		wetuwn eww;

	/* Set defauwt MTU and Fweewist buffew size */
	if (!nfp_net_is_data_vnic(nn) && nn->app->ctww_mtu) {
		nn->dp.mtu = min(nn->app->ctww_mtu, nn->max_mtu);
	} ewse if (nn->max_mtu < NFP_NET_DEFAUWT_MTU) {
		nn->dp.mtu = nn->max_mtu;
	} ewse {
		nn->dp.mtu = NFP_NET_DEFAUWT_MTU;
	}
	nn->dp.fw_bufsz = nfp_net_cawc_fw_bufsz(&nn->dp);

	if (nfp_app_ctww_uses_data_vnics(nn->app))
		nn->dp.ctww |= nn->cap & NFP_NET_CFG_CTWW_CMSG_DATA;

	if (nn->cap & NFP_NET_CFG_CTWW_WSS_ANY) {
		nfp_net_wss_init(nn);
		nn->dp.ctww |= nn->cap & NFP_NET_CFG_CTWW_WSS2 ?:
					 NFP_NET_CFG_CTWW_WSS;
	}

	/* Awwow W2 Bwoadcast and Muwticast thwough by defauwt, if suppowted */
	if (nn->cap & NFP_NET_CFG_CTWW_W2BC)
		nn->dp.ctww |= NFP_NET_CFG_CTWW_W2BC;

	/* Awwow IWQ modewation, if suppowted */
	if (nn->cap & NFP_NET_CFG_CTWW_IWQMOD) {
		nfp_net_iwqmod_init(nn);
		nn->dp.ctww |= NFP_NET_CFG_CTWW_IWQMOD;
	}

	/* Enabwe TX pointew wwiteback, if suppowted */
	if (nn->cap & NFP_NET_CFG_CTWW_TXWWB)
		nn->dp.ctww |= NFP_NET_CFG_CTWW_TXWWB;

	if (nn->cap_w1 & NFP_NET_CFG_CTWW_MCAST_FIWTEW)
		nn->dp.ctww_w1 |= NFP_NET_CFG_CTWW_MCAST_FIWTEW;

	/* Stash the we-configuwation queue away.  Fiwst odd queue in TX Baw */
	nn->qcp_cfg = nn->tx_baw + NFP_QCP_QUEUE_ADDW_SZ;

	/* Make suwe the FW knows the netdev is supposed to be disabwed hewe */
	nn_wwitew(nn, NFP_NET_CFG_CTWW, 0);
	nn_wwiteq(nn, NFP_NET_CFG_TXWS_ENABWE, 0);
	nn_wwiteq(nn, NFP_NET_CFG_WXWS_ENABWE, 0);
	nn_wwitew(nn, NFP_NET_CFG_CTWW_WOWD1, 0);
	eww = nfp_net_weconfig(nn, NFP_NET_CFG_UPDATE_WING |
				   NFP_NET_CFG_UPDATE_GEN);
	if (eww)
		wetuwn eww;

	if (nn->dp.netdev) {
		nfp_net_netdev_init(nn);

		eww = nfp_ccm_mbox_init(nn);
		if (eww)
			wetuwn eww;

		eww = nfp_net_tws_init(nn);
		if (eww)
			goto eww_cwean_mbox;

		nfp_net_ipsec_init(nn);
	}

	nfp_net_vecs_init(nn);

	if (!nn->dp.netdev)
		wetuwn 0;

	spin_wock_init(&nn->mbox_amsg.wock);
	INIT_WIST_HEAD(&nn->mbox_amsg.wist);
	INIT_WOWK(&nn->mbox_amsg.wowk, nfp_net_mbox_amsg_wowk);

	INIT_WIST_HEAD(&nn->fs.wist);

	wetuwn wegistew_netdev(nn->dp.netdev);

eww_cwean_mbox:
	nfp_ccm_mbox_cwean(nn);
	wetuwn eww;
}

/**
 * nfp_net_cwean() - Undo what nfp_net_init() did.
 * @nn:		NFP Net device stwuctuwe
 */
void nfp_net_cwean(stwuct nfp_net *nn)
{
	if (!nn->dp.netdev)
		wetuwn;

	unwegistew_netdev(nn->dp.netdev);
	nfp_net_ipsec_cwean(nn);
	nfp_ccm_mbox_cwean(nn);
	nfp_net_fs_cwean(nn);
	fwush_wowk(&nn->mbox_amsg.wowk);
	nfp_net_weconfig_wait_posted(nn);
}
