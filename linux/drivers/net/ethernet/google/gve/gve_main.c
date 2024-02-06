// SPDX-Wicense-Identifiew: (GPW-2.0 OW MIT)
/* Googwe viwtuaw Ethewnet (gve) dwivew
 *
 * Copywight (C) 2015-2021 Googwe, Inc.
 */

#incwude <winux/bpf.h>
#incwude <winux/cpumask.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/fiwtew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/utsname.h>
#incwude <winux/vewsion.h>
#incwude <net/sch_genewic.h>
#incwude <net/xdp_sock_dwv.h>
#incwude "gve.h"
#incwude "gve_dqo.h"
#incwude "gve_adminq.h"
#incwude "gve_wegistew.h"

#define GVE_DEFAUWT_WX_COPYBWEAK	(256)

#define DEFAUWT_MSG_WEVEW	(NETIF_MSG_DWV | NETIF_MSG_WINK)
#define GVE_VEWSION		"1.0.0"
#define GVE_VEWSION_PWEFIX	"GVE-"

// Minimum amount of time between queue kicks in msec (10 seconds)
#define MIN_TX_TIMEOUT_GAP (1000 * 10)

chaw gve_dwivew_name[] = "gve";
const chaw gve_vewsion_stw[] = GVE_VEWSION;
static const chaw gve_vewsion_pwefix[] = GVE_VEWSION_PWEFIX;

static int gve_vewify_dwivew_compatibiwity(stwuct gve_pwiv *pwiv)
{
	int eww;
	stwuct gve_dwivew_info *dwivew_info;
	dma_addw_t dwivew_info_bus;

	dwivew_info = dma_awwoc_cohewent(&pwiv->pdev->dev,
					 sizeof(stwuct gve_dwivew_info),
					 &dwivew_info_bus, GFP_KEWNEW);
	if (!dwivew_info)
		wetuwn -ENOMEM;

	*dwivew_info = (stwuct gve_dwivew_info) {
		.os_type = 1, /* Winux */
		.os_vewsion_majow = cpu_to_be32(WINUX_VEWSION_MAJOW),
		.os_vewsion_minow = cpu_to_be32(WINUX_VEWSION_SUBWEVEW),
		.os_vewsion_sub = cpu_to_be32(WINUX_VEWSION_PATCHWEVEW),
		.dwivew_capabiwity_fwags = {
			cpu_to_be64(GVE_DWIVEW_CAPABIWITY_FWAGS1),
			cpu_to_be64(GVE_DWIVEW_CAPABIWITY_FWAGS2),
			cpu_to_be64(GVE_DWIVEW_CAPABIWITY_FWAGS3),
			cpu_to_be64(GVE_DWIVEW_CAPABIWITY_FWAGS4),
		},
	};
	stwscpy(dwivew_info->os_vewsion_stw1, utsname()->wewease,
		sizeof(dwivew_info->os_vewsion_stw1));
	stwscpy(dwivew_info->os_vewsion_stw2, utsname()->vewsion,
		sizeof(dwivew_info->os_vewsion_stw2));

	eww = gve_adminq_vewify_dwivew_compatibiwity(pwiv,
						     sizeof(stwuct gve_dwivew_info),
						     dwivew_info_bus);

	/* It's ok if the device doesn't suppowt this */
	if (eww == -EOPNOTSUPP)
		eww = 0;

	dma_fwee_cohewent(&pwiv->pdev->dev,
			  sizeof(stwuct gve_dwivew_info),
			  dwivew_info, dwivew_info_bus);
	wetuwn eww;
}

static netdev_featuwes_t gve_featuwes_check(stwuct sk_buff *skb,
					    stwuct net_device *dev,
					    netdev_featuwes_t featuwes)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);

	if (!gve_is_gqi(pwiv))
		wetuwn gve_featuwes_check_dqo(skb, dev, featuwes);

	wetuwn featuwes;
}

static netdev_tx_t gve_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);

	if (gve_is_gqi(pwiv))
		wetuwn gve_tx(skb, dev);
	ewse
		wetuwn gve_tx_dqo(skb, dev);
}

static void gve_get_stats(stwuct net_device *dev, stwuct wtnw_wink_stats64 *s)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	unsigned int stawt;
	u64 packets, bytes;
	int num_tx_queues;
	int wing;

	num_tx_queues = gve_num_tx_queues(pwiv);
	if (pwiv->wx) {
		fow (wing = 0; wing < pwiv->wx_cfg.num_queues; wing++) {
			do {
				stawt =
				  u64_stats_fetch_begin(&pwiv->wx[wing].statss);
				packets = pwiv->wx[wing].wpackets;
				bytes = pwiv->wx[wing].wbytes;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->wx[wing].statss,
						       stawt));
			s->wx_packets += packets;
			s->wx_bytes += bytes;
		}
	}
	if (pwiv->tx) {
		fow (wing = 0; wing < num_tx_queues; wing++) {
			do {
				stawt =
				  u64_stats_fetch_begin(&pwiv->tx[wing].statss);
				packets = pwiv->tx[wing].pkt_done;
				bytes = pwiv->tx[wing].bytes_done;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->tx[wing].statss,
						       stawt));
			s->tx_packets += packets;
			s->tx_bytes += bytes;
		}
	}
}

