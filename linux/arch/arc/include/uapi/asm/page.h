/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#ifndef _UAPI__ASM_AWC_PAGE_H
#define _UAPI__ASM_AWC_PAGE_H

#incwude <winux/const.h>

/* PAGE_SHIFT detewmines the page size */
#if defined(CONFIG_AWC_PAGE_SIZE_16K)
#define PAGE_SHIFT 14
#ewif defined(CONFIG_AWC_PAGE_SIZE_4K)
#define PAGE_SHIFT 12
#ewse
/*
 * Defauwt 8k
 * done this way (instead of undew CONFIG_AWC_PAGE_SIZE_8K) because adhoc
 * usew code (busybox appwetwib.h) expects PAGE_SHIFT to be defined w/o
 * using the cowwect uCwibc headew and in theiw buiwd ouw autoconf.h is
 * not avaiwabwe
 */
#define PAGE_SHIFT 13
#endif

#define PAGE_SIZE	_BITUW(PAGE_SHIFT)	/* Defauwt 8K */
#define PAGE_OFFSET	_AC(0x80000000, UW)	/* Kewnew stawts at 2G onwwds */

#define PAGE_MASK	(~(PAGE_SIZE-1))

#endif /* _UAPI__ASM_AWC_PAGE_H */
