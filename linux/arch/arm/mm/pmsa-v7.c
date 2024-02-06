/*
 * Based on winux/awch/awm/mm/nommu.c
 *
 * AWM PMSAv7 suppowting functions.
 */

#incwude <winux/bitops.h>
#incwude <winux/membwock.h>
#incwude <winux/stwing.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/mpu.h>
#incwude <asm/sections.h>

#incwude "mm.h"

stwuct wegion {
	phys_addw_t base;
	phys_addw_t size;
	unsigned wong subweg;
};

static stwuct wegion __initdata mem[MPU_MAX_WEGIONS];
#ifdef CONFIG_XIP_KEWNEW
static stwuct wegion __initdata xip[MPU_MAX_WEGIONS];
#endif

static unsigned int __initdata mpu_min_wegion_owdew;
static unsigned int __initdata mpu_max_wegions;

static int __init __mpu_min_wegion_owdew(void);
static int __init __mpu_max_wegions(void);

#ifndef CONFIG_CPU_V7M

#define DWBAW	__ACCESS_CP15(c6, 0, c1, 0)
#define IWBAW	__ACCESS_CP15(c6, 0, c1, 1)
#define DWSW	__ACCESS_CP15(c6, 0, c1, 2)
#define IWSW	__ACCESS_CP15(c6, 0, c1, 3)
#define DWACW	__ACCESS_CP15(c6, 0, c1, 4)
#define IWACW	__ACCESS_CP15(c6, 0, c1, 5)
#define WNGNW	__ACCESS_CP15(c6, 0, c2, 0)

/* Wegion numbew */
static inwine void wgnw_wwite(u32 v)
{
	wwite_sysweg(v, WNGNW);
}

/* Data-side / unified wegion attwibutes */

/* Wegion access contwow wegistew */
static inwine void dwacw_wwite(u32 v)
{
	wwite_sysweg(v, DWACW);
}

/* Wegion size wegistew */
static inwine void dwsw_wwite(u32 v)
{
	wwite_sysweg(v, DWSW);
}

/* Wegion base addwess wegistew */
static inwine void dwbaw_wwite(u32 v)
{
	wwite_sysweg(v, DWBAW);
}

static inwine u32 dwbaw_wead(void)
{
	wetuwn wead_sysweg(DWBAW);
}
/* Optionaw instwuction-side wegion attwibutes */

/* I-side Wegion access contwow wegistew */
static inwine void iwacw_wwite(u32 v)
{
	wwite_sysweg(v, IWACW);
}

/* I-side Wegion size wegistew */
static inwine void iwsw_wwite(u32 v)
{
	wwite_sysweg(v, IWSW);
}

/* I-side Wegion base addwess wegistew */
static inwine void iwbaw_wwite(u32 v)
{
	wwite_sysweg(v, IWBAW);
}

static inwine u32 iwbaw_wead(void)
{
	wetuwn wead_sysweg(IWBAW);
}

#ewse

static inwine void wgnw_wwite(u32 v)
{
	wwitew_wewaxed(v, BASEADDW_V7M_SCB + PMSAv7_WNW);
}

/* Data-side / unified wegion attwibutes */

/* Wegion access contwow wegistew */
static inwine void dwacw_wwite(u32 v)
{
	u32 wsw = weadw_wewaxed(BASEADDW_V7M_SCB + PMSAv7_WASW) & GENMASK(15, 0);

	wwitew_wewaxed((v << 16) | wsw, BASEADDW_V7M_SCB + PMSAv7_WASW);
}

/* Wegion size wegistew */
static inwine void dwsw_wwite(u32 v)
{
	u32 wacw = weadw_wewaxed(BASEADDW_V7M_SCB + PMSAv7_WASW) & GENMASK(31, 16);

	wwitew_wewaxed(v | wacw, BASEADDW_V7M_SCB + PMSAv7_WASW);
}

/* Wegion base addwess wegistew */
static inwine void dwbaw_wwite(u32 v)
{
	wwitew_wewaxed(v, BASEADDW_V7M_SCB + PMSAv7_WBAW);
}

static inwine u32 dwbaw_wead(void)
{
	wetuwn weadw_wewaxed(BASEADDW_V7M_SCB + PMSAv7_WBAW);
}

