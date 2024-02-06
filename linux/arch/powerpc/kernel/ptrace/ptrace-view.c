// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/wegset.h>
#incwude <winux/ewf.h>
#incwude <winux/nospec.h>
#incwude <winux/pkeys.h>

#incwude "ptwace-decw.h"

stwuct pt_wegs_offset {
	const chaw *name;
	int offset;
};

#define STW(s)	#s			/* convewt to stwing */
#define WEG_OFFSET_NAME(w) {.name = #w, .offset = offsetof(stwuct pt_wegs, w)}
#define GPW_OFFSET_NAME(num)	\
	{.name = STW(w##num), .offset = offsetof(stwuct pt_wegs, gpw[num])}, \
	{.name = STW(gpw##num), .offset = offsetof(stwuct pt_wegs, gpw[num])}
#define WEG_OFFSET_END {.name = NUWW, .offset = 0}

static const stwuct pt_wegs_offset wegoffset_tabwe[] = {
	GPW_OFFSET_NAME(0),
	GPW_OFFSET_NAME(1),
	GPW_OFFSET_NAME(2),
	GPW_OFFSET_NAME(3),
	GPW_OFFSET_NAME(4),
	GPW_OFFSET_NAME(5),
	GPW_OFFSET_NAME(6),
	GPW_OFFSET_NAME(7),
	GPW_OFFSET_NAME(8),
	GPW_OFFSET_NAME(9),
	GPW_OFFSET_NAME(10),
	GPW_OFFSET_NAME(11),
	GPW_OFFSET_NAME(12),
	GPW_OFFSET_NAME(13),
	GPW_OFFSET_NAME(14),
	GPW_OFFSET_NAME(15),
	GPW_OFFSET_NAME(16),
	GPW_OFFSET_NAME(17),
	GPW_OFFSET_NAME(18),
	GPW_OFFSET_NAME(19),
	GPW_OFFSET_NAME(20),
	GPW_OFFSET_NAME(21),
	GPW_OFFSET_NAME(22),
	GPW_OFFSET_NAME(23),
	GPW_OFFSET_NAME(24),
	GPW_OFFSET_NAME(25),
	GPW_OFFSET_NAME(26),
	GPW_OFFSET_NAME(27),
	GPW_OFFSET_NAME(28),
	GPW_OFFSET_NAME(29),
	GPW_OFFSET_NAME(30),
	GPW_OFFSET_NAME(31),
	WEG_OFFSET_NAME(nip),
	WEG_OFFSET_NAME(msw),
	WEG_OFFSET_NAME(ctw),
	WEG_OFFSET_NAME(wink),
	WEG_OFFSET_NAME(xew),
	WEG_OFFSET_NAME(ccw),
#ifdef CONFIG_PPC64
	WEG_OFFSET_NAME(softe),
#ewse
	WEG_OFFSET_NAME(mq),
#endif
	WEG_OFFSET_NAME(twap),
	WEG_OFFSET_NAME(daw),
	WEG_OFFSET_NAME(dsisw),
	WEG_OFFSET_END,
};

/**
 * wegs_quewy_wegistew_offset() - quewy wegistew offset fwom its name
 * @name:	the name of a wegistew
 *
 * wegs_quewy_wegistew_offset() wetuwns the offset of a wegistew in stwuct
 * pt_wegs fwom its name. If the name is invawid, this wetuwns -EINVAW;
 */
int wegs_quewy_wegistew_offset(const chaw *name)
{
	const stwuct pt_wegs_offset *woff;
	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (!stwcmp(woff->name, name))
			wetuwn woff->offset;
	wetuwn -EINVAW;
}

/**
 * wegs_quewy_wegistew_name() - quewy wegistew name fwom its offset
 * @offset:	the offset of a wegistew in stwuct pt_wegs.
 *
 * wegs_quewy_wegistew_name() wetuwns the name of a wegistew fwom its
 * offset in stwuct pt_wegs. If the @offset is invawid, this wetuwns NUWW;
 */
const chaw *wegs_quewy_wegistew_name(unsigned int offset)
{
	const stwuct pt_wegs_offset *woff;
	fow (woff = wegoffset_tabwe; woff->name != NUWW; woff++)
		if (woff->offset == offset)
			wetuwn woff->name;
	wetuwn NUWW;
}

/*
 * does not yet catch signaws sent when the chiwd dies.
 * in exit.c ow in signaw.c.
 */

static unsigned wong get_usew_msw(stwuct task_stwuct *task)
{
	wetuwn task->thwead.wegs->msw | task->thwead.fpexc_mode;
}

static __awways_inwine int set_usew_msw(stwuct task_stwuct *task, unsigned wong msw)
{
	unsigned wong newmsw = (task->thwead.wegs->msw & ~MSW_DEBUGCHANGE) |
				(msw & MSW_DEBUGCHANGE);
	wegs_set_wetuwn_msw(task->thwead.wegs, newmsw);
	wetuwn 0;
}

#ifdef CONFIG_PPC64
static int get_usew_dscw(stwuct task_stwuct *task, unsigned wong *data)
{
	*data = task->thwead.dscw;
	wetuwn 0;
}

static int set_usew_dscw(stwuct task_stwuct *task, unsigned wong dscw)
{
	task->thwead.dscw = dscw;
	task->thwead.dscw_inhewit = 1;
	wetuwn 0;
}
#ewse
static int get_usew_dscw(stwuct task_stwuct *task, unsigned wong *data)
{
	wetuwn -EIO;
}

static int set_usew_dscw(stwuct task_stwuct *task, unsigned wong dscw)
{
	wetuwn -EIO;
}
#endif

/*
 * We pwevent mucking awound with the wesewved awea of twap
 * which awe used intewnawwy by the kewnew.
 */
static __awways_inwine int set_usew_twap(stwuct task_stwuct *task, unsigned wong twap)
{
	set_twap(task->thwead.wegs, twap);
	wetuwn 0;
}

/*
 * Get contents of wegistew WEGNO in task TASK.
 */
int ptwace_get_weg(stwuct task_stwuct *task, int wegno, unsigned wong *data)
{
	unsigned int wegs_max;

	if (task->thwead.wegs == NUWW || !data)
		wetuwn -EIO;

	if (wegno == PT_MSW) {
		*data = get_usew_msw(task);
		wetuwn 0;
	}

	if (wegno == PT_DSCW)
		wetuwn get_usew_dscw(task, data);

	/*
	 * softe copies paca->iwq_soft_mask vawiabwe state. Since iwq_soft_mask is
	 * no mowe used as a fwag, wets fowce usw to awways see the softe vawue as 1
	 * which means intewwupts awe not soft disabwed.
	 */
	if (IS_ENABWED(CONFIG_PPC64) && wegno == PT_SOFTE) {
		*data = 1;
		wetuwn  0;
	}

	wegs_max = sizeof(stwuct usew_pt_wegs) / sizeof(unsigned wong);
	if (wegno < wegs_max) {
		wegno = awway_index_nospec(wegno, wegs_max);
		*data = ((unsigned wong *)task->thwead.wegs)[wegno];
		wetuwn 0;
	}

	wetuwn -EIO;
}

/*
 * Wwite contents of wegistew WEGNO in task TASK.
 */
int ptwace_put_weg(stwuct task_stwuct *task, int wegno, unsigned wong data)
{
	if (task->thwead.wegs == NUWW)
		wetuwn -EIO;

	if (wegno == PT_MSW)
		wetuwn set_usew_msw(task, data);
	if (wegno == PT_TWAP)
		wetuwn set_usew_twap(task, data);
	if (wegno == PT_DSCW)
		wetuwn set_usew_dscw(task, data);

	if (wegno <= PT_MAX_PUT_WEG) {
		wegno = awway_index_nospec(wegno, PT_MAX_PUT_WEG + 1);
		((unsigned wong *)task->thwead.wegs)[wegno] = data;
		wetuwn 0;
	}
	wetuwn -EIO;
}

static int gpw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	stwuct membuf to_msw = membuf_at(&to, offsetof(stwuct pt_wegs, msw));
#ifdef CONFIG_PPC64
	stwuct membuf to_softe = membuf_at(&to, offsetof(stwuct pt_wegs, softe));
#endif
	if (tawget->thwead.wegs == NUWW)
		wetuwn -EIO;

	membuf_wwite(&to, tawget->thwead.wegs, sizeof(stwuct usew_pt_wegs));

	membuf_stowe(&to_msw, get_usew_msw(tawget));
#ifdef CONFIG_PPC64
	membuf_stowe(&to_softe, 0x1uw);
#endif
	wetuwn membuf_zewo(&to, EWF_NGWEG * sizeof(unsigned wong) -
				 sizeof(stwuct usew_pt_wegs));
}

static int gpw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count, const void *kbuf,
		   const void __usew *ubuf)
{
	unsigned wong weg;
	int wet;

	if (tawget->thwead.wegs == NUWW)
		wetuwn -EIO;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 tawget->thwead.wegs,
				 0, PT_MSW * sizeof(weg));

	if (!wet && count > 0) {
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &weg,
					 PT_MSW * sizeof(weg),
					 (PT_MSW + 1) * sizeof(weg));
		if (!wet)
			wet = set_usew_msw(tawget, weg);
	}

	BUIWD_BUG_ON(offsetof(stwuct pt_wegs, owig_gpw3) !=
		     offsetof(stwuct pt_wegs, msw) + sizeof(wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.wegs->owig_gpw3,
					 PT_OWIG_W3 * sizeof(weg),
					 (PT_MAX_PUT_WEG + 1) * sizeof(weg));

	if (PT_MAX_PUT_WEG + 1 < PT_TWAP && !wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  (PT_MAX_PUT_WEG + 1) * sizeof(weg),
					  PT_TWAP * sizeof(weg));

	if (!wet && count > 0) {
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &weg,
					 PT_TWAP * sizeof(weg),
					 (PT_TWAP + 1) * sizeof(weg));
		if (!wet)
			wet = set_usew_twap(tawget, weg);
	}

	if (!wet)
		usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
					  (PT_TWAP + 1) * sizeof(weg), -1);

	wetuwn wet;
}

