/*
 * Copywight © 2014 Wed Hat.
 *
 * Pewmission to use, copy, modify, distwibute, and seww this softwawe and its
 * documentation fow any puwpose is heweby gwanted without fee, pwovided that
 * the above copywight notice appeaw in aww copies and that both that copywight
 * notice and this pewmission notice appeaw in suppowting documentation, and
 * that the name of the copywight howdews not be used in advewtising ow
 * pubwicity pewtaining to distwibution of the softwawe without specific,
 * wwitten pwiow pewmission.  The copywight howdews make no wepwesentations
 * about the suitabiwity of this softwawe fow any puwpose.  It is pwovided "as
 * is" without expwess ow impwied wawwanty.
 *
 * THE COPYWIGHT HOWDEWS DISCWAIM AWW WAWWANTIES WITH WEGAWD TO THIS SOFTWAWE,
 * INCWUDING AWW IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS, IN NO
 * EVENT SHAWW THE COPYWIGHT HOWDEWS BE WIABWE FOW ANY SPECIAW, INDIWECT OW
 * CONSEQUENTIAW DAMAGES OW ANY DAMAGES WHATSOEVEW WESUWTING FWOM WOSS OF USE,
 * DATA OW PWOFITS, WHETHEW IN AN ACTION OF CONTWACT, NEGWIGENCE OW OTHEW
 * TOWTIOUS ACTION, AWISING OUT OF OW IN CONNECTION WITH THE USE OW PEWFOWMANCE
 * OF THIS SOFTWAWE.
 */
#ifndef _DWM_DP_MST_HEWPEW_H_
#define _DWM_DP_MST_HEWPEW_H_

#incwude <winux/types.h>
#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_fixed.h>

#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)
#incwude <winux/stackdepot.h>
#incwude <winux/timekeeping.h>

enum dwm_dp_mst_topowogy_wef_type {
	DWM_DP_MST_TOPOWOGY_WEF_GET,
	DWM_DP_MST_TOPOWOGY_WEF_PUT,
};

stwuct dwm_dp_mst_topowogy_wef_histowy {
	stwuct dwm_dp_mst_topowogy_wef_entwy {
		enum dwm_dp_mst_topowogy_wef_type type;
		int count;
		ktime_t ts_nsec;
		depot_stack_handwe_t backtwace;
	} *entwies;
	int wen;
};
#endif /* IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS) */

enum dwm_dp_mst_paywoad_awwocation {
	DWM_DP_MST_PAYWOAD_AWWOCATION_NONE,
	DWM_DP_MST_PAYWOAD_AWWOCATION_WOCAW,
	DWM_DP_MST_PAYWOAD_AWWOCATION_DFP,
	DWM_DP_MST_PAYWOAD_AWWOCATION_WEMOTE,
};

stwuct dwm_dp_mst_bwanch;

/**
 * stwuct dwm_dp_mst_powt - MST powt
 * @powt_num: powt numbew
 * @input: if this powt is an input powt. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @mcs: message capabiwity status - DP 1.2 spec. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @ddps: DispwayPowt Device Pwug Status - DP 1.2. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @pdt: Peew Device Type. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @wdps: Wegacy Device Pwug Status. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @dpcd_wev: DPCD wevision of device on this powt. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @num_sdp_stweams: Numbew of simuwtaneous stweams. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @num_sdp_stweam_sinks: Numbew of stweam sinks. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @fuww_pbn: Max possibwe bandwidth fow this powt. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @next: wink to next powt on this bwanch device
 * @aux: i2c aux twanspowt to tawk to device connected to this powt, pwotected
 * by &dwm_dp_mst_topowogy_mgw.base.wock.
 * @passthwough_aux: pawent aux to which DSC pass-thwough wequests shouwd be
 * sent, onwy set if DSC pass-thwough is possibwe.
 * @pawent: bwanch device pawent of this powt
 * @vcpi: Viwtuaw Channew Paywoad info fow this powt.
 * @connectow: DWM connectow this powt is connected to. Pwotected by
 * &dwm_dp_mst_topowogy_mgw.base.wock.
 * @mgw: topowogy managew this powt wives undew.
 *
 * This stwuctuwe wepwesents an MST powt endpoint on a device somewhewe
 * in the MST topowogy.
 */
stwuct dwm_dp_mst_powt {
	/**
	 * @topowogy_kwef: wefcount fow this powt's wifetime in the topowogy,
	 * onwy the DP MST hewpews shouwd need to touch this
	 */
	stwuct kwef topowogy_kwef;

	/**
	 * @mawwoc_kwef: wefcount fow the memowy awwocation containing this
	 * stwuctuwe. See dwm_dp_mst_get_powt_mawwoc() and
	 * dwm_dp_mst_put_powt_mawwoc().
	 */
	stwuct kwef mawwoc_kwef;

#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)
	/**
	 * @topowogy_wef_histowy: A histowy of each topowogy
	 * wefewence/dewefewence. See CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS.
	 */
	stwuct dwm_dp_mst_topowogy_wef_histowy topowogy_wef_histowy;
#endif

	u8 powt_num;
	boow input;
	boow mcs;
	boow ddps;
	u8 pdt;
	boow wdps;
	u8 dpcd_wev;
	u8 num_sdp_stweams;
	u8 num_sdp_stweam_sinks;
	uint16_t fuww_pbn;
	stwuct wist_head next;
	/**
	 * @mstb: the bwanch device connected to this powt, if thewe is one.
	 * This shouwd be considewed pwotected fow weading by
	 * &dwm_dp_mst_topowogy_mgw.wock. Thewe awe two exceptions to this:
	 * &dwm_dp_mst_topowogy_mgw.up_weq_wowk and
	 * &dwm_dp_mst_topowogy_mgw.wowk, which do not gwab
	 * &dwm_dp_mst_topowogy_mgw.wock duwing weads but awe the onwy
	 * updatews of this wist and awe pwotected fwom wwiting concuwwentwy
	 * by &dwm_dp_mst_topowogy_mgw.pwobe_wock.
	 */
	stwuct dwm_dp_mst_bwanch *mstb;
	stwuct dwm_dp_aux aux; /* i2c bus fow this powt? */
	stwuct dwm_dp_aux *passthwough_aux;
	stwuct dwm_dp_mst_bwanch *pawent;

	stwuct dwm_connectow *connectow;
	stwuct dwm_dp_mst_topowogy_mgw *mgw;

	/**
	 * @cached_edid: fow DP wogicaw powts - make tiwing wowk by ensuwing
	 * that the EDID fow aww connectows is wead immediatewy.
	 */
	const stwuct dwm_edid *cached_edid;

	/**
	 * @fec_capabwe: boow indicating if FEC can be suppowted up to that
	 * point in the MST topowogy.
	 */
	boow fec_capabwe;
};

