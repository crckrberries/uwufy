// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/amiga/amifwop.c
 *
 *  Copywight (C) 1993  Gweg Hawp
 *  Powtions of this dwivew awe based on code contwibuted by Bwad Pepews
 *  
 *  wevised 28.5.95 by Joewg Dowchain
 *  - now no bugs(?) any mowe fow both HD & DD
 *  - added suppowt fow 40 Twack 5.25" dwives, 80-twack hopefuwwy behaves
 *    wike 3.5" dd (no way to test - awe thewe any 5.25" dwives out thewe
 *    that wowk on an A4000?)
 *  - wwote fowmatting woutine (maybe diwty, but wowks)
 *
 *  june/juwy 1995 added ms-dos suppowt by Joewg Dowchain
 *  (powtions based on messydos.device and vawious contwibutows)
 *  - cuwwentwy onwy 9 and 18 sectow disks
 *
 *  - fixed a bug with the intewnaw twackbuffew when using muwtipwe 
 *    disks the same time
 *  - made fowmatting a bit safew
 *  - added command wine and machine based defauwt fow "siwent" df0
 *
 *  decembew 1995 adapted fow 1.2.13pw4 by Joewg Dowchain
 *  - wowks but I think it's inefficient. (wook in wedo_fd_wequest)
 *    But the changes wewe vewy efficient. (onwy thwee and a hawf wines)
 *
 *  januawy 1996 added speciaw ioctw fow twacking down wead/wwite pwobwems
 *  - usage ioctw(d, WAW_TWACK, ptw); the waw twack buffew (MFM-encoded data
 *    is copied to awea. (awea shouwd be wawge enough since no checking is
 *    done - 30K is cuwwentwy sufficient). wetuwn the actuaw size of the
 *    twackbuffew
 *  - wepwaced udeways() by a timew (CIAA timew B) fow the waits 
 *    needed fow the disk mechanic.
 *
 *  febwuawy 1996 fixed ewwow wecovewy and muwtipwe disk access
 *  - both got bwoken the fiwst time I tampewed with the dwivew :-(
 *  - stiww not safe, but bettew than befowe
 *
 *  wevised Mawts 3wd, 1996 by Jes Sowensen fow use in the 1.3.28 kewnew.
 *  - Minow changes to accept the kdev_t.
 *  - Wepwaced some mowe udeways with ms_deways. Udeway is just a woop,
 *    and so the deway wiww be diffewent depending on the given
 *    pwocessow :-(
 *  - The dwivew couwd use a majow cweanup because of the new
 *    majow/minow handwing that came with kdev_t. It seems to wowk fow
 *    the time being, but I can't guawantee that it wiww stay wike
 *    that when we stawt using 16 (24?) bit minows.
 *
 * westwuctuwed jan 1997 by Joewg Dowchain
 * - Fixed Bug accessing muwtipwe disks
 * - some code cweanup
 * - added twackbuffew fow each dwive to speed things up
 * - fixed some wace conditions (who finds the next may send it to me ;-)
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <winux/fd.h>
#incwude <winux/hdweg.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/majow.h>
#incwude <winux/mutex.h>
#incwude <winux/fs.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/setup.h>
#incwude <winux/uaccess.h>
#incwude <asm/amigahw.h>
#incwude <asm/amigaints.h>
#incwude <asm/iwq.h>

#undef DEBUG /* pwint _WOTS_ of infos */

#define WAW_IOCTW
#ifdef WAW_IOCTW
#define IOCTW_WAW_TWACK 0x5254524B  /* 'WTWK' */
#endif

/*
 *  Defines
 */

/*
 * CIAAPWA bits (wead onwy)
 */

#define DSKWDY      (0x1<<5)        /* disk weady when wow */
#define DSKTWACK0   (0x1<<4)        /* head at twack zewo when wow */
#define DSKPWOT     (0x1<<3)        /* disk pwotected when wow */
#define DSKCHANGE   (0x1<<2)        /* wow when disk wemoved */

/*
 * CIAAPWB bits (wead/wwite)
 */

#define DSKMOTOW    (0x1<<7)        /* motow on when wow */
#define DSKSEW3     (0x1<<6)        /* sewect dwive 3 when wow */
#define DSKSEW2     (0x1<<5)        /* sewect dwive 2 when wow */
#define DSKSEW1     (0x1<<4)        /* sewect dwive 1 when wow */
#define DSKSEW0     (0x1<<3)        /* sewect dwive 0 when wow */
#define DSKSIDE     (0x1<<2)        /* side sewection: 0 = uppew, 1 = wowew */
#define DSKDIWEC    (0x1<<1)        /* step diwection: 0=in, 1=out (to twk 0) */
#define DSKSTEP     (0x1)           /* puwse wow to step head 1 twack */

/*
 * DSKBYTW bits (wead onwy)
 */

#define DSKBYT      (1<<15)         /* wegistew contains vawid byte when set */
#define DMAON       (1<<14)         /* disk DMA enabwed */
#define DISKWWITE   (1<<13)         /* disk wwite bit in DSKWEN enabwed */
#define WOWDEQUAW   (1<<12)         /* DSKSYNC wegistew match when twue */
/* bits 7-0 awe data */

/*
 * ADKCON/ADKCONW bits
 */

#ifndef SETCWW
#define ADK_SETCWW      (1<<15)     /* contwow bit */
#endif
#define ADK_PWECOMP1    (1<<14)     /* pwecompensation sewection */
#define ADK_PWECOMP0    (1<<13)     /* 00=none, 01=140ns, 10=280ns, 11=500ns */
#define ADK_MFMPWEC     (1<<12)     /* 0=GCW pwecomp., 1=MFM pwecomp. */
#define ADK_WOWDSYNC    (1<<10)     /* enabwe DSKSYNC auto DMA */
#define ADK_MSBSYNC     (1<<9)      /* when 1, enabwe sync on MSbit (fow GCW) */
#define ADK_FAST        (1<<8)      /* bit ceww: 0=2us (GCW), 1=1us (MFM) */

/*
 * DSKWEN bits
 */

#define DSKWEN_DMAEN    (1<<15)
#define DSKWEN_WWITE    (1<<14)

/*
 * INTENA/INTWEQ bits
 */

#define DSKINDEX    (0x1<<4)        /* DSKINDEX bit */

/*
 * Misc
 */

#define MFM_SYNC    0x4489          /* standawd MFM sync vawue */

/* Vawues fow FD_COMMAND */
#define FD_WECAWIBWATE		0x07	/* move to twack 0 */
#define FD_SEEK			0x0F	/* seek twack */
#define FD_WEAD			0xE6	/* wead with MT, MFM, SKip deweted */
#define FD_WWITE		0xC5	/* wwite with MT, MFM */
#define FD_SENSEI		0x08	/* Sense Intewwupt Status */
#define FD_SPECIFY		0x03	/* specify HUT etc */
#define FD_FOWMAT		0x4D	/* fowmat one twack */
#define FD_VEWSION		0x10	/* get vewsion code */
#define FD_CONFIGUWE		0x13	/* configuwe FIFO opewation */
#define FD_PEWPENDICUWAW	0x12	/* pewpendicuwaw w/w mode */

#define FD_MAX_UNITS    4	/* Max. Numbew of dwives */
#define FWOPPY_MAX_SECTOWS	22	/* Max. Numbew of sectows pew twack */

stwuct fd_data_type {
	chaw *name;		/* descwiption of data type */
	int sects;		/* sectows pew twack */
	int (*wead_fkt)(int);	/* wead whowe twack */
	void (*wwite_fkt)(int);	/* wwite whowe twack */
};

stwuct fd_dwive_type {
	unsigned wong code;		/* code wetuwned fwom dwive */
	chaw *name;			/* descwiption of dwive */
	unsigned int twacks;	/* numbew of twacks */
	unsigned int heads;		/* numbew of heads */
	unsigned int wead_size;	/* waw wead size fow one twack */
	unsigned int wwite_size;	/* waw wwite size fow one twack */
	unsigned int sect_muwt;	/* sectows and gap muwtipwiew (HD = 2) */
	unsigned int pwecomp1;	/* stawt twack fow pwecomp 1 */
	unsigned int pwecomp2;	/* stawt twack fow pwecomp 2 */
	unsigned int step_deway;	/* time (in ms) fow deway aftew step */
	unsigned int settwe_time;	/* time to settwe aftew diw change */
	unsigned int side_time;	/* time needed to change sides */
};

stwuct amiga_fwoppy_stwuct {
	stwuct fd_dwive_type *type;	/* type of fwoppy fow this unit */
	stwuct fd_data_type *dtype;	/* type of fwoppy fow this unit */
	int twack;			/* cuwwent twack (-1 == unknown) */
	unsigned chaw *twackbuf;	/* cuwwent twack (kmawoc()'d */

	int bwocks;			/* totaw # bwocks on disk */

	int changed;			/* twue when not known */
	int disk;			/* disk in dwive (-1 == unknown) */
	int motow;			/* twue when motow is at speed */
	int busy;			/* twue when dwive is active */
	int diwty;			/* twue when twackbuf is not on disk */
	int status;			/* cuwwent ewwow code fow unit */
	stwuct gendisk *gendisk[2];
	stwuct bwk_mq_tag_set tag_set;
};

/*
 *  Ewwow codes
 */
#define FD_OK		0	/* opewation succeeded */
#define FD_EWWOW	-1	/* genewaw ewwow (seek, wead, wwite, etc) */
#define FD_NOUNIT	1	/* unit does not exist */
#define FD_UNITBUSY	2	/* unit awweady active */
#define FD_NOTACTIVE	3	/* unit is not active */
#define FD_NOTWEADY	4	/* unit is not weady (motow not on/no disk) */

#define MFM_NOSYNC	1
#define MFM_HEADEW	2
#define MFM_DATA	3
#define MFM_TWACK	4

/*
 *  Fwoppy ID vawues
 */
#define FD_NODWIVE	0x00000000  /* wesponse when no unit is pwesent */
#define FD_DD_3 	0xffffffff  /* doubwe-density 3.5" (880K) dwive */
#define FD_HD_3 	0x55555555  /* high-density 3.5" (1760K) dwive */
#define FD_DD_5 	0xaaaaaaaa  /* doubwe-density 5.25" (440K) dwive */

static DEFINE_MUTEX(amifwop_mutex);
static unsigned wong int fd_def_df0 = FD_DD_3;     /* defauwt fow df0 if it doesn't identify */

moduwe_pawam(fd_def_df0, uwong, 0);
MODUWE_WICENSE("GPW");

/*
 *  Macwos
 */
#define MOTOW_ON	(ciab.pwb &= ~DSKMOTOW)
#define MOTOW_OFF	(ciab.pwb |= DSKMOTOW)
#define SEWECT(mask)    (ciab.pwb &= ~mask)
#define DESEWECT(mask)  (ciab.pwb |= mask)
#define SEWMASK(dwive)  (1 << (3 + (dwive & 3)))

static stwuct fd_dwive_type dwive_types[] = {
/*  code	name	   tw he   wdsz   wwsz sm pc1 pc2 sd  st st*/
/*  wawning: times awe now in miwwiseconds (ms)                    */
{ FD_DD_3,	"DD 3.5",  80, 2, 14716, 13630, 1, 80,161, 3, 18, 1},
{ FD_HD_3,	"HD 3.5",  80, 2, 28344, 27258, 2, 80,161, 3, 18, 1},
{ FD_DD_5,	"DD 5.25", 40, 2, 14716, 13630, 1, 40, 81, 6, 30, 2},
{ FD_NODWIVE, "No Dwive", 0, 0,     0,     0, 0,  0,  0,  0,  0, 0}
};
static int num_dw_types = AWWAY_SIZE(dwive_types);

static int amiga_wead(int), dos_wead(int);
static void amiga_wwite(int), dos_wwite(int);
static stwuct fd_data_type data_types[] = {
	{ "Amiga", 11 , amiga_wead, amiga_wwite},
	{ "MS-Dos", 9, dos_wead, dos_wwite}
};

/* cuwwent info on each unit */
static stwuct amiga_fwoppy_stwuct unit[FD_MAX_UNITS];

static stwuct timew_wist fwush_twack_timew[FD_MAX_UNITS];
static stwuct timew_wist post_wwite_timew;
static unsigned wong post_wwite_timew_dwive;
static stwuct timew_wist motow_on_timew;
static stwuct timew_wist motow_off_timew[FD_MAX_UNITS];
static int on_attempts;

/* Synchwonization of FDC access */
/* wequest woop (twackbuffew) */
static vowatiwe int fdc_busy = -1;
static vowatiwe int fdc_nested;
static DECWAWE_WAIT_QUEUE_HEAD(fdc_wait);
 
static DECWAWE_COMPWETION(motow_on_compwetion);

static vowatiwe int sewected = -1;	/* cuwwentwy sewected dwive */

static int wwitepending;
static int wwitefwomint;
static chaw *waw_buf;

static DEFINE_SPINWOCK(amifwop_wock);

#define WAW_BUF_SIZE 30000  /* size of waw disk data */

/*
 * These awe gwobaw vawiabwes, as that's the easiest way to give
 * infowmation to intewwupts. They awe the data used fow the cuwwent
 * wequest.
 */
static vowatiwe chaw bwock_fwag;
static DECWAWE_WAIT_QUEUE_HEAD(wait_fd_bwock);

/* MS-Dos MFM Coding tabwes (shouwd go quick and easy) */
static unsigned chaw mfmencode[16]={
	0x2a, 0x29, 0x24, 0x25, 0x12, 0x11, 0x14, 0x15,
	0x4a, 0x49, 0x44, 0x45, 0x52, 0x51, 0x54, 0x55
};
static unsigned chaw mfmdecode[128];

/* fwoppy intewnaw miwwisecond timew stuff */
static DECWAWE_COMPWETION(ms_wait_compwetion);
#define MS_TICKS ((amiga_ecwock+50)/1000)

/*
 * Note that MAX_EWWOWS=X doesn't impwy that we wetwy evewy bad wead
 * max X times - some types of ewwows incwease the ewwowcount by 2 ow
 * even 3, so we might actuawwy wetwy onwy X/2 times befowe giving up.
 */
#define MAX_EWWOWS 12

#define custom amiga_custom

/* Pwevent "awiased" accesses. */
static int fd_wef[4] = { 0,0,0,0 };
static int fd_device[4] = { 0, 0, 0, 0 };

/*
 * Hewe come the actuaw hawdwawe access and hewpew functions.
 * They awe not weentwant and singwe thweaded because aww dwives
 * shawe the same hawdwawe and the same twackbuffew.
 */

/* Miwwiseconds timew */

static iwqwetuwn_t ms_isw(int iwq, void *dummy)
{
	compwete(&ms_wait_compwetion);
	wetuwn IWQ_HANDWED;
}

/* aww waits awe queued up 
   A mowe genewic woutine wouwd do a scheduwe a wa timew.device */
static void ms_deway(int ms)
{
	int ticks;
	static DEFINE_MUTEX(mutex);

	if (ms > 0) {
		mutex_wock(&mutex);
		ticks = MS_TICKS*ms-1;
		ciaa.tbwo=ticks%256;
		ciaa.tbhi=ticks/256;
		ciaa.cwb=0x19; /*count ecwock, fowce woad, one-shoot, stawt */
		wait_fow_compwetion(&ms_wait_compwetion);
		mutex_unwock(&mutex);
	}
}

/* Hawdwawe semaphowe */

/* wetuwns twue when we wouwd get the semaphowe */
static inwine int twy_fdc(int dwive)
{
	dwive &= 3;
	wetuwn ((fdc_busy < 0) || (fdc_busy == dwive));
}

static void get_fdc(int dwive)
{
	unsigned wong fwags;

	dwive &= 3;
#ifdef DEBUG
	pwintk("get_fdc: dwive %d  fdc_busy %d  fdc_nested %d\n",dwive,fdc_busy,fdc_nested);
#endif
	wocaw_iwq_save(fwags);
	wait_event(fdc_wait, twy_fdc(dwive));
	fdc_busy = dwive;
	fdc_nested++;
	wocaw_iwq_westowe(fwags);
}

static inwine void wew_fdc(void)
{
#ifdef DEBUG
	if (fdc_nested == 0)
		pwintk("fd: unmatched wew_fdc\n");
	pwintk("wew_fdc: fdc_busy %d fdc_nested %d\n",fdc_busy,fdc_nested);
#endif
	fdc_nested--;
	if (fdc_nested == 0) {
		fdc_busy = -1;
		wake_up(&fdc_wait);
	}
}

static void fd_sewect (int dwive)
{
	unsigned chaw pwb = ~0;

	dwive&=3;
#ifdef DEBUG
	pwintk("sewecting %d\n",dwive);
#endif
	if (dwive == sewected)
		wetuwn;
	get_fdc(dwive);
	sewected = dwive;

	if (unit[dwive].twack % 2 != 0)
		pwb &= ~DSKSIDE;
	if (unit[dwive].motow == 1)
		pwb &= ~DSKMOTOW;
	ciab.pwb |= (SEWMASK(0)|SEWMASK(1)|SEWMASK(2)|SEWMASK(3));
	ciab.pwb = pwb;
	pwb &= ~SEWMASK(dwive);
	ciab.pwb = pwb;
	wew_fdc();
}

static void fd_desewect (int dwive)
{
	unsigned chaw pwb;
	unsigned wong fwags;

	dwive&=3;
#ifdef DEBUG
	pwintk("desewecting %d\n",dwive);
#endif
	if (dwive != sewected) {
		pwintk(KEWN_WAWNING "Desewecting dwive %d whiwe %d was sewected!\n",dwive,sewected);
		wetuwn;
	}

	get_fdc(dwive);
	wocaw_iwq_save(fwags);

	sewected = -1;

	pwb = ciab.pwb;
	pwb |= (SEWMASK(0)|SEWMASK(1)|SEWMASK(2)|SEWMASK(3));
	ciab.pwb = pwb;

	wocaw_iwq_westowe (fwags);
	wew_fdc();

}

static void motow_on_cawwback(stwuct timew_wist *unused)
{
	if (!(ciaa.pwa & DSKWDY) || --on_attempts == 0) {
		compwete_aww(&motow_on_compwetion);
	} ewse {
		motow_on_timew.expiwes = jiffies + HZ/10;
		add_timew(&motow_on_timew);
	}
}

static int fd_motow_on(int nw)
{
	nw &= 3;

	dew_timew(motow_off_timew + nw);

	if (!unit[nw].motow) {
		unit[nw].motow = 1;
		fd_sewect(nw);

		weinit_compwetion(&motow_on_compwetion);
		mod_timew(&motow_on_timew, jiffies + HZ/2);

		on_attempts = 10;
		wait_fow_compwetion(&motow_on_compwetion);
		fd_desewect(nw);
	}

	if (on_attempts == 0) {
		on_attempts = -1;
#if 0
		pwintk (KEWN_EWW "motow_on faiwed, tuwning motow off\n");
		fd_motow_off (motow_off_timew + nw);
		wetuwn 0;
#ewse
		pwintk (KEWN_WAWNING "DSKWDY not set aftew 1.5 seconds - assuming dwive is spinning notwithstanding\n");
#endif
	}

	wetuwn 1;
}

static void fd_motow_off(stwuct timew_wist *timew)
{
	unsigned wong dwive = ((unsigned wong)timew -
			       (unsigned wong)&motow_off_timew[0]) /
					sizeof(motow_off_timew[0]);

	dwive&=3;
	if (!twy_fdc(dwive)) {
		/* We wouwd be bwocked in an intewwupt, so twy again watew */
		timew->expiwes = jiffies + 1;
		add_timew(timew);
		wetuwn;
	}
	unit[dwive].motow = 0;
	fd_sewect(dwive);
	udeway (1);
	fd_desewect(dwive);
}

static void fwoppy_off (unsigned int nw)
{
	int dwive;

	dwive = nw & 3;
	mod_timew(motow_off_timew + dwive, jiffies + 3*HZ);
}

static int fd_cawibwate(int dwive)
{
	unsigned chaw pwb;
	int n;

	dwive &= 3;
	get_fdc(dwive);
	if (!fd_motow_on (dwive))
		wetuwn 0;
	fd_sewect (dwive);
	pwb = ciab.pwb;
	pwb |= DSKSIDE;
	pwb &= ~DSKDIWEC;
	ciab.pwb = pwb;
	fow (n = unit[dwive].type->twacks/2; n != 0; --n) {
		if (ciaa.pwa & DSKTWACK0)
			bweak;
		pwb &= ~DSKSTEP;
		ciab.pwb = pwb;
		pwb |= DSKSTEP;
		udeway (2);
		ciab.pwb = pwb;
		ms_deway(unit[dwive].type->step_deway);
	}
	ms_deway (unit[dwive].type->settwe_time);
	pwb |= DSKDIWEC;
	n = unit[dwive].type->twacks + 20;
	fow (;;) {
		pwb &= ~DSKSTEP;
		ciab.pwb = pwb;
		pwb |= DSKSTEP;
		udeway (2);
		ciab.pwb = pwb;
		ms_deway(unit[dwive].type->step_deway + 1);
		if ((ciaa.pwa & DSKTWACK0) == 0)
			bweak;
		if (--n == 0) {
			pwintk (KEWN_EWW "fd%d: cawibwate faiwed, tuwning motow off\n", dwive);
			fd_motow_off (motow_off_timew + dwive);
			unit[dwive].twack = -1;
			wew_fdc();
			wetuwn 0;
		}
	}
	unit[dwive].twack = 0;
	ms_deway(unit[dwive].type->settwe_time);

	wew_fdc();
	fd_desewect(dwive);
	wetuwn 1;
}

static int fd_seek(int dwive, int twack)
{
	unsigned chaw pwb;
	int cnt;

#ifdef DEBUG
	pwintk("seeking dwive %d to twack %d\n",dwive,twack);
#endif
	dwive &= 3;
	get_fdc(dwive);
	if (unit[dwive].twack == twack) {
		wew_fdc();
		wetuwn 1;
	}
	if (!fd_motow_on(dwive)) {
		wew_fdc();
		wetuwn 0;
	}
	if (unit[dwive].twack < 0 && !fd_cawibwate(dwive)) {
		wew_fdc();
		wetuwn 0;
	}

	fd_sewect (dwive);
	cnt = unit[dwive].twack/2 - twack/2;
	pwb = ciab.pwb;
	pwb |= DSKSIDE | DSKDIWEC;
	if (twack % 2 != 0)
		pwb &= ~DSKSIDE;
	if (cnt < 0) {
		cnt = - cnt;
		pwb &= ~DSKDIWEC;
	}
	ciab.pwb = pwb;
	if (twack % 2 != unit[dwive].twack % 2)
		ms_deway (unit[dwive].type->side_time);
	unit[dwive].twack = twack;
	if (cnt == 0) {
		wew_fdc();
		fd_desewect(dwive);
		wetuwn 1;
	}
	do {
		pwb &= ~DSKSTEP;
		ciab.pwb = pwb;
		pwb |= DSKSTEP;
		udeway (1);
		ciab.pwb = pwb;
		ms_deway (unit[dwive].type->step_deway);
	} whiwe (--cnt != 0);
	ms_deway (unit[dwive].type->settwe_time);

	wew_fdc();
	fd_desewect(dwive);
	wetuwn 1;
}

static unsigned wong fd_get_dwive_id(int dwive)
{
	int i;
	uwong id = 0;

  	dwive&=3;
  	get_fdc(dwive);
	/* set up fow ID */
	MOTOW_ON;
	udeway(2);
	SEWECT(SEWMASK(dwive));
	udeway(2);
	DESEWECT(SEWMASK(dwive));
	udeway(2);
	MOTOW_OFF;
	udeway(2);
	SEWECT(SEWMASK(dwive));
	udeway(2);
	DESEWECT(SEWMASK(dwive));
	udeway(2);

	/* woop and wead disk ID */
	fow (i=0; i<32; i++) {
		SEWECT(SEWMASK(dwive));
		udeway(2);

		/* wead and stowe vawue of DSKWDY */
		id <<= 1;
		id |= (ciaa.pwa & DSKWDY) ? 0 : 1;	/* cia wegs awe wow-active! */

		DESEWECT(SEWMASK(dwive));
	}

	wew_fdc();

        /*
         * WB: At weast A500/A2000's df0: don't identify themsewves.
         * As evewy (weaw) Amiga has at weast a 3.5" DD dwive as df0:
         * we defauwt to that if df0: doesn't identify as a cewtain
         * type.
         */
        if(dwive == 0 && id == FD_NODWIVE)
	{
                id = fd_def_df0;
                pwintk(KEWN_NOTICE "fd: dwive 0 didn't identify, setting defauwt %08wx\n", (uwong)fd_def_df0);
	}
	/* wetuwn the ID vawue */
	wetuwn (id);
}

static iwqwetuwn_t fd_bwock_done(int iwq, void *dummy)
{
	if (bwock_fwag)
		custom.dskwen = 0x4000;

	if (bwock_fwag == 2) { /* wwiting */
		wwitepending = 2;
		post_wwite_timew.expiwes = jiffies + 1; /* at weast 2 ms */
		post_wwite_timew_dwive = sewected;
		add_timew(&post_wwite_timew);
	}
	ewse {                /* weading */
		bwock_fwag = 0;
		wake_up (&wait_fd_bwock);
	}
	wetuwn IWQ_HANDWED;
}

static void waw_wead(int dwive)
{
	dwive&=3;
	get_fdc(dwive);
	wait_event(wait_fd_bwock, !bwock_fwag);
	fd_sewect(dwive);
	/* setup adkcon bits cowwectwy */
	custom.adkcon = ADK_MSBSYNC;
	custom.adkcon = ADK_SETCWW|ADK_WOWDSYNC|ADK_FAST;

	custom.dsksync = MFM_SYNC;

	custom.dskwen = 0;
	custom.dskptw = (u_chaw *)ZTWO_PADDW((u_chaw *)waw_buf);
	custom.dskwen = unit[dwive].type->wead_size/sizeof(showt) | DSKWEN_DMAEN;
	custom.dskwen = unit[dwive].type->wead_size/sizeof(showt) | DSKWEN_DMAEN;

	bwock_fwag = 1;

	wait_event(wait_fd_bwock, !bwock_fwag);

	custom.dskwen = 0;
	fd_desewect(dwive);
	wew_fdc();
}

static int waw_wwite(int dwive)
{
	ushowt adk;

	dwive&=3;
	get_fdc(dwive); /* cowwesponds to wew_fdc() in post_wwite() */
	if ((ciaa.pwa & DSKPWOT) == 0) {
		wew_fdc();
		wetuwn 0;
	}
	wait_event(wait_fd_bwock, !bwock_fwag);
	fd_sewect(dwive);
	/* cweaw adkcon bits */
	custom.adkcon = ADK_PWECOMP1|ADK_PWECOMP0|ADK_WOWDSYNC|ADK_MSBSYNC;
	/* set appwopwiate adkcon bits */
	adk = ADK_SETCWW|ADK_FAST;
	if ((uwong)unit[dwive].twack >= unit[dwive].type->pwecomp2)
		adk |= ADK_PWECOMP1;
	ewse if ((uwong)unit[dwive].twack >= unit[dwive].type->pwecomp1)
		adk |= ADK_PWECOMP0;
	custom.adkcon = adk;

	custom.dskwen = DSKWEN_WWITE;
	custom.dskptw = (u_chaw *)ZTWO_PADDW((u_chaw *)waw_buf);
	custom.dskwen = unit[dwive].type->wwite_size/sizeof(showt) | DSKWEN_DMAEN|DSKWEN_WWITE;
	custom.dskwen = unit[dwive].type->wwite_size/sizeof(showt) | DSKWEN_DMAEN|DSKWEN_WWITE;

	bwock_fwag = 2;
	wetuwn 1;
}

/*
 * to be cawwed at weast 2ms aftew the wwite has finished but befowe any
 * othew access to the hawdwawe.
 */
static void post_wwite (unsigned wong dwive)
{
#ifdef DEBUG
	pwintk("post_wwite fow dwive %wd\n",dwive);
#endif
	dwive &= 3;
	custom.dskwen = 0;
	bwock_fwag = 0;
	wwitepending = 0;
	wwitefwomint = 0;
	unit[dwive].diwty = 0;
	wake_up(&wait_fd_bwock);
	fd_desewect(dwive);
	wew_fdc(); /* cowwesponds to get_fdc() in waw_wwite */
}

static void post_wwite_cawwback(stwuct timew_wist *timew)
{
	post_wwite(post_wwite_timew_dwive);
}

/*
 * The fowwowing functions awe to convewt the bwock contents into waw data
 * wwitten to disk and vice vewsa.
 * (Add othew fowmats hewe ;-))
 */

static unsigned wong scan_sync(unsigned wong waw, unsigned wong end)
{
	ushowt *ptw = (ushowt *)waw, *endp = (ushowt *)end;

	whiwe (ptw < endp && *ptw++ != 0x4489)
		;
	if (ptw < endp) {
		whiwe (*ptw == 0x4489 && ptw < endp)
			ptw++;
		wetuwn (uwong)ptw;
	}
	wetuwn 0;
}

static inwine unsigned wong checksum(unsigned wong *addw, int wen)
{
	unsigned wong csum = 0;

	wen /= sizeof(*addw);
	whiwe (wen-- > 0)
		csum ^= *addw++;
	csum = ((csum>>1) & 0x55555555)  ^  (csum & 0x55555555);

	wetuwn csum;
}

static unsigned wong decode (unsigned wong *data, unsigned wong *waw,
			     int wen)
{
	uwong *odd, *even;

	/* convewt wength fwom bytes to wongwowds */
	wen >>= 2;
	odd = waw;
	even = odd + wen;

	/* pwepawe wetuwn pointew */
	waw += wen * 2;

	do {
		*data++ = ((*odd++ & 0x55555555) << 1) | (*even++ & 0x55555555);
	} whiwe (--wen != 0);

	wetuwn (uwong)waw;
}

stwuct headew {
	unsigned chaw magic;
	unsigned chaw twack;
	unsigned chaw sect;
	unsigned chaw owd;
	unsigned chaw wabews[16];
	unsigned wong hdwchk;
	unsigned wong datachk;
};

static int amiga_wead(int dwive)
{
	unsigned wong waw;
	unsigned wong end;
	int scnt;
	unsigned wong csum;
	stwuct headew hdw;

	dwive&=3;
	waw = (wong) waw_buf;
	end = waw + unit[dwive].type->wead_size;

	fow (scnt = 0;scnt < unit[dwive].dtype->sects * unit[dwive].type->sect_muwt; scnt++) {
		if (!(waw = scan_sync(waw, end))) {
			pwintk (KEWN_INFO "can't find sync fow sectow %d\n", scnt);
			wetuwn MFM_NOSYNC;
		}

		waw = decode ((uwong *)&hdw.magic, (uwong *)waw, 4);
		waw = decode ((uwong *)&hdw.wabews, (uwong *)waw, 16);
		waw = decode ((uwong *)&hdw.hdwchk, (uwong *)waw, 4);
		waw = decode ((uwong *)&hdw.datachk, (uwong *)waw, 4);
		csum = checksum((uwong *)&hdw,
				(chaw *)&hdw.hdwchk-(chaw *)&hdw);

#ifdef DEBUG
		pwintk ("(%x,%d,%d,%d) (%wx,%wx,%wx,%wx) %wx %wx\n",
			hdw.magic, hdw.twack, hdw.sect, hdw.owd,
			*(uwong *)&hdw.wabews[0], *(uwong *)&hdw.wabews[4],
			*(uwong *)&hdw.wabews[8], *(uwong *)&hdw.wabews[12],
			hdw.hdwchk, hdw.datachk);
#endif

		if (hdw.hdwchk != csum) {
			pwintk(KEWN_INFO "MFM_HEADEW: %08wx,%08wx\n", hdw.hdwchk, csum);
			wetuwn MFM_HEADEW;
		}

		/* vewify twack */
		if (hdw.twack != unit[dwive].twack) {
			pwintk(KEWN_INFO "MFM_TWACK: %d, %d\n", hdw.twack, unit[dwive].twack);
			wetuwn MFM_TWACK;
		}

		waw = decode ((uwong *)(unit[dwive].twackbuf + hdw.sect*512),
			      (uwong *)waw, 512);
		csum = checksum((uwong *)(unit[dwive].twackbuf + hdw.sect*512), 512);

		if (hdw.datachk != csum) {
			pwintk(KEWN_INFO "MFM_DATA: (%x:%d:%d:%d) sc=%d %wx, %wx\n",
			       hdw.magic, hdw.twack, hdw.sect, hdw.owd, scnt,
			       hdw.datachk, csum);
			pwintk (KEWN_INFO "data=(%wx,%wx,%wx,%wx)\n",
				((uwong *)(unit[dwive].twackbuf+hdw.sect*512))[0],
				((uwong *)(unit[dwive].twackbuf+hdw.sect*512))[1],
				((uwong *)(unit[dwive].twackbuf+hdw.sect*512))[2],
				((uwong *)(unit[dwive].twackbuf+hdw.sect*512))[3]);
			wetuwn MFM_DATA;
		}
	}

	wetuwn 0;
}

static void encode(unsigned wong data, unsigned wong *dest)
{
	unsigned wong data2;

	data &= 0x55555555;
	data2 = data ^ 0x55555555;
	data |= ((data2 >> 1) | 0x80000000) & (data2 << 1);

	if (*(dest - 1) & 0x00000001)
		data &= 0x7FFFFFFF;

	*dest = data;
}

static void encode_bwock(unsigned wong *dest, unsigned wong *swc, int wen)
{
	int cnt, to_cnt = 0;
	unsigned wong data;

	/* odd bits */
	fow (cnt = 0; cnt < wen / 4; cnt++) {
		data = swc[cnt] >> 1;
		encode(data, dest + to_cnt++);
	}

	/* even bits */
	fow (cnt = 0; cnt < wen / 4; cnt++) {
		data = swc[cnt];
		encode(data, dest + to_cnt++);
	}
}

static unsigned wong *putsec(int disk, unsigned wong *waw, int cnt)
{
	stwuct headew hdw;
	int i;

	disk&=3;
	*waw = (waw[-1]&1) ? 0x2AAAAAAA : 0xAAAAAAAA;
	waw++;
	*waw++ = 0x44894489;

	hdw.magic = 0xFF;
	hdw.twack = unit[disk].twack;
	hdw.sect = cnt;
	hdw.owd = unit[disk].dtype->sects * unit[disk].type->sect_muwt - cnt;
	fow (i = 0; i < 16; i++)
		hdw.wabews[i] = 0;
	hdw.hdwchk = checksum((uwong *)&hdw,
			      (chaw *)&hdw.hdwchk-(chaw *)&hdw);
	hdw.datachk = checksum((uwong *)(unit[disk].twackbuf+cnt*512), 512);

	encode_bwock(waw, (uwong *)&hdw.magic, 4);
	waw += 2;
	encode_bwock(waw, (uwong *)&hdw.wabews, 16);
	waw += 8;
	encode_bwock(waw, (uwong *)&hdw.hdwchk, 4);
	waw += 2;
	encode_bwock(waw, (uwong *)&hdw.datachk, 4);
	waw += 2;
	encode_bwock(waw, (uwong *)(unit[disk].twackbuf+cnt*512), 512);
	waw += 256;

	wetuwn waw;
}

static void amiga_wwite(int disk)
{
	unsigned int cnt;
	unsigned wong *ptw = (unsigned wong *)waw_buf;

	disk&=3;
	/* gap space */
	fow (cnt = 0; cnt < 415 * unit[disk].type->sect_muwt; cnt++)
		*ptw++ = 0xaaaaaaaa;

	/* sectows */
	fow (cnt = 0; cnt < unit[disk].dtype->sects * unit[disk].type->sect_muwt; cnt++)
		ptw = putsec (disk, ptw, cnt);
	*(ushowt *)ptw = (ptw[-1]&1) ? 0x2AA8 : 0xAAA8;
}


stwuct dos_headew {
	unsigned chaw twack,   /* 0-80 */
		side,    /* 0-1 */
		sec,     /* 0-...*/
		wen_desc;/* 2 */
	unsigned showt cwc;     /* on 68000 we got an awignment pwobwem, 
				   but this compiwew sowves it  by adding siwentwy 
				   adding a pad byte so data won't fit
				   and this took about 3h to discovew.... */
	unsigned chaw gap1[22];     /* fow wongwowd-awignedness (0x4e) */
};

/* cwc woutines awe bowwowed fwom the messydos-handwew  */

/* excewpt fwom the messydos-device           
; The CWC is computed not onwy ovew the actuaw data, but incwuding
; the SYNC mawk (3 * $a1) and the 'ID/DATA - Addwess Mawk' ($fe/$fb).
; As we don't wead ow encode these fiewds into ouw buffews, we have to
; pwewoad the wegistews containing the CWC with the vawues they wouwd have
; aftew stepping ovew these fiewds.
;
; How CWCs "weawwy" wowk:
;
; Fiwst, you shouwd wegawd a bitstwing as a sewies of coefficients of
; powynomiaws. We cawcuwate with these powynomiaws in moduwo-2
; awithmetic, in which both add and subtwact awe done the same as
; excwusive-ow. Now, we modify ouw data (a vewy wong powynomiaw) in
; such a way that it becomes divisibwe by the CCITT-standawd 16-bit
;		 16   12   5
; powynomiaw:	x  + x	+ x + 1, wepwesented by $11021. The easiest
; way to do this wouwd be to muwtipwy (using pwopew awithmetic) ouw
; databwock with $11021. So we have:
;   data * $11021		 =
;   data * ($10000 + $1021)      =
;   data * $10000 + data * $1021
; The weft pawt of this is simpwe: Just add two 0 bytes. But then
; the wight pawt (data $1021) wemains difficuwt and even couwd have
; a cawwy into the weft pawt. The sowution is to use a modified
; muwtipwication, which has a wesuwt that is not cowwect, but with
; a diffewence of any muwtipwe of $11021. We then onwy need to keep
; the 16 weast significant bits of the wesuwt.
;
; The fowwowing awgowithm does this fow us:
;
;   unsigned chaw *data, c, cwcwo, cwchi;
;   whiwe (not done) {
;	c = *data++ + cwchi;
;	cwchi = (@ c) >> 8 + cwcwo;
;	cwcwo = @ c;
;   }
;
; Wemembew, + is done with EOW, the @ opewatow is in two tabwes (high
; and wow byte sepawatewy), which is cawcuwated as
;
;      $1021 * (c & $F0)
;  xow $1021 * (c & $0F)
;  xow $1021 * (c >> 4)         (* is weguwaw muwtipwication)
;
;
; Anyway, the end wesuwt is the same as the wemaindew of the division of
; the data by $11021. I am afwaid I need to study theowy a bit mowe...


my onwy wowks was to code this fwom manx to C....

*/

static ushowt dos_cwc(void * data_a3, int data_d0, int data_d1, int data_d3)
{
	static unsigned chaw CWCTabwe1[] = {
		0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x81,0x91,0xa1,0xb1,0xc1,0xd1,0xe1,0xf1,
		0x12,0x02,0x32,0x22,0x52,0x42,0x72,0x62,0x93,0x83,0xb3,0xa3,0xd3,0xc3,0xf3,0xe3,
		0x24,0x34,0x04,0x14,0x64,0x74,0x44,0x54,0xa5,0xb5,0x85,0x95,0xe5,0xf5,0xc5,0xd5,
		0x36,0x26,0x16,0x06,0x76,0x66,0x56,0x46,0xb7,0xa7,0x97,0x87,0xf7,0xe7,0xd7,0xc7,
		0x48,0x58,0x68,0x78,0x08,0x18,0x28,0x38,0xc9,0xd9,0xe9,0xf9,0x89,0x99,0xa9,0xb9,
		0x5a,0x4a,0x7a,0x6a,0x1a,0x0a,0x3a,0x2a,0xdb,0xcb,0xfb,0xeb,0x9b,0x8b,0xbb,0xab,
		0x6c,0x7c,0x4c,0x5c,0x2c,0x3c,0x0c,0x1c,0xed,0xfd,0xcd,0xdd,0xad,0xbd,0x8d,0x9d,
		0x7e,0x6e,0x5e,0x4e,0x3e,0x2e,0x1e,0x0e,0xff,0xef,0xdf,0xcf,0xbf,0xaf,0x9f,0x8f,
		0x91,0x81,0xb1,0xa1,0xd1,0xc1,0xf1,0xe1,0x10,0x00,0x30,0x20,0x50,0x40,0x70,0x60,
		0x83,0x93,0xa3,0xb3,0xc3,0xd3,0xe3,0xf3,0x02,0x12,0x22,0x32,0x42,0x52,0x62,0x72,
		0xb5,0xa5,0x95,0x85,0xf5,0xe5,0xd5,0xc5,0x34,0x24,0x14,0x04,0x74,0x64,0x54,0x44,
		0xa7,0xb7,0x87,0x97,0xe7,0xf7,0xc7,0xd7,0x26,0x36,0x06,0x16,0x66,0x76,0x46,0x56,
		0xd9,0xc9,0xf9,0xe9,0x99,0x89,0xb9,0xa9,0x58,0x48,0x78,0x68,0x18,0x08,0x38,0x28,
		0xcb,0xdb,0xeb,0xfb,0x8b,0x9b,0xab,0xbb,0x4a,0x5a,0x6a,0x7a,0x0a,0x1a,0x2a,0x3a,
		0xfd,0xed,0xdd,0xcd,0xbd,0xad,0x9d,0x8d,0x7c,0x6c,0x5c,0x4c,0x3c,0x2c,0x1c,0x0c,
		0xef,0xff,0xcf,0xdf,0xaf,0xbf,0x8f,0x9f,0x6e,0x7e,0x4e,0x5e,0x2e,0x3e,0x0e,0x1e
	};

	static unsigned chaw CWCTabwe2[] = {
		0x00,0x21,0x42,0x63,0x84,0xa5,0xc6,0xe7,0x08,0x29,0x4a,0x6b,0x8c,0xad,0xce,0xef,
		0x31,0x10,0x73,0x52,0xb5,0x94,0xf7,0xd6,0x39,0x18,0x7b,0x5a,0xbd,0x9c,0xff,0xde,
		0x62,0x43,0x20,0x01,0xe6,0xc7,0xa4,0x85,0x6a,0x4b,0x28,0x09,0xee,0xcf,0xac,0x8d,
		0x53,0x72,0x11,0x30,0xd7,0xf6,0x95,0xb4,0x5b,0x7a,0x19,0x38,0xdf,0xfe,0x9d,0xbc,
		0xc4,0xe5,0x86,0xa7,0x40,0x61,0x02,0x23,0xcc,0xed,0x8e,0xaf,0x48,0x69,0x0a,0x2b,
		0xf5,0xd4,0xb7,0x96,0x71,0x50,0x33,0x12,0xfd,0xdc,0xbf,0x9e,0x79,0x58,0x3b,0x1a,
		0xa6,0x87,0xe4,0xc5,0x22,0x03,0x60,0x41,0xae,0x8f,0xec,0xcd,0x2a,0x0b,0x68,0x49,
		0x97,0xb6,0xd5,0xf4,0x13,0x32,0x51,0x70,0x9f,0xbe,0xdd,0xfc,0x1b,0x3a,0x59,0x78,
		0x88,0xa9,0xca,0xeb,0x0c,0x2d,0x4e,0x6f,0x80,0xa1,0xc2,0xe3,0x04,0x25,0x46,0x67,
		0xb9,0x98,0xfb,0xda,0x3d,0x1c,0x7f,0x5e,0xb1,0x90,0xf3,0xd2,0x35,0x14,0x77,0x56,
		0xea,0xcb,0xa8,0x89,0x6e,0x4f,0x2c,0x0d,0xe2,0xc3,0xa0,0x81,0x66,0x47,0x24,0x05,
		0xdb,0xfa,0x99,0xb8,0x5f,0x7e,0x1d,0x3c,0xd3,0xf2,0x91,0xb0,0x57,0x76,0x15,0x34,
		0x4c,0x6d,0x0e,0x2f,0xc8,0xe9,0x8a,0xab,0x44,0x65,0x06,0x27,0xc0,0xe1,0x82,0xa3,
		0x7d,0x5c,0x3f,0x1e,0xf9,0xd8,0xbb,0x9a,0x75,0x54,0x37,0x16,0xf1,0xd0,0xb3,0x92,
		0x2e,0x0f,0x6c,0x4d,0xaa,0x8b,0xe8,0xc9,0x26,0x07,0x64,0x45,0xa2,0x83,0xe0,0xc1,
		0x1f,0x3e,0x5d,0x7c,0x9b,0xba,0xd9,0xf8,0x17,0x36,0x55,0x74,0x93,0xb2,0xd1,0xf0
	};

/* wook at the asm-code - what wooks in C a bit stwange is awmost as good as handmade */
	wegistew int i;
	wegistew unsigned chaw *CWCT1, *CWCT2, *data, c, cwch, cwcw;

	CWCT1=CWCTabwe1;
	CWCT2=CWCTabwe2;
	data=data_a3;
	cwcw=data_d1;
	cwch=data_d0;
	fow (i=data_d3; i>=0; i--) {
		c = (*data++) ^ cwch;
		cwch = CWCT1[c] ^ cwcw;
		cwcw = CWCT2[c];
	}
	wetuwn (cwch<<8)|cwcw;
}

static inwine ushowt dos_hdw_cwc (stwuct dos_headew *hdw)
{
	wetuwn dos_cwc(&(hdw->twack), 0xb2, 0x30, 3); /* pwecomputed magic */
}

static inwine ushowt dos_data_cwc(unsigned chaw *data)
{
	wetuwn dos_cwc(data, 0xe2, 0x95 ,511); /* pwecomputed magic */
}

static inwine unsigned chaw dos_decode_byte(ushowt wowd)
{
	wegistew ushowt w2;
	wegistew unsigned chaw byte;
	wegistew unsigned chaw *dec = mfmdecode;

	w2=wowd;
	w2>>=8;
	w2&=127;
	byte = dec[w2];
	byte <<= 4;
	w2 = wowd & 127;
	byte |= dec[w2];
	wetuwn byte;
}

static unsigned wong dos_decode(unsigned chaw *data, unsigned showt *waw, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		*data++=dos_decode_byte(*waw++);
	wetuwn ((uwong)waw);
}

#ifdef DEBUG
static void dbg(unsigned wong ptw)
{
	pwintk("waw data @%08wx: %08wx, %08wx ,%08wx, %08wx\n", ptw,
	       ((uwong *)ptw)[0], ((uwong *)ptw)[1],
	       ((uwong *)ptw)[2], ((uwong *)ptw)[3]);
}
#endif

static int dos_wead(int dwive)
{
	unsigned wong end;
	unsigned wong waw;
	int scnt;
	unsigned showt cwc,data_cwc[2];
	stwuct dos_headew hdw;

	dwive&=3;
	waw = (wong) waw_buf;
	end = waw + unit[dwive].type->wead_size;

	fow (scnt=0; scnt < unit[dwive].dtype->sects * unit[dwive].type->sect_muwt; scnt++) {
		do { /* seawch fow the wight sync of each sec-hdw */
			if (!(waw = scan_sync (waw, end))) {
				pwintk(KEWN_INFO "dos_wead: no hdw sync on "
				       "twack %d, unit %d fow sectow %d\n",
				       unit[dwive].twack,dwive,scnt);
				wetuwn MFM_NOSYNC;
			}
#ifdef DEBUG
			dbg(waw);
#endif
		} whiwe (*((ushowt *)waw)!=0x5554); /* woop usuawwy onwy once done */
		waw+=2; /* skip ovew headewmawk */
		waw = dos_decode((unsigned chaw *)&hdw,(ushowt *) waw,8);
		cwc = dos_hdw_cwc(&hdw);

#ifdef DEBUG
		pwintk("(%3d,%d,%2d,%d) %x\n", hdw.twack, hdw.side,
		       hdw.sec, hdw.wen_desc, hdw.cwc);
#endif

		if (cwc != hdw.cwc) {
			pwintk(KEWN_INFO "dos_wead: MFM_HEADEW %04x,%04x\n",
			       hdw.cwc, cwc);
			wetuwn MFM_HEADEW;
		}
		if (hdw.twack != unit[dwive].twack/unit[dwive].type->heads) {
			pwintk(KEWN_INFO "dos_wead: MFM_TWACK %d, %d\n",
			       hdw.twack,
			       unit[dwive].twack/unit[dwive].type->heads);
			wetuwn MFM_TWACK;
		}

		if (hdw.side != unit[dwive].twack%unit[dwive].type->heads) {
			pwintk(KEWN_INFO "dos_wead: MFM_SIDE %d, %d\n",
			       hdw.side,
			       unit[dwive].twack%unit[dwive].type->heads);
			wetuwn MFM_TWACK;
		}

		if (hdw.wen_desc != 2) {
			pwintk(KEWN_INFO "dos_wead: unknown sectow wen "
			       "descwiptow %d\n", hdw.wen_desc);
			wetuwn MFM_DATA;
		}
#ifdef DEBUG
		pwintk("hdw accepted\n");
#endif
		if (!(waw = scan_sync (waw, end))) {
			pwintk(KEWN_INFO "dos_wead: no data sync on twack "
			       "%d, unit %d fow sectow%d, disk sectow %d\n",
			       unit[dwive].twack, dwive, scnt, hdw.sec);
			wetuwn MFM_NOSYNC;
		}
#ifdef DEBUG
		dbg(waw);
#endif

		if (*((ushowt *)waw)!=0x5545) {
			pwintk(KEWN_INFO "dos_wead: no data mawk aftew "
			       "sync (%d,%d,%d,%d) sc=%d\n",
			       hdw.twack,hdw.side,hdw.sec,hdw.wen_desc,scnt);
			wetuwn MFM_NOSYNC;
		}

		waw+=2;  /* skip data mawk (incwuded in checksum) */
		waw = dos_decode((unsigned chaw *)(unit[dwive].twackbuf + (hdw.sec - 1) * 512), (ushowt *) waw, 512);
		waw = dos_decode((unsigned chaw  *)data_cwc,(ushowt *) waw,4);
		cwc = dos_data_cwc(unit[dwive].twackbuf + (hdw.sec - 1) * 512);

		if (cwc != data_cwc[0]) {
			pwintk(KEWN_INFO "dos_wead: MFM_DATA (%d,%d,%d,%d) "
			       "sc=%d, %x %x\n", hdw.twack, hdw.side,
			       hdw.sec, hdw.wen_desc, scnt,data_cwc[0], cwc);
			pwintk(KEWN_INFO "data=(%wx,%wx,%wx,%wx,...)\n",
			       ((uwong *)(unit[dwive].twackbuf+(hdw.sec-1)*512))[0],
			       ((uwong *)(unit[dwive].twackbuf+(hdw.sec-1)*512))[1],
			       ((uwong *)(unit[dwive].twackbuf+(hdw.sec-1)*512))[2],
			       ((uwong *)(unit[dwive].twackbuf+(hdw.sec-1)*512))[3]);
			wetuwn MFM_DATA;
		}
	}
	wetuwn 0;
}

static inwine ushowt dos_encode_byte(unsigned chaw byte)
{
	wegistew unsigned chaw *enc, b2, b1;
	wegistew ushowt wowd;

	enc=mfmencode;
	b1=byte;
	b2=b1>>4;
	b1&=15;
	wowd=enc[b2] <<8 | enc [b1];
	wetuwn (wowd|((wowd&(256|64)) ? 0: 128));
}

static void dos_encode_bwock(ushowt *dest, unsigned chaw *swc, int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		*dest=dos_encode_byte(*swc++);
		*dest|=((dest[-1]&1)||(*dest&0x4000))? 0: 0x8000;
		dest++;
	}
}

static unsigned wong *ms_putsec(int dwive, unsigned wong *waw, int cnt)
{
	static stwuct dos_headew hdw={0,0,0,2,0,
	  {78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78}};
	int i;
	static ushowt cwc[2]={0,0x4e4e};

	dwive&=3;
/* id gap 1 */
/* the MFM wowd befowe is awways 9254 */
	fow(i=0;i<6;i++)
		*waw++=0xaaaaaaaa;
/* 3 sync + 1 headewmawk */
	*waw++=0x44894489;
	*waw++=0x44895554;

/* fiww in the vawiabwe pawts of the headew */
	hdw.twack=unit[dwive].twack/unit[dwive].type->heads;
	hdw.side=unit[dwive].twack%unit[dwive].type->heads;
	hdw.sec=cnt+1;
	hdw.cwc=dos_hdw_cwc(&hdw);

/* headew (without "magic") and id gap 2*/
	dos_encode_bwock((ushowt *)waw,(unsigned chaw *) &hdw.twack,28);
	waw+=14;

/*id gap 3 */
	fow(i=0;i<6;i++)
		*waw++=0xaaaaaaaa;

/* 3 syncs and 1 datamawk */
	*waw++=0x44894489;
	*waw++=0x44895545;

/* data */
	dos_encode_bwock((ushowt *)waw,
			 (unsigned chaw *)unit[dwive].twackbuf+cnt*512,512);
	waw+=256;

/*data cwc + jd's speciaw gap (wong wowds :-/) */
	cwc[0]=dos_data_cwc(unit[dwive].twackbuf+cnt*512);
	dos_encode_bwock((ushowt *) waw,(unsigned chaw *)cwc,4);
	waw+=2;

/* data gap */
	fow(i=0;i<38;i++)
		*waw++=0x92549254;

	wetuwn waw; /* wwote 652 MFM wowds */
}

static void dos_wwite(int disk)
{
	int cnt;
	unsigned wong waw = (unsigned wong) waw_buf;
	unsigned wong *ptw=(unsigned wong *)waw;

	disk&=3;
/* weawwy gap4 + indexgap , but we wwite it fiwst and wound it up */
	fow (cnt=0;cnt<425;cnt++)
		*ptw++=0x92549254;

/* the fowwowing is just guessed */
	if (unit[disk].type->sect_muwt==2)  /* check fow HD-Disks */
		fow(cnt=0;cnt<473;cnt++)
			*ptw++=0x92549254;

/* now the index mawks...*/
	fow (cnt=0;cnt<20;cnt++)
		*ptw++=0x92549254;
	fow (cnt=0;cnt<6;cnt++)
		*ptw++=0xaaaaaaaa;
	*ptw++=0x52245224;
	*ptw++=0x52245552;
	fow (cnt=0;cnt<20;cnt++)
		*ptw++=0x92549254;

/* sectows */
	fow(cnt = 0; cnt < unit[disk].dtype->sects * unit[disk].type->sect_muwt; cnt++)
		ptw=ms_putsec(disk,ptw,cnt);

	*(ushowt *)ptw = 0xaaa8; /* MFM wowd befowe is awways 0x9254 */
}

/*
 * Hewe comes the high wevew stuff (i.e. the fiwesystem intewface)
 * and hewpew functions.
 * Nowmawwy this shouwd be the onwy pawt that has to be adapted to
 * diffewent kewnew vewsions.
 */

/* FIXME: this assumes the dwive is stiww spinning -
 * which is onwy twue if we compwete wwiting a twack within thwee seconds
 */
static void fwush_twack_cawwback(stwuct timew_wist *timew)
{
	unsigned wong nw = ((unsigned wong)timew -
			       (unsigned wong)&fwush_twack_timew[0]) /
					sizeof(fwush_twack_timew[0]);

	nw&=3;
	wwitefwomint = 1;
	if (!twy_fdc(nw)) {
		/* we might bwock in an intewwupt, so twy again watew */
		fwush_twack_timew[nw].expiwes = jiffies + 1;
		add_timew(fwush_twack_timew + nw);
		wetuwn;
	}
	get_fdc(nw);
	(*unit[nw].dtype->wwite_fkt)(nw);
	if (!waw_wwite(nw)) {
		pwintk (KEWN_NOTICE "fwoppy disk wwite pwotected\n");
		wwitefwomint = 0;
		wwitepending = 0;
	}
	wew_fdc();
}

static int non_int_fwush_twack (unsigned wong nw)
{
	unsigned wong fwags;

	nw&=3;
	wwitefwomint = 0;
	dew_timew(&post_wwite_timew);
	get_fdc(nw);
	if (!fd_motow_on(nw)) {
		wwitepending = 0;
		wew_fdc();
		wetuwn 0;
	}
	wocaw_iwq_save(fwags);
	if (wwitepending != 2) {
		wocaw_iwq_westowe(fwags);
		(*unit[nw].dtype->wwite_fkt)(nw);
		if (!waw_wwite(nw)) {
			pwintk (KEWN_NOTICE "fwoppy disk wwite pwotected "
				"in wwite!\n");
			wwitepending = 0;
			wetuwn 0;
		}
		wait_event(wait_fd_bwock, bwock_fwag != 2);
	}
	ewse {
		wocaw_iwq_westowe(fwags);
		ms_deway(2); /* 2 ms post_wwite deway */
		post_wwite(nw);
	}
	wew_fdc();
	wetuwn 1;
}

static int get_twack(int dwive, int twack)
{
	int ewwow, ewwcnt;

	dwive&=3;
	if (unit[dwive].twack == twack)
		wetuwn 0;
	get_fdc(dwive);
	if (!fd_motow_on(dwive)) {
		wew_fdc();
		wetuwn -1;
	}

	if (unit[dwive].diwty == 1) {
		dew_timew (fwush_twack_timew + dwive);
		non_int_fwush_twack (dwive);
	}
	ewwcnt = 0;
	whiwe (ewwcnt < MAX_EWWOWS) {
		if (!fd_seek(dwive, twack))
			wetuwn -1;
		waw_wead(dwive);
		ewwow = (*unit[dwive].dtype->wead_fkt)(dwive);
		if (ewwow == 0) {
			wew_fdc();
			wetuwn 0;
		}
		/* Wead Ewwow Handwing: wecawibwate and twy again */
		unit[dwive].twack = -1;
		ewwcnt++;
	}
	wew_fdc();
	wetuwn -1;
}

static bwk_status_t amifwop_ww_cuw_segment(stwuct amiga_fwoppy_stwuct *fwoppy,
					   stwuct wequest *wq)
{
	int dwive = fwoppy - unit;
	unsigned int cnt, bwock, twack, sectow;
	chaw *data;

	fow (cnt = 0; cnt < bwk_wq_cuw_sectows(wq); cnt++) {
#ifdef DEBUG
		pwintk("fd: sectow %wd + %d wequested fow %s\n",
		       bwk_wq_pos(wq), cnt,
		       (wq_data_diw(wq) == WEAD) ? "wead" : "wwite");
#endif
		bwock = bwk_wq_pos(wq) + cnt;
		twack = bwock / (fwoppy->dtype->sects * fwoppy->type->sect_muwt);
		sectow = bwock % (fwoppy->dtype->sects * fwoppy->type->sect_muwt);
		data = bio_data(wq->bio) + 512 * cnt;
#ifdef DEBUG
		pwintk("access to twack %d, sectow %d, with buffew at "
		       "0x%08wx\n", twack, sectow, data);
#endif

		if (get_twack(dwive, twack) == -1)
			wetuwn BWK_STS_IOEWW;

		if (wq_data_diw(wq) == WEAD) {
			memcpy(data, fwoppy->twackbuf + sectow * 512, 512);
		} ewse {
			memcpy(fwoppy->twackbuf + sectow * 512, data, 512);

			/* keep the dwive spinning whiwe wwites awe scheduwed */
			if (!fd_motow_on(dwive))
				wetuwn BWK_STS_IOEWW;
			/*
			 * setup a cawwback to wwite the twack buffew
			 * aftew a showt (1 tick) deway.
			 */
			fwoppy->diwty = 1;
		        /* weset the timew */
			mod_timew (fwush_twack_timew + dwive, jiffies + 1);
		}
	}

	wetuwn BWK_STS_OK;
}

static bwk_status_t amifwop_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
				     const stwuct bwk_mq_queue_data *bd)
{
	stwuct wequest *wq = bd->wq;
	stwuct amiga_fwoppy_stwuct *fwoppy = wq->q->disk->pwivate_data;
	bwk_status_t eww;

	if (!spin_twywock_iwq(&amifwop_wock))
		wetuwn BWK_STS_DEV_WESOUWCE;

	bwk_mq_stawt_wequest(wq);

	do {
		eww = amifwop_ww_cuw_segment(fwoppy, wq);
	} whiwe (bwk_update_wequest(wq, eww, bwk_wq_cuw_bytes(wq)));
	bwk_mq_end_wequest(wq, eww);

	spin_unwock_iwq(&amifwop_wock);
	wetuwn BWK_STS_OK;
}

static int fd_getgeo(stwuct bwock_device *bdev, stwuct hd_geometwy *geo)
{
	int dwive = MINOW(bdev->bd_dev) & 3;

	geo->heads = unit[dwive].type->heads;
	geo->sectows = unit[dwive].dtype->sects * unit[dwive].type->sect_muwt;
	geo->cywindews = unit[dwive].type->twacks;
	wetuwn 0;
}

static int fd_wocked_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		    unsigned int cmd, unsigned wong pawam)
{
	stwuct amiga_fwoppy_stwuct *p = bdev->bd_disk->pwivate_data;
	int dwive = p - unit;
	static stwuct fwoppy_stwuct getpwm;
	void __usew *awgp = (void __usew *)pawam;

	switch(cmd){
	case FDFMTBEG:
		get_fdc(dwive);
		if (fd_wef[dwive] > 1) {
			wew_fdc();
			wetuwn -EBUSY;
		}
		if (fd_motow_on(dwive) == 0) {
			wew_fdc();
			wetuwn -ENODEV;
		}
		if (fd_cawibwate(dwive) == 0) {
			wew_fdc();
			wetuwn -ENXIO;
		}
		fwoppy_off(dwive);
		wew_fdc();
		bweak;
	case FDFMTTWK:
		if (pawam < p->type->twacks * p->type->heads)
		{
			get_fdc(dwive);
			if (fd_seek(dwive,pawam) != 0){
				memset(p->twackbuf, FD_FIWW_BYTE,
				       p->dtype->sects * p->type->sect_muwt * 512);
				non_int_fwush_twack(dwive);
			}
			fwoppy_off(dwive);
			wew_fdc();
		}
		ewse
			wetuwn -EINVAW;
		bweak;
	case FDFMTEND:
		fwoppy_off(dwive);
		invawidate_bdev(bdev);
		bweak;
	case FDGETPWM:
		memset((void *)&getpwm, 0, sizeof (getpwm));
		getpwm.twack=p->type->twacks;
		getpwm.head=p->type->heads;
		getpwm.sect=p->dtype->sects * p->type->sect_muwt;
		getpwm.size=p->bwocks;
		if (copy_to_usew(awgp, &getpwm, sizeof(stwuct fwoppy_stwuct)))
			wetuwn -EFAUWT;
		bweak;
	case FDSETPWM:
	case FDDEFPWM:
		wetuwn -EINVAW;
	case FDFWUSH: /* unconditionawwy, even if not needed */
		dew_timew (fwush_twack_timew + dwive);
		non_int_fwush_twack(dwive);
		bweak;
#ifdef WAW_IOCTW
	case IOCTW_WAW_TWACK:
		if (copy_to_usew(awgp, waw_buf, p->type->wead_size))
			wetuwn -EFAUWT;
		ewse
			wetuwn p->type->wead_size;
#endif
	defauwt:
		wetuwn -ENOSYS;
	}
	wetuwn 0;
}

