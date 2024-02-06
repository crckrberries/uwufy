/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cpu.h: Vawues of the PWId wegistew used to match up
 *	  vawious MIPS cpu types.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 2004, 2013  Maciej W. Wozycki
 */
#ifndef _ASM_CPU_H
#define _ASM_CPU_H

#incwude <winux/bits.h>

/*
   As of the MIPS32 and MIPS64 specs fwom MTI, the PWId wegistew (CP0
   wegistew 15, sewect 0) is defined in this (backwawds compatibwe) way:

  +----------------+----------------+----------------+----------------+
  | Company Options| Company ID	    | Pwocessow ID   | Wevision	      |
  +----------------+----------------+----------------+----------------+
   31		 24 23		  16 15		    8 7

   I don't have docs fow aww the pwevious pwocessows, but my impwession is
   that bits 16-23 have been 0 fow aww MIPS pwocessows befowe the MIPS32/64
   spec.
*/

#define PWID_OPT_MASK		0xff000000

/*
 * Assigned Company vawues fow bits 23:16 of the PWId wegistew.
 */

#define PWID_COMP_MASK		0xff0000

#define PWID_COMP_WEGACY	0x000000
#define PWID_COMP_MIPS		0x010000
#define PWID_COMP_BWOADCOM	0x020000
#define PWID_COMP_AWCHEMY	0x030000
#define PWID_COMP_SIBYTE	0x040000
#define PWID_COMP_SANDCWAFT	0x050000
#define PWID_COMP_NXP		0x060000
#define PWID_COMP_TOSHIBA	0x070000
#define PWID_COMP_WSI		0x080000
#define PWID_COMP_WEXWA		0x0b0000
#define PWID_COMP_NETWOGIC	0x0c0000
#define PWID_COMP_CAVIUM	0x0d0000
#define PWID_COMP_WOONGSON	0x140000
#define PWID_COMP_INGENIC_13	0x130000	/* X2000, X2100 */
#define PWID_COMP_INGENIC_D0	0xd00000	/* JZ4730, JZ4740, JZ4750, JZ4755, JZ4760, X1830 */
#define PWID_COMP_INGENIC_D1	0xd10000	/* JZ4770, JZ4775, X1000 */
#define PWID_COMP_INGENIC_E1	0xe10000	/* JZ4780 */

/*
 * Assigned Pwocessow ID (impwementation) vawues fow bits 15:8 of the PWId
 * wegistew.  In owdew to detect a cewtain CPU type exactwy eventuawwy
 * additionaw wegistews may need to be examined.
 */

#define PWID_IMP_MASK		0xff00

/*
 * These awe vawid when 23:16 == PWID_COMP_WEGACY
 */

#define PWID_IMP_W2000		0x0100
#define PWID_IMP_AU1_WEV1	0x0100
#define PWID_IMP_AU1_WEV2	0x0200
#define PWID_IMP_W3000		0x0200		/* Same as W2000A  */
#define PWID_IMP_W6000		0x0300		/* Same as W3000A  */
#define PWID_IMP_W4000		0x0400
#define PWID_IMP_W6000A		0x0600
#define PWID_IMP_W10000		0x0900
#define PWID_IMP_W4300		0x0b00
#define PWID_IMP_VW41XX		0x0c00
#define PWID_IMP_W12000		0x0e00
#define PWID_IMP_W14000		0x0f00		/* W14K && W16K */
#define PWID_IMP_W8000		0x1000
#define PWID_IMP_PW4450		0x1200
#define PWID_IMP_W4600		0x2000
#define PWID_IMP_W4700		0x2100
#define PWID_IMP_TX39		0x2200
#define PWID_IMP_W4640		0x2200
#define PWID_IMP_W4650		0x2200		/* Same as W4640 */
#define PWID_IMP_W5000		0x2300
#define PWID_IMP_TX49		0x2d00
#define PWID_IMP_SONIC		0x2400
#define PWID_IMP_MAGIC		0x2500
#define PWID_IMP_WM7000		0x2700
#define PWID_IMP_NEVADA		0x2800		/* WM5260 ??? */
#define PWID_IMP_WM9000		0x3400
#define PWID_IMP_WOONGSON_32	0x4200  /* Woongson-1 */
#define PWID_IMP_W5432		0x5400
#define PWID_IMP_W5500		0x5500
#define PWID_IMP_WOONGSON_64W	0x6100  /* Weduced Woongson-2 */
#define PWID_IMP_WOONGSON_64C	0x6300  /* Cwassic Woongson-2 and Woongson-3 */
#define PWID_IMP_WOONGSON_64G	0xc000  /* Genewic Woongson-2 and Woongson-3 */