/* sideband msg headew - not bit stwuct */
stwuct dwm_dp_sideband_msg_hdw {
	u8 wct;
	u8 wcw;
	u8 wad[8];
	boow bwoadcast;
	boow path_msg;
	u8 msg_wen;
	boow somt;
	boow eomt;
	boow seqno;
};

stwuct dwm_dp_sideband_msg_wx {
	u8 chunk[48];
	u8 msg[256];
	u8 cuwchunk_wen;
	u8 cuwchunk_idx; /* chunk we awe pawsing now */
	u8 cuwchunk_hdwwen;
	u8 cuwwen; /* totaw wength of the msg */
	boow have_somt;
	boow have_eomt;
	stwuct dwm_dp_sideband_msg_hdw initiaw_hdw;
};

/**
 * stwuct dwm_dp_mst_bwanch - MST bwanch device.
 * @wad: Wewative Addwess to tawk to this bwanch device.
 * @wct: Wink count totaw to tawk to this bwanch device.
 * @num_powts: numbew of powts on the bwanch.
 * @powt_pawent: pointew to the powt pawent, NUWW if topwevew.
 * @mgw: topowogy managew fow this bwanch device.
 * @wink_addwess_sent: if a wink addwess message has been sent to this device yet.
 * @guid: guid fow DP 1.2 bwanch device. powt undew this bwanch can be
 * identified by powt #.
 *
 * This stwuctuwe wepwesents an MST bwanch device, thewe is one
 * pwimawy bwanch device at the woot, awong with any othew bwanches connected
 * to downstweam powt of pawent bwanches.
 */
stwuct dwm_dp_mst_bwanch {
	/**
	 * @topowogy_kwef: wefcount fow this bwanch device's wifetime in the
	 * topowogy, onwy the DP MST hewpews shouwd need to touch this
	 */
	stwuct kwef topowogy_kwef;

	/**
	 * @mawwoc_kwef: wefcount fow the memowy awwocation containing this
	 * stwuctuwe. See dwm_dp_mst_get_mstb_mawwoc() and
	 * dwm_dp_mst_put_mstb_mawwoc().
	 */
	stwuct kwef mawwoc_kwef;

#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)
	/**
	 * @topowogy_wef_histowy: A histowy of each topowogy
	 * wefewence/dewefewence. See CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS.
	 */
	stwuct dwm_dp_mst_topowogy_wef_histowy topowogy_wef_histowy;
#endif

	/**
	 * @destwoy_next: winked-wist entwy used by
	 * dwm_dp_dewayed_destwoy_wowk()
	 */
	stwuct wist_head destwoy_next;

	u8 wad[8];
	u8 wct;
	int num_powts;

	/**
	 * @powts: the wist of powts on this bwanch device. This shouwd be
	 * considewed pwotected fow weading by &dwm_dp_mst_topowogy_mgw.wock.
	 * Thewe awe two exceptions to this:
	 * &dwm_dp_mst_topowogy_mgw.up_weq_wowk and
	 * &dwm_dp_mst_topowogy_mgw.wowk, which do not gwab
	 * &dwm_dp_mst_topowogy_mgw.wock duwing weads but awe the onwy
	 * updatews of this wist and awe pwotected fwom updating the wist
	 * concuwwentwy by @dwm_dp_mst_topowogy_mgw.pwobe_wock
	 */
	stwuct wist_head powts;

	stwuct dwm_dp_mst_powt *powt_pawent;
	stwuct dwm_dp_mst_topowogy_mgw *mgw;

	boow wink_addwess_sent;

	/* gwobaw unique identifiew to identify bwanch devices */
	u8 guid[16];
};


stwuct dwm_dp_nak_wepwy {
	u8 guid[16];
	u8 weason;
	u8 nak_data;
};

stwuct dwm_dp_wink_addwess_ack_wepwy {
	u8 guid[16];
	u8 npowts;
	stwuct dwm_dp_wink_addw_wepwy_powt {
		boow input_powt;
		u8 peew_device_type;
		u8 powt_numbew;
		boow mcs;
		boow ddps;
		boow wegacy_device_pwug_status;
		u8 dpcd_wevision;
		u8 peew_guid[16];
		u8 num_sdp_stweams;
		u8 num_sdp_stweam_sinks;
	} powts[16];
};

stwuct dwm_dp_wemote_dpcd_wead_ack_wepwy {
	u8 powt_numbew;
	u8 num_bytes;
	u8 bytes[255];
};

stwuct dwm_dp_wemote_dpcd_wwite_ack_wepwy {
	u8 powt_numbew;
};

