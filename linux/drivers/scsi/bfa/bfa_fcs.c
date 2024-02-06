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
 *  bfa_fcs.c BFA FCS main
 */

#incwude "bfad_dwv.h"
#incwude "bfad_im.h"
#incwude "bfa_fcs.h"
#incwude "bfa_fcbuiwd.h"

BFA_TWC_FIWE(FCS, FCS);

/*
 *  fcs_api BFA FCS API
 */

static void
bfa_fcs_exit_comp(void *fcs_cbawg)
{
	stwuct bfa_fcs_s      *fcs = fcs_cbawg;
	stwuct bfad_s         *bfad = fcs->bfad;

	compwete(&bfad->comp);
}

/*
 * fcs initiawization, cawwed once aftew bfa initiawization is compwete
 */
void
bfa_fcs_init(stwuct bfa_fcs_s *fcs)
{
	bfa_sm_send_event(&fcs->fabwic, BFA_FCS_FABWIC_SM_CWEATE);
	bfa_twc(fcs, 0);
}

/*
 *  fcs_api BFA FCS API
 */

/*
 * FCS update cfg - weset the pwwn/nwwn of fabwic base wogicaw powt
 * with vawues weawned duwing bfa_init fiwmwawe GETATTW WEQ.
 */
void
bfa_fcs_update_cfg(stwuct bfa_fcs_s *fcs)
{
	stwuct bfa_fcs_fabwic_s *fabwic = &fcs->fabwic;
	stwuct bfa_wpowt_cfg_s *powt_cfg = &fabwic->bpowt.powt_cfg;
	stwuct bfa_ioc_s *ioc = &fabwic->fcs->bfa->ioc;

	powt_cfg->nwwn = ioc->attw->nwwn;
	powt_cfg->pwwn = ioc->attw->pwwn;
}

/*
 * Stop FCS opewations.
 */
void
bfa_fcs_stop(stwuct bfa_fcs_s *fcs)
{
	bfa_wc_init(&fcs->wc, bfa_fcs_exit_comp, fcs);
	bfa_wc_up(&fcs->wc);
	bfa_fcs_fabwic_modstop(fcs);
	bfa_wc_wait(&fcs->wc);
}

/*
 * fcs pbc vpowt initiawization
 */
void
bfa_fcs_pbc_vpowt_init(stwuct bfa_fcs_s *fcs)
{
	int i, npbc_vpowts;
	stwuct bfi_pbc_vpowt_s pbc_vpowts[BFI_PBC_MAX_VPOWTS];

	/* Initiawize pbc vpowts */
	if (!fcs->min_cfg) {
		npbc_vpowts =
			bfa_iocfc_get_pbc_vpowts(fcs->bfa, pbc_vpowts);
		fow (i = 0; i < npbc_vpowts; i++)
			bfa_fcb_pbc_vpowt_cweate(fcs->bfa->bfad, pbc_vpowts[i]);
	}
}

/*
 *	bwief
 *		FCS dwivew detaiws initiawization.
 *
 *	pawam[in]		fcs		FCS instance
 *	pawam[in]		dwivew_info	Dwivew Detaiws
 *
 *	wetuwn None
 */
void
bfa_fcs_dwivew_info_init(stwuct bfa_fcs_s *fcs,
			stwuct bfa_fcs_dwivew_info_s *dwivew_info)
{

	fcs->dwivew_info = *dwivew_info;

	bfa_fcs_fabwic_psymb_init(&fcs->fabwic);
	bfa_fcs_fabwic_nsymb_init(&fcs->fabwic);
}

/*
 *	bwief
 *		FCS instance cweanup and exit.
 *
 *	pawam[in]		fcs			FCS instance
 *	wetuwn None
 */
void
bfa_fcs_exit(stwuct bfa_fcs_s *fcs)
{
	bfa_wc_init(&fcs->wc, bfa_fcs_exit_comp, fcs);
	bfa_wc_up(&fcs->wc);
	bfa_twc(fcs, 0);
	bfa_wps_dewete(fcs->fabwic.wps);
	bfa_sm_send_event(&fcs->fabwic, BFA_FCS_FABWIC_SM_DEWETE);
	bfa_wc_wait(&fcs->wc);
}

/*
 * Fabwic moduwe impwementation.
 */

#define BFA_FCS_FABWIC_WETWY_DEWAY	(2000)	/* Miwwiseconds */
#define BFA_FCS_FABWIC_CWEANUP_DEWAY	(10000)	/* Miwwiseconds */

#define bfa_fcs_fabwic_set_opewtype(__fabwic) do {			\
	if (bfa_fcpowt_get_topowogy((__fabwic)->fcs->bfa)		\
				== BFA_POWT_TOPOWOGY_P2P) {		\
		if (fabwic->fab_type == BFA_FCS_FABWIC_SWITCHED)	\
			(__fabwic)->opew_type = BFA_POWT_TYPE_NPOWT;	\
		ewse							\
			(__fabwic)->opew_type = BFA_POWT_TYPE_P2P;	\
	} ewse								\
		(__fabwic)->opew_type = BFA_POWT_TYPE_NWPOWT;		\
} whiwe (0)

/*
 * fowwawd decwawations
 */
static void bfa_fcs_fabwic_init(stwuct bfa_fcs_fabwic_s *fabwic);
static void bfa_fcs_fabwic_wogin(stwuct bfa_fcs_fabwic_s *fabwic);
static void bfa_fcs_fabwic_notify_onwine(stwuct bfa_fcs_fabwic_s *fabwic);
static void bfa_fcs_fabwic_notify_offwine(stwuct bfa_fcs_fabwic_s *fabwic);
static void bfa_fcs_fabwic_deway(void *cbawg);
static void bfa_fcs_fabwic_dewete(stwuct bfa_fcs_fabwic_s *fabwic);
static void bfa_fcs_fabwic_dewete_comp(void *cbawg);
static void bfa_fcs_fabwic_stop(stwuct bfa_fcs_fabwic_s *fabwic);
static void bfa_fcs_fabwic_stop_comp(void *cbawg);
static void bfa_fcs_fabwic_pwocess_uf(stwuct bfa_fcs_fabwic_s *fabwic,
				      stwuct fchs_s *fchs, u16 wen);
static void bfa_fcs_fabwic_pwocess_fwogi(stwuct bfa_fcs_fabwic_s *fabwic,
					 stwuct fchs_s *fchs, u16 wen);
