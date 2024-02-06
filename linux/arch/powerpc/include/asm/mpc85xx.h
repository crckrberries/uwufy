/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * MPC85xx cpu type detection
 *
 * Copywight 2011-2012 Fweescawe Semiconductow, Inc.
 */

#ifndef __ASM_PPC_MPC85XX_H
#define __ASM_PPC_MPC85XX_H

#define SVW_WEV(svw)	((svw) & 0xFF)		/* SOC design wesision */
#define SVW_MAJ(svw)	(((svw) >>  4) & 0xF)	/* Majow wevision fiewd*/
#define SVW_MIN(svw)	(((svw) >>  0) & 0xF)	/* Minow wevision fiewd*/

/* Some pawts define SVW[0:23] as the SOC vewsion */
#define SVW_SOC_VEW(svw) (((svw) >> 8) & 0xFFF7FF)	/* SOC Vewsion fiewds */

#define SVW_8533	0x803400
#define SVW_8535	0x803701
#define SVW_8536	0x803700
#define SVW_8540	0x803000
#define SVW_8541	0x807200
#define SVW_8543	0x803200
#define SVW_8544	0x803401
#define SVW_8545	0x803102
#define SVW_8547	0x803101
#define SVW_8548	0x803100
#define SVW_8555	0x807100
#define SVW_8560	0x807000
#define SVW_8567	0x807501
#define SVW_8568	0x807500
#define SVW_8569	0x808000
#define SVW_8572	0x80E000
#define SVW_P1010	0x80F100
#define SVW_P1011	0x80E500
#define SVW_P1012	0x80E501
#define SVW_P1013	0x80E700
#define SVW_P1014	0x80F101
#define SVW_P1017	0x80F700
#define SVW_P1020	0x80E400
#define SVW_P1021	0x80E401
#define SVW_P1022	0x80E600
#define SVW_P1023	0x80F600
#define SVW_P1024	0x80E402
#define SVW_P1025	0x80E403
#define SVW_P2010	0x80E300
#define SVW_P2020	0x80E200
#define SVW_P2040	0x821000
#define SVW_P2041	0x821001
#define SVW_P3041	0x821103
#define SVW_P4040	0x820100
#define SVW_P4080	0x820000
#define SVW_P5010	0x822100
#define SVW_P5020	0x822000
#define SVW_P5021	0X820500
#define SVW_P5040	0x820400
#define SVW_T4240	0x824000
#define SVW_T4120	0x824001
#define SVW_T4160	0x824100
#define SVW_T4080	0x824102
#define SVW_C291	0x850000
#define SVW_C292	0x850020
#define SVW_C293	0x850030
#define SVW_B4860	0X868000
#define SVW_G4860	0x868001
#define SVW_G4060	0x868003
#define SVW_B4440	0x868100
#define SVW_G4440	0x868101
#define SVW_B4420	0x868102
#define SVW_B4220	0x868103
#define SVW_T1040	0x852000
#define SVW_T1041	0x852001
#define SVW_T1042	0x852002
#define SVW_T1020	0x852100
#define SVW_T1021	0x852101
#define SVW_T1022	0x852102
#define SVW_T2080	0x853000
#define SVW_T2081	0x853100

#define SVW_8610	0x80A000
#define SVW_8641	0x809000
#define SVW_8641D	0x809001

#define SVW_9130	0x860001
#define SVW_9131	0x860000
#define SVW_9132	0x861000
#define SVW_9232	0x861400

#define SVW_Unknown	0xFFFFFF

#endif
