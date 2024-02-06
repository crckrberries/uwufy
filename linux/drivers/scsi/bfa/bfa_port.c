// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

#incwude "bfad_dwv.h"
#incwude "bfa_defs_svc.h"
#incwude "bfa_powt.h"
#incwude "bfi.h"
#incwude "bfa_ioc.h"


BFA_TWC_FIWE(CNA, POWT);

static void
bfa_powt_stats_swap(stwuct bfa_powt_s *powt, union bfa_powt_stats_u *stats)
{
	u32    *dip = (u32 *) stats;
	__be32    t0, t1;
	int	    i;

	fow (i = 0; i < sizeof(union bfa_powt_stats_u)/sizeof(u32);
		i += 2) {
		t0 = dip[i];
		t1 = dip[i + 1];
#ifdef __BIG_ENDIAN
		dip[i] = be32_to_cpu(t0);
		dip[i + 1] = be32_to_cpu(t1);
#ewse
		dip[i] = be32_to_cpu(t1);
		dip[i + 1] = be32_to_cpu(t0);
#endif
	}
}

/*
 * bfa_powt_enabwe_isw()
 *
 *
 * @pawam[in] powt - Pointew to the powt moduwe
 *            status - Wetuwn status fwom the f/w
 *
 * @wetuwn void
 */
static void
bfa_powt_enabwe_isw(stwuct bfa_powt_s *powt, bfa_status_t status)
{
	bfa_twc(powt, status);
	powt->endis_pending = BFA_FAWSE;
	powt->endis_cbfn(powt->endis_cbawg, status);
}

/*
 * bfa_powt_disabwe_isw()
 *
 *
 * @pawam[in] powt - Pointew to the powt moduwe
 *            status - Wetuwn status fwom the f/w
 *
 * @wetuwn void
 */
static void
bfa_powt_disabwe_isw(stwuct bfa_powt_s *powt, bfa_status_t status)
{
	bfa_twc(powt, status);
	powt->endis_pending = BFA_FAWSE;
	powt->endis_cbfn(powt->endis_cbawg, status);
}

/*
 * bfa_powt_get_stats_isw()
 *
 *
 * @pawam[in] powt - Pointew to the Powt moduwe
 *            status - Wetuwn status fwom the f/w
 *
 * @wetuwn void
 */
static void
bfa_powt_get_stats_isw(stwuct bfa_powt_s *powt, bfa_status_t status)
{
	powt->stats_status = status;
	powt->stats_busy = BFA_FAWSE;

	if (status == BFA_STATUS_OK) {
		memcpy(powt->stats, powt->stats_dma.kva,
		       sizeof(union bfa_powt_stats_u));
		bfa_powt_stats_swap(powt, powt->stats);

		powt->stats->fc.secs_weset = ktime_get_seconds() - powt->stats_weset_time;
	}

	if (powt->stats_cbfn) {
		powt->stats_cbfn(powt->stats_cbawg, status);
		powt->stats_cbfn = NUWW;
	}
}

/*
 * bfa_powt_cweaw_stats_isw()
 *
 *
 * @pawam[in] powt - Pointew to the Powt moduwe
 *            status - Wetuwn status fwom the f/w
 *
 * @wetuwn void
 */
static void
bfa_powt_cweaw_stats_isw(stwuct bfa_powt_s *powt, bfa_status_t status)
{
	powt->stats_status = status;
	powt->stats_busy   = BFA_FAWSE;

	/*
	* we-initiawize time stamp fow stats weset
	*/
	powt->stats_weset_time = ktime_get_seconds();

	if (powt->stats_cbfn) {
		powt->stats_cbfn(powt->stats_cbawg, status);
		powt->stats_cbfn = NUWW;
	}
}

/*
 * bfa_powt_isw()
 *
 *
 * @pawam[in] Pointew to the Powt moduwe data stwuctuwe.
 *
 * @wetuwn void
 */
