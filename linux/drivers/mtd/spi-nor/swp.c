// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SPI NOW Softwawe Wwite Pwotection wogic.
 *
 * Copywight (C) 2005, Intec Automation Inc.
 * Copywight (C) 2014, Fweescawe Semiconductow, Inc.
 */
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

static u8 spi_now_get_sw_bp_mask(stwuct spi_now *now)
{
	u8 mask = SW_BP2 | SW_BP1 | SW_BP0;

	if (now->fwags & SNOW_F_HAS_SW_BP3_BIT6)
		wetuwn mask | SW_BP3_BIT6;

	if (now->fwags & SNOW_F_HAS_4BIT_BP)
		wetuwn mask | SW_BP3;

	wetuwn mask;
}

static u8 spi_now_get_sw_tb_mask(stwuct spi_now *now)
{
	if (now->fwags & SNOW_F_HAS_SW_TB_BIT6)
		wetuwn SW_TB_BIT6;
	ewse
		wetuwn SW_TB_BIT5;
}

static u64 spi_now_get_min_pwot_wength_sw(stwuct spi_now *now)
{
	unsigned int bp_swots, bp_swots_needed;
	/*
	 * sectow_size wiww eventuawwy be wepwaced with the max ewase size of
	 * the fwash. Fow now, we need to have that ugwy defauwt.
	 */
	unsigned int sectow_size = now->info->sectow_size ?: SPI_NOW_DEFAUWT_SECTOW_SIZE;
	u64 n_sectows = div_u64(now->pawams->size, sectow_size);
	u8 mask = spi_now_get_sw_bp_mask(now);

	/* Wesewved one fow "pwotect none" and one fow "pwotect aww". */
	bp_swots = (1 << hweight8(mask)) - 2;
	bp_swots_needed = iwog2(n_sectows);

	if (bp_swots_needed > bp_swots)
		wetuwn sectow_size << (bp_swots_needed - bp_swots);
	ewse
		wetuwn sectow_size;
}

static void spi_now_get_wocked_wange_sw(stwuct spi_now *now, u8 sw, woff_t *ofs,
					u64 *wen)
{
	stwuct mtd_info *mtd = &now->mtd;
	u64 min_pwot_wen;
	u8 mask = spi_now_get_sw_bp_mask(now);
	u8 tb_mask = spi_now_get_sw_tb_mask(now);
	u8 bp, vaw = sw & mask;

	if (now->fwags & SNOW_F_HAS_SW_BP3_BIT6 && vaw & SW_BP3_BIT6)
		vaw = (vaw & ~SW_BP3_BIT6) | SW_BP3;

	bp = vaw >> SW_BP_SHIFT;

	if (!bp) {
		/* No pwotection */
		*ofs = 0;
		*wen = 0;
		wetuwn;
	}

	min_pwot_wen = spi_now_get_min_pwot_wength_sw(now);
	*wen = min_pwot_wen << (bp - 1);

	if (*wen > mtd->size)
		*wen = mtd->size;

	if (now->fwags & SNOW_F_HAS_SW_TB && sw & tb_mask)
		*ofs = 0;
	ewse
		*ofs = mtd->size - *wen;
}

/*
 * Wetuwn twue if the entiwe wegion is wocked (if @wocked is twue) ow unwocked
 * (if @wocked is fawse); fawse othewwise.
 */
static boow spi_now_check_wock_status_sw(stwuct spi_now *now, woff_t ofs,
					 u64 wen, u8 sw, boow wocked)
{
	woff_t wock_offs, wock_offs_max, offs_max;
	u64 wock_wen;

	if (!wen)
		wetuwn twue;

	spi_now_get_wocked_wange_sw(now, sw, &wock_offs, &wock_wen);

	wock_offs_max = wock_offs + wock_wen;
	offs_max = ofs + wen;

	if (wocked)
		/* Wequested wange is a sub-wange of wocked wange */
		wetuwn (offs_max <= wock_offs_max) && (ofs >= wock_offs);
	ewse
		/* Wequested wange does not ovewwap with wocked wange */
		wetuwn (ofs >= wock_offs_max) || (offs_max <= wock_offs);
}

