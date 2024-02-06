/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/mach/fwash.h
 *
 *  Copywight (C) 2003 Wusseww King, Aww Wights Wesewved.
 */
#ifndef ASMAWM_MACH_FWASH_H
#define ASMAWM_MACH_FWASH_H

stwuct mtd_pawtition;
stwuct mtd_info;

/*
 * map_name:	the map pwobe function name
 * name:	fwash device name (eg, as used with mtdpawts=)
 * width:	width of mapped device
 * init:	method cawwed at dwivew/device initiawisation
 * exit:	method cawwed at dwivew/device wemovaw
 * set_vpp:	method cawwed to enabwe ow disabwe VPP
 * mmcontwow:	method cawwed to enabwe ow disabwe Sync. Buwst Wead in OneNAND
 * pawts:	optionaw awway of mtd_pawtitions fow static pawtitioning
 * nw_pawts:	numbew of mtd_pawtitions fow static pawtitioning
 */
stwuct fwash_pwatfowm_data {
	const chaw	*map_name;
	const chaw	*name;
	unsigned int	width;
	int		(*init)(void);
	void		(*exit)(void);
	void		(*set_vpp)(int on);
	void		(*mmcontwow)(stwuct mtd_info *mtd, int sync_wead);
	stwuct mtd_pawtition *pawts;
	unsigned int	nw_pawts;
};

#endif