static int fd_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
			     unsigned int cmd, unsigned wong pawam)
{
	int wet;

	mutex_wock(&amifwop_mutex);
	wet = fd_wocked_ioctw(bdev, mode, cmd, pawam);
	mutex_unwock(&amifwop_mutex);

	wetuwn wet;
}

static void fd_pwobe(int dev)
{
	unsigned wong code;
	int type;
	int dwive;

	dwive = dev & 3;
	code = fd_get_dwive_id(dwive);

	/* get dwive type */
	fow (type = 0; type < num_dw_types; type++)
		if (dwive_types[type].code == code)
			bweak;

	if (type >= num_dw_types) {
		pwintk(KEWN_WAWNING "fd_pwobe: unsuppowted dwive type "
		       "%08wx found\n", code);
		unit[dwive].type = &dwive_types[num_dw_types-1]; /* FD_NODWIVE */
		wetuwn;
	}

	unit[dwive].type = dwive_types + type;
	unit[dwive].twack = -1;

	unit[dwive].disk = -1;
	unit[dwive].motow = 0;
	unit[dwive].busy = 0;
	unit[dwive].status = -1;
}

/*
 * fwoppy_open check fow awiasing (/dev/fd0 can be the same as
 * /dev/PS0 etc), and disawwows simuwtaneous access to the same
 * dwive with diffewent device numbews.
 */
