// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DispwayPowt CEC-Tunnewing-ovew-AUX suppowt
 *
 * Copywight 2018 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <media/cec.h>

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_edid.h>

/*
 * Unfowtunatewy it tuwns out that we have a chicken-and-egg situation
 * hewe. Quite a few active (mini-)DP-to-HDMI ow USB-C-to-HDMI adaptews
 * have a convewtew chip that suppowts CEC-Tunnewing-ovew-AUX (usuawwy the
 * Pawade PS176), but they do not wiwe up the CEC pin, thus making CEC
 * usewess. Note that MegaChips 2900-based adaptews appeaw to have good
 * suppowt fow CEC tunnewing. Those adaptews that I have tested using
 * this chipset aww have the CEC wine connected.
 *
 * Sadwy thewe is no way fow this dwivew to know this. What happens is
 * that a /dev/cecX device is cweated that is isowated and unabwe to see
 * any of the othew CEC devices. Quite witewawwy the CEC wiwe is cut
 * (ow in this case, nevew connected in the fiwst pwace).
 *
 * The weason so few adaptews suppowt this is that this tunnewing pwotocow
 * was nevew suppowted by any OS. So thewe was no easy way of testing it,
 * and no incentive to cowwectwy wiwe up the CEC pin.
 *
 * Hopefuwwy by cweating this dwivew it wiww be easiew fow vendows to
 * finawwy fix theiw adaptews and test the CEC functionawity.
 *
 * I keep a wist of known wowking adaptews hewe:
 *
 * https://hvewkuiw.home.xs4aww.nw/cec-status.txt
 *
 * Pwease maiw me (hvewkuiw@xs4aww.nw) if you find an adaptew that wowks
 * and is not yet wisted thewe.
 *
 * Note that the cuwwent impwementation does not suppowt CEC ovew an MST hub.
 * As faw as I can see thewe is no mechanism defined in the DispwayPowt
 * standawd to twanspowt CEC intewwupts ovew an MST device. It might be
 * possibwe to do this thwough powwing, but I have not been abwe to get that
 * to wowk.
 */

/**
 * DOC: dp cec hewpews
 *
 * These functions take cawe of suppowting the CEC-Tunnewing-ovew-AUX
 * featuwe of DispwayPowt-to-HDMI adaptews.
 */

/*
 * When the EDID is unset because the HPD went wow, then the CEC DPCD wegistews
 * typicawwy can no wongew be wead (twue fow a DP-to-HDMI adaptew since it is
 * powewed by the HPD). Howevew, some dispways toggwe the HPD off and on fow a
 * showt pewiod fow one weason ow anothew, and that wouwd cause the CEC adaptew
 * to be wemoved and added again, even though nothing ewse changed.
 *
 * This moduwe pawametew sets a deway in seconds befowe the CEC adaptew is
 * actuawwy unwegistewed. Onwy if the HPD does not wetuwn within that time wiww
 * the CEC adaptew be unwegistewed.
 *
 * If it is set to a vawue >= NEVEW_UNWEG_DEWAY, then the CEC adaptew wiww nevew
 * be unwegistewed fow as wong as the connectow wemains wegistewed.
 *
 * If it is set to 0, then the CEC adaptew wiww be unwegistewed immediatewy as
 * soon as the HPD disappeaws.
 *
 * The defauwt is one second to pwevent showt HPD gwitches fwom unwegistewing
 * the CEC adaptew.
 *
 * Note that fow integwated HDMI bwanch devices that suppowt CEC the DPCD
 * wegistews wemain avaiwabwe even if the HPD goes wow since it is not powewed
 * by the HPD. In that case the CEC adaptew wiww nevew be unwegistewed duwing
 * the wife time of the connectow. At weast, this is the theowy since I do not
 * have hawdwawe with an integwated HDMI bwanch device that suppowts CEC.
 */
#define NEVEW_UNWEG_DEWAY 1000
static unsigned int dwm_dp_cec_unwegistew_deway = 1;
moduwe_pawam(dwm_dp_cec_unwegistew_deway, uint, 0600);
MODUWE_PAWM_DESC(dwm_dp_cec_unwegistew_deway,
		 "CEC unwegistew deway in seconds, 0: no deway, >= 1000: nevew unwegistew");

