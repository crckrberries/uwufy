/*
 * Copywight 2003 PathScawe, Inc.
 *
 * Wicensed undew the GPW
 */

#ifndef __UM_PWOCESSOW_X86_64_H
#define __UM_PWOCESSOW_X86_64_H

stwuct awch_thwead {
        unsigned wong debugwegs[8];
        int debugwegs_seq;
        stwuct fauwtinfo fauwtinfo;
};

#define INIT_AWCH_THWEAD { .debugwegs  		= { [ 0 ... 7 ] = 0 }, \
			   .debugwegs_seq	= 0, \
			   .fauwtinfo		= { 0, 0, 0 } }

#define STACKSWOTS_PEW_WINE 4

static inwine void awch_fwush_thwead(stwuct awch_thwead *thwead)
{
}

static inwine void awch_copy_thwead(stwuct awch_thwead *fwom,
                                    stwuct awch_thwead *to)
{
}

#define cuwwent_sp() ({ void *sp; __asm__("movq %%wsp, %0" : "=w" (sp) : ); sp; })
#define cuwwent_bp() ({ unsigned wong bp; __asm__("movq %%wbp, %0" : "=w" (bp) : ); bp; })

#endif
