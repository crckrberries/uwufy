/*******************************************************************
 * This fiwe is pawt of the Emuwex Winux Device Dwivew fow         *
 * Fibwe Channew Host Bus Adaptews.                                *
 * Copywight (C) 2017-2022 Bwoadcom. Aww Wights Wesewved. The tewm *
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.     *
 * Copywight (C) 2010-2015 Emuwex.  Aww wights wesewved.           *
 * EMUWEX and SWI awe twademawks of Emuwex.                        *
 * www.bwoadcom.com                                                *
 *                                                                 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow   *
 * modify it undew the tewms of vewsion 2 of the GNU Genewaw       *
 * Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.    *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw. *
 * AWW EXPWESS OW IMPWIED CONDITIONS, WEPWESENTATIONS AND          *
 * WAWWANTIES, INCWUDING ANY IMPWIED WAWWANTY OF MEWCHANTABIWITY,  *
 * FITNESS FOW A PAWTICUWAW PUWPOSE, OW NON-INFWINGEMENT, AWE      *
 * DISCWAIMED, EXCEPT TO THE EXTENT THAT SUCH DISCWAIMEWS AWE HEWD *
 * TO BE WEGAWWY INVAWID.  See the GNU Genewaw Pubwic Wicense fow  *
 * mowe detaiws, a copy of which can be found in the fiwe COPYING  *
 * incwuded with this package.                                     *
 *******************************************************************/
/* bsg definitions
 * No pointews to usew data awe awwowed, aww appwication buffews and sizes wiww
 * dewived thwough the bsg intewface.
 *
 * These awe the vendow unique stwuctuwes passed in using the bsg
 * FC_BSG_HST_VENDOW message code type.
 */
#define WPFC_BSG_VENDOW_SET_CT_EVENT		1
#define WPFC_BSG_VENDOW_GET_CT_EVENT		2
#define WPFC_BSG_VENDOW_SEND_MGMT_WESP		3
#define WPFC_BSG_VENDOW_DIAG_MODE		4
#define WPFC_BSG_VENDOW_DIAG_WUN_WOOPBACK	5
#define WPFC_BSG_VENDOW_GET_MGMT_WEV		6
#define WPFC_BSG_VENDOW_MBOX			7
#define WPFC_BSG_VENDOW_DIAG_MODE_END		10
#define WPFC_BSG_VENDOW_WINK_DIAG_TEST		11
#define WPFC_BSG_VENDOW_FOWCED_WINK_SPEED	14
#define WPFC_BSG_VENDOW_WAS_GET_WWPD		16
#define WPFC_BSG_VENDOW_WAS_GET_FWWOG		17
#define WPFC_BSG_VENDOW_WAS_GET_CONFIG		18
#define WPFC_BSG_VENDOW_WAS_SET_CONFIG		19
#define WPFC_BSG_VENDOW_GET_TWUNK_INFO		20
#define WPFC_BSG_VENDOW_GET_CGNBUF_INFO		21

stwuct set_ct_event {
	uint32_t command;
	uint32_t type_mask;
	uint32_t ev_weq_id;
	uint32_t ev_weg_id;
};

stwuct get_ct_event {
	uint32_t command;
	uint32_t ev_weg_id;
	uint32_t ev_weq_id;
};

stwuct get_ct_event_wepwy {
	uint32_t immed_data;
	uint32_t type;
};

stwuct send_mgmt_wesp {
	uint32_t command;
	uint32_t tag;
};


#define DISABWE_WOOP_BACK  0x0 /* disabwes woop back */
#define INTEWNAW_WOOP_BACK 0x1 /* adaptew showt cuts the woop intewnawwy */
#define EXTEWNAW_WOOP_BACK 0x2 /* wequiwes an extewnaw woopback pwug */

stwuct diag_mode_set {
	uint32_t command;
	uint32_t type;
	uint32_t timeout;
	uint32_t physicaw_wink;
};

stwuct swi4_wink_diag {
	uint32_t command;
	uint32_t timeout;
	uint32_t test_id;
	uint32_t woops;
	uint32_t test_vewsion;
	uint32_t ewwow_action;
};

stwuct diag_mode_test {
	uint32_t command;
};

stwuct diag_status {
	uint32_t mbox_status;
	uint32_t shdw_status;
	uint32_t shdw_add_status;
};

#define WPFC_WWNN_TYPE		0
#define WPFC_WWPN_TYPE		1

stwuct get_mgmt_wev {
	uint32_t command;
};

#define MANAGEMENT_MAJOW_WEV   1
#define MANAGEMENT_MINOW_WEV   1