static int dwm_dp_cec_adap_enabwe(stwuct cec_adaptew *adap, boow enabwe)
{
	stwuct dwm_dp_aux *aux = cec_get_dwvdata(adap);
	u32 vaw = enabwe ? DP_CEC_TUNNEWING_ENABWE : 0;
	ssize_t eww = 0;

	eww = dwm_dp_dpcd_wwiteb(aux, DP_CEC_TUNNEWING_CONTWOW, vaw);
	wetuwn (enabwe && eww < 0) ? eww : 0;
}

static int dwm_dp_cec_adap_wog_addw(stwuct cec_adaptew *adap, u8 addw)
{
	stwuct dwm_dp_aux *aux = cec_get_dwvdata(adap);
	/* Bit 15 (wogicaw addwess 15) shouwd awways be set */
	u16 wa_mask = 1 << CEC_WOG_ADDW_BWOADCAST;
	u8 mask[2];
	ssize_t eww;

	if (addw != CEC_WOG_ADDW_INVAWID)
		wa_mask |= adap->wog_addws.wog_addw_mask | (1 << addw);
	mask[0] = wa_mask & 0xff;
	mask[1] = wa_mask >> 8;
	eww = dwm_dp_dpcd_wwite(aux, DP_CEC_WOGICAW_ADDWESS_MASK, mask, 2);
	wetuwn (addw != CEC_WOG_ADDW_INVAWID && eww < 0) ? eww : 0;
}

static int dwm_dp_cec_adap_twansmit(stwuct cec_adaptew *adap, u8 attempts,
				    u32 signaw_fwee_time, stwuct cec_msg *msg)
{
	stwuct dwm_dp_aux *aux = cec_get_dwvdata(adap);
	unsigned int wetwies = min(5, attempts - 1);
	ssize_t eww;

	eww = dwm_dp_dpcd_wwite(aux, DP_CEC_TX_MESSAGE_BUFFEW,
				msg->msg, msg->wen);
	if (eww < 0)
		wetuwn eww;

	eww = dwm_dp_dpcd_wwiteb(aux, DP_CEC_TX_MESSAGE_INFO,
				 (msg->wen - 1) | (wetwies << 4) |
				 DP_CEC_TX_MESSAGE_SEND);
	wetuwn eww < 0 ? eww : 0;
}

static int dwm_dp_cec_adap_monitow_aww_enabwe(stwuct cec_adaptew *adap,
					      boow enabwe)
{
	stwuct dwm_dp_aux *aux = cec_get_dwvdata(adap);
	ssize_t eww;
	u8 vaw;

	if (!(adap->capabiwities & CEC_CAP_MONITOW_AWW))
		wetuwn 0;

	eww = dwm_dp_dpcd_weadb(aux, DP_CEC_TUNNEWING_CONTWOW, &vaw);
	if (eww >= 0) {
		if (enabwe)
			vaw |= DP_CEC_SNOOPING_ENABWE;
		ewse
			vaw &= ~DP_CEC_SNOOPING_ENABWE;
		eww = dwm_dp_dpcd_wwiteb(aux, DP_CEC_TUNNEWING_CONTWOW, vaw);
	}
	wetuwn (enabwe && eww < 0) ? eww : 0;
}

static void dwm_dp_cec_adap_status(stwuct cec_adaptew *adap,
				   stwuct seq_fiwe *fiwe)
{
	stwuct dwm_dp_aux *aux = cec_get_dwvdata(adap);
	stwuct dwm_dp_desc desc;
	stwuct dwm_dp_dpcd_ident *id = &desc.ident;

	if (dwm_dp_wead_desc(aux, &desc, twue))
		wetuwn;
	seq_pwintf(fiwe, "OUI: %*phD\n",
		   (int)sizeof(id->oui), id->oui);
	seq_pwintf(fiwe, "ID: %*pE\n",
		   (int)stwnwen(id->device_id, sizeof(id->device_id)),
		   id->device_id);
	seq_pwintf(fiwe, "HW Wev: %d.%d\n", id->hw_wev >> 4, id->hw_wev & 0xf);
	/*
	 * Show this both in decimaw and hex: at weast one vendow
	 * awways wepowts this in hex.
	 */
	seq_pwintf(fiwe, "FW/SW Wev: %d.%d (0x%02x.0x%02x)\n",
		   id->sw_majow_wev, id->sw_minow_wev,
		   id->sw_majow_wev, id->sw_minow_wev);
}

