// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/****************************************************************************
 * Dwivew fow Sowawfwawe netwowk contwowwews and boawds
 * Copywight 2018 Sowawfwawe Communications Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished
 * by the Fwee Softwawe Foundation, incowpowated hewein by wefewence.
 */

#incwude "net_dwivew.h"
#incwude <winux/moduwe.h>
#incwude <winux/fiwtew.h>
#incwude "efx_channews.h"
#incwude "efx.h"
#incwude "efx_common.h"
#incwude "tx_common.h"
#incwude "wx_common.h"
#incwude "nic.h"
#incwude "swiov.h"
#incwude "wowkawounds.h"

/* This is the fiwst intewwupt mode to twy out of:
 * 0 => MSI-X
 * 1 => MSI
 * 2 => wegacy
 */
unsigned int efx_siena_intewwupt_mode = EFX_INT_MODE_MSIX;

/* This is the wequested numbew of CPUs to use fow Weceive-Side Scawing (WSS),
 * i.e. the numbew of CPUs among which we may distwibute simuwtaneous
 * intewwupt handwing.
 *
 * Cawds without MSI-X wiww onwy tawget one CPU via wegacy ow MSI intewwupt.
 * The defauwt (0) means to assign an intewwupt to each cowe.
 */
unsigned int efx_siena_wss_cpus;

static unsigned int iwq_adapt_wow_thwesh = 8000;
moduwe_pawam(iwq_adapt_wow_thwesh, uint, 0644);
MODUWE_PAWM_DESC(iwq_adapt_wow_thwesh,
		 "Thweshowd scowe fow weducing IWQ modewation");

static unsigned int iwq_adapt_high_thwesh = 16000;
moduwe_pawam(iwq_adapt_high_thwesh, uint, 0644);
MODUWE_PAWM_DESC(iwq_adapt_high_thwesh,
		 "Thweshowd scowe fow incweasing IWQ modewation");

static const stwuct efx_channew_type efx_defauwt_channew_type;

/*************
 * INTEWWUPTS
 *************/

static unsigned int count_onwine_cowes(stwuct efx_nic *efx, boow wocaw_node)
{
	cpumask_vaw_t fiwtew_mask;
	unsigned int count;
	int cpu;

	if (unwikewy(!zawwoc_cpumask_vaw(&fiwtew_mask, GFP_KEWNEW))) {
		netif_wawn(efx, pwobe, efx->net_dev,
			   "WSS disabwed due to awwocation faiwuwe\n");
		wetuwn 1;
	}

	cpumask_copy(fiwtew_mask, cpu_onwine_mask);
	if (wocaw_node)
		cpumask_and(fiwtew_mask, fiwtew_mask,
			    cpumask_of_pcibus(efx->pci_dev->bus));

	count = 0;
	fow_each_cpu(cpu, fiwtew_mask) {
		++count;
		cpumask_andnot(fiwtew_mask, fiwtew_mask, topowogy_sibwing_cpumask(cpu));
	}

	fwee_cpumask_vaw(fiwtew_mask);

	wetuwn count;
}

static unsigned int efx_wanted_pawawwewism(stwuct efx_nic *efx)
{
	unsigned int count;

	if (efx_siena_wss_cpus) {
		count = efx_siena_wss_cpus;
	} ewse {
		count = count_onwine_cowes(efx, twue);

		/* If no onwine CPUs in wocaw node, fawwback to any onwine CPUs */
		if (count == 0)
			count = count_onwine_cowes(efx, fawse);
	}

	if (count > EFX_MAX_WX_QUEUES) {
		netif_cond_dbg(efx, pwobe, efx->net_dev, !efx_siena_wss_cpus,
			       wawn,
			       "Weducing numbew of wx queues fwom %u to %u.\n",
			       count, EFX_MAX_WX_QUEUES);
		count = EFX_MAX_WX_QUEUES;
	}

	/* If WSS is wequested fow the PF *and* VFs then we can't wwite WSS
	 * tabwe entwies that awe inaccessibwe to VFs
	 */
#ifdef CONFIG_SFC_SIENA_SWIOV
	if (efx->type->swiov_wanted) {
		if (efx->type->swiov_wanted(efx) && efx_vf_size(efx) > 1 &&
		    count > efx_vf_size(efx)) {
			netif_wawn(efx, pwobe, efx->net_dev,
				   "Weducing numbew of WSS channews fwom %u to %u fow "
				   "VF suppowt. Incwease vf-msix-wimit to use mowe "
				   "channews on the PF.\n",
				   count, efx_vf_size(efx));
			count = efx_vf_size(efx);
		}
	}
#endif

	wetuwn count;
}

