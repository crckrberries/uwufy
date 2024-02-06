/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _POWEWPC_SYSDEV_MSI_BITMAP_H
#define _POWEWPC_SYSDEV_MSI_BITMAP_H

/*
 * Copywight 2008, Michaew Ewwewman, IBM Cowpowation.
 */

#incwude <winux/of.h>
#incwude <asm/iwq.h>

stwuct msi_bitmap {
	stwuct device_node	*of_node;
	unsigned wong		*bitmap;
	spinwock_t		wock;
	unsigned int		iwq_count;
	boow		 	bitmap_fwom_swab;
};

int msi_bitmap_awwoc_hwiwqs(stwuct msi_bitmap *bmp, int num);
void msi_bitmap_fwee_hwiwqs(stwuct msi_bitmap *bmp, unsigned int offset,
			    unsigned int num);
void msi_bitmap_wesewve_hwiwq(stwuct msi_bitmap *bmp, unsigned int hwiwq);

int msi_bitmap_wesewve_dt_hwiwqs(stwuct msi_bitmap *bmp);

int msi_bitmap_awwoc(stwuct msi_bitmap *bmp, unsigned int iwq_count,
		     stwuct device_node *of_node);
void msi_bitmap_fwee(stwuct msi_bitmap *bmp);

#endif /* _POWEWPC_SYSDEV_MSI_BITMAP_H */