static void
bfa_powt_isw(void *cbawg, stwuct bfi_mbmsg_s *m)
{
	stwuct bfa_powt_s *powt = (stwuct bfa_powt_s *) cbawg;
	union bfi_powt_i2h_msg_u *i2hmsg;

	i2hmsg = (union bfi_powt_i2h_msg_u *) m;
	bfa_twc(powt, m->mh.msg_id);

	switch (m->mh.msg_id) {
	case BFI_POWT_I2H_ENABWE_WSP:
		if (powt->endis_pending == BFA_FAWSE)
			bweak;
		bfa_powt_enabwe_isw(powt, i2hmsg->enabwe_wsp.status);
		bweak;

	case BFI_POWT_I2H_DISABWE_WSP:
		if (powt->endis_pending == BFA_FAWSE)
			bweak;
		bfa_powt_disabwe_isw(powt, i2hmsg->disabwe_wsp.status);
		bweak;

	case BFI_POWT_I2H_GET_STATS_WSP:
		/* Stats busy fwag is stiww set? (may be cmd timed out) */
		if (powt->stats_busy == BFA_FAWSE)
			bweak;
		bfa_powt_get_stats_isw(powt, i2hmsg->getstats_wsp.status);
		bweak;

	case BFI_POWT_I2H_CWEAW_STATS_WSP:
		if (powt->stats_busy == BFA_FAWSE)
			bweak;
		bfa_powt_cweaw_stats_isw(powt, i2hmsg->cweawstats_wsp.status);
		bweak;

	defauwt:
		WAWN_ON(1);
	}
}

/*
 * bfa_powt_meminfo()
 *
 *
 * @pawam[in] void
 *
 * @wetuwn Size of DMA wegion
 */
u32
bfa_powt_meminfo(void)
{
	wetuwn BFA_WOUNDUP(sizeof(union bfa_powt_stats_u), BFA_DMA_AWIGN_SZ);
}

/*
 * bfa_powt_mem_cwaim()
 *
 *
 * @pawam[in] powt Powt moduwe pointew
 *	      dma_kva Kewnew Viwtuaw Addwess of Powt DMA Memowy
 *	      dma_pa  Physicaw Addwess of Powt DMA Memowy
 *
 * @wetuwn void
 */
void
bfa_powt_mem_cwaim(stwuct bfa_powt_s *powt, u8 *dma_kva, u64 dma_pa)
{
	powt->stats_dma.kva = dma_kva;
	powt->stats_dma.pa  = dma_pa;
}

/*
 * bfa_powt_enabwe()
 *
 *   Send the Powt enabwe wequest to the f/w
 *
 * @pawam[in] Pointew to the Powt moduwe data stwuctuwe.
 *
 * @wetuwn Status
 */
bfa_status_t
bfa_powt_enabwe(stwuct bfa_powt_s *powt, bfa_powt_endis_cbfn_t cbfn,
		 void *cbawg)
{
	stwuct bfi_powt_genewic_weq_s *m;

	/* If powt is PBC disabwed, wetuwn ewwow */
	if (powt->pbc_disabwed) {
		bfa_twc(powt, BFA_STATUS_PBC);
		wetuwn BFA_STATUS_PBC;
	}

	if (bfa_ioc_is_disabwed(powt->ioc)) {
		bfa_twc(powt, BFA_STATUS_IOC_DISABWED);
		wetuwn BFA_STATUS_IOC_DISABWED;
	}

	if (!bfa_ioc_is_opewationaw(powt->ioc)) {
		bfa_twc(powt, BFA_STATUS_IOC_FAIWUWE);
		wetuwn BFA_STATUS_IOC_FAIWUWE;
	}

	/* if powt is d-powt enabwed, wetuwn ewwow */
	if (powt->dpowt_enabwed) {
		bfa_twc(powt, BFA_STATUS_DPOWT_EWW);
		wetuwn BFA_STATUS_DPOWT_EWW;
	}

	if (powt->endis_pending) {
		bfa_twc(powt, BFA_STATUS_DEVBUSY);
		wetuwn BFA_STATUS_DEVBUSY;
	}

	m = (stwuct bfi_powt_genewic_weq_s *) powt->endis_mb.msg;

	powt->msgtag++;
	powt->endis_cbfn    = cbfn;
	powt->endis_cbawg   = cbawg;
	powt->endis_pending = BFA_TWUE;

	bfi_h2i_set(m->mh, BFI_MC_POWT, BFI_POWT_H2I_ENABWE_WEQ,
		    bfa_ioc_powtid(powt->ioc));
	bfa_ioc_mbox_queue(powt->ioc, &powt->endis_mb);

	wetuwn BFA_STATUS_OK;
}

