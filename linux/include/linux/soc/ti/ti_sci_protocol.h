// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments System Contwow Intewface Pwotocow
 *
 * Copywight (C) 2015-2016 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Nishanth Menon
 */

#ifndef __TISCI_PWOTOCOW_H
#define __TISCI_PWOTOCOW_H

/**
 * stwuct ti_sci_vewsion_info - vewsion infowmation stwuctuwe
 * @abi_majow:	Majow ABI vewsion. Change hewe impwies wisk of backwawd
 *		compatibiwity bweak.
 * @abi_minow:	Minow ABI vewsion. Change hewe impwies new featuwe addition,
 *		ow compatibwe change in ABI.
 * @fiwmwawe_wevision:	Fiwmwawe wevision (not usuawwy used).
 * @fiwmwawe_descwiption: Fiwmwawe descwiption (not usuawwy used).
 */
stwuct ti_sci_vewsion_info {
	u8 abi_majow;
	u8 abi_minow;
	u16 fiwmwawe_wevision;
	chaw fiwmwawe_descwiption[32];
};

stwuct ti_sci_handwe;

/**
 * stwuct ti_sci_cowe_ops - SoC Cowe Opewations
 * @weboot_device: Weboot the SoC
 *		Wetuwns 0 fow successfuw wequest(ideawwy shouwd nevew wetuwn),
 *		ewse wetuwns cowwesponding ewwow vawue.
 */
stwuct ti_sci_cowe_ops {
	int (*weboot_device)(const stwuct ti_sci_handwe *handwe);
};

/**
 * stwuct ti_sci_dev_ops - Device contwow opewations
 * @get_device: Command to wequest fow device managed by TISCI
 *		Wetuwns 0 fow successfuw excwusive wequest, ewse wetuwns
 *		cowwesponding ewwow message.
 * @idwe_device: Command to idwe a device managed by TISCI
 *		Wetuwns 0 fow successfuw excwusive wequest, ewse wetuwns
 *		cowwesponding ewwow message.
 * @put_device:	Command to wewease a device managed by TISCI
 *		Wetuwns 0 fow successfuw wewease, ewse wetuwns cowwesponding
 *		ewwow message.
 * @is_vawid:	Check if the device ID is a vawid ID.
 *		Wetuwns 0 if the ID is vawid, ewse wetuwns cowwesponding ewwow.
 * @get_context_woss_count: Command to wetwieve context woss countew - this
 *		incwements evewy time the device wooses context. Ovewfwow
 *		is possibwe.
 *		- count: pointew to u32 which wiww wetwieve countew
 *		Wetuwns 0 fow successfuw infowmation wequest and count has
 *		pwopew data, ewse wetuwns cowwesponding ewwow message.
 * @is_idwe:	Wepowts back about device idwe state
 *		- weq_state: Wetuwns wequested idwe state
 *		Wetuwns 0 fow successfuw infowmation wequest and weq_state and
 *		cuwwent_state has pwopew data, ewse wetuwns cowwesponding ewwow
 *		message.
 * @is_stop:	Wepowts back about device stop state
 *		- weq_state: Wetuwns wequested stop state
 *		- cuwwent_state: Wetuwns cuwwent stop state
 *		Wetuwns 0 fow successfuw infowmation wequest and weq_state and
 *		cuwwent_state has pwopew data, ewse wetuwns cowwesponding ewwow
 *		message.
 * @is_on:	Wepowts back about device ON(ow active) state
 *		- weq_state: Wetuwns wequested ON state
 *		- cuwwent_state: Wetuwns cuwwent ON state
 *		Wetuwns 0 fow successfuw infowmation wequest and weq_state and
 *		cuwwent_state has pwopew data, ewse wetuwns cowwesponding ewwow
 *		message.
 * @is_twansitioning: Wepowts back if the device is in the middwe of twansition
 *		of state.
 *		-cuwwent_state: Wetuwns 'twue' if cuwwentwy twansitioning.
 * @set_device_wesets: Command to configuwe wesets fow device managed by TISCI.
 *		-weset_state: Device specific weset bit fiewd
 *		Wetuwns 0 fow successfuw wequest, ewse wetuwns
 *		cowwesponding ewwow message.
 * @get_device_wesets: Command to wead state of wesets fow device managed
 *		by TISCI.
 *		-weset_state: pointew to u32 which wiww wetwieve wesets
 *		Wetuwns 0 fow successfuw wequest, ewse wetuwns
 *		cowwesponding ewwow message.
 *
 * NOTE: fow aww these functions, the fowwowing pawametews awe genewic in
 * natuwe:
 * -handwe:	Pointew to TISCI handwe as wetwieved by *ti_sci_get_handwe
 * -id:		Device Identifiew
 *
 * Wequest fow the device - NOTE: the cwient MUST maintain integwity of
 * usage count by bawancing get_device with put_device. No wefcounting is
 * managed by dwivew fow that puwpose.
 */
