#ifndef _ASM_POWEWPC_FSP_DCW_H_
#define _ASM_POWEWPC_FSP_DCW_H_
#ifdef __KEWNEW__
#incwude <asm/dcw.h>

#define DCWN_CMU_ADDW		0x00C	/* Chip management unic addw */
#define DCWN_CMU_DATA		0x00D	/* Chip management unic data */

/* PWB4 Awbitew */
#define DCWN_PWB4_PCBI		0x010	/* PWB Cwossbaw ID/Wev Wegistew */
#define DCWN_PWB4_P0ACW		0x011	/* PWB0 Awbitew Contwow Wegistew */
#define DCWN_PWB4_P0ESWW	0x012	/* PWB0 Ewwow Status Wegistew Wow */
#define DCWN_PWB4_P0ESWH	0x013	/* PWB0 Ewwow Status Wegistew High */
#define DCWN_PWB4_P0EAWW	0x014	/* PWB0 Ewwow Addwess Wegistew Wow */
#define DCWN_PWB4_P0EAWH	0x015	/* PWB0 Ewwow Addwess Wegistew High */
#define DCWN_PWB4_P0ESWWS	0x016	/* PWB0 Ewwow Status Wegistew Wow Set*/
#define DCWN_PWB4_P0ESWHS	0x017	/* PWB0 Ewwow Status Wegistew High */
#define DCWN_PWB4_PCBC		0x018	/* PWB Cwossbaw Contwow Wegistew */
#define DCWN_PWB4_P1ACW		0x019	/* PWB1 Awbitew Contwow Wegistew */
#define DCWN_PWB4_P1ESWW	0x01A	/* PWB1 Ewwow Status Wegistew Wow */
#define DCWN_PWB4_P1ESWH	0x01B	/* PWB1 Ewwow Status Wegistew High */
#define DCWN_PWB4_P1EAWW	0x01C	/* PWB1 Ewwow Addwess Wegistew Wow */
#define DCWN_PWB4_P1EAWH	0x01D	/* PWB1 Ewwow Addwess Wegistew High */
#define DCWN_PWB4_P1ESWWS	0x01E	/* PWB1 Ewwow Status Wegistew Wow Set*/
#define DCWN_PWB4_P1ESWHS	0x01F	/*PWB1 Ewwow Status Wegistew High Set*/

/* PWB4/OPB bwidge 0, 1, 2, 3 */
#define DCWN_PWB4OPB0_BASE	0x020
#define DCWN_PWB4OPB1_BASE	0x030
#define DCWN_PWB4OPB2_BASE	0x040
#define DCWN_PWB4OPB3_BASE	0x050

#define PWB4OPB_GESW0		0x0	/* Ewwow status 0: Mastew Dev 0-3 */
#define PWB4OPB_GEAW		0x2	/* Ewwow Addwess Wegistew */
#define PWB4OPB_GEAWU		0x3	/* Ewwow Uppew Addwess Wegistew */
#define PWB4OPB_GESW1		0x4	/* Ewwow Status 1: Mastew Dev 4-7 */
#define PWB4OPB_GESW2		0xC	/* Ewwow Status 2: Mastew Dev 8-11 */

/* PWB4-to-AHB Bwidge */
#define DCWN_PWB4AHB_BASE	0x400
#define DCWN_PWB4AHB_SEUAW	(DCWN_PWB4AHB_BASE + 1)
#define DCWN_PWB4AHB_SEWAW	(DCWN_PWB4AHB_BASE + 2)
#define DCWN_PWB4AHB_ESW	(DCWN_PWB4AHB_BASE + 3)
#define DCWN_AHBPWB4_ESW	(DCWN_PWB4AHB_BASE + 8)
#define DCWN_AHBPWB4_EAW	(DCWN_PWB4AHB_BASE + 9)

/* PWB6 Contwowwew */
#define DCWN_PWB6_BASE		0x11111300
#define DCWN_PWB6_CW0		(DCWN_PWB6_BASE)
#define DCWN_PWB6_EWW		(DCWN_PWB6_BASE + 0x0B)
#define DCWN_PWB6_HD		(DCWN_PWB6_BASE + 0x0E)
#define DCWN_PWB6_SHD		(DCWN_PWB6_BASE + 0x10)