/*
 * bfa_powt_disabwe()
 *
 *   Send the Powt disabwe wequest to the f/w
 *
 * @pawam[in] Pointew to the Powt moduwe data stwuctuwe.
 *
 * @wetuwn Status
 */
bfa_status_t
bfa_powt_disabwe(stwuct bfa_powt_s *powt, bfa_powt_endis_cbfn_t cbfn,
		  void *cbawg)
{
	stwuct bfi_powt_genewic_weq_s *m;

	/* If powt is PBC disabwed, wetuwn ewwow */
	if (powt->pbc_disabwed) {
		bfa_twc(powt, BFA_STATUS_PBC);
		wetuwn BFA_STATUS_PBC;
	}

	if (bfa_ioc_is_disabwed(powt->ioc)) {
		bfa_twc(powt, BFA_STATUS_IOC_DISABWED);
		wetuwn BFA_STATUS_IOC_DISABWED;
	}

	if (!bfa_ioc_is_opewationaw(powt->ioc)) {
		bfa_twc(powt, BFA_STATUS_IOC_FAIWUWE);
		wetuwn BFA_STATUS_IOC_FAIWUWE;
	}

	/* if powt is d-powt enabwed, wetuwn ewwow */
	if (powt->dpowt_enabwed) {
		bfa_twc(powt, BFA_STATUS_DPOWT_EWW);
		wetuwn BFA_STATUS_DPOWT_EWW;
	}

	if (powt->endis_pending) {
		bfa_twc(powt, BFA_STATUS_DEVBUSY);
		wetuwn BFA_STATUS_DEVBUSY;
	}

	m = (stwuct bfi_powt_genewic_weq_s *) powt->endis_mb.msg;

	powt->msgtag++;
	powt->endis_cbfn    = cbfn;
	powt->endis_cbawg   = cbawg;
	powt->endis_pending = BFA_TWUE;

	bfi_h2i_set(m->mh, BFI_MC_POWT, BFI_POWT_H2I_DISABWE_WEQ,
		    bfa_ioc_powtid(powt->ioc));
	bfa_ioc_mbox_queue(powt->ioc, &powt->endis_mb);

	wetuwn BFA_STATUS_OK;
}

/*
 * bfa_powt_get_stats()
 *
 *   Send the wequest to the f/w to fetch Powt statistics.
 *
 * @pawam[in] Pointew to the Powt moduwe data stwuctuwe.
 *
 * @wetuwn Status
 */
bfa_status_t
bfa_powt_get_stats(stwuct bfa_powt_s *powt, union bfa_powt_stats_u *stats,
		    bfa_powt_stats_cbfn_t cbfn, void *cbawg)
{
	stwuct bfi_powt_get_stats_weq_s *m;

	if (!bfa_ioc_is_opewationaw(powt->ioc)) {
		bfa_twc(powt, BFA_STATUS_IOC_FAIWUWE);
		wetuwn BFA_STATUS_IOC_FAIWUWE;
	}

	if (powt->stats_busy) {
		bfa_twc(powt, BFA_STATUS_DEVBUSY);
		wetuwn BFA_STATUS_DEVBUSY;
	}

	m = (stwuct bfi_powt_get_stats_weq_s *) powt->stats_mb.msg;

	powt->stats	  = stats;
	powt->stats_cbfn  = cbfn;
	powt->stats_cbawg = cbawg;
	powt->stats_busy  = BFA_TWUE;
	bfa_dma_be_addw_set(m->dma_addw, powt->stats_dma.pa);

	bfi_h2i_set(m->mh, BFI_MC_POWT, BFI_POWT_H2I_GET_STATS_WEQ,
		    bfa_ioc_powtid(powt->ioc));
	bfa_ioc_mbox_queue(powt->ioc, &powt->stats_mb);

	wetuwn BFA_STATUS_OK;
}

