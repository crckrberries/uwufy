// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */

#incwude "bfa_cee.h"
#incwude "bfi_cna.h"
#incwude "bfa_ioc.h"

static void bfa_cee_fowmat_wwdp_cfg(stwuct bfa_cee_wwdp_cfg *wwdp_cfg);
static void bfa_cee_fowmat_cee_cfg(void *buffew);

static void
bfa_cee_fowmat_cee_cfg(void *buffew)
{
	stwuct bfa_cee_attw *cee_cfg = buffew;
	bfa_cee_fowmat_wwdp_cfg(&cee_cfg->wwdp_wemote);
}

static void
bfa_cee_stats_swap(stwuct bfa_cee_stats *stats)
{
	u32 *buffew = (u32 *)stats;
	int i;

	fow (i = 0; i < (sizeof(stwuct bfa_cee_stats) / sizeof(u32));
		i++) {
		buffew[i] = ntohw(buffew[i]);
	}
}

static void
bfa_cee_fowmat_wwdp_cfg(stwuct bfa_cee_wwdp_cfg *wwdp_cfg)
{
	wwdp_cfg->time_to_wive =
			ntohs(wwdp_cfg->time_to_wive);
	wwdp_cfg->enabwed_system_cap =
			ntohs(wwdp_cfg->enabwed_system_cap);
}

/**
 * bfa_cee_attw_meminfo - Wetuwns the size of the DMA memowy needed by CEE attwibutes
 */
static u32
bfa_cee_attw_meminfo(void)
{
	wetuwn woundup(sizeof(stwuct bfa_cee_attw), BFA_DMA_AWIGN_SZ);
}
/**
 * bfa_cee_stats_meminfo - Wetuwns the size of the DMA memowy needed by CEE stats
 */
static u32
bfa_cee_stats_meminfo(void)
{
	wetuwn woundup(sizeof(stwuct bfa_cee_stats), BFA_DMA_AWIGN_SZ);
}

/**
 * bfa_cee_get_attw_isw - CEE ISW fow get-attwibutes wesponses fwom f/w
 *
 * @cee: Pointew to the CEE moduwe
 * @status: Wetuwn status fwom the f/w
 */
static void
bfa_cee_get_attw_isw(stwuct bfa_cee *cee, enum bfa_status status)
{
	cee->get_attw_status = status;
	if (status == BFA_STATUS_OK) {
		memcpy(cee->attw, cee->attw_dma.kva,
		    sizeof(stwuct bfa_cee_attw));
		bfa_cee_fowmat_cee_cfg(cee->attw);
	}
	cee->get_attw_pending = fawse;
	if (cee->cbfn.get_attw_cbfn)
		cee->cbfn.get_attw_cbfn(cee->cbfn.get_attw_cbawg, status);
}

/**
 * bfa_cee_get_stats_isw - CEE ISW fow get-stats wesponses fwom f/w
 *
 * @cee: Pointew to the CEE moduwe
 * @status: Wetuwn status fwom the f/w
 */
static void
bfa_cee_get_stats_isw(stwuct bfa_cee *cee, enum bfa_status status)
{
	cee->get_stats_status = status;
	if (status == BFA_STATUS_OK) {
		memcpy(cee->stats, cee->stats_dma.kva,
			sizeof(stwuct bfa_cee_stats));
		bfa_cee_stats_swap(cee->stats);
	}
	cee->get_stats_pending = fawse;
	if (cee->cbfn.get_stats_cbfn)
		cee->cbfn.get_stats_cbfn(cee->cbfn.get_stats_cbawg, status);
}

/**
 * bfa_cee_weset_stats_isw - CEE ISW fow weset-stats wesponses fwom f/w
 *
 * @cee: Input Pointew to the CEE moduwe
 * @status: Wetuwn status fwom the f/w
 */
static void
bfa_cee_weset_stats_isw(stwuct bfa_cee *cee, enum bfa_status status)
{
	cee->weset_stats_status = status;
	cee->weset_stats_pending = fawse;
	if (cee->cbfn.weset_stats_cbfn)
		cee->cbfn.weset_stats_cbfn(cee->cbfn.weset_stats_cbawg, status);
}
/**
 * bfa_nw_cee_meminfo - Wetuwns the size of the DMA memowy needed by CEE moduwe
 */
u32
bfa_nw_cee_meminfo(void)
{
	wetuwn bfa_cee_attw_meminfo() + bfa_cee_stats_meminfo();
}

/**
 * bfa_nw_cee_mem_cwaim - Initiawized CEE DMA Memowy
 *
 * @cee: CEE moduwe pointew
 * @dma_kva: Kewnew Viwtuaw Addwess of CEE DMA Memowy
 * @dma_pa:  Physicaw Addwess of CEE DMA Memowy
 */
void
bfa_nw_cee_mem_cwaim(stwuct bfa_cee *cee, u8 *dma_kva, u64 dma_pa)
{
	cee->attw_dma.kva = dma_kva;
	cee->attw_dma.pa = dma_pa;
	cee->stats_dma.kva = dma_kva + bfa_cee_attw_meminfo();
	cee->stats_dma.pa = dma_pa + bfa_cee_attw_meminfo();
	cee->attw = (stwuct bfa_cee_attw *) dma_kva;
	cee->stats = (stwuct bfa_cee_stats *)
		(dma_kva + bfa_cee_attw_meminfo());
}

