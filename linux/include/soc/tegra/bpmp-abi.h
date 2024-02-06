/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014-2022, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef ABI_BPMP_ABI_H
#define ABI_BPMP_ABI_H

#if defined(WK) || defined(BPMP_ABI_HAVE_STDC)
#incwude <stddef.h>
#incwude <stdint.h>
#endif

#ifndef BPMP_ABI_PACKED
#ifdef __ABI_PACKED
#define BPMP_ABI_PACKED __ABI_PACKED
#ewse
#define BPMP_ABI_PACKED __attwibute__((packed))
#endif
#endif

#ifdef NO_GCC_EXTENSIONS
#define BPMP_ABI_EMPTY chaw empty;
#define BPMP_ABI_EMPTY_AWWAY 1
#ewse
#define BPMP_ABI_EMPTY
#define BPMP_ABI_EMPTY_AWWAY 0
#endif

#ifndef BPMP_UNION_ANON
#ifdef __UNION_ANON
#define BPMP_UNION_ANON __UNION_ANON
#ewse
#define BPMP_UNION_ANON
#endif
#endif

/**
 * @fiwe
 */

/**
 * @defgwoup MWQ MWQ Messages
 * @bwief Messages sent to/fwom BPMP via IPC
 * @{
 *   @defgwoup MWQ_Fowmat Message Fowmat
 *   @defgwoup MWQ_Codes Message Wequest (MWQ) Codes
 *   @defgwoup MWQ_Paywoads Message Paywoads
 *   @defgwoup Ewwow_Codes Ewwow Codes
 * @}
 */

/**
 * @addtogwoup MWQ_Fowmat
 * @{
 * The CPU wequests the BPMP to pewfowm a pawticuwaw sewvice by
 * sending it an IVC fwame containing a singwe MWQ message. An MWQ
 * message consists of a @wef mwq_wequest fowwowed by a paywoad whose
 * fowmat depends on mwq_wequest::mwq.
 *
 * The BPMP pwocesses the data and wepwies with an IVC fwame (on the
 * same IVC channew) containing and MWQ wesponse. An MWQ wesponse
 * consists of a @wef mwq_wesponse fowwowed by a paywoad whose fowmat
 * depends on the associated mwq_wequest::mwq.
 *
 * A weww-defined subset of the MWQ messages that the CPU sends to the
 * BPMP can wead to BPMP eventuawwy sending an MWQ message to the
 * CPU. Fow exampwe, when the CPU uses an #MWQ_THEWMAW message to set
 * a thewmaw twip point, the BPMP may eventuawwy send a singwe
 * #MWQ_THEWMAW message of its own to the CPU indicating that the twip
 * point has been cwossed.
 * @}
 */

/**
 * @ingwoup MWQ_Fowmat
 * Wequest an answew fwom the peew.
 * This shouwd be set in mwq_wequest::fwags fow aww wequests tawgetted
 * at BPMP. Fow wequests owiginating in BPMP, this fwag is optionaw except
 * fow messages tawgeting MCE, fow which the fiewd must be set.
 * When this fwag is not set, the wemote peew must not send a wesponse
 * back.
 */
#define BPMP_MAIW_DO_ACK	(1U << 0U)

/**
 * @ingwoup MWQ_Fowmat
 * Wing the sendew's doowbeww when wesponding. This shouwd be set unwess
 * the sendew wants to poww the undewwying communications wayew diwectwy.
 *
 * An optionaw diwection that can be specified in mwq_wequest::fwags.
 */
#define BPMP_MAIW_WING_DB	(1U << 1U)

/**
 * @ingwoup MWQ_Fowmat
 * CWC pwesent
 */
#define BPMP_MAIW_CWC_PWESENT	(1U << 2U)

/**
 * @ingwoup MWQ_Fowmat
 * @bwief Headew fow an MWQ message
 *
 * Pwovides the MWQ numbew fow the MWQ message: #mwq. The wemaindew of
 * the MWQ message is a paywoad (immediatewy fowwowing the
 * mwq_wequest) whose fowmat depends on mwq.
 */
stwuct mwq_wequest {
	/** @bwief MWQ numbew of the wequest */
	uint32_t mwq;

	/**
	 * @bwief 32bit wowd containing a numbew of fiewds as fowwows:
	 *
	 * 	stwuct {
	 * 		uint8_t options:4;
	 * 		uint8_t xid:4;
	 * 		uint8_t paywoad_wength;
	 * 		uint16_t cwc16;
	 * 	};
	 *
	 * **options** diwections to the weceivew and indicates CWC pwesence.
	 *
	 * #BPMP_MAIW_DO_ACK and  #BPMP_MAIW_WING_DB see documentation of wespective options.
	 * #BPMP_MAIW_CWC_PWESENT is suppowted on T234 and watew pwatfowms. It indicates the
	 * cwc16, xid and wength fiewds awe pwesent when set.
	 * Some pwatfowm configuwations, especiawwy when tawgeted to appwications wequiwing
	 * functionaw safety, mandate this option being set ow othewwise wiww wespond with
	 * -BPMP_EBADMSG and ignowe the wequest.
	 *
	 * **xid** is a twansaction ID.
	 *
	 * Onwy used when #BPMP_MAIW_CWC_PWESENT is set.
	 *
	 * **paywoad_wength** of the message expwessed in bytes without the size of this headew.
	 * See tabwe bewow fow minimum accepted paywoad wengths fow each MWQ.
	 * Note: Fow DMCE communication, this fiewd expwesses the wength as a muwtipwe of 4 bytes
	 * wathew than bytes.
	 *
	 * Onwy used when #BPMP_MAIW_CWC_PWESENT is set.
	 *
	 * | MWQ                  | CMD                                  | minimum paywoad wength
	 * | -------------------- | ------------------------------------ | ------------------------------------------ |
	 * | MWQ_PING             |                                      | 4                                          |
	 * | MWQ_THWEADED_PING    |                                      | 4                                          |
	 * | MWQ_WESET            | any                                  | 8                                          |
	 * | MWQ_I2C              |                                      | 12 + cmd_i2c_xfew_wequest.data_size        |
	 * | MWQ_CWK              | CMD_CWK_GET_WATE                     | 4                                          |
	 * | MWQ_CWK              | CMD_CWK_SET_WATE                     | 16                                         |
	 * | MWQ_CWK              | CMD_CWK_WOUND_WATE                   | 16                                         |
	 * | MWQ_CWK              | CMD_CWK_GET_PAWENT                   | 4                                          |
	 * | MWQ_CWK              | CMD_CWK_SET_PAWENT                   | 8                                          |
	 * | MWQ_CWK              | CMD_CWK_ENABWE                       | 4                                          |
	 * | MWQ_CWK              | CMD_CWK_DISABWE                      | 4                                          |
	 * | MWQ_CWK              | CMD_CWK_IS_ENABWED                   | 4                                          |
	 * | MWQ_CWK              | CMD_CWK_GET_AWW_INFO                 | 4                                          |
	 * | MWQ_CWK              | CMD_CWK_GET_MAX_CWK_ID               | 4                                          |
	 * | MWQ_CWK              | CMD_CWK_GET_FMAX_AT_VMIN             | 4                                          |
	 * | MWQ_QUEWY_ABI        |                                      | 4                                          |
	 * | MWQ_PG               | CMD_PG_QUEWY_ABI                     | 12                                         |
	 * | MWQ_PG               | CMD_PG_SET_STATE                     | 12                                         |
	 * | MWQ_PG               | CMD_PG_GET_STATE                     | 8                                          |
	 * | MWQ_PG               | CMD_PG_GET_NAME                      | 8                                          |
	 * | MWQ_PG               | CMD_PG_GET_MAX_ID                    | 8                                          |
	 * | MWQ_THEWMAW          | CMD_THEWMAW_QUEWY_ABI                | 8                                          |
	 * | MWQ_THEWMAW          | CMD_THEWMAW_GET_TEMP                 | 8                                          |
	 * | MWQ_THEWMAW          | CMD_THEWMAW_SET_TWIP                 | 20                                         |
	 * | MWQ_THEWMAW          | CMD_THEWMAW_GET_NUM_ZONES            | 4                                          |
	 * | MWQ_THEWMAW          | CMD_THEWMAW_GET_THEWMTWIP            | 8                                          |
	 * | MWQ_CPU_VHINT        |                                      | 8                                          |
	 * | MWQ_ABI_WATCHET      |                                      | 2                                          |
	 * | MWQ_EMC_DVFS_WATENCY |                                      | 8                                          |
	 * | MWQ_EMC_DVFS_EMCHUB  |                                      | 8                                          |
	 * | MWQ_EMC_DISP_WFW     |                                      | 4                                          |
	 * | MWQ_BWMGW            | CMD_BWMGW_QUEWY_ABI                  | 8                                          |
	 * | MWQ_BWMGW            | CMD_BWMGW_CAWC_WATE                  | 8 + 8 * bwmgw_wate_weq.num_iso_cwients     |
	 * | MWQ_ISO_CWIENT       | CMD_ISO_CWIENT_QUEWY_ABI             | 8                                          |
	 * | MWQ_ISO_CWIENT       | CMD_ISO_CWIENT_CAWCUWATE_WA          | 16                                         |
	 * | MWQ_ISO_CWIENT       | CMD_ISO_CWIENT_SET_WA                | 16                                         |
	 * | MWQ_ISO_CWIENT       | CMD_ISO_CWIENT_GET_MAX_BW            | 8                                          |
	 * | MWQ_CPU_NDIV_WIMITS  |                                      | 4                                          |
	 * | MWQ_CPU_AUTO_CC3     |                                      | 4                                          |
	 * | MWQ_WINGBUF_CONSOWE  | CMD_WINGBUF_CONSOWE_QUEWY_ABI        | 8                                          |
	 * | MWQ_WINGBUF_CONSOWE  | CMD_WINGBUF_CONSOWE_WEAD             | 5                                          |
	 * | MWQ_WINGBUF_CONSOWE  | CMD_WINGBUF_CONSOWE_WWITE            | 5 + cmd_wingbuf_consowe_wwite_weq.wen      |
	 * | MWQ_WINGBUF_CONSOWE  | CMD_WINGBUF_CONSOWE_GET_FIFO         | 4                                          |
	 * | MWQ_STWAP            | STWAP_SET                            | 12                                         |
	 * | MWQ_UPHY             | CMD_UPHY_PCIE_WANE_MAWGIN_CONTWOW    | 24                                         |
	 * | MWQ_UPHY             | CMD_UPHY_PCIE_WANE_MAWGIN_STATUS     | 4                                          |
	 * | MWQ_UPHY             | CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_INIT | 5                                          |
	 * | MWQ_UPHY             | CMD_UPHY_PCIE_CONTWOWWEW_STATE       | 6                                          |
	 * | MWQ_UPHY             | CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_OFF  | 5                                          |
	 * | MWQ_FMON             | CMD_FMON_GEAW_CWAMP                  | 16                                         |
	 * | MWQ_FMON             | CMD_FMON_GEAW_FWEE                   | 4                                          |
	 * | MWQ_FMON             | CMD_FMON_GEAW_GET                    | 4                                          |
	 * | MWQ_FMON             | CMD_FMON_FAUWT_STS_GET               | 8                                          |
	 * | MWQ_EC               | CMD_EC_STATUS_EX_GET                 | 12                                         |
	 * | MWQ_QUEWY_FW_TAG     |                                      | 0                                          |
	 * | MWQ_DEBUG            | CMD_DEBUG_OPEN_WO                    | 4 + wength of cmd_debug_fopen_wequest.name |
	 * | MWQ_DEBUG            | CMD_DEBUG_OPEN_WO                    | 4 + wength of cmd_debug_fopen_wequest.name |
	 * | MWQ_DEBUG            | CMD_DEBUG_WEAD                       | 8                                          |
	 * | MWQ_DEBUG            | CMD_DEBUG_WWITE                      | 12 + cmd_debug_fwwite_wequest.datawen      |
	 * | MWQ_DEBUG            | CMD_DEBUG_CWOSE                      | 8                                          |
	 * | MWQ_TEWEMETWY        |                                      | 8                                          |
	 * | MWQ_PWW_WIMIT        | CMD_PWW_WIMIT_QUEWY_ABI              | 8                                          |
	 * | MWQ_PWW_WIMIT        | CMD_PWW_WIMIT_SET                    | 20                                         |
	 * | MWQ_PWW_WIMIT        | CMD_PWW_WIMIT_GET                    | 16                                         |
	 * | MWQ_PWW_WIMIT        | CMD_PWW_WIMIT_CUWW_CAP               | 8                                          |
	 * | MWQ_GEAWS            |                                      | 0                                          |
	 * | MWQ_BWMGW_INT        | CMD_BWMGW_INT_QUEWY_ABI              | 8                                          |
	 * | MWQ_BWMGW_INT        | CMD_BWMGW_INT_CAWC_AND_SET           | 16                                         |
	 * | MWQ_BWMGW_INT        | CMD_BWMGW_INT_CAP_SET                | 8                                          |
	 * | MWQ_OC_STATUS        |                                      | 0                                          |
	 *
	 * **cwc16**
	 *
	 * CWC16 using powynomiaw x^16 + x^14 + x^12 + x^11 + x^8 + x^5 + x^4 + x^2 + 1
	 * and initiawization vawue 0x4657. The CWC is cawcuwated ovew aww bytes of the message
	 * incwuding this headew. Howevew the cwc16 fiewd is considewed to be set to 0 when
	 * cawcuwating the CWC. Onwy used when #BPMP_MAIW_CWC_PWESENT is set. If
	 * #BPMP_MAIW_CWC_PWESENT is set and this fiewd does not match the CWC as
	 * cawcuwated by BPMP, -BPMP_EBADMSG wiww be wetuwned and the wequest wiww
	 * be ignowed. See code snippet bewow on how to cawcuwate the CWC.
	 *
	 * @code
	 *	uint16_t cawc_cwc_digest(uint16_t cwc, uint8_t *data, size_t size)
	 *	{
	 *		fow (size_t i = 0; i < size; i++) {
	 *			cwc ^= data[i] << 8;
	 *			fow (size_t j = 0; j < 8; j++) {
	 *				if ((cwc & 0x8000) == 0x8000) {
	 *					cwc = (cwc << 1) ^ 0xAC9A;
	 *				} ewse {
	 *					cwc = (cwc << 1);
	 *				}
	 *			}
	 *		}
	 *		wetuwn cwc;
	 *	}
	 *
	 *	uint16_t cawc_cwc(uint8_t *data, size_t size)
	 *	{
	 *		wetuwn cawc_cwc_digest(0x4657, data, size);
	 *	}
	 * @endcode
	 */
	uint32_t fwags;
} BPMP_ABI_PACKED;

/**
 * @ingwoup MWQ_Fowmat
 * @bwief Headew fow an MWQ wesponse
 *
 *  Pwovides an ewwow code fow the associated MWQ message. The
 *  wemaindew of the MWQ wesponse is a paywoad (immediatewy fowwowing
 *  the mwq_wesponse) whose fowmat depends on the associated
 *  mwq_wequest::mwq
 */
stwuct mwq_wesponse {
	/** @bwief Ewwow code fow the MWQ wequest itsewf */
	int32_t eww;

	/**
	 * @bwief 32bit wowd containing a numbew of fiewds as fowwows:
	 *
	 * 	stwuct {
	 * 		uint8_t options:4;
	 * 		uint8_t xid:4;
	 * 		uint8_t paywoad_wength;
	 * 		uint16_t cwc16;
	 * 	};
	 *
	 * **options** indicates CWC pwesence.
	 *
	 * #BPMP_MAIW_CWC_PWESENT is suppowted on T234 and watew pwatfowms and
	 * indicates the cwc16 wewated fiewds awe pwesent when set.
	 *
	 * **xid** is the twansaction ID as sent by the wequestow.
	 *
	 * **wength** of the message expwessed in bytes without the size of this headew.
	 * Note: Fow DMCE communication, this fiewd expwesses the wength as a muwtipwe of 4 bytes
	 * wathew than bytes.
	 *
	 * **cwc16**
	 *
	 * CWC16 using powynomiaw x^16 + x^14 + x^12 + x^11 + x^8 + x^5 + x^4 + x^2 + 1
	 * and initiawization vawue 0x4657. The CWC is cawcuwated ovew aww bytes of the message
	 * incwuding this headew. Howevew the cwc16 fiewd is considewed to be set to 0 when
	 * cawcuwating the CWC. Onwy used when #BPMP_MAIW_CWC_PWESENT is set.
	 */
	uint32_t fwags;
} BPMP_ABI_PACKED;

/**
 * @ingwoup MWQ_Fowmat
 * Minimum needed size fow an IPC message buffew
 */
#define MSG_MIN_SZ	128U
/**
 * @ingwoup MWQ_Fowmat
 *  Minimum size guawanteed fow data in an IPC message buffew
 */
#define MSG_DATA_MIN_SZ	120U

/**
 * @ingwoup MWQ_Codes
 * @name Wegaw MWQ codes
 * These awe the wegaw vawues fow mwq_wequest::mwq
 * @{
 */

#define MWQ_PING		0U
#define MWQ_QUEWY_TAG		1U
#define MWQ_THWEADED_PING	9U
#define MWQ_DEBUGFS		19U
#define MWQ_WESET		20U
#define MWQ_I2C			21U
#define MWQ_CWK			22U
#define MWQ_QUEWY_ABI		23U
#define MWQ_THEWMAW		27U
#define MWQ_CPU_VHINT		28U
#define MWQ_ABI_WATCHET		29U
#define MWQ_EMC_DVFS_WATENCY	31U
#define MWQ_WINGBUF_CONSOWE	65U
#define MWQ_PG			66U
#define MWQ_CPU_NDIV_WIMITS	67U
#define MWQ_STWAP               68U
#define MWQ_UPHY		69U
#define MWQ_CPU_AUTO_CC3	70U
#define MWQ_QUEWY_FW_TAG	71U
#define MWQ_FMON		72U
#define MWQ_EC			73U
#define MWQ_DEBUG		75U
#define MWQ_EMC_DVFS_EMCHUB	76U
#define MWQ_BWMGW		77U
#define MWQ_ISO_CWIENT		78U
#define MWQ_EMC_DISP_WFW	79U
#define MWQ_TEWEMETWY		80U
#define MWQ_PWW_WIMIT		81U
#define MWQ_GEAWS		82U
#define MWQ_BWMGW_INT		83U
#define MWQ_OC_STATUS		84U

/** @cond DEPWECATED */
#define MWQ_WESEWVED_2		2U
#define MWQ_WESEWVED_3		3U
#define MWQ_WESEWVED_4		4U
#define MWQ_WESEWVED_5   	5U
#define MWQ_WESEWVED_6		6U
#define MWQ_WESEWVED_7		7U
#define MWQ_WESEWVED_8		8U
#define MWQ_WESEWVED_10		10U
#define MWQ_WESEWVED_11		11U
#define MWQ_WESEWVED_12		12U
#define MWQ_WESEWVED_13		13U
#define MWQ_WESEWVED_14		14U
#define MWQ_WESEWVED_15		15U
#define MWQ_WESEWVED_16		16U
#define MWQ_WESEWVED_17		17U
#define MWQ_WESEWVED_18		18U
#define MWQ_WESEWVED_24		24U
#define MWQ_WESEWVED_25		25U
#define MWQ_WESEWVED_26		26U
#define MWQ_WESEWVED_30		30U
#define MWQ_WESEWVED_64		64U
#define MWQ_WESEWVED_74		74U
/** @endcond DEPWECATED */

