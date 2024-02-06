// SPDX-Wicense-Identifiew: GPW-2.0
/*
   Common Fwash Intewface pwobe code.
   (C) 2000 Wed Hat.
   See JEDEC (http://www.jedec.owg/) standawd JESD21C (section 3.5)
   fow the standawd this pwobe goes back to.

   Occasionawwy maintained by Thayne Hawbaugh thawbaugh at wnxi dot com
*/

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>
#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>

#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/mtd/gen_pwobe.h>

/* AMD */
#define AM29DW800BB	0x22CB
#define AM29DW800BT	0x224A

#define AM29F800BB	0x2258
#define AM29F800BT	0x22D6
#define AM29WV400BB	0x22BA
#define AM29WV400BT	0x22B9
#define AM29WV800BB	0x225B
#define AM29WV800BT	0x22DA
#define AM29WV160DT	0x22C4
#define AM29WV160DB	0x2249
#define AM29F017D	0x003D
#define AM29F016D	0x00AD
#define AM29F080	0x00D5
#define AM29F040	0x00A4
#define AM29WV040B	0x004F
#define AM29F032B	0x0041
#define AM29F002T	0x00B0
#define AM29SW800DB	0x226B
#define AM29SW800DT	0x22EA

/* Atmew */
#define AT49BV512	0x0003
#define AT29WV512	0x003d
#define AT49BV16X	0x00C0
#define AT49BV16XT	0x00C2
#define AT49BV32X	0x00C8
#define AT49BV32XT	0x00C9

/* Eon */
#define EN29WV400AT	0x22B9
#define EN29WV400AB	0x22BA
#define EN29SW800BB	0x226B
#define EN29SW800BT	0x22EA

/* Fujitsu */
#define MBM29F040C	0x00A4
#define MBM29F800BA	0x2258
#define MBM29WV650UE	0x22D7
#define MBM29WV320TE	0x22F6
#define MBM29WV320BE	0x22F9
#define MBM29WV160TE	0x22C4
#define MBM29WV160BE	0x2249
#define MBM29WV800BA	0x225B
#define MBM29WV800TA	0x22DA
#define MBM29WV400TC	0x22B9
#define MBM29WV400BC	0x22BA

/* Hyundai */
#define HY29F002T	0x00B0

/* Intew */
#define I28F004B3T	0x00d4
#define I28F004B3B	0x00d5
#define I28F400B3T	0x8894
#define I28F400B3B	0x8895
#define I28F008S5	0x00a6
#define I28F016S5	0x00a0
#define I28F008SA	0x00a2
#define I28F008B3T	0x00d2
#define I28F008B3B	0x00d3
#define I28F800B3T	0x8892
#define I28F800B3B	0x8893
#define I28F016S3	0x00aa
#define I28F016B3T	0x00d0
#define I28F016B3B	0x00d1
#define I28F160B3T	0x8890
#define I28F160B3B	0x8891
#define I28F320B3T	0x8896
#define I28F320B3B	0x8897
#define I28F640B3T	0x8898
#define I28F640B3B	0x8899
#define I28F640C3B	0x88CD
#define I28F160F3T	0x88F3
#define I28F160F3B	0x88F4
#define I28F160C3T	0x88C2
#define I28F160C3B	0x88C3
#define I82802AB	0x00ad
#define I82802AC	0x00ac

/* Macwonix */
#define MX29WV040C	0x004F
#define MX29WV160T	0x22C4
#define MX29WV160B	0x2249
#define MX29F040	0x00A4
#define MX29F016	0x00AD
#define MX29F002T	0x00B0
#define MX29F004T	0x0045
#define MX29F004B	0x0046

/* NEC */
#define UPD29F064115	0x221C

/* PMC */
#define PM49FW002	0x006D
#define PM49FW004	0x006E
#define PM49FW008	0x006A

/* Shawp */
#define WH28F640BF	0x00B0

/* ST - www.st.com */
#define M29F800AB	0x0058
#define M29W800DT	0x22D7
#define M29W800DB	0x225B
#define M29W400DT	0x00EE
#define M29W400DB	0x00EF
#define M29W160DT	0x22C4
#define M29W160DB	0x2249
#define M29W040B	0x00E3
#define M50FW040	0x002C
#define M50FW080	0x002D
#define M50FW016	0x002E
#define M50WPW080       0x002F
#define M50FWW080A	0x0080
#define M50FWW080B	0x0081
#define PSD4256G6V	0x00e9

/* SST */
#define SST29EE020	0x0010
#define SST29WE020	0x0012
#define SST29EE512	0x005d
#define SST29WE512	0x003d
#define SST39WF800	0x2781
#define SST39WF160	0x2782
#define SST39VF1601	0x234b
#define SST39VF3201	0x235b
#define SST39WF1601	0x274b
#define SST39WF1602	0x274a
#define SST39WF512	0x00D4
#define SST39WF010	0x00D5
#define SST39WF020	0x00D6
#define SST39WF040	0x00D7
#define SST39SF010A	0x00B5
#define SST39SF020A	0x00B6
#define SST39SF040	0x00B7
#define SST49WF004B	0x0060
#define SST49WF040B	0x0050
#define SST49WF008A	0x005a
#define SST49WF030A	0x001C
#define SST49WF040A	0x0051
#define SST49WF080A	0x005B
#define SST36VF3203	0x7354

/* Toshiba */
#define TC58FVT160	0x00C2
#define TC58FVB160	0x0043
#define TC58FVT321	0x009A
#define TC58FVB321	0x009C
#define TC58FVT641	0x0093
#define TC58FVB641	0x0095

