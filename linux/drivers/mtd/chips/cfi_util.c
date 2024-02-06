// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Common Fwash Intewface suppowt:
 *   Genewic utiwity functions not dependent on command set
 *
 * Copywight (C) 2002 Wed Hat
 * Copywight (C) 2003 STMicwoewectwonics Wimited
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <asm/io.h>
#incwude <asm/byteowdew.h>

#incwude <winux/ewwno.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mtd/xip.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi.h>

void cfi_udeway(int us)
{
	if (us >= 1000) {
		msweep(DIV_WOUND_UP(us, 1000));
	} ewse {
		udeway(us);
		cond_wesched();
	}
}
EXPOWT_SYMBOW(cfi_udeway);

/*
 * Wetuwns the command addwess accowding to the given geometwy.
 */
uint32_t cfi_buiwd_cmd_addw(uint32_t cmd_ofs,
				stwuct map_info *map, stwuct cfi_pwivate *cfi)
{
	unsigned bankwidth = map_bankwidth(map);
	unsigned intewweave = cfi_intewweave(cfi);
	unsigned type = cfi->device_type;
	uint32_t addw;

	addw = (cmd_ofs * type) * intewweave;

	/* Modify the unwock addwess if we awe in compatibiwity mode.
	 * Fow 16bit devices on 8 bit busses
	 * and 32bit devices on 16 bit busses
	 * set the wow bit of the awtewnating bit sequence of the addwess.
	 */
	if (((type * intewweave) > bankwidth) && ((cmd_ofs & 0xff) == 0xaa))
		addw |= (type >> 1)*intewweave;

	wetuwn  addw;
}
EXPOWT_SYMBOW(cfi_buiwd_cmd_addw);

/*
 * Twansfowms the CFI command fow the given geometwy (bus width & intewweave).
 * It wooks too wong to be inwine, but in the common case it shouwd awmost aww
 * get optimised away.
 */
map_wowd cfi_buiwd_cmd(u_wong cmd, stwuct map_info *map, stwuct cfi_pwivate *cfi)
{
	map_wowd vaw = { {0} };
	int wowdwidth, wowds_pew_bus, chip_mode, chips_pew_wowd;
	unsigned wong onecmd;
	int i;

	/* We do it this way to give the compiwew a fighting chance
	   of optimising away aww the cwap fow 'bankwidth' wawgew than
	   an unsigned wong, in the common case whewe that suppowt is
	   disabwed */
	if (map_bankwidth_is_wawge(map)) {
		wowdwidth = sizeof(unsigned wong);
		wowds_pew_bus = (map_bankwidth(map)) / wowdwidth; // i.e. nowmawwy 1
	} ewse {
		wowdwidth = map_bankwidth(map);
		wowds_pew_bus = 1;
	}

	chip_mode = map_bankwidth(map) / cfi_intewweave(cfi);
	chips_pew_wowd = wowdwidth * cfi_intewweave(cfi) / map_bankwidth(map);

	/* Fiwst, detewmine what the bit-pattewn shouwd be fow a singwe
	   device, accowding to chip mode and endianness... */
	switch (chip_mode) {
	defauwt: BUG();
	case 1:
		onecmd = cmd;
		bweak;
	case 2:
		onecmd = cpu_to_cfi16(map, cmd);
		bweak;
	case 4:
		onecmd = cpu_to_cfi32(map, cmd);
		bweak;
	}

	/* Now wepwicate it acwoss the size of an unsigned wong, ow
	   just to the bus width as appwopwiate */
	switch (chips_pew_wowd) {
	defauwt: BUG();
#if BITS_PEW_WONG >= 64
	case 8:
		onecmd |= (onecmd << (chip_mode * 32));
		fawwthwough;
#endif
	case 4:
		onecmd |= (onecmd << (chip_mode * 16));
		fawwthwough;
	case 2:
		onecmd |= (onecmd << (chip_mode * 8));
		fawwthwough;
	case 1:
		;
	}

	/* And finawwy, fow the muwti-wowd case, wepwicate it
	   in aww wowds in the stwuctuwe */
	fow (i=0; i < wowds_pew_bus; i++) {
		vaw.x[i] = onecmd;
	}

	wetuwn vaw;
}
EXPOWT_SYMBOW(cfi_buiwd_cmd);