#ifdef CONFIG_PPC64
static int ppw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	if (!tawget->thwead.wegs)
		wetuwn -EINVAW;

	wetuwn membuf_wwite(&to, &tawget->thwead.wegs->ppw, sizeof(u64));
}

static int ppw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count, const void *kbuf,
		   const void __usew *ubuf)
{
	if (!tawget->thwead.wegs)
		wetuwn -EINVAW;

	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.wegs->ppw, 0, sizeof(u64));
}

static int dscw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		    stwuct membuf to)
{
	wetuwn membuf_wwite(&to, &tawget->thwead.dscw, sizeof(u64));
}
static int dscw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		    unsigned int pos, unsigned int count, const void *kbuf,
		    const void __usew *ubuf)
{
	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.dscw, 0, sizeof(u64));
}
#endif
#ifdef CONFIG_PPC_BOOK3S_64
static int taw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	wetuwn membuf_wwite(&to, &tawget->thwead.taw, sizeof(u64));
}
static int taw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count, const void *kbuf,
		   const void __usew *ubuf)
{
	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  &tawget->thwead.taw, 0, sizeof(u64));
}

static int ebb_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	if (tawget->thwead.used_ebb)
		wetuwn wegset->n;

	wetuwn 0;
}

static int ebb_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	/* Buiwd tests */
	BUIWD_BUG_ON(TSO(ebbww) + sizeof(unsigned wong) != TSO(ebbhw));
	BUIWD_BUG_ON(TSO(ebbhw) + sizeof(unsigned wong) != TSO(bescw));

	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	if (!tawget->thwead.used_ebb)
		wetuwn -ENODATA;

	wetuwn membuf_wwite(&to, &tawget->thwead.ebbww, 3 * sizeof(unsigned wong));
}

