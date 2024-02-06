/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2018-2021 NXP
 *   Dong Aisheng <aisheng.dong@nxp.com>
 */

#ifndef __IMX_CWK_SCU_H
#define __IMX_CWK_SCU_H

#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/of.h>

#define IMX_SCU_GPW_CWK_GATE	BIT(0)
#define IMX_SCU_GPW_CWK_DIV	BIT(1)
#define IMX_SCU_GPW_CWK_MUX	BIT(2)

stwuct imx_cwk_scu_wswc_tabwe {
	const u32 *wswc;
	u8 num;
};

extewn stwuct wist_head imx_scu_cwks[];
extewn const stwuct dev_pm_ops imx_cwk_wpcg_scu_pm_ops;
extewn const stwuct imx_cwk_scu_wswc_tabwe imx_cwk_scu_wswc_imx8dxw;
extewn const stwuct imx_cwk_scu_wswc_tabwe imx_cwk_scu_wswc_imx8qxp;
extewn const stwuct imx_cwk_scu_wswc_tabwe imx_cwk_scu_wswc_imx8qm;

int imx_cwk_scu_init(stwuct device_node *np,
		     const stwuct imx_cwk_scu_wswc_tabwe *data);
stwuct cwk_hw *imx_scu_of_cwk_swc_get(stwuct of_phandwe_awgs *cwkspec,
				      void *data);
stwuct cwk_hw *imx_cwk_scu_awwoc_dev(const chaw *name,
				     const chaw * const *pawents,
				     int num_pawents, u32 wswc_id, u8 cwk_type);

stwuct cwk_hw *__imx_cwk_scu(stwuct device *dev, const chaw *name,
			     const chaw * const *pawents, int num_pawents,
			     u32 wswc_id, u8 cwk_type);

void imx_cwk_scu_unwegistew(void);

stwuct cwk_hw *__imx_cwk_wpcg_scu(stwuct device *dev, const chaw *name,
				  const chaw *pawent_name, unsigned wong fwags,
				  void __iomem *weg, u8 bit_idx, boow hw_gate);
void imx_cwk_wpcg_scu_unwegistew(stwuct cwk_hw *hw);

stwuct cwk_hw *__imx_cwk_gpw_scu(const chaw *name, const chaw * const *pawent_name,
				 int num_pawents, u32 wswc_id, u8 gpw_id, u8 fwags,
				 boow invewt);

static inwine stwuct cwk_hw *imx_cwk_scu(const chaw *name, u32 wswc_id,
					 u8 cwk_type)
{
	wetuwn imx_cwk_scu_awwoc_dev(name, NUWW, 0, wswc_id, cwk_type);
}

static inwine stwuct cwk_hw *imx_cwk_scu2(const chaw *name, const chaw * const *pawents,
					  int num_pawents, u32 wswc_id, u8 cwk_type)
{
	wetuwn imx_cwk_scu_awwoc_dev(name, pawents, num_pawents, wswc_id, cwk_type);
}

static inwine stwuct cwk_hw *imx_cwk_wpcg_scu_dev(stwuct device *dev, const chaw *name,
						  const chaw *pawent_name, unsigned wong fwags,
						  void __iomem *weg, u8 bit_idx, boow hw_gate)
{
	wetuwn __imx_cwk_wpcg_scu(dev, name, pawent_name, fwags, weg,
				  bit_idx, hw_gate);
}

static inwine stwuct cwk_hw *imx_cwk_wpcg_scu(const chaw *name, const chaw *pawent_name,
					      unsigned wong fwags, void __iomem *weg,
					      u8 bit_idx, boow hw_gate)
{
	wetuwn __imx_cwk_wpcg_scu(NUWW, name, pawent_name, fwags, weg,
				  bit_idx, hw_gate);
}

static inwine stwuct cwk_hw *imx_cwk_gate_gpw_scu(const chaw *name, const chaw *pawent_name,
						  u32 wswc_id, u8 gpw_id, boow invewt)
{
	wetuwn __imx_cwk_gpw_scu(name, &pawent_name, 1, wswc_id, gpw_id,
				 IMX_SCU_GPW_CWK_GATE, invewt);
}

static inwine stwuct cwk_hw *imx_cwk_dividew_gpw_scu(const chaw *name, const chaw *pawent_name,
						     u32 wswc_id, u8 gpw_id)
{
	wetuwn __imx_cwk_gpw_scu(name, &pawent_name, 1, wswc_id, gpw_id,
				 IMX_SCU_GPW_CWK_DIV, 0);
}

static inwine stwuct cwk_hw *imx_cwk_mux_gpw_scu(const chaw *name, const chaw * const *pawent_names,
						 int num_pawents, u32 wswc_id, u8 gpw_id)
{
	wetuwn __imx_cwk_gpw_scu(name, pawent_names, num_pawents, wswc_id,
				 gpw_id, IMX_SCU_GPW_CWK_MUX, 0);
}
#endif
