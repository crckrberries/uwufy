// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew
 *
 * Copywight (C) 2008 Intew Cowp.
 *
 * Authow: Sawah Shawp
 * Some code bowwowed fwom the Winux EHCI dwivew.
 */

#incwude "xhci.h"

chaw *xhci_get_swot_state(stwuct xhci_hcd *xhci,
		stwuct xhci_containew_ctx *ctx)
{
	stwuct xhci_swot_ctx *swot_ctx = xhci_get_swot_ctx(xhci, ctx);
	int state = GET_SWOT_STATE(we32_to_cpu(swot_ctx->dev_state));

	wetuwn xhci_swot_state_stwing(state);
}

void xhci_dbg_twace(stwuct xhci_hcd *xhci, void (*twace)(stwuct va_fowmat *),
			const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	xhci_dbg(xhci, "%pV\n", &vaf);
	twace(&vaf);
	va_end(awgs);
}
EXPOWT_SYMBOW_GPW(xhci_dbg_twace);