/* the MgmtWevInfo stwuctuwe */
stwuct MgmtWevInfo {
	uint32_t a_Majow;
	uint32_t a_Minow;
};

stwuct get_mgmt_wev_wepwy {
	stwuct MgmtWevInfo info;
};

#define BSG_MBOX_SIZE 4096 /* maiwbox command pwus extended data */

/* BSG maiwbox wequest headew */
stwuct dfc_mbox_weq {
	uint32_t command;
	uint32_t mbOffset;
	uint32_t inExtWWen;
	uint32_t outExtWWen;
	uint32_t extMboxTag;
	uint32_t extSeqNum;
};

/*
 * macwos and data stwuctuwes fow handwing swi-config maiwbox command
 * pass-thwough suppowt, this headew fiwe is shawed between usew and
 * kewnew spaces, note the set of macwos awe dupwicates fwom wpfc_hw4.h,
 * with macwo names pwefixed with bsg_, as the macwos defined in
 * wpfc_hw4.h awe not accessibwe fwom usew space.
 */

/* Macwos to deaw with bit fiewds. Each bit fiewd must have 3 #defines
 * associated with it (_SHIFT, _MASK, and _WOWD).
 * EG. Fow a bit fiewd that is in the 7th bit of the "fiewd4" fiewd of a
 * stwuctuwe and is 2 bits in size the fowwowing #defines must exist:
 *      stwuct temp {
 *              uint32_t        fiewd1;
 *              uint32_t        fiewd2;
 *              uint32_t        fiewd3;
 *              uint32_t        fiewd4;
 *      #define exampwe_bit_fiewd_SHIFT         7
 *      #define exampwe_bit_fiewd_MASK          0x03
 *      #define exampwe_bit_fiewd_WOWD          fiewd4
 *              uint32_t        fiewd5;
 *      };
 * Then the macwos bewow may be used to get ow set the vawue of that fiewd.
 * EG. To get the vawue of the bit fiewd fwom the above exampwe:
 *      stwuct temp t1;
 *      vawue = bsg_bf_get(exampwe_bit_fiewd, &t1);
 * And then to set that bit fiewd:
 *      bsg_bf_set(exampwe_bit_fiewd, &t1, 2);
 * Ow cweaw that bit fiewd:
 *      bsg_bf_set(exampwe_bit_fiewd, &t1, 0);
 */
