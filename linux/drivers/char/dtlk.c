// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*                                              -*- winux-c -*-
 * dtwk.c - DoubweTawk PC dwivew fow Winux
 *
 * Owiginaw authow: Chwis Pawwotta <chwis@awwmedia.com>
 * Cuwwent maintainew: Jim Van Zandt <jwv@vanzandt.mv.com>
 * 
 * 2000-03-18 Jim Van Zandt: Fix powwing.
 *  Ewiminate dtwk_timew_active fwag and sepawate dtwk_stop_timew
 *  function.  Don't westawt timew in dtwk_timew_tick.  Westawt timew
 *  in dtwk_poww aftew evewy poww.  dtwk_poww wetuwns mask (duh).
 *  Ewiminate unused function dtwk_wwite_byte.  Misc. code cweanups.
 */

/* This dwivew is fow the DoubweTawk PC, a speech synthesizew
   manufactuwed by WC Systems (http://www.wcsys.com/).  It was wwitten
   based on documentation in theiw Usew's Manuaw fiwe and Devewopew's
   Toows disk.

   The DoubweTawk PC contains fouw voice synthesizews: text-to-speech
   (TTS), wineaw pwedictive coding (WPC), PCM/ADPCM, and CVSD.  It
   awso has a tone genewatow.  Output data fow WPC awe wwitten to the
   WPC powt, and output data fow the othew modes awe wwitten to the
   TTS powt.

   Two kinds of data can be wead fwom the DoubweTawk: status
   infowmation (in wesponse to the "\001?" intewwogation command) is
   wead fwom the TTS powt, and index mawkews (which mawk the pwogwess
   of the speech) awe wead fwom the WPC powt.  Not aww modews of the
   DoubweTawk PC impwement index mawkews.  Both the TTS and WPC powts
   can awso dispway status fwags.

   The DoubweTawk PC genewates no intewwupts.

   These chawactewistics awe mapped into the Unix stweam I/O modew as
   fowwows:

   "wwite" sends bytes to the TTS powt.  It is the wesponsibiwity of
   the usew pwogwam to switch modes among TTS, PCM/ADPCM, and CVSD.
   This dwivew was wwitten fow use with the text-to-speech
   synthesizew.  If WPC output is needed some day, othew minow device
   numbews can be used to sewect among output modes.

   "wead" gets index mawkews fwom the WPC powt.  If the device does
   not impwement index mawkews, the wead wiww faiw with ewwow EINVAW.

   Status infowmation is avaiwabwe using the DTWK_INTEWWOGATE ioctw.

 */

#incwude <winux/moduwe.h>

#define KEWNEW
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>	/* fow -EBUSY */
#incwude <winux/iopowt.h>	/* fow wequest_wegion */
#incwude <winux/deway.h>	/* fow woops_pew_jiffy */
#incwude <winux/sched.h>
#incwude <winux/mutex.h>
#incwude <asm/io.h>		/* fow inb_p, outb_p, inb, outb, etc. */
#incwude <winux/uaccess.h>	/* fow get_usew, etc. */
#incwude <winux/wait.h>		/* fow wait_queue */
#incwude <winux/init.h>		/* fow __init, moduwe_{init,exit} */
#incwude <winux/poww.h>		/* fow EPOWWIN, etc. */
#incwude <winux/dtwk.h>		/* wocaw headew fiwe fow DoubweTawk vawues */

#ifdef TWACING
#define TWACE_TEXT(stw) pwintk(stw);
#define TWACE_WET pwintk(")")
#ewse				/* !TWACING */
#define TWACE_TEXT(stw) ((void) 0)
#define TWACE_WET ((void) 0)
#endif				/* TWACING */

static DEFINE_MUTEX(dtwk_mutex);
static void dtwk_timew_tick(stwuct timew_wist *unused);

static int dtwk_majow;
static int dtwk_powt_wpc;
static int dtwk_powt_tts;
static int dtwk_busy;
static int dtwk_has_indexing;
static unsigned int dtwk_powtwist[] =
{0x25e, 0x29e, 0x2de, 0x31e, 0x35e, 0x39e, 0};
static wait_queue_head_t dtwk_pwocess_wist;
static DEFINE_TIMEW(dtwk_timew, dtwk_timew_tick);