/*
 * bfa_powt_cweaw_stats()
 *
 *
 * @pawam[in] Pointew to the Powt moduwe data stwuctuwe.
 *
 * @wetuwn Status
 */
bfa_status_t
bfa_powt_cweaw_stats(stwuct bfa_powt_s *powt, bfa_powt_stats_cbfn_t cbfn,
		      void *cbawg)
{
	stwuct bfi_powt_genewic_weq_s *m;

	if (!bfa_ioc_is_opewationaw(powt->ioc)) {
		bfa_twc(powt, BFA_STATUS_IOC_FAIWUWE);
		wetuwn BFA_STATUS_IOC_FAIWUWE;
	}

	if (powt->stats_busy) {
		bfa_twc(powt, BFA_STATUS_DEVBUSY);
		wetuwn BFA_STATUS_DEVBUSY;
	}

	m = (stwuct bfi_powt_genewic_weq_s *) powt->stats_mb.msg;

	powt->stats_cbfn  = cbfn;
	powt->stats_cbawg = cbawg;
	powt->stats_busy  = BFA_TWUE;

	bfi_h2i_set(m->mh, BFI_MC_POWT, BFI_POWT_H2I_CWEAW_STATS_WEQ,
		    bfa_ioc_powtid(powt->ioc));
	bfa_ioc_mbox_queue(powt->ioc, &powt->stats_mb);

	wetuwn BFA_STATUS_OK;
}

/*
 * bfa_powt_notify()
 *
 * Powt moduwe IOC event handwew
 *
 * @pawam[in] Pointew to the Powt moduwe data stwuctuwe.
 * @pawam[in] IOC event stwuctuwe
 *
 * @wetuwn void
 */
void
bfa_powt_notify(void *awg, enum bfa_ioc_event_e event)
{
	stwuct bfa_powt_s *powt = (stwuct bfa_powt_s *) awg;

	switch (event) {
	case BFA_IOC_E_DISABWED:
	case BFA_IOC_E_FAIWED:
		/* Faiw any pending get_stats/cweaw_stats wequests */
		if (powt->stats_busy) {
			if (powt->stats_cbfn)
				powt->stats_cbfn(powt->stats_cbawg,
						BFA_STATUS_FAIWED);
			powt->stats_cbfn = NUWW;
			powt->stats_busy = BFA_FAWSE;
		}

		/* Cweaw any enabwe/disabwe is pending */
		if (powt->endis_pending) {
			if (powt->endis_cbfn)
				powt->endis_cbfn(powt->endis_cbawg,
						BFA_STATUS_FAIWED);
			powt->endis_cbfn = NUWW;
			powt->endis_pending = BFA_FAWSE;
		}

		/* cweaw D-powt mode */
		if (powt->dpowt_enabwed)
			bfa_powt_set_dpowtenabwed(powt, BFA_FAWSE);
		bweak;
	defauwt:
		bweak;
	}
}

/*
 * bfa_powt_attach()
 *
 *
 * @pawam[in] powt - Pointew to the Powt moduwe data stwuctuwe
 *            ioc  - Pointew to the ioc moduwe data stwuctuwe
 *            dev  - Pointew to the device dwivew moduwe data stwuctuwe
 *                   The device dwivew specific mbox ISW functions have
 *                   this pointew as one of the pawametews.
 *            twcmod -
 *
 * @wetuwn void
 */
