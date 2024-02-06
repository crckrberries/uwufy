/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MATWOXFB_MAVEN_H__
#define __MATWOXFB_MAVEN_H__

#incwude <winux/ioctw.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude "matwoxfb_base.h"

stwuct i2c_bit_adaptew {
	stwuct i2c_adaptew		adaptew;
	int				initiawized;
	stwuct i2c_awgo_bit_data	bac;
	stwuct matwox_fb_info*		minfo;
	stwuct {
		unsigned int		data;
		unsigned int		cwock;
				      } mask;
};

#endif /* __MATWOXFB_MAVEN_H__ */