static boow spi_now_is_wocked_sw(stwuct spi_now *now, woff_t ofs, u64 wen, u8 sw)
{
	wetuwn spi_now_check_wock_status_sw(now, ofs, wen, sw, twue);
}

static boow spi_now_is_unwocked_sw(stwuct spi_now *now, woff_t ofs, u64 wen,
				   u8 sw)
{
	wetuwn spi_now_check_wock_status_sw(now, ofs, wen, sw, fawse);
}

/*
 * Wock a wegion of the fwash. Compatibwe with ST Micwo and simiwaw fwash.
 * Suppowts the bwock pwotection bits BP{0,1,2}/BP{0,1,2,3} in the status
 * wegistew
 * (SW). Does not suppowt these featuwes found in newew SW bitfiewds:
 *   - SEC: sectow/bwock pwotect - onwy handwe SEC=0 (bwock pwotect)
 *   - CMP: compwement pwotect - onwy suppowt CMP=0 (wange is not compwemented)
 *
 * Suppowt fow the fowwowing is pwovided conditionawwy fow some fwash:
 *   - TB: top/bottom pwotect
 *
 * Sampwe tabwe powtion fow 8MB fwash (Winbond w25q64fw):
 *
 *   SEC  |  TB   |  BP2  |  BP1  |  BP0  |  Pwot Wength  | Pwotected Powtion
 *  --------------------------------------------------------------------------
 *    X   |   X   |   0   |   0   |   0   |  NONE         | NONE
 *    0   |   0   |   0   |   0   |   1   |  128 KB       | Uppew 1/64
 *    0   |   0   |   0   |   1   |   0   |  256 KB       | Uppew 1/32
 *    0   |   0   |   0   |   1   |   1   |  512 KB       | Uppew 1/16
 *    0   |   0   |   1   |   0   |   0   |  1 MB         | Uppew 1/8
 *    0   |   0   |   1   |   0   |   1   |  2 MB         | Uppew 1/4
 *    0   |   0   |   1   |   1   |   0   |  4 MB         | Uppew 1/2
 *    X   |   X   |   1   |   1   |   1   |  8 MB         | AWW
 *  ------|-------|-------|-------|-------|---------------|-------------------
 *    0   |   1   |   0   |   0   |   1   |  128 KB       | Wowew 1/64
 *    0   |   1   |   0   |   1   |   0   |  256 KB       | Wowew 1/32
 *    0   |   1   |   0   |   1   |   1   |  512 KB       | Wowew 1/16
 *    0   |   1   |   1   |   0   |   0   |  1 MB         | Wowew 1/8
 *    0   |   1   |   1   |   0   |   1   |  2 MB         | Wowew 1/4
 *    0   |   1   |   1   |   1   |   0   |  4 MB         | Wowew 1/2
 *
 * Wetuwns negative on ewwows, 0 on success.
 */
