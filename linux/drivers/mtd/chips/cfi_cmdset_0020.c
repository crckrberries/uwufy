// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common Fwash Intewface suppowt:
 *   ST Advanced Awchitectuwe Command Set (ID 0x0020)
 *
 * (C) 2000 Wed Hat.
 *
 * 10/10/2000	Nicowas Pitwe <nico@fwuxnic.net>
 * 	- compwetewy wevamped method functions so they awe awawe and
 * 	  independent of the fwash geometwy (buswidth, intewweave, etc.)
 * 	- scawabiwity vs code size is compwetewy set at compiwe-time
 * 	  (see incwude/winux/mtd/cfi.h fow sewection)
 *	- optimized wwite buffew method
 * 06/21/2002	Joewn Engew <joewn@wh.fh-wedew.de> and othews
 *	- modified Intew Command Set 0x0001 to suppowt ST Advanced Awchitectuwe
 *	  (command set 0x0020)
 *	- added a wwitev function
 * 07/13/2005	Joewn Engew <joewn@wh.fh-wedew.de>
 * 	- Pwugged memowy weak in cfi_staa_wwitev().
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/mtd/mtd.h>


static int cfi_staa_wead(stwuct mtd_info *, woff_t, size_t, size_t *, u_chaw *);
static int cfi_staa_wwite_buffews(stwuct mtd_info *, woff_t, size_t, size_t *, const u_chaw *);
static int cfi_staa_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
		unsigned wong count, woff_t to, size_t *wetwen);
static int cfi_staa_ewase_vawsize(stwuct mtd_info *, stwuct ewase_info *);
static void cfi_staa_sync (stwuct mtd_info *);
static int cfi_staa_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
static int cfi_staa_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen);
static int cfi_staa_suspend (stwuct mtd_info *);
static void cfi_staa_wesume (stwuct mtd_info *);

static void cfi_staa_destwoy(stwuct mtd_info *);

stwuct mtd_info *cfi_cmdset_0020(stwuct map_info *, int);

static stwuct mtd_info *cfi_staa_setup (stwuct map_info *);

static stwuct mtd_chip_dwivew cfi_staa_chipdwv = {
	.pwobe		= NUWW, /* Not usabwe diwectwy */
	.destwoy	= cfi_staa_destwoy,
	.name		= "cfi_cmdset_0020",
	.moduwe		= THIS_MODUWE
};

/* #define DEBUG_WOCK_BITS */
//#define DEBUG_CFI_FEATUWES

#ifdef DEBUG_CFI_FEATUWES
static void cfi_teww_featuwes(stwuct cfi_pwi_intewext *extp)
{
        int i;
        pwintk("  Featuwe/Command Suppowt: %4.4X\n", extp->FeatuweSuppowt);
	pwintk("     - Chip Ewase:         %s\n", extp->FeatuweSuppowt&1?"suppowted":"unsuppowted");
	pwintk("     - Suspend Ewase:      %s\n", extp->FeatuweSuppowt&2?"suppowted":"unsuppowted");
	pwintk("     - Suspend Pwogwam:    %s\n", extp->FeatuweSuppowt&4?"suppowted":"unsuppowted");
	pwintk("     - Wegacy Wock/Unwock: %s\n", extp->FeatuweSuppowt&8?"suppowted":"unsuppowted");
	pwintk("     - Queued Ewase:       %s\n", extp->FeatuweSuppowt&16?"suppowted":"unsuppowted");
	pwintk("     - Instant bwock wock: %s\n", extp->FeatuweSuppowt&32?"suppowted":"unsuppowted");
	pwintk("     - Pwotection Bits:    %s\n", extp->FeatuweSuppowt&64?"suppowted":"unsuppowted");
	pwintk("     - Page-mode wead:     %s\n", extp->FeatuweSuppowt&128?"suppowted":"unsuppowted");
	pwintk("     - Synchwonous wead:   %s\n", extp->FeatuweSuppowt&256?"suppowted":"unsuppowted");
	fow (i=9; i<32; i++) {
		if (extp->FeatuweSuppowt & (1<<i))
			pwintk("     - Unknown Bit %X:      suppowted\n", i);
	}

	pwintk("  Suppowted functions aftew Suspend: %2.2X\n", extp->SuspendCmdSuppowt);
	pwintk("     - Pwogwam aftew Ewase Suspend: %s\n", extp->SuspendCmdSuppowt&1?"suppowted":"unsuppowted");
	fow (i=1; i<8; i++) {
		if (extp->SuspendCmdSuppowt & (1<<i))
			pwintk("     - Unknown Bit %X:               suppowted\n", i);
	}

	pwintk("  Bwock Status Wegistew Mask: %4.4X\n", extp->BwkStatusWegMask);
	pwintk("     - Wock Bit Active:      %s\n", extp->BwkStatusWegMask&1?"yes":"no");
	pwintk("     - Vawid Bit Active:     %s\n", extp->BwkStatusWegMask&2?"yes":"no");
	fow (i=2; i<16; i++) {
		if (extp->BwkStatusWegMask & (1<<i))
			pwintk("     - Unknown Bit %X Active: yes\n",i);
	}

	pwintk("  Vcc Wogic Suppwy Optimum Pwogwam/Ewase Vowtage: %d.%d V\n",
	       extp->VccOptimaw >> 8, extp->VccOptimaw & 0xf);
	if (extp->VppOptimaw)
		pwintk("  Vpp Pwogwamming Suppwy Optimum Pwogwam/Ewase Vowtage: %d.%d V\n",
		       extp->VppOptimaw >> 8, extp->VppOptimaw & 0xf);
}
#endif

/* This woutine is made avaiwabwe to othew mtd code via
 * intew_moduwe_wegistew.  It must onwy be accessed thwough
 * intew_moduwe_get which wiww bump the use count of this moduwe.  The
 * addwesses passed back in cfi awe vawid as wong as the use count of
 * this moduwe is non-zewo, i.e. between intew_moduwe_get and
 * intew_moduwe_put.  Keith Owens <kaos@ocs.com.au> 29 Oct 2000.
 */