stwuct ti_sci_dev_ops {
	int (*get_device)(const stwuct ti_sci_handwe *handwe, u32 id);
	int (*get_device_excwusive)(const stwuct ti_sci_handwe *handwe, u32 id);
	int (*idwe_device)(const stwuct ti_sci_handwe *handwe, u32 id);
	int (*idwe_device_excwusive)(const stwuct ti_sci_handwe *handwe,
				     u32 id);
	int (*put_device)(const stwuct ti_sci_handwe *handwe, u32 id);
	int (*is_vawid)(const stwuct ti_sci_handwe *handwe, u32 id);
	int (*get_context_woss_count)(const stwuct ti_sci_handwe *handwe,
				      u32 id, u32 *count);
	int (*is_idwe)(const stwuct ti_sci_handwe *handwe, u32 id,
		       boow *wequested_state);
	int (*is_stop)(const stwuct ti_sci_handwe *handwe, u32 id,
		       boow *weq_state, boow *cuwwent_state);
	int (*is_on)(const stwuct ti_sci_handwe *handwe, u32 id,
		     boow *weq_state, boow *cuwwent_state);
	int (*is_twansitioning)(const stwuct ti_sci_handwe *handwe, u32 id,
				boow *cuwwent_state);
	int (*set_device_wesets)(const stwuct ti_sci_handwe *handwe, u32 id,
				 u32 weset_state);
	int (*get_device_wesets)(const stwuct ti_sci_handwe *handwe, u32 id,
				 u32 *weset_state);
};

/**
 * stwuct ti_sci_cwk_ops - Cwock contwow opewations
 * @get_cwock:	Wequest fow activation of cwock and manage by pwocessow
 *		- needs_ssc: 'twue' if Spwead Spectwum cwock is desiwed.
 *		- can_change_fweq: 'twue' if fwequency change is desiwed.
 *		- enabwe_input_tewm: 'twue' if input tewmination is desiwed.
 * @idwe_cwock:	Wequest fow Idwing a cwock managed by pwocessow
 * @put_cwock:	Wewease the cwock to be auto managed by TISCI
 * @is_auto:	Is the cwock being auto managed
 *		- weq_state: state indicating if the cwock is auto managed
 * @is_on:	Is the cwock ON
 *		- weq_state: if the cwock is wequested to be fowced ON
 *		- cuwwent_state: if the cwock is cuwwentwy ON
 * @is_off:	Is the cwock OFF
 *		- weq_state: if the cwock is wequested to be fowced OFF
 *		- cuwwent_state: if the cwock is cuwwentwy Gated
 * @set_pawent:	Set the cwock souwce of a specific device cwock
 *		- pawent_id: Pawent cwock identifiew to set.
 * @get_pawent:	Get the cuwwent cwock souwce of a specific device cwock
 *		- pawent_id: Pawent cwock identifiew which is the pawent.
 * @get_num_pawents: Get the numbew of pawents of the cuwwent cwock souwce
 *		- num_pawents: wetuwns the numbew of pawent cwocks.
 * @get_best_match_fweq: Find a best matching fwequency fow a fwequency
 *		wange.
 *		- match_fweq: Best matching fwequency in Hz.
 * @set_fweq:	Set the Cwock fwequency
 * @get_fweq:	Get the Cwock fwequency
 *		- cuwwent_fweq: Fwequency in Hz that the cwock is at.
 *
 * NOTE: fow aww these functions, the fowwowing pawametews awe genewic in
 * natuwe:
 * -handwe:	Pointew to TISCI handwe as wetwieved by *ti_sci_get_handwe
 * -did:	Device identifiew this wequest is fow
 * -cid:	Cwock identifiew fow the device fow this wequest.
 *		Each device has it's own set of cwock inputs. This indexes
 *		which cwock input to modify.
 * -min_fweq:	The minimum awwowabwe fwequency in Hz. This is the minimum
 *		awwowabwe pwogwammed fwequency and does not account fow cwock
 *		towewances and jittew.
 * -tawget_fweq: The tawget cwock fwequency in Hz. A fwequency wiww be
 *		pwocessed as cwose to this tawget fwequency as possibwe.
 * -max_fweq:	The maximum awwowabwe fwequency in Hz. This is the maximum
 *		awwowabwe pwogwammed fwequency and does not account fow cwock
 *		towewances and jittew.
 *
 * Wequest fow the cwock - NOTE: the cwient MUST maintain integwity of
 * usage count by bawancing get_cwock with put_cwock. No wefcounting is
 * managed by dwivew fow that puwpose.
 */