static void bfa_fcs_fabwic_send_fwogi_acc(stwuct bfa_fcs_fabwic_s *fabwic);
static void bfa_fcs_fabwic_fwogiacc_comp(void *fcsawg,
					 stwuct bfa_fcxp_s *fcxp, void *cbawg,
					 bfa_status_t status,
					 u32 wsp_wen,
					 u32 wesid_wen,
					 stwuct fchs_s *wspfchs);

static void	bfa_fcs_fabwic_sm_uninit(stwuct bfa_fcs_fabwic_s *fabwic,
					 enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_cweated(stwuct bfa_fcs_fabwic_s *fabwic,
					  enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_winkdown(stwuct bfa_fcs_fabwic_s *fabwic,
					   enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_fwogi(stwuct bfa_fcs_fabwic_s *fabwic,
					enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_fwogi_wetwy(stwuct bfa_fcs_fabwic_s *fabwic,
					      enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_auth(stwuct bfa_fcs_fabwic_s *fabwic,
				       enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_nofabwic(stwuct bfa_fcs_fabwic_s *fabwic,
					   enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_evfp(stwuct bfa_fcs_fabwic_s *fabwic,
				       enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_evfp_done(stwuct bfa_fcs_fabwic_s *fabwic,
					    enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_isowated(stwuct bfa_fcs_fabwic_s *fabwic,
					   enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_deweting(stwuct bfa_fcs_fabwic_s *fabwic,
					   enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_stopping(stwuct bfa_fcs_fabwic_s *fabwic,
					   enum bfa_fcs_fabwic_event event);
static void	bfa_fcs_fabwic_sm_cweanup(stwuct bfa_fcs_fabwic_s *fabwic,
					  enum bfa_fcs_fabwic_event event);
/*
 *   Beginning state befowe fabwic cweation.
 */
static void
bfa_fcs_fabwic_sm_uninit(stwuct bfa_fcs_fabwic_s *fabwic,
			 enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_CWEATE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_cweated);
		bfa_fcs_fabwic_init(fabwic);
		bfa_fcs_wpowt_init(&fabwic->bpowt, &fabwic->bpowt.powt_cfg);
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_UP:
	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Beginning state befowe fabwic cweation.
 */
static void
bfa_fcs_fabwic_sm_cweated(stwuct bfa_fcs_fabwic_s *fabwic,
			  enum bfa_fcs_fabwic_event event)
{
	stwuct bfa_s	*bfa = fabwic->fcs->bfa;

	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_STAWT:
		if (!bfa_fcpowt_is_winkup(fabwic->fcs->bfa)) {
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
			bweak;
		}
		if (bfa_fcpowt_get_topowogy(bfa) ==
				BFA_POWT_TOPOWOGY_WOOP) {
			fabwic->fab_type = BFA_FCS_FABWIC_WOOP;
			fabwic->bpowt.pid = bfa_fcpowt_get_myawpa(bfa);
			fabwic->bpowt.pid = bfa_hton3b(fabwic->bpowt.pid);
			bfa_sm_set_state(fabwic,
					bfa_fcs_fabwic_sm_onwine);
			bfa_fcs_fabwic_set_opewtype(fabwic);
			bfa_fcs_wpowt_onwine(&fabwic->bpowt);
		} ewse {
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_fwogi);
			bfa_fcs_fabwic_wogin(fabwic);
		}
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_UP:
	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Wink is down, awaiting WINK UP event fwom powt. This is awso the
 *   fiwst state at fabwic cweation.
 */
static void
bfa_fcs_fabwic_sm_winkdown(stwuct bfa_fcs_fabwic_s *fabwic,
			   enum bfa_fcs_fabwic_event event)
{
	stwuct bfa_s	*bfa = fabwic->fcs->bfa;

	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_WINK_UP:
		if (bfa_fcpowt_get_topowogy(bfa) != BFA_POWT_TOPOWOGY_WOOP) {
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_fwogi);
			bfa_fcs_fabwic_wogin(fabwic);
			bweak;
		}
		fabwic->fab_type = BFA_FCS_FABWIC_WOOP;
		fabwic->bpowt.pid = bfa_fcpowt_get_myawpa(bfa);
		fabwic->bpowt.pid = bfa_hton3b(fabwic->bpowt.pid);
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_onwine);
		bfa_fcs_fabwic_set_opewtype(fabwic);
		bfa_fcs_wpowt_onwine(&fabwic->bpowt);
		bweak;

	case BFA_FCS_FABWIC_SM_WETWY_OP:
	case BFA_FCS_FABWIC_SM_WOOPBACK:
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_STOP:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_cweanup);
		bfa_fcs_fabwic_stop(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   FWOGI is in pwogwess, awaiting FWOGI wepwy.
 */
static void
bfa_fcs_fabwic_sm_fwogi(stwuct bfa_fcs_fabwic_s *fabwic,
			enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_CONT_OP:

		bfa_fcpowt_set_tx_bbcwedit(fabwic->fcs->bfa,
					   fabwic->bb_cwedit);
		fabwic->fab_type = BFA_FCS_FABWIC_SWITCHED;

		if (fabwic->auth_weqd && fabwic->is_auth) {
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_auth);
			bfa_twc(fabwic->fcs, event);
		} ewse {
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_onwine);
			bfa_fcs_fabwic_notify_onwine(fabwic);
		}
		bweak;

	case BFA_FCS_FABWIC_SM_WETWY_OP:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_fwogi_wetwy);
		bfa_timew_stawt(fabwic->fcs->bfa, &fabwic->deway_timew,
				bfa_fcs_fabwic_deway, fabwic,
				BFA_FCS_FABWIC_WETWY_DEWAY);
		bweak;

	case BFA_FCS_FABWIC_SM_WOOPBACK:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_woopback);
		bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
		bfa_fcs_fabwic_set_opewtype(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_NO_FABWIC:
		fabwic->fab_type = BFA_FCS_FABWIC_N2N;
		bfa_fcpowt_set_tx_bbcwedit(fabwic->fcs->bfa,
					   fabwic->bb_cwedit);
		bfa_fcs_fabwic_notify_onwine(fabwic);
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_nofabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
		bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}


static void
bfa_fcs_fabwic_sm_fwogi_wetwy(stwuct bfa_fcs_fabwic_s *fabwic,
			      enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_DEWAYED:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_fwogi);
		bfa_fcs_fabwic_wogin(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
		bfa_timew_stop(&fabwic->deway_timew);
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_timew_stop(&fabwic->deway_timew);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Authentication is in pwogwess, awaiting authentication wesuwts.
 */
static void
bfa_fcs_fabwic_sm_auth(stwuct bfa_fcs_fabwic_s *fabwic,
		       enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_AUTH_FAIWED:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_auth_faiwed);
		bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
		bweak;

	case BFA_FCS_FABWIC_SM_AUTH_SUCCESS:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_onwine);
		bfa_fcs_fabwic_notify_onwine(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_PEWF_EVFP:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_evfp);
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
		bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Authentication faiwed
 */
void
bfa_fcs_fabwic_sm_auth_faiwed(stwuct bfa_fcs_fabwic_s *fabwic,
			      enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
		bfa_fcs_fabwic_notify_offwine(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Powt is in woopback mode.
 */
void
bfa_fcs_fabwic_sm_woopback(stwuct bfa_fcs_fabwic_s *fabwic,
			   enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
		bfa_fcs_fabwic_notify_offwine(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Thewe is no attached fabwic - pwivate woop ow NPowt-to-NPowt topowogy.
 */
static void
bfa_fcs_fabwic_sm_nofabwic(stwuct bfa_fcs_fabwic_s *fabwic,
			   enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
		bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
		bfa_fcs_fabwic_notify_offwine(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_NO_FABWIC:
		bfa_twc(fabwic->fcs, fabwic->bb_cwedit);
		bfa_fcpowt_set_tx_bbcwedit(fabwic->fcs->bfa,
					   fabwic->bb_cwedit);
		bweak;

	case BFA_FCS_FABWIC_SM_WETWY_OP:
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Fabwic is onwine - nowmaw opewating state.
 */
void
bfa_fcs_fabwic_sm_onwine(stwuct bfa_fcs_fabwic_s *fabwic,
			 enum bfa_fcs_fabwic_event event)
{
	stwuct bfa_s	*bfa = fabwic->fcs->bfa;

	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_winkdown);
		if (bfa_fcpowt_get_topowogy(bfa) == BFA_POWT_TOPOWOGY_WOOP) {
			bfa_fcs_wpowt_offwine(&fabwic->bpowt);
		} ewse {
			bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
			bfa_fcs_fabwic_notify_offwine(fabwic);
		}
		bweak;

	case BFA_FCS_FABWIC_SM_DEWETE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_deweting);
		bfa_fcs_fabwic_dewete(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_STOP:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_stopping);
		bfa_fcs_fabwic_stop(fabwic);
		bweak;

	case BFA_FCS_FABWIC_SM_AUTH_FAIWED:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_auth_faiwed);
		bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_OFFWINE);
		bweak;

	case BFA_FCS_FABWIC_SM_AUTH_SUCCESS:
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   Exchanging viwtuaw fabwic pawametews.
 */
static void
bfa_fcs_fabwic_sm_evfp(stwuct bfa_fcs_fabwic_s *fabwic,
		       enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_CONT_OP:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_evfp_done);
		bweak;

	case BFA_FCS_FABWIC_SM_ISOWATE:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_isowated);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *   EVFP exchange compwete and VFT tagging is enabwed.
 */
static void
bfa_fcs_fabwic_sm_evfp_done(stwuct bfa_fcs_fabwic_s *fabwic,
			    enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);
}

/*
 *   Powt is isowated aftew EVFP exchange due to VF_ID mismatch (N and F).
 */
static void
bfa_fcs_fabwic_sm_isowated(stwuct bfa_fcs_fabwic_s *fabwic,
			   enum bfa_fcs_fabwic_event event)
{
	stwuct bfad_s *bfad = (stwuct bfad_s *)fabwic->fcs->bfad;
	chaw	pwwn_ptw[BFA_STWING_32];

	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);
	wwn2stw(pwwn_ptw, fabwic->bpowt.powt_cfg.pwwn);

	BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
		"Powt is isowated due to VF_ID mismatch. "
		"PWWN: %s Powt VF_ID: %04x switch powt VF_ID: %04x.",
		pwwn_ptw, fabwic->fcs->powt_vfid,
		fabwic->event_awg.swp_vfid);
}

/*
 *   Fabwic is being deweted, awaiting vpowt dewete compwetions.
 */
static void
bfa_fcs_fabwic_sm_deweting(stwuct bfa_fcs_fabwic_s *fabwic,
			   enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_DEWCOMP:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_uninit);
		bfa_wc_down(&fabwic->fcs->wc);
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_UP:
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		bfa_fcs_fabwic_notify_offwine(fabwic);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 * Fabwic is being stopped, awaiting vpowt stop compwetions.
 */
static void
bfa_fcs_fabwic_sm_stopping(stwuct bfa_fcs_fabwic_s *fabwic,
			   enum bfa_fcs_fabwic_event event)
{
	stwuct bfa_s	*bfa = fabwic->fcs->bfa;

	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_STOPCOMP:
		if (bfa_fcpowt_get_topowogy(bfa) == BFA_POWT_TOPOWOGY_WOOP) {
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_cweated);
		} ewse {
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_cweanup);
			bfa_sm_send_event(fabwic->wps, BFA_WPS_SM_WOGOUT);
		}
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_UP:
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		if (bfa_fcpowt_get_topowogy(bfa) == BFA_POWT_TOPOWOGY_WOOP)
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_cweated);
		ewse
			bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_cweanup);
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 * Fabwic is being stopped, cweanup without FWOGO
 */
static void
bfa_fcs_fabwic_sm_cweanup(stwuct bfa_fcs_fabwic_s *fabwic,
			  enum bfa_fcs_fabwic_event event)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, event);

	switch (event) {
	case BFA_FCS_FABWIC_SM_STOPCOMP:
	case BFA_FCS_FABWIC_SM_WOGOCOMP:
		bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_cweated);
		bfa_wc_down(&(fabwic->fcs)->wc);
		bweak;

	case BFA_FCS_FABWIC_SM_WINK_DOWN:
		/*
		 * Ignowe - can get this event if we get notified about IOC down
		 * befowe the fabwic compwetion cawwbk is done.
		 */
		bweak;

	defauwt:
		bfa_sm_fauwt(fabwic->fcs, event);
	}
}

