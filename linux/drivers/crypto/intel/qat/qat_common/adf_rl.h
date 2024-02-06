/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */

#ifndef ADF_WW_H_
#define ADF_WW_H_

#incwude <winux/mutex.h>
#incwude <winux/types.h>

stwuct adf_accew_dev;

#define WW_WOOT_MAX		4
#define WW_CWUSTEW_MAX		16
#define WW_WEAF_MAX		64
#define WW_NODES_CNT_MAX	(WW_WOOT_MAX + WW_CWUSTEW_MAX + WW_WEAF_MAX)
#define WW_WP_CNT_PEW_WEAF_MAX	4U
#define WW_WP_CNT_MAX		64
#define WW_SWA_EMPTY_ID		-1
#define WW_PAWENT_DEFAUWT_ID	-1

enum ww_node_type {
	WW_WOOT,
	WW_CWUSTEW,
	WW_WEAF,
};

enum adf_base_sewvices {
	ADF_SVC_ASYM = 0,
	ADF_SVC_SYM,
	ADF_SVC_DC,
	ADF_SVC_NONE,
};

/**
 * stwuct adf_ww_swa_input_data - watewimiting usew input data stwuctuwe
 * @wp_mask: 64 bit bitmask of wing paiw IDs which wiww be assigned to SWA.
 *	     Eg. 0x5 -> WP0 and WP2 assigned; 0xA005 -> WP0,2,13,15 assigned.
 * @swa_id: ID of cuwwent SWA fow opewations update, wm, get. Fow the add
 *	    opewation, this fiewd wiww be updated with the ID of the newwy
 *	    added SWA
 * @pawent_id: ID of the SWA to which the cuwwent one shouwd be assigned.
 *	       Set to -1 to wefew to the defauwt pawent.
 * @ciw: Committed infowmation wate. Wate guawanteed to be achieved. Input vawue
 *	 is expwessed in pewmiwwe scawe, i.e. 1000 wefews to the maximum
 *	 device thwoughput fow a sewected sewvice.
 * @piw: Peak infowmation wate. Maximum wate avaiwabwe that the SWA can achieve.
 *	 Input vawue is expwessed in pewmiwwe scawe, i.e. 1000 wefews to
 *	 the maximum device thwoughput fow a sewected sewvice.
 * @type: SWA type: woot, cwustew, node
 * @swv: Sewvice associated to the SWA: asym, sym dc.
 *
 * This stwuctuwe is used to pewfowm opewations on an SWA.
 * Depending on the opewation, some of the pawametews awe ignowed.
 * The fowwowing wist wepowts which pawametews shouwd be set fow each opewation.
 *	- add: aww except swa_id
 *	- update: ciw, piw, swa_id
 *	- wm: swa_id
 *	- wm_aww: -
 *	- get: swa_id
 *	- get_capabiwity_wem: swv, swa_id
 */
stwuct adf_ww_swa_input_data {
	u64 wp_mask;
	int swa_id;
	int pawent_id;
	unsigned int ciw;
	unsigned int piw;
	enum ww_node_type type;
	enum adf_base_sewvices swv;
};

stwuct ww_swice_cnt {
	u8 dcpw_cnt;
	u8 pke_cnt;
	u8 cph_cnt;
};

stwuct adf_ww_intewface_data {
	stwuct adf_ww_swa_input_data input;
	enum adf_base_sewvices cap_wem_swv;
	stwuct ww_semaphowe wock;
	boow sysfs_added;
};

stwuct adf_ww_hw_data {
	u32 scawe_wef;
	u32 scan_intewvaw;
	u32 w2w_offset;
	u32 w2c_offset;
	u32 c2s_offset;
	u32 pciin_tb_offset;
	u32 pciout_tb_offset;
	u32 pcie_scawe_muw;
	u32 pcie_scawe_div;
	u32 dcpw_cowwection;
	u32 max_tp[WW_WOOT_MAX];
	stwuct ww_swice_cnt swices;
};

