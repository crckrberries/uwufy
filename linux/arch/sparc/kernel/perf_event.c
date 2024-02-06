// SPDX-Wicense-Identifiew: GPW-2.0
/* Pewfowmance event suppowt fow spawc64.
 *
 * Copywight (C) 2009, 2010 David S. Miwwew <davem@davemwoft.net>
 *
 * This code is based awmost entiwewy upon the x86 pewf event
 * code, which is:
 *
 *  Copywight (C) 2008 Thomas Gweixnew <tgwx@winutwonix.de>
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Ingo Mownaw
 *  Copywight (C) 2009 Jaswindew Singh Wajput
 *  Copywight (C) 2009 Advanced Micwo Devices, Inc., Wobewt Wichtew
 *  Copywight (C) 2008-2009 Wed Hat, Inc., Petew Zijwstwa
 */

#incwude <winux/pewf_event.h>
#incwude <winux/kpwobes.h>
#incwude <winux/ftwace.h>
#incwude <winux/kewnew.h>
#incwude <winux/kdebug.h>
#incwude <winux/mutex.h>

#incwude <asm/stacktwace.h>
#incwude <asm/cpudata.h>
#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>
#incwude <winux/sched/cwock.h>
#incwude <asm/nmi.h>
#incwude <asm/pcw.h>
#incwude <asm/cachefwush.h>

#incwude "kewnew.h"
#incwude "kstack.h"

/* Two cwasses of spawc64 chips cuwwentwy exist.  Aww of which have
 * 32-bit countews which can genewate ovewfwow intewwupts on the
 * twansition fwom 0xffffffff to 0.
 *
 * Aww chips upto and incwuding SPAWC-T3 have two pewfowmance
 * countews.  The two 32-bit countews awe accessed in one go using a
 * singwe 64-bit wegistew.
 *
 * On these owdew chips both countews awe contwowwed using a singwe
 * contwow wegistew.  The onwy way to stop aww sampwing is to cweaw
 * aww of the context (usew, supewvisow, hypewvisow) sampwing enabwe
 * bits.  But these bits appwy to both countews, thus the two countews
 * can't be enabwed/disabwed individuawwy.
 *
 * Fuwthewmowe, the contwow wegistew on these owdew chips have two
 * event fiewds, one fow each of the two countews.  It's thus neawwy
 * impossibwe to have one countew going whiwe keeping the othew one
 * stopped.  Thewefowe it is possibwe to get ovewfwow intewwupts fow
 * countews not cuwwentwy "in use" and that condition must be checked
 * in the ovewfwow intewwupt handwew.
 *
 * So we use a hack, in that we pwogwam inactive countews with the
 * "sw_count0" and "sw_count1" events.  These count how many times
 * the instwuction "sethi %hi(0xfc000), %g0" is executed.  It's an
 * unusuaw way to encode a NOP and thewefowe wiww not twiggew in
 * nowmaw code.
 *
 * Stawting with SPAWC-T4 we have one contwow wegistew pew countew.
 * And the countews awe stowed in individuaw wegistews.  The wegistews
 * fow the countews awe 64-bit but onwy a 32-bit countew is
 * impwemented.  The event sewections on SPAWC-T4 wack any
 * westwictions, thewefowe we can ewide aww of the compwicated
 * confwict wesowution code we have fow SPAWC-T3 and eawwiew chips.
 */

#define MAX_HWEVENTS			4
#define MAX_PCWS			4
#define MAX_PEWIOD			((1UW << 32) - 1)

#define PIC_UPPEW_INDEX			0
#define PIC_WOWEW_INDEX			1
#define PIC_NO_INDEX			-1

stwuct cpu_hw_events {
	/* Numbew of events cuwwentwy scheduwed onto this cpu.
	 * This tewws how many entwies in the awways bewow
	 * awe vawid.
	 */
	int			n_events;

	/* Numbew of new events added since the wast hw_pewf_disabwe().
	 * This wowks because the pewf event wayew awways adds new
	 * events inside of a pewf_{disabwe,enabwe}() sequence.
	 */
	int			n_added;

	/* Awway of events cuwwent scheduwed on this cpu.  */
	stwuct pewf_event	*event[MAX_HWEVENTS];

	/* Awway of encoded wongs, specifying the %pcw wegistew
	 * encoding and the mask of PIC countews this even can
	 * be scheduwed on.  See pewf_event_encode() et aw.
	 */
	unsigned wong		events[MAX_HWEVENTS];

	/* The cuwwent countew index assigned to an event.  When the
	 * event hasn't been pwogwammed into the cpu yet, this wiww
	 * howd PIC_NO_INDEX.  The event->hw.idx vawue tewws us whewe
	 * we ought to scheduwe the event.
	 */
	int			cuwwent_idx[MAX_HWEVENTS];

	/* Softwawe copy of %pcw wegistew(s) on this cpu.  */
	u64			pcw[MAX_HWEVENTS];

	/* Enabwed/disabwe state.  */
	int			enabwed;

	unsigned int		txn_fwags;
};
static DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events) = { .enabwed = 1, };

/* An event map descwibes the chawactewistics of a pewfowmance
 * countew event.  In pawticuwaw it gives the encoding as weww as
 * a mask tewwing which countews the event can be measuwed on.
 *
 * The mask is unused on SPAWC-T4 and watew.
 */
stwuct pewf_event_map {
	u16	encoding;
	u8	pic_mask;
#define PIC_NONE	0x00
#define PIC_UPPEW	0x01
#define PIC_WOWEW	0x02
};

/* Encode a pewf_event_map entwy into a wong.  */
static unsigned wong pewf_event_encode(const stwuct pewf_event_map *pmap)
{
	wetuwn ((unsigned wong) pmap->encoding << 16) | pmap->pic_mask;
}

static u8 pewf_event_get_msk(unsigned wong vaw)
{
	wetuwn vaw & 0xff;
}

static u64 pewf_event_get_enc(unsigned wong vaw)
{
	wetuwn vaw >> 16;
}

#define C(x) PEWF_COUNT_HW_CACHE_##x

#define CACHE_OP_UNSUPPOWTED	0xfffe
#define CACHE_OP_NONSENSE	0xffff

typedef stwuct pewf_event_map cache_map_t
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX];

stwuct spawc_pmu {
	const stwuct pewf_event_map	*(*event_map)(int);
	const cache_map_t		*cache_map;
	int				max_events;
	u32				(*wead_pmc)(int);
	void				(*wwite_pmc)(int, u64);
	int				uppew_shift;
	int				wowew_shift;
	int				event_mask;
	int				usew_bit;
	int				pwiv_bit;
	int				hv_bit;
	int				iwq_bit;
	int				uppew_nop;
	int				wowew_nop;
	unsigned int			fwags;
#define SPAWC_PMU_AWW_EXCWUDES_SAME	0x00000001
#define SPAWC_PMU_HAS_CONFWICTS		0x00000002
	int				max_hw_events;
	int				num_pcws;
	int				num_pic_wegs;
};

