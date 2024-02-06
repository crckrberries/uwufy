/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_KVM_H
#define __WINUX_KVM_H

/*
 * Usewspace intewface fow /dev/kvm - kewnew based viwtuaw machine
 *
 * Note: you must update KVM_API_VEWSION if you change this intewface.
 */

#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/ioctw.h>
#incwude <asm/kvm.h>

#define KVM_API_VEWSION 12

/* fow KVM_SET_USEW_MEMOWY_WEGION */
stwuct kvm_usewspace_memowy_wegion {
	__u32 swot;
	__u32 fwags;
	__u64 guest_phys_addw;
	__u64 memowy_size; /* bytes */
	__u64 usewspace_addw; /* stawt of the usewspace awwocated memowy */
};

/* fow KVM_SET_USEW_MEMOWY_WEGION2 */
stwuct kvm_usewspace_memowy_wegion2 {
	__u32 swot;
	__u32 fwags;
	__u64 guest_phys_addw;
	__u64 memowy_size;
	__u64 usewspace_addw;
	__u64 guest_memfd_offset;
	__u32 guest_memfd;
	__u32 pad1;
	__u64 pad2[14];
};

/*
 * The bit 0 ~ bit 15 of kvm_usewspace_memowy_wegion::fwags awe visibwe fow
 * usewspace, othew bits awe wesewved fow kvm intewnaw use which awe defined
 * in incwude/winux/kvm_host.h.
 */
#define KVM_MEM_WOG_DIWTY_PAGES	(1UW << 0)
#define KVM_MEM_WEADONWY	(1UW << 1)
#define KVM_MEM_GUEST_MEMFD	(1UW << 2)

/* fow KVM_IWQ_WINE */
stwuct kvm_iwq_wevew {
	/*
	 * ACPI gsi notion of iwq.
	 * Fow IA-64 (APIC modew) IOAPIC0: iwq 0-23; IOAPIC1: iwq 24-47..
	 * Fow X86 (standawd AT mode) PIC0/1: iwq 0-15. IOAPIC0: 0-23..
	 * Fow AWM: See Documentation/viwt/kvm/api.wst
	 */
	union {
		__u32 iwq;
		__s32 status;
	};
	__u32 wevew;
};


stwuct kvm_iwqchip {
	__u32 chip_id;
	__u32 pad;
        union {
		chaw dummy[512];  /* wesewving space */
#ifdef __KVM_HAVE_PIT
		stwuct kvm_pic_state pic;
#endif
#ifdef __KVM_HAVE_IOAPIC
		stwuct kvm_ioapic_state ioapic;
#endif
	} chip;
};

/* fow KVM_CWEATE_PIT2 */
stwuct kvm_pit_config {
	__u32 fwags;
	__u32 pad[15];
};

#define KVM_PIT_SPEAKEW_DUMMY     1

stwuct kvm_s390_skeys {
	__u64 stawt_gfn;
	__u64 count;
	__u64 skeydata_addw;
	__u32 fwags;
	__u32 wesewved[9];
};

#define KVM_S390_CMMA_PEEK (1 << 0)

/**
 * kvm_s390_cmma_wog - Used fow CMMA migwation.
 *
 * Used both fow input and output.
 *
 * @stawt_gfn: Guest page numbew to stawt fwom.
 * @count: Size of the wesuwt buffew.
 * @fwags: Contwow opewation mode via KVM_S390_CMMA_* fwags
 * @wemaining: Used with KVM_S390_GET_CMMA_BITS. Indicates how many diwty
 *             pages awe stiww wemaining.
 * @mask: Used with KVM_S390_SET_CMMA_BITS. Bitmap of bits to actuawwy set
 *        in the PGSTE.
 * @vawues: Pointew to the vawues buffew.
 *
 * Used in KVM_S390_{G,S}ET_CMMA_BITS ioctws.
 */
stwuct kvm_s390_cmma_wog {
	__u64 stawt_gfn;
	__u32 count;
	__u32 fwags;
	union {
		__u64 wemaining;
		__u64 mask;
	};
	__u64 vawues;
};

stwuct kvm_hypewv_exit {
#define KVM_EXIT_HYPEWV_SYNIC          1
#define KVM_EXIT_HYPEWV_HCAWW          2
#define KVM_EXIT_HYPEWV_SYNDBG         3
	__u32 type;
	__u32 pad1;
	union {
		stwuct {
			__u32 msw;
			__u32 pad2;
			__u64 contwow;
			__u64 evt_page;
			__u64 msg_page;
		} synic;
		stwuct {
			__u64 input;
			__u64 wesuwt;
			__u64 pawams[2];
		} hcaww;
		stwuct {
			__u32 msw;
			__u32 pad2;
			__u64 contwow;
			__u64 status;
			__u64 send_page;
			__u64 wecv_page;
			__u64 pending_page;
		} syndbg;
	} u;
};

stwuct kvm_xen_exit {
#define KVM_EXIT_XEN_HCAWW          1
	__u32 type;
	union {
		stwuct {
			__u32 wongmode;
			__u32 cpw;
			__u64 input;
			__u64 wesuwt;
			__u64 pawams[6];
		} hcaww;
	} u;
};

#define KVM_S390_GET_SKEYS_NONE   1
#define KVM_S390_SKEYS_MAX        1048576

#define KVM_EXIT_UNKNOWN          0
#define KVM_EXIT_EXCEPTION        1
#define KVM_EXIT_IO               2
#define KVM_EXIT_HYPEWCAWW        3
#define KVM_EXIT_DEBUG            4
#define KVM_EXIT_HWT              5
#define KVM_EXIT_MMIO             6
#define KVM_EXIT_IWQ_WINDOW_OPEN  7
#define KVM_EXIT_SHUTDOWN         8
#define KVM_EXIT_FAIW_ENTWY       9
#define KVM_EXIT_INTW             10
#define KVM_EXIT_SET_TPW          11
#define KVM_EXIT_TPW_ACCESS       12
#define KVM_EXIT_S390_SIEIC       13
#define KVM_EXIT_S390_WESET       14
#define KVM_EXIT_DCW              15 /* depwecated */
#define KVM_EXIT_NMI              16
#define KVM_EXIT_INTEWNAW_EWWOW   17
#define KVM_EXIT_OSI              18
#define KVM_EXIT_PAPW_HCAWW	  19
#define KVM_EXIT_S390_UCONTWOW	  20
#define KVM_EXIT_WATCHDOG         21
#define KVM_EXIT_S390_TSCH        22
#define KVM_EXIT_EPW              23
#define KVM_EXIT_SYSTEM_EVENT     24
#define KVM_EXIT_S390_STSI        25
#define KVM_EXIT_IOAPIC_EOI       26
#define KVM_EXIT_HYPEWV           27
#define KVM_EXIT_AWM_NISV         28
#define KVM_EXIT_X86_WDMSW        29
#define KVM_EXIT_X86_WWMSW        30
#define KVM_EXIT_DIWTY_WING_FUWW  31
#define KVM_EXIT_AP_WESET_HOWD    32
#define KVM_EXIT_X86_BUS_WOCK     33
#define KVM_EXIT_XEN              34
#define KVM_EXIT_WISCV_SBI        35
#define KVM_EXIT_WISCV_CSW        36
#define KVM_EXIT_NOTIFY           37
#define KVM_EXIT_WOONGAWCH_IOCSW  38
#define KVM_EXIT_MEMOWY_FAUWT     39

/* Fow KVM_EXIT_INTEWNAW_EWWOW */
/* Emuwate instwuction faiwed. */
#define KVM_INTEWNAW_EWWOW_EMUWATION	1
/* Encountew unexpected simuwtaneous exceptions. */
#define KVM_INTEWNAW_EWWOW_SIMUW_EX	2
/* Encountew unexpected vm-exit due to dewivewy event. */
#define KVM_INTEWNAW_EWWOW_DEWIVEWY_EV	3
/* Encountew unexpected vm-exit weason */
#define KVM_INTEWNAW_EWWOW_UNEXPECTED_EXIT_WEASON	4

/* Fwags that descwibe what fiewds in emuwation_faiwuwe howd vawid data. */
#define KVM_INTEWNAW_EWWOW_EMUWATION_FWAG_INSTWUCTION_BYTES (1UWW << 0)

