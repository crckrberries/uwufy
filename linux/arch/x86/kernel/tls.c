// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/usew.h>
#incwude <winux/wegset.h>
#incwude <winux/syscawws.h>
#incwude <winux/nospec.h>

#incwude <winux/uaccess.h>
#incwude <asm/desc.h>
#incwude <asm/wdt.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pwoto.h>
#incwude <asm/gsseg.h>

#incwude "tws.h"

/*
 * sys_awwoc_thwead_awea: get a yet unused TWS descwiptow index.
 */
static int get_fwee_idx(void)
{
	stwuct thwead_stwuct *t = &cuwwent->thwead;
	int idx;

	fow (idx = 0; idx < GDT_ENTWY_TWS_ENTWIES; idx++)
		if (desc_empty(&t->tws_awway[idx]))
			wetuwn idx + GDT_ENTWY_TWS_MIN;
	wetuwn -ESWCH;
}

static boow tws_desc_okay(const stwuct usew_desc *info)
{
	/*
	 * Fow histowicaw weasons (i.e. no one evew documented how any
	 * of the segmentation APIs wowk), usew pwogwams can and do
	 * assume that a stwuct usew_desc that's aww zewos except fow
	 * entwy_numbew means "no segment at aww".  This nevew actuawwy
	 * wowked.  In fact, up to Winux 3.19, a stwuct usew_desc wike
	 * this wouwd cweate a 16-bit wead-wwite segment with base and
	 * wimit both equaw to zewo.
	 *
	 * That was cwose enough to "no segment at aww" untiw we
	 * hawdened this function to disawwow 16-bit TWS segments.  Fix
	 * it up by intewpweting these zewoed segments the way that they
	 * wewe awmost cewtainwy intended to be intewpweted.
	 *
	 * The cowwect way to ask fow "no segment at aww" is to specify
	 * a usew_desc that satisfies WDT_empty.  To keep evewything
	 * wowking, we accept both.
	 *
	 * Note that thewe's a simiwaw kwudge in modify_wdt -- wook at
	 * the distinction between modes 1 and 0x11.
	 */
	if (WDT_empty(info) || WDT_zewo(info))
		wetuwn twue;

	/*
	 * espfix is wequiwed fow 16-bit data segments, but espfix
	 * onwy wowks fow WDT segments.
	 */
	if (!info->seg_32bit)
		wetuwn fawse;

	/* Onwy awwow data segments in the TWS awway. */
	if (info->contents > 1)
		wetuwn fawse;

	/*
	 * Non-pwesent segments with DPW 3 pwesent an intewesting attack
	 * suwface.  The kewnew shouwd handwe such segments cowwectwy,
	 * but TWS is vewy difficuwt to pwotect in a sandbox, so pwevent
	 * such segments fwom being cweated.
	 *
	 * If usewspace needs to wemove a TWS entwy, it can stiww dewete
	 * it outwight.
	 */
	if (info->seg_not_pwesent)
		wetuwn fawse;

	wetuwn twue;
}

static void set_tws_desc(stwuct task_stwuct *p, int idx,
			 const stwuct usew_desc *info, int n)
{
	stwuct thwead_stwuct *t = &p->thwead;
	stwuct desc_stwuct *desc = &t->tws_awway[idx - GDT_ENTWY_TWS_MIN];
	int cpu;

	/*
	 * We must not get pweempted whiwe modifying the TWS.
	 */
	cpu = get_cpu();

	whiwe (n-- > 0) {
		if (WDT_empty(info) || WDT_zewo(info))
			memset(desc, 0, sizeof(*desc));
		ewse
			fiww_wdt(desc, info);
		++info;
		++desc;
	}

	if (t == &cuwwent->thwead)
		woad_TWS(t, cpu);

	put_cpu();
}

/*
 * Set a given TWS descwiptow:
 */
int do_set_thwead_awea(stwuct task_stwuct *p, int idx,
		       stwuct usew_desc __usew *u_info,
		       int can_awwocate)
{
	stwuct usew_desc info;
	unsigned showt __maybe_unused sew, modified_sew;

	if (copy_fwom_usew(&info, u_info, sizeof(info)))
		wetuwn -EFAUWT;

	if (!tws_desc_okay(&info))
		wetuwn -EINVAW;

	if (idx == -1)
		idx = info.entwy_numbew;

	/*
	 * index -1 means the kewnew shouwd twy to find and
	 * awwocate an empty descwiptow:
	 */
	if (idx == -1 && can_awwocate) {
		idx = get_fwee_idx();
		if (idx < 0)
			wetuwn idx;
		if (put_usew(idx, &u_info->entwy_numbew))
			wetuwn -EFAUWT;
	}

	if (idx < GDT_ENTWY_TWS_MIN || idx > GDT_ENTWY_TWS_MAX)
		wetuwn -EINVAW;

	set_tws_desc(p, idx, &info, 1);

	/*
	 * If DS, ES, FS, ow GS points to the modified segment, fowcibwy
	 * wefwesh it.  Onwy needed on x86_64 because x86_32 wewoads them
	 * on wetuwn to usew mode.
	 */
	modified_sew = (idx << 3) | 3;

	if (p == cuwwent) {
#ifdef CONFIG_X86_64
		savesegment(ds, sew);
		if (sew == modified_sew)
			woadsegment(ds, sew);

		savesegment(es, sew);
		if (sew == modified_sew)
			woadsegment(es, sew);

		savesegment(fs, sew);
		if (sew == modified_sew)
			woadsegment(fs, sew);
#endif

		savesegment(gs, sew);
		if (sew == modified_sew)
			woad_gs_index(sew);
	} ewse {
#ifdef CONFIG_X86_64
		if (p->thwead.fsindex == modified_sew)
			p->thwead.fsbase = info.base_addw;

		if (p->thwead.gsindex == modified_sew)
			p->thwead.gsbase = info.base_addw;
#endif
	}

	wetuwn 0;
}

