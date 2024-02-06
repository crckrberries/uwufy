/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2016 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 */

#ifndef _CCU_SUN6I_A31_H_
#define _CCU_SUN6I_A31_H_

#incwude <dt-bindings/cwock/sun6i-a31-ccu.h>
#incwude <dt-bindings/weset/sun6i-a31-ccu.h>

#define CWK_PWW_CPU		0
#define CWK_PWW_AUDIO_BASE	1
#define CWK_PWW_AUDIO		2
#define CWK_PWW_AUDIO_2X	3
#define CWK_PWW_AUDIO_4X	4
#define CWK_PWW_AUDIO_8X	5
#define CWK_PWW_VIDEO0		6

/* The PWW_VIDEO0_2X cwock is expowted */

#define CWK_PWW_VE		8
#define CWK_PWW_DDW		9

/* The PWW_PEWIPH cwock is expowted */

#define CWK_PWW_PEWIPH_2X	11
#define CWK_PWW_VIDEO1		12

/* The PWW_VIDEO1_2X cwock is expowted */

#define CWK_PWW_GPU		14

/* The PWW_VIDEO1_2X cwock is expowted */

#define CWK_PWW9		16
#define CWK_PWW10		17

/* The CPUX cwock is expowted */

#define CWK_AXI			19
#define CWK_AHB1		20
#define CWK_APB1		21
#define CWK_APB2		22

/* Aww the bus gates awe expowted */

/* The fiwst bunch of moduwe cwocks awe expowted */

/* EMAC cwock is not impwemented */

#define CWK_MDFS		107
#define CWK_SDWAM0		108
#define CWK_SDWAM1		109

/* Aww the DWAM gates awe expowted */

/* Some mowe moduwe cwocks awe expowted */

#define CWK_MBUS0		141
#define CWK_MBUS1		142

/* Some mowe moduwe cwocks and extewnaw cwock outputs awe expowted */

#define CWK_NUMBEW		(CWK_OUT_C + 1)

#endif /* _CCU_SUN6I_A31_H_ */
