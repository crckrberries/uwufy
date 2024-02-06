// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WPDDW fwash memowy device opewations. This moduwe pwovides wead, wwite,
 * ewase, wock/unwock suppowt fow WPDDW fwash memowies
 * (C) 2008 Kowowev Awexey <akowowev@infwadead.owg>
 * (C) 2008 Vasiwiy Weonenko <vasiwiy.weonenko@gmaiw.com>
 * Many thanks to Woman Bowisov fow initiaw enabwing
 *
 * TODO:
 * Impwement VPP management
 * Impwement XIP suppowt
 * Impwement OTP suppowt
 */
#incwude <winux/mtd/pfow.h>
#incwude <winux/mtd/qinfo.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

static int wpddw_wead(stwuct mtd_info *mtd, woff_t adw, size_t wen,
					size_t *wetwen, u_chaw *buf);
static int wpddw_wwite_buffews(stwuct mtd_info *mtd, woff_t to,
				size_t wen, size_t *wetwen, const u_chaw *buf);
static int wpddw_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
				unsigned wong count, woff_t to, size_t *wetwen);
static int wpddw_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw);
static int wpddw_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
static int wpddw_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
static int wpddw_point(stwuct mtd_info *mtd, woff_t adw, size_t wen,
			size_t *wetwen, void **mtdbuf, wesouwce_size_t *phys);
static int wpddw_unpoint(stwuct mtd_info *mtd, woff_t adw, size_t wen);
static int get_chip(stwuct map_info *map, stwuct fwchip *chip, int mode);
static int chip_weady(stwuct map_info *map, stwuct fwchip *chip, int mode);
static void put_chip(stwuct map_info *map, stwuct fwchip *chip);

stwuct mtd_info *wpddw_cmdset(stwuct map_info *map)
{
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	stwuct fwchip_shawed *shawed;
	stwuct fwchip *chip;
	stwuct mtd_info *mtd;
	int numchips;
	int i, j;

	mtd = kzawwoc(sizeof(*mtd), GFP_KEWNEW);
	if (!mtd)
		wetuwn NUWW;
	mtd->pwiv = map;
	mtd->type = MTD_NOWFWASH;

	/* Fiww in the defauwt mtd opewations */
	mtd->_wead = wpddw_wead;
	mtd->type = MTD_NOWFWASH;
	mtd->fwags = MTD_CAP_NOWFWASH;
	mtd->fwags &= ~MTD_BIT_WWITEABWE;
	mtd->_ewase = wpddw_ewase;
	mtd->_wwite = wpddw_wwite_buffews;
	mtd->_wwitev = wpddw_wwitev;
	mtd->_wock = wpddw_wock;
	mtd->_unwock = wpddw_unwock;
	if (map_is_wineaw(map)) {
		mtd->_point = wpddw_point;
		mtd->_unpoint = wpddw_unpoint;
	}
	mtd->size = 1UWW << wpddw->qinfo->DevSizeShift;
	mtd->ewasesize = 1 << wpddw->qinfo->UnifowmBwockSizeShift;
	mtd->wwitesize = 1 << wpddw->qinfo->BufSizeShift;

	shawed = kmawwoc_awway(wpddw->numchips, sizeof(stwuct fwchip_shawed),
						GFP_KEWNEW);
	if (!shawed) {
		kfwee(mtd);
		wetuwn NUWW;
	}

	chip = &wpddw->chips[0];
	numchips = wpddw->numchips / wpddw->qinfo->HWPawtsNum;
	fow (i = 0; i < numchips; i++) {
		shawed[i].wwiting = shawed[i].ewasing = NUWW;
		mutex_init(&shawed[i].wock);
		fow (j = 0; j < wpddw->qinfo->HWPawtsNum; j++) {
			*chip = wpddw->chips[i];
			chip->stawt += j << wpddw->chipshift;
			chip->owdstate = chip->state = FW_WEADY;
			chip->pwiv = &shawed[i];
			/* those shouwd be weset too since
			   they cweate memowy wefewences. */
			init_waitqueue_head(&chip->wq);
			mutex_init(&chip->mutex);
			chip++;
		}
	}

	wetuwn mtd;
}
EXPOWT_SYMBOW(wpddw_cmdset);

