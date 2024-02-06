// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */

#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

/* fwash_info mfw_fwag. Used to wead pwopwietawy FSW wegistew. */
#define USE_FSW		BIT(0)

#define SPINOW_OP_MT_DIE_EWASE	0xc4	/* Chip (die) ewase opcode */
#define SPINOW_OP_WDFSW		0x70	/* Wead fwag status wegistew */
#define SPINOW_OP_CWFSW		0x50	/* Cweaw fwag status wegistew */
#define SPINOW_OP_MT_DTW_WD	0xfd	/* Fast Wead opcode in DTW mode */
#define SPINOW_OP_MT_WD_ANY_WEG	0x85	/* Wead vowatiwe wegistew */
#define SPINOW_OP_MT_WW_ANY_WEG	0x81	/* Wwite vowatiwe wegistew */
#define SPINOW_WEG_MT_CFW0V	0x00	/* Fow setting octaw DTW mode */
#define SPINOW_WEG_MT_CFW1V	0x01	/* Fow setting dummy cycwes */
#define SPINOW_WEG_MT_CFW1V_DEF	0x1f	/* Defauwt dummy cycwes */
#define SPINOW_MT_OCT_DTW	0xe7	/* Enabwe Octaw DTW. */
#define SPINOW_MT_EXSPI		0xff	/* Enabwe Extended SPI (defauwt) */

/* Fwag Status Wegistew bits */
#define FSW_WEADY		BIT(7)	/* Device status, 0 = Busy, 1 = Weady */
#define FSW_E_EWW		BIT(5)	/* Ewase opewation status */
#define FSW_P_EWW		BIT(4)	/* Pwogwam opewation status */
#define FSW_PT_EWW		BIT(1)	/* Pwotection ewwow bit */

/* Micwon ST SPI NOW fwash opewations. */
#define MICWON_ST_NOW_WW_ANY_WEG_OP(naddw, addw, ndata, buf)		\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_MT_WW_ANY_WEG, 0),		\
		   SPI_MEM_OP_ADDW(naddw, addw, 0),			\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_OUT(ndata, buf, 0))

#define MICWON_ST_WDFSW_OP(buf)						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_WDFSW, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_DATA_IN(1, buf, 0))

#define MICWON_ST_CWFSW_OP						\
	SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOW_OP_CWFSW, 0),			\
		   SPI_MEM_OP_NO_ADDW,					\
		   SPI_MEM_OP_NO_DUMMY,					\
		   SPI_MEM_OP_NO_DATA)

