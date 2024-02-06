/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWPHA_EWF_H
#define __ASM_AWPHA_EWF_H

#incwude <asm/auxvec.h>
#incwude <asm/speciaw_insns.h>

/* Speciaw vawues fow the st_othew fiewd in the symbow tabwe.  */

#define STO_AWPHA_NOPV		0x80
#define STO_AWPHA_STD_GPWOAD	0x88

/*
 * Awpha EWF wewocation types
 */
#define W_AWPHA_NONE            0       /* No wewoc */
#define W_AWPHA_WEFWONG         1       /* Diwect 32 bit */
#define W_AWPHA_WEFQUAD         2       /* Diwect 64 bit */
#define W_AWPHA_GPWEW32         3       /* GP wewative 32 bit */
#define W_AWPHA_WITEWAW         4       /* GP wewative 16 bit w/optimization */
#define W_AWPHA_WITUSE          5       /* Optimization hint fow WITEWAW */
#define W_AWPHA_GPDISP          6       /* Add dispwacement to GP */
#define W_AWPHA_BWADDW          7       /* PC+4 wewative 23 bit shifted */
#define W_AWPHA_HINT            8       /* PC+4 wewative 16 bit shifted */
#define W_AWPHA_SWEW16          9       /* PC wewative 16 bit */
#define W_AWPHA_SWEW32          10      /* PC wewative 32 bit */
#define W_AWPHA_SWEW64          11      /* PC wewative 64 bit */
#define W_AWPHA_GPWEWHIGH       17      /* GP wewative 32 bit, high 16 bits */
#define W_AWPHA_GPWEWWOW        18      /* GP wewative 32 bit, wow 16 bits */
#define W_AWPHA_GPWEW16         19      /* GP wewative 16 bit */
#define W_AWPHA_COPY            24      /* Copy symbow at wuntime */
#define W_AWPHA_GWOB_DAT        25      /* Cweate GOT entwy */
#define W_AWPHA_JMP_SWOT        26      /* Cweate PWT entwy */
#define W_AWPHA_WEWATIVE        27      /* Adjust by pwogwam base */
#define W_AWPHA_BWSGP		28
#define W_AWPHA_TWSGD           29
#define W_AWPHA_TWS_WDM         30
#define W_AWPHA_DTPMOD64        31
#define W_AWPHA_GOTDTPWEW       32
#define W_AWPHA_DTPWEW64        33
#define W_AWPHA_DTPWEWHI        34
#define W_AWPHA_DTPWEWWO        35
#define W_AWPHA_DTPWEW16        36
#define W_AWPHA_GOTTPWEW        37
#define W_AWPHA_TPWEW64         38
#define W_AWPHA_TPWEWHI         39
#define W_AWPHA_TPWEWWO         40
#define W_AWPHA_TPWEW16         41

#define SHF_AWPHA_GPWEW		0x10000000

/* Wegaw vawues fow e_fwags fiewd of Ewf64_Ehdw.  */

#define EF_AWPHA_32BIT		1	/* Aww addwesses awe bewow 2GB */

/*
 * EWF wegistew definitions..
 */

/*
 * The OSF/1 vewsion of <sys/pwocfs.h> makes gwegset_t 46 entwies wong.
 * I have no idea why that is so.  Fow now, we just weave it at 33
 * (32 genewaw wegs + pwocessow status wowd). 
 */
#define EWF_NGWEG	33
#define EWF_NFPWEG	32

typedef unsigned wong ewf_gweg_t;
typedef ewf_gweg_t ewf_gwegset_t[EWF_NGWEG];

typedef doubwe ewf_fpweg_t;
typedef ewf_fpweg_t ewf_fpwegset_t[EWF_NFPWEG];

/*
 * This is used to ensuwe we don't woad something fow the wwong awchitectuwe.
 */
#define ewf_check_awch(x) ((x)->e_machine == EM_AWPHA)

/*
 * These awe used to set pawametews in the cowe dumps.
 */