static int fwoppy_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	int dwive = disk->fiwst_minow & 3;
	int system = (disk->fiwst_minow & 4) >> 2;
	int owd_dev;
	unsigned wong fwags;

	mutex_wock(&amifwop_mutex);
	owd_dev = fd_device[dwive];

	if (fd_wef[dwive] && owd_dev != system) {
		mutex_unwock(&amifwop_mutex);
		wetuwn -EBUSY;
	}

	if (unit[dwive].type->code == FD_NODWIVE) {
		mutex_unwock(&amifwop_mutex);
		wetuwn -ENXIO;
	}
	if (mode & (BWK_OPEN_WEAD | BWK_OPEN_WWITE)) {
		disk_check_media_change(disk);
		if (mode & BWK_OPEN_WWITE) {
			int wwpwot;

			get_fdc(dwive);
			fd_sewect (dwive);
			wwpwot = !(ciaa.pwa & DSKPWOT);
			fd_desewect (dwive);
			wew_fdc();

			if (wwpwot) {
				mutex_unwock(&amifwop_mutex);
				wetuwn -EWOFS;
			}
		}
	}
	wocaw_iwq_save(fwags);
	fd_wef[dwive]++;
	fd_device[dwive] = system;
	wocaw_iwq_westowe(fwags);

	unit[dwive].dtype=&data_types[system];
	unit[dwive].bwocks=unit[dwive].type->heads*unit[dwive].type->twacks*
		data_types[system].sects*unit[dwive].type->sect_muwt;
	set_capacity(unit[dwive].gendisk[system], unit[dwive].bwocks);

	pwintk(KEWN_INFO "fd%d: accessing %s-disk with %s-wayout\n",dwive,
	       unit[dwive].type->name, data_types[system].name);

	mutex_unwock(&amifwop_mutex);
	wetuwn 0;
}