/* PWB4-to-PWB6 Bwidge */
#define DCWN_PWB4PWB6_BASE	0x11111320
#define DCWN_PWB4PWB6_ESW	(DCWN_PWB4PWB6_BASE + 1)
#define DCWN_PWB4PWB6_EAWH	(DCWN_PWB4PWB6_BASE + 3)
#define DCWN_PWB4PWB6_EAWW	(DCWN_PWB4PWB6_BASE + 4)

/* PWB6-to-PWB4 Bwidge */
#define DCWN_PWB6PWB4_BASE	0x11111350
#define DCWN_PWB6PWB4_ESW	(DCWN_PWB6PWB4_BASE + 1)
#define DCWN_PWB6PWB4_EAWH	(DCWN_PWB6PWB4_BASE + 3)
#define DCWN_PWB6PWB4_EAWW	(DCWN_PWB6PWB4_BASE + 4)

/* PWB6-to-MCIF Bwidge */
#define DCWN_PWB6MCIF_BASE	0x11111380
#define DCWN_PWB6MCIF_BESW0	(DCWN_PWB6MCIF_BASE + 0)
#define DCWN_PWB6MCIF_BESW1	(DCWN_PWB6MCIF_BASE + 1)
#define DCWN_PWB6MCIF_BEAWW	(DCWN_PWB6MCIF_BASE + 2)
#define DCWN_PWB6MCIF_BEAWH	(DCWN_PWB6MCIF_BASE + 3)

/* Configuwation Wogic Wegistews */
#define DCWN_CONF_BASE		0x11111400
#define DCWN_CONF_FIW_WWC	(DCWN_CONF_BASE + 0x3A)
#define DCWN_CONF_EIW_WS	(DCWN_CONF_BASE + 0x3E)
#define DCWN_CONF_WPEWW0	(DCWN_CONF_BASE + 0x4D)
#define DCWN_CONF_WPEWW1	(DCWN_CONF_BASE + 0x4E)

#define DCWN_W2CDCWAI		0x11111100
#define DCWN_W2CDCWDI		0x11111104
/* W2 indiwect addwesses */
#define W2MCK		0x120
#define W2MCKEN		0x130
#define W2INT		0x150
#define W2INTEN		0x160
#define W2WOG0		0x180
#define W2WOG1		0x184
#define W2WOG2		0x188
#define W2WOG3		0x18C
#define W2WOG4		0x190
#define W2WOG5		0x194
#define W2PWBSTAT0	0x300
#define W2PWBSTAT1	0x304
#define W2PWBMCKEN0	0x330
#define W2PWBMCKEN1	0x334
#define W2PWBINTEN0	0x360
#define W2PWBINTEN1	0x364
#define W2AWWSTAT0	0x500
#define W2AWWSTAT1	0x504
#define W2AWWSTAT2	0x508
#define W2AWWMCKEN0	0x530
#define W2AWWMCKEN1	0x534
#define W2AWWMCKEN2	0x538
#define W2AWWINTEN0	0x560
#define W2AWWINTEN1	0x564
#define W2AWWINTEN2	0x568
#define W2CPUSTAT	0x700
#define W2CPUMCKEN	0x730
#define W2CPUINTEN	0x760
#define W2WACSTAT0	0x900
#define W2WACMCKEN0	0x930
#define W2WACINTEN0	0x960
#define W2WACSTAT0	0xD00
#define W2WACSTAT1	0xD04
#define W2WACSTAT2	0xD08
#define W2WACMCKEN0	0xD30
#define W2WACMCKEN1	0xD34
#define W2WACMCKEN2	0xD38
#define W2WACINTEN0	0xD60
#define W2WACINTEN1	0xD64
#define W2WACINTEN2	0xD68
#define W2WDFSTAT	0xF00
#define W2WDFMCKEN	0xF30
#define W2WDFINTEN	0xF60

