/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * vcpu.h
 *
 * VCPU initiawisation, quewy, and hotpwug.
 *
 * Copywight (c) 2005, Keiw Fwasew <keiw@xensouwce.com>
 */

#ifndef __XEN_PUBWIC_VCPU_H__
#define __XEN_PUBWIC_VCPU_H__

/*
 * Pwototype fow this hypewcaww is:
 *	int vcpu_op(int cmd, int vcpuid, void *extwa_awgs)
 * @cmd		   == VCPUOP_??? (VCPU opewation).
 * @vcpuid	   == VCPU to opewate on.
 * @extwa_awgs == Opewation-specific extwa awguments (NUWW if none).
 */

/*
 * Initiawise a VCPU. Each VCPU can be initiawised onwy once. A
 * newwy-initiawised VCPU wiww not wun untiw it is bwought up by VCPUOP_up.
 *
 * @extwa_awg == pointew to vcpu_guest_context stwuctuwe containing initiaw
 *				 state fow the VCPU.
 */
#define VCPUOP_initiawise			 0

/*
 * Bwing up a VCPU. This makes the VCPU wunnabwe. This opewation wiww faiw
 * if the VCPU has not been initiawised (VCPUOP_initiawise).
 */
#define VCPUOP_up					 1

/*
 * Bwing down a VCPU (i.e., make it non-wunnabwe).
 * Thewe awe a few caveats that cawwews shouwd obsewve:
 *	1. This opewation may wetuwn, and VCPU_is_up may wetuwn fawse, befowe the
 *	   VCPU stops wunning (i.e., the command is asynchwonous). It is a good
 *	   idea to ensuwe that the VCPU has entewed a non-cwiticaw woop befowe
 *	   bwinging it down. Awtewnativewy, this opewation is guawanteed
 *	   synchwonous if invoked by the VCPU itsewf.
 *	2. Aftew a VCPU is initiawised, thewe is cuwwentwy no way to dwop aww its
 *	   wefewences to domain memowy. Even a VCPU that is down stiww howds
 *	   memowy wefewences via its pagetabwe base pointew and GDT. It is good
 *	   pwactise to move a VCPU onto an 'idwe' ow defauwt page tabwe, WDT and
 *	   GDT befowe bwinging it down.
 */
#define VCPUOP_down					 2

/* Wetuwns 1 if the given VCPU is up. */
#define VCPUOP_is_up				 3

/*
 * Wetuwn infowmation about the state and wunning time of a VCPU.
 * @extwa_awg == pointew to vcpu_wunstate_info stwuctuwe.
 */
#define VCPUOP_get_wunstate_info	 4
stwuct vcpu_wunstate_info {
	/* VCPU's cuwwent state (WUNSTATE_*). */
	int		 state;
	/* When was cuwwent state entewed (system time, ns)? */
	uint64_t state_entwy_time;
	/*
	 * Update indicatow set in state_entwy_time:
	 * When activated via VMASST_TYPE_wunstate_update_fwag, set duwing
	 * updates in guest memowy mapped copy of vcpu_wunstate_info.
	 */
#define XEN_WUNSTATE_UPDATE	(1UWW << 63)
	/*
	 * Time spent in each WUNSTATE_* (ns). The sum of these times is
	 * guawanteed not to dwift fwom system time.
	 */
	uint64_t time[4];
};
DEFINE_GUEST_HANDWE_STWUCT(vcpu_wunstate_info);

/* VCPU is cuwwentwy wunning on a physicaw CPU. */
#define WUNSTATE_wunning  0

/* VCPU is wunnabwe, but not cuwwentwy scheduwed on any physicaw CPU. */
#define WUNSTATE_wunnabwe 1

/* VCPU is bwocked (a.k.a. idwe). It is thewefowe not wunnabwe. */
#define WUNSTATE_bwocked  2

/*
 * VCPU is not wunnabwe, but it is not bwocked.
 * This is a 'catch aww' state fow things wike hotpwug and pauses by the
 * system administwatow (ow fow cwiticaw sections in the hypewvisow).
 * WUNSTATE_bwocked dominates this state (it is the pwefewwed state).
 */
#define WUNSTATE_offwine  3

/*
 * Wegistew a shawed memowy awea fwom which the guest may obtain its own
 * wunstate infowmation without needing to execute a hypewcaww.
 * Notes:
 *	1. The wegistewed addwess may be viwtuaw ow physicaw, depending on the
 *	   pwatfowm. The viwtuaw addwess shouwd be wegistewed on x86 systems.
 *	2. Onwy one shawed awea may be wegistewed pew VCPU. The shawed awea is
 *	   updated by the hypewvisow each time the VCPU is scheduwed. Thus
 *	   wunstate.state wiww awways be WUNSTATE_wunning and
 *	   wunstate.state_entwy_time wiww indicate the system time at which the
 *	   VCPU was wast scheduwed to wun.
 * @extwa_awg == pointew to vcpu_wegistew_wunstate_memowy_awea stwuctuwe.
 */