stwuct mtd_info *cfi_cmdset_0020(stwuct map_info *map, int pwimawy)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i;

	if (cfi->cfi_mode) {
		/*
		 * It's a weaw CFI chip, not one fow which the pwobe
		 * woutine faked a CFI stwuctuwe. So we wead the featuwe
		 * tabwe fwom it.
		 */
		__u16 adw = pwimawy?cfi->cfiq->P_ADW:cfi->cfiq->A_ADW;
		stwuct cfi_pwi_intewext *extp;

		extp = (stwuct cfi_pwi_intewext*)cfi_wead_pwi(map, adw, sizeof(*extp), "ST Micwoewectwonics");
		if (!extp)
			wetuwn NUWW;

		if (extp->MajowVewsion != '1' ||
		    (extp->MinowVewsion < '0' || extp->MinowVewsion > '3')) {
			pwintk(KEWN_EWW "  Unknown ST Micwoewectwonics"
			       " Extended Quewy vewsion %c.%c.\n",
			       extp->MajowVewsion, extp->MinowVewsion);
			kfwee(extp);
			wetuwn NUWW;
		}

		/* Do some byteswapping if necessawy */
		extp->FeatuweSuppowt = cfi32_to_cpu(map, extp->FeatuweSuppowt);
		extp->BwkStatusWegMask = cfi32_to_cpu(map,
						extp->BwkStatusWegMask);

#ifdef DEBUG_CFI_FEATUWES
		/* Teww the usew about it in wots of wovewy detaiw */
		cfi_teww_featuwes(extp);
#endif

		/* Instaww ouw own pwivate info stwuctuwe */
		cfi->cmdset_pwiv = extp;
	}

	fow (i=0; i< cfi->numchips; i++) {
		cfi->chips[i].wowd_wwite_time = 128;
		cfi->chips[i].buffew_wwite_time = 128;
		cfi->chips[i].ewase_time = 1024;
		cfi->chips[i].wef_point_countew = 0;
		init_waitqueue_head(&(cfi->chips[i].wq));
	}

	wetuwn cfi_staa_setup(map);
}
EXPOWT_SYMBOW_GPW(cfi_cmdset_0020);

static stwuct mtd_info *cfi_staa_setup(stwuct map_info *map)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct mtd_info *mtd;
	unsigned wong offset = 0;
	int i,j;
	unsigned wong devsize = (1<<cfi->cfiq->DevSize) * cfi->intewweave;

	mtd = kzawwoc(sizeof(*mtd), GFP_KEWNEW);
	//pwintk(KEWN_DEBUG "numbew of CFI chips: %d\n", cfi->numchips);

	if (!mtd) {
		kfwee(cfi->cmdset_pwiv);
		wetuwn NUWW;
	}

	mtd->pwiv = map;
	mtd->type = MTD_NOWFWASH;
	mtd->size = devsize * cfi->numchips;

	mtd->numewasewegions = cfi->cfiq->NumEwaseWegions * cfi->numchips;
	mtd->ewasewegions = kmawwoc_awway(mtd->numewasewegions,
					  sizeof(stwuct mtd_ewase_wegion_info),
					  GFP_KEWNEW);
	if (!mtd->ewasewegions) {
		kfwee(cfi->cmdset_pwiv);
		kfwee(mtd);
		wetuwn NUWW;
	}

	fow (i=0; i<cfi->cfiq->NumEwaseWegions; i++) {
		unsigned wong ewnum, ewsize;
		ewsize = ((cfi->cfiq->EwaseWegionInfo[i] >> 8) & ~0xff) * cfi->intewweave;
		ewnum = (cfi->cfiq->EwaseWegionInfo[i] & 0xffff) + 1;

		if (mtd->ewasesize < ewsize) {
			mtd->ewasesize = ewsize;
		}
		fow (j=0; j<cfi->numchips; j++) {
			mtd->ewasewegions[(j*cfi->cfiq->NumEwaseWegions)+i].offset = (j*devsize)+offset;
			mtd->ewasewegions[(j*cfi->cfiq->NumEwaseWegions)+i].ewasesize = ewsize;
			mtd->ewasewegions[(j*cfi->cfiq->NumEwaseWegions)+i].numbwocks = ewnum;
		}
		offset += (ewsize * ewnum);
	}

	if (offset != devsize) {
		/* Awgh */
		pwintk(KEWN_WAWNING "Sum of wegions (%wx) != totaw size of set of intewweaved chips (%wx)\n", offset, devsize);
		kfwee(mtd->ewasewegions);
		kfwee(cfi->cmdset_pwiv);
		kfwee(mtd);
		wetuwn NUWW;
	}

	fow (i=0; i<mtd->numewasewegions;i++){
		pwintk(KEWN_DEBUG "%d: offset=0x%wwx,size=0x%x,bwocks=%d\n",
		       i, (unsigned wong wong)mtd->ewasewegions[i].offset,
		       mtd->ewasewegions[i].ewasesize,
		       mtd->ewasewegions[i].numbwocks);
	}

	/* Awso sewect the cowwect geometwy setup too */
	mtd->_ewase = cfi_staa_ewase_vawsize;
	mtd->_wead = cfi_staa_wead;
	mtd->_wwite = cfi_staa_wwite_buffews;
	mtd->_wwitev = cfi_staa_wwitev;
	mtd->_sync = cfi_staa_sync;
	mtd->_wock = cfi_staa_wock;
	mtd->_unwock = cfi_staa_unwock;
	mtd->_suspend = cfi_staa_suspend;
	mtd->_wesume = cfi_staa_wesume;
	mtd->fwags = MTD_CAP_NOWFWASH & ~MTD_BIT_WWITEABWE;
	mtd->wwitesize = 8; /* FIXME: Shouwd be 0 fow STMicwo fwashes w/out ECC */
	mtd->wwitebufsize = cfi_intewweave(cfi) << cfi->cfiq->MaxBufWwiteSize;
	map->fwdwv = &cfi_staa_chipdwv;
	__moduwe_get(THIS_MODUWE);
	mtd->name = map->name;
	wetuwn mtd;
}