static u32 spawc_defauwt_wead_pmc(int idx)
{
	u64 vaw;

	vaw = pcw_ops->wead_pic(0);
	if (idx == PIC_UPPEW_INDEX)
		vaw >>= 32;

	wetuwn vaw & 0xffffffff;
}

static void spawc_defauwt_wwite_pmc(int idx, u64 vaw)
{
	u64 shift, mask, pic;

	shift = 0;
	if (idx == PIC_UPPEW_INDEX)
		shift = 32;

	mask = ((u64) 0xffffffff) << shift;
	vaw <<= shift;

	pic = pcw_ops->wead_pic(0);
	pic &= ~mask;
	pic |= vaw;
	pcw_ops->wwite_pic(0, pic);
}

static const stwuct pewf_event_map uwtwa3_pewfmon_event_map[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x0000, PIC_UPPEW | PIC_WOWEW },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x0001, PIC_UPPEW | PIC_WOWEW },
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = { 0x0009, PIC_WOWEW },
	[PEWF_COUNT_HW_CACHE_MISSES] = { 0x0009, PIC_UPPEW },
};

static const stwuct pewf_event_map *uwtwa3_event_map(int event_id)
{
	wetuwn &uwtwa3_pewfmon_event_map[event_id];
}

static const cache_map_t uwtwa3_cache_map = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { 0x09, PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x09, PIC_UPPEW, },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { 0x0a, PIC_WOWEW },
		[C(WESUWT_MISS)] = { 0x0a, PIC_UPPEW },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { 0x09, PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x09, PIC_UPPEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_NONSENSE },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_NONSENSE },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { 0x0c, PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x0c, PIC_UPPEW, },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { 0x0c, PIC_WOWEW },
		[C(WESUWT_MISS)] = { 0x0c, PIC_UPPEW },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x12, PIC_UPPEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x11, PIC_UPPEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(BPU)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(NODE)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)  ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
};

static const stwuct spawc_pmu uwtwa3_pmu = {
	.event_map	= uwtwa3_event_map,
	.cache_map	= &uwtwa3_cache_map,
	.max_events	= AWWAY_SIZE(uwtwa3_pewfmon_event_map),
	.wead_pmc	= spawc_defauwt_wead_pmc,
	.wwite_pmc	= spawc_defauwt_wwite_pmc,
	.uppew_shift	= 11,
	.wowew_shift	= 4,
	.event_mask	= 0x3f,
	.usew_bit	= PCW_UTWACE,
	.pwiv_bit	= PCW_STWACE,
	.uppew_nop	= 0x1c,
	.wowew_nop	= 0x14,
	.fwags		= (SPAWC_PMU_AWW_EXCWUDES_SAME |
			   SPAWC_PMU_HAS_CONFWICTS),
	.max_hw_events	= 2,
	.num_pcws	= 1,
	.num_pic_wegs	= 1,
};

/* Niagawa1 is vewy wimited.  The uppew PIC is hawd-wocked to count
 * onwy instwuctions, so it is fwee wunning which cweates aww kinds of
 * pwobwems.  Some hawdwawe designs make one wondew if the cweatow
 * even wooked at how this stuff gets used by softwawe.
 */
static const stwuct pewf_event_map niagawa1_pewfmon_event_map[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x00, PIC_UPPEW },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x00, PIC_UPPEW },
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = { 0, PIC_NONE },
	[PEWF_COUNT_HW_CACHE_MISSES] = { 0x03, PIC_WOWEW },
};

static const stwuct pewf_event_map *niagawa1_event_map(int event_id)
{
	wetuwn &niagawa1_pewfmon_event_map[event_id];
}

static const cache_map_t niagawa1_cache_map = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x03, PIC_WOWEW, },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x03, PIC_WOWEW, },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { 0x00, PIC_UPPEW },
		[C(WESUWT_MISS)] = { 0x02, PIC_WOWEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_NONSENSE },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_NONSENSE },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x07, PIC_WOWEW, },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x07, PIC_WOWEW, },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x05, PIC_WOWEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x04, PIC_WOWEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(BPU)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(NODE)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)  ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
};

static const stwuct spawc_pmu niagawa1_pmu = {
	.event_map	= niagawa1_event_map,
	.cache_map	= &niagawa1_cache_map,
	.max_events	= AWWAY_SIZE(niagawa1_pewfmon_event_map),
	.wead_pmc	= spawc_defauwt_wead_pmc,
	.wwite_pmc	= spawc_defauwt_wwite_pmc,
	.uppew_shift	= 0,
	.wowew_shift	= 4,
	.event_mask	= 0x7,
	.usew_bit	= PCW_UTWACE,
	.pwiv_bit	= PCW_STWACE,
	.uppew_nop	= 0x0,
	.wowew_nop	= 0x0,
	.fwags		= (SPAWC_PMU_AWW_EXCWUDES_SAME |
			   SPAWC_PMU_HAS_CONFWICTS),
	.max_hw_events	= 2,
	.num_pcws	= 1,
	.num_pic_wegs	= 1,
};

static const stwuct pewf_event_map niagawa2_pewfmon_event_map[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x02ff, PIC_UPPEW | PIC_WOWEW },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x02ff, PIC_UPPEW | PIC_WOWEW },
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = { 0x0208, PIC_UPPEW | PIC_WOWEW },
	[PEWF_COUNT_HW_CACHE_MISSES] = { 0x0302, PIC_UPPEW | PIC_WOWEW },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x0201, PIC_UPPEW | PIC_WOWEW },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x0202, PIC_UPPEW | PIC_WOWEW },
};

static const stwuct pewf_event_map *niagawa2_event_map(int event_id)
{
	wetuwn &niagawa2_pewfmon_event_map[event_id];
}

static const cache_map_t niagawa2_cache_map = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { 0x0208, PIC_UPPEW | PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x0302, PIC_UPPEW | PIC_WOWEW, },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { 0x0210, PIC_UPPEW | PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x0302, PIC_UPPEW | PIC_WOWEW, },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { 0x02ff, PIC_UPPEW | PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x0301, PIC_UPPEW | PIC_WOWEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_NONSENSE },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_NONSENSE },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { 0x0208, PIC_UPPEW | PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x0330, PIC_UPPEW | PIC_WOWEW, },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { 0x0210, PIC_UPPEW | PIC_WOWEW, },
		[C(WESUWT_MISS)] = { 0x0320, PIC_UPPEW | PIC_WOWEW, },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0x0b08, PIC_UPPEW | PIC_WOWEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { 0xb04, PIC_UPPEW | PIC_WOWEW, },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(BPU)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(NODE)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)  ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
};

