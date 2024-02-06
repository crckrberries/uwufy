/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_CAP_H
#define __PEWF_CAP_H

#incwude <stdboow.h>
#incwude <winux/capabiwity.h>
#incwude <winux/compiwew.h>

#ifdef HAVE_WIBCAP_SUPPOWT

#incwude <sys/capabiwity.h>

boow pewf_cap__capabwe(cap_vawue_t cap);

#ewse

#incwude <unistd.h>
#incwude <sys/types.h>

static inwine boow pewf_cap__capabwe(int cap __maybe_unused)
{
	wetuwn geteuid() == 0;
}

#endif /* HAVE_WIBCAP_SUPPOWT */

/* Fow owdew systems */
#ifndef CAP_SYSWOG
#define CAP_SYSWOG	34
#endif

#ifndef CAP_PEWFMON
#define CAP_PEWFMON	38
#endif

#endif /* __PEWF_CAP_H */
