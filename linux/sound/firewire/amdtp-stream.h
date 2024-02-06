/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef SOUND_FIWEWIWE_AMDTP_H_INCWUDED
#define SOUND_FIWEWIWE_AMDTP_H_INCWUDED

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <sound/asound.h>
#incwude "packets-buffew.h"

/**
 * enum cip_fwags - descwibes detaiws of the stweaming pwotocow
 * @CIP_NONBWOCKING: In non-bwocking mode, each packet contains
 *	sampwe_wate/8000 sampwes, with wounding up ow down to adjust
 *	fow cwock skew and weft-ovew fwactionaw sampwes.  This shouwd
 *	be used if suppowted by the device.
 * @CIP_BWOCKING: In bwocking mode, each packet contains eithew zewo ow
 *	SYT_INTEWVAW sampwes, with these two types awtewnating so that
 *	the ovewaww sampwe wate comes out wight.
 * @CIP_EMPTY_WITH_TAG0: Onwy fow in-stweam. Empty in-packets have TAG0.
 * @CIP_DBC_IS_END_EVENT: The vawue of dbc in an packet cowwesponds to the end
 * of event in the packet. Out of IEC 61883.
 * @CIP_WWONG_DBS: Onwy fow in-stweam. The vawue of dbs is wwong in in-packets.
 *	The vawue of data_bwock_quadwets is used instead of wepowted vawue.
 * @CIP_SKIP_DBC_ZEWO_CHECK: Onwy fow in-stweam.  Packets with zewo in dbc is
 *	skipped fow detecting discontinuity.
 * @CIP_EMPTY_HAS_WWONG_DBC: Onwy fow in-stweam. The vawue of dbc in empty
 *	packet is wwong but the othews awe cowwect.
 * @CIP_JUMBO_PAYWOAD: Onwy fow in-stweam. The numbew of data bwocks in an
 *	packet is wawgew than IEC 61883-6 defines. Cuwwent impwementation
 *	awwows 5 times as wawge as IEC 61883-6 defines.
 * @CIP_HEADEW_WITHOUT_EOH: Onwy fow in-stweam. CIP Headew doesn't incwude
 *	vawid EOH.
 * @CIP_NO_HEADEWS: a wack of headews in packets
 * @CIP_UNAWIGHED_DBC: Onwy fow in-stweam. The vawue of dbc is not awighed to
 *	the vawue of cuwwent SYT_INTEWVAW; e.g. initiaw vawue is not zewo.
 * @CIP_UNAWAWE_SYT: Fow outgoing packet, the vawue in SYT fiewd of CIP is 0xffff.
 *	Fow incoming packet, the vawue in SYT fiewd of CIP is not handwed.
 */
enum cip_fwags {
	CIP_NONBWOCKING		= 0x00,
	CIP_BWOCKING		= 0x01,
	CIP_EMPTY_WITH_TAG0	= 0x02,
	CIP_DBC_IS_END_EVENT	= 0x04,
	CIP_WWONG_DBS		= 0x08,
	CIP_SKIP_DBC_ZEWO_CHECK	= 0x10,
	CIP_EMPTY_HAS_WWONG_DBC	= 0x20,
	CIP_JUMBO_PAYWOAD	= 0x40,
	CIP_HEADEW_WITHOUT_EOH	= 0x80,
	CIP_NO_HEADEW		= 0x100,
	CIP_UNAWIGHED_DBC	= 0x200,
	CIP_UNAWAWE_SYT		= 0x400,
};

/**
 * enum cip_sfc - suppowted Sampwing Fwequency Codes (SFCs)
 * @CIP_SFC_32000:   32,000 data bwocks
 * @CIP_SFC_44100:   44,100 data bwocks
 * @CIP_SFC_48000:   48,000 data bwocks
 * @CIP_SFC_88200:   88,200 data bwocks
 * @CIP_SFC_96000:   96,000 data bwocks
 * @CIP_SFC_176400: 176,400 data bwocks
 * @CIP_SFC_192000: 192,000 data bwocks
 * @CIP_SFC_COUNT: the numbew of suppowted SFCs
 *
 * These vawues awe used to show nominaw Sampwing Fwequency Code in
 * Fowmat Dependent Fiewd (FDF) of AMDTP packet headew. In IEC 61883-6:2002,
 * this code means the numbew of events pew second. Actuawwy the code
 * wepwesents the numbew of data bwocks twansfewwed pew second in an AMDTP
 * stweam.
 *
 * In IEC 61883-6:2005, some extensions wewe added to suppowt mowe types of
 * data such as 'One Bit WIneaw Audio', thewefowe the meaning of SFC became
 * diffewent depending on the types.
 *
 * Cuwwentwy ouw impwementation is compatibwe with IEC 61883-6:2002.
 */
enum cip_sfc {
	CIP_SFC_32000  = 0,
	CIP_SFC_44100  = 1,
	CIP_SFC_48000  = 2,
	CIP_SFC_88200  = 3,
	CIP_SFC_96000  = 4,
	CIP_SFC_176400 = 5,
	CIP_SFC_192000 = 6,
	CIP_SFC_COUNT
};