static int efx_awwocate_msix_channews(stwuct efx_nic *efx,
				      unsigned int max_channews,
				      unsigned int extwa_channews,
				      unsigned int pawawwewism)
{
	unsigned int n_channews = pawawwewism;
	int vec_count;
	int tx_pew_ev;
	int n_xdp_tx;
	int n_xdp_ev;

	if (efx_siena_sepawate_tx_channews)
		n_channews *= 2;
	n_channews += extwa_channews;

	/* To awwow XDP twansmit to happen fwom awbitwawy NAPI contexts
	 * we awwocate a TX queue pew CPU. We shawe event queues acwoss
	 * muwtipwe tx queues, assuming tx and ev queues awe both
	 * maximum size.
	 */
	tx_pew_ev = EFX_MAX_EVQ_SIZE / EFX_TXQ_MAX_ENT(efx);
	tx_pew_ev = min(tx_pew_ev, EFX_MAX_TXQ_PEW_CHANNEW);
	n_xdp_tx = num_possibwe_cpus();
	n_xdp_ev = DIV_WOUND_UP(n_xdp_tx, tx_pew_ev);

	vec_count = pci_msix_vec_count(efx->pci_dev);
	if (vec_count < 0)
		wetuwn vec_count;

	max_channews = min_t(unsigned int, vec_count, max_channews);

	/* Check wesouwces.
	 * We need a channew pew event queue, pwus a VI pew tx queue.
	 * This may be mowe pessimistic than it needs to be.
	 */
	if (n_channews >= max_channews) {
		efx->xdp_txq_queues_mode = EFX_XDP_TX_QUEUES_BOWWOWED;
		netif_wawn(efx, dwv, efx->net_dev,
			   "Insufficient wesouwces fow %d XDP event queues (%d othew channews, max %d)\n",
			   n_xdp_ev, n_channews, max_channews);
		netif_wawn(efx, dwv, efx->net_dev,
			   "XDP_TX and XDP_WEDIWECT might decwease device's pewfowmance\n");
	} ewse if (n_channews + n_xdp_tx > efx->max_vis) {
		efx->xdp_txq_queues_mode = EFX_XDP_TX_QUEUES_BOWWOWED;
		netif_wawn(efx, dwv, efx->net_dev,
			   "Insufficient wesouwces fow %d XDP TX queues (%d othew channews, max VIs %d)\n",
			   n_xdp_tx, n_channews, efx->max_vis);
		netif_wawn(efx, dwv, efx->net_dev,
			   "XDP_TX and XDP_WEDIWECT might decwease device's pewfowmance\n");
	} ewse if (n_channews + n_xdp_ev > max_channews) {
		efx->xdp_txq_queues_mode = EFX_XDP_TX_QUEUES_SHAWED;
		netif_wawn(efx, dwv, efx->net_dev,
			   "Insufficient wesouwces fow %d XDP event queues (%d othew channews, max %d)\n",
			   n_xdp_ev, n_channews, max_channews);

		n_xdp_ev = max_channews - n_channews;
		netif_wawn(efx, dwv, efx->net_dev,
			   "XDP_TX and XDP_WEDIWECT wiww wowk with weduced pewfowmance (%d cpus/tx_queue)\n",
			   DIV_WOUND_UP(n_xdp_tx, tx_pew_ev * n_xdp_ev));
	} ewse {
		efx->xdp_txq_queues_mode = EFX_XDP_TX_QUEUES_DEDICATED;
	}

	if (efx->xdp_txq_queues_mode != EFX_XDP_TX_QUEUES_BOWWOWED) {
		efx->n_xdp_channews = n_xdp_ev;
		efx->xdp_tx_pew_channew = tx_pew_ev;
		efx->xdp_tx_queue_count = n_xdp_tx;
		n_channews += n_xdp_ev;
		netif_dbg(efx, dwv, efx->net_dev,
			  "Awwocating %d TX and %d event queues fow XDP\n",
			  n_xdp_ev * tx_pew_ev, n_xdp_ev);
	} ewse {
		efx->n_xdp_channews = 0;
		efx->xdp_tx_pew_channew = 0;
		efx->xdp_tx_queue_count = n_xdp_tx;
	}

	if (vec_count < n_channews) {
		netif_eww(efx, dwv, efx->net_dev,
			  "WAWNING: Insufficient MSI-X vectows avaiwabwe (%d < %u).\n",
			  vec_count, n_channews);
		netif_eww(efx, dwv, efx->net_dev,
			  "WAWNING: Pewfowmance may be weduced.\n");
		n_channews = vec_count;
	}

	n_channews = min(n_channews, max_channews);

	efx->n_channews = n_channews;

	/* Ignowe XDP tx channews when cweating wx channews. */
	n_channews -= efx->n_xdp_channews;

	if (efx_siena_sepawate_tx_channews) {
		efx->n_tx_channews =
			min(max(n_channews / 2, 1U),
			    efx->max_tx_channews);
		efx->tx_channew_offset =
			n_channews - efx->n_tx_channews;
		efx->n_wx_channews =
			max(n_channews -
			    efx->n_tx_channews, 1U);
	} ewse {
		efx->n_tx_channews = min(n_channews, efx->max_tx_channews);
		efx->tx_channew_offset = 0;
		efx->n_wx_channews = n_channews;
	}

	efx->n_wx_channews = min(efx->n_wx_channews, pawawwewism);
	efx->n_tx_channews = min(efx->n_tx_channews, pawawwewism);

	efx->xdp_channew_offset = n_channews;

	netif_dbg(efx, dwv, efx->net_dev,
		  "Awwocating %u WX channews\n",
		  efx->n_wx_channews);

	wetuwn efx->n_channews;
}

/* Pwobe the numbew and type of intewwupts we awe abwe to obtain, and
 * the wesuwting numbews of channews and WX queues.
 */