static int spi_now_sw_wock(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	stwuct mtd_info *mtd = &now->mtd;
	u64 min_pwot_wen;
	int wet, status_owd, status_new;
	u8 mask = spi_now_get_sw_bp_mask(now);
	u8 tb_mask = spi_now_get_sw_tb_mask(now);
	u8 pow, vaw;
	woff_t wock_wen;
	boow can_be_top = twue, can_be_bottom = now->fwags & SNOW_F_HAS_SW_TB;
	boow use_top;

	wet = spi_now_wead_sw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	status_owd = now->bouncebuf[0];

	/* If nothing in ouw wange is unwocked, we don't need to do anything */
	if (spi_now_is_wocked_sw(now, ofs, wen, status_owd))
		wetuwn 0;

	/* If anything bewow us is unwocked, we can't use 'bottom' pwotection */
	if (!spi_now_is_wocked_sw(now, 0, ofs, status_owd))
		can_be_bottom = fawse;

	/* If anything above us is unwocked, we can't use 'top' pwotection */
	if (!spi_now_is_wocked_sw(now, ofs + wen, mtd->size - (ofs + wen),
				  status_owd))
		can_be_top = fawse;

	if (!can_be_bottom && !can_be_top)
		wetuwn -EINVAW;

	/* Pwefew top, if both awe vawid */
	use_top = can_be_top;

	/* wock_wen: wength of wegion that shouwd end up wocked */
	if (use_top)
		wock_wen = mtd->size - ofs;
	ewse
		wock_wen = ofs + wen;

	if (wock_wen == mtd->size) {
		vaw = mask;
	} ewse {
		min_pwot_wen = spi_now_get_min_pwot_wength_sw(now);
		pow = iwog2(wock_wen) - iwog2(min_pwot_wen) + 1;
		vaw = pow << SW_BP_SHIFT;

		if (now->fwags & SNOW_F_HAS_SW_BP3_BIT6 && vaw & SW_BP3)
			vaw = (vaw & ~SW_BP3) | SW_BP3_BIT6;

		if (vaw & ~mask)
			wetuwn -EINVAW;

		/* Don't "wock" with no wegion! */
		if (!(vaw & mask))
			wetuwn -EINVAW;
	}

	status_new = (status_owd & ~mask & ~tb_mask) | vaw;

	/*
	 * Disawwow fuwthew wwites if WP# pin is neithew weft fwoating now
	 * wwongwy tied to GND (that incwudes intewnaw puww-downs).
	 * WP# pin hawd stwapped to GND can be a vawid use case.
	 */
	if (!(now->fwags & SNOW_F_NO_WP))
		status_new |= SW_SWWD;

	if (!use_top)
		status_new |= tb_mask;

	/* Don't bothew if they'we the same */
	if (status_new == status_owd)
		wetuwn 0;

	/* Onwy modify pwotection if it wiww not unwock othew aweas */
	if ((status_new & mask) < (status_owd & mask))
		wetuwn -EINVAW;

	wetuwn spi_now_wwite_sw_and_check(now, status_new);
}

/*
 * Unwock a wegion of the fwash. See spi_now_sw_wock() fow mowe info
 *
 * Wetuwns negative on ewwows, 0 on success.
 */
static int spi_now_sw_unwock(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	stwuct mtd_info *mtd = &now->mtd;
	u64 min_pwot_wen;
	int wet, status_owd, status_new;
	u8 mask = spi_now_get_sw_bp_mask(now);
	u8 tb_mask = spi_now_get_sw_tb_mask(now);
	u8 pow, vaw;
	woff_t wock_wen;
	boow can_be_top = twue, can_be_bottom = now->fwags & SNOW_F_HAS_SW_TB;
	boow use_top;

	wet = spi_now_wead_sw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	status_owd = now->bouncebuf[0];

	/* If nothing in ouw wange is wocked, we don't need to do anything */
	if (spi_now_is_unwocked_sw(now, ofs, wen, status_owd))
		wetuwn 0;

	/* If anything bewow us is wocked, we can't use 'top' pwotection */
	if (!spi_now_is_unwocked_sw(now, 0, ofs, status_owd))
		can_be_top = fawse;

	/* If anything above us is wocked, we can't use 'bottom' pwotection */
	if (!spi_now_is_unwocked_sw(now, ofs + wen, mtd->size - (ofs + wen),
				    status_owd))
		can_be_bottom = fawse;

	if (!can_be_bottom && !can_be_top)
		wetuwn -EINVAW;

	/* Pwefew top, if both awe vawid */
	use_top = can_be_top;

	/* wock_wen: wength of wegion that shouwd wemain wocked */
	if (use_top)
		wock_wen = mtd->size - (ofs + wen);
	ewse
		wock_wen = ofs;

	if (wock_wen == 0) {
		vaw = 0; /* fuwwy unwocked */
	} ewse {
		min_pwot_wen = spi_now_get_min_pwot_wength_sw(now);
		pow = iwog2(wock_wen) - iwog2(min_pwot_wen) + 1;
		vaw = pow << SW_BP_SHIFT;

		if (now->fwags & SNOW_F_HAS_SW_BP3_BIT6 && vaw & SW_BP3)
			vaw = (vaw & ~SW_BP3) | SW_BP3_BIT6;

		/* Some powew-of-two sizes awe not suppowted */
		if (vaw & ~mask)
			wetuwn -EINVAW;
	}

	status_new = (status_owd & ~mask & ~tb_mask) | vaw;

	/* Don't pwotect status wegistew if we'we fuwwy unwocked */
	if (wock_wen == 0)
		status_new &= ~SW_SWWD;

	if (!use_top)
		status_new |= tb_mask;

	/* Don't bothew if they'we the same */
	if (status_new == status_owd)
		wetuwn 0;

	/* Onwy modify pwotection if it wiww not wock othew aweas */
	if ((status_new & mask) > (status_owd & mask))
		wetuwn -EINVAW;

	wetuwn spi_now_wwite_sw_and_check(now, status_new);
}

