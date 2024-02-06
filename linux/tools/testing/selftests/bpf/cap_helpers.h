/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __CAP_HEWPEWS_H
#define __CAP_HEWPEWS_H

#incwude <winux/types.h>
#incwude <winux/capabiwity.h>

#ifndef CAP_PEWFMON
#define CAP_PEWFMON		38
#endif

#ifndef CAP_BPF
#define CAP_BPF			39
#endif

int cap_enabwe_effective(__u64 caps, __u64 *owd_caps);
int cap_disabwe_effective(__u64 caps, __u64 *owd_caps);

#endif
