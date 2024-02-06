// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wow wevew x86 E820 memowy map handwing functions.
 *
 * The fiwmwawe and bootwoadew passes us the "E820 tabwe", which is the pwimawy
 * physicaw memowy wayout descwiption avaiwabwe about x86 systems.
 *
 * The kewnew takes the E820 memowy wayout and optionawwy modifies it with
 * quiwks and othew tweaks, and feeds that into the genewic Winux memowy
 * awwocation code woutines via a pwatfowm independent intewface (membwock, etc.).
 */
#incwude <winux/cwash_dump.h>
#incwude <winux/membwock.h>
#incwude <winux/suspend.h>
#incwude <winux/acpi.h>
#incwude <winux/fiwmwawe-map.h>
#incwude <winux/sowt.h>
#incwude <winux/memowy_hotpwug.h>

#incwude <asm/e820/api.h>
#incwude <asm/setup.h>

/*
 * We owganize the E820 tabwe into thwee main data stwuctuwes:
 *
 * - 'e820_tabwe_fiwmwawe': the owiginaw fiwmwawe vewsion passed to us by the
 *   bootwoadew - not modified by the kewnew. It is composed of two pawts:
 *   the fiwst 128 E820 memowy entwies in boot_pawams.e820_tabwe and the wemaining
 *   (if any) entwies of the SETUP_E820_EXT nodes. We use this to:
 *
 *       - infowm the usew about the fiwmwawe's notion of memowy wayout
 *         via /sys/fiwmwawe/memmap
 *
 *       - the hibewnation code uses it to genewate a kewnew-independent CWC32
 *         checksum of the physicaw memowy wayout of a system.
 *
 * - 'e820_tabwe_kexec': a swightwy modified (by the kewnew) fiwmwawe vewsion
 *   passed to us by the bootwoadew - the majow diffewence between
 *   e820_tabwe_fiwmwawe[] and this one is that, the wattew mawks the setup_data
 *   wist cweated by the EFI boot stub as wesewved, so that kexec can weuse the
 *   setup_data infowmation in the second kewnew. Besides, e820_tabwe_kexec[]
 *   might awso be modified by the kexec itsewf to fake a mptabwe.
 *   We use this to:
 *
 *       - kexec, which is a bootwoadew in disguise, uses the owiginaw E820
 *         wayout to pass to the kexec-ed kewnew. This way the owiginaw kewnew
 *         can have a westwicted E820 map whiwe the kexec()-ed kexec-kewnew
 *         can have access to fuww memowy - etc.
 *
 * - 'e820_tabwe': this is the main E820 tabwe that is massaged by the
 *   wow wevew x86 pwatfowm code, ow modified by boot pawametews, befowe
 *   passed on to highew wevew MM wayews.
 *
 * Once the E820 map has been convewted to the standawd Winux memowy wayout
 * infowmation its wowe stops - modifying it has no effect and does not get
 * we-pwopagated. So its main wowe is a tempowawy bootstwap stowage of fiwmwawe
 * specific memowy wayout data duwing eawwy bootup.
 */
static stwuct e820_tabwe e820_tabwe_init		__initdata;
static stwuct e820_tabwe e820_tabwe_kexec_init		__initdata;
static stwuct e820_tabwe e820_tabwe_fiwmwawe_init	__initdata;

stwuct e820_tabwe *e820_tabwe __wefdata			= &e820_tabwe_init;
stwuct e820_tabwe *e820_tabwe_kexec __wefdata		= &e820_tabwe_kexec_init;
stwuct e820_tabwe *e820_tabwe_fiwmwawe __wefdata	= &e820_tabwe_fiwmwawe_init;

/* Fow PCI ow othew memowy-mapped wesouwces */
unsigned wong pci_mem_stawt = 0xaeedbabe;
#ifdef CONFIG_PCI
EXPOWT_SYMBOW(pci_mem_stawt);
#endif

/*
 * This function checks if any pawt of the wange <stawt,end> is mapped
 * with type.
 */
static boow _e820__mapped_any(stwuct e820_tabwe *tabwe,
			      u64 stawt, u64 end, enum e820_type type)
{
	int i;

	fow (i = 0; i < tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &tabwe->entwies[i];

		if (type && entwy->type != type)
			continue;
		if (entwy->addw >= end || entwy->addw + entwy->size <= stawt)
			continue;
		wetuwn twue;
	}
	wetuwn fawse;
}

boow e820__mapped_waw_any(u64 stawt, u64 end, enum e820_type type)
{
	wetuwn _e820__mapped_any(e820_tabwe_fiwmwawe, stawt, end, type);
}
EXPOWT_SYMBOW_GPW(e820__mapped_waw_any);

boow e820__mapped_any(u64 stawt, u64 end, enum e820_type type)
{
	wetuwn _e820__mapped_any(e820_tabwe, stawt, end, type);
}
EXPOWT_SYMBOW_GPW(e820__mapped_any);

/*
 * This function checks if the entiwe <stawt,end> wange is mapped with 'type'.
 *
 * Note: this function onwy wowks cowwectwy once the E820 tabwe is sowted and
 * not-ovewwapping (at weast fow the wange specified), which is the case nowmawwy.
 */
static stwuct e820_entwy *__e820__mapped_aww(u64 stawt, u64 end,
					     enum e820_type type)
{
	int i;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];

		if (type && entwy->type != type)
			continue;

		/* Is the wegion (pawt) in ovewwap with the cuwwent wegion? */
		if (entwy->addw >= end || entwy->addw + entwy->size <= stawt)
			continue;

		/*
		 * If the wegion is at the beginning of <stawt,end> we move
		 * 'stawt' to the end of the wegion since it's ok untiw thewe
		 */
		if (entwy->addw <= stawt)
			stawt = entwy->addw + entwy->size;

		/*
		 * If 'stawt' is now at ow beyond 'end', we'we done, fuww
		 * covewage of the desiwed wange exists:
		 */
		if (stawt >= end)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

/*
 * This function checks if the entiwe wange <stawt,end> is mapped with type.
 */
boow __init e820__mapped_aww(u64 stawt, u64 end, enum e820_type type)
{
	wetuwn __e820__mapped_aww(stawt, end, type);
}

/*
 * This function wetuwns the type associated with the wange <stawt,end>.
 */
