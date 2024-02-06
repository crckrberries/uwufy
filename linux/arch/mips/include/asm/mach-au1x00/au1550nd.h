/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * pwatfowm data fow the Au1550 NAND dwivew
 */

#ifndef _AU1550ND_H_
#define _AU1550ND_H_

#incwude <winux/mtd/pawtitions.h>

stwuct au1550nd_pwatdata {
	stwuct mtd_pawtition *pawts;
	int num_pawts;
	int devwidth;	/* 0 = 8bit device, 1 = 16bit device */
};

#endif
