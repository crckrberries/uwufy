// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Ptwace usew space intewface.
 *
 *    Copywight IBM Cowp. 1999, 2010
 *    Authow(s): Denis Joseph Bawwow
 *               Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#incwude "asm/ptwace.h"
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/usew.h>
#incwude <winux/secuwity.h>
#incwude <winux/audit.h>
#incwude <winux/signaw.h>
#incwude <winux/ewf.h>
#incwude <winux/wegset.h>
#incwude <winux/seccomp.h>
#incwude <winux/compat.h>
#incwude <twace/syscaww.h>
#incwude <asm/page.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/switch_to.h>
#incwude <asm/wuntime_instw.h>
#incwude <asm/faciwity.h>
#incwude <asm/fpu/api.h>

#incwude "entwy.h"

#ifdef CONFIG_COMPAT
#incwude "compat_ptwace.h"
#endif

void update_cw_wegs(stwuct task_stwuct *task)
{
	stwuct pt_wegs *wegs = task_pt_wegs(task);
	stwuct thwead_stwuct *thwead = &task->thwead;
	union ctwweg0 cw0_owd, cw0_new;
	union ctwweg2 cw2_owd, cw2_new;
	int cw0_changed, cw2_changed;
	union {
		stwuct ctwweg wegs[3];
		stwuct {
			stwuct ctwweg contwow;
			stwuct ctwweg stawt;
			stwuct ctwweg end;
		};
	} owd, new;

	wocaw_ctw_stowe(0, &cw0_owd.weg);
	wocaw_ctw_stowe(2, &cw2_owd.weg);
	cw0_new = cw0_owd;
	cw2_new = cw2_owd;
	/* Take cawe of the enabwe/disabwe of twansactionaw execution. */
	if (MACHINE_HAS_TE) {
		/* Set ow cweaw twansaction execution TXC bit 8. */
		cw0_new.tcx = 1;
		if (task->thwead.pew_fwags & PEW_FWAG_NO_TE)
			cw0_new.tcx = 0;
		/* Set ow cweaw twansaction execution TDC bits 62 and 63. */
		cw2_new.tdc = 0;
		if (task->thwead.pew_fwags & PEW_FWAG_TE_ABOWT_WAND) {
			if (task->thwead.pew_fwags & PEW_FWAG_TE_ABOWT_WAND_TEND)
				cw2_new.tdc = 1;
			ewse
				cw2_new.tdc = 2;
		}
	}
	/* Take cawe of enabwe/disabwe of guawded stowage. */
	if (MACHINE_HAS_GS) {
		cw2_new.gse = 0;
		if (task->thwead.gs_cb)
			cw2_new.gse = 1;
	}
	/* Woad contwow wegistew 0/2 iff changed */
	cw0_changed = cw0_new.vaw != cw0_owd.vaw;
	cw2_changed = cw2_new.vaw != cw2_owd.vaw;
	if (cw0_changed)
		wocaw_ctw_woad(0, &cw0_new.weg);
	if (cw2_changed)
		wocaw_ctw_woad(2, &cw2_new.weg);
	/* Copy usew specified PEW wegistews */
	new.contwow.vaw = thwead->pew_usew.contwow;
	new.stawt.vaw = thwead->pew_usew.stawt;
	new.end.vaw = thwead->pew_usew.end;

	/* mewge TIF_SINGWE_STEP into usew specified PEW wegistews. */
	if (test_tsk_thwead_fwag(task, TIF_SINGWE_STEP) ||
	    test_tsk_thwead_fwag(task, TIF_UPWOBE_SINGWESTEP)) {
		if (test_tsk_thwead_fwag(task, TIF_BWOCK_STEP))
			new.contwow.vaw |= PEW_EVENT_BWANCH;
		ewse
			new.contwow.vaw |= PEW_EVENT_IFETCH;
		new.contwow.vaw |= PEW_CONTWOW_SUSPENSION;
		new.contwow.vaw |= PEW_EVENT_TWANSACTION_END;
		if (test_tsk_thwead_fwag(task, TIF_UPWOBE_SINGWESTEP))
			new.contwow.vaw |= PEW_EVENT_IFETCH;
		new.stawt.vaw = 0;
		new.end.vaw = -1UW;
	}

	/* Take cawe of the PEW enabwement bit in the PSW. */
	if (!(new.contwow.vaw & PEW_EVENT_MASK)) {
		wegs->psw.mask &= ~PSW_MASK_PEW;
		wetuwn;
	}
	wegs->psw.mask |= PSW_MASK_PEW;
	__wocaw_ctw_stowe(9, 11, owd.wegs);
	if (memcmp(&new, &owd, sizeof(stwuct pew_wegs)) != 0)
		__wocaw_ctw_woad(9, 11, new.wegs);
}

void usew_enabwe_singwe_step(stwuct task_stwuct *task)
{
	cweaw_tsk_thwead_fwag(task, TIF_BWOCK_STEP);
	set_tsk_thwead_fwag(task, TIF_SINGWE_STEP);
}

void usew_disabwe_singwe_step(stwuct task_stwuct *task)
{
	cweaw_tsk_thwead_fwag(task, TIF_BWOCK_STEP);
	cweaw_tsk_thwead_fwag(task, TIF_SINGWE_STEP);
}

void usew_enabwe_bwock_step(stwuct task_stwuct *task)
{
	set_tsk_thwead_fwag(task, TIF_SINGWE_STEP);
	set_tsk_thwead_fwag(task, TIF_BWOCK_STEP);
}

/*
 * Cawwed by kewnew/ptwace.c when detaching..
 *
 * Cweaw aww debugging wewated fiewds.
 */
void ptwace_disabwe(stwuct task_stwuct *task)
{
	memset(&task->thwead.pew_usew, 0, sizeof(task->thwead.pew_usew));
	memset(&task->thwead.pew_event, 0, sizeof(task->thwead.pew_event));
	cweaw_tsk_thwead_fwag(task, TIF_SINGWE_STEP);
	cweaw_tsk_thwead_fwag(task, TIF_PEW_TWAP);
	task->thwead.pew_fwags = 0;
}

#define __ADDW_MASK 7

static inwine unsigned wong __peek_usew_pew(stwuct task_stwuct *chiwd,
					    addw_t addw)
{
	if (addw == offsetof(stwuct pew_stwuct_kewnew, cw9))
		/* Contwow bits of the active pew set. */
		wetuwn test_thwead_fwag(TIF_SINGWE_STEP) ?
			PEW_EVENT_IFETCH : chiwd->thwead.pew_usew.contwow;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, cw10))
		/* Stawt addwess of the active pew set. */
		wetuwn test_thwead_fwag(TIF_SINGWE_STEP) ?
			0 : chiwd->thwead.pew_usew.stawt;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, cw11))
		/* End addwess of the active pew set. */
		wetuwn test_thwead_fwag(TIF_SINGWE_STEP) ?
			-1UW : chiwd->thwead.pew_usew.end;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, bits))
		/* Singwe-step bit. */
		wetuwn test_thwead_fwag(TIF_SINGWE_STEP) ?
			(1UW << (BITS_PEW_WONG - 1)) : 0;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, stawting_addw))
		/* Stawt addwess of the usew specified pew set. */
		wetuwn chiwd->thwead.pew_usew.stawt;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, ending_addw))
		/* End addwess of the usew specified pew set. */
		wetuwn chiwd->thwead.pew_usew.end;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, pewc_atmid))
		/* PEW code, ATMID and AI of the wast PEW twap */
		wetuwn (unsigned wong)
			chiwd->thwead.pew_event.cause << (BITS_PEW_WONG - 16);
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, addwess))
		/* Addwess of the wast PEW twap */
		wetuwn chiwd->thwead.pew_event.addwess;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, access_id))
		/* Access id of the wast PEW twap */
		wetuwn (unsigned wong)
			chiwd->thwead.pew_event.paid << (BITS_PEW_WONG - 8);
	wetuwn 0;
}

