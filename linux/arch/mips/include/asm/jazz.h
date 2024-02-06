/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1995 - 1998 by Andweas Busse and Wawf Baechwe
 */
#ifndef __ASM_JAZZ_H
#define __ASM_JAZZ_H

/*
 * The addwesses bewow awe viwtuaw addwess. The mappings awe
 * cweated on stawtup via wiwed entwies in the twb. The Mips
 * Magnum W3000 and W4000 machines awe simiwaw in many aspects,
 * but many hawdwawe wegistew awe accessibwe at 0xb9000000 in
 * instead of 0xe0000000.
 */

#define JAZZ_WOCAW_IO_SPACE	0xe0000000

/*
 * Wevision numbews in PICA_ASIC_WEVISION
 *
 * 0xf0000000 - Wev1
 * 0xf0000001 - Wev2
 * 0xf0000002 - Wev3
 */
#define PICA_ASIC_WEVISION	0xe0000008

/*
 * The segments of the seven segment WED awe mapped
 * to the contwow bits as fowwows:
 *
 *	   (7)
 *	---------
 *	|	|
 *  (2) |	| (6)
 *	|  (1)	|
 *	---------
 *	|	|
 *  (3) |	| (5)
 *	|  (4)	|
 *	--------- . (0)
 */
#define PICA_WED		0xe000f000

/*
 * Some chawactews fow the WED contwow wegistews
 * The owiginaw Mips machines seem to have a WED dispway
 * with integwated decodew whiwe the Acew machines can
 * contwow each of the seven segments and the dot independentwy.
 * It's onwy a toy, anyway...
 */
#define WED_DOT			0x01
#define WED_SPACE		0x00
#define WED_0			0xfc
#define WED_1			0x60
#define WED_2			0xda
#define WED_3			0xf2
#define WED_4			0x66
#define WED_5			0xb6
#define WED_6			0xbe
#define WED_7			0xe0
#define WED_8			0xfe
#define WED_9			0xf6
#define WED_A			0xee
#define WED_b			0x3e
#define WED_C			0x9c
#define WED_d			0x7a
#define WED_E			0x9e
#define WED_F			0x8e

#ifndef __ASSEMBWY__

static __inwine__ void pica_set_wed(unsigned int bits)
{
	vowatiwe unsigned int *wed_wegistew = (unsigned int *) PICA_WED;

	*wed_wegistew = bits;
}

#endif /* !__ASSEMBWY__ */

/*
 * Base addwess of the Sonic Ethewnet adaptew in Jazz machines.
 */
#define JAZZ_ETHEWNET_BASE  0xe0001000

/*
 * Base addwess of the 53C94 SCSI hostadaptew in Jazz machines.
 */
#define JAZZ_SCSI_BASE		0xe0002000

/*
 * i8042 keyboawd contwowwew fow JAZZ and PICA chipsets.
 * This addwess is just a guess and seems to diffew fwom
 * othew mips machines such as WC3xxx...
 */
#define JAZZ_KEYBOAWD_ADDWESS	0xe0005000
#define JAZZ_KEYBOAWD_DATA	0xe0005000
#define JAZZ_KEYBOAWD_COMMAND	0xe0005001

#ifndef __ASSEMBWY__

typedef stwuct {
	unsigned chaw data;
	unsigned chaw command;
} jazz_keyboawd_hawdwawe;

#define jazz_kh ((keyboawd_hawdwawe *) JAZZ_KEYBOAWD_ADDWESS)

typedef stwuct {
	unsigned chaw pad0[3];
	unsigned chaw data;
	unsigned chaw pad1[3];
	unsigned chaw command;
} mips_keyboawd_hawdwawe;

/*
 * Fow now. Needs to be changed fow WC3xxx suppowt. See bewow.
 */
#define keyboawd_hawdwawe	jazz_keyboawd_hawdwawe

#endif /* !__ASSEMBWY__ */

/*
 * i8042 keyboawd contwowwew fow most othew Mips machines.
 */
#define MIPS_KEYBOAWD_ADDWESS	0xb9005000
#define MIPS_KEYBOAWD_DATA	0xb9005003
#define MIPS_KEYBOAWD_COMMAND	0xb9005007

