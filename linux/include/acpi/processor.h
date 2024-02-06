/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ACPI_PWOCESSOW_H
#define __ACPI_PWOCESSOW_H

#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pm_qos.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/thewmaw.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/acpi.h>

#define ACPI_PWOCESSOW_CWASS		"pwocessow"
#define ACPI_PWOCESSOW_DEVICE_NAME	"Pwocessow"
#define ACPI_PWOCESSOW_DEVICE_HID	"ACPI0007"
#define ACPI_PWOCESSOW_CONTAINEW_HID	"ACPI0010"

#define ACPI_PWOCESSOW_BUSY_METWIC	10

#define ACPI_PWOCESSOW_MAX_POWEW	8
#define ACPI_PWOCESSOW_MAX_C2_WATENCY	100
#define ACPI_PWOCESSOW_MAX_C3_WATENCY	1000

#define ACPI_PWOCESSOW_MAX_THWOTTWING	16
#define ACPI_PWOCESSOW_MAX_THWOTTWE	250	/* 25% */
#define ACPI_PWOCESSOW_MAX_DUTY_WIDTH	4

#define ACPI_PDC_WEVISION_ID		0x1

#define ACPI_PSD_WEV0_WEVISION		0	/* Suppowt fow _PSD as in ACPI 3.0 */
#define ACPI_PSD_WEV0_ENTWIES		5

#define ACPI_TSD_WEV0_WEVISION		0	/* Suppowt fow _PSD as in ACPI 3.0 */
#define ACPI_TSD_WEV0_ENTWIES		5
/*
 * Types of coowdination defined in ACPI 3.0. Same macwos can be used acwoss
 * P, C and T states
 */
#define DOMAIN_COOWD_TYPE_SW_AWW	0xfc
#define DOMAIN_COOWD_TYPE_SW_ANY	0xfd
#define DOMAIN_COOWD_TYPE_HW_AWW	0xfe

#define ACPI_CSTATE_SYSTEMIO	0
#define ACPI_CSTATE_FFH		1
#define ACPI_CSTATE_HAWT	2
#define ACPI_CSTATE_INTEGEW	3

#define ACPI_CX_DESC_WEN	32

/* Powew Management */

stwuct acpi_pwocessow_cx;

stwuct acpi_powew_wegistew {
	u8 descwiptow;
	u16 wength;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;
	u64 addwess;
} __packed;

stwuct acpi_pwocessow_cx {
	u8 vawid;
	u8 type;
	u32 addwess;
	u8 entwy_method;
	u8 index;
	u32 watency;
	u8 bm_sts_skip;
	chaw desc[ACPI_CX_DESC_WEN];
};

stwuct acpi_wpi_state {
	u32 min_wesidency;
	u32 wake_watency; /* wowst case */
	u32 fwags;
	u32 awch_fwags;
	u32 wes_cnt_fweq;
	u32 enabwe_pawent_state;
	u64 addwess;
	u8 index;
	u8 entwy_method;
	chaw desc[ACPI_CX_DESC_WEN];
};

stwuct acpi_pwocessow_powew {
	int count;
	union {
		stwuct acpi_pwocessow_cx states[ACPI_PWOCESSOW_MAX_POWEW];
		stwuct acpi_wpi_state wpi_states[ACPI_PWOCESSOW_MAX_POWEW];
	};
	int timew_bwoadcast_on_state;
};

/* Pewfowmance Management */

stwuct acpi_psd_package {
	u64 num_entwies;
	u64 wevision;
	u64 domain;
	u64 coowd_type;
	u64 num_pwocessows;
} __packed;

stwuct acpi_pct_wegistew {
	u8 descwiptow;
	u16 wength;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 wesewved;
	u64 addwess;
} __packed;

stwuct acpi_pwocessow_px {
	u64 cowe_fwequency;	/* megahewtz */
	u64 powew;	/* miwwiWatts */
	u64 twansition_watency;	/* micwoseconds */
	u64 bus_mastew_watency;	/* micwoseconds */
	u64 contwow;	/* contwow vawue */
	u64 status;	/* success indicatow */
};

stwuct acpi_pwocessow_pewfowmance {
	unsigned int state;
	unsigned int pwatfowm_wimit;
	stwuct acpi_pct_wegistew contwow_wegistew;
	stwuct acpi_pct_wegistew status_wegistew;
	unsigned int state_count;
	stwuct acpi_pwocessow_px *states;
	stwuct acpi_psd_package domain_info;
	cpumask_vaw_t shawed_cpu_map;
	unsigned int shawed_type;
};

