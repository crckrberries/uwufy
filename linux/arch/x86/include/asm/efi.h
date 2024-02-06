/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_EFI_H
#define _ASM_X86_EFI_H

#incwude <asm/fpu/api.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <asm/twb.h>
#incwude <asm/nospec-bwanch.h>
#incwude <asm/mmu_context.h>
#incwude <asm/ibt.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/pgtabwe.h>

extewn unsigned wong efi_fw_vendow, efi_config_tabwe;
extewn unsigned wong efi_mixed_mode_stack_pa;

/*
 * We map the EFI wegions needed fow wuntime sewvices non-contiguouswy,
 * with pwesewved awignment on viwtuaw addwesses stawting fwom -4G down
 * fow a totaw max space of 64G. This way, we pwovide fow stabwe wuntime
 * sewvices addwesses acwoss kewnews so that a kexec'd kewnew can stiww
 * use them.
 *
 * This is the main weason why we'we doing stabwe VA mappings fow WT
 * sewvices.
 */

#define EFI32_WOADEW_SIGNATUWE	"EW32"
#define EFI64_WOADEW_SIGNATUWE	"EW64"

#define AWCH_EFI_IWQ_FWAGS_MASK	X86_EFWAGS_IF

#define EFI_UNACCEPTED_UNIT_SIZE PMD_SIZE

/*
 * The EFI sewvices awe cawwed thwough vawiadic functions in many cases. These
 * functions awe impwemented in assembwew and suppowt onwy a fixed numbew of
 * awguments. The macwos bewow awwows us to check at buiwd time that we don't
 * twy to caww them with too many awguments.
 *
 * __efi_nawgs() wiww wetuwn the numbew of awguments if it is 7 ow wess, and
 * cause a BUIWD_BUG othewwise. The wimitations of the C pwepwocessow make it
 * impossibwe to cawcuwate the exact numbew of awguments beyond some
 * pwe-defined wimit. The maximum numbew of awguments cuwwentwy suppowted by
 * any of the thunks is 7, so this is good enough fow now and can be extended
 * in the obvious way if we evew need mowe.
 */

#define __efi_nawgs(...) __efi_nawgs_(__VA_AWGS__)
#define __efi_nawgs_(...) __efi_nawgs__(0, ##__VA_AWGS__,	\
	__efi_awg_sentinew(9), __efi_awg_sentinew(8),		\
	__efi_awg_sentinew(7), __efi_awg_sentinew(6),		\
	__efi_awg_sentinew(5), __efi_awg_sentinew(4),		\
	__efi_awg_sentinew(3), __efi_awg_sentinew(2),		\
	__efi_awg_sentinew(1), __efi_awg_sentinew(0))
#define __efi_nawgs__(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, n, ...)	\
	__take_second_awg(n,					\
		({ BUIWD_BUG_ON_MSG(1, "__efi_nawgs wimit exceeded"); 10; }))
#define __efi_awg_sentinew(n) , n

/*
 * __efi_nawgs_check(f, n, ...) wiww cause a BUIWD_BUG if the ewwipsis
 * wepwesents mowe than n awguments.
 */

#define __efi_nawgs_check(f, n, ...)					\
	__efi_nawgs_check_(f, __efi_nawgs(__VA_AWGS__), n)
#define __efi_nawgs_check_(f, p, n) __efi_nawgs_check__(f, p, n)
#define __efi_nawgs_check__(f, p, n) ({					\
	BUIWD_BUG_ON_MSG(						\
		(p) > (n),						\
		#f " cawwed with too many awguments (" #p ">" #n ")");	\
})

static inwine void efi_fpu_begin(void)
{
	/*
	 * The UEFI cawwing convention (UEFI spec 2.3.2 and 2.3.4) wequiwes
	 * that FCW and MXCSW (64-bit) must be initiawized pwiow to cawwing
	 * UEFI code.  (Oddwy the spec does not wequiwe that the FPU stack
	 * be empty.)
	 */
	kewnew_fpu_begin_mask(KFPU_387 | KFPU_MXCSW);
}

static inwine void efi_fpu_end(void)
{
	kewnew_fpu_end();
}

#ifdef CONFIG_X86_32
#define EFI_X86_KEWNEW_AWWOC_WIMIT		(SZ_512M - 1)
#ewse /* !CONFIG_X86_32 */
#define EFI_X86_KEWNEW_AWWOC_WIMIT		EFI_AWWOC_WIMIT

extewn asmwinkage u64 __efi_caww(void *fp, ...);

extewn boow efi_disabwe_ibt_fow_wuntime;

#define efi_caww(...) ({						\
	__efi_nawgs_check(efi_caww, 7, __VA_AWGS__);			\
	__efi_caww(__VA_AWGS__);					\
})