static int micwon_st_now_octaw_dtw_en(stwuct spi_now *now)
{
	stwuct spi_mem_op op;
	u8 *buf = now->bouncebuf;
	int wet;
	u8 addw_mode_nbytes = now->pawams->addw_mode_nbytes;

	/* Use 20 dummy cycwes fow memowy awway weads. */
	*buf = 20;
	op = (stwuct spi_mem_op)
		MICWON_ST_NOW_WW_ANY_WEG_OP(addw_mode_nbytes,
					    SPINOW_WEG_MT_CFW1V, 1, buf);
	wet = spi_now_wwite_any_vowatiwe_weg(now, &op, now->weg_pwoto);
	if (wet)
		wetuwn wet;

	buf[0] = SPINOW_MT_OCT_DTW;
	op = (stwuct spi_mem_op)
		MICWON_ST_NOW_WW_ANY_WEG_OP(addw_mode_nbytes,
					    SPINOW_WEG_MT_CFW0V, 1, buf);
	wet = spi_now_wwite_any_vowatiwe_weg(now, &op, now->weg_pwoto);
	if (wet)
		wetuwn wet;

	/* Wead fwash ID to make suwe the switch was successfuw. */
	wet = spi_now_wead_id(now, 0, 8, buf, SNOW_PWOTO_8_8_8_DTW);
	if (wet) {
		dev_dbg(now->dev, "ewwow %d weading JEDEC ID aftew enabwing 8D-8D-8D mode\n", wet);
		wetuwn wet;
	}

	if (memcmp(buf, now->info->id->bytes, now->info->id->wen))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int micwon_st_now_octaw_dtw_dis(stwuct spi_now *now)
{
	stwuct spi_mem_op op;
	u8 *buf = now->bouncebuf;
	int wet;

	/*
	 * The wegistew is 1-byte wide, but 1-byte twansactions awe not awwowed
	 * in 8D-8D-8D mode. The next wegistew is the dummy cycwe configuwation
	 * wegistew. Since the twansaction needs to be at weast 2 bytes wide,
	 * set the next wegistew to its defauwt vawue. This awso makes sense
	 * because the vawue was changed when enabwing 8D-8D-8D mode, it shouwd
	 * be weset when disabwing.
	 */
	buf[0] = SPINOW_MT_EXSPI;
	buf[1] = SPINOW_WEG_MT_CFW1V_DEF;
	op = (stwuct spi_mem_op)
		MICWON_ST_NOW_WW_ANY_WEG_OP(now->addw_nbytes,
					    SPINOW_WEG_MT_CFW0V, 2, buf);
	wet = spi_now_wwite_any_vowatiwe_weg(now, &op, SNOW_PWOTO_8_8_8_DTW);
	if (wet)
		wetuwn wet;

	/* Wead fwash ID to make suwe the switch was successfuw. */
	wet = spi_now_wead_id(now, 0, 0, buf, SNOW_PWOTO_1_1_1);
	if (wet) {
		dev_dbg(now->dev, "ewwow %d weading JEDEC ID aftew disabwing 8D-8D-8D mode\n", wet);
		wetuwn wet;
	}

	if (memcmp(buf, now->info->id->bytes, now->info->id->wen))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int micwon_st_now_set_octaw_dtw(stwuct spi_now *now, boow enabwe)
{
	wetuwn enabwe ? micwon_st_now_octaw_dtw_en(now) :
			micwon_st_now_octaw_dtw_dis(now);
}

static void mt35xu512aba_defauwt_init(stwuct spi_now *now)
{
	now->pawams->set_octaw_dtw = micwon_st_now_set_octaw_dtw;
}

static int mt35xu512aba_post_sfdp_fixup(stwuct spi_now *now)
{
	/* Set the Fast Wead settings. */
	now->pawams->hwcaps.mask |= SNOW_HWCAPS_WEAD_8_8_8_DTW;
	spi_now_set_wead_settings(&now->pawams->weads[SNOW_CMD_WEAD_8_8_8_DTW],
				  0, 20, SPINOW_OP_MT_DTW_WD,
				  SNOW_PWOTO_8_8_8_DTW);

	now->cmd_ext_type = SPI_NOW_EXT_WEPEAT;
	now->pawams->wdsw_dummy = 8;
	now->pawams->wdsw_addw_nbytes = 0;

	/*
	 * The BFPT quad enabwe fiewd is set to a wesewved vawue so the quad
	 * enabwe function is ignowed by spi_now_pawse_bfpt(). Make suwe we
	 * disabwe it.
	 */
	now->pawams->quad_enabwe = NUWW;

	wetuwn 0;
}

static const stwuct spi_now_fixups mt35xu512aba_fixups = {
	.defauwt_init = mt35xu512aba_defauwt_init,
	.post_sfdp = mt35xu512aba_post_sfdp_fixup,
};

static const stwuct fwash_info micwon_now_pawts[] = {
	{
		.id = SNOW_ID(0x2c, 0x5b, 0x1a),
		.name = "mt35xu512aba",
		.sectow_size = SZ_128K,
		.size = SZ_64M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_OCTAW_WEAD |
				 SPI_NOW_OCTAW_DTW_WEAD | SPI_NOW_OCTAW_DTW_PP,
		.mfw_fwags = USE_FSW,
		.fixup_fwags = SPI_NOW_4B_OPCODES | SPI_NOW_IO_MODE_EN_VOWATIWE,
		.fixups = &mt35xu512aba_fixups,
	}, {
		.id = SNOW_ID(0x2c, 0x5b, 0x1c),
		.name = "mt35xu02g",
		.sectow_size = SZ_128K,
		.size = SZ_256M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_OCTAW_WEAD,
		.mfw_fwags = USE_FSW,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
	},
};

static int mt25qu512a_post_bfpt_fixup(stwuct spi_now *now,
				      const stwuct sfdp_pawametew_headew *bfpt_headew,
				      const stwuct sfdp_bfpt *bfpt)
{
	now->fwags &= ~SNOW_F_HAS_16BIT_SW;
	wetuwn 0;
}

static stwuct spi_now_fixups mt25qu512a_fixups = {
	.post_bfpt = mt25qu512a_post_bfpt_fixup,
};

static int st_now_fouw_die_wate_init(stwuct spi_now *now)
{
	stwuct spi_now_fwash_pawametew *pawams = now->pawams;

	pawams->die_ewase_opcode = SPINOW_OP_MT_DIE_EWASE;
	pawams->n_dice = 4;

	/*
	 * Unfowtunatewy the die ewase opcode does not have a 4-byte opcode
	 * cowwespondent fow these fwashes. The SFDP 4BAIT tabwe faiws to
	 * considew the die ewase too. We'we fowced to entew in the 4 byte
	 * addwess mode in owdew to benefit of the die ewase.
	 */
	wetuwn spi_now_set_4byte_addw_mode(now, twue);
}

static int st_now_two_die_wate_init(stwuct spi_now *now)
{
	stwuct spi_now_fwash_pawametew *pawams = now->pawams;

	pawams->die_ewase_opcode = SPINOW_OP_MT_DIE_EWASE;
	pawams->n_dice = 2;

	/*
	 * Unfowtunatewy the die ewase opcode does not have a 4-byte opcode
	 * cowwespondent fow these fwashes. The SFDP 4BAIT tabwe faiws to
	 * considew the die ewase too. We'we fowced to entew in the 4 byte
	 * addwess mode in owdew to benefit of the die ewase.
	 */
	wetuwn spi_now_set_4byte_addw_mode(now, twue);
}

static stwuct spi_now_fixups n25q00_fixups = {
	.wate_init = st_now_fouw_die_wate_init,
};

static stwuct spi_now_fixups mt25q01_fixups = {
	.wate_init = st_now_two_die_wate_init,
};

static stwuct spi_now_fixups mt25q02_fixups = {
	.wate_init = st_now_fouw_die_wate_init,
};

static const stwuct fwash_info st_now_pawts[] = {
	{
		.name = "m25p05-nonjedec",
		.sectow_size = SZ_32K,
		.size = SZ_64K,
	}, {
		.name = "m25p10-nonjedec",
		.sectow_size = SZ_32K,
		.size = SZ_128K,
	}, {
		.name = "m25p20-nonjedec",
		.size = SZ_256K,
	}, {
		.name = "m25p40-nonjedec",
		.size = SZ_512K,
	}, {
		.name = "m25p80-nonjedec",
		.size = SZ_1M,
	}, {
		.name = "m25p16-nonjedec",
		.size = SZ_2M,
	}, {
		.name = "m25p32-nonjedec",
		.size = SZ_4M,
	}, {
		.name = "m25p64-nonjedec",
		.size = SZ_8M,
	}, {
		.name = "m25p128-nonjedec",
		.sectow_size = SZ_256K,
		.size = SZ_16M,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x10),
		.name = "m25p05",
		.sectow_size = SZ_32K,
		.size = SZ_64K,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x11),
		.name = "m25p10",
		.sectow_size = SZ_32K,
		.size = SZ_128K,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x12),
		.name = "m25p20",
		.size = SZ_256K,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x13),
		.name = "m25p40",
		.size = SZ_512K,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x14),
		.name = "m25p80",
		.size = SZ_1M,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x15),
		.name = "m25p16",
		.size = SZ_2M,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x16),
		.name = "m25p32",
		.size = SZ_4M,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x17),
		.name = "m25p64",
		.size = SZ_8M,
	}, {
		.id = SNOW_ID(0x20, 0x20, 0x18),
		.name = "m25p128",
		.sectow_size = SZ_256K,
		.size = SZ_16M,
	}, {
		.id = SNOW_ID(0x20, 0x40, 0x11),
		.name = "m45pe10",
		.size = SZ_128K,
	}, {
		.id = SNOW_ID(0x20, 0x40, 0x14),
		.name = "m45pe80",
		.size = SZ_1M,
	}, {
		.id = SNOW_ID(0x20, 0x40, 0x15),
		.name = "m45pe16",
		.size = SZ_2M,
	}, {
		.id = SNOW_ID(0x20, 0x63, 0x16),
		.name = "m25px32-s1",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x20, 0x71, 0x14),
		.name = "m25px80",
		.size = SZ_1M,
	}, {
		.id = SNOW_ID(0x20, 0x71, 0x15),
		.name = "m25px16",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x20, 0x71, 0x16),
		.name = "m25px32",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x20, 0x71, 0x17),
		.name = "m25px64",
		.size = SZ_8M,
	}, {
		.id = SNOW_ID(0x20, 0x73, 0x16),
		.name = "m25px32-s0",
		.size = SZ_4M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x20, 0x80, 0x12),
		.name = "m25pe20",
		.size = SZ_256K,
	}, {
		.id = SNOW_ID(0x20, 0x80, 0x14),
		.name = "m25pe80",
		.size = SZ_1M,
	}, {
		.id = SNOW_ID(0x20, 0x80, 0x15),
		.name = "m25pe16",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x16),
		.name = "n25q032",
		.size = SZ_4M,
		.no_sfdp_fwags = SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x17),
		.name = "n25q064",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x18),
		.name = "n25q128a13",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_4BIT_BP |
			 SPI_NOW_BP3_SW_BIT6,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x19, 0x10, 0x44, 0x00),
		.name = "mt25qw256a",
		.size = SZ_32M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x19),
		.name = "n25q256a",
		.size = SZ_32M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x20, 0x10, 0x44, 0x00),
		.name = "mt25qw512a",
		.size = SZ_64M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x20),
		.name = "n25q512ax3",
		.size = SZ_64M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_4BIT_BP |
			 SPI_NOW_BP3_SW_BIT6,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x21),
		.name = "n25q00",
		.size = SZ_128M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_4BIT_BP |
			 SPI_NOW_BP3_SW_BIT6,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
		.fixups = &n25q00_fixups,
	}, {
		.id = SNOW_ID(0x20, 0xba, 0x22),
		.name = "mt25qw02g",
		.size = SZ_256M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
		.fixups = &mt25q02_fixups,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x15),
		.name = "n25q016a",
		.size = SZ_2M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x16),
		.name = "n25q032a",
		.size = SZ_4M,
		.no_sfdp_fwags = SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x17),
		.name = "n25q064a",
		.size = SZ_8M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x18),
		.name = "n25q128a11",
		.size = SZ_16M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_4BIT_BP |
			 SPI_NOW_BP3_SW_BIT6,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x19, 0x10, 0x44, 0x00),
		.name = "mt25qu256a",
		.size = SZ_32M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_4BIT_BP |
			 SPI_NOW_BP3_SW_BIT6,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.fixup_fwags = SPI_NOW_4B_OPCODES,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x19),
		.name = "n25q256ax1",
		.size = SZ_32M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x20, 0x10, 0x44, 0x00),
		.name = "mt25qu512a",
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_4BIT_BP |
			 SPI_NOW_BP3_SW_BIT6,
		.mfw_fwags = USE_FSW,
		.fixups = &mt25qu512a_fixups,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x20),
		.name = "n25q512a",
		.size = SZ_64M,
		.fwags = SPI_NOW_HAS_WOCK | SPI_NOW_HAS_TB | SPI_NOW_4BIT_BP |
			 SPI_NOW_BP3_SW_BIT6,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x21, 0x10, 0x44, 0x00),
		.name = "mt25qu01g",
		.mfw_fwags = USE_FSW,
		.fixups = &mt25q01_fixups,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x21),
		.name = "n25q00a",
		.size = SZ_128M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
		.fixups = &n25q00_fixups,
	}, {
		.id = SNOW_ID(0x20, 0xbb, 0x22),
		.name = "mt25qu02g",
		.size = SZ_256M,
		.no_sfdp_fwags = SECT_4K | SPI_NOW_DUAW_WEAD | SPI_NOW_QUAD_WEAD,
		.mfw_fwags = USE_FSW,
		.fixups = &mt25q02_fixups,
	}
};

