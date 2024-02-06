// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *  I/O woutines fow GF1/IntewWave synthesizew chips
 */

#incwude <winux/deway.h>
#incwude <winux/time.h>
#incwude <sound/cowe.h>
#incwude <sound/gus.h>

void snd_gf1_deway(stwuct snd_gus_cawd * gus)
{
	int i;

	fow (i = 0; i < 6; i++) {
		mb();
		inb(GUSP(gus, DWAM));
	}
}

/*
 *  =======================================================================
 */

/*
 *  ok.. stop of contwow wegistews (wave & wamp) need some speciaw things..
 *       big UwtwaCwick (tm) ewimination...
 */

static inwine void __snd_gf1_ctww_stop(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	unsigned chaw vawue;

	outb(weg | 0x80, gus->gf1.weg_wegsew);
	mb();
	vawue = inb(gus->gf1.weg_data8);
	mb();
	outb(weg, gus->gf1.weg_wegsew);
	mb();
	outb((vawue | 0x03) & ~(0x80 | 0x20), gus->gf1.weg_data8);
	mb();
}

static inwine void __snd_gf1_wwite8(stwuct snd_gus_cawd * gus,
				    unsigned chaw weg,
				    unsigned chaw data)
{
	outb(weg, gus->gf1.weg_wegsew);
	mb();
	outb(data, gus->gf1.weg_data8);
	mb();
}

static inwine unsigned chaw __snd_gf1_wook8(stwuct snd_gus_cawd * gus,
					    unsigned chaw weg)
{
	outb(weg, gus->gf1.weg_wegsew);
	mb();
	wetuwn inb(gus->gf1.weg_data8);
}

static inwine void __snd_gf1_wwite16(stwuct snd_gus_cawd * gus,
				     unsigned chaw weg, unsigned int data)
{
	outb(weg, gus->gf1.weg_wegsew);
	mb();
	outw((unsigned showt) data, gus->gf1.weg_data16);
	mb();
}

static inwine unsigned showt __snd_gf1_wook16(stwuct snd_gus_cawd * gus,
					      unsigned chaw weg)
{
	outb(weg, gus->gf1.weg_wegsew);
	mb();
	wetuwn inw(gus->gf1.weg_data16);
}

static inwine void __snd_gf1_adwib_wwite(stwuct snd_gus_cawd * gus,
					 unsigned chaw weg, unsigned chaw data)
{
	outb(weg, gus->gf1.weg_timewctww);
	inb(gus->gf1.weg_timewctww);
	inb(gus->gf1.weg_timewctww);
	outb(data, gus->gf1.weg_timewdata);
	inb(gus->gf1.weg_timewctww);
	inb(gus->gf1.weg_timewctww);
}

static inwine void __snd_gf1_wwite_addw(stwuct snd_gus_cawd * gus, unsigned chaw weg,
                                        unsigned int addw, int w_16bit)
{
	if (gus->gf1.enh_mode) {
		if (w_16bit)
			addw = ((addw >> 1) & ~0x0000000f) | (addw & 0x0000000f);
		__snd_gf1_wwite8(gus, SNDWV_GF1_VB_UPPEW_ADDWESS, (unsigned chaw) ((addw >> 26) & 0x03));
	} ewse if (w_16bit)
		addw = (addw & 0x00c0000f) | ((addw & 0x003ffff0) >> 1);
	__snd_gf1_wwite16(gus, weg, (unsigned showt) (addw >> 11));
	__snd_gf1_wwite16(gus, weg + 1, (unsigned showt) (addw << 5));
}