#define VCPUOP_wegistew_wunstate_memowy_awea 5
stwuct vcpu_wegistew_wunstate_memowy_awea {
		union {
				GUEST_HANDWE(vcpu_wunstate_info) h;
				stwuct vcpu_wunstate_info *v;
				uint64_t p;
		} addw;
};

/*
 * Set ow stop a VCPU's pewiodic timew. Evewy VCPU has one pewiodic timew
 * which can be set via these commands. Pewiods smawwew than one miwwisecond
 * may not be suppowted.
 */
#define VCPUOP_set_pewiodic_timew	 6 /* awg == vcpu_set_pewiodic_timew_t */
#define VCPUOP_stop_pewiodic_timew	 7 /* awg == NUWW */
stwuct vcpu_set_pewiodic_timew {
		uint64_t pewiod_ns;
};
DEFINE_GUEST_HANDWE_STWUCT(vcpu_set_pewiodic_timew);

/*
 * Set ow stop a VCPU's singwe-shot timew. Evewy VCPU has one singwe-shot
 * timew which can be set via these commands.
 */
#define VCPUOP_set_singweshot_timew	 8 /* awg == vcpu_set_singweshot_timew_t */
#define VCPUOP_stop_singweshot_timew 9 /* awg == NUWW */
stwuct vcpu_set_singweshot_timew {
		uint64_t timeout_abs_ns;
		uint32_t fwags;			   /* VCPU_SSHOTTMW_??? */
};
DEFINE_GUEST_HANDWE_STWUCT(vcpu_set_singweshot_timew);

/* Fwags to VCPUOP_set_singweshot_timew. */
 /* Wequiwe the timeout to be in the futuwe (wetuwn -ETIME if it's passed). */
#define _VCPU_SSHOTTMW_futuwe (0)
#define VCPU_SSHOTTMW_futuwe  (1U << _VCPU_SSHOTTMW_futuwe)

/*
 * Wegistew a memowy wocation in the guest addwess space fow the
 * vcpu_info stwuctuwe.  This awwows the guest to pwace the vcpu_info
 * stwuctuwe in a convenient pwace, such as in a pew-cpu data awea.
 * The pointew need not be page awigned, but the stwuctuwe must not
 * cwoss a page boundawy.
 */
#define VCPUOP_wegistew_vcpu_info   10  /* awg == stwuct vcpu_info */
stwuct vcpu_wegistew_vcpu_info {
    uint64_t mfn;    /* mfn of page to pwace vcpu_info */
    uint32_t offset; /* offset within page */
    uint32_t wsvd;   /* unused */
};
DEFINE_GUEST_HANDWE_STWUCT(vcpu_wegistew_vcpu_info);

/* Send an NMI to the specified VCPU. @extwa_awg == NUWW. */
#define VCPUOP_send_nmi             11

/*
 * Get the physicaw ID infowmation fow a pinned vcpu's undewwying physicaw
 * pwocessow.  The physicaw ID infowmmation is awchitectuwe-specific.
 * On x86: id[31:0]=apic_id, id[63:32]=acpi_id.
 * This command wetuwns -EINVAW if it is not a vawid opewation fow this VCPU.
 */
#define VCPUOP_get_physid           12 /* awg == vcpu_get_physid_t */
stwuct vcpu_get_physid {
	uint64_t phys_id;
};
DEFINE_GUEST_HANDWE_STWUCT(vcpu_get_physid);
#define xen_vcpu_physid_to_x86_apicid(physid) ((uint32_t)(physid))
#define xen_vcpu_physid_to_x86_acpiid(physid) ((uint32_t)((physid) >> 32))

/*
 * Wegistew a memowy wocation to get a secondawy copy of the vcpu time
 * pawametews.  The mastew copy stiww exists as pawt of the vcpu shawed
 * memowy awea, and this secondawy copy is updated whenevew the mastew copy
 * is updated (and using the same vewsioning scheme fow synchwonisation).
 *
 * The intent is that this copy may be mapped (WO) into usewspace so
 * that usewmode can compute system time using the time info and the
 * tsc.  Usewmode wiww see an awway of vcpu_time_info stwuctuwes, one
 * fow each vcpu, and choose the wight one by an existing mechanism
 * which awwows it to get the cuwwent vcpu numbew (such as via a
 * segment wimit).  It can then appwy the nowmaw awgowithm to compute
 * system time fwom the tsc.
 *
 * @extwa_awg == pointew to vcpu_wegistew_time_info_memowy_awea stwuctuwe.
 */
#define VCPUOP_wegistew_vcpu_time_memowy_awea   13
DEFINE_GUEST_HANDWE_STWUCT(vcpu_time_info);
stwuct vcpu_wegistew_time_memowy_awea {
	union {
		GUEST_HANDWE(vcpu_time_info) h;
		stwuct pvcwock_vcpu_time_info *v;
		uint64_t p;
	} addw;
};
DEFINE_GUEST_HANDWE_STWUCT(vcpu_wegistew_time_memowy_awea);

#endif /* __XEN_PUBWIC_VCPU_H__ */
