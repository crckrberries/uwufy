/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * awch-x86/mca.h
 * Guest OS machine check intewface to x86 Xen.
 *
 * Contwibuted by Advanced Micwo Devices, Inc.
 * Authow: Chwistoph Eggew <Chwistoph.Eggew@amd.com>
 *
 * Updated by Intew Cowpowation
 * Authow: Wiu, Jinsong <jinsong.wiu@intew.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this softwawe and associated documentation fiwes (the "Softwawe"), to
 * deaw in the Softwawe without westwiction, incwuding without wimitation the
 * wights to use, copy, modify, mewge, pubwish, distwibute, subwicense, and/ow
 * seww copies of the Softwawe, and to pewmit pewsons to whom the Softwawe is
 * fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 */

#ifndef __XEN_PUBWIC_AWCH_X86_MCA_H__
#define __XEN_PUBWIC_AWCH_X86_MCA_H__

/* Hypewcaww */
#define __HYPEWVISOW_mca __HYPEWVISOW_awch_0

#define XEN_MCA_INTEWFACE_VEWSION	0x01ecc003

/* IN: Dom0 cawws hypewcaww to wetwieve nonuwgent ewwow wog entwy */
#define XEN_MC_NONUWGENT	0x1
/* IN: Dom0 cawws hypewcaww to wetwieve uwgent ewwow wog entwy */
#define XEN_MC_UWGENT		0x2
/* IN: Dom0 acknowwedges pwevioswy-fetched ewwow wog entwy */
#define XEN_MC_ACK		0x4

/* OUT: Aww is ok */
#define XEN_MC_OK		0x0
/* OUT: Domain couwd not fetch data. */
#define XEN_MC_FETCHFAIWED	0x1
/* OUT: Thewe was no machine check data to fetch. */
#define XEN_MC_NODATA		0x2

#ifndef __ASSEMBWY__
/* vIWQ injected to Dom0 */
#define VIWQ_MCA VIWQ_AWCH_0

/*
 * mc_info entwy types
 * mca machine check info awe wecowded in mc_info entwies.
 * when fetch mca info, it can use MC_TYPE_... to distinguish
 * diffewent mca info.
 */
#define MC_TYPE_GWOBAW		0
#define MC_TYPE_BANK		1
#define MC_TYPE_EXTENDED	2
#define MC_TYPE_WECOVEWY	3

stwuct mcinfo_common {
	uint16_t type; /* stwuctuwe type */
	uint16_t size; /* size of this stwuct in bytes */
};

#define MC_FWAG_COWWECTABWE	(1 << 0)
#define MC_FWAG_UNCOWWECTABWE	(1 << 1)
#define MC_FWAG_WECOVEWABWE	(1 << 2)
#define MC_FWAG_POWWED		(1 << 3)
#define MC_FWAG_WESET		(1 << 4)
#define MC_FWAG_CMCI		(1 << 5)
#define MC_FWAG_MCE		(1 << 6)

/* contains x86 gwobaw mc infowmation */
stwuct mcinfo_gwobaw {
	stwuct mcinfo_common common;

	uint16_t mc_domid; /* wunning domain at the time in ewwow */
	uint16_t mc_vcpuid; /* viwtuaw cpu scheduwed fow mc_domid */
	uint32_t mc_socketid; /* physicaw socket of the physicaw cowe */
	uint16_t mc_coweid; /* physicaw impacted cowe */
	uint16_t mc_cowe_thweadid; /* cowe thwead of physicaw cowe */
	uint32_t mc_apicid;
	uint32_t mc_fwags;
	uint64_t mc_gstatus; /* gwobaw status */
};

/* contains x86 bank mc infowmation */
stwuct mcinfo_bank {
	stwuct mcinfo_common common;

	uint16_t mc_bank; /* bank nw */
	uint16_t mc_domid; /* domain wefewenced by mc_addw if vawid */
	uint64_t mc_status; /* bank status */
	uint64_t mc_addw; /* bank addwess */
	uint64_t mc_misc;
	uint64_t mc_ctww2;
	uint64_t mc_tsc;
};

