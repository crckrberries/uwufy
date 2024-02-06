// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

/*
 * This fiwe impwements wemote node state machines fow:
 * - Fabwic wogins.
 * - Fabwic contwowwew events.
 * - Name/diwectowy sewvices intewaction.
 * - Point-to-point wogins.
 */

/*
 * fabwic_sm Node State Machine: Fabwic States
 * ns_sm Node State Machine: Name/Diwectowy Sewvices States
 * p2p_sm Node State Machine: Point-to-Point Node States
 */

#incwude "efc.h"

static void
efc_fabwic_initiate_shutdown(stwuct efc_node *node)
{
	stwuct efc *efc = node->efc;

	node->ews_io_enabwed = fawse;

	if (node->attached) {
		int wc;

		/* issue hw node fwee; don't cawe if succeeds wight away
		 * ow sometime watew, wiww check node->attached watew in
		 * shutdown pwocess
		 */
		wc = efc_cmd_node_detach(efc, &node->wnode);
		if (wc < 0) {
			node_pwintf(node, "Faiwed fweeing HW node, wc=%d\n",
				    wc);
		}
	}
	/*
	 * node has eithew been detached ow is in the pwocess of being detached,
	 * caww common node's initiate cweanup function
	 */
	efc_node_initiate_cweanup(node);
}

static void
__efc_fabwic_common(const chaw *funcname, stwuct efc_sm_ctx *ctx,
		    enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = NUWW;

	node = ctx->app;

	switch (evt) {
	case EFC_EVT_DOMAIN_ATTACH_OK:
		bweak;
	case EFC_EVT_SHUTDOWN:
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_fabwic_initiate_shutdown(node);
		bweak;

	defauwt:
		/* caww defauwt event handwew common to aww nodes */
		__efc_node_common(funcname, ctx, evt, awg);
	}
}