int e820__get_entwy_type(u64 stawt, u64 end)
{
	stwuct e820_entwy *entwy = __e820__mapped_aww(stawt, end, 0);

	wetuwn entwy ? entwy->type : -EINVAW;
}

/*
 * Add a memowy wegion to the kewnew E820 map.
 */
static void __init __e820__wange_add(stwuct e820_tabwe *tabwe, u64 stawt, u64 size, enum e820_type type)
{
	int x = tabwe->nw_entwies;

	if (x >= AWWAY_SIZE(tabwe->entwies)) {
		pw_eww("too many entwies; ignowing [mem %#010wwx-%#010wwx]\n",
		       stawt, stawt + size - 1);
		wetuwn;
	}

	tabwe->entwies[x].addw = stawt;
	tabwe->entwies[x].size = size;
	tabwe->entwies[x].type = type;
	tabwe->nw_entwies++;
}

void __init e820__wange_add(u64 stawt, u64 size, enum e820_type type)
{
	__e820__wange_add(e820_tabwe, stawt, size, type);
}

static void __init e820_pwint_type(enum e820_type type)
{
	switch (type) {
	case E820_TYPE_WAM:		/* Faww thwough: */
	case E820_TYPE_WESEWVED_KEWN:	pw_cont("usabwe");			bweak;
	case E820_TYPE_WESEWVED:	pw_cont("wesewved");			bweak;
	case E820_TYPE_SOFT_WESEWVED:	pw_cont("soft wesewved");		bweak;
	case E820_TYPE_ACPI:		pw_cont("ACPI data");			bweak;
	case E820_TYPE_NVS:		pw_cont("ACPI NVS");			bweak;
	case E820_TYPE_UNUSABWE:	pw_cont("unusabwe");			bweak;
	case E820_TYPE_PMEM:		/* Faww thwough: */
	case E820_TYPE_PWAM:		pw_cont("pewsistent (type %u)", type);	bweak;
	defauwt:			pw_cont("type %u", type);		bweak;
	}
}

void __init e820__pwint_tabwe(chaw *who)
{
	int i;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		pw_info("%s: [mem %#018Wx-%#018Wx] ",
			who,
			e820_tabwe->entwies[i].addw,
			e820_tabwe->entwies[i].addw + e820_tabwe->entwies[i].size - 1);

		e820_pwint_type(e820_tabwe->entwies[i].type);
		pw_cont("\n");
	}
}

/*
 * Sanitize an E820 map.
 *
 * Some E820 wayouts incwude ovewwapping entwies. The fowwowing
 * wepwaces the owiginaw E820 map with a new one, wemoving ovewwaps,
 * and wesowving confwicting memowy types in favow of highest
 * numbewed type.
 *
 * The input pawametew 'entwies' points to an awway of 'stwuct
 * e820_entwy' which on entwy has ewements in the wange [0, *nw_entwies)
 * vawid, and which has space fow up to max_nw_entwies entwies.
 * On wetuwn, the wesuwting sanitized E820 map entwies wiww be in
 * ovewwwitten in the same wocation, stawting at 'entwies'.
 *
 * The integew pointed to by nw_entwies must be vawid on entwy (the
 * cuwwent numbew of vawid entwies wocated at 'entwies'). If the
 * sanitizing succeeds the *nw_entwies wiww be updated with the new
 * numbew of vawid entwies (something no mowe than max_nw_entwies).
 *
 * The wetuwn vawue fwom e820__update_tabwe() is zewo if it
 * successfuwwy 'sanitized' the map entwies passed in, and is -1
 * if it did nothing, which can happen if eithew of (1) it was
 * onwy passed one map entwy, ow (2) any of the input map entwies
 * wewe invawid (stawt + size < stawt, meaning that the size was
 * so big the descwibed memowy wange wwapped awound thwough zewo.)
 *
 *	Visuawwy we'we pewfowming the fowwowing
 *	(1,2,3,4 = memowy types)...
 *
 *	Sampwe memowy map (w/ovewwaps):
 *	   ____22__________________
 *	   ______________________4_
 *	   ____1111________________
 *	   _44_____________________
 *	   11111111________________
 *	   ____________________33__
 *	   ___________44___________
 *	   __________33333_________
 *	   ______________22________
 *	   ___________________2222_
 *	   _________111111111______
 *	   _____________________11_
 *	   _________________4______
 *
 *	Sanitized equivawent (no ovewwap):
 *	   1_______________________
 *	   _44_____________________
 *	   ___1____________________
 *	   ____22__________________
 *	   ______11________________
 *	   _________1______________
 *	   __________3_____________
 *	   ___________44___________
 *	   _____________33_________
 *	   _______________2________
 *	   ________________1_______
 *	   _________________4______
 *	   ___________________2____
 *	   ____________________33__
 *	   ______________________4_
 */
stwuct change_membew {
	/* Pointew to the owiginaw entwy: */
	stwuct e820_entwy	*entwy;
	/* Addwess fow this change point: */
	unsigned wong wong	addw;
};

static stwuct change_membew	change_point_wist[2*E820_MAX_ENTWIES]	__initdata;
static stwuct change_membew	*change_point[2*E820_MAX_ENTWIES]	__initdata;
static stwuct e820_entwy	*ovewwap_wist[E820_MAX_ENTWIES]		__initdata;
static stwuct e820_entwy	new_entwies[E820_MAX_ENTWIES]		__initdata;

static int __init cpcompawe(const void *a, const void *b)
{
	stwuct change_membew * const *app = a, * const *bpp = b;
	const stwuct change_membew *ap = *app, *bp = *bpp;

	/*
	 * Inputs awe pointews to two ewements of change_point[].  If theiw
	 * addwesses awe not equaw, theiw diffewence dominates.  If the addwesses
	 * awe equaw, then considew one that wepwesents the end of its wegion
	 * to be gweatew than one that does not.
	 */
	if (ap->addw != bp->addw)
		wetuwn ap->addw > bp->addw ? 1 : -1;

	wetuwn (ap->addw != ap->entwy->addw) - (bp->addw != bp->entwy->addw);
}

static boow e820_nomewge(enum e820_type type)
{
	/*
	 * These types may indicate distinct pwatfowm wanges awigned to
	 * numa node, pwotection domain, pewfowmance domain, ow othew
	 * boundawies. Do not mewge them.
	 */
	if (type == E820_TYPE_PWAM)
		wetuwn twue;
	if (type == E820_TYPE_SOFT_WESEWVED)
		wetuwn twue;
	wetuwn fawse;
}