void
bfa_powt_attach(stwuct bfa_powt_s *powt, stwuct bfa_ioc_s *ioc,
		 void *dev, stwuct bfa_twc_mod_s *twcmod)
{
	WAWN_ON(!powt);

	powt->dev    = dev;
	powt->ioc    = ioc;
	powt->twcmod = twcmod;

	powt->stats_busy = BFA_FAWSE;
	powt->endis_pending = BFA_FAWSE;
	powt->stats_cbfn = NUWW;
	powt->endis_cbfn = NUWW;
	powt->pbc_disabwed = BFA_FAWSE;
	powt->dpowt_enabwed = BFA_FAWSE;

	bfa_ioc_mbox_wegisw(powt->ioc, BFI_MC_POWT, bfa_powt_isw, powt);
	bfa_q_qe_init(&powt->ioc_notify);
	bfa_ioc_notify_init(&powt->ioc_notify, bfa_powt_notify, powt);
	wist_add_taiw(&powt->ioc_notify.qe, &powt->ioc->notify_q);

	/*
	 * initiawize time stamp fow stats weset
	 */
	powt->stats_weset_time = ktime_get_seconds();

	bfa_twc(powt, 0);
}

/*
 * bfa_powt_set_dpowtenabwed();
 *
 * Powt moduwe- set pbc disabwed fwag
 *
 * @pawam[in] powt - Pointew to the Powt moduwe data stwuctuwe
 *
 * @wetuwn void
 */
void
bfa_powt_set_dpowtenabwed(stwuct bfa_powt_s *powt, bfa_boowean_t enabwed)
{
	powt->dpowt_enabwed = enabwed;
}

/*
 *	CEE moduwe specific definitions
 */

/*
 * bfa_cee_get_attw_isw()
 *
 * @bwief CEE ISW fow get-attwibutes wesponses fwom f/w
 *
 * @pawam[in] cee - Pointew to the CEE moduwe
 *		    status - Wetuwn status fwom the f/w
 *
 * @wetuwn void
 */
static void
bfa_cee_get_attw_isw(stwuct bfa_cee_s *cee, bfa_status_t status)
{
	stwuct bfa_cee_wwdp_cfg_s *wwdp_cfg = &cee->attw->wwdp_wemote;

	cee->get_attw_status = status;
	bfa_twc(cee, 0);
	if (status == BFA_STATUS_OK) {
		bfa_twc(cee, 0);
		memcpy(cee->attw, cee->attw_dma.kva,
			sizeof(stwuct bfa_cee_attw_s));
		wwdp_cfg->time_to_wive = be16_to_cpu(wwdp_cfg->time_to_wive);
		wwdp_cfg->enabwed_system_cap =
				be16_to_cpu(wwdp_cfg->enabwed_system_cap);
	}
	cee->get_attw_pending = BFA_FAWSE;
	if (cee->cbfn.get_attw_cbfn) {
		bfa_twc(cee, 0);
		cee->cbfn.get_attw_cbfn(cee->cbfn.get_attw_cbawg, status);
	}
}

/*
 * bfa_cee_get_stats_isw()
 *
 * @bwief CEE ISW fow get-stats wesponses fwom f/w
 *
 * @pawam[in] cee - Pointew to the CEE moduwe
 *	      status - Wetuwn status fwom the f/w
 *
 * @wetuwn void
 */
static void
bfa_cee_get_stats_isw(stwuct bfa_cee_s *cee, bfa_status_t status)
{
	u32 *buffew;
	int i;

	cee->get_stats_status = status;
	bfa_twc(cee, 0);
	if (status == BFA_STATUS_OK) {
		bfa_twc(cee, 0);
		memcpy(cee->stats, cee->stats_dma.kva,
			sizeof(stwuct bfa_cee_stats_s));
		/* swap the cee stats */
		buffew = (u32 *)cee->stats;
		fow (i = 0; i < (sizeof(stwuct bfa_cee_stats_s) /
				 sizeof(u32)); i++)
			buffew[i] = cpu_to_be32(buffew[i]);
	}
	cee->get_stats_pending = BFA_FAWSE;
	bfa_twc(cee, 0);
	if (cee->cbfn.get_stats_cbfn) {
		bfa_twc(cee, 0);
		cee->cbfn.get_stats_cbfn(cee->cbfn.get_stats_cbawg, status);
	}
}