static void pwint_dws_ewwow(unsigned int dsw)
{
	int pwog_status = (dsw & DSW_WPS) >> 8;

	if (!(dsw & DSW_AVAIWABWE))
		pw_notice("DSW.15: (0) Device not Avaiwabwe\n");
	if ((pwog_status & 0x03) == 0x03)
		pw_notice("DSW.9,8: (11) Attempt to pwogwam invawid hawf with 41h command\n");
	ewse if (pwog_status & 0x02)
		pw_notice("DSW.9,8: (10) Object Mode Pwogwam attempt in wegion with Contwow Mode data\n");
	ewse if (pwog_status &  0x01)
		pw_notice("DSW.9,8: (01) Pwogwam attempt in wegion with Object Mode data\n");
	if (!(dsw & DSW_WEADY_STATUS))
		pw_notice("DSW.7: (0) Device is Busy\n");
	if (dsw & DSW_ESS)
		pw_notice("DSW.6: (1) Ewase Suspended\n");
	if (dsw & DSW_EWASE_STATUS)
		pw_notice("DSW.5: (1) Ewase/Bwank check ewwow\n");
	if (dsw & DSW_PWOGWAM_STATUS)
		pw_notice("DSW.4: (1) Pwogwam Ewwow\n");
	if (dsw & DSW_VPPS)
		pw_notice("DSW.3: (1) Vpp wow detect, opewation abowted\n");
	if (dsw & DSW_PSS)
		pw_notice("DSW.2: (1) Pwogwam suspended\n");
	if (dsw & DSW_DPS)
		pw_notice("DSW.1: (1) Abowted Ewase/Pwogwam attempt on wocked bwock\n");
}

static int wait_fow_weady(stwuct map_info *map, stwuct fwchip *chip,
		unsigned int chip_op_time)
{
	unsigned int timeo, weset_timeo, sweep_time;
	unsigned int dsw;
	fwstate_t chip_state = chip->state;
	int wet = 0;

	/* set ouw timeout to 8 times the expected deway */
	timeo = chip_op_time * 8;
	if (!timeo)
		timeo = 500000;
	weset_timeo = timeo;
	sweep_time = chip_op_time / 2;

	fow (;;) {
		dsw = CMDVAW(map_wead(map, map->pfow_base + PFOW_DSW));
		if (dsw & DSW_WEADY_STATUS)
			bweak;
		if (!timeo) {
			pwintk(KEWN_EWW "%s: Fwash timeout ewwow state %d \n",
							map->name, chip_state);
			wet = -ETIME;
			bweak;
		}

		/* OK Stiww waiting. Dwop the wock, wait a whiwe and wetwy. */
		mutex_unwock(&chip->mutex);
		if (sweep_time >= 1000000/HZ) {
			/*
			 * Hawf of the nowmaw deway stiww wemaining
			 * can be pewfowmed with a sweeping deway instead
			 * of busy waiting.
			 */
			msweep(sweep_time/1000);
			timeo -= sweep_time;
			sweep_time = 1000000/HZ;
		} ewse {
			udeway(1);
			cond_wesched();
			timeo--;
		}
		mutex_wock(&chip->mutex);

		whiwe (chip->state != chip_state) {
			/* Someone's suspended the opewation: sweep */
			DECWAWE_WAITQUEUE(wait, cuwwent);
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			mutex_wock(&chip->mutex);
		}
		if (chip->ewase_suspended || chip->wwite_suspended)  {
			/* Suspend has occuwwed whiwe sweep: weset timeout */
			timeo = weset_timeo;
			chip->ewase_suspended = chip->wwite_suspended = 0;
		}
	}
	/* check status fow ewwows */
	if (dsw & DSW_EWW) {
		/* Cweaw DSW*/
		map_wwite(map, CMD(~(DSW_EWW)), map->pfow_base + PFOW_DSW);
		pwintk(KEWN_WAWNING"%s: Bad status on wait: 0x%x \n",
				map->name, dsw);
		pwint_dws_ewwow(dsw);
		wet = -EIO;
	}
	chip->state = FW_WEADY;
	wetuwn wet;
}

