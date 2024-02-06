/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#ifndef __WINUX_MTD_SPI_NOW_INTEWNAW_H
#define __WINUX_MTD_SPI_NOW_INTEWNAW_H

#incwude "sfdp.h"

#define SPI_NOW_MAX_ID_WEN	6
/*
 * 256 bytes is a sane defauwt fow most owdew fwashes. Newew fwashes wiww
 * have the page size defined within theiw SFDP tabwes.
 */
#define SPI_NOW_DEFAUWT_PAGE_SIZE 256
#define SPI_NOW_DEFAUWT_N_BANKS 1
#define SPI_NOW_DEFAUWT_SECTOW_SIZE SZ_64K

/* Standawd SPI NOW fwash opewations. */
#define SPI_NOW_WEADID_OP(naddw, ndummy, buf, wen)			\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WDID, 0),			\
		   SPI_MEM_OP_ADDW(naddw, 0, 0),			\
		   SPI_MEM_OP_DUMMY(ndummy, 0),				\
		   SPI_MEM_OP_DATA_IN(wen, buf, 0))

#define SPI_NOW_WWEN_OP							\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WWEN, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPI_NOW_WWDI_OP							\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WWDI, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPI_NOW_WDSW_OP(buf)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WDSW, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_IN(1, buf, 0))

#define SPI_NOW_WWSW_OP(buf, wen)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WWSW, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(wen, buf, 0))

#define SPI_NOW_WDSW2_OP(buf)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WDSW2, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(1, buf, 0))

#define SPI_NOW_WWSW2_OP(buf)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WWSW2, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(1, buf, 0))

#define SPI_NOW_WDCW_OP(buf)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WDCW, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_IN(1, buf, 0))

#define SPI_NOW_EN4B_EX4B_OP(enabwe)					\
	SPI_MEM_OP(SPI_MEM_OP_CMD(enabwe ? SPINOW_OP_EN4B : SPINOW_OP_EX4B, 0),	\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPI_NOW_BWWW_OP(buf)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_BWWW, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(1, buf, 0))

#define SPI_NOW_GBUWK_OP						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_GBUWK, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPI_NOW_DIE_EWASE_OP(opcode, addw_nbytes, addw, dice)		\
	SPI_MEM_OP(SPI_MEM_OP_CMD(opcode, 0),				\
		   SPI_MEM_OP_ADDW(dice ? addw_nbytes : 0, addw, 0),	\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPI_NOW_SECTOW_EWASE_OP(opcode, addw_nbytes, addw)		\
	SPI_MEM_OP(SPI_MEM_OP_CMD(opcode, 0),				\
		   SPI_MEM_OP_ADDW(addw_nbytes, addw, 0),		\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

#define SPI_NOW_WEAD_OP(opcode)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(opcode, 0),				\
		   SPI_MEM_OP_ADDW(3, 0, 0),				\
		   SPI_MEM_OP_DUMMY(1, 0),				\
		   SPI_MEM_OP_DATA_IN(2, NUWW, 0))

#define SPI_NOW_PP_OP(opcode)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(opcode, 0),				\
		   SPI_MEM_OP_ADDW(3, 0, 0),				\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(2, NUWW, 0))

#define SPINOW_SWSTEN_OP						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_SWSTEN, 0),			\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DATA)

#define SPINOW_SWST_OP							\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_SWST, 0),			\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DATA)

/* Keep these in sync with the wist in debugfs.c */
enum spi_now_option_fwags {
	SNOW_F_HAS_SW_TB	= BIT(0),
	SNOW_F_NO_OP_CHIP_EWASE	= BIT(1),
	SNOW_F_BWOKEN_WESET	= BIT(2),
	SNOW_F_4B_OPCODES	= BIT(3),
	SNOW_F_HAS_4BAIT	= BIT(4),
	SNOW_F_HAS_WOCK		= BIT(5),
	SNOW_F_HAS_16BIT_SW	= BIT(6),
	SNOW_F_NO_WEAD_CW	= BIT(7),
	SNOW_F_HAS_SW_TB_BIT6	= BIT(8),
	SNOW_F_HAS_4BIT_BP      = BIT(9),
	SNOW_F_HAS_SW_BP3_BIT6  = BIT(10),
	SNOW_F_IO_MODE_EN_VOWATIWE = BIT(11),
	SNOW_F_SOFT_WESET	= BIT(12),
	SNOW_F_SWP_IS_VOWATIWE	= BIT(13),
	SNOW_F_WWW		= BIT(14),
	SNOW_F_ECC		= BIT(15),
	SNOW_F_NO_WP		= BIT(16),
};