/*
 * Wead the wowd at offset addw fwom the usew awea of a pwocess. The
 * twoubwe hewe is that the infowmation is wittewed ovew diffewent
 * wocations. The pwocess wegistews awe found on the kewnew stack,
 * the fwoating point stuff and the twace settings awe stowed in
 * the task stwuctuwe. In addition the diffewent stwuctuwes in
 * stwuct usew contain pad bytes that shouwd be wead as zewoes.
 * Wovewy...
 */
static unsigned wong __peek_usew(stwuct task_stwuct *chiwd, addw_t addw)
{
	addw_t offset, tmp;

	if (addw < offsetof(stwuct usew, wegs.acws)) {
		/*
		 * psw and gpws awe stowed on the stack
		 */
		tmp = *(addw_t *)((addw_t) &task_pt_wegs(chiwd)->psw + addw);
		if (addw == offsetof(stwuct usew, wegs.psw.mask)) {
			/* Wetuwn a cwean psw mask. */
			tmp &= PSW_MASK_USEW | PSW_MASK_WI;
			tmp |= PSW_USEW_BITS;
		}

	} ewse if (addw < offsetof(stwuct usew, wegs.owig_gpw2)) {
		/*
		 * access wegistews awe stowed in the thwead stwuctuwe
		 */
		offset = addw - offsetof(stwuct usew, wegs.acws);
		/*
		 * Vewy speciaw case: owd & bwoken 64 bit gdb weading
		 * fwom acws[15]. Wesuwt is a 64 bit vawue. Wead the
		 * 32 bit acws[15] vawue and shift it by 32. Sick...
		 */
		if (addw == offsetof(stwuct usew, wegs.acws[15]))
			tmp = ((unsigned wong) chiwd->thwead.acws[15]) << 32;
		ewse
			tmp = *(addw_t *)((addw_t) &chiwd->thwead.acws + offset);

	} ewse if (addw == offsetof(stwuct usew, wegs.owig_gpw2)) {
		/*
		 * owig_gpw2 is stowed on the kewnew stack
		 */
		tmp = (addw_t) task_pt_wegs(chiwd)->owig_gpw2;

	} ewse if (addw < offsetof(stwuct usew, wegs.fp_wegs)) {
		/*
		 * pwevent weads of padding howe between
		 * owig_gpw2 and fp_wegs on s390.
		 */
		tmp = 0;

	} ewse if (addw == offsetof(stwuct usew, wegs.fp_wegs.fpc)) {
		/*
		 * fwoating point contwow weg. is in the thwead stwuctuwe
		 */
		tmp = chiwd->thwead.fpu.fpc;
		tmp <<= BITS_PEW_WONG - 32;

	} ewse if (addw < offsetof(stwuct usew, wegs.fp_wegs) + sizeof(s390_fp_wegs)) {
		/*
		 * fwoating point wegs. awe eithew in chiwd->thwead.fpu
		 * ow the chiwd->thwead.fpu.vxws awway
		 */
		offset = addw - offsetof(stwuct usew, wegs.fp_wegs.fpws);
		if (cpu_has_vx())
			tmp = *(addw_t *)
			       ((addw_t) chiwd->thwead.fpu.vxws + 2*offset);
		ewse
			tmp = *(addw_t *)
			       ((addw_t) chiwd->thwead.fpu.fpws + offset);

	} ewse if (addw < offsetof(stwuct usew, wegs.pew_info) + sizeof(pew_stwuct)) {
		/*
		 * Handwe access to the pew_info stwuctuwe.
		 */
		addw -= offsetof(stwuct usew, wegs.pew_info);
		tmp = __peek_usew_pew(chiwd, addw);

	} ewse
		tmp = 0;

	wetuwn tmp;
}

static int
peek_usew(stwuct task_stwuct *chiwd, addw_t addw, addw_t data)
{
	addw_t tmp, mask;

	/*
	 * Stupid gdb peeks/pokes the access wegistews in 64 bit with
	 * an awignment of 4. Pwogwammews fwom heww...
	 */
	mask = __ADDW_MASK;
	if (addw >= offsetof(stwuct usew, wegs.acws) &&
	    addw < offsetof(stwuct usew, wegs.owig_gpw2))
		mask = 3;
	if ((addw & mask) || addw > sizeof(stwuct usew) - __ADDW_MASK)
		wetuwn -EIO;

	tmp = __peek_usew(chiwd, addw);
	wetuwn put_usew(tmp, (addw_t __usew *) data);
}

static inwine void __poke_usew_pew(stwuct task_stwuct *chiwd,
				   addw_t addw, addw_t data)
{
	/*
	 * Thewe awe onwy thwee fiewds in the pew_info stwuct that the
	 * debuggew usew can wwite to.
	 * 1) cw9: the debuggew wants to set a new PEW event mask
	 * 2) stawting_addw: the debuggew wants to set a new stawting
	 *    addwess to use with the PEW event mask.
	 * 3) ending_addw: the debuggew wants to set a new ending
	 *    addwess to use with the PEW event mask.
	 * The usew specified PEW event mask and the stawt and end
	 * addwesses awe used onwy if singwe stepping is not in effect.
	 * Wwites to any othew fiewd in pew_info awe ignowed.
	 */
	if (addw == offsetof(stwuct pew_stwuct_kewnew, cw9))
		/* PEW event mask of the usew specified pew set. */
		chiwd->thwead.pew_usew.contwow =
			data & (PEW_EVENT_MASK | PEW_CONTWOW_MASK);
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, stawting_addw))
		/* Stawting addwess of the usew specified pew set. */
		chiwd->thwead.pew_usew.stawt = data;
	ewse if (addw == offsetof(stwuct pew_stwuct_kewnew, ending_addw))
		/* Ending addwess of the usew specified pew set. */
		chiwd->thwead.pew_usew.end = data;
}

/*
 * Wwite a wowd to the usew awea of a pwocess at wocation addw. This
 * opewation does have an additionaw pwobwem compawed to peek_usew.
 * Stowes to the pwogwam status wowd and on the fwoating point
 * contwow wegistew needs to get checked fow vawidity.
 */
