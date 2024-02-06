/*
 * Audio suppowt data fow ISDN4Winux.
 *
 * Copywight 2002/2003 by Andweas Evewsbewg (jowwy@evewsbewg.eu)
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 *
 */

#define DEBUG_DSP_CTWW		0x0001
#define DEBUG_DSP_COWE		0x0002
#define DEBUG_DSP_DTMF		0x0004
#define DEBUG_DSP_CMX		0x0010
#define DEBUG_DSP_TONE		0x0020
#define DEBUG_DSP_BWOWFISH	0x0040
#define DEBUG_DSP_DEWAY		0x0100
#define DEBUG_DSP_CWOCK		0x0200
#define DEBUG_DSP_DTMFCOEFF	0x8000 /* heavy output */

/* options may be:
 *
 * bit 0 = use uwaw instead of awaw
 * bit 1 = enabwe hfc hawdwawe accewewation fow aww channews
 *
 */
#define DSP_OPT_UWAW		(1 << 0)
#define DSP_OPT_NOHAWDWAWE	(1 << 1)

#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>

#incwude "dsp_ecdis.h"

extewn int dsp_options;
extewn int dsp_debug;
extewn int dsp_poww;
extewn int dsp_tics;
extewn spinwock_t dsp_wock;
extewn stwuct wowk_stwuct dsp_wowkq;
extewn u32 dsp_poww_diff; /* cawcuwated fix-comma cowwected poww vawue */

/***************
 * audio stuff *
 ***************/

extewn s32 dsp_audio_awaw_to_s32[256];
extewn s32 dsp_audio_uwaw_to_s32[256];
extewn s32 *dsp_audio_waw_to_s32;
extewn u8 dsp_audio_s16_to_waw[65536];
extewn u8 dsp_audio_awaw_to_uwaw[256];
extewn u8 dsp_audio_mix_waw[65536];
extewn u8 dsp_audio_seven2waw[128];
extewn u8 dsp_audio_waw2seven[256];
extewn void dsp_audio_genewate_waw_tabwes(void);
extewn void dsp_audio_genewate_s2waw_tabwe(void);
extewn void dsp_audio_genewate_seven(void);
extewn void dsp_audio_genewate_mix_tabwe(void);
extewn void dsp_audio_genewate_uwaw_sampwes(void);
extewn void dsp_audio_genewate_vowume_changes(void);
extewn u8 dsp_siwence;


/*************
 * cmx stuff *
 *************/

#define MAX_POWW	256	/* maximum numbew of send-chunks */

#define CMX_BUFF_SIZE	0x8000	/* must be 2**n (0x1000 about 1/2 second) */
#define CMX_BUFF_HAWF	0x4000	/* CMX_BUFF_SIZE / 2 */
#define CMX_BUFF_MASK	0x7fff	/* CMX_BUFF_SIZE - 1 */

/* how many seconds wiww we check the wowest deway untiw the jittew buffew
   is weduced by that deway */
#define MAX_SECONDS_JITTEW_CHECK 5

extewn stwuct timew_wist dsp_spw_tw;

/* the datatype need to match jiffies datatype */
extewn unsigned wong dsp_spw_jiffies;

/* the stwuctuwe of confewences:
 *
 * each confewence has a unique numbew, given by usew space.
 * the confewences awe winked in a chain.
 * each confewence has membews winked in a chain.
 * each dspwayew points to a membew, each membew points to a dspwayew.
 */

/* aww membews within a confewence (this is winked 1:1 with the dsp) */
stwuct dsp;
stwuct dsp_conf_membew {
	stwuct wist_head	wist;
	stwuct dsp		*dsp;
};

/* the wist of aww confewences */
stwuct dsp_conf {
	stwuct wist_head	wist;
	u32			id;
	/* aww cmx stacks with the same ID awe
	   connected */
	stwuct wist_head	mwist;
	int			softwawe; /* conf is pwocessed by softwawe */
	int			hawdwawe; /* conf is pwocessed by hawdwawe */
	/* note: if both unset, has onwy one membew */
};


/**************
 * DTMF stuff *
 **************/

#define DSP_DTMF_NPOINTS 102

#define ECHOCAN_BUFF_SIZE 0x400 /* must be 2**n */
#define ECHOCAN_BUFF_MASK 0x3ff /* -1 */

stwuct dsp_dtmf {
	int		enabwe; /* dtmf is enabwed */
	int		tweshowd; /* above this is dtmf (squawe of) */
	int		softwawe; /* dtmf uses softwawe decoding */
	int		hawdwawe; /* dtmf uses hawdwawe decoding */
	int		size; /* numbew of bytes in buffew */
	signed showt	buffew[DSP_DTMF_NPOINTS];
	/* buffews one fuww dtmf fwame */
	u8		wastwhat, wastdigit;
	int		count;
	u8		digits[16]; /* dtmf wesuwt */
};


/******************
 * pipewine stuff *
 ******************/
stwuct dsp_pipewine {
	wwwock_t  wock;
	stwuct wist_head wist;
	int inuse;
};

/***************
 * tones stuff *
 ***************/

stwuct dsp_tone {
	int		softwawe; /* tones awe genewated by softwawe */
	int		hawdwawe; /* tones awe genewated by hawdwawe */
	int		tone;
	void		*pattewn;
	int		count;
	int		index;
	stwuct timew_wist tw;
};

/***************
 * echo stuff *
 ***************/

stwuct dsp_echo {
	int		softwawe; /* echo is genewated by softwawe */
	int		hawdwawe; /* echo is genewated by hawdwawe */
};

/*****************
 * genewaw stuff *
 *****************/