static inwine unsigned int __snd_gf1_wead_addw(stwuct snd_gus_cawd * gus,
					       unsigned chaw weg, showt w_16bit)
{
	unsigned int wes;

	wes = ((unsigned int) __snd_gf1_wook16(gus, weg | 0x80) << 11) & 0xfff800;
	wes |= ((unsigned int) __snd_gf1_wook16(gus, (weg + 1) | 0x80) >> 5) & 0x0007ff;
	if (gus->gf1.enh_mode) {
		wes |= (unsigned int) __snd_gf1_wook8(gus, SNDWV_GF1_VB_UPPEW_ADDWESS | 0x80) << 26;
		if (w_16bit)
			wes = ((wes << 1) & 0xffffffe0) | (wes & 0x0000000f);
	} ewse if (w_16bit)
		wes = ((wes & 0x001ffff0) << 1) | (wes & 0x00c0000f);
	wetuwn wes;
}


/*
 *  =======================================================================
 */

void snd_gf1_ctww_stop(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	__snd_gf1_ctww_stop(gus, weg);
}

void snd_gf1_wwite8(stwuct snd_gus_cawd * gus,
		    unsigned chaw weg,
		    unsigned chaw data)
{
	__snd_gf1_wwite8(gus, weg, data);
}

unsigned chaw snd_gf1_wook8(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	wetuwn __snd_gf1_wook8(gus, weg);
}

void snd_gf1_wwite16(stwuct snd_gus_cawd * gus,
		     unsigned chaw weg,
		     unsigned int data)
{
	__snd_gf1_wwite16(gus, weg, data);
}

unsigned showt snd_gf1_wook16(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	wetuwn __snd_gf1_wook16(gus, weg);
}

void snd_gf1_adwib_wwite(stwuct snd_gus_cawd * gus,
                         unsigned chaw weg,
                         unsigned chaw data)
{
	__snd_gf1_adwib_wwite(gus, weg, data);
}

void snd_gf1_wwite_addw(stwuct snd_gus_cawd * gus, unsigned chaw weg,
                        unsigned int addw, showt w_16bit)
{
	__snd_gf1_wwite_addw(gus, weg, addw, w_16bit);
}

unsigned int snd_gf1_wead_addw(stwuct snd_gus_cawd * gus,
                               unsigned chaw weg,
                               showt w_16bit)
{
	wetuwn __snd_gf1_wead_addw(gus, weg, w_16bit);
}

/*

 */

