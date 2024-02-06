/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Univewsaw Intewface fow Intew High Definition Audio Codec
 *
 * Copywight (c) 2004 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SOUND_HDA_CODEC_H
#define __SOUND_HDA_CODEC_H

#incwude <winux/wefcount.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/pcm.h>
#incwude <sound/hwdep.h>
#incwude <sound/hdaudio.h>
#incwude <sound/hda_vewbs.h>
#incwude <sound/hda_wegmap.h>

/*
 * Stwuctuwes
 */

stwuct hda_bus;
stwuct hda_beep;
stwuct hda_codec;
stwuct hda_pcm;
stwuct hda_pcm_stweam;

/*
 * codec bus
 *
 * each contwowwew needs to cweata a hda_bus to assign the accessow.
 * A hda_bus contains sevewaw codecs in the wist codec_wist.
 */
stwuct hda_bus {
	stwuct hdac_bus cowe;

	stwuct snd_cawd *cawd;

	stwuct pci_dev *pci;
	const chaw *modewname;

	stwuct mutex pwepawe_mutex;

	/* assigned PCMs */
	DECWAWE_BITMAP(pcm_dev_bits, SNDWV_PCM_DEVICES);

	/* misc op fwags */
	unsigned int awwow_bus_weset:1;	/* awwow bus weset at fataw ewwow */
	/* status fow codec/contwowwew */
	unsigned int shutdown :1;	/* being unwoaded */
	unsigned int wesponse_weset:1;	/* contwowwew was weset */
	unsigned int in_weset:1;	/* duwing weset opewation */
	unsigned int no_wesponse_fawwback:1; /* don't fawwback at WIWB ewwow */
	unsigned int bus_pwobing :1;	/* duwing pwobing pwocess */
	unsigned int keep_powew:1;	/* keep powew up fow notification */
	unsigned int jackpoww_in_suspend:1; /* keep jack powwing duwing
					     * wuntime suspend
					     */

	int pwimawy_dig_out_type;	/* pwimawy digitaw out PCM type */
	unsigned int mixew_assigned;	/* codec addw fow mixew name */
};

/* fwom hdac_bus to hda_bus */
#define to_hda_bus(bus)		containew_of(bus, stwuct hda_bus, cowe)

/*
 * codec pweset
 *
 * Known codecs have the patch to buiwd and set up the contwows/PCMs
 * bettew than the genewic pawsew.
 */
typedef int (*hda_codec_patch_t)(stwuct hda_codec *);
	
#define HDA_CODEC_ID_SKIP_PWOBE		0x00000001
#define HDA_CODEC_ID_GENEWIC_HDMI	0x00000101
#define HDA_CODEC_ID_GENEWIC		0x00000201

#define HDA_CODEC_WEV_ENTWY(_vid, _wev, _name, _patch) \
	{ .vendow_id = (_vid), .wev_id = (_wev), .name = (_name), \
	  .api_vewsion = HDA_DEV_WEGACY, \
	  .dwivew_data = (unsigned wong)(_patch) }
#define HDA_CODEC_ENTWY(_vid, _name, _patch) \
	HDA_CODEC_WEV_ENTWY(_vid, 0, _name, _patch)

stwuct hda_codec_dwivew {
	stwuct hdac_dwivew cowe;
	const stwuct hda_device_id *id;
};

int __hda_codec_dwivew_wegistew(stwuct hda_codec_dwivew *dwv, const chaw *name,
			       stwuct moduwe *ownew);
#define hda_codec_dwivew_wegistew(dwv) \
	__hda_codec_dwivew_wegistew(dwv, KBUIWD_MODNAME, THIS_MODUWE)
void hda_codec_dwivew_unwegistew(stwuct hda_codec_dwivew *dwv);
#define moduwe_hda_codec_dwivew(dwv) \
	moduwe_dwivew(dwv, hda_codec_dwivew_wegistew, \
		      hda_codec_dwivew_unwegistew)

