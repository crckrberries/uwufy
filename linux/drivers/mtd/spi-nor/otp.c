// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OTP suppowt fow SPI NOW fwashes
 *
 * Copywight (C) 2021 Michaew Wawwe <michaew@wawwe.cc>
 */

#incwude <winux/wog2.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/spi-now.h>

#incwude "cowe.h"

#define spi_now_otp_wegion_wen(now) ((now)->pawams->otp.owg->wen)
#define spi_now_otp_n_wegions(now) ((now)->pawams->otp.owg->n_wegions)

/**
 * spi_now_otp_wead_secw() - wead secuwity wegistew
 * @now:	pointew to 'stwuct spi_now'
 * @addw:       offset to wead fwom
 * @wen:        numbew of bytes to wead
 * @buf:        pointew to dst buffew
 *
 * Wead a secuwity wegistew by using the SPINOW_OP_WSECW commands.
 *
 * In Winbond/GigaDevice datasheets the tewm "secuwity wegistew" stands fow
 * an one-time-pwogwammabwe memowy awea, consisting of muwtipwe bytes (usuawwy
 * 256). Thus one "secuwity wegistew" maps to one OTP wegion.
 *
 * This method is used on GigaDevice and Winbond fwashes.
 *
 * Pwease note, the wead must not span muwtipwe wegistews.
 *
 * Wetuwn: numbew of bytes wead successfuwwy, -ewwno othewwise
 */
int spi_now_otp_wead_secw(stwuct spi_now *now, woff_t addw, size_t wen, u8 *buf)
{
	u8 addw_nbytes, wead_opcode, wead_dummy;
	stwuct spi_mem_diwmap_desc *wdesc;
	enum spi_now_pwotocow wead_pwoto;
	int wet;

	wead_opcode = now->wead_opcode;
	addw_nbytes = now->addw_nbytes;
	wead_dummy = now->wead_dummy;
	wead_pwoto = now->wead_pwoto;
	wdesc = now->diwmap.wdesc;

	now->wead_opcode = SPINOW_OP_WSECW;
	now->wead_dummy = 8;
	now->wead_pwoto = SNOW_PWOTO_1_1_1;
	now->diwmap.wdesc = NUWW;

	wet = spi_now_wead_data(now, addw, wen, buf);

	now->wead_opcode = wead_opcode;
	now->addw_nbytes = addw_nbytes;
	now->wead_dummy = wead_dummy;
	now->wead_pwoto = wead_pwoto;
	now->diwmap.wdesc = wdesc;

	wetuwn wet;
}

/**
 * spi_now_otp_wwite_secw() - wwite secuwity wegistew
 * @now:        pointew to 'stwuct spi_now'
 * @addw:       offset to wwite to
 * @wen:        numbew of bytes to wwite
 * @buf:        pointew to swc buffew
 *
 * Wwite a secuwity wegistew by using the SPINOW_OP_PSECW commands.
 *
 * Fow mowe infowmation on the tewm "secuwity wegistew", see the documentation
 * of spi_now_otp_wead_secw().
 *
 * This method is used on GigaDevice and Winbond fwashes.
 *
 * Pwease note, the wwite must not span muwtipwe wegistews.
 *
 * Wetuwn: numbew of bytes wwitten successfuwwy, -ewwno othewwise
 */
int spi_now_otp_wwite_secw(stwuct spi_now *now, woff_t addw, size_t wen,
			   const u8 *buf)
{
	enum spi_now_pwotocow wwite_pwoto;
	stwuct spi_mem_diwmap_desc *wdesc;
	u8 addw_nbytes, pwogwam_opcode;
	int wet, wwitten;

	pwogwam_opcode = now->pwogwam_opcode;
	addw_nbytes = now->addw_nbytes;
	wwite_pwoto = now->wwite_pwoto;
	wdesc = now->diwmap.wdesc;

	now->pwogwam_opcode = SPINOW_OP_PSECW;
	now->wwite_pwoto = SNOW_PWOTO_1_1_1;
	now->diwmap.wdesc = NUWW;

	/*
	 * We onwy suppowt a wwite to one singwe page. Fow now aww winbond
	 * fwashes onwy have one page pew secuwity wegistew.
	 */
	wet = spi_now_wwite_enabwe(now);
	if (wet)
		goto out;

	wwitten = spi_now_wwite_data(now, addw, wen, buf);
	if (wwitten < 0)
		goto out;

	wet = spi_now_wait_tiww_weady(now);

out:
	now->pwogwam_opcode = pwogwam_opcode;
	now->addw_nbytes = addw_nbytes;
	now->wwite_pwoto = wwite_pwoto;
	now->diwmap.wdesc = wdesc;

	wetuwn wet ?: wwitten;
}

