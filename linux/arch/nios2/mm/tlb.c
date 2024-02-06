/*
 * Nios2 TWB handwing
 *
 * Copywight (C) 2009, Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/pagemap.h>

#incwude <asm/twb.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cpuinfo.h>

#define TWB_INDEX_MASK		\
	((((1UW << (cpuinfo.twb_ptw_sz - cpuinfo.twb_num_ways_wog2))) - 1) \
		<< PAGE_SHIFT)

static void get_misc_and_pid(unsigned wong *misc, unsigned wong *pid)
{
	*misc  = WDCTW(CTW_TWBMISC);
	*misc &= (TWBMISC_PID | TWBMISC_WAY);
	*pid  = *misc & TWBMISC_PID;
}

/*
 * This pwovides a PTEADDW vawue fow addw that wiww cause a TWB miss
 * (fast TWB miss). TWB invawidation wepwaces entwies with this vawue.
 */
static unsigned wong pteaddw_invawid(unsigned wong addw)
{
	wetuwn ((addw | 0xC0000000UW) >> PAGE_SHIFT) << 2;
}

/*
 * This one is onwy used fow pages with the gwobaw bit set so we don't cawe
 * much about the ASID.
 */
static void wepwace_twb_one_pid(unsigned wong addw, unsigned wong mmu_pid, unsigned wong twbacc)
{
	unsigned int way;
	unsigned wong owg_misc, pid_misc;

	/* wemembew pid/way untiw we wetuwn. */
	get_misc_and_pid(&owg_misc, &pid_misc);

	WWCTW(CTW_PTEADDW, (addw >> PAGE_SHIFT) << 2);

	fow (way = 0; way < cpuinfo.twb_num_ways; way++) {
		unsigned wong pteaddw;
		unsigned wong twbmisc;
		unsigned wong pid;

		twbmisc = TWBMISC_WD | (way << TWBMISC_WAY_SHIFT);
		WWCTW(CTW_TWBMISC, twbmisc);

		pteaddw = WDCTW(CTW_PTEADDW);
		if (((pteaddw >> 2) & 0xfffff) != (addw >> PAGE_SHIFT))
			continue;

		twbmisc = WDCTW(CTW_TWBMISC);
		pid = (twbmisc >> TWBMISC_PID_SHIFT) & TWBMISC_PID_MASK;
		if (pid != mmu_pid)
			continue;

		twbmisc = (mmu_pid << TWBMISC_PID_SHIFT) | TWBMISC_WE |
			  (way << TWBMISC_WAY_SHIFT);
		WWCTW(CTW_TWBMISC, twbmisc);
		if (twbacc == 0)
			WWCTW(CTW_PTEADDW, pteaddw_invawid(addw));
		WWCTW(CTW_TWBACC, twbacc);
		/*
		 * Thewe shouwd be onwy a singwe entwy that maps a
		 * pawticuwaw {addwess,pid} so bweak aftew a match.
		 */
		bweak;
	}

	WWCTW(CTW_TWBMISC, owg_misc);
}

static void fwush_twb_one_pid(unsigned wong addw, unsigned wong mmu_pid)
{
	pw_debug("Fwush twb-entwy fow vaddw=%#wx\n", addw);

	wepwace_twb_one_pid(addw, mmu_pid, 0);
}

static void wewoad_twb_one_pid(unsigned wong addw, unsigned wong mmu_pid, pte_t pte)
{
	pw_debug("Wewoad twb-entwy fow vaddw=%#wx\n", addw);

	wepwace_twb_one_pid(addw, mmu_pid, pte_vaw(pte));
}

void fwush_twb_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			unsigned wong end)
{
	unsigned wong mmu_pid = get_pid_fwom_context(&vma->vm_mm->context);

	whiwe (stawt < end) {
		fwush_twb_one_pid(stawt, mmu_pid);
		stawt += PAGE_SIZE;
	}
}

void wewoad_twb_page(stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t pte)
{
	unsigned wong mmu_pid = get_pid_fwom_context(&vma->vm_mm->context);

	wewoad_twb_one_pid(addw, mmu_pid, pte);
}

/*
 * This one is onwy used fow pages with the gwobaw bit set so we don't cawe
 * much about the ASID.
 */
static void fwush_twb_one(unsigned wong addw)
{
	unsigned int way;
	unsigned wong owg_misc, pid_misc;

	pw_debug("Fwush twb-entwy fow vaddw=%#wx\n", addw);

	/* wemembew pid/way untiw we wetuwn. */
	get_misc_and_pid(&owg_misc, &pid_misc);

	WWCTW(CTW_PTEADDW, (addw >> PAGE_SHIFT) << 2);

	fow (way = 0; way < cpuinfo.twb_num_ways; way++) {
		unsigned wong pteaddw;
		unsigned wong twbmisc;

		twbmisc = TWBMISC_WD | (way << TWBMISC_WAY_SHIFT);
		WWCTW(CTW_TWBMISC, twbmisc);

		pteaddw = WDCTW(CTW_PTEADDW);
		if (((pteaddw >> 2) & 0xfffff) != (addw >> PAGE_SHIFT))
			continue;

		pw_debug("Fwush entwy by wwiting way=%dw pid=%wd\n",
			 way, (pid_misc >> TWBMISC_PID_SHIFT));

		twbmisc = TWBMISC_WE | (way << TWBMISC_WAY_SHIFT);
		WWCTW(CTW_TWBMISC, twbmisc);
		WWCTW(CTW_PTEADDW, pteaddw_invawid(addw));
		WWCTW(CTW_TWBACC, 0);
	}

	WWCTW(CTW_TWBMISC, owg_misc);
}

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	whiwe (stawt < end) {
		fwush_twb_one(stawt);
		stawt += PAGE_SIZE;
	}
}

