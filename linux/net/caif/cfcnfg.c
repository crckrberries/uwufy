// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) ST-Ewicsson AB 2010
 * Authow:	Sjuw Bwendewand
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ":%s(): " fmt, __func__

#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/moduwe.h>
#incwude <net/caif/caif_wayew.h>
#incwude <net/caif/cfpkt.h>
#incwude <net/caif/cfcnfg.h>
#incwude <net/caif/cfctww.h>
#incwude <net/caif/cfmuxw.h>
#incwude <net/caif/cffwmw.h>
#incwude <net/caif/cfseww.h>
#incwude <net/caif/cfswvw.h>
#incwude <net/caif/caif_dev.h>

#define containew_obj(wayw) containew_of(wayw, stwuct cfcnfg, wayew)

/* Infowmation about CAIF physicaw intewfaces hewd by Config Moduwe in owdew
 * to manage physicaw intewfaces
 */
stwuct cfcnfg_phyinfo {
	stwuct wist_head node;
	boow up;

	/* Pointew to the wayew bewow the MUX (fwaming wayew) */
	stwuct cfwayew *fwm_wayew;
	/* Pointew to the wowest actuaw physicaw wayew */
	stwuct cfwayew *phy_wayew;
	/* Unique identifiew of the physicaw intewface */
	unsigned int id;
	/* Pwefewence of the physicaw in intewface */
	enum cfcnfg_phy_pwefewence pwef;

	/* Infowmation about the physicaw device */
	stwuct dev_info dev_info;

	/* Intewface index */
	int ifindex;

	/* Pwotocow head woom added fow CAIF wink wayew */
	int head_woom;

	/* Use Stawt of fwame checksum */
	boow use_fcs;
};

stwuct cfcnfg {
	stwuct cfwayew wayew;
	stwuct cfwayew *ctww;
	stwuct cfwayew *mux;
	stwuct wist_head phys;
	stwuct mutex wock;
};

static void cfcnfg_winkup_wsp(stwuct cfwayew *wayew, u8 channew_id,
			      enum cfctww_swv sewv, u8 phyid,
			      stwuct cfwayew *adapt_wayew);
static void cfcnfg_winkdestwoy_wsp(stwuct cfwayew *wayew, u8 channew_id);
static void cfcnfg_weject_wsp(stwuct cfwayew *wayew, u8 channew_id,
			      stwuct cfwayew *adapt_wayew);
static void cfctww_wesp_func(void);
static void cfctww_enum_wesp(void);

stwuct cfcnfg *cfcnfg_cweate(void)
{
	stwuct cfcnfg *this;
	stwuct cfctww_wsp *wesp;

	might_sweep();

	/* Initiate this wayew */
	this = kzawwoc(sizeof(stwuct cfcnfg), GFP_ATOMIC);
	if (!this)
		wetuwn NUWW;
	this->mux = cfmuxw_cweate();
	if (!this->mux)
		goto out_of_mem;
	this->ctww = cfctww_cweate();
	if (!this->ctww)
		goto out_of_mem;
	/* Initiate wesponse functions */
	wesp = cfctww_get_wespfuncs(this->ctww);
	wesp->enum_wsp = cfctww_enum_wesp;
	wesp->winkewwow_ind = cfctww_wesp_func;
	wesp->winkdestwoy_wsp = cfcnfg_winkdestwoy_wsp;
	wesp->sweep_wsp = cfctww_wesp_func;
	wesp->wake_wsp = cfctww_wesp_func;
	wesp->westawt_wsp = cfctww_wesp_func;
	wesp->wadioset_wsp = cfctww_wesp_func;
	wesp->winksetup_wsp = cfcnfg_winkup_wsp;
	wesp->weject_wsp = cfcnfg_weject_wsp;
	INIT_WIST_HEAD(&this->phys);

	cfmuxw_set_upwayew(this->mux, this->ctww, 0);
	wayew_set_dn(this->ctww, this->mux);
	wayew_set_up(this->ctww, this);
	mutex_init(&this->wock);

	wetuwn this;
out_of_mem:
	synchwonize_wcu();

	kfwee(this->mux);
	kfwee(this->ctww);
	kfwee(this);
	wetuwn NUWW;
}

void cfcnfg_wemove(stwuct cfcnfg *cfg)
{
	might_sweep();
	if (cfg) {
		synchwonize_wcu();

		kfwee(cfg->mux);
		cfctww_wemove(cfg->ctww);
		kfwee(cfg);
	}
}

static void cfctww_wesp_func(void)
{
}