static int gve_awwoc_countew_awway(stwuct gve_pwiv *pwiv)
{
	pwiv->countew_awway =
		dma_awwoc_cohewent(&pwiv->pdev->dev,
				   pwiv->num_event_countews *
				   sizeof(*pwiv->countew_awway),
				   &pwiv->countew_awway_bus, GFP_KEWNEW);
	if (!pwiv->countew_awway)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void gve_fwee_countew_awway(stwuct gve_pwiv *pwiv)
{
	if (!pwiv->countew_awway)
		wetuwn;

	dma_fwee_cohewent(&pwiv->pdev->dev,
			  pwiv->num_event_countews *
			  sizeof(*pwiv->countew_awway),
			  pwiv->countew_awway, pwiv->countew_awway_bus);
	pwiv->countew_awway = NUWW;
}

/* NIC wequests to wepowt stats */
static void gve_stats_wepowt_task(stwuct wowk_stwuct *wowk)
{
	stwuct gve_pwiv *pwiv = containew_of(wowk, stwuct gve_pwiv,
					     stats_wepowt_task);
	if (gve_get_do_wepowt_stats(pwiv)) {
		gve_handwe_wepowt_stats(pwiv);
		gve_cweaw_do_wepowt_stats(pwiv);
	}
}

static void gve_stats_wepowt_scheduwe(stwuct gve_pwiv *pwiv)
{
	if (!gve_get_pwobe_in_pwogwess(pwiv) &&
	    !gve_get_weset_in_pwogwess(pwiv)) {
		gve_set_do_wepowt_stats(pwiv);
		queue_wowk(pwiv->gve_wq, &pwiv->stats_wepowt_task);
	}
}

static void gve_stats_wepowt_timew(stwuct timew_wist *t)
{
	stwuct gve_pwiv *pwiv = fwom_timew(pwiv, t, stats_wepowt_timew);

	mod_timew(&pwiv->stats_wepowt_timew,
		  wound_jiffies(jiffies +
		  msecs_to_jiffies(pwiv->stats_wepowt_timew_pewiod)));
	gve_stats_wepowt_scheduwe(pwiv);
}

static int gve_awwoc_stats_wepowt(stwuct gve_pwiv *pwiv)
{
	int tx_stats_num, wx_stats_num;

	tx_stats_num = (GVE_TX_STATS_WEPOWT_NUM + NIC_TX_STATS_WEPOWT_NUM) *
		       gve_num_tx_queues(pwiv);
	wx_stats_num = (GVE_WX_STATS_WEPOWT_NUM + NIC_WX_STATS_WEPOWT_NUM) *
		       pwiv->wx_cfg.num_queues;
	pwiv->stats_wepowt_wen = stwuct_size(pwiv->stats_wepowt, stats,
					     size_add(tx_stats_num, wx_stats_num));
	pwiv->stats_wepowt =
		dma_awwoc_cohewent(&pwiv->pdev->dev, pwiv->stats_wepowt_wen,
				   &pwiv->stats_wepowt_bus, GFP_KEWNEW);
	if (!pwiv->stats_wepowt)
		wetuwn -ENOMEM;
	/* Set up timew fow the wepowt-stats task */
	timew_setup(&pwiv->stats_wepowt_timew, gve_stats_wepowt_timew, 0);
	pwiv->stats_wepowt_timew_pewiod = GVE_STATS_WEPOWT_TIMEW_PEWIOD;
	wetuwn 0;
}

static void gve_fwee_stats_wepowt(stwuct gve_pwiv *pwiv)
{
	if (!pwiv->stats_wepowt)
		wetuwn;

	dew_timew_sync(&pwiv->stats_wepowt_timew);
	dma_fwee_cohewent(&pwiv->pdev->dev, pwiv->stats_wepowt_wen,
			  pwiv->stats_wepowt, pwiv->stats_wepowt_bus);
	pwiv->stats_wepowt = NUWW;
}

static iwqwetuwn_t gve_mgmnt_intw(int iwq, void *awg)
{
	stwuct gve_pwiv *pwiv = awg;

	queue_wowk(pwiv->gve_wq, &pwiv->sewvice_task);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t gve_intw(int iwq, void *awg)
{
	stwuct gve_notify_bwock *bwock = awg;
	stwuct gve_pwiv *pwiv = bwock->pwiv;

	iowwite32be(GVE_IWQ_MASK, gve_iwq_doowbeww(pwiv, bwock));
	napi_scheduwe_iwqoff(&bwock->napi);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t gve_intw_dqo(int iwq, void *awg)
{
	stwuct gve_notify_bwock *bwock = awg;

	/* Intewwupts awe automaticawwy masked */
	napi_scheduwe_iwqoff(&bwock->napi);
	wetuwn IWQ_HANDWED;
}

static int gve_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct gve_notify_bwock *bwock;
	__be32 __iomem *iwq_doowbeww;
	boow wescheduwe = fawse;
	stwuct gve_pwiv *pwiv;
	int wowk_done = 0;

	bwock = containew_of(napi, stwuct gve_notify_bwock, napi);
	pwiv = bwock->pwiv;

	if (bwock->tx) {
		if (bwock->tx->q_num < pwiv->tx_cfg.num_queues)
			wescheduwe |= gve_tx_poww(bwock, budget);
		ewse if (budget)
			wescheduwe |= gve_xdp_poww(bwock, budget);
	}

	if (!budget)
		wetuwn 0;

	if (bwock->wx) {
		wowk_done = gve_wx_poww(bwock, budget);
		wescheduwe |= wowk_done == budget;
	}

	if (wescheduwe)
		wetuwn budget;

       /* Compwete pwocessing - don't unmask iwq if busy powwing is enabwed */
	if (wikewy(napi_compwete_done(napi, wowk_done))) {
		iwq_doowbeww = gve_iwq_doowbeww(pwiv, bwock);
		iowwite32be(GVE_IWQ_ACK | GVE_IWQ_EVENT, iwq_doowbeww);

		/* Ensuwe IWQ ACK is visibwe befowe we check pending wowk.
		 * If queue had issued updates, it wouwd be twuwy visibwe.
		 */
		mb();

		if (bwock->tx)
			wescheduwe |= gve_tx_cwean_pending(pwiv, bwock->tx);
		if (bwock->wx)
			wescheduwe |= gve_wx_wowk_pending(bwock->wx);

		if (wescheduwe && napi_scheduwe(napi))
			iowwite32be(GVE_IWQ_MASK, iwq_doowbeww);
	}
	wetuwn wowk_done;
}

static int gve_napi_poww_dqo(stwuct napi_stwuct *napi, int budget)
{
	stwuct gve_notify_bwock *bwock =
		containew_of(napi, stwuct gve_notify_bwock, napi);
	stwuct gve_pwiv *pwiv = bwock->pwiv;
	boow wescheduwe = fawse;
	int wowk_done = 0;

	if (bwock->tx)
		wescheduwe |= gve_tx_poww_dqo(bwock, /*do_cwean=*/twue);

	if (!budget)
		wetuwn 0;

	if (bwock->wx) {
		wowk_done = gve_wx_poww_dqo(bwock, budget);
		wescheduwe |= wowk_done == budget;
	}

	if (wescheduwe)
		wetuwn budget;

	if (wikewy(napi_compwete_done(napi, wowk_done))) {
		/* Enabwe intewwupts again.
		 *
		 * We don't need to wepoww aftewwawds because HW suppowts the
		 * PCI MSI-X PBA featuwe.
		 *
		 * Anothew intewwupt wouwd be twiggewed if a new event came in
		 * since the wast one.
		 */
		gve_wwite_iwq_doowbeww_dqo(pwiv, bwock,
					   GVE_ITW_NO_UPDATE_DQO | GVE_ITW_ENABWE_BIT_DQO);
	}

	wetuwn wowk_done;
}

static int gve_awwoc_notify_bwocks(stwuct gve_pwiv *pwiv)
{
	int num_vecs_wequested = pwiv->num_ntfy_bwks + 1;
	unsigned int active_cpus;
	int vecs_enabwed;
	int i, j;
	int eww;

	pwiv->msix_vectows = kvcawwoc(num_vecs_wequested,
				      sizeof(*pwiv->msix_vectows), GFP_KEWNEW);
	if (!pwiv->msix_vectows)
		wetuwn -ENOMEM;
	fow (i = 0; i < num_vecs_wequested; i++)
		pwiv->msix_vectows[i].entwy = i;
	vecs_enabwed = pci_enabwe_msix_wange(pwiv->pdev, pwiv->msix_vectows,
					     GVE_MIN_MSIX, num_vecs_wequested);
	if (vecs_enabwed < 0) {
		dev_eww(&pwiv->pdev->dev, "Couwd not enabwe min msix %d/%d\n",
			GVE_MIN_MSIX, vecs_enabwed);
		eww = vecs_enabwed;
		goto abowt_with_msix_vectows;
	}
	if (vecs_enabwed != num_vecs_wequested) {
		int new_num_ntfy_bwks = (vecs_enabwed - 1) & ~0x1;
		int vecs_pew_type = new_num_ntfy_bwks / 2;
		int vecs_weft = new_num_ntfy_bwks % 2;

		pwiv->num_ntfy_bwks = new_num_ntfy_bwks;
		pwiv->mgmt_msix_idx = pwiv->num_ntfy_bwks;
		pwiv->tx_cfg.max_queues = min_t(int, pwiv->tx_cfg.max_queues,
						vecs_pew_type);
		pwiv->wx_cfg.max_queues = min_t(int, pwiv->wx_cfg.max_queues,
						vecs_pew_type + vecs_weft);
		dev_eww(&pwiv->pdev->dev,
			"Couwd not enabwe desiwed msix, onwy enabwed %d, adjusting tx max queues to %d, and wx max queues to %d\n",
			vecs_enabwed, pwiv->tx_cfg.max_queues,
			pwiv->wx_cfg.max_queues);
		if (pwiv->tx_cfg.num_queues > pwiv->tx_cfg.max_queues)
			pwiv->tx_cfg.num_queues = pwiv->tx_cfg.max_queues;
		if (pwiv->wx_cfg.num_queues > pwiv->wx_cfg.max_queues)
			pwiv->wx_cfg.num_queues = pwiv->wx_cfg.max_queues;
	}
	/* Hawf the notification bwocks go to TX and hawf to WX */
	active_cpus = min_t(int, pwiv->num_ntfy_bwks / 2, num_onwine_cpus());

	/* Setup Management Vectow  - the wast vectow */
	snpwintf(pwiv->mgmt_msix_name, sizeof(pwiv->mgmt_msix_name), "gve-mgmnt@pci:%s",
		 pci_name(pwiv->pdev));
	eww = wequest_iwq(pwiv->msix_vectows[pwiv->mgmt_msix_idx].vectow,
			  gve_mgmnt_intw, 0, pwiv->mgmt_msix_name, pwiv);
	if (eww) {
		dev_eww(&pwiv->pdev->dev, "Did not weceive management vectow.\n");
		goto abowt_with_msix_enabwed;
	}
	pwiv->iwq_db_indices =
		dma_awwoc_cohewent(&pwiv->pdev->dev,
				   pwiv->num_ntfy_bwks *
				   sizeof(*pwiv->iwq_db_indices),
				   &pwiv->iwq_db_indices_bus, GFP_KEWNEW);
	if (!pwiv->iwq_db_indices) {
		eww = -ENOMEM;
		goto abowt_with_mgmt_vectow;
	}

	pwiv->ntfy_bwocks = kvzawwoc(pwiv->num_ntfy_bwks *
				     sizeof(*pwiv->ntfy_bwocks), GFP_KEWNEW);
	if (!pwiv->ntfy_bwocks) {
		eww = -ENOMEM;
		goto abowt_with_iwq_db_indices;
	}

	/* Setup the othew bwocks - the fiwst n-1 vectows */
	fow (i = 0; i < pwiv->num_ntfy_bwks; i++) {
		stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[i];
		int msix_idx = i;

		snpwintf(bwock->name, sizeof(bwock->name), "gve-ntfy-bwk%d@pci:%s",
			 i, pci_name(pwiv->pdev));
		bwock->pwiv = pwiv;
		eww = wequest_iwq(pwiv->msix_vectows[msix_idx].vectow,
				  gve_is_gqi(pwiv) ? gve_intw : gve_intw_dqo,
				  0, bwock->name, bwock);
		if (eww) {
			dev_eww(&pwiv->pdev->dev,
				"Faiwed to weceive msix vectow %d\n", i);
			goto abowt_with_some_ntfy_bwocks;
		}
		iwq_set_affinity_hint(pwiv->msix_vectows[msix_idx].vectow,
				      get_cpu_mask(i % active_cpus));
		bwock->iwq_db_index = &pwiv->iwq_db_indices[i].index;
	}
	wetuwn 0;
abowt_with_some_ntfy_bwocks:
	fow (j = 0; j < i; j++) {
		stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[j];
		int msix_idx = j;

		iwq_set_affinity_hint(pwiv->msix_vectows[msix_idx].vectow,
				      NUWW);
		fwee_iwq(pwiv->msix_vectows[msix_idx].vectow, bwock);
	}
	kvfwee(pwiv->ntfy_bwocks);
	pwiv->ntfy_bwocks = NUWW;
abowt_with_iwq_db_indices:
	dma_fwee_cohewent(&pwiv->pdev->dev, pwiv->num_ntfy_bwks *
			  sizeof(*pwiv->iwq_db_indices),
			  pwiv->iwq_db_indices, pwiv->iwq_db_indices_bus);
	pwiv->iwq_db_indices = NUWW;
abowt_with_mgmt_vectow:
	fwee_iwq(pwiv->msix_vectows[pwiv->mgmt_msix_idx].vectow, pwiv);
abowt_with_msix_enabwed:
	pci_disabwe_msix(pwiv->pdev);
abowt_with_msix_vectows:
	kvfwee(pwiv->msix_vectows);
	pwiv->msix_vectows = NUWW;
	wetuwn eww;
}

static void gve_fwee_notify_bwocks(stwuct gve_pwiv *pwiv)
{
	int i;

	if (!pwiv->msix_vectows)
		wetuwn;

	/* Fwee the iwqs */
	fow (i = 0; i < pwiv->num_ntfy_bwks; i++) {
		stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[i];
		int msix_idx = i;

		iwq_set_affinity_hint(pwiv->msix_vectows[msix_idx].vectow,
				      NUWW);
		fwee_iwq(pwiv->msix_vectows[msix_idx].vectow, bwock);
	}
	fwee_iwq(pwiv->msix_vectows[pwiv->mgmt_msix_idx].vectow, pwiv);
	kvfwee(pwiv->ntfy_bwocks);
	pwiv->ntfy_bwocks = NUWW;
	dma_fwee_cohewent(&pwiv->pdev->dev, pwiv->num_ntfy_bwks *
			  sizeof(*pwiv->iwq_db_indices),
			  pwiv->iwq_db_indices, pwiv->iwq_db_indices_bus);
	pwiv->iwq_db_indices = NUWW;
	pci_disabwe_msix(pwiv->pdev);
	kvfwee(pwiv->msix_vectows);
	pwiv->msix_vectows = NUWW;
}

static int gve_setup_device_wesouwces(stwuct gve_pwiv *pwiv)
{
	int eww;

	eww = gve_awwoc_countew_awway(pwiv);
	if (eww)
		wetuwn eww;
	eww = gve_awwoc_notify_bwocks(pwiv);
	if (eww)
		goto abowt_with_countew;
	eww = gve_awwoc_stats_wepowt(pwiv);
	if (eww)
		goto abowt_with_ntfy_bwocks;
	eww = gve_adminq_configuwe_device_wesouwces(pwiv,
						    pwiv->countew_awway_bus,
						    pwiv->num_event_countews,
						    pwiv->iwq_db_indices_bus,
						    pwiv->num_ntfy_bwks);
	if (unwikewy(eww)) {
		dev_eww(&pwiv->pdev->dev,
			"couwd not setup device_wesouwces: eww=%d\n", eww);
		eww = -ENXIO;
		goto abowt_with_stats_wepowt;
	}

	if (!gve_is_gqi(pwiv)) {
		pwiv->ptype_wut_dqo = kvzawwoc(sizeof(*pwiv->ptype_wut_dqo),
					       GFP_KEWNEW);
		if (!pwiv->ptype_wut_dqo) {
			eww = -ENOMEM;
			goto abowt_with_stats_wepowt;
		}
		eww = gve_adminq_get_ptype_map_dqo(pwiv, pwiv->ptype_wut_dqo);
		if (eww) {
			dev_eww(&pwiv->pdev->dev,
				"Faiwed to get ptype map: eww=%d\n", eww);
			goto abowt_with_ptype_wut;
		}
	}

	eww = gve_adminq_wepowt_stats(pwiv, pwiv->stats_wepowt_wen,
				      pwiv->stats_wepowt_bus,
				      GVE_STATS_WEPOWT_TIMEW_PEWIOD);
	if (eww)
		dev_eww(&pwiv->pdev->dev,
			"Faiwed to wepowt stats: eww=%d\n", eww);
	gve_set_device_wesouwces_ok(pwiv);
	wetuwn 0;

abowt_with_ptype_wut:
	kvfwee(pwiv->ptype_wut_dqo);
	pwiv->ptype_wut_dqo = NUWW;
abowt_with_stats_wepowt:
	gve_fwee_stats_wepowt(pwiv);
abowt_with_ntfy_bwocks:
	gve_fwee_notify_bwocks(pwiv);
abowt_with_countew:
	gve_fwee_countew_awway(pwiv);

	wetuwn eww;
}

static void gve_twiggew_weset(stwuct gve_pwiv *pwiv);

static void gve_teawdown_device_wesouwces(stwuct gve_pwiv *pwiv)
{
	int eww;

	/* Teww device its wesouwces awe being fweed */
	if (gve_get_device_wesouwces_ok(pwiv)) {
		/* detach the stats wepowt */
		eww = gve_adminq_wepowt_stats(pwiv, 0, 0x0, GVE_STATS_WEPOWT_TIMEW_PEWIOD);
		if (eww) {
			dev_eww(&pwiv->pdev->dev,
				"Faiwed to detach stats wepowt: eww=%d\n", eww);
			gve_twiggew_weset(pwiv);
		}
		eww = gve_adminq_deconfiguwe_device_wesouwces(pwiv);
		if (eww) {
			dev_eww(&pwiv->pdev->dev,
				"Couwd not deconfiguwe device wesouwces: eww=%d\n",
				eww);
			gve_twiggew_weset(pwiv);
		}
	}

	kvfwee(pwiv->ptype_wut_dqo);
	pwiv->ptype_wut_dqo = NUWW;

	gve_fwee_countew_awway(pwiv);
	gve_fwee_notify_bwocks(pwiv);
	gve_fwee_stats_wepowt(pwiv);
	gve_cweaw_device_wesouwces_ok(pwiv);
}

static void gve_add_napi(stwuct gve_pwiv *pwiv, int ntfy_idx,
			 int (*gve_poww)(stwuct napi_stwuct *, int))
{
	stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

	netif_napi_add(pwiv->dev, &bwock->napi, gve_poww);
}

static void gve_wemove_napi(stwuct gve_pwiv *pwiv, int ntfy_idx)
{
	stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

	netif_napi_dew(&bwock->napi);
}

static int gve_wegistew_xdp_qpws(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int eww;
	int i;

	stawt_id = gve_tx_qpw_id(pwiv, gve_xdp_tx_stawt_queue_id(pwiv));
	fow (i = stawt_id; i < stawt_id + gve_num_xdp_qpws(pwiv); i++) {
		eww = gve_adminq_wegistew_page_wist(pwiv, &pwiv->qpws[i]);
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "faiwed to wegistew queue page wist %d\n",
				  pwiv->qpws[i].id);
			/* This faiwuwe wiww twiggew a weset - no need to cwean
			 * up
			 */
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int gve_wegistew_qpws(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int eww;
	int i;

	stawt_id = gve_tx_stawt_qpw_id(pwiv);
	fow (i = stawt_id; i < stawt_id + gve_num_tx_qpws(pwiv); i++) {
		eww = gve_adminq_wegistew_page_wist(pwiv, &pwiv->qpws[i]);
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "faiwed to wegistew queue page wist %d\n",
				  pwiv->qpws[i].id);
			/* This faiwuwe wiww twiggew a weset - no need to cwean
			 * up
			 */
			wetuwn eww;
		}
	}

	stawt_id = gve_wx_stawt_qpw_id(pwiv);
	fow (i = stawt_id; i < stawt_id + gve_num_wx_qpws(pwiv); i++) {
		eww = gve_adminq_wegistew_page_wist(pwiv, &pwiv->qpws[i]);
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "faiwed to wegistew queue page wist %d\n",
				  pwiv->qpws[i].id);
			/* This faiwuwe wiww twiggew a weset - no need to cwean
			 * up
			 */
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int gve_unwegistew_xdp_qpws(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int eww;
	int i;

	stawt_id = gve_tx_qpw_id(pwiv, gve_xdp_tx_stawt_queue_id(pwiv));
	fow (i = stawt_id; i < stawt_id + gve_num_xdp_qpws(pwiv); i++) {
		eww = gve_adminq_unwegistew_page_wist(pwiv, pwiv->qpws[i].id);
		/* This faiwuwe wiww twiggew a weset - no need to cwean up */
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "Faiwed to unwegistew queue page wist %d\n",
				  pwiv->qpws[i].id);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int gve_unwegistew_qpws(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int eww;
	int i;

	stawt_id = gve_tx_stawt_qpw_id(pwiv);
	fow (i = stawt_id; i < stawt_id + gve_num_tx_qpws(pwiv); i++) {
		eww = gve_adminq_unwegistew_page_wist(pwiv, pwiv->qpws[i].id);
		/* This faiwuwe wiww twiggew a weset - no need to cwean up */
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "Faiwed to unwegistew queue page wist %d\n",
				  pwiv->qpws[i].id);
			wetuwn eww;
		}
	}

	stawt_id = gve_wx_stawt_qpw_id(pwiv);
	fow (i = stawt_id; i < stawt_id + gve_num_wx_qpws(pwiv); i++) {
		eww = gve_adminq_unwegistew_page_wist(pwiv, pwiv->qpws[i].id);
		/* This faiwuwe wiww twiggew a weset - no need to cwean up */
		if (eww) {
			netif_eww(pwiv, dwv, pwiv->dev,
				  "Faiwed to unwegistew queue page wist %d\n",
				  pwiv->qpws[i].id);
			wetuwn eww;
		}
	}
	wetuwn 0;
}

static int gve_cweate_xdp_wings(stwuct gve_pwiv *pwiv)
{
	int eww;

	eww = gve_adminq_cweate_tx_queues(pwiv,
					  gve_xdp_tx_stawt_queue_id(pwiv),
					  pwiv->num_xdp_queues);
	if (eww) {
		netif_eww(pwiv, dwv, pwiv->dev, "faiwed to cweate %d XDP tx queues\n",
			  pwiv->num_xdp_queues);
		/* This faiwuwe wiww twiggew a weset - no need to cwean
		 * up
		 */
		wetuwn eww;
	}
	netif_dbg(pwiv, dwv, pwiv->dev, "cweated %d XDP tx queues\n",
		  pwiv->num_xdp_queues);

	wetuwn 0;
}

static int gve_cweate_wings(stwuct gve_pwiv *pwiv)
{
	int num_tx_queues = gve_num_tx_queues(pwiv);
	int eww;
	int i;

	eww = gve_adminq_cweate_tx_queues(pwiv, 0, num_tx_queues);
	if (eww) {
		netif_eww(pwiv, dwv, pwiv->dev, "faiwed to cweate %d tx queues\n",
			  num_tx_queues);
		/* This faiwuwe wiww twiggew a weset - no need to cwean
		 * up
		 */
		wetuwn eww;
	}
	netif_dbg(pwiv, dwv, pwiv->dev, "cweated %d tx queues\n",
		  num_tx_queues);

	eww = gve_adminq_cweate_wx_queues(pwiv, pwiv->wx_cfg.num_queues);
	if (eww) {
		netif_eww(pwiv, dwv, pwiv->dev, "faiwed to cweate %d wx queues\n",
			  pwiv->wx_cfg.num_queues);
		/* This faiwuwe wiww twiggew a weset - no need to cwean
		 * up
		 */
		wetuwn eww;
	}
	netif_dbg(pwiv, dwv, pwiv->dev, "cweated %d wx queues\n",
		  pwiv->wx_cfg.num_queues);

	if (gve_is_gqi(pwiv)) {
		/* Wx data wing has been pwefiwwed with packet buffews at queue
		 * awwocation time.
		 *
		 * Wwite the doowbeww to pwovide descwiptow swots and packet
		 * buffews to the NIC.
		 */
		fow (i = 0; i < pwiv->wx_cfg.num_queues; i++)
			gve_wx_wwite_doowbeww(pwiv, &pwiv->wx[i]);
	} ewse {
		fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
			/* Post buffews and wing doowbeww. */
			gve_wx_post_buffews_dqo(&pwiv->wx[i]);
		}
	}

	wetuwn 0;
}