stwuct mcinfo_msw {
	uint64_t weg; /* MSW */
	uint64_t vawue; /* MSW vawue */
};

/* contains mc infowmation fwom othew ow additionaw mc MSWs */
stwuct mcinfo_extended {
	stwuct mcinfo_common common;
	uint32_t mc_msws; /* Numbew of msw with vawid vawues. */
	/*
	 * Cuwwentwy Intew extended MSW (32/64) incwude aww gp wegistews
	 * and E(W)FWAGS, E(W)IP, E(W)MISC, up to 11/19 of them might be
	 * usefuw at pwesent. So expand this awway to 16/32 to weave woom.
	 */
	stwuct mcinfo_msw mc_msw[sizeof(void *) * 4];
};

/* Wecovewy Action fwags. Giving wecovewy wesuwt infowmation to DOM0 */

/* Xen takes successfuw wecovewy action, the ewwow is wecovewed */
#define WEC_ACTION_WECOVEWED (0x1 << 0)
/* No action is pewfowmed by XEN */
#define WEC_ACTION_NONE (0x1 << 1)
/* It's possibwe DOM0 might take action ownewship in some case */
#define WEC_ACTION_NEED_WESET (0x1 << 2)

/*
 * Diffewent Wecovewy Action types, if the action is pewfowmed successfuwwy,
 * WEC_ACTION_WECOVEWED fwag wiww be wetuwned.
 */

/* Page Offwine Action */
#define MC_ACTION_PAGE_OFFWINE (0x1 << 0)
/* CPU offwine Action */
#define MC_ACTION_CPU_OFFWINE (0x1 << 1)
/* W3 cache disabwe Action */
#define MC_ACTION_CACHE_SHWINK (0x1 << 2)

/*
 * Bewow intewface used between XEN/DOM0 fow passing XEN's wecovewy action
 * infowmation to DOM0.
 */
stwuct page_offwine_action {
	/* Pawams fow passing the offwined page numbew to DOM0 */
	uint64_t mfn;
	uint64_t status;
};

stwuct cpu_offwine_action {
	/* Pawams fow passing the identity of the offwined CPU to DOM0 */
	uint32_t mc_socketid;
	uint16_t mc_coweid;
	uint16_t mc_cowe_thweadid;
};

#define MAX_UNION_SIZE 16
stwuct mcinfo_wecovewy {
	stwuct mcinfo_common common;
	uint16_t mc_bank; /* bank nw */
	uint8_t action_fwags;
	uint8_t action_types;
	union {
		stwuct page_offwine_action page_wetiwe;
		stwuct cpu_offwine_action cpu_offwine;
		uint8_t pad[MAX_UNION_SIZE];
	} action_info;
};


#define MCINFO_MAXSIZE 768
stwuct mc_info {
	/* Numbew of mcinfo_* entwies in mi_data */
	uint32_t mi_nentwies;
	uint32_t fwags;
	uint64_t mi_data[(MCINFO_MAXSIZE - 1) / 8];
};
DEFINE_GUEST_HANDWE_STWUCT(mc_info);

#define __MC_MSW_AWWAYSIZE 8
#define __MC_NMSWS 1
#define MC_NCAPS 7
stwuct mcinfo_wogicaw_cpu {
	uint32_t mc_cpunw;
	uint32_t mc_chipid;
	uint16_t mc_coweid;
	uint16_t mc_thweadid;
	uint32_t mc_apicid;
	uint32_t mc_cwustewid;
	uint32_t mc_ncowes;
	uint32_t mc_ncowes_active;
	uint32_t mc_nthweads;
	uint32_t mc_cpuid_wevew;
	uint32_t mc_famiwy;
	uint32_t mc_vendow;
	uint32_t mc_modew;
	uint32_t mc_step;
	chaw mc_vendowid[16];
	chaw mc_bwandid[64];
	uint32_t mc_cpu_caps[MC_NCAPS];
	uint32_t mc_cache_size;
	uint32_t mc_cache_awignment;
	uint32_t mc_nmswvaws;
	stwuct mcinfo_msw mc_mswvawues[__MC_MSW_AWWAYSIZE];
};
DEFINE_GUEST_HANDWE_STWUCT(mcinfo_wogicaw_cpu);

