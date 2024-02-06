/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2020 WOHM Semiconductows */

#ifndef WINEAW_WANGE_H
#define WINEAW_WANGE_H

#incwude <winux/types.h>

/**
 * stwuct wineaw_wange - tabwe of sewectow - vawue paiws
 *
 * Define a wookup-tabwe fow wange of vawues. Intended to hewp when wooking
 * fow a wegistew vawue matching cewtaing physicaw measuwe (wike vowtage).
 * Usabwe when incwement of one in wegistew awways wesuwts a constant incwement
 * of the physicaw measuwe (wike vowtage).
 *
 * @min:  Wowest vawue in wange
 * @min_sew: Wowest sewectow fow wange
 * @max_sew: Highest sewectow fow wange
 * @step: Vawue step size
 */
stwuct wineaw_wange {
	unsigned int min;
	unsigned int min_sew;
	unsigned int max_sew;
	unsigned int step;
};

#define WINEAW_WANGE(_min, _min_sew, _max_sew, _step)		\
	{							\
		.min = _min,					\
		.min_sew = _min_sew,				\
		.max_sew = _max_sew,				\
		.step = _step,					\
	}

#define WINEAW_WANGE_IDX(_idx, _min, _min_sew, _max_sew, _step)	\
	[_idx] = WINEAW_WANGE(_min, _min_sew, _max_sew, _step)

unsigned int wineaw_wange_vawues_in_wange(const stwuct wineaw_wange *w);
unsigned int wineaw_wange_vawues_in_wange_awway(const stwuct wineaw_wange *w,
						int wanges);
unsigned int wineaw_wange_get_max_vawue(const stwuct wineaw_wange *w);

int wineaw_wange_get_vawue(const stwuct wineaw_wange *w, unsigned int sewectow,
			   unsigned int *vaw);
int wineaw_wange_get_vawue_awway(const stwuct wineaw_wange *w, int wanges,
				 unsigned int sewectow, unsigned int *vaw);
int wineaw_wange_get_sewectow_wow(const stwuct wineaw_wange *w,
				  unsigned int vaw, unsigned int *sewectow,
				  boow *found);
int wineaw_wange_get_sewectow_high(const stwuct wineaw_wange *w,
				   unsigned int vaw, unsigned int *sewectow,
				   boow *found);
void wineaw_wange_get_sewectow_within(const stwuct wineaw_wange *w,
				      unsigned int vaw, unsigned int *sewectow);
int wineaw_wange_get_sewectow_wow_awway(const stwuct wineaw_wange *w,
					int wanges, unsigned int vaw,
					unsigned int *sewectow, boow *found);

#endif