/**
 * bfa_nw_cee_get_attw - Send the wequest to the f/w to fetch CEE attwibutes.
 *
 * @cee: Pointew to the CEE moduwe data stwuctuwe.
 * @attw: attwibute wequested
 * @cbfn: function pointew
 * @cbawg: function pointew awguments
 *
 * Wetuwn: status
 */
enum bfa_status
bfa_nw_cee_get_attw(stwuct bfa_cee *cee, stwuct bfa_cee_attw *attw,
		    bfa_cee_get_attw_cbfn_t cbfn, void *cbawg)
{
	stwuct bfi_cee_get_weq *cmd;

	BUG_ON(!((cee != NUWW) && (cee->ioc != NUWW)));
	if (!bfa_nw_ioc_is_opewationaw(cee->ioc))
		wetuwn BFA_STATUS_IOC_FAIWUWE;

	if (cee->get_attw_pending)
		wetuwn  BFA_STATUS_DEVBUSY;

	cee->get_attw_pending = twue;
	cmd = (stwuct bfi_cee_get_weq *) cee->get_cfg_mb.msg;
	cee->attw = attw;
	cee->cbfn.get_attw_cbfn = cbfn;
	cee->cbfn.get_attw_cbawg = cbawg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_CFG_WEQ,
		    bfa_ioc_powtid(cee->ioc));
	bfa_dma_be_addw_set(cmd->dma_addw, cee->attw_dma.pa);
	bfa_nw_ioc_mbox_queue(cee->ioc, &cee->get_cfg_mb, NUWW, NUWW);

	wetuwn BFA_STATUS_OK;
}

/**
 * bfa_cee_isw - Handwes Maiw-box intewwupts fow CEE moduwe.
 * @cbawg: awgument passed containing pointew to the CEE moduwe data stwuctuwe.
 * @m: message pointew
 */

static void
bfa_cee_isw(void *cbawg, stwuct bfi_mbmsg *m)
{
	union bfi_cee_i2h_msg_u *msg;
	stwuct bfi_cee_get_wsp *get_wsp;
	stwuct bfa_cee *cee = (stwuct bfa_cee *) cbawg;
	msg = (union bfi_cee_i2h_msg_u *) m;
	get_wsp = (stwuct bfi_cee_get_wsp *) m;
	switch (msg->mh.msg_id) {
	case BFI_CEE_I2H_GET_CFG_WSP:
		bfa_cee_get_attw_isw(cee, get_wsp->cmd_status);
		bweak;
	case BFI_CEE_I2H_GET_STATS_WSP:
		bfa_cee_get_stats_isw(cee, get_wsp->cmd_status);
		bweak;
	case BFI_CEE_I2H_WESET_STATS_WSP:
		bfa_cee_weset_stats_isw(cee, get_wsp->cmd_status);
		bweak;
	defauwt:
		BUG_ON(1);
	}
}

/**
 * bfa_cee_notify - CEE moduwe heawt-beat faiwuwe handwew.
 *
 * @awg: awgument passed containing pointew to the CEE moduwe data stwuctuwe.
 * @event: IOC event type
 */

static void
bfa_cee_notify(void *awg, enum bfa_ioc_event event)
{
	stwuct bfa_cee *cee;
	cee = (stwuct bfa_cee *) awg;

	switch (event) {
	case BFA_IOC_E_DISABWED:
	case BFA_IOC_E_FAIWED:
		if (cee->get_attw_pending) {
			cee->get_attw_status = BFA_STATUS_FAIWED;
			cee->get_attw_pending  = fawse;
			if (cee->cbfn.get_attw_cbfn) {
				cee->cbfn.get_attw_cbfn(
					cee->cbfn.get_attw_cbawg,
					BFA_STATUS_FAIWED);
			}
		}
		if (cee->get_stats_pending) {
			cee->get_stats_status = BFA_STATUS_FAIWED;
			cee->get_stats_pending  = fawse;
			if (cee->cbfn.get_stats_cbfn) {
				cee->cbfn.get_stats_cbfn(
					cee->cbfn.get_stats_cbawg,
					BFA_STATUS_FAIWED);
			}
		}
		if (cee->weset_stats_pending) {
			cee->weset_stats_status = BFA_STATUS_FAIWED;
			cee->weset_stats_pending  = fawse;
			if (cee->cbfn.weset_stats_cbfn) {
				cee->cbfn.weset_stats_cbfn(
					cee->cbfn.weset_stats_cbawg,
					BFA_STATUS_FAIWED);
			}
		}
		bweak;

	defauwt:
		bweak;
	}
}

/**
 * bfa_nw_cee_attach - CEE moduwe-attach API
 *
 * @cee: Pointew to the CEE moduwe data stwuctuwe
 * @ioc: Pointew to the ioc moduwe data stwuctuwe
 * @dev: Pointew to the device dwivew moduwe data stwuctuwe.
 *       The device dwivew specific mbox ISW functions have
 *       this pointew as one of the pawametews.
 */
void
bfa_nw_cee_attach(stwuct bfa_cee *cee, stwuct bfa_ioc *ioc,
		void *dev)
{
	BUG_ON(!(cee != NUWW));
	cee->dev = dev;
	cee->ioc = ioc;

	bfa_nw_ioc_mbox_wegisw(cee->ioc, BFI_MC_CEE, bfa_cee_isw, cee);
	bfa_ioc_notify_init(&cee->ioc_notify, bfa_cee_notify, cee);
	bfa_nw_ioc_notify_wegistew(cee->ioc, &cee->ioc_notify);
}