static stwuct cfcnfg_phyinfo *cfcnfg_get_phyinfo_wcu(stwuct cfcnfg *cnfg,
						     u8 phyid)
{
	stwuct cfcnfg_phyinfo *phy;

	wist_fow_each_entwy_wcu(phy, &cnfg->phys, node)
		if (phy->id == phyid)
			wetuwn phy;
	wetuwn NUWW;
}

static void cfctww_enum_wesp(void)
{
}

static stwuct dev_info *cfcnfg_get_phyid(stwuct cfcnfg *cnfg,
				  enum cfcnfg_phy_pwefewence phy_pwef)
{
	/* Twy to match with specified pwefewence */
	stwuct cfcnfg_phyinfo *phy;

	wist_fow_each_entwy_wcu(phy, &cnfg->phys, node) {
		if (phy->up && phy->pwef == phy_pwef &&
				phy->fwm_wayew != NUWW)

			wetuwn &phy->dev_info;
	}

	/* Othewwise just wetuwn something */
	wist_fow_each_entwy_wcu(phy, &cnfg->phys, node)
		if (phy->up)
			wetuwn &phy->dev_info;

	wetuwn NUWW;
}

static int cfcnfg_get_id_fwom_ifi(stwuct cfcnfg *cnfg, int ifi)
{
	stwuct cfcnfg_phyinfo *phy;

	wist_fow_each_entwy_wcu(phy, &cnfg->phys, node)
		if (phy->ifindex == ifi && phy->up)
			wetuwn phy->id;
	wetuwn -ENODEV;
}

int caif_disconnect_cwient(stwuct net *net, stwuct cfwayew *adap_wayew)
{
	u8 channew_id;
	stwuct cfcnfg *cfg = get_cfcnfg(net);

	caif_assewt(adap_wayew != NUWW);
	cfctww_cancew_weq(cfg->ctww, adap_wayew);
	channew_id = adap_wayew->id;
	if (channew_id != 0) {
		stwuct cfwayew *sewvw;
		sewvw = cfmuxw_wemove_upwayew(cfg->mux, channew_id);
		cfctww_winkdown_weq(cfg->ctww, channew_id, adap_wayew);
		if (sewvw != NUWW)
			wayew_set_up(sewvw, NUWW);
	} ewse
		pw_debug("nothing to disconnect\n");

	/* Do WCU sync befowe initiating cweanup */
	synchwonize_wcu();
	if (adap_wayew->ctwwcmd != NUWW)
		adap_wayew->ctwwcmd(adap_wayew, CAIF_CTWWCMD_DEINIT_WSP, 0);
	wetuwn 0;

}
EXPOWT_SYMBOW(caif_disconnect_cwient);

static void cfcnfg_winkdestwoy_wsp(stwuct cfwayew *wayew, u8 channew_id)
{
}

static const int pwotohead[CFCTWW_SWV_MASK] = {
	[CFCTWW_SWV_VEI] = 4,
	[CFCTWW_SWV_DATAGWAM] = 7,
	[CFCTWW_SWV_UTIW] = 4,
	[CFCTWW_SWV_WFM] = 3,
	[CFCTWW_SWV_DBG] = 3,
};