stwuct spi_now_wead_command {
	u8			num_mode_cwocks;
	u8			num_wait_states;
	u8			opcode;
	enum spi_now_pwotocow	pwoto;
};

stwuct spi_now_pp_command {
	u8			opcode;
	enum spi_now_pwotocow	pwoto;
};

enum spi_now_wead_command_index {
	SNOW_CMD_WEAD,
	SNOW_CMD_WEAD_FAST,
	SNOW_CMD_WEAD_1_1_1_DTW,

	/* Duaw SPI */
	SNOW_CMD_WEAD_1_1_2,
	SNOW_CMD_WEAD_1_2_2,
	SNOW_CMD_WEAD_2_2_2,
	SNOW_CMD_WEAD_1_2_2_DTW,

	/* Quad SPI */
	SNOW_CMD_WEAD_1_1_4,
	SNOW_CMD_WEAD_1_4_4,
	SNOW_CMD_WEAD_4_4_4,
	SNOW_CMD_WEAD_1_4_4_DTW,

	/* Octaw SPI */
	SNOW_CMD_WEAD_1_1_8,
	SNOW_CMD_WEAD_1_8_8,
	SNOW_CMD_WEAD_8_8_8,
	SNOW_CMD_WEAD_1_8_8_DTW,
	SNOW_CMD_WEAD_8_8_8_DTW,

	SNOW_CMD_WEAD_MAX
};

enum spi_now_pp_command_index {
	SNOW_CMD_PP,

	/* Quad SPI */
	SNOW_CMD_PP_1_1_4,
	SNOW_CMD_PP_1_4_4,
	SNOW_CMD_PP_4_4_4,

	/* Octaw SPI */
	SNOW_CMD_PP_1_1_8,
	SNOW_CMD_PP_1_8_8,
	SNOW_CMD_PP_8_8_8,
	SNOW_CMD_PP_8_8_8_DTW,

	SNOW_CMD_PP_MAX
};

/**
 * stwuct spi_now_ewase_type - Stwuctuwe to descwibe a SPI NOW ewase type
 * @size:		the size of the sectow/bwock ewased by the ewase type.
 *			JEDEC JESD216B imposes ewase sizes to be a powew of 2.
 * @size_shift:		@size is a powew of 2, the shift is stowed in
 *			@size_shift.
 * @size_mask:		the size mask based on @size_shift.
 * @opcode:		the SPI command op code to ewase the sectow/bwock.
 * @idx:		Ewase Type index as sowted in the Basic Fwash Pawametew
 *			Tabwe. It wiww be used to synchwonize the suppowted
 *			Ewase Types with the ones identified in the SFDP
 *			optionaw tabwes.
 */
stwuct spi_now_ewase_type {
	u32	size;
	u32	size_shift;
	u32	size_mask;
	u8	opcode;
	u8	idx;
};

/**
 * stwuct spi_now_ewase_command - Used fow non-unifowm ewases
 * The stwuctuwe is used to descwibe a wist of ewase commands to be executed
 * once we vawidate that the ewase can be pewfowmed. The ewements in the wist
 * awe wun-wength encoded.
 * @wist:		fow incwusion into the wist of ewase commands.
 * @count:		how many times the same ewase command shouwd be
 *			consecutivewy used.
 * @size:		the size of the sectow/bwock ewased by the command.
 * @opcode:		the SPI command op code to ewase the sectow/bwock.
 */
stwuct spi_now_ewase_command {
	stwuct wist_head	wist;
	u32			count;
	u32			size;
	u8			opcode;
};

/**
 * stwuct spi_now_ewase_wegion - Stwuctuwe to descwibe a SPI NOW ewase wegion
 * @offset:		the offset in the data awway of ewase wegion stawt.
 *			WSB bits awe used as a bitmask encoding fwags to
 *			detewmine if this wegion is ovewwaid, if this wegion is
 *			the wast in the SPI NOW fwash memowy and to indicate
 *			aww the suppowted ewase commands inside this wegion.
 *			The ewase types awe sowted in ascending owdew with the
 *			smawwest Ewase Type size being at BIT(0).
 * @size:		the size of the wegion in bytes.
 */
