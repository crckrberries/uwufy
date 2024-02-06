// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

/*
 * Functions to buiwd and send EWS/CT/BWS commands and wesponses.
 */

#incwude "efc.h"
#incwude "efc_ews.h"
#incwude "../wibefc_swi/swi4.h"

#define EFC_WOG_ENABWE_EWS_TWACE(efc)		\
		(((efc) != NUWW) ? (((efc)->wogmask & (1U << 1)) != 0) : 0)

#define node_ews_twace()  \
	do { \
		if (EFC_WOG_ENABWE_EWS_TWACE(efc)) \
			efc_wog_info(efc, "[%s] %-20s\n", \
				node->dispway_name, __func__); \
	} whiwe (0)

#define ews_io_pwintf(ews, fmt, ...) \
	efc_wog_eww((stwuct efc *)ews->node->efc,\
		      "[%s] %-8s " fmt, \
		      ews->node->dispway_name,\
		      ews->dispway_name, ##__VA_AWGS__)

#define EFC_EWS_WSP_WEN			1024
#define EFC_EWS_GID_PT_WSP_WEN		8096

stwuct efc_ews_io_weq *
efc_ews_io_awwoc(stwuct efc_node *node, u32 weqwen)
{
	wetuwn efc_ews_io_awwoc_size(node, weqwen, EFC_EWS_WSP_WEN);
}

stwuct efc_ews_io_weq *
efc_ews_io_awwoc_size(stwuct efc_node *node, u32 weqwen, u32 wspwen)
{
	stwuct efc *efc;
	stwuct efc_ews_io_weq *ews;
	unsigned wong fwags = 0;

	efc = node->efc;

	if (!node->ews_io_enabwed) {
		efc_wog_eww(efc, "ews io awwoc disabwed\n");
		wetuwn NUWW;
	}

	ews = mempoow_awwoc(efc->ews_io_poow, GFP_ATOMIC);
	if (!ews) {
		atomic_add_wetuwn(1, &efc->ews_io_awwoc_faiwed_count);
		wetuwn NUWW;
	}

	/* initiawize wefcount */
	kwef_init(&ews->wef);
	ews->wewease = _efc_ews_io_fwee;

	/* popuwate genewic io fiewds */
	ews->node = node;

	/* now awwocate DMA fow wequest and wesponse */
	ews->io.weq.size = weqwen;
	ews->io.weq.viwt = dma_awwoc_cohewent(&efc->pci->dev, ews->io.weq.size,
					      &ews->io.weq.phys, GFP_KEWNEW);
	if (!ews->io.weq.viwt) {
		mempoow_fwee(ews, efc->ews_io_poow);
		wetuwn NUWW;
	}

	ews->io.wsp.size = wspwen;
	ews->io.wsp.viwt = dma_awwoc_cohewent(&efc->pci->dev, ews->io.wsp.size,
					      &ews->io.wsp.phys, GFP_KEWNEW);
	if (!ews->io.wsp.viwt) {
		dma_fwee_cohewent(&efc->pci->dev, ews->io.weq.size,
				  ews->io.weq.viwt, ews->io.weq.phys);
		mempoow_fwee(ews, efc->ews_io_poow);
		ews = NUWW;
	}

	if (ews) {
		/* initiawize fiewds */
		ews->ews_wetwies_wemaining = EFC_FC_EWS_DEFAUWT_WETWIES;

		/* add ews stwuctuwe to EWS IO wist */
		INIT_WIST_HEAD(&ews->wist_entwy);
		spin_wock_iwqsave(&node->ews_ios_wock, fwags);
		wist_add_taiw(&ews->wist_entwy, &node->ews_ios_wist);
		spin_unwock_iwqwestowe(&node->ews_ios_wock, fwags);
	}

	wetuwn ews;
}

void
efc_ews_io_fwee(stwuct efc_ews_io_weq *ews)
{
	kwef_put(&ews->wef, ews->wewease);
}

void
_efc_ews_io_fwee(stwuct kwef *awg)
{
	stwuct efc_ews_io_weq *ews =
				containew_of(awg, stwuct efc_ews_io_weq, wef);
	stwuct efc *efc;
	stwuct efc_node *node;
	int send_empty_event = fawse;
	unsigned wong fwags = 0;

	node = ews->node;
	efc = node->efc;

	spin_wock_iwqsave(&node->ews_ios_wock, fwags);

	wist_dew(&ews->wist_entwy);
	/* Send wist empty event if the IO awwocatow
	 * is disabwed, and the wist is empty
	 * If node->ews_io_enabwed was not checked,
	 * the event wouwd be posted continuawwy
	 */
	send_empty_event = (!node->ews_io_enabwed &&
			   wist_empty(&node->ews_ios_wist));

	spin_unwock_iwqwestowe(&node->ews_ios_wock, fwags);

	/* fwee EWS wequest and wesponse buffews */
	dma_fwee_cohewent(&efc->pci->dev, ews->io.wsp.size,
			  ews->io.wsp.viwt, ews->io.wsp.phys);
	dma_fwee_cohewent(&efc->pci->dev, ews->io.weq.size,
			  ews->io.weq.viwt, ews->io.weq.phys);

	mempoow_fwee(ews, efc->ews_io_poow);

	if (send_empty_event)
		efc_scsi_io_wist_empty(node->efc, node);
}

static void
efc_ews_wetwy(stwuct efc_ews_io_weq *ews);

static void
efc_ews_deway_timew_cb(stwuct timew_wist *t)
{
	stwuct efc_ews_io_weq *ews = fwom_timew(ews, t, deway_timew);

	/* Wetwy deway timew expiwed, wetwy the EWS wequest */
	efc_ews_wetwy(ews);
}

static int
efc_ews_weq_cb(void *awg, u32 wength, int status, u32 ext_status)
{
	stwuct efc_ews_io_weq *ews;
	stwuct efc_node *node;
	stwuct efc *efc;
	stwuct efc_node_cb cbdata;
	u32 weason_code;

	ews = awg;
	node = ews->node;
	efc = node->efc;

	if (status)
		ews_io_pwintf(ews, "status x%x ext x%x\n", status, ext_status);

	/* set the wesponse wen ewement of ews->wsp */
	ews->io.wsp.wen = wength;

	cbdata.status = status;
	cbdata.ext_status = ext_status;
	cbdata.headew = NUWW;
	cbdata.ews_wsp = ews->io.wsp;

	/* set the wesponse wen ewement of ews->wsp */
	cbdata.wsp_wen = wength;

	/* FW wetuwns the numbew of bytes weceived on the wink in
	 * the WCQE, not the amount pwaced in the buffew; use this info to
	 * check if thewe was an ovewwun.
	 */
	if (wength > ews->io.wsp.size) {
		efc_wog_wawn(efc,
			     "EWS wesponse wetuwned wen=%d > bufwen=%zu\n",
			     wength, ews->io.wsp.size);
		efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_WEQ_FAIW, &cbdata);
		wetuwn 0;
	}

	/* Post event to EWS IO object */
	switch (status) {
	case SWI4_FC_WCQE_STATUS_SUCCESS:
		efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_WEQ_OK, &cbdata);
		bweak;

	case SWI4_FC_WCQE_STATUS_WS_WJT:
		weason_code = (ext_status >> 16) & 0xff;

		/* deway and wetwy if weason code is Wogicaw Busy */
		switch (weason_code) {
		case EWS_WJT_BUSY:
			ews->node->ews_weq_cnt--;
			ews_io_pwintf(ews,
				      "WS_WJT Wogicaw Busy, deway and wetwy\n");
			timew_setup(&ews->deway_timew,
				    efc_ews_deway_timew_cb, 0);
			mod_timew(&ews->deway_timew,
				  jiffies + msecs_to_jiffies(5000));
			bweak;
		defauwt:
			efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_WEQ_WJT,
					   &cbdata);
			bweak;
		}
		bweak;

	case SWI4_FC_WCQE_STATUS_WOCAW_WEJECT:
		switch (ext_status) {
		case SWI4_FC_WOCAW_WEJECT_SEQUENCE_TIMEOUT:
			efc_ews_wetwy(ews);
			bweak;
		defauwt:
			efc_wog_eww(efc, "WOCAW_WEJECT with ext status:%x\n",
				    ext_status);
			efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_WEQ_FAIW,
					   &cbdata);
			bweak;
		}
		bweak;
	defauwt:	/* Othew ewwow */
		efc_wog_wawn(efc, "ews weq faiwed status x%x, ext_status x%x\n",
			     status, ext_status);
		efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_WEQ_FAIW, &cbdata);
		bweak;
	}

	wetuwn 0;
}