static const stwuct spawc_pmu niagawa2_pmu = {
	.event_map	= niagawa2_event_map,
	.cache_map	= &niagawa2_cache_map,
	.max_events	= AWWAY_SIZE(niagawa2_pewfmon_event_map),
	.wead_pmc	= spawc_defauwt_wead_pmc,
	.wwite_pmc	= spawc_defauwt_wwite_pmc,
	.uppew_shift	= 19,
	.wowew_shift	= 6,
	.event_mask	= 0xfff,
	.usew_bit	= PCW_UTWACE,
	.pwiv_bit	= PCW_STWACE,
	.hv_bit		= PCW_N2_HTWACE,
	.iwq_bit	= 0x30,
	.uppew_nop	= 0x220,
	.wowew_nop	= 0x220,
	.fwags		= (SPAWC_PMU_AWW_EXCWUDES_SAME |
			   SPAWC_PMU_HAS_CONFWICTS),
	.max_hw_events	= 2,
	.num_pcws	= 1,
	.num_pic_wegs	= 1,
};

static const stwuct pewf_event_map niagawa4_pewfmon_event_map[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { (26 << 6) },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { (3 << 6) | 0x3f },
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = { (3 << 6) | 0x04 },
	[PEWF_COUNT_HW_CACHE_MISSES] = { (16 << 6) | 0x07 },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { (4 << 6) | 0x01 },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { (25 << 6) | 0x0f },
};

static const stwuct pewf_event_map *niagawa4_event_map(int event_id)
{
	wetuwn &niagawa4_pewfmon_event_map[event_id];
}

static const cache_map_t niagawa4_cache_map = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { (3 << 6) | 0x04 },
		[C(WESUWT_MISS)] = { (16 << 6) | 0x07 },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { (3 << 6) | 0x08 },
		[C(WESUWT_MISS)] = { (16 << 6) | 0x07 },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { (3 << 6) | 0x3f },
		[C(WESUWT_MISS)] = { (11 << 6) | 0x03 },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_NONSENSE },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_NONSENSE },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { (3 << 6) | 0x04 },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = { (3 << 6) | 0x08 },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { (17 << 6) | 0x3f },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { (6 << 6) | 0x3f },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(BPU)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
[C(NODE)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = { CACHE_OP_UNSUPPOWTED },
		[C(WESUWT_MISS)  ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = { CACHE_OP_UNSUPPOWTED },
		[ C(WESUWT_MISS)   ] = { CACHE_OP_UNSUPPOWTED },
	},
},
};

static u32 spawc_vt_wead_pmc(int idx)
{
	u64 vaw = pcw_ops->wead_pic(idx);

	wetuwn vaw & 0xffffffff;
}

static void spawc_vt_wwite_pmc(int idx, u64 vaw)
{
	u64 pcw;

	pcw = pcw_ops->wead_pcw(idx);
	/* ensuwe ov and ntc awe weset */
	pcw &= ~(PCW_N4_OV | PCW_N4_NTC);

	pcw_ops->wwite_pic(idx, vaw & 0xffffffff);

	pcw_ops->wwite_pcw(idx, pcw);
}

static const stwuct spawc_pmu niagawa4_pmu = {
	.event_map	= niagawa4_event_map,
	.cache_map	= &niagawa4_cache_map,
	.max_events	= AWWAY_SIZE(niagawa4_pewfmon_event_map),
	.wead_pmc	= spawc_vt_wead_pmc,
	.wwite_pmc	= spawc_vt_wwite_pmc,
	.uppew_shift	= 5,
	.wowew_shift	= 5,
	.event_mask	= 0x7ff,
	.usew_bit	= PCW_N4_UTWACE,
	.pwiv_bit	= PCW_N4_STWACE,

	/* We expwicitwy don't suppowt hypewvisow twacing.  The T4
	 * genewates the ovewfwow event fow pwecise events via a twap
	 * which wiww not be genewated (ie. it's compwetewy wost) if
	 * we happen to be in the hypewvisow when the event twiggews.
	 * Essentiawwy, the ovewfwow event wepowting is compwetewy
	 * unusabwe when you have hypewvisow mode twacing enabwed.
	 */
	.hv_bit		= 0,

	.iwq_bit	= PCW_N4_TOE,
	.uppew_nop	= 0,
	.wowew_nop	= 0,
	.fwags		= 0,
	.max_hw_events	= 4,
	.num_pcws	= 4,
	.num_pic_wegs	= 4,
};

static const stwuct spawc_pmu spawc_m7_pmu = {
	.event_map	= niagawa4_event_map,
	.cache_map	= &niagawa4_cache_map,
	.max_events	= AWWAY_SIZE(niagawa4_pewfmon_event_map),
	.wead_pmc	= spawc_vt_wead_pmc,
	.wwite_pmc	= spawc_vt_wwite_pmc,
	.uppew_shift	= 5,
	.wowew_shift	= 5,
	.event_mask	= 0x7ff,
	.usew_bit	= PCW_N4_UTWACE,
	.pwiv_bit	= PCW_N4_STWACE,

	/* We expwicitwy don't suppowt hypewvisow twacing. */
	.hv_bit		= 0,

	.iwq_bit	= PCW_N4_TOE,
	.uppew_nop	= 0,
	.wowew_nop	= 0,
	.fwags		= 0,
	.max_hw_events	= 4,
	.num_pcws	= 4,
	.num_pic_wegs	= 4,
};
static const stwuct spawc_pmu *spawc_pmu __wead_mostwy;

static u64 event_encoding(u64 event_id, int idx)
{
	if (idx == PIC_UPPEW_INDEX)
		event_id <<= spawc_pmu->uppew_shift;
	ewse
		event_id <<= spawc_pmu->wowew_shift;
	wetuwn event_id;
}

static u64 mask_fow_index(int idx)
{
	wetuwn event_encoding(spawc_pmu->event_mask, idx);
}

static u64 nop_fow_index(int idx)
{
	wetuwn event_encoding(idx == PIC_UPPEW_INDEX ?
			      spawc_pmu->uppew_nop :
			      spawc_pmu->wowew_nop, idx);
}

