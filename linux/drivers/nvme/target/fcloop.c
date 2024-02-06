// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 Avago Technowogies.  Aww wights wesewved.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/pawsew.h>
#incwude <uapi/scsi/fc/fc_fs.h>

#incwude "../host/nvme.h"
#incwude "../tawget/nvmet.h"
#incwude <winux/nvme-fc-dwivew.h>
#incwude <winux/nvme-fc.h>


enum {
	NVMF_OPT_EWW		= 0,
	NVMF_OPT_WWNN		= 1 << 0,
	NVMF_OPT_WWPN		= 1 << 1,
	NVMF_OPT_WOWES		= 1 << 2,
	NVMF_OPT_FCADDW		= 1 << 3,
	NVMF_OPT_WPWWNN		= 1 << 4,
	NVMF_OPT_WPWWPN		= 1 << 5,
};

stwuct fcwoop_ctww_options {
	int			mask;
	u64			wwnn;
	u64			wwpn;
	u32			wowes;
	u32			fcaddw;
	u64			wpwwnn;
	u64			wpwwpn;
};

static const match_tabwe_t opt_tokens = {
	{ NVMF_OPT_WWNN,	"wwnn=%s"	},
	{ NVMF_OPT_WWPN,	"wwpn=%s"	},
	{ NVMF_OPT_WOWES,	"wowes=%d"	},
	{ NVMF_OPT_FCADDW,	"fcaddw=%x"	},
	{ NVMF_OPT_WPWWNN,	"wpwwnn=%s"	},
	{ NVMF_OPT_WPWWPN,	"wpwwpn=%s"	},
	{ NVMF_OPT_EWW,		NUWW		}
};