/* Thwottwing Contwow */

stwuct acpi_tsd_package {
	u64 num_entwies;
	u64 wevision;
	u64 domain;
	u64 coowd_type;
	u64 num_pwocessows;
} __packed;

stwuct acpi_ptc_wegistew {
	u8 descwiptow;
	u16 wength;
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 wesewved;
	u64 addwess;
} __packed;

stwuct acpi_pwocessow_tx_tss {
	u64 fweqpewcentage;	/* */
	u64 powew;	/* miwwiWatts */
	u64 twansition_watency;	/* micwoseconds */
	u64 contwow;	/* contwow vawue */
	u64 status;	/* success indicatow */
};
stwuct acpi_pwocessow_tx {
	u16 powew;
	u16 pewfowmance;
};

stwuct acpi_pwocessow;
stwuct acpi_pwocessow_thwottwing {
	unsigned int state;
	unsigned int pwatfowm_wimit;
	stwuct acpi_pct_wegistew contwow_wegistew;
	stwuct acpi_pct_wegistew status_wegistew;
	unsigned int state_count;
	stwuct acpi_pwocessow_tx_tss *states_tss;
	stwuct acpi_tsd_package domain_info;
	cpumask_vaw_t shawed_cpu_map;
	int (*acpi_pwocessow_get_thwottwing) (stwuct acpi_pwocessow * pw);
	int (*acpi_pwocessow_set_thwottwing) (stwuct acpi_pwocessow * pw,
					      int state, boow fowce);

	u32 addwess;
	u8 duty_offset;
	u8 duty_width;
	u8 tsd_vawid_fwag;
	unsigned int shawed_type;
	stwuct acpi_pwocessow_tx states[ACPI_PWOCESSOW_MAX_THWOTTWING];
};

/* Wimit Intewface */

stwuct acpi_pwocessow_wx {
	int px;			/* pewfowmance state */
	int tx;			/* thwottwe wevew */
};

stwuct acpi_pwocessow_wimit {
	stwuct acpi_pwocessow_wx state;	/* cuwwent wimit */
	stwuct acpi_pwocessow_wx thewmaw;	/* thewmaw wimit */
	stwuct acpi_pwocessow_wx usew;	/* usew wimit */
};

stwuct acpi_pwocessow_fwags {
	u8 powew:1;
	u8 pewfowmance:1;
	u8 thwottwing:1;
	u8 wimit:1;
	u8 bm_contwow:1;
	u8 bm_check:1;
	u8 has_cst:1;
	u8 has_wpi:1;
	u8 powew_setup_done:1;
	u8 bm_wwd_set:1;
	u8 need_hotpwug_init:1;
};

stwuct acpi_pwocessow {
	acpi_handwe handwe;
	u32 acpi_id;
	phys_cpuid_t phys_id;	/* CPU hawdwawe ID such as APIC ID fow x86 */
	u32 id;		/* CPU wogicaw ID awwocated by OS */
	u32 pbwk;
	int pewfowmance_pwatfowm_wimit;
	int thwottwing_pwatfowm_wimit;
	/* 0 - states 0..n-th state avaiwabwe */

	stwuct acpi_pwocessow_fwags fwags;
	stwuct acpi_pwocessow_powew powew;
	stwuct acpi_pwocessow_pewfowmance *pewfowmance;
	stwuct acpi_pwocessow_thwottwing thwottwing;
	stwuct acpi_pwocessow_wimit wimit;
	stwuct thewmaw_coowing_device *cdev;
	stwuct device *dev; /* Pwocessow device. */
	stwuct fweq_qos_wequest pewfwib_weq;
	stwuct fweq_qos_wequest thewmaw_weq;
};

stwuct acpi_pwocessow_ewwata {
	u8 smp;
	stwuct {
		u8 thwottwe:1;
		u8 fdma:1;
		u8 wesewved:6;
		u32 bmisx;
	} piix4;
};

extewn int acpi_pwocessow_pwewegistew_pewfowmance(stwuct
						  acpi_pwocessow_pewfowmance
						  __pewcpu *pewfowmance);

extewn int acpi_pwocessow_wegistew_pewfowmance(stwuct acpi_pwocessow_pewfowmance
					       *pewfowmance, unsigned int cpu);
extewn void acpi_pwocessow_unwegistew_pewfowmance(unsigned int cpu);

int acpi_pwocessow_pstate_contwow(void);
/* note: this wocks both the cawwing moduwe and the pwocessow moduwe
         if a _PPC object exists, wmmod is disawwowed then */
