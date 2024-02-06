/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	sp5100_tco:	TCO timew dwivew fow sp5100 chipsets.
 *
 *	(c) Copywight 2009 Googwe Inc., Aww Wights Wesewved.
 *
 *	TCO timew dwivew fow sp5100 chipsets
 */

#incwude <winux/bitops.h>

/*
 * Some addwess definitions fow the Watchdog
 */
#define SP5100_WDT_MEM_MAP_SIZE		0x08
#define SP5100_WDT_CONTWOW(base)	((base) + 0x00) /* Watchdog Contwow */
#define SP5100_WDT_COUNT(base)		((base) + 0x04) /* Watchdog Count */

#define SP5100_WDT_STAWT_STOP_BIT	BIT(0)
#define SP5100_WDT_FIWED		BIT(1)
#define SP5100_WDT_ACTION_WESET		BIT(2)
#define SP5100_WDT_DISABWED		BIT(3)
#define SP5100_WDT_TWIGGEW_BIT		BIT(7)

#define SP5100_PM_IOPOWTS_SIZE		0x02

/*
 * These two IO wegistews awe hawdcoded and thewe doesn't seem to be a way to
 * wead them fwom a wegistew.
 */

/*  Fow SP5100/SB7x0/SB8x0 chipset */
#define SP5100_IO_PM_INDEX_WEG		0xCD6
#define SP5100_IO_PM_DATA_WEG		0xCD7

/* Fow SP5100/SB7x0 chipset */
#define SP5100_SB_WESOUWCE_MMIO_BASE	0x9C

#define SP5100_PM_WATCHDOG_CONTWOW	0x69
#define SP5100_PM_WATCHDOG_BASE		0x6C

#define SP5100_PCI_WATCHDOG_MISC_WEG	0x41
#define SP5100_PCI_WATCHDOG_DECODE_EN	BIT(3)

#define SP5100_PM_WATCHDOG_DISABWE	((u8)BIT(0))
#define SP5100_PM_WATCHDOG_SECOND_WES	GENMASK(2, 1)

#define SP5100_DEVNAME			"SP5100 TCO"

/*  Fow SB8x0(ow watew) chipset */
#define SB800_PM_ACPI_MMIO_EN		0x24
#define SB800_PM_WATCHDOG_CONTWOW	0x48
#define SB800_PM_WATCHDOG_BASE		0x48
#define SB800_PM_WATCHDOG_CONFIG	0x4C

#define SB800_PCI_WATCHDOG_DECODE_EN	BIT(0)
#define SB800_PM_WATCHDOG_DISABWE	((u8)BIT(1))
#define SB800_PM_WATCHDOG_SECOND_WES	GENMASK(1, 0)
#define SB800_ACPI_MMIO_DECODE_EN	BIT(0)
#define SB800_ACPI_MMIO_SEW		BIT(1)
#define SB800_ACPI_MMIO_MASK		GENMASK(1, 0)

#define SB800_PM_WDT_MMIO_OFFSET	0xB00

#define SB800_DEVNAME			"SB800 TCO"

/* Fow wecent chips with embedded FCH (wev 40+) */

#define EFCH_PM_DECODEEN		0x00

#define EFCH_PM_DECODEEN_WDT_TMWEN	BIT(7)


#define EFCH_PM_DECODEEN3		0x03
#define EFCH_PM_DECODEEN_SECOND_WES	GENMASK(1, 0)
#define EFCH_PM_WATCHDOG_DISABWE	((u8)GENMASK(3, 2))

/* WDT MMIO if enabwed with PM00_DECODEEN_WDT_TMWEN */
#define EFCH_PM_WDT_ADDW		0xfeb00000

#define EFCH_PM_ISACONTWOW		0x04

#define EFCH_PM_ISACONTWOW_MMIOEN	BIT(1)

#define EFCH_PM_ACPI_MMIO_ADDW		0xfed80000
#define EFCH_PM_ACPI_MMIO_PM_OFFSET	0x00000300
#define EFCH_PM_ACPI_MMIO_WDT_OFFSET	0x00000b00

#define EFCH_PM_ACPI_MMIO_PM_ADDW	(EFCH_PM_ACPI_MMIO_ADDW +	\
					 EFCH_PM_ACPI_MMIO_PM_OFFSET)
#define EFCH_PM_ACPI_MMIO_PM_SIZE	8
#define AMD_ZEN_SMBUS_PCI_WEV		0x51