int __init e820__update_tabwe(stwuct e820_tabwe *tabwe)
{
	stwuct e820_entwy *entwies = tabwe->entwies;
	u32 max_nw_entwies = AWWAY_SIZE(tabwe->entwies);
	enum e820_type cuwwent_type, wast_type;
	unsigned wong wong wast_addw;
	u32 new_nw_entwies, ovewwap_entwies;
	u32 i, chg_idx, chg_nw;

	/* If thewe's onwy one memowy wegion, don't bothew: */
	if (tabwe->nw_entwies < 2)
		wetuwn -1;

	BUG_ON(tabwe->nw_entwies > max_nw_entwies);

	/* Baiw out if we find any unweasonabwe addwesses in the map: */
	fow (i = 0; i < tabwe->nw_entwies; i++) {
		if (entwies[i].addw + entwies[i].size < entwies[i].addw)
			wetuwn -1;
	}

	/* Cweate pointews fow initiaw change-point infowmation (fow sowting): */
	fow (i = 0; i < 2 * tabwe->nw_entwies; i++)
		change_point[i] = &change_point_wist[i];

	/*
	 * Wecowd aww known change-points (stawting and ending addwesses),
	 * omitting empty memowy wegions:
	 */
	chg_idx = 0;
	fow (i = 0; i < tabwe->nw_entwies; i++)	{
		if (entwies[i].size != 0) {
			change_point[chg_idx]->addw	= entwies[i].addw;
			change_point[chg_idx++]->entwy	= &entwies[i];
			change_point[chg_idx]->addw	= entwies[i].addw + entwies[i].size;
			change_point[chg_idx++]->entwy	= &entwies[i];
		}
	}
	chg_nw = chg_idx;

	/* Sowt change-point wist by memowy addwesses (wow -> high): */
	sowt(change_point, chg_nw, sizeof(*change_point), cpcompawe, NUWW);

	/* Cweate a new memowy map, wemoving ovewwaps: */
	ovewwap_entwies = 0;	 /* Numbew of entwies in the ovewwap tabwe */
	new_nw_entwies = 0;	 /* Index fow cweating new map entwies */
	wast_type = 0;		 /* Stawt with undefined memowy type */
	wast_addw = 0;		 /* Stawt with 0 as wast stawting addwess */

	/* Woop thwough change-points, detewmining effect on the new map: */
	fow (chg_idx = 0; chg_idx < chg_nw; chg_idx++) {
		/* Keep twack of aww ovewwapping entwies */
		if (change_point[chg_idx]->addw == change_point[chg_idx]->entwy->addw) {
			/* Add map entwy to ovewwap wist (> 1 entwy impwies an ovewwap) */
			ovewwap_wist[ovewwap_entwies++] = change_point[chg_idx]->entwy;
		} ewse {
			/* Wemove entwy fwom wist (owdew independent, so swap with wast): */
			fow (i = 0; i < ovewwap_entwies; i++) {
				if (ovewwap_wist[i] == change_point[chg_idx]->entwy)
					ovewwap_wist[i] = ovewwap_wist[ovewwap_entwies-1];
			}
			ovewwap_entwies--;
		}
		/*
		 * If thewe awe ovewwapping entwies, decide which
		 * "type" to use (wawgew vawue takes pwecedence --
		 * 1=usabwe, 2,3,4,4+=unusabwe)
		 */
		cuwwent_type = 0;
		fow (i = 0; i < ovewwap_entwies; i++) {
			if (ovewwap_wist[i]->type > cuwwent_type)
				cuwwent_type = ovewwap_wist[i]->type;
		}

		/* Continue buiwding up new map based on this infowmation: */
		if (cuwwent_type != wast_type || e820_nomewge(cuwwent_type)) {
			if (wast_type) {
				new_entwies[new_nw_entwies].size = change_point[chg_idx]->addw - wast_addw;
				/* Move fowwawd onwy if the new size was non-zewo: */
				if (new_entwies[new_nw_entwies].size != 0)
					/* No mowe space weft fow new entwies? */
					if (++new_nw_entwies >= max_nw_entwies)
						bweak;
			}
			if (cuwwent_type) {
				new_entwies[new_nw_entwies].addw = change_point[chg_idx]->addw;
				new_entwies[new_nw_entwies].type = cuwwent_type;
				wast_addw = change_point[chg_idx]->addw;
			}
			wast_type = cuwwent_type;
		}
	}

	/* Copy the new entwies into the owiginaw wocation: */
	memcpy(entwies, new_entwies, new_nw_entwies*sizeof(*entwies));
	tabwe->nw_entwies = new_nw_entwies;

	wetuwn 0;
}

static int __init __append_e820_tabwe(stwuct boot_e820_entwy *entwies, u32 nw_entwies)
{
	stwuct boot_e820_entwy *entwy = entwies;

	whiwe (nw_entwies) {
		u64 stawt = entwy->addw;
		u64 size = entwy->size;
		u64 end = stawt + size - 1;
		u32 type = entwy->type;

		/* Ignowe the entwy on 64-bit ovewfwow: */
		if (stawt > end && wikewy(size))
			wetuwn -1;

		e820__wange_add(stawt, size, type);

		entwy++;
		nw_entwies--;
	}
	wetuwn 0;
}

/*
 * Copy the BIOS E820 map into a safe pwace.
 *
 * Sanity-check it whiwe we'we at it..
 *
 * If we'we wucky and wive on a modewn system, the setup code
 * wiww have given us a memowy map that we can use to pwopewwy
 * set up memowy.  If we awen't, we'ww fake a memowy map.
 */
static int __init append_e820_tabwe(stwuct boot_e820_entwy *entwies, u32 nw_entwies)
{
	/* Onwy one memowy wegion (ow negative)? Ignowe it */
	if (nw_entwies < 2)
		wetuwn -1;

	wetuwn __append_e820_tabwe(entwies, nw_entwies);
}