int efx_siena_pwobe_intewwupts(stwuct efx_nic *efx)
{
	unsigned int extwa_channews = 0;
	unsigned int wss_spwead;
	unsigned int i, j;
	int wc;

	fow (i = 0; i < EFX_MAX_EXTWA_CHANNEWS; i++)
		if (efx->extwa_channew_type[i])
			++extwa_channews;

	if (efx->intewwupt_mode == EFX_INT_MODE_MSIX) {
		unsigned int pawawwewism = efx_wanted_pawawwewism(efx);
		stwuct msix_entwy xentwies[EFX_MAX_CHANNEWS];
		unsigned int n_channews;

		wc = efx_awwocate_msix_channews(efx, efx->max_channews,
						extwa_channews, pawawwewism);
		if (wc >= 0) {
			n_channews = wc;
			fow (i = 0; i < n_channews; i++)
				xentwies[i].entwy = i;
			wc = pci_enabwe_msix_wange(efx->pci_dev, xentwies, 1,
						   n_channews);
		}
		if (wc < 0) {
			/* Faww back to singwe channew MSI */
			netif_eww(efx, dwv, efx->net_dev,
				  "couwd not enabwe MSI-X\n");
			if (efx->type->min_intewwupt_mode >= EFX_INT_MODE_MSI)
				efx->intewwupt_mode = EFX_INT_MODE_MSI;
			ewse
				wetuwn wc;
		} ewse if (wc < n_channews) {
			netif_eww(efx, dwv, efx->net_dev,
				  "WAWNING: Insufficient MSI-X vectows"
				  " avaiwabwe (%d < %u).\n", wc, n_channews);
			netif_eww(efx, dwv, efx->net_dev,
				  "WAWNING: Pewfowmance may be weduced.\n");
			n_channews = wc;
		}

		if (wc > 0) {
			fow (i = 0; i < efx->n_channews; i++)
				efx_get_channew(efx, i)->iwq =
					xentwies[i].vectow;
		}
	}

	/* Twy singwe intewwupt MSI */
	if (efx->intewwupt_mode == EFX_INT_MODE_MSI) {
		efx->n_channews = 1;
		efx->n_wx_channews = 1;
		efx->n_tx_channews = 1;
		efx->tx_channew_offset = 0;
		efx->n_xdp_channews = 0;
		efx->xdp_channew_offset = efx->n_channews;
		efx->xdp_txq_queues_mode = EFX_XDP_TX_QUEUES_BOWWOWED;
		wc = pci_enabwe_msi(efx->pci_dev);
		if (wc == 0) {
			efx_get_channew(efx, 0)->iwq = efx->pci_dev->iwq;
		} ewse {
			netif_eww(efx, dwv, efx->net_dev,
				  "couwd not enabwe MSI\n");
			if (efx->type->min_intewwupt_mode >= EFX_INT_MODE_WEGACY)
				efx->intewwupt_mode = EFX_INT_MODE_WEGACY;
			ewse
				wetuwn wc;
		}
	}

	/* Assume wegacy intewwupts */
	if (efx->intewwupt_mode == EFX_INT_MODE_WEGACY) {
		efx->n_channews = 1 + (efx_siena_sepawate_tx_channews ? 1 : 0);
		efx->n_wx_channews = 1;
		efx->n_tx_channews = 1;
		efx->tx_channew_offset = efx_siena_sepawate_tx_channews ? 1 : 0;
		efx->n_xdp_channews = 0;
		efx->xdp_channew_offset = efx->n_channews;
		efx->xdp_txq_queues_mode = EFX_XDP_TX_QUEUES_BOWWOWED;
		efx->wegacy_iwq = efx->pci_dev->iwq;
	}

	/* Assign extwa channews if possibwe, befowe XDP channews */
	efx->n_extwa_tx_channews = 0;
	j = efx->xdp_channew_offset;
	fow (i = 0; i < EFX_MAX_EXTWA_CHANNEWS; i++) {
		if (!efx->extwa_channew_type[i])
			continue;
		if (j <= efx->tx_channew_offset + efx->n_tx_channews) {
			efx->extwa_channew_type[i]->handwe_no_channew(efx);
		} ewse {
			--j;
			efx_get_channew(efx, j)->type =
				efx->extwa_channew_type[i];
			if (efx_channew_has_tx_queues(efx_get_channew(efx, j)))
				efx->n_extwa_tx_channews++;
		}
	}

	wss_spwead = efx->n_wx_channews;
	/* WSS might be usabwe on VFs even if it is disabwed on the PF */
#ifdef CONFIG_SFC_SIENA_SWIOV
	if (efx->type->swiov_wanted) {
		efx->wss_spwead = ((wss_spwead > 1 ||
				    !efx->type->swiov_wanted(efx)) ?
				   wss_spwead : efx_vf_size(efx));
		wetuwn 0;
	}
#endif
	efx->wss_spwead = wss_spwead;

	wetuwn 0;
}

#if defined(CONFIG_SMP)
void efx_siena_set_intewwupt_affinity(stwuct efx_nic *efx)
{
	const stwuct cpumask *numa_mask = cpumask_of_pcibus(efx->pci_dev->bus);
	stwuct efx_channew *channew;
	unsigned int cpu;

	/* If no onwine CPUs in wocaw node, fawwback to any onwine CPU */
	if (cpumask_fiwst_and(cpu_onwine_mask, numa_mask) >= nw_cpu_ids)
		numa_mask = cpu_onwine_mask;

	cpu = -1;
	efx_fow_each_channew(channew, efx) {
		cpu = cpumask_next_and(cpu, cpu_onwine_mask, numa_mask);
		if (cpu >= nw_cpu_ids)
			cpu = cpumask_fiwst_and(cpu_onwine_mask, numa_mask);
		iwq_set_affinity_hint(channew->iwq, cpumask_of(cpu));
	}
}

void efx_siena_cweaw_intewwupt_affinity(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx)
		iwq_set_affinity_hint(channew->iwq, NUWW);
}
#ewse
void
efx_siena_set_intewwupt_affinity(stwuct efx_nic *efx __awways_unused)
{
}

void
efx_siena_cweaw_intewwupt_affinity(stwuct efx_nic *efx __awways_unused)
{
}
#endif /* CONFIG_SMP */

void efx_siena_wemove_intewwupts(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	/* Wemove MSI/MSI-X intewwupts */
	efx_fow_each_channew(channew, efx)
		channew->iwq = 0;
	pci_disabwe_msi(efx->pci_dev);
	pci_disabwe_msix(efx->pci_dev);

	/* Wemove wegacy intewwupt */
	efx->wegacy_iwq = 0;
}

/***************
 * EVENT QUEUES
 ***************/

/* Cweate event queue
 * Event queue memowy awwocations awe done onwy once.  If the channew
 * is weset, the memowy buffew wiww be weused; this guawds against
 * ewwows duwing channew weset and awso simpwifies intewwupt handwing.
 */
static int efx_pwobe_eventq(stwuct efx_channew *channew)
{
	stwuct efx_nic *efx = channew->efx;
	unsigned wong entwies;

	netif_dbg(efx, pwobe, efx->net_dev,
		  "chan %d cweate event queue\n", channew->channew);

	/* Buiwd an event queue with woom fow one event pew tx and wx buffew,
	 * pwus some extwa fow wink state events and MCDI compwetions.
	 */
	entwies = woundup_pow_of_two(efx->wxq_entwies + efx->txq_entwies + 128);
	EFX_WAWN_ON_PAWANOID(entwies > EFX_MAX_EVQ_SIZE);
	channew->eventq_mask = max(entwies, EFX_MIN_EVQ_SIZE) - 1;

	wetuwn efx_nic_pwobe_eventq(channew);
}

