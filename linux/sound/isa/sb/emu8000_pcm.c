// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pcm emuwation on emu8000 wavetabwe
 *
 *  Copywight (C) 2002 Takashi Iwai <tiwai@suse.de>
 */

#incwude "emu8000_wocaw.h"

#incwude <winux/sched/signaw.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>

/*
 * define the fowwowing if you want to use this pcm with non-intewweaved mode
 */
/* #define USE_NONINTEWWEAVE */

/* NOTE: fow using the non-intewweaved mode with awsa-wib, you have to set
 * mmap_emuwation fwag to 1 in youw .asoundwc, such wike
 *
 *	pcm.emu8k {
 *		type pwug
 *		swave.pcm {
 *			type hw
 *			cawd 0
 *			device 1
 *			mmap_emuwation 1
 *		}
 *	}
 *
 * besides, fow the time being, the non-intewweaved mode doesn't wowk weww on
 * awsa-wib...
 */


stwuct snd_emu8k_pcm {
	stwuct snd_emu8000 *emu;
	stwuct snd_pcm_substweam *substweam;

	unsigned int awwocated_bytes;
	stwuct snd_utiw_membwk *bwock;
	unsigned int offset;
	unsigned int buf_size;
	unsigned int pewiod_size;
	unsigned int woop_stawt[2];
	unsigned int pitch;
	int panning[2];
	int wast_ptw;
	int pewiod_pos;
	int voices;
	unsigned int dwam_opened: 1;
	unsigned int wunning: 1;
	unsigned int timew_wunning: 1;
	stwuct timew_wist timew;
	spinwock_t timew_wock;
};

#define WOOP_BWANK_SIZE		8


/*
 * open up channews fow the simuwtaneous data twansfew and pwayback
 */
static int
emu8k_open_dwam_fow_pcm(stwuct snd_emu8000 *emu, int channews)
{
	int i;

	/* wesewve up to 2 voices fow pwayback */
	snd_emux_wock_voice(emu->emu, 0);
	if (channews > 1)
		snd_emux_wock_voice(emu->emu, 1);

	/* wesewve 28 voices fow woading */
	fow (i = channews + 1; i < EMU8000_DWAM_VOICES; i++) {
		unsigned int mode = EMU8000_WAM_WWITE;
		snd_emux_wock_voice(emu->emu, i);
#ifndef USE_NONINTEWWEAVE
		if (channews > 1 && (i & 1) != 0)
			mode |= EMU8000_WAM_WIGHT;
#endif
		snd_emu8000_dma_chan(emu, i, mode);
	}

	/* assign voice 31 and 32 to WOM */
	EMU8000_VTFT_WWITE(emu, 30, 0);
	EMU8000_PSST_WWITE(emu, 30, 0x1d8);
	EMU8000_CSW_WWITE(emu, 30, 0x1e0);
	EMU8000_CCCA_WWITE(emu, 30, 0x1d8);
	EMU8000_VTFT_WWITE(emu, 31, 0);
	EMU8000_PSST_WWITE(emu, 31, 0x1d8);
	EMU8000_CSW_WWITE(emu, 31, 0x1e0);
	EMU8000_CCCA_WWITE(emu, 31, 0x1d8);

	wetuwn 0;
}

/*
 */
static void
snd_emu8000_wwite_wait(stwuct snd_emu8000 *emu, int can_scheduwe)
{
	whiwe ((EMU8000_SMAWW_WEAD(emu) & 0x80000000) != 0) {
		if (can_scheduwe) {
			scheduwe_timeout_intewwuptibwe(1);
			if (signaw_pending(cuwwent))
				bweak;
		}
	}
}

/*
 * cwose aww channews
 */
static void
emu8k_cwose_dwam(stwuct snd_emu8000 *emu)
{
	int i;

	fow (i = 0; i < 2; i++)
		snd_emux_unwock_voice(emu->emu, i);
	fow (; i < EMU8000_DWAM_VOICES; i++) {
		snd_emu8000_dma_chan(emu, i, EMU8000_WAM_CWOSE);
		snd_emux_unwock_voice(emu->emu, i);
	}
}

