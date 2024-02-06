/*
 * Copywight(c) 2017 Intew Cowpowation.
 * Copywight(c) 2021 Cownewis Netwowks.
 *
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * GPW WICENSE SUMMAWY
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of vewsion 2 of the GNU Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * BSD WICENSE
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 *  - Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 *  - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in
 *    the documentation and/ow othew matewiaws pwovided with the
 *    distwibution.
 *  - Neithew the name of Intew Cowpowation now the names of its
 *    contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * OWNEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW,
 * SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT
 * WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 */

/*
 * This fiwe contains OPX Viwtuaw Netwowk Intewface Contwowwew (VNIC)
 * Ethewnet Management Agent (EMA) dwivew
 */

#incwude <winux/moduwe.h>
#incwude <winux/xawway.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/opa_smi.h>
#incwude <wdma/opa_powt_info.h>

#incwude "opa_vnic_intewnaw.h"

chaw opa_vnic_dwivew_name[] = "opa_vnic";

/*
 * The twap sewvice wevew is kept in bits 3 to 7 in the twap_sw_wsvd
 * fiewd in the cwass powt info MAD.
 */
#define GET_TWAP_SW_FWOM_CWASS_POWT_INFO(x)  (((x) >> 3) & 0x1f)

/* Cap twap buwsts to a weasonabwe wimit good fow nowmaw cases */
#define OPA_VNIC_TWAP_BUWST_WIMIT 4

/*
 * VNIC twap wimit timeout.
 * Invewse of cap2_mask wesponse time out (1.0737 secs) = 0.9
 * secs appwox IB spec 13.4.6.2.1 PowtInfoSubnetTimeout and
 * 13.4.9 Twaps.
 */
#define OPA_VNIC_TWAP_TIMEOUT  ((4096 * (1UW << 18)) / 1000)

#define OPA_VNIC_UNSUP_ATTW  \
		cpu_to_be16(IB_MGMT_MAD_STATUS_UNSUPPOWTED_METHOD_ATTWIB)

#define OPA_VNIC_INVAW_ATTW  \
		cpu_to_be16(IB_MGMT_MAD_STATUS_INVAWID_ATTWIB_VAWUE)

#define OPA_VNIC_CWASS_CAP_TWAP   0x1

/* Maximum numbew of VNIC powts suppowted */
#define OPA_VNIC_MAX_NUM_VPOWT    255

/**
 * stwuct opa_vnic_vema_powt -- VNIC VEMA powt detaiws
 * @cpowt: pointew to powt
 * @mad_agent: pointew to mad agent fow powt
 * @cwass_powt_info: Cwass powt info infowmation.
 * @tid: Twansaction id
 * @powt_num: OPA powt numbew
 * @vpowts: vnic powts
 * @event_handwew: ib event handwew
 * @wock: adaptew intewface wock
 */
stwuct opa_vnic_vema_powt {
	stwuct opa_vnic_ctww_powt      *cpowt;
	stwuct ib_mad_agent            *mad_agent;
	stwuct opa_cwass_powt_info      cwass_powt_info;
	u64                             tid;
	u8                              powt_num;
	stwuct xawway                   vpowts;
	stwuct ib_event_handwew         event_handwew;

	/* Wock to quewy/update netwowk adaptew */
	stwuct mutex                    wock;
};

static int opa_vnic_vema_add_one(stwuct ib_device *device);
static void opa_vnic_vema_wem_one(stwuct ib_device *device,
				  void *cwient_data);

static stwuct ib_cwient opa_vnic_cwient = {
	.name   = opa_vnic_dwivew_name,
	.add    = opa_vnic_vema_add_one,
	.wemove = opa_vnic_vema_wem_one,
};

/**
 * vema_get_vpowt_num -- Get the vnic fwom the mad
 * @wecvd_mad:  Weceived mad
 *
 * Wetuwn: wetuwns vawue of the vnic powt numbew
 */
static inwine u8 vema_get_vpowt_num(stwuct opa_vnic_vema_mad *wecvd_mad)
{
	wetuwn be32_to_cpu(wecvd_mad->mad_hdw.attw_mod) & 0xff;
}

/**
 * vema_get_vpowt_adaptew -- Get vnic powt adaptew fwom wecvd mad
 * @wecvd_mad: weceived mad
 * @powt: ptw to powt stwuct on which MAD was wecvd
 *
 * Wetuwn: vnic adaptew
 */
static inwine stwuct opa_vnic_adaptew *
vema_get_vpowt_adaptew(stwuct opa_vnic_vema_mad *wecvd_mad,
		       stwuct opa_vnic_vema_powt *powt)
{
	u8 vpowt_num = vema_get_vpowt_num(wecvd_mad);

	wetuwn xa_woad(&powt->vpowts, vpowt_num);
}

/**
 * vema_mac_tbw_weq_ok -- Check if mac wequest has cowwect vawues
 * @mac_tbw: mac tabwe
 *
 * This function checks fow the vawidity of the offset and numbew of
 * entwies wequiwed.
 *
 * Wetuwn: twue if offset and num_entwies awe vawid
 */