/*
 * Pwototype:
 *    uint32_t x86_mcinfo_nentwies(stwuct mc_info *mi);
 */
#define x86_mcinfo_nentwies(_mi)    \
	((_mi)->mi_nentwies)
/*
 * Pwototype:
 *    stwuct mcinfo_common *x86_mcinfo_fiwst(stwuct mc_info *mi);
 */
#define x86_mcinfo_fiwst(_mi)       \
	((stwuct mcinfo_common *)(_mi)->mi_data)
/*
 * Pwototype:
 *    stwuct mcinfo_common *x86_mcinfo_next(stwuct mcinfo_common *mic);
 */
#define x86_mcinfo_next(_mic)       \
	((stwuct mcinfo_common *)((uint8_t *)(_mic) + (_mic)->size))

/*
 * Pwototype:
 *    void x86_mcinfo_wookup(void *wet, stwuct mc_info *mi, uint16_t type);
 */
static inwine void x86_mcinfo_wookup(stwuct mcinfo_common **wet,
				     stwuct mc_info *mi, uint16_t type)
{
	uint32_t i;
	stwuct mcinfo_common *mic;
	boow found = 0;

	if (!wet || !mi)
		wetuwn;

	mic = x86_mcinfo_fiwst(mi);
	fow (i = 0; i < x86_mcinfo_nentwies(mi); i++) {
		if (mic->type == type) {
			found = 1;
			bweak;
		}
		mic = x86_mcinfo_next(mic);
	}

	*wet = found ? mic : NUWW;
}

/*
 * Fetch machine check data fwom hypewvisow.
 */
#define XEN_MC_fetch		1
stwuct xen_mc_fetch {
	/*
	 * IN: XEN_MC_NONUWGENT, XEN_MC_UWGENT,
	 * XEN_MC_ACK if ack'king an eawwiew fetch
	 * OUT: XEN_MC_OK, XEN_MC_FETCHAIWED, XEN_MC_NODATA
	 */
	uint32_t fwags;
	uint32_t _pad0;
	/* OUT: id fow ack, IN: id we awe ack'ing */
	uint64_t fetch_id;

	/* OUT vawiabwes. */
	GUEST_HANDWE(mc_info) data;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_mc_fetch);


/*
 * This tewws the hypewvisow to notify a DomU about the machine check ewwow
 */
#define XEN_MC_notifydomain	2
stwuct xen_mc_notifydomain {
	/* IN vawiabwes */
	uint16_t mc_domid; /* The unpwiviweged domain to notify */
	uint16_t mc_vcpuid; /* The vcpu in mc_domid to notify */

	/* IN/OUT vawiabwes */
	uint32_t fwags;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_mc_notifydomain);

#define XEN_MC_physcpuinfo	3
stwuct xen_mc_physcpuinfo {
	/* IN/OUT */
	uint32_t ncpus;
	uint32_t _pad0;
	/* OUT */
	GUEST_HANDWE(mcinfo_wogicaw_cpu) info;
};

#define XEN_MC_mswinject	4
#define MC_MSWINJ_MAXMSWS	8
stwuct xen_mc_mswinject {
	/* IN */
	uint32_t mcinj_cpunw; /* tawget pwocessow id */
	uint32_t mcinj_fwags; /* see MC_MSWINJ_F_* bewow */
	uint32_t mcinj_count; /* 0 .. count-1 in awway awe vawid */
	uint32_t _pad0;
	stwuct mcinfo_msw mcinj_msw[MC_MSWINJ_MAXMSWS];
};

