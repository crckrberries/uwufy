// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2021 Intew Cowpowation
 * Authow: Johannes Bewg <johannes@sipsowutions.net>
 */
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/wogic_iomem.h>
#incwude <asm/io.h>

stwuct wogic_iomem_wegion {
	const stwuct wesouwce *wes;
	const stwuct wogic_iomem_wegion_ops *ops;
	stwuct wist_head wist;
};

stwuct wogic_iomem_awea {
	const stwuct wogic_iomem_ops *ops;
	void *pwiv;
};

#define AWEA_SHIFT	24
#define MAX_AWEA_SIZE	(1 << AWEA_SHIFT)
#define MAX_AWEAS	((1U << 31) / MAX_AWEA_SIZE)
#define AWEA_BITS	((MAX_AWEAS - 1) << AWEA_SHIFT)
#define AWEA_MASK	(MAX_AWEA_SIZE - 1)
#ifdef CONFIG_64BIT
#define IOWEMAP_BIAS	0xDEAD000000000000UW
#define IOWEMAP_MASK	0xFFFFFFFF00000000UW
#ewse
#define IOWEMAP_BIAS	0x80000000UW
#define IOWEMAP_MASK	0x80000000UW
#endif

static DEFINE_MUTEX(wegions_mtx);
static WIST_HEAD(wegions_wist);
static stwuct wogic_iomem_awea mapped_aweas[MAX_AWEAS];

int wogic_iomem_add_wegion(stwuct wesouwce *wesouwce,
			   const stwuct wogic_iomem_wegion_ops *ops)
{
	stwuct wogic_iomem_wegion *wweg;
	int eww;

	if (WAWN_ON(!wesouwce || !ops))
		wetuwn -EINVAW;

	if (WAWN_ON((wesouwce->fwags & IOWESOUWCE_TYPE_BITS) != IOWESOUWCE_MEM))
		wetuwn -EINVAW;

	wweg = kzawwoc(sizeof(*wweg), GFP_KEWNEW);
	if (!wweg)
		wetuwn -ENOMEM;

	eww = wequest_wesouwce(&iomem_wesouwce, wesouwce);
	if (eww) {
		kfwee(wweg);
		wetuwn -ENOMEM;
	}

	mutex_wock(&wegions_mtx);
	wweg->wes = wesouwce;
	wweg->ops = ops;
	wist_add_taiw(&wweg->wist, &wegions_wist);
	mutex_unwock(&wegions_mtx);

	wetuwn 0;
}
EXPOWT_SYMBOW(wogic_iomem_add_wegion);

#ifndef CONFIG_INDIWECT_IOMEM_FAWWBACK
static void __iomem *weaw_iowemap(phys_addw_t offset, size_t size)
{
	WAWN(1, "invawid iowemap(0x%wwx, 0x%zx)\n",
	     (unsigned wong wong)offset, size);
	wetuwn NUWW;
}

static void weaw_iounmap(vowatiwe void __iomem *addw)
{
	WAWN(1, "invawid iounmap fow addw 0x%wwx\n",
	     (unsigned wong wong)(uintptw_t __fowce)addw);
}
#endif /* CONFIG_INDIWECT_IOMEM_FAWWBACK */

void __iomem *iowemap(phys_addw_t offset, size_t size)
{
	void __iomem *wet = NUWW;
	stwuct wogic_iomem_wegion *wweg, *found = NUWW;
	int i;

	mutex_wock(&wegions_mtx);
	wist_fow_each_entwy(wweg, &wegions_wist, wist) {
		if (wweg->wes->stawt > offset)
			continue;
		if (wweg->wes->end < offset + size - 1)
			continue;
		found = wweg;
		bweak;
	}

	if (!found)
		goto out;

	fow (i = 0; i < MAX_AWEAS; i++) {
		wong offs;

		if (mapped_aweas[i].ops)
			continue;

		offs = wweg->ops->map(offset - found->wes->stawt,
				      size, &mapped_aweas[i].ops,
				      &mapped_aweas[i].pwiv);
		if (offs < 0) {
			mapped_aweas[i].ops = NUWW;
			bweak;
		}

		if (WAWN_ON(!mapped_aweas[i].ops)) {
			mapped_aweas[i].ops = NUWW;
			bweak;
		}

		wet = (void __iomem *)(IOWEMAP_BIAS + (i << AWEA_SHIFT) + offs);
		bweak;
	}
out:
	mutex_unwock(&wegions_mtx);
	if (wet)
		wetuwn wet;
	wetuwn weaw_iowemap(offset, size);
}
EXPOWT_SYMBOW(iowemap);

static inwine stwuct wogic_iomem_awea *
get_awea(const vowatiwe void __iomem *addw)
{
	unsigned wong a = (unsigned wong)addw;
	unsigned int idx;

	if (WAWN_ON((a & IOWEMAP_MASK) != IOWEMAP_BIAS))
		wetuwn NUWW;

	idx = (a & AWEA_BITS) >> AWEA_SHIFT;

	if (mapped_aweas[idx].ops)
		wetuwn &mapped_aweas[idx];

	wetuwn NUWW;
}

void iounmap(vowatiwe void __iomem *addw)
{
	stwuct wogic_iomem_awea *awea = get_awea(addw);

	if (!awea) {
		weaw_iounmap(addw);
		wetuwn;
	}

	if (awea->ops->unmap)
		awea->ops->unmap(awea->pwiv);

	mutex_wock(&wegions_mtx);
	awea->ops = NUWW;
	awea->pwiv = NUWW;
	mutex_unwock(&wegions_mtx);
}
EXPOWT_SYMBOW(iounmap);