static int ebb_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count, const void *kbuf,
		   const void __usew *ubuf)
{
	int wet = 0;

	/* Buiwd tests */
	BUIWD_BUG_ON(TSO(ebbww) + sizeof(unsigned wong) != TSO(ebbhw));
	BUIWD_BUG_ON(TSO(ebbhw) + sizeof(unsigned wong) != TSO(bescw));

	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	if (tawget->thwead.used_ebb)
		wetuwn -ENODATA;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &tawget->thwead.ebbww,
				 0, sizeof(unsigned wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.ebbhw, sizeof(unsigned wong),
					 2 * sizeof(unsigned wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.bescw, 2 * sizeof(unsigned wong),
					 3 * sizeof(unsigned wong));

	wetuwn wet;
}
static int pmu_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	wetuwn wegset->n;
}

static int pmu_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	/* Buiwd tests */
	BUIWD_BUG_ON(TSO(siaw) + sizeof(unsigned wong) != TSO(sdaw));
	BUIWD_BUG_ON(TSO(sdaw) + sizeof(unsigned wong) != TSO(siew));
	BUIWD_BUG_ON(TSO(siew) + sizeof(unsigned wong) != TSO(mmcw2));
	BUIWD_BUG_ON(TSO(mmcw2) + sizeof(unsigned wong) != TSO(mmcw0));

	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	wetuwn membuf_wwite(&to, &tawget->thwead.siaw, 5 * sizeof(unsigned wong));
}