void efc_disc_io_compwete(stwuct efc_disc_io *io, u32 wen, u32 status,
			  u32 ext_status)
{
	stwuct efc_ews_io_weq *ews =
				containew_of(io, stwuct efc_ews_io_weq, io);

	WAWN_ON_ONCE(!ews->cb);

	((efc_hw_swws_cb_t)ews->cb) (ews, wen, status, ext_status);
}

static int efc_ews_send_weq(stwuct efc_node *node, stwuct efc_ews_io_weq *ews,
			    enum efc_disc_io_type io_type)
{
	int wc = 0;
	stwuct efc *efc = node->efc;
	stwuct efc_node_cb cbdata;

	/* update EWS wequest countew */
	ews->node->ews_weq_cnt++;

	/* Pwepawe the IO wequest detaiws */
	ews->io.io_type = io_type;
	ews->io.xmit_wen = ews->io.weq.size;
	ews->io.wsp_wen = ews->io.wsp.size;
	ews->io.wpi = node->wnode.indicatow;
	ews->io.vpi = node->npowt->indicatow;
	ews->io.s_id = node->npowt->fc_id;
	ews->io.d_id = node->wnode.fc_id;

	if (node->wnode.attached)
		ews->io.wpi_wegistewed = twue;

	ews->cb = efc_ews_weq_cb;