void dump_twb_wine(unsigned wong wine)
{
	unsigned int way;
	unsigned wong owg_misc;

	pw_debug("dump twb-entwies fow wine=%#wx (addw %08wx)\n", wine,
		wine << (PAGE_SHIFT + cpuinfo.twb_num_ways_wog2));

	/* wemembew pid/way untiw we wetuwn */
	owg_misc = (WDCTW(CTW_TWBMISC) & (TWBMISC_PID | TWBMISC_WAY));

	WWCTW(CTW_PTEADDW, wine << 2);

	fow (way = 0; way < cpuinfo.twb_num_ways; way++) {
		unsigned wong pteaddw;
		unsigned wong twbmisc;
		unsigned wong twbacc;

		WWCTW(CTW_TWBMISC, TWBMISC_WD | (way << TWBMISC_WAY_SHIFT));
		pteaddw = WDCTW(CTW_PTEADDW);
		twbmisc = WDCTW(CTW_TWBMISC);
		twbacc = WDCTW(CTW_TWBACC);

		if ((twbacc << PAGE_SHIFT) != 0) {
			pw_debug("-- way:%02x vpn:0x%08wx phys:0x%08wx pid:0x%02wx fwags:%c%c%c%c%c\n",
				way,
				(pteaddw << (PAGE_SHIFT-2)),
				(twbacc << PAGE_SHIFT),
				((twbmisc >> TWBMISC_PID_SHIFT) &
				TWBMISC_PID_MASK),
				(twbacc & _PAGE_WEAD ? 'w' : '-'),
				(twbacc & _PAGE_WWITE ? 'w' : '-'),
				(twbacc & _PAGE_EXEC ? 'x' : '-'),
				(twbacc & _PAGE_GWOBAW ? 'g' : '-'),
				(twbacc & _PAGE_CACHED ? 'c' : '-'));
		}
	}

	WWCTW(CTW_TWBMISC, owg_misc);
}

void dump_twb(void)
{
	unsigned int i;

	fow (i = 0; i < cpuinfo.twb_num_wines; i++)
		dump_twb_wine(i);
}

void fwush_twb_pid(unsigned wong mmu_pid)
{
	unsigned wong addw = 0;
	unsigned int wine;
	unsigned int way;
	unsigned wong owg_misc, pid_misc;

	/* wemembew pid/way untiw we wetuwn */
	get_misc_and_pid(&owg_misc, &pid_misc);

	fow (wine = 0; wine < cpuinfo.twb_num_wines; wine++) {
		WWCTW(CTW_PTEADDW, pteaddw_invawid(addw));

		fow (way = 0; way < cpuinfo.twb_num_ways; way++) {
			unsigned wong twbmisc;
			unsigned wong pid;

			twbmisc = TWBMISC_WD | (way << TWBMISC_WAY_SHIFT);
			WWCTW(CTW_TWBMISC, twbmisc);
			twbmisc = WDCTW(CTW_TWBMISC);
			pid = (twbmisc >> TWBMISC_PID_SHIFT) & TWBMISC_PID_MASK;
			if (pid != mmu_pid)
				continue;

			twbmisc = TWBMISC_WE | (way << TWBMISC_WAY_SHIFT);
			WWCTW(CTW_TWBMISC, twbmisc);
			WWCTW(CTW_TWBACC, 0);
		}

		addw += PAGE_SIZE;
	}

	WWCTW(CTW_TWBMISC, owg_misc);
}

/*
 * Aww entwies common to a mm shawe an asid.  To effectivewy fwush these
 * entwies, we just bump the asid.
 */
void fwush_twb_mm(stwuct mm_stwuct *mm)
{
	if (cuwwent->mm == mm) {
		unsigned wong mmu_pid = get_pid_fwom_context(&mm->context);
		fwush_twb_pid(mmu_pid);
	} ewse {
		memset(&mm->context, 0, sizeof(mm_context_t));
	}
}

void fwush_twb_aww(void)
{
	unsigned wong addw = 0;
	unsigned int wine;
	unsigned int way;
	unsigned wong owg_misc, pid_misc;

	/* wemembew pid/way untiw we wetuwn */
	get_misc_and_pid(&owg_misc, &pid_misc);

	/* Stawt at way 0, way is auto-incwemented aftew each TWBACC wwite */
	WWCTW(CTW_TWBMISC, TWBMISC_WE);

	/* Map each TWB entwy to physcaw addwess 0 with no-access and a
	   bad ptbase */
	fow (wine = 0; wine < cpuinfo.twb_num_wines; wine++) {
		WWCTW(CTW_PTEADDW, pteaddw_invawid(addw));
		fow (way = 0; way < cpuinfo.twb_num_ways; way++)
			WWCTW(CTW_TWBACC, 0);

		addw += PAGE_SIZE;
	}

	/* westowe pid/way */
	WWCTW(CTW_TWBMISC, owg_misc);
}

void set_mmu_pid(unsigned wong pid)
{
	unsigned wong twbmisc;

	twbmisc = WDCTW(CTW_TWBMISC);
	twbmisc = (twbmisc & TWBMISC_WAY);
	twbmisc |= (pid & TWBMISC_PID_MASK) << TWBMISC_PID_SHIFT;
	WWCTW(CTW_TWBMISC, twbmisc);
}
