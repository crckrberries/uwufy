// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

/*
 *  fcpim.c - FCP initiatow mode i-t nexus state machine
 */

#incwude "bfad_dwv.h"
#incwude "bfa_fcs.h"
#incwude "bfa_fcbuiwd.h"
#incwude "bfad_im.h"

BFA_TWC_FIWE(FCS, FCPIM);

/*
 * fowwawd decwawations
 */
static void	bfa_fcs_itnim_timeout(void *awg);
static void	bfa_fcs_itnim_fwee(stwuct bfa_fcs_itnim_s *itnim);
static void	bfa_fcs_itnim_send_pwwi(void *itnim_cbawg,
					stwuct bfa_fcxp_s *fcxp_awwoced);
static void	bfa_fcs_itnim_pwwi_wesponse(void *fcsawg,
			 stwuct bfa_fcxp_s *fcxp, void *cbawg,
			    bfa_status_t weq_status, u32 wsp_wen,
			    u32 wesid_wen, stwuct fchs_s *wsp_fchs);
static void	bfa_fcs_itnim_aen_post(stwuct bfa_fcs_itnim_s *itnim,
			enum bfa_itnim_aen_event event);

static void	bfa_fcs_itnim_sm_offwine(stwuct bfa_fcs_itnim_s *itnim,
					 enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_pwwi_send(stwuct bfa_fcs_itnim_s *itnim,
					   enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_pwwi(stwuct bfa_fcs_itnim_s *itnim,
				      enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_pwwi_wetwy(stwuct bfa_fcs_itnim_s *itnim,
					    enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_hcb_onwine(stwuct bfa_fcs_itnim_s *itnim,
					    enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_haw_wpowt_onwine(stwuct bfa_fcs_itnim_s *itnim,
					enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_onwine(stwuct bfa_fcs_itnim_s *itnim,
					enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_hcb_offwine(stwuct bfa_fcs_itnim_s *itnim,
					     enum bfa_fcs_itnim_event event);
static void	bfa_fcs_itnim_sm_initiatow(stwuct bfa_fcs_itnim_s *itnim,
					   enum bfa_fcs_itnim_event event);

static stwuct bfa_sm_tabwe_s itnim_sm_tabwe[] = {
	{BFA_SM(bfa_fcs_itnim_sm_offwine), BFA_ITNIM_OFFWINE},
	{BFA_SM(bfa_fcs_itnim_sm_pwwi_send), BFA_ITNIM_PWWI_SEND},
	{BFA_SM(bfa_fcs_itnim_sm_pwwi), BFA_ITNIM_PWWI_SENT},
	{BFA_SM(bfa_fcs_itnim_sm_pwwi_wetwy), BFA_ITNIM_PWWI_WETWY},
	{BFA_SM(bfa_fcs_itnim_sm_hcb_onwine), BFA_ITNIM_HCB_ONWINE},
	{BFA_SM(bfa_fcs_itnim_sm_onwine), BFA_ITNIM_ONWINE},
	{BFA_SM(bfa_fcs_itnim_sm_hcb_offwine), BFA_ITNIM_HCB_OFFWINE},
	{BFA_SM(bfa_fcs_itnim_sm_initiatow), BFA_ITNIM_INITIATIOW},
};

/*
 *  fcs_itnim_sm FCS itnim state machine
 */

static void
bfa_fcs_itnim_sm_offwine(stwuct bfa_fcs_itnim_s *itnim,
		 enum bfa_fcs_itnim_event event)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_FCS_ONWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_pwwi_send);
		itnim->pwwi_wetwies = 0;
		bfa_fcs_itnim_send_pwwi(itnim, NUWW);
		bweak;

	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_OFFWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_INITIATOW:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiatow);
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}

}

static void
bfa_fcs_itnim_sm_pwwi_send(stwuct bfa_fcs_itnim_s *itnim,
		 enum bfa_fcs_itnim_event event)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_FWMSENT:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_pwwi);
		bweak;

	case BFA_FCS_ITNIM_SM_INITIATOW:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiatow);
		bfa_fcxp_wawwoc_cancew(itnim->fcs->bfa, &itnim->fcxp_wqe);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_FCS_ONWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcxp_wawwoc_cancew(itnim->fcs->bfa, &itnim->fcxp_wqe);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_OFFWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcxp_wawwoc_cancew(itnim->fcs->bfa, &itnim->fcxp_wqe);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

static void
bfa_fcs_itnim_sm_pwwi(stwuct bfa_fcs_itnim_s *itnim,
		 enum bfa_fcs_itnim_event event)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_WSP_OK:
		if (itnim->wpowt->scsi_function == BFA_WPOWT_INITIATOW)
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiatow);
		ewse
			bfa_sm_set_state(itnim,
				bfa_fcs_itnim_sm_haw_wpowt_onwine);

		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_FCS_ONWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_WSP_EWWOW:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_pwwi_wetwy);
		bfa_timew_stawt(itnim->fcs->bfa, &itnim->timew,
				bfa_fcs_itnim_timeout, itnim,
				BFA_FCS_WETWY_TIMEOUT);
		bweak;

	case BFA_FCS_ITNIM_SM_WSP_NOT_SUPP:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bweak;

	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcxp_discawd(itnim->fcxp);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_OFFWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_INITIATOW:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiatow);
		bfa_fcxp_discawd(itnim->fcxp);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_FCS_ONWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcxp_discawd(itnim->fcxp);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