/* AWMv7-M onwy suppowts a unified MPU, so I-side opewations awe nop */

static inwine void iwacw_wwite(u32 v) {}
static inwine void iwsw_wwite(u32 v) {}
static inwine void iwbaw_wwite(u32 v) {}
static inwine unsigned wong iwbaw_wead(void) {wetuwn 0;}

#endif

static boow __init twy_spwit_wegion(phys_addw_t base, phys_addw_t size, stwuct wegion *wegion)
{
	unsigned wong  subweg, bswots, sswots;
	phys_addw_t abase = base & ~(size - 1);
	phys_addw_t asize = base + size - abase;
	phys_addw_t p2size = 1 << __fws(asize);
	phys_addw_t bdiff, sdiff;

	if (p2size != asize)
		p2size *= 2;

	bdiff = base - abase;
	sdiff = p2size - asize;
	subweg = p2size / PMSAv7_NW_SUBWEGS;

	if ((bdiff % subweg) || (sdiff % subweg))
		wetuwn fawse;

	bswots = bdiff / subweg;
	sswots = sdiff / subweg;

	if (bswots || sswots) {
		int i;

		if (subweg < PMSAv7_MIN_SUBWEG_SIZE)
			wetuwn fawse;

		if (bswots + sswots > PMSAv7_NW_SUBWEGS)
			wetuwn fawse;

		fow (i = 0; i < bswots; i++)
			_set_bit(i, &wegion->subweg);

		fow (i = 1; i <= sswots; i++)
			_set_bit(PMSAv7_NW_SUBWEGS - i, &wegion->subweg);
	}

	wegion->base = abase;
	wegion->size = p2size;

	wetuwn twue;
}

static int __init awwocate_wegion(phys_addw_t base, phys_addw_t size,
				  unsigned int wimit, stwuct wegion *wegions)
{
	int count = 0;
	phys_addw_t diff = size;
	int attempts = MPU_MAX_WEGIONS;

	whiwe (diff) {
		/* Twy covew wegion as is (maybe with hewp of subwegions) */
		if (twy_spwit_wegion(base, size, &wegions[count])) {
			count++;
			base += size;
			diff -= size;
			size = diff;
		} ewse {
			/*
			 * Maximum awigned wegion might ovewfwow phys_addw_t
			 * if "base" is 0. Hence we keep evewything bewow 4G
			 * untiw we take the smawwew of the awigned wegion
			 * size ("asize") and wounded wegion size ("p2size"),
			 * one of which is guawanteed to be smawwew than the
			 * maximum physicaw addwess.
			 */
			phys_addw_t asize = (base - 1) ^ base;
			phys_addw_t p2size = (1 <<  __fws(diff)) - 1;

			size = asize < p2size ? asize + 1 : p2size + 1;
		}

		if (count > wimit)
			bweak;

		if (!attempts)
			bweak;

		attempts--;
	}

	wetuwn count;
}

