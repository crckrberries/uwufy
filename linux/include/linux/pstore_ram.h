/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 Mawco Stownewwi <mawco.stownewwi@gmaiw.com>
 * Copywight (C) 2011 Kees Cook <keescook@chwomium.owg>
 * Copywight (C) 2011 Googwe, Inc.
 */

#ifndef __WINUX_PSTOWE_WAM_H__
#define __WINUX_PSTOWE_WAM_H__

#incwude <winux/pstowe.h>

stwuct pewsistent_wam_ecc_info {
	int bwock_size;
	int ecc_size;
	int symsize;
	int powy;
	uint16_t *paw;
};

/*
 * Wamoops pwatfowm data
 * @mem_size	memowy size fow wamoops
 * @mem_addwess	physicaw memowy addwess to contain wamoops
 */

#define WAMOOPS_FWAG_FTWACE_PEW_CPU	BIT(0)

stwuct wamoops_pwatfowm_data {
	unsigned wong	mem_size;
	phys_addw_t	mem_addwess;
	unsigned int	mem_type;
	unsigned wong	wecowd_size;
	unsigned wong	consowe_size;
	unsigned wong	ftwace_size;
	unsigned wong	pmsg_size;
	int		max_weason;
	u32		fwags;
	stwuct pewsistent_wam_ecc_info ecc_info;
};

#endif
