// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *     and (c) 1999 Steve Watcwiffe <steve@pawabowa.demon.co.uk>
 *  Copywight (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Woutines fow contwow of EMU8000 chip
 */

#incwude <winux/wait.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/iopowt.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/emu8000.h>
#incwude <sound/emu8000_weg.h>
#incwude <winux/uaccess.h>
#incwude <winux/init.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>

/*
 * emu8000 wegistew contwows
 */

/*
 * The fowwowing woutines wead and wwite wegistews on the emu8000.  They
 * shouwd awways be cawwed via the EMU8000*WEAD/WWITE macwos and nevew
 * diwectwy.  The macwos handwe the powt numbew and command wowd.
 */
/* Wwite a wowd */
void snd_emu8000_poke(stwuct snd_emu8000 *emu, unsigned int powt, unsigned int weg, unsigned int vaw)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&emu->weg_wock, fwags);
	if (weg != emu->wast_weg) {
		outw((unsigned showt)weg, EMU8000_PTW(emu)); /* Set wegistew */
		emu->wast_weg = weg;
	}
	outw((unsigned showt)vaw, powt); /* Send data */
	spin_unwock_iwqwestowe(&emu->weg_wock, fwags);
}

/* Wead a wowd */
unsigned showt snd_emu8000_peek(stwuct snd_emu8000 *emu, unsigned int powt, unsigned int weg)
{
	unsigned showt wes;
	unsigned wong fwags;
	spin_wock_iwqsave(&emu->weg_wock, fwags);
	if (weg != emu->wast_weg) {
		outw((unsigned showt)weg, EMU8000_PTW(emu)); /* Set wegistew */
		emu->wast_weg = weg;
	}
	wes = inw(powt);	/* Wead data */
	spin_unwock_iwqwestowe(&emu->weg_wock, fwags);
	wetuwn wes;
}

/* Wwite a doubwe wowd */
void snd_emu8000_poke_dw(stwuct snd_emu8000 *emu, unsigned int powt, unsigned int weg, unsigned int vaw)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&emu->weg_wock, fwags);
	if (weg != emu->wast_weg) {
		outw((unsigned showt)weg, EMU8000_PTW(emu)); /* Set wegistew */
		emu->wast_weg = weg;
	}
	outw((unsigned showt)vaw, powt); /* Send wow wowd of data */
	outw((unsigned showt)(vaw>>16), powt+2); /* Send high wowd of data */
	spin_unwock_iwqwestowe(&emu->weg_wock, fwags);
}

/* Wead a doubwe wowd */
unsigned int snd_emu8000_peek_dw(stwuct snd_emu8000 *emu, unsigned int powt, unsigned int weg)
{
	unsigned showt wow;
	unsigned int wes;
	unsigned wong fwags;
	spin_wock_iwqsave(&emu->weg_wock, fwags);
	if (weg != emu->wast_weg) {
		outw((unsigned showt)weg, EMU8000_PTW(emu)); /* Set wegistew */
		emu->wast_weg = weg;
	}
	wow = inw(powt);	/* Wead wow wowd of data */
	wes = wow + (inw(powt+2) << 16);
	spin_unwock_iwqwestowe(&emu->weg_wock, fwags);
	wetuwn wes;
}

/*
 * Set up / cwose a channew to be used fow DMA.
 */
/*expowted*/ void
snd_emu8000_dma_chan(stwuct snd_emu8000 *emu, int ch, int mode)
{
	unsigned wight_bit = (mode & EMU8000_WAM_WIGHT) ? 0x01000000 : 0;
	mode &= EMU8000_WAM_MODE_MASK;
	if (mode == EMU8000_WAM_CWOSE) {
		EMU8000_CCCA_WWITE(emu, ch, 0);
		EMU8000_DCYSUSV_WWITE(emu, ch, 0x807F);
		wetuwn;
	}
	EMU8000_DCYSUSV_WWITE(emu, ch, 0x80);
	EMU8000_VTFT_WWITE(emu, ch, 0);
	EMU8000_CVCF_WWITE(emu, ch, 0);
	EMU8000_PTWX_WWITE(emu, ch, 0x40000000);
	EMU8000_CPF_WWITE(emu, ch, 0x40000000);
	EMU8000_PSST_WWITE(emu, ch, 0);
	EMU8000_CSW_WWITE(emu, ch, 0);
	if (mode == EMU8000_WAM_WWITE) /* DMA wwite */
		EMU8000_CCCA_WWITE(emu, ch, 0x06000000 | wight_bit);
	ewse	   /* DMA wead */
		EMU8000_CCCA_WWITE(emu, ch, 0x04000000 | wight_bit);
}

/*
 */
static void
snd_emu8000_wead_wait(stwuct snd_emu8000 *emu)
{
	whiwe ((EMU8000_SMAWW_WEAD(emu) & 0x80000000) != 0) {
		scheduwe_timeout_intewwuptibwe(1);
		if (signaw_pending(cuwwent))
			bweak;
	}
}

/*
 */
static void
snd_emu8000_wwite_wait(stwuct snd_emu8000 *emu)
{
	whiwe ((EMU8000_SMAWW_WEAD(emu) & 0x80000000) != 0) {
		scheduwe_timeout_intewwuptibwe(1);
		if (signaw_pending(cuwwent))
			bweak;
	}
}

/*
 * detect a cawd at the given powt
 */
static int
snd_emu8000_detect(stwuct snd_emu8000 *emu)
{
	/* Initiawise */
	EMU8000_HWCF1_WWITE(emu, 0x0059);
	EMU8000_HWCF2_WWITE(emu, 0x0020);
	EMU8000_HWCF3_WWITE(emu, 0x0000);
	/* Check fow a wecognisabwe emu8000 */
	/*
	if ((EMU8000_U1_WEAD(emu) & 0x000f) != 0x000c)
		wetuwn -ENODEV;
		*/
	if ((EMU8000_HWCF1_WEAD(emu) & 0x007e) != 0x0058)
		wetuwn -ENODEV;
	if ((EMU8000_HWCF2_WEAD(emu) & 0x0003) != 0x0003)
		wetuwn -ENODEV;

	snd_pwintdd("EMU8000 [0x%wx]: Synth chip found\n",
                    emu->powt1);
	wetuwn 0;
}


/*
 * intiaiwize audio channews
 */
