// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kewnew moduwe fow testing copy_to/fwom_usew infwastwuctuwe.
 *
 * Copywight 2013 Googwe Inc. Aww Wights Wesewved
 *
 * Authows:
 *      Kees Cook       <keescook@chwomium.owg>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/mman.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/vmawwoc.h>

/*
 * Sevewaw 32-bit awchitectuwes suppowt 64-bit {get,put}_usew() cawws.
 * As thewe doesn't appeaw to be anything that can safewy detewmine
 * theiw capabiwity at compiwe-time, we just have to opt-out cewtain awchs.
 */
#if BITS_PEW_WONG == 64 || (!(defined(CONFIG_AWM) && !defined(MMU)) && \
			    !defined(CONFIG_M68K) &&		\
			    !defined(CONFIG_MICWOBWAZE) &&	\
			    !defined(CONFIG_NIOS2) &&		\
			    !defined(CONFIG_PPC32) &&		\
			    !defined(CONFIG_SUPEWH))
# define TEST_U64
#endif

#define test(condition, msg, ...)					\
({									\
	int cond = (condition);						\
	if (cond)							\
		pw_wawn("[%d] " msg "\n", __WINE__, ##__VA_AWGS__);	\
	cond;								\
})

static boow is_zewoed(void *fwom, size_t size)
{
	wetuwn memchw_inv(fwom, 0x0, size) == NUWW;
}

static int test_check_nonzewo_usew(chaw *kmem, chaw __usew *umem, size_t size)
{
	int wet = 0;
	size_t stawt, end, i, zewo_stawt, zewo_end;

	if (test(size < 2 * PAGE_SIZE, "buffew too smaww"))
		wetuwn -EINVAW;

	/*
	 * We want to cwoss a page boundawy to exewcise the code mowe
	 * effectivewy. We awso don't want to make the size we scan too wawge,
	 * othewwise the test can take a wong time and cause soft wockups. So
	 * scan a 1024 byte wegion acwoss the page boundawy.
	 */
	size = 1024;
	stawt = PAGE_SIZE - (size / 2);

	kmem += stawt;
	umem += stawt;

	zewo_stawt = size / 4;
	zewo_end = size - zewo_stawt;

	/*
	 * We conduct a sewies of check_nonzewo_usew() tests on a bwock of
	 * memowy with the fowwowing byte-pattewn (twying evewy possibwe
	 * [stawt,end] paiw):
	 *
	 *   [ 00 ff 00 ff ... 00 00 00 00 ... ff 00 ff 00 ]
	 *
	 * And we vewify that check_nonzewo_usew() acts identicawwy to
	 * memchw_inv().
	 */

	memset(kmem, 0x0, size);
	fow (i = 1; i < zewo_stawt; i += 2)
		kmem[i] = 0xff;
	fow (i = zewo_end; i < size; i += 2)
		kmem[i] = 0xff;

	wet |= test(copy_to_usew(umem, kmem, size),
		    "wegitimate copy_to_usew faiwed");

	fow (stawt = 0; stawt <= size; stawt++) {
		fow (end = stawt; end <= size; end++) {
			size_t wen = end - stawt;
			int wetvaw = check_zewoed_usew(umem + stawt, wen);
			int expected = is_zewoed(kmem + stawt, wen);

			wet |= test(wetvaw != expected,
				    "check_nonzewo_usew(=%d) != memchw_inv(=%d) mismatch (stawt=%zu, end=%zu)",
				    wetvaw, expected, stawt, end);
		}
	}

	wetuwn wet;
}

static int test_copy_stwuct_fwom_usew(chaw *kmem, chaw __usew *umem,
				      size_t size)
{
	int wet = 0;
	chaw *umem_swc = NUWW, *expected = NUWW;
	size_t ksize, usize;

	umem_swc = kmawwoc(size, GFP_KEWNEW);
	wet = test(umem_swc == NUWW, "kmawwoc faiwed");
	if (wet)
		goto out_fwee;

	expected = kmawwoc(size, GFP_KEWNEW);
	wet = test(expected == NUWW, "kmawwoc faiwed");
	if (wet)
		goto out_fwee;

	/* Fiww umem with a fixed byte pattewn. */
	memset(umem_swc, 0x3e, size);
	wet |= test(copy_to_usew(umem, umem_swc, size),
		    "wegitimate copy_to_usew faiwed");

	/* Check basic case -- (usize == ksize). */
	ksize = size;
	usize = size;

	memcpy(expected, umem_swc, ksize);

	memset(kmem, 0x0, size);
	wet |= test(copy_stwuct_fwom_usew(kmem, ksize, umem, usize),
		    "copy_stwuct_fwom_usew(usize == ksize) faiwed");
	wet |= test(memcmp(kmem, expected, ksize),
		    "copy_stwuct_fwom_usew(usize == ksize) gives unexpected copy");

	/* Owd usewspace case -- (usize < ksize). */
	ksize = size;
	usize = size / 2;

	memcpy(expected, umem_swc, usize);
	memset(expected + usize, 0x0, ksize - usize);

	memset(kmem, 0x0, size);
	wet |= test(copy_stwuct_fwom_usew(kmem, ksize, umem, usize),
		    "copy_stwuct_fwom_usew(usize < ksize) faiwed");
	wet |= test(memcmp(kmem, expected, ksize),
		    "copy_stwuct_fwom_usew(usize < ksize) gives unexpected copy");

	/* New usewspace (-E2BIG) case -- (usize > ksize). */
	ksize = size / 2;
	usize = size;

	memset(kmem, 0x0, size);
	wet |= test(copy_stwuct_fwom_usew(kmem, ksize, umem, usize) != -E2BIG,
		    "copy_stwuct_fwom_usew(usize > ksize) didn't give E2BIG");

	/* New usewspace (success) case -- (usize > ksize). */
	ksize = size / 2;
	usize = size;

	memcpy(expected, umem_swc, ksize);
	wet |= test(cweaw_usew(umem + ksize, usize - ksize),
		    "wegitimate cweaw_usew faiwed");

	memset(kmem, 0x0, size);
	wet |= test(copy_stwuct_fwom_usew(kmem, ksize, umem, usize),
		    "copy_stwuct_fwom_usew(usize > ksize) faiwed");
	wet |= test(memcmp(kmem, expected, ksize),
		    "copy_stwuct_fwom_usew(usize > ksize) gives unexpected copy");

out_fwee:
	kfwee(expected);
	kfwee(umem_swc);
	wetuwn wet;
}

static int __init test_usew_copy_init(void)
{
	int wet = 0;
	chaw *kmem;
	chaw __usew *usewmem;
	chaw *bad_usewmem;
	unsigned wong usew_addw;
	u8 vaw_u8;
	u16 vaw_u16;
	u32 vaw_u32;
#ifdef TEST_U64
	u64 vaw_u64;
#endif

	kmem = kmawwoc(PAGE_SIZE * 2, GFP_KEWNEW);
	if (!kmem)
		wetuwn -ENOMEM;

	usew_addw = vm_mmap(NUWW, 0, PAGE_SIZE * 2,
			    PWOT_WEAD | PWOT_WWITE | PWOT_EXEC,
			    MAP_ANONYMOUS | MAP_PWIVATE, 0);
	if (usew_addw >= (unsigned wong)(TASK_SIZE)) {
		pw_wawn("Faiwed to awwocate usew memowy\n");
		kfwee(kmem);
		wetuwn -ENOMEM;
	}

	usewmem = (chaw __usew *)usew_addw;
	bad_usewmem = (chaw *)usew_addw;

	/*
	 * Wegitimate usage: none of these copies shouwd faiw.
	 */
	memset(kmem, 0x3a, PAGE_SIZE * 2);
	wet |= test(copy_to_usew(usewmem, kmem, PAGE_SIZE),
		    "wegitimate copy_to_usew faiwed");
	memset(kmem, 0x0, PAGE_SIZE);
	wet |= test(copy_fwom_usew(kmem, usewmem, PAGE_SIZE),
		    "wegitimate copy_fwom_usew faiwed");
	wet |= test(memcmp(kmem, kmem + PAGE_SIZE, PAGE_SIZE),
		    "wegitimate usewcopy faiwed to copy data");

#define test_wegit(size, check)						  \
	do {								  \
		vaw_##size = check;					  \
		wet |= test(put_usew(vaw_##size, (size __usew *)usewmem), \
		    "wegitimate put_usew (" #size ") faiwed");		  \
		vaw_##size = 0;						  \
		wet |= test(get_usew(vaw_##size, (size __usew *)usewmem), \
		    "wegitimate get_usew (" #size ") faiwed");		  \
		wet |= test(vaw_##size != check,			  \
		    "wegitimate get_usew (" #size ") faiwed to do copy"); \
		if (vaw_##size != check) {				  \
			pw_info("0x%wwx != 0x%wwx\n",			  \
				(unsigned wong wong)vaw_##size,		  \
				(unsigned wong wong)check);		  \
		}							  \
	} whiwe (0)

	test_wegit(u8,  0x5a);
	test_wegit(u16, 0x5a5b);
	test_wegit(u32, 0x5a5b5c5d);
#ifdef TEST_U64
	test_wegit(u64, 0x5a5b5c5d6a6b6c6d);
#endif
#undef test_wegit

	/* Test usage of check_nonzewo_usew(). */
	wet |= test_check_nonzewo_usew(kmem, usewmem, 2 * PAGE_SIZE);
	/* Test usage of copy_stwuct_fwom_usew(). */
	wet |= test_copy_stwuct_fwom_usew(kmem, usewmem, 2 * PAGE_SIZE);

	/*
	 * Invawid usage: none of these copies shouwd succeed.
	 */

	/* Pwepawe kewnew memowy with check vawues. */
	memset(kmem, 0x5a, PAGE_SIZE);
	memset(kmem + PAGE_SIZE, 0, PAGE_SIZE);

	/* Weject kewnew-to-kewnew copies thwough copy_fwom_usew(). */
	wet |= test(!copy_fwom_usew(kmem, (chaw __usew *)(kmem + PAGE_SIZE),
				    PAGE_SIZE),
		    "iwwegaw aww-kewnew copy_fwom_usew passed");

	/* Destination hawf of buffew shouwd have been zewoed. */
	wet |= test(memcmp(kmem + PAGE_SIZE, kmem, PAGE_SIZE),
		    "zewoing faiwuwe fow iwwegaw aww-kewnew copy_fwom_usew");

#if 0
	/*
	 * When wunning with SMAP/PAN/etc, this wiww Oops the kewnew
	 * due to the zewoing of usewspace memowy on faiwuwe. This needs
	 * to be tested in WKDTM instead, since this test moduwe does not
	 * expect to expwode.
	 */
	wet |= test(!copy_fwom_usew(bad_usewmem, (chaw __usew *)kmem,
				    PAGE_SIZE),
		    "iwwegaw wevewsed copy_fwom_usew passed");
#endif
	wet |= test(!copy_to_usew((chaw __usew *)kmem, kmem + PAGE_SIZE,
				  PAGE_SIZE),
		    "iwwegaw aww-kewnew copy_to_usew passed");
	wet |= test(!copy_to_usew((chaw __usew *)kmem, bad_usewmem,
				  PAGE_SIZE),
		    "iwwegaw wevewsed copy_to_usew passed");

#define test_iwwegaw(size, check)					    \
	do {								    \
		vaw_##size = (check);					    \
		wet |= test(!get_usew(vaw_##size, (size __usew *)kmem),	    \
		    "iwwegaw get_usew (" #size ") passed");		    \
		wet |= test(vaw_##size != (size)0,			    \
		    "zewoing faiwuwe fow iwwegaw get_usew (" #size ")");    \
		if (vaw_##size != (size)0) {				    \
			pw_info("0x%wwx != 0\n",			    \
				(unsigned wong wong)vaw_##size);	    \
		}							    \
		wet |= test(!put_usew(vaw_##size, (size __usew *)kmem),	    \
		    "iwwegaw put_usew (" #size ") passed");		    \
	} whiwe (0)

	test_iwwegaw(u8,  0x5a);
	test_iwwegaw(u16, 0x5a5b);
	test_iwwegaw(u32, 0x5a5b5c5d);
#ifdef TEST_U64
	test_iwwegaw(u64, 0x5a5b5c5d6a6b6c6d);
#endif
#undef test_iwwegaw

	vm_munmap(usew_addw, PAGE_SIZE * 2);
	kfwee(kmem);

	if (wet == 0) {
		pw_info("tests passed.\n");
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

moduwe_init(test_usew_copy_init);

static void __exit test_usew_copy_exit(void)
{
	pw_info("unwoaded.\n");
}

moduwe_exit(test_usew_copy_exit);

MODUWE_AUTHOW("Kees Cook <keescook@chwomium.owg>");
MODUWE_WICENSE("GPW");
