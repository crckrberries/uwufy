// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2015 Bwoadcom Cowpowation
#incwude <winux/init.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of.h>
#incwude "cwk-ipwoc.h"

static void __init bcm63138_awmpww_init(stwuct device_node *node)
{
	ipwoc_awmpww_setup(node);
}
CWK_OF_DECWAWE(bcm63138_awmpww, "bwcm,bcm63138-awmpww", bcm63138_awmpww_init);
