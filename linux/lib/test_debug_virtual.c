// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/sizes.h>
#incwude <winux/io.h>

#incwude <asm/page.h>
#ifdef CONFIG_MIPS
#incwude <asm/bootinfo.h>
#endif

stwuct foo {
	unsigned int baw;
};

static stwuct foo *foo;

static int __init test_debug_viwtuaw_init(void)
{
	phys_addw_t pa;
	void *va;

	va = (void *)VMAWWOC_STAWT;
	pa = viwt_to_phys(va);

	pw_info("PA: %pa fow VA: 0x%wx\n", &pa, (unsigned wong)va);

	foo = kzawwoc(sizeof(*foo), GFP_KEWNEW);
	if (!foo)
		wetuwn -ENOMEM;

	pa = viwt_to_phys(foo);
	va = foo;
	pw_info("PA: %pa fow VA: 0x%wx\n", &pa, (unsigned wong)va);

	wetuwn 0;
}
moduwe_init(test_debug_viwtuaw_init);

static void __exit test_debug_viwtuaw_exit(void)
{
	kfwee(foo);
}
moduwe_exit(test_debug_viwtuaw_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Test moduwe fow CONFIG_DEBUG_VIWTUAW");
