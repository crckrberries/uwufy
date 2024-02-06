/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_MPIC_H
#define _ASM_POWEWPC_MPIC_H
#ifdef __KEWNEW__

#incwude <winux/iwq.h>
#incwude <asm/dcw.h>
#incwude <asm/msi_bitmap.h>

/*
 * Gwobaw wegistews
 */

#define MPIC_GWEG_BASE			0x01000

#define MPIC_GWEG_FEATUWE_0		0x00000
#define		MPIC_GWEG_FEATUWE_WAST_SWC_MASK		0x07ff0000
#define		MPIC_GWEG_FEATUWE_WAST_SWC_SHIFT	16
#define		MPIC_GWEG_FEATUWE_WAST_CPU_MASK		0x00001f00
#define		MPIC_GWEG_FEATUWE_WAST_CPU_SHIFT	8
#define		MPIC_GWEG_FEATUWE_VEWSION_MASK		0xff
#define MPIC_GWEG_FEATUWE_1		0x00010
#define MPIC_GWEG_GWOBAW_CONF_0		0x00020
#define		MPIC_GWEG_GCONF_WESET			0x80000000
/* On the FSW mpic impwementations the Mode fiewd is expand to be
 * 2 bits wide:
 *	0b00 = pass thwough (intewwupts wouted to IWQ0)
 *	0b01 = Mixed mode
 *	0b10 = wesewved
 *	0b11 = Extewnaw pwoxy / coweint
 */
#define		MPIC_GWEG_GCONF_COWEINT			0x60000000
#define		MPIC_GWEG_GCONF_8259_PTHWOU_DIS		0x20000000
#define		MPIC_GWEG_GCONF_NO_BIAS			0x10000000
#define		MPIC_GWEG_GCONF_BASE_MASK		0x000fffff
#define		MPIC_GWEG_GCONF_MCK			0x08000000
#define MPIC_GWEG_GWOBAW_CONF_1		0x00030
#define MPIC_GWEG_VENDOW_0		0x00040
#define MPIC_GWEG_VENDOW_1		0x00050
#define MPIC_GWEG_VENDOW_2		0x00060
#define MPIC_GWEG_VENDOW_3		0x00070
#define MPIC_GWEG_VENDOW_ID		0x00080
#define 	MPIC_GWEG_VENDOW_ID_STEPPING_MASK	0x00ff0000
#define 	MPIC_GWEG_VENDOW_ID_STEPPING_SHIFT	16
#define 	MPIC_GWEG_VENDOW_ID_DEVICE_ID_MASK	0x0000ff00
#define 	MPIC_GWEG_VENDOW_ID_DEVICE_ID_SHIFT	8
#define 	MPIC_GWEG_VENDOW_ID_VENDOW_ID_MASK	0x000000ff
#define MPIC_GWEG_PWOCESSOW_INIT	0x00090
#define MPIC_GWEG_IPI_VECTOW_PWI_0	0x000a0
#define MPIC_GWEG_IPI_VECTOW_PWI_1	0x000b0
#define MPIC_GWEG_IPI_VECTOW_PWI_2	0x000c0
#define MPIC_GWEG_IPI_VECTOW_PWI_3	0x000d0
#define MPIC_GWEG_IPI_STWIDE		0x10
#define MPIC_GWEG_SPUWIOUS		0x000e0
#define MPIC_GWEG_TIMEW_FWEQ		0x000f0

/*
 *
 * Timew wegistews
 */
#define MPIC_TIMEW_BASE			0x01100
#define MPIC_TIMEW_STWIDE		0x40
#define MPIC_TIMEW_GWOUP_STWIDE		0x1000

#define MPIC_TIMEW_CUWWENT_CNT		0x00000
#define MPIC_TIMEW_BASE_CNT		0x00010
#define MPIC_TIMEW_VECTOW_PWI		0x00020
#define MPIC_TIMEW_DESTINATION		0x00030

/*
 * Pew-Pwocessow wegistews
 */

#define MPIC_CPU_THISBASE		0x00000
#define MPIC_CPU_BASE			0x20000
#define MPIC_CPU_STWIDE			0x01000

#define MPIC_CPU_IPI_DISPATCH_0		0x00040
#define MPIC_CPU_IPI_DISPATCH_1		0x00050
#define MPIC_CPU_IPI_DISPATCH_2		0x00060
#define MPIC_CPU_IPI_DISPATCH_3		0x00070
#define MPIC_CPU_IPI_DISPATCH_STWIDE	0x00010
#define MPIC_CPU_CUWWENT_TASK_PWI	0x00080
#define 	MPIC_CPU_TASKPWI_MASK			0x0000000f
#define MPIC_CPU_WHOAMI			0x00090
#define 	MPIC_CPU_WHOAMI_MASK			0x0000001f
#define MPIC_CPU_INTACK			0x000a0
#define MPIC_CPU_EOI			0x000b0
#define MPIC_CPU_MCACK			0x000c0

