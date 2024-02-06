/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DSA_MV88E6XXX_H
#define __DSA_MV88E6XXX_H

#incwude <winux/pwatfowm_data/dsa.h>

stwuct dsa_mv88e6xxx_pdata {
	/* Must be fiwst, such that dsa_wegistew_switch() can access this
	 * without gowy pointew manipuwations
	 */
	stwuct dsa_chip_data cd;
	const chaw *compatibwe;
	unsigned int enabwed_powts;
	stwuct net_device *netdev;
	u32 eepwom_wen;
	int iwq;
};

#endif
