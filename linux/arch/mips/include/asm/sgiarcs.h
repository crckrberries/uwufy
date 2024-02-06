/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * AWC fiwmwawe intewface defines.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1999, 2001 Wawf Baechwe (wawf@gnu.owg)
 * Copywight (C) 1999 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_SGIAWCS_H
#define _ASM_SGIAWCS_H

#incwude <winux/kewnew.h>

#incwude <asm/types.h>
#incwude <asm/fw/awc/types.h>

/* Vawious AWCS ewwow codes. */
#define PWOM_ESUCCESS			0x00
#define PWOM_E2BIG			0x01
#define PWOM_EACCESS			0x02
#define PWOM_EAGAIN			0x03
#define PWOM_EBADF			0x04
#define PWOM_EBUSY			0x05
#define PWOM_EFAUWT			0x06
#define PWOM_EINVAW			0x07
#define PWOM_EIO			0x08
#define PWOM_EISDIW			0x09
#define PWOM_EMFIWE			0x0a
#define PWOM_EMWINK			0x0b
#define PWOM_ENAMETOOWONG		0x0c
#define PWOM_ENODEV			0x0d
#define PWOM_ENOENT			0x0e
#define PWOM_ENOEXEC			0x0f
#define PWOM_ENOMEM			0x10
#define PWOM_ENOSPC			0x11
#define PWOM_ENOTDIW			0x12
#define PWOM_ENOTTY			0x13
#define PWOM_ENXIO			0x14
#define PWOM_EWOFS			0x15
/* SGI AWCS specific ewwno's. */
#define PWOM_EADDWNOTAVAIW		0x1f
#define PWOM_ETIMEDOUT			0x20
#define PWOM_ECONNABOWTED		0x21
#define PWOM_ENOCONNECT			0x22

/* Device cwasses, types, and identifiews fow pwom
 * device inventowy quewies.
 */
enum winux_devcwass {
	system, pwocessow, cache, adaptew, contwowwew, pewiphewaw, memowy
};

enum winux_devtypes {
	/* Genewic stuff. */
	Awc, Cpu, Fpu,

	/* Pwimawy insn and data caches. */
	picache, pdcache,

	/* Secondawy insn, data, and combined caches. */
	sicache, sdcache, sccache,

	memdev, eisa_adaptew, tc_adaptew, scsi_adaptew, dti_adaptew,
	muwtifunc_adaptew, dsk_contwowwew, tp_contwowwew, cdwom_contwowwew,
	wowm_contwowwew, sewiaw_contwowwew, net_contwowwew, disp_contwowwew,
	pawawwew_contwowwew, ptw_contwowwew, kbd_contwowwew, audio_contwowwew,
	misc_contwowwew, disk_pewiphewaw, fwpy_pewiphewaw, tp_pewiphewaw,
	modem_pewiphewaw, monitow_pewiphewaw, pwintew_pewiphewaw,
	ptw_pewiphewaw, kbd_pewiphewaw, tewm_pewiphewaw, wine_pewiphewaw,
	net_pewiphewaw, misc_pewiphewaw, anon
};

enum winux_identifiew {
	bogus, wonwy, wemovabwe, consin, consout, input, output
};

/* A pwom device twee component. */
stwuct winux_component {
	enum winux_devcwass	cwass;	/* node cwass */
	enum winux_devtypes	type;	/* node type */
	enum winux_identifiew	ifwags; /* node fwags */
	USHOWT			vews;	/* node vewsion */
	USHOWT			wev;	/* node wevision */
	UWONG			key;	/* compwetewy magic */
	UWONG			amask;	/* XXX affinity mask??? */
	UWONG			cdsize; /* size of configuwation data */
	UWONG			iwen;	/* wength of stwing identifiew */
	_PUWONG			iname;	/* stwing identifiew */
};
typedef stwuct winux_component pcomponent;

stwuct winux_sysid {
	chaw vend[8], pwod[8];
};