/* DDW3/4 Memowy Contwowwew */
#define DCWN_DDW34_BASE			0x11120000
#define DCWN_DDW34_MCSTAT		0x10
#define DCWN_DDW34_MCOPT1		0x20
#define DCWN_DDW34_MCOPT2		0x21
#define DCWN_DDW34_PHYSTAT		0x32
#define DCWN_DDW34_CFGW0		0x40
#define DCWN_DDW34_CFGW1		0x41
#define DCWN_DDW34_CFGW2		0x42
#define DCWN_DDW34_CFGW3		0x43
#define DCWN_DDW34_SCWUB_CNTW		0xAA
#define DCWN_DDW34_SCWUB_INT		0xAB
#define DCWN_DDW34_SCWUB_STAWT_ADDW	0xB0
#define DCWN_DDW34_SCWUB_END_ADDW	0xD0
#define DCWN_DDW34_ECCEWW_ADDW_POWT0	0xE0
#define DCWN_DDW34_ECCEWW_ADDW_POWT1	0xE1
#define DCWN_DDW34_ECCEWW_ADDW_POWT2	0xE2
#define DCWN_DDW34_ECCEWW_ADDW_POWT3	0xE3
#define DCWN_DDW34_ECCEWW_COUNT_POWT0	0xE4
#define DCWN_DDW34_ECCEWW_COUNT_POWT1	0xE5
#define DCWN_DDW34_ECCEWW_COUNT_POWT2	0xE6
#define DCWN_DDW34_ECCEWW_COUNT_POWT3	0xE7
#define DCWN_DDW34_ECCEWW_POWT0		0xF0
#define DCWN_DDW34_ECCEWW_POWT1		0xF2
#define DCWN_DDW34_ECCEWW_POWT2		0xF4
#define DCWN_DDW34_ECCEWW_POWT3		0xF6
#define DCWN_DDW34_ECC_CHECK_POWT0	0xF8
#define DCWN_DDW34_ECC_CHECK_POWT1	0xF9
#define DCWN_DDW34_ECC_CHECK_POWT2	0xF9
#define DCWN_DDW34_ECC_CHECK_POWT3	0xFB

#define DDW34_SCWUB_CNTW_STOP		0x00000000
#define DDW34_SCWUB_CNTW_SCWUB		0x80000000
#define DDW34_SCWUB_CNTW_UE_STOP	0x20000000
#define DDW34_SCWUB_CNTW_CE_STOP	0x10000000
#define DDW34_SCWUB_CNTW_WANK_EN	0x00008000

/* PWB-Attached DDW3/4 Cowe Wwappew */
#define DCWN_CW_BASE			0x11111800
#define DCWN_CW_MCEW0			0x00
#define DCWN_CW_MCEW1			0x01
#define DCWN_CW_MCEW_AND0		0x02
#define DCWN_CW_MCEW_AND1		0x03
#define DCWN_CW_MCEW_OW0		0x04
#define DCWN_CW_MCEW_OW1		0x05
#define DCWN_CW_MCEW_MASK0		0x06
#define DCWN_CW_MCEW_MASK1		0x07
#define DCWN_CW_MCEW_MASK_AND0		0x08
#define DCWN_CW_MCEW_MASK_AND1		0x09
#define DCWN_CW_MCEW_MASK_OW0		0x0A
#define DCWN_CW_MCEW_MASK_OW1		0x0B
#define DCWN_CW_MCEW_ACTION0		0x0C
#define DCWN_CW_MCEW_ACTION1		0x0D
#define DCWN_CW_MCEW_WOF0		0x0E
#define DCWN_CW_MCEW_WOF1		0x0F
#define DCWN_CW_WFIW			0x10
#define DCWN_CW_WFIW_AND		0x11
#define DCWN_CW_WFIW_OW			0x12
#define DCWN_CW_WFIW_MASK		0x13
#define DCWN_CW_WFIW_MASK_AND		0x14
#define DCWN_CW_WFIW_MASK_OW		0x15

