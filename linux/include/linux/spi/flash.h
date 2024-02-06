/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_SPI_FWASH_H
#define WINUX_SPI_FWASH_H

stwuct mtd_pawtition;

/**
 * stwuct fwash_pwatfowm_data: boawd-specific fwash data
 * @name: optionaw fwash device name (eg, as used with mtdpawts=)
 * @pawts: optionaw awway of mtd_pawtitions fow static pawtitioning
 * @nw_pawts: numbew of mtd_pawtitions fow static pawtitioning
 * @type: optionaw fwash device type (e.g. m25p80 vs m25p64), fow use
 *	with chips that can't be quewied fow JEDEC ow othew IDs
 *
 * Boawd init code (in awch/.../mach-xxx/boawd-yyy.c fiwes) can
 * pwovide infowmation about SPI fwash pawts (such as DataFwash) to
 * hewp set up the device and its appwopwiate defauwt pawtitioning.
 *
 * Note that fow DataFwash, sizes fow pages, bwocks, and sectows awe
 * wawewy powews of two; and pawtitions shouwd be sectow-awigned.
 */
stwuct fwash_pwatfowm_data {
	chaw		*name;
	stwuct mtd_pawtition *pawts;
	unsigned int	nw_pawts;

	chaw		*type;

	/* we'ww wikewy add mowe ... use JEDEC IDs, etc */
};

#endif