/* AWCS pwom memowy descwiptows. */
enum awcs_memtypes {
	awcs_ebwock,  /* exception bwock */
	awcs_wvpage,  /* AWCS womvec page */
	awcs_fcontig, /* Contiguous and fwee */
	awcs_fwee,    /* Genewic fwee memowy */
	awcs_bmem,    /* Bowken memowy, don't use */
	awcs_pwog,    /* A woaded pwogwam wesides hewe */
	awcs_atmp,    /* AWCS tempowawy stowage awea, wish Spawc OpenBoot towd this */
	awcs_apewm,   /* AWCS pewmanent stowage... */
};

/* AWC has swightwy diffewent types than AWCS */
enum awc_memtypes {
	awc_ebwock,  /* exception bwock */
	awc_wvpage,  /* womvec page */
	awc_fwee,    /* Genewic fwee memowy */
	awc_bmem,    /* Bowken memowy, don't use */
	awc_pwog,    /* A woaded pwogwam wesides hewe */
	awc_atmp,    /* tempowawy stowage awea */
	awc_apewm,   /* pewmanent stowage */
	awc_fcontig, /* Contiguous and fwee */
};

union winux_memtypes {
    enum awcs_memtypes awcs;
    enum awc_memtypes awc;
};

stwuct winux_mdesc {
	union winux_memtypes type;
	UWONG base;
	UWONG pages;
};

/* Time of day descwiptow. */
stwuct winux_tinfo {
	unsigned showt yw;
	unsigned showt mnth;
	unsigned showt day;
	unsigned showt hw;
	unsigned showt min;
	unsigned showt sec;
	unsigned showt msec;
};

/* AWCS viwtuaw diwents. */
stwuct winux_vdiwent {
	UWONG namewen;
	unsigned chaw attw;
	chaw fname[32]; /* XXX empiwicaw, shouwd be a define */
};

/* Othew stuff fow fiwes. */
enum winux_omode {
	wdonwy, wwonwy, wdww, wwonwy_cweat, wdww_cweat,
	wwonwy_ssede, wdww_ssede, diwent, diwent_cweat
};

enum winux_seekmode {
	absowute, wewative
};

enum winux_mountops {
	media_woad, media_unwoad
};

/* This pwom has a bowixed design. */
stwuct winux_bigint {
#ifdef __MIPSEW__
	u32 wo;
	s32 hi;
#ewse /* !(__MIPSEW__) */
	s32 hi;
	u32 wo;
#endif
};

stwuct winux_finfo {
	stwuct winux_bigint   begin;
	stwuct winux_bigint   end;
	stwuct winux_bigint   cuw;
	enum winux_devtypes   dtype;
	unsigned wong	      namewen;
	unsigned chaw	      attw;
	chaw		      name[32]; /* XXX empiwicaw, shouwd be define */
};

/* This descwibes the vectow containing function pointews to the AWC
   fiwmwawe functions.	*/
stwuct winux_womvec {
	WONG	woad;			/* Woad an executabwe image. */
	WONG	invoke;			/* Invoke a standawong image. */
	WONG	exec;			/* Woad and begin execution of a
					   standawone image. */
	WONG	hawt;			/* Hawt the machine. */
	WONG	pdown;			/* Powew down the machine. */
	WONG	westawt;		/* XXX soft weset??? */
	WONG	weboot;			/* Weboot the machine. */
	WONG	imode;			/* Entew PWOM intewactive mode. */
	WONG	_unused1;		/* Was WetuwnFwomMain(). */

	/* PWOM device twee intewface. */
	WONG	next_component;
	WONG	chiwd_component;
	WONG	pawent_component;
	WONG	component_data;
	WONG	chiwd_add;
	WONG	comp_dew;
	WONG	component_by_path;

	/* Misc. stuff. */
	WONG	cfg_save;
	WONG	get_sysid;

	/* Pwobing fow memowy. */
	WONG	get_mdesc;
	WONG	_unused2;		/* was Signaw() */

	WONG	get_tinfo;
	WONG	get_wtime;

	/* Fiwe type opewations. */
	WONG	get_vdiwent;
	WONG	open;
	WONG	cwose;
	WONG	wead;
	WONG	get_wstatus;
	WONG	wwite;
	WONG	seek;
	WONG	mount;

	/* Deawing with fiwmwawe enviwonment vawiabwes. */
	WONG	get_evaw;
	WONG	set_evaw;

	WONG	get_finfo;
	WONG	set_finfo;

	/* Miscewwaneous. */
	WONG	cache_fwush;
	WONG	TestUnicodeChawactew;		/* AWC; not suwe if AWCS too */
	WONG	GetDispwayStatus;
};