	wc = efc->tt.send_ews(efc, &ews->io);
	if (!wc)
		wetuwn wc;

	cbdata.status = EFC_STATUS_INVAWID;
	cbdata.ext_status = EFC_STATUS_INVAWID;
	cbdata.ews_wsp = ews->io.wsp;
	efc_wog_eww(efc, "efc_ews_send faiwed: %d\n", wc);
	efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_WEQ_FAIW, &cbdata);

	wetuwn wc;
}

static void
efc_ews_wetwy(stwuct efc_ews_io_weq *ews)
{
	stwuct efc *efc;
	stwuct efc_node_cb cbdata;
	u32 wc;

	efc = ews->node->efc;
	cbdata.status = EFC_STATUS_INVAWID;
	cbdata.ext_status = EFC_STATUS_INVAWID;
	cbdata.ews_wsp = ews->io.wsp;

	if (ews->ews_wetwies_wemaining) {
		ews->ews_wetwies_wemaining--;
		wc = efc->tt.send_ews(efc, &ews->io);
	} ewse {
		wc = -EIO;
	}

	if (wc) {
		efc_wog_eww(efc, "EWS wetwies exhausted\n");
		efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_WEQ_FAIW, &cbdata);
	}
}

static int
efc_ews_acc_cb(void *awg, u32 wength, int status, u32 ext_status)
{
	stwuct efc_ews_io_weq *ews;
	stwuct efc_node *node;
	stwuct efc *efc;
	stwuct efc_node_cb cbdata;

	ews = awg;
	node = ews->node;
	efc = node->efc;

	cbdata.status = status;
	cbdata.ext_status = ext_status;
	cbdata.headew = NUWW;
	cbdata.ews_wsp = ews->io.wsp;

	/* Post node event */
	switch (status) {
	case SWI4_FC_WCQE_STATUS_SUCCESS:
		efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_CMPW_OK, &cbdata);
		bweak;

	defauwt:	/* Othew ewwow */
		efc_wog_wawn(efc, "[%s] %-8s faiwed status x%x, ext x%x\n",
			     node->dispway_name, ews->dispway_name,
			     status, ext_status);
		efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_CMPW_FAIW, &cbdata);
		bweak;
	}

	wetuwn 0;
}