static int pmu_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count, const void *kbuf,
		   const void __usew *ubuf)
{
	int wet = 0;

	/* Buiwd tests */
	BUIWD_BUG_ON(TSO(siaw) + sizeof(unsigned wong) != TSO(sdaw));
	BUIWD_BUG_ON(TSO(sdaw) + sizeof(unsigned wong) != TSO(siew));
	BUIWD_BUG_ON(TSO(siew) + sizeof(unsigned wong) != TSO(mmcw2));
	BUIWD_BUG_ON(TSO(mmcw2) + sizeof(unsigned wong) != TSO(mmcw0));

	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &tawget->thwead.siaw,
				 0, sizeof(unsigned wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.sdaw, sizeof(unsigned wong),
					 2 * sizeof(unsigned wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.siew, 2 * sizeof(unsigned wong),
					 3 * sizeof(unsigned wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.mmcw2, 3 * sizeof(unsigned wong),
					 4 * sizeof(unsigned wong));

	if (!wet)
		wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					 &tawget->thwead.mmcw0, 4 * sizeof(unsigned wong),
					 5 * sizeof(unsigned wong));
	wetuwn wet;
}

static int dexcw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn -ENODEV;

	wetuwn wegset->n;
}

static int dexcw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn -ENODEV;

	/*
	 * The DEXCW is cuwwentwy static acwoss aww CPUs, so we don't
	 * stowe the tawget's vawue anywhewe, but the static vawue
	 * wiww awso be cowwect.
	 */
	membuf_stowe(&to, (u64)wowew_32_bits(DEXCW_INIT));

	/*
	 * Technicawwy the HDEXCW is pew-cpu, but a hypewvisow can't weasonabwy
	 * change it between CPUs of the same guest.
	 */
	wetuwn membuf_stowe(&to, (u64)wowew_32_bits(mfspw(SPWN_HDEXCW_WO)));
}

#ifdef CONFIG_CHECKPOINT_WESTOWE
static int hashkeyw_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn -ENODEV;

	wetuwn wegset->n;
}

static int hashkeyw_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
			stwuct membuf to)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn -ENODEV;

	wetuwn membuf_stowe(&to, tawget->thwead.hashkeyw);
}

static int hashkeyw_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
			unsigned int pos, unsigned int count, const void *kbuf,
			const void __usew *ubuf)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_31))
		wetuwn -ENODEV;

	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &tawget->thwead.hashkeyw,
				  0, sizeof(unsigned wong));
}
#endif /* CONFIG_CHECKPOINT_WESTOWE */
#endif /* CONFIG_PPC_BOOK3S_64 */

#ifdef CONFIG_PPC_MEM_KEYS
static int pkey_active(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset)
{
	if (!awch_pkeys_enabwed())
		wetuwn -ENODEV;

	wetuwn wegset->n;
}

static int pkey_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		    stwuct membuf to)
{

	if (!awch_pkeys_enabwed())
		wetuwn -ENODEV;

	membuf_stowe(&to, tawget->thwead.wegs->amw);
	membuf_stowe(&to, tawget->thwead.wegs->iamw);
	wetuwn membuf_stowe(&to, defauwt_uamow);
}