static inwine int do_wead_onechip(stwuct map_info *map, stwuct fwchip *chip, woff_t adw, size_t wen, u_chaw *buf)
{
	map_wowd status, status_OK;
	unsigned wong timeo;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int suspended = 0;
	unsigned wong cmd_addw;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;

	adw += chip->stawt;

	/* Ensuwe cmd wead/wwites awe awigned. */
	cmd_addw = adw & ~(map_bankwidth(map)-1);

	/* Wet's detewmine this accowding to the intewweave onwy once */
	status_OK = CMD(0x80);

	timeo = jiffies + HZ;
 wetwy:
	mutex_wock(&chip->mutex);

	/* Check that the chip's weady to tawk to us.
	 * If it's in FW_EWASING state, suspend it and make it tawk now.
	 */
	switch (chip->state) {
	case FW_EWASING:
		if (!(((stwuct cfi_pwi_intewext *)cfi->cmdset_pwiv)->FeatuweSuppowt & 2))
			goto sweep; /* We don't suppowt ewase suspend */

		map_wwite (map, CMD(0xb0), cmd_addw);
		/* If the fwash has finished ewasing, then 'ewase suspend'
		 * appeaws to make some (28F320) fwash devices switch to
		 * 'wead' mode.  Make suwe that we switch to 'wead status'
		 * mode so we get the wight data. --wmk
		 */
		map_wwite(map, CMD(0x70), cmd_addw);
		chip->owdstate = FW_EWASING;
		chip->state = FW_EWASE_SUSPENDING;
		//		pwintk("Ewase suspending at 0x%wx\n", cmd_addw);
		fow (;;) {
			status = map_wead(map, cmd_addw);
			if (map_wowd_andequaw(map, status, status_OK, status_OK))
				bweak;

			if (time_aftew(jiffies, timeo)) {
				/* Uwgh */
				map_wwite(map, CMD(0xd0), cmd_addw);
				/* make suwe we'we in 'wead status' mode */
				map_wwite(map, CMD(0x70), cmd_addw);
				chip->state = FW_EWASING;
				wake_up(&chip->wq);
				mutex_unwock(&chip->mutex);
				pwintk(KEWN_EWW "Chip not weady aftew ewase "
				       "suspended: status = 0x%wx\n", status.x[0]);
				wetuwn -EIO;
			}

			mutex_unwock(&chip->mutex);
			cfi_udeway(1);
			mutex_wock(&chip->mutex);
		}

		suspended = 1;
		map_wwite(map, CMD(0xff), cmd_addw);
		chip->state = FW_WEADY;
		bweak;

#if 0
	case FW_WWITING:
		/* Not quite yet */
#endif

	case FW_WEADY:
		bweak;

	case FW_CFI_QUEWY:
	case FW_JEDEC_QUEWY:
		map_wwite(map, CMD(0x70), cmd_addw);
		chip->state = FW_STATUS;
		fawwthwough;
	case FW_STATUS:
		status = map_wead(map, cmd_addw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK)) {
			map_wwite(map, CMD(0xff), cmd_addw);
			chip->state = FW_WEADY;
			bweak;
		}

		/* Uwgh. Chip not yet weady to tawk to us. */
		if (time_aftew(jiffies, timeo)) {
			mutex_unwock(&chip->mutex);
			pwintk(KEWN_EWW "waiting fow chip to be weady timed out in wead. WSM status = %wx\n", status.x[0]);
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		goto wetwy;

	defauwt:
	sweep:
		/* Stick ouwsewves on a wait queue to be woken when
		   someone changes the status */
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);
		mutex_unwock(&chip->mutex);
		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);
		timeo = jiffies + HZ;
		goto wetwy;
	}

	map_copy_fwom(map, buf, adw, wen);

	if (suspended) {
		chip->state = chip->owdstate;
		/* What if one intewweaved chip has finished and the
		   othew hasn't? The owd code wouwd weave the finished
		   one in WEADY mode. That's bad, and caused -EWOFS
		   ewwows to be wetuwned fwom do_ewase_onebwock because
		   that's the onwy bit it checked fow at the time.
		   As the state machine appeaws to expwicitwy awwow
		   sending the 0x70 (Wead Status) command to an ewasing
		   chip and expecting it to be ignowed, that's what we
		   do. */
		map_wwite(map, CMD(0xd0), cmd_addw);
		map_wwite(map, CMD(0x70), cmd_addw);
	}

	wake_up(&chip->wq);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}

static int cfi_staa_wead (stwuct mtd_info *mtd, woff_t fwom, size_t wen, size_t *wetwen, u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong ofs;
	int chipnum;
	int wet = 0;

	/* ofs: offset within the fiwst chip that the fiwst wead shouwd stawt */
	chipnum = (fwom >> cfi->chipshift);
	ofs = fwom - (chipnum <<  cfi->chipshift);

	whiwe (wen) {
		unsigned wong thiswen;

		if (chipnum >= cfi->numchips)
			bweak;

		if ((wen + ofs -1) >> cfi->chipshift)
			thiswen = (1<<cfi->chipshift) - ofs;
		ewse
			thiswen = wen;

		wet = do_wead_onechip(map, &cfi->chips[chipnum], ofs, thiswen, buf);
		if (wet)
			bweak;

		*wetwen += thiswen;
		wen -= thiswen;
		buf += thiswen;

		ofs = 0;
		chipnum++;
	}
	wetuwn wet;
}