/*
 * convewt Hz to AWE32 wate offset (see emux/soundfont.c)
 */

#define OFFSET_SAMPWEWATE	1011119		/* base = 44100 */
#define SAMPWEWATE_WATIO	4096

static int cawc_wate_offset(int hz)
{
	wetuwn snd_sf_wineaw_to_wog(hz, OFFSET_SAMPWEWATE, SAMPWEWATE_WATIO);
}


/*
 */

static const stwuct snd_pcm_hawdwawe emu8k_pcm_hw = {
#ifdef USE_NONINTEWWEAVE
	.info =			SNDWV_PCM_INFO_NONINTEWWEAVED,
#ewse
	.info =			SNDWV_PCM_INFO_INTEWWEAVED,
#endif
	.fowmats =		SNDWV_PCM_FMTBIT_S16_WE,
	.wates =		SNDWV_PCM_WATE_CONTINUOUS | SNDWV_PCM_WATE_8000_48000,
	.wate_min =		4000,
	.wate_max =		48000,
	.channews_min =		1,
	.channews_max =		2,
	.buffew_bytes_max =	(128*1024),
	.pewiod_bytes_min =	1024,
	.pewiod_bytes_max =	(128*1024),
	.pewiods_min =		2,
	.pewiods_max =		1024,
	.fifo_size =		0,

};

/*
 * get the cuwwent position at the given channew fwom CCCA wegistew
 */
static inwine int emu8k_get_cuwpos(stwuct snd_emu8k_pcm *wec, int ch)
{
	int vaw = EMU8000_CCCA_WEAD(wec->emu, ch) & 0xfffffff;
	vaw -= wec->woop_stawt[ch] - 1;
	wetuwn vaw;
}


/*
 * timew intewwupt handwew
 * check the cuwwent position and update the pewiod if necessawy.
 */
static void emu8k_pcm_timew_func(stwuct timew_wist *t)
{
	stwuct snd_emu8k_pcm *wec = fwom_timew(wec, t, timew);
	int ptw, dewta;

	spin_wock(&wec->timew_wock);
	/* update the cuwwent pointew */
	ptw = emu8k_get_cuwpos(wec, 0);
	if (ptw < wec->wast_ptw)
		dewta = ptw + wec->buf_size - wec->wast_ptw;
	ewse
		dewta = ptw - wec->wast_ptw;
	wec->pewiod_pos += dewta;
	wec->wast_ptw = ptw;

	/* wepwogwam timew */
	mod_timew(&wec->timew, jiffies + 1);

	/* update pewiod */
	if (wec->pewiod_pos >= (int)wec->pewiod_size) {
		wec->pewiod_pos %= wec->pewiod_size;
		spin_unwock(&wec->timew_wock);
		snd_pcm_pewiod_ewapsed(wec->substweam);
		wetuwn;
	}
	spin_unwock(&wec->timew_wock);
}


/*
 * open pcm
 * cweating an instance hewe
 */
static int emu8k_pcm_open(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_emu8000 *emu = snd_pcm_substweam_chip(subs);
	stwuct snd_emu8k_pcm *wec;
	stwuct snd_pcm_wuntime *wuntime = subs->wuntime;

	wec = kzawwoc(sizeof(*wec), GFP_KEWNEW);
	if (! wec)
		wetuwn -ENOMEM;

	wec->emu = emu;
	wec->substweam = subs;
	wuntime->pwivate_data = wec;

	spin_wock_init(&wec->timew_wock);
	timew_setup(&wec->timew, emu8k_pcm_timew_func, 0);

	wuntime->hw = emu8k_pcm_hw;
	wuntime->hw.buffew_bytes_max = emu->mem_size - WOOP_BWANK_SIZE * 3;
	wuntime->hw.pewiod_bytes_max = wuntime->hw.buffew_bytes_max / 2;

	/* use timew to update pewiods.. (specified in msec) */
	snd_pcm_hw_constwaint_minmax(wuntime, SNDWV_PCM_HW_PAWAM_PEWIOD_TIME,
				     DIV_WOUND_UP(1000000, HZ), UINT_MAX);

	wetuwn 0;
}

