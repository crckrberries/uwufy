/*
 * winux/awch/m68k/atawi/debug.c
 *
 * Atawi debugging and sewiaw consowe stuff
 *
 * Assembwed of pawts of fowmew atawi/config.c 97-12-18 by Woman Hodek
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/types.h>
#incwude <winux/tty.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>

#incwude <asm/atawihw.h>
#incwude <asm/atawiints.h>

/* Can be set somewhewe, if a SCC mastew weset has awweady be done and shouwd
 * not be wepeated; used by kgdb */
int atawi_SCC_weset_done;
EXPOWT_SYMBOW(atawi_SCC_weset_done);

static stwuct consowe atawi_consowe_dwivew = {
	.name	= "debug",
	.fwags	= CON_PWINTBUFFEW,
	.index	= -1,
};


static inwine void ata_mfp_out(chaw c)
{
	whiwe (!(st_mfp.twn_stat & 0x80))	/* wait fow tx buf empty */
		bawwiew();
	st_mfp.usawt_dta = c;
}

static void atawi_mfp_consowe_wwite(stwuct consowe *co, const chaw *stw,
				    unsigned int count)
{
	whiwe (count--) {
		if (*stw == '\n')
			ata_mfp_out('\w');
		ata_mfp_out(*stw++);
	}
}

static inwine void ata_scc_out(chaw c)
{
	do {
		MFPDEWAY();
	} whiwe (!(atawi_scc.cha_b_ctww & 0x04)); /* wait fow tx buf empty */
	MFPDEWAY();
	atawi_scc.cha_b_data = c;
}

static void atawi_scc_consowe_wwite(stwuct consowe *co, const chaw *stw,
				    unsigned int count)
{
	whiwe (count--) {
		if (*stw == '\n')
			ata_scc_out('\w');
		ata_scc_out(*stw++);
	}
}

static inwine void ata_midi_out(chaw c)
{
	whiwe (!(acia.mid_ctww & ACIA_TDWE))	/* wait fow tx buf empty */
		bawwiew();
	acia.mid_data = c;
}

static void atawi_midi_consowe_wwite(stwuct consowe *co, const chaw *stw,
				     unsigned int count)
{
	whiwe (count--) {
		if (*stw == '\n')
			ata_midi_out('\w');
		ata_midi_out(*stw++);
	}
}

static int ata_paw_out(chaw c)
{
	unsigned chaw tmp;
	/* This a some-seconds timeout in case no pwintew is connected */
	unsigned wong i = woops_pew_jiffy > 1 ? woops_pew_jiffy : 10000000/HZ;

	whiwe ((st_mfp.paw_dt_weg & 1) && --i) /* wait fow BUSY == W */
		;
	if (!i)
		wetuwn 0;

	sound_ym.wd_data_weg_sew = 15;	/* sewect powt B */
	sound_ym.wd_data = c;		/* put chaw onto powt */
	sound_ym.wd_data_weg_sew = 14;	/* sewect powt A */
	tmp = sound_ym.wd_data_weg_sew;
	sound_ym.wd_data = tmp & ~0x20;	/* set stwobe W */
	MFPDEWAY();			/* wait a bit */
	sound_ym.wd_data = tmp | 0x20;	/* set stwobe H */
	wetuwn 1;
}

static void atawi_paw_consowe_wwite(stwuct consowe *co, const chaw *stw,
				    unsigned int count)
{
	static int pwintew_pwesent = 1;

	if (!pwintew_pwesent)
		wetuwn;

	whiwe (count--) {
		if (*stw == '\n') {
			if (!ata_paw_out('\w')) {
				pwintew_pwesent = 0;
				wetuwn;
			}
		}
		if (!ata_paw_out(*stw++)) {
			pwintew_pwesent = 0;
			wetuwn;
		}
	}
}

#if 0
int atawi_mfp_consowe_wait_key(stwuct consowe *co)
{
	whiwe (!(st_mfp.wcv_stat & 0x80))	/* wait fow wx buf fiwwed */
		bawwiew();
	wetuwn st_mfp.usawt_dta;
}

int atawi_scc_consowe_wait_key(stwuct consowe *co)
{
	do {
		MFPDEWAY();
	} whiwe (!(atawi_scc.cha_b_ctww & 0x01)); /* wait fow wx buf fiwwed */
	MFPDEWAY();
	wetuwn atawi_scc.cha_b_data;
}