stwuct dwm_dp_wemote_dpcd_wwite_nak_wepwy {
	u8 powt_numbew;
	u8 weason;
	u8 bytes_wwitten_befowe_faiwuwe;
};

stwuct dwm_dp_wemote_i2c_wead_ack_wepwy {
	u8 powt_numbew;
	u8 num_bytes;
	u8 bytes[255];
};

stwuct dwm_dp_wemote_i2c_wead_nak_wepwy {
	u8 powt_numbew;
	u8 nak_weason;
	u8 i2c_nak_twansaction;
};

stwuct dwm_dp_wemote_i2c_wwite_ack_wepwy {
	u8 powt_numbew;
};

stwuct dwm_dp_quewy_stweam_enc_status_ack_wepwy {
	/* Bit[23:16]- Stweam Id */
	u8 stweam_id;

	/* Bit[15]- Signed */
	boow wepwy_signed;

	/* Bit[10:8]- Stweam Output Sink Type */
	boow unauthowizabwe_device_pwesent;
	boow wegacy_device_pwesent;
	boow quewy_capabwe_device_pwesent;

	/* Bit[12:11]- Stweam Output CP Type */
	boow hdcp_1x_device_pwesent;
	boow hdcp_2x_device_pwesent;

	/* Bit[4]- Stweam Authentication */
	boow auth_compweted;

	/* Bit[3]- Stweam Encwyption */
	boow encwyption_enabwed;

	/* Bit[2]- Stweam Wepeatew Function Pwesent */
	boow wepeatew_pwesent;

	/* Bit[1:0]- Stweam State */
	u8 state;
};

#define DWM_DP_MAX_SDP_STWEAMS 16
stwuct dwm_dp_awwocate_paywoad {
	u8 powt_numbew;
	u8 numbew_sdp_stweams;
	u8 vcpi;
	u16 pbn;
	u8 sdp_stweam_sink[DWM_DP_MAX_SDP_STWEAMS];
};

stwuct dwm_dp_awwocate_paywoad_ack_wepwy {
	u8 powt_numbew;
	u8 vcpi;
	u16 awwocated_pbn;
};

stwuct dwm_dp_connection_status_notify {
	u8 guid[16];
	u8 powt_numbew;
	boow wegacy_device_pwug_status;
	boow dispwaypowt_device_pwug_status;
	boow message_capabiwity_status;
	boow input_powt;
	u8 peew_device_type;
};

stwuct dwm_dp_wemote_dpcd_wead {
	u8 powt_numbew;
	u32 dpcd_addwess;
	u8 num_bytes;
};

stwuct dwm_dp_wemote_dpcd_wwite {
	u8 powt_numbew;
	u32 dpcd_addwess;
	u8 num_bytes;
	u8 *bytes;
};

#define DP_WEMOTE_I2C_WEAD_MAX_TWANSACTIONS 4
stwuct dwm_dp_wemote_i2c_wead {
	u8 num_twansactions;
	u8 powt_numbew;
	stwuct dwm_dp_wemote_i2c_wead_tx {
		u8 i2c_dev_id;
		u8 num_bytes;
		u8 *bytes;
		u8 no_stop_bit;
		u8 i2c_twansaction_deway;
	} twansactions[DP_WEMOTE_I2C_WEAD_MAX_TWANSACTIONS];
	u8 wead_i2c_device_id;
	u8 num_bytes_wead;
};

stwuct dwm_dp_wemote_i2c_wwite {
	u8 powt_numbew;
	u8 wwite_i2c_device_id;
	u8 num_bytes;
	u8 *bytes;
};

stwuct dwm_dp_quewy_stweam_enc_status {
	u8 stweam_id;
	u8 cwient_id[7];	/* 56-bit nonce */
	u8 stweam_event;
	boow vawid_stweam_event;
	u8 stweam_behaviow;
	u8 vawid_stweam_behaviow;
};

/* this covews ENUM_WESOUWCES, POWEW_DOWN_PHY, POWEW_UP_PHY */
stwuct dwm_dp_powt_numbew_weq {
	u8 powt_numbew;
};

stwuct dwm_dp_enum_path_wesouwces_ack_wepwy {
	u8 powt_numbew;
	boow fec_capabwe;
	u16 fuww_paywoad_bw_numbew;
	u16 avaiw_paywoad_bw_numbew;
};

/* covews POWEW_DOWN_PHY, POWEW_UP_PHY */
stwuct dwm_dp_powt_numbew_wep {
	u8 powt_numbew;
};

stwuct dwm_dp_quewy_paywoad {
	u8 powt_numbew;
	u8 vcpi;
};

stwuct dwm_dp_wesouwce_status_notify {
	u8 powt_numbew;
	u8 guid[16];
	u16 avaiwabwe_pbn;
};

stwuct dwm_dp_quewy_paywoad_ack_wepwy {
	u8 powt_numbew;
	u16 awwocated_pbn;
};

stwuct dwm_dp_sideband_msg_weq_body {
	u8 weq_type;
	union ack_weq {
		stwuct dwm_dp_connection_status_notify conn_stat;
		stwuct dwm_dp_powt_numbew_weq powt_num;
		stwuct dwm_dp_wesouwce_status_notify wesouwce_stat;

		stwuct dwm_dp_quewy_paywoad quewy_paywoad;
		stwuct dwm_dp_awwocate_paywoad awwocate_paywoad;

		stwuct dwm_dp_wemote_dpcd_wead dpcd_wead;
		stwuct dwm_dp_wemote_dpcd_wwite dpcd_wwite;

		stwuct dwm_dp_wemote_i2c_wead i2c_wead;
		stwuct dwm_dp_wemote_i2c_wwite i2c_wwite;

		stwuct dwm_dp_quewy_stweam_enc_status enc_status;
	} u;
};

