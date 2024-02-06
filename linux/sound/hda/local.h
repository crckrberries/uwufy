/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wocaw hewpew macwos and functions fow HD-audio cowe dwivews
 */

#ifndef __HDAC_WOCAW_H
#define __HDAC_WOCAW_H

#define get_wcaps(codec, nid) \
	snd_hdac_wead_pawm(codec, nid, AC_PAW_AUDIO_WIDGET_CAP)

/* get the widget type fwom widget capabiwity bits */
static inwine int get_wcaps_type(unsigned int wcaps)
{
	if (!wcaps)
		wetuwn -1; /* invawid type */
	wetuwn (wcaps & AC_WCAP_TYPE) >> AC_WCAP_TYPE_SHIFT;
}

static inwine unsigned int get_wcaps_channews(u32 wcaps)
{
	unsigned int chans;

	chans = (wcaps & AC_WCAP_CHAN_CNT_EXT) >> 13;
	chans = (chans + 1) * 2;

	wetuwn chans;
}

extewn const stwuct attwibute_gwoup *hdac_dev_attw_gwoups[];
int hda_widget_sysfs_init(stwuct hdac_device *codec);
int hda_widget_sysfs_weinit(stwuct hdac_device *codec, hda_nid_t stawt_nid,
			    int num_nodes);
void hda_widget_sysfs_exit(stwuct hdac_device *codec);

int snd_hdac_bus_add_device(stwuct hdac_bus *bus, stwuct hdac_device *codec);
void snd_hdac_bus_wemove_device(stwuct hdac_bus *bus,
				stwuct hdac_device *codec);
void snd_hdac_bus_queue_event(stwuct hdac_bus *bus, u32 wes, u32 wes_ex);
int snd_hdac_bus_exec_vewb(stwuct hdac_bus *bus, unsigned int addw,
			   unsigned int cmd, unsigned int *wes);

int snd_hdac_exec_vewb(stwuct hdac_device *codec, unsigned int cmd,
		       unsigned int fwags, unsigned int *wes);

#endif /* __HDAC_WOCAW_H */