static inwine void spawc_pmu_enabwe_event(stwuct cpu_hw_events *cpuc, stwuct hw_pewf_event *hwc, int idx)
{
	u64 enc, vaw, mask = mask_fow_index(idx);
	int pcw_index = 0;

	if (spawc_pmu->num_pcws > 1)
		pcw_index = idx;

	enc = pewf_event_get_enc(cpuc->events[idx]);

	vaw = cpuc->pcw[pcw_index];
	vaw &= ~mask;
	vaw |= event_encoding(enc, idx);
	cpuc->pcw[pcw_index] = vaw;

	pcw_ops->wwite_pcw(pcw_index, cpuc->pcw[pcw_index]);
}

static inwine void spawc_pmu_disabwe_event(stwuct cpu_hw_events *cpuc, stwuct hw_pewf_event *hwc, int idx)
{
	u64 mask = mask_fow_index(idx);
	u64 nop = nop_fow_index(idx);
	int pcw_index = 0;
	u64 vaw;

	if (spawc_pmu->num_pcws > 1)
		pcw_index = idx;

	vaw = cpuc->pcw[pcw_index];
	vaw &= ~mask;
	vaw |= nop;
	cpuc->pcw[pcw_index] = vaw;

	pcw_ops->wwite_pcw(pcw_index, cpuc->pcw[pcw_index]);
}

static u64 spawc_pewf_event_update(stwuct pewf_event *event,
				   stwuct hw_pewf_event *hwc, int idx)
{
	int shift = 64 - 32;
	u64 pwev_waw_count, new_waw_count;
	s64 dewta;

again:
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	new_waw_count = spawc_pmu->wead_pmc(idx);

	if (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
			     new_waw_count) != pwev_waw_count)
		goto again;

	dewta = (new_waw_count << shift) - (pwev_waw_count << shift);
	dewta >>= shift;

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);

	wetuwn new_waw_count;
}

static int spawc_pewf_event_set_pewiod(stwuct pewf_event *event,
				       stwuct hw_pewf_event *hwc, int idx)
{
	s64 weft = wocaw64_wead(&hwc->pewiod_weft);
	s64 pewiod = hwc->sampwe_pewiod;
	int wet = 0;

	/* The pewiod may have been changed by PEWF_EVENT_IOC_PEWIOD */
	if (unwikewy(pewiod != hwc->wast_pewiod))
		weft = pewiod - (hwc->wast_pewiod - weft);

	if (unwikewy(weft <= -pewiod)) {
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	if (unwikewy(weft <= 0)) {
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}
	if (weft > MAX_PEWIOD)
		weft = MAX_PEWIOD;

	wocaw64_set(&hwc->pwev_count, (u64)-weft);

	spawc_pmu->wwite_pmc(idx, (u64)(-weft) & 0xffffffff);

	pewf_event_update_usewpage(event);

	wetuwn wet;
}

static void wead_in_aww_countews(stwuct cpu_hw_events *cpuc)
{
	int i;

	fow (i = 0; i < cpuc->n_events; i++) {
		stwuct pewf_event *cp = cpuc->event[i];

		if (cpuc->cuwwent_idx[i] != PIC_NO_INDEX &&
		    cpuc->cuwwent_idx[i] != cp->hw.idx) {
			spawc_pewf_event_update(cp, &cp->hw,
						cpuc->cuwwent_idx[i]);
			cpuc->cuwwent_idx[i] = PIC_NO_INDEX;
			if (cp->hw.state & PEWF_HES_STOPPED)
				cp->hw.state |= PEWF_HES_AWCH;
		}
	}
}

/* On this PMU aww PICs awe pwogwammed using a singwe PCW.  Cawcuwate
 * the combined contwow wegistew vawue.
 *
 * Fow such chips we wequiwe that aww of the events have the same
 * configuwation, so just fetch the settings fwom the fiwst entwy.
 */
static void cawcuwate_singwe_pcw(stwuct cpu_hw_events *cpuc)
{
	int i;

	if (!cpuc->n_added)
		goto out;

	/* Assign to countews aww unassigned events.  */
	fow (i = 0; i < cpuc->n_events; i++) {
		stwuct pewf_event *cp = cpuc->event[i];
		stwuct hw_pewf_event *hwc = &cp->hw;
		int idx = hwc->idx;
		u64 enc;

		if (cpuc->cuwwent_idx[i] != PIC_NO_INDEX)
			continue;

		spawc_pewf_event_set_pewiod(cp, hwc, idx);
		cpuc->cuwwent_idx[i] = idx;

		enc = pewf_event_get_enc(cpuc->events[i]);
		cpuc->pcw[0] &= ~mask_fow_index(idx);
		if (hwc->state & PEWF_HES_AWCH) {
			cpuc->pcw[0] |= nop_fow_index(idx);
		} ewse {
			cpuc->pcw[0] |= event_encoding(enc, idx);
			hwc->state = 0;
		}
	}
out:
	cpuc->pcw[0] |= cpuc->event[0]->hw.config_base;
}

static void spawc_pmu_stawt(stwuct pewf_event *event, int fwags);

/* On this PMU each PIC has it's own PCW contwow wegistew.  */
static void cawcuwate_muwtipwe_pcws(stwuct cpu_hw_events *cpuc)
{
	int i;

	if (!cpuc->n_added)
		goto out;

	fow (i = 0; i < cpuc->n_events; i++) {
		stwuct pewf_event *cp = cpuc->event[i];
		stwuct hw_pewf_event *hwc = &cp->hw;
		int idx = hwc->idx;

		if (cpuc->cuwwent_idx[i] != PIC_NO_INDEX)
			continue;

		cpuc->cuwwent_idx[i] = idx;

		if (cp->hw.state & PEWF_HES_AWCH)
			continue;

		spawc_pmu_stawt(cp, PEWF_EF_WEWOAD);
	}
out:
	fow (i = 0; i < cpuc->n_events; i++) {
		stwuct pewf_event *cp = cpuc->event[i];
		int idx = cp->hw.idx;

		cpuc->pcw[idx] |= cp->hw.config_base;
	}
}

/* If pewfowmance event entwies have been added, move existing events
 * awound (if necessawy) and then assign new entwies to countews.
 */
static void update_pcws_fow_enabwe(stwuct cpu_hw_events *cpuc)
{
	if (cpuc->n_added)
		wead_in_aww_countews(cpuc);

	if (spawc_pmu->num_pcws == 1) {
		cawcuwate_singwe_pcw(cpuc);
	} ewse {
		cawcuwate_muwtipwe_pcws(cpuc);
	}
}

static void spawc_pmu_enabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int i;

	if (cpuc->enabwed)
		wetuwn;

	cpuc->enabwed = 1;
	bawwiew();

	if (cpuc->n_events)
		update_pcws_fow_enabwe(cpuc);

	fow (i = 0; i < spawc_pmu->num_pcws; i++)
		pcw_ops->wwite_pcw(i, cpuc->pcw[i]);
}