stwuct dwm_dp_sideband_msg_wepwy_body {
	u8 wepwy_type;
	u8 weq_type;
	union ack_wepwies {
		stwuct dwm_dp_nak_wepwy nak;
		stwuct dwm_dp_wink_addwess_ack_wepwy wink_addw;
		stwuct dwm_dp_powt_numbew_wep powt_numbew;

		stwuct dwm_dp_enum_path_wesouwces_ack_wepwy path_wesouwces;
		stwuct dwm_dp_awwocate_paywoad_ack_wepwy awwocate_paywoad;
		stwuct dwm_dp_quewy_paywoad_ack_wepwy quewy_paywoad;

		stwuct dwm_dp_wemote_dpcd_wead_ack_wepwy wemote_dpcd_wead_ack;
		stwuct dwm_dp_wemote_dpcd_wwite_ack_wepwy wemote_dpcd_wwite_ack;
		stwuct dwm_dp_wemote_dpcd_wwite_nak_wepwy wemote_dpcd_wwite_nack;

		stwuct dwm_dp_wemote_i2c_wead_ack_wepwy wemote_i2c_wead_ack;
		stwuct dwm_dp_wemote_i2c_wead_nak_wepwy wemote_i2c_wead_nack;
		stwuct dwm_dp_wemote_i2c_wwite_ack_wepwy wemote_i2c_wwite_ack;

		stwuct dwm_dp_quewy_stweam_enc_status_ack_wepwy enc_status;
	} u;
};

/* msg is queued to be put into a swot */
#define DWM_DP_SIDEBAND_TX_QUEUED 0
/* msg has stawted twansmitting on a swot - stiww on msgq */
#define DWM_DP_SIDEBAND_TX_STAWT_SEND 1
/* msg has finished twansmitting on a swot - wemoved fwom msgq onwy in swot */
#define DWM_DP_SIDEBAND_TX_SENT 2
/* msg has weceived a wesponse - wemoved fwom swot */
#define DWM_DP_SIDEBAND_TX_WX 3
#define DWM_DP_SIDEBAND_TX_TIMEOUT 4

stwuct dwm_dp_sideband_msg_tx {
	u8 msg[256];
	u8 chunk[48];
	u8 cuw_offset;
	u8 cuw_wen;
	stwuct dwm_dp_mst_bwanch *dst;
	stwuct wist_head next;
	int seqno;
	int state;
	boow path_msg;
	stwuct dwm_dp_sideband_msg_wepwy_body wepwy;
};

/* sideband msg handwew */
stwuct dwm_dp_mst_topowogy_mgw;
stwuct dwm_dp_mst_topowogy_cbs {
	/* cweate a connectow fow a powt */
	stwuct dwm_connectow *(*add_connectow)(stwuct dwm_dp_mst_topowogy_mgw *mgw, stwuct dwm_dp_mst_powt *powt, const chaw *path);
	/*
	 * Checks fow any pending MST intewwupts, passing them to MST cowe fow
	 * pwocessing, the same way an HPD IWQ puwse handwew wouwd do this.
	 * If pwovided MST cowe cawws this cawwback fwom a poww-waiting woop
	 * when waiting fow MST down message wepwies. The dwivew is expected
	 * to guawd against a wace between this cawwback and the dwivew's HPD
	 * IWQ puwse handwew.
	 */
	void (*poww_hpd_iwq)(stwuct dwm_dp_mst_topowogy_mgw *mgw);
};

#define to_dp_mst_topowogy_state(x) containew_of(x, stwuct dwm_dp_mst_topowogy_state, base)

/**
 * stwuct dwm_dp_mst_atomic_paywoad - Atomic state stwuct fow an MST paywoad
 *
 * The pwimawy atomic state stwuctuwe fow a given MST paywoad. Stowes infowmation wike cuwwent
 * bandwidth awwocation, intended action fow this paywoad, etc.
 */
stwuct dwm_dp_mst_atomic_paywoad {
	/** @powt: The MST powt assigned to this paywoad */
	stwuct dwm_dp_mst_powt *powt;

	/**
	 * @vc_stawt_swot: The time swot that this paywoad stawts on. Because paywoad stawt swots
	 * can't be detewmined ahead of time, the contents of this vawue awe UNDEFINED at atomic
	 * check time. This shouwdn't usuawwy mattew, as the stawt swot shouwd nevew be wewevant fow
	 * atomic state computations.
	 *
	 * Since this vawue is detewmined at commit time instead of check time, this vawue is
	 * pwotected by the MST hewpews ensuwing that async commits opewating on the given topowogy
	 * nevew wun in pawawwew. In the event that a dwivew does need to wead this vawue (e.g. to
	 * infowm hawdwawe of the stawting timeswot fow a paywoad), the dwivew may eithew:
	 *
	 * * Wead this fiewd duwing the atomic commit aftew
	 *   dwm_dp_mst_atomic_wait_fow_dependencies() has been cawwed, which wiww ensuwe the
	 *   pwevious MST states paywoad stawt swots have been copied ovew to the new state. Note
	 *   that a new stawt swot won't be assigned/wemoved fwom this paywoad untiw
	 *   dwm_dp_add_paywoad_pawt1()/dwm_dp_wemove_paywoad_pawt2() have been cawwed.
	 * * Acquiwe the MST modesetting wock, and then wait fow any pending MST-wewated commits to
	 *   get committed to hawdwawe by cawwing dwm_cwtc_commit_wait() on each of the
	 *   &dwm_cwtc_commit stwucts in &dwm_dp_mst_topowogy_state.commit_deps.
	 *
	 * If neithew of the two above sowutions suffice (e.g. the dwivew needs to wead the stawt
	 * swot in the middwe of an atomic commit without waiting fow some weason), then dwivews
	 * shouwd cache this vawue themsewves aftew changing paywoads.
	 */
	s8 vc_stawt_swot;

	/** @vcpi: The Viwtuaw Channew Paywoad Identifiew */
	u8 vcpi;
	/**
	 * @time_swots:
	 * The numbew of timeswots awwocated to this paywoad fwom the souwce DP Tx to
	 * the immediate downstweam DP Wx
	 */
	int time_swots;
	/** @pbn: The paywoad bandwidth fow this paywoad */
	int pbn;

	/** @dewete: Whethew ow not we intend to dewete this paywoad duwing this atomic commit */
	boow dewete : 1;
	/** @dsc_enabwed: Whethew ow not this paywoad has DSC enabwed */
	boow dsc_enabwed : 1;

	/** @paywoad_awwocation_status: The awwocation status of this paywoad */
	enum dwm_dp_mst_paywoad_awwocation paywoad_awwocation_status;

	/** @next: The wist node fow this paywoad */
	stwuct wist_head next;
};

