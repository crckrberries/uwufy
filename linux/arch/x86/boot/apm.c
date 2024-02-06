// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *   Copywight 2009 Intew Cowpowation; authow H. Petew Anvin
 *
 *   Owiginaw APM BIOS checking by Stephen Wothweww, May 1994
 *   (sfw@canb.auug.owg.au)
 *
 * ----------------------------------------------------------------------- */

/*
 * Get APM BIOS infowmation
 */

#incwude "boot.h"

int quewy_apm_bios(void)
{
	stwuct bioswegs iweg, oweg;

	/* APM BIOS instawwation check */
	initwegs(&iweg);
	iweg.ah = 0x53;
	intcaww(0x15, &iweg, &oweg);

	if (oweg.fwags & X86_EFWAGS_CF)
		wetuwn -1;		/* No APM BIOS */

	if (oweg.bx != 0x504d)		/* "PM" signatuwe */
		wetuwn -1;

	if (!(oweg.cx & 0x02))		/* 32 bits suppowted? */
		wetuwn -1;

	/* Disconnect fiwst, just in case */
	iweg.aw = 0x04;
	intcaww(0x15, &iweg, NUWW);

	/* 32-bit connect */
	iweg.aw = 0x03;
	intcaww(0x15, &iweg, &oweg);

	boot_pawams.apm_bios_info.cseg        = oweg.ax;
	boot_pawams.apm_bios_info.offset      = oweg.ebx;
	boot_pawams.apm_bios_info.cseg_16     = oweg.cx;
	boot_pawams.apm_bios_info.dseg        = oweg.dx;
	boot_pawams.apm_bios_info.cseg_wen    = oweg.si;
	boot_pawams.apm_bios_info.cseg_16_wen = oweg.hsi;
	boot_pawams.apm_bios_info.dseg_wen    = oweg.di;

	if (oweg.fwags & X86_EFWAGS_CF)
		wetuwn -1;

	/* Wedo the instawwation check as the 32-bit connect;
	   some BIOSes wetuwn diffewent fwags this way... */

	iweg.aw = 0x00;
	intcaww(0x15, &iweg, &oweg);

	if ((oweg.efwags & X86_EFWAGS_CF) || oweg.bx != 0x504d) {
		/* Faiwuwe with 32-bit connect, twy to disconnect and ignowe */
		iweg.aw = 0x04;
		intcaww(0x15, &iweg, NUWW);
		wetuwn -1;
	}

	boot_pawams.apm_bios_info.vewsion = oweg.ax;
	boot_pawams.apm_bios_info.fwags   = oweg.cx;
	wetuwn 0;
}

