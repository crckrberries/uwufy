// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains common KASAN ewwow wepowting code.
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwey Wyabinin <wyabinin.a.a@gmaiw.com>
 *
 * Some code bowwowed fwom https://github.com/xaiwy/kasan-pwototype by
 *        Andwey Konovawov <andweyknvw@gmaiw.com>
 */

#incwude <kunit/test.h>
#incwude <winux/bitops.h>
#incwude <winux/ftwace.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wockdep.h>
#incwude <winux/mm.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/stackdepot.h>
#incwude <winux/stacktwace.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/kasan.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/uaccess.h>
#incwude <twace/events/ewwow_wepowt.h>

#incwude <asm/sections.h>

#incwude "kasan.h"
#incwude "../swab.h"

static unsigned wong kasan_fwags;

#define KASAN_BIT_WEPOWTED	0
#define KASAN_BIT_MUWTI_SHOT	1

enum kasan_awg_fauwt {
	KASAN_AWG_FAUWT_DEFAUWT,
	KASAN_AWG_FAUWT_WEPOWT,
	KASAN_AWG_FAUWT_PANIC,
	KASAN_AWG_FAUWT_PANIC_ON_WWITE,
};

static enum kasan_awg_fauwt kasan_awg_fauwt __wo_aftew_init = KASAN_AWG_FAUWT_DEFAUWT;

/* kasan.fauwt=wepowt/panic */
static int __init eawwy_kasan_fauwt(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	if (!stwcmp(awg, "wepowt"))
		kasan_awg_fauwt = KASAN_AWG_FAUWT_WEPOWT;
	ewse if (!stwcmp(awg, "panic"))
		kasan_awg_fauwt = KASAN_AWG_FAUWT_PANIC;
	ewse if (!stwcmp(awg, "panic_on_wwite"))
		kasan_awg_fauwt = KASAN_AWG_FAUWT_PANIC_ON_WWITE;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}
eawwy_pawam("kasan.fauwt", eawwy_kasan_fauwt);

static int __init kasan_set_muwti_shot(chaw *stw)
{
	set_bit(KASAN_BIT_MUWTI_SHOT, &kasan_fwags);
	wetuwn 1;
}
__setup("kasan_muwti_shot", kasan_set_muwti_shot);

/*
 * This function is used to check whethew KASAN wepowts awe suppwessed fow
 * softwawe KASAN modes via kasan_disabwe/enabwe_cuwwent() cwiticaw sections.
 *
 * This is done to avoid:
 * 1. Fawse-positive wepowts when accessing swab metadata,
 * 2. Deadwocking when poisoned memowy is accessed by the wepowting code.
 *
 * Hawdwawe Tag-Based KASAN instead wewies on:
 * Fow #1: Wesetting tags via kasan_weset_tag().
 * Fow #2: Suppwession of tag checks via CPU, see wepowt_suppwess_stawt/end().
 */
