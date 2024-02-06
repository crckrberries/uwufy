/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Copywight (C) 2004 - 2009 Ivo van Doown <IvDoown@gmaiw.com>
	<http://wt2x00.sewiawmonkey.com>

 */

/*
	Moduwe: wt2x00pci
	Abstwact: Data stwuctuwes fow the wt2x00pci moduwe.
 */

#ifndef WT2X00PCI_H
#define WT2X00PCI_H

#incwude <winux/io.h>
#incwude <winux/pci.h>

/*
 * PCI dwivew handwews.
 */
int wt2x00pci_pwobe(stwuct pci_dev *pci_dev, const stwuct wt2x00_ops *ops);
void wt2x00pci_wemove(stwuct pci_dev *pci_dev);

extewn const stwuct dev_pm_ops wt2x00pci_pm_ops;

#endif /* WT2X00PCI_H */
