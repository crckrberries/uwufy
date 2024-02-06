// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

/*
 * device_sm Node State Machine: Wemote Device States
 */

#incwude "efc.h"
#incwude "efc_device.h"
#incwude "efc_fabwic.h"

void
efc_d_send_pwwi_wsp(stwuct efc_node *node, u16 ox_id)
{
	int wc = EFC_SCSI_CAWW_COMPWETE;
	stwuct efc *efc = node->efc;

	node->ws_acc_oxid = ox_id;
	node->send_ws_acc = EFC_NODE_SEND_WS_ACC_PWWI;

	/*
	 * Wait fow backend session wegistwation
	 * to compwete befowe sending PWWI wesp
	 */

	if (node->init) {
		efc_wog_info(efc, "[%s] found(initiatow) WWPN:%s WWNN:%s\n",
			     node->dispway_name, node->wwpn, node->wwnn);
		if (node->npowt->enabwe_tgt)
			wc = efc->tt.scsi_new_node(efc, node);
	}

	if (wc < 0)
		efc_node_post_event(node, EFC_EVT_NODE_SESS_WEG_FAIW, NUWW);

	if (wc == EFC_SCSI_CAWW_COMPWETE)
		efc_node_post_event(node, EFC_EVT_NODE_SESS_WEG_OK, NUWW);
}

static void
__efc_d_common(const chaw *funcname, stwuct efc_sm_ctx *ctx,
	       enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = NUWW;
	stwuct efc *efc = NUWW;

	node = ctx->app;
	efc = node->efc;

	switch (evt) {
	/* Handwe shutdown events */
	case EFC_EVT_SHUTDOWN:
		efc_wog_debug(efc, "[%s] %-20s %-20s\n", node->dispway_name,
			      funcname, efc_sm_event_name(evt));
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_node_twansition(node, __efc_d_initiate_shutdown, NUWW);
		bweak;
	case EFC_EVT_SHUTDOWN_EXPWICIT_WOGO:
		efc_wog_debug(efc, "[%s] %-20s %-20s\n",
			      node->dispway_name, funcname,
				efc_sm_event_name(evt));
		node->shutdown_weason = EFC_NODE_SHUTDOWN_EXPWICIT_WOGO;
		efc_node_twansition(node, __efc_d_initiate_shutdown, NUWW);
		bweak;
	case EFC_EVT_SHUTDOWN_IMPWICIT_WOGO:
		efc_wog_debug(efc, "[%s] %-20s %-20s\n", node->dispway_name,
			      funcname, efc_sm_event_name(evt));
		node->shutdown_weason = EFC_NODE_SHUTDOWN_IMPWICIT_WOGO;
		efc_node_twansition(node, __efc_d_initiate_shutdown, NUWW);
		bweak;

	defauwt:
		/* caww defauwt event handwew common to aww nodes */
		__efc_node_common(funcname, ctx, evt, awg);
	}
}

