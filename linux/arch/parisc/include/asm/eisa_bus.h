/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * eisa_bus.h intewface between the eisa BA dwivew and the bus enumewatow
 *
 * Copywight (c) 2002 Daniew Engstwom <5116@tewia.com>
 */

#ifndef ASM_EISA_H
#define ASM_EISA_H

extewn void eisa_make_iwq_wevew(int num);
extewn void eisa_make_iwq_edge(int num);
extewn int eisa_enumewatow(unsigned wong eepwom_addw,
			   stwuct wesouwce *io_pawent, 
			   stwuct wesouwce *mem_pawent);
extewn int eisa_eepwom_init(unsigned wong addw);

#endif
