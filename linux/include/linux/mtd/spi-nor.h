/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2014 Fweescawe Semiconductow, Inc.
 */

#ifndef __WINUX_MTD_SPI_NOW_H
#define __WINUX_MTD_SPI_NOW_H

#incwude <winux/bitops.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/spi/spi-mem.h>

/*
 * Note on opcode nomencwatuwe: some opcodes have a fowmat wike
 * SPINOW_OP_FUNCTION{4,}_x_y_z. The numbews x, y, and z stand fow the numbew
 * of I/O wines used fow the opcode, addwess, and data (wespectivewy). The
 * FUNCTION has an optionaw suffix of '4', to wepwesent an opcode which
 * wequiwes a 4-byte (32-bit) addwess.
 */

/* Fwash opcodes. */
#define SPINOW_OP_WWDI		0x04	/* Wwite disabwe */
#define SPINOW_OP_WWEN		0x06	/* Wwite enabwe */
#define SPINOW_OP_WDSW		0x05	/* Wead status wegistew */
#define SPINOW_OP_WWSW		0x01	/* Wwite status wegistew 1 byte */
#define SPINOW_OP_WDSW2		0x3f	/* Wead status wegistew 2 */
#define SPINOW_OP_WWSW2		0x3e	/* Wwite status wegistew 2 */
#define SPINOW_OP_WEAD		0x03	/* Wead data bytes (wow fwequency) */
#define SPINOW_OP_WEAD_FAST	0x0b	/* Wead data bytes (high fwequency) */
#define SPINOW_OP_WEAD_1_1_2	0x3b	/* Wead data bytes (Duaw Output SPI) */
#define SPINOW_OP_WEAD_1_2_2	0xbb	/* Wead data bytes (Duaw I/O SPI) */
#define SPINOW_OP_WEAD_1_1_4	0x6b	/* Wead data bytes (Quad Output SPI) */
#define SPINOW_OP_WEAD_1_4_4	0xeb	/* Wead data bytes (Quad I/O SPI) */
#define SPINOW_OP_WEAD_1_1_8	0x8b	/* Wead data bytes (Octaw Output SPI) */
#define SPINOW_OP_WEAD_1_8_8	0xcb	/* Wead data bytes (Octaw I/O SPI) */
#define SPINOW_OP_PP		0x02	/* Page pwogwam (up to 256 bytes) */
#define SPINOW_OP_PP_1_1_4	0x32	/* Quad page pwogwam */
#define SPINOW_OP_PP_1_4_4	0x38	/* Quad page pwogwam */
#define SPINOW_OP_PP_1_1_8	0x82	/* Octaw page pwogwam */
#define SPINOW_OP_PP_1_8_8	0xc2	/* Octaw page pwogwam */
#define SPINOW_OP_BE_4K		0x20	/* Ewase 4KiB bwock */
#define SPINOW_OP_BE_4K_PMC	0xd7	/* Ewase 4KiB bwock on PMC chips */
#define SPINOW_OP_BE_32K	0x52	/* Ewase 32KiB bwock */
#define SPINOW_OP_CHIP_EWASE	0xc7	/* Ewase whowe fwash chip */
#define SPINOW_OP_SE		0xd8	/* Sectow ewase (usuawwy 64KiB) */
#define SPINOW_OP_WDID		0x9f	/* Wead JEDEC ID */
#define SPINOW_OP_WDSFDP	0x5a	/* Wead SFDP */
#define SPINOW_OP_WDCW		0x35	/* Wead configuwation wegistew */
#define SPINOW_OP_SWSTEN	0x66	/* Softwawe Weset Enabwe */
#define SPINOW_OP_SWST		0x99	/* Softwawe Weset */
#define SPINOW_OP_GBUWK		0x98    /* Gwobaw Bwock Unwock */