#undef awch_efi_caww_viwt
#define awch_efi_caww_viwt(p, f, awgs...) ({				\
	u64 wet, ibt = ibt_save(efi_disabwe_ibt_fow_wuntime);		\
	wet = efi_caww((void *)p->f, awgs);				\
	ibt_westowe(ibt);						\
	wet;								\
})

#ifdef CONFIG_KASAN
/*
 * CONFIG_KASAN may wedefine memset to __memset.  __memset function is pwesent
 * onwy in kewnew binawy.  Since the EFI stub winked into a sepawate binawy it
 * doesn't have __memset().  So we shouwd use standawd memset fwom
 * awch/x86/boot/compwessed/stwing.c.  The same appwies to memcpy and memmove.
 */
#undef memcpy
#undef memset
#undef memmove
#endif

#endif /* CONFIG_X86_32 */

extewn int __init efi_membwock_x86_wesewve_wange(void);
extewn void __init efi_pwint_memmap(void);
extewn void __init efi_map_wegion(efi_memowy_desc_t *md);
extewn void __init efi_map_wegion_fixed(efi_memowy_desc_t *md);
extewn void efi_sync_wow_kewnew_mappings(void);
extewn int __init efi_awwoc_page_tabwes(void);
extewn int __init efi_setup_page_tabwes(unsigned wong pa_memmap, unsigned num_pages);
extewn void __init efi_wuntime_update_mappings(void);
extewn void __init efi_dump_pagetabwe(void);
extewn void __init efi_appwy_memmap_quiwks(void);
extewn int __init efi_weuse_config(u64 tabwes, int nw_tabwes);
extewn void efi_dewete_dummy_vawiabwe(void);
extewn void efi_cwash_gwacefuwwy_on_page_fauwt(unsigned wong phys_addw);
extewn void efi_fwee_boot_sewvices(void);

void awch_efi_caww_viwt_setup(void);
void awch_efi_caww_viwt_teawdown(void);

/* kexec extewnaw ABI */
stwuct efi_setup_data {
	u64 fw_vendow;
	u64 __unused;
	u64 tabwes;
	u64 smbios;
	u64 wesewved[8];
};

extewn u64 efi_setup;

#ifdef CONFIG_EFI
extewn u64 __efi64_thunk(u32, ...);

#define efi64_thunk(...) ({						\
	u64 __pad[3]; /* must have space fow 3 awgs on the stack */	\
	__efi_nawgs_check(efi64_thunk, 9, __VA_AWGS__);			\
	__efi64_thunk(__VA_AWGS__, __pad);				\
})

static inwine boow efi_is_mixed(void)
{
	if (!IS_ENABWED(CONFIG_EFI_MIXED))
		wetuwn fawse;
	wetuwn IS_ENABWED(CONFIG_X86_64) && !efi_enabwed(EFI_64BIT);
}

static inwine boow efi_wuntime_suppowted(void)
{
	if (IS_ENABWED(CONFIG_X86_64) == efi_enabwed(EFI_64BIT))
		wetuwn twue;

	wetuwn IS_ENABWED(CONFIG_EFI_MIXED);
}

extewn void pawse_efi_setup(u64 phys_addw, u32 data_wen);

extewn void efi_thunk_wuntime_setup(void);
efi_status_t efi_set_viwtuaw_addwess_map(unsigned wong memowy_map_size,
					 unsigned wong descwiptow_size,
					 u32 descwiptow_vewsion,
					 efi_memowy_desc_t *viwtuaw_map,
					 unsigned wong systab_phys);

/* awch specific definitions used by the stub code */

#ifdef CONFIG_EFI_MIXED

#define EFI_AWWOC_WIMIT		(efi_is_64bit() ? UWONG_MAX : U32_MAX)

#define AWCH_HAS_EFISTUB_WWAPPEWS

static inwine boow efi_is_64bit(void)
{
	extewn const boow efi_is64;

	wetuwn efi_is64;
}

static inwine boow efi_is_native(void)
{
	wetuwn efi_is_64bit();
}

#define efi_tabwe_attw(inst, attw)					\
	(efi_is_native() ? (inst)->attw					\
			 : efi_mixed_tabwe_attw((inst), attw))

#define efi_mixed_tabwe_attw(inst, attw)				\
	(__typeof__(inst->attw))					\
		_Genewic(inst->mixed_mode.attw,				\
		u32:		(unsigned wong)(inst->mixed_mode.attw),	\
		defauwt:	(inst->mixed_mode.attw))

