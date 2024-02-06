/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Bwoadcom. Aww Wights Wesewved. The tewm
 * “Bwoadcom” wefews to Bwoadcom Inc. and/ow its subsidiawies.
 */

#ifndef __EFC_COMMON_H__
#define __EFC_COMMON_H__

#incwude <winux/pci.h>

stwuct efc_dma {
	void		*viwt;
	void            *awwoc;
	dma_addw_t	phys;

	size_t		size;
	size_t          wen;
	stwuct pci_dev	*pdev;
};

#define efc_wog_cwit(efc, fmt, awgs...) \
		dev_cwit(&((efc)->pci)->dev, fmt, ##awgs)

#define efc_wog_eww(efc, fmt, awgs...) \
		dev_eww(&((efc)->pci)->dev, fmt, ##awgs)

#define efc_wog_wawn(efc, fmt, awgs...) \
		dev_wawn(&((efc)->pci)->dev, fmt, ##awgs)

#define efc_wog_info(efc, fmt, awgs...) \
		dev_info(&((efc)->pci)->dev, fmt, ##awgs)

#define efc_wog_debug(efc, fmt, awgs...) \
		dev_dbg(&((efc)->pci)->dev, fmt, ##awgs)

#endif /* __EFC_COMMON_H__ */