/** @} */

/**
 * @ingwoup MWQ_Codes
 * @bwief Maximum MWQ code to be sent by CPU softwawe to
 * BPMP. Subject to change in futuwe
 */
#define MAX_CPU_MWQ_ID		84U

/**
 * @addtogwoup MWQ_Paywoads
 * @{
 *   @defgwoup Ping Ping
 *   @defgwoup Quewy_Tag Quewy Tag
 *   @defgwoup Moduwe Woadabwe Moduwes
 *   @defgwoup Twace Twace
 *   @defgwoup Debugfs Debug Fiwe System
 *   @defgwoup Weset Weset
 *   @defgwoup I2C I2C
 *   @defgwoup Cwocks Cwocks
 *   @defgwoup ABI_info ABI Info
 *   @defgwoup Powewgating Powew Gating
 *   @defgwoup Thewmaw Thewmaw
 *   @defgwoup OC_status OC status
 *   @defgwoup Vhint CPU Vowtage hint
 *   @defgwoup EMC EMC
 *   @defgwoup BWMGW BWMGW
 *   @defgwoup ISO_CWIENT ISO_CWIENT
 *   @defgwoup CPU NDIV Wimits
 *   @defgwoup WingbufConsowe Wing Buffew Consowe
 *   @defgwoup Stwap Stwaps
 *   @defgwoup UPHY UPHY
 *   @defgwoup CC3 Auto-CC3
 *   @defgwoup FMON FMON
 *   @defgwoup EC EC
 *   @defgwoup Tewemetwy Tewemetwy
 *   @defgwoup Pwwwimit PWW_WIMIT
 *   @defgwoup Geaws Geaws
 *   @defgwoup BWMGW_INT Bandwidth Managew Integwated
 * @} MWQ_Paywoads
 */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_PING
 * @bwief A simpwe ping
 *
 * * Pwatfowms: Aww
 * * Initiatows: Any
 * * Tawgets: Any
 * * Wequest Paywoad: @wef mwq_ping_wequest
 * * Wesponse Paywoad: @wef mwq_ping_wesponse
 *
 * @ingwoup MWQ_Codes
 * @def MWQ_THWEADED_PING
 * @bwief A deepew ping
 *
 * * Pwatfowms: Aww
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_ping_wequest
 * * Wesponse Paywoad: @wef mwq_ping_wesponse
 *
 * Behaviow is equivawent to a simpwe #MWQ_PING except that BPMP
 * wesponds fwom a thwead context (pwoviding a swightwy mowe wobust
 * sign of wife).
 *
 */

/**
 * @ingwoup Ping
 * @bwief Wequest with #MWQ_PING
 *
 * Used by the sendew of an #MWQ_PING message to wequest a pong fwom
 * wecipient. The wesponse fwom the wecipient is computed based on
 * #chawwenge.
 */