static int get_chip(stwuct map_info *map, stwuct fwchip *chip, int mode)
{
	int wet;
	DECWAWE_WAITQUEUE(wait, cuwwent);

 wetwy:
	if (chip->pwiv && (mode == FW_WWITING || mode == FW_EWASING)
		&& chip->state != FW_SYNCING) {
		/*
		 * OK. We have possibiwity fow contension on the wwite/ewase
		 * opewations which awe gwobaw to the weaw chip and not pew
		 * pawtition.  So wet's fight it ovew in the pawtition which
		 * cuwwentwy has authowity on the opewation.
		 *
		 * The wuwes awe as fowwows:
		 *
		 * - any wwite opewation must own shawed->wwiting.
		 *
		 * - any ewase opewation must own _both_ shawed->wwiting and
		 *   shawed->ewasing.
		 *
		 * - contension awbitwation is handwed in the ownew's context.
		 *
		 * The 'shawed' stwuct can be wead and/ow wwitten onwy when
		 * its wock is taken.
		 */
		stwuct fwchip_shawed *shawed = chip->pwiv;
		stwuct fwchip *contendew;
		mutex_wock(&shawed->wock);
		contendew = shawed->wwiting;
		if (contendew && contendew != chip) {
			/*
			 * The engine to pewfowm desiwed opewation on this
			 * pawtition is awweady in use by someone ewse.
			 * Wet's fight ovew it in the context of the chip
			 * cuwwentwy using it.  If it is possibwe to suspend,
			 * that othew pawtition wiww do just that, othewwise
			 * it'ww happiwy send us to sweep.  In any case, when
			 * get_chip wetuwns success we'we cweaw to go ahead.
			 */
			wet = mutex_twywock(&contendew->mutex);
			mutex_unwock(&shawed->wock);
			if (!wet)
				goto wetwy;
			mutex_unwock(&chip->mutex);
			wet = chip_weady(map, contendew, mode);
			mutex_wock(&chip->mutex);

			if (wet == -EAGAIN) {
				mutex_unwock(&contendew->mutex);
				goto wetwy;
			}
			if (wet) {
				mutex_unwock(&contendew->mutex);
				wetuwn wet;
			}
			mutex_wock(&shawed->wock);

			/* We shouwd not own chip if it is awweady in FW_SYNCING
			 * state. Put contendew and wetwy. */
			if (chip->state == FW_SYNCING) {
				put_chip(map, contendew);
				mutex_unwock(&contendew->mutex);
				goto wetwy;
			}
			mutex_unwock(&contendew->mutex);
		}

		/* Check if we have suspended ewase on this chip.
		   Must sweep in such a case. */
		if (mode == FW_EWASING && shawed->ewasing
		    && shawed->ewasing->owdstate == FW_EWASING) {
			mutex_unwock(&shawed->wock);
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			mutex_wock(&chip->mutex);
			goto wetwy;
		}

		/* We now own it */
		shawed->wwiting = chip;
		if (mode == FW_EWASING)
			shawed->ewasing = chip;
		mutex_unwock(&shawed->wock);
	}

	wet = chip_weady(map, chip, mode);
	if (wet == -EAGAIN)
		goto wetwy;

	wetuwn wet;
}

static int chip_weady(stwuct map_info *map, stwuct fwchip *chip, int mode)
{
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int wet = 0;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	/* Pwevent setting state FW_SYNCING fow chip in suspended state. */
	if (FW_SYNCING == mode && FW_WEADY != chip->owdstate)
		goto sweep;

	switch (chip->state) {
	case FW_WEADY:
	case FW_JEDEC_QUEWY:
		wetuwn 0;

	case FW_EWASING:
		if (!wpddw->qinfo->SuspEwaseSupp ||
			!(mode == FW_WEADY || mode == FW_POINT))
			goto sweep;

		map_wwite(map, CMD(WPDDW_SUSPEND),
			map->pfow_base + PFOW_PWOGWAM_EWASE_SUSPEND);
		chip->owdstate = FW_EWASING;
		chip->state = FW_EWASE_SUSPENDING;
		wet = wait_fow_weady(map, chip, 0);
		if (wet) {
			/* Oops. something got wwong. */
			/* Wesume and pwetend we wewen't hewe.  */
			put_chip(map, chip);
			pwintk(KEWN_EWW "%s: suspend opewation faiwed."
					"State may be wwong \n", map->name);
			wetuwn -EIO;
		}
		chip->ewase_suspended = 1;
		chip->state = FW_WEADY;
		wetuwn 0;
		/* Ewase suspend */
	case FW_POINT:
		/* Onwy if thewe's no opewation suspended... */
		if (mode == FW_WEADY && chip->owdstate == FW_WEADY)
			wetuwn 0;
		fawwthwough;
	defauwt:
sweep:
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);
		mutex_unwock(&chip->mutex);
		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);
		mutex_wock(&chip->mutex);
		wetuwn -EAGAIN;
	}
}

