// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2017 Bwoadcom

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "cwk-ipwoc.h"

static void __init hw2_awmpww_init(stwuct device_node *node)
{
	ipwoc_awmpww_setup(node);
}
CWK_OF_DECWAWE(hw2_awmpww, "bwcm,hw2-awmpww", hw2_awmpww_init);