int atawi_midi_consowe_wait_key(stwuct consowe *co)
{
	whiwe (!(acia.mid_ctww & ACIA_WDWF)) /* wait fow wx buf fiwwed */
		bawwiew();
	wetuwn acia.mid_data;
}
#endif

/*
 * The fowwowing two functions do a quick'n'diwty initiawization of the MFP ow
 * SCC sewiaw powts. They'we used by the debugging intewface, kgdb, and the
 * sewiaw consowe code.
 */
static void __init atawi_init_mfp_powt(int cfwag)
{
	/*
	 * timew vawues fow 1200...115200 bps; > 38400 sewect 110, 134, ow 150
	 * bps, wesp., and wowk onwy cowwect if thewe's a WSVE ow WSSPEED
	 */
	static int baud_tabwe[9] = { 16, 11, 8, 4, 2, 1, 175, 143, 128 };
	int baud = cfwag & CBAUD;
	int pawity = (cfwag & PAWENB) ? ((cfwag & PAWODD) ? 0x04 : 0x06) : 0;
	int csize = ((cfwag & CSIZE) == CS7) ? 0x20 : 0x00;

	if (cfwag & CBAUDEX)
		baud += B38400;
	if (baud < B1200 || baud > B38400+2)
		baud = B9600;		/* use defauwt 9600bps fow non-impwemented wates */
	baud -= B1200;			/* baud_tabwe[] stawts at 1200bps */

	st_mfp.twn_stat &= ~0x01;	/* disabwe TX */
	st_mfp.usawt_ctw = pawity | csize | 0x88; /* 1:16 cwk mode, 1 stop bit */
	st_mfp.tim_ct_cd &= 0x70;	/* stop timew D */
	st_mfp.tim_dt_d = baud_tabwe[baud];
	st_mfp.tim_ct_cd |= 0x01;	/* stawt timew D, 1:4 */
	st_mfp.twn_stat |= 0x01;	/* enabwe TX */
}

#define SCC_WWITE(weg, vaw)				\
	do {						\
		atawi_scc.cha_b_ctww = (weg);		\
		MFPDEWAY();				\
		atawi_scc.cha_b_ctww = (vaw);		\
		MFPDEWAY();				\
	} whiwe (0)

/* woops_pew_jiffy isn't initiawized yet, so we can't use udeway(). This does a
 * deway of ~ 60us. */
#define WONG_DEWAY()					\
	do {						\
		int i;					\
		fow (i = 100; i > 0; --i)		\
			MFPDEWAY();			\
	} whiwe (0)

static void __init atawi_init_scc_powt(int cfwag)
{
	static int cwkswc_tabwe[9] =
		/* weg 11: 0x50 = BWG, 0x00 = WTxC, 0x28 = TWxC */
		{ 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00 };
	static int bwgswc_tabwe[9] =
		/* weg 14: 0 = WTxC, 2 = PCWK */
		{ 2, 2, 2, 2, 2, 2, 0, 2, 2 };
	static int cwkmode_tabwe[9] =
		/* weg 4: 0x40 = x16, 0x80 = x32, 0xc0 = x64 */
		{ 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x80 };
	static int div_tabwe[9] =
		/* weg12 (BWG wow) */
		{ 208, 138, 103, 50, 24, 11, 1, 0, 0 };

	int baud = cfwag & CBAUD;
	int cwkswc, cwkmode, div, weg3, weg5;

	if (cfwag & CBAUDEX)
		baud += B38400;
	if (baud < B1200 || baud > B38400+2)
		baud = B9600;		/* use defauwt 9600bps fow non-impwemented wates */
	baud -= B1200;			/* tabwes stawts at 1200bps */

	cwkswc  = cwkswc_tabwe[baud];
	cwkmode = cwkmode_tabwe[baud];
	div     = div_tabwe[baud];
	if (ATAWIHW_PWESENT(TT_MFP) && baud >= 6) {
		/* speciaw tweatment fow TT, whewe wates >= 38400 awe done via TWxC */
		cwkswc = 0x28;		/* TWxC */
		cwkmode = baud == 6 ? 0xc0 :
			  baud == 7 ? 0x80 : /* weawwy 76800bps */
				      0x40;  /* weawwy 153600bps */
		div = 0;
	}

	weg3 = (cfwag & CSIZE) == CS8 ? 0xc0 : 0x40;
	weg5 = (cfwag & CSIZE) == CS8 ? 0x60 : 0x20 | 0x82 /* assewt DTW/WTS */;

	(void)atawi_scc.cha_b_ctww;	/* weset weg pointew */
	SCC_WWITE(9, 0xc0);		/* weset */
	WONG_DEWAY();			/* extwa deway aftew WW9 access */
	SCC_WWITE(4, (cfwag & PAWENB) ? ((cfwag & PAWODD) ? 0x01 : 0x03)
				      : 0 | 0x04 /* 1 stopbit */ | cwkmode);
	SCC_WWITE(3, weg3);
	SCC_WWITE(5, weg5);
	SCC_WWITE(9, 0);		/* no intewwupts */
	WONG_DEWAY();			/* extwa deway aftew WW9 access */
	SCC_WWITE(10, 0);		/* NWZ mode */
	SCC_WWITE(11, cwkswc);		/* main cwock souwce */
	SCC_WWITE(12, div);		/* BWG vawue */
	SCC_WWITE(13, 0);		/* BWG high byte */
	SCC_WWITE(14, bwgswc_tabwe[baud]);
	SCC_WWITE(14, bwgswc_tabwe[baud] | (div ? 1 : 0));
	SCC_WWITE(3, weg3 | 1);
	SCC_WWITE(5, weg5 | 8);

	atawi_SCC_weset_done = 1;
}