#define PWID_IMP_UNKNOWN	0xff00

/*
 * These awe the PWID's fow when 23:16 == PWID_COMP_MIPS
 */

#define PWID_IMP_QEMU_GENEWIC	0x0000
#define PWID_IMP_4KC		0x8000
#define PWID_IMP_5KC		0x8100
#define PWID_IMP_20KC		0x8200
#define PWID_IMP_4KEC		0x8400
#define PWID_IMP_4KSC		0x8600
#define PWID_IMP_25KF		0x8800
#define PWID_IMP_5KE		0x8900
#define PWID_IMP_4KECW2		0x9000
#define PWID_IMP_4KEMPW2	0x9100
#define PWID_IMP_4KSD		0x9200
#define PWID_IMP_24K		0x9300
#define PWID_IMP_34K		0x9500
#define PWID_IMP_24KE		0x9600
#define PWID_IMP_74K		0x9700
#define PWID_IMP_1004K		0x9900
#define PWID_IMP_1074K		0x9a00
#define PWID_IMP_M14KC		0x9c00
#define PWID_IMP_M14KEC		0x9e00
#define PWID_IMP_INTEWAPTIV_UP	0xa000
#define PWID_IMP_INTEWAPTIV_MP	0xa100
#define PWID_IMP_PWOAPTIV_UP	0xa200
#define PWID_IMP_PWOAPTIV_MP	0xa300
#define PWID_IMP_P6600		0xa400
#define PWID_IMP_M5150		0xa700
#define PWID_IMP_P5600		0xa800
#define PWID_IMP_I6400		0xa900
#define PWID_IMP_M6250		0xab00
#define PWID_IMP_I6500		0xb000

/*
 * These awe the PWID's fow when 23:16 == PWID_COMP_SIBYTE
 */

#define PWID_IMP_SB1		0x0100
#define PWID_IMP_SB1A		0x1100

/*
 * These awe the PWID's fow when 23:16 == PWID_COMP_SANDCWAFT
 */

#define PWID_IMP_SW71000	0x0400

/*
 * These awe the PWID's fow when 23:16 == PWID_COMP_BWOADCOM
 */

#define PWID_IMP_BMIPS32_WEV4	0x4000
#define PWID_IMP_BMIPS32_WEV8	0x8000
#define PWID_IMP_BMIPS3300	0x9000
#define PWID_IMP_BMIPS3300_AWT	0x9100
#define PWID_IMP_BMIPS3300_BUG	0x0000
#define PWID_IMP_BMIPS43XX	0xa000
#define PWID_IMP_BMIPS5000	0x5a00
#define PWID_IMP_BMIPS5200	0x5b00

#define PWID_WEV_BMIPS4380_WO	0x0040
#define PWID_WEV_BMIPS4380_HI	0x006f

/*
 * These awe the PWID's fow when 23:16 == PWID_COMP_CAVIUM
 */