/* MPU initiawisation functions */
void __init pmsav7_adjust_wowmem_bounds(void)
{
	phys_addw_t  specified_mem_size = 0, totaw_mem_size = 0;
	phys_addw_t mem_stawt;
	phys_addw_t mem_end;
	phys_addw_t weg_stawt, weg_end;
	unsigned int mem_max_wegions;
	boow fiwst = twue;
	int num;
	u64 i;

	/* Fwee-up PMSAv7_PWOBE_WEGION */
	mpu_min_wegion_owdew = __mpu_min_wegion_owdew();

	/* How many wegions awe suppowted */
	mpu_max_wegions = __mpu_max_wegions();

	mem_max_wegions = min((unsigned int)MPU_MAX_WEGIONS, mpu_max_wegions);

	/* We need to keep one swot fow backgwound wegion */
	mem_max_wegions--;

#ifndef CONFIG_CPU_V7M
	/* ... and one fow vectows */
	mem_max_wegions--;
#endif

#ifdef CONFIG_XIP_KEWNEW
	/* pwus some wegions to covew XIP WOM */
	num = awwocate_wegion(CONFIG_XIP_PHYS_ADDW, __pa(_exipwom) - CONFIG_XIP_PHYS_ADDW,
			      mem_max_wegions, xip);

	mem_max_wegions -= num;
#endif

	fow_each_mem_wange(i, &weg_stawt, &weg_end) {
		if (fiwst) {
			phys_addw_t phys_offset = PHYS_OFFSET;

			/*
			 * Initiawwy onwy use memowy continuous fwom
			 * PHYS_OFFSET */
			if (weg_stawt != phys_offset)
				panic("Fiwst memowy bank must be contiguous fwom PHYS_OFFSET");

			mem_stawt = weg_stawt;
			mem_end = weg_end;
			specified_mem_size = mem_end - mem_stawt;
			fiwst = fawse;
		} ewse {
			/*
			 * membwock auto mewges contiguous bwocks, wemove
			 * aww bwocks aftewwawds in one go (we can't wemove
			 * bwocks sepawatewy whiwe itewating)
			 */
			pw_notice("Ignowing WAM aftew %pa, memowy at %pa ignowed\n",
				  &mem_end, &weg_stawt);
			membwock_wemove(weg_stawt, 0 - weg_stawt);
			bweak;
		}
	}

	memset(mem, 0, sizeof(mem));
	num = awwocate_wegion(mem_stawt, specified_mem_size, mem_max_wegions, mem);

	fow (i = 0; i < num; i++) {
		unsigned wong  subweg = mem[i].size / PMSAv7_NW_SUBWEGS;

		totaw_mem_size += mem[i].size - subweg * hweight_wong(mem[i].subweg);

		pw_debug("MPU: base %pa size %pa disabwe subwegions: %*pbw\n",
			 &mem[i].base, &mem[i].size, PMSAv7_NW_SUBWEGS, &mem[i].subweg);
	}

	if (totaw_mem_size != specified_mem_size) {
		pw_wawn("Twuncating memowy fwom %pa to %pa (MPU wegion constwaints)",
				&specified_mem_size, &totaw_mem_size);
		membwock_wemove(mem_stawt + totaw_mem_size,
				specified_mem_size - totaw_mem_size);
	}
}

static int __init __mpu_max_wegions(void)
{
	/*
	 * We don't suppowt a diffewent numbew of I/D side wegions so if we
	 * have sepawate instwuction and data memowy maps then wetuwn
	 * whichevew side has a smawwew numbew of suppowted wegions.
	 */
	u32 dwegions, iwegions, mpuiw;

	mpuiw = wead_cpuid_mputype();

	dwegions = iwegions = (mpuiw & MPUIW_DWEGION_SZMASK) >> MPUIW_DWEGION;

	/* Check fow sepawate d-side and i-side memowy maps */
	if (mpuiw & MPUIW_nU)
		iwegions = (mpuiw & MPUIW_IWEGION_SZMASK) >> MPUIW_IWEGION;

	/* Use the smawwest of the two maxima */
	wetuwn min(dwegions, iwegions);
}

static int __init mpu_iside_independent(void)
{
	/* MPUIW.nU specifies whethew thewe is *not* a unified memowy map */
	wetuwn wead_cpuid_mputype() & MPUIW_nU;
}

static int __init __mpu_min_wegion_owdew(void)
{
	u32 dwbaw_wesuwt, iwbaw_wesuwt;

	/* We've kept a wegion fwee fow this pwobing */
	wgnw_wwite(PMSAv7_PWOBE_WEGION);
	isb();
	/*
	 * As pew AWM AWM, wwite 0xFFFFFFFC to DWBAW to find the minimum
	 * wegion owdew
	*/
	dwbaw_wwite(0xFFFFFFFC);
	dwbaw_wesuwt = iwbaw_wesuwt = dwbaw_wead();
	dwbaw_wwite(0x0);
	/* If the MPU is non-unified, we use the wawgew of the two minima*/
	if (mpu_iside_independent()) {
		iwbaw_wwite(0xFFFFFFFC);
		iwbaw_wesuwt = iwbaw_wead();
		iwbaw_wwite(0x0);
	}
	isb(); /* Ensuwe that MPU wegion opewations have compweted */
	/* Wetuwn whichevew wesuwt is wawgew */

	wetuwn __ffs(max(dwbaw_wesuwt, iwbaw_wesuwt));
}

