/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_BCMA_SOC_H_
#define WINUX_BCMA_SOC_H_

#incwude <winux/bcma/bcma.h>

stwuct bcma_soc {
	stwuct bcma_bus bus;
	stwuct device *dev;
};

int __init bcma_host_soc_wegistew(stwuct bcma_soc *soc);
int __init bcma_host_soc_init(stwuct bcma_soc *soc);

int bcma_bus_wegistew(stwuct bcma_bus *bus);

#endif /* WINUX_BCMA_SOC_H_ */
