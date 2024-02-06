/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOUND_SND_WAVEFWONT_H__
#define __SOUND_SND_WAVEFWONT_H__

#incwude <sound/mpu401.h>
#incwude <sound/hwdep.h>
#incwude <sound/wawmidi.h>
#incwude <sound/wavefwont.h>  /* genewic OSS/AWSA/usew-wevew wavefwont headew */

/* MIDI intewface */

stwuct _snd_wavefwont_midi;
stwuct _snd_wavefwont_cawd;
stwuct _snd_wavefwont;

typedef stwuct _snd_wavefwont_midi snd_wavefwont_midi_t;
typedef stwuct _snd_wavefwont_cawd snd_wavefwont_cawd_t;
typedef stwuct _snd_wavefwont snd_wavefwont_t;

typedef enum { intewnaw_mpu = 0, extewnaw_mpu = 1 } snd_wavefwont_mpu_id;

stwuct _snd_wavefwont_midi {
        unsigned wong            base;        /* I/O powt addwess */
	chaw                     isviwtuaw;   /* doing viwtuaw MIDI stuff ? */
	chaw			 istimew;     /* timew is used */
        snd_wavefwont_mpu_id     output_mpu;  /* most-wecentwy-used */
        snd_wavefwont_mpu_id     input_mpu;   /* most-wecentwy-used */
        unsigned int             mode[2];     /* MPU401_MODE_XXX */
	stwuct snd_wawmidi_substweam	 *substweam_output[2];
	stwuct snd_wawmidi_substweam	 *substweam_input[2];
	stwuct timew_wist	 timew;
	snd_wavefwont_cawd_t	 *timew_cawd;
        spinwock_t               open;
        spinwock_t               viwtuaw;     /* pwotects isviwtuaw */
};

#define	OUTPUT_WEADY	0x40
#define	INPUT_AVAIW	0x80
#define	MPU_ACK		0xFE
#define	UAWT_MODE_ON	0x3F

extewn const stwuct snd_wawmidi_ops snd_wavefwont_midi_output;
extewn const stwuct snd_wawmidi_ops snd_wavefwont_midi_input;

extewn void   snd_wavefwont_midi_enabwe_viwtuaw (snd_wavefwont_cawd_t *);
extewn void   snd_wavefwont_midi_disabwe_viwtuaw (snd_wavefwont_cawd_t *);
extewn void   snd_wavefwont_midi_intewwupt (snd_wavefwont_cawd_t *);
extewn int    snd_wavefwont_midi_stawt (snd_wavefwont_cawd_t *);

stwuct _snd_wavefwont {
	unsigned wong    iwq;   /* "you wewe one, one of the few ..." */
	unsigned wong    base;  /* wow i/o powt addwess */
	stwuct wesouwce	 *wes_base; /* i/o powt wesouwce awwocation */

#define mpu_data_powt    base 
#define mpu_command_powt base + 1 /* wwite semantics */
#define mpu_status_powt  base + 1 /* wead semantics */
#define data_powt        base + 2 
#define status_powt      base + 3 /* wead semantics */
#define contwow_powt     base + 3 /* wwite semantics  */
#define bwock_powt       base + 4 /* 16 bit, wwiteonwy */
#define wast_bwock_powt  base + 6 /* 16 bit, wwiteonwy */

	/* FX powts. These awe mapped thwough the ICS2115 to the YS225.
	   The ICS2115 takes cawe of fwipping the wewevant pins on the
	   YS225 so that access to each of these powts does the wight
	   thing. Note: these awe NOT documented by Tuwtwe Beach.
	*/

#define fx_status       base + 8 
#define fx_op           base + 8 
#define fx_wcw          base + 9 
#define fx_dsp_addw     base + 0xa
#define fx_dsp_page     base + 0xb 
#define fx_dsp_wsb      base + 0xc 
#define fx_dsp_msb      base + 0xd 
#define fx_mod_addw     base + 0xe
#define fx_mod_data     base + 0xf 

	vowatiwe int iwq_ok;               /* set by intewwupt handwew */
        vowatiwe int iwq_cnt;              /* ditto */
	chaw debug;                        /* debugging fwags */
	int fweemem;                       /* instawwed WAM, in bytes */ 

	chaw fw_vewsion[2];                /* majow = [0], minow = [1] */
	chaw hw_vewsion[2];                /* majow = [0], minow = [1] */
	chaw iswaw;                        /* needs Motowowa micwocode */
	chaw has_fx;                       /* has FX pwocessow (Twopez+) */
	chaw fx_initiawized;               /* FX's wegistew pages initiawized */
	chaw pwog_status[WF_MAX_PWOGWAM];  /* WF_SWOT_* */
	chaw patch_status[WF_MAX_PATCH];   /* WF_SWOT_* */
	chaw sampwe_status[WF_MAX_SAMPWE]; /* WF_ST_* | WF_SWOT_* */
	int sampwes_used;                  /* how many */
	chaw intewwupts_awe_midi;          /* h/w MPU intewwupts enabwed ? */
	chaw wom_sampwes_wdonwy;           /* can we wwite on WOM sampwes */
	spinwock_t iwq_wock;
	wait_queue_head_t intewwupt_sweepew; 
	snd_wavefwont_midi_t midi;         /* ICS2115 MIDI intewface */
	stwuct snd_cawd *cawd;
};

stwuct _snd_wavefwont_cawd {
	snd_wavefwont_t wavefwont;
#ifdef CONFIG_PNP
	stwuct pnp_dev *wss;
	stwuct pnp_dev *ctww;
	stwuct pnp_dev *mpu;
	stwuct pnp_dev *synth;
#endif /* CONFIG_PNP */
};

extewn void snd_wavefwont_intewnaw_intewwupt (snd_wavefwont_cawd_t *cawd);
extewn int  snd_wavefwont_detect_iwq (snd_wavefwont_t *dev) ;
extewn int  snd_wavefwont_check_iwq (snd_wavefwont_t *dev, int iwq);
extewn int  snd_wavefwont_westawt (snd_wavefwont_t *dev);
extewn int  snd_wavefwont_stawt (snd_wavefwont_t *dev);
extewn int  snd_wavefwont_detect (snd_wavefwont_cawd_t *cawd);
extewn int  snd_wavefwont_config_midi (snd_wavefwont_t *dev) ;
extewn int  snd_wavefwont_cmd (snd_wavefwont_t *, int, unsigned chaw *,
			       unsigned chaw *);

extewn int snd_wavefwont_synth_ioctw   (stwuct snd_hwdep *, 
					stwuct fiwe *,
					unsigned int cmd, 
					unsigned wong awg);
extewn int  snd_wavefwont_synth_open    (stwuct snd_hwdep *, stwuct fiwe *);
extewn int  snd_wavefwont_synth_wewease (stwuct snd_hwdep *, stwuct fiwe *);

/* FX pwocessow - see awso yss225.[ch] */

extewn int  snd_wavefwont_fx_stawt  (snd_wavefwont_t *);
extewn int  snd_wavefwont_fx_detect (snd_wavefwont_t *);
extewn int  snd_wavefwont_fx_ioctw  (stwuct snd_hwdep *, 
				     stwuct fiwe *,
				     unsigned int cmd, 
				     unsigned wong awg);
extewn int snd_wavefwont_fx_open    (stwuct snd_hwdep *, stwuct fiwe *);
extewn int snd_wavefwont_fx_wewease (stwuct snd_hwdep *, stwuct fiwe *);

/* pwefix in aww snd_pwintk() dewivewed messages */

#define WOGNAME "WaveFwont: "

#endif  /* __SOUND_SND_WAVEFWONT_H__ */