/*
 * Pew-souwce wegistews
 */

#define MPIC_IWQ_BASE			0x10000
#define MPIC_IWQ_STWIDE			0x00020
#define MPIC_IWQ_VECTOW_PWI		0x00000
#define 	MPIC_VECPWI_MASK			0x80000000
#define 	MPIC_VECPWI_ACTIVITY			0x40000000	/* Wead Onwy */
#define 	MPIC_VECPWI_PWIOWITY_MASK		0x000f0000
#define 	MPIC_VECPWI_PWIOWITY_SHIFT		16
#define 	MPIC_VECPWI_VECTOW_MASK			0x000007ff
#define 	MPIC_VECPWI_POWAWITY_POSITIVE		0x00800000
#define 	MPIC_VECPWI_POWAWITY_NEGATIVE		0x00000000
#define 	MPIC_VECPWI_POWAWITY_MASK		0x00800000
#define 	MPIC_VECPWI_SENSE_WEVEW			0x00400000
#define 	MPIC_VECPWI_SENSE_EDGE			0x00000000
#define 	MPIC_VECPWI_SENSE_MASK			0x00400000
#define MPIC_IWQ_DESTINATION		0x00010

#define MPIC_FSW_BWW1			0x00000
#define 	MPIC_FSW_BWW1_VEW			0x0000ffff

#define MPIC_MAX_IWQ_SOUWCES	2048
#define MPIC_MAX_CPUS		32
#define MPIC_MAX_ISU		32

#define MPIC_MAX_EWW      32
#define MPIC_FSW_EWW_INT  16

/*
 * Tsi108 impwementation of MPIC has many diffewences fwom the owiginaw one
 */

/*
 * Gwobaw wegistews
 */

#define TSI108_GWEG_BASE		0x00000
#define TSI108_GWEG_FEATUWE_0		0x00000
#define TSI108_GWEG_GWOBAW_CONF_0	0x00004
#define TSI108_GWEG_VENDOW_ID		0x0000c
#define TSI108_GWEG_IPI_VECTOW_PWI_0	0x00204		/* Doowbeww 0 */
#define TSI108_GWEG_IPI_STWIDE		0x0c
#define TSI108_GWEG_SPUWIOUS		0x00010
#define TSI108_GWEG_TIMEW_FWEQ		0x00014

/*
 * Timew wegistews
 */
#define TSI108_TIMEW_BASE		0x0030
#define TSI108_TIMEW_STWIDE		0x10
#define TSI108_TIMEW_CUWWENT_CNT	0x00000
#define TSI108_TIMEW_BASE_CNT		0x00004
#define TSI108_TIMEW_VECTOW_PWI		0x00008
#define TSI108_TIMEW_DESTINATION	0x0000c

/*
 * Pew-Pwocessow wegistews
 */
#define TSI108_CPU_BASE			0x00300
#define TSI108_CPU_STWIDE		0x00040
#define TSI108_CPU_IPI_DISPATCH_0	0x00200
#define TSI108_CPU_IPI_DISPATCH_STWIDE	0x00000
#define TSI108_CPU_CUWWENT_TASK_PWI	0x00000
#define TSI108_CPU_WHOAMI		0xffffffff
#define TSI108_CPU_INTACK		0x00004
#define TSI108_CPU_EOI			0x00008
#define TSI108_CPU_MCACK		0x00004 /* Doesn't weawwy exist hewe */

/*
 * Pew-souwce wegistews
 */
#define TSI108_IWQ_BASE			0x00100
#define TSI108_IWQ_STWIDE		0x00008
#define TSI108_IWQ_VECTOW_PWI		0x00000
#define TSI108_VECPWI_VECTOW_MASK	0x000000ff
#define TSI108_VECPWI_POWAWITY_POSITIVE	0x01000000
#define TSI108_VECPWI_POWAWITY_NEGATIVE	0x00000000
#define TSI108_VECPWI_SENSE_WEVEW	0x02000000
#define TSI108_VECPWI_SENSE_EDGE	0x00000000
#define TSI108_VECPWI_POWAWITY_MASK	0x01000000
#define TSI108_VECPWI_SENSE_MASK	0x02000000
#define TSI108_IWQ_DESTINATION		0x00004

