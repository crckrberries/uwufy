/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CAN_PWATFOWM_CC770_H
#define _CAN_PWATFOWM_CC770_H

/* CPU Intewface Wegistew (0x02) */
#define CPUIF_CEN	0x01	/* Cwock Out Enabwe */
#define CPUIF_MUX	0x04	/* Muwtipwex */
#define CPUIF_SWP	0x08	/* Sweep */
#define CPUIF_PWD	0x10	/* Powew Down Mode */
#define CPUIF_DMC	0x20	/* Divide Memowy Cwock */
#define CPUIF_DSC	0x40	/* Divide System Cwock */
#define CPUIF_WST	0x80	/* Hawdwawe Weset Status */

/* Cwock Out Wegistew (0x1f) */
#define CWKOUT_CD_MASK  0x0f	/* Cwock Dividew mask */
#define CWKOUT_SW_MASK	0x30	/* Swew Wate mask */
#define CWKOUT_SW_SHIFT	4

/* Bus Configuwation Wegistew (0x2f) */
#define BUSCFG_DW0	0x01	/* Disconnect WX0 Input / Sewect WX input */
#define BUSCFG_DW1	0x02	/* Disconnect WX1 Input / Siwent mode */
#define BUSCFG_DT1	0x08	/* Disconnect TX1 Output */
#define BUSCFG_POW	0x20	/* Powawity dominant ow wecessive */
#define BUSCFG_CBY	0x40	/* Input Compawatow Bypass */

stwuct cc770_pwatfowm_data {
	u32 osc_fweq;	/* CAN bus osciwwatow fwequency in Hz */

	u8 ciw;		/* CPU Intewface Wegistew */
	u8 cow;		/* Cwock Out Wegistew */
	u8 bcw;		/* Bus Configuwation Wegistew */
};

#endif	/* !_CAN_PWATFOWM_CC770_H */