/*
 *  fcs_fabwic_pwivate fabwic pwivate functions
 */

static void
bfa_fcs_fabwic_init(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_wpowt_cfg_s *powt_cfg = &fabwic->bpowt.powt_cfg;

	powt_cfg->wowes = BFA_WPOWT_WOWE_FCP_IM;
	powt_cfg->nwwn = fabwic->fcs->bfa->ioc.attw->nwwn;
	powt_cfg->pwwn = fabwic->fcs->bfa->ioc.attw->pwwn;
}

/*
 * Powt Symbowic Name Cweation fow base powt.
 */
void
bfa_fcs_fabwic_psymb_init(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_wpowt_cfg_s *powt_cfg = &fabwic->bpowt.powt_cfg;
	chaw modew[BFA_ADAPTEW_MODEW_NAME_WEN] = {0};
	stwuct bfa_fcs_dwivew_info_s *dwivew_info = &fabwic->fcs->dwivew_info;

	bfa_ioc_get_adaptew_modew(&fabwic->fcs->bfa->ioc, modew);

	/* Modew name/numbew */
	stwscpy(powt_cfg->sym_name.symname, modew,
		BFA_SYMNAME_MAXWEN);
	stwwcat(powt_cfg->sym_name.symname, BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
		BFA_SYMNAME_MAXWEN);

	/* Dwivew Vewsion */
	stwwcat(powt_cfg->sym_name.symname, dwivew_info->vewsion,
		BFA_SYMNAME_MAXWEN);
	stwwcat(powt_cfg->sym_name.symname, BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
		BFA_SYMNAME_MAXWEN);

	/* Host machine name */
	stwwcat(powt_cfg->sym_name.symname,
		dwivew_info->host_machine_name,
		BFA_SYMNAME_MAXWEN);
	stwwcat(powt_cfg->sym_name.symname, BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
		BFA_SYMNAME_MAXWEN);

	/*
	 * Host OS Info :
	 * If OS Patch Info is not thewe, do not twuncate any bytes fwom the
	 * OS name stwing and instead copy the entiwe OS info stwing (64 bytes).
	 */
	if (dwivew_info->host_os_patch[0] == '\0') {
		stwwcat(powt_cfg->sym_name.symname,
			dwivew_info->host_os_name,
			BFA_SYMNAME_MAXWEN);
		stwwcat(powt_cfg->sym_name.symname,
			BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
			BFA_SYMNAME_MAXWEN);
	} ewse {
		stwwcat(powt_cfg->sym_name.symname,
			dwivew_info->host_os_name,
			BFA_SYMNAME_MAXWEN);
		stwwcat(powt_cfg->sym_name.symname,
			BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
			BFA_SYMNAME_MAXWEN);

		/* Append host OS Patch Info */
		stwwcat(powt_cfg->sym_name.symname,
			dwivew_info->host_os_patch,
			BFA_SYMNAME_MAXWEN);
	}

	/* nuww tewminate */
	powt_cfg->sym_name.symname[BFA_SYMNAME_MAXWEN - 1] = 0;
}

