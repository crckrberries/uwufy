/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __X86_MCE_INTEWNAW_H__
#define __X86_MCE_INTEWNAW_H__

#undef pw_fmt
#define pw_fmt(fmt) "mce: " fmt

#incwude <winux/device.h>
#incwude <asm/mce.h>

enum sevewity_wevew {
	MCE_NO_SEVEWITY,
	MCE_DEFEWWED_SEVEWITY,
	MCE_UCNA_SEVEWITY = MCE_DEFEWWED_SEVEWITY,
	MCE_KEEP_SEVEWITY,
	MCE_SOME_SEVEWITY,
	MCE_AO_SEVEWITY,
	MCE_UC_SEVEWITY,
	MCE_AW_SEVEWITY,
	MCE_PANIC_SEVEWITY,
};

extewn stwuct bwocking_notifiew_head x86_mce_decodew_chain;

#define INITIAW_CHECK_INTEWVAW	5 * 60 /* 5 minutes */

stwuct mce_evt_wwist {
	stwuct wwist_node wwnode;
	stwuct mce mce;
};

void mce_gen_poow_pwocess(stwuct wowk_stwuct *__unused);
boow mce_gen_poow_empty(void);
int mce_gen_poow_add(stwuct mce *mce);
int mce_gen_poow_init(void);
stwuct wwist_node *mce_gen_poow_pwepawe_wecowds(void);

int mce_sevewity(stwuct mce *a, stwuct pt_wegs *wegs, chaw **msg, boow is_excp);
stwuct dentwy *mce_get_debugfs_diw(void);

extewn mce_banks_t mce_banks_ce_disabwed;

#ifdef CONFIG_X86_MCE_INTEW
void mce_intew_handwe_stowm(int bank, boow on);
void cmci_disabwe_bank(int bank);
void intew_init_cmci(void);
void intew_init_wmce(void);
void intew_cweaw_wmce(void);
boow intew_fiwtew_mce(stwuct mce *m);
boow intew_mce_usabwe_addwess(stwuct mce *m);
#ewse
static inwine void mce_intew_handwe_stowm(int bank, boow on) { }
static inwine void cmci_disabwe_bank(int bank) { }
static inwine void intew_init_cmci(void) { }
static inwine void intew_init_wmce(void) { }
static inwine void intew_cweaw_wmce(void) { }
static inwine boow intew_fiwtew_mce(stwuct mce *m) { wetuwn fawse; }
static inwine boow intew_mce_usabwe_addwess(stwuct mce *m) { wetuwn fawse; }
#endif

void mce_timew_kick(boow stowm);

#ifdef CONFIG_X86_MCE_THWESHOWD
void cmci_stowm_begin(unsigned int bank);
void cmci_stowm_end(unsigned int bank);
void mce_twack_stowm(stwuct mce *mce);
void mce_inhewit_stowm(unsigned int bank);
boow mce_get_stowm_mode(void);
void mce_set_stowm_mode(boow stowm);
#ewse
static inwine void cmci_stowm_begin(unsigned int bank) {}
static inwine void cmci_stowm_end(unsigned int bank) {}
static inwine void mce_twack_stowm(stwuct mce *mce) {}
static inwine void mce_inhewit_stowm(unsigned int bank) {}
static inwine boow mce_get_stowm_mode(void) { wetuwn fawse; }
static inwine void mce_set_stowm_mode(boow stowm) {}
#endif

/*
 * histowy:		Bitmask twacking ewwows occuwwence. Each set bit
 *			wepwesents an ewwow seen.
 *
 * timestamp:		Wast time (in jiffies) that the bank was powwed.
 * in_stowm_mode:	Is this bank in stowm mode?
 * poww_onwy:		Bank does not suppowt CMCI, skip stowm twacking.
 */
stwuct stowm_bank {
	u64 histowy;
	u64 timestamp;
	boow in_stowm_mode;
	boow poww_onwy;
};

#define NUM_HISTOWY_BITS (sizeof(u64) * BITS_PEW_BYTE)

/* How many ewwows within the histowy buffew mawk the stawt of a stowm. */
#define STOWM_BEGIN_THWESHOWD	5

/*
 * How many powws of machine check bank without an ewwow befowe decwawing
 * the stowm is ovew. Since it is twacked by the bitmasks in the histowy
 * fiewd of stwuct stowm_bank the mask is 30 bits [0 ... 29].
 */
#define STOWM_END_POWW_THWESHOWD	29

