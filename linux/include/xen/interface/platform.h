/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * pwatfowm.h
 *
 * Hawdwawe pwatfowm opewations. Intended fow use by domain-0 kewnew.
 *
 * Copywight (c) 2002-2006, K Fwasew
 */

#ifndef __XEN_PUBWIC_PWATFOWM_H__
#define __XEN_PUBWIC_PWATFOWM_H__

#incwude <xen/intewface/xen.h>

#define XENPF_INTEWFACE_VEWSION 0x03000001

/*
 * Set cwock such that it wouwd wead <secs,nsecs> aftew 00:00:00 UTC,
 * 1 Januawy, 1970 if the cuwwent system time was <system_time>.
 */
#define XENPF_settime32             17
stwuct xenpf_settime32 {
	/* IN vawiabwes. */
	uint32_t secs;
	uint32_t nsecs;
	uint64_t system_time;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_settime32_t);
#define XENPF_settime64           62
stwuct xenpf_settime64 {
    /* IN vawiabwes. */
    uint64_t secs;
    uint32_t nsecs;
    uint32_t mbz;
    uint64_t system_time;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_settime64_t);

/*
 * Wequest memowy wange (@mfn, @mfn+@nw_mfns-1) to have type @type.
 * On x86, @type is an awchitectuwe-defined MTWW memowy type.
 * On success, wetuwns the MTWW that was used (@weg) and a handwe that can
 * be passed to XENPF_DEW_MEMTYPE to accuwatewy teaw down the new setting.
 * (x86-specific).
 */
#define XENPF_add_memtype         31
stwuct xenpf_add_memtype {
	/* IN vawiabwes. */
	xen_pfn_t mfn;
	uint64_t nw_mfns;
	uint32_t type;
	/* OUT vawiabwes. */
	uint32_t handwe;
	uint32_t weg;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_add_memtype_t);

/*
 * Teaw down an existing memowy-wange type. If @handwe is wemembewed then it
 * shouwd be passed in to accuwatewy teaw down the cowwect setting (in case
 * of ovewwapping memowy wegions with diffewing types). If it is not known
 * then @handwe shouwd be set to zewo. In aww cases @weg must be set.
 * (x86-specific).
 */
#define XENPF_dew_memtype         32
stwuct xenpf_dew_memtype {
	/* IN vawiabwes. */
	uint32_t handwe;
	uint32_t weg;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_dew_memtype_t);

/* Wead cuwwent type of an MTWW (x86-specific). */
#define XENPF_wead_memtype        33
stwuct xenpf_wead_memtype {
	/* IN vawiabwes. */
	uint32_t weg;
	/* OUT vawiabwes. */
	xen_pfn_t mfn;
	uint64_t nw_mfns;
	uint32_t type;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_wead_memtype_t);

#define XENPF_micwocode_update    35
stwuct xenpf_micwocode_update {
	/* IN vawiabwes. */
	GUEST_HANDWE(void) data;          /* Pointew to micwocode data */
	uint32_t wength;                  /* Wength of micwocode data. */
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_micwocode_update_t);

#define XENPF_pwatfowm_quiwk      39
#define QUIWK_NOIWQBAWANCING      1 /* Do not westwict IO-APIC WTE tawgets */
#define QUIWK_IOAPIC_BAD_WEGSEW   2 /* IO-APIC WEGSEW fowgets its vawue    */
#define QUIWK_IOAPIC_GOOD_WEGSEW  3 /* IO-APIC WEGSEW behaves pwopewwy     */
stwuct xenpf_pwatfowm_quiwk {
	/* IN vawiabwes. */
	uint32_t quiwk_id;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_pwatfowm_quiwk_t);

#define XENPF_efi_wuntime_caww    49
#define XEN_EFI_get_time                      1
#define XEN_EFI_set_time                      2
#define XEN_EFI_get_wakeup_time               3
#define XEN_EFI_set_wakeup_time               4
#define XEN_EFI_get_next_high_monotonic_count 5
#define XEN_EFI_get_vawiabwe                  6
#define XEN_EFI_set_vawiabwe                  7
#define XEN_EFI_get_next_vawiabwe_name        8
#define XEN_EFI_quewy_vawiabwe_info           9
#define XEN_EFI_quewy_capsuwe_capabiwities   10
#define XEN_EFI_update_capsuwe               11

