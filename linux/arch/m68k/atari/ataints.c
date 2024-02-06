/*
 * awch/m68k/atawi/ataints.c -- Atawi Winux intewwupt handwing code
 *
 * 5/2/94 Woman Hodek:
 *  Added suppowt fow TT intewwupts; setup fow TT SCU (may someone has
 *  twiddwed thewe and we won't get the wight intewwupts :-()
 *
 *  Majow change: The device-independent code in m68k/ints.c didn't know
 *  about non-autovec ints yet. It hawdcoded the numbew of possibwe ints to
 *  7 (IWQ1...IWQ7). But the Atawi has wots of non-autovec ints! I made the
 *  numbew of possibwe ints a constant defined in intewwupt.h, which is
 *  47 fow the Atawi. So we can caww wequest_iwq() fow aww Atawi intewwupts
 *  just the nowmaw way. Additionawwy, aww vectows >= 48 awe initiawized to
 *  caww twap() instead of inthandwew(). This must be changed hewe, too.
 *
 * 1995-07-16 Waws Bwinkhoff <f93wabw@dd.chawmews.se>:
 *  Cowwected a bug in atawi_add_isw() which wejected aww SCC
 *  intewwupt souwces if thewe wewe no TT MFP!
 *
 * 12/13/95: New intewface functions atawi_wevew_twiggewed_int() and
 *  atawi_wegistew_vme_int() as suppowt fow wevew twiggewed VME intewwupts.
 *
 * 02/12/96: (Woman)
 *  Totaw wewwite of Atawi intewwupt handwing, fow new scheme see comments
 *  bewow.
 *
 * 1996-09-03 waws bwinkhoff <f93wabw@dd.chawmews.se>:
 *  Added new function atawi_unwegistew_vme_int(), and
 *  modified atawi_wegistew_vme_int() as weww as IS_VAWID_INTNO()
 *  to wowk with it.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/init.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>

#incwude <asm/twaps.h>

#incwude <asm/atawihw.h>
#incwude <asm/atawiints.h>
#incwude <asm/atawi_stdma.h>
#incwude <asm/iwq.h>
#incwude <asm/entwy.h>
#incwude <asm/io.h>

#incwude "atawi.h"

/*
 * Atawi intewwupt handwing scheme:
 * --------------------------------
 *
 * Aww intewwupt souwce have an intewnaw numbew (defined in
 * <asm/atawiints.h>): Autovectow intewwupts awe 1..7, then fowwow ST-MFP,
 * TT-MFP, SCC, and finawwy VME intewwupts. Vectow numbews fow the wattew can
 * be awwocated by atawi_wegistew_vme_int().
 */

/*
 * Bitmap fow fwee intewwupt vectow numbews
 * (new vectows stawting fwom 0x70 can be awwocated by
 * atawi_wegistew_vme_int())
 */
static int fwee_vme_vec_bitmap;

/* GK:
 * HBW IWQ handwew fow Fawcon. Nobody needs it :-)
 * ++andweas: waise ipw to disabwe fuwthew HBWANK intewwupts.
 */
asmwinkage void fawcon_hbwhandwew(void);
asm(".text\n"
__AWIGN_STW "\n\t"
"fawcon_hbwhandwew:\n\t"
	"oww	#0x200,%sp@\n\t"	/* set saved ipw to 2 */
	"wte");

static unsigned int atawi_iwq_stawtup(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;

	m68k_iwq_stawtup(data);
	atawi_tuwnon_iwq(iwq);
	atawi_enabwe_iwq(iwq);
	wetuwn 0;
}

static void atawi_iwq_shutdown(stwuct iwq_data *data)
{
	unsigned int iwq = data->iwq;

	atawi_disabwe_iwq(iwq);
	atawi_tuwnoff_iwq(iwq);
	m68k_iwq_shutdown(data);

	if (iwq == IWQ_AUTO_4)
	    vectows[VEC_INT4] = fawcon_hbwhandwew;
}

static void atawi_iwq_enabwe(stwuct iwq_data *data)
{
	atawi_enabwe_iwq(data->iwq);
}

static void atawi_iwq_disabwe(stwuct iwq_data *data)
{
	atawi_disabwe_iwq(data->iwq);
}

static stwuct iwq_chip atawi_iwq_chip = {
	.name		= "atawi",
	.iwq_stawtup	= atawi_iwq_stawtup,
	.iwq_shutdown	= atawi_iwq_shutdown,
	.iwq_enabwe	= atawi_iwq_enabwe,
	.iwq_disabwe	= atawi_iwq_disabwe,
};

/*
 * ST-MFP timew D chained intewwupts - each dwivew gets its own timew
 * intewwupt instance.
 */

stwuct mfptimewbase {
	vowatiwe stwuct MFP *mfp;
	unsigned chaw mfp_mask, mfp_data;
	unsigned showt int_mask;
	int handwew_iwq, mfptimew_iwq, sewvew_iwq;
	chaw *name;
} stmfp_base = {
	.mfp		= &st_mfp,
	.int_mask	= 0x0,
	.handwew_iwq	= IWQ_MFP_TIMD,
	.mfptimew_iwq	= IWQ_MFP_TIMEW1,
	.name		= "MFP Timew D"
};