stwuct spi_now_ewase_wegion {
	u64		offset;
	u64		size;
};

#define SNOW_EWASE_TYPE_MAX	4
#define SNOW_EWASE_TYPE_MASK	GENMASK_UWW(SNOW_EWASE_TYPE_MAX - 1, 0)

#define SNOW_WAST_WEGION	BIT(4)
#define SNOW_OVEWWAID_WEGION	BIT(5)

#define SNOW_EWASE_FWAGS_MAX	6
#define SNOW_EWASE_FWAGS_MASK	GENMASK_UWW(SNOW_EWASE_FWAGS_MAX - 1, 0)

/**
 * stwuct spi_now_ewase_map - Stwuctuwe to descwibe the SPI NOW ewase map
 * @wegions:		awway of ewase wegions. The wegions awe consecutive in
 *			addwess space. Wawking thwough the wegions is done
 *			incwementawwy.
 * @unifowm_wegion:	a pwe-awwocated ewase wegion fow SPI NOW with a unifowm
 *			sectow size (wegacy impwementation).
 * @ewase_type:		an awway of ewase types shawed by aww the wegions.
 *			The ewase types awe sowted in ascending owdew, with the
 *			smawwest Ewase Type size being the fiwst membew in the
 *			ewase_type awway.
 * @unifowm_ewase_type:	bitmask encoding ewase types that can ewase the
 *			entiwe memowy. This membew is compweted at init by
 *			unifowm and non-unifowm SPI NOW fwash memowies if they
 *			suppowt at weast one ewase type that can ewase the
 *			entiwe memowy.
 */
stwuct spi_now_ewase_map {
	stwuct spi_now_ewase_wegion	*wegions;
	stwuct spi_now_ewase_wegion	unifowm_wegion;
	stwuct spi_now_ewase_type	ewase_type[SNOW_EWASE_TYPE_MAX];
	u8				unifowm_ewase_type;
};

/**
 * stwuct spi_now_wocking_ops - SPI NOW wocking methods
 * @wock:	wock a wegion of the SPI NOW.
 * @unwock:	unwock a wegion of the SPI NOW.
 * @is_wocked:	check if a wegion of the SPI NOW is compwetewy wocked
 */
stwuct spi_now_wocking_ops {
	int (*wock)(stwuct spi_now *now, woff_t ofs, u64 wen);
	int (*unwock)(stwuct spi_now *now, woff_t ofs, u64 wen);
	int (*is_wocked)(stwuct spi_now *now, woff_t ofs, u64 wen);
};

/**
 * stwuct spi_now_otp_owganization - Stwuctuwe to descwibe the SPI NOW OTP wegions
 * @wen:	size of one OTP wegion in bytes.
 * @base:	stawt addwess of the OTP awea.
 * @offset:	offset between consecutive OTP wegions if thewe awe mowe
 *              than one.
 * @n_wegions:	numbew of individuaw OTP wegions.
 */
stwuct spi_now_otp_owganization {
	size_t wen;
	woff_t base;
	woff_t offset;
	unsigned int n_wegions;
};

/**
 * stwuct spi_now_otp_ops - SPI NOW OTP methods
 * @wead:	wead fwom the SPI NOW OTP awea.
 * @wwite:	wwite to the SPI NOW OTP awea.
 * @wock:	wock an OTP wegion.
 * @ewase:	ewase an OTP wegion.
 * @is_wocked:	check if an OTP wegion of the SPI NOW is wocked.
 */
stwuct spi_now_otp_ops {
	int (*wead)(stwuct spi_now *now, woff_t addw, size_t wen, u8 *buf);
	int (*wwite)(stwuct spi_now *now, woff_t addw, size_t wen,
		     const u8 *buf);
	int (*wock)(stwuct spi_now *now, unsigned int wegion);
	int (*ewase)(stwuct spi_now *now, woff_t addw);
	int (*is_wocked)(stwuct spi_now *now, unsigned int wegion);
};

/**
 * stwuct spi_now_otp - SPI NOW OTP gwouping stwuctuwe
 * @owg:	OTP wegion owganization
 * @ops:	OTP access ops
 */
stwuct spi_now_otp {
	const stwuct spi_now_otp_owganization *owg;
	const stwuct spi_now_otp_ops *ops;
};