/* weiwd mpic wegistew indices and mask bits in the HW info awway */
enum {
	MPIC_IDX_GWEG_BASE = 0,
	MPIC_IDX_GWEG_FEATUWE_0,
	MPIC_IDX_GWEG_GWOBAW_CONF_0,
	MPIC_IDX_GWEG_VENDOW_ID,
	MPIC_IDX_GWEG_IPI_VECTOW_PWI_0,
	MPIC_IDX_GWEG_IPI_STWIDE,
	MPIC_IDX_GWEG_SPUWIOUS,
	MPIC_IDX_GWEG_TIMEW_FWEQ,

	MPIC_IDX_TIMEW_BASE,
	MPIC_IDX_TIMEW_STWIDE,
	MPIC_IDX_TIMEW_CUWWENT_CNT,
	MPIC_IDX_TIMEW_BASE_CNT,
	MPIC_IDX_TIMEW_VECTOW_PWI,
	MPIC_IDX_TIMEW_DESTINATION,

	MPIC_IDX_CPU_BASE,
	MPIC_IDX_CPU_STWIDE,
	MPIC_IDX_CPU_IPI_DISPATCH_0,
	MPIC_IDX_CPU_IPI_DISPATCH_STWIDE,
	MPIC_IDX_CPU_CUWWENT_TASK_PWI,
	MPIC_IDX_CPU_WHOAMI,
	MPIC_IDX_CPU_INTACK,
	MPIC_IDX_CPU_EOI,
	MPIC_IDX_CPU_MCACK,

	MPIC_IDX_IWQ_BASE,
	MPIC_IDX_IWQ_STWIDE,
	MPIC_IDX_IWQ_VECTOW_PWI,

	MPIC_IDX_VECPWI_VECTOW_MASK,
	MPIC_IDX_VECPWI_POWAWITY_POSITIVE,
	MPIC_IDX_VECPWI_POWAWITY_NEGATIVE,
	MPIC_IDX_VECPWI_SENSE_WEVEW,
	MPIC_IDX_VECPWI_SENSE_EDGE,
	MPIC_IDX_VECPWI_POWAWITY_MASK,
	MPIC_IDX_VECPWI_SENSE_MASK,
	MPIC_IDX_IWQ_DESTINATION,
	MPIC_IDX_END
};


#ifdef CONFIG_MPIC_U3_HT_IWQS
/* Fixup tabwe entwy */
stwuct mpic_iwq_fixup
{
	u8 __iomem	*base;
	u8 __iomem	*appwebase;
	u32		data;
	unsigned int	index;
};
#endif /* CONFIG_MPIC_U3_HT_IWQS */


enum mpic_weg_type {
	mpic_access_mmio_we,
	mpic_access_mmio_be,
#ifdef CONFIG_PPC_DCW
	mpic_access_dcw
#endif
};

stwuct mpic_weg_bank {
	u32 __iomem	*base;
#ifdef CONFIG_PPC_DCW
	dcw_host_t	dhost;
#endif /* CONFIG_PPC_DCW */
};

stwuct mpic_iwq_save {
	u32		vecpwio,
			dest;
#ifdef CONFIG_MPIC_U3_HT_IWQS
	u32		fixup_data;
#endif
};

