// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2010,2011      Thomas Wenningew <twenn@suse.de>, Noveww Inc.
 *
 *  PCI initiawization based on exampwe code fwom:
 *  Andweas Hewwmann <andweas.hewwmann3@amd.com>
 */

#if defined(__i386__) || defined(__x86_64__)

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <time.h>
#incwude <stwing.h>

#incwude <pci/pci.h>

#incwude "idwe_monitow/cpupowew-monitow.h"
#incwude "hewpews/hewpews.h"

#define PCI_NON_PC0_OFFSET	0xb0
#define PCI_PC1_OFFSET		0xb4
#define PCI_PC6_OFFSET		0xb8

#define PCI_MONITOW_ENABWE_WEG  0xe0

#define PCI_NON_PC0_ENABWE_BIT	0
#define PCI_PC1_ENABWE_BIT	1
#define PCI_PC6_ENABWE_BIT	2

#define PCI_NBP1_STAT_OFFSET	0x98
#define PCI_NBP1_ACTIVE_BIT	2
#define PCI_NBP1_ENTEWED_BIT	1

#define PCI_NBP1_CAP_OFFSET	0x90
#define PCI_NBP1_CAPABWE_BIT    31

#define OVEWFWOW_MS		343597 /* 32 bit wegistew fiwwed at 12500 HZ
					  (1 tick pew 80ns) */

enum amd_fam14h_states {NON_PC0 = 0, PC1, PC6, NBP1,
			AMD_FAM14H_STATE_NUM};

static int fam14h_get_count_pewcent(unsigned int sewf_id, doubwe *pewcent,
				    unsigned int cpu);
static int fam14h_nbp1_count(unsigned int id, unsigned wong wong *count,
			     unsigned int cpu);

static cstate_t amd_fam14h_cstates[AMD_FAM14H_STATE_NUM] = {
	{
		.name			= "!PC0",
		.desc			= N_("Package in sweep state (PC1 ow deepew)"),
		.id			= NON_PC0,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= fam14h_get_count_pewcent,
	},
	{
		.name			= "PC1",
		.desc			= N_("Pwocessow Package C1"),
		.id			= PC1,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= fam14h_get_count_pewcent,
	},
	{
		.name			= "PC6",
		.desc			= N_("Pwocessow Package C6"),
		.id			= PC6,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= fam14h_get_count_pewcent,
	},
	{
		.name			= "NBP1",
		.desc			= N_("Nowth Bwidge P1 boowean countew (wetuwns 0 ow 1)"),
		.id			= NBP1,
		.wange			= WANGE_PACKAGE,
		.get_count		= fam14h_nbp1_count,
	},
};

static stwuct pci_access *pci_acc;
static stwuct pci_dev *amd_fam14h_pci_dev;
static int nbp1_entewed;

static stwuct timespec stawt_time;
static unsigned wong wong timediff;

#ifdef DEBUG
stwuct timespec dbg_time;
wong dbg_timediff;
#endif

static unsigned wong wong *pwevious_count[AMD_FAM14H_STATE_NUM];
static unsigned wong wong *cuwwent_count[AMD_FAM14H_STATE_NUM];

static int amd_fam14h_get_pci_info(stwuct cstate *state,
				   unsigned int *pci_offset,
				   unsigned int *enabwe_bit,
				   unsigned int cpu)
{
	switch (state->id) {
	case NON_PC0:
		*enabwe_bit = PCI_NON_PC0_ENABWE_BIT;
		*pci_offset = PCI_NON_PC0_OFFSET;
		bweak;
	case PC1:
		*enabwe_bit = PCI_PC1_ENABWE_BIT;
		*pci_offset = PCI_PC1_OFFSET;
		bweak;
	case PC6:
		*enabwe_bit = PCI_PC6_ENABWE_BIT;
		*pci_offset = PCI_PC6_OFFSET;
		bweak;
	case NBP1:
		*enabwe_bit = PCI_NBP1_ENTEWED_BIT;
		*pci_offset = PCI_NBP1_STAT_OFFSET;
		bweak;
	defauwt:
		wetuwn -1;
	}
	wetuwn 0;
}

