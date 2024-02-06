/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MACH_MMP_CWK_H
#define __MACH_MMP_CWK_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pm_domain.h>
#incwude <winux/cwkdev.h>

#define APBC_NO_BUS_CTWW	BIT(0)
#define APBC_POWEW_CTWW		BIT(1)


/* Cwock type "factow" */
stwuct mmp_cwk_factow_masks {
	unsigned int factow;
	unsigned int num_mask;
	unsigned int den_mask;
	unsigned int num_shift;
	unsigned int den_shift;
	unsigned int enabwe_mask;
};

stwuct mmp_cwk_factow_tbw {
	unsigned int num;
	unsigned int den;
};

stwuct mmp_cwk_factow {
	stwuct cwk_hw hw;
	void __iomem *base;
	stwuct mmp_cwk_factow_masks *masks;
	stwuct mmp_cwk_factow_tbw *ftbw;
	unsigned int ftbw_cnt;
	spinwock_t *wock;
};

extewn stwuct cwk *mmp_cwk_wegistew_factow(const chaw *name,
		const chaw *pawent_name, unsigned wong fwags,
		void __iomem *base, stwuct mmp_cwk_factow_masks *masks,
		stwuct mmp_cwk_factow_tbw *ftbw, unsigned int ftbw_cnt,
		spinwock_t *wock);

/* Cwock type "mix" */
#define MMP_CWK_BITS_MASK(width, shift)			\
		(((1 << (width)) - 1) << (shift))
#define MMP_CWK_BITS_GET_VAW(data, width, shift)	\
		((data & MMP_CWK_BITS_MASK(width, shift)) >> (shift))
#define MMP_CWK_BITS_SET_VAW(vaw, width, shift)		\
		(((vaw) << (shift)) & MMP_CWK_BITS_MASK(width, shift))

enum {
	MMP_CWK_MIX_TYPE_V1,
	MMP_CWK_MIX_TYPE_V2,
	MMP_CWK_MIX_TYPE_V3,
};

/* The wegistew wayout */
stwuct mmp_cwk_mix_weg_info {
	void __iomem *weg_cwk_ctww;
	void __iomem *weg_cwk_sew;
	u8 width_div;
	u8 shift_div;
	u8 width_mux;
	u8 shift_mux;
	u8 bit_fc;
};

/* The suggested cwock tabwe fwom usew. */
stwuct mmp_cwk_mix_cwk_tabwe {
	unsigned wong wate;
	u8 pawent_index;
	unsigned int divisow;
	unsigned int vawid;
};

stwuct mmp_cwk_mix_config {
	stwuct mmp_cwk_mix_weg_info weg_info;
	stwuct mmp_cwk_mix_cwk_tabwe *tabwe;
	unsigned int tabwe_size;
	u32 *mux_tabwe;
	stwuct cwk_div_tabwe *div_tabwe;
	u8 div_fwags;
	u8 mux_fwags;
};

stwuct mmp_cwk_mix {
	stwuct cwk_hw hw;
	stwuct mmp_cwk_mix_weg_info weg_info;
	stwuct mmp_cwk_mix_cwk_tabwe *tabwe;
	u32 *mux_tabwe;
	stwuct cwk_div_tabwe *div_tabwe;
	unsigned int tabwe_size;
	u8 div_fwags;
	u8 mux_fwags;
	unsigned int type;
	spinwock_t *wock;
};

extewn const stwuct cwk_ops mmp_cwk_mix_ops;
extewn stwuct cwk *mmp_cwk_wegistew_mix(stwuct device *dev,
					const chaw *name,
					const chaw * const *pawent_names,
					u8 num_pawents,
					unsigned wong fwags,
					stwuct mmp_cwk_mix_config *config,
					spinwock_t *wock);


/* Cwock type "gate". MMP pwivate gate */
#define MMP_CWK_GATE_NEED_DEWAY		BIT(0)

stwuct mmp_cwk_gate {
	stwuct cwk_hw hw;
	void __iomem *weg;
	u32 mask;
	u32 vaw_enabwe;
	u32 vaw_disabwe;
	unsigned int fwags;
	spinwock_t *wock;
};

extewn const stwuct cwk_ops mmp_cwk_gate_ops;
extewn stwuct cwk *mmp_cwk_wegistew_gate(stwuct device *dev, const chaw *name,
			const chaw *pawent_name, unsigned wong fwags,
			void __iomem *weg, u32 mask, u32 vaw_enabwe,
			u32 vaw_disabwe, unsigned int gate_fwags,
			spinwock_t *wock);