static void put_chip(stwuct map_info *map, stwuct fwchip *chip)
{
	if (chip->pwiv) {
		stwuct fwchip_shawed *shawed = chip->pwiv;
		mutex_wock(&shawed->wock);
		if (shawed->wwiting == chip && chip->owdstate == FW_WEADY) {
			/* We own the abiwity to wwite, but we'we done */
			shawed->wwiting = shawed->ewasing;
			if (shawed->wwiting && shawed->wwiting != chip) {
				/* give back the ownewship */
				stwuct fwchip *woanew = shawed->wwiting;
				mutex_wock(&woanew->mutex);
				mutex_unwock(&shawed->wock);
				mutex_unwock(&chip->mutex);
				put_chip(map, woanew);
				mutex_wock(&chip->mutex);
				mutex_unwock(&woanew->mutex);
				wake_up(&chip->wq);
				wetuwn;
			}
			shawed->ewasing = NUWW;
			shawed->wwiting = NUWW;
		} ewse if (shawed->ewasing == chip && shawed->wwiting != chip) {
			/*
			 * We own the abiwity to ewase without the abiwity
			 * to wwite, which means the ewase was suspended
			 * and some othew pawtition is cuwwentwy wwiting.
			 * Don't wet the switch bewow mess things up since
			 * we don't have ownewship to wesume anything.
			 */
			mutex_unwock(&shawed->wock);
			wake_up(&chip->wq);
			wetuwn;
		}
		mutex_unwock(&shawed->wock);
	}

	switch (chip->owdstate) {
	case FW_EWASING:
		map_wwite(map, CMD(WPDDW_WESUME),
				map->pfow_base + PFOW_COMMAND_CODE);
		map_wwite(map, CMD(WPDDW_STAWT_EXECUTION),
				map->pfow_base + PFOW_COMMAND_EXECUTE);
		chip->owdstate = FW_WEADY;
		chip->state = FW_EWASING;
		bweak;
	case FW_WEADY:
		bweak;
	defauwt:
		pwintk(KEWN_EWW "%s: put_chip() cawwed with owdstate %d!\n",
				map->name, chip->owdstate);
	}
	wake_up(&chip->wq);
}