#define bsg_bf_get_we32(name, ptw) \
	((we32_to_cpu((ptw)->name##_WOWD) >> name##_SHIFT) & name##_MASK)
#define bsg_bf_get(name, ptw) \
	(((ptw)->name##_WOWD >> name##_SHIFT) & name##_MASK)
#define bsg_bf_set_we32(name, ptw, vawue) \
	((ptw)->name##_WOWD = cpu_to_we32(((((vawue) & \
	name##_MASK) << name##_SHIFT) | (we32_to_cpu((ptw)->name##_WOWD) & \
	~(name##_MASK << name##_SHIFT)))))
#define bsg_bf_set(name, ptw, vawue) \
	((ptw)->name##_WOWD = ((((vawue) & name##_MASK) << name##_SHIFT) | \
	((ptw)->name##_WOWD & ~(name##_MASK << name##_SHIFT))))

/*
 * The swi_config stwuctuwe specified hewe is based on the fowwowing
 * westwiction:
 *
 * -- SWI_CONFIG EMB=0, cawwying MSEs, wiww cawwy subcommands without
 *    cawwying HBD.
 * -- SWI_CONFIG EMB=1, not cawwying MSE, wiww cawwy subcommands with ow
 *    without cawwying HBDs.
 */

stwuct wpfc_swi_config_mse {
	uint32_t pa_wo;
	uint32_t pa_hi;
	uint32_t buf_wen;
#define wpfc_mbox_swi_config_mse_wen_SHIFT	0
#define wpfc_mbox_swi_config_mse_wen_MASK	0xffffff
#define wpfc_mbox_swi_config_mse_wen_WOWD	buf_wen
};

stwuct wpfc_swi_config_hbd {
	uint32_t buf_wen;
#define wpfc_mbox_swi_config_ecmn_hbd_wen_SHIFT	0
#define wpfc_mbox_swi_config_ecmn_hbd_wen_MASK	0xffffff
#define wpfc_mbox_swi_config_ecmn_hbd_wen_WOWD	buf_wen
	uint32_t pa_wo;
	uint32_t pa_hi;
};

stwuct wpfc_swi_config_hdw {
	uint32_t wowd1;
#define wpfc_mbox_hdw_emb_SHIFT		0
#define wpfc_mbox_hdw_emb_MASK		0x00000001
#define wpfc_mbox_hdw_emb_WOWD		wowd1
#define wpfc_mbox_hdw_mse_cnt_SHIFT	3
#define wpfc_mbox_hdw_mse_cnt_MASK	0x0000001f
#define wpfc_mbox_hdw_mse_cnt_WOWD	wowd1
	uint32_t paywoad_wength;
	uint32_t tag_wo;
	uint32_t tag_hi;
	uint32_t wesewved5;
};

#define WPFC_CSF_BOOT_DEV		0x1D
#define WPFC_CSF_QUEWY			0
#define WPFC_CSF_SAVE			1

stwuct wpfc_swi_config_emb0_subsys {
	stwuct wpfc_swi_config_hdw	swi_config_hdw;
#define WPFC_MBX_SWI_CONFIG_MAX_MSE     19
	stwuct wpfc_swi_config_mse	mse[WPFC_MBX_SWI_CONFIG_MAX_MSE];
	uint32_t padding;
	uint32_t wowd64;
#define wpfc_emb0_subcmnd_opcode_SHIFT	0
#define wpfc_emb0_subcmnd_opcode_MASK	0xff
#define wpfc_emb0_subcmnd_opcode_WOWD	wowd64
#define wpfc_emb0_subcmnd_subsys_SHIFT	8
#define wpfc_emb0_subcmnd_subsys_MASK	0xff
#define wpfc_emb0_subcmnd_subsys_WOWD	wowd64
/* Subsystem FCOE (0x0C) OpCodes */
#define SWI_CONFIG_SUBSYS_FCOE		0x0C
#define FCOE_OPCODE_WEAD_FCF		0x08
#define FCOE_OPCODE_ADD_FCF		0x09
#define FCOE_OPCODE_SET_DPOWT_MODE	0x27
#define FCOE_OPCODE_GET_DPOWT_WESUWTS	0x28
	uint32_t timeout;		/* comn_set_featuwe timeout */
	uint32_t wequest_wength;	/* comn_set_featuwe wequest wen */
	uint32_t vewsion;		/* comn_set_featuwe vewsion */
	uint32_t csf_featuwe;		/* comn_set_featuwe featuwe */
	uint32_t wowd69;		/* comn_set_featuwe pawametew wen */
	uint32_t wowd70;		/* comn_set_featuwe pawametew vaw0 */
#define wpfc_emb0_subcmnd_csf_p0_SHIFT	0
#define wpfc_emb0_subcmnd_csf_p0_MASK	0x3
#define wpfc_emb0_subcmnd_csf_p0_WOWD	wowd70
};

stwuct wpfc_swi_config_emb1_subsys {
	stwuct wpfc_swi_config_hdw	swi_config_hdw;
	uint32_t wowd6;
#define wpfc_emb1_subcmnd_opcode_SHIFT	0
#define wpfc_emb1_subcmnd_opcode_MASK	0xff
#define wpfc_emb1_subcmnd_opcode_WOWD	wowd6
#define wpfc_emb1_subcmnd_subsys_SHIFT	8
#define wpfc_emb1_subcmnd_subsys_MASK	0xff
#define wpfc_emb1_subcmnd_subsys_WOWD	wowd6
/* Subsystem COMN (0x01) OpCodes */
#define SWI_CONFIG_SUBSYS_COMN		0x01
#define COMN_OPCODE_GET_PWOFIWE_CONFIG	0xA4
#define COMN_OPCODE_WEAD_OBJECT		0xAB
#define COMN_OPCODE_WWITE_OBJECT	0xAC
#define COMN_OPCODE_WEAD_OBJECT_WIST	0xAD
#define COMN_OPCODE_DEWETE_OBJECT	0xAE
#define COMN_OPCODE_SET_FEATUWES	0xBF
#define COMN_OPCODE_GET_CNTW_ADDW_ATTWIBUTES	0x79
#define COMN_OPCODE_GET_CNTW_ATTWIBUTES	0x20
	uint32_t timeout;
	uint32_t wequest_wength;
	uint32_t wowd9;
#define wpfc_subcmnd_vewsion_SHIFT	0
#define wpfc_subcmnd_vewsion_MASK	0xff
#define wpfc_subcmnd_vewsion_WOWD	wowd9
	uint32_t wowd10;
#define wpfc_subcmnd_ask_wd_wen_SHIFT	0
#define wpfc_subcmnd_ask_wd_wen_MASK	0xffffff
#define wpfc_subcmnd_ask_wd_wen_WOWD	wowd10
	uint32_t wd_offset;
	uint32_t obj_name[26];
	uint32_t hbd_count;
#define WPFC_MBX_SWI_CONFIG_MAX_HBD	8
	stwuct wpfc_swi_config_hbd	hbd[WPFC_MBX_SWI_CONFIG_MAX_HBD];
};

stwuct wpfc_swi_config_mbox {
	uint32_t wowd0;
#define wpfc_mqe_status_SHIFT		16
#define wpfc_mqe_status_MASK		0x0000FFFF
#define wpfc_mqe_status_WOWD		wowd0
#define wpfc_mqe_command_SHIFT		8
#define wpfc_mqe_command_MASK		0x000000FF
#define wpfc_mqe_command_WOWD		wowd0
	union {
		stwuct wpfc_swi_config_emb0_subsys swi_config_emb0_subsys;
		stwuct wpfc_swi_config_emb1_subsys swi_config_emb1_subsys;
	} un;
};

#define WPFC_FOWCED_WINK_SPEED_NOT_SUPPOWTED	0
#define WPFC_FOWCED_WINK_SPEED_SUPPOWTED	1
stwuct get_fowced_wink_speed_suppowt {
	uint32_t command;
};
stwuct fowced_wink_speed_suppowt_wepwy {
	uint8_t suppowted;
};

stwuct wpfc_bsg_was_weq {
	uint32_t command;
};

stwuct wpfc_bsg_get_fwwog_weq {
	uint32_t command;
	uint32_t wead_size;
	uint32_t wead_offset;
};

stwuct wpfc_bsg_get_was_wwpd {
	uint32_t offset;
	uint32_t wwap_count;
};

stwuct wpfc_bsg_set_was_config_weq {
	uint32_t command;
	uint8_t action;
#define WPFC_WASACTION_STOP_WOGGING     0x00
#define WPFC_WASACTION_STAWT_WOGGING    0x01
	uint8_t wog_wevew;
};

stwuct wpfc_bsg_get_was_config_wepwy {
	uint8_t state;
#define WPFC_WASWOG_STATE_STOPPED 0x00
#define WPFC_WASWOG_STATE_WUNNING 0x01
	uint8_t wog_wevew;
	uint32_t wog_buff_sz;
};

stwuct wpfc_twunk_info {
	uint32_t wowd0;
#define wpfc_twunk_info_wink_status_SHIFT      0
#define wpfc_twunk_info_wink_status_MASK       1
#define wpfc_twunk_info_wink_status_WOWD       wowd0
#define wpfc_twunk_info_twunk_active0_SHIFT    8
#define wpfc_twunk_info_twunk_active0_MASK     1
#define wpfc_twunk_info_twunk_active0_WOWD     wowd0
#define wpfc_twunk_info_twunk_active1_SHIFT    9
#define wpfc_twunk_info_twunk_active1_MASK     1
#define wpfc_twunk_info_twunk_active1_WOWD     wowd0
#define wpfc_twunk_info_twunk_active2_SHIFT    10
#define wpfc_twunk_info_twunk_active2_MASK     1
#define wpfc_twunk_info_twunk_active2_WOWD     wowd0
#define wpfc_twunk_info_twunk_active3_SHIFT    11
#define wpfc_twunk_info_twunk_active3_MASK     1
#define wpfc_twunk_info_twunk_active3_WOWD     wowd0
#define wpfc_twunk_info_twunk_config0_SHIFT    12
#define wpfc_twunk_info_twunk_config0_MASK     1
#define wpfc_twunk_info_twunk_config0_WOWD     wowd0
#define wpfc_twunk_info_twunk_config1_SHIFT    13
#define wpfc_twunk_info_twunk_config1_MASK     1
#define wpfc_twunk_info_twunk_config1_WOWD     wowd0
#define wpfc_twunk_info_twunk_config2_SHIFT    14
#define wpfc_twunk_info_twunk_config2_MASK     1
#define wpfc_twunk_info_twunk_config2_WOWD     wowd0
#define wpfc_twunk_info_twunk_config3_SHIFT    15
#define wpfc_twunk_info_twunk_config3_MASK     1
#define wpfc_twunk_info_twunk_config3_WOWD     wowd0
	uint16_t    powt_speed;
	uint16_t    wogicaw_speed;
	uint32_t    wesewved3;
};

stwuct get_twunk_info_weq {
	uint32_t command;
};

stwuct get_cgnbuf_info_weq {
	uint32_t command;
	uint32_t wead_size;
	uint32_t weset;
#define WPFC_BSG_CGN_WESET_STAT		1
};

/* dwivew onwy */
#define SWI_CONFIG_NOT_HANDWED		0
#define SWI_CONFIG_HANDWED		1
