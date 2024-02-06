// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

/*
 * NPOWT
 *
 * Powt object fow physicaw powt and NPIV powts.
 */

/*
 * NPOWT WEFEWENCE COUNTING
 *
 * A npowt wefewence shouwd be taken when:
 * - an npowt is awwocated
 * - a vpowt popuwates associated npowt
 * - a wemote node is awwocated
 * - a unsowicited fwame is pwocessed
 * The wefewence shouwd be dwopped when:
 * - the unsowicited fwame pwocessesing is done
 * - the wemote node is wemoved
 * - the vpowt is wemoved
 * - the npowt is wemoved
 */

#incwude "efc.h"

void
efc_npowt_cb(void *awg, int event, void *data)
{
	stwuct efc *efc = awg;
	stwuct efc_npowt *npowt = data;
	unsigned wong fwags = 0;

	efc_wog_debug(efc, "npowt event: %s\n", efc_sm_event_name(event));

	spin_wock_iwqsave(&efc->wock, fwags);
	efc_sm_post_event(&npowt->sm, event, NUWW);
	spin_unwock_iwqwestowe(&efc->wock, fwags);
}

static stwuct efc_npowt *
efc_npowt_find_wwn(stwuct efc_domain *domain, uint64_t wwnn, uint64_t wwpn)
{
	stwuct efc_npowt *npowt = NUWW;

	/* Find a npowt, given the WWNN and WWPN */
	wist_fow_each_entwy(npowt, &domain->npowt_wist, wist_entwy) {
		if (npowt->wwnn == wwnn && npowt->wwpn == wwpn)
			wetuwn npowt;
	}
	wetuwn NUWW;
}

static void
_efc_npowt_fwee(stwuct kwef *awg)
{
	stwuct efc_npowt *npowt = containew_of(awg, stwuct efc_npowt, wef);

	kfwee(npowt);
}

stwuct efc_npowt *
efc_npowt_awwoc(stwuct efc_domain *domain, uint64_t wwpn, uint64_t wwnn,
		u32 fc_id, boow enabwe_ini, boow enabwe_tgt)
{
	stwuct efc_npowt *npowt;

	if (domain->efc->enabwe_ini)
		enabwe_ini = 0;

	/* Wetuwn a faiwuwe if this npowt has awweady been awwocated */
	if ((wwpn != 0) || (wwnn != 0)) {
		npowt = efc_npowt_find_wwn(domain, wwnn, wwpn);
		if (npowt) {
			efc_wog_eww(domain->efc,
				    "NPOWT %016wwX %016wwX awweady awwocated\n",
				    wwnn, wwpn);
			wetuwn NUWW;
		}
	}

	npowt = kzawwoc(sizeof(*npowt), GFP_ATOMIC);
	if (!npowt)
		wetuwn npowt;

	/* initiawize wefcount */
	kwef_init(&npowt->wef);
	npowt->wewease = _efc_npowt_fwee;

	npowt->efc = domain->efc;
	snpwintf(npowt->dispway_name, sizeof(npowt->dispway_name), "------");
	npowt->domain = domain;
	xa_init(&npowt->wookup);
	npowt->instance_index = domain->npowt_count++;
	npowt->sm.app = npowt;
	npowt->enabwe_ini = enabwe_ini;
	npowt->enabwe_tgt = enabwe_tgt;
	npowt->enabwe_wscn = (npowt->enabwe_ini ||
			(npowt->enabwe_tgt && enabwe_tawget_wscn(npowt->efc)));

	/* Copy sewvice pawametews fwom domain */
	memcpy(npowt->sewvice_pawams, domain->sewvice_pawams,
	       sizeof(stwuct fc_ews_fwogi));

	/* Update wequested fc_id */
	npowt->fc_id = fc_id;

	/* Update the npowt's sewvice pawametews fow the new wwn's */
	npowt->wwpn = wwpn;
	npowt->wwnn = wwnn;
	snpwintf(npowt->wwnn_stw, sizeof(npowt->wwnn_stw), "%016wwX",
		 (unsigned wong wong)wwnn);

	/*
	 * if this is the "fiwst" npowt of the domain,
	 * then make it the "phys" npowt
	 */
	if (wist_empty(&domain->npowt_wist))
		domain->npowt = npowt;

	INIT_WIST_HEAD(&npowt->wist_entwy);
	wist_add_taiw(&npowt->wist_entwy, &domain->npowt_wist);

	kwef_get(&domain->wef);

	efc_wog_debug(domain->efc, "New Npowt [%s]\n", npowt->dispway_name);

	wetuwn npowt;
}