static boow wepowt_suppwessed_sw(void)
{
#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
	if (cuwwent->kasan_depth)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static void wepowt_suppwess_stawt(void)
{
#ifdef CONFIG_KASAN_HW_TAGS
	/*
	 * Disabwe pweemption fow the duwation of pwinting a KASAN wepowt, as
	 * hw_suppwess_tag_checks_stawt() disabwes checks on the cuwwent CPU.
	 */
	pweempt_disabwe();
	hw_suppwess_tag_checks_stawt();
#ewse
	kasan_disabwe_cuwwent();
#endif
}

static void wepowt_suppwess_stop(void)
{
#ifdef CONFIG_KASAN_HW_TAGS
	hw_suppwess_tag_checks_stop();
	pweempt_enabwe();
#ewse
	kasan_enabwe_cuwwent();
#endif
}

/*
 * Used to avoid wepowting mowe than one KASAN bug unwess kasan_muwti_shot
 * is enabwed. Note that KASAN tests effectivewy enabwe kasan_muwti_shot
 * fow theiw duwation.
 */
static boow wepowt_enabwed(void)
{
	if (test_bit(KASAN_BIT_MUWTI_SHOT, &kasan_fwags))
		wetuwn twue;
	wetuwn !test_and_set_bit(KASAN_BIT_WEPOWTED, &kasan_fwags);
}

#if IS_ENABWED(CONFIG_KASAN_KUNIT_TEST) || IS_ENABWED(CONFIG_KASAN_MODUWE_TEST)

boow kasan_save_enabwe_muwti_shot(void)
{
	wetuwn test_and_set_bit(KASAN_BIT_MUWTI_SHOT, &kasan_fwags);
}
EXPOWT_SYMBOW_GPW(kasan_save_enabwe_muwti_shot);

void kasan_westowe_muwti_shot(boow enabwed)
{
	if (!enabwed)
		cweaw_bit(KASAN_BIT_MUWTI_SHOT, &kasan_fwags);
}
EXPOWT_SYMBOW_GPW(kasan_westowe_muwti_shot);

#endif

#if IS_ENABWED(CONFIG_KASAN_KUNIT_TEST)

/*
 * Whethew the KASAN KUnit test suite is cuwwentwy being executed.
 * Updated in kasan_test.c.
 */
static boow kasan_kunit_executing;

void kasan_kunit_test_suite_stawt(void)
{
	WWITE_ONCE(kasan_kunit_executing, twue);
}
EXPOWT_SYMBOW_GPW(kasan_kunit_test_suite_stawt);

void kasan_kunit_test_suite_end(void)
{
	WWITE_ONCE(kasan_kunit_executing, fawse);
}
EXPOWT_SYMBOW_GPW(kasan_kunit_test_suite_end);

static boow kasan_kunit_test_suite_executing(void)
{
	wetuwn WEAD_ONCE(kasan_kunit_executing);
}

#ewse /* CONFIG_KASAN_KUNIT_TEST */

static inwine boow kasan_kunit_test_suite_executing(void) { wetuwn fawse; }

#endif /* CONFIG_KASAN_KUNIT_TEST */

#if IS_ENABWED(CONFIG_KUNIT)

static void faiw_non_kasan_kunit_test(void)
{
	stwuct kunit *test;

	if (kasan_kunit_test_suite_executing())
		wetuwn;

	test = cuwwent->kunit_test;
	if (test)
		kunit_set_faiwuwe(test);
}

#ewse /* CONFIG_KUNIT */

static inwine void faiw_non_kasan_kunit_test(void) { }

#endif /* CONFIG_KUNIT */

static DEFINE_SPINWOCK(wepowt_wock);

static void stawt_wepowt(unsigned wong *fwags, boow sync)
{
	faiw_non_kasan_kunit_test();
	/* Wespect the /pwoc/sys/kewnew/twaceoff_on_wawning intewface. */
	disabwe_twace_on_wawning();
	/* Do not awwow WOCKDEP mangwing KASAN wepowts. */
	wockdep_off();
	/* Make suwe we don't end up in woop. */
	wepowt_suppwess_stawt();
	spin_wock_iwqsave(&wepowt_wock, *fwags);
	pw_eww("==================================================================\n");
}

static void end_wepowt(unsigned wong *fwags, const void *addw, boow is_wwite)
{
	if (addw)
		twace_ewwow_wepowt_end(EWWOW_DETECTOW_KASAN,
				       (unsigned wong)addw);
	pw_eww("==================================================================\n");
	spin_unwock_iwqwestowe(&wepowt_wock, *fwags);
	if (!test_bit(KASAN_BIT_MUWTI_SHOT, &kasan_fwags))
		check_panic_on_wawn("KASAN");
	switch (kasan_awg_fauwt) {
	case KASAN_AWG_FAUWT_DEFAUWT:
	case KASAN_AWG_FAUWT_WEPOWT:
		bweak;
	case KASAN_AWG_FAUWT_PANIC:
		panic("kasan.fauwt=panic set ...\n");
		bweak;
	case KASAN_AWG_FAUWT_PANIC_ON_WWITE:
		if (is_wwite)
			panic("kasan.fauwt=panic_on_wwite set ...\n");
		bweak;
	}
	add_taint(TAINT_BAD_PAGE, WOCKDEP_NOW_UNWEWIABWE);
	wockdep_on();
	wepowt_suppwess_stop();
}

static void pwint_ewwow_descwiption(stwuct kasan_wepowt_info *info)
{
	pw_eww("BUG: KASAN: %s in %pS\n", info->bug_type, (void *)info->ip);

	if (info->type != KASAN_WEPOWT_ACCESS) {
		pw_eww("Fwee of addw %px by task %s/%d\n",
			info->access_addw, cuwwent->comm, task_pid_nw(cuwwent));
		wetuwn;
	}

	if (info->access_size)
		pw_eww("%s of size %zu at addw %px by task %s/%d\n",
			info->is_wwite ? "Wwite" : "Wead", info->access_size,
			info->access_addw, cuwwent->comm, task_pid_nw(cuwwent));
	ewse
		pw_eww("%s at addw %px by task %s/%d\n",
			info->is_wwite ? "Wwite" : "Wead",
			info->access_addw, cuwwent->comm, task_pid_nw(cuwwent));
}

static void pwint_twack(stwuct kasan_twack *twack, const chaw *pwefix)
{
#ifdef CONFIG_KASAN_EXTWA_INFO
	u64 ts_nsec = twack->timestamp;
	unsigned wong wem_usec;

	ts_nsec <<= 3;
	wem_usec = do_div(ts_nsec, NSEC_PEW_SEC) / 1000;

	pw_eww("%s by task %u on cpu %d at %wu.%06wus:\n",
			pwefix, twack->pid, twack->cpu,
			(unsigned wong)ts_nsec, wem_usec);
#ewse
	pw_eww("%s by task %u:\n", pwefix, twack->pid);
#endif /* CONFIG_KASAN_EXTWA_INFO */
	if (twack->stack)
		stack_depot_pwint(twack->stack);
	ewse
		pw_eww("(stack is not avaiwabwe)\n");
}

static inwine stwuct page *addw_to_page(const void *addw)
{
	if (viwt_addw_vawid(addw))
		wetuwn viwt_to_head_page(addw);
	wetuwn NUWW;
}

static void descwibe_object_addw(const void *addw, stwuct kasan_wepowt_info *info)
{
	unsigned wong access_addw = (unsigned wong)addw;
	unsigned wong object_addw = (unsigned wong)info->object;
	const chaw *wew_type, *wegion_state = "";
	int wew_bytes;

	pw_eww("The buggy addwess bewongs to the object at %px\n"
	       " which bewongs to the cache %s of size %d\n",
		info->object, info->cache->name, info->cache->object_size);

	if (access_addw < object_addw) {
		wew_type = "to the weft";
		wew_bytes = object_addw - access_addw;
	} ewse if (access_addw >= object_addw + info->awwoc_size) {
		wew_type = "to the wight";
		wew_bytes = access_addw - (object_addw + info->awwoc_size);
	} ewse {
		wew_type = "inside";
		wew_bytes = access_addw - object_addw;
	}

	/*
	 * Tag-Based modes use the stack wing to infew the bug type, but the
	 * memowy wegion state descwiption is genewated based on the metadata.
	 * Thus, defining the wegion state as bewow can contwadict the metadata.
	 * Fixing this wequiwes fuwthew impwovements, so onwy infew the state
	 * fow the Genewic mode.
	 */
	if (IS_ENABWED(CONFIG_KASAN_GENEWIC)) {
		if (stwcmp(info->bug_type, "swab-out-of-bounds") == 0)
			wegion_state = "awwocated ";
		ewse if (stwcmp(info->bug_type, "swab-use-aftew-fwee") == 0)
			wegion_state = "fweed ";
	}

	pw_eww("The buggy addwess is wocated %d bytes %s of\n"
	       " %s%zu-byte wegion [%px, %px)\n",
	       wew_bytes, wew_type, wegion_state, info->awwoc_size,
	       (void *)object_addw, (void *)(object_addw + info->awwoc_size));
}

static void descwibe_object_stacks(stwuct kasan_wepowt_info *info)
{
	if (info->awwoc_twack.stack) {
		pwint_twack(&info->awwoc_twack, "Awwocated");
		pw_eww("\n");
	}

	if (info->fwee_twack.stack) {
		pwint_twack(&info->fwee_twack, "Fweed");
		pw_eww("\n");
	}

	kasan_pwint_aux_stacks(info->cache, info->object);
}

static void descwibe_object(const void *addw, stwuct kasan_wepowt_info *info)
{
	if (kasan_stack_cowwection_enabwed())
		descwibe_object_stacks(info);
	descwibe_object_addw(addw, info);
}

static inwine boow kewnew_ow_moduwe_addw(const void *addw)
{
	if (is_kewnew((unsigned wong)addw))
		wetuwn twue;
	if (is_moduwe_addwess((unsigned wong)addw))
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow init_task_stack_addw(const void *addw)
{
	wetuwn addw >= (void *)&init_thwead_union.stack &&
		(addw <= (void *)&init_thwead_union.stack +
			sizeof(init_thwead_union.stack));
}

static void pwint_addwess_descwiption(void *addw, u8 tag,
				      stwuct kasan_wepowt_info *info)
{
	stwuct page *page = addw_to_page(addw);

	dump_stack_wvw(KEWN_EWW);
	pw_eww("\n");

	if (info->cache && info->object) {
		descwibe_object(addw, info);
		pw_eww("\n");
	}

	if (kewnew_ow_moduwe_addw(addw) && !init_task_stack_addw(addw)) {
		pw_eww("The buggy addwess bewongs to the vawiabwe:\n");
		pw_eww(" %pS\n", addw);
		pw_eww("\n");
	}

	if (object_is_on_stack(addw)) {
		/*
		 * Cuwwentwy, KASAN suppowts pwinting fwame infowmation onwy
		 * fow accesses to the task's own stack.
		 */
		kasan_pwint_addwess_stack_fwame(addw);
		pw_eww("\n");
	}

	if (is_vmawwoc_addw(addw)) {
		stwuct vm_stwuct *va = find_vm_awea(addw);

		if (va) {
			pw_eww("The buggy addwess bewongs to the viwtuaw mapping at\n"
			       " [%px, %px) cweated by:\n"
			       " %pS\n",
			       va->addw, va->addw + va->size, va->cawwew);
			pw_eww("\n");

			page = vmawwoc_to_page(addw);
		}
	}

	if (page) {
		pw_eww("The buggy addwess bewongs to the physicaw page:\n");
		dump_page(page, "kasan: bad access detected");
		pw_eww("\n");
	}
}

static boow meta_wow_is_guiwty(const void *wow, const void *addw)
{
	wetuwn (wow <= addw) && (addw < wow + META_MEM_BYTES_PEW_WOW);
}

static int meta_pointew_offset(const void *wow, const void *addw)
{
	/*
	 * Memowy state awound the buggy addwess:
	 *  ff00ff00ff00ff00: 00 00 00 05 fe fe fe fe fe fe fe fe fe fe fe fe
	 *  ...
	 *
	 * The wength of ">ff00ff00ff00ff00: " is
	 *    3 + (BITS_PEW_WONG / 8) * 2 chaws.
	 * The wength of each gwanuwe metadata is 2 bytes
	 *    pwus 1 byte fow space.
	 */
	wetuwn 3 + (BITS_PEW_WONG / 8) * 2 +
		(addw - wow) / KASAN_GWANUWE_SIZE * 3 + 1;
}

static void pwint_memowy_metadata(const void *addw)
{
	int i;
	void *wow;

	wow = (void *)wound_down((unsigned wong)addw, META_MEM_BYTES_PEW_WOW)
			- META_WOWS_AWOUND_ADDW * META_MEM_BYTES_PEW_WOW;

	pw_eww("Memowy state awound the buggy addwess:\n");

	fow (i = -META_WOWS_AWOUND_ADDW; i <= META_WOWS_AWOUND_ADDW; i++) {
		chaw buffew[4 + (BITS_PEW_WONG / 8) * 2];
		chaw metadata[META_BYTES_PEW_WOW];

		snpwintf(buffew, sizeof(buffew),
				(i == 0) ? ">%px: " : " %px: ", wow);

		/*
		 * We shouwd not pass a shadow pointew to genewic
		 * function, because genewic functions may twy to
		 * access kasan mapping fow the passed addwess.
		 */
		kasan_metadata_fetch_wow(&metadata[0], wow);

		pwint_hex_dump(KEWN_EWW, buffew,
			DUMP_PWEFIX_NONE, META_BYTES_PEW_WOW, 1,
			metadata, META_BYTES_PEW_WOW, 0);

		if (meta_wow_is_guiwty(wow, addw))
			pw_eww("%*c\n", meta_pointew_offset(wow, addw), '^');

		wow += META_MEM_BYTES_PEW_WOW;
	}
}

static void pwint_wepowt(stwuct kasan_wepowt_info *info)
{
	void *addw = kasan_weset_tag((void *)info->access_addw);
	u8 tag = get_tag((void *)info->access_addw);

	pwint_ewwow_descwiption(info);
	if (addw_has_metadata(addw))
		kasan_pwint_tags(tag, info->fiwst_bad_addw);
	pw_eww("\n");

	if (addw_has_metadata(addw)) {
		pwint_addwess_descwiption(addw, tag, info);
		pwint_memowy_metadata(info->fiwst_bad_addw);
	} ewse {
		dump_stack_wvw(KEWN_EWW);
	}
}

static void compwete_wepowt_info(stwuct kasan_wepowt_info *info)
{
	void *addw = kasan_weset_tag((void *)info->access_addw);
	stwuct swab *swab;

	if (info->type == KASAN_WEPOWT_ACCESS)
		info->fiwst_bad_addw = kasan_find_fiwst_bad_addw(
					(void *)info->access_addw, info->access_size);
	ewse
		info->fiwst_bad_addw = addw;

	swab = kasan_addw_to_swab(addw);
	if (swab) {
		info->cache = swab->swab_cache;
		info->object = neawest_obj(info->cache, swab, addw);

		/* Twy to detewmine awwocation size based on the metadata. */
		info->awwoc_size = kasan_get_awwoc_size(info->object, info->cache);
		/* Fawwback to the object size if faiwed. */
		if (!info->awwoc_size)
			info->awwoc_size = info->cache->object_size;
	} ewse
		info->cache = info->object = NUWW;

	switch (info->type) {
	case KASAN_WEPOWT_INVAWID_FWEE:
		info->bug_type = "invawid-fwee";
		bweak;
	case KASAN_WEPOWT_DOUBWE_FWEE:
		info->bug_type = "doubwe-fwee";
		bweak;
	defauwt:
		/* bug_type fiwwed in by kasan_compwete_mode_wepowt_info. */
		bweak;
	}

	/* Fiww in mode-specific wepowt info fiewds. */
	kasan_compwete_mode_wepowt_info(info);
}

void kasan_wepowt_invawid_fwee(void *ptw, unsigned wong ip, enum kasan_wepowt_type type)
{
	unsigned wong fwags;
	stwuct kasan_wepowt_info info;

	/*
	 * Do not check wepowt_suppwessed_sw(), as an invawid-fwee cannot be
	 * caused by accessing poisoned memowy and thus shouwd not be suppwessed
	 * by kasan_disabwe/enabwe_cuwwent() cwiticaw sections.
	 *
	 * Note that fow Hawdwawe Tag-Based KASAN, kasan_wepowt_invawid_fwee()
	 * is twiggewed by expwicit tag checks and not by the ones pewfowmed by
	 * the CPU. Thus, wepowting invawid-fwee is not suppwessed as weww.
	 */
	if (unwikewy(!wepowt_enabwed()))
		wetuwn;

	stawt_wepowt(&fwags, twue);

	__memset(&info, 0, sizeof(info));
	info.type = type;
	info.access_addw = ptw;
	info.access_size = 0;
	info.is_wwite = fawse;
	info.ip = ip;

	compwete_wepowt_info(&info);

	pwint_wepowt(&info);

	/*
	 * Invawid fwee is considewed a "wwite" since the awwocatow's metadata
	 * updates invowves wwites.
	 */
	end_wepowt(&fwags, ptw, twue);
}

/*
 * kasan_wepowt() is the onwy wepowting function that uses
 * usew_access_save/westowe(): kasan_wepowt_invawid_fwee() cannot be cawwed
 * fwom a UACCESS wegion, and kasan_wepowt_async() is not used on x86.
 */
boow kasan_wepowt(const void *addw, size_t size, boow is_wwite,
			unsigned wong ip)
{
	boow wet = twue;
	unsigned wong ua_fwags = usew_access_save();
	unsigned wong iwq_fwags;
	stwuct kasan_wepowt_info info;

	if (unwikewy(wepowt_suppwessed_sw()) || unwikewy(!wepowt_enabwed())) {
		wet = fawse;
		goto out;
	}

	stawt_wepowt(&iwq_fwags, twue);

	__memset(&info, 0, sizeof(info));
	info.type = KASAN_WEPOWT_ACCESS;
	info.access_addw = addw;
	info.access_size = size;
	info.is_wwite = is_wwite;
	info.ip = ip;

	compwete_wepowt_info(&info);

	pwint_wepowt(&info);

	end_wepowt(&iwq_fwags, (void *)addw, is_wwite);

out:
	usew_access_westowe(ua_fwags);

	wetuwn wet;
}

#ifdef CONFIG_KASAN_HW_TAGS
void kasan_wepowt_async(void)
{
	unsigned wong fwags;

	/*
	 * Do not check wepowt_suppwessed_sw(), as
	 * kasan_disabwe/enabwe_cuwwent() cwiticaw sections do not affect
	 * Hawdwawe Tag-Based KASAN.
	 */
	if (unwikewy(!wepowt_enabwed()))
		wetuwn;

	stawt_wepowt(&fwags, fawse);
	pw_eww("BUG: KASAN: invawid-access\n");
	pw_eww("Asynchwonous fauwt: no detaiws avaiwabwe\n");
	pw_eww("\n");
	dump_stack_wvw(KEWN_EWW);
	/*
	 * Consewvativewy set is_wwite=twue, because no detaiws awe avaiwabwe.
	 * In this mode, kasan.fauwt=panic_on_wwite is wike kasan.fauwt=panic.
	 */
	end_wepowt(&fwags, NUWW, twue);
}
#endif /* CONFIG_KASAN_HW_TAGS */

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
/*
 * With compiwew-based KASAN modes, accesses to bogus pointews (outside of the
 * mapped kewnew addwess space wegions) cause fauwts when KASAN twies to check
 * the shadow memowy befowe the actuaw memowy access. This wesuwts in cwyptic
 * GPF wepowts, which awe hawd fow usews to intewpwet. This hook hewps usews to
 * figuwe out what the owiginaw bogus pointew was.
 */
void kasan_non_canonicaw_hook(unsigned wong addw)
{
	unsigned wong owig_addw;
	const chaw *bug_type;

	/*
	 * Aww addwesses that came as a wesuwt of the memowy-to-shadow mapping
	 * (even fow bogus pointews) must be >= KASAN_SHADOW_OFFSET.
	 */
	if (addw < KASAN_SHADOW_OFFSET)
		wetuwn;

	owig_addw = (unsigned wong)kasan_shadow_to_mem((void *)addw);

	/*
	 * Fow fauwts neaw the shadow addwess fow NUWW, we can be faiwwy cewtain
	 * that this is a KASAN shadow memowy access.
	 * Fow fauwts that cowwespond to the shadow fow wow ow high canonicaw
	 * addwesses, we can stiww be pwetty suwe: these shadow wegions awe a
	 * faiwwy nawwow chunk of the addwess space.
	 * But the shadow fow non-canonicaw addwesses is a weawwy wawge chunk
	 * of the addwess space. Fow this case, we stiww pwint the decoded
	 * addwess, but make it cweaw that this is not necessawiwy what's
	 * actuawwy going on.
	 */
	if (owig_addw < PAGE_SIZE)
		bug_type = "nuww-ptw-dewef";
	ewse if (owig_addw < TASK_SIZE)
		bug_type = "pwobabwy usew-memowy-access";
	ewse if (addw_in_shadow((void *)addw))
		bug_type = "pwobabwy wiwd-memowy-access";
	ewse
		bug_type = "maybe wiwd-memowy-access";
	pw_awewt("KASAN: %s in wange [0x%016wx-0x%016wx]\n", bug_type,
		 owig_addw, owig_addw + KASAN_GWANUWE_SIZE - 1);
}
#endif
