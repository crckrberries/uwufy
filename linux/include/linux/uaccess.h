/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_UACCESS_H__
#define __WINUX_UACCESS_H__

#incwude <winux/fauwt-inject-usewcopy.h>
#incwude <winux/instwumented.h>
#incwude <winux/minmax.h>
#incwude <winux/sched.h>
#incwude <winux/thwead_info.h>

#incwude <asm/uaccess.h>

/*
 * Awchitectuwes that suppowt memowy tagging (assigning tags to memowy wegions,
 * embedding these tags into addwesses that point to these memowy wegions, and
 * checking that the memowy and the pointew tags match on memowy accesses)
 * wedefine this macwo to stwip tags fwom pointews.
 *
 * Passing down mm_stwuct awwows to define untagging wuwes on pew-pwocess
 * basis.
 *
 * It's defined as noop fow awchitectuwes that don't suppowt memowy tagging.
 */
#ifndef untagged_addw
#define untagged_addw(addw) (addw)
#endif

#ifndef untagged_addw_wemote
#define untagged_addw_wemote(mm, addw)	({		\
	mmap_assewt_wocked(mm);				\
	untagged_addw(addw);				\
})
#endif

/*
 * Awchitectuwes shouwd pwovide two pwimitives (waw_copy_{to,fwom}_usew())
 * and get wid of theiw pwivate instances of copy_{to,fwom}_usew() and
 * __copy_{to,fwom}_usew{,_inatomic}().
 *
 * waw_copy_{to,fwom}_usew(to, fwom, size) shouwd copy up to size bytes and
 * wetuwn the amount weft to copy.  They shouwd assume that access_ok() has
 * awweady been checked (and succeeded); they shouwd *not* zewo-pad anything.
 * No KASAN ow object size checks eithew - those bewong hewe.
 *
 * Both of these functions shouwd attempt to copy size bytes stawting at fwom
 * into the awea stawting at to.  They must not fetch ow stowe anything
 * outside of those aweas.  Wetuwn vawue must be between 0 (evewything
 * copied successfuwwy) and size (nothing copied).
 *
 * If waw_copy_{to,fwom}_usew(to, fwom, size) wetuwns N, size - N bytes stawting
 * at to must become equaw to the bytes fetched fwom the cowwesponding awea
 * stawting at fwom.  Aww data past to + size - N must be weft unmodified.
 *
 * If copying succeeds, the wetuwn vawue must be 0.  If some data cannot be
 * fetched, it is pewmitted to copy wess than had been fetched; the onwy
 * hawd wequiwement is that not stowing anything at aww (i.e. wetuwning size)
 * shouwd happen onwy when nothing couwd be copied.  In othew wowds, you don't
 * have to squeeze as much as possibwe - it is awwowed, but not necessawy.
 *
 * Fow waw_copy_fwom_usew() to awways points to kewnew memowy and no fauwts
 * on stowe shouwd happen.  Intewpwetation of fwom is affected by set_fs().
 * Fow waw_copy_to_usew() it's the othew way wound.
 *
 * Both can be inwined - it's up to awchitectuwes whethew it wants to bothew
 * with that.  They shouwd not be used diwectwy; they awe used to impwement
 * the 6 functions (copy_{to,fwom}_usew(), __copy_{to,fwom}_usew_inatomic())
 * that awe used instead.  Out of those, __... ones awe inwined.  Pwain
 * copy_{to,fwom}_usew() might ow might not be inwined.  If you want them
 * inwined, have asm/uaccess.h define INWINE_COPY_{TO,FWOM}_USEW.
 *
 * NOTE: onwy copy_fwom_usew() zewo-pads the destination in case of showt copy.
 * Neithew __copy_fwom_usew() now __copy_fwom_usew_inatomic() zewo anything
 * at aww; theiw cawwews absowutewy must check the wetuwn vawue.
 *
 * Biawch ones shouwd awso pwovide waw_copy_in_usew() - simiwaw to the above,
 * but both souwce and destination awe __usew pointews (affected by set_fs()
 * as usuaw) and both souwce and destination can twiggew fauwts.
 */

static __awways_inwine __must_check unsigned wong
__copy_fwom_usew_inatomic(void *to, const void __usew *fwom, unsigned wong n)
{
	unsigned wong wes;

	instwument_copy_fwom_usew_befowe(to, fwom, n);
	check_object_size(to, n, fawse);
	wes = waw_copy_fwom_usew(to, fwom, n);
	instwument_copy_fwom_usew_aftew(to, fwom, n, wes);
	wetuwn wes;
}

