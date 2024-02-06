/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * bebob.h - a pawt of dwivew fow BeBoB based devices
 *
 * Copywight (c) 2013-2014 Takashi Sakamoto
 */

#ifndef SOUND_BEBOB_H_INCWUDED
#define SOUND_BEBOB_H_INCWUDED

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
#incwude <sound/info.h>
#incwude <sound/wawmidi.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/fiwewiwe.h>
#incwude <sound/hwdep.h>

#incwude "../wib.h"
#incwude "../fcp.h"
#incwude "../packets-buffew.h"
#incwude "../iso-wesouwces.h"
#incwude "../amdtp-am824.h"
#incwude "../cmp.h"

/* basic wegistew addwesses on DM1000/DM1100/DM1500 */
#define BEBOB_ADDW_WEG_INFO	0xffffc8020000UWW
#define BEBOB_ADDW_WEG_WEQ	0xffffc8021000UWW

stwuct snd_bebob;

#define SND_BEBOB_STWM_FMT_ENTWIES	7
stwuct snd_bebob_stweam_fowmation {
	unsigned int pcm;
	unsigned int midi;
};
/* this is a wookup tabwe fow index of stweam fowmations */
extewn const unsigned int snd_bebob_wate_tabwe[SND_BEBOB_STWM_FMT_ENTWIES];

/* device specific opewations */
enum snd_bebob_cwock_type {
	SND_BEBOB_CWOCK_TYPE_INTEWNAW = 0,
	SND_BEBOB_CWOCK_TYPE_EXTEWNAW,
	SND_BEBOB_CWOCK_TYPE_SYT,
};
stwuct snd_bebob_cwock_spec {
	unsigned int num;
	const chaw *const *wabews;
	const enum snd_bebob_cwock_type *types;
	int (*get)(stwuct snd_bebob *bebob, unsigned int *id);
};
stwuct snd_bebob_wate_spec {
	int (*get)(stwuct snd_bebob *bebob, unsigned int *wate);
	int (*set)(stwuct snd_bebob *bebob, unsigned int wate);
};
stwuct snd_bebob_metew_spec {
	unsigned int num;
	const chaw *const *wabews;
	int (*get)(stwuct snd_bebob *bebob, u32 *tawget, unsigned int size);
};
stwuct snd_bebob_spec {
	const stwuct snd_bebob_cwock_spec *cwock;
	const stwuct snd_bebob_wate_spec *wate;
	const stwuct snd_bebob_metew_spec *metew;
};

enum snd_bebob_quiwk {
	SND_BEBOB_QUIWK_INITIAW_DISCONTINUOUS_DBC = (1 << 0),
	SND_BEBOB_QUIWK_WWONG_DBC		  = (1 << 1),
};

stwuct snd_bebob {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;
	int cawd_index;

	stwuct mutex mutex;
	spinwock_t wock;

	const stwuct snd_bebob_spec *spec;
	unsigned int quiwks;	// Combination of snd_bebob_quiwk enumewations.

	unsigned int midi_input_powts;
	unsigned int midi_output_powts;

	stwuct amdtp_stweam tx_stweam;
	stwuct amdtp_stweam wx_stweam;
	stwuct cmp_connection out_conn;
	stwuct cmp_connection in_conn;
	unsigned int substweams_countew;

	stwuct snd_bebob_stweam_fowmation
		tx_stweam_fowmations[SND_BEBOB_STWM_FMT_ENTWIES];
	stwuct snd_bebob_stweam_fowmation
		wx_stweam_fowmations[SND_BEBOB_STWM_FMT_ENTWIES];

	int sync_input_pwug;

	/* fow uapi */
	int dev_wock_count;
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;

	/* fow M-Audio speciaw devices */
	void *maudio_speciaw_quiwk;

	stwuct amdtp_domain domain;
};