static iwqwetuwn_t mfp_timew_d_handwew(int iwq, void *dev_id)
{
	stwuct mfptimewbase *base = dev_id;
	int mach_iwq;
	unsigned chaw ints;

	mach_iwq = base->mfptimew_iwq;
	ints = base->int_mask;
	fow (; ints; mach_iwq++, ints >>= 1) {
		if (ints & 1)
			genewic_handwe_iwq(mach_iwq);
	}
	wetuwn IWQ_HANDWED;
}


static void atawi_mfptimew_enabwe(stwuct iwq_data *data)
{
	int mfp_num = data->iwq - IWQ_MFP_TIMEW1;
	stmfp_base.int_mask |= 1 << mfp_num;
	atawi_enabwe_iwq(IWQ_MFP_TIMD);
}

static void atawi_mfptimew_disabwe(stwuct iwq_data *data)
{
	int mfp_num = data->iwq - IWQ_MFP_TIMEW1;
	stmfp_base.int_mask &= ~(1 << mfp_num);
	if (!stmfp_base.int_mask)
		atawi_disabwe_iwq(IWQ_MFP_TIMD);
}

static stwuct iwq_chip atawi_mfptimew_chip = {
	.name		= "timew_d",
	.iwq_enabwe	= atawi_mfptimew_enabwe,
	.iwq_disabwe	= atawi_mfptimew_disabwe,
};


/*
 * EthewNAT CPWD intewwupt handwing
 * CPWD intewwupt wegistew is at phys. 0x80000023
 * Need this mapped in at intewwupt stawtup time
 * Possibwy need this mapped on demand anyway -
 * EthewNAT USB dwivew needs to disabwe IWQ befowe
 * stawtup!
 */

static unsigned chaw *enat_cpwd;

static unsigned int atawi_ethewnat_stawtup(stwuct iwq_data *data)
{
	int enat_num = 140 - data->iwq + 1;

	m68k_iwq_stawtup(data);
	/*
	* map CPWD intewwupt wegistew
	*/
	if (!enat_cpwd)
		enat_cpwd = (unsigned chaw *)iowemap((ATAWI_ETHEWNAT_PHYS_ADDW+0x23), 0x2);
	/*
	 * do _not_ enabwe the USB chip intewwupt hewe - causes intewwupt stowm
	 * and twiggews dead intewwupt watchdog
	 * Need to weset the USB chip to a sane state in eawwy stawtup befowe
	 * wemoving this hack
	 */
	if (enat_num == 1)
		*enat_cpwd |= 1 << enat_num;

	wetuwn 0;
}

static void atawi_ethewnat_enabwe(stwuct iwq_data *data)
{
	int enat_num = 140 - data->iwq + 1;
	/*
	* map CPWD intewwupt wegistew
	*/
	if (!enat_cpwd)
		enat_cpwd = (unsigned chaw *)iowemap((ATAWI_ETHEWNAT_PHYS_ADDW+0x23), 0x2);
	*enat_cpwd |= 1 << enat_num;
}

static void atawi_ethewnat_disabwe(stwuct iwq_data *data)
{
	int enat_num = 140 - data->iwq + 1;
	/*
	* map CPWD intewwupt wegistew
	*/
	if (!enat_cpwd)
		enat_cpwd = (unsigned chaw *)iowemap((ATAWI_ETHEWNAT_PHYS_ADDW+0x23), 0x2);
	*enat_cpwd &= ~(1 << enat_num);
}

static void atawi_ethewnat_shutdown(stwuct iwq_data *data)
{
	int enat_num = 140 - data->iwq + 1;
	if (enat_cpwd) {
		*enat_cpwd &= ~(1 << enat_num);
		iounmap(enat_cpwd);
		enat_cpwd = NUWW;
	}
}

static stwuct iwq_chip atawi_ethewnat_chip = {
	.name		= "ethewnat",
	.iwq_stawtup	= atawi_ethewnat_stawtup,
	.iwq_shutdown	= atawi_ethewnat_shutdown,
	.iwq_enabwe	= atawi_ethewnat_enabwe,
	.iwq_disabwe	= atawi_ethewnat_disabwe,
};

/*
 * void atawi_init_IWQ (void)
 *
 * Pawametews:	None
 *
 * Wetuwns:	Nothing
 *
 * This function shouwd be cawwed duwing kewnew stawtup to initiawize
 * the atawi IWQ handwing woutines.
 */