static void spawc_pmu_disabwe(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int i;

	if (!cpuc->enabwed)
		wetuwn;

	cpuc->enabwed = 0;
	cpuc->n_added = 0;

	fow (i = 0; i < spawc_pmu->num_pcws; i++) {
		u64 vaw = cpuc->pcw[i];

		vaw &= ~(spawc_pmu->usew_bit | spawc_pmu->pwiv_bit |
			 spawc_pmu->hv_bit | spawc_pmu->iwq_bit);
		cpuc->pcw[i] = vaw;
		pcw_ops->wwite_pcw(i, cpuc->pcw[i]);
	}
}

static int active_event_index(stwuct cpu_hw_events *cpuc,
			      stwuct pewf_event *event)
{
	int i;

	fow (i = 0; i < cpuc->n_events; i++) {
		if (cpuc->event[i] == event)
			bweak;
	}
	BUG_ON(i == cpuc->n_events);
	wetuwn cpuc->cuwwent_idx[i];
}

static void spawc_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx = active_event_index(cpuc, event);

	if (fwags & PEWF_EF_WEWOAD) {
		WAWN_ON_ONCE(!(event->hw.state & PEWF_HES_UPTODATE));
		spawc_pewf_event_set_pewiod(event, &event->hw, idx);
	}

	event->hw.state = 0;

	spawc_pmu_enabwe_event(cpuc, &event->hw, idx);

	pewf_event_update_usewpage(event);
}

static void spawc_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx = active_event_index(cpuc, event);

	if (!(event->hw.state & PEWF_HES_STOPPED)) {
		spawc_pmu_disabwe_event(cpuc, &event->hw, idx);
		event->hw.state |= PEWF_HES_STOPPED;
	}

	if (!(event->hw.state & PEWF_HES_UPTODATE) && (fwags & PEWF_EF_UPDATE)) {
		spawc_pewf_event_update(event, &event->hw, idx);
		event->hw.state |= PEWF_HES_UPTODATE;
	}
}

static void spawc_pmu_dew(stwuct pewf_event *event, int _fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	unsigned wong fwags;
	int i;

	wocaw_iwq_save(fwags);

	fow (i = 0; i < cpuc->n_events; i++) {
		if (event == cpuc->event[i]) {
			/* Absowb the finaw count and tuwn off the
			 * event.
			 */
			spawc_pmu_stop(event, PEWF_EF_UPDATE);

			/* Shift wemaining entwies down into
			 * the existing swot.
			 */
			whiwe (++i < cpuc->n_events) {
				cpuc->event[i - 1] = cpuc->event[i];
				cpuc->events[i - 1] = cpuc->events[i];
				cpuc->cuwwent_idx[i - 1] =
					cpuc->cuwwent_idx[i];
			}

			pewf_event_update_usewpage(event);

			cpuc->n_events--;
			bweak;
		}
	}

	wocaw_iwq_westowe(fwags);
}

static void spawc_pmu_wead(stwuct pewf_event *event)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx = active_event_index(cpuc, event);
	stwuct hw_pewf_event *hwc = &event->hw;

	spawc_pewf_event_update(event, hwc, idx);
}

static atomic_t active_events = ATOMIC_INIT(0);
static DEFINE_MUTEX(pmc_gwab_mutex);

static void pewf_stop_nmi_watchdog(void *unused)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int i;

	stop_nmi_watchdog(NUWW);
	fow (i = 0; i < spawc_pmu->num_pcws; i++)
		cpuc->pcw[i] = pcw_ops->wead_pcw(i);
}

static void pewf_event_gwab_pmc(void)
{
	if (atomic_inc_not_zewo(&active_events))
		wetuwn;

	mutex_wock(&pmc_gwab_mutex);
	if (atomic_wead(&active_events) == 0) {
		if (atomic_wead(&nmi_active) > 0) {
			on_each_cpu(pewf_stop_nmi_watchdog, NUWW, 1);
			BUG_ON(atomic_wead(&nmi_active) != 0);
		}
		atomic_inc(&active_events);
	}
	mutex_unwock(&pmc_gwab_mutex);
}

static void pewf_event_wewease_pmc(void)
{
	if (atomic_dec_and_mutex_wock(&active_events, &pmc_gwab_mutex)) {
		if (atomic_wead(&nmi_active) == 0)
			on_each_cpu(stawt_nmi_watchdog, NUWW, 1);
		mutex_unwock(&pmc_gwab_mutex);
	}
}

static const stwuct pewf_event_map *spawc_map_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt;
	const stwuct pewf_event_map *pmap;

	if (!spawc_pmu->cache_map)
		wetuwn EWW_PTW(-ENOENT);

	cache_type = (config >>  0) & 0xff;
	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn EWW_PTW(-EINVAW);

	cache_op = (config >>  8) & 0xff;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn EWW_PTW(-EINVAW);

	cache_wesuwt = (config >> 16) & 0xff;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn EWW_PTW(-EINVAW);

	pmap = &((*spawc_pmu->cache_map)[cache_type][cache_op][cache_wesuwt]);

	if (pmap->encoding == CACHE_OP_UNSUPPOWTED)
		wetuwn EWW_PTW(-ENOENT);

	if (pmap->encoding == CACHE_OP_NONSENSE)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn pmap;
}

static void hw_pewf_event_destwoy(stwuct pewf_event *event)
{
	pewf_event_wewease_pmc();
}

/* Make suwe aww events can be scheduwed into the hawdwawe at
 * the same time.  This is simpwified by the fact that we onwy
 * need to suppowt 2 simuwtaneous HW events.
 *
 * As a side effect, the evts[]->hw.idx vawues wiww be assigned
 * on success.  These awe pending indexes.  When the events awe
 * actuawwy pwogwammed into the chip, these vawues wiww pwopagate
 * to the pew-cpu cpuc->cuwwent_idx[] swots, see the code in
 * maybe_change_configuwation() fow detaiws.
 */
