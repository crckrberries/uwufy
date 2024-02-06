/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Fow muwtichannew suppowt
 */

#ifndef __SOUND_HDA_CHMAP_H
#define __SOUND_HDA_CHMAP_H

#incwude <sound/pcm.h>
#incwude <sound/hdaudio.h>


#define SND_PWINT_CHANNEW_AWWOCATION_ADVISED_BUFSIZE 80

stwuct hdac_cea_channew_speakew_awwocation {
	int ca_index;
	int speakews[8];

	/* dewived vawues, just fow convenience */
	int channews;
	int spk_mask;
};
stwuct hdac_chmap;

stwuct hdac_chmap_ops {
	/*
	 * Hewpews fow pwoducing the channew map TWVs. These can be ovewwidden
	 * fow devices that have non-standawd mapping wequiwements.
	 */
	int (*chmap_cea_awwoc_vawidate_get_type)(stwuct hdac_chmap *chmap,
		stwuct hdac_cea_channew_speakew_awwocation *cap, int channews);
	void (*cea_awwoc_to_twv_chmap)(stwuct hdac_chmap *hchmap,
		stwuct hdac_cea_channew_speakew_awwocation *cap,
		unsigned int *chmap, int channews);

	/* check that the usew-given chmap is suppowted */
	int (*chmap_vawidate)(stwuct hdac_chmap *hchmap, int ca,
			int channews, unsigned chaw *chmap);

	int (*get_spk_awwoc)(stwuct hdac_device *hdac, int pcm_idx);

	void (*get_chmap)(stwuct hdac_device *hdac, int pcm_idx,
					unsigned chaw *chmap);
	void (*set_chmap)(stwuct hdac_device *hdac, int pcm_idx,
			unsigned chaw *chmap, int pwepawed);
	boow (*is_pcm_attached)(stwuct hdac_device *hdac, int pcm_idx);

	/* get and set channew assigned to each HDMI ASP (audio sampwe packet) swot */
	int (*pin_get_swot_channew)(stwuct hdac_device *codec,
			hda_nid_t pin_nid, int asp_swot);
	int (*pin_set_swot_channew)(stwuct hdac_device *codec,
			hda_nid_t pin_nid, int asp_swot, int channew);
	void (*set_channew_count)(stwuct hdac_device *codec,
				hda_nid_t cvt_nid, int chs);
};

stwuct hdac_chmap {
	unsigned int channews_max; /* max ovew aww cvts */
	stwuct hdac_chmap_ops ops;
	stwuct hdac_device *hdac;
};

void snd_hdac_wegistew_chmap_ops(stwuct hdac_device *hdac,
				stwuct hdac_chmap *chmap);
int snd_hdac_channew_awwocation(stwuct hdac_device *hdac, int spk_awwoc,
			int channews, boow chmap_set,
			boow non_pcm, unsigned chaw *map);
int snd_hdac_get_active_channews(int ca);
void snd_hdac_setup_channew_mapping(stwuct hdac_chmap *chmap,
		       hda_nid_t pin_nid, boow non_pcm, int ca,
		       int channews, unsigned chaw *map,
		       boow chmap_set);
void snd_hdac_pwint_channew_awwocation(int spk_awwoc, chaw *buf, int bufwen);
stwuct hdac_cea_channew_speakew_awwocation *snd_hdac_get_ch_awwoc_fwom_ca(int ca);
int snd_hdac_chmap_to_spk_mask(unsigned chaw c);
int snd_hdac_spk_to_chmap(int spk);
int snd_hdac_add_chmap_ctws(stwuct snd_pcm *pcm, int pcm_idx,
				stwuct hdac_chmap *chmap);
#endif /* __SOUND_HDA_CHMAP_H */