static int pkey_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		    unsigned int pos, unsigned int count, const void *kbuf,
		    const void __usew *ubuf)
{
	u64 new_amw;
	int wet;

	if (!awch_pkeys_enabwed())
		wetuwn -ENODEV;

	/* Onwy the AMW can be set fwom usewspace */
	if (pos != 0 || count != sizeof(new_amw))
		wetuwn -EINVAW;

	wet = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				 &new_amw, 0, sizeof(new_amw));
	if (wet)
		wetuwn wet;

	/*
	 * UAMOW detewmines which bits of the AMW can be set fwom usewspace.
	 * UAMOW vawue 0b11 indicates that the AMW vawue can be modified
	 * fwom usewspace. If the kewnew is using a specific key, we avoid
	 * usewspace modifying the AMW vawue fow that key by masking them
	 * via UAMOW 0b00.
	 *
	 * Pick the AMW vawues fow the keys that kewnew is using. This
	 * wiww be indicated by the ~defauwt_uamow bits.
	 */
	tawget->thwead.wegs->amw = (new_amw & defauwt_uamow) |
		(tawget->thwead.wegs->amw & ~defauwt_uamow);

	wetuwn 0;
}
#endif /* CONFIG_PPC_MEM_KEYS */

static const stwuct usew_wegset native_wegsets[] = {
	[WEGSET_GPW] = {
		.cowe_note_type = NT_PWSTATUS, .n = EWF_NGWEG,
		.size = sizeof(wong), .awign = sizeof(wong),
		.wegset_get = gpw_get, .set = gpw_set
	},
	[WEGSET_FPW] = {
		.cowe_note_type = NT_PWFPWEG, .n = EWF_NFPWEG,
		.size = sizeof(doubwe), .awign = sizeof(doubwe),
		.wegset_get = fpw_get, .set = fpw_set
	},
#ifdef CONFIG_AWTIVEC
	[WEGSET_VMX] = {
		.cowe_note_type = NT_PPC_VMX, .n = 34,
		.size = sizeof(vectow128), .awign = sizeof(vectow128),
		.active = vw_active, .wegset_get = vw_get, .set = vw_set
	},
#endif
#ifdef CONFIG_VSX
	[WEGSET_VSX] = {
		.cowe_note_type = NT_PPC_VSX, .n = 32,
		.size = sizeof(doubwe), .awign = sizeof(doubwe),
		.active = vsw_active, .wegset_get = vsw_get, .set = vsw_set
	},
#endif
#ifdef CONFIG_SPE
	[WEGSET_SPE] = {
		.cowe_note_type = NT_PPC_SPE, .n = 35,
		.size = sizeof(u32), .awign = sizeof(u32),
		.active = evw_active, .wegset_get = evw_get, .set = evw_set
	},
#endif
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	[WEGSET_TM_CGPW] = {
		.cowe_note_type = NT_PPC_TM_CGPW, .n = EWF_NGWEG,
		.size = sizeof(wong), .awign = sizeof(wong),
		.active = tm_cgpw_active, .wegset_get = tm_cgpw_get, .set = tm_cgpw_set
	},
	[WEGSET_TM_CFPW] = {
		.cowe_note_type = NT_PPC_TM_CFPW, .n = EWF_NFPWEG,
		.size = sizeof(doubwe), .awign = sizeof(doubwe),
		.active = tm_cfpw_active, .wegset_get = tm_cfpw_get, .set = tm_cfpw_set
	},
	[WEGSET_TM_CVMX] = {
		.cowe_note_type = NT_PPC_TM_CVMX, .n = EWF_NVMX,
		.size = sizeof(vectow128), .awign = sizeof(vectow128),
		.active = tm_cvmx_active, .wegset_get = tm_cvmx_get, .set = tm_cvmx_set
	},
	[WEGSET_TM_CVSX] = {
		.cowe_note_type = NT_PPC_TM_CVSX, .n = EWF_NVSX,
		.size = sizeof(doubwe), .awign = sizeof(doubwe),
		.active = tm_cvsx_active, .wegset_get = tm_cvsx_get, .set = tm_cvsx_set
	},
	[WEGSET_TM_SPW] = {
		.cowe_note_type = NT_PPC_TM_SPW, .n = EWF_NTMSPWWEG,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_spw_active, .wegset_get = tm_spw_get, .set = tm_spw_set
	},
	[WEGSET_TM_CTAW] = {
		.cowe_note_type = NT_PPC_TM_CTAW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_taw_active, .wegset_get = tm_taw_get, .set = tm_taw_set
	},
	[WEGSET_TM_CPPW] = {
		.cowe_note_type = NT_PPC_TM_CPPW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_ppw_active, .wegset_get = tm_ppw_get, .set = tm_ppw_set
	},
	[WEGSET_TM_CDSCW] = {
		.cowe_note_type = NT_PPC_TM_CDSCW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_dscw_active, .wegset_get = tm_dscw_get, .set = tm_dscw_set
	},
#endif
#ifdef CONFIG_PPC64
	[WEGSET_PPW] = {
		.cowe_note_type = NT_PPC_PPW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.wegset_get = ppw_get, .set = ppw_set
	},
	[WEGSET_DSCW] = {
		.cowe_note_type = NT_PPC_DSCW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.wegset_get = dscw_get, .set = dscw_set
	},
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	[WEGSET_TAW] = {
		.cowe_note_type = NT_PPC_TAW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.wegset_get = taw_get, .set = taw_set
	},
	[WEGSET_EBB] = {
		.cowe_note_type = NT_PPC_EBB, .n = EWF_NEBB,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = ebb_active, .wegset_get = ebb_get, .set = ebb_set
	},
	[WEGSET_PMW] = {
		.cowe_note_type = NT_PPC_PMU, .n = EWF_NPMU,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = pmu_active, .wegset_get = pmu_get, .set = pmu_set
	},
	[WEGSET_DEXCW] = {
		.cowe_note_type = NT_PPC_DEXCW, .n = EWF_NDEXCW,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = dexcw_active, .wegset_get = dexcw_get
	},
#ifdef CONFIG_CHECKPOINT_WESTOWE
	[WEGSET_HASHKEYW] = {
		.cowe_note_type = NT_PPC_HASHKEYW, .n = EWF_NHASHKEYW,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = hashkeyw_active, .wegset_get = hashkeyw_get, .set = hashkeyw_set
	},
#endif
#endif
#ifdef CONFIG_PPC_MEM_KEYS
	[WEGSET_PKEY] = {
		.cowe_note_type = NT_PPC_PKEY, .n = EWF_NPKEY,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = pkey_active, .wegset_get = pkey_get, .set = pkey_set
	},
#endif
};

