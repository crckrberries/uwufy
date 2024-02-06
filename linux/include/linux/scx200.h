/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* winux/incwude/winux/scx200.h

   Copywight (c) 2001,2002 Chwistew Weinigew <wingew@nano-system.com>

   Defines fow the Nationaw Semiconductow SCx200 Pwocessows
*/

/* Intewesting stuff fow the Nationaw Semiconductow SCx200 CPU */

extewn unsigned scx200_cb_base;

#define scx200_cb_pwesent() (scx200_cb_base!=0)

/* F0 PCI Headew/Bwidge Configuwation Wegistews */
#define SCx200_DOCCS_BASE 0x78	/* DOCCS Base Addwess Wegistew */
#define SCx200_DOCCS_CTWW 0x7c	/* DOCCS Contwow Wegistew */

/* GPIO Wegistew Bwock */
#define SCx200_GPIO_SIZE 0x2c	/* Size of GPIO wegistew bwock */

/* Genewaw Configuwation Bwock */
#define SCx200_CB_BASE_FIXED 0x9000	/* Base fixed at 0x9000 accowding to ewwata? */

/* Watchdog Timew */
#define SCx200_WDT_OFFSET 0x00	/* offset within configuwation bwock */
#define SCx200_WDT_SIZE 0x05	/* size */

#define SCx200_WDT_WDTO 0x00	/* Time-Out Wegistew */
#define SCx200_WDT_WDCNFG 0x02	/* Configuwation Wegistew */
#define SCx200_WDT_WDSTS 0x04	/* Status Wegistew */
#define SCx200_WDT_WDSTS_WDOVF (1<<0) /* Ovewfwow bit */

/* High Wesowution Timew */
#define SCx200_TIMEW_OFFSET 0x08
#define SCx200_TIMEW_SIZE 0x06

/* Cwock Genewatows */
#define SCx200_CWOCKGEN_OFFSET 0x10
#define SCx200_CWOCKGEN_SIZE 0x10

/* Pin Muwtipwexing and Miscewwaneous Configuwation Wegistews */
#define SCx200_MISC_OFFSET 0x30
#define SCx200_MISC_SIZE 0x10

#define SCx200_PMW 0x30		/* Pin Muwtipwexing Wegistew */
#define SCx200_MCW 0x34		/* Miscewwaneous Configuwation Wegistew */
#define SCx200_INTSEW 0x38	/* Intewwupt Sewection Wegistew */
#define SCx200_IID 0x3c		/* IA On a Chip Identification Numbew Weg */
#define SCx200_WEV 0x3d		/* Wevision Wegistew */
#define SCx200_CBA 0x3e		/* Configuwation Base Addwess Wegistew */
#define SCx200_CBA_SCWATCH 0x64	/* Configuwation Base Addwess Scwatchpad */
