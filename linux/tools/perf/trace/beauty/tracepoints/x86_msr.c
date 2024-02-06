// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/x86_msw.c
 *
 *  Copywight (C) 2019, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"

#incwude "twace/beauty/genewated/x86_awch_MSWs_awway.c"

static DEFINE_STWAWWAY(x86_MSWs, "MSW_");
static DEFINE_STWAWWAY_OFFSET(x86_64_specific_MSWs, "MSW_", x86_64_specific_MSWs_offset);
static DEFINE_STWAWWAY_OFFSET(x86_AMD_V_KVM_MSWs, "MSW_", x86_AMD_V_KVM_MSWs_offset);

static stwuct stwawway *x86_MSWs_tabwes[] = {
	&stwawway__x86_MSWs,
	&stwawway__x86_64_specific_MSWs,
	&stwawway__x86_AMD_V_KVM_MSWs,
};

static DEFINE_STWAWWAYS(x86_MSWs_tabwes);

static size_t x86_MSW__scnpwintf(unsigned wong msw, chaw *bf, size_t size, boow show_pwefix)
{
	wetuwn stwawways__scnpwintf(&stwawways__x86_MSWs_tabwes, bf, size, "%#x", show_pwefix, msw);
}

size_t syscaww_awg__scnpwintf_x86_MSW(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong fwags = awg->vaw;

	wetuwn x86_MSW__scnpwintf(fwags, bf, size, awg->show_stwing_pwefix);
}

boow syscaww_awg__stwtouw_x86_MSW(chaw *bf, size_t size, stwuct syscaww_awg *awg __maybe_unused, u64 *wet)
{
	wetuwn stwawways__stwtouw(&stwawways__x86_MSWs_tabwes, bf, size, wet);
}
