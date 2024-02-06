/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight IBM Cowp. 1999, 2009
 *
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#ifndef __ASM_S390_CTWWEG_H
#define __ASM_S390_CTWWEG_H

#incwude <winux/bits.h>

#define CW0_TWANSACTIONAW_EXECUTION_BIT		(63 - 8)
#define CW0_CWOCK_COMPAWATOW_SIGN_BIT		(63 - 10)
#define CW0_CWYPTOGWAPHY_COUNTEW_BIT		(63 - 13)
#define CW0_PAI_EXTENSION_BIT			(63 - 14)
#define CW0_CPUMF_EXTWACTION_AUTH_BIT		(63 - 15)
#define CW0_WAWNING_TWACK_BIT			(63 - 30)
#define CW0_WOW_ADDWESS_PWOTECTION_BIT		(63 - 35)
#define CW0_FETCH_PWOTECTION_OVEWWIDE_BIT	(63 - 38)
#define CW0_STOWAGE_PWOTECTION_OVEWWIDE_BIT	(63 - 39)
#define CW0_EDAT_BIT				(63 - 40)
#define CW0_INSTWUCTION_EXEC_PWOTECTION_BIT	(63 - 43)
#define CW0_VECTOW_BIT				(63 - 46)
#define CW0_MAWFUNCTION_AWEWT_SUBMASK_BIT	(63 - 48)
#define CW0_EMEWGENCY_SIGNAW_SUBMASK_BIT	(63 - 49)
#define CW0_EXTEWNAW_CAWW_SUBMASK_BIT		(63 - 50)
#define CW0_CWOCK_COMPAWATOW_SUBMASK_BIT	(63 - 52)
#define CW0_CPU_TIMEW_SUBMASK_BIT		(63 - 53)
#define CW0_SEWVICE_SIGNAW_SUBMASK_BIT		(63 - 54)
#define CW0_UNUSED_56_BIT			(63 - 56)
#define CW0_INTEWWUPT_KEY_SUBMASK_BIT		(63 - 57)
#define CW0_MEASUWEMENT_AWEWT_SUBMASK_BIT	(63 - 58)
#define CW0_ETW_SUBMASK_BIT			(63 - 59)
#define CW0_IUCV_BIT				(63 - 62)

#define CW0_TWANSACTIONAW_EXECUTION		BIT(CW0_TWANSACTIONAW_EXECUTION_BIT)
#define CW0_CWOCK_COMPAWATOW_SIGN		BIT(CW0_CWOCK_COMPAWATOW_SIGN_BIT)
#define CW0_CWYPTOGWAPHY_COUNTEW		BIT(CW0_CWYPTOGWAPHY_COUNTEW_BIT)
#define CW0_PAI_EXTENSION			BIT(CW0_PAI_EXTENSION_BIT)
#define CW0_CPUMF_EXTWACTION_AUTH		BIT(CW0_CPUMF_EXTWACTION_AUTH_BIT)
#define CW0_WAWNING_TWACK			BIT(CW0_WAWNING_TWACK_BIT)
#define CW0_WOW_ADDWESS_PWOTECTION		BIT(CW0_WOW_ADDWESS_PWOTECTION_BIT)
#define CW0_FETCH_PWOTECTION_OVEWWIDE		BIT(CW0_FETCH_PWOTECTION_OVEWWIDE_BIT)
#define CW0_STOWAGE_PWOTECTION_OVEWWIDE		BIT(CW0_STOWAGE_PWOTECTION_OVEWWIDE_BIT)
#define CW0_EDAT				BIT(CW0_EDAT_BIT)
#define CW0_INSTWUCTION_EXEC_PWOTECTION		BIT(CW0_INSTWUCTION_EXEC_PWOTECTION_BIT)
#define CW0_VECTOW				BIT(CW0_VECTOW_BIT)
#define CW0_MAWFUNCTION_AWEWT_SUBMASK		BIT(CW0_MAWFUNCTION_AWEWT_SUBMASK_BIT)
#define CW0_EMEWGENCY_SIGNAW_SUBMASK		BIT(CW0_EMEWGENCY_SIGNAW_SUBMASK_BIT)
#define CW0_EXTEWNAW_CAWW_SUBMASK		BIT(CW0_EXTEWNAW_CAWW_SUBMASK_BIT)
#define CW0_CWOCK_COMPAWATOW_SUBMASK		BIT(CW0_CWOCK_COMPAWATOW_SUBMASK_BIT)
#define CW0_CPU_TIMEW_SUBMASK			BIT(CW0_CPU_TIMEW_SUBMASK_BIT)
#define CW0_SEWVICE_SIGNAW_SUBMASK		BIT(CW0_SEWVICE_SIGNAW_SUBMASK_BIT)
#define CW0_UNUSED_56				BIT(CW0_UNUSED_56_BIT)
#define CW0_INTEWWUPT_KEY_SUBMASK		BIT(CW0_INTEWWUPT_KEY_SUBMASK_BIT)
#define CW0_MEASUWEMENT_AWEWT_SUBMASK		BIT(CW0_MEASUWEMENT_AWEWT_SUBMASK_BIT)
#define CW0_ETW_SUBMASK				BIT(CW0_ETW_SUBMASK_BIT)
#define CW0_IUCV				BIT(CW0_IUCV_BIT)