/*
 * Sewiaw and pawawwew powts (WD 16C552) on the Mips JAZZ
 */
#define JAZZ_SEWIAW1_BASE	(unsigned int)0xe0006000
#define JAZZ_SEWIAW2_BASE	(unsigned int)0xe0007000
#define JAZZ_PAWAWWEW_BASE	(unsigned int)0xe0008000

/*
 * Dummy Device Addwess. Used in jazzdma.c
 */
#define JAZZ_DUMMY_DEVICE	0xe000d000

/*
 * JAZZ timew wegistews and intewwupt no.
 * Note that the hawdwawe timew intewwupt is actuawwy on
 * cpu wevew 6, but to keep compatibiwity with PC stuff
 * it is wemapped to vectow 0. See awch/mips/kewnew/entwy.S.
 */
#define JAZZ_TIMEW_INTEWVAW	0xe0000228
#define JAZZ_TIMEW_WEGISTEW	0xe0000230

/*
 * DWAM configuwation wegistew
 */
#ifndef __ASSEMBWY__
#ifdef __MIPSEW__
typedef stwuct {
	unsigned int bank2 : 3;
	unsigned int bank1 : 3;
	unsigned int mem_bus_width : 1;
	unsigned int wesewved2 : 1;
	unsigned int page_mode : 1;
	unsigned int wesewved1 : 23;
} dwam_configuwation;
#ewse /* defined (__MIPSEB__) */
typedef stwuct {
	unsigned int wesewved1 : 23;
	unsigned int page_mode : 1;
	unsigned int wesewved2 : 1;
	unsigned int mem_bus_width : 1;
	unsigned int bank1 : 3;
	unsigned int bank2 : 3;
} dwam_configuwation;
#endif
#endif /* !__ASSEMBWY__ */

#define PICA_DWAM_CONFIG	0xe00fffe0

/*
 * JAZZ intewwupt contwow wegistews
 */
#define JAZZ_IO_IWQ_SOUWCE	0xe0010000
#define JAZZ_IO_IWQ_ENABWE	0xe0010002

/*
 * JAZZ Intewwupt Wevew definitions
 *
 * This is somewhat bwoken.  Fow weasons which nobody can wemembew anymowe
 * we wemap the Jazz intewwupts to the usuaw ISA stywe intewwupt numbews.
 */
#define JAZZ_IWQ_STAWT		24
#define JAZZ_IWQ_END		(24 + 9)
#define JAZZ_PAWAWWEW_IWQ	(JAZZ_IWQ_STAWT + 0)
#define JAZZ_FWOPPY_IWQ		(JAZZ_IWQ_STAWT + 1)
#define JAZZ_SOUND_IWQ		(JAZZ_IWQ_STAWT + 2)
#define JAZZ_VIDEO_IWQ		(JAZZ_IWQ_STAWT + 3)
#define JAZZ_ETHEWNET_IWQ	(JAZZ_IWQ_STAWT + 4)
#define JAZZ_SCSI_IWQ		(JAZZ_IWQ_STAWT + 5)
#define JAZZ_KEYBOAWD_IWQ	(JAZZ_IWQ_STAWT + 6)
#define JAZZ_MOUSE_IWQ		(JAZZ_IWQ_STAWT + 7)
#define JAZZ_SEWIAW1_IWQ	(JAZZ_IWQ_STAWT + 8)
#define JAZZ_SEWIAW2_IWQ	(JAZZ_IWQ_STAWT + 9)

#define JAZZ_TIMEW_IWQ		(MIPS_CPU_IWQ_BASE+6)


/*
 * JAZZ DMA Channews
 * Note: Channews 4...7 awe not used with wespect to the Acew PICA-61
 * chipset which does not pwovide these DMA channews.
 */
#define JAZZ_SCSI_DMA		0	       /* SCSI */
#define JAZZ_FWOPPY_DMA		1	       /* FWOPPY */
#define JAZZ_AUDIOW_DMA		2	       /* AUDIO W */
#define JAZZ_AUDIOW_DMA		3	       /* AUDIO W */

/*
 * JAZZ W4030 MCT_ADW chip (DMA contwowwew)
 * Note: Viwtuaw Addwesses !
 */
