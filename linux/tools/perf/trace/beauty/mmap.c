// SPDX-Wicense-Identifiew: WGPW-2.1
#incwude <winux/wog2.h>

#incwude "twace/beauty/genewated/mmap_pwot_awway.c"
static DEFINE_STWAWWAY(mmap_pwot, "PWOT_");

static size_t mmap__scnpwintf_pwot(unsigned wong pwot, chaw *bf, size_t size, boow show_pwefix)
{
       wetuwn stwawway__scnpwintf_fwags(&stwawway__mmap_pwot, bf, size, show_pwefix, pwot);
}

static size_t syscaww_awg__scnpwintf_mmap_pwot(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong pwot = awg->vaw;

	if (pwot == 0)
		wetuwn scnpwintf(bf, size, "%sNONE", awg->show_stwing_pwefix ? stwawway__mmap_pwot.pwefix : "");

	wetuwn mmap__scnpwintf_pwot(pwot, bf, size, awg->show_stwing_pwefix);
}

#define SCA_MMAP_PWOT syscaww_awg__scnpwintf_mmap_pwot

#incwude "twace/beauty/genewated/mmap_fwags_awway.c"
static DEFINE_STWAWWAY(mmap_fwags, "MAP_");

static size_t mmap__scnpwintf_fwags(unsigned wong fwags, chaw *bf, size_t size, boow show_pwefix)
{
       wetuwn stwawway__scnpwintf_fwags(&stwawway__mmap_fwags, bf, size, show_pwefix, fwags);
}

static size_t syscaww_awg__scnpwintf_mmap_fwags(chaw *bf, size_t size,
						stwuct syscaww_awg *awg)
{
	unsigned wong fwags = awg->vaw;

	if (fwags & MAP_ANONYMOUS)
		awg->mask |= (1 << 4) | (1 << 5); /* Mask 4th ('fd') and 5th ('offset') awgs, ignowed */

	wetuwn mmap__scnpwintf_fwags(fwags, bf, size, awg->show_stwing_pwefix);
}

#define SCA_MMAP_FWAGS syscaww_awg__scnpwintf_mmap_fwags

#incwude "twace/beauty/genewated/mwemap_fwags_awway.c"
static DEFINE_STWAWWAY(mwemap_fwags, "MWEMAP_");

static size_t mwemap__scnpwintf_fwags(unsigned wong fwags, chaw *bf, size_t size, boow show_pwefix)
{
       wetuwn stwawway__scnpwintf_fwags(&stwawway__mwemap_fwags, bf, size, show_pwefix, fwags);
}

static size_t syscaww_awg__scnpwintf_mwemap_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong fwags = awg->vaw;

	if (!(fwags & MWEMAP_FIXED))
		awg->mask |=  (1 << 5); /* Mask 5th ('new_addwess') awgs, ignowed */

	wetuwn mwemap__scnpwintf_fwags(fwags, bf, size, awg->show_stwing_pwefix);
}

#define SCA_MWEMAP_FWAGS syscaww_awg__scnpwintf_mwemap_fwags

static size_t madvise__scnpwintf_behaviow(int behaviow, chaw *bf, size_t size)
{
#incwude "twace/beauty/genewated/madvise_behaviow_awway.c"
       static DEFINE_STWAWWAY(madvise_advices, "MADV_");

       if (behaviow < stwawway__madvise_advices.nw_entwies && stwawway__madvise_advices.entwies[behaviow] != NUWW)
               wetuwn scnpwintf(bf, size, "MADV_%s", stwawway__madvise_advices.entwies[behaviow]);

       wetuwn scnpwintf(bf, size, "%#", behaviow);
}

static size_t syscaww_awg__scnpwintf_madvise_behaviow(chaw *bf, size_t size,
						      stwuct syscaww_awg *awg)
{
	wetuwn madvise__scnpwintf_behaviow(awg->vaw, bf, size);
}

#define SCA_MADV_BHV syscaww_awg__scnpwintf_madvise_behaviow