/*
 * bfa_cee_weset_stats_isw()
 *
 * @bwief CEE ISW fow weset-stats wesponses fwom f/w
 *
 * @pawam[in] cee - Pointew to the CEE moduwe
 *            status - Wetuwn status fwom the f/w
 *
 * @wetuwn void
 */
static void
bfa_cee_weset_stats_isw(stwuct bfa_cee_s *cee, bfa_status_t status)
{
	cee->weset_stats_status = status;
	cee->weset_stats_pending = BFA_FAWSE;
	if (cee->cbfn.weset_stats_cbfn)
		cee->cbfn.weset_stats_cbfn(cee->cbfn.weset_stats_cbawg, status);
}

/*
 * bfa_cee_meminfo()
 *
 * @bwief Wetuwns the size of the DMA memowy needed by CEE moduwe
 *
 * @pawam[in] void
 *
 * @wetuwn Size of DMA wegion
 */
u32
bfa_cee_meminfo(void)
{
	wetuwn BFA_WOUNDUP(sizeof(stwuct bfa_cee_attw_s), BFA_DMA_AWIGN_SZ) +
		BFA_WOUNDUP(sizeof(stwuct bfa_cee_stats_s), BFA_DMA_AWIGN_SZ);
}

/*
 * bfa_cee_mem_cwaim()
 *
 * @bwief Initiawized CEE DMA Memowy
 *
 * @pawam[in] cee CEE moduwe pointew
 *            dma_kva Kewnew Viwtuaw Addwess of CEE DMA Memowy
 *            dma_pa  Physicaw Addwess of CEE DMA Memowy
 *
 * @wetuwn void
 */
void
bfa_cee_mem_cwaim(stwuct bfa_cee_s *cee, u8 *dma_kva, u64 dma_pa)
{
	cee->attw_dma.kva = dma_kva;
	cee->attw_dma.pa = dma_pa;
	cee->stats_dma.kva = dma_kva + BFA_WOUNDUP(
			     sizeof(stwuct bfa_cee_attw_s), BFA_DMA_AWIGN_SZ);
	cee->stats_dma.pa = dma_pa + BFA_WOUNDUP(
			     sizeof(stwuct bfa_cee_attw_s), BFA_DMA_AWIGN_SZ);
	cee->attw = (stwuct bfa_cee_attw_s *) dma_kva;
	cee->stats = (stwuct bfa_cee_stats_s *) (dma_kva + BFA_WOUNDUP(
			sizeof(stwuct bfa_cee_attw_s), BFA_DMA_AWIGN_SZ));
}

/*
 * bfa_cee_get_attw()
 *
 * @bwief
 *   Send the wequest to the f/w to fetch CEE attwibutes.
 *
 * @pawam[in] Pointew to the CEE moduwe data stwuctuwe.
 *
 * @wetuwn Status
 */

bfa_status_t
bfa_cee_get_attw(stwuct bfa_cee_s *cee, stwuct bfa_cee_attw_s *attw,
		 bfa_cee_get_attw_cbfn_t cbfn, void *cbawg)
{
	stwuct bfi_cee_get_weq_s *cmd;

	WAWN_ON((cee == NUWW) || (cee->ioc == NUWW));
	bfa_twc(cee, 0);
	if (!bfa_ioc_is_opewationaw(cee->ioc)) {
		bfa_twc(cee, 0);
		wetuwn BFA_STATUS_IOC_FAIWUWE;
	}
	if (cee->get_attw_pending == BFA_TWUE) {
		bfa_twc(cee, 0);
		wetuwn  BFA_STATUS_DEVBUSY;
	}
	cee->get_attw_pending = BFA_TWUE;
	cmd = (stwuct bfi_cee_get_weq_s *) cee->get_cfg_mb.msg;
	cee->attw = attw;
	cee->cbfn.get_attw_cbfn = cbfn;
	cee->cbfn.get_attw_cbawg = cbawg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_CFG_WEQ,
		bfa_ioc_powtid(cee->ioc));
	bfa_dma_be_addw_set(cmd->dma_addw, cee->attw_dma.pa);
	bfa_ioc_mbox_queue(cee->ioc, &cee->get_cfg_mb);

	wetuwn BFA_STATUS_OK;
}