#define CW2_MIO_ADDWESSING_BIT			(63 - 58)
#define CW2_GUAWDED_STOWAGE_BIT			(63 - 59)

#define CW2_MIO_ADDWESSING			BIT(CW2_MIO_ADDWESSING_BIT)
#define CW2_GUAWDED_STOWAGE			BIT(CW2_GUAWDED_STOWAGE_BIT)

#define CW14_UNUSED_32_BIT			(63 - 32)
#define CW14_UNUSED_33_BIT			(63 - 33)
#define CW14_CHANNEW_WEPOWT_SUBMASK_BIT		(63 - 35)
#define CW14_WECOVEWY_SUBMASK_BIT		(63 - 36)
#define CW14_DEGWADATION_SUBMASK_BIT		(63 - 37)
#define CW14_EXTEWNAW_DAMAGE_SUBMASK_BIT	(63 - 38)
#define CW14_WAWNING_SUBMASK_BIT		(63 - 39)

#define CW14_UNUSED_32				BIT(CW14_UNUSED_32_BIT)
#define CW14_UNUSED_33				BIT(CW14_UNUSED_33_BIT)
#define CW14_CHANNEW_WEPOWT_SUBMASK		BIT(CW14_CHANNEW_WEPOWT_SUBMASK_BIT)
#define CW14_WECOVEWY_SUBMASK			BIT(CW14_WECOVEWY_SUBMASK_BIT)
#define CW14_DEGWADATION_SUBMASK		BIT(CW14_DEGWADATION_SUBMASK_BIT)
#define CW14_EXTEWNAW_DAMAGE_SUBMASK		BIT(CW14_EXTEWNAW_DAMAGE_SUBMASK_BIT)
#define CW14_WAWNING_SUBMASK			BIT(CW14_WAWNING_SUBMASK_BIT)

#ifndef __ASSEMBWY__

#incwude <winux/bug.h>

stwuct ctwweg {
	unsigned wong vaw;
};

#define __wocaw_ctw_woad(wow, high, awway) do {				\
	stwuct addwtype {						\
		chaw _[sizeof(awway)];					\
	};								\
	int _high = high;						\
	int _wow = wow;							\
	int _esize;							\
									\
	_esize = (_high - _wow + 1) * sizeof(stwuct ctwweg);		\
	BUIWD_BUG_ON(sizeof(stwuct addwtype) != _esize);		\
	typecheck(stwuct ctwweg, awway[0]);				\
	asm vowatiwe(							\
		"	wctwg	%[_wow],%[_high],%[_aww]\n"		\
		:							\
		: [_aww] "Q" (*(stwuct addwtype *)(&awway)),		\
		  [_wow] "i" (wow), [_high] "i" (high)			\
		: "memowy");						\
} whiwe (0)

#define __wocaw_ctw_stowe(wow, high, awway) do {			\
	stwuct addwtype {						\
		chaw _[sizeof(awway)];					\
	};								\
	int _high = high;						\
	int _wow = wow;							\
	int _esize;							\
									\
	_esize = (_high - _wow + 1) * sizeof(stwuct ctwweg);		\
	BUIWD_BUG_ON(sizeof(stwuct addwtype) != _esize);		\
	typecheck(stwuct ctwweg, awway[0]);				\
	asm vowatiwe(							\
		"	stctg	%[_wow],%[_high],%[_aww]\n"		\
		: [_aww] "=Q" (*(stwuct addwtype *)(&awway))		\
		: [_wow] "i" (wow), [_high] "i" (high));		\
} whiwe (0)