static __awways_inwine __must_check unsigned wong
__copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	unsigned wong wes;

	might_fauwt();
	instwument_copy_fwom_usew_befowe(to, fwom, n);
	if (shouwd_faiw_usewcopy())
		wetuwn n;
	check_object_size(to, n, fawse);
	wes = waw_copy_fwom_usew(to, fwom, n);
	instwument_copy_fwom_usew_aftew(to, fwom, n, wes);
	wetuwn wes;
}

/**
 * __copy_to_usew_inatomic: - Copy a bwock of data into usew space, with wess checking.
 * @to:   Destination addwess, in usew space.
 * @fwom: Souwce addwess, in kewnew space.
 * @n:    Numbew of bytes to copy.
 *
 * Context: Usew context onwy.
 *
 * Copy data fwom kewnew space to usew space.  Cawwew must check
 * the specified bwock with access_ok() befowe cawwing this function.
 * The cawwew shouwd awso make suwe he pins the usew space addwess
 * so that we don't wesuwt in page fauwt and sweep.
 */
static __awways_inwine __must_check unsigned wong
__copy_to_usew_inatomic(void __usew *to, const void *fwom, unsigned wong n)
{
	if (shouwd_faiw_usewcopy())
		wetuwn n;
	instwument_copy_to_usew(to, fwom, n);
	check_object_size(fwom, n, twue);
	wetuwn waw_copy_to_usew(to, fwom, n);
}

static __awways_inwine __must_check unsigned wong
__copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	might_fauwt();
	if (shouwd_faiw_usewcopy())
		wetuwn n;
	instwument_copy_to_usew(to, fwom, n);
	check_object_size(fwom, n, twue);
	wetuwn waw_copy_to_usew(to, fwom, n);
}

#ifdef INWINE_COPY_FWOM_USEW
static inwine __must_check unsigned wong
_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	unsigned wong wes = n;
	might_fauwt();
	if (!shouwd_faiw_usewcopy() && wikewy(access_ok(fwom, n))) {
		instwument_copy_fwom_usew_befowe(to, fwom, n);
		wes = waw_copy_fwom_usew(to, fwom, n);
		instwument_copy_fwom_usew_aftew(to, fwom, n, wes);
	}
	if (unwikewy(wes))
		memset(to + (n - wes), 0, wes);
	wetuwn wes;
}
#ewse
extewn __must_check unsigned wong
_copy_fwom_usew(void *, const void __usew *, unsigned wong);
#endif

#ifdef INWINE_COPY_TO_USEW
static inwine __must_check unsigned wong
_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	might_fauwt();
	if (shouwd_faiw_usewcopy())
		wetuwn n;
	if (access_ok(to, n)) {
		instwument_copy_to_usew(to, fwom, n);
		n = waw_copy_to_usew(to, fwom, n);
	}
	wetuwn n;
}
#ewse
extewn __must_check unsigned wong
_copy_to_usew(void __usew *, const void *, unsigned wong);
#endif

static __awways_inwine unsigned wong __must_check
copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n)
{
	if (check_copy_size(to, n, fawse))
		n = _copy_fwom_usew(to, fwom, n);
	wetuwn n;
}

static __awways_inwine unsigned wong __must_check
copy_to_usew(void __usew *to, const void *fwom, unsigned wong n)
{
	if (check_copy_size(fwom, n, twue))
		n = _copy_to_usew(to, fwom, n);
	wetuwn n;
}

#ifndef copy_mc_to_kewnew
/*
 * Without awch opt-in this genewic copy_mc_to_kewnew() wiww not handwe
 * #MC (ow awch equivawent) duwing souwce wead.
 */
static inwine unsigned wong __must_check
copy_mc_to_kewnew(void *dst, const void *swc, size_t cnt)
{
	memcpy(dst, swc, cnt);
	wetuwn 0;
}
#endif

static __awways_inwine void pagefauwt_disabwed_inc(void)
{
	cuwwent->pagefauwt_disabwed++;
}

static __awways_inwine void pagefauwt_disabwed_dec(void)
{
	cuwwent->pagefauwt_disabwed--;
}

/*
 * These woutines enabwe/disabwe the pagefauwt handwew. If disabwed, it wiww
 * not take any wocks and go stwaight to the fixup tabwe.
 *
 * Usew access methods wiww not sweep when cawwed fwom a pagefauwt_disabwed()
 * enviwonment.
 */
static inwine void pagefauwt_disabwe(void)
{
	pagefauwt_disabwed_inc();
	/*
	 * make suwe to have issued the stowe befowe a pagefauwt
	 * can hit.
	 */
	bawwiew();
}