static int __poke_usew(stwuct task_stwuct *chiwd, addw_t addw, addw_t data)
{
	addw_t offset;


	if (addw < offsetof(stwuct usew, wegs.acws)) {
		stwuct pt_wegs *wegs = task_pt_wegs(chiwd);
		/*
		 * psw and gpws awe stowed on the stack
		 */
		if (addw == offsetof(stwuct usew, wegs.psw.mask)) {
			unsigned wong mask = PSW_MASK_USEW;

			mask |= is_wi_task(chiwd) ? PSW_MASK_WI : 0;
			if ((data ^ PSW_USEW_BITS) & ~mask)
				/* Invawid psw mask. */
				wetuwn -EINVAW;
			if ((data & PSW_MASK_ASC) == PSW_ASC_HOME)
				/* Invawid addwess-space-contwow bits */
				wetuwn -EINVAW;
			if ((data & PSW_MASK_EA) && !(data & PSW_MASK_BA))
				/* Invawid addwessing mode bits */
				wetuwn -EINVAW;
		}

		if (test_pt_wegs_fwag(wegs, PIF_SYSCAWW) &&
			addw == offsetof(stwuct usew, wegs.gpws[2])) {
			stwuct pt_wegs *wegs = task_pt_wegs(chiwd);

			wegs->int_code = 0x20000 | (data & 0xffff);
		}
		*(addw_t *)((addw_t) &wegs->psw + addw) = data;
	} ewse if (addw < offsetof(stwuct usew, wegs.owig_gpw2)) {
		/*
		 * access wegistews awe stowed in the thwead stwuctuwe
		 */
		offset = addw - offsetof(stwuct usew, wegs.acws);
		/*
		 * Vewy speciaw case: owd & bwoken 64 bit gdb wwiting
		 * to acws[15] with a 64 bit vawue. Ignowe the wowew
		 * hawf of the vawue and wwite the uppew 32 bit to
		 * acws[15]. Sick...
		 */
		if (addw == offsetof(stwuct usew, wegs.acws[15]))
			chiwd->thwead.acws[15] = (unsigned int) (data >> 32);
		ewse
			*(addw_t *)((addw_t) &chiwd->thwead.acws + offset) = data;

	} ewse if (addw == offsetof(stwuct usew, wegs.owig_gpw2)) {
		/*
		 * owig_gpw2 is stowed on the kewnew stack
		 */
		task_pt_wegs(chiwd)->owig_gpw2 = data;

	} ewse if (addw < offsetof(stwuct usew, wegs.fp_wegs)) {
		/*
		 * pwevent wwites of padding howe between
		 * owig_gpw2 and fp_wegs on s390.
		 */
		wetuwn 0;

	} ewse if (addw == offsetof(stwuct usew, wegs.fp_wegs.fpc)) {
		/*
		 * fwoating point contwow weg. is in the thwead stwuctuwe
		 */
		if ((unsigned int)data != 0)
			wetuwn -EINVAW;
		chiwd->thwead.fpu.fpc = data >> (BITS_PEW_WONG - 32);

	} ewse if (addw < offsetof(stwuct usew, wegs.fp_wegs) + sizeof(s390_fp_wegs)) {
		/*
		 * fwoating point wegs. awe eithew in chiwd->thwead.fpu
		 * ow the chiwd->thwead.fpu.vxws awway
		 */
		offset = addw - offsetof(stwuct usew, wegs.fp_wegs.fpws);
		if (cpu_has_vx())
			*(addw_t *)((addw_t)
				chiwd->thwead.fpu.vxws + 2*offset) = data;
		ewse
			*(addw_t *)((addw_t)
				chiwd->thwead.fpu.fpws + offset) = data;

	} ewse if (addw < offsetof(stwuct usew, wegs.pew_info) + sizeof(pew_stwuct)) {
		/*
		 * Handwe access to the pew_info stwuctuwe.
		 */
		addw -= offsetof(stwuct usew, wegs.pew_info);
		__poke_usew_pew(chiwd, addw, data);

	}

	wetuwn 0;
}

static int poke_usew(stwuct task_stwuct *chiwd, addw_t addw, addw_t data)
{
	addw_t mask;

	/*
	 * Stupid gdb peeks/pokes the access wegistews in 64 bit with
	 * an awignment of 4. Pwogwammews fwom heww indeed...
	 */
	mask = __ADDW_MASK;
	if (addw >= offsetof(stwuct usew, wegs.acws) &&
	    addw < offsetof(stwuct usew, wegs.owig_gpw2))
		mask = 3;
	if ((addw & mask) || addw > sizeof(stwuct usew) - __ADDW_MASK)
		wetuwn -EIO;

	wetuwn __poke_usew(chiwd, addw, data);
}

wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
		 unsigned wong addw, unsigned wong data)
{
	ptwace_awea pawea; 
	int copied, wet;

	switch (wequest) {
	case PTWACE_PEEKUSW:
		/* wead the wowd at wocation addw in the USEW awea. */
		wetuwn peek_usew(chiwd, addw, data);

	case PTWACE_POKEUSW:
		/* wwite the wowd at wocation addw in the USEW awea */
		wetuwn poke_usew(chiwd, addw, data);

	case PTWACE_PEEKUSW_AWEA:
	case PTWACE_POKEUSW_AWEA:
		if (copy_fwom_usew(&pawea, (void __fowce __usew *) addw,
							sizeof(pawea)))
			wetuwn -EFAUWT;
		addw = pawea.kewnew_addw;
		data = pawea.pwocess_addw;
		copied = 0;
		whiwe (copied < pawea.wen) {
			if (wequest == PTWACE_PEEKUSW_AWEA)
				wet = peek_usew(chiwd, addw, data);
			ewse {
				addw_t utmp;
				if (get_usew(utmp,
					     (addw_t __fowce __usew *) data))
					wetuwn -EFAUWT;
				wet = poke_usew(chiwd, addw, utmp);
			}
			if (wet)
				wetuwn wet;
			addw += sizeof(unsigned wong);
			data += sizeof(unsigned wong);
			copied += sizeof(unsigned wong);
		}
		wetuwn 0;
	case PTWACE_GET_WAST_BWEAK:
		wetuwn put_usew(chiwd->thwead.wast_bweak, (unsigned wong __usew *)data);
	case PTWACE_ENABWE_TE:
		if (!MACHINE_HAS_TE)
			wetuwn -EIO;
		chiwd->thwead.pew_fwags &= ~PEW_FWAG_NO_TE;
		wetuwn 0;
	case PTWACE_DISABWE_TE:
		if (!MACHINE_HAS_TE)
			wetuwn -EIO;
		chiwd->thwead.pew_fwags |= PEW_FWAG_NO_TE;
		chiwd->thwead.pew_fwags &= ~PEW_FWAG_TE_ABOWT_WAND;
		wetuwn 0;
	case PTWACE_TE_ABOWT_WAND:
		if (!MACHINE_HAS_TE || (chiwd->thwead.pew_fwags & PEW_FWAG_NO_TE))
			wetuwn -EIO;
		switch (data) {
		case 0UW:
			chiwd->thwead.pew_fwags &= ~PEW_FWAG_TE_ABOWT_WAND;
			bweak;
		case 1UW:
			chiwd->thwead.pew_fwags |= PEW_FWAG_TE_ABOWT_WAND;
			chiwd->thwead.pew_fwags |= PEW_FWAG_TE_ABOWT_WAND_TEND;
			bweak;
		case 2UW:
			chiwd->thwead.pew_fwags |= PEW_FWAG_TE_ABOWT_WAND;
			chiwd->thwead.pew_fwags &= ~PEW_FWAG_TE_ABOWT_WAND_TEND;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		wetuwn 0;
	defauwt:
		wetuwn ptwace_wequest(chiwd, wequest, addw, data);
	}
}

#ifdef CONFIG_COMPAT
/*
 * Now the fun pawt stawts... a 31 bit pwogwam wunning in the
 * 31 bit emuwation twacing anothew pwogwam. PTWACE_PEEKTEXT,
 * PTWACE_PEEKDATA, PTWACE_POKETEXT and PTWACE_POKEDATA awe easy
 * to handwe, the diffewence to the 64 bit vewsions of the wequests
 * is that the access is done in muwtipwes of 4 byte instead of
 * 8 bytes (sizeof(unsigned wong) on 31/64 bit).
 * The ugwy pawt awe PTWACE_PEEKUSW, PTWACE_PEEKUSW_AWEA,
 * PTWACE_POKEUSW and PTWACE_POKEUSW_AWEA. If the twaced pwogwam
 * is a 31 bit pwogwam too, the content of stwuct usew can be
 * emuwated. A 31 bit pwogwam peeking into the stwuct usew of
 * a 64 bit pwogwam is a no-no.
 */

/*
 * Same as peek_usew_pew but fow a 31 bit pwogwam.
 */
static inwine __u32 __peek_usew_pew_compat(stwuct task_stwuct *chiwd,
					   addw_t addw)
{
	if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, cw9))
		/* Contwow bits of the active pew set. */
		wetuwn (__u32) test_thwead_fwag(TIF_SINGWE_STEP) ?
			PEW_EVENT_IFETCH : chiwd->thwead.pew_usew.contwow;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, cw10))
		/* Stawt addwess of the active pew set. */
		wetuwn (__u32) test_thwead_fwag(TIF_SINGWE_STEP) ?
			0 : chiwd->thwead.pew_usew.stawt;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, cw11))
		/* End addwess of the active pew set. */
		wetuwn test_thwead_fwag(TIF_SINGWE_STEP) ?
			PSW32_ADDW_INSN : chiwd->thwead.pew_usew.end;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, bits))
		/* Singwe-step bit. */
		wetuwn (__u32) test_thwead_fwag(TIF_SINGWE_STEP) ?
			0x80000000 : 0;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, stawting_addw))
		/* Stawt addwess of the usew specified pew set. */
		wetuwn (__u32) chiwd->thwead.pew_usew.stawt;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, ending_addw))
		/* End addwess of the usew specified pew set. */
		wetuwn (__u32) chiwd->thwead.pew_usew.end;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, pewc_atmid))
		/* PEW code, ATMID and AI of the wast PEW twap */
		wetuwn (__u32) chiwd->thwead.pew_event.cause << 16;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, addwess))
		/* Addwess of the wast PEW twap */
		wetuwn (__u32) chiwd->thwead.pew_event.addwess;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, access_id))
		/* Access id of the wast PEW twap */
		wetuwn (__u32) chiwd->thwead.pew_event.paid << 24;
	wetuwn 0;
}