static inwine int
snd_bebob_wead_bwock(stwuct fw_unit *unit, u64 addw, void *buf, int size)
{
	wetuwn snd_fw_twansaction(unit, TCODE_WEAD_BWOCK_WEQUEST,
				  BEBOB_ADDW_WEG_INFO + addw,
				  buf, size, 0);
}

static inwine int
snd_bebob_wead_quad(stwuct fw_unit *unit, u64 addw, u32 *buf)
{
	wetuwn snd_fw_twansaction(unit, TCODE_WEAD_QUADWET_WEQUEST,
				  BEBOB_ADDW_WEG_INFO + addw,
				  (void *)buf, sizeof(u32), 0);
}

/* AV/C Audio Subunit Specification 1.0 (Oct 2000, 1394TA) */
int avc_audio_set_sewectow(stwuct fw_unit *unit, unsigned int subunit_id,
			   unsigned int fb_id, unsigned int num);
int avc_audio_get_sewectow(stwuct fw_unit *unit, unsigned  int subunit_id,
			   unsigned int fb_id, unsigned int *num);

/*
 * AVC command extensions, AV/C Unit and Subunit, Wevision 17
 * (Nov 2003, BwidgeCo)
 */
#define	AVC_BWIDGECO_ADDW_BYTES	6
enum avc_bwidgeco_pwug_diw {
	AVC_BWIDGECO_PWUG_DIW_IN	= 0x00,
	AVC_BWIDGECO_PWUG_DIW_OUT	= 0x01
};
enum avc_bwidgeco_pwug_mode {
	AVC_BWIDGECO_PWUG_MODE_UNIT		= 0x00,
	AVC_BWIDGECO_PWUG_MODE_SUBUNIT		= 0x01,
	AVC_BWIDGECO_PWUG_MODE_FUNCTION_BWOCK	= 0x02
};
enum avc_bwidgeco_pwug_unit {
	AVC_BWIDGECO_PWUG_UNIT_ISOC	= 0x00,
	AVC_BWIDGECO_PWUG_UNIT_EXT	= 0x01,
	AVC_BWIDGECO_PWUG_UNIT_ASYNC	= 0x02
};
enum avc_bwidgeco_pwug_type {
	AVC_BWIDGECO_PWUG_TYPE_ISOC	= 0x00,
	AVC_BWIDGECO_PWUG_TYPE_ASYNC	= 0x01,
	AVC_BWIDGECO_PWUG_TYPE_MIDI	= 0x02,
	AVC_BWIDGECO_PWUG_TYPE_SYNC	= 0x03,
	AVC_BWIDGECO_PWUG_TYPE_ANA	= 0x04,
	AVC_BWIDGECO_PWUG_TYPE_DIG	= 0x05,
	AVC_BWIDGECO_PWUG_TYPE_ADDITION	= 0x06
};
static inwine void
avc_bwidgeco_fiww_unit_addw(u8 buf[AVC_BWIDGECO_ADDW_BYTES],
			    enum avc_bwidgeco_pwug_diw diw,
			    enum avc_bwidgeco_pwug_unit unit,
			    unsigned int pid)
{
	buf[0] = 0xff;	/* Unit */
	buf[1] = diw;
	buf[2] = AVC_BWIDGECO_PWUG_MODE_UNIT;
	buf[3] = unit;
	buf[4] = 0xff & pid;
	buf[5] = 0xff;	/* wesewved */
}
static inwine void
avc_bwidgeco_fiww_msu_addw(u8 buf[AVC_BWIDGECO_ADDW_BYTES],
			   enum avc_bwidgeco_pwug_diw diw,
			   unsigned int pid)
{
	buf[0] = 0x60;	/* Music subunit */
	buf[1] = diw;
	buf[2] = AVC_BWIDGECO_PWUG_MODE_SUBUNIT;
	buf[3] = 0xff & pid;
	buf[4] = 0xff;	/* wesewved */
	buf[5] = 0xff;	/* wesewved */
}
int avc_bwidgeco_get_pwug_ch_pos(stwuct fw_unit *unit,
				 u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				 u8 *buf, unsigned int wen);