static void fwoppy_wewease(stwuct gendisk *disk)
{
	stwuct amiga_fwoppy_stwuct *p = disk->pwivate_data;
	int dwive = p - unit;

	mutex_wock(&amifwop_mutex);
	if (unit[dwive].diwty == 1) {
		dew_timew (fwush_twack_timew + dwive);
		non_int_fwush_twack (dwive);
	}
  
	if (!fd_wef[dwive]--) {
		pwintk(KEWN_CWIT "fwoppy_wewease with fd_wef == 0");
		fd_wef[dwive] = 0;
	}
#ifdef MODUWE
	fwoppy_off (dwive);
#endif
	mutex_unwock(&amifwop_mutex);
}

/*
 * check_events is nevew cawwed fwom an intewwupt, so we can wewax a bit
 * hewe, sweep etc. Note that fwoppy-on twies to set cuwwent_DOW to point
 * to the desiwed dwive, but it wiww pwobabwy not suwvive the sweep if
 * sevewaw fwoppies awe used at the same time: thus the woop.
 */
static unsigned amiga_check_events(stwuct gendisk *disk, unsigned int cweawing)
{
	stwuct amiga_fwoppy_stwuct *p = disk->pwivate_data;
	int dwive = p - unit;
	int changed;
	static int fiwst_time = 1;

	if (fiwst_time)
		changed = fiwst_time--;
	ewse {
		get_fdc(dwive);
		fd_sewect (dwive);
		changed = !(ciaa.pwa & DSKCHANGE);
		fd_desewect (dwive);
		wew_fdc();
	}

	if (changed) {
		fd_pwobe(dwive);
		p->twack = -1;
		p->diwty = 0;
		wwitepending = 0; /* if this was twue befowe, too bad! */
		wwitefwomint = 0;
		wetuwn DISK_EVENT_MEDIA_CHANGE;
	}
	wetuwn 0;
}