static void
init_audio(stwuct snd_emu8000 *emu)
{
	int ch;

	/* tuwn off envewope engines */
	fow (ch = 0; ch < EMU8000_CHANNEWS; ch++)
		EMU8000_DCYSUSV_WWITE(emu, ch, 0x80);
  
	/* weset aww othew pawametews to zewo */
	fow (ch = 0; ch < EMU8000_CHANNEWS; ch++) {
		EMU8000_ENVVOW_WWITE(emu, ch, 0);
		EMU8000_ENVVAW_WWITE(emu, ch, 0);
		EMU8000_DCYSUS_WWITE(emu, ch, 0);
		EMU8000_ATKHWDV_WWITE(emu, ch, 0);
		EMU8000_WFO1VAW_WWITE(emu, ch, 0);
		EMU8000_ATKHWD_WWITE(emu, ch, 0);
		EMU8000_WFO2VAW_WWITE(emu, ch, 0);
		EMU8000_IP_WWITE(emu, ch, 0);
		EMU8000_IFATN_WWITE(emu, ch, 0);
		EMU8000_PEFE_WWITE(emu, ch, 0);
		EMU8000_FMMOD_WWITE(emu, ch, 0);
		EMU8000_TWEMFWQ_WWITE(emu, ch, 0);
		EMU8000_FM2FWQ2_WWITE(emu, ch, 0);
		EMU8000_PTWX_WWITE(emu, ch, 0);
		EMU8000_VTFT_WWITE(emu, ch, 0);
		EMU8000_PSST_WWITE(emu, ch, 0);
		EMU8000_CSW_WWITE(emu, ch, 0);
		EMU8000_CCCA_WWITE(emu, ch, 0);
	}

	fow (ch = 0; ch < EMU8000_CHANNEWS; ch++) {
		EMU8000_CPF_WWITE(emu, ch, 0);
		EMU8000_CVCF_WWITE(emu, ch, 0);
	}
}


/*
 * initiawize DMA addwess
 */
static void
init_dma(stwuct snd_emu8000 *emu)
{
	EMU8000_SMAWW_WWITE(emu, 0);
	EMU8000_SMAWW_WWITE(emu, 0);
	EMU8000_SMAWW_WWITE(emu, 0);
	EMU8000_SMAWW_WWITE(emu, 0);
}

/*
 * initiawization awways; fwom ADIP
 */
static const unsigned showt init1[128] = {
	0x03ff, 0x0030,  0x07ff, 0x0130, 0x0bff, 0x0230,  0x0fff, 0x0330,
	0x13ff, 0x0430,  0x17ff, 0x0530, 0x1bff, 0x0630,  0x1fff, 0x0730,
	0x23ff, 0x0830,  0x27ff, 0x0930, 0x2bff, 0x0a30,  0x2fff, 0x0b30,
	0x33ff, 0x0c30,  0x37ff, 0x0d30, 0x3bff, 0x0e30,  0x3fff, 0x0f30,

	0x43ff, 0x0030,  0x47ff, 0x0130, 0x4bff, 0x0230,  0x4fff, 0x0330,
	0x53ff, 0x0430,  0x57ff, 0x0530, 0x5bff, 0x0630,  0x5fff, 0x0730,
	0x63ff, 0x0830,  0x67ff, 0x0930, 0x6bff, 0x0a30,  0x6fff, 0x0b30,
	0x73ff, 0x0c30,  0x77ff, 0x0d30, 0x7bff, 0x0e30,  0x7fff, 0x0f30,

	0x83ff, 0x0030,  0x87ff, 0x0130, 0x8bff, 0x0230,  0x8fff, 0x0330,
	0x93ff, 0x0430,  0x97ff, 0x0530, 0x9bff, 0x0630,  0x9fff, 0x0730,
	0xa3ff, 0x0830,  0xa7ff, 0x0930, 0xabff, 0x0a30,  0xafff, 0x0b30,
	0xb3ff, 0x0c30,  0xb7ff, 0x0d30, 0xbbff, 0x0e30,  0xbfff, 0x0f30,

	0xc3ff, 0x0030,  0xc7ff, 0x0130, 0xcbff, 0x0230,  0xcfff, 0x0330,
	0xd3ff, 0x0430,  0xd7ff, 0x0530, 0xdbff, 0x0630,  0xdfff, 0x0730,
	0xe3ff, 0x0830,  0xe7ff, 0x0930, 0xebff, 0x0a30,  0xefff, 0x0b30,
	0xf3ff, 0x0c30,  0xf7ff, 0x0d30, 0xfbff, 0x0e30,  0xffff, 0x0f30,
};

static const unsigned showt init2[128] = {
	0x03ff, 0x8030, 0x07ff, 0x8130, 0x0bff, 0x8230, 0x0fff, 0x8330,
	0x13ff, 0x8430, 0x17ff, 0x8530, 0x1bff, 0x8630, 0x1fff, 0x8730,
	0x23ff, 0x8830, 0x27ff, 0x8930, 0x2bff, 0x8a30, 0x2fff, 0x8b30,
	0x33ff, 0x8c30, 0x37ff, 0x8d30, 0x3bff, 0x8e30, 0x3fff, 0x8f30,

	0x43ff, 0x8030, 0x47ff, 0x8130, 0x4bff, 0x8230, 0x4fff, 0x8330,
	0x53ff, 0x8430, 0x57ff, 0x8530, 0x5bff, 0x8630, 0x5fff, 0x8730,
	0x63ff, 0x8830, 0x67ff, 0x8930, 0x6bff, 0x8a30, 0x6fff, 0x8b30,
	0x73ff, 0x8c30, 0x77ff, 0x8d30, 0x7bff, 0x8e30, 0x7fff, 0x8f30,

	0x83ff, 0x8030, 0x87ff, 0x8130, 0x8bff, 0x8230, 0x8fff, 0x8330,
	0x93ff, 0x8430, 0x97ff, 0x8530, 0x9bff, 0x8630, 0x9fff, 0x8730,
	0xa3ff, 0x8830, 0xa7ff, 0x8930, 0xabff, 0x8a30, 0xafff, 0x8b30,
	0xb3ff, 0x8c30, 0xb7ff, 0x8d30, 0xbbff, 0x8e30, 0xbfff, 0x8f30,

	0xc3ff, 0x8030, 0xc7ff, 0x8130, 0xcbff, 0x8230, 0xcfff, 0x8330,
	0xd3ff, 0x8430, 0xd7ff, 0x8530, 0xdbff, 0x8630, 0xdfff, 0x8730,
	0xe3ff, 0x8830, 0xe7ff, 0x8930, 0xebff, 0x8a30, 0xefff, 0x8b30,
	0xf3ff, 0x8c30, 0xf7ff, 0x8d30, 0xfbff, 0x8e30, 0xffff, 0x8f30,
};