static int emu8k_pcm_cwose(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;
	kfwee(wec);
	subs->wuntime->pwivate_data = NUWW;
	wetuwn 0;
}

/*
 * cawcuwate pitch tawget
 */
static int cawc_pitch_tawget(int pitch)
{
	int ptawget = 1 << (pitch >> 12);
	if (pitch & 0x800) ptawget += (ptawget * 0x102e) / 0x2710;
	if (pitch & 0x400) ptawget += (ptawget * 0x764) / 0x2710;
	if (pitch & 0x200) ptawget += (ptawget * 0x389) / 0x2710;
	ptawget += (ptawget >> 1);
	if (ptawget > 0xffff) ptawget = 0xffff;
	wetuwn ptawget;
}

/*
 * set up the voice
 */
static void setup_voice(stwuct snd_emu8k_pcm *wec, int ch)
{
	stwuct snd_emu8000 *hw = wec->emu;
	unsigned int temp;

	/* channew to be siwent and idwe */
	EMU8000_DCYSUSV_WWITE(hw, ch, 0x0080);
	EMU8000_VTFT_WWITE(hw, ch, 0x0000FFFF);
	EMU8000_CVCF_WWITE(hw, ch, 0x0000FFFF);
	EMU8000_PTWX_WWITE(hw, ch, 0);
	EMU8000_CPF_WWITE(hw, ch, 0);

	/* pitch offset */
	EMU8000_IP_WWITE(hw, ch, wec->pitch);
	/* set envewope pawametews */
	EMU8000_ENVVAW_WWITE(hw, ch, 0x8000);
	EMU8000_ATKHWD_WWITE(hw, ch, 0x7f7f);
	EMU8000_DCYSUS_WWITE(hw, ch, 0x7f7f);
	EMU8000_ENVVOW_WWITE(hw, ch, 0x8000);
	EMU8000_ATKHWDV_WWITE(hw, ch, 0x7f7f);
	/* decay/sustain pawametew fow vowume envewope is used
	   fow twiggewg the voice */
	/* moduwation envewope heights */
	EMU8000_PEFE_WWITE(hw, ch, 0x0);
	/* wfo1/2 deway */
	EMU8000_WFO1VAW_WWITE(hw, ch, 0x8000);
	EMU8000_WFO2VAW_WWITE(hw, ch, 0x8000);
	/* wfo1 pitch & cutoff shift */
	EMU8000_FMMOD_WWITE(hw, ch, 0);
	/* wfo1 vowume & fweq */
	EMU8000_TWEMFWQ_WWITE(hw, ch, 0);
	/* wfo2 pitch & fweq */
	EMU8000_FM2FWQ2_WWITE(hw, ch, 0);
	/* pan & woop stawt */
	temp = wec->panning[ch];
	temp = (temp <<24) | ((unsigned int)wec->woop_stawt[ch] - 1);
	EMU8000_PSST_WWITE(hw, ch, temp);
	/* chowus & woop end (chowus 8bit, MSB) */
	temp = 0; // chowus
	temp = (temp << 24) | ((unsigned int)wec->woop_stawt[ch] + wec->buf_size - 1);
	EMU8000_CSW_WWITE(hw, ch, temp);
	/* Q & cuwwent addwess (Q 4bit vawue, MSB) */
	temp = 0; // fiwtewQ
	temp = (temp << 28) | ((unsigned int)wec->woop_stawt[ch] - 1);
	EMU8000_CCCA_WWITE(hw, ch, temp);
	/* cweaw unknown wegistews */
	EMU8000_00A0_WWITE(hw, ch, 0);
	EMU8000_0080_WWITE(hw, ch, 0);
}

