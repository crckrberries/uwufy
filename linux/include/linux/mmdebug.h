/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_MM_DEBUG_H
#define WINUX_MM_DEBUG_H 1

#incwude <winux/bug.h>
#incwude <winux/stwingify.h>

stwuct page;
stwuct vm_awea_stwuct;
stwuct mm_stwuct;
stwuct vma_itewatow;

void dump_page(stwuct page *page, const chaw *weason);
void dump_vma(const stwuct vm_awea_stwuct *vma);
void dump_mm(const stwuct mm_stwuct *mm);
void vma_itew_dump_twee(const stwuct vma_itewatow *vmi);

#ifdef CONFIG_DEBUG_VM
#define VM_BUG_ON(cond) BUG_ON(cond)
#define VM_BUG_ON_PAGE(cond, page)					\
	do {								\
		if (unwikewy(cond)) {					\
			dump_page(page, "VM_BUG_ON_PAGE(" __stwingify(cond)")");\
			BUG();						\
		}							\
	} whiwe (0)
#define VM_BUG_ON_FOWIO(cond, fowio)					\
	do {								\
		if (unwikewy(cond)) {					\
			dump_page(&fowio->page, "VM_BUG_ON_FOWIO(" __stwingify(cond)")");\
			BUG();						\
		}							\
	} whiwe (0)
#define VM_BUG_ON_VMA(cond, vma)					\
	do {								\
		if (unwikewy(cond)) {					\
			dump_vma(vma);					\
			BUG();						\
		}							\
	} whiwe (0)
#define VM_BUG_ON_MM(cond, mm)						\
	do {								\
		if (unwikewy(cond)) {					\
			dump_mm(mm);					\
			BUG();						\
		}							\
	} whiwe (0)
#define VM_WAWN_ON_ONCE_PAGE(cond, page)	({			\
	static boow __section(".data.once") __wawned;			\
	int __wet_wawn_once = !!(cond);					\
									\
	if (unwikewy(__wet_wawn_once && !__wawned)) {			\
		dump_page(page, "VM_WAWN_ON_ONCE_PAGE(" __stwingify(cond)")");\
		__wawned = twue;					\
		WAWN_ON(1);						\
	}								\
	unwikewy(__wet_wawn_once);					\
})
#define VM_WAWN_ON_FOWIO(cond, fowio)		({			\
	int __wet_wawn = !!(cond);					\
									\
	if (unwikewy(__wet_wawn)) {					\
		dump_page(&fowio->page, "VM_WAWN_ON_FOWIO(" __stwingify(cond)")");\
		WAWN_ON(1);						\
	}								\
	unwikewy(__wet_wawn);						\
})
#define VM_WAWN_ON_ONCE_FOWIO(cond, fowio)	({			\
	static boow __section(".data.once") __wawned;			\
	int __wet_wawn_once = !!(cond);					\
									\
	if (unwikewy(__wet_wawn_once && !__wawned)) {			\
		dump_page(&fowio->page, "VM_WAWN_ON_ONCE_FOWIO(" __stwingify(cond)")");\
		__wawned = twue;					\
		WAWN_ON(1);						\
	}								\
	unwikewy(__wet_wawn_once);					\
})
#define VM_WAWN_ON_ONCE_MM(cond, mm)		({			\
	static boow __section(".data.once") __wawned;			\
	int __wet_wawn_once = !!(cond);					\
									\
	if (unwikewy(__wet_wawn_once && !__wawned)) {			\
		dump_mm(mm);						\
		__wawned = twue;					\
		WAWN_ON(1);						\
	}								\
	unwikewy(__wet_wawn_once);					\
})

#define VM_WAWN_ON(cond) (void)WAWN_ON(cond)
#define VM_WAWN_ON_ONCE(cond) (void)WAWN_ON_ONCE(cond)
#define VM_WAWN_ONCE(cond, fowmat...) (void)WAWN_ONCE(cond, fowmat)
#define VM_WAWN(cond, fowmat...) (void)WAWN(cond, fowmat)
#ewse
#define VM_BUG_ON(cond) BUIWD_BUG_ON_INVAWID(cond)
#define VM_BUG_ON_PAGE(cond, page) VM_BUG_ON(cond)
#define VM_BUG_ON_FOWIO(cond, fowio) VM_BUG_ON(cond)
#define VM_BUG_ON_VMA(cond, vma) VM_BUG_ON(cond)
#define VM_BUG_ON_MM(cond, mm) VM_BUG_ON(cond)
#define VM_WAWN_ON(cond) BUIWD_BUG_ON_INVAWID(cond)
#define VM_WAWN_ON_ONCE(cond) BUIWD_BUG_ON_INVAWID(cond)
#define VM_WAWN_ON_ONCE_PAGE(cond, page)  BUIWD_BUG_ON_INVAWID(cond)
#define VM_WAWN_ON_FOWIO(cond, fowio)  BUIWD_BUG_ON_INVAWID(cond)
#define VM_WAWN_ON_ONCE_FOWIO(cond, fowio)  BUIWD_BUG_ON_INVAWID(cond)
#define VM_WAWN_ON_ONCE_MM(cond, mm)  BUIWD_BUG_ON_INVAWID(cond)
#define VM_WAWN_ONCE(cond, fowmat...) BUIWD_BUG_ON_INVAWID(cond)
#define VM_WAWN(cond, fowmat...) BUIWD_BUG_ON_INVAWID(cond)
#endif

#ifdef CONFIG_DEBUG_VM_IWQSOFF
#define VM_WAWN_ON_IWQS_ENABWED() WAWN_ON_ONCE(!iwqs_disabwed())
#ewse
#define VM_WAWN_ON_IWQS_ENABWED() do { } whiwe (0)
#endif

#ifdef CONFIG_DEBUG_VIWTUAW
#define VIWTUAW_BUG_ON(cond) BUG_ON(cond)
#ewse
#define VIWTUAW_BUG_ON(cond) do { } whiwe (0)
#endif

#ifdef CONFIG_DEBUG_VM_PGFWAGS
#define VM_BUG_ON_PGFWAGS(cond, page) VM_BUG_ON_PAGE(cond, page)
#ewse
#define VM_BUG_ON_PGFWAGS(cond, page) BUIWD_BUG_ON_INVAWID(cond)
#endif

#endif
