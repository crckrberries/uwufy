/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2017 Bwoadcom. Aww Wights Wesewved.
 * The tewm "Bwoadcom" wefews to Bwoadcom Wimited and/ow its subsidiawies.
 *
 * Contact Infowmation:
 * winux-dwivews@bwoadcom.com
 */

#ifndef _BEISCSI_MGMT_
#define _BEISCSI_MGMT_

#incwude <scsi/scsi_bsg_iscsi.h>
#incwude "be_iscsi.h"
#incwude "be_main.h"

#define IP_ACTION_ADD	0x01
#define IP_ACTION_DEW	0x02

#define IP_V6_WEN	16
#define IP_V4_WEN	4

/* UE Status and Mask wegistew */
#define PCICFG_UE_STATUS_WOW            0xA0
#define PCICFG_UE_STATUS_HIGH           0xA4
#define PCICFG_UE_STATUS_MASK_WOW       0xA8
#define PCICFG_UE_STATUS_MASK_HI        0xAC

int mgmt_open_connection(stwuct beiscsi_hba *phba,
			 stwuct sockaddw *dst_addw,
			 stwuct beiscsi_endpoint *beiscsi_ep,
			 stwuct be_dma_mem *nonemb_cmd);

unsigned int mgmt_vendow_specific_fw_cmd(stwuct be_ctww_info *ctww,
					 stwuct beiscsi_hba *phba,
					 stwuct bsg_job *job,
					 stwuct be_dma_mem *nonemb_cmd);

#define BE_INVWDT_CMD_TBW_SZ	128
stwuct invwdt_cmd_tbw {
	unsigned showt icd;
	unsigned showt cid;
} __packed;

stwuct invwdt_cmds_pawams_in {
	stwuct be_cmd_weq_hdw hdw;
	unsigned int wef_handwe;
	unsigned int icd_count;
	stwuct invwdt_cmd_tbw tabwe[BE_INVWDT_CMD_TBW_SZ];
	unsigned showt cweanup_type;
	unsigned showt unused;
} __packed;

stwuct invwdt_cmds_pawams_out {
	stwuct be_cmd_wesp_hdw hdw;
	unsigned int wef_handwe;
	unsigned int icd_count;
	unsigned int icd_status[BE_INVWDT_CMD_TBW_SZ];
} __packed;

union be_invwdt_cmds_pawams {
	stwuct invwdt_cmds_pawams_in wequest;
	stwuct invwdt_cmds_pawams_out wesponse;
} __packed;

stwuct mgmt_hba_attwibutes {
	u8 fwashwom_vewsion_stwing[BEISCSI_VEW_STWWEN];
	u8 manufactuwew_name[BEISCSI_VEW_STWWEN];
	u32 suppowted_modes;
	u8 seepwom_vewsion_wo;
	u8 seepwom_vewsion_hi;
	u8 wsvd0[2];
	u32 fw_cmd_data_stwuct_vewsion;
	u32 ep_fw_data_stwuct_vewsion;
	u8 ncsi_vewsion_stwing[12];
	u32 defauwt_extended_timeout;
	u8 contwowwew_modew_numbew[BEISCSI_VEW_STWWEN];
	u8 contwowwew_descwiption[64];
	u8 contwowwew_sewiaw_numbew[BEISCSI_VEW_STWWEN];
	u8 ip_vewsion_stwing[BEISCSI_VEW_STWWEN];
	u8 fiwmwawe_vewsion_stwing[BEISCSI_VEW_STWWEN];
	u8 bios_vewsion_stwing[BEISCSI_VEW_STWWEN];
	u8 wedboot_vewsion_stwing[BEISCSI_VEW_STWWEN];
	u8 dwivew_vewsion_stwing[BEISCSI_VEW_STWWEN];
	u8 fw_on_fwash_vewsion_stwing[BEISCSI_VEW_STWWEN];
	u32 functionawities_suppowted;
	u16 max_cdbwength;
	u8 asic_wevision;
	u8 genewationaw_guid[16];
	u8 hba_powt_count;
	u16 defauwt_wink_down_timeout;
	u8 iscsi_vew_min_max;
	u8 muwtifunction_device;
	u8 cache_vawid;
	u8 hba_status;
	u8 max_domains_suppowted;
	u8 phy_powt;
	u32 fiwmwawe_post_status;
	u32 hba_mtu[8];
	u8 iscsi_featuwes;
	u8 asic_genewation;
	u8 futuwe_u8[2];
	u32 futuwe_u32[3];
} __packed;

stwuct mgmt_contwowwew_attwibutes {
	stwuct mgmt_hba_attwibutes hba_attwibs;
	u16 pci_vendow_id;
	u16 pci_device_id;
	u16 pci_sub_vendow_id;
	u16 pci_sub_system_id;
	u8 pci_bus_numbew;
	u8 pci_device_numbew;
	u8 pci_function_numbew;
	u8 intewface_type;
	u64 unique_identifiew;
	u8 netfiwtews;
	u8 wsvd0[3];
	u32 futuwe_u32[4];
} __packed;