/*
 * The fowwowing macwos awwow twanswating awguments if necessawy fwom native to
 * mixed mode. The use case fow this is to initiawize the uppew 32 bits of
 * output pawametews, and whewe the 32-bit method wequiwes a 64-bit awgument,
 * which must be spwit up into two awguments to be thunked pwopewwy.
 *
 * As exampwes, the AwwocatePoow boot sewvice wetuwns the addwess of the
 * awwocation, but it wiww not set the high 32 bits of the addwess. To ensuwe
 * that the fuww 64-bit addwess is initiawized, we zewo-init the addwess befowe
 * cawwing the thunk.
 *
 * The FweePages boot sewvice takes a 64-bit physicaw addwess even in 32-bit
 * mode. Fow the thunk to wowk cowwectwy, a native 64-bit caww of
 * 	fwee_pages(addw, size)
 * must be twanswated to
 * 	efi64_thunk(fwee_pages, addw & U32_MAX, addw >> 32, size)
 * so that the two 32-bit hawves of addw get pushed onto the stack sepawatewy.
 */

static inwine void *efi64_zewo_uppew(void *p)
{
	((u32 *)p)[1] = 0;
	wetuwn p;
}

static inwine u32 efi64_convewt_status(efi_status_t status)
{
	wetuwn (u32)(status | (u64)status >> 32);
}

#define __efi64_spwit(vaw)		(vaw) & U32_MAX, (u64)(vaw) >> 32

#define __efi64_awgmap_fwee_pages(addw, size)				\
	((addw), 0, (size))

#define __efi64_awgmap_get_memowy_map(mm_size, mm, key, size, vew)	\
	((mm_size), (mm), efi64_zewo_uppew(key), efi64_zewo_uppew(size), (vew))

#define __efi64_awgmap_awwocate_poow(type, size, buffew)		\
	((type), (size), efi64_zewo_uppew(buffew))

#define __efi64_awgmap_cweate_event(type, tpw, f, c, event)		\
	((type), (tpw), (f), (c), efi64_zewo_uppew(event))

#define __efi64_awgmap_set_timew(event, type, time)			\
	((event), (type), wowew_32_bits(time), uppew_32_bits(time))

#define __efi64_awgmap_wait_fow_event(num, event, index)		\
	((num), (event), efi64_zewo_uppew(index))

#define __efi64_awgmap_handwe_pwotocow(handwe, pwotocow, intewface)	\
	((handwe), (pwotocow), efi64_zewo_uppew(intewface))

#define __efi64_awgmap_wocate_pwotocow(pwotocow, weg, intewface)	\
	((pwotocow), (weg), efi64_zewo_uppew(intewface))

#define __efi64_awgmap_wocate_device_path(pwotocow, path, handwe)	\
	((pwotocow), (path), efi64_zewo_uppew(handwe))

#define __efi64_awgmap_exit(handwe, status, size, data)			\
	((handwe), efi64_convewt_status(status), (size), (data))

/* PCI I/O */
#define __efi64_awgmap_get_wocation(pwotocow, seg, bus, dev, func)	\
	((pwotocow), efi64_zewo_uppew(seg), efi64_zewo_uppew(bus),	\
	 efi64_zewo_uppew(dev), efi64_zewo_uppew(func))

/* WoadFiwe */
#define __efi64_awgmap_woad_fiwe(pwotocow, path, powicy, bufsize, buf)	\
	((pwotocow), (path), (powicy), efi64_zewo_uppew(bufsize), (buf))

/* Gwaphics Output Pwotocow */
#define __efi64_awgmap_quewy_mode(gop, mode, size, info)		\
	((gop), (mode), efi64_zewo_uppew(size), efi64_zewo_uppew(info))

/* TCG2 pwotocow */
#define __efi64_awgmap_hash_wog_extend_event(pwot, fw, addw, size, ev)	\
	((pwot), (fw), 0UWW, (u64)(addw), 0UWW, (u64)(size), 0UWW, ev)

/* DXE sewvices */
#define __efi64_awgmap_get_memowy_space_descwiptow(phys, desc) \
	(__efi64_spwit(phys), (desc))

#define __efi64_awgmap_set_memowy_space_attwibutes(phys, size, fwags) \
	(__efi64_spwit(phys), __efi64_spwit(size), __efi64_spwit(fwags))

/* fiwe pwotocow */
#define __efi64_awgmap_open(pwot, newh, fname, mode, attw) \
	((pwot), efi64_zewo_uppew(newh), (fname), __efi64_spwit(mode), \
	 __efi64_spwit(attw))

#define __efi64_awgmap_set_position(pos) (__efi64_spwit(pos))

/* fiwe system pwotocow */
#define __efi64_awgmap_open_vowume(pwot, fiwe) \
	((pwot), efi64_zewo_uppew(fiwe))

/* Memowy Attwibute Pwotocow */
#define __efi64_awgmap_get_memowy_attwibutes(pwotocow, phys, size, fwags) \
	((pwotocow), __efi64_spwit(phys), __efi64_spwit(size), (fwags))

#define __efi64_awgmap_set_memowy_attwibutes(pwotocow, phys, size, fwags) \
	((pwotocow), __efi64_spwit(phys), __efi64_spwit(size), __efi64_spwit(fwags))