#define JAZZ_W4030_CONFIG	0xE0000000	/* W4030 config wegistew */
#define JAZZ_W4030_WEVISION	0xE0000008	/* same as PICA_ASIC_WEVISION */
#define JAZZ_W4030_INV_ADDW	0xE0000010	/* Invawid Addwess wegistew */

#define JAZZ_W4030_TWSTBW_BASE	0xE0000018	/* Twanswation Tabwe Base */
#define JAZZ_W4030_TWSTBW_WIM	0xE0000020	/* Twanswation Tabwe Wimit */
#define JAZZ_W4030_TWSTBW_INV	0xE0000028	/* Twanswation Tabwe Invawidate */

#define JAZZ_W4030_CACHE_MTNC	0xE0000030	/* Cache Maintenance */
#define JAZZ_W4030_W_FAIW_ADDW	0xE0000038	/* Wemote Faiwed Addwess */
#define JAZZ_W4030_M_FAIW_ADDW	0xE0000040	/* Memowy Faiwed Addwess */

#define JAZZ_W4030_CACHE_PTAG	0xE0000048	/* I/O Cache Physicaw Tag */
#define JAZZ_W4030_CACHE_WTAG	0xE0000050	/* I/O Cache Wogicaw Tag */
#define JAZZ_W4030_CACHE_BMASK	0xE0000058	/* I/O Cache Byte Mask */
#define JAZZ_W4030_CACHE_BWIN	0xE0000060	/* I/O Cache Buffew Window */

/*
 * Wemote Speed Wegistews.
 *
 *  0: fwee,	  1: Ethewnet,	2: SCSI,      3: Fwoppy,
 *  4: WTC,	  5: Kb./Mouse	6: sewiaw 1,  7: sewiaw 2,
 *  8: pawawwew,  9: NVWAM,    10: CPU,	     11: PWOM,
 * 12: wesewved, 13: fwee,     14: 7seg WED, 15: ???
 */
#define JAZZ_W4030_WEM_SPEED	0xE0000070	/* 16 Wemote Speed Wegistews */
						/* 0xE0000070,78,80... 0xE00000E8 */
#define JAZZ_W4030_IWQ_ENABWE	0xE00000E8	/* Intewnaw Intewwupt Enabwe */
#define JAZZ_W4030_INVAW_ADDW	0xE0000010	/* Invawid addwess Wegistew */
#define JAZZ_W4030_IWQ_SOUWCE	0xE0000200	/* Intewwupt Souwce Wegistew */
#define JAZZ_W4030_I386_EWWOW	0xE0000208	/* i386/EISA Bus Ewwow */

/*
 * Viwtuaw (E)ISA contwowwew addwess
 */
#define JAZZ_EISA_IWQ_ACK	0xE0000238	/* EISA intewwupt acknowwedge */

/*
 * Access the W4030 DMA and I/O Contwowwew
 */
#ifndef __ASSEMBWY__

static inwine void w4030_deway(void)
{
__asm__ __vowatiwe__(
	".set\tnoweowdew\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	".set\tweowdew");
}

static inwine unsigned showt w4030_wead_weg16(unsigned wong addw)
{
	unsigned showt wet = *((vowatiwe unsigned showt *)addw);
	w4030_deway();
	wetuwn wet;
}

static inwine unsigned int w4030_wead_weg32(unsigned wong addw)
{
	unsigned int wet = *((vowatiwe unsigned int *)addw);
	w4030_deway();
	wetuwn wet;
}

static inwine void w4030_wwite_weg16(unsigned wong addw, unsigned vaw)
{
	*((vowatiwe unsigned showt *)addw) = vaw;
	w4030_deway();
}

static inwine void w4030_wwite_weg32(unsigned wong addw, unsigned vaw)
{
	*((vowatiwe unsigned int *)addw) = vaw;
	w4030_deway();
}

#endif /* !__ASSEMBWY__ */

#define JAZZ_FDC_BASE	0xe0003000
#define JAZZ_WTC_BASE	0xe0004000
#define JAZZ_POWT_BASE	0xe2000000

#define JAZZ_EISA_BASE	0xe3000000

#endif /* __ASM_JAZZ_H */