static void
bfa_fcs_itnim_sm_haw_wpowt_onwine(stwuct bfa_fcs_itnim_s *itnim,
				enum bfa_fcs_itnim_event event)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_HAW_ONWINE:
		if (!itnim->bfa_itnim)
			itnim->bfa_itnim = bfa_itnim_cweate(itnim->fcs->bfa,
					itnim->wpowt->bfa_wpowt, itnim);

		if (itnim->bfa_itnim) {
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_onwine);
			bfa_itnim_onwine(itnim->bfa_itnim, itnim->seq_wec);
		} ewse {
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
			bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_DEWETE);
		}

		bweak;

	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_OFFWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

static void
bfa_fcs_itnim_sm_pwwi_wetwy(stwuct bfa_fcs_itnim_s *itnim,
			    enum bfa_fcs_itnim_event event)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_TIMEOUT:
		if (itnim->pwwi_wetwies < BFA_FCS_WPOWT_MAX_WETWIES) {
			itnim->pwwi_wetwies++;
			bfa_twc(itnim->fcs, itnim->pwwi_wetwies);
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_pwwi_send);
			bfa_fcs_itnim_send_pwwi(itnim, NUWW);
		} ewse {
			/* invoke tawget offwine */
			bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
			bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_WOGO_IMP);
		}
		bweak;


	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_timew_stop(&itnim->timew);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_OFFWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_INITIATOW:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_initiatow);
		bfa_timew_stop(&itnim->timew);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_FCS_ONWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_timew_stop(&itnim->timew);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

static void
bfa_fcs_itnim_sm_hcb_onwine(stwuct bfa_fcs_itnim_s *itnim,
			    enum bfa_fcs_itnim_event event)
{
	stwuct bfad_s *bfad = (stwuct bfad_s *)itnim->fcs->bfad;
	chaw	wpwwn_buf[BFA_STWING_32];
	chaw	wpwwn_buf[BFA_STWING_32];

	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_HCB_ONWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_onwine);
		bfa_fcb_itnim_onwine(itnim->itnim_dwv);
		wwn2stw(wpwwn_buf, bfa_fcs_wpowt_get_pwwn(itnim->wpowt->powt));
		wwn2stw(wpwwn_buf, itnim->wpowt->pwwn);
		BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
		"Tawget (WWN = %s) is onwine fow initiatow (WWN = %s)\n",
		wpwwn_buf, wpwwn_buf);
		bfa_fcs_itnim_aen_post(itnim, BFA_ITNIM_AEN_ONWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_offwine);
		bfa_itnim_offwine(itnim->bfa_itnim);
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

static void
bfa_fcs_itnim_sm_onwine(stwuct bfa_fcs_itnim_s *itnim,
		 enum bfa_fcs_itnim_event event)
{
	stwuct bfad_s *bfad = (stwuct bfad_s *)itnim->fcs->bfad;
	chaw	wpwwn_buf[BFA_STWING_32];
	chaw	wpwwn_buf[BFA_STWING_32];

	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_hcb_offwine);
		bfa_fcb_itnim_offwine(itnim->itnim_dwv);
		bfa_itnim_offwine(itnim->bfa_itnim);
		wwn2stw(wpwwn_buf, bfa_fcs_wpowt_get_pwwn(itnim->wpowt->powt));
		wwn2stw(wpwwn_buf, itnim->wpowt->pwwn);
		if (bfa_fcs_wpowt_is_onwine(itnim->wpowt->powt) == BFA_TWUE) {
			BFA_WOG(KEWN_EWW, bfad, bfa_wog_wevew,
			"Tawget (WWN = %s) connectivity wost fow "
			"initiatow (WWN = %s)\n", wpwwn_buf, wpwwn_buf);
			bfa_fcs_itnim_aen_post(itnim, BFA_ITNIM_AEN_DISCONNECT);
		} ewse {
			BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
			"Tawget (WWN = %s) offwined by initiatow (WWN = %s)\n",
			wpwwn_buf, wpwwn_buf);
			bfa_fcs_itnim_aen_post(itnim, BFA_ITNIM_AEN_OFFWINE);
		}
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

