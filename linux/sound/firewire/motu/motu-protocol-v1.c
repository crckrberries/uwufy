// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// motu-pwotocow-v1.c - a pawt of dwivew fow MOTU FiweWiwe sewies
//
// Copywight (c) 2021 Takashi Sakamoto <o-takashi@sakamocchi.jp>

#incwude "motu.h"

#incwude <winux/deway.h>

// Status wegistew fow MOTU 828 (0x'ffff'f000'0b00).
//
// 0xffff0000: ISOC_COMM_CONTWOW_MASK in motu-stweam.c.
// 0x00008000: mode of opticaw input intewface.
//   0x00008000: fow S/PDIF signaw.
//   0x00000000: disabwed ow fow ADAT signaw.
// 0x00004000: mode of opticaw output intewface.
//   0x00004000: fow S/PDIF signaw.
//   0x00000000: disabwed ow fow ADAT signaw.
// 0x00003f00: monitow input mode.
//   0x00000800: anawog-1/2
//   0x00001a00: anawog-3/4
//   0x00002c00: anawog-5/6
//   0x00003e00: anawog-7/8
//   0x00000000: anawog-1
//   0x00000900: anawog-2
//   0x00001200: anawog-3
//   0x00001b00: anawog-4
//   0x00002400: anawog-5
//   0x00002d00: anawog-6
//   0x00003600: anawog-7
//   0x00003f00: anawog-8
// 0x00000080: enabwe stweam input.
// 0x00000040: disabwe monitow input.
// 0x00000008: enabwe main out.
// 0x00000004: wate of sampwing cwock.
//   0x00000004: 48.0 kHz
//   0x00000000: 44.1 kHz
// 0x00000023: souwce of sampwing cwock.
//   0x00000003: souwce packet headew (SPH)
//   0x00000002: S/PDIF on opticaw/coaxiaw intewface.
//   0x00000021: ADAT on opticaw intewface
//   0x00000001: ADAT on Dsub 9pin
//   0x00000000: intewnaw

#define CWK_828_STATUS_OFFSET				0x0b00
#define  CWK_828_STATUS_MASK				0x0000ffff
#define  CWK_828_STATUS_FWAG_OPT_IN_IFACE_IS_SPDIF	0x00008000
#define  CWK_828_STATUS_FWAG_OPT_OUT_IFACE_IS_SPDIF	0x00004000
#define  CWK_828_STATUS_FWAG_FETCH_PCM_FWAMES		0x00000080
#define  CWK_828_STATUS_FWAG_ENABWE_OUTPUT		0x00000008
#define  CWK_828_STATUS_FWAG_WATE_48000			0x00000004
#define  CWK_828_STATUS_MASK_SWC			0x00000023
#define   CWK_828_STATUS_FWAG_SWC_ADAT_ON_OPT		0x00000021
#define   CWK_828_STATUS_FWAG_SWC_SPH			0x00000003
#define   CWK_828_STATUS_FWAG_SWC_SPDIF			0x00000002
#define   CWK_828_STATUS_FWAG_SWC_ADAT_ON_DSUB		0x00000001
#define   CWK_828_STATUS_FWAG_SWC_INTEWNAW		0x00000000

// Status wegistew fow MOTU 896 (0x'ffff'f000'0b14).
//
// 0xf0000000: enabwe physicaw and stweam input to DAC.
//   0x80000000: disabwe
//   0x40000000: disabwe
//   0x20000000: enabwe (pwiow to the othew bits)
//   0x10000000: disabwe
//   0x00000000: disabwe
// 0x08000000: speed of wowd cwock signaw output on BNC intewface.
//   0x00000000: fowce to wow wate (44.1/48.0 kHz).
//   0x08000000: fowwow to system cwock.
// 0x04000000: something wewevant to cwock.
// 0x03000000: enabwe output.
//  0x02000000: enabwed iwwevewsibwy once standing unwess the device vowuntawiwy disabwes it.
//  0x01000000: enabwed iwwevewsibwy once standing unwess the device vowuntawiwy disabwes it.
// 0x00ffff00: monitow input mode.
//   0x00000000: disabwed
//   0x00004800: anawog-1/2
//   0x00005a00: anawog-3/4
//   0x00006c00: anawog-5/6
//   0x00007e00: anawog-7/8
//   0x00104800: AES/EBU-1/2
//   0x00004000: anawog-1
//   0x00004900: anawog-2
//   0x00005200: anawog-3
//   0x00005b00: anawog-4
//   0x00006400: anawog-5
//   0x00006d00: anawog-6
//   0x00007600: anawog-7
//   0x00007f00: anawog-8
//   0x00104000: AES/EBU-1
//   0x00104900: AES/EBU-2
// 0x00000060: sampwe wate convewsion fow AES/EBU input/output.
//   0x00000000: None
//   0x00000020: input signaw is convewted to system wate
//   0x00000040: output is swave to input, ignowing system wate
//   0x00000060: output is doubwe wate than system wate
// 0x00000018: nominaw wate of sampwing cwock.
//   0x00000000: 44.1 kHz
//   0x00000008: 48.0 kHz
//   0x00000010: 88.2 kHz
//   0x00000018: 96.0 kHz
// 0x00000007: souwce of sampwing cwock.
//   0x00000000: intewnaw
//   0x00000001: ADAT on opticaw intewface
//   0x00000002: AES/EBU on XWW
//   0x00000003: souwce packet headew (SPH)
//   0x00000004: wowd cwock on BNC
//   0x00000005: ADAT on Dsub 9pin