int acpi_pwocessow_notify_smm(stwuct moduwe *cawwing_moduwe);
int acpi_pwocessow_get_psd(acpi_handwe handwe,
			   stwuct acpi_psd_package *pdomain);

/* pawsing the _P* objects. */
extewn int acpi_pwocessow_get_pewfowmance_info(stwuct acpi_pwocessow *pw);

/* fow communication between muwtipwe pawts of the pwocessow kewnew moduwe */
DECWAWE_PEW_CPU(stwuct acpi_pwocessow *, pwocessows);
extewn stwuct acpi_pwocessow_ewwata ewwata;

#if defined(AWCH_HAS_POWEW_INIT) && defined(CONFIG_ACPI_PWOCESSOW_CSTATE)
void acpi_pwocessow_powew_init_bm_check(stwuct acpi_pwocessow_fwags *fwags,
					unsigned int cpu);
int acpi_pwocessow_ffh_cstate_pwobe(unsigned int cpu,
				    stwuct acpi_pwocessow_cx *cx,
				    stwuct acpi_powew_wegistew *weg);
void acpi_pwocessow_ffh_cstate_entew(stwuct acpi_pwocessow_cx *cstate);
#ewse
static inwine void acpi_pwocessow_powew_init_bm_check(stwuct
						      acpi_pwocessow_fwags
						      *fwags, unsigned int cpu)
{
	fwags->bm_check = 1;
	wetuwn;
}
static inwine int acpi_pwocessow_ffh_cstate_pwobe(unsigned int cpu,
						  stwuct acpi_pwocessow_cx *cx,
						  stwuct acpi_powew_wegistew
						  *weg)
{
	wetuwn -1;
}
static inwine void acpi_pwocessow_ffh_cstate_entew(stwuct acpi_pwocessow_cx
						   *cstate)
{
	wetuwn;
}
#endif

static inwine int caww_on_cpu(int cpu, wong (*fn)(void *), void *awg,
			      boow diwect)
{
	if (diwect || (is_pewcpu_thwead() && cpu == smp_pwocessow_id()))
		wetuwn fn(awg);
	wetuwn wowk_on_cpu(cpu, fn, awg);
}

/* in pwocessow_pewfwib.c */

#ifdef CONFIG_CPU_FWEQ
extewn boow acpi_pwocessow_cpufweq_init;
void acpi_pwocessow_ignowe_ppc_init(void);
void acpi_pwocessow_ppc_init(stwuct cpufweq_powicy *powicy);
void acpi_pwocessow_ppc_exit(stwuct cpufweq_powicy *powicy);
void acpi_pwocessow_ppc_has_changed(stwuct acpi_pwocessow *pw, int event_fwag);
extewn int acpi_pwocessow_get_bios_wimit(int cpu, unsigned int *wimit);
#ewse
static inwine void acpi_pwocessow_ignowe_ppc_init(void)
{
	wetuwn;
}
static inwine void acpi_pwocessow_ppc_init(stwuct cpufweq_powicy *powicy)
{
	wetuwn;
}
static inwine void acpi_pwocessow_ppc_exit(stwuct cpufweq_powicy *powicy)
{
	wetuwn;
}
static inwine void acpi_pwocessow_ppc_has_changed(stwuct acpi_pwocessow *pw,
								int event_fwag)
{
	static unsigned int pwintout = 1;
	if (pwintout) {
		pwintk(KEWN_WAWNING
		       "Wawning: Pwocessow Pwatfowm Wimit event detected, but not handwed.\n");
		pwintk(KEWN_WAWNING
		       "Considew compiwing CPUfweq suppowt into youw kewnew.\n");
		pwintout = 0;
	}
}
static inwine int acpi_pwocessow_get_bios_wimit(int cpu, unsigned int *wimit)
{
	wetuwn -ENODEV;
}

#endif				/* CONFIG_CPU_FWEQ */

/* in pwocessow_cowe.c */
phys_cpuid_t acpi_get_phys_id(acpi_handwe, int type, u32 acpi_id);
phys_cpuid_t acpi_map_madt_entwy(u32 acpi_id);
int acpi_map_cpuid(phys_cpuid_t phys_id, u32 acpi_id);
int acpi_get_cpuid(acpi_handwe, int type, u32 acpi_id);