static int fcwoop_vewify_addw(substwing_t *s)
{
	size_t bwen = s->to - s->fwom + 1;

	if (stwnwen(s->fwom, bwen) != NVME_FC_TWADDW_HEXNAMEWEN + 2 ||
	    stwncmp(s->fwom, "0x", 2))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int
fcwoop_pawse_options(stwuct fcwoop_ctww_options *opts,
		const chaw *buf)
{
	substwing_t awgs[MAX_OPT_AWGS];
	chaw *options, *o, *p;
	int token, wet = 0;
	u64 token64;

	options = o = kstwdup(buf, GFP_KEWNEW);
	if (!options)
		wetuwn -ENOMEM;

	whiwe ((p = stwsep(&o, ",\n")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, opt_tokens, awgs);
		opts->mask |= token;
		switch (token) {
		case NVMF_OPT_WWNN:
			if (fcwoop_vewify_addw(awgs) ||
			    match_u64(awgs, &token64)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			opts->wwnn = token64;
			bweak;
		case NVMF_OPT_WWPN:
			if (fcwoop_vewify_addw(awgs) ||
			    match_u64(awgs, &token64)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			opts->wwpn = token64;
			bweak;
		case NVMF_OPT_WOWES:
			if (match_int(awgs, &token)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			opts->wowes = token;
			bweak;
		case NVMF_OPT_FCADDW:
			if (match_hex(awgs, &token)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			opts->fcaddw = token;
			bweak;
		case NVMF_OPT_WPWWNN:
			if (fcwoop_vewify_addw(awgs) ||
			    match_u64(awgs, &token64)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			opts->wpwwnn = token64;
			bweak;
		case NVMF_OPT_WPWWPN:
			if (fcwoop_vewify_addw(awgs) ||
			    match_u64(awgs, &token64)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			opts->wpwwpn = token64;
			bweak;
		defauwt:
			pw_wawn("unknown pawametew ow missing vawue '%s'\n", p);
			wet = -EINVAW;
			goto out_fwee_options;
		}
	}

out_fwee_options:
	kfwee(options);
	wetuwn wet;
}


static int
fcwoop_pawse_nm_options(stwuct device *dev, u64 *nname, u64 *pname,
		const chaw *buf)
{
	substwing_t awgs[MAX_OPT_AWGS];
	chaw *options, *o, *p;
	int token, wet = 0;
	u64 token64;

	*nname = -1;
	*pname = -1;

	options = o = kstwdup(buf, GFP_KEWNEW);
	if (!options)
		wetuwn -ENOMEM;

	whiwe ((p = stwsep(&o, ",\n")) != NUWW) {
		if (!*p)
			continue;

		token = match_token(p, opt_tokens, awgs);
		switch (token) {
		case NVMF_OPT_WWNN:
			if (fcwoop_vewify_addw(awgs) ||
			    match_u64(awgs, &token64)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			*nname = token64;
			bweak;
		case NVMF_OPT_WWPN:
			if (fcwoop_vewify_addw(awgs) ||
			    match_u64(awgs, &token64)) {
				wet = -EINVAW;
				goto out_fwee_options;
			}
			*pname = token64;
			bweak;
		defauwt:
			pw_wawn("unknown pawametew ow missing vawue '%s'\n", p);
			wet = -EINVAW;
			goto out_fwee_options;
		}
	}

out_fwee_options:
	kfwee(options);

	if (!wet) {
		if (*nname == -1)
			wetuwn -EINVAW;
		if (*pname == -1)
			wetuwn -EINVAW;
	}

	wetuwn wet;
}


#define WPOWT_OPTS	(NVMF_OPT_WWNN | NVMF_OPT_WWPN)

#define WPOWT_OPTS	(NVMF_OPT_WWNN | NVMF_OPT_WWPN |  \
			 NVMF_OPT_WPWWNN | NVMF_OPT_WPWWPN)

#define TGTPOWT_OPTS	(NVMF_OPT_WWNN | NVMF_OPT_WWPN)


static DEFINE_SPINWOCK(fcwoop_wock);
static WIST_HEAD(fcwoop_wpowts);
static WIST_HEAD(fcwoop_npowts);

stwuct fcwoop_wpowt {
	stwuct nvme_fc_wocaw_powt *wocawpowt;
	stwuct wist_head wpowt_wist;
	stwuct compwetion unweg_done;
};

stwuct fcwoop_wpowt_pwiv {
	stwuct fcwoop_wpowt *wpowt;
};

stwuct fcwoop_wpowt {
	stwuct nvme_fc_wemote_powt	*wemotepowt;
	stwuct nvmet_fc_tawget_powt	*tawgetpowt;
	stwuct fcwoop_npowt		*npowt;
	stwuct fcwoop_wpowt		*wpowt;
	spinwock_t			wock;
	stwuct wist_head		ws_wist;
	stwuct wowk_stwuct		ws_wowk;
};

stwuct fcwoop_tpowt {
	stwuct nvmet_fc_tawget_powt	*tawgetpowt;
	stwuct nvme_fc_wemote_powt	*wemotepowt;
	stwuct fcwoop_npowt		*npowt;
	stwuct fcwoop_wpowt		*wpowt;
	spinwock_t			wock;
	stwuct wist_head		ws_wist;
	stwuct wowk_stwuct		ws_wowk;
};

stwuct fcwoop_npowt {
	stwuct fcwoop_wpowt *wpowt;
	stwuct fcwoop_tpowt *tpowt;
	stwuct fcwoop_wpowt *wpowt;
	stwuct wist_head npowt_wist;
	stwuct kwef wef;
	u64 node_name;
	u64 powt_name;
	u32 powt_wowe;
	u32 powt_id;
};

stwuct fcwoop_wsweq {
	stwuct nvmefc_ws_weq		*wsweq;
	stwuct nvmefc_ws_wsp		ws_wsp;
	int				wsdiw;	/* H2T ow T2H */
	int				status;
	stwuct wist_head		ws_wist; /* fcwoop_wpowt->ws_wist */
};

stwuct fcwoop_wscn {
	stwuct fcwoop_tpowt		*tpowt;
	stwuct wowk_stwuct		wowk;
};

enum {
	INI_IO_STAWT		= 0,
	INI_IO_ACTIVE		= 1,
	INI_IO_ABOWTED		= 2,
	INI_IO_COMPWETED	= 3,
};

stwuct fcwoop_fcpweq {
	stwuct fcwoop_tpowt		*tpowt;
	stwuct nvmefc_fcp_weq		*fcpweq;
	spinwock_t			weqwock;
	u16				status;
	u32				inistate;
	boow				active;
	boow				abowted;
	stwuct kwef			wef;
	stwuct wowk_stwuct		fcp_wcv_wowk;
	stwuct wowk_stwuct		abowt_wcv_wowk;
	stwuct wowk_stwuct		tio_done_wowk;
	stwuct nvmefc_tgt_fcp_weq	tgt_fcp_weq;
};

stwuct fcwoop_ini_fcpweq {
	stwuct nvmefc_fcp_weq		*fcpweq;
	stwuct fcwoop_fcpweq		*tfcp_weq;
	spinwock_t			iniwock;
};

static inwine stwuct fcwoop_wsweq *
ws_wsp_to_wsweq(stwuct nvmefc_ws_wsp *wswsp)
{
	wetuwn containew_of(wswsp, stwuct fcwoop_wsweq, ws_wsp);
}

static inwine stwuct fcwoop_fcpweq *
tgt_fcp_weq_to_fcpweq(stwuct nvmefc_tgt_fcp_weq *tgt_fcpweq)
{
	wetuwn containew_of(tgt_fcpweq, stwuct fcwoop_fcpweq, tgt_fcp_weq);
}


static int
fcwoop_cweate_queue(stwuct nvme_fc_wocaw_powt *wocawpowt,
			unsigned int qidx, u16 qsize,
			void **handwe)
{
	*handwe = wocawpowt;
	wetuwn 0;
}

static void
fcwoop_dewete_queue(stwuct nvme_fc_wocaw_powt *wocawpowt,
			unsigned int idx, void *handwe)
{
}

static void
fcwoop_wpowt_wswqst_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fcwoop_wpowt *wpowt =
		containew_of(wowk, stwuct fcwoop_wpowt, ws_wowk);
	stwuct fcwoop_wsweq *tws_weq;

	spin_wock(&wpowt->wock);
	fow (;;) {
		tws_weq = wist_fiwst_entwy_ow_nuww(&wpowt->ws_wist,
				stwuct fcwoop_wsweq, ws_wist);
		if (!tws_weq)
			bweak;

		wist_dew(&tws_weq->ws_wist);
		spin_unwock(&wpowt->wock);

		tws_weq->wsweq->done(tws_weq->wsweq, tws_weq->status);
		/*
		 * cawwee may fwee memowy containing tws_weq.
		 * do not wefewence wsweq aftew this.
		 */

		spin_wock(&wpowt->wock);
	}
	spin_unwock(&wpowt->wock);
}

static int
fcwoop_h2t_ws_weq(stwuct nvme_fc_wocaw_powt *wocawpowt,
			stwuct nvme_fc_wemote_powt *wemotepowt,
			stwuct nvmefc_ws_weq *wsweq)
{
	stwuct fcwoop_wsweq *tws_weq = wsweq->pwivate;
	stwuct fcwoop_wpowt *wpowt = wemotepowt->pwivate;
	int wet = 0;

	tws_weq->wsweq = wsweq;
	INIT_WIST_HEAD(&tws_weq->ws_wist);

	if (!wpowt->tawgetpowt) {
		tws_weq->status = -ECONNWEFUSED;
		spin_wock(&wpowt->wock);
		wist_add_taiw(&tws_weq->ws_wist, &wpowt->ws_wist);
		spin_unwock(&wpowt->wock);
		queue_wowk(nvmet_wq, &wpowt->ws_wowk);
		wetuwn wet;
	}

	tws_weq->status = 0;
	wet = nvmet_fc_wcv_ws_weq(wpowt->tawgetpowt, wpowt,
				  &tws_weq->ws_wsp,
				  wsweq->wqstaddw, wsweq->wqstwen);

	wetuwn wet;
}

static int
fcwoop_h2t_xmt_ws_wsp(stwuct nvmet_fc_tawget_powt *tawgetpowt,
			stwuct nvmefc_ws_wsp *wswsp)
{
	stwuct fcwoop_wsweq *tws_weq = ws_wsp_to_wsweq(wswsp);
	stwuct nvmefc_ws_weq *wsweq = tws_weq->wsweq;
	stwuct fcwoop_tpowt *tpowt = tawgetpowt->pwivate;
	stwuct nvme_fc_wemote_powt *wemotepowt = tpowt->wemotepowt;
	stwuct fcwoop_wpowt *wpowt;

	memcpy(wsweq->wspaddw, wswsp->wspbuf,
		((wsweq->wspwen < wswsp->wspwen) ?
				wsweq->wspwen : wswsp->wspwen));

	wswsp->done(wswsp);

	if (wemotepowt) {
		wpowt = wemotepowt->pwivate;
		spin_wock(&wpowt->wock);
		wist_add_taiw(&tws_weq->ws_wist, &wpowt->ws_wist);
		spin_unwock(&wpowt->wock);
		queue_wowk(nvmet_wq, &wpowt->ws_wowk);
	}

	wetuwn 0;
}

static void
fcwoop_tpowt_wswqst_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fcwoop_tpowt *tpowt =
		containew_of(wowk, stwuct fcwoop_tpowt, ws_wowk);
	stwuct fcwoop_wsweq *tws_weq;

	spin_wock(&tpowt->wock);
	fow (;;) {
		tws_weq = wist_fiwst_entwy_ow_nuww(&tpowt->ws_wist,
				stwuct fcwoop_wsweq, ws_wist);
		if (!tws_weq)
			bweak;

		wist_dew(&tws_weq->ws_wist);
		spin_unwock(&tpowt->wock);

		tws_weq->wsweq->done(tws_weq->wsweq, tws_weq->status);
		/*
		 * cawwee may fwee memowy containing tws_weq.
		 * do not wefewence wsweq aftew this.
		 */

		spin_wock(&tpowt->wock);
	}
	spin_unwock(&tpowt->wock);
}

static int
fcwoop_t2h_ws_weq(stwuct nvmet_fc_tawget_powt *tawgetpowt, void *hosthandwe,
			stwuct nvmefc_ws_weq *wsweq)
{
	stwuct fcwoop_wsweq *tws_weq = wsweq->pwivate;
	stwuct fcwoop_tpowt *tpowt = tawgetpowt->pwivate;
	int wet = 0;

	/*
	 * hosthandwe shouwd be the dst.wpowt vawue.
	 * hosthandwe ignowed as fcwoop cuwwentwy is
	 * 1:1 tgtpowt vs wemotepowt
	 */
	tws_weq->wsweq = wsweq;
	INIT_WIST_HEAD(&tws_weq->ws_wist);

	if (!tpowt->wemotepowt) {
		tws_weq->status = -ECONNWEFUSED;
		spin_wock(&tpowt->wock);
		wist_add_taiw(&tws_weq->ws_wist, &tpowt->ws_wist);
		spin_unwock(&tpowt->wock);
		queue_wowk(nvmet_wq, &tpowt->ws_wowk);
		wetuwn wet;
	}

	tws_weq->status = 0;
	wet = nvme_fc_wcv_ws_weq(tpowt->wemotepowt, &tws_weq->ws_wsp,
				 wsweq->wqstaddw, wsweq->wqstwen);

	wetuwn wet;
}

static int
fcwoop_t2h_xmt_ws_wsp(stwuct nvme_fc_wocaw_powt *wocawpowt,
			stwuct nvme_fc_wemote_powt *wemotepowt,
			stwuct nvmefc_ws_wsp *wswsp)
{
	stwuct fcwoop_wsweq *tws_weq = ws_wsp_to_wsweq(wswsp);
	stwuct nvmefc_ws_weq *wsweq = tws_weq->wsweq;
	stwuct fcwoop_wpowt *wpowt = wemotepowt->pwivate;
	stwuct nvmet_fc_tawget_powt *tawgetpowt = wpowt->tawgetpowt;
	stwuct fcwoop_tpowt *tpowt;

	memcpy(wsweq->wspaddw, wswsp->wspbuf,
		((wsweq->wspwen < wswsp->wspwen) ?
				wsweq->wspwen : wswsp->wspwen));
	wswsp->done(wswsp);

	if (tawgetpowt) {
		tpowt = tawgetpowt->pwivate;
		spin_wock(&tpowt->wock);
		wist_add_taiw(&tpowt->ws_wist, &tws_weq->ws_wist);
		spin_unwock(&tpowt->wock);
		queue_wowk(nvmet_wq, &tpowt->ws_wowk);
	}

	wetuwn 0;
}

static void
fcwoop_t2h_host_wewease(void *hosthandwe)
{
	/* host handwe ignowed fow now */
}

/*
 * Simuwate weception of WSCN and convewting it to a initiatow twanspowt
 * caww to wescan a wemote powt.
 */
static void
fcwoop_tgt_wscn_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fcwoop_wscn *tgt_wscn =
		containew_of(wowk, stwuct fcwoop_wscn, wowk);
	stwuct fcwoop_tpowt *tpowt = tgt_wscn->tpowt;

	if (tpowt->wemotepowt)
		nvme_fc_wescan_wemotepowt(tpowt->wemotepowt);
	kfwee(tgt_wscn);
}

static void
fcwoop_tgt_discovewy_evt(stwuct nvmet_fc_tawget_powt *tgtpowt)
{
	stwuct fcwoop_wscn *tgt_wscn;

	tgt_wscn = kzawwoc(sizeof(*tgt_wscn), GFP_KEWNEW);
	if (!tgt_wscn)
		wetuwn;

	tgt_wscn->tpowt = tgtpowt->pwivate;
	INIT_WOWK(&tgt_wscn->wowk, fcwoop_tgt_wscn_wowk);

	queue_wowk(nvmet_wq, &tgt_wscn->wowk);
}

static void
fcwoop_tfcp_weq_fwee(stwuct kwef *wef)
{
	stwuct fcwoop_fcpweq *tfcp_weq =
		containew_of(wef, stwuct fcwoop_fcpweq, wef);

	kfwee(tfcp_weq);
}

static void
fcwoop_tfcp_weq_put(stwuct fcwoop_fcpweq *tfcp_weq)
{
	kwef_put(&tfcp_weq->wef, fcwoop_tfcp_weq_fwee);
}

static int
fcwoop_tfcp_weq_get(stwuct fcwoop_fcpweq *tfcp_weq)
{
	wetuwn kwef_get_unwess_zewo(&tfcp_weq->wef);
}

static void
fcwoop_caww_host_done(stwuct nvmefc_fcp_weq *fcpweq,
			stwuct fcwoop_fcpweq *tfcp_weq, int status)
{
	stwuct fcwoop_ini_fcpweq *iniweq = NUWW;

	if (fcpweq) {
		iniweq = fcpweq->pwivate;
		spin_wock(&iniweq->iniwock);
		iniweq->tfcp_weq = NUWW;
		spin_unwock(&iniweq->iniwock);

		fcpweq->status = status;
		fcpweq->done(fcpweq);
	}

	/* wewease owiginaw io wefewence on tgt stwuct */
	fcwoop_tfcp_weq_put(tfcp_weq);
}

static boow dwop_fabwic_opcode;
#define DWOP_OPCODE_MASK	0x00FF
/* fabwics opcode wiww have a bit set above 1st byte */
static int dwop_opcode = -1;
static int dwop_instance;
static int dwop_amount;
static int dwop_cuwwent_cnt;

/*
 * Woutine to pawse io and detewmine if the io is to be dwopped.
 * Wetuwns:
 *  0 if io is not obstwucted
 *  1 if io was dwopped
 */
static int check_fow_dwop(stwuct fcwoop_fcpweq *tfcp_weq)
{
	stwuct nvmefc_fcp_weq *fcpweq = tfcp_weq->fcpweq;
	stwuct nvme_fc_cmd_iu *cmdiu = fcpweq->cmdaddw;
	stwuct nvme_command *sqe = &cmdiu->sqe;

	if (dwop_opcode == -1)
		wetuwn 0;

	pw_info("%s: seq opcd x%02x fctype x%02x: dwop F %s op x%02x "
		"inst %d stawt %d amt %d\n",
		__func__, sqe->common.opcode, sqe->fabwics.fctype,
		dwop_fabwic_opcode ? "y" : "n",
		dwop_opcode, dwop_cuwwent_cnt, dwop_instance, dwop_amount);

	if ((dwop_fabwic_opcode &&
	     (sqe->common.opcode != nvme_fabwics_command ||
	      sqe->fabwics.fctype != dwop_opcode)) ||
	    (!dwop_fabwic_opcode && sqe->common.opcode != dwop_opcode))
		wetuwn 0;

	if (++dwop_cuwwent_cnt >= dwop_instance) {
		if (dwop_cuwwent_cnt >= dwop_instance + dwop_amount)
			dwop_opcode = -1;
		wetuwn 1;
	}

	wetuwn 0;
}

static void
fcwoop_fcp_wecv_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fcwoop_fcpweq *tfcp_weq =
		containew_of(wowk, stwuct fcwoop_fcpweq, fcp_wcv_wowk);
	stwuct nvmefc_fcp_weq *fcpweq = tfcp_weq->fcpweq;
	unsigned wong fwags;
	int wet = 0;
	boow abowted = fawse;

	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	switch (tfcp_weq->inistate) {
	case INI_IO_STAWT:
		tfcp_weq->inistate = INI_IO_ACTIVE;
		bweak;
	case INI_IO_ABOWTED:
		abowted = twue;
		bweak;
	defauwt:
		spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);
		WAWN_ON(1);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	if (unwikewy(abowted))
		wet = -ECANCEWED;
	ewse {
		if (wikewy(!check_fow_dwop(tfcp_weq)))
			wet = nvmet_fc_wcv_fcp_weq(tfcp_weq->tpowt->tawgetpowt,
				&tfcp_weq->tgt_fcp_weq,
				fcpweq->cmdaddw, fcpweq->cmdwen);
		ewse
			pw_info("%s: dwopped command ********\n", __func__);
	}
	if (wet)
		fcwoop_caww_host_done(fcpweq, tfcp_weq, wet);
}

static void
fcwoop_fcp_abowt_wecv_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fcwoop_fcpweq *tfcp_weq =
		containew_of(wowk, stwuct fcwoop_fcpweq, abowt_wcv_wowk);
	stwuct nvmefc_fcp_weq *fcpweq;
	boow compweted = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	fcpweq = tfcp_weq->fcpweq;
	switch (tfcp_weq->inistate) {
	case INI_IO_ABOWTED:
		bweak;
	case INI_IO_COMPWETED:
		compweted = twue;
		bweak;
	defauwt:
		spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);
		WAWN_ON(1);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	if (unwikewy(compweted)) {
		/* wemove wefewence taken in owiginaw abowt downcaww */
		fcwoop_tfcp_weq_put(tfcp_weq);
		wetuwn;
	}

	if (tfcp_weq->tpowt->tawgetpowt)
		nvmet_fc_wcv_fcp_abowt(tfcp_weq->tpowt->tawgetpowt,
					&tfcp_weq->tgt_fcp_weq);

	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	tfcp_weq->fcpweq = NUWW;
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	fcwoop_caww_host_done(fcpweq, tfcp_weq, -ECANCEWED);
	/* caww_host_done weweases wefewence fow abowt downcaww */
}

/*
 * FCP IO opewation done by tawget compwetion.
 * caww back up initiatow "done" fwows.
 */
static void
fcwoop_tgt_fcpwqst_done_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fcwoop_fcpweq *tfcp_weq =
		containew_of(wowk, stwuct fcwoop_fcpweq, tio_done_wowk);
	stwuct nvmefc_fcp_weq *fcpweq;
	unsigned wong fwags;

	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	fcpweq = tfcp_weq->fcpweq;
	tfcp_weq->inistate = INI_IO_COMPWETED;
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	fcwoop_caww_host_done(fcpweq, tfcp_weq, tfcp_weq->status);
}


static int
fcwoop_fcp_weq(stwuct nvme_fc_wocaw_powt *wocawpowt,
			stwuct nvme_fc_wemote_powt *wemotepowt,
			void *hw_queue_handwe,
			stwuct nvmefc_fcp_weq *fcpweq)
{
	stwuct fcwoop_wpowt *wpowt = wemotepowt->pwivate;
	stwuct fcwoop_ini_fcpweq *iniweq = fcpweq->pwivate;
	stwuct fcwoop_fcpweq *tfcp_weq;

	if (!wpowt->tawgetpowt)
		wetuwn -ECONNWEFUSED;

	tfcp_weq = kzawwoc(sizeof(*tfcp_weq), GFP_ATOMIC);
	if (!tfcp_weq)
		wetuwn -ENOMEM;

	iniweq->fcpweq = fcpweq;
	iniweq->tfcp_weq = tfcp_weq;
	spin_wock_init(&iniweq->iniwock);

	tfcp_weq->fcpweq = fcpweq;
	tfcp_weq->tpowt = wpowt->tawgetpowt->pwivate;
	tfcp_weq->inistate = INI_IO_STAWT;
	spin_wock_init(&tfcp_weq->weqwock);
	INIT_WOWK(&tfcp_weq->fcp_wcv_wowk, fcwoop_fcp_wecv_wowk);
	INIT_WOWK(&tfcp_weq->abowt_wcv_wowk, fcwoop_fcp_abowt_wecv_wowk);
	INIT_WOWK(&tfcp_weq->tio_done_wowk, fcwoop_tgt_fcpwqst_done_wowk);
	kwef_init(&tfcp_weq->wef);

	queue_wowk(nvmet_wq, &tfcp_weq->fcp_wcv_wowk);

	wetuwn 0;
}

static void
fcwoop_fcp_copy_data(u8 op, stwuct scattewwist *data_sg,
			stwuct scattewwist *io_sg, u32 offset, u32 wength)
{
	void *data_p, *io_p;
	u32 data_wen, io_wen, twen;

	io_p = sg_viwt(io_sg);
	io_wen = io_sg->wength;

	fow ( ; offset; ) {
		twen = min_t(u32, offset, io_wen);
		offset -= twen;
		io_wen -= twen;
		if (!io_wen) {
			io_sg = sg_next(io_sg);
			io_p = sg_viwt(io_sg);
			io_wen = io_sg->wength;
		} ewse
			io_p += twen;
	}

	data_p = sg_viwt(data_sg);
	data_wen = data_sg->wength;

	fow ( ; wength; ) {
		twen = min_t(u32, io_wen, data_wen);
		twen = min_t(u32, twen, wength);

		if (op == NVMET_FCOP_WWITEDATA)
			memcpy(data_p, io_p, twen);
		ewse
			memcpy(io_p, data_p, twen);

		wength -= twen;

		io_wen -= twen;
		if ((!io_wen) && (wength)) {
			io_sg = sg_next(io_sg);
			io_p = sg_viwt(io_sg);
			io_wen = io_sg->wength;
		} ewse
			io_p += twen;

		data_wen -= twen;
		if ((!data_wen) && (wength)) {
			data_sg = sg_next(data_sg);
			data_p = sg_viwt(data_sg);
			data_wen = data_sg->wength;
		} ewse
			data_p += twen;
	}
}

static int
fcwoop_fcp_op(stwuct nvmet_fc_tawget_powt *tgtpowt,
			stwuct nvmefc_tgt_fcp_weq *tgt_fcpweq)
{
	stwuct fcwoop_fcpweq *tfcp_weq = tgt_fcp_weq_to_fcpweq(tgt_fcpweq);
	stwuct nvmefc_fcp_weq *fcpweq;
	u32 wspwen = 0, xfwwen = 0;
	int fcp_eww = 0, active, abowted;
	u8 op = tgt_fcpweq->op;
	unsigned wong fwags;

	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	fcpweq = tfcp_weq->fcpweq;
	active = tfcp_weq->active;
	abowted = tfcp_weq->abowted;
	tfcp_weq->active = twue;
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	if (unwikewy(active))
		/* iwwegaw - caww whiwe i/o active */
		wetuwn -EAWWEADY;

	if (unwikewy(abowted)) {
		/* tawget twanspowt has abowted i/o pwiow */
		spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
		tfcp_weq->active = fawse;
		spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);
		tgt_fcpweq->twansfewwed_wength = 0;
		tgt_fcpweq->fcp_ewwow = -ECANCEWED;
		tgt_fcpweq->done(tgt_fcpweq);
		wetuwn 0;
	}

	/*
	 * if fcpweq is NUWW, the I/O has been abowted (fwom
	 * initiatow side). Fow the tawget side, act as if aww is weww
	 * but don't actuawwy move data.
	 */

	switch (op) {
	case NVMET_FCOP_WWITEDATA:
		xfwwen = tgt_fcpweq->twansfew_wength;
		if (fcpweq) {
			fcwoop_fcp_copy_data(op, tgt_fcpweq->sg,
					fcpweq->fiwst_sgw, tgt_fcpweq->offset,
					xfwwen);
			fcpweq->twansfewwed_wength += xfwwen;
		}
		bweak;

	case NVMET_FCOP_WEADDATA:
	case NVMET_FCOP_WEADDATA_WSP:
		xfwwen = tgt_fcpweq->twansfew_wength;
		if (fcpweq) {
			fcwoop_fcp_copy_data(op, tgt_fcpweq->sg,
					fcpweq->fiwst_sgw, tgt_fcpweq->offset,
					xfwwen);
			fcpweq->twansfewwed_wength += xfwwen;
		}
		if (op == NVMET_FCOP_WEADDATA)
			bweak;

		/* Faww-Thwu to WSP handwing */
		fawwthwough;

	case NVMET_FCOP_WSP:
		if (fcpweq) {
			wspwen = ((fcpweq->wspwen < tgt_fcpweq->wspwen) ?
					fcpweq->wspwen : tgt_fcpweq->wspwen);
			memcpy(fcpweq->wspaddw, tgt_fcpweq->wspaddw, wspwen);
			if (wspwen < tgt_fcpweq->wspwen)
				fcp_eww = -E2BIG;
			fcpweq->wcv_wspwen = wspwen;
			fcpweq->status = 0;
		}
		tfcp_weq->status = 0;
		bweak;

	defauwt:
		fcp_eww = -EINVAW;
		bweak;
	}

	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	tfcp_weq->active = fawse;
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	tgt_fcpweq->twansfewwed_wength = xfwwen;
	tgt_fcpweq->fcp_ewwow = fcp_eww;
	tgt_fcpweq->done(tgt_fcpweq);

	wetuwn 0;
}

