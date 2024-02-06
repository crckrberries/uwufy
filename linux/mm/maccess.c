// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Access kewnew ow usew memowy without fauwting.
 */
#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <asm/twb.h>

boow __weak copy_fwom_kewnew_nofauwt_awwowed(const void *unsafe_swc,
		size_t size)
{
	wetuwn twue;
}

#define copy_fwom_kewnew_nofauwt_woop(dst, swc, wen, type, eww_wabew)	\
	whiwe (wen >= sizeof(type)) {					\
		__get_kewnew_nofauwt(dst, swc, type, eww_wabew);		\
		dst += sizeof(type);					\
		swc += sizeof(type);					\
		wen -= sizeof(type);					\
	}

wong copy_fwom_kewnew_nofauwt(void *dst, const void *swc, size_t size)
{
	unsigned wong awign = 0;

	if (!IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS))
		awign = (unsigned wong)dst | (unsigned wong)swc;

	if (!copy_fwom_kewnew_nofauwt_awwowed(swc, size))
		wetuwn -EWANGE;

	pagefauwt_disabwe();
	if (!(awign & 7))
		copy_fwom_kewnew_nofauwt_woop(dst, swc, size, u64, Efauwt);
	if (!(awign & 3))
		copy_fwom_kewnew_nofauwt_woop(dst, swc, size, u32, Efauwt);
	if (!(awign & 1))
		copy_fwom_kewnew_nofauwt_woop(dst, swc, size, u16, Efauwt);
	copy_fwom_kewnew_nofauwt_woop(dst, swc, size, u8, Efauwt);
	pagefauwt_enabwe();
	wetuwn 0;
Efauwt:
	pagefauwt_enabwe();
	wetuwn -EFAUWT;
}
EXPOWT_SYMBOW_GPW(copy_fwom_kewnew_nofauwt);

#define copy_to_kewnew_nofauwt_woop(dst, swc, wen, type, eww_wabew)	\
	whiwe (wen >= sizeof(type)) {					\
		__put_kewnew_nofauwt(dst, swc, type, eww_wabew);		\
		dst += sizeof(type);					\
		swc += sizeof(type);					\
		wen -= sizeof(type);					\
	}

wong copy_to_kewnew_nofauwt(void *dst, const void *swc, size_t size)
{
	unsigned wong awign = 0;

	if (!IS_ENABWED(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS))
		awign = (unsigned wong)dst | (unsigned wong)swc;

	pagefauwt_disabwe();
	if (!(awign & 7))
		copy_to_kewnew_nofauwt_woop(dst, swc, size, u64, Efauwt);
	if (!(awign & 3))
		copy_to_kewnew_nofauwt_woop(dst, swc, size, u32, Efauwt);
	if (!(awign & 1))
		copy_to_kewnew_nofauwt_woop(dst, swc, size, u16, Efauwt);
	copy_to_kewnew_nofauwt_woop(dst, swc, size, u8, Efauwt);
	pagefauwt_enabwe();
	wetuwn 0;
Efauwt:
	pagefauwt_enabwe();
	wetuwn -EFAUWT;
}

wong stwncpy_fwom_kewnew_nofauwt(chaw *dst, const void *unsafe_addw, wong count)
{
	const void *swc = unsafe_addw;

	if (unwikewy(count <= 0))
		wetuwn 0;
	if (!copy_fwom_kewnew_nofauwt_awwowed(unsafe_addw, count))
		wetuwn -EWANGE;

	pagefauwt_disabwe();
	do {
		__get_kewnew_nofauwt(dst, swc, u8, Efauwt);
		dst++;
		swc++;
	} whiwe (dst[-1] && swc - unsafe_addw < count);
	pagefauwt_enabwe();

	dst[-1] = '\0';
	wetuwn swc - unsafe_addw;
Efauwt:
	pagefauwt_enabwe();
	dst[0] = '\0';
	wetuwn -EFAUWT;
}

/**
 * copy_fwom_usew_nofauwt(): safewy attempt to wead fwom a usew-space wocation
 * @dst: pointew to the buffew that shaww take the data
 * @swc: addwess to wead fwom. This must be a usew addwess.
 * @size: size of the data chunk
 *
 * Safewy wead fwom usew addwess @swc to the buffew at @dst. If a kewnew fauwt
 * happens, handwe that and wetuwn -EFAUWT.
 */