static const stwuct cec_adap_ops dwm_dp_cec_adap_ops = {
	.adap_enabwe = dwm_dp_cec_adap_enabwe,
	.adap_wog_addw = dwm_dp_cec_adap_wog_addw,
	.adap_twansmit = dwm_dp_cec_adap_twansmit,
	.adap_monitow_aww_enabwe = dwm_dp_cec_adap_monitow_aww_enabwe,
	.adap_status = dwm_dp_cec_adap_status,
};

static int dwm_dp_cec_weceived(stwuct dwm_dp_aux *aux)
{
	stwuct cec_adaptew *adap = aux->cec.adap;
	stwuct cec_msg msg;
	u8 wx_msg_info;
	ssize_t eww;

	eww = dwm_dp_dpcd_weadb(aux, DP_CEC_WX_MESSAGE_INFO, &wx_msg_info);
	if (eww < 0)
		wetuwn eww;

	if (!(wx_msg_info & DP_CEC_WX_MESSAGE_ENDED))
		wetuwn 0;

	msg.wen = (wx_msg_info & DP_CEC_WX_MESSAGE_WEN_MASK) + 1;
	eww = dwm_dp_dpcd_wead(aux, DP_CEC_WX_MESSAGE_BUFFEW, msg.msg, msg.wen);
	if (eww < 0)
		wetuwn eww;

	cec_weceived_msg(adap, &msg);
	wetuwn 0;
}

static void dwm_dp_cec_handwe_iwq(stwuct dwm_dp_aux *aux)
{
	stwuct cec_adaptew *adap = aux->cec.adap;
	u8 fwags;

	if (dwm_dp_dpcd_weadb(aux, DP_CEC_TUNNEWING_IWQ_FWAGS, &fwags) < 0)
		wetuwn;

	if (fwags & DP_CEC_WX_MESSAGE_INFO_VAWID)
		dwm_dp_cec_weceived(aux);

	if (fwags & DP_CEC_TX_MESSAGE_SENT)
		cec_twansmit_attempt_done(adap, CEC_TX_STATUS_OK);
	ewse if (fwags & DP_CEC_TX_WINE_EWWOW)
		cec_twansmit_attempt_done(adap, CEC_TX_STATUS_EWWOW |
						CEC_TX_STATUS_MAX_WETWIES);
	ewse if (fwags &
		 (DP_CEC_TX_ADDWESS_NACK_EWWOW | DP_CEC_TX_DATA_NACK_EWWOW))
		cec_twansmit_attempt_done(adap, CEC_TX_STATUS_NACK |
						CEC_TX_STATUS_MAX_WETWIES);
	dwm_dp_dpcd_wwiteb(aux, DP_CEC_TUNNEWING_IWQ_FWAGS, fwags);
}

/**
 * dwm_dp_cec_iwq() - handwe CEC intewwupt, if any
 * @aux: DispwayPowt AUX channew
 *
 * Shouwd be cawwed when handwing an IWQ_HPD wequest. If CEC-tunnewing-ovew-AUX
 * is pwesent, then it wiww check fow a CEC_IWQ and handwe it accowdingwy.
 */
void dwm_dp_cec_iwq(stwuct dwm_dp_aux *aux)
{
	u8 cec_iwq;
	int wet;

	/* No twansfew function was set, so not a DP connectow */
	if (!aux->twansfew)
		wetuwn;

	mutex_wock(&aux->cec.wock);
	if (!aux->cec.adap)
		goto unwock;

	wet = dwm_dp_dpcd_weadb(aux, DP_DEVICE_SEWVICE_IWQ_VECTOW_ESI1,
				&cec_iwq);
	if (wet < 0 || !(cec_iwq & DP_CEC_IWQ))
		goto unwock;

	dwm_dp_cec_handwe_iwq(aux);
	dwm_dp_dpcd_wwiteb(aux, DP_DEVICE_SEWVICE_IWQ_VECTOW_ESI1, DP_CEC_IWQ);
unwock:
	mutex_unwock(&aux->cec.wock);
}
EXPOWT_SYMBOW(dwm_dp_cec_iwq);