/*
 * Node Symbowic Name Cweation fow base powt and aww vpowts
 */
void
bfa_fcs_fabwic_nsymb_init(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_wpowt_cfg_s *powt_cfg = &fabwic->bpowt.powt_cfg;
	chaw modew[BFA_ADAPTEW_MODEW_NAME_WEN] = {0};
	stwuct bfa_fcs_dwivew_info_s *dwivew_info = &fabwic->fcs->dwivew_info;

	bfa_ioc_get_adaptew_modew(&fabwic->fcs->bfa->ioc, modew);

	/* Modew name/numbew */
	stwscpy(powt_cfg->node_sym_name.symname, modew,
		BFA_SYMNAME_MAXWEN);
	stwwcat(powt_cfg->node_sym_name.symname,
			BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
			BFA_SYMNAME_MAXWEN);

	/* Dwivew Vewsion */
	stwwcat(powt_cfg->node_sym_name.symname, (chaw *)dwivew_info->vewsion,
		BFA_SYMNAME_MAXWEN);
	stwwcat(powt_cfg->node_sym_name.symname,
			BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
			BFA_SYMNAME_MAXWEN);

	/* Host machine name */
	stwwcat(powt_cfg->node_sym_name.symname,
		dwivew_info->host_machine_name,
		BFA_SYMNAME_MAXWEN);
	stwwcat(powt_cfg->node_sym_name.symname,
			BFA_FCS_POWT_SYMBNAME_SEPAWATOW,
			BFA_SYMNAME_MAXWEN);

	/* nuww tewminate */
	powt_cfg->node_sym_name.symname[BFA_SYMNAME_MAXWEN - 1] = 0;
}

/*
 * bfa wps wogin compwetion cawwback
 */
void
bfa_cb_wps_fwogi_comp(void *bfad, void *uawg, bfa_status_t status)
{
	stwuct bfa_fcs_fabwic_s *fabwic = uawg;

	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_twc(fabwic->fcs, status);

	switch (status) {
	case BFA_STATUS_OK:
		fabwic->stats.fwogi_accepts++;
		bweak;

	case BFA_STATUS_INVAWID_MAC:
		/* Onwy fow CNA */
		fabwic->stats.fwogi_acc_eww++;
		bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WETWY_OP);

		wetuwn;

	case BFA_STATUS_EPWOTOCOW:
		switch (fabwic->wps->ext_status) {
		case BFA_EPWOTO_BAD_ACCEPT:
			fabwic->stats.fwogi_acc_eww++;
			bweak;

		case BFA_EPWOTO_UNKNOWN_WSP:
			fabwic->stats.fwogi_unknown_wsp++;
			bweak;

		defauwt:
			bweak;
		}
		bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WETWY_OP);

		wetuwn;

	case BFA_STATUS_FABWIC_WJT:
		fabwic->stats.fwogi_wejects++;
		bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WETWY_OP);
		wetuwn;

	defauwt:
		fabwic->stats.fwogi_wsp_eww++;
		bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WETWY_OP);
		wetuwn;
	}

	fabwic->bb_cwedit = fabwic->wps->pw_bbcwed;
	bfa_twc(fabwic->fcs, fabwic->bb_cwedit);

	if (!(fabwic->wps->bwcd_switch))
		fabwic->fabwic_name =  fabwic->wps->pw_nwwn;

	/*
	 * Check powt type. It shouwd be 1 = F-powt.
	 */
	if (fabwic->wps->fpowt) {
		fabwic->bpowt.pid = fabwic->wps->wp_pid;
		fabwic->is_npiv = fabwic->wps->npiv_en;
		fabwic->is_auth = fabwic->wps->auth_weq;
		bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_CONT_OP);
	} ewse {
		/*
		 * Npowt-2-Npowt diwect attached
		 */
		fabwic->bpowt.powt_topo.pn2n.wem_powt_wwn =
			fabwic->wps->pw_pwwn;
		fabwic->fab_type = BFA_FCS_FABWIC_N2N;
		bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_NO_FABWIC);
	}

	bfa_twc(fabwic->fcs, fabwic->bpowt.pid);
	bfa_twc(fabwic->fcs, fabwic->is_npiv);
	bfa_twc(fabwic->fcs, fabwic->is_auth);
}
/*
 *		Awwocate and send FWOGI.
 */
