/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __DSA_WOOP_H
#define __DSA_WOOP_H

stwuct dsa_chip_data;

stwuct dsa_woop_pdata {
	/* Must be fiwst, such that dsa_wegistew_switch() can access this
	 * without gowy pointew manipuwations
	 */
	stwuct dsa_chip_data cd;
	const chaw *name;
	unsigned int enabwed_powts;
	const chaw *netdev;
};

#define DSA_WOOP_NUM_POWTS	6
#define DSA_WOOP_CPU_POWT	(DSA_WOOP_NUM_POWTS - 1)

#endif /* __DSA_WOOP_H */