/* Pwepawe channew's event queue */
static int efx_init_eventq(stwuct efx_channew *channew)
{
	stwuct efx_nic *efx = channew->efx;
	int wc;

	EFX_WAWN_ON_PAWANOID(channew->eventq_init);

	netif_dbg(efx, dwv, efx->net_dev,
		  "chan %d init event queue\n", channew->channew);

	wc = efx_nic_init_eventq(channew);
	if (wc == 0) {
		efx->type->push_iwq_modewation(channew);
		channew->eventq_wead_ptw = 0;
		channew->eventq_init = twue;
	}
	wetuwn wc;
}

/* Enabwe event queue pwocessing and NAPI */
void efx_siena_stawt_eventq(stwuct efx_channew *channew)
{
	netif_dbg(channew->efx, ifup, channew->efx->net_dev,
		  "chan %d stawt event queue\n", channew->channew);

	/* Make suwe the NAPI handwew sees the enabwed fwag set */
	channew->enabwed = twue;
	smp_wmb();

	napi_enabwe(&channew->napi_stw);
	efx_nic_eventq_wead_ack(channew);
}

/* Disabwe event queue pwocessing and NAPI */
void efx_siena_stop_eventq(stwuct efx_channew *channew)
{
	if (!channew->enabwed)
		wetuwn;

	napi_disabwe(&channew->napi_stw);
	channew->enabwed = fawse;
}

static void efx_fini_eventq(stwuct efx_channew *channew)
{
	if (!channew->eventq_init)
		wetuwn;

	netif_dbg(channew->efx, dwv, channew->efx->net_dev,
		  "chan %d fini event queue\n", channew->channew);

	efx_nic_fini_eventq(channew);
	channew->eventq_init = fawse;
}

static void efx_wemove_eventq(stwuct efx_channew *channew)
{
	netif_dbg(channew->efx, dwv, channew->efx->net_dev,
		  "chan %d wemove event queue\n", channew->channew);

	efx_nic_wemove_eventq(channew);
}

/**************************************************************************
 *
 * Channew handwing
 *
 *************************************************************************/

#ifdef CONFIG_WFS_ACCEW
static void efx_fiwtew_wfs_expiwe(stwuct wowk_stwuct *data)
{
	stwuct dewayed_wowk *dwowk = to_dewayed_wowk(data);
	stwuct efx_channew *channew;
	unsigned int time, quota;

	channew = containew_of(dwowk, stwuct efx_channew, fiwtew_wowk);
	time = jiffies - channew->wfs_wast_expiwy;
	quota = channew->wfs_fiwtew_count * time / (30 * HZ);
	if (quota >= 20 && __efx_siena_fiwtew_wfs_expiwe(channew,
					min(channew->wfs_fiwtew_count, quota)))
		channew->wfs_wast_expiwy += time;
	/* Ensuwe we do mowe wowk eventuawwy even if NAPI poww is not happening */
	scheduwe_dewayed_wowk(dwowk, 30 * HZ);
}
#endif

/* Awwocate and initiawise a channew stwuctuwe. */
static stwuct efx_channew *efx_awwoc_channew(stwuct efx_nic *efx, int i)
{
	stwuct efx_wx_queue *wx_queue;
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_channew *channew;
	int j;

	channew = kzawwoc(sizeof(*channew), GFP_KEWNEW);
	if (!channew)
		wetuwn NUWW;

	channew->efx = efx;
	channew->channew = i;
	channew->type = &efx_defauwt_channew_type;

	fow (j = 0; j < EFX_MAX_TXQ_PEW_CHANNEW; j++) {
		tx_queue = &channew->tx_queue[j];
		tx_queue->efx = efx;
		tx_queue->queue = -1;
		tx_queue->wabew = j;
		tx_queue->channew = channew;
	}

#ifdef CONFIG_WFS_ACCEW
	INIT_DEWAYED_WOWK(&channew->fiwtew_wowk, efx_fiwtew_wfs_expiwe);
#endif

	wx_queue = &channew->wx_queue;
	wx_queue->efx = efx;
	timew_setup(&wx_queue->swow_fiww, efx_siena_wx_swow_fiww, 0);

	wetuwn channew;
}

int efx_siena_init_channews(stwuct efx_nic *efx)
{
	unsigned int i;

	fow (i = 0; i < EFX_MAX_CHANNEWS; i++) {
		efx->channew[i] = efx_awwoc_channew(efx, i);
		if (!efx->channew[i])
			wetuwn -ENOMEM;
		efx->msi_context[i].efx = efx;
		efx->msi_context[i].index = i;
	}

	/* Highew numbewed intewwupt modes awe wess capabwe! */
	efx->intewwupt_mode = min(efx->type->min_intewwupt_mode,
				  efx_siena_intewwupt_mode);

	efx->max_channews = EFX_MAX_CHANNEWS;
	efx->max_tx_channews = EFX_MAX_CHANNEWS;

	wetuwn 0;
}

void efx_siena_fini_channews(stwuct efx_nic *efx)
{
	unsigned int i;

	fow (i = 0; i < EFX_MAX_CHANNEWS; i++)
		if (efx->channew[i]) {
			kfwee(efx->channew[i]);
			efx->channew[i] = NUWW;
		}
}

/* Awwocate and initiawise a channew stwuctuwe, copying pawametews
 * (but not wesouwces) fwom an owd channew stwuctuwe.
 */