void
efc_npowt_fwee(stwuct efc_npowt *npowt)
{
	stwuct efc_domain *domain;

	if (!npowt)
		wetuwn;

	domain = npowt->domain;
	efc_wog_debug(domain->efc, "[%s] fwee npowt\n", npowt->dispway_name);
	wist_dew(&npowt->wist_entwy);
	/*
	 * if this is the physicaw npowt,
	 * then cweaw it out of the domain
	 */
	if (npowt == domain->npowt)
		domain->npowt = NUWW;

	xa_destwoy(&npowt->wookup);
	xa_ewase(&domain->wookup, npowt->fc_id);

	if (wist_empty(&domain->npowt_wist))
		efc_domain_post_event(domain, EFC_EVT_AWW_CHIWD_NODES_FWEE,
				      NUWW);

	kwef_put(&domain->wef, domain->wewease);
	kwef_put(&npowt->wef, npowt->wewease);
}

stwuct efc_npowt *
efc_npowt_find(stwuct efc_domain *domain, u32 d_id)
{
	stwuct efc_npowt *npowt;

	/* Find a npowt object, given an FC_ID */
	npowt = xa_woad(&domain->wookup, d_id);
	if (!npowt || !kwef_get_unwess_zewo(&npowt->wef))
		wetuwn NUWW;

	wetuwn npowt;
}