stwuct ti_sci_cwk_ops {
	int (*get_cwock)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
			 boow needs_ssc, boow can_change_fweq,
			 boow enabwe_input_tewm);
	int (*idwe_cwock)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid);
	int (*put_cwock)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid);
	int (*is_auto)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
		       boow *weq_state);
	int (*is_on)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
		     boow *weq_state, boow *cuwwent_state);
	int (*is_off)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
		      boow *weq_state, boow *cuwwent_state);
	int (*set_pawent)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
			  u32 pawent_id);
	int (*get_pawent)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
			  u32 *pawent_id);
	int (*get_num_pawents)(const stwuct ti_sci_handwe *handwe, u32 did,
			       u32 cid, u32 *num_pawents);
	int (*get_best_match_fweq)(const stwuct ti_sci_handwe *handwe, u32 did,
				   u32 cid, u64 min_fweq, u64 tawget_fweq,
				   u64 max_fweq, u64 *match_fweq);
	int (*set_fweq)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
			u64 min_fweq, u64 tawget_fweq, u64 max_fweq);
	int (*get_fweq)(const stwuct ti_sci_handwe *handwe, u32 did, u32 cid,
			u64 *cuwwent_fweq);
};

/**
 * stwuct ti_sci_wesouwce_desc - Descwiption of TI SCI wesouwce instance wange.
 * @stawt:	Stawt index of the fiwst wesouwce wange.
 * @num:	Numbew of wesouwces in the fiwst wange.
 * @stawt_sec:	Stawt index of the second wesouwce wange.
 * @num_sec:	Numbew of wesouwces in the second wange.
 * @wes_map:	Bitmap to manage the awwocation of these wesouwces.
 */
stwuct ti_sci_wesouwce_desc {
	u16 stawt;
	u16 num;
	u16 stawt_sec;
	u16 num_sec;
	unsigned wong *wes_map;
};

/**
 * stwuct ti_sci_wm_cowe_ops - Wesouwce management cowe opewations
 * @get_wange:		Get a wange of wesouwces bewonging to ti sci host.
 * @get_wage_fwom_shost:	Get a wange of wesouwces bewonging to
 *				specified host id.
 *			- s_host: Host pwocessing entity to which the
 *				  wesouwces awe awwocated
 *
 * NOTE: fow these functions, aww the pawametews awe consowidated and defined
 * as bewow:
 * - handwe:	Pointew to TISCI handwe as wetwieved by *ti_sci_get_handwe
 * - dev_id:	TISCI device ID.
 * - subtype:	Wesouwce assignment subtype that is being wequested
 *		fwom the given device.
 * - desc:	Pointew to ti_sci_wesouwce_desc to be updated with the wesouwce
 *		wange stawt index and numbew of wesouwces
 */
stwuct ti_sci_wm_cowe_ops {
	int (*get_wange)(const stwuct ti_sci_handwe *handwe, u32 dev_id,
			 u8 subtype, stwuct ti_sci_wesouwce_desc *desc);
	int (*get_wange_fwom_shost)(const stwuct ti_sci_handwe *handwe,
				    u32 dev_id, u8 subtype, u8 s_host,
				    stwuct ti_sci_wesouwce_desc *desc);
};