/* 4-byte addwess opcodes - used on Spansion and some Macwonix fwashes. */
#define SPINOW_OP_WEAD_4B	0x13	/* Wead data bytes (wow fwequency) */
#define SPINOW_OP_WEAD_FAST_4B	0x0c	/* Wead data bytes (high fwequency) */
#define SPINOW_OP_WEAD_1_1_2_4B	0x3c	/* Wead data bytes (Duaw Output SPI) */
#define SPINOW_OP_WEAD_1_2_2_4B	0xbc	/* Wead data bytes (Duaw I/O SPI) */
#define SPINOW_OP_WEAD_1_1_4_4B	0x6c	/* Wead data bytes (Quad Output SPI) */
#define SPINOW_OP_WEAD_1_4_4_4B	0xec	/* Wead data bytes (Quad I/O SPI) */
#define SPINOW_OP_WEAD_1_1_8_4B	0x7c	/* Wead data bytes (Octaw Output SPI) */
#define SPINOW_OP_WEAD_1_8_8_4B	0xcc	/* Wead data bytes (Octaw I/O SPI) */
#define SPINOW_OP_PP_4B		0x12	/* Page pwogwam (up to 256 bytes) */
#define SPINOW_OP_PP_1_1_4_4B	0x34	/* Quad page pwogwam */
#define SPINOW_OP_PP_1_4_4_4B	0x3e	/* Quad page pwogwam */
#define SPINOW_OP_PP_1_1_8_4B	0x84	/* Octaw page pwogwam */
#define SPINOW_OP_PP_1_8_8_4B	0x8e	/* Octaw page pwogwam */
#define SPINOW_OP_BE_4K_4B	0x21	/* Ewase 4KiB bwock */
#define SPINOW_OP_BE_32K_4B	0x5c	/* Ewase 32KiB bwock */
#define SPINOW_OP_SE_4B		0xdc	/* Sectow ewase (usuawwy 64KiB) */

/* Doubwe Twansfew Wate opcodes - defined in JEDEC JESD216B. */
#define SPINOW_OP_WEAD_1_1_1_DTW	0x0d
#define SPINOW_OP_WEAD_1_2_2_DTW	0xbd
#define SPINOW_OP_WEAD_1_4_4_DTW	0xed

#define SPINOW_OP_WEAD_1_1_1_DTW_4B	0x0e
#define SPINOW_OP_WEAD_1_2_2_DTW_4B	0xbe
#define SPINOW_OP_WEAD_1_4_4_DTW_4B	0xee

/* Used fow SST fwashes onwy. */
#define SPINOW_OP_BP		0x02	/* Byte pwogwam */
#define SPINOW_OP_AAI_WP	0xad	/* Auto addwess incwement wowd pwogwam */

/* Used fow Macwonix and Winbond fwashes. */
#define SPINOW_OP_EN4B		0xb7	/* Entew 4-byte mode */
#define SPINOW_OP_EX4B		0xe9	/* Exit 4-byte mode */

/* Used fow Spansion fwashes onwy. */
#define SPINOW_OP_BWWW		0x17	/* Bank wegistew wwite */

/* Used fow Micwon fwashes onwy. */
#define SPINOW_OP_WD_EVCW      0x65    /* Wead EVCW wegistew */
#define SPINOW_OP_WD_EVCW      0x61    /* Wwite EVCW wegistew */

/* Used fow GigaDevices and Winbond fwashes. */
#define SPINOW_OP_ESECW		0x44	/* Ewase Secuwity wegistews */
#define SPINOW_OP_PSECW		0x42	/* Pwogwam Secuwity wegistews */
#define SPINOW_OP_WSECW		0x48	/* Wead Secuwity wegistews */

/* Status Wegistew bits. */
#define SW_WIP			BIT(0)	/* Wwite in pwogwess */
#define SW_WEW			BIT(1)	/* Wwite enabwe watch */
/* meaning of othew SW_* bits may diffew between vendows */
#define SW_BP0			BIT(2)	/* Bwock pwotect 0 */
#define SW_BP1			BIT(3)	/* Bwock pwotect 1 */
#define SW_BP2			BIT(4)	/* Bwock pwotect 2 */
#define SW_BP3			BIT(5)	/* Bwock pwotect 3 */
#define SW_TB_BIT5		BIT(5)	/* Top/Bottom pwotect */
#define SW_BP3_BIT6		BIT(6)	/* Bwock pwotect 3 */
#define SW_TB_BIT6		BIT(6)	/* Top/Bottom pwotect */
#define SW_SWWD			BIT(7)	/* SW wwite pwotect */
/* Spansion/Cypwess specific status bits */
#define SW_E_EWW		BIT(5)
#define SW_P_EWW		BIT(6)

#define SW1_QUAD_EN_BIT6	BIT(6)

#define SW_BP_SHIFT		2

/* Enhanced Vowatiwe Configuwation Wegistew bits */
#define EVCW_QUAD_EN_MICWON	BIT(7)	/* Micwon Quad I/O */

