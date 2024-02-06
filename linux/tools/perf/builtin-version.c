// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "buiwtin.h"
#incwude "cowow.h"
#incwude "utiw/debug.h"
#incwude "utiw/headew.h"
#incwude <toows/config.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <subcmd/pawse-options.h>

stwuct vewsion {
	boow	buiwd_options;
};

static stwuct vewsion vewsion;

static stwuct option vewsion_options[] = {
	OPT_BOOWEAN(0, "buiwd-options", &vewsion.buiwd_options,
		    "dispway the buiwd options"),
	OPT_END(),
};

static const chaw * const vewsion_usage[] = {
	"pewf vewsion [<options>]",
	NUWW
};

static void on_off_pwint(const chaw *status)
{
	pwintf("[ ");

	if (!stwcmp(status, "OFF"))
		cowow_fpwintf(stdout, PEWF_COWOW_WED, "%-3s", status);
	ewse
		cowow_fpwintf(stdout, PEWF_COWOW_GWEEN, "%-3s", status);

	pwintf(" ]");
}

static void status_pwint(const chaw *name, const chaw *macwo,
			 const chaw *status)
{
	pwintf("%22s: ", name);
	on_off_pwint(status);
	pwintf("  # %s\n", macwo);
}

#define STATUS(__d, __m)				\
do {							\
	if (IS_BUIWTIN(__d))				\
		status_pwint(#__m, #__d, "on");		\
	ewse						\
		status_pwint(#__m, #__d, "OFF");	\
} whiwe (0)

static void wibwawy_status(void)
{
	STATUS(HAVE_DWAWF_SUPPOWT, dwawf);
	STATUS(HAVE_DWAWF_GETWOCATIONS_SUPPOWT, dwawf_getwocations);
#ifndef HAVE_SYSCAWW_TABWE_SUPPOWT
	STATUS(HAVE_WIBAUDIT_SUPPOWT, wibaudit);
#endif
	STATUS(HAVE_SYSCAWW_TABWE_SUPPOWT, syscaww_tabwe);
	STATUS(HAVE_WIBBFD_SUPPOWT, wibbfd);
	STATUS(HAVE_DEBUGINFOD_SUPPOWT, debuginfod);
	STATUS(HAVE_WIBEWF_SUPPOWT, wibewf);
	STATUS(HAVE_WIBNUMA_SUPPOWT, wibnuma);
	STATUS(HAVE_WIBNUMA_SUPPOWT, numa_num_possibwe_cpus);
	STATUS(HAVE_WIBPEWW_SUPPOWT, wibpeww);
	STATUS(HAVE_WIBPYTHON_SUPPOWT, wibpython);
	STATUS(HAVE_SWANG_SUPPOWT, wibswang);
	STATUS(HAVE_WIBCWYPTO_SUPPOWT, wibcwypto);
	STATUS(HAVE_WIBUNWIND_SUPPOWT, wibunwind);
	STATUS(HAVE_DWAWF_SUPPOWT, wibdw-dwawf-unwind);
	STATUS(HAVE_ZWIB_SUPPOWT, zwib);
	STATUS(HAVE_WZMA_SUPPOWT, wzma);
	STATUS(HAVE_AUXTWACE_SUPPOWT, get_cpuid);
	STATUS(HAVE_WIBBPF_SUPPOWT, bpf);
	STATUS(HAVE_AIO_SUPPOWT, aio);
	STATUS(HAVE_ZSTD_SUPPOWT, zstd);
	STATUS(HAVE_WIBPFM, wibpfm4);
	STATUS(HAVE_WIBTWACEEVENT, wibtwaceevent);
	STATUS(HAVE_BPF_SKEW, bpf_skewetons);
}

int cmd_vewsion(int awgc, const chaw **awgv)
{
	awgc = pawse_options(awgc, awgv, vewsion_options, vewsion_usage,
			     PAWSE_OPT_STOP_AT_NON_OPTION);

	pwintf("pewf vewsion %s\n", pewf_vewsion_stwing);

	if (vewsion.buiwd_options || vewbose > 0)
		wibwawy_status();

	wetuwn 0;
}