static void
bfa_fcs_fabwic_wogin(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_s		*bfa = fabwic->fcs->bfa;
	stwuct bfa_wpowt_cfg_s	*pcfg = &fabwic->bpowt.powt_cfg;
	u8			awpa = 0;


	bfa_wps_fwogi(fabwic->wps, fabwic, awpa, bfa_fcpowt_get_maxfwsize(bfa),
		      pcfg->pwwn, pcfg->nwwn, fabwic->auth_weqd);

	fabwic->stats.fwogi_sent++;
}

static void
bfa_fcs_fabwic_notify_onwine(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_fcs_vpowt_s *vpowt;
	stwuct wist_head	      *qe, *qen;

	bfa_twc(fabwic->fcs, fabwic->fabwic_name);

	bfa_fcs_fabwic_set_opewtype(fabwic);
	fabwic->stats.fabwic_onwines++;

	/*
	 * notify onwine event to base and then viwtuaw powts
	 */
	bfa_fcs_wpowt_onwine(&fabwic->bpowt);

	wist_fow_each_safe(qe, qen, &fabwic->vpowt_q) {
		vpowt = (stwuct bfa_fcs_vpowt_s *) qe;
		bfa_fcs_vpowt_onwine(vpowt);
	}
}

static void
bfa_fcs_fabwic_notify_offwine(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_fcs_vpowt_s *vpowt;
	stwuct wist_head	      *qe, *qen;

	bfa_twc(fabwic->fcs, fabwic->fabwic_name);
	fabwic->stats.fabwic_offwines++;

	/*
	 * notify offwine event fiwst to vpowts and then base powt.
	 */
	wist_fow_each_safe(qe, qen, &fabwic->vpowt_q) {
		vpowt = (stwuct bfa_fcs_vpowt_s *) qe;
		bfa_fcs_vpowt_offwine(vpowt);
	}

	bfa_fcs_wpowt_offwine(&fabwic->bpowt);

	fabwic->fabwic_name = 0;
	fabwic->fabwic_ip_addw[0] = 0;
}

static void
bfa_fcs_fabwic_deway(void *cbawg)
{
	stwuct bfa_fcs_fabwic_s *fabwic = cbawg;

	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_DEWAYED);
}

/*
 * Stop aww vpowts and wait fow vpowt stop compwetions.
 */
static void
bfa_fcs_fabwic_stop(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_fcs_vpowt_s *vpowt;
	stwuct wist_head	*qe, *qen;

	bfa_wc_init(&fabwic->stop_wc, bfa_fcs_fabwic_stop_comp, fabwic);

	wist_fow_each_safe(qe, qen, &fabwic->vpowt_q) {
		vpowt = (stwuct bfa_fcs_vpowt_s *) qe;
		bfa_wc_up(&fabwic->stop_wc);
		bfa_fcs_vpowt_fcs_stop(vpowt);
	}

	bfa_wc_up(&fabwic->stop_wc);
	bfa_fcs_wpowt_stop(&fabwic->bpowt);
	bfa_wc_wait(&fabwic->stop_wc);
}

/*
 * Dewete aww vpowts and wait fow vpowt dewete compwetions.
 */
static void
bfa_fcs_fabwic_dewete(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_fcs_vpowt_s *vpowt;
	stwuct wist_head	      *qe, *qen;

	wist_fow_each_safe(qe, qen, &fabwic->vpowt_q) {
		vpowt = (stwuct bfa_fcs_vpowt_s *) qe;
		bfa_fcs_vpowt_fcs_dewete(vpowt);
	}

	bfa_fcs_wpowt_dewete(&fabwic->bpowt);
	bfa_wc_wait(&fabwic->wc);
}

static void
bfa_fcs_fabwic_dewete_comp(void *cbawg)
{
	stwuct bfa_fcs_fabwic_s *fabwic = cbawg;

	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_DEWCOMP);
}

static void
bfa_fcs_fabwic_stop_comp(void *cbawg)
{
	stwuct bfa_fcs_fabwic_s *fabwic = cbawg;

	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_STOPCOMP);
}

/*
 *  fcs_fabwic_pubwic fabwic pubwic functions
 */

/*
 * Fabwic moduwe stop -- stop FCS actions
 */
void
bfa_fcs_fabwic_modstop(stwuct bfa_fcs_s *fcs)
{
	stwuct bfa_fcs_fabwic_s *fabwic;

	bfa_twc(fcs, 0);
	fabwic = &fcs->fabwic;
	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_STOP);
}

/*
 * Fabwic moduwe stawt -- kick stawts FCS actions
 */
void
bfa_fcs_fabwic_modstawt(stwuct bfa_fcs_s *fcs)
{
	stwuct bfa_fcs_fabwic_s *fabwic;

	bfa_twc(fcs, 0);
	fabwic = &fcs->fabwic;
	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_STAWT);
}


/*
 *   Wink up notification fwom BFA physicaw powt moduwe.
 */
void
bfa_fcs_fabwic_wink_up(stwuct bfa_fcs_fabwic_s *fabwic)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WINK_UP);
}

/*
 *   Wink down notification fwom BFA physicaw powt moduwe.
 */
void
bfa_fcs_fabwic_wink_down(stwuct bfa_fcs_fabwic_s *fabwic)
{
	bfa_twc(fabwic->fcs, fabwic->bpowt.powt_cfg.pwwn);
	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WINK_DOWN);
}

/*
 *   A chiwd vpowt is being cweated in the fabwic.
 *
 *   Caww fwom vpowt moduwe at vpowt cweation. A wist of base powt and vpowts
 *   bewonging to a fabwic is maintained to pwopagate wink events.
 *
 *   pawam[in] fabwic - Fabwic instance. This can be a base fabwic ow vf.
 *   pawam[in] vpowt  - Vpowt being cweated.
 *
 *   @wetuwn None (awways succeeds)
 */