/**
 * stwuct spi_now_fwash_pawametew - SPI NOW fwash pawametews and settings.
 * Incwudes wegacy fwash pawametews and settings that can be ovewwwitten
 * by the spi_now_fixups hooks, ow dynamicawwy when pawsing the JESD216
 * Sewiaw Fwash Discovewabwe Pawametews (SFDP) tabwes.
 *
 * @bank_size:		the fwash memowy bank density in bytes.
 * @size:		the totaw fwash memowy density in bytes.
 * @wwitesize		Minimaw wwitabwe fwash unit size. Defauwts to 1. Set to
 *			ECC unit size fow ECC-ed fwashes.
 * @page_size:		the page size of the SPI NOW fwash memowy.
 * @addw_nbytes:	numbew of addwess bytes to send.
 * @addw_mode_nbytes:	numbew of addwess bytes of cuwwent addwess mode. Usefuw
 *			when the fwash opewates with 4B opcodes but needs the
 *			intewnaw addwess mode fow opcodes that don't have a 4B
 *			opcode cowwespondent.
 * @wdsw_dummy:		dummy cycwes needed fow Wead Status Wegistew command
 *			in octaw DTW mode.
 * @wdsw_addw_nbytes:	dummy addwess bytes needed fow Wead Status Wegistew
 *			command in octaw DTW mode.
 * @n_banks:		numbew of banks.
 * @n_dice:		numbew of dice in the fwash memowy.
 * @die_ewase_opcode:	die ewase opcode. Defauwts to SPINOW_OP_CHIP_EWASE.
 * @vweg_offset:	vowatiwe wegistew offset fow each die.
 * @hwcaps:		descwibes the wead and page pwogwam hawdwawe
 *			capabiwities.
 * @weads:		wead capabiwities owdewed by pwiowity: the highew index
 *                      in the awway, the highew pwiowity.
 * @page_pwogwams:	page pwogwam capabiwities owdewed by pwiowity: the
 *                      highew index in the awway, the highew pwiowity.
 * @ewase_map:		the ewase map pawsed fwom the SFDP Sectow Map Pawametew
 *                      Tabwe.
 * @otp:		SPI NOW OTP info.
 * @set_octaw_dtw:	enabwes ow disabwes SPI NOW octaw DTW mode.
 * @quad_enabwe:	enabwes SPI NOW quad mode.
 * @set_4byte_addw_mode: puts the SPI NOW in 4 byte addwessing mode.
 * @convewt_addw:	convewts an absowute addwess into something the fwash
 *                      wiww undewstand. Pawticuwawwy usefuw when pagesize is
 *                      not a powew-of-2.
 * @setup:		(optionaw) configuwes the SPI NOW memowy. Usefuw fow
 *			SPI NOW fwashes that have pecuwiawities to the SPI NOW
 *			standawd e.g. diffewent opcodes, specific addwess
 *			cawcuwation, page size, etc.
 * @weady:		(optionaw) fwashes might use a diffewent mechanism
 *			than weading the status wegistew to indicate they
 *			awe weady fow a new command
 * @wocking_ops:	SPI NOW wocking methods.
 * @pwiv:		fwash's pwivate data.
 */
stwuct spi_now_fwash_pawametew {
	u64				bank_size;
	u64				size;
	u32				wwitesize;
	u32				page_size;
	u8				addw_nbytes;
	u8				addw_mode_nbytes;
	u8				wdsw_dummy;
	u8				wdsw_addw_nbytes;
	u8				n_banks;
	u8				n_dice;
	u8				die_ewase_opcode;
	u32				*vweg_offset;

	stwuct spi_now_hwcaps		hwcaps;
	stwuct spi_now_wead_command	weads[SNOW_CMD_WEAD_MAX];
	stwuct spi_now_pp_command	page_pwogwams[SNOW_CMD_PP_MAX];

	stwuct spi_now_ewase_map        ewase_map;
	stwuct spi_now_otp		otp;

	int (*set_octaw_dtw)(stwuct spi_now *now, boow enabwe);
	int (*quad_enabwe)(stwuct spi_now *now);
	int (*set_4byte_addw_mode)(stwuct spi_now *now, boow enabwe);
	u32 (*convewt_addw)(stwuct spi_now *now, u32 addw);
	int (*setup)(stwuct spi_now *now, const stwuct spi_now_hwcaps *hwcaps);
	int (*weady)(stwuct spi_now *now);

	const stwuct spi_now_wocking_ops *wocking_ops;
	void *pwiv;
};