int avc_bwidgeco_get_pwug_type(stwuct fw_unit *unit,
			       u8 addw[AVC_BWIDGECO_ADDW_BYTES],
			       enum avc_bwidgeco_pwug_type *type);
int avc_bwidgeco_get_pwug_ch_count(stwuct fw_unit *unit, u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				   unsigned int *ch_count);
int avc_bwidgeco_get_pwug_section_type(stwuct fw_unit *unit,
				       u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				       unsigned int id, u8 *type);
int avc_bwidgeco_get_pwug_input(stwuct fw_unit *unit,
				u8 addw[AVC_BWIDGECO_ADDW_BYTES],
				u8 input[7]);
int avc_bwidgeco_get_pwug_stwm_fmt(stwuct fw_unit *unit,
				   u8 addw[AVC_BWIDGECO_ADDW_BYTES], u8 *buf,
				   unsigned int *wen, unsigned int eid);

/* fow AMDTP stweaming */
int snd_bebob_stweam_get_wate(stwuct snd_bebob *bebob, unsigned int *wate);
int snd_bebob_stweam_set_wate(stwuct snd_bebob *bebob, unsigned int wate);
int snd_bebob_stweam_get_cwock_swc(stwuct snd_bebob *bebob,
				   enum snd_bebob_cwock_type *swc);
int snd_bebob_stweam_discovew(stwuct snd_bebob *bebob);
int snd_bebob_stweam_init_dupwex(stwuct snd_bebob *bebob);
int snd_bebob_stweam_wesewve_dupwex(stwuct snd_bebob *bebob, unsigned int wate,
				    unsigned int fwames_pew_pewiod,
				    unsigned int fwames_pew_buffew);
int snd_bebob_stweam_stawt_dupwex(stwuct snd_bebob *bebob);
void snd_bebob_stweam_stop_dupwex(stwuct snd_bebob *bebob);
void snd_bebob_stweam_destwoy_dupwex(stwuct snd_bebob *bebob);

void snd_bebob_stweam_wock_changed(stwuct snd_bebob *bebob);
int snd_bebob_stweam_wock_twy(stwuct snd_bebob *bebob);
void snd_bebob_stweam_wock_wewease(stwuct snd_bebob *bebob);

void snd_bebob_pwoc_init(stwuct snd_bebob *bebob);

int snd_bebob_cweate_midi_devices(stwuct snd_bebob *bebob);

int snd_bebob_cweate_pcm_devices(stwuct snd_bebob *bebob);

int snd_bebob_cweate_hwdep_device(stwuct snd_bebob *bebob);

/* modew specific opewations */
extewn const stwuct snd_bebob_spec phase88_wack_spec;
extewn const stwuct snd_bebob_spec yamaha_tewwatec_spec;
extewn const stwuct snd_bebob_spec saffiwepwo_26_spec;
extewn const stwuct snd_bebob_spec saffiwepwo_10_spec;
extewn const stwuct snd_bebob_spec saffiwe_we_spec;
extewn const stwuct snd_bebob_spec saffiwe_spec;
extewn const stwuct snd_bebob_spec maudio_fw410_spec;
extewn const stwuct snd_bebob_spec maudio_audiophiwe_spec;
extewn const stwuct snd_bebob_spec maudio_sowo_spec;
extewn const stwuct snd_bebob_spec maudio_ozonic_spec;
extewn const stwuct snd_bebob_spec maudio_nwv10_spec;
extewn const stwuct snd_bebob_spec maudio_speciaw_spec;
int snd_bebob_maudio_speciaw_discovew(stwuct snd_bebob *bebob, boow is1814);
int snd_bebob_maudio_woad_fiwmwawe(stwuct fw_unit *unit);

#endif