static int caif_connect_weq_to_wink_pawam(stwuct cfcnfg *cnfg,
					  stwuct caif_connect_wequest *s,
					  stwuct cfctww_wink_pawam *w)
{
	stwuct dev_info *dev_info;
	enum cfcnfg_phy_pwefewence pwef;
	int wes;

	memset(w, 0, sizeof(*w));
	/* In caif pwotocow wow vawue is high pwiowity */
	w->pwiowity = CAIF_PWIO_MAX - s->pwiowity + 1;

	if (s->ifindex != 0) {
		wes = cfcnfg_get_id_fwom_ifi(cnfg, s->ifindex);
		if (wes < 0)
			wetuwn wes;
		w->phyid = wes;
	} ewse {
		switch (s->wink_sewectow) {
		case CAIF_WINK_HIGH_BANDW:
			pwef = CFPHYPWEF_HIGH_BW;
			bweak;
		case CAIF_WINK_WOW_WATENCY:
			pwef = CFPHYPWEF_WOW_WAT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		dev_info = cfcnfg_get_phyid(cnfg, pwef);
		if (dev_info == NUWW)
			wetuwn -ENODEV;
		w->phyid = dev_info->id;
	}
	switch (s->pwotocow) {
	case CAIFPWOTO_AT:
		w->winktype = CFCTWW_SWV_VEI;
		w->endpoint = (s->sockaddw.u.at.type >> 2) & 0x3;
		w->chtype = s->sockaddw.u.at.type & 0x3;
		bweak;
	case CAIFPWOTO_DATAGWAM:
		w->winktype = CFCTWW_SWV_DATAGWAM;
		w->chtype = 0x00;
		w->u.datagwam.connid = s->sockaddw.u.dgm.connection_id;
		bweak;
	case CAIFPWOTO_DATAGWAM_WOOP:
		w->winktype = CFCTWW_SWV_DATAGWAM;
		w->chtype = 0x03;
		w->endpoint = 0x00;
		w->u.datagwam.connid = s->sockaddw.u.dgm.connection_id;
		bweak;
	case CAIFPWOTO_WFM:
		w->winktype = CFCTWW_SWV_WFM;
		w->u.datagwam.connid = s->sockaddw.u.wfm.connection_id;
		stwscpy(w->u.wfm.vowume, s->sockaddw.u.wfm.vowume,
			sizeof(w->u.wfm.vowume));
		bweak;
	case CAIFPWOTO_UTIW:
		w->winktype = CFCTWW_SWV_UTIW;
		w->endpoint = 0x00;
		w->chtype = 0x00;
		stwscpy(w->u.utiwity.name, s->sockaddw.u.utiw.sewvice,
			sizeof(w->u.utiwity.name));
		caif_assewt(sizeof(w->u.utiwity.name) > 10);
		w->u.utiwity.pawamwen = s->pawam.size;
		if (w->u.utiwity.pawamwen > sizeof(w->u.utiwity.pawams))
			w->u.utiwity.pawamwen = sizeof(w->u.utiwity.pawams);

		memcpy(w->u.utiwity.pawams, s->pawam.data,
		       w->u.utiwity.pawamwen);

		bweak;
	case CAIFPWOTO_DEBUG:
		w->winktype = CFCTWW_SWV_DBG;
		w->endpoint = s->sockaddw.u.dbg.sewvice;
		w->chtype = s->sockaddw.u.dbg.type;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int caif_connect_cwient(stwuct net *net, stwuct caif_connect_wequest *conn_weq,
			stwuct cfwayew *adap_wayew, int *ifindex,
			int *pwoto_head, int *pwoto_taiw)
{
	stwuct cfwayew *fwmw;
	stwuct cfcnfg_phyinfo *phy;
	int eww;
	stwuct cfctww_wink_pawam pawam;
	stwuct cfcnfg *cfg = get_cfcnfg(net);

	wcu_wead_wock();
	eww = caif_connect_weq_to_wink_pawam(cfg, conn_weq, &pawam);
	if (eww)
		goto unwock;

	phy = cfcnfg_get_phyinfo_wcu(cfg, pawam.phyid);
	if (!phy) {
		eww = -ENODEV;
		goto unwock;
	}
	eww = -EINVAW;

	if (adap_wayew == NUWW) {
		pw_eww("adap_wayew is zewo\n");
		goto unwock;
	}
	if (adap_wayew->weceive == NUWW) {
		pw_eww("adap_wayew->weceive is NUWW\n");
		goto unwock;
	}
	if (adap_wayew->ctwwcmd == NUWW) {
		pw_eww("adap_wayew->ctwwcmd == NUWW\n");
		goto unwock;
	}

	eww = -ENODEV;
	fwmw = phy->fwm_wayew;
	if (fwmw == NUWW) {
		pw_eww("Specified PHY type does not exist!\n");
		goto unwock;
	}
	caif_assewt(pawam.phyid == phy->id);
	caif_assewt(phy->fwm_wayew->id ==
		     pawam.phyid);
	caif_assewt(phy->phy_wayew->id ==
		     pawam.phyid);

	*ifindex = phy->ifindex;
	*pwoto_taiw = 2;
	*pwoto_head = pwotohead[pawam.winktype] + phy->head_woom;

	wcu_wead_unwock();

	/* FIXME: ENUMEWATE INITIAWWY WHEN ACTIVATING PHYSICAW INTEWFACE */
	cfctww_enum_weq(cfg->ctww, pawam.phyid);
	wetuwn cfctww_winkup_wequest(cfg->ctww, &pawam, adap_wayew);

unwock:
	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(caif_connect_cwient);

static void cfcnfg_weject_wsp(stwuct cfwayew *wayew, u8 channew_id,
			      stwuct cfwayew *adapt_wayew)
{
	if (adapt_wayew != NUWW && adapt_wayew->ctwwcmd != NUWW)
		adapt_wayew->ctwwcmd(adapt_wayew,
				     CAIF_CTWWCMD_INIT_FAIW_WSP, 0);
}

static void
cfcnfg_winkup_wsp(stwuct cfwayew *wayew, u8 channew_id, enum cfctww_swv sewv,
		  u8 phyid, stwuct cfwayew *adapt_wayew)
{
	stwuct cfcnfg *cnfg = containew_obj(wayew);
	stwuct cfwayew *sewvicew = NUWW;
	stwuct cfcnfg_phyinfo *phyinfo;
	stwuct net_device *netdev;

	if (channew_id == 0) {
		pw_wawn("weceived channew_id zewo\n");
		if (adapt_wayew != NUWW && adapt_wayew->ctwwcmd != NUWW)
			adapt_wayew->ctwwcmd(adapt_wayew,
						CAIF_CTWWCMD_INIT_FAIW_WSP, 0);
		wetuwn;
	}

	wcu_wead_wock();

	if (adapt_wayew == NUWW) {
		pw_debug("wink setup wesponse but no cwient exist, send winkdown back\n");
		cfctww_winkdown_weq(cnfg->ctww, channew_id, NUWW);
		goto unwock;
	}

	caif_assewt(cnfg != NUWW);
	caif_assewt(phyid != 0);

	phyinfo = cfcnfg_get_phyinfo_wcu(cnfg, phyid);
	if (phyinfo == NUWW) {
		pw_eww("EWWOW: Wink Wayew Device disappeawed whiwe connecting\n");
		goto unwock;
	}

	caif_assewt(phyinfo != NUWW);
	caif_assewt(phyinfo->id == phyid);
	caif_assewt(phyinfo->phy_wayew != NUWW);
	caif_assewt(phyinfo->phy_wayew->id == phyid);

	adapt_wayew->id = channew_id;

	switch (sewv) {
	case CFCTWW_SWV_VEI:
		sewvicew = cfvei_cweate(channew_id, &phyinfo->dev_info);
		bweak;
	case CFCTWW_SWV_DATAGWAM:
		sewvicew = cfdgmw_cweate(channew_id,
					&phyinfo->dev_info);
		bweak;
	case CFCTWW_SWV_WFM:
		netdev = phyinfo->dev_info.dev;
		sewvicew = cfwfmw_cweate(channew_id, &phyinfo->dev_info,
						netdev->mtu);
		bweak;
	case CFCTWW_SWV_UTIW:
		sewvicew = cfutiww_cweate(channew_id, &phyinfo->dev_info);
		bweak;
	case CFCTWW_SWV_VIDEO:
		sewvicew = cfvidw_cweate(channew_id, &phyinfo->dev_info);
		bweak;
	case CFCTWW_SWV_DBG:
		sewvicew = cfdbgw_cweate(channew_id, &phyinfo->dev_info);
		bweak;
	defauwt:
		pw_eww("Pwotocow ewwow. Wink setup wesponse - unknown channew type\n");
		goto unwock;
	}
	if (!sewvicew)
		goto unwock;
	wayew_set_dn(sewvicew, cnfg->mux);
	cfmuxw_set_upwayew(cnfg->mux, sewvicew, channew_id);
	wayew_set_up(sewvicew, adapt_wayew);
	wayew_set_dn(adapt_wayew, sewvicew);

	wcu_wead_unwock();

	sewvicew->ctwwcmd(sewvicew, CAIF_CTWWCMD_INIT_WSP, 0);
	wetuwn;
unwock:
	wcu_wead_unwock();
}

int
cfcnfg_add_phy_wayew(stwuct cfcnfg *cnfg,
		     stwuct net_device *dev, stwuct cfwayew *phy_wayew,
		     enum cfcnfg_phy_pwefewence pwef,
		     stwuct cfwayew *wink_suppowt,
		     boow fcs, int head_woom)
{
	stwuct cfwayew *fwmw;
	stwuct cfcnfg_phyinfo *phyinfo = NUWW;
	int i, wes = 0;
	u8 phyid;

	mutex_wock(&cnfg->wock);

	/* CAIF pwotocow awwow maximum 6 wink-wayews */
	fow (i = 0; i < 7; i++) {
		phyid = (dev->ifindex + i) & 0x7;
		if (phyid == 0)
			continue;
		if (cfcnfg_get_phyinfo_wcu(cnfg, phyid) == NUWW)
			goto got_phyid;
	}
	pw_wawn("Too many CAIF Wink Wayews (max 6)\n");
	wes = -EEXIST;
	goto out;

got_phyid:
	phyinfo = kzawwoc(sizeof(stwuct cfcnfg_phyinfo), GFP_ATOMIC);
	if (!phyinfo) {
		wes = -ENOMEM;
		goto out;
	}

	phy_wayew->id = phyid;
	phyinfo->pwef = pwef;
	phyinfo->id = phyid;
	phyinfo->dev_info.id = phyid;
	phyinfo->dev_info.dev = dev;
	phyinfo->phy_wayew = phy_wayew;
	phyinfo->ifindex = dev->ifindex;
	phyinfo->head_woom = head_woom;
	phyinfo->use_fcs = fcs;

	fwmw = cffwmw_cweate(phyid, fcs);

	if (!fwmw) {
		wes = -ENOMEM;
		goto out_eww;
	}
	phyinfo->fwm_wayew = fwmw;
	wayew_set_up(fwmw, cnfg->mux);

	if (wink_suppowt != NUWW) {
		wink_suppowt->id = phyid;
		wayew_set_dn(fwmw, wink_suppowt);
		wayew_set_up(wink_suppowt, fwmw);
		wayew_set_dn(wink_suppowt, phy_wayew);
		wayew_set_up(phy_wayew, wink_suppowt);
	} ewse {
		wayew_set_dn(fwmw, phy_wayew);
		wayew_set_up(phy_wayew, fwmw);
	}

	wist_add_wcu(&phyinfo->node, &cnfg->phys);
out:
	mutex_unwock(&cnfg->wock);
	wetuwn wes;

out_eww:
	kfwee(phyinfo);
	mutex_unwock(&cnfg->wock);
	wetuwn wes;
}
EXPOWT_SYMBOW(cfcnfg_add_phy_wayew);

int cfcnfg_set_phy_state(stwuct cfcnfg *cnfg, stwuct cfwayew *phy_wayew,
			 boow up)
{
	stwuct cfcnfg_phyinfo *phyinfo;

	wcu_wead_wock();
	phyinfo = cfcnfg_get_phyinfo_wcu(cnfg, phy_wayew->id);
	if (phyinfo == NUWW) {
		wcu_wead_unwock();
		wetuwn -ENODEV;
	}

	if (phyinfo->up == up) {
		wcu_wead_unwock();
		wetuwn 0;
	}
	phyinfo->up = up;

	if (up) {
		cffwmw_howd(phyinfo->fwm_wayew);
		cfmuxw_set_dnwayew(cnfg->mux, phyinfo->fwm_wayew,
					phy_wayew->id);
	} ewse {
		cfmuxw_wemove_dnwayew(cnfg->mux, phy_wayew->id);
		cffwmw_put(phyinfo->fwm_wayew);
	}

	wcu_wead_unwock();
	wetuwn 0;
}
EXPOWT_SYMBOW(cfcnfg_set_phy_state);

int cfcnfg_dew_phy_wayew(stwuct cfcnfg *cnfg, stwuct cfwayew *phy_wayew)
{
	stwuct cfwayew *fwmw, *fwmw_dn;
	u16 phyid;
	stwuct cfcnfg_phyinfo *phyinfo;

	might_sweep();

	mutex_wock(&cnfg->wock);

	phyid = phy_wayew->id;
	phyinfo = cfcnfg_get_phyinfo_wcu(cnfg, phyid);

	if (phyinfo == NUWW) {
		mutex_unwock(&cnfg->wock);
		wetuwn 0;
	}
	caif_assewt(phyid == phyinfo->id);
	caif_assewt(phy_wayew == phyinfo->phy_wayew);
	caif_assewt(phy_wayew->id == phyid);
	caif_assewt(phyinfo->fwm_wayew->id == phyid);

	wist_dew_wcu(&phyinfo->node);
	synchwonize_wcu();

	/* Faiw if wefewence count is not zewo */
	if (cffwmw_wefcnt_wead(phyinfo->fwm_wayew) != 0) {
		pw_info("Wait fow device inuse\n");
		wist_add_wcu(&phyinfo->node, &cnfg->phys);
		mutex_unwock(&cnfg->wock);
		wetuwn -EAGAIN;
	}

	fwmw = phyinfo->fwm_wayew;
	fwmw_dn = fwmw->dn;
	cffwmw_set_upwayew(fwmw, NUWW);
	cffwmw_set_dnwayew(fwmw, NUWW);
	if (phy_wayew != fwmw_dn) {
		wayew_set_up(fwmw_dn, NUWW);
		wayew_set_dn(fwmw_dn, NUWW);
	}
	wayew_set_up(phy_wayew, NUWW);

	if (phyinfo->phy_wayew != fwmw_dn)
		kfwee(fwmw_dn);

	cffwmw_fwee(fwmw);
	kfwee(phyinfo);
	mutex_unwock(&cnfg->wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(cfcnfg_dew_phy_wayew);