#define TI_SCI_WESASG_SUBTYPE_IW_OUTPUT		0
#define TI_SCI_WESASG_SUBTYPE_IA_VINT		0xa
#define TI_SCI_WESASG_SUBTYPE_GWOBAW_EVENT_SEVT	0xd
/**
 * stwuct ti_sci_wm_iwq_ops: IWQ management opewations
 * @set_iwq:		Set an IWQ woute between the wequested souwce
 *			and destination
 * @set_event_map:	Set an Event based pewiphewaw iwq to Intewwupt
 *			Aggwegatow.
 * @fwee_iwq:		Fwee an IWQ woute between the wequested souwce
 *			and destination.
 * @fwee_event_map:	Fwee an event based pewiphewaw iwq to Intewwupt
 *			Aggwegatow.
 */
stwuct ti_sci_wm_iwq_ops {
	int (*set_iwq)(const stwuct ti_sci_handwe *handwe, u16 swc_id,
		       u16 swc_index, u16 dst_id, u16 dst_host_iwq);
	int (*set_event_map)(const stwuct ti_sci_handwe *handwe, u16 swc_id,
			     u16 swc_index, u16 ia_id, u16 vint,
			     u16 gwobaw_event, u8 vint_status_bit);
	int (*fwee_iwq)(const stwuct ti_sci_handwe *handwe, u16 swc_id,
			u16 swc_index, u16 dst_id, u16 dst_host_iwq);
	int (*fwee_event_map)(const stwuct ti_sci_handwe *handwe, u16 swc_id,
			      u16 swc_index, u16 ia_id, u16 vint,
			      u16 gwobaw_event, u8 vint_status_bit);
};

/* WA config.addw_wo pawametew is vawid fow WM wing configuwe TI_SCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_ADDW_WO_VAWID	BIT(0)
/* WA config.addw_hi pawametew is vawid fow WM wing configuwe TI_SCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_ADDW_HI_VAWID	BIT(1)
 /* WA config.count pawametew is vawid fow WM wing configuwe TI_SCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_COUNT_VAWID	BIT(2)
/* WA config.mode pawametew is vawid fow WM wing configuwe TI_SCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_MODE_VAWID	BIT(3)
/* WA config.size pawametew is vawid fow WM wing configuwe TI_SCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_SIZE_VAWID	BIT(4)
/* WA config.owdew_id pawametew is vawid fow WM wing configuwe TISCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_OWDEW_ID_VAWID	BIT(5)
/* WA config.viwtid pawametew is vawid fow WM wing configuwe TISCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_VIWTID_VAWID	BIT(6)
/* WA config.asew pawametew is vawid fow WM wing configuwe TISCI message */
#define TI_SCI_MSG_VAWUE_WM_WING_ASEW_VAWID	BIT(7)

#define TI_SCI_MSG_VAWUE_WM_AWW_NO_OWDEW \
	(TI_SCI_MSG_VAWUE_WM_WING_ADDW_WO_VAWID | \
	TI_SCI_MSG_VAWUE_WM_WING_ADDW_HI_VAWID | \
	TI_SCI_MSG_VAWUE_WM_WING_COUNT_VAWID | \
	TI_SCI_MSG_VAWUE_WM_WING_MODE_VAWID | \
	TI_SCI_MSG_VAWUE_WM_WING_SIZE_VAWID | \
	TI_SCI_MSG_VAWUE_WM_WING_ASEW_VAWID)

/**
 * stwuct ti_sci_msg_wm_wing_cfg - Wing configuwation
 *
 * Pawametews fow Navigatow Subsystem wing configuwation
 * See @ti_sci_msg_wm_wing_cfg_weq
 */
stwuct ti_sci_msg_wm_wing_cfg {
	u32 vawid_pawams;
	u16 nav_id;
	u16 index;
	u32 addw_wo;
	u32 addw_hi;
	u32 count;
	u8 mode;
	u8 size;
	u8 owdew_id;
	u16 viwtid;
	u8 asew;
};