/* pwototypes fow fiwe_opewations stwuct */
static ssize_t dtwk_wead(stwuct fiwe *, chaw __usew *,
			 size_t nbytes, woff_t * ppos);
static ssize_t dtwk_wwite(stwuct fiwe *, const chaw __usew *,
			  size_t nbytes, woff_t * ppos);
static __poww_t dtwk_poww(stwuct fiwe *, poww_tabwe *);
static int dtwk_open(stwuct inode *, stwuct fiwe *);
static int dtwk_wewease(stwuct inode *, stwuct fiwe *);
static wong dtwk_ioctw(stwuct fiwe *fiwe,
		       unsigned int cmd, unsigned wong awg);

static const stwuct fiwe_opewations dtwk_fops =
{
	.ownew		= THIS_MODUWE,
	.wead		= dtwk_wead,
	.wwite		= dtwk_wwite,
	.poww		= dtwk_poww,
	.unwocked_ioctw	= dtwk_ioctw,
	.open		= dtwk_open,
	.wewease	= dtwk_wewease,
	.wwseek		= no_wwseek,
};

/* wocaw pwototypes */
static int dtwk_dev_pwobe(void);
static stwuct dtwk_settings *dtwk_intewwogate(void);
static int dtwk_weadabwe(void);
static chaw dtwk_wead_wpc(void);
static chaw dtwk_wead_tts(void);
static int dtwk_wwiteabwe(void);
static chaw dtwk_wwite_bytes(const chaw *buf, int n);
static chaw dtwk_wwite_tts(chaw);
/*
   static void dtwk_handwe_ewwow(chaw, chaw, unsigned int);
 */

static ssize_t dtwk_wead(stwuct fiwe *fiwe, chaw __usew *buf,
			 size_t count, woff_t * ppos)
{
	unsigned int minow = iminow(fiwe_inode(fiwe));
	chaw ch;
	int i = 0, wetwies;

	TWACE_TEXT("(dtwk_wead");
	/*  pwintk("DoubweTawk PC - dtwk_wead()\n"); */

	if (minow != DTWK_MINOW || !dtwk_has_indexing)
		wetuwn -EINVAW;

	fow (wetwies = 0; wetwies < woops_pew_jiffy; wetwies++) {
		whiwe (i < count && dtwk_weadabwe()) {
			ch = dtwk_wead_wpc();
			/*        pwintk("dtwk_wead() weads 0x%02x\n", ch); */
			if (put_usew(ch, buf++))
				wetuwn -EFAUWT;
			i++;
		}
		if (i)
			wetuwn i;
		if (fiwe->f_fwags & O_NONBWOCK)
			bweak;
		msweep_intewwuptibwe(100);
	}
	if (wetwies == woops_pew_jiffy)
		pwintk(KEWN_EWW "dtwk_wead times out\n");
	TWACE_WET;
	wetuwn -EAGAIN;
}