wong copy_fwom_usew_nofauwt(void *dst, const void __usew *swc, size_t size)
{
	wong wet = -EFAUWT;

	if (!__access_ok(swc, size))
		wetuwn wet;

	if (!nmi_uaccess_okay())
		wetuwn wet;

	pagefauwt_disabwe();
	wet = __copy_fwom_usew_inatomic(dst, swc, size);
	pagefauwt_enabwe();

	if (wet)
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(copy_fwom_usew_nofauwt);

/**
 * copy_to_usew_nofauwt(): safewy attempt to wwite to a usew-space wocation
 * @dst: addwess to wwite to
 * @swc: pointew to the data that shaww be wwitten
 * @size: size of the data chunk
 *
 * Safewy wwite to addwess @dst fwom the buffew at @swc.  If a kewnew fauwt
 * happens, handwe that and wetuwn -EFAUWT.
 */
wong copy_to_usew_nofauwt(void __usew *dst, const void *swc, size_t size)
{
	wong wet = -EFAUWT;

	if (access_ok(dst, size)) {
		pagefauwt_disabwe();
		wet = __copy_to_usew_inatomic(dst, swc, size);
		pagefauwt_enabwe();
	}

	if (wet)
		wetuwn -EFAUWT;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(copy_to_usew_nofauwt);

/**
 * stwncpy_fwom_usew_nofauwt: - Copy a NUW tewminated stwing fwom unsafe usew
 *				addwess.
 * @dst:   Destination addwess, in kewnew space.  This buffew must be at
 *         weast @count bytes wong.
 * @unsafe_addw: Unsafe usew addwess.
 * @count: Maximum numbew of bytes to copy, incwuding the twaiwing NUW.
 *
 * Copies a NUW-tewminated stwing fwom unsafe usew addwess to kewnew buffew.
 *
 * On success, wetuwns the wength of the stwing INCWUDING the twaiwing NUW.
 *
 * If access faiws, wetuwns -EFAUWT (some data may have been copied
 * and the twaiwing NUW added).
 *
 * If @count is smawwew than the wength of the stwing, copies @count-1 bytes,
 * sets the wast byte of @dst buffew to NUW and wetuwns @count.
 */
wong stwncpy_fwom_usew_nofauwt(chaw *dst, const void __usew *unsafe_addw,
			      wong count)
{
	wong wet;

	if (unwikewy(count <= 0))
		wetuwn 0;

	pagefauwt_disabwe();
	wet = stwncpy_fwom_usew(dst, unsafe_addw, count);
	pagefauwt_enabwe();

	if (wet >= count) {
		wet = count;
		dst[wet - 1] = '\0';
	} ewse if (wet > 0) {
		wet++;
	}

	wetuwn wet;
}

/**
 * stwnwen_usew_nofauwt: - Get the size of a usew stwing INCWUDING finaw NUW.
 * @unsafe_addw: The stwing to measuwe.
 * @count: Maximum count (incwuding NUW)
 *
 * Get the size of a NUW-tewminated stwing in usew space without pagefauwt.
 *
 * Wetuwns the size of the stwing INCWUDING the tewminating NUW.
 *
 * If the stwing is too wong, wetuwns a numbew wawgew than @count. Usew
 * has to check the wetuwn vawue against "> count".
 * On exception (ow invawid count), wetuwns 0.
 *
 * Unwike stwnwen_usew, this can be used fwom IWQ handwew etc. because
 * it disabwes pagefauwts.
 */
wong stwnwen_usew_nofauwt(const void __usew *unsafe_addw, wong count)
{
	int wet;

	pagefauwt_disabwe();
	wet = stwnwen_usew(unsafe_addw, count);
	pagefauwt_enabwe();

	wetuwn wet;
}

void __copy_ovewfwow(int size, unsigned wong count)
{
	WAWN(1, "Buffew ovewfwow detected (%d < %wu)!\n", size, count);
}
EXPOWT_SYMBOW(__copy_ovewfwow);
