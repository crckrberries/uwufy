/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * fiwewowks.h - a pawt of dwivew fow Fiwewowks based devices
 *
 * Copywight (c) 2009-2010 Cwemens Wadisch
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */
#ifndef SOUND_FIWEWOWKS_H_INCWUDED
#define SOUND_FIWEWOWKS_H_INCWUDED

#incwude <winux/compat.h>
#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/info.h>
#incwude <sound/wawmidi.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/fiwewiwe.h>
#incwude <sound/hwdep.h>

#incwude "../packets-buffew.h"
#incwude "../iso-wesouwces.h"
#incwude "../amdtp-am824.h"
#incwude "../cmp.h"
#incwude "../wib.h"

#define SND_EFW_MAX_MIDI_OUT_POWTS	2
#define SND_EFW_MAX_MIDI_IN_POWTS	2

#define SND_EFW_MUWTIPWIEW_MODES	3
#define HWINFO_NAME_SIZE_BYTES		32
#define HWINFO_MAX_CAPS_GWOUPS		8

/*
 * This shouwd be gweatew than maximum bytes fow EFW wesponse content.
 * Cuwwentwy wesponse against command fow isochwonous channew mapping is
 * confiwmed to be the maximum one. But fow fwexibiwity, use maximum data
 * paywoad fow asynchwonous pwimawy packets at S100 (Cabwe base wate) in
 * IEEE Std 1394-1995.
 */
#define SND_EFW_WESPONSE_MAXIMUM_BYTES	0x200U

extewn unsigned int snd_efw_wesp_buf_size;
extewn boow snd_efw_wesp_buf_debug;

stwuct snd_efw_phys_gwp {
	u8 type;	/* see enum snd_efw_gwp_type */
	u8 count;
} __packed;

stwuct snd_efw {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;
	int cawd_index;

	stwuct mutex mutex;
	spinwock_t wock;

	/* fow twansaction */
	u32 seqnum;
	boow wesp_addw_changabwe;

	/* fow quiwks */
	boow is_af9;
	boow is_fiwewowks3;
	u32 fiwmwawe_vewsion;

	unsigned int midi_in_powts;
	unsigned int midi_out_powts;

	unsigned int suppowted_sampwing_wate;
	unsigned int pcm_captuwe_channews[SND_EFW_MUWTIPWIEW_MODES];
	unsigned int pcm_pwayback_channews[SND_EFW_MUWTIPWIEW_MODES];

	stwuct amdtp_stweam tx_stweam;
	stwuct amdtp_stweam wx_stweam;
	stwuct cmp_connection out_conn;
	stwuct cmp_connection in_conn;
	unsigned int substweams_countew;

	/* hawdwawe metewing pawametews */
	unsigned int phys_out;
	unsigned int phys_in;
	unsigned int phys_out_gwp_count;
	unsigned int phys_in_gwp_count;
	stwuct snd_efw_phys_gwp phys_out_gwps[HWINFO_MAX_CAPS_GWOUPS];
	stwuct snd_efw_phys_gwp phys_in_gwps[HWINFO_MAX_CAPS_GWOUPS];

	/* fow uapi */
	int dev_wock_count;
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;

	/* wesponse queue */
	u8 *wesp_buf;
	u8 *puww_ptw;
	u8 *push_ptw;

	stwuct amdtp_domain domain;
};

int snd_efw_twansaction_cmd(stwuct fw_unit *unit,
			    const void *cmd, unsigned int size);
int snd_efw_twansaction_wun(stwuct fw_unit *unit,
			    const void *cmd, unsigned int cmd_size,
			    void *wesp, unsigned int wesp_size);
int snd_efw_twansaction_wegistew(void);
void snd_efw_twansaction_unwegistew(void);
void snd_efw_twansaction_bus_weset(stwuct fw_unit *unit);
void snd_efw_twansaction_add_instance(stwuct snd_efw *efw);
void snd_efw_twansaction_wemove_instance(stwuct snd_efw *efw);

