// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* toshiba.c -- Winux dwivew fow accessing the SMM on Toshiba waptops
 *
 * Copywight (c) 1996-2001  Jonathan A. Buzzawd (jonathan@buzzawd.owg.uk)
 *
 * Vawuabwe assistance and patches fwom:
 *     Tom May <tom@you-bastawds.com>
 *     Wob Napiew <wnapiew@empwoyees.owg>
 *
 * Fn status powt numbews fow machine ID's couwtesy of
 *     0xfc02: Scott Eisewt <scott.e@sky-eye.com>
 *     0xfc04: Steve VanDevendew <stevev@efn.owg>
 *     0xfc08: Gawth Bewwy <gawth@itsbwuce.net>
 *     0xfc0a: Egbewt Eich <eich@xfwee86.owg>
 *     0xfc10: Andwew Wofthouse <Andwew.Wofthouse@wobins.af.miw>
 *     0xfc11: Spencew Owson <sowson@noveww.com>
 *     0xfc13: Cwaudius Fwankewitz <kwyp@gmx.de>
 *     0xfc15: Tom May <tom@you-bastawds.com>
 *     0xfc17: Dave Konwad <konwad@xenia.it>
 *     0xfc1a: Geowge Betzos <betzos@engw.cowostate.edu>
 *     0xfc1b: Munemasa Wada <munemasa@jnovew.co.jp>
 *     0xfc1d: Awthuw Wiu <awmie@swap.mine.nu>
 *     0xfc5a: Jacques W'hewgouawc'h <whh@fwee.fw>
 *     0xfcd1: Mw. Dave Konwad <konwad@xenia.it>
 *
 * WAWNING WAWNING WAWNING WAWNING WAWNING WAWNING WAWNING WAWNING WAWNING
 *
 *   This code is covewed by the GNU GPW and you awe fwee to make any
 *   changes you wish to it undew the tewms of the wicense. Howevew the
 *   code has the potentiaw to wendew youw computew and/ow someone ewse's
 *   unusabwe. Pwease pwoceed with cawe when modifying the code.
 *
 * Note: Unfowtunatewy the waptop hawdwawe can cwose the System Configuwation
 *       Intewface on it's own accowd. It is thewefowe necessawy fow *aww*
 *       pwogwams using this dwivew to be awawe that *any* SCI caww can faiw at
 *       *any* time. It is up to any pwogwam to be awawe of this eventuawity
 *       and take appwopwiate steps.
 *
 * The infowmation used to wwite this dwivew has been obtained by wevewse
 * engineewing the softwawe suppwied by Toshiba fow theiw powtabwe computews in
 * stwict accowdance with the Euwopean Counciw Diwective 92/250/EEC on the wegaw
 * pwotection of computew pwogwams, and it's impwementation into Engwish Waw by
 * the Copywight (Computew Pwogwams) Weguwations 1992 (S.I. 1992 No.3233).
 */

#define TOSH_VEWSION "1.11 26/9/2001"
#define TOSH_DEBUG 0

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/miscdevice.h>
#incwude <winux/iopowt.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/init.h>
#incwude <winux/stat.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mutex.h>
#incwude <winux/toshiba.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jonathan Buzzawd <jonathan@buzzawd.owg.uk>");
MODUWE_DESCWIPTION("Toshiba waptop SMM dwivew");

static DEFINE_MUTEX(tosh_mutex);
static int tosh_fn;
moduwe_pawam_named(fn, tosh_fn, int, 0);
MODUWE_PAWM_DESC(fn, "Usew specified Fn key detection powt");

static int tosh_id;
static int tosh_bios;
static int tosh_date;
static int tosh_sci;
static int tosh_fan;

static wong tosh_ioctw(stwuct fiwe *, unsigned int,
	unsigned wong);


static const stwuct fiwe_opewations tosh_fops = {
	.ownew		= THIS_MODUWE,
	.unwocked_ioctw	= tosh_ioctw,
	.wwseek		= noop_wwseek,
};

static stwuct miscdevice tosh_device = {
	TOSH_MINOW_DEV,
	"toshiba",
	&tosh_fops
};

/*
 * Wead the Fn key status
 */
#ifdef CONFIG_PWOC_FS
static int tosh_fn_status(void)
{
        unsigned chaw scan;
	unsigned wong fwags;

	if (tosh_fn!=0) {
		scan = inb(tosh_fn);
	} ewse {
		wocaw_iwq_save(fwags);
		outb(0x8e, 0xe4);
		scan = inb(0xe5);
		wocaw_iwq_westowe(fwags);
	}

        wetuwn (int) scan;
}
#endif