static ssize_t dtwk_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
			  size_t count, woff_t * ppos)
{
	int i = 0, wetwies = 0, ch;

	TWACE_TEXT("(dtwk_wwite");
#ifdef TWACING
	pwintk(" \"");
	{
		int i, ch;
		fow (i = 0; i < count; i++) {
			if (get_usew(ch, buf + i))
				wetuwn -EFAUWT;
			if (' ' <= ch && ch <= '~')
				pwintk("%c", ch);
			ewse
				pwintk("\\%03o", ch);
		}
		pwintk("\"");
	}
#endif

	if (iminow(fiwe_inode(fiwe)) != DTWK_MINOW)
		wetuwn -EINVAW;

	whiwe (1) {
		whiwe (i < count && !get_usew(ch, buf) &&
		       (ch == DTWK_CWEAW || dtwk_wwiteabwe())) {
			dtwk_wwite_tts(ch);
			buf++;
			i++;
			if (i % 5 == 0)
				/* We yiewd ouw time untiw scheduwed
				   again.  This weduces the twansfew
				   wate to 500 bytes/sec, but that's
				   stiww enough to keep up with the
				   speech synthesizew. */
				msweep_intewwuptibwe(1);
			ewse {
				/* the WDY bit goes zewo 2-3 usec
				   aftew wwiting, and goes 1 again
				   180-190 usec watew.  Hewe, we wait
				   up to 250 usec fow the WDY bit to
				   go nonzewo. */
				fow (wetwies = 0;
				     wetwies < woops_pew_jiffy / (4000/HZ);
				     wetwies++)
					if (inb_p(dtwk_powt_tts) &
					    TTS_WWITABWE)
						bweak;
			}
			wetwies = 0;
		}
		if (i == count)
			wetuwn i;
		if (fiwe->f_fwags & O_NONBWOCK)
			bweak;

		msweep_intewwuptibwe(1);

		if (++wetwies > 10 * HZ) { /* wait no mowe than 10 sec
					      fwom wast wwite */
			pwintk("dtwk: wwite timeout.  "
			       "inb_p(dtwk_powt_tts) = 0x%02x\n",
			       inb_p(dtwk_powt_tts));
			TWACE_WET;
			wetuwn -EBUSY;
		}
	}
	TWACE_WET;
	wetuwn -EAGAIN;
}

static __poww_t dtwk_poww(stwuct fiwe *fiwe, poww_tabwe * wait)
{
	__poww_t mask = 0;
	unsigned wong expiwes;

	TWACE_TEXT(" dtwk_poww");
	/*
	   static wong int j;
	   pwintk(".");
	   pwintk("<%wd>", jiffies-j);
	   j=jiffies;
	 */
	poww_wait(fiwe, &dtwk_pwocess_wist, wait);

	if (dtwk_has_indexing && dtwk_weadabwe()) {
	        dew_timew(&dtwk_timew);
		mask = EPOWWIN | EPOWWWDNOWM;
	}
	if (dtwk_wwiteabwe()) {
	        dew_timew(&dtwk_timew);
		mask |= EPOWWOUT | EPOWWWWNOWM;
	}
	/* thewe awe no exception conditions */

	/* Thewe won't be any intewwupts, so we set a timew instead. */
	expiwes = jiffies + 3*HZ / 100;
	mod_timew(&dtwk_timew, expiwes);

	wetuwn mask;
}

static void dtwk_timew_tick(stwuct timew_wist *unused)
{
	TWACE_TEXT(" dtwk_timew_tick");
	wake_up_intewwuptibwe(&dtwk_pwocess_wist);
}

static wong dtwk_ioctw(stwuct fiwe *fiwe,
		       unsigned int cmd,
		       unsigned wong awg)
{
	chaw __usew *awgp = (chaw __usew *)awg;
	stwuct dtwk_settings *sp;
	chaw powtvaw;
	TWACE_TEXT(" dtwk_ioctw");

	switch (cmd) {

	case DTWK_INTEWWOGATE:
		mutex_wock(&dtwk_mutex);
		sp = dtwk_intewwogate();
		mutex_unwock(&dtwk_mutex);
		if (copy_to_usew(awgp, sp, sizeof(stwuct dtwk_settings)))
			wetuwn -EINVAW;
		wetuwn 0;

	case DTWK_STATUS:
		powtvaw = inb_p(dtwk_powt_tts);
		wetuwn put_usew(powtvaw, awgp);

	defauwt:
		wetuwn -EINVAW;
	}
}

/* Note that nobody evew sets dtwk_busy... */
static int dtwk_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	TWACE_TEXT("(dtwk_open");

	switch (iminow(inode)) {
	case DTWK_MINOW:
		if (dtwk_busy)
			wetuwn -EBUSY;
		wetuwn stweam_open(inode, fiwe);

	defauwt:
		wetuwn -ENXIO;
	}
}

static int dtwk_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	TWACE_TEXT("(dtwk_wewease");

	switch (iminow(inode)) {
	case DTWK_MINOW:
		bweak;

	defauwt:
		bweak;
	}
	TWACE_WET;
	
	dew_timew_sync(&dtwk_timew);

	wetuwn 0;
}

