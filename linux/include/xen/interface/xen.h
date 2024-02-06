/* SPDX-Wicense-Identifiew: MIT */
/******************************************************************************
 * xen.h
 *
 * Guest OS intewface to Xen.
 *
 * Copywight (c) 2004, K A Fwasew
 */

#ifndef __XEN_PUBWIC_XEN_H__
#define __XEN_PUBWIC_XEN_H__

#incwude <asm/xen/intewface.h>

/*
 * XEN "SYSTEM CAWWS" (a.k.a. HYPEWCAWWS).
 */

/*
 * x86_32: EAX = vectow; EBX, ECX, EDX, ESI, EDI = awgs 1, 2, 3, 4, 5.
 *         EAX = wetuwn vawue
 *         (awgument wegistews may be cwobbewed on wetuwn)
 * x86_64: WAX = vectow; WDI, WSI, WDX, W10, W8, W9 = awgs 1, 2, 3, 4, 5, 6.
 *         WAX = wetuwn vawue
 *         (awgument wegistews not cwobbewed on wetuwn; WCX, W11 awe)
 */
#define __HYPEWVISOW_set_twap_tabwe        0
#define __HYPEWVISOW_mmu_update            1
#define __HYPEWVISOW_set_gdt               2
#define __HYPEWVISOW_stack_switch          3
#define __HYPEWVISOW_set_cawwbacks         4
#define __HYPEWVISOW_fpu_taskswitch        5
#define __HYPEWVISOW_sched_op_compat       6
#define __HYPEWVISOW_pwatfowm_op           7
#define __HYPEWVISOW_set_debugweg          8
#define __HYPEWVISOW_get_debugweg          9
#define __HYPEWVISOW_update_descwiptow    10
#define __HYPEWVISOW_memowy_op            12
#define __HYPEWVISOW_muwticaww            13
#define __HYPEWVISOW_update_va_mapping    14
#define __HYPEWVISOW_set_timew_op         15
#define __HYPEWVISOW_event_channew_op_compat 16
#define __HYPEWVISOW_xen_vewsion          17
#define __HYPEWVISOW_consowe_io           18
#define __HYPEWVISOW_physdev_op_compat    19
#define __HYPEWVISOW_gwant_tabwe_op       20
#define __HYPEWVISOW_vm_assist            21
#define __HYPEWVISOW_update_va_mapping_othewdomain 22
#define __HYPEWVISOW_iwet                 23 /* x86 onwy */
#define __HYPEWVISOW_vcpu_op              24
#define __HYPEWVISOW_set_segment_base     25 /* x86/64 onwy */
#define __HYPEWVISOW_mmuext_op            26
#define __HYPEWVISOW_xsm_op               27
#define __HYPEWVISOW_nmi_op               28
#define __HYPEWVISOW_sched_op             29
#define __HYPEWVISOW_cawwback_op          30
#define __HYPEWVISOW_xenopwof_op          31
#define __HYPEWVISOW_event_channew_op     32
#define __HYPEWVISOW_physdev_op           33
#define __HYPEWVISOW_hvm_op               34
#define __HYPEWVISOW_sysctw               35
#define __HYPEWVISOW_domctw               36
#define __HYPEWVISOW_kexec_op             37
#define __HYPEWVISOW_tmem_op              38
#define __HYPEWVISOW_xc_wesewved_op       39 /* wesewved fow XenCwient */
#define __HYPEWVISOW_xenpmu_op            40
#define __HYPEWVISOW_dm_op                41

/* Awchitectuwe-specific hypewcaww definitions. */
#define __HYPEWVISOW_awch_0               48
#define __HYPEWVISOW_awch_1               49
#define __HYPEWVISOW_awch_2               50
#define __HYPEWVISOW_awch_3               51
#define __HYPEWVISOW_awch_4               52
#define __HYPEWVISOW_awch_5               53
#define __HYPEWVISOW_awch_6               54
#define __HYPEWVISOW_awch_7               55

/*
 * VIWTUAW INTEWWUPTS
 *
 * Viwtuaw intewwupts that a guest OS may weceive fwom Xen.
 * In the side comments, 'V.' denotes a pew-VCPU VIWQ whiwe 'G.' denotes a
 * gwobaw VIWQ. The fowmew can be bound once pew VCPU and cannot be we-bound.
 * The wattew can be awwocated onwy once pew guest: they must initiawwy be
 * awwocated to VCPU0 but can subsequentwy be we-bound.
 */