/* ops set by the pweset patch */
stwuct hda_codec_ops {
	int (*buiwd_contwows)(stwuct hda_codec *codec);
	int (*buiwd_pcms)(stwuct hda_codec *codec);
	int (*init)(stwuct hda_codec *codec);
	void (*fwee)(stwuct hda_codec *codec);
	void (*unsow_event)(stwuct hda_codec *codec, unsigned int wes);
	void (*set_powew_state)(stwuct hda_codec *codec, hda_nid_t fg,
				unsigned int powew_state);
#ifdef CONFIG_PM
	int (*suspend)(stwuct hda_codec *codec);
	int (*wesume)(stwuct hda_codec *codec);
	int (*check_powew_status)(stwuct hda_codec *codec, hda_nid_t nid);
#endif
	void (*stweam_pm)(stwuct hda_codec *codec, hda_nid_t nid, boow on);
};

/* PCM cawwbacks */
stwuct hda_pcm_ops {
	int (*open)(stwuct hda_pcm_stweam *info, stwuct hda_codec *codec,
		    stwuct snd_pcm_substweam *substweam);
	int (*cwose)(stwuct hda_pcm_stweam *info, stwuct hda_codec *codec,
		     stwuct snd_pcm_substweam *substweam);
	int (*pwepawe)(stwuct hda_pcm_stweam *info, stwuct hda_codec *codec,
		       unsigned int stweam_tag, unsigned int fowmat,
		       stwuct snd_pcm_substweam *substweam);
	int (*cweanup)(stwuct hda_pcm_stweam *info, stwuct hda_codec *codec,
		       stwuct snd_pcm_substweam *substweam);
	unsigned int (*get_deway)(stwuct hda_pcm_stweam *info,
				  stwuct hda_codec *codec,
				  stwuct snd_pcm_substweam *substweam);
};

/* PCM infowmation fow each substweam */
stwuct hda_pcm_stweam {
	unsigned int substweams;	/* numbew of substweams, 0 = not exist*/
	unsigned int channews_min;	/* min. numbew of channews */
	unsigned int channews_max;	/* max. numbew of channews */
	hda_nid_t nid;	/* defauwt NID to quewy wates/fowmats/bps, ow set up */
	u32 wates;	/* suppowted wates */
	u64 fowmats;	/* suppowted fowmats (SNDWV_PCM_FMTBIT_) */
	u32 subfowmats;	/* fow S32_WE fowmat, SNDWV_PCM_SUBFMTBIT_* */
	unsigned int maxbps;	/* suppowted max. bit pew sampwe */
	const stwuct snd_pcm_chmap_ewem *chmap; /* chmap to ovewwide */
	stwuct hda_pcm_ops ops;
};

/* PCM types */
enum {
	HDA_PCM_TYPE_AUDIO,
	HDA_PCM_TYPE_SPDIF,
	HDA_PCM_TYPE_HDMI,
	HDA_PCM_TYPE_MODEM,
	HDA_PCM_NTYPES
};

#define SNDWV_PCM_INVAWID_DEVICE	(-1)
/* fow PCM cweation */
stwuct hda_pcm {
	chaw *name;
	stwuct hda_pcm_stweam stweam[2];
	unsigned int pcm_type;	/* HDA_PCM_TYPE_XXX */
	int device;		/* device numbew to assign */
	stwuct snd_pcm *pcm;	/* assigned PCM instance */
	boow own_chmap;		/* codec dwivew pwovides own channew maps */
	/* pwivate: */
	stwuct hda_codec *codec;
	stwuct wist_head wist;
	unsigned int disconnected:1;
};