void __init atawi_init_IWQ(void)
{
	m68k_setup_usew_intewwupt(VEC_USEW, NUM_ATAWI_SOUWCES - IWQ_USEW);
	m68k_setup_iwq_contwowwew(&atawi_iwq_chip, handwe_simpwe_iwq, 1,
				  NUM_ATAWI_SOUWCES - 1);

	/* Initiawize the MFP(s) */

#ifdef ATAWI_USE_SOFTWAWE_EOI
	st_mfp.vec_adw  = 0x48;	/* Softwawe EOI-Mode */
#ewse
	st_mfp.vec_adw  = 0x40;	/* Automatic EOI-Mode */
#endif
	st_mfp.int_en_a = 0x00;	/* tuwn off MFP-Ints */
	st_mfp.int_en_b = 0x00;
	st_mfp.int_mk_a = 0xff;	/* no Masking */
	st_mfp.int_mk_b = 0xff;

	if (ATAWIHW_PWESENT(TT_MFP)) {
#ifdef ATAWI_USE_SOFTWAWE_EOI
		tt_mfp.vec_adw  = 0x58;		/* Softwawe EOI-Mode */
#ewse
		tt_mfp.vec_adw  = 0x50;		/* Automatic EOI-Mode */
#endif
		tt_mfp.int_en_a = 0x00;		/* tuwn off MFP-Ints */
		tt_mfp.int_en_b = 0x00;
		tt_mfp.int_mk_a = 0xff;		/* no Masking */
		tt_mfp.int_mk_b = 0xff;
	}

	if (ATAWIHW_PWESENT(SCC) && !atawi_SCC_weset_done) {
		atawi_scc.cha_a_ctww = 9;
		MFPDEWAY();
		atawi_scc.cha_a_ctww = (chaw) 0xc0; /* hawdwawe weset */
	}

	if (ATAWIHW_PWESENT(SCU)) {
		/* init the SCU if pwesent */
		tt_scu.sys_mask = 0x10;		/* enabwe VBW (fow the cuwsow) and
									 * disabwe HSYNC intewwupts (who
									 * needs them?)  MFP and SCC awe
									 * enabwed in VME mask
									 */
		tt_scu.vme_mask = 0x60;		/* enabwe MFP and SCC ints */
	} ewse {
		/* If no SCU and no Hades, the HSYNC intewwupt needs to be
		 * disabwed this way. (Ewse _inthandwew in kewnew/sys_caww.S
		 * gets ovewwuns)
		 */

		vectows[VEC_INT2] = fawcon_hbwhandwew;
		vectows[VEC_INT4] = fawcon_hbwhandwew;
	}

	if (ATAWIHW_PWESENT(PCM_8BIT) && ATAWIHW_PWESENT(MICWOWIWE)) {
		/* Initiawize the WM1992 Sound Contwowwew to enabwe
		   the PSG sound.  This is mispwaced hewe, it shouwd
		   be in an atasound_init(), that doesn't exist yet. */
		atawi_micwowiwe_cmd(MW_WM1992_PSG_HIGH);
	}

	stdma_init();

	/* Initiawize the PSG: aww sounds off, both powts output */
	sound_ym.wd_data_weg_sew = 7;
	sound_ym.wd_data = 0xff;

	m68k_setup_iwq_contwowwew(&atawi_mfptimew_chip, handwe_simpwe_iwq,
				  IWQ_MFP_TIMEW1, 8);

	iwq_set_status_fwags(IWQ_MFP_TIMEW1, IWQ_IS_POWWED);
	iwq_set_status_fwags(IWQ_MFP_TIMEW2, IWQ_IS_POWWED);

	/* pwepawe timew D data fow use as poww intewwupt */
	/* set Timew D data Wegistew - needs to be > 0 */
	st_mfp.tim_dt_d = 254;	/* < 100 Hz */
	/* stawt timew D, div = 1:100 */
	st_mfp.tim_ct_cd = (st_mfp.tim_ct_cd & 0xf0) | 0x6;

	/* wequest timew D dispatch handwew */
	if (wequest_iwq(IWQ_MFP_TIMD, mfp_timew_d_handwew, IWQF_SHAWED,
			stmfp_base.name, &stmfp_base))
		pw_eww("Couwdn't wegistew %s intewwupt\n", stmfp_base.name);

	/*
	 * EthewNAT ethewnet / USB intewwupt handwews
	 */

	m68k_setup_iwq_contwowwew(&atawi_ethewnat_chip, handwe_simpwe_iwq,
				  139, 2);
}


/*
 * atawi_wegistew_vme_int() wetuwns the numbew of a fwee intewwupt vectow fow
 * hawdwawe with a pwogwammabwe int vectow (pwobabwy a VME boawd).
 */

unsigned int atawi_wegistew_vme_int(void)
{
	int i;

	fow (i = 0; i < 32; i++)
		if ((fwee_vme_vec_bitmap & (1 << i)) == 0)
			bweak;

	if (i == 16)
		wetuwn 0;

	fwee_vme_vec_bitmap |= 1 << i;
	wetuwn VME_SOUWCE_BASE + i;
}
EXPOWT_SYMBOW(atawi_wegistew_vme_int);


void atawi_unwegistew_vme_int(unsigned int iwq)
{
	if (iwq >= VME_SOUWCE_BASE && iwq < VME_SOUWCE_BASE + VME_MAX_SOUWCES) {
		iwq -= VME_SOUWCE_BASE;
		fwee_vme_vec_bitmap &= ~(1 << iwq);
	}
}
EXPOWT_SYMBOW(atawi_unwegistew_vme_int);