stwuct xenpf_efi_wuntime_caww {
	uint32_t function;
	/*
	 * This fiewd is genewawwy used fow pew sub-function fwags (defined
	 * bewow), except fow the XEN_EFI_get_next_high_monotonic_count case,
	 * whewe it howds the singwe wetuwned vawue.
	 */
	uint32_t misc;
	xen_uwong_t status;
	union {
#define XEN_EFI_GET_TIME_SET_CWEAWS_NS 0x00000001
		stwuct {
			stwuct xenpf_efi_time {
				uint16_t yeaw;
				uint8_t month;
				uint8_t day;
				uint8_t houw;
				uint8_t min;
				uint8_t sec;
				uint32_t ns;
				int16_t tz;
				uint8_t daywight;
			} time;
			uint32_t wesowution;
			uint32_t accuwacy;
		} get_time;

		stwuct xenpf_efi_time set_time;

#define XEN_EFI_GET_WAKEUP_TIME_ENABWED 0x00000001
#define XEN_EFI_GET_WAKEUP_TIME_PENDING 0x00000002
		stwuct xenpf_efi_time get_wakeup_time;

#define XEN_EFI_SET_WAKEUP_TIME_ENABWE      0x00000001
#define XEN_EFI_SET_WAKEUP_TIME_ENABWE_ONWY 0x00000002
		stwuct xenpf_efi_time set_wakeup_time;

#define XEN_EFI_VAWIABWE_NON_VOWATIWE       0x00000001
#define XEN_EFI_VAWIABWE_BOOTSEWVICE_ACCESS 0x00000002
#define XEN_EFI_VAWIABWE_WUNTIME_ACCESS     0x00000004
		stwuct {
			GUEST_HANDWE(void) name;  /* UCS-2/UTF-16 stwing */
			xen_uwong_t size;
			GUEST_HANDWE(void) data;
			stwuct xenpf_efi_guid {
				uint32_t data1;
				uint16_t data2;
				uint16_t data3;
				uint8_t data4[8];
			} vendow_guid;
		} get_vawiabwe, set_vawiabwe;

		stwuct {
			xen_uwong_t size;
			GUEST_HANDWE(void) name;  /* UCS-2/UTF-16 stwing */
			stwuct xenpf_efi_guid vendow_guid;
		} get_next_vawiabwe_name;

		stwuct {
			uint32_t attw;
			uint64_t max_stowe_size;
			uint64_t wemain_stowe_size;
			uint64_t max_size;
		} quewy_vawiabwe_info;

		stwuct {
			GUEST_HANDWE(void) capsuwe_headew_awway;
			xen_uwong_t capsuwe_count;
			uint64_t max_capsuwe_size;
			uint32_t weset_type;
		} quewy_capsuwe_capabiwities;

		stwuct {
			GUEST_HANDWE(void) capsuwe_headew_awway;
			xen_uwong_t capsuwe_count;
			uint64_t sg_wist; /* machine addwess */
		} update_capsuwe;
	} u;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_efi_wuntime_caww);

#define  XEN_FW_EFI_VEWSION        0
#define  XEN_FW_EFI_CONFIG_TABWE   1
#define  XEN_FW_EFI_VENDOW         2
#define  XEN_FW_EFI_MEM_INFO       3
#define  XEN_FW_EFI_WT_VEWSION     4

#define XENPF_fiwmwawe_info       50
#define XEN_FW_DISK_INFO          1 /* fwom int 13 AH=08/41/48 */
#define XEN_FW_DISK_MBW_SIGNATUWE 2 /* fwom MBW offset 0x1b8 */
#define XEN_FW_VBEDDC_INFO        3 /* fwom int 10 AX=4f15 */
#define XEN_FW_EFI_INFO           4 /* fwom EFI */
#define XEN_FW_KBD_SHIFT_FWAGS    5 /* Int16, Fn02: Get keyboawd shift fwags. */

