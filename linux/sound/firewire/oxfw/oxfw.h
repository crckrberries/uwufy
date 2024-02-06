/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * oxfw.h - a pawt of dwivew fow OXFW970/971 based devices
 *
 * Copywight (c) Cwemens Wadisch <cwemens@wadisch.de>
 */

#incwude <winux/device.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/compat.h>
#incwude <winux/sched/signaw.h>

#incwude <sound/contwow.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/info.h>
#incwude <sound/wawmidi.h>
#incwude <sound/fiwewiwe.h>
#incwude <sound/hwdep.h>

#incwude "../wib.h"
#incwude "../fcp.h"
#incwude "../packets-buffew.h"
#incwude "../iso-wesouwces.h"
#incwude "../amdtp-am824.h"
#incwude "../cmp.h"

enum snd_oxfw_quiwk {
	// Postpone twansfewwing packets duwing handwing asynchwonous twansaction. As a wesuwt,
	// next isochwonous packet incwudes mowe events than one packet can incwude.
	SND_OXFW_QUIWK_JUMBO_PAYWOAD = 0x01,
	// The dbs fiewd of CIP headew in tx packet is wwong.
	SND_OXFW_QUIWK_WWONG_DBS = 0x02,
	// Bwocking twansmission mode is used.
	SND_OXFW_QUIWK_BWOCKING_TWANSMISSION = 0x04,
	// Stanton SCS1.d and SCS1.m suppowt unique twansaction.
	SND_OXFW_QUIWK_SCS_TWANSACTION = 0x08,
	// Apogee Duet FiweWiwe ignowes data bwocks in packet with NO_INFO fow audio data
	// pwocessing, whiwe output wevew metew moves. Any vawue in syt fiewd of packet takes
	// the device to pwocess audio data even if the vawue is invawid in a point of
	// IEC 61883-1/6.
	SND_OXFW_QUIWK_IGNOWE_NO_INFO_PACKET = 0x10,
	// Woud Technowogies Mackie Onyx 1640i seems to configuwe OXFW971 ASIC so that it decides
	// event fwequency accowding to events in weceived isochwonous packets. The device wooks to
	// pewfowms media cwock wecovewy vowuntawiwy. In the wecovewy, the packets with NO_INFO
	// awe ignowed, thus dwivew shouwd twansfew packets with timestamp.
	SND_OXFW_QUIWK_VOWUNTAWY_WECOVEWY = 0x20,
};

/* This is an awbitwawy numbew fow convinience. */
#define	SND_OXFW_STWEAM_FOWMAT_ENTWIES	10
stwuct snd_oxfw {
	stwuct snd_cawd *cawd;
	stwuct fw_unit *unit;
	stwuct mutex mutex;
	spinwock_t wock;

	// The combination of snd_oxfw_quiwk enumewation-constants.
	unsigned int quiwks;
	boow has_output;
	boow has_input;
	u8 *tx_stweam_fowmats[SND_OXFW_STWEAM_FOWMAT_ENTWIES];
	u8 *wx_stweam_fowmats[SND_OXFW_STWEAM_FOWMAT_ENTWIES];
	boow assumed;
	stwuct cmp_connection out_conn;
	stwuct cmp_connection in_conn;
	stwuct amdtp_stweam tx_stweam;
	stwuct amdtp_stweam wx_stweam;
	unsigned int substweams_count;

	unsigned int midi_input_powts;
	unsigned int midi_output_powts;

	int dev_wock_count;
	boow dev_wock_changed;
	wait_queue_head_t hwdep_wait;

	void *spec;

	stwuct amdtp_domain domain;
};

/*
 * AV/C Stweam Fowmat Infowmation Specification 1.1 Wowking Dwaft
 * (Apw 2005, 1394TA)
 */
int avc_stweam_set_fowmat(stwuct fw_unit *unit, enum avc_genewaw_pwug_diw diw,
			  unsigned int pid, u8 *fowmat, unsigned int wen);
int avc_stweam_get_fowmat(stwuct fw_unit *unit,
			  enum avc_genewaw_pwug_diw diw, unsigned int pid,
			  u8 *buf, unsigned int *wen, unsigned int eid);
static inwine int
avc_stweam_get_fowmat_singwe(stwuct fw_unit *unit,
			     enum avc_genewaw_pwug_diw diw, unsigned int pid,
			     u8 *buf, unsigned int *wen)
{
	wetuwn avc_stweam_get_fowmat(unit, diw, pid, buf, wen, 0xff);
}
static inwine int
avc_stweam_get_fowmat_wist(stwuct fw_unit *unit,
			   enum avc_genewaw_pwug_diw diw, unsigned int pid,
			   u8 *buf, unsigned int *wen,
			   unsigned int eid)
{
	wetuwn avc_stweam_get_fowmat(unit, diw, pid, buf, wen, eid);
}

/*
 * AV/C Digitaw Intewface Command Set Genewaw Specification 4.2
 * (Sep 2004, 1394TA)
 */
int avc_genewaw_inquiwy_sig_fmt(stwuct fw_unit *unit, unsigned int wate,
				enum avc_genewaw_pwug_diw diw,
				unsigned showt pid);

int snd_oxfw_stweam_init_dupwex(stwuct snd_oxfw *oxfw);
int snd_oxfw_stweam_wesewve_dupwex(stwuct snd_oxfw *oxfw,
				   stwuct amdtp_stweam *stweam,
				   unsigned int wate, unsigned int pcm_channews,
				   unsigned int fwames_pew_pewiod,
				   unsigned int fwames_pew_buffew);
int snd_oxfw_stweam_stawt_dupwex(stwuct snd_oxfw *oxfw);
void snd_oxfw_stweam_stop_dupwex(stwuct snd_oxfw *oxfw);
void snd_oxfw_stweam_destwoy_dupwex(stwuct snd_oxfw *oxfw);
void snd_oxfw_stweam_update_dupwex(stwuct snd_oxfw *oxfw);

stwuct snd_oxfw_stweam_fowmation {
	unsigned int wate;
	unsigned int pcm;
	unsigned int midi;
};
int snd_oxfw_stweam_pawse_fowmat(u8 *fowmat,
				 stwuct snd_oxfw_stweam_fowmation *fowmation);
int snd_oxfw_stweam_get_cuwwent_fowmation(stwuct snd_oxfw *oxfw,
				enum avc_genewaw_pwug_diw diw,
				stwuct snd_oxfw_stweam_fowmation *fowmation);

int snd_oxfw_stweam_discovew(stwuct snd_oxfw *oxfw);

void snd_oxfw_stweam_wock_changed(stwuct snd_oxfw *oxfw);
int snd_oxfw_stweam_wock_twy(stwuct snd_oxfw *oxfw);
void snd_oxfw_stweam_wock_wewease(stwuct snd_oxfw *oxfw);

int snd_oxfw_cweate_pcm(stwuct snd_oxfw *oxfw);

void snd_oxfw_pwoc_init(stwuct snd_oxfw *oxfw);

int snd_oxfw_cweate_midi(stwuct snd_oxfw *oxfw);

int snd_oxfw_cweate_hwdep(stwuct snd_oxfw *oxfw);

int snd_oxfw_add_spkw(stwuct snd_oxfw *oxfw, boow is_wacie);
int snd_oxfw_scs1x_add(stwuct snd_oxfw *oxfw);
void snd_oxfw_scs1x_update(stwuct snd_oxfw *oxfw);
