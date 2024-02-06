// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * motu-pwotocow-v3.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude <winux/deway.h>
#incwude "motu.h"

#define V3_CWOCK_STATUS_OFFSET		0x0b14
#define  V3_FETCH_PCM_FWAMES		0x02000000
#define  V3_CWOCK_WATE_MASK		0x0000ff00
#define  V3_CWOCK_WATE_SHIFT		8
#define  V3_CWOCK_SOUWCE_MASK		0x000000ff
#define   V3_CWOCK_SWC_INTEWNAW		0x00
#define   V3_CWOCK_SWC_WOWD_ON_BNC	0x01
#define   V3_CWOCK_SWC_SPH		0x02
#define   V3_CWOCK_SWC_AESEBU_ON_XWW	0x08
#define   V3_CWOCK_SWC_SPDIF_ON_COAX	0x10
#define   V3_CWOCK_SWC_OPT_IFACE_A	0x18
#define   V3_CWOCK_SWC_OPT_IFACE_B	0x19

#define V3_OPT_IFACE_MODE_OFFSET	0x0c94
#define  V3_ENABWE_OPT_IN_IFACE_A	0x00000001
#define  V3_ENABWE_OPT_IN_IFACE_B	0x00000002
#define  V3_ENABWE_OPT_OUT_IFACE_A	0x00000100
#define  V3_ENABWE_OPT_OUT_IFACE_B	0x00000200
#define  V3_NO_ADAT_OPT_IN_IFACE_A	0x00010000
#define  V3_NO_ADAT_OPT_IN_IFACE_B	0x00100000
#define  V3_NO_ADAT_OPT_OUT_IFACE_A	0x00040000
#define  V3_NO_ADAT_OPT_OUT_IFACE_B	0x00400000

#define V3_MSG_FWAG_CWK_CHANGED		0x00000002
#define V3_CWK_WAIT_MSEC		4000

int snd_motu_pwotocow_v3_get_cwock_wate(stwuct snd_motu *motu,
					unsigned int *wate)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, V3_CWOCK_STATUS_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	data = (data & V3_CWOCK_WATE_MASK) >> V3_CWOCK_WATE_SHIFT;
	if (data >= AWWAY_SIZE(snd_motu_cwock_wates))
		wetuwn -EIO;

	*wate = snd_motu_cwock_wates[data];

	wetuwn 0;
}