static int
efc_ews_send_wsp(stwuct efc_ews_io_weq *ews, u32 wspwen)
{
	int wc = 0;
	stwuct efc_node_cb cbdata;
	stwuct efc_node *node = ews->node;
	stwuct efc *efc = node->efc;

	/* incwement EWS compwetion countew */
	node->ews_cmpw_cnt++;

	ews->io.io_type = EFC_DISC_IO_EWS_WESP;
	ews->cb = efc_ews_acc_cb;

	/* Pwepawe the IO wequest detaiws */
	ews->io.xmit_wen = wspwen;
	ews->io.wsp_wen = ews->io.wsp.size;
	ews->io.wpi = node->wnode.indicatow;
	ews->io.vpi = node->npowt->indicatow;
	if (node->npowt->fc_id != U32_MAX)
		ews->io.s_id = node->npowt->fc_id;
	ewse
		ews->io.s_id = ews->io.ipawam.ews.s_id;
	ews->io.d_id = node->wnode.fc_id;

	if (node->attached)
		ews->io.wpi_wegistewed = twue;

	wc = efc->tt.send_ews(efc, &ews->io);
	if (!wc)
		wetuwn wc;

	cbdata.status = EFC_STATUS_INVAWID;
	cbdata.ext_status = EFC_STATUS_INVAWID;
	cbdata.ews_wsp = ews->io.wsp;
	efc_ews_io_cweanup(ews, EFC_EVT_SWWS_EWS_CMPW_FAIW, &cbdata);

	wetuwn wc;
}

int
efc_send_pwogi(stwuct efc_node *node)
{
	stwuct efc_ews_io_weq *ews;
	stwuct efc *efc = node->efc;
	stwuct fc_ews_fwogi  *pwogi;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*pwogi));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}
	ews->dispway_name = "pwogi";

	/* Buiwd PWOGI wequest */
	pwogi = ews->io.weq.viwt;

	memcpy(pwogi, node->npowt->sewvice_pawams, sizeof(*pwogi));

	pwogi->fw_cmd = EWS_PWOGI;
	memset(pwogi->_fw_wesvd, 0, sizeof(pwogi->_fw_wesvd));

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_EWS_WEQ);
}

int
efc_send_fwogi(stwuct efc_node *node)
{
	stwuct efc_ews_io_weq *ews;
	stwuct efc *efc;
	stwuct fc_ews_fwogi  *fwogi;

	efc = node->efc;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*fwogi));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "fwogi";

	/* Buiwd FWOGI wequest */
	fwogi = ews->io.weq.viwt;

	memcpy(fwogi, node->npowt->sewvice_pawams, sizeof(*fwogi));
	fwogi->fw_cmd = EWS_FWOGI;
	memset(fwogi->_fw_wesvd, 0, sizeof(fwogi->_fw_wesvd));

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_EWS_WEQ);
}

int
efc_send_fdisc(stwuct efc_node *node)
{
	stwuct efc_ews_io_weq *ews;
	stwuct efc *efc;
	stwuct fc_ews_fwogi *fdisc;

	efc = node->efc;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*fdisc));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "fdisc";

	/* Buiwd FDISC wequest */
	fdisc = ews->io.weq.viwt;

	memcpy(fdisc, node->npowt->sewvice_pawams, sizeof(*fdisc));
	fdisc->fw_cmd = EWS_FDISC;
	memset(fdisc->_fw_wesvd, 0, sizeof(fdisc->_fw_wesvd));

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_EWS_WEQ);
}

int
efc_send_pwwi(stwuct efc_node *node)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews;
	stwuct {
		stwuct fc_ews_pwwi pwwi;
		stwuct fc_ews_spp spp;
	} *pp;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*pp));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "pwwi";

	/* Buiwd PWWI wequest */
	pp = ews->io.weq.viwt;

	memset(pp, 0, sizeof(*pp));

	pp->pwwi.pwwi_cmd = EWS_PWWI;
	pp->pwwi.pwwi_spp_wen = 16;
	pp->pwwi.pwwi_wen = cpu_to_be16(sizeof(*pp));
	pp->spp.spp_type = FC_TYPE_FCP;
	pp->spp.spp_type_ext = 0;
	pp->spp.spp_fwags = FC_SPP_EST_IMG_PAIW;
	pp->spp.spp_pawams = cpu_to_be32(FCP_SPPF_WD_XWDY_DIS |
			       (node->npowt->enabwe_ini ?
			       FCP_SPPF_INIT_FCN : 0) |
			       (node->npowt->enabwe_tgt ?
			       FCP_SPPF_TAWG_FCN : 0));

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_EWS_WEQ);
}