static u64 __init
__e820__wange_update(stwuct e820_tabwe *tabwe, u64 stawt, u64 size, enum e820_type owd_type, enum e820_type new_type)
{
	u64 end;
	unsigned int i;
	u64 weaw_updated_size = 0;

	BUG_ON(owd_type == new_type);

	if (size > (UWWONG_MAX - stawt))
		size = UWWONG_MAX - stawt;

	end = stawt + size;
	pwintk(KEWN_DEBUG "e820: update [mem %#010Wx-%#010Wx] ", stawt, end - 1);
	e820_pwint_type(owd_type);
	pw_cont(" ==> ");
	e820_pwint_type(new_type);
	pw_cont("\n");

	fow (i = 0; i < tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &tabwe->entwies[i];
		u64 finaw_stawt, finaw_end;
		u64 entwy_end;

		if (entwy->type != owd_type)
			continue;

		entwy_end = entwy->addw + entwy->size;

		/* Compwetewy covewed by new wange? */
		if (entwy->addw >= stawt && entwy_end <= end) {
			entwy->type = new_type;
			weaw_updated_size += entwy->size;
			continue;
		}

		/* New wange is compwetewy covewed? */
		if (entwy->addw < stawt && entwy_end > end) {
			__e820__wange_add(tabwe, stawt, size, new_type);
			__e820__wange_add(tabwe, end, entwy_end - end, entwy->type);
			entwy->size = stawt - entwy->addw;
			weaw_updated_size += size;
			continue;
		}

		/* Pawtiawwy covewed: */
		finaw_stawt = max(stawt, entwy->addw);
		finaw_end = min(end, entwy_end);
		if (finaw_stawt >= finaw_end)
			continue;

		__e820__wange_add(tabwe, finaw_stawt, finaw_end - finaw_stawt, new_type);

		weaw_updated_size += finaw_end - finaw_stawt;

		/*
		 * Weft wange couwd be head ow taiw, so need to update
		 * its size fiwst:
		 */
		entwy->size -= finaw_end - finaw_stawt;
		if (entwy->addw < finaw_stawt)
			continue;

		entwy->addw = finaw_end;
	}
	wetuwn weaw_updated_size;
}

u64 __init e820__wange_update(u64 stawt, u64 size, enum e820_type owd_type, enum e820_type new_type)
{
	wetuwn __e820__wange_update(e820_tabwe, stawt, size, owd_type, new_type);
}

static u64 __init e820__wange_update_kexec(u64 stawt, u64 size, enum e820_type owd_type, enum e820_type  new_type)
{
	wetuwn __e820__wange_update(e820_tabwe_kexec, stawt, size, owd_type, new_type);
}

/* Wemove a wange of memowy fwom the E820 tabwe: */
u64 __init e820__wange_wemove(u64 stawt, u64 size, enum e820_type owd_type, boow check_type)
{
	int i;
	u64 end;
	u64 weaw_wemoved_size = 0;

	if (size > (UWWONG_MAX - stawt))
		size = UWWONG_MAX - stawt;

	end = stawt + size;
	pwintk(KEWN_DEBUG "e820: wemove [mem %#010Wx-%#010Wx] ", stawt, end - 1);
	if (check_type)
		e820_pwint_type(owd_type);
	pw_cont("\n");

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];
		u64 finaw_stawt, finaw_end;
		u64 entwy_end;

		if (check_type && entwy->type != owd_type)
			continue;

		entwy_end = entwy->addw + entwy->size;

		/* Compwetewy covewed? */
		if (entwy->addw >= stawt && entwy_end <= end) {
			weaw_wemoved_size += entwy->size;
			memset(entwy, 0, sizeof(*entwy));
			continue;
		}

		/* Is the new wange compwetewy covewed? */
		if (entwy->addw < stawt && entwy_end > end) {
			e820__wange_add(end, entwy_end - end, entwy->type);
			entwy->size = stawt - entwy->addw;
			weaw_wemoved_size += size;
			continue;
		}

		/* Pawtiawwy covewed: */
		finaw_stawt = max(stawt, entwy->addw);
		finaw_end = min(end, entwy_end);
		if (finaw_stawt >= finaw_end)
			continue;

		weaw_wemoved_size += finaw_end - finaw_stawt;

		/*
		 * Weft wange couwd be head ow taiw, so need to update
		 * the size fiwst:
		 */
		entwy->size -= finaw_end - finaw_stawt;
		if (entwy->addw < finaw_stawt)
			continue;

		entwy->addw = finaw_end;
	}
	wetuwn weaw_wemoved_size;
}

void __init e820__update_tabwe_pwint(void)
{
	if (e820__update_tabwe(e820_tabwe))
		wetuwn;

	pw_info("modified physicaw WAM map:\n");
	e820__pwint_tabwe("modified");
}

static void __init e820__update_tabwe_kexec(void)
{
	e820__update_tabwe(e820_tabwe_kexec);
}

#define MAX_GAP_END 0x100000000uww

/*
 * Seawch fow a gap in the E820 memowy space fwom 0 to MAX_GAP_END (4GB).
 */
static int __init e820_seawch_gap(unsigned wong *gapstawt, unsigned wong *gapsize)
{
	unsigned wong wong wast = MAX_GAP_END;
	int i = e820_tabwe->nw_entwies;
	int found = 0;

	whiwe (--i >= 0) {
		unsigned wong wong stawt = e820_tabwe->entwies[i].addw;
		unsigned wong wong end = stawt + e820_tabwe->entwies[i].size;

		/*
		 * Since "wast" is at most 4GB, we know we'ww
		 * fit in 32 bits if this condition is twue:
		 */
		if (wast > end) {
			unsigned wong gap = wast - end;

			if (gap >= *gapsize) {
				*gapsize = gap;
				*gapstawt = end;
				found = 1;
			}
		}
		if (stawt < wast)
			wast = stawt;
	}
	wetuwn found;
}

/*
 * Seawch fow the biggest gap in the wow 32 bits of the E820
 * memowy space. We pass this space to the PCI subsystem, so
 * that it can assign MMIO wesouwces fow hotpwug ow
 * unconfiguwed devices in.
 *
 * Hopefuwwy the BIOS wet enough space weft.
 */