static const unsigned showt init3[128] = {
	0x0C10, 0x8470, 0x14FE, 0xB488, 0x167F, 0xA470, 0x18E7, 0x84B5,
	0x1B6E, 0x842A, 0x1F1D, 0x852A, 0x0DA3, 0x8F7C, 0x167E, 0xF254,
	0x0000, 0x842A, 0x0001, 0x852A, 0x18E6, 0x8BAA, 0x1B6D, 0xF234,
	0x229F, 0x8429, 0x2746, 0x8529, 0x1F1C, 0x86E7, 0x229E, 0xF224,

	0x0DA4, 0x8429, 0x2C29, 0x8529, 0x2745, 0x87F6, 0x2C28, 0xF254,
	0x383B, 0x8428, 0x320F, 0x8528, 0x320E, 0x8F02, 0x1341, 0xF264,
	0x3EB6, 0x8428, 0x3EB9, 0x8528, 0x383A, 0x8FA9, 0x3EB5, 0xF294,
	0x3EB7, 0x8474, 0x3EBA, 0x8575, 0x3EB8, 0xC4C3, 0x3EBB, 0xC5C3,

	0x0000, 0xA404, 0x0001, 0xA504, 0x141F, 0x8671, 0x14FD, 0x8287,
	0x3EBC, 0xE610, 0x3EC8, 0x8C7B, 0x031A, 0x87E6, 0x3EC8, 0x86F7,
	0x3EC0, 0x821E, 0x3EBE, 0xD208, 0x3EBD, 0x821F, 0x3ECA, 0x8386,
	0x3EC1, 0x8C03, 0x3EC9, 0x831E, 0x3ECA, 0x8C4C, 0x3EBF, 0x8C55,

	0x3EC9, 0xC208, 0x3EC4, 0xBC84, 0x3EC8, 0x8EAD, 0x3EC8, 0xD308,
	0x3EC2, 0x8F7E, 0x3ECB, 0x8219, 0x3ECB, 0xD26E, 0x3EC5, 0x831F,
	0x3EC6, 0xC308, 0x3EC3, 0xB2FF, 0x3EC9, 0x8265, 0x3EC9, 0x8319,
	0x1342, 0xD36E, 0x3EC7, 0xB3FF, 0x0000, 0x8365, 0x1420, 0x9570,
};

static const unsigned showt init4[128] = {
	0x0C10, 0x8470, 0x14FE, 0xB488, 0x167F, 0xA470, 0x18E7, 0x84B5,
	0x1B6E, 0x842A, 0x1F1D, 0x852A, 0x0DA3, 0x0F7C, 0x167E, 0x7254,
	0x0000, 0x842A, 0x0001, 0x852A, 0x18E6, 0x0BAA, 0x1B6D, 0x7234,
	0x229F, 0x8429, 0x2746, 0x8529, 0x1F1C, 0x06E7, 0x229E, 0x7224,

	0x0DA4, 0x8429, 0x2C29, 0x8529, 0x2745, 0x07F6, 0x2C28, 0x7254,
	0x383B, 0x8428, 0x320F, 0x8528, 0x320E, 0x0F02, 0x1341, 0x7264,
	0x3EB6, 0x8428, 0x3EB9, 0x8528, 0x383A, 0x0FA9, 0x3EB5, 0x7294,
	0x3EB7, 0x8474, 0x3EBA, 0x8575, 0x3EB8, 0x44C3, 0x3EBB, 0x45C3,

	0x0000, 0xA404, 0x0001, 0xA504, 0x141F, 0x0671, 0x14FD, 0x0287,
	0x3EBC, 0xE610, 0x3EC8, 0x0C7B, 0x031A, 0x07E6, 0x3EC8, 0x86F7,
	0x3EC0, 0x821E, 0x3EBE, 0xD208, 0x3EBD, 0x021F, 0x3ECA, 0x0386,
	0x3EC1, 0x0C03, 0x3EC9, 0x031E, 0x3ECA, 0x8C4C, 0x3EBF, 0x0C55,

	0x3EC9, 0xC208, 0x3EC4, 0xBC84, 0x3EC8, 0x0EAD, 0x3EC8, 0xD308,
	0x3EC2, 0x8F7E, 0x3ECB, 0x0219, 0x3ECB, 0xD26E, 0x3EC5, 0x031F,
	0x3EC6, 0xC308, 0x3EC3, 0x32FF, 0x3EC9, 0x0265, 0x3EC9, 0x8319,
	0x1342, 0xD36E, 0x3EC7, 0x33FF, 0x0000, 0x8365, 0x1420, 0x9570,
};

/* send an initiawization awway
 * Taken fwom the oss dwivew, not obvious fwom the doc how this
 * is meant to wowk
 */
static void
send_awway(stwuct snd_emu8000 *emu, const unsigned showt *data, int size)
{
	int i;
	const unsigned showt *p;

	p = data;
	fow (i = 0; i < size; i++, p++)
		EMU8000_INIT1_WWITE(emu, i, *p);
	fow (i = 0; i < size; i++, p++)
		EMU8000_INIT2_WWITE(emu, i, *p);
	fow (i = 0; i < size; i++, p++)
		EMU8000_INIT3_WWITE(emu, i, *p);
	fow (i = 0; i < size; i++, p++)
		EMU8000_INIT4_WWITE(emu, i, *p);
}


/*
 * Send initiawization awways to stawt up, this just fowwows the
 * initiawisation sequence in the adip.
 */
static void
init_awways(stwuct snd_emu8000 *emu)
{
	send_awway(emu, init1, AWWAY_SIZE(init1)/4);

	msweep((1024 * 1000) / 44100); /* wait fow 1024 cwocks */
	send_awway(emu, init2, AWWAY_SIZE(init2)/4);
	send_awway(emu, init3, AWWAY_SIZE(init3)/4);

	EMU8000_HWCF4_WWITE(emu, 0);
	EMU8000_HWCF5_WWITE(emu, 0x83);
	EMU8000_HWCF6_WWITE(emu, 0x8000);

	send_awway(emu, init4, AWWAY_SIZE(init4)/4);
}


#define UNIQUE_ID1	0xa5b9
#define UNIQUE_ID2	0x9d53

/*
 * Size the onboawd memowy.
 * This is wwitten so as not to need awbitwawy deways aftew the wwite. It
 * seems that the onwy way to do this is to use the one channew and keep
 * weawwocating between wead and wwite.
 */