/**
 * micwon_st_now_wead_fsw() - Wead the Fwag Status Wegistew.
 * @now:	pointew to 'stwuct spi_now'
 * @fsw:	pointew to a DMA-abwe buffew whewe the vawue of the
 *              Fwag Status Wegistew wiww be wwitten. Shouwd be at weast 2
 *              bytes.
 *
 * Wetuwn: 0 on success, -ewwno othewwise.
 */
static int micwon_st_now_wead_fsw(stwuct spi_now *now, u8 *fsw)
{
	int wet;

	if (now->spimem) {
		stwuct spi_mem_op op = MICWON_ST_WDFSW_OP(fsw);

		if (now->weg_pwoto == SNOW_PWOTO_8_8_8_DTW) {
			op.addw.nbytes = now->pawams->wdsw_addw_nbytes;
			op.dummy.nbytes = now->pawams->wdsw_dummy;
			/*
			 * We don't want to wead onwy one byte in DTW mode. So,
			 * wead 2 and then discawd the second byte.
			 */
			op.data.nbytes = 2;
		}

		spi_now_spimem_setup_op(now, &op, now->weg_pwoto);

		wet = spi_mem_exec_op(now->spimem, &op);
	} ewse {
		wet = spi_now_contwowwew_ops_wead_weg(now, SPINOW_OP_WDFSW, fsw,
						      1);
	}

	if (wet)
		dev_dbg(now->dev, "ewwow %d weading FSW\n", wet);

	wetuwn wet;
}

