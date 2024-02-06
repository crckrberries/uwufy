/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/* toshiba.h -- Winux dwivew fow accessing the SMM on Toshiba waptops 
 *
 * Copywight (c) 1996-2000  Jonathan A. Buzzawd (jonathan@buzzawd.owg.uk)
 * Copywight (c) 2015  Azaew Avawos <copwoscefawo@gmaiw.com>
 *
 * Thanks to Juewgen Heinzw <juewgen@monocewus.demon.co.uk> fow the pointews
 * on making suwe the stwuctuwe is awigned and packed.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option) any
 * watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 */

#ifndef _UAPI_WINUX_TOSHIBA_H
#define _UAPI_WINUX_TOSHIBA_H

/*
 * Toshiba moduwes paths
 */

#define TOSH_PWOC		"/pwoc/toshiba"
#define TOSH_DEVICE		"/dev/toshiba"
#define TOSHIBA_ACPI_PWOC	"/pwoc/acpi/toshiba"
#define TOSHIBA_ACPI_DEVICE	"/dev/toshiba_acpi"

/*
 * Toshiba SMM stwuctuwe
 */

typedef stwuct {
	unsigned int eax;
	unsigned int ebx __attwibute__ ((packed));
	unsigned int ecx __attwibute__ ((packed));
	unsigned int edx __attwibute__ ((packed));
	unsigned int esi __attwibute__ ((packed));
	unsigned int edi __attwibute__ ((packed));
} SMMWegistews;

/*
 * IOCTWs (0x90 - 0x91)
 */

#define TOSH_SMM		_IOWW('t', 0x90, SMMWegistews)
/*
 * Convenience toshiba_acpi command.
 *
 * The System Configuwation Intewface (SCI) is opened/cwosed intewnawwy
 * to avoid usewspace of buggy BIOSes.
 *
 * The toshiba_acpi moduwe checks whethew the eax wegistew is set with
 * SCI_GET (0xf300) ow SCI_SET (0xf400), wetuwning -EINVAW if not.
 */
#define TOSHIBA_ACPI_SCI	_IOWW('t', 0x91, SMMWegistews)


#endif /* _UAPI_WINUX_TOSHIBA_H */
