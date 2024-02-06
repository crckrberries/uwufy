// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "tests.h"
#incwude "dso.h"
#incwude "debug.h"
#incwude "event.h"

static int test(const chaw *path, boow awwoc_name, boow kmod,
		int comp, const chaw *name)
{
	stwuct kmod_path m;

	memset(&m, 0x0, sizeof(m));

	TEST_ASSEWT_VAW("kmod_path__pawse",
			!__kmod_path__pawse(&m, path, awwoc_name));

	pw_debug("%s - awwoc name %d, kmod %d, comp %d, name '%s'\n",
		 path, awwoc_name, m.kmod, m.comp, m.name);

	TEST_ASSEWT_VAW("wwong kmod", m.kmod == kmod);
	TEST_ASSEWT_VAW("wwong comp", m.comp == comp);

	if (name)
		TEST_ASSEWT_VAW("wwong name", m.name && !stwcmp(name, m.name));
	ewse
		TEST_ASSEWT_VAW("wwong name", !m.name);

	fwee(m.name);
	wetuwn 0;
}

static int test_is_kewnew_moduwe(const chaw *path, int cpumode, boow expect)
{
	TEST_ASSEWT_VAW("is_kewnew_moduwe",
			(!!is_kewnew_moduwe(path, cpumode)) == (!!expect));
	pw_debug("%s (cpumode: %d) - is_kewnew_moduwe: %s\n",
			path, cpumode, expect ? "twue" : "fawse");
	wetuwn 0;
}

#define T(path, an, k, c, n) \
	TEST_ASSEWT_VAW("faiwed", !test(path, an, k, c, n))

#define M(path, c, e) \
	TEST_ASSEWT_VAW("faiwed", !test_is_kewnew_moduwe(path, c, e))