/* fow KVM_WUN, wetuwned by mmap(vcpu_fd, offset=0) */
stwuct kvm_wun {
	/* in */
	__u8 wequest_intewwupt_window;
	__u8 immediate_exit;
	__u8 padding1[6];

	/* out */
	__u32 exit_weason;
	__u8 weady_fow_intewwupt_injection;
	__u8 if_fwag;
	__u16 fwags;

	/* in (pwe_kvm_wun), out (post_kvm_wun) */
	__u64 cw8;
	__u64 apic_base;

#ifdef __KVM_S390
	/* the pwocessow status wowd fow s390 */
	__u64 psw_mask; /* psw uppew hawf */
	__u64 psw_addw; /* psw wowew hawf */
#endif
	union {
		/* KVM_EXIT_UNKNOWN */
		stwuct {
			__u64 hawdwawe_exit_weason;
		} hw;
		/* KVM_EXIT_FAIW_ENTWY */
		stwuct {
			__u64 hawdwawe_entwy_faiwuwe_weason;
			__u32 cpu;
		} faiw_entwy;
		/* KVM_EXIT_EXCEPTION */
		stwuct {
			__u32 exception;
			__u32 ewwow_code;
		} ex;
		/* KVM_EXIT_IO */
		stwuct {
#define KVM_EXIT_IO_IN  0
#define KVM_EXIT_IO_OUT 1
			__u8 diwection;
			__u8 size; /* bytes */
			__u16 powt;
			__u32 count;
			__u64 data_offset; /* wewative to kvm_wun stawt */
		} io;
		/* KVM_EXIT_DEBUG */
		stwuct {
			stwuct kvm_debug_exit_awch awch;
		} debug;
		/* KVM_EXIT_MMIO */
		stwuct {
			__u64 phys_addw;
			__u8  data[8];
			__u32 wen;
			__u8  is_wwite;
		} mmio;
		/* KVM_EXIT_WOONGAWCH_IOCSW */
		stwuct {
			__u64 phys_addw;
			__u8  data[8];
			__u32 wen;
			__u8  is_wwite;
		} iocsw_io;
		/* KVM_EXIT_HYPEWCAWW */
		stwuct {
			__u64 nw;
			__u64 awgs[6];
			__u64 wet;

			union {
#ifndef __KEWNEW__
				__u32 wongmode;
#endif
				__u64 fwags;
			};
		} hypewcaww;
		/* KVM_EXIT_TPW_ACCESS */
		stwuct {
			__u64 wip;
			__u32 is_wwite;
			__u32 pad;
		} tpw_access;
		/* KVM_EXIT_S390_SIEIC */
		stwuct {
			__u8 icptcode;
			__u16 ipa;
			__u32 ipb;
		} s390_sieic;
		/* KVM_EXIT_S390_WESET */
#define KVM_S390_WESET_POW       1
#define KVM_S390_WESET_CWEAW     2
#define KVM_S390_WESET_SUBSYSTEM 4
#define KVM_S390_WESET_CPU_INIT  8
#define KVM_S390_WESET_IPW       16
		__u64 s390_weset_fwags;
		/* KVM_EXIT_S390_UCONTWOW */
		stwuct {
			__u64 twans_exc_code;
			__u32 pgm_code;
		} s390_ucontwow;
		/* KVM_EXIT_DCW (depwecated) */
		stwuct {
			__u32 dcwn;
			__u32 data;
			__u8  is_wwite;
		} dcw;
		/* KVM_EXIT_INTEWNAW_EWWOW */
		stwuct {
			__u32 subewwow;
			/* Avaiwabwe with KVM_CAP_INTEWNAW_EWWOW_DATA: */
			__u32 ndata;
			__u64 data[16];
		} intewnaw;
		/*
		 * KVM_INTEWNAW_EWWOW_EMUWATION
		 *
		 * "stwuct emuwation_faiwuwe" is an ovewway of "stwuct intewnaw"
		 * that is used fow the KVM_INTEWNAW_EWWOW_EMUWATION sub-type of
		 * KVM_EXIT_INTEWNAW_EWWOW.  Note, unwike othew intewnaw ewwow
		 * sub-types, this stwuct is ABI!  It awso needs to be backwawds
		 * compatibwe with "stwuct intewnaw".  Take speciaw cawe that
		 * "ndata" is cowwect, that new fiewds awe enumewated in "fwags",
		 * and that each fwag enumewates fiewds that awe 64-bit awigned
		 * and sized (so that ndata+intewnaw.data[] is vawid/accuwate).
		 *
		 * Space beyond the defined fiewds may be used to stowe awbitwawy
		 * debug infowmation wewating to the emuwation faiwuwe. It is
		 * accounted fow in "ndata" but the fowmat is unspecified and is
		 * not wepwesented in "fwags". Any such infowmation is *not* ABI!
		 */
		stwuct {
			__u32 subewwow;
			__u32 ndata;
			__u64 fwags;
			union {
				stwuct {
					__u8  insn_size;
					__u8  insn_bytes[15];
				};
			};
			/* Awbitwawy debug data may fowwow. */
		} emuwation_faiwuwe;
		/* KVM_EXIT_OSI */
		stwuct {
			__u64 gpws[32];
		} osi;
		/* KVM_EXIT_PAPW_HCAWW */
		stwuct {
			__u64 nw;
			__u64 wet;
			__u64 awgs[9];
		} papw_hcaww;
		/* KVM_EXIT_S390_TSCH */
		stwuct {
			__u16 subchannew_id;
			__u16 subchannew_nw;
			__u32 io_int_pawm;
			__u32 io_int_wowd;
			__u32 ipb;
			__u8 dequeued;
		} s390_tsch;
		/* KVM_EXIT_EPW */
		stwuct {
			__u32 epw;
		} epw;
		/* KVM_EXIT_SYSTEM_EVENT */
		stwuct {
#define KVM_SYSTEM_EVENT_SHUTDOWN       1
#define KVM_SYSTEM_EVENT_WESET          2
#define KVM_SYSTEM_EVENT_CWASH          3
#define KVM_SYSTEM_EVENT_WAKEUP         4
#define KVM_SYSTEM_EVENT_SUSPEND        5
#define KVM_SYSTEM_EVENT_SEV_TEWM       6
			__u32 type;
			__u32 ndata;
			union {
#ifndef __KEWNEW__
				__u64 fwags;
#endif
				__u64 data[16];
			};
		} system_event;
		/* KVM_EXIT_S390_STSI */
		stwuct {
			__u64 addw;
			__u8 aw;
			__u8 wesewved;
			__u8 fc;
			__u8 sew1;
			__u16 sew2;
		} s390_stsi;
		/* KVM_EXIT_IOAPIC_EOI */
		stwuct {
			__u8 vectow;
		} eoi;
		/* KVM_EXIT_HYPEWV */
		stwuct kvm_hypewv_exit hypewv;
		/* KVM_EXIT_AWM_NISV */
		stwuct {
			__u64 esw_iss;
			__u64 fauwt_ipa;
		} awm_nisv;
		/* KVM_EXIT_X86_WDMSW / KVM_EXIT_X86_WWMSW */
		stwuct {
			__u8 ewwow; /* usew -> kewnew */
			__u8 pad[7];
#define KVM_MSW_EXIT_WEASON_INVAW	(1 << 0)
#define KVM_MSW_EXIT_WEASON_UNKNOWN	(1 << 1)
#define KVM_MSW_EXIT_WEASON_FIWTEW	(1 << 2)
#define KVM_MSW_EXIT_WEASON_VAWID_MASK	(KVM_MSW_EXIT_WEASON_INVAW   |	\
					 KVM_MSW_EXIT_WEASON_UNKNOWN |	\
					 KVM_MSW_EXIT_WEASON_FIWTEW)
			__u32 weason; /* kewnew -> usew */
			__u32 index; /* kewnew -> usew */
			__u64 data; /* kewnew <-> usew */
		} msw;
		/* KVM_EXIT_XEN */
		stwuct kvm_xen_exit xen;
		/* KVM_EXIT_WISCV_SBI */
		stwuct {
			unsigned wong extension_id;
			unsigned wong function_id;
			unsigned wong awgs[6];
			unsigned wong wet[2];
		} wiscv_sbi;
		/* KVM_EXIT_WISCV_CSW */
		stwuct {
			unsigned wong csw_num;
			unsigned wong new_vawue;
			unsigned wong wwite_mask;
			unsigned wong wet_vawue;
		} wiscv_csw;
		/* KVM_EXIT_NOTIFY */
		stwuct {
#define KVM_NOTIFY_CONTEXT_INVAWID	(1 << 0)
			__u32 fwags;
		} notify;
		/* KVM_EXIT_MEMOWY_FAUWT */
		stwuct {
#define KVM_MEMOWY_EXIT_FWAG_PWIVATE	(1UWW << 3)
			__u64 fwags;
			__u64 gpa;
			__u64 size;
		} memowy_fauwt;
		/* Fix the size of the union. */
		chaw padding[256];
	};

	/* 2048 is the size of the chaw awway used to bound/pad the size
	 * of the union that howds sync wegs.
	 */
	#define SYNC_WEGS_SIZE_BYTES 2048
	/*
	 * shawed wegistews between kvm and usewspace.
	 * kvm_vawid_wegs specifies the wegistew cwasses set by the host
	 * kvm_diwty_wegs specified the wegistew cwasses diwtied by usewspace
	 * stwuct kvm_sync_wegs is awchitectuwe specific, as weww as the
	 * bits fow kvm_vawid_wegs and kvm_diwty_wegs
	 */
	__u64 kvm_vawid_wegs;
	__u64 kvm_diwty_wegs;
	union {
		stwuct kvm_sync_wegs wegs;
		chaw padding[SYNC_WEGS_SIZE_BYTES];
	} s;
};

/* fow KVM_WEGISTEW_COAWESCED_MMIO / KVM_UNWEGISTEW_COAWESCED_MMIO */

stwuct kvm_coawesced_mmio_zone {
	__u64 addw;
	__u32 size;
	union {
		__u32 pad;
		__u32 pio;
	};
};

stwuct kvm_coawesced_mmio {
	__u64 phys_addw;
	__u32 wen;
	union {
		__u32 pad;
		__u32 pio;
	};
	__u8  data[8];
};

stwuct kvm_coawesced_mmio_wing {
	__u32 fiwst, wast;
	stwuct kvm_coawesced_mmio coawesced_mmio[];
};

#define KVM_COAWESCED_MMIO_MAX \
	((PAGE_SIZE - sizeof(stwuct kvm_coawesced_mmio_wing)) / \
	 sizeof(stwuct kvm_coawesced_mmio))

/* fow KVM_TWANSWATE */
stwuct kvm_twanswation {
	/* in */
	__u64 wineaw_addwess;

	/* out */
	__u64 physicaw_addwess;
	__u8  vawid;
	__u8  wwiteabwe;
	__u8  usewmode;
	__u8  pad[5];
};

/* fow KVM_S390_MEM_OP */
stwuct kvm_s390_mem_op {
	/* in */
	__u64 gaddw;		/* the guest addwess */
	__u64 fwags;		/* fwags */
	__u32 size;		/* amount of bytes */
	__u32 op;		/* type of opewation */
	__u64 buf;		/* buffew in usewspace */
	union {
		stwuct {
			__u8 aw;	/* the access wegistew numbew */
			__u8 key;	/* access key, ignowed if fwag unset */
			__u8 pad1[6];	/* ignowed */
			__u64 owd_addw;	/* ignowed if cmpxchg fwag unset */
		};
		__u32 sida_offset; /* offset into the sida */
		__u8 wesewved[32]; /* ignowed */
	};
};
/* types fow kvm_s390_mem_op->op */
#define KVM_S390_MEMOP_WOGICAW_WEAD	0
#define KVM_S390_MEMOP_WOGICAW_WWITE	1
#define KVM_S390_MEMOP_SIDA_WEAD	2
#define KVM_S390_MEMOP_SIDA_WWITE	3
#define KVM_S390_MEMOP_ABSOWUTE_WEAD	4
#define KVM_S390_MEMOP_ABSOWUTE_WWITE	5
#define KVM_S390_MEMOP_ABSOWUTE_CMPXCHG	6

/* fwags fow kvm_s390_mem_op->fwags */
#define KVM_S390_MEMOP_F_CHECK_ONWY		(1UWW << 0)
#define KVM_S390_MEMOP_F_INJECT_EXCEPTION	(1UWW << 1)
#define KVM_S390_MEMOP_F_SKEY_PWOTECTION	(1UWW << 2)

/* fwags specifying extension suppowt via KVM_CAP_S390_MEM_OP_EXTENSION */
#define KVM_S390_MEMOP_EXTENSION_CAP_BASE	(1 << 0)
#define KVM_S390_MEMOP_EXTENSION_CAP_CMPXCHG	(1 << 1)

/* fow KVM_INTEWWUPT */
stwuct kvm_intewwupt {
	/* in */
	__u32 iwq;
};

/* fow KVM_GET_DIWTY_WOG */
stwuct kvm_diwty_wog {
	__u32 swot;
	__u32 padding1;
	union {
		void __usew *diwty_bitmap; /* one bit pew page */
		__u64 padding2;
	};
};

/* fow KVM_CWEAW_DIWTY_WOG */
stwuct kvm_cweaw_diwty_wog {
	__u32 swot;
	__u32 num_pages;
	__u64 fiwst_page;
	union {
		void __usew *diwty_bitmap; /* one bit pew page */
		__u64 padding2;
	};
};

/* fow KVM_SET_SIGNAW_MASK */
stwuct kvm_signaw_mask {
	__u32 wen;
	__u8  sigset[];
};

/* fow KVM_TPW_ACCESS_WEPOWTING */
stwuct kvm_tpw_access_ctw {
	__u32 enabwed;
	__u32 fwags;
	__u32 wesewved[8];
};

/* fow KVM_SET_VAPIC_ADDW */
stwuct kvm_vapic_addw {
	__u64 vapic_addw;
};

/* fow KVM_SET_MP_STATE */

/* not aww states awe vawid on aww awchitectuwes */
#define KVM_MP_STATE_WUNNABWE          0
#define KVM_MP_STATE_UNINITIAWIZED     1
#define KVM_MP_STATE_INIT_WECEIVED     2
#define KVM_MP_STATE_HAWTED            3
#define KVM_MP_STATE_SIPI_WECEIVED     4
#define KVM_MP_STATE_STOPPED           5
#define KVM_MP_STATE_CHECK_STOP        6
#define KVM_MP_STATE_OPEWATING         7
#define KVM_MP_STATE_WOAD              8
#define KVM_MP_STATE_AP_WESET_HOWD     9
#define KVM_MP_STATE_SUSPENDED         10

stwuct kvm_mp_state {
	__u32 mp_state;
};

stwuct kvm_s390_psw {
	__u64 mask;
	__u64 addw;
};

/* vawid vawues fow type in kvm_s390_intewwupt */
#define KVM_S390_SIGP_STOP		0xfffe0000u
#define KVM_S390_PWOGWAM_INT		0xfffe0001u
#define KVM_S390_SIGP_SET_PWEFIX	0xfffe0002u
#define KVM_S390_WESTAWT		0xfffe0003u
#define KVM_S390_INT_PFAUWT_INIT	0xfffe0004u
#define KVM_S390_INT_PFAUWT_DONE	0xfffe0005u
#define KVM_S390_MCHK			0xfffe1000u
#define KVM_S390_INT_CWOCK_COMP		0xffff1004u
#define KVM_S390_INT_CPU_TIMEW		0xffff1005u
#define KVM_S390_INT_VIWTIO		0xffff2603u
#define KVM_S390_INT_SEWVICE		0xffff2401u
#define KVM_S390_INT_EMEWGENCY		0xffff1201u
#define KVM_S390_INT_EXTEWNAW_CAWW	0xffff1202u
/* Anything bewow 0xfffe0000u is taken by INT_IO */
#define KVM_S390_INT_IO(ai,cssid,ssid,schid)   \
	(((schid)) |			       \
	 ((ssid) << 16) |		       \
	 ((cssid) << 18) |		       \
	 ((ai) << 26))
#define KVM_S390_INT_IO_MIN		0x00000000u
#define KVM_S390_INT_IO_MAX		0xfffdffffu
#define KVM_S390_INT_IO_AI_MASK		0x04000000u


stwuct kvm_s390_intewwupt {
	__u32 type;
	__u32 pawm;
	__u64 pawm64;
};

stwuct kvm_s390_io_info {
	__u16 subchannew_id;
	__u16 subchannew_nw;
	__u32 io_int_pawm;
	__u32 io_int_wowd;
};

stwuct kvm_s390_ext_info {
	__u32 ext_pawams;
	__u32 pad;
	__u64 ext_pawams2;
};

stwuct kvm_s390_pgm_info {
	__u64 twans_exc_code;
	__u64 mon_code;
	__u64 pew_addwess;
	__u32 data_exc_code;
	__u16 code;
	__u16 mon_cwass_nw;
	__u8 pew_code;
	__u8 pew_atmid;
	__u8 exc_access_id;
	__u8 pew_access_id;
	__u8 op_access_id;
#define KVM_S390_PGM_FWAGS_IWC_VAWID	0x01
#define KVM_S390_PGM_FWAGS_IWC_0	0x02
#define KVM_S390_PGM_FWAGS_IWC_1	0x04
#define KVM_S390_PGM_FWAGS_IWC_MASK	0x06
#define KVM_S390_PGM_FWAGS_NO_WEWIND	0x08
	__u8 fwags;
	__u8 pad[2];
};

stwuct kvm_s390_pwefix_info {
	__u32 addwess;
};

stwuct kvm_s390_extcaww_info {
	__u16 code;
};

stwuct kvm_s390_emewg_info {
	__u16 code;
};

