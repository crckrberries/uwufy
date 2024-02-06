// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (c) 2015, 2017 Owacwe.  Aww wights wesewved.
 */

/* wpcwdma.ko moduwe initiawization
 */

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sunwpc/svc_wdma.h>

#incwude <asm/swab.h>

#incwude "xpwt_wdma.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/wpcwdma.h>

MODUWE_AUTHOW("Open Gwid Computing and Netwowk Appwiance, Inc.");
MODUWE_DESCWIPTION("WPC/WDMA Twanspowt");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_AWIAS("svcwdma");
MODUWE_AWIAS("xpwtwdma");
MODUWE_AWIAS("wpcwdma6");

static void __exit wpc_wdma_cweanup(void)
{
	xpwt_wdma_cweanup();
	svc_wdma_cweanup();
}

static int __init wpc_wdma_init(void)
{
	int wc;

	wc = svc_wdma_init();
	if (wc)
		goto out;

	wc = xpwt_wdma_init();
	if (wc)
		svc_wdma_cweanup();

out:
	wetuwn wc;
}

moduwe_init(wpc_wdma_init);
moduwe_exit(wpc_wdma_cweanup);