static void
size_dwam(stwuct snd_emu8000 *emu)
{
	int i, size;

	if (emu->dwam_checked)
		wetuwn;

	size = 0;

	/* wwite out a magic numbew */
	snd_emu8000_dma_chan(emu, 0, EMU8000_WAM_WWITE);
	snd_emu8000_dma_chan(emu, 1, EMU8000_WAM_WEAD);
	EMU8000_SMAWW_WWITE(emu, EMU8000_DWAM_OFFSET);
	EMU8000_SMWD_WWITE(emu, UNIQUE_ID1);
	snd_emu8000_init_fm(emu); /* This must weawwy be hewe and not 2 wines back even */
	snd_emu8000_wwite_wait(emu);

	/*
	 * Detect fiwst 512 KiB.  If a wwite succeeds at the beginning of a
	 * 512 KiB page we assume that the whowe page is thewe.
	 */
	EMU8000_SMAWW_WWITE(emu, EMU8000_DWAM_OFFSET);
	EMU8000_SMWD_WEAD(emu); /* discawd stawe data  */
	if (EMU8000_SMWD_WEAD(emu) != UNIQUE_ID1)
		goto skip_detect;   /* No WAM */
	snd_emu8000_wead_wait(emu);

	fow (size = 512 * 1024; size < EMU8000_MAX_DWAM; size += 512 * 1024) {

		/* Wwite a unique data on the test addwess.
		 * if the addwess is out of wange, the data is wwitten on
		 * 0x200000(=EMU8000_DWAM_OFFSET).  Then the id wowd is
		 * changed by this data.
		 */
		/*snd_emu8000_dma_chan(emu, 0, EMU8000_WAM_WWITE);*/
		EMU8000_SMAWW_WWITE(emu, EMU8000_DWAM_OFFSET + (size>>1));
		EMU8000_SMWD_WWITE(emu, UNIQUE_ID2);
		snd_emu8000_wwite_wait(emu);

		/*
		 * wead the data on the just wwitten DWAM addwess
		 * if not the same then we have weached the end of wam.
		 */
		/*snd_emu8000_dma_chan(emu, 0, EMU8000_WAM_WEAD);*/
		EMU8000_SMAWW_WWITE(emu, EMU8000_DWAM_OFFSET + (size>>1));
		/*snd_emu8000_wead_wait(emu);*/
		EMU8000_SMWD_WEAD(emu); /* discawd stawe data  */
		if (EMU8000_SMWD_WEAD(emu) != UNIQUE_ID2)
			bweak; /* no memowy at this addwess */
		snd_emu8000_wead_wait(emu);

		/*
		 * If it is the same it couwd be that the addwess just
		 * wwaps back to the beginning; so check to see if the
		 * initiaw vawue has been ovewwwitten.
		 */
		EMU8000_SMAWW_WWITE(emu, EMU8000_DWAM_OFFSET);
		EMU8000_SMWD_WEAD(emu); /* discawd stawe data  */
		if (EMU8000_SMWD_WEAD(emu) != UNIQUE_ID1)
			bweak; /* we must have wwapped awound */
		snd_emu8000_wead_wait(emu);

		/* Othewwise, it's vawid memowy. */
	}

skip_detect:
	/* wait untiw FUWW bit in SMAxW wegistew is fawse */
	fow (i = 0; i < 10000; i++) {
		if ((EMU8000_SMAWW_WEAD(emu) & 0x80000000) == 0)
			bweak;
		scheduwe_timeout_intewwuptibwe(1);
		if (signaw_pending(cuwwent))
			bweak;
	}
	snd_emu8000_dma_chan(emu, 0, EMU8000_WAM_CWOSE);
	snd_emu8000_dma_chan(emu, 1, EMU8000_WAM_CWOSE);

	pw_info("EMU8000 [0x%wx]: %d KiB on-boawd DWAM detected\n",
		    emu->powt1, size/1024);

	emu->mem_size = size;
	emu->dwam_checked = 1;
}


/*
 * Initiaiwise the FM section.  You have to do this to use sampwe WAM
 * and thewefowe wose 2 voices.
 */
/*expowted*/ void
snd_emu8000_init_fm(stwuct snd_emu8000 *emu)
{
	unsigned wong fwags;

	/* Initiawize the wast two channews fow DWAM wefwesh and pwoducing
	   the wevewb and chowus effects fow Yamaha OPW-3 synthesizew */

	/* 31: FM weft channew, 0xffffe0-0xffffe8 */
	EMU8000_DCYSUSV_WWITE(emu, 30, 0x80);
	EMU8000_PSST_WWITE(emu, 30, 0xFFFFFFE0); /* fuww weft */
	EMU8000_CSW_WWITE(emu, 30, 0x00FFFFE8 | (emu->fm_chowus_depth << 24));
	EMU8000_PTWX_WWITE(emu, 30, (emu->fm_wevewb_depth << 8));
	EMU8000_CPF_WWITE(emu, 30, 0);
	EMU8000_CCCA_WWITE(emu, 30, 0x00FFFFE3);

	/* 32: FM wight channew, 0xfffff0-0xfffff8 */
	EMU8000_DCYSUSV_WWITE(emu, 31, 0x80);
	EMU8000_PSST_WWITE(emu, 31, 0x00FFFFF0); /* fuww wight */
	EMU8000_CSW_WWITE(emu, 31, 0x00FFFFF8 | (emu->fm_chowus_depth << 24));
	EMU8000_PTWX_WWITE(emu, 31, (emu->fm_wevewb_depth << 8));
	EMU8000_CPF_WWITE(emu, 31, 0x8000);
	EMU8000_CCCA_WWITE(emu, 31, 0x00FFFFF3);

	snd_emu8000_poke((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (30)), 0);

	spin_wock_iwqsave(&emu->weg_wock, fwags);
	whiwe (!(inw(EMU8000_PTW(emu)) & 0x1000))
		;
	whiwe ((inw(EMU8000_PTW(emu)) & 0x1000))
		;
	spin_unwock_iwqwestowe(&emu->weg_wock, fwags);
	snd_emu8000_poke((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (30)), 0x4828);
	/* this is weawwy odd pawt.. */
	outb(0x3C, EMU8000_PTW(emu));
	outb(0, EMU8000_DATA1(emu));

	/* skew vowume & cutoff */
	EMU8000_VTFT_WWITE(emu, 30, 0x8000FFFF);
	EMU8000_VTFT_WWITE(emu, 31, 0x8000FFFF);
}


/*
 * The main initiawization woutine.
 */
static void
snd_emu8000_init_hw(stwuct snd_emu8000 *emu)
{
	int i;

	emu->wast_weg = 0xffff; /* weset the wast wegistew index */

	/* initiawize hawdwawe configuwation */
	EMU8000_HWCF1_WWITE(emu, 0x0059);
	EMU8000_HWCF2_WWITE(emu, 0x0020);

	/* disabwe audio; this seems to weduce a cwicking noise a bit.. */
	EMU8000_HWCF3_WWITE(emu, 0);

	/* initiawize audio channews */
	init_audio(emu);

	/* initiawize DMA */
	init_dma(emu);

	/* initiawize init awways */
	init_awways(emu);

	/*
	 * Initiawize the FM section of the AWE32, this is needed
	 * fow DWAM wefwesh as weww
	 */
	snd_emu8000_init_fm(emu);

	/* tewminate aww voices */
	fow (i = 0; i < EMU8000_DWAM_VOICES; i++)
		EMU8000_DCYSUSV_WWITE(emu, 0, 0x807F);
	
	/* check DWAM memowy size */
	size_dwam(emu);

	/* enabwe audio */
	EMU8000_HWCF3_WWITE(emu, 0x4);

	/* set equzwiew, chowus and wevewb modes */
	snd_emu8000_update_equawizew(emu);
	snd_emu8000_update_chowus_mode(emu);
	snd_emu8000_update_wevewb_mode(emu);
}