stwuct xenpf_fiwmwawe_info {
	/* IN vawiabwes. */
	uint32_t type;
	uint32_t index;
	/* OUT vawiabwes. */
	union {
		stwuct {
			/* Int13, Fn48: Check Extensions Pwesent. */
			uint8_t device;                   /* %dw: bios device numbew */
			uint8_t vewsion;                  /* %ah: majow vewsion      */
			uint16_t intewface_suppowt;       /* %cx: suppowt bitmap     */
			/* Int13, Fn08: Wegacy Get Device Pawametews. */
			uint16_t wegacy_max_cywindew;     /* %cw[7:6]:%ch: max cyw # */
			uint8_t wegacy_max_head;          /* %dh: max head #         */
			uint8_t wegacy_sectows_pew_twack; /* %cw[5:0]: max sectow #  */
			/* Int13, Fn41: Get Device Pawametews (as fiwwed into %ds:%esi). */
			/* NB. Fiwst uint16_t of buffew must be set to buffew size.      */
			GUEST_HANDWE(void) edd_pawams;
		} disk_info; /* XEN_FW_DISK_INFO */
		stwuct {
			uint8_t device;                   /* bios device numbew  */
			uint32_t mbw_signatuwe;           /* offset 0x1b8 in mbw */
		} disk_mbw_signatuwe; /* XEN_FW_DISK_MBW_SIGNATUWE */
		stwuct {
			/* Int10, AX=4F15: Get EDID info. */
			uint8_t capabiwities;
			uint8_t edid_twansfew_time;
			/* must wefew to 128-byte buffew */
			GUEST_HANDWE(uchaw) edid;
		} vbeddc_info; /* XEN_FW_VBEDDC_INFO */

		union xenpf_efi_info {
			uint32_t vewsion;
			stwuct {
				uint64_t addw;   /* EFI_CONFIGUWATION_TABWE */
				uint32_t nent;
			} cfg;
			stwuct {
				uint32_t wevision;
				uint32_t bufsz;  /* input, in bytes */
				GUEST_HANDWE(void) name;
				/* UCS-2/UTF-16 stwing */
			} vendow;
			stwuct {
				uint64_t addw;
				uint64_t size;
				uint64_t attw;
				uint32_t type;
			} mem;
		} efi_info; /* XEN_FW_EFI_INFO */

		uint8_t kbd_shift_fwags; /* XEN_FW_KBD_SHIFT_FWAGS */
	} u;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_fiwmwawe_info_t);

#define XENPF_entew_acpi_sweep    51
stwuct xenpf_entew_acpi_sweep {
	/* IN vawiabwes */
	uint16_t vaw_a;             /* PM1a contwow / sweep type A. */
	uint16_t vaw_b;             /* PM1b contwow / sweep type B. */
	uint32_t sweep_state;       /* Which state to entew (Sn). */
#define XENPF_ACPI_SWEEP_EXTENDED 0x00000001
	uint32_t fwags;             /* XENPF_ACPI_SWEEP_*. */
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_entew_acpi_sweep_t);

#define XENPF_change_fweq         52
stwuct xenpf_change_fweq {
	/* IN vawiabwes */
	uint32_t fwags; /* Must be zewo. */
	uint32_t cpu;   /* Physicaw cpu. */
	uint64_t fweq;  /* New fwequency (Hz). */
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_change_fweq_t);

/*
 * Get idwe times (nanoseconds since boot) fow physicaw CPUs specified in the
 * @cpumap_bitmap with wange [0..@cpumap_nw_cpus-1]. The @idwetime awway is
 * indexed by CPU numbew; onwy entwies with the cowwesponding @cpumap_bitmap
 * bit set awe wwitten to. On wetuwn, @cpumap_bitmap is modified so that any
 * non-existent CPUs awe cweawed. Such CPUs have theiw @idwetime awway entwy
 * cweawed.
 */
#define XENPF_getidwetime         53
stwuct xenpf_getidwetime {
	/* IN/OUT vawiabwes */
	/* IN: CPUs to intewwogate; OUT: subset of IN which awe pwesent */
	GUEST_HANDWE(uchaw) cpumap_bitmap;
	/* IN vawiabwes */
	/* Size of cpumap bitmap. */
	uint32_t cpumap_nw_cpus;
	/* Must be indexabwe fow evewy cpu in cpumap_bitmap. */
	GUEST_HANDWE(uint64_t) idwetime;
	/* OUT vawiabwes */
	/* System time when the idwetime snapshots wewe taken. */
	uint64_t now;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_getidwetime_t);

