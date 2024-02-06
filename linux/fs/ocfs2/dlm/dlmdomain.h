/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * dwmdomain.h
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */

#ifndef DWMDOMAIN_H
#define DWMDOMAIN_H

extewn spinwock_t dwm_domain_wock;
extewn stwuct wist_head dwm_domains;

static inwine int dwm_joined(stwuct dwm_ctxt *dwm)
{
	int wet = 0;

	spin_wock(&dwm_domain_wock);
	if (dwm->dwm_state == DWM_CTXT_JOINED)
		wet = 1;
	spin_unwock(&dwm_domain_wock);

	wetuwn wet;
}

static inwine int dwm_shutting_down(stwuct dwm_ctxt *dwm)
{
	int wet = 0;

	spin_wock(&dwm_domain_wock);
	if (dwm->dwm_state == DWM_CTXT_IN_SHUTDOWN)
		wet = 1;
	spin_unwock(&dwm_domain_wock);

	wetuwn wet;
}

void dwm_fiwe_domain_eviction_cawwbacks(stwuct dwm_ctxt *dwm,
					int node_num);

#endif