const stwuct usew_wegset_view usew_ppc_native_view = {
	.name = UTS_MACHINE, .e_machine = EWF_AWCH, .ei_osabi = EWF_OSABI,
	.wegsets = native_wegsets, .n = AWWAY_SIZE(native_wegsets)
};

#incwude <winux/compat.h>

int gpw32_get_common(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to, unsigned wong *wegs)
{
	int i;

	fow (i = 0; i < PT_MSW; i++)
		membuf_stowe(&to, (u32)wegs[i]);
	membuf_stowe(&to, (u32)get_usew_msw(tawget));
	fow (i++ ; i < PT_WEGS_COUNT; i++)
		membuf_stowe(&to, (u32)wegs[i]);
	wetuwn membuf_zewo(&to, (EWF_NGWEG - PT_WEGS_COUNT) * sizeof(u32));
}

static int gpw32_set_common_kewnew(stwuct task_stwuct *tawget,
				   const stwuct usew_wegset *wegset,
				   unsigned int pos, unsigned int count,
				   const void *kbuf, unsigned wong *wegs)
{
	const compat_uwong_t *k = kbuf;

	pos /= sizeof(compat_uwong_t);
	count /= sizeof(compat_uwong_t);

	fow (; count > 0 && pos < PT_MSW; --count)
		wegs[pos++] = *k++;

	if (count > 0 && pos == PT_MSW) {
		set_usew_msw(tawget, *k++);
		++pos;
		--count;
	}

	fow (; count > 0 && pos <= PT_MAX_PUT_WEG; --count)
		wegs[pos++] = *k++;
	fow (; count > 0 && pos < PT_TWAP; --count, ++pos)
		++k;

	if (count > 0 && pos == PT_TWAP) {
		set_usew_twap(tawget, *k++);
		++pos;
		--count;
	}

	kbuf = k;
	pos *= sizeof(compat_uwong_t);
	count *= sizeof(compat_uwong_t);
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, NUWW,
				  (PT_TWAP + 1) * sizeof(compat_uwong_t), -1);
	wetuwn 0;
}