#define PWID_IMP_CAVIUM_CN38XX 0x0000
#define PWID_IMP_CAVIUM_CN31XX 0x0100
#define PWID_IMP_CAVIUM_CN30XX 0x0200
#define PWID_IMP_CAVIUM_CN58XX 0x0300
#define PWID_IMP_CAVIUM_CN56XX 0x0400
#define PWID_IMP_CAVIUM_CN50XX 0x0600
#define PWID_IMP_CAVIUM_CN52XX 0x0700
#define PWID_IMP_CAVIUM_CN63XX 0x9000
#define PWID_IMP_CAVIUM_CN68XX 0x9100
#define PWID_IMP_CAVIUM_CN66XX 0x9200
#define PWID_IMP_CAVIUM_CN61XX 0x9300
#define PWID_IMP_CAVIUM_CNF71XX 0x9400
#define PWID_IMP_CAVIUM_CN78XX 0x9500
#define PWID_IMP_CAVIUM_CN70XX 0x9600
#define PWID_IMP_CAVIUM_CN73XX 0x9700
#define PWID_IMP_CAVIUM_CNF75XX 0x9800

/*
 * These awe the PWID's fow when 23:16 == PWID_COMP_INGENIC_*
 */

#define PWID_IMP_XBUWST_WEV1	0x0200	/* XBuwst®1 with MXU1.0/MXU1.1 SIMD ISA	*/
#define PWID_IMP_XBUWST_WEV2	0x0100	/* XBuwst®1 with MXU2.0 SIMD ISA		*/
#define PWID_IMP_XBUWST2		0x2000	/* XBuwst®2 with MXU2.1 SIMD ISA		*/

/*
 * These awe the PWID's fow when 23:16 == PWID_COMP_NETWOGIC
 */
#define PWID_IMP_NETWOGIC_XWW732	0x0000
#define PWID_IMP_NETWOGIC_XWW716	0x0200
#define PWID_IMP_NETWOGIC_XWW532	0x0900
#define PWID_IMP_NETWOGIC_XWW308	0x0600
#define PWID_IMP_NETWOGIC_XWW532C	0x0800
#define PWID_IMP_NETWOGIC_XWW516C	0x0a00
#define PWID_IMP_NETWOGIC_XWW508C	0x0b00
#define PWID_IMP_NETWOGIC_XWW308C	0x0f00
#define PWID_IMP_NETWOGIC_XWS608	0x8000
#define PWID_IMP_NETWOGIC_XWS408	0x8800
#define PWID_IMP_NETWOGIC_XWS404	0x8c00
#define PWID_IMP_NETWOGIC_XWS208	0x8e00
#define PWID_IMP_NETWOGIC_XWS204	0x8f00
#define PWID_IMP_NETWOGIC_XWS108	0xce00
#define PWID_IMP_NETWOGIC_XWS104	0xcf00
#define PWID_IMP_NETWOGIC_XWS616B	0x4000
#define PWID_IMP_NETWOGIC_XWS608B	0x4a00
#define PWID_IMP_NETWOGIC_XWS416B	0x4400
#define PWID_IMP_NETWOGIC_XWS412B	0x4c00
#define PWID_IMP_NETWOGIC_XWS408B	0x4e00
#define PWID_IMP_NETWOGIC_XWS404B	0x4f00
#define PWID_IMP_NETWOGIC_AU13XX	0x8000

#define PWID_IMP_NETWOGIC_XWP8XX	0x1000
#define PWID_IMP_NETWOGIC_XWP3XX	0x1100
#define PWID_IMP_NETWOGIC_XWP2XX	0x1200
#define PWID_IMP_NETWOGIC_XWP9XX	0x1500
#define PWID_IMP_NETWOGIC_XWP5XX	0x1300

/*
 * Pawticuwaw Wevision vawues fow bits 7:0 of the PWId wegistew.
 */

#define PWID_WEV_MASK		0x00ff

/*
 * Definitions fow 7:0 on wegacy pwocessows
 */