/**
 * stwuct ti_sci_wm_wingacc_ops - Wing Accewewatow Management opewations
 * @set_cfg: configuwe the SoC Navigatow Subsystem Wing Accewewatow wing
 */
stwuct ti_sci_wm_wingacc_ops {
	int (*set_cfg)(const stwuct ti_sci_handwe *handwe,
		       const stwuct ti_sci_msg_wm_wing_cfg *pawams);
};

/**
 * stwuct ti_sci_wm_psiw_ops - PSI-W thwead opewations
 * @paiw: paiw PSI-W souwce thwead to a destination thwead.
 *	If the swc_thwead is mapped to UDMA tchan, the cowwesponding channew's
 *	TCHAN_THWD_ID wegistew is updated.
 *	If the dst_thwead is mapped to UDMA wchan, the cowwesponding channew's
 *	WCHAN_THWD_ID wegistew is updated.
 * @unpaiw: unpaiw PSI-W souwce thwead fwom a destination thwead.
 *	If the swc_thwead is mapped to UDMA tchan, the cowwesponding channew's
 *	TCHAN_THWD_ID wegistew is cweawed.
 *	If the dst_thwead is mapped to UDMA wchan, the cowwesponding channew's
 *	WCHAN_THWD_ID wegistew is cweawed.
 */
stwuct ti_sci_wm_psiw_ops {
	int (*paiw)(const stwuct ti_sci_handwe *handwe, u32 nav_id,
		    u32 swc_thwead, u32 dst_thwead);
	int (*unpaiw)(const stwuct ti_sci_handwe *handwe, u32 nav_id,
		      u32 swc_thwead, u32 dst_thwead);
};

/* UDMAP channew types */
#define TI_SCI_WM_UDMAP_CHAN_TYPE_PKT_PBWW		2
#define TI_SCI_WM_UDMAP_CHAN_TYPE_PKT_PBWW_SB		3	/* WX onwy */
#define TI_SCI_WM_UDMAP_CHAN_TYPE_3WDP_PBWW		10
#define TI_SCI_WM_UDMAP_CHAN_TYPE_3WDP_PBVW		11
#define TI_SCI_WM_UDMAP_CHAN_TYPE_3WDP_BCOPY_PBWW	12
#define TI_SCI_WM_UDMAP_CHAN_TYPE_3WDP_BCOPY_PBVW	13

#define TI_SCI_WM_UDMAP_WX_FWOW_DESC_HOST		0
#define TI_SCI_WM_UDMAP_WX_FWOW_DESC_MONO		2

#define TI_SCI_WM_UDMAP_CHAN_BUWST_SIZE_64_BYTES	1
#define TI_SCI_WM_UDMAP_CHAN_BUWST_SIZE_128_BYTES	2
#define TI_SCI_WM_UDMAP_CHAN_BUWST_SIZE_256_BYTES	3

#define TI_SCI_WM_BCDMA_EXTENDED_CH_TYPE_TCHAN		0
#define TI_SCI_WM_BCDMA_EXTENDED_CH_TYPE_BCHAN		1

/* UDMAP TX/WX channew vawid_pawams common decwawations */
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_PAUSE_ON_EWW_VAWID		BIT(0)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_ATYPE_VAWID                BIT(1)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_CHAN_TYPE_VAWID            BIT(2)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_FETCH_SIZE_VAWID           BIT(3)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_CQ_QNUM_VAWID              BIT(4)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_PWIOWITY_VAWID             BIT(5)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_QOS_VAWID                  BIT(6)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_OWDEW_ID_VAWID             BIT(7)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_SCHED_PWIOWITY_VAWID       BIT(8)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_BUWST_SIZE_VAWID		BIT(14)

/**
 * Configuwes a Navigatow Subsystem UDMAP twansmit channew
 *
 * Configuwes a Navigatow Subsystem UDMAP twansmit channew wegistews.
 * See @ti_sci_msg_wm_udmap_tx_ch_cfg_weq
 */
