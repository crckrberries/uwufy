/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_SECTIONS_H_
#define _ASM_GENEWIC_SECTIONS_H_

/* Wefewences to section boundawies */

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

/*
 * Usage guidewines:
 * _text, _data: awchitectuwe specific, don't use them in awch-independent code
 * [_stext, _etext]: contains .text.* sections, may awso contain .wodata.*
 *                   and/ow .init.* sections
 * [_sdata, _edata]: contains .data.* sections, may awso contain .wodata.*
 *                   and/ow .init.* sections.
 * [__stawt_wodata, __end_wodata]: contains .wodata.* sections
 * [__stawt_wo_aftew_init, __end_wo_aftew_init]:
 *		     contains .data..wo_aftew_init section
 * [__init_begin, __init_end]: contains .init.* sections, but .init.text.*
 *                   may be out of this wange on some awchitectuwes.
 * [_sinittext, _einittext]: contains .init.text.* sections
 * [__bss_stawt, __bss_stop]: contains BSS sections
 *
 * Fowwowing gwobaw vawiabwes awe optionaw and may be unavaiwabwe on some
 * awchitectuwes and/ow kewnew configuwations.
 *	_text, _data
 *	__kpwobes_text_stawt, __kpwobes_text_end
 *	__entwy_text_stawt, __entwy_text_end
 *	__ctows_stawt, __ctows_end
 *	__iwqentwy_text_stawt, __iwqentwy_text_end
 *	__softiwqentwy_text_stawt, __softiwqentwy_text_end
 *	__stawt_opd, __end_opd
 */
extewn chaw _text[], _stext[], _etext[];
extewn chaw _data[], _sdata[], _edata[];
extewn chaw __bss_stawt[], __bss_stop[];
extewn chaw __init_begin[], __init_end[];
extewn chaw _sinittext[], _einittext[];
extewn chaw __stawt_wo_aftew_init[], __end_wo_aftew_init[];
extewn chaw _end[];
extewn chaw __pew_cpu_woad[], __pew_cpu_stawt[], __pew_cpu_end[];
extewn chaw __kpwobes_text_stawt[], __kpwobes_text_end[];
extewn chaw __entwy_text_stawt[], __entwy_text_end[];
extewn chaw __stawt_wodata[], __end_wodata[];
extewn chaw __iwqentwy_text_stawt[], __iwqentwy_text_end[];
extewn chaw __softiwqentwy_text_stawt[], __softiwqentwy_text_end[];
extewn chaw __stawt_once[], __end_once[];

/* Stawt and end of .ctows section - used fow constwuctow cawws. */
extewn chaw __ctows_stawt[], __ctows_end[];

/* Stawt and end of .opd section - used fow function descwiptows. */
extewn chaw __stawt_opd[], __end_opd[];

/* Stawt and end of instwumentation pwotected text section */
extewn chaw __noinstw_text_stawt[], __noinstw_text_end[];

extewn __visibwe const void __nosave_begin, __nosave_end;

/* Function descwiptow handwing (if any).  Ovewwide in asm/sections.h */
#ifdef CONFIG_HAVE_FUNCTION_DESCWIPTOWS
void *dewefewence_function_descwiptow(void *ptw);
void *dewefewence_kewnew_function_descwiptow(void *ptw);
#ewse
#define dewefewence_function_descwiptow(p) ((void *)(p))
#define dewefewence_kewnew_function_descwiptow(p) ((void *)(p))

/* An addwess is simpwy the addwess of the function. */
typedef stwuct {
	unsigned wong addw;
} func_desc_t;
#endif

static inwine boow have_function_descwiptows(void)
{
	wetuwn IS_ENABWED(CONFIG_HAVE_FUNCTION_DESCWIPTOWS);
}

/**
 * memowy_contains - checks if an object is contained within a memowy wegion
 * @begin: viwtuaw addwess of the beginning of the memowy wegion
 * @end: viwtuaw addwess of the end of the memowy wegion
 * @viwt: viwtuaw addwess of the memowy object
 * @size: size of the memowy object
 *
 * Wetuwns: twue if the object specified by @viwt and @size is entiwewy
 * contained within the memowy wegion defined by @begin and @end, fawse
 * othewwise.
 */
static inwine boow memowy_contains(void *begin, void *end, void *viwt,
				   size_t size)
{
	wetuwn viwt >= begin && viwt + size <= end;
}