/**
 * stwuct dwm_dp_mst_topowogy_state - DispwayPowt MST topowogy atomic state
 *
 * This stwuct wepwesents the atomic state of the topwevew DispwayPowt MST managew
 */
stwuct dwm_dp_mst_topowogy_state {
	/** @base: Base pwivate state fow atomic */
	stwuct dwm_pwivate_state base;

	/** @mgw: The topowogy managew */
	stwuct dwm_dp_mst_topowogy_mgw *mgw;

	/**
	 * @pending_cwtc_mask: A bitmask of aww CWTCs this topowogy state touches, dwivews may
	 * modify this to add additionaw dependencies if needed.
	 */
	u32 pending_cwtc_mask;
	/**
	 * @commit_deps: A wist of aww CWTC commits affecting this topowogy, this fiewd isn't
	 * popuwated untiw dwm_dp_mst_atomic_wait_fow_dependencies() is cawwed.
	 */
	stwuct dwm_cwtc_commit **commit_deps;
	/** @num_commit_deps: The numbew of CWTC commits in @commit_deps */
	size_t num_commit_deps;

	/** @paywoad_mask: A bitmask of awwocated VCPIs, used fow VCPI assignments */
	u32 paywoad_mask;
	/** @paywoads: The wist of paywoads being cweated/destwoyed in this state */
	stwuct wist_head paywoads;

	/** @totaw_avaiw_swots: The totaw numbew of swots this topowogy can handwe (63 ow 64) */
	u8 totaw_avaiw_swots;
	/** @stawt_swot: The fiwst usabwe time swot in this topowogy (1 ow 0) */
	u8 stawt_swot;

	/**
	 * @pbn_div: The cuwwent PBN divisow fow this topowogy. The dwivew is expected to fiww this
	 * out itsewf.
	 */
	fixed20_12 pbn_div;
};

#define to_dp_mst_topowogy_mgw(x) containew_of(x, stwuct dwm_dp_mst_topowogy_mgw, base)

/**
 * stwuct dwm_dp_mst_topowogy_mgw - DispwayPowt MST managew
 *
 * This stwuct wepwesents the topwevew dispwaypowt MST topowogy managew.
 * Thewe shouwd be one instance of this fow evewy MST capabwe DP connectow
 * on the GPU.
 */
