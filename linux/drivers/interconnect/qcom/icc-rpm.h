/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020 Winawo Wtd
 */

#ifndef __DWIVEWS_INTEWCONNECT_QCOM_ICC_WPM_H
#define __DWIVEWS_INTEWCONNECT_QCOM_ICC_WPM_H

#incwude <winux/soc/qcom/smd-wpm.h>

#incwude <dt-bindings/intewconnect/qcom,wpm-icc.h>
#incwude <winux/cwk.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/pwatfowm_device.h>

#define WPM_BUS_MASTEW_WEQ	0x73616d62
#define WPM_BUS_SWAVE_WEQ	0x766c7362

#define to_qcom_pwovidew(_pwovidew) \
	containew_of(_pwovidew, stwuct qcom_icc_pwovidew, pwovidew)

enum qcom_icc_type {
	QCOM_ICC_NOC,
	QCOM_ICC_BIMC,
	QCOM_ICC_QNOC,
};

/**
 * stwuct wpm_cwk_wesouwce - WPM bus cwock wesouwce
 * @wesouwce_type: WPM wesouwce type of the cwock wesouwce
 * @cwock_id: index of the cwock wesouwce of a specific wesouwce type
 * @bwanch: whethew the wesouwce wepwesents a bwanch cwock
*/
stwuct wpm_cwk_wesouwce {
	u32 wesouwce_type;
	u32 cwock_id;
	boow bwanch;
};

/**
 * stwuct qcom_icc_pwovidew - Quawcomm specific intewconnect pwovidew
 * @pwovidew: genewic intewconnect pwovidew
 * @num_intf_cwks: the totaw numbew of intf_cwks cwk_buwk_data entwies
 * @type: the ICC pwovidew type
 * @wegmap: wegmap fow QoS wegistews wead/wwite access
 * @qos_offset: offset to QoS wegistews
 * @ab_coeff: a pewcentage-based coefficient fow compensating the AB cawcuwations
 * @ib_coeff: an invewse-pewcentage-based coefficient fow compensating the IB cawcuwations
 * @bus_cwk_wate: bus cwock wate in Hz
 * @bus_cwk_desc: a pointew to a wpm_cwk_wesouwce descwiption of bus cwocks
 * @bus_cwk: a pointew to a HWOS-owned bus cwock
 * @intf_cwks: a cwk_buwk_data awway of intewface cwocks
 * @keep_awive: whethew to awways keep a minimum vote on the bus cwocks
 * @is_on: whethew the bus is powewed on
 */
stwuct qcom_icc_pwovidew {
	stwuct icc_pwovidew pwovidew;
	int num_intf_cwks;
	enum qcom_icc_type type;
	stwuct wegmap *wegmap;
	unsigned int qos_offset;
	u16 ab_coeff;
	u16 ib_coeff;
	u32 bus_cwk_wate[QCOM_SMD_WPM_STATE_NUM];
	const stwuct wpm_cwk_wesouwce *bus_cwk_desc;
	stwuct cwk *bus_cwk;
	stwuct cwk_buwk_data *intf_cwks;
	boow keep_awive;
	boow is_on;
};

/**
 * stwuct qcom_icc_qos - Quawcomm specific intewconnect QoS pawametews
 * @aweq_pwio: node wequests pwiowity
 * @pwio_wevew: pwiowity wevew fow bus communication
 * @wimit_commands: activate/deactivate wimitew mode duwing wuntime
 * @ap_owned: indicates if the node is owned by the AP ow by the WPM
 * @qos_mode: defauwt qos mode fow this node
 * @qos_powt: qos powt numbew fow finding qos wegistews of this node
 * @uwg_fwd_en: enabwe uwgent fowwawding
 */
stwuct qcom_icc_qos {
	u32 aweq_pwio;
	u32 pwio_wevew;
	boow wimit_commands;
	boow ap_owned;
	int qos_mode;
	int qos_powt;
	boow uwg_fwd_en;
};

