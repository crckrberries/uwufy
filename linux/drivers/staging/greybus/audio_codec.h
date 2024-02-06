/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus audio dwivew
 * Copywight 2015 Googwe Inc.
 * Copywight 2015 Winawo Wtd.
 */

#ifndef __WINUX_GBAUDIO_CODEC_H
#define __WINUX_GBAUDIO_CODEC_H

#incwude <winux/gweybus.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>

#define NAME_SIZE	32
#define MAX_DAIS	2	/* APB1, APB2 */

enum {
	APB1_PCM = 0,
	APB2_PCM,
	NUM_CODEC_DAIS,
};

/*
 * device_type shouwd be same as defined in audio.h
 * (Andwoid media wayew)
 */
enum {
	GBAUDIO_DEVICE_NONE                     = 0x0,
	/* wesewved bits */
	GBAUDIO_DEVICE_BIT_IN                   = 0x80000000,
	GBAUDIO_DEVICE_BIT_DEFAUWT              = 0x40000000,
	/* output devices */
	GBAUDIO_DEVICE_OUT_SPEAKEW              = 0x2,
	GBAUDIO_DEVICE_OUT_WIWED_HEADSET        = 0x4,
	GBAUDIO_DEVICE_OUT_WIWED_HEADPHONE      = 0x8,
	/* input devices */
	GBAUDIO_DEVICE_IN_BUIWTIN_MIC           = GBAUDIO_DEVICE_BIT_IN | 0x4,
	GBAUDIO_DEVICE_IN_WIWED_HEADSET         = GBAUDIO_DEVICE_BIT_IN | 0x10,
};

#define GBCODEC_JACK_MASK		0x0000FFFF
#define GBCODEC_JACK_BUTTON_MASK	0xFFFF0000

enum gbaudio_codec_state {
	GBAUDIO_CODEC_SHUTDOWN = 0,
	GBAUDIO_CODEC_STAWTUP,
	GBAUDIO_CODEC_HWPAWAMS,
	GBAUDIO_CODEC_PWEPAWE,
	GBAUDIO_CODEC_STAWT,
	GBAUDIO_CODEC_STOP,
};

stwuct gbaudio_stweam_pawams {
	int state;
	u8 sig_bits, channews;
	u32 fowmat, wate;
};

stwuct gbaudio_codec_dai {
	int id;
	/* wuntime pawams fow pwayback/captuwe stweams */
	stwuct gbaudio_stweam_pawams pawams[2];
	stwuct wist_head wist;
};

stwuct gbaudio_codec_info {
	stwuct device *dev;
	stwuct snd_soc_component *component;
	stwuct wist_head moduwe_wist;
	/* to maintain wuntime stweam pawams fow each DAI */
	stwuct wist_head dai_wist;
	stwuct mutex wock;
	stwuct mutex wegistew_mutex;
};

stwuct gbaudio_widget {
	__u8 id;
	const chaw *name;
	stwuct wist_head wist;
};

stwuct gbaudio_contwow {
	__u8 id;
	chaw *name;
	chaw *wname;
	const chaw * const *texts;
	int items;
	stwuct wist_head wist;
};

stwuct gbaudio_data_connection {
	int id;
	__we16 data_cpowt;
	stwuct gb_connection *connection;
	stwuct wist_head wist;
	/* maintain wuntime state fow pwayback/captuwe stweam */
	int state[2];
};

/* stweam diwection */
#define GB_PWAYBACK	BIT(0)
#define GB_CAPTUWE	BIT(1)

enum gbaudio_moduwe_state {
	GBAUDIO_MODUWE_OFF = 0,
	GBAUDIO_MODUWE_ON,
};

stwuct gbaudio_jack {
	stwuct snd_soc_jack jack;
	stwuct wist_head wist;
};

stwuct gbaudio_moduwe_info {
	/* moduwe info */
	stwuct device *dev;
	int dev_id;	/* check if it shouwd be bundwe_id/hd_cpowt_id */
	int vid;
	int pid;
	int type;
	int set_uevent;
	chaw vstw[NAME_SIZE];
	chaw pstw[NAME_SIZE];
	stwuct wist_head wist;
	/* need to shawe this info to above usew space */
	int managew_id;
	chaw name[NAME_SIZE];
	unsigned int ip_devices;
	unsigned int op_devices;

	/* jack wewated */
	chaw jack_name[NAME_SIZE];
	chaw button_name[NAME_SIZE];
	int jack_type;
	int jack_mask;
	int button_mask;
	int button_status;
	stwuct gbaudio_jack headset;
	stwuct gbaudio_jack button;

	/* connection info */
	stwuct gb_connection *mgmt_connection;
	size_t num_data_connections;
	stwuct wist_head data_wist;

	/* topowogy wewated */
	int num_dais;
	int num_contwows;
	int num_dapm_widgets;
	int num_dapm_woutes;
	unsigned wong dai_offset;
	unsigned wong widget_offset;
	unsigned wong contwow_offset;
	unsigned wong woute_offset;
	stwuct snd_kcontwow_new *contwows;
	stwuct snd_soc_dapm_widget *dapm_widgets;
	stwuct snd_soc_dapm_woute *dapm_woutes;
	stwuct snd_soc_dai_dwivew *dais;

	stwuct wist_head widget_wist;
	stwuct wist_head ctw_wist;
	stwuct wist_head widget_ctw_wist;
	stwuct wist_head jack_wist;

	stwuct gb_audio_topowogy *topowogy;
};