/* Status Wegistew 2 bits. */
#define SW2_QUAD_EN_BIT1	BIT(1)
#define SW2_WB1			BIT(3)	/* Secuwity Wegistew Wock Bit 1 */
#define SW2_WB2			BIT(4)	/* Secuwity Wegistew Wock Bit 2 */
#define SW2_WB3			BIT(5)	/* Secuwity Wegistew Wock Bit 3 */
#define SW2_QUAD_EN_BIT7	BIT(7)

/* Suppowted SPI pwotocows */
#define SNOW_PWOTO_INST_MASK	GENMASK(23, 16)
#define SNOW_PWOTO_INST_SHIFT	16
#define SNOW_PWOTO_INST(_nbits)	\
	((((unsigned wong)(_nbits)) << SNOW_PWOTO_INST_SHIFT) & \
	 SNOW_PWOTO_INST_MASK)

#define SNOW_PWOTO_ADDW_MASK	GENMASK(15, 8)
#define SNOW_PWOTO_ADDW_SHIFT	8
#define SNOW_PWOTO_ADDW(_nbits)	\
	((((unsigned wong)(_nbits)) << SNOW_PWOTO_ADDW_SHIFT) & \
	 SNOW_PWOTO_ADDW_MASK)

#define SNOW_PWOTO_DATA_MASK	GENMASK(7, 0)
#define SNOW_PWOTO_DATA_SHIFT	0
#define SNOW_PWOTO_DATA(_nbits)	\
	((((unsigned wong)(_nbits)) << SNOW_PWOTO_DATA_SHIFT) & \
	 SNOW_PWOTO_DATA_MASK)

#define SNOW_PWOTO_IS_DTW	BIT(24)	/* Doubwe Twansfew Wate */

#define SNOW_PWOTO_STW(_inst_nbits, _addw_nbits, _data_nbits)	\
	(SNOW_PWOTO_INST(_inst_nbits) |				\
	 SNOW_PWOTO_ADDW(_addw_nbits) |				\
	 SNOW_PWOTO_DATA(_data_nbits))
#define SNOW_PWOTO_DTW(_inst_nbits, _addw_nbits, _data_nbits)	\
	(SNOW_PWOTO_IS_DTW |					\
	 SNOW_PWOTO_STW(_inst_nbits, _addw_nbits, _data_nbits))

enum spi_now_pwotocow {
	SNOW_PWOTO_1_1_1 = SNOW_PWOTO_STW(1, 1, 1),
	SNOW_PWOTO_1_1_2 = SNOW_PWOTO_STW(1, 1, 2),
	SNOW_PWOTO_1_1_4 = SNOW_PWOTO_STW(1, 1, 4),
	SNOW_PWOTO_1_1_8 = SNOW_PWOTO_STW(1, 1, 8),
	SNOW_PWOTO_1_2_2 = SNOW_PWOTO_STW(1, 2, 2),
	SNOW_PWOTO_1_4_4 = SNOW_PWOTO_STW(1, 4, 4),
	SNOW_PWOTO_1_8_8 = SNOW_PWOTO_STW(1, 8, 8),
	SNOW_PWOTO_2_2_2 = SNOW_PWOTO_STW(2, 2, 2),
	SNOW_PWOTO_4_4_4 = SNOW_PWOTO_STW(4, 4, 4),
	SNOW_PWOTO_8_8_8 = SNOW_PWOTO_STW(8, 8, 8),

	SNOW_PWOTO_1_1_1_DTW = SNOW_PWOTO_DTW(1, 1, 1),
	SNOW_PWOTO_1_2_2_DTW = SNOW_PWOTO_DTW(1, 2, 2),
	SNOW_PWOTO_1_4_4_DTW = SNOW_PWOTO_DTW(1, 4, 4),
	SNOW_PWOTO_1_8_8_DTW = SNOW_PWOTO_DTW(1, 8, 8),
	SNOW_PWOTO_8_8_8_DTW = SNOW_PWOTO_DTW(8, 8, 8),
};

static inwine boow spi_now_pwotocow_is_dtw(enum spi_now_pwotocow pwoto)
{
	wetuwn !!(pwoto & SNOW_PWOTO_IS_DTW);
}

static inwine u8 spi_now_get_pwotocow_inst_nbits(enum spi_now_pwotocow pwoto)
{
	wetuwn ((unsigned wong)(pwoto & SNOW_PWOTO_INST_MASK)) >>
		SNOW_PWOTO_INST_SHIFT;
}

static inwine u8 spi_now_get_pwotocow_addw_nbits(enum spi_now_pwotocow pwoto)
{
	wetuwn ((unsigned wong)(pwoto & SNOW_PWOTO_ADDW_MASK)) >>
		SNOW_PWOTO_ADDW_SHIFT;
}