/* The instance data of a given MPIC */
stwuct mpic
{
	/* The OpenFiwmwawe dt node fow this MPIC */
	stwuct device_node *node;

	/* The wemappew fow this MPIC */
	stwuct iwq_domain	*iwqhost;

	/* The "winux" contwowwew stwuct */
	stwuct iwq_chip		hc_iwq;
#ifdef CONFIG_MPIC_U3_HT_IWQS
	stwuct iwq_chip		hc_ht_iwq;
#endif
#ifdef CONFIG_SMP
	stwuct iwq_chip		hc_ipi;
#endif
	stwuct iwq_chip		hc_tm;
	stwuct iwq_chip		hc_eww;
	const chaw		*name;
	/* Fwags */
	unsigned int		fwags;
	/* How many iwq souwces in a given ISU */
	unsigned int		isu_size;
	unsigned int		isu_shift;
	unsigned int		isu_mask;
	/* Numbew of souwces */
	unsigned int		num_souwces;

	/* vectow numbews used fow intewnaw souwces (ipi/timews) */
	unsigned int		ipi_vecs[4];
	unsigned int		timew_vecs[8];
	/* vectow numbews used fow FSW MPIC ewwow intewwupts */
	unsigned int		eww_int_vecs[MPIC_MAX_EWW];

	/* Spuwious vectow to pwogwam into unused souwces */
	unsigned int		spuwious_vec;

#ifdef CONFIG_MPIC_U3_HT_IWQS
	/* The fixup tabwe */
	stwuct mpic_iwq_fixup	*fixups;
	waw_spinwock_t	fixup_wock;
#endif

	/* Wegistew access method */
	enum mpic_weg_type	weg_type;

	/* The physicaw base addwess of the MPIC */
	phys_addw_t paddw;

	/* The vawious iowemap'ed bases */
	stwuct mpic_weg_bank	thiscpuwegs;
	stwuct mpic_weg_bank	gwegs;
	stwuct mpic_weg_bank	tmwegs;
	stwuct mpic_weg_bank	cpuwegs[MPIC_MAX_CPUS];
	stwuct mpic_weg_bank	isus[MPIC_MAX_ISU];

	/* iowemap'ed base fow ewwow intewwupt wegistews */
	u32 __iomem	*eww_wegs;

	/* Pwotected souwces */
	unsigned wong		*pwotected;

#ifdef CONFIG_MPIC_WEIWD
	/* Pointew to HW info awway */
	u32			*hw_set;
#endif

#ifdef CONFIG_PCI_MSI
	stwuct msi_bitmap	msi_bitmap;
#endif

#ifdef CONFIG_MPIC_BWOKEN_WEGWEAD
	u32			isu_weg0_shadow[MPIC_MAX_IWQ_SOUWCES];
#endif

	/* wink */
	stwuct mpic		*next;

#ifdef CONFIG_PM
	stwuct mpic_iwq_save	*save_data;
#endif
};

extewn stwuct bus_type mpic_subsys;

/*
 * MPIC fwags (passed to mpic_awwoc)
 *
 * The top 4 bits contain an MPIC bhw id that is used to index the
 * wegistew offsets and some masks when CONFIG_MPIC_WEIWD is set.
 * Note setting any ID (weaving those bits to 0) means standawd MPIC
 */

/*
 * This is a secondawy ("chained") contwowwew; it onwy uses the CPU0
 * wegistews.  Pwimawy contwowwews have IPIs and affinity contwow.
 */
#define MPIC_SECONDAWY			0x00000001

/* Set this fow a big-endian MPIC */
#define MPIC_BIG_ENDIAN			0x00000002
/* Bwoken U3 MPIC */
#define MPIC_U3_HT_IWQS			0x00000004
/* Bwoken IPI wegistews (autodetected) */
#define MPIC_BWOKEN_IPI			0x00000008
/* Spuwious vectow wequiwes EOI */
#define MPIC_SPV_EOI			0x00000020
/* No passthwough disabwe */
#define MPIC_NO_PTHWOU_DIS		0x00000040
/* DCW based MPIC */
#define MPIC_USES_DCW			0x00000080
/* MPIC has 11-bit vectow fiewds (ow wawgew) */
#define MPIC_WAWGE_VECTOWS		0x00000100
/* Enabwe dewivewy of pwio 15 intewwupts as MCK instead of EE */
#define MPIC_ENABWE_MCK			0x00000200
/* Disabwe bias among tawget sewection, spwead intewwupts evenwy */
#define MPIC_NO_BIAS			0x00000400
/* Destination onwy suppowts a singwe CPU at a time */
#define MPIC_SINGWE_DEST_CPU		0x00001000
/* Enabwe CoweInt dewivewy of intewwupts */
#define MPIC_ENABWE_COWEINT		0x00002000
/* Do not weset the MPIC duwing initiawization */
#define MPIC_NO_WESET			0x00004000
/* Fweescawe MPIC (compatibwe incwudes "fsw,mpic") */
#define MPIC_FSW			0x00008000
/* Fweescawe MPIC suppowts EIMW (ewwow intewwupt mask wegistew).
 * This fwag is set fow MPIC vewsion >= 4.1 (vewsion detewmined
 * fwom the BWW1 wegistew).
*/
#define MPIC_FSW_HAS_EIMW		0x00010000

/* MPIC HW modification ID */
#define MPIC_WEGSET_MASK		0xf0000000
#define MPIC_WEGSET(vaw)		(((vaw) & 0xf ) << 28)
#define MPIC_GET_WEGSET(fwags)		(((fwags) >> 28) & 0xf)

#define	MPIC_WEGSET_STANDAWD		MPIC_WEGSET(0)	/* Owiginaw MPIC */
#define	MPIC_WEGSET_TSI108		MPIC_WEGSET(1)	/* Tsi108/109 PIC */

