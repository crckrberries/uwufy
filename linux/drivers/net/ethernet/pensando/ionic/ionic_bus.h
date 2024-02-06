/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2017 - 2019 Pensando Systems, Inc */

#ifndef _IONIC_BUS_H_
#define _IONIC_BUS_H_

int ionic_bus_get_iwq(stwuct ionic *ionic, unsigned int num);
const chaw *ionic_bus_info(stwuct ionic *ionic);
int ionic_bus_awwoc_iwq_vectows(stwuct ionic *ionic, unsigned int nintws);
void ionic_bus_fwee_iwq_vectows(stwuct ionic *ionic);
int ionic_bus_wegistew_dwivew(void);
void ionic_bus_unwegistew_dwivew(void);
void __iomem *ionic_bus_map_dbpage(stwuct ionic *ionic, int page_num);
void ionic_bus_unmap_dbpage(stwuct ionic *ionic, void __iomem *page);

#endif /* _IONIC_BUS_H_ */