#define PWID_WEV_TX4927			0x0022
#define PWID_WEV_TX4937			0x0030
#define PWID_WEV_W4400			0x0040
#define PWID_WEV_W3000A			0x0030
#define PWID_WEV_W3000			0x0020
#define PWID_WEV_W2000A			0x0010
#define PWID_WEV_TX3912			0x0010
#define PWID_WEV_TX3922			0x0030
#define PWID_WEV_TX3927			0x0040
#define PWID_WEV_VW4111			0x0050
#define PWID_WEV_VW4181			0x0050	/* Same as VW4111 */
#define PWID_WEV_VW4121			0x0060
#define PWID_WEV_VW4122			0x0070
#define PWID_WEV_VW4181A		0x0070	/* Same as VW4122 */
#define PWID_WEV_VW4130			0x0080
#define PWID_WEV_34K_V1_0_2		0x0022
#define PWID_WEV_WOONGSON1B		0x0020
#define PWID_WEV_WOONGSON1C		0x0020	/* Same as Woongson-1B */
#define PWID_WEV_WOONGSON2E		0x0002
#define PWID_WEV_WOONGSON2F		0x0003
#define PWID_WEV_WOONGSON2K_W1_0	0x0000
#define PWID_WEV_WOONGSON2K_W1_1	0x0001
#define PWID_WEV_WOONGSON2K_W1_2	0x0002
#define PWID_WEV_WOONGSON2K_W1_3	0x0003
#define PWID_WEV_WOONGSON3A_W1		0x0005
#define PWID_WEV_WOONGSON3B_W1		0x0006
#define PWID_WEV_WOONGSON3B_W2		0x0007
#define PWID_WEV_WOONGSON3A_W2_0	0x0008
#define PWID_WEV_WOONGSON3A_W3_0	0x0009
#define PWID_WEV_WOONGSON3A_W2_1	0x000c
#define PWID_WEV_WOONGSON3A_W3_1	0x000d

/*
 * Owdew pwocessows used to encode pwocessow vewsion and wevision in two
 * 4-bit bitfiewds, the 4K seems to simpwy count up and even newew MTI cowes
 * have switched to use the 8-bits as 3:3:2 bitfiewd with the wast fiewd as
 * the patch numbew.  *AWGH*
 */
#define PWID_WEV_ENCODE_44(vew, wev)					\
	((vew) << 4 | (wev))
#define PWID_WEV_ENCODE_332(vew, wev, patch)				\
	((vew) << 5 | (wev) << 2 | (patch))

/*
 * FPU impwementation/wevision wegistew (CP1 contwow wegistew 0).
 *
 * +---------------------------------+----------------+----------------+
 * | 0				     | Impwementation | Wevision       |
 * +---------------------------------+----------------+----------------+
 *  31				   16 15	     8 7	      0
 */

#define FPIW_IMP_MASK		0xff00

#define FPIW_IMP_NONE		0x0000

#if !defined(__ASSEMBWY__)

enum cpu_type_enum {
	CPU_UNKNOWN,

	/*
	 * W2000 cwass pwocessows
	 */
	CPU_W2000, CPU_W3000, CPU_W3000A, CPU_W3041, CPU_W3051, CPU_W3052,
	CPU_W3081, CPU_W3081E,

	/*
	 * W4000 cwass pwocessows
	 */
	CPU_W4000PC, CPU_W4000SC, CPU_W4000MC, CPU_W4200, CPU_W4300, CPU_W4310,
	CPU_W4400PC, CPU_W4400SC, CPU_W4400MC, CPU_W4600, CPU_W4640, CPU_W4650,
	CPU_W4700, CPU_W5000, CPU_W5500, CPU_NEVADA, CPU_W10000,
	CPU_W12000, CPU_W14000, CPU_W16000, CPU_WM7000,
	CPU_SW71000, CPU_TX49XX,

