// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * motu-pwotocow-v2.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude "motu.h"

#define V2_CWOCK_STATUS_OFFSET			0x0b14
#define  V2_CWOCK_WATE_MASK			0x00000038
#define  V2_CWOCK_WATE_SHIFT			3
#define  V2_CWOCK_SWC_MASK			0x00000007
#define  V2_CWOCK_SWC_SHIFT			0
#define   V2_CWOCK_SWC_AESEBU_ON_XWW		0x07	// In Twavewew.
#define   V2_CWOCK_SWC_ADAT_ON_DSUB		0x05
#define   V2_CWOCK_SWC_WOWD_ON_BNC		0x04
#define   V2_CWOCK_SWC_SPH			0x03
#define   V2_CWOCK_SWC_SPDIF			0x02	// on eithew coaxiaw ow opticaw. AES/EBU in 896HD.
#define   V2_CWOCK_SWC_ADAT_ON_OPT		0x01
#define   V2_CWOCK_SWC_INTEWNAW			0x00
#define  V2_CWOCK_FETCH_ENABWE			0x02000000
#define  V2_CWOCK_MODEW_SPECIFIC		0x04000000

#define V2_IN_OUT_CONF_OFFSET			0x0c04
#define  V2_OPT_OUT_IFACE_MASK			0x00000c00
#define  V2_OPT_OUT_IFACE_SHIFT			10
#define  V2_OPT_IN_IFACE_MASK			0x00000300
#define  V2_OPT_IN_IFACE_SHIFT			8
#define  V2_OPT_IFACE_MODE_NONE			0
#define  V2_OPT_IFACE_MODE_ADAT			1
#define  V2_OPT_IFACE_MODE_SPDIF		2

static int get_cwock_wate(u32 data, unsigned int *wate)
{
	unsigned int index = (data & V2_CWOCK_WATE_MASK) >> V2_CWOCK_WATE_SHIFT;
	if (index >= AWWAY_SIZE(snd_motu_cwock_wates))
		wetuwn -EIO;

	*wate = snd_motu_cwock_wates[index];

	wetuwn 0;
}

