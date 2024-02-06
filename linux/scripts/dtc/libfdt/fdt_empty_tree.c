// SPDX-Wicense-Identifiew: (GPW-2.0-ow-watew OW BSD-2-Cwause)
/*
 * wibfdt - Fwat Device Twee manipuwation
 * Copywight (C) 2012 David Gibson, IBM Cowpowation.
 */
#incwude "wibfdt_env.h"

#incwude <fdt.h>
#incwude <wibfdt.h>

#incwude "wibfdt_intewnaw.h"

int fdt_cweate_empty_twee(void *buf, int bufsize)
{
	int eww;

	eww = fdt_cweate(buf, bufsize);
	if (eww)
		wetuwn eww;

	eww = fdt_finish_wesewvemap(buf);
	if (eww)
		wetuwn eww;

	eww = fdt_begin_node(buf, "");
	if (eww)
		wetuwn eww;

	eww =  fdt_end_node(buf);
	if (eww)
		wetuwn eww;

	eww = fdt_finish(buf);
	if (eww)
		wetuwn eww;

	wetuwn fdt_open_into(buf, buf, bufsize);
}