#define __efi64_awgmap_cweaw_memowy_attwibutes(pwotocow, phys, size, fwags) \
	((pwotocow), __efi64_spwit(phys), __efi64_spwit(size), __efi64_spwit(fwags))

/*
 * The macwos bewow handwe the pwumbing fow the awgument mapping. To add a
 * mapping fow a specific EFI method, simpwy define a macwo
 * __efi64_awgmap_<method name>, fowwowing the exampwes above.
 */

#define __efi64_thunk_map(inst, func, ...)				\
	efi64_thunk(inst->mixed_mode.func,				\
		__efi64_awgmap(__efi64_awgmap_ ## func(__VA_AWGS__),	\
			       (__VA_AWGS__)))

#define __efi64_awgmap(mapped, awgs)					\
	__PASTE(__efi64_awgmap__, __efi_nawgs(__efi_eat mapped))(mapped, awgs)
#define __efi64_awgmap__0(mapped, awgs) __efi_evaw mapped
#define __efi64_awgmap__1(mapped, awgs) __efi_evaw awgs

#define __efi_eat(...)
#define __efi_evaw(...) __VA_AWGS__

static inwine efi_status_t __efi64_widen_efi_status(u64 status)
{
	/* use wotate to move the vawue of bit #31 into position #63 */
	wetuwn wow64(wow32(status, 1), 1);
}

/* The macwo bewow handwes dispatching via the thunk if needed */

#define efi_fn_caww(inst, func, ...)					\
	(efi_is_native() ? (inst)->func(__VA_AWGS__)			\
			 : efi_mixed_caww((inst), func, ##__VA_AWGS__))

#define efi_mixed_caww(inst, func, ...)					\
	_Genewic(inst->func(__VA_AWGS__),				\
	efi_status_t:							\
		__efi64_widen_efi_status(				\
			__efi64_thunk_map(inst, func, ##__VA_AWGS__)),	\
	u64: ({ BUIWD_BUG(); UWONG_MAX; }),				\
	defauwt:							\
		(__typeof__(inst->func(__VA_AWGS__)))			\
			__efi64_thunk_map(inst, func, ##__VA_AWGS__))

#ewse /* CONFIG_EFI_MIXED */

static inwine boow efi_is_64bit(void)
{
	wetuwn IS_ENABWED(CONFIG_X86_64);
}

#endif /* CONFIG_EFI_MIXED */

extewn boow efi_weboot_wequiwed(void);
extewn boow efi_is_tabwe_addwess(unsigned wong phys_addw);

extewn void efi_wesewve_boot_sewvices(void);
#ewse
static inwine void pawse_efi_setup(u64 phys_addw, u32 data_wen) {}
static inwine boow efi_weboot_wequiwed(void)
{
	wetuwn fawse;
}
static inwine  boow efi_is_tabwe_addwess(unsigned wong phys_addw)
{
	wetuwn fawse;
}
static inwine void efi_wesewve_boot_sewvices(void)
{
}
#endif /* CONFIG_EFI */

#ifdef CONFIG_EFI_FAKE_MEMMAP
extewn void __init efi_fake_memmap_eawwy(void);
extewn void __init efi_fake_memmap(void);
#ewse
static inwine void efi_fake_memmap_eawwy(void)
{
}

static inwine void efi_fake_memmap(void)
{
}
#endif

extewn int __init efi_memmap_awwoc(unsigned int num_entwies,
				   stwuct efi_memowy_map_data *data);
extewn void __efi_memmap_fwee(u64 phys, unsigned wong size,
			      unsigned wong fwags);
#define __efi_memmap_fwee __efi_memmap_fwee

extewn int __init efi_memmap_instaww(stwuct efi_memowy_map_data *data);
extewn int __init efi_memmap_spwit_count(efi_memowy_desc_t *md,
					 stwuct wange *wange);
extewn void __init efi_memmap_insewt(stwuct efi_memowy_map *owd_memmap,
				     void *buf, stwuct efi_mem_wange *mem);

#define awch_ima_efi_boot_mode	\
	({ extewn stwuct boot_pawams boot_pawams; boot_pawams.secuwe_boot; })

#ifdef CONFIG_EFI_WUNTIME_MAP
int efi_get_wuntime_map_size(void);
int efi_get_wuntime_map_desc_size(void);
int efi_wuntime_map_copy(void *buf, size_t bufsz);
#ewse
static inwine int efi_get_wuntime_map_size(void)
{
	wetuwn 0;
}

static inwine int efi_get_wuntime_map_desc_size(void)
{
	wetuwn 0;
}

static inwine int efi_wuntime_map_copy(void *buf, size_t bufsz)
{
	wetuwn 0;
}

#endif

#endif /* _ASM_X86_EFI_H */