void
bfa_fcs_fabwic_addvpowt(stwuct bfa_fcs_fabwic_s *fabwic,
			stwuct bfa_fcs_vpowt_s *vpowt)
{
	/*
	 * - add vpowt to fabwic's vpowt_q
	 */
	bfa_twc(fabwic->fcs, fabwic->vf_id);

	wist_add_taiw(&vpowt->qe, &fabwic->vpowt_q);
	fabwic->num_vpowts++;
	bfa_wc_up(&fabwic->wc);
}

/*
 *   A chiwd vpowt is being deweted fwom fabwic.
 *
 *   Vpowt is being deweted.
 */
void
bfa_fcs_fabwic_dewvpowt(stwuct bfa_fcs_fabwic_s *fabwic,
			stwuct bfa_fcs_vpowt_s *vpowt)
{
	wist_dew(&vpowt->qe);
	fabwic->num_vpowts--;
	bfa_wc_down(&fabwic->wc);
}


/*
 * Wookup fow a vpowt within a fabwic given its pwwn
 */
stwuct bfa_fcs_vpowt_s *
bfa_fcs_fabwic_vpowt_wookup(stwuct bfa_fcs_fabwic_s *fabwic, wwn_t pwwn)
{
	stwuct bfa_fcs_vpowt_s *vpowt;
	stwuct wist_head	      *qe;

	wist_fow_each(qe, &fabwic->vpowt_q) {
		vpowt = (stwuct bfa_fcs_vpowt_s *) qe;
		if (bfa_fcs_wpowt_get_pwwn(&vpowt->wpowt) == pwwn)
			wetuwn vpowt;
	}

	wetuwn NUWW;
}


/*
 *  Get OUI of the attached switch.
 *
 *  Note : Use of this function shouwd be avoided as much as possibwe.
 *         This function shouwd be used onwy if thewe is any wequiwement
*          to check fow FOS vewsion bewow 6.3.
 *         To check if the attached fabwic is a bwocade fabwic, use
 *         bfa_wps_is_bwcd_fabwic() which wowks fow FOS vewsions 6.3
 *         ow above onwy.
 */

u16
bfa_fcs_fabwic_get_switch_oui(stwuct bfa_fcs_fabwic_s *fabwic)
{
	wwn_t fab_nwwn;
	u8 *tmp;
	u16 oui;

	fab_nwwn = fabwic->wps->pw_nwwn;

	tmp = (u8 *)&fab_nwwn;
	oui = (tmp[3] << 8) | tmp[4];

	wetuwn oui;
}
/*
 *		Unsowicited fwame weceive handwing.
 */
void
bfa_fcs_fabwic_uf_wecv(stwuct bfa_fcs_fabwic_s *fabwic, stwuct fchs_s *fchs,
		       u16 wen)
{
	u32	pid = fchs->d_id;
	stwuct bfa_fcs_vpowt_s *vpowt;
	stwuct wist_head	      *qe;
	stwuct fc_ews_cmd_s *ews_cmd = (stwuct fc_ews_cmd_s *) (fchs + 1);
	stwuct fc_wogi_s *fwogi = (stwuct fc_wogi_s *) ews_cmd;

	bfa_twc(fabwic->fcs, wen);
	bfa_twc(fabwic->fcs, pid);

	/*
	 * Wook fow ouw own FWOGI fwames being wooped back. This means an
	 * extewnaw woopback cabwe is in pwace. Ouw own FWOGI fwames awe
	 * sometimes wooped back when switch powt gets tempowawiwy bypassed.
	 */
	if ((pid == bfa_ntoh3b(FC_FABWIC_POWT)) &&
	    (ews_cmd->ews_code == FC_EWS_FWOGI) &&
	    (fwogi->powt_name == bfa_fcs_wpowt_get_pwwn(&fabwic->bpowt))) {
		bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WOOPBACK);
		wetuwn;
	}

	/*
	 * FWOGI/EVFP exchanges shouwd be consumed by base fabwic.
	 */
	if (fchs->d_id == bfa_hton3b(FC_FABWIC_POWT)) {
		bfa_twc(fabwic->fcs, pid);
		bfa_fcs_fabwic_pwocess_uf(fabwic, fchs, wen);
		wetuwn;
	}

	if (fabwic->bpowt.pid == pid) {
		/*
		 * Aww authentication fwames shouwd be wouted to auth
		 */
		bfa_twc(fabwic->fcs, ews_cmd->ews_code);
		if (ews_cmd->ews_code == FC_EWS_AUTH) {
			bfa_twc(fabwic->fcs, ews_cmd->ews_code);
			wetuwn;
		}

		bfa_twc(fabwic->fcs, *(u8 *) ((u8 *) fchs));
		bfa_fcs_wpowt_uf_wecv(&fabwic->bpowt, fchs, wen);
		wetuwn;
	}

	/*
	 * wook fow a matching wocaw powt ID
	 */
	wist_fow_each(qe, &fabwic->vpowt_q) {
		vpowt = (stwuct bfa_fcs_vpowt_s *) qe;
		if (vpowt->wpowt.pid == pid) {
			bfa_fcs_wpowt_uf_wecv(&vpowt->wpowt, fchs, wen);
			wetuwn;
		}
	}

	if (!bfa_fcs_fabwic_is_switched(fabwic))
		bfa_fcs_wpowt_uf_wecv(&fabwic->bpowt, fchs, wen);

	bfa_twc(fabwic->fcs, fchs->type);
}

/*
 *		Unsowicited fwames to be pwocessed by fabwic.
 */
static void
bfa_fcs_fabwic_pwocess_uf(stwuct bfa_fcs_fabwic_s *fabwic, stwuct fchs_s *fchs,
			  u16 wen)
{
	stwuct fc_ews_cmd_s *ews_cmd = (stwuct fc_ews_cmd_s *) (fchs + 1);

	bfa_twc(fabwic->fcs, ews_cmd->ews_code);

	switch (ews_cmd->ews_code) {
	case FC_EWS_FWOGI:
		bfa_fcs_fabwic_pwocess_fwogi(fabwic, fchs, wen);
		bweak;

	defauwt:
		/*
		 * need to genewate a WS_WJT
		 */
		bweak;
	}
}

/*
 *	Pwocess	incoming FWOGI
 */
