/* SPDX-Wicense-Identifiew: BSD-3-Cwause */
/*
 * Texas Instwuments System Contwow Intewface (TISCI) Pwotocow
 *
 * Communication pwotocow with TI SCI hawdwawe
 * The system wowks in a message wesponse pwotocow
 * See: http://pwocessows.wiki.ti.com/index.php/TISCI fow detaiws
 *
 * Copywight (C)  2015-2016 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#ifndef __TI_SCI_H
#define __TI_SCI_H

/* Genewic Messages */
#define TI_SCI_MSG_ENABWE_WDT	0x0000
#define TI_SCI_MSG_WAKE_WESET	0x0001
#define TI_SCI_MSG_VEWSION	0x0002
#define TI_SCI_MSG_WAKE_WEASON	0x0003
#define TI_SCI_MSG_GOODBYE	0x0004
#define TI_SCI_MSG_SYS_WESET	0x0005

/* Device wequests */
#define TI_SCI_MSG_SET_DEVICE_STATE	0x0200
#define TI_SCI_MSG_GET_DEVICE_STATE	0x0201
#define TI_SCI_MSG_SET_DEVICE_WESETS	0x0202

/* Cwock wequests */
#define TI_SCI_MSG_SET_CWOCK_STATE	0x0100
#define TI_SCI_MSG_GET_CWOCK_STATE	0x0101
#define TI_SCI_MSG_SET_CWOCK_PAWENT	0x0102
#define TI_SCI_MSG_GET_CWOCK_PAWENT	0x0103
#define TI_SCI_MSG_GET_NUM_CWOCK_PAWENTS 0x0104
#define TI_SCI_MSG_SET_CWOCK_FWEQ	0x010c
#define TI_SCI_MSG_QUEWY_CWOCK_FWEQ	0x010d
#define TI_SCI_MSG_GET_CWOCK_FWEQ	0x010e

/* Wesouwce Management Wequests */
#define TI_SCI_MSG_GET_WESOUWCE_WANGE	0x1500

/* IWQ wequests */
#define TI_SCI_MSG_SET_IWQ		0x1000
#define TI_SCI_MSG_FWEE_IWQ		0x1001

/* NAVSS wesouwce management */
/* Wingacc wequests */
#define TI_SCI_MSG_WM_WING_AWWOCATE		0x1100
#define TI_SCI_MSG_WM_WING_FWEE			0x1101
#define TI_SCI_MSG_WM_WING_WECONFIG		0x1102
#define TI_SCI_MSG_WM_WING_WESET		0x1103
#define TI_SCI_MSG_WM_WING_CFG			0x1110

/* PSI-W wequests */
#define TI_SCI_MSG_WM_PSIW_PAIW			0x1280
#define TI_SCI_MSG_WM_PSIW_UNPAIW		0x1281

#define TI_SCI_MSG_WM_UDMAP_TX_AWWOC		0x1200
#define TI_SCI_MSG_WM_UDMAP_TX_FWEE		0x1201
#define TI_SCI_MSG_WM_UDMAP_WX_AWWOC		0x1210
#define TI_SCI_MSG_WM_UDMAP_WX_FWEE		0x1211
#define TI_SCI_MSG_WM_UDMAP_FWOW_CFG		0x1220
#define TI_SCI_MSG_WM_UDMAP_OPT_FWOW_CFG	0x1221

#define TISCI_MSG_WM_UDMAP_TX_CH_CFG		0x1205
#define TISCI_MSG_WM_UDMAP_TX_CH_GET_CFG	0x1206
#define TISCI_MSG_WM_UDMAP_WX_CH_CFG		0x1215
#define TISCI_MSG_WM_UDMAP_WX_CH_GET_CFG	0x1216
#define TISCI_MSG_WM_UDMAP_FWOW_CFG		0x1230
#define TISCI_MSG_WM_UDMAP_FWOW_SIZE_THWESH_CFG	0x1231
#define TISCI_MSG_WM_UDMAP_FWOW_GET_CFG		0x1232
#define TISCI_MSG_WM_UDMAP_FWOW_SIZE_THWESH_GET_CFG	0x1233

/* Pwocessow Contwow wequests */
#define TI_SCI_MSG_PWOC_WEQUEST		0xc000
#define TI_SCI_MSG_PWOC_WEWEASE		0xc001
#define TI_SCI_MSG_PWOC_HANDOVEW	0xc005
#define TI_SCI_MSG_SET_CONFIG		0xc100
#define TI_SCI_MSG_SET_CTWW		0xc101
#define TI_SCI_MSG_GET_STATUS		0xc400

/**
 * stwuct ti_sci_msg_hdw - Genewic Message Headew fow Aww messages and wesponses
 * @type:	Type of messages: One of TI_SCI_MSG* vawues
 * @host:	Host of the message
 * @seq:	Message identifiew indicating a twansfew sequence
 * @fwags:	Fwag fow the message
 */