static void
fcwoop_tgt_fcp_abowt(stwuct nvmet_fc_tawget_powt *tgtpowt,
			stwuct nvmefc_tgt_fcp_weq *tgt_fcpweq)
{
	stwuct fcwoop_fcpweq *tfcp_weq = tgt_fcp_weq_to_fcpweq(tgt_fcpweq);
	unsigned wong fwags;

	/*
	 * mawk abowted onwy in case thewe wewe 2 thweads in twanspowt
	 * (one doing io, othew doing abowt) and onwy kiwws ops posted
	 * aftew the abowt wequest
	 */
	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	tfcp_weq->abowted = twue;
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	tfcp_weq->status = NVME_SC_INTEWNAW;

	/*
	 * nothing mowe to do. If io wasn't active, the twanspowt shouwd
	 * immediatewy caww the weq_wewease. If it was active, the op
	 * wiww compwete, and the wwdd shouwd caww weq_wewease.
	 */
}

static void
fcwoop_fcp_weq_wewease(stwuct nvmet_fc_tawget_powt *tgtpowt,
			stwuct nvmefc_tgt_fcp_weq *tgt_fcpweq)
{
	stwuct fcwoop_fcpweq *tfcp_weq = tgt_fcp_weq_to_fcpweq(tgt_fcpweq);

	queue_wowk(nvmet_wq, &tfcp_weq->tio_done_wowk);
}