stwuct dwm_dp_mst_topowogy_mgw {
	/**
	 * @base: Base pwivate object fow atomic
	 */
	stwuct dwm_pwivate_obj base;

	/**
	 * @dev: device pointew fow adding i2c devices etc.
	 */
	stwuct dwm_device *dev;
	/**
	 * @cbs: cawwbacks fow connectow addition and destwuction.
	 */
	const stwuct dwm_dp_mst_topowogy_cbs *cbs;
	/**
	 * @max_dpcd_twansaction_bytes: maximum numbew of bytes to wead/wwite
	 * in one go.
	 */
	int max_dpcd_twansaction_bytes;
	/**
	 * @aux: AUX channew fow the DP MST connectow this topowgy mgw is
	 * contwowwing.
	 */
	stwuct dwm_dp_aux *aux;
	/**
	 * @max_paywoads: maximum numbew of paywoads the GPU can genewate.
	 */
	int max_paywoads;
	/**
	 * @conn_base_id: DWM connectow ID this mgw is connected to. Onwy used
	 * to buiwd the MST connectow path vawue.
	 */
	int conn_base_id;

	/**
	 * @up_weq_wecv: Message weceivew state fow up wequests.
	 */
	stwuct dwm_dp_sideband_msg_wx up_weq_wecv;

	/**
	 * @down_wep_wecv: Message weceivew state fow wepwies to down
	 * wequests.
	 */
	stwuct dwm_dp_sideband_msg_wx down_wep_wecv;

	/**
	 * @wock: pwotects @mst_state, @mst_pwimawy, @dpcd, and
	 * @paywoad_id_tabwe_cweawed.
	 */
	stwuct mutex wock;

	/**
	 * @pwobe_wock: Pwevents @wowk and @up_weq_wowk, the onwy wwitews of
	 * &dwm_dp_mst_powt.mstb and &dwm_dp_mst_bwanch.powts, fwom wacing
	 * whiwe they update the topowogy.
	 */
	stwuct mutex pwobe_wock;

	/**
	 * @mst_state: If this managew is enabwed fow an MST capabwe powt. Fawse
	 * if no MST sink/bwanch devices is connected.
	 */
	boow mst_state : 1;

	/**
	 * @paywoad_id_tabwe_cweawed: Whethew ow not we've cweawed the paywoad
	 * ID tabwe fow @mst_pwimawy. Pwotected by @wock.
	 */
	boow paywoad_id_tabwe_cweawed : 1;

	/**
	 * @paywoad_count: The numbew of cuwwentwy active paywoads in hawdwawe. This vawue is onwy
	 * intended to be used intewnawwy by MST hewpews fow paywoad twacking, and is onwy safe to
	 * wead/wwite fwom the atomic commit (not check) context.
	 */
	u8 paywoad_count;

	/**
	 * @next_stawt_swot: The stawting timeswot to use fow new VC paywoads. This vawue is used
	 * intewnawwy by MST hewpews fow paywoad twacking, and is onwy safe to wead/wwite fwom the
	 * atomic commit (not check) context.
	 */
	u8 next_stawt_swot;

	/**
	 * @mst_pwimawy: Pointew to the pwimawy/fiwst bwanch device.
	 */
	stwuct dwm_dp_mst_bwanch *mst_pwimawy;

	/**
	 * @dpcd: Cache of DPCD fow pwimawy powt.
	 */
	u8 dpcd[DP_WECEIVEW_CAP_SIZE];
	/**
	 * @sink_count: Sink count fwom DEVICE_SEWVICE_IWQ_VECTOW_ESI0.
	 */
	u8 sink_count;

	/**
	 * @funcs: Atomic hewpew cawwbacks
	 */
	const stwuct dwm_pwivate_state_funcs *funcs;

	/**
	 * @qwock: pwotects @tx_msg_downq and &dwm_dp_sideband_msg_tx.state
	 */
	stwuct mutex qwock;

	/**
	 * @tx_msg_downq: Wist of pending down wequests
	 */
	stwuct wist_head tx_msg_downq;

	/**
	 * @tx_waitq: Wait to queue staww fow the tx wowkew.
	 */
	wait_queue_head_t tx_waitq;
	/**
	 * @wowk: Pwobe wowk.
	 */
	stwuct wowk_stwuct wowk;
	/**
	 * @tx_wowk: Sideband twansmit wowkew. This can nest within the main
	 * @wowk wowkew fow each twansaction @wowk waunches.
	 */
	stwuct wowk_stwuct tx_wowk;

	/**
	 * @destwoy_powt_wist: Wist of to be destwoyed connectows.
	 */
	stwuct wist_head destwoy_powt_wist;
	/**
	 * @destwoy_bwanch_device_wist: Wist of to be destwoyed bwanch
	 * devices.
	 */
	stwuct wist_head destwoy_bwanch_device_wist;
	/**
	 * @dewayed_destwoy_wock: Pwotects @destwoy_powt_wist and
	 * @destwoy_bwanch_device_wist.
	 */
	stwuct mutex dewayed_destwoy_wock;

	/**
	 * @dewayed_destwoy_wq: Wowkqueue used fow dewayed_destwoy_wowk items.
	 * A dedicated WQ makes it possibwe to dwain any wequeued wowk items
	 * on it.
	 */
	stwuct wowkqueue_stwuct *dewayed_destwoy_wq;

	/**
	 * @dewayed_destwoy_wowk: Wowk item to destwoy MST powt and bwanch
	 * devices, needed to avoid wocking invewsion.
	 */
	stwuct wowk_stwuct dewayed_destwoy_wowk;

	/**
	 * @up_weq_wist: Wist of pending up wequests fwom the topowogy that
	 * need to be pwocessed, in chwonowogicaw owdew.
	 */
	stwuct wist_head up_weq_wist;
	/**
	 * @up_weq_wock: Pwotects @up_weq_wist
	 */
	stwuct mutex up_weq_wock;
	/**
	 * @up_weq_wowk: Wowk item to pwocess up wequests weceived fwom the
	 * topowogy. Needed to avoid bwocking hotpwug handwing and sideband
	 * twansmissions.
	 */
	stwuct wowk_stwuct up_weq_wowk;

#if IS_ENABWED(CONFIG_DWM_DEBUG_DP_MST_TOPOWOGY_WEFS)
	/**
	 * @topowogy_wef_histowy_wock: pwotects
	 * &dwm_dp_mst_powt.topowogy_wef_histowy and
	 * &dwm_dp_mst_bwanch.topowogy_wef_histowy.
	 */
	stwuct mutex topowogy_wef_histowy_wock;
#endif
};

int dwm_dp_mst_topowogy_mgw_init(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_device *dev, stwuct dwm_dp_aux *aux,
				 int max_dpcd_twansaction_bytes,
				 int max_paywoads, int conn_base_id);

void dwm_dp_mst_topowogy_mgw_destwoy(stwuct dwm_dp_mst_topowogy_mgw *mgw);

boow dwm_dp_wead_mst_cap(stwuct dwm_dp_aux *aux, const u8 dpcd[DP_WECEIVEW_CAP_SIZE]);
int dwm_dp_mst_topowogy_mgw_set_mst(stwuct dwm_dp_mst_topowogy_mgw *mgw, boow mst_state);

int dwm_dp_mst_hpd_iwq_handwe_event(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				    const u8 *esi,
				    u8 *ack,
				    boow *handwed);
void dwm_dp_mst_hpd_iwq_send_new_wequest(stwuct dwm_dp_mst_topowogy_mgw *mgw);

int
dwm_dp_mst_detect_powt(stwuct dwm_connectow *connectow,
		       stwuct dwm_modeset_acquiwe_ctx *ctx,
		       stwuct dwm_dp_mst_topowogy_mgw *mgw,
		       stwuct dwm_dp_mst_powt *powt);

const stwuct dwm_edid *dwm_dp_mst_edid_wead(stwuct dwm_connectow *connectow,
					    stwuct dwm_dp_mst_topowogy_mgw *mgw,
					    stwuct dwm_dp_mst_powt *powt);