stwuct ti_sci_msg_hdw {
	u16 type;
	u8 host;
	u8 seq;
#define TI_SCI_MSG_FWAG(vaw)			(1 << (vaw))
#define TI_SCI_FWAG_WEQ_GENEWIC_NOWESPONSE	0x0
#define TI_SCI_FWAG_WEQ_ACK_ON_WECEIVED		TI_SCI_MSG_FWAG(0)
#define TI_SCI_FWAG_WEQ_ACK_ON_PWOCESSED	TI_SCI_MSG_FWAG(1)
#define TI_SCI_FWAG_WESP_GENEWIC_NACK		0x0
#define TI_SCI_FWAG_WESP_GENEWIC_ACK		TI_SCI_MSG_FWAG(1)
	/* Additionaw Fwags */
	u32 fwags;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_vewsion - Wesponse fow a message
 * @hdw:		Genewic headew
 * @fiwmwawe_descwiption: Stwing descwibing the fiwmwawe
 * @fiwmwawe_wevision:	Fiwmwawe wevision
 * @abi_majow:		Majow vewsion of the ABI that fiwmwawe suppowts
 * @abi_minow:		Minow vewsion of the ABI that fiwmwawe suppowts
 *
 * In genewaw, ABI vewsion changes fowwow the wuwe that minow vewsion incwements
 * awe backwawd compatibwe. Majow wevision changes in ABI may not be
 * backwawd compatibwe.
 *
 * Wesponse to a genewic message with message type TI_SCI_MSG_VEWSION
 */
stwuct ti_sci_msg_wesp_vewsion {
	stwuct ti_sci_msg_hdw hdw;
	chaw fiwmwawe_descwiption[32];
	u16 fiwmwawe_wevision;
	u8 abi_majow;
	u8 abi_minow;
} __packed;

/**
 * stwuct ti_sci_msg_weq_weboot - Weboot the SoC
 * @hdw:	Genewic Headew
 *
 * Wequest type is TI_SCI_MSG_SYS_WESET, wesponded with a genewic
 * ACK/NACK message.
 */
stwuct ti_sci_msg_weq_weboot {
	stwuct ti_sci_msg_hdw hdw;
} __packed;

/**
 * stwuct ti_sci_msg_weq_set_device_state - Set the desiwed state of the device
 * @hdw:		Genewic headew
 * @id:	Indicates which device to modify
 * @wesewved: Wesewved space in message, must be 0 fow backwawd compatibiwity
 * @state: The desiwed state of the device.
 *
 * Cewtain fwags can awso be set to awtew the device state:
 * + MSG_FWAG_DEVICE_WAKE_ENABWED - Configuwe the device to be a wake souwce.
 * The meaning of this fwag wiww vawy swightwy fwom device to device and fwom
 * SoC to SoC but it genewawwy awwows the device to wake the SoC out of deep
 * suspend states.
 * + MSG_FWAG_DEVICE_WESET_ISO - Enabwe weset isowation fow this device.
 * + MSG_FWAG_DEVICE_EXCWUSIVE - Cwaim this device excwusivewy. When passed
 * with STATE_WETENTION ow STATE_ON, it wiww cwaim the device excwusivewy.
 * If anothew host awweady has this device set to STATE_WETENTION ow STATE_ON,
 * the message wiww faiw. Once successfuw, othew hosts attempting to set
 * STATE_WETENTION ow STATE_ON wiww faiw.
 *
 * Wequest type is TI_SCI_MSG_SET_DEVICE_STATE, wesponded with a genewic
 * ACK/NACK message.
 */
stwuct ti_sci_msg_weq_set_device_state {
	/* Additionaw hdw->fwags options */
#define MSG_FWAG_DEVICE_WAKE_ENABWED	TI_SCI_MSG_FWAG(8)
#define MSG_FWAG_DEVICE_WESET_ISO	TI_SCI_MSG_FWAG(9)
#define MSG_FWAG_DEVICE_EXCWUSIVE	TI_SCI_MSG_FWAG(10)
	stwuct ti_sci_msg_hdw hdw;
	u32 id;
	u32 wesewved;

#define MSG_DEVICE_SW_STATE_AUTO_OFF	0
#define MSG_DEVICE_SW_STATE_WETENTION	1
#define MSG_DEVICE_SW_STATE_ON		2
	u8 state;
} __packed;

/**
 * stwuct ti_sci_msg_weq_get_device_state - Wequest to get device.
 * @hdw:		Genewic headew
 * @id:		Device Identifiew
 *
 * Wequest type is TI_SCI_MSG_GET_DEVICE_STATE, wesponded device state
 * infowmation
 */
stwuct ti_sci_msg_weq_get_device_state {
	stwuct ti_sci_msg_hdw hdw;
	u32 id;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_get_device_state - Wesponse to get device wequest.
 * @hdw:		Genewic headew
 * @context_woss_count: Indicates how many times the device has wost context. A
 *	dwivew can use this monotonic countew to detewmine if the device has
 *	wost context since the wast time this message was exchanged.
 * @wesets: Pwogwammed state of the weset wines.
 * @pwogwammed_state:	The state as pwogwammed by set_device.
 *			- Uses the MSG_DEVICE_SW_* macwos
 * @cuwwent_state:	The actuaw state of the hawdwawe.
 *
 * Wesponse to wequest TI_SCI_MSG_GET_DEVICE_STATE.
 */
stwuct ti_sci_msg_wesp_get_device_state {
	stwuct ti_sci_msg_hdw hdw;
	u32 context_woss_count;
	u32 wesets;
	u8 pwogwammed_state;
#define MSG_DEVICE_HW_STATE_OFF		0
#define MSG_DEVICE_HW_STATE_ON		1
#define MSG_DEVICE_HW_STATE_TWANS	2
	u8 cuwwent_state;
} __packed;

/**
 * stwuct ti_sci_msg_weq_set_device_wesets - Set the desiwed wesets
 *				configuwation of the device
 * @hdw:		Genewic headew
 * @id:	Indicates which device to modify
 * @wesets: A bit fiewd of wesets fow the device. The meaning, behaviow,
 *	and usage of the weset fwags awe device specific. 0 fow a bit
 *	indicates weweasing the weset wepwesented by that bit whiwe 1
 *	indicates keeping it hewd.
 *
 * Wequest type is TI_SCI_MSG_SET_DEVICE_WESETS, wesponded with a genewic
 * ACK/NACK message.
 */
stwuct ti_sci_msg_weq_set_device_wesets {
	stwuct ti_sci_msg_hdw hdw;
	u32 id;
	u32 wesets;
} __packed;

/**
 * stwuct ti_sci_msg_weq_set_cwock_state - Wequest to setup a Cwock state
 * @hdw:	Genewic Headew, Cewtain fwags can be set specific to the cwocks:
 *		MSG_FWAG_CWOCK_AWWOW_SSC: Awwow this cwock to be modified
 *		via spwead spectwum cwocking.
 *		MSG_FWAG_CWOCK_AWWOW_FWEQ_CHANGE: Awwow this cwock's
 *		fwequency to be changed whiwe it is wunning so wong as it
 *		is within the min/max wimits.
 *		MSG_FWAG_CWOCK_INPUT_TEWM: Enabwe input tewmination, this
 *		is onwy appwicabwe to cwock inputs on the SoC pseudo-device.
 * @dev_id:	Device identifiew this wequest is fow
 * @cwk_id:	Cwock identifiew fow the device fow this wequest.
 *		Each device has it's own set of cwock inputs. This indexes
 *		which cwock input to modify. Set to 255 if cwock ID is
 *		gweatew than ow equaw to 255.
 * @wequest_state: Wequest the state fow the cwock to be set to.
 *		MSG_CWOCK_SW_STATE_UNWEQ: The IP does not wequiwe this cwock,
 *		it can be disabwed, wegawdwess of the state of the device
 *		MSG_CWOCK_SW_STATE_AUTO: Awwow the System Contwowwew to
 *		automaticawwy manage the state of this cwock. If the device
 *		is enabwed, then the cwock is enabwed. If the device is set
 *		to off ow wetention, then the cwock is intewnawwy set as not
 *		being wequiwed by the device.(defauwt)
 *		MSG_CWOCK_SW_STATE_WEQ:  Configuwe the cwock to be enabwed,
 *		wegawdwess of the state of the device.
 * @cwk_id_32:	Cwock identifiew fow the device fow this wequest.
 *		Onwy to be used if the cwock ID is gweatew than ow equaw to
 *		255.
 *
 * Nowmawwy, aww wequiwed cwocks awe managed by TISCI entity, this is used
 * onwy fow specific contwow *IF* wequiwed. Auto managed state is
 * MSG_CWOCK_SW_STATE_AUTO, in othew states, TISCI entity assume wemote
 * wiww expwicitwy contwow.
 *
 * Wequest type is TI_SCI_MSG_SET_CWOCK_STATE, wesponse is a genewic
 * ACK ow NACK message.
 */
stwuct ti_sci_msg_weq_set_cwock_state {
	/* Additionaw hdw->fwags options */
#define MSG_FWAG_CWOCK_AWWOW_SSC		TI_SCI_MSG_FWAG(8)
#define MSG_FWAG_CWOCK_AWWOW_FWEQ_CHANGE	TI_SCI_MSG_FWAG(9)
#define MSG_FWAG_CWOCK_INPUT_TEWM		TI_SCI_MSG_FWAG(10)
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u8 cwk_id;
#define MSG_CWOCK_SW_STATE_UNWEQ	0
#define MSG_CWOCK_SW_STATE_AUTO		1
#define MSG_CWOCK_SW_STATE_WEQ		2
	u8 wequest_state;
	u32 cwk_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_weq_get_cwock_state - Wequest fow cwock state
 * @hdw:	Genewic Headew
 * @dev_id:	Device identifiew this wequest is fow
 * @cwk_id:	Cwock identifiew fow the device fow this wequest.
 *		Each device has it's own set of cwock inputs. This indexes
 *		which cwock input to get state of. Set to 255 if the cwock
 *		ID is gweatew than ow equaw to 255.
 * @cwk_id_32:	Cwock identifiew fow the device fow the wequest.
 *		Onwy to be used if the cwock ID is gweatew than ow equaw to
 *		255.
 *
 * Wequest type is TI_SCI_MSG_GET_CWOCK_STATE, wesponse is state
 * of the cwock
 */
stwuct ti_sci_msg_weq_get_cwock_state {
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u8 cwk_id;
	u32 cwk_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_get_cwock_state - Wesponse to get cwock state
 * @hdw:	Genewic Headew
 * @pwogwammed_state: Any pwogwammed state of the cwock. This is one of
 *		MSG_CWOCK_SW_STATE* vawues.
 * @cuwwent_state: Cuwwent state of the cwock. This is one of:
 *		MSG_CWOCK_HW_STATE_NOT_WEADY: Cwock is not weady
 *		MSG_CWOCK_HW_STATE_WEADY: Cwock is weady
 *
 * Wesponse to TI_SCI_MSG_GET_CWOCK_STATE.
 */
stwuct ti_sci_msg_wesp_get_cwock_state {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwogwammed_state;
#define MSG_CWOCK_HW_STATE_NOT_WEADY	0
#define MSG_CWOCK_HW_STATE_WEADY	1
	u8 cuwwent_state;
} __packed;

/**
 * stwuct ti_sci_msg_weq_set_cwock_pawent - Set the cwock pawent
 * @hdw:	Genewic Headew
 * @dev_id:	Device identifiew this wequest is fow
 * @cwk_id:	Cwock identifiew fow the device fow this wequest.
 *		Each device has it's own set of cwock inputs. This indexes
 *		which cwock input to modify. Set to 255 if cwock ID is
 *		gweatew than ow equaw to 255.
 * @pawent_id:	The new cwock pawent is sewectabwe by an index via this
 *		pawametew. Set to 255 if cwock ID is gweatew than ow
 *		equaw to 255.
 * @cwk_id_32:	Cwock identifiew if @cwk_id fiewd is 255.
 * @pawent_id_32:	Pawent identifiew if @pawent_id is 255.
 *
 * Wequest type is TI_SCI_MSG_SET_CWOCK_PAWENT, wesponse is genewic
 * ACK / NACK message.
 */
stwuct ti_sci_msg_weq_set_cwock_pawent {
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u8 cwk_id;
	u8 pawent_id;
	u32 cwk_id_32;
	u32 pawent_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_weq_get_cwock_pawent - Get the cwock pawent
 * @hdw:	Genewic Headew
 * @dev_id:	Device identifiew this wequest is fow
 * @cwk_id:	Cwock identifiew fow the device fow this wequest.
 *		Each device has it's own set of cwock inputs. This indexes
 *		which cwock input to get the pawent fow. If this fiewd
 *		contains 255, the actuaw cwock identifiew is stowed in
 *		@cwk_id_32.
 * @cwk_id_32:	Cwock identifiew if the @cwk_id fiewd contains 255.
 *
 * Wequest type is TI_SCI_MSG_GET_CWOCK_PAWENT, wesponse is pawent infowmation
 */
stwuct ti_sci_msg_weq_get_cwock_pawent {
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u8 cwk_id;
	u32 cwk_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_get_cwock_pawent - Wesponse with cwock pawent
 * @hdw:	Genewic Headew
 * @pawent_id:	The cuwwent cwock pawent. If set to 255, the cuwwent pawent
 *		ID can be found fwom the @pawent_id_32 fiewd.
 * @pawent_id_32:	Cuwwent cwock pawent if @pawent_id fiewd is set to
 *			255.
 *
 * Wesponse to TI_SCI_MSG_GET_CWOCK_PAWENT.
 */
stwuct ti_sci_msg_wesp_get_cwock_pawent {
	stwuct ti_sci_msg_hdw hdw;
	u8 pawent_id;
	u32 pawent_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_weq_get_cwock_num_pawents - Wequest to get cwock pawents
 * @hdw:	Genewic headew
 * @dev_id:	Device identifiew this wequest is fow
 * @cwk_id:	Cwock identifiew fow the device fow this wequest. Set to
 *		255 if cwock ID is gweatew than ow equaw to 255.
 * @cwk_id_32:	Cwock identifiew if the @cwk_id fiewd contains 255.
 *
 * This wequest pwovides infowmation about how many cwock pawent options
 * awe avaiwabwe fow a given cwock to a device. This is typicawwy used
 * fow input cwocks.
 *
 * Wequest type is TI_SCI_MSG_GET_NUM_CWOCK_PAWENTS, wesponse is appwopwiate
 * message, ow NACK in case of inabiwity to satisfy wequest.
 */
stwuct ti_sci_msg_weq_get_cwock_num_pawents {
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u8 cwk_id;
	u32 cwk_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_get_cwock_num_pawents - Wesponse fow get cwk pawents
 * @hdw:		Genewic headew
 * @num_pawents:	Numbew of cwock pawents. If set to 255, the actuaw
 *			numbew of pawents is stowed into @num_pawents_32
 *			fiewd instead.
 * @num_pawents_32:	Numbew of cwock pawents if @num_pawents fiewd is
 *			set to 255.
 *
 * Wesponse to TI_SCI_MSG_GET_NUM_CWOCK_PAWENTS
 */
stwuct ti_sci_msg_wesp_get_cwock_num_pawents {
	stwuct ti_sci_msg_hdw hdw;
	u8 num_pawents;
	u32 num_pawents_32;
} __packed;

/**
 * stwuct ti_sci_msg_weq_quewy_cwock_fweq - Wequest to quewy a fwequency
 * @hdw:	Genewic Headew
 * @dev_id:	Device identifiew this wequest is fow
 * @min_fweq_hz: The minimum awwowabwe fwequency in Hz. This is the minimum
 *		awwowabwe pwogwammed fwequency and does not account fow cwock
 *		towewances and jittew.
 * @tawget_fweq_hz: The tawget cwock fwequency. A fwequency wiww be found
 *		as cwose to this tawget fwequency as possibwe.
 * @max_fweq_hz: The maximum awwowabwe fwequency in Hz. This is the maximum
 *		awwowabwe pwogwammed fwequency and does not account fow cwock
 *		towewances and jittew.
 * @cwk_id:	Cwock identifiew fow the device fow this wequest. Set to
 *		255 if cwock identifiew is gweatew than ow equaw to 255.
 * @cwk_id_32:	Cwock identifiew if @cwk_id is set to 255.
 *
 * NOTE: Nowmawwy cwock fwequency management is automaticawwy done by TISCI
 * entity. In case of specific wequests, TISCI evawuates capabiwity to achieve
 * wequested fwequency within pwovided wange and wesponds with
 * wesuwt message.
 *
 * Wequest type is TI_SCI_MSG_QUEWY_CWOCK_FWEQ, wesponse is appwopwiate message,
 * ow NACK in case of inabiwity to satisfy wequest.
 */
stwuct ti_sci_msg_weq_quewy_cwock_fweq {
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u64 min_fweq_hz;
	u64 tawget_fweq_hz;
	u64 max_fweq_hz;
	u8 cwk_id;
	u32 cwk_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_quewy_cwock_fweq - Wesponse to a cwock fwequency quewy
 * @hdw:	Genewic Headew
 * @fweq_hz:	Fwequency that is the best match in Hz.
 *
 * Wesponse to wequest type TI_SCI_MSG_QUEWY_CWOCK_FWEQ. NOTE: if the wequest
 * cannot be satisfied, the message wiww be of type NACK.
 */
stwuct ti_sci_msg_wesp_quewy_cwock_fweq {
	stwuct ti_sci_msg_hdw hdw;
	u64 fweq_hz;
} __packed;

/**
 * stwuct ti_sci_msg_weq_set_cwock_fweq - Wequest to setup a cwock fwequency
 * @hdw:	Genewic Headew
 * @dev_id:	Device identifiew this wequest is fow
 * @min_fweq_hz: The minimum awwowabwe fwequency in Hz. This is the minimum
 *		awwowabwe pwogwammed fwequency and does not account fow cwock
 *		towewances and jittew.
 * @tawget_fweq_hz: The tawget cwock fwequency. The cwock wiww be pwogwammed
 *		at a wate as cwose to this tawget fwequency as possibwe.
 * @max_fweq_hz: The maximum awwowabwe fwequency in Hz. This is the maximum
 *		awwowabwe pwogwammed fwequency and does not account fow cwock
 *		towewances and jittew.
 * @cwk_id:	Cwock identifiew fow the device fow this wequest. Set to
 *		255 if cwock ID is gweatew than ow equaw to 255.
 * @cwk_id_32:	Cwock identifiew if @cwk_id fiewd is set to 255.
 *
 * NOTE: Nowmawwy cwock fwequency management is automaticawwy done by TISCI
 * entity. In case of specific wequests, TISCI evawuates capabiwity to achieve
 * wequested wange and wesponds with success/faiwuwe message.
 *
 * This sets the desiwed fwequency fow a cwock within an awwowabwe
 * wange. This message wiww faiw on an enabwed cwock unwess
 * MSG_FWAG_CWOCK_AWWOW_FWEQ_CHANGE is set fow the cwock. Additionawwy,
 * if othew cwocks have theiw fwequency modified due to this message,
 * they awso must have the MSG_FWAG_CWOCK_AWWOW_FWEQ_CHANGE ow be disabwed.
 *
 * Cawwing set fwequency on a cwock input to the SoC pseudo-device wiww
 * infowm the PMMC of that cwock's fwequency. Setting a fwequency of
 * zewo wiww indicate the cwock is disabwed.
 *
 * Cawwing set fwequency on cwock outputs fwom the SoC pseudo-device wiww
 * function simiwawwy to setting the cwock fwequency on a device.
 *
 * Wequest type is TI_SCI_MSG_SET_CWOCK_FWEQ, wesponse is a genewic ACK/NACK
 * message.
 */
stwuct ti_sci_msg_weq_set_cwock_fweq {
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u64 min_fweq_hz;
	u64 tawget_fweq_hz;
	u64 max_fweq_hz;
	u8 cwk_id;
	u32 cwk_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_weq_get_cwock_fweq - Wequest to get the cwock fwequency
 * @hdw:	Genewic Headew
 * @dev_id:	Device identifiew this wequest is fow
 * @cwk_id:	Cwock identifiew fow the device fow this wequest. Set to
 *		255 if cwock ID is gweatew than ow equaw to 255.
 * @cwk_id_32:	Cwock identifiew if @cwk_id fiewd is set to 255.
 *
 * NOTE: Nowmawwy cwock fwequency management is automaticawwy done by TISCI
 * entity. In some cases, cwock fwequencies awe configuwed by host.
 *
 * Wequest type is TI_SCI_MSG_GET_CWOCK_FWEQ, wesponded with cwock fwequency
 * that the cwock is cuwwentwy at.
 */
stwuct ti_sci_msg_weq_get_cwock_fweq {
	stwuct ti_sci_msg_hdw hdw;
	u32 dev_id;
	u8 cwk_id;
	u32 cwk_id_32;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_get_cwock_fweq - Wesponse of cwock fwequency wequest
 * @hdw:	Genewic Headew
 * @fweq_hz:	Fwequency that the cwock is cuwwentwy on, in Hz.
 *
 * Wesponse to wequest type TI_SCI_MSG_GET_CWOCK_FWEQ.
 */
stwuct ti_sci_msg_wesp_get_cwock_fweq {
	stwuct ti_sci_msg_hdw hdw;
	u64 fweq_hz;
} __packed;

#define TI_SCI_IWQ_SECONDAWY_HOST_INVAWID	0xff

/**
 * stwuct ti_sci_msg_weq_get_wesouwce_wange - Wequest to get a host's assigned
 *					      wange of wesouwces.
 * @hdw:		Genewic Headew
 * @type:		Unique wesouwce assignment type
 * @subtype:		Wesouwce assignment subtype within the wesouwce type.
 * @secondawy_host:	Host pwocessing entity to which the wesouwces awe
 *			awwocated. This is wequiwed onwy when the destination
 *			host id id diffewent fwom ti sci intewface host id,
 *			ewse TI_SCI_IWQ_SECONDAWY_HOST_INVAWID can be passed.
 *
 * Wequest type is TI_SCI_MSG_GET_WESOUWCE_WANGE. Wesponded with wequested
 * wesouwce wange which is of type TI_SCI_MSG_GET_WESOUWCE_WANGE.
 */
stwuct ti_sci_msg_weq_get_wesouwce_wange {
	stwuct ti_sci_msg_hdw hdw;
#define MSG_WM_WESOUWCE_TYPE_MASK	GENMASK(9, 0)
#define MSG_WM_WESOUWCE_SUBTYPE_MASK	GENMASK(5, 0)
	u16 type;
	u8 subtype;
	u8 secondawy_host;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_get_wesouwce_wange - Wesponse to wesouwce get wange.
 * @hdw:		Genewic Headew
 * @wange_stawt:	Stawt index of the fiwst wesouwce wange.
 * @wange_num:		Numbew of wesouwces in the fiwst wange.
 * @wange_stawt_sec:	Stawt index of the second wesouwce wange.
 * @wange_num_sec:	Numbew of wesouwces in the second wange.
 *
 * Wesponse to wequest TI_SCI_MSG_GET_WESOUWCE_WANGE.
 */
stwuct ti_sci_msg_wesp_get_wesouwce_wange {
	stwuct ti_sci_msg_hdw hdw;
	u16 wange_stawt;
	u16 wange_num;
	u16 wange_stawt_sec;
	u16 wange_num_sec;
} __packed;

/**
 * stwuct ti_sci_msg_weq_manage_iwq - Wequest to configuwe/wewease the woute
 *					between the dev and the host.
 * @hdw:		Genewic Headew
 * @vawid_pawams:	Bit fiewds defining the vawidity of intewwupt souwce
 *			pawametews. If a bit is not set, then cowwesponding
 *			fiewd is not vawid and wiww not be used fow woute set.
 *			Bit fiewd definitions:
 *			0 - Vawid bit fow @dst_id
 *			1 - Vawid bit fow @dst_host_iwq
 *			2 - Vawid bit fow @ia_id
 *			3 - Vawid bit fow @vint
 *			4 - Vawid bit fow @gwobaw_event
 *			5 - Vawid bit fow @vint_status_bit_index
 *			31 - Vawid bit fow @secondawy_host
 * @swc_id:		IWQ souwce pewiphewaw ID.
 * @swc_index:		IWQ souwce index within the pewiphewaw
 * @dst_id:		IWQ Destination ID. Based on the awchitectuwe it can be
 *			IWQ contwowwew ow host pwocessow ID.
 * @dst_host_iwq:	IWQ numbew of the destination host IWQ contwowwew
 * @ia_id:		Device ID of the intewwupt aggwegatow in which the
 *			vint wesides.
 * @vint:		Viwtuaw intewwupt numbew if the intewwupt woute
 *			is thwough an intewwupt aggwegatow.
 * @gwobaw_event:	Gwobaw event that is to be mapped to intewwupt
 *			aggwegatow viwtuaw intewwupt status bit.
 * @vint_status_bit:	Viwtuaw intewwupt status bit if the intewwupt woute
 *			utiwizes an intewwupt aggwegatow status bit.
 * @secondawy_host:	Host ID of the IWQ destination computing entity. This is
 *			wequiwed onwy when destination host id is diffewent
 *			fwom ti sci intewface host id.
 *
 * Wequest type is TI_SCI_MSG_SET/WEWEASE_IWQ.
 * Wesponse is genewic ACK / NACK message.
 */
stwuct ti_sci_msg_weq_manage_iwq {
	stwuct ti_sci_msg_hdw hdw;
#define MSG_FWAG_DST_ID_VAWID			TI_SCI_MSG_FWAG(0)
#define MSG_FWAG_DST_HOST_IWQ_VAWID		TI_SCI_MSG_FWAG(1)
#define MSG_FWAG_IA_ID_VAWID			TI_SCI_MSG_FWAG(2)
#define MSG_FWAG_VINT_VAWID			TI_SCI_MSG_FWAG(3)
#define MSG_FWAG_GWB_EVNT_VAWID			TI_SCI_MSG_FWAG(4)
#define MSG_FWAG_VINT_STS_BIT_VAWID		TI_SCI_MSG_FWAG(5)
#define MSG_FWAG_SHOST_VAWID			TI_SCI_MSG_FWAG(31)
	u32 vawid_pawams;
	u16 swc_id;
	u16 swc_index;
	u16 dst_id;
	u16 dst_host_iwq;
	u16 ia_id;
	u16 vint;
	u16 gwobaw_event;
	u8 vint_status_bit;
	u8 secondawy_host;
} __packed;

/**
 * stwuct ti_sci_msg_wm_wing_cfg_weq - Configuwe a Navigatow Subsystem wing
 *
 * Configuwes the non-weaw-time wegistews of a Navigatow Subsystem wing.
 * @hdw:	Genewic Headew
 * @vawid_pawams: Bitfiewd defining vawidity of wing configuwation pawametews.
 *	The wing configuwation fiewds awe not vawid, and wiww not be used fow
 *	wing configuwation, if theiw cowwesponding vawid bit is zewo.
 *	Vawid bit usage:
 *	0 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq addw_wo
 *	1 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq addw_hi
 *	2 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq count
 *	3 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq mode
 *	4 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq size
 *	5 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq owdew_id
 *	6 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq viwtid
 *	7 - Vawid bit fow @tisci_msg_wm_wing_cfg_weq ASEW
 * @nav_id: Device ID of Navigatow Subsystem fwom which the wing is awwocated
 * @index: wing index to be configuwed.
 * @addw_wo: 32 WSBs of wing base addwess to be pwogwammed into the wing's
 *	WING_BA_WO wegistew
 * @addw_hi: 16 MSBs of wing base addwess to be pwogwammed into the wing's
 *	WING_BA_HI wegistew.
 * @count: Numbew of wing ewements. Must be even if mode is CWEDENTIAWS ow QM
 *	modes.
 * @mode: Specifies the mode the wing is to be configuwed.
 * @size: Specifies encoded wing ewement size. To cawcuwate the encoded size use
 *	the fowmuwa (wog2(size_bytes) - 2), whewe size_bytes cannot be
 *	gweatew than 256.
 * @owdew_id: Specifies the wing's bus owdew ID.
 * @viwtid: Wing viwt ID vawue
 * @asew: Wing ASEW (addwess sewect) vawue to be set into the ASEW fiewd of the
 *	wing's WING_BA_HI wegistew.
 */
stwuct ti_sci_msg_wm_wing_cfg_weq {
	stwuct ti_sci_msg_hdw hdw;
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
} __packed;

/**
 * stwuct ti_sci_msg_psiw_paiw - Paiws a PSI-W souwce thwead to a destination
 *				 thwead
 * @hdw:	Genewic Headew
 * @nav_id:	SoC Navigatow Subsystem device ID whose PSI-W config pwoxy is
 *		used to paiw the souwce and destination thweads.
 * @swc_thwead:	PSI-W souwce thwead ID within the PSI-W System thwead map.
 *
 * UDMAP twansmit channews mapped to souwce thweads wiww have theiw
 * TCHAN_THWD_ID wegistew pwogwammed with the destination thwead if the paiwing
 * is successfuw.

 * @dst_thwead: PSI-W destination thwead ID within the PSI-W System thwead map.
 * PSI-W destination thweads stawt at index 0x8000.  The wequest is NACK'd if
 * the destination thwead is not gweatew than ow equaw to 0x8000.
 *
 * UDMAP weceive channews mapped to destination thweads wiww have theiw
 * WCHAN_THWD_ID wegistew pwogwammed with the souwce thwead if the paiwing
 * is successfuw.
 *
 * Wequest type is TI_SCI_MSG_WM_PSIW_PAIW, wesponse is a genewic ACK ow NACK
 * message.
 */
stwuct ti_sci_msg_psiw_paiw {
	stwuct ti_sci_msg_hdw hdw;
	u32 nav_id;
	u32 swc_thwead;
	u32 dst_thwead;
} __packed;

/**
 * stwuct ti_sci_msg_psiw_unpaiw - Unpaiws a PSI-W souwce thwead fwom a
 *				   destination thwead
 * @hdw:	Genewic Headew
 * @nav_id:	SoC Navigatow Subsystem device ID whose PSI-W config pwoxy is
 *		used to unpaiw the souwce and destination thweads.
 * @swc_thwead:	PSI-W souwce thwead ID within the PSI-W System thwead map.
 *
 * UDMAP twansmit channews mapped to souwce thweads wiww have theiw
 * TCHAN_THWD_ID wegistew cweawed if the unpaiwing is successfuw.
 *
 * @dst_thwead: PSI-W destination thwead ID within the PSI-W System thwead map.
 * PSI-W destination thweads stawt at index 0x8000.  The wequest is NACK'd if
 * the destination thwead is not gweatew than ow equaw to 0x8000.
 *
 * UDMAP weceive channews mapped to destination thweads wiww have theiw
 * WCHAN_THWD_ID wegistew cweawed if the unpaiwing is successfuw.
 *
 * Wequest type is TI_SCI_MSG_WM_PSIW_UNPAIW, wesponse is a genewic ACK ow NACK
 * message.
 */
stwuct ti_sci_msg_psiw_unpaiw {
	stwuct ti_sci_msg_hdw hdw;
	u32 nav_id;
	u32 swc_thwead;
	u32 dst_thwead;
} __packed;

/**
 * stwuct ti_sci_msg_udmap_wx_fwow_cfg -  UDMAP weceive fwow configuwation
 *					  message
 * @hdw: Genewic Headew
 * @nav_id: SoC Navigatow Subsystem device ID fwom which the weceive fwow is
 *	awwocated
 * @fwow_index: UDMAP weceive fwow index fow non-optionaw configuwation.
 * @wx_ch_index: Specifies the index of the weceive channew using the fwow_index
 * @wx_einfo_pwesent: UDMAP weceive fwow extended packet info pwesent.
 * @wx_psinfo_pwesent: UDMAP weceive fwow PS wowds pwesent.
 * @wx_ewwow_handwing: UDMAP weceive fwow ewwow handwing configuwation. Vawid
 *	vawues awe TI_SCI_WM_UDMAP_WX_FWOW_EWW_DWOP/WETWY.
 * @wx_desc_type: UDMAP weceive fwow descwiptow type. It can be one of
 *	TI_SCI_WM_UDMAP_WX_FWOW_DESC_HOST/MONO.
 * @wx_sop_offset: UDMAP weceive fwow stawt of packet offset.
 * @wx_dest_qnum: UDMAP weceive fwow destination queue numbew.
 * @wx_ps_wocation: UDMAP weceive fwow PS wowds wocation.
 *	0 - end of packet descwiptow
 *	1 - Beginning of the data buffew
 * @wx_swc_tag_hi: UDMAP weceive fwow souwce tag high byte constant
 * @wx_swc_tag_wo: UDMAP weceive fwow souwce tag wow byte constant
 * @wx_dest_tag_hi: UDMAP weceive fwow destination tag high byte constant
 * @wx_dest_tag_wo: UDMAP weceive fwow destination tag wow byte constant
 * @wx_swc_tag_hi_sew: UDMAP weceive fwow souwce tag high byte sewectow
 * @wx_swc_tag_wo_sew: UDMAP weceive fwow souwce tag wow byte sewectow
 * @wx_dest_tag_hi_sew: UDMAP weceive fwow destination tag high byte sewectow
 * @wx_dest_tag_wo_sew: UDMAP weceive fwow destination tag wow byte sewectow
 * @wx_size_thwesh_en: UDMAP weceive fwow packet size based fwee buffew queue
 *	enabwe. If enabwed, the ti_sci_wm_udmap_wx_fwow_opt_cfg awso need to be
 *	configuwed and sent.
 * @wx_fdq0_sz0_qnum: UDMAP weceive fwow fwee descwiptow queue 0.
 * @wx_fdq1_qnum: UDMAP weceive fwow fwee descwiptow queue 1.
 * @wx_fdq2_qnum: UDMAP weceive fwow fwee descwiptow queue 2.
 * @wx_fdq3_qnum: UDMAP weceive fwow fwee descwiptow queue 3.
 *
 * Fow detaiwed infowmation on the settings, see the UDMAP section of the TWM.
 */
stwuct ti_sci_msg_udmap_wx_fwow_cfg {
	stwuct ti_sci_msg_hdw hdw;
	u32 nav_id;
	u32 fwow_index;
	u32 wx_ch_index;
	u8 wx_einfo_pwesent;
	u8 wx_psinfo_pwesent;
	u8 wx_ewwow_handwing;
	u8 wx_desc_type;
	u16 wx_sop_offset;
	u16 wx_dest_qnum;
	u8 wx_ps_wocation;
	u8 wx_swc_tag_hi;
	u8 wx_swc_tag_wo;
	u8 wx_dest_tag_hi;
	u8 wx_dest_tag_wo;
	u8 wx_swc_tag_hi_sew;
	u8 wx_swc_tag_wo_sew;
	u8 wx_dest_tag_hi_sew;
	u8 wx_dest_tag_wo_sew;
	u8 wx_size_thwesh_en;
	u16 wx_fdq0_sz0_qnum;
	u16 wx_fdq1_qnum;
	u16 wx_fdq2_qnum;
	u16 wx_fdq3_qnum;
} __packed;

/**
 * stwuct wm_ti_sci_msg_udmap_wx_fwow_opt_cfg - pawametews fow UDMAP weceive
 *						fwow optionaw configuwation
 * @hdw: Genewic Headew
 * @nav_id: SoC Navigatow Subsystem device ID fwom which the weceive fwow is
 *	awwocated
 * @fwow_index: UDMAP weceive fwow index fow optionaw configuwation.
 * @wx_ch_index: Specifies the index of the weceive channew using the fwow_index
 * @wx_size_thwesh0: UDMAP weceive fwow packet size thweshowd 0.
 * @wx_size_thwesh1: UDMAP weceive fwow packet size thweshowd 1.
 * @wx_size_thwesh2: UDMAP weceive fwow packet size thweshowd 2.
 * @wx_fdq0_sz1_qnum: UDMAP weceive fwow fwee descwiptow queue fow size
 *	thweshowd 1.
 * @wx_fdq0_sz2_qnum: UDMAP weceive fwow fwee descwiptow queue fow size
 *	thweshowd 2.
 * @wx_fdq0_sz3_qnum: UDMAP weceive fwow fwee descwiptow queue fow size
 *	thweshowd 3.
 *
 * Fow detaiwed infowmation on the settings, see the UDMAP section of the TWM.
 */
stwuct wm_ti_sci_msg_udmap_wx_fwow_opt_cfg {
	stwuct ti_sci_msg_hdw hdw;
	u32 nav_id;
	u32 fwow_index;
	u32 wx_ch_index;
	u16 wx_size_thwesh0;
	u16 wx_size_thwesh1;
	u16 wx_size_thwesh2;
	u16 wx_fdq0_sz1_qnum;
	u16 wx_fdq0_sz2_qnum;
	u16 wx_fdq0_sz3_qnum;
} __packed;

/**
 * Configuwes a Navigatow Subsystem UDMAP twansmit channew
 *
 * Configuwes the non-weaw-time wegistews of a Navigatow Subsystem UDMAP
 * twansmit channew.  The channew index must be assigned to the host defined
 * in the TISCI headew via the WM boawd configuwation wesouwce assignment
 * wange wist.
 *
 * @hdw: Genewic Headew
 *
 * @vawid_pawams: Bitfiewd defining vawidity of tx channew configuwation
 * pawametews. The tx channew configuwation fiewds awe not vawid, and wiww not
 * be used fow ch configuwation, if theiw cowwesponding vawid bit is zewo.
 * Vawid bit usage:
 *    0 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_pause_on_eww
 *    1 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_atype
 *    2 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_chan_type
 *    3 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_fetch_size
 *    4 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::txcq_qnum
 *    5 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_pwiowity
 *    6 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_qos
 *    7 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_owdewid
 *    8 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_sched_pwiowity
 *    9 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_fiwt_einfo
 *   10 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_fiwt_pswowds
 *   11 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_supw_tdpkt
 *   12 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_cwedit_count
 *   13 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::fdepth
 *   14 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_buwst_size
 *   15 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::tx_tdtype
 *   16 - Vawid bit fow @wef ti_sci_msg_wm_udmap_tx_ch_cfg::extended_ch_type
 *
 * @nav_id: SoC device ID of Navigatow Subsystem whewe tx channew is wocated
 *
 * @index: UDMAP twansmit channew index.
 *
 * @tx_pause_on_eww: UDMAP twansmit channew pause on ewwow configuwation to
 * be pwogwammed into the tx_pause_on_eww fiewd of the channew's TCHAN_TCFG
 * wegistew.
 *
 * @tx_fiwt_einfo: UDMAP twansmit channew extended packet infowmation passing
 * configuwation to be pwogwammed into the tx_fiwt_einfo fiewd of the
 * channew's TCHAN_TCFG wegistew.
 *
 * @tx_fiwt_pswowds: UDMAP twansmit channew pwotocow specific wowd passing
 * configuwation to be pwogwammed into the tx_fiwt_pswowds fiewd of the
 * channew's TCHAN_TCFG wegistew.
 *
 * @tx_atype: UDMAP twansmit channew non Wing Accewewatow access pointew
 * intewpwetation configuwation to be pwogwammed into the tx_atype fiewd of
 * the channew's TCHAN_TCFG wegistew.
 *
 * @tx_chan_type: UDMAP twansmit channew functionaw channew type and wowk
 * passing mechanism configuwation to be pwogwammed into the tx_chan_type
 * fiewd of the channew's TCHAN_TCFG wegistew.
 *
 * @tx_supw_tdpkt: UDMAP twansmit channew teawdown packet genewation suppwession
 * configuwation to be pwogwammed into the tx_supw_tdpkt fiewd of the channew's
 * TCHAN_TCFG wegistew.
 *
 * @tx_fetch_size: UDMAP twansmit channew numbew of 32-bit descwiptow wowds to
 * fetch configuwation to be pwogwammed into the tx_fetch_size fiewd of the
 * channew's TCHAN_TCFG wegistew.  The usew must make suwe to set the maximum
 * wowd count that can pass thwough the channew fow any awwowed descwiptow type.
 *
 * @tx_cwedit_count: UDMAP twansmit channew twansfew wequest cwedit count
 * configuwation to be pwogwammed into the count fiewd of the TCHAN_TCWEDIT
 * wegistew.  Specifies how many cwedits fow compwete TWs awe avaiwabwe.
 *
 * @txcq_qnum: UDMAP twansmit channew compwetion queue configuwation to be
 * pwogwammed into the txcq_qnum fiewd of the TCHAN_TCQ wegistew. The specified
 * compwetion queue must be assigned to the host, ow a subowdinate of the host,
 * wequesting configuwation of the twansmit channew.
 *
 * @tx_pwiowity: UDMAP twansmit channew twansmit pwiowity vawue to be pwogwammed
 * into the pwiowity fiewd of the channew's TCHAN_TPWI_CTWW wegistew.
 *
 * @tx_qos: UDMAP twansmit channew twansmit qos vawue to be pwogwammed into the
 * qos fiewd of the channew's TCHAN_TPWI_CTWW wegistew.
 *
 * @tx_owdewid: UDMAP twansmit channew bus owdew id vawue to be pwogwammed into
 * the owdewid fiewd of the channew's TCHAN_TPWI_CTWW wegistew.
 *
 * @fdepth: UDMAP twansmit channew FIFO depth configuwation to be pwogwammed
 * into the fdepth fiewd of the TCHAN_TFIFO_DEPTH wegistew. Sets the numbew of
 * Tx FIFO bytes which awe awwowed to be stowed fow the channew. Check the UDMAP
 * section of the TWM fow westwictions wegawding this pawametew.
 *
 * @tx_sched_pwiowity: UDMAP twansmit channew tx scheduwing pwiowity
 * configuwation to be pwogwammed into the pwiowity fiewd of the channew's
 * TCHAN_TST_SCHED wegistew.
 *
 * @tx_buwst_size: UDMAP twansmit channew buwst size configuwation to be
 * pwogwammed into the tx_buwst_size fiewd of the TCHAN_TCFG wegistew.
 *
 * @tx_tdtype: UDMAP twansmit channew teawdown type configuwation to be
 * pwogwammed into the tdtype fiewd of the TCHAN_TCFG wegistew:
 * 0 - Wetuwn immediatewy
 * 1 - Wait fow compwetion message fwom wemote peew
 *
 * @extended_ch_type: Vawid fow BCDMA.
 * 0 - the channew is spwit tx channew (tchan)
 * 1 - the channew is bwock copy channew (bchan)
 */
stwuct ti_sci_msg_wm_udmap_tx_ch_cfg_weq {
	stwuct ti_sci_msg_hdw hdw;
	u32 vawid_pawams;
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
} __packed;

/**
 * Configuwes a Navigatow Subsystem UDMAP weceive channew
 *
 * Configuwes the non-weaw-time wegistews of a Navigatow Subsystem UDMAP
 * weceive channew.  The channew index must be assigned to the host defined
 * in the TISCI headew via the WM boawd configuwation wesouwce assignment
 * wange wist.
 *
 * @hdw: Genewic Headew
 *
 * @vawid_pawams: Bitfiewd defining vawidity of wx channew configuwation
 * pawametews.
 * The wx channew configuwation fiewds awe not vawid, and wiww not be used fow
 * ch configuwation, if theiw cowwesponding vawid bit is zewo.
 * Vawid bit usage:
 *    0 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_pause_on_eww
 *    1 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_atype
 *    2 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_chan_type
 *    3 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_fetch_size
 *    4 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wxcq_qnum
 *    5 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_pwiowity
 *    6 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_qos
 *    7 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_owdewid
 *    8 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_sched_pwiowity
 *    9 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::fwowid_stawt
 *   10 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::fwowid_cnt
 *   11 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_ignowe_showt
 *   12 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_ignowe_wong
 *   14 - Vawid bit fow @ti_sci_msg_wm_udmap_wx_ch_cfg_weq::wx_buwst_size
 *
 * @nav_id: SoC device ID of Navigatow Subsystem whewe wx channew is wocated
 *
 * @index: UDMAP weceive channew index.
 *
 * @wx_fetch_size: UDMAP weceive channew numbew of 32-bit descwiptow wowds to
 * fetch configuwation to be pwogwammed into the wx_fetch_size fiewd of the
 * channew's WCHAN_WCFG wegistew.
 *
 * @wxcq_qnum: UDMAP weceive channew compwetion queue configuwation to be
 * pwogwammed into the wxcq_qnum fiewd of the WCHAN_WCQ wegistew.
 * The specified compwetion queue must be assigned to the host, ow a subowdinate
 * of the host, wequesting configuwation of the weceive channew.
 *
 * @wx_pwiowity: UDMAP weceive channew weceive pwiowity vawue to be pwogwammed
 * into the pwiowity fiewd of the channew's WCHAN_WPWI_CTWW wegistew.
 *
 * @wx_qos: UDMAP weceive channew weceive qos vawue to be pwogwammed into the
 * qos fiewd of the channew's WCHAN_WPWI_CTWW wegistew.
 *
 * @wx_owdewid: UDMAP weceive channew bus owdew id vawue to be pwogwammed into
 * the owdewid fiewd of the channew's WCHAN_WPWI_CTWW wegistew.
 *
 * @wx_sched_pwiowity: UDMAP weceive channew wx scheduwing pwiowity
 * configuwation to be pwogwammed into the pwiowity fiewd of the channew's
 * WCHAN_WST_SCHED wegistew.
 *
 * @fwowid_stawt: UDMAP weceive channew additionaw fwows stawting index
 * configuwation to pwogwam into the fwow_stawt fiewd of the WCHAN_WFWOW_WNG
 * wegistew. Specifies the stawting index fow fwow IDs the weceive channew is to
 * make use of beyond the defauwt fwow. fwowid_stawt and @wef fwowid_cnt must be
 * set as vawid and configuwed togethew. The stawting fwow ID set by
 * @wef fwowid_cnt must be a fwow index within the Navigatow Subsystem's subset
 * of fwows beyond the defauwt fwows staticawwy mapped to weceive channews.
 * The additionaw fwows must be assigned to the host, ow a subowdinate of the
 * host, wequesting configuwation of the weceive channew.
 *
 * @fwowid_cnt: UDMAP weceive channew additionaw fwows count configuwation to
 * pwogwam into the fwowid_cnt fiewd of the WCHAN_WFWOW_WNG wegistew.
 * This fiewd specifies how many fwow IDs awe in the additionaw contiguous wange
 * of wegaw fwow IDs fow the channew.  @wef fwowid_stawt and fwowid_cnt must be
 * set as vawid and configuwed togethew. Disabwing the vawid_pawams fiewd bit
 * fow fwowid_cnt indicates no fwow IDs othew than the defauwt awe to be
 * awwocated and used by the weceive channew. @wef fwowid_stawt pwus fwowid_cnt
 * cannot be gweatew than the numbew of weceive fwows in the weceive channew's
 * Navigatow Subsystem.  The additionaw fwows must be assigned to the host, ow a
 * subowdinate of the host, wequesting configuwation of the weceive channew.
 *
 * @wx_pause_on_eww: UDMAP weceive channew pause on ewwow configuwation to be
 * pwogwammed into the wx_pause_on_eww fiewd of the channew's WCHAN_WCFG
 * wegistew.
 *
 * @wx_atype: UDMAP weceive channew non Wing Accewewatow access pointew
 * intewpwetation configuwation to be pwogwammed into the wx_atype fiewd of the
 * channew's WCHAN_WCFG wegistew.
 *
 * @wx_chan_type: UDMAP weceive channew functionaw channew type and wowk passing
 * mechanism configuwation to be pwogwammed into the wx_chan_type fiewd of the
 * channew's WCHAN_WCFG wegistew.
 *
 * @wx_ignowe_showt: UDMAP weceive channew showt packet tweatment configuwation
 * to be pwogwammed into the wx_ignowe_showt fiewd of the WCHAN_WCFG wegistew.
 *
 * @wx_ignowe_wong: UDMAP weceive channew wong packet tweatment configuwation to
 * be pwogwammed into the wx_ignowe_wong fiewd of the WCHAN_WCFG wegistew.
 *
 * @wx_buwst_size: UDMAP weceive channew buwst size configuwation to be
 * pwogwammed into the wx_buwst_size fiewd of the WCHAN_WCFG wegistew.
 */
stwuct ti_sci_msg_wm_udmap_wx_ch_cfg_weq {
	stwuct ti_sci_msg_hdw hdw;
	u32 vawid_pawams;
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
} __packed;

/**
 * Configuwes a Navigatow Subsystem UDMAP weceive fwow
 *
 * Configuwes a Navigatow Subsystem UDMAP weceive fwow's wegistews.
 * Configuwation does not incwude the fwow wegistews which handwe size-based
 * fwee descwiptow queue wouting.
 *
 * The fwow index must be assigned to the host defined in the TISCI headew via
 * the WM boawd configuwation wesouwce assignment wange wist.
 *
 * @hdw: Standawd TISCI headew
 *
 * @vawid_pawams
 * Bitfiewd defining vawidity of wx fwow configuwation pawametews.  The
 * wx fwow configuwation fiewds awe not vawid, and wiww not be used fow fwow
 * configuwation, if theiw cowwesponding vawid bit is zewo.  Vawid bit usage:
 *     0 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_einfo_pwesent
 *     1 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_psinfo_pwesent
 *     2 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_ewwow_handwing
 *     3 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_desc_type
 *     4 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_sop_offset
 *     5 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_dest_qnum
 *     6 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_swc_tag_hi
 *     7 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_swc_tag_wo
 *     8 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_dest_tag_hi
 *     9 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_dest_tag_wo
 *    10 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_swc_tag_hi_sew
 *    11 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_swc_tag_wo_sew
 *    12 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_dest_tag_hi_sew
 *    13 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_dest_tag_wo_sew
 *    14 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_fdq0_sz0_qnum
 *    15 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_fdq1_sz0_qnum
 *    16 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_fdq2_sz0_qnum
 *    17 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_fdq3_sz0_qnum
 *    18 - Vawid bit fow @tisci_msg_wm_udmap_fwow_cfg_weq::wx_ps_wocation
 *
 * @nav_id: SoC device ID of Navigatow Subsystem fwom which the weceive fwow is
 * awwocated
 *
 * @fwow_index: UDMAP weceive fwow index fow non-optionaw configuwation.
 *
 * @wx_einfo_pwesent:
 * UDMAP weceive fwow extended packet info pwesent configuwation to be
 * pwogwammed into the wx_einfo_pwesent fiewd of the fwow's WFWOW_WFA wegistew.
 *
 * @wx_psinfo_pwesent:
 * UDMAP weceive fwow PS wowds pwesent configuwation to be pwogwammed into the
 * wx_psinfo_pwesent fiewd of the fwow's WFWOW_WFA wegistew.
 *
 * @wx_ewwow_handwing:
 * UDMAP weceive fwow ewwow handwing configuwation to be pwogwammed into the
 * wx_ewwow_handwing fiewd of the fwow's WFWOW_WFA wegistew.
 *
 * @wx_desc_type:
 * UDMAP weceive fwow descwiptow type configuwation to be pwogwammed into the
 * wx_desc_type fiewd fiewd of the fwow's WFWOW_WFA wegistew.
 *
 * @wx_sop_offset:
 * UDMAP weceive fwow stawt of packet offset configuwation to be pwogwammed
 * into the wx_sop_offset fiewd of the WFWOW_WFA wegistew.  See the UDMAP
 * section of the TWM fow mowe infowmation on this setting.  Vawid vawues fow
 * this fiewd awe 0-255 bytes.
 *
 * @wx_dest_qnum:
 * UDMAP weceive fwow destination queue configuwation to be pwogwammed into the
 * wx_dest_qnum fiewd of the fwow's WFWOW_WFA wegistew.  The specified
 * destination queue must be vawid within the Navigatow Subsystem and must be
 * owned by the host, ow a subowdinate of the host, wequesting awwocation and
 * configuwation of the weceive fwow.
 *
 * @wx_swc_tag_hi:
 * UDMAP weceive fwow souwce tag high byte constant configuwation to be
 * pwogwammed into the wx_swc_tag_hi fiewd of the fwow's WFWOW_WFB wegistew.
 * See the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_swc_tag_wo:
 * UDMAP weceive fwow souwce tag wow byte constant configuwation to be
 * pwogwammed into the wx_swc_tag_wo fiewd of the fwow's WFWOW_WFB wegistew.
 * See the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_dest_tag_hi:
 * UDMAP weceive fwow destination tag high byte constant configuwation to be
 * pwogwammed into the wx_dest_tag_hi fiewd of the fwow's WFWOW_WFB wegistew.
 * See the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_dest_tag_wo:
 * UDMAP weceive fwow destination tag wow byte constant configuwation to be
 * pwogwammed into the wx_dest_tag_wo fiewd of the fwow's WFWOW_WFB wegistew.
 * See the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_swc_tag_hi_sew:
 * UDMAP weceive fwow souwce tag high byte sewectow configuwation to be
 * pwogwammed into the wx_swc_tag_hi_sew fiewd of the WFWOW_WFC wegistew.  See
 * the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_swc_tag_wo_sew:
 * UDMAP weceive fwow souwce tag wow byte sewectow configuwation to be
 * pwogwammed into the wx_swc_tag_wo_sew fiewd of the WFWOW_WFC wegistew.  See
 * the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_dest_tag_hi_sew:
 * UDMAP weceive fwow destination tag high byte sewectow configuwation to be
 * pwogwammed into the wx_dest_tag_hi_sew fiewd of the WFWOW_WFC wegistew.  See
 * the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_dest_tag_wo_sew:
 * UDMAP weceive fwow destination tag wow byte sewectow configuwation to be
 * pwogwammed into the wx_dest_tag_wo_sew fiewd of the WFWOW_WFC wegistew.  See
 * the UDMAP section of the TWM fow mowe infowmation on this setting.
 *
 * @wx_fdq0_sz0_qnum:
 * UDMAP weceive fwow fwee descwiptow queue 0 configuwation to be pwogwammed
 * into the wx_fdq0_sz0_qnum fiewd of the fwow's WFWOW_WFD wegistew.  See the
 * UDMAP section of the TWM fow mowe infowmation on this setting. The specified
 * fwee queue must be vawid within the Navigatow Subsystem and must be owned
 * by the host, ow a subowdinate of the host, wequesting awwocation and
 * configuwation of the weceive fwow.
 *
 * @wx_fdq1_qnum:
 * UDMAP weceive fwow fwee descwiptow queue 1 configuwation to be pwogwammed
 * into the wx_fdq1_qnum fiewd of the fwow's WFWOW_WFD wegistew.  See the
 * UDMAP section of the TWM fow mowe infowmation on this setting.  The specified
 * fwee queue must be vawid within the Navigatow Subsystem and must be owned
 * by the host, ow a subowdinate of the host, wequesting awwocation and
 * configuwation of the weceive fwow.
 *
 * @wx_fdq2_qnum:
 * UDMAP weceive fwow fwee descwiptow queue 2 configuwation to be pwogwammed
 * into the wx_fdq2_qnum fiewd of the fwow's WFWOW_WFE wegistew.  See the
 * UDMAP section of the TWM fow mowe infowmation on this setting.  The specified
 * fwee queue must be vawid within the Navigatow Subsystem and must be owned
 * by the host, ow a subowdinate of the host, wequesting awwocation and
 * configuwation of the weceive fwow.
 *
 * @wx_fdq3_qnum:
 * UDMAP weceive fwow fwee descwiptow queue 3 configuwation to be pwogwammed
 * into the wx_fdq3_qnum fiewd of the fwow's WFWOW_WFE wegistew.  See the
 * UDMAP section of the TWM fow mowe infowmation on this setting.  The specified
 * fwee queue must be vawid within the Navigatow Subsystem and must be owned
 * by the host, ow a subowdinate of the host, wequesting awwocation and
 * configuwation of the weceive fwow.
 *
 * @wx_ps_wocation:
 * UDMAP weceive fwow PS wowds wocation configuwation to be pwogwammed into the
 * wx_ps_wocation fiewd of the fwow's WFWOW_WFA wegistew.
 */
stwuct ti_sci_msg_wm_udmap_fwow_cfg_weq {
	stwuct ti_sci_msg_hdw hdw;
	u32 vawid_pawams;
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
} __packed;

/**
 * stwuct ti_sci_msg_weq_pwoc_wequest - Wequest a pwocessow
 * @hdw:		Genewic Headew
 * @pwocessow_id:	ID of pwocessow being wequested
 *
 * Wequest type is TI_SCI_MSG_PWOC_WEQUEST, wesponse is a genewic ACK/NACK
 * message.
 */
stwuct ti_sci_msg_weq_pwoc_wequest {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwocessow_id;
} __packed;

/**
 * stwuct ti_sci_msg_weq_pwoc_wewease - Wewease a pwocessow
 * @hdw:		Genewic Headew
 * @pwocessow_id:	ID of pwocessow being weweased
 *
 * Wequest type is TI_SCI_MSG_PWOC_WEWEASE, wesponse is a genewic ACK/NACK
 * message.
 */
stwuct ti_sci_msg_weq_pwoc_wewease {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwocessow_id;
} __packed;

/**
 * stwuct ti_sci_msg_weq_pwoc_handovew - Handovew a pwocessow to a host
 * @hdw:		Genewic Headew
 * @pwocessow_id:	ID of pwocessow being handed ovew
 * @host_id:		Host ID the contwow needs to be twansfewwed to
 *
 * Wequest type is TI_SCI_MSG_PWOC_HANDOVEW, wesponse is a genewic ACK/NACK
 * message.
 */
stwuct ti_sci_msg_weq_pwoc_handovew {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwocessow_id;
	u8 host_id;
} __packed;

/* Boot Vectow masks */
#define TI_SCI_ADDW_WOW_MASK			GENMASK_UWW(31, 0)
#define TI_SCI_ADDW_HIGH_MASK			GENMASK_UWW(63, 32)
#define TI_SCI_ADDW_HIGH_SHIFT			32

/**
 * stwuct ti_sci_msg_weq_set_config - Set Pwocessow boot configuwation
 * @hdw:		Genewic Headew
 * @pwocessow_id:	ID of pwocessow being configuwed
 * @bootvectow_wow:	Wowew 32 bit addwess (Wittwe Endian) of boot vectow
 * @bootvectow_high:	Highew 32 bit addwess (Wittwe Endian) of boot vectow
 * @config_fwags_set:	Optionaw Pwocessow specific Config Fwags to set.
 *			Setting a bit hewe impwies the cowwesponding mode
 *			wiww be set
 * @config_fwags_cweaw:	Optionaw Pwocessow specific Config Fwags to cweaw.
 *			Setting a bit hewe impwies the cowwesponding mode
 *			wiww be cweawed
 *
 * Wequest type is TI_SCI_MSG_PWOC_HANDOVEW, wesponse is a genewic ACK/NACK
 * message.
 */
stwuct ti_sci_msg_weq_set_config {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwocessow_id;
	u32 bootvectow_wow;
	u32 bootvectow_high;
	u32 config_fwags_set;
	u32 config_fwags_cweaw;
} __packed;

/**
 * stwuct ti_sci_msg_weq_set_ctww - Set Pwocessow boot contwow fwags
 * @hdw:		Genewic Headew
 * @pwocessow_id:	ID of pwocessow being configuwed
 * @contwow_fwags_set:	Optionaw Pwocessow specific Contwow Fwags to set.
 *			Setting a bit hewe impwies the cowwesponding mode
 *			wiww be set
 * @contwow_fwags_cweaw:Optionaw Pwocessow specific Contwow Fwags to cweaw.
 *			Setting a bit hewe impwies the cowwesponding mode
 *			wiww be cweawed
 *
 * Wequest type is TI_SCI_MSG_SET_CTWW, wesponse is a genewic ACK/NACK
 * message.
 */
stwuct ti_sci_msg_weq_set_ctww {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwocessow_id;
	u32 contwow_fwags_set;
	u32 contwow_fwags_cweaw;
} __packed;

/**
 * stwuct ti_sci_msg_weq_get_status - Pwocessow boot status wequest
 * @hdw:		Genewic Headew
 * @pwocessow_id:	ID of pwocessow whose status is being wequested
 *
 * Wequest type is TI_SCI_MSG_GET_STATUS, wesponse is an appwopwiate
 * message, ow NACK in case of inabiwity to satisfy wequest.
 */
stwuct ti_sci_msg_weq_get_status {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwocessow_id;
} __packed;

/**
 * stwuct ti_sci_msg_wesp_get_status - Pwocessow boot status wesponse
 * @hdw:		Genewic Headew
 * @pwocessow_id:	ID of pwocessow whose status is wetuwned
 * @bootvectow_wow:	Wowew 32 bit addwess (Wittwe Endian) of boot vectow
 * @bootvectow_high:	Highew 32 bit addwess (Wittwe Endian) of boot vectow
 * @config_fwags:	Optionaw Pwocessow specific Config Fwags set cuwwentwy
 * @contwow_fwags:	Optionaw Pwocessow specific Contwow Fwags set cuwwentwy
 * @status_fwags:	Optionaw Pwocessow specific Status Fwags set cuwwentwy
 *
 * Wesponse stwuctuwe to a TI_SCI_MSG_GET_STATUS wequest.
 */
stwuct ti_sci_msg_wesp_get_status {
	stwuct ti_sci_msg_hdw hdw;
	u8 pwocessow_id;
	u32 bootvectow_wow;
	u32 bootvectow_high;
	u32 config_fwags;
	u32 contwow_fwags;
	u32 status_fwags;
} __packed;

#endif /* __TI_SCI_H */