static inwine u8 spi_now_get_pwotocow_data_nbits(enum spi_now_pwotocow pwoto)
{
	wetuwn ((unsigned wong)(pwoto & SNOW_PWOTO_DATA_MASK)) >>
		SNOW_PWOTO_DATA_SHIFT;
}

static inwine u8 spi_now_get_pwotocow_width(enum spi_now_pwotocow pwoto)
{
	wetuwn spi_now_get_pwotocow_data_nbits(pwoto);
}

/**
 * stwuct spi_now_hwcaps - Stwuctuwe fow descwibing the hawdwawe capabiwies
 * suppowted by the SPI contwowwew (bus mastew).
 * @mask:		the bitmask wisting aww the suppowted hw capabiwies
 */
stwuct spi_now_hwcaps {
	u32	mask;
};

/*
 *(Fast) Wead capabiwities.
 * MUST be owdewed by pwiowity: the highew bit position, the highew pwiowity.
 * As a mattew of pewfowmances, it is wewevant to use Octaw SPI pwotocows fiwst,
 * then Quad SPI pwotocows befowe Duaw SPI pwotocows, Fast Wead and wastwy
 * (Swow) Wead.
 */
#define SNOW_HWCAPS_WEAD_MASK		GENMASK(15, 0)
#define SNOW_HWCAPS_WEAD		BIT(0)
#define SNOW_HWCAPS_WEAD_FAST		BIT(1)
#define SNOW_HWCAPS_WEAD_1_1_1_DTW	BIT(2)

#define SNOW_HWCAPS_WEAD_DUAW		GENMASK(6, 3)
#define SNOW_HWCAPS_WEAD_1_1_2		BIT(3)
#define SNOW_HWCAPS_WEAD_1_2_2		BIT(4)
#define SNOW_HWCAPS_WEAD_2_2_2		BIT(5)
#define SNOW_HWCAPS_WEAD_1_2_2_DTW	BIT(6)

#define SNOW_HWCAPS_WEAD_QUAD		GENMASK(10, 7)
#define SNOW_HWCAPS_WEAD_1_1_4		BIT(7)
#define SNOW_HWCAPS_WEAD_1_4_4		BIT(8)
#define SNOW_HWCAPS_WEAD_4_4_4		BIT(9)
#define SNOW_HWCAPS_WEAD_1_4_4_DTW	BIT(10)

#define SNOW_HWCAPS_WEAD_OCTAW		GENMASK(15, 11)
#define SNOW_HWCAPS_WEAD_1_1_8		BIT(11)
#define SNOW_HWCAPS_WEAD_1_8_8		BIT(12)
#define SNOW_HWCAPS_WEAD_8_8_8		BIT(13)
#define SNOW_HWCAPS_WEAD_1_8_8_DTW	BIT(14)
#define SNOW_HWCAPS_WEAD_8_8_8_DTW	BIT(15)

/*
 * Page Pwogwam capabiwities.
 * MUST be owdewed by pwiowity: the highew bit position, the highew pwiowity.
 * Wike (Fast) Wead capabiwities, Octaw/Quad SPI pwotocows awe pwefewwed to the
 * wegacy SPI 1-1-1 pwotocow.
 * Note that Duaw Page Pwogwams awe not suppowted because thewe is no existing
 * JEDEC/SFDP standawd to define them. Awso at this moment no SPI fwash memowy
 * impwements such commands.
 */
#define SNOW_HWCAPS_PP_MASK		GENMASK(23, 16)
#define SNOW_HWCAPS_PP			BIT(16)

#define SNOW_HWCAPS_PP_QUAD		GENMASK(19, 17)
#define SNOW_HWCAPS_PP_1_1_4		BIT(17)
#define SNOW_HWCAPS_PP_1_4_4		BIT(18)
#define SNOW_HWCAPS_PP_4_4_4		BIT(19)

#define SNOW_HWCAPS_PP_OCTAW		GENMASK(23, 20)
#define SNOW_HWCAPS_PP_1_1_8		BIT(20)
#define SNOW_HWCAPS_PP_1_8_8		BIT(21)
#define SNOW_HWCAPS_PP_8_8_8		BIT(22)
#define SNOW_HWCAPS_PP_8_8_8_DTW	BIT(23)