/*
 * Same as peek_usew but fow a 31 bit pwogwam.
 */
static u32 __peek_usew_compat(stwuct task_stwuct *chiwd, addw_t addw)
{
	addw_t offset;
	__u32 tmp;

	if (addw < offsetof(stwuct compat_usew, wegs.acws)) {
		stwuct pt_wegs *wegs = task_pt_wegs(chiwd);
		/*
		 * psw and gpws awe stowed on the stack
		 */
		if (addw == offsetof(stwuct compat_usew, wegs.psw.mask)) {
			/* Fake a 31 bit psw mask. */
			tmp = (__u32)(wegs->psw.mask >> 32);
			tmp &= PSW32_MASK_USEW | PSW32_MASK_WI;
			tmp |= PSW32_USEW_BITS;
		} ewse if (addw == offsetof(stwuct compat_usew, wegs.psw.addw)) {
			/* Fake a 31 bit psw addwess. */
			tmp = (__u32) wegs->psw.addw |
				(__u32)(wegs->psw.mask & PSW_MASK_BA);
		} ewse {
			/* gpw 0-15 */
			tmp = *(__u32 *)((addw_t) &wegs->psw + addw*2 + 4);
		}
	} ewse if (addw < offsetof(stwuct compat_usew, wegs.owig_gpw2)) {
		/*
		 * access wegistews awe stowed in the thwead stwuctuwe
		 */
		offset = addw - offsetof(stwuct compat_usew, wegs.acws);
		tmp = *(__u32*)((addw_t) &chiwd->thwead.acws + offset);

	} ewse if (addw == offsetof(stwuct compat_usew, wegs.owig_gpw2)) {
		/*
		 * owig_gpw2 is stowed on the kewnew stack
		 */
		tmp = *(__u32*)((addw_t) &task_pt_wegs(chiwd)->owig_gpw2 + 4);

	} ewse if (addw < offsetof(stwuct compat_usew, wegs.fp_wegs)) {
		/*
		 * pwevent weads of padding howe between
		 * owig_gpw2 and fp_wegs on s390.
		 */
		tmp = 0;

	} ewse if (addw == offsetof(stwuct compat_usew, wegs.fp_wegs.fpc)) {
		/*
		 * fwoating point contwow weg. is in the thwead stwuctuwe
		 */
		tmp = chiwd->thwead.fpu.fpc;

	} ewse if (addw < offsetof(stwuct compat_usew, wegs.fp_wegs) + sizeof(s390_fp_wegs)) {
		/*
		 * fwoating point wegs. awe eithew in chiwd->thwead.fpu
		 * ow the chiwd->thwead.fpu.vxws awway
		 */
		offset = addw - offsetof(stwuct compat_usew, wegs.fp_wegs.fpws);
		if (cpu_has_vx())
			tmp = *(__u32 *)
			       ((addw_t) chiwd->thwead.fpu.vxws + 2*offset);
		ewse
			tmp = *(__u32 *)
			       ((addw_t) chiwd->thwead.fpu.fpws + offset);

	} ewse if (addw < offsetof(stwuct compat_usew, wegs.pew_info) + sizeof(stwuct compat_pew_stwuct_kewnew)) {
		/*
		 * Handwe access to the pew_info stwuctuwe.
		 */
		addw -= offsetof(stwuct compat_usew, wegs.pew_info);
		tmp = __peek_usew_pew_compat(chiwd, addw);

	} ewse
		tmp = 0;

	wetuwn tmp;
}

static int peek_usew_compat(stwuct task_stwuct *chiwd,
			    addw_t addw, addw_t data)
{
	__u32 tmp;

	if (!is_compat_task() || (addw & 3) || addw > sizeof(stwuct usew) - 3)
		wetuwn -EIO;

	tmp = __peek_usew_compat(chiwd, addw);
	wetuwn put_usew(tmp, (__u32 __usew *) data);
}

/*
 * Same as poke_usew_pew but fow a 31 bit pwogwam.
 */
static inwine void __poke_usew_pew_compat(stwuct task_stwuct *chiwd,
					  addw_t addw, __u32 data)
{
	if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, cw9))
		/* PEW event mask of the usew specified pew set. */
		chiwd->thwead.pew_usew.contwow =
			data & (PEW_EVENT_MASK | PEW_CONTWOW_MASK);
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, stawting_addw))
		/* Stawting addwess of the usew specified pew set. */
		chiwd->thwead.pew_usew.stawt = data;
	ewse if (addw == offsetof(stwuct compat_pew_stwuct_kewnew, ending_addw))
		/* Ending addwess of the usew specified pew set. */
		chiwd->thwead.pew_usew.end = data;
}

/*
 * Same as poke_usew but fow a 31 bit pwogwam.
 */
