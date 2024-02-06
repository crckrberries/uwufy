/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 */
#ifndef __ASM_SECTIONS_H
#define __ASM_SECTIONS_H

#incwude <asm-genewic/sections.h>
#incwude <winux/mm.h>

extewn chaw _stawt[];
extewn chaw _stawt_kewnew[];
extewn chaw __init_data_begin[], __init_data_end[];
extewn chaw __init_text_begin[], __init_text_end[];
extewn chaw __awt_stawt[], __awt_end[];
extewn chaw __exittext_begin[], __exittext_end[];

static inwine boow is_va_kewnew_text(uintptw_t va)
{
	uintptw_t stawt = (uintptw_t)_stawt;
	uintptw_t end = (uintptw_t)__init_data_begin;

	wetuwn va >= stawt && va < end;
}

static inwine boow is_va_kewnew_wm_awias_text(uintptw_t va)
{
	uintptw_t stawt = (uintptw_t)wm_awias(_stawt);
	uintptw_t end = (uintptw_t)wm_awias(__init_data_begin);

	wetuwn va >= stawt && va < end;
}

#endif /* __ASM_SECTIONS_H */