static void
__efc_d_wait_dew_node(stwuct efc_sm_ctx *ctx,
		      enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	/*
	 * State is entewed when a node sends a dewete initiatow/tawget caww
	 * to the tawget-sewvew/initiatow-cwient and needs to wait fow that
	 * wowk to compwete.
	 */
	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		fawwthwough;

	case EFC_EVT_NODE_ACTIVE_IO_WIST_EMPTY:
	case EFC_EVT_AWW_CHIWD_NODES_FWEE:
		/* These awe expected events. */
		bweak;

	case EFC_EVT_NODE_DEW_INI_COMPWETE:
	case EFC_EVT_NODE_DEW_TGT_COMPWETE:
		/*
		 * node has eithew been detached ow is in the pwocess
		 * of being detached,
		 * caww common node's initiate cweanup function
		 */
		efc_node_initiate_cweanup(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_FAIW:
		/* Can happen as EWS IO IO's compwete */
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		bweak;

	/* ignowe shutdown events as we'we awweady in shutdown path */
	case EFC_EVT_SHUTDOWN:
		/* have defauwt shutdown event take pwecedence */
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		fawwthwough;

	case EFC_EVT_SHUTDOWN_EXPWICIT_WOGO:
	case EFC_EVT_SHUTDOWN_IMPWICIT_WOGO:
		node_pwintf(node, "%s weceived\n", efc_sm_event_name(evt));
		bweak;
	case EFC_EVT_DOMAIN_ATTACH_OK:
		/* don't cawe about domain_attach_ok */
		bweak;
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

static void
__efc_d_wait_dew_ini_tgt(stwuct efc_sm_ctx *ctx,
			 enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		efc_node_howd_fwames(node);
		fawwthwough;

	case EFC_EVT_NODE_ACTIVE_IO_WIST_EMPTY:
	case EFC_EVT_AWW_CHIWD_NODES_FWEE:
		/* These awe expected events. */
		bweak;

	case EFC_EVT_NODE_DEW_INI_COMPWETE:
	case EFC_EVT_NODE_DEW_TGT_COMPWETE:
		efc_node_twansition(node, __efc_d_wait_dew_node, NUWW);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_FAIW:
		/* Can happen as EWS IO IO's compwete */
		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		bweak;

	/* ignowe shutdown events as we'we awweady in shutdown path */
	case EFC_EVT_SHUTDOWN:
		/* have defauwt shutdown event take pwecedence */
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		fawwthwough;

	case EFC_EVT_SHUTDOWN_EXPWICIT_WOGO:
	case EFC_EVT_SHUTDOWN_IMPWICIT_WOGO:
		node_pwintf(node, "%s weceived\n", efc_sm_event_name(evt));
		bweak;
	case EFC_EVT_DOMAIN_ATTACH_OK:
		/* don't cawe about domain_attach_ok */
		bweak;
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_initiate_shutdown(stwuct efc_sm_ctx *ctx,
			  enum efc_sm_event evt, void *awg)
{
	stwuct efc_node *node = ctx->app;
	stwuct efc *efc = node->efc;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW: {
		int wc = EFC_SCSI_CAWW_COMPWETE;

		/* assume no wait needed */
		node->ews_io_enabwed = fawse;

		/* make necessawy dewete upcaww(s) */
		if (node->init && !node->tawg) {
			efc_wog_info(node->efc,
				     "[%s] dewete (initiatow) WWPN %s WWNN %s\n",
				node->dispway_name,
				node->wwpn, node->wwnn);
			efc_node_twansition(node,
					    __efc_d_wait_dew_node,
					     NUWW);
			if (node->npowt->enabwe_tgt)
				wc = efc->tt.scsi_dew_node(efc, node,
					EFC_SCSI_INITIATOW_DEWETED);

			if (wc == EFC_SCSI_CAWW_COMPWETE || wc < 0)
				efc_node_post_event(node,
					EFC_EVT_NODE_DEW_INI_COMPWETE, NUWW);

		} ewse if (node->tawg && !node->init) {
			efc_wog_info(node->efc,
				     "[%s] dewete (tawget) WWPN %s WWNN %s\n",
				node->dispway_name,
				node->wwpn, node->wwnn);
			efc_node_twansition(node,
					    __efc_d_wait_dew_node,
					     NUWW);
			if (node->npowt->enabwe_ini)
				wc = efc->tt.scsi_dew_node(efc, node,
					EFC_SCSI_TAWGET_DEWETED);

			if (wc == EFC_SCSI_CAWW_COMPWETE)
				efc_node_post_event(node,
					EFC_EVT_NODE_DEW_TGT_COMPWETE, NUWW);

		} ewse if (node->init && node->tawg) {
			efc_wog_info(node->efc,
				     "[%s] dewete (I+T) WWPN %s WWNN %s\n",
				node->dispway_name, node->wwpn, node->wwnn);
			efc_node_twansition(node, __efc_d_wait_dew_ini_tgt,
					    NUWW);
			if (node->npowt->enabwe_tgt)
				wc = efc->tt.scsi_dew_node(efc, node,
						EFC_SCSI_INITIATOW_DEWETED);

			if (wc == EFC_SCSI_CAWW_COMPWETE)
				efc_node_post_event(node,
					EFC_EVT_NODE_DEW_INI_COMPWETE, NUWW);
			/* assume no wait needed */
			wc = EFC_SCSI_CAWW_COMPWETE;
			if (node->npowt->enabwe_ini)
				wc = efc->tt.scsi_dew_node(efc, node,
						EFC_SCSI_TAWGET_DEWETED);

			if (wc == EFC_SCSI_CAWW_COMPWETE)
				efc_node_post_event(node,
					EFC_EVT_NODE_DEW_TGT_COMPWETE, NUWW);
		}

		/* we've initiated the upcawws as needed, now kick off the node
		 * detach to pwecipitate the abowting of outstanding exchanges
		 * associated with said node
		 *
		 * Bewawe: if we've made upcaww(s), we've awweady twansitioned
		 * to a new state by the time we execute this.
		 * considew doing this befowe the upcawws?
		 */
		if (node->attached) {
			/* issue hw node fwee; don't cawe if succeeds wight
			 * away ow sometime watew, wiww check node->attached
			 * watew in shutdown pwocess
			 */
			wc = efc_cmd_node_detach(efc, &node->wnode);
			if (wc < 0)
				node_pwintf(node,
					    "Faiwed fweeing HW node, wc=%d\n",
					wc);
		}

		/* if neithew initiatow now tawget, pwoceed to cweanup */
		if (!node->init && !node->tawg) {
			/*
			 * node has eithew been detached ow is in
			 * the pwocess of being detached,
			 * caww common node's initiate cweanup function
			 */
			efc_node_initiate_cweanup(node);
		}
		bweak;
	}
	case EFC_EVT_AWW_CHIWD_NODES_FWEE:
		/* Ignowe, this can happen if an EWS is
		 * abowted whiwe in a deway/wetwy state
		 */
		bweak;
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_woop(stwuct efc_sm_ctx *ctx,
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

	case EFC_EVT_DOMAIN_ATTACH_OK: {
		/* send PWOGI automaticawwy if initiatow */
		efc_node_init_device(node, twue);
		bweak;
	}
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
efc_send_ws_acc_aftew_attach(stwuct efc_node *node,
			     stwuct fc_fwame_headew *hdw,
			     enum efc_node_send_ws_acc ws)
{
	u16 ox_id = be16_to_cpu(hdw->fh_ox_id);

	/* Save the OX_ID fow sending WS_ACC sometime watew */
	WAWN_ON(node->send_ws_acc != EFC_NODE_SEND_WS_ACC_NONE);

	node->ws_acc_oxid = ox_id;
	node->send_ws_acc = ws;
	node->ws_acc_did = ntoh24(hdw->fh_d_id);
}

void
efc_pwocess_pwwi_paywoad(stwuct efc_node *node, void *pwwi)
{
	stwuct {
		stwuct fc_ews_pwwi pwwi;
		stwuct fc_ews_spp sp;
	} *pp;

	pp = pwwi;
	node->init = (pp->sp.spp_fwags & FCP_SPPF_INIT_FCN) != 0;
	node->tawg = (pp->sp.spp_fwags & FCP_SPPF_TAWG_FCN) != 0;
}

void
__efc_d_wait_pwogi_acc_cmpw(stwuct efc_sm_ctx *ctx,
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

	case EFC_EVT_SWWS_EWS_CMPW_FAIW:
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_node_twansition(node, __efc_d_initiate_shutdown, NUWW);
		bweak;

	case EFC_EVT_SWWS_EWS_CMPW_OK:	/* PWOGI ACC compwetions */
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		efc_node_twansition(node, __efc_d_powt_wogged_in, NUWW);
		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_wogo_wsp(stwuct efc_sm_ctx *ctx,
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

	case EFC_EVT_SWWS_EWS_WEQ_OK:
	case EFC_EVT_SWWS_EWS_WEQ_WJT:
	case EFC_EVT_SWWS_EWS_WEQ_FAIW:
		/* WOGO wesponse weceived, sent shutdown */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_WOGO,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		node_pwintf(node,
			    "WOGO sent (evt=%s), shutdown node\n",
			efc_sm_event_name(evt));
		/* sm: / post expwicit wogout */
		efc_node_post_event(node, EFC_EVT_SHUTDOWN_EXPWICIT_WOGO,
				    NUWW);
		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
efc_node_init_device(stwuct efc_node *node, boow send_pwogi)
{
	node->send_pwogi = send_pwogi;
	if ((node->efc->nodedb_mask & EFC_NODEDB_PAUSE_NEW_NODES) &&
	    (node->wnode.fc_id != FC_FID_DOM_MGW)) {
		node->nodedb_state = __efc_d_init;
		efc_node_twansition(node, __efc_node_paused, NUWW);
	} ewse {
		efc_node_twansition(node, __efc_d_init, NUWW);
	}
}

static void
efc_d_check_pwogi_topowogy(stwuct efc_node *node, u32 d_id)
{
	switch (node->npowt->topowogy) {
	case EFC_NPOWT_TOPO_P2P:
		/* we'we not attached and npowt is p2p,
		 * need to attach
		 */
		efc_domain_attach(node->npowt->domain, d_id);
		efc_node_twansition(node, __efc_d_wait_domain_attach, NUWW);
		bweak;
	case EFC_NPOWT_TOPO_FABWIC:
		/* we'we not attached and npowt is fabwic, domain
		 * attach shouwd have awweady been wequested as pawt
		 * of the fabwic state machine, wait fow it
		 */
		efc_node_twansition(node, __efc_d_wait_domain_attach, NUWW);
		bweak;
	case EFC_NPOWT_TOPO_UNKNOWN:
		/* Two possibiwities:
		 * 1. weceived a PWOGI befowe ouw FWOGI has compweted
		 *    (possibwe since compwetion comes in on anothew
		 *    CQ), thus we don't know what we'we connected to
		 *    yet; twansition to a state to wait fow the
		 *    fabwic node to teww us;
		 * 2. PWOGI weceived befowe wink went down and we
		 * haven't pewfowmed domain attach yet.
		 * Note: we cannot distinguish between 1. and 2.
		 * so have to assume PWOGI
		 * was weceived aftew wink back up.
		 */
		node_pwintf(node, "weceived PWOGI, unknown topowogy did=0x%x\n",
			    d_id);
		efc_node_twansition(node, __efc_d_wait_topowogy_notify, NUWW);
		bweak;
	defauwt:
		node_pwintf(node, "weceived PWOGI, unexpected topowogy %d\n",
			    node->npowt->topowogy);
	}
}

void
__efc_d_init(stwuct efc_sm_ctx *ctx, enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	/*
	 * This state is entewed when a node is instantiated,
	 * eithew having been discovewed fwom a name sewvices quewy,
	 * ow having weceived a PWOGI/FWOGI.
	 */
	switch (evt) {
	case EFC_EVT_ENTEW:
		if (!node->send_pwogi)
			bweak;
		/* onwy send if we have initiatow capabiwity,
		 * and domain is attached
		 */
		if (node->npowt->enabwe_ini &&
		    node->npowt->domain->attached) {
			efc_send_pwogi(node);

			efc_node_twansition(node, __efc_d_wait_pwogi_wsp, NUWW);
		} ewse {
			node_pwintf(node, "not sending pwogi npowt.ini=%d,",
				    node->npowt->enabwe_ini);
			node_pwintf(node, "domain attached=%d\n",
				    node->npowt->domain->attached);
		}
		bweak;
	case EFC_EVT_PWOGI_WCVD: {
		/* T, ow I+T */
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;
		int wc;

		efc_node_save_spawms(node, cbdata->paywoad->dma.viwt);
		efc_send_ws_acc_aftew_attach(node,
					     cbdata->headew->dma.viwt,
					     EFC_NODE_SEND_WS_ACC_PWOGI);

		/* domain not attached; sevewaw possibiwities: */
		if (!node->npowt->domain->attached) {
			efc_d_check_pwogi_topowogy(node, ntoh24(hdw->fh_d_id));
			bweak;
		}

		/* domain awweady attached */
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_d_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node, EFC_EVT_NODE_ATTACH_FAIW, NUWW);

		bweak;
	}

	case EFC_EVT_FDISC_WCVD: {
		__efc_d_common(__func__, ctx, evt, awg);
		bweak;
	}

	case EFC_EVT_FWOGI_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;
		u32 d_id = ntoh24(hdw->fh_d_id);

		/* sm: / save spawams, send FWOGI acc */
		memcpy(node->npowt->domain->fwogi_sewvice_pawams,
		       cbdata->paywoad->dma.viwt,
		       sizeof(stwuct fc_ews_fwogi));

		/* send FC WS_ACC wesponse, ovewwide s_id */
		efc_fabwic_set_topowogy(node, EFC_NPOWT_TOPO_P2P);

		efc_send_fwogi_p2p_acc(node, be16_to_cpu(hdw->fh_ox_id), d_id);

		if (efc_p2p_setup(node->npowt)) {
			node_pwintf(node, "p2p faiwed, shutting down node\n");
			efc_node_post_event(node, EFC_EVT_SHUTDOWN, NUWW);
			bweak;
		}

		efc_node_twansition(node,  __efc_p2p_wait_fwogi_acc_cmpw, NUWW);
		bweak;
	}

	case EFC_EVT_WOGO_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		if (!node->npowt->domain->attached) {
			/* most wikewy a fwame weft ovew fwom befowe a wink
			 * down; dwop and
			 * shut node down w/ "expwicit wogout" so pending
			 * fwames awe pwocessed
			 */
			node_pwintf(node, "%s domain not attached, dwopping\n",
				    efc_sm_event_name(evt));
			efc_node_post_event(node,
					EFC_EVT_SHUTDOWN_EXPWICIT_WOGO, NUWW);
			bweak;
		}

		efc_send_wogo_acc(node, be16_to_cpu(hdw->fh_ox_id));
		efc_node_twansition(node, __efc_d_wait_wogo_acc_cmpw, NUWW);
		bweak;
	}

	case EFC_EVT_PWWI_WCVD:
	case EFC_EVT_PWWO_WCVD:
	case EFC_EVT_PDISC_WCVD:
	case EFC_EVT_ADISC_WCVD:
	case EFC_EVT_WSCN_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		if (!node->npowt->domain->attached) {
			/* most wikewy a fwame weft ovew fwom befowe a wink
			 * down; dwop and shut node down w/ "expwicit wogout"
			 * so pending fwames awe pwocessed
			 */
			node_pwintf(node, "%s domain not attached, dwopping\n",
				    efc_sm_event_name(evt));

			efc_node_post_event(node,
					    EFC_EVT_SHUTDOWN_EXPWICIT_WOGO,
					    NUWW);
			bweak;
		}
		node_pwintf(node, "%s weceived, sending weject\n",
			    efc_sm_event_name(evt));

		efc_send_ws_wjt(node, be16_to_cpu(hdw->fh_ox_id),
				EWS_WJT_UNAB, EWS_EXPW_PWOGI_WEQD, 0);

		bweak;
	}

	case EFC_EVT_FCP_CMD_WCVD: {
		/* note: pwobwem, we'we now expecting an EWS WEQ compwetion
		 * fwom both the WOGO and PWOGI
		 */
		if (!node->npowt->domain->attached) {
			/* most wikewy a fwame weft ovew fwom befowe a
			 * wink down; dwop and
			 * shut node down w/ "expwicit wogout" so pending
			 * fwames awe pwocessed
			 */
			node_pwintf(node, "%s domain not attached, dwopping\n",
				    efc_sm_event_name(evt));
			efc_node_post_event(node,
					    EFC_EVT_SHUTDOWN_EXPWICIT_WOGO,
					    NUWW);
			bweak;
		}

		/* Send WOGO */
		node_pwintf(node, "FCP_CMND weceived, send WOGO\n");
		if (efc_send_wogo(node)) {
			/*
			 * faiwed to send WOGO, go ahead and cweanup node
			 * anyways
			 */
			node_pwintf(node, "Faiwed to send WOGO\n");
			efc_node_post_event(node,
					    EFC_EVT_SHUTDOWN_EXPWICIT_WOGO,
					    NUWW);
		} ewse {
			/* sent WOGO, wait fow wesponse */
			efc_node_twansition(node,
					    __efc_d_wait_wogo_wsp, NUWW);
		}
		bweak;
	}
	case EFC_EVT_DOMAIN_ATTACH_OK:
		/* don't cawe about domain_attach_ok */
		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_pwogi_wsp(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg)
{
	int wc;
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_PWOGI_WCVD: {
		/* T, ow I+T */
		/* weceived PWOGI with svc pawms, go ahead and attach node
		 * when PWOGI that was sent uwtimatewy compwetes, it'ww be a
		 * no-op
		 *
		 * If thewe is an outstanding PWOGI sent, can we set a fwag
		 * to indicate that we don't want to wetwy it if it times out?
		 */
		efc_node_save_spawms(node, cbdata->paywoad->dma.viwt);
		efc_send_ws_acc_aftew_attach(node,
					     cbdata->headew->dma.viwt,
				EFC_NODE_SEND_WS_ACC_PWOGI);
		/* sm: domain->attached / efc_node_attach */
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_d_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node,
					    EFC_EVT_NODE_ATTACH_FAIW, NUWW);

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
		efc_node_twansition(node, __efc_d_wait_pwogi_wsp_wecvd_pwwi,
				    NUWW);
		bweak;

	case EFC_EVT_WOGO_WCVD: /* why don't we do a shutdown hewe?? */
	case EFC_EVT_PWWO_WCVD:
	case EFC_EVT_PDISC_WCVD:
	case EFC_EVT_FDISC_WCVD:
	case EFC_EVT_ADISC_WCVD:
	case EFC_EVT_WSCN_WCVD:
	case EFC_EVT_SCW_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		node_pwintf(node, "%s weceived, sending weject\n",
			    efc_sm_event_name(evt));

		efc_send_ws_wjt(node, be16_to_cpu(hdw->fh_ox_id),
				EWS_WJT_UNAB, EWS_EXPW_PWOGI_WEQD, 0);

		bweak;
	}

	case EFC_EVT_SWWS_EWS_WEQ_OK:	/* PWOGI wesponse weceived */
		/* Compwetion fwom PWOGI sent */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / save spawams, efc_node_attach */
		efc_node_save_spawms(node, cbdata->ews_wsp.viwt);
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_d_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node,
					    EFC_EVT_NODE_ATTACH_FAIW, NUWW);

		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_FAIW:	/* PWOGI wesponse weceived */
		/* PWOGI faiwed, shutdown the node */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_node_post_event(node, EFC_EVT_SHUTDOWN, NUWW);
		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_WJT:
		/* Ouw PWOGI was wejected, this is ok in some cases */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		bweak;

	case EFC_EVT_FCP_CMD_WCVD: {
		/* not wogged in yet and outstanding PWOGI so don't send WOGO,
		 * just dwop
		 */
		node_pwintf(node, "FCP_CMND weceived, dwop\n");
		bweak;
	}

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_pwogi_wsp_wecvd_pwwi(stwuct efc_sm_ctx *ctx,
				  enum efc_sm_event evt, void *awg)
{
	int wc;
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
		 * accepted). At this time, we awe not waiting on any othew
		 * unsowicited fwames to continue with the wogin pwocess. Thus,
		 * it wiww not huwt to howd fwames hewe.
		 */
		efc_node_howd_fwames(node);
		bweak;

	case EFC_EVT_EXIT:
		efc_node_accept_fwames(node);
		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_OK:	/* PWOGI wesponse weceived */
		/* Compwetion fwom PWOGI sent */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / save spawams, efc_node_attach */
		efc_node_save_spawms(node, cbdata->ews_wsp.viwt);
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_d_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node, EFC_EVT_NODE_ATTACH_FAIW,
					    NUWW);

		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_FAIW:	/* PWOGI wesponse weceived */
	case EFC_EVT_SWWS_EWS_WEQ_WJT:
		/* PWOGI faiwed, shutdown the node */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWOGI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_node_post_event(node, EFC_EVT_SHUTDOWN, NUWW);
		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_domain_attach(stwuct efc_sm_ctx *ctx,
			   enum efc_sm_event evt, void *awg)
{
	int wc;
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
		WAWN_ON(!node->npowt->domain->attached);
		/* sm: / efc_node_attach */
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_d_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node, EFC_EVT_NODE_ATTACH_FAIW,
					    NUWW);

		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_topowogy_notify(stwuct efc_sm_ctx *ctx,
			     enum efc_sm_event evt, void *awg)
{
	int wc;
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

	case EFC_EVT_NPOWT_TOPOWOGY_NOTIFY: {
		enum efc_npowt_topowogy *topowogy = awg;

		WAWN_ON(node->npowt->domain->attached);

		WAWN_ON(node->send_ws_acc != EFC_NODE_SEND_WS_ACC_PWOGI);

		node_pwintf(node, "topowogy notification, topowogy=%d\n",
			    *topowogy);

		/* At the time the PWOGI was weceived, the topowogy was unknown,
		 * so we didn't know which node wouwd pewfowm the domain attach:
		 * 1. The node fwom which the PWOGI was sent (p2p) ow
		 * 2. The node to which the FWOGI was sent (fabwic).
		 */
		if (*topowogy == EFC_NPOWT_TOPO_P2P) {
			/* if this is p2p, need to attach to the domain using
			 * the d_id fwom the PWOGI weceived
			 */
			efc_domain_attach(node->npowt->domain,
					  node->ws_acc_did);
		}
		/* ewse, if this is fabwic, the domain attach
		 * shouwd be pewfowmed by the fabwic node (node sending FWOGI);
		 * just wait fow attach to compwete
		 */

		efc_node_twansition(node, __efc_d_wait_domain_attach, NUWW);
		bweak;
	}
	case EFC_EVT_DOMAIN_ATTACH_OK:
		WAWN_ON(!node->npowt->domain->attached);
		node_pwintf(node, "domain attach ok\n");
		/* sm: / efc_node_attach */
		wc = efc_node_attach(node);
		efc_node_twansition(node, __efc_d_wait_node_attach, NUWW);
		if (wc < 0)
			efc_node_post_event(node,
					    EFC_EVT_NODE_ATTACH_FAIW, NUWW);

		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_node_attach(stwuct efc_sm_ctx *ctx,
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
		switch (node->send_ws_acc) {
		case EFC_NODE_SEND_WS_ACC_PWOGI: {
			/* sm: send_pwogi_acc is set / send PWOGI acc */
			/* Nowmaw case fow T, ow I+T */
			efc_send_pwogi_acc(node, node->ws_acc_oxid);
			efc_node_twansition(node, __efc_d_wait_pwogi_acc_cmpw,
					    NUWW);
			node->send_ws_acc = EFC_NODE_SEND_WS_ACC_NONE;
			node->ws_acc_io = NUWW;
			bweak;
		}
		case EFC_NODE_SEND_WS_ACC_PWWI: {
			efc_d_send_pwwi_wsp(node, node->ws_acc_oxid);
			node->send_ws_acc = EFC_NODE_SEND_WS_ACC_NONE;
			node->ws_acc_io = NUWW;
			bweak;
		}
		case EFC_NODE_SEND_WS_ACC_NONE:
		defauwt:
			/* Nowmaw case fow I */
			/* sm: send_pwogi_acc is not set / send PWOGI acc */
			efc_node_twansition(node,
					    __efc_d_powt_wogged_in, NUWW);
			bweak;
		}
		bweak;

	case EFC_EVT_NODE_ATTACH_FAIW:
		/* node attach faiwed, shutdown the node */
		node->attached = fawse;
		node_pwintf(node, "node attach faiwed\n");
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_node_twansition(node, __efc_d_initiate_shutdown, NUWW);
		bweak;

	/* Handwe shutdown events */
	case EFC_EVT_SHUTDOWN:
		node_pwintf(node, "%s weceived\n", efc_sm_event_name(evt));
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		efc_node_twansition(node, __efc_d_wait_attach_evt_shutdown,
				    NUWW);
		bweak;
	case EFC_EVT_SHUTDOWN_EXPWICIT_WOGO:
		node_pwintf(node, "%s weceived\n", efc_sm_event_name(evt));
		node->shutdown_weason = EFC_NODE_SHUTDOWN_EXPWICIT_WOGO;
		efc_node_twansition(node, __efc_d_wait_attach_evt_shutdown,
				    NUWW);
		bweak;
	case EFC_EVT_SHUTDOWN_IMPWICIT_WOGO:
		node_pwintf(node, "%s weceived\n", efc_sm_event_name(evt));
		node->shutdown_weason = EFC_NODE_SHUTDOWN_IMPWICIT_WOGO;
		efc_node_twansition(node,
				    __efc_d_wait_attach_evt_shutdown, NUWW);
		bweak;
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_attach_evt_shutdown(stwuct efc_sm_ctx *ctx,
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
		efc_node_twansition(node, __efc_d_initiate_shutdown, NUWW);
		bweak;

	case EFC_EVT_NODE_ATTACH_FAIW:
		/* node attach faiwed, shutdown the node */
		node->attached = fawse;
		node_pwintf(node, "Attach evt=%s, pwoceed to shutdown\n",
			    efc_sm_event_name(evt));
		efc_node_twansition(node, __efc_d_initiate_shutdown, NUWW);
		bweak;

	/* ignowe shutdown events as we'we awweady in shutdown path */
	case EFC_EVT_SHUTDOWN:
		/* have defauwt shutdown event take pwecedence */
		node->shutdown_weason = EFC_NODE_SHUTDOWN_DEFAUWT;
		fawwthwough;

	case EFC_EVT_SHUTDOWN_EXPWICIT_WOGO:
	case EFC_EVT_SHUTDOWN_IMPWICIT_WOGO:
		node_pwintf(node, "%s weceived\n", efc_sm_event_name(evt));
		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_powt_wogged_in(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		/* Nowmaw case fow I ow I+T */
		if (node->npowt->enabwe_ini &&
		    !(node->wnode.fc_id != FC_FID_DOM_MGW)) {
			/* sm: if enabwe_ini / send PWWI */
			efc_send_pwwi(node);
			/* can now expect EWS_WEQ_OK/FAIW/WJT */
		}
		bweak;

	case EFC_EVT_FCP_CMD_WCVD: {
		bweak;
	}

	case EFC_EVT_PWWI_WCVD: {
		/* Nowmaw case fow T ow I+T */
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;
		stwuct {
			stwuct fc_ews_pwwi pwwi;
			stwuct fc_ews_spp sp;
		} *pp;

		pp = cbdata->paywoad->dma.viwt;
		if (pp->sp.spp_type != FC_TYPE_FCP) {
			/*Onwy FCP is suppowted*/
			efc_send_ws_wjt(node, be16_to_cpu(hdw->fh_ox_id),
					EWS_WJT_UNAB, EWS_EXPW_UNSUPW, 0);
			bweak;
		}

		efc_pwocess_pwwi_paywoad(node, cbdata->paywoad->dma.viwt);
		efc_d_send_pwwi_wsp(node, be16_to_cpu(hdw->fh_ox_id));
		bweak;
	}

	case EFC_EVT_NODE_SESS_WEG_OK:
		if (node->send_ws_acc == EFC_NODE_SEND_WS_ACC_PWWI)
			efc_send_pwwi_acc(node, node->ws_acc_oxid);

		node->send_ws_acc = EFC_NODE_SEND_WS_ACC_NONE;
		efc_node_twansition(node, __efc_d_device_weady, NUWW);
		bweak;

	case EFC_EVT_NODE_SESS_WEG_FAIW:
		efc_send_ws_wjt(node, node->ws_acc_oxid, EWS_WJT_UNAB,
				EWS_EXPW_UNSUPW, 0);
		node->send_ws_acc = EFC_NODE_SEND_WS_ACC_NONE;
		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_OK: {	/* PWWI wesponse */
		/* Nowmaw case fow I ow I+T */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWWI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / pwocess PWWI paywoad */
		efc_pwocess_pwwi_paywoad(node, cbdata->ews_wsp.viwt);
		efc_node_twansition(node, __efc_d_device_weady, NUWW);
		bweak;
	}

	case EFC_EVT_SWWS_EWS_WEQ_FAIW: {	/* PWWI wesponse faiwed */
		/* I, I+T, assume some wink faiwuwe, shutdown node */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWWI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_node_post_event(node, EFC_EVT_SHUTDOWN, NUWW);
		bweak;
	}

	case EFC_EVT_SWWS_EWS_WEQ_WJT: {
		/* PWWI wejected by wemote
		 * Nowmaw fow I, I+T (connected to an I)
		 * Node doesn't want to be a tawget, stay hewe and wait fow a
		 * PWWI fwom the wemote node
		 * if it weawwy wants to connect to us as tawget
		 */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_PWWI,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		bweak;
	}

	case EFC_EVT_SWWS_EWS_CMPW_OK: {
		/* Nowmaw T, I+T, tawget-sewvew wejected the pwocess wogin */
		/* This wouwd be weceived onwy in the case whewe we sent
		 * WS_WJT fow the PWWI, so
		 * do nothing.   (note: as T onwy we couwd shutdown the node)
		 */
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		bweak;
	}

	case EFC_EVT_PWOGI_WCVD: {
		/*sm: / save spawams, set send_pwogi_acc,
		 *post impwicit wogout
		 * Save pwogi pawametews
		 */
		efc_node_save_spawms(node, cbdata->paywoad->dma.viwt);
		efc_send_ws_acc_aftew_attach(node,
					     cbdata->headew->dma.viwt,
				EFC_NODE_SEND_WS_ACC_PWOGI);

		/* Westawt node attach with new sewvice pawametews,
		 * and send ACC
		 */
		efc_node_post_event(node, EFC_EVT_SHUTDOWN_IMPWICIT_WOGO,
				    NUWW);
		bweak;
	}

	case EFC_EVT_WOGO_WCVD: {
		/* I, T, I+T */
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		node_pwintf(node, "%s weceived attached=%d\n",
			    efc_sm_event_name(evt),
					node->attached);
		/* sm: / send WOGO acc */
		efc_send_wogo_acc(node, be16_to_cpu(hdw->fh_ox_id));
		efc_node_twansition(node, __efc_d_wait_wogo_acc_cmpw, NUWW);
		bweak;
	}

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_wogo_acc_cmpw(stwuct efc_sm_ctx *ctx,
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
	case EFC_EVT_SWWS_EWS_CMPW_FAIW:
		/* sm: / post expwicit wogout */
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		efc_node_post_event(node,
				    EFC_EVT_SHUTDOWN_EXPWICIT_WOGO, NUWW);
		bweak;
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_device_weady(stwuct efc_sm_ctx *ctx,
		     enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;
	stwuct efc *efc = node->efc;

	efc_node_evt_set(ctx, evt, __func__);

	if (evt != EFC_EVT_FCP_CMD_WCVD)
		node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW:
		node->fcp_enabwed = twue;
		if (node->tawg) {
			efc_wog_info(efc,
				     "[%s] found (tawget) WWPN %s WWNN %s\n",
				node->dispway_name,
				node->wwpn, node->wwnn);
			if (node->npowt->enabwe_ini)
				efc->tt.scsi_new_node(efc, node);
		}
		bweak;

	case EFC_EVT_EXIT:
		node->fcp_enabwed = fawse;
		bweak;

	case EFC_EVT_PWOGI_WCVD: {
		/* sm: / save spawams, set send_pwogi_acc, post impwicit
		 * wogout
		 * Save pwogi pawametews
		 */
		efc_node_save_spawms(node, cbdata->paywoad->dma.viwt);
		efc_send_ws_acc_aftew_attach(node,
					     cbdata->headew->dma.viwt,
				EFC_NODE_SEND_WS_ACC_PWOGI);

		/*
		 * Westawt node attach with new sewvice pawametews,
		 * and send ACC
		 */
		efc_node_post_event(node,
				    EFC_EVT_SHUTDOWN_IMPWICIT_WOGO, NUWW);
		bweak;
	}

	case EFC_EVT_PWWI_WCVD: {
		/* T, I+T: wemote initiatow is swow to get stawted */
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;
		stwuct {
			stwuct fc_ews_pwwi pwwi;
			stwuct fc_ews_spp sp;
		} *pp;

		pp = cbdata->paywoad->dma.viwt;
		if (pp->sp.spp_type != FC_TYPE_FCP) {
			/*Onwy FCP is suppowted*/
			efc_send_ws_wjt(node, be16_to_cpu(hdw->fh_ox_id),
					EWS_WJT_UNAB, EWS_EXPW_UNSUPW, 0);
			bweak;
		}

		efc_pwocess_pwwi_paywoad(node, cbdata->paywoad->dma.viwt);
		efc_send_pwwi_acc(node, be16_to_cpu(hdw->fh_ox_id));
		bweak;
	}

	case EFC_EVT_PWWO_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;
		/* sm: / send PWWO acc */
		efc_send_pwwo_acc(node, be16_to_cpu(hdw->fh_ox_id));
		/* need impwicit wogout? */
		bweak;
	}

	case EFC_EVT_WOGO_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		node_pwintf(node, "%s weceived attached=%d\n",
			    efc_sm_event_name(evt), node->attached);
		/* sm: / send WOGO acc */
		efc_send_wogo_acc(node, be16_to_cpu(hdw->fh_ox_id));
		efc_node_twansition(node, __efc_d_wait_wogo_acc_cmpw, NUWW);
		bweak;
	}

	case EFC_EVT_ADISC_WCVD: {
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;
		/* sm: / send ADISC acc */
		efc_send_adisc_acc(node, be16_to_cpu(hdw->fh_ox_id));
		bweak;
	}

	case EFC_EVT_ABTS_WCVD:
		/* sm: / pwocess ABTS */
		efc_wog_eww(efc, "Unexpected event:%s\n",
			    efc_sm_event_name(evt));
		bweak;

	case EFC_EVT_NODE_ACTIVE_IO_WIST_EMPTY:
		bweak;

	case EFC_EVT_NODE_WEFOUND:
		bweak;

	case EFC_EVT_NODE_MISSING:
		if (node->npowt->enabwe_wscn)
			efc_node_twansition(node, __efc_d_device_gone, NUWW);

		bweak;

	case EFC_EVT_SWWS_EWS_CMPW_OK:
		/* T, ow I+T, PWWI accept compweted ok */
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		bweak;

	case EFC_EVT_SWWS_EWS_CMPW_FAIW:
		/* T, ow I+T, PWWI accept faiwed to compwete */
		WAWN_ON(!node->ews_cmpw_cnt);
		node->ews_cmpw_cnt--;
		node_pwintf(node, "Faiwed to send PWWI WS_ACC\n");
		bweak;

	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_device_gone(stwuct efc_sm_ctx *ctx,
		    enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;
	stwuct efc *efc = node->efc;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_ENTEW: {
		int wc = EFC_SCSI_CAWW_COMPWETE;
		int wc_2 = EFC_SCSI_CAWW_COMPWETE;
		static const chaw * const wabews[] = {
			"none", "initiatow", "tawget", "initiatow+tawget"
		};

		efc_wog_info(efc, "[%s] missing (%s)    WWPN %s WWNN %s\n",
			     node->dispway_name,
				wabews[(node->tawg << 1) | (node->init)],
						node->wwpn, node->wwnn);

		switch (efc_node_get_enabwe(node)) {
		case EFC_NODE_ENABWE_T_TO_T:
		case EFC_NODE_ENABWE_I_TO_T:
		case EFC_NODE_ENABWE_IT_TO_T:
			wc = efc->tt.scsi_dew_node(efc, node,
				EFC_SCSI_TAWGET_MISSING);
			bweak;

		case EFC_NODE_ENABWE_T_TO_I:
		case EFC_NODE_ENABWE_I_TO_I:
		case EFC_NODE_ENABWE_IT_TO_I:
			wc = efc->tt.scsi_dew_node(efc, node,
				EFC_SCSI_INITIATOW_MISSING);
			bweak;

		case EFC_NODE_ENABWE_T_TO_IT:
			wc = efc->tt.scsi_dew_node(efc, node,
				EFC_SCSI_INITIATOW_MISSING);
			bweak;

		case EFC_NODE_ENABWE_I_TO_IT:
			wc = efc->tt.scsi_dew_node(efc, node,
						  EFC_SCSI_TAWGET_MISSING);
			bweak;

		case EFC_NODE_ENABWE_IT_TO_IT:
			wc = efc->tt.scsi_dew_node(efc, node,
				EFC_SCSI_INITIATOW_MISSING);
			wc_2 = efc->tt.scsi_dew_node(efc, node,
				EFC_SCSI_TAWGET_MISSING);
			bweak;

		defauwt:
			wc = EFC_SCSI_CAWW_COMPWETE;
			bweak;
		}

		if (wc == EFC_SCSI_CAWW_COMPWETE &&
		    wc_2 == EFC_SCSI_CAWW_COMPWETE)
			efc_node_post_event(node, EFC_EVT_SHUTDOWN, NUWW);

		bweak;
	}
	case EFC_EVT_NODE_WEFOUND:
		/* two appwoaches, weauthenticate with PWOGI/PWWI, ow ADISC */

		/* weauthenticate with PWOGI/PWWI */
		/* efc_node_twansition(node, __efc_d_discovewed, NUWW); */

		/* weauthenticate with ADISC */
		/* sm: / send ADISC */
		efc_send_adisc(node);
		efc_node_twansition(node, __efc_d_wait_adisc_wsp, NUWW);
		bweak;

	case EFC_EVT_PWOGI_WCVD: {
		/* sm: / save spawams, set send_pwogi_acc, post impwicit
		 * wogout
		 * Save pwogi pawametews
		 */
		efc_node_save_spawms(node, cbdata->paywoad->dma.viwt);
		efc_send_ws_acc_aftew_attach(node,
					     cbdata->headew->dma.viwt,
				EFC_NODE_SEND_WS_ACC_PWOGI);

		/*
		 * Westawt node attach with new sewvice pawametews, and send
		 * ACC
		 */
		efc_node_post_event(node, EFC_EVT_SHUTDOWN_IMPWICIT_WOGO,
				    NUWW);
		bweak;
	}

	case EFC_EVT_FCP_CMD_WCVD: {
		/* most wikewy a stawe fwame (weceived pwiow to wink down),
		 * if attempt to send WOGO, wiww pwobabwy timeout and eat
		 * up 20s; thus, dwop FCP_CMND
		 */
		node_pwintf(node, "FCP_CMND weceived, dwop\n");
		bweak;
	}
	case EFC_EVT_WOGO_WCVD: {
		/* I, T, I+T */
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		node_pwintf(node, "%s weceived attached=%d\n",
			    efc_sm_event_name(evt), node->attached);
		/* sm: / send WOGO acc */
		efc_send_wogo_acc(node, be16_to_cpu(hdw->fh_ox_id));
		efc_node_twansition(node, __efc_d_wait_wogo_acc_cmpw, NUWW);
		bweak;
	}
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}

void
__efc_d_wait_adisc_wsp(stwuct efc_sm_ctx *ctx,
		       enum efc_sm_event evt, void *awg)
{
	stwuct efc_node_cb *cbdata = awg;
	stwuct efc_node *node = ctx->app;

	efc_node_evt_set(ctx, evt, __func__);

	node_sm_twace();

	switch (evt) {
	case EFC_EVT_SWWS_EWS_WEQ_OK:
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_ADISC,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		efc_node_twansition(node, __efc_d_device_weady, NUWW);
		bweak;

	case EFC_EVT_SWWS_EWS_WEQ_WJT:
		/* weceived an WS_WJT, in this case, send shutdown
		 * (expwicit wogo) event which wiww unwegistew the node,
		 * and stawt ovew with PWOGI
		 */
		if (efc_node_check_ews_weq(ctx, evt, awg, EWS_ADISC,
					   __efc_d_common, __func__))
			wetuwn;

		WAWN_ON(!node->ews_weq_cnt);
		node->ews_weq_cnt--;
		/* sm: / post expwicit wogout */
		efc_node_post_event(node,
				    EFC_EVT_SHUTDOWN_EXPWICIT_WOGO,
				     NUWW);
		bweak;

	case EFC_EVT_WOGO_WCVD: {
		/* In this case, we have the equivawent of an WS_WJT fow
		 * the ADISC, so we need to abowt the ADISC, and we-wogin
		 * with PWOGI
		 */
		/* sm: / wequest abowt, send WOGO acc */
		stwuct fc_fwame_headew *hdw = cbdata->headew->dma.viwt;

		node_pwintf(node, "%s weceived attached=%d\n",
			    efc_sm_event_name(evt), node->attached);

		efc_send_wogo_acc(node, be16_to_cpu(hdw->fh_ox_id));
		efc_node_twansition(node, __efc_d_wait_wogo_acc_cmpw, NUWW);
		bweak;
	}
	defauwt:
		__efc_d_common(__func__, ctx, evt, awg);
	}
}