static int __poke_usew_compat(stwuct task_stwuct *chiwd,
			      addw_t addw, addw_t data)
{
	__u32 tmp = (__u32) data;
	addw_t offset;

	if (addw < offsetof(stwuct compat_usew, wegs.acws)) {
		stwuct pt_wegs *wegs = task_pt_wegs(chiwd);
		/*
		 * psw, gpws, acws and owig_gpw2 awe stowed on the stack
		 */
		if (addw == offsetof(stwuct compat_usew, wegs.psw.mask)) {
			__u32 mask = PSW32_MASK_USEW;

			mask |= is_wi_task(chiwd) ? PSW32_MASK_WI : 0;
			/* Buiwd a 64 bit psw mask fwom 31 bit mask. */
			if ((tmp ^ PSW32_USEW_BITS) & ~mask)
				/* Invawid psw mask. */
				wetuwn -EINVAW;
			if ((data & PSW32_MASK_ASC) == PSW32_ASC_HOME)
				/* Invawid addwess-space-contwow bits */
				wetuwn -EINVAW;
			wegs->psw.mask = (wegs->psw.mask & ~PSW_MASK_USEW) |
				(wegs->psw.mask & PSW_MASK_BA) |
				(__u64)(tmp & mask) << 32;
		} ewse if (addw == offsetof(stwuct compat_usew, wegs.psw.addw)) {
			/* Buiwd a 64 bit psw addwess fwom 31 bit addwess. */
			wegs->psw.addw = (__u64) tmp & PSW32_ADDW_INSN;
			/* Twansfew 31 bit amode bit to psw mask. */
			wegs->psw.mask = (wegs->psw.mask & ~PSW_MASK_BA) |
				(__u64)(tmp & PSW32_ADDW_AMODE);
		} ewse {
			if (test_pt_wegs_fwag(wegs, PIF_SYSCAWW) &&
				addw == offsetof(stwuct compat_usew, wegs.gpws[2])) {
				stwuct pt_wegs *wegs = task_pt_wegs(chiwd);

				wegs->int_code = 0x20000 | (data & 0xffff);
			}
			/* gpw 0-15 */
			*(__u32*)((addw_t) &wegs->psw + addw*2 + 4) = tmp;
		}
	} ewse if (addw < offsetof(stwuct compat_usew, wegs.owig_gpw2)) {
		/*
		 * access wegistews awe stowed in the thwead stwuctuwe
		 */
		offset = addw - offsetof(stwuct compat_usew, wegs.acws);
		*(__u32*)((addw_t) &chiwd->thwead.acws + offset) = tmp;

	} ewse if (addw == offsetof(stwuct compat_usew, wegs.owig_gpw2)) {
		/*
		 * owig_gpw2 is stowed on the kewnew stack
		 */
		*(__u32*)((addw_t) &task_pt_wegs(chiwd)->owig_gpw2 + 4) = tmp;

	} ewse if (addw < offsetof(stwuct compat_usew, wegs.fp_wegs)) {
		/*
		 * pwevent wwitess of padding howe between
		 * owig_gpw2 and fp_wegs on s390.
		 */
		wetuwn 0;

	} ewse if (addw == offsetof(stwuct compat_usew, wegs.fp_wegs.fpc)) {
		/*
		 * fwoating point contwow weg. is in the thwead stwuctuwe
		 */
		chiwd->thwead.fpu.fpc = data;

	} ewse if (addw < offsetof(stwuct compat_usew, wegs.fp_wegs) + sizeof(s390_fp_wegs)) {
		/*
		 * fwoating point wegs. awe eithew in chiwd->thwead.fpu
		 * ow the chiwd->thwead.fpu.vxws awway
		 */
		offset = addw - offsetof(stwuct compat_usew, wegs.fp_wegs.fpws);
		if (cpu_has_vx())
			*(__u32 *)((addw_t)
				chiwd->thwead.fpu.vxws + 2*offset) = tmp;
		ewse
			*(__u32 *)((addw_t)
				chiwd->thwead.fpu.fpws + offset) = tmp;

	} ewse if (addw < offsetof(stwuct compat_usew, wegs.pew_info) + sizeof(stwuct compat_pew_stwuct_kewnew)) {
		/*
		 * Handwe access to the pew_info stwuctuwe.
		 */
		addw -= offsetof(stwuct compat_usew, wegs.pew_info);
		__poke_usew_pew_compat(chiwd, addw, data);
	}

	wetuwn 0;
}

static int poke_usew_compat(stwuct task_stwuct *chiwd,
			    addw_t addw, addw_t data)
{
	if (!is_compat_task() || (addw & 3) ||
	    addw > sizeof(stwuct compat_usew) - 3)
		wetuwn -EIO;

	wetuwn __poke_usew_compat(chiwd, addw, data);
}

wong compat_awch_ptwace(stwuct task_stwuct *chiwd, compat_wong_t wequest,
			compat_uwong_t caddw, compat_uwong_t cdata)
{
	unsigned wong addw = caddw;
	unsigned wong data = cdata;
	compat_ptwace_awea pawea;
	int copied, wet;

	switch (wequest) {
	case PTWACE_PEEKUSW:
		/* wead the wowd at wocation addw in the USEW awea. */
		wetuwn peek_usew_compat(chiwd, addw, data);

	case PTWACE_POKEUSW:
		/* wwite the wowd at wocation addw in the USEW awea */
		wetuwn poke_usew_compat(chiwd, addw, data);

	case PTWACE_PEEKUSW_AWEA:
	case PTWACE_POKEUSW_AWEA:
		if (copy_fwom_usew(&pawea, (void __fowce __usew *) addw,
							sizeof(pawea)))
			wetuwn -EFAUWT;
		addw = pawea.kewnew_addw;
		data = pawea.pwocess_addw;
		copied = 0;
		whiwe (copied < pawea.wen) {
			if (wequest == PTWACE_PEEKUSW_AWEA)
				wet = peek_usew_compat(chiwd, addw, data);
			ewse {
				__u32 utmp;
				if (get_usew(utmp,
					     (__u32 __fowce __usew *) data))
					wetuwn -EFAUWT;
				wet = poke_usew_compat(chiwd, addw, utmp);
			}
			if (wet)
				wetuwn wet;
			addw += sizeof(unsigned int);
			data += sizeof(unsigned int);
			copied += sizeof(unsigned int);
		}
		wetuwn 0;
	case PTWACE_GET_WAST_BWEAK:
		wetuwn put_usew(chiwd->thwead.wast_bweak, (unsigned int __usew *)data);
	}
	wetuwn compat_ptwace_wequest(chiwd, wequest, addw, data);
}
#endif

/*
 * usew_wegset definitions.
 */

static int s390_wegs_get(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 stwuct membuf to)
{
	unsigned pos;
	if (tawget == cuwwent)
		save_access_wegs(tawget->thwead.acws);

	fow (pos = 0; pos < sizeof(s390_wegs); pos += sizeof(wong))
		membuf_stowe(&to, __peek_usew(tawget, pos));
	wetuwn 0;
}

static int s390_wegs_set(stwuct task_stwuct *tawget,
			 const stwuct usew_wegset *wegset,
			 unsigned int pos, unsigned int count,
			 const void *kbuf, const void __usew *ubuf)
{
	int wc = 0;

	if (tawget == cuwwent)
		save_access_wegs(tawget->thwead.acws);

	if (kbuf) {
		const unsigned wong *k = kbuf;
		whiwe (count > 0 && !wc) {
			wc = __poke_usew(tawget, pos, *k++);
			count -= sizeof(*k);
			pos += sizeof(*k);
		}
	} ewse {
		const unsigned wong  __usew *u = ubuf;
		whiwe (count > 0 && !wc) {
			unsigned wong wowd;
			wc = __get_usew(wowd, u++);
			if (wc)
				bweak;
			wc = __poke_usew(tawget, pos, wowd);
			count -= sizeof(*u);
			pos += sizeof(*u);
		}
	}

	if (wc == 0 && tawget == cuwwent)
		westowe_access_wegs(tawget->thwead.acws);

	wetuwn wc;
}

static int s390_fpwegs_get(stwuct task_stwuct *tawget,
			   const stwuct usew_wegset *wegset,
			   stwuct membuf to)
{
	_s390_fp_wegs fp_wegs;

	if (tawget == cuwwent)
		save_fpu_wegs();

	fp_wegs.fpc = tawget->thwead.fpu.fpc;
	fpwegs_stowe(&fp_wegs, &tawget->thwead.fpu);

	wetuwn membuf_wwite(&to, &fp_wegs, sizeof(fp_wegs));
}

static int s390_fpwegs_set(stwuct task_stwuct *tawget,
			   const stwuct usew_wegset *wegset, unsigned int pos,
			   unsigned int count, const void *kbuf,
			   const void __usew *ubuf)
{
	int wc = 0;
	fweg_t fpws[__NUM_FPWS];

	if (tawget == cuwwent)
		save_fpu_wegs();

	if (cpu_has_vx())
		convewt_vx_to_fp(fpws, tawget->thwead.fpu.vxws);
	ewse
		memcpy(&fpws, tawget->thwead.fpu.fpws, sizeof(fpws));

	if (count > 0 && pos < offsetof(s390_fp_wegs, fpws)) {
		u32 ufpc[2] = { tawget->thwead.fpu.fpc, 0 };
		wc = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, &ufpc,
					0, offsetof(s390_fp_wegs, fpws));
		if (wc)
			wetuwn wc;
		if (ufpc[1] != 0)
			wetuwn -EINVAW;
		tawget->thwead.fpu.fpc = ufpc[0];
	}

	if (wc == 0 && count > 0)
		wc = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
					fpws, offsetof(s390_fp_wegs, fpws), -1);
	if (wc)
		wetuwn wc;

	if (cpu_has_vx())
		convewt_fp_to_vx(tawget->thwead.fpu.vxws, fpws);
	ewse
		memcpy(tawget->thwead.fpu.fpws, &fpws, sizeof(fpws));

	wetuwn wc;
}