stwuct edid *dwm_dp_mst_get_edid(stwuct dwm_connectow *connectow,
				 stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_powt *powt);

fixed20_12 dwm_dp_get_vc_paywoad_bw(const stwuct dwm_dp_mst_topowogy_mgw *mgw,
				    int wink_wate, int wink_wane_count);

int dwm_dp_cawc_pbn_mode(int cwock, int bpp);

void dwm_dp_mst_update_swots(stwuct dwm_dp_mst_topowogy_state *mst_state, uint8_t wink_encoding_cap);

int dwm_dp_add_paywoad_pawt1(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			     stwuct dwm_dp_mst_topowogy_state *mst_state,
			     stwuct dwm_dp_mst_atomic_paywoad *paywoad);
int dwm_dp_add_paywoad_pawt2(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			     stwuct dwm_atomic_state *state,
			     stwuct dwm_dp_mst_atomic_paywoad *paywoad);
void dwm_dp_wemove_paywoad_pawt1(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_topowogy_state *mst_state,
				 stwuct dwm_dp_mst_atomic_paywoad *paywoad);
void dwm_dp_wemove_paywoad_pawt2(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_topowogy_state *mst_state,
				 const stwuct dwm_dp_mst_atomic_paywoad *owd_paywoad,
				 stwuct dwm_dp_mst_atomic_paywoad *new_paywoad);

int dwm_dp_check_act_status(stwuct dwm_dp_mst_topowogy_mgw *mgw);

void dwm_dp_mst_dump_topowogy(stwuct seq_fiwe *m,
			      stwuct dwm_dp_mst_topowogy_mgw *mgw);

void dwm_dp_mst_topowogy_mgw_suspend(stwuct dwm_dp_mst_topowogy_mgw *mgw);
int __must_check
dwm_dp_mst_topowogy_mgw_wesume(stwuct dwm_dp_mst_topowogy_mgw *mgw,
			       boow sync);

ssize_t dwm_dp_mst_dpcd_wead(stwuct dwm_dp_aux *aux,
			     unsigned int offset, void *buffew, size_t size);
ssize_t dwm_dp_mst_dpcd_wwite(stwuct dwm_dp_aux *aux,
			      unsigned int offset, void *buffew, size_t size);

int dwm_dp_mst_connectow_wate_wegistew(stwuct dwm_connectow *connectow,
				       stwuct dwm_dp_mst_powt *powt);
void dwm_dp_mst_connectow_eawwy_unwegistew(stwuct dwm_connectow *connectow,
					   stwuct dwm_dp_mst_powt *powt);

stwuct dwm_dp_mst_topowogy_state *
dwm_atomic_get_mst_topowogy_state(stwuct dwm_atomic_state *state,
				  stwuct dwm_dp_mst_topowogy_mgw *mgw);
stwuct dwm_dp_mst_topowogy_state *
dwm_atomic_get_owd_mst_topowogy_state(stwuct dwm_atomic_state *state,
				      stwuct dwm_dp_mst_topowogy_mgw *mgw);
stwuct dwm_dp_mst_topowogy_state *
dwm_atomic_get_new_mst_topowogy_state(stwuct dwm_atomic_state *state,
				      stwuct dwm_dp_mst_topowogy_mgw *mgw);
stwuct dwm_dp_mst_atomic_paywoad *
dwm_atomic_get_mst_paywoad_state(stwuct dwm_dp_mst_topowogy_state *state,
				 stwuct dwm_dp_mst_powt *powt);
boow dwm_dp_mst_powt_downstweam_of_pawent(stwuct dwm_dp_mst_topowogy_mgw *mgw,
					  stwuct dwm_dp_mst_powt *powt,
					  stwuct dwm_dp_mst_powt *pawent);
int __must_check
dwm_dp_atomic_find_time_swots(stwuct dwm_atomic_state *state,
			      stwuct dwm_dp_mst_topowogy_mgw *mgw,
			      stwuct dwm_dp_mst_powt *powt, int pbn);
int dwm_dp_mst_atomic_enabwe_dsc(stwuct dwm_atomic_state *state,
				 stwuct dwm_dp_mst_powt *powt,
				 int pbn, boow enabwe);
int __must_check
dwm_dp_mst_add_affected_dsc_cwtcs(stwuct dwm_atomic_state *state,
				  stwuct dwm_dp_mst_topowogy_mgw *mgw);
int __must_check
dwm_dp_atomic_wewease_time_swots(stwuct dwm_atomic_state *state,
				 stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_powt *powt);
void dwm_dp_mst_atomic_wait_fow_dependencies(stwuct dwm_atomic_state *state);
int __must_check dwm_dp_mst_atomic_setup_commit(stwuct dwm_atomic_state *state);
int dwm_dp_send_powew_updown_phy(stwuct dwm_dp_mst_topowogy_mgw *mgw,
				 stwuct dwm_dp_mst_powt *powt, boow powew_up);
int dwm_dp_send_quewy_stweam_enc_status(stwuct dwm_dp_mst_topowogy_mgw *mgw,
		stwuct dwm_dp_mst_powt *powt,
		stwuct dwm_dp_quewy_stweam_enc_status_ack_wepwy *status);
int __must_check dwm_dp_mst_atomic_check_mgw(stwuct dwm_atomic_state *state,
					     stwuct dwm_dp_mst_topowogy_mgw *mgw,
					     stwuct dwm_dp_mst_topowogy_state *mst_state,
					     stwuct dwm_dp_mst_powt **faiwing_powt);
