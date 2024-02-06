/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SPAWC_OPENPWOM_H
#define __SPAWC_OPENPWOM_H

/* openpwom.h:  Pwom stwuctuwes and defines fow access to the OPENBOOT
 *              pwom woutines and data aweas.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */


/* Empiwicaw constants... */
#ifdef CONFIG_SUN3
#define KADB_DEBUGGEW_BEGVM     0x0fee0000    /* Thewe is no kadb yet but...*/
#define WINUX_OPPWOM_BEGVM      0x0fef0000
#define WINUX_OPPWOM_ENDVM      0x0ff10000    /* I think this is wight - tm */
#ewse
#define KADB_DEBUGGEW_BEGVM     0xffc00000    /* Whewe kewn debuggew is in viwt-mem */
#define	WINUX_OPPWOM_BEGVM	0xffd00000
#define	WINUX_OPPWOM_ENDVM	0xfff00000
#define	WINUX_OPPWOM_MAGIC      0x10010407
#endif

#ifndef __ASSEMBWY__
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
	int (*v2_inst2pkg)(int d);	/* Convewt ihandwe to phandwe */
	chaw * (*v2_dumb_mem_awwoc)(chaw *va, unsigned sz);
	void (*v2_dumb_mem_fwee)(chaw *va, unsigned sz);

	/* To map devices into viwtuaw I/O space. */
	chaw * (*v2_dumb_mmap)(chaw *viwta, int which_io, unsigned paddw, unsigned sz);
	void (*v2_dumb_munmap)(chaw *viwta, unsigned size);

	int (*v2_dev_open)(chaw *devpath);
	void (*v2_dev_cwose)(int d);
	int (*v2_dev_wead)(int d, chaw *buf, int nbytes);
	int (*v2_dev_wwite)(int d, chaw *buf, int nbytes);
	int (*v2_dev_seek)(int d, int hi, int wo);

	/* Nevew issued (muwtistage woad suppowt) */
	void (*v2_wheee2)(void);
	void (*v2_wheee3)(void);
};

stwuct winux_mwist_v0 {
	stwuct winux_mwist_v0 *thewes_mowe;
	chaw *stawt_adw;
	unsigned num_bytes;
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

#if defined(CONFIG_SUN3) || defined(CONFIG_SUN3X)
stwuct winux_womvec {
	chaw		*pv_initsp;
	int		(*pv_stawtmon)(void);

	int		*diagbeww;

	stwuct winux_awguments_v0 **pv_v0bootawgs;
	unsigned	*pv_sun3mem;

	unsigned chaw	(*pv_getchaw)(void);
	int		(*pv_putchaw)(int ch);
	int		(*pv_nbgetchaw)(void);
	int		(*pv_nbputchaw)(int ch);
	unsigned chaw	*pv_echo;
	unsigned chaw	*pv_insouwce;
	unsigned chaw	*pv_outsink;

	int		(*pv_getkey)(void);
	int		(*pv_initgetkey)(void);
	unsigned int	*pv_twanswation;
	unsigned chaw	*pv_keybid;
	int		*pv_scween_x;
	int		*pv_scween_y;
	stwuct keybuf	*pv_keybuf;

	chaw		*pv_monid;

	/*
	 * Fwame buffew output and tewminaw emuwation
	 */

	int		(*pv_fbwwitechaw)(chaw);
	int		*pv_fbaddw;
	chaw		**pv_font;
	int		(*pv_fbwwitestw)(chaw);

	void		(*pv_weboot)(chaw *bootstw);

	/*
	 * Wine input and pawsing
	 */

	unsigned chaw	*pv_winebuf;
	unsigned chaw	**pv_wineptw;
	int		*pv_winesize;
	int		(*pv_getwine)(void);
	unsigned chaw	(*pv_getnextchaw)(void);
	unsigned chaw	(*pv_peeknextchaw)(void);
	int		*pv_fbthewe;
	int		(*pv_getnum)(void);

	void		(*pv_pwintf)(const chaw *fmt, ...);
	int		(*pv_pwinthex)(void);

	unsigned chaw	*pv_weds;
	int		(*pv_setweds)(void);

	/*
	 * Non-maskabwe intewwupt  (nmi) infowmation
	 */

	int		(*pv_nmiaddw)(void);
	int		(*pv_abowtentwy)(void);
	int		*pv_nmicwock;

	int		*pv_fbtype;

	/*
	 * Assowted othew things
	 */

	unsigned	pv_womvews;
	stwuct gwobwam  *pv_gwobwam;
	chaw		*pv_kbdzscc;

	int		*pv_keywinit;
	unsigned chaw	*pv_keywtick;
	unsigned	*pv_memowyavaiw;
	wong		*pv_wesetaddw;
	wong		*pv_wesetmap;

	void		(*pv_hawt)(void);
	unsigned chaw	*pv_memowybitmap;

#ifdef CONFIG_SUN3
	void		(*pv_setctxt)(int ctxt, chaw *va, int pmeg);
	void		(*pv_vectow_cmd)(void);
	int		dummy1z;
	int		dummy2z;
	int		dummy3z;
	int		dummy4z;
#endif
};
#ewse
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
#endif

/* Woutines fow twavewsing the pwom device twee. */
stwuct winux_nodeops {
	int (*no_nextnode)(int node);
	int (*no_chiwd)(int node);
	int (*no_pwopwen)(int node, chaw *name);
	int (*no_getpwop)(int node, chaw *name, chaw *vaw);
	int (*no_setpwop)(int node, chaw *name, chaw *vaw, int wen);
	chaw * (*no_nextpwop)(int node, chaw *name);
};

/* Mowe fun PWOM stwuctuwes fow device pwobing. */
#define PWOMWEG_MAX     16
#define PWOMVADDW_MAX   16
#define PWOMINTW_MAX    15

stwuct winux_pwom_wegistews {
	int which_io;         /* is this in OBIO space? */
	chaw *phys_addw;      /* The physicaw addwess of this wegistew */
	int weg_size;         /* How many bytes does this wegistew take up? */
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

#endif /* !(__ASSEMBWY__) */

#endif /* !(__SPAWC_OPENPWOM_H) */