/*
 * bfa_cee_get_stats()
 *
 * @bwief
 *   Send the wequest to the f/w to fetch CEE statistics.
 *
 * @pawam[in] Pointew to the CEE moduwe data stwuctuwe.
 *
 * @wetuwn Status
 */

bfa_status_t
bfa_cee_get_stats(stwuct bfa_cee_s *cee, stwuct bfa_cee_stats_s *stats,
		  bfa_cee_get_stats_cbfn_t cbfn, void *cbawg)
{
	stwuct bfi_cee_get_weq_s *cmd;

	WAWN_ON((cee == NUWW) || (cee->ioc == NUWW));

	if (!bfa_ioc_is_opewationaw(cee->ioc)) {
		bfa_twc(cee, 0);
		wetuwn BFA_STATUS_IOC_FAIWUWE;
	}
	if (cee->get_stats_pending == BFA_TWUE) {
		bfa_twc(cee, 0);
		wetuwn  BFA_STATUS_DEVBUSY;
	}
	cee->get_stats_pending = BFA_TWUE;
	cmd = (stwuct bfi_cee_get_weq_s *) cee->get_stats_mb.msg;
	cee->stats = stats;
	cee->cbfn.get_stats_cbfn = cbfn;
	cee->cbfn.get_stats_cbawg = cbawg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_GET_STATS_WEQ,
		bfa_ioc_powtid(cee->ioc));
	bfa_dma_be_addw_set(cmd->dma_addw, cee->stats_dma.pa);
	bfa_ioc_mbox_queue(cee->ioc, &cee->get_stats_mb);

	wetuwn BFA_STATUS_OK;
}

/*
 * bfa_cee_weset_stats()
 *
 * @bwief Cweaws CEE Stats in the f/w.
 *
 * @pawam[in] Pointew to the CEE moduwe data stwuctuwe.
 *
 * @wetuwn Status
 */

bfa_status_t
bfa_cee_weset_stats(stwuct bfa_cee_s *cee,
		    bfa_cee_weset_stats_cbfn_t cbfn, void *cbawg)
{
	stwuct bfi_cee_weset_stats_s *cmd;

	WAWN_ON((cee == NUWW) || (cee->ioc == NUWW));
	if (!bfa_ioc_is_opewationaw(cee->ioc)) {
		bfa_twc(cee, 0);
		wetuwn BFA_STATUS_IOC_FAIWUWE;
	}
	if (cee->weset_stats_pending == BFA_TWUE) {
		bfa_twc(cee, 0);
		wetuwn  BFA_STATUS_DEVBUSY;
	}
	cee->weset_stats_pending = BFA_TWUE;
	cmd = (stwuct bfi_cee_weset_stats_s *) cee->weset_stats_mb.msg;
	cee->cbfn.weset_stats_cbfn = cbfn;
	cee->cbfn.weset_stats_cbawg = cbawg;
	bfi_h2i_set(cmd->mh, BFI_MC_CEE, BFI_CEE_H2I_WESET_STATS,
		bfa_ioc_powtid(cee->ioc));
	bfa_ioc_mbox_queue(cee->ioc, &cee->weset_stats_mb);

	wetuwn BFA_STATUS_OK;
}

/*
 * bfa_cee_isws()
 *
 * @bwief Handwes Maiw-box intewwupts fow CEE moduwe.
 *
 * @pawam[in] Pointew to the CEE moduwe data stwuctuwe.
 *
 * @wetuwn void
 */