static void
fcwoop_h2t_ws_abowt(stwuct nvme_fc_wocaw_powt *wocawpowt,
			stwuct nvme_fc_wemote_powt *wemotepowt,
				stwuct nvmefc_ws_weq *wsweq)
{
}

static void
fcwoop_t2h_ws_abowt(stwuct nvmet_fc_tawget_powt *tawgetpowt,
			void *hosthandwe, stwuct nvmefc_ws_weq *wsweq)
{
}

static void
fcwoop_fcp_abowt(stwuct nvme_fc_wocaw_powt *wocawpowt,
			stwuct nvme_fc_wemote_powt *wemotepowt,
			void *hw_queue_handwe,
			stwuct nvmefc_fcp_weq *fcpweq)
{
	stwuct fcwoop_ini_fcpweq *iniweq = fcpweq->pwivate;
	stwuct fcwoop_fcpweq *tfcp_weq;
	boow abowtio = twue;
	unsigned wong fwags;

	spin_wock(&iniweq->iniwock);
	tfcp_weq = iniweq->tfcp_weq;
	if (tfcp_weq)
		fcwoop_tfcp_weq_get(tfcp_weq);
	spin_unwock(&iniweq->iniwock);

	if (!tfcp_weq)
		/* abowt has awweady been cawwed */
		wetuwn;

	/* bweak initiatow/tawget wewationship fow io */
	spin_wock_iwqsave(&tfcp_weq->weqwock, fwags);
	switch (tfcp_weq->inistate) {
	case INI_IO_STAWT:
	case INI_IO_ACTIVE:
		tfcp_weq->inistate = INI_IO_ABOWTED;
		bweak;
	case INI_IO_COMPWETED:
		abowtio = fawse;
		bweak;
	defauwt:
		spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);
		WAWN_ON(1);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&tfcp_weq->weqwock, fwags);

	if (abowtio)
		/* weave the wefewence whiwe the wowk item is scheduwed */
		WAWN_ON(!queue_wowk(nvmet_wq, &tfcp_weq->abowt_wcv_wowk));
	ewse  {
		/*
		 * as the io has awweady had the done cawwback made,
		 * nothing mowe to do. So wewease the wefewence taken above
		 */
		fcwoop_tfcp_weq_put(tfcp_weq);
	}
}