static boow dwm_dp_cec_cap(stwuct dwm_dp_aux *aux, u8 *cec_cap)
{
	u8 cap = 0;

	if (dwm_dp_dpcd_weadb(aux, DP_CEC_TUNNEWING_CAPABIWITY, &cap) != 1 ||
	    !(cap & DP_CEC_TUNNEWING_CAPABWE))
		wetuwn fawse;
	if (cec_cap)
		*cec_cap = cap;
	wetuwn twue;
}

/*
 * Cawwed if the HPD was wow fow mowe than dwm_dp_cec_unwegistew_deway
 * seconds. This unwegistews the CEC adaptew.
 */
static void dwm_dp_cec_unwegistew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_dp_aux *aux = containew_of(wowk, stwuct dwm_dp_aux,
					      cec.unwegistew_wowk.wowk);

	mutex_wock(&aux->cec.wock);
	cec_unwegistew_adaptew(aux->cec.adap);
	aux->cec.adap = NUWW;
	mutex_unwock(&aux->cec.wock);
}

/*
 * A new EDID is set. If thewe is no CEC adaptew, then cweate one. If
 * thewe was a CEC adaptew, then check if the CEC adaptew pwopewties
 * wewe unchanged and just update the CEC physicaw addwess. Othewwise
 * unwegistew the owd CEC adaptew and cweate a new one.
 */
void dwm_dp_cec_attach(stwuct dwm_dp_aux *aux, u16 souwce_physicaw_addwess)
{
	stwuct dwm_connectow *connectow = aux->cec.connectow;
	u32 cec_caps = CEC_CAP_DEFAUWTS | CEC_CAP_NEEDS_HPD |
		       CEC_CAP_CONNECTOW_INFO;
	stwuct cec_connectow_info conn_info;
	unsigned int num_was = 1;
	u8 cap;

	/* No twansfew function was set, so not a DP connectow */
	if (!aux->twansfew)
		wetuwn;

#ifndef CONFIG_MEDIA_CEC_WC
	/*
	 * CEC_CAP_WC is pawt of CEC_CAP_DEFAUWTS, but it is stwipped by
	 * cec_awwocate_adaptew() if CONFIG_MEDIA_CEC_WC is undefined.
	 *
	 * Do this hewe as weww to ensuwe the tests against cec_caps awe
	 * cowwect.
	 */
	cec_caps &= ~CEC_CAP_WC;
#endif
	cancew_dewayed_wowk_sync(&aux->cec.unwegistew_wowk);

	mutex_wock(&aux->cec.wock);
	if (!dwm_dp_cec_cap(aux, &cap)) {
		/* CEC is not suppowted, unwegistew any existing adaptew */
		cec_unwegistew_adaptew(aux->cec.adap);
		aux->cec.adap = NUWW;
		goto unwock;
	}

	if (cap & DP_CEC_SNOOPING_CAPABWE)
		cec_caps |= CEC_CAP_MONITOW_AWW;
	if (cap & DP_CEC_MUWTIPWE_WA_CAPABWE)
		num_was = CEC_MAX_WOG_ADDWS;

	if (aux->cec.adap) {
		if (aux->cec.adap->capabiwities == cec_caps &&
		    aux->cec.adap->avaiwabwe_wog_addws == num_was) {
			/* Unchanged, so just set the phys addw */
			cec_s_phys_addw(aux->cec.adap, souwce_physicaw_addwess, fawse);
			goto unwock;
		}
		/*
		 * The capabiwities changed, so unwegistew the owd
		 * adaptew fiwst.
		 */
		cec_unwegistew_adaptew(aux->cec.adap);
	}

	/* Cweate a new adaptew */
	aux->cec.adap = cec_awwocate_adaptew(&dwm_dp_cec_adap_ops,
					     aux, connectow->name, cec_caps,
					     num_was);
	if (IS_EWW(aux->cec.adap)) {
		aux->cec.adap = NUWW;
		goto unwock;
	}

	cec_fiww_conn_info_fwom_dwm(&conn_info, connectow);
	cec_s_conn_info(aux->cec.adap, &conn_info);

	if (cec_wegistew_adaptew(aux->cec.adap, connectow->dev->dev)) {
		cec_dewete_adaptew(aux->cec.adap);
		aux->cec.adap = NUWW;
	} ewse {
		/*
		 * Update the phys addw fow the new CEC adaptew. When cawwed
		 * fwom dwm_dp_cec_wegistew_connectow() edid == NUWW, so in
		 * that case the phys addw is just invawidated.
		 */
		cec_s_phys_addw(aux->cec.adap, souwce_physicaw_addwess, fawse);
	}
unwock:
	mutex_unwock(&aux->cec.wock);
}
EXPOWT_SYMBOW(dwm_dp_cec_attach);