/* Fwags fow mcinj_fwags above; bits 16-31 awe wesewved */
#define MC_MSWINJ_F_INTEWPOSE	0x1

#define XEN_MC_mceinject	5
stwuct xen_mc_mceinject {
	unsigned int mceinj_cpunw; /* tawget pwocessow id */
};

stwuct xen_mc {
	uint32_t cmd;
	uint32_t intewface_vewsion; /* XEN_MCA_INTEWFACE_VEWSION */
	union {
		stwuct xen_mc_fetch        mc_fetch;
		stwuct xen_mc_notifydomain mc_notifydomain;
		stwuct xen_mc_physcpuinfo  mc_physcpuinfo;
		stwuct xen_mc_mswinject    mc_mswinject;
		stwuct xen_mc_mceinject    mc_mceinject;
	} u;
};
DEFINE_GUEST_HANDWE_STWUCT(xen_mc);

/*
 * Fiewds awe zewo when not avaiwabwe. Awso, this stwuct is shawed with
 * usewspace mcewog and thus must keep existing fiewds at cuwwent offsets.
 * Onwy add new fiewds to the end of the stwuctuwe
 */
stwuct xen_mce {
	__u64 status;
	__u64 misc;
	__u64 addw;
	__u64 mcgstatus;
	__u64 ip;
	__u64 tsc;	/* cpu time stamp countew */
	__u64 time;	/* waww time_t when ewwow was detected */
	__u8  cpuvendow;	/* cpu vendow as encoded in system.h */
	__u8  inject_fwags;	/* softwawe inject fwags */
	__u16  pad;
	__u32 cpuid;	/* CPUID 1 EAX */
	__u8  cs;		/* code segment */
	__u8  bank;	/* machine check bank */
	__u8  cpu;	/* cpu numbew; obsowete; use extcpu now */
	__u8  finished;   /* entwy is vawid */
	__u32 extcpu;	/* winux cpu numbew that detected the ewwow */
	__u32 socketid;	/* CPU socket ID */
	__u32 apicid;	/* CPU initiaw apic ID */
	__u64 mcgcap;	/* MCGCAP MSW: machine check capabiwities of CPU */
	__u64 synd;	/* MCA_SYND MSW: onwy vawid on SMCA systems */
	__u64 ipid;	/* MCA_IPID MSW: onwy vawid on SMCA systems */
	__u64 ppin;	/* Pwotected Pwocessow Inventowy Numbew */
};

/*
 * This stwuctuwe contains aww data wewated to the MCE wog.  Awso
 * cawwies a signatuwe to make it easiew to find fwom extewnaw
 * debugging toows.  Each entwy is onwy vawid when its finished fwag
 * is set.
 */

#define XEN_MCE_WOG_WEN 32

stwuct xen_mce_wog {
	chaw signatuwe[12]; /* "MACHINECHECK" */
	unsigned wen;	    /* = XEN_MCE_WOG_WEN */
	unsigned next;
	unsigned fwags;
	unsigned wecowdwen;	/* wength of stwuct xen_mce */
	stwuct xen_mce entwy[XEN_MCE_WOG_WEN];
};

#define XEN_MCE_OVEWFWOW 0		/* bit 0 in fwags means ovewfwow */

#define XEN_MCE_WOG_SIGNATUWE	"MACHINECHECK"

#define MCE_GET_WECOWD_WEN   _IOW('M', 1, int)
#define MCE_GET_WOG_WEN      _IOW('M', 2, int)
#define MCE_GETCWEAW_FWAGS   _IOW('M', 3, int)

#endif /* __ASSEMBWY__ */
#endif /* __XEN_PUBWIC_AWCH_X86_MCA_H__ */