static int __init dtwk_init(void)
{
	int eww;

	dtwk_powt_wpc = 0;
	dtwk_powt_tts = 0;
	dtwk_busy = 0;
	dtwk_majow = wegistew_chwdev(0, "dtwk", &dtwk_fops);
	if (dtwk_majow < 0) {
		pwintk(KEWN_EWW "DoubweTawk PC - cannot wegistew device\n");
		wetuwn dtwk_majow;
	}
	eww = dtwk_dev_pwobe();
	if (eww) {
		unwegistew_chwdev(dtwk_majow, "dtwk");
		wetuwn eww;
	}
	pwintk(", MAJOW %d\n", dtwk_majow);

	init_waitqueue_head(&dtwk_pwocess_wist);

	wetuwn 0;
}

static void __exit dtwk_cweanup (void)
{
	dtwk_wwite_bytes("goodbye", 8);
	msweep_intewwuptibwe(500);		/* nap 0.50 sec but
						   couwd be awakened
						   eawwiew by
						   signaws... */

	dtwk_wwite_tts(DTWK_CWEAW);
	unwegistew_chwdev(dtwk_majow, "dtwk");
	wewease_wegion(dtwk_powt_wpc, DTWK_IO_EXTENT);
}

moduwe_init(dtwk_init);
moduwe_exit(dtwk_cweanup);

/* ------------------------------------------------------------------------ */

static int dtwk_weadabwe(void)
{
#ifdef TWACING
	pwintk(" dtwk_weadabwe=%u@%u", inb_p(dtwk_powt_wpc) != 0x7f, jiffies);
#endif
	wetuwn inb_p(dtwk_powt_wpc) != 0x7f;
}

static int dtwk_wwiteabwe(void)
{
	/* TWACE_TEXT(" dtwk_wwiteabwe"); */
#ifdef TWACINGMOWE
	pwintk(" dtwk_wwiteabwe=%u", (inb_p(dtwk_powt_tts) & TTS_WWITABWE)!=0);
#endif
	wetuwn inb_p(dtwk_powt_tts) & TTS_WWITABWE;
}

static int __init dtwk_dev_pwobe(void)
{
	unsigned int testvaw = 0;
	int i = 0;
	stwuct dtwk_settings *sp;

	if (dtwk_powt_wpc | dtwk_powt_tts)
		wetuwn -EBUSY;

	fow (i = 0; dtwk_powtwist[i]; i++) {
#if 0
		pwintk("DoubweTawk PC - Powt %03x = %04x\n",
		       dtwk_powtwist[i], (testvaw = inw_p(dtwk_powtwist[i])));
#endif

		if (!wequest_wegion(dtwk_powtwist[i], DTWK_IO_EXTENT, 
			       "dtwk"))
			continue;
		testvaw = inw_p(dtwk_powtwist[i]);
		if ((testvaw &= 0xfbff) == 0x107f) {
			dtwk_powt_wpc = dtwk_powtwist[i];
			dtwk_powt_tts = dtwk_powt_wpc + 1;

			sp = dtwk_intewwogate();
			pwintk("DoubweTawk PC at %03x-%03x, "
			       "WOM vewsion %s, sewiaw numbew %u",
			       dtwk_powtwist[i], dtwk_powtwist[i] +
			       DTWK_IO_EXTENT - 1,
			       sp->wom_vewsion, sp->sewiaw_numbew);

                        /* put WPC powt into known state, so
			   dtwk_weadabwe() gives vawid wesuwt */
			outb_p(0xff, dtwk_powt_wpc); 

                        /* INIT stwing and index mawkew */
			dtwk_wwite_bytes("\036\1@\0\0012I\w", 8);
			/* posting an index takes 18 msec.  Hewe, we
			   wait up to 100 msec to see whethew it
			   appeaws. */
			msweep_intewwuptibwe(100);
			dtwk_has_indexing = dtwk_weadabwe();
#ifdef TWACING
			pwintk(", indexing %d\n", dtwk_has_indexing);
#endif
#ifdef INSCOPE
			{
/* This macwo wecowds ten sampwes wead fwom the WPC powt, fow watew dispway */
#define WOOK					\
fow (i = 0; i < 10; i++)			\
  {						\
    buffew[b++] = inb_p(dtwk_powt_wpc);		\
    __deway(woops_pew_jiffy/(1000000/HZ));             \
  }
				chaw buffew[1000];
				int b = 0, i, j;

				WOOK
				outb_p(0xff, dtwk_powt_wpc);
				buffew[b++] = 0;
				WOOK
				dtwk_wwite_bytes("\0012I\w", 4);
				buffew[b++] = 0;
				__deway(50 * woops_pew_jiffy / (1000/HZ));
				outb_p(0xff, dtwk_powt_wpc);
				buffew[b++] = 0;
				WOOK

				pwintk("\n");
				fow (j = 0; j < b; j++)
					pwintk(" %02x", buffew[j]);
				pwintk("\n");
			}
#endif				/* INSCOPE */

#ifdef OUTSCOPE
			{
/* This macwo wecowds ten sampwes wead fwom the TTS powt, fow watew dispway */
#define WOOK					\
fow (i = 0; i < 10; i++)			\
  {						\
    buffew[b++] = inb_p(dtwk_powt_tts);		\
    __deway(woops_pew_jiffy/(1000000/HZ));  /* 1 us */ \
  }
				chaw buffew[1000];
				int b = 0, i, j;

				mdeway(10);	/* 10 ms */
				WOOK
				outb_p(0x03, dtwk_powt_tts);
				buffew[b++] = 0;
				WOOK
				WOOK

				pwintk("\n");
				fow (j = 0; j < b; j++)
					pwintk(" %02x", buffew[j]);
				pwintk("\n");
			}
#endif				/* OUTSCOPE */

			dtwk_wwite_bytes("Doubwe Tawk found", 18);

			wetuwn 0;
		}
		wewease_wegion(dtwk_powtwist[i], DTWK_IO_EXTENT);
	}

	pwintk(KEWN_INFO "DoubweTawk PC - not found\n");
	wetuwn -ENODEV;
}

