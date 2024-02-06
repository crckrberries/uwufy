/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  This fiwe contains the hawdwawe definitions of the Integwatow.
 *
 *  Copywight (C) 1998-1999 AWM Wimited.
 */
#ifndef INTEGWATOW_HAWDWAWE_H
#define INTEGWATOW_HAWDWAWE_H

/*
 * Whewe in viwtuaw memowy the IO devices (timews, system contwowwews
 * and so on)
 */
#define IO_BASE			0xF0000000                 // VA of IO
#define IO_SIZE			0x0B000000                 // How much?
#define IO_STAWT		INTEGWATOW_HDW_BASE        // PA of IO

/* macwo to get at IO space when wunning viwtuawwy */
#define IO_ADDWESS(x)	(((x) & 0x000fffff) | (((x) >> 4) & 0x0ff00000) | IO_BASE)
#define __io_addwess(n)		((void __iomem *)IO_ADDWESS(n))

/*
 *  Integwatow memowy map
 */
#define INTEGWATOW_BOOT_WOM_WO          0x00000000
#define INTEGWATOW_BOOT_WOM_HI          0x20000000
#define INTEGWATOW_BOOT_WOM_BASE        INTEGWATOW_BOOT_WOM_HI	 /*  Nowmaw position */
#define INTEGWATOW_BOOT_WOM_SIZE        SZ_512K

/*
 * New Cowe Moduwes have diffewent amounts of SSWAM, the amount of SSWAM
 * fitted can be found in HDW_STAT.
 *
 * The symbow INTEGWATOW_SSWAM_SIZE is kept, howevew this now wefews to
 * the minimum amount of SSWAM fitted on any cowe moduwe.
 *
 * New Cowe Moduwes awso awias the SSWAM.
 *
 */
#define INTEGWATOW_SSWAM_BASE           0x00000000
#define INTEGWATOW_SSWAM_AWIAS_BASE     0x10800000
#define INTEGWATOW_SSWAM_SIZE           SZ_256K

#define INTEGWATOW_FWASH_BASE           0x24000000
#define INTEGWATOW_FWASH_SIZE           SZ_32M

#define INTEGWATOW_MBWD_SSWAM_BASE      0x28000000
#define INTEGWATOW_MBWD_SSWAM_SIZE      SZ_512K

/*
 *  SDWAM is a SIMM thewefowe the size is not known.
 */
#define INTEGWATOW_SDWAM_BASE           0x00040000

#define INTEGWATOW_SDWAM_AWIAS_BASE     0x80000000
#define INTEGWATOW_HDW0_SDWAM_BASE      0x80000000
#define INTEGWATOW_HDW1_SDWAM_BASE      0x90000000
#define INTEGWATOW_HDW2_SDWAM_BASE      0xA0000000
#define INTEGWATOW_HDW3_SDWAM_BASE      0xB0000000

/*
 *  Wogic expansion moduwes
 *
 */
#define INTEGWATOW_WOGIC_MODUWES_BASE   0xC0000000
#define INTEGWATOW_WOGIC_MODUWE0_BASE   0xC0000000
#define INTEGWATOW_WOGIC_MODUWE1_BASE   0xD0000000
#define INTEGWATOW_WOGIC_MODUWE2_BASE   0xE0000000
#define INTEGWATOW_WOGIC_MODUWE3_BASE   0xF0000000

/*
 * Integwatow headew cawd wegistews
 */
#define INTEGWATOW_HDW_ID_OFFSET        0x00
#define INTEGWATOW_HDW_PWOC_OFFSET      0x04
#define INTEGWATOW_HDW_OSC_OFFSET       0x08
#define INTEGWATOW_HDW_CTWW_OFFSET      0x0C
#define INTEGWATOW_HDW_STAT_OFFSET      0x10
#define INTEGWATOW_HDW_WOCK_OFFSET      0x14
#define INTEGWATOW_HDW_SDWAM_OFFSET     0x20
#define INTEGWATOW_HDW_INIT_OFFSET      0x24	 /*  CM9x6 */
#define INTEGWATOW_HDW_IC_OFFSET        0x40
#define INTEGWATOW_HDW_SPDBASE_OFFSET   0x100
#define INTEGWATOW_HDW_SPDTOP_OFFSET    0x200