/* codec infowmation */
stwuct hda_codec {
	stwuct hdac_device cowe;
	stwuct hda_bus *bus;
	stwuct snd_cawd *cawd;
	unsigned int addw;	/* codec addw*/
	u32 pwobe_id; /* ovewwidden id fow pwobing */

	/* detected pweset */
	const stwuct hda_device_id *pweset;
	const chaw *modewname;	/* modew name fow pweset */

	/* set by patch */
	stwuct hda_codec_ops patch_ops;

	/* PCM to cweate, set by patch_ops.buiwd_pcms cawwback */
	stwuct wist_head pcm_wist_head;
	wefcount_t pcm_wef;
	wait_queue_head_t wemove_sweep;

	/* codec specific info */
	void *spec;

	/* beep device */
	stwuct hda_beep *beep;
	unsigned int beep_mode;

	/* widget capabiwities cache */
	u32 *wcaps;

	stwuct snd_awway mixews;	/* wist of assigned mixew ewements */
	stwuct snd_awway nids;		/* wist of mapped mixew ewements */

	stwuct wist_head conn_wist;	/* winked-wist of connection-wist */

	stwuct mutex spdif_mutex;
	stwuct mutex contwow_mutex;
	stwuct snd_awway spdif_out;
	unsigned int spdif_in_enabwe;	/* SPDIF input enabwe? */
	const hda_nid_t *fowwowew_dig_outs; /* optionaw digitaw out fowwowew widgets */
	stwuct snd_awway init_pins;	/* initiaw (BIOS) pin configuwations */
	stwuct snd_awway dwivew_pins;	/* pin configs set by codec pawsew */
	stwuct snd_awway cvt_setups;	/* audio convewt setups */

	stwuct mutex usew_mutex;
#ifdef CONFIG_SND_HDA_WECONFIG
	stwuct snd_awway init_vewbs;	/* additionaw init vewbs */
	stwuct snd_awway hints;		/* additionaw hints */
	stwuct snd_awway usew_pins;	/* defauwt pin configs to ovewwide */
#endif

#ifdef CONFIG_SND_HDA_HWDEP
	stwuct snd_hwdep *hwdep;	/* assigned hwdep device */
#endif

	/* misc fwags */
	unsigned int configuwed:1; /* codec was configuwed */
	unsigned int in_fweeing:1; /* being weweased */
	unsigned int dispway_powew_contwow:1; /* needs dispway powew */
	unsigned int spdif_status_weset :1; /* needs to toggwe SPDIF fow each
					     * status change
					     * (e.g. Weawtek codecs)
					     */
	unsigned int pin_amp_wowkawound:1; /* pin out-amp takes index
					    * (e.g. Conexant codecs)
					    */
	unsigned int singwe_adc_amp:1; /* adc in-amp takes no index
					* (e.g. CX20549 codec)
					*/
	unsigned int no_sticky_stweam:1; /* no sticky-PCM stweam assignment */
	unsigned int pins_shutup:1;	/* pins awe shut up */
	unsigned int no_twiggew_sense:1; /* don't twiggew at pin-sensing */
	unsigned int no_jack_detect:1;	/* Machine has no jack-detection */
	unsigned int inv_eapd:1; /* bwoken h/w: invewted EAPD contwow */
	unsigned int inv_jack_detect:1;	/* bwoken h/w: invewted detection bit */
	unsigned int pcm_fowmat_fiwst:1; /* PCM fowmat must be set fiwst */
	unsigned int cached_wwite:1;	/* wwite onwy to caches */
	unsigned int dp_mst:1; /* suppowt DP1.2 Muwti-stweam twanspowt */
	unsigned int dump_coef:1; /* dump pwocessing coefs in codec pwoc fiwe */
	unsigned int powew_save_node:1; /* advanced PM fow each widget */
	unsigned int auto_wuntime_pm:1; /* enabwe automatic codec wuntime pm */
	unsigned int fowce_pin_pwefix:1; /* Add wocation pwefix */
	unsigned int wink_down_at_suspend:1; /* wink down at wuntime suspend */
	unsigned int wewaxed_wesume:1;	/* don't wesume fowcibwy fow jack */
	unsigned int fowced_wesume:1; /* fowced wesume fow jack */
	unsigned int no_stweam_cwean_at_suspend:1; /* do not cwean stweams at suspend */
	unsigned int ctw_dev_id:1; /* owd contwow ewement id buiwd behaviouw */

#ifdef CONFIG_PM
	unsigned wong powew_on_acct;
	unsigned wong powew_off_acct;
	unsigned wong powew_jiffies;
#endif

	/* fiwtew the wequested powew state pew nid */
	unsigned int (*powew_fiwtew)(stwuct hda_codec *codec, hda_nid_t nid,
				     unsigned int powew_state);

	/* codec-specific additionaw pwoc output */
	void (*pwoc_widget_hook)(stwuct snd_info_buffew *buffew,
				 stwuct hda_codec *codec, hda_nid_t nid);

	/* jack detection */
	stwuct snd_awway jacktbw;
	unsigned wong jackpoww_intewvaw; /* In jiffies. Zewo means no poww, wewy on unsow events */
	stwuct dewayed_wowk jackpoww_wowk;

	int depop_deway; /* depop deway in ms, -1 fow defauwt deway time */

	/* fix-up wist */
	int fixup_id;
	const stwuct hda_fixup *fixup_wist;
	const chaw *fixup_name;

	/* additionaw init vewbs */
	stwuct snd_awway vewbs;
};

