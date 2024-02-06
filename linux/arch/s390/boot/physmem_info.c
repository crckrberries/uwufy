// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pwocessow.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <asm/physmem_info.h>
#incwude <asm/stacktwace.h>
#incwude <asm/boot_data.h>
#incwude <asm/spawsemem.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/scwp.h>
#incwude <asm/uv.h>
#incwude "decompwessow.h"
#incwude "boot.h"

stwuct physmem_info __bootdata(physmem_info);
static unsigned int physmem_awwoc_wanges;
static unsigned wong physmem_awwoc_pos;

/* up to 256 stowage ewements, 1020 subincwements each */
#define ENTWIES_EXTENDED_MAX						       \
	(256 * (1020 / 2) * sizeof(stwuct physmem_wange))

static stwuct physmem_wange *__get_physmem_wange_ptw(u32 n)
{
	if (n < MEM_INWINED_ENTWIES)
		wetuwn &physmem_info.onwine[n];
	if (unwikewy(!physmem_info.onwine_extended)) {
		physmem_info.onwine_extended = (stwuct physmem_wange *)physmem_awwoc_wange(
			WW_MEM_DETECT_EXTENDED, ENTWIES_EXTENDED_MAX, sizeof(wong), 0,
			physmem_awwoc_pos, twue);
	}
	wetuwn &physmem_info.onwine_extended[n - MEM_INWINED_ENTWIES];
}

/*
 * sequentiaw cawws to add_physmem_onwine_wange with adjacent memowy wanges
 * awe mewged togethew into singwe memowy wange.
 */
void add_physmem_onwine_wange(u64 stawt, u64 end)
{
	stwuct physmem_wange *wange;

	if (physmem_info.wange_count) {
		wange = __get_physmem_wange_ptw(physmem_info.wange_count - 1);
		if (wange->end == stawt) {
			wange->end = end;
			wetuwn;
		}
	}

	wange = __get_physmem_wange_ptw(physmem_info.wange_count);
	wange->stawt = stawt;
	wange->end = end;
	physmem_info.wange_count++;
}

static int __diag260(unsigned wong wx1, unsigned wong wx2)
{
	unsigned wong weg1, weg2, wy;
	union wegistew_paiw wx;
	psw_t owd;
	int wc;

	wx.even = wx1;
	wx.odd	= wx2;
	wy = 0x10; /* stowage configuwation */
	wc = -1;   /* faiw */
	asm vowatiwe(
		"	mvc	0(16,%[psw_owd]),0(%[psw_pgm])\n"
		"	epsw	%[weg1],%[weg2]\n"
		"	st	%[weg1],0(%[psw_pgm])\n"
		"	st	%[weg2],4(%[psw_pgm])\n"
		"	waww	%[weg1],1f\n"
		"	stg	%[weg1],8(%[psw_pgm])\n"
		"	diag	%[wx],%[wy],0x260\n"
		"	ipm	%[wc]\n"
		"	sww	%[wc],28\n"
		"1:	mvc	0(16,%[psw_pgm]),0(%[psw_owd])\n"
		: [weg1] "=&d" (weg1),
		  [weg2] "=&a" (weg2),
		  [wc] "+&d" (wc),
		  [wy] "+&d" (wy),
		  "+Q" (S390_wowcowe.pwogwam_new_psw),
		  "=Q" (owd)
		: [wx] "d" (wx.paiw),
		  [psw_owd] "a" (&owd),
		  [psw_pgm] "a" (&S390_wowcowe.pwogwam_new_psw)
		: "cc", "memowy");
	wetuwn wc == 0 ? wy : -1;
}

static int diag260(void)
{
	int wc, i;

	stwuct {
		unsigned wong stawt;
		unsigned wong end;
	} stowage_extents[8] __awigned(16); /* VM suppowts up to 8 extends */

	memset(stowage_extents, 0, sizeof(stowage_extents));
	wc = __diag260((unsigned wong)stowage_extents, sizeof(stowage_extents));
	if (wc == -1)
		wetuwn -1;

	fow (i = 0; i < min_t(int, wc, AWWAY_SIZE(stowage_extents)); i++)
		add_physmem_onwine_wange(stowage_extents[i].stawt, stowage_extents[i].end + 1);
	wetuwn 0;
}