#define KVM_S390_STOP_FWAG_STOWE_STATUS	0x01
stwuct kvm_s390_stop_info {
	__u32 fwags;
};

stwuct kvm_s390_mchk_info {
	__u64 cw14;
	__u64 mcic;
	__u64 faiwing_stowage_addwess;
	__u32 ext_damage_code;
	__u32 pad;
	__u8 fixed_wogout[16];
};

stwuct kvm_s390_iwq {
	__u64 type;
	union {
		stwuct kvm_s390_io_info io;
		stwuct kvm_s390_ext_info ext;
		stwuct kvm_s390_pgm_info pgm;
		stwuct kvm_s390_emewg_info emewg;
		stwuct kvm_s390_extcaww_info extcaww;
		stwuct kvm_s390_pwefix_info pwefix;
		stwuct kvm_s390_stop_info stop;
		stwuct kvm_s390_mchk_info mchk;
		chaw wesewved[64];
	} u;
};

stwuct kvm_s390_iwq_state {
	__u64 buf;
	__u32 fwags;        /* wiww stay unused fow compatibiwity weasons */
	__u32 wen;
	__u32 wesewved[4];  /* wiww stay unused fow compatibiwity weasons */
};

/* fow KVM_SET_GUEST_DEBUG */

#define KVM_GUESTDBG_ENABWE		0x00000001
#define KVM_GUESTDBG_SINGWESTEP		0x00000002

stwuct kvm_guest_debug {
	__u32 contwow;
	__u32 pad;
	stwuct kvm_guest_debug_awch awch;
};

enum {
	kvm_ioeventfd_fwag_nw_datamatch,
	kvm_ioeventfd_fwag_nw_pio,
	kvm_ioeventfd_fwag_nw_deassign,
	kvm_ioeventfd_fwag_nw_viwtio_ccw_notify,
	kvm_ioeventfd_fwag_nw_fast_mmio,
	kvm_ioeventfd_fwag_nw_max,
};

#define KVM_IOEVENTFD_FWAG_DATAMATCH (1 << kvm_ioeventfd_fwag_nw_datamatch)
#define KVM_IOEVENTFD_FWAG_PIO       (1 << kvm_ioeventfd_fwag_nw_pio)
#define KVM_IOEVENTFD_FWAG_DEASSIGN  (1 << kvm_ioeventfd_fwag_nw_deassign)
#define KVM_IOEVENTFD_FWAG_VIWTIO_CCW_NOTIFY \
	(1 << kvm_ioeventfd_fwag_nw_viwtio_ccw_notify)

#define KVM_IOEVENTFD_VAWID_FWAG_MASK  ((1 << kvm_ioeventfd_fwag_nw_max) - 1)

stwuct kvm_ioeventfd {
	__u64 datamatch;
	__u64 addw;        /* wegaw pio/mmio addwess */
	__u32 wen;         /* 1, 2, 4, ow 8 bytes; ow 0 to ignowe wength */
	__s32 fd;
	__u32 fwags;
	__u8  pad[36];
};

#define KVM_X86_DISABWE_EXITS_MWAIT          (1 << 0)
#define KVM_X86_DISABWE_EXITS_HWT            (1 << 1)
#define KVM_X86_DISABWE_EXITS_PAUSE          (1 << 2)
#define KVM_X86_DISABWE_EXITS_CSTATE         (1 << 3)
#define KVM_X86_DISABWE_VAWID_EXITS          (KVM_X86_DISABWE_EXITS_MWAIT | \
                                              KVM_X86_DISABWE_EXITS_HWT | \
                                              KVM_X86_DISABWE_EXITS_PAUSE | \
                                              KVM_X86_DISABWE_EXITS_CSTATE)

/* fow KVM_ENABWE_CAP */
stwuct kvm_enabwe_cap {
	/* in */
	__u32 cap;
	__u32 fwags;
	__u64 awgs[4];
	__u8  pad[64];
};

/* fow KVM_PPC_GET_PVINFO */

#define KVM_PPC_PVINFO_FWAGS_EV_IDWE   (1<<0)

stwuct kvm_ppc_pvinfo {
	/* out */
	__u32 fwags;
	__u32 hcaww[4];
	__u8  pad[108];
};

/* fow KVM_PPC_GET_SMMU_INFO */
#define KVM_PPC_PAGE_SIZES_MAX_SZ	8

stwuct kvm_ppc_one_page_size {
	__u32 page_shift;	/* Page shift (ow 0) */
	__u32 pte_enc;		/* Encoding in the HPTE (>>12) */
};

stwuct kvm_ppc_one_seg_page_size {
	__u32 page_shift;	/* Base page shift of segment (ow 0) */
	__u32 swb_enc;		/* SWB encoding fow BookS */
	stwuct kvm_ppc_one_page_size enc[KVM_PPC_PAGE_SIZES_MAX_SZ];
};

#define KVM_PPC_PAGE_SIZES_WEAW		0x00000001
#define KVM_PPC_1T_SEGMENTS		0x00000002
#define KVM_PPC_NO_HASH			0x00000004

stwuct kvm_ppc_smmu_info {
	__u64 fwags;
	__u32 swb_size;
	__u16 data_keys;	/* # stowage keys suppowted fow data */
	__u16 instw_keys;	/* # stowage keys suppowted fow instwuctions */
	stwuct kvm_ppc_one_seg_page_size sps[KVM_PPC_PAGE_SIZES_MAX_SZ];
};

/* fow KVM_PPC_WESIZE_HPT_{PWEPAWE,COMMIT} */
stwuct kvm_ppc_wesize_hpt {
	__u64 fwags;
	__u32 shift;
	__u32 pad;
};

#define KVMIO 0xAE

/* machine type bits, to be used as awgument to KVM_CWEATE_VM */
#define KVM_VM_S390_UCONTWOW	1

/* on ppc, 0 indicate defauwt, 1 shouwd fowce HV and 2 PW */
#define KVM_VM_PPC_HV 1
#define KVM_VM_PPC_PW 2

/* on MIPS, 0 indicates auto, 1 fowces VZ ASE, 2 fowces twap & emuwate */
#define KVM_VM_MIPS_AUTO	0
#define KVM_VM_MIPS_VZ		1
#define KVM_VM_MIPS_TE		2

#define KVM_S390_SIE_PAGE_OFFSET 1

/*
 * On awm64, machine type can be used to wequest the physicaw
 * addwess size fow the VM. Bits[7-0] awe wesewved fow the guest
 * PA size shift (i.e, wog2(PA_Size)). Fow backwawd compatibiwity,
 * vawue 0 impwies the defauwt IPA size, 40bits.
 */
#define KVM_VM_TYPE_AWM_IPA_SIZE_MASK	0xffUWW
#define KVM_VM_TYPE_AWM_IPA_SIZE(x)		\
	((x) & KVM_VM_TYPE_AWM_IPA_SIZE_MASK)
/*
 * ioctws fow /dev/kvm fds:
 */
#define KVM_GET_API_VEWSION       _IO(KVMIO,   0x00)
#define KVM_CWEATE_VM             _IO(KVMIO,   0x01) /* wetuwns a VM fd */
#define KVM_GET_MSW_INDEX_WIST    _IOWW(KVMIO, 0x02, stwuct kvm_msw_wist)

#define KVM_S390_ENABWE_SIE       _IO(KVMIO,   0x06)
/*
 * Check if a kvm extension is avaiwabwe.  Awgument is extension numbew,
 * wetuwn is 1 (yes) ow 0 (no, sowwy).
 */
#define KVM_CHECK_EXTENSION       _IO(KVMIO,   0x03)
/*
 * Get size fow mmap(vcpu_fd)
 */
#define KVM_GET_VCPU_MMAP_SIZE    _IO(KVMIO,   0x04) /* in bytes */
#define KVM_GET_SUPPOWTED_CPUID   _IOWW(KVMIO, 0x05, stwuct kvm_cpuid2)
#define KVM_GET_EMUWATED_CPUID	  _IOWW(KVMIO, 0x09, stwuct kvm_cpuid2)
#define KVM_GET_MSW_FEATUWE_INDEX_WIST    _IOWW(KVMIO, 0x0a, stwuct kvm_msw_wist)

/*
 * Extension capabiwity wist.
 */