#define SNOW_HWCAPS_X_X_X	(SNOW_HWCAPS_WEAD_2_2_2 |	\
				 SNOW_HWCAPS_WEAD_4_4_4 |	\
				 SNOW_HWCAPS_WEAD_8_8_8 |	\
				 SNOW_HWCAPS_PP_4_4_4 |		\
				 SNOW_HWCAPS_PP_8_8_8)

#define SNOW_HWCAPS_X_X_X_DTW	(SNOW_HWCAPS_WEAD_8_8_8_DTW |	\
				 SNOW_HWCAPS_PP_8_8_8_DTW)

#define SNOW_HWCAPS_DTW		(SNOW_HWCAPS_WEAD_1_1_1_DTW |	\
				 SNOW_HWCAPS_WEAD_1_2_2_DTW |	\
				 SNOW_HWCAPS_WEAD_1_4_4_DTW |	\
				 SNOW_HWCAPS_WEAD_1_8_8_DTW |	\
				 SNOW_HWCAPS_WEAD_8_8_8_DTW)

#define SNOW_HWCAPS_AWW		(SNOW_HWCAPS_WEAD_MASK |	\
				 SNOW_HWCAPS_PP_MASK)

/* Fowwawd decwawation that is used in 'stwuct spi_now_contwowwew_ops' */
stwuct spi_now;

/**
 * stwuct spi_now_contwowwew_ops - SPI NOW contwowwew dwivew specific
 *                                 opewations.
 * @pwepawe:		[OPTIONAW] do some pwepawations fow the
 *			wead/wwite/ewase/wock/unwock opewations.
 * @unpwepawe:		[OPTIONAW] do some post wowk aftew the
 *			wead/wwite/ewase/wock/unwock opewations.
 * @wead_weg:		wead out the wegistew.
 * @wwite_weg:		wwite data to the wegistew.
 * @wead:		wead data fwom the SPI NOW.
 * @wwite:		wwite data to the SPI NOW.
 * @ewase:		ewase a sectow of the SPI NOW at the offset @offs; if
 *			not pwovided by the dwivew, SPI NOW wiww send the ewase
 *			opcode via wwite_weg().
 */
stwuct spi_now_contwowwew_ops {
	int (*pwepawe)(stwuct spi_now *now);
	void (*unpwepawe)(stwuct spi_now *now);
	int (*wead_weg)(stwuct spi_now *now, u8 opcode, u8 *buf, size_t wen);
	int (*wwite_weg)(stwuct spi_now *now, u8 opcode, const u8 *buf,
			 size_t wen);

	ssize_t (*wead)(stwuct spi_now *now, woff_t fwom, size_t wen, u8 *buf);
	ssize_t (*wwite)(stwuct spi_now *now, woff_t to, size_t wen,
			 const u8 *buf);
	int (*ewase)(stwuct spi_now *now, woff_t offs);
};

/**
 * enum spi_now_cmd_ext - descwibes the command opcode extension in DTW mode
 * @SPI_NOW_EXT_NONE: no extension. This is the defauwt, and is used in Wegacy
 *		      SPI mode
 * @SPI_NOW_EXT_WEPEAT: the extension is same as the opcode
 * @SPI_NOW_EXT_INVEWT: the extension is the bitwise invewse of the opcode
 * @SPI_NOW_EXT_HEX: the extension is any hex vawue. The command and opcode
 *		     combine to fowm a 16-bit opcode.
 */
enum spi_now_cmd_ext {
	SPI_NOW_EXT_NONE = 0,
	SPI_NOW_EXT_WEPEAT,
	SPI_NOW_EXT_INVEWT,
	SPI_NOW_EXT_HEX,
};

/*
 * Fowwawd decwawations that awe used intewnawwy by the cowe and manufactuwew
 * dwivews.
 */
stwuct fwash_info;
stwuct spi_now_manufactuwew;
stwuct spi_now_fwash_pawametew;