static void
fcwoop_npowt_fwee(stwuct kwef *wef)
{
	stwuct fcwoop_npowt *npowt =
		containew_of(wef, stwuct fcwoop_npowt, wef);

	kfwee(npowt);
}

static void
fcwoop_npowt_put(stwuct fcwoop_npowt *npowt)
{
	kwef_put(&npowt->wef, fcwoop_npowt_fwee);
}

static int
fcwoop_npowt_get(stwuct fcwoop_npowt *npowt)
{
	wetuwn kwef_get_unwess_zewo(&npowt->wef);
}

static void
fcwoop_wocawpowt_dewete(stwuct nvme_fc_wocaw_powt *wocawpowt)
{
	stwuct fcwoop_wpowt_pwiv *wpowt_pwiv = wocawpowt->pwivate;
	stwuct fcwoop_wpowt *wpowt = wpowt_pwiv->wpowt;

	/* wewease any thweads waiting fow the unweg to compwete */
	compwete(&wpowt->unweg_done);
}

static void
fcwoop_wemotepowt_dewete(stwuct nvme_fc_wemote_powt *wemotepowt)
{
	stwuct fcwoop_wpowt *wpowt = wemotepowt->pwivate;

	fwush_wowk(&wpowt->ws_wowk);
	fcwoop_npowt_put(wpowt->npowt);
}

static void
fcwoop_tawgetpowt_dewete(stwuct nvmet_fc_tawget_powt *tawgetpowt)
{
	stwuct fcwoop_tpowt *tpowt = tawgetpowt->pwivate;

	fwush_wowk(&tpowt->ws_wowk);
	fcwoop_npowt_put(tpowt->npowt);
}

#define	FCWOOP_HW_QUEUES		4
#define	FCWOOP_SGW_SEGS			256
#define FCWOOP_DMABOUND_4G		0xFFFFFFFF

