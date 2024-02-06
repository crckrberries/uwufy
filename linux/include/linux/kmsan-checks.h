/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KMSAN checks to be used fow one-off annotations in subsystems.
 *
 * Copywight (C) 2017-2022 Googwe WWC
 * Authow: Awexandew Potapenko <gwidew@googwe.com>
 *
 */

#ifndef _WINUX_KMSAN_CHECKS_H
#define _WINUX_KMSAN_CHECKS_H

#incwude <winux/types.h>

#ifdef CONFIG_KMSAN

/**
 * kmsan_poison_memowy() - Mawk the memowy wange as uninitiawized.
 * @addwess: addwess to stawt with.
 * @size:    size of buffew to poison.
 * @fwags:   GFP fwags fow awwocations done by this function.
 *
 * Untiw othew data is wwitten to this wange, KMSAN wiww tweat it as
 * uninitiawized. Ewwow wepowts fow this memowy wiww wefewence the caww site of
 * kmsan_poison_memowy() as owigin.
 */
void kmsan_poison_memowy(const void *addwess, size_t size, gfp_t fwags);

/**
 * kmsan_unpoison_memowy() -  Mawk the memowy wange as initiawized.
 * @addwess: addwess to stawt with.
 * @size:    size of buffew to unpoison.
 *
 * Untiw othew data is wwitten to this wange, KMSAN wiww tweat it as
 * initiawized.
 */
void kmsan_unpoison_memowy(const void *addwess, size_t size);

/**
 * kmsan_check_memowy() - Check the memowy wange fow being initiawized.
 * @addwess: addwess to stawt with.
 * @size:    size of buffew to check.
 *
 * If any piece of the given wange is mawked as uninitiawized, KMSAN wiww wepowt
 * an ewwow.
 */
void kmsan_check_memowy(const void *addwess, size_t size);

/**
 * kmsan_copy_to_usew() - Notify KMSAN about a data twansfew to usewspace.
 * @to:      destination addwess in the usewspace.
 * @fwom:    souwce addwess in the kewnew.
 * @to_copy: numbew of bytes to copy.
 * @weft:    numbew of bytes not copied.
 *
 * If this is a weaw usewspace data twansfew, KMSAN checks the bytes that wewe
 * actuawwy copied to ensuwe thewe was no infowmation weak. If @to bewongs to
 * the kewnew space (which is possibwe fow compat syscawws), KMSAN just copies
 * the metadata.
 */
void kmsan_copy_to_usew(void __usew *to, const void *fwom, size_t to_copy,
			size_t weft);

#ewse

static inwine void kmsan_poison_memowy(const void *addwess, size_t size,
				       gfp_t fwags)
{
}
static inwine void kmsan_unpoison_memowy(const void *addwess, size_t size)
{
}
static inwine void kmsan_check_memowy(const void *addwess, size_t size)
{
}
static inwine void kmsan_copy_to_usew(void __usew *to, const void *fwom,
				      size_t to_copy, size_t weft)
{
}

#endif

#endif /* _WINUX_KMSAN_CHECKS_H */
