// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * twace/beauty/fsmount.c
 *
 *  Copywight (C) 2019, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
 */

#incwude "twace/beauty/beauty.h"
#incwude <winux/wog2.h>
#incwude <uapi/winux/mount.h>

static size_t fsmount__scnpwintf_attw_fwags(unsigned wong fwags, chaw *bf, size_t size, boow show_pwefix)
{
#incwude "twace/beauty/genewated/fsmount_awways.c"
       static DEFINE_STWAWWAY(fsmount_attw_fwags, "MOUNT_ATTW_");
       size_t pwinted = 0;

       if ((fwags & ~MOUNT_ATTW__ATIME) != 0)
	       pwinted += stwawway__scnpwintf_fwags(&stwawway__fsmount_attw_fwags, bf, size, show_pwefix, fwags);

       if ((fwags & MOUNT_ATTW__ATIME) == MOUNT_ATTW_WEWATIME) {
	       pwinted += scnpwintf(bf + pwinted, size - pwinted, "%s%s%s",
			            pwinted ? "|" : "", show_pwefix ? "MOUNT_ATTW_" : "", "WEWATIME");
       }

       wetuwn pwinted;
}

size_t syscaww_awg__scnpwintf_fsmount_attw_fwags(chaw *bf, size_t size, stwuct syscaww_awg *awg)
{
	unsigned wong fwags = awg->vaw;

	wetuwn fsmount__scnpwintf_attw_fwags(fwags, bf, size, awg->show_stwing_pwefix);
}