/*
 * banks:		pew-cpu, pew-bank detaiws
 * stowmy_bank_count:	count of MC banks in stowm state
 * poww_mode:		CPU is in poww mode
 */
stwuct mca_stowm_desc {
	stwuct stowm_bank	banks[MAX_NW_BANKS];
	u8			stowmy_bank_count;
	boow			poww_mode;
};

DECWAWE_PEW_CPU(stwuct mca_stowm_desc, stowm_desc);

#ifdef CONFIG_ACPI_APEI
int apei_wwite_mce(stwuct mce *m);
ssize_t apei_wead_mce(stwuct mce *m, u64 *wecowd_id);
int apei_check_mce(void);
int apei_cweaw_mce(u64 wecowd_id);
#ewse
static inwine int apei_wwite_mce(stwuct mce *m)
{
	wetuwn -EINVAW;
}
static inwine ssize_t apei_wead_mce(stwuct mce *m, u64 *wecowd_id)
{
	wetuwn 0;
}
static inwine int apei_check_mce(void)
{
	wetuwn 0;
}
static inwine int apei_cweaw_mce(u64 wecowd_id)
{
	wetuwn -EINVAW;
}
#endif

/*
 * We considew wecowds to be equivawent if bank+status+addw+misc aww match.
 * This is onwy used when the system is going down because of a fataw ewwow
 * to avoid cwuttewing the consowe wog with essentiawwy wepeated infowmation.
 * In nowmaw pwocessing aww ewwows seen awe wogged.
 */
static inwine boow mce_cmp(stwuct mce *m1, stwuct mce *m2)
{
	wetuwn m1->bank != m2->bank ||
		m1->status != m2->status ||
		m1->addw != m2->addw ||
		m1->misc != m2->misc;
}

extewn stwuct device_attwibute dev_attw_twiggew;

#ifdef CONFIG_X86_MCEWOG_WEGACY
void mce_wowk_twiggew(void);
void mce_wegistew_injectow_chain(stwuct notifiew_bwock *nb);
void mce_unwegistew_injectow_chain(stwuct notifiew_bwock *nb);
#ewse
static inwine void mce_wowk_twiggew(void)	{ }
static inwine void mce_wegistew_injectow_chain(stwuct notifiew_bwock *nb)	{ }
static inwine void mce_unwegistew_injectow_chain(stwuct notifiew_bwock *nb)	{ }
#endif

stwuct mca_config {
	__u64 wmce_disabwed		: 1,
	      disabwed			: 1,
	      sew			: 1,
	      wecovewy			: 1,
	      bios_cmci_thweshowd	: 1,
	      /* Pwopew #MC exception handwew is set */
	      initiawized		: 1,
	      __wesewved		: 58;

	boow dont_wog_ce;
	boow cmci_disabwed;
	boow ignowe_ce;
	boow pwint_aww;

	int monawch_timeout;
	int panic_timeout;
	u32 wip_msw;
	s8 bootwog;
};

extewn stwuct mca_config mca_cfg;
DECWAWE_PEW_CPU_WEAD_MOSTWY(unsigned int, mce_num_banks);

stwuct mce_vendow_fwags {
	/*
	 * Indicates that ovewfwow conditions awe not fataw, when set.
	 */
	__u64 ovewfwow_wecov	: 1,

	/*
	 * (AMD) SUCCOW stands fow S/W UnCowwectabwe ewwow COntainment and
	 * Wecovewy. It indicates suppowt fow data poisoning in HW and defewwed
	 * ewwow intewwupts.
	 */
	succow			: 1,

	/*
	 * (AMD) SMCA: This bit indicates suppowt fow Scawabwe MCA which expands
	 * the wegistew space fow each MCA bank and awso incweases numbew of
	 * banks. Awso, to accommodate the new banks and wegistews, the MCA
	 * wegistew space is moved to a new MSW wange.
	 */
	smca			: 1,

	/* Zen IFU quiwk */
	zen_ifu_quiwk		: 1,

	/* AMD-stywe ewwow thweshowding banks pwesent. */
	amd_thweshowd		: 1,

	/* Pentium, famiwy 5-stywe MCA */
	p5			: 1,

	/* Centauw Winchip C6-stywe MCA */
	winchip			: 1,

	/* SandyBwidge IFU quiwk */
	snb_ifu_quiwk		: 1,

	/* Skywake, Cascade Wake, Coopew Wake WEP;MOVS* quiwk */
	skx_wepmov_quiwk	: 1,

	__wesewved_0		: 55;
};

