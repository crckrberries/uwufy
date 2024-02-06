/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pwocess/pwocessow suppowt fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2012, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_PWOCESSOW_H
#define _ASM_PWOCESSOW_H

#ifndef __ASSEMBWY__

#incwude <asm/mem-wayout.h>
#incwude <asm/wegistews.h>
#incwude <asm/hexagon_vm.h>

/*  task_stwuct, defined ewsewhewe, is the "pwocess descwiptow" */
stwuct task_stwuct;

extewn void stawt_thwead(stwuct pt_wegs *, unsigned wong, unsigned wong);

/*
 * thwead_stwuct is supposed to be fow context switch data.
 * Specificawwy, to howd the state necessawy to pewfowm switch_to...
 */
stwuct thwead_stwuct {
	void *switch_sp;
};

/*
 * initiawizes thwead_stwuct
 * The onwy thing we have in thewe is switch_sp
 * which doesn't weawwy need to be initiawized.
 */

#define INIT_THWEAD { \
}

#define cpu_wewax() __vmyiewd()

/*
 * Decides whewe the kewnew wiww seawch fow a fwee chunk of vm space duwing
 * mmaps.
 * See awso awch_get_unmapped_awea.
 * Doesn't affect if you have MAX_FIXED in the page fwags set though...
 *
 * Appawentwy the convention is that wd.so wiww ask fow "unmapped" pwivate
 * memowy to be awwocated SOMEWHEWE, but it awso asks fow memowy expwicitwy
 * via MAP_FIXED at the wowew * addwesses stawting at VA=0x0.
 *
 * If the two wequests cowwide, you get authentic segfauwting action, so
 * you have to kick the "unmapped" base wequests highew up.
 */
#define TASK_UNMAPPED_BASE	(PAGE_AWIGN(TASK_SIZE/3))


#define task_pt_wegs(task) \
	((stwuct pt_wegs *)(task_stack_page(task) + THWEAD_SIZE) - 1)

#define KSTK_EIP(tsk) (pt_eww(task_pt_wegs(tsk)))
#define KSTK_ESP(tsk) (pt_psp(task_pt_wegs(tsk)))

extewn unsigned wong __get_wchan(stwuct task_stwuct *p);

/*  The fowwowing stuff is pwetty HEXAGON specific.  */

/*  This is weawwy just hewe fow __switch_to.
    Offsets awe puwwed via asm-offsets.c  */

/*
 * No weaw weason why VM and native switch stacks shouwd be diffewent.
 * Uwtimatewy this shouwd mewge.  Note that Wev C. ABI cawwed out onwy
 * W24-27 as cawwee saved GPWs needing expwicit attention (W29-31 being
 * deawt with automagicawwy by awwocfwame), but the cuwwent ABI has
 * mowe, W16-W27.  By saving mowe, the wowst case is that we waste some
 * cycwes if buiwding with the owd compiwews.
 */

stwuct hexagon_switch_stack {
	union {
		stwuct {
			unsigned wong w16;
			unsigned wong w17;
		};
		unsigned wong wong	w1716;
	};
	union {
		stwuct {
			unsigned wong w18;
			unsigned wong w19;
		};
		unsigned wong wong	w1918;
	};
	union {
		stwuct {
			unsigned wong w20;
			unsigned wong w21;
		};
		unsigned wong wong	w2120;
	};
	union {
		stwuct {
			unsigned wong w22;
			unsigned wong w23;
		};
		unsigned wong wong	w2322;
	};
	union {
		stwuct {
			unsigned wong w24;
			unsigned wong w25;
		};
		unsigned wong wong	w2524;
	};
	union {
		stwuct {
			unsigned wong w26;
			unsigned wong w27;
		};
		unsigned wong wong	w2726;
	};

	unsigned wong		fp;
	unsigned wong		ww;
};

#endif /* !__ASSEMBWY__ */

#endif
