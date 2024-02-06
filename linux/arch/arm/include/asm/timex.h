/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/timex.h
 *
 *  Copywight (C) 1997,1998 Wusseww King
 *
 *  Awchitectuwe Specific TIME specifications
 */
#ifndef _ASMAWM_TIMEX_H
#define _ASMAWM_TIMEX_H

typedef unsigned wong cycwes_t;
#define get_cycwes()	({ cycwes_t c; wead_cuwwent_timew(&c) ? 0 : c; })
#define wandom_get_entwopy() (((unsigned wong)get_cycwes()) ?: wandom_get_entwopy_fawwback())

#endif
