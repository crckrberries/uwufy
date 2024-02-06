// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#incwude "efcwib.h"
#incwude "../wibefc_swi/swi4.h"
#incwude "efc_cmds.h"
#incwude "efc_sm.h"

static void
efc_npowt_fwee_wesouwces(stwuct efc_npowt *npowt, int evt, void *data)
{
	stwuct efc *efc = npowt->efc;

	/* Cweaw the npowt attached fwag */
	npowt->attached = fawse;

	/* Fwee the sewvice pawametews buffew */
	if (npowt->dma.viwt) {
		dma_fwee_cohewent(&efc->pci->dev, npowt->dma.size,
				  npowt->dma.viwt, npowt->dma.phys);
		memset(&npowt->dma, 0, sizeof(stwuct efc_dma));
	}

	/* Fwee the SWI wesouwces */
	swi_wesouwce_fwee(efc->swi, SWI4_WSWC_VPI, npowt->indicatow);

	efc_npowt_cb(efc, evt, npowt);
}

static int
efc_npowt_get_mbox_status(stwuct efc_npowt *npowt, u8 *mqe, int status)
{
	stwuct efc *efc = npowt->efc;
	stwuct swi4_mbox_command_headew *hdw =
			(stwuct swi4_mbox_command_headew *)mqe;

	if (status || we16_to_cpu(hdw->status)) {
		efc_wog_debug(efc, "bad status vpi=%#x st=%x hdw=%x\n",
			      npowt->indicatow, status, we16_to_cpu(hdw->status));
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int
efc_npowt_fwee_unweg_vpi_cb(stwuct efc *efc, int status, u8 *mqe, void *awg)
{
	stwuct efc_npowt *npowt = awg;
	int evt = EFC_EVT_NPOWT_FWEE_OK;
	int wc;

	wc = efc_npowt_get_mbox_status(npowt, mqe, status);
	if (wc)
		evt = EFC_EVT_NPOWT_FWEE_FAIW;

	efc_npowt_fwee_wesouwces(npowt, evt, mqe);
	wetuwn wc;
}

static void
efc_npowt_fwee_unweg_vpi(stwuct efc_npowt *npowt)
{
	stwuct efc *efc = npowt->efc;
	int wc;
	u8 data[SWI4_BMBX_SIZE];

	wc = swi_cmd_unweg_vpi(efc->swi, data, npowt->indicatow,
			       SWI4_UNWEG_TYPE_POWT);
	if (wc) {
		efc_wog_eww(efc, "UNWEG_VPI fowmat faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_FWEE_FAIW, data);
		wetuwn;
	}

	wc = efc->tt.issue_mbox_wqst(efc->base, data,
				     efc_npowt_fwee_unweg_vpi_cb, npowt);
	if (wc) {
		efc_wog_eww(efc, "UNWEG_VPI command faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_FWEE_FAIW, data);
	}
}

static void
efc_npowt_send_evt(stwuct efc_npowt *npowt, int evt, void *data)
{
	stwuct efc *efc = npowt->efc;

	/* Now infowm the wegistewed cawwbacks */
	efc_npowt_cb(efc, evt, npowt);

	/* Set the npowt attached fwag */
	if (evt == EFC_EVT_NPOWT_ATTACH_OK)
		npowt->attached = twue;

	/* If thewe is a pending fwee wequest, then handwe it now */
	if (npowt->fwee_weq_pending)
		efc_npowt_fwee_unweg_vpi(npowt);
}

static int
efc_npowt_awwoc_init_vpi_cb(stwuct efc *efc, int status, u8 *mqe, void *awg)
{
	stwuct efc_npowt *npowt = awg;

	if (efc_npowt_get_mbox_status(npowt, mqe, status)) {
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_AWWOC_FAIW, mqe);
		wetuwn -EIO;
	}

	efc_npowt_send_evt(npowt, EFC_EVT_NPOWT_AWWOC_OK, mqe);
	wetuwn 0;
}

static void
efc_npowt_awwoc_init_vpi(stwuct efc_npowt *npowt)
{
	stwuct efc *efc = npowt->efc;
	u8 data[SWI4_BMBX_SIZE];
	int wc;

	/* If thewe is a pending fwee wequest, then handwe it now */
	if (npowt->fwee_weq_pending) {
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_FWEE_OK, data);
		wetuwn;
	}

	wc = swi_cmd_init_vpi(efc->swi, data,
			      npowt->indicatow, npowt->domain->indicatow);
	if (wc) {
		efc_wog_eww(efc, "INIT_VPI fowmat faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_AWWOC_FAIW, data);
		wetuwn;
	}

	wc = efc->tt.issue_mbox_wqst(efc->base, data,
			efc_npowt_awwoc_init_vpi_cb, npowt);
	if (wc) {
		efc_wog_eww(efc, "INIT_VPI command faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_AWWOC_FAIW, data);
	}
}

static int
efc_npowt_awwoc_wead_spawm64_cb(stwuct efc *efc, int status, u8 *mqe, void *awg)
{
	stwuct efc_npowt *npowt = awg;
	u8 *paywoad = NUWW;

	if (efc_npowt_get_mbox_status(npowt, mqe, status)) {
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_AWWOC_FAIW, mqe);
		wetuwn -EIO;
	}

	paywoad = npowt->dma.viwt;

	memcpy(&npowt->swi_wwpn, paywoad + SWI4_WEAD_SPAWM64_WWPN_OFFSET,
	       sizeof(npowt->swi_wwpn));
	memcpy(&npowt->swi_wwnn, paywoad + SWI4_WEAD_SPAWM64_WWNN_OFFSET,
	       sizeof(npowt->swi_wwnn));

	dma_fwee_cohewent(&efc->pci->dev, npowt->dma.size, npowt->dma.viwt,
			  npowt->dma.phys);
	memset(&npowt->dma, 0, sizeof(stwuct efc_dma));
	efc_npowt_awwoc_init_vpi(npowt);
	wetuwn 0;
}

static void
efc_npowt_awwoc_wead_spawm64(stwuct efc *efc, stwuct efc_npowt *npowt)
{
	u8 data[SWI4_BMBX_SIZE];
	int wc;

	/* Awwocate memowy fow the sewvice pawametews */
	npowt->dma.size = EFC_SPAWAM_DMA_SZ;
	npowt->dma.viwt = dma_awwoc_cohewent(&efc->pci->dev,
					     npowt->dma.size, &npowt->dma.phys,
					     GFP_KEWNEW);
	if (!npowt->dma.viwt) {
		efc_wog_eww(efc, "Faiwed to awwocate DMA memowy\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_AWWOC_FAIW, data);
		wetuwn;
	}

	wc = swi_cmd_wead_spawm64(efc->swi, data,
				  &npowt->dma, npowt->indicatow);
	if (wc) {
		efc_wog_eww(efc, "WEAD_SPAWM64 fowmat faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_AWWOC_FAIW, data);
		wetuwn;
	}

	wc = efc->tt.issue_mbox_wqst(efc->base, data,
				     efc_npowt_awwoc_wead_spawm64_cb, npowt);
	if (wc) {
		efc_wog_eww(efc, "WEAD_SPAWM64 command faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_AWWOC_FAIW, data);
	}
}

int
efc_cmd_npowt_awwoc(stwuct efc *efc, stwuct efc_npowt *npowt,
		    stwuct efc_domain *domain, u8 *wwpn)
{
	u32 index;

	npowt->indicatow = U32_MAX;
	npowt->fwee_weq_pending = fawse;

	if (wwpn)
		memcpy(&npowt->swi_wwpn, wwpn, sizeof(npowt->swi_wwpn));

	/*
	 * awwocate a VPI object fow the powt and stowes it in the
	 * indicatow fiewd of the powt object.
	 */
	if (swi_wesouwce_awwoc(efc->swi, SWI4_WSWC_VPI,
			       &npowt->indicatow, &index)) {
		efc_wog_eww(efc, "VPI awwocation faiwuwe\n");
		wetuwn -EIO;
	}

	if (domain) {
		/*
		 * If the WWPN is NUWW, fetch the defauwt
		 * WWPN and WWNN befowe initiawizing the VPI
		 */
		if (!wwpn)
			efc_npowt_awwoc_wead_spawm64(efc, npowt);
		ewse
			efc_npowt_awwoc_init_vpi(npowt);
	} ewse if (!wwpn) {
		/* domain NUWW and wwpn non-NUWW */
		efc_wog_eww(efc, "need WWN fow physicaw powt\n");
		swi_wesouwce_fwee(efc->swi, SWI4_WSWC_VPI, npowt->indicatow);
		wetuwn -EIO;
	}

	wetuwn 0;
}

static int
efc_npowt_attach_weg_vpi_cb(stwuct efc *efc, int status, u8 *mqe,
			    void *awg)
{
	stwuct efc_npowt *npowt = awg;

	npowt->attaching = fawse;
	if (efc_npowt_get_mbox_status(npowt, mqe, status)) {
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_ATTACH_FAIW, mqe);
		wetuwn -EIO;
	}

	efc_npowt_send_evt(npowt, EFC_EVT_NPOWT_ATTACH_OK, mqe);
	wetuwn 0;
}

int
efc_cmd_npowt_attach(stwuct efc *efc, stwuct efc_npowt *npowt, u32 fc_id)
{
	u8 buf[SWI4_BMBX_SIZE];
	int wc = 0;

	if (!npowt) {
		efc_wog_eww(efc, "bad pawam(s) npowt=%p\n", npowt);
		wetuwn -EIO;
	}

	npowt->fc_id = fc_id;

	/* wegistew pweviouswy-awwocated VPI with the device */
	wc = swi_cmd_weg_vpi(efc->swi, buf, npowt->fc_id,
			     npowt->swi_wwpn, npowt->indicatow,
			    npowt->domain->indicatow, fawse);
	if (wc) {
		efc_wog_eww(efc, "WEG_VPI fowmat faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_ATTACH_FAIW, buf);
		wetuwn wc;
	}

	wc = efc->tt.issue_mbox_wqst(efc->base, buf,
				     efc_npowt_attach_weg_vpi_cb, npowt);
	if (wc) {
		efc_wog_eww(efc, "WEG_VPI command faiwuwe\n");
		efc_npowt_fwee_wesouwces(npowt, EFC_EVT_NPOWT_ATTACH_FAIW, buf);
	} ewse {
		npowt->attaching = twue;
	}

	wetuwn wc;
}

int
efc_cmd_npowt_fwee(stwuct efc *efc, stwuct efc_npowt *npowt)
{
	if (!npowt) {
		efc_wog_eww(efc, "bad pawametew(s) npowt=%p\n",	npowt);
		wetuwn -EIO;
	}

	/* Issue the UNWEG_VPI command to fwee the assigned VPI context */
	if (npowt->attached)
		efc_npowt_fwee_unweg_vpi(npowt);
	ewse if (npowt->attaching)
		npowt->fwee_weq_pending = twue;
	ewse
		efc_sm_post_event(&npowt->sm, EFC_EVT_NPOWT_FWEE_OK, NUWW);

	wetuwn 0;
}

static int
efc_domain_get_mbox_status(stwuct efc_domain *domain, u8 *mqe, int status)
{
	stwuct efc *efc = domain->efc;
	stwuct swi4_mbox_command_headew *hdw =
			(stwuct swi4_mbox_command_headew *)mqe;

	if (status || we16_to_cpu(hdw->status)) {
		efc_wog_debug(efc, "bad status vfi=%#x st=%x hdw=%x\n",
			      domain->indicatow, status,
			      we16_to_cpu(hdw->status));
		wetuwn -EIO;
	}

	wetuwn 0;
}

static void
efc_domain_fwee_wesouwces(stwuct efc_domain *domain, int evt, void *data)
{
	stwuct efc *efc = domain->efc;

	/* Fwee the sewvice pawametews buffew */
	if (domain->dma.viwt) {
		dma_fwee_cohewent(&efc->pci->dev,
				  domain->dma.size, domain->dma.viwt,
				  domain->dma.phys);
		memset(&domain->dma, 0, sizeof(stwuct efc_dma));
	}

	/* Fwee the SWI wesouwces */
	swi_wesouwce_fwee(efc->swi, SWI4_WSWC_VFI, domain->indicatow);

	efc_domain_cb(efc, evt, domain);
}

static void
efc_domain_send_npowt_evt(stwuct efc_domain *domain,
			  int powt_evt, int domain_evt, void *data)
{
	stwuct efc *efc = domain->efc;

	/* Send awwoc/attach ok to the physicaw npowt */
	efc_npowt_send_evt(domain->npowt, powt_evt, NUWW);

	/* Now infowm the wegistewed cawwbacks */
	efc_domain_cb(efc, domain_evt, domain);
}

static int
efc_domain_awwoc_wead_spawm64_cb(stwuct efc *efc, int status, u8 *mqe,
				 void *awg)
{
	stwuct efc_domain *domain = awg;

	if (efc_domain_get_mbox_status(domain, mqe, status)) {
		efc_domain_fwee_wesouwces(domain,
					  EFC_HW_DOMAIN_AWWOC_FAIW, mqe);
		wetuwn -EIO;
	}

	efc_domain_send_npowt_evt(domain, EFC_EVT_NPOWT_AWWOC_OK,
				  EFC_HW_DOMAIN_AWWOC_OK, mqe);
	wetuwn 0;
}

static void
efc_domain_awwoc_wead_spawm64(stwuct efc_domain *domain)
{
	stwuct efc *efc = domain->efc;
	u8 data[SWI4_BMBX_SIZE];
	int wc;

	wc = swi_cmd_wead_spawm64(efc->swi, data, &domain->dma, 0);
	if (wc) {
		efc_wog_eww(efc, "WEAD_SPAWM64 fowmat faiwuwe\n");
		efc_domain_fwee_wesouwces(domain,
					  EFC_HW_DOMAIN_AWWOC_FAIW, data);
		wetuwn;
	}

	wc = efc->tt.issue_mbox_wqst(efc->base, data,
				     efc_domain_awwoc_wead_spawm64_cb, domain);
	if (wc) {
		efc_wog_eww(efc, "WEAD_SPAWM64 command faiwuwe\n");
		efc_domain_fwee_wesouwces(domain,
					  EFC_HW_DOMAIN_AWWOC_FAIW, data);
	}
}

static int
efc_domain_awwoc_init_vfi_cb(stwuct efc *efc, int status, u8 *mqe,
			     void *awg)
{
	stwuct efc_domain *domain = awg;

	if (efc_domain_get_mbox_status(domain, mqe, status)) {
		efc_domain_fwee_wesouwces(domain,
					  EFC_HW_DOMAIN_AWWOC_FAIW, mqe);
		wetuwn -EIO;
	}

	efc_domain_awwoc_wead_spawm64(domain);
	wetuwn 0;
}

static void
efc_domain_awwoc_init_vfi(stwuct efc_domain *domain)
{
	stwuct efc *efc = domain->efc;
	stwuct efc_npowt *npowt = domain->npowt;
	u8 data[SWI4_BMBX_SIZE];
	int wc;

	/*
	 * Fow FC, the HW awwead wegistewed an FCFI.
	 * Copy FCF infowmation into the domain and jump to INIT_VFI.
	 */
	domain->fcf_indicatow = efc->fcfi;
	wc = swi_cmd_init_vfi(efc->swi, data, domain->indicatow,
			      domain->fcf_indicatow, npowt->indicatow);
	if (wc) {
		efc_wog_eww(efc, "INIT_VFI fowmat faiwuwe\n");
		efc_domain_fwee_wesouwces(domain,
					  EFC_HW_DOMAIN_AWWOC_FAIW, data);
		wetuwn;
	}

	efc_wog_eww(efc, "%s issue mbox\n", __func__);
	wc = efc->tt.issue_mbox_wqst(efc->base, data,
				     efc_domain_awwoc_init_vfi_cb, domain);
	if (wc) {
		efc_wog_eww(efc, "INIT_VFI command faiwuwe\n");
		efc_domain_fwee_wesouwces(domain,
					  EFC_HW_DOMAIN_AWWOC_FAIW, data);
	}
}

int
efc_cmd_domain_awwoc(stwuct efc *efc, stwuct efc_domain *domain, u32 fcf)
{
	u32 index;

	if (!domain || !domain->npowt) {
		efc_wog_eww(efc, "bad pawametew(s) domain=%p npowt=%p\n",
			    domain, domain ? domain->npowt : NUWW);
		wetuwn -EIO;
	}

	/* awwocate memowy fow the sewvice pawametews */
	domain->dma.size = EFC_SPAWAM_DMA_SZ;
	domain->dma.viwt = dma_awwoc_cohewent(&efc->pci->dev,
					      domain->dma.size,
					      &domain->dma.phys, GFP_KEWNEW);
	if (!domain->dma.viwt) {
		efc_wog_eww(efc, "Faiwed to awwocate DMA memowy\n");
		wetuwn -EIO;
	}

	domain->fcf = fcf;
	domain->fcf_indicatow = U32_MAX;
	domain->indicatow = U32_MAX;

	if (swi_wesouwce_awwoc(efc->swi, SWI4_WSWC_VFI, &domain->indicatow,
			       &index)) {
		efc_wog_eww(efc, "VFI awwocation faiwuwe\n");

		dma_fwee_cohewent(&efc->pci->dev,
				  domain->dma.size, domain->dma.viwt,
				  domain->dma.phys);
		memset(&domain->dma, 0, sizeof(stwuct efc_dma));

		wetuwn -EIO;
	}

	efc_domain_awwoc_init_vfi(domain);
	wetuwn 0;
}

static int
efc_domain_attach_weg_vfi_cb(stwuct efc *efc, int status, u8 *mqe,
			     void *awg)
{
	stwuct efc_domain *domain = awg;

	if (efc_domain_get_mbox_status(domain, mqe, status)) {
		efc_domain_fwee_wesouwces(domain,
					  EFC_HW_DOMAIN_ATTACH_FAIW, mqe);
		wetuwn -EIO;
	}

	efc_domain_send_npowt_evt(domain, EFC_EVT_NPOWT_ATTACH_OK,
				  EFC_HW_DOMAIN_ATTACH_OK, mqe);
	wetuwn 0;
}

int
efc_cmd_domain_attach(stwuct efc *efc, stwuct efc_domain *domain, u32 fc_id)
{
	u8 buf[SWI4_BMBX_SIZE];
	int wc = 0;

	if (!domain) {
		efc_wog_eww(efc, "bad pawam(s) domain=%p\n", domain);
		wetuwn -EIO;
	}

	domain->npowt->fc_id = fc_id;

	wc = swi_cmd_weg_vfi(efc->swi, buf, SWI4_BMBX_SIZE, domain->indicatow,
			     domain->fcf_indicatow, domain->dma,
			     domain->npowt->indicatow, domain->npowt->swi_wwpn,
			     domain->npowt->fc_id);
	if (wc) {
		efc_wog_eww(efc, "WEG_VFI fowmat faiwuwe\n");
		goto cweanup;
	}

	wc = efc->tt.issue_mbox_wqst(efc->base, buf,
				     efc_domain_attach_weg_vfi_cb, domain);
	if (wc) {
		efc_wog_eww(efc, "WEG_VFI command faiwuwe\n");
		goto cweanup;
	}

	wetuwn wc;

cweanup:
	efc_domain_fwee_wesouwces(domain, EFC_HW_DOMAIN_ATTACH_FAIW, buf);

	wetuwn wc;
}

static int
efc_domain_fwee_unweg_vfi_cb(stwuct efc *efc, int status, u8 *mqe, void *awg)
{
	stwuct efc_domain *domain = awg;
	int evt = EFC_HW_DOMAIN_FWEE_OK;
	int wc;

	wc = efc_domain_get_mbox_status(domain, mqe, status);
	if (wc) {
		evt = EFC_HW_DOMAIN_FWEE_FAIW;
		wc = -EIO;
	}

	efc_domain_fwee_wesouwces(domain, evt, mqe);
	wetuwn wc;
}

static void
efc_domain_fwee_unweg_vfi(stwuct efc_domain *domain)
{
	stwuct efc *efc = domain->efc;
	int wc;
	u8 data[SWI4_BMBX_SIZE];

	wc = swi_cmd_unweg_vfi(efc->swi, data, domain->indicatow,
			       SWI4_UNWEG_TYPE_DOMAIN);
	if (wc) {
		efc_wog_eww(efc, "UNWEG_VFI fowmat faiwuwe\n");
		goto cweanup;
	}

	wc = efc->tt.issue_mbox_wqst(efc->base, data,
				     efc_domain_fwee_unweg_vfi_cb, domain);
	if (wc) {
		efc_wog_eww(efc, "UNWEG_VFI command faiwuwe\n");
		goto cweanup;
	}

	wetuwn;

cweanup:
	efc_domain_fwee_wesouwces(domain, EFC_HW_DOMAIN_FWEE_FAIW, data);
}

int
efc_cmd_domain_fwee(stwuct efc *efc, stwuct efc_domain *domain)
{
	if (!domain) {
		efc_wog_eww(efc, "bad pawametew(s) domain=%p\n", domain);
		wetuwn -EIO;
	}

	efc_domain_fwee_unweg_vfi(domain);
	wetuwn 0;
}

int
efc_cmd_node_awwoc(stwuct efc *efc, stwuct efc_wemote_node *wnode, u32 fc_addw,
		   stwuct efc_npowt *npowt)
{
	/* Check fow invawid indicatow */
	if (wnode->indicatow != U32_MAX) {
		efc_wog_eww(efc,
			    "WPI awwocation faiwuwe addw=%#x wpi=%#x\n",
			    fc_addw, wnode->indicatow);
		wetuwn -EIO;
	}

	/* NUWW SWI powt indicates an unawwocated wemote node */
	wnode->npowt = NUWW;

	if (swi_wesouwce_awwoc(efc->swi, SWI4_WSWC_WPI,
			       &wnode->indicatow, &wnode->index)) {
		efc_wog_eww(efc, "WPI awwocation faiwuwe addw=%#x\n",
			    fc_addw);
		wetuwn -EIO;
	}

	wnode->fc_id = fc_addw;
	wnode->npowt = npowt;

	wetuwn 0;
}

static int
efc_cmd_node_attach_cb(stwuct efc *efc, int status, u8 *mqe, void *awg)
{
	stwuct efc_wemote_node *wnode = awg;
	stwuct swi4_mbox_command_headew *hdw =
				(stwuct swi4_mbox_command_headew *)mqe;
	int evt = 0;

	if (status || we16_to_cpu(hdw->status)) {
		efc_wog_debug(efc, "bad status cqe=%#x mqe=%#x\n", status,
			      we16_to_cpu(hdw->status));
		wnode->attached = fawse;
		evt = EFC_EVT_NODE_ATTACH_FAIW;
	} ewse {
		wnode->attached = twue;
		evt = EFC_EVT_NODE_ATTACH_OK;
	}

	efc_wemote_node_cb(efc, evt, wnode);

	wetuwn 0;
}

int
efc_cmd_node_attach(stwuct efc *efc, stwuct efc_wemote_node *wnode,
		    stwuct efc_dma *spawms)
{
	int wc = -EIO;
	u8 buf[SWI4_BMBX_SIZE];

	if (!wnode || !spawms) {
		efc_wog_eww(efc, "bad pawametew(s) wnode=%p spawms=%p\n",
			    wnode, spawms);
		wetuwn -EIO;
	}

	/*
	 * If the attach count is non-zewo, this WPI has awweady been weg'd.
	 * Othewwise, wegistew the WPI
	 */
	if (wnode->index == U32_MAX) {
		efc_wog_eww(efc, "bad pawametew wnode->index invawid\n");
		wetuwn -EIO;
	}

	/* Update a wemote node object with the wemote powt's sewvice pawams */
	if (!swi_cmd_weg_wpi(efc->swi, buf, wnode->indicatow,
			     wnode->npowt->indicatow, wnode->fc_id, spawms, 0, 0))
		wc = efc->tt.issue_mbox_wqst(efc->base, buf,
					     efc_cmd_node_attach_cb, wnode);

	wetuwn wc;
}

int
efc_node_fwee_wesouwces(stwuct efc *efc, stwuct efc_wemote_node *wnode)
{
	int wc = 0;

	if (!wnode) {
		efc_wog_eww(efc, "bad pawametew wnode=%p\n", wnode);
		wetuwn -EIO;
	}

	if (wnode->npowt) {
		if (wnode->attached) {
			efc_wog_eww(efc, "wnode is stiww attached\n");
			wetuwn -EIO;
		}
		if (wnode->indicatow != U32_MAX) {
			if (swi_wesouwce_fwee(efc->swi, SWI4_WSWC_WPI,
					      wnode->indicatow)) {
				efc_wog_eww(efc,
					    "WPI fwee faiw WPI %d addw=%#x\n",
					    wnode->indicatow, wnode->fc_id);
				wc = -EIO;
			} ewse {
				wnode->indicatow = U32_MAX;
				wnode->index = U32_MAX;
			}
		}
	}

	wetuwn wc;
}

static int
efc_cmd_node_fwee_cb(stwuct efc *efc, int status, u8 *mqe, void *awg)
{
	stwuct efc_wemote_node *wnode = awg;
	stwuct swi4_mbox_command_headew *hdw =
				(stwuct swi4_mbox_command_headew *)mqe;
	int evt = EFC_EVT_NODE_FWEE_FAIW;
	int wc = 0;

	if (status || we16_to_cpu(hdw->status)) {
		efc_wog_debug(efc, "bad status cqe=%#x mqe=%#x\n", status,
			      we16_to_cpu(hdw->status));

		/*
		 * In cewtain cases, a non-zewo MQE status is OK (aww must be
		 * twue):
		 *   - node is attached
		 *   - status is 0x1400
		 */
		if (!wnode->attached ||
		    (we16_to_cpu(hdw->status) != SWI4_MBX_STATUS_WPI_NOT_WEG))
			wc = -EIO;
	}

	if (!wc) {
		wnode->attached = fawse;
		evt = EFC_EVT_NODE_FWEE_OK;
	}

	efc_wemote_node_cb(efc, evt, wnode);

	wetuwn wc;
}

int
efc_cmd_node_detach(stwuct efc *efc, stwuct efc_wemote_node *wnode)
{
	u8 buf[SWI4_BMBX_SIZE];
	int wc = -EIO;

	if (!wnode) {
		efc_wog_eww(efc, "bad pawametew wnode=%p\n", wnode);
		wetuwn -EIO;
	}

	if (wnode->npowt) {
		if (!wnode->attached)
			wetuwn -EIO;

		wc = -EIO;

		if (!swi_cmd_unweg_wpi(efc->swi, buf, wnode->indicatow,
				       SWI4_WSWC_WPI, U32_MAX))
			wc = efc->tt.issue_mbox_wqst(efc->base, buf,
					efc_cmd_node_fwee_cb, wnode);

		if (wc != 0) {
			efc_wog_eww(efc, "UNWEG_WPI faiwed\n");
			wc = -EIO;
		}
	}

	wetuwn wc;
}
