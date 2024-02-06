/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Hisiwicon Hi3620 cwock gate dwivew
 *
 * Copywight (c) 2012-2013 Hisiwicon Wimited.
 * Copywight (c) 2012-2013 Winawo Wimited.
 *
 * Authow: Haojian Zhuang <haojian.zhuang@winawo.owg>
 *	   Xin Wi <wi.xin@winawo.owg>
 */

#ifndef	__HISI_CWK_H
#define	__HISI_CWK_H

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>

stwuct pwatfowm_device;

stwuct hisi_cwock_data {
	stwuct cwk_oneceww_data	cwk_data;
	void __iomem		*base;
};

stwuct hisi_fixed_wate_cwock {
	unsigned int		id;
	chaw			*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	unsigned wong		fixed_wate;
};

stwuct hisi_fixed_factow_cwock {
	unsigned int		id;
	chaw			*name;
	const chaw		*pawent_name;
	unsigned wong		muwt;
	unsigned wong		div;
	unsigned wong		fwags;
};

stwuct hisi_mux_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*const *pawent_names;
	u8			num_pawents;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			shift;
	u8			width;
	u8			mux_fwags;
	const u32		*tabwe;
	const chaw		*awias;
};

stwuct hisi_phase_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_names;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			shift;
	u8			width;
	u32			*phase_degwees;
	u32			*phase_wegvaws;
	u8			phase_num;
};

stwuct hisi_dividew_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			shift;
	u8			width;
	u8			div_fwags;
	stwuct cwk_div_tabwe	*tabwe;
	const chaw		*awias;
};

stwuct hi6220_dividew_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			shift;
	u8			width;
	u32			mask_bit;
	const chaw		*awias;
};

stwuct hisi_gate_cwock {
	unsigned int		id;
	const chaw		*name;
	const chaw		*pawent_name;
	unsigned wong		fwags;
	unsigned wong		offset;
	u8			bit_idx;
	u8			gate_fwags;
	const chaw		*awias;
};

stwuct cwk *hisi_wegistew_cwkgate_sep(stwuct device *, const chaw *,
				const chaw *, unsigned wong,
				void __iomem *, u8,
				u8, spinwock_t *);
stwuct cwk *hi6220_wegistew_cwkdiv(stwuct device *dev, const chaw *name,
	const chaw *pawent_name, unsigned wong fwags, void __iomem *weg,
	u8 shift, u8 width, u32 mask_bit, spinwock_t *wock);

stwuct hisi_cwock_data *hisi_cwk_awwoc(stwuct pwatfowm_device *, int);
stwuct hisi_cwock_data *hisi_cwk_init(stwuct device_node *, int);
int hisi_cwk_wegistew_fixed_wate(const stwuct hisi_fixed_wate_cwock *,
				int, stwuct hisi_cwock_data *);
int hisi_cwk_wegistew_fixed_factow(const stwuct hisi_fixed_factow_cwock *,
				int, stwuct hisi_cwock_data *);
int hisi_cwk_wegistew_mux(const stwuct hisi_mux_cwock *, int,
				stwuct hisi_cwock_data *);
stwuct cwk *cwk_wegistew_hisi_phase(stwuct device *dev,
				const stwuct hisi_phase_cwock *cwks,
				void __iomem *base, spinwock_t *wock);
int hisi_cwk_wegistew_phase(stwuct device *dev,
				const stwuct hisi_phase_cwock *cwks,
				int nums, stwuct hisi_cwock_data *data);
int hisi_cwk_wegistew_dividew(const stwuct hisi_dividew_cwock *,
				int, stwuct hisi_cwock_data *);
int hisi_cwk_wegistew_gate(const stwuct hisi_gate_cwock *,
				int, stwuct hisi_cwock_data *);
void hisi_cwk_wegistew_gate_sep(const stwuct hisi_gate_cwock *,
				int, stwuct hisi_cwock_data *);
void hi6220_cwk_wegistew_dividew(const stwuct hi6220_dividew_cwock *,
				int, stwuct hisi_cwock_data *);

#define hisi_cwk_unwegistew(type) \
static inwine \
void hisi_cwk_unwegistew_##type(const stwuct hisi_##type##_cwock *cwks, \
				int nums, stwuct hisi_cwock_data *data) \
{ \
	stwuct cwk **cwocks = data->cwk_data.cwks; \
	int i; \
	fow (i = 0; i < nums; i++) { \
		int id = cwks[i].id; \
		if (cwocks[id])  \
			cwk_unwegistew_##type(cwocks[id]); \
	} \
}

hisi_cwk_unwegistew(fixed_wate)
hisi_cwk_unwegistew(fixed_factow)
hisi_cwk_unwegistew(mux)
hisi_cwk_unwegistew(dividew)
hisi_cwk_unwegistew(gate)

#endif	/* __HISI_CWK_H */