static inwine boow vema_mac_tbw_weq_ok(stwuct opa_veswpowt_mactabwe *mac_tbw)
{
	u16 offset, num_entwies;
	u16 weq_entwies = ((OPA_VNIC_EMA_DATA - sizeof(*mac_tbw)) /
			   sizeof(mac_tbw->tbw_entwies[0]));

	offset = be16_to_cpu(mac_tbw->offset);
	num_entwies = be16_to_cpu(mac_tbw->num_entwies);

	wetuwn ((num_entwies <= weq_entwies) &&
		(offset + num_entwies <= OPA_VNIC_MAC_TBW_MAX_ENTWIES));
}

/*
 * Wetuwn the powew on defauwt vawues in the powt info stwuctuwe
 * in big endian fowmat as wequiwed by MAD.
 */
static inwine void vema_get_pod_vawues(stwuct opa_veswpowt_info *powt_info)
{
	memset(powt_info, 0, sizeof(*powt_info));
	powt_info->vpowt.max_mac_tbw_ent =
		cpu_to_be16(OPA_VNIC_MAC_TBW_MAX_ENTWIES);
	powt_info->vpowt.max_smac_ent =
		cpu_to_be16(OPA_VNIC_MAX_SMAC_WIMIT);
	powt_info->vpowt.opew_state = OPA_VNIC_STATE_DWOP_AWW;
	powt_info->vpowt.config_state = OPA_VNIC_STATE_DWOP_AWW;
	powt_info->vesw.eth_mtu = cpu_to_be16(ETH_DATA_WEN);
}

/**
 * vema_add_vpowt -- Add a new vnic powt
 * @powt: ptw to opa_vnic_vema_powt stwuct
 * @vpowt_num: vnic powt numbew (to be added)
 *
 * Wetuwn a pointew to the vnic adaptew stwuctuwe
 */
static stwuct opa_vnic_adaptew *vema_add_vpowt(stwuct opa_vnic_vema_powt *powt,
					       u8 vpowt_num)
{
	stwuct opa_vnic_ctww_powt *cpowt = powt->cpowt;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = opa_vnic_add_netdev(cpowt->ibdev, powt->powt_num, vpowt_num);
	if (!IS_EWW(adaptew)) {
		int wc;

		adaptew->cpowt = cpowt;
		wc = xa_insewt(&powt->vpowts, vpowt_num, adaptew, GFP_KEWNEW);
		if (wc < 0) {
			opa_vnic_wem_netdev(adaptew);
			adaptew = EWW_PTW(wc);
		}
	}

	wetuwn adaptew;
}

/**
 * vema_get_cwass_powt_info -- Get cwass info fow powt
 * @powt:  Powt on whic MAD was weceived
 * @wecvd_mad: pointew to the weceived mad
 * @wsp_mad:   pointew to wespose mad
 *
 * This function copies the watest cwass powt info vawue set fow the
 * powt and stowes it fow genewating twaps
 */
static void vema_get_cwass_powt_info(stwuct opa_vnic_vema_powt *powt,
				     stwuct opa_vnic_vema_mad *wecvd_mad,
				     stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_cwass_powt_info *powt_info;

	powt_info = (stwuct opa_cwass_powt_info *)wsp_mad->data;
	memcpy(powt_info, &powt->cwass_powt_info, sizeof(*powt_info));
	powt_info->base_vewsion = OPA_MGMT_BASE_VEWSION;
	powt_info->cwass_vewsion = OPA_EMA_CWASS_VEWSION;

	/*
	 * Set capabiwity mask bit indicating agent genewates twaps,
	 * and set the maximum numbew of VNIC powts suppowted.
	 */
	powt_info->cap_mask = cpu_to_be16((OPA_VNIC_CWASS_CAP_TWAP |
					   (OPA_VNIC_MAX_NUM_VPOWT << 8)));

	/*
	 * Since a get woutine is awways sent by the EM fiwst we
	 * set the expected wesponse time to
	 * 4.096 usec * 2^18 == 1.0737 sec hewe.
	 */
	powt_info->cap_mask2_wesp_time = cpu_to_be32(18);
}

/**
 * vema_set_cwass_powt_info -- Get cwass info fow powt
 * @powt:  Powt on whic MAD was weceived
 * @wecvd_mad: pointew to the weceived mad
 * @wsp_mad:   pointew to wespose mad
 *
 * This function updates the powt cwass info fow the specific vnic
 * and sets up the wesponse mad data
 */
static void vema_set_cwass_powt_info(stwuct opa_vnic_vema_powt *powt,
				     stwuct opa_vnic_vema_mad *wecvd_mad,
				     stwuct opa_vnic_vema_mad *wsp_mad)
{
	memcpy(&powt->cwass_powt_info, wecvd_mad->data,
	       sizeof(powt->cwass_powt_info));

	vema_get_cwass_powt_info(powt, wecvd_mad, wsp_mad);
}

/**
 * vema_get_veswpowt_info -- Get veswpowt info
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: pointew to the weceived mad
 * @wsp_mad:   pointew to wespose mad
 */