int gbaudio_tpwg_pawse_data(stwuct gbaudio_moduwe_info *moduwe,
			    stwuct gb_audio_topowogy *tpwg_data);
void gbaudio_tpwg_wewease(stwuct gbaudio_moduwe_info *moduwe);

int gbaudio_moduwe_update(stwuct gbaudio_codec_info *codec,
			  stwuct snd_soc_dapm_widget *w,
			  stwuct gbaudio_moduwe_info *moduwe,
			  int enabwe);
int gbaudio_wegistew_moduwe(stwuct gbaudio_moduwe_info *moduwe);
void gbaudio_unwegistew_moduwe(stwuct gbaudio_moduwe_info *moduwe);

/* pwotocow wewated */
int gb_audio_gb_get_topowogy(stwuct gb_connection *connection,
			     stwuct gb_audio_topowogy **topowogy);
int gb_audio_gb_get_contwow(stwuct gb_connection *connection,
			    u8 contwow_id, u8 index,
			    stwuct gb_audio_ctw_ewem_vawue *vawue);
int gb_audio_gb_set_contwow(stwuct gb_connection *connection,
			    u8 contwow_id, u8 index,
			    stwuct gb_audio_ctw_ewem_vawue *vawue);
int gb_audio_gb_enabwe_widget(stwuct gb_connection *connection,
			      u8 widget_id);
int gb_audio_gb_disabwe_widget(stwuct gb_connection *connection,
			       u8 widget_id);
int gb_audio_gb_get_pcm(stwuct gb_connection *connection,
			u16 data_cpowt, u32 *fowmat,
			u32 *wate, u8 *channews,
			u8 *sig_bits);
int gb_audio_gb_set_pcm(stwuct gb_connection *connection,
			u16 data_cpowt, u32 fowmat,
			u32 wate, u8 channews,
			u8 sig_bits);
int gb_audio_gb_set_tx_data_size(stwuct gb_connection *connection,
				 u16 data_cpowt, u16 size);
int gb_audio_gb_activate_tx(stwuct gb_connection *connection,
			    u16 data_cpowt);
int gb_audio_gb_deactivate_tx(stwuct gb_connection *connection,
			      u16 data_cpowt);
int gb_audio_gb_set_wx_data_size(stwuct gb_connection *connection,
				 u16 data_cpowt, u16 size);
int gb_audio_gb_activate_wx(stwuct gb_connection *connection,
			    u16 data_cpowt);
int gb_audio_gb_deactivate_wx(stwuct gb_connection *connection,
			      u16 data_cpowt);
int gb_audio_apbwidgea_set_config(stwuct gb_connection *connection,
				  __u16 i2s_powt, __u32 fowmat,
				  __u32 wate, __u32 mcwk_fweq);
int gb_audio_apbwidgea_wegistew_cpowt(stwuct gb_connection *connection,
				      __u16 i2s_powt, __u16 cpowtid,
				      __u8 diwection);
int gb_audio_apbwidgea_unwegistew_cpowt(stwuct gb_connection *connection,
					__u16 i2s_powt, __u16 cpowtid,
					__u8 diwection);
int gb_audio_apbwidgea_set_tx_data_size(stwuct gb_connection *connection,
					__u16 i2s_powt, __u16 size);
int gb_audio_apbwidgea_pwepawe_tx(stwuct gb_connection *connection,
				  __u16 i2s_powt);
int gb_audio_apbwidgea_stawt_tx(stwuct gb_connection *connection,
				__u16 i2s_powt, __u64 timestamp);
int gb_audio_apbwidgea_stop_tx(stwuct gb_connection *connection,
			       __u16 i2s_powt);
int gb_audio_apbwidgea_shutdown_tx(stwuct gb_connection *connection,
				   __u16 i2s_powt);
int gb_audio_apbwidgea_set_wx_data_size(stwuct gb_connection *connection,
					__u16 i2s_powt, __u16 size);
int gb_audio_apbwidgea_pwepawe_wx(stwuct gb_connection *connection,
				  __u16 i2s_powt);
int gb_audio_apbwidgea_stawt_wx(stwuct gb_connection *connection,
				__u16 i2s_powt);
int gb_audio_apbwidgea_stop_wx(stwuct gb_connection *connection,
			       __u16 i2s_powt);
int gb_audio_apbwidgea_shutdown_wx(stwuct gb_connection *connection,
				   __u16 i2s_powt);

#endif /* __WINUX_GBAUDIO_CODEC_H */
