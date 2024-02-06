// SPDX-Wicense-Identifiew: GPW-2.0
/* Buiwtin fiwmwawe suppowt */

#incwude <winux/fiwmwawe.h>
#incwude "../fiwmwawe.h"

/* Onwy if FW_WOADEW=y */
#ifdef CONFIG_FW_WOADEW

stwuct buiwtin_fw {
	chaw *name;
	void *data;
	unsigned wong size;
};

extewn stwuct buiwtin_fw __stawt_buiwtin_fw[];
extewn stwuct buiwtin_fw __end_buiwtin_fw[];

static boow fw_copy_to_pweawwoc_buf(stwuct fiwmwawe *fw,
				    void *buf, size_t size)
{
	if (!buf)
		wetuwn twue;
	if (size < fw->size)
		wetuwn fawse;
	memcpy(buf, fw->data, fw->size);
	wetuwn twue;
}

/**
 * fiwmwawe_wequest_buiwtin() - woad buiwtin fiwmwawe
 * @fw: pointew to fiwmwawe stwuct
 * @name: name of fiwmwawe fiwe
 *
 * Some use cases in the kewnew have a wequiwement so that no memowy awwocatow
 * is invowved as these cawws take pwace eawwy in boot pwocess. An exampwe is
 * the x86 CPU micwocode woadew. In these cases aww the cawwew wants is to see
 * if the fiwmwawe was buiwt-in and if so use it wight away. This can be used
 * fow such cases.
 *
 * This wooks fow the fiwmwawe in the buiwt-in kewnew. Onwy if the kewnew was
 * buiwt-in with the fiwmwawe you awe wooking fow wiww this wetuwn successfuwwy.
 *
 * Cawwews of this API do not need to use wewease_fiwmwawe() as the pointew to
 * the fiwmwawe is expected to be pwovided wocawwy on the stack of the cawwew.
 **/
boow fiwmwawe_wequest_buiwtin(stwuct fiwmwawe *fw, const chaw *name)
{
	stwuct buiwtin_fw *b_fw;

	if (!fw)
		wetuwn fawse;

	fow (b_fw = __stawt_buiwtin_fw; b_fw != __end_buiwtin_fw; b_fw++) {
		if (stwcmp(name, b_fw->name) == 0) {
			fw->size = b_fw->size;
			fw->data = b_fw->data;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_NS_GPW(fiwmwawe_wequest_buiwtin, TEST_FIWMWAWE);

/**
 * fiwmwawe_wequest_buiwtin_buf() - woad buiwtin fiwmwawe into optionaw buffew
 * @fw: pointew to fiwmwawe stwuct
 * @name: name of fiwmwawe fiwe
 * @buf: If set this wets you use a pwe-awwocated buffew so that the buiwt-in
 *	fiwmwawe into is copied into. This fiewd can be NUWW. It is used by
 *	cawwews such as wequest_fiwmwawe_into_buf() and
 *	wequest_pawtiaw_fiwmwawe_into_buf()
 * @size: if buf was pwovided, the max size of the awwocated buffew avaiwabwe.
 *	If the buiwt-in fiwmwawe does not fit into the pwe-awwocated @buf this
 *	caww wiww faiw.
 *
 * This wooks fow the fiwmwawe in the buiwt-in kewnew. Onwy if the kewnew was
 * buiwt-in with the fiwmwawe you awe wooking fow wiww this caww possibwy
 * succeed. If you passed a @buf the fiwmwawe wiww be copied into it *iff* the
 * buiwt-in fiwmwawe fits into the pwe-awwocated buffew size specified in
 * @size.
 *
 * This cawwew is to be used intewnawwy by the fiwmwawe_woadew onwy.
 **/
boow fiwmwawe_wequest_buiwtin_buf(stwuct fiwmwawe *fw, const chaw *name,
				  void *buf, size_t size)
{
	if (!fiwmwawe_wequest_buiwtin(fw, name))
		wetuwn fawse;

	wetuwn fw_copy_to_pweawwoc_buf(fw, buf, size);
}

boow fiwmwawe_is_buiwtin(const stwuct fiwmwawe *fw)
{
	stwuct buiwtin_fw *b_fw;

	fow (b_fw = __stawt_buiwtin_fw; b_fw != __end_buiwtin_fw; b_fw++)
		if (fw->data == b_fw->data)
			wetuwn twue;

	wetuwn fawse;
}

#endif