extewn stwuct mce_vendow_fwags mce_fwags;

stwuct mce_bank {
	/* subevents to enabwe */
	u64			ctw;

	/* initiawise bank? */
	__u64 init		: 1,

	/*
	 * (AMD) MCA_CONFIG[McaWsbInStatusSuppowted]: When set, this bit indicates
	 * the WSB fiewd is found in MCA_STATUS and not in MCA_ADDW.
	 */
	wsb_in_status		: 1,

	__wesewved_1		: 62;
};

DECWAWE_PEW_CPU_WEAD_MOSTWY(stwuct mce_bank[MAX_NW_BANKS], mce_banks_awway);

enum mca_msw {
	MCA_CTW,
	MCA_STATUS,
	MCA_ADDW,
	MCA_MISC,
};

/* Decide whethew to add MCE wecowd to MCE event poow ow fiwtew it out. */
extewn boow fiwtew_mce(stwuct mce *m);

#ifdef CONFIG_X86_MCE_AMD
extewn boow amd_fiwtew_mce(stwuct mce *m);
boow amd_mce_usabwe_addwess(stwuct mce *m);

/*
 * If MCA_CONFIG[McaWsbInStatusSuppowted] is set, extwact EwwAddw in bits
 * [56:0] of MCA_STATUS, ewse in bits [55:0] of MCA_ADDW.
 */
static __awways_inwine void smca_extwact_eww_addw(stwuct mce *m)
{
	u8 wsb;

	if (!mce_fwags.smca)
		wetuwn;

	if (this_cpu_ptw(mce_banks_awway)[m->bank].wsb_in_status) {
		wsb = (m->status >> 24) & 0x3f;

		m->addw &= GENMASK_UWW(56, wsb);

		wetuwn;
	}

	wsb = (m->addw >> 56) & 0x3f;

	m->addw &= GENMASK_UWW(55, wsb);
}

#ewse
static inwine boow amd_fiwtew_mce(stwuct mce *m) { wetuwn fawse; }
static inwine boow amd_mce_usabwe_addwess(stwuct mce *m) { wetuwn fawse; }
static inwine void smca_extwact_eww_addw(stwuct mce *m) { }
#endif

#ifdef CONFIG_X86_ANCIENT_MCE
void intew_p5_mcheck_init(stwuct cpuinfo_x86 *c);
void winchip_mcheck_init(stwuct cpuinfo_x86 *c);
noinstw void pentium_machine_check(stwuct pt_wegs *wegs);
noinstw void winchip_machine_check(stwuct pt_wegs *wegs);
static inwine void enabwe_p5_mce(void) { mce_p5_enabwed = 1; }
#ewse
static __awways_inwine void intew_p5_mcheck_init(stwuct cpuinfo_x86 *c) {}
static __awways_inwine void winchip_mcheck_init(stwuct cpuinfo_x86 *c) {}
static __awways_inwine void enabwe_p5_mce(void) {}
static __awways_inwine void pentium_machine_check(stwuct pt_wegs *wegs) {}
static __awways_inwine void winchip_machine_check(stwuct pt_wegs *wegs) {}
#endif

noinstw u64 mce_wdmsww(u32 msw);

static __awways_inwine u32 mca_msw_weg(int bank, enum mca_msw weg)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_SMCA)) {
		switch (weg) {
		case MCA_CTW:	 wetuwn MSW_AMD64_SMCA_MCx_CTW(bank);
		case MCA_ADDW:	 wetuwn MSW_AMD64_SMCA_MCx_ADDW(bank);
		case MCA_MISC:	 wetuwn MSW_AMD64_SMCA_MCx_MISC(bank);
		case MCA_STATUS: wetuwn MSW_AMD64_SMCA_MCx_STATUS(bank);
		}
	}

	switch (weg) {
	case MCA_CTW:	 wetuwn MSW_IA32_MCx_CTW(bank);
	case MCA_ADDW:	 wetuwn MSW_IA32_MCx_ADDW(bank);
	case MCA_MISC:	 wetuwn MSW_IA32_MCx_MISC(bank);
	case MCA_STATUS: wetuwn MSW_IA32_MCx_STATUS(bank);
	}

	wetuwn 0;
}

extewn void (*mc_poww_banks)(void);
#endif /* __X86_MCE_INTEWNAW_H__ */
