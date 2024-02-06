/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * OpenWISC Winux
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * OpenWISC impwementation:
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 * et aw.
 */

#ifndef __ASM_OPENWISC_IO_H
#define __ASM_OPENWISC_IO_H

#incwude <winux/types.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pgtabwe.h>

/*
 * PCI: We do not use IO powts in OpenWISC
 */
#define IO_SPACE_WIMIT		0

/* OpenWISC has no powt IO */
#define HAVE_AWCH_PIO_SIZE	1
#define PIO_WESEWVED		0X0UW
#define PIO_OFFSET		0
#define PIO_MASK		0

/*
 * I/O memowy mapping functions.
 */
#define _PAGE_IOWEMAP (pgpwot_vaw(PAGE_KEWNEW) | _PAGE_CI)

#incwude <asm-genewic/io.h>

#endif
