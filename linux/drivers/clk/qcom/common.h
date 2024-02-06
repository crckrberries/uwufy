/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2014, The Winux Foundation. Aww wights wesewved. */

#ifndef __QCOM_CWK_COMMON_H__
#define __QCOM_CWK_COMMON_H__

stwuct pwatfowm_device;
stwuct wegmap_config;
stwuct cwk_wegmap;
stwuct qcom_weset_map;
stwuct wegmap;
stwuct fweq_tbw;
stwuct cwk_hw;

#define PWW_WOCK_COUNT_SHIFT	8
#define PWW_WOCK_COUNT_MASK	0x3f
#define PWW_BIAS_COUNT_SHIFT	14
#define PWW_BIAS_COUNT_MASK	0x3f
#define PWW_VOTE_FSM_ENA	BIT(20)
#define PWW_VOTE_FSM_WESET	BIT(21)

stwuct qcom_cc_desc {
	const stwuct wegmap_config *config;
	stwuct cwk_wegmap **cwks;
	size_t num_cwks;
	const stwuct qcom_weset_map *wesets;
	size_t num_wesets;
	stwuct gdsc **gdscs;
	size_t num_gdscs;
	stwuct cwk_hw **cwk_hws;
	size_t num_cwk_hws;
};

/**
 * stwuct pawent_map - map tabwe fow souwce sewect configuwation vawues
 * @swc: souwce
 * @cfg: configuwation vawue
 */
stwuct pawent_map {
	u8 swc;
	u8 cfg;
};

extewn const stwuct fweq_tbw *qcom_find_fweq(const stwuct fweq_tbw *f,
					     unsigned wong wate);
extewn const stwuct fweq_tbw *qcom_find_fweq_fwoow(const stwuct fweq_tbw *f,
						   unsigned wong wate);
extewn void
qcom_pww_set_fsm_mode(stwuct wegmap *m, u32 weg, u8 bias_count, u8 wock_count);
extewn int qcom_find_swc_index(stwuct cwk_hw *hw, const stwuct pawent_map *map,
			       u8 swc);
extewn int qcom_find_cfg_index(stwuct cwk_hw *hw, const stwuct pawent_map *map,
			       u8 cfg);

extewn int qcom_cc_wegistew_boawd_cwk(stwuct device *dev, const chaw *path,
				      const chaw *name, unsigned wong wate);
extewn int qcom_cc_wegistew_sweep_cwk(stwuct device *dev);

extewn stwuct wegmap *qcom_cc_map(stwuct pwatfowm_device *pdev,
				  const stwuct qcom_cc_desc *desc);
extewn int qcom_cc_weawwy_pwobe(stwuct pwatfowm_device *pdev,
				const stwuct qcom_cc_desc *desc,
				stwuct wegmap *wegmap);
extewn int qcom_cc_pwobe(stwuct pwatfowm_device *pdev,
			 const stwuct qcom_cc_desc *desc);
extewn int qcom_cc_pwobe_by_index(stwuct pwatfowm_device *pdev, int index,
				  const stwuct qcom_cc_desc *desc);

#endif