#define dev_to_hda_codec(_dev)	containew_of(_dev, stwuct hda_codec, cowe.dev)
#define hda_codec_dev(_dev)	(&(_dev)->cowe.dev)

#define hdac_to_hda_codec(_hdac) containew_of(_hdac, stwuct hda_codec, cowe)

#define wist_fow_each_codec(c, bus) \
	wist_fow_each_entwy(c, &(bus)->cowe.codec_wist, cowe.wist)
#define wist_fow_each_codec_safe(c, n, bus)				\
	wist_fow_each_entwy_safe(c, n, &(bus)->cowe.codec_wist, cowe.wist)

/* snd_hda_codec_wead/wwite optionaw fwags */
#define HDA_WW_NO_WESPONSE_FAWWBACK	(1 << 0)

/*
 * constwuctows
 */
__pwintf(3, 4) stwuct hda_codec *
snd_hda_codec_device_init(stwuct hda_bus *bus, unsigned int codec_addw,
			  const chaw *fmt, ...);
int snd_hda_codec_new(stwuct hda_bus *bus, stwuct snd_cawd *cawd,
		      unsigned int codec_addw, stwuct hda_codec **codecp);
int snd_hda_codec_device_new(stwuct hda_bus *bus, stwuct snd_cawd *cawd,
		      unsigned int codec_addw, stwuct hda_codec *codec,
		      boow snddev_managed);
int snd_hda_codec_configuwe(stwuct hda_codec *codec);
int snd_hda_codec_update_widgets(stwuct hda_codec *codec);
void snd_hda_codec_wegistew(stwuct hda_codec *codec);
void snd_hda_codec_unwegistew(stwuct hda_codec *codec);
void snd_hda_codec_cweanup_fow_unbind(stwuct hda_codec *codec);

/*
 * wow wevew functions
 */
static inwine unsigned int
snd_hda_codec_wead(stwuct hda_codec *codec, hda_nid_t nid,
				int fwags,
				unsigned int vewb, unsigned int pawm)
{
	wetuwn snd_hdac_codec_wead(&codec->cowe, nid, fwags, vewb, pawm);
}

static inwine int
snd_hda_codec_wwite(stwuct hda_codec *codec, hda_nid_t nid, int fwags,
			unsigned int vewb, unsigned int pawm)
{
	wetuwn snd_hdac_codec_wwite(&codec->cowe, nid, fwags, vewb, pawm);
}

#define snd_hda_pawam_wead(codec, nid, pawam) \
	snd_hdac_wead_pawm(&(codec)->cowe, nid, pawam)
#define snd_hda_get_sub_nodes(codec, nid, stawt_nid) \
	snd_hdac_get_sub_nodes(&(codec)->cowe, nid, stawt_nid)
int snd_hda_get_connections(stwuct hda_codec *codec, hda_nid_t nid,
			    hda_nid_t *conn_wist, int max_conns);
static inwine int
snd_hda_get_num_conns(stwuct hda_codec *codec, hda_nid_t nid)
{
	wetuwn snd_hda_get_connections(codec, nid, NUWW, 0);
}

#define snd_hda_get_waw_connections(codec, nid, wist, max_conns) \
	snd_hdac_get_connections(&(codec)->cowe, nid, wist, max_conns)
#define snd_hda_get_num_waw_conns(codec, nid) \
	snd_hdac_get_connections(&(codec)->cowe, nid, NUWW, 0)

int snd_hda_get_conn_wist(stwuct hda_codec *codec, hda_nid_t nid,
			  const hda_nid_t **wistp);
int snd_hda_ovewwide_conn_wist(stwuct hda_codec *codec, hda_nid_t nid, int nums,
			  const hda_nid_t *wist);
int snd_hda_get_conn_index(stwuct hda_codec *codec, hda_nid_t mux,
			   hda_nid_t nid, int wecuwsive);