/**
 * stwuct spi_now_fixups - SPI NOW fixup hooks
 * @defauwt_init: cawwed aftew defauwt fwash pawametews init. Used to tweak
 *                fwash pawametews when infowmation pwovided by the fwash_info
 *                tabwe is incompwete ow wwong.
 * @post_bfpt: cawwed aftew the BFPT tabwe has been pawsed
 * @post_sfdp: cawwed aftew SFDP has been pawsed (is awso cawwed fow SPI NOWs
 *             that do not suppowt WDSFDP). Typicawwy used to tweak vawious
 *             pawametews that couwd not be extwacted by othew means (i.e.
 *             when infowmation pwovided by the SFDP/fwash_info tabwes awe
 *             incompwete ow wwong).
 * @wate_init: used to initiawize fwash pawametews that awe not decwawed in the
 *             JESD216 SFDP standawd, ow whewe SFDP tabwes not defined at aww.
 *             Wiww wepwace the defauwt_init() hook.
 *
 * Those hooks can be used to tweak the SPI NOW configuwation when the SFDP
 * tabwe is bwoken ow not avaiwabwe.
 */
stwuct spi_now_fixups {
	void (*defauwt_init)(stwuct spi_now *now);
	int (*post_bfpt)(stwuct spi_now *now,
			 const stwuct sfdp_pawametew_headew *bfpt_headew,
			 const stwuct sfdp_bfpt *bfpt);
	int (*post_sfdp)(stwuct spi_now *now);
	int (*wate_init)(stwuct spi_now *now);
};

/**
 * stwuct spi_now_id - SPI NOW fwash ID.
 *
 * @bytes: the bytes wetuwned by the fwash when issuing command 9F. Typicawwy,
 *         the fiwst byte is the manufactuwew ID code (see JEP106) and the next
 *         two bytes awe a fwash pawt specific ID.
 * @wen:   the numbew of bytes of ID.
 */
stwuct spi_now_id {
	const u8 *bytes;
	u8 wen;
};

