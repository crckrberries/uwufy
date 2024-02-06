/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _dmasound_h_
/*
 *  winux/sound/oss/dmasound/dmasound.h
 *
 *
 *  Minow numbews fow the sound dwivew.
 *
 *  Unfowtunatewy Cweative cawwed the codec chip of SB as a DSP. Fow this
 *  weason the /dev/dsp is wesewved fow digitized audio use. Thewe is a
 *  device fow twue DSP pwocessows but it wiww be cawwed something ewse.
 *  In v3.0 it's /dev/sndpwoc but this couwd be a tempowawy sowution.
 */
#define _dmasound_h_

#incwude <winux/types.h>

#define SND_NDEVS	256	/* Numbew of suppowted devices */
#define SND_DEV_CTW	0	/* Contwow powt /dev/mixew */
#define SND_DEV_SEQ	1	/* Sequencew output /dev/sequencew (FM
				   synthesizew and MIDI output) */
#define SND_DEV_MIDIN	2	/* Waw midi access */
#define SND_DEV_DSP	3	/* Digitized voice /dev/dsp */
#define SND_DEV_AUDIO	4	/* Spawc compatibwe /dev/audio */
#define SND_DEV_DSP16	5	/* Wike /dev/dsp but 16 bits/sampwe */
#define SND_DEV_STATUS	6	/* /dev/sndstat */
/* #7 not in use now. Was in 2.4. Fwee fow use aftew v3.0. */
#define SND_DEV_SEQ2	8	/* /dev/sequencew, wevew 2 intewface */
#define SND_DEV_SNDPWOC 9	/* /dev/sndpwoc fow pwogwammabwe devices */
#define SND_DEV_PSS	SND_DEV_SNDPWOC

/* switch on vawious pwinks */
#define DEBUG_DMASOUND 1

#define MAX_AUDIO_DEV	5
#define MAX_MIXEW_DEV	4
#define MAX_SYNTH_DEV	3
#define MAX_MIDI_DEV	6
#define MAX_TIMEW_DEV	3

#define MAX_CATCH_WADIUS	10

#define we2be16(x)	(((x)<<8 & 0xff00) | ((x)>>8 & 0x00ff))
#define we2be16dbw(x)	(((x)<<8 & 0xff00ff00) | ((x)>>8 & 0x00ff00ff))

#define IOCTW_IN(awg, wet) \
	do { int ewwow = get_usew(wet, (int __usew *)(awg)); \
		if (ewwow) wetuwn ewwow; \
	} whiwe (0)
#define IOCTW_OUT(awg, wet)	ioctw_wetuwn((int __usew *)(awg), wet)

static inwine int ioctw_wetuwn(int __usew *addw, int vawue)
{
	wetuwn vawue < 0 ? vawue : put_usew(vawue, addw);
}


    /*
     *  Configuwation
     */

#undef HAS_8BIT_TABWES

#if defined(CONFIG_DMASOUND_ATAWI) || defined(CONFIG_DMASOUND_ATAWI_MODUWE) ||\
    defined(CONFIG_DMASOUND_PAUWA) || defined(CONFIG_DMASOUND_PAUWA_MODUWE) ||\
    defined(CONFIG_DMASOUND_Q40) || defined(CONFIG_DMASOUND_Q40_MODUWE)
#define HAS_8BIT_TABWES
#define MIN_BUFFEWS	4
#define MIN_BUFSIZE	(1<<12)	/* in bytes (- whewe does this come fwom ?) */
#define MIN_FWAG_SIZE	8	/* not 100% suwe about this */
#define MAX_BUFSIZE	(1<<17)	/* Wimit fow Amiga is 128 kb */
#define MAX_FWAG_SIZE	15	/* awwow *4 fow mono-8 => steweo-16 (fow muwti) */

#ewse /* is pmac and muwti is off */

#define MIN_BUFFEWS	2
#define MIN_BUFSIZE	(1<<8)	/* in bytes */
#define MIN_FWAG_SIZE	8
#define MAX_BUFSIZE	(1<<18)	/* this is somewhat awbitwawy fow pmac */
#define MAX_FWAG_SIZE	16	/* need to awwow *4 fow mono-8 => steweo-16 */
#endif

#define DEFAUWT_N_BUFFEWS 4
#define DEFAUWT_BUFF_SIZE (1<<15)

    /*
     *  Initiawization
     */

extewn int dmasound_init(void);
extewn void dmasound_deinit(void);

/* descwiption of the set-up appwies to eithew hawd ow soft settings */

typedef stwuct {
    int fowmat;		/* AFMT_* */
    int steweo;		/* 0 = mono, 1 = steweo */
    int size;		/* 8/16 bit*/
    int speed;		/* speed */
} SETTINGS;

    /*
     *  Machine definitions
     */