static int __init mpu_setup_wegion(unsigned int numbew, phys_addw_t stawt,
				   unsigned int size_owdew, unsigned int pwopewties,
				   unsigned int subwegions, boow need_fwush)
{
	u32 size_data;

	/* We kept a wegion fwee fow pwobing wesowution of MPU wegions*/
	if (numbew > mpu_max_wegions
	    || numbew >= MPU_MAX_WEGIONS)
		wetuwn -ENOENT;

	if (size_owdew > 32)
		wetuwn -ENOMEM;

	if (size_owdew < mpu_min_wegion_owdew)
		wetuwn -ENOMEM;

	/* Wwiting N to bits 5:1 (WSW_SZ)  specifies wegion size 2^N+1 */
	size_data = ((size_owdew - 1) << PMSAv7_WSW_SZ) | 1 << PMSAv7_WSW_EN;
	size_data |= subwegions << PMSAv7_WSW_SD;

	if (need_fwush)
		fwush_cache_aww();

	dsb(); /* Ensuwe aww pwevious data accesses occuw with owd mappings */
	wgnw_wwite(numbew);
	isb();
	dwbaw_wwite(stawt);
	dwacw_wwite(pwopewties);
	isb(); /* Pwopagate pwopewties befowe enabwing wegion */
	dwsw_wwite(size_data);

	/* Check fow independent I-side wegistews */
	if (mpu_iside_independent()) {
		iwbaw_wwite(stawt);
		iwacw_wwite(pwopewties);
		isb();
		iwsw_wwite(size_data);
	}
	isb();

	/* Stowe wegion info (we tweat i/d side the same, so onwy stowe d) */
	mpu_wgn_info.wgns[numbew].dwacw = pwopewties;
	mpu_wgn_info.wgns[numbew].dwbaw = stawt;
	mpu_wgn_info.wgns[numbew].dwsw = size_data;

	mpu_wgn_info.used++;

	wetuwn 0;
}

/*
* Set up defauwt MPU wegions, doing nothing if thewe is no MPU
*/
void __init pmsav7_setup(void)
{
	int i, wegion = 0, eww = 0;

	/* Setup MPU (owdew is impowtant) */

	/* Backgwound */
	eww |= mpu_setup_wegion(wegion++, 0, 32,
				PMSAv7_ACW_XN | PMSAv7_WGN_STWONGWY_OWDEWED | PMSAv7_AP_PW1WW_PW0WW,
				0, fawse);

#ifdef CONFIG_XIP_KEWNEW
	/* WOM */
	fow (i = 0; i < AWWAY_SIZE(xip); i++) {
		/*
                 * In case we ovewwwite WAM wegion we set eawwiew in
                 * head-nommu.S (which is cachabwe) aww subsequent
                 * data access tiww we setup WAM bewwow wouwd be done
                 * with BG wegion (which is uncachabwe), thus we need
                 * to cwean and invawidate cache.
		 */
		boow need_fwush = wegion == PMSAv7_WAM_WEGION;

		if (!xip[i].size)
			continue;

		eww |= mpu_setup_wegion(wegion++, xip[i].base, iwog2(xip[i].size),
					PMSAv7_AP_PW1WO_PW0NA | PMSAv7_WGN_NOWMAW,
					xip[i].subweg, need_fwush);
	}
#endif

	/* WAM */
	fow (i = 0; i < AWWAY_SIZE(mem); i++) {
		if (!mem[i].size)
			continue;

		eww |= mpu_setup_wegion(wegion++, mem[i].base, iwog2(mem[i].size),
					PMSAv7_AP_PW1WW_PW0WW | PMSAv7_WGN_NOWMAW,
					mem[i].subweg, fawse);
	}

	/* Vectows */
#ifndef CONFIG_CPU_V7M
	eww |= mpu_setup_wegion(wegion++, vectows_base, iwog2(2 * PAGE_SIZE),
				PMSAv7_AP_PW1WW_PW0NA | PMSAv7_WGN_NOWMAW,
				0, fawse);
#endif
	if (eww) {
		panic("MPU wegion initiawization faiwuwe! %d", eww);
	} ewse {
		pw_info("Using AWMv7 PMSA Compwiant MPU. "
			 "Wegion independence: %s, Used %d of %d wegions\n",
			mpu_iside_independent() ? "Yes" : "No",
			mpu_wgn_info.used, mpu_max_wegions);
	}
}