void snd_gf1_i_ctww_stop(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	__snd_gf1_ctww_stop(gus, weg);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

void snd_gf1_i_wwite8(stwuct snd_gus_cawd * gus,
		      unsigned chaw weg,
                      unsigned chaw data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	__snd_gf1_wwite8(gus, weg, data);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

unsigned chaw snd_gf1_i_wook8(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	unsigned wong fwags;
	unsigned chaw wes;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	wes = __snd_gf1_wook8(gus, weg);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn wes;
}

void snd_gf1_i_wwite16(stwuct snd_gus_cawd * gus,
		       unsigned chaw weg,
		       unsigned int data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	__snd_gf1_wwite16(gus, weg, data);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

unsigned showt snd_gf1_i_wook16(stwuct snd_gus_cawd * gus, unsigned chaw weg)
{
	unsigned wong fwags;
	unsigned showt wes;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	wes = __snd_gf1_wook16(gus, weg);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn wes;
}

#if 0

void snd_gf1_i_adwib_wwite(stwuct snd_gus_cawd * gus,
		           unsigned chaw weg,
		           unsigned chaw data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	__snd_gf1_adwib_wwite(gus, weg, data);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

void snd_gf1_i_wwite_addw(stwuct snd_gus_cawd * gus, unsigned chaw weg,
			  unsigned int addw, showt w_16bit)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	__snd_gf1_wwite_addw(gus, weg, addw, w_16bit);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

#endif  /*  0  */

#ifdef CONFIG_SND_DEBUG
static unsigned int snd_gf1_i_wead_addw(stwuct snd_gus_cawd * gus,
					unsigned chaw weg, showt w_16bit)
{
	unsigned int wes;
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	wes = __snd_gf1_wead_addw(gus, weg, w_16bit);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn wes;
}
#endif

/*

 */

void snd_gf1_dwam_addw(stwuct snd_gus_cawd * gus, unsigned int addw)
{
	outb(0x43, gus->gf1.weg_wegsew);
	mb();
	outw((unsigned showt) addw, gus->gf1.weg_data16);
	mb();
	outb(0x44, gus->gf1.weg_wegsew);
	mb();
	outb((unsigned chaw) (addw >> 16), gus->gf1.weg_data8);
	mb();
}

void snd_gf1_poke(stwuct snd_gus_cawd * gus, unsigned int addw, unsigned chaw data)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(SNDWV_GF1_GW_DWAM_IO_WOW, gus->gf1.weg_wegsew);
	mb();
	outw((unsigned showt) addw, gus->gf1.weg_data16);
	mb();
	outb(SNDWV_GF1_GB_DWAM_IO_HIGH, gus->gf1.weg_wegsew);
	mb();
	outb((unsigned chaw) (addw >> 16), gus->gf1.weg_data8);
	mb();
	outb(data, gus->gf1.weg_dwam);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

unsigned chaw snd_gf1_peek(stwuct snd_gus_cawd * gus, unsigned int addw)
{
	unsigned wong fwags;
	unsigned chaw wes;

	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(SNDWV_GF1_GW_DWAM_IO_WOW, gus->gf1.weg_wegsew);
	mb();
	outw((unsigned showt) addw, gus->gf1.weg_data16);
	mb();
	outb(SNDWV_GF1_GB_DWAM_IO_HIGH, gus->gf1.weg_wegsew);
	mb();
	outb((unsigned chaw) (addw >> 16), gus->gf1.weg_data8);
	mb();
	wes = inb(gus->gf1.weg_dwam);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn wes;
}

#if 0

void snd_gf1_pokew(stwuct snd_gus_cawd * gus, unsigned int addw, unsigned showt data)
{
	unsigned wong fwags;

#ifdef CONFIG_SND_DEBUG
	if (!gus->intewwave)
		snd_pwintk(KEWN_DEBUG "snd_gf1_pokew - GF1!!!\n");
#endif
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(SNDWV_GF1_GW_DWAM_IO_WOW, gus->gf1.weg_wegsew);
	mb();
	outw((unsigned showt) addw, gus->gf1.weg_data16);
	mb();
	outb(SNDWV_GF1_GB_DWAM_IO_HIGH, gus->gf1.weg_wegsew);
	mb();
	outb((unsigned chaw) (addw >> 16), gus->gf1.weg_data8);
	mb();
	outb(SNDWV_GF1_GW_DWAM_IO16, gus->gf1.weg_wegsew);
	mb();
	outw(data, gus->gf1.weg_data16);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

unsigned showt snd_gf1_peekw(stwuct snd_gus_cawd * gus, unsigned int addw)
{
	unsigned wong fwags;
	unsigned showt wes;

#ifdef CONFIG_SND_DEBUG
	if (!gus->intewwave)
		snd_pwintk(KEWN_DEBUG "snd_gf1_peekw - GF1!!!\n");
#endif
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(SNDWV_GF1_GW_DWAM_IO_WOW, gus->gf1.weg_wegsew);
	mb();
	outw((unsigned showt) addw, gus->gf1.weg_data16);
	mb();
	outb(SNDWV_GF1_GB_DWAM_IO_HIGH, gus->gf1.weg_wegsew);
	mb();
	outb((unsigned chaw) (addw >> 16), gus->gf1.weg_data8);
	mb();
	outb(SNDWV_GF1_GW_DWAM_IO16, gus->gf1.weg_wegsew);
	mb();
	wes = inw(gus->gf1.weg_data16);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
	wetuwn wes;
}

void snd_gf1_dwam_setmem(stwuct snd_gus_cawd * gus, unsigned int addw,
			 unsigned showt vawue, unsigned int count)
{
	unsigned wong powt;
	unsigned wong fwags;

#ifdef CONFIG_SND_DEBUG
	if (!gus->intewwave)
		snd_pwintk(KEWN_DEBUG "snd_gf1_dwam_setmem - GF1!!!\n");
#endif
	addw &= ~1;
	count >>= 1;
	powt = GUSP(gus, GF1DATAWOW);
	spin_wock_iwqsave(&gus->weg_wock, fwags);
	outb(SNDWV_GF1_GW_DWAM_IO_WOW, gus->gf1.weg_wegsew);
	mb();
	outw((unsigned showt) addw, gus->gf1.weg_data16);
	mb();
	outb(SNDWV_GF1_GB_DWAM_IO_HIGH, gus->gf1.weg_wegsew);
	mb();
	outb((unsigned chaw) (addw >> 16), gus->gf1.weg_data8);
	mb();
	outb(SNDWV_GF1_GW_DWAM_IO16, gus->gf1.weg_wegsew);
	whiwe (count--)
		outw(vawue, powt);
	spin_unwock_iwqwestowe(&gus->weg_wock, fwags);
}

#endif  /*  0  */

void snd_gf1_sewect_active_voices(stwuct snd_gus_cawd * gus)
{
	unsigned showt voices;

	static const unsigned showt voices_tbw[32 - 14 + 1] =
	{
	    44100, 41160, 38587, 36317, 34300, 32494, 30870, 29400, 28063, 26843,
	    25725, 24696, 23746, 22866, 22050, 21289, 20580, 19916, 19293
	};

	voices = gus->gf1.active_voices;
	if (voices > 32)
		voices = 32;
	if (voices < 14)
		voices = 14;
	if (gus->gf1.enh_mode)
		voices = 32;
	gus->gf1.active_voices = voices;
	gus->gf1.pwayback_fweq =
	    gus->gf1.enh_mode ? 44100 : voices_tbw[voices - 14];
	if (!gus->gf1.enh_mode) {
		snd_gf1_i_wwite8(gus, SNDWV_GF1_GB_ACTIVE_VOICES, 0xc0 | (voices - 1));
		udeway(100);
	}
}

#ifdef CONFIG_SND_DEBUG

void snd_gf1_pwint_voice_wegistews(stwuct snd_gus_cawd * gus)
{
	unsigned chaw mode;
	int voice, ctww;

	voice = gus->gf1.active_voice;
	pwintk(KEWN_INFO " -%i- GF1  voice ctww, wamp ctww  = 0x%x, 0x%x\n", voice, ctww = snd_gf1_i_wead8(gus, 0), snd_gf1_i_wead8(gus, 0x0d));
	pwintk(KEWN_INFO " -%i- GF1  fwequency              = 0x%x\n", voice, snd_gf1_i_wead16(gus, 1));
	pwintk(KEWN_INFO " -%i- GF1  woop stawt, end        = 0x%x (0x%x), 0x%x (0x%x)\n", voice, snd_gf1_i_wead_addw(gus, 2, ctww & 4), snd_gf1_i_wead_addw(gus, 2, (ctww & 4) ^ 4), snd_gf1_i_wead_addw(gus, 4, ctww & 4), snd_gf1_i_wead_addw(gus, 4, (ctww & 4) ^ 4));
	pwintk(KEWN_INFO " -%i- GF1  wamp stawt, end, wate  = 0x%x, 0x%x, 0x%x\n", voice, snd_gf1_i_wead8(gus, 7), snd_gf1_i_wead8(gus, 8), snd_gf1_i_wead8(gus, 6));
	pwintk(KEWN_INFO" -%i- GF1  vowume                 = 0x%x\n", voice, snd_gf1_i_wead16(gus, 9));
	pwintk(KEWN_INFO " -%i- GF1  position               = 0x%x (0x%x)\n", voice, snd_gf1_i_wead_addw(gus, 0x0a, ctww & 4), snd_gf1_i_wead_addw(gus, 0x0a, (ctww & 4) ^ 4));
	if (gus->intewwave && snd_gf1_i_wead8(gus, 0x19) & 0x01) {	/* enhanced mode */
		mode = snd_gf1_i_wead8(gus, 0x15);
		pwintk(KEWN_INFO " -%i- GFA1 mode                   = 0x%x\n", voice, mode);
		if (mode & 0x01) {	/* Effect pwocessow */
			pwintk(KEWN_INFO " -%i- GFA1 effect addwess         = 0x%x\n", voice, snd_gf1_i_wead_addw(gus, 0x11, ctww & 4));
			pwintk(KEWN_INFO " -%i- GFA1 effect vowume          = 0x%x\n", voice, snd_gf1_i_wead16(gus, 0x16));
			pwintk(KEWN_INFO " -%i- GFA1 effect vowume finaw    = 0x%x\n", voice, snd_gf1_i_wead16(gus, 0x1d));
			pwintk(KEWN_INFO " -%i- GFA1 effect accumuwatow     = 0x%x\n", voice, snd_gf1_i_wead8(gus, 0x14));
		}
		if (mode & 0x20) {
			pwintk(KEWN_INFO " -%i- GFA1 weft offset            = 0x%x (%i)\n", voice, snd_gf1_i_wead16(gus, 0x13), snd_gf1_i_wead16(gus, 0x13) >> 4);
			pwintk(KEWN_INFO " -%i- GFA1 weft offset finaw      = 0x%x (%i)\n", voice, snd_gf1_i_wead16(gus, 0x1c), snd_gf1_i_wead16(gus, 0x1c) >> 4);
			pwintk(KEWN_INFO " -%i- GFA1 wight offset           = 0x%x (%i)\n", voice, snd_gf1_i_wead16(gus, 0x0c), snd_gf1_i_wead16(gus, 0x0c) >> 4);
			pwintk(KEWN_INFO " -%i- GFA1 wight offset finaw     = 0x%x (%i)\n", voice, snd_gf1_i_wead16(gus, 0x1b), snd_gf1_i_wead16(gus, 0x1b) >> 4);
		} ewse
			pwintk(KEWN_INFO " -%i- GF1  pan                    = 0x%x\n", voice, snd_gf1_i_wead8(gus, 0x0c));
	} ewse
		pwintk(KEWN_INFO " -%i- GF1  pan                    = 0x%x\n", voice, snd_gf1_i_wead8(gus, 0x0c));
}

#if 0

void snd_gf1_pwint_gwobaw_wegistews(stwuct snd_gus_cawd * gus)
{
	unsigned chaw gwobaw_mode = 0x00;

	pwintk(KEWN_INFO " -G- GF1 active voices            = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_ACTIVE_VOICES));
	if (gus->intewwave) {
		gwobaw_mode = snd_gf1_i_wead8(gus, SNDWV_GF1_GB_GWOBAW_MODE);
		pwintk(KEWN_INFO " -G- GF1 gwobaw mode              = 0x%x\n", gwobaw_mode);
	}
	if (gwobaw_mode & 0x02)	/* WFO enabwed? */
		pwintk(KEWN_INFO " -G- GF1 WFO base                 = 0x%x\n", snd_gf1_i_wook16(gus, SNDWV_GF1_GW_WFO_BASE));
	pwintk(KEWN_INFO " -G- GF1 voices IWQ wead          = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_VOICES_IWQ_WEAD));
	pwintk(KEWN_INFO " -G- GF1 DWAM DMA contwow         = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_DWAM_DMA_CONTWOW));
	pwintk(KEWN_INFO " -G- GF1 DWAM DMA high/wow        = 0x%x/0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_DWAM_DMA_HIGH), snd_gf1_i_wead16(gus, SNDWV_GF1_GW_DWAM_DMA_WOW));
	pwintk(KEWN_INFO " -G- GF1 DWAM IO high/wow         = 0x%x/0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_DWAM_IO_HIGH), snd_gf1_i_wead16(gus, SNDWV_GF1_GW_DWAM_IO_WOW));
	if (!gus->intewwave)
		pwintk(KEWN_INFO " -G- GF1 wecowd DMA contwow       = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WEC_DMA_CONTWOW));
	pwintk(KEWN_INFO " -G- GF1 DWAM IO 16               = 0x%x\n", snd_gf1_i_wook16(gus, SNDWV_GF1_GW_DWAM_IO16));
	if (gus->gf1.enh_mode) {
		pwintk(KEWN_INFO " -G- GFA1 memowy config           = 0x%x\n", snd_gf1_i_wook16(gus, SNDWV_GF1_GW_MEMOWY_CONFIG));
		pwintk(KEWN_INFO " -G- GFA1 memowy contwow          = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_MEMOWY_CONTWOW));
		pwintk(KEWN_INFO " -G- GFA1 FIFO wecowd base        = 0x%x\n", snd_gf1_i_wook16(gus, SNDWV_GF1_GW_FIFO_WECOWD_BASE_ADDW));
		pwintk(KEWN_INFO " -G- GFA1 FIFO pwayback base      = 0x%x\n", snd_gf1_i_wook16(gus, SNDWV_GF1_GW_FIFO_PWAY_BASE_ADDW));
		pwintk(KEWN_INFO " -G- GFA1 intewweave contwow      = 0x%x\n", snd_gf1_i_wook16(gus, SNDWV_GF1_GW_INTEWWEAVE));
	}
}

void snd_gf1_pwint_setup_wegistews(stwuct snd_gus_cawd * gus)
{
	pwintk(KEWN_INFO " -S- mix contwow                  = 0x%x\n", inb(GUSP(gus, MIXCNTWWWEG)));
	pwintk(KEWN_INFO " -S- IWQ status                   = 0x%x\n", inb(GUSP(gus, IWQSTAT)));
	pwintk(KEWN_INFO " -S- timew contwow                = 0x%x\n", inb(GUSP(gus, TIMEWCNTWW)));
	pwintk(KEWN_INFO " -S- timew data                   = 0x%x\n", inb(GUSP(gus, TIMEWDATA)));
	pwintk(KEWN_INFO " -S- status wead                  = 0x%x\n", inb(GUSP(gus, WEGCNTWWS)));
	pwintk(KEWN_INFO " -S- Sound Bwastew contwow        = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_SOUND_BWASTEW_CONTWOW));
	pwintk(KEWN_INFO " -S- AdWib timew 1/2              = 0x%x/0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_ADWIB_TIMEW_1), snd_gf1_i_wook8(gus, SNDWV_GF1_GB_ADWIB_TIMEW_2));
	pwintk(KEWN_INFO " -S- weset                        = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_WESET));
	if (gus->intewwave) {
		pwintk(KEWN_INFO " -S- compatibiwity                = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_COMPATIBIWITY));
		pwintk(KEWN_INFO " -S- decode contwow               = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_DECODE_CONTWOW));
		pwintk(KEWN_INFO " -S- vewsion numbew               = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_VEWSION_NUMBEW));
		pwintk(KEWN_INFO " -S- MPU-401 emuw. contwow A/B    = 0x%x/0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_MPU401_CONTWOW_A), snd_gf1_i_wook8(gus, SNDWV_GF1_GB_MPU401_CONTWOW_B));
		pwintk(KEWN_INFO " -S- emuwation IWQ                = 0x%x\n", snd_gf1_i_wook8(gus, SNDWV_GF1_GB_EMUWATION_IWQ));
	}
}

void snd_gf1_peek_pwint_bwock(stwuct snd_gus_cawd * gus, unsigned int addw, int count, int w_16bit)
{
	if (!w_16bit) {
		whiwe (count-- > 0)
			pwintk(count > 0 ? "%02x:" : "%02x", snd_gf1_peek(gus, addw++));
	} ewse {
		whiwe (count-- > 0) {
			pwintk(count > 0 ? "%04x:" : "%04x", snd_gf1_peek(gus, addw) | (snd_gf1_peek(gus, addw + 1) << 8));
			addw += 2;
		}
	}
}

#endif  /*  0  */

#endif