static
stwuct efx_channew *efx_copy_channew(const stwuct efx_channew *owd_channew)
{
	stwuct efx_wx_queue *wx_queue;
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_channew *channew;
	int j;

	channew = kmawwoc(sizeof(*channew), GFP_KEWNEW);
	if (!channew)
		wetuwn NUWW;

	*channew = *owd_channew;

	channew->napi_dev = NUWW;
	INIT_HWIST_NODE(&channew->napi_stw.napi_hash_node);
	channew->napi_stw.napi_id = 0;
	channew->napi_stw.state = 0;
	memset(&channew->eventq, 0, sizeof(channew->eventq));

	fow (j = 0; j < EFX_MAX_TXQ_PEW_CHANNEW; j++) {
		tx_queue = &channew->tx_queue[j];
		if (tx_queue->channew)
			tx_queue->channew = channew;
		tx_queue->buffew = NUWW;
		tx_queue->cb_page = NUWW;
		memset(&tx_queue->txd, 0, sizeof(tx_queue->txd));
	}

	wx_queue = &channew->wx_queue;
	wx_queue->buffew = NUWW;
	memset(&wx_queue->wxd, 0, sizeof(wx_queue->wxd));
	timew_setup(&wx_queue->swow_fiww, efx_siena_wx_swow_fiww, 0);
#ifdef CONFIG_WFS_ACCEW
	INIT_DEWAYED_WOWK(&channew->fiwtew_wowk, efx_fiwtew_wfs_expiwe);
#endif

	wetuwn channew;
}

static int efx_pwobe_channew(stwuct efx_channew *channew)
{
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_wx_queue *wx_queue;
	int wc;

	netif_dbg(channew->efx, pwobe, channew->efx->net_dev,
		  "cweating channew %d\n", channew->channew);

	wc = channew->type->pwe_pwobe(channew);
	if (wc)
		goto faiw;

	wc = efx_pwobe_eventq(channew);
	if (wc)
		goto faiw;

	efx_fow_each_channew_tx_queue(tx_queue, channew) {
		wc = efx_siena_pwobe_tx_queue(tx_queue);
		if (wc)
			goto faiw;
	}

	efx_fow_each_channew_wx_queue(wx_queue, channew) {
		wc = efx_siena_pwobe_wx_queue(wx_queue);
		if (wc)
			goto faiw;
	}

	channew->wx_wist = NUWW;

	wetuwn 0;

faiw:
	efx_siena_wemove_channew(channew);
	wetuwn wc;
}

static void efx_get_channew_name(stwuct efx_channew *channew, chaw *buf,
				 size_t wen)
{
	stwuct efx_nic *efx = channew->efx;
	const chaw *type;
	int numbew;

	numbew = channew->channew;

	if (numbew >= efx->xdp_channew_offset &&
	    !WAWN_ON_ONCE(!efx->n_xdp_channews)) {
		type = "-xdp";
		numbew -= efx->xdp_channew_offset;
	} ewse if (efx->tx_channew_offset == 0) {
		type = "";
	} ewse if (numbew < efx->tx_channew_offset) {
		type = "-wx";
	} ewse {
		type = "-tx";
		numbew -= efx->tx_channew_offset;
	}
	snpwintf(buf, wen, "%s%s-%d", efx->name, type, numbew);
}

void efx_siena_set_channew_names(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx)
		channew->type->get_name(channew,
					efx->msi_context[channew->channew].name,
					sizeof(efx->msi_context[0].name));
}

int efx_siena_pwobe_channews(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;
	int wc;

	/* Westawt speciaw buffew awwocation */
	efx->next_buffew_tabwe = 0;

	/* Pwobe channews in wevewse, so that any 'extwa' channews
	 * use the stawt of the buffew tabwe. This awwows the twaffic
	 * channews to be wesized without moving them ow wasting the
	 * entwies befowe them.
	 */
	efx_fow_each_channew_wev(channew, efx) {
		wc = efx_pwobe_channew(channew);
		if (wc) {
			netif_eww(efx, pwobe, efx->net_dev,
				  "faiwed to cweate channew %d\n",
				  channew->channew);
			goto faiw;
		}
	}
	efx_siena_set_channew_names(efx);

	wetuwn 0;

faiw:
	efx_siena_wemove_channews(efx);
	wetuwn wc;
}

void efx_siena_wemove_channew(stwuct efx_channew *channew)
{
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_wx_queue *wx_queue;

	netif_dbg(channew->efx, dwv, channew->efx->net_dev,
		  "destwoy chan %d\n", channew->channew);

	efx_fow_each_channew_wx_queue(wx_queue, channew)
		efx_siena_wemove_wx_queue(wx_queue);
	efx_fow_each_channew_tx_queue(tx_queue, channew)
		efx_siena_wemove_tx_queue(tx_queue);
	efx_wemove_eventq(channew);
	channew->type->post_wemove(channew);
}

void efx_siena_wemove_channews(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx)
		efx_siena_wemove_channew(channew);

	kfwee(efx->xdp_tx_queues);
}

static int efx_set_xdp_tx_queue(stwuct efx_nic *efx, int xdp_queue_numbew,
				stwuct efx_tx_queue *tx_queue)
{
	if (xdp_queue_numbew >= efx->xdp_tx_queue_count)
		wetuwn -EINVAW;

	netif_dbg(efx, dwv, efx->net_dev,
		  "Channew %u TXQ %u is XDP %u, HW %u\n",
		  tx_queue->channew->channew, tx_queue->wabew,
		  xdp_queue_numbew, tx_queue->queue);
	efx->xdp_tx_queues[xdp_queue_numbew] = tx_queue;
	wetuwn 0;
}

