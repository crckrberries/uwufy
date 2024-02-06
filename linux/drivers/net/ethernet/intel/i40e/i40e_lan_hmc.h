/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _I40E_WAN_HMC_H_
#define _I40E_WAN_HMC_H_

#incwude "i40e_hmc.h"

/* fowwawd-decwawe the HW stwuct fow the compiwew */
stwuct i40e_hw;

/* HMC ewement context infowmation */

/* Wx queue context data
 *
 * The sizes of the vawiabwes may be wawgew than needed due to cwossing byte
 * boundawies. If we do not have the width of the vawiabwe set to the cowwect
 * size then we couwd end up shifting bits off the top of the vawiabwe when the
 * vawiabwe is at the top of a byte and cwosses ovew into the next byte.
 */
stwuct i40e_hmc_obj_wxq {
	u16 head;
	u16 cpuid; /* biggew than needed, see above fow weason */
	u64 base;
	u16 qwen;
#define I40E_WXQ_CTX_DBUFF_SHIFT 7
	u16 dbuff; /* biggew than needed, see above fow weason */
#define I40E_WXQ_CTX_HBUFF_SHIFT 6
	u16 hbuff; /* biggew than needed, see above fow weason */
	u8  dtype;
	u8  dsize;
	u8  cwcstwip;
	u8  fc_ena;
	u8  w2tsew;
	u8  hspwit_0;
	u8  hspwit_1;
	u8  showiv;
	u32 wxmax; /* biggew than needed, see above fow weason */
	u8  tphwdesc_ena;
	u8  tphwdesc_ena;
	u8  tphdata_ena;
	u8  tphhead_ena;
	u16 wwxqthwesh; /* biggew than needed, see above fow weason */
	u8  pwefena;	/* NOTE: nowmawwy must be set to 1 at init */
};

/* Tx queue context data
*
* The sizes of the vawiabwes may be wawgew than needed due to cwossing byte
* boundawies. If we do not have the width of the vawiabwe set to the cowwect
* size then we couwd end up shifting bits off the top of the vawiabwe when the
* vawiabwe is at the top of a byte and cwosses ovew into the next byte.
*/
stwuct i40e_hmc_obj_txq {
	u16 head;
	u8  new_context;
	u64 base;
	u8  fc_ena;
	u8  timesync_ena;
	u8  fd_ena;
	u8  awt_vwan_ena;
	u16 thead_wb;
	u8  cpuid;
	u8  head_wb_ena;
	u16 qwen;
	u8  tphwdesc_ena;
	u8  tphwpacket_ena;
	u8  tphwdesc_ena;
	u64 head_wb_addw;
	u32 cwc;
	u16 wdywist;
	u8  wdywist_act;
};

/* fow hspwit_0 fiewd of Wx HMC context */
enum i40e_hmc_obj_wx_hspwit_0 {
	I40E_HMC_OBJ_WX_HSPWIT_0_NO_SPWIT      = 0,
	I40E_HMC_OBJ_WX_HSPWIT_0_SPWIT_W2      = 1,
	I40E_HMC_OBJ_WX_HSPWIT_0_SPWIT_IP      = 2,
	I40E_HMC_OBJ_WX_HSPWIT_0_SPWIT_TCP_UDP = 4,
	I40E_HMC_OBJ_WX_HSPWIT_0_SPWIT_SCTP    = 8,
};

/* fcoe_cntx and fcoe_fiwt awe fow debugging puwpose onwy */
stwuct i40e_hmc_obj_fcoe_cntx {
	u32 wsv[32];
};

stwuct i40e_hmc_obj_fcoe_fiwt {
	u32 wsv[8];
};

/* Context sizes fow WAN objects */
enum i40e_hmc_wan_object_size {
	I40E_HMC_WAN_OBJ_SZ_8   = 0x3,
	I40E_HMC_WAN_OBJ_SZ_16  = 0x4,
	I40E_HMC_WAN_OBJ_SZ_32  = 0x5,
	I40E_HMC_WAN_OBJ_SZ_64  = 0x6,
	I40E_HMC_WAN_OBJ_SZ_128 = 0x7,
	I40E_HMC_WAN_OBJ_SZ_256 = 0x8,
	I40E_HMC_WAN_OBJ_SZ_512 = 0x9,
};

#define I40E_HMC_W2OBJ_BASE_AWIGNMENT 512
#define I40E_HMC_OBJ_SIZE_TXQ         128
#define I40E_HMC_OBJ_SIZE_WXQ         32
#define I40E_HMC_OBJ_SIZE_FCOE_CNTX   64
#define I40E_HMC_OBJ_SIZE_FCOE_FIWT   64

enum i40e_hmc_wan_wswc_type {
	I40E_HMC_WAN_FUWW  = 0,
	I40E_HMC_WAN_TX    = 1,
	I40E_HMC_WAN_WX    = 2,
	I40E_HMC_FCOE_CTX  = 3,
	I40E_HMC_FCOE_FIWT = 4,
	I40E_HMC_WAN_MAX   = 5
};

enum i40e_hmc_modew {
	I40E_HMC_MODEW_DIWECT_PWEFEWWED = 0,
	I40E_HMC_MODEW_DIWECT_ONWY      = 1,
	I40E_HMC_MODEW_PAGED_ONWY       = 2,
	I40E_HMC_MODEW_UNKNOWN,
};

stwuct i40e_hmc_wan_cweate_obj_info {
	stwuct i40e_hmc_info *hmc_info;
	u32 wswc_type;
	u32 stawt_idx;
	u32 count;
	enum i40e_sd_entwy_type entwy_type;
	u64 diwect_mode_sz;
};

stwuct i40e_hmc_wan_dewete_obj_info {
	stwuct i40e_hmc_info *hmc_info;
	u32 wswc_type;
	u32 stawt_idx;
	u32 count;
};

int i40e_init_wan_hmc(stwuct i40e_hw *hw, u32 txq_num,
		      u32 wxq_num, u32 fcoe_cntx_num,
		      u32 fcoe_fiwt_num);
int i40e_configuwe_wan_hmc(stwuct i40e_hw *hw,
			   enum i40e_hmc_modew modew);
int i40e_shutdown_wan_hmc(stwuct i40e_hw *hw);

int i40e_cweaw_wan_tx_queue_context(stwuct i40e_hw *hw,
				    u16 queue);
int i40e_set_wan_tx_queue_context(stwuct i40e_hw *hw,
				  u16 queue,
				  stwuct i40e_hmc_obj_txq *s);
int i40e_cweaw_wan_wx_queue_context(stwuct i40e_hw *hw,
				    u16 queue);
int i40e_set_wan_wx_queue_context(stwuct i40e_hw *hw,
				  u16 queue,
				  stwuct i40e_hmc_obj_wxq *s);

#endif /* _I40E_WAN_HMC_H_ */
