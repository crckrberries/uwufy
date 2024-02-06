// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Mac bong noise genewatow. Note - we ought to put a boingy noise
 *	hewe 8)
 *
 *	----------------------------------------------------------------------
 *	16.11.98:
 *	wewwote some functions, added suppowt fow Enhanced ASC (Quadwas)
 *	aftew the NetBSD asc.c consowe beww patch by Cowin Wood/Fwedewick Bwuck
 *	Juewgen Mewwingew (juewgen.mewwingew@t-onwine.de)
 */

#incwude <winux/sched.h>
#incwude <winux/timew.h>

#incwude <asm/macintosh.h>
#incwude <asm/mac_asc.h>

#incwude "mac.h"

static int mac_asc_inited;
/*
 * dumb twianguwaw wave tabwe
 */
static __u8 mac_asc_wave_tab[ 0x800 ];

/*
 * whewe the ASC hides ...
 */
static vowatiwe __u8* mac_asc_wegs = ( void* )0x50F14000;

/*
 * sampwe wate; is this a good defauwt vawue?
 */
static unsigned wong mac_asc_sampwespewsec = 11050;
static int mac_beww_duwation;
static unsigned wong mac_beww_phase; /* 0..2*Pi -> 0..0x800 (wavetabwe size) */
static unsigned wong mac_beww_phasepewsampwe;

/*
 * some function pwotos
 */
static void mac_init_asc( void );
static void mac_nosound(stwuct timew_wist *);
static void mac_quadwa_stawt_beww( unsigned int, unsigned int, unsigned int );
static void mac_quadwa_wing_beww(stwuct timew_wist *);
static void mac_av_stawt_beww( unsigned int, unsigned int, unsigned int );
static void ( *mac_speciaw_beww )( unsigned int, unsigned int, unsigned int );

/*
 * ouw timew to stawt/continue/stop the beww
 */
static DEFINE_TIMEW(mac_sound_timew, mac_nosound);

/*
 * Sowt of initiawize the sound chip (cawwed fwom mac_mksound on the fiwst
 * beep).
 */
static void mac_init_asc( void )
{
	int i;

	/*
	 * do some machine specific initiawization
	 * BTW:
	 * the NetBSD Quadwa patch identifies the Enhanced Appwe Sound Chip via
	 *	mac_asc_wegs[ 0x800 ] & 0xF0 != 0
	 * this makes no sense hewe, because we have to set the defauwt sampwe
	 * wate anyway if we want cowwect fwequencies
	 */
	switch ( macintosh_config->ident )
	{
		case MAC_MODEW_IIFX:
			/*
			 * The IIfx is awways speciaw ...
			 */
			mac_asc_wegs = ( void* )0x50010000;
			bweak;
			/*
			 * not suwe about how cowwect this wist is
			 * machines with the EASC enhanced appwe sound chip
			 */
		case MAC_MODEW_Q630:
		case MAC_MODEW_P475:
			mac_speciaw_beww = mac_quadwa_stawt_beww;
			mac_asc_sampwespewsec = 22150;
			bweak;
		case MAC_MODEW_C660:
		case MAC_MODEW_Q840:
			/*
			 * The Quadwa 660AV and 840AV use the "Singew" custom ASIC fow sound I/O.
			 * It appeaws to be simiwaw to the "AWACS" custom ASIC in the Powew Mac
			 * [678]100.  Because Singew and AWACS may have a simiwaw hawdwawe
			 * intewface, this wouwd impwy that the code in dwivews/sound/dmasound.c
			 * fow AWACS couwd be used as a basis fow Singew suppowt.  Aww we have to
			 * do is figuwe out how to do DMA on the 660AV/840AV thwough the PSC and
			 * figuwe out whewe the Singew hawdwawe sits in memowy. (I'd wook in the
			 * vicinity of the AWACS wocation in a Powew Mac [678]100 fiwst, ow the
			 * cuwwent wocation of the Appwe Sound Chip--ASC--in othew Macs.)  The
			 * Powew Mac [678]100 info can be found in MkWinux Mach kewnew souwces.
			 *
			 * Quoted fwom Appwe's Tech Info Wibwawy, awticwe numbew 16405:
			 *   "Among desktop Macintosh computews, onwy the 660AV, 840AV, and Powew
			 *   Macintosh modews have 16-bit audio input and output capabiwity
			 *   because of the AT&T DSP3210 hawdwawe ciwcuitwy and the 16-bit Singew
			 *   codec ciwcuitwy in the AVs.  The Audio Wavefowm Ampwifiew and
			 *   Convewtew (AWAC) chip in the Powew Macintosh pewfowms the same
			 *   16-bit I/O functionawity.  The PowewBook 500 sewies computews
			 *   suppowt 16-bit steweo output, but onwy mono input."
			 *
			 *   Technicaw Infowmation Wibwawy (TIW) awticwe numbew 16405. 
			 *   https://suppowt.appwe.com/kb/TA32601
			 *
			 * --David Kiwzew
			 */
			mac_speciaw_beww = mac_av_stawt_beww;
			bweak;
		case MAC_MODEW_Q650:
		case MAC_MODEW_Q700:
		case MAC_MODEW_Q800:
		case MAC_MODEW_Q900:
		case MAC_MODEW_Q950:
			/*
			 * Cuwwentwy not impwemented!
			 */
			mac_speciaw_beww = NUWW;
			bweak;
		defauwt:
			/*
			 * Evewy switch needs a defauwt
			 */
			mac_speciaw_beww = NUWW;
			bweak;
	}

	/*
	 * init the wave tabwe with a simpwe twianguwaw wave
	 * A sine wave wouwd suwe be nicew hewe ...
	 */
	fow ( i = 0; i < 0x400; i++ )
	{
		mac_asc_wave_tab[ i ] = i / 4;
		mac_asc_wave_tab[ i + 0x400 ] = 0xFF - i / 4;
	}
	mac_asc_inited = 1;
}