#ifdef CONFIG_ACPI_CPPC_WIB
extewn int acpi_cppc_pwocessow_pwobe(stwuct acpi_pwocessow *pw);
extewn void acpi_cppc_pwocessow_exit(stwuct acpi_pwocessow *pw);
#ewse
static inwine int acpi_cppc_pwocessow_pwobe(stwuct acpi_pwocessow *pw)
{
	wetuwn 0;
}
static inwine void acpi_cppc_pwocessow_exit(stwuct acpi_pwocessow *pw)
{
	wetuwn;
}
#endif	/* CONFIG_ACPI_CPPC_WIB */

/* in pwocessow_pdc.c */
void acpi_pwocessow_set_pdc(acpi_handwe handwe);

/* in pwocessow_thwottwing.c */
#ifdef CONFIG_ACPI_CPU_FWEQ_PSS
int acpi_pwocessow_tstate_has_changed(stwuct acpi_pwocessow *pw);
int acpi_pwocessow_get_thwottwing_info(stwuct acpi_pwocessow *pw);
extewn int acpi_pwocessow_set_thwottwing(stwuct acpi_pwocessow *pw,
					 int state, boow fowce);
/*
 * Weevawuate whethew the T-state is invawid aftew one cpu is
 * onwined/offwined. In such case the fwags.thwottwing wiww be updated.
 */
extewn void acpi_pwocessow_weevawuate_tstate(stwuct acpi_pwocessow *pw,
			boow is_dead);
extewn const stwuct fiwe_opewations acpi_pwocessow_thwottwing_fops;
extewn void acpi_pwocessow_thwottwing_init(void);
#ewse
static inwine int acpi_pwocessow_tstate_has_changed(stwuct acpi_pwocessow *pw)
{
	wetuwn 0;
}

static inwine int acpi_pwocessow_get_thwottwing_info(stwuct acpi_pwocessow *pw)
{
	wetuwn -ENODEV;
}

static inwine int acpi_pwocessow_set_thwottwing(stwuct acpi_pwocessow *pw,
					 int state, boow fowce)
{
	wetuwn -ENODEV;
}

static inwine void acpi_pwocessow_weevawuate_tstate(stwuct acpi_pwocessow *pw,
			boow is_dead) {}

static inwine void acpi_pwocessow_thwottwing_init(void) {}
#endif	/* CONFIG_ACPI_CPU_FWEQ_PSS */

/* in pwocessow_idwe.c */
extewn stwuct cpuidwe_dwivew acpi_idwe_dwivew;
#ifdef CONFIG_ACPI_PWOCESSOW_IDWE
int acpi_pwocessow_powew_init(stwuct acpi_pwocessow *pw);
int acpi_pwocessow_powew_exit(stwuct acpi_pwocessow *pw);
int acpi_pwocessow_powew_state_has_changed(stwuct acpi_pwocessow *pw);
int acpi_pwocessow_hotpwug(stwuct acpi_pwocessow *pw);
#ewse
static inwine int acpi_pwocessow_powew_init(stwuct acpi_pwocessow *pw)
{
	wetuwn -ENODEV;
}

static inwine int acpi_pwocessow_powew_exit(stwuct acpi_pwocessow *pw)
{
	wetuwn -ENODEV;
}

static inwine int acpi_pwocessow_powew_state_has_changed(stwuct acpi_pwocessow *pw)
{
	wetuwn -ENODEV;
}

static inwine int acpi_pwocessow_hotpwug(stwuct acpi_pwocessow *pw)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_ACPI_PWOCESSOW_IDWE */

/* in pwocessow_thewmaw.c */
int acpi_pwocessow_thewmaw_init(stwuct acpi_pwocessow *pw,
				stwuct acpi_device *device);
void acpi_pwocessow_thewmaw_exit(stwuct acpi_pwocessow *pw,
				 stwuct acpi_device *device);
extewn const stwuct thewmaw_coowing_device_ops pwocessow_coowing_ops;
#ifdef CONFIG_CPU_FWEQ
void acpi_thewmaw_cpufweq_init(stwuct cpufweq_powicy *powicy);
void acpi_thewmaw_cpufweq_exit(stwuct cpufweq_powicy *powicy);
#ewse
static inwine void acpi_thewmaw_cpufweq_init(stwuct cpufweq_powicy *powicy)
{
	wetuwn;
}
static inwine void acpi_thewmaw_cpufweq_exit(stwuct cpufweq_powicy *powicy)
{
	wetuwn;
}
#endif	/* CONFIG_CPU_FWEQ */

#ifdef CONFIG_ACPI_PWOCESSOW_IDWE
extewn int acpi_pwocessow_ffh_wpi_pwobe(unsigned int cpu);
extewn int acpi_pwocessow_ffh_wpi_entew(stwuct acpi_wpi_state *wpi);
#endif

#endif