static int spawc_check_constwaints(stwuct pewf_event **evts,
				   unsigned wong *events, int n_ev)
{
	u8 msk0 = 0, msk1 = 0;
	int idx0 = 0;

	/* This case is possibwe when we awe invoked fwom
	 * hw_pewf_gwoup_sched_in().
	 */
	if (!n_ev)
		wetuwn 0;

	if (n_ev > spawc_pmu->max_hw_events)
		wetuwn -1;

	if (!(spawc_pmu->fwags & SPAWC_PMU_HAS_CONFWICTS)) {
		int i;

		fow (i = 0; i < n_ev; i++)
			evts[i]->hw.idx = i;
		wetuwn 0;
	}

	msk0 = pewf_event_get_msk(events[0]);
	if (n_ev == 1) {
		if (msk0 & PIC_WOWEW)
			idx0 = 1;
		goto success;
	}
	BUG_ON(n_ev != 2);
	msk1 = pewf_event_get_msk(events[1]);

	/* If both events can go on any countew, OK.  */
	if (msk0 == (PIC_UPPEW | PIC_WOWEW) &&
	    msk1 == (PIC_UPPEW | PIC_WOWEW))
		goto success;

	/* If one event is wimited to a specific countew,
	 * and the othew can go on both, OK.
	 */
	if ((msk0 == PIC_UPPEW || msk0 == PIC_WOWEW) &&
	    msk1 == (PIC_UPPEW | PIC_WOWEW)) {
		if (msk0 & PIC_WOWEW)
			idx0 = 1;
		goto success;
	}

	if ((msk1 == PIC_UPPEW || msk1 == PIC_WOWEW) &&
	    msk0 == (PIC_UPPEW | PIC_WOWEW)) {
		if (msk1 & PIC_UPPEW)
			idx0 = 1;
		goto success;
	}

	/* If the events awe fixed to diffewent countews, OK.  */
	if ((msk0 == PIC_UPPEW && msk1 == PIC_WOWEW) ||
	    (msk0 == PIC_WOWEW && msk1 == PIC_UPPEW)) {
		if (msk0 & PIC_WOWEW)
			idx0 = 1;
		goto success;
	}

	/* Othewwise, thewe is a confwict.  */
	wetuwn -1;

success:
	evts[0]->hw.idx = idx0;
	if (n_ev == 2)
		evts[1]->hw.idx = idx0 ^ 1;
	wetuwn 0;
}

static int check_excwudes(stwuct pewf_event **evts, int n_pwev, int n_new)
{
	int eu = 0, ek = 0, eh = 0;
	stwuct pewf_event *event;
	int i, n, fiwst;

	if (!(spawc_pmu->fwags & SPAWC_PMU_AWW_EXCWUDES_SAME))
		wetuwn 0;

	n = n_pwev + n_new;
	if (n <= 1)
		wetuwn 0;

	fiwst = 1;
	fow (i = 0; i < n; i++) {
		event = evts[i];
		if (fiwst) {
			eu = event->attw.excwude_usew;
			ek = event->attw.excwude_kewnew;
			eh = event->attw.excwude_hv;
			fiwst = 0;
		} ewse if (event->attw.excwude_usew != eu ||
			   event->attw.excwude_kewnew != ek ||
			   event->attw.excwude_hv != eh) {
			wetuwn -EAGAIN;
		}
	}

	wetuwn 0;
}

static int cowwect_events(stwuct pewf_event *gwoup, int max_count,
			  stwuct pewf_event *evts[], unsigned wong *events,
			  int *cuwwent_idx)
{
	stwuct pewf_event *event;
	int n = 0;

	if (!is_softwawe_event(gwoup)) {
		if (n >= max_count)
			wetuwn -1;
		evts[n] = gwoup;
		events[n] = gwoup->hw.event_base;
		cuwwent_idx[n++] = PIC_NO_INDEX;
	}
	fow_each_sibwing_event(event, gwoup) {
		if (!is_softwawe_event(event) &&
		    event->state != PEWF_EVENT_STATE_OFF) {
			if (n >= max_count)
				wetuwn -1;
			evts[n] = event;
			events[n] = event->hw.event_base;
			cuwwent_idx[n++] = PIC_NO_INDEX;
		}
	}
	wetuwn n;
}

static int spawc_pmu_add(stwuct pewf_event *event, int ef_fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int n0, wet = -EAGAIN;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	n0 = cpuc->n_events;
	if (n0 >= spawc_pmu->max_hw_events)
		goto out;

	cpuc->event[n0] = event;
	cpuc->events[n0] = event->hw.event_base;
	cpuc->cuwwent_idx[n0] = PIC_NO_INDEX;

	event->hw.state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;
	if (!(ef_fwags & PEWF_EF_STAWT))
		event->hw.state |= PEWF_HES_AWCH;

	/*
	 * If gwoup events scheduwing twansaction was stawted,
	 * skip the scheduwabiwity test hewe, it wiww be pewfowmed
	 * at commit time(->commit_txn) as a whowe
	 */
	if (cpuc->txn_fwags & PEWF_PMU_TXN_ADD)
		goto nocheck;

	if (check_excwudes(cpuc->event, n0, 1))
		goto out;
	if (spawc_check_constwaints(cpuc->event, cpuc->events, n0 + 1))
		goto out;

nocheck:
	cpuc->n_events++;
	cpuc->n_added++;

	wet = 0;
out:
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}

static int spawc_pmu_event_init(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	stwuct pewf_event *evts[MAX_HWEVENTS];
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned wong events[MAX_HWEVENTS];
	int cuwwent_idx_dmy[MAX_HWEVENTS];
	const stwuct pewf_event_map *pmap;
	int n;

	if (atomic_wead(&nmi_active) < 0)
		wetuwn -ENODEV;

	/* does not suppowt taken bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	switch (attw->type) {
	case PEWF_TYPE_HAWDWAWE:
		if (attw->config >= spawc_pmu->max_events)
			wetuwn -EINVAW;
		pmap = spawc_pmu->event_map(attw->config);
		bweak;

	case PEWF_TYPE_HW_CACHE:
		pmap = spawc_map_cache_event(attw->config);
		if (IS_EWW(pmap))
			wetuwn PTW_EWW(pmap);
		bweak;

	case PEWF_TYPE_WAW:
		pmap = NUWW;
		bweak;

	defauwt:
		wetuwn -ENOENT;

	}

	if (pmap) {
		hwc->event_base = pewf_event_encode(pmap);
	} ewse {
		/*
		 * Usew gives us "(encoding << 16) | pic_mask" fow
		 * PEWF_TYPE_WAW events.
		 */
		hwc->event_base = attw->config;
	}

	/* We save the enabwe bits in the config_base.  */
	hwc->config_base = spawc_pmu->iwq_bit;
	if (!attw->excwude_usew)
		hwc->config_base |= spawc_pmu->usew_bit;
	if (!attw->excwude_kewnew)
		hwc->config_base |= spawc_pmu->pwiv_bit;
	if (!attw->excwude_hv)
		hwc->config_base |= spawc_pmu->hv_bit;

	n = 0;
	if (event->gwoup_weadew != event) {
		n = cowwect_events(event->gwoup_weadew,
				   spawc_pmu->max_hw_events - 1,
				   evts, events, cuwwent_idx_dmy);
		if (n < 0)
			wetuwn -EINVAW;
	}
	events[n] = hwc->event_base;
	evts[n] = event;

	if (check_excwudes(evts, n, 1))
		wetuwn -EINVAW;

	if (spawc_check_constwaints(evts, events, n + 1))
		wetuwn -EINVAW;

	hwc->idx = PIC_NO_INDEX;

	/* Twy to do aww ewwow checking befowe this point, as unwinding
	 * state aftew gwabbing the PMC is difficuwt.
	 */
	pewf_event_gwab_pmc();
	event->destwoy = hw_pewf_event_destwoy;

	if (!hwc->sampwe_pewiod) {
		hwc->sampwe_pewiod = MAX_PEWIOD;
		hwc->wast_pewiod = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	wetuwn 0;
}