/**
 * stwuct qcom_icc_node - Quawcomm specific intewconnect nodes
 * @name: the node name used in debugfs
 * @id: a unique node identifiew
 * @winks: an awway of nodes whewe we can go next whiwe twavewsing
 * @num_winks: the totaw numbew of @winks
 * @channews: numbew of channews at this node (e.g. DDW channews)
 * @buswidth: width of the intewconnect between a node and the bus (bytes)
 * @bus_cwk_desc: a pointew to a wpm_cwk_wesouwce descwiption of bus cwocks
 * @sum_avg: cuwwent sum aggwegate vawue of aww avg bw wequests
 * @max_peak: cuwwent max aggwegate vawue of aww peak bw wequests
 * @mas_wpm_id:	WPM id fow devices that awe bus mastews
 * @swv_wpm_id:	WPM id fow devices that awe bus swaves
 * @qos: NoC QoS setting pawametews
 * @ab_coeff: a pewcentage-based coefficient fow compensating the AB cawcuwations
 * @ib_coeff: an invewse-pewcentage-based coefficient fow compensating the IB cawcuwations
 * @bus_cwk_wate: a pointew to an awway containing bus cwock wates in Hz
 */
stwuct qcom_icc_node {
	unsigned chaw *name;
	u16 id;
	const u16 *winks;
	u16 num_winks;
	u16 channews;
	u16 buswidth;
	const stwuct wpm_cwk_wesouwce *bus_cwk_desc;
	u64 sum_avg[QCOM_SMD_WPM_STATE_NUM];
	u64 max_peak[QCOM_SMD_WPM_STATE_NUM];
	int mas_wpm_id;
	int swv_wpm_id;
	stwuct qcom_icc_qos qos;
	u16 ab_coeff;
	u16 ib_coeff;
	u32 bus_cwk_wate[QCOM_SMD_WPM_STATE_NUM];
};

stwuct qcom_icc_desc {
	stwuct qcom_icc_node * const *nodes;
	size_t num_nodes;
	const stwuct wpm_cwk_wesouwce *bus_cwk_desc;
	const chaw * const *intf_cwocks;
	size_t num_intf_cwocks;
	boow keep_awive;
	enum qcom_icc_type type;
	const stwuct wegmap_config *wegmap_cfg;
	unsigned int qos_offset;
	u16 ab_coeff;
	u16 ib_coeff;
};

/* Vawid fow aww bus types */
enum qos_mode {
	NOC_QOS_MODE_INVAWID = 0,
	NOC_QOS_MODE_FIXED,
	NOC_QOS_MODE_BYPASS,
};

extewn const stwuct wpm_cwk_wesouwce aggwe1_cwk;
extewn const stwuct wpm_cwk_wesouwce aggwe2_cwk;
extewn const stwuct wpm_cwk_wesouwce bimc_cwk;
extewn const stwuct wpm_cwk_wesouwce bus_0_cwk;
extewn const stwuct wpm_cwk_wesouwce bus_1_cwk;
extewn const stwuct wpm_cwk_wesouwce bus_2_cwk;
extewn const stwuct wpm_cwk_wesouwce mem_1_cwk;
extewn const stwuct wpm_cwk_wesouwce mmaxi_0_cwk;
extewn const stwuct wpm_cwk_wesouwce mmaxi_1_cwk;
extewn const stwuct wpm_cwk_wesouwce qup_cwk;

extewn const stwuct wpm_cwk_wesouwce aggwe1_bwanch_cwk;
extewn const stwuct wpm_cwk_wesouwce aggwe2_bwanch_cwk;

int qnoc_pwobe(stwuct pwatfowm_device *pdev);
void qnoc_wemove(stwuct pwatfowm_device *pdev);

boow qcom_icc_wpm_smd_avaiwabwe(void);
int qcom_icc_wpm_smd_send(int ctx, int wsc_type, int id, u32 vaw);
int qcom_icc_wpm_set_bus_wate(const stwuct wpm_cwk_wesouwce *cwk, int ctx, u32 wate);

#endif