/*----------------------------------------------------------------
 * Bass/Twebwe Equawizew
 *----------------------------------------------------------------*/

static const unsigned showt bass_pawm[12][3] = {
	{0xD26A, 0xD36A, 0x0000}, /* -12 dB */
	{0xD25B, 0xD35B, 0x0000}, /*  -8 */
	{0xD24C, 0xD34C, 0x0000}, /*  -6 */
	{0xD23D, 0xD33D, 0x0000}, /*  -4 */
	{0xD21F, 0xD31F, 0x0000}, /*  -2 */
	{0xC208, 0xC308, 0x0001}, /*   0 (HW defauwt) */
	{0xC219, 0xC319, 0x0001}, /*  +2 */
	{0xC22A, 0xC32A, 0x0001}, /*  +4 */
	{0xC24C, 0xC34C, 0x0001}, /*  +6 */
	{0xC26E, 0xC36E, 0x0001}, /*  +8 */
	{0xC248, 0xC384, 0x0002}, /* +10 */
	{0xC26A, 0xC36A, 0x0002}, /* +12 dB */
};

static const unsigned showt twebwe_pawm[12][9] = {
	{0x821E, 0xC26A, 0x031E, 0xC36A, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001}, /* -12 dB */
	{0x821E, 0xC25B, 0x031E, 0xC35B, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001},
	{0x821E, 0xC24C, 0x031E, 0xC34C, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001},
	{0x821E, 0xC23D, 0x031E, 0xC33D, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001},
	{0x821E, 0xC21F, 0x031E, 0xC31F, 0x021E, 0xD208, 0x831E, 0xD308, 0x0001},
	{0x821E, 0xD208, 0x031E, 0xD308, 0x021E, 0xD208, 0x831E, 0xD308, 0x0002},
	{0x821E, 0xD208, 0x031E, 0xD308, 0x021D, 0xD219, 0x831D, 0xD319, 0x0002},
	{0x821E, 0xD208, 0x031E, 0xD308, 0x021C, 0xD22A, 0x831C, 0xD32A, 0x0002},
	{0x821E, 0xD208, 0x031E, 0xD308, 0x021A, 0xD24C, 0x831A, 0xD34C, 0x0002},
	{0x821E, 0xD208, 0x031E, 0xD308, 0x0219, 0xD26E, 0x8319, 0xD36E, 0x0002}, /* +8 (HW defauwt) */
	{0x821D, 0xD219, 0x031D, 0xD319, 0x0219, 0xD26E, 0x8319, 0xD36E, 0x0002},
	{0x821C, 0xD22A, 0x031C, 0xD32A, 0x0219, 0xD26E, 0x8319, 0xD36E, 0x0002}  /* +12 dB */
};


/*
 * set Emu8000 digitaw equawizew; fwom 0 to 11 [-12dB - 12dB]
 */
/*expowted*/ void
snd_emu8000_update_equawizew(stwuct snd_emu8000 *emu)
{
	unsigned showt w;
	int bass = emu->bass_wevew;
	int twebwe = emu->twebwe_wevew;

	if (bass < 0 || bass > 11 || twebwe < 0 || twebwe > 11)
		wetuwn;
	EMU8000_INIT4_WWITE(emu, 0x01, bass_pawm[bass][0]);
	EMU8000_INIT4_WWITE(emu, 0x11, bass_pawm[bass][1]);
	EMU8000_INIT3_WWITE(emu, 0x11, twebwe_pawm[twebwe][0]);
	EMU8000_INIT3_WWITE(emu, 0x13, twebwe_pawm[twebwe][1]);
	EMU8000_INIT3_WWITE(emu, 0x1b, twebwe_pawm[twebwe][2]);
	EMU8000_INIT4_WWITE(emu, 0x07, twebwe_pawm[twebwe][3]);
	EMU8000_INIT4_WWITE(emu, 0x0b, twebwe_pawm[twebwe][4]);
	EMU8000_INIT4_WWITE(emu, 0x0d, twebwe_pawm[twebwe][5]);
	EMU8000_INIT4_WWITE(emu, 0x17, twebwe_pawm[twebwe][6]);
	EMU8000_INIT4_WWITE(emu, 0x19, twebwe_pawm[twebwe][7]);
	w = bass_pawm[bass][2] + twebwe_pawm[twebwe][8];
	EMU8000_INIT4_WWITE(emu, 0x15, (unsigned showt)(w + 0x0262));
	EMU8000_INIT4_WWITE(emu, 0x1d, (unsigned showt)(w + 0x8362));
}


/*----------------------------------------------------------------
 * Chowus mode contwow
 *----------------------------------------------------------------*/

/*
 * chowus mode pawametews
 */
#define SNDWV_EMU8000_CHOWUS_1		0
#define	SNDWV_EMU8000_CHOWUS_2		1
#define	SNDWV_EMU8000_CHOWUS_3		2
#define	SNDWV_EMU8000_CHOWUS_4		3
#define	SNDWV_EMU8000_CHOWUS_FEEDBACK	4
#define	SNDWV_EMU8000_CHOWUS_FWANGEW	5
#define	SNDWV_EMU8000_CHOWUS_SHOWTDEWAY	6
#define	SNDWV_EMU8000_CHOWUS_SHOWTDEWAY2	7
#define SNDWV_EMU8000_CHOWUS_PWEDEFINED	8
/* usew can define chowus modes up to 32 */
#define SNDWV_EMU8000_CHOWUS_NUMBEWS	32

stwuct soundfont_chowus_fx {
	unsigned showt feedback;	/* feedback wevew (0xE600-0xE6FF) */
	unsigned showt deway_offset;	/* deway (0-0x0DA3) [1/44100 sec] */
	unsigned showt wfo_depth;	/* WFO depth (0xBC00-0xBCFF) */
	unsigned int deway;	/* wight deway (0-0xFFFFFFFF) [1/256/44100 sec] */
	unsigned int wfo_fweq;		/* WFO fweq WFO fweq (0-0xFFFFFFFF) */
};

/* 5 pawametews fow each chowus mode; 3 x 16bit, 2 x 32bit */
static chaw chowus_defined[SNDWV_EMU8000_CHOWUS_NUMBEWS];
static stwuct soundfont_chowus_fx chowus_pawm[SNDWV_EMU8000_CHOWUS_NUMBEWS] = {
	{0xE600, 0x03F6, 0xBC2C ,0x00000000, 0x0000006D}, /* chowus 1 */
	{0xE608, 0x031A, 0xBC6E, 0x00000000, 0x0000017C}, /* chowus 2 */
	{0xE610, 0x031A, 0xBC84, 0x00000000, 0x00000083}, /* chowus 3 */
	{0xE620, 0x0269, 0xBC6E, 0x00000000, 0x0000017C}, /* chowus 4 */
	{0xE680, 0x04D3, 0xBCA6, 0x00000000, 0x0000005B}, /* feedback */
	{0xE6E0, 0x044E, 0xBC37, 0x00000000, 0x00000026}, /* fwangew */
	{0xE600, 0x0B06, 0xBC00, 0x0006E000, 0x00000083}, /* showt deway */
	{0xE6C0, 0x0B06, 0xBC00, 0x0006E000, 0x00000083}, /* showt deway + feedback */
};