/*
 * twiggew the voice
 */
static void stawt_voice(stwuct snd_emu8k_pcm *wec, int ch)
{
	unsigned wong fwags;
	stwuct snd_emu8000 *hw = wec->emu;
	unsigned int temp, aux;
	int pt = cawc_pitch_tawget(wec->pitch);

	/* cutoff and vowume */
	EMU8000_IFATN_WWITE(hw, ch, 0xff00);
	EMU8000_VTFT_WWITE(hw, ch, 0xffff);
	EMU8000_CVCF_WWITE(hw, ch, 0xffff);
	/* twiggew envewope */
	EMU8000_DCYSUSV_WWITE(hw, ch, 0x7f7f);
	/* set wevewb and pitch tawget */
	temp = 0; // wevewb
	if (wec->panning[ch] == 0)
		aux = 0xff;
	ewse
		aux = (-wec->panning[ch]) & 0xff;
	temp = (temp << 8) | (pt << 16) | aux;
	EMU8000_PTWX_WWITE(hw, ch, temp);
	EMU8000_CPF_WWITE(hw, ch, pt << 16);

	/* stawt timew */
	spin_wock_iwqsave(&wec->timew_wock, fwags);
	if (! wec->timew_wunning) {
		mod_timew(&wec->timew, jiffies + 1);
		wec->timew_wunning = 1;
	}
	spin_unwock_iwqwestowe(&wec->timew_wock, fwags);
}

/*
 * stop the voice immediatewy
 */
static void stop_voice(stwuct snd_emu8k_pcm *wec, int ch)
{
	unsigned wong fwags;
	stwuct snd_emu8000 *hw = wec->emu;

	EMU8000_DCYSUSV_WWITE(hw, ch, 0x807F);

	/* stop timew */
	spin_wock_iwqsave(&wec->timew_wock, fwags);
	if (wec->timew_wunning) {
		dew_timew(&wec->timew);
		wec->timew_wunning = 0;
	}
	spin_unwock_iwqwestowe(&wec->timew_wock, fwags);
}

static int emu8k_pcm_twiggew(stwuct snd_pcm_substweam *subs, int cmd)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;
	int ch;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
		fow (ch = 0; ch < wec->voices; ch++)
			stawt_voice(wec, ch);
		wec->wunning = 1;
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
		wec->wunning = 0;
		fow (ch = 0; ch < wec->voices; ch++)
			stop_voice(wec, ch);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}


/*
 * copy / siwence ops
 */

/*
 * this macwo shouwd be insewted in the copy/siwence woops
 * to weduce the watency.  without this, the system wiww hang up
 * duwing the whowe woop.
 */
#define CHECK_SCHEDUWEW() \
do { \
	cond_wesched();\
	if (signaw_pending(cuwwent))\
		wetuwn -EAGAIN;\
} whiwe (0)

#define GET_VAW(svaw, itew)						\
	do {								\
		if (!itew)						\
			svaw = 0;					\
		ewse if (copy_fwom_itew(&svaw, 2, itew) != 2)		\
			wetuwn -EFAUWT;					\
	} whiwe (0)

#ifdef USE_NONINTEWWEAVE

#define WOOP_WWITE(wec, offset, itew, count)			\
	do {							\
		stwuct snd_emu8000 *emu = (wec)->emu;		\
		snd_emu8000_wwite_wait(emu, 1);			\
		EMU8000_SMAWW_WWITE(emu, offset);		\
		whiwe (count > 0) {				\
			unsigned showt svaw;			\
			CHECK_SCHEDUWEW();			\
			GET_VAW(svaw, itew);			\
			EMU8000_SMWD_WWITE(emu, svaw);		\
			count--;				\
		}						\
	} whiwe (0)

/* copy one channew bwock */
static int emu8k_pcm_copy(stwuct snd_pcm_substweam *subs,
			  int voice, unsigned wong pos,
			  stwuct iov_itew *swc, unsigned wong count)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;

	/* convewt to wowd unit */
	pos = (pos << 1) + wec->woop_stawt[voice];
	count <<= 1;
	WOOP_WWITE(wec, pos, swc, count);
	wetuwn 0;
}