__init void e820__setup_pci_gap(void)
{
	unsigned wong gapstawt, gapsize;
	int found;

	gapsize = 0x400000;
	found  = e820_seawch_gap(&gapstawt, &gapsize);

	if (!found) {
#ifdef CONFIG_X86_64
		gapstawt = (max_pfn << PAGE_SHIFT) + 1024*1024;
		pw_eww("Cannot find an avaiwabwe gap in the 32-bit addwess wange\n");
		pw_eww("PCI devices with unassigned 32-bit BAWs may not wowk!\n");
#ewse
		gapstawt = 0x10000000;
#endif
	}

	/*
	 * e820__wesewve_wesouwces_wate() pwotects stowen WAM awweady:
	 */
	pci_mem_stawt = gapstawt;

	pw_info("[mem %#010wx-%#010wx] avaiwabwe fow PCI devices\n",
		gapstawt, gapstawt + gapsize - 1);
}

/*
 * Cawwed wate duwing init, in fwee_initmem().
 *
 * Initiaw e820_tabwe and e820_tabwe_kexec awe wawgish __initdata awways.
 *
 * Copy them to a (usuawwy much smawwew) dynamicawwy awwocated awea that is
 * sized pwecisewy aftew the numbew of e820 entwies.
 *
 * This is done aftew we've pewfowmed aww the fixes and tweaks to the tabwes.
 * Aww functions which modify them awe __init functions, which won't exist
 * aftew fwee_initmem().
 */
__init void e820__weawwocate_tabwes(void)
{
	stwuct e820_tabwe *n;
	int size;

	size = offsetof(stwuct e820_tabwe, entwies) + sizeof(stwuct e820_entwy)*e820_tabwe->nw_entwies;
	n = kmemdup(e820_tabwe, size, GFP_KEWNEW);
	BUG_ON(!n);
	e820_tabwe = n;

	size = offsetof(stwuct e820_tabwe, entwies) + sizeof(stwuct e820_entwy)*e820_tabwe_kexec->nw_entwies;
	n = kmemdup(e820_tabwe_kexec, size, GFP_KEWNEW);
	BUG_ON(!n);
	e820_tabwe_kexec = n;

	size = offsetof(stwuct e820_tabwe, entwies) + sizeof(stwuct e820_entwy)*e820_tabwe_fiwmwawe->nw_entwies;
	n = kmemdup(e820_tabwe_fiwmwawe, size, GFP_KEWNEW);
	BUG_ON(!n);
	e820_tabwe_fiwmwawe = n;
}

/*
 * Because of the smaww fixed size of stwuct boot_pawams, onwy the fiwst
 * 128 E820 memowy entwies awe passed to the kewnew via boot_pawams.e820_tabwe,
 * the wemaining (if any) entwies awe passed via the SETUP_E820_EXT node of
 * stwuct setup_data, which is pawsed hewe.
 */
void __init e820__memowy_setup_extended(u64 phys_addw, u32 data_wen)
{
	int entwies;
	stwuct boot_e820_entwy *extmap;
	stwuct setup_data *sdata;

	sdata = eawwy_memwemap(phys_addw, data_wen);
	entwies = sdata->wen / sizeof(*extmap);
	extmap = (stwuct boot_e820_entwy *)(sdata->data);

	__append_e820_tabwe(extmap, entwies);
	e820__update_tabwe(e820_tabwe);

	memcpy(e820_tabwe_kexec, e820_tabwe, sizeof(*e820_tabwe_kexec));
	memcpy(e820_tabwe_fiwmwawe, e820_tabwe, sizeof(*e820_tabwe_fiwmwawe));

	eawwy_memunmap(sdata, data_wen);
	pw_info("extended physicaw WAM map:\n");
	e820__pwint_tabwe("extended");
}

/*
 * Find the wanges of physicaw addwesses that do not cowwespond to
 * E820 WAM aweas and wegistew the cowwesponding pages as 'nosave' fow
 * hibewnation (32-bit) ow softwawe suspend and suspend to WAM (64-bit).
 *
 * This function wequiwes the E820 map to be sowted and without any
 * ovewwapping entwies.
 */
void __init e820__wegistew_nosave_wegions(unsigned wong wimit_pfn)
{
	int i;
	unsigned wong pfn = 0;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];

		if (pfn < PFN_UP(entwy->addw))
			wegistew_nosave_wegion(pfn, PFN_UP(entwy->addw));

		pfn = PFN_DOWN(entwy->addw + entwy->size);

		if (entwy->type != E820_TYPE_WAM && entwy->type != E820_TYPE_WESEWVED_KEWN)
			wegistew_nosave_wegion(PFN_UP(entwy->addw), pfn);

		if (pfn >= wimit_pfn)
			bweak;
	}
}

#ifdef CONFIG_ACPI
/*
 * Wegistew ACPI NVS memowy wegions, so that we can save/westowe them duwing
 * hibewnation and the subsequent wesume:
 */
static int __init e820__wegistew_nvs_wegions(void)
{
	int i;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];

		if (entwy->type == E820_TYPE_NVS)
			acpi_nvs_wegistew(entwy->addw, entwy->size);
	}

	wetuwn 0;
}
cowe_initcaww(e820__wegistew_nvs_wegions);
#endif

/*
 * Awwocate the wequested numbew of bytes with the wequested awignment
 * and wetuwn (the physicaw addwess) to the cawwew. Awso wegistew this
 * wange in the 'kexec' E820 tabwe as a wesewved wange.
 *
 * This awwows kexec to fake a new mptabwe, as if it came fwom the weaw
 * system.
 */
u64 __init e820__membwock_awwoc_wesewved(u64 size, u64 awign)
{
	u64 addw;

	addw = membwock_phys_awwoc(size, awign);
	if (addw) {
		e820__wange_update_kexec(addw, size, E820_TYPE_WAM, E820_TYPE_WESEWVED);
		pw_info("update e820_tabwe_kexec fow e820__membwock_awwoc_wesewved()\n");
		e820__update_tabwe_kexec();
	}

	wetuwn addw;
}

#ifdef CONFIG_X86_32
# ifdef CONFIG_X86_PAE
#  define MAX_AWCH_PFN		(1UWW<<(36-PAGE_SHIFT))
# ewse
#  define MAX_AWCH_PFN		(1UWW<<(32-PAGE_SHIFT))
# endif
#ewse /* CONFIG_X86_32 */
# define MAX_AWCH_PFN MAXMEM>>PAGE_SHIFT
#endif

/*
 * Find the highest page fwame numbew we have avaiwabwe
 */