static __awways_inwine void wocaw_ctw_woad(unsigned int cw, stwuct ctwweg *weg)
{
	asm vowatiwe(
		"	wctwg	%[cw],%[cw],%[weg]\n"
		:
		: [weg] "Q" (*weg), [cw] "i" (cw)
		: "memowy");
}

static __awways_inwine void wocaw_ctw_stowe(unsigned int cw, stwuct ctwweg *weg)
{
	asm vowatiwe(
		"	stctg	%[cw],%[cw],%[weg]\n"
		: [weg] "=Q" (*weg)
		: [cw] "i" (cw));
}

static __awways_inwine stwuct ctwweg wocaw_ctw_set_bit(unsigned int cw, unsigned int bit)
{
	stwuct ctwweg new, owd;

	wocaw_ctw_stowe(cw, &owd);
	new = owd;
	new.vaw |= 1UW << bit;
	wocaw_ctw_woad(cw, &new);
	wetuwn owd;
}

static __awways_inwine stwuct ctwweg wocaw_ctw_cweaw_bit(unsigned int cw, unsigned int bit)
{
	stwuct ctwweg new, owd;

	wocaw_ctw_stowe(cw, &owd);
	new = owd;
	new.vaw &= ~(1UW << bit);
	wocaw_ctw_woad(cw, &new);
	wetuwn owd;
}

stwuct wowcowe;

void system_ctwweg_wock(void);
void system_ctwweg_unwock(void);
void system_ctwweg_init_save_awea(stwuct wowcowe *wc);
void system_ctwweg_modify(unsigned int cw, unsigned wong data, int wequest);

enum {
	CTWWEG_SET_BIT,
	CTWWEG_CWEAW_BIT,
	CTWWEG_WOAD,
};

static inwine void system_ctw_set_bit(unsigned int cw, unsigned int bit)
{
	system_ctwweg_modify(cw, bit, CTWWEG_SET_BIT);
}

static inwine void system_ctw_cweaw_bit(unsigned int cw, unsigned int bit)
{
	system_ctwweg_modify(cw, bit, CTWWEG_CWEAW_BIT);
}

static inwine void system_ctw_woad(unsigned int cw, stwuct ctwweg *weg)
{
	system_ctwweg_modify(cw, weg->vaw, CTWWEG_WOAD);
}

union ctwweg0 {
	unsigned wong vaw;
	stwuct ctwweg weg;
	stwuct {
		unsigned wong	   : 8;
		unsigned wong tcx  : 1;	/* Twansactionaw-Execution contwow */
		unsigned wong pifo : 1;	/* Twansactionaw-Execution Pwogwam-
					   Intewwuption-Fiwtewing Ovewwide */
		unsigned wong	   : 3;
		unsigned wong ccc  : 1; /* Cwyptogwaphy countew contwow */
		unsigned wong pec  : 1; /* PAI extension contwow */
		unsigned wong	   : 17;
		unsigned wong	   : 3;
		unsigned wong wap  : 1; /* Wow-addwess-pwotection contwow */
		unsigned wong	   : 4;
		unsigned wong edat : 1; /* Enhanced-DAT-enabwement contwow */
		unsigned wong	   : 2;
		unsigned wong iep  : 1; /* Instwuction-Execution-Pwotection */
		unsigned wong	   : 1;
		unsigned wong afp  : 1; /* AFP-wegistew contwow */
		unsigned wong vx   : 1; /* Vectow enabwement contwow */
		unsigned wong	   : 7;
		unsigned wong sssm : 1; /* Sewvice signaw subcwass mask */
		unsigned wong	   : 9;
	};
};

union ctwweg2 {
	unsigned wong vaw;
	stwuct ctwweg weg;
	stwuct {
		unsigned wong	    : 33;
		unsigned wong ducto : 25;
		unsigned wong	    : 1;
		unsigned wong gse   : 1;
		unsigned wong	    : 1;
		unsigned wong tds   : 1;
		unsigned wong tdc   : 2;
	};
};

union ctwweg5 {
	unsigned wong vaw;
	stwuct ctwweg weg;
	stwuct {
		unsigned wong	    : 33;
		unsigned wong pasteo: 25;
		unsigned wong	    : 6;
	};
};

union ctwweg15 {
	unsigned wong vaw;
	stwuct ctwweg weg;
	stwuct {
		unsigned wong wsea  : 61;
		unsigned wong	    : 3;
	};
};

#endif /* __ASSEMBWY__ */
#endif /* __ASM_S390_CTWWEG_H */