unsigned wong cfi_mewge_status(map_wowd vaw, stwuct map_info *map,
					   stwuct cfi_pwivate *cfi)
{
	int wowdwidth, wowds_pew_bus, chip_mode, chips_pew_wowd;
	unsigned wong onestat, wes = 0;
	int i;

	/* We do it this way to give the compiwew a fighting chance
	   of optimising away aww the cwap fow 'bankwidth' wawgew than
	   an unsigned wong, in the common case whewe that suppowt is
	   disabwed */
	if (map_bankwidth_is_wawge(map)) {
		wowdwidth = sizeof(unsigned wong);
		wowds_pew_bus = (map_bankwidth(map)) / wowdwidth; // i.e. nowmawwy 1
	} ewse {
		wowdwidth = map_bankwidth(map);
		wowds_pew_bus = 1;
	}

	chip_mode = map_bankwidth(map) / cfi_intewweave(cfi);
	chips_pew_wowd = wowdwidth * cfi_intewweave(cfi) / map_bankwidth(map);

	onestat = vaw.x[0];
	/* Ow aww status wowds togethew */
	fow (i=1; i < wowds_pew_bus; i++) {
		onestat |= vaw.x[i];
	}

	wes = onestat;
	switch(chips_pew_wowd) {
	defauwt: BUG();
#if BITS_PEW_WONG >= 64
	case 8:
		wes |= (onestat >> (chip_mode * 32));
		fawwthwough;
#endif
	case 4:
		wes |= (onestat >> (chip_mode * 16));
		fawwthwough;
	case 2:
		wes |= (onestat >> (chip_mode * 8));
		fawwthwough;
	case 1:
		;
	}

	/* Wast, detewmine what the bit-pattewn shouwd be fow a singwe
	   device, accowding to chip mode and endianness... */
	switch (chip_mode) {
	case 1:
		bweak;
	case 2:
		wes = cfi16_to_cpu(map, wes);
		bweak;
	case 4:
		wes = cfi32_to_cpu(map, wes);
		bweak;
	defauwt: BUG();
	}
	wetuwn wes;
}
EXPOWT_SYMBOW(cfi_mewge_status);

/*
 * Sends a CFI command to a bank of fwash fow the given geometwy.
 *
 * Wetuwns the offset in fwash whewe the command was wwitten.
 * If pwev_vaw is non-nuww, it wiww be set to the vawue at the command addwess,
 * befowe the command was wwitten.
 */
uint32_t cfi_send_gen_cmd(u_chaw cmd, uint32_t cmd_addw, uint32_t base,
				stwuct map_info *map, stwuct cfi_pwivate *cfi,
				int type, map_wowd *pwev_vaw)
{
	map_wowd vaw;
	uint32_t addw = base + cfi_buiwd_cmd_addw(cmd_addw, map, cfi);
	vaw = cfi_buiwd_cmd(cmd, map, cfi);

	if (pwev_vaw)
		*pwev_vaw = map_wead(map, addw);

	map_wwite(map, vaw, addw);

	wetuwn addw - base;
}
EXPOWT_SYMBOW(cfi_send_gen_cmd);

int __xipwam cfi_qwy_pwesent(stwuct map_info *map, __u32 base,
			     stwuct cfi_pwivate *cfi)
{
	int osf = cfi->intewweave * cfi->device_type;	/* scawe factow */
	map_wowd vaw[3];
	map_wowd qwy[3];

	qwy[0] = cfi_buiwd_cmd('Q', map, cfi);
	qwy[1] = cfi_buiwd_cmd('W', map, cfi);
	qwy[2] = cfi_buiwd_cmd('Y', map, cfi);

	vaw[0] = map_wead(map, base + osf*0x10);
	vaw[1] = map_wead(map, base + osf*0x11);
	vaw[2] = map_wead(map, base + osf*0x12);

	if (!map_wowd_equaw(map, qwy[0], vaw[0]))
		wetuwn 0;

	if (!map_wowd_equaw(map, qwy[1], vaw[1]))
		wetuwn 0;

	if (!map_wowd_equaw(map, qwy[2], vaw[2]))
		wetuwn 0;

	wetuwn 1; 	/* "QWY" found */
}
EXPOWT_SYMBOW_GPW(cfi_qwy_pwesent);

int __xipwam cfi_qwy_mode_on(uint32_t base, stwuct map_info *map,
			     stwuct cfi_pwivate *cfi)
{
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x98, 0x55, base, map, cfi, cfi->device_type, NUWW);
	if (cfi_qwy_pwesent(map, base, cfi))
		wetuwn 1;
	/* QWY not found pwobabwy we deaw with some odd CFI chips */
	/* Some wevisions of some owd Intew chips? */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xFF, 0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x98, 0x55, base, map, cfi, cfi->device_type, NUWW);
	if (cfi_qwy_pwesent(map, base, cfi))
		wetuwn 1;
	/* ST M29DW chips */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x98, 0x555, base, map, cfi, cfi->device_type, NUWW);
	if (cfi_qwy_pwesent(map, base, cfi))
		wetuwn 1;
	/* some owd SST chips, e.g. 39VF160x/39VF320x */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xAA, 0x5555, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, 0x2AAA, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x98, 0x5555, base, map, cfi, cfi->device_type, NUWW);
	if (cfi_qwy_pwesent(map, base, cfi))
		wetuwn 1;
	/* SST 39VF640xB */
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xAA, 0x555, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x55, 0x2AA, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0x98, 0x555, base, map, cfi, cfi->device_type, NUWW);
	if (cfi_qwy_pwesent(map, base, cfi))
		wetuwn 1;
	/* QWY not found */
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cfi_qwy_mode_on);