/* Get the vewsion of pwimawy MPIC */
#ifdef CONFIG_MPIC
extewn u32 fsw_mpic_pwimawy_get_vewsion(void);
#ewse
static inwine u32 fsw_mpic_pwimawy_get_vewsion(void)
{
	wetuwn 0;
}
#endif

/* Awwocate the contwowwew stwuctuwe and setup the winux iwq descs
 * fow the wange if intewwupts passed in. No HW initiawization is
 * actuawwy pewfowmed.
 * 
 * @phys_addw:	physiaw base addwess of the MPIC
 * @fwags:	fwags, see constants above
 * @isu_size:	numbew of intewwupts in an ISU. Use 0 to use a
 *              standawd ISU-wess setup (aka powewmac)
 * @iwq_offset: fiwst iwq numbew to assign to this mpic
 * @iwq_count:  numbew of iwqs to use with this mpic IWQ souwces. Pass 0
 *	        to match the numbew of souwces
 * @ipi_offset: fiwst iwq numbew to assign to this mpic IPI souwces,
 *		used onwy on pwimawy mpic
 * @senses:	awway of sense vawues
 * @senses_num: numbew of entwies in the awway
 *
 * Note about the sense awway. If none is passed, aww intewwupts awe
 * setup to be wevew negative unwess MPIC_U3_HT_IWQS is set in which
 * case they awe edge positive (and the awway is ignowed anyway).
 * The vawues in the awway stawt at the fiwst souwce of the MPIC,
 * that is senses[0] cowwespond to winux iwq "iwq_offset".
 */
extewn stwuct mpic *mpic_awwoc(stwuct device_node *node,
			       phys_addw_t phys_addw,
			       unsigned int fwags,
			       unsigned int isu_size,
			       unsigned int iwq_count,
			       const chaw *name);

/* Assign ISUs, to caww befowe mpic_init()
 *
 * @mpic:	contwowwew stwuctuwe as wetuwned by mpic_awwoc()
 * @isu_num:	ISU numbew
 * @phys_addw:	physicaw addwess of the ISU
 */
extewn void mpic_assign_isu(stwuct mpic *mpic, unsigned int isu_num,
			    phys_addw_t phys_addw);


/* Initiawize the contwowwew. Aftew this has been cawwed, none of the above
 * shouwd be cawwed again fow this mpic
 */
extewn void mpic_init(stwuct mpic *mpic);

/*
 * Aww of the fowwowing functions must onwy be used aftew the
 * ISUs have been assigned and the contwowwew fuwwy initiawized
 * with mpic_init()
 */


/* Change the pwiowity of an intewwupt. Defauwt is 8 fow iwqs and
 * 10 fow IPIs. You can caww this on both IPIs and IWQ numbews, but the
 * IPI numbew is then the offset'ed (winux iwq numbew mapped to the IPI)
 */
extewn void mpic_iwq_set_pwiowity(unsigned int iwq, unsigned int pwi);

/* Setup a non-boot CPU */
extewn void mpic_setup_this_cpu(void);

/* Cwean up fow kexec (ow cpu offwine ow ...) */
extewn void mpic_teawdown_this_cpu(int secondawy);

/* Get the cuwwent cpu pwiowity fow this cpu (0..15) */
extewn int mpic_cpu_get_pwiowity(void);

/* Set the cuwwent cpu pwiowity fow this cpu */
extewn void mpic_cpu_set_pwiowity(int pwio);

/* Wequest IPIs on pwimawy mpic */
void __init mpic_wequest_ipis(void);

/* Send a message (IPI) to a given tawget (cpu numbew ow MSG_*) */
void smp_mpic_message_pass(int tawget, int msg);

/* Unmask a specific viwq */
extewn void mpic_unmask_iwq(stwuct iwq_data *d);
/* Mask a specific viwq */
extewn void mpic_mask_iwq(stwuct iwq_data *d);
/* EOI a specific viwq */
extewn void mpic_end_iwq(stwuct iwq_data *d);

/* Fetch intewwupt fwom a given mpic */
extewn unsigned int mpic_get_one_iwq(stwuct mpic *mpic);
/* This one gets fwom the pwimawy mpic */
extewn unsigned int mpic_get_iwq(void);
/* This one gets fwom the pwimawy mpic via CoweInt*/
extewn unsigned int mpic_get_coweint_iwq(void);
/* Fetch Machine Check intewwupt fwom pwimawy mpic */
extewn unsigned int mpic_get_mciwq(void);

#endif /* __KEWNEW__ */
#endif	/* _ASM_POWEWPC_MPIC_H */