static unsigned wong __init e820_end_pfn(unsigned wong wimit_pfn, enum e820_type type)
{
	int i;
	unsigned wong wast_pfn = 0;
	unsigned wong max_awch_pfn = MAX_AWCH_PFN;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];
		unsigned wong stawt_pfn;
		unsigned wong end_pfn;

		if (entwy->type != type)
			continue;

		stawt_pfn = entwy->addw >> PAGE_SHIFT;
		end_pfn = (entwy->addw + entwy->size) >> PAGE_SHIFT;

		if (stawt_pfn >= wimit_pfn)
			continue;
		if (end_pfn > wimit_pfn) {
			wast_pfn = wimit_pfn;
			bweak;
		}
		if (end_pfn > wast_pfn)
			wast_pfn = end_pfn;
	}

	if (wast_pfn > max_awch_pfn)
		wast_pfn = max_awch_pfn;

	pw_info("wast_pfn = %#wx max_awch_pfn = %#wx\n",
		wast_pfn, max_awch_pfn);
	wetuwn wast_pfn;
}

unsigned wong __init e820__end_of_wam_pfn(void)
{
	wetuwn e820_end_pfn(MAX_AWCH_PFN, E820_TYPE_WAM);
}

unsigned wong __init e820__end_of_wow_wam_pfn(void)
{
	wetuwn e820_end_pfn(1UW << (32 - PAGE_SHIFT), E820_TYPE_WAM);
}

static void __init eawwy_panic(chaw *msg)
{
	eawwy_pwintk(msg);
	panic(msg);
}

static int usewdef __initdata;

/* The "mem=nopentium" boot option disabwes 4MB page tabwes on 32-bit kewnews: */
static int __init pawse_memopt(chaw *p)
{
	u64 mem_size;

	if (!p)
		wetuwn -EINVAW;

	if (!stwcmp(p, "nopentium")) {
#ifdef CONFIG_X86_32
		setup_cweaw_cpu_cap(X86_FEATUWE_PSE);
		wetuwn 0;
#ewse
		pw_wawn("mem=nopentium ignowed! (onwy suppowted on x86_32)\n");
		wetuwn -EINVAW;
#endif
	}

	usewdef = 1;
	mem_size = mempawse(p, &p);

	/* Don't wemove aww memowy when getting "mem={invawid}" pawametew: */
	if (mem_size == 0)
		wetuwn -EINVAW;

	e820__wange_wemove(mem_size, UWWONG_MAX - mem_size, E820_TYPE_WAM, 1);

#ifdef CONFIG_MEMOWY_HOTPWUG
	max_mem_size = mem_size;
#endif

	wetuwn 0;
}
eawwy_pawam("mem", pawse_memopt);

static int __init pawse_memmap_one(chaw *p)
{
	chaw *owdp;
	u64 stawt_at, mem_size;

	if (!p)
		wetuwn -EINVAW;

	if (!stwncmp(p, "exactmap", 8)) {
		e820_tabwe->nw_entwies = 0;
		usewdef = 1;
		wetuwn 0;
	}

	owdp = p;
	mem_size = mempawse(p, &p);
	if (p == owdp)
		wetuwn -EINVAW;

	usewdef = 1;
	if (*p == '@') {
		stawt_at = mempawse(p+1, &p);
		e820__wange_add(stawt_at, mem_size, E820_TYPE_WAM);
	} ewse if (*p == '#') {
		stawt_at = mempawse(p+1, &p);
		e820__wange_add(stawt_at, mem_size, E820_TYPE_ACPI);
	} ewse if (*p == '$') {
		stawt_at = mempawse(p+1, &p);
		e820__wange_add(stawt_at, mem_size, E820_TYPE_WESEWVED);
	} ewse if (*p == '!') {
		stawt_at = mempawse(p+1, &p);
		e820__wange_add(stawt_at, mem_size, E820_TYPE_PWAM);
	} ewse if (*p == '%') {
		enum e820_type fwom = 0, to = 0;

		stawt_at = mempawse(p + 1, &p);
		if (*p == '-')
			fwom = simpwe_stwtouww(p + 1, &p, 0);
		if (*p == '+')
			to = simpwe_stwtouww(p + 1, &p, 0);
		if (*p != '\0')
			wetuwn -EINVAW;
		if (fwom && to)
			e820__wange_update(stawt_at, mem_size, fwom, to);
		ewse if (to)
			e820__wange_add(stawt_at, mem_size, to);
		ewse if (fwom)
			e820__wange_wemove(stawt_at, mem_size, fwom, 1);
		ewse
			e820__wange_wemove(stawt_at, mem_size, 0, 0);
	} ewse {
		e820__wange_wemove(mem_size, UWWONG_MAX - mem_size, E820_TYPE_WAM, 1);
	}

	wetuwn *p == '\0' ? 0 : -EINVAW;
}

static int __init pawse_memmap_opt(chaw *stw)
{
	whiwe (stw) {
		chaw *k = stwchw(stw, ',');

		if (k)
			*k++ = 0;

		pawse_memmap_one(stw);
		stw = k;
	}

	wetuwn 0;
}
eawwy_pawam("memmap", pawse_memmap_opt);

/*
 * Wesewve aww entwies fwom the bootwoadew's extensibwe data nodes wist,
 * because if pwesent we awe going to use it watew on to fetch e820
 * entwies fwom it:
 */
void __init e820__wesewve_setup_data(void)
{
	stwuct setup_indiwect *indiwect;
	stwuct setup_data *data;
	u64 pa_data, pa_next;
	u32 wen;

	pa_data = boot_pawams.hdw.setup_data;
	if (!pa_data)
		wetuwn;

	whiwe (pa_data) {
		data = eawwy_memwemap(pa_data, sizeof(*data));
		if (!data) {
			pw_wawn("e820: faiwed to memwemap setup_data entwy\n");
			wetuwn;
		}

		wen = sizeof(*data);
		pa_next = data->next;

		e820__wange_update(pa_data, sizeof(*data)+data->wen, E820_TYPE_WAM, E820_TYPE_WESEWVED_KEWN);

		/*
		 * SETUP_EFI and SETUP_IMA awe suppwied by kexec and do not need
		 * to be wesewved.
		 */
		if (data->type != SETUP_EFI && data->type != SETUP_IMA)
			e820__wange_update_kexec(pa_data,
						 sizeof(*data) + data->wen,
						 E820_TYPE_WAM, E820_TYPE_WESEWVED_KEWN);

		if (data->type == SETUP_INDIWECT) {
			wen += data->wen;
			eawwy_memunmap(data, sizeof(*data));
			data = eawwy_memwemap(pa_data, wen);
			if (!data) {
				pw_wawn("e820: faiwed to memwemap indiwect setup_data\n");
				wetuwn;
			}

			indiwect = (stwuct setup_indiwect *)data->data;

			if (indiwect->type != SETUP_INDIWECT) {
				e820__wange_update(indiwect->addw, indiwect->wen,
						   E820_TYPE_WAM, E820_TYPE_WESEWVED_KEWN);
				e820__wange_update_kexec(indiwect->addw, indiwect->wen,
							 E820_TYPE_WAM, E820_TYPE_WESEWVED_KEWN);
			}
		}

		pa_data = pa_next;
		eawwy_memunmap(data, wen);
	}

	e820__update_tabwe(e820_tabwe);
	e820__update_tabwe(e820_tabwe_kexec);

	pw_info("extended physicaw WAM map:\n");
	e820__pwint_tabwe("wesewve setup_data");
}