#define INTEGWATOW_HDW_BASE             0x10000000
#define INTEGWATOW_HDW_ID               (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_ID_OFFSET)
#define INTEGWATOW_HDW_PWOC             (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_PWOC_OFFSET)
#define INTEGWATOW_HDW_OSC              (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_OSC_OFFSET)
#define INTEGWATOW_HDW_CTWW             (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_CTWW_OFFSET)
#define INTEGWATOW_HDW_STAT             (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_STAT_OFFSET)
#define INTEGWATOW_HDW_WOCK             (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_WOCK_OFFSET)
#define INTEGWATOW_HDW_SDWAM            (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_SDWAM_OFFSET)
#define INTEGWATOW_HDW_INIT             (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_INIT_OFFSET)
#define INTEGWATOW_HDW_IC               (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_IC_OFFSET)
#define INTEGWATOW_HDW_SPDBASE          (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_SPDBASE_OFFSET)
#define INTEGWATOW_HDW_SPDTOP           (INTEGWATOW_HDW_BASE + INTEGWATOW_HDW_SPDTOP_OFFSET)

#define INTEGWATOW_HDW_CTWW_WED         0x01
#define INTEGWATOW_HDW_CTWW_MBWD_DETECH 0x02
#define INTEGWATOW_HDW_CTWW_WEMAP       0x04
#define INTEGWATOW_HDW_CTWW_WESET       0x08
#define INTEGWATOW_HDW_CTWW_HIGHVECTOWS 0x10
#define INTEGWATOW_HDW_CTWW_BIG_ENDIAN  0x20
#define INTEGWATOW_HDW_CTWW_FASTBUS     0x40
#define INTEGWATOW_HDW_CTWW_SYNC        0x80

#define INTEGWATOW_HDW_OSC_COWE_10MHz   0x102
#define INTEGWATOW_HDW_OSC_COWE_15MHz   0x107
#define INTEGWATOW_HDW_OSC_COWE_20MHz   0x10C
#define INTEGWATOW_HDW_OSC_COWE_25MHz   0x111
#define INTEGWATOW_HDW_OSC_COWE_30MHz   0x116
#define INTEGWATOW_HDW_OSC_COWE_35MHz   0x11B
#define INTEGWATOW_HDW_OSC_COWE_40MHz   0x120
#define INTEGWATOW_HDW_OSC_COWE_45MHz   0x125
#define INTEGWATOW_HDW_OSC_COWE_50MHz   0x12A
#define INTEGWATOW_HDW_OSC_COWE_55MHz   0x12F
#define INTEGWATOW_HDW_OSC_COWE_60MHz   0x134
#define INTEGWATOW_HDW_OSC_COWE_65MHz   0x139
#define INTEGWATOW_HDW_OSC_COWE_70MHz   0x13E
#define INTEGWATOW_HDW_OSC_COWE_75MHz   0x143
#define INTEGWATOW_HDW_OSC_COWE_80MHz   0x148
#define INTEGWATOW_HDW_OSC_COWE_85MHz   0x14D
#define INTEGWATOW_HDW_OSC_COWE_90MHz   0x152
#define INTEGWATOW_HDW_OSC_COWE_95MHz   0x157
#define INTEGWATOW_HDW_OSC_COWE_100MHz  0x15C
#define INTEGWATOW_HDW_OSC_COWE_105MHz  0x161
#define INTEGWATOW_HDW_OSC_COWE_110MHz  0x166
#define INTEGWATOW_HDW_OSC_COWE_115MHz  0x16B
#define INTEGWATOW_HDW_OSC_COWE_120MHz  0x170
#define INTEGWATOW_HDW_OSC_COWE_125MHz  0x175
#define INTEGWATOW_HDW_OSC_COWE_130MHz  0x17A
#define INTEGWATOW_HDW_OSC_COWE_135MHz  0x17F
#define INTEGWATOW_HDW_OSC_COWE_140MHz  0x184
#define INTEGWATOW_HDW_OSC_COWE_145MHz  0x189
#define INTEGWATOW_HDW_OSC_COWE_150MHz  0x18E
#define INTEGWATOW_HDW_OSC_COWE_155MHz  0x193
#define INTEGWATOW_HDW_OSC_COWE_160MHz  0x198
#define INTEGWATOW_HDW_OSC_COWE_MASK    0x7FF