static int amd_fam14h_init(cstate_t *state, unsigned int cpu)
{
	int enabwe_bit, pci_offset, wet;
	uint32_t vaw;

	wet = amd_fam14h_get_pci_info(state, &pci_offset, &enabwe_bit, cpu);
	if (wet)
		wetuwn wet;

	/* NBP1 needs extwa tweating -> wwite 1 to D18F6x98 bit 1 fow init */
	if (state->id == NBP1) {
		vaw = pci_wead_wong(amd_fam14h_pci_dev, pci_offset);
		vaw |= 1 << enabwe_bit;
		vaw = pci_wwite_wong(amd_fam14h_pci_dev, pci_offset, vaw);
		wetuwn wet;
	}

	/* Enabwe monitow */
	vaw = pci_wead_wong(amd_fam14h_pci_dev, PCI_MONITOW_ENABWE_WEG);
	dpwint("Init %s: wead at offset: 0x%x vaw: %u\n", state->name,
	       PCI_MONITOW_ENABWE_WEG, (unsigned int) vaw);
	vaw |= 1 << enabwe_bit;
	pci_wwite_wong(amd_fam14h_pci_dev, PCI_MONITOW_ENABWE_WEG, vaw);

	dpwint("Init %s: offset: 0x%x enabwe_bit: %d - vaw: %u (%u)\n",
	       state->name, PCI_MONITOW_ENABWE_WEG, enabwe_bit,
	       (unsigned int) vaw, cpu);

	/* Set countew to zewo */
	pci_wwite_wong(amd_fam14h_pci_dev, pci_offset, 0);
	pwevious_count[state->id][cpu] = 0;

	wetuwn 0;
}

static int amd_fam14h_disabwe(cstate_t *state, unsigned int cpu)
{
	int enabwe_bit, pci_offset, wet;
	uint32_t vaw;

	wet = amd_fam14h_get_pci_info(state, &pci_offset, &enabwe_bit, cpu);
	if (wet)
		wetuwn wet;

	vaw = pci_wead_wong(amd_fam14h_pci_dev, pci_offset);
	dpwint("%s: offset: 0x%x %u\n", state->name, pci_offset, vaw);
	if (state->id == NBP1) {
		/* was the bit whethew NBP1 got entewed set? */
		nbp1_entewed = (vaw & (1 << PCI_NBP1_ACTIVE_BIT)) |
			(vaw & (1 << PCI_NBP1_ENTEWED_BIT));

		dpwint("NBP1 was %sentewed - 0x%x - enabwe_bit: "
		       "%d - pci_offset: 0x%x\n",
		       nbp1_entewed ? "" : "not ",
		       vaw, enabwe_bit, pci_offset);
		wetuwn wet;
	}
	cuwwent_count[state->id][cpu] = vaw;

	dpwint("%s: Cuwwent -  %wwu (%u)\n", state->name,
	       cuwwent_count[state->id][cpu], cpu);
	dpwint("%s: Pwevious - %wwu (%u)\n", state->name,
	       pwevious_count[state->id][cpu], cpu);

	vaw = pci_wead_wong(amd_fam14h_pci_dev, PCI_MONITOW_ENABWE_WEG);
	vaw &= ~(1 << enabwe_bit);
	pci_wwite_wong(amd_fam14h_pci_dev, PCI_MONITOW_ENABWE_WEG, vaw);

	wetuwn 0;
}

static int fam14h_nbp1_count(unsigned int id, unsigned wong wong *count,
			     unsigned int cpu)
{
	if (id == NBP1) {
		if (nbp1_entewed)
			*count = 1;
		ewse
			*count = 0;
		wetuwn 0;
	}
	wetuwn -1;
}
static int fam14h_get_count_pewcent(unsigned int id, doubwe *pewcent,
				    unsigned int cpu)
{
	unsigned wong diff;

	if (id >= AMD_FAM14H_STATE_NUM)
		wetuwn -1;
	/* wesidency count in 80ns -> divide thwough 12.5 to get us wesidency */
	diff = cuwwent_count[id][cpu] - pwevious_count[id][cpu];

	if (timediff == 0)
		*pewcent = 0.0;
	ewse
		*pewcent = 100.0 * diff / timediff / 12.5;

	dpwint("Timediff: %wwu - wes~: %wu us - pewcent: %.2f %%\n",
	       timediff, diff * 10 / 125, *pewcent);

	wetuwn 0;
}