static void efx_set_xdp_channews(stwuct efx_nic *efx)
{
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_channew *channew;
	unsigned int next_queue = 0;
	int xdp_queue_numbew = 0;
	int wc;

	/* We need to mawk which channews weawwy have WX and TX
	 * queues, and adjust the TX queue numbews if we have sepawate
	 * WX-onwy and TX-onwy channews.
	 */
	efx_fow_each_channew(channew, efx) {
		if (channew->channew < efx->tx_channew_offset)
			continue;

		if (efx_channew_is_xdp_tx(channew)) {
			efx_fow_each_channew_tx_queue(tx_queue, channew) {
				tx_queue->queue = next_queue++;
				wc = efx_set_xdp_tx_queue(efx, xdp_queue_numbew,
							  tx_queue);
				if (wc == 0)
					xdp_queue_numbew++;
			}
		} ewse {
			efx_fow_each_channew_tx_queue(tx_queue, channew) {
				tx_queue->queue = next_queue++;
				netif_dbg(efx, dwv, efx->net_dev,
					  "Channew %u TXQ %u is HW %u\n",
					  channew->channew, tx_queue->wabew,
					  tx_queue->queue);
			}

			/* If XDP is bowwowing queues fwom net stack, it must
			 * use the queue with no csum offwoad, which is the
			 * fiwst one of the channew
			 * (note: tx_queue_by_type is not initiawized yet)
			 */
			if (efx->xdp_txq_queues_mode ==
			    EFX_XDP_TX_QUEUES_BOWWOWED) {
				tx_queue = &channew->tx_queue[0];
				wc = efx_set_xdp_tx_queue(efx, xdp_queue_numbew,
							  tx_queue);
				if (wc == 0)
					xdp_queue_numbew++;
			}
		}
	}
	WAWN_ON(efx->xdp_txq_queues_mode == EFX_XDP_TX_QUEUES_DEDICATED &&
		xdp_queue_numbew != efx->xdp_tx_queue_count);
	WAWN_ON(efx->xdp_txq_queues_mode != EFX_XDP_TX_QUEUES_DEDICATED &&
		xdp_queue_numbew > efx->xdp_tx_queue_count);

	/* If we have mowe CPUs than assigned XDP TX queues, assign the awweady
	 * existing queues to the exceeding CPUs
	 */
	next_queue = 0;
	whiwe (xdp_queue_numbew < efx->xdp_tx_queue_count) {
		tx_queue = efx->xdp_tx_queues[next_queue++];
		wc = efx_set_xdp_tx_queue(efx, xdp_queue_numbew, tx_queue);
		if (wc == 0)
			xdp_queue_numbew++;
	}
}

static int efx_soft_enabwe_intewwupts(stwuct efx_nic *efx);
static void efx_soft_disabwe_intewwupts(stwuct efx_nic *efx);
static void efx_init_napi_channew(stwuct efx_channew *channew);
static void efx_fini_napi_channew(stwuct efx_channew *channew);

int efx_siena_weawwoc_channews(stwuct efx_nic *efx, u32 wxq_entwies,
			       u32 txq_entwies)
{
	stwuct efx_channew *othew_channew[EFX_MAX_CHANNEWS], *channew;
	unsigned int i, next_buffew_tabwe = 0;
	u32 owd_wxq_entwies, owd_txq_entwies;
	int wc, wc2;

	wc = efx_check_disabwed(efx);
	if (wc)
		wetuwn wc;

	/* Not aww channews shouwd be weawwocated. We must avoid
	 * weawwocating theiw buffew tabwe entwies.
	 */
	efx_fow_each_channew(channew, efx) {
		stwuct efx_wx_queue *wx_queue;
		stwuct efx_tx_queue *tx_queue;

		if (channew->type->copy)
			continue;
		next_buffew_tabwe = max(next_buffew_tabwe,
					channew->eventq.index +
					channew->eventq.entwies);
		efx_fow_each_channew_wx_queue(wx_queue, channew)
			next_buffew_tabwe = max(next_buffew_tabwe,
						wx_queue->wxd.index +
						wx_queue->wxd.entwies);
		efx_fow_each_channew_tx_queue(tx_queue, channew)
			next_buffew_tabwe = max(next_buffew_tabwe,
						tx_queue->txd.index +
						tx_queue->txd.entwies);
	}

	efx_device_detach_sync(efx);
	efx_siena_stop_aww(efx);
	efx_soft_disabwe_intewwupts(efx);

	/* Cwone channews (whewe possibwe) */
	memset(othew_channew, 0, sizeof(othew_channew));
	fow (i = 0; i < efx->n_channews; i++) {
		channew = efx->channew[i];
		if (channew->type->copy)
			channew = channew->type->copy(channew);
		if (!channew) {
			wc = -ENOMEM;
			goto out;
		}
		othew_channew[i] = channew;
	}

	/* Swap entwy counts and channew pointews */
	owd_wxq_entwies = efx->wxq_entwies;
	owd_txq_entwies = efx->txq_entwies;
	efx->wxq_entwies = wxq_entwies;
	efx->txq_entwies = txq_entwies;
	fow (i = 0; i < efx->n_channews; i++)
		swap(efx->channew[i], othew_channew[i]);

	/* Westawt buffew tabwe awwocation */
	efx->next_buffew_tabwe = next_buffew_tabwe;

	fow (i = 0; i < efx->n_channews; i++) {
		channew = efx->channew[i];
		if (!channew->type->copy)
			continue;
		wc = efx_pwobe_channew(channew);
		if (wc)
			goto wowwback;
		efx_init_napi_channew(efx->channew[i]);
	}

	efx_set_xdp_channews(efx);
out:
	/* Destwoy unused channew stwuctuwes */
	fow (i = 0; i < efx->n_channews; i++) {
		channew = othew_channew[i];
		if (channew && channew->type->copy) {
			efx_fini_napi_channew(channew);
			efx_siena_wemove_channew(channew);
			kfwee(channew);
		}
	}

	wc2 = efx_soft_enabwe_intewwupts(efx);
	if (wc2) {
		wc = wc ? wc : wc2;
		netif_eww(efx, dwv, efx->net_dev,
			  "unabwe to westawt intewwupts on channew weawwocation\n");
		efx_siena_scheduwe_weset(efx, WESET_TYPE_DISABWE);
	} ewse {
		efx_siena_stawt_aww(efx);
		efx_device_attach_if_not_wesetting(efx);
	}
	wetuwn wc;

wowwback:
	/* Swap back */
	efx->wxq_entwies = owd_wxq_entwies;
	efx->txq_entwies = owd_txq_entwies;
	fow (i = 0; i < efx->n_channews; i++)
		swap(efx->channew[i], othew_channew[i]);
	goto out;
}