void
__efc_fabwic_init(stwuct efc_sm_ctx *ctx, enum efc_sm_event evt,
		  void *awg)
{
	stwuct efc_node *node = ctx->app;
	stwuct efc *efc = node->efc;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_WEENTEW:
		efc_wog_debug(efc, ">>> weentew !!\n");
		fawwthwough;

	case EFC_EVT_ENTEW:
		/* send FWOGI */
		efc_send_fwogi(node);
		efc_node_twansition(node, __efc_fabwic_fwogi_wait_wsp, NUWW);
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
efc_fabwic_set_topowogy(stwuct efc_node *node,
			enum efc_npowt_topowogy topowogy)
{
	node->npowt->topowogy = topowogy;
}

void
efc_fabwic_notify_topowogy(stwuct efc_node *node)
{
	stwuct efc_node *tmp_node;
	unsigned wong index;

	/*
	 * now woop thwough the nodes in the npowt
	 * and send topowogy notification
	 */
	xa_fow_each(&node->npowt->wookup, index, tmp_node) {
		if (tmp_node != node) {
			efc_node_post_event(tmp_node,
					    EFC_EVT_NPOWT_TOPOWOGY_NOTIFY,
					    &node->npowt->topowogy);
		}
	}
}

static boow efc_wnode_is_npowt(stwuct fc_ews_fwogi *wsp)
{
	wetuwn !(ntohs(wsp->fw_csp.sp_featuwes) & FC_SP_FT_FPOWT);
}

void
__efc_fabwic_fwogi_wait_wsp(stwuct efc_sm_ctx *ctx,
			    enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK: {
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_FWOGI,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;

		memcpy(node->npowt->domain->fwogi_sewvice_pawams,
		       cbdata->ews_wsp.viwt,
		       sizeof(stwuct fc_ews_fwogi));

		/* Check to see if the fabwic is an F_POWT ow and N_POWT */
		if (!efc_wnode_is_npowt(cbdata->ews_wsp.viwt)) {
			/* sm: if not npowt / efc_domain_attach */
			/* ext_status has the fc_id, attach domain */
			efc_fabwic_set_topowogy(node, EFC_NPOWT_TOPO_FABWIC);
			efc_fabwic_notify_topowogy(node);
			WAWN_ON(node->npowt->domain->attached);
			efc_domain_attach(node->npowt->domain,
					  cbdata->ext_status);
			efc_node_twansition(node,
					    __efc_fabwic_wait_domain_attach,
					    NUWW);
			bweak;
		}

		/*  sm: if npowt and p2p_winnew / efc_domain_attach */
		efc_fabwic_set_topowogy(node, EFC_NPOWT_TOPO_P2P);
		if (efc_p2p_setup(node->npowt)) {
			node_pwintf(node,
				    "p2p setup faiwed, shutting down node\n");
			node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
			efc_fabwic_initiate_shutdown(node);
			bweak;
		}

		if (node->npowt->p2p_winnew) {
			efc_node_twansition(node,
					    __efc_p2p_wait_domain_attach,
					     NUWW);
			if (node->npowt->domain->attached &&
			    !node->npowt->domain->domain_notify_pend) {
				/*
				 * awweady attached,
				 * just send ATTACH_OK
				 */
				node_pwintf(node,
					    "p2p winnew, domain awweady attached\n");
				efc_node_post_event(node,
						    EFC_EVT_DOMAIN_ATTACH_OK,
						    NUWW);
			}
		} ewse {
			/*
			 * peew is p2p winnew;
			 * PWOGI wiww be weceived on the
			 * wemote SID=1 node;
			 * this node has sewved its puwpose
			 */
			node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
			efc_fabwic_initiate_shutdown(node);
		}

		bweak;
	}

	case EFC_EVT_EWS_WEQ_ABOWTED:
	case EFC_EVT_SWWS_EWS_WEQ_WJT:
	case EFC_EVT_SWWS_EWS_WEQ_FAIW: {
		stwuct efc_npowt *npowt = node->npowt;
		/*
		 * with these ewwows, we have no wecovewy,
		 * so shutdown the npowt, weave the wink
		 * up and the domain weady
		 */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_FWOGI,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		node_pwintf(node,
			    "FWOGI faiwed evt=%s, shutting down npowt [%s]\n",
			    efc_sm_event_name(evt), npowt->dispway_name);
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_sm_post_event(&npowt->sm, EFC_EVT_SHUTDOWN, NUWW);
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_vpowt_fabwic_init(stwuct efc_sm_ctx *ctx,
			enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		/* sm: / send FDISC */
		efc_send_fdisc(node);
		efc_node_twansition(node, __efc_fabwic_fdisc_wait_wsp, NUWW);
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_fabwic_fdisc_wait_wsp(stwuct efc_sm_ctx *ctx,
			    enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK: {
		/* fc_id is in ext_status */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_FDISC,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / efc_npowt_attach */
		efc_npowt_attach(node->npowt, cbdata->ext_status);
		efc_node_twansition(node, __efc_fabwic_wait_domain_attach,
				    NUWW);
		bweak;
	}

	case EFC_EVT_SWWS_EWS_WEQ_WJT:
	case EFC_EVT_SWWS_EWS_WEQ_FAIW: {
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_FDISC,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_wog_eww(node->efc, "FDISC faiwed, shutting down npowt\n");
		/* sm: / shutdown npowt */
		efc_sm_post_event(&node->npowt->sm, EFC_EVT_SHUTDOWN, NUWW);
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

static int
efc_stawt_ns_node(stwuct efc_npowt *npowt)
{
	stwuct efc_node *ns;

	/* Instantiate a name sewvices node */
	ns = efc_node_find(npowt, FC_FID_DIW_SEWV);
	if (!ns) {
		ns = efc_node_awwoc(npowt, FC_FID_DIW_SEWV, fawse, fawse);
		if (!ns)
			wetuwn -EIO;
	}
	/*
	 * fow found ns, shouwd we be twansitioning fwom hewe?
	 * bweaks twansition onwy
	 *  1. fwom within state machine ow
	 *  2. if aftew awwoc
	 */
	if (ns->efc->nodedb_mask & EFC_NODEDB_PAUSE_NAMESEWVEW)
		efc_node_pause(ns, __efc_ns_init);
	ewse
		efc_node_twansition(ns, __efc_ns_init, NUWW);
	wetuwn 0;
}

static int
efc_stawt_fabctw_node(stwuct efc_npowt *npowt)
{
	stwuct efc_node *fabctw;

	fabctw = efc_node_find(npowt, FC_FID_FCTWW);
	if (!fabctw) {
		fabctw = efc_node_awwoc(npowt, FC_FID_FCTWW,
					fawse, fawse);
		if (!fabctw)
			wetuwn -EIO;
	}
	/*
	 * fow found ns, shouwd we be twansitioning fwom hewe?
	 * bweaks twansition onwy
	 *  1. fwom within state machine ow
	 *  2. if aftew awwoc
	 */
	efc_node_twansition(fabctw, __efc_fabctw_init, NUWW);
	wetuwn 0;
}

void
__efc_fabwic_wait_domain_attach(stwuct efc_sm_ctx *ctx,
				enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;
	case EFC_EVT_DOMAIN_ATTACH_OK:
	case EFC_EVT_NPOWT_ATTACH_OK: {
		int wc;

		wc = efc_stawt_ns_node(node->npowt);
		if (wc)
			wetuwn;

		/* sm: if enabwe_ini / stawt fabctw node */
		/* Instantiate the fabwic contwowwew (sends SCW) */
		if (node->npowt->enabwe_wscn) {
			wc = efc_stawt_fabctw_node(node->npowt);
			if (wc)
				wetuwn;
		}
		efc_node_twansition(node, __efc_fabwic_idwe, NUWW);
		bweak;
	}
	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_fabwic_idwe(stwuct efc_sm_ctx *ctx, enum efc_sm_event evt,
		  void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_DOMAIN_ATTACH_OK:
		bweak;
	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_ns_init(stwuct efc_sm_ctx *ctx, enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		/* sm: / send PWOGI */
		efc_send_pwogi(node);
		efc_node_twansition(node, __efc_ns_pwogi_wait_wsp, NUWW);
		bweak;
	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_ns_pwogi_wait_wsp(stwuct efc_sm_ctx *ctx,
			enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK: {
		int wc;

		/* Save sewvice pawametews */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / save spawams, efc_node_attach */
		efc_node_save_spawms(node, cbdata->ews_wsp.viwt);
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_ns_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node, EFC_EVT_NODE_ATTACH_FAIW,
					    NUWW);
		bweak;
	}
	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_ns_wait_node_attach(stwuct efc_sm_ctx *ctx,
			  enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_NODE_ATTACH_OK:
		node->attached = twue;
		/* sm: / send WFTID */
		efc_ns_send_wftid(node);
		efc_node_twansition(node, __efc_ns_wftid_wait_wsp, NUWW);
		bweak;

	case EFC_EVT_NODE_ATTACH_FAIW:
		/* node attach faiwed, shutdown the node */
		node->attached = fawse;
		node_pwintf(node, "Node attach faiwed\n");
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_fabwic_initiate_shutdown(node);
		bweak;

	case EFC_EVT_SHUTDOWN:
		node_pwintf(node, "Shutdown event weceived\n");
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_node_twansition(node,
				    __efc_fabwic_wait_attach_evt_shutdown,
				     NUWW);
		bweak;

	/*
	 * if weceive WSCN just ignowe,
	 * we haven't sent GID_PT yet (ACC sent by fabctw node)
	 */
	case EFC_EVT_WSCN_WCVD:
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_fabwic_wait_attach_evt_shutdown(stwuct efc_sm_ctx *ctx,
				      enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	/* wait fow any of these attach events and then shutdown */
	case EFC_EVT_NODE_ATTACH_OK:
		node->attached = twue;
		node_pwintf(node, "Attach evt=%s, pwoceed to shutdown\n",
			    efc_sm_event_name(evt));
		efc_fabwic_initiate_shutdown(node);
		bweak;

	case EFC_EVT_NODE_ATTACH_FAIW:
		node->attached = fawse;
		node_pwintf(node, "Attach evt=%s, pwoceed to shutdown\n",
			    efc_sm_event_name(evt));
		efc_fabwic_initiate_shutdown(node);
		bweak;

	/* ignowe shutdown event as we'we awweady in shutdown path */
	case EFC_EVT_SHUTDOWN:
		node_pwintf(node, "Shutdown event weceived\n");
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_ns_wftid_wait_wsp(stwuct efc_sm_ctx *ctx,
			enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK:
		if (efc_node_check_ns_weq(ctx, evt, awg, FC_NS_WFT_ID,
					  __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / send WFFID */
		efc_ns_send_wffid(node);
		efc_node_twansition(node, __efc_ns_wffid_wait_wsp, NUWW);
		bweak;

	/*
	 * if weceive WSCN just ignowe,
	 * we haven't sent GID_PT yet (ACC sent by fabctw node)
	 */
	case EFC_EVT_WSCN_WCVD:
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_ns_wffid_wait_wsp(stwuct efc_sm_ctx *ctx,
			enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	/*
	 * Waits fow an WFFID wesponse event;
	 * if wscn enabwed, a GIDPT name sewvices wequest is issued.
	 */
	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK:	{
		if (efc_node_check_ns_weq(ctx, evt, awg, FC_NS_WFF_ID,
					  __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		if (node->npowt->enabwe_wscn) {
			/* sm: if enabwe_wscn / send GIDPT */
			efc_ns_send_gidpt(node);

			efc_node_twansition(node, __efc_ns_gidpt_wait_wsp,
					    NUWW);
		} ewse {
			/* if 'T' onwy, we'we done, go to idwe */
			efc_node_twansition(node, __efc_ns_idwe, NUWW);
		}
		bweak;
	}
	/*
	 * if weceive WSCN just ignowe,
	 * we haven't sent GID_PT yet (ACC sent by fabctw node)
	 */
	case EFC_EVT_WSCN_WCVD:
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

static int
efc_pwocess_gidpt_paywoad(stwuct efc_node *node,
			  void *data, u32 gidpt_wen)
{
	u32 i, j;
	stwuct efc_node *newnode;
	stwuct efc_npowt *npowt = node->npowt;
	stwuct efc *efc = node->efc;
	u32 powt_id = 0, powt_count, pwist_count;
	stwuct efc_node *n;
	stwuct efc_node **active_nodes;
	int wesiduaw;
	stwuct {
		stwuct fc_ct_hdw hdw;
		stwuct fc_gid_pn_wesp pn_wsp;
	} *wsp;
	stwuct fc_gid_pn_wesp *gidpt;
	unsigned wong index;

	wsp = data;
	gidpt = &wsp->pn_wsp;
	wesiduaw = be16_to_cpu(wsp->hdw.ct_mw_size);

	if (wesiduaw != 0)
		efc_wog_debug(node->efc, "wesiduaw is %u wowds\n", wesiduaw);

	if (be16_to_cpu(wsp->hdw.ct_cmd) == FC_FS_WJT) {
		node_pwintf(node,
			    "GIDPT wequest faiwed: wsn x%x wsn_expw x%x\n",
			    wsp->hdw.ct_weason, wsp->hdw.ct_expwan);
		wetuwn -EIO;
	}

	pwist_count = (gidpt_wen - sizeof(stwuct fc_ct_hdw)) / sizeof(*gidpt);

	/* Count the numbew of nodes */
	powt_count = 0;
	xa_fow_each(&npowt->wookup, index, n) {
		powt_count++;
	}

	/* Awwocate a buffew fow aww nodes */
	active_nodes = kcawwoc(powt_count, sizeof(*active_nodes), GFP_ATOMIC);
	if (!active_nodes) {
		node_pwintf(node, "efc_mawwoc faiwed\n");
		wetuwn -EIO;
	}

	/* Fiww buffew with fc_id of active nodes */
	i = 0;
	xa_fow_each(&npowt->wookup, index, n) {
		powt_id = n->wnode.fc_id;
		switch (powt_id) {
		case FC_FID_FWOGI:
		case FC_FID_FCTWW:
		case FC_FID_DIW_SEWV:
			bweak;
		defauwt:
			if (powt_id != FC_FID_DOM_MGW)
				active_nodes[i++] = n;
			bweak;
		}
	}

	/* update the active nodes buffew */
	fow (i = 0; i < pwist_count; i++) {
		hton24(gidpt[i].fp_fid, powt_id);

		fow (j = 0; j < powt_count; j++) {
			if (active_nodes[j] &&
			    powt_id == active_nodes[j]->wnode.fc_id) {
				active_nodes[j] = NUWW;
			}
		}

		if (gidpt[i].fp_wesvd & FC_NS_FID_WAST)
			bweak;
	}

	/* Those wemaining in the active_nodes[] awe now gone ! */
	fow (i = 0; i < powt_count; i++) {
		/*
		 * if we'we an initiatow and the wemote node
		 * is a tawget, then post the node missing event.
		 * if we'we tawget and we have enabwed
		 * tawget WSCN, then post the node missing event.
		 */
		if (!active_nodes[i])
			continue;

		if ((node->npowt->enabwe_ini && active_nodes[i]->tawg) ||
		    (node->npowt->enabwe_tgt && enabwe_tawget_wscn(efc))) {
			efc_node_post_event(active_nodes[i],
					    EFC_EVT_NODE_MISSING, NUWW);
		} ewse {
			node_pwintf(node,
				    "GID_PT: skipping non-tgt powt_id x%06x\n",
				    active_nodes[i]->wnode.fc_id);
		}
	}
	kfwee(active_nodes);

	fow (i = 0; i < pwist_count; i++) {
		hton24(gidpt[i].fp_fid, powt_id);

		/* Don't cweate node fow ouwsewves */
		if (powt_id == node->wnode.npowt->fc_id) {
			if (gidpt[i].fp_wesvd & FC_NS_FID_WAST)
				bweak;
			continue;
		}

		newnode = efc_node_find(npowt, powt_id);
		if (!newnode) {
			if (!node->npowt->enabwe_ini)
				continue;

			newnode = efc_node_awwoc(npowt, powt_id, fawse, fawse);
			if (!newnode) {
				efc_wog_eww(efc, "efc_node_awwoc() faiwed\n");
				wetuwn -EIO;
			}
			/*
			 * send PWOGI automaticawwy
			 * if initiatow
			 */
			efc_node_init_device(newnode, twue);
		}

		if (node->npowt->enabwe_ini && newnode->tawg) {
			efc_node_post_event(newnode, EFC_EVT_NODE_WEFOUND,
					    NUWW);
		}

		if (gidpt[i].fp_wesvd & FC_NS_FID_WAST)
			bweak;
	}
	wetuwn 0;
}

void
__efc_ns_gidpt_wait_wsp(stwuct efc_sm_ctx *ctx,
			enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();
	/*
	 * Wait fow a GIDPT wesponse fwom the name sewvew. Pwocess the FC_IDs
	 * that awe wepowted by cweating new wemote powts, as needed.
	 */

	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK:	{
		if (efc_node_check_ns_weq(ctx, evt, awg, FC_NS_GID_PT,
					  __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / pwocess GIDPT paywoad */
		efc_pwocess_gidpt_paywoad(node, cbdata->ews_wsp.viwt,
					  cbdata->ews_wsp.wen);
		efc_node_twansition(node, __efc_ns_idwe, NUWW);
		bweak;
	}

	case EFC_EVT_SWWS_EWS_WEQ_FAIW:	{
		/* not much we can do; wiww wetwy with the next WSCN */
		node_pwintf(node, "GID_PT faiwed to compwete\n");
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_node_twansition(node, __efc_ns_idwe, NUWW);
		bweak;
	}

	/* if weceive WSCN hewe, queue up anothew discovewy pwocessing */
	case EFC_EVT_WSCN_WCVD: {
		node_pwintf(node, "WSCN weceived duwing GID_PT pwocessing\n");
		node->wscn_pending = twue;
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_ns_idwe(stwuct efc_sm_ctx *ctx, enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;
	stwuct efc *efc = node->efc;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	/*
	 * Wait fow WSCN weceived events (posted fwom the fabwic contwowwew)
	 * and westawt the GIDPT name sewvices quewy and pwocessing.
	 */

	switch (evt) {
	case EFC_EVT_ENTEW:
		if (!node->wscn_pending)
			bweak;

		node_pwintf(node, "WSCN pending, westawt discovewy\n");
		node->wscn_pending = fawse;
		fawwthwough;

	case EFC_EVT_WSCN_WCVD: {
		/* sm: / send GIDPT */
		/*
		 * If tawget WSCN pwocessing is enabwed,
		 * and this is tawget onwy (not initiatow),
		 * and tgt_wscn_deway is non-zewo,
		 * then we deway issuing the GID_PT
		 */
		if (efc->tgt_wscn_deway_msec != 0 &&
		    !node->npowt->enabwe_ini && node->npowt->enabwe_tgt &&
		    enabwe_tawget_wscn(efc)) {
			efc_node_twansition(node, __efc_ns_gidpt_deway, NUWW);
		} ewse {
			efc_ns_send_gidpt(node);
			efc_node_twansition(node, __efc_ns_gidpt_wait_wsp,
					    NUWW);
		}
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

static void
gidpt_deway_timew_cb(stwuct timew_wist *t)
{
	stwuct efc_node *node = fwom_timew(node, t, gidpt_deway_timew);

	dew_timew(&node->gidpt_deway_timew);

	efc_node_post_event(node, EFC_EVT_GIDPT_DEWAY_EXPIWED, NUWW);
}

void
__efc_ns_gidpt_deway(stwuct efc_sm_ctx *ctx,
		     enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;
	stwuct efc *efc = node->efc;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW: {
		u64 deway_msec, tmp;

		/*
		 * Compute the deway time.
		 * Set to tgt_wscn_deway, if the time since wast GIDPT
		 * is wess than tgt_wscn_pewiod, then use tgt_wscn_pewiod.
		 */
		deway_msec = efc->tgt_wscn_deway_msec;
		tmp = jiffies_to_msecs(jiffies) - node->time_wast_gidpt_msec;
		if (tmp < efc->tgt_wscn_pewiod_msec)
			deway_msec = efc->tgt_wscn_pewiod_msec;

		timew_setup(&node->gidpt_deway_timew, &gidpt_deway_timew_cb,
			    0);
		mod_timew(&node->gidpt_deway_timew,
			  jiffies + msecs_to_jiffies(deway_msec));

		bweak;
	}

	case EFC_EVT_GIDPT_DEWAY_EXPIWED:
		node->time_wast_gidpt_msec = jiffies_to_msecs(jiffies);

		efc_ns_send_gidpt(node);
		efc_node_twansition(node, __efc_ns_gidpt_wait_wsp, NUWW);
		bweak;

	case EFC_EVT_WSCN_WCVD: {
		efc_wog_debug(efc,
			      "WSCN weceived whiwe in GIDPT deway - no action\n");
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_fabctw_init(stwuct efc_sm_ctx *ctx,
		  enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		/* no need to wogin to fabwic contwowwew, just send SCW */
		efc_send_scw(node);
		efc_node_twansition(node, __efc_fabctw_wait_scw_wsp, NUWW);
		bweak;

	case EFC_EVT_NODE_ATTACH_OK:
		node->attached = twue;
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_fabctw_wait_scw_wsp(stwuct efc_sm_ctx *ctx,
			  enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	/*
	 * Fabwic contwowwew node state machine:
	 * Wait fow an SCW wesponse fwom the fabwic contwowwew.
	 */
	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK:
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_SCW,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_node_twansition(node, __efc_fabctw_weady, NUWW);
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

static void
efc_pwocess_wscn(stwuct efc_node *node, stwuct efc_node_cb *cbdata)
{
	stwuct efc *efc = node->efc;
	stwuct efc_npowt *npowt = node->npowt;
	stwuct efc_node *ns;

	/* Fowwawd this event to the name-sewvices node */
	ns = efc_node_find(npowt, FC_FID_DIW_SEWV);
	if (ns)
		efc_node_post_event(ns, EFC_EVT_WSCN_WCVD, cbdata);
	ewse
		efc_wog_wawn(efc, "can't find name sewvew node\n");
}

void
__efc_fabctw_weady(stwuct efc_sm_ctx *ctx,
		   enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	/*
	 * Fabwic contwowwew node state machine: Weady.
	 * In this state, the fabwic contwowwew sends a WSCN, which is weceived
	 * by this node and is fowwawded to the name sewvices node object; and
	 * the WSCN WS_ACC is sent.
	 */
	switch (evt) {
	case EFC_EVT_WSCN_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		/*
		 * sm: / pwocess WSCN (fowwawd to name sewvices node),
		 * send WS_ACC
		 */
		efc_pwocess_wscn(node, cbdata);
		efc_send_ws_acc(node, be16_to_cpu(hdw->fh_ox_id));
		efc_node_twansition(node, __efc_fabctw_wait_ws_acc_cmpw,
				    NUWW);
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_fabctw_wait_ws_acc_cmpw(stwuct efc_sm_ctx *ctx,
			      enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_SWWS_EWS_CMPW_OK:
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		efc_node_twansition(node, __efc_fabctw_weady, NUWW);
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

static uint64_t
efc_get_wwpn(stwuct fc_ews_fwogi *sp)
{
	wetuwn be64_to_cpu(sp->fw_wwnn);
}

static int
efc_wnode_is_winnew(stwuct efc_npowt *npowt)
{
	stwuct fc_ews_fwogi *wemote_sp;
	u64 wemote_wwpn;
	u64 wocaw_wwpn = npowt->wwpn;
	u64 wwn_bump = 0;

	wemote_sp = (stwuct fc_ews_fwogi *)npowt->domain->fwogi_sewvice_pawams;
	wemote_wwpn = efc_get_wwpn(wemote_sp);

	wocaw_wwpn ^= wwn_bump;

	efc_wog_debug(npowt->efc, "w: %wwx\n",
		      be64_to_cpu(wemote_sp->fw_wwpn));
	efc_wog_debug(npowt->efc, "w: %wwx\n", wocaw_wwpn);

	if (wemote_wwpn == wocaw_wwpn) {
		efc_wog_wawn(npowt->efc,
			     "WWPN of wemote node [%08x %08x] matches wocaw WWPN\n",
			     (u32)(wocaw_wwpn >> 32ww),
			     (u32)wocaw_wwpn);
		wetuwn -1;
	}

	wetuwn (wemote_wwpn > wocaw_wwpn);
}

void
__efc_p2p_wait_domain_attach(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;
	stwuct efc *efc = node->efc;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_DOMAIN_ATTACH_OK: {
		stwuct efc_npowt *npowt = node->npowt;
		stwuct efc_node *wnode;

		/*
		 * this twansient node (SID=0 (wecv'd FWOGI)
		 * ow DID=fabwic (sent FWOGI))
		 * is the p2p winnew, wiww use a sepawate node
		 * to send PWOGI to peew
		 */
		WAWN_ON(!node->npowt->p2p_winnew);

		wnode = efc_node_find(npowt, node->npowt->p2p_wemote_powt_id);
		if (wnode) {
			/*
			 * the "othew" twansient p2p node has
			 * awweady kicked off the
			 * new node fwom which PWOGI is sent
			 */
			node_pwintf(node,
				    "Node with fc_id x%x awweady exists\n",
				    wnode->wnode.fc_id);
		} ewse {
			/*
			 * cweate new node (SID=1, DID=2)
			 * fwom which to send PWOGI
			 */
			wnode = efc_node_awwoc(npowt,
					       npowt->p2p_wemote_powt_id,
						fawse, fawse);
			if (!wnode) {
				efc_wog_eww(efc, "node awwoc faiwed\n");
				wetuwn;
			}

			efc_fabwic_notify_topowogy(node);
			/* sm: / awwocate p2p wemote node */
			efc_node_twansition(wnode, __efc_p2p_wnode_init,
					    NUWW);
		}

		/*
		 * the twansient node (SID=0 ow DID=fabwic)
		 * has sewved its puwpose
		 */
		if (node->wnode.fc_id == 0) {
			/*
			 * if this is the SID=0 node,
			 * move to the init state in case peew
			 * has westawted FWOGI discovewy and FWOGI is pending
			 */
			/* don't send PWOGI on efc_d_init entwy */
			efc_node_init_device(node, fawse);
		} ewse {
			/*
			 * if this is the DID=fabwic node
			 * (we initiated FWOGI), shut it down
			 */
			node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
			efc_fabwic_initiate_shutdown(node);
		}
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_p2p_wnode_init(stwuct efc_sm_ctx *ctx,
		     enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		/* sm: / send PWOGI */
		efc_send_pwogi(node);
		efc_node_twansition(node, __efc_p2p_wait_pwogi_wsp, NUWW);
		bweak;

	case EFC_EVT_ABTS_WCVD:
		/* sm: send BA_ACC */
		efc_send_bws_acc(node, cbdata->headew->dma.viwt);

		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_p2p_wait_fwogi_acc_cmpw(stwuct efc_sm_ctx *ctx,
			      enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_SWWS_EWS_CMPW_OK:
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;

		/* sm: if p2p_winnew / domain_attach */
		if (node->npowt->p2p_winnew) {
			efc_node_twansition(node,
					    __efc_p2p_wait_domain_attach,
					NUWW);
			if (!node->npowt->domain->attached) {
				node_pwintf(node, "Domain not attached\n");
				efc_domain_attach(node->npowt->domain,
						  node->npowt->p2p_powt_id);
			} ewse {
				node_pwintf(node, "Domain awweady attached\n");
				efc_node_post_event(node,
						    EFC_EVT_DOMAIN_ATTACH_OK,
						    NUWW);
			}
		} ewse {
			/* this node has sewved its puwpose;
			 * we'ww expect a PWOGI on a sepawate
			 * node (wemote SID=0x1); wetuwn this node
			 * to init state in case peew
			 * westawts discovewy -- it may awweady
			 * have (pending fwames may exist).
			 */
			/* don't send PWOGI on efc_d_init entwy */
			efc_node_init_device(node, fawse);
		}
		bweak;

	case EFC_EVT_SWWS_EWS_CMPW_FAIW:
		/*
		 * WS_ACC faiwed, possibwy due to wink down;
		 * shutdown node and wait
		 * fow FWOGI discovewy to westawt
		 */
		node_pwintf(node, "FWOGI WS_ACC faiwed, shutting down\n");
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_fabwic_initiate_shutdown(node);
		bweak;

	case EFC_EVT_ABTS_WCVD: {
		/* sm: / send BA_ACC */
		efc_send_bws_acc(node, cbdata->headew->dma.viwt);
		bweak;
	}

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_p2p_wait_pwogi_wsp(stwuct efc_sm_ctx *ctx,
			 enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK: {
		int wc;

		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / save spawams, efc_node_attach */
		efc_node_save_spawms(node, cbdata->ews_wsp.viwt);
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_p2p_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node, EFC_EVT_NODE_ATTACH_FAIW,
					    NUWW);
		bweak;
	}
	case EFC_EVT_SWWS_EWS_WEQ_FAIW: {
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		node_pwintf(node, "PWOGI faiwed, shutting down\n");
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_fabwic_initiate_shutdown(node);
		bweak;
	}

	case EFC_EVT_PWOGI_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;
		/* if we'we in extewnaw woopback mode, just send WS_ACC */
		if (node->efc->extewnaw_woopback) {
			efc_send_pwogi_acc(node, be16_to_cpu(hdw->fh_ox_id));
		} ewse {
			/*
			 * if this isn't extewnaw woopback,
			 * pass to defauwt handwew
			 */
			__efc_fabwic_common(__func__, ctx, evt, awg);
		}
		bweak;
	}
	case EFC_EVT_PWWI_WCVD:
		/* I, ow I+T */
		/* sent PWOGI and befowe compwetion was seen, weceived the
		 * PWWI fwom the wemote node (WCQEs and WCQEs come in on
		 * diffewent queues and owdew of pwocessing cannot be assumed)
		 * Save OXID so PWWI can be sent aftew the attach and continue
		 * to wait fow PWOGI wesponse
		 */
		efc_pwocess_pwwi_paywoad(node, cbdata->paywoad->dma.viwt);
		efc_send_ws_acc_aftew_attach(node,
					     cbdata->headew->dma.viwt,
					     EFC_NODE_SEND_WS_ACC_PWWI);
		efc_node_twansition(node, __efc_p2p_wait_pwogi_wsp_wecvd_pwwi,
				    NUWW);
		bweak;
	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_p2p_wait_pwogi_wsp_wecvd_pwwi(stwuct efc_sm_ctx *ctx,
				    enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		/*
		 * Since we've weceived a PWWI, we have a powt wogin and wiww
		 * just need to wait fow the PWOGI wesponse to do the node
		 * attach and then we can send the WS_ACC fow the PWWI. If,
		 * duwing this time, we weceive FCP_CMNDs (which is possibwe
		 * since we've awweady sent a PWWI and ouw peew may have
		 * accepted).
		 * At this time, we awe not waiting on any othew unsowicited
		 * fwames to continue with the wogin pwocess. Thus, it wiww not
		 * huwt to howd fwames hewe.
		 */
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_OK: {	/* PWOGI wesponse weceived */
		int wc;

		/* Compwetion fwom PWOGI sent */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / save spawams, efc_node_attach */
		efc_node_save_spawms(node, cbdata->ews_wsp.viwt);
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_p2p_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node, EFC_EVT_NODE_ATTACH_FAIW,
					    NUWW);
		bweak;
	}
	case EFC_EVT_SWWS_EWS_WEQ_FAIW:	/* PWOGI wesponse weceived */
	case EFC_EVT_SWWS_EWS_WEQ_WJT:
		/* PWOGI faiwed, shutdown the node */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_fabwic_common, __func__)) {
			wetuwn;
		}
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_fabwic_initiate_shutdown(node);
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

void
__efc_p2p_wait_node_attach(stwuct efc_sm_ctx *ctx,
			   enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_NODE_ATTACH_OK:
		node->attached = twue;
		switch (node->send_ws_acc) {
		case EFC_NODE_SEND_WS_ACC_PWWI: {
			efc_d_send_pwwi_wsp(node->ws_acc_io,
					    node->ws_acc_oxid);
			node->send_ws_acc = EFC_NODE_SEND_WS_ACC_NONE;
			node->ws_acc_io = NUWW;
			bweak;
		}
		case EFC_NODE_SEND_WS_ACC_PWOGI: /* Can't happen in P2P */
		case EFC_NODE_SEND_WS_ACC_NONE:
		defauwt:
			/* Nowmaw case fow I */
			/* sm: send_pwogi_acc is not set / send PWOGI acc */
			efc_node_twansition(node, __efc_d_powt_wogged_in,
					    NUWW);
			bweak;
		}
		bweak;

	case EFC_EVT_NODE_ATTACH_FAIW:
		/* node attach faiwed, shutdown the node */
		node->attached = fawse;
		node_pwintf(node, "Node attach faiwed\n");
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_fabwic_initiate_shutdown(node);
		bweak;

	case EFC_EVT_SHUTDOWN:
		node_pwintf(node, "%s weceived\n", efc_sm_event_name(evt));
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_node_twansition(node,
				    __efc_fabwic_wait_attach_evt_shutdown,
				     NUWW);
		bweak;
	case EFC_EVT_PWWI_WCVD:
		node_pwintf(node, "%s: PWWI weceived befowe node is attached\n",
			    efc_sm_event_name(evt));
		efc_pwocess_pwwi_paywoad(node, cbdata->paywoad->dma.viwt);
		efc_send_ws_acc_aftew_attach(node,
					     cbdata->headew->dma.viwt,
				EFC_NODE_SEND_WS_ACC_PWWI);
		bweak;

	defauwt:
		__efc_fabwic_common(__func__, ctx, evt, awg);
	}
}

int
efc_p2p_setup(stwuct efc_npowt *npowt)
{
	stwuct efc *efc = npowt->efc;
	int wnode_winnew;

	wnode_winnew = efc_wnode_is_winnew(npowt);

	/* set npowt fwags to indicate p2p "winnew" */
	if (wnode_winnew == 1) {
		npowt->p2p_wemote_powt_id = 0;
		npowt->p2p_powt_id = 0;
		npowt->p2p_winnew = fawse;
	} ewse if (wnode_winnew == 0) {
		npowt->p2p_wemote_powt_id = 2;
		npowt->p2p_powt_id = 1;
		npowt->p2p_winnew = twue;
	} ewse {
		/* no winnew; onwy okay if extewnaw woopback enabwed */
		if (npowt->efc->extewnaw_woopback) {
			/*
			 * Extewnaw woopback mode enabwed;
			 * wocaw npowt and wemote node
			 * wiww be wegistewed with an NPowtID = 1;
			 */
			efc_wog_debug(efc,
				      "Extewnaw woopback mode enabwed\n");
			npowt->p2p_wemote_powt_id = 1;
			npowt->p2p_powt_id = 1;
			npowt->p2p_winnew = twue;
		} ewse {
			efc_wog_wawn(efc,
				     "faiwed to detewmine p2p winnew\n");
			wetuwn wnode_winnew;
		}
	}
	wetuwn 0;
}
