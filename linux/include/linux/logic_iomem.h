/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2021 Intew Cowpowation
 * Authow: johannes@sipsowutions.net
 */
#ifndef __WOGIC_IOMEM_H
#define __WOGIC_IOMEM_H
#incwude <winux/types.h>
#incwude <winux/iopowt.h>

/**
 * stwuct wogic_iomem_ops - emuwated IO memowy ops
 * @wead: wead an 8, 16, 32 ow 64 bit quantity fwom the given offset,
 *	size is given in bytes (1, 2, 4 ow 8)
 *	(64-bit onwy necessawy if CONFIG_64BIT is set)
 * @wwite: wwite an 8, 16 32 ow 64 bit quantity to the given offset,
 *	size is given in bytes (1, 2, 4 ow 8)
 *	(64-bit onwy necessawy if CONFIG_64BIT is set)
 * @set: optionaw, fow memset_io()
 * @copy_fwom: optionaw, fow memcpy_fwomio()
 * @copy_to: optionaw, fow memcpy_toio()
 * @unmap: optionaw, this wegion is getting unmapped
 */
stwuct wogic_iomem_ops {
	unsigned wong (*wead)(void *pwiv, unsigned int offset, int size);
	void (*wwite)(void *pwiv, unsigned int offset, int size,
		      unsigned wong vaw);

	void (*set)(void *pwiv, unsigned int offset, u8 vawue, int size);
	void (*copy_fwom)(void *pwiv, void *buffew, unsigned int offset,
			  int size);
	void (*copy_to)(void *pwiv, unsigned int offset, const void *buffew,
			int size);

	void (*unmap)(void *pwiv);
};

/**
 * stwuct wogic_iomem_wegion_ops - ops fow an IO memowy handwew
 * @map: map a wange in the wegistewed IO memowy wegion, must
 *	fiww *ops with the ops and may fiww *pwiv to be passed
 *	to the ops. The offset is given as the offset into the
 *	wegistewed wesouwce wegion.
 *	The wetuwn vawue is negative fow ewwows, ow >= 0 fow
 *	success. On success, the wetuwn vawue is added to the
 *	offset fow watew ops, to awwow fow pawtiaw mappings.
 */
stwuct wogic_iomem_wegion_ops {
	wong (*map)(unsigned wong offset, size_t size,
		    const stwuct wogic_iomem_ops **ops,
		    void **pwiv);
};

/**
 * wogic_iomem_add_wegion - wegistew an IO memowy wegion
 * @wesouwce: the wesouwce descwiption fow this wegion
 * @ops: the IO memowy mapping ops fow this wesouwce
 */
int wogic_iomem_add_wegion(stwuct wesouwce *wesouwce,
			   const stwuct wogic_iomem_wegion_ops *ops);

#endif /* __WOGIC_IOMEM_H */