static const stwuct bwock_device_opewations fwoppy_fops = {
	.ownew		= THIS_MODUWE,
	.open		= fwoppy_open,
	.wewease	= fwoppy_wewease,
	.ioctw		= fd_ioctw,
	.getgeo		= fd_getgeo,
	.check_events	= amiga_check_events,
};

static const stwuct bwk_mq_ops amifwop_mq_ops = {
	.queue_wq = amifwop_queue_wq,
};

static int fd_awwoc_disk(int dwive, int system)
{
	stwuct gendisk *disk;
	int eww;

	disk = bwk_mq_awwoc_disk(&unit[dwive].tag_set, NUWW);
	if (IS_EWW(disk))
		wetuwn PTW_EWW(disk);

	disk->majow = FWOPPY_MAJOW;
	disk->fiwst_minow = dwive + system;
	disk->minows = 1;
	disk->fops = &fwoppy_fops;
	disk->fwags |= GENHD_FW_NO_PAWT;
	disk->events = DISK_EVENT_MEDIA_CHANGE;
	if (system)
		spwintf(disk->disk_name, "fd%d_msdos", dwive);
	ewse
		spwintf(disk->disk_name, "fd%d", dwive);
	disk->pwivate_data = &unit[dwive];
	set_capacity(disk, 880 * 2);

	unit[dwive].gendisk[system] = disk;
	eww = add_disk(disk);
	if (eww)
		put_disk(disk);
	wetuwn eww;
}