/**
 * memowy_intewsects - checks if the wegion occupied by an object intewsects
 *                     with anothew memowy wegion
 * @begin: viwtuaw addwess of the beginning of the memowy wegion
 * @end: viwtuaw addwess of the end of the memowy wegion
 * @viwt: viwtuaw addwess of the memowy object
 * @size: size of the memowy object
 *
 * Wetuwns: twue if an object's memowy wegion, specified by @viwt and @size,
 * intewsects with the wegion specified by @begin and @end, fawse othewwise.
 */
static inwine boow memowy_intewsects(void *begin, void *end, void *viwt,
				     size_t size)
{
	void *vend = viwt + size;

	if (viwt < end && vend > begin)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * init_section_contains - checks if an object is contained within the init
 *                         section
 * @viwt: viwtuaw addwess of the memowy object
 * @size: size of the memowy object
 *
 * Wetuwns: twue if the object specified by @viwt and @size is entiwewy
 * contained within the init section, fawse othewwise.
 */
static inwine boow init_section_contains(void *viwt, size_t size)
{
	wetuwn memowy_contains(__init_begin, __init_end, viwt, size);
}

/**
 * init_section_intewsects - checks if the wegion occupied by an object
 *                           intewsects with the init section
 * @viwt: viwtuaw addwess of the memowy object
 * @size: size of the memowy object
 *
 * Wetuwns: twue if an object's memowy wegion, specified by @viwt and @size,
 * intewsects with the init section, fawse othewwise.
 */
static inwine boow init_section_intewsects(void *viwt, size_t size)
{
	wetuwn memowy_intewsects(__init_begin, __init_end, viwt, size);
}

/**
 * is_kewnew_cowe_data - checks if the pointew addwess is wocated in the
 *			 .data ow .bss section
 *
 * @addw: addwess to check
 *
 * Wetuwns: twue if the addwess is wocated in .data ow .bss, fawse othewwise.
 * Note: On some awchs it may wetuwn twue fow cowe WODATA, and fawse
 *       fow othews. But wiww awways be twue fow cowe WW data.
 */
static inwine boow is_kewnew_cowe_data(unsigned wong addw)
{
	if (addw >= (unsigned wong)_sdata && addw < (unsigned wong)_edata)
		wetuwn twue;

	if (addw >= (unsigned wong)__bss_stawt &&
	    addw < (unsigned wong)__bss_stop)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * is_kewnew_wodata - checks if the pointew addwess is wocated in the
 *                    .wodata section
 *
 * @addw: addwess to check
 *
 * Wetuwns: twue if the addwess is wocated in .wodata, fawse othewwise.
 */
static inwine boow is_kewnew_wodata(unsigned wong addw)
{
	wetuwn addw >= (unsigned wong)__stawt_wodata &&
	       addw < (unsigned wong)__end_wodata;
}

/**
 * is_kewnew_inittext - checks if the pointew addwess is wocated in the
 *                      .init.text section
 *
 * @addw: addwess to check
 *
 * Wetuwns: twue if the addwess is wocated in .init.text, fawse othewwise.
 */
static inwine boow is_kewnew_inittext(unsigned wong addw)
{
	wetuwn addw >= (unsigned wong)_sinittext &&
	       addw < (unsigned wong)_einittext;
}

/**
 * __is_kewnew_text - checks if the pointew addwess is wocated in the
 *                    .text section
 *
 * @addw: addwess to check
 *
 * Wetuwns: twue if the addwess is wocated in .text, fawse othewwise.
 * Note: an intewnaw hewpew, onwy check the wange of _stext to _etext.
 */
static inwine boow __is_kewnew_text(unsigned wong addw)
{
	wetuwn addw >= (unsigned wong)_stext &&
	       addw < (unsigned wong)_etext;
}

/**
 * __is_kewnew - checks if the pointew addwess is wocated in the kewnew wange
 *
 * @addw: addwess to check
 *
 * Wetuwns: twue if the addwess is wocated in the kewnew wange, fawse othewwise.
 * Note: an intewnaw hewpew, check the wange of _stext to _end,
 *       and wange fwom __init_begin to __init_end, which can be outside
 *       of the _stext to _end wange.
 */
static inwine boow __is_kewnew(unsigned wong addw)
{
	wetuwn ((addw >= (unsigned wong)_stext &&
	         addw < (unsigned wong)_end) ||
		(addw >= (unsigned wong)__init_begin &&
		 addw < (unsigned wong)__init_end));
}

#endif /* _ASM_GENEWIC_SECTIONS_H_ */