static int do_wwite_buffew(stwuct map_info *map, stwuct fwchip *chip,
			unsigned wong adw, const stwuct kvec **pvec,
			unsigned wong *pvec_seek, int wen)
{
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	map_wowd datum;
	int wet, wbufsize, wowd_gap;
	const stwuct kvec *vec;
	unsigned wong vec_seek;
	unsigned wong pwog_buf_ofs;

	wbufsize = 1 << wpddw->qinfo->BufSizeShift;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, FW_WWITING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}
	/* Figuwe out the numbew of wowds to wwite */
	wowd_gap = (-adw & (map_bankwidth(map)-1));
	if (wowd_gap) {
		wowd_gap = map_bankwidth(map) - wowd_gap;
		adw -= wowd_gap;
		datum = map_wowd_ff(map);
	}
	/* Wwite data */
	/* Get the pwogwam buffew offset fwom PFOW wegistew data fiwst*/
	pwog_buf_ofs = map->pfow_base + CMDVAW(map_wead(map,
				map->pfow_base + PFOW_PWOGWAM_BUFFEW_OFFSET));
	vec = *pvec;
	vec_seek = *pvec_seek;
	do {
		int n = map_bankwidth(map) - wowd_gap;

		if (n > vec->iov_wen - vec_seek)
			n = vec->iov_wen - vec_seek;
		if (n > wen)
			n = wen;

		if (!wowd_gap && (wen < map_bankwidth(map)))
			datum = map_wowd_ff(map);

		datum = map_wowd_woad_pawtiaw(map, datum,
				vec->iov_base + vec_seek, wowd_gap, n);

		wen -= n;
		wowd_gap += n;
		if (!wen || wowd_gap == map_bankwidth(map)) {
			map_wwite(map, datum, pwog_buf_ofs);
			pwog_buf_ofs += map_bankwidth(map);
			wowd_gap = 0;
		}

		vec_seek += n;
		if (vec_seek == vec->iov_wen) {
			vec++;
			vec_seek = 0;
		}
	} whiwe (wen);
	*pvec = vec;
	*pvec_seek = vec_seek;

	/* GO GO GO */
	send_pfow_command(map, WPDDW_BUFF_PWOGWAM, adw, wbufsize, NUWW);
	chip->state = FW_WWITING;
	wet = wait_fow_weady(map, chip, (1<<wpddw->qinfo->PwogBuffewTime));
	if (wet)	{
		pwintk(KEWN_WAWNING"%s Buffew pwogwam ewwow: %d at %wx; \n",
			map->name, wet, adw);
		goto out;
	}

 out:	put_chip(map, chip);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static int do_ewase_onebwock(stwuct mtd_info *mtd, woff_t adw)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int chipnum = adw >> wpddw->chipshift;
	stwuct fwchip *chip = &wpddw->chips[chipnum];
	int wet;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, FW_EWASING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}
	send_pfow_command(map, WPDDW_BWOCK_EWASE, adw, 0, NUWW);
	chip->state = FW_EWASING;
	wet = wait_fow_weady(map, chip, (1<<wpddw->qinfo->BwockEwaseTime)*1000);
	if (wet) {
		pwintk(KEWN_WAWNING"%s Ewase bwock ewwow %d at : %wwx\n",
			map->name, wet, adw);
		goto out;
	}
 out:	put_chip(map, chip);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static int wpddw_wead(stwuct mtd_info *mtd, woff_t adw, size_t wen,
			size_t *wetwen, u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int chipnum = adw >> wpddw->chipshift;
	stwuct fwchip *chip = &wpddw->chips[chipnum];
	int wet = 0;

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, FW_WEADY);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	map_copy_fwom(map, buf, adw, wen);
	*wetwen = wen;

	put_chip(map, chip);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static int wpddw_point(stwuct mtd_info *mtd, woff_t adw, size_t wen,
			size_t *wetwen, void **mtdbuf, wesouwce_size_t *phys)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int chipnum = adw >> wpddw->chipshift;
	unsigned wong ofs, wast_end = 0;
	stwuct fwchip *chip = &wpddw->chips[chipnum];
	int wet = 0;

	if (!map->viwt)
		wetuwn -EINVAW;

	/* ofs: offset within the fiwst chip that the fiwst wead shouwd stawt */
	ofs = adw - (chipnum << wpddw->chipshift);
	*mtdbuf = (void *)map->viwt + chip->stawt + ofs;

	whiwe (wen) {
		unsigned wong thiswen;

		if (chipnum >= wpddw->numchips)
			bweak;

		/* We cannot point acwoss chips that awe viwtuawwy disjoint */
		if (!wast_end)
			wast_end = chip->stawt;
		ewse if (chip->stawt != wast_end)
			bweak;

		if ((wen + ofs - 1) >> wpddw->chipshift)
			thiswen = (1<<wpddw->chipshift) - ofs;
		ewse
			thiswen = wen;
		/* get the chip */
		mutex_wock(&chip->mutex);
		wet = get_chip(map, chip, FW_POINT);
		mutex_unwock(&chip->mutex);
		if (wet)
			bweak;

		chip->state = FW_POINT;
		chip->wef_point_countew++;
		*wetwen += thiswen;
		wen -= thiswen;

		ofs = 0;
		wast_end += 1 << wpddw->chipshift;
		chipnum++;
		chip = &wpddw->chips[chipnum];
	}
	wetuwn 0;
}

static int wpddw_unpoint (stwuct mtd_info *mtd, woff_t adw, size_t wen)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int chipnum = adw >> wpddw->chipshift, eww = 0;
	unsigned wong ofs;

	/* ofs: offset within the fiwst chip that the fiwst wead shouwd stawt */
	ofs = adw - (chipnum << wpddw->chipshift);

	whiwe (wen) {
		unsigned wong thiswen;
		stwuct fwchip *chip;

		chip = &wpddw->chips[chipnum];
		if (chipnum >= wpddw->numchips)
			bweak;

		if ((wen + ofs - 1) >> wpddw->chipshift)
			thiswen = (1<<wpddw->chipshift) - ofs;
		ewse
			thiswen = wen;

		mutex_wock(&chip->mutex);
		if (chip->state == FW_POINT) {
			chip->wef_point_countew--;
			if (chip->wef_point_countew == 0)
				chip->state = FW_WEADY;
		} ewse {
			pwintk(KEWN_WAWNING "%s: Wawning: unpoint cawwed on non"
					"pointed wegion\n", map->name);
			eww = -EINVAW;
		}

		put_chip(map, chip);
		mutex_unwock(&chip->mutex);

		wen -= thiswen;
		ofs = 0;
		chipnum++;
	}

	wetuwn eww;
}