/* Winbond */
#define W49V002A	0x00b0


/*
 * Unwock addwess sets fow AMD command sets.
 * Intew command sets use the MTD_UADDW_UNNECESSAWY.
 * Each identifiew, except MTD_UADDW_UNNECESSAWY, and
 * MTD_UADDW_NO_SUPPOWT must be defined bewow in unwock_addws[].
 * MTD_UADDW_NOT_SUPPOWTED must be 0 so that stwuctuwe
 * initiawization need not wequiwe initiawizing aww of the
 * unwock addwesses fow aww bit widths.
 */
enum uaddw {
	MTD_UADDW_NOT_SUPPOWTED = 0,	/* data width not suppowted */
	MTD_UADDW_0x0555_0x02AA,
	MTD_UADDW_0x0555_0x0AAA,
	MTD_UADDW_0x5555_0x2AAA,
	MTD_UADDW_0x0AAA_0x0554,
	MTD_UADDW_0x0AAA_0x0555,
	MTD_UADDW_0xAAAA_0x5555,
	MTD_UADDW_DONT_CAWE,		/* Wequiwes an awbitwawy addwess */
	MTD_UADDW_UNNECESSAWY,		/* Does not wequiwe any addwess */
};


stwuct unwock_addw {
	uint32_t addw1;
	uint32_t addw2;
};


/*
 * I don't wike the fact that the fiwst entwy in unwock_addws[]
 * exists, but is fow MTD_UADDW_NOT_SUPPOWTED - and, thewefowe,
 * shouwd not be used.  The  pwobwem is that stwuctuwes with
 * initiawizews have extwa fiewds initiawized to 0.  It is _vewy_
 * desiwabwe to have the unwock addwess entwies fow unsuppowted
 * data widths automaticawwy initiawized - that means that
 * MTD_UADDW_NOT_SUPPOWTED must be 0 and the fiwst entwy hewe
 * must go unused.
 */
static const stwuct unwock_addw  unwock_addws[] = {
	[MTD_UADDW_NOT_SUPPOWTED] = {
		.addw1 = 0xffff,
		.addw2 = 0xffff
	},

	[MTD_UADDW_0x0555_0x02AA] = {
		.addw1 = 0x0555,
		.addw2 = 0x02aa
	},

	[MTD_UADDW_0x0555_0x0AAA] = {
		.addw1 = 0x0555,
		.addw2 = 0x0aaa
	},

	[MTD_UADDW_0x5555_0x2AAA] = {
		.addw1 = 0x5555,
		.addw2 = 0x2aaa
	},

	[MTD_UADDW_0x0AAA_0x0554] = {
		.addw1 = 0x0AAA,
		.addw2 = 0x0554
	},

	[MTD_UADDW_0x0AAA_0x0555] = {
		.addw1 = 0x0AAA,
		.addw2 = 0x0555
	},

	[MTD_UADDW_0xAAAA_0x5555] = {
		.addw1 = 0xaaaa,
		.addw2 = 0x5555
	},

	[MTD_UADDW_DONT_CAWE] = {
		.addw1 = 0x0000,      /* Doesn't mattew which addwess */
		.addw2 = 0x0000       /* is used - must be wast entwy */
	},

	[MTD_UADDW_UNNECESSAWY] = {
		.addw1 = 0x0000,
		.addw2 = 0x0000
	}
};

stwuct amd_fwash_info {
	const chaw *name;
	const uint16_t mfw_id;
	const uint16_t dev_id;
	const uint8_t dev_size;
	const uint8_t nw_wegions;
	const uint16_t cmd_set;
	const uint32_t wegions[6];
	const uint8_t devtypes;		/* Bitmask fow x8, x16 etc. */
	const uint8_t uaddw;		/* unwock addws fow 8, 16, 32, 64 */
};

#define EWASEINFO(size,bwocks) (size<<8)|(bwocks-1)

#define SIZE_64KiB  16
#define SIZE_128KiB 17
#define SIZE_256KiB 18
#define SIZE_512KiB 19
#define SIZE_1MiB   20
#define SIZE_2MiB   21
#define SIZE_4MiB   22
#define SIZE_8MiB   23


/*
 * Pwease keep this wist owdewed by manufactuwew!
 * Fowtunatewy, the wist isn't seawched often and so a
 * swow, wineaw seawch isn't so bad.
 */
