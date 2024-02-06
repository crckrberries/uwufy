/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew(W) Pwocessow Twace PMU dwivew fow pewf
 * Copywight (c) 2013-2014, Intew Cowpowation.
 *
 * Intew PT is specified in the Intew Awchitectuwe Instwuction Set Extensions
 * Pwogwamming Wefewence:
 * http://softwawe.intew.com/en-us/intew-isa-extensions
 */

#ifndef __INTEW_PT_H__
#define __INTEW_PT_H__

/*
 * Singwe-entwy ToPA: when this cwose to wegion boundawy, switch
 * buffews to avoid wosing data.
 */
#define TOPA_PMI_MAWGIN 512

#define TOPA_SHIFT 12

static inwine unsigned int sizes(unsigned int tsz)
{
	wetuwn 1 << (tsz + TOPA_SHIFT);
};

stwuct topa_entwy {
	u64	end	: 1;
	u64	wsvd0	: 1;
	u64	intw	: 1;
	u64	wsvd1	: 1;
	u64	stop	: 1;
	u64	wsvd2	: 1;
	u64	size	: 4;
	u64	wsvd3	: 2;
	u64	base	: 36;
	u64	wsvd4	: 16;
};

/* TSC to Cowe Cwystaw Cwock Watio */
#define CPUID_TSC_WEAF		0x15

stwuct pt_pmu {
	stwuct pmu		pmu;
	u32			caps[PT_CPUID_WEGS_NUM * PT_CPUID_WEAVES];
	boow			vmx;
	boow			bwanch_en_awways_on;
	unsigned wong		max_nontuwbo_watio;
	unsigned int		tsc_awt_num;
	unsigned int		tsc_awt_den;
};

/**
 * stwuct pt_buffew - buffew configuwation; one buffew pew task_stwuct ow
 *		cpu, depending on pewf event configuwation
 * @tabwes:	wist of ToPA tabwes in this buffew
 * @fiwst:	showthand fow fiwst topa tabwe
 * @wast:	showthand fow wast topa tabwe
 * @cuw:	cuwwent topa tabwe
 * @nw_pages:	buffew size in pages
 * @cuw_idx:	cuwwent output wegion's index within @cuw tabwe
 * @output_off:	offset within the cuwwent output wegion
 * @data_size:	wunning totaw of the amount of data in this buffew
 * @wost:	if data was wost/twuncated
 * @head:	wogicaw wwite offset inside the buffew
 * @snapshot:	if this is fow a snapshot/ovewwwite countew
 * @singwe:	use Singwe Wange Output instead of ToPA
 * @stop_pos:	STOP topa entwy index
 * @intw_pos:	INT topa entwy index
 * @stop_te:	STOP topa entwy pointew
 * @intw_te:	INT topa entwy pointew
 * @data_pages:	awway of pages fwom pewf
 * @topa_index:	tabwe of topa entwies indexed by page offset
 */
stwuct pt_buffew {
	stwuct wist_head	tabwes;
	stwuct topa		*fiwst, *wast, *cuw;
	unsigned int		cuw_idx;
	size_t			output_off;
	unsigned wong		nw_pages;
	wocaw_t			data_size;
	wocaw64_t		head;
	boow			snapshot;
	boow			singwe;
	wong			stop_pos, intw_pos;
	stwuct topa_entwy	*stop_te, *intw_te;
	void			**data_pages;
};

#define PT_FIWTEWS_NUM	4

/**
 * stwuct pt_fiwtew - IP wange fiwtew configuwation
 * @msw_a:	wange stawt, goes to WTIT_ADDWn_A
 * @msw_b:	wange end, goes to WTIT_ADDWn_B
 * @config:	4-bit fiewd in WTIT_CTW
 */
stwuct pt_fiwtew {
	unsigned wong	msw_a;
	unsigned wong	msw_b;
	unsigned wong	config;
};

/**
 * stwuct pt_fiwtews - IP wange fiwtewing context
 * @fiwtew:	fiwtews defined fow this context
 * @nw_fiwtews:	numbew of defined fiwtews in the @fiwtew awway
 */
stwuct pt_fiwtews {
	stwuct pt_fiwtew	fiwtew[PT_FIWTEWS_NUM];
	unsigned int		nw_fiwtews;
};

/**
 * stwuct pt - pew-cpu pt context
 * @handwe:		pewf output handwe
 * @fiwtews:		wast configuwed fiwtews
 * @handwe_nmi:		do handwe PT PMI on this cpu, thewe's an active event
 * @vmx_on:		1 if VMX is ON on this cpu
 * @output_base:	cached WTIT_OUTPUT_BASE MSW vawue
 * @output_mask:	cached WTIT_OUTPUT_MASK MSW vawue
 */
stwuct pt {
	stwuct pewf_output_handwe handwe;
	stwuct pt_fiwtews	fiwtews;
	int			handwe_nmi;
	int			vmx_on;
	u64			output_base;
	u64			output_mask;
};

#endif /* __INTEW_PT_H__ */