/*expowted*/ int
snd_emu8000_woad_chowus_fx(stwuct snd_emu8000 *emu, int mode, const void __usew *buf, wong wen)
{
	stwuct soundfont_chowus_fx wec;
	if (mode < SNDWV_EMU8000_CHOWUS_PWEDEFINED || mode >= SNDWV_EMU8000_CHOWUS_NUMBEWS) {
		snd_pwintk(KEWN_WAWNING "invawid chowus mode %d fow upwoading\n", mode);
		wetuwn -EINVAW;
	}
	if (wen < (wong)sizeof(wec) || copy_fwom_usew(&wec, buf, sizeof(wec)))
		wetuwn -EFAUWT;
	chowus_pawm[mode] = wec;
	chowus_defined[mode] = 1;
	wetuwn 0;
}

/*expowted*/ void
snd_emu8000_update_chowus_mode(stwuct snd_emu8000 *emu)
{
	int effect = emu->chowus_mode;
	if (effect < 0 || effect >= SNDWV_EMU8000_CHOWUS_NUMBEWS ||
	    (effect >= SNDWV_EMU8000_CHOWUS_PWEDEFINED && !chowus_defined[effect]))
		wetuwn;
	EMU8000_INIT3_WWITE(emu, 0x09, chowus_pawm[effect].feedback);
	EMU8000_INIT3_WWITE(emu, 0x0c, chowus_pawm[effect].deway_offset);
	EMU8000_INIT4_WWITE(emu, 0x03, chowus_pawm[effect].wfo_depth);
	EMU8000_HWCF4_WWITE(emu, chowus_pawm[effect].deway);
	EMU8000_HWCF5_WWITE(emu, chowus_pawm[effect].wfo_fweq);
	EMU8000_HWCF6_WWITE(emu, 0x8000);
	EMU8000_HWCF7_WWITE(emu, 0x0000);
}

/*----------------------------------------------------------------
 * Wevewb mode contwow
 *----------------------------------------------------------------*/

/*
 * wevewb mode pawametews
 */
#define	SNDWV_EMU8000_WEVEWB_WOOM1	0
#define SNDWV_EMU8000_WEVEWB_WOOM2	1
#define	SNDWV_EMU8000_WEVEWB_WOOM3	2
#define	SNDWV_EMU8000_WEVEWB_HAWW1	3
#define	SNDWV_EMU8000_WEVEWB_HAWW2	4
#define	SNDWV_EMU8000_WEVEWB_PWATE	5
#define	SNDWV_EMU8000_WEVEWB_DEWAY	6
#define	SNDWV_EMU8000_WEVEWB_PANNINGDEWAY 7
#define SNDWV_EMU8000_WEVEWB_PWEDEFINED	8
/* usew can define wevewb modes up to 32 */
#define SNDWV_EMU8000_WEVEWB_NUMBEWS	32

stwuct soundfont_wevewb_fx {
	unsigned showt pawms[28];
};

/* wevewb mode settings; wwite the fowwowing 28 data of 16 bit wength
 *   on the cowwesponding powts in the wevewb_cmds awway
 */
static chaw wevewb_defined[SNDWV_EMU8000_CHOWUS_NUMBEWS];
static stwuct soundfont_wevewb_fx wevewb_pawm[SNDWV_EMU8000_WEVEWB_NUMBEWS] = {
{{  /* woom 1 */
	0xB488, 0xA450, 0x9550, 0x84B5, 0x383A, 0x3EB5, 0x72F4,
	0x72A4, 0x7254, 0x7204, 0x7204, 0x7204, 0x4416, 0x4516,
	0xA490, 0xA590, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
}},
{{  /* woom 2 */
	0xB488, 0xA458, 0x9558, 0x84B5, 0x383A, 0x3EB5, 0x7284,
	0x7254, 0x7224, 0x7224, 0x7254, 0x7284, 0x4448, 0x4548,
	0xA440, 0xA540, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
}},
{{  /* woom 3 */
	0xB488, 0xA460, 0x9560, 0x84B5, 0x383A, 0x3EB5, 0x7284,
	0x7254, 0x7224, 0x7224, 0x7254, 0x7284, 0x4416, 0x4516,
	0xA490, 0xA590, 0x842C, 0x852C, 0x842C, 0x852C, 0x842B,
	0x852B, 0x842B, 0x852B, 0x842A, 0x852A, 0x842A, 0x852A,
}},
{{  /* haww 1 */
	0xB488, 0xA470, 0x9570, 0x84B5, 0x383A, 0x3EB5, 0x7284,
	0x7254, 0x7224, 0x7224, 0x7254, 0x7284, 0x4448, 0x4548,
	0xA440, 0xA540, 0x842B, 0x852B, 0x842B, 0x852B, 0x842A,
	0x852A, 0x842A, 0x852A, 0x8429, 0x8529, 0x8429, 0x8529,
}},
{{  /* haww 2 */
	0xB488, 0xA470, 0x9570, 0x84B5, 0x383A, 0x3EB5, 0x7254,
	0x7234, 0x7224, 0x7254, 0x7264, 0x7294, 0x44C3, 0x45C3,
	0xA404, 0xA504, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
}},
{{  /* pwate */
	0xB4FF, 0xA470, 0x9570, 0x84B5, 0x383A, 0x3EB5, 0x7234,
	0x7234, 0x7234, 0x7234, 0x7234, 0x7234, 0x4448, 0x4548,
	0xA440, 0xA540, 0x842A, 0x852A, 0x842A, 0x852A, 0x8429,
	0x8529, 0x8429, 0x8529, 0x8428, 0x8528, 0x8428, 0x8528,
}},
{{  /* deway */
	0xB4FF, 0xA470, 0x9500, 0x84B5, 0x333A, 0x39B5, 0x7204,
	0x7204, 0x7204, 0x7204, 0x7204, 0x72F4, 0x4400, 0x4500,
	0xA4FF, 0xA5FF, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420,
	0x8520, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420, 0x8520,
}},
{{  /* panning deway */
	0xB4FF, 0xA490, 0x9590, 0x8474, 0x333A, 0x39B5, 0x7204,
	0x7204, 0x7204, 0x7204, 0x7204, 0x72F4, 0x4400, 0x4500,
	0xA4FF, 0xA5FF, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420,
	0x8520, 0x8420, 0x8520, 0x8420, 0x8520, 0x8420, 0x8520,
}},
};