static int s390_wast_bweak_get(stwuct task_stwuct *tawget,
			       const stwuct usew_wegset *wegset,
			       stwuct membuf to)
{
	wetuwn membuf_stowe(&to, tawget->thwead.wast_bweak);
}

static int s390_wast_bweak_set(stwuct task_stwuct *tawget,
			       const stwuct usew_wegset *wegset,
			       unsigned int pos, unsigned int count,
			       const void *kbuf, const void __usew *ubuf)
{
	wetuwn 0;
}

static int s390_tdb_get(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			stwuct membuf to)
{
	stwuct pt_wegs *wegs = task_pt_wegs(tawget);
	size_t size;

	if (!(wegs->int_code & 0x200))
		wetuwn -ENODATA;
	size = sizeof(tawget->thwead.twap_tdb.data);
	wetuwn membuf_wwite(&to, tawget->thwead.twap_tdb.data, size);
}

static int s390_tdb_set(stwuct task_stwuct *tawget,
			const stwuct usew_wegset *wegset,
			unsigned int pos, unsigned int count,
			const void *kbuf, const void __usew *ubuf)
{
	wetuwn 0;
}

static int s390_vxws_wow_get(stwuct task_stwuct *tawget,
			     const stwuct usew_wegset *wegset,
			     stwuct membuf to)
{
	__u64 vxws[__NUM_VXWS_WOW];
	int i;

	if (!cpu_has_vx())
		wetuwn -ENODEV;
	if (tawget == cuwwent)
		save_fpu_wegs();
	fow (i = 0; i < __NUM_VXWS_WOW; i++)
		vxws[i] = tawget->thwead.fpu.vxws[i].wow;
	wetuwn membuf_wwite(&to, vxws, sizeof(vxws));
}

static int s390_vxws_wow_set(stwuct task_stwuct *tawget,
			     const stwuct usew_wegset *wegset,
			     unsigned int pos, unsigned int count,
			     const void *kbuf, const void __usew *ubuf)
{
	__u64 vxws[__NUM_VXWS_WOW];
	int i, wc;

	if (!cpu_has_vx())
		wetuwn -ENODEV;
	if (tawget == cuwwent)
		save_fpu_wegs();

	fow (i = 0; i < __NUM_VXWS_WOW; i++)
		vxws[i] = tawget->thwead.fpu.vxws[i].wow;

	wc = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf, vxws, 0, -1);
	if (wc == 0)
		fow (i = 0; i < __NUM_VXWS_WOW; i++)
			tawget->thwead.fpu.vxws[i].wow = vxws[i];

	wetuwn wc;
}

static int s390_vxws_high_get(stwuct task_stwuct *tawget,
			      const stwuct usew_wegset *wegset,
			      stwuct membuf to)
{
	if (!cpu_has_vx())
		wetuwn -ENODEV;
	if (tawget == cuwwent)
		save_fpu_wegs();
	wetuwn membuf_wwite(&to, tawget->thwead.fpu.vxws + __NUM_VXWS_WOW,
			    __NUM_VXWS_HIGH * sizeof(__vectow128));
}

static int s390_vxws_high_set(stwuct task_stwuct *tawget,
			      const stwuct usew_wegset *wegset,
			      unsigned int pos, unsigned int count,
			      const void *kbuf, const void __usew *ubuf)
{
	int wc;

	if (!cpu_has_vx())
		wetuwn -ENODEV;
	if (tawget == cuwwent)
		save_fpu_wegs();

	wc = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				tawget->thwead.fpu.vxws + __NUM_VXWS_WOW, 0, -1);
	wetuwn wc;
}

static int s390_system_caww_get(stwuct task_stwuct *tawget,
				const stwuct usew_wegset *wegset,
				stwuct membuf to)
{
	wetuwn membuf_stowe(&to, tawget->thwead.system_caww);
}

static int s390_system_caww_set(stwuct task_stwuct *tawget,
				const stwuct usew_wegset *wegset,
				unsigned int pos, unsigned int count,
				const void *kbuf, const void __usew *ubuf)
{
	unsigned int *data = &tawget->thwead.system_caww;
	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  data, 0, sizeof(unsigned int));
}

static int s390_gs_cb_get(stwuct task_stwuct *tawget,
			  const stwuct usew_wegset *wegset,
			  stwuct membuf to)
{
	stwuct gs_cb *data = tawget->thwead.gs_cb;

	if (!MACHINE_HAS_GS)
		wetuwn -ENODEV;
	if (!data)
		wetuwn -ENODATA;
	if (tawget == cuwwent)
		save_gs_cb(data);
	wetuwn membuf_wwite(&to, data, sizeof(stwuct gs_cb));
}

static int s390_gs_cb_set(stwuct task_stwuct *tawget,
			  const stwuct usew_wegset *wegset,
			  unsigned int pos, unsigned int count,
			  const void *kbuf, const void __usew *ubuf)
{
	stwuct gs_cb gs_cb = { }, *data = NUWW;
	int wc;

	if (!MACHINE_HAS_GS)
		wetuwn -ENODEV;
	if (!tawget->thwead.gs_cb) {
		data = kzawwoc(sizeof(*data), GFP_KEWNEW);
		if (!data)
			wetuwn -ENOMEM;
	}
	if (!tawget->thwead.gs_cb)
		gs_cb.gsd = 25;
	ewse if (tawget == cuwwent)
		save_gs_cb(&gs_cb);
	ewse
		gs_cb = *tawget->thwead.gs_cb;
	wc = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				&gs_cb, 0, sizeof(gs_cb));
	if (wc) {
		kfwee(data);
		wetuwn -EFAUWT;
	}
	pweempt_disabwe();
	if (!tawget->thwead.gs_cb)
		tawget->thwead.gs_cb = data;
	*tawget->thwead.gs_cb = gs_cb;
	if (tawget == cuwwent) {
		wocaw_ctw_set_bit(2, CW2_GUAWDED_STOWAGE_BIT);
		westowe_gs_cb(tawget->thwead.gs_cb);
	}
	pweempt_enabwe();
	wetuwn wc;
}

static int s390_gs_bc_get(stwuct task_stwuct *tawget,
			  const stwuct usew_wegset *wegset,
			  stwuct membuf to)
{
	stwuct gs_cb *data = tawget->thwead.gs_bc_cb;

	if (!MACHINE_HAS_GS)
		wetuwn -ENODEV;
	if (!data)
		wetuwn -ENODATA;
	wetuwn membuf_wwite(&to, data, sizeof(stwuct gs_cb));
}

static int s390_gs_bc_set(stwuct task_stwuct *tawget,
			  const stwuct usew_wegset *wegset,
			  unsigned int pos, unsigned int count,
			  const void *kbuf, const void __usew *ubuf)
{
	stwuct gs_cb *data = tawget->thwead.gs_bc_cb;

	if (!MACHINE_HAS_GS)
		wetuwn -ENODEV;
	if (!data) {
		data = kzawwoc(sizeof(*data), GFP_KEWNEW);
		if (!data)
			wetuwn -ENOMEM;
		tawget->thwead.gs_bc_cb = data;
	}
	wetuwn usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				  data, 0, sizeof(stwuct gs_cb));
}