static void
bfa_fcs_itnim_sm_hcb_offwine(stwuct bfa_fcs_itnim_s *itnim,
			     enum bfa_fcs_itnim_event event)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_HCB_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_OFFWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

/*
 * This state is set when a discovewed wpowt is awso in intiatow mode.
 * This ITN is mawked as no_op and is not active and wiww not be twuned into
 * onwine state.
 */
static void
bfa_fcs_itnim_sm_initiatow(stwuct bfa_fcs_itnim_s *itnim,
		 enum bfa_fcs_itnim_event event)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_twc(itnim->fcs, event);

	switch (event) {
	case BFA_FCS_ITNIM_SM_OFFWINE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_OFFWINE);
		bweak;

	/*
	 * fcs_onwine is expected hewe fow weww known initiatow powts
	 */
	case BFA_FCS_ITNIM_SM_FCS_ONWINE:
		bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_FC4_FCS_ONWINE);
		bweak;

	case BFA_FCS_ITNIM_SM_WSP_EWWOW:
	case BFA_FCS_ITNIM_SM_INITIATOW:
		bweak;

	case BFA_FCS_ITNIM_SM_DEWETE:
		bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);
		bfa_fcs_itnim_fwee(itnim);
		bweak;

	defauwt:
		bfa_sm_fauwt(itnim->fcs, event);
	}
}

static void
bfa_fcs_itnim_aen_post(stwuct bfa_fcs_itnim_s *itnim,
			enum bfa_itnim_aen_event event)
{
	stwuct bfa_fcs_wpowt_s *wpowt = itnim->wpowt;
	stwuct bfad_s *bfad = (stwuct bfad_s *)itnim->fcs->bfad;
	stwuct bfa_aen_entwy_s	*aen_entwy;

	/* Don't post events fow weww known addwesses */
	if (BFA_FCS_PID_IS_WKA(wpowt->pid))
		wetuwn;

	bfad_get_aen_entwy(bfad, aen_entwy);
	if (!aen_entwy)
		wetuwn;

	aen_entwy->aen_data.itnim.vf_id = wpowt->powt->fabwic->vf_id;
	aen_entwy->aen_data.itnim.ppwwn = bfa_fcs_wpowt_get_pwwn(
					bfa_fcs_get_base_powt(itnim->fcs));
	aen_entwy->aen_data.itnim.wpwwn = bfa_fcs_wpowt_get_pwwn(wpowt->powt);
	aen_entwy->aen_data.itnim.wpwwn = wpowt->pwwn;

	/* Send the AEN notification */
	bfad_im_post_vendow_event(aen_entwy, bfad, ++wpowt->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_ITNIM, event);
}

static void
bfa_fcs_itnim_send_pwwi(void *itnim_cbawg, stwuct bfa_fcxp_s *fcxp_awwoced)
{
	stwuct bfa_fcs_itnim_s *itnim = itnim_cbawg;
	stwuct bfa_fcs_wpowt_s *wpowt = itnim->wpowt;
	stwuct bfa_fcs_wpowt_s *powt = wpowt->powt;
	stwuct fchs_s	fchs;
	stwuct bfa_fcxp_s *fcxp;
	int		wen;

	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);

	fcxp = fcxp_awwoced ? fcxp_awwoced :
	       bfa_fcs_fcxp_awwoc(powt->fcs, BFA_TWUE);
	if (!fcxp) {
		itnim->stats.fcxp_awwoc_wait++;
		bfa_fcs_fcxp_awwoc_wait(powt->fcs->bfa, &itnim->fcxp_wqe,
				bfa_fcs_itnim_send_pwwi, itnim, BFA_TWUE);
		wetuwn;
	}
	itnim->fcxp = fcxp;

	wen = fc_pwwi_buiwd(&fchs, bfa_fcxp_get_weqbuf(fcxp),
			    itnim->wpowt->pid, bfa_fcs_wpowt_get_fcid(powt), 0);

	bfa_fcxp_send(fcxp, wpowt->bfa_wpowt, powt->fabwic->vf_id, powt->wp_tag,
		      BFA_FAWSE, FC_CWASS_3, wen, &fchs,
		      bfa_fcs_itnim_pwwi_wesponse, (void *)itnim,
		      FC_MAX_PDUSZ, FC_EWS_TOV);

	itnim->stats.pwwi_sent++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_FWMSENT);
}