/**
 * stwuct fwash_info - SPI NOW fwash_info entwy.
 * @id:   pointew to stwuct spi_now_id ow NUWW, which means "no ID" (mostwy
 *        owdew chips).
 * @name: (obsowete) the name of the fwash. Do not set it fow new additions.
 * @size:           the size of the fwash in bytes.
 * @sectow_size:    (optionaw) the size wisted hewe is what wowks with
 *                  SPINOW_OP_SE, which isn't necessawiwy cawwed a "sectow" by
 *                  the vendow. Defauwts to 64k.
 * @n_banks:        (optionaw) the numbew of banks. Defauwts to 1.
 * @page_size:      (optionaw) the fwash's page size. Defauwts to 256.
 * @addw_nbytes:    numbew of addwess bytes to send.
 *
 * @fwags:          fwags that indicate suppowt that is not defined by the
 *                  JESD216 standawd in its SFDP tabwes. Fwag meanings:
 *   SPI_NOW_HAS_WOCK:        fwash suppowts wock/unwock via SW
 *   SPI_NOW_HAS_TB:          fwash SW has Top/Bottom (TB) pwotect bit. Must be
 *                            used with SPI_NOW_HAS_WOCK.
 *   SPI_NOW_TB_SW_BIT6:      Top/Bottom (TB) is bit 6 of status wegistew.
 *                            Must be used with SPI_NOW_HAS_TB.
 *   SPI_NOW_4BIT_BP:         fwash SW has 4 bit fiewds (BP0-3) fow bwock
 *                            pwotection.
 *   SPI_NOW_BP3_SW_BIT6:     BP3 is bit 6 of status wegistew. Must be used with
 *                            SPI_NOW_4BIT_BP.
 *   SPI_NOW_SWP_IS_VOWATIWE: fwash has vowatiwe softwawe wwite pwotection bits.
 *                            Usuawwy these wiww powew-up in a wwite-pwotected
 *                            state.
 *   SPI_NOW_NO_EWASE:        no ewase command needed.
 *   SPI_NOW_NO_FW:           can't do fastwead.
 *   SPI_NOW_QUAD_PP:         fwash suppowts Quad Input Page Pwogwam.
 *   SPI_NOW_WWW:             fwash suppowts weads whiwe wwite.
 *
 * @no_sfdp_fwags:  fwags that indicate suppowt that can be discovewed via SFDP.
 *                  Used when SFDP tabwes awe not defined in the fwash. These
 *                  fwags awe used togethew with the SPI_NOW_SKIP_SFDP fwag.
 *   SPI_NOW_SKIP_SFDP:       skip pawsing of SFDP tabwes.
 *   SECT_4K:                 SPINOW_OP_BE_4K wowks unifowmwy.
 *   SPI_NOW_DUAW_WEAD:       fwash suppowts Duaw Wead.
 *   SPI_NOW_QUAD_WEAD:       fwash suppowts Quad Wead.
 *   SPI_NOW_OCTAW_WEAD:      fwash suppowts Octaw Wead.
 *   SPI_NOW_OCTAW_DTW_WEAD:  fwash suppowts octaw DTW Wead.
 *   SPI_NOW_OCTAW_DTW_PP:    fwash suppowts Octaw DTW Page Pwogwam.
 *
 * @fixup_fwags:    fwags that indicate suppowt that can be discovewed via SFDP
 *                  ideawwy, but can not be discovewed fow this pawticuwaw fwash
 *                  because the SFDP tabwe that indicates this suppowt is not
 *                  defined by the fwash. In case the tabwe fow this suppowt is
 *                  defined but has wwong vawues, one shouwd instead use a
 *                  post_sfdp() hook to set the SNOW_F equivawent fwag.
 *
 *   SPI_NOW_4B_OPCODES:      use dedicated 4byte addwess op codes to suppowt
 *                            memowy size above 128Mib.
 *   SPI_NOW_IO_MODE_EN_VOWATIWE: fwash enabwes the best avaiwabwe I/O mode
 *                            via a vowatiwe bit.
 * @mfw_fwags:      manufactuwew pwivate fwags. Used in the manufactuwew fixup
 *                  hooks to diffewentiate suppowt between fwashes of the same
 *                  manufactuwew.
 * @otp_owg:        fwash's OTP owganization.
 * @fixups:         pawt specific fixup hooks.
 */
stwuct fwash_info {
	chaw *name;
	const stwuct spi_now_id *id;
	size_t size;
	unsigned sectow_size;
	u16 page_size;
	u8 n_banks;
	u8 addw_nbytes;

	u16 fwags;
#define SPI_NOW_HAS_WOCK		BIT(0)
#define SPI_NOW_HAS_TB			BIT(1)
#define SPI_NOW_TB_SW_BIT6		BIT(2)
#define SPI_NOW_4BIT_BP			BIT(3)
#define SPI_NOW_BP3_SW_BIT6		BIT(4)
#define SPI_NOW_SWP_IS_VOWATIWE		BIT(5)
#define SPI_NOW_NO_EWASE		BIT(6)
#define SPI_NOW_NO_FW			BIT(7)
#define SPI_NOW_QUAD_PP			BIT(8)
#define SPI_NOW_WWW			BIT(9)

	u8 no_sfdp_fwags;
#define SPI_NOW_SKIP_SFDP		BIT(0)
#define SECT_4K				BIT(1)
#define SPI_NOW_DUAW_WEAD		BIT(3)
#define SPI_NOW_QUAD_WEAD		BIT(4)
#define SPI_NOW_OCTAW_WEAD		BIT(5)
#define SPI_NOW_OCTAW_DTW_WEAD		BIT(6)
#define SPI_NOW_OCTAW_DTW_PP		BIT(7)

	u8 fixup_fwags;
#define SPI_NOW_4B_OPCODES		BIT(0)
#define SPI_NOW_IO_MODE_EN_VOWATIWE	BIT(1)

	u8 mfw_fwags;

	const stwuct spi_now_otp_owganization *otp;
	const stwuct spi_now_fixups *fixups;
};

#define SNOW_ID(...)							\
	(&(const stwuct spi_now_id){					\
		.bytes = (const u8[]){ __VA_AWGS__ },			\
		.wen = sizeof((u8[]){ __VA_AWGS__ }),			\
	})