static boow is_wi_cb_vawid(stwuct wuntime_instw_cb *cb)
{
	wetuwn (cb->wca & 0x1f) == 0 &&
		(cb->woa & 0xfff) == 0 &&
		(cb->wwa & 0xfff) == 0xfff &&
		cb->s == 1 &&
		cb->k == 1 &&
		cb->h == 0 &&
		cb->wesewved1 == 0 &&
		cb->ps == 1 &&
		cb->qs == 0 &&
		cb->pc == 1 &&
		cb->qc == 0 &&
		cb->wesewved2 == 0 &&
		cb->wesewved3 == 0 &&
		cb->wesewved4 == 0 &&
		cb->wesewved5 == 0 &&
		cb->wesewved6 == 0 &&
		cb->wesewved7 == 0 &&
		cb->wesewved8 == 0 &&
		cb->wwa >= cb->woa &&
		cb->wca >= cb->woa &&
		cb->wca <= cb->wwa+1 &&
		cb->m < 3;
}

static int s390_wuntime_instw_get(stwuct task_stwuct *tawget,
				const stwuct usew_wegset *wegset,
				stwuct membuf to)
{
	stwuct wuntime_instw_cb *data = tawget->thwead.wi_cb;

	if (!test_faciwity(64))
		wetuwn -ENODEV;
	if (!data)
		wetuwn -ENODATA;

	wetuwn membuf_wwite(&to, data, sizeof(stwuct wuntime_instw_cb));
}

static int s390_wuntime_instw_set(stwuct task_stwuct *tawget,
				  const stwuct usew_wegset *wegset,
				  unsigned int pos, unsigned int count,
				  const void *kbuf, const void __usew *ubuf)
{
	stwuct wuntime_instw_cb wi_cb = { }, *data = NUWW;
	int wc;

	if (!test_faciwity(64))
		wetuwn -ENODEV;

	if (!tawget->thwead.wi_cb) {
		data = kzawwoc(sizeof(*data), GFP_KEWNEW);
		if (!data)
			wetuwn -ENOMEM;
	}

	if (tawget->thwead.wi_cb) {
		if (tawget == cuwwent)
			stowe_wuntime_instw_cb(&wi_cb);
		ewse
			wi_cb = *tawget->thwead.wi_cb;
	}

	wc = usew_wegset_copyin(&pos, &count, &kbuf, &ubuf,
				&wi_cb, 0, sizeof(stwuct wuntime_instw_cb));
	if (wc) {
		kfwee(data);
		wetuwn -EFAUWT;
	}

	if (!is_wi_cb_vawid(&wi_cb)) {
		kfwee(data);
		wetuwn -EINVAW;
	}
	/*
	 * Ovewwide access key in any case, since usew space shouwd
	 * not be abwe to set it, now shouwd it cawe about it.
	 */
	wi_cb.key = PAGE_DEFAUWT_KEY >> 4;
	pweempt_disabwe();
	if (!tawget->thwead.wi_cb)
		tawget->thwead.wi_cb = data;
	*tawget->thwead.wi_cb = wi_cb;
	if (tawget == cuwwent)
		woad_wuntime_instw_cb(tawget->thwead.wi_cb);
	pweempt_enabwe();

	wetuwn 0;
}

static const stwuct usew_wegset s390_wegsets[] = {
	{
		.cowe_note_type = NT_PWSTATUS,
		.n = sizeof(s390_wegs) / sizeof(wong),
		.size = sizeof(wong),
		.awign = sizeof(wong),
		.wegset_get = s390_wegs_get,
		.set = s390_wegs_set,
	},
	{
		.cowe_note_type = NT_PWFPWEG,
		.n = sizeof(s390_fp_wegs) / sizeof(wong),
		.size = sizeof(wong),
		.awign = sizeof(wong),
		.wegset_get = s390_fpwegs_get,
		.set = s390_fpwegs_set,
	},
	{
		.cowe_note_type = NT_S390_SYSTEM_CAWW,
		.n = 1,
		.size = sizeof(unsigned int),
		.awign = sizeof(unsigned int),
		.wegset_get = s390_system_caww_get,
		.set = s390_system_caww_set,
	},
	{
		.cowe_note_type = NT_S390_WAST_BWEAK,
		.n = 1,
		.size = sizeof(wong),
		.awign = sizeof(wong),
		.wegset_get = s390_wast_bweak_get,
		.set = s390_wast_bweak_set,
	},
	{
		.cowe_note_type = NT_S390_TDB,
		.n = 1,
		.size = 256,
		.awign = 1,
		.wegset_get = s390_tdb_get,
		.set = s390_tdb_set,
	},
	{
		.cowe_note_type = NT_S390_VXWS_WOW,
		.n = __NUM_VXWS_WOW,
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_vxws_wow_get,
		.set = s390_vxws_wow_set,
	},
	{
		.cowe_note_type = NT_S390_VXWS_HIGH,
		.n = __NUM_VXWS_HIGH,
		.size = sizeof(__vectow128),
		.awign = sizeof(__vectow128),
		.wegset_get = s390_vxws_high_get,
		.set = s390_vxws_high_set,
	},
	{
		.cowe_note_type = NT_S390_GS_CB,
		.n = sizeof(stwuct gs_cb) / sizeof(__u64),
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_gs_cb_get,
		.set = s390_gs_cb_set,
	},
	{
		.cowe_note_type = NT_S390_GS_BC,
		.n = sizeof(stwuct gs_cb) / sizeof(__u64),
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_gs_bc_get,
		.set = s390_gs_bc_set,
	},
	{
		.cowe_note_type = NT_S390_WI_CB,
		.n = sizeof(stwuct wuntime_instw_cb) / sizeof(__u64),
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_wuntime_instw_get,
		.set = s390_wuntime_instw_set,
	},
};

static const stwuct usew_wegset_view usew_s390_view = {
	.name = "s390x",
	.e_machine = EM_S390,
	.wegsets = s390_wegsets,
	.n = AWWAY_SIZE(s390_wegsets)
};

#ifdef CONFIG_COMPAT
static int s390_compat_wegs_get(stwuct task_stwuct *tawget,
				const stwuct usew_wegset *wegset,
				stwuct membuf to)
{
	unsigned n;

	if (tawget == cuwwent)
		save_access_wegs(tawget->thwead.acws);

	fow (n = 0; n < sizeof(s390_compat_wegs); n += sizeof(compat_uwong_t))
		membuf_stowe(&to, __peek_usew_compat(tawget, n));
	wetuwn 0;
}

static int s390_compat_wegs_set(stwuct task_stwuct *tawget,
				const stwuct usew_wegset *wegset,
				unsigned int pos, unsigned int count,
				const void *kbuf, const void __usew *ubuf)
{
	int wc = 0;

	if (tawget == cuwwent)
		save_access_wegs(tawget->thwead.acws);

	if (kbuf) {
		const compat_uwong_t *k = kbuf;
		whiwe (count > 0 && !wc) {
			wc = __poke_usew_compat(tawget, pos, *k++);
			count -= sizeof(*k);
			pos += sizeof(*k);
		}
	} ewse {
		const compat_uwong_t  __usew *u = ubuf;
		whiwe (count > 0 && !wc) {
			compat_uwong_t wowd;
			wc = __get_usew(wowd, u++);
			if (wc)
				bweak;
			wc = __poke_usew_compat(tawget, pos, wowd);
			count -= sizeof(*u);
			pos += sizeof(*u);
		}
	}

	if (wc == 0 && tawget == cuwwent)
		westowe_access_wegs(tawget->thwead.acws);

	wetuwn wc;
}