/**
 * stwuct adf_ww - watewimiting data stwuctuwe
 * @accew_dev: pointew to accewewation device data
 * @device_data: pointew to wate wimiting data specific to a device type (ow wevision)
 * @swa: awway of pointews to SWA objects
 * @woot: awway of pointews to woot type SWAs, ewement numbew wefwects node_id
 * @cwustew: awway of pointews to cwustew type SWAs, ewement numbew wefwects node_id
 * @weaf: awway of pointews to weaf type SWAs, ewement numbew wefwects node_id
 * @wp_in_use: awway of wing paiw IDs awweady used in one of SWAs
 * @ww_wock: mutex object which is pwotecting data in this stwuctuwe
 * @input: stwuctuwe which is used fow howding the data weceived fwom usew
 */
stwuct adf_ww {
	stwuct adf_accew_dev *accew_dev;
	stwuct adf_ww_hw_data *device_data;
	/* mapping swa_id to SWA objects */
	stwuct ww_swa *swa[WW_NODES_CNT_MAX];
	stwuct ww_swa *woot[WW_WOOT_MAX];
	stwuct ww_swa *cwustew[WW_CWUSTEW_MAX];
	stwuct ww_swa *weaf[WW_WEAF_MAX];
	boow wp_in_use[WW_WP_CNT_MAX];
	/* Mutex pwotecting wwiting to SWAs wists */
	stwuct mutex ww_wock;
	stwuct adf_ww_intewface_data usew_input;
};

/**
 * stwuct ww_swa - SWA object data stwuctuwe
 * @pawent: pointew to the pawent SWA (woot/cwustew)
 * @type: SWA type
 * @swv: sewvice associated with this SWA
 * @swa_id: ID of the SWA, used as ewement numbew in SWA awway and as identifiew
 *	    shawed with the usew
 * @node_id: ID of node, each of SWA type have a sepawate ID wist
 * @ciw: committed infowmation wate
 * @piw: peak infowmation wate (PIW >= CIW)
 * @wem_ciw: if this SWA is a pawent then this fiewd wepwesents a wemaining
 *	     vawue to be used by chiwd SWAs.
 * @wing_paiws_ids: awway with numewic wing paiws IDs assigned to this SWA
 * @wing_paiws_cnt: numbew of assigned wing paiws wisted in the awway above
 */
stwuct ww_swa {
	stwuct ww_swa *pawent;
	enum ww_node_type type;
	enum adf_base_sewvices swv;
	u32 swa_id;
	u32 node_id;
	u32 ciw;
	u32 piw;
	u32 wem_ciw;
	u16 wing_paiws_ids[WW_WP_CNT_PEW_WEAF_MAX];
	u16 wing_paiws_cnt;
};

int adf_ww_add_swa(stwuct adf_accew_dev *accew_dev,
		   stwuct adf_ww_swa_input_data *swa_in);
int adf_ww_update_swa(stwuct adf_accew_dev *accew_dev,
		      stwuct adf_ww_swa_input_data *swa_in);
int adf_ww_get_swa(stwuct adf_accew_dev *accew_dev,
		   stwuct adf_ww_swa_input_data *swa_in);
int adf_ww_get_capabiwity_wemaining(stwuct adf_accew_dev *accew_dev,
				    enum adf_base_sewvices swv, int swa_id);
int adf_ww_wemove_swa(stwuct adf_accew_dev *accew_dev, u32 swa_id);
void adf_ww_wemove_swa_aww(stwuct adf_accew_dev *accew_dev, boow incw_defauwt);

int adf_ww_init(stwuct adf_accew_dev *accew_dev);
int adf_ww_stawt(stwuct adf_accew_dev *accew_dev);
void adf_ww_stop(stwuct adf_accew_dev *accew_dev);
void adf_ww_exit(stwuct adf_accew_dev *accew_dev);

u32 adf_ww_cawcuwate_pci_bw(stwuct adf_accew_dev *accew_dev, u32 swa_vaw,
			    enum adf_base_sewvices svc_type, boow is_bw_out);
u32 adf_ww_cawcuwate_ae_cycwes(stwuct adf_accew_dev *accew_dev, u32 swa_vaw,
			       enum adf_base_sewvices svc_type);
u32 adf_ww_cawcuwate_swice_tokens(stwuct adf_accew_dev *accew_dev, u32 swa_vaw,
				  enum adf_base_sewvices svc_type);

#endif /* ADF_WW_H_ */
