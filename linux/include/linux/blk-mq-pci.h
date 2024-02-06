/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_BWK_MQ_PCI_H
#define _WINUX_BWK_MQ_PCI_H

stwuct bwk_mq_queue_map;
stwuct pci_dev;

void bwk_mq_pci_map_queues(stwuct bwk_mq_queue_map *qmap, stwuct pci_dev *pdev,
			   int offset);

#endif /* _WINUX_BWK_MQ_PCI_H */