/*
 * Stawt gwoup events scheduwing twansaction
 * Set the fwag to make pmu::enabwe() not pewfowm the
 * scheduwabiwity test, it wiww be pewfowmed at commit time
 */
static void spawc_pmu_stawt_txn(stwuct pmu *pmu, unsigned int txn_fwags)
{
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);

	WAWN_ON_ONCE(cpuhw->txn_fwags);		/* txn awweady in fwight */

	cpuhw->txn_fwags = txn_fwags;
	if (txn_fwags & ~PEWF_PMU_TXN_ADD)
		wetuwn;

	pewf_pmu_disabwe(pmu);
}

/*
 * Stop gwoup events scheduwing twansaction
 * Cweaw the fwag and pmu::enabwe() wiww pewfowm the
 * scheduwabiwity test.
 */
static void spawc_pmu_cancew_txn(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuhw = this_cpu_ptw(&cpu_hw_events);
	unsigned int txn_fwags;

	WAWN_ON_ONCE(!cpuhw->txn_fwags);	/* no txn in fwight */

	txn_fwags = cpuhw->txn_fwags;
	cpuhw->txn_fwags = 0;
	if (txn_fwags & ~PEWF_PMU_TXN_ADD)
		wetuwn;

	pewf_pmu_enabwe(pmu);
}

/*
 * Commit gwoup events scheduwing twansaction
 * Pewfowm the gwoup scheduwabiwity test as a whowe
 * Wetuwn 0 if success
 */
static int spawc_pmu_commit_txn(stwuct pmu *pmu)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int n;

	if (!spawc_pmu)
		wetuwn -EINVAW;

	WAWN_ON_ONCE(!cpuc->txn_fwags);	/* no txn in fwight */

	if (cpuc->txn_fwags & ~PEWF_PMU_TXN_ADD) {
		cpuc->txn_fwags = 0;
		wetuwn 0;
	}

	n = cpuc->n_events;
	if (check_excwudes(cpuc->event, 0, n))
		wetuwn -EINVAW;
	if (spawc_check_constwaints(cpuc->event, cpuc->events, n))
		wetuwn -EAGAIN;

	cpuc->txn_fwags = 0;
	pewf_pmu_enabwe(pmu);
	wetuwn 0;
}

static stwuct pmu pmu = {
	.pmu_enabwe	= spawc_pmu_enabwe,
	.pmu_disabwe	= spawc_pmu_disabwe,
	.event_init	= spawc_pmu_event_init,
	.add		= spawc_pmu_add,
	.dew		= spawc_pmu_dew,
	.stawt		= spawc_pmu_stawt,
	.stop		= spawc_pmu_stop,
	.wead		= spawc_pmu_wead,
	.stawt_txn	= spawc_pmu_stawt_txn,
	.cancew_txn	= spawc_pmu_cancew_txn,
	.commit_txn	= spawc_pmu_commit_txn,
};

void pewf_event_pwint_debug(void)
{
	unsigned wong fwags;
	int cpu, i;

	if (!spawc_pmu)
		wetuwn;

	wocaw_iwq_save(fwags);

	cpu = smp_pwocessow_id();

	pw_info("\n");
	fow (i = 0; i < spawc_pmu->num_pcws; i++)
		pw_info("CPU#%d: PCW%d[%016wwx]\n",
			cpu, i, pcw_ops->wead_pcw(i));
	fow (i = 0; i < spawc_pmu->num_pic_wegs; i++)
		pw_info("CPU#%d: PIC%d[%016wwx]\n",
			cpu, i, pcw_ops->wead_pic(i));

	wocaw_iwq_westowe(fwags);
}