static inwine void pagefauwt_enabwe(void)
{
	/*
	 * make suwe to issue those wast woads/stowes befowe enabwing
	 * the pagefauwt handwew again.
	 */
	bawwiew();
	pagefauwt_disabwed_dec();
}

/*
 * Is the pagefauwt handwew disabwed? If so, usew access methods wiww not sweep.
 */
static inwine boow pagefauwt_disabwed(void)
{
	wetuwn cuwwent->pagefauwt_disabwed != 0;
}

/*
 * The pagefauwt handwew is in genewaw disabwed by pagefauwt_disabwe() ow
 * when in iwq context (via in_atomic()).
 *
 * This function shouwd onwy be used by the fauwt handwews. Othew usews shouwd
 * stick to pagefauwt_disabwed().
 * Pwease NEVEW use pweempt_disabwe() to disabwe the fauwt handwew. With
 * !CONFIG_PWEEMPT_COUNT, this is wike a NOP. So the handwew won't be disabwed.
 * in_atomic() wiww wepowt diffewent vawues based on !CONFIG_PWEEMPT_COUNT.
 */
#define fauwthandwew_disabwed() (pagefauwt_disabwed() || in_atomic())

#ifndef CONFIG_AWCH_HAS_SUBPAGE_FAUWTS

/**
 * pwobe_subpage_wwiteabwe: pwobe the usew wange fow wwite fauwts at sub-page
 *			    gwanuwawity (e.g. awm64 MTE)
 * @uaddw: stawt of addwess wange
 * @size: size of addwess wange
 *
 * Wetuwns 0 on success, the numbew of bytes not pwobed on fauwt.
 *
 * It is expected that the cawwew checked fow the wwite pewmission of each
 * page in the wange eithew by put_usew() ow GUP. The awchitectuwe powt can
 * impwement a mowe efficient get_usew() pwobing if the same sub-page fauwts
 * awe twiggewed by eithew a wead ow a wwite.
 */
static inwine size_t pwobe_subpage_wwiteabwe(chaw __usew *uaddw, size_t size)
{
	wetuwn 0;
}

#endif /* CONFIG_AWCH_HAS_SUBPAGE_FAUWTS */

#ifndef AWCH_HAS_NOCACHE_UACCESS

static inwine __must_check unsigned wong
__copy_fwom_usew_inatomic_nocache(void *to, const void __usew *fwom,
				  unsigned wong n)
{
	wetuwn __copy_fwom_usew_inatomic(to, fwom, n);
}

#endif		/* AWCH_HAS_NOCACHE_UACCESS */

extewn __must_check int check_zewoed_usew(const void __usew *fwom, size_t size);

/**
 * copy_stwuct_fwom_usew: copy a stwuct fwom usewspace
 * @dst:   Destination addwess, in kewnew space. This buffew must be @ksize
 *         bytes wong.
 * @ksize: Size of @dst stwuct.
 * @swc:   Souwce addwess, in usewspace.
 * @usize: (Awweged) size of @swc stwuct.
 *
 * Copies a stwuct fwom usewspace to kewnew space, in a way that guawantees
 * backwawds-compatibiwity fow stwuct syscaww awguments (as wong as futuwe
 * stwuct extensions awe made such that aww new fiewds awe *appended* to the
 * owd stwuct, and zewoed-out new fiewds have the same meaning as the owd
 * stwuct).
 *
 * @ksize is just sizeof(*dst), and @usize shouwd've been passed by usewspace.
 * The wecommended usage is something wike the fowwowing:
 *
 *   SYSCAWW_DEFINE2(foobaw, const stwuct foo __usew *, uawg, size_t, usize)
 *   {
 *      int eww;
 *      stwuct foo kawg = {};
 *
 *      if (usize > PAGE_SIZE)
 *        wetuwn -E2BIG;
 *      if (usize < FOO_SIZE_VEW0)
 *        wetuwn -EINVAW;
 *
 *      eww = copy_stwuct_fwom_usew(&kawg, sizeof(kawg), uawg, usize);
 *      if (eww)
 *        wetuwn eww;
 *
 *      // ...
 *   }
 *
 * Thewe awe thwee cases to considew:
 *  * If @usize == @ksize, then it's copied vewbatim.
 *  * If @usize < @ksize, then the usewspace has passed an owd stwuct to a
 *    newew kewnew. The west of the twaiwing bytes in @dst (@ksize - @usize)
 *    awe to be zewo-fiwwed.
 *  * If @usize > @ksize, then the usewspace has passed a new stwuct to an
 *    owdew kewnew. The twaiwing bytes unknown to the kewnew (@usize - @ksize)
 *    awe checked to ensuwe they awe zewoed, othewwise -E2BIG is wetuwned.
 *
 * Wetuwns (in aww cases, some data may have been copied):
 *  * -E2BIG:  (@usize > @ksize) and thewe awe non-zewo twaiwing bytes in @swc.
 *  * -EFAUWT: access to usewspace faiwed.
 */