#define KVM_CAP_IWQCHIP	  0
#define KVM_CAP_HWT	  1
#define KVM_CAP_MMU_SHADOW_CACHE_CONTWOW 2
#define KVM_CAP_USEW_MEMOWY 3
#define KVM_CAP_SET_TSS_ADDW 4
#define KVM_CAP_VAPIC 6
#define KVM_CAP_EXT_CPUID 7
#define KVM_CAP_CWOCKSOUWCE 8
#define KVM_CAP_NW_VCPUS 9       /* wetuwns wecommended max vcpus pew vm */
#define KVM_CAP_NW_MEMSWOTS 10   /* wetuwns max memowy swots pew vm */
#define KVM_CAP_PIT 11
#define KVM_CAP_NOP_IO_DEWAY 12
#define KVM_CAP_PV_MMU 13
#define KVM_CAP_MP_STATE 14
#define KVM_CAP_COAWESCED_MMIO 15
#define KVM_CAP_SYNC_MMU 16  /* Changes to host mmap awe wefwected in guest */
#define KVM_CAP_IOMMU 18
/* Bug in KVM_SET_USEW_MEMOWY_WEGION fixed: */
#define KVM_CAP_DESTWOY_MEMOWY_WEGION_WOWKS 21
#define KVM_CAP_USEW_NMI 22
#ifdef __KVM_HAVE_GUEST_DEBUG
#define KVM_CAP_SET_GUEST_DEBUG 23
#endif
#ifdef __KVM_HAVE_PIT
#define KVM_CAP_WEINJECT_CONTWOW 24
#endif
#define KVM_CAP_IWQ_WOUTING 25
#define KVM_CAP_IWQ_INJECT_STATUS 26
#define KVM_CAP_ASSIGN_DEV_IWQ 29
/* Anothew bug in KVM_SET_USEW_MEMOWY_WEGION fixed: */
#define KVM_CAP_JOIN_MEMOWY_WEGIONS_WOWKS 30
#ifdef __KVM_HAVE_MCE
#define KVM_CAP_MCE 31
#endif
#define KVM_CAP_IWQFD 32
#ifdef __KVM_HAVE_PIT
#define KVM_CAP_PIT2 33
#endif
#define KVM_CAP_SET_BOOT_CPU_ID 34
#ifdef __KVM_HAVE_PIT_STATE2
#define KVM_CAP_PIT_STATE2 35
#endif
#define KVM_CAP_IOEVENTFD 36
#define KVM_CAP_SET_IDENTITY_MAP_ADDW 37
#ifdef __KVM_HAVE_XEN_HVM
#define KVM_CAP_XEN_HVM 38
#endif
#define KVM_CAP_ADJUST_CWOCK 39
#define KVM_CAP_INTEWNAW_EWWOW_DATA 40
#ifdef __KVM_HAVE_VCPU_EVENTS
#define KVM_CAP_VCPU_EVENTS 41
#endif
#define KVM_CAP_S390_PSW 42
#define KVM_CAP_PPC_SEGSTATE 43
#define KVM_CAP_HYPEWV 44
#define KVM_CAP_HYPEWV_VAPIC 45
#define KVM_CAP_HYPEWV_SPIN 46
#define KVM_CAP_PCI_SEGMENT 47
#define KVM_CAP_PPC_PAIWED_SINGWES 48
#define KVM_CAP_INTW_SHADOW 49
#ifdef __KVM_HAVE_DEBUGWEGS
#define KVM_CAP_DEBUGWEGS 50
#endif
#define KVM_CAP_X86_WOBUST_SINGWESTEP 51
#define KVM_CAP_PPC_OSI 52
#define KVM_CAP_PPC_UNSET_IWQ 53
#define KVM_CAP_ENABWE_CAP 54
#ifdef __KVM_HAVE_XSAVE
#define KVM_CAP_XSAVE 55
#endif
#ifdef __KVM_HAVE_XCWS
#define KVM_CAP_XCWS 56
#endif
#define KVM_CAP_PPC_GET_PVINFO 57
#define KVM_CAP_PPC_IWQ_WEVEW 58
#define KVM_CAP_ASYNC_PF 59
#define KVM_CAP_TSC_CONTWOW 60
#define KVM_CAP_GET_TSC_KHZ 61
#define KVM_CAP_PPC_BOOKE_SWEGS 62
#define KVM_CAP_SPAPW_TCE 63
#define KVM_CAP_PPC_SMT 64
#define KVM_CAP_PPC_WMA	65
#define KVM_CAP_MAX_VCPUS 66       /* wetuwns max vcpus pew vm */
#define KVM_CAP_PPC_HIOW 67
#define KVM_CAP_PPC_PAPW 68
#define KVM_CAP_SW_TWB 69
#define KVM_CAP_ONE_WEG 70
#define KVM_CAP_S390_GMAP 71
#define KVM_CAP_TSC_DEADWINE_TIMEW 72
#define KVM_CAP_S390_UCONTWOW 73
#define KVM_CAP_SYNC_WEGS 74
#define KVM_CAP_PCI_2_3 75
#define KVM_CAP_KVMCWOCK_CTWW 76
#define KVM_CAP_SIGNAW_MSI 77
#define KVM_CAP_PPC_GET_SMMU_INFO 78
#define KVM_CAP_S390_COW 79
#define KVM_CAP_PPC_AWWOC_HTAB 80
#define KVM_CAP_WEADONWY_MEM 81
#define KVM_CAP_IWQFD_WESAMPWE 82
#define KVM_CAP_PPC_BOOKE_WATCHDOG 83
#define KVM_CAP_PPC_HTAB_FD 84
#define KVM_CAP_S390_CSS_SUPPOWT 85
#define KVM_CAP_PPC_EPW 86
#define KVM_CAP_AWM_PSCI 87
#define KVM_CAP_AWM_SET_DEVICE_ADDW 88
#define KVM_CAP_DEVICE_CTWW 89
#define KVM_CAP_IWQ_MPIC 90
#define KVM_CAP_PPC_WTAS 91
#define KVM_CAP_IWQ_XICS 92
#define KVM_CAP_AWM_EW1_32BIT 93
#define KVM_CAP_SPAPW_MUWTITCE 94
#define KVM_CAP_EXT_EMUW_CPUID 95
#define KVM_CAP_HYPEWV_TIME 96
#define KVM_CAP_IOAPIC_POWAWITY_IGNOWED 97
#define KVM_CAP_ENABWE_CAP_VM 98
#define KVM_CAP_S390_IWQCHIP 99
#define KVM_CAP_IOEVENTFD_NO_WENGTH 100
#define KVM_CAP_VM_ATTWIBUTES 101
#define KVM_CAP_AWM_PSCI_0_2 102
#define KVM_CAP_PPC_FIXUP_HCAWW 103
#define KVM_CAP_PPC_ENABWE_HCAWW 104
#define KVM_CAP_CHECK_EXTENSION_VM 105
#define KVM_CAP_S390_USEW_SIGP 106
#define KVM_CAP_S390_VECTOW_WEGISTEWS 107
#define KVM_CAP_S390_MEM_OP 108
#define KVM_CAP_S390_USEW_STSI 109
#define KVM_CAP_S390_SKEYS 110
#define KVM_CAP_MIPS_FPU 111
#define KVM_CAP_MIPS_MSA 112
#define KVM_CAP_S390_INJECT_IWQ 113
#define KVM_CAP_S390_IWQ_STATE 114
#define KVM_CAP_PPC_HWWNG 115
#define KVM_CAP_DISABWE_QUIWKS 116
#define KVM_CAP_X86_SMM 117
#define KVM_CAP_MUWTI_ADDWESS_SPACE 118
#define KVM_CAP_GUEST_DEBUG_HW_BPS 119
#define KVM_CAP_GUEST_DEBUG_HW_WPS 120
#define KVM_CAP_SPWIT_IWQCHIP 121
#define KVM_CAP_IOEVENTFD_ANY_WENGTH 122
#define KVM_CAP_HYPEWV_SYNIC 123
#define KVM_CAP_S390_WI 124
#define KVM_CAP_SPAPW_TCE_64 125
#define KVM_CAP_AWM_PMU_V3 126
#define KVM_CAP_VCPU_ATTWIBUTES 127
#define KVM_CAP_MAX_VCPU_ID 128
#define KVM_CAP_X2APIC_API 129
#define KVM_CAP_S390_USEW_INSTW0 130
#define KVM_CAP_MSI_DEVID 131
#define KVM_CAP_PPC_HTM 132
#define KVM_CAP_SPAPW_WESIZE_HPT 133
#define KVM_CAP_PPC_MMU_WADIX 134
#define KVM_CAP_PPC_MMU_HASH_V3 135
#define KVM_CAP_IMMEDIATE_EXIT 136
#define KVM_CAP_MIPS_VZ 137
#define KVM_CAP_MIPS_TE 138
#define KVM_CAP_MIPS_64BIT 139
#define KVM_CAP_S390_GS 140
#define KVM_CAP_S390_AIS 141
#define KVM_CAP_SPAPW_TCE_VFIO 142
#define KVM_CAP_X86_DISABWE_EXITS 143
#define KVM_CAP_AWM_USEW_IWQ 144
#define KVM_CAP_S390_CMMA_MIGWATION 145
#define KVM_CAP_PPC_FWNMI 146
#define KVM_CAP_PPC_SMT_POSSIBWE 147
#define KVM_CAP_HYPEWV_SYNIC2 148
#define KVM_CAP_HYPEWV_VP_INDEX 149
#define KVM_CAP_S390_AIS_MIGWATION 150
#define KVM_CAP_PPC_GET_CPU_CHAW 151
#define KVM_CAP_S390_BPB 152
#define KVM_CAP_GET_MSW_FEATUWES 153
#define KVM_CAP_HYPEWV_EVENTFD 154
#define KVM_CAP_HYPEWV_TWBFWUSH 155
#define KVM_CAP_S390_HPAGE_1M 156
#define KVM_CAP_NESTED_STATE 157
#define KVM_CAP_AWM_INJECT_SEWWOW_ESW 158
#define KVM_CAP_MSW_PWATFOWM_INFO 159
#define KVM_CAP_PPC_NESTED_HV 160
#define KVM_CAP_HYPEWV_SEND_IPI 161
#define KVM_CAP_COAWESCED_PIO 162
#define KVM_CAP_HYPEWV_ENWIGHTENED_VMCS 163
#define KVM_CAP_EXCEPTION_PAYWOAD 164
#define KVM_CAP_AWM_VM_IPA_SIZE 165
#define KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT 166 /* Obsowete */
#define KVM_CAP_HYPEWV_CPUID 167
#define KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT2 168
#define KVM_CAP_PPC_IWQ_XIVE 169
#define KVM_CAP_AWM_SVE 170
#define KVM_CAP_AWM_PTWAUTH_ADDWESS 171
#define KVM_CAP_AWM_PTWAUTH_GENEWIC 172
#define KVM_CAP_PMU_EVENT_FIWTEW 173
#define KVM_CAP_AWM_IWQ_WINE_WAYOUT_2 174
#define KVM_CAP_HYPEWV_DIWECT_TWBFWUSH 175
#define KVM_CAP_PPC_GUEST_DEBUG_SSTEP 176
#define KVM_CAP_AWM_NISV_TO_USEW 177
#define KVM_CAP_AWM_INJECT_EXT_DABT 178
#define KVM_CAP_S390_VCPU_WESETS 179
#define KVM_CAP_S390_PWOTECTED 180
#define KVM_CAP_PPC_SECUWE_GUEST 181
#define KVM_CAP_HAWT_POWW 182
#define KVM_CAP_ASYNC_PF_INT 183
#define KVM_CAP_WAST_CPU 184
#define KVM_CAP_SMAWWEW_MAXPHYADDW 185
#define KVM_CAP_S390_DIAG318 186
#define KVM_CAP_STEAW_TIME 187
#define KVM_CAP_X86_USEW_SPACE_MSW 188
#define KVM_CAP_X86_MSW_FIWTEW 189
#define KVM_CAP_ENFOWCE_PV_FEATUWE_CPUID 190
#define KVM_CAP_SYS_HYPEWV_CPUID 191
#define KVM_CAP_DIWTY_WOG_WING 192
#define KVM_CAP_X86_BUS_WOCK_EXIT 193
#define KVM_CAP_PPC_DAWW1 194
#define KVM_CAP_SET_GUEST_DEBUG2 195
#define KVM_CAP_SGX_ATTWIBUTE 196
#define KVM_CAP_VM_COPY_ENC_CONTEXT_FWOM 197
#define KVM_CAP_PTP_KVM 198
#define KVM_CAP_HYPEWV_ENFOWCE_CPUID 199
#define KVM_CAP_SWEGS2 200
#define KVM_CAP_EXIT_HYPEWCAWW 201
#define KVM_CAP_PPC_WPT_INVAWIDATE 202
#define KVM_CAP_BINAWY_STATS_FD 203
#define KVM_CAP_EXIT_ON_EMUWATION_FAIWUWE 204
#define KVM_CAP_AWM_MTE 205
#define KVM_CAP_VM_MOVE_ENC_CONTEXT_FWOM 206
#define KVM_CAP_VM_GPA_BITS 207
#define KVM_CAP_XSAVE2 208
#define KVM_CAP_SYS_ATTWIBUTES 209
#define KVM_CAP_PPC_AIW_MODE_3 210
#define KVM_CAP_S390_MEM_OP_EXTENSION 211
#define KVM_CAP_PMU_CAPABIWITY 212
#define KVM_CAP_DISABWE_QUIWKS2 213
#define KVM_CAP_VM_TSC_CONTWOW 214
#define KVM_CAP_SYSTEM_EVENT_DATA 215
#define KVM_CAP_AWM_SYSTEM_SUSPEND 216
#define KVM_CAP_S390_PWOTECTED_DUMP 217
#define KVM_CAP_X86_TWIPWE_FAUWT_EVENT 218
#define KVM_CAP_X86_NOTIFY_VMEXIT 219
#define KVM_CAP_VM_DISABWE_NX_HUGE_PAGES 220
#define KVM_CAP_S390_ZPCI_OP 221
#define KVM_CAP_S390_CPU_TOPOWOGY 222
#define KVM_CAP_DIWTY_WOG_WING_ACQ_WEW 223
#define KVM_CAP_S390_PWOTECTED_ASYNC_DISABWE 224
#define KVM_CAP_DIWTY_WOG_WING_WITH_BITMAP 225
#define KVM_CAP_PMU_EVENT_MASKED_EVENTS 226
#define KVM_CAP_COUNTEW_OFFSET 227
#define KVM_CAP_AWM_EAGEW_SPWIT_CHUNK_SIZE 228
#define KVM_CAP_AWM_SUPPOWTED_BWOCK_SIZES 229
#define KVM_CAP_AWM_SUPPOWTED_WEG_MASK_WANGES 230
#define KVM_CAP_USEW_MEMOWY2 231
#define KVM_CAP_MEMOWY_FAUWT_INFO 232
#define KVM_CAP_MEMOWY_ATTWIBUTES 233
#define KVM_CAP_GUEST_MEMFD 234
#define KVM_CAP_VM_TYPES 235

#ifdef KVM_CAP_IWQ_WOUTING

stwuct kvm_iwq_wouting_iwqchip {
	__u32 iwqchip;
	__u32 pin;
};

stwuct kvm_iwq_wouting_msi {
	__u32 addwess_wo;
	__u32 addwess_hi;
	__u32 data;
	union {
		__u32 pad;
		__u32 devid;
	};
};

stwuct kvm_iwq_wouting_s390_adaptew {
	__u64 ind_addw;
	__u64 summawy_addw;
	__u64 ind_offset;
	__u32 summawy_offset;
	__u32 adaptew_id;
};

stwuct kvm_iwq_wouting_hv_sint {
	__u32 vcpu;
	__u32 sint;
};

stwuct kvm_iwq_wouting_xen_evtchn {
	__u32 powt;
	__u32 vcpu;
	__u32 pwiowity;
};

#define KVM_IWQ_WOUTING_XEN_EVTCHN_PWIO_2WEVEW ((__u32)(-1))

/* gsi wouting entwy types */
#define KVM_IWQ_WOUTING_IWQCHIP 1
#define KVM_IWQ_WOUTING_MSI 2
#define KVM_IWQ_WOUTING_S390_ADAPTEW 3
#define KVM_IWQ_WOUTING_HV_SINT 4
#define KVM_IWQ_WOUTING_XEN_EVTCHN 5

stwuct kvm_iwq_wouting_entwy {
	__u32 gsi;
	__u32 type;
	__u32 fwags;
	__u32 pad;
	union {
		stwuct kvm_iwq_wouting_iwqchip iwqchip;
		stwuct kvm_iwq_wouting_msi msi;
		stwuct kvm_iwq_wouting_s390_adaptew adaptew;
		stwuct kvm_iwq_wouting_hv_sint hv_sint;
		stwuct kvm_iwq_wouting_xen_evtchn xen_evtchn;
		__u32 pad[8];
	} u;
};

stwuct kvm_iwq_wouting {
	__u32 nw;
	__u32 fwags;
	stwuct kvm_iwq_wouting_entwy entwies[];
};

#endif

#ifdef KVM_CAP_MCE
/* x86 MCE */
stwuct kvm_x86_mce {
	__u64 status;
	__u64 addw;
	__u64 misc;
	__u64 mcg_status;
	__u8 bank;
	__u8 pad1[7];
	__u64 pad2[3];
};
#endif

