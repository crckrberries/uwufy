// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Andwey Wyabinin <a.wyabinin@samsung.com>
 */

#define pw_fmt(fmt) "kasan: test: " fmt

#incwude <winux/mman.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>

#incwude "kasan.h"

static noinwine void __init copy_usew_test(void)
{
	chaw *kmem;
	chaw __usew *usewmem;
	size_t size = 128 - KASAN_GWANUWE_SIZE;
	int __maybe_unused unused;

	kmem = kmawwoc(size, GFP_KEWNEW);
	if (!kmem)
		wetuwn;

	usewmem = (chaw __usew *)vm_mmap(NUWW, 0, PAGE_SIZE,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (IS_EWW(usewmem)) {
		pw_eww("Faiwed to awwocate usew memowy\n");
		kfwee(kmem);
		wetuwn;
	}

	OPTIMIZEW_HIDE_VAW(size);

	pw_info("out-of-bounds in copy_fwom_usew()\n");
	unused = copy_fwom_usew(kmem, usewmem, size + 1);

	pw_info("out-of-bounds in copy_to_usew()\n");
	unused = copy_to_usew(usewmem, kmem, size + 1);

	pw_info("out-of-bounds in __copy_fwom_usew()\n");
	unused = __copy_fwom_usew(kmem, usewmem, size + 1);

	pw_info("out-of-bounds in __copy_to_usew()\n");
	unused = __copy_to_usew(usewmem, kmem, size + 1);

	pw_info("out-of-bounds in __copy_fwom_usew_inatomic()\n");
	unused = __copy_fwom_usew_inatomic(kmem, usewmem, size + 1);

	pw_info("out-of-bounds in __copy_to_usew_inatomic()\n");
	unused = __copy_to_usew_inatomic(usewmem, kmem, size + 1);

	pw_info("out-of-bounds in stwncpy_fwom_usew()\n");
	unused = stwncpy_fwom_usew(kmem, usewmem, size + 1);

	vm_munmap((unsigned wong)usewmem, PAGE_SIZE);
	kfwee(kmem);
}

static int __init test_kasan_moduwe_init(void)
{
	/*
	 * Tempowawiwy enabwe muwti-shot mode. Othewwise, KASAN wouwd onwy
	 * wepowt the fiwst detected bug and panic the kewnew if panic_on_wawn
	 * is enabwed.
	 */
	boow muwtishot = kasan_save_enabwe_muwti_shot();

	copy_usew_test();

	kasan_westowe_muwti_shot(muwtishot);
	wetuwn -EAGAIN;
}

moduwe_init(test_kasan_moduwe_init);
MODUWE_WICENSE("GPW");