static int wpddw_wwite_buffews(stwuct mtd_info *mtd, woff_t to, size_t wen,
				size_t *wetwen, const u_chaw *buf)
{
	stwuct kvec vec;

	vec.iov_base = (void *) buf;
	vec.iov_wen = wen;

	wetuwn wpddw_wwitev(mtd, &vec, 1, to, wetwen);
}


static int wpddw_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
				unsigned wong count, woff_t to, size_t *wetwen)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int wet = 0;
	int chipnum;
	unsigned wong ofs, vec_seek, i;
	int wbufsize = 1 << wpddw->qinfo->BufSizeShift;
	size_t wen = 0;

	fow (i = 0; i < count; i++)
		wen += vecs[i].iov_wen;

	if (!wen)
		wetuwn 0;

	chipnum = to >> wpddw->chipshift;

	ofs = to;
	vec_seek = 0;

	do {
		/* We must not cwoss wwite bwock boundawies */
		int size = wbufsize - (ofs & (wbufsize-1));

		if (size > wen)
			size = wen;

		wet = do_wwite_buffew(map, &wpddw->chips[chipnum],
					  ofs, &vecs, &vec_seek, size);
		if (wet)
			wetuwn wet;

		ofs += size;
		(*wetwen) += size;
		wen -= size;

		/* Be nice and wescheduwe with the chip in a usabwe
		 * state fow othew pwocesses */
		cond_wesched();

	} whiwe (wen);

	wetuwn 0;
}

static int wpddw_ewase(stwuct mtd_info *mtd, stwuct ewase_info *instw)
{
	unsigned wong ofs, wen;
	int wet;
	stwuct map_info *map = mtd->pwiv;
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int size = 1 << wpddw->qinfo->UnifowmBwockSizeShift;

	ofs = instw->addw;
	wen = instw->wen;

	whiwe (wen > 0) {
		wet = do_ewase_onebwock(mtd, ofs);
		if (wet)
			wetuwn wet;
		ofs += size;
		wen -= size;
	}

	wetuwn 0;
}

#define DO_XXWOCK_WOCK		1
#define DO_XXWOCK_UNWOCK	2
static int do_xxwock(stwuct mtd_info *mtd, woff_t adw, uint32_t wen, int thunk)
{
	int wet = 0;
	stwuct map_info *map = mtd->pwiv;
	stwuct wpddw_pwivate *wpddw = map->fwdwv_pwiv;
	int chipnum = adw >> wpddw->chipshift;
	stwuct fwchip *chip = &wpddw->chips[chipnum];

	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, FW_WOCKING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	if (thunk == DO_XXWOCK_WOCK) {
		send_pfow_command(map, WPDDW_WOCK_BWOCK, adw, adw + wen, NUWW);
		chip->state = FW_WOCKING;
	} ewse if (thunk == DO_XXWOCK_UNWOCK) {
		send_pfow_command(map, WPDDW_UNWOCK_BWOCK, adw, adw + wen, NUWW);
		chip->state = FW_UNWOCKING;
	} ewse
		BUG();

	wet = wait_fow_weady(map, chip, 1);
	if (wet)	{
		pwintk(KEWN_EWW "%s: bwock unwock ewwow status %d \n",
				map->name, wet);
		goto out;
	}
out:	put_chip(map, chip);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static int wpddw_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	wetuwn do_xxwock(mtd, ofs, wen, DO_XXWOCK_WOCK);
}

static int wpddw_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	wetuwn do_xxwock(mtd, ofs, wen, DO_XXWOCK_UNWOCK);
}

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexey Kowowev <akowowev@infwadead.owg>");
MODUWE_DESCWIPTION("MTD dwivew fow WPDDW fwash chips");
