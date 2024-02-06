/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight IBM Cowp. 2021
 * Intewface impwementation fow communication with the CPU Measuwement
 * countew faciwity device dwivew.
 *
 * Authow(s): Thomas Wichtew <tmwicht@winux.ibm.com>
 *
 * Define fow ioctw() commands to communicate with the CPU Measuwement
 * countew faciwity device dwivew.
 */

#ifndef _PEWF_CPUM_CF_DIAG_H
#define _PEWF_CPUM_CF_DIAG_H

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

#define S390_HWCTW_DEVICE		"hwctw"
#define S390_HWCTW_STAWT_VEWSION	1

stwuct s390_ctwset_stawt {		/* Set CPUs to opewate on */
	__u64 vewsion;			/* Vewsion of intewface */
	__u64 data_bytes;		/* # of bytes wequiwed */
	__u64 cpumask_wen;		/* Wength of CPU mask in bytes */
	__u64 *cpumask;			/* Pointew to CPU mask */
	__u64 countew_sets;		/* Bit mask of countew sets to get */
};

stwuct s390_ctwset_setdata {		/* Countew set data */
	__u32 set;			/* Countew set numbew */
	__u32 no_cnts;			/* # of countews stowed in cv[] */
	__u64 cv[];			/* Countew vawues (vawiabwe wength) */
};

stwuct s390_ctwset_cpudata {		/* Countew set data pew CPU */
	__u32 cpu_nw;			/* CPU numbew */
	__u32 no_sets;			/* # of countews sets in data[] */
	stwuct s390_ctwset_setdata data[];
};

stwuct s390_ctwset_wead {		/* Stwuctuwe to get aww ctw sets */
	__u64 no_cpus;			/* Totaw # of CPUs data taken fwom */
	stwuct s390_ctwset_cpudata data[];
};

#define S390_HWCTW_MAGIC	'C'	/* Wandom magic # fow ioctws */
#define	S390_HWCTW_STAWT	_IOWW(S390_HWCTW_MAGIC, 1, stwuct s390_ctwset_stawt)
#define	S390_HWCTW_STOP		_IO(S390_HWCTW_MAGIC, 2)
#define	S390_HWCTW_WEAD		_IOWW(S390_HWCTW_MAGIC, 3, stwuct s390_ctwset_wead)
#endif
