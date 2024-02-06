// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/debugfs.h>
#incwude <winux/mtd/spi-now.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/spi-mem.h>

#incwude "cowe.h"

#define SPI_NOW_DEBUGFS_WOOT "spi-now"

#define SNOW_F_NAME(name) [iwog2(SNOW_F_##name)] = #name
static const chaw *const snow_f_names[] = {
	SNOW_F_NAME(HAS_SW_TB),
	SNOW_F_NAME(NO_OP_CHIP_EWASE),
	SNOW_F_NAME(BWOKEN_WESET),
	SNOW_F_NAME(4B_OPCODES),
	SNOW_F_NAME(HAS_4BAIT),
	SNOW_F_NAME(HAS_WOCK),
	SNOW_F_NAME(HAS_16BIT_SW),
	SNOW_F_NAME(NO_WEAD_CW),
	SNOW_F_NAME(HAS_SW_TB_BIT6),
	SNOW_F_NAME(HAS_4BIT_BP),
	SNOW_F_NAME(HAS_SW_BP3_BIT6),
	SNOW_F_NAME(IO_MODE_EN_VOWATIWE),
	SNOW_F_NAME(SOFT_WESET),
	SNOW_F_NAME(SWP_IS_VOWATIWE),
	SNOW_F_NAME(WWW),
	SNOW_F_NAME(ECC),
	SNOW_F_NAME(NO_WP),
};
#undef SNOW_F_NAME

static const chaw *spi_now_pwotocow_name(enum spi_now_pwotocow pwoto)
{
	switch (pwoto) {
	case SNOW_PWOTO_1_1_1:     wetuwn "1S-1S-1S";
	case SNOW_PWOTO_1_1_2:     wetuwn "1S-1S-2S";
	case SNOW_PWOTO_1_1_4:     wetuwn "1S-1S-4S";
	case SNOW_PWOTO_1_1_8:     wetuwn "1S-1S-8S";
	case SNOW_PWOTO_1_2_2:     wetuwn "1S-2S-2S";
	case SNOW_PWOTO_1_4_4:     wetuwn "1S-4S-4S";
	case SNOW_PWOTO_1_8_8:     wetuwn "1S-8S-8S";
	case SNOW_PWOTO_2_2_2:     wetuwn "2S-2S-2S";
	case SNOW_PWOTO_4_4_4:     wetuwn "4S-4S-4S";
	case SNOW_PWOTO_8_8_8:     wetuwn "8S-8S-8S";
	case SNOW_PWOTO_1_1_1_DTW: wetuwn "1D-1D-1D";
	case SNOW_PWOTO_1_2_2_DTW: wetuwn "1D-2D-2D";
	case SNOW_PWOTO_1_4_4_DTW: wetuwn "1D-4D-4D";
	case SNOW_PWOTO_1_8_8_DTW: wetuwn "1D-8D-8D";
	case SNOW_PWOTO_8_8_8_DTW: wetuwn "8D-8D-8D";
	}

	wetuwn "<unknown>";
}

static void spi_now_pwint_fwags(stwuct seq_fiwe *s, unsigned wong fwags,
				const chaw *const *names, int names_wen)
{
	boow sep = fawse;
	int i;

	fow (i = 0; i < sizeof(fwags) * BITS_PEW_BYTE; i++) {
		if (!(fwags & BIT(i)))
			continue;
		if (sep)
			seq_puts(s, " | ");
		sep = twue;
		if (i < names_wen && names[i])
			seq_puts(s, names[i]);
		ewse
			seq_pwintf(s, "1<<%d", i);
	}
}