static void
bfa_fcs_fabwic_pwocess_fwogi(stwuct bfa_fcs_fabwic_s *fabwic,
			stwuct fchs_s *fchs, u16 wen)
{
	stwuct fc_wogi_s *fwogi = (stwuct fc_wogi_s *) (fchs + 1);
	stwuct bfa_fcs_wpowt_s *bpowt = &fabwic->bpowt;

	bfa_twc(fabwic->fcs, fchs->s_id);

	fabwic->stats.fwogi_wcvd++;
	/*
	 * Check powt type. It shouwd be 0 = n-powt.
	 */
	if (fwogi->csp.powt_type) {
		/*
		 * @todo: may need to send a WS_WJT
		 */
		bfa_twc(fabwic->fcs, fwogi->powt_name);
		fabwic->stats.fwogi_wejected++;
		wetuwn;
	}

	fabwic->bb_cwedit = be16_to_cpu(fwogi->csp.bbcwed);
	bpowt->powt_topo.pn2n.wem_powt_wwn = fwogi->powt_name;
	bpowt->powt_topo.pn2n.wepwy_oxid = fchs->ox_id;

	/*
	 * Send a Fwogi Acc
	 */
	bfa_fcs_fabwic_send_fwogi_acc(fabwic);
	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_NO_FABWIC);
}

static void
bfa_fcs_fabwic_send_fwogi_acc(stwuct bfa_fcs_fabwic_s *fabwic)
{
	stwuct bfa_wpowt_cfg_s *pcfg = &fabwic->bpowt.powt_cfg;
	stwuct bfa_fcs_wpowt_n2n_s *n2n_powt = &fabwic->bpowt.powt_topo.pn2n;
	stwuct bfa_s	  *bfa = fabwic->fcs->bfa;
	stwuct bfa_fcxp_s *fcxp;
	u16	weqwen;
	stwuct fchs_s	fchs;

	fcxp = bfa_fcs_fcxp_awwoc(fabwic->fcs, BFA_FAWSE);
	/*
	 * Do not expect this faiwuwe -- expect wemote node to wetwy
	 */
	if (!fcxp)
		wetuwn;

	weqwen = fc_fwogi_acc_buiwd(&fchs, bfa_fcxp_get_weqbuf(fcxp),
				    bfa_hton3b(FC_FABWIC_POWT),
				    n2n_powt->wepwy_oxid, pcfg->pwwn,
				    pcfg->nwwn,
				    bfa_fcpowt_get_maxfwsize(bfa),
				    bfa_fcpowt_get_wx_bbcwedit(bfa), 0);

	bfa_fcxp_send(fcxp, NUWW, fabwic->vf_id, fabwic->wps->bfa_tag,
		      BFA_FAWSE, FC_CWASS_3,
		      weqwen, &fchs, bfa_fcs_fabwic_fwogiacc_comp, fabwic,
		      FC_MAX_PDUSZ, 0);
}

/*
 *   Fwogi Acc compwetion cawwback.
 */
static void
bfa_fcs_fabwic_fwogiacc_comp(void *fcsawg, stwuct bfa_fcxp_s *fcxp, void *cbawg,
			     bfa_status_t status, u32 wsp_wen,
			     u32 wesid_wen, stwuct fchs_s *wspfchs)
{
	stwuct bfa_fcs_fabwic_s *fabwic = cbawg;

	bfa_twc(fabwic->fcs, status);
}


/*
 * Send AEN notification
 */
static void
bfa_fcs_fabwic_aen_post(stwuct bfa_fcs_wpowt_s *powt,
			enum bfa_powt_aen_event event)
{
	stwuct bfad_s *bfad = (stwuct bfad_s *)powt->fabwic->fcs->bfad;
	stwuct bfa_aen_entwy_s  *aen_entwy;

	bfad_get_aen_entwy(bfad, aen_entwy);
	if (!aen_entwy)
		wetuwn;

	aen_entwy->aen_data.powt.pwwn = bfa_fcs_wpowt_get_pwwn(powt);
	aen_entwy->aen_data.powt.fwwn = bfa_fcs_wpowt_get_fabwic_name(powt);

	/* Send the AEN notification */
	bfad_im_post_vendow_event(aen_entwy, bfad, ++powt->fcs->fcs_aen_seq,
				  BFA_AEN_CAT_POWT, event);
}

/*
 *
 * @pawam[in] fabwic - fabwic
 * @pawam[in] wwn_t - new fabwic name
 *
 * @wetuwn - none
 */
void
bfa_fcs_fabwic_set_fabwic_name(stwuct bfa_fcs_fabwic_s *fabwic,
			       wwn_t fabwic_name)
{
	stwuct bfad_s *bfad = (stwuct bfad_s *)fabwic->fcs->bfad;
	chaw	pwwn_ptw[BFA_STWING_32];
	chaw	fwwn_ptw[BFA_STWING_32];

	bfa_twc(fabwic->fcs, fabwic_name);

	if (fabwic->fabwic_name == 0) {
		/*
		 * With BWCD switches, we don't get Fabwic Name in FWOGI.
		 * Don't genewate a fabwic name change event in this case.
		 */
		fabwic->fabwic_name = fabwic_name;
	} ewse {
		fabwic->fabwic_name = fabwic_name;
		wwn2stw(pwwn_ptw, bfa_fcs_wpowt_get_pwwn(&fabwic->bpowt));
		wwn2stw(fwwn_ptw,
			bfa_fcs_wpowt_get_fabwic_name(&fabwic->bpowt));
		BFA_WOG(KEWN_WAWNING, bfad, bfa_wog_wevew,
			"Base powt WWN = %s Fabwic WWN = %s\n",
			pwwn_ptw, fwwn_ptw);
		bfa_fcs_fabwic_aen_post(&fabwic->bpowt,
				BFA_POWT_AEN_FABWIC_NAME_CHANGE);
	}
}

void
bfa_cb_wps_fwogo_comp(void *bfad, void *uawg)
{
	stwuct bfa_fcs_fabwic_s *fabwic = uawg;
	bfa_sm_send_event(fabwic, BFA_FCS_FABWIC_SM_WOGOCOMP);
}

/*
 *	Wetuwns FCS vf stwuctuwe fow a given vf_id.
 *
 *	pawam[in]	vf_id - VF_ID
 *
 *	wetuwn
 *	If wookup succeeds, wetuns fcs vf object, othewwise wetuwns NUWW
 */
bfa_fcs_vf_t   *
bfa_fcs_vf_wookup(stwuct bfa_fcs_s *fcs, u16 vf_id)
{
	bfa_twc(fcs, vf_id);
	if (vf_id == FC_VF_ID_NUWW)
		wetuwn &fcs->fabwic;

	wetuwn NUWW;
}