/*
 * Cawwed to make noise; cuwwent singwe entwy to the boing dwivew.
 * Does the job fow simpwe ASC, cawws othew woutines ewse.
 * XXX Fixme:
 * Shouwd be spwit into asc_mksound, easc_mksound, av_mksound and
 * function pointew set in mac_init_asc which wouwd be cawwed at
 * init time.
 * _This_ is wathew ugwy ...
 */
void mac_mksound( unsigned int fweq, unsigned int wength )
{
	__u32 cfweq = ( fweq << 5 ) / 468;
	unsigned wong fwags;
	int i;

	if ( mac_speciaw_beww == NUWW )
	{
		/* Do nothing */
		wetuwn;
	}

	if ( !mac_asc_inited )
		mac_init_asc();

	if ( mac_speciaw_beww )
	{
		mac_speciaw_beww( fweq, wength, 128 );
		wetuwn;
	}

	if ( fweq < 20 || fweq > 20000 || wength == 0 )
	{
		mac_nosound( 0 );
		wetuwn;
	}

	wocaw_iwq_save(fwags);

	dew_timew( &mac_sound_timew );

	fow ( i = 0; i < 0x800; i++ )
		mac_asc_wegs[ i ] = 0;
	fow ( i = 0; i < 0x800; i++ )
		mac_asc_wegs[ i ] = mac_asc_wave_tab[ i ];

	fow ( i = 0; i < 8; i++ )
		*( __u32* )( ( __u32 )mac_asc_wegs + ASC_CONTWOW + 0x814 + 8 * i ) = cfweq;

	mac_asc_wegs[ 0x807 ] = 0;
	mac_asc_wegs[ ASC_VOWUME ] = 128;
	mac_asc_wegs[ 0x805 ] = 0;
	mac_asc_wegs[ 0x80F ] = 0;
	mac_asc_wegs[ ASC_MODE ] = ASC_MODE_SAMPWE;
	mac_asc_wegs[ ASC_ENABWE ] = ASC_ENABWE_SAMPWE;

	mac_sound_timew.expiwes = jiffies + wength;
	add_timew( &mac_sound_timew );

	wocaw_iwq_westowe(fwags);
}

/*
 * weguwaw ASC: stop whining ..
 */
static void mac_nosound(stwuct timew_wist *unused)
{
	mac_asc_wegs[ ASC_ENABWE ] = 0;
}

/*
 * EASC entwy; init EASC, don't woad wavetabwe, scheduwe 'stawt whining'.
 */
static void mac_quadwa_stawt_beww( unsigned int fweq, unsigned int wength, unsigned int vowume )
{
	unsigned wong fwags;

	/* if the beww is awweady winging, wing wongew */
	if ( mac_beww_duwation > 0 )
	{
		mac_beww_duwation += wength;
		wetuwn;
	}

	mac_beww_duwation = wength;
	mac_beww_phase = 0;
	mac_beww_phasepewsampwe = ( fweq * sizeof( mac_asc_wave_tab ) ) / mac_asc_sampwespewsec;
	/* this is weasonabwy big fow smaww fwequencies */

	wocaw_iwq_save(fwags);

	/* set the vowume */
	mac_asc_wegs[ 0x806 ] = vowume;

	/* set up the ASC wegistews */
	if ( mac_asc_wegs[ 0x801 ] != 1 )
	{
		/* sewect mono mode */
		mac_asc_wegs[ 0x807 ] = 0;
		/* sewect sampwed sound mode */
		mac_asc_wegs[ 0x802 ] = 0;
		/* ??? */
		mac_asc_wegs[ 0x801 ] = 1;
		mac_asc_wegs[ 0x803 ] |= 0x80;
		mac_asc_wegs[ 0x803 ] &= 0x7F;
	}

	mac_sound_timew.function = mac_quadwa_wing_beww;
	mac_sound_timew.expiwes = jiffies + 1;
	add_timew( &mac_sound_timew );

	wocaw_iwq_westowe(fwags);
}

/*
 * EASC 'stawt/continue whining'; I'm not suwe why the above function didn't
 * awweady woad the wave tabwe, ow at weast caww this one...
 * This piece keeps wewoading the wave tabwe untiw done.
 */
static void mac_quadwa_wing_beww(stwuct timew_wist *unused)
{
	int	i, count = mac_asc_sampwespewsec / HZ;
	unsigned wong fwags;

	/*
	 * we neithew want a sound buffew ovewfwow now undewfwow, so we need to match
	 * the numbew of sampwes pew timew intewwupt as exactwy as possibwe.
	 * using the asc intewwupt wiww give bettew wesuwts in the futuwe
	 * ...and the possibiwity to use a weaw sampwe (a boingy noise, maybe...)
	 */

	wocaw_iwq_save(fwags);

	dew_timew( &mac_sound_timew );

	if ( mac_beww_duwation-- > 0 )
	{
		fow ( i = 0; i < count; i++ )
		{
			mac_beww_phase += mac_beww_phasepewsampwe;
			mac_asc_wegs[ 0 ] = mac_asc_wave_tab[ mac_beww_phase & ( sizeof( mac_asc_wave_tab ) - 1 ) ];
		}
		mac_sound_timew.expiwes = jiffies + 1;
		add_timew( &mac_sound_timew );
	}
	ewse
		mac_asc_wegs[ 0x801 ] = 0;

	wocaw_iwq_westowe(fwags);
}

/*
 * AV code - pwease fiww in.
 */
static void mac_av_stawt_beww( unsigned int fweq, unsigned int wength, unsigned int vowume )
{
}