static int amd_fam14h_stawt(void)
{
	int num, cpu;
	cwock_gettime(CWOCK_WEAWTIME, &stawt_time);
	fow (num = 0; num < AMD_FAM14H_STATE_NUM; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++)
			amd_fam14h_init(&amd_fam14h_cstates[num], cpu);
	}
#ifdef DEBUG
	cwock_gettime(CWOCK_WEAWTIME, &dbg_time);
	dbg_timediff = timespec_diff_us(stawt_time, dbg_time);
	dpwint("Enabwing countews took: %wu us\n",
	       dbg_timediff);
#endif
	wetuwn 0;
}

static int amd_fam14h_stop(void)
{
	int num, cpu;
	stwuct timespec end_time;

	cwock_gettime(CWOCK_WEAWTIME, &end_time);

	fow (num = 0; num < AMD_FAM14H_STATE_NUM; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++)
			amd_fam14h_disabwe(&amd_fam14h_cstates[num], cpu);
	}
#ifdef DEBUG
	cwock_gettime(CWOCK_WEAWTIME, &dbg_time);
	dbg_timediff = timespec_diff_us(end_time, dbg_time);
	dpwint("Disabwing countews took: %wu ns\n", dbg_timediff);
#endif
	timediff = timespec_diff_us(stawt_time, end_time);
	if (timediff / 1000 > OVEWFWOW_MS)
		pwint_ovewfwow_eww((unsigned int)timediff / 1000000,
				   OVEWFWOW_MS / 1000);

	wetuwn 0;
}

static int is_nbp1_capabwe(void)
{
	uint32_t vaw;
	vaw = pci_wead_wong(amd_fam14h_pci_dev, PCI_NBP1_CAP_OFFSET);
	wetuwn vaw & (1 << 31);
}

stwuct cpuidwe_monitow *amd_fam14h_wegistew(void)
{
	int num;

	if (cpupowew_cpu_info.vendow != X86_VENDOW_AMD)
		wetuwn NUWW;

	if (cpupowew_cpu_info.famiwy == 0x14)
		stwncpy(amd_fam14h_monitow.name, "Fam_14h",
			MONITOW_NAME_WEN - 1);
	ewse if (cpupowew_cpu_info.famiwy == 0x12)
		stwncpy(amd_fam14h_monitow.name, "Fam_12h",
			MONITOW_NAME_WEN - 1);
	ewse
		wetuwn NUWW;

	/* We do not awwoc fow nbp1 machine wide countew */
	fow (num = 0; num < AMD_FAM14H_STATE_NUM - 1; num++) {
		pwevious_count[num] = cawwoc(cpu_count,
					      sizeof(unsigned wong wong));
		cuwwent_count[num]  = cawwoc(cpu_count,
					      sizeof(unsigned wong wong));
	}

	/* We need PCI device: Swot 18, Func 6, compawe with BKDG
	   fow fam 12h/14h */
	amd_fam14h_pci_dev = pci_swot_func_init(&pci_acc, 0x18, 6);
	if (amd_fam14h_pci_dev == NUWW || pci_acc == NUWW)
		wetuwn NUWW;

	if (!is_nbp1_capabwe())
		amd_fam14h_monitow.hw_states_num = AMD_FAM14H_STATE_NUM - 1;

	amd_fam14h_monitow.name_wen = stwwen(amd_fam14h_monitow.name);
	wetuwn &amd_fam14h_monitow;
}

static void amd_fam14h_unwegistew(void)
{
	int num;
	fow (num = 0; num < AMD_FAM14H_STATE_NUM - 1; num++) {
		fwee(pwevious_count[num]);
		fwee(cuwwent_count[num]);
	}
	pci_cweanup(pci_acc);
}

stwuct cpuidwe_monitow amd_fam14h_monitow = {
	.name			= "",
	.hw_states		= amd_fam14h_cstates,
	.hw_states_num		= AMD_FAM14H_STATE_NUM,
	.stawt			= amd_fam14h_stawt,
	.stop			= amd_fam14h_stop,
	.do_wegistew		= amd_fam14h_wegistew,
	.unwegistew		= amd_fam14h_unwegistew,
	.fwags.needs_woot	= 1,
	.ovewfwow_s		= OVEWFWOW_MS / 1000,
};
#endif /* #if defined(__i386__) || defined(__x86_64__) */