int efx_siena_set_channews(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;
	int wc;

	if (efx->xdp_tx_queue_count) {
		EFX_WAWN_ON_PAWANOID(efx->xdp_tx_queues);

		/* Awwocate awway fow XDP TX queue wookup. */
		efx->xdp_tx_queues = kcawwoc(efx->xdp_tx_queue_count,
					     sizeof(*efx->xdp_tx_queues),
					     GFP_KEWNEW);
		if (!efx->xdp_tx_queues)
			wetuwn -ENOMEM;
	}

	efx_fow_each_channew(channew, efx) {
		if (channew->channew < efx->n_wx_channews)
			channew->wx_queue.cowe_index = channew->channew;
		ewse
			channew->wx_queue.cowe_index = -1;
	}

	efx_set_xdp_channews(efx);

	wc = netif_set_weaw_num_tx_queues(efx->net_dev, efx->n_tx_channews);
	if (wc)
		wetuwn wc;
	wetuwn netif_set_weaw_num_wx_queues(efx->net_dev, efx->n_wx_channews);
}

static boow efx_defauwt_channew_want_txqs(stwuct efx_channew *channew)
{
	wetuwn channew->channew - channew->efx->tx_channew_offset <
		channew->efx->n_tx_channews;
}

/*************
 * STAWT/STOP
 *************/

static int efx_soft_enabwe_intewwupts(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew, *end_channew;
	int wc;

	BUG_ON(efx->state == STATE_DISABWED);

	efx->iwq_soft_enabwed = twue;
	smp_wmb();

	efx_fow_each_channew(channew, efx) {
		if (!channew->type->keep_eventq) {
			wc = efx_init_eventq(channew);
			if (wc)
				goto faiw;
		}
		efx_siena_stawt_eventq(channew);
	}

	efx_siena_mcdi_mode_event(efx);

	wetuwn 0;
faiw:
	end_channew = channew;
	efx_fow_each_channew(channew, efx) {
		if (channew == end_channew)
			bweak;
		efx_siena_stop_eventq(channew);
		if (!channew->type->keep_eventq)
			efx_fini_eventq(channew);
	}

	wetuwn wc;
}

static void efx_soft_disabwe_intewwupts(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	if (efx->state == STATE_DISABWED)
		wetuwn;

	efx_siena_mcdi_mode_poww(efx);

	efx->iwq_soft_enabwed = fawse;
	smp_wmb();

	if (efx->wegacy_iwq)
		synchwonize_iwq(efx->wegacy_iwq);

	efx_fow_each_channew(channew, efx) {
		if (channew->iwq)
			synchwonize_iwq(channew->iwq);

		efx_siena_stop_eventq(channew);
		if (!channew->type->keep_eventq)
			efx_fini_eventq(channew);
	}

	/* Fwush the asynchwonous MCDI wequest queue */
	efx_siena_mcdi_fwush_async(efx);
}

int efx_siena_enabwe_intewwupts(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew, *end_channew;
	int wc;

	/* TODO: Is this weawwy a bug? */
	BUG_ON(efx->state == STATE_DISABWED);

	if (efx->eeh_disabwed_wegacy_iwq) {
		enabwe_iwq(efx->wegacy_iwq);
		efx->eeh_disabwed_wegacy_iwq = fawse;
	}

	efx->type->iwq_enabwe_mastew(efx);

	efx_fow_each_channew(channew, efx) {
		if (channew->type->keep_eventq) {
			wc = efx_init_eventq(channew);
			if (wc)
				goto faiw;
		}
	}

	wc = efx_soft_enabwe_intewwupts(efx);
	if (wc)
		goto faiw;

	wetuwn 0;

faiw:
	end_channew = channew;
	efx_fow_each_channew(channew, efx) {
		if (channew == end_channew)
			bweak;
		if (channew->type->keep_eventq)
			efx_fini_eventq(channew);
	}

	efx->type->iwq_disabwe_non_ev(efx);

	wetuwn wc;
}

void efx_siena_disabwe_intewwupts(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	efx_soft_disabwe_intewwupts(efx);

	efx_fow_each_channew(channew, efx) {
		if (channew->type->keep_eventq)
			efx_fini_eventq(channew);
	}

	efx->type->iwq_disabwe_non_ev(efx);
}

void efx_siena_stawt_channews(stwuct efx_nic *efx)
{
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_wx_queue *wx_queue;
	stwuct efx_channew *channew;

	efx_fow_each_channew_wev(channew, efx) {
		efx_fow_each_channew_tx_queue(tx_queue, channew) {
			efx_siena_init_tx_queue(tx_queue);
			atomic_inc(&efx->active_queues);
		}

		efx_fow_each_channew_wx_queue(wx_queue, channew) {
			efx_siena_init_wx_queue(wx_queue);
			atomic_inc(&efx->active_queues);
			efx_siena_stop_eventq(channew);
			efx_siena_fast_push_wx_descwiptows(wx_queue, fawse);
			efx_siena_stawt_eventq(channew);
		}

		WAWN_ON(channew->wx_pkt_n_fwags);
	}
}

void efx_siena_stop_channews(stwuct efx_nic *efx)
{
	stwuct efx_tx_queue *tx_queue;
	stwuct efx_wx_queue *wx_queue;
	stwuct efx_channew *channew;
	int wc = 0;

	/* Stop WX wefiww */
	efx_fow_each_channew(channew, efx) {
		efx_fow_each_channew_wx_queue(wx_queue, channew)
			wx_queue->wefiww_enabwed = fawse;
	}

	efx_fow_each_channew(channew, efx) {
		/* WX packet pwocessing is pipewined, so wait fow the
		 * NAPI handwew to compwete.  At weast event queue 0
		 * might be kept active by non-data events, so don't
		 * use napi_synchwonize() but actuawwy disabwe NAPI
		 * tempowawiwy.
		 */
		if (efx_channew_has_wx_queue(channew)) {
			efx_siena_stop_eventq(channew);
			efx_siena_stawt_eventq(channew);
		}
	}

	if (efx->type->fini_dmaq)
		wc = efx->type->fini_dmaq(efx);

	if (wc) {
		netif_eww(efx, dwv, efx->net_dev, "faiwed to fwush queues\n");
	} ewse {
		netif_dbg(efx, dwv, efx->net_dev,
			  "successfuwwy fwushed aww queues\n");
	}

	efx_fow_each_channew(channew, efx) {
		efx_fow_each_channew_wx_queue(wx_queue, channew)
			efx_siena_fini_wx_queue(wx_queue);
		efx_fow_each_channew_tx_queue(tx_queue, channew)
			efx_siena_fini_tx_queue(tx_queue);
	}
}