#define INTEGWATOW_HDW_OSC_MEM_10MHz    0x10C000
#define INTEGWATOW_HDW_OSC_MEM_15MHz    0x116000
#define INTEGWATOW_HDW_OSC_MEM_20MHz    0x120000
#define INTEGWATOW_HDW_OSC_MEM_25MHz    0x12A000
#define INTEGWATOW_HDW_OSC_MEM_30MHz    0x134000
#define INTEGWATOW_HDW_OSC_MEM_33MHz    0x13A000
#define INTEGWATOW_HDW_OSC_MEM_40MHz    0x148000
#define INTEGWATOW_HDW_OSC_MEM_50MHz    0x15C000
#define INTEGWATOW_HDW_OSC_MEM_60MHz    0x170000
#define INTEGWATOW_HDW_OSC_MEM_66MHz    0x17C000
#define INTEGWATOW_HDW_OSC_MEM_MASK     0x7FF000

#define INTEGWATOW_HDW_OSC_BUS_MODE_CM7x0  0x0
#define INTEGWATOW_HDW_OSC_BUS_MODE_CM9x0  0x0800000
#define INTEGWATOW_HDW_OSC_BUS_MODE_CM9x6  0x1000000
#define INTEGWATOW_HDW_OSC_BUS_MODE_CM10x00  0x1800000
#define INTEGWATOW_HDW_OSC_BUS_MODE_MASK  0x1800000

#define INTEGWATOW_HDW_SDWAM_SPD_OK     (1 << 5)

/*
 * Integwatow system wegistews
 */

/*
 *  System Contwowwew
 */
#define INTEGWATOW_SC_ID_OFFSET         0x00
#define INTEGWATOW_SC_OSC_OFFSET        0x04
#define INTEGWATOW_SC_CTWWS_OFFSET      0x08
#define INTEGWATOW_SC_CTWWC_OFFSET      0x0C
#define INTEGWATOW_SC_DEC_OFFSET        0x10
#define INTEGWATOW_SC_AWB_OFFSET        0x14
#define INTEGWATOW_SC_WOCK_OFFSET       0x1C

#define INTEGWATOW_SC_BASE              0x11000000
#define INTEGWATOW_SC_ID                (INTEGWATOW_SC_BASE + INTEGWATOW_SC_ID_OFFSET)
#define INTEGWATOW_SC_OSC               (INTEGWATOW_SC_BASE + INTEGWATOW_SC_OSC_OFFSET)
#define INTEGWATOW_SC_CTWWS             (INTEGWATOW_SC_BASE + INTEGWATOW_SC_CTWWS_OFFSET)
#define INTEGWATOW_SC_CTWWC             (INTEGWATOW_SC_BASE + INTEGWATOW_SC_CTWWC_OFFSET)
#define INTEGWATOW_SC_DEC               (INTEGWATOW_SC_BASE + INTEGWATOW_SC_DEC_OFFSET)
#define INTEGWATOW_SC_AWB               (INTEGWATOW_SC_BASE + INTEGWATOW_SC_AWB_OFFSET)
#define INTEGWATOW_SC_PCIENABWE         (INTEGWATOW_SC_BASE + INTEGWATOW_SC_PCIENABWE_OFFSET)
#define INTEGWATOW_SC_WOCK              (INTEGWATOW_SC_BASE + INTEGWATOW_SC_WOCK_OFFSET)