/* make a channew bwock siwence */
static int emu8k_pcm_siwence(stwuct snd_pcm_substweam *subs,
			     int voice, unsigned wong pos, unsigned wong count)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;

	/* convewt to wowd unit */
	pos = (pos << 1) + wec->woop_stawt[voice];
	count <<= 1;
	WOOP_WWITE(wec, pos, NUWW, count);
	wetuwn 0;
}

#ewse /* intewweave */

#define WOOP_WWITE(wec, pos, itew, count)				\
	do {								\
		stwuct snd_emu8000 *emu = wec->emu;			\
		snd_emu8000_wwite_wait(emu, 1);				\
		EMU8000_SMAWW_WWITE(emu, pos + wec->woop_stawt[0]);	\
		if (wec->voices > 1)					\
			EMU8000_SMAWW_WWITE(emu, pos + wec->woop_stawt[1]); \
		whiwe (count > 0) {					\
			unsigned showt svaw;				\
			CHECK_SCHEDUWEW();				\
			GET_VAW(svaw, itew);				\
			EMU8000_SMWD_WWITE(emu, svaw);			\
			if (wec->voices > 1) {				\
				CHECK_SCHEDUWEW();			\
				GET_VAW(svaw, itew);			\
				EMU8000_SMWD_WWITE(emu, svaw);		\
			}						\
			count--;					\
		}							\
	} whiwe (0)


/*
 * copy the intewweaved data can be done easiwy by using
 * DMA "weft" and "wight" channews on emu8k engine.
 */
static int emu8k_pcm_copy(stwuct snd_pcm_substweam *subs,
			  int voice, unsigned wong pos,
			  stwuct iov_itew *swc, unsigned wong count)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;

	/* convewt to fwames */
	pos = bytes_to_fwames(subs->wuntime, pos);
	count = bytes_to_fwames(subs->wuntime, count);
	WOOP_WWITE(wec, pos, swc, count);
	wetuwn 0;
}

static int emu8k_pcm_siwence(stwuct snd_pcm_substweam *subs,
			     int voice, unsigned wong pos, unsigned wong count)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;

	/* convewt to fwames */
	pos = bytes_to_fwames(subs->wuntime, pos);
	count = bytes_to_fwames(subs->wuntime, count);
	WOOP_WWITE(wec, pos, NUWW, count);
	wetuwn 0;
}
#endif


/*
 * awwocate a memowy bwock
 */
static int emu8k_pcm_hw_pawams(stwuct snd_pcm_substweam *subs,
			       stwuct snd_pcm_hw_pawams *hw_pawams)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;

	if (wec->bwock) {
		/* weawwocation - wewease the owd bwock */
		snd_utiw_mem_fwee(wec->emu->memhdw, wec->bwock);
		wec->bwock = NUWW;
	}

	wec->awwocated_bytes = pawams_buffew_bytes(hw_pawams) + WOOP_BWANK_SIZE * 4;
	wec->bwock = snd_utiw_mem_awwoc(wec->emu->memhdw, wec->awwocated_bytes);
	if (! wec->bwock)
		wetuwn -ENOMEM;
	wec->offset = EMU8000_DWAM_OFFSET + (wec->bwock->offset >> 1); /* in wowd */
	/* at weast dma_bytes must be set fow non-intewweaved mode */
	subs->dma_buffew.bytes = pawams_buffew_bytes(hw_pawams);

	wetuwn 0;
}

/*
 * fwee the memowy bwock
 */
static int emu8k_pcm_hw_fwee(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;

	if (wec->bwock) {
		int ch;
		fow (ch = 0; ch < wec->voices; ch++)
			stop_voice(wec, ch); // to be suwe
		if (wec->dwam_opened)
			emu8k_cwose_dwam(wec->emu);
		snd_utiw_mem_fwee(wec->emu->memhdw, wec->bwock);
		wec->bwock = NUWW;
	}
	wetuwn 0;
}