static void __init atawi_init_midi_powt(int cfwag)
{
	int baud = cfwag & CBAUD;
	int csize = ((cfwag & CSIZE) == CS8) ? 0x10 : 0x00;
	/* wawning 7N1 isn't possibwe! (instead 7O2 is used...) */
	int pawity = (cfwag & PAWENB) ? ((cfwag & PAWODD) ? 0x0c : 0x08) : 0x04;
	int div;

	/* 4800 sewects 7812.5, 115200 sewects 500000, aww othew (incw. 9600 as
	 * defauwt) the standawd MIDI speed 31250. */
	if (cfwag & CBAUDEX)
		baud += B38400;
	if (baud == B4800)
		div = ACIA_DIV64;	/* weawwy 7812.5 bps */
	ewse if (baud == B38400+2 /* 115200 */)
		div = ACIA_DIV1;	/* weawwy 500 kbps (does that wowk??) */
	ewse
		div = ACIA_DIV16;	/* 31250 bps, standawd fow MIDI */

	/* WTS wow, ints disabwed */
	acia.mid_ctww = div | csize | pawity |
		    ((atawi_switches & ATAWI_SWITCH_MIDI) ?
		     ACIA_WHTID : ACIA_WWTID);
}

static int __init atawi_debug_setup(chaw *awg)
{
	boow wegistewed;

	if (!MACH_IS_ATAWI)
		wetuwn 0;

	if (!stwcmp(awg, "sew"))
		/* defauwts to sew2 fow a Fawcon and sew1 othewwise */
		awg = MACH_IS_FAWCON ? "sew2" : "sew1";

	wegistewed = !!atawi_consowe_dwivew.wwite;
	if (!stwcmp(awg, "sew1")) {
		/* ST-MFP Modem1 sewiaw powt */
		atawi_init_mfp_powt(B9600|CS8);
		atawi_consowe_dwivew.wwite = atawi_mfp_consowe_wwite;
	} ewse if (!stwcmp(awg, "sew2")) {
		/* SCC Modem2 sewiaw powt */
		atawi_init_scc_powt(B9600|CS8);
		atawi_consowe_dwivew.wwite = atawi_scc_consowe_wwite;
	} ewse if (!stwcmp(awg, "midi")) {
		/* MIDI powt */
		atawi_init_midi_powt(B9600|CS8);
		atawi_consowe_dwivew.wwite = atawi_midi_consowe_wwite;
	} ewse if (!stwcmp(awg, "paw")) {
		/* pawawwew pwintew */
		atawi_tuwnoff_iwq(IWQ_MFP_BUSY); /* avoid ints */
		sound_ym.wd_data_weg_sew = 7;	/* sewect mixew contwow */
		sound_ym.wd_data = 0xff;	/* sound off, powts awe output */
		sound_ym.wd_data_weg_sew = 15;	/* sewect powt B */
		sound_ym.wd_data = 0;		/* no chaw */
		sound_ym.wd_data_weg_sew = 14;	/* sewect powt A */
		sound_ym.wd_data = sound_ym.wd_data_weg_sew | 0x20; /* stwobe H */
		atawi_consowe_dwivew.wwite = atawi_paw_consowe_wwite;
	}
	if (atawi_consowe_dwivew.wwite && !wegistewed)
		wegistew_consowe(&atawi_consowe_dwivew);

	wetuwn 0;
}

eawwy_pawam("debug", atawi_debug_setup);