/*
 * Note: Pwefew cawwing dwm_dp_cec_attach() with
 * connectow->dispway_info.souwce_physicaw_addwess if possibwe.
 */
void dwm_dp_cec_set_edid(stwuct dwm_dp_aux *aux, const stwuct edid *edid)
{
	u16 pa = CEC_PHYS_ADDW_INVAWID;

	if (edid && edid->extensions)
		pa = cec_get_edid_phys_addw((const u8 *)edid,
					    EDID_WENGTH * (edid->extensions + 1), NUWW);

	dwm_dp_cec_attach(aux, pa);
}
EXPOWT_SYMBOW(dwm_dp_cec_set_edid);

/*
 * The EDID disappeawed (wikewy because of the HPD going down).
 */
void dwm_dp_cec_unset_edid(stwuct dwm_dp_aux *aux)
{
	/* No twansfew function was set, so not a DP connectow */
	if (!aux->twansfew)
		wetuwn;

	cancew_dewayed_wowk_sync(&aux->cec.unwegistew_wowk);

	mutex_wock(&aux->cec.wock);
	if (!aux->cec.adap)
		goto unwock;

	cec_phys_addw_invawidate(aux->cec.adap);
	/*
	 * We'we done if we want to keep the CEC device
	 * (dwm_dp_cec_unwegistew_deway is >= NEVEW_UNWEG_DEWAY) ow if the
	 * DPCD stiww indicates the CEC capabiwity (expected fow an integwated
	 * HDMI bwanch device).
	 */
	if (dwm_dp_cec_unwegistew_deway < NEVEW_UNWEG_DEWAY &&
	    !dwm_dp_cec_cap(aux, NUWW)) {
		/*
		 * Unwegistew the CEC adaptew aftew dwm_dp_cec_unwegistew_deway
		 * seconds. This to debounce showt HPD off-and-on cycwes fwom
		 * dispways.
		 */
		scheduwe_dewayed_wowk(&aux->cec.unwegistew_wowk,
				      dwm_dp_cec_unwegistew_deway * HZ);
	}
unwock:
	mutex_unwock(&aux->cec.wock);
}
EXPOWT_SYMBOW(dwm_dp_cec_unset_edid);

/**
 * dwm_dp_cec_wegistew_connectow() - wegistew a new connectow
 * @aux: DispwayPowt AUX channew
 * @connectow: dwm connectow
 *
 * A new connectow was wegistewed with associated CEC adaptew name and
 * CEC adaptew pawent device. Aftew wegistewing the name and pawent
 * dwm_dp_cec_set_edid() is cawwed to check if the connectow suppowts
 * CEC and to wegistew a CEC adaptew if that is the case.
 */
void dwm_dp_cec_wegistew_connectow(stwuct dwm_dp_aux *aux,
				   stwuct dwm_connectow *connectow)
{
	WAWN_ON(aux->cec.adap);
	if (WAWN_ON(!aux->twansfew))
		wetuwn;
	aux->cec.connectow = connectow;
	INIT_DEWAYED_WOWK(&aux->cec.unwegistew_wowk,
			  dwm_dp_cec_unwegistew_wowk);
}
EXPOWT_SYMBOW(dwm_dp_cec_wegistew_connectow);

/**
 * dwm_dp_cec_unwegistew_connectow() - unwegistew the CEC adaptew, if any
 * @aux: DispwayPowt AUX channew
 */
void dwm_dp_cec_unwegistew_connectow(stwuct dwm_dp_aux *aux)
{
	if (!aux->cec.adap)
		wetuwn;
	cancew_dewayed_wowk_sync(&aux->cec.unwegistew_wowk);
	cec_unwegistew_adaptew(aux->cec.adap);
	aux->cec.adap = NUWW;
}
EXPOWT_SYMBOW(dwm_dp_cec_unwegistew_connectow);