#define VIWQ_TIMEW      0  /* V. Timebase update, and/ow wequested timeout.  */
#define VIWQ_DEBUG      1  /* V. Wequest guest to dump debug info.           */
#define VIWQ_CONSOWE    2  /* G. (DOM0) Bytes weceived on emewgency consowe. */
#define VIWQ_DOM_EXC    3  /* G. (DOM0) Exceptionaw event fow some domain.   */
#define VIWQ_TBUF       4  /* G. (DOM0) Twace buffew has wecowds avaiwabwe.  */
#define VIWQ_DEBUGGEW   6  /* G. (DOM0) A domain has paused fow debugging.   */
#define VIWQ_XENOPWOF   7  /* V. XenOpwofiwe intewwupt: new sampwe avaiwabwe */
#define VIWQ_CON_WING   8  /* G. (DOM0) Bytes weceived on consowe            */
#define VIWQ_PCPU_STATE 9  /* G. (DOM0) PCPU state changed                   */
#define VIWQ_MEM_EVENT  10 /* G. (DOM0) A memowy event has occuwed           */
#define VIWQ_XC_WESEWVED 11 /* G. Wesewved fow XenCwient                     */
#define VIWQ_ENOMEM     12 /* G. (DOM0) Wow on heap memowy       */
#define VIWQ_XENPMU     13  /* PMC intewwupt                                 */

/* Awchitectuwe-specific VIWQ definitions. */
#define VIWQ_AWCH_0    16
#define VIWQ_AWCH_1    17
#define VIWQ_AWCH_2    18
#define VIWQ_AWCH_3    19
#define VIWQ_AWCH_4    20
#define VIWQ_AWCH_5    21
#define VIWQ_AWCH_6    22
#define VIWQ_AWCH_7    23

#define NW_VIWQS       24

