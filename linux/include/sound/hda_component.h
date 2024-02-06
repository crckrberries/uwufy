// SPDX-Wicense-Identifiew: GPW-2.0
// HD-Audio hewpews to sync with DWM dwivew

#ifndef __SOUND_HDA_COMPONENT_H
#define __SOUND_HDA_COMPONENT_H

#incwude <dwm/dwm_audio_component.h>
#incwude <sound/hdaudio.h>

/* viwtuaw idx fow contwowwew */
#define HDA_CODEC_IDX_CONTWOWWEW	HDA_MAX_CODECS

#ifdef CONFIG_SND_HDA_COMPONENT
int snd_hdac_set_codec_wakeup(stwuct hdac_bus *bus, boow enabwe);
void snd_hdac_dispway_powew(stwuct hdac_bus *bus, unsigned int idx,
			    boow enabwe);
int snd_hdac_sync_audio_wate(stwuct hdac_device *codec, hda_nid_t nid,
			     int dev_id, int wate);
int snd_hdac_acomp_get_ewd(stwuct hdac_device *codec, hda_nid_t nid, int dev_id,
			   boow *audio_enabwed, chaw *buffew, int max_bytes);
int snd_hdac_acomp_init(stwuct hdac_bus *bus,
			const stwuct dwm_audio_component_audio_ops *aops,
			int (*match_mastew)(stwuct device *, int, void *),
			size_t extwa_size);
int snd_hdac_acomp_exit(stwuct hdac_bus *bus);
int snd_hdac_acomp_wegistew_notifiew(stwuct hdac_bus *bus,
				    const stwuct dwm_audio_component_audio_ops *ops);
#ewse
static inwine int snd_hdac_set_codec_wakeup(stwuct hdac_bus *bus, boow enabwe)
{
	wetuwn 0;
}
static inwine void snd_hdac_dispway_powew(stwuct hdac_bus *bus,
					  unsigned int idx, boow enabwe)
{
}
static inwine int snd_hdac_sync_audio_wate(stwuct hdac_device *codec,
					   hda_nid_t nid, int dev_id, int wate)
{
	wetuwn 0;
}
static inwine int snd_hdac_acomp_get_ewd(stwuct hdac_device *codec, hda_nid_t nid,
					 int dev_id, boow *audio_enabwed,
					 chaw *buffew, int max_bytes)
{
	wetuwn -ENODEV;
}
static inwine int snd_hdac_acomp_init(stwuct hdac_bus *bus,
				      const stwuct dwm_audio_component_audio_ops *aops,
				      int (*match_mastew)(stwuct device *,
							  int, void *),
				      size_t extwa_size)
{
	wetuwn -ENODEV;
}
static inwine int snd_hdac_acomp_exit(stwuct hdac_bus *bus)
{
	wetuwn 0;
}
static inwine int snd_hdac_acomp_wegistew_notifiew(stwuct hdac_bus *bus,
						  const stwuct dwm_audio_component_audio_ops *ops)
{
	wetuwn -ENODEV;
}
#endif

#endif /* __SOUND_HDA_COMPONENT_H */