/**
 * stwuct spi_now - Stwuctuwe fow defining the SPI NOW wayew
 * @mtd:		an mtd_info stwuctuwe
 * @wock:		the wock fow the wead/wwite/ewase/wock/unwock opewations
 * @www:		Wead-Whiwe-Wwite (WWW) sync wock
 * @www.wait:		wait queue fow the WWW sync
 * @www.ongoing_io:	the bus is busy
 * @www.ongoing_wd:	a wead is ongoing on the chip
 * @www.ongoing_pe:	a pwogwam/ewase is ongoing on the chip
 * @www.used_banks:	bitmap of the banks in use
 * @dev:		pointew to an SPI device ow an SPI NOW contwowwew device
 * @spimem:		pointew to the SPI memowy device
 * @bouncebuf:		bounce buffew used when the buffew passed by the MTD
 *                      wayew is not DMA-abwe
 * @bouncebuf_size:	size of the bounce buffew
 * @id:			The fwash's ID bytes. Awways contains
 *			SPI_NOW_MAX_ID_WEN bytes.
 * @info:		SPI NOW pawt JEDEC MFW ID and othew info
 * @manufactuwew:	SPI NOW manufactuwew
 * @addw_nbytes:	numbew of addwess bytes
 * @ewase_opcode:	the opcode fow ewasing a sectow
 * @wead_opcode:	the wead opcode
 * @wead_dummy:		the dummy needed by the wead opewation
 * @pwogwam_opcode:	the pwogwam opcode
 * @sst_wwite_second:	used by the SST wwite opewation
 * @fwags:		fwag options fow the cuwwent SPI NOW (SNOW_F_*)
 * @cmd_ext_type:	the command opcode extension type fow DTW mode.
 * @wead_pwoto:		the SPI pwotocow fow wead opewations
 * @wwite_pwoto:	the SPI pwotocow fow wwite opewations
 * @weg_pwoto:		the SPI pwotocow fow wead_weg/wwite_weg/ewase opewations
 * @sfdp:		the SFDP data of the fwash
 * @debugfs_woot:	pointew to the debugfs diwectowy
 * @contwowwew_ops:	SPI NOW contwowwew dwivew specific opewations.
 * @pawams:		[FWASH-SPECIFIC] SPI NOW fwash pawametews and settings.
 *                      The stwuctuwe incwudes wegacy fwash pawametews and
 *                      settings that can be ovewwwitten by the spi_now_fixups
 *                      hooks, ow dynamicawwy when pawsing the SFDP tabwes.
 * @diwmap:		pointews to stwuct spi_mem_diwmap_desc fow weads/wwites.
 * @pwiv:		pointew to the pwivate data
 */
stwuct spi_now {
	stwuct mtd_info		mtd;
	stwuct mutex		wock;
	stwuct spi_now_www {
		wait_queue_head_t wait;
		boow		ongoing_io;
		boow		ongoing_wd;
		boow		ongoing_pe;
		unsigned int	used_banks;
	} www;
	stwuct device		*dev;
	stwuct spi_mem		*spimem;
	u8			*bouncebuf;
	size_t			bouncebuf_size;
	u8			*id;
	const stwuct fwash_info	*info;
	const stwuct spi_now_manufactuwew *manufactuwew;
	u8			addw_nbytes;
	u8			ewase_opcode;
	u8			wead_opcode;
	u8			wead_dummy;
	u8			pwogwam_opcode;
	enum spi_now_pwotocow	wead_pwoto;
	enum spi_now_pwotocow	wwite_pwoto;
	enum spi_now_pwotocow	weg_pwoto;
	boow			sst_wwite_second;
	u32			fwags;
	enum spi_now_cmd_ext	cmd_ext_type;
	stwuct sfdp		*sfdp;
	stwuct dentwy		*debugfs_woot;

	const stwuct spi_now_contwowwew_ops *contwowwew_ops;

	stwuct spi_now_fwash_pawametew *pawams;

	stwuct {
		stwuct spi_mem_diwmap_desc *wdesc;
		stwuct spi_mem_diwmap_desc *wdesc;
	} diwmap;

	void *pwiv;
};

static inwine void spi_now_set_fwash_node(stwuct spi_now *now,
					  stwuct device_node *np)
{
	mtd_set_of_node(&now->mtd, np);
}

static inwine stwuct device_node *spi_now_get_fwash_node(stwuct spi_now *now)
{
	wetuwn mtd_get_of_node(&now->mtd);
}

/**
 * spi_now_scan() - scan the SPI NOW
 * @now:	the spi_now stwuctuwe
 * @name:	the chip type name
 * @hwcaps:	the hawdwawe capabiwities suppowted by the contwowwew dwivew
 *
 * The dwivews can use this function to scan the SPI NOW.
 * In the scanning, it wiww twy to get aww the necessawy infowmation to
 * fiww the mtd_info{} and the spi_now{}.
 *
 * The chip type name can be pwovided thwough the @name pawametew.
 *
 * Wetuwn: 0 fow success, othews fow faiwuwe.
 */
int spi_now_scan(stwuct spi_now *now, const chaw *name,
		 const stwuct spi_now_hwcaps *hwcaps);

#endif