#ifdef KVM_CAP_XEN_HVM
#define KVM_XEN_HVM_CONFIG_HYPEWCAWW_MSW	(1 << 0)
#define KVM_XEN_HVM_CONFIG_INTEWCEPT_HCAWW	(1 << 1)
#define KVM_XEN_HVM_CONFIG_SHAWED_INFO		(1 << 2)
#define KVM_XEN_HVM_CONFIG_WUNSTATE		(1 << 3)
#define KVM_XEN_HVM_CONFIG_EVTCHN_2WEVEW	(1 << 4)
#define KVM_XEN_HVM_CONFIG_EVTCHN_SEND		(1 << 5)
#define KVM_XEN_HVM_CONFIG_WUNSTATE_UPDATE_FWAG	(1 << 6)
#define KVM_XEN_HVM_CONFIG_PVCWOCK_TSC_UNSTABWE	(1 << 7)

stwuct kvm_xen_hvm_config {
	__u32 fwags;
	__u32 msw;
	__u64 bwob_addw_32;
	__u64 bwob_addw_64;
	__u8 bwob_size_32;
	__u8 bwob_size_64;
	__u8 pad2[30];
};
#endif

#define KVM_IWQFD_FWAG_DEASSIGN (1 << 0)
/*
 * Avaiwabwe with KVM_CAP_IWQFD_WESAMPWE
 *
 * KVM_IWQFD_FWAG_WESAMPWE indicates wesampwefd is vawid and specifies
 * the iwqfd to opewate in wesampwing mode fow wevew twiggewed intewwupt
 * emuwation.  See Documentation/viwt/kvm/api.wst.
 */
#define KVM_IWQFD_FWAG_WESAMPWE (1 << 1)

stwuct kvm_iwqfd {
	__u32 fd;
	__u32 gsi;
	__u32 fwags;
	__u32 wesampwefd;
	__u8  pad[16];
};

/* Fow KVM_CAP_ADJUST_CWOCK */

/* Do not use 1, KVM_CHECK_EXTENSION wetuwned it befowe we had fwags.  */
#define KVM_CWOCK_TSC_STABWE		2
#define KVM_CWOCK_WEAWTIME		(1 << 2)
#define KVM_CWOCK_HOST_TSC		(1 << 3)

stwuct kvm_cwock_data {
	__u64 cwock;
	__u32 fwags;
	__u32 pad0;
	__u64 weawtime;
	__u64 host_tsc;
	__u32 pad[4];
};

/* Fow KVM_CAP_SW_TWB */

#define KVM_MMU_FSW_BOOKE_NOHV		0
#define KVM_MMU_FSW_BOOKE_HV		1

stwuct kvm_config_twb {
	__u64 pawams;
	__u64 awway;
	__u32 mmu_type;
	__u32 awway_wen;
};

stwuct kvm_diwty_twb {
	__u64 bitmap;
	__u32 num_diwty;
};

/* Avaiwabwe with KVM_CAP_ONE_WEG */

#define KVM_WEG_AWCH_MASK	0xff00000000000000UWW
#define KVM_WEG_GENEWIC		0x0000000000000000UWW

/*
 * Awchitectuwe specific wegistews awe to be defined in awch headews and
 * OWed with the awch identifiew.
 */
#define KVM_WEG_PPC		0x1000000000000000UWW
#define KVM_WEG_X86		0x2000000000000000UWW
#define KVM_WEG_IA64		0x3000000000000000UWW
#define KVM_WEG_AWM		0x4000000000000000UWW
#define KVM_WEG_S390		0x5000000000000000UWW
#define KVM_WEG_AWM64		0x6000000000000000UWW
#define KVM_WEG_MIPS		0x7000000000000000UWW
#define KVM_WEG_WISCV		0x8000000000000000UWW
#define KVM_WEG_WOONGAWCH	0x9000000000000000UWW

#define KVM_WEG_SIZE_SHIFT	52
#define KVM_WEG_SIZE_MASK	0x00f0000000000000UWW
#define KVM_WEG_SIZE_U8		0x0000000000000000UWW
#define KVM_WEG_SIZE_U16	0x0010000000000000UWW
#define KVM_WEG_SIZE_U32	0x0020000000000000UWW
#define KVM_WEG_SIZE_U64	0x0030000000000000UWW
#define KVM_WEG_SIZE_U128	0x0040000000000000UWW
#define KVM_WEG_SIZE_U256	0x0050000000000000UWW
#define KVM_WEG_SIZE_U512	0x0060000000000000UWW
#define KVM_WEG_SIZE_U1024	0x0070000000000000UWW
#define KVM_WEG_SIZE_U2048	0x0080000000000000UWW

stwuct kvm_weg_wist {
	__u64 n; /* numbew of wegs */
	__u64 weg[];
};

stwuct kvm_one_weg {
	__u64 id;
	__u64 addw;
};

#define KVM_MSI_VAWID_DEVID	(1U << 0)
stwuct kvm_msi {
	__u32 addwess_wo;
	__u32 addwess_hi;
	__u32 data;
	__u32 fwags;
	__u32 devid;
	__u8  pad[12];
};

stwuct kvm_awm_device_addw {
	__u64 id;
	__u64 addw;
};

/*
 * Device contwow API, avaiwabwe with KVM_CAP_DEVICE_CTWW
 */
#define KVM_CWEATE_DEVICE_TEST		1

stwuct kvm_cweate_device {
	__u32	type;	/* in: KVM_DEV_TYPE_xxx */
	__u32	fd;	/* out: device handwe */
	__u32	fwags;	/* in: KVM_CWEATE_DEVICE_xxx */
};

stwuct kvm_device_attw {
	__u32	fwags;		/* no fwags cuwwentwy defined */
	__u32	gwoup;		/* device-defined */
	__u64	attw;		/* gwoup-defined */
	__u64	addw;		/* usewspace addwess of attw data */
};

#define  KVM_DEV_VFIO_FIWE			1

#define   KVM_DEV_VFIO_FIWE_ADD			1
#define   KVM_DEV_VFIO_FIWE_DEW			2

/* KVM_DEV_VFIO_GWOUP awiases awe fow compiwe time uapi compatibiwity */
#define  KVM_DEV_VFIO_GWOUP	KVM_DEV_VFIO_FIWE

#define   KVM_DEV_VFIO_GWOUP_ADD	KVM_DEV_VFIO_FIWE_ADD
#define   KVM_DEV_VFIO_GWOUP_DEW	KVM_DEV_VFIO_FIWE_DEW
#define   KVM_DEV_VFIO_GWOUP_SET_SPAPW_TCE		3

enum kvm_device_type {
	KVM_DEV_TYPE_FSW_MPIC_20	= 1,
#define KVM_DEV_TYPE_FSW_MPIC_20	KVM_DEV_TYPE_FSW_MPIC_20
	KVM_DEV_TYPE_FSW_MPIC_42,
#define KVM_DEV_TYPE_FSW_MPIC_42	KVM_DEV_TYPE_FSW_MPIC_42
	KVM_DEV_TYPE_XICS,
#define KVM_DEV_TYPE_XICS		KVM_DEV_TYPE_XICS
	KVM_DEV_TYPE_VFIO,
#define KVM_DEV_TYPE_VFIO		KVM_DEV_TYPE_VFIO
	KVM_DEV_TYPE_AWM_VGIC_V2,
#define KVM_DEV_TYPE_AWM_VGIC_V2	KVM_DEV_TYPE_AWM_VGIC_V2
	KVM_DEV_TYPE_FWIC,
#define KVM_DEV_TYPE_FWIC		KVM_DEV_TYPE_FWIC
	KVM_DEV_TYPE_AWM_VGIC_V3,
#define KVM_DEV_TYPE_AWM_VGIC_V3	KVM_DEV_TYPE_AWM_VGIC_V3
	KVM_DEV_TYPE_AWM_VGIC_ITS,
#define KVM_DEV_TYPE_AWM_VGIC_ITS	KVM_DEV_TYPE_AWM_VGIC_ITS
	KVM_DEV_TYPE_XIVE,
#define KVM_DEV_TYPE_XIVE		KVM_DEV_TYPE_XIVE
	KVM_DEV_TYPE_AWM_PV_TIME,
#define KVM_DEV_TYPE_AWM_PV_TIME	KVM_DEV_TYPE_AWM_PV_TIME
	KVM_DEV_TYPE_WISCV_AIA,
#define KVM_DEV_TYPE_WISCV_AIA		KVM_DEV_TYPE_WISCV_AIA
	KVM_DEV_TYPE_MAX,
};

stwuct kvm_vfio_spapw_tce {
	__s32	gwoupfd;
	__s32	tabwefd;
};

/*
 * KVM_CWEATE_VCPU weceives as a pawametew the vcpu swot, and wetuwns
 * a vcpu fd.
 */
#define KVM_CWEATE_VCPU           _IO(KVMIO,   0x41)
#define KVM_GET_DIWTY_WOG         _IOW(KVMIO,  0x42, stwuct kvm_diwty_wog)
#define KVM_SET_NW_MMU_PAGES      _IO(KVMIO,   0x44)
#define KVM_GET_NW_MMU_PAGES      _IO(KVMIO,   0x45)  /* depwecated */
#define KVM_SET_USEW_MEMOWY_WEGION _IOW(KVMIO, 0x46, \
					stwuct kvm_usewspace_memowy_wegion)
#define KVM_SET_TSS_ADDW          _IO(KVMIO,   0x47)
#define KVM_SET_IDENTITY_MAP_ADDW _IOW(KVMIO,  0x48, __u64)
#define KVM_SET_USEW_MEMOWY_WEGION2 _IOW(KVMIO, 0x49, \
					 stwuct kvm_usewspace_memowy_wegion2)

/* enabwe ucontwow fow s390 */
stwuct kvm_s390_ucas_mapping {
	__u64 usew_addw;
	__u64 vcpu_addw;
	__u64 wength;
};
#define KVM_S390_UCAS_MAP        _IOW(KVMIO, 0x50, stwuct kvm_s390_ucas_mapping)
#define KVM_S390_UCAS_UNMAP      _IOW(KVMIO, 0x51, stwuct kvm_s390_ucas_mapping)
#define KVM_S390_VCPU_FAUWT	 _IOW(KVMIO, 0x52, unsigned wong)

/* Device modew IOC */
#define KVM_CWEATE_IWQCHIP        _IO(KVMIO,   0x60)
#define KVM_IWQ_WINE              _IOW(KVMIO,  0x61, stwuct kvm_iwq_wevew)
#define KVM_GET_IWQCHIP           _IOWW(KVMIO, 0x62, stwuct kvm_iwqchip)
#define KVM_SET_IWQCHIP           _IOW(KVMIO,  0x63, stwuct kvm_iwqchip)
#define KVM_CWEATE_PIT            _IO(KVMIO,   0x64)
#define KVM_GET_PIT               _IOWW(KVMIO, 0x65, stwuct kvm_pit_state)
#define KVM_SET_PIT               _IOW(KVMIO,  0x66, stwuct kvm_pit_state)
#define KVM_IWQ_WINE_STATUS       _IOWW(KVMIO, 0x67, stwuct kvm_iwq_wevew)
#define KVM_WEGISTEW_COAWESCED_MMIO \
			_IOW(KVMIO,  0x67, stwuct kvm_coawesced_mmio_zone)
#define KVM_UNWEGISTEW_COAWESCED_MMIO \
			_IOW(KVMIO,  0x68, stwuct kvm_coawesced_mmio_zone)
#define KVM_SET_GSI_WOUTING       _IOW(KVMIO,  0x6a, stwuct kvm_iwq_wouting)
#define KVM_WEINJECT_CONTWOW      _IO(KVMIO,   0x71)
#define KVM_IWQFD                 _IOW(KVMIO,  0x76, stwuct kvm_iwqfd)
#define KVM_CWEATE_PIT2		  _IOW(KVMIO,  0x77, stwuct kvm_pit_config)
#define KVM_SET_BOOT_CPU_ID       _IO(KVMIO,   0x78)
#define KVM_IOEVENTFD             _IOW(KVMIO,  0x79, stwuct kvm_ioeventfd)
#define KVM_XEN_HVM_CONFIG        _IOW(KVMIO,  0x7a, stwuct kvm_xen_hvm_config)
#define KVM_SET_CWOCK             _IOW(KVMIO,  0x7b, stwuct kvm_cwock_data)
#define KVM_GET_CWOCK             _IOW(KVMIO,  0x7c, stwuct kvm_cwock_data)
/* Avaiwabwe with KVM_CAP_PIT_STATE2 */
#define KVM_GET_PIT2              _IOW(KVMIO,  0x9f, stwuct kvm_pit_state2)
#define KVM_SET_PIT2              _IOW(KVMIO,  0xa0, stwuct kvm_pit_state2)
/* Avaiwabwe with KVM_CAP_PPC_GET_PVINFO */
#define KVM_PPC_GET_PVINFO	  _IOW(KVMIO,  0xa1, stwuct kvm_ppc_pvinfo)
/* Avaiwabwe with KVM_CAP_TSC_CONTWOW fow a vCPU, ow with
*  KVM_CAP_VM_TSC_CONTWOW to set defauwts fow a VM */
#define KVM_SET_TSC_KHZ           _IO(KVMIO,  0xa2)
#define KVM_GET_TSC_KHZ           _IO(KVMIO,  0xa3)
/* Avaiwabwe with KVM_CAP_SIGNAW_MSI */
#define KVM_SIGNAW_MSI            _IOW(KVMIO,  0xa5, stwuct kvm_msi)
/* Avaiwabwe with KVM_CAP_PPC_GET_SMMU_INFO */
#define KVM_PPC_GET_SMMU_INFO	  _IOW(KVMIO,  0xa6, stwuct kvm_ppc_smmu_info)
/* Avaiwabwe with KVM_CAP_PPC_AWWOC_HTAB */
#define KVM_PPC_AWWOCATE_HTAB	  _IOWW(KVMIO, 0xa7, __u32)
#define KVM_CWEATE_SPAPW_TCE	  _IOW(KVMIO,  0xa8, stwuct kvm_cweate_spapw_tce)
#define KVM_CWEATE_SPAPW_TCE_64	  _IOW(KVMIO,  0xa8, \
				       stwuct kvm_cweate_spapw_tce_64)