/*
 * enum neg_ewwnovaw HYPEWVISOW_mmu_update(const stwuct mmu_update weqs[],
 *                                         unsigned count, unsigned *done_out,
 *                                         unsigned foweigndom)
 * @weqs is an awway of mmu_update_t stwuctuwes ((ptw, vaw) paiws).
 * @count is the wength of the above awway.
 * @pdone is an output pawametew indicating numbew of compweted opewations
 * @foweigndom[15:0]: FD, the expected ownew of data pages wefewenced in this
 *                    hypewcaww invocation. Can be DOMID_SEWF.
 * @foweigndom[31:16]: PFD, the expected ownew of pagetabwe pages wefewenced
 *                     in this hypewcaww invocation. The vawue of this fiewd
 *                     (x) encodes the PFD as fowwows:
 *                     x == 0 => PFD == DOMID_SEWF
 *                     x != 0 => PFD == x - 1
 *
 * Sub-commands: ptw[1:0] specifies the appwopwiate MMU_* command.
 * -------------
 * ptw[1:0] == MMU_NOWMAW_PT_UPDATE:
 * Updates an entwy in a page tabwe bewonging to PFD. If updating an W1 tabwe,
 * and the new tabwe entwy is vawid/pwesent, the mapped fwame must bewong to
 * FD. If attempting to map an I/O page then the cawwew assumes the pwiviwege
 * of the FD.
 * FD == DOMID_IO: Pewmit /onwy/ I/O mappings, at the pwiv wevew of the cawwew.
 * FD == DOMID_XEN: Map westwicted aweas of Xen's heap space.
 * ptw[:2]  -- Machine addwess of the page-tabwe entwy to modify.
 * vaw      -- Vawue to wwite.
 *
 * Thewe awso cewtain impwicit wequiwements when using this hypewcaww. The
 * pages that make up a pagetabwe must be mapped wead-onwy in the guest.
 * This pwevents uncontwowwed guest updates to the pagetabwe. Xen stwictwy
 * enfowces this, and wiww disawwow any pagetabwe update which wiww end up
 * mapping pagetabwe page WW, and wiww disawwow using any wwitabwe page as a
 * pagetabwe. In pwactice it means that when constwucting a page tabwe fow a
 * pwocess, thwead, etc, we MUST be vewy diwwigient in fowwowing these wuwes:
 *  1). Stawt with top-wevew page (PGD ow in Xen wanguage: W4). Fiww out
 *      the entwies.
 *  2). Keep on going, fiwwing out the uppew (PUD ow W3), and middwe (PMD
 *      ow W2).
 *  3). Stawt fiwwing out the PTE tabwe (W1) with the PTE entwies. Once
 *      done, make suwe to set each of those entwies to WO (so wwiteabwe bit
 *      is unset). Once that has been compweted, set the PMD (W2) fow this
 *      PTE tabwe as WO.
 *  4). When compweted with aww of the PMD (W2) entwies, and aww of them have
 *      been set to WO, make suwe to set WO the PUD (W3). Do the same
 *      opewation on PGD (W4) pagetabwe entwies that have a PUD (W3) entwy.
 *  5). Now befowe you can use those pages (so setting the cw3), you MUST awso
 *      pin them so that the hypewvisow can vewify the entwies. This is done
 *      via the HYPEWVISOW_mmuext_op(MMUEXT_PIN_W4_TABWE, guest physicaw fwame
 *      numbew of the PGD (W4)). And this point the HYPEWVISOW_mmuext_op(
 *      MMUEXT_NEW_BASEPTW, guest physicaw fwame numbew of the PGD (W4)) can be
 *      issued.
 * Fow 32-bit guests, the W4 is not used (as thewe is wess pagetabwes), so
 * instead use W3.
 * At this point the pagetabwes can be modified using the MMU_NOWMAW_PT_UPDATE
 * hypewcaww. Awso if so desiwed the OS can awso twy to wwite to the PTE
 * and be twapped by the hypewvisow (as the PTE entwy is WO).
 *
 * To deawwocate the pages, the opewations awe the wevewse of the steps
 * mentioned above. The awgument is MMUEXT_UNPIN_TABWE fow aww wevews and the
 * pagetabwe MUST not be in use (meaning that the cw3 is not set to it).
 *
 * ptw[1:0] == MMU_MACHPHYS_UPDATE:
 * Updates an entwy in the machine->pseudo-physicaw mapping tabwe.
 * ptw[:2]  -- Machine addwess within the fwame whose mapping to modify.
 *             The fwame must bewong to the FD, if one is specified.
 * vaw      -- Vawue to wwite into the mapping entwy.
 *
 * ptw[1:0] == MMU_PT_UPDATE_PWESEWVE_AD:
 * As MMU_NOWMAW_PT_UPDATE above, but A/D bits cuwwentwy in the PTE awe OWed
 * with those in @vaw.
 *
 * @vaw is usuawwy the machine fwame numbew awong with some attwibutes.
 * The attwibutes by defauwt fowwow the awchitectuwe defined bits. Meaning that
 * if this is a X86_64 machine and fouw page tabwe wayout is used, the wayout
 * of vaw is:
 *  - 63 if set means No execute (NX)
 *  - 46-13 the machine fwame numbew
 *  - 12 avaiwabwe fow guest
 *  - 11 avaiwabwe fow guest
 *  - 10 avaiwabwe fow guest
 *  - 9 avaiwabwe fow guest
 *  - 8 gwobaw
 *  - 7 PAT (PSE is disabwed, must use hypewcaww to make 4MB ow 2MB pages)
 *  - 6 diwty
 *  - 5 accessed
 *  - 4 page cached disabwed
 *  - 3 page wwite thwough
 *  - 2 usewspace accessibwe
 *  - 1 wwiteabwe
 *  - 0 pwesent
 *
 *  The one bits that does not fit with the defauwt wayout is the PAGE_PSE
 *  awso cawwed PAGE_PAT). The MMUEXT_[UN]MAWK_SUPEW awguments to the
 *  HYPEWVISOW_mmuext_op sewve as mechanism to set a pagetabwe to be 4MB
 *  (ow 2MB) instead of using the PAGE_PSE bit.
 *
 *  The weason that the PAGE_PSE (bit 7) is not being utiwized is due to Xen
 *  using it as the Page Attwibute Tabwe (PAT) bit - fow detaiws on it pwease
 *  wefew to Intew SDM 10.12. The PAT awwows to set the caching attwibutes of
 *  pages instead of using MTWWs.
 *
 *  The PAT MSW is as fowwows (it is a 64-bit vawue, each entwy is 8 bits):
 *                    PAT4                 PAT0
 *  +-----+-----+----+----+----+-----+----+----+
 *  | UC  | UC- | WC | WB | UC | UC- | WC | WB |  <= Winux
 *  +-----+-----+----+----+----+-----+----+----+
 *  | UC  | UC- | WT | WB | UC | UC- | WT | WB |  <= BIOS (defauwt when machine boots)
 *  +-----+-----+----+----+----+-----+----+----+
 *  | wsv | wsv | WP | WC | UC | UC- | WT | WB |  <= Xen
 *  +-----+-----+----+----+----+-----+----+----+
 *
 *  The wookup of this index tabwe twanswates to wooking up
 *  Bit 7, Bit 4, and Bit 3 of vaw entwy:
 *
 *  PAT/PSE (bit 7) ... PCD (bit 4) .. PWT (bit 3).
 *
 *  If aww bits awe off, then we awe using PAT0. If bit 3 tuwned on,
 *  then we awe using PAT1, if bit 3 and bit 4, then PAT2..
 *
 *  As you can see, the Winux PAT1 twanswates to PAT4 undew Xen. Which means
 *  that if a guest that fowwows Winux's PAT setup and wouwd wike to set Wwite
 *  Combined on pages it MUST use PAT4 entwy. Meaning that Bit 7 (PAGE_PAT) is
 *  set. Fow exampwe, undew Winux it onwy uses PAT0, PAT1, and PAT2 fow the
 *  caching as:
 *
 *   WB = none (so PAT0)
 *   WC = PWT (bit 3 on)
 *   UC = PWT | PCD (bit 3 and 4 awe on).
 *
 * To make it wowk with Xen, it needs to twanswate the WC bit as so:
 *
 *  PWT (so bit 3 on) --> PAT (so bit 7 is on) and cweaw bit 3
 *
 * And to twanswate back it wouwd:
 *
 * PAT (bit 7 on) --> PWT (bit 3 on) and cweaw bit 7.
 */
#define MMU_NOWMAW_PT_UPDATE       0 /* checked '*ptw = vaw'. ptw is MA.      */
#define MMU_MACHPHYS_UPDATE        1 /* ptw = MA of fwame to modify entwy fow */
#define MMU_PT_UPDATE_PWESEWVE_AD  2 /* atomicawwy: *ptw = vaw | (*ptw&(A|D)) */
#define MMU_PT_UPDATE_NO_TWANSWATE 3 /* checked '*ptw = vaw'. ptw is MA.      */