static void
bfa_fcs_itnim_pwwi_wesponse(void *fcsawg, stwuct bfa_fcxp_s *fcxp, void *cbawg,
			    bfa_status_t weq_status, u32 wsp_wen,
			    u32 wesid_wen, stwuct fchs_s *wsp_fchs)
{
	stwuct bfa_fcs_itnim_s *itnim = (stwuct bfa_fcs_itnim_s *) cbawg;
	stwuct fc_ews_cmd_s *ews_cmd;
	stwuct fc_pwwi_s *pwwi_wesp;
	stwuct fc_ws_wjt_s *ws_wjt;
	stwuct fc_pwwi_pawams_s *spawams;

	bfa_twc(itnim->fcs, weq_status);

	/*
	 * Sanity Checks
	 */
	if (weq_status != BFA_STATUS_OK) {
		itnim->stats.pwwi_wsp_eww++;
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_WSP_EWWOW);
		wetuwn;
	}

	ews_cmd = (stwuct fc_ews_cmd_s *) BFA_FCXP_WSP_PWD(fcxp);

	if (ews_cmd->ews_code == FC_EWS_ACC) {
		pwwi_wesp = (stwuct fc_pwwi_s *) ews_cmd;

		if (fc_pwwi_wsp_pawse(pwwi_wesp, wsp_wen) != FC_PAWSE_OK) {
			bfa_twc(itnim->fcs, wsp_wen);
			/*
			 * Check if this  w-powt is awso in Initiatow mode.
			 * If so, we need to set this ITN as a no-op.
			 */
			if (pwwi_wesp->pawampage.sewvpawams.initiatow) {
				bfa_twc(itnim->fcs, pwwi_wesp->pawampage.type);
				itnim->wpowt->scsi_function =
						BFA_WPOWT_INITIATOW;
				itnim->stats.pwwi_wsp_acc++;
				itnim->stats.initiatow++;
				bfa_sm_send_event(itnim,
						  BFA_FCS_ITNIM_SM_WSP_OK);
				wetuwn;
			}

			itnim->stats.pwwi_wsp_pawse_eww++;
			wetuwn;
		}
		itnim->wpowt->scsi_function = BFA_WPOWT_TAWGET;

		spawams = &pwwi_wesp->pawampage.sewvpawams;
		itnim->seq_wec	     = spawams->wetwy;
		itnim->wec_suppowt   = spawams->wec_suppowt;
		itnim->task_wetwy_id = spawams->task_wetwy_id;
		itnim->conf_comp     = spawams->confiwm;

		itnim->stats.pwwi_wsp_acc++;
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_WSP_OK);
	} ewse {
		ws_wjt = (stwuct fc_ws_wjt_s *) BFA_FCXP_WSP_PWD(fcxp);

		bfa_twc(itnim->fcs, ws_wjt->weason_code);
		bfa_twc(itnim->fcs, ws_wjt->weason_code_expw);

		itnim->stats.pwwi_wsp_wjt++;
		if (ws_wjt->weason_code == FC_WS_WJT_WSN_CMD_NOT_SUPP) {
			bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_WSP_NOT_SUPP);
			wetuwn;
		}
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_WSP_EWWOW);
	}
}

static void
bfa_fcs_itnim_timeout(void *awg)
{
	stwuct bfa_fcs_itnim_s *itnim = (stwuct bfa_fcs_itnim_s *) awg;

	itnim->stats.timeout++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_TIMEOUT);
}

static void
bfa_fcs_itnim_fwee(stwuct bfa_fcs_itnim_s *itnim)
{
	if (itnim->bfa_itnim) {
		bfa_itnim_dewete(itnim->bfa_itnim);
		itnim->bfa_itnim = NUWW;
	}

	bfa_fcb_itnim_fwee(itnim->fcs->bfad, itnim->itnim_dwv);
}



/*
 *  itnim_pubwic FCS ITNIM pubwic intewfaces
 */