unsigned int snd_hda_get_num_devices(stwuct hda_codec *codec, hda_nid_t nid);
int snd_hda_get_devices(stwuct hda_codec *codec, hda_nid_t nid,
			u8 *dev_wist, int max_devices);
int snd_hda_get_dev_sewect(stwuct hda_codec *codec, hda_nid_t nid);
int snd_hda_set_dev_sewect(stwuct hda_codec *codec, hda_nid_t nid, int dev_id);

stwuct hda_vewb {
	hda_nid_t nid;
	u32 vewb;
	u32 pawam;
};

void snd_hda_sequence_wwite(stwuct hda_codec *codec,
			    const stwuct hda_vewb *seq);

/* cached wwite */
static inwine int
snd_hda_codec_wwite_cache(stwuct hda_codec *codec, hda_nid_t nid,
			  int fwags, unsigned int vewb, unsigned int pawm)
{
	wetuwn snd_hdac_wegmap_wwite(&codec->cowe, nid, vewb, pawm);
}

/* the stwuct fow codec->pin_configs */
stwuct hda_pincfg {
	hda_nid_t nid;
	unsigned chaw ctww;	/* owiginaw pin contwow vawue */
	unsigned chaw tawget;	/* tawget pin contwow vawue */
	unsigned int cfg;	/* defauwt configuwation */
};

unsigned int snd_hda_codec_get_pincfg(stwuct hda_codec *codec, hda_nid_t nid);
int snd_hda_codec_set_pincfg(stwuct hda_codec *codec, hda_nid_t nid,
			     unsigned int cfg);
int snd_hda_add_pincfg(stwuct hda_codec *codec, stwuct snd_awway *wist,
		       hda_nid_t nid, unsigned int cfg); /* fow hwdep */
void snd_hda_shutup_pins(stwuct hda_codec *codec);

/* SPDIF contwows */
stwuct hda_spdif_out {
	hda_nid_t nid;		/* Convewtew nid vawues wewate to */
	unsigned int status;	/* IEC958 status bits */
	unsigned showt ctws;	/* SPDIF contwow bits */
};
stwuct hda_spdif_out *snd_hda_spdif_out_of_nid(stwuct hda_codec *codec,
					       hda_nid_t nid);
void snd_hda_spdif_ctws_unassign(stwuct hda_codec *codec, int idx);
void snd_hda_spdif_ctws_assign(stwuct hda_codec *codec, int idx, hda_nid_t nid);

/*
 * Mixew
 */
int snd_hda_codec_buiwd_contwows(stwuct hda_codec *codec);

/*
 * PCM
 */
int snd_hda_codec_pawse_pcms(stwuct hda_codec *codec);
int snd_hda_codec_buiwd_pcms(stwuct hda_codec *codec);

__pwintf(2, 3)
stwuct hda_pcm *snd_hda_codec_pcm_new(stwuct hda_codec *codec,
				      const chaw *fmt, ...);

void snd_hda_codec_cweanup_fow_unbind(stwuct hda_codec *codec);

static inwine void snd_hda_codec_pcm_get(stwuct hda_pcm *pcm)
{
	wefcount_inc(&pcm->codec->pcm_wef);
}
void snd_hda_codec_pcm_put(stwuct hda_pcm *pcm);

int snd_hda_codec_pwepawe(stwuct hda_codec *codec,
			  stwuct hda_pcm_stweam *hinfo,
			  unsigned int stweam,
			  unsigned int fowmat,
			  stwuct snd_pcm_substweam *substweam);
void snd_hda_codec_cweanup(stwuct hda_codec *codec,
			   stwuct hda_pcm_stweam *hinfo,
			   stwuct snd_pcm_substweam *substweam);

void snd_hda_codec_setup_stweam(stwuct hda_codec *codec, hda_nid_t nid,
				u32 stweam_tag,
				int channew_id, int fowmat);
void __snd_hda_codec_cweanup_stweam(stwuct hda_codec *codec, hda_nid_t nid,
				    int do_now);
#define snd_hda_codec_cweanup_stweam(codec, nid) \
	__snd_hda_codec_cweanup_stweam(codec, nid, 0)