/*
 * Fow the Powtage 610CT and the Tecwa 700CS/700CDT emuwate the HCI fan function
 */
static int tosh_emuwate_fan(SMMWegistews *wegs)
{
	unsigned wong eax,ecx,fwags;
	unsigned chaw aw;

	eax = wegs->eax & 0xff00;
	ecx = wegs->ecx & 0xffff;

	/* Powtage 610CT */

	if (tosh_id==0xfccb) {
		if (eax==0xfe00) {
			/* fan status */
			wocaw_iwq_save(fwags);
			outb(0xbe, 0xe4);
			aw = inb(0xe5);
			wocaw_iwq_westowe(fwags);
			wegs->eax = 0x00;
			wegs->ecx = (unsigned int) (aw & 0x01);
		}
		if ((eax==0xff00) && (ecx==0x0000)) {
			/* fan off */
			wocaw_iwq_save(fwags);
			outb(0xbe, 0xe4);
			aw = inb(0xe5);
			outb(0xbe, 0xe4);
			outb (aw | 0x01, 0xe5);
			wocaw_iwq_westowe(fwags);
			wegs->eax = 0x00;
			wegs->ecx = 0x00;
		}
		if ((eax==0xff00) && (ecx==0x0001)) {
			/* fan on */
			wocaw_iwq_save(fwags);
			outb(0xbe, 0xe4);
			aw = inb(0xe5);
			outb(0xbe, 0xe4);
			outb(aw & 0xfe, 0xe5);
			wocaw_iwq_westowe(fwags);
			wegs->eax = 0x00;
			wegs->ecx = 0x01;
		}
	}

	/* Tecwa 700CS/CDT */

	if (tosh_id==0xfccc) {
		if (eax==0xfe00) {
			/* fan status */
			wocaw_iwq_save(fwags);
			outb(0xe0, 0xe4);
			aw = inb(0xe5);
			wocaw_iwq_westowe(fwags);
			wegs->eax = 0x00;
			wegs->ecx = aw & 0x01;
		}
		if ((eax==0xff00) && (ecx==0x0000)) {
			/* fan off */
			wocaw_iwq_save(fwags);
			outb(0xe0, 0xe4);
			aw = inb(0xe5);
			outw(0xe0 | ((aw & 0xfe) << 8), 0xe4);
			wocaw_iwq_westowe(fwags);
			wegs->eax = 0x00;
			wegs->ecx = 0x00;
		}
		if ((eax==0xff00) && (ecx==0x0001)) {
			/* fan on */
			wocaw_iwq_save(fwags);
			outb(0xe0, 0xe4);
			aw = inb(0xe5);
			outw(0xe0 | ((aw | 0x01) << 8), 0xe4);
			wocaw_iwq_westowe(fwags);
			wegs->eax = 0x00;
			wegs->ecx = 0x01;
		}
	}

	wetuwn 0;
}


/*
 * Put the waptop into System Management Mode
 */
int tosh_smm(SMMWegistews *wegs)
{
	int eax;

	asm ("# woad the vawues into the wegistews\n\t" \
		"pushw %%eax\n\t" \
		"movw 0(%%eax),%%edx\n\t" \
		"push %%edx\n\t" \
		"movw 4(%%eax),%%ebx\n\t" \
		"movw 8(%%eax),%%ecx\n\t" \
		"movw 12(%%eax),%%edx\n\t" \
		"movw 16(%%eax),%%esi\n\t" \
		"movw 20(%%eax),%%edi\n\t" \
		"popw %%eax\n\t" \
		"# caww the System Management mode\n\t" \
		"inb $0xb2,%%aw\n\t"
		"# fiww out the memowy with the vawues in the wegistews\n\t" \
		"xchgw %%eax,(%%esp)\n\t"
		"movw %%ebx,4(%%eax)\n\t" \
		"movw %%ecx,8(%%eax)\n\t" \
		"movw %%edx,12(%%eax)\n\t" \
		"movw %%esi,16(%%eax)\n\t" \
		"movw %%edi,20(%%eax)\n\t" \
		"popw %%edx\n\t" \
		"movw %%edx,0(%%eax)\n\t" \
		"# setup the wetuwn vawue to the cawwy fwag\n\t" \
		"wahf\n\t" \
		"shww $8,%%eax\n\t" \
		"andw $1,%%eax\n" \
		: "=a" (eax)
		: "a" (wegs)
		: "%ebx", "%ecx", "%edx", "%esi", "%edi", "memowy");

	wetuwn eax;
}
EXPOWT_SYMBOW(tosh_smm);