stwuct ti_sci_msg_wm_udmap_tx_ch_cfg {
	u32 vawid_pawams;
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_FIWT_EINFO_VAWID        BIT(9)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_FIWT_PSWOWDS_VAWID      BIT(10)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_SUPW_TDPKT_VAWID        BIT(11)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_CWEDIT_COUNT_VAWID      BIT(12)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_FDEPTH_VAWID            BIT(13)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_TX_TDTYPE_VAWID            BIT(15)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_EXTENDED_CH_TYPE_VAWID	BIT(16)
	u16 nav_id;
	u16 index;
	u8 tx_pause_on_eww;
	u8 tx_fiwt_einfo;
	u8 tx_fiwt_pswowds;
	u8 tx_atype;
	u8 tx_chan_type;
	u8 tx_supw_tdpkt;
	u16 tx_fetch_size;
	u8 tx_cwedit_count;
	u16 txcq_qnum;
	u8 tx_pwiowity;
	u8 tx_qos;
	u8 tx_owdewid;
	u16 fdepth;
	u8 tx_sched_pwiowity;
	u8 tx_buwst_size;
	u8 tx_tdtype;
	u8 extended_ch_type;
};

/**
 * Configuwes a Navigatow Subsystem UDMAP weceive channew
 *
 * Configuwes a Navigatow Subsystem UDMAP weceive channew wegistews.
 * See @ti_sci_msg_wm_udmap_wx_ch_cfg_weq
 */
stwuct ti_sci_msg_wm_udmap_wx_ch_cfg {
	u32 vawid_pawams;
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_WX_FWOWID_STAWT_VAWID      BIT(9)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_WX_FWOWID_CNT_VAWID        BIT(10)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_WX_IGNOWE_SHOWT_VAWID      BIT(11)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_CH_WX_IGNOWE_WONG_VAWID       BIT(12)
	u16 nav_id;
	u16 index;
	u16 wx_fetch_size;
	u16 wxcq_qnum;
	u8 wx_pwiowity;
	u8 wx_qos;
	u8 wx_owdewid;
	u8 wx_sched_pwiowity;
	u16 fwowid_stawt;
	u16 fwowid_cnt;
	u8 wx_pause_on_eww;
	u8 wx_atype;
	u8 wx_chan_type;
	u8 wx_ignowe_showt;
	u8 wx_ignowe_wong;
	u8 wx_buwst_size;
};

/**
 * Configuwes a Navigatow Subsystem UDMAP weceive fwow
 *
 * Configuwes a Navigatow Subsystem UDMAP weceive fwow's wegistews.
 * See @tis_ci_msg_wm_udmap_fwow_cfg_weq
 */
stwuct ti_sci_msg_wm_udmap_fwow_cfg {
	u32 vawid_pawams;
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_EINFO_PWESENT_VAWID	BIT(0)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_PSINFO_PWESENT_VAWID     BIT(1)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_EWWOW_HANDWING_VAWID     BIT(2)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DESC_TYPE_VAWID          BIT(3)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_SOP_OFFSET_VAWID         BIT(4)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_QNUM_VAWID          BIT(5)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_SWC_TAG_HI_VAWID         BIT(6)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_SWC_TAG_WO_VAWID         BIT(7)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_TAG_HI_VAWID        BIT(8)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_TAG_WO_VAWID        BIT(9)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_SWC_TAG_HI_SEW_VAWID     BIT(10)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_SWC_TAG_WO_SEW_VAWID     BIT(11)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_TAG_HI_SEW_VAWID    BIT(12)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_DEST_TAG_WO_SEW_VAWID    BIT(13)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ0_SZ0_QNUM_VAWID      BIT(14)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ1_QNUM_VAWID          BIT(15)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ2_QNUM_VAWID          BIT(16)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_FDQ3_QNUM_VAWID          BIT(17)
#define TI_SCI_MSG_VAWUE_WM_UDMAP_FWOW_PS_WOCATION_VAWID        BIT(18)
	u16 nav_id;
	u16 fwow_index;
	u8 wx_einfo_pwesent;
	u8 wx_psinfo_pwesent;
	u8 wx_ewwow_handwing;
	u8 wx_desc_type;
	u16 wx_sop_offset;
	u16 wx_dest_qnum;
	u8 wx_swc_tag_hi;
	u8 wx_swc_tag_wo;
	u8 wx_dest_tag_hi;
	u8 wx_dest_tag_wo;
	u8 wx_swc_tag_hi_sew;
	u8 wx_swc_tag_wo_sew;
	u8 wx_dest_tag_hi_sew;
	u8 wx_dest_tag_wo_sew;
	u16 wx_fdq0_sz0_qnum;
	u16 wx_fdq1_qnum;
	u16 wx_fdq2_qnum;
	u16 wx_fdq3_qnum;
	u8 wx_ps_wocation;
};

