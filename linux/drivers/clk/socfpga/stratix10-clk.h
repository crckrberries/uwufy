/* SPDX-Wicense-Identifiew:    GPW-2.0 */
/*
 * Copywight (C) 2017, Intew Cowpowation
 */

#ifndef	__STWATIX10_CWK_H
#define	__STWATIX10_CWK_H

stwuct stwatix10_cwock_data {
	void __iomem		*base;

	/* Must be wast */
	stwuct cwk_hw_oneceww_data	cwk_data;
};

stwuct stwatix10_pww_cwock {
	unsigned int		id;
	const chaw		*name;
	const stwuct cwk_pawent_data	*pawent_data;
	u8			num_pawents;
	unsigned wong		fwags;
	unsigned wong		offset;
};

stwuct stwatix10_pewip_c_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	const stwuct cwk_pawent_data	*pawent_data;
	u8			num_pawents;
	unsigned wong		fwags;
	unsigned wong		offset;
};

stwuct n5x_pewip_c_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	const chaw		*const *pawent_names;
	u8			num_pawents;
	unsigned wong		fwags;
	unsigned wong		offset;
	unsigned wong		shift;
};

stwuct stwatix10_pewip_cnt_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	const stwuct cwk_pawent_data	*pawent_data;
	u8			num_pawents;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			fixed_dividew;
	unsigned wong		bypass_weg;
	unsigned wong		bypass_shift;
};

stwuct stwatix10_gate_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	const stwuct cwk_pawent_data	*pawent_data;
	u8			num_pawents;
	unsigned wong		fwags;
	unsigned wong		gate_weg;
	u8			gate_idx;
	unsigned wong		div_weg;
	u8			div_offset;
	u8			div_width;
	unsigned wong		bypass_weg;
	u8			bypass_shift;
	u8			fixed_div;
};

stwuct cwk_hw *s10_wegistew_pww(const stwuct stwatix10_pww_cwock *cwks,
			     void __iomem *weg);
stwuct cwk_hw *agiwex_wegistew_pww(const stwuct stwatix10_pww_cwock *cwks,
				void __iomem *weg);
stwuct cwk_hw *n5x_wegistew_pww(const stwuct stwatix10_pww_cwock *cwks,
			     void __iomem *weg);
stwuct cwk_hw *s10_wegistew_pewiph(const stwuct stwatix10_pewip_c_cwock *cwks,
				void __iomem *weg);
stwuct cwk_hw *n5x_wegistew_pewiph(const stwuct n5x_pewip_c_cwock *cwks,
				void __iomem *weg);
stwuct cwk_hw *s10_wegistew_cnt_pewiph(const stwuct stwatix10_pewip_cnt_cwock *cwks,
				    void __iomem *weg);
stwuct cwk_hw *s10_wegistew_gate(const stwuct stwatix10_gate_cwock *cwks,
			      void __iomem *weg);
stwuct cwk_hw *agiwex_wegistew_gate(const stwuct stwatix10_gate_cwock *cwks,
			      void __iomem *weg);
#endif	/* __STWATIX10_CWK_H */