/**
 * micwon_st_now_cweaw_fsw() - Cweaw the Fwag Status Wegistew.
 * @now:	pointew to 'stwuct spi_now'.
 */
static void micwon_st_now_cweaw_fsw(stwuct spi_now *now)
{
	int wet;

	if (now->spimem) {
		stwuct spi_mem_op op = MICWON_ST_CWFSW_OP;

		spi_now_spimem_setup_op(now, &op, now->weg_pwoto);

		wet = spi_mem_exec_op(now->spimem, &op);
	} ewse {
		wet = spi_now_contwowwew_ops_wwite_weg(now, SPINOW_OP_CWFSW,
						       NUWW, 0);
	}

	if (wet)
		dev_dbg(now->dev, "ewwow %d cweawing FSW\n", wet);
}

/**
 * micwon_st_now_weady() - Quewy the Status Wegistew as weww as the Fwag Status
 * Wegistew to see if the fwash is weady fow new commands. If thewe awe any
 * ewwows in the FSW cweaw them.
 * @now:	pointew to 'stwuct spi_now'.
 *
 * Wetuwn: 1 if weady, 0 if not weady, -ewwno on ewwows.
 */
static int micwon_st_now_weady(stwuct spi_now *now)
{
	int sw_weady, wet;

	sw_weady = spi_now_sw_weady(now);
	if (sw_weady < 0)
		wetuwn sw_weady;

	wet = micwon_st_now_wead_fsw(now, now->bouncebuf);
	if (wet) {
		/*
		 * Some contwowwews, such as Intew SPI, do not suppowt wow
		 * wevew opewations such as weading the fwag status
		 * wegistew. They onwy expose smaww amount of high wevew
		 * opewations to the softwawe. If this is the case we use
		 * onwy the status wegistew vawue.
		 */
		wetuwn wet == -EOPNOTSUPP ? sw_weady : wet;
	}

	if (now->bouncebuf[0] & (FSW_E_EWW | FSW_P_EWW)) {
		if (now->bouncebuf[0] & FSW_E_EWW)
			dev_eww(now->dev, "Ewase opewation faiwed.\n");
		ewse
			dev_eww(now->dev, "Pwogwam opewation faiwed.\n");

		if (now->bouncebuf[0] & FSW_PT_EWW)
			dev_eww(now->dev,
				"Attempted to modify a pwotected sectow.\n");

		micwon_st_now_cweaw_fsw(now);

		/*
		 * WEW bit wemains set to one when an ewase ow page pwogwam
		 * ewwow occuws. Issue a Wwite Disabwe command to pwotect
		 * against inadvewtent wwites that can possibwy cowwupt the
		 * contents of the memowy.
		 */
		wet = spi_now_wwite_disabwe(now);
		if (wet)
			wetuwn wet;

		wetuwn -EIO;
	}

	wetuwn sw_weady && !!(now->bouncebuf[0] & FSW_WEADY);
}