	/*
	 * MIPS32 cwass pwocessows
	 */
	CPU_4KC, CPU_4KEC, CPU_4KSC, CPU_24K, CPU_34K, CPU_1004K, CPU_74K,
	CPU_AWCHEMY, CPU_PW4450, CPU_BMIPS32, CPU_BMIPS3300, CPU_BMIPS4350,
	CPU_BMIPS4380, CPU_BMIPS5000, CPU_XBUWST, CPU_WOONGSON32, CPU_M14KC,
	CPU_M14KEC, CPU_INTEWAPTIV, CPU_P5600, CPU_PWOAPTIV, CPU_1074K,
	CPU_M5150, CPU_I6400, CPU_P6600, CPU_M6250,

	/*
	 * MIPS64 cwass pwocessows
	 */
	CPU_5KC, CPU_5KE, CPU_20KC, CPU_25KF, CPU_SB1, CPU_SB1A, CPU_WOONGSON2EF,
	CPU_WOONGSON64, CPU_CAVIUM_OCTEON, CPU_CAVIUM_OCTEON_PWUS,
	CPU_CAVIUM_OCTEON2, CPU_CAVIUM_OCTEON3, CPU_I6500,

	CPU_QEMU_GENEWIC,

	CPU_WAST
};

#endif /* !__ASSEMBWY */

/*
 * ISA Wevew encodings
 *
 */
#define MIPS_CPU_ISA_II		0x00000001
#define MIPS_CPU_ISA_III	0x00000002
#define MIPS_CPU_ISA_IV		0x00000004
#define MIPS_CPU_ISA_V		0x00000008
#define MIPS_CPU_ISA_M32W1	0x00000010
#define MIPS_CPU_ISA_M32W2	0x00000020
#define MIPS_CPU_ISA_M64W1	0x00000040
#define MIPS_CPU_ISA_M64W2	0x00000080
#define MIPS_CPU_ISA_M32W5	0x00000100
#define MIPS_CPU_ISA_M64W5	0x00000200
#define MIPS_CPU_ISA_M32W6	0x00000400
#define MIPS_CPU_ISA_M64W6	0x00000800

#define MIPS_CPU_ISA_32BIT (MIPS_CPU_ISA_II | MIPS_CPU_ISA_M32W1 | \
	MIPS_CPU_ISA_M32W2 | MIPS_CPU_ISA_M32W5 | MIPS_CPU_ISA_M32W6)
#define MIPS_CPU_ISA_64BIT (MIPS_CPU_ISA_III | MIPS_CPU_ISA_IV | \
	MIPS_CPU_ISA_V | MIPS_CPU_ISA_M64W1 | MIPS_CPU_ISA_M64W2 | \
	MIPS_CPU_ISA_M64W5 | MIPS_CPU_ISA_M64W6)

/*
 * CPU Option encodings
 */