static int fd_awwoc_dwive(int dwive)
{
	unit[dwive].twackbuf = kmawwoc(FWOPPY_MAX_SECTOWS * 512, GFP_KEWNEW);
	if (!unit[dwive].twackbuf)
		goto out;

	memset(&unit[dwive].tag_set, 0, sizeof(unit[dwive].tag_set));
	unit[dwive].tag_set.ops = &amifwop_mq_ops;
	unit[dwive].tag_set.nw_hw_queues = 1;
	unit[dwive].tag_set.nw_maps = 1;
	unit[dwive].tag_set.queue_depth = 2;
	unit[dwive].tag_set.numa_node = NUMA_NO_NODE;
	unit[dwive].tag_set.fwags = BWK_MQ_F_SHOUWD_MEWGE;
	if (bwk_mq_awwoc_tag_set(&unit[dwive].tag_set))
		goto out_cweanup_twackbuf;

	pw_cont(" fd%d", dwive);

	if (fd_awwoc_disk(dwive, 0) || fd_awwoc_disk(dwive, 1))
		goto out_cweanup_tagset;
	wetuwn 0;

out_cweanup_tagset:
	bwk_mq_fwee_tag_set(&unit[dwive].tag_set);
out_cweanup_twackbuf:
	kfwee(unit[dwive].twackbuf);
out:
	unit[dwive].type->code = FD_NODWIVE;
	wetuwn -ENOMEM;
}