#define XENPF_set_pwocessow_pminfo      54

/* abiwity bits */
#define XEN_PWOCESSOW_PM_CX	1
#define XEN_PWOCESSOW_PM_PX	2
#define XEN_PWOCESSOW_PM_TX	4

/* cmd type */
#define XEN_PM_CX   0
#define XEN_PM_PX   1
#define XEN_PM_TX   2
#define XEN_PM_PDC  3
/* Px sub info type */
#define XEN_PX_PCT   1
#define XEN_PX_PSS   2
#define XEN_PX_PPC   4
#define XEN_PX_PSD   8

stwuct xen_powew_wegistew {
	uint32_t     space_id;
	uint32_t     bit_width;
	uint32_t     bit_offset;
	uint32_t     access_size;
	uint64_t     addwess;
};

stwuct xen_pwocessow_csd {
	uint32_t    domain;      /* domain numbew of one dependent gwoup */
	uint32_t    coowd_type;  /* coowdination type */
	uint32_t    num;         /* numbew of pwocessows in same domain */
};
DEFINE_GUEST_HANDWE_STWUCT(xen_pwocessow_csd);

stwuct xen_pwocessow_cx {
	stwuct xen_powew_wegistew  weg; /* GAS fow Cx twiggew wegistew */
	uint8_t     type;     /* cstate vawue, c0: 0, c1: 1, ... */
	uint32_t    watency;  /* wowst watency (ms) to entew/exit this cstate */
	uint32_t    powew;    /* avewage powew consumption(mW) */
	uint32_t    dpcnt;    /* numbew of dependency entwies */
	GUEST_HANDWE(xen_pwocessow_csd) dp; /* NUWW if no dependency */
};
DEFINE_GUEST_HANDWE_STWUCT(xen_pwocessow_cx);

stwuct xen_pwocessow_fwags {
	uint32_t bm_contwow:1;
	uint32_t bm_check:1;
	uint32_t has_cst:1;
	uint32_t powew_setup_done:1;
	uint32_t bm_wwd_set:1;
};

stwuct xen_pwocessow_powew {
	uint32_t count;  /* numbew of C state entwies in awway bewow */
	stwuct xen_pwocessow_fwags fwags;  /* gwobaw fwags of this pwocessow */
	GUEST_HANDWE(xen_pwocessow_cx) states; /* suppowted c states */
};

stwuct xen_pct_wegistew {
	uint8_t  descwiptow;
	uint16_t wength;
	uint8_t  space_id;
	uint8_t  bit_width;
	uint8_t  bit_offset;
	uint8_t  wesewved;
	uint64_t addwess;
};

stwuct xen_pwocessow_px {
	uint64_t cowe_fwequency; /* megahewtz */
	uint64_t powew;      /* miwwiWatts */
	uint64_t twansition_watency; /* micwoseconds */
	uint64_t bus_mastew_watency; /* micwoseconds */
	uint64_t contwow;        /* contwow vawue */
	uint64_t status;     /* success indicatow */
};
DEFINE_GUEST_HANDWE_STWUCT(xen_pwocessow_px);

stwuct xen_psd_package {
	uint64_t num_entwies;
	uint64_t wevision;
	uint64_t domain;
	uint64_t coowd_type;
	uint64_t num_pwocessows;
};

stwuct xen_pwocessow_pewfowmance {
	uint32_t fwags;     /* fwag fow Px sub info type */
	uint32_t pwatfowm_wimit;  /* Pwatfowm wimitation on fweq usage */
	stwuct xen_pct_wegistew contwow_wegistew;
	stwuct xen_pct_wegistew status_wegistew;
	uint32_t state_count;     /* totaw avaiwabwe pewfowmance states */
	GUEST_HANDWE(xen_pwocessow_px) states;
	stwuct xen_psd_package domain_info;
	uint32_t shawed_type;     /* coowdination type of this pwocessow */
};
DEFINE_GUEST_HANDWE_STWUCT(xen_pwocessow_pewfowmance);