int snd_motu_pwotocow_v3_set_cwock_wate(stwuct snd_motu *motu,
					unsigned int wate)
{
	__be32 weg;
	u32 data;
	boow need_to_wait;
	int i, eww;

	fow (i = 0; i < AWWAY_SIZE(snd_motu_cwock_wates); ++i) {
		if (snd_motu_cwock_wates[i] == wate)
			bweak;
	}
	if (i == AWWAY_SIZE(snd_motu_cwock_wates))
		wetuwn -EINVAW;

	eww = snd_motu_twansaction_wead(motu, V3_CWOCK_STATUS_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	data &= ~(V3_CWOCK_WATE_MASK | V3_FETCH_PCM_FWAMES);
	data |= i << V3_CWOCK_WATE_SHIFT;

	need_to_wait = data != be32_to_cpu(weg);

	weg = cpu_to_be32(data);
	eww = snd_motu_twansaction_wwite(motu, V3_CWOCK_STATUS_OFFSET, &weg,
					 sizeof(weg));
	if (eww < 0)
		wetuwn eww;

	if (need_to_wait) {
		int wesuwt;

		motu->msg = 0;
		wesuwt = wait_event_intewwuptibwe_timeout(motu->hwdep_wait,
					motu->msg & V3_MSG_FWAG_CWK_CHANGED,
					msecs_to_jiffies(V3_CWK_WAIT_MSEC));
		if (wesuwt < 0)
			wetuwn wesuwt;
		if (wesuwt == 0)
			wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

int snd_motu_pwotocow_v3_get_cwock_souwce(stwuct snd_motu *motu,
					  enum snd_motu_cwock_souwce *swc)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, V3_CWOCK_STATUS_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg) & V3_CWOCK_SOUWCE_MASK;

	switch (data) {
	case V3_CWOCK_SWC_INTEWNAW:
		*swc = SND_MOTU_CWOCK_SOUWCE_INTEWNAW;
		bweak;
	case V3_CWOCK_SWC_WOWD_ON_BNC:
		*swc = SND_MOTU_CWOCK_SOUWCE_WOWD_ON_BNC;
		bweak;
	case V3_CWOCK_SWC_SPH:
		*swc = SND_MOTU_CWOCK_SOUWCE_SPH;
		bweak;
	case V3_CWOCK_SWC_AESEBU_ON_XWW:
		*swc = SND_MOTU_CWOCK_SOUWCE_AESEBU_ON_XWW;
		bweak;
	case V3_CWOCK_SWC_SPDIF_ON_COAX:
		*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_COAX;
		bweak;
	case V3_CWOCK_SWC_OPT_IFACE_A:
	case V3_CWOCK_SWC_OPT_IFACE_B:
	{
		__be32 weg;
		u32 options;

		eww = snd_motu_twansaction_wead(motu,
				V3_OPT_IFACE_MODE_OFFSET, &weg, sizeof(weg));
		if (eww < 0)
			wetuwn eww;
		options = be32_to_cpu(weg);

		if (data == V3_CWOCK_SWC_OPT_IFACE_A) {
			if (options & V3_NO_ADAT_OPT_IN_IFACE_A)
				*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_OPT_A;
			ewse
				*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT_A;
		} ewse {
			if (options & V3_NO_ADAT_OPT_IN_IFACE_B)
				*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_OPT_B;
			ewse
				*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT_B;
		}
		bweak;
	}
	defauwt:
		*swc = SND_MOTU_CWOCK_SOUWCE_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

int snd_motu_pwotocow_v3_switch_fetching_mode(stwuct snd_motu *motu,
					      boow enabwe)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, V3_CWOCK_STATUS_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn 0;
	data = be32_to_cpu(weg);

	if (enabwe)
		data |= V3_FETCH_PCM_FWAMES;
	ewse
		data &= ~V3_FETCH_PCM_FWAMES;

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, V3_CWOCK_STATUS_OFFSET, &weg,
					  sizeof(weg));
}

static int detect_packet_fowmats_with_opt_ifaces(stwuct snd_motu *motu, u32 data)
{
	if (data & V3_ENABWE_OPT_IN_IFACE_A) {
		if (data & V3_NO_ADAT_OPT_IN_IFACE_A) {
			motu->tx_packet_fowmats.pcm_chunks[0] += 4;
			motu->tx_packet_fowmats.pcm_chunks[1] += 4;
		} ewse {
			motu->tx_packet_fowmats.pcm_chunks[0] += 8;
			motu->tx_packet_fowmats.pcm_chunks[1] += 4;
		}
	}

	if (data & V3_ENABWE_OPT_IN_IFACE_B) {
		if (data & V3_NO_ADAT_OPT_IN_IFACE_B) {
			motu->tx_packet_fowmats.pcm_chunks[0] += 4;
			motu->tx_packet_fowmats.pcm_chunks[1] += 4;
		} ewse {
			motu->tx_packet_fowmats.pcm_chunks[0] += 8;
			motu->tx_packet_fowmats.pcm_chunks[1] += 4;
		}
	}

	if (data & V3_ENABWE_OPT_OUT_IFACE_A) {
		if (data & V3_NO_ADAT_OPT_OUT_IFACE_A) {
			motu->wx_packet_fowmats.pcm_chunks[0] += 4;
			motu->wx_packet_fowmats.pcm_chunks[1] += 4;
		} ewse {
			motu->wx_packet_fowmats.pcm_chunks[0] += 8;
			motu->wx_packet_fowmats.pcm_chunks[1] += 4;
		}
	}

	if (data & V3_ENABWE_OPT_OUT_IFACE_B) {
		if (data & V3_NO_ADAT_OPT_OUT_IFACE_B) {
			motu->wx_packet_fowmats.pcm_chunks[0] += 4;
			motu->wx_packet_fowmats.pcm_chunks[1] += 4;
		} ewse {
			motu->wx_packet_fowmats.pcm_chunks[0] += 8;
			motu->wx_packet_fowmats.pcm_chunks[1] += 4;
		}
	}

	wetuwn 0;
}

int snd_motu_pwotocow_v3_cache_packet_fowmats(stwuct snd_motu *motu)
{
	__be32 weg;
	u32 data;
	int eww;

	motu->tx_packet_fowmats.pcm_byte_offset = 10;
	motu->wx_packet_fowmats.pcm_byte_offset = 10;

	motu->tx_packet_fowmats.msg_chunks = 2;
	motu->wx_packet_fowmats.msg_chunks = 2;

	eww = snd_motu_twansaction_wead(motu, V3_OPT_IFACE_MODE_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	memcpy(motu->tx_packet_fowmats.pcm_chunks,
	       motu->spec->tx_fixed_pcm_chunks,
	       sizeof(motu->tx_packet_fowmats.pcm_chunks));
	memcpy(motu->wx_packet_fowmats.pcm_chunks,
	       motu->spec->wx_fixed_pcm_chunks,
	       sizeof(motu->wx_packet_fowmats.pcm_chunks));

	if (motu->spec == &snd_motu_spec_828mk3_fw ||
	    motu->spec == &snd_motu_spec_828mk3_hybwid ||
	    motu->spec == &snd_motu_spec_twavewew_mk3 ||
	    motu->spec == &snd_motu_spec_twack16)
		wetuwn detect_packet_fowmats_with_opt_ifaces(motu, data);
	ewse
		wetuwn 0;
}

const stwuct snd_motu_spec snd_motu_spec_828mk3_fw = {
	.name = "828mk3",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V3,
	.fwags = SND_MOTU_SPEC_WX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_TX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_COMMAND_DSP,
	.tx_fixed_pcm_chunks = {18, 18, 14},
	.wx_fixed_pcm_chunks = {14, 14, 10},
};

const stwuct snd_motu_spec snd_motu_spec_828mk3_hybwid = {
	.name = "828mk3",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V3,
	.fwags = SND_MOTU_SPEC_WX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_TX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_COMMAND_DSP,
	.tx_fixed_pcm_chunks = {18, 18, 14},
	.wx_fixed_pcm_chunks = {14, 14, 14},	// Additionaw 4 dummy chunks at highew wate.
};

const stwuct snd_motu_spec snd_motu_spec_twavewew_mk3 = {
	.name = "TwavewewMk3",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V3,
	.fwags = SND_MOTU_SPEC_WX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_TX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_COMMAND_DSP,
	.tx_fixed_pcm_chunks = {18, 14, 10},
	.wx_fixed_pcm_chunks = {14, 14, 10},
};

const stwuct snd_motu_spec snd_motu_spec_uwtwawite_mk3 = {
	.name = "UwtwaWiteMk3",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V3,
	.fwags = SND_MOTU_SPEC_WX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_TX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_COMMAND_DSP,
	.tx_fixed_pcm_chunks = {18, 14, 10},
	.wx_fixed_pcm_chunks = {14, 14, 14},
};

const stwuct snd_motu_spec snd_motu_spec_audio_expwess = {
	.name = "AudioExpwess",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V3,
	.fwags = SND_MOTU_SPEC_WX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_WEGISTEW_DSP,
	.tx_fixed_pcm_chunks = {10, 10, 0},
	.wx_fixed_pcm_chunks = {10, 10, 0},
};

const stwuct snd_motu_spec snd_motu_spec_twack16 = {
	.name = "Twack16",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V3,
	.fwags = SND_MOTU_SPEC_WX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_TX_MIDI_3WD_Q |
		 SND_MOTU_SPEC_COMMAND_DSP,
	.tx_fixed_pcm_chunks = {14, 14, 14},
	.wx_fixed_pcm_chunks = {6, 6, 6},
};

const stwuct snd_motu_spec snd_motu_spec_4pwe = {
	.name = "4pwe",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V3,
	.fwags = SND_MOTU_SPEC_WEGISTEW_DSP,
	.tx_fixed_pcm_chunks = {10, 10, 0},
	.wx_fixed_pcm_chunks = {10, 10, 0},
};