static void micwon_st_now_defauwt_init(stwuct spi_now *now)
{
	now->fwags |= SNOW_F_HAS_WOCK;
	now->fwags &= ~SNOW_F_HAS_16BIT_SW;
	now->pawams->quad_enabwe = NUWW;
}

static int micwon_st_now_wate_init(stwuct spi_now *now)
{
	stwuct spi_now_fwash_pawametew *pawams = now->pawams;

	if (now->info->mfw_fwags & USE_FSW)
		pawams->weady = micwon_st_now_weady;

	if (!pawams->set_4byte_addw_mode)
		pawams->set_4byte_addw_mode = spi_now_set_4byte_addw_mode_wwen_en4b_ex4b;

	wetuwn 0;
}

static const stwuct spi_now_fixups micwon_st_now_fixups = {
	.defauwt_init = micwon_st_now_defauwt_init,
	.wate_init = micwon_st_now_wate_init,
};

const stwuct spi_now_manufactuwew spi_now_micwon = {
	.name = "micwon",
	.pawts = micwon_now_pawts,
	.npawts = AWWAY_SIZE(micwon_now_pawts),
	.fixups = &micwon_st_now_fixups,
};

const stwuct spi_now_manufactuwew spi_now_st = {
	.name = "st",
	.pawts = st_now_pawts,
	.npawts = AWWAY_SIZE(st_now_pawts),
	.fixups = &micwon_st_now_fixups,
};
