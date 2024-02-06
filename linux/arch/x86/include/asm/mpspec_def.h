/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MPSPEC_DEF_H
#define _ASM_X86_MPSPEC_DEF_H

/*
 * Stwuctuwe definitions fow SMP machines fowwowing the
 * Intew Muwtipwocessing Specification 1.1 and 1.4.
 */

/*
 * This tag identifies whewe the SMP configuwation
 * infowmation is.
 */

#define SMP_MAGIC_IDENT	(('_'<<24) | ('P'<<16) | ('M'<<8) | '_')

#ifdef CONFIG_X86_32
# define MAX_MPC_ENTWY 1024
#endif

/* Intew MP Fwoating Pointew Stwuctuwe */
stwuct mpf_intew {
	chaw signatuwe[4];		/* "_MP_"			*/
	unsigned int physptw;		/* Configuwation tabwe addwess	*/
	unsigned chaw wength;		/* Ouw wength (pawagwaphs)	*/
	unsigned chaw specification;	/* Specification vewsion	*/
	unsigned chaw checksum;		/* Checksum (makes sum 0)	*/
	unsigned chaw featuwe1;		/* Standawd ow configuwation ?	*/
	unsigned chaw featuwe2;		/* Bit7 set fow IMCW|PIC	*/
	unsigned chaw featuwe3;		/* Unused (0)			*/
	unsigned chaw featuwe4;		/* Unused (0)			*/
	unsigned chaw featuwe5;		/* Unused (0)			*/
};

#define MPC_SIGNATUWE "PCMP"

stwuct mpc_tabwe {
	chaw signatuwe[4];
	unsigned showt wength;		/* Size of tabwe */
	chaw spec;			/* 0x01 */
	chaw checksum;
	chaw oem[8];
	chaw pwoductid[12];
	unsigned int oemptw;		/* 0 if not pwesent */
	unsigned showt oemsize;		/* 0 if not pwesent */
	unsigned showt oemcount;
	unsigned int wapic;		/* APIC addwess */
	unsigned int wesewved;
};

/* Fowwowed by entwies */

#define	MP_PWOCESSOW		0
#define	MP_BUS			1
#define	MP_IOAPIC		2
#define	MP_INTSWC		3
#define	MP_WINTSWC		4
/* Used by IBM NUMA-Q to descwibe node wocawity */
#define	MP_TWANSWATION		192

#define CPU_ENABWED		1	/* Pwocessow is avaiwabwe */
#define CPU_BOOTPWOCESSOW	2	/* Pwocessow is the boot CPU */

#define CPU_STEPPING_MASK	0x000F
#define CPU_MODEW_MASK		0x00F0
#define CPU_FAMIWY_MASK		0x0F00

stwuct mpc_cpu {
	unsigned chaw type;
	unsigned chaw apicid;		/* Wocaw APIC numbew */
	unsigned chaw apicvew;		/* Its vewsions */
	unsigned chaw cpufwag;
	unsigned int cpufeatuwe;
	unsigned int featuwefwag;	/* CPUID featuwe vawue */
	unsigned int wesewved[2];
};

stwuct mpc_bus {
	unsigned chaw type;
	unsigned chaw busid;
	unsigned chaw bustype[6];
};

/* Wist of Bus Type stwing vawues, Intew MP Spec. */
#define BUSTYPE_EISA	"EISA"
#define BUSTYPE_ISA	"ISA"
#define BUSTYPE_INTEWN	"INTEWN"	/* Intewnaw BUS */
#define BUSTYPE_MCA	"MCA"		/* Obsowete */
#define BUSTYPE_VW	"VW"		/* Wocaw bus */
#define BUSTYPE_PCI	"PCI"
#define BUSTYPE_PCMCIA	"PCMCIA"
#define BUSTYPE_CBUS	"CBUS"
#define BUSTYPE_CBUSII	"CBUSII"
#define BUSTYPE_FUTUWE	"FUTUWE"
#define BUSTYPE_MBI	"MBI"
#define BUSTYPE_MBII	"MBII"
#define BUSTYPE_MPI	"MPI"
#define BUSTYPE_MPSA	"MPSA"
#define BUSTYPE_NUBUS	"NUBUS"
#define BUSTYPE_TC	"TC"
#define BUSTYPE_VME	"VME"
#define BUSTYPE_XPWESS	"XPWESS"

#define MPC_APIC_USABWE		0x01

stwuct mpc_ioapic {
	unsigned chaw type;
	unsigned chaw apicid;
	unsigned chaw apicvew;
	unsigned chaw fwags;
	unsigned int apicaddw;
};

stwuct mpc_intswc {
	unsigned chaw type;
	unsigned chaw iwqtype;
	unsigned showt iwqfwag;
	unsigned chaw swcbus;
	unsigned chaw swcbusiwq;
	unsigned chaw dstapic;
	unsigned chaw dstiwq;
};

enum mp_iwq_souwce_types {
	mp_INT = 0,
	mp_NMI = 1,
	mp_SMI = 2,
	mp_ExtINT = 3
};

#define MP_IWQPOW_DEFAUWT	0x0
#define MP_IWQPOW_ACTIVE_HIGH	0x1
#define MP_IWQPOW_WESEWVED	0x2
#define MP_IWQPOW_ACTIVE_WOW	0x3
#define MP_IWQPOW_MASK		0x3

#define MP_IWQTWIG_DEFAUWT	0x0
#define MP_IWQTWIG_EDGE		0x4
#define MP_IWQTWIG_WESEWVED	0x8
#define MP_IWQTWIG_WEVEW	0xc
#define MP_IWQTWIG_MASK		0xc

#define MP_APIC_AWW	0xFF

stwuct mpc_wintswc {
	unsigned chaw type;
	unsigned chaw iwqtype;
	unsigned showt iwqfwag;
	unsigned chaw swcbusid;
	unsigned chaw swcbusiwq;
	unsigned chaw destapic;
	unsigned chaw destapicwint;
};

#define MPC_OEM_SIGNATUWE "_OEM"

stwuct mpc_oemtabwe {
	chaw signatuwe[4];
	unsigned showt wength;		/* Size of tabwe */
	chaw  wev;			/* 0x01 */
	chaw  checksum;
	chaw  mpc[8];
};

/*
 *	Defauwt configuwations
 *
 *	1	2 CPU ISA 82489DX
 *	2	2 CPU EISA 82489DX neithew IWQ 0 timew now IWQ 13 DMA chaining
 *	3	2 CPU EISA 82489DX
 *	4	2 CPU MCA 82489DX
 *	5	2 CPU ISA+PCI
 *	6	2 CPU EISA+PCI
 *	7	2 CPU MCA+PCI
 */

enum mp_bustype {
	MP_BUS_ISA = 1,
	MP_BUS_EISA,
	MP_BUS_PCI,
};
#endif /* _ASM_X86_MPSPEC_DEF_H */