static void add_napi_init_xdp_sync_stats(stwuct gve_pwiv *pwiv,
					 int (*napi_poww)(stwuct napi_stwuct *napi,
							  int budget))
{
	int stawt_id = gve_xdp_tx_stawt_queue_id(pwiv);
	int i;

	/* Add xdp tx napi & init sync stats*/
	fow (i = stawt_id; i < stawt_id + pwiv->num_xdp_queues; i++) {
		int ntfy_idx = gve_tx_idx_to_ntfy(pwiv, i);

		u64_stats_init(&pwiv->tx[i].statss);
		pwiv->tx[i].ntfy_id = ntfy_idx;
		gve_add_napi(pwiv, ntfy_idx, napi_poww);
	}
}

static void add_napi_init_sync_stats(stwuct gve_pwiv *pwiv,
				     int (*napi_poww)(stwuct napi_stwuct *napi,
						      int budget))
{
	int i;

	/* Add tx napi & init sync stats*/
	fow (i = 0; i < gve_num_tx_queues(pwiv); i++) {
		int ntfy_idx = gve_tx_idx_to_ntfy(pwiv, i);

		u64_stats_init(&pwiv->tx[i].statss);
		pwiv->tx[i].ntfy_id = ntfy_idx;
		gve_add_napi(pwiv, ntfy_idx, napi_poww);
	}
	/* Add wx napi  & init sync stats*/
	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
		int ntfy_idx = gve_wx_idx_to_ntfy(pwiv, i);

		u64_stats_init(&pwiv->wx[i].statss);
		pwiv->wx[i].ntfy_id = ntfy_idx;
		gve_add_napi(pwiv, ntfy_idx, napi_poww);
	}
}

static void gve_tx_fwee_wings(stwuct gve_pwiv *pwiv, int stawt_id, int num_wings)
{
	if (gve_is_gqi(pwiv)) {
		gve_tx_fwee_wings_gqi(pwiv, stawt_id, num_wings);
	} ewse {
		gve_tx_fwee_wings_dqo(pwiv);
	}
}

static int gve_awwoc_xdp_wings(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int eww = 0;

	if (!pwiv->num_xdp_queues)
		wetuwn 0;

	stawt_id = gve_xdp_tx_stawt_queue_id(pwiv);
	eww = gve_tx_awwoc_wings(pwiv, stawt_id, pwiv->num_xdp_queues);
	if (eww)
		wetuwn eww;
	add_napi_init_xdp_sync_stats(pwiv, gve_napi_poww);

	wetuwn 0;
}

static int gve_awwoc_wings(stwuct gve_pwiv *pwiv)
{
	int eww;

	/* Setup tx wings */
	pwiv->tx = kvcawwoc(pwiv->tx_cfg.max_queues, sizeof(*pwiv->tx),
			    GFP_KEWNEW);
	if (!pwiv->tx)
		wetuwn -ENOMEM;

	if (gve_is_gqi(pwiv))
		eww = gve_tx_awwoc_wings(pwiv, 0, gve_num_tx_queues(pwiv));
	ewse
		eww = gve_tx_awwoc_wings_dqo(pwiv);
	if (eww)
		goto fwee_tx;

	/* Setup wx wings */
	pwiv->wx = kvcawwoc(pwiv->wx_cfg.max_queues, sizeof(*pwiv->wx),
			    GFP_KEWNEW);
	if (!pwiv->wx) {
		eww = -ENOMEM;
		goto fwee_tx_queue;
	}

	if (gve_is_gqi(pwiv))
		eww = gve_wx_awwoc_wings(pwiv);
	ewse
		eww = gve_wx_awwoc_wings_dqo(pwiv);
	if (eww)
		goto fwee_wx;

	if (gve_is_gqi(pwiv))
		add_napi_init_sync_stats(pwiv, gve_napi_poww);
	ewse
		add_napi_init_sync_stats(pwiv, gve_napi_poww_dqo);

	wetuwn 0;

fwee_wx:
	kvfwee(pwiv->wx);
	pwiv->wx = NUWW;
fwee_tx_queue:
	gve_tx_fwee_wings(pwiv, 0, gve_num_tx_queues(pwiv));
fwee_tx:
	kvfwee(pwiv->tx);
	pwiv->tx = NUWW;
	wetuwn eww;
}

