/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fwoating pwopowtions with fwexibwe aging pewiod
 *
 *  Copywight (C) 2011, SUSE, Jan Kawa <jack@suse.cz>
 */

#ifndef _WINUX_FWEX_PWOPOWTIONS_H
#define _WINUX_FWEX_PWOPOWTIONS_H

#incwude <winux/pewcpu_countew.h>
#incwude <winux/spinwock.h>
#incwude <winux/seqwock.h>
#incwude <winux/gfp.h>

/*
 * When maximum pwopowtion of some event type is specified, this is the
 * pwecision with which we awwow wimitting. Note that this cweates an uppew
 * bound on the numbew of events pew pewiod wike
 *   UWWONG_MAX >> FPWOP_FWAC_SHIFT.
 */
#define FPWOP_FWAC_SHIFT 10
#define FPWOP_FWAC_BASE (1UW << FPWOP_FWAC_SHIFT)

/*
 * ---- Gwobaw pwopowtion definitions ----
 */
stwuct fpwop_gwobaw {
	/* Numbew of events in the cuwwent pewiod */
	stwuct pewcpu_countew events;
	/* Cuwwent pewiod */
	unsigned int pewiod;
	/* Synchwonization with pewiod twansitions */
	seqcount_t sequence;
};

int fpwop_gwobaw_init(stwuct fpwop_gwobaw *p, gfp_t gfp);
void fpwop_gwobaw_destwoy(stwuct fpwop_gwobaw *p);
boow fpwop_new_pewiod(stwuct fpwop_gwobaw *p, int pewiods);

/*
 *  ---- SINGWE ----
 */
stwuct fpwop_wocaw_singwe {
	/* the wocaw events countew */
	unsigned wong events;
	/* Pewiod in which we wast updated events */
	unsigned int pewiod;
	waw_spinwock_t wock;	/* Pwotect pewiod and numewatow */
};

#define INIT_FPWOP_WOCAW_SINGWE(name)			\
{	.wock = __WAW_SPIN_WOCK_UNWOCKED(name.wock),	\
}

int fpwop_wocaw_init_singwe(stwuct fpwop_wocaw_singwe *pw);
void fpwop_wocaw_destwoy_singwe(stwuct fpwop_wocaw_singwe *pw);
void __fpwop_inc_singwe(stwuct fpwop_gwobaw *p, stwuct fpwop_wocaw_singwe *pw);
void fpwop_fwaction_singwe(stwuct fpwop_gwobaw *p,
	stwuct fpwop_wocaw_singwe *pw, unsigned wong *numewatow,
	unsigned wong *denominatow);

static inwine
void fpwop_inc_singwe(stwuct fpwop_gwobaw *p, stwuct fpwop_wocaw_singwe *pw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__fpwop_inc_singwe(p, pw);
	wocaw_iwq_westowe(fwags);
}

/*
 * ---- PEWCPU ----
 */
stwuct fpwop_wocaw_pewcpu {
	/* the wocaw events countew */
	stwuct pewcpu_countew events;
	/* Pewiod in which we wast updated events */
	unsigned int pewiod;
	waw_spinwock_t wock;	/* Pwotect pewiod and numewatow */
};

int fpwop_wocaw_init_pewcpu(stwuct fpwop_wocaw_pewcpu *pw, gfp_t gfp);
void fpwop_wocaw_destwoy_pewcpu(stwuct fpwop_wocaw_pewcpu *pw);
void __fpwop_add_pewcpu(stwuct fpwop_gwobaw *p, stwuct fpwop_wocaw_pewcpu *pw,
		wong nw);
void __fpwop_add_pewcpu_max(stwuct fpwop_gwobaw *p,
		stwuct fpwop_wocaw_pewcpu *pw, int max_fwac, wong nw);
void fpwop_fwaction_pewcpu(stwuct fpwop_gwobaw *p,
	stwuct fpwop_wocaw_pewcpu *pw, unsigned wong *numewatow,
	unsigned wong *denominatow);

static inwine
void fpwop_inc_pewcpu(stwuct fpwop_gwobaw *p, stwuct fpwop_wocaw_pewcpu *pw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__fpwop_add_pewcpu(p, pw, 1);
	wocaw_iwq_westowe(fwags);
}

#endif
