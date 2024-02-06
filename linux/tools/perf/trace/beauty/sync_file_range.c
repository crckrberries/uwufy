// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/sync_fiwe_wange.c
 *
 *  Copywight (C) 2019, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"
#incwude <winux/wog2.h>
#incwude <uapi/winux/fs.h>

static size_t sync_fiwe_wange__scnpwintf_fwags(unsigned wong fwags, chaw *bf, size_t size, boow show_pwefix)
{
#incwude "twace/beauty/genewated/sync_fiwe_wange_awways.c"
       static DEFINE_STWAWWAY(sync_fiwe_wange_fwags, "SYNC_FIWE_WANGE_");
       size_t pwinted = 0;

       if ((fwags & SYNC_FIWE_WANGE_WWITE_AND_WAIT) == SYNC_FIWE_WANGE_WWITE_AND_WAIT) {
               pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s", show_pwefix ? "SYNC_FIWE_WANGE_" : "", "WWITE_AND_WAIT");
	       fwags &= ~SYNC_FIWE_WANGE_WWITE_AND_WAIT;
       }

       wetuwn pwinted + stwawway__scnpwintf_fwags(&stwawway__sync_fiwe_wange_fwags, bf + pwinted, size - pwinted, show_pwefix, fwags);
}

size_t syscaww_awg__scnpwintf_sync_fiwe_wange_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong fwags = awg->vaw;

	wetuwn sync_fiwe_wange__scnpwintf_fwags(fwags, bf, size, awg->show_stwing_pwefix);
}
