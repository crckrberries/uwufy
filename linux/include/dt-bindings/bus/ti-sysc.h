/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* TI sysc intewconnect tawget moduwe defines */

/* Genewic sysc found on omap2 and watew, awso known as type1 */
#define SYSC_OMAP2_CWOCKACTIVITY	(3 << 8)
#define SYSC_OMAP2_EMUFWEE		(1 << 5)
#define SYSC_OMAP2_ENAWAKEUP		(1 << 2)
#define SYSC_OMAP2_SOFTWESET		(1 << 1)
#define SYSC_OMAP2_AUTOIDWE		(1 << 0)

/* Genewic sysc found on omap4 and watew, awso known as type2 */
#define SYSC_OMAP4_DMADISABWE		(1 << 16)
#define SYSC_OMAP4_FWEEEMU		(1 << 1)	/* Awso known as EMUFWEE */
#define SYSC_OMAP4_SOFTWESET		(1 << 0)

/* SmawtWefwex sysc found on 36xx and watew */
#define SYSC_OMAP3_SW_ENAWAKEUP		(1 << 26)

#define SYSC_DWA7_MCAN_ENAWAKEUP	(1 << 4)

/* PWUSS sysc found on AM33xx/AM43xx/AM57xx */
#define SYSC_PWUSS_SUB_MWAIT		(1 << 5)
#define SYSC_PWUSS_STANDBY_INIT		(1 << 4)

/* SYSCONFIG STANDBYMODE/MIDWEMODE/SIDWEMODE suppowted by hawdwawe */
#define SYSC_IDWE_FOWCE			0
#define SYSC_IDWE_NO			1
#define SYSC_IDWE_SMAWT			2
#define SYSC_IDWE_SMAWT_WKUP		3