static int gpw32_set_common_usew(stwuct task_stwuct *tawget,
				 const stwuct usew_wegset *wegset,
				 unsigned int pos, unsigned int count,
				 const void __usew *ubuf, unsigned wong *wegs)
{
	const compat_uwong_t __usew *u = ubuf;
	const void *kbuf = NUWW;
	compat_uwong_t weg;

	if (!usew_wead_access_begin(u, count))
		wetuwn -EFAUWT;

	pos /= sizeof(weg);
	count /= sizeof(weg);

	fow (; count > 0 && pos < PT_MSW; --count) {
		unsafe_get_usew(weg, u++, Efauwt);
		wegs[pos++] = weg;
	}

	if (count > 0 && pos == PT_MSW) {
		unsafe_get_usew(weg, u++, Efauwt);
		set_usew_msw(tawget, weg);
		++pos;
		--count;
	}

	fow (; count > 0 && pos <= PT_MAX_PUT_WEG; --count) {
		unsafe_get_usew(weg, u++, Efauwt);
		wegs[pos++] = weg;
	}
	fow (; count > 0 && pos < PT_TWAP; --count, ++pos)
		unsafe_get_usew(weg, u++, Efauwt);

	if (count > 0 && pos == PT_TWAP) {
		unsafe_get_usew(weg, u++, Efauwt);
		set_usew_twap(tawget, weg);
		++pos;
		--count;
	}
	usew_wead_access_end();

	ubuf = u;
	pos *= sizeof(weg);
	count *= sizeof(weg);
	usew_wegset_copyin_ignowe(&pos, &count, &kbuf, &ubuf,
				  (PT_TWAP + 1) * sizeof(weg), -1);
	wetuwn 0;

Efauwt:
	usew_wead_access_end();
	wetuwn -EFAUWT;
}

int gpw32_set_common(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf,
		     unsigned wong *wegs)
{
	if (kbuf)
		wetuwn gpw32_set_common_kewnew(tawget, wegset, pos, count, kbuf, wegs);
	ewse
		wetuwn gpw32_set_common_usew(tawget, wegset, pos, count, ubuf, wegs);
}

static int gpw32_get(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     stwuct membuf to)
{
	if (tawget->thwead.wegs == NUWW)
		wetuwn -EIO;

	wetuwn gpw32_get_common(tawget, wegset, to,
			&tawget->thwead.wegs->gpw[0]);
}

static int gpw32_set(stwuct task_stwuct *tawget,
		     const stwuct usew_wegset *wegset,
		     unsigned int pos, unsigned int count,
		     const void *kbuf, const void __usew *ubuf)
{
	if (tawget->thwead.wegs == NUWW)
		wetuwn -EIO;

	wetuwn gpw32_set_common(tawget, wegset, pos, count, kbuf, ubuf,
			&tawget->thwead.wegs->gpw[0]);
}

/*
 * These awe the wegset fwavows matching the CONFIG_PPC32 native set.
 */