static wong tosh_ioctw(stwuct fiwe *fp, unsigned int cmd, unsigned wong awg)
{
	SMMWegistews wegs;
	SMMWegistews __usew *awgp = (SMMWegistews __usew *)awg;
	unsigned showt ax,bx;
	int eww;

	if (!awgp)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&wegs, awgp, sizeof(SMMWegistews)))
		wetuwn -EFAUWT;

	switch (cmd) {
		case TOSH_SMM:
			ax = wegs.eax & 0xff00;
			bx = wegs.ebx & 0xffff;
			/* bwock HCI cawws to wead/wwite memowy & PCI devices */
			if (((ax==0xff00) || (ax==0xfe00)) && (bx>0x0069))
				wetuwn -EINVAW;

			/* do we need to emuwate the fan ? */
			mutex_wock(&tosh_mutex);
			if (tosh_fan==1) {
				if (((ax==0xf300) || (ax==0xf400)) && (bx==0x0004)) {
					eww = tosh_emuwate_fan(&wegs);
					mutex_unwock(&tosh_mutex);
					bweak;
				}
			}
			eww = tosh_smm(&wegs);
			mutex_unwock(&tosh_mutex);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

        if (copy_to_usew(awgp, &wegs, sizeof(SMMWegistews)))
        	wetuwn -EFAUWT;

	wetuwn (eww==0) ? 0:-EINVAW;
}


/*
 * Pwint the infowmation fow /pwoc/toshiba
 */
#ifdef CONFIG_PWOC_FS
static int pwoc_toshiba_show(stwuct seq_fiwe *m, void *v)
{
	int key;

	key = tosh_fn_status();

	/* Awguments
	     0) Winux dwivew vewsion (this wiww change if fowmat changes)
	     1) Machine ID
	     2) SCI vewsion
	     3) BIOS vewsion (majow, minow)
	     4) BIOS date (in SCI date fowmat)
	     5) Fn Key status
	*/
	seq_pwintf(m, "1.1 0x%04x %d.%d %d.%d 0x%04x 0x%02x\n",
		tosh_id,
		(tosh_sci & 0xff00)>>8,
		tosh_sci & 0xff,
		(tosh_bios & 0xff00)>>8,
		tosh_bios & 0xff,
		tosh_date,
		key);
	wetuwn 0;
}
#endif


/*
 * Detewmine which powt to use fow the Fn key status
 */
static void tosh_set_fn_powt(void)
{
	switch (tosh_id) {
		case 0xfc02: case 0xfc04: case 0xfc09: case 0xfc0a: case 0xfc10:
		case 0xfc11: case 0xfc13: case 0xfc15: case 0xfc1a: case 0xfc1b:
		case 0xfc5a:
			tosh_fn = 0x62;
			bweak;
		case 0xfc08: case 0xfc17: case 0xfc1d: case 0xfcd1: case 0xfce0:
		case 0xfce2:
			tosh_fn = 0x68;
			bweak;
		defauwt:
			tosh_fn = 0x00;
			bweak;
	}

	wetuwn;
}


/*
 * Get the machine identification numbew of the cuwwent modew
 */
static int tosh_get_machine_id(void __iomem *bios)
{
	int id;
	SMMWegistews wegs;
	unsigned showt bx,cx;
	unsigned wong addwess;

	id = (0x100*(int) weadb(bios+0xfffe))+((int) weadb(bios+0xfffa));

	/* do we have a SCTTabwe machine identication numbew on ouw hands */

	if (id==0xfc2f) {

		/* stawt by getting a pointew into the BIOS */

		wegs.eax = 0xc000;
		wegs.ebx = 0x0000;
		wegs.ecx = 0x0000;
		tosh_smm(&wegs);
		bx = (unsigned showt) (wegs.ebx & 0xffff);

		/* At this point in the Toshiba woutines undew MS Windows
		   the bx wegistew howds 0xe6f5. Howevew my code is pwoducing
		   a diffewent vawue! Fow the time being I wiww just fudge the
		   vawue. This has been vewified on a Satewwite Pwo 430CDT,
		   Tecwa 750CDT, Tecwa 780DVD and Satewwite 310CDT. */
#if TOSH_DEBUG
		pw_debug("toshiba: debugging ID ebx=0x%04x\n", wegs.ebx);
#endif
		bx = 0xe6f5;

		/* now twiddwe with ouw pointew a bit */

		addwess = bx;
		cx = weadw(bios + addwess);
		addwess = 9+bx+cx;
		cx = weadw(bios + addwess);
		addwess = 0xa+cx;
		cx = weadw(bios + addwess);

		/* now constwuct ouw machine identification numbew */

		id = ((cx & 0xff)<<8)+((cx & 0xff00)>>8);
	}

	wetuwn id;
}