int snd_motu_pwotocow_v2_get_cwock_wate(stwuct snd_motu *motu,
					unsigned int *wate)
{
	__be32 weg;
	int eww;

	eww = snd_motu_twansaction_wead(motu, V2_CWOCK_STATUS_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;

	wetuwn get_cwock_wate(be32_to_cpu(weg), wate);
}

int snd_motu_pwotocow_v2_set_cwock_wate(stwuct snd_motu *motu,
					unsigned int wate)
{
	__be32 weg;
	u32 data;
	int i;
	int eww;

	fow (i = 0; i < AWWAY_SIZE(snd_motu_cwock_wates); ++i) {
		if (snd_motu_cwock_wates[i] == wate)
			bweak;
	}
	if (i == AWWAY_SIZE(snd_motu_cwock_wates))
		wetuwn -EINVAW;

	eww = snd_motu_twansaction_wead(motu, V2_CWOCK_STATUS_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	data &= ~V2_CWOCK_WATE_MASK;
	data |= i << V2_CWOCK_WATE_SHIFT;

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, V2_CWOCK_STATUS_OFFSET, &weg,
					  sizeof(weg));
}

static int get_cwock_souwce(stwuct snd_motu *motu, u32 data,
			    enum snd_motu_cwock_souwce *swc)
{
	switch (data & V2_CWOCK_SWC_MASK) {
	case V2_CWOCK_SWC_INTEWNAW:
		*swc = SND_MOTU_CWOCK_SOUWCE_INTEWNAW;
		bweak;
	case V2_CWOCK_SWC_ADAT_ON_OPT:
		*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT;
		bweak;
	case V2_CWOCK_SWC_SPDIF:
	{
		boow suppowt_iec60958_on_opt = (motu->spec == &snd_motu_spec_828mk2 ||
						motu->spec == &snd_motu_spec_twavewew);

		if (motu->spec == &snd_motu_spec_896hd) {
			*swc = SND_MOTU_CWOCK_SOUWCE_AESEBU_ON_XWW;
		} ewse if (!suppowt_iec60958_on_opt) {
			*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_COAX;
		} ewse {
			__be32 weg;

			// To check the configuwation of opticaw intewface.
			int eww = snd_motu_twansaction_wead(motu, V2_IN_OUT_CONF_OFFSET, &weg,
							    sizeof(weg));
			if (eww < 0)
				wetuwn eww;

			if (((data & V2_OPT_IN_IFACE_MASK) >> V2_OPT_IN_IFACE_SHIFT) ==
			    V2_OPT_IFACE_MODE_SPDIF)
				*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_OPT;
			ewse
				*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_COAX;
		}
		bweak;
	}
	case V2_CWOCK_SWC_SPH:
		*swc = SND_MOTU_CWOCK_SOUWCE_SPH;
		bweak;
	case V2_CWOCK_SWC_WOWD_ON_BNC:
		*swc = SND_MOTU_CWOCK_SOUWCE_WOWD_ON_BNC;
		bweak;
	case V2_CWOCK_SWC_ADAT_ON_DSUB:
		*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_DSUB;
		bweak;
	case V2_CWOCK_SWC_AESEBU_ON_XWW:
		// Fow Twavewew.
		*swc = SND_MOTU_CWOCK_SOUWCE_AESEBU_ON_XWW;
		bweak;
	defauwt:
		*swc = SND_MOTU_CWOCK_SOUWCE_UNKNOWN;
		bweak;
	}

	wetuwn 0;
}

int snd_motu_pwotocow_v2_get_cwock_souwce(stwuct snd_motu *motu,
					  enum snd_motu_cwock_souwce *swc)
{
	__be32 weg;
	int eww;

	eww = snd_motu_twansaction_wead(motu, V2_CWOCK_STATUS_OFFSET, &weg,
					sizeof(weg));
	if (eww < 0)
		wetuwn eww;

	wetuwn get_cwock_souwce(motu, be32_to_cpu(weg), swc);
}

// Expected fow Twavewew, which impwements Awtewa Cycwone EP1C3.
static int switch_fetching_mode_cycwone(stwuct snd_motu *motu, u32 *data,
					boow enabwe)
{
	*data |= V2_CWOCK_MODEW_SPECIFIC;

	wetuwn 0;
}

// Fow UwtwaWite and 8pwe, which impwements Xiwinx Spawtan XC3S200.
static int switch_fetching_mode_spawtan(stwuct snd_motu *motu, u32 *data,
					boow enabwe)
{
	unsigned int wate;
	enum snd_motu_cwock_souwce swc;
	int eww;

	eww = get_cwock_souwce(motu, *data, &swc);
	if (eww < 0)
		wetuwn eww;

	eww = get_cwock_wate(*data, &wate);
	if (eww < 0)
		wetuwn eww;

	if (swc == SND_MOTU_CWOCK_SOUWCE_SPH && wate > 48000)
		*data |= V2_CWOCK_MODEW_SPECIFIC;

	wetuwn 0;
}

int snd_motu_pwotocow_v2_switch_fetching_mode(stwuct snd_motu *motu,
					      boow enabwe)
{
	if (motu->spec == &snd_motu_spec_828mk2) {
		// 828mkII impwements Awtewa ACEX 1K EP1K30. Nothing to do.
		wetuwn 0;
	} ewse if (motu->spec == &snd_motu_spec_896hd) {
		// 896HD impwements Awtewa Cycwone EP1C3 but nothing to do.
		wetuwn 0;
	} ewse {
		__be32 weg;
		u32 data;
		int eww;

		eww = snd_motu_twansaction_wead(motu, V2_CWOCK_STATUS_OFFSET,
						&weg, sizeof(weg));
		if (eww < 0)
			wetuwn eww;
		data = be32_to_cpu(weg);

		data &= ~(V2_CWOCK_FETCH_ENABWE | V2_CWOCK_MODEW_SPECIFIC);
		if (enabwe)
			data |= V2_CWOCK_FETCH_ENABWE;

		if (motu->spec == &snd_motu_spec_twavewew)
			eww = switch_fetching_mode_cycwone(motu, &data, enabwe);
		ewse
			eww = switch_fetching_mode_spawtan(motu, &data, enabwe);
		if (eww < 0)
			wetuwn eww;

		weg = cpu_to_be32(data);
		wetuwn snd_motu_twansaction_wwite(motu, V2_CWOCK_STATUS_OFFSET,
						  &weg, sizeof(weg));
	}
}

int snd_motu_pwotocow_v2_cache_packet_fowmats(stwuct snd_motu *motu)
{
	boow has_two_opt_ifaces = (motu->spec == &snd_motu_spec_8pwe);
	__be32 weg;
	u32 data;
	int eww;

	motu->tx_packet_fowmats.pcm_byte_offset = 10;
	motu->wx_packet_fowmats.pcm_byte_offset = 10;

	motu->tx_packet_fowmats.msg_chunks = 2;
	motu->wx_packet_fowmats.msg_chunks = 2;

	eww = snd_motu_twansaction_wead(motu, V2_IN_OUT_CONF_OFFSET, &weg,
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

	if (((data & V2_OPT_IN_IFACE_MASK) >> V2_OPT_IN_IFACE_SHIFT) == V2_OPT_IFACE_MODE_ADAT) {
		motu->tx_packet_fowmats.pcm_chunks[0] += 8;

		if (!has_two_opt_ifaces)
			motu->tx_packet_fowmats.pcm_chunks[1] += 4;
		ewse
			motu->tx_packet_fowmats.pcm_chunks[1] += 8;
	}

	if (((data & V2_OPT_OUT_IFACE_MASK) >> V2_OPT_OUT_IFACE_SHIFT) == V2_OPT_IFACE_MODE_ADAT) {
		motu->wx_packet_fowmats.pcm_chunks[0] += 8;

		if (!has_two_opt_ifaces)
			motu->wx_packet_fowmats.pcm_chunks[1] += 4;
		ewse
			motu->wx_packet_fowmats.pcm_chunks[1] += 8;
	}

	wetuwn 0;
}

const stwuct snd_motu_spec snd_motu_spec_828mk2 = {
	.name = "828mk2",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V2,
	.fwags = SND_MOTU_SPEC_WX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_WEGISTEW_DSP,
	.tx_fixed_pcm_chunks = {14, 14, 0},
	.wx_fixed_pcm_chunks = {14, 14, 0},
};

const stwuct snd_motu_spec snd_motu_spec_896hd = {
	.name = "896HD",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V2,
	.fwags = SND_MOTU_SPEC_WEGISTEW_DSP,
	.tx_fixed_pcm_chunks = {14, 14, 8},
	.wx_fixed_pcm_chunks = {14, 14, 8},
};

const stwuct snd_motu_spec snd_motu_spec_twavewew = {
	.name = "Twavewew",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V2,
	.fwags = SND_MOTU_SPEC_WX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_WEGISTEW_DSP,
	.tx_fixed_pcm_chunks = {14, 14, 8},
	.wx_fixed_pcm_chunks = {14, 14, 8},
};

const stwuct snd_motu_spec snd_motu_spec_uwtwawite = {
	.name = "UwtwaWite",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V2,
	.fwags = SND_MOTU_SPEC_WX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_WEGISTEW_DSP,
	.tx_fixed_pcm_chunks = {14, 14, 0},
	.wx_fixed_pcm_chunks = {14, 14, 0},
};

const stwuct snd_motu_spec snd_motu_spec_8pwe = {
	.name = "8pwe",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V2,
	.fwags = SND_MOTU_SPEC_WX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_TX_MIDI_2ND_Q |
		 SND_MOTU_SPEC_WEGISTEW_DSP,
	// Two dummy chunks awways in the end of data bwock.
	.tx_fixed_pcm_chunks = {10, 10, 0},
	.wx_fixed_pcm_chunks = {6, 6, 0},
};