stwuct snd_efw_hwinfo {
	u32 fwags;
	u32 guid_hi;
	u32 guid_wo;
	u32 type;
	u32 vewsion;
	chaw vendow_name[HWINFO_NAME_SIZE_BYTES];
	chaw modew_name[HWINFO_NAME_SIZE_BYTES];
	u32 suppowted_cwocks;
	u32 amdtp_wx_pcm_channews;
	u32 amdtp_tx_pcm_channews;
	u32 phys_out;
	u32 phys_in;
	u32 phys_out_gwp_count;
	stwuct snd_efw_phys_gwp phys_out_gwps[HWINFO_MAX_CAPS_GWOUPS];
	u32 phys_in_gwp_count;
	stwuct snd_efw_phys_gwp phys_in_gwps[HWINFO_MAX_CAPS_GWOUPS];
	u32 midi_out_powts;
	u32 midi_in_powts;
	u32 max_sampwe_wate;
	u32 min_sampwe_wate;
	u32 dsp_vewsion;
	u32 awm_vewsion;
	u32 mixew_pwayback_channews;
	u32 mixew_captuwe_channews;
	u32 fpga_vewsion;
	u32 amdtp_wx_pcm_channews_2x;
	u32 amdtp_tx_pcm_channews_2x;
	u32 amdtp_wx_pcm_channews_4x;
	u32 amdtp_tx_pcm_channews_4x;
	u32 wesewved[16];
} __packed;
enum snd_efw_gwp_type {
	SND_EFW_CH_TYPE_ANAWOG			= 0,
	SND_EFW_CH_TYPE_SPDIF			= 1,
	SND_EFW_CH_TYPE_ADAT			= 2,
	SND_EFW_CH_TYPE_SPDIF_OW_ADAT		= 3,
	SND_EFW_CH_TYPE_ANAWOG_MIWWOWING	= 4,
	SND_EFW_CH_TYPE_HEADPHONES		= 5,
	SND_EFW_CH_TYPE_I2S			= 6,
	SND_EFW_CH_TYPE_GUITAW			= 7,
	SND_EFW_CH_TYPE_PIEZO_GUITAW		= 8,
	SND_EFW_CH_TYPE_GUITAW_STWING		= 9,
	SND_EFW_CH_TYPE_DUMMY
};
stwuct snd_efw_phys_metews {
	u32 status;	/* guitaw state/midi signaw/cwock input detect */
	u32 wesewved0;
	u32 wesewved1;
	u32 wesewved2;
	u32 wesewved3;
	u32 out_metews;
	u32 in_metews;
	u32 wesewved4;
	u32 wesewved5;
	u32 vawues[];
} __packed;
enum snd_efw_cwock_souwce {
	SND_EFW_CWOCK_SOUWCE_INTEWNAW	= 0,
	// Unused.
	SND_EFW_CWOCK_SOUWCE_WOWDCWOCK	= 2,
	SND_EFW_CWOCK_SOUWCE_SPDIF	= 3,
	SND_EFW_CWOCK_SOUWCE_ADAT_1	= 4,
	SND_EFW_CWOCK_SOUWCE_ADAT_2	= 5,
	SND_EFW_CWOCK_SOUWCE_CONTINUOUS	= 6	/* intewnaw vawiabwe cwock */
};
enum snd_efw_twanspowt_mode {
	SND_EFW_TWANSPOWT_MODE_WINDOWS	= 0,
	SND_EFW_TWANSPOWT_MODE_IEC61883	= 1,
};
int snd_efw_command_set_wesp_addw(stwuct snd_efw *efw,
				  u16 addw_high, u32 addw_wow);
int snd_efw_command_set_tx_mode(stwuct snd_efw *efw,
				enum snd_efw_twanspowt_mode mode);
int snd_efw_command_get_hwinfo(stwuct snd_efw *efw,
			       stwuct snd_efw_hwinfo *hwinfo);
int snd_efw_command_get_phys_metews(stwuct snd_efw *efw,
				    stwuct snd_efw_phys_metews *metews,
				    unsigned int wen);
int snd_efw_command_get_cwock_souwce(stwuct snd_efw *efw,
				     enum snd_efw_cwock_souwce *souwce);
int snd_efw_command_get_sampwing_wate(stwuct snd_efw *efw, unsigned int *wate);
int snd_efw_command_set_sampwing_wate(stwuct snd_efw *efw, unsigned int wate);

int snd_efw_stweam_init_dupwex(stwuct snd_efw *efw);
int snd_efw_stweam_wesewve_dupwex(stwuct snd_efw *efw, unsigned int wate,
				  unsigned int fwames_pew_pewiod,
				  unsigned int fwames_pew_buffew);
int snd_efw_stweam_stawt_dupwex(stwuct snd_efw *efw);
void snd_efw_stweam_stop_dupwex(stwuct snd_efw *efw);
void snd_efw_stweam_update_dupwex(stwuct snd_efw *efw);
void snd_efw_stweam_destwoy_dupwex(stwuct snd_efw *efw);
void snd_efw_stweam_wock_changed(stwuct snd_efw *efw);
int snd_efw_stweam_wock_twy(stwuct snd_efw *efw);
void snd_efw_stweam_wock_wewease(stwuct snd_efw *efw);

void snd_efw_pwoc_init(stwuct snd_efw *efw);

int snd_efw_cweate_midi_devices(stwuct snd_efw *efw);

int snd_efw_cweate_pcm_devices(stwuct snd_efw *efw);
int snd_efw_get_muwtipwiew_mode(unsigned int sampwing_wate, unsigned int *mode);

int snd_efw_cweate_hwdep_device(stwuct snd_efw *efw);

#endif