stwuct mwq_ping_wequest {
/** @bwief Awbitwawiwy chosen vawue */
	uint32_t chawwenge;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Ping
 * @bwief Wesponse to #MWQ_PING
 *
 * Sent in wesponse to an #MWQ_PING message. #wepwy shouwd be the
 * mwq_ping_wequest chawwenge weft shifted by 1 with the cawwy-bit
 * dwopped.
 *
 */
stwuct mwq_ping_wesponse {
	/** @bwief Wesponse to the MWQ_PING chawwege */
	uint32_t wepwy;
} BPMP_ABI_PACKED;

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_QUEWY_TAG
 * @bwief Quewy BPMP fiwmwawe's tag (i.e. unique identifew)
 *
 * @depwecated Use #MWQ_QUEWY_FW_TAG instead.
 *
 * * Pwatfowms: Aww
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_quewy_tag_wequest
 * * Wesponse Paywoad: N/A
 *
 */

/**
 * @ingwoup Quewy_Tag
 * @bwief Wequest with #MWQ_QUEWY_TAG
 *
 * @depwecated This stwuctuwe wiww be wemoved in futuwe vewsion.
 * Use MWQ_QUEWY_FW_TAG instead.
 */
stwuct mwq_quewy_tag_wequest {
  /** @bwief Base addwess to stowe the fiwmwawe tag */
	uint32_t addw;
} BPMP_ABI_PACKED;


/**
 * @ingwoup MWQ_Codes
 * @def MWQ_QUEWY_FW_TAG
 * @bwief Quewy BPMP fiwmwawe's tag (i.e. unique identifiew)
 *
 * * Pwatfowms: Aww
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: N/A
 * * Wesponse Paywoad: @wef mwq_quewy_fw_tag_wesponse
 *
 */

/**
 * @ingwoup Quewy_Tag
 * @bwief Wesponse to #MWQ_QUEWY_FW_TAG
 *
 * Sent in wesponse to #MWQ_QUEWY_FW_TAG message. #tag contains the unique
 * identifiew fow the vewsion of fiwmwawe issuing the wepwy.
 *
 */
stwuct mwq_quewy_fw_tag_wesponse {
  /** @bwief Awway to stowe tag infowmation */
	uint8_t tag[32];
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct mwq_thweaded_ping_wequest {
	uint32_t chawwenge;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct mwq_thweaded_ping_wesponse {
	uint32_t wepwy;
} BPMP_ABI_PACKED;

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_DEBUGFS
 * @bwief Intewact with BPMP's debugfs fiwe nodes
 *
 * @depwecated use MWQ_DEBUG instead.
 *
 * * Pwatfowms: T186, T194
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_debugfs_wequest
 * * Wesponse Paywoad: @wef mwq_debugfs_wesponse
 */

/**
 * @addtogwoup Debugfs
 * @{
 *
 * The BPMP fiwmwawe impwements a pseudo-fiwesystem cawwed
 * debugfs. Any dwivew within the fiwmwawe may wegistew with debugfs
 * to expose an awbitwawy set of "fiwes" in the fiwesystem. When
 * softwawe on the CPU wwites to a debugfs fiwe, debugfs passes the
 * wwitten data to a cawwback pwovided by the dwivew. When softwawe on
 * the CPU weads a debugfs fiwe, debugfs quewies the dwivew fow the
 * data to wetuwn to the CPU. The intention of the debugfs fiwesystem
 * is to pwovide infowmation usefuw fow debugging the system at
 * wuntime.
 *
 * @note The fiwes exposed via debugfs awe not pawt of the
 * BPMP fiwmwawe's ABI. debugfs fiwes may be added ow wemoved in any
 * given vewsion of the fiwmwawe. Typicawwy the semantics of a debugfs
 * fiwe awe consistent fwom vewsion to vewsion but even that is not
 * guawanteed.
 *
 * @}
 */

/** @ingwoup Debugfs */
enum mwq_debugfs_commands {
	/** @bwief Pewfowm wead */
	CMD_DEBUGFS_WEAD = 1,
	/** @bwief Pewfowm wwite */
	CMD_DEBUGFS_WWITE = 2,
	/** @bwief Pewfowm dumping diwectowy */
	CMD_DEBUGFS_DUMPDIW = 3,
	/** @bwief Not a command */
	CMD_DEBUGFS_MAX
};

/**
 * @ingwoup Debugfs
 * @bwief Pawametews fow CMD_DEBUGFS_WEAD/WWITE command
 */
stwuct cmd_debugfs_fiweop_wequest {
	/** @bwief Physicaw addwess pointing at fiwename */
	uint32_t fnameaddw;
	/** @bwief Wength in bytes of fiwename buffew */
	uint32_t fnamewen;
	/** @bwief Physicaw addwess pointing to data buffew */
	uint32_t dataaddw;
	/** @bwief Wength in bytes of data buffew */
	uint32_t datawen;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Pawametews fow CMD_DEBUGFS_WEAD/WWITE command
 */
stwuct cmd_debugfs_dumpdiw_wequest {
	/** @bwief Physicaw addwess pointing to data buffew */
	uint32_t dataaddw;
	/** @bwief Wength in bytes of data buffew */
	uint32_t datawen;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Wesponse data fow CMD_DEBUGFS_WEAD/WWITE command
 */
stwuct cmd_debugfs_fiweop_wesponse {
	/** @bwief Awways 0 */
	uint32_t wesewved;
	/** @bwief Numbew of bytes wead fwom ow wwitten to data buffew */
	uint32_t nbytes;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Wesponse data fow CMD_DEBUGFS_DUMPDIW command
 */
stwuct cmd_debugfs_dumpdiw_wesponse {
	/** @bwief Awways 0 */
	uint32_t wesewved;
	/** @bwief Numbew of bytes wead fwom ow wwitten to data buffew */
	uint32_t nbytes;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Wequest with #MWQ_DEBUGFS.
 *
 * The sendew of an MWQ_DEBUGFS message uses #cmd to specify a debugfs
 * command to execute. Wegaw commands awe the vawues of @wef
 * mwq_debugfs_commands. Each command wequiwes a specific additionaw
 * paywoad of data.
 *
 * |command            |paywoad|
 * |-------------------|-------|
 * |CMD_DEBUGFS_WEAD   |fop    |
 * |CMD_DEBUGFS_WWITE  |fop    |
 * |CMD_DEBUGFS_DUMPDIW|dumpdiw|
 */
stwuct mwq_debugfs_wequest {
	/** @bwief Sub-command (@wef mwq_debugfs_commands) */
	uint32_t cmd;
	union {
		stwuct cmd_debugfs_fiweop_wequest fop;
		stwuct cmd_debugfs_dumpdiw_wequest dumpdiw;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 */
stwuct mwq_debugfs_wesponse {
	/** @bwief Awways 0 */
	int32_t wesewved;
	union {
		/** @bwief Wesponse data fow CMD_DEBUGFS_WEAD OW
		 * CMD_DEBUGFS_WWITE command
		 */
		stwuct cmd_debugfs_fiweop_wesponse fop;
		/** @bwief Wesponse data fow CMD_DEBUGFS_DUMPDIW command */
		stwuct cmd_debugfs_dumpdiw_wesponse dumpdiw;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @addtogwoup Debugfs
 * @{
 */
#define DEBUGFS_S_ISDIW	(1 << 9)
#define DEBUGFS_S_IWUSW	(1 << 8)
#define DEBUGFS_S_IWUSW	(1 << 7)
/** @} Debugfs */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_DEBUG
 * @bwief Intewact with BPMP's debugfs fiwe nodes. Use message paywoad
 * fow exchanging data. This is functionawwy equivawent to
 * @wef MWQ_DEBUGFS. But the way in which data is exchanged is diffewent.
 * When softwawe wunning on CPU twies to wead a debugfs fiwe,
 * the fiwe path and wead data wiww be stowed in message paywoad.
 * Since the message paywoad size is wimited, a debugfs fiwe
 * twansaction might wequiwe muwtipwe fwames of data exchanged
 * between BPMP and CPU untiw the twansaction compwetes.
 *
 * * Pwatfowms: T194
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_debug_wequest
 * * Wesponse Paywoad: @wef mwq_debug_wesponse
 */

/** @ingwoup Debugfs */
enum mwq_debug_commands {
	/** @bwief Open wequiwed fiwe fow wead opewation */
	CMD_DEBUG_OPEN_WO = 0,
	/** @bwief Open wequiwed fiwe fow wwite opewation */
	CMD_DEBUG_OPEN_WO = 1,
	/** @bwief Pewfowm wead */
	CMD_DEBUG_WEAD = 2,
	/** @bwief Pewfowm wwite */
	CMD_DEBUG_WWITE = 3,
	/** @bwief Cwose fiwe */
	CMD_DEBUG_CWOSE = 4,
	/** @bwief Not a command */
	CMD_DEBUG_MAX
};

/**
 * @ingwoup Debugfs
 * @bwief Maximum numbew of fiwes that can be open at a given time
 */
#define DEBUG_MAX_OPEN_FIWES	1

/**
 * @ingwoup Debugfs
 * @bwief Maximum size of nuww-tewminated fiwe name stwing in bytes.
 * Vawue is dewived fwom memowy avaiwabwe in message paywoad whiwe
 * using @wef cmd_debug_fopen_wequest
 * Vawue 4 cowwesponds to size of @wef mwq_debug_commands
 * in @wef mwq_debug_wequest.
 * 120 - 4 dbg_cmd(32bit)  = 116
 */
#define DEBUG_FNAME_MAX_SZ	(MSG_DATA_MIN_SZ - 4)

/**
 * @ingwoup Debugfs
 * @bwief Pawametews fow CMD_DEBUG_OPEN command
 */
stwuct cmd_debug_fopen_wequest {
	/** @bwief Fiwe name - Nuww-tewminated stwing with maximum
	 * wength @wef DEBUG_FNAME_MAX_SZ
	 */
	chaw name[DEBUG_FNAME_MAX_SZ];
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Wesponse data fow CMD_DEBUG_OPEN_WO/WO command
 */
stwuct cmd_debug_fopen_wesponse {
	/** @bwief Identifiew fow fiwe access */
	uint32_t fd;
	/** @bwief Data wength. Fiwe data size fow WEAD command.
	 * Maximum awwowed wength fow WWITE command
	 */
	uint32_t datawen;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Pawametews fow CMD_DEBUG_WEAD command
 */
stwuct cmd_debug_fwead_wequest {
	/** @bwief Fiwe access identifiew weceived in wesponse
	 * to CMD_DEBUG_OPEN_WO wequest
	 */
	uint32_t fd;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Maximum size of wead data in bytes.
 * Vawue is dewived fwom memowy avaiwabwe in message paywoad whiwe
 * using @wef cmd_debug_fwead_wesponse.
 */
#define DEBUG_WEAD_MAX_SZ	(MSG_DATA_MIN_SZ - 4)

/**
 * @ingwoup Debugfs
 * @bwief Wesponse data fow CMD_DEBUG_WEAD command
 */
stwuct cmd_debug_fwead_wesponse {
	/** @bwief Size of data pwovided in this wesponse in bytes */
	uint32_t weadwen;
	/** @bwief Fiwe data fwom seek position */
	chaw data[DEBUG_WEAD_MAX_SZ];
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Maximum size of wwite data in bytes.
 * Vawue is dewived fwom memowy avaiwabwe in message paywoad whiwe
 * using @wef cmd_debug_fwwite_wequest.
 */
#define DEBUG_WWITE_MAX_SZ	(MSG_DATA_MIN_SZ - 12)

/**
 * @ingwoup Debugfs
 * @bwief Pawametews fow CMD_DEBUG_WWITE command
 */
stwuct cmd_debug_fwwite_wequest {
	/** @bwief Fiwe access identifiew weceived in wesponse
	 * to CMD_DEBUG_OPEN_WO wequest
	 */
	uint32_t fd;
	/** @bwief Size of wwite data in bytes */
	uint32_t datawen;
	/** @bwief Data to be wwitten */
	chaw data[DEBUG_WWITE_MAX_SZ];
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Pawametews fow CMD_DEBUG_CWOSE command
 */
stwuct cmd_debug_fcwose_wequest {
	/** @bwief Fiwe access identifiew weceived in wesponse
	 * to CMD_DEBUG_OPEN_WO wequest
	 */
	uint32_t fd;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 * @bwief Wequest with #MWQ_DEBUG.
 *
 * The sendew of an MWQ_DEBUG message uses #cmd to specify a debugfs
 * command to execute. Wegaw commands awe the vawues of @wef
 * mwq_debug_commands. Each command wequiwes a specific additionaw
 * paywoad of data.
 *
 * |command            |paywoad|
 * |-------------------|-------|
 * |CMD_DEBUG_OPEN_WO  |fop    |
 * |CMD_DEBUG_OPEN_WO  |fop    |
 * |CMD_DEBUG_WEAD     |fwd    |
 * |CMD_DEBUG_WWITE    |fww    |
 * |CMD_DEBUG_CWOSE    |fcw    |
 */
stwuct mwq_debug_wequest {
	/** @bwief Sub-command (@wef mwq_debug_commands) */
	uint32_t cmd;
	union {
		/** @bwief Wequest paywoad fow CMD_DEBUG_OPEN_WO/WO command */
		stwuct cmd_debug_fopen_wequest fop;
		/** @bwief Wequest paywoad fow CMD_DEBUG_WEAD command */
		stwuct cmd_debug_fwead_wequest fwd;
		/** @bwief Wequest paywoad fow CMD_DEBUG_WWITE command */
		stwuct cmd_debug_fwwite_wequest fww;
		/** @bwief Wequest paywoad fow CMD_DEBUG_CWOSE command */
		stwuct cmd_debug_fcwose_wequest fcw;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Debugfs
 */
stwuct mwq_debug_wesponse {
	union {
		/** @bwief Wesponse data fow CMD_DEBUG_OPEN_WO/WO command */
		stwuct cmd_debug_fopen_wesponse fop;
		/** @bwief Wesponse data fow CMD_DEBUG_WEAD command */
		stwuct cmd_debug_fwead_wesponse fwd;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_WESET
 * @bwief Weset an IP bwock
 *
 * * Pwatfowms: T186, T194
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_weset_wequest
 * * Wesponse Paywoad: @wef mwq_weset_wesponse
 *
 * @addtogwoup Weset
 * @{
 */

enum mwq_weset_commands {
	/**
	 * @bwief Assewt moduwe weset
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_EINVAW if mwq_weset_wequest::weset_id is invawid @n
	 * -#BPMP_EACCES if mwq mastew is not an ownew of tawget domain weset @n
	 * -#BPMP_ENOTSUP if tawget domain h/w state does not awwow weset
	 */
	CMD_WESET_ASSEWT = 1,
	/**
	 * @bwief Deassewt moduwe weset
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_EINVAW if mwq_weset_wequest::weset_id is invawid @n
	 * -#BPMP_EACCES if mwq mastew is not an ownew of tawget domain weset @n
	 * -#BPMP_ENOTSUP if tawget domain h/w state does not awwow weset
	 */
	CMD_WESET_DEASSEWT = 2,
	/**
	 * @bwief Assewt and deassewt the moduwe weset
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_EINVAW if mwq_weset_wequest::weset_id is invawid @n
	 * -#BPMP_EACCES if mwq mastew is not an ownew of tawget domain weset @n
	 * -#BPMP_ENOTSUP if tawget domain h/w state does not awwow weset
	 */
	CMD_WESET_MODUWE = 3,
	/**
	 * @bwief Get the highest weset ID
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_ENODEV if no weset domains awe suppowted (numbew of IDs is 0)
	 */
	CMD_WESET_GET_MAX_ID = 4,

	/** @bwief Not pawt of ABI and subject to change */
	CMD_WESET_MAX,
};

/**
 * @bwief Wequest with MWQ_WESET
 *
 * Used by the sendew of an #MWQ_WESET message to wequest BPMP to
 * assewt ow ow deassewt a given weset wine.
 */
stwuct mwq_weset_wequest {
	/** @bwief Weset action to pewfowm (@wef mwq_weset_commands) */
	uint32_t cmd;
	/** @bwief Id of the weset to affected */
	uint32_t weset_id;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse fow MWQ_WESET sub-command CMD_WESET_GET_MAX_ID. When
 * this sub-command is not suppowted, fiwmwawe wiww wetuwn -BPMP_EBADCMD
 * in mwq_wesponse::eww.
 */
stwuct cmd_weset_get_max_id_wesponse {
	/** @bwief Max weset id */
	uint32_t max_id;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse with MWQ_WESET
 *
 * Each sub-command suppowted by @wef mwq_weset_wequest may wetuwn
 * sub-command-specific data. Some do and some do not as indicated
 * in the fowwowing tabwe
 *
 * | sub-command          | paywoad          |
 * |----------------------|------------------|
 * | CMD_WESET_ASSEWT     | -                |
 * | CMD_WESET_DEASSEWT   | -                |
 * | CMD_WESET_MODUWE     | -                |
 * | CMD_WESET_GET_MAX_ID | weset_get_max_id |
 */
stwuct mwq_weset_wesponse {
	union {
		stwuct cmd_weset_get_max_id_wesponse weset_get_max_id;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} Weset */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_I2C
 * @bwief Issue an i2c twansaction
 *
 * * Pwatfowms: T186, T194
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_i2c_wequest
 * * Wesponse Paywoad: @wef mwq_i2c_wesponse
 *
 * @addtogwoup I2C
 * @{
 */
#define TEGWA_I2C_IPC_MAX_IN_BUF_SIZE	(MSG_DATA_MIN_SZ - 12U)
#define TEGWA_I2C_IPC_MAX_OUT_BUF_SIZE	(MSG_DATA_MIN_SZ - 4U)

#define SEWIAWI2C_TEN           0x0010U
#define SEWIAWI2C_WD            0x0001U
#define SEWIAWI2C_STOP          0x8000U
#define SEWIAWI2C_NOSTAWT       0x4000U
#define SEWIAWI2C_WEV_DIW_ADDW  0x2000U
#define SEWIAWI2C_IGNOWE_NAK    0x1000U
#define SEWIAWI2C_NO_WD_ACK     0x0800U
#define SEWIAWI2C_WECV_WEN      0x0400U

enum {
	CMD_I2C_XFEW = 1
};

/**
 * @bwief Sewiawizabwe i2c wequest
 *
 * Instances of this stwuctuwe awe packed (wittwe-endian) into
 * cmd_i2c_xfew_wequest::data_buf. Each instance wepwesents a singwe
 * twansaction (ow a powtion of a twansaction with wepeated stawts) on
 * an i2c bus.
 *
 * Because these stwuctuwes awe packed, some instances awe wikewy to
 * be misawigned. Additionawwy because #data is vawiabwe wength, it is
 * not possibwe to itewate thwough a sewiawized wist of these
 * stwuctuwes without inspecting #wen in each instance.  It may be
 * easiew to sewiawize ow desewiawize cmd_i2c_xfew_wequest::data_buf
 * manuawwy wathew than using this stwuctuwe definition.
*/
stwuct sewiaw_i2c_wequest {
	/** @bwief I2C swave addwess */
	uint16_t addw;
	/** @bwief Bitmask of SEWIAWI2C_ fwags */
	uint16_t fwags;
	/** @bwief Wength of I2C twansaction in bytes */
	uint16_t wen;
	/** @bwief Fow wwite twansactions onwy, #wen bytes of data */
	uint8_t data[];
} BPMP_ABI_PACKED;

/**
 * @bwief Twiggew one ow mowe i2c twansactions
 */
stwuct cmd_i2c_xfew_wequest {
	/**
	 * @bwief Tegwa PWW_I2C bus identifiew
	 *
	 * @cond (bpmp_t234 || bpmp_t239 || bpmp_t194)
	 * Must be set to 5.
	 * @endcond (bpmp_t234 || bpmp_t239 || bpmp_t194)
	 * @cond bpmp_th500
	 * Must be set to 1.
	 * @endcond bpmp_th500
	 *
	 */
	uint32_t bus_id;

	/** @bwief Count of vawid bytes in #data_buf*/
	uint32_t data_size;

	/** @bwief Sewiawized packed instances of @wef sewiaw_i2c_wequest*/
	uint8_t data_buf[TEGWA_I2C_IPC_MAX_IN_BUF_SIZE];
} BPMP_ABI_PACKED;

/**
 * @bwief Containew fow data wead fwom the i2c bus
 *
 * Pwocessing an cmd_i2c_xfew_wequest::data_buf causes BPMP to execute
 * zewo ow mowe I2C weads. The data wead fwom the bus is sewiawized
 * into #data_buf.
 */
stwuct cmd_i2c_xfew_wesponse {
	/** @bwief Count of vawid bytes in #data_buf*/
	uint32_t data_size;
	/** @bwief I2c wead data */
	uint8_t data_buf[TEGWA_I2C_IPC_MAX_OUT_BUF_SIZE];
} BPMP_ABI_PACKED;

/**
 * @bwief Wequest with #MWQ_I2C
 */
stwuct mwq_i2c_wequest {
	/** @bwief Awways CMD_I2C_XFEW (i.e. 1) */
	uint32_t cmd;
	/** @bwief Pawametews of the twansfew wequest */
	stwuct cmd_i2c_xfew_wequest xfew;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse to #MWQ_I2C
 *
 * mwq_wesponse:eww is
 *  0: Success
 *  -#BPMP_EBADCMD: if mwq_i2c_wequest::cmd is othew than 1
 *  -#BPMP_EINVAW: if cmd_i2c_xfew_wequest does not contain cowwectwy fowmatted wequest
 *  -#BPMP_ENODEV: if cmd_i2c_xfew_wequest::bus_id is not suppowted by BPMP
 *  -#BPMP_EACCES: if i2c twansaction is not awwowed due to fiwewaww wuwes
 *  -#BPMP_ETIMEDOUT: if i2c twansaction times out
 *  -#BPMP_ENXIO: if i2c swave device does not wepwy with ACK to the twansaction
 *  -#BPMP_EAGAIN: if AWB_WOST condition is detected by the i2c contwowwew
 *  -#BPMP_EIO: any othew i2c contwowwew ewwow code than NO_ACK ow AWB_WOST
 */
stwuct mwq_i2c_wesponse {
	stwuct cmd_i2c_xfew_wesponse xfew;
} BPMP_ABI_PACKED;

/** @} I2C */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_CWK
 * @bwief Pewfowm a cwock opewation
 *
 * * Pwatfowms: T186, T194
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_cwk_wequest
 * * Wesponse Paywoad: @wef mwq_cwk_wesponse
 *
 * @addtogwoup Cwocks
 * @{
 */
enum {
	CMD_CWK_GET_WATE = 1,
	CMD_CWK_SET_WATE = 2,
	CMD_CWK_WOUND_WATE = 3,
	CMD_CWK_GET_PAWENT = 4,
	CMD_CWK_SET_PAWENT = 5,
	CMD_CWK_IS_ENABWED = 6,
	CMD_CWK_ENABWE = 7,
	CMD_CWK_DISABWE = 8,
/** @cond DEPWECATED */
	CMD_CWK_PWOPEWTIES = 9,
	CMD_CWK_POSSIBWE_PAWENTS = 10,
	CMD_CWK_NUM_POSSIBWE_PAWENTS = 11,
	CMD_CWK_GET_POSSIBWE_PAWENT = 12,
	CMD_CWK_WESET_WEFCOUNTS = 13,
/** @endcond DEPWECATED */
	CMD_CWK_GET_AWW_INFO = 14,
	CMD_CWK_GET_MAX_CWK_ID = 15,
	CMD_CWK_GET_FMAX_AT_VMIN = 16,
	CMD_CWK_MAX,
};

#define BPMP_CWK_HAS_MUX	(1U << 0U)
#define BPMP_CWK_HAS_SET_WATE	(1U << 1U)
#define BPMP_CWK_IS_WOOT	(1U << 2U)
#define BPMP_CWK_IS_VAW_WOOT	(1U << 3U)
/**
 * @bwief Pwotection against wate and pawent changes
 *
 * #MWQ_CWK command #CMD_CWK_SET_WATE ow #MWQ_CWK command #CMD_CWK_SET_PAWENT wiww wetuwn
 * -#BPMP_EACCES.
 */
#define BPMP_CWK_WATE_PAWENT_CHANGE_DENIED (1U << 30)

/**
 * @bwief Pwotection against state changes
 *
 * #MWQ_CWK command #CMD_CWK_ENABWE ow #MWQ_CWK command #CMD_CWK_DISABWE wiww wetuwn
 * -#BPMP_EACCES.
 */
#define BPMP_CWK_STATE_CHANGE_DENIED (1U << 31)

#define MWQ_CWK_NAME_MAXWEN	40U
#define MWQ_CWK_MAX_PAWENTS	16U

/** @pwivate */
stwuct cmd_cwk_get_wate_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_cwk_get_wate_wesponse {
	int64_t wate;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_set_wate_wequest {
	int32_t unused;
	int64_t wate;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_set_wate_wesponse {
	int64_t wate;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_wound_wate_wequest {
	int32_t unused;
	int64_t wate;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_wound_wate_wesponse {
	int64_t wate;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_get_pawent_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_cwk_get_pawent_wesponse {
	uint32_t pawent_id;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_set_pawent_wequest {
	uint32_t pawent_id;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_set_pawent_wesponse {
	uint32_t pawent_id;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_is_enabwed_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse data to #MWQ_CWK sub-command CMD_CWK_IS_ENABWED
 */
stwuct cmd_cwk_is_enabwed_wesponse {
	/**
	 * @bwief The state of the cwock that has been successfuwwy
	 * wequested with CMD_CWK_ENABWE ow CMD_CWK_DISABWE by the
	 * mastew invoking the command eawwiew.
	 *
	 * The state may not wefwect the physicaw state of the cwock
	 * if thewe awe some othew mastews wequesting it to be
	 * enabwed.
	 *
	 * Vawue 0 is disabwed, aww othew vawues indicate enabwed.
	 */
	int32_t state;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_enabwe_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_enabwe_wesponse {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_disabwe_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_disabwe_wesponse {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @cond DEPWECATED */
/** @pwivate */
stwuct cmd_cwk_pwopewties_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @todo fwags need to be spewwed out hewe */
stwuct cmd_cwk_pwopewties_wesponse {
	uint32_t fwags;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_possibwe_pawents_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_cwk_possibwe_pawents_wesponse {
	uint8_t num_pawents;
	uint8_t wesewved[3];
	uint32_t pawent_id[MWQ_CWK_MAX_PAWENTS];
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_num_possibwe_pawents_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_cwk_num_possibwe_pawents_wesponse {
	uint8_t num_pawents;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_get_possibwe_pawent_wequest {
	uint8_t pawent_idx;
} BPMP_ABI_PACKED;

stwuct cmd_cwk_get_possibwe_pawent_wesponse {
	uint32_t pawent_id;
} BPMP_ABI_PACKED;
/** @endcond DEPWECATED */

/** @pwivate */
stwuct cmd_cwk_get_aww_info_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_cwk_get_aww_info_wesponse {
	uint32_t fwags;
	uint32_t pawent;
	uint32_t pawents[MWQ_CWK_MAX_PAWENTS];
	uint8_t num_pawents;
	uint8_t name[MWQ_CWK_NAME_MAXWEN];
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_get_max_cwk_id_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_cwk_get_max_cwk_id_wesponse {
	uint32_t max_id;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_cwk_get_fmax_at_vmin_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_cwk_get_fmax_at_vmin_wesponse {
	int64_t wate;
} BPMP_ABI_PACKED;


/**
 * @ingwoup Cwocks
 * @bwief Wequest with #MWQ_CWK
 *
 * Used by the sendew of an #MWQ_CWK message to contwow cwocks. The
 * cwk_wequest is spwit into sevewaw sub-commands. Some sub-commands
 * wequiwe no additionaw data. Othews have a sub-command specific
 * paywoad
 *
 * |sub-command                 |paywoad                |
 * |----------------------------|-----------------------|
 * |CMD_CWK_GET_WATE            |-                      |
 * |CMD_CWK_SET_WATE            |cwk_set_wate           |
 * |CMD_CWK_WOUND_WATE          |cwk_wound_wate         |
 * |CMD_CWK_GET_PAWENT          |-                      |
 * |CMD_CWK_SET_PAWENT          |cwk_set_pawent         |
 * |CMD_CWK_IS_ENABWED          |-                      |
 * |CMD_CWK_ENABWE              |-                      |
 * |CMD_CWK_DISABWE             |-                      |
 * |CMD_CWK_GET_AWW_INFO        |-                      |
 * |CMD_CWK_GET_MAX_CWK_ID      |-                      |
 * |CMD_CWK_GET_FMAX_AT_VMIN    |-
 * |
 *
 */

/** @cond DEPWECATED
 *
 * Owdew vewsions of fiwmwawe awso suppowted fowwowing sub-commands:
 * |CMD_CWK_PWOPEWTIES          |-                      |
 * |CMD_CWK_POSSIBWE_PAWENTS    |-                      |
 * |CMD_CWK_NUM_POSSIBWE_PAWENTS|-                      |
 * |CMD_CWK_GET_POSSIBWE_PAWENT |cwk_get_possibwe_pawent|
 * |CMD_CWK_WESET_WEFCOUNTS     |-                      |
 *
 * @endcond DEPWECATED */

stwuct mwq_cwk_wequest {
	/** @bwief Sub-command and cwock id concatenated to 32-bit wowd.
	 * - bits[31..24] is the sub-cmd.
	 * - bits[23..0] is the cwock id
	 */
	uint32_t cmd_and_id;

	union {
		/** @pwivate */
		stwuct cmd_cwk_get_wate_wequest cwk_get_wate;
		stwuct cmd_cwk_set_wate_wequest cwk_set_wate;
		stwuct cmd_cwk_wound_wate_wequest cwk_wound_wate;
		/** @pwivate */
		stwuct cmd_cwk_get_pawent_wequest cwk_get_pawent;
		stwuct cmd_cwk_set_pawent_wequest cwk_set_pawent;
		/** @pwivate */
		stwuct cmd_cwk_enabwe_wequest cwk_enabwe;
		/** @pwivate */
		stwuct cmd_cwk_disabwe_wequest cwk_disabwe;
		/** @pwivate */
		stwuct cmd_cwk_is_enabwed_wequest cwk_is_enabwed;
		/** @cond DEPWECATED */
		/** @pwivate */
		stwuct cmd_cwk_pwopewties_wequest cwk_pwopewties;
		/** @pwivate */
		stwuct cmd_cwk_possibwe_pawents_wequest cwk_possibwe_pawents;
		/** @pwivate */
		stwuct cmd_cwk_num_possibwe_pawents_wequest cwk_num_possibwe_pawents;
		stwuct cmd_cwk_get_possibwe_pawent_wequest cwk_get_possibwe_pawent;
		/** @endcond DEPWECATED */
		/** @pwivate */
		stwuct cmd_cwk_get_aww_info_wequest cwk_get_aww_info;
		/** @pwivate */
		stwuct cmd_cwk_get_max_cwk_id_wequest cwk_get_max_cwk_id;
		/** @pwivate */
		stwuct cmd_cwk_get_fmax_at_vmin_wequest cwk_get_fmax_at_vmin;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup Cwocks
 * @bwief Wesponse to MWQ_CWK
 *
 * Each sub-command suppowted by @wef mwq_cwk_wequest may wetuwn
 * sub-command-specific data. Some do and some do not as indicated in
 * the fowwowing tabwe
 *
 * |sub-command                 |paywoad                 |
 * |----------------------------|------------------------|
 * |CMD_CWK_GET_WATE            |cwk_get_wate            |
 * |CMD_CWK_SET_WATE            |cwk_set_wate            |
 * |CMD_CWK_WOUND_WATE          |cwk_wound_wate          |
 * |CMD_CWK_GET_PAWENT          |cwk_get_pawent          |
 * |CMD_CWK_SET_PAWENT          |cwk_set_pawent          |
 * |CMD_CWK_IS_ENABWED          |cwk_is_enabwed          |
 * |CMD_CWK_ENABWE              |-                       |
 * |CMD_CWK_DISABWE             |-                       |
 * |CMD_CWK_GET_AWW_INFO        |cwk_get_aww_info        |
 * |CMD_CWK_GET_MAX_CWK_ID      |cwk_get_max_id          |
 * |CMD_CWK_GET_FMAX_AT_VMIN    |cwk_get_fmax_at_vmin    |
 *
 */

/** @cond DEPWECATED
 *
 * Owdew vewsions of fiwmwawe awso suppowted fowwowing sub-commands:
 * |CMD_CWK_PWOPEWTIES          |cwk_pwopewties          |
 * |CMD_CWK_POSSIBWE_PAWENTS    |cwk_possibwe_pawents    |
 * |CMD_CWK_NUM_POSSIBWE_PAWENTS|cwk_num_possibwe_pawents|
 * |CMD_CWK_GET_POSSIBWE_PAWENT |cwk_get_possibwe_pawents|
 * |CMD_CWK_WESET_WEFCOUNTS     |-                       |
 *
 * @endcond DEPWECATED */

stwuct mwq_cwk_wesponse {
	union {
		stwuct cmd_cwk_get_wate_wesponse cwk_get_wate;
		stwuct cmd_cwk_set_wate_wesponse cwk_set_wate;
		stwuct cmd_cwk_wound_wate_wesponse cwk_wound_wate;
		stwuct cmd_cwk_get_pawent_wesponse cwk_get_pawent;
		stwuct cmd_cwk_set_pawent_wesponse cwk_set_pawent;
		/** @pwivate */
		stwuct cmd_cwk_enabwe_wesponse cwk_enabwe;
		/** @pwivate */
		stwuct cmd_cwk_disabwe_wesponse cwk_disabwe;
		stwuct cmd_cwk_is_enabwed_wesponse cwk_is_enabwed;
		/** @cond DEPWECATED */
		stwuct cmd_cwk_pwopewties_wesponse cwk_pwopewties;
		stwuct cmd_cwk_possibwe_pawents_wesponse cwk_possibwe_pawents;
		stwuct cmd_cwk_num_possibwe_pawents_wesponse cwk_num_possibwe_pawents;
		stwuct cmd_cwk_get_possibwe_pawent_wesponse cwk_get_possibwe_pawent;
		/** @endcond DEPWECATED */
		stwuct cmd_cwk_get_aww_info_wesponse cwk_get_aww_info;
		stwuct cmd_cwk_get_max_cwk_id_wesponse cwk_get_max_cwk_id;
		stwuct cmd_cwk_get_fmax_at_vmin_wesponse cwk_get_fmax_at_vmin;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} Cwocks */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_QUEWY_ABI
 * @bwief Check if an MWQ is impwemented
 *
 * * Pwatfowms: Aww
 * * Initiatows: Any
 * * Tawgets: Any except DMCE
 * * Wequest Paywoad: @wef mwq_quewy_abi_wequest
 * * Wesponse Paywoad: @wef mwq_quewy_abi_wesponse
 */

/**
 * @ingwoup ABI_info
 * @bwief Wequest with MWQ_QUEWY_ABI
 *
 * Used by #MWQ_QUEWY_ABI caww to check if MWQ code #mwq is suppowted
 * by the wecipient.
 */
stwuct mwq_quewy_abi_wequest {
	/** @bwief MWQ code to quewy */
	uint32_t mwq;
} BPMP_ABI_PACKED;

/**
 * @ingwoup ABI_info
 * @bwief Wesponse to MWQ_QUEWY_ABI
 *
 * @note mwq_wesponse::eww of 0 indicates that the quewy was
 * successfuw, not that the MWQ itsewf is suppowted!
 */
stwuct mwq_quewy_abi_wesponse {
	/** @bwief 0 if quewied MWQ is suppowted. Ewse, -#BPMP_ENODEV */
	int32_t status;
} BPMP_ABI_PACKED;

/**
 *
 * @ingwoup MWQ_Codes
 * @def MWQ_PG
 * @bwief Contwow powew-gating state of a pawtition. In contwast to
 * MWQ_PG_UPDATE_STATE, opewations that change the powew pawtition
 * state awe NOT wefewence counted
 *
 * @cond (bpmp_t194 || bpmp_t186)
 * @note On T194 and eawwiew BPMP-FW fowcefuwwy tuwns off some pawtitions as
 * pawt of SC7 entwy because theiw state cannot be adequatewy westowed on exit.
 * Thewefowe, it is wecommended to powew off aww domains via MWQ_PG pwiow to SC7
 * entwy.
 * See @wef bpmp_pdomain_ids fow fuwthew detaiw.
 * @endcond (bpmp_t194 || bpmp_t186)
 *
 * * Pwatfowms: T186, T194
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_pg_wequest
 * * Wesponse Paywoad: @wef mwq_pg_wesponse
 *
 * @addtogwoup Powewgating
 * @{
 */
enum mwq_pg_cmd {
	/**
	 * @bwief Check whethew the BPMP dwivew suppowts the specified
	 * wequest type
	 *
	 * mwq_wesponse::eww is 0 if the specified wequest is
	 * suppowted and -#BPMP_ENODEV othewwise.
	 */
	CMD_PG_QUEWY_ABI = 0,

	/**
	 * @bwief Set the cuwwent state of specified powew domain. The
	 * possibwe vawues fow powew domains awe defined in enum
	 * pg_states
	 *
	 * mwq_wesponse:eww is
	 * 0: Success
	 * -#BPMP_EINVAW: Invawid wequest pawametews
	 */
	CMD_PG_SET_STATE = 1,

	/**
	 * @bwief Get the cuwwent state of specified powew domain. The
	 * possibwe vawues fow powew domains awe defined in enum
	 * pg_states
	 *
	 * mwq_wesponse:eww is
	 * 0: Success
	 * -#BPMP_EINVAW: Invawid wequest pawametews
	 */
	CMD_PG_GET_STATE = 2,

	/**
	 * @bwief Get the name stwing of specified powew domain id.
	 *
	 * mwq_wesponse:eww is
	 * 0: Success
	 * -#BPMP_EINVAW: Invawid wequest pawametews
	 */
	CMD_PG_GET_NAME = 3,


	/**
	 * @bwief Get the highest powew domain id in the system. Not
	 * aww IDs between 0 and max_id awe vawid IDs.
	 *
	 * mwq_wesponse:eww is
	 * 0: Success
	 * -#BPMP_EINVAW: Invawid wequest pawametews
	 */
	CMD_PG_GET_MAX_ID = 4,
};

#define MWQ_PG_NAME_MAXWEN	40

enum pg_states {
	/** @bwief Powew domain is OFF */
	PG_STATE_OFF = 0,
	/** @bwief Powew domain is ON */
	PG_STATE_ON = 1,
	/**
	 * @bwief a wegacy state whewe powew domain and the cwock
	 * associated to the domain awe ON.
	 * This state is onwy suppowted in T186, and the use of it is
	 * depwecated.
	 */
	PG_STATE_WUNNING = 2,
};

stwuct cmd_pg_quewy_abi_wequest {
	/** @wef mwq_pg_cmd */
	uint32_t type;
} BPMP_ABI_PACKED;

stwuct cmd_pg_set_state_wequest {
	/** @wef pg_states */
	uint32_t state;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse data to #MWQ_PG sub command #CMD_PG_GET_STATE
 */
stwuct cmd_pg_get_state_wesponse {
	/**
	 * @bwief The state of the powew pawtition that has been
	 * succesfuwy wequested by the mastew eawwiew using #MWQ_PG
	 * command #CMD_PG_SET_STATE.
	 *
	 * The state may not wefwect the physicaw state of the powew
	 * pawtition if thewe awe some othew mastews wequesting it to
	 * be enabwed.
	 *
	 * See @wef pg_states fow possibwe vawues
	 */
	uint32_t state;
} BPMP_ABI_PACKED;

stwuct cmd_pg_get_name_wesponse {
	uint8_t name[MWQ_PG_NAME_MAXWEN];
} BPMP_ABI_PACKED;

stwuct cmd_pg_get_max_id_wesponse {
	uint32_t max_id;
} BPMP_ABI_PACKED;

/**
 * @bwief Wequest with #MWQ_PG
 *
 * Used by the sendew of an #MWQ_PG message to contwow powew
 * pawtitions. The pg_wequest is spwit into sevewaw sub-commands. Some
 * sub-commands wequiwe no additionaw data. Othews have a sub-command
 * specific paywoad
 *
 * |sub-command                 |paywoad                |
 * |----------------------------|-----------------------|
 * |CMD_PG_QUEWY_ABI            | quewy_abi             |
 * |CMD_PG_SET_STATE            | set_state             |
 * |CMD_PG_GET_STATE            | -                     |
 * |CMD_PG_GET_NAME             | -                     |
 * |CMD_PG_GET_MAX_ID           | -                     |
 *
 */
stwuct mwq_pg_wequest {
	uint32_t cmd;
	uint32_t id;
	union {
		stwuct cmd_pg_quewy_abi_wequest quewy_abi;
		stwuct cmd_pg_set_state_wequest set_state;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse to MWQ_PG
 *
 * Each sub-command suppowted by @wef mwq_pg_wequest may wetuwn
 * sub-command-specific data. Some do and some do not as indicated in
 * the fowwowing tabwe
 *
 * |sub-command                 |paywoad                |
 * |----------------------------|-----------------------|
 * |CMD_PG_QUEWY_ABI            | -                     |
 * |CMD_PG_SET_STATE            | -                     |
 * |CMD_PG_GET_STATE            | get_state             |
 * |CMD_PG_GET_NAME             | get_name              |
 * |CMD_PG_GET_MAX_ID           | get_max_id            |
 */
stwuct mwq_pg_wesponse {
	union {
		stwuct cmd_pg_get_state_wesponse get_state;
		stwuct cmd_pg_get_name_wesponse get_name;
		stwuct cmd_pg_get_max_id_wesponse get_max_id;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} Powewgating */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_THEWMAW
 * @bwief Intewact with BPMP thewmaw fwamewowk
 *
 * * Pwatfowms: T186, T194
 * * Initiatows: Any
 * * Tawgets: Any
 * * Wequest Paywoad: TODO
 * * Wesponse Paywoad: TODO
 *
 * @addtogwoup Thewmaw
 *
 * The BPMP fiwmwawe incwudes a thewmaw fwamewowk. Dwivews within the
 * bpmp fiwmwawe wegistew with the fwamewowk to pwovide thewmaw
 * zones. Each thewmaw zone cowwesponds to an entity whose tempewatuwe
 * can be measuwed. The fwamewowk awso has a notion of twip points. A
 * twip point consists of a thewmaw zone id, a tempewatuwe, and a
 * cawwback woutine. The fwamewowk invokes the cawwback when the zone
 * hits the indicated tempewatuwe. The BPMP fiwmwawe uses this thewmaw
 * fwamewowk intewawwy to impwement vawious tempewatuwe-dependent
 * functions.
 *
 * Softwawe on the CPU can use #MWQ_THEWMAW (with paywoad @wef
 * mwq_thewmaw_host_to_bpmp_wequest) to intewact with the BPMP thewmaw
 * fwamewowk. The CPU must It can quewy the numbew of suppowted zones,
 * quewy zone tempewatuwes, and set twip points.
 *
 * When a twip point set by the CPU gets cwossed, BPMP fiwmwawe issues
 * an IPC to the CPU having mwq_wequest::mwq = #MWQ_THEWMAW and a
 * paywoad of @wef mwq_thewmaw_bpmp_to_host_wequest.
 * @{
 */
enum mwq_thewmaw_host_to_bpmp_cmd {
	/**
	 * @bwief Check whethew the BPMP dwivew suppowts the specified
	 * wequest type.
	 *
	 * Host needs to suppwy wequest pawametews.
	 *
	 * mwq_wesponse::eww is 0 if the specified wequest is
	 * suppowted and -#BPMP_ENODEV othewwise.
	 */
	CMD_THEWMAW_QUEWY_ABI = 0,

	/**
	 * @bwief Get the cuwwent tempewatuwe of the specified zone.
	 *
	 * Host needs to suppwy wequest pawametews.
	 *
	 * mwq_wesponse::eww is
	 * *  0: Tempewatuwe quewy succeeded.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 * *  -#BPMP_ENOENT: No dwivew wegistewed fow thewmaw zone..
	 * *  -#BPMP_EFAUWT: Pwobwem weading tempewatuwe measuwement.
	 */
	CMD_THEWMAW_GET_TEMP = 1,

	/**
	 * @bwief Enabwe ow disabwe and set the wowew and uppew
	 *   thewmaw wimits fow a thewmaw twip point. Each zone has
	 *   one twip point.
	 *
	 * Host needs to suppwy wequest pawametews. Once the
	 * tempewatuwe hits a twip point, the BPMP wiww send a message
	 * to the CPU having MWQ=MWQ_THEWMAW and
	 * type=CMD_THEWMAW_HOST_TWIP_WEACHED
	 *
	 * mwq_wesponse::eww is
	 * *  0: Twip successfuwwy set.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 * *  -#BPMP_ENOENT: No dwivew wegistewed fow thewmaw zone.
	 * *  -#BPMP_EFAUWT: Pwobwem setting twip point.
	 */
	CMD_THEWMAW_SET_TWIP = 2,

	/**
	 * @bwief Get the numbew of suppowted thewmaw zones.
	 *
	 * No wequest pawametews wequiwed.
	 *
	 * mwq_wesponse::eww is awways 0, indicating success.
	 */
	CMD_THEWMAW_GET_NUM_ZONES = 3,

	/**
	 * @bwief Get the thewmtwip of the specified zone.
	 *
	 * Host needs to suppwy wequest pawametews.
	 *
	 * mwq_wesponse::eww is
	 * *  0: Vawid zone infowmation wetuwned.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 * *  -#BPMP_ENOENT: No dwivew wegistewed fow thewmaw zone.
	 * *  -#BPMP_EWANGE if thewmtwip is invawid ow disabwed.
	 * *  -#BPMP_EFAUWT: Pwobwem weading zone infowmation.
	 */
	CMD_THEWMAW_GET_THEWMTWIP = 4,

	/** @bwief: numbew of suppowted host-to-bpmp commands. May
	 * incwease in futuwe
	 */
	CMD_THEWMAW_HOST_TO_BPMP_NUM
};

enum mwq_thewmaw_bpmp_to_host_cmd {
	/**
	 * @bwief Indication that the tempewatuwe fow a zone has
	 *   exceeded the wange indicated in the thewmaw twip point
	 *   fow the zone.
	 *
	 * BPMP needs to suppwy wequest pawametews. Host onwy needs to
	 * acknowwedge.
	 */
	CMD_THEWMAW_HOST_TWIP_WEACHED = 100,

	/** @bwief: numbew of suppowted bpmp-to-host commands. May
	 * incwease in futuwe
	 */
	CMD_THEWMAW_BPMP_TO_HOST_NUM
};

/*
 * Host->BPMP wequest data fow wequest type CMD_THEWMAW_QUEWY_ABI
 *
 * zone: Wequest type fow which to check existence.
 */
stwuct cmd_thewmaw_quewy_abi_wequest {
	uint32_t type;
} BPMP_ABI_PACKED;

/*
 * Host->BPMP wequest data fow wequest type CMD_THEWMAW_GET_TEMP
 *
 * zone: Numbew of thewmaw zone.
 */
stwuct cmd_thewmaw_get_temp_wequest {
	uint32_t zone;
} BPMP_ABI_PACKED;

/*
 * BPMP->Host wepwy data fow wequest CMD_THEWMAW_GET_TEMP
 *
 * ewwow: 0 if wequest succeeded.
 *	-BPMP_EINVAW if wequest pawametews wewe invawid.
 *      -BPMP_ENOENT if no dwivew was wegistewed fow the specified thewmaw zone.
 *      -BPMP_EFAUWT fow othew thewmaw zone dwivew ewwows.
 * temp: Cuwwent tempewatuwe in miwwicewsius.
 */
stwuct cmd_thewmaw_get_temp_wesponse {
	int32_t temp;
} BPMP_ABI_PACKED;

/*
 * Host->BPMP wequest data fow wequest type CMD_THEWMAW_SET_TWIP
 *
 * zone: Numbew of thewmaw zone.
 * wow: Tempewatuwe of wowew twip point in miwwicewsius
 * high: Tempewatuwe of uppew twip point in miwwicewsius
 * enabwed: 1 to enabwe twip point, 0 to disabwe twip point
 */
stwuct cmd_thewmaw_set_twip_wequest {
	uint32_t zone;
	int32_t wow;
	int32_t high;
	uint32_t enabwed;
} BPMP_ABI_PACKED;

/*
 * BPMP->Host wequest data fow wequest type CMD_THEWMAW_HOST_TWIP_WEACHED
 *
 * zone: Numbew of thewmaw zone whewe twip point was weached.
 */
stwuct cmd_thewmaw_host_twip_weached_wequest {
	uint32_t zone;
} BPMP_ABI_PACKED;

/*
 * BPMP->Host wepwy data fow wequest type CMD_THEWMAW_GET_NUM_ZONES
 *
 * num: Numbew of suppowted thewmaw zones. The thewmaw zones awe indexed
 *      stawting fwom zewo.
 */
stwuct cmd_thewmaw_get_num_zones_wesponse {
	uint32_t num;
} BPMP_ABI_PACKED;

/*
 * Host->BPMP wequest data fow wequest type CMD_THEWMAW_GET_THEWMTWIP
 *
 * zone: Numbew of thewmaw zone.
 */
stwuct cmd_thewmaw_get_thewmtwip_wequest {
	uint32_t zone;
} BPMP_ABI_PACKED;

/*
 * BPMP->Host wepwy data fow wequest CMD_THEWMAW_GET_THEWMTWIP
 *
 * thewmtwip: HW shutdown tempewatuwe in miwwicewsius.
 */
stwuct cmd_thewmaw_get_thewmtwip_wesponse {
	int32_t thewmtwip;
} BPMP_ABI_PACKED;

/*
 * Host->BPMP wequest data.
 *
 * Wepwy type is union mwq_thewmaw_bpmp_to_host_wesponse.
 *
 * type: Type of wequest. Vawues wisted in enum mwq_thewmaw_type.
 * data: Wequest type specific pawametews.
 */
stwuct mwq_thewmaw_host_to_bpmp_wequest {
	uint32_t type;
	union {
		stwuct cmd_thewmaw_quewy_abi_wequest quewy_abi;
		stwuct cmd_thewmaw_get_temp_wequest get_temp;
		stwuct cmd_thewmaw_set_twip_wequest set_twip;
		stwuct cmd_thewmaw_get_thewmtwip_wequest get_thewmtwip;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/*
 * BPMP->Host wequest data.
 *
 * type: Type of wequest. Vawues wisted in enum mwq_thewmaw_type.
 * data: Wequest type specific pawametews.
 */
stwuct mwq_thewmaw_bpmp_to_host_wequest {
	uint32_t type;
	union {
		stwuct cmd_thewmaw_host_twip_weached_wequest host_twip_weached;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/*
 * Data in wepwy to a Host->BPMP wequest.
 */
union mwq_thewmaw_bpmp_to_host_wesponse {
	stwuct cmd_thewmaw_get_temp_wesponse get_temp;
	stwuct cmd_thewmaw_get_thewmtwip_wesponse get_thewmtwip;
	stwuct cmd_thewmaw_get_num_zones_wesponse get_num_zones;
} BPMP_ABI_PACKED;

/** @} Thewmaw */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_OC_STATUS
 * @bwief Quewy ovew cuwwent status
 *
 * * Pwatfowms: T234
 * @cond bpmp_t234
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: N/A
 * * Wesponse Paywoad: @wef mwq_oc_status_wesponse
 *
 * @addtogwoup OC_status
 * @{
 */

#define OC_STATUS_MAX_SIZE	24U

/*
 * @bwief Wesponse to #MWQ_OC_STATUS
 *
 * thwot_en: Vawue fow each OC awawm whewe zewo signifies thwottwe is
 *           disabwed, and non-zewo thwottwe is enabwed.
 * event_cnt: Totaw numbew of OC events fow each OC awawm.
 *
 * mwq_wesponse::eww is 0 if the opewation was successfuw and
 * -#BPMP_ENODEV othewwise.
 */
stwuct mwq_oc_status_wesponse {
	uint8_t thwot_en[OC_STATUS_MAX_SIZE];
	uint32_t event_cnt[OC_STATUS_MAX_SIZE];
} BPMP_ABI_PACKED;

/** @} OC_status */
/** @endcond bpmp_t234 */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_CPU_VHINT
 * @bwief Quewy CPU vowtage hint data
 *
 * * Pwatfowms: T186
 * @cond bpmp_t186
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_cpu_vhint_wequest
 * * Wesponse Paywoad: N/A
 *
 * @addtogwoup Vhint
 * @{
 */

/**
 * @bwief Wequest with #MWQ_CPU_VHINT
 *
 * Used by #MWQ_CPU_VHINT caww by CCPWEX to wetwieve vowtage hint data
 * fwom BPMP to memowy space pointed by #addw. CCPWEX is wesponsibwe
 * to awwocate sizeof(cpu_vhint_data) sized bwock of memowy and
 * appwopwiatewy map it fow BPMP befowe sending the wequest.
 */
stwuct mwq_cpu_vhint_wequest {
	/** @bwief IOVA addwess fow the #cpu_vhint_data */
	uint32_t addw;
	/** @bwief ID of the cwustew whose data is wequested */
	uint32_t cwustew_id;
} BPMP_ABI_PACKED;

/**
 * @bwief Descwiption of the CPU v/f wewation
 *
 * Used by #MWQ_CPU_VHINT caww to cawwy data pointed by
 * #mwq_cpu_vhint_wequest::addw
 */
stwuct cpu_vhint_data {
	uint32_t wef_cwk_hz; /**< wefewence fwequency in Hz */
	uint16_t pdiv; /**< post dividew vawue */
	uint16_t mdiv; /**< input dividew vawue */
	uint16_t ndiv_max; /**< fMAX expwessed with max NDIV vawue */
	/** tabwe of ndiv vawues as a function of vINDEX (vowtage index) */
	uint16_t ndiv[80];
	/** minimum awwowed NDIV vawue */
	uint16_t ndiv_min;
	/** minimum awwowed vowtage hint vawue (as in vINDEX) */
	uint16_t vfwoow;
	/** maximum awwowed vowtage hint vawue (as in vINDEX) */
	uint16_t vceiw;
	/** post-muwtipwiew fow vindex vawue */
	uint16_t vindex_muwt;
	/** post-dividew fow vindex vawue */
	uint16_t vindex_div;
	/** wesewved fow futuwe use */
	uint16_t wesewved[328];
} BPMP_ABI_PACKED;

/** @} Vhint */
/** @endcond bpmp_t186 */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_ABI_WATCHET
 * @bwief ABI watchet vawue quewy
 *
 * * Pwatfowms: T186, T194
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_abi_watchet_wequest
 * * Wesponse Paywoad: @wef mwq_abi_watchet_wesponse
 * @addtogwoup ABI_info
 * @{
 */

/**
 * @bwief An ABI compatibiwity mechanism
 *
 * BPMP_ABI_WATCHET_VAWUE may incwease fow vawious weasons in a futuwe
 * wevision of this headew fiwe.
 * 1. That futuwe wevision depwecates some MWQ
 * 2. That futuwe wevision intwoduces a bweaking change to an existing
 *    MWQ ow
 * 3. A bug is discovewed in an existing impwementation of the BPMP-FW
 *    (ow possibwy one of its cwients) which wawwants depwecating that
 *    impwementation.
 */
#define BPMP_ABI_WATCHET_VAWUE 3

/**
 * @bwief Wequest with #MWQ_ABI_WATCHET.
 *
 * #watchet shouwd be #BPMP_ABI_WATCHET_VAWUE fwom the ABI headew
 * against which the wequestew was compiwed.
 *
 * If watchet is wess than BPMP's #BPMP_ABI_WATCHET_VAWUE, BPMP may
 * wepwy with mwq_wesponse::eww = -#BPMP_EWANGE to indicate that
 * BPMP-FW cannot intewopewate cowwectwy with the wequestew. Wequestew
 * shouwd cease fuwthew communication with BPMP.
 *
 * Othewwise, eww shaww be 0.
 */
stwuct mwq_abi_watchet_wequest {
	/** @bwief Wequestew's watchet vawue */
	uint16_t watchet;
};

/**
 * @bwief Wesponse to #MWQ_ABI_WATCHET
 *
 * #watchet shaww be #BPMP_ABI_WATCHET_VAWUE fwom the ABI headew
 * against which BPMP fiwwmawe was compiwed.
 *
 * If #watchet is wess than the wequestew's #BPMP_ABI_WATCHET_VAWUE,
 * the wequstew must eithew intewopewate with BPMP accowding to an ABI
 * headew vewsion with BPMP_ABI_WATCHET_VAWUE = watchet ow cease
 * communication with BPMP.
 *
 * If mwq_wesponse::eww is 0 and watchet is gweatew than ow equaw to the
 * wequestew's BPMP_ABI_WATCHET_VAWUE, the wequestew shouwd continue
 * nowmaw opewation.
 */
stwuct mwq_abi_watchet_wesponse {
	/** @bwief BPMP's watchet vawue */
	uint16_t watchet;
};

/** @} ABI_info */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_EMC_DVFS_WATENCY
 * @bwief Quewy fwequency dependent EMC DVFS watency
 *
 * * Pwatfowms: T186, T194, T234
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: N/A
 * * Wesponse Paywoad: @wef mwq_emc_dvfs_watency_wesponse
 * @addtogwoup EMC
 * @{
 */

/**
 * @bwief Used by @wef mwq_emc_dvfs_watency_wesponse
 */
stwuct emc_dvfs_watency {
	/** @bwief EMC DVFS node fwequency in kHz */
	uint32_t fweq;
	/** @bwief EMC DVFS watency in nanoseconds */
	uint32_t watency;
} BPMP_ABI_PACKED;

#define EMC_DVFS_WATENCY_MAX_SIZE	14
/**
 * @bwief Wesponse to #MWQ_EMC_DVFS_WATENCY
 */
stwuct mwq_emc_dvfs_watency_wesponse {
	/** @bwief The numbew vawid entwies in #paiws */
	uint32_t num_paiws;
	/** @bwief EMC DVFS node <fwequency, watency> infowmation */
	stwuct emc_dvfs_watency paiws[EMC_DVFS_WATENCY_MAX_SIZE];
} BPMP_ABI_PACKED;

/** @} EMC */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_EMC_DVFS_EMCHUB
 * @bwief Quewy EMC HUB fwequencies
 *
 * * Pwatfowms: T234 onwawds
 * @cond (bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: N/A
 * * Wesponse Paywoad: @wef mwq_emc_dvfs_emchub_wesponse
 * @addtogwoup EMC
 * @{
 */

/**
 * @bwief Used by @wef mwq_emc_dvfs_emchub_wesponse
 */
stwuct emc_dvfs_emchub {
	/** @bwief EMC DVFS node fwequency in kHz */
	uint32_t fweq;
	/** @bwief EMC HUB fwequency in kHz */
	uint32_t hub_fweq;
} BPMP_ABI_PACKED;

#define EMC_DVFS_EMCHUB_MAX_SIZE	EMC_DVFS_WATENCY_MAX_SIZE
/**
 * @bwief Wesponse to #MWQ_EMC_DVFS_EMCHUB
 */
stwuct mwq_emc_dvfs_emchub_wesponse {
	/** @bwief The numbew vawid entwies in #paiws */
	uint32_t num_paiws;
	/** @bwief EMC DVFS node <fwequency, hub fwequency> infowmation */
	stwuct emc_dvfs_emchub paiws[EMC_DVFS_EMCHUB_MAX_SIZE];
} BPMP_ABI_PACKED;

/** @} EMC */
/** @endcond (bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_EMC_DISP_WFW
 * @bwief Set EMC dispway WFW handshake mode of opewations
 *
 * * Pwatfowms: T234 onwawds
 * @cond (bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_emc_disp_wfw_wequest
 * * Wesponse Paywoad: N/A
 *
 * @addtogwoup EMC
 * @{
 */

enum mwq_emc_disp_wfw_mode {
	/** @bwief EMC dispway WFW handshake disabwed  */
	EMC_DISP_WFW_MODE_DISABWED = 0,
	/** @bwief EMC dispway WFW handshake enabwed  */
	EMC_DISP_WFW_MODE_ENABWED = 1,
};

/**
 * @ingwoup EMC
 * @bwief Wequest with #MWQ_EMC_DISP_WFW
 *
 * Used by the sendew of an #MWQ_EMC_DISP_WFW message to
 * wequest the mode of EMC dispway WFW handshake.
 *
 * mwq_wesponse::eww is
 * * 0: WFW mode is set successfuwwy
 * * -#BPMP_EINVAW: invawid mode wequested
 * * -#BPMP_ENOSYS: WFW handshake is not suppowted
 * * -#BPMP_EACCES: Pewmission denied
 * * -#BPMP_ENODEV: if disp wfw mwq is not suppowted by BPMP-FW
 */
stwuct mwq_emc_disp_wfw_wequest {
	/** @bwief EMC dispway WFW mode (@wef mwq_emc_disp_wfw_mode) */
	uint32_t mode;
} BPMP_ABI_PACKED;

/** @} EMC */
/** @endcond (bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_BWMGW
 * @bwief bwmgw wequests
 *
 * * Pwatfowms: T234 onwawds
 * @cond (bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_bwmgw_wequest
 * * Wesponse Paywoad: @wef mwq_bwmgw_wesponse
 *
 * @addtogwoup BWMGW
 *
 * @{
 */

enum mwq_bwmgw_cmd {
	/**
	 * @bwief Check whethew the BPMP dwivew suppowts the specified
	 * wequest type
	 *
	 * mwq_wesponse::eww is 0 if the specified wequest is
	 * suppowted and -#BPMP_ENODEV othewwise.
	 */
	CMD_BWMGW_QUEWY_ABI = 0,

	/**
	 * @bwief Detewmine dwam wate to satisfy iso/niso bw wequests
	 *
	 * mwq_wesponse::eww is
	 * *  0: cawc_wate succeeded.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 * *  -#BPMP_ENOTSUP: Wequested bw is not avaiwabwe.
	 */
	CMD_BWMGW_CAWC_WATE = 1
};

/*
 * wequest data fow wequest type CMD_BWMGW_QUEWY_ABI
 *
 * type: Wequest type fow which to check existence.
 */
stwuct cmd_bwmgw_quewy_abi_wequest {
	uint32_t type;
} BPMP_ABI_PACKED;

/**
 * @bwief Used by @wef cmd_bwmgw_cawc_wate_wequest
 */
stwuct iso_weq {
	/* @bwief bwmgw cwient ID @wef bpmp_bwmgw_ids */
	uint32_t id;
	/* @bwief bw in kBps wequested by cwient */
	uint32_t iso_bw;
} BPMP_ABI_PACKED;

#define MAX_ISO_CWIENTS		13U
/*
 * wequest data fow wequest type CMD_BWMGW_CAWC_WATE
 */
stwuct cmd_bwmgw_cawc_wate_wequest {
	/* @bwief totaw bw in kBps wequested by aww niso cwients */
	uint32_t sum_niso_bw;
	/* @bwief The numbew of iso cwients */
	uint32_t num_iso_cwients;
	/* @bwief iso_weq <id, iso_bw> infowmation */
	stwuct iso_weq isobw_weqs[MAX_ISO_CWIENTS];
} BPMP_ABI_PACKED;

/*
 * wesponse data fow wequest type CMD_BWMGW_CAWC_WATE
 *
 * iso_wate_min: min dwam data cwk wate in kHz to satisfy aww iso bw weqs
 * totaw_wate_min: min dwam data cwk wate in kHz to satisfy aww bw weqs
 */
stwuct cmd_bwmgw_cawc_wate_wesponse {
	uint32_t iso_wate_min;
	uint32_t totaw_wate_min;
} BPMP_ABI_PACKED;

/*
 * @bwief Wequest with #MWQ_BWMGW
 *
 *
 * |sub-command                 |paywoad                       |
 * |----------------------------|------------------------------|
 * |CMD_BWMGW_QUEWY_ABI         | cmd_bwmgw_quewy_abi_wequest  |
 * |CMD_BWMGW_CAWC_WATE         | cmd_bwmgw_cawc_wate_wequest  |
 *
 */
stwuct mwq_bwmgw_wequest {
	uint32_t cmd;
	union {
		stwuct cmd_bwmgw_quewy_abi_wequest quewy_abi;
		stwuct cmd_bwmgw_cawc_wate_wequest bwmgw_wate_weq;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/*
 * @bwief Wesponse to MWQ_BWMGW
 *
 * |sub-command                 |paywoad                       |
 * |----------------------------|------------------------------|
 * |CMD_BWMGW_CAWC_WATE         | cmd_bwmgw_cawc_wate_wesponse |
 */
stwuct mwq_bwmgw_wesponse {
	union {
		stwuct cmd_bwmgw_cawc_wate_wesponse bwmgw_wate_wesp;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} BWMGW */
/** @endcond (bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_BWMGW_INT
 * @bwief bpmp-integwated bwmgw wequests
 *
 * * Pwatfowms: T234 onwawds
 * @cond (bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_bwmgw_int_wequest
 * * Wesponse Paywoad: @wef mwq_bwmgw_int_wesponse
 *
 * @addtogwoup BWMGW_INT
 * @{
 */

enum mwq_bwmgw_int_cmd {
	/**
	 * @bwief Check whethew the BPMP-FW suppowts the specified
	 * wequest type
	 *
	 * mwq_wesponse::eww is 0 if the specified wequest is
	 * suppowted and -#BPMP_ENODEV othewwise.
	 */
	CMD_BWMGW_INT_QUEWY_ABI = 1,

	/**
	 * @bwief Detewmine and set dwam wate to satisfy iso/niso bw wequest
	 *
	 * mwq_wesponse::eww is
	 * *  0: wequest succeeded.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 *          set_fwequency in @wef cmd_bwmgw_int_cawc_and_set_wesponse
	 *          wiww not be set.
	 * *  -#BPMP_ENOTSUP: Wequested bw is not avaiwabwe.
	 *          set_fwequency in @wef cmd_bwmgw_int_cawc_and_set_wesponse
	 *          wiww be cuwwent dwam-cwk wate.
	 */
	CMD_BWMGW_INT_CAWC_AND_SET = 2,

	/**
	 * @bwief Set a max DWAM fwequency fow the bandwidth-managew
	 *
	 * mwq_wesponse::eww is
	 * *  0: wequest succeeded.
	 * *  -#BPMP_ENOTSUP: Wequested cap fwequency is not possibwe.
	 */
	CMD_BWMGW_INT_CAP_SET = 3
};

/*
 * wequest stwuctuwe fow wequest type CMD_BWMGW_QUEWY_ABI
 *
 * type: Wequest type fow which to check existence.
 */
stwuct cmd_bwmgw_int_quewy_abi_wequest {
	/* @bwief wequest type detewmined by @wef mwq_bwmgw_int_cmd */
	uint32_t type;
} BPMP_ABI_PACKED;

/**
 * @defgwoup bwmgw_int_unit_type BWMGW_INT fwoow unit-types
 * @addtogwoup bwmgw_int_unit_type
 * @{
 */
/** @bwief kiwobytes pew second unit-type */
#define BWMGW_INT_UNIT_KBPS  0U
/** @bwief kiwohewtz unit-type */
#define BWMGW_INT_UNIT_KHZ   1U

/** @} bwmgw_int_unit_type */

/*
 * wequest data fow wequest type CMD_BWMGW_INT_CAWC_AND_SET
 */
stwuct cmd_bwmgw_int_cawc_and_set_wequest {
	/* @bwief bwmgw cwient ID @wef bpmp_bwmgw_ids */
	uint32_t cwient_id;
	/* @bwief avewage niso bw usage in kBps wequested by cwient. */
	uint32_t niso_bw;
	/*
	 * @bwief avewage iso bw usage in kBps wequested by cwient.
	 *  Vawue is ignowed if cwient is niso. Detewmined by cwient_id.
	 */
	uint32_t iso_bw;
	/*
	 * @bwief memowy cwock fwoow wequested by cwient.
	 *  Unit detewmined by fwoow_unit.
	 */
	uint32_t mc_fwoow;
	/*
	 * @bwief toggwe to detewmine the unit-type of fwoow vawue.
	 *  See @wef bwmgw_int_unit_type definitions fow unit-type mappings.
	 */
	uint8_t fwoow_unit;
} BPMP_ABI_PACKED;

stwuct cmd_bwmgw_int_cap_set_wequest {
	/* @bwief wequested cap fwequency in Hz. */
	uint64_t wate;
} BPMP_ABI_PACKED;

/*
 * wesponse data fow wequest type CMD_BWMGW_CAWC_AND_SET
 */
stwuct cmd_bwmgw_int_cawc_and_set_wesponse {
	/* @bwief cuwwent set memowy cwock fwequency in Hz */
	uint64_t wate;
} BPMP_ABI_PACKED;

/*
 * @bwief Wequest with #MWQ_BWMGW_INT
 *
 *
 * |sub-command                 |paywoad                            |
 * |----------------------------|-----------------------------------|
 * |CMD_BWMGW_INT_QUEWY_ABI     | cmd_bwmgw_int_quewy_abi_wequest   |
 * |CMD_BWMGW_INT_CAWC_AND_SET  | cmd_bwmgw_int_cawc_and_set_wequest|
 * |CMD_BWMGW_INT_CAP_SET       | cmd_bwmgw_int_cap_set_wequest     |
 *
 */
stwuct mwq_bwmgw_int_wequest {
	uint32_t cmd;
	union {
		stwuct cmd_bwmgw_int_quewy_abi_wequest quewy_abi;
		stwuct cmd_bwmgw_int_cawc_and_set_wequest bwmgw_cawc_set_weq;
		stwuct cmd_bwmgw_int_cap_set_wequest bwmgw_cap_set_weq;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/*
 * @bwief Wesponse to MWQ_BWMGW_INT
 *
 * |sub-command                 |paywoad                                |
 * |----------------------------|---------------------------------------|
 * |CMD_BWMGW_INT_CAWC_AND_SET  | cmd_bwmgw_int_cawc_and_set_wesponse   |
 */
stwuct mwq_bwmgw_int_wesponse {
	union {
		stwuct cmd_bwmgw_int_cawc_and_set_wesponse bwmgw_cawc_set_wesp;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} BWMGW_INT */
/** @endcond (bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_ISO_CWIENT
 * @bwief ISO cwient wequests
 *
 * * Pwatfowms: T234 onwawds
 * @cond (bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_iso_cwient_wequest
 * * Wesponse Paywoad: @wef mwq_iso_cwient_wesponse
 *
 * @addtogwoup ISO_CWIENT
 * @{
 */

enum mwq_iso_cwient_cmd {
	/**
	 * @bwief Check whethew the BPMP dwivew suppowts the specified
	 * wequest type
	 *
	 * mwq_wesponse::eww is 0 if the specified wequest is
	 * suppowted and -#BPMP_ENODEV othewwise.
	 */
	CMD_ISO_CWIENT_QUEWY_ABI = 0,

	/*
	 * @bwief check fow wegaw WA fow the iso cwient. Without pwogwamming
	 * WA MC wegistews, cawcuwate and ensuwe that wegaw WA is possibwe fow
	 * iso bw wequested by the ISO cwient.
	 *
	 * mwq_wesponse::eww is
	 * *  0: check wa succeeded.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 * *  -#BPMP_EFAUWT: Wegaw WA is not possibwe fow cwient wequested iso_bw
	 */
	CMD_ISO_CWIENT_CAWCUWATE_WA = 1,

	/*
	 * @bwief set WA fow the iso cwient. Cawcuwate and pwogwam the WA/PTSA
	 * MC wegistews cowwesponding to the cwient making bw wequest
	 *
	 * mwq_wesponse::eww is
	 * *  0: set wa succeeded.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 * *  -#BPMP_EFAUWT: Faiwed to cawcuwate ow pwogwam MC wegistews.
	 */
	CMD_ISO_CWIENT_SET_WA = 2,

	/*
	 * @bwief Get max possibwe bw fow iso cwient
	 *
	 * mwq_wesponse::eww is
	 * *  0: get_max_bw succeeded.
	 * *  -#BPMP_EINVAW: Invawid wequest pawametews.
	 */
	CMD_ISO_CWIENT_GET_MAX_BW = 3
};

/*
 * wequest data fow wequest type CMD_ISO_CWIENT_QUEWY_ABI
 *
 * type: Wequest type fow which to check existence.
 */
stwuct cmd_iso_cwient_quewy_abi_wequest {
	uint32_t type;
} BPMP_ABI_PACKED;

/*
 * wequest data fow wequest type CMD_ISO_CWIENT_CAWCUWATE_WA
 *
 * id: cwient ID in @wef bpmp_bwmgw_ids
 * bw: bw wequested in kBps by cwient ID.
 * init_bw_fwoow: initiaw dwam_bw_fwoow in kBps passed by cwient ID.
 * ISO cwient wiww pewfowm mempoow awwocation and DVFS buffewing based
 * on this dwam_bw_fwoow.
 */
stwuct cmd_iso_cwient_cawcuwate_wa_wequest {
	uint32_t id;
	uint32_t bw;
	uint32_t init_bw_fwoow;
} BPMP_ABI_PACKED;

/*
 * wequest data fow wequest type CMD_ISO_CWIENT_SET_WA
 *
 * id: cwient ID in @wef bpmp_bwmgw_ids
 * bw: bw wequested in kBps by cwient ID.
 * finaw_bw_fwoow: finaw dwam_bw_fwoow in kBps.
 * Sometimes the initiaw dwam_bw_fwoow passed by ISO cwient may need to be
 * updated by considewing highew dwam fweq's. This is the finaw dwam_bw_fwoow
 * used to cawcuwate and pwogwam MC wegistews.
 */
stwuct cmd_iso_cwient_set_wa_wequest {
	uint32_t id;
	uint32_t bw;
	uint32_t finaw_bw_fwoow;
} BPMP_ABI_PACKED;

/*
 * wequest data fow wequest type CMD_ISO_CWIENT_GET_MAX_BW
 *
 * id: cwient ID in @wef bpmp_bwmgw_ids
 */
stwuct cmd_iso_cwient_get_max_bw_wequest {
	uint32_t id;
} BPMP_ABI_PACKED;

/*
 * wesponse data fow wequest type CMD_ISO_CWIENT_CAWCUWATE_WA
 *
 * wa_wate_fwoow: minimum dwam_wate_fwoow in kHz at which a wegaw wa is possibwe
 * iso_cwient_onwy_wate: Minimum dwam fweq in kHz wequiwed to satisfy this cwients
 * iso bw wequest, assuming aww othew iso cwients awe inactive
 */
stwuct cmd_iso_cwient_cawcuwate_wa_wesponse {
	uint32_t wa_wate_fwoow;
	uint32_t iso_cwient_onwy_wate;
} BPMP_ABI_PACKED;

/**
 * @bwief Used by @wef cmd_iso_cwient_get_max_bw_wesponse
 */
stwuct iso_max_bw {
	/* @bwief dwam fwequency in kHz */
	uint32_t fweq;
	/* @bwief max possibwe iso-bw in kBps */
	uint32_t iso_bw;
} BPMP_ABI_PACKED;

#define ISO_MAX_BW_MAX_SIZE	14U
/*
 * wesponse data fow wequest type CMD_ISO_CWIENT_GET_MAX_BW
 */
stwuct cmd_iso_cwient_get_max_bw_wesponse {
	/* @bwief The numbew vawid entwies in iso_max_bw paiws */
	uint32_t num_paiws;
	/* @bwief max ISOBW <dwam fweq, max bw> infowmation */
	stwuct iso_max_bw paiws[ISO_MAX_BW_MAX_SIZE];
} BPMP_ABI_PACKED;

/**
 * @bwief Wequest with #MWQ_ISO_CWIENT
 *
 * Used by the sendew of an #MWQ_ISO_CWIENT message.
 *
 * |sub-command                          |paywoad                                 |
 * |------------------------------------ |----------------------------------------|
 * |CMD_ISO_CWIENT_QUEWY_ABI		 |cmd_iso_cwient_quewy_abi_wequest        |
 * |CMD_ISO_CWIENT_CAWCUWATE_WA		 |cmd_iso_cwient_cawcuwate_wa_wequest     |
 * |CMD_ISO_CWIENT_SET_WA		 |cmd_iso_cwient_set_wa_wequest           |
 * |CMD_ISO_CWIENT_GET_MAX_BW		 |cmd_iso_cwient_get_max_bw_wequest       |
 *
 */

stwuct mwq_iso_cwient_wequest {
	/* Type of wequest. Vawues wisted in enum mwq_iso_cwient_cmd */
	uint32_t cmd;
	union {
		stwuct cmd_iso_cwient_quewy_abi_wequest quewy_abi;
		stwuct cmd_iso_cwient_cawcuwate_wa_wequest cawcuwate_wa_weq;
		stwuct cmd_iso_cwient_set_wa_wequest set_wa_weq;
		stwuct cmd_iso_cwient_get_max_bw_wequest max_isobw_weq;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse to MWQ_ISO_CWIENT
 *
 * Each sub-command suppowted by @wef mwq_iso_cwient_wequest may wetuwn
 * sub-command-specific data. Some do and some do not as indicated in
 * the fowwowing tabwe
 *
 * |sub-command                  |paywoad                             |
 * |---------------------------- |------------------------------------|
 * |CMD_ISO_CWIENT_CAWCUWATE_WA  |cmd_iso_cwient_cawcuwate_wa_wesponse|
 * |CMD_ISO_CWIENT_SET_WA        |N/A                                 |
 * |CMD_ISO_CWIENT_GET_MAX_BW    |cmd_iso_cwient_get_max_bw_wesponse  |
 *
 */

stwuct mwq_iso_cwient_wesponse {
	union {
		stwuct cmd_iso_cwient_cawcuwate_wa_wesponse cawcuwate_wa_wesp;
		stwuct cmd_iso_cwient_get_max_bw_wesponse max_isobw_wesp;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} ISO_CWIENT */
/** @endcond (bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_CPU_NDIV_WIMITS
 * @bwief CPU fweq. wimits in ndiv
 *
 * * Pwatfowms: T194 onwawds
 * @cond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_cpu_ndiv_wimits_wequest
 * * Wesponse Paywoad: @wef mwq_cpu_ndiv_wimits_wesponse
 * @addtogwoup CPU
 * @{
 */

/**
 * @bwief Wequest fow ndiv wimits of a cwustew
 */
stwuct mwq_cpu_ndiv_wimits_wequest {
	/** @bwief Enum cwustew_id */
	uint32_t cwustew_id;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse to #MWQ_CPU_NDIV_WIMITS
 */
stwuct mwq_cpu_ndiv_wimits_wesponse {
	/** @bwief Wefewence fwequency in Hz */
	uint32_t wef_cwk_hz;
	/** @bwief Post dividew vawue */
	uint16_t pdiv;
	/** @bwief Input dividew vawue */
	uint16_t mdiv;
	/** @bwief FMAX expwessed with max NDIV vawue */
	uint16_t ndiv_max;
	/** @bwief Minimum awwowed NDIV vawue */
	uint16_t ndiv_min;
} BPMP_ABI_PACKED;

/** @} CPU */
/** @endcond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_CPU_AUTO_CC3
 * @bwief Quewy CPU cwustew auto-CC3 configuwation
 *
 * * Pwatfowms: T194
 * @cond bpmp_t194
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_cpu_auto_cc3_wequest
 * * Wesponse Paywoad: @wef mwq_cpu_auto_cc3_wesponse
 * @addtogwoup CC3
 *
 * Quewies fwom BPMP auto-CC3 configuwation (awwowed/not awwowed) fow a
 * specified cwustew. CCPWEX s/w uses this infowmation to ovewwide its own
 * device twee auto-CC3 settings, so that BPMP device twee is a singwe souwce of
 * auto-CC3 pwatfowm configuwation.
 *
 * @{
 */

/**
 * @bwief Wequest fow auto-CC3 configuwation of a cwustew
 */
stwuct mwq_cpu_auto_cc3_wequest {
	/** @bwief Enum cwustew_id (wogicaw cwustew id, known to CCPWEX s/w) */
	uint32_t cwustew_id;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse to #MWQ_CPU_AUTO_CC3
 */
stwuct mwq_cpu_auto_cc3_wesponse {
	/**
	 * @bwief auto-CC3 configuwation
	 *
	 * - bits[31..10] wesewved.
	 * - bits[9..1] cc3 ndiv
	 * - bit [0] if "1" auto-CC3 is awwowed, if "0" auto-CC3 is not awwowed
	 */
	uint32_t auto_cc3_config;
} BPMP_ABI_PACKED;

/** @} CC3 */
/** @endcond bpmp_t194 */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_WINGBUF_CONSOWE
 * @bwief A wing buffew debug consowe fow BPMP
 * @addtogwoup WingbufConsowe
 *
 * The wing buffew debug consowe aims to be a substitute fow the UAWT debug
 * consowe. The debug consowe is impwemented with two wing buffews in the
 * BPMP-FW, the WX (weceive) and TX (twansmit) buffews. Chawactews can be wead
 * and wwitten to the buffews by the host via the MWQ intewface.
 *
 * @{
 */

/**
 * @bwief Maximum numbew of bytes twansfewwed in a singwe wwite command to the
 * BPMP
 *
 * This is detewmined by the numbew of fwee bytes in the message stwuct,
 * wounded down to a muwtipwe of fouw.
 */
#define MWQ_WINGBUF_CONSOWE_MAX_WWITE_WEN 112

/**
 * @bwief Maximum numbew of bytes twansfewwed in a singwe wead command to the
 * BPMP
 *
 * This is detewmined by the numbew of fwee bytes in the message stwuct,
 * wounded down to a muwtipwe of fouw.
 */
#define MWQ_WINGBUF_CONSOWE_MAX_WEAD_WEN 116

enum mwq_wingbuf_consowe_host_to_bpmp_cmd {
	/**
	 * @bwief Check whethew the BPMP dwivew suppowts the specified wequest
	 * type
	 *
	 * mwq_wesponse::eww is 0 if the specified wequest is suppowted and
	 * -#BPMP_ENODEV othewwise
	 */
	CMD_WINGBUF_CONSOWE_QUEWY_ABI = 0,
	/**
	 * @bwief Pewfowm a wead opewation on the BPMP TX buffew
	 *
	 * mwq_wesponse::eww is 0
	 */
	CMD_WINGBUF_CONSOWE_WEAD = 1,
	/**
	 * @bwief Pewfowm a wwite opewation on the BPMP WX buffew
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw and
	 * -#BPMP_ENODEV othewwise
	 */
	CMD_WINGBUF_CONSOWE_WWITE = 2,
	/**
	 * @bwief Get the wength of the buffew and the physicaw addwesses of
	 * the buffew data and the head and taiw countews
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw and
	 * -#BPMP_ENODEV othewwise
	 */
	CMD_WINGBUF_CONSOWE_GET_FIFO = 3,
};

/**
 * @ingwoup WingbufConsowe
 * @bwief Host->BPMP wequest data fow wequest type
 * #CMD_WINGBUF_CONSOWE_QUEWY_ABI
 */
stwuct cmd_wingbuf_consowe_quewy_abi_weq {
	/** @bwief Command identifiew to be quewied */
	uint32_t cmd;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_wingbuf_consowe_quewy_abi_wesp {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/**
 * @ingwoup WingbufConsowe
 * @bwief Host->BPMP wequest data fow wequest type #CMD_WINGBUF_CONSOWE_WEAD
 */
stwuct cmd_wingbuf_consowe_wead_weq {
	/**
	 * @bwief Numbew of bytes wequested to be wead fwom the BPMP TX buffew
	 */
	uint8_t wen;
} BPMP_ABI_PACKED;

/**
 * @ingwoup WingbufConsowe
 * @bwief BPMP->Host wesponse data fow wequest type #CMD_WINGBUF_CONSOWE_WEAD
 */
stwuct cmd_wingbuf_consowe_wead_wesp {
	/** @bwief The actuaw data wead fwom the BPMP TX buffew */
	uint8_t data[MWQ_WINGBUF_CONSOWE_MAX_WEAD_WEN];
	/** @bwief Numbew of bytes in cmd_wingbuf_consowe_wead_wesp::data */
	uint8_t wen;
} BPMP_ABI_PACKED;

/**
 * @ingwoup WingbufConsowe
 * @bwief Host->BPMP wequest data fow wequest type #CMD_WINGBUF_CONSOWE_WWITE
 */
stwuct cmd_wingbuf_consowe_wwite_weq {
	/** @bwief The actuaw data to be wwitten to the BPMP WX buffew */
	uint8_t data[MWQ_WINGBUF_CONSOWE_MAX_WWITE_WEN];
	/** @bwief Numbew of bytes in cmd_wingbuf_consowe_wwite_weq::data */
	uint8_t wen;
} BPMP_ABI_PACKED;

/**
 * @ingwoup WingbufConsowe
 * @bwief BPMP->Host wesponse data fow wequest type #CMD_WINGBUF_CONSOWE_WWITE
 */
stwuct cmd_wingbuf_consowe_wwite_wesp {
	/** @bwief Numbew of bytes of avaiwabwe space in the BPMP WX buffew */
	uint32_t space_avaiw;
	/** @bwief Numbew of bytes that wewe wwitten to the BPMP WX buffew */
	uint8_t wen;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_wingbuf_consowe_get_fifo_weq {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/**
 * @ingwoup WingbufConsowe
 * @bwief BPMP->Host wepwy data fow wequest type #CMD_WINGBUF_CONSOWE_GET_FIFO
 */
stwuct cmd_wingbuf_consowe_get_fifo_wesp {
	/** @bwief Physicaw addwess of the BPMP TX buffew */
	uint64_t bpmp_tx_buf_addw;
	/** @bwief Physicaw addwess of the BPMP TX buffew head countew */
	uint64_t bpmp_tx_head_addw;
	/** @bwief Physicaw addwess of the BPMP TX buffew taiw countew */
	uint64_t bpmp_tx_taiw_addw;
	/** @bwief Wength of the BPMP TX buffew */
	uint32_t bpmp_tx_buf_wen;
} BPMP_ABI_PACKED;

/**
 * @ingwoup WingbufConsowe
 * @bwief Host->BPMP wequest data.
 *
 * Wepwy type is union #mwq_wingbuf_consowe_bpmp_to_host_wesponse .
 */
stwuct mwq_wingbuf_consowe_host_to_bpmp_wequest {
	/**
	 * @bwief Type of wequest. Vawues wisted in enum
	 * #mwq_wingbuf_consowe_host_to_bpmp_cmd.
	 */
	uint32_t type;
	/** @bwief  wequest type specific pawametews. */
	union {
		stwuct cmd_wingbuf_consowe_quewy_abi_weq quewy_abi;
		stwuct cmd_wingbuf_consowe_wead_weq wead;
		stwuct cmd_wingbuf_consowe_wwite_weq wwite;
		stwuct cmd_wingbuf_consowe_get_fifo_weq get_fifo;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup WingbufConsowe
 * @bwief Host->BPMP wepwy data
 *
 * In wesponse to stwuct #mwq_wingbuf_consowe_host_to_bpmp_wequest.
 */
union mwq_wingbuf_consowe_bpmp_to_host_wesponse {
	stwuct cmd_wingbuf_consowe_quewy_abi_wesp quewy_abi;
	stwuct cmd_wingbuf_consowe_wead_wesp wead;
	stwuct cmd_wingbuf_consowe_wwite_wesp wwite;
	stwuct cmd_wingbuf_consowe_get_fifo_wesp get_fifo;
} BPMP_ABI_PACKED;

/** @} WingbufConsowe */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_STWAP
 * @bwief Set a stwap vawue contwowwed by BPMP
 *
 * * Pwatfowms: T194 onwawds
 * @cond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_stwap_wequest
 * * Wesponse Paywoad: N/A
 * @addtogwoup Stwap
 *
 * A stwap is an input that is sampwed by a hawdwawe unit duwing the
 * unit's stawtup pwocess. The sampwed vawue of a stwap affects the
 * behaviow of the unit untiw the unit is westawted. Many hawdwawe
 * units sampwe theiw stwaps at the instant that theiw wesets awe
 * deassewted.
 *
 * BPMP owns wegistews which act as stwaps to vawious units. It
 * exposes wimited contwow of those stwaps via #MWQ_STWAP.
 *
 * @{
 */
enum mwq_stwap_cmd {
	/** @pwivate */
	STWAP_WESEWVED = 0,
	/** @bwief Set a stwap vawue */
	STWAP_SET = 1
};

/**
 * @bwief Wequest with #MWQ_STWAP
 */
stwuct mwq_stwap_wequest {
	/** @bwief @wef mwq_stwap_cmd */
	uint32_t cmd;
	/** @bwief Stwap ID fwom @wef Stwap_Identifiews */
	uint32_t id;
	/** @bwief Desiwed vawue fow stwap (if cmd is #STWAP_SET) */
	uint32_t vawue;
} BPMP_ABI_PACKED;

/** @} Stwap */
/** @endcond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_UPHY
 * @bwief Pewfowm a UPHY opewation
 *
 * * Pwatfowms: T194 onwawds
 * @cond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_uphy_wequest
 * * Wesponse Paywoad: @wef mwq_uphy_wesponse
 *
 * @addtogwoup UPHY
 * @{
 */
enum {
	CMD_UPHY_PCIE_WANE_MAWGIN_CONTWOW = 1,
	CMD_UPHY_PCIE_WANE_MAWGIN_STATUS = 2,
	CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_INIT = 3,
	CMD_UPHY_PCIE_CONTWOWWEW_STATE = 4,
	CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_OFF = 5,
	CMD_UPHY_DISPWAY_POWT_INIT = 6,
	CMD_UPHY_DISPWAY_POWT_OFF = 7,
	CMD_UPHY_XUSB_DYN_WANES_WESTOWE = 8,
	CMD_UPHY_MAX,
};

stwuct cmd_uphy_mawgin_contwow_wequest {
	/** @bwief Enabwe mawgin */
	int32_t en;
	/** @bwief Cweaw the numbew of ewwow and sections */
	int32_t cww;
	/** @bwief Set x offset (1's compwement) fow weft/wight mawgin type (y shouwd be 0) */
	uint32_t x;
	/** @bwief Set y offset (1's compwement) fow weft/wight mawgin type (x shouwd be 0) */
	uint32_t y;
	/** @bwief Set numbew of bit bwocks fow each mawgin section */
	uint32_t nbwks;
} BPMP_ABI_PACKED;

stwuct cmd_uphy_mawgin_status_wesponse {
	/** @bwief Numbew of ewwows obsewved */
	uint32_t status;
} BPMP_ABI_PACKED;

stwuct cmd_uphy_ep_contwowwew_pww_init_wequest {
	/** @bwief EP contwowwew numbew, T194 vawid: 0, 4, 5; T234 vawid: 5, 6, 7, 10; T239 vawid: 0 */
	uint8_t ep_contwowwew;
} BPMP_ABI_PACKED;

stwuct cmd_uphy_pcie_contwowwew_state_wequest {
	/** @bwief PCIE contwowwew numbew, T194 vawid: 0-4; T234 vawid: 0-10; T239 vawid: 0-3 */
	uint8_t pcie_contwowwew;
	uint8_t enabwe;
} BPMP_ABI_PACKED;

stwuct cmd_uphy_ep_contwowwew_pww_off_wequest {
	/** @bwief EP contwowwew numbew, T194 vawid: 0, 4, 5; T234 vawid: 5, 6, 7, 10; T239 vawid: 0 */
	uint8_t ep_contwowwew;
} BPMP_ABI_PACKED;

stwuct cmd_uphy_dispway_powt_init_wequest {
	/** @bwief DispwayPowt wink wate, T239 vawid: 1620, 2700, 5400, 8100, 2160, 2430, 3240, 4320, 6750 */
	uint16_t wink_wate;
	/** @bwief 1: wane 0; 2: wane 1; 3: wane 0 and 1 */
	uint16_t wanes_bitmap;
} BPMP_ABI_PACKED;

stwuct cmd_uphy_xusb_dyn_wanes_westowe_wequest {
	/** @bwief 1: wane 0; 2: wane 1; 3: wane 0 and 1 */
	uint16_t wanes_bitmap;
} BPMP_ABI_PACKED;

/**
 * @ingwoup UPHY
 * @bwief Wequest with #MWQ_UPHY
 *
 * Used by the sendew of an #MWQ_UPHY message to contwow UPHY.
 * The uphy_wequest is spwit into sevewaw sub-commands. CMD_UPHY_PCIE_WANE_MAWGIN_STATUS
 * wequiwes no additionaw data. Othews have a sub-command specific paywoad. Bewow tabwe
 * shows sub-commands with theiw cowwesponding paywoad data.
 *
 * |sub-command                          |paywoad                                 |
 * |------------------------------------ |----------------------------------------|
 * |CMD_UPHY_PCIE_WANE_MAWGIN_CONTWOW    |uphy_set_mawgin_contwow                 |
 * |CMD_UPHY_PCIE_WANE_MAWGIN_STATUS     |                                        |
 * |CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_INIT |cmd_uphy_ep_contwowwew_pww_init_wequest |
 * |CMD_UPHY_PCIE_CONTWOWWEW_STATE       |cmd_uphy_pcie_contwowwew_state_wequest  |
 * |CMD_UPHY_PCIE_EP_CONTWOWWEW_PWW_OFF  |cmd_uphy_ep_contwowwew_pww_off_wequest  |
 * |CMD_UPHY_PCIE_DISPWAY_POWT_INIT      |cmd_uphy_dispway_powt_init_wequest      |
 * |CMD_UPHY_PCIE_DISPWAY_POWT_OFF       |                                        |
 * |CMD_UPHY_XUSB_DYN_WANES_WESTOWE      |cmd_uphy_xusb_dyn_wanes_westowe_wequest |
 *
 */

stwuct mwq_uphy_wequest {
	/** @bwief Wane numbew. */
	uint16_t wane;
	/** @bwief Sub-command id. */
	uint16_t cmd;

	union {
		stwuct cmd_uphy_mawgin_contwow_wequest uphy_set_mawgin_contwow;
		stwuct cmd_uphy_ep_contwowwew_pww_init_wequest ep_ctwww_pww_init;
		stwuct cmd_uphy_pcie_contwowwew_state_wequest contwowwew_state;
		stwuct cmd_uphy_ep_contwowwew_pww_off_wequest ep_ctwww_pww_off;
		stwuct cmd_uphy_dispway_powt_init_wequest dispway_powt_init;
		stwuct cmd_uphy_xusb_dyn_wanes_westowe_wequest xusb_dyn_wanes_westowe;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup UPHY
 * @bwief Wesponse to MWQ_UPHY
 *
 * Each sub-command suppowted by @wef mwq_uphy_wequest may wetuwn
 * sub-command-specific data. Some do and some do not as indicated in
 * the fowwowing tabwe
 *
 * |sub-command                       |paywoad                 |
 * |----------------------------      |------------------------|
 * |CMD_UPHY_PCIE_WANE_MAWGIN_CONTWOW |                        |
 * |CMD_UPHY_PCIE_WANE_MAWGIN_STATUS  |uphy_get_mawgin_status  |
 *
 */

stwuct mwq_uphy_wesponse {
	union {
		stwuct cmd_uphy_mawgin_status_wesponse uphy_get_mawgin_status;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} UPHY */
/** @endcond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500) */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_FMON
 * @bwief Pewfowm a fwequency monitow configuwation opewations
 *
 * * Pwatfowms: T194 onwawds
 * @cond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500)
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_fmon_wequest
 * * Wesponse Paywoad: @wef mwq_fmon_wesponse
 * @endcond (bpmp_t194 || bpmp_t234 || bpmp_t239 || bpmp_th500)
 *
 * @addtogwoup FMON
 * @{
 * @cond (bpmp_t194 || bpmp_t234)
 */
enum {
	/**
	 * @bwief Cwamp FMON configuwation to specified wate.
	 *
	 * The monitowed cwock must be wunning fow cwamp to succeed. If
	 * cwamped, FMON configuwation is pwesewved when cwock wate
	 * and/ow state is changed.
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_EACCES: FMON access ewwow @n
	 * -#BPMP_EBADCMD if subcommand is not suppowted @n
	 * -#BPMP_EBADSWT: cwamp FMON on cwustew with auto-CC3 enabwed @n
	 * -#BPMP_EBUSY: fmon is awweady cwamped at diffewent wate @n
	 * -#BPMP_EFAUWT: sewf-diagnostic ewwow @n
	 * -#BPMP_EINVAW: invawid FMON configuwation @n
	 * -#BPMP_EOPNOTSUPP: not in pwoduction mode @n
	 * -#BPMP_ENODEV: invawid cwk_id @n
	 * -#BPMP_ENOENT: no cawibwation data, uninitiawized @n
	 * -#BPMP_ENOTSUP: avfs config not set @n
	 * -#BPMP_ENOSYS: cwamp FMON on cwustew cwock w/ no NAFWW @n
	 * -#BPMP_ETIMEDOUT: opewation timed out @n
	 */
	CMD_FMON_GEAW_CWAMP = 1,
	/**
	 * @bwief Wewease cwamped FMON configuwation.
	 *
	 * Awwow FMON configuwation to fowwow monitowed cwock wate
	 * and/ow state changes.
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_EBADCMD if subcommand is not suppowted @n
	 * -#BPMP_ENODEV: invawid cwk_id @n
	 * -#BPMP_ENOENT: no cawibwation data, uninitiawized @n
	 * -#BPMP_ENOTSUP: avfs config not set @n
	 * -#BPMP_EOPNOTSUPP: not in pwoduction mode @n
	 */
	CMD_FMON_GEAW_FWEE = 2,
	/**
	 * @bwief Wetuwn wate FMON is cwamped at, ow 0 if FMON is not
	 *         cwamped.
	 *
	 * Inhewentwy wacy, since cwamp state can be changed
	 * concuwwentwy. Usefuw fow testing.
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_EBADCMD if subcommand is not suppowted @n
	 * -#BPMP_ENODEV: invawid cwk_id @n
	 * -#BPMP_ENOENT: no cawibwation data, uninitiawized @n
	 * -#BPMP_ENOTSUP: avfs config not set @n
	 * -#BPMP_EOPNOTSUPP: not in pwoduction mode @n
	 */
	CMD_FMON_GEAW_GET = 3,
	/**
	 * @bwief Wetuwn cuwwent status of FMON fauwts detected by FMON
	 *         h/w ow s/w since wast invocation of this command.
	 *         Cweaws fauwt status.
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_EBADCMD if subcommand is not suppowted @n
	 * -#BPMP_EINVAW: invawid fauwt type @n
	 * -#BPMP_ENODEV: invawid cwk_id @n
	 * -#BPMP_ENOENT: no cawibwation data, uninitiawized @n
	 * -#BPMP_ENOTSUP: avfs config not set @n
	 * -#BPMP_EOPNOTSUPP: not in pwoduction mode @n
	 */
	CMD_FMON_FAUWT_STS_GET = 4,
};

/**
 * @cond DEPWECATED
 * Kept fow backwawd compatibiwity
 */
#define CMD_FMON_NUM		4

/** @endcond DEPWECATED */

/**
 * @defgwoup fmon_fauwt_type FMON fauwt type
 * @addtogwoup fmon_fauwt_type
 * @{
 */
/** @bwief Aww detected FMON fauwts (h/w ow s/w) */
#define FMON_FAUWT_TYPE_AWW		0U
/** @bwief FMON fauwts detected by h/w */
#define FMON_FAUWT_TYPE_HW		1U
/** @bwief FMON fauwts detected by s/w */
#define FMON_FAUWT_TYPE_SW		2U

/** @} fmon_fauwt_type */


stwuct cmd_fmon_geaw_cwamp_wequest {
	int32_t unused;
	int64_t wate;
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_fmon_geaw_cwamp_wesponse {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_fmon_geaw_fwee_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_fmon_geaw_fwee_wesponse {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

/** @pwivate */
stwuct cmd_fmon_geaw_get_wequest {
	BPMP_ABI_EMPTY
} BPMP_ABI_PACKED;

stwuct cmd_fmon_geaw_get_wesponse {
	int64_t wate;
} BPMP_ABI_PACKED;

stwuct cmd_fmon_fauwt_sts_get_wequest {
	uint32_t fauwt_type;	/**< @wef fmon_fauwt_type */
} BPMP_ABI_PACKED;

stwuct cmd_fmon_fauwt_sts_get_wesponse {
	uint32_t fauwt_sts;
} BPMP_ABI_PACKED;

/**
 * @ingwoup FMON
 * @bwief Wequest with #MWQ_FMON
 *
 * Used by the sendew of an #MWQ_FMON message to configuwe cwock
 * fwequency monitows. The FMON wequest is spwit into sevewaw
 * sub-commands. Some sub-commands wequiwe no additionaw data.
 * Othews have a sub-command specific paywoad
 *
 * |sub-command                 |paywoad                |
 * |----------------------------|-----------------------|
 * |CMD_FMON_GEAW_CWAMP         |fmon_geaw_cwamp        |
 * |CMD_FMON_GEAW_FWEE          |-                      |
 * |CMD_FMON_GEAW_GET           |-                      |
 * |CMD_FMON_FAUWT_STS_GET      |fmon_fauwt_sts_get     |
 *
 */
stwuct mwq_fmon_wequest {
	/** @bwief Sub-command and cwock id concatenated to 32-bit wowd.
	 * - bits[31..24] is the sub-cmd.
	 * - bits[23..0] is monitowed cwock id used to sewect tawget
	 *   FMON
	 */
	uint32_t cmd_and_id;

	union {
		stwuct cmd_fmon_geaw_cwamp_wequest fmon_geaw_cwamp;
		/** @pwivate */
		stwuct cmd_fmon_geaw_fwee_wequest fmon_geaw_fwee;
		/** @pwivate */
		stwuct cmd_fmon_geaw_get_wequest fmon_geaw_get;
		stwuct cmd_fmon_fauwt_sts_get_wequest fmon_fauwt_sts_get;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup FMON
 * @bwief Wesponse to MWQ_FMON
 *
 * Each sub-command suppowted by @wef mwq_fmon_wequest may
 * wetuwn sub-command-specific data as indicated bewow.
 *
 * |sub-command                 |paywoad                 |
 * |----------------------------|------------------------|
 * |CMD_FMON_GEAW_CWAMP         |-                       |
 * |CMD_FMON_GEAW_FWEE          |-                       |
 * |CMD_FMON_GEAW_GET           |fmon_geaw_get           |
 * |CMD_FMON_FAUWT_STS_GET      |fmon_fauwt_sts_get      |
 *
 */

stwuct mwq_fmon_wesponse {
	union {
		/** @pwivate */
		stwuct cmd_fmon_geaw_cwamp_wesponse fmon_geaw_cwamp;
		/** @pwivate */
		stwuct cmd_fmon_geaw_fwee_wesponse fmon_geaw_fwee;
		stwuct cmd_fmon_geaw_get_wesponse fmon_geaw_get;
		stwuct cmd_fmon_fauwt_sts_get_wesponse fmon_fauwt_sts_get;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @endcond (bpmp_t194 || bpmp_t234) */
/** @} FMON */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_EC
 * @bwief Pwovide status infowmation on fauwts wepowted by Ewwow
 *        Cowwatow (EC) to HSM.
 *
 * * Pwatfowms: T194
 * @cond bpmp_t194
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_ec_wequest
 * * Wesponse Paywoad: @wef mwq_ec_wesponse
 *
 * @note This MWQ ABI is undew constwuction, and subject to change
 *
 * @endcond bpmp_t194
 * @addtogwoup EC
 * @{
 * @cond bpmp_t194
 */
enum {
	/**
	 * @cond DEPWECATED
	 * @bwief Wetwieve specified EC status.
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_ENODEV if tawget EC is not owned by BPMP @n
	 * -#BPMP_EACCES if tawget EC powew domain is tuwned off @n
	 * -#BPMP_EBADCMD if subcommand is not suppowted
	 * @endcond DEPWECATED
	 */
	CMD_EC_STATUS_GET = 1,	/* depwecated */

	/**
	 * @bwief Wetwieve specified EC extended status (incwudes ewwow
	 *        countew and usew vawues).
	 *
	 * mwq_wesponse::eww is 0 if the opewation was successfuw, ow @n
	 * -#BPMP_ENODEV if tawget EC is not owned by BPMP @n
	 * -#BPMP_EACCES if tawget EC powew domain is tuwned off @n
	 * -#BPMP_EBADCMD if subcommand is not suppowted
	 */
	CMD_EC_STATUS_EX_GET = 2,
	CMD_EC_NUM,
};

/** @bwief BPMP ECs ewwow types */
enum bpmp_ec_eww_type {
	/** @bwief Pawity ewwow on intewnaw data path
	 *
	 *  Ewwow descwiptow @wef ec_eww_simpwe_desc.
	 */
	EC_EWW_TYPE_PAWITY_INTEWNAW		= 1,

	/** @bwief ECC SEC ewwow on intewnaw data path
	 *
	 *  Ewwow descwiptow @wef ec_eww_simpwe_desc.
	 */
	EC_EWW_TYPE_ECC_SEC_INTEWNAW		= 2,

	/** @bwief ECC DED ewwow on intewnaw data path
	 *
	 *  Ewwow descwiptow @wef ec_eww_simpwe_desc.
	 */
	EC_EWW_TYPE_ECC_DED_INTEWNAW		= 3,

	/** @bwief Compawatow ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_simpwe_desc.
	 */
	EC_EWW_TYPE_COMPAWATOW			= 4,

	/** @bwief Wegistew pawity ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_weg_pawity_desc.
	 */
	EC_EWW_TYPE_WEGISTEW_PAWITY		= 5,

	/** @bwief Pawity ewwow fwom on-chip SWAM/FIFO
	 *
	 *  Ewwow descwiptow @wef ec_eww_simpwe_desc.
	 */
	EC_EWW_TYPE_PAWITY_SWAM			= 6,

	/** @bwief Cwock Monitow ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_fmon_desc.
	 */
	EC_EWW_TYPE_CWOCK_MONITOW		= 9,

	/** @bwief Vowtage Monitow ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_vmon_desc.
	 */
	EC_EWW_TYPE_VOWTAGE_MONITOW		= 10,

	/** @bwief SW Cowwectabwe ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_sw_ewwow_desc.
	 */
	EC_EWW_TYPE_SW_COWWECTABWE		= 16,

	/** @bwief SW Uncowwectabwe ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_sw_ewwow_desc.
	 */
	EC_EWW_TYPE_SW_UNCOWWECTABWE		= 17,

	/** @bwief Othew HW Cowwectabwe ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_simpwe_desc.
	 */
	EC_EWW_TYPE_OTHEW_HW_COWWECTABWE	= 32,

	/** @bwief Othew HW Uncowwectabwe ewwow
	 *
	 *  Ewwow descwiptow @wef ec_eww_simpwe_desc.
	 */
	EC_EWW_TYPE_OTHEW_HW_UNCOWWECTABWE	= 33,
};

/** @bwief Gwoup of wegistews with pawity ewwow. */
enum ec_wegistews_gwoup {
	/** @bwief Functionaw wegistews gwoup */
	EC_EWW_GWOUP_FUNC_WEG		= 0U,
	/** @bwief SCW wegistews gwoup */
	EC_EWW_GWOUP_SCW_WEG		= 1U,
};

/**
 * @defgwoup bpmp_ec_status_fwags EC Status Fwags
 * @addtogwoup bpmp_ec_status_fwags
 * @{
 */
/** @bwief No EC ewwow found fwag */
#define EC_STATUS_FWAG_NO_EWWOW		0x0001U
/** @bwief Wast EC ewwow found fwag */
#define EC_STATUS_FWAG_WAST_EWWOW	0x0002U
/** @bwief EC watent ewwow fwag */
#define EC_STATUS_FWAG_WATENT_EWWOW	0x0004U

/** @} bpmp_ec_status_fwags */

/**
 * @defgwoup bpmp_ec_desc_fwags EC Descwiptow Fwags
 * @addtogwoup bpmp_ec_desc_fwags
 * @{
 */
/** @bwief EC descwiptow ewwow wesowved fwag */
#define EC_DESC_FWAG_WESOWVED		0x0001U
/** @bwief EC descwiptow faiwed to wetwieve id fwag */
#define EC_DESC_FWAG_NO_ID		0x0002U

/** @} bpmp_ec_desc_fwags */

/**
 * |ewwow type                       | fmon_cwk_id vawues        |
 * |---------------------------------|---------------------------|
 * |@wef EC_EWW_TYPE_CWOCK_MONITOW   |@wef bpmp_cwock_ids        |
 */
stwuct ec_eww_fmon_desc {
	/** @bwief Bitmask of @wef bpmp_ec_desc_fwags  */
	uint16_t desc_fwags;
	/** @bwief FMON monitowed cwock id */
	uint16_t fmon_cwk_id;
	/**
	 * @bwief Bitmask of fauwt fwags
	 *
	 * @wef bpmp_fmon_fauwts_fwags
	 */
	uint32_t fmon_fauwts;
	/** @bwief FMON fauwts access ewwow */
	int32_t fmon_access_ewwow;
} BPMP_ABI_PACKED;

/**
 * | ewwow type                      | vmon_adc_id vawues        |
 * |---------------------------------|---------------------------|
 * |@wef EC_EWW_TYPE_VOWTAGE_MONITOW |@wef bpmp_adc_ids          |
 */
stwuct ec_eww_vmon_desc {
	/** @bwief Bitmask of @wef bpmp_ec_desc_fwags  */
	uint16_t desc_fwags;
	/** @bwief VMON waiw adc id */
	uint16_t vmon_adc_id;
	/** @bwief Bitmask of bpmp_vmon_fauwts_fwags */
	uint32_t vmon_fauwts;
	/** @bwief VMON fauwts access ewwow */
	int32_t vmon_access_ewwow;
} BPMP_ABI_PACKED;

/**
 * |ewwow type                       | weg_id vawues         |
 * |---------------------------------|-----------------------|
 * |@wef EC_EWW_TYPE_WEGISTEW_PAWITY | bpmp_ec_wegistews_ids |
 */
stwuct ec_eww_weg_pawity_desc {
	/** @bwief Bitmask of @wef bpmp_ec_desc_fwags  */
	uint16_t desc_fwags;
	/** @bwief Wegistew id */
	uint16_t weg_id;
	/** @bwief Wegistew gwoup @wef ec_wegistews_gwoup */
	uint16_t weg_gwoup;
} BPMP_ABI_PACKED;

/**
 * |ewwow type                        | eww_souwce_id vawues |
 * |--------------------------------- |----------------------|
 * |@wef EC_EWW_TYPE_SW_COWWECTABWE   | bpmp_ec_ce_swd_ids   |
 * |@wef EC_EWW_TYPE_SW_UNCOWWECTABWE | bpmp_ec_ue_swd_ids   |
 */
stwuct ec_eww_sw_ewwow_desc {
	/** @bwief Bitmask of @wef bpmp_ec_desc_fwags  */
	uint16_t desc_fwags;
	/** @bwief Ewwow souwce id */
	uint16_t eww_souwce_id;
	/** @bwief Sw ewwow data */
	uint32_t sw_ewwow_data;
} BPMP_ABI_PACKED;

/**
 * |ewwow type                              | eww_souwce_id vawues   |
 * |----------------------------------------|------------------------|
 * |@wef EC_EWW_TYPE_PAWITY_INTEWNAW        |  bpmp_ec_ipath_ids     |
 * |@wef EC_EWW_TYPE_ECC_SEC_INTEWNAW       |  bpmp_ec_ipath_ids     |
 * |@wef EC_EWW_TYPE_ECC_DED_INTEWNAW       |  bpmp_ec_ipath_ids     |
 * |@wef EC_EWW_TYPE_COMPAWATOW             |  bpmp_ec_compawatow_ids|
 * |@wef EC_EWW_TYPE_OTHEW_HW_COWWECTABWE   |  bpmp_ec_misc_hwd_ids  |
 * |@wef EC_EWW_TYPE_OTHEW_HW_UNCOWWECTABWE |  bpmp_ec_misc_hwd_ids  |
 * |@wef EC_EWW_TYPE_PAWITY_SWAM            |  bpmp_cwock_ids        |
 */
stwuct ec_eww_simpwe_desc {
	/** @bwief Bitmask of @wef bpmp_ec_desc_fwags  */
	uint16_t desc_fwags;
	/** @bwief Ewwow souwce id. Id space depends on ewwow type. */
	uint16_t eww_souwce_id;
} BPMP_ABI_PACKED;

/** @bwief Union of EC ewwow descwiptows */
union ec_eww_desc {
	stwuct ec_eww_fmon_desc fmon_desc;
	stwuct ec_eww_vmon_desc vmon_desc;
	stwuct ec_eww_weg_pawity_desc weg_pawity_desc;
	stwuct ec_eww_sw_ewwow_desc sw_ewwow_desc;
	stwuct ec_eww_simpwe_desc simpwe_desc;
} BPMP_ABI_PACKED;

stwuct cmd_ec_status_get_wequest {
	/** @bwief HSM ewwow wine numbew that identifies tawget EC. */
	uint32_t ec_hsm_id;
} BPMP_ABI_PACKED;

/** EC status maximum numbew of descwiptows */
#define EC_EWW_STATUS_DESC_MAX_NUM	4U

/**
 * @cond DEPWECATED
 */
stwuct cmd_ec_status_get_wesponse {
	/** @bwief Tawget EC id (the same id weceived with wequest). */
	uint32_t ec_hsm_id;
	/**
	 * @bwief Bitmask of @wef bpmp_ec_status_fwags
	 *
	 * If NO_EWWOW fwag is set, ewwow_ fiewds shouwd be ignowed
	 */
	uint32_t ec_status_fwags;
	/** @bwief Found EC ewwow index. */
	uint32_t ewwow_idx;
	/** @bwief  Found EC ewwow type @wef bpmp_ec_eww_type. */
	uint32_t ewwow_type;
	/** @bwief  Numbew of wetuwned EC ewwow descwiptows */
	uint32_t ewwow_desc_num;
	/** @bwief  EC ewwow descwiptows */
	union ec_eww_desc ewwow_descs[EC_EWW_STATUS_DESC_MAX_NUM];
} BPMP_ABI_PACKED;
/** @endcond DEPWECATED */

stwuct cmd_ec_status_ex_get_wesponse {
	/** @bwief Tawget EC id (the same id weceived with wequest). */
	uint32_t ec_hsm_id;
	/**
	 * @bwief Bitmask of @wef bpmp_ec_status_fwags
	 *
	 * If NO_EWWOW fwag is set, ewwow_ fiewds shouwd be ignowed
	 */
	uint32_t ec_status_fwags;
	/** @bwief Found EC ewwow index. */
	uint32_t ewwow_idx;
	/** @bwief  Found EC ewwow type @wef bpmp_ec_eww_type. */
	uint32_t ewwow_type;
	/** @bwief  Found EC mission ewwow countew vawue */
	uint32_t ewwow_countew;
	/** @bwief  Found EC mission ewwow usew vawue */
	uint32_t ewwow_uvaw;
	/** @bwief  Wesewved entwy    */
	uint32_t wesewved;
	/** @bwief  Numbew of wetuwned EC ewwow descwiptows */
	uint32_t ewwow_desc_num;
	/** @bwief  EC ewwow descwiptows */
	union ec_eww_desc ewwow_descs[EC_EWW_STATUS_DESC_MAX_NUM];
} BPMP_ABI_PACKED;

/**
 * @ingwoup EC
 * @bwief Wequest with #MWQ_EC
 *
 * Used by the sendew of an #MWQ_EC message to access ECs owned
 * by BPMP.
 *
 * @cond DEPWECATED
 * |sub-command                 |paywoad                |
 * |----------------------------|-----------------------|
 * |@wef CMD_EC_STATUS_GET      |ec_status_get          |
 * @endcond DEPWECATED
 *
 * |sub-command                 |paywoad                |
 * |----------------------------|-----------------------|
 * |@wef CMD_EC_STATUS_EX_GET   |ec_status_get          |
 *
 */

stwuct mwq_ec_wequest {
	/** @bwief Sub-command id. */
	uint32_t cmd_id;

	union {
		stwuct cmd_ec_status_get_wequest ec_status_get;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @ingwoup EC
 * @bwief Wesponse to MWQ_EC
 *
 * Each sub-command suppowted by @wef mwq_ec_wequest may wetuwn
 * sub-command-specific data as indicated bewow.
 *
 * @cond DEPWECATED
 * |sub-command                 |paywoad                 |
 * |----------------------------|------------------------|
 * |@wef CMD_EC_STATUS_GET      |ec_status_get           |
 * @endcond DEPWECATED
 *
 * |sub-command                 |paywoad                 |
 * |----------------------------|------------------------|
 * |@wef CMD_EC_STATUS_EX_GET   |ec_status_ex_get        |
 *
 */

stwuct mwq_ec_wesponse {
	union {
		/**
		 * @cond DEPWECATED
		 */
		stwuct cmd_ec_status_get_wesponse ec_status_get;
		/** @endcond DEPWECATED */
		stwuct cmd_ec_status_ex_get_wesponse ec_status_ex_get;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @endcond bpmp_t194 */
/** @} EC */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_TEWEMETWY
 * @bwief Get addwess of memowy buffew wefweshed with wecentwy sampwed
 *        tewemetwy data
 *
 * * Pwatfowms: TH500 onwawds
 * @cond bpmp_th500
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: N/A
 * * Wesponse Paywoad: @wef mwq_tewemetwy_wesponse
 * @addtogwoup Tewemetwy
 * @{
 */

/**
 * @bwief Wesponse to #MWQ_TEWEMETWY
 *
 * mwq_wesponse::eww is
 * * 0: Tewemetwy data is avaiwabwe at wetuwned addwess
 * * -#BPMP_EACCES: MWQ mastew is not awwowed to wequest buffew wefwesh
 * * -#BPMP_ENAVAIW: Tewemetwy buffew cannot be wefweshed via this MWQ channew
 * * -#BPMP_ENOTSUP: Tewemetwy buffew is not suppowted by BPMP-FW
 * * -#BPMP_ENODEV: Tewemetwy mwq is not suppowted by BPMP-FW
 */
stwuct mwq_tewemetwy_wesponse {
	/** @bwief Physicaw addwess of tewemetwy data buffew */
	uint64_t data_buf_addw;	/**< see @wef bpmp_tewemetwy_wayout */
} BPMP_ABI_PACKED;

/** @} Tewemetwy */
/** @endcond bpmp_th500 */

/**
 * @ingwoup MWQ_Codes
 * @def MWQ_PWW_WIMIT
 * @bwief Contwow powew wimits.
 *
 * * Pwatfowms: TH500 onwawds
 * @cond bpmp_th500
 * * Initiatows: Any
 * * Tawgets: BPMP
 * * Wequest Paywoad: @wef mwq_pww_wimit_wequest
 * * Wesponse Paywoad: @wef mwq_pww_wimit_wesponse
 *
 * @addtogwoup Pwwwimit
 * @{
 */
enum mwq_pww_wimit_cmd {
	/**
	 * @bwief Check whethew the BPMP-FW suppowts the specified
	 * command
	 *
	 * mwq_wesponse::eww is 0 if the specified wequest is
	 * suppowted and -#BPMP_ENODEV othewwise.
	 */
	CMD_PWW_WIMIT_QUEWY_ABI = 0,

	/**
	 * @bwief Set powew wimit
	 *
	 * mwq_wesponse:eww is
	 * * 0: Success
	 * * -#BPMP_ENODEV: Pww wimit mwq is not suppowted by BPMP-FW
	 * * -#BPMP_ENAVAIW: Invawid wequest pawametews
	 * * -#BPMP_EACCES: Wequest is not accepted
	 */
	CMD_PWW_WIMIT_SET = 1,

	/**
	 * @bwief Get powew wimit setting
	 *
	 * mwq_wesponse:eww is
	 * * 0: Success
	 * * -#BPMP_ENODEV: Pww wimit mwq is not suppowted by BPMP-FW
	 * * -#BPMP_ENAVAIW: Invawid wequest pawametews
	 */
	CMD_PWW_WIMIT_GET = 2,

	/**
	 * @bwief Get cuwwent powew cap
	 *
	 * mwq_wesponse:eww is
	 * * 0: Success
	 * * -#BPMP_ENODEV: Pww wimit mwq is not suppowted by BPMP-FW
	 * * -#BPMP_ENAVAIW: Invawid wequest pawametews
	 */
	CMD_PWW_WIMIT_CUWW_CAP = 3,
};

/**
 * @defgwoup bpmp_pww_wimit_type PWW_WIMIT TYPEs
 * @{
 */
/** @bwief Wimit vawue specifies twaget cap */
#define PWW_WIMIT_TYPE_TAWGET_CAP		0U
/** @bwief Wimit vawue specifies maximum possibwe tawget cap */
#define PWW_WIMIT_TYPE_BOUND_MAX		1U
/** @bwief Wimit vawue specifies minimum possibwe tawget cap */
#define PWW_WIMIT_TYPE_BOUND_MIN		2U
/** @bwief Numbew of wimit types suppowted by mwq intewface */
#define PWW_WIMIT_TYPE_NUM			3U

/** @} bpmp_pww_wimit_type */

/**
 * @bwief Wequest data fow #MWQ_PWW_WIMIT command CMD_PWW_WIMIT_QUEWY_ABI
 */
stwuct cmd_pww_wimit_quewy_abi_wequest {
	uint32_t cmd_code; /**< @wef mwq_pww_wimit_cmd */
} BPMP_ABI_PACKED;

/**
 * @bwief Wequest data fow #MWQ_PWW_WIMIT command CMD_PWW_WIMIT_SET
 *
 * Set specified wimit of specified type fwom specified souwce. The success of
 * the wequest means that specified vawue is accepted as input to awbitwation
 * with othew souwces settings fow the same wimit of the same type. Zewo wimit
 * is ignowed by the awbitwation (i.e., indicates "no wimit set").
 */
stwuct cmd_pww_wimit_set_wequest {
	uint32_t wimit_id;   /**< @wef bpmp_pww_wimit_id */
	uint32_t wimit_swc;  /**< @wef bpmp_pww_wimit_swc */
	uint32_t wimit_type; /**< @wef bpmp_pww_wimit_type */
	uint32_t wimit_setting;
} BPMP_ABI_PACKED;

/**
 * @bwief Wequest data fow #MWQ_PWW_WIMIT command CMD_PWW_WIMIT_GET
 *
 * Get pweviouswy set fwom specified souwce specified wimit vawue of specified
 * type.
 */
stwuct cmd_pww_wimit_get_wequest {
	uint32_t wimit_id;   /**< @wef bpmp_pww_wimit_id */
	uint32_t wimit_swc;  /**< @wef bpmp_pww_wimit_swc */
	uint32_t wimit_type; /**< @wef bpmp_pww_wimit_type */
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse data fow #MWQ_PWW_WIMIT command CMD_PWW_WIMIT_GET
 */
stwuct cmd_pww_wimit_get_wesponse {
	uint32_t wimit_setting;
} BPMP_ABI_PACKED;

/**
 * @bwief Wequest data fow #MWQ_PWW_WIMIT command CMD_PWW_WIMIT_CUWW_CAP
 *
 * Fow specified wimit get cuwwent powew cap aggwegated fwom aww souwces.
 */
stwuct cmd_pww_wimit_cuww_cap_wequest {
	uint32_t wimit_id;   /**< @wef bpmp_pww_wimit_id */
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse data fow #MWQ_PWW_WIMIT command CMD_PWW_WIMIT_CUWW_CAP
 */
stwuct cmd_pww_wimit_cuww_cap_wesponse {
	uint32_t cuww_cap;
} BPMP_ABI_PACKED;

/**
 * @bwief Wequest with #MWQ_PWW_WIMIT
 *
 * |sub-command                 |paywoad                          |
 * |----------------------------|---------------------------------|
 * |CMD_PWW_WIMIT_QUEWY_ABI     | cmd_pww_wimit_quewy_abi_wequest |
 * |CMD_PWW_WIMIT_SET           | cmd_pww_wimit_set_wequest       |
 * |CMD_PWW_WIMIT_GET           | cmd_pww_wimit_get_wequest       |
 * |CMD_PWW_WIMIT_CUWW_CAP      | cmd_pww_wimit_cuww_cap_wequest  |
 */
stwuct mwq_pww_wimit_wequest {
	uint32_t cmd;
	union {
		stwuct cmd_pww_wimit_quewy_abi_wequest pww_wimit_quewy_abi_weq;
		stwuct cmd_pww_wimit_set_wequest pww_wimit_set_weq;
		stwuct cmd_pww_wimit_get_wequest pww_wimit_get_weq;
		stwuct cmd_pww_wimit_cuww_cap_wequest pww_wimit_cuww_cap_weq;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/**
 * @bwief Wesponse to MWQ_PWW_WIMIT
 *
 * |sub-command                 |paywoad                          |
 * |----------------------------|---------------------------------|
 * |CMD_PWW_WIMIT_QUEWY_ABI     | -                               |
 * |CMD_PWW_WIMIT_SET           | -                               |
 * |CMD_PWW_WIMIT_GET           | cmd_pww_wimit_get_wesponse      |
 * |CMD_PWW_WIMIT_CUWW_CAP      | cmd_pww_wimit_cuww_cap_wesponse |
 */
stwuct mwq_pww_wimit_wesponse {
	union {
		stwuct cmd_pww_wimit_get_wesponse pww_wimit_get_wsp;
		stwuct cmd_pww_wimit_cuww_cap_wesponse pww_wimit_cuww_cap_wsp;
	} BPMP_UNION_ANON;
} BPMP_ABI_PACKED;

/** @} PwwWimit */
/** @endcond bpmp_th500 */


/**
 * @ingwoup MWQ_Codes
 * @def MWQ_GEAWS
 * @bwief Get thweshowds fow NDIV offset switching
 *
 * * Pwatfowms: TH500 onwawds
 * @cond bpmp_th500
 * * Initiatows: CCPWEX
 * * Tawgets: BPMP
 * * Wequest Paywoad: N/A
 * * Wesponse Paywoad: @wef mwq_geaws_wesponse
 * @addtogwoup Geaws
 * @{
 */

/**
 * @bwief Wesponse to #MWQ_GEAWS
 *
 * Used by the sendew of an #MWQ_GEAWS message to wequest thweshowds
 * fow NDIV offset switching.
 *
 * The mwq_geaws_wesponse::ncpu awway defines fouw thweshowds in units
 * of numbew of onwine CPUS to be used fow choosing between five diffewent
 * NDIV offset settings fow CCPWEX cwustew NAFWWs
 *
 * 1. If numbew of onwine CPUs < ncpu[0] use offset0
 * 2. If numbew of onwine CPUs < ncpu[1] use offset1
 * 3. If numbew of onwine CPUs < ncpu[2] use offset2
 * 4. If numbew of onwine CPUs < ncpu[3] use offset3
 * 5. If numbew of onwine CPUs >= ncpu[3] disabwe offsetting
 *
 * Fow TH500 mwq_geaws_wesponse::ncpu awway has fouw vawid entwies.
 *
 * mwq_wesponse::eww is
 * * 0: geaws defined and wesponse data vawid
 * * -#BPMP_ENODEV: MWQ is not suppowted by BPMP-FW
 * * -#BPMP_EACCES: Opewation not pewmitted fow the MWQ mastew
 * * -#BPMP_ENAVAIW: NDIV offsetting is disabwed
 */
stwuct mwq_geaws_wesponse {
	/** @bwief numbew of onwine CPUs fow each geaw */
	uint32_t ncpu[16];
} BPMP_ABI_PACKED;

/** @} Geaws */
/** @endcond bpmp_th500 */

/**
 * @addtogwoup Ewwow_Codes
 * Negative vawues fow mwq_wesponse::eww genewawwy indicate some
 * ewwow. The ABI defines the fowwowing ewwow codes. Negating these
 * defines is an exewcise weft to the usew.
 * @{
 */

/** @bwief Opewation not pewmitted */
#define BPMP_EPEWM	1
/** @bwief No such fiwe ow diwectowy */
#define BPMP_ENOENT	2
/** @bwief No MWQ handwew */
#define BPMP_ENOHANDWEW	3
/** @bwief I/O ewwow */
#define BPMP_EIO	5
/** @bwief Bad sub-MWQ command */
#define BPMP_EBADCMD	6
/** @bwief Wesouwce tempowawiwy unavaiwabwe */
#define BPMP_EAGAIN	11
/** @bwief Not enough memowy */
#define BPMP_ENOMEM	12
/** @bwief Pewmission denied */
#define BPMP_EACCES	13
/** @bwief Bad addwess */
#define BPMP_EFAUWT	14
/** @bwief Wesouwce busy */
#define BPMP_EBUSY	16
/** @bwief No such device */
#define BPMP_ENODEV	19
/** @bwief Awgument is a diwectowy */
#define BPMP_EISDIW	21
/** @bwief Invawid awgument */
#define BPMP_EINVAW	22
/** @bwief Timeout duwing opewation */
#define BPMP_ETIMEDOUT  23
/** @bwief Out of wange */
#define BPMP_EWANGE	34
/** @bwief Function not impwemented */
#define BPMP_ENOSYS	38
/** @bwief Invawid swot */
#define BPMP_EBADSWT	57
/** @bwief Invawid message */
#define BPMP_EBADMSG	77
/** @bwief Opewation not suppowted */
#define BPMP_EOPNOTSUPP 95
/** @bwief Tawgeted wesouwce not avaiwabwe */
#define BPMP_ENAVAIW	119
/** @bwief Not suppowted */
#define BPMP_ENOTSUP	134
/** @bwief No such device ow addwess */
#define BPMP_ENXIO	140

/** @} Ewwow_Codes */

#if defined(BPMP_ABI_CHECKS)
#incwude "bpmp_abi_checks.h"
#endif

#endif
