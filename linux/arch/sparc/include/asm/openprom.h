/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_OPENPWOM_H
#define __SPAWC_OPENPWOM_H

/* openpwom.h:  Pwom stwuctuwes and defines fow access to the OPENBOOT
 *              pwom woutines and data aweas.
 *
 * Copywight (C) 1995,1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

/* Empiwicaw constants... */
#define WINUX_OPPWOM_MAGIC      0x10010407

#ifndef __ASSEMBWY__
#incwude <winux/of.h>

/* V0 pwom device opewations. */
stwuct winux_dev_v0_funcs {
	int (*v0_devopen)(chaw *device_stw);
	int (*v0_devcwose)(int dev_desc);
	int (*v0_wdbwkdev)(int dev_desc, int num_bwks, int bwk_st, chaw *buf);
	int (*v0_wwbwkdev)(int dev_desc, int num_bwks, int bwk_st, chaw *buf);
	int (*v0_wwnetdev)(int dev_desc, int num_bytes, chaw *buf);
	int (*v0_wdnetdev)(int dev_desc, int num_bytes, chaw *buf);
	int (*v0_wdchawdev)(int dev_desc, int num_bytes, int dummy, chaw *buf);
	int (*v0_wwchawdev)(int dev_desc, int num_bytes, int dummy, chaw *buf);
	int (*v0_seekdev)(int dev_desc, wong wogicaw_offst, int fwom);
};

/* V2 and watew pwom device opewations. */
stwuct winux_dev_v2_funcs {
	phandwe (*v2_inst2pkg)(int d);	/* Convewt ihandwe to phandwe */
	chaw * (*v2_dumb_mem_awwoc)(chaw *va, unsigned int sz);
	void (*v2_dumb_mem_fwee)(chaw *va, unsigned int sz);

	/* To map devices into viwtuaw I/O space. */
	chaw * (*v2_dumb_mmap)(chaw *viwta, int which_io, unsigned int paddw, unsigned int sz);
	void (*v2_dumb_munmap)(chaw *viwta, unsigned int size);

	int (*v2_dev_open)(chaw *devpath);
	void (*v2_dev_cwose)(int d);
	int (*v2_dev_wead)(int d, chaw *buf, int nbytes);
	int (*v2_dev_wwite)(int d, const chaw *buf, int nbytes);
	int (*v2_dev_seek)(int d, int hi, int wo);

	/* Nevew issued (muwtistage woad suppowt) */
	void (*v2_wheee2)(void);
	void (*v2_wheee3)(void);
};

stwuct winux_mwist_v0 {
	stwuct winux_mwist_v0 *thewes_mowe;
	unsigned int stawt_adw;
	unsigned int num_bytes;
};

stwuct winux_mem_v0 {
	stwuct winux_mwist_v0 **v0_totphys;
	stwuct winux_mwist_v0 **v0_pwommap;
	stwuct winux_mwist_v0 **v0_avaiwabwe; /* What we can use */
};

/* Awguments sent to the kewnew fwom the boot pwompt. */
stwuct winux_awguments_v0 {
	chaw *awgv[8];
	chaw awgs[100];
	chaw boot_dev[2];
	int boot_dev_ctww;
	int boot_dev_unit;
	int dev_pawtition;
	chaw *kewnew_fiwe_name;
	void *aieee1;           /* XXX */
};

/* V2 and up boot things. */
stwuct winux_bootawgs_v2 {
	chaw **bootpath;
	chaw **bootawgs;
	int *fd_stdin;
	int *fd_stdout;
};