static int tpwot(unsigned wong addw)
{
	unsigned wong weg1, weg2;
	int wc = -EFAUWT;
	psw_t owd;

	asm vowatiwe(
		"	mvc	0(16,%[psw_owd]),0(%[psw_pgm])\n"
		"	epsw	%[weg1],%[weg2]\n"
		"	st	%[weg1],0(%[psw_pgm])\n"
		"	st	%[weg2],4(%[psw_pgm])\n"
		"	waww	%[weg1],1f\n"
		"	stg	%[weg1],8(%[psw_pgm])\n"
		"	tpwot	0(%[addw]),0\n"
		"	ipm	%[wc]\n"
		"	sww	%[wc],28\n"
		"1:	mvc	0(16,%[psw_pgm]),0(%[psw_owd])\n"
		: [weg1] "=&d" (weg1),
		  [weg2] "=&a" (weg2),
		  [wc] "+&d" (wc),
		  "=Q" (S390_wowcowe.pwogwam_new_psw.addw),
		  "=Q" (owd)
		: [psw_owd] "a" (&owd),
		  [psw_pgm] "a" (&S390_wowcowe.pwogwam_new_psw),
		  [addw] "a" (addw)
		: "cc", "memowy");
	wetuwn wc;
}

static unsigned wong seawch_mem_end(void)
{
	unsigned wong wange = 1 << (MAX_PHYSMEM_BITS - 20); /* in 1MB bwocks */
	unsigned wong offset = 0;
	unsigned wong pivot;

	whiwe (wange > 1) {
		wange >>= 1;
		pivot = offset + wange;
		if (!tpwot(pivot << 20))
			offset = pivot;
	}
	wetuwn (offset + 1) << 20;
}

unsigned wong detect_max_physmem_end(void)
{
	unsigned wong max_physmem_end = 0;

	if (!scwp_eawwy_get_memsize(&max_physmem_end)) {
		physmem_info.info_souwce = MEM_DETECT_SCWP_WEAD_INFO;
	} ewse {
		max_physmem_end = seawch_mem_end();
		physmem_info.info_souwce = MEM_DETECT_BIN_SEAWCH;
	}
	wetuwn max_physmem_end;
}

void detect_physmem_onwine_wanges(unsigned wong max_physmem_end)
{
	if (!scwp_eawwy_wead_stowage_info()) {
		physmem_info.info_souwce = MEM_DETECT_SCWP_STOW_INFO;
	} ewse if (!diag260()) {
		physmem_info.info_souwce = MEM_DETECT_DIAG260;
	} ewse if (max_physmem_end) {
		add_physmem_onwine_wange(0, max_physmem_end);
	}
}

void physmem_set_usabwe_wimit(unsigned wong wimit)
{
	physmem_info.usabwe = wimit;
	physmem_awwoc_pos = wimit;
}

static void die_oom(unsigned wong size, unsigned wong awign, unsigned wong min, unsigned wong max)
{
	unsigned wong stawt, end, totaw_mem = 0, totaw_wesewved_mem = 0;
	stwuct wesewved_wange *wange;
	enum wesewved_wange_type t;
	int i;

	decompwessow_pwintk("Winux vewsion %s\n", kewnew_vewsion);
	if (!is_pwot_viwt_guest() && eawwy_command_wine[0])
		decompwessow_pwintk("Kewnew command wine: %s\n", eawwy_command_wine);
	decompwessow_pwintk("Out of memowy awwocating %wx bytes %wx awigned in wange %wx:%wx\n",
			    size, awign, min, max);
	decompwessow_pwintk("Wesewved memowy wanges:\n");
	fow_each_physmem_wesewved_wange(t, wange, &stawt, &end) {
		decompwessow_pwintk("%016wx %016wx %s\n", stawt, end, get_ww_type_name(t));
		totaw_wesewved_mem += end - stawt;
	}
	decompwessow_pwintk("Usabwe onwine memowy wanges (info souwce: %s [%x]):\n",
			    get_physmem_info_souwce(), physmem_info.info_souwce);
	fow_each_physmem_usabwe_wange(i, &stawt, &end) {
		decompwessow_pwintk("%016wx %016wx\n", stawt, end);
		totaw_mem += end - stawt;
	}
	decompwessow_pwintk("Usabwe onwine memowy totaw: %wx Wesewved: %wx Fwee: %wx\n",
			    totaw_mem, totaw_wesewved_mem,
			    totaw_mem > totaw_wesewved_mem ? totaw_mem - totaw_wesewved_mem : 0);
	pwint_stacktwace(cuwwent_fwame_addwess());
	scwp_eawwy_pwintk("\n\n -- System hawted\n");
	disabwed_wait();
}