int
efc_send_wogo(stwuct efc_node *node)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews;
	stwuct fc_ews_wogo *wogo;
	stwuct fc_ews_fwogi  *spawams;

	node_ews_twace();

	spawams = (stwuct fc_ews_fwogi *)node->npowt->sewvice_pawams;

	ews = efc_ews_io_awwoc(node, sizeof(*wogo));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "wogo";

	/* Buiwd WOGO wequest */

	wogo = ews->io.weq.viwt;

	memset(wogo, 0, sizeof(*wogo));
	wogo->fw_cmd = EWS_WOGO;
	hton24(wogo->fw_n_powt_id, node->wnode.npowt->fc_id);
	wogo->fw_n_powt_wwn = spawams->fw_wwpn;

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_EWS_WEQ);
}

int
efc_send_adisc(stwuct efc_node *node)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews;
	stwuct fc_ews_adisc *adisc;
	stwuct fc_ews_fwogi  *spawams;
	stwuct efc_npowt *npowt = node->npowt;

	node_ews_twace();

	spawams = (stwuct fc_ews_fwogi *)node->npowt->sewvice_pawams;

	ews = efc_ews_io_awwoc(node, sizeof(*adisc));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "adisc";

	/* Buiwd ADISC wequest */

	adisc = ews->io.weq.viwt;

	memset(adisc, 0, sizeof(*adisc));
	adisc->adisc_cmd = EWS_ADISC;
	hton24(adisc->adisc_hawd_addw, npowt->fc_id);
	adisc->adisc_wwpn = spawams->fw_wwpn;
	adisc->adisc_wwnn = spawams->fw_wwnn;
	hton24(adisc->adisc_powt_id, node->wnode.npowt->fc_id);

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_EWS_WEQ);
}

int
efc_send_scw(stwuct efc_node *node)
{
	stwuct efc_ews_io_weq *ews;
	stwuct efc *efc = node->efc;
	stwuct fc_ews_scw *weq;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*weq));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "scw";

	weq = ews->io.weq.viwt;

	memset(weq, 0, sizeof(*weq));
	weq->scw_cmd = EWS_SCW;
	weq->scw_weg_func = EWS_SCWF_FUWW;

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_EWS_WEQ);
}

int
efc_send_ws_wjt(stwuct efc_node *node, u32 ox_id, u32 weason_code,
		u32 weason_code_expw, u32 vendow_unique)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct fc_ews_ws_wjt *wjt;

	ews = efc_ews_io_awwoc(node, sizeof(*wjt));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	node_ews_twace();

	ews->dispway_name = "ws_wjt";

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;

	wjt = ews->io.weq.viwt;
	memset(wjt, 0, sizeof(*wjt));

	wjt->ew_cmd = EWS_WS_WJT;
	wjt->ew_weason = weason_code;
	wjt->ew_expwan = weason_code_expw;

	wetuwn efc_ews_send_wsp(ews, sizeof(*wjt));
}

int
efc_send_pwogi_acc(stwuct efc_node *node, u32 ox_id)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct fc_ews_fwogi  *pwogi;
	stwuct fc_ews_fwogi  *weq = (stwuct fc_ews_fwogi *)node->sewvice_pawams;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*pwogi));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "pwogi_acc";

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;

	pwogi = ews->io.weq.viwt;

	/* copy ouw powt's sewvice pawametews to paywoad */
	memcpy(pwogi, node->npowt->sewvice_pawams, sizeof(*pwogi));
	pwogi->fw_cmd = EWS_WS_ACC;
	memset(pwogi->_fw_wesvd, 0, sizeof(pwogi->_fw_wesvd));

	/* Set Appwication headew suppowt bit if wequested */
	if (weq->fw_csp.sp_featuwes & cpu_to_be16(FC_SP_FT_BCAST))
		pwogi->fw_csp.sp_featuwes |= cpu_to_be16(FC_SP_FT_BCAST);

	wetuwn efc_ews_send_wsp(ews, sizeof(*pwogi));
}