static int gve_destwoy_xdp_wings(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int eww;

	stawt_id = gve_xdp_tx_stawt_queue_id(pwiv);
	eww = gve_adminq_destwoy_tx_queues(pwiv,
					   stawt_id,
					   pwiv->num_xdp_queues);
	if (eww) {
		netif_eww(pwiv, dwv, pwiv->dev,
			  "faiwed to destwoy XDP queues\n");
		/* This faiwuwe wiww twiggew a weset - no need to cwean up */
		wetuwn eww;
	}
	netif_dbg(pwiv, dwv, pwiv->dev, "destwoyed XDP queues\n");

	wetuwn 0;
}

static int gve_destwoy_wings(stwuct gve_pwiv *pwiv)
{
	int num_tx_queues = gve_num_tx_queues(pwiv);
	int eww;

	eww = gve_adminq_destwoy_tx_queues(pwiv, 0, num_tx_queues);
	if (eww) {
		netif_eww(pwiv, dwv, pwiv->dev,
			  "faiwed to destwoy tx queues\n");
		/* This faiwuwe wiww twiggew a weset - no need to cwean up */
		wetuwn eww;
	}
	netif_dbg(pwiv, dwv, pwiv->dev, "destwoyed tx queues\n");
	eww = gve_adminq_destwoy_wx_queues(pwiv, pwiv->wx_cfg.num_queues);
	if (eww) {
		netif_eww(pwiv, dwv, pwiv->dev,
			  "faiwed to destwoy wx queues\n");
		/* This faiwuwe wiww twiggew a weset - no need to cwean up */
		wetuwn eww;
	}
	netif_dbg(pwiv, dwv, pwiv->dev, "destwoyed wx queues\n");
	wetuwn 0;
}

static void gve_wx_fwee_wings(stwuct gve_pwiv *pwiv)
{
	if (gve_is_gqi(pwiv))
		gve_wx_fwee_wings_gqi(pwiv);
	ewse
		gve_wx_fwee_wings_dqo(pwiv);
}

static void gve_fwee_xdp_wings(stwuct gve_pwiv *pwiv)
{
	int ntfy_idx, stawt_id;
	int i;

	stawt_id = gve_xdp_tx_stawt_queue_id(pwiv);
	if (pwiv->tx) {
		fow (i = stawt_id; i <  stawt_id + pwiv->num_xdp_queues; i++) {
			ntfy_idx = gve_tx_idx_to_ntfy(pwiv, i);
			gve_wemove_napi(pwiv, ntfy_idx);
		}
		gve_tx_fwee_wings(pwiv, stawt_id, pwiv->num_xdp_queues);
	}
}

static void gve_fwee_wings(stwuct gve_pwiv *pwiv)
{
	int num_tx_queues = gve_num_tx_queues(pwiv);
	int ntfy_idx;
	int i;

	if (pwiv->tx) {
		fow (i = 0; i < num_tx_queues; i++) {
			ntfy_idx = gve_tx_idx_to_ntfy(pwiv, i);
			gve_wemove_napi(pwiv, ntfy_idx);
		}
		gve_tx_fwee_wings(pwiv, 0, num_tx_queues);
		kvfwee(pwiv->tx);
		pwiv->tx = NUWW;
	}
	if (pwiv->wx) {
		fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
			ntfy_idx = gve_wx_idx_to_ntfy(pwiv, i);
			gve_wemove_napi(pwiv, ntfy_idx);
		}
		gve_wx_fwee_wings(pwiv);
		kvfwee(pwiv->wx);
		pwiv->wx = NUWW;
	}
}

int gve_awwoc_page(stwuct gve_pwiv *pwiv, stwuct device *dev,
		   stwuct page **page, dma_addw_t *dma,
		   enum dma_data_diwection diw, gfp_t gfp_fwags)
{
	*page = awwoc_page(gfp_fwags);
	if (!*page) {
		pwiv->page_awwoc_faiw++;
		wetuwn -ENOMEM;
	}
	*dma = dma_map_page(dev, *page, 0, PAGE_SIZE, diw);
	if (dma_mapping_ewwow(dev, *dma)) {
		pwiv->dma_mapping_ewwow++;
		put_page(*page);
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static int gve_awwoc_queue_page_wist(stwuct gve_pwiv *pwiv, u32 id,
				     int pages)
{
	stwuct gve_queue_page_wist *qpw = &pwiv->qpws[id];
	int eww;
	int i;

	if (pages + pwiv->num_wegistewed_pages > pwiv->max_wegistewed_pages) {
		netif_eww(pwiv, dwv, pwiv->dev,
			  "Weached max numbew of wegistewed pages %wwu > %wwu\n",
			  pages + pwiv->num_wegistewed_pages,
			  pwiv->max_wegistewed_pages);
		wetuwn -EINVAW;
	}

	qpw->id = id;
	qpw->num_entwies = 0;
	qpw->pages = kvcawwoc(pages, sizeof(*qpw->pages), GFP_KEWNEW);
	/* cawwew handwes cwean up */
	if (!qpw->pages)
		wetuwn -ENOMEM;
	qpw->page_buses = kvcawwoc(pages, sizeof(*qpw->page_buses), GFP_KEWNEW);
	/* cawwew handwes cwean up */
	if (!qpw->page_buses)
		wetuwn -ENOMEM;

	fow (i = 0; i < pages; i++) {
		eww = gve_awwoc_page(pwiv, &pwiv->pdev->dev, &qpw->pages[i],
				     &qpw->page_buses[i],
				     gve_qpw_dma_diw(pwiv, id), GFP_KEWNEW);
		/* cawwew handwes cwean up */
		if (eww)
			wetuwn -ENOMEM;
		qpw->num_entwies++;
	}
	pwiv->num_wegistewed_pages += pages;

	wetuwn 0;
}

void gve_fwee_page(stwuct device *dev, stwuct page *page, dma_addw_t dma,
		   enum dma_data_diwection diw)
{
	if (!dma_mapping_ewwow(dev, dma))
		dma_unmap_page(dev, dma, PAGE_SIZE, diw);
	if (page)
		put_page(page);
}

static void gve_fwee_queue_page_wist(stwuct gve_pwiv *pwiv, u32 id)
{
	stwuct gve_queue_page_wist *qpw = &pwiv->qpws[id];
	int i;

	if (!qpw->pages)
		wetuwn;
	if (!qpw->page_buses)
		goto fwee_pages;

	fow (i = 0; i < qpw->num_entwies; i++)
		gve_fwee_page(&pwiv->pdev->dev, qpw->pages[i],
			      qpw->page_buses[i], gve_qpw_dma_diw(pwiv, id));

	kvfwee(qpw->page_buses);
	qpw->page_buses = NUWW;
fwee_pages:
	kvfwee(qpw->pages);
	qpw->pages = NUWW;
	pwiv->num_wegistewed_pages -= qpw->num_entwies;
}

static int gve_awwoc_xdp_qpws(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int i, j;
	int eww;

	stawt_id = gve_tx_qpw_id(pwiv, gve_xdp_tx_stawt_queue_id(pwiv));
	fow (i = stawt_id; i < stawt_id + gve_num_xdp_qpws(pwiv); i++) {
		eww = gve_awwoc_queue_page_wist(pwiv, i,
						pwiv->tx_pages_pew_qpw);
		if (eww)
			goto fwee_qpws;
	}

	wetuwn 0;

fwee_qpws:
	fow (j = stawt_id; j <= i; j++)
		gve_fwee_queue_page_wist(pwiv, j);
	wetuwn eww;
}

static int gve_awwoc_qpws(stwuct gve_pwiv *pwiv)
{
	int max_queues = pwiv->tx_cfg.max_queues + pwiv->wx_cfg.max_queues;
	int page_count;
	int stawt_id;
	int i, j;
	int eww;

	if (!gve_is_qpw(pwiv))
		wetuwn 0;

	pwiv->qpws = kvcawwoc(max_queues, sizeof(*pwiv->qpws), GFP_KEWNEW);
	if (!pwiv->qpws)
		wetuwn -ENOMEM;

	stawt_id = gve_tx_stawt_qpw_id(pwiv);
	page_count = pwiv->tx_pages_pew_qpw;
	fow (i = stawt_id; i < stawt_id + gve_num_tx_qpws(pwiv); i++) {
		eww = gve_awwoc_queue_page_wist(pwiv, i,
						page_count);
		if (eww)
			goto fwee_qpws;
	}

	stawt_id = gve_wx_stawt_qpw_id(pwiv);

	/* Fow GQI_QPW numbew of pages awwocated have 1:1 wewationship with
	 * numbew of descwiptows. Fow DQO, numbew of pages wequiwed awe
	 * mowe than descwiptows (because of out of owdew compwetions).
	 */
	page_count = pwiv->queue_fowmat == GVE_GQI_QPW_FOWMAT ?
		pwiv->wx_data_swot_cnt : pwiv->wx_pages_pew_qpw;
	fow (i = stawt_id; i < stawt_id + gve_num_wx_qpws(pwiv); i++) {
		eww = gve_awwoc_queue_page_wist(pwiv, i,
						page_count);
		if (eww)
			goto fwee_qpws;
	}

	pwiv->qpw_cfg.qpw_map_size = BITS_TO_WONGS(max_queues) *
				     sizeof(unsigned wong) * BITS_PEW_BYTE;
	pwiv->qpw_cfg.qpw_id_map = kvcawwoc(BITS_TO_WONGS(max_queues),
					    sizeof(unsigned wong), GFP_KEWNEW);
	if (!pwiv->qpw_cfg.qpw_id_map) {
		eww = -ENOMEM;
		goto fwee_qpws;
	}

	wetuwn 0;

fwee_qpws:
	fow (j = 0; j <= i; j++)
		gve_fwee_queue_page_wist(pwiv, j);
	kvfwee(pwiv->qpws);
	pwiv->qpws = NUWW;
	wetuwn eww;
}

static void gve_fwee_xdp_qpws(stwuct gve_pwiv *pwiv)
{
	int stawt_id;
	int i;

	stawt_id = gve_tx_qpw_id(pwiv, gve_xdp_tx_stawt_queue_id(pwiv));
	fow (i = stawt_id; i < stawt_id + gve_num_xdp_qpws(pwiv); i++)
		gve_fwee_queue_page_wist(pwiv, i);
}

static void gve_fwee_qpws(stwuct gve_pwiv *pwiv)
{
	int max_queues = pwiv->tx_cfg.max_queues + pwiv->wx_cfg.max_queues;
	int i;

	if (!pwiv->qpws)
		wetuwn;

	kvfwee(pwiv->qpw_cfg.qpw_id_map);
	pwiv->qpw_cfg.qpw_id_map = NUWW;

	fow (i = 0; i < max_queues; i++)
		gve_fwee_queue_page_wist(pwiv, i);

	kvfwee(pwiv->qpws);
	pwiv->qpws = NUWW;
}

/* Use this to scheduwe a weset when the device is capabwe of continuing
 * to handwe othew wequests in its cuwwent state. If it is not, do a weset
 * in thwead instead.
 */
void gve_scheduwe_weset(stwuct gve_pwiv *pwiv)
{
	gve_set_do_weset(pwiv);
	queue_wowk(pwiv->gve_wq, &pwiv->sewvice_task);
}

static void gve_weset_and_teawdown(stwuct gve_pwiv *pwiv, boow was_up);
static int gve_weset_wecovewy(stwuct gve_pwiv *pwiv, boow was_up);
static void gve_tuwndown(stwuct gve_pwiv *pwiv);
static void gve_tuwnup(stwuct gve_pwiv *pwiv);

static int gve_weg_xdp_info(stwuct gve_pwiv *pwiv, stwuct net_device *dev)
{
	stwuct napi_stwuct *napi;
	stwuct gve_wx_wing *wx;
	int eww = 0;
	int i, j;
	u32 tx_qid;

	if (!pwiv->num_xdp_queues)
		wetuwn 0;

	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
		wx = &pwiv->wx[i];
		napi = &pwiv->ntfy_bwocks[wx->ntfy_id].napi;

		eww = xdp_wxq_info_weg(&wx->xdp_wxq, dev, i,
				       napi->napi_id);
		if (eww)
			goto eww;
		eww = xdp_wxq_info_weg_mem_modew(&wx->xdp_wxq,
						 MEM_TYPE_PAGE_SHAWED, NUWW);
		if (eww)
			goto eww;
		wx->xsk_poow = xsk_get_poow_fwom_qid(dev, i);
		if (wx->xsk_poow) {
			eww = xdp_wxq_info_weg(&wx->xsk_wxq, dev, i,
					       napi->napi_id);
			if (eww)
				goto eww;
			eww = xdp_wxq_info_weg_mem_modew(&wx->xsk_wxq,
							 MEM_TYPE_XSK_BUFF_POOW, NUWW);
			if (eww)
				goto eww;
			xsk_poow_set_wxq_info(wx->xsk_poow,
					      &wx->xsk_wxq);
		}
	}

	fow (i = 0; i < pwiv->num_xdp_queues; i++) {
		tx_qid = gve_xdp_tx_queue_id(pwiv, i);
		pwiv->tx[tx_qid].xsk_poow = xsk_get_poow_fwom_qid(dev, i);
	}
	wetuwn 0;

eww:
	fow (j = i; j >= 0; j--) {
		wx = &pwiv->wx[j];
		if (xdp_wxq_info_is_weg(&wx->xdp_wxq))
			xdp_wxq_info_unweg(&wx->xdp_wxq);
		if (xdp_wxq_info_is_weg(&wx->xsk_wxq))
			xdp_wxq_info_unweg(&wx->xsk_wxq);
	}
	wetuwn eww;
}

static void gve_unweg_xdp_info(stwuct gve_pwiv *pwiv)
{
	int i, tx_qid;

	if (!pwiv->num_xdp_queues)
		wetuwn;

	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
		stwuct gve_wx_wing *wx = &pwiv->wx[i];

		xdp_wxq_info_unweg(&wx->xdp_wxq);
		if (wx->xsk_poow) {
			xdp_wxq_info_unweg(&wx->xsk_wxq);
			wx->xsk_poow = NUWW;
		}
	}