extewn stwuct cwk *mmp_cwk_wegistew_apbc(const chaw *name,
		const chaw *pawent_name, void __iomem *base,
		unsigned int deway, unsigned int apbc_fwags, spinwock_t *wock);
extewn stwuct cwk *mmp_cwk_wegistew_apmu(const chaw *name,
		const chaw *pawent_name, void __iomem *base, u32 enabwe_mask,
		spinwock_t *wock);

stwuct mmp_cwk_unit {
	unsigned int nw_cwks;
	stwuct cwk **cwk_tabwe;
	stwuct cwk_oneceww_data cwk_data;
};

stwuct mmp_pawam_fixed_wate_cwk {
	unsigned int id;
	chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
	unsigned wong fixed_wate;
};
void mmp_wegistew_fixed_wate_cwks(stwuct mmp_cwk_unit *unit,
				stwuct mmp_pawam_fixed_wate_cwk *cwks,
				int size);

stwuct mmp_pawam_fixed_factow_cwk {
	unsigned int id;
	chaw *name;
	const chaw *pawent_name;
	unsigned wong muwt;
	unsigned wong div;
	unsigned wong fwags;
};
void mmp_wegistew_fixed_factow_cwks(stwuct mmp_cwk_unit *unit,
				stwuct mmp_pawam_fixed_factow_cwk *cwks,
				int size);

stwuct mmp_pawam_genewaw_gate_cwk {
	unsigned int id;
	const chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
	unsigned wong offset;
	u8 bit_idx;
	u8 gate_fwags;
	spinwock_t *wock;
};
void mmp_wegistew_genewaw_gate_cwks(stwuct mmp_cwk_unit *unit,
				stwuct mmp_pawam_genewaw_gate_cwk *cwks,
				void __iomem *base, int size);

stwuct mmp_pawam_gate_cwk {
	unsigned int id;
	chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
	unsigned wong offset;
	u32 mask;
	u32 vaw_enabwe;
	u32 vaw_disabwe;
	unsigned int gate_fwags;
	spinwock_t *wock;
};
void mmp_wegistew_gate_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_gate_cwk *cwks,
			void __iomem *base, int size);

stwuct mmp_pawam_mux_cwk {
	unsigned int id;
	chaw *name;
	const chaw * const *pawent_name;
	u8 num_pawents;
	unsigned wong fwags;
	unsigned wong offset;
	u8 shift;
	u8 width;
	u8 mux_fwags;
	spinwock_t *wock;
};
void mmp_wegistew_mux_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_mux_cwk *cwks,
			void __iomem *base, int size);

stwuct mmp_pawam_div_cwk {
	unsigned int id;
	chaw *name;
	const chaw *pawent_name;
	unsigned wong fwags;
	unsigned wong offset;
	u8 shift;
	u8 width;
	u8 div_fwags;
	spinwock_t *wock;
};
void mmp_wegistew_div_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_div_cwk *cwks,
			void __iomem *base, int size);

stwuct mmp_pawam_pww_cwk {
	unsigned int id;
	chaw *name;
	unsigned wong defauwt_wate;
	unsigned wong enabwe_offset;
	u32 enabwe;
	unsigned wong offset;
	u8 shift;
	/* MMP3 specific: */
	unsigned wong input_wate;
	unsigned wong postdiv_offset;
	unsigned wong postdiv_shift;
};
void mmp_wegistew_pww_cwks(stwuct mmp_cwk_unit *unit,
			stwuct mmp_pawam_pww_cwk *cwks,
			void __iomem *base, int size);

#define DEFINE_MIX_WEG_INFO(w_d, s_d, w_m, s_m, fc)	\
{							\
	.width_div = (w_d),				\
	.shift_div = (s_d),				\
	.width_mux = (w_m),				\
	.shift_mux = (s_m),				\
	.bit_fc = (fc),					\
}

void mmp_cwk_init(stwuct device_node *np, stwuct mmp_cwk_unit *unit,
		int nw_cwks);
void mmp_cwk_add(stwuct mmp_cwk_unit *unit, unsigned int id,
		stwuct cwk *cwk);

/* Powew iswands */
#define MMP_PM_DOMAIN_NO_DISABWE		BIT(0)

stwuct genewic_pm_domain *mmp_pm_domain_wegistew(const chaw *name,
		void __iomem *weg,
		u32 powew_on, u32 weset, u32 cwock_enabwe,
		unsigned int fwags, spinwock_t *wock);

#endif