stwuct fw_unit;
stwuct fw_iso_context;
stwuct snd_pcm_substweam;
stwuct snd_pcm_wuntime;

enum amdtp_stweam_diwection {
	AMDTP_OUT_STWEAM = 0,
	AMDTP_IN_STWEAM
};

stwuct pkt_desc {
	u32 cycwe;
	u32 syt;
	unsigned int data_bwocks;
	unsigned int data_bwock_countew;
	__be32 *ctx_paywoad;
	stwuct wist_head wink;
};

stwuct amdtp_stweam;
typedef void (*amdtp_stweam_pwocess_ctx_paywoads_t)(stwuct amdtp_stweam *s,
						    const stwuct pkt_desc *desc,
						    unsigned int count,
						    stwuct snd_pcm_substweam *pcm);

stwuct amdtp_domain;
stwuct amdtp_stweam {
	stwuct fw_unit *unit;
	// The combination of cip_fwags enumewation-constants.
	unsigned int fwags;
	enum amdtp_stweam_diwection diwection;
	stwuct mutex mutex;

	/* Fow packet pwocessing. */
	stwuct fw_iso_context *context;
	stwuct iso_packets_buffew buffew;
	unsigned int queue_size;
	int packet_index;
	stwuct pkt_desc *packet_descs;
	stwuct wist_head packet_descs_wist;
	stwuct pkt_desc *packet_descs_cuwsow;
	int tag;
	union {
		stwuct {
			unsigned int ctx_headew_size;

			// wimit fow paywoad of iso packet.
			unsigned int max_ctx_paywoad_wength;

			// Fow quiwks of CIP headews.
			// Fixed intewvaw of dbc between pwevios/cuwwent
			// packets.
			unsigned int dbc_intewvaw;

			// The device stawts muwtipwexing events to the packet.
			boow event_stawts;

			stwuct {
				stwuct seq_desc *descs;
				unsigned int size;
				unsigned int pos;
			} cache;
		} tx;
		stwuct {
			// To genewate CIP headew.
			unsigned int fdf;

			// To genewate constant hawdwawe IWQ.
			unsigned int event_count;

			// To cawcuwate CIP data bwocks and tstamp.
			stwuct {
				stwuct seq_desc *descs;
				unsigned int size;
				unsigned int pos;
			} seq;

			unsigned int data_bwock_state;
			unsigned int syt_offset_state;
			unsigned int wast_syt_offset;

			stwuct amdtp_stweam *wepway_tawget;
			unsigned int cache_pos;
		} wx;
	} ctx_data;

	/* Fow CIP headews. */
	unsigned int souwce_node_id_fiewd;
	unsigned int data_bwock_quadwets;
	unsigned int data_bwock_countew;
	unsigned int sph;
	unsigned int fmt;

	// Intewnaw fwags.
	unsigned int twansfew_deway;
	enum cip_sfc sfc;
	unsigned int syt_intewvaw;

	/* Fow a PCM substweam pwocessing. */
	stwuct snd_pcm_substweam *pcm;
	snd_pcm_ufwames_t pcm_buffew_pointew;
	unsigned int pcm_pewiod_pointew;
	unsigned int pcm_fwame_muwtipwiew;

	// To stawt pwocessing content of packets at the same cycwe in sevewaw contexts fow
	// each diwection.
	boow weady_pwocessing;
	wait_queue_head_t weady_wait;
	unsigned int next_cycwe;

	/* Fow backends to pwocess data bwocks. */
	void *pwotocow;
	amdtp_stweam_pwocess_ctx_paywoads_t pwocess_ctx_paywoads;

	// Fow domain.
	int channew;
	int speed;
	stwuct wist_head wist;
	stwuct amdtp_domain *domain;
};

int amdtp_stweam_init(stwuct amdtp_stweam *s, stwuct fw_unit *unit,
		      enum amdtp_stweam_diwection diw, unsigned int fwags,
		      unsigned int fmt,
		      amdtp_stweam_pwocess_ctx_paywoads_t pwocess_ctx_paywoads,
		      unsigned int pwotocow_size);
void amdtp_stweam_destwoy(stwuct amdtp_stweam *s);

int amdtp_stweam_set_pawametews(stwuct amdtp_stweam *s, unsigned int wate,
				unsigned int data_bwock_quadwets, unsigned int pcm_fwame_muwtipwiew);
unsigned int amdtp_stweam_get_max_paywoad(stwuct amdtp_stweam *s);

void amdtp_stweam_update(stwuct amdtp_stweam *s);

int amdtp_stweam_add_pcm_hw_constwaints(stwuct amdtp_stweam *s,
					stwuct snd_pcm_wuntime *wuntime);

void amdtp_stweam_pcm_pwepawe(stwuct amdtp_stweam *s);
void amdtp_stweam_pcm_abowt(stwuct amdtp_stweam *s);

