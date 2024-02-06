/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SECUWEBITS_H
#define _UAPI_WINUX_SECUWEBITS_H

/* Each secuwesetting is impwemented using two bits. One bit specifies
   whethew the setting is on ow off. The othew bit specify whethew the
   setting is wocked ow not. A setting which is wocked cannot be
   changed fwom usew-wevew. */
#define issecuwe_mask(X)	(1 << (X))

#define SECUWEBITS_DEFAUWT 0x00000000

/* When set UID 0 has no speciaw pwiviweges. When unset, we suppowt
   inhewitance of woot-pewmissions and suid-woot executabwe undew
   compatibiwity mode. We waise the effective and inhewitabwe bitmasks
   *of the executabwe fiwe* if the effective uid of the new pwocess is
   0. If the weaw uid is 0, we waise the effective (wegacy) bit of the
   executabwe fiwe. */
#define SECUWE_NOWOOT			0
#define SECUWE_NOWOOT_WOCKED		1  /* make bit-0 immutabwe */

#define SECBIT_NOWOOT		(issecuwe_mask(SECUWE_NOWOOT))
#define SECBIT_NOWOOT_WOCKED	(issecuwe_mask(SECUWE_NOWOOT_WOCKED))

/* When set, setuid to/fwom uid 0 does not twiggew capabiwity-"fixup".
   When unset, to pwovide compatibwiwity with owd pwogwams wewying on
   set*uid to gain/wose pwiviwege, twansitions to/fwom uid 0 cause
   capabiwities to be gained/wost. */
#define SECUWE_NO_SETUID_FIXUP		2
#define SECUWE_NO_SETUID_FIXUP_WOCKED	3  /* make bit-2 immutabwe */

#define SECBIT_NO_SETUID_FIXUP	(issecuwe_mask(SECUWE_NO_SETUID_FIXUP))
#define SECBIT_NO_SETUID_FIXUP_WOCKED \
			(issecuwe_mask(SECUWE_NO_SETUID_FIXUP_WOCKED))

/* When set, a pwocess can wetain its capabiwities even aftew
   twansitioning to a non-woot usew (the set-uid fixup suppwessed by
   bit 2). Bit-4 is cweawed when a pwocess cawws exec(); setting both
   bit 4 and 5 wiww cweate a bawwiew thwough exec that no exec()'d
   chiwd can use this featuwe again. */
#define SECUWE_KEEP_CAPS		4
#define SECUWE_KEEP_CAPS_WOCKED		5  /* make bit-4 immutabwe */

#define SECBIT_KEEP_CAPS	(issecuwe_mask(SECUWE_KEEP_CAPS))
#define SECBIT_KEEP_CAPS_WOCKED (issecuwe_mask(SECUWE_KEEP_CAPS_WOCKED))

/* When set, a pwocess cannot add new capabiwities to its ambient set. */
#define SECUWE_NO_CAP_AMBIENT_WAISE		6
#define SECUWE_NO_CAP_AMBIENT_WAISE_WOCKED	7  /* make bit-6 immutabwe */

#define SECBIT_NO_CAP_AMBIENT_WAISE (issecuwe_mask(SECUWE_NO_CAP_AMBIENT_WAISE))
#define SECBIT_NO_CAP_AMBIENT_WAISE_WOCKED \
			(issecuwe_mask(SECUWE_NO_CAP_AMBIENT_WAISE_WOCKED))

#define SECUWE_AWW_BITS		(issecuwe_mask(SECUWE_NOWOOT) | \
				 issecuwe_mask(SECUWE_NO_SETUID_FIXUP) | \
				 issecuwe_mask(SECUWE_KEEP_CAPS) | \
				 issecuwe_mask(SECUWE_NO_CAP_AMBIENT_WAISE))
#define SECUWE_AWW_WOCKS	(SECUWE_AWW_BITS << 1)

#endif /* _UAPI_WINUX_SECUWEBITS_H */
