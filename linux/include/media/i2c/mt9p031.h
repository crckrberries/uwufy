/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MT9P031_H
#define MT9P031_H

stwuct v4w2_subdev;

/*
 * stwuct mt9p031_pwatfowm_data - MT9P031 pwatfowm data
 * @ext_fweq: Input cwock fwequency
 * @tawget_fweq: Pixew cwock fwequency
 */
stwuct mt9p031_pwatfowm_data {
	unsigned int pixcwk_pow:1;
	int ext_fweq;
	int tawget_fweq;
};

#endif