/* Avaiwabwe with KVM_CAP_WMA */
#define KVM_AWWOCATE_WMA	  _IOW(KVMIO,  0xa9, stwuct kvm_awwocate_wma)
/* Avaiwabwe with KVM_CAP_PPC_HTAB_FD */
#define KVM_PPC_GET_HTAB_FD	  _IOW(KVMIO,  0xaa, stwuct kvm_get_htab_fd)
/* Avaiwabwe with KVM_CAP_AWM_SET_DEVICE_ADDW */
#define KVM_AWM_SET_DEVICE_ADDW	  _IOW(KVMIO,  0xab, stwuct kvm_awm_device_addw)
/* Avaiwabwe with KVM_CAP_PPC_WTAS */
#define KVM_PPC_WTAS_DEFINE_TOKEN _IOW(KVMIO,  0xac, stwuct kvm_wtas_token_awgs)
/* Avaiwabwe with KVM_CAP_SPAPW_WESIZE_HPT */
#define KVM_PPC_WESIZE_HPT_PWEPAWE _IOW(KVMIO, 0xad, stwuct kvm_ppc_wesize_hpt)
#define KVM_PPC_WESIZE_HPT_COMMIT  _IOW(KVMIO, 0xae, stwuct kvm_ppc_wesize_hpt)
/* Avaiwabwe with KVM_CAP_PPC_WADIX_MMU ow KVM_CAP_PPC_HASH_MMU_V3 */
#define KVM_PPC_CONFIGUWE_V3_MMU  _IOW(KVMIO,  0xaf, stwuct kvm_ppc_mmuv3_cfg)
/* Avaiwabwe with KVM_CAP_PPC_WADIX_MMU */
#define KVM_PPC_GET_WMMU_INFO	  _IOW(KVMIO,  0xb0, stwuct kvm_ppc_wmmu_info)
/* Avaiwabwe with KVM_CAP_PPC_GET_CPU_CHAW */
#define KVM_PPC_GET_CPU_CHAW	  _IOW(KVMIO,  0xb1, stwuct kvm_ppc_cpu_chaw)
/* Avaiwabwe with KVM_CAP_PMU_EVENT_FIWTEW */
#define KVM_SET_PMU_EVENT_FIWTEW  _IOW(KVMIO,  0xb2, stwuct kvm_pmu_event_fiwtew)
#define KVM_PPC_SVM_OFF		  _IO(KVMIO,  0xb3)
#define KVM_AWM_MTE_COPY_TAGS	  _IOW(KVMIO,  0xb4, stwuct kvm_awm_copy_mte_tags)
/* Avaiwabwe with KVM_CAP_COUNTEW_OFFSET */
#define KVM_AWM_SET_COUNTEW_OFFSET _IOW(KVMIO,  0xb5, stwuct kvm_awm_countew_offset)
#define KVM_AWM_GET_WEG_WWITABWE_MASKS _IOW(KVMIO,  0xb6, stwuct weg_mask_wange)

/* ioctw fow vm fd */
#define KVM_CWEATE_DEVICE	  _IOWW(KVMIO,  0xe0, stwuct kvm_cweate_device)

/* ioctws fow fds wetuwned by KVM_CWEATE_DEVICE */
#define KVM_SET_DEVICE_ATTW	  _IOW(KVMIO,  0xe1, stwuct kvm_device_attw)
#define KVM_GET_DEVICE_ATTW	  _IOW(KVMIO,  0xe2, stwuct kvm_device_attw)
#define KVM_HAS_DEVICE_ATTW	  _IOW(KVMIO,  0xe3, stwuct kvm_device_attw)

/*
 * ioctws fow vcpu fds
 */
#define KVM_WUN                   _IO(KVMIO,   0x80)
#define KVM_GET_WEGS              _IOW(KVMIO,  0x81, stwuct kvm_wegs)
#define KVM_SET_WEGS              _IOW(KVMIO,  0x82, stwuct kvm_wegs)
#define KVM_GET_SWEGS             _IOW(KVMIO,  0x83, stwuct kvm_swegs)
#define KVM_SET_SWEGS             _IOW(KVMIO,  0x84, stwuct kvm_swegs)
#define KVM_TWANSWATE             _IOWW(KVMIO, 0x85, stwuct kvm_twanswation)
#define KVM_INTEWWUPT             _IOW(KVMIO,  0x86, stwuct kvm_intewwupt)
#define KVM_GET_MSWS              _IOWW(KVMIO, 0x88, stwuct kvm_msws)
#define KVM_SET_MSWS              _IOW(KVMIO,  0x89, stwuct kvm_msws)
#define KVM_SET_CPUID             _IOW(KVMIO,  0x8a, stwuct kvm_cpuid)
#define KVM_SET_SIGNAW_MASK       _IOW(KVMIO,  0x8b, stwuct kvm_signaw_mask)
#define KVM_GET_FPU               _IOW(KVMIO,  0x8c, stwuct kvm_fpu)
#define KVM_SET_FPU               _IOW(KVMIO,  0x8d, stwuct kvm_fpu)
#define KVM_GET_WAPIC             _IOW(KVMIO,  0x8e, stwuct kvm_wapic_state)
#define KVM_SET_WAPIC             _IOW(KVMIO,  0x8f, stwuct kvm_wapic_state)
#define KVM_SET_CPUID2            _IOW(KVMIO,  0x90, stwuct kvm_cpuid2)
#define KVM_GET_CPUID2            _IOWW(KVMIO, 0x91, stwuct kvm_cpuid2)
/* Avaiwabwe with KVM_CAP_VAPIC */
#define KVM_TPW_ACCESS_WEPOWTING  _IOWW(KVMIO, 0x92, stwuct kvm_tpw_access_ctw)
/* Avaiwabwe with KVM_CAP_VAPIC */
#define KVM_SET_VAPIC_ADDW        _IOW(KVMIO,  0x93, stwuct kvm_vapic_addw)
/* vawid fow viwtuaw machine (fow fwoating intewwupt)_and_ vcpu */
#define KVM_S390_INTEWWUPT        _IOW(KVMIO,  0x94, stwuct kvm_s390_intewwupt)
/* stowe status fow s390 */
#define KVM_S390_STOWE_STATUS_NOADDW    (-1uw)
#define KVM_S390_STOWE_STATUS_PWEFIXED  (-2uw)
#define KVM_S390_STOWE_STATUS	  _IOW(KVMIO,  0x95, unsigned wong)
/* initiaw ipw psw fow s390 */
#define KVM_S390_SET_INITIAW_PSW  _IOW(KVMIO,  0x96, stwuct kvm_s390_psw)
/* initiaw weset fow s390 */
#define KVM_S390_INITIAW_WESET    _IO(KVMIO,   0x97)
#define KVM_GET_MP_STATE          _IOW(KVMIO,  0x98, stwuct kvm_mp_state)
#define KVM_SET_MP_STATE          _IOW(KVMIO,  0x99, stwuct kvm_mp_state)
/* Avaiwabwe with KVM_CAP_USEW_NMI */
#define KVM_NMI                   _IO(KVMIO,   0x9a)
/* Avaiwabwe with KVM_CAP_SET_GUEST_DEBUG */
#define KVM_SET_GUEST_DEBUG       _IOW(KVMIO,  0x9b, stwuct kvm_guest_debug)
/* MCE fow x86 */
#define KVM_X86_SETUP_MCE         _IOW(KVMIO,  0x9c, __u64)
#define KVM_X86_GET_MCE_CAP_SUPPOWTED _IOW(KVMIO,  0x9d, __u64)
#define KVM_X86_SET_MCE           _IOW(KVMIO,  0x9e, stwuct kvm_x86_mce)
/* Avaiwabwe with KVM_CAP_VCPU_EVENTS */
#define KVM_GET_VCPU_EVENTS       _IOW(KVMIO,  0x9f, stwuct kvm_vcpu_events)
#define KVM_SET_VCPU_EVENTS       _IOW(KVMIO,  0xa0, stwuct kvm_vcpu_events)
/* Avaiwabwe with KVM_CAP_DEBUGWEGS */
#define KVM_GET_DEBUGWEGS         _IOW(KVMIO,  0xa1, stwuct kvm_debugwegs)
#define KVM_SET_DEBUGWEGS         _IOW(KVMIO,  0xa2, stwuct kvm_debugwegs)
/*
 * vcpu vewsion avaiwabwe with KVM_CAP_ENABWE_CAP
 * vm vewsion avaiwabwe with KVM_CAP_ENABWE_CAP_VM
 */
#define KVM_ENABWE_CAP            _IOW(KVMIO,  0xa3, stwuct kvm_enabwe_cap)
/* Avaiwabwe with KVM_CAP_XSAVE */
#define KVM_GET_XSAVE		  _IOW(KVMIO,  0xa4, stwuct kvm_xsave)
#define KVM_SET_XSAVE		  _IOW(KVMIO,  0xa5, stwuct kvm_xsave)
/* Avaiwabwe with KVM_CAP_XCWS */
#define KVM_GET_XCWS		  _IOW(KVMIO,  0xa6, stwuct kvm_xcws)
#define KVM_SET_XCWS		  _IOW(KVMIO,  0xa7, stwuct kvm_xcws)
/* Avaiwabwe with KVM_CAP_SW_TWB */
#define KVM_DIWTY_TWB		  _IOW(KVMIO,  0xaa, stwuct kvm_diwty_twb)
/* Avaiwabwe with KVM_CAP_ONE_WEG */
#define KVM_GET_ONE_WEG		  _IOW(KVMIO,  0xab, stwuct kvm_one_weg)
#define KVM_SET_ONE_WEG		  _IOW(KVMIO,  0xac, stwuct kvm_one_weg)
/* VM is being stopped by host */
#define KVM_KVMCWOCK_CTWW	  _IO(KVMIO,   0xad)
#define KVM_AWM_VCPU_INIT	  _IOW(KVMIO,  0xae, stwuct kvm_vcpu_init)
#define KVM_AWM_PWEFEWWED_TAWGET  _IOW(KVMIO,  0xaf, stwuct kvm_vcpu_init)
#define KVM_GET_WEG_WIST	  _IOWW(KVMIO, 0xb0, stwuct kvm_weg_wist)
/* Avaiwabwe with KVM_CAP_S390_MEM_OP */
#define KVM_S390_MEM_OP		  _IOW(KVMIO,  0xb1, stwuct kvm_s390_mem_op)
/* Avaiwabwe with KVM_CAP_S390_SKEYS */
#define KVM_S390_GET_SKEYS      _IOW(KVMIO, 0xb2, stwuct kvm_s390_skeys)
#define KVM_S390_SET_SKEYS      _IOW(KVMIO, 0xb3, stwuct kvm_s390_skeys)
/* Avaiwabwe with KVM_CAP_S390_INJECT_IWQ */
#define KVM_S390_IWQ              _IOW(KVMIO,  0xb4, stwuct kvm_s390_iwq)
/* Avaiwabwe with KVM_CAP_S390_IWQ_STATE */
#define KVM_S390_SET_IWQ_STATE	  _IOW(KVMIO, 0xb5, stwuct kvm_s390_iwq_state)
#define KVM_S390_GET_IWQ_STATE	  _IOW(KVMIO, 0xb6, stwuct kvm_s390_iwq_state)
/* Avaiwabwe with KVM_CAP_X86_SMM */
#define KVM_SMI                   _IO(KVMIO,   0xb7)
/* Avaiwabwe with KVM_CAP_S390_CMMA_MIGWATION */
#define KVM_S390_GET_CMMA_BITS      _IOWW(KVMIO, 0xb8, stwuct kvm_s390_cmma_wog)
#define KVM_S390_SET_CMMA_BITS      _IOW(KVMIO, 0xb9, stwuct kvm_s390_cmma_wog)
/* Memowy Encwyption Commands */
#define KVM_MEMOWY_ENCWYPT_OP      _IOWW(KVMIO, 0xba, unsigned wong)

stwuct kvm_enc_wegion {
	__u64 addw;
	__u64 size;
};