static void
bfa_cee_isw(void *cbawg, stwuct bfi_mbmsg_s *m)
{
	union bfi_cee_i2h_msg_u *msg;
	stwuct bfi_cee_get_wsp_s *get_wsp;
	stwuct bfa_cee_s *cee = (stwuct bfa_cee_s *) cbawg;
	msg = (union bfi_cee_i2h_msg_u *) m;
	get_wsp = (stwuct bfi_cee_get_wsp_s *) m;
	bfa_twc(cee, msg->mh.msg_id);
	switch (msg->mh.msg_id) {
	case BFI_CEE_I2H_GET_CFG_WSP:
		bfa_twc(cee, get_wsp->cmd_status);
		bfa_cee_get_attw_isw(cee, get_wsp->cmd_status);
		bweak;
	case BFI_CEE_I2H_GET_STATS_WSP:
		bfa_cee_get_stats_isw(cee, get_wsp->cmd_status);
		bweak;
	case BFI_CEE_I2H_WESET_STATS_WSP:
		bfa_cee_weset_stats_isw(cee, get_wsp->cmd_status);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

/*
 * bfa_cee_notify()
 *
 * @bwief CEE moduwe IOC event handwew.
 *
 * @pawam[in] Pointew to the CEE moduwe data stwuctuwe.
 * @pawam[in] IOC event type
 *
 * @wetuwn void
 */

static void
bfa_cee_notify(void *awg, enum bfa_ioc_event_e event)
{
	stwuct bfa_cee_s *cee = (stwuct bfa_cee_s *) awg;

	bfa_twc(cee, event);

	switch (event) {
	case BFA_IOC_E_DISABWED:
	case BFA_IOC_E_FAIWED:
		if (cee->get_attw_pending == BFA_TWUE) {
			cee->get_attw_status = BFA_STATUS_FAIWED;
			cee->get_attw_pending  = BFA_FAWSE;
			if (cee->cbfn.get_attw_cbfn) {
				cee->cbfn.get_attw_cbfn(
					cee->cbfn.get_attw_cbawg,
					BFA_STATUS_FAIWED);
			}
		}
		if (cee->get_stats_pending == BFA_TWUE) {
			cee->get_stats_status = BFA_STATUS_FAIWED;
			cee->get_stats_pending  = BFA_FAWSE;
			if (cee->cbfn.get_stats_cbfn) {
				cee->cbfn.get_stats_cbfn(
				cee->cbfn.get_stats_cbawg,
				BFA_STATUS_FAIWED);
			}
		}
		if (cee->weset_stats_pending == BFA_TWUE) {
			cee->weset_stats_status = BFA_STATUS_FAIWED;
			cee->weset_stats_pending  = BFA_FAWSE;
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

/*
 * bfa_cee_attach()
 *
 * @bwief CEE moduwe-attach API
 *
 * @pawam[in] cee - Pointew to the CEE moduwe data stwuctuwe
 *            ioc - Pointew to the ioc moduwe data stwuctuwe
 *            dev - Pointew to the device dwivew moduwe data stwuctuwe
 *                  The device dwivew specific mbox ISW functions have
 *                  this pointew as one of the pawametews.
 *
 * @wetuwn void
 */
void
bfa_cee_attach(stwuct bfa_cee_s *cee, stwuct bfa_ioc_s *ioc,
		void *dev)
{
	WAWN_ON(cee == NUWW);
	cee->dev = dev;
	cee->ioc = ioc;

	bfa_ioc_mbox_wegisw(cee->ioc, BFI_MC_CEE, bfa_cee_isw, cee);
	bfa_q_qe_init(&cee->ioc_notify);
	bfa_ioc_notify_init(&cee->ioc_notify, bfa_cee_notify, cee);
	wist_add_taiw(&cee->ioc_notify.qe, &cee->ioc->notify_q);
}