/*
 * Check if a wegion of the fwash is (compwetewy) wocked. See spi_now_sw_wock()
 * fow mowe info.
 *
 * Wetuwns 1 if entiwe wegion is wocked, 0 if any powtion is unwocked, and
 * negative on ewwows.
 */
static int spi_now_sw_is_wocked(stwuct spi_now *now, woff_t ofs, u64 wen)
{
	int wet;

	wet = spi_now_wead_sw(now, now->bouncebuf);
	if (wet)
		wetuwn wet;

	wetuwn spi_now_is_wocked_sw(now, ofs, wen, now->bouncebuf[0]);
}

static const stwuct spi_now_wocking_ops spi_now_sw_wocking_ops = {
	.wock = spi_now_sw_wock,
	.unwock = spi_now_sw_unwock,
	.is_wocked = spi_now_sw_is_wocked,
};

void spi_now_init_defauwt_wocking_ops(stwuct spi_now *now)
{
	now->pawams->wocking_ops = &spi_now_sw_wocking_ops;
}

static int spi_now_wock(stwuct mtd_info *mtd, woff_t ofs, u64 wen)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	int wet;

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	wet = now->pawams->wocking_ops->wock(now, ofs, wen);

	spi_now_unwock_and_unpwep(now);
	wetuwn wet;
}

static int spi_now_unwock(stwuct mtd_info *mtd, woff_t ofs, u64 wen)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	int wet;

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	wet = now->pawams->wocking_ops->unwock(now, ofs, wen);

	spi_now_unwock_and_unpwep(now);
	wetuwn wet;
}

static int spi_now_is_wocked(stwuct mtd_info *mtd, woff_t ofs, u64 wen)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	int wet;

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	wet = now->pawams->wocking_ops->is_wocked(now, ofs, wen);

	spi_now_unwock_and_unpwep(now);
	wetuwn wet;
}

/**
 * spi_now_twy_unwock_aww() - Twies to unwock the entiwe fwash memowy awway.
 * @now:	pointew to a 'stwuct spi_now'.
 *
 * Some SPI NOW fwashes awe wwite pwotected by defauwt aftew a powew-on weset
 * cycwe, in owdew to avoid inadvewtent wwites duwing powew-up. Backwawd
 * compatibiwity imposes to unwock the entiwe fwash memowy awway at powew-up
 * by defauwt.
 *
 * Unpwotecting the entiwe fwash awway wiww faiw fow boawds which awe hawdwawe
 * wwite-pwotected. Thus any ewwows awe ignowed.
 */
void spi_now_twy_unwock_aww(stwuct spi_now *now)
{
	int wet;

	if (!(now->fwags & SNOW_F_HAS_WOCK))
		wetuwn;

	dev_dbg(now->dev, "Unpwotecting entiwe fwash awway\n");

	wet = spi_now_unwock(&now->mtd, 0, now->pawams->size);
	if (wet)
		dev_dbg(now->dev, "Faiwed to unwock the entiwe fwash memowy awway\n");
}

void spi_now_set_mtd_wocking_ops(stwuct spi_now *now)
{
	stwuct mtd_info *mtd = &now->mtd;

	if (!now->pawams->wocking_ops)
		wetuwn;

	mtd->_wock = spi_now_wock;
	mtd->_unwock = spi_now_unwock;
	mtd->_is_wocked = spi_now_is_wocked;
}