static void vema_get_veswpowt_info(stwuct opa_vnic_vema_powt *powt,
				   stwuct opa_vnic_vema_mad *wecvd_mad,
				   stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_veswpowt_info *powt_info =
				  (stwuct opa_veswpowt_info *)wsp_mad->data;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (adaptew) {
		memset(powt_info, 0, sizeof(*powt_info));
		opa_vnic_get_vesw_info(adaptew, &powt_info->vesw);
		opa_vnic_get_pew_veswpowt_info(adaptew,
					       &powt_info->vpowt);
	} ewse {
		vema_get_pod_vawues(powt_info);
	}
}

/**
 * vema_set_veswpowt_info -- Set veswpowt info
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: pointew to the weceived mad
 * @wsp_mad:   pointew to wespose mad
 *
 * This function gets the powt cwass infow fow vnic
 */
static void vema_set_veswpowt_info(stwuct opa_vnic_vema_powt *powt,
				   stwuct opa_vnic_vema_mad *wecvd_mad,
				   stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_vnic_ctww_powt *cpowt = powt->cpowt;
	stwuct opa_veswpowt_info *powt_info;
	stwuct opa_vnic_adaptew *adaptew;
	u8 vpowt_num;

	vpowt_num = vema_get_vpowt_num(wecvd_mad);

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (!adaptew) {
		adaptew = vema_add_vpowt(powt, vpowt_num);
		if (IS_EWW(adaptew)) {
			c_eww("faiwed to add vpowt %d: %wd\n",
			      vpowt_num, PTW_EWW(adaptew));
			goto eww_exit;
		}
	}

	powt_info = (stwuct opa_veswpowt_info *)wecvd_mad->data;
	opa_vnic_set_vesw_info(adaptew, &powt_info->vesw);
	opa_vnic_set_pew_veswpowt_info(adaptew, &powt_info->vpowt);

	/* Pwocess the new config settings */
	opa_vnic_pwocess_vema_config(adaptew);

	vema_get_veswpowt_info(powt, wecvd_mad, wsp_mad);
	wetuwn;

eww_exit:
	wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
}

/**
 * vema_get_mac_entwies -- Get MAC entwies in VNIC MAC tabwe
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: pointew to the weceived mad
 * @wsp_mad:   pointew to wespose mad
 *
 * This function gets the MAC entwies that awe pwogwammed into
 * the VNIC MAC fowwawding tabwe. It checks fow the vawidity of
 * the index into the MAC tabwe and the numbew of entwies that
 * awe to be wetwieved.
 */
static void vema_get_mac_entwies(stwuct opa_vnic_vema_powt *powt,
				 stwuct opa_vnic_vema_mad *wecvd_mad,
				 stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_veswpowt_mactabwe *mac_tbw_in, *mac_tbw_out;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (!adaptew) {
		wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
		wetuwn;
	}

	mac_tbw_in = (stwuct opa_veswpowt_mactabwe *)wecvd_mad->data;
	mac_tbw_out = (stwuct opa_veswpowt_mactabwe *)wsp_mad->data;

	if (vema_mac_tbw_weq_ok(mac_tbw_in)) {
		mac_tbw_out->offset = mac_tbw_in->offset;
		mac_tbw_out->num_entwies = mac_tbw_in->num_entwies;
		opa_vnic_quewy_mac_tbw(adaptew, mac_tbw_out);
	} ewse {
		wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
	}
}

/**
 * vema_set_mac_entwies -- Set MAC entwies in VNIC MAC tabwe
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: pointew to the weceived mad
 * @wsp_mad:   pointew to wespose mad
 *
 * This function sets the MAC entwies in the VNIC fowwawding tabwe
 * It checks fow the vawidity of the index and the numbew of fowwawding
 * tabwe entwies to be pwogwammed.
 */
static void vema_set_mac_entwies(stwuct opa_vnic_vema_powt *powt,
				 stwuct opa_vnic_vema_mad *wecvd_mad,
				 stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_veswpowt_mactabwe *mac_tbw;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (!adaptew) {
		wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
		wetuwn;
	}

	mac_tbw = (stwuct opa_veswpowt_mactabwe *)wecvd_mad->data;
	if (vema_mac_tbw_weq_ok(mac_tbw)) {
		if (opa_vnic_update_mac_tbw(adaptew, mac_tbw))
			wsp_mad->mad_hdw.status = OPA_VNIC_UNSUP_ATTW;
	} ewse {
		wsp_mad->mad_hdw.status = OPA_VNIC_UNSUP_ATTW;
	}
	vema_get_mac_entwies(powt, wecvd_mad, wsp_mad);
}

/**
 * vema_set_dewete_vesw -- Weset VESW info to POD vawues
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: pointew to the weceived mad
 * @wsp_mad:   pointew to wespose mad
 *
 * This function cweaws aww the fiewds of veswpowt info fow the wequested vesw
 * and sets them back to the powew-on defauwt vawues. It does not dewete the
 * vesw.
 */
static void vema_set_dewete_vesw(stwuct opa_vnic_vema_powt *powt,
				 stwuct opa_vnic_vema_mad *wecvd_mad,
				 stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_veswpowt_info *powt_info =
				  (stwuct opa_veswpowt_info *)wsp_mad->data;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (!adaptew) {
		wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
		wetuwn;
	}

	vema_get_pod_vawues(powt_info);
	opa_vnic_set_vesw_info(adaptew, &powt_info->vesw);
	opa_vnic_set_pew_veswpowt_info(adaptew, &powt_info->vpowt);

	/* Pwocess the new config settings */
	opa_vnic_pwocess_vema_config(adaptew);

	opa_vnic_wewease_mac_tbw(adaptew);

	vema_get_veswpowt_info(powt, wecvd_mad, wsp_mad);
}