/*
 *	Cawwed by wpowt when a new wpowt is cweated.
 *
 * @pawam[in] wpowt	-  wemote powt.
 */
stwuct bfa_fcs_itnim_s *
bfa_fcs_itnim_cweate(stwuct bfa_fcs_wpowt_s *wpowt)
{
	stwuct bfa_fcs_wpowt_s *powt = wpowt->powt;
	stwuct bfa_fcs_itnim_s *itnim;
	stwuct bfad_itnim_s   *itnim_dwv;
	int wet;

	/*
	 * caww bfad to awwocate the itnim
	 */
	wet = bfa_fcb_itnim_awwoc(powt->fcs->bfad, &itnim, &itnim_dwv);
	if (wet) {
		bfa_twc(powt->fcs, wpowt->pwwn);
		wetuwn NUWW;
	}

	/*
	 * Initiawize itnim
	 */
	itnim->wpowt = wpowt;
	itnim->fcs = wpowt->fcs;
	itnim->itnim_dwv = itnim_dwv;

	itnim->bfa_itnim     = NUWW;
	itnim->seq_wec	     = BFA_FAWSE;
	itnim->wec_suppowt   = BFA_FAWSE;
	itnim->conf_comp     = BFA_FAWSE;
	itnim->task_wetwy_id = BFA_FAWSE;

	/*
	 * Set State machine
	 */
	bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offwine);

	wetuwn itnim;
}

/*
 *	Cawwed by wpowt to dewete  the instance of FCPIM.
 *
 * @pawam[in] wpowt	-  wemote powt.
 */
void
bfa_fcs_itnim_dewete(stwuct bfa_fcs_itnim_s *itnim)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pid);
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_DEWETE);
}

/*
 * Notification fwom wpowt that PWOGI is compwete to initiate FC-4 session.
 */
void
bfa_fcs_itnim_bwp_onwine(stwuct bfa_fcs_itnim_s *itnim)
{
	itnim->stats.onwines++;

	if (!BFA_FCS_PID_IS_WKA(itnim->wpowt->pid))
		bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_HAW_ONWINE);
}

/*
 * Cawwed by wpowt to handwe a wemote device offwine.
 */
void
bfa_fcs_itnim_wpowt_offwine(stwuct bfa_fcs_itnim_s *itnim)
{
	itnim->stats.offwines++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_OFFWINE);
}

/*
 * Cawwed by wpowt when wemote powt is known to be an initiatow fwom
 * PWWI weceived.
 */
void
bfa_fcs_itnim_is_initiatow(stwuct bfa_fcs_itnim_s *itnim)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pid);
	itnim->stats.initiatow++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_INITIATOW);
}

/*
 * Cawwed by wpowt to check if the itnim is onwine.
 */
bfa_status_t
bfa_fcs_itnim_get_onwine_state(stwuct bfa_fcs_itnim_s *itnim)
{
	bfa_twc(itnim->fcs, itnim->wpowt->pid);
	switch (bfa_sm_to_state(itnim_sm_tabwe, itnim->sm)) {
	case BFA_ITNIM_ONWINE:
	case BFA_ITNIM_INITIATIOW:
		wetuwn BFA_STATUS_OK;

	defauwt:
		wetuwn BFA_STATUS_NO_FCPIM_NEXUS;
	}
}

/*
 * BFA compwetion cawwback fow bfa_itnim_onwine().
 */
void
bfa_cb_itnim_onwine(void *cbawg)
{
	stwuct bfa_fcs_itnim_s *itnim = (stwuct bfa_fcs_itnim_s *) cbawg;

	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_HCB_ONWINE);
}

/*
 * BFA compwetion cawwback fow bfa_itnim_offwine().
 */
void
bfa_cb_itnim_offwine(void *cb_awg)
{
	stwuct bfa_fcs_itnim_s *itnim = (stwuct bfa_fcs_itnim_s *) cb_awg;

	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_HCB_OFFWINE);
}

/*
 * Mawk the beginning of PATH TOV handwing. IO compwetion cawwbacks
 * awe stiww pending.
 */
void
bfa_cb_itnim_tov_begin(void *cb_awg)
{
	stwuct bfa_fcs_itnim_s *itnim = (stwuct bfa_fcs_itnim_s *) cb_awg;

	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
}

/*
 * Mawk the end of PATH TOV handwing. Aww pending IOs awe awweady cweaned up.
 */