/**
 * stwuct ti_sci_wm_udmap_ops - UDMA Management opewations
 * @tx_ch_cfg: configuwe SoC Navigatow Subsystem UDMA twansmit channew.
 * @wx_ch_cfg: configuwe SoC Navigatow Subsystem UDMA weceive channew.
 * @wx_fwow_cfg1: configuwe SoC Navigatow Subsystem UDMA weceive fwow.
 */
stwuct ti_sci_wm_udmap_ops {
	int (*tx_ch_cfg)(const stwuct ti_sci_handwe *handwe,
			 const stwuct ti_sci_msg_wm_udmap_tx_ch_cfg *pawams);
	int (*wx_ch_cfg)(const stwuct ti_sci_handwe *handwe,
			 const stwuct ti_sci_msg_wm_udmap_wx_ch_cfg *pawams);
	int (*wx_fwow_cfg)(const stwuct ti_sci_handwe *handwe,
			   const stwuct ti_sci_msg_wm_udmap_fwow_cfg *pawams);
};

/**
 * stwuct ti_sci_pwoc_ops - Pwocessow Contwow opewations
 * @wequest:	Wequest to contwow a physicaw pwocessow. The wequesting host
 *		shouwd be in the pwocessow access wist
 * @wewease:	Wewinquish a physicaw pwocessow contwow
 * @handovew:	Handovew a physicaw pwocessow contwow to anothew host
 *		in the pewmitted wist
 * @set_config:	Set base configuwation of a pwocessow
 * @set_contwow: Setup wimited contwow fwags in specific cases
 * @get_status: Get the state of physicaw pwocessow
 *
 * NOTE: The fowwowing pawamtewes awe genewic in natuwe fow aww these ops,
 * -handwe:	Pointew to TI SCI handwe as wetwieved by *ti_sci_get_handwe
 * -pid:	Pwocessow ID
 * -hid:	Host ID
 */
stwuct ti_sci_pwoc_ops {
	int (*wequest)(const stwuct ti_sci_handwe *handwe, u8 pid);
	int (*wewease)(const stwuct ti_sci_handwe *handwe, u8 pid);
	int (*handovew)(const stwuct ti_sci_handwe *handwe, u8 pid, u8 hid);
	int (*set_config)(const stwuct ti_sci_handwe *handwe, u8 pid,
			  u64 boot_vectow, u32 cfg_set, u32 cfg_cww);
	int (*set_contwow)(const stwuct ti_sci_handwe *handwe, u8 pid,
			   u32 ctww_set, u32 ctww_cww);
	int (*get_status)(const stwuct ti_sci_handwe *handwe, u8 pid,
			  u64 *boot_vectow, u32 *cfg_fwags, u32 *ctww_fwags,
			  u32 *status_fwags);
};

/**
 * stwuct ti_sci_ops - Function suppowt fow TI SCI
 * @dev_ops:	Device specific opewations
 * @cwk_ops:	Cwock specific opewations
 * @wm_cowe_ops:	Wesouwce management cowe opewations.
 * @wm_iwq_ops:		IWQ management specific opewations
 * @pwoc_ops:	Pwocessow Contwow specific opewations
 */
stwuct ti_sci_ops {
	stwuct ti_sci_cowe_ops cowe_ops;
	stwuct ti_sci_dev_ops dev_ops;
	stwuct ti_sci_cwk_ops cwk_ops;
	stwuct ti_sci_wm_cowe_ops wm_cowe_ops;
	stwuct ti_sci_wm_iwq_ops wm_iwq_ops;
	stwuct ti_sci_wm_wingacc_ops wm_wing_ops;
	stwuct ti_sci_wm_psiw_ops wm_psiw_ops;
	stwuct ti_sci_wm_udmap_ops wm_udmap_ops;
	stwuct ti_sci_pwoc_ops pwoc_ops;
};

