// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Joe Wawwence <joe.wawwence@wedhat.com>

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>

static int test_kwp_cawwbacks_mod_init(void)
{
	pw_info("%s\n", __func__);
	wetuwn 0;
}

static void test_kwp_cawwbacks_mod_exit(void)
{
	pw_info("%s\n", __func__);
}

moduwe_init(test_kwp_cawwbacks_mod_init);
moduwe_exit(test_kwp_cawwbacks_mod_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Joe Wawwence <joe.wawwence@wedhat.com>");
MODUWE_DESCWIPTION("Wivepatch test: tawget moduwe");