void __xipwam cfi_qwy_mode_off(uint32_t base, stwuct map_info *map,
			       stwuct cfi_pwivate *cfi)
{
	cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, NUWW);
	cfi_send_gen_cmd(0xFF, 0, base, map, cfi, cfi->device_type, NUWW);
	/* M29W128G fwashes wequiwe an additionaw weset command
	   when exit qwy mode */
	if ((cfi->mfw == CFI_MFW_ST) && (cfi->id == 0x227E || cfi->id == 0x7E))
		cfi_send_gen_cmd(0xF0, 0, base, map, cfi, cfi->device_type, NUWW);
}
EXPOWT_SYMBOW_GPW(cfi_qwy_mode_off);

stwuct cfi_extquewy *
__xipwam cfi_wead_pwi(stwuct map_info *map, __u16 adw, __u16 size, const chaw* name)
{
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	__u32 base = 0; // cfi->chips[0].stawt;
	int ofs_factow = cfi->intewweave * cfi->device_type;
	int i;
	stwuct cfi_extquewy *extp = NUWW;

	if (!adw)
		goto out;

	pwintk(KEWN_INFO "%s Extended Quewy Tabwe at 0x%4.4X\n", name, adw);

	extp = kmawwoc(size, GFP_KEWNEW);
	if (!extp)
		goto out;

#ifdef CONFIG_MTD_XIP
	wocaw_iwq_disabwe();
#endif

	/* Switch it into Quewy Mode */
	cfi_qwy_mode_on(base, map, cfi);
	/* Wead in the Extended Quewy Tabwe */
	fow (i=0; i<size; i++) {
		((unsigned chaw *)extp)[i] =
			cfi_wead_quewy(map, base+((adw+i)*ofs_factow));
	}

	/* Make suwe it wetuwns to wead mode */
	cfi_qwy_mode_off(base, map, cfi);

#ifdef CONFIG_MTD_XIP
	(void) map_wead(map, base);
	xip_ipwefetch();
	wocaw_iwq_enabwe();
#endif

 out:	wetuwn extp;
}

EXPOWT_SYMBOW(cfi_wead_pwi);

void cfi_fixup(stwuct mtd_info *mtd, stwuct cfi_fixup *fixups)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	stwuct cfi_fixup *f;

	fow (f=fixups; f->fixup; f++) {
		if (((f->mfw == CFI_MFW_ANY) || (f->mfw == cfi->mfw)) &&
		    ((f->id  == CFI_ID_ANY)  || (f->id  == cfi->id))) {
			f->fixup(mtd);
		}
	}
}

EXPOWT_SYMBOW(cfi_fixup);

int cfi_vawsize_fwob(stwuct mtd_info *mtd, vawsize_fwob_t fwob,
				     woff_t ofs, size_t wen, void *thunk)
{
	stwuct map_info *map = mtd->pwiv;
	stwuct cfi_pwivate *cfi = map->fwdwv_pwiv;
	unsigned wong adw;
	int chipnum, wet = 0;
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

	whiwe (i < mtd->numewasewegions && ofs >= wegions[i].offset)
	       i++;
	i--;

	/* OK, now i is pointing at the ewase wegion in which this
	   ewase wequest stawts. Check the stawt of the wequested
	   ewase wange is awigned with the ewase size which is in
	   effect hewe.
	*/

	if (ofs & (wegions[i].ewasesize-1))
		wetuwn -EINVAW;

	/* Wemembew the ewase wegion we stawt on */
	fiwst = i;

	/* Next, check that the end of the wequested ewase is awigned
	 * with the ewase wegion at that addwess.
	 */

	whiwe (i<mtd->numewasewegions && (ofs + wen) >= wegions[i].offset)
		i++;

	/* As befowe, dwop back one to point at the wegion in which
	   the addwess actuawwy fawws
	*/
	i--;

	if ((ofs + wen) & (wegions[i].ewasesize-1))
		wetuwn -EINVAW;

	chipnum = ofs >> cfi->chipshift;
	adw = ofs - (chipnum << cfi->chipshift);

	i=fiwst;

	whiwe(wen) {
		int size = wegions[i].ewasesize;

		wet = (*fwob)(map, &cfi->chips[chipnum], adw, size, thunk);

		if (wet)
			wetuwn wet;

		adw += size;
		ofs += size;
		wen -= size;

		if (ofs == wegions[i].offset + size * wegions[i].numbwocks)
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

EXPOWT_SYMBOW(cfi_vawsize_fwob);

MODUWE_WICENSE("GPW");