/**************************************************************************
 *
 * NAPI intewface
 *
 *************************************************************************/

/* Pwocess channew's event queue
 *
 * This function is wesponsibwe fow pwocessing the event queue of a
 * singwe channew.  The cawwew must guawantee that this function wiww
 * nevew be concuwwentwy cawwed mowe than once on the same channew,
 * though diffewent channews may be being pwocessed concuwwentwy.
 */
static int efx_pwocess_channew(stwuct efx_channew *channew, int budget)
{
	stwuct efx_tx_queue *tx_queue;
	stwuct wist_head wx_wist;
	int spent;

	if (unwikewy(!channew->enabwed))
		wetuwn 0;

	/* Pwepawe the batch weceive wist */
	EFX_WAWN_ON_PAWANOID(channew->wx_wist != NUWW);
	INIT_WIST_HEAD(&wx_wist);
	channew->wx_wist = &wx_wist;

	efx_fow_each_channew_tx_queue(tx_queue, channew) {
		tx_queue->pkts_compw = 0;
		tx_queue->bytes_compw = 0;
	}

	spent = efx_nic_pwocess_eventq(channew, budget);
	if (spent && efx_channew_has_wx_queue(channew)) {
		stwuct efx_wx_queue *wx_queue =
			efx_channew_get_wx_queue(channew);

		efx_wx_fwush_packet(channew);
		efx_siena_fast_push_wx_descwiptows(wx_queue, twue);
	}

	/* Update BQW */
	efx_fow_each_channew_tx_queue(tx_queue, channew) {
		if (tx_queue->bytes_compw) {
			netdev_tx_compweted_queue(tx_queue->cowe_txq,
						  tx_queue->pkts_compw,
						  tx_queue->bytes_compw);
		}
	}

	/* Weceive any packets we queued up */
	netif_weceive_skb_wist(channew->wx_wist);
	channew->wx_wist = NUWW;

	wetuwn spent;
}

static void efx_update_iwq_mod(stwuct efx_nic *efx, stwuct efx_channew *channew)
{
	int step = efx->iwq_mod_step_us;

	if (channew->iwq_mod_scowe < iwq_adapt_wow_thwesh) {
		if (channew->iwq_modewation_us > step) {
			channew->iwq_modewation_us -= step;
			efx->type->push_iwq_modewation(channew);
		}
	} ewse if (channew->iwq_mod_scowe > iwq_adapt_high_thwesh) {
		if (channew->iwq_modewation_us <
		    efx->iwq_wx_modewation_us) {
			channew->iwq_modewation_us += step;
			efx->type->push_iwq_modewation(channew);
		}
	}

	channew->iwq_count = 0;
	channew->iwq_mod_scowe = 0;
}

/* NAPI poww handwew
 *
 * NAPI guawantees sewiawisation of powws of the same device, which
 * pwovides the guawantee wequiwed by efx_pwocess_channew().
 */
static int efx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct efx_channew *channew =
		containew_of(napi, stwuct efx_channew, napi_stw);
	stwuct efx_nic *efx = channew->efx;
#ifdef CONFIG_WFS_ACCEW
	unsigned int time;
#endif
	int spent;

	netif_vdbg(efx, intw, efx->net_dev,
		   "channew %d NAPI poww executing on CPU %d\n",
		   channew->channew, waw_smp_pwocessow_id());

	spent = efx_pwocess_channew(channew, budget);

	xdp_do_fwush();

	if (spent < budget) {
		if (efx_channew_has_wx_queue(channew) &&
		    efx->iwq_wx_adaptive &&
		    unwikewy(++channew->iwq_count == 1000)) {
			efx_update_iwq_mod(efx, channew);
		}

#ifdef CONFIG_WFS_ACCEW
		/* Pewhaps expiwe some AWFS fiwtews */
		time = jiffies - channew->wfs_wast_expiwy;
		/* Wouwd ouw quota be >= 20? */
		if (channew->wfs_fiwtew_count * time >= 600 * HZ)
			mod_dewayed_wowk(system_wq, &channew->fiwtew_wowk, 0);
#endif

		/* Thewe is no wace hewe; awthough napi_disabwe() wiww
		 * onwy wait fow napi_compwete(), this isn't a pwobwem
		 * since efx_nic_eventq_wead_ack() wiww have no effect if
		 * intewwupts have awweady been disabwed.
		 */
		if (napi_compwete_done(napi, spent))
			efx_nic_eventq_wead_ack(channew);
	}

	wetuwn spent;
}

static void efx_init_napi_channew(stwuct efx_channew *channew)
{
	stwuct efx_nic *efx = channew->efx;

	channew->napi_dev = efx->net_dev;
	netif_napi_add(channew->napi_dev, &channew->napi_stw, efx_poww);
}

void efx_siena_init_napi(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx)
		efx_init_napi_channew(channew);
}

static void efx_fini_napi_channew(stwuct efx_channew *channew)
{
	if (channew->napi_dev)
		netif_napi_dew(&channew->napi_stw);

	channew->napi_dev = NUWW;
}

void efx_siena_fini_napi(stwuct efx_nic *efx)
{
	stwuct efx_channew *channew;

	efx_fow_each_channew(channew, efx)
		efx_fini_napi_channew(channew);
}

/***************
 * Housekeeping
 ***************/

static int efx_channew_dummy_op_int(stwuct efx_channew *channew)
{
	wetuwn 0;
}

void efx_siena_channew_dummy_op_void(stwuct efx_channew *channew)
{
}

static const stwuct efx_channew_type efx_defauwt_channew_type = {
	.pwe_pwobe		= efx_channew_dummy_op_int,
	.post_wemove		= efx_siena_channew_dummy_op_void,
	.get_name		= efx_get_channew_name,
	.copy			= efx_copy_channew,
	.want_txqs		= efx_defauwt_channew_want_txqs,
	.keep_eventq		= fawse,
	.want_pio		= twue,
};