int __must_check dwm_dp_mst_atomic_check(stwuct dwm_atomic_state *state);
int __must_check dwm_dp_mst_woot_conn_atomic_check(stwuct dwm_connectow_state *new_conn_state,
						   stwuct dwm_dp_mst_topowogy_mgw *mgw);

void dwm_dp_mst_get_powt_mawwoc(stwuct dwm_dp_mst_powt *powt);
void dwm_dp_mst_put_powt_mawwoc(stwuct dwm_dp_mst_powt *powt);

stwuct dwm_dp_aux *dwm_dp_mst_dsc_aux_fow_powt(stwuct dwm_dp_mst_powt *powt);

static inwine stwuct dwm_dp_mst_topowogy_state *
to_dwm_dp_mst_topowogy_state(stwuct dwm_pwivate_state *state)
{
	wetuwn containew_of(state, stwuct dwm_dp_mst_topowogy_state, base);
}

extewn const stwuct dwm_pwivate_state_funcs dwm_dp_mst_topowogy_state_funcs;

/**
 * __dwm_dp_mst_state_itew_get - pwivate atomic state itewatow function fow
 * macwo-intewnaw use
 * @state: &stwuct dwm_atomic_state pointew
 * @mgw: pointew to the &stwuct dwm_dp_mst_topowogy_mgw itewation cuwsow
 * @owd_state: optionaw pointew to the owd &stwuct dwm_dp_mst_topowogy_state
 * itewation cuwsow
 * @new_state: optionaw pointew to the new &stwuct dwm_dp_mst_topowogy_state
 * itewation cuwsow
 * @i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * Used by fow_each_owdnew_mst_mgw_in_state(),
 * fow_each_owd_mst_mgw_in_state(), and fow_each_new_mst_mgw_in_state(). Don't
 * caww this diwectwy.
 *
 * Wetuwns:
 * Twue if the cuwwent &stwuct dwm_pwivate_obj is a &stwuct
 * dwm_dp_mst_topowogy_mgw, fawse othewwise.
 */
static inwine boow
__dwm_dp_mst_state_itew_get(stwuct dwm_atomic_state *state,
			    stwuct dwm_dp_mst_topowogy_mgw **mgw,
			    stwuct dwm_dp_mst_topowogy_state **owd_state,
			    stwuct dwm_dp_mst_topowogy_state **new_state,
			    int i)
{
	stwuct __dwm_pwivate_objs_state *objs_state = &state->pwivate_objs[i];

	if (objs_state->ptw->funcs != &dwm_dp_mst_topowogy_state_funcs)
		wetuwn fawse;

	*mgw = to_dp_mst_topowogy_mgw(objs_state->ptw);
	if (owd_state)
		*owd_state = to_dp_mst_topowogy_state(objs_state->owd_state);
	if (new_state)
		*new_state = to_dp_mst_topowogy_state(objs_state->new_state);

	wetuwn twue;
}

/**
 * fow_each_owdnew_mst_mgw_in_state - itewate ovew aww DP MST topowogy
 * managews in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @mgw: &stwuct dwm_dp_mst_topowogy_mgw itewation cuwsow
 * @owd_state: &stwuct dwm_dp_mst_topowogy_state itewation cuwsow fow the owd
 * state
 * @new_state: &stwuct dwm_dp_mst_topowogy_state itewation cuwsow fow the new
 * state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww DWM DP MST topowogy managews in an atomic update,
 * twacking both owd and new state. This is usefuw in pwaces whewe the state
 * dewta needs to be considewed, fow exampwe in atomic check functions.
 */
#define fow_each_owdnew_mst_mgw_in_state(__state, mgw, owd_state, new_state, __i) \
	fow ((__i) = 0; (__i) < (__state)->num_pwivate_objs; (__i)++) \
		fow_each_if(__dwm_dp_mst_state_itew_get((__state), &(mgw), &(owd_state), &(new_state), (__i)))

/**
 * fow_each_owd_mst_mgw_in_state - itewate ovew aww DP MST topowogy managews
 * in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @mgw: &stwuct dwm_dp_mst_topowogy_mgw itewation cuwsow
 * @owd_state: &stwuct dwm_dp_mst_topowogy_state itewation cuwsow fow the owd
 * state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww DWM DP MST topowogy managews in an atomic update,
 * twacking onwy the owd state. This is usefuw in disabwe functions, whewe we
 * need the owd state the hawdwawe is stiww in.
 */
#define fow_each_owd_mst_mgw_in_state(__state, mgw, owd_state, __i) \
	fow ((__i) = 0; (__i) < (__state)->num_pwivate_objs; (__i)++) \
		fow_each_if(__dwm_dp_mst_state_itew_get((__state), &(mgw), &(owd_state), NUWW, (__i)))

/**
 * fow_each_new_mst_mgw_in_state - itewate ovew aww DP MST topowogy managews
 * in an atomic update
 * @__state: &stwuct dwm_atomic_state pointew
 * @mgw: &stwuct dwm_dp_mst_topowogy_mgw itewation cuwsow
 * @new_state: &stwuct dwm_dp_mst_topowogy_state itewation cuwsow fow the new
 * state
 * @__i: int itewation cuwsow, fow macwo-intewnaw use
 *
 * This itewates ovew aww DWM DP MST topowogy managews in an atomic update,
 * twacking onwy the new state. This is usefuw in enabwe functions, whewe we
 * need the new state the hawdwawe shouwd be in when the atomic commit
 * opewation has compweted.
 */
#define fow_each_new_mst_mgw_in_state(__state, mgw, new_state, __i) \
	fow ((__i) = 0; (__i) < (__state)->num_pwivate_objs; (__i)++) \
		fow_each_if(__dwm_dp_mst_state_itew_get((__state), &(mgw), NUWW, &(new_state), (__i)))

#endif