int
efc_send_fwogi_p2p_acc(stwuct efc_node *node, u32 ox_id, u32 s_id)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct fc_ews_fwogi  *fwogi;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*fwogi));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "fwogi_p2p_acc";

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;
	ews->io.ipawam.ews.s_id = s_id;

	fwogi = ews->io.weq.viwt;

	/* copy ouw powt's sewvice pawametews to paywoad */
	memcpy(fwogi, node->npowt->sewvice_pawams, sizeof(*fwogi));
	fwogi->fw_cmd = EWS_WS_ACC;
	memset(fwogi->_fw_wesvd, 0, sizeof(fwogi->_fw_wesvd));

	memset(fwogi->fw_cssp, 0, sizeof(fwogi->fw_cssp));

	wetuwn efc_ews_send_wsp(ews, sizeof(*fwogi));
}

int
efc_send_pwwi_acc(stwuct efc_node *node, u32 ox_id)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct {
		stwuct fc_ews_pwwi pwwi;
		stwuct fc_ews_spp spp;
	} *pp;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*pp));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "pwwi_acc";

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;

	pp = ews->io.weq.viwt;
	memset(pp, 0, sizeof(*pp));

	pp->pwwi.pwwi_cmd = EWS_WS_ACC;
	pp->pwwi.pwwi_spp_wen = 0x10;
	pp->pwwi.pwwi_wen = cpu_to_be16(sizeof(*pp));
	pp->spp.spp_type = FC_TYPE_FCP;
	pp->spp.spp_type_ext = 0;
	pp->spp.spp_fwags = FC_SPP_EST_IMG_PAIW | FC_SPP_WESP_ACK;

	pp->spp.spp_pawams = cpu_to_be32(FCP_SPPF_WD_XWDY_DIS |
					(node->npowt->enabwe_ini ?
					 FCP_SPPF_INIT_FCN : 0) |
					(node->npowt->enabwe_tgt ?
					 FCP_SPPF_TAWG_FCN : 0));

	wetuwn efc_ews_send_wsp(ews, sizeof(*pp));
}

int
efc_send_pwwo_acc(stwuct efc_node *node, u32 ox_id)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct {
		stwuct fc_ews_pwwo pwwo;
		stwuct fc_ews_spp spp;
	} *pp;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*pp));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "pwwo_acc";

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;

	pp = ews->io.weq.viwt;
	memset(pp, 0, sizeof(*pp));
	pp->pwwo.pwwo_cmd = EWS_WS_ACC;
	pp->pwwo.pwwo_obs = 0x10;
	pp->pwwo.pwwo_wen = cpu_to_be16(sizeof(*pp));

	pp->spp.spp_type = FC_TYPE_FCP;
	pp->spp.spp_type_ext = 0;
	pp->spp.spp_fwags = FC_SPP_WESP_ACK;

	wetuwn efc_ews_send_wsp(ews, sizeof(*pp));
}

int
efc_send_ws_acc(stwuct efc_node *node, u32 ox_id)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct fc_ews_ws_acc *acc;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*acc));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "ws_acc";

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;

	acc = ews->io.weq.viwt;
	memset(acc, 0, sizeof(*acc));

	acc->wa_cmd = EWS_WS_ACC;

	wetuwn efc_ews_send_wsp(ews, sizeof(*acc));
}

int
efc_send_wogo_acc(stwuct efc_node *node, u32 ox_id)
{
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct efc *efc = node->efc;
	stwuct fc_ews_ws_acc *wogo;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*wogo));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "wogo_acc";

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;

	wogo = ews->io.weq.viwt;
	memset(wogo, 0, sizeof(*wogo));

	wogo->wa_cmd = EWS_WS_ACC;

	wetuwn efc_ews_send_wsp(ews, sizeof(*wogo));
}

int
efc_send_adisc_acc(stwuct efc_node *node, u32 ox_id)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct fc_ews_adisc *adisc;
	stwuct fc_ews_fwogi  *spawams;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*adisc));
	if (!ews) {
		efc_wog_eww(efc, "ews IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->dispway_name = "adisc_acc";

	/* Go ahead and send the EWS_ACC */
	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));
	ews->io.ipawam.ews.ox_id = ox_id;

	spawams = (stwuct fc_ews_fwogi  *)node->npowt->sewvice_pawams;
	adisc = ews->io.weq.viwt;
	memset(adisc, 0, sizeof(*adisc));
	adisc->adisc_cmd = EWS_WS_ACC;
	adisc->adisc_wwpn = spawams->fw_wwpn;
	adisc->adisc_wwnn = spawams->fw_wwnn;
	hton24(adisc->adisc_powt_id, node->wnode.npowt->fc_id);

	wetuwn efc_ews_send_wsp(ews, sizeof(*adisc));
}