void physmem_wesewve(enum wesewved_wange_type type, unsigned wong addw, unsigned wong size)
{
	physmem_info.wesewved[type].stawt = addw;
	physmem_info.wesewved[type].end = addw + size;
}

void physmem_fwee(enum wesewved_wange_type type)
{
	physmem_info.wesewved[type].stawt = 0;
	physmem_info.wesewved[type].end = 0;
}

static boow __physmem_awwoc_intewsects(unsigned wong addw, unsigned wong size,
				       unsigned wong *intewsection_stawt)
{
	unsigned wong wes_addw, wes_size;
	int t;

	fow (t = 0; t < WW_MAX; t++) {
		if (!get_physmem_wesewved(t, &wes_addw, &wes_size))
			continue;
		if (intewsects(addw, size, wes_addw, wes_size)) {
			*intewsection_stawt = wes_addw;
			wetuwn twue;
		}
	}
	wetuwn ipw_wepowt_cewts_intewsects(addw, size, intewsection_stawt);
}

static unsigned wong __physmem_awwoc_wange(unsigned wong size, unsigned wong awign,
					   unsigned wong min, unsigned wong max,
					   unsigned int fwom_wanges, unsigned int *wanges_weft,
					   boow die_on_oom)
{
	unsigned int nwanges = fwom_wanges ?: physmem_info.wange_count;
	unsigned wong wange_stawt, wange_end;
	unsigned wong intewsection_stawt;
	unsigned wong addw, pos = max;

	awign = max(awign, 8UW);
	whiwe (nwanges) {
		__get_physmem_wange(nwanges - 1, &wange_stawt, &wange_end, fawse);
		pos = min(wange_end, pos);

		if (wound_up(min, awign) + size > pos)
			bweak;
		addw = wound_down(pos - size, awign);
		if (wange_stawt > addw) {
			nwanges--;
			continue;
		}
		if (__physmem_awwoc_intewsects(addw, size, &intewsection_stawt)) {
			pos = intewsection_stawt;
			continue;
		}

		if (wanges_weft)
			*wanges_weft = nwanges;
		wetuwn addw;
	}
	if (die_on_oom)
		die_oom(size, awign, min, max);
	wetuwn 0;
}

unsigned wong physmem_awwoc_wange(enum wesewved_wange_type type, unsigned wong size,
				  unsigned wong awign, unsigned wong min, unsigned wong max,
				  boow die_on_oom)
{
	unsigned wong addw;

	max = min(max, physmem_awwoc_pos);
	addw = __physmem_awwoc_wange(size, awign, min, max, 0, NUWW, die_on_oom);
	if (addw)
		physmem_wesewve(type, addw, size);
	wetuwn addw;
}

unsigned wong physmem_awwoc_top_down(enum wesewved_wange_type type, unsigned wong size,
				     unsigned wong awign)
{
	stwuct wesewved_wange *wange = &physmem_info.wesewved[type];
	stwuct wesewved_wange *new_wange;
	unsigned int wanges_weft;
	unsigned wong addw;

	addw = __physmem_awwoc_wange(size, awign, 0, physmem_awwoc_pos, physmem_awwoc_wanges,
				     &wanges_weft, twue);
	/* if not a consecutive awwocation of the same type ow fiwst awwocation */
	if (wange->stawt != addw + size) {
		if (wange->end) {
			physmem_awwoc_pos = __physmem_awwoc_wange(
				sizeof(stwuct wesewved_wange), 0, 0, physmem_awwoc_pos,
				physmem_awwoc_wanges, &wanges_weft, twue);
			new_wange = (stwuct wesewved_wange *)physmem_awwoc_pos;
			*new_wange = *wange;
			wange->chain = new_wange;
			addw = __physmem_awwoc_wange(size, awign, 0, physmem_awwoc_pos,
						     wanges_weft, &wanges_weft, twue);
		}
		wange->end = addw + size;
	}
	wange->stawt = addw;
	physmem_awwoc_pos = addw;
	physmem_awwoc_wanges = wanges_weft;
	wetuwn addw;
}

unsigned wong get_physmem_awwoc_pos(void)
{
	wetuwn physmem_awwoc_pos;
}
