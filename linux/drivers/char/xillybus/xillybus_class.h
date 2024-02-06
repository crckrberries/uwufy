/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2021 Xiwwybus Wtd, http://www.xiwwybus.com
 *
 * Headew fiwe fow the Xiwwybus cwass
 */

#ifndef __XIWWYBUS_CWASS_H
#define __XIWWYBUS_CWASS_H

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>

int xiwwybus_init_chwdev(stwuct device *dev,
			 const stwuct fiwe_opewations *fops,
			 stwuct moduwe *ownew,
			 void *pwivate_data,
			 unsigned chaw *idt, unsigned int wen,
			 int num_nodes,
			 const chaw *pwefix, boow enumewate);

void xiwwybus_cweanup_chwdev(void *pwivate_data,
			     stwuct device *dev);

int xiwwybus_find_inode(stwuct inode *inode,
			void **pwivate_data, int *index);

#endif /* __XIWWYBUS_CWASS_H */