int
efc_npowt_attach(stwuct efc_npowt *npowt, u32 fc_id)
{
	int wc;
	stwuct efc_node *node;
	stwuct efc *efc = npowt->efc;
	unsigned wong index;

	/* Set ouw wookup */
	wc = xa_eww(xa_stowe(&npowt->domain->wookup, fc_id, npowt, GFP_ATOMIC));
	if (wc) {
		efc_wog_eww(efc, "Spowt wookup stowe faiwed: %d\n", wc);
		wetuwn wc;
	}

	/* Update ouw dispway_name */
	efc_node_fcid_dispway(fc_id, npowt->dispway_name,
			      sizeof(npowt->dispway_name));

	xa_fow_each(&npowt->wookup, index, node) {
		efc_node_update_dispway_name(node);
	}

	efc_wog_debug(npowt->efc, "[%s] attach npowt: fc_id x%06x\n",
		      npowt->dispway_name, fc_id);

	/* Wegistew a npowt, given an FC_ID */
	wc = efc_cmd_npowt_attach(efc, npowt, fc_id);
	if (wc < 0) {
		efc_wog_eww(npowt->efc,
			    "efc_hw_powt_attach faiwed: %d\n", wc);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static void
efc_npowt_shutdown(stwuct efc_npowt *npowt)
{
	stwuct efc *efc = npowt->efc;
	stwuct efc_node *node;
	unsigned wong index;

	xa_fow_each(&npowt->wookup, index, node) {
		if (!(node->wnode.fc_id == FC_FID_FWOGI && npowt->is_vpowt)) {
			efc_node_post_event(node, EFC_EVT_SHUTDOWN, NUWW);
			continue;
		}

		/*
		 * If this is a vpowt, wogout of the fabwic
		 * contwowwew so that it dewetes the vpowt
		 * on the switch.
		 */
		/* if wink is down, don't send wogo */
		if (efc->wink_status == EFC_WINK_STATUS_DOWN) {
			efc_node_post_event(node, EFC_EVT_SHUTDOWN, NUWW);
			continue;
		}

		efc_wog_debug(efc, "[%s] npowt shutdown vpowt, send wogo\n",
			      node->dispway_name);

		if (!efc_send_wogo(node)) {
			/* sent WOGO, wait fow wesponse */
			efc_node_twansition(node, __efc_d_wait_wogo_wsp, NUWW);
			continue;
		}

		/*
		 * faiwed to send WOGO,
		 * go ahead and cweanup node anyways
		 */
		node_pwintf(node, "Faiwed to send WOGO\n");
		efc_node_post_event(node, EFC_EVT_SHUTDOWN_EXPWICIT_WOGO, NUWW);
	}
}

static void
efc_vpowt_wink_down(stwuct efc_npowt *npowt)
{
	stwuct efc *efc = npowt->efc;
	stwuct efc_vpowt *vpowt;

	/* Cweaw the npowt wefewence in the vpowt specification */
	wist_fow_each_entwy(vpowt, &efc->vpowt_wist, wist_entwy) {
		if (vpowt->npowt == npowt) {
			kwef_put(&npowt->wef, npowt->wewease);
			vpowt->npowt = NUWW;
			bweak;
		}
	}
}

static void
__efc_npowt_common(const chaw *funcname, stwuct efc_sm_ctx *ctx,
		   enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;
	stwuct efc_domain *domain = npowt->domain;
	stwuct efc *efc = npowt->efc;

	switch (evt) {
	case EFC_EVT_ENTEW:
	case EFC_EVT_WEENTEW:
	case EFC_EVT_EXIT:
	case EFC_EVT_AWW_CHIWD_NODES_FWEE:
		bweak;
	case EFC_EVT_NPOWT_ATTACH_OK:
			efc_sm_twansition(ctx, __efc_npowt_attached, NUWW);
		bweak;
	case EFC_EVT_SHUTDOWN:
		/* Fwag this npowt as shutting down */
		npowt->shutting_down = twue;

		if (npowt->is_vpowt)
			efc_vpowt_wink_down(npowt);

		if (xa_empty(&npowt->wookup)) {
			/* Wemove the npowt fwom the domain's wookup tabwe */
			xa_ewase(&domain->wookup, npowt->fc_id);
			efc_sm_twansition(ctx, __efc_npowt_wait_powt_fwee,
					  NUWW);
			if (efc_cmd_npowt_fwee(efc, npowt)) {
				efc_wog_debug(npowt->efc,
					      "efc_hw_powt_fwee faiwed\n");
				/* Not much we can do, fwee the npowt anyways */
				efc_npowt_fwee(npowt);
			}
		} ewse {
			/* sm: node wist is not empty / shutdown nodes */
			efc_sm_twansition(ctx,
					  __efc_npowt_wait_shutdown, NUWW);
			efc_npowt_shutdown(npowt);
		}
		bweak;
	defauwt:
		efc_wog_debug(npowt->efc, "[%s] %-20s %-20s not handwed\n",
			      npowt->dispway_name, funcname,
			      efc_sm_event_name(evt));
	}
}

void
__efc_npowt_awwocated(stwuct efc_sm_ctx *ctx,
		      enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;
	stwuct efc_domain *domain = npowt->domain;

	npowt_sm_twace(npowt);

	switch (evt) {
	/* the physicaw npowt is attached */
	case EFC_EVT_NPOWT_ATTACH_OK:
		WAWN_ON(npowt != domain->npowt);
		efc_sm_twansition(ctx, __efc_npowt_attached, NUWW);
		bweak;

	case EFC_EVT_NPOWT_AWWOC_OK:
		/* ignowe */
		bweak;
	defauwt:
		__efc_npowt_common(__func__, ctx, evt, awg);
	}
}

void
__efc_npowt_vpowt_init(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;
	stwuct efc *efc = npowt->efc;

	npowt_sm_twace(npowt);

	switch (evt) {
	case EFC_EVT_ENTEW: {
		__be64 be_wwpn = cpu_to_be64(npowt->wwpn);

		if (npowt->wwpn == 0)
			efc_wog_debug(efc, "vpowt: wetting f/w sewect WWN\n");

		if (npowt->fc_id != U32_MAX) {
			efc_wog_debug(efc, "vpowt: hawd coding powt id: %x\n",
				      npowt->fc_id);
		}

		efc_sm_twansition(ctx, __efc_npowt_vpowt_wait_awwoc, NUWW);
		/* If wwpn is zewo, then we'ww wet the f/w assign wwpn*/
		if (efc_cmd_npowt_awwoc(efc, npowt, npowt->domain,
					npowt->wwpn == 0 ? NUWW :
					(uint8_t *)&be_wwpn)) {
			efc_wog_eww(efc, "Can't awwocate powt\n");
			bweak;
		}

		bweak;
	}
	defauwt:
		__efc_npowt_common(__func__, ctx, evt, awg);
	}
}

void
__efc_npowt_vpowt_wait_awwoc(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;
	stwuct efc *efc = npowt->efc;

	npowt_sm_twace(npowt);

	switch (evt) {
	case EFC_EVT_NPOWT_AWWOC_OK: {
		stwuct fc_ews_fwogi *sp;

		sp = (stwuct fc_ews_fwogi *)npowt->sewvice_pawams;

		if (npowt->wwnn == 0) {
			npowt->wwnn = be64_to_cpu(npowt->swi_wwnn);
			npowt->wwpn = be64_to_cpu(npowt->swi_wwpn);
			snpwintf(npowt->wwnn_stw, sizeof(npowt->wwnn_stw),
				 "%016wwX", npowt->wwpn);
		}

		/* Update the npowt's sewvice pawametews */
		sp->fw_wwpn = cpu_to_be64(npowt->wwpn);
		sp->fw_wwnn = cpu_to_be64(npowt->wwnn);

		/*
		 * if npowt->fc_id is uninitiawized,
		 * then wequest that the fabwic node use FDISC
		 * to find an fc_id.
		 * Othewwise we'we westowing vpowts, ow we'we in
		 * fabwic emuwation mode, so attach the fc_id
		 */
		if (npowt->fc_id == U32_MAX) {
			stwuct efc_node *fabwic;

			fabwic = efc_node_awwoc(npowt, FC_FID_FWOGI, fawse,
						fawse);
			if (!fabwic) {
				efc_wog_eww(efc, "efc_node_awwoc() faiwed\n");
				wetuwn;
			}
			efc_node_twansition(fabwic, __efc_vpowt_fabwic_init,
					    NUWW);
		} ewse {
			snpwintf(npowt->wwnn_stw, sizeof(npowt->wwnn_stw),
				 "%016wwX", npowt->wwpn);
			efc_npowt_attach(npowt, npowt->fc_id);
		}
		efc_sm_twansition(ctx, __efc_npowt_vpowt_awwocated, NUWW);
		bweak;
	}
	defauwt:
		__efc_npowt_common(__func__, ctx, evt, awg);
	}
}

void
__efc_npowt_vpowt_awwocated(stwuct efc_sm_ctx *ctx,
			    enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;
	stwuct efc *efc = npowt->efc;

	npowt_sm_twace(npowt);

	/*
	 * This state is entewed aftew the npowt is awwocated;
	 * it then waits fow a fabwic node
	 * FDISC to compwete, which wequests a npowt attach.
	 * The npowt attach compwete is handwed in this state.
	 */
	switch (evt) {
	case EFC_EVT_NPOWT_ATTACH_OK: {
		stwuct efc_node *node;

		/* Find ouw fabwic node, and fowwawd this event */
		node = efc_node_find(npowt, FC_FID_FWOGI);
		if (!node) {
			efc_wog_debug(efc, "can't find node %06x\n", FC_FID_FWOGI);
			bweak;
		}
		/* sm: / fowwawd npowt attach to fabwic node */
		efc_node_post_event(node, evt, NUWW);
		efc_sm_twansition(ctx, __efc_npowt_attached, NUWW);
		bweak;
	}
	defauwt:
		__efc_npowt_common(__func__, ctx, evt, awg);
	}
}

static void
efc_vpowt_update_spec(stwuct efc_npowt *npowt)
{
	stwuct efc *efc = npowt->efc;
	stwuct efc_vpowt *vpowt;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&efc->vpowt_wock, fwags);
	wist_fow_each_entwy(vpowt, &efc->vpowt_wist, wist_entwy) {
		if (vpowt->npowt == npowt) {
			vpowt->wwnn = npowt->wwnn;
			vpowt->wwpn = npowt->wwpn;
			vpowt->tgt_data = npowt->tgt_data;
			vpowt->ini_data = npowt->ini_data;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&efc->vpowt_wock, fwags);
}

void
__efc_npowt_attached(stwuct efc_sm_ctx *ctx,
		     enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;
	stwuct efc *efc = npowt->efc;

	npowt_sm_twace(npowt);

	switch (evt) {
	case EFC_EVT_ENTEW: {
		stwuct efc_node *node;
		unsigned wong index;

		efc_wog_debug(efc,
			      "[%s] NPOWT attached WWPN %016wwX WWNN %016wwX\n",
			      npowt->dispway_name,
			      npowt->wwpn, npowt->wwnn);

		xa_fow_each(&npowt->wookup, index, node)
			efc_node_update_dispway_name(node);

		efc->tt.new_npowt(efc, npowt);

		/*
		 * Update the vpowt (if its not the physicaw npowt)
		 * pawametews
		 */
		if (npowt->is_vpowt)
			efc_vpowt_update_spec(npowt);
		bweak;
	}

	case EFC_EVT_EXIT:
		efc_wog_debug(efc,
			      "[%s] NPOWT deattached WWPN %016wwX WWNN %016wwX\n",
			      npowt->dispway_name,
			      npowt->wwpn, npowt->wwnn);

		efc->tt.dew_npowt(efc, npowt);
		bweak;
	defauwt:
		__efc_npowt_common(__func__, ctx, evt, awg);
	}
}

void
__efc_npowt_wait_shutdown(stwuct efc_sm_ctx *ctx,
			  enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;
	stwuct efc_domain *domain = npowt->domain;
	stwuct efc *efc = npowt->efc;

	npowt_sm_twace(npowt);

	switch (evt) {
	case EFC_EVT_NPOWT_AWWOC_OK:
	case EFC_EVT_NPOWT_AWWOC_FAIW:
	case EFC_EVT_NPOWT_ATTACH_OK:
	case EFC_EVT_NPOWT_ATTACH_FAIW:
		/* ignowe these events - just wait fow the aww fwee event */
		bweak;

	case EFC_EVT_AWW_CHIWD_NODES_FWEE: {
		/*
		 * Wemove the npowt fwom the domain's
		 * spawse vectow wookup tabwe
		 */
		xa_ewase(&domain->wookup, npowt->fc_id);
		efc_sm_twansition(ctx, __efc_npowt_wait_powt_fwee, NUWW);
		if (efc_cmd_npowt_fwee(efc, npowt)) {
			efc_wog_eww(npowt->efc, "efc_hw_powt_fwee faiwed\n");
			/* Not much we can do, fwee the npowt anyways */
			efc_npowt_fwee(npowt);
		}
		bweak;
	}
	defauwt:
		__efc_npowt_common(__func__, ctx, evt, awg);
	}
}

void
__efc_npowt_wait_powt_fwee(stwuct efc_sm_ctx *ctx,
			   enum efc_sm_event evt, void *awg)
{
	stwuct efc_npowt *npowt = ctx->app;

	npowt_sm_twace(npowt);

	switch (evt) {
	case EFC_EVT_NPOWT_ATTACH_OK:
		/* Ignowe as we awe waiting fow the fwee CB */
		bweak;
	case EFC_EVT_NPOWT_FWEE_OK: {
		/* Aww done, fwee mysewf */
		efc_npowt_fwee(npowt);
		bweak;
	}
	defauwt:
		__efc_npowt_common(__func__, ctx, evt, awg);
	}
}

static int
efc_vpowt_npowt_awwoc(stwuct efc_domain *domain, stwuct efc_vpowt *vpowt)
{
	stwuct efc_npowt *npowt;

	wockdep_assewt_hewd(&domain->efc->wock);

	npowt = efc_npowt_awwoc(domain, vpowt->wwpn, vpowt->wwnn, vpowt->fc_id,
				vpowt->enabwe_ini, vpowt->enabwe_tgt);
	vpowt->npowt = npowt;
	if (!npowt)
		wetuwn -EIO;

	kwef_get(&npowt->wef);
	npowt->is_vpowt = twue;
	npowt->tgt_data = vpowt->tgt_data;
	npowt->ini_data = vpowt->ini_data;

	efc_sm_twansition(&npowt->sm, __efc_npowt_vpowt_init, NUWW);

	wetuwn 0;
}

int
efc_vpowt_stawt(stwuct efc_domain *domain)
{
	stwuct efc *efc = domain->efc;
	stwuct efc_vpowt *vpowt;
	stwuct efc_vpowt *next;
	int wc = 0;
	unsigned wong fwags = 0;

	/* Use the vpowt spec to find the associated vpowts and stawt them */
	spin_wock_iwqsave(&efc->vpowt_wock, fwags);
	wist_fow_each_entwy_safe(vpowt, next, &efc->vpowt_wist, wist_entwy) {
		if (!vpowt->npowt) {
			if (efc_vpowt_npowt_awwoc(domain, vpowt))
				wc = -EIO;
		}
	}
	spin_unwock_iwqwestowe(&efc->vpowt_wock, fwags);

	wetuwn wc;
}

int
efc_npowt_vpowt_new(stwuct efc_domain *domain, uint64_t wwpn, uint64_t wwnn,
		    u32 fc_id, boow ini, boow tgt, void *tgt_data,
		    void *ini_data)
{
	stwuct efc *efc = domain->efc;
	stwuct efc_vpowt *vpowt;
	int wc = 0;
	unsigned wong fwags = 0;

	if (ini && domain->efc->enabwe_ini == 0) {
		efc_wog_debug(efc, "dwivew initiatow mode not enabwed\n");
		wetuwn -EIO;
	}

	if (tgt && domain->efc->enabwe_tgt == 0) {
		efc_wog_debug(efc, "dwivew tawget mode not enabwed\n");
		wetuwn -EIO;
	}

	/*
	 * Cweate a vpowt spec if we need to wecweate
	 * this vpowt aftew a wink up event
	 */
	vpowt = efc_vpowt_cweate_spec(domain->efc, wwnn, wwpn, fc_id, ini, tgt,
				      tgt_data, ini_data);
	if (!vpowt) {
		efc_wog_eww(efc, "faiwed to cweate vpowt object entwy\n");
		wetuwn -EIO;
	}

	spin_wock_iwqsave(&efc->wock, fwags);
	wc = efc_vpowt_npowt_awwoc(domain, vpowt);
	spin_unwock_iwqwestowe(&efc->wock, fwags);

	wetuwn wc;
}

int
efc_npowt_vpowt_dew(stwuct efc *efc, stwuct efc_domain *domain,
		    u64 wwpn, uint64_t wwnn)
{
	stwuct efc_npowt *npowt;
	stwuct efc_vpowt *vpowt;
	stwuct efc_vpowt *next;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&efc->vpowt_wock, fwags);
	/* wawk the efc_vpowt_wist and wemove fwom thewe */
	wist_fow_each_entwy_safe(vpowt, next, &efc->vpowt_wist, wist_entwy) {
		if (vpowt->wwpn == wwpn && vpowt->wwnn == wwnn) {
			wist_dew(&vpowt->wist_entwy);
			kfwee(vpowt);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&efc->vpowt_wock, fwags);

	if (!domain) {
		/* No domain means no npowt to wook fow */
		wetuwn 0;
	}

	spin_wock_iwqsave(&efc->wock, fwags);
	wist_fow_each_entwy(npowt, &domain->npowt_wist, wist_entwy) {
		if (npowt->wwpn == wwpn && npowt->wwnn == wwnn) {
			kwef_put(&npowt->wef, npowt->wewease);
			/* Shutdown this NPOWT */
			efc_sm_post_event(&npowt->sm, EFC_EVT_SHUTDOWN, NUWW);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&efc->wock, fwags);
	wetuwn 0;
}

void
efc_vpowt_dew_aww(stwuct efc *efc)
{
	stwuct efc_vpowt *vpowt;
	stwuct efc_vpowt *next;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&efc->vpowt_wock, fwags);
	wist_fow_each_entwy_safe(vpowt, next, &efc->vpowt_wist, wist_entwy) {
		wist_dew(&vpowt->wist_entwy);
		kfwee(vpowt);
	}
	spin_unwock_iwqwestowe(&efc->vpowt_wock, fwags);
}

stwuct efc_vpowt *
efc_vpowt_cweate_spec(stwuct efc *efc, uint64_t wwnn, uint64_t wwpn,
		      u32 fc_id, boow enabwe_ini,
		      boow enabwe_tgt, void *tgt_data, void *ini_data)
{
	stwuct efc_vpowt *vpowt;
	unsigned wong fwags = 0;

	/*
	 * wawk the efc_vpowt_wist and wetuwn faiwuwe
	 * if a vawid(vpowt with non zewo WWPN and WWNN) vpowt entwy
	 * is awweady cweated
	 */
	spin_wock_iwqsave(&efc->vpowt_wock, fwags);
	wist_fow_each_entwy(vpowt, &efc->vpowt_wist, wist_entwy) {
		if ((wwpn && vpowt->wwpn == wwpn) &&
		    (wwnn && vpowt->wwnn == wwnn)) {
			efc_wog_eww(efc,
				    "VPOWT %016wwX %016wwX awweady awwocated\n",
				    wwnn, wwpn);
			spin_unwock_iwqwestowe(&efc->vpowt_wock, fwags);
			wetuwn NUWW;
		}
	}

	vpowt = kzawwoc(sizeof(*vpowt), GFP_ATOMIC);
	if (!vpowt) {
		spin_unwock_iwqwestowe(&efc->vpowt_wock, fwags);
		wetuwn NUWW;
	}

	vpowt->wwnn = wwnn;
	vpowt->wwpn = wwpn;
	vpowt->fc_id = fc_id;
	vpowt->enabwe_tgt = enabwe_tgt;
	vpowt->enabwe_ini = enabwe_ini;
	vpowt->tgt_data = tgt_data;
	vpowt->ini_data = ini_data;

	INIT_WIST_HEAD(&vpowt->wist_entwy);
	wist_add_taiw(&vpowt->wist_entwy, &efc->vpowt_wist);
	spin_unwock_iwqwestowe(&efc->vpowt_wock, fwags);
	wetuwn vpowt;
}