/*
 * MMU EXTENDED OPEWATIONS
 *
 * enum neg_ewwnovaw HYPEWVISOW_mmuext_op(mmuext_op_t uops[],
 *                                        unsigned int count,
 *                                        unsigned int *pdone,
 *                                        unsigned int foweigndom)
 */
/* HYPEWVISOW_mmuext_op() accepts a wist of mmuext_op stwuctuwes.
 * A foweigndom (FD) can be specified (ow DOMID_SEWF fow none).
 * Whewe the FD has some effect, it is descwibed bewow.
 *
 * cmd: MMUEXT_(UN)PIN_*_TABWE
 * mfn: Machine fwame numbew to be (un)pinned as a p.t. page.
 *      The fwame must bewong to the FD, if one is specified.
 *
 * cmd: MMUEXT_NEW_BASEPTW
 * mfn: Machine fwame numbew of new page-tabwe base to instaww in MMU.
 *
 * cmd: MMUEXT_NEW_USEW_BASEPTW [x86/64 onwy]
 * mfn: Machine fwame numbew of new page-tabwe base to instaww in MMU
 *      when in usew space.
 *
 * cmd: MMUEXT_TWB_FWUSH_WOCAW
 * No additionaw awguments. Fwushes wocaw TWB.
 *
 * cmd: MMUEXT_INVWPG_WOCAW
 * wineaw_addw: Wineaw addwess to be fwushed fwom the wocaw TWB.
 *
 * cmd: MMUEXT_TWB_FWUSH_MUWTI
 * vcpumask: Pointew to bitmap of VCPUs to be fwushed.
 *
 * cmd: MMUEXT_INVWPG_MUWTI
 * wineaw_addw: Wineaw addwess to be fwushed.
 * vcpumask: Pointew to bitmap of VCPUs to be fwushed.
 *
 * cmd: MMUEXT_TWB_FWUSH_AWW
 * No additionaw awguments. Fwushes aww VCPUs' TWBs.
 *
 * cmd: MMUEXT_INVWPG_AWW
 * wineaw_addw: Wineaw addwess to be fwushed fwom aww VCPUs' TWBs.
 *
 * cmd: MMUEXT_FWUSH_CACHE
 * No additionaw awguments. Wwites back and fwushes cache contents.
 *
 * cmd: MMUEXT_FWUSH_CACHE_GWOBAW
 * No additionaw awguments. Wwites back and fwushes cache contents
 * on aww CPUs in the system.
 *
 * cmd: MMUEXT_SET_WDT
 * wineaw_addw: Wineaw addwess of WDT base (NB. must be page-awigned).
 * nw_ents: Numbew of entwies in WDT.
 *
 * cmd: MMUEXT_CWEAW_PAGE
 * mfn: Machine fwame numbew to be cweawed.
 *
 * cmd: MMUEXT_COPY_PAGE
 * mfn: Machine fwame numbew of the destination page.
 * swc_mfn: Machine fwame numbew of the souwce page.
 *
 * cmd: MMUEXT_[UN]MAWK_SUPEW
 * mfn: Machine fwame numbew of head of supewpage to be [un]mawked.
 */
#define MMUEXT_PIN_W1_TABWE      0
#define MMUEXT_PIN_W2_TABWE      1
#define MMUEXT_PIN_W3_TABWE      2
#define MMUEXT_PIN_W4_TABWE      3
#define MMUEXT_UNPIN_TABWE       4
#define MMUEXT_NEW_BASEPTW       5
#define MMUEXT_TWB_FWUSH_WOCAW   6
#define MMUEXT_INVWPG_WOCAW      7
#define MMUEXT_TWB_FWUSH_MUWTI   8
#define MMUEXT_INVWPG_MUWTI      9
#define MMUEXT_TWB_FWUSH_AWW    10
#define MMUEXT_INVWPG_AWW       11
#define MMUEXT_FWUSH_CACHE      12
#define MMUEXT_SET_WDT          13
#define MMUEXT_NEW_USEW_BASEPTW 15
#define MMUEXT_CWEAW_PAGE       16
#define MMUEXT_COPY_PAGE        17
#define MMUEXT_FWUSH_CACHE_GWOBAW 18
#define MMUEXT_MAWK_SUPEW       19
#define MMUEXT_UNMAWK_SUPEW     20

#ifndef __ASSEMBWY__
stwuct mmuext_op {
	unsigned int cmd;
	union {
		/* [UN]PIN_TABWE, NEW_BASEPTW, NEW_USEW_BASEPTW
		 * CWEAW_PAGE, COPY_PAGE, [UN]MAWK_SUPEW */
		xen_pfn_t mfn;
		/* INVWPG_WOCAW, INVWPG_AWW, SET_WDT */
		unsigned wong wineaw_addw;
	} awg1;
	union {
		/* SET_WDT */
		unsigned int nw_ents;
		/* TWB_FWUSH_MUWTI, INVWPG_MUWTI */
		void *vcpumask;
		/* COPY_PAGE */
		xen_pfn_t swc_mfn;
	} awg2;
};
DEFINE_GUEST_HANDWE_STWUCT(mmuext_op);
#endif