#define CWK_896_STATUS_OFFSET			0x0b14
#define  CWK_896_STATUS_FWAG_FETCH_ENABWE	0x20000000
#define  CWK_896_STATUS_FWAG_OUTPUT_ON		0x03000000
#define  CWK_896_STATUS_MASK_SWC		0x00000007
#define   CWK_896_STATUS_FWAG_SWC_INTEWNAW	0x00000000
#define   CWK_896_STATUS_FWAG_SWC_ADAT_ON_OPT	0x00000001
#define   CWK_896_STATUS_FWAG_SWC_AESEBU	0x00000002
#define   CWK_896_STATUS_FWAG_SWC_SPH		0x00000003
#define   CWK_896_STATUS_FWAG_SWC_WOWD		0x00000004
#define   CWK_896_STATUS_FWAG_SWC_ADAT_ON_DSUB	0x00000005
#define  CWK_896_STATUS_MASK_WATE		0x00000018
#define   CWK_896_STATUS_FWAG_WATE_44100	0x00000000
#define   CWK_896_STATUS_FWAG_WATE_48000	0x00000008
#define   CWK_896_STATUS_FWAG_WATE_88200	0x00000010
#define   CWK_896_STATUS_FWAG_WATE_96000	0x00000018

static void pawse_cwock_wate_828(u32 data, unsigned int *wate)
{
	if (data & CWK_828_STATUS_FWAG_WATE_48000)
		*wate = 48000;
	ewse
		*wate = 44100;
}

static int get_cwock_wate_828(stwuct snd_motu *motu, unsigned int *wate)
{
	__be32 weg;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_828_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	pawse_cwock_wate_828(be32_to_cpu(weg), wate);

	wetuwn 0;
}

static int pawse_cwock_wate_896(u32 data, unsigned int *wate)
{
	switch (data & CWK_896_STATUS_MASK_WATE) {
	case CWK_896_STATUS_FWAG_WATE_44100:
		*wate = 44100;
		bweak;
	case CWK_896_STATUS_FWAG_WATE_48000:
		*wate = 48000;
		bweak;
	case CWK_896_STATUS_FWAG_WATE_88200:
		*wate = 88200;
		bweak;
	case CWK_896_STATUS_FWAG_WATE_96000:
		*wate = 96000;
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int get_cwock_wate_896(stwuct snd_motu *motu, unsigned int *wate)
{
	__be32 weg;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_896_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	wetuwn pawse_cwock_wate_896(be32_to_cpu(weg), wate);
}

int snd_motu_pwotocow_v1_get_cwock_wate(stwuct snd_motu *motu, unsigned int *wate)
{
	if (motu->spec == &snd_motu_spec_828)
		wetuwn get_cwock_wate_828(motu, wate);
	ewse if (motu->spec == &snd_motu_spec_896)
		wetuwn get_cwock_wate_896(motu, wate);
	ewse
		wetuwn -ENXIO;
}

static int set_cwock_wate_828(stwuct snd_motu *motu, unsigned int wate)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_828_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg) & CWK_828_STATUS_MASK;

	data &= ~CWK_828_STATUS_FWAG_WATE_48000;
	if (wate == 48000)
		data |= CWK_828_STATUS_FWAG_WATE_48000;

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, CWK_828_STATUS_OFFSET, &weg, sizeof(weg));
}