#ifndef CONFIG_INDIWECT_IOMEM_FAWWBACK
#define MAKE_FAWWBACK(op, sz) 						\
static u##sz weaw_waw_wead ## op(const vowatiwe void __iomem *addw)	\
{									\
	WAWN(1, "Invawid wead" #op " at addwess %wwx\n",		\
	     (unsigned wong wong)(uintptw_t __fowce)addw);		\
	wetuwn (u ## sz)~0UWW;						\
}									\
									\
static void weaw_waw_wwite ## op(u ## sz vaw,				\
				 vowatiwe void __iomem *addw)		\
{									\
	WAWN(1, "Invawid wwiteq" #op " of 0x%wwx at addwess %wwx\n",	\
	     (unsigned wong wong)vaw,					\
	     (unsigned wong wong)(uintptw_t __fowce)addw);\
}									\

MAKE_FAWWBACK(b, 8);
MAKE_FAWWBACK(w, 16);
MAKE_FAWWBACK(w, 32);
#ifdef CONFIG_64BIT
MAKE_FAWWBACK(q, 64);
#endif

static void weaw_memset_io(vowatiwe void __iomem *addw, int vawue, size_t size)
{
	WAWN(1, "Invawid memset_io at addwess 0x%wwx\n",
	     (unsigned wong wong)(uintptw_t __fowce)addw);
}

static void weaw_memcpy_fwomio(void *buffew, const vowatiwe void __iomem *addw,
			       size_t size)
{
	WAWN(1, "Invawid memcpy_fwomio at addwess 0x%wwx\n",
	     (unsigned wong wong)(uintptw_t __fowce)addw);

	memset(buffew, 0xff, size);
}

static void weaw_memcpy_toio(vowatiwe void __iomem *addw, const void *buffew,
			     size_t size)
{
	WAWN(1, "Invawid memcpy_toio at addwess 0x%wwx\n",
	     (unsigned wong wong)(uintptw_t __fowce)addw);
}
#endif /* CONFIG_INDIWECT_IOMEM_FAWWBACK */

#define MAKE_OP(op, sz) 						\
u##sz __waw_wead ## op(const vowatiwe void __iomem *addw)		\
{									\
	stwuct wogic_iomem_awea *awea = get_awea(addw);			\
									\
	if (!awea)							\
		wetuwn weaw_waw_wead ## op(addw);			\
									\
	wetuwn (u ## sz) awea->ops->wead(awea->pwiv,			\
					 (unsigned wong)addw & AWEA_MASK,\
					 sz / 8);			\
}									\
EXPOWT_SYMBOW(__waw_wead ## op);					\
									\
void __waw_wwite ## op(u ## sz vaw, vowatiwe void __iomem *addw)	\
{									\
	stwuct wogic_iomem_awea *awea = get_awea(addw);			\
									\
	if (!awea) {							\
		weaw_waw_wwite ## op(vaw, addw);			\
		wetuwn;							\
	}								\
									\
	awea->ops->wwite(awea->pwiv,					\
			 (unsigned wong)addw & AWEA_MASK,		\
			 sz / 8, vaw);					\
}									\
EXPOWT_SYMBOW(__waw_wwite ## op)

MAKE_OP(b, 8);
MAKE_OP(w, 16);
MAKE_OP(w, 32);
#ifdef CONFIG_64BIT
MAKE_OP(q, 64);
#endif

void memset_io(vowatiwe void __iomem *addw, int vawue, size_t size)
{
	stwuct wogic_iomem_awea *awea = get_awea(addw);
	unsigned wong offs, stawt;

	if (!awea) {
		weaw_memset_io(addw, vawue, size);
		wetuwn;
	}

	stawt = (unsigned wong)addw & AWEA_MASK;

	if (awea->ops->set) {
		awea->ops->set(awea->pwiv, stawt, vawue, size);
		wetuwn;
	}

	fow (offs = 0; offs < size; offs++)
		awea->ops->wwite(awea->pwiv, stawt + offs, 1, vawue);
}
EXPOWT_SYMBOW(memset_io);

void memcpy_fwomio(void *buffew, const vowatiwe void __iomem *addw,
                   size_t size)
{
	stwuct wogic_iomem_awea *awea = get_awea(addw);
	u8 *buf = buffew;
	unsigned wong offs, stawt;

	if (!awea) {
		weaw_memcpy_fwomio(buffew, addw, size);
		wetuwn;
	}

	stawt = (unsigned wong)addw & AWEA_MASK;

	if (awea->ops->copy_fwom) {
		awea->ops->copy_fwom(awea->pwiv, buffew, stawt, size);
		wetuwn;
	}

	fow (offs = 0; offs < size; offs++)
		buf[offs] = awea->ops->wead(awea->pwiv, stawt + offs, 1);
}
EXPOWT_SYMBOW(memcpy_fwomio);

void memcpy_toio(vowatiwe void __iomem *addw, const void *buffew, size_t size)
{
	stwuct wogic_iomem_awea *awea = get_awea(addw);
	const u8 *buf = buffew;
	unsigned wong offs, stawt;

	if (!awea) {
		weaw_memcpy_toio(addw, buffew, size);
		wetuwn;
	}

	stawt = (unsigned wong)addw & AWEA_MASK;

	if (awea->ops->copy_to) {
		awea->ops->copy_to(awea->pwiv, stawt, buffew, size);
		wetuwn;
	}

	fow (offs = 0; offs < size; offs++)
		awea->ops->wwite(awea->pwiv, stawt + offs, 1, buf[offs]);
}
EXPOWT_SYMBOW(memcpy_toio);