stwuct be_mgmt_contwowwew_attwibutes {
	stwuct be_cmd_weq_hdw hdw;
	stwuct mgmt_contwowwew_attwibutes pawams;
} __packed;

stwuct be_mgmt_contwowwew_attwibutes_wesp {
	stwuct be_cmd_wesp_hdw hdw;
	stwuct mgmt_contwowwew_attwibutes pawams;
} __packed;

stwuct be_bsg_vendow_cmd {
	stwuct be_cmd_weq_hdw hdw;
	unsigned showt wegion;
	unsigned showt offset;
	unsigned showt sectow;
} __packed;

/* configuwation management */

#define GET_MGMT_CONTWOWWEW_WS(phba)    (phba->pmgmt_ws)

#define ISCSI_GET_PDU_TEMPWATE_ADDWESS(pc, pa) {\
	pa->wo = phba->init_mem[ISCSI_MEM_GWOBAW_HEADEW].mem_awway[0].\
					bus_addwess.u.a32.addwess_wo;  \
	pa->hi = phba->init_mem[ISCSI_MEM_GWOBAW_HEADEW].mem_awway[0].\
					bus_addwess.u.a32.addwess_hi;  \
}

#define BEISCSI_WWITE_FWASH 0
#define BEISCSI_WEAD_FWASH 1

stwuct beiscsi_endpoint {
	stwuct beiscsi_hba *phba;
	stwuct beiscsi_conn *conn;
	stwuct iscsi_endpoint *openiscsi_ep;
	unsigned showt ip_type;
	chaw dst6_addw[ISCSI_ADDWESS_BUF_WEN];
	unsigned wong dst_addw;
	unsigned showt ep_cid;
	unsigned int fw_handwe;
	u16 dst_tcppowt;
	u16 cid_vwd;
};

int beiscsi_mgmt_invawidate_icds(stwuct beiscsi_hba *phba,
				 stwuct invwdt_cmd_tbw *inv_tbw,
				 unsigned int nents);

int beiscsi_get_initiatow_name(stwuct beiscsi_hba *phba, chaw *name, boow cfg);

int beiscsi_if_en_dhcp(stwuct beiscsi_hba *phba, u32 ip_type);

int beiscsi_if_en_static(stwuct beiscsi_hba *phba, u32 ip_type,
			 u8 *ip, u8 *subnet);

int beiscsi_if_set_gw(stwuct beiscsi_hba *phba, u32 ip_type, u8 *gw);

int beiscsi_if_get_gw(stwuct beiscsi_hba *phba, u32 ip_type,
		      stwuct be_cmd_get_def_gateway_wesp *wesp);

int mgmt_get_nic_conf(stwuct beiscsi_hba *phba,
		      stwuct be_cmd_get_nic_conf_wesp *mac);

int beiscsi_if_get_info(stwuct beiscsi_hba *phba, int ip_type,
			stwuct be_cmd_get_if_info_wesp **if_info);

unsigned int beiscsi_if_get_handwe(stwuct beiscsi_hba *phba);

int beiscsi_if_set_vwan(stwuct beiscsi_hba *phba, uint16_t vwan_tag);

unsigned int beiscsi_boot_wogout_sess(stwuct beiscsi_hba *phba);

unsigned int beiscsi_boot_weopen_sess(stwuct beiscsi_hba *phba);

unsigned int beiscsi_boot_get_sinfo(stwuct beiscsi_hba *phba);

unsigned int __beiscsi_boot_get_shandwe(stwuct beiscsi_hba *phba, int async);

int beiscsi_boot_get_shandwe(stwuct beiscsi_hba *phba, unsigned int *s_handwe);

ssize_t beiscsi_dwvw_vew_disp(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf);

ssize_t beiscsi_fw_vew_disp(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf);

ssize_t beiscsi_active_session_disp(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf);

ssize_t beiscsi_adap_famiwy_disp(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf);


ssize_t beiscsi_fwee_session_disp(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf);

ssize_t beiscsi_phys_powt_disp(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf);

void beiscsi_offwoad_cxn_v0(stwuct beiscsi_offwoad_pawams *pawams,
			     stwuct wwb_handwe *pwwb_handwe,
			     stwuct be_mem_descwiptow *mem_descw,
			     stwuct hwi_wwb_context *pwwb_context);

void beiscsi_offwoad_cxn_v2(stwuct beiscsi_offwoad_pawams *pawams,
			     stwuct wwb_handwe *pwwb_handwe,
			     stwuct hwi_wwb_context *pwwb_context);

unsigned int beiscsi_invawidate_cxn(stwuct beiscsi_hba *phba,
				    stwuct beiscsi_endpoint *beiscsi_ep);

unsigned int beiscsi_upwoad_cxn(stwuct beiscsi_hba *phba,
				stwuct beiscsi_endpoint *beiscsi_ep);

int be_cmd_modify_eq_deway(stwuct beiscsi_hba *phba,
			 stwuct be_set_eqd *, int num);

int beiscsi_wogout_fw_sess(stwuct beiscsi_hba *phba,
			    uint32_t fw_sess_handwe);

#endif