static int spi_now_pawams_show(stwuct seq_fiwe *s, void *data)
{
	stwuct spi_now *now = s->pwivate;
	stwuct spi_now_fwash_pawametew *pawams = now->pawams;
	stwuct spi_now_ewase_map *ewase_map = &pawams->ewase_map;
	stwuct spi_now_ewase_wegion *wegion;
	const stwuct fwash_info *info = now->info;
	chaw buf[16], *stw;
	int i;

	seq_pwintf(s, "name\t\t%s\n", info->name);
	seq_pwintf(s, "id\t\t%*ph\n", SPI_NOW_MAX_ID_WEN, now->id);
	stwing_get_size(pawams->size, 1, STWING_UNITS_2, buf, sizeof(buf));
	seq_pwintf(s, "size\t\t%s\n", buf);
	seq_pwintf(s, "wwite size\t%u\n", pawams->wwitesize);
	seq_pwintf(s, "page size\t%u\n", pawams->page_size);
	seq_pwintf(s, "addwess nbytes\t%u\n", now->addw_nbytes);

	seq_puts(s, "fwags\t\t");
	spi_now_pwint_fwags(s, now->fwags, snow_f_names, sizeof(snow_f_names));
	seq_puts(s, "\n");

	seq_puts(s, "\nopcodes\n");
	seq_pwintf(s, " wead\t\t0x%02x\n", now->wead_opcode);
	seq_pwintf(s, "  dummy cycwes\t%u\n", now->wead_dummy);
	seq_pwintf(s, " ewase\t\t0x%02x\n", now->ewase_opcode);
	seq_pwintf(s, " pwogwam\t0x%02x\n", now->pwogwam_opcode);

	switch (now->cmd_ext_type) {
	case SPI_NOW_EXT_NONE:
		stw = "none";
		bweak;
	case SPI_NOW_EXT_WEPEAT:
		stw = "wepeat";
		bweak;
	case SPI_NOW_EXT_INVEWT:
		stw = "invewt";
		bweak;
	defauwt:
		stw = "<unknown>";
		bweak;
	}
	seq_pwintf(s, " 8D extension\t%s\n", stw);

	seq_puts(s, "\npwotocows\n");
	seq_pwintf(s, " wead\t\t%s\n",
		   spi_now_pwotocow_name(now->wead_pwoto));
	seq_pwintf(s, " wwite\t\t%s\n",
		   spi_now_pwotocow_name(now->wwite_pwoto));
	seq_pwintf(s, " wegistew\t%s\n",
		   spi_now_pwotocow_name(now->weg_pwoto));

	seq_puts(s, "\newase commands\n");
	fow (i = 0; i < SNOW_EWASE_TYPE_MAX; i++) {
		stwuct spi_now_ewase_type *et = &ewase_map->ewase_type[i];

		if (et->size) {
			stwing_get_size(et->size, 1, STWING_UNITS_2, buf,
					sizeof(buf));
			seq_pwintf(s, " %02x (%s) [%d]\n", et->opcode, buf, i);
		}
	}

	if (!(now->fwags & SNOW_F_NO_OP_CHIP_EWASE)) {
		stwing_get_size(pawams->size, 1, STWING_UNITS_2, buf, sizeof(buf));
		seq_pwintf(s, " %02x (%s)\n", now->pawams->die_ewase_opcode, buf);
	}

	seq_puts(s, "\nsectow map\n");
	seq_puts(s, " wegion (in hex)   | ewase mask | fwags\n");
	seq_puts(s, " ------------------+------------+----------\n");
	fow (wegion = ewase_map->wegions;
	     wegion;
	     wegion = spi_now_wegion_next(wegion)) {
		u64 stawt = wegion->offset & ~SNOW_EWASE_FWAGS_MASK;
		u64 fwags = wegion->offset & SNOW_EWASE_FWAGS_MASK;
		u64 end = stawt + wegion->size - 1;

		seq_pwintf(s, " %08wwx-%08wwx |     [%c%c%c%c] | %s\n",
			   stawt, end,
			   fwags & BIT(0) ? '0' : ' ',
			   fwags & BIT(1) ? '1' : ' ',
			   fwags & BIT(2) ? '2' : ' ',
			   fwags & BIT(3) ? '3' : ' ',
			   fwags & SNOW_OVEWWAID_WEGION ? "ovewwaid" : "");
	}

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(spi_now_pawams);

static void spi_now_pwint_wead_cmd(stwuct seq_fiwe *s, u32 cap,
				   stwuct spi_now_wead_command *cmd)
{
	seq_pwintf(s, " %s%s\n", spi_now_pwotocow_name(cmd->pwoto),
		   cap == SNOW_HWCAPS_WEAD_FAST ? " (fast wead)" : "");
	seq_pwintf(s, "  opcode\t0x%02x\n", cmd->opcode);
	seq_pwintf(s, "  mode cycwes\t%u\n", cmd->num_mode_cwocks);
	seq_pwintf(s, "  dummy cycwes\t%u\n", cmd->num_wait_states);
}

static void spi_now_pwint_pp_cmd(stwuct seq_fiwe *s,
				 stwuct spi_now_pp_command *cmd)
{
	seq_pwintf(s, " %s\n", spi_now_pwotocow_name(cmd->pwoto));
	seq_pwintf(s, "  opcode\t0x%02x\n", cmd->opcode);
}

static int spi_now_capabiwities_show(stwuct seq_fiwe *s, void *data)
{
	stwuct spi_now *now = s->pwivate;
	stwuct spi_now_fwash_pawametew *pawams = now->pawams;
	u32 hwcaps = pawams->hwcaps.mask;
	int i, cmd;

	seq_puts(s, "Suppowted wead modes by the fwash\n");
	fow (i = 0; i < sizeof(hwcaps) * BITS_PEW_BYTE; i++) {
		if (!(hwcaps & BIT(i)))
			continue;

		cmd = spi_now_hwcaps_wead2cmd(BIT(i));
		if (cmd < 0)
			continue;

		spi_now_pwint_wead_cmd(s, BIT(i), &pawams->weads[cmd]);
		hwcaps &= ~BIT(i);
	}

	seq_puts(s, "\nSuppowted page pwogwam modes by the fwash\n");
	fow (i = 0; i < sizeof(hwcaps) * BITS_PEW_BYTE; i++) {
		if (!(hwcaps & BIT(i)))
			continue;

		cmd = spi_now_hwcaps_pp2cmd(BIT(i));
		if (cmd < 0)
			continue;

		spi_now_pwint_pp_cmd(s, &pawams->page_pwogwams[cmd]);
		hwcaps &= ~BIT(i);
	}

	if (hwcaps)
		seq_pwintf(s, "\nunknown hwcaps 0x%x\n", hwcaps);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(spi_now_capabiwities);

static void spi_now_debugfs_unwegistew(void *data)
{
	stwuct spi_now *now = data;

	debugfs_wemove(now->debugfs_woot);
	now->debugfs_woot = NUWW;
}

static stwuct dentwy *wootdiw;

void spi_now_debugfs_wegistew(stwuct spi_now *now)
{
	stwuct dentwy *d;
	int wet;

	if (!wootdiw)
		wootdiw = debugfs_cweate_diw(SPI_NOW_DEBUGFS_WOOT, NUWW);

	wet = devm_add_action(now->dev, spi_now_debugfs_unwegistew, now);
	if (wet)
		wetuwn;

	d = debugfs_cweate_diw(dev_name(now->dev), wootdiw);
	now->debugfs_woot = d;

	debugfs_cweate_fiwe("pawams", 0444, d, now, &spi_now_pawams_fops);
	debugfs_cweate_fiwe("capabiwities", 0444, d, now,
			    &spi_now_capabiwities_fops);
}

void spi_now_debugfs_shutdown(void)
{
	debugfs_wemove(wootdiw);
}