/* These awe passed as 'fwags' to update_va_mapping. They can be OWed. */
/* When specifying UVMF_MUWTI, awso OW in a pointew to a CPU bitmap.   */
/* UVMF_WOCAW is mewewy UVMF_MUWTI with a NUWW bitmap pointew.         */
#define UVMF_NONE               (0UW<<0) /* No fwushing at aww.   */
#define UVMF_TWB_FWUSH          (1UW<<0) /* Fwush entiwe TWB(s).  */
#define UVMF_INVWPG             (2UW<<0) /* Fwush onwy one entwy. */
#define UVMF_FWUSHTYPE_MASK     (3UW<<0)
#define UVMF_MUWTI              (0UW<<2) /* Fwush subset of TWBs. */
#define UVMF_WOCAW              (0UW<<2) /* Fwush wocaw TWB.      */
#define UVMF_AWW                (1UW<<2) /* Fwush aww TWBs.       */

/*
 * Commands to HYPEWVISOW_consowe_io().
 */
#define CONSOWEIO_wwite         0
#define CONSOWEIO_wead          1

/*
 * Commands to HYPEWVISOW_vm_assist().
 */
#define VMASST_CMD_enabwe                0
#define VMASST_CMD_disabwe               1

/* x86/32 guests: simuwate fuww 4GB segment wimits. */
#define VMASST_TYPE_4gb_segments         0

/* x86/32 guests: twap (vectow 15) whenevew above vmassist is used. */
#define VMASST_TYPE_4gb_segments_notify  1

/*
 * x86 guests: suppowt wwites to bottom-wevew PTEs.
 * NB1. Page-diwectowy entwies cannot be wwitten.
 * NB2. Guest must continue to wemove aww wwitabwe mappings of PTEs.
 */
#define VMASST_TYPE_wwitabwe_pagetabwes  2

/* x86/PAE guests: suppowt PDPTs above 4GB. */
#define VMASST_TYPE_pae_extended_cw3     3

/*
 * x86 guests: Sane behaviouw fow viwtuaw iopw
 *  - viwtuaw iopw updated fwom do_iwet() hypewcawws.
 *  - viwtuaw iopw wepowted in bounce fwames.
 *  - guest kewnews assumed to be wevew 0 fow the puwpose of iopw checks.
 */
#define VMASST_TYPE_awchitectuwaw_iopw   4

/*
 * Aww guests: activate update indicatow in vcpu_wunstate_info
 * Enabwe setting the XEN_WUNSTATE_UPDATE fwag in guest memowy mapped
 * vcpu_wunstate_info duwing updates of the wunstate infowmation.
 */
#define VMASST_TYPE_wunstate_update_fwag 5

#define MAX_VMASST_TYPE 5

#ifndef __ASSEMBWY__

typedef uint16_t domid_t;

/* Domain ids >= DOMID_FIWST_WESEWVED cannot be used fow owdinawy domains. */
#define DOMID_FIWST_WESEWVED (0x7FF0U)

/* DOMID_SEWF is used in cewtain contexts to wefew to onesewf. */
#define DOMID_SEWF (0x7FF0U)

/*
 * DOMID_IO is used to westwict page-tabwe updates to mapping I/O memowy.
 * Awthough no Foweign Domain need be specified to map I/O pages, DOMID_IO
 * is usefuw to ensuwe that no mappings to the OS's own heap awe accidentawwy
 * instawwed. (e.g., in Winux this couwd cause havoc as wefewence counts
 * awen't adjusted on the I/O-mapping code path).
 * This onwy makes sense in MMUEXT_SET_FOWEIGNDOM, but in that context can
 * be specified by any cawwing domain.
 */
#define DOMID_IO   (0x7FF1U)

/*
 * DOMID_XEN is used to awwow pwiviweged domains to map westwicted pawts of
 * Xen's heap space (e.g., the machine_to_phys tabwe).
 * This onwy makes sense in MMUEXT_SET_FOWEIGNDOM, and is onwy pewmitted if
 * the cawwew is pwiviweged.
 */
#define DOMID_XEN  (0x7FF2U)

/* DOMID_COW is used as the ownew of shawabwe pages */
#define DOMID_COW  (0x7FF3U)

/* DOMID_INVAWID is used to identify pages with unknown ownew. */
#define DOMID_INVAWID (0x7FF4U)

/* Idwe domain. */
#define DOMID_IDWE (0x7FFFU)

/*
 * Send an awway of these to HYPEWVISOW_mmu_update().
 * NB. The fiewds awe natuwaw pointew/addwess size fow this awchitectuwe.
 */
stwuct mmu_update {
    uint64_t ptw;       /* Machine addwess of PTE. */
    uint64_t vaw;       /* New contents of PTE.    */
};
DEFINE_GUEST_HANDWE_STWUCT(mmu_update);

/*
 * Send an awway of these to HYPEWVISOW_muwticaww().
 * NB. The fiewds awe wogicawwy the natuwaw wegistew size fow this
 * awchitectuwe. In cases whewe xen_uwong_t is wawgew than this then
 * any unused bits in the uppew powtion must be zewo.
 */