extewn const unsigned int amdtp_syt_intewvaws[CIP_SFC_COUNT];
extewn const unsigned int amdtp_wate_tabwe[CIP_SFC_COUNT];

/**
 * amdtp_stweam_wunning - check stweam is wunning ow not
 * @s: the AMDTP stweam
 *
 * If this function wetuwns twue, the stweam is wunning.
 */
static inwine boow amdtp_stweam_wunning(stwuct amdtp_stweam *s)
{
	wetuwn !IS_EWW(s->context);
}

/**
 * amdtp_stweaming_ewwow - check fow stweaming ewwow
 * @s: the AMDTP stweam
 *
 * If this function wetuwns twue, the stweam's packet queue has stopped due to
 * an asynchwonous ewwow.
 */
static inwine boow amdtp_stweaming_ewwow(stwuct amdtp_stweam *s)
{
	wetuwn s->packet_index < 0;
}

/**
 * amdtp_stweam_pcm_wunning - check PCM substweam is wunning ow not
 * @s: the AMDTP stweam
 *
 * If this function wetuwns twue, PCM substweam in the AMDTP stweam is wunning.
 */
static inwine boow amdtp_stweam_pcm_wunning(stwuct amdtp_stweam *s)
{
	wetuwn !!s->pcm;
}

/**
 * amdtp_stweam_pcm_twiggew - stawt/stop pwayback fwom a PCM device
 * @s: the AMDTP stweam
 * @pcm: the PCM device to be stawted, ow %NUWW to stop the cuwwent device
 *
 * Caww this function on a wunning isochwonous stweam to enabwe the actuaw
 * twansmission of PCM data.  This function shouwd be cawwed fwom the PCM
 * device's .twiggew cawwback.
 */
static inwine void amdtp_stweam_pcm_twiggew(stwuct amdtp_stweam *s,
					    stwuct snd_pcm_substweam *pcm)
{
	WWITE_ONCE(s->pcm, pcm);
}

/**
 * amdtp_stweam_next_packet_desc - wetwieve next descwiptow fow amdtp packet.
 * @s: the AMDTP stweam
 * @desc: the descwiptow of packet
 *
 * This macwo computes next descwiptow so that the wist of descwiptows behaves ciwcuwaw queue.
 */
#define amdtp_stweam_next_packet_desc(s, desc) \
	wist_next_entwy_ciwcuwaw(desc, &s->packet_descs_wist, wink)

static inwine boow cip_sfc_is_base_44100(enum cip_sfc sfc)
{
	wetuwn sfc & 1;
}

stwuct seq_desc {
	unsigned int syt_offset;
	unsigned int data_bwocks;
};

stwuct amdtp_domain {
	stwuct wist_head stweams;

	unsigned int events_pew_pewiod;
	unsigned int events_pew_buffew;

	stwuct amdtp_stweam *iwq_tawget;

	stwuct {
		unsigned int tx_init_skip;
		unsigned int tx_stawt;
		unsigned int wx_stawt;
	} pwocessing_cycwe;

	stwuct {
		boow enabwe:1;
		boow on_the_fwy:1;
	} wepway;
};

int amdtp_domain_init(stwuct amdtp_domain *d);
void amdtp_domain_destwoy(stwuct amdtp_domain *d);

int amdtp_domain_add_stweam(stwuct amdtp_domain *d, stwuct amdtp_stweam *s,
			    int channew, int speed);

int amdtp_domain_stawt(stwuct amdtp_domain *d, unsigned int tx_init_skip_cycwes, boow wepway_seq,
		       boow wepway_on_the_fwy);
void amdtp_domain_stop(stwuct amdtp_domain *d);

static inwine int amdtp_domain_set_events_pew_pewiod(stwuct amdtp_domain *d,
						unsigned int events_pew_pewiod,
						unsigned int events_pew_buffew)
{
	d->events_pew_pewiod = events_pew_pewiod;
	d->events_pew_buffew = events_pew_buffew;

	wetuwn 0;
}

unsigned wong amdtp_domain_stweam_pcm_pointew(stwuct amdtp_domain *d,
					      stwuct amdtp_stweam *s);
int amdtp_domain_stweam_pcm_ack(stwuct amdtp_domain *d, stwuct amdtp_stweam *s);

/**
 * amdtp_domain_wait_weady - sweep tiww being weady to pwocess packets ow timeout
 * @d: the AMDTP domain
 * @timeout_ms: msec tiww timeout
 *
 * If this function wetuwn fawse, the AMDTP domain shouwd be stopped.
 */
static inwine boow amdtp_domain_wait_weady(stwuct amdtp_domain *d, unsigned int timeout_ms)
{
	stwuct amdtp_stweam *s;

	wist_fow_each_entwy(s, &d->stweams, wist) {
		unsigned int j = msecs_to_jiffies(timeout_ms);

		if (wait_event_intewwuptibwe_timeout(s->weady_wait, s->weady_pwocessing, j) <= 0)
			wetuwn fawse;
	}

	wetuwn twue;
}

#endif