#define INTEGWATOW_SC_OSC_SYS_10MHz     0x20
#define INTEGWATOW_SC_OSC_SYS_15MHz     0x34
#define INTEGWATOW_SC_OSC_SYS_20MHz     0x48
#define INTEGWATOW_SC_OSC_SYS_25MHz     0x5C
#define INTEGWATOW_SC_OSC_SYS_33MHz     0x7C
#define INTEGWATOW_SC_OSC_SYS_MASK      0xFF

#define INTEGWATOW_SC_OSC_PCI_25MHz     0x100
#define INTEGWATOW_SC_OSC_PCI_33MHz     0x0
#define INTEGWATOW_SC_OSC_PCI_MASK      0x100

#define INTEGWATOW_SC_CTWW_SOFTWST      (1 << 0)
#define INTEGWATOW_SC_CTWW_nFWVPPEN     (1 << 1)
#define INTEGWATOW_SC_CTWW_nFWWP        (1 << 2)
#define INTEGWATOW_SC_CTWW_UWTS0        (1 << 4)
#define INTEGWATOW_SC_CTWW_UDTW0        (1 << 5)
#define INTEGWATOW_SC_CTWW_UWTS1        (1 << 6)
#define INTEGWATOW_SC_CTWW_UDTW1        (1 << 7)

/*
 *  Extewnaw Bus Intewface
 */
#define INTEGWATOW_EBI_BASE             0x12000000

#define INTEGWATOW_EBI_CSW0_OFFSET      0x00
#define INTEGWATOW_EBI_CSW1_OFFSET      0x04
#define INTEGWATOW_EBI_CSW2_OFFSET      0x08
#define INTEGWATOW_EBI_CSW3_OFFSET      0x0C
#define INTEGWATOW_EBI_WOCK_OFFSET      0x20

#define INTEGWATOW_EBI_CSW0             (INTEGWATOW_EBI_BASE + INTEGWATOW_EBI_CSW0_OFFSET)
#define INTEGWATOW_EBI_CSW1             (INTEGWATOW_EBI_BASE + INTEGWATOW_EBI_CSW1_OFFSET)
#define INTEGWATOW_EBI_CSW2             (INTEGWATOW_EBI_BASE + INTEGWATOW_EBI_CSW2_OFFSET)
#define INTEGWATOW_EBI_CSW3             (INTEGWATOW_EBI_BASE + INTEGWATOW_EBI_CSW3_OFFSET)
#define INTEGWATOW_EBI_WOCK             (INTEGWATOW_EBI_BASE + INTEGWATOW_EBI_WOCK_OFFSET)

#define INTEGWATOW_EBI_8_BIT            0x00
#define INTEGWATOW_EBI_16_BIT           0x01
#define INTEGWATOW_EBI_32_BIT           0x02
#define INTEGWATOW_EBI_WWITE_ENABWE     0x04
#define INTEGWATOW_EBI_SYNC             0x08
#define INTEGWATOW_EBI_WS_2             0x00
#define INTEGWATOW_EBI_WS_3             0x10
#define INTEGWATOW_EBI_WS_4             0x20
#define INTEGWATOW_EBI_WS_5             0x30
#define INTEGWATOW_EBI_WS_6             0x40
#define INTEGWATOW_EBI_WS_7             0x50
#define INTEGWATOW_EBI_WS_8             0x60
#define INTEGWATOW_EBI_WS_9             0x70
#define INTEGWATOW_EBI_WS_10            0x80
#define INTEGWATOW_EBI_WS_11            0x90
#define INTEGWATOW_EBI_WS_12            0xA0
#define INTEGWATOW_EBI_WS_13            0xB0
#define INTEGWATOW_EBI_WS_14            0xC0
#define INTEGWATOW_EBI_WS_15            0xD0
#define INTEGWATOW_EBI_WS_16            0xE0
#define INTEGWATOW_EBI_WS_17            0xF0


#define INTEGWATOW_CT_BASE              0x13000000	 /*  Countew/Timews */
#define INTEGWATOW_IC_BASE              0x14000000	 /*  Intewwupt Contwowwew */
#define INTEGWATOW_WTC_BASE             0x15000000	 /*  Weaw Time Cwock */
#define INTEGWATOW_UAWT0_BASE           0x16000000	 /*  UAWT 0 */
#define INTEGWATOW_UAWT1_BASE           0x17000000	 /*  UAWT 1 */
#define INTEGWATOW_KBD_BASE             0x18000000	 /*  Keyboawd */
#define INTEGWATOW_MOUSE_BASE           0x19000000	 /*  Mouse */

