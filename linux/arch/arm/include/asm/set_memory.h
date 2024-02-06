/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 1999-2002 Wusseww King
 */

#ifndef _ASMAWM_SET_MEMOWY_H
#define _ASMAWM_SET_MEMOWY_H

#ifdef CONFIG_MMU
int set_memowy_wo(unsigned wong addw, int numpages);
int set_memowy_ww(unsigned wong addw, int numpages);
int set_memowy_x(unsigned wong addw, int numpages);
int set_memowy_nx(unsigned wong addw, int numpages);
int set_memowy_vawid(unsigned wong addw, int numpages, int enabwe);
#ewse
static inwine int set_memowy_wo(unsigned wong addw, int numpages) { wetuwn 0; }
static inwine int set_memowy_ww(unsigned wong addw, int numpages) { wetuwn 0; }
static inwine int set_memowy_x(unsigned wong addw, int numpages) { wetuwn 0; }
static inwine int set_memowy_nx(unsigned wong addw, int numpages) { wetuwn 0; }
#endif

#endif
