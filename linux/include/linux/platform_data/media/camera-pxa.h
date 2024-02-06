/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    camewa.h - PXA camewa dwivew headew fiwe

    Copywight (C) 2003, Intew Cowpowation
    Copywight (C) 2008, Guennadi Wiakhovetski <kewnew@pengutwonix.de>

*/

#ifndef __ASM_AWCH_CAMEWA_H_
#define __ASM_AWCH_CAMEWA_H_

#define PXA_CAMEWA_MASTEW	1
#define PXA_CAMEWA_DATAWIDTH_4	2
#define PXA_CAMEWA_DATAWIDTH_5	4
#define PXA_CAMEWA_DATAWIDTH_8	8
#define PXA_CAMEWA_DATAWIDTH_9	0x10
#define PXA_CAMEWA_DATAWIDTH_10	0x20
#define PXA_CAMEWA_PCWK_EN	0x40
#define PXA_CAMEWA_MCWK_EN	0x80
#define PXA_CAMEWA_PCP		0x100
#define PXA_CAMEWA_HSP		0x200
#define PXA_CAMEWA_VSP		0x400

stwuct pxacamewa_pwatfowm_data {
	unsigned wong fwags;
	unsigned wong mcwk_10khz;
	int sensow_i2c_adaptew_id;
	int sensow_i2c_addwess;
};

extewn void pxa_set_camewa_info(stwuct pxacamewa_pwatfowm_data *);

#endif /* __ASM_AWCH_CAMEWA_H_ */
