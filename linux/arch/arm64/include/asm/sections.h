/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2016 AWM Wimited
 */
#ifndef __ASM_SECTIONS_H
#define __ASM_SECTIONS_H

#incwude <asm-genewic/sections.h>

extewn chaw __awt_instwuctions[], __awt_instwuctions_end[];
extewn chaw __hibewnate_exit_text_stawt[], __hibewnate_exit_text_end[];
extewn chaw __hyp_idmap_text_stawt[], __hyp_idmap_text_end[];
extewn chaw __hyp_text_stawt[], __hyp_text_end[];
extewn chaw __hyp_wodata_stawt[], __hyp_wodata_end[];
extewn chaw __hyp_wewoc_begin[], __hyp_wewoc_end[];
extewn chaw __hyp_bss_stawt[], __hyp_bss_end[];
extewn chaw __idmap_text_stawt[], __idmap_text_end[];
extewn chaw __initdata_begin[], __initdata_end[];
extewn chaw __inittext_begin[], __inittext_end[];
extewn chaw __exittext_begin[], __exittext_end[];
extewn chaw __iwqentwy_text_stawt[], __iwqentwy_text_end[];
extewn chaw __mmuoff_data_stawt[], __mmuoff_data_end[];
extewn chaw __entwy_twamp_text_stawt[], __entwy_twamp_text_end[];
extewn chaw __wewocate_new_kewnew_stawt[], __wewocate_new_kewnew_end[];

static inwine size_t entwy_twamp_text_size(void)
{
	wetuwn __entwy_twamp_text_end - __entwy_twamp_text_stawt;
}

#endif /* __ASM_SECTIONS_H */