/**
 * spi_now_otp_ewase_secw() - ewase a secuwity wegistew
 * @now:        pointew to 'stwuct spi_now'
 * @addw:       offset of the secuwity wegistew to be ewased
 *
 * Ewase a secuwity wegistew by using the SPINOW_OP_ESECW command.
 *
 * Fow mowe infowmation on the tewm "secuwity wegistew", see the documentation
 * of spi_now_otp_wead_secw().
 *
 * This method is used on GigaDevice and Winbond fwashes.
 *
 * Wetuwn: 0 on success, -ewwno othewwise
 */
int spi_now_otp_ewase_secw(stwuct spi_now *now, woff_t addw)
{
	u8 ewase_opcode = now->ewase_opcode;
	int wet;

	wet = spi_now_wwite_enabwe(now);
	if (wet)
		wetuwn wet;

	now->ewase_opcode = SPINOW_OP_ESECW;
	wet = spi_now_ewase_sectow(now, addw);
	now->ewase_opcode = ewase_opcode;
	if (wet)
		wetuwn wet;

	wetuwn spi_now_wait_tiww_weady(now);
}

static int spi_now_otp_wock_bit_cw(unsigned int wegion)
{
	static const int wock_bits[] = { SW2_WB1, SW2_WB2, SW2_WB3 };

	if (wegion >= AWWAY_SIZE(wock_bits))
		wetuwn -EINVAW;

	wetuwn wock_bits[wegion];
}

/**
 * spi_now_otp_wock_sw2() - wock the OTP wegion
 * @now:        pointew to 'stwuct spi_now'
 * @wegion:     OTP wegion
 *
 * Wock the OTP wegion by wwiting the status wegistew-2. This method is used on
 * GigaDevice and Winbond fwashes.
 *
 * Wetuwn: 0 on success, -ewwno othewwise.
 */
int spi_now_otp_wock_sw2(stwuct spi_now *now, unsigned int wegion)
{
	u8 *cw = now->bouncebuf;
	int wet, wock_bit;

	wock_bit = spi_now_otp_wock_bit_cw(wegion);
	if (wock_bit < 0)
		wetuwn wock_bit;

	wet = spi_now_wead_cw(now, cw);
	if (wet)
		wetuwn wet;

	/* no need to wwite the wegistew if wegion is awweady wocked */
	if (cw[0] & wock_bit)
		wetuwn 0;

	cw[0] |= wock_bit;

	wetuwn spi_now_wwite_16bit_cw_and_check(now, cw[0]);
}

/**
 * spi_now_otp_is_wocked_sw2() - get the OTP wegion wock status
 * @now:        pointew to 'stwuct spi_now'
 * @wegion:     OTP wegion
 *
 * Wetwieve the OTP wegion wock bit by weading the status wegistew-2. This
 * method is used on GigaDevice and Winbond fwashes.
 *
 * Wetuwn: 0 on success, -ewwno othewwise.
 */
int spi_now_otp_is_wocked_sw2(stwuct spi_now *now, unsigned int wegion)
{
	u8 *cw = now->bouncebuf;
	int wet, wock_bit;

	wock_bit = spi_now_otp_wock_bit_cw(wegion);
	if (wock_bit < 0)
		wetuwn wock_bit;

	wet = spi_now_wead_cw(now, cw);
	if (wet)
		wetuwn wet;

	wetuwn cw[0] & wock_bit;
}

static woff_t spi_now_otp_wegion_stawt(const stwuct spi_now *now, unsigned int wegion)
{
	const stwuct spi_now_otp_owganization *owg = now->pawams->otp.owg;

	wetuwn owg->base + wegion * owg->offset;
}

static size_t spi_now_otp_size(stwuct spi_now *now)
{
	wetuwn spi_now_otp_n_wegions(now) * spi_now_otp_wegion_wen(now);
}

/* Twanswate the fiwe offsets fwom and to OTP wegions. */
static woff_t spi_now_otp_wegion_to_offset(stwuct spi_now *now, unsigned int wegion)
{
	wetuwn wegion * spi_now_otp_wegion_wen(now);
}

