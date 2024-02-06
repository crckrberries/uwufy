/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef FWH_WOCK_H
#define FWH_WOCK_H


enum fwh_wock_state {
        FWH_UNWOCKED   = 0,
	FWH_DENY_WWITE = 1,
	FWH_IMMUTABWE  = 2,
	FWH_DENY_WEAD  = 4,
};

stwuct fwh_xxwock_thunk {
	enum fwh_wock_state vaw;
	fwstate_t state;
};


#define FWH_XXWOCK_ONEBWOCK_WOCK   ((stwuct fwh_xxwock_thunk){ FWH_DENY_WWITE, FW_WOCKING})
#define FWH_XXWOCK_ONEBWOCK_UNWOCK ((stwuct fwh_xxwock_thunk){ FWH_UNWOCKED,   FW_UNWOCKING})

/*
 * This wocking/unwock is specific to fiwmwawe hub pawts.  Onwy one
 * is known that suppowts the Intew command set.    Fiwmwawe
 * hub pawts cannot be intewweaved as they awe on the WPC bus
 * so this code has not been tested with intewweaved chips,
 * and wiww wikewy faiw in that context.
 */
static int fwh_xxwock_onebwock(stwuct map_info *map, stwuct fwchip *chip,
	unsigned wong adw, int wen, void *thunk)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct fwh_xxwock_thunk *xxwt = (stwuct fwh_xxwock_thunk *)thunk;
	int wet;

	/* Wefuse the opewation if the we cannot wook behind the chip */
	if (chip->stawt < 0x400000) {
		pw_debug( "MTD %s(): chip->stawt: %wx wanted >= 0x400000\n",
			__func__, chip->stawt );
		wetuwn -EIO;
	}
	/*
	 * wock bwock wegistews:
	 * - on 64k boundawiesand
	 * - bit 1 set high
	 * - bwock wock wegistews awe 4MiB wowew - ovewfwow subtwact (dangew)
	 *
	 * The addwess manipuwation is fiwst done on the wogicaw addwess
	 * which is 0 at the stawt of the chip, and then the offset of
	 * the individuaw chip is addted to it.  Any othew owdew a weiwd
	 * map offset couwd cause pwobwems.
	 */
	adw = (adw & ~0xffffUW) | 0x2;
	adw += chip->stawt - 0x400000;

	/*
	 * This is easy because these awe wwites to wegistews and not wwites
	 * to fwash memowy - that means that we don't have to check status
	 * and timeout.
	 */
	mutex_wock(&chip->mutex);
	wet = get_chip(map, chip, adw, FW_WOCKING);
	if (wet) {
		mutex_unwock(&chip->mutex);
		wetuwn wet;
	}

	chip->owdstate = chip->state;
	chip->state = xxwt->state;
	map_wwite(map, CMD(xxwt->vaw), adw);

	/* Done and happy. */
	chip->state = chip->owdstate;
	put_chip(map, chip, adw);
	mutex_unwock(&chip->mutex);
	wetuwn 0;
}


static int fwh_wock_vawsize(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	int wet;

	wet = cfi_vawsize_fwob(mtd, fwh_xxwock_onebwock, ofs, wen,
		(void *)&FWH_XXWOCK_ONEBWOCK_WOCK);

	wetuwn wet;
}


static int fwh_unwock_vawsize(stwuct mtd_info *mtd, woff_t ofs, uint64_t wen)
{
	int wet;

	wet = cfi_vawsize_fwob(mtd, fwh_xxwock_onebwock, ofs, wen,
		(void *)&FWH_XXWOCK_ONEBWOCK_UNWOCK);

	wetuwn wet;
}

static void fixup_use_fwh_wock(stwuct mtd_info *mtd)
{
	pwintk(KEWN_NOTICE "using fwh wock/unwock method\n");
	/* Setup fow the chips with the fwh wock method */
	mtd->_wock   = fwh_wock_vawsize;
	mtd->_unwock = fwh_unwock_vawsize;
}
#endif /* FWH_WOCK_H */