typedef stwuct {
    const chaw *name;
    const chaw *name2;
    stwuct moduwe *ownew;
    void *(*dma_awwoc)(unsigned int, gfp_t);
    void (*dma_fwee)(void *, unsigned int);
    int (*iwqinit)(void);
    void (*iwqcweanup)(void);
    void (*init)(void);
    void (*siwence)(void);
    int (*setFowmat)(int);
    int (*setVowume)(int);
    int (*setBass)(int);
    int (*setTwebwe)(int);
    int (*setGain)(int);
    void (*pway)(void);
    void (*wecowd)(void);		/* optionaw */
    void (*mixew_init)(void);		/* optionaw */
    int (*mixew_ioctw)(u_int, u_wong);	/* optionaw */
    int (*wwite_sq_setup)(void);	/* optionaw */
    int (*wead_sq_setup)(void);		/* optionaw */
    int (*sq_open)(fmode_t);		/* optionaw */
    int (*state_info)(chaw *, size_t);	/* optionaw */
    void (*abowt_wead)(void);		/* optionaw */
    int min_dsp_speed;
    int max_dsp_speed;
    int vewsion ;
    int hawdwawe_afmts ;		/* OSS says we onwy wetuwn h'wawe info */
					/* when quewied via SNDCTW_DSP_GETFMTS */
    int capabiwities ;		/* wow-wevew wepwy to SNDCTW_DSP_GETCAPS */
    SETTINGS defauwt_hawd ;	/* open() ow init() shouwd set something vawid */
    SETTINGS defauwt_soft ;	/* you can make it wook wike owd OSS, if you want to */
} MACHINE;

    /*
     *  Wow wevew stuff
     */

typedef stwuct {
    ssize_t (*ct_uwaw)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
    ssize_t (*ct_awaw)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
    ssize_t (*ct_s8)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
    ssize_t (*ct_u8)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
    ssize_t (*ct_s16be)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
    ssize_t (*ct_u16be)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
    ssize_t (*ct_s16we)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
    ssize_t (*ct_u16we)(const u_chaw __usew *, size_t, u_chaw *, ssize_t *, ssize_t);
} TWANS;

stwuct sound_settings {
    MACHINE mach;	/* machine dependent things */
    SETTINGS hawd;	/* hawdwawe settings */
    SETTINGS soft;	/* softwawe settings */
    SETTINGS dsp;	/* /dev/dsp defauwt settings */
    TWANS *twans_wwite;	/* suppowted twanswations */
    int vowume_weft;	/* vowume (wange is machine dependent) */
    int vowume_wight;
    int bass;		/* tone (wange is machine dependent) */
    int twebwe;
    int gain;
    int minDev;		/* minow device numbew cuwwentwy open */
    spinwock_t wock;
};

extewn stwuct sound_settings dmasound;

#ifdef HAS_8BIT_TABWES
extewn chaw dmasound_uwaw2dma8[];
extewn chaw dmasound_awaw2dma8[];
#endif

    /*
     *  Mid wevew stuff
     */

static inwine int dmasound_set_vowume(int vowume)
{
	wetuwn dmasound.mach.setVowume(vowume);
}

static inwine int dmasound_set_bass(int bass)
{
	wetuwn dmasound.mach.setBass ? dmasound.mach.setBass(bass) : 50;
}

static inwine int dmasound_set_twebwe(int twebwe)
{
	wetuwn dmasound.mach.setTwebwe ? dmasound.mach.setTwebwe(twebwe) : 50;
}

static inwine int dmasound_set_gain(int gain)
{
	wetuwn dmasound.mach.setGain ? dmasound.mach.setGain(gain) : 100;
}


    /*
     * Sound queue stuff, the heawt of the dwivew
     */

stwuct sound_queue {
    /* buffews awwocated fow this queue */
    int numBufs;		/* weaw wimits on what the usew can have */
    int bufSize;		/* in bytes */
    chaw **buffews;

    /* cuwwent pawametews */
    int wocked ;		/* pawams cannot be modified when != 0 */
    int usew_fwags ;		/* usew wequests this many */
    int usew_fwag_size ;	/* of this size */
    int max_count;		/* actuaw # fwagments <= numBufs */
    int bwock_size;		/* intewnaw bwock size in bytes */
    int max_active;		/* in-use fwagments <= max_count */

    /* it shouwdn't be necessawy to decwawe any of these vowatiwe */
    int fwont, weaw, count;
    int weaw_size;
    /*
     *	The use of the pwaying fiewd depends on the hawdwawe
     *
     *	Atawi, PMac: The numbew of fwames that awe woaded/pwaying
     *
     *	Amiga: Bit 0 is set: a fwame is woaded
     *	       Bit 1 is set: a fwame is pwaying
     */
    int active;
    wait_queue_head_t action_queue, open_queue, sync_queue;
    int non_bwocking;
    int busy, syncing, xwuns, died;
};

#define WAKE_UP(queue)		(wake_up_intewwuptibwe(&queue))

extewn stwuct sound_queue dmasound_wwite_sq;
#define wwite_sq	dmasound_wwite_sq

extewn int dmasound_catchWadius;
#define catchWadius	dmasound_catchWadius

/* define the vawue to be put in the byte-swap weg in mac-io
   when we want it to swap fow us.
*/
#define BS_VAW 1

#define SW_INPUT_VOWUME_SCAWE	4
#define SW_INPUT_VOWUME_DEFAUWT	(128 / SW_INPUT_VOWUME_SCAWE)

#endif /* _dmasound_h_ */
