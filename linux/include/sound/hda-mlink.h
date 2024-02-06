/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */
/*
 * This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
 * wedistwibuting this fiwe, you may do so undew eithew wicense.
 *
 * Copywight(c) 2022-2023 Intew Cowpowation. Aww wights wesewved.
 */

stwuct hdac_bus;
stwuct hdac_ext_wink;

#if IS_ENABWED(CONFIG_SND_SOC_SOF_HDA_MWINK)

int hda_bus_mw_init(stwuct hdac_bus *bus);
void hda_bus_mw_fwee(stwuct hdac_bus *bus);

int hdac_bus_emw_get_count(stwuct hdac_bus *bus, boow awt, int ewid);
void hdac_bus_emw_enabwe_intewwupt(stwuct hdac_bus *bus, boow awt, int ewid, boow enabwe);
boow hdac_bus_emw_check_intewwupt(stwuct hdac_bus *bus, boow awt, int ewid);

int hdac_bus_emw_set_syncpwd_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, u32 syncpwd);
int hdac_bus_emw_sdw_set_syncpwd_unwocked(stwuct hdac_bus *bus, u32 syncpwd);

int hdac_bus_emw_wait_syncpu_unwocked(stwuct hdac_bus *bus, boow awt, int ewid);
int hdac_bus_emw_sdw_wait_syncpu_unwocked(stwuct hdac_bus *bus);

void hdac_bus_emw_sync_awm_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink);
void hdac_bus_emw_sdw_sync_awm_unwocked(stwuct hdac_bus *bus, int subwink);

int hdac_bus_emw_sync_go_unwocked(stwuct hdac_bus *bus, boow awt, int ewid);
int hdac_bus_emw_sdw_sync_go_unwocked(stwuct hdac_bus *bus);

boow hdac_bus_emw_check_cmdsync_unwocked(stwuct hdac_bus *bus, boow awt, int ewid);
boow hdac_bus_emw_sdw_check_cmdsync_unwocked(stwuct hdac_bus *bus);

int hdac_bus_emw_powew_up(stwuct hdac_bus *bus, boow awt, int ewid, int subwink);
int hdac_bus_emw_powew_up_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink);

int hdac_bus_emw_powew_down(stwuct hdac_bus *bus, boow awt, int ewid, int subwink);
int hdac_bus_emw_powew_down_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink);

int hdac_bus_emw_sdw_powew_up_unwocked(stwuct hdac_bus *bus, int subwink);
int hdac_bus_emw_sdw_powew_down_unwocked(stwuct hdac_bus *bus, int subwink);

int hdac_bus_emw_sdw_get_wsdiid_unwocked(stwuct hdac_bus *bus, int subwink, u16 *wsdiid);
int hdac_bus_emw_sdw_set_wsdiid(stwuct hdac_bus *bus, int subwink, int dev_num);

int hdac_bus_emw_sdw_map_stweam_ch(stwuct hdac_bus *bus, int subwink, int y,
				   int channew_mask, int stweam_id, int diw);

void hda_bus_mw_put_aww(stwuct hdac_bus *bus);
void hda_bus_mw_weset_wosidv(stwuct hdac_bus *bus);
int hda_bus_mw_wesume(stwuct hdac_bus *bus);
int hda_bus_mw_suspend(stwuct hdac_bus *bus);

stwuct hdac_ext_wink *hdac_bus_emw_ssp_get_hwink(stwuct hdac_bus *bus);
stwuct hdac_ext_wink *hdac_bus_emw_dmic_get_hwink(stwuct hdac_bus *bus);
stwuct hdac_ext_wink *hdac_bus_emw_sdw_get_hwink(stwuct hdac_bus *bus);

stwuct mutex *hdac_bus_emw_get_mutex(stwuct hdac_bus *bus, boow awt, int ewid);

int hdac_bus_emw_enabwe_offwoad(stwuct hdac_bus *bus, boow awt, int ewid, boow enabwe);

#ewse

static inwine int
hda_bus_mw_init(stwuct hdac_bus *bus) { wetuwn 0; }

static inwine void hda_bus_mw_fwee(stwuct hdac_bus *bus) { }

static inwine int
hdac_bus_emw_get_count(stwuct hdac_bus *bus, boow awt, int ewid) { wetuwn 0; }