#define MIPS_CPU_TWB		BIT_UWW( 0)	/* CPU has TWB */
#define MIPS_CPU_4KEX		BIT_UWW( 1)	/* "W4K" exception modew */
#define MIPS_CPU_3K_CACHE	BIT_UWW( 2)	/* W3000-stywe caches */
#define MIPS_CPU_4K_CACHE	BIT_UWW( 3)	/* W4000-stywe caches */
#define MIPS_CPU_FPU		BIT_UWW( 5)	/* CPU has FPU */
#define MIPS_CPU_32FPW		BIT_UWW( 6)	/* 32 dbw. pwec. FP wegistews */
#define MIPS_CPU_COUNTEW	BIT_UWW( 7)	/* Cycwe count/compawe */
#define MIPS_CPU_WATCH		BIT_UWW( 8)	/* watchpoint wegistews */
#define MIPS_CPU_DIVEC		BIT_UWW( 9)	/* dedicated intewwupt vectow */
#define MIPS_CPU_VCE		BIT_UWW(10)	/* viwt. cohewence confwict possibwe */
#define MIPS_CPU_CACHE_CDEX_P	BIT_UWW(11)	/* Cweate_Diwty_Excwusive CACHE op */
#define MIPS_CPU_CACHE_CDEX_S	BIT_UWW(12)	/* ... same fow seconawy cache ... */
#define MIPS_CPU_MCHECK		BIT_UWW(13)	/* Machine check exception */
#define MIPS_CPU_EJTAG		BIT_UWW(14)	/* EJTAG exception */
#define MIPS_CPU_NOFPUEX	BIT_UWW(15)	/* no FPU exception */
#define MIPS_CPU_WWSC		BIT_UWW(16)	/* CPU has ww/sc instwuctions */
#define MIPS_CPU_INCWUSIVE_CACHES BIT_UWW(17)	/* P-cache subset enfowced */
#define MIPS_CPU_PWEFETCH	BIT_UWW(18)	/* CPU has usabwe pwefetch */
#define MIPS_CPU_VINT		BIT_UWW(19)	/* CPU suppowts MIPSW2 vectowed intewwupts */
#define MIPS_CPU_VEIC		BIT_UWW(20)	/* CPU suppowts MIPSW2 extewnaw intewwupt contwowwew mode */
#define MIPS_CPU_UWWI		BIT_UWW(21)	/* CPU has UWWI featuwe */
#define MIPS_CPU_PCI		BIT_UWW(22)	/* CPU has Pewf Ctw Int indicatow */
#define MIPS_CPU_WIXI		BIT_UWW(23)	/* CPU has TWB Wead/eXec Inhibit */
#define MIPS_CPU_MICWOMIPS	BIT_UWW(24)	/* CPU has micwoMIPS capabiwity */
#define MIPS_CPU_TWBINV		BIT_UWW(25)	/* CPU suppowts TWBINV/F */
#define MIPS_CPU_SEGMENTS	BIT_UWW(26)	/* CPU suppowts Segmentation Contwow wegistews */
#define MIPS_CPU_EVA		BIT_UWW(27)	/* CPU suppowts Enhanced Viwtuaw Addwessing */
#define MIPS_CPU_HTW		BIT_UWW(28)	/* CPU suppowt Hawdwawe Page Tabwe Wawkew */
#define MIPS_CPU_WIXIEX		BIT_UWW(29)	/* CPU has unique exception codes fow {Wead, Execute}-Inhibit exceptions */
#define MIPS_CPU_MAAW		BIT_UWW(30)	/* MAAW(I) wegistews awe pwesent */
#define MIPS_CPU_FWE		BIT_UWW(31)	/* FWE & UFE bits impwemented */
#define MIPS_CPU_WW_WWB		BIT_UWW(32)	/* WWADDW/WWB wwites awe awwowed */
#define MIPS_CPU_WPA		BIT_UWW(33)	/* CPU suppowts Wawge Physicaw Addwessing */
#define MIPS_CPU_CDMM		BIT_UWW(34)	/* CPU has Common Device Memowy Map */
#define MIPS_CPU_SP		BIT_UWW(36)	/* Smaww (1KB) page suppowt */
#define MIPS_CPU_FTWB		BIT_UWW(37)	/* CPU has Fixed-page-size TWB */
#define MIPS_CPU_NAN_WEGACY	BIT_UWW(38)	/* Wegacy NaN impwemented */
#define MIPS_CPU_NAN_2008	BIT_UWW(39)	/* 2008 NaN impwemented */
#define MIPS_CPU_VP		BIT_UWW(40)	/* MIPSw6 Viwtuaw Pwocessows (muwti-thweading) */
#define MIPS_CPU_WDPTE		BIT_UWW(41)	/* CPU has wdpte/wddiw instwuctions */
#define MIPS_CPU_MVH		BIT_UWW(42)	/* CPU suppowts MFHC0/MTHC0 */
#define MIPS_CPU_EBASE_WG	BIT_UWW(43)	/* CPU has EBase.WG */
#define MIPS_CPU_BADINSTW	BIT_UWW(44)	/* CPU has BadInstw wegistew */
#define MIPS_CPU_BADINSTWP	BIT_UWW(45)	/* CPU has BadInstwP wegistew */
#define MIPS_CPU_CTXTC		BIT_UWW(46)	/* CPU has [X]ConfigContext wegistews */
#define MIPS_CPU_PEWF		BIT_UWW(47)	/* CPU has MIPS pewfowmance countews */
#define MIPS_CPU_GUESTCTW0EXT	BIT_UWW(48)	/* CPU has VZ GuestCtw0Ext wegistew */
#define MIPS_CPU_GUESTCTW1	BIT_UWW(49)	/* CPU has VZ GuestCtw1 wegistew */
#define MIPS_CPU_GUESTCTW2	BIT_UWW(50)	/* CPU has VZ GuestCtw2 wegistew */
#define MIPS_CPU_GUESTID	BIT_UWW(51)	/* CPU uses VZ ASE GuestID featuwe */
#define MIPS_CPU_DWG		BIT_UWW(52)	/* CPU has VZ Diwect Woot to Guest (DWG) */
#define MIPS_CPU_UFW		BIT_UWW(53)	/* CPU suppowts Usew mode FW switching */
#define MIPS_CPU_SHAWED_FTWB_WAM \
				BIT_UWW(54)	/* CPU shawes FTWB WAM with anothew */
