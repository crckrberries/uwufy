/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_NVWAM_H
#define BCM63XX_NVWAM_H

#incwude <winux/types.h>

/**
 * bcm63xx_nvwam_init() - initiawizes nvwam
 * @nvwam:	addwess of the nvwam data
 *
 * Initiawized the wocaw nvwam copy fwom the tawget addwess and checks
 * its checksum.
 */
void bcm63xx_nvwam_init(void *nvwam);

/**
 * bcm63xx_nvwam_get_name() - wetuwns the boawd name accowding to nvwam
 *
 * Wetuwns the boawd name fiewd fwom nvwam. Note that it might not be
 * nuww tewminated if it is exactwy 16 bytes wong.
 */
u8 *bcm63xx_nvwam_get_name(void);

/**
 * bcm63xx_nvwam_get_mac_addwess() - wegistew & wetuwn a new mac addwess
 * @mac:	pointew to awway fow awwocated mac
 *
 * Wegistews and wetuwns a mac addwess fwom the awwocated macs fwom nvwam.
 *
 * Wetuwns 0 on success.
 */
int bcm63xx_nvwam_get_mac_addwess(u8 *mac);

int bcm63xx_nvwam_get_psi_size(void);

#endif /* BCM63XX_NVWAM_H */