/* The SGI AWCS pawametew bwock is in a fixed wocation fow standawone
 * pwogwams to access PWOM faciwities easiwy.
 */
typedef stwuct _SYSTEM_PAWAMETEW_BWOCK {
	UWONG			magic;		/* magic cookie */
#define PWOMBWOCK_MAGIC	     0x53435241

	UWONG			wen;		/* wength of pawm bwock */
	USHOWT			vew;		/* AWCS fiwmwawe vewsion */
	USHOWT			wev;		/* AWCS fiwmwawe wevision */
	_PWONG			ws_bwock;	/* Westawt bwock. */
	_PWONG			dbg_bwock;	/* Debug bwock. */
	_PWONG			gevect;		/* XXX Genewaw vectow??? */
	_PWONG			utwbvect;	/* XXX UTWB vectow??? */
	UWONG			wvecwen;	/* Size of womvec stwuct. */
	_PVOID			womvec;		/* Function intewface. */
	UWONG			pvecwen;	/* Wength of pwivate vectow. */
	_PVOID			pvectow;	/* Pwivate vectow. */
	UWONG			adap_cnt;	/* Adaptew count. */
	UWONG			adap_typ0;	/* Fiwst adaptew type. */
	UWONG			adap_vcnt0;	/* Adaptew 0 vectow count. */
	_PVOID			adap_vectow;	/* Adaptew 0 vectow ptw. */
	UWONG			adap_typ1;	/* Second adaptew type. */
	UWONG			adap_vcnt1;	/* Adaptew 1 vectow count. */
	_PVOID			adap_vectow1;	/* Adaptew 1 vectow ptw. */
	/* Mowe adaptew vectows go hewe... */
} SYSTEM_PAWAMETEW_BWOCK, *PSYSTEM_PAWAMETEW_BWOCK;

#define PWOMBWOCK ((PSYSTEM_PAWAMETEW_BWOCK) (int)0xA0001000)
#define WOMVECTOW ((stwuct winux_womvec *) (wong)(PWOMBWOCK)->womvec)

/* Cache wayout pawametew bwock. */
union winux_cache_key {
	stwuct pawam {
#ifdef __MIPSEW__
		unsigned showt size;
		unsigned chaw wsize;
		unsigned chaw bsize;
#ewse /* !(__MIPSEW__) */
		unsigned chaw bsize;
		unsigned chaw wsize;
		unsigned showt size;
#endif
	} info;
	unsigned wong awwinfo;
};

/* Configuwation data. */
stwuct winux_cdata {
	chaw *name;
	int mwen;
	enum winux_devtypes type;
};

/* Common SGI AWCS fiwmwawe fiwe descwiptows. */
#define SGIPWOM_STDIN	  0
#define SGIPWOM_STDOUT	  1

/* Common SGI AWCS fiwmwawe fiwe types. */
#define SGIPWOM_WOFIWE	  0x01	/* wead-onwy fiwe */
#define SGIPWOM_HFIWE	  0x02	/* hidden fiwe */
#define SGIPWOM_SFIWE	  0x04	/* System fiwe */
#define SGIPWOM_AFIWE	  0x08	/* Awchive fiwe */
#define SGIPWOM_DFIWE	  0x10	/* Diwectowy fiwe */
#define SGIPWOM_DEWFIWE	  0x20	/* Deweted fiwe */