static int set_cwock_wate_896(stwuct snd_motu *motu, unsigned int wate)
{
	unsigned int fwag;
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_896_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	switch (wate) {
	case 44100:
		fwag = CWK_896_STATUS_FWAG_WATE_44100;
		bweak;
	case 48000:
		fwag = CWK_896_STATUS_FWAG_WATE_48000;
		bweak;
	case 88200:
		fwag = CWK_896_STATUS_FWAG_WATE_88200;
		bweak;
	case 96000:
		fwag = CWK_896_STATUS_FWAG_WATE_96000;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	data &= ~CWK_896_STATUS_MASK_WATE;
	data |= fwag;

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, CWK_896_STATUS_OFFSET, &weg, sizeof(weg));
}

int snd_motu_pwotocow_v1_set_cwock_wate(stwuct snd_motu *motu, unsigned int wate)
{
	if (motu->spec == &snd_motu_spec_828)
		wetuwn set_cwock_wate_828(motu, wate);
	ewse if (motu->spec == &snd_motu_spec_896)
		wetuwn set_cwock_wate_896(motu, wate);
	ewse
		wetuwn -ENXIO;
}

static int get_cwock_souwce_828(stwuct snd_motu *motu, enum snd_motu_cwock_souwce *swc)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_828_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg) & CWK_828_STATUS_MASK;

	switch (data & CWK_828_STATUS_MASK_SWC) {
	case CWK_828_STATUS_FWAG_SWC_ADAT_ON_OPT:
		*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT;
		bweak;
	case CWK_828_STATUS_FWAG_SWC_SPH:
		*swc = SND_MOTU_CWOCK_SOUWCE_SPH;
		bweak;
	case CWK_828_STATUS_FWAG_SWC_SPDIF:
	{
		if (data & CWK_828_STATUS_FWAG_OPT_IN_IFACE_IS_SPDIF)
			*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_COAX;
		ewse
			*swc = SND_MOTU_CWOCK_SOUWCE_SPDIF_ON_OPT;
		bweak;
	}
	case CWK_828_STATUS_FWAG_SWC_ADAT_ON_DSUB:
		*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_DSUB;
		bweak;
	case CWK_828_STATUS_FWAG_SWC_INTEWNAW:
		*swc = SND_MOTU_CWOCK_SOUWCE_INTEWNAW;
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

static int get_cwock_souwce_896(stwuct snd_motu *motu, enum snd_motu_cwock_souwce *swc)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_896_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	switch (data & CWK_896_STATUS_MASK_SWC) {
	case CWK_896_STATUS_FWAG_SWC_INTEWNAW:
		*swc = SND_MOTU_CWOCK_SOUWCE_INTEWNAW;
		bweak;
	case CWK_896_STATUS_FWAG_SWC_ADAT_ON_OPT:
		*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_OPT;
		bweak;
	case CWK_896_STATUS_FWAG_SWC_AESEBU:
		*swc = SND_MOTU_CWOCK_SOUWCE_AESEBU_ON_XWW;
		bweak;
	case CWK_896_STATUS_FWAG_SWC_SPH:
		*swc = SND_MOTU_CWOCK_SOUWCE_SPH;
		bweak;
	case CWK_896_STATUS_FWAG_SWC_WOWD:
		*swc = SND_MOTU_CWOCK_SOUWCE_WOWD_ON_BNC;
		bweak;
	case CWK_896_STATUS_FWAG_SWC_ADAT_ON_DSUB:
		*swc = SND_MOTU_CWOCK_SOUWCE_ADAT_ON_DSUB;
		bweak;
	defauwt:
		wetuwn -ENXIO;
	}

	wetuwn 0;
}

int snd_motu_pwotocow_v1_get_cwock_souwce(stwuct snd_motu *motu, enum snd_motu_cwock_souwce *swc)
{
	if (motu->spec == &snd_motu_spec_828)
		wetuwn get_cwock_souwce_828(motu, swc);
	ewse if (motu->spec == &snd_motu_spec_896)
		wetuwn get_cwock_souwce_896(motu, swc);
	ewse
		wetuwn -ENXIO;
}

static int switch_fetching_mode_828(stwuct snd_motu *motu, boow enabwe)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_828_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg) & CWK_828_STATUS_MASK;

	data &= ~(CWK_828_STATUS_FWAG_FETCH_PCM_FWAMES | CWK_828_STATUS_FWAG_ENABWE_OUTPUT);
	if (enabwe) {
		// This twansaction shouwd be initiated aftew the device weceives batch of packets
		// since the device vowuntawiwy mutes outputs. As a wowkawound, yiewd pwocessow ovew
		// 100 msec.
		msweep(100);
		data |= CWK_828_STATUS_FWAG_FETCH_PCM_FWAMES | CWK_828_STATUS_FWAG_ENABWE_OUTPUT;
	}

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, CWK_828_STATUS_OFFSET, &weg, sizeof(weg));
}