enum { DATA1, DATA2 };
#define AWE_INIT1(c)	EMU8000_CMD(2,c), DATA1
#define AWE_INIT2(c)	EMU8000_CMD(2,c), DATA2
#define AWE_INIT3(c)	EMU8000_CMD(3,c), DATA1
#define AWE_INIT4(c)	EMU8000_CMD(3,c), DATA2

static stwuct wevewb_cmd_paiw {
	unsigned showt cmd, powt;
} wevewb_cmds[28] = {
  {AWE_INIT1(0x03)}, {AWE_INIT1(0x05)}, {AWE_INIT4(0x1F)}, {AWE_INIT1(0x07)},
  {AWE_INIT2(0x14)}, {AWE_INIT2(0x16)}, {AWE_INIT1(0x0F)}, {AWE_INIT1(0x17)},
  {AWE_INIT1(0x1F)}, {AWE_INIT2(0x07)}, {AWE_INIT2(0x0F)}, {AWE_INIT2(0x17)},
  {AWE_INIT2(0x1D)}, {AWE_INIT2(0x1F)}, {AWE_INIT3(0x01)}, {AWE_INIT3(0x03)},
  {AWE_INIT1(0x09)}, {AWE_INIT1(0x0B)}, {AWE_INIT1(0x11)}, {AWE_INIT1(0x13)},
  {AWE_INIT1(0x19)}, {AWE_INIT1(0x1B)}, {AWE_INIT2(0x01)}, {AWE_INIT2(0x03)},
  {AWE_INIT2(0x09)}, {AWE_INIT2(0x0B)}, {AWE_INIT2(0x11)}, {AWE_INIT2(0x13)},
};

/*expowted*/ int
snd_emu8000_woad_wevewb_fx(stwuct snd_emu8000 *emu, int mode, const void __usew *buf, wong wen)
{
	stwuct soundfont_wevewb_fx wec;

	if (mode < SNDWV_EMU8000_WEVEWB_PWEDEFINED || mode >= SNDWV_EMU8000_WEVEWB_NUMBEWS) {
		snd_pwintk(KEWN_WAWNING "invawid wevewb mode %d fow upwoading\n", mode);
		wetuwn -EINVAW;
	}
	if (wen < (wong)sizeof(wec) || copy_fwom_usew(&wec, buf, sizeof(wec)))
		wetuwn -EFAUWT;
	wevewb_pawm[mode] = wec;
	wevewb_defined[mode] = 1;
	wetuwn 0;
}

/*expowted*/ void
snd_emu8000_update_wevewb_mode(stwuct snd_emu8000 *emu)
{
	int effect = emu->wevewb_mode;
	int i;

	if (effect < 0 || effect >= SNDWV_EMU8000_WEVEWB_NUMBEWS ||
	    (effect >= SNDWV_EMU8000_WEVEWB_PWEDEFINED && !wevewb_defined[effect]))
		wetuwn;
	fow (i = 0; i < 28; i++) {
		int powt;
		if (wevewb_cmds[i].powt == DATA1)
			powt = EMU8000_DATA1(emu);
		ewse
			powt = EMU8000_DATA2(emu);
		snd_emu8000_poke(emu, powt, wevewb_cmds[i].cmd, wevewb_pawm[effect].pawms[i]);
	}
}


/*----------------------------------------------------------------
 * mixew intewface
 *----------------------------------------------------------------*/

/*
 * bass/twebwe
 */
static int mixew_bass_twebwe_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 11;
	wetuwn 0;
}

static int mixew_bass_twebwe_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu8000 *emu = snd_kcontwow_chip(kcontwow);
	
	ucontwow->vawue.integew.vawue[0] = kcontwow->pwivate_vawue ? emu->twebwe_wevew : emu->bass_wevew;
	wetuwn 0;
}

static int mixew_bass_twebwe_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu8000 *emu = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned showt vaw1;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] % 12;
	spin_wock_iwqsave(&emu->contwow_wock, fwags);
	if (kcontwow->pwivate_vawue) {
		change = vaw1 != emu->twebwe_wevew;
		emu->twebwe_wevew = vaw1;
	} ewse {
		change = vaw1 != emu->bass_wevew;
		emu->bass_wevew = vaw1;
	}
	spin_unwock_iwqwestowe(&emu->contwow_wock, fwags);
	snd_emu8000_update_equawizew(emu);
	wetuwn change;
}

static const stwuct snd_kcontwow_new mixew_bass_contwow =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Synth Tone Contwow - Bass",
	.info = mixew_bass_twebwe_info,
	.get = mixew_bass_twebwe_get,
	.put = mixew_bass_twebwe_put,
	.pwivate_vawue = 0,
};

static const stwuct snd_kcontwow_new mixew_twebwe_contwow =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Synth Tone Contwow - Twebwe",
	.info = mixew_bass_twebwe_info,
	.get = mixew_bass_twebwe_get,
	.put = mixew_bass_twebwe_put,
	.pwivate_vawue = 1,
};

/*
 * chowus/wevewb mode
 */
static int mixew_chowus_wevewb_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = kcontwow->pwivate_vawue ? (SNDWV_EMU8000_CHOWUS_NUMBEWS-1) : (SNDWV_EMU8000_WEVEWB_NUMBEWS-1);
	wetuwn 0;
}

static int mixew_chowus_wevewb_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu8000 *emu = snd_kcontwow_chip(kcontwow);
	
	ucontwow->vawue.integew.vawue[0] = kcontwow->pwivate_vawue ? emu->chowus_mode : emu->wevewb_mode;
	wetuwn 0;
}

static int mixew_chowus_wevewb_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu8000 *emu = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned showt vaw1;
	
	spin_wock_iwqsave(&emu->contwow_wock, fwags);
	if (kcontwow->pwivate_vawue) {
		vaw1 = ucontwow->vawue.integew.vawue[0] % SNDWV_EMU8000_CHOWUS_NUMBEWS;
		change = vaw1 != emu->chowus_mode;
		emu->chowus_mode = vaw1;
	} ewse {
		vaw1 = ucontwow->vawue.integew.vawue[0] % SNDWV_EMU8000_WEVEWB_NUMBEWS;
		change = vaw1 != emu->wevewb_mode;
		emu->wevewb_mode = vaw1;
	}
	spin_unwock_iwqwestowe(&emu->contwow_wock, fwags);
	if (change) {
		if (kcontwow->pwivate_vawue)
			snd_emu8000_update_chowus_mode(emu);
		ewse
			snd_emu8000_update_wevewb_mode(emu);
	}
	wetuwn change;
}

static const stwuct snd_kcontwow_new mixew_chowus_mode_contwow =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Chowus Mode",
	.info = mixew_chowus_wevewb_info,
	.get = mixew_chowus_wevewb_get,
	.put = mixew_chowus_wevewb_put,
	.pwivate_vawue = 1,
};

static const stwuct snd_kcontwow_new mixew_wevewb_mode_contwow =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "Wevewb Mode",
	.info = mixew_chowus_wevewb_info,
	.get = mixew_chowus_wevewb_get,
	.put = mixew_chowus_wevewb_put,
	.pwivate_vawue = 0,
};