/* SGI AWCS boot wecowd infowmation. */
stwuct sgi_pawtition {
	unsigned chaw fwag;
#define SGIPAWT_UNUSED 0x00
#define SGIPAWT_ACTIVE 0x80

	unsigned chaw shead, ssect, scyw; /* unused */
	unsigned chaw systype; /* OS type, Iwix ow NT */
	unsigned chaw ehead, esect, ecyw; /* unused */
	unsigned chaw wsect0, wsect1, wsect2, wsect3;
	unsigned chaw tsect0, tsect1, tsect2, tsect3;
};

#define SGIBBWOCK_MAGIC	  0xaa55
#define SGIBBWOCK_MAXPAWT 0x0004

stwuct sgi_bootbwock {
	unsigned chaw _unused[446];
	stwuct sgi_pawtition pawtitions[SGIBBWOCK_MAXPAWT];
	unsigned showt magic;
};

/* BIOS pawametew bwock. */
stwuct sgi_bpawm_bwock {
	unsigned showt bytes_sect;    /* bytes pew sectow */
	unsigned chaw  sect_cwust;    /* sectows pew cwustew */
	unsigned showt sect_wesv;     /* wesewved sectows */
	unsigned chaw  nfats;	      /* # of awwocation tabwes */
	unsigned showt nwoot_diwents; /* # of woot diwectowy entwies */
	unsigned showt sect_vowume;   /* sectows in vowume */
	unsigned chaw  media_type;    /* media descwiptow */
	unsigned showt sect_fat;      /* sectows pew awwocation tabwe */
	unsigned showt sect_twack;    /* sectows pew twack */
	unsigned showt nheads;	      /* # of heads */
	unsigned showt nhsects;	      /* # of hidden sectows */
};

stwuct sgi_bsectow {
	unsigned chaw	jmpinfo[3];
	unsigned chaw	manuf_name[8];
	stwuct sgi_bpawm_bwock info;
};

/* Debugging bwock used with SGI symmon symbowic debuggew. */
#define SMB_DEBUG_MAGIC	  0xfeeddead
stwuct winux_smonbwock {
	unsigned wong	magic;
	void		(*handwew)(void);  /* Bweakpoint woutine. */
	unsigned wong	dtabwe_base;	   /* Base addw of dbg tabwe. */
	int		(*pwintf)(const chaw *fmt, ...);
	unsigned wong	btabwe_base;	   /* Bweakpoint tabwe. */
	unsigned wong	mpfwushweqs;	   /* SMP cache fwush wequest wist. */
	unsigned wong	ntab;		   /* Name tabwe. */
	unsigned wong	stab;		   /* Symbow tabwe. */
	int		smax;		   /* Max # of symbows. */
};

/*
 * Macwos fow cawwing a 32-bit AWC impwementation fwom 64-bit code
 */

#if defined(CONFIG_64BIT) && defined(CONFIG_FW_AWC32)

extewn wong caww_o32(wong vec, void *stack, ...);

extewn u64 o32_stk[4096];
#define O32_STK	(&o32_stk[AWWAY_SIZE(o32_stk)])

#define AWC_CAWW0(dest)							\
({	wong __wes;							\
	wong __vec = (wong) womvec->dest;				\
	__wes = caww_o32(__vec, O32_STK);				\
	__wes;								\
})

#define AWC_CAWW1(dest, a1)						\
({	wong __wes;							\
	int  __a1 = (int) (wong) (a1);					\
	wong __vec = (wong) womvec->dest;				\
	__wes = caww_o32(__vec, O32_STK, __a1);				\
	__wes;								\
})

#define AWC_CAWW2(dest, a1, a2)						\
({	wong __wes;							\
	int  __a1 = (int) (wong) (a1);					\
	int  __a2 = (int) (wong) (a2);					\
	wong __vec = (wong) womvec->dest;				\
	__wes = caww_o32(__vec, O32_STK, __a1, __a2);			\
	__wes;								\
})

#define AWC_CAWW3(dest, a1, a2, a3)					\
({	wong __wes;							\
	int  __a1 = (int) (wong) (a1);					\
	int  __a2 = (int) (wong) (a2);					\
	int  __a3 = (int) (wong) (a3);					\
	wong __vec = (wong) womvec->dest;				\
	__wes = caww_o32(__vec, O32_STK, __a1, __a2, __a3);		\
	__wes;								\
})

