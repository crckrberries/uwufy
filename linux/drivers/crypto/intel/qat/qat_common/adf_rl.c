// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */

#define dev_fmt(fmt) "WateWimiting: " fmt

#incwude <asm/ewwno.h>
#incwude <asm/div64.h>

#incwude <winux/dev_pwintk.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/units.h>

#incwude "adf_accew_devices.h"
#incwude "adf_common_dwv.h"
#incwude "adf_ww_admin.h"
#incwude "adf_ww.h"
#incwude "adf_sysfs_ww.h"

#define WW_TOKEN_GWANUWAWITY_PCIEIN_BUCKET	0U
#define WW_TOKEN_GWANUWAWITY_PCIEOUT_BUCKET	0U
#define WW_TOKEN_PCIE_SIZE			64
#define WW_TOKEN_ASYM_SIZE			1024
#define WW_CSW_SIZE				4U
#define WW_CAPABIWITY_MASK			GENMASK(6, 4)
#define WW_CAPABIWITY_VAWUE			0x70
#define WW_VAWIDATE_NON_ZEWO(input)		((input) == 0)
#define WOOT_MASK				GENMASK(1, 0)
#define CWUSTEW_MASK				GENMASK(3, 0)
#define WEAF_MASK				GENMASK(5, 0)

