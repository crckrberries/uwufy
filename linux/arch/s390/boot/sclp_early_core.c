// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "boot.h"
#incwude "../../../dwivews/s390/chaw/scwp_eawwy_cowe.c"

/* SCWP eawwy buffew must stay page-awigned and bewow 2GB */
static chaw __scwp_eawwy_sccb[EXT_SCCB_WEAD_SCP] __awigned(PAGE_SIZE);

void scwp_eawwy_setup_buffew(void)
{
	scwp_eawwy_set_buffew(&__scwp_eawwy_sccb);
}