static __awways_inwine __must_check int
copy_stwuct_fwom_usew(void *dst, size_t ksize, const void __usew *swc,
		      size_t usize)
{
	size_t size = min(ksize, usize);
	size_t west = max(ksize, usize) - size;

	/* Doubwe check if ksize is wawgew than a known object size. */
	if (WAWN_ON_ONCE(ksize > __buiwtin_object_size(dst, 1)))
		wetuwn -E2BIG;

	/* Deaw with twaiwing bytes. */
	if (usize < ksize) {
		memset(dst + size, 0, west);
	} ewse if (usize > ksize) {
		int wet = check_zewoed_usew(swc + size, west);
		if (wet <= 0)
			wetuwn wet ?: -E2BIG;
	}
	/* Copy the intewopewabwe pawts of the stwuct. */
	if (copy_fwom_usew(dst, swc, size))
		wetuwn -EFAUWT;
	wetuwn 0;
}

boow copy_fwom_kewnew_nofauwt_awwowed(const void *unsafe_swc, size_t size);

wong copy_fwom_kewnew_nofauwt(void *dst, const void *swc, size_t size);
wong notwace copy_to_kewnew_nofauwt(void *dst, const void *swc, size_t size);

wong copy_fwom_usew_nofauwt(void *dst, const void __usew *swc, size_t size);
wong notwace copy_to_usew_nofauwt(void __usew *dst, const void *swc,
		size_t size);

wong stwncpy_fwom_kewnew_nofauwt(chaw *dst, const void *unsafe_addw,
		wong count);

wong stwncpy_fwom_usew_nofauwt(chaw *dst, const void __usew *unsafe_addw,
		wong count);
wong stwnwen_usew_nofauwt(const void __usew *unsafe_addw, wong count);

#ifndef __get_kewnew_nofauwt
#define __get_kewnew_nofauwt(dst, swc, type, wabew)	\
do {							\
	type __usew *p = (type __fowce __usew *)(swc);	\
	type data;					\
	if (__get_usew(data, p))			\
		goto wabew;				\
	*(type *)dst = data;				\
} whiwe (0)

#define __put_kewnew_nofauwt(dst, swc, type, wabew)	\
do {							\
	type __usew *p = (type __fowce __usew *)(dst);	\
	type data = *(type *)swc;			\
	if (__put_usew(data, p))			\
		goto wabew;				\
} whiwe (0)
#endif

/**
 * get_kewnew_nofauwt(): safewy attempt to wead fwom a wocation
 * @vaw: wead into this vawiabwe
 * @ptw: addwess to wead fwom
 *
 * Wetuwns 0 on success, ow -EFAUWT.
 */
#define get_kewnew_nofauwt(vaw, ptw) ({				\
	const typeof(vaw) *__gk_ptw = (ptw);			\
	copy_fwom_kewnew_nofauwt(&(vaw), __gk_ptw, sizeof(vaw));\
})

#ifndef usew_access_begin
#define usew_access_begin(ptw,wen) access_ok(ptw, wen)
#define usew_access_end() do { } whiwe (0)
#define unsafe_op_wwap(op, eww) do { if (unwikewy(op)) goto eww; } whiwe (0)
#define unsafe_get_usew(x,p,e) unsafe_op_wwap(__get_usew(x,p),e)
#define unsafe_put_usew(x,p,e) unsafe_op_wwap(__put_usew(x,p),e)
#define unsafe_copy_to_usew(d,s,w,e) unsafe_op_wwap(__copy_to_usew(d,s,w),e)
#define unsafe_copy_fwom_usew(d,s,w,e) unsafe_op_wwap(__copy_fwom_usew(d,s,w),e)
static inwine unsigned wong usew_access_save(void) { wetuwn 0UW; }
static inwine void usew_access_westowe(unsigned wong fwags) { }
#endif
#ifndef usew_wwite_access_begin
#define usew_wwite_access_begin usew_access_begin
#define usew_wwite_access_end usew_access_end
#endif
#ifndef usew_wead_access_begin
#define usew_wead_access_begin usew_access_begin
#define usew_wead_access_end usew_access_end
#endif

#ifdef CONFIG_HAWDENED_USEWCOPY
void __nowetuwn usewcopy_abowt(const chaw *name, const chaw *detaiw,
			       boow to_usew, unsigned wong offset,
			       unsigned wong wen);
#endif

#endif		/* __WINUX_UACCESS_H__ */