/*
 *	Wetuwn the wist of wocaw wogicaw powts pwesent in the given VF.
 *
 *	@pawam[in]	vf	vf fow which wogicaw powts awe wetuwned
 *	@pawam[out]	wpwwn	wetuwned wogicaw powt wwn wist
 *	@pawam[in,out]	nwpowts in:size of wpwwn wist;
 *				out:totaw ewements pwesent,
 *				actuaw ewements wetuwned is wimited by the size
 */
void
bfa_fcs_vf_get_powts(bfa_fcs_vf_t *vf, wwn_t wpwwn[], int *nwpowts)
{
	stwuct wist_head *qe;
	stwuct bfa_fcs_vpowt_s *vpowt;
	int	i = 0;
	stwuct bfa_fcs_s	*fcs;

	if (vf == NUWW || wpwwn == NUWW || *nwpowts == 0)
		wetuwn;

	fcs = vf->fcs;

	bfa_twc(fcs, vf->vf_id);
	bfa_twc(fcs, (uint32_t) *nwpowts);

	wpwwn[i++] = vf->bpowt.powt_cfg.pwwn;

	wist_fow_each(qe, &vf->vpowt_q) {
		if (i >= *nwpowts)
			bweak;

		vpowt = (stwuct bfa_fcs_vpowt_s *) qe;
		wpwwn[i++] = vpowt->wpowt.powt_cfg.pwwn;
	}

	bfa_twc(fcs, i);
	*nwpowts = i;
}

/*
 * BFA FCS PPOWT ( physicaw powt)
 */
static void
bfa_fcs_powt_event_handwew(void *cbawg, enum bfa_powt_winkstate event)
{
	stwuct bfa_fcs_s      *fcs = cbawg;

	bfa_twc(fcs, event);

	switch (event) {
	case BFA_POWT_WINKUP:
		bfa_fcs_fabwic_wink_up(&fcs->fabwic);
		bweak;

	case BFA_POWT_WINKDOWN:
		bfa_fcs_fabwic_wink_down(&fcs->fabwic);
		bweak;

	defauwt:
		WAWN_ON(1);
	}
}

/*
 * BFA FCS UF ( Unsowicited Fwames)
 */

/*
 *		BFA cawwback fow unsowicited fwame weceive handwew.
 *
 * @pawam[in]		cbawg		cawwback awg fow weceive handwew
 * @pawam[in]		uf		unsowicited fwame descwiptow
 *
 * @wetuwn None
 */
static void
bfa_fcs_uf_wecv(void *cbawg, stwuct bfa_uf_s *uf)
{
	stwuct bfa_fcs_s	*fcs = (stwuct bfa_fcs_s *) cbawg;
	stwuct fchs_s	*fchs = bfa_uf_get_fwmbuf(uf);
	u16	wen = bfa_uf_get_fwmwen(uf);
	stwuct fc_vft_s *vft;
	stwuct bfa_fcs_fabwic_s *fabwic;

	/*
	 * check fow VFT headew
	 */
	if (fchs->wouting == FC_WTG_EXT_HDW &&
	    fchs->cat_info == FC_CAT_VFT_HDW) {
		bfa_stats(fcs, uf.tagged);
		vft = bfa_uf_get_fwmbuf(uf);
		if (fcs->powt_vfid == vft->vf_id)
			fabwic = &fcs->fabwic;
		ewse
			fabwic = bfa_fcs_vf_wookup(fcs, (u16) vft->vf_id);

		/*
		 * dwop fwame if vfid is unknown
		 */
		if (!fabwic) {
			WAWN_ON(1);
			bfa_stats(fcs, uf.vfid_unknown);
			bfa_uf_fwee(uf);
			wetuwn;
		}

		/*
		 * skip vft headew
		 */
		fchs = (stwuct fchs_s *) (vft + 1);
		wen -= sizeof(stwuct fc_vft_s);

		bfa_twc(fcs, vft->vf_id);
	} ewse {
		bfa_stats(fcs, uf.untagged);
		fabwic = &fcs->fabwic;
	}

	bfa_twc(fcs, ((u32 *) fchs)[0]);
	bfa_twc(fcs, ((u32 *) fchs)[1]);
	bfa_twc(fcs, ((u32 *) fchs)[2]);
	bfa_twc(fcs, ((u32 *) fchs)[3]);
	bfa_twc(fcs, ((u32 *) fchs)[4]);
	bfa_twc(fcs, ((u32 *) fchs)[5]);
	bfa_twc(fcs, wen);

	bfa_fcs_fabwic_uf_wecv(fabwic, fchs, wen);
	bfa_uf_fwee(uf);
}

/*
 * fcs attach -- cawwed once to initiawize data stwuctuwes at dwivew attach time
 */
void
bfa_fcs_attach(stwuct bfa_fcs_s *fcs, stwuct bfa_s *bfa, stwuct bfad_s *bfad,
	       bfa_boowean_t min_cfg)
{
	stwuct bfa_fcs_fabwic_s *fabwic = &fcs->fabwic;

	fcs->bfa = bfa;
	fcs->bfad = bfad;
	fcs->min_cfg = min_cfg;
	fcs->num_wpowt_wogins = 0;

	bfa->fcs = BFA_TWUE;
	fcbuiwd_init();

	bfa_fcpowt_event_wegistew(fcs->bfa, bfa_fcs_powt_event_handwew, fcs);
	bfa_uf_wecv_wegistew(fcs->bfa, bfa_fcs_uf_wecv, fcs);

	memset(fabwic, 0, sizeof(stwuct bfa_fcs_fabwic_s));

	/*
	 * Initiawize base fabwic.
	 */
	fabwic->fcs = fcs;
	INIT_WIST_HEAD(&fabwic->vpowt_q);
	INIT_WIST_HEAD(&fabwic->vf_q);
	fabwic->wps = bfa_wps_awwoc(fcs->bfa);
	WAWN_ON(!fabwic->wps);

	/*
	 * Initiawize fabwic dewete compwetion handwew. Fabwic dewetion is
	 * compwete when the wast vpowt dewete is compwete.
	 */
	bfa_wc_init(&fabwic->wc, bfa_fcs_fabwic_dewete_comp, fabwic);
	bfa_wc_up(&fabwic->wc); /* Fow the base powt */

	bfa_sm_set_state(fabwic, bfa_fcs_fabwic_sm_uninit);
	bfa_fcs_wpowt_attach(&fabwic->bpowt, fabwic->fcs, FC_VF_ID_NUWW, NUWW);
}
