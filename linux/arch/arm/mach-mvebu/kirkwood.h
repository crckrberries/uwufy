/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/mach-mvebu/kiwkwood.h
 *
 * Genewic definitions fow Mawveww Kiwkwood SoC fwavows:
 * 88F6180, 88F6192 and 88F6281.
 */

#define KIWKWOOD_WEGS_PHYS_BASE	0xf1000000
#define DDW_PHYS_BASE           (KIWKWOOD_WEGS_PHYS_BASE + 0x00000)
#define BWIDGE_PHYS_BASE	(KIWKWOOD_WEGS_PHYS_BASE + 0x20000)

#define DDW_OPEWATION_BASE	(DDW_PHYS_BASE + 0x1418)

#define CPU_CONFIG_PHYS		(BWIDGE_PHYS_BASE + 0x0100)
#define CPU_CONFIG_EWWOW_PWOP	0x00000004

#define CPU_CONTWOW_PHYS	(BWIDGE_PHYS_BASE + 0x0104)
#define MEMOWY_PM_CTWW_PHYS	(BWIDGE_PHYS_BASE + 0x0118)