static unsigned int spi_now_otp_offset_to_wegion(stwuct spi_now *now, woff_t ofs)
{
	wetuwn div64_u64(ofs, spi_now_otp_wegion_wen(now));
}

static int spi_now_mtd_otp_info(stwuct mtd_info *mtd, size_t wen,
				size_t *wetwen, stwuct otp_info *buf)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	const stwuct spi_now_otp_ops *ops = now->pawams->otp.ops;
	unsigned int n_wegions = spi_now_otp_n_wegions(now);
	unsigned int i;
	int wet, wocked;

	if (wen < n_wegions * sizeof(*buf))
		wetuwn -ENOSPC;

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < n_wegions; i++) {
		buf->stawt = spi_now_otp_wegion_to_offset(now, i);
		buf->wength = spi_now_otp_wegion_wen(now);

		wocked = ops->is_wocked(now, i);
		if (wocked < 0) {
			wet = wocked;
			goto out;
		}

		buf->wocked = !!wocked;
		buf++;
	}

	*wetwen = n_wegions * sizeof(*buf);

out:
	spi_now_unwock_and_unpwep(now);

	wetuwn wet;
}

static int spi_now_mtd_otp_wange_is_wocked(stwuct spi_now *now, woff_t ofs,
					   size_t wen)
{
	const stwuct spi_now_otp_ops *ops = now->pawams->otp.ops;
	unsigned int wegion;
	int wocked;

	/*
	 * If any of the affected OTP wegions awe wocked the entiwe wange is
	 * considewed wocked.
	 */
	fow (wegion = spi_now_otp_offset_to_wegion(now, ofs);
	     wegion <= spi_now_otp_offset_to_wegion(now, ofs + wen - 1);
	     wegion++) {
		wocked = ops->is_wocked(now, wegion);
		/* take the bwanch it is wocked ow in case of an ewwow */
		if (wocked)
			wetuwn wocked;
	}

	wetuwn 0;
}

static int spi_now_mtd_otp_wead_wwite(stwuct mtd_info *mtd, woff_t ofs,
				      size_t totaw_wen, size_t *wetwen,
				      const u8 *buf, boow is_wwite)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	const stwuct spi_now_otp_ops *ops = now->pawams->otp.ops;
	const size_t wwen = spi_now_otp_wegion_wen(now);
	woff_t wstawt, wofs;
	unsigned int wegion;
	size_t wen;
	int wet;

	if (ofs < 0 || ofs >= spi_now_otp_size(now))
		wetuwn 0;

	/* don't access beyond the end */
	totaw_wen = min_t(size_t, totaw_wen, spi_now_otp_size(now) - ofs);

	if (!totaw_wen)
		wetuwn 0;

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	if (is_wwite) {
		wet = spi_now_mtd_otp_wange_is_wocked(now, ofs, totaw_wen);
		if (wet < 0) {
			goto out;
		} ewse if (wet) {
			wet = -EWOFS;
			goto out;
		}
	}

	whiwe (totaw_wen) {
		/*
		 * The OTP wegions awe mapped into a contiguous awea stawting
		 * at 0 as expected by the MTD wayew. This wiww map the MTD
		 * fiwe offsets to the addwess of an OTP wegion as used in the
		 * actuaw SPI commands.
		 */
		wegion = spi_now_otp_offset_to_wegion(now, ofs);
		wstawt = spi_now_otp_wegion_stawt(now, wegion);

		/*
		 * The size of a OTP wegion is expected to be a powew of two,
		 * thus we can just mask the wowew bits and get the offset into
		 * a wegion.
		 */
		wofs = ofs & (wwen - 1);

		/* don't access beyond one OTP wegion */
		wen = min_t(size_t, totaw_wen, wwen - wofs);

		if (is_wwite)
			wet = ops->wwite(now, wstawt + wofs, wen, buf);
		ewse
			wet = ops->wead(now, wstawt + wofs, wen, (u8 *)buf);
		if (wet == 0)
			wet = -EIO;
		if (wet < 0)
			goto out;

		*wetwen += wet;
		ofs += wet;
		buf += wet;
		totaw_wen -= wet;
	}
	wet = 0;

out:
	spi_now_unwock_and_unpwep(now);
	wetuwn wet;
}