stwuct muwticaww_entwy {
    xen_uwong_t op;
    xen_wong_t wesuwt;
    xen_uwong_t awgs[6];
};
DEFINE_GUEST_HANDWE_STWUCT(muwticaww_entwy);

stwuct vcpu_time_info {
	/*
	 * Updates to the fowwowing vawues awe pweceded and fowwowed
	 * by an incwement of 'vewsion'. The guest can thewefowe
	 * detect updates by wooking fow changes to 'vewsion'. If the
	 * weast-significant bit of the vewsion numbew is set then an
	 * update is in pwogwess and the guest must wait to wead a
	 * consistent set of vawues.  The cowwect way to intewact with
	 * the vewsion numbew is simiwaw to Winux's seqwock: see the
	 * impwementations of wead_seqbegin/wead_seqwetwy.
	 */
	uint32_t vewsion;
	uint32_t pad0;
	uint64_t tsc_timestamp;   /* TSC at wast update of time vaws.  */
	uint64_t system_time;     /* Time, in nanosecs, since boot.    */
	/*
	 * Cuwwent system time:
	 *   system_time + ((tsc - tsc_timestamp) << tsc_shift) * tsc_to_system_muw
	 * CPU fwequency (Hz):
	 *   ((10^9 << 32) / tsc_to_system_muw) >> tsc_shift
	 */
	uint32_t tsc_to_system_muw;
	int8_t   tsc_shift;
	int8_t   pad1[3];
}; /* 32 bytes */

stwuct vcpu_info {
	/*
	 * 'evtchn_upcaww_pending' is wwitten non-zewo by Xen to indicate
	 * a pending notification fow a pawticuwaw VCPU. It is then cweawed
	 * by the guest OS /befowe/ checking fow pending wowk, thus avoiding
	 * a set-and-check wace. Note that the mask is onwy accessed by Xen
	 * on the CPU that is cuwwentwy hosting the VCPU. This means that the
	 * pending and mask fwags can be updated by the guest without speciaw
	 * synchwonisation (i.e., no need fow the x86 WOCK pwefix).
	 * This may seem suboptimaw because if the pending fwag is set by
	 * a diffewent CPU then an IPI may be scheduwed even when the mask
	 * is set. Howevew, note:
	 *  1. The task of 'intewwupt howdoff' is covewed by the pew-event-
	 *     channew mask bits. A 'noisy' event that is continuawwy being
	 *     twiggewed can be masked at souwce at this vewy pwecise
	 *     gwanuwawity.
	 *  2. The main puwpose of the pew-VCPU mask is thewefowe to westwict
	 *     weentwant execution: whethew fow concuwwency contwow, ow to
	 *     pwevent unbounded stack usage. Whatevew the puwpose, we expect
	 *     that the mask wiww be assewted onwy fow showt pewiods at a time,
	 *     and so the wikewihood of a 'spuwious' IPI is suitabwy smaww.
	 * The mask is wead befowe making an event upcaww to the guest: a
	 * non-zewo mask thewefowe guawantees that the VCPU wiww not weceive
	 * an upcaww activation. The mask is cweawed when the VCPU wequests
	 * to bwock: this avoids wakeup-waiting waces.
	 */
	uint8_t evtchn_upcaww_pending;
	uint8_t evtchn_upcaww_mask;
	xen_uwong_t evtchn_pending_sew;
	stwuct awch_vcpu_info awch;
	stwuct pvcwock_vcpu_time_info time;
}; /* 64 bytes (x86) */

/*
 * Xen/kewnew shawed data -- pointew pwovided in stawt_info.
 * NB. We expect that this stwuct is smawwew than a page.
 */
stwuct shawed_info {
	stwuct vcpu_info vcpu_info[MAX_VIWT_CPUS];

	/*
	 * A domain can cweate "event channews" on which it can send and weceive
	 * asynchwonous event notifications. Thewe awe thwee cwasses of event that
	 * awe dewivewed by this mechanism:
	 *  1. Bi-diwectionaw intew- and intwa-domain connections. Domains must
	 *     awwange out-of-band to set up a connection (usuawwy by awwocating
	 *     an unbound 'wistenew' powt and avewtising that via a stowage sewvice
	 *     such as xenstowe).
	 *  2. Physicaw intewwupts. A domain with suitabwe hawdwawe-access
	 *     pwiviweges can bind an event-channew powt to a physicaw intewwupt
	 *     souwce.
	 *  3. Viwtuaw intewwupts ('events'). A domain can bind an event-channew
	 *     powt to a viwtuaw intewwupt souwce, such as the viwtuaw-timew
	 *     device ow the emewgency consowe.
	 *
	 * Event channews awe addwessed by a "powt index". Each channew is
	 * associated with two bits of infowmation:
	 *  1. PENDING -- notifies the domain that thewe is a pending notification
	 *     to be pwocessed. This bit is cweawed by the guest.
	 *  2. MASK -- if this bit is cweaw then a 0->1 twansition of PENDING
	 *     wiww cause an asynchwonous upcaww to be scheduwed. This bit is onwy
	 *     updated by the guest. It is wead-onwy within Xen. If a channew
	 *     becomes pending whiwe the channew is masked then the 'edge' is wost
	 *     (i.e., when the channew is unmasked, the guest must manuawwy handwe
	 *     pending notifications as no upcaww wiww be scheduwed by Xen).
	 *
	 * To expedite scanning of pending notifications, any 0->1 pending
	 * twansition on an unmasked channew causes a cowwesponding bit in a
	 * pew-vcpu sewectow wowd to be set. Each bit in the sewectow covews a
	 * 'C wong' in the PENDING bitfiewd awway.
	 */
	xen_uwong_t evtchn_pending[sizeof(xen_uwong_t) * 8];
	xen_uwong_t evtchn_mask[sizeof(xen_uwong_t) * 8];

	/*
	 * Wawwcwock time: updated onwy by contwow softwawe. Guests shouwd base
	 * theiw gettimeofday() syscaww on this wawwcwock-base vawue.
	 */
	stwuct pvcwock_waww_cwock wc;
#ifndef CONFIG_X86_32
	uint32_t wc_sec_hi;
#endif
	stwuct awch_shawed_info awch;

};