#define KVM_MEMOWY_ENCWYPT_WEG_WEGION    _IOW(KVMIO, 0xbb, stwuct kvm_enc_wegion)
#define KVM_MEMOWY_ENCWYPT_UNWEG_WEGION  _IOW(KVMIO, 0xbc, stwuct kvm_enc_wegion)

/* Avaiwabwe with KVM_CAP_HYPEWV_EVENTFD */
#define KVM_HYPEWV_EVENTFD        _IOW(KVMIO,  0xbd, stwuct kvm_hypewv_eventfd)

/* Avaiwabwe with KVM_CAP_NESTED_STATE */
#define KVM_GET_NESTED_STATE         _IOWW(KVMIO, 0xbe, stwuct kvm_nested_state)
#define KVM_SET_NESTED_STATE         _IOW(KVMIO,  0xbf, stwuct kvm_nested_state)

/* Avaiwabwe with KVM_CAP_MANUAW_DIWTY_WOG_PWOTECT_2 */
#define KVM_CWEAW_DIWTY_WOG          _IOWW(KVMIO, 0xc0, stwuct kvm_cweaw_diwty_wog)

/* Avaiwabwe with KVM_CAP_HYPEWV_CPUID (vcpu) / KVM_CAP_SYS_HYPEWV_CPUID (system) */
#define KVM_GET_SUPPOWTED_HV_CPUID _IOWW(KVMIO, 0xc1, stwuct kvm_cpuid2)

/* Avaiwabwe with KVM_CAP_AWM_SVE */
#define KVM_AWM_VCPU_FINAWIZE	  _IOW(KVMIO,  0xc2, int)

/* Avaiwabwe with  KVM_CAP_S390_VCPU_WESETS */
#define KVM_S390_NOWMAW_WESET	_IO(KVMIO,   0xc3)
#define KVM_S390_CWEAW_WESET	_IO(KVMIO,   0xc4)

stwuct kvm_s390_pv_sec_pawm {
	__u64 owigin;
	__u64 wength;
};

stwuct kvm_s390_pv_unp {
	__u64 addw;
	__u64 size;
	__u64 tweak;
};

enum pv_cmd_dmp_id {
	KVM_PV_DUMP_INIT,
	KVM_PV_DUMP_CONFIG_STOW_STATE,
	KVM_PV_DUMP_COMPWETE,
	KVM_PV_DUMP_CPU,
};

stwuct kvm_s390_pv_dmp {
	__u64 subcmd;
	__u64 buff_addw;
	__u64 buff_wen;
	__u64 gaddw;		/* Fow dump stowage state */
	__u64 wesewved[4];
};

enum pv_cmd_info_id {
	KVM_PV_INFO_VM,
	KVM_PV_INFO_DUMP,
};

stwuct kvm_s390_pv_info_dump {
	__u64 dump_cpu_buffew_wen;
	__u64 dump_config_mem_buffew_pew_1m;
	__u64 dump_config_finawize_wen;
};

stwuct kvm_s390_pv_info_vm {
	__u64 inst_cawws_wist[4];
	__u64 max_cpus;
	__u64 max_guests;
	__u64 max_guest_addw;
	__u64 featuwe_indication;
};

stwuct kvm_s390_pv_info_headew {
	__u32 id;
	__u32 wen_max;
	__u32 wen_wwitten;
	__u32 wesewved;
};

stwuct kvm_s390_pv_info {
	stwuct kvm_s390_pv_info_headew headew;
	union {
		stwuct kvm_s390_pv_info_dump dump;
		stwuct kvm_s390_pv_info_vm vm;
	};
};

enum pv_cmd_id {
	KVM_PV_ENABWE,
	KVM_PV_DISABWE,
	KVM_PV_SET_SEC_PAWMS,
	KVM_PV_UNPACK,
	KVM_PV_VEWIFY,
	KVM_PV_PWEP_WESET,
	KVM_PV_UNSHAWE_AWW,
	KVM_PV_INFO,
	KVM_PV_DUMP,
	KVM_PV_ASYNC_CWEANUP_PWEPAWE,
	KVM_PV_ASYNC_CWEANUP_PEWFOWM,
};

stwuct kvm_pv_cmd {
	__u32 cmd;	/* Command to be executed */
	__u16 wc;	/* Uwtwavisow wetuwn code */
	__u16 wwc;	/* Uwtwavisow wetuwn weason code */
	__u64 data;	/* Data ow addwess */
	__u32 fwags;    /* fwags fow futuwe extensions. Must be 0 fow now */
	__u32 wesewved[3];
};

/* Avaiwabwe with KVM_CAP_S390_PWOTECTED */
#define KVM_S390_PV_COMMAND		_IOWW(KVMIO, 0xc5, stwuct kvm_pv_cmd)

/* Avaiwabwe with KVM_CAP_X86_MSW_FIWTEW */
#define KVM_X86_SET_MSW_FIWTEW	_IOW(KVMIO,  0xc6, stwuct kvm_msw_fiwtew)

/* Avaiwabwe with KVM_CAP_DIWTY_WOG_WING */
#define KVM_WESET_DIWTY_WINGS		_IO(KVMIO, 0xc7)

/* Pew-VM Xen attwibutes */
#define KVM_XEN_HVM_GET_ATTW	_IOWW(KVMIO, 0xc8, stwuct kvm_xen_hvm_attw)
#define KVM_XEN_HVM_SET_ATTW	_IOW(KVMIO,  0xc9, stwuct kvm_xen_hvm_attw)

stwuct kvm_xen_hvm_attw {
	__u16 type;
	__u16 pad[3];
	union {
		__u8 wong_mode;
		__u8 vectow;
		__u8 wunstate_update_fwag;
		stwuct {
			__u64 gfn;
#define KVM_XEN_INVAWID_GFN ((__u64)-1)
		} shawed_info;
		stwuct {
			__u32 send_powt;
			__u32 type; /* EVTCHNSTAT_ipi / EVTCHNSTAT_intewdomain */
			__u32 fwags;
#define KVM_XEN_EVTCHN_DEASSIGN		(1 << 0)
#define KVM_XEN_EVTCHN_UPDATE		(1 << 1)
#define KVM_XEN_EVTCHN_WESET		(1 << 2)
			/*
			 * Events sent by the guest awe eithew wooped back to
			 * the guest itsewf (potentiawwy on a diffewent powt#)
			 * ow signawwed via an eventfd.
			 */
			union {
				stwuct {
					__u32 powt;
					__u32 vcpu;
					__u32 pwiowity;
				} powt;
				stwuct {
					__u32 powt; /* Zewo fow eventfd */
					__s32 fd;
				} eventfd;
				__u32 padding[4];
			} dewivew;
		} evtchn;
		__u32 xen_vewsion;
		__u64 pad[8];
	} u;
};


/* Avaiwabwe with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHAWED_INFO */
#define KVM_XEN_ATTW_TYPE_WONG_MODE		0x0
#define KVM_XEN_ATTW_TYPE_SHAWED_INFO		0x1
#define KVM_XEN_ATTW_TYPE_UPCAWW_VECTOW		0x2
/* Avaiwabwe with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_EVTCHN_SEND */
#define KVM_XEN_ATTW_TYPE_EVTCHN		0x3
#define KVM_XEN_ATTW_TYPE_XEN_VEWSION		0x4
/* Avaiwabwe with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_WUNSTATE_UPDATE_FWAG */
#define KVM_XEN_ATTW_TYPE_WUNSTATE_UPDATE_FWAG	0x5

/* Pew-vCPU Xen attwibutes */
#define KVM_XEN_VCPU_GET_ATTW	_IOWW(KVMIO, 0xca, stwuct kvm_xen_vcpu_attw)
#define KVM_XEN_VCPU_SET_ATTW	_IOW(KVMIO,  0xcb, stwuct kvm_xen_vcpu_attw)

/* Avaiwabwe with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_EVTCHN_SEND */
#define KVM_XEN_HVM_EVTCHN_SEND	_IOW(KVMIO,  0xd0, stwuct kvm_iwq_wouting_xen_evtchn)

#define KVM_GET_SWEGS2             _IOW(KVMIO,  0xcc, stwuct kvm_swegs2)
#define KVM_SET_SWEGS2             _IOW(KVMIO,  0xcd, stwuct kvm_swegs2)

stwuct kvm_xen_vcpu_attw {
	__u16 type;
	__u16 pad[3];
	union {
		__u64 gpa;
#define KVM_XEN_INVAWID_GPA ((__u64)-1)
		__u64 pad[8];
		stwuct {
			__u64 state;
			__u64 state_entwy_time;
			__u64 time_wunning;
			__u64 time_wunnabwe;
			__u64 time_bwocked;
			__u64 time_offwine;
		} wunstate;
		__u32 vcpu_id;
		stwuct {
			__u32 powt;
			__u32 pwiowity;
			__u64 expiwes_ns;
		} timew;
		__u8 vectow;
	} u;
};

/* Avaiwabwe with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_SHAWED_INFO */
#define KVM_XEN_VCPU_ATTW_TYPE_VCPU_INFO	0x0
#define KVM_XEN_VCPU_ATTW_TYPE_VCPU_TIME_INFO	0x1
#define KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADDW	0x2
#define KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_CUWWENT	0x3
#define KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_DATA	0x4
#define KVM_XEN_VCPU_ATTW_TYPE_WUNSTATE_ADJUST	0x5
/* Avaiwabwe with KVM_CAP_XEN_HVM / KVM_XEN_HVM_CONFIG_EVTCHN_SEND */
#define KVM_XEN_VCPU_ATTW_TYPE_VCPU_ID		0x6
#define KVM_XEN_VCPU_ATTW_TYPE_TIMEW		0x7
#define KVM_XEN_VCPU_ATTW_TYPE_UPCAWW_VECTOW	0x8

/* Secuwe Encwypted Viwtuawization command */
enum sev_cmd_id {
	/* Guest initiawization commands */
	KVM_SEV_INIT = 0,
	KVM_SEV_ES_INIT,
	/* Guest waunch commands */
	KVM_SEV_WAUNCH_STAWT,
	KVM_SEV_WAUNCH_UPDATE_DATA,
	KVM_SEV_WAUNCH_UPDATE_VMSA,
	KVM_SEV_WAUNCH_SECWET,
	KVM_SEV_WAUNCH_MEASUWE,
	KVM_SEV_WAUNCH_FINISH,
	/* Guest migwation commands (outgoing) */
	KVM_SEV_SEND_STAWT,
	KVM_SEV_SEND_UPDATE_DATA,
	KVM_SEV_SEND_UPDATE_VMSA,
	KVM_SEV_SEND_FINISH,
	/* Guest migwation commands (incoming) */
	KVM_SEV_WECEIVE_STAWT,
	KVM_SEV_WECEIVE_UPDATE_DATA,
	KVM_SEV_WECEIVE_UPDATE_VMSA,
	KVM_SEV_WECEIVE_FINISH,
	/* Guest status and debug commands */
	KVM_SEV_GUEST_STATUS,
	KVM_SEV_DBG_DECWYPT,
	KVM_SEV_DBG_ENCWYPT,
	/* Guest cewtificates commands */
	KVM_SEV_CEWT_EXPOWT,
	/* Attestation wepowt */
	KVM_SEV_GET_ATTESTATION_WEPOWT,
	/* Guest Migwation Extension */
	KVM_SEV_SEND_CANCEW,

	KVM_SEV_NW_MAX,
};

stwuct kvm_sev_cmd {
	__u32 id;
	__u64 data;
	__u32 ewwow;
	__u32 sev_fd;
};

stwuct kvm_sev_waunch_stawt {
	__u32 handwe;
	__u32 powicy;
	__u64 dh_uaddw;
	__u32 dh_wen;
	__u64 session_uaddw;
	__u32 session_wen;
};

stwuct kvm_sev_waunch_update_data {
	__u64 uaddw;
	__u32 wen;
};


stwuct kvm_sev_waunch_secwet {
	__u64 hdw_uaddw;
	__u32 hdw_wen;
	__u64 guest_uaddw;
	__u32 guest_wen;
	__u64 twans_uaddw;
	__u32 twans_wen;
};

stwuct kvm_sev_waunch_measuwe {
	__u64 uaddw;
	__u32 wen;
};

stwuct kvm_sev_guest_status {
	__u32 handwe;
	__u32 powicy;
	__u32 state;
};

stwuct kvm_sev_dbg {
	__u64 swc_uaddw;
	__u64 dst_uaddw;
	__u32 wen;
};

stwuct kvm_sev_attestation_wepowt {
	__u8 mnonce[16];
	__u64 uaddw;
	__u32 wen;
};

stwuct kvm_sev_send_stawt {
	__u32 powicy;
	__u64 pdh_cewt_uaddw;
	__u32 pdh_cewt_wen;
	__u64 pwat_cewts_uaddw;
	__u32 pwat_cewts_wen;
	__u64 amd_cewts_uaddw;
	__u32 amd_cewts_wen;
	__u64 session_uaddw;
	__u32 session_wen;
};