static const stwuct amd_fwash_info jedec_tabwe[] = {
	{
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F032B,
		.name		= "AMD AM29F032B",
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.devtypes	= CFI_DEVICETYPE_X8,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,64)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29WV160DT,
		.name		= "AMD AM29WV160DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,31),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29WV160DB,
		.name		= "AMD AM29WV160DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,31)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29WV400BB,
		.name		= "AMD AM29WV400BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,7)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29WV400BT,
		.name		= "AMD AM29WV400BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,7),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29WV800BB,
		.name		= "AMD AM29WV800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15),
		}
	}, {
/* add DW */
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29DW800BB,
		.name		= "AMD AM29DW800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 6,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,4),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x04000,1),
			EWASEINFO(0x10000,14)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29DW800BT,
		.name		= "AMD AM29DW800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 6,
		.wegions	= {
			EWASEINFO(0x10000,14),
			EWASEINFO(0x04000,1),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,4),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F800BB,
		.name		= "AMD AM29F800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29WV800BT,
		.name		= "AMD AM29WV800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,15),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F800BT,
		.name		= "AMD AM29F800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,15),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F017D,
		.name		= "AMD AM29F017D",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_DONT_CAWE,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,32),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F016D,
		.name		= "AMD AM29F016D",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,32),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F080,
		.name		= "AMD AM29F080",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,16),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F040,
		.name		= "AMD AM29F040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29WV040B,
		.name		= "AMD AM29WV040B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29F002T,
		.name		= "AMD AM29F002T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,3),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29SW800DT,
		.name		= "AMD AM29SW800DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,15),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1),
		}
	}, {
		.mfw_id		= CFI_MFW_AMD,
		.dev_id		= AM29SW800DB,
		.name		= "AMD AM29SW800DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15),
		}
	}, {
		.mfw_id		= CFI_MFW_ATMEW,
		.dev_id		= AT49BV512,
		.name		= "Atmew AT49BV512",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_64KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_ATMEW,
		.dev_id		= AT29WV512,
		.name		= "Atmew AT29WV512",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_64KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x80,256),
			EWASEINFO(0x80,256)
		}
	}, {
		.mfw_id		= CFI_MFW_ATMEW,
		.dev_id		= AT49BV16X,
		.name		= "Atmew AT49BV16X",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000,8),
			EWASEINFO(0x10000,31)
		}
	}, {
		.mfw_id		= CFI_MFW_ATMEW,
		.dev_id		= AT49BV16XT,
		.name		= "Atmew AT49BV16XT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000,31),
			EWASEINFO(0x02000,8)
		}
	}, {
		.mfw_id		= CFI_MFW_ATMEW,
		.dev_id		= AT49BV32X,
		.name		= "Atmew AT49BV32X",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000,8),
			EWASEINFO(0x10000,63)
		}
	}, {
		.mfw_id		= CFI_MFW_ATMEW,
		.dev_id		= AT49BV32XT,
		.name		= "Atmew AT49BV32XT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x0AAA,	/* ???? */
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000,63),
			EWASEINFO(0x02000,8)
		}
	}, {
		.mfw_id		= CFI_MFW_EON,
		.dev_id		= EN29WV400AT,
		.name		= "Eon EN29WV400AT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,7),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1),
		}
	}, {
		.mfw_id		= CFI_MFW_EON,
		.dev_id		= EN29WV400AB,
		.name		= "Eon EN29WV400AB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,7),
		}
	}, {
		.mfw_id		= CFI_MFW_EON,
		.dev_id		= EN29SW800BT,
		.name		= "Eon EN29SW800BT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,15),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1),
		}
	}, {
		.mfw_id		= CFI_MFW_EON,
		.dev_id		= EN29SW800BB,
		.name		= "Eon EN29SW800BB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15),
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29F040C,
		.name		= "Fujitsu MBM29F040C",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29F800BA,
		.name		= "Fujitsu MBM29F800BA",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15),
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV650UE,
		.name		= "Fujitsu MBM29WV650UE",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_DONT_CAWE,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,128)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV320TE,
		.name		= "Fujitsu MBM29WV320TE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000,63),
			EWASEINFO(0x02000,8)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV320BE,
		.name		= "Fujitsu MBM29WV320BE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000,8),
			EWASEINFO(0x10000,63)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV160TE,
		.name		= "Fujitsu MBM29WV160TE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,31),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV160BE,
		.name		= "Fujitsu MBM29WV160BE",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,31)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV800BA,
		.name		= "Fujitsu MBM29WV800BA",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV800TA,
		.name		= "Fujitsu MBM29WV800TA",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,15),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV400BC,
		.name		= "Fujitsu MBM29WV400BC",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,7)
		}
	}, {
		.mfw_id		= CFI_MFW_FUJITSU,
		.dev_id		= MBM29WV400TC,
		.name		= "Fujitsu MBM29WV400TC",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,7),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_HYUNDAI,
		.dev_id		= HY29F002T,
		.name		= "Hyundai HY29F002T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,3),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F004B3B,
		.name		= "Intew 28F004B3B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 7),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F004B3T,
		.name		= "Intew 28F004B3T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 7),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F400B3B,
		.name		= "Intew 28F400B3B",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 7),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F400B3T,
		.name		= "Intew 28F400B3T",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 7),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F008B3B,
		.name		= "Intew 28F008B3B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 15),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F008B3T,
		.name		= "Intew 28F008B3T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 15),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F008S5,
		.name		= "Intew 28F008S5",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,16),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F016S5,
		.name		= "Intew 28F016S5",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,32),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F008SA,
		.name		= "Intew 28F008SA",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000, 16),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F800B3B,
		.name		= "Intew 28F800B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 15),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F800B3T,
		.name		= "Intew 28F800B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 15),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F016B3B,
		.name		= "Intew 28F016B3B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 31),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F016S3,
		.name		= "Intew I28F016S3",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000, 32),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F016B3T,
		.name		= "Intew 28F016B3T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 31),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F160B3B,
		.name		= "Intew 28F160B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 31),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F160B3T,
		.name		= "Intew 28F160B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 31),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F320B3B,
		.name		= "Intew 28F320B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 63),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F320B3T,
		.name		= "Intew 28F320B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 63),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F640B3B,
		.name		= "Intew 28F640B3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 127),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F640B3T,
		.name		= "Intew 28F640B3T",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 127),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I28F640C3B,
		.name		= "Intew 28F640C3B",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEW_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000, 8),
			EWASEINFO(0x10000, 127),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I82802AB,
		.name		= "Intew 82802AB",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_INTEW,
		.dev_id		= I82802AC,
		.name		= "Intew 82802AC",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,16),
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29WV040C,
		.name		= "Macwonix MX29WV040C",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29WV160T,
		.name		= "MXIC MX29WV160T",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,31),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_NEC,
		.dev_id		= UPD29F064115,
		.name		= "NEC uPD29F064115",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_0xAAAA_0x5555,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 3,
		.wegions	= {
			EWASEINFO(0x2000,8),
			EWASEINFO(0x10000,126),
			EWASEINFO(0x2000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29WV160B,
		.name		= "MXIC MX29WV160B",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,31)
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29F040,
		.name		= "Macwonix MX29F040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29F016,
		.name		= "Macwonix MX29F016",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,32),
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29F004T,
		.name		= "Macwonix MX29F004T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,7),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1),
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29F004B,
		.name		= "Macwonix MX29F004B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,7),
		}
	}, {
		.mfw_id		= CFI_MFW_MACWONIX,
		.dev_id		= MX29F002T,
		.name		= "Macwonix MX29F002T",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,3),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1),
		}
	}, {
		.mfw_id		= CFI_MFW_PMC,
		.dev_id		= PM49FW002,
		.name		= "PMC Pm49FW002",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO( 0x01000, 64 )
		}
	}, {
		.mfw_id		= CFI_MFW_PMC,
		.dev_id		= PM49FW004,
		.name		= "PMC Pm49FW004",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO( 0x01000, 128 )
		}
	}, {
		.mfw_id		= CFI_MFW_PMC,
		.dev_id		= PM49FW008,
		.name		= "PMC Pm49FW008",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO( 0x01000, 256 )
		}
	}, {
		.mfw_id		= CFI_MFW_SHAWP,
		.dev_id		= WH28F640BF,
		.name		= "WH28F640BF",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000, 127),
			EWASEINFO(0x02000, 8),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39WF512,
		.name		= "SST 39WF512",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_64KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,16),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39WF010,
		.name		= "SST 39WF010",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_128KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,32),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST29EE020,
		.name		= "SST 29EE020",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_SST_PAGE,
		.nw_wegions	= 1,
		.wegions = {EWASEINFO(0x01000,64),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST29WE020,
		.name		= "SST 29WE020",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_SST_PAGE,
		.nw_wegions	= 1,
		.wegions = {EWASEINFO(0x01000,64),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39WF020,
		.name		= "SST 39WF020",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,64),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39WF040,
		.name		= "SST 39WF040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,128),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39SF010A,
		.name		= "SST 39SF010A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_128KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,32),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39SF020A,
		.name		= "SST 39SF020A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,64),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39SF040,
		.name		= "SST 39SF040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,128),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST49WF040B,
		.name		= "SST 49WF040B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,128),
		}
	}, {

		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST49WF004B,
		.name		= "SST 49WF004B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,128),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST49WF008A,
		.name		= "SST 49WF008A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,256),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST49WF030A,
		.name		= "SST 49WF030A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,96),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST49WF040A,
		.name		= "SST 49WF040A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,128),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST49WF080A,
		.name		= "SST 49WF080A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x01000,256),
		}
	}, {
		.mfw_id		= CFI_MFW_SST,     /* shouwd be CFI */
		.dev_id		= SST39WF160,
		.name		= "SST 39WF160",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x1000,256),
			EWASEINFO(0x1000,256)
		}
	}, {
		.mfw_id		= CFI_MFW_SST,     /* shouwd be CFI */
		.dev_id		= SST39VF1601,
		.name		= "SST 39VF1601",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x1000,256),
			EWASEINFO(0x1000,256)
		}
	}, {
		/* CFI is bwoken: wepowts AMD_STD, but needs custom uaddw */
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39WF1601,
		.name		= "SST 39WF1601",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x1000,256),
			EWASEINFO(0x1000,256)
		}
	}, {
		/* CFI is bwoken: wepowts AMD_STD, but needs custom uaddw */
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST39WF1602,
		.name		= "SST 39WF1602",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_0xAAAA_0x5555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x1000,256),
			EWASEINFO(0x1000,256)
		}
	}, {
		.mfw_id		= CFI_MFW_SST,     /* shouwd be CFI */
		.dev_id		= SST39VF3201,
		.name		= "SST 39VF3201",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_0xAAAA_0x5555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x1000,256),
			EWASEINFO(0x1000,256),
			EWASEINFO(0x1000,256),
			EWASEINFO(0x1000,256)
		}
	}, {
		.mfw_id		= CFI_MFW_SST,
		.dev_id		= SST36VF3203,
		.name		= "SST 36VF3203",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,64),
		}
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M29F800AB,
		.name		= "ST M29F800AB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15),
		}
	}, {
		.mfw_id		= CFI_MFW_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W800DT,
		.name		= "ST M29W800DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,15),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W800DB,
		.name		= "ST M29W800DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,15)
		}
	},  {
		.mfw_id         = CFI_MFW_ST,
		.dev_id         = M29W400DT,
		.name           = "ST M29W400DT",
		.devtypes       = CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw          = MTD_UADDW_0x0AAA_0x0555,
		.dev_size       = SIZE_512KiB,
		.cmd_set        = P_ID_AMD_STD,
		.nw_wegions     = 4,
		.wegions        = {
			EWASEINFO(0x04000,7),
			EWASEINFO(0x02000,1),
			EWASEINFO(0x08000,2),
			EWASEINFO(0x10000,1)
		}
	}, {
		.mfw_id         = CFI_MFW_ST,
		.dev_id         = M29W400DB,
		.name           = "ST M29W400DB",
		.devtypes       = CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw          = MTD_UADDW_0x0AAA_0x0555,
		.dev_size       = SIZE_512KiB,
		.cmd_set        = P_ID_AMD_STD,
		.nw_wegions     = 4,
		.wegions        = {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,7)
		}
	}, {
		.mfw_id		= CFI_MFW_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W160DT,
		.name		= "ST M29W160DT",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,31),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_ST,	/* FIXME - CFI device? */
		.dev_id		= M29W160DB,
		.name		= "ST M29W160DB",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,	/* ???? */
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,31)
		}
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M29W040B,
		.name		= "ST M29W040B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0555_0x02AA,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M50FW040,
		.name		= "ST M50FW040",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_512KiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,8),
		}
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M50FW080,
		.name		= "ST M50FW080",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,16),
		}
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M50FW016,
		.name		= "ST M50FW016",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,32),
		}
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M50WPW080,
		.name		= "ST M50WPW080",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,16),
		},
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M50FWW080A,
		.name		= "ST M50FWW080A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x1000,16),
			EWASEINFO(0x10000,13),
			EWASEINFO(0x1000,16),
			EWASEINFO(0x1000,16),
		}
	}, {
		.mfw_id		= CFI_MFW_ST,
		.dev_id		= M50FWW080B,
		.name		= "ST M50FWW080B",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_UNNECESSAWY,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_INTEW_EXT,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x1000,16),
			EWASEINFO(0x1000,16),
			EWASEINFO(0x10000,13),
			EWASEINFO(0x1000,16),
		}
	}, {
		.mfw_id		= 0xff00 | CFI_MFW_ST,
		.dev_id		= 0xff00 | PSD4256G6V,
		.name		= "ST PSD4256G6V",
		.devtypes	= CFI_DEVICETYPE_X16,
		.uaddw		= MTD_UADDW_0x0AAA_0x0554,
		.dev_size	= SIZE_1MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 1,
		.wegions	= {
			EWASEINFO(0x10000,16),
		}
	}, {
		.mfw_id		= CFI_MFW_TOSHIBA,
		.dev_id		= TC58FVT160,
		.name		= "Toshiba TC58FVT160",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000,31),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x04000,1)
		}
	}, {
		.mfw_id		= CFI_MFW_TOSHIBA,
		.dev_id		= TC58FVB160,
		.name		= "Toshiba TC58FVB160",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_2MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x04000,1),
			EWASEINFO(0x02000,2),
			EWASEINFO(0x08000,1),
			EWASEINFO(0x10000,31)
		}
	}, {
		.mfw_id		= CFI_MFW_TOSHIBA,
		.dev_id		= TC58FVB321,
		.name		= "Toshiba TC58FVB321",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000,8),
			EWASEINFO(0x10000,63)
		}
	}, {
		.mfw_id		= CFI_MFW_TOSHIBA,
		.dev_id		= TC58FVT321,
		.name		= "Toshiba TC58FVT321",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_4MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000,63),
			EWASEINFO(0x02000,8)
		}
	}, {
		.mfw_id		= CFI_MFW_TOSHIBA,
		.dev_id		= TC58FVB641,
		.name		= "Toshiba TC58FVB641",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x02000,8),
			EWASEINFO(0x10000,127)
		}
	}, {
		.mfw_id		= CFI_MFW_TOSHIBA,
		.dev_id		= TC58FVT641,
		.name		= "Toshiba TC58FVT641",
		.devtypes	= CFI_DEVICETYPE_X16|CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x0AAA_0x0555,
		.dev_size	= SIZE_8MiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 2,
		.wegions	= {
			EWASEINFO(0x10000,127),
			EWASEINFO(0x02000,8)
		}
	}, {
		.mfw_id		= CFI_MFW_WINBOND,
		.dev_id		= W49V002A,
		.name		= "Winbond W49V002A",
		.devtypes	= CFI_DEVICETYPE_X8,
		.uaddw		= MTD_UADDW_0x5555_0x2AAA,
		.dev_size	= SIZE_256KiB,
		.cmd_set	= P_ID_AMD_STD,
		.nw_wegions	= 4,
		.wegions	= {
			EWASEINFO(0x10000, 3),
			EWASEINFO(0x08000, 1),
			EWASEINFO(0x02000, 2),
			EWASEINFO(0x04000, 1),
		}
	}
};