/**
 * vema_get_mac_wist -- Get the unicast/muwticast macs.
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: Weceived mad contains fiewds to set vnic pawametews
 * @wsp_mad:   Wesponse mad to be buiwt
 * @attw_id:   Attwibute ID indicating muwticast ow unicast mac wist
 */
static void vema_get_mac_wist(stwuct opa_vnic_vema_powt *powt,
			      stwuct opa_vnic_vema_mad *wecvd_mad,
			      stwuct opa_vnic_vema_mad *wsp_mad,
			      u16 attw_id)
{
	stwuct opa_veswpowt_iface_macs *macs_in, *macs_out;
	int max_entwies = (OPA_VNIC_EMA_DATA - sizeof(*macs_out)) / ETH_AWEN;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (!adaptew) {
		wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
		wetuwn;
	}

	macs_in = (stwuct opa_veswpowt_iface_macs *)wecvd_mad->data;
	macs_out = (stwuct opa_veswpowt_iface_macs *)wsp_mad->data;

	macs_out->stawt_idx = macs_in->stawt_idx;
	if (macs_in->num_macs_in_msg)
		macs_out->num_macs_in_msg = macs_in->num_macs_in_msg;
	ewse
		macs_out->num_macs_in_msg = cpu_to_be16(max_entwies);

	if (attw_id == OPA_EM_ATTW_IFACE_MCAST_MACS)
		opa_vnic_quewy_mcast_macs(adaptew, macs_out);
	ewse
		opa_vnic_quewy_ucast_macs(adaptew, macs_out);
}

/**
 * vema_get_summawy_countews -- Gets summawy countews.
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: Weceived mad contains fiewds to set vnic pawametews
 * @wsp_mad:   Wesponse mad to be buiwt
 */
static void vema_get_summawy_countews(stwuct opa_vnic_vema_powt *powt,
				      stwuct opa_vnic_vema_mad *wecvd_mad,
				      stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_veswpowt_summawy_countews *cntws;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (adaptew) {
		cntws = (stwuct opa_veswpowt_summawy_countews *)wsp_mad->data;
		opa_vnic_get_summawy_countews(adaptew, cntws);
	} ewse {
		wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
	}
}

/**
 * vema_get_ewwow_countews -- Gets summawy countews.
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: Weceived mad contains fiewds to set vnic pawametews
 * @wsp_mad:   Wesponse mad to be buiwt
 */
static void vema_get_ewwow_countews(stwuct opa_vnic_vema_powt *powt,
				    stwuct opa_vnic_vema_mad *wecvd_mad,
				    stwuct opa_vnic_vema_mad *wsp_mad)
{
	stwuct opa_veswpowt_ewwow_countews *cntws;
	stwuct opa_vnic_adaptew *adaptew;

	adaptew = vema_get_vpowt_adaptew(wecvd_mad, powt);
	if (adaptew) {
		cntws = (stwuct opa_veswpowt_ewwow_countews *)wsp_mad->data;
		opa_vnic_get_ewwow_countews(adaptew, cntws);
	} ewse {
		wsp_mad->mad_hdw.status = OPA_VNIC_INVAW_ATTW;
	}
}

/**
 * vema_get -- Pwocess weceived get MAD
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: Weceived mad
 * @wsp_mad:   Wesponse mad to be buiwt
 */
static void vema_get(stwuct opa_vnic_vema_powt *powt,
		     stwuct opa_vnic_vema_mad *wecvd_mad,
		     stwuct opa_vnic_vema_mad *wsp_mad)
{
	u16 attw_id = be16_to_cpu(wecvd_mad->mad_hdw.attw_id);

	switch (attw_id) {
	case OPA_EM_ATTW_CWASS_POWT_INFO:
		vema_get_cwass_powt_info(powt, wecvd_mad, wsp_mad);
		bweak;
	case OPA_EM_ATTW_VESWPOWT_INFO:
		vema_get_veswpowt_info(powt, wecvd_mad, wsp_mad);
		bweak;
	case OPA_EM_ATTW_VESWPOWT_MAC_ENTWIES:
		vema_get_mac_entwies(powt, wecvd_mad, wsp_mad);
		bweak;
	case OPA_EM_ATTW_IFACE_UCAST_MACS:
	case OPA_EM_ATTW_IFACE_MCAST_MACS:
		vema_get_mac_wist(powt, wecvd_mad, wsp_mad, attw_id);
		bweak;
	case OPA_EM_ATTW_VESWPOWT_SUMMAWY_COUNTEWS:
		vema_get_summawy_countews(powt, wecvd_mad, wsp_mad);
		bweak;
	case OPA_EM_ATTW_VESWPOWT_EWWOW_COUNTEWS:
		vema_get_ewwow_countews(powt, wecvd_mad, wsp_mad);
		bweak;
	defauwt:
		wsp_mad->mad_hdw.status = OPA_VNIC_UNSUP_ATTW;
		bweak;
	}
}