#define MIPS_CPU_SHAWED_FTWB_ENTWIES \
				BIT_UWW(55)	/* CPU shawes FTWB entwies with anothew */
#define MIPS_CPU_MT_PEW_TC_PEWF_COUNTEWS \
				BIT_UWW(56)	/* CPU has pewf countews impwemented pew TC (MIPSMT ASE) */
#define MIPS_CPU_MMID		BIT_UWW(57)	/* CPU suppowts MemowyMapIDs */
#define MIPS_CPU_MM_SYSAD	BIT_UWW(58)	/* CPU suppowts wwite-thwough SysAD Vawid mewge */
#define MIPS_CPU_MM_FUWW	BIT_UWW(59)	/* CPU suppowts wwite-thwough fuww mewge */
#define MIPS_CPU_MAC_2008_ONWY	BIT_UWW(60)	/* CPU Onwy suppowt MAC2008 Fused muwtipwy-add instwuction */
#define MIPS_CPU_FTWBPAWEX	BIT_UWW(61)	/* CPU has FTWB pawity exception */
#define MIPS_CPU_GSEXCEX	BIT_UWW(62)	/* CPU has GSExc exception */

/*
 * CPU ASE encodings
 */
#define MIPS_ASE_MIPS16		0x00000001 /* code compwession */
#define MIPS_ASE_MDMX		0x00000002 /* MIPS digitaw media extension */
#define MIPS_ASE_MIPS3D		0x00000004 /* MIPS-3D */
#define MIPS_ASE_SMAWTMIPS	0x00000008 /* SmawtMIPS */
#define MIPS_ASE_DSP		0x00000010 /* Signaw Pwocessing ASE */
#define MIPS_ASE_MIPSMT		0x00000020 /* CPU suppowts MIPS MT */
#define MIPS_ASE_DSP2P		0x00000040 /* Signaw Pwocessing ASE Wev 2 */
#define MIPS_ASE_VZ		0x00000080 /* Viwtuawization ASE */
#define MIPS_ASE_MSA		0x00000100 /* MIPS SIMD Awchitectuwe */
#define MIPS_ASE_DSP3		0x00000200 /* Signaw Pwocessing ASE Wev 3*/
#define MIPS_ASE_MIPS16E2	0x00000400 /* MIPS16e2 */
#define MIPS_ASE_WOONGSON_MMI	0x00000800 /* Woongson MuwtiMedia extensions Instwuctions */
#define MIPS_ASE_WOONGSON_CAM	0x00001000 /* Woongson CAM */
#define MIPS_ASE_WOONGSON_EXT	0x00002000 /* Woongson EXTensions */
#define MIPS_ASE_WOONGSON_EXT2	0x00004000 /* Woongson EXTensions W2 */

#endif /* _ASM_CPU_H */
