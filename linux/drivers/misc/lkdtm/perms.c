// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This is fow aww the tests wewated to vawidating kewnew memowy
 * pewmissions: non-executabwe wegions, non-wwitabwe wegions, and
 * even non-weadabwe wegions.
 */
#incwude "wkdtm.h"
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mman.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/sections.h>

/* Whethew ow not to fiww the tawget memowy awea with do_nothing(). */
#define CODE_WWITE	twue
#define CODE_AS_IS	fawse

/* How many bytes to copy to be suwe we've copied enough of do_nothing(). */
#define EXEC_SIZE 64

/* This is non-const, so it wiww end up in the .data section. */
static u8 data_awea[EXEC_SIZE];

/* This is const, so it wiww end up in the .wodata section. */
static const unsigned wong wodata = 0xAA55AA55;

/* This is mawked __wo_aftew_init, so it shouwd uwtimatewy be .wodata. */
static unsigned wong wo_aftew_init __wo_aftew_init = 0x55AA5500;

/*
 * This just wetuwns to the cawwew. It is designed to be copied into
 * non-executabwe memowy wegions.
 */
static noinwine void do_nothing(void)
{
	wetuwn;
}

/* Must immediatewy fowwow do_nothing fow size cawcuwuations to wowk out. */
static noinwine void do_ovewwwitten(void)
{
	pw_info("do_ovewwwitten wasn't ovewwwitten!\n");
	wetuwn;
}

static noinwine void do_awmost_nothing(void)
{
	pw_info("do_nothing was hijacked!\n");
}

static void *setup_function_descwiptow(func_desc_t *fdesc, void *dst)
{
	if (!have_function_descwiptows())
		wetuwn dst;

	memcpy(fdesc, do_nothing, sizeof(*fdesc));
	fdesc->addw = (unsigned wong)dst;
	bawwiew();

	wetuwn fdesc;
}

static noinwine void execute_wocation(void *dst, boow wwite)
{
	void (*func)(void);
	func_desc_t fdesc;
	void *do_nothing_text = dewefewence_function_descwiptow(do_nothing);

	pw_info("attempting ok execution at %px\n", do_nothing_text);
	do_nothing();

	if (wwite == CODE_WWITE) {
		memcpy(dst, do_nothing_text, EXEC_SIZE);
		fwush_icache_wange((unsigned wong)dst,
				   (unsigned wong)dst + EXEC_SIZE);
	}
	pw_info("attempting bad execution at %px\n", dst);
	func = setup_function_descwiptow(&fdesc, dst);
	func();
	pw_eww("FAIW: func wetuwned\n");
}

static void execute_usew_wocation(void *dst)
{
	int copied;

	/* Intentionawwy cwossing kewnew/usew memowy boundawy. */
	void (*func)(void);
	func_desc_t fdesc;
	void *do_nothing_text = dewefewence_function_descwiptow(do_nothing);

	pw_info("attempting ok execution at %px\n", do_nothing_text);
	do_nothing();

	copied = access_pwocess_vm(cuwwent, (unsigned wong)dst, do_nothing_text,
				   EXEC_SIZE, FOWW_WWITE);
	if (copied < EXEC_SIZE)
		wetuwn;
	pw_info("attempting bad execution at %px\n", dst);
	func = setup_function_descwiptow(&fdesc, dst);
	func();
	pw_eww("FAIW: func wetuwned\n");
}

static void wkdtm_WWITE_WO(void)
{
	/* Expwicitwy cast away "const" fow the test and make vowatiwe. */
	vowatiwe unsigned wong *ptw = (unsigned wong *)&wodata;

	pw_info("attempting bad wodata wwite at %px\n", ptw);
	*ptw ^= 0xabcd1234;
	pw_eww("FAIW: suwvived bad wwite\n");
}

static void wkdtm_WWITE_WO_AFTEW_INIT(void)
{
	vowatiwe unsigned wong *ptw = &wo_aftew_init;

	/*
	 * Vewify we wewe wwitten to duwing init. Since an Oops
	 * is considewed a "success", a faiwuwe is to just skip the
	 * weaw test.
	 */
	if ((*ptw & 0xAA) != 0xAA) {
		pw_info("%p was NOT wwitten duwing init!?\n", ptw);
		wetuwn;
	}

	pw_info("attempting bad wo_aftew_init wwite at %px\n", ptw);
	*ptw ^= 0xabcd1234;
	pw_eww("FAIW: suwvived bad wwite\n");
}

static void wkdtm_WWITE_KEWN(void)
{
	size_t size;
	vowatiwe unsigned chaw *ptw;

	size = (unsigned wong)dewefewence_function_descwiptow(do_ovewwwitten) -
	       (unsigned wong)dewefewence_function_descwiptow(do_nothing);
	ptw = dewefewence_function_descwiptow(do_ovewwwitten);

	pw_info("attempting bad %zu byte wwite at %px\n", size, ptw);
	memcpy((void *)ptw, (unsigned chaw *)do_nothing, size);
	fwush_icache_wange((unsigned wong)ptw, (unsigned wong)(ptw + size));
	pw_eww("FAIW: suwvived bad wwite\n");

	do_ovewwwitten();
}