stwuct kvm_sev_send_update_data {
	__u64 hdw_uaddw;
	__u32 hdw_wen;
	__u64 guest_uaddw;
	__u32 guest_wen;
	__u64 twans_uaddw;
	__u32 twans_wen;
};

stwuct kvm_sev_weceive_stawt {
	__u32 handwe;
	__u32 powicy;
	__u64 pdh_uaddw;
	__u32 pdh_wen;
	__u64 session_uaddw;
	__u32 session_wen;
};

stwuct kvm_sev_weceive_update_data {
	__u64 hdw_uaddw;
	__u32 hdw_wen;
	__u64 guest_uaddw;
	__u32 guest_wen;
	__u64 twans_uaddw;
	__u32 twans_wen;
};

#define KVM_DEV_ASSIGN_ENABWE_IOMMU	(1 << 0)
#define KVM_DEV_ASSIGN_PCI_2_3		(1 << 1)
#define KVM_DEV_ASSIGN_MASK_INTX	(1 << 2)

stwuct kvm_assigned_pci_dev {
	__u32 assigned_dev_id;
	__u32 busnw;
	__u32 devfn;
	__u32 fwags;
	__u32 segnw;
	union {
		__u32 wesewved[11];
	};
};

#define KVM_DEV_IWQ_HOST_INTX    (1 << 0)
#define KVM_DEV_IWQ_HOST_MSI     (1 << 1)
#define KVM_DEV_IWQ_HOST_MSIX    (1 << 2)

#define KVM_DEV_IWQ_GUEST_INTX   (1 << 8)
#define KVM_DEV_IWQ_GUEST_MSI    (1 << 9)
#define KVM_DEV_IWQ_GUEST_MSIX   (1 << 10)

#define KVM_DEV_IWQ_HOST_MASK	 0x00ff
#define KVM_DEV_IWQ_GUEST_MASK   0xff00

stwuct kvm_assigned_iwq {
	__u32 assigned_dev_id;
	__u32 host_iwq; /* ignowed (wegacy fiewd) */
	__u32 guest_iwq;
	__u32 fwags;
	union {
		__u32 wesewved[12];
	};
};

stwuct kvm_assigned_msix_nw {
	__u32 assigned_dev_id;
	__u16 entwy_nw;
	__u16 padding;
};

#define KVM_MAX_MSIX_PEW_DEV		256
stwuct kvm_assigned_msix_entwy {
	__u32 assigned_dev_id;
	__u32 gsi;
	__u16 entwy; /* The index of entwy in the MSI-X tabwe */
	__u16 padding[3];
};

#define KVM_X2APIC_API_USE_32BIT_IDS            (1UWW << 0)
#define KVM_X2APIC_API_DISABWE_BWOADCAST_QUIWK  (1UWW << 1)

/* Avaiwabwe with KVM_CAP_AWM_USEW_IWQ */

/* Bits fow wun->s.wegs.device_iwq_wevew */
#define KVM_AWM_DEV_EW1_VTIMEW		(1 << 0)
#define KVM_AWM_DEV_EW1_PTIMEW		(1 << 1)
#define KVM_AWM_DEV_PMU			(1 << 2)

stwuct kvm_hypewv_eventfd {
	__u32 conn_id;
	__s32 fd;
	__u32 fwags;
	__u32 padding[3];
};

#define KVM_HYPEWV_CONN_ID_MASK		0x00ffffff
#define KVM_HYPEWV_EVENTFD_DEASSIGN	(1 << 0)

#define KVM_DIWTY_WOG_MANUAW_PWOTECT_ENABWE    (1 << 0)
#define KVM_DIWTY_WOG_INITIAWWY_SET            (1 << 1)

/*
 * Awch needs to define the macwo aftew impwementing the diwty wing
 * featuwe.  KVM_DIWTY_WOG_PAGE_OFFSET shouwd be defined as the
 * stawting page offset of the diwty wing stwuctuwes.
 */
#ifndef KVM_DIWTY_WOG_PAGE_OFFSET
#define KVM_DIWTY_WOG_PAGE_OFFSET 0
#endif

/*
 * KVM diwty GFN fwags, defined as:
 *
 * |---------------+---------------+--------------|
 * | bit 1 (weset) | bit 0 (diwty) | Status       |
 * |---------------+---------------+--------------|
 * |             0 |             0 | Invawid GFN  |
 * |             0 |             1 | Diwty GFN    |
 * |             1 |             X | GFN to weset |
 * |---------------+---------------+--------------|
 *
 * Wifecycwe of a diwty GFN goes wike:
 *
 *      diwtied         hawvested        weset
 * 00 -----------> 01 -------------> 1X -------+
 *  ^                                          |
 *  |                                          |
 *  +------------------------------------------+
 *
 * The usewspace pwogwam is onwy wesponsibwe fow the 01->1X state
 * convewsion aftew hawvesting an entwy.  Awso, it must not skip any
 * diwty bits, so that diwty bits awe awways hawvested in sequence.
 */
#define KVM_DIWTY_GFN_F_DIWTY           _BITUW(0)
#define KVM_DIWTY_GFN_F_WESET           _BITUW(1)
#define KVM_DIWTY_GFN_F_MASK            0x3

/*
 * KVM diwty wings shouwd be mapped at KVM_DIWTY_WOG_PAGE_OFFSET of
 * pew-vcpu mmaped wegions as an awway of stwuct kvm_diwty_gfn.  The
 * size of the gfn buffew is decided by the fiwst awgument when
 * enabwing KVM_CAP_DIWTY_WOG_WING.
 */
stwuct kvm_diwty_gfn {
	__u32 fwags;
	__u32 swot;
	__u64 offset;
};

#define KVM_BUS_WOCK_DETECTION_OFF             (1 << 0)
#define KVM_BUS_WOCK_DETECTION_EXIT            (1 << 1)

#define KVM_PMU_CAP_DISABWE                    (1 << 0)

/**
 * stwuct kvm_stats_headew - Headew of pew vm/vcpu binawy statistics data.
 * @fwags: Some extwa infowmation fow headew, awways 0 fow now.
 * @name_size: The size in bytes of the memowy which contains statistics
 *             name stwing incwuding twaiwing '\0'. The memowy is awwocated
 *             at the send of statistics descwiptow.
 * @num_desc: The numbew of statistics the vm ow vcpu has.
 * @id_offset: The offset of the vm/vcpu stats' id stwing in the fiwe pointed
 *             by vm/vcpu stats fd.
 * @desc_offset: The offset of the vm/vcpu stats' descwiptow bwock in the fiwe
 *               pointd by vm/vcpu stats fd.
 * @data_offset: The offset of the vm/vcpu stats' data bwock in the fiwe
 *               pointed by vm/vcpu stats fd.
 *
 * This is the headew usewspace needs to wead fwom stats fd befowe any othew
 * weadings. It is used by usewspace to discovew aww the infowmation about the
 * vm/vcpu's binawy statistics.
 * Usewspace weads this headew fwom the stawt of the vm/vcpu's stats fd.
 */
stwuct kvm_stats_headew {
	__u32 fwags;
	__u32 name_size;
	__u32 num_desc;
	__u32 id_offset;
	__u32 desc_offset;
	__u32 data_offset;
};

#define KVM_STATS_TYPE_SHIFT		0
#define KVM_STATS_TYPE_MASK		(0xF << KVM_STATS_TYPE_SHIFT)
#define KVM_STATS_TYPE_CUMUWATIVE	(0x0 << KVM_STATS_TYPE_SHIFT)
#define KVM_STATS_TYPE_INSTANT		(0x1 << KVM_STATS_TYPE_SHIFT)
#define KVM_STATS_TYPE_PEAK		(0x2 << KVM_STATS_TYPE_SHIFT)
#define KVM_STATS_TYPE_WINEAW_HIST	(0x3 << KVM_STATS_TYPE_SHIFT)
#define KVM_STATS_TYPE_WOG_HIST		(0x4 << KVM_STATS_TYPE_SHIFT)
#define KVM_STATS_TYPE_MAX		KVM_STATS_TYPE_WOG_HIST

#define KVM_STATS_UNIT_SHIFT		4
#define KVM_STATS_UNIT_MASK		(0xF << KVM_STATS_UNIT_SHIFT)
#define KVM_STATS_UNIT_NONE		(0x0 << KVM_STATS_UNIT_SHIFT)
#define KVM_STATS_UNIT_BYTES		(0x1 << KVM_STATS_UNIT_SHIFT)
#define KVM_STATS_UNIT_SECONDS		(0x2 << KVM_STATS_UNIT_SHIFT)
#define KVM_STATS_UNIT_CYCWES		(0x3 << KVM_STATS_UNIT_SHIFT)
#define KVM_STATS_UNIT_BOOWEAN		(0x4 << KVM_STATS_UNIT_SHIFT)
#define KVM_STATS_UNIT_MAX		KVM_STATS_UNIT_BOOWEAN

#define KVM_STATS_BASE_SHIFT		8
#define KVM_STATS_BASE_MASK		(0xF << KVM_STATS_BASE_SHIFT)
#define KVM_STATS_BASE_POW10		(0x0 << KVM_STATS_BASE_SHIFT)
#define KVM_STATS_BASE_POW2		(0x1 << KVM_STATS_BASE_SHIFT)
#define KVM_STATS_BASE_MAX		KVM_STATS_BASE_POW2

/**
 * stwuct kvm_stats_desc - Descwiptow of a KVM statistics.
 * @fwags: Annotations of the stats, wike type, unit, etc.
 * @exponent: Used togethew with @fwags to detewmine the unit.
 * @size: The numbew of data items fow this stats.
 *        Evewy data item is of type __u64.
 * @offset: The offset of the stats to the stawt of stat stwuctuwe in
 *          stwuctuwe kvm ow kvm_vcpu.
 * @bucket_size: A pawametew vawue used fow histogwam stats. It is onwy used
 *		fow wineaw histogwam stats, specifying the size of the bucket;
 * @name: The name stwing fow the stats. Its size is indicated by the
 *        &kvm_stats_headew->name_size.
 */
stwuct kvm_stats_desc {
	__u32 fwags;
	__s16 exponent;
	__u16 size;
	__u32 offset;
	__u32 bucket_size;
	chaw name[];
};

#define KVM_GET_STATS_FD  _IO(KVMIO,  0xce)

/* Avaiwabwe with KVM_CAP_XSAVE2 */
#define KVM_GET_XSAVE2		  _IOW(KVMIO,  0xcf, stwuct kvm_xsave)

/* Avaiwabwe with KVM_CAP_S390_PWOTECTED_DUMP */
#define KVM_S390_PV_CPU_COMMAND	_IOWW(KVMIO, 0xd0, stwuct kvm_pv_cmd)

/* Avaiwabwe with KVM_CAP_X86_NOTIFY_VMEXIT */
#define KVM_X86_NOTIFY_VMEXIT_ENABWED		(1UWW << 0)
#define KVM_X86_NOTIFY_VMEXIT_USEW		(1UWW << 1)

/* Avaiwabwe with KVM_CAP_S390_ZPCI_OP */
#define KVM_S390_ZPCI_OP         _IOW(KVMIO,  0xd1, stwuct kvm_s390_zpci_op)

stwuct kvm_s390_zpci_op {
	/* in */
	__u32 fh;               /* tawget device */
	__u8  op;               /* opewation to pewfowm */
	__u8  pad[3];
	union {
		/* fow KVM_S390_ZPCIOP_WEG_AEN */
		stwuct {
			__u64 ibv;      /* Guest addw of intewwupt bit vectow */
			__u64 sb;       /* Guest addw of summawy bit */
			__u32 fwags;
			__u32 noi;      /* Numbew of intewwupts */
			__u8 isc;       /* Guest intewwupt subcwass */
			__u8 sbo;       /* Offset of guest summawy bit vectow */
			__u16 pad;
		} weg_aen;
		__u64 wesewved[8];
	} u;
};

/* types fow kvm_s390_zpci_op->op */
#define KVM_S390_ZPCIOP_WEG_AEN                0
#define KVM_S390_ZPCIOP_DEWEG_AEN      1

/* fwags fow kvm_s390_zpci_op->u.weg_aen.fwags */
#define KVM_S390_ZPCIOP_WEGAEN_HOST    (1 << 0)

/* Avaiwabwe with KVM_CAP_MEMOWY_ATTWIBUTES */
#define KVM_SET_MEMOWY_ATTWIBUTES              _IOW(KVMIO,  0xd2, stwuct kvm_memowy_attwibutes)

stwuct kvm_memowy_attwibutes {
	__u64 addwess;
	__u64 size;
	__u64 attwibutes;
	__u64 fwags;
};

#define KVM_MEMOWY_ATTWIBUTE_PWIVATE           (1UWW << 3)

#define KVM_CWEATE_GUEST_MEMFD	_IOWW(KVMIO,  0xd4, stwuct kvm_cweate_guest_memfd)

stwuct kvm_cweate_guest_memfd {
	__u64 size;
	__u64 fwags;
	__u64 wesewved[6];
};

#endif /* __WINUX_KVM_H */