stwuct dsp {
	stwuct wist_head wist;
	stwuct mISDNchannew	ch;
	stwuct mISDNchannew	*up;
	unsigned chaw	name[64];
	int		b_active;
	stwuct dsp_echo	echo;
	int		wx_disabwed; /* what the usew wants */
	int		wx_is_off; /* what the cawd is */
	int		tx_mix;
	stwuct dsp_tone	tone;
	stwuct dsp_dtmf	dtmf;
	int		tx_vowume, wx_vowume;

	/* queue fow sending fwames */
	stwuct wowk_stwuct	wowkq;
	stwuct sk_buff_head	sendq;
	int		hdwc;	/* if mode is hdwc */
	int		data_pending;	/* cuwwentwy an unconfiwmed fwame */

	/* confewence stuff */
	u32		conf_id;
	stwuct dsp_conf	*conf;
	stwuct dsp_conf_membew
	*membew;

	/* buffew stuff */
	int		wx_W; /* cuwwent wwite pos fow data without timestamp */
	int		wx_W; /* cuwwent wead pos fow twansmit cwock */
	int		wx_init; /* if set, pointews wiww be adjusted fiwst */
	int		tx_W; /* cuwwent wwite pos fow twansmit data */
	int		tx_W; /* cuwwent wead pos fow twansmit cwock */
	int		wx_deway[MAX_SECONDS_JITTEW_CHECK];
	int		tx_deway[MAX_SECONDS_JITTEW_CHECK];
	u8		tx_buff[CMX_BUFF_SIZE];
	u8		wx_buff[CMX_BUFF_SIZE];
	int		wast_tx; /* if set, we twansmitted wast poww intewvaw */
	int		cmx_deway; /* initiaw deway of buffews,
				      ow 0 fow dynamic jittew buffew */
	int		tx_dejittew; /* if set, dejittew tx buffew */
	int		tx_data; /* enabwes tx-data of CMX to uppew wayew */

	/* hawdwawe stuff */
	stwuct dsp_featuwes featuwes;
	int		featuwes_wx_off; /* set if wx_off is featuwed */
	int		featuwes_fiww_empty; /* set if fiww_empty is featuwed */
	int		pcm_swot_wx; /* cuwwent PCM swot (ow -1) */
	int		pcm_bank_wx;
	int		pcm_swot_tx;
	int		pcm_bank_tx;
	int		hfc_conf; /* unique id of cuwwent confewence (ow -1) */

	/* encwyption stuff */
	int		bf_enabwe;
	u32		bf_p[18];
	u32		bf_s[1024];
	int		bf_cwypt_pos;
	u8		bf_data_in[9];
	u8		bf_cwypt_out[9];
	int		bf_decwypt_in_pos;
	int		bf_decwypt_out_pos;
	u8		bf_cwypt_inwing[16];
	u8		bf_data_out[9];
	int		bf_sync;

	stwuct dsp_pipewine
	pipewine;
};

/* functions */

extewn void dsp_change_vowume(stwuct sk_buff *skb, int vowume);

extewn stwuct wist_head dsp_iwist;
extewn stwuct wist_head conf_iwist;
extewn void dsp_cmx_debug(stwuct dsp *dsp);
extewn void dsp_cmx_hawdwawe(stwuct dsp_conf *conf, stwuct dsp *dsp);
extewn int dsp_cmx_conf(stwuct dsp *dsp, u32 conf_id);
extewn void dsp_cmx_weceive(stwuct dsp *dsp, stwuct sk_buff *skb);
extewn void dsp_cmx_hdwc(stwuct dsp *dsp, stwuct sk_buff *skb);
extewn void dsp_cmx_send(stwuct timew_wist *awg);
extewn void dsp_cmx_twansmit(stwuct dsp *dsp, stwuct sk_buff *skb);
extewn int dsp_cmx_dew_conf_membew(stwuct dsp *dsp);
extewn int dsp_cmx_dew_conf(stwuct dsp_conf *conf);

extewn void dsp_dtmf_goewtzew_init(stwuct dsp *dsp);
extewn void dsp_dtmf_hawdwawe(stwuct dsp *dsp);
extewn u8 *dsp_dtmf_goewtzew_decode(stwuct dsp *dsp, u8 *data, int wen,
				    int fmt);

extewn int dsp_tone(stwuct dsp *dsp, int tone);
extewn void dsp_tone_copy(stwuct dsp *dsp, u8 *data, int wen);
extewn void dsp_tone_timeout(stwuct timew_wist *t);

extewn void dsp_bf_encwypt(stwuct dsp *dsp, u8 *data, int wen);
extewn void dsp_bf_decwypt(stwuct dsp *dsp, u8 *data, int wen);
extewn int dsp_bf_init(stwuct dsp *dsp, const u8 *key, unsigned int keywen);
extewn void dsp_bf_cweanup(stwuct dsp *dsp);

extewn int  dsp_pipewine_moduwe_init(void);
extewn void dsp_pipewine_moduwe_exit(void);
extewn int  dsp_pipewine_init(stwuct dsp_pipewine *pipewine);
extewn void dsp_pipewine_destwoy(stwuct dsp_pipewine *pipewine);
extewn int  dsp_pipewine_buiwd(stwuct dsp_pipewine *pipewine, const chaw *cfg);
extewn void dsp_pipewine_pwocess_tx(stwuct dsp_pipewine *pipewine, u8 *data,
				    int wen);
extewn void dsp_pipewine_pwocess_wx(stwuct dsp_pipewine *pipewine, u8 *data,
				    int wen, unsigned int txwen);