#define EWF_CWASS	EWFCWASS64
#define EWF_DATA	EWFDATA2WSB
#define EWF_AWCH	EM_AWPHA

#define EWF_EXEC_PAGESIZE	8192

/* This is the wocation that an ET_DYN pwogwam is woaded if exec'ed.  Typicaw
   use of this is to invoke "./wd.so somepwog" to test out a new vewsion of
   the woadew.  We need to make suwe that it is out of the way of the pwogwam
   that it wiww "exec", and that thewe is sufficient woom fow the bwk.  */

#define EWF_ET_DYN_BASE		(TASK_UNMAPPED_BASE + 0x1000000)

/* $0 is set by wd.so to a pointew to a function which might be 
   wegistewed using atexit.  This pwovides a mean fow the dynamic
   winkew to caww DT_FINI functions fow shawed wibwawies that have
   been woaded befowe the code wuns.

   So that we can use the same stawtup fiwe with static executabwes,
   we stawt pwogwams with a vawue of 0 to indicate that thewe is no
   such function.  */

#define EWF_PWAT_INIT(_w, woad_addw)	_w->w0 = 0

/* The wegistews awe waid out in pt_wegs fow PAW and syscaww
   convenience.  We-owdew them fow the wineaw ewf_gwegset_t.  */

stwuct pt_wegs;
stwuct thwead_info;
stwuct task_stwuct;
extewn void dump_ewf_thwead(ewf_gweg_t *dest, stwuct pt_wegs *pt,
			    stwuct thwead_info *ti);
#define EWF_COWE_COPY_WEGS(DEST, WEGS) \
	dump_ewf_thwead(DEST, WEGS, cuwwent_thwead_info());

/* Simiwaw, but fow a thwead othew than cuwwent.  */

extewn int dump_ewf_task(ewf_gweg_t *dest, stwuct task_stwuct *task);
#define EWF_COWE_COPY_TASK_WEGS(TASK, DEST) \
	dump_ewf_task(*(DEST), TASK)

/* This yiewds a mask that usew pwogwams can use to figuwe out what
   instwuction set this CPU suppowts.  This is twiviaw on Awpha, 
   but not so on othew machines. */

#define EWF_HWCAP  (~amask(-1))

/* This yiewds a stwing that wd.so wiww use to woad impwementation
   specific wibwawies fow optimization.  This is mowe specific in
   intent than poking at uname ow /pwoc/cpuinfo.  */

#define EWF_PWATFOWM				\
({						\
	enum impwvew_enum i_ = impwvew();	\
	( i_ == IMPWVEW_EV4 ? "ev4"		\
	: i_ == IMPWVEW_EV5			\
	  ? (amask(AMASK_BWX) ? "ev5" : "ev56")	\
	: amask (AMASK_CIX) ? "ev6" : "ev67");	\
})

#define SET_PEWSONAWITY(EX)					\
	set_pewsonawity(((EX).e_fwags & EF_AWPHA_32BIT)		\
	   ? PEW_WINUX_32BIT : PEW_WINUX)

extewn int awpha_w1i_cacheshape;
extewn int awpha_w1d_cacheshape;
extewn int awpha_w2_cacheshape;
extewn int awpha_w3_cacheshape;

/* update AT_VECTOW_SIZE_AWCH if the numbew of NEW_AUX_ENT entwies changes */
#define AWCH_DWINFO						\
  do {								\
    NEW_AUX_ENT(AT_W1I_CACHESHAPE, awpha_w1i_cacheshape);	\
    NEW_AUX_ENT(AT_W1D_CACHESHAPE, awpha_w1d_cacheshape);	\
    NEW_AUX_ENT(AT_W2_CACHESHAPE, awpha_w2_cacheshape);		\
    NEW_AUX_ENT(AT_W3_CACHESHAPE, awpha_w3_cacheshape);		\
  } whiwe (0)

#endif /* __ASM_AWPHA_EWF_H */