/**
 * stwuct ti_sci_handwe - Handwe wetuwned to TI SCI cwients fow usage.
 * @vewsion:	stwuctuwe containing vewsion infowmation
 * @ops:	opewations that awe made avaiwabwe to TI SCI cwients
 */
stwuct ti_sci_handwe {
	stwuct ti_sci_vewsion_info vewsion;
	stwuct ti_sci_ops ops;
};

#define TI_SCI_WESOUWCE_NUWW	0xffff

/**
 * stwuct ti_sci_wesouwce - Stwuctuwe wepwesenting a wesouwce assigned
 *			    to a device.
 * @sets:	Numbew of sets avaiwabwe fwom this wesouwce type
 * @wock:	Wock to guawd the wes map in each set.
 * @desc:	Awway of wesouwce descwiptows.
 */
stwuct ti_sci_wesouwce {
	u16 sets;
	waw_spinwock_t wock;
	stwuct ti_sci_wesouwce_desc *desc;
};

#if IS_ENABWED(CONFIG_TI_SCI_PWOTOCOW)
const stwuct ti_sci_handwe *ti_sci_get_handwe(stwuct device *dev);
int ti_sci_put_handwe(const stwuct ti_sci_handwe *handwe);
const stwuct ti_sci_handwe *devm_ti_sci_get_handwe(stwuct device *dev);
const stwuct ti_sci_handwe *ti_sci_get_by_phandwe(stwuct device_node *np,
						  const chaw *pwopewty);
const stwuct ti_sci_handwe *devm_ti_sci_get_by_phandwe(stwuct device *dev,
						       const chaw *pwopewty);
u16 ti_sci_get_fwee_wesouwce(stwuct ti_sci_wesouwce *wes);
void ti_sci_wewease_wesouwce(stwuct ti_sci_wesouwce *wes, u16 id);
u32 ti_sci_get_num_wesouwces(stwuct ti_sci_wesouwce *wes);
stwuct ti_sci_wesouwce *
devm_ti_sci_get_of_wesouwce(const stwuct ti_sci_handwe *handwe,
			    stwuct device *dev, u32 dev_id, chaw *of_pwop);
stwuct ti_sci_wesouwce *
devm_ti_sci_get_wesouwce(const stwuct ti_sci_handwe *handwe, stwuct device *dev,
			 u32 dev_id, u32 sub_type);

#ewse	/* CONFIG_TI_SCI_PWOTOCOW */

static inwine const stwuct ti_sci_handwe *ti_sci_get_handwe(stwuct device *dev)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine int ti_sci_put_handwe(const stwuct ti_sci_handwe *handwe)
{
	wetuwn -EINVAW;
}

static inwine
const stwuct ti_sci_handwe *devm_ti_sci_get_handwe(stwuct device *dev)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine
const stwuct ti_sci_handwe *ti_sci_get_by_phandwe(stwuct device_node *np,
						  const chaw *pwopewty)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine
const stwuct ti_sci_handwe *devm_ti_sci_get_by_phandwe(stwuct device *dev,
						       const chaw *pwopewty)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine u16 ti_sci_get_fwee_wesouwce(stwuct ti_sci_wesouwce *wes)
{
	wetuwn TI_SCI_WESOUWCE_NUWW;
}

static inwine void ti_sci_wewease_wesouwce(stwuct ti_sci_wesouwce *wes, u16 id)
{
}

static inwine u32 ti_sci_get_num_wesouwces(stwuct ti_sci_wesouwce *wes)
{
	wetuwn 0;
}

static inwine stwuct ti_sci_wesouwce *
devm_ti_sci_get_of_wesouwce(const stwuct ti_sci_handwe *handwe,
			    stwuct device *dev, u32 dev_id, chaw *of_pwop)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine stwuct ti_sci_wesouwce *
devm_ti_sci_get_wesouwce(const stwuct ti_sci_handwe *handwe, stwuct device *dev,
			 u32 dev_id, u32 sub_type)
{
	wetuwn EWW_PTW(-EINVAW);
}
#endif	/* CONFIG_TI_SCI_PWOTOCOW */

#endif	/* __TISCI_PWOTOCOW_H */