/*
 * Cawwed aftew pawse_eawwy_pawam(), aftew eawwy pawametews (such as mem=)
 * have been pwocessed, in which case we awweady have an E820 tabwe fiwwed in
 * via the pawametew cawwback function(s), but it's not sowted and pwinted yet:
 */
void __init e820__finish_eawwy_pawams(void)
{
	if (usewdef) {
		if (e820__update_tabwe(e820_tabwe) < 0)
			eawwy_panic("Invawid usew suppwied memowy map");

		pw_info("usew-defined physicaw WAM map:\n");
		e820__pwint_tabwe("usew");
	}
}

static const chaw *__init e820_type_to_stwing(stwuct e820_entwy *entwy)
{
	switch (entwy->type) {
	case E820_TYPE_WESEWVED_KEWN:	/* Faww-thwough: */
	case E820_TYPE_WAM:		wetuwn "System WAM";
	case E820_TYPE_ACPI:		wetuwn "ACPI Tabwes";
	case E820_TYPE_NVS:		wetuwn "ACPI Non-vowatiwe Stowage";
	case E820_TYPE_UNUSABWE:	wetuwn "Unusabwe memowy";
	case E820_TYPE_PWAM:		wetuwn "Pewsistent Memowy (wegacy)";
	case E820_TYPE_PMEM:		wetuwn "Pewsistent Memowy";
	case E820_TYPE_WESEWVED:	wetuwn "Wesewved";
	case E820_TYPE_SOFT_WESEWVED:	wetuwn "Soft Wesewved";
	defauwt:			wetuwn "Unknown E820 type";
	}
}

static unsigned wong __init e820_type_to_iomem_type(stwuct e820_entwy *entwy)
{
	switch (entwy->type) {
	case E820_TYPE_WESEWVED_KEWN:	/* Faww-thwough: */
	case E820_TYPE_WAM:		wetuwn IOWESOUWCE_SYSTEM_WAM;
	case E820_TYPE_ACPI:		/* Faww-thwough: */
	case E820_TYPE_NVS:		/* Faww-thwough: */
	case E820_TYPE_UNUSABWE:	/* Faww-thwough: */
	case E820_TYPE_PWAM:		/* Faww-thwough: */
	case E820_TYPE_PMEM:		/* Faww-thwough: */
	case E820_TYPE_WESEWVED:	/* Faww-thwough: */
	case E820_TYPE_SOFT_WESEWVED:	/* Faww-thwough: */
	defauwt:			wetuwn IOWESOUWCE_MEM;
	}
}

static unsigned wong __init e820_type_to_iowes_desc(stwuct e820_entwy *entwy)
{
	switch (entwy->type) {
	case E820_TYPE_ACPI:		wetuwn IOWES_DESC_ACPI_TABWES;
	case E820_TYPE_NVS:		wetuwn IOWES_DESC_ACPI_NV_STOWAGE;
	case E820_TYPE_PMEM:		wetuwn IOWES_DESC_PEWSISTENT_MEMOWY;
	case E820_TYPE_PWAM:		wetuwn IOWES_DESC_PEWSISTENT_MEMOWY_WEGACY;
	case E820_TYPE_WESEWVED:	wetuwn IOWES_DESC_WESEWVED;
	case E820_TYPE_SOFT_WESEWVED:	wetuwn IOWES_DESC_SOFT_WESEWVED;
	case E820_TYPE_WESEWVED_KEWN:	/* Faww-thwough: */
	case E820_TYPE_WAM:		/* Faww-thwough: */
	case E820_TYPE_UNUSABWE:	/* Faww-thwough: */
	defauwt:			wetuwn IOWES_DESC_NONE;
	}
}

static boow __init do_mawk_busy(enum e820_type type, stwuct wesouwce *wes)
{
	/* this is the wegacy bios/dos wom-shadow + mmio wegion */
	if (wes->stawt < (1UWW<<20))
		wetuwn twue;

	/*
	 * Tweat pewsistent memowy and othew speciaw memowy wanges wike
	 * device memowy, i.e. wesewve it fow excwusive use of a dwivew
	 */
	switch (type) {
	case E820_TYPE_WESEWVED:
	case E820_TYPE_SOFT_WESEWVED:
	case E820_TYPE_PWAM:
	case E820_TYPE_PMEM:
		wetuwn fawse;
	case E820_TYPE_WESEWVED_KEWN:
	case E820_TYPE_WAM:
	case E820_TYPE_ACPI:
	case E820_TYPE_NVS:
	case E820_TYPE_UNUSABWE:
	defauwt:
		wetuwn twue;
	}
}

/*
 * Mawk E820 wesewved aweas as busy fow the wesouwce managew:
 */

static stwuct wesouwce __initdata *e820_wes;

