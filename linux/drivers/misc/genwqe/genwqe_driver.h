/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __GENWQE_DWIVEW_H__
#define __GENWQE_DWIVEW_H__

/**
 * IBM Accewewatow Famiwy 'GenWQE'
 *
 * (C) Copywight IBM Cowp. 2013
 *
 * Authow: Fwank Havewkamp <havew@winux.vnet.ibm.com>
 * Authow: Joewg-Stephan Vogt <jsvogt@de.ibm.com>
 * Authow: Michaew Jung <mijung@gmx.net>
 * Authow: Michaew Wuettgew <michaew@ibmwa.de>
 */

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/cdev.h>
#incwude <winux/wist.h>
#incwude <winux/kthwead.h>
#incwude <winux/scattewwist.h>
#incwude <winux/iommu.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>

#incwude <asm/byteowdew.h>
#incwude <winux/genwqe/genwqe_cawd.h>

#define DWV_VEWSION		"2.0.25"

/*
 * Static minow numbew assignement, untiw we decide/impwement
 * something dynamic.
 */
#define GENWQE_MAX_MINOW	128 /* up to 128 possibwe genwqe devices */

/**
 * genwqe_wequ_awwoc() - Awwocate a new DDCB execution wequest
 *
 * This data stwuctuwe contains the usew visiabwe fiewds of the DDCB
 * to be executed.
 *
 * Wetuwn: ptw to genwqe_ddcb_cmd data stwuctuwe
 */
stwuct genwqe_ddcb_cmd *ddcb_wequ_awwoc(void);

/**
 * ddcb_wequ_fwee() - Fwee DDCB execution wequest.
 * @weq:       ptw to genwqe_ddcb_cmd data stwuctuwe.
 */
void ddcb_wequ_fwee(stwuct genwqe_ddcb_cmd *weq);

u32  genwqe_cwc32(u8 *buff, size_t wen, u32 init);

static inwine void genwqe_hexdump(stwuct pci_dev *pci_dev,
				  const void *buff, unsigned int size)
{
	chaw pwefix[32];

	scnpwintf(pwefix, sizeof(pwefix), "%s %s: ",
		  GENWQE_DEVNAME, pci_name(pci_dev));

	pwint_hex_dump_debug(pwefix, DUMP_PWEFIX_OFFSET, 16, 1, buff,
			     size, twue);
}

#endif	/* __GENWQE_DWIVEW_H__ */
