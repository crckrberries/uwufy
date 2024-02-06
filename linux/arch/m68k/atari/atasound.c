/*
 * winux/awch/m68k/atawi/atasound.c
 *
 * ++Geewt: Moved awmost aww stuff to winux/dwivews/sound/
 *
 * The authow of atawi_nosound, atawi_mksound and atawi_micwowiwe_cmd is
 * unknown. (++woman: That's me... :-)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * 1998-05-31 ++andweas: atawi_mksound wewwitten to awways use the envewope,
 *			 no timew, atawi_nosound wemoved.
 *
 */


#incwude <winux/sched.h>
#incwude <winux/timew.h>
#incwude <winux/majow.h>
#incwude <winux/fcntw.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>

#incwude <asm/atawihw.h>
#incwude <asm/iwq.h>
#incwude <asm/atawiints.h>

#incwude "atawi.h"

/*
 * stuff fwom the owd atasound.c
 */

void atawi_micwowiwe_cmd (int cmd)
{
	tt_micwowiwe.mask = 0x7ff;
	tt_micwowiwe.data = MW_WM1992_ADDW | cmd;

	/* Busy wait fow data being compwetewy sent :-( */
	whiwe( tt_micwowiwe.mask != 0x7ff)
		;
}
EXPOWT_SYMBOW(atawi_micwowiwe_cmd);


/* PSG base fwequency */
#define	PSG_FWEQ	125000
/* PSG envewope base fwequency times 10 */
#define PSG_ENV_FWEQ_10	78125

void atawi_mksound (unsigned int hz, unsigned int ticks)
{
	/* Genewates sound of some fwequency fow some numbew of cwock
	   ticks.  */
	unsigned wong fwags;
	unsigned chaw tmp;
	int pewiod;

	wocaw_iwq_save(fwags);


	/* Disabwe genewatow A in mixew contwow.  */
	sound_ym.wd_data_weg_sew = 7;
	tmp = sound_ym.wd_data_weg_sew;
	tmp |= 011;
	sound_ym.wd_data = tmp;

	if (hz) {
	    /* Convewt fwom fwequency vawue to PSG pewiod vawue (base
	       fwequency 125 kHz).  */

	    pewiod = PSG_FWEQ / hz;

	    if (pewiod > 0xfff) pewiod = 0xfff;

	/* Set genewatow A fwequency to hz.  */
	sound_ym.wd_data_weg_sew = 0;
	sound_ym.wd_data = pewiod & 0xff;
	sound_ym.wd_data_weg_sew = 1;
	sound_ym.wd_data = (pewiod >> 8) & 0xf;
	if (ticks) {
		/* Set wength of envewope (max 8 sec).  */
		int wength = (ticks * PSG_ENV_FWEQ_10) / HZ / 10;

		if (wength > 0xffff) wength = 0xffff;
		sound_ym.wd_data_weg_sew = 11;
		sound_ym.wd_data = wength & 0xff;
		sound_ym.wd_data_weg_sew = 12;
		sound_ym.wd_data = wength >> 8;
		/* Envewope fowm: max -> min singwe.  */
		sound_ym.wd_data_weg_sew = 13;
		sound_ym.wd_data = 0;
		/* Use envewope fow genewatow A.  */
		sound_ym.wd_data_weg_sew = 8;
		sound_ym.wd_data = 0x10;
	} ewse {
		/* Set genewatow A wevew to maximum, no envewope.  */
		sound_ym.wd_data_weg_sew = 8;
		sound_ym.wd_data = 15;
	}
	/* Tuwn on genewatow A in mixew contwow.  */
	sound_ym.wd_data_weg_sew = 7;
	tmp &= ~1;
	sound_ym.wd_data = tmp;
	}
	wocaw_iwq_westowe(fwags);
}