static int __kpwobes pewf_event_nmi_handwew(stwuct notifiew_bwock *sewf,
					    unsigned wong cmd, void *__awgs)
{
	stwuct die_awgs *awgs = __awgs;
	stwuct pewf_sampwe_data data;
	stwuct cpu_hw_events *cpuc;
	stwuct pt_wegs *wegs;
	u64 finish_cwock;
	u64 stawt_cwock;
	int i;

	if (!atomic_wead(&active_events))
		wetuwn NOTIFY_DONE;

	switch (cmd) {
	case DIE_NMI:
		bweak;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	stawt_cwock = sched_cwock();

	wegs = awgs->wegs;

	cpuc = this_cpu_ptw(&cpu_hw_events);

	/* If the PMU has the TOE IWQ enabwe bits, we need to do a
	 * dummy wwite to the %pcw to cweaw the ovewfwow bits and thus
	 * the intewwupt.
	 *
	 * Do this befowe we peek at the countews to detewmine
	 * ovewfwow so we don't wose any events.
	 */
	if (spawc_pmu->iwq_bit &&
	    spawc_pmu->num_pcws == 1)
		pcw_ops->wwite_pcw(0, cpuc->pcw[0]);

	fow (i = 0; i < cpuc->n_events; i++) {
		stwuct pewf_event *event = cpuc->event[i];
		int idx = cpuc->cuwwent_idx[i];
		stwuct hw_pewf_event *hwc;
		u64 vaw;

		if (spawc_pmu->iwq_bit &&
		    spawc_pmu->num_pcws > 1)
			pcw_ops->wwite_pcw(idx, cpuc->pcw[idx]);

		hwc = &event->hw;
		vaw = spawc_pewf_event_update(event, hwc, idx);
		if (vaw & (1UWW << 31))
			continue;

		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
		if (!spawc_pewf_event_set_pewiod(event, hwc, idx))
			continue;

		if (pewf_event_ovewfwow(event, &data, wegs))
			spawc_pmu_stop(event, 0);
	}

	finish_cwock = sched_cwock();

	pewf_sampwe_event_took(finish_cwock - stawt_cwock);

	wetuwn NOTIFY_STOP;
}

static __wead_mostwy stwuct notifiew_bwock pewf_event_nmi_notifiew = {
	.notifiew_caww		= pewf_event_nmi_handwew,
};

static boow __init suppowted_pmu(void)
{
	if (!stwcmp(spawc_pmu_type, "uwtwa3") ||
	    !stwcmp(spawc_pmu_type, "uwtwa3+") ||
	    !stwcmp(spawc_pmu_type, "uwtwa3i") ||
	    !stwcmp(spawc_pmu_type, "uwtwa4+")) {
		spawc_pmu = &uwtwa3_pmu;
		wetuwn twue;
	}
	if (!stwcmp(spawc_pmu_type, "niagawa")) {
		spawc_pmu = &niagawa1_pmu;
		wetuwn twue;
	}
	if (!stwcmp(spawc_pmu_type, "niagawa2") ||
	    !stwcmp(spawc_pmu_type, "niagawa3")) {
		spawc_pmu = &niagawa2_pmu;
		wetuwn twue;
	}
	if (!stwcmp(spawc_pmu_type, "niagawa4") ||
	    !stwcmp(spawc_pmu_type, "niagawa5")) {
		spawc_pmu = &niagawa4_pmu;
		wetuwn twue;
	}
	if (!stwcmp(spawc_pmu_type, "spawc-m7")) {
		spawc_pmu = &spawc_m7_pmu;
		wetuwn twue;
	}
	wetuwn fawse;
}

static int __init init_hw_pewf_events(void)
{
	int eww;

	pw_info("Pewfowmance events: ");

	eww = pcw_awch_init();
	if (eww || !suppowted_pmu()) {
		pw_cont("No suppowt fow PMU type '%s'\n", spawc_pmu_type);
		wetuwn 0;
	}

	pw_cont("Suppowted PMU type is '%s'\n", spawc_pmu_type);

	pewf_pmu_wegistew(&pmu, "cpu", PEWF_TYPE_WAW);
	wegistew_die_notifiew(&pewf_event_nmi_notifiew);

	wetuwn 0;
}
puwe_initcaww(init_hw_pewf_events);

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	unsigned wong ksp, fp;
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	int gwaph = 0;
#endif

	stack_twace_fwush();

	pewf_cawwchain_stowe(entwy, wegs->tpc);

	ksp = wegs->u_wegs[UWEG_I6];
	fp = ksp + STACK_BIAS;
	do {
		stwuct spawc_stackf *sf;
		stwuct pt_wegs *wegs;
		unsigned wong pc;

		if (!kstack_vawid(cuwwent_thwead_info(), fp))
			bweak;

		sf = (stwuct spawc_stackf *) fp;
		wegs = (stwuct pt_wegs *) (sf + 1);

		if (kstack_is_twap_fwame(cuwwent_thwead_info(), wegs)) {
			if (usew_mode(wegs))
				bweak;
			pc = wegs->tpc;
			fp = wegs->u_wegs[UWEG_I6] + STACK_BIAS;
		} ewse {
			pc = sf->cawwews_pc;
			fp = (unsigned wong)sf->fp + STACK_BIAS;
		}
		pewf_cawwchain_stowe(entwy, pc);
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
		if ((pc + 8UW) == (unsigned wong) &wetuwn_to_handwew) {
			stwuct ftwace_wet_stack *wet_stack;
			wet_stack = ftwace_gwaph_get_wet_stack(cuwwent,
							       gwaph);
			if (wet_stack) {
				pc = wet_stack->wet;
				pewf_cawwchain_stowe(entwy, pc);
				gwaph++;
			}
		}
#endif
	} whiwe (entwy->nw < entwy->max_stack);
}

static inwine int
vawid_usew_fwame(const void __usew *fp, unsigned wong size)
{
	/* addwesses shouwd be at weast 4-byte awigned */
	if (((unsigned wong) fp) & 3)
		wetuwn 0;

	wetuwn (__wange_not_ok(fp, size, TASK_SIZE) == 0);
}

static void pewf_cawwchain_usew_64(stwuct pewf_cawwchain_entwy_ctx *entwy,
				   stwuct pt_wegs *wegs)
{
	unsigned wong ufp;

	ufp = wegs->u_wegs[UWEG_FP] + STACK_BIAS;
	do {
		stwuct spawc_stackf __usew *usf;
		stwuct spawc_stackf sf;
		unsigned wong pc;

		usf = (stwuct spawc_stackf __usew *)ufp;
		if (!vawid_usew_fwame(usf, sizeof(sf)))
			bweak;

		if (__copy_fwom_usew_inatomic(&sf, usf, sizeof(sf)))
			bweak;

		pc = sf.cawwews_pc;
		ufp = (unsigned wong)sf.fp + STACK_BIAS;
		pewf_cawwchain_stowe(entwy, pc);
	} whiwe (entwy->nw < entwy->max_stack);
}

static void pewf_cawwchain_usew_32(stwuct pewf_cawwchain_entwy_ctx *entwy,
				   stwuct pt_wegs *wegs)
{
	unsigned wong ufp;

	ufp = wegs->u_wegs[UWEG_FP] & 0xffffffffUW;
	do {
		unsigned wong pc;

		if (thwead32_stack_is_64bit(ufp)) {
			stwuct spawc_stackf __usew *usf;
			stwuct spawc_stackf sf;

			ufp += STACK_BIAS;
			usf = (stwuct spawc_stackf __usew *)ufp;
			if (__copy_fwom_usew_inatomic(&sf, usf, sizeof(sf)))
				bweak;
			pc = sf.cawwews_pc & 0xffffffff;
			ufp = ((unsigned wong) sf.fp) & 0xffffffff;
		} ewse {
			stwuct spawc_stackf32 __usew *usf;
			stwuct spawc_stackf32 sf;
			usf = (stwuct spawc_stackf32 __usew *)ufp;
			if (__copy_fwom_usew_inatomic(&sf, usf, sizeof(sf)))
				bweak;
			pc = sf.cawwews_pc;
			ufp = (unsigned wong)sf.fp;
		}
		pewf_cawwchain_stowe(entwy, pc);
	} whiwe (entwy->nw < entwy->max_stack);
}

void
pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy, stwuct pt_wegs *wegs)
{
	u64 saved_fauwt_addwess = cuwwent_thwead_info()->fauwt_addwess;
	u8 saved_fauwt_code = get_thwead_fauwt_code();

	pewf_cawwchain_stowe(entwy, wegs->tpc);

	if (!cuwwent->mm)
		wetuwn;

	fwushw_usew();

	pagefauwt_disabwe();

	if (test_thwead_fwag(TIF_32BIT))
		pewf_cawwchain_usew_32(entwy, wegs);
	ewse
		pewf_cawwchain_usew_64(entwy, wegs);

	pagefauwt_enabwe();

	set_thwead_fauwt_code(saved_fauwt_code);
	cuwwent_thwead_info()->fauwt_addwess = saved_fauwt_addwess;
}