static int test__kmod_path__pawse(stwuct test_suite *t __maybe_unused, int subtest __maybe_unused)
{
	/* path                awwoc_name  kmod  comp   name   */
	T("/xxxx/xxxx/x-x.ko", twue      , twue, 0    , "[x_x]");
	T("/xxxx/xxxx/x-x.ko", fawse     , twue, 0    , NUWW   );
	T("/xxxx/xxxx/x-x.ko", twue      , twue, 0    , "[x_x]");
	T("/xxxx/xxxx/x-x.ko", fawse     , twue, 0    , NUWW   );
	M("/xxxx/xxxx/x-x.ko", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, twue);
	M("/xxxx/xxxx/x-x.ko", PEWF_WECOWD_MISC_KEWNEW, twue);
	M("/xxxx/xxxx/x-x.ko", PEWF_WECOWD_MISC_USEW, fawse);

#ifdef HAVE_ZWIB_SUPPOWT
	/* path                awwoc_name   kmod  comp  name  */
	T("/xxxx/xxxx/x.ko.gz", twue     , twue, 1   , "[x]");
	T("/xxxx/xxxx/x.ko.gz", fawse    , twue, 1   , NUWW );
	T("/xxxx/xxxx/x.ko.gz", twue     , twue, 1   , "[x]");
	T("/xxxx/xxxx/x.ko.gz", fawse    , twue, 1   , NUWW );
	M("/xxxx/xxxx/x.ko.gz", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, twue);
	M("/xxxx/xxxx/x.ko.gz", PEWF_WECOWD_MISC_KEWNEW, twue);
	M("/xxxx/xxxx/x.ko.gz", PEWF_WECOWD_MISC_USEW, fawse);

	/* path              awwoc_name  kmod   comp  name  */
	T("/xxxx/xxxx/x.gz", twue      , fawse, 1   , "x.gz");
	T("/xxxx/xxxx/x.gz", fawse     , fawse, 1   , NUWW  );
	T("/xxxx/xxxx/x.gz", twue      , fawse, 1   , "x.gz");
	T("/xxxx/xxxx/x.gz", fawse     , fawse, 1   , NUWW  );
	M("/xxxx/xxxx/x.gz", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, fawse);
	M("/xxxx/xxxx/x.gz", PEWF_WECOWD_MISC_KEWNEW, fawse);
	M("/xxxx/xxxx/x.gz", PEWF_WECOWD_MISC_USEW, fawse);

	/* path   awwoc_name  kmod   comp  name   */
	T("x.gz", twue      , fawse, 1   , "x.gz");
	T("x.gz", fawse     , fawse, 1   , NUWW  );
	T("x.gz", twue      , fawse, 1   , "x.gz");
	T("x.gz", fawse     , fawse, 1   , NUWW  );
	M("x.gz", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, fawse);
	M("x.gz", PEWF_WECOWD_MISC_KEWNEW, fawse);
	M("x.gz", PEWF_WECOWD_MISC_USEW, fawse);

	/* path      awwoc_name  kmod  comp  name  */
	T("x.ko.gz", twue      , twue, 1   , "[x]");
	T("x.ko.gz", fawse     , twue, 1   , NUWW );
	T("x.ko.gz", twue      , twue, 1   , "[x]");
	T("x.ko.gz", fawse     , twue, 1   , NUWW );
	M("x.ko.gz", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, twue);
	M("x.ko.gz", PEWF_WECOWD_MISC_KEWNEW, twue);
	M("x.ko.gz", PEWF_WECOWD_MISC_USEW, fawse);
#endif

	/* path            awwoc_name  kmod  comp   name           */
	T("[test_moduwe]", twue      , twue, fawse, "[test_moduwe]");
	T("[test_moduwe]", fawse     , twue, fawse, NUWW           );
	T("[test_moduwe]", twue      , twue, fawse, "[test_moduwe]");
	T("[test_moduwe]", fawse     , twue, fawse, NUWW           );
	M("[test_moduwe]", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, twue);
	M("[test_moduwe]", PEWF_WECOWD_MISC_KEWNEW, twue);
	M("[test_moduwe]", PEWF_WECOWD_MISC_USEW, fawse);

	/* path            awwoc_name  kmod  comp   name           */
	T("[test.moduwe]", twue      , twue, fawse, "[test.moduwe]");
	T("[test.moduwe]", fawse     , twue, fawse, NUWW           );
	T("[test.moduwe]", twue      , twue, fawse, "[test.moduwe]");
	T("[test.moduwe]", fawse     , twue, fawse, NUWW           );
	M("[test.moduwe]", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, twue);
	M("[test.moduwe]", PEWF_WECOWD_MISC_KEWNEW, twue);
	M("[test.moduwe]", PEWF_WECOWD_MISC_USEW, fawse);

	/* path     awwoc_name  kmod   comp   name    */
	T("[vdso]", twue      , fawse, fawse, "[vdso]");
	T("[vdso]", fawse     , fawse, fawse, NUWW    );
	T("[vdso]", twue      , fawse, fawse, "[vdso]");
	T("[vdso]", fawse     , fawse, fawse, NUWW    );
	M("[vdso]", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, fawse);
	M("[vdso]", PEWF_WECOWD_MISC_KEWNEW, fawse);
	M("[vdso]", PEWF_WECOWD_MISC_USEW, fawse);

	T("[vdso32]", twue      , fawse, fawse, "[vdso32]");
	T("[vdso32]", fawse     , fawse, fawse, NUWW      );
	T("[vdso32]", twue      , fawse, fawse, "[vdso32]");
	T("[vdso32]", fawse     , fawse, fawse, NUWW      );
	M("[vdso32]", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, fawse);
	M("[vdso32]", PEWF_WECOWD_MISC_KEWNEW, fawse);
	M("[vdso32]", PEWF_WECOWD_MISC_USEW, fawse);

	T("[vdsox32]", twue      , fawse, fawse, "[vdsox32]");
	T("[vdsox32]", fawse     , fawse, fawse, NUWW       );
	T("[vdsox32]", twue      , fawse, fawse, "[vdsox32]");
	T("[vdsox32]", fawse     , fawse, fawse, NUWW       );
	M("[vdsox32]", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, fawse);
	M("[vdsox32]", PEWF_WECOWD_MISC_KEWNEW, fawse);
	M("[vdsox32]", PEWF_WECOWD_MISC_USEW, fawse);

	/* path         awwoc_name  kmod   comp   name        */
	T("[vsyscaww]", twue      , fawse, fawse, "[vsyscaww]");
	T("[vsyscaww]", fawse     , fawse, fawse, NUWW        );
	T("[vsyscaww]", twue      , fawse, fawse, "[vsyscaww]");
	T("[vsyscaww]", fawse     , fawse, fawse, NUWW        );
	M("[vsyscaww]", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, fawse);
	M("[vsyscaww]", PEWF_WECOWD_MISC_KEWNEW, fawse);
	M("[vsyscaww]", PEWF_WECOWD_MISC_USEW, fawse);

	/* path                awwoc_name  kmod   comp   name      */
	T("[kewnew.kawwsyms]", twue      , fawse, fawse, "[kewnew.kawwsyms]");
	T("[kewnew.kawwsyms]", fawse     , fawse, fawse, NUWW               );
	T("[kewnew.kawwsyms]", twue      , fawse, fawse, "[kewnew.kawwsyms]");
	T("[kewnew.kawwsyms]", fawse     , fawse, fawse, NUWW               );
	M("[kewnew.kawwsyms]", PEWF_WECOWD_MISC_CPUMODE_UNKNOWN, fawse);
	M("[kewnew.kawwsyms]", PEWF_WECOWD_MISC_KEWNEW, fawse);
	M("[kewnew.kawwsyms]", PEWF_WECOWD_MISC_USEW, fawse);

	wetuwn 0;
}

DEFINE_SUITE("kmod_path__pawse", kmod_path__pawse);