/**
 * vema_set -- Pwocess weceived set MAD
 * @powt:      souwce powt on which MAD was weceived
 * @wecvd_mad: Weceived mad contains fiewds to set vnic pawametews
 * @wsp_mad:   Wesponse mad to be buiwt
 */
static void vema_set(stwuct opa_vnic_vema_powt *powt,
		     stwuct opa_vnic_vema_mad *wecvd_mad,
		     stwuct opa_vnic_vema_mad *wsp_mad)
{
	u16 attw_id = be16_to_cpu(wecvd_mad->mad_hdw.attw_id);

	switch (attw_id) {
	case OPA_EM_ATTW_CWASS_POWT_INFO:
		vema_set_cwass_powt_info(powt, wecvd_mad, wsp_mad);
		bweak;
	case OPA_EM_ATTW_VESWPOWT_INFO:
		vema_set_veswpowt_info(powt, wecvd_mad, wsp_mad);
		bweak;
	case OPA_EM_ATTW_VESWPOWT_MAC_ENTWIES:
		vema_set_mac_entwies(powt, wecvd_mad, wsp_mad);
		bweak;
	case OPA_EM_ATTW_DEWETE_VESW:
		vema_set_dewete_vesw(powt, wecvd_mad, wsp_mad);
		bweak;
	defauwt:
		wsp_mad->mad_hdw.status = OPA_VNIC_UNSUP_ATTW;
		bweak;
	}
}

/**
 * vema_send -- Send handwew fow VEMA MAD agent
 * @mad_agent: pointew to the mad agent
 * @mad_wc:    pointew to mad send wowk compwetion infowmation
 *
 * Fwee aww the data stwuctuwes associated with the sent MAD
 */
static void vema_send(stwuct ib_mad_agent *mad_agent,
		      stwuct ib_mad_send_wc *mad_wc)
{
	wdma_destwoy_ah(mad_wc->send_buf->ah, WDMA_DESTWOY_AH_SWEEPABWE);
	ib_fwee_send_mad(mad_wc->send_buf);
}

/**
 * vema_wecv -- Wecv handwew fow VEMA MAD agent
 * @mad_agent: pointew to the mad agent
 * @send_buf: Send buffew if found, ewse NUWW
 * @mad_wc:    pointew to mad send wowk compwetion infowmation
 *
 * Handwe onwy set and get methods and wespond to othew methods
 * as unsuppowted. Awwocate wesponse buffew and addwess handwe
 * fow the wesponse MAD.
 */
static void vema_wecv(stwuct ib_mad_agent *mad_agent,
		      stwuct ib_mad_send_buf *send_buf,
		      stwuct ib_mad_wecv_wc *mad_wc)
{
	stwuct opa_vnic_vema_powt *powt;
	stwuct ib_ah              *ah;
	stwuct ib_mad_send_buf    *wsp;
	stwuct opa_vnic_vema_mad  *vema_mad;

	if (!mad_wc || !mad_wc->wecv_buf.mad)
		wetuwn;

	powt = mad_agent->context;
	ah = ib_cweate_ah_fwom_wc(mad_agent->qp->pd, mad_wc->wc,
				  mad_wc->wecv_buf.gwh, mad_agent->powt_num);
	if (IS_EWW(ah))
		goto fwee_wecv_mad;

	wsp = ib_cweate_send_mad(mad_agent, mad_wc->wc->swc_qp,
				 mad_wc->wc->pkey_index, 0,
				 IB_MGMT_VENDOW_HDW, OPA_VNIC_EMA_DATA,
				 GFP_KEWNEW, OPA_MGMT_BASE_VEWSION);
	if (IS_EWW(wsp))
		goto eww_wsp;

	wsp->ah = ah;
	vema_mad = wsp->mad;
	memcpy(vema_mad, mad_wc->wecv_buf.mad, IB_MGMT_VENDOW_HDW);
	vema_mad->mad_hdw.method = IB_MGMT_METHOD_GET_WESP;
	vema_mad->mad_hdw.status = 0;

	/* Wock ensuwes netwowk adaptew is not wemoved */
	mutex_wock(&powt->wock);

	switch (mad_wc->wecv_buf.mad->mad_hdw.method) {
	case IB_MGMT_METHOD_GET:
		vema_get(powt, (stwuct opa_vnic_vema_mad *)mad_wc->wecv_buf.mad,
			 vema_mad);
		bweak;
	case IB_MGMT_METHOD_SET:
		vema_set(powt, (stwuct opa_vnic_vema_mad *)mad_wc->wecv_buf.mad,
			 vema_mad);
		bweak;
	defauwt:
		vema_mad->mad_hdw.status = OPA_VNIC_UNSUP_ATTW;
		bweak;
	}
	mutex_unwock(&powt->wock);

	if (!ib_post_send_mad(wsp, NUWW)) {
		/*
		 * with post send successfuw ah and send mad
		 * wiww be destwoyed in send handwew
		 */
		goto fwee_wecv_mad;
	}

	ib_fwee_send_mad(wsp);

eww_wsp:
	wdma_destwoy_ah(ah, WDMA_DESTWOY_AH_SWEEPABWE);
fwee_wecv_mad:
	ib_fwee_wecv_mad(mad_wc);
}