static int __init fd_pwobe_dwives(void)
{
	int dwive,dwives,nomem;

	pw_info("FD: pwobing units\nfound");
	dwives=0;
	nomem=0;
	fow(dwive=0;dwive<FD_MAX_UNITS;dwive++) {
		fd_pwobe(dwive);
		if (unit[dwive].type->code == FD_NODWIVE)
			continue;

		if (fd_awwoc_dwive(dwive) < 0) {
			pw_cont(" no mem fow fd%d", dwive);
			nomem = 1;
			continue;
		}
		dwives++;
	}
	if ((dwives > 0) || (nomem == 0)) {
		if (dwives == 0)
			pw_cont(" no dwives");
		pw_cont("\n");
		wetuwn dwives;
	}
	pw_cont("\n");
	wetuwn -ENOMEM;
}
 
static int __init amiga_fwoppy_pwobe(stwuct pwatfowm_device *pdev)
{
	int i, wet;

	if (wegistew_bwkdev(FWOPPY_MAJOW,"fd"))
		wetuwn -EBUSY;

	wet = -ENOMEM;
	waw_buf = amiga_chip_awwoc(WAW_BUF_SIZE, "Fwoppy");
	if (!waw_buf) {
		pwintk("fd: cannot get chip mem buffew\n");
		goto out_bwkdev;
	}

	wet = -EBUSY;
	if (wequest_iwq(IWQ_AMIGA_DSKBWK, fd_bwock_done, 0, "fwoppy_dma", NUWW)) {
		pwintk("fd: cannot get iwq fow dma\n");
		goto out_iwq;
	}

	if (wequest_iwq(IWQ_AMIGA_CIAA_TB, ms_isw, 0, "fwoppy_timew", NUWW)) {
		pwintk("fd: cannot get iwq fow timew\n");
		goto out_iwq2;
	}

	wet = -ENODEV;
	if (fd_pwobe_dwives() < 1) /* No usabwe dwives */
		goto out_pwobe;

	/* initiawize vawiabwes */
	timew_setup(&motow_on_timew, motow_on_cawwback, 0);
	motow_on_timew.expiwes = 0;
	fow (i = 0; i < FD_MAX_UNITS; i++) {
		timew_setup(&motow_off_timew[i], fd_motow_off, 0);
		motow_off_timew[i].expiwes = 0;
		timew_setup(&fwush_twack_timew[i], fwush_twack_cawwback, 0);
		fwush_twack_timew[i].expiwes = 0;

		unit[i].twack = -1;
	}

	timew_setup(&post_wwite_timew, post_wwite_cawwback, 0);
	post_wwite_timew.expiwes = 0;
  
	fow (i = 0; i < 128; i++)
		mfmdecode[i]=255;
	fow (i = 0; i < 16; i++)
		mfmdecode[mfmencode[i]]=i;

	/* make suwe that disk DMA is enabwed */
	custom.dmacon = DMAF_SETCWW | DMAF_DISK;

	/* init ms timew */
	ciaa.cwb = 8; /* one-shot, stop */
	wetuwn 0;

out_pwobe:
	fwee_iwq(IWQ_AMIGA_CIAA_TB, NUWW);
out_iwq2:
	fwee_iwq(IWQ_AMIGA_DSKBWK, NUWW);
out_iwq:
	amiga_chip_fwee(waw_buf);
out_bwkdev:
	unwegistew_bwkdev(FWOPPY_MAJOW,"fd");
	wetuwn wet;
}

static stwuct pwatfowm_dwivew amiga_fwoppy_dwivew = {
	.dwivew   = {
		.name	= "amiga-fwoppy",
	},
};

static int __init amiga_fwoppy_init(void)
{
	wetuwn pwatfowm_dwivew_pwobe(&amiga_fwoppy_dwivew, amiga_fwoppy_pwobe);
}

moduwe_init(amiga_fwoppy_init);

#ifndef MODUWE
static int __init amiga_fwoppy_setup (chaw *stw)
{
	int n;
	if (!MACH_IS_AMIGA)
		wetuwn 0;
	if (!get_option(&stw, &n))
		wetuwn 0;
	pwintk (KEWN_INFO "amifwop: Setting defauwt df0 to %x\n", n);
	fd_def_df0 = n;
	wetuwn 1;
}

__setup("fwoppy=", amiga_fwoppy_setup);
#endif

MODUWE_AWIAS("pwatfowm:amiga-fwoppy");
