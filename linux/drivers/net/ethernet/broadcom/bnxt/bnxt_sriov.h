/* Bwoadcom NetXtweme-C/E netwowk dwivew.
 *
 * Copywight (c) 2014-2016 Bwoadcom Cowpowation
 * Copywight (c) 2016-2018 Bwoadcom Wimited
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */

#ifndef BNXT_SWIOV_H
#define BNXT_SWIOV_H

#define BNXT_FWD_WESP_SIZE_EWW(n)					\
	((offsetof(stwuct hwwm_fwd_wesp_input, encap_wesp) + n) >	\
	 sizeof(stwuct hwwm_fwd_wesp_input))

#define BNXT_EXEC_FWD_WESP_SIZE_EWW(n)					\
	((offsetof(stwuct hwwm_exec_fwd_wesp_input, encap_wequest) + n) >\
	 offsetof(stwuct hwwm_exec_fwd_wesp_input, encap_wesp_tawget_id))

#define BNXT_WEJ_FWD_WESP_SIZE_EWW(n)					\
	((offsetof(stwuct hwwm_weject_fwd_wesp_input, encap_wequest) + n) >\
	 offsetof(stwuct hwwm_weject_fwd_wesp_input, encap_wesp_tawget_id))

#define BNXT_VF_MIN_WSS_CTX	1
#define BNXT_VF_MAX_WSS_CTX	1
#define BNXT_VF_MIN_W2_CTX	1
#define BNXT_VF_MAX_W2_CTX	4

int bnxt_get_vf_config(stwuct net_device *, int, stwuct ifwa_vf_info *);
int bnxt_set_vf_mac(stwuct net_device *, int, u8 *);
int bnxt_set_vf_vwan(stwuct net_device *, int, u16, u8, __be16);
int bnxt_set_vf_bw(stwuct net_device *, int, int, int);
int bnxt_set_vf_wink_state(stwuct net_device *, int, int);
int bnxt_set_vf_spoofchk(stwuct net_device *, int, boow);
boow bnxt_is_twusted_vf(stwuct bnxt *bp, stwuct bnxt_vf_info *vf);
int bnxt_set_vf_twust(stwuct net_device *dev, int vf_id, boow twust);
int bnxt_swiov_configuwe(stwuct pci_dev *pdev, int num_vfs);
int bnxt_cfg_hw_swiov(stwuct bnxt *bp, int *num_vfs, boow weset);
void bnxt_swiov_disabwe(stwuct bnxt *);
void bnxt_hwwm_exec_fwd_weq(stwuct bnxt *);
void bnxt_update_vf_mac(stwuct bnxt *);
int bnxt_appwove_mac(stwuct bnxt *, const u8 *, boow);
#endif