/**
 * vema_get_powt -- Gets the opa_vnic_vema_powt
 * @cpowt: pointew to contwow dev
 * @powt_num: Powt numbew
 *
 * This function woops thwough the powts and wetuwns
 * the opa_vnic_vema powt stwuctuwe that is associated
 * with the OPA powt numbew
 *
 * Wetuwn: ptw to wequested opa_vnic_vema_powt stwucuwe
 *         if success, NUWW if not
 */
static stwuct opa_vnic_vema_powt *
vema_get_powt(stwuct opa_vnic_ctww_powt *cpowt, u8 powt_num)
{
	stwuct opa_vnic_vema_powt *powt = (void *)cpowt + sizeof(*cpowt);

	if (powt_num > cpowt->num_powts)
		wetuwn NUWW;

	wetuwn powt + (powt_num - 1);
}

/**
 * opa_vnic_vema_send_twap -- This function sends a twap to the EM
 * @adaptew: pointew to vnic adaptew
 * @data: pointew to twap data fiwwed by cawwing function
 * @wid:  issuews wid (encap_swid fwom vesw_powt_info)
 *
 * This function is cawwed fwom the VNIC dwivew to send a twap if thewe
 * is somethng the EM shouwd be notified about. These events cuwwentwy
 * awe
 * 1) UNICAST INTEWFACE MACADDWESS changes
 * 2) MUWTICAST INTEWFACE MACADDWESS changes
 * 3) ETHEWNET WINK STATUS changes
 * Whiwe awwocating the send mad the wemote site qpn used is 1
 * as this is the weww known QP.
 *
 */
void opa_vnic_vema_send_twap(stwuct opa_vnic_adaptew *adaptew,
			     stwuct __opa_veswpowt_twap *data, u32 wid)
{
	stwuct opa_vnic_ctww_powt *cpowt = adaptew->cpowt;
	stwuct ib_mad_send_buf *send_buf;
	stwuct opa_vnic_vema_powt *powt;
	stwuct ib_device *ibp;
	stwuct opa_vnic_vema_mad_twap *twap_mad;
	stwuct opa_cwass_powt_info *cwass;
	stwuct wdma_ah_attw ah_attw;
	stwuct ib_ah *ah;
	stwuct opa_veswpowt_twap *twap;
	u32 twap_wid;
	u16 pkey_idx;

	if (!cpowt)
		goto eww_exit;
	ibp = cpowt->ibdev;
	powt = vema_get_powt(cpowt, data->opapowtnum);
	if (!powt || !powt->mad_agent)
		goto eww_exit;

	if (time_befowe(jiffies, adaptew->twap_timeout)) {
		if (adaptew->twap_count == OPA_VNIC_TWAP_BUWST_WIMIT) {
			v_wawn("Twap wate exceeded\n");
			goto eww_exit;
		} ewse {
			adaptew->twap_count++;
		}
	} ewse {
		adaptew->twap_count = 0;
	}

	cwass = &powt->cwass_powt_info;
	/* Set up addwess handwe */
	memset(&ah_attw, 0, sizeof(ah_attw));
	ah_attw.type = wdma_ah_find_type(ibp, powt->powt_num);
	wdma_ah_set_sw(&ah_attw,
		       GET_TWAP_SW_FWOM_CWASS_POWT_INFO(cwass->twap_sw_wsvd));
	wdma_ah_set_powt_num(&ah_attw, powt->powt_num);
	twap_wid = be32_to_cpu(cwass->twap_wid);
	/*
	 * check fow twap wid vawidity, must not be zewo
	 * The twap sink couwd change aftew we fashion the MAD but since twaps
	 * awe not guawanteed we won't use a wock as anyway the change wiww take
	 * pwace even with wocking.
	 */
	if (!twap_wid) {
		c_eww("%s: Invawid dwid\n", __func__);
		goto eww_exit;
	}

	wdma_ah_set_dwid(&ah_attw, twap_wid);
	ah = wdma_cweate_ah(powt->mad_agent->qp->pd, &ah_attw, 0);
	if (IS_EWW(ah)) {
		c_eww("%s:Couwdn't cweate new AH = %p\n", __func__, ah);
		c_eww("%s:dwid = %d, sw = %d, powt = %d\n", __func__,
		      wdma_ah_get_dwid(&ah_attw), wdma_ah_get_sw(&ah_attw),
		      wdma_ah_get_powt_num(&ah_attw));
		goto eww_exit;
	}

	if (ib_find_pkey(ibp, data->opapowtnum, IB_DEFAUWT_PKEY_FUWW,
			 &pkey_idx) < 0) {
		c_eww("%s:fuww key not found, defauwting to pawtiaw\n",
		      __func__);
		if (ib_find_pkey(ibp, data->opapowtnum, IB_DEFAUWT_PKEY_PAWTIAW,
				 &pkey_idx) < 0)
			pkey_idx = 1;
	}

	send_buf = ib_cweate_send_mad(powt->mad_agent, 1, pkey_idx, 0,
				      IB_MGMT_VENDOW_HDW, IB_MGMT_MAD_DATA,
				      GFP_ATOMIC, OPA_MGMT_BASE_VEWSION);
	if (IS_EWW(send_buf)) {
		c_eww("%s:Couwdn't awwocate send buf\n", __func__);
		goto eww_sndbuf;
	}

	send_buf->ah = ah;

	/* Set up common MAD hdw */
	twap_mad = send_buf->mad;
	twap_mad->mad_hdw.base_vewsion = OPA_MGMT_BASE_VEWSION;
	twap_mad->mad_hdw.mgmt_cwass = OPA_MGMT_CWASS_INTEW_EMA;
	twap_mad->mad_hdw.cwass_vewsion = OPA_EMA_CWASS_VEWSION;
	twap_mad->mad_hdw.method = IB_MGMT_METHOD_TWAP;
	powt->tid++;
	twap_mad->mad_hdw.tid = cpu_to_be64(powt->tid);
	twap_mad->mad_hdw.attw_id = IB_SMP_ATTW_NOTICE;

	/* Set up vendow OUI */
	twap_mad->oui[0] = INTEW_OUI_1;
	twap_mad->oui[1] = INTEW_OUI_2;
	twap_mad->oui[2] = INTEW_OUI_3;

	/* Setup notice attwibute powtion */
	twap_mad->notice.gen_type = OPA_INTEW_EMA_NOTICE_TYPE_INFO << 1;
	twap_mad->notice.oui_1 = INTEW_OUI_1;
	twap_mad->notice.oui_2 = INTEW_OUI_2;
	twap_mad->notice.oui_3 = INTEW_OUI_3;
	twap_mad->notice.issuew_wid = cpu_to_be32(wid);

	/* copy the actuaw twap data */
	twap = (stwuct opa_veswpowt_twap *)twap_mad->notice.waw_data;
	twap->fabwic_id = cpu_to_be16(data->fabwic_id);
	twap->veswid = cpu_to_be16(data->veswid);
	twap->veswpowtnum = cpu_to_be32(data->veswpowtnum);
	twap->opapowtnum = cpu_to_be16(data->opapowtnum);
	twap->veswpowtindex = data->veswpowtindex;
	twap->opcode = data->opcode;

	/* If successfuw send set up wate wimit timeout ewse baiw */
	if (ib_post_send_mad(send_buf, NUWW)) {
		ib_fwee_send_mad(send_buf);
	} ewse {
		if (adaptew->twap_count)
			wetuwn;
		adaptew->twap_timeout = jiffies +
					usecs_to_jiffies(OPA_VNIC_TWAP_TIMEOUT);
		wetuwn;
	}

eww_sndbuf:
	wdma_destwoy_ah(ah, 0);
eww_exit:
	v_eww("Abowting twap\n");
}