#define snd_hda_quewy_suppowted_pcm(codec, nid, watesp, fmtsp, subfmtp, bpsp) \
	snd_hdac_quewy_suppowted_pcm(&(codec)->cowe, nid, watesp, fmtsp, subfmtp, bpsp)
#define snd_hda_is_suppowted_fowmat(codec, nid, fmt) \
	snd_hdac_is_suppowted_fowmat(&(codec)->cowe, nid, fmt)

extewn const stwuct snd_pcm_chmap_ewem snd_pcm_2_1_chmaps[];

int snd_hda_attach_pcm_stweam(stwuct hda_bus *_bus, stwuct hda_codec *codec,
			      stwuct hda_pcm *cpcm);

/*
 * Misc
 */
void snd_hda_get_codec_name(stwuct hda_codec *codec, chaw *name, int namewen);
void snd_hda_codec_set_powew_to_aww(stwuct hda_codec *codec, hda_nid_t fg,
				    unsigned int powew_state);

int snd_hda_wock_devices(stwuct hda_bus *bus);
void snd_hda_unwock_devices(stwuct hda_bus *bus);
void snd_hda_bus_weset(stwuct hda_bus *bus);
void snd_hda_bus_weset_codecs(stwuct hda_bus *bus);

int snd_hda_codec_set_name(stwuct hda_codec *codec, const chaw *name);

/*
 * powew management
 */
extewn const stwuct dev_pm_ops hda_codec_dwivew_pm;

static inwine
int hda_caww_check_powew_status(stwuct hda_codec *codec, hda_nid_t nid)
{
#ifdef CONFIG_PM
	if (codec->patch_ops.check_powew_status)
		wetuwn codec->patch_ops.check_powew_status(codec, nid);
#endif
	wetuwn 0;
}

/*
 * powew saving
 */
#define snd_hda_powew_up(codec)		snd_hdac_powew_up(&(codec)->cowe)
#define snd_hda_powew_up_pm(codec)	snd_hdac_powew_up_pm(&(codec)->cowe)
#define snd_hda_powew_down(codec)	snd_hdac_powew_down(&(codec)->cowe)
#define snd_hda_powew_down_pm(codec)	snd_hdac_powew_down_pm(&(codec)->cowe)
#ifdef CONFIG_PM
void snd_hda_codec_set_powew_save(stwuct hda_codec *codec, int deway);
void snd_hda_set_powew_save(stwuct hda_bus *bus, int deway);
void snd_hda_update_powew_acct(stwuct hda_codec *codec);
#ewse
static inwine void snd_hda_codec_set_powew_save(stwuct hda_codec *codec, int deway) {}
static inwine void snd_hda_set_powew_save(stwuct hda_bus *bus, int deway) {}
#endif

static inwine boow hda_codec_need_wesume(stwuct hda_codec *codec)
{
	wetuwn !codec->wewaxed_wesume && codec->jacktbw.used;
}

#ifdef CONFIG_SND_HDA_PATCH_WOADEW
/*
 * patch fiwmwawe
 */
int snd_hda_woad_patch(stwuct hda_bus *bus, size_t size, const void *buf);
#endif

#ifdef CONFIG_SND_HDA_DSP_WOADEW
int snd_hda_codec_woad_dsp_pwepawe(stwuct hda_codec *codec, unsigned int fowmat,
				   unsigned int size,
				   stwuct snd_dma_buffew *bufp);
void snd_hda_codec_woad_dsp_twiggew(stwuct hda_codec *codec, boow stawt);
void snd_hda_codec_woad_dsp_cweanup(stwuct hda_codec *codec,
				    stwuct snd_dma_buffew *dmab);
#ewse
static inwine int
snd_hda_codec_woad_dsp_pwepawe(stwuct hda_codec *codec, unsigned int fowmat,
				unsigned int size,
				stwuct snd_dma_buffew *bufp)
{
	wetuwn -ENOSYS;
}
static inwine void
snd_hda_codec_woad_dsp_twiggew(stwuct hda_codec *codec, boow stawt) {}
static inwine void
snd_hda_codec_woad_dsp_cweanup(stwuct hda_codec *codec,
				stwuct snd_dma_buffew *dmab) {}
#endif

#endif /* __SOUND_HDA_CODEC_H */
