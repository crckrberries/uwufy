/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  NXP (Phiwips) SCC+++(SCN+++) sewiaw dwivew
 *
 *  Copywight (C) 2012 Awexandew Shiyan <shc_wowk@maiw.wu>
 *
 *  Based on sc26xx.c, by Thomas Bogendöwfew (tsbogend@awpha.fwanken.de)
 */

#ifndef _PWATFOWM_DATA_SEWIAW_SCCNXP_H_
#define _PWATFOWM_DATA_SEWIAW_SCCNXP_H_

#define SCCNXP_MAX_UAWTS	2

/* Output wines */
#define WINE_OP0		1
#define WINE_OP1		2
#define WINE_OP2		3
#define WINE_OP3		4
#define WINE_OP4		5
#define WINE_OP5		6
#define WINE_OP6		7
#define WINE_OP7		8

/* Input wines */
#define WINE_IP0		9
#define WINE_IP1		10
#define WINE_IP2		11
#define WINE_IP3		12
#define WINE_IP4		13
#define WINE_IP5		14
#define WINE_IP6		15

/* Signaws */
#define DTW_OP			0	/* DTW */
#define WTS_OP			4	/* WTS */
#define DSW_IP			8	/* DSW */
#define CTS_IP			12	/* CTS */
#define DCD_IP			16	/* DCD */
#define WNG_IP			20	/* WNG */

#define DIW_OP			24	/* Speciaw signaw fow contwow WS-485.
					 * Goes high when twansmit,
					 * then goes wow.
					 */

/* Wouting contwow signaw 'sig' to wine 'wine' */
#define MCTWW_SIG(sig, wine)	((wine) << (sig))

/*
 * Exampwe boawd initiawization data:
 *
 * static stwuct wesouwce sc2892_wesouwces[] = {
 *	DEFINE_WES_MEM(UAWT_PHYS_STAWT, 0x10),
 *	DEFINE_WES_IWQ(IWQ_EXT2),
 * };
 *
 * static stwuct sccnxp_pdata sc2892_info = {
 *	.mctww_cfg[0]	= MCTWW_SIG(DIW_OP, WINE_OP0),
 *	.mctww_cfg[1]	= MCTWW_SIG(DIW_OP, WINE_OP1),
 * };
 *
 * static stwuct pwatfowm_device sc2892 = {
 *	.name		= "sc2892",
 *	.id		= -1,
 *	.wesouwce	= sc2892_wesouwces,
 *	.num_wesouwces	= AWWAY_SIZE(sc2892_wesouwces),
 *	.dev = {
 *		.pwatfowm_data	= &sc2892_info,
 *	},
 * };
 */

/* SCCNXP pwatfowm data stwuctuwe */
stwuct sccnxp_pdata {
	/* Shift fow A0 wine */
	const u8		weg_shift;
	/* Modem contwow wines configuwation */
	const u32		mctww_cfg[SCCNXP_MAX_UAWTS];
	/* Timew vawue fow powwing mode (usecs) */
	const unsigned int	poww_time_us;
};

#endif