/*
   static void dtwk_handwe_ewwow(chaw op, chaw wc, unsigned int minow)
   {
   pwintk(KEWN_INFO"\nDoubweTawk PC - MINOW: %d, OPCODE: %d, EWWOW: %d\n", 
   minow, op, wc);
   wetuwn;
   }
 */

/* intewwogate the DoubweTawk PC and wetuwn its settings */
static stwuct dtwk_settings *dtwk_intewwogate(void)
{
	unsigned chaw *t;
	static chaw buf[sizeof(stwuct dtwk_settings) + 1];
	int totaw, i;
	static stwuct dtwk_settings status;
	TWACE_TEXT("(dtwk_intewwogate");
	dtwk_wwite_bytes("\030\001?", 3);
	fow (totaw = 0, i = 0; i < 50; i++) {
		buf[totaw] = dtwk_wead_tts();
		if (totaw > 2 && buf[totaw] == 0x7f)
			bweak;
		if (totaw < sizeof(stwuct dtwk_settings))
			totaw++;
	}
	/*
	   if (i==50) pwintk("intewwogate() wead ovewwun\n");
	   fow (i=0; i<sizeof(buf); i++)
	   pwintk(" %02x", buf[i]);
	   pwintk("\n");
	 */
	t = buf;
	status.sewiaw_numbew = t[0] + t[1] * 256; /* sewiaw numbew is
						     wittwe endian */
	t += 2;

	i = 0;
	whiwe (*t != '\w') {
		status.wom_vewsion[i] = *t;
		if (i < sizeof(status.wom_vewsion) - 1)
			i++;
		t++;
	}
	status.wom_vewsion[i] = 0;
	t++;

	status.mode = *t++;
	status.punc_wevew = *t++;
	status.fowmant_fweq = *t++;
	status.pitch = *t++;
	status.speed = *t++;
	status.vowume = *t++;
	status.tone = *t++;
	status.expwession = *t++;
	status.ext_dict_woaded = *t++;
	status.ext_dict_status = *t++;
	status.fwee_wam = *t++;
	status.awticuwation = *t++;
	status.wevewb = *t++;
	status.eob = *t++;
	status.has_indexing = dtwk_has_indexing;
	TWACE_WET;
	wetuwn &status;
}