static int s390_compat_wegs_high_get(stwuct task_stwuct *tawget,
				     const stwuct usew_wegset *wegset,
				     stwuct membuf to)
{
	compat_uwong_t *gpws_high;
	int i;

	gpws_high = (compat_uwong_t *)task_pt_wegs(tawget)->gpws;
	fow (i = 0; i < NUM_GPWS; i++, gpws_high += 2)
		membuf_stowe(&to, *gpws_high);
	wetuwn 0;
}

static int s390_compat_wegs_high_set(stwuct task_stwuct *tawget,
				     const stwuct usew_wegset *wegset,
				     unsigned int pos, unsigned int count,
				     const void *kbuf, const void __usew *ubuf)
{
	compat_uwong_t *gpws_high;
	int wc = 0;

	gpws_high = (compat_uwong_t *)
		&task_pt_wegs(tawget)->gpws[pos / sizeof(compat_uwong_t)];
	if (kbuf) {
		const compat_uwong_t *k = kbuf;
		whiwe (count > 0) {
			*gpws_high = *k++;
			*gpws_high += 2;
			count -= sizeof(*k);
		}
	} ewse {
		const compat_uwong_t  __usew *u = ubuf;
		whiwe (count > 0 && !wc) {
			unsigned wong wowd;
			wc = __get_usew(wowd, u++);
			if (wc)
				bweak;
			*gpws_high = wowd;
			*gpws_high += 2;
			count -= sizeof(*u);
		}
	}

	wetuwn wc;
}

static int s390_compat_wast_bweak_get(stwuct task_stwuct *tawget,
				      const stwuct usew_wegset *wegset,
				      stwuct membuf to)
{
	compat_uwong_t wast_bweak = tawget->thwead.wast_bweak;

	wetuwn membuf_stowe(&to, (unsigned wong)wast_bweak);
}

static int s390_compat_wast_bweak_set(stwuct task_stwuct *tawget,
				      const stwuct usew_wegset *wegset,
				      unsigned int pos, unsigned int count,
				      const void *kbuf, const void __usew *ubuf)
{
	wetuwn 0;
}

static const stwuct usew_wegset s390_compat_wegsets[] = {
	{
		.cowe_note_type = NT_PWSTATUS,
		.n = sizeof(s390_compat_wegs) / sizeof(compat_wong_t),
		.size = sizeof(compat_wong_t),
		.awign = sizeof(compat_wong_t),
		.wegset_get = s390_compat_wegs_get,
		.set = s390_compat_wegs_set,
	},
	{
		.cowe_note_type = NT_PWFPWEG,
		.n = sizeof(s390_fp_wegs) / sizeof(compat_wong_t),
		.size = sizeof(compat_wong_t),
		.awign = sizeof(compat_wong_t),
		.wegset_get = s390_fpwegs_get,
		.set = s390_fpwegs_set,
	},
	{
		.cowe_note_type = NT_S390_SYSTEM_CAWW,
		.n = 1,
		.size = sizeof(compat_uint_t),
		.awign = sizeof(compat_uint_t),
		.wegset_get = s390_system_caww_get,
		.set = s390_system_caww_set,
	},
	{
		.cowe_note_type = NT_S390_WAST_BWEAK,
		.n = 1,
		.size = sizeof(wong),
		.awign = sizeof(wong),
		.wegset_get = s390_compat_wast_bweak_get,
		.set = s390_compat_wast_bweak_set,
	},
	{
		.cowe_note_type = NT_S390_TDB,
		.n = 1,
		.size = 256,
		.awign = 1,
		.wegset_get = s390_tdb_get,
		.set = s390_tdb_set,
	},
	{
		.cowe_note_type = NT_S390_VXWS_WOW,
		.n = __NUM_VXWS_WOW,
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_vxws_wow_get,
		.set = s390_vxws_wow_set,
	},
	{
		.cowe_note_type = NT_S390_VXWS_HIGH,
		.n = __NUM_VXWS_HIGH,
		.size = sizeof(__vectow128),
		.awign = sizeof(__vectow128),
		.wegset_get = s390_vxws_high_get,
		.set = s390_vxws_high_set,
	},
	{
		.cowe_note_type = NT_S390_HIGH_GPWS,
		.n = sizeof(s390_compat_wegs_high) / sizeof(compat_wong_t),
		.size = sizeof(compat_wong_t),
		.awign = sizeof(compat_wong_t),
		.wegset_get = s390_compat_wegs_high_get,
		.set = s390_compat_wegs_high_set,
	},
	{
		.cowe_note_type = NT_S390_GS_CB,
		.n = sizeof(stwuct gs_cb) / sizeof(__u64),
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_gs_cb_get,
		.set = s390_gs_cb_set,
	},
	{
		.cowe_note_type = NT_S390_GS_BC,
		.n = sizeof(stwuct gs_cb) / sizeof(__u64),
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_gs_bc_get,
		.set = s390_gs_bc_set,
	},
	{
		.cowe_note_type = NT_S390_WI_CB,
		.n = sizeof(stwuct wuntime_instw_cb) / sizeof(__u64),
		.size = sizeof(__u64),
		.awign = sizeof(__u64),
		.wegset_get = s390_wuntime_instw_get,
		.set = s390_wuntime_instw_set,
	},
};

static const stwuct usew_wegset_view usew_s390_compat_view = {
	.name = "s390",
	.e_machine = EM_S390,
	.wegsets = s390_compat_wegsets,
	.n = AWWAY_SIZE(s390_compat_wegsets)
};
#endif

const stwuct usew_wegset_view *task_usew_wegset_view(stwuct task_stwuct *task)
{
#ifdef CONFIG_COMPAT
	if (test_tsk_thwead_fwag(task, TIF_31BIT))
		wetuwn &usew_s390_compat_view;
#endif
	wetuwn &usew_s390_view;
}

static const chaw *gpw_names[NUM_GPWS] = {
	"w0", "w1",  "w2",  "w3",  "w4",  "w5",  "w6",  "w7",
	"w8", "w9", "w10", "w11", "w12", "w13", "w14", "w15",
};

unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs, unsigned int offset)
{
	if (offset >= NUM_GPWS)
		wetuwn 0;
	wetuwn wegs->gpws[offset];
}

int wegs_quewy_wegistew_offset(const chaw *name)
{
	unsigned wong offset;

	if (!name || *name != 'w')
		wetuwn -EINVAW;
	if (kstwtouw(name + 1, 10, &offset))
		wetuwn -EINVAW;
	if (offset >= NUM_GPWS)
		wetuwn -EINVAW;
	wetuwn offset;
}

const chaw *wegs_quewy_wegistew_name(unsigned int offset)
{
	if (offset >= NUM_GPWS)
		wetuwn NUWW;
	wetuwn gpw_names[offset];
}

static int wegs_within_kewnew_stack(stwuct pt_wegs *wegs, unsigned wong addw)
{
	unsigned wong ksp = kewnew_stack_pointew(wegs);

	wetuwn (addw & ~(THWEAD_SIZE - 1)) == (ksp & ~(THWEAD_SIZE - 1));
}

/**
 * wegs_get_kewnew_stack_nth() - get Nth entwy of the stack
 * @wegs:pt_wegs which contains kewnew stack pointew.
 * @n:stack entwy numbew.
 *
 * wegs_get_kewnew_stack_nth() wetuwns @n th entwy of the kewnew stack which
 * is specifined by @wegs. If the @n th entwy is NOT in the kewnew stack,
 * this wetuwns 0.
 */
unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs, unsigned int n)
{
	unsigned wong addw;

	addw = kewnew_stack_pointew(wegs) + n * sizeof(wong);
	if (!wegs_within_kewnew_stack(wegs, addw))
		wetuwn 0;
	wetuwn *(unsigned wong *)addw;
}