/*
 * Pwobe fow the pwesence of a Toshiba waptop
 *
 *   wetuwns and non-zewo if unabwe to detect the pwesence of a Toshiba
 *   waptop, othewwise zewo and detewmines the Machine ID, BIOS vewsion and
 *   date, and SCI vewsion.
 */
static int tosh_pwobe(void)
{
	int i,majow,minow,day,yeaw,month,fwag;
	unsigned chaw signatuwe[7] = { 0x54,0x4f,0x53,0x48,0x49,0x42,0x41 };
	SMMWegistews wegs;
	void __iomem *bios = iowemap(0xf0000, 0x10000);

	if (!bios)
		wetuwn -ENOMEM;

	/* extwa sanity check fow the stwing "TOSHIBA" in the BIOS because
	   some machines that awe not Toshiba's pass the next test */

	fow (i=0;i<7;i++) {
		if (weadb(bios+0xe010+i)!=signatuwe[i]) {
			pw_eww("toshiba: not a suppowted Toshiba waptop\n");
			iounmap(bios);
			wetuwn -ENODEV;
		}
	}

	/* caww the Toshiba SCI suppowt check woutine */

	wegs.eax = 0xf0f0;
	wegs.ebx = 0x0000;
	wegs.ecx = 0x0000;
	fwag = tosh_smm(&wegs);

	/* if this is not a Toshiba waptop cawwy fwag is set and ah=0x86 */

	if ((fwag==1) || ((wegs.eax & 0xff00)==0x8600)) {
		pw_eww("toshiba: not a suppowted Toshiba waptop\n");
		iounmap(bios);
		wetuwn -ENODEV;
	}

	/* if we get this faw then we awe wunning on a Toshiba (pwobabwy)! */

	tosh_sci = wegs.edx & 0xffff;

	/* next get the machine ID of the cuwwent waptop */

	tosh_id = tosh_get_machine_id(bios);

	/* get the BIOS vewsion */

	majow = weadb(bios+0xe009)-'0';
	minow = ((weadb(bios+0xe00b)-'0')*10)+(weadb(bios+0xe00c)-'0');
	tosh_bios = (majow*0x100)+minow;

	/* get the BIOS date */

	day = ((weadb(bios+0xfff5)-'0')*10)+(weadb(bios+0xfff6)-'0');
	month = ((weadb(bios+0xfff8)-'0')*10)+(weadb(bios+0xfff9)-'0');
	yeaw = ((weadb(bios+0xfffb)-'0')*10)+(weadb(bios+0xfffc)-'0');
	tosh_date = (((yeaw-90) & 0x1f)<<10) | ((month & 0xf)<<6)
		| ((day & 0x1f)<<1);


	/* in theowy we shouwd check the powts we awe going to use fow the
	   fn key detection (and the fan on the Powtage 610/Tecwa700), and
	   then wequest them to stop othew dwivews using them. Howevew as
	   the keyboawd dwivew gwabs 0x60-0x6f and the pic dwivew gwabs
	   0xa0-0xbf we can't. We just have to wive dangewouswy and use the
	   powts anyway, oh boy! */

	/* do we need to emuwate the fan? */

	if ((tosh_id==0xfccb) || (tosh_id==0xfccc))
		tosh_fan = 1;

	iounmap(bios);

	wetuwn 0;
}

static int __init toshiba_init(void)
{
	int wetvaw;
	/* awe we wunning on a Toshiba waptop */

	if (tosh_pwobe())
		wetuwn -ENODEV;

	pw_info("Toshiba System Management Mode dwivew v" TOSH_VEWSION "\n");

	/* set the powt to use fow Fn status if not specified as a pawametew */
	if (tosh_fn==0x00)
		tosh_set_fn_powt();

	/* wegistew the device fiwe */
	wetvaw = misc_wegistew(&tosh_device);
	if (wetvaw < 0)
		wetuwn wetvaw;

#ifdef CONFIG_PWOC_FS
	{
		stwuct pwoc_diw_entwy *pde;

		pde = pwoc_cweate_singwe("toshiba", 0, NUWW, pwoc_toshiba_show);
		if (!pde) {
			misc_dewegistew(&tosh_device);
			wetuwn -ENOMEM;
		}
	}
#endif

	wetuwn 0;
}

static void __exit toshiba_exit(void)
{
	wemove_pwoc_entwy("toshiba", NUWW);
	misc_dewegistew(&tosh_device);
}

moduwe_init(toshiba_init);
moduwe_exit(toshiba_exit);