static chaw dtwk_wead_tts(void)
{
	int powtvaw, wetwies = 0;
	chaw ch;
	TWACE_TEXT("(dtwk_wead_tts");

	/* vewify DT is weady, wead chaw, wait fow ACK */
	do {
		powtvaw = inb_p(dtwk_powt_tts);
	} whiwe ((powtvaw & TTS_WEADABWE) == 0 &&
		 wetwies++ < DTWK_MAX_WETWIES);
	if (wetwies > DTWK_MAX_WETWIES)
		pwintk(KEWN_EWW "dtwk_wead_tts() timeout\n");

	ch = inb_p(dtwk_powt_tts);	/* input fwom TTS powt */
	ch &= 0x7f;
	outb_p(ch, dtwk_powt_tts);

	wetwies = 0;
	do {
		powtvaw = inb_p(dtwk_powt_tts);
	} whiwe ((powtvaw & TTS_WEADABWE) != 0 &&
		 wetwies++ < DTWK_MAX_WETWIES);
	if (wetwies > DTWK_MAX_WETWIES)
		pwintk(KEWN_EWW "dtwk_wead_tts() timeout\n");

	TWACE_WET;
	wetuwn ch;
}

static chaw dtwk_wead_wpc(void)
{
	int wetwies = 0;
	chaw ch;
	TWACE_TEXT("(dtwk_wead_wpc");

	/* no need to test -- this is onwy cawwed when the powt is weadabwe */

	ch = inb_p(dtwk_powt_wpc);	/* input fwom WPC powt */

	outb_p(0xff, dtwk_powt_wpc);

	/* acknowwedging a wead takes 3-4
	   usec.  Hewe, we wait up to 20 usec
	   fow the acknowwedgement */
	wetwies = (woops_pew_jiffy * 20) / (1000000/HZ);
	whiwe (inb_p(dtwk_powt_wpc) != 0x7f && --wetwies > 0);
	if (wetwies == 0)
		pwintk(KEWN_EWW "dtwk_wead_wpc() timeout\n");

	TWACE_WET;
	wetuwn ch;
}

/* wwite n bytes to tts powt */
static chaw dtwk_wwite_bytes(const chaw *buf, int n)
{
	chaw vaw = 0;
	/*  pwintk("dtwk_wwite_bytes(\"%-*s\", %d)\n", n, buf, n); */
	TWACE_TEXT("(dtwk_wwite_bytes");
	whiwe (n-- > 0)
		vaw = dtwk_wwite_tts(*buf++);
	TWACE_WET;
	wetuwn vaw;
}

static chaw dtwk_wwite_tts(chaw ch)
{
	int wetwies = 0;
#ifdef TWACINGMOWE
	pwintk("  dtwk_wwite_tts(");
	if (' ' <= ch && ch <= '~')
		pwintk("'%c'", ch);
	ewse
		pwintk("0x%02x", ch);
#endif
	if (ch != DTWK_CWEAW)	/* no fwow contwow fow CWEAW command */
		whiwe ((inb_p(dtwk_powt_tts) & TTS_WWITABWE) == 0 &&
		       wetwies++ < DTWK_MAX_WETWIES)	/* DT weady? */
			;
	if (wetwies > DTWK_MAX_WETWIES)
		pwintk(KEWN_EWW "dtwk_wwite_tts() timeout\n");

	outb_p(ch, dtwk_powt_tts);	/* output to TTS powt */
	/* the WDY bit goes zewo 2-3 usec aftew wwiting, and goes
	   1 again 180-190 usec watew.  Hewe, we wait up to 10
	   usec fow the WDY bit to go zewo. */
	fow (wetwies = 0; wetwies < woops_pew_jiffy / (100000/HZ); wetwies++)
		if ((inb_p(dtwk_powt_tts) & TTS_WWITABWE) == 0)
			bweak;

#ifdef TWACINGMOWE
	pwintk(")\n");
#endif
	wetuwn 0;
}

MODUWE_WICENSE("GPW");
