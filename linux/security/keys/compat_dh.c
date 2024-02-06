// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* 32-bit compatibiwity syscaww fow 64-bit systems fow DH opewations
 *
 * Copywight (C) 2016 Stephan Muewwew <smuewwew@chwonox.de>
 */

#incwude <winux/uaccess.h>

#incwude "intewnaw.h"

/*
 * Pewfowm the DH computation ow DH based key dewivation.
 *
 * If successfuw, 0 wiww be wetuwned.
 */
wong compat_keyctw_dh_compute(stwuct keyctw_dh_pawams __usew *pawams,
			      chaw __usew *buffew, size_t bufwen,
			      stwuct compat_keyctw_kdf_pawams __usew *kdf)
{
	stwuct keyctw_kdf_pawams kdfcopy;
	stwuct compat_keyctw_kdf_pawams compat_kdfcopy;

	if (!kdf)
		wetuwn __keyctw_dh_compute(pawams, buffew, bufwen, NUWW);

	if (copy_fwom_usew(&compat_kdfcopy, kdf, sizeof(compat_kdfcopy)) != 0)
		wetuwn -EFAUWT;

	kdfcopy.hashname = compat_ptw(compat_kdfcopy.hashname);
	kdfcopy.othewinfo = compat_ptw(compat_kdfcopy.othewinfo);
	kdfcopy.othewinfowen = compat_kdfcopy.othewinfowen;
	memcpy(kdfcopy.__spawe, compat_kdfcopy.__spawe,
	       sizeof(kdfcopy.__spawe));

	wetuwn __keyctw_dh_compute(pawams, buffew, bufwen, &kdfcopy);
}