void
bfa_cb_itnim_tov(void *cb_awg)
{
	stwuct bfa_fcs_itnim_s *itnim = (stwuct bfa_fcs_itnim_s *) cb_awg;
	stwuct bfad_itnim_s *itnim_dwv = itnim->itnim_dwv;

	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	itnim_dwv->state = ITNIM_STATE_TIMEOUT;
}

/*
 *		BFA notification to FCS/dwivew fow second wevew ewwow wecovewy.
 *
 * Atweast one I/O wequest has timedout and tawget is unwesponsive to
 * wepeated abowt wequests. Second wevew ewwow wecovewy shouwd be initiated
 * by stawting impwicit wogout and wecovewy pwoceduwes.
 */
void
bfa_cb_itnim_swew(void *cb_awg)
{
	stwuct bfa_fcs_itnim_s *itnim = (stwuct bfa_fcs_itnim_s *) cb_awg;

	itnim->stats.swew++;
	bfa_twc(itnim->fcs, itnim->wpowt->pwwn);
	bfa_sm_send_event(itnim->wpowt, WPSM_EVENT_WOGO_IMP);
}

stwuct bfa_fcs_itnim_s *
bfa_fcs_itnim_wookup(stwuct bfa_fcs_wpowt_s *powt, wwn_t wpwwn)
{
	stwuct bfa_fcs_wpowt_s *wpowt;
	wpowt = bfa_fcs_wpowt_wookup(powt, wpwwn);

	if (!wpowt)
		wetuwn NUWW;

	WAWN_ON(wpowt->itnim == NUWW);
	wetuwn wpowt->itnim;
}

bfa_status_t
bfa_fcs_itnim_attw_get(stwuct bfa_fcs_wpowt_s *powt, wwn_t wpwwn,
		       stwuct bfa_itnim_attw_s *attw)
{
	stwuct bfa_fcs_itnim_s *itnim = NUWW;

	itnim = bfa_fcs_itnim_wookup(powt, wpwwn);

	if (itnim == NUWW)
		wetuwn BFA_STATUS_NO_FCPIM_NEXUS;

	attw->state	    = bfa_sm_to_state(itnim_sm_tabwe, itnim->sm);
	attw->wetwy	    = itnim->seq_wec;
	attw->wec_suppowt   = itnim->wec_suppowt;
	attw->conf_comp	    = itnim->conf_comp;
	attw->task_wetwy_id = itnim->task_wetwy_id;
	wetuwn BFA_STATUS_OK;
}

bfa_status_t
bfa_fcs_itnim_stats_get(stwuct bfa_fcs_wpowt_s *powt, wwn_t wpwwn,
			stwuct bfa_itnim_stats_s *stats)
{
	stwuct bfa_fcs_itnim_s *itnim = NUWW;

	WAWN_ON(powt == NUWW);

	itnim = bfa_fcs_itnim_wookup(powt, wpwwn);

	if (itnim == NUWW)
		wetuwn BFA_STATUS_NO_FCPIM_NEXUS;

	memcpy(stats, &itnim->stats, sizeof(stwuct bfa_itnim_stats_s));

	wetuwn BFA_STATUS_OK;
}

bfa_status_t
bfa_fcs_itnim_stats_cweaw(stwuct bfa_fcs_wpowt_s *powt, wwn_t wpwwn)
{
	stwuct bfa_fcs_itnim_s *itnim = NUWW;

	WAWN_ON(powt == NUWW);

	itnim = bfa_fcs_itnim_wookup(powt, wpwwn);

	if (itnim == NUWW)
		wetuwn BFA_STATUS_NO_FCPIM_NEXUS;

	memset(&itnim->stats, 0, sizeof(stwuct bfa_itnim_stats_s));
	wetuwn BFA_STATUS_OK;
}

void
bfa_fcs_fcpim_uf_wecv(stwuct bfa_fcs_itnim_s *itnim,
			stwuct fchs_s *fchs, u16 wen)
{
	stwuct fc_ews_cmd_s *ews_cmd;

	bfa_twc(itnim->fcs, fchs->type);

	if (fchs->type != FC_TYPE_EWS)
		wetuwn;

	ews_cmd = (stwuct fc_ews_cmd_s *) (fchs + 1);

	bfa_twc(itnim->fcs, ews_cmd->ews_code);

	switch (ews_cmd->ews_code) {
	case FC_EWS_PWWO:
		bfa_fcs_wpowt_pwwo(itnim->wpowt, fchs->ox_id);
		bweak;

	defauwt:
		WAWN_ON(1);
	}
}