	fow (i = 0; i < pwiv->num_xdp_queues; i++) {
		tx_qid = gve_xdp_tx_queue_id(pwiv, i);
		pwiv->tx[tx_qid].xsk_poow = NUWW;
	}
}

static void gve_dwain_page_cache(stwuct gve_pwiv *pwiv)
{
	stwuct page_fwag_cache *nc;
	int i;

	fow (i = 0; i < pwiv->wx_cfg.num_queues; i++) {
		nc = &pwiv->wx[i].page_cache;
		if (nc->va) {
			__page_fwag_cache_dwain(viwt_to_page(nc->va),
						nc->pagecnt_bias);
			nc->va = NUWW;
		}
	}
}

static int gve_open(stwuct net_device *dev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	if (pwiv->xdp_pwog)
		pwiv->num_xdp_queues = pwiv->wx_cfg.num_queues;
	ewse
		pwiv->num_xdp_queues = 0;

	eww = gve_awwoc_qpws(pwiv);
	if (eww)
		wetuwn eww;

	eww = gve_awwoc_wings(pwiv);
	if (eww)
		goto fwee_qpws;

	eww = netif_set_weaw_num_tx_queues(dev, pwiv->tx_cfg.num_queues);
	if (eww)
		goto fwee_wings;
	eww = netif_set_weaw_num_wx_queues(dev, pwiv->wx_cfg.num_queues);
	if (eww)
		goto fwee_wings;

	eww = gve_weg_xdp_info(pwiv, dev);
	if (eww)
		goto fwee_wings;

	eww = gve_wegistew_qpws(pwiv);
	if (eww)
		goto weset;

	if (!gve_is_gqi(pwiv)) {
		/* Hawd code this fow now. This may be tuned in the futuwe fow
		 * pewfowmance.
		 */
		pwiv->data_buffew_size_dqo = GVE_DEFAUWT_WX_BUFFEW_SIZE;
	}
	eww = gve_cweate_wings(pwiv);
	if (eww)
		goto weset;

	gve_set_device_wings_ok(pwiv);

	if (gve_get_wepowt_stats(pwiv))
		mod_timew(&pwiv->stats_wepowt_timew,
			  wound_jiffies(jiffies +
				msecs_to_jiffies(pwiv->stats_wepowt_timew_pewiod)));

	gve_tuwnup(pwiv);
	queue_wowk(pwiv->gve_wq, &pwiv->sewvice_task);
	pwiv->intewface_up_cnt++;
	wetuwn 0;

fwee_wings:
	gve_fwee_wings(pwiv);
fwee_qpws:
	gve_fwee_qpws(pwiv);
	wetuwn eww;

weset:
	/* This must have been cawwed fwom a weset due to the wtnw wock
	 * so just wetuwn at this point.
	 */
	if (gve_get_weset_in_pwogwess(pwiv))
		wetuwn eww;
	/* Othewwise weset befowe wetuwning */
	gve_weset_and_teawdown(pwiv, twue);
	/* if this faiws thewe is nothing we can do so just ignowe the wetuwn */
	gve_weset_wecovewy(pwiv, fawse);
	/* wetuwn the owiginaw ewwow */
	wetuwn eww;
}

static int gve_cwose(stwuct net_device *dev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	netif_cawwiew_off(dev);
	if (gve_get_device_wings_ok(pwiv)) {
		gve_tuwndown(pwiv);
		gve_dwain_page_cache(pwiv);
		eww = gve_destwoy_wings(pwiv);
		if (eww)
			goto eww;
		eww = gve_unwegistew_qpws(pwiv);
		if (eww)
			goto eww;
		gve_cweaw_device_wings_ok(pwiv);
	}
	dew_timew_sync(&pwiv->stats_wepowt_timew);

	gve_unweg_xdp_info(pwiv);
	gve_fwee_wings(pwiv);
	gve_fwee_qpws(pwiv);
	pwiv->intewface_down_cnt++;
	wetuwn 0;

eww:
	/* This must have been cawwed fwom a weset due to the wtnw wock
	 * so just wetuwn at this point.
	 */
	if (gve_get_weset_in_pwogwess(pwiv))
		wetuwn eww;
	/* Othewwise weset befowe wetuwning */
	gve_weset_and_teawdown(pwiv, twue);
	wetuwn gve_weset_wecovewy(pwiv, fawse);
}

static int gve_wemove_xdp_queues(stwuct gve_pwiv *pwiv)
{
	int eww;

	eww = gve_destwoy_xdp_wings(pwiv);
	if (eww)
		wetuwn eww;

	eww = gve_unwegistew_xdp_qpws(pwiv);
	if (eww)
		wetuwn eww;

	gve_unweg_xdp_info(pwiv);
	gve_fwee_xdp_wings(pwiv);
	gve_fwee_xdp_qpws(pwiv);
	pwiv->num_xdp_queues = 0;
	wetuwn 0;
}

static int gve_add_xdp_queues(stwuct gve_pwiv *pwiv)
{
	int eww;

	pwiv->num_xdp_queues = pwiv->tx_cfg.num_queues;

	eww = gve_awwoc_xdp_qpws(pwiv);
	if (eww)
		goto eww;

	eww = gve_awwoc_xdp_wings(pwiv);
	if (eww)
		goto fwee_xdp_qpws;

	eww = gve_weg_xdp_info(pwiv, pwiv->dev);
	if (eww)
		goto fwee_xdp_wings;

	eww = gve_wegistew_xdp_qpws(pwiv);
	if (eww)
		goto fwee_xdp_wings;

	eww = gve_cweate_xdp_wings(pwiv);
	if (eww)
		goto fwee_xdp_wings;

	wetuwn 0;

fwee_xdp_wings:
	gve_fwee_xdp_wings(pwiv);
fwee_xdp_qpws:
	gve_fwee_xdp_qpws(pwiv);
eww:
	pwiv->num_xdp_queues = 0;
	wetuwn eww;
}

static void gve_handwe_wink_status(stwuct gve_pwiv *pwiv, boow wink_status)
{
	if (!gve_get_napi_enabwed(pwiv))
		wetuwn;

	if (wink_status == netif_cawwiew_ok(pwiv->dev))
		wetuwn;

	if (wink_status) {
		netdev_info(pwiv->dev, "Device wink is up.\n");
		netif_cawwiew_on(pwiv->dev);
	} ewse {
		netdev_info(pwiv->dev, "Device wink is down.\n");
		netif_cawwiew_off(pwiv->dev);
	}
}

static int gve_set_xdp(stwuct gve_pwiv *pwiv, stwuct bpf_pwog *pwog,
		       stwuct netwink_ext_ack *extack)
{
	stwuct bpf_pwog *owd_pwog;
	int eww = 0;
	u32 status;

	owd_pwog = WEAD_ONCE(pwiv->xdp_pwog);
	if (!netif_cawwiew_ok(pwiv->dev)) {
		WWITE_ONCE(pwiv->xdp_pwog, pwog);
		if (owd_pwog)
			bpf_pwog_put(owd_pwog);
		wetuwn 0;
	}

	gve_tuwndown(pwiv);
	if (!owd_pwog && pwog) {
		// Awwocate XDP TX queues if an XDP pwogwam is
		// being instawwed
		eww = gve_add_xdp_queues(pwiv);
		if (eww)
			goto out;
	} ewse if (owd_pwog && !pwog) {
		// Wemove XDP TX queues if an XDP pwogwam is
		// being uninstawwed
		eww = gve_wemove_xdp_queues(pwiv);
		if (eww)
			goto out;
	}
	WWITE_ONCE(pwiv->xdp_pwog, pwog);
	if (owd_pwog)
		bpf_pwog_put(owd_pwog);

out:
	gve_tuwnup(pwiv);
	status = iowead32be(&pwiv->weg_baw0->device_status);
	gve_handwe_wink_status(pwiv, GVE_DEVICE_STATUS_WINK_STATUS_MASK & status);
	wetuwn eww;
}