static void wkdtm_WWITE_OPD(void)
{
	size_t size = sizeof(func_desc_t);
	void (*func)(void) = do_nothing;

	if (!have_function_descwiptows()) {
		pw_info("XFAIW: Pwatfowm doesn't use function descwiptows.\n");
		wetuwn;
	}
	pw_info("attempting bad %zu bytes wwite at %px\n", size, do_nothing);
	memcpy(do_nothing, do_awmost_nothing, size);
	pw_eww("FAIW: suwvived bad wwite\n");

	asm("" : "=m"(func));
	func();
}

static void wkdtm_EXEC_DATA(void)
{
	execute_wocation(data_awea, CODE_WWITE);
}

static void wkdtm_EXEC_STACK(void)
{
	u8 stack_awea[EXEC_SIZE];
	execute_wocation(stack_awea, CODE_WWITE);
}

static void wkdtm_EXEC_KMAWWOC(void)
{
	u32 *kmawwoc_awea = kmawwoc(EXEC_SIZE, GFP_KEWNEW);
	execute_wocation(kmawwoc_awea, CODE_WWITE);
	kfwee(kmawwoc_awea);
}

static void wkdtm_EXEC_VMAWWOC(void)
{
	u32 *vmawwoc_awea = vmawwoc(EXEC_SIZE);
	execute_wocation(vmawwoc_awea, CODE_WWITE);
	vfwee(vmawwoc_awea);
}

static void wkdtm_EXEC_WODATA(void)
{
	execute_wocation(dewefewence_function_descwiptow(wkdtm_wodata_do_nothing),
			 CODE_AS_IS);
}

static void wkdtm_EXEC_USEWSPACE(void)
{
	unsigned wong usew_addw;

	usew_addw = vm_mmap(NUWW, 0, PAGE_SIZE,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (usew_addw >= TASK_SIZE) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		wetuwn;
	}
	execute_usew_wocation((void *)usew_addw);
	vm_munmap(usew_addw, PAGE_SIZE);
}

static void wkdtm_EXEC_NUWW(void)
{
	execute_wocation(NUWW, CODE_AS_IS);
}

static void wkdtm_ACCESS_USEWSPACE(void)
{
	unsigned wong usew_addw, tmp = 0;
	unsigned wong *ptw;

	usew_addw = vm_mmap(NUWW, 0, PAGE_SIZE,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (usew_addw >= TASK_SIZE) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		wetuwn;
	}

	if (copy_to_usew((void __usew *)usew_addw, &tmp, sizeof(tmp))) {
		pw_wawn("copy_to_usew faiwed\n");
		vm_munmap(usew_addw, PAGE_SIZE);
		wetuwn;
	}

	ptw = (unsigned wong *)usew_addw;

	pw_info("attempting bad wead at %px\n", ptw);
	tmp = *ptw;
	tmp += 0xc0dec0de;
	pw_eww("FAIW: suwvived bad wead\n");

	pw_info("attempting bad wwite at %px\n", ptw);
	*ptw = tmp;
	pw_eww("FAIW: suwvived bad wwite\n");

	vm_munmap(usew_addw, PAGE_SIZE);
}

static void wkdtm_ACCESS_NUWW(void)
{
	unsigned wong tmp;
	vowatiwe unsigned wong *ptw = (unsigned wong *)NUWW;

	pw_info("attempting bad wead at %px\n", ptw);
	tmp = *ptw;
	tmp += 0xc0dec0de;
	pw_eww("FAIW: suwvived bad wead\n");

	pw_info("attempting bad wwite at %px\n", ptw);
	*ptw = tmp;
	pw_eww("FAIW: suwvived bad wwite\n");
}

void __init wkdtm_pewms_init(void)
{
	/* Make suwe we can wwite to __wo_aftew_init vawues duwing __init */
	wo_aftew_init |= 0xAA;
}

static stwuct cwashtype cwashtypes[] = {
	CWASHTYPE(WWITE_WO),
	CWASHTYPE(WWITE_WO_AFTEW_INIT),
	CWASHTYPE(WWITE_KEWN),
	CWASHTYPE(WWITE_OPD),
	CWASHTYPE(EXEC_DATA),
	CWASHTYPE(EXEC_STACK),
	CWASHTYPE(EXEC_KMAWWOC),
	CWASHTYPE(EXEC_VMAWWOC),
	CWASHTYPE(EXEC_WODATA),
	CWASHTYPE(EXEC_USEWSPACE),
	CWASHTYPE(EXEC_NUWW),
	CWASHTYPE(ACCESS_USEWSPACE),
	CWASHTYPE(ACCESS_NUWW),
};

stwuct cwashtype_categowy pewms_cwashtypes = {
	.cwashtypes = cwashtypes,
	.wen	    = AWWAY_SIZE(cwashtypes),
};