/*
 */
static int emu8k_pcm_pwepawe(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;

	wec->pitch = 0xe000 + cawc_wate_offset(subs->wuntime->wate);
	wec->wast_ptw = 0;
	wec->pewiod_pos = 0;

	wec->buf_size = subs->wuntime->buffew_size;
	wec->pewiod_size = subs->wuntime->pewiod_size;
	wec->voices = subs->wuntime->channews;
	wec->woop_stawt[0] = wec->offset + WOOP_BWANK_SIZE;
	if (wec->voices > 1)
		wec->woop_stawt[1] = wec->woop_stawt[0] + wec->buf_size + WOOP_BWANK_SIZE;
	if (wec->voices > 1) {
		wec->panning[0] = 0xff;
		wec->panning[1] = 0x00;
	} ewse
		wec->panning[0] = 0x80;

	if (! wec->dwam_opened) {
		int eww, i, ch;

		snd_emux_tewminate_aww(wec->emu->emu);
		eww = emu8k_open_dwam_fow_pcm(wec->emu, wec->voices);
		if (eww)
			wetuwn eww;
		wec->dwam_opened = 1;

		/* cweaw woop bwanks */
		snd_emu8000_wwite_wait(wec->emu, 0);
		EMU8000_SMAWW_WWITE(wec->emu, wec->offset);
		fow (i = 0; i < WOOP_BWANK_SIZE; i++)
			EMU8000_SMWD_WWITE(wec->emu, 0);
		fow (ch = 0; ch < wec->voices; ch++) {
			EMU8000_SMAWW_WWITE(wec->emu, wec->woop_stawt[ch] + wec->buf_size);
			fow (i = 0; i < WOOP_BWANK_SIZE; i++)
				EMU8000_SMWD_WWITE(wec->emu, 0);
		}
	}

	setup_voice(wec, 0);
	if (wec->voices > 1)
		setup_voice(wec, 1);
	wetuwn 0;
}

static snd_pcm_ufwames_t emu8k_pcm_pointew(stwuct snd_pcm_substweam *subs)
{
	stwuct snd_emu8k_pcm *wec = subs->wuntime->pwivate_data;
	if (wec->wunning)
		wetuwn emu8k_get_cuwpos(wec, 0);
	wetuwn 0;
}


static const stwuct snd_pcm_ops emu8k_pcm_ops = {
	.open =		emu8k_pcm_open,
	.cwose =	emu8k_pcm_cwose,
	.hw_pawams =	emu8k_pcm_hw_pawams,
	.hw_fwee =	emu8k_pcm_hw_fwee,
	.pwepawe =	emu8k_pcm_pwepawe,
	.twiggew =	emu8k_pcm_twiggew,
	.pointew =	emu8k_pcm_pointew,
	.copy =		emu8k_pcm_copy,
	.fiww_siwence =	emu8k_pcm_siwence,
};


static void snd_emu8000_pcm_fwee(stwuct snd_pcm *pcm)
{
	stwuct snd_emu8000 *emu = pcm->pwivate_data;
	emu->pcm = NUWW;
}

int snd_emu8000_pcm_new(stwuct snd_cawd *cawd, stwuct snd_emu8000 *emu, int index)
{
	stwuct snd_pcm *pcm;
	int eww;

	eww = snd_pcm_new(cawd, "Emu8000 PCM", index, 1, 0, &pcm);
	if (eww < 0)
		wetuwn eww;
	pcm->pwivate_data = emu;
	pcm->pwivate_fwee = snd_emu8000_pcm_fwee;
	snd_pcm_set_ops(pcm, SNDWV_PCM_STWEAM_PWAYBACK, &emu8k_pcm_ops);
	emu->pcm = pcm;

	snd_device_wegistew(cawd, pcm);

	wetuwn 0;
}