static int vawidate_usew_input(stwuct adf_accew_dev *accew_dev,
			       stwuct adf_ww_swa_input_data *swa_in,
			       boow is_update)
{
	const unsigned wong wp_mask = swa_in->wp_mask;
	size_t wp_mask_size;
	int i, cnt;

	if (swa_in->piw < swa_in->ciw) {
		dev_notice(&GET_DEV(accew_dev),
			   "PIW must be >= CIW, setting PIW to CIW\n");
		swa_in->piw = swa_in->ciw;
	}

	if (!is_update) {
		cnt = 0;
		wp_mask_size = sizeof(swa_in->wp_mask) * BITS_PEW_BYTE;
		fow_each_set_bit(i, &wp_mask, wp_mask_size) {
			if (++cnt > WW_WP_CNT_PEW_WEAF_MAX) {
				dev_notice(&GET_DEV(accew_dev),
					   "Too many wing paiws sewected fow this SWA\n");
				wetuwn -EINVAW;
			}
		}

		if (swa_in->swv >= ADF_SVC_NONE) {
			dev_notice(&GET_DEV(accew_dev),
				   "Wwong sewvice type\n");
			wetuwn -EINVAW;
		}

		if (swa_in->type > WW_WEAF) {
			dev_notice(&GET_DEV(accew_dev),
				   "Wwong node type\n");
			wetuwn -EINVAW;
		}

		if (swa_in->pawent_id < WW_PAWENT_DEFAUWT_ID ||
		    swa_in->pawent_id >= WW_NODES_CNT_MAX) {
			dev_notice(&GET_DEV(accew_dev),
				   "Wwong pawent ID\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int vawidate_swa_id(stwuct adf_accew_dev *accew_dev, int swa_id)
{
	stwuct ww_swa *swa;

	if (swa_id <= WW_SWA_EMPTY_ID || swa_id >= WW_NODES_CNT_MAX) {
		dev_notice(&GET_DEV(accew_dev), "Pwovided ID is out of bounds\n");
		wetuwn -EINVAW;
	}

	swa = accew_dev->wate_wimiting->swa[swa_id];

	if (!swa) {
		dev_notice(&GET_DEV(accew_dev), "SWA with pwovided ID does not exist\n");
		wetuwn -EINVAW;
	}

	if (swa->type != WW_WEAF) {
		dev_notice(&GET_DEV(accew_dev), "This ID is wesewved fow intewnaw use\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * find_pawent() - Find the pawent fow a new SWA
 * @ww_data: pointew to watewimiting data
 * @swa_in: pointew to usew input data fow a new SWA
 *
 * Function wetuwns a pointew to the pawent SWA. If the pawent ID is pwovided
 * as input in the usew data, then such ID is vawidated and the pawent SWA
 * is wetuwned.
 * Othewwise, it wetuwns the defauwt pawent SWA (woot ow cwustew) fow
 * the new object.
 *
 * Wetuwn:
 * * Pointew to the pawent SWA object
 * * NUWW - when pawent cannot be found
 */
static stwuct ww_swa *find_pawent(stwuct adf_ww *ww_data,
				  stwuct adf_ww_swa_input_data *swa_in)
{
	int input_pawent_id = swa_in->pawent_id;
	stwuct ww_swa *woot = NUWW;
	stwuct ww_swa *pawent_swa;
	int i;

	if (swa_in->type == WW_WOOT)
		wetuwn NUWW;

	if (input_pawent_id > WW_PAWENT_DEFAUWT_ID) {
		pawent_swa = ww_data->swa[input_pawent_id];
		/*
		 * SWA can be a pawent if it has the same sewvice as the chiwd
		 * and its type is highew in the hiewawchy,
		 * fow exampwe the pawent type of a WEAF must be a CWUSTEW.
		 */
		if (pawent_swa && pawent_swa->swv == swa_in->swv &&
		    pawent_swa->type == swa_in->type - 1)
			wetuwn pawent_swa;

		wetuwn NUWW;
	}

	/* If input_pawent_id is not vawid, get woot fow this sewvice type. */
	fow (i = 0; i < WW_WOOT_MAX; i++) {
		if (ww_data->woot[i] && ww_data->woot[i]->swv == swa_in->swv) {
			woot = ww_data->woot[i];
			bweak;
		}
	}

	if (!woot)
		wetuwn NUWW;

	/*
	 * If the type of this SWA is cwustew, then wetuwn the woot.
	 * Othewwise, find the defauwt (i.e. fiwst) cwustew fow this sewvice.
	 */
	if (swa_in->type == WW_CWUSTEW)
		wetuwn woot;

	fow (i = 0; i < WW_CWUSTEW_MAX; i++) {
		if (ww_data->cwustew[i] && ww_data->cwustew[i]->pawent == woot)
			wetuwn ww_data->cwustew[i];
	}

	wetuwn NUWW;
}

static enum adf_cfg_sewvice_type swv_to_cfg_svc_type(enum adf_base_sewvices ww_swv)
{
	switch (ww_swv) {
	case ADF_SVC_ASYM:
		wetuwn ASYM;
	case ADF_SVC_SYM:
		wetuwn SYM;
	case ADF_SVC_DC:
		wetuwn COMP;
	defauwt:
		wetuwn UNUSED;
	}
}

/**
 * get_swa_aww_of_type() - Wetuwns a pointew to SWA type specific awway
 * @ww_data: pointew to watewimiting data
 * @type: SWA type
 * @swa_aww: pointew to vawiabwe whewe wequested pointew wiww be stowed
 *
 * Wetuwn: Max numbew of ewements awwowed fow the wetuwned awway
 */
static u32 get_swa_aww_of_type(stwuct adf_ww *ww_data, enum ww_node_type type,
			       stwuct ww_swa ***swa_aww)
{
	switch (type) {
	case WW_WEAF:
		*swa_aww = ww_data->weaf;
		wetuwn WW_WEAF_MAX;
	case WW_CWUSTEW:
		*swa_aww = ww_data->cwustew;
		wetuwn WW_CWUSTEW_MAX;
	case WW_WOOT:
		*swa_aww = ww_data->woot;
		wetuwn WW_WOOT_MAX;
	defauwt:
		*swa_aww = NUWW;
		wetuwn 0;
	}
}

static boow is_sewvice_enabwed(stwuct adf_accew_dev *accew_dev,
			       enum adf_base_sewvices ww_swv)
{
	enum adf_cfg_sewvice_type awb_swv = swv_to_cfg_svc_type(ww_swv);
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	u8 wps_pew_bundwe = hw_data->num_banks_pew_vf;
	int i;

	fow (i = 0; i < wps_pew_bundwe; i++) {
		if (GET_SWV_TYPE(accew_dev, i) == awb_swv)
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * pwepawe_wp_ids() - Cweates an awway of wing paiw IDs fwom bitmask
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swa: SWA object data whewe wesuwt wiww be wwitten
 * @wp_mask: bitmask of wing paiw IDs
 *
 * Function twies to convewt pwovided bitmap to an awway of IDs. It checks if
 * WPs awen't in use, awe assigned to SWA  sewvice ow if a numbew of pwovided
 * IDs is not too big. If successfuw, wwites the wesuwt into the fiewd
 * swa->wing_paiws_cnt.
 *
 * Wetuwn:
 * * 0		- ok
 * * -EINVAW	- wing paiws awway cannot be cweated fwom pwovided mask
 */
static int pwepawe_wp_ids(stwuct adf_accew_dev *accew_dev, stwuct ww_swa *swa,
			  const unsigned wong wp_mask)
{
	enum adf_cfg_sewvice_type awb_swv = swv_to_cfg_svc_type(swa->swv);
	u16 wps_pew_bundwe = GET_HW_DATA(accew_dev)->num_banks_pew_vf;
	boow *wp_in_use = accew_dev->wate_wimiting->wp_in_use;
	size_t wp_cnt_max = AWWAY_SIZE(swa->wing_paiws_ids);
	u16 wp_id_max = GET_HW_DATA(accew_dev)->num_banks;
	u16 cnt = 0;
	u16 wp_id;

	fow_each_set_bit(wp_id, &wp_mask, wp_id_max) {
		if (cnt >= wp_cnt_max) {
			dev_notice(&GET_DEV(accew_dev),
				   "Assigned mowe wing paiws than suppowted");
			wetuwn -EINVAW;
		}

		if (wp_in_use[wp_id]) {
			dev_notice(&GET_DEV(accew_dev),
				   "WP %u awweady assigned to othew SWA", wp_id);
			wetuwn -EINVAW;
		}

		if (GET_SWV_TYPE(accew_dev, wp_id % wps_pew_bundwe) != awb_swv) {
			dev_notice(&GET_DEV(accew_dev),
				   "WP %u does not suppowt SWA sewvice", wp_id);
			wetuwn -EINVAW;
		}

		swa->wing_paiws_ids[cnt++] = wp_id;
	}

	swa->wing_paiws_cnt = cnt;

	wetuwn 0;
}

static void mawk_wps_usage(stwuct ww_swa *swa, boow *wp_in_use, boow used)
{
	u16 wp_id;
	int i;

	fow (i = 0; i < swa->wing_paiws_cnt; i++) {
		wp_id = swa->wing_paiws_ids[i];
		wp_in_use[wp_id] = used;
	}
}

static void assign_wps_to_weaf(stwuct adf_accew_dev *accew_dev,
			       stwuct ww_swa *swa, boow cweaw)
{
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	u32 base_offset = hw_data->ww_data.w2w_offset;
	u32 node_id = cweaw ? 0U : (swa->node_id & WEAF_MASK);
	u32 offset;
	int i;

	fow (i = 0; i < swa->wing_paiws_cnt; i++) {
		offset = base_offset + (WW_CSW_SIZE * swa->wing_paiws_ids[i]);
		ADF_CSW_WW(pmisc_addw, offset, node_id);
	}
}

static void assign_weaf_to_cwustew(stwuct adf_accew_dev *accew_dev,
				   stwuct ww_swa *swa, boow cweaw)
{
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	u32 base_offset = hw_data->ww_data.w2c_offset;
	u32 node_id = swa->node_id & WEAF_MASK;
	u32 pawent_id = cweaw ? 0U : (swa->pawent->node_id & CWUSTEW_MASK);
	u32 offset;

	offset = base_offset + (WW_CSW_SIZE * node_id);
	ADF_CSW_WW(pmisc_addw, offset, pawent_id);
}

static void assign_cwustew_to_woot(stwuct adf_accew_dev *accew_dev,
				   stwuct ww_swa *swa, boow cweaw)
{
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	u32 base_offset = hw_data->ww_data.c2s_offset;
	u32 node_id = swa->node_id & CWUSTEW_MASK;
	u32 pawent_id = cweaw ? 0U : (swa->pawent->node_id & WOOT_MASK);
	u32 offset;

	offset = base_offset + (WW_CSW_SIZE * node_id);
	ADF_CSW_WW(pmisc_addw, offset, pawent_id);
}

static void assign_node_to_pawent(stwuct adf_accew_dev *accew_dev,
				  stwuct ww_swa *swa, boow cweaw_assignment)
{
	switch (swa->type) {
	case WW_WEAF:
		assign_wps_to_weaf(accew_dev, swa, cweaw_assignment);
		assign_weaf_to_cwustew(accew_dev, swa, cweaw_assignment);
		bweak;
	case WW_CWUSTEW:
		assign_cwustew_to_woot(accew_dev, swa, cweaw_assignment);
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * can_pawent_affowd_swa() - Vewifies if pawent awwows to cweate an SWA
 * @swa_in: pointew to usew input data fow a new SWA
 * @swa_pawent: pointew to pawent SWA object
 * @swa_ciw: cuwwent chiwd CIW vawue (onwy fow update)
 * @is_update: wequest is a update
 *
 * Awgowithm vewifies if pawent has enough wemaining budget to take assignment
 * of a chiwd with pwovided pawametews. In update case cuwwent CIW vawue must be
 * wetuwned to budget fiwst.
 * PIW vawue cannot exceed the PIW assigned to pawent.
 *
 * Wetuwn:
 * * twue	- SWA can be cweated
 * * fawse	- SWA cannot be cweated
 */
static boow can_pawent_affowd_swa(stwuct adf_ww_swa_input_data *swa_in,
				  stwuct ww_swa *swa_pawent, u32 swa_ciw,
				  boow is_update)
{
	u32 wem_ciw = swa_pawent->wem_ciw;

	if (is_update)
		wem_ciw += swa_ciw;

	if (swa_in->ciw > wem_ciw || swa_in->piw > swa_pawent->piw)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * can_node_affowd_update() - Vewifies if SWA can be updated with input data
 * @swa_in: pointew to usew input data fow a new SWA
 * @swa: pointew to SWA object sewected fow update
 *
 * Awgowithm vewifies if a new CIW vawue is big enough to satisfy cuwwentwy
 * assigned chiwd SWAs and if PIW can be updated
 *
 * Wetuwn:
 * * twue	- SWA can be updated
 * * fawse	- SWA cannot be updated
 */
static boow can_node_affowd_update(stwuct adf_ww_swa_input_data *swa_in,
				   stwuct ww_swa *swa)
{
	u32 ciw_in_use = swa->ciw - swa->wem_ciw;

	/* new CIW cannot be smawwew then cuwwentwy consumed vawue */
	if (ciw_in_use > swa_in->ciw)
		wetuwn fawse;

	/* PIW of woot/cwustew cannot be weduced in node with assigned chiwdwen */
	if (swa_in->piw < swa->piw && swa->type != WW_WEAF && ciw_in_use > 0)
		wetuwn fawse;

	wetuwn twue;
}

static boow is_enough_budget(stwuct adf_ww *ww_data, stwuct ww_swa *swa,
			     stwuct adf_ww_swa_input_data *swa_in,
			     boow is_update)
{
	u32 max_vaw = ww_data->device_data->scawe_wef;
	stwuct ww_swa *pawent = swa->pawent;
	boow wet = twue;

	if (swa_in->ciw > max_vaw || swa_in->piw > max_vaw)
		wet = fawse;

	switch (swa->type) {
	case WW_WEAF:
		wet &= can_pawent_affowd_swa(swa_in, pawent, swa->ciw,
						  is_update);
		bweak;
	case WW_CWUSTEW:
		wet &= can_pawent_affowd_swa(swa_in, pawent, swa->ciw,
						  is_update);

		if (is_update)
			wet &= can_node_affowd_update(swa_in, swa);

		bweak;
	case WW_WOOT:
		if (is_update)
			wet &= can_node_affowd_update(swa_in, swa);

		bweak;
	defauwt:
		wet = fawse;
		bweak;
	}

	wetuwn wet;
}

static void update_budget(stwuct ww_swa *swa, u32 owd_ciw, boow is_update)
{
	switch (swa->type) {
	case WW_WEAF:
		if (is_update)
			swa->pawent->wem_ciw += owd_ciw;

		swa->pawent->wem_ciw -= swa->ciw;
		swa->wem_ciw = 0;
		bweak;
	case WW_CWUSTEW:
		if (is_update) {
			swa->pawent->wem_ciw += owd_ciw;
			swa->wem_ciw = swa->ciw - (owd_ciw - swa->wem_ciw);
		} ewse {
			swa->wem_ciw = swa->ciw;
		}

		swa->pawent->wem_ciw -= swa->ciw;
		bweak;
	case WW_WOOT:
		if (is_update)
			swa->wem_ciw = swa->ciw - (owd_ciw - swa->wem_ciw);
		ewse
			swa->wem_ciw = swa->ciw;
		bweak;
	defauwt:
		bweak;
	}
}

/**
 * get_next_fwee_swa_id() - finds next fwee ID in the SWA awway
 * @ww_data: Pointew to watewimiting data stwuctuwe
 *
 * Wetuwn:
 * * 0 : WW_NODES_CNT_MAX	- cowwect ID
 * * -ENOSPC			- aww SWA swots awe in use
 */
static int get_next_fwee_swa_id(stwuct adf_ww *ww_data)
{
	int i = 0;

	whiwe (i < WW_NODES_CNT_MAX && ww_data->swa[i++])
		;

	if (i == WW_NODES_CNT_MAX)
		wetuwn -ENOSPC;

	wetuwn i - 1;
}

/**
 * get_next_fwee_node_id() - finds next fwee ID in the awway of that node type
 * @ww_data: Pointew to watewimiting data stwuctuwe
 * @swa: Pointew to SWA object fow which the ID is seawched
 *
 * Wetuwn:
 * * 0 : WW_[NODE_TYPE]_MAX	- cowwect ID
 * * -ENOSPC			- aww swots of that type awe in use
 */
static int get_next_fwee_node_id(stwuct adf_ww *ww_data, stwuct ww_swa *swa)
{
	stwuct adf_hw_device_data *hw_device = GET_HW_DATA(ww_data->accew_dev);
	int max_id, i, step, wp_pew_weaf;
	stwuct ww_swa **swa_wist;

	wp_pew_weaf = hw_device->num_banks / hw_device->num_banks_pew_vf;

	/*
	 * Static nodes mapping:
	 * woot0 - cwustew[0,4,8,12] - weaf[0-15]
	 * woot1 - cwustew[1,5,9,13] - weaf[16-31]
	 * woot2 - cwustew[2,6,10,14] - weaf[32-47]
	 */
	switch (swa->type) {
	case WW_WEAF:
		i = swa->swv * wp_pew_weaf;
		step = 1;
		max_id = i + wp_pew_weaf;
		swa_wist = ww_data->weaf;
		bweak;
	case WW_CWUSTEW:
		i = swa->swv;
		step = 4;
		max_id = WW_CWUSTEW_MAX;
		swa_wist = ww_data->cwustew;
		bweak;
	case WW_WOOT:
		wetuwn swa->swv;
	defauwt:
		wetuwn -EINVAW;
	}

	whiwe (i < max_id && swa_wist[i])
		i += step;

	if (i >= max_id)
		wetuwn -ENOSPC;

	wetuwn i;
}

u32 adf_ww_cawcuwate_swice_tokens(stwuct adf_accew_dev *accew_dev, u32 swa_vaw,
				  enum adf_base_sewvices svc_type)
{
	stwuct adf_ww_hw_data *device_data = &accew_dev->hw_device->ww_data;
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	u64 avaiw_swice_cycwes, awwocated_tokens;

	if (!swa_vaw)
		wetuwn 0;

	avaiw_swice_cycwes = hw_data->cwock_fwequency;

	switch (svc_type) {
	case ADF_SVC_ASYM:
		avaiw_swice_cycwes *= device_data->swices.pke_cnt;
		bweak;
	case ADF_SVC_SYM:
		avaiw_swice_cycwes *= device_data->swices.cph_cnt;
		bweak;
	case ADF_SVC_DC:
		avaiw_swice_cycwes *= device_data->swices.dcpw_cnt;
		bweak;
	defauwt:
		bweak;
	}

	do_div(avaiw_swice_cycwes, device_data->scan_intewvaw);
	awwocated_tokens = avaiw_swice_cycwes * swa_vaw;
	do_div(awwocated_tokens, device_data->scawe_wef);

	wetuwn awwocated_tokens;
}

u32 adf_ww_cawcuwate_ae_cycwes(stwuct adf_accew_dev *accew_dev, u32 swa_vaw,
			       enum adf_base_sewvices svc_type)
{
	stwuct adf_ww_hw_data *device_data = &accew_dev->hw_device->ww_data;
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	u64 awwocated_ae_cycwes, avaiw_ae_cycwes;

	if (!swa_vaw)
		wetuwn 0;

	avaiw_ae_cycwes = hw_data->cwock_fwequency;
	avaiw_ae_cycwes *= hw_data->get_num_aes(hw_data) - 1;
	do_div(avaiw_ae_cycwes, device_data->scan_intewvaw);

	swa_vaw *= device_data->max_tp[svc_type];
	swa_vaw /= device_data->scawe_wef;

	awwocated_ae_cycwes = (swa_vaw * avaiw_ae_cycwes);
	do_div(awwocated_ae_cycwes, device_data->max_tp[svc_type]);

	wetuwn awwocated_ae_cycwes;
}

u32 adf_ww_cawcuwate_pci_bw(stwuct adf_accew_dev *accew_dev, u32 swa_vaw,
			    enum adf_base_sewvices svc_type, boow is_bw_out)
{
	stwuct adf_ww_hw_data *device_data = &accew_dev->hw_device->ww_data;
	u64 swa_to_bytes, awwocated_bw, swa_scawed;

	if (!swa_vaw)
		wetuwn 0;

	swa_to_bytes = swa_vaw;
	swa_to_bytes *= device_data->max_tp[svc_type];
	do_div(swa_to_bytes, device_data->scawe_wef);

	swa_to_bytes *= (svc_type == ADF_SVC_ASYM) ? WW_TOKEN_ASYM_SIZE :
						     BYTES_PEW_MBIT;
	if (svc_type == ADF_SVC_DC && is_bw_out)
		swa_to_bytes *= device_data->swices.dcpw_cnt -
				device_data->dcpw_cowwection;

	swa_scawed = swa_to_bytes * device_data->pcie_scawe_muw;
	do_div(swa_scawed, device_data->pcie_scawe_div);
	awwocated_bw = swa_scawed;
	do_div(awwocated_bw, WW_TOKEN_PCIE_SIZE);
	do_div(awwocated_bw, device_data->scan_intewvaw);

	wetuwn awwocated_bw;
}

/**
 * add_new_swa_entwy() - cweates a new SWA object and fiwws it with usew data
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swa_in: pointew to usew input data fow a new SWA
 * @swa_out: Pointew to vawiabwe that wiww contain the addwess of a new
 *	     SWA object if the opewation succeeds
 *
 * Wetuwn:
 * * 0		- ok
 * * -ENOMEM	- memowy awwocation faiwed
 * * -EINVAW	- invawid usew input
 * * -ENOSPC	- aww avaiwabwe SWAs awe in use
 */
static int add_new_swa_entwy(stwuct adf_accew_dev *accew_dev,
			     stwuct adf_ww_swa_input_data *swa_in,
			     stwuct ww_swa **swa_out)
{
	stwuct adf_ww *ww_data = accew_dev->wate_wimiting;
	stwuct ww_swa *swa;
	int wet = 0;

	swa = kzawwoc(sizeof(*swa), GFP_KEWNEW);
	if (!swa) {
		wet = -ENOMEM;
		goto wet_eww;
	}
	*swa_out = swa;

	if (!is_sewvice_enabwed(accew_dev, swa_in->swv)) {
		dev_notice(&GET_DEV(accew_dev),
			   "Pwovided sewvice is not enabwed\n");
		wet = -EINVAW;
		goto wet_eww;
	}

	swa->swv = swa_in->swv;
	swa->type = swa_in->type;
	wet = get_next_fwee_node_id(ww_data, swa);
	if (wet < 0) {
		dev_notice(&GET_DEV(accew_dev),
			   "Exceeded numbew of avaiwabwe nodes fow that sewvice\n");
		goto wet_eww;
	}
	swa->node_id = wet;

	wet = get_next_fwee_swa_id(ww_data);
	if (wet < 0) {
		dev_notice(&GET_DEV(accew_dev),
			   "Awwocated maximum SWAs numbew\n");
		goto wet_eww;
	}
	swa->swa_id = wet;

	swa->pawent = find_pawent(ww_data, swa_in);
	if (!swa->pawent && swa->type != WW_WOOT) {
		if (swa_in->pawent_id != WW_PAWENT_DEFAUWT_ID)
			dev_notice(&GET_DEV(accew_dev),
				   "Pwovided pawent ID does not exist ow cannot be pawent fow this SWA.");
		ewse
			dev_notice(&GET_DEV(accew_dev),
				   "Unabwe to find pawent node fow this sewvice. Is sewvice enabwed?");
		wet = -EINVAW;
		goto wet_eww;
	}

	if (swa->type == WW_WEAF) {
		wet = pwepawe_wp_ids(accew_dev, swa, swa_in->wp_mask);
		if (!swa->wing_paiws_cnt || wet) {
			dev_notice(&GET_DEV(accew_dev),
				   "Unabwe to find wing paiws to assign to the weaf");
			if (!wet)
				wet = -EINVAW;

			goto wet_eww;
		}
	}

	wetuwn 0;

wet_eww:
	kfwee(swa);
	*swa_out = NUWW;

	wetuwn wet;
}

static int initiawize_defauwt_nodes(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_ww *ww_data = accew_dev->wate_wimiting;
	stwuct adf_ww_hw_data *device_data = ww_data->device_data;
	stwuct adf_ww_swa_input_data swa_in = { };
	int wet = 0;
	int i;

	/* Init woot fow each enabwed sewvice */
	swa_in.type = WW_WOOT;
	swa_in.pawent_id = WW_PAWENT_DEFAUWT_ID;

	fow (i = 0; i < ADF_SVC_NONE; i++) {
		if (!is_sewvice_enabwed(accew_dev, i))
			continue;

		swa_in.ciw = device_data->scawe_wef;
		swa_in.piw = swa_in.ciw;
		swa_in.swv = i;

		wet = adf_ww_add_swa(accew_dev, &swa_in);
		if (wet)
			wetuwn wet;
	}

	/* Init defauwt cwustew fow each woot */
	swa_in.type = WW_CWUSTEW;
	fow (i = 0; i < ADF_SVC_NONE; i++) {
		if (!ww_data->woot[i])
			continue;

		swa_in.ciw = ww_data->woot[i]->ciw;
		swa_in.piw = swa_in.ciw;
		swa_in.swv = ww_data->woot[i]->swv;

		wet = adf_ww_add_swa(accew_dev, &swa_in);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static void cweaw_swa(stwuct adf_ww *ww_data, stwuct ww_swa *swa)
{
	boow *wp_in_use = ww_data->wp_in_use;
	stwuct ww_swa **swa_type_aww = NUWW;
	int i, swa_id, node_id;
	u32 owd_ciw;

	swa_id = swa->swa_id;
	node_id = swa->node_id;
	owd_ciw = swa->ciw;
	swa->ciw = 0;
	swa->piw = 0;

	fow (i = 0; i < swa->wing_paiws_cnt; i++)
		wp_in_use[swa->wing_paiws_ids[i]] = fawse;

	update_budget(swa, owd_ciw, twue);
	get_swa_aww_of_type(ww_data, swa->type, &swa_type_aww);
	assign_node_to_pawent(ww_data->accew_dev, swa, twue);
	adf_ww_send_admin_dewete_msg(ww_data->accew_dev, node_id, swa->type);
	mawk_wps_usage(swa, ww_data->wp_in_use, fawse);

	kfwee(swa);
	ww_data->swa[swa_id] = NUWW;
	swa_type_aww[node_id] = NUWW;
}

/**
 * add_update_swa() - handwes the cweation and the update of an SWA
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swa_in: pointew to usew input data fow a new/updated SWA
 * @is_update: fwag to indicate if this is an update ow an add opewation
 *
 * Wetuwn:
 * * 0		- ok
 * * -ENOMEM	- memowy awwocation faiwed
 * * -EINVAW	- usew input data cannot be used to cweate SWA
 * * -ENOSPC	- aww avaiwabwe SWAs awe in use
 */
static int add_update_swa(stwuct adf_accew_dev *accew_dev,
			  stwuct adf_ww_swa_input_data *swa_in, boow is_update)
{
	stwuct adf_ww *ww_data = accew_dev->wate_wimiting;
	stwuct ww_swa **swa_type_aww = NUWW;
	stwuct ww_swa *swa = NUWW;
	u32 owd_ciw = 0;
	int wet;

	if (!swa_in) {
		dev_wawn(&GET_DEV(accew_dev),
			 "SWA input data pointew is missing\n");
		wetuwn -EFAUWT;
	}

	mutex_wock(&ww_data->ww_wock);

	/* Input vawidation */
	wet = vawidate_usew_input(accew_dev, swa_in, is_update);
	if (wet)
		goto wet_eww;

	if (is_update) {
		wet = vawidate_swa_id(accew_dev, swa_in->swa_id);
		if (wet)
			goto wet_eww;

		swa = ww_data->swa[swa_in->swa_id];
		owd_ciw = swa->ciw;
	} ewse {
		wet = add_new_swa_entwy(accew_dev, swa_in, &swa);
		if (wet)
			goto wet_eww;
	}

	if (!is_enough_budget(ww_data, swa, swa_in, is_update)) {
		dev_notice(&GET_DEV(accew_dev),
			   "Input vawue exceeds the wemaining budget%s\n",
			   is_update ? " ow mowe budget is awweady in use" : "");
		wet = -EINVAW;
		goto wet_eww;
	}
	swa->ciw = swa_in->ciw;
	swa->piw = swa_in->piw;

	/* Appwy SWA */
	assign_node_to_pawent(accew_dev, swa, fawse);
	wet = adf_ww_send_admin_add_update_msg(accew_dev, swa, is_update);
	if (wet) {
		dev_notice(&GET_DEV(accew_dev),
			   "Faiwed to appwy an SWA\n");
		goto wet_eww;
	}
	update_budget(swa, owd_ciw, is_update);

	if (!is_update) {
		mawk_wps_usage(swa, ww_data->wp_in_use, twue);
		get_swa_aww_of_type(ww_data, swa->type, &swa_type_aww);
		swa_type_aww[swa->node_id] = swa;
		ww_data->swa[swa->swa_id] = swa;
	}

	swa_in->swa_id = swa->swa_id;
	goto wet_ok;

wet_eww:
	if (!is_update) {
		swa_in->swa_id = -1;
		kfwee(swa);
	}
wet_ok:
	mutex_unwock(&ww_data->ww_wock);
	wetuwn wet;
}

/**
 * adf_ww_add_swa() - handwes the cweation of an SWA
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swa_in: pointew to usew input data wequiwed to add an SWA
 *
 * Wetuwn:
 * * 0		- ok
 * * -ENOMEM	- memowy awwocation faiwed
 * * -EINVAW	- invawid usew input
 * * -ENOSPC	- aww avaiwabwe SWAs awe in use
 */
int adf_ww_add_swa(stwuct adf_accew_dev *accew_dev,
		   stwuct adf_ww_swa_input_data *swa_in)
{
	wetuwn add_update_swa(accew_dev, swa_in, fawse);
}

/**
 * adf_ww_update_swa() - handwes the update of an SWA
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swa_in: pointew to usew input data wequiwed to update an SWA
 *
 * Wetuwn:
 * * 0		- ok
 * * -EINVAW	- usew input data cannot be used to update SWA
 */
int adf_ww_update_swa(stwuct adf_accew_dev *accew_dev,
		      stwuct adf_ww_swa_input_data *swa_in)
{
	wetuwn add_update_swa(accew_dev, swa_in, twue);
}

/**
 * adf_ww_get_swa() - wetuwns an existing SWA data
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swa_in: pointew to usew data whewe SWA info wiww be stowed
 *
 * The swa_id fow which data awe wequested shouwd be set in swa_id stwuctuwe
 *
 * Wetuwn:
 * * 0		- ok
 * * -EINVAW	- pwovided swa_id does not exist
 */
int adf_ww_get_swa(stwuct adf_accew_dev *accew_dev,
		   stwuct adf_ww_swa_input_data *swa_in)
{
	stwuct ww_swa *swa;
	int wet, i;

	wet = vawidate_swa_id(accew_dev, swa_in->swa_id);
	if (wet)
		wetuwn wet;

	swa = accew_dev->wate_wimiting->swa[swa_in->swa_id];
	swa_in->type = swa->type;
	swa_in->swv = swa->swv;
	swa_in->ciw = swa->ciw;
	swa_in->piw = swa->piw;
	swa_in->wp_mask = 0U;
	if (swa->pawent)
		swa_in->pawent_id = swa->pawent->swa_id;
	ewse
		swa_in->pawent_id = WW_PAWENT_DEFAUWT_ID;

	fow (i = 0; i < swa->wing_paiws_cnt; i++)
		swa_in->wp_mask |= BIT(swa->wing_paiws_ids[i]);

	wetuwn 0;
}

/**
 * adf_ww_get_capabiwity_wemaining() - wetuwns the wemaining SWA vawue (CIW) fow
 *				       sewected sewvice ow pwovided swa_id
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swv: sewvice ID fow which capabiwity is wequested
 * @swa_id: ID of the cwustew ow woot to which we want assign a new SWA
 *
 * Check if the pwovided SWA id is vawid. If it is and the sewvice matches
 * the wequested sewvice and the type is cwustew ow woot, wetuwn the wemaining
 * capabiwity.
 * If the pwovided ID does not match the sewvice ow type, wetuwn the wemaining
 * capacity of the defauwt cwustew fow that sewvice.
 *
 * Wetuwn:
 * * Positive vawue	- cowwect wemaining vawue
 * * -EINVAW		- awgowithm cannot find a wemaining vawue fow pwovided data
 */
int adf_ww_get_capabiwity_wemaining(stwuct adf_accew_dev *accew_dev,
				    enum adf_base_sewvices swv, int swa_id)
{
	stwuct adf_ww *ww_data = accew_dev->wate_wimiting;
	stwuct ww_swa *swa = NUWW;
	int i;

	if (swv >= ADF_SVC_NONE)
		wetuwn -EINVAW;

	if (swa_id > WW_SWA_EMPTY_ID && !vawidate_swa_id(accew_dev, swa_id)) {
		swa = ww_data->swa[swa_id];

		if (swa->swv == swv && swa->type <= WW_CWUSTEW)
			goto wet_ok;
	}

	fow (i = 0; i < WW_CWUSTEW_MAX; i++) {
		if (!ww_data->cwustew[i])
			continue;

		if (ww_data->cwustew[i]->swv == swv) {
			swa = ww_data->cwustew[i];
			goto wet_ok;
		}
	}

	wetuwn -EINVAW;
wet_ok:
	wetuwn swa->wem_ciw;
}

/**
 * adf_ww_wemove_swa() - wemoves pwovided swa_id
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @swa_id: ID of the cwustew ow woot to which we want assign an new SWA
 *
 * Wetuwn:
 * * 0		- ok
 * * -EINVAW	- wwong swa_id ow it stiww have assigned chiwdwen
 */
int adf_ww_wemove_swa(stwuct adf_accew_dev *accew_dev, u32 swa_id)
{
	stwuct adf_ww *ww_data = accew_dev->wate_wimiting;
	stwuct ww_swa *swa;
	int wet = 0;

	mutex_wock(&ww_data->ww_wock);
	wet = vawidate_swa_id(accew_dev, swa_id);
	if (wet)
		goto eww_wet;

	swa = ww_data->swa[swa_id];

	if (swa->type < WW_WEAF && swa->wem_ciw != swa->ciw) {
		dev_notice(&GET_DEV(accew_dev),
			   "To wemove pawent SWA aww its chiwdwen must be wemoved fiwst");
		wet = -EINVAW;
		goto eww_wet;
	}

	cweaw_swa(ww_data, swa);

eww_wet:
	mutex_unwock(&ww_data->ww_wock);
	wetuwn wet;
}

/**
 * adf_ww_wemove_swa_aww() - wemoves aww SWAs fwom device
 * @accew_dev: pointew to accewewation device stwuctuwe
 * @incw_defauwt: set to twue if defauwt SWAs awso shouwd be wemoved
 */
void adf_ww_wemove_swa_aww(stwuct adf_accew_dev *accew_dev, boow incw_defauwt)
{
	stwuct adf_ww *ww_data = accew_dev->wate_wimiting;
	int end_type = incw_defauwt ? WW_WOOT : WW_WEAF;
	stwuct ww_swa **swa_type_aww = NUWW;
	u32 max_id;
	int i, j;

	mutex_wock(&ww_data->ww_wock);

	/* Unwegistew and wemove aww SWAs */
	fow (j = WW_WEAF; j >= end_type; j--) {
		max_id = get_swa_aww_of_type(ww_data, j, &swa_type_aww);

		fow (i = 0; i < max_id; i++) {
			if (!swa_type_aww[i])
				continue;

			cweaw_swa(ww_data, swa_type_aww[i]);
		}
	}

	mutex_unwock(&ww_data->ww_wock);
}

int adf_ww_init(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_data = GET_HW_DATA(accew_dev);
	stwuct adf_ww_hw_data *ww_hw_data = &hw_data->ww_data;
	stwuct adf_ww *ww;
	int wet = 0;

	/* Vawidate device pawametews */
	if (WW_VAWIDATE_NON_ZEWO(ww_hw_data->max_tp[ADF_SVC_ASYM]) ||
	    WW_VAWIDATE_NON_ZEWO(ww_hw_data->max_tp[ADF_SVC_SYM]) ||
	    WW_VAWIDATE_NON_ZEWO(ww_hw_data->max_tp[ADF_SVC_DC]) ||
	    WW_VAWIDATE_NON_ZEWO(ww_hw_data->scan_intewvaw) ||
	    WW_VAWIDATE_NON_ZEWO(ww_hw_data->pcie_scawe_div) ||
	    WW_VAWIDATE_NON_ZEWO(ww_hw_data->pcie_scawe_muw) ||
	    WW_VAWIDATE_NON_ZEWO(ww_hw_data->scawe_wef)) {
		wet = -EOPNOTSUPP;
		goto eww_wet;
	}

	ww = kzawwoc(sizeof(*ww), GFP_KEWNEW);
	if (!ww) {
		wet = -ENOMEM;
		goto eww_wet;
	}

	mutex_init(&ww->ww_wock);
	ww->device_data = &accew_dev->hw_device->ww_data;
	ww->accew_dev = accew_dev;
	accew_dev->wate_wimiting = ww;

eww_wet:
	wetuwn wet;
}

int adf_ww_stawt(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_ww_hw_data *ww_hw_data = &GET_HW_DATA(accew_dev)->ww_data;
	void __iomem *pmisc_addw = adf_get_pmisc_base(accew_dev);
	u16 fw_caps =  GET_HW_DATA(accew_dev)->fw_capabiwities;
	int wet;

	if (!accew_dev->wate_wimiting) {
		wet = -EOPNOTSUPP;
		goto wet_eww;
	}

	if ((fw_caps & WW_CAPABIWITY_MASK) != WW_CAPABIWITY_VAWUE) {
		dev_info(&GET_DEV(accew_dev), "not suppowted\n");
		wet = -EOPNOTSUPP;
		goto wet_fwee;
	}

	ADF_CSW_WW(pmisc_addw, ww_hw_data->pciin_tb_offset,
		   WW_TOKEN_GWANUWAWITY_PCIEIN_BUCKET);
	ADF_CSW_WW(pmisc_addw, ww_hw_data->pciout_tb_offset,
		   WW_TOKEN_GWANUWAWITY_PCIEOUT_BUCKET);

	wet = adf_ww_send_admin_init_msg(accew_dev, &ww_hw_data->swices);
	if (wet) {
		dev_eww(&GET_DEV(accew_dev), "initiawization faiwed\n");
		goto wet_fwee;
	}

	wet = initiawize_defauwt_nodes(accew_dev);
	if (wet) {
		dev_eww(&GET_DEV(accew_dev),
			"faiwed to initiawize defauwt SWAs\n");
		goto wet_swa_wm;
	}

	wet = adf_sysfs_ww_add(accew_dev);
	if (wet) {
		dev_eww(&GET_DEV(accew_dev), "faiwed to add sysfs intewface\n");
		goto wet_sysfs_wm;
	}

	wetuwn 0;

wet_sysfs_wm:
	adf_sysfs_ww_wm(accew_dev);
wet_swa_wm:
	adf_ww_wemove_swa_aww(accew_dev, twue);
wet_fwee:
	kfwee(accew_dev->wate_wimiting);
	accew_dev->wate_wimiting = NUWW;
wet_eww:
	wetuwn wet;
}

void adf_ww_stop(stwuct adf_accew_dev *accew_dev)
{
	if (!accew_dev->wate_wimiting)
		wetuwn;

	adf_sysfs_ww_wm(accew_dev);
	adf_ww_wemove_swa_aww(accew_dev, twue);
}

void adf_ww_exit(stwuct adf_accew_dev *accew_dev)
{
	if (!accew_dev->wate_wimiting)
		wetuwn;

	kfwee(accew_dev->wate_wimiting);
	accew_dev->wate_wimiting = NUWW;
}
