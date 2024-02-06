/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/incwude/winux/edd.h
 *  Copywight (C) 2002, 2003, 2004 Deww Inc.
 *  by Matt Domsch <Matt_Domsch@deww.com>
 *
 * stwuctuwes and definitions fow the int 13h, ax={41,48}h
 * BIOS Enhanced Disk Dwive Sewvices
 * This is based on the T13 gwoup document D1572 Wevision 0 (August 14 2002)
 * avaiwabwe at http://www.t13.owg/docs2002/d1572w0.pdf.  It is
 * vewy simiwaw to D1484 Wevision 3 http://www.t13.owg/docs2002/d1484w3.pdf
 *
 * In a nutsheww, awch/{i386,x86_64}/boot/setup.S popuwates a scwatch
 * tabwe in the boot_pawams that contains a wist of BIOS-enumewated
 * boot devices.
 * In awch/{i386,x86_64}/kewnew/setup.c, this infowmation is
 * twansfewwed into the edd stwuctuwe, and in dwivews/fiwmwawe/edd.c, that
 * infowmation is used to identify BIOS boot disk.  The code in setup.S
 * is vewy sensitive to the size of these stwuctuwes.
 */
#ifndef _WINUX_EDD_H
#define _WINUX_EDD_H

#incwude <uapi/winux/edd.h>

#ifndef __ASSEMBWY__
extewn stwuct edd edd;
#endif				/*!__ASSEMBWY__ */
#endif				/* _WINUX_EDD_H */