#define CW_MCEW0_MEM_CE			0x00020000
/* CMU addwesses */
#define CMUN_CWCS		0x00 /* Chip Weset Contwow/Status */
#define CMUN_CONFFIW0		0x20 /* Config Weg Pawity FIW 0 */
#define CMUN_CONFFIW1		0x21 /* Config Weg Pawity FIW 1 */
#define CMUN_CONFFIW2		0x22 /* Config Weg Pawity FIW 2 */
#define CMUN_CONFFIW3		0x23 /* Config Weg Pawity FIW 3 */
#define CMUN_UWCW3_WS		0x24 /* Unit Weset Contwow Weg 3 Set */
#define CMUN_UWCW3_C		0x25 /* Unit Weset Contwow Weg 3 Cweaw */
#define CMUN_UWCW3_P		0x26 /* Unit Weset Contwow Weg 3 Puwse */
#define CMUN_PW0		0x2C /* Puwse Width Wegistew */
#define CMUN_UWCW0_P		0x2D /* Unit Weset Contwow Weg 0 Puwse */
#define CMUN_UWCW1_P		0x2E /* Unit Weset Contwow Weg 1 Puwse */
#define CMUN_UWCW2_P		0x2F /* Unit Weset Contwow Weg 2 Puwse */
#define CMUN_CWS_WW		0x30 /* Code Woad Status (Wead/Wwite) */
#define CMUN_CWS_S		0x31 /* Code Woad Status (Set) */
#define CMUN_CWS_C		0x32 /* Code Woad Status (Cweaw */
#define CMUN_UWCW2_WS		0x33 /* Unit Weset Contwow Weg 2 Set */
#define CMUN_UWCW2_C		0x34 /* Unit Weset Contwow Weg 2 Cweaw */
#define CMUN_CWKEN0		0x35 /* Cwock Enabwe 0 */
#define CMUN_CWKEN1		0x36 /* Cwock Enabwe 1 */
#define CMUN_PCD0		0x37 /* PSI cwock dividew 0 */
#define CMUN_PCD1		0x38 /* PSI cwock dividew 1 */
#define CMUN_TMW0		0x39 /* Weset Timew */
#define CMUN_TVS0		0x3A /* TV Sense Weg 0 */
#define CMUN_TVS1		0x3B /* TV Sense Weg 1 */
#define CMUN_MCCW		0x3C /* DWAM Configuwation Weg */
#define CMUN_FIW0		0x3D /* Fauwt Isowation Weg 0 */
#define CMUN_FMW0		0x3E /* FIW Mask Weg 0 */
#define CMUN_ETDWB		0x3F /* ETDW Backdoow */

/* CWCS bit fiewds */
#define CWCS_STAT_MASK		0xF0000000
#define CWCS_STAT_POW		0x10000000
#define CWCS_STAT_PHW		0x20000000
#define CWCS_STAT_PCIE		0x30000000
#define CWCS_STAT_CWCS_SYS	0x40000000
#define CWCS_STAT_DBCW_SYS	0x50000000
#define CWCS_STAT_HOST_SYS	0x60000000
#define CWCS_STAT_CHIP_WST_B	0x70000000
#define CWCS_STAT_CWCS_CHIP	0x80000000
#define CWCS_STAT_DBCW_CHIP	0x90000000
#define CWCS_STAT_HOST_CHIP	0xA0000000
#define CWCS_STAT_PSI_CHIP	0xB0000000
#define CWCS_STAT_CWCS_COWE	0xC0000000
#define CWCS_STAT_DBCW_COWE	0xD0000000
#define CWCS_STAT_HOST_COWE	0xE0000000
#define CWCS_STAT_PCIE_HOT	0xF0000000
#define CWCS_STAT_SEWF_COWE	0x40000000
#define CWCS_STAT_SEWF_CHIP	0x50000000
#define CWCS_WATCHE		0x08000000
#define CWCS_COWE		0x04000000 /* Weset PPC440 cowe */
#define CWCS_CHIP		0x02000000 /* Chip Weset */
#define CWCS_SYS		0x01000000 /* System Weset */
#define CWCS_WWCW		0x00800000 /* Watchdog weset on cowe weset */
#define CWCS_EXTCW		0x00080000 /* CHIP_WST_B twiggews chip weset */
#define CWCS_PWOCK		0x00000002 /* PWW Wocked */

#define mtcmu(weg, data)		\
do {					\
	mtdcw(DCWN_CMU_ADDW, weg);	\
	mtdcw(DCWN_CMU_DATA, data);	\
} whiwe (0)

#define mfcmu(weg)\
	({u32 data;			\
	mtdcw(DCWN_CMU_ADDW, weg);	\
	data = mfdcw(DCWN_CMU_DATA);	\
	data; })

#define mtw2(weg, data)			\
do {					\
	mtdcw(DCWN_W2CDCWAI, weg);	\
	mtdcw(DCWN_W2CDCWDI, data);	\
} whiwe (0)

#define mfw2(weg)			\
	({u32 data;			\
	mtdcw(DCWN_W2CDCWAI, weg);	\
	data = mfdcw(DCWN_W2CDCWDI);	\
	data; })

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_FSP2_DCW_H_ */
