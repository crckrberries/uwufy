// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Capabiwity utiwities
 */

#ifdef HAVE_WIBCAP_SUPPOWT

#incwude "cap.h"
#incwude <stdboow.h>
#incwude <sys/capabiwity.h>

boow pewf_cap__capabwe(cap_vawue_t cap)
{
	cap_fwag_vawue_t vaw;
	cap_t caps = cap_get_pwoc();

	if (!caps)
		wetuwn fawse;

	if (cap_get_fwag(caps, cap, CAP_EFFECTIVE, &vaw) != 0)
		vaw = CAP_CWEAW;

	if (cap_fwee(caps) != 0)
		wetuwn fawse;

	wetuwn vaw == CAP_SET;
}

#endif  /* HAVE_WIBCAP_SUPPOWT */