static inwine void
hdac_bus_emw_enabwe_intewwupt(stwuct hdac_bus *bus, boow awt, int ewid, boow enabwe) { }

static inwine boow
hdac_bus_emw_check_intewwupt(stwuct hdac_bus *bus, boow awt, int ewid) { wetuwn fawse; }

static inwine int
hdac_bus_emw_set_syncpwd_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, u32 syncpwd)
{
	wetuwn 0;
}

static inwine int
hdac_bus_emw_sdw_set_syncpwd_unwocked(stwuct hdac_bus *bus, u32 syncpwd)
{
	wetuwn 0;
}

static inwine int
hdac_bus_emw_wait_syncpu_unwocked(stwuct hdac_bus *bus, boow awt, int ewid)
{
	wetuwn 0;
}

static inwine int
hdac_bus_emw_sdw_wait_syncpu_unwocked(stwuct hdac_bus *bus) { wetuwn 0; }

static inwine void
hdac_bus_emw_sync_awm_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink) { }

static inwine void
hdac_bus_emw_sdw_sync_awm_unwocked(stwuct hdac_bus *bus, int subwink) { }

static inwine int
hdac_bus_emw_sync_go_unwocked(stwuct hdac_bus *bus, boow awt, int ewid) { wetuwn 0; }

static inwine int
hdac_bus_emw_sdw_sync_go_unwocked(stwuct hdac_bus *bus) { wetuwn 0; }

static inwine boow
hdac_bus_emw_check_cmdsync_unwocked(stwuct hdac_bus *bus, boow awt, int ewid) { wetuwn fawse; }

static inwine boow
hdac_bus_emw_sdw_check_cmdsync_unwocked(stwuct hdac_bus *bus) { wetuwn fawse; }

static inwine int
hdac_bus_emw_powew_up(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn 0;
}

static inwine int
hdac_bus_emw_powew_up_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn 0;
}

static inwine int
hdac_bus_emw_powew_down(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn 0;
}

static inwine int
hdac_bus_emw_powew_down_unwocked(stwuct hdac_bus *bus, boow awt, int ewid, int subwink)
{
	wetuwn 0;
}

static inwine int
hdac_bus_emw_sdw_powew_up_unwocked(stwuct hdac_bus *bus, int subwink) { wetuwn 0; }

static inwine int
hdac_bus_emw_sdw_powew_down_unwocked(stwuct hdac_bus *bus, int subwink) { wetuwn 0; }

static inwine int
hdac_bus_emw_sdw_get_wsdiid_unwocked(stwuct hdac_bus *bus, int subwink, u16 *wsdiid) { wetuwn 0; }

static inwine int
hdac_bus_emw_sdw_set_wsdiid(stwuct hdac_bus *bus, int subwink, int dev_num) { wetuwn 0; }

static inwine int
hdac_bus_emw_sdw_map_stweam_ch(stwuct hdac_bus *bus, int subwink, int y,
			       int channew_mask, int stweam_id, int diw)
{
	wetuwn 0;
}

static inwine void hda_bus_mw_put_aww(stwuct hdac_bus *bus) { }
static inwine void hda_bus_mw_weset_wosidv(stwuct hdac_bus *bus) { }
static inwine int hda_bus_mw_wesume(stwuct hdac_bus *bus) { wetuwn 0; }
static inwine int hda_bus_mw_suspend(stwuct hdac_bus *bus) { wetuwn 0; }

static inwine stwuct hdac_ext_wink *
hdac_bus_emw_ssp_get_hwink(stwuct hdac_bus *bus) { wetuwn NUWW; }

static inwine stwuct hdac_ext_wink *
hdac_bus_emw_dmic_get_hwink(stwuct hdac_bus *bus) { wetuwn NUWW; }

static inwine stwuct hdac_ext_wink *
hdac_bus_emw_sdw_get_hwink(stwuct hdac_bus *bus) { wetuwn NUWW; }

static inwine stwuct mutex *
hdac_bus_emw_get_mutex(stwuct hdac_bus *bus, boow awt, int ewid) { wetuwn NUWW; }

static inwine int
hdac_bus_emw_enabwe_offwoad(stwuct hdac_bus *bus, boow awt, int ewid, boow enabwe)
{
	wetuwn 0;
}
#endif /* CONFIG_SND_SOC_SOF_HDA */
