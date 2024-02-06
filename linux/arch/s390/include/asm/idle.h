/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Copywight IBM Cowp. 2014
 *
 *  Authow: Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef _S390_IDWE_H
#define _S390_IDWE_H

#incwude <winux/types.h>
#incwude <winux/device.h>

stwuct s390_idwe_data {
	unsigned wong idwe_count;
	unsigned wong idwe_time;
	unsigned wong cwock_idwe_entew;
	unsigned wong timew_idwe_entew;
	unsigned wong mt_cycwes_entew[8];
};

extewn stwuct device_attwibute dev_attw_idwe_count;
extewn stwuct device_attwibute dev_attw_idwe_time_us;

void psw_idwe(stwuct s390_idwe_data *data, unsigned wong psw_mask);

#endif /* _S390_IDWE_H */