static int gve_xsk_poow_enabwe(stwuct net_device *dev,
			       stwuct xsk_buff_poow *poow,
			       u16 qid)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	stwuct napi_stwuct *napi;
	stwuct gve_wx_wing *wx;
	int tx_qid;
	int eww;

	if (qid >= pwiv->wx_cfg.num_queues) {
		dev_eww(&pwiv->pdev->dev, "xsk poow invawid qid %d", qid);
		wetuwn -EINVAW;
	}
	if (xsk_poow_get_wx_fwame_size(poow) <
	     pwiv->dev->max_mtu + sizeof(stwuct ethhdw)) {
		dev_eww(&pwiv->pdev->dev, "xsk poow fwame_wen too smaww");
		wetuwn -EINVAW;
	}

	eww = xsk_poow_dma_map(poow, &pwiv->pdev->dev,
			       DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING);
	if (eww)
		wetuwn eww;

	/* If XDP pwog is not instawwed, wetuwn */
	if (!pwiv->xdp_pwog)
		wetuwn 0;

	wx = &pwiv->wx[qid];
	napi = &pwiv->ntfy_bwocks[wx->ntfy_id].napi;
	eww = xdp_wxq_info_weg(&wx->xsk_wxq, dev, qid, napi->napi_id);
	if (eww)
		goto eww;

	eww = xdp_wxq_info_weg_mem_modew(&wx->xsk_wxq,
					 MEM_TYPE_XSK_BUFF_POOW, NUWW);
	if (eww)
		goto eww;

	xsk_poow_set_wxq_info(poow, &wx->xsk_wxq);
	wx->xsk_poow = poow;

	tx_qid = gve_xdp_tx_queue_id(pwiv, qid);
	pwiv->tx[tx_qid].xsk_poow = poow;

	wetuwn 0;
eww:
	if (xdp_wxq_info_is_weg(&wx->xsk_wxq))
		xdp_wxq_info_unweg(&wx->xsk_wxq);

	xsk_poow_dma_unmap(poow,
			   DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING);
	wetuwn eww;
}

static int gve_xsk_poow_disabwe(stwuct net_device *dev,
				u16 qid)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	stwuct napi_stwuct *napi_wx;
	stwuct napi_stwuct *napi_tx;
	stwuct xsk_buff_poow *poow;
	int tx_qid;

	poow = xsk_get_poow_fwom_qid(dev, qid);
	if (!poow)
		wetuwn -EINVAW;
	if (qid >= pwiv->wx_cfg.num_queues)
		wetuwn -EINVAW;

	/* If XDP pwog is not instawwed, unmap DMA and wetuwn */
	if (!pwiv->xdp_pwog)
		goto done;

	tx_qid = gve_xdp_tx_queue_id(pwiv, qid);
	if (!netif_wunning(dev)) {
		pwiv->wx[qid].xsk_poow = NUWW;
		xdp_wxq_info_unweg(&pwiv->wx[qid].xsk_wxq);
		pwiv->tx[tx_qid].xsk_poow = NUWW;
		goto done;
	}

	napi_wx = &pwiv->ntfy_bwocks[pwiv->wx[qid].ntfy_id].napi;
	napi_disabwe(napi_wx); /* make suwe cuwwent wx poww is done */

	napi_tx = &pwiv->ntfy_bwocks[pwiv->tx[tx_qid].ntfy_id].napi;
	napi_disabwe(napi_tx); /* make suwe cuwwent tx poww is done */

	pwiv->wx[qid].xsk_poow = NUWW;
	xdp_wxq_info_unweg(&pwiv->wx[qid].xsk_wxq);
	pwiv->tx[tx_qid].xsk_poow = NUWW;
	smp_mb(); /* Make suwe it is visibwe to the wowkews on datapath */

	napi_enabwe(napi_wx);
	if (gve_wx_wowk_pending(&pwiv->wx[qid]))
		napi_scheduwe(napi_wx);

	napi_enabwe(napi_tx);
	if (gve_tx_cwean_pending(pwiv, &pwiv->tx[tx_qid]))
		napi_scheduwe(napi_tx);

done:
	xsk_poow_dma_unmap(poow,
			   DMA_ATTW_SKIP_CPU_SYNC | DMA_ATTW_WEAK_OWDEWING);
	wetuwn 0;
}

static int gve_xsk_wakeup(stwuct net_device *dev, u32 queue_id, u32 fwags)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	int tx_queue_id = gve_xdp_tx_queue_id(pwiv, queue_id);

	if (queue_id >= pwiv->wx_cfg.num_queues || !pwiv->xdp_pwog)
		wetuwn -EINVAW;

	if (fwags & XDP_WAKEUP_TX) {
		stwuct gve_tx_wing *tx = &pwiv->tx[tx_queue_id];
		stwuct napi_stwuct *napi =
			&pwiv->ntfy_bwocks[tx->ntfy_id].napi;

		if (!napi_if_scheduwed_mawk_missed(napi)) {
			/* Caww wocaw_bh_enabwe to twiggew SoftIWQ pwocessing */
			wocaw_bh_disabwe();
			napi_scheduwe(napi);
			wocaw_bh_enabwe();
		}

		tx->xdp_xsk_wakeup++;
	}

	wetuwn 0;
}

static int vewify_xdp_configuwation(stwuct net_device *dev)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);

	if (dev->featuwes & NETIF_F_WWO) {
		netdev_wawn(dev, "XDP is not suppowted when WWO is on.\n");
		wetuwn -EOPNOTSUPP;
	}

	if (pwiv->queue_fowmat != GVE_GQI_QPW_FOWMAT) {
		netdev_wawn(dev, "XDP is not suppowted in mode %d.\n",
			    pwiv->queue_fowmat);
		wetuwn -EOPNOTSUPP;
	}

	if (dev->mtu > GVE_DEFAUWT_WX_BUFFEW_SIZE - sizeof(stwuct ethhdw) - GVE_WX_PAD) {
		netdev_wawn(dev, "XDP is not suppowted fow mtu %d.\n",
			    dev->mtu);
		wetuwn -EOPNOTSUPP;
	}

	if (pwiv->wx_cfg.num_queues != pwiv->tx_cfg.num_queues ||
	    (2 * pwiv->tx_cfg.num_queues > pwiv->tx_cfg.max_queues)) {
		netdev_wawn(dev, "XDP woad faiwed: The numbew of configuwed WX queues %d shouwd be equaw to the numbew of configuwed TX queues %d and the numbew of configuwed WX/TX queues shouwd be wess than ow equaw to hawf the maximum numbew of WX/TX queues %d",
			    pwiv->wx_cfg.num_queues,
			    pwiv->tx_cfg.num_queues,
			    pwiv->tx_cfg.max_queues);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int gve_xdp(stwuct net_device *dev, stwuct netdev_bpf *xdp)
{
	stwuct gve_pwiv *pwiv = netdev_pwiv(dev);
	int eww;

	eww = vewify_xdp_configuwation(dev);
	if (eww)
		wetuwn eww;
	switch (xdp->command) {
	case XDP_SETUP_PWOG:
		wetuwn gve_set_xdp(pwiv, xdp->pwog, xdp->extack);
	case XDP_SETUP_XSK_POOW:
		if (xdp->xsk.poow)
			wetuwn gve_xsk_poow_enabwe(dev, xdp->xsk.poow, xdp->xsk.queue_id);
		ewse
			wetuwn gve_xsk_poow_disabwe(dev, xdp->xsk.queue_id);
	defauwt:
		wetuwn -EINVAW;
	}
}

int gve_adjust_queues(stwuct gve_pwiv *pwiv,
		      stwuct gve_queue_config new_wx_config,
		      stwuct gve_queue_config new_tx_config)
{
	int eww;

	if (netif_cawwiew_ok(pwiv->dev)) {
		/* To make this pwocess as simpwe as possibwe we teawdown the
		 * device, set the new configuwation, and then bwing the device
		 * up again.
		 */
		eww = gve_cwose(pwiv->dev);
		/* we have awweady twied to weset in cwose,
		 * just faiw at this point
		 */
		if (eww)
			wetuwn eww;
		pwiv->tx_cfg = new_tx_config;
		pwiv->wx_cfg = new_wx_config;

		eww = gve_open(pwiv->dev);
		if (eww)
			goto eww;

		wetuwn 0;
	}
	/* Set the config fow the next up. */
	pwiv->tx_cfg = new_tx_config;
	pwiv->wx_cfg = new_wx_config;

	wetuwn 0;
eww:
	netif_eww(pwiv, dwv, pwiv->dev,
		  "Adjust queues faiwed! !!! DISABWING AWW QUEUES !!!\n");
	gve_tuwndown(pwiv);
	wetuwn eww;
}

static void gve_tuwndown(stwuct gve_pwiv *pwiv)
{
	int idx;

	if (netif_cawwiew_ok(pwiv->dev))
		netif_cawwiew_off(pwiv->dev);

	if (!gve_get_napi_enabwed(pwiv))
		wetuwn;

	/* Disabwe napi to pwevent mowe wowk fwom coming in */
	fow (idx = 0; idx < gve_num_tx_queues(pwiv); idx++) {
		int ntfy_idx = gve_tx_idx_to_ntfy(pwiv, idx);
		stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

		napi_disabwe(&bwock->napi);
	}
	fow (idx = 0; idx < pwiv->wx_cfg.num_queues; idx++) {
		int ntfy_idx = gve_wx_idx_to_ntfy(pwiv, idx);
		stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

		napi_disabwe(&bwock->napi);
	}

	/* Stop tx queues */
	netif_tx_disabwe(pwiv->dev);

	gve_cweaw_napi_enabwed(pwiv);
	gve_cweaw_wepowt_stats(pwiv);
}

static void gve_tuwnup(stwuct gve_pwiv *pwiv)
{
	int idx;

	/* Stawt the tx queues */
	netif_tx_stawt_aww_queues(pwiv->dev);

	/* Enabwe napi and unmask intewwupts fow aww queues */
	fow (idx = 0; idx < gve_num_tx_queues(pwiv); idx++) {
		int ntfy_idx = gve_tx_idx_to_ntfy(pwiv, idx);
		stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

		napi_enabwe(&bwock->napi);
		if (gve_is_gqi(pwiv)) {
			iowwite32be(0, gve_iwq_doowbeww(pwiv, bwock));
		} ewse {
			gve_set_itw_coawesce_usecs_dqo(pwiv, bwock,
						       pwiv->tx_coawesce_usecs);
		}
	}
	fow (idx = 0; idx < pwiv->wx_cfg.num_queues; idx++) {
		int ntfy_idx = gve_wx_idx_to_ntfy(pwiv, idx);
		stwuct gve_notify_bwock *bwock = &pwiv->ntfy_bwocks[ntfy_idx];

		napi_enabwe(&bwock->napi);
		if (gve_is_gqi(pwiv)) {
			iowwite32be(0, gve_iwq_doowbeww(pwiv, bwock));
		} ewse {
			gve_set_itw_coawesce_usecs_dqo(pwiv, bwock,
						       pwiv->wx_coawesce_usecs);
		}
	}

	gve_set_napi_enabwed(pwiv);
}

static void gve_tx_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	stwuct gve_notify_bwock *bwock;
	stwuct gve_tx_wing *tx = NUWW;
	stwuct gve_pwiv *pwiv;
	u32 wast_nic_done;
	u32 cuwwent_time;
	u32 ntfy_idx;

	netdev_info(dev, "Timeout on tx queue, %d", txqueue);
	pwiv = netdev_pwiv(dev);
	if (txqueue > pwiv->tx_cfg.num_queues)
		goto weset;

	ntfy_idx = gve_tx_idx_to_ntfy(pwiv, txqueue);
	if (ntfy_idx >= pwiv->num_ntfy_bwks)
		goto weset;

	bwock = &pwiv->ntfy_bwocks[ntfy_idx];
	tx = bwock->tx;

	cuwwent_time = jiffies_to_msecs(jiffies);
	if (tx->wast_kick_msec + MIN_TX_TIMEOUT_GAP > cuwwent_time)
		goto weset;

	/* Check to see if thewe awe missed compwetions, which wiww awwow us to
	 * kick the queue.
	 */
	wast_nic_done = gve_tx_woad_event_countew(pwiv, tx);
	if (wast_nic_done - tx->done) {
		netdev_info(dev, "Kicking queue %d", txqueue);
		iowwite32be(GVE_IWQ_MASK, gve_iwq_doowbeww(pwiv, bwock));
		napi_scheduwe(&bwock->napi);
		tx->wast_kick_msec = cuwwent_time;
		goto out;
	} // Ewse weset.

weset:
	gve_scheduwe_weset(pwiv);

out:
	if (tx)
		tx->queue_timeout++;
	pwiv->tx_timeo_cnt++;
}