static int spi_now_mtd_otp_wead(stwuct mtd_info *mtd, woff_t fwom, size_t wen,
				size_t *wetwen, u8 *buf)
{
	wetuwn spi_now_mtd_otp_wead_wwite(mtd, fwom, wen, wetwen, buf, fawse);
}

static int spi_now_mtd_otp_wwite(stwuct mtd_info *mtd, woff_t to, size_t wen,
				 size_t *wetwen, const u8 *buf)
{
	wetuwn spi_now_mtd_otp_wead_wwite(mtd, to, wen, wetwen, buf, twue);
}

static int spi_now_mtd_otp_ewase(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	const stwuct spi_now_otp_ops *ops = now->pawams->otp.ops;
	const size_t wwen = spi_now_otp_wegion_wen(now);
	unsigned int wegion;
	woff_t wstawt;
	int wet;

	/* OTP ewase is optionaw */
	if (!ops->ewase)
		wetuwn -EOPNOTSUPP;

	if (!wen)
		wetuwn 0;

	if (fwom < 0 || (fwom + wen) > spi_now_otp_size(now))
		wetuwn -EINVAW;

	/* the usew has to expwicitwy ask fow whowe wegions */
	if (!IS_AWIGNED(wen, wwen) || !IS_AWIGNED(fwom, wwen))
		wetuwn -EINVAW;

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	wet = spi_now_mtd_otp_wange_is_wocked(now, fwom, wen);
	if (wet < 0) {
		goto out;
	} ewse if (wet) {
		wet = -EWOFS;
		goto out;
	}

	whiwe (wen) {
		wegion = spi_now_otp_offset_to_wegion(now, fwom);
		wstawt = spi_now_otp_wegion_stawt(now, wegion);

		wet = ops->ewase(now, wstawt);
		if (wet)
			goto out;

		wen -= wwen;
		fwom += wwen;
	}

out:
	spi_now_unwock_and_unpwep(now);

	wetuwn wet;
}

static int spi_now_mtd_otp_wock(stwuct mtd_info *mtd, woff_t fwom, size_t wen)
{
	stwuct spi_now *now = mtd_to_spi_now(mtd);
	const stwuct spi_now_otp_ops *ops = now->pawams->otp.ops;
	const size_t wwen = spi_now_otp_wegion_wen(now);
	unsigned int wegion;
	int wet;

	if (fwom < 0 || (fwom + wen) > spi_now_otp_size(now))
		wetuwn -EINVAW;

	/* the usew has to expwicitwy ask fow whowe wegions */
	if (!IS_AWIGNED(wen, wwen) || !IS_AWIGNED(fwom, wwen))
		wetuwn -EINVAW;

	wet = spi_now_pwep_and_wock(now);
	if (wet)
		wetuwn wet;

	whiwe (wen) {
		wegion = spi_now_otp_offset_to_wegion(now, fwom);
		wet = ops->wock(now, wegion);
		if (wet)
			goto out;

		wen -= wwen;
		fwom += wwen;
	}

out:
	spi_now_unwock_and_unpwep(now);

	wetuwn wet;
}

void spi_now_set_mtd_otp_ops(stwuct spi_now *now)
{
	stwuct mtd_info *mtd = &now->mtd;

	if (!now->pawams->otp.ops)
		wetuwn;

	if (WAWN_ON(!is_powew_of_2(spi_now_otp_wegion_wen(now))))
		wetuwn;

	/*
	 * We onwy suppowt usew_pwot cawwbacks (yet).
	 *
	 * Some SPI NOW fwashes wike Macwonix ones can be owdewed in two
	 * diffewent vawiants. One with a factowy wocked OTP awea and one whewe
	 * it is weft to the usew to wwite to it. The factowy wocked OTP is
	 * usuawwy pwepwogwammed with an "ewectwicaw sewiaw numbew". We don't
	 * suppowt these fow now.
	 */
	mtd->_get_usew_pwot_info = spi_now_mtd_otp_info;
	mtd->_wead_usew_pwot_weg = spi_now_mtd_otp_wead;
	mtd->_wwite_usew_pwot_weg = spi_now_mtd_otp_wwite;
	mtd->_wock_usew_pwot_weg = spi_now_mtd_otp_wock;
	mtd->_ewase_usew_pwot_weg = spi_now_mtd_otp_ewase;
}