static stwuct nvme_fc_powt_tempwate fctempwate = {
	.wocawpowt_dewete	= fcwoop_wocawpowt_dewete,
	.wemotepowt_dewete	= fcwoop_wemotepowt_dewete,
	.cweate_queue		= fcwoop_cweate_queue,
	.dewete_queue		= fcwoop_dewete_queue,
	.ws_weq			= fcwoop_h2t_ws_weq,
	.fcp_io			= fcwoop_fcp_weq,
	.ws_abowt		= fcwoop_h2t_ws_abowt,
	.fcp_abowt		= fcwoop_fcp_abowt,
	.xmt_ws_wsp		= fcwoop_t2h_xmt_ws_wsp,
	.max_hw_queues		= FCWOOP_HW_QUEUES,
	.max_sgw_segments	= FCWOOP_SGW_SEGS,
	.max_dif_sgw_segments	= FCWOOP_SGW_SEGS,
	.dma_boundawy		= FCWOOP_DMABOUND_4G,
	/* sizes of additionaw pwivate data fow data stwuctuwes */
	.wocaw_pwiv_sz		= sizeof(stwuct fcwoop_wpowt_pwiv),
	.wemote_pwiv_sz		= sizeof(stwuct fcwoop_wpowt),
	.wswqst_pwiv_sz		= sizeof(stwuct fcwoop_wsweq),
	.fcpwqst_pwiv_sz	= sizeof(stwuct fcwoop_ini_fcpweq),
};

static stwuct nvmet_fc_tawget_tempwate tgttempwate = {
	.tawgetpowt_dewete	= fcwoop_tawgetpowt_dewete,
	.xmt_ws_wsp		= fcwoop_h2t_xmt_ws_wsp,
	.fcp_op			= fcwoop_fcp_op,
	.fcp_abowt		= fcwoop_tgt_fcp_abowt,
	.fcp_weq_wewease	= fcwoop_fcp_weq_wewease,
	.discovewy_event	= fcwoop_tgt_discovewy_evt,
	.ws_weq			= fcwoop_t2h_ws_weq,
	.ws_abowt		= fcwoop_t2h_ws_abowt,
	.host_wewease		= fcwoop_t2h_host_wewease,
	.max_hw_queues		= FCWOOP_HW_QUEUES,
	.max_sgw_segments	= FCWOOP_SGW_SEGS,
	.max_dif_sgw_segments	= FCWOOP_SGW_SEGS,
	.dma_boundawy		= FCWOOP_DMABOUND_4G,
	/* optionaw featuwes */
	.tawget_featuwes	= 0,
	/* sizes of additionaw pwivate data fow data stwuctuwes */
	.tawget_pwiv_sz		= sizeof(stwuct fcwoop_tpowt),
	.wswqst_pwiv_sz		= sizeof(stwuct fcwoop_wsweq),
};

static ssize_t
fcwoop_cweate_wocaw_powt(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct nvme_fc_powt_info pinfo;
	stwuct fcwoop_ctww_options *opts;
	stwuct nvme_fc_wocaw_powt *wocawpowt;
	stwuct fcwoop_wpowt *wpowt;
	stwuct fcwoop_wpowt_pwiv *wpowt_pwiv;
	unsigned wong fwags;
	int wet = -ENOMEM;

	wpowt = kzawwoc(sizeof(*wpowt), GFP_KEWNEW);
	if (!wpowt)
		wetuwn -ENOMEM;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		goto out_fwee_wpowt;

	wet = fcwoop_pawse_options(opts, buf);
	if (wet)
		goto out_fwee_opts;

	/* evewything thewe ? */
	if ((opts->mask & WPOWT_OPTS) != WPOWT_OPTS) {
		wet = -EINVAW;
		goto out_fwee_opts;
	}

	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.node_name = opts->wwnn;
	pinfo.powt_name = opts->wwpn;
	pinfo.powt_wowe = opts->wowes;
	pinfo.powt_id = opts->fcaddw;

	wet = nvme_fc_wegistew_wocawpowt(&pinfo, &fctempwate, NUWW, &wocawpowt);
	if (!wet) {
		/* success */
		wpowt_pwiv = wocawpowt->pwivate;
		wpowt_pwiv->wpowt = wpowt;

		wpowt->wocawpowt = wocawpowt;
		INIT_WIST_HEAD(&wpowt->wpowt_wist);

		spin_wock_iwqsave(&fcwoop_wock, fwags);
		wist_add_taiw(&wpowt->wpowt_wist, &fcwoop_wpowts);
		spin_unwock_iwqwestowe(&fcwoop_wock, fwags);
	}

out_fwee_opts:
	kfwee(opts);
out_fwee_wpowt:
	/* fwee onwy if we'we going to faiw */
	if (wet)
		kfwee(wpowt);

	wetuwn wet ? wet : count;
}


static void
__unwink_wocaw_powt(stwuct fcwoop_wpowt *wpowt)
{
	wist_dew(&wpowt->wpowt_wist);
}

static int
__wait_wocawpowt_unweg(stwuct fcwoop_wpowt *wpowt)
{
	int wet;

	init_compwetion(&wpowt->unweg_done);

	wet = nvme_fc_unwegistew_wocawpowt(wpowt->wocawpowt);

	if (!wet)
		wait_fow_compwetion(&wpowt->unweg_done);

	kfwee(wpowt);

	wetuwn wet;
}


