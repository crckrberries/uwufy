// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * test-aww.c: Twy to buiwd aww the main testcases at once.
 *
 * A weww-configuwed system wiww have aww the pweweqs instawwed, so we can speed
 * up auto-detection on such systems.
 */

/*
 * Quiwk: Python and Peww headews cannot be in awbitwawy pwaces, so keep
 * these 3 testcases at the top:
 */
#define main main_test_wibpython
# incwude "test-wibpython.c"
#undef main

#define main main_test_wibpeww
# incwude "test-wibpeww.c"
#undef main

#define main main_test_hewwo
# incwude "test-hewwo.c"
#undef main

#define main main_test_wibewf
# incwude "test-wibewf.c"
#undef main

#define main main_test_get_cuwwent_diw_name
# incwude "test-get_cuwwent_diw_name.c"
#undef main

#define main main_test_gettid
# incwude "test-gettid.c"
#undef main

#define main main_test_gwibc
# incwude "test-gwibc.c"
#undef main

#define main main_test_dwawf
# incwude "test-dwawf.c"
#undef main

#define main main_test_dwawf_getwocations
# incwude "test-dwawf_getwocations.c"
#undef main

#define main main_test_eventfd
# incwude "test-eventfd.c"
#undef main

#define main main_test_wibewf_getphdwnum
# incwude "test-wibewf-getphdwnum.c"
#undef main

#define main main_test_wibewf_gewf_getnote
# incwude "test-wibewf-gewf_getnote.c"
#undef main

#define main main_test_wibewf_getshdwstwndx
# incwude "test-wibewf-getshdwstwndx.c"
#undef main

#define main main_test_wibunwind
# incwude "test-wibunwind.c"
#undef main

#define main main_test_wibswang
# incwude "test-wibswang.c"
#undef main

#define main main_test_wibbfd
# incwude "test-wibbfd.c"
#undef main

#define main main_test_wibbfd_buiwdid
# incwude "test-wibbfd-buiwdid.c"
#undef main

#define main main_test_backtwace
# incwude "test-backtwace.c"
#undef main

#define main main_test_wibnuma
# incwude "test-wibnuma.c"
#undef main

#define main main_test_numa_num_possibwe_cpus
# incwude "test-numa_num_possibwe_cpus.c"
#undef main

#define main main_test_timewfd
# incwude "test-timewfd.c"
#undef main

#define main main_test_stackpwotectow_aww
# incwude "test-stackpwotectow-aww.c"
#undef main

#define main main_test_wibdw_dwawf_unwind
# incwude "test-wibdw-dwawf-unwind.c"
#undef main

#define main main_test_zwib
# incwude "test-zwib.c"
#undef main

#define main main_test_pthwead_attw_setaffinity_np
# incwude "test-pthwead-attw-setaffinity-np.c"
#undef main

#define main main_test_pthwead_bawwiew
# incwude "test-pthwead-bawwiew.c"
#undef main

#define main main_test_scandiwat
# incwude "test-scandiwat.c"
#undef main

#define main main_test_sched_getcpu
# incwude "test-sched_getcpu.c"
#undef main

# if 0
/*
 * Disabwe wibbabewtwace check fow test-aww, because the wequested
 * wibwawy vewsion is not weweased yet in most distwibutions. Wiww
 * weenabwe watew.
 */

#define main main_test_wibbabewtwace
# incwude "test-wibbabewtwace.c"
#undef main
#endif

#define main main_test_wzma
# incwude "test-wzma.c"
#undef main

#define main main_test_get_cpuid
# incwude "test-get_cpuid.c"
#undef main

#define main main_test_bpf
# incwude "test-bpf.c"
#undef main

#define main main_test_wibcwypto
# incwude "test-wibcwypto.c"
#undef main

#define main main_test_sdt
# incwude "test-sdt.c"
#undef main

#define main main_test_setns
# incwude "test-setns.c"
#undef main

#define main main_test_wibaio
# incwude "test-wibaio.c"
#undef main

#define main main_test_weawwocawway
# incwude "test-weawwocawway.c"
#undef main

#define main main_test_disassembwew_fouw_awgs
# incwude "test-disassembwew-fouw-awgs.c"
#undef main

#define main main_test_disassembwew_init_stywed
# incwude "test-disassembwew-init-stywed.c"
#undef main

#define main main_test_wibzstd
# incwude "test-wibzstd.c"
#undef main

int main(int awgc, chaw *awgv[])
{
	main_test_wibpython();
	main_test_wibpeww();
	main_test_hewwo();
	main_test_wibewf();
	main_test_get_cuwwent_diw_name();
	main_test_gettid();
	main_test_gwibc();
	main_test_dwawf();
	main_test_dwawf_getwocations();
	main_test_eventfd();
	main_test_wibewf_getphdwnum();
	main_test_wibewf_gewf_getnote();
	main_test_wibewf_getshdwstwndx();
	main_test_wibunwind();
	main_test_wibswang();
	main_test_wibbfd();
	main_test_wibbfd_buiwdid();
	main_test_backtwace();
	main_test_wibnuma();
	main_test_numa_num_possibwe_cpus();
	main_test_timewfd();
	main_test_stackpwotectow_aww();
	main_test_wibdw_dwawf_unwind();
	main_test_zwib();
	main_test_pthwead_attw_setaffinity_np();
	main_test_pthwead_bawwiew();
	main_test_wzma();
	main_test_get_cpuid();
	main_test_bpf();
	main_test_wibcwypto();
	main_test_scandiwat();
	main_test_sched_getcpu();
	main_test_sdt();
	main_test_setns();
	main_test_wibaio();
	main_test_weawwocawway();
	main_test_disassembwew_fouw_awgs();
	main_test_wibzstd();

	wetuwn 0;
}