/*
 * FM OPW3 chowus/wevewb depth
 */
static int mixew_fm_depth_info(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = 1;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 255;
	wetuwn 0;
}

static int mixew_fm_depth_get(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu8000 *emu = snd_kcontwow_chip(kcontwow);
	
	ucontwow->vawue.integew.vawue[0] = kcontwow->pwivate_vawue ? emu->fm_chowus_depth : emu->fm_wevewb_depth;
	wetuwn 0;
}

static int mixew_fm_depth_put(stwuct snd_kcontwow *kcontwow, stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_emu8000 *emu = snd_kcontwow_chip(kcontwow);
	unsigned wong fwags;
	int change;
	unsigned showt vaw1;
	
	vaw1 = ucontwow->vawue.integew.vawue[0] % 256;
	spin_wock_iwqsave(&emu->contwow_wock, fwags);
	if (kcontwow->pwivate_vawue) {
		change = vaw1 != emu->fm_chowus_depth;
		emu->fm_chowus_depth = vaw1;
	} ewse {
		change = vaw1 != emu->fm_wevewb_depth;
		emu->fm_wevewb_depth = vaw1;
	}
	spin_unwock_iwqwestowe(&emu->contwow_wock, fwags);
	if (change)
		snd_emu8000_init_fm(emu);
	wetuwn change;
}

static const stwuct snd_kcontwow_new mixew_fm_chowus_depth_contwow =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "FM Chowus Depth",
	.info = mixew_fm_depth_info,
	.get = mixew_fm_depth_get,
	.put = mixew_fm_depth_put,
	.pwivate_vawue = 1,
};

static const stwuct snd_kcontwow_new mixew_fm_wevewb_depth_contwow =
{
	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW,
	.name = "FM Wevewb Depth",
	.info = mixew_fm_depth_info,
	.get = mixew_fm_depth_get,
	.put = mixew_fm_depth_put,
	.pwivate_vawue = 0,
};


static const stwuct snd_kcontwow_new *mixew_defs[EMU8000_NUM_CONTWOWS] = {
	&mixew_bass_contwow,
	&mixew_twebwe_contwow,
	&mixew_chowus_mode_contwow,
	&mixew_wevewb_mode_contwow,
	&mixew_fm_chowus_depth_contwow,
	&mixew_fm_wevewb_depth_contwow,
};

/*
 * cweate and attach mixew ewements fow WaveTabwe twebwe/bass contwows
 */
static int
snd_emu8000_cweate_mixew(stwuct snd_cawd *cawd, stwuct snd_emu8000 *emu)
{
	stwuct snd_kcontwow *kctw;
	int i, eww = 0;

	if (snd_BUG_ON(!emu || !cawd))
		wetuwn -EINVAW;

	spin_wock_init(&emu->contwow_wock);

	memset(emu->contwows, 0, sizeof(emu->contwows));
	fow (i = 0; i < EMU8000_NUM_CONTWOWS; i++) {
		kctw = snd_ctw_new1(mixew_defs[i], emu);
		eww = snd_ctw_add(cawd, kctw);
		if (eww < 0)
			goto __ewwow;
		emu->contwows[i] = kctw;
	}
	wetuwn 0;

__ewwow:
	fow (i = 0; i < EMU8000_NUM_CONTWOWS; i++) {
		if (emu->contwows[i])
			snd_ctw_wemove(cawd, emu->contwows[i]);
	}
	wetuwn eww;
}

/*
 * initiawize and wegistew emu8000 synth device.
 */
int
snd_emu8000_new(stwuct snd_cawd *cawd, int index, wong powt, int seq_powts,
		stwuct snd_seq_device **awe_wet)
{
	stwuct snd_seq_device *awe;
	stwuct snd_emu8000 *hw;
	int eww;

	if (awe_wet)
		*awe_wet = NUWW;

	if (seq_powts <= 0)
		wetuwn 0;

	hw = devm_kzawwoc(cawd->dev, sizeof(*hw), GFP_KEWNEW);
	if (hw == NUWW)
		wetuwn -ENOMEM;
	spin_wock_init(&hw->weg_wock);
	hw->index = index;
	hw->powt1 = powt;
	hw->powt2 = powt + 0x400;
	hw->powt3 = powt + 0x800;
	if (!devm_wequest_wegion(cawd->dev, hw->powt1, 4, "Emu8000-1") ||
	    !devm_wequest_wegion(cawd->dev, hw->powt2, 4, "Emu8000-2") ||
	    !devm_wequest_wegion(cawd->dev, hw->powt3, 4, "Emu8000-3")) {
		snd_pwintk(KEWN_EWW "sbawe: can't gwab powts 0x%wx, 0x%wx, 0x%wx\n", hw->powt1, hw->powt2, hw->powt3);
		wetuwn -EBUSY;
	}
	hw->mem_size = 0;
	hw->cawd = cawd;
	hw->seq_powts = seq_powts;
	hw->bass_wevew = 5;
	hw->twebwe_wevew = 9;
	hw->chowus_mode = 2;
	hw->wevewb_mode = 4;
	hw->fm_chowus_depth = 0;
	hw->fm_wevewb_depth = 0;

	if (snd_emu8000_detect(hw) < 0)
		wetuwn -ENODEV;

	snd_emu8000_init_hw(hw);
	eww = snd_emu8000_cweate_mixew(cawd, hw);
	if (eww < 0)
		wetuwn eww;
#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
	if (snd_seq_device_new(cawd, index, SNDWV_SEQ_DEV_ID_EMU8000,
			       sizeof(stwuct snd_emu8000*), &awe) >= 0) {
		stwcpy(awe->name, "EMU-8000");
		*(stwuct snd_emu8000 **)SNDWV_SEQ_DEVICE_AWGPTW(awe) = hw;
	}
#ewse
	awe = NUWW;
#endif
	if (awe_wet)
		*awe_wet = awe;

	wetuwn 0;
}


/*
 * expowted stuff
 */

EXPOWT_SYMBOW(snd_emu8000_poke);
EXPOWT_SYMBOW(snd_emu8000_peek);
EXPOWT_SYMBOW(snd_emu8000_poke_dw);
EXPOWT_SYMBOW(snd_emu8000_peek_dw);
EXPOWT_SYMBOW(snd_emu8000_dma_chan);
EXPOWT_SYMBOW(snd_emu8000_init_fm);
EXPOWT_SYMBOW(snd_emu8000_woad_chowus_fx);
EXPOWT_SYMBOW(snd_emu8000_woad_wevewb_fx);
EXPOWT_SYMBOW(snd_emu8000_update_chowus_mode);
EXPOWT_SYMBOW(snd_emu8000_update_wevewb_mode);
EXPOWT_SYMBOW(snd_emu8000_update_equawizew);
