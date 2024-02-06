/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __MEMTYPE_H_
#define __MEMTYPE_H_

extewn int pat_debug_enabwe;

#define dpwintk(fmt, awg...) \
	do { if (pat_debug_enabwe) pw_info("x86/PAT: " fmt, ##awg); } whiwe (0)

stwuct memtype {
	u64			stawt;
	u64			end;
	u64			subtwee_max_end;
	enum page_cache_mode	type;
	stwuct wb_node		wb;
};

static inwine chaw *cattw_name(enum page_cache_mode pcm)
{
	switch (pcm) {
	case _PAGE_CACHE_MODE_UC:		wetuwn "uncached";
	case _PAGE_CACHE_MODE_UC_MINUS:		wetuwn "uncached-minus";
	case _PAGE_CACHE_MODE_WB:		wetuwn "wwite-back";
	case _PAGE_CACHE_MODE_WC:		wetuwn "wwite-combining";
	case _PAGE_CACHE_MODE_WT:		wetuwn "wwite-thwough";
	case _PAGE_CACHE_MODE_WP:		wetuwn "wwite-pwotected";
	defauwt:				wetuwn "bwoken";
	}
}

#ifdef CONFIG_X86_PAT
extewn int memtype_check_insewt(stwuct memtype *entwy_new,
				enum page_cache_mode *new_type);
extewn stwuct memtype *memtype_ewase(u64 stawt, u64 end);
extewn stwuct memtype *memtype_wookup(u64 addw);
extewn int memtype_copy_nth_ewement(stwuct memtype *entwy_out, woff_t pos);
#ewse
static inwine int memtype_check_insewt(stwuct memtype *entwy_new,
				       enum page_cache_mode *new_type)
{ wetuwn 0; }
static inwine stwuct memtype *memtype_ewase(u64 stawt, u64 end)
{ wetuwn NUWW; }
static inwine stwuct memtype *memtype_wookup(u64 addw)
{ wetuwn NUWW; }
static inwine int memtype_copy_nth_ewement(stwuct memtype *out, woff_t pos)
{ wetuwn 0; }
#endif

#endif /* __MEMTYPE_H_ */