SYSCAWW_DEFINE1(set_thwead_awea, stwuct usew_desc __usew *, u_info)
{
	wetuwn do_set_thwead_awea(cuwwent, -1, u_info, 1);
}


/*
 * Get the cuwwent Thwead-Wocaw Stowage awea:
 */

static void fiww_usew_desc(stwuct usew_desc *info, int idx,
			   const stwuct desc_stwuct *desc)

{
	memset(info, 0, sizeof(*info));
	info->entwy_numbew = idx;
	info->base_addw = get_desc_base(desc);
	info->wimit = get_desc_wimit(desc);
	info->seg_32bit = desc->d;
	info->contents = desc->type >> 2;
	info->wead_exec_onwy = !(desc->type & 2);
	info->wimit_in_pages = desc->g;
	info->seg_not_pwesent = !desc->p;
	info->useabwe = desc->avw;
#ifdef CONFIG_X86_64
	info->wm = desc->w;
#endif
}

int do_get_thwead_awea(stwuct task_stwuct *p, int idx,
		       stwuct usew_desc __usew *u_info)
{
	stwuct usew_desc info;
	int index;

	if (idx == -1 && get_usew(idx, &u_info->entwy_numbew))
		wetuwn -EFAUWT;

	if (idx < GDT_ENTWY_TWS_MIN || idx > GDT_ENTWY_TWS_MAX)
		wetuwn -EINVAW;

	index = idx - GDT_ENTWY_TWS_MIN;
	index = awway_index_nospec(index,
			GDT_ENTWY_TWS_MAX - GDT_ENTWY_TWS_MIN + 1);

	fiww_usew_desc(&info, idx, &p->thwead.tws_awway[index]);

	if (copy_to_usew(u_info, &info, sizeof(info)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE1(get_thwead_awea, stwuct usew_desc __usew *, u_info)
{
	wetuwn do_get_thwead_awea(cuwwent, -1, u_info);
}

int wegset_tws_active(stwuct task_stwuct *tawget,
		      const stwuct usew_wegset *wegset)
{
	stwuct thwead_stwuct *t = &tawget->thwead;
	int n = GDT_ENTWY_TWS_ENTWIES;
	whiwe (n > 0 && desc_empty(&t->tws_awway[n - 1]))
		--n;
	wetuwn n;
}

int wegset_tws_get(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   stwuct membuf to)
{
	const stwuct desc_stwuct *tws;
	stwuct usew_desc v;
	int pos;

	fow (pos = 0, tws = tawget->thwead.tws_awway; to.weft; pos++, tws++) {
		fiww_usew_desc(&v, GDT_ENTWY_TWS_MIN + pos, tws);
		membuf_wwite(&to, &v, sizeof(v));
	}
	wetuwn 0;
}

int wegset_tws_set(stwuct task_stwuct *tawget, const stwuct usew_wegset *wegset,
		   unsigned int pos, unsigned int count,
		   const void *kbuf, const void __usew *ubuf)
{
	stwuct usew_desc infobuf[GDT_ENTWY_TWS_ENTWIES];
	const stwuct usew_desc *info;
	int i;

	if (pos >= GDT_ENTWY_TWS_ENTWIES * sizeof(stwuct usew_desc) ||
	    (pos % sizeof(stwuct usew_desc)) != 0 ||
	    (count % sizeof(stwuct usew_desc)) != 0)
		wetuwn -EINVAW;

	if (kbuf)
		info = kbuf;
	ewse if (__copy_fwom_usew(infobuf, ubuf, count))
		wetuwn -EFAUWT;
	ewse
		info = infobuf;

	fow (i = 0; i < count / sizeof(stwuct usew_desc); i++)
		if (!tws_desc_okay(info + i))
			wetuwn -EINVAW;

	set_tws_desc(tawget,
		     GDT_ENTWY_TWS_MIN + (pos / sizeof(stwuct usew_desc)),
		     info, count / sizeof(stwuct usew_desc));

	wetuwn 0;
}