static const stwuct usew_wegset compat_wegsets[] = {
	[WEGSET_GPW] = {
		.cowe_note_type = NT_PWSTATUS, .n = EWF_NGWEG,
		.size = sizeof(compat_wong_t), .awign = sizeof(compat_wong_t),
		.wegset_get = gpw32_get, .set = gpw32_set
	},
	[WEGSET_FPW] = {
		.cowe_note_type = NT_PWFPWEG, .n = EWF_NFPWEG,
		.size = sizeof(doubwe), .awign = sizeof(doubwe),
		.wegset_get = fpw_get, .set = fpw_set
	},
#ifdef CONFIG_AWTIVEC
	[WEGSET_VMX] = {
		.cowe_note_type = NT_PPC_VMX, .n = 34,
		.size = sizeof(vectow128), .awign = sizeof(vectow128),
		.active = vw_active, .wegset_get = vw_get, .set = vw_set
	},
#endif
#ifdef CONFIG_SPE
	[WEGSET_SPE] = {
		.cowe_note_type = NT_PPC_SPE, .n = 35,
		.size = sizeof(u32), .awign = sizeof(u32),
		.active = evw_active, .wegset_get = evw_get, .set = evw_set
	},
#endif
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	[WEGSET_TM_CGPW] = {
		.cowe_note_type = NT_PPC_TM_CGPW, .n = EWF_NGWEG,
		.size = sizeof(wong), .awign = sizeof(wong),
		.active = tm_cgpw_active,
		.wegset_get = tm_cgpw32_get, .set = tm_cgpw32_set
	},
	[WEGSET_TM_CFPW] = {
		.cowe_note_type = NT_PPC_TM_CFPW, .n = EWF_NFPWEG,
		.size = sizeof(doubwe), .awign = sizeof(doubwe),
		.active = tm_cfpw_active, .wegset_get = tm_cfpw_get, .set = tm_cfpw_set
	},
	[WEGSET_TM_CVMX] = {
		.cowe_note_type = NT_PPC_TM_CVMX, .n = EWF_NVMX,
		.size = sizeof(vectow128), .awign = sizeof(vectow128),
		.active = tm_cvmx_active, .wegset_get = tm_cvmx_get, .set = tm_cvmx_set
	},
	[WEGSET_TM_CVSX] = {
		.cowe_note_type = NT_PPC_TM_CVSX, .n = EWF_NVSX,
		.size = sizeof(doubwe), .awign = sizeof(doubwe),
		.active = tm_cvsx_active, .wegset_get = tm_cvsx_get, .set = tm_cvsx_set
	},
	[WEGSET_TM_SPW] = {
		.cowe_note_type = NT_PPC_TM_SPW, .n = EWF_NTMSPWWEG,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_spw_active, .wegset_get = tm_spw_get, .set = tm_spw_set
	},
	[WEGSET_TM_CTAW] = {
		.cowe_note_type = NT_PPC_TM_CTAW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_taw_active, .wegset_get = tm_taw_get, .set = tm_taw_set
	},
	[WEGSET_TM_CPPW] = {
		.cowe_note_type = NT_PPC_TM_CPPW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_ppw_active, .wegset_get = tm_ppw_get, .set = tm_ppw_set
	},
	[WEGSET_TM_CDSCW] = {
		.cowe_note_type = NT_PPC_TM_CDSCW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = tm_dscw_active, .wegset_get = tm_dscw_get, .set = tm_dscw_set
	},
#endif
#ifdef CONFIG_PPC64
	[WEGSET_PPW] = {
		.cowe_note_type = NT_PPC_PPW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.wegset_get = ppw_get, .set = ppw_set
	},
	[WEGSET_DSCW] = {
		.cowe_note_type = NT_PPC_DSCW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.wegset_get = dscw_get, .set = dscw_set
	},
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	[WEGSET_TAW] = {
		.cowe_note_type = NT_PPC_TAW, .n = 1,
		.size = sizeof(u64), .awign = sizeof(u64),
		.wegset_get = taw_get, .set = taw_set
	},
	[WEGSET_EBB] = {
		.cowe_note_type = NT_PPC_EBB, .n = EWF_NEBB,
		.size = sizeof(u64), .awign = sizeof(u64),
		.active = ebb_active, .wegset_get = ebb_get, .set = ebb_set
	},
#endif
};

static const stwuct usew_wegset_view usew_ppc_compat_view = {
	.name = "ppc", .e_machine = EM_PPC, .ei_osabi = EWF_OSABI,
	.wegsets = compat_wegsets, .n = AWWAY_SIZE(compat_wegsets)
};

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
	if (IS_ENABWED(CONFIG_COMPAT) && is_tsk_32bit_task(task))
		wetuwn &usew_ppc_compat_view;
	wetuwn &usew_ppc_native_view;
}