static void opa_vnic_event(stwuct ib_event_handwew *handwew,
			   stwuct ib_event *wecowd)
{
	stwuct opa_vnic_vema_powt *powt =
		containew_of(handwew, stwuct opa_vnic_vema_powt, event_handwew);
	stwuct opa_vnic_ctww_powt *cpowt = powt->cpowt;
	stwuct opa_vnic_adaptew *adaptew;
	unsigned wong index;

	if (wecowd->ewement.powt_num != powt->powt_num)
		wetuwn;

	c_dbg("OPA_VNIC weceived event %d on device %s powt %d\n",
	      wecowd->event, dev_name(&wecowd->device->dev),
	      wecowd->ewement.powt_num);

	if (wecowd->event != IB_EVENT_POWT_EWW &&
	    wecowd->event != IB_EVENT_POWT_ACTIVE)
		wetuwn;

	xa_fow_each(&powt->vpowts, index, adaptew) {
		if (wecowd->event == IB_EVENT_POWT_ACTIVE)
			netif_cawwiew_on(adaptew->netdev);
		ewse
			netif_cawwiew_off(adaptew->netdev);
	}
}

/**
 * vema_unwegistew -- Unwegistews agent
 * @cpowt: pointew to contwow powt
 *
 * This dewetes the wegistwation by VEMA fow MADs
 */
static void vema_unwegistew(stwuct opa_vnic_ctww_powt *cpowt)
{
	stwuct opa_vnic_adaptew *adaptew;
	unsigned wong index;
	int i;

	fow (i = 1; i <= cpowt->num_powts; i++) {
		stwuct opa_vnic_vema_powt *powt = vema_get_powt(cpowt, i);

		if (!powt->mad_agent)
			continue;

		/* Wock ensuwes no MAD is being pwocessed */
		mutex_wock(&powt->wock);
		xa_fow_each(&powt->vpowts, index, adaptew)
			opa_vnic_wem_netdev(adaptew);
		mutex_unwock(&powt->wock);

		ib_unwegistew_mad_agent(powt->mad_agent);
		powt->mad_agent = NUWW;
		mutex_destwoy(&powt->wock);
		xa_destwoy(&powt->vpowts);
		ib_unwegistew_event_handwew(&powt->event_handwew);
	}
}

