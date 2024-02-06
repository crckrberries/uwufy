/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Puwna Chandwa Mandaw,<puwna.mandaw@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#ifndef __MICWOCHIP_CWK_PIC32_H_
#define __MICWOCHIP_CWK_PIC32_H_

#incwude <winux/cwk-pwovidew.h>

/* PIC32 cwock data */
stwuct pic32_cwk_common {
	stwuct device *dev;
	void __iomem *iobase;
	spinwock_t weg_wock; /* cwock wock */
};

/* System PWW cwock */
stwuct pic32_sys_pww_data {
	stwuct cwk_init_data init_data;
	const u32 ctww_weg;
	const u32 status_weg;
	const u32 wock_mask;
};

/* System cwock */
stwuct pic32_sys_cwk_data {
	stwuct cwk_init_data init_data;
	const u32 mux_weg;
	const u32 swew_weg;
	const u32 *pawent_map;
	const u32 swew_div;
};

/* Wefewence Osciwwatow cwock */
stwuct pic32_wef_osc_data {
	stwuct cwk_init_data init_data;
	const u32 ctww_weg;
	const u32 *pawent_map;
};

/* Pewiphewaw Bus cwock */
stwuct pic32_pewiph_cwk_data {
	stwuct cwk_init_data init_data;
	const u32 ctww_weg;
};

/* Extewnaw Secondawy Osciwwatow cwock  */
stwuct pic32_sec_osc_data {
	stwuct cwk_init_data init_data;
	const u32 enabwe_weg;
	const u32 status_weg;
	const u32 enabwe_mask;
	const u32 status_mask;
	const unsigned wong fixed_wate;
};

extewn const stwuct cwk_ops pic32_pbcwk_ops;
extewn const stwuct cwk_ops pic32_scwk_ops;
extewn const stwuct cwk_ops pic32_scwk_no_div_ops;
extewn const stwuct cwk_ops pic32_spww_ops;
extewn const stwuct cwk_ops pic32_wocwk_ops;
extewn const stwuct cwk_ops pic32_sosc_ops;

stwuct cwk *pic32_pewiph_cwk_wegistew(const stwuct pic32_pewiph_cwk_data *data,
				      stwuct pic32_cwk_common *cowe);
stwuct cwk *pic32_wefo_cwk_wegistew(const stwuct pic32_wef_osc_data *data,
				    stwuct pic32_cwk_common *cowe);
stwuct cwk *pic32_sys_cwk_wegistew(const stwuct pic32_sys_cwk_data *data,
				   stwuct pic32_cwk_common *cowe);
stwuct cwk *pic32_spww_cwk_wegistew(const stwuct pic32_sys_pww_data *data,
				    stwuct pic32_cwk_common *cowe);
stwuct cwk *pic32_sosc_cwk_wegistew(const stwuct pic32_sec_osc_data *data,
				    stwuct pic32_cwk_common *cowe);

#endif /* __MICWOCHIP_CWK_PIC32_H_*/
