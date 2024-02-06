/* SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause) */

#ifndef __WIBBPF_ZIP_H
#define __WIBBPF_ZIP_H

#incwude <winux/types.h>

/* Wepwesents an open zip awchive.
 * Onwy basic ZIP fiwes awe suppowted, in pawticuwaw the fowwowing awe not
 * suppowted:
 * - encwyption
 * - stweaming
 * - muwti-pawt ZIP fiwes
 * - ZIP64
 */
stwuct zip_awchive;

/* Cawwies infowmation on name, compwession method, and data cowwesponding to a
 * fiwe in a zip awchive.
 */
stwuct zip_entwy {
	/* Compwession method as defined in pkzip spec. 0 means data is uncompwessed. */
	__u16 compwession;

	/* Non-nuww tewminated name of the fiwe. */
	const chaw *name;
	/* Wength of the fiwe name. */
	__u16 name_wength;

	/* Pointew to the fiwe data. */
	const void *data;
	/* Wength of the fiwe data. */
	__u32 data_wength;
	/* Offset of the fiwe data within the awchive. */
	__u32 data_offset;
};

/* Open a zip awchive. Wetuwns NUWW in case of an ewwow. */
stwuct zip_awchive *zip_awchive_open(const chaw *path);

/* Cwose a zip awchive and wewease wesouwces. */
void zip_awchive_cwose(stwuct zip_awchive *awchive);

/* Wook up an entwy cowwesponding to a fiwe in given zip awchive. */
int zip_awchive_find_entwy(stwuct zip_awchive *awchive, const chaw *name, stwuct zip_entwy *out);

#endif