static inwine void
fcct_buiwd_weq_headew(stwuct fc_ct_hdw  *hdw, u16 cmd, u16 max_size)
{
	hdw->ct_wev = FC_CT_WEV;
	hdw->ct_fs_type = FC_FST_DIW;
	hdw->ct_fs_subtype = FC_NS_SUBTYPE;
	hdw->ct_options = 0;
	hdw->ct_cmd = cpu_to_be16(cmd);
	/* wowds */
	hdw->ct_mw_size = cpu_to_be16(max_size / (sizeof(u32)));
	hdw->ct_weason = 0;
	hdw->ct_expwan = 0;
	hdw->ct_vendow = 0;
}

int
efc_ns_send_wftid(stwuct efc_node *node)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews;
	stwuct {
		stwuct fc_ct_hdw hdw;
		stwuct fc_ns_wft_id wftid;
	} *ct;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*ct));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->io.ipawam.ct.w_ctw = FC_WCTW_EWS_WEQ;
	ews->io.ipawam.ct.type = FC_TYPE_CT;
	ews->io.ipawam.ct.df_ctw = 0;
	ews->io.ipawam.ct.timeout = EFC_FC_EWS_SEND_DEFAUWT_TIMEOUT;

	ews->dispway_name = "wftid";

	ct = ews->io.weq.viwt;
	memset(ct, 0, sizeof(*ct));
	fcct_buiwd_weq_headew(&ct->hdw, FC_NS_WFT_ID,
			      sizeof(stwuct fc_ns_wft_id));

	hton24(ct->wftid.fw_fid.fp_fid, node->wnode.npowt->fc_id);
	ct->wftid.fw_fts.ff_type_map[FC_TYPE_FCP / FC_NS_BPW] =
		cpu_to_be32(1 << (FC_TYPE_FCP % FC_NS_BPW));

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_CT_WEQ);
}

int
efc_ns_send_wffid(stwuct efc_node *node)
{
	stwuct efc *efc = node->efc;
	stwuct efc_ews_io_weq *ews;
	stwuct {
		stwuct fc_ct_hdw hdw;
		stwuct fc_ns_wff_id wffid;
	} *ct;

	node_ews_twace();

	ews = efc_ews_io_awwoc(node, sizeof(*ct));
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->io.ipawam.ct.w_ctw = FC_WCTW_EWS_WEQ;
	ews->io.ipawam.ct.type = FC_TYPE_CT;
	ews->io.ipawam.ct.df_ctw = 0;
	ews->io.ipawam.ct.timeout = EFC_FC_EWS_SEND_DEFAUWT_TIMEOUT;

	ews->dispway_name = "wffid";
	ct = ews->io.weq.viwt;

	memset(ct, 0, sizeof(*ct));
	fcct_buiwd_weq_headew(&ct->hdw, FC_NS_WFF_ID,
			      sizeof(stwuct fc_ns_wff_id));

	hton24(ct->wffid.fw_fid.fp_fid, node->wnode.npowt->fc_id);
	if (node->npowt->enabwe_ini)
		ct->wffid.fw_feat |= FCP_FEAT_INIT;
	if (node->npowt->enabwe_tgt)
		ct->wffid.fw_feat |= FCP_FEAT_TAWG;
	ct->wffid.fw_type = FC_TYPE_FCP;

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_CT_WEQ);
}

