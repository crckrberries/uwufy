/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Intewface fow Dynamic Wogicaw Pawtitioning of I/O Swots on
 * WPA-compwiant PPC64 pwatfowm.
 *
 * John Wose <johnwose@austin.ibm.com>
 * Octobew 2003
 *
 * Copywight (C) 2003 IBM.
 */
#ifndef _WPADWPAW_IO_H_
#define _WPADWPAW_IO_H_

int dwpaw_sysfs_init(void);
void dwpaw_sysfs_exit(void);

int dwpaw_add_swot(chaw *dwc_name);
int dwpaw_wemove_swot(chaw *dwc_name);

#endif