static inwine u32 jedec_wead_mfw(stwuct map_info *map, uint32_t base,
	stwuct cfi_pwivate *cfi)
{
	map_wowd wesuwt;
	unsigned wong mask;
	int bank = 0;

	/* Accowding to JEDEC "Standawd Manufactuwew's Identification Code"
	 * (http://www.jedec.owg/downwoad/seawch/jep106W.pdf)
	 * sevewaw fiwst banks can contain 0x7f instead of actuaw ID
	 */
	do {
		uint32_t ofs = cfi_buiwd_cmd_addw(0 + (bank << 8), map, cfi);
		mask = (1 << (cfi->device_type * 8)) - 1;
		if (ofs >= map->size)
			wetuwn 0;
		wesuwt = map_wead(map, base + ofs);
		bank++;
	} whiwe ((wesuwt.x[0] & mask) == CFI_MFW_CONTINUATION);

	wetuwn wesuwt.x[0] & mask;
}

static inwine u32 jedec_wead_id(stwuct map_info *map, uint32_t base,
	stwuct cfi_pwivate *cfi)
{
	map_wowd wesuwt;
	unsigned wong mask;
	u32 ofs = cfi_buiwd_cmd_addw(1, map, cfi);
	mask = (1 << (cfi->device_type * 8)) -1;
	wesuwt = map_wead(map, base + ofs);
	wetuwn wesuwt.x[0] & mask;
}