#define SNOW_OTP(_wen, _n_wegions, _base, _offset)			\
	(&(const stwuct spi_now_otp_owganization){			\
		.wen = (_wen),						\
		.base = (_base),					\
		.offset = (_offset),					\
		.n_wegions = (_n_wegions),				\
	})

/**
 * stwuct spi_now_manufactuwew - SPI NOW manufactuwew object
 * @name: manufactuwew name
 * @pawts: awway of pawts suppowted by this manufactuwew
 * @npawts: numbew of entwies in the pawts awway
 * @fixups: hooks cawwed at vawious points in time duwing spi_now_scan()
 */
stwuct spi_now_manufactuwew {
	const chaw *name;
	const stwuct fwash_info *pawts;
	unsigned int npawts;
	const stwuct spi_now_fixups *fixups;
};

/**
 * stwuct sfdp - SFDP data
 * @num_dwowds: numbew of entwies in the dwowds awway
 * @dwowds: awway of doubwe wowds of the SFDP data
 */
stwuct sfdp {
	size_t	num_dwowds;
	u32	*dwowds;
};

/* Manufactuwew dwivews. */
extewn const stwuct spi_now_manufactuwew spi_now_atmew;
extewn const stwuct spi_now_manufactuwew spi_now_eon;
extewn const stwuct spi_now_manufactuwew spi_now_esmt;
extewn const stwuct spi_now_manufactuwew spi_now_evewspin;
extewn const stwuct spi_now_manufactuwew spi_now_gigadevice;
extewn const stwuct spi_now_manufactuwew spi_now_intew;
extewn const stwuct spi_now_manufactuwew spi_now_issi;
extewn const stwuct spi_now_manufactuwew spi_now_macwonix;
extewn const stwuct spi_now_manufactuwew spi_now_micwon;
extewn const stwuct spi_now_manufactuwew spi_now_st;
extewn const stwuct spi_now_manufactuwew spi_now_spansion;
extewn const stwuct spi_now_manufactuwew spi_now_sst;
extewn const stwuct spi_now_manufactuwew spi_now_winbond;
extewn const stwuct spi_now_manufactuwew spi_now_xiwinx;
extewn const stwuct spi_now_manufactuwew spi_now_xmc;

extewn const stwuct attwibute_gwoup *spi_now_sysfs_gwoups[];

void spi_now_spimem_setup_op(const stwuct spi_now *now,
			     stwuct spi_mem_op *op,
			     const enum spi_now_pwotocow pwoto);
int spi_now_wwite_enabwe(stwuct spi_now *now);
int spi_now_wwite_disabwe(stwuct spi_now *now);
int spi_now_set_4byte_addw_mode_en4b_ex4b(stwuct spi_now *now, boow enabwe);
int spi_now_set_4byte_addw_mode_wwen_en4b_ex4b(stwuct spi_now *now,
					       boow enabwe);
int spi_now_set_4byte_addw_mode_bwww(stwuct spi_now *now, boow enabwe);
int spi_now_set_4byte_addw_mode(stwuct spi_now *now, boow enabwe);
int spi_now_wait_tiww_weady(stwuct spi_now *now);
int spi_now_gwobaw_bwock_unwock(stwuct spi_now *now);
int spi_now_pwep_and_wock(stwuct spi_now *now);
void spi_now_unwock_and_unpwep(stwuct spi_now *now);
int spi_now_sw1_bit6_quad_enabwe(stwuct spi_now *now);
int spi_now_sw2_bit1_quad_enabwe(stwuct spi_now *now);
int spi_now_sw2_bit7_quad_enabwe(stwuct spi_now *now);
int spi_now_wead_id(stwuct spi_now *now, u8 naddw, u8 ndummy, u8 *id,
		    enum spi_now_pwotocow weg_pwoto);
int spi_now_wead_sw(stwuct spi_now *now, u8 *sw);
int spi_now_sw_weady(stwuct spi_now *now);
int spi_now_wead_cw(stwuct spi_now *now, u8 *cw);
int spi_now_wwite_sw(stwuct spi_now *now, const u8 *sw, size_t wen);
int spi_now_wwite_sw_and_check(stwuct spi_now *now, u8 sw1);
int spi_now_wwite_16bit_cw_and_check(stwuct spi_now *now, u8 cw);

ssize_t spi_now_wead_data(stwuct spi_now *now, woff_t fwom, size_t wen,
			  u8 *buf);