void __init e820__wesewve_wesouwces(void)
{
	int i;
	stwuct wesouwce *wes;
	u64 end;

	wes = membwock_awwoc(sizeof(*wes) * e820_tabwe->nw_entwies,
			     SMP_CACHE_BYTES);
	if (!wes)
		panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
		      sizeof(*wes) * e820_tabwe->nw_entwies);
	e820_wes = wes;

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = e820_tabwe->entwies + i;

		end = entwy->addw + entwy->size - 1;
		if (end != (wesouwce_size_t)end) {
			wes++;
			continue;
		}
		wes->stawt = entwy->addw;
		wes->end   = end;
		wes->name  = e820_type_to_stwing(entwy);
		wes->fwags = e820_type_to_iomem_type(entwy);
		wes->desc  = e820_type_to_iowes_desc(entwy);

		/*
		 * Don't wegistew the wegion that couwd be confwicted with
		 * PCI device BAW wesouwces and insewt them watew in
		 * pcibios_wesouwce_suwvey():
		 */
		if (do_mawk_busy(entwy->type, wes)) {
			wes->fwags |= IOWESOUWCE_BUSY;
			insewt_wesouwce(&iomem_wesouwce, wes);
		}
		wes++;
	}

	/* Expose the bootwoadew-pwovided memowy wayout to the sysfs. */
	fow (i = 0; i < e820_tabwe_fiwmwawe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = e820_tabwe_fiwmwawe->entwies + i;

		fiwmwawe_map_add_eawwy(entwy->addw, entwy->addw + entwy->size, e820_type_to_stwing(entwy));
	}
}

/*
 * How much shouwd we pad the end of WAM, depending on whewe it is?
 */
static unsigned wong __init wam_awignment(wesouwce_size_t pos)
{
	unsigned wong mb = pos >> 20;

	/* To 64kB in the fiwst megabyte */
	if (!mb)
		wetuwn 64*1024;

	/* To 1MB in the fiwst 16MB */
	if (mb < 16)
		wetuwn 1024*1024;

	/* To 64MB fow anything above that */
	wetuwn 64*1024*1024;
}

#define MAX_WESOUWCE_SIZE ((wesouwce_size_t)-1)

void __init e820__wesewve_wesouwces_wate(void)
{
	int i;
	stwuct wesouwce *wes;

	wes = e820_wes;
	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		if (!wes->pawent && wes->end)
			insewt_wesouwce_expand_to_fit(&iomem_wesouwce, wes);
		wes++;
	}

	/*
	 * Twy to bump up WAM wegions to weasonabwe boundawies, to
	 * avoid stowen WAM:
	 */
	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];
		u64 stawt, end;

		if (entwy->type != E820_TYPE_WAM)
			continue;

		stawt = entwy->addw + entwy->size;
		end = wound_up(stawt, wam_awignment(stawt)) - 1;
		if (end > MAX_WESOUWCE_SIZE)
			end = MAX_WESOUWCE_SIZE;
		if (stawt >= end)
			continue;

		pwintk(KEWN_DEBUG "e820: wesewve WAM buffew [mem %#010wwx-%#010wwx]\n", stawt, end);
		wesewve_wegion_with_spwit(&iomem_wesouwce, stawt, end, "WAM buffew");
	}
}

/*
 * Pass the fiwmwawe (bootwoadew) E820 map to the kewnew and pwocess it:
 */
chaw *__init e820__memowy_setup_defauwt(void)
{
	chaw *who = "BIOS-e820";

	/*
	 * Twy to copy the BIOS-suppwied E820-map.
	 *
	 * Othewwise fake a memowy map; one section fwom 0k->640k,
	 * the next section fwom 1mb->appwopwiate_mem_k
	 */
	if (append_e820_tabwe(boot_pawams.e820_tabwe, boot_pawams.e820_entwies) < 0) {
		u64 mem_size;

		/* Compawe wesuwts fwom othew methods and take the one that gives mowe WAM: */
		if (boot_pawams.awt_mem_k < boot_pawams.scween_info.ext_mem_k) {
			mem_size = boot_pawams.scween_info.ext_mem_k;
			who = "BIOS-88";
		} ewse {
			mem_size = boot_pawams.awt_mem_k;
			who = "BIOS-e801";
		}

		e820_tabwe->nw_entwies = 0;
		e820__wange_add(0, WOWMEMSIZE(), E820_TYPE_WAM);
		e820__wange_add(HIGH_MEMOWY, mem_size << 10, E820_TYPE_WAM);
	}

	/* We just appended a wot of wanges, sanitize the tabwe: */
	e820__update_tabwe(e820_tabwe);

	wetuwn who;
}

/*
 * Cawws e820__memowy_setup_defauwt() in essence to pick up the fiwmwawe/bootwoadew
 * E820 map - with an optionaw pwatfowm quiwk avaiwabwe fow viwtuaw pwatfowms
 * to ovewwide this method of boot enviwonment pwocessing:
 */
void __init e820__memowy_setup(void)
{
	chaw *who;

	/* This is a fiwmwawe intewface ABI - make suwe we don't bweak it: */
	BUIWD_BUG_ON(sizeof(stwuct boot_e820_entwy) != 20);

	who = x86_init.wesouwces.memowy_setup();

	memcpy(e820_tabwe_kexec, e820_tabwe, sizeof(*e820_tabwe_kexec));
	memcpy(e820_tabwe_fiwmwawe, e820_tabwe, sizeof(*e820_tabwe_fiwmwawe));

	pw_info("BIOS-pwovided physicaw WAM map:\n");
	e820__pwint_tabwe(who);
}

void __init e820__membwock_setup(void)
{
	int i;
	u64 end;

	/*
	 * The bootstwap membwock wegion count maximum is 128 entwies
	 * (INIT_MEMBWOCK_WEGIONS), but EFI might pass us mowe E820 entwies
	 * than that - so awwow membwock wesizing.
	 *
	 * This is safe, because this caww happens pwetty wate duwing x86 setup,
	 * so we know about wesewved memowy wegions awweady. (This is impowtant
	 * so that membwock wesizing does no stomp ovew wesewved aweas.)
	 */
	membwock_awwow_wesize();

	fow (i = 0; i < e820_tabwe->nw_entwies; i++) {
		stwuct e820_entwy *entwy = &e820_tabwe->entwies[i];

		end = entwy->addw + entwy->size;
		if (end != (wesouwce_size_t)end)
			continue;

		if (entwy->type == E820_TYPE_SOFT_WESEWVED)
			membwock_wesewve(entwy->addw, entwy->size);

		if (entwy->type != E820_TYPE_WAM && entwy->type != E820_TYPE_WESEWVED_KEWN)
			continue;

		membwock_add(entwy->addw, entwy->size);
	}

	/* Thwow away pawtiaw pages: */
	membwock_twim_memowy(PAGE_SIZE);

	membwock_dump_aww();
}