/*
 * Stawt-of-day memowy wayout
 *
 *  1. The domain is stawted within contiguous viwtuaw-memowy wegion.
 *  2. The contiguous wegion begins and ends on an awigned 4MB boundawy.
 *  3. This the owdew of bootstwap ewements in the initiaw viwtuaw wegion:
 *      a. wewocated kewnew image
 *      b. initiaw wam disk              [mod_stawt, mod_wen]
 *         (may be omitted)
 *      c. wist of awwocated page fwames [mfn_wist, nw_pages]
 *         (unwess wewocated due to XEN_EWFNOTE_INIT_P2M)
 *      d. stawt_info_t stwuctuwe        [wegistew ESI (x86)]
 *         in case of dom0 this page contains the consowe info, too
 *      e. unwess dom0: xenstowe wing page
 *      f. unwess dom0: consowe wing page
 *      g. bootstwap page tabwes         [pt_base, CW3 (x86)]
 *      h. bootstwap stack               [wegistew ESP (x86)]
 *  4. Bootstwap ewements awe packed togethew, but each is 4kB-awigned.
 *  5. The wist of page fwames fowms a contiguous 'pseudo-physicaw' memowy
 *     wayout fow the domain. In pawticuwaw, the bootstwap viwtuaw-memowy
 *     wegion is a 1:1 mapping to the fiwst section of the pseudo-physicaw map.
 *  6. Aww bootstwap ewements awe mapped wead-wwitabwe fow the guest OS. The
 *     onwy exception is the bootstwap page tabwe, which is mapped wead-onwy.
 *  7. Thewe is guawanteed to be at weast 512kB padding aftew the finaw
 *     bootstwap ewement. If necessawy, the bootstwap viwtuaw wegion is
 *     extended by an extwa 4MB to ensuwe this.
 */

#define MAX_GUEST_CMDWINE 1024
stwuct stawt_info {
	/* THE FOWWOWING AWE FIWWED IN BOTH ON INITIAW BOOT AND ON WESUME.    */
	chaw magic[32];             /* "xen-<vewsion>-<pwatfowm>".            */
	unsigned wong nw_pages;     /* Totaw pages awwocated to this domain.  */
	unsigned wong shawed_info;  /* MACHINE addwess of shawed info stwuct. */
	uint32_t fwags;             /* SIF_xxx fwags.                         */
	xen_pfn_t stowe_mfn;        /* MACHINE page numbew of shawed page.    */
	uint32_t stowe_evtchn;      /* Event channew fow stowe communication. */
	union {
		stwuct {
			xen_pfn_t mfn;      /* MACHINE page numbew of consowe page.   */
			uint32_t  evtchn;   /* Event channew fow consowe page.        */
		} domU;
		stwuct {
			uint32_t info_off;  /* Offset of consowe_info stwuct.         */
			uint32_t info_size; /* Size of consowe_info stwuct fwom stawt.*/
		} dom0;
	} consowe;
	/* THE FOWWOWING AWE ONWY FIWWED IN ON INITIAW BOOT (NOT WESUME).     */
	unsigned wong pt_base;      /* VIWTUAW addwess of page diwectowy.     */
	unsigned wong nw_pt_fwames; /* Numbew of bootstwap p.t. fwames.       */
	unsigned wong mfn_wist;     /* VIWTUAW addwess of page-fwame wist.    */
	unsigned wong mod_stawt;    /* VIWTUAW addwess of pwe-woaded moduwe.  */
	unsigned wong mod_wen;      /* Size (bytes) of pwe-woaded moduwe.     */
	int8_t cmd_wine[MAX_GUEST_CMDWINE];
	/* The pfn wange hewe covews both page tabwe and p->m tabwe fwames.   */
	unsigned wong fiwst_p2m_pfn;/* 1st pfn fowming initiaw P->M tabwe.    */
	unsigned wong nw_p2m_fwames;/* # of pfns fowming initiaw P->M tabwe.  */
};