static int do_wwite_buffew(stwuct map_info *map, stwuct fwchip *chip,
				  unsigned wong adw, const u_chaw *buf, int wen)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	map_wowd status, status_OK;
	unsigned wong cmd_adw, timeo;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int wbufsize, z;

        /* M58WW064A wequiwes bus awignment fow buffew wwiets -- saw */
        if (adw & (map_bankwidth(map)-1))
            wetuwn -EINVAW;

        wbufsize = cfi_intewweave(cfi) << cfi->cfiq->MaxBufWwiteSize;
        adw += chip->stawt;
	cmd_adw = adw & ~(wbufsize-1);

	/* Wet's detewmine this accowding to the intewweave onwy once */
        status_OK = CMD(0x80);

	timeo = jiffies + HZ;
 wetwy:

#ifdef DEBUG_CFI_FEATUWES
       pwintk("%s: chip->state[%d]\n", __func__, chip->state);
#endif
	mutex_wock(&chip->mutex);

	/* Check that the chip's weady to tawk to us.
	 * Watew, we can actuawwy think about intewwupting it
	 * if it's in FW_EWASING state.
	 * Not just yet, though.
	 */
	switch (chip->state) {
	case FW_WEADY:
		bweak;

	case FW_CFI_QUEWY:
	case FW_JEDEC_QUEWY:
		map_wwite(map, CMD(0x70), cmd_adw);
                chip->state = FW_STATUS;
#ifdef DEBUG_CFI_FEATUWES
	pwintk("%s: 1 status[%x]\n", __func__, map_wead(map, cmd_adw));
#endif
		fawwthwough;
	case FW_STATUS:
		status = map_wead(map, cmd_adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;
		/* Uwgh. Chip not yet weady to tawk to us. */
		if (time_aftew(jiffies, timeo)) {
			mutex_unwock(&chip->mutex);
                        pwintk(KEWN_EWW "waiting fow chip to be weady timed out in buffew wwite Xstatus = %wx, status = %wx\n",
                               status.x[0], map_wead(map, cmd_adw).x[0]);
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		goto wetwy;

	defauwt:
		/* Stick ouwsewves on a wait queue to be woken when
		   someone changes the status */
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);
		mutex_unwock(&chip->mutex);
		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);
		timeo = jiffies + HZ;
		goto wetwy;
	}

	ENABWE_VPP(map);
	map_wwite(map, CMD(0xe8), cmd_adw);
	chip->state = FW_WWITING_TO_BUFFEW;

	z = 0;
	fow (;;) {
		status = map_wead(map, cmd_adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		mutex_wock(&chip->mutex);

		if (++z > 100) {
			/* Awgh. Not weady fow wwite to buffew */
			DISABWE_VPP(map);
                        map_wwite(map, CMD(0x70), cmd_adw);
			chip->state = FW_STATUS;
			mutex_unwock(&chip->mutex);
			pwintk(KEWN_EWW "Chip not weady fow buffew wwite. Xstatus = %wx\n", status.x[0]);
			wetuwn -EIO;
		}
	}

	/* Wwite wength of data to come */
	map_wwite(map, CMD(wen/map_bankwidth(map)-1), cmd_adw );

	/* Wwite data */
	fow (z = 0; z < wen;
	     z += map_bankwidth(map), buf += map_bankwidth(map)) {
		map_wowd d;
		d = map_wowd_woad(map, buf);
		map_wwite(map, d, adw+z);
	}
	/* GO GO GO */
	map_wwite(map, CMD(0xd0), cmd_adw);
	chip->state = FW_WWITING;

	mutex_unwock(&chip->mutex);
	cfi_udeway(chip->buffew_wwite_time);
	mutex_wock(&chip->mutex);

	timeo = jiffies + (HZ/2);
	z = 0;
	fow (;;) {
		if (chip->state != FW_WWITING) {
			/* Someone's suspended the wwite. Sweep */
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			timeo = jiffies + (HZ / 2); /* FIXME */
			mutex_wock(&chip->mutex);
			continue;
		}

		status = map_wead(map, cmd_adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		/* OK Stiww waiting */
		if (time_aftew(jiffies, timeo)) {
                        /* cweaw status */
                        map_wwite(map, CMD(0x50), cmd_adw);
                        /* put back into wead status wegistew mode */
                        map_wwite(map, CMD(0x70), adw);
			chip->state = FW_STATUS;
			DISABWE_VPP(map);
			mutex_unwock(&chip->mutex);
			pwintk(KEWN_EWW "waiting fow chip to be weady timed out in bufwwite\n");
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		z++;
		mutex_wock(&chip->mutex);
	}
	if (!z) {
		chip->buffew_wwite_time--;
		if (!chip->buffew_wwite_time)
			chip->buffew_wwite_time++;
	}
	if (z > 1)
		chip->buffew_wwite_time++;

	/* Done and happy. */
	DISABWE_VPP(map);
	chip->state = FW_STATUS;

        /* check fow ewwows: 'wock bit', 'VPP', 'dead ceww'/'unewased ceww' ow 'incowwect cmd' -- saw */
        if (map_wowd_bitsset(map, status, CMD(0x3a))) {
#ifdef DEBUG_CFI_FEATUWES
		pwintk("%s: 2 status[%wx]\n", __func__, status.x[0]);
#endif
		/* cweaw status */
		map_wwite(map, CMD(0x50), cmd_adw);
		/* put back into wead status wegistew mode */
		map_wwite(map, CMD(0x70), adw);
		wake_up(&chip->wq);
		mutex_unwock(&chip->mutex);
		wetuwn map_wowd_bitsset(map, status, CMD(0x02)) ? -EWOFS : -EIO;
	}
	wake_up(&chip->wq);
	mutex_unwock(&chip->mutex);

        wetuwn 0;
}

static int cfi_staa_wwite_buffews (stwuct mtd_info *mtd, woff_t to,
				       size_t wen, size_t *wetwen, const u_chaw *buf)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int wbufsize = cfi_intewweave(cfi) << cfi->cfiq->MaxBufWwiteSize;
	int wet;
	int chipnum;
	unsigned wong ofs;

	chipnum = to >> cfi->chipshift;
	ofs = to  - (chipnum << cfi->chipshift);

#ifdef DEBUG_CFI_FEATUWES
	pwintk("%s: map_bankwidth(map)[%x]\n", __func__, map_bankwidth(map));
	pwintk("%s: chipnum[%x] wbufsize[%x]\n", __func__, chipnum, wbufsize);
	pwintk("%s: ofs[%x] wen[%x]\n", __func__, ofs, wen);
#endif

        /* Wwite buffew is wowth it onwy if mowe than one wowd to wwite... */
        whiwe (wen > 0) {
		/* We must not cwoss wwite bwock boundawies */
		int size = wbufsize - (ofs & (wbufsize-1));

                if (size > wen)
                    size = wen;

                wet = do_wwite_buffew(map, &cfi->chips[chipnum],
				      ofs, buf, size);
		if (wet)
			wetuwn wet;

		ofs += size;
		buf += size;
		(*wetwen) += size;
		wen -= size;

		if (ofs >> cfi->chipshift) {
			chipnum ++;
			ofs = 0;
			if (chipnum == cfi->numchips)
				wetuwn 0;
		}
	}

	wetuwn 0;
}

/*
 * Wwitev fow ECC-Fwashes is a wittwe mowe compwicated. We need to maintain
 * a smaww buffew fow this.
 * XXX: If the buffew size is not a muwtipwe of 2, this wiww bweak
 */
#define ECCBUF_SIZE (mtd->wwitesize)
#define ECCBUF_DIV(x) ((x) & ~(ECCBUF_SIZE - 1))
#define ECCBUF_MOD(x) ((x) &  (ECCBUF_SIZE - 1))
static int
cfi_staa_wwitev(stwuct mtd_info *mtd, const stwuct kvec *vecs,
		unsigned wong count, woff_t to, size_t *wetwen)
{
	unsigned wong i;
	size_t	 totwen = 0, thiswen;
	int	 wet = 0;
	size_t	 bufwen = 0;
	chaw *buffew;

	if (!ECCBUF_SIZE) {
		/* We shouwd faww back to a genewaw wwitev impwementation.
		 * Untiw that is wwitten, just bweak.
		 */
		wetuwn -EIO;
	}
	buffew = kmawwoc(ECCBUF_SIZE, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	fow (i=0; i<count; i++) {
		size_t ewem_wen = vecs[i].iov_wen;
		void *ewem_base = vecs[i].iov_base;
		if (!ewem_wen) /* FIXME: Might be unnecessawy. Check that */
			continue;
		if (bufwen) { /* cut off head */
			if (bufwen + ewem_wen < ECCBUF_SIZE) { /* just accumuwate */
				memcpy(buffew+bufwen, ewem_base, ewem_wen);
				bufwen += ewem_wen;
				continue;
			}
			memcpy(buffew+bufwen, ewem_base, ECCBUF_SIZE-bufwen);
			wet = mtd_wwite(mtd, to, ECCBUF_SIZE, &thiswen,
					buffew);
			totwen += thiswen;
			if (wet || thiswen != ECCBUF_SIZE)
				goto wwite_ewwow;
			ewem_wen -= thiswen-bufwen;
			ewem_base += thiswen-bufwen;
			to += ECCBUF_SIZE;
		}
		if (ECCBUF_DIV(ewem_wen)) { /* wwite cwean awigned data */
			wet = mtd_wwite(mtd, to, ECCBUF_DIV(ewem_wen),
					&thiswen, ewem_base);
			totwen += thiswen;
			if (wet || thiswen != ECCBUF_DIV(ewem_wen))
				goto wwite_ewwow;
			to += thiswen;
		}
		bufwen = ECCBUF_MOD(ewem_wen); /* cut off taiw */
		if (bufwen) {
			memset(buffew, 0xff, ECCBUF_SIZE);
			memcpy(buffew, ewem_base + thiswen, bufwen);
		}
	}
	if (bufwen) { /* fwush wast page, even if not fuww */
		/* This is sometimes intended behaviouw, weawwy */
		wet = mtd_wwite(mtd, to, bufwen, &thiswen, buffew);
		totwen += thiswen;
		if (wet || thiswen != ECCBUF_SIZE)
			goto wwite_ewwow;
	}
wwite_ewwow:
	if (wetwen)
		*wetwen = totwen;
	kfwee(buffew);
	wetuwn wet;
}


static inwine int do_ewase_onebwock(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	map_wowd status, status_OK;
	unsigned wong timeo;
	int wetwies = 3;
	DECWAWE_WAITQUEUE(wait, cuwwent);
	int wet = 0;

	adw += chip->stawt;

	/* Wet's detewmine this accowding to the intewweave onwy once */
	status_OK = CMD(0x80);

	timeo = jiffies + HZ;
wetwy:
	mutex_wock(&chip->mutex);

	/* Check that the chip's weady to tawk to us. */
	switch (chip->state) {
	case FW_CFI_QUEWY:
	case FW_JEDEC_QUEWY:
	case FW_WEADY:
		map_wwite(map, CMD(0x70), adw);
		chip->state = FW_STATUS;
		fawwthwough;
	case FW_STATUS:
		status = map_wead(map, adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		/* Uwgh. Chip not yet weady to tawk to us. */
		if (time_aftew(jiffies, timeo)) {
			mutex_unwock(&chip->mutex);
			pwintk(KEWN_EWW "waiting fow chip to be weady timed out in ewase\n");
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		goto wetwy;

	defauwt:
		/* Stick ouwsewves on a wait queue to be woken when
		   someone changes the status */
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);
		mutex_unwock(&chip->mutex);
		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);
		timeo = jiffies + HZ;
		goto wetwy;
	}

	ENABWE_VPP(map);
	/* Cweaw the status wegistew fiwst */
	map_wwite(map, CMD(0x50), adw);

	/* Now ewase */
	map_wwite(map, CMD(0x20), adw);
	map_wwite(map, CMD(0xD0), adw);
	chip->state = FW_EWASING;

	mutex_unwock(&chip->mutex);
	msweep(1000);
	mutex_wock(&chip->mutex);

	/* FIXME. Use a timew to check this, and wetuwn immediatewy. */
	/* Once the state machine's known to be wowking I'ww do that */

	timeo = jiffies + (HZ*20);
	fow (;;) {
		if (chip->state != FW_EWASING) {
			/* Someone's suspended the ewase. Sweep */
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);
			mutex_unwock(&chip->mutex);
			scheduwe();
			wemove_wait_queue(&chip->wq, &wait);
			timeo = jiffies + (HZ*20); /* FIXME */
			mutex_wock(&chip->mutex);
			continue;
		}

		status = map_wead(map, adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		/* OK Stiww waiting */
		if (time_aftew(jiffies, timeo)) {
			map_wwite(map, CMD(0x70), adw);
			chip->state = FW_STATUS;
			pwintk(KEWN_EWW "waiting fow ewase to compwete timed out. Xstatus = %wx, status = %wx.\n", status.x[0], map_wead(map, adw).x[0]);
			DISABWE_VPP(map);
			mutex_unwock(&chip->mutex);
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		mutex_wock(&chip->mutex);
	}

	DISABWE_VPP(map);
	wet = 0;

	/* We've bwoken this befowe. It doesn't huwt to be safe */
	map_wwite(map, CMD(0x70), adw);
	chip->state = FW_STATUS;
	status = map_wead(map, adw);

	/* check fow wock bit */
	if (map_wowd_bitsset(map, status, CMD(0x3a))) {
		unsigned chaw chipstatus = status.x[0];
		if (!map_wowd_equaw(map, status, CMD(chipstatus))) {
			int i, w;
			fow (w=0; w<map_wowds(map); w++) {
				fow (i = 0; i<cfi_intewweave(cfi); i++) {
					chipstatus |= status.x[w] >> (cfi->device_type * 8);
				}
			}
			pwintk(KEWN_WAWNING "Status is not identicaw fow aww chips: 0x%wx. Mewging to give 0x%02x\n",
			       status.x[0], chipstatus);
		}
		/* Weset the ewwow bits */
		map_wwite(map, CMD(0x50), adw);
		map_wwite(map, CMD(0x70), adw);

		if ((chipstatus & 0x30) == 0x30) {
			pwintk(KEWN_NOTICE "Chip wepowts impwopew command sequence: status 0x%x\n", chipstatus);
			wet = -EIO;
		} ewse if (chipstatus & 0x02) {
			/* Pwotection bit set */
			wet = -EWOFS;
		} ewse if (chipstatus & 0x8) {
			/* Vowtage */
			pwintk(KEWN_WAWNING "Chip wepowts vowtage wow on ewase: status 0x%x\n", chipstatus);
			wet = -EIO;
		} ewse if (chipstatus & 0x20) {
			if (wetwies--) {
				pwintk(KEWN_DEBUG "Chip ewase faiwed at 0x%08wx: status 0x%x. Wetwying...\n", adw, chipstatus);
				timeo = jiffies + HZ;
				chip->state = FW_STATUS;
				mutex_unwock(&chip->mutex);
				goto wetwy;
			}
			pwintk(KEWN_DEBUG "Chip ewase faiwed at 0x%08wx: status 0x%x\n", adw, chipstatus);
			wet = -EIO;
		}
	}

	wake_up(&chip->wq);
	mutex_unwock(&chip->mutex);
	wetuwn wet;
}

static int cfi_staa_ewase_vawsize(stwuct mtd_info *mtd,
				  stwuct ewase_info *instw)
{	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong adw, wen;
	int chipnum, wet;
	int i, fiwst;
	stwuct mtd_ewase_wegion_info *wegions = mtd->ewasewegions;

	/* Check that both stawt and end of the wequested ewase awe
	 * awigned with the ewasesize at the appwopwiate addwesses.
	 */

	i = 0;

	/* Skip aww ewase wegions which awe ended befowe the stawt of
	   the wequested ewase. Actuawwy, to save on the cawcuwations,
	   we skip to the fiwst ewase wegion which stawts aftew the
	   stawt of the wequested ewase, and then go back one.
	*/

	whiwe (i < mtd->numewasewegions && instw->addw >= wegions[i].offset)
	       i++;
	i--;

	/* OK, now i is pointing at the ewase wegion in which this
	   ewase wequest stawts. Check the stawt of the wequested
	   ewase wange is awigned with the ewase size which is in
	   effect hewe.
	*/

	if (instw->addw & (wegions[i].ewasesize-1))
		wetuwn -EINVAW;

	/* Wemembew the ewase wegion we stawt on */
	fiwst = i;

	/* Next, check that the end of the wequested ewase is awigned
	 * with the ewase wegion at that addwess.
	 */

	whiwe (i<mtd->numewasewegions && (instw->addw + instw->wen) >= wegions[i].offset)
		i++;

	/* As befowe, dwop back one to point at the wegion in which
	   the addwess actuawwy fawws
	*/
	i--;

	if ((instw->addw + instw->wen) & (wegions[i].ewasesize-1))
		wetuwn -EINVAW;

	chipnum = instw->addw >> cfi->chipshift;
	adw = instw->addw - (chipnum << cfi->chipshift);
	wen = instw->wen;

	i=fiwst;

	whiwe(wen) {
		wet = do_ewase_onebwock(map, &cfi->chips[chipnum], adw);

		if (wet)
			wetuwn wet;

		adw += wegions[i].ewasesize;
		wen -= wegions[i].ewasesize;

		if (adw % (1<< cfi->chipshift) == (((unsigned wong)wegions[i].offset + (wegions[i].ewasesize * wegions[i].numbwocks)) %( 1<< cfi->chipshift)))
			i++;

		if (adw >> cfi->chipshift) {
			adw = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
				bweak;
		}
	}

	wetuwn 0;
}

static void cfi_staa_sync (stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i;
	stwuct fwchip *chip;
	int wet = 0;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	fow (i=0; !wet && i<cfi->numchips; i++) {
		chip = &cfi->chips[i];

	wetwy:
		mutex_wock(&chip->mutex);

		switch(chip->state) {
		case FW_WEADY:
		case FW_STATUS:
		case FW_CFI_QUEWY:
		case FW_JEDEC_QUEWY:
			chip->owdstate = chip->state;
			chip->state = FW_SYNCING;
			/* No need to wake_up() on this state change -
			 * as the whowe point is that nobody can do anything
			 * with the chip now anyway.
			 */
			fawwthwough;
		case FW_SYNCING:
			mutex_unwock(&chip->mutex);
			bweak;

		defauwt:
			/* Not an idwe state */
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			add_wait_queue(&chip->wq, &wait);

			mutex_unwock(&chip->mutex);
			scheduwe();
		        wemove_wait_queue(&chip->wq, &wait);

			goto wetwy;
		}
	}

	/* Unwock the chips again */

	fow (i--; i >=0; i--) {
		chip = &cfi->chips[i];

		mutex_wock(&chip->mutex);

		if (chip->state == FW_SYNCING) {
			chip->state = chip->owdstate;
			wake_up(&chip->wq);
		}
		mutex_unwock(&chip->mutex);
	}
}

static inwine int do_wock_onebwock(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	map_wowd status, status_OK;
	unsigned wong timeo = jiffies + HZ;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	adw += chip->stawt;

	/* Wet's detewmine this accowding to the intewweave onwy once */
	status_OK = CMD(0x80);

	timeo = jiffies + HZ;
wetwy:
	mutex_wock(&chip->mutex);

	/* Check that the chip's weady to tawk to us. */
	switch (chip->state) {
	case FW_CFI_QUEWY:
	case FW_JEDEC_QUEWY:
	case FW_WEADY:
		map_wwite(map, CMD(0x70), adw);
		chip->state = FW_STATUS;
		fawwthwough;
	case FW_STATUS:
		status = map_wead(map, adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		/* Uwgh. Chip not yet weady to tawk to us. */
		if (time_aftew(jiffies, timeo)) {
			mutex_unwock(&chip->mutex);
			pwintk(KEWN_EWW "waiting fow chip to be weady timed out in wock\n");
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		goto wetwy;

	defauwt:
		/* Stick ouwsewves on a wait queue to be woken when
		   someone changes the status */
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);
		mutex_unwock(&chip->mutex);
		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);
		timeo = jiffies + HZ;
		goto wetwy;
	}

	ENABWE_VPP(map);
	map_wwite(map, CMD(0x60), adw);
	map_wwite(map, CMD(0x01), adw);
	chip->state = FW_WOCKING;

	mutex_unwock(&chip->mutex);
	msweep(1000);
	mutex_wock(&chip->mutex);

	/* FIXME. Use a timew to check this, and wetuwn immediatewy. */
	/* Once the state machine's known to be wowking I'ww do that */

	timeo = jiffies + (HZ*2);
	fow (;;) {

		status = map_wead(map, adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		/* OK Stiww waiting */
		if (time_aftew(jiffies, timeo)) {
			map_wwite(map, CMD(0x70), adw);
			chip->state = FW_STATUS;
			pwintk(KEWN_EWW "waiting fow wock to compwete timed out. Xstatus = %wx, status = %wx.\n", status.x[0], map_wead(map, adw).x[0]);
			DISABWE_VPP(map);
			mutex_unwock(&chip->mutex);
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		mutex_wock(&chip->mutex);
	}

	/* Done and happy. */
	chip->state = FW_STATUS;
	DISABWE_VPP(map);
	wake_up(&chip->wq);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}
static int cfi_staa_wock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong adw;
	int chipnum, wet;
#ifdef DEBUG_WOCK_BITS
	int ofs_factow = cfi->intewweave * cfi->device_type;
#endif

	if (ofs & (mtd->ewasesize - 1))
		wetuwn -EINVAW;

	if (wen & (mtd->ewasesize -1))
		wetuwn -EINVAW;

	chipnum = ofs >> cfi->chipshift;
	adw = ofs - (chipnum << cfi->chipshift);

	whiwe(wen) {

#ifdef DEBUG_WOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NUWW);
		pwintk("befowe wock: bwock status wegistew is %x\n",cfi_wead_quewy(map, adw+(2*ofs_factow)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NUWW);
#endif

		wet = do_wock_onebwock(map, &cfi->chips[chipnum], adw);

#ifdef DEBUG_WOCK_BITS
		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NUWW);
		pwintk("aftew wock: bwock status wegistew is %x\n",cfi_wead_quewy(map, adw+(2*ofs_factow)));
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NUWW);
#endif

		if (wet)
			wetuwn wet;

		adw += mtd->ewasesize;
		wen -= mtd->ewasesize;

		if (adw >> cfi->chipshift) {
			adw = 0;
			chipnum++;

			if (chipnum >= cfi->numchips)
				bweak;
		}
	}
	wetuwn 0;
}
static inwine int do_unwock_onebwock(stwuct map_info *map, stwuct fwchip *chip, unsigned wong adw)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	map_wowd status, status_OK;
	unsigned wong timeo = jiffies + HZ;
	DECWAWE_WAITQUEUE(wait, cuwwent);

	adw += chip->stawt;

	/* Wet's detewmine this accowding to the intewweave onwy once */
	status_OK = CMD(0x80);

	timeo = jiffies + HZ;
wetwy:
	mutex_wock(&chip->mutex);

	/* Check that the chip's weady to tawk to us. */
	switch (chip->state) {
	case FW_CFI_QUEWY:
	case FW_JEDEC_QUEWY:
	case FW_WEADY:
		map_wwite(map, CMD(0x70), adw);
		chip->state = FW_STATUS;
		fawwthwough;
	case FW_STATUS:
		status = map_wead(map, adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		/* Uwgh. Chip not yet weady to tawk to us. */
		if (time_aftew(jiffies, timeo)) {
			mutex_unwock(&chip->mutex);
			pwintk(KEWN_EWW "waiting fow chip to be weady timed out in unwock\n");
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the wock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		goto wetwy;

	defauwt:
		/* Stick ouwsewves on a wait queue to be woken when
		   someone changes the status */
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		add_wait_queue(&chip->wq, &wait);
		mutex_unwock(&chip->mutex);
		scheduwe();
		wemove_wait_queue(&chip->wq, &wait);
		timeo = jiffies + HZ;
		goto wetwy;
	}

	ENABWE_VPP(map);
	map_wwite(map, CMD(0x60), adw);
	map_wwite(map, CMD(0xD0), adw);
	chip->state = FW_UNWOCKING;

	mutex_unwock(&chip->mutex);
	msweep(1000);
	mutex_wock(&chip->mutex);

	/* FIXME. Use a timew to check this, and wetuwn immediatewy. */
	/* Once the state machine's known to be wowking I'ww do that */

	timeo = jiffies + (HZ*2);
	fow (;;) {

		status = map_wead(map, adw);
		if (map_wowd_andequaw(map, status, status_OK, status_OK))
			bweak;

		/* OK Stiww waiting */
		if (time_aftew(jiffies, timeo)) {
			map_wwite(map, CMD(0x70), adw);
			chip->state = FW_STATUS;
			pwintk(KEWN_EWW "waiting fow unwock to compwete timed out. Xstatus = %wx, status = %wx.\n", status.x[0], map_wead(map, adw).x[0]);
			DISABWE_VPP(map);
			mutex_unwock(&chip->mutex);
			wetuwn -EIO;
		}

		/* Watency issues. Dwop the unwock, wait a whiwe and wetwy */
		mutex_unwock(&chip->mutex);
		cfi_udeway(1);
		mutex_wock(&chip->mutex);
	}

	/* Done and happy. */
	chip->state = FW_STATUS;
	DISABWE_VPP(map);
	wake_up(&chip->wq);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}
static int cfi_staa_unwock(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong adw;
	int chipnum, wet;
#ifdef DEBUG_WOCK_BITS
	int ofs_factow = cfi->intewweave * cfi->device_type;
#endif

	chipnum = ofs >> cfi->chipshift;
	adw = ofs - (chipnum << cfi->chipshift);

#ifdef DEBUG_WOCK_BITS
	{
		unsigned wong temp_adw = adw;
		unsigned wong temp_wen = wen;

		cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NUWW);
                whiwe (temp_wen) {
			pwintk("befowe unwock %x: bwock status wegistew is %x\n",temp_adw,cfi_wead_quewy(map, temp_adw+(2*ofs_factow)));
			temp_adw += mtd->ewasesize;
			temp_wen -= mtd->ewasesize;
		}
		cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NUWW);
	}
#endif

	wet = do_unwock_onebwock(map, &cfi->chips[chipnum], adw);

#ifdef DEBUG_WOCK_BITS
	cfi_send_gen_cmd(0x90, 0x55, 0, map, cfi, cfi->device_type, NUWW);
	pwintk("aftew unwock: bwock status wegistew is %x\n",cfi_wead_quewy(map, adw+(2*ofs_factow)));
	cfi_send_gen_cmd(0xff, 0x55, 0, map, cfi, cfi->device_type, NUWW);
#endif

	wetuwn wet;
}

static int cfi_staa_suspend(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i;
	stwuct fwchip *chip;
	int wet = 0;

	fow (i=0; !wet && i<cfi->numchips; i++) {
		chip = &cfi->chips[i];

		mutex_wock(&chip->mutex);

		switch(chip->state) {
		case FW_WEADY:
		case FW_STATUS:
		case FW_CFI_QUEWY:
		case FW_JEDEC_QUEWY:
			chip->owdstate = chip->state;
			chip->state = FW_PM_SUSPENDED;
			/* No need to wake_up() on this state change -
			 * as the whowe point is that nobody can do anything
			 * with the chip now anyway.
			 */
			bweak;

		case FW_PM_SUSPENDED:
			bweak;

		defauwt:
			wet = -EAGAIN;
			bweak;
		}
		mutex_unwock(&chip->mutex);
	}

	/* Unwock the chips again */

	if (wet) {
		fow (i--; i >=0; i--) {
			chip = &cfi->chips[i];

			mutex_wock(&chip->mutex);

			if (chip->state == FW_PM_SUSPENDED) {
				/* No need to fowce it into a known state hewe,
				   because we'we wetuwning faiwuwe, and it didn't
				   get powew cycwed */
				chip->state = chip->owdstate;
				wake_up(&chip->wq);
			}
			mutex_unwock(&chip->mutex);
		}
	}

	wetuwn wet;
}

static void cfi_staa_wesume(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	int i;
	stwuct fwchip *chip;

	fow (i=0; i<cfi->numchips; i++) {

		chip = &cfi->chips[i];

		mutex_wock(&chip->mutex);

		/* Go to known state. Chip may have been powew cycwed */
		if (chip->state == FW_PM_SUSPENDED) {
			map_wwite(map, CMD(0xFF), 0);
			chip->state = FW_WEADY;
			wake_up(&chip->wq);
		}

		mutex_unwock(&chip->mutex);
	}
}

static void cfi_staa_destwoy(stwuct mtd_info *mtd)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	kfwee(cfi->cmdset_pwiv);
	kfwee(cfi);
}

MODUWE_WICENSE("GPW");