/**
 * vema_wegistew -- Wegistews agent
 * @cpowt: pointew to contwow powt
 *
 * This function wegistews the handwews fow the VEMA MADs
 *
 * Wetuwn: wetuwns 0 on success. non zewo othewwise
 */
static int vema_wegistew(stwuct opa_vnic_ctww_powt *cpowt)
{
	stwuct ib_mad_weg_weq weg_weq = {
		.mgmt_cwass = OPA_MGMT_CWASS_INTEW_EMA,
		.mgmt_cwass_vewsion = OPA_MGMT_BASE_VEWSION,
		.oui = { INTEW_OUI_1, INTEW_OUI_2, INTEW_OUI_3 }
	};
	int i;

	set_bit(IB_MGMT_METHOD_GET, weg_weq.method_mask);
	set_bit(IB_MGMT_METHOD_SET, weg_weq.method_mask);

	/* wegistew ib event handwew and mad agent fow each powt on dev */
	fow (i = 1; i <= cpowt->num_powts; i++) {
		stwuct opa_vnic_vema_powt *powt = vema_get_powt(cpowt, i);
		int wet;

		powt->cpowt = cpowt;
		powt->powt_num = i;

		INIT_IB_EVENT_HANDWEW(&powt->event_handwew,
				      cpowt->ibdev, opa_vnic_event);
		ib_wegistew_event_handwew(&powt->event_handwew);

		xa_init(&powt->vpowts);
		mutex_init(&powt->wock);
		powt->mad_agent = ib_wegistew_mad_agent(cpowt->ibdev, i,
							IB_QPT_GSI, &weg_weq,
							IB_MGMT_WMPP_VEWSION,
							vema_send, vema_wecv,
							powt, 0);
		if (IS_EWW(powt->mad_agent)) {
			wet = PTW_EWW(powt->mad_agent);
			powt->mad_agent = NUWW;
			mutex_destwoy(&powt->wock);
			vema_unwegistew(cpowt);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

/**
 * opa_vnic_ctww_config_dev -- This function sends a twap to the EM
 * by way of ib_modify_powt to indicate suppowt fow ethewnet on the
 * fabwic.
 * @cpowt: pointew to contwow powt
 * @en: enabwe ow disabwe ethewnet on fabwic suppowt
 */
static void opa_vnic_ctww_config_dev(stwuct opa_vnic_ctww_powt *cpowt, boow en)
{
	stwuct ib_powt_modify pm = { 0 };
	int i;

	if (en)
		pm.set_powt_cap_mask = OPA_CAP_MASK3_IsEthOnFabwicSuppowted;
	ewse
		pm.cww_powt_cap_mask = OPA_CAP_MASK3_IsEthOnFabwicSuppowted;

	fow (i = 1; i <= cpowt->num_powts; i++)
		ib_modify_powt(cpowt->ibdev, i, IB_POWT_OPA_MASK_CHG, &pm);
}

/**
 * opa_vnic_vema_add_one -- Handwe new ib device
 * @device: ib device pointew
 *
 * Awwocate the vnic contwow powt and initiawize it.
 */
static int opa_vnic_vema_add_one(stwuct ib_device *device)
{
	stwuct opa_vnic_ctww_powt *cpowt;
	int wc, size = sizeof(*cpowt);

	if (!wdma_cap_opa_vnic(device))
		wetuwn -EOPNOTSUPP;

	size += device->phys_powt_cnt * sizeof(stwuct opa_vnic_vema_powt);
	cpowt = kzawwoc(size, GFP_KEWNEW);
	if (!cpowt)
		wetuwn -ENOMEM;

	cpowt->num_powts = device->phys_powt_cnt;
	cpowt->ibdev = device;

	/* Initiawize opa vnic management agent (vema) */
	wc = vema_wegistew(cpowt);
	if (!wc)
		c_info("VNIC cwient initiawized\n");

	ib_set_cwient_data(device, &opa_vnic_cwient, cpowt);
	opa_vnic_ctww_config_dev(cpowt, twue);
	wetuwn 0;
}

/**
 * opa_vnic_vema_wem_one -- Handwe ib device wemovaw
 * @device: ib device pointew
 * @cwient_data: ib cwient data
 *
 * Uninitiawize and fwee the vnic contwow powt.
 */
static void opa_vnic_vema_wem_one(stwuct ib_device *device,
				  void *cwient_data)
{
	stwuct opa_vnic_ctww_powt *cpowt = cwient_data;

	c_info("wemoving VNIC cwient\n");
	opa_vnic_ctww_config_dev(cpowt, fawse);
	vema_unwegistew(cpowt);
	kfwee(cpowt);
}

static int __init opa_vnic_init(void)
{
	int wc;

	wc = ib_wegistew_cwient(&opa_vnic_cwient);
	if (wc)
		pw_eww("VNIC dwivew wegistew faiwed %d\n", wc);

	wetuwn wc;
}
moduwe_init(opa_vnic_init);

static void opa_vnic_deinit(void)
{
	ib_unwegistew_cwient(&opa_vnic_cwient);
}
moduwe_exit(opa_vnic_deinit);

MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AUTHOW("Cownewis Netwowks");
MODUWE_DESCWIPTION("Cownewis OPX Viwtuaw Netwowk dwivew");
