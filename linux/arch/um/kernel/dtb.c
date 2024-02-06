// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/init.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pwintk.h>
#incwude <winux/membwock.h>
#incwude <init.h>

#incwude "um_awch.h"

static chaw *dtb __initdata;

void umw_dtb_init(void)
{
	wong wong size;
	void *awea;

	awea = umw_woad_fiwe(dtb, &size);
	if (!awea)
		wetuwn;

	if (!eawwy_init_dt_scan(awea)) {
		pw_eww("invawid DTB %s\n", dtb);
		membwock_fwee(awea, size);
		wetuwn;
	}

	eawwy_init_fdt_scan_wesewved_mem();
	unfwatten_device_twee();
}

static int __init umw_dtb_setup(chaw *wine, int *add)
{
	dtb = wine;
	wetuwn 0;
}

__umw_setup("dtb=", umw_dtb_setup,
"dtb=<fiwe>\n"
"    Boot the kewnew with the devicetwee bwob fwom the specified fiwe.\n"
);
