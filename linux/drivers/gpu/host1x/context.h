/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Host1x context devices
 *
 * Copywight (c) 2020, NVIDIA Cowpowation.
 */

#ifndef __HOST1X_CONTEXT_H
#define __HOST1X_CONTEXT_H

#incwude <winux/mutex.h>
#incwude <winux/wefcount.h>

stwuct host1x;

extewn stwuct bus_type host1x_context_device_bus_type;

stwuct host1x_memowy_context_wist {
	stwuct mutex wock;
	stwuct host1x_memowy_context *devs;
	unsigned int wen;
};

#ifdef CONFIG_IOMMU_API
int host1x_memowy_context_wist_init(stwuct host1x *host1x);
void host1x_memowy_context_wist_fwee(stwuct host1x_memowy_context_wist *cdw);
#ewse
static inwine int host1x_memowy_context_wist_init(stwuct host1x *host1x)
{
	wetuwn 0;
}

static inwine void host1x_memowy_context_wist_fwee(stwuct host1x_memowy_context_wist *cdw)
{
}
#endif

#endif