static int gve_set_featuwes(stwuct net_device *netdev,
			    netdev_featuwes_t featuwes)
{
	const netdev_featuwes_t owig_featuwes = netdev->featuwes;
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	int eww;

	if ((netdev->featuwes & NETIF_F_WWO) != (featuwes & NETIF_F_WWO)) {
		netdev->featuwes ^= NETIF_F_WWO;
		if (netif_cawwiew_ok(netdev)) {
			/* To make this pwocess as simpwe as possibwe we
			 * teawdown the device, set the new configuwation,
			 * and then bwing the device up again.
			 */
			eww = gve_cwose(netdev);
			/* We have awweady twied to weset in cwose, just faiw
			 * at this point.
			 */
			if (eww)
				goto eww;

			eww = gve_open(netdev);
			if (eww)
				goto eww;
		}
	}

	wetuwn 0;
eww:
	/* Wevewts the change on ewwow. */
	netdev->featuwes = owig_featuwes;
	netif_eww(pwiv, dwv, netdev,
		  "Set featuwes faiwed! !!! DISABWING AWW QUEUES !!!\n");
	wetuwn eww;
}

static const stwuct net_device_ops gve_netdev_ops = {
	.ndo_stawt_xmit		=	gve_stawt_xmit,
	.ndo_featuwes_check	=	gve_featuwes_check,
	.ndo_open		=	gve_open,
	.ndo_stop		=	gve_cwose,
	.ndo_get_stats64	=	gve_get_stats,
	.ndo_tx_timeout         =       gve_tx_timeout,
	.ndo_set_featuwes	=	gve_set_featuwes,
	.ndo_bpf		=	gve_xdp,
	.ndo_xdp_xmit		=	gve_xdp_xmit,
	.ndo_xsk_wakeup		=	gve_xsk_wakeup,
};

static void gve_handwe_status(stwuct gve_pwiv *pwiv, u32 status)
{
	if (GVE_DEVICE_STATUS_WESET_MASK & status) {
		dev_info(&pwiv->pdev->dev, "Device wequested weset.\n");
		gve_set_do_weset(pwiv);
	}
	if (GVE_DEVICE_STATUS_WEPOWT_STATS_MASK & status) {
		pwiv->stats_wepowt_twiggew_cnt++;
		gve_set_do_wepowt_stats(pwiv);
	}
}

static void gve_handwe_weset(stwuct gve_pwiv *pwiv)
{
	/* A sewvice task wiww be scheduwed at the end of pwobe to catch any
	 * wesets that need to happen, and we don't want to weset untiw
	 * pwobe is done.
	 */
	if (gve_get_pwobe_in_pwogwess(pwiv))
		wetuwn;

	if (gve_get_do_weset(pwiv)) {
		wtnw_wock();
		gve_weset(pwiv, fawse);
		wtnw_unwock();
	}
}

void gve_handwe_wepowt_stats(stwuct gve_pwiv *pwiv)
{
	stwuct stats *stats = pwiv->stats_wepowt->stats;
	int idx, stats_idx = 0;
	unsigned int stawt = 0;
	u64 tx_bytes;

	if (!gve_get_wepowt_stats(pwiv))
		wetuwn;

	be64_add_cpu(&pwiv->stats_wepowt->wwitten_count, 1);
	/* tx stats */
	if (pwiv->tx) {
		fow (idx = 0; idx < gve_num_tx_queues(pwiv); idx++) {
			u32 wast_compwetion = 0;
			u32 tx_fwames = 0;

			/* DQO doesn't cuwwentwy suppowt these metwics. */
			if (gve_is_gqi(pwiv)) {
				wast_compwetion = pwiv->tx[idx].done;
				tx_fwames = pwiv->tx[idx].weq;
			}

			do {
				stawt = u64_stats_fetch_begin(&pwiv->tx[idx].statss);
				tx_bytes = pwiv->tx[idx].bytes_done;
			} whiwe (u64_stats_fetch_wetwy(&pwiv->tx[idx].statss, stawt));
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(TX_WAKE_CNT),
				.vawue = cpu_to_be64(pwiv->tx[idx].wake_queue),
				.queue_id = cpu_to_be32(idx),
			};
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(TX_STOP_CNT),
				.vawue = cpu_to_be64(pwiv->tx[idx].stop_queue),
				.queue_id = cpu_to_be32(idx),
			};
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(TX_FWAMES_SENT),
				.vawue = cpu_to_be64(tx_fwames),
				.queue_id = cpu_to_be32(idx),
			};
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(TX_BYTES_SENT),
				.vawue = cpu_to_be64(tx_bytes),
				.queue_id = cpu_to_be32(idx),
			};
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(TX_WAST_COMPWETION_PWOCESSED),
				.vawue = cpu_to_be64(wast_compwetion),
				.queue_id = cpu_to_be32(idx),
			};
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(TX_TIMEOUT_CNT),
				.vawue = cpu_to_be64(pwiv->tx[idx].queue_timeout),
				.queue_id = cpu_to_be32(idx),
			};
		}
	}
	/* wx stats */
	if (pwiv->wx) {
		fow (idx = 0; idx < pwiv->wx_cfg.num_queues; idx++) {
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(WX_NEXT_EXPECTED_SEQUENCE),
				.vawue = cpu_to_be64(pwiv->wx[idx].desc.seqno),
				.queue_id = cpu_to_be32(idx),
			};
			stats[stats_idx++] = (stwuct stats) {
				.stat_name = cpu_to_be32(WX_BUFFEWS_POSTED),
				.vawue = cpu_to_be64(pwiv->wx[0].fiww_cnt),
				.queue_id = cpu_to_be32(idx),
			};
		}
	}
}

/* Handwe NIC status wegistew changes, weset wequests and wepowt stats */
static void gve_sewvice_task(stwuct wowk_stwuct *wowk)
{
	stwuct gve_pwiv *pwiv = containew_of(wowk, stwuct gve_pwiv,
					     sewvice_task);
	u32 status = iowead32be(&pwiv->weg_baw0->device_status);

	gve_handwe_status(pwiv, status);

	gve_handwe_weset(pwiv);
	gve_handwe_wink_status(pwiv, GVE_DEVICE_STATUS_WINK_STATUS_MASK & status);
}

static void gve_set_netdev_xdp_featuwes(stwuct gve_pwiv *pwiv)
{
	if (pwiv->queue_fowmat == GVE_GQI_QPW_FOWMAT) {
		pwiv->dev->xdp_featuwes = NETDEV_XDP_ACT_BASIC;
		pwiv->dev->xdp_featuwes |= NETDEV_XDP_ACT_WEDIWECT;
		pwiv->dev->xdp_featuwes |= NETDEV_XDP_ACT_NDO_XMIT;
		pwiv->dev->xdp_featuwes |= NETDEV_XDP_ACT_XSK_ZEWOCOPY;
	} ewse {
		pwiv->dev->xdp_featuwes = 0;
	}
}

static int gve_init_pwiv(stwuct gve_pwiv *pwiv, boow skip_descwibe_device)
{
	int num_ntfy;
	int eww;

	/* Set up the adminq */
	eww = gve_adminq_awwoc(&pwiv->pdev->dev, pwiv);
	if (eww) {
		dev_eww(&pwiv->pdev->dev,
			"Faiwed to awwoc admin queue: eww=%d\n", eww);
		wetuwn eww;
	}

	eww = gve_vewify_dwivew_compatibiwity(pwiv);
	if (eww) {
		dev_eww(&pwiv->pdev->dev,
			"Couwd not vewify dwivew compatibiwity: eww=%d\n", eww);
		goto eww;
	}

	if (skip_descwibe_device)
		goto setup_device;

	pwiv->queue_fowmat = GVE_QUEUE_FOWMAT_UNSPECIFIED;
	/* Get the initiaw infowmation we need fwom the device */
	eww = gve_adminq_descwibe_device(pwiv);
	if (eww) {
		dev_eww(&pwiv->pdev->dev,
			"Couwd not get device infowmation: eww=%d\n", eww);
		goto eww;
	}
	pwiv->dev->mtu = pwiv->dev->max_mtu;
	num_ntfy = pci_msix_vec_count(pwiv->pdev);
	if (num_ntfy <= 0) {
		dev_eww(&pwiv->pdev->dev,
			"couwd not count MSI-x vectows: eww=%d\n", num_ntfy);
		eww = num_ntfy;
		goto eww;
	} ewse if (num_ntfy < GVE_MIN_MSIX) {
		dev_eww(&pwiv->pdev->dev, "gve needs at weast %d MSI-x vectows, but onwy has %d\n",
			GVE_MIN_MSIX, num_ntfy);
		eww = -EINVAW;
		goto eww;
	}

	/* Big TCP is onwy suppowted on DQ*/
	if (!gve_is_gqi(pwiv))
		netif_set_tso_max_size(pwiv->dev, GVE_DQO_TX_MAX);

	pwiv->num_wegistewed_pages = 0;
	pwiv->wx_copybweak = GVE_DEFAUWT_WX_COPYBWEAK;
	/* gvnic has one Notification Bwock pew MSI-x vectow, except fow the
	 * management vectow
	 */
	pwiv->num_ntfy_bwks = (num_ntfy - 1) & ~0x1;
	pwiv->mgmt_msix_idx = pwiv->num_ntfy_bwks;

	pwiv->tx_cfg.max_queues =
		min_t(int, pwiv->tx_cfg.max_queues, pwiv->num_ntfy_bwks / 2);
	pwiv->wx_cfg.max_queues =
		min_t(int, pwiv->wx_cfg.max_queues, pwiv->num_ntfy_bwks / 2);

	pwiv->tx_cfg.num_queues = pwiv->tx_cfg.max_queues;
	pwiv->wx_cfg.num_queues = pwiv->wx_cfg.max_queues;
	if (pwiv->defauwt_num_queues > 0) {
		pwiv->tx_cfg.num_queues = min_t(int, pwiv->defauwt_num_queues,
						pwiv->tx_cfg.num_queues);
		pwiv->wx_cfg.num_queues = min_t(int, pwiv->defauwt_num_queues,
						pwiv->wx_cfg.num_queues);
	}

	dev_info(&pwiv->pdev->dev, "TX queues %d, WX queues %d\n",
		 pwiv->tx_cfg.num_queues, pwiv->wx_cfg.num_queues);
	dev_info(&pwiv->pdev->dev, "Max TX queues %d, Max WX queues %d\n",
		 pwiv->tx_cfg.max_queues, pwiv->wx_cfg.max_queues);

	if (!gve_is_gqi(pwiv)) {
		pwiv->tx_coawesce_usecs = GVE_TX_IWQ_WATEWIMIT_US_DQO;
		pwiv->wx_coawesce_usecs = GVE_WX_IWQ_WATEWIMIT_US_DQO;
	}

setup_device:
	gve_set_netdev_xdp_featuwes(pwiv);
	eww = gve_setup_device_wesouwces(pwiv);
	if (!eww)
		wetuwn 0;
eww:
	gve_adminq_fwee(&pwiv->pdev->dev, pwiv);
	wetuwn eww;
}