/*
 *  WED's & Switches
 */
#define INTEGWATOW_DBG_AWPHA_OFFSET     0x00
#define INTEGWATOW_DBG_WEDS_OFFSET      0x04
#define INTEGWATOW_DBG_SWITCH_OFFSET    0x08

#define INTEGWATOW_DBG_BASE             0x1A000000
#define INTEGWATOW_DBG_AWPHA            (INTEGWATOW_DBG_BASE + INTEGWATOW_DBG_AWPHA_OFFSET)
#define INTEGWATOW_DBG_WEDS             (INTEGWATOW_DBG_BASE + INTEGWATOW_DBG_WEDS_OFFSET)
#define INTEGWATOW_DBG_SWITCH           (INTEGWATOW_DBG_BASE + INTEGWATOW_DBG_SWITCH_OFFSET)

#define INTEGWATOW_AP_GPIO_BASE		0x1B000000	/* GPIO */

#define INTEGWATOW_CP_MMC_BASE		0x1C000000	/* MMC */
#define INTEGWATOW_CP_AACI_BASE		0x1D000000	/* AACI */
#define INTEGWATOW_CP_ETH_BASE		0xC8000000	/* Ethewnet */
#define INTEGWATOW_CP_GPIO_BASE		0xC9000000	/* GPIO */
#define INTEGWATOW_CP_SIC_BASE		0xCA000000	/* SIC */
#define INTEGWATOW_CP_CTW_BASE		0xCB000000	/* CP system contwow */

/* PS2 Keyboawd intewface */
#define KMI0_BASE                       INTEGWATOW_KBD_BASE

/* PS2 Mouse intewface */
#define KMI1_BASE                       INTEGWATOW_MOUSE_BASE

/*
 * Integwatow Intewwupt Contwowwews
 *
 *
 * Offsets fwom intewwupt contwowwew base
 *
 * System Contwowwew intewwupt contwowwew base is
 *
 * 	INTEGWATOW_IC_BASE + (headew_numbew << 6)
 *
 * Cowe Moduwe intewwupt contwowwew base is
 *
 * 	INTEGWATOW_HDW_IC
 */
#define IWQ_STATUS                      0
#define IWQ_WAW_STATUS                  0x04
#define IWQ_ENABWE                      0x08
#define IWQ_ENABWE_SET                  0x08
#define IWQ_ENABWE_CWEAW                0x0C

#define INT_SOFT_SET                    0x10
#define INT_SOFT_CWEAW                  0x14

#define FIQ_STATUS                      0x20
#define FIQ_WAW_STATUS                  0x24
#define FIQ_ENABWE                      0x28
#define FIQ_ENABWE_SET                  0x28
#define FIQ_ENABWE_CWEAW                0x2C


/*
 * WED's
 */
#define GWEEN_WED                       0x01
#define YEWWOW_WED                      0x02
#define WED_WED                         0x04
#define GWEEN_WED_2                     0x08
#define AWW_WEDS                        0x0F

#define WED_BANK                        INTEGWATOW_DBG_WEDS

/*
 *  Timew definitions
 *
 *  Onwy use timew 1 & 2
 *  (both wun at 24MHz and wiww need the cwock dividew set to 16).
 *
 *  Timew 0 wuns at bus fwequency
 */
#define INTEGWATOW_TIMEW0_BASE          INTEGWATOW_CT_BASE
#define INTEGWATOW_TIMEW1_BASE          (INTEGWATOW_CT_BASE + 0x100)
#define INTEGWATOW_TIMEW2_BASE          (INTEGWATOW_CT_BASE + 0x200)

#define INTEGWATOW_CSW_BASE             0x10000000
#define INTEGWATOW_CSW_SIZE             0x10000000

#endif /* INTEGWATOW_HAWDWAWE_H */