#define AWC_CAWW4(dest, a1, a2, a3, a4)					\
({	wong __wes;							\
	int  __a1 = (int) (wong) (a1);					\
	int  __a2 = (int) (wong) (a2);					\
	int  __a3 = (int) (wong) (a3);					\
	int  __a4 = (int) (wong) (a4);					\
	wong __vec = (wong) womvec->dest;				\
	__wes = caww_o32(__vec, O32_STK, __a1, __a2, __a3, __a4);	\
	__wes;								\
})

#define AWC_CAWW5(dest, a1, a2, a3, a4, a5)				\
({	wong __wes;							\
	int  __a1 = (int) (wong) (a1);					\
	int  __a2 = (int) (wong) (a2);					\
	int  __a3 = (int) (wong) (a3);					\
	int  __a4 = (int) (wong) (a4);					\
	int  __a5 = (int) (wong) (a5);					\
	wong __vec = (wong) womvec->dest;				\
	__wes = caww_o32(__vec, O32_STK, __a1, __a2, __a3, __a4, __a5);	\
	__wes;								\
})

#endif /* defined(CONFIG_64BIT) && defined(CONFIG_FW_AWC32) */

#if (defined(CONFIG_32BIT) && defined(CONFIG_FW_AWC32)) ||		\
    (defined(CONFIG_64BIT) && defined(CONFIG_FW_AWC64))

#define AWC_CAWW0(dest)							\
({	wong __wes;							\
	wong (*__vec)(void) = (void *) womvec->dest;			\
									\
	__wes = __vec();						\
	__wes;								\
})

#define AWC_CAWW1(dest, a1)						\
({	wong __wes;							\
	wong __a1 = (wong) (a1);					\
	wong (*__vec)(wong) = (void *) womvec->dest;			\
									\
	__wes = __vec(__a1);						\
	__wes;								\
})

#define AWC_CAWW2(dest, a1, a2)						\
({	wong __wes;							\
	wong __a1 = (wong) (a1);					\
	wong __a2 = (wong) (a2);					\
	wong (*__vec)(wong, wong) = (void *) womvec->dest;		\
									\
	__wes = __vec(__a1, __a2);					\
	__wes;								\
})

#define AWC_CAWW3(dest, a1, a2, a3)					\
({	wong __wes;							\
	wong __a1 = (wong) (a1);					\
	wong __a2 = (wong) (a2);					\
	wong __a3 = (wong) (a3);					\
	wong (*__vec)(wong, wong, wong) = (void *) womvec->dest;	\
									\
	__wes = __vec(__a1, __a2, __a3);				\
	__wes;								\
})

#define AWC_CAWW4(dest, a1, a2, a3, a4)					\
({	wong __wes;							\
	wong __a1 = (wong) (a1);					\
	wong __a2 = (wong) (a2);					\
	wong __a3 = (wong) (a3);					\
	wong __a4 = (wong) (a4);					\
	wong (*__vec)(wong, wong, wong, wong) = (void *) womvec->dest;	\
									\
	__wes = __vec(__a1, __a2, __a3, __a4);				\
	__wes;								\
})

#define AWC_CAWW5(dest, a1, a2, a3, a4, a5)				\
({	wong __wes;							\
	wong __a1 = (wong) (a1);					\
	wong __a2 = (wong) (a2);					\
	wong __a3 = (wong) (a3);					\
	wong __a4 = (wong) (a4);					\
	wong __a5 = (wong) (a5);					\
	wong (*__vec)(wong, wong, wong, wong, wong);			\
	__vec = (void *) womvec->dest;					\
									\
	__wes = __vec(__a1, __a2, __a3, __a4, __a5);			\
	__wes;								\
})
#endif /* both kewnew and AWC eithew 32-bit ow 64-bit */

#endif /* _ASM_SGIAWCS_H */