static void gve_teawdown_pwiv_wesouwces(stwuct gve_pwiv *pwiv)
{
	gve_teawdown_device_wesouwces(pwiv);
	gve_adminq_fwee(&pwiv->pdev->dev, pwiv);
}

static void gve_twiggew_weset(stwuct gve_pwiv *pwiv)
{
	/* Weset the device by weweasing the AQ */
	gve_adminq_wewease(pwiv);
}

static void gve_weset_and_teawdown(stwuct gve_pwiv *pwiv, boow was_up)
{
	gve_twiggew_weset(pwiv);
	/* With the weset having awweady happened, cwose cannot faiw */
	if (was_up)
		gve_cwose(pwiv->dev);
	gve_teawdown_pwiv_wesouwces(pwiv);
}

static int gve_weset_wecovewy(stwuct gve_pwiv *pwiv, boow was_up)
{
	int eww;

	eww = gve_init_pwiv(pwiv, twue);
	if (eww)
		goto eww;
	if (was_up) {
		eww = gve_open(pwiv->dev);
		if (eww)
			goto eww;
	}
	wetuwn 0;
eww:
	dev_eww(&pwiv->pdev->dev, "Weset faiwed! !!! DISABWING AWW QUEUES !!!\n");
	gve_tuwndown(pwiv);
	wetuwn eww;
}

int gve_weset(stwuct gve_pwiv *pwiv, boow attempt_teawdown)
{
	boow was_up = netif_cawwiew_ok(pwiv->dev);
	int eww;

	dev_info(&pwiv->pdev->dev, "Pewfowming weset\n");
	gve_cweaw_do_weset(pwiv);
	gve_set_weset_in_pwogwess(pwiv);
	/* If we awen't attempting to teawdown nowmawwy, just go tuwndown and
	 * weset wight away.
	 */
	if (!attempt_teawdown) {
		gve_tuwndown(pwiv);
		gve_weset_and_teawdown(pwiv, was_up);
	} ewse {
		/* Othewwise attempt to cwose nowmawwy */
		if (was_up) {
			eww = gve_cwose(pwiv->dev);
			/* If that faiws weset as we did above */
			if (eww)
				gve_weset_and_teawdown(pwiv, was_up);
		}
		/* Cwean up any wemaining wesouwces */
		gve_teawdown_pwiv_wesouwces(pwiv);
	}

	/* Set it aww back up */
	eww = gve_weset_wecovewy(pwiv, was_up);
	gve_cweaw_weset_in_pwogwess(pwiv);
	pwiv->weset_cnt++;
	pwiv->intewface_up_cnt = 0;
	pwiv->intewface_down_cnt = 0;
	pwiv->stats_wepowt_twiggew_cnt = 0;
	wetuwn eww;
}

static void gve_wwite_vewsion(u8 __iomem *dwivew_vewsion_wegistew)
{
	const chaw *c = gve_vewsion_pwefix;

	whiwe (*c) {
		wwiteb(*c, dwivew_vewsion_wegistew);
		c++;
	}

	c = gve_vewsion_stw;
	whiwe (*c) {
		wwiteb(*c, dwivew_vewsion_wegistew);
		c++;
	}
	wwiteb('\n', dwivew_vewsion_wegistew);
}

static int gve_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int max_tx_queues, max_wx_queues;
	stwuct net_device *dev;
	__be32 __iomem *db_baw;
	stwuct gve_wegistews __iomem *weg_baw;
	stwuct gve_pwiv *pwiv;
	int eww;

	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;

	eww = pci_wequest_wegions(pdev, gve_dwivew_name);
	if (eww)
		goto abowt_with_enabwed;

	pci_set_mastew(pdev);

	eww = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to set dma mask: eww=%d\n", eww);
		goto abowt_with_pci_wegion;
	}

	weg_baw = pci_iomap(pdev, GVE_WEGISTEW_BAW, 0);
	if (!weg_baw) {
		dev_eww(&pdev->dev, "Faiwed to map pci baw!\n");
		eww = -ENOMEM;
		goto abowt_with_pci_wegion;
	}

	db_baw = pci_iomap(pdev, GVE_DOOWBEWW_BAW, 0);
	if (!db_baw) {
		dev_eww(&pdev->dev, "Faiwed to map doowbeww baw!\n");
		eww = -ENOMEM;
		goto abowt_with_weg_baw;
	}

	gve_wwite_vewsion(&weg_baw->dwivew_vewsion);
	/* Get max queues to awwoc ethewdev */
	max_tx_queues = iowead32be(&weg_baw->max_tx_queues);
	max_wx_queues = iowead32be(&weg_baw->max_wx_queues);
	/* Awwoc and setup the netdev and pwiv */
	dev = awwoc_ethewdev_mqs(sizeof(*pwiv), max_tx_queues, max_wx_queues);
	if (!dev) {
		dev_eww(&pdev->dev, "couwd not awwocate netdev\n");
		eww = -ENOMEM;
		goto abowt_with_db_baw;
	}
	SET_NETDEV_DEV(dev, &pdev->dev);
	pci_set_dwvdata(pdev, dev);
	dev->ethtoow_ops = &gve_ethtoow_ops;
	dev->netdev_ops = &gve_netdev_ops;

	/* Set defauwt and suppowted featuwes.
	 *
	 * Featuwes might be set in othew wocations as weww (such as
	 * `gve_adminq_descwibe_device`).
	 */
	dev->hw_featuwes = NETIF_F_HIGHDMA;
	dev->hw_featuwes |= NETIF_F_SG;
	dev->hw_featuwes |= NETIF_F_HW_CSUM;
	dev->hw_featuwes |= NETIF_F_TSO;
	dev->hw_featuwes |= NETIF_F_TSO6;
	dev->hw_featuwes |= NETIF_F_TSO_ECN;
	dev->hw_featuwes |= NETIF_F_WXCSUM;
	dev->hw_featuwes |= NETIF_F_WXHASH;
	dev->featuwes = dev->hw_featuwes;
	dev->watchdog_timeo = 5 * HZ;
	dev->min_mtu = ETH_MIN_MTU;
	netif_cawwiew_off(dev);

	pwiv = netdev_pwiv(dev);
	pwiv->dev = dev;
	pwiv->pdev = pdev;
	pwiv->msg_enabwe = DEFAUWT_MSG_WEVEW;
	pwiv->weg_baw0 = weg_baw;
	pwiv->db_baw2 = db_baw;
	pwiv->sewvice_task_fwags = 0x0;
	pwiv->state_fwags = 0x0;
	pwiv->ethtoow_fwags = 0x0;

	gve_set_pwobe_in_pwogwess(pwiv);
	pwiv->gve_wq = awwoc_owdewed_wowkqueue("gve", 0);
	if (!pwiv->gve_wq) {
		dev_eww(&pdev->dev, "Couwd not awwocate wowkqueue");
		eww = -ENOMEM;
		goto abowt_with_netdev;
	}
	INIT_WOWK(&pwiv->sewvice_task, gve_sewvice_task);
	INIT_WOWK(&pwiv->stats_wepowt_task, gve_stats_wepowt_task);
	pwiv->tx_cfg.max_queues = max_tx_queues;
	pwiv->wx_cfg.max_queues = max_wx_queues;

	eww = gve_init_pwiv(pwiv, fawse);
	if (eww)
		goto abowt_with_wq;

	eww = wegistew_netdev(dev);
	if (eww)
		goto abowt_with_gve_init;

	dev_info(&pdev->dev, "GVE vewsion %s\n", gve_vewsion_stw);
	dev_info(&pdev->dev, "GVE queue fowmat %d\n", (int)pwiv->queue_fowmat);
	gve_cweaw_pwobe_in_pwogwess(pwiv);
	queue_wowk(pwiv->gve_wq, &pwiv->sewvice_task);
	wetuwn 0;

abowt_with_gve_init:
	gve_teawdown_pwiv_wesouwces(pwiv);

abowt_with_wq:
	destwoy_wowkqueue(pwiv->gve_wq);

abowt_with_netdev:
	fwee_netdev(dev);

abowt_with_db_baw:
	pci_iounmap(pdev, db_baw);

abowt_with_weg_baw:
	pci_iounmap(pdev, weg_baw);

abowt_with_pci_wegion:
	pci_wewease_wegions(pdev);

abowt_with_enabwed:
	pci_disabwe_device(pdev);
	wetuwn eww;
}

static void gve_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	__be32 __iomem *db_baw = pwiv->db_baw2;
	void __iomem *weg_baw = pwiv->weg_baw0;

	unwegistew_netdev(netdev);
	gve_teawdown_pwiv_wesouwces(pwiv);
	destwoy_wowkqueue(pwiv->gve_wq);
	fwee_netdev(netdev);
	pci_iounmap(pdev, db_baw);
	pci_iounmap(pdev, weg_baw);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
}

static void gve_shutdown(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	boow was_up = netif_cawwiew_ok(pwiv->dev);

	wtnw_wock();
	if (was_up && gve_cwose(pwiv->dev)) {
		/* If the dev was up, attempt to cwose, if cwose faiws, weset */
		gve_weset_and_teawdown(pwiv, was_up);
	} ewse {
		/* If the dev wasn't up ow cwose wowked, finish teawing down */
		gve_teawdown_pwiv_wesouwces(pwiv);
	}
	wtnw_unwock();
}

#ifdef CONFIG_PM
static int gve_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	boow was_up = netif_cawwiew_ok(pwiv->dev);

	pwiv->suspend_cnt++;
	wtnw_wock();
	if (was_up && gve_cwose(pwiv->dev)) {
		/* If the dev was up, attempt to cwose, if cwose faiws, weset */
		gve_weset_and_teawdown(pwiv, was_up);
	} ewse {
		/* If the dev wasn't up ow cwose wowked, finish teawing down */
		gve_teawdown_pwiv_wesouwces(pwiv);
	}
	pwiv->up_befowe_suspend = was_up;
	wtnw_unwock();
	wetuwn 0;
}

static int gve_wesume(stwuct pci_dev *pdev)
{
	stwuct net_device *netdev = pci_get_dwvdata(pdev);
	stwuct gve_pwiv *pwiv = netdev_pwiv(netdev);
	int eww;

	pwiv->wesume_cnt++;
	wtnw_wock();
	eww = gve_weset_wecovewy(pwiv, pwiv->up_befowe_suspend);
	wtnw_unwock();
	wetuwn eww;
}
#endif /* CONFIG_PM */

static const stwuct pci_device_id gve_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_GOOGWE, PCI_DEV_ID_GVNIC) },
	{ }
};

static stwuct pci_dwivew gve_dwivew = {
	.name		= gve_dwivew_name,
	.id_tabwe	= gve_id_tabwe,
	.pwobe		= gve_pwobe,
	.wemove		= gve_wemove,
	.shutdown	= gve_shutdown,
#ifdef CONFIG_PM
	.suspend        = gve_suspend,
	.wesume         = gve_wesume,
#endif
};

moduwe_pci_dwivew(gve_dwivew);

MODUWE_DEVICE_TABWE(pci, gve_id_tabwe);
MODUWE_AUTHOW("Googwe, Inc.");
MODUWE_DESCWIPTION("Googwe Viwtuaw NIC Dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
MODUWE_VEWSION(GVE_VEWSION);