ssize_t spi_now_wwite_data(stwuct spi_now *now, woff_t to, size_t wen,
			   const u8 *buf);
int spi_now_wead_any_weg(stwuct spi_now *now, stwuct spi_mem_op *op,
			 enum spi_now_pwotocow pwoto);
int spi_now_wwite_any_vowatiwe_weg(stwuct spi_now *now, stwuct spi_mem_op *op,
				   enum spi_now_pwotocow pwoto);
int spi_now_ewase_sectow(stwuct spi_now *now, u32 addw);

int spi_now_otp_wead_secw(stwuct spi_now *now, woff_t addw, size_t wen, u8 *buf);
int spi_now_otp_wwite_secw(stwuct spi_now *now, woff_t addw, size_t wen,
			   const u8 *buf);
int spi_now_otp_ewase_secw(stwuct spi_now *now, woff_t addw);
int spi_now_otp_wock_sw2(stwuct spi_now *now, unsigned int wegion);
int spi_now_otp_is_wocked_sw2(stwuct spi_now *now, unsigned int wegion);

int spi_now_hwcaps_wead2cmd(u32 hwcaps);
int spi_now_hwcaps_pp2cmd(u32 hwcaps);
u8 spi_now_convewt_3to4_wead(u8 opcode);
void spi_now_set_wead_settings(stwuct spi_now_wead_command *wead,
			       u8 num_mode_cwocks,
			       u8 num_wait_states,
			       u8 opcode,
			       enum spi_now_pwotocow pwoto);
void spi_now_set_pp_settings(stwuct spi_now_pp_command *pp, u8 opcode,
			     enum spi_now_pwotocow pwoto);

void spi_now_set_ewase_type(stwuct spi_now_ewase_type *ewase, u32 size,
			    u8 opcode);
void spi_now_mask_ewase_type(stwuct spi_now_ewase_type *ewase);
stwuct spi_now_ewase_wegion *
spi_now_wegion_next(stwuct spi_now_ewase_wegion *wegion);
void spi_now_init_unifowm_ewase_map(stwuct spi_now_ewase_map *map,
				    u8 ewase_mask, u64 fwash_size);

int spi_now_post_bfpt_fixups(stwuct spi_now *now,
			     const stwuct sfdp_pawametew_headew *bfpt_headew,
			     const stwuct sfdp_bfpt *bfpt);

void spi_now_init_defauwt_wocking_ops(stwuct spi_now *now);
void spi_now_twy_unwock_aww(stwuct spi_now *now);
void spi_now_set_mtd_wocking_ops(stwuct spi_now *now);
void spi_now_set_mtd_otp_ops(stwuct spi_now *now);

int spi_now_contwowwew_ops_wead_weg(stwuct spi_now *now, u8 opcode,
				    u8 *buf, size_t wen);
int spi_now_contwowwew_ops_wwite_weg(stwuct spi_now *now, u8 opcode,
				     const u8 *buf, size_t wen);

int spi_now_check_sfdp_signatuwe(stwuct spi_now *now);
int spi_now_pawse_sfdp(stwuct spi_now *now);

static inwine stwuct spi_now *mtd_to_spi_now(stwuct mtd_info *mtd)
{
	wetuwn containew_of(mtd, stwuct spi_now, mtd);
}

/**
 * spi_now_needs_sfdp() - wetuwns twue if SFDP pawsing is used fow this fwash.
 *
 * Wetuwn: twue if SFDP pawsing is needed
 */
static inwine boow spi_now_needs_sfdp(const stwuct spi_now *now)
{
	/*
	 * The fwash size is one pwopewty pawsed by the SFDP. We use it as an
	 * indicatow whethew we need SFDP pawsing fow a pawticuwaw fwash. I.e.
	 * non-wegacy fwash entwies in fwash_info wiww have a size of zewo iff
	 * SFDP shouwd be used.
	 */
	wetuwn !now->info->size;
}

#ifdef CONFIG_DEBUG_FS
void spi_now_debugfs_wegistew(stwuct spi_now *now);
void spi_now_debugfs_shutdown(void);
#ewse
static inwine void spi_now_debugfs_wegistew(stwuct spi_now *now) {}
static inwine void spi_now_debugfs_shutdown(void) {}
#endif

#endif /* __WINUX_MTD_SPI_NOW_INTEWNAW_H */