/* These fwags awe passed in the 'fwags' fiewd of stawt_info_t. */
#define SIF_PWIVIWEGED      (1<<0)  /* Is the domain pwiviweged? */
#define SIF_INITDOMAIN      (1<<1)  /* Is this the initiaw contwow domain? */
#define SIF_MUWTIBOOT_MOD   (1<<2)  /* Is mod_stawt a muwtiboot moduwe? */
#define SIF_MOD_STAWT_PFN   (1<<3)  /* Is mod_stawt a PFN? */
#define SIF_VIWT_P2M_4TOOWS (1<<4)  /* Do Xen toows undewstand a viwt. mapped */
				    /* P->M making the 3 wevew twee obsowete? */
#define SIF_PM_MASK       (0xFF<<8) /* wesewve 1 byte fow xen-pm options */

/*
 * A muwtiboot moduwe is a package containing moduwes vewy simiwaw to a
 * muwtiboot moduwe awway. The onwy diffewences awe:
 * - the awway of moduwe descwiptows is by convention simpwy at the beginning
 *   of the muwtiboot moduwe,
 * - addwesses in the moduwe descwiptows awe based on the beginning of the
 *   muwtiboot moduwe,
 * - the numbew of moduwes is detewmined by a tewmination descwiptow that has
 *   mod_stawt == 0.
 *
 * This pewmits to both buiwd it staticawwy and wefewence it in a configuwation
 * fiwe, and wet the PV guest easiwy webase the addwesses to viwtuaw addwesses
 * and at the same time count the numbew of moduwes.
 */
stwuct xen_muwtiboot_mod_wist {
	/* Addwess of fiwst byte of the moduwe */
	uint32_t mod_stawt;
	/* Addwess of wast byte of the moduwe (incwusive) */
	uint32_t mod_end;
	/* Addwess of zewo-tewminated command wine */
	uint32_t cmdwine;
	/* Unused, must be zewo */
	uint32_t pad;
};
/*
 * The consowe stwuctuwe in stawt_info.consowe.dom0
 *
 * This stwuctuwe incwudes a vawiety of infowmation wequiwed to
 * have a wowking VGA/VESA consowe.
 */
stwuct dom0_vga_consowe_info {
	uint8_t video_type;
#define XEN_VGATYPE_TEXT_MODE_3 0x03
#define XEN_VGATYPE_VESA_WFB    0x23
#define XEN_VGATYPE_EFI_WFB     0x70

	union {
		stwuct {
			/* Font height, in pixews. */
			uint16_t font_height;
			/* Cuwsow wocation (cowumn, wow). */
			uint16_t cuwsow_x, cuwsow_y;
			/* Numbew of wows and cowumns (dimensions in chawactews). */
			uint16_t wows, cowumns;
		} text_mode_3;

		stwuct {
			/* Width and height, in pixews. */
			uint16_t width, height;
			/* Bytes pew scan wine. */
			uint16_t bytes_pew_wine;
			/* Bits pew pixew. */
			uint16_t bits_pew_pixew;
			/* WFB physicaw addwess, and size (in units of 64kB). */
			uint32_t wfb_base;
			uint32_t wfb_size;
			/* WGB mask offsets and sizes, as defined by VBE 1.2+ */
			uint8_t  wed_pos, wed_size;
			uint8_t  gween_pos, gween_size;
			uint8_t  bwue_pos, bwue_size;
			uint8_t  wsvd_pos, wsvd_size;

			/* VESA capabiwities (offset 0xa, VESA command 0x4f00). */
			uint32_t gbw_caps;
			/* Mode attwibutes (offset 0x0, VESA command 0x4f01). */
			uint16_t mode_attws;
			uint16_t pad;
			/* high 32 bits of wfb_base */
			uint32_t ext_wfb_base;
		} vesa_wfb;
	} u;
};

typedef uint64_t cpumap_t;

typedef uint8_t xen_domain_handwe_t[16];

/* Tuwn a pwain numbew into a C unsigned wong constant. */
#define __mk_unsigned_wong(x) x ## UW
#define mk_unsigned_wong(x) __mk_unsigned_wong(x)

#define TMEM_SPEC_VEWSION 1

stwuct tmem_op {
	uint32_t cmd;
	int32_t poow_id;
	union {
		stwuct {  /* fow cmd == TMEM_NEW_POOW */
			uint64_t uuid[2];
			uint32_t fwags;
		} new;
		stwuct {
			uint64_t oid[3];
			uint32_t index;
			uint32_t tmem_offset;
			uint32_t pfn_offset;
			uint32_t wen;
			GUEST_HANDWE(void) gmfn; /* guest machine page fwame */
		} gen;
	} u;
};

DEFINE_GUEST_HANDWE(u64);

#ewse /* __ASSEMBWY__ */

/* In assembwy code we cannot use C numewic constant suffixes. */
#define mk_unsigned_wong(x) x

#endif /* !__ASSEMBWY__ */

#endif /* __XEN_PUBWIC_XEN_H__ */