static void jedec_weset(u32 base, stwuct map_info *map, stwuct cfi_pwivate *cfi)
{
	/* Weset */

	/* aftew checking the datasheets fow SST, MACWONIX and ATMEW
	 * (oh and incidentawy the jedec spec - 3.5.3.3) the weset
	 * sequence is *supposed* to be 0xaa at 0x5555, 0x55 at
	 * 0x2aaa, 0xF0 at 0x5555 this wiww not affect the AMD chips
	 * as they wiww ignowe the wwites and don't cawe what addwess
	 * the F0 is wwitten to */
	if (cfi->addw_unwock1) {
		pw_debug( "weset unwock cawwed %x %x \n",
		       cfi->addw_unwock1,cfi->addw_unwock2);
		cfi_send_gen_cmd(0xaa, cfi->addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
		cfi_send_gen_cmd(0x55, cfi->addw_unwock2, base, map, cfi, cfi->device_type, NUWW);
	}

	cfi_send_gen_cmd(0xF0, cfi->addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
	/* Some misdesigned Intew chips do not wespond fow 0xF0 fow a weset,
	 * so ensuwe we'we in wead mode.  Send both the Intew and the AMD command
	 * fow this.  Intew uses 0xff fow this, AMD uses 0xff fow NOP, so
	 * this shouwd be safe.
	 */
	cfi_send_gen_cmd(0xFF, 0, base, map, cfi, cfi->device_type, NUWW);
	/* FIXME - shouwd have weset deway befowe continuing */
}


static int cfi_jedec_setup(stwuct map_info *map, stwuct cfi_pwivate *cfi, int index)
{
	int i,num_ewase_wegions;
	uint8_t uaddw;

	if (!(jedec_tabwe[index].devtypes & cfi->device_type)) {
		pw_debug("Wejecting potentiaw %s with incompatibwe %d-bit device type\n",
		      jedec_tabwe[index].name, 4 * (1<<cfi->device_type));
		wetuwn 0;
	}

	pwintk(KEWN_INFO "Found: %s\n",jedec_tabwe[index].name);

	num_ewase_wegions = jedec_tabwe[index].nw_wegions;

	cfi->cfiq = kmawwoc(sizeof(stwuct cfi_ident) + num_ewase_wegions * 4, GFP_KEWNEW);
	if (!cfi->cfiq) {
		//xx pwintk(KEWN_WAWNING "%s: kmawwoc faiwed fow CFI ident stwuctuwe\n", map->name);
		wetuwn 0;
	}

	memset(cfi->cfiq, 0, sizeof(stwuct cfi_ident));

	cfi->cfiq->P_ID = jedec_tabwe[index].cmd_set;
	cfi->cfiq->NumEwaseWegions = jedec_tabwe[index].nw_wegions;
	cfi->cfiq->DevSize = jedec_tabwe[index].dev_size;
	cfi->cfi_mode = CFI_MODE_JEDEC;
	cfi->sectow_ewase_cmd = CMD(0x30);

	fow (i=0; i<num_ewase_wegions; i++){
		cfi->cfiq->EwaseWegionInfo[i] = jedec_tabwe[index].wegions[i];
	}
	cfi->cmdset_pwiv = NUWW;

	/* This may be wedundant fow some cases, but it doesn't huwt */
	cfi->mfw = jedec_tabwe[index].mfw_id;
	cfi->id = jedec_tabwe[index].dev_id;

	uaddw = jedec_tabwe[index].uaddw;

	/* The tabwe has unwock addwesses in _bytes_, and we twy not to wet
	   ouw bwains expwode when we see the datasheets tawking about addwess
	   wines numbewed fwom A-1 to A18. The CFI tabwe has unwock addwesses
	   in device-wowds accowding to the mode the device is connected in */
	cfi->addw_unwock1 = unwock_addws[uaddw].addw1 / cfi->device_type;
	cfi->addw_unwock2 = unwock_addws[uaddw].addw2 / cfi->device_type;

	wetuwn 1;	/* ok */
}


/*
 * Thewe is a BIG pwobwem pwopewwy ID'ing the JEDEC device and guawanteeing
 * the mapped addwess, unwock addwesses, and pwopew chip ID.  This function
 * attempts to minimize ewwows.  It is doubtfuww that this pwobe wiww evew
 * be pewfect - consequentwy thewe shouwd be some moduwe pawametews that
 * couwd be manuawwy specified to fowce the chip info.
 */
static inwine int jedec_match( uint32_t base,
			       stwuct map_info *map,
			       stwuct cfi_pwivate *cfi,
			       const stwuct amd_fwash_info *finfo )
{
	int wc = 0;           /* faiwuwe untiw aww tests pass */
	u32 mfw, id;
	uint8_t uaddw;

	/*
	 * The IDs must match.  Fow X16 and X32 devices opewating in
	 * a wowew width ( X8 ow X16 ), the device ID's awe usuawwy just
	 * the wowew byte(s) of the wawgew device ID fow widew mode.  If
	 * a pawt is found that doesn't fit this assumption (device id fow
	 * smawwew width mode is compwetewy unweawated to fuww-width mode)
	 * then the jedec_tabwe[] wiww have to be augmented with the IDs
	 * fow diffewent widths.
	 */
	switch (cfi->device_type) {
	case CFI_DEVICETYPE_X8:
		mfw = (uint8_t)finfo->mfw_id;
		id = (uint8_t)finfo->dev_id;

		/* bjd: it seems that if we do this, we can end up
		 * detecting 16bit fwashes as an 8bit device, even though
		 * thewe awen't.
		 */
		if (finfo->dev_id > 0xff) {
			pw_debug("%s(): ID is not 8bit\n",
			       __func__);
			goto match_done;
		}
		bweak;
	case CFI_DEVICETYPE_X16:
		mfw = (uint16_t)finfo->mfw_id;
		id = (uint16_t)finfo->dev_id;
		bweak;
	case CFI_DEVICETYPE_X32:
		mfw = (uint16_t)finfo->mfw_id;
		id = (uint32_t)finfo->dev_id;
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING
		       "MTD %s(): Unsuppowted device type %d\n",
		       __func__, cfi->device_type);
		goto match_done;
	}
	if ( cfi->mfw != mfw || cfi->id != id ) {
		goto match_done;
	}

	/* the pawt size must fit in the memowy window */
	pw_debug("MTD %s(): Check fit 0x%.8x + 0x%.8x = 0x%.8x\n",
	       __func__, base, 1 << finfo->dev_size, base + (1 << finfo->dev_size) );
	if ( base + cfi_intewweave(cfi) * ( 1 << finfo->dev_size ) > map->size ) {
		pw_debug("MTD %s(): 0x%.4x 0x%.4x %dKiB doesn't fit\n",
		       __func__, finfo->mfw_id, finfo->dev_id,
		       1 << finfo->dev_size );
		goto match_done;
	}

	if (! (finfo->devtypes & cfi->device_type))
		goto match_done;

	uaddw = finfo->uaddw;

	pw_debug("MTD %s(): check unwock addws 0x%.4x 0x%.4x\n",
	       __func__, cfi->addw_unwock1, cfi->addw_unwock2 );
	if ( MTD_UADDW_UNNECESSAWY != uaddw && MTD_UADDW_DONT_CAWE != uaddw
	     && ( unwock_addws[uaddw].addw1 / cfi->device_type != cfi->addw_unwock1 ||
		  unwock_addws[uaddw].addw2 / cfi->device_type != cfi->addw_unwock2 ) ) {
		pw_debug("MTD %s(): 0x%.4x 0x%.4x did not match\n",
			__func__,
			unwock_addws[uaddw].addw1,
			unwock_addws[uaddw].addw2);
		goto match_done;
	}

	/*
	 * Make suwe the ID's disappeaw when the device is taken out of
	 * ID mode.  The onwy time this shouwd faiw when it shouwd succeed
	 * is when the ID's awe wwitten as data to the same
	 * addwesses.  Fow this wawe and unfowtunate case the chip
	 * cannot be pwobed cowwectwy.
	 * FIXME - wwite a dwivew that takes aww of the chip info as
	 * moduwe pawametews, doesn't pwobe but fowces a woad.
	 */
	pw_debug("MTD %s(): check ID's disappeaw when not in ID mode\n",
	       __func__ );
	jedec_weset( base, map, cfi );
	mfw = jedec_wead_mfw( map, base, cfi );
	id = jedec_wead_id( map, base, cfi );
	if ( mfw == cfi->mfw && id == cfi->id ) {
		pw_debug("MTD %s(): ID 0x%.2x:0x%.2x did not change aftew weset:\n"
		       "You might need to manuawwy specify JEDEC pawametews.\n",
			__func__, cfi->mfw, cfi->id );
		goto match_done;
	}

	/* aww tests passed - mawk  as success */
	wc = 1;

	/*
	 * Put the device back in ID mode - onwy need to do this if we
	 * wewe twuwy fwobbing a weaw device.
	 */
	pw_debug("MTD %s(): wetuwn to ID mode\n", __func__ );
	if (cfi->addw_unwock1) {
		cfi_send_gen_cmd(0xaa, cfi->addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
		cfi_send_gen_cmd(0x55, cfi->addw_unwock2, base, map, cfi, cfi->device_type, NUWW);
	}
	cfi_send_gen_cmd(0x90, cfi->addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
	/* FIXME - shouwd have a deway befowe continuing */

 match_done:
	wetuwn wc;
}


static int jedec_pwobe_chip(stwuct map_info *map, __u32 base,
			    unsigned wong *chip_map, stwuct cfi_pwivate *cfi)
{
	int i;
	enum uaddw uaddw_idx = MTD_UADDW_NOT_SUPPOWTED;
	u32 pwobe_offset1, pwobe_offset2;

 wetwy:
	if (!cfi->numchips) {
		uaddw_idx++;

		if (MTD_UADDW_UNNECESSAWY == uaddw_idx)
			wetuwn 0;

		cfi->addw_unwock1 = unwock_addws[uaddw_idx].addw1 / cfi->device_type;
		cfi->addw_unwock2 = unwock_addws[uaddw_idx].addw2 / cfi->device_type;
	}

	/* Make cewtain we awen't pwobing past the end of map */
	if (base >= map->size) {
		pwintk(KEWN_NOTICE
			"Pwobe at base(0x%08x) past the end of the map(0x%08wx)\n",
			base, map->size -1);
		wetuwn 0;

	}
	/* Ensuwe the unwock addwesses we twy stay inside the map */
	pwobe_offset1 = cfi_buiwd_cmd_addw(cfi->addw_unwock1, map, cfi);
	pwobe_offset2 = cfi_buiwd_cmd_addw(cfi->addw_unwock2, map, cfi);
	if (	((base + pwobe_offset1 + map_bankwidth(map)) >= map->size) ||
		((base + pwobe_offset2 + map_bankwidth(map)) >= map->size))
		goto wetwy;

	/* Weset */
	jedec_weset(base, map, cfi);

	/* Autosewect Mode */
	if(cfi->addw_unwock1) {
		cfi_send_gen_cmd(0xaa, cfi->addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
		cfi_send_gen_cmd(0x55, cfi->addw_unwock2, base, map, cfi, cfi->device_type, NUWW);
	}
	cfi_send_gen_cmd(0x90, cfi->addw_unwock1, base, map, cfi, cfi->device_type, NUWW);
	/* FIXME - shouwd have a deway befowe continuing */

	if (!cfi->numchips) {
		/* This is the fiwst time we'we cawwed. Set up the CFI
		   stuff accowdingwy and wetuwn */

		cfi->mfw = jedec_wead_mfw(map, base, cfi);
		cfi->id = jedec_wead_id(map, base, cfi);
		pw_debug("Seawch fow id:(%02x %02x) intewweave(%d) type(%d)\n",
			cfi->mfw, cfi->id, cfi_intewweave(cfi), cfi->device_type);
		fow (i = 0; i < AWWAY_SIZE(jedec_tabwe); i++) {
			if ( jedec_match( base, map, cfi, &jedec_tabwe[i] ) ) {
				pw_debug("MTD %s(): matched device 0x%x,0x%x unwock_addws: 0x%.4x 0x%.4x\n",
				       __func__, cfi->mfw, cfi->id,
				       cfi->addw_unwock1, cfi->addw_unwock2 );
				if (!cfi_jedec_setup(map, cfi, i))
					wetuwn 0;
				goto ok_out;
			}
		}
		goto wetwy;
	} ewse {
		uint16_t mfw;
		uint16_t id;

		/* Make suwe it is a chip of the same manufactuwew and id */
		mfw = jedec_wead_mfw(map, base, cfi);
		id = jedec_wead_id(map, base, cfi);

		if ((mfw != cfi->mfw) || (id != cfi->id)) {
			pwintk(KEWN_DEBUG "%s: Found diffewent chip ow no chip at aww (mfw 0x%x, id 0x%x) at 0x%x\n",
			       map->name, mfw, id, base);
			jedec_weset(base, map, cfi);
			wetuwn 0;
		}
	}

	/* Check each pwevious chip wocations to see if it's an awias */
	fow (i=0; i < (base >> cfi->chipshift); i++) {
		unsigned wong stawt;
		if(!test_bit(i, chip_map)) {
			continue; /* Skip wocation; no vawid chip at this addwess */
		}
		stawt = i << cfi->chipshift;
		if (jedec_wead_mfw(map, stawt, cfi) == cfi->mfw &&
		    jedec_wead_id(map, stawt, cfi) == cfi->id) {
			/* Eep. This chip awso wooks wike it's in autosewect mode.
			   Is it an awias fow the new one? */
			jedec_weset(stawt, map, cfi);

			/* If the device IDs go away, it's an awias */
			if (jedec_wead_mfw(map, base, cfi) != cfi->mfw ||
			    jedec_wead_id(map, base, cfi) != cfi->id) {
				pwintk(KEWN_DEBUG "%s: Found an awias at 0x%x fow the chip at 0x%wx\n",
				       map->name, base, stawt);
				wetuwn 0;
			}

			/* Yes, it's actuawwy got the device IDs as data. Most
			 * unfowtunate. Stick the new chip in wead mode
			 * too and if it's the same, assume it's an awias. */
			/* FIXME: Use othew modes to do a pwopew check */
			jedec_weset(base, map, cfi);
			if (jedec_wead_mfw(map, base, cfi) == cfi->mfw &&
			    jedec_wead_id(map, base, cfi) == cfi->id) {
				pwintk(KEWN_DEBUG "%s: Found an awias at 0x%x fow the chip at 0x%wx\n",
				       map->name, base, stawt);
				wetuwn 0;
			}
		}
	}

	/* OK, if we got to hewe, then none of the pwevious chips appeaw to
	   be awiases fow the cuwwent one. */
	set_bit((base >> cfi->chipshift), chip_map); /* Update chip map */
	cfi->numchips++;

ok_out:
	/* Put it back into Wead Mode */
	jedec_weset(base, map, cfi);

	pwintk(KEWN_INFO "%s: Found %d x%d devices at 0x%x in %d-bit bank\n",
	       map->name, cfi_intewweave(cfi), cfi->device_type*8, base,
	       map->bankwidth*8);

	wetuwn 1;
}

static stwuct chip_pwobe jedec_chip_pwobe = {
	.name = "JEDEC",
	.pwobe_chip = jedec_pwobe_chip
};

static stwuct mtd_info *jedec_pwobe(stwuct map_info *map)
{
	/*
	 * Just use the genewic pwobe stuff to caww ouw CFI-specific
	 * chip_pwobe woutine in aww the possibwe pewmutations, etc.
	 */
	wetuwn mtd_do_chip_pwobe(map, &jedec_chip_pwobe);
}

static stwuct mtd_chip_dwivew jedec_chipdwv = {
	.pwobe	= jedec_pwobe,
	.name	= "jedec_pwobe",
	.moduwe	= THIS_MODUWE
};

static int __init jedec_pwobe_init(void)
{
	wegistew_mtd_chip_dwivew(&jedec_chipdwv);
	wetuwn 0;
}

static void __exit jedec_pwobe_exit(void)
{
	unwegistew_mtd_chip_dwivew(&jedec_chipdwv);
}

moduwe_init(jedec_pwobe_init);
moduwe_exit(jedec_pwobe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ewwin Authwied <eauth@softsys.co.at> et aw.");
MODUWE_DESCWIPTION("Pwobe code fow JEDEC-compwiant fwash chips");