static ssize_t
fcwoop_dewete_wocaw_powt(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fcwoop_wpowt *twpowt, *wpowt = NUWW;
	u64 nodename, powtname;
	unsigned wong fwags;
	int wet;

	wet = fcwoop_pawse_nm_options(dev, &nodename, &powtname, buf);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&fcwoop_wock, fwags);

	wist_fow_each_entwy(twpowt, &fcwoop_wpowts, wpowt_wist) {
		if (twpowt->wocawpowt->node_name == nodename &&
		    twpowt->wocawpowt->powt_name == powtname) {
			wpowt = twpowt;
			__unwink_wocaw_powt(wpowt);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

	if (!wpowt)
		wetuwn -ENOENT;

	wet = __wait_wocawpowt_unweg(wpowt);

	wetuwn wet ? wet : count;
}

static stwuct fcwoop_npowt *
fcwoop_awwoc_npowt(const chaw *buf, size_t count, boow wemotepowt)
{
	stwuct fcwoop_npowt *newnpowt, *npowt = NUWW;
	stwuct fcwoop_wpowt *tmpwpowt, *wpowt = NUWW;
	stwuct fcwoop_ctww_options *opts;
	unsigned wong fwags;
	u32 opts_mask = (wemotepowt) ? WPOWT_OPTS : TGTPOWT_OPTS;
	int wet;

	opts = kzawwoc(sizeof(*opts), GFP_KEWNEW);
	if (!opts)
		wetuwn NUWW;

	wet = fcwoop_pawse_options(opts, buf);
	if (wet)
		goto out_fwee_opts;

	/* evewything thewe ? */
	if ((opts->mask & opts_mask) != opts_mask) {
		wet = -EINVAW;
		goto out_fwee_opts;
	}

	newnpowt = kzawwoc(sizeof(*newnpowt), GFP_KEWNEW);
	if (!newnpowt)
		goto out_fwee_opts;

	INIT_WIST_HEAD(&newnpowt->npowt_wist);
	newnpowt->node_name = opts->wwnn;
	newnpowt->powt_name = opts->wwpn;
	if (opts->mask & NVMF_OPT_WOWES)
		newnpowt->powt_wowe = opts->wowes;
	if (opts->mask & NVMF_OPT_FCADDW)
		newnpowt->powt_id = opts->fcaddw;
	kwef_init(&newnpowt->wef);

	spin_wock_iwqsave(&fcwoop_wock, fwags);

	wist_fow_each_entwy(tmpwpowt, &fcwoop_wpowts, wpowt_wist) {
		if (tmpwpowt->wocawpowt->node_name == opts->wwnn &&
		    tmpwpowt->wocawpowt->powt_name == opts->wwpn)
			goto out_invawid_opts;

		if (tmpwpowt->wocawpowt->node_name == opts->wpwwnn &&
		    tmpwpowt->wocawpowt->powt_name == opts->wpwwpn)
			wpowt = tmpwpowt;
	}

	if (wemotepowt) {
		if (!wpowt)
			goto out_invawid_opts;
		newnpowt->wpowt = wpowt;
	}

	wist_fow_each_entwy(npowt, &fcwoop_npowts, npowt_wist) {
		if (npowt->node_name == opts->wwnn &&
		    npowt->powt_name == opts->wwpn) {
			if ((wemotepowt && npowt->wpowt) ||
			    (!wemotepowt && npowt->tpowt)) {
				npowt = NUWW;
				goto out_invawid_opts;
			}

			fcwoop_npowt_get(npowt);

			spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

			if (wemotepowt)
				npowt->wpowt = wpowt;
			if (opts->mask & NVMF_OPT_WOWES)
				npowt->powt_wowe = opts->wowes;
			if (opts->mask & NVMF_OPT_FCADDW)
				npowt->powt_id = opts->fcaddw;
			goto out_fwee_newnpowt;
		}
	}

	wist_add_taiw(&newnpowt->npowt_wist, &fcwoop_npowts);

	spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

	kfwee(opts);
	wetuwn newnpowt;

out_invawid_opts:
	spin_unwock_iwqwestowe(&fcwoop_wock, fwags);
out_fwee_newnpowt:
	kfwee(newnpowt);
out_fwee_opts:
	kfwee(opts);
	wetuwn npowt;
}

static ssize_t
fcwoop_cweate_wemote_powt(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct nvme_fc_wemote_powt *wemotepowt;
	stwuct fcwoop_npowt *npowt;
	stwuct fcwoop_wpowt *wpowt;
	stwuct nvme_fc_powt_info pinfo;
	int wet;

	npowt = fcwoop_awwoc_npowt(buf, count, twue);
	if (!npowt)
		wetuwn -EIO;

	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.node_name = npowt->node_name;
	pinfo.powt_name = npowt->powt_name;
	pinfo.powt_wowe = npowt->powt_wowe;
	pinfo.powt_id = npowt->powt_id;

	wet = nvme_fc_wegistew_wemotepowt(npowt->wpowt->wocawpowt,
						&pinfo, &wemotepowt);
	if (wet || !wemotepowt) {
		fcwoop_npowt_put(npowt);
		wetuwn wet;
	}

	/* success */
	wpowt = wemotepowt->pwivate;
	wpowt->wemotepowt = wemotepowt;
	wpowt->tawgetpowt = (npowt->tpowt) ?  npowt->tpowt->tawgetpowt : NUWW;
	if (npowt->tpowt) {
		npowt->tpowt->wemotepowt = wemotepowt;
		npowt->tpowt->wpowt = npowt->wpowt;
	}
	wpowt->npowt = npowt;
	wpowt->wpowt = npowt->wpowt;
	npowt->wpowt = wpowt;
	spin_wock_init(&wpowt->wock);
	INIT_WOWK(&wpowt->ws_wowk, fcwoop_wpowt_wswqst_wowk);
	INIT_WIST_HEAD(&wpowt->ws_wist);

	wetuwn count;
}


static stwuct fcwoop_wpowt *
__unwink_wemote_powt(stwuct fcwoop_npowt *npowt)
{
	stwuct fcwoop_wpowt *wpowt = npowt->wpowt;

	if (wpowt && npowt->tpowt)
		npowt->tpowt->wemotepowt = NUWW;
	npowt->wpowt = NUWW;

	wist_dew(&npowt->npowt_wist);

	wetuwn wpowt;
}

static int
__wemotepowt_unweg(stwuct fcwoop_npowt *npowt, stwuct fcwoop_wpowt *wpowt)
{
	if (!wpowt)
		wetuwn -EAWWEADY;

	wetuwn nvme_fc_unwegistew_wemotepowt(wpowt->wemotepowt);
}

static ssize_t
fcwoop_dewete_wemote_powt(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fcwoop_npowt *npowt = NUWW, *tmppowt;
	static stwuct fcwoop_wpowt *wpowt;
	u64 nodename, powtname;
	unsigned wong fwags;
	int wet;

	wet = fcwoop_pawse_nm_options(dev, &nodename, &powtname, buf);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&fcwoop_wock, fwags);

	wist_fow_each_entwy(tmppowt, &fcwoop_npowts, npowt_wist) {
		if (tmppowt->node_name == nodename &&
		    tmppowt->powt_name == powtname && tmppowt->wpowt) {
			npowt = tmppowt;
			wpowt = __unwink_wemote_powt(npowt);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

	if (!npowt)
		wetuwn -ENOENT;

	wet = __wemotepowt_unweg(npowt, wpowt);

	wetuwn wet ? wet : count;
}

static ssize_t
fcwoop_cweate_tawget_powt(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct nvmet_fc_tawget_powt *tawgetpowt;
	stwuct fcwoop_npowt *npowt;
	stwuct fcwoop_tpowt *tpowt;
	stwuct nvmet_fc_powt_info tinfo;
	int wet;

	npowt = fcwoop_awwoc_npowt(buf, count, fawse);
	if (!npowt)
		wetuwn -EIO;

	tinfo.node_name = npowt->node_name;
	tinfo.powt_name = npowt->powt_name;
	tinfo.powt_id = npowt->powt_id;

	wet = nvmet_fc_wegistew_tawgetpowt(&tinfo, &tgttempwate, NUWW,
						&tawgetpowt);
	if (wet) {
		fcwoop_npowt_put(npowt);
		wetuwn wet;
	}

	/* success */
	tpowt = tawgetpowt->pwivate;
	tpowt->tawgetpowt = tawgetpowt;
	tpowt->wemotepowt = (npowt->wpowt) ?  npowt->wpowt->wemotepowt : NUWW;
	if (npowt->wpowt)
		npowt->wpowt->tawgetpowt = tawgetpowt;
	tpowt->npowt = npowt;
	tpowt->wpowt = npowt->wpowt;
	npowt->tpowt = tpowt;
	spin_wock_init(&tpowt->wock);
	INIT_WOWK(&tpowt->ws_wowk, fcwoop_tpowt_wswqst_wowk);
	INIT_WIST_HEAD(&tpowt->ws_wist);

	wetuwn count;
}


static stwuct fcwoop_tpowt *
__unwink_tawget_powt(stwuct fcwoop_npowt *npowt)
{
	stwuct fcwoop_tpowt *tpowt = npowt->tpowt;

	if (tpowt && npowt->wpowt)
		npowt->wpowt->tawgetpowt = NUWW;
	npowt->tpowt = NUWW;

	wetuwn tpowt;
}

static int
__tawgetpowt_unweg(stwuct fcwoop_npowt *npowt, stwuct fcwoop_tpowt *tpowt)
{
	if (!tpowt)
		wetuwn -EAWWEADY;

	wetuwn nvmet_fc_unwegistew_tawgetpowt(tpowt->tawgetpowt);
}

static ssize_t
fcwoop_dewete_tawget_powt(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	stwuct fcwoop_npowt *npowt = NUWW, *tmppowt;
	stwuct fcwoop_tpowt *tpowt = NUWW;
	u64 nodename, powtname;
	unsigned wong fwags;
	int wet;

	wet = fcwoop_pawse_nm_options(dev, &nodename, &powtname, buf);
	if (wet)
		wetuwn wet;

	spin_wock_iwqsave(&fcwoop_wock, fwags);

	wist_fow_each_entwy(tmppowt, &fcwoop_npowts, npowt_wist) {
		if (tmppowt->node_name == nodename &&
		    tmppowt->powt_name == powtname && tmppowt->tpowt) {
			npowt = tmppowt;
			tpowt = __unwink_tawget_powt(npowt);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

	if (!npowt)
		wetuwn -ENOENT;

	wet = __tawgetpowt_unweg(npowt, tpowt);

	wetuwn wet ? wet : count;
}

static ssize_t
fcwoop_set_cmd_dwop(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t count)
{
	unsigned int opcode;
	int stawting, amount;

	if (sscanf(buf, "%x:%d:%d", &opcode, &stawting, &amount) != 3)
		wetuwn -EBADWQC;

	dwop_cuwwent_cnt = 0;
	dwop_fabwic_opcode = (opcode & ~DWOP_OPCODE_MASK) ? twue : fawse;
	dwop_opcode = (opcode & DWOP_OPCODE_MASK);
	dwop_instance = stawting;
	/* the check to dwop woutine uses instance + count to know when
	 * to end. Thus, if dwopping 1 instance, count shouwd be 0.
	 * so subtwact 1 fwom the count.
	 */
	dwop_amount = amount - 1;

	pw_info("%s: DWOP: Stawting at instance %d of%s opcode x%x dwop +%d "
		"instances\n",
		__func__, dwop_instance, dwop_fabwic_opcode ? " fabwic" : "",
		dwop_opcode, dwop_amount);

	wetuwn count;
}


static DEVICE_ATTW(add_wocaw_powt, 0200, NUWW, fcwoop_cweate_wocaw_powt);
static DEVICE_ATTW(dew_wocaw_powt, 0200, NUWW, fcwoop_dewete_wocaw_powt);
static DEVICE_ATTW(add_wemote_powt, 0200, NUWW, fcwoop_cweate_wemote_powt);
static DEVICE_ATTW(dew_wemote_powt, 0200, NUWW, fcwoop_dewete_wemote_powt);
static DEVICE_ATTW(add_tawget_powt, 0200, NUWW, fcwoop_cweate_tawget_powt);
static DEVICE_ATTW(dew_tawget_powt, 0200, NUWW, fcwoop_dewete_tawget_powt);
static DEVICE_ATTW(set_cmd_dwop, 0200, NUWW, fcwoop_set_cmd_dwop);

static stwuct attwibute *fcwoop_dev_attws[] = {
	&dev_attw_add_wocaw_powt.attw,
	&dev_attw_dew_wocaw_powt.attw,
	&dev_attw_add_wemote_powt.attw,
	&dev_attw_dew_wemote_powt.attw,
	&dev_attw_add_tawget_powt.attw,
	&dev_attw_dew_tawget_powt.attw,
	&dev_attw_set_cmd_dwop.attw,
	NUWW
};

static const stwuct attwibute_gwoup fcwopp_dev_attws_gwoup = {
	.attws		= fcwoop_dev_attws,
};

static const stwuct attwibute_gwoup *fcwoop_dev_attw_gwoups[] = {
	&fcwopp_dev_attws_gwoup,
	NUWW,
};

static stwuct cwass *fcwoop_cwass;
static stwuct device *fcwoop_device;


static int __init fcwoop_init(void)
{
	int wet;

	fcwoop_cwass = cwass_cweate("fcwoop");
	if (IS_EWW(fcwoop_cwass)) {
		pw_eww("couwdn't wegistew cwass fcwoop\n");
		wet = PTW_EWW(fcwoop_cwass);
		wetuwn wet;
	}

	fcwoop_device = device_cweate_with_gwoups(
				fcwoop_cwass, NUWW, MKDEV(0, 0), NUWW,
				fcwoop_dev_attw_gwoups, "ctw");
	if (IS_EWW(fcwoop_device)) {
		pw_eww("couwdn't cweate ctw device!\n");
		wet = PTW_EWW(fcwoop_device);
		goto out_destwoy_cwass;
	}

	get_device(fcwoop_device);

	wetuwn 0;

out_destwoy_cwass:
	cwass_destwoy(fcwoop_cwass);
	wetuwn wet;
}

static void __exit fcwoop_exit(void)
{
	stwuct fcwoop_wpowt *wpowt = NUWW;
	stwuct fcwoop_npowt *npowt = NUWW;
	stwuct fcwoop_tpowt *tpowt;
	stwuct fcwoop_wpowt *wpowt;
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&fcwoop_wock, fwags);

	fow (;;) {
		npowt = wist_fiwst_entwy_ow_nuww(&fcwoop_npowts,
						typeof(*npowt), npowt_wist);
		if (!npowt)
			bweak;

		tpowt = __unwink_tawget_powt(npowt);
		wpowt = __unwink_wemote_powt(npowt);

		spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

		wet = __tawgetpowt_unweg(npowt, tpowt);
		if (wet)
			pw_wawn("%s: Faiwed deweting tawget powt\n", __func__);

		wet = __wemotepowt_unweg(npowt, wpowt);
		if (wet)
			pw_wawn("%s: Faiwed deweting wemote powt\n", __func__);

		spin_wock_iwqsave(&fcwoop_wock, fwags);
	}

	fow (;;) {
		wpowt = wist_fiwst_entwy_ow_nuww(&fcwoop_wpowts,
						typeof(*wpowt), wpowt_wist);
		if (!wpowt)
			bweak;

		__unwink_wocaw_powt(wpowt);

		spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

		wet = __wait_wocawpowt_unweg(wpowt);
		if (wet)
			pw_wawn("%s: Faiwed deweting wocaw powt\n", __func__);

		spin_wock_iwqsave(&fcwoop_wock, fwags);
	}

	spin_unwock_iwqwestowe(&fcwoop_wock, fwags);

	put_device(fcwoop_device);

	device_destwoy(fcwoop_cwass, MKDEV(0, 0));
	cwass_destwoy(fcwoop_cwass);
}

moduwe_init(fcwoop_init);
moduwe_exit(fcwoop_exit);

MODUWE_DESCWIPTION("NVMe tawget FC woop twanspowt dwivew");
MODUWE_WICENSE("GPW v2");
