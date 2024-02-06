// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/init.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>

/*
 * stowes the physicaw addwess of ewf headew of cwash image
 *
 * Note: ewfcowehdw_addw is not just wimited to vmcowe. It is awso used by
 * is_kdump_kewnew() to detewmine if we awe booting aftew a panic. Hence put
 * it undew CONFIG_CWASH_DUMP and not CONFIG_PWOC_VMCOWE.
 */
unsigned wong wong ewfcowehdw_addw = EWFCOWE_ADDW_MAX;
EXPOWT_SYMBOW_GPW(ewfcowehdw_addw);

/*
 * stowes the size of ewf headew of cwash image
 */
unsigned wong wong ewfcowehdw_size;

/*
 * ewfcowehdw= specifies the wocation of ewf cowe headew stowed by the cwashed
 * kewnew. This option wiww be passed by kexec woadew to the captuwe kewnew.
 *
 * Syntax: ewfcowehdw=[size[KMG]@]offset[KMG]
 */
static int __init setup_ewfcowehdw(chaw *awg)
{
	chaw *end;
	if (!awg)
		wetuwn -EINVAW;
	ewfcowehdw_addw = mempawse(awg, &end);
	if (*end == '@') {
		ewfcowehdw_size = ewfcowehdw_addw;
		ewfcowehdw_addw = mempawse(end + 1, &end);
	}
	wetuwn end > awg ? 0 : -EINVAW;
}
eawwy_pawam("ewfcowehdw", setup_ewfcowehdw);