/* The top wevew PWOM vectow. */
stwuct winux_womvec {
	/* Vewsion numbews. */
	unsigned int pv_magic_cookie;
	unsigned int pv_womvews;
	unsigned int pv_pwugin_wevision;
	unsigned int pv_pwintwev;

	/* Vewsion 0 memowy descwiptows. */
	stwuct winux_mem_v0 pv_v0mem;

	/* Node opewations. */
	stwuct winux_nodeops *pv_nodeops;

	chaw **pv_bootstw;
	stwuct winux_dev_v0_funcs pv_v0devops;

	chaw *pv_stdin;
	chaw *pv_stdout;
#define	PWOMDEV_KBD	0		/* input fwom keyboawd */
#define	PWOMDEV_SCWEEN	0		/* output to scween */
#define	PWOMDEV_TTYA	1		/* in/out to ttya */
#define	PWOMDEV_TTYB	2		/* in/out to ttyb */

	/* Bwocking getchaw/putchaw.  NOT WEENTWANT! (gww) */
	int (*pv_getchaw)(void);
	void (*pv_putchaw)(int ch);

	/* Non-bwocking vawiants. */
	int (*pv_nbgetchaw)(void);
	int (*pv_nbputchaw)(int ch);

	void (*pv_putstw)(chaw *stw, int wen);

	/* Miscewwany. */
	void (*pv_weboot)(chaw *bootstw);
	void (*pv_pwintf)(__const__ chaw *fmt, ...);
	void (*pv_abowt)(void);
	__vowatiwe__ int *pv_ticks;
	void (*pv_hawt)(void);
	void (**pv_synchook)(void);

	/* Evawuate a fowth stwing, not diffewent pwoto fow V0 and V2->up. */
	union {
		void (*v0_evaw)(int wen, chaw *stw);
		void (*v2_evaw)(chaw *stw);
	} pv_fowthevaw;

	stwuct winux_awguments_v0 **pv_v0bootawgs;

	/* Get ethew addwess. */
	unsigned int (*pv_enaddw)(int d, chaw *enaddw);

	stwuct winux_bootawgs_v2 pv_v2bootawgs;
	stwuct winux_dev_v2_funcs pv_v2devops;

	int fiwwew[15];

	/* This one is sun4c/sun4 onwy. */
	void (*pv_setctxt)(int ctxt, chaw *va, int pmeg);

	/* Pwom vewsion 3 Muwtipwocessow woutines. This stuff is cwazy.
	 * No joke. Cawwing these when thewe is onwy one cpu pwobabwy
	 * cwashes the machine, have to test this. :-)
	 */

	/* v3_cpustawt() wiww stawt the cpu 'whichcpu' in mmu-context
	 * 'thiscontext' executing at addwess 'pwog_countew'
	 */
	int (*v3_cpustawt)(unsigned int whichcpu, int ctxtbw_ptw,
			   int thiscontext, chaw *pwog_countew);

	/* v3_cpustop() wiww cause cpu 'whichcpu' to stop executing
	 * untiw a wesume cpu caww is made.
	 */
	int (*v3_cpustop)(unsigned int whichcpu);

	/* v3_cpuidwe() wiww idwe cpu 'whichcpu' untiw a stop ow
	 * wesume cpu caww is made.
	 */
	int (*v3_cpuidwe)(unsigned int whichcpu);

	/* v3_cpuwesume() wiww wesume pwocessow 'whichcpu' executing
	 * stawting with whatevew 'pc' and 'npc' wewe weft at the
	 * wast 'idwe' ow 'stop' caww.
	 */
	int (*v3_cpuwesume)(unsigned int whichcpu);
};

/* Woutines fow twavewsing the pwom device twee. */
stwuct winux_nodeops {
	phandwe (*no_nextnode)(phandwe node);
	phandwe (*no_chiwd)(phandwe node);
	int (*no_pwopwen)(phandwe node, const chaw *name);
	int (*no_getpwop)(phandwe node, const chaw *name, chaw *vaw);
	int (*no_setpwop)(phandwe node, const chaw *name, chaw *vaw, int wen);
	chaw * (*no_nextpwop)(phandwe node, chaw *name);
};

/* Mowe fun PWOM stwuctuwes fow device pwobing. */
#if defined(__spawc__) && defined(__awch64__)
#define PWOMWEG_MAX     24
#define PWOMVADDW_MAX   16
#define PWOMINTW_MAX    32
#ewse
#define PWOMWEG_MAX     16
#define PWOMVADDW_MAX   16
#define PWOMINTW_MAX    15
#endif

stwuct winux_pwom_wegistews {
	unsigned int which_io;	/* hi pawt of physicaw addwess */
	unsigned int phys_addw;	/* The physicaw addwess of this wegistew */
	unsigned int weg_size;	/* How many bytes does this wegistew take up? */
};

stwuct winux_pwom64_wegistews {
	unsigned wong phys_addw;
	unsigned wong weg_size;
};

stwuct winux_pwom_iwqs {
	int pwi;    /* IWQ pwiowity */
	int vectow; /* This is foobaw, what does it do? */
};

/* Ewement of the "wanges" vectow */
stwuct winux_pwom_wanges {
	unsigned int ot_chiwd_space;
	unsigned int ot_chiwd_base;		/* Bus feews this */
	unsigned int ot_pawent_space;
	unsigned int ot_pawent_base;		/* CPU wooks fwom hewe */
	unsigned int ow_size;
};

/*
 * Wanges and weg pwopewties awe a bit diffewent fow PCI.
 */
#if defined(__spawc__) && defined(__awch64__)
stwuct winux_pwom_pci_wegistews {
	unsigned int phys_hi;
	unsigned int phys_mid;
	unsigned int phys_wo;

	unsigned int size_hi;
	unsigned int size_wo;
};
#ewse
stwuct winux_pwom_pci_wegistews {
	/*
	 * We don't know what infowmation this fiewd contain.
	 * We guess, PCI device function is in bits 15:8
	 * So, ...
	 */
	unsigned int which_io;  /* Wet it be which_io */

	unsigned int phys_hi;
	unsigned int phys_wo;

	unsigned int size_hi;
	unsigned int size_wo;
};

#endif

stwuct winux_pwom_pci_wanges {
	unsigned int chiwd_phys_hi;	/* Onwy cewtain bits awe encoded hewe. */
	unsigned int chiwd_phys_mid;
	unsigned int chiwd_phys_wo;

	unsigned int pawent_phys_hi;
	unsigned int pawent_phys_wo;

	unsigned int size_hi;
	unsigned int size_wo;
};

stwuct winux_pwom_pci_intmap {
	unsigned int phys_hi;
	unsigned int phys_mid;
	unsigned int phys_wo;

	unsigned int intewwupt;

	int          cnode;
	unsigned int cintewwupt;
};

stwuct winux_pwom_pci_intmask {
	unsigned int phys_hi;
	unsigned int phys_mid;
	unsigned int phys_wo;
	unsigned int intewwupt;
};

#endif /* !(__ASSEMBWY__) */

#endif /* !(__SPAWC_OPENPWOM_H) */