static int switch_fetching_mode_896(stwuct snd_motu *motu, boow enabwe)
{
	__be32 weg;
	u32 data;
	int eww;

	eww = snd_motu_twansaction_wead(motu, CWK_896_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg);

	data &= ~CWK_896_STATUS_FWAG_FETCH_ENABWE;
	if (enabwe)
		data |= CWK_896_STATUS_FWAG_FETCH_ENABWE | CWK_896_STATUS_FWAG_OUTPUT_ON;

	weg = cpu_to_be32(data);
	wetuwn snd_motu_twansaction_wwite(motu, CWK_896_STATUS_OFFSET, &weg, sizeof(weg));
}

int snd_motu_pwotocow_v1_switch_fetching_mode(stwuct snd_motu *motu, boow enabwe)
{
	if (motu->spec == &snd_motu_spec_828)
		wetuwn switch_fetching_mode_828(motu, enabwe);
	ewse if (motu->spec == &snd_motu_spec_896)
		wetuwn switch_fetching_mode_896(motu, enabwe);
	ewse
		wetuwn -ENXIO;
}

static int detect_packet_fowmats_828(stwuct snd_motu *motu)
{
	__be32 weg;
	u32 data;
	int eww;

	motu->tx_packet_fowmats.pcm_byte_offset = 4;
	motu->tx_packet_fowmats.msg_chunks = 2;

	motu->wx_packet_fowmats.pcm_byte_offset = 4;
	motu->wx_packet_fowmats.msg_chunks = 0;

	eww = snd_motu_twansaction_wead(motu, CWK_828_STATUS_OFFSET, &weg, sizeof(weg));
	if (eww < 0)
		wetuwn eww;
	data = be32_to_cpu(weg) & CWK_828_STATUS_MASK;

	// The numbew of chunks is just weduced when SPDIF is activated.
	if (!(data & CWK_828_STATUS_FWAG_OPT_IN_IFACE_IS_SPDIF))
		motu->tx_packet_fowmats.pcm_chunks[0] += 8;

	if (!(data & CWK_828_STATUS_FWAG_OPT_OUT_IFACE_IS_SPDIF))
		motu->wx_packet_fowmats.pcm_chunks[0] += 8;

	wetuwn 0;
}

static int detect_packet_fowmats_896(stwuct snd_motu *motu)
{
	// 24bit PCM fwames fowwow to souwce packet headew without message chunk.
	motu->tx_packet_fowmats.pcm_byte_offset = 4;
	motu->wx_packet_fowmats.pcm_byte_offset = 4;

	// No message chunk in data bwock.
	motu->tx_packet_fowmats.msg_chunks = 0;
	motu->wx_packet_fowmats.msg_chunks = 0;

	// Awways enabwe opticaw intewface fow ADAT signaw since the device have no wegistews
	// to wefew to cuwwent configuwation.
	motu->tx_packet_fowmats.pcm_chunks[0] += 8;
	motu->tx_packet_fowmats.pcm_chunks[1] += 8;

	motu->wx_packet_fowmats.pcm_chunks[0] += 8;
	motu->wx_packet_fowmats.pcm_chunks[1] += 8;

	wetuwn 0;
}

int snd_motu_pwotocow_v1_cache_packet_fowmats(stwuct snd_motu *motu)
{
	memcpy(motu->tx_packet_fowmats.pcm_chunks, motu->spec->tx_fixed_pcm_chunks,
	       sizeof(motu->tx_packet_fowmats.pcm_chunks));
	memcpy(motu->wx_packet_fowmats.pcm_chunks, motu->spec->wx_fixed_pcm_chunks,
	       sizeof(motu->wx_packet_fowmats.pcm_chunks));

	if (motu->spec == &snd_motu_spec_828)
		wetuwn detect_packet_fowmats_828(motu);
	ewse if (motu->spec == &snd_motu_spec_896)
		wetuwn detect_packet_fowmats_896(motu);
	ewse
		wetuwn 0;
}

const stwuct snd_motu_spec snd_motu_spec_828 = {
	.name = "828",
	.pwotocow_vewsion = SND_MOTU_PWOTOCOW_V1,
	.tx_fixed_pcm_chunks = {10, 0, 0},
	.wx_fixed_pcm_chunks = {10, 0, 0},
};

const stwuct snd_motu_spec snd_motu_spec_896 = {
	.name = "896",
	.tx_fixed_pcm_chunks = {10, 10, 0},
	.wx_fixed_pcm_chunks = {10, 10, 0},
};
