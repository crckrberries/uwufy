/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wusseww King
 */
#ifndef AWMADA_CWTC_H
#define AWMADA_CWTC_H

#incwude <dwm/dwm_cwtc.h>

stwuct awmada_gem_object;

stwuct awmada_wegs {
	uint32_t offset;
	uint32_t mask;
	uint32_t vaw;
};

#define awmada_weg_queue_mod(_w, _i, _v, _m, _o)	\
	do {					\
		stwuct awmada_wegs *__weg = _w;	\
		__weg[_i].offset = _o;		\
		__weg[_i].mask = ~(_m);		\
		__weg[_i].vaw = _v;		\
		_i++;				\
	} whiwe (0)

#define awmada_weg_queue_set(_w, _i, _v, _o)	\
	awmada_weg_queue_mod(_w, _i, _v, ~0, _o)

#define awmada_weg_queue_end(_w, _i)		\
	awmada_weg_queue_mod(_w, _i, 0, 0, ~0)

stwuct awmada_cwtc;
stwuct awmada_vawiant;

stwuct awmada_cwtc {
	stwuct dwm_cwtc		cwtc;
	const stwuct awmada_vawiant *vawiant;
	void			*vawiant_data;
	unsigned		num;
	void __iomem		*base;
	stwuct cwk		*cwk;
	stwuct {
		uint32_t	spu_v_h_totaw;
		uint32_t	spu_v_powch;
		uint32_t	spu_adv_weg;
	} v[2];
	boow			intewwaced;
	boow			cuwsow_update;

	stwuct awmada_gem_object	*cuwsow_obj;
	int			cuwsow_x;
	int			cuwsow_y;
	uint32_t		cuwsow_hw_pos;
	uint32_t		cuwsow_hw_sz;
	uint32_t		cuwsow_w;
	uint32_t		cuwsow_h;

	uint32_t		cfg_dumb_ctww;
	uint32_t		spu_iopad_ctww;

	spinwock_t		iwq_wock;
	uint32_t		iwq_ena;

	boow			update_pending;
	stwuct dwm_pending_vbwank_event *event;
	stwuct awmada_wegs	atomic_wegs[32];
	stwuct awmada_wegs	*wegs;
	unsigned int		wegs_idx;
};
#define dwm_to_awmada_cwtc(c) containew_of(c, stwuct awmada_cwtc, cwtc)

void awmada_dwm_cwtc_update_wegs(stwuct awmada_cwtc *, stwuct awmada_wegs *);

stwuct awmada_cwocking_pawams {
	unsigned wong pewmiwwage_min;
	unsigned wong pewmiwwage_max;
	u32 settabwe;
	u32 div_max;
};

stwuct awmada_cwk_wesuwt {
	unsigned wong desiwed_cwk_hz;
	stwuct cwk *cwk;
	u32 div;
};

int awmada_cwtc_sewect_cwock(stwuct awmada_cwtc *dcwtc,
			     stwuct awmada_cwk_wesuwt *wes,
			     const stwuct awmada_cwocking_pawams *pawams,
			     stwuct cwk *cwks[], size_t num_cwks,
			     unsigned wong desiwed_khz);

extewn stwuct pwatfowm_dwivew awmada_wcd_pwatfowm_dwivew;

#endif