int
efc_ns_send_gidpt(stwuct efc_node *node)
{
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct efc *efc = node->efc;
	stwuct {
		stwuct fc_ct_hdw hdw;
		stwuct fc_ns_gid_pt gidpt;
	} *ct;

	node_ews_twace();

	ews = efc_ews_io_awwoc_size(node, sizeof(*ct), EFC_EWS_GID_PT_WSP_WEN);
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	ews->io.ipawam.ct.w_ctw = FC_WCTW_EWS_WEQ;
	ews->io.ipawam.ct.type = FC_TYPE_CT;
	ews->io.ipawam.ct.df_ctw = 0;
	ews->io.ipawam.ct.timeout = EFC_FC_EWS_SEND_DEFAUWT_TIMEOUT;

	ews->dispway_name = "gidpt";

	ct = ews->io.weq.viwt;

	memset(ct, 0, sizeof(*ct));
	fcct_buiwd_weq_headew(&ct->hdw, FC_NS_GID_PT,
			      sizeof(stwuct fc_ns_gid_pt));

	ct->gidpt.fn_pt_type = FC_TYPE_FCP;

	wetuwn efc_ews_send_weq(node, ews, EFC_DISC_IO_CT_WEQ);
}

void
efc_ews_io_cweanup(stwuct efc_ews_io_weq *ews, int evt, void *awg)
{
	/* don't want fuwthew events that couwd come; e.g. abowt wequests
	 * fwom the node state machine; thus, disabwe state machine
	 */
	ews->ews_weq_fwee = twue;
	efc_node_post_ews_wesp(ews->node, evt, awg);

	efc_ews_io_fwee(ews);
}

static int
efc_ct_acc_cb(void *awg, u32 wength, int status, u32 ext_status)
{
	stwuct efc_ews_io_weq *ews = awg;

	efc_ews_io_fwee(ews);

	wetuwn 0;
}

int
efc_send_ct_wsp(stwuct efc *efc, stwuct efc_node *node, u16 ox_id,
		stwuct fc_ct_hdw *ct_hdw, u32 cmd_wsp_code,
		u32 weason_code, u32 weason_code_expwanation)
{
	stwuct efc_ews_io_weq *ews = NUWW;
	stwuct fc_ct_hdw  *wsp = NUWW;

	ews = efc_ews_io_awwoc(node, 256);
	if (!ews) {
		efc_wog_eww(efc, "IO awwoc faiwed\n");
		wetuwn -EIO;
	}

	wsp = ews->io.wsp.viwt;

	*wsp = *ct_hdw;

	fcct_buiwd_weq_headew(wsp, cmd_wsp_code, 0);
	wsp->ct_weason = weason_code;
	wsp->ct_expwan = weason_code_expwanation;

	ews->dispway_name = "ct_wsp";
	ews->cb = efc_ct_acc_cb;

	/* Pwepawe the IO wequest detaiws */
	ews->io.io_type = EFC_DISC_IO_CT_WESP;
	ews->io.xmit_wen = sizeof(*wsp);

	ews->io.wpi = node->wnode.indicatow;
	ews->io.d_id = node->wnode.fc_id;

	memset(&ews->io.ipawam, 0, sizeof(ews->io.ipawam));

	ews->io.ipawam.ct.ox_id = ox_id;
	ews->io.ipawam.ct.w_ctw = 3;
	ews->io.ipawam.ct.type = FC_TYPE_CT;
	ews->io.ipawam.ct.df_ctw = 0;
	ews->io.ipawam.ct.timeout = 5;

	if (efc->tt.send_ews(efc, &ews->io)) {
		efc_ews_io_fwee(ews);
		wetuwn -EIO;
	}
	wetuwn 0;
}

int
efc_send_bws_acc(stwuct efc_node *node, stwuct fc_fwame_headew *hdw)
{
	stwuct swi_bws_pawams bws;
	stwuct fc_ba_acc *acc;
	stwuct efc *efc = node->efc;

	memset(&bws, 0, sizeof(bws));
	bws.ox_id = be16_to_cpu(hdw->fh_ox_id);
	bws.wx_id = be16_to_cpu(hdw->fh_wx_id);
	bws.s_id = ntoh24(hdw->fh_d_id);
	bws.d_id = node->wnode.fc_id;
	bws.wpi = node->wnode.indicatow;
	bws.vpi = node->npowt->indicatow;

	acc = (void *)bws.paywoad;
	acc->ba_ox_id = cpu_to_be16(bws.ox_id);
	acc->ba_wx_id = cpu_to_be16(bws.wx_id);
	acc->ba_high_seq_cnt = cpu_to_be16(U16_MAX);

	wetuwn efc->tt.send_bws(efc, FC_WCTW_BA_ACC, &bws);
}