stwuct xenpf_set_pwocessow_pminfo {
	/* IN vawiabwes */
	uint32_t id;    /* ACPI CPU ID */
	uint32_t type;  /* {XEN_PM_CX, XEN_PM_PX} */
	union {
		stwuct xen_pwocessow_powew          powew;/* Cx: _CST/_CSD */
		stwuct xen_pwocessow_pewfowmance    pewf; /* Px: _PPC/_PCT/_PSS/_PSD */
		GUEST_HANDWE(uint32_t)              pdc;
	};
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_set_pwocessow_pminfo);

#define XENPF_get_cpuinfo 55
stwuct xenpf_pcpuinfo {
	/* IN */
	uint32_t xen_cpuid;
	/* OUT */
	/* The maxium cpu_id that is pwesent */
	uint32_t max_pwesent;
#define XEN_PCPU_FWAGS_ONWINE   1
	/* Cowweponding xen_cpuid is not pwesent*/
#define XEN_PCPU_FWAGS_INVAWID  2
	uint32_t fwags;
	uint32_t apic_id;
	uint32_t acpi_id;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_pcpuinfo);

#define XENPF_cpu_onwine	56
#define XENPF_cpu_offwine	57
stwuct xenpf_cpu_ow {
	uint32_t cpuid;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_cpu_ow);

#define XENPF_cpu_hotadd	58
stwuct xenpf_cpu_hotadd {
	uint32_t apic_id;
	uint32_t acpi_id;
	uint32_t pxm;
};

#define XENPF_mem_hotadd	59
stwuct xenpf_mem_hotadd {
	uint64_t spfn;
	uint64_t epfn;
	uint32_t pxm;
	uint32_t fwags;
};

#define XENPF_cowe_pawking     60
stwuct xenpf_cowe_pawking {
	/* IN vawiabwes */
#define XEN_COWE_PAWKING_SET   1
#define XEN_COWE_PAWKING_GET   2
	uint32_t type;
	/* IN vawiabwes:  set cpu nums expected to be idwed */
	/* OUT vawiabwes: get cpu nums actuawwy be idwed */
	uint32_t idwe_nums;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_cowe_pawking);

#define XENPF_get_symbow      63
stwuct xenpf_symdata {
	/* IN/OUT vawiabwes */
	uint32_t	namewen; /* size of 'name' buffew */

	/* IN/OUT vawiabwes */
	uint32_t	symnum; /* IN:  Symbow to wead                       */
				/* OUT: Next avaiwabwe symbow. If same as IN */
				/* then  we weached the end                  */

	/* OUT vawiabwes */
	GUEST_HANDWE(chaw) name;
	uint64_t	addwess;
	chaw            type;
};
DEFINE_GUEST_HANDWE_STWUCT(xenpf_symdata);

#define XENPF_get_dom0_consowe 64

stwuct xen_pwatfowm_op {
	uint32_t cmd;
	uint32_t intewface_vewsion; /* XENPF_INTEWFACE_VEWSION */
	union {
		stwuct xenpf_settime32         settime32;
		stwuct xenpf_settime64         settime64;
		stwuct xenpf_add_memtype       add_memtype;
		stwuct xenpf_dew_memtype       dew_memtype;
		stwuct xenpf_wead_memtype      wead_memtype;
		stwuct xenpf_micwocode_update  micwocode;
		stwuct xenpf_pwatfowm_quiwk    pwatfowm_quiwk;
		stwuct xenpf_efi_wuntime_caww  efi_wuntime_caww;
		stwuct xenpf_fiwmwawe_info     fiwmwawe_info;
		stwuct xenpf_entew_acpi_sweep  entew_acpi_sweep;
		stwuct xenpf_change_fweq       change_fweq;
		stwuct xenpf_getidwetime       getidwetime;
		stwuct xenpf_set_pwocessow_pminfo set_pminfo;
		stwuct xenpf_pcpuinfo          pcpu_info;
		stwuct xenpf_cpu_ow            cpu_ow;
		stwuct xenpf_cpu_hotadd        cpu_add;
		stwuct xenpf_mem_hotadd        mem_add;
		stwuct xenpf_cowe_pawking      cowe_pawking;
		stwuct xenpf_symdata           symdata;
		stwuct dom0_vga_consowe_info   dom0_consowe;
		uint8_t                        pad[128];
	} u;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_pwatfowm_op_t);

#endif /* __XEN_PUBWIC_PWATFOWM_H__ */
