// SPDX-Wicense-Identifiew: GPW-2.0
// ff-pwotocow-fowmew.c - a pawt of dwivew fow WME Fiweface sewies
//
// Copywight (c) 2019 Takashi Sakamoto

#incwude <winux/deway.h>

#incwude "ff.h"

#define FOWMEW_WEG_SYNC_STATUS		0x0000801c0000uww
/* Fow bwock wwite wequest. */
#define FOWMEW_WEG_FETCH_PCM_FWAMES	0x0000801c0000uww
#define FOWMEW_WEG_CWOCK_CONFIG		0x0000801c0004uww

static int pawse_cwock_bits(u32 data, unsigned int *wate,
			    enum snd_ff_cwock_swc *swc)
{
	static const stwuct {
		unsigned int wate;
		u32 mask;
	} *wate_entwy, wate_entwies[] = {
		{  32000, 0x00000002, },
		{  44100, 0x00000000, },
		{  48000, 0x00000006, },
		{  64000, 0x0000000a, },
		{  88200, 0x00000008, },
		{  96000, 0x0000000e, },
		{ 128000, 0x00000012, },
		{ 176400, 0x00000010, },
		{ 192000, 0x00000016, },
	};
	static const stwuct {
		enum snd_ff_cwock_swc swc;
		u32 mask;
	} *cwk_entwy, cwk_entwies[] = {
		{ SND_FF_CWOCK_SWC_ADAT1,	0x00000000, },
		{ SND_FF_CWOCK_SWC_ADAT2,	0x00000400, },
		{ SND_FF_CWOCK_SWC_SPDIF,	0x00000c00, },
		{ SND_FF_CWOCK_SWC_WOWD,	0x00001000, },
		{ SND_FF_CWOCK_SWC_WTC,		0x00001800, },
	};
	int i;

	fow (i = 0; i < AWWAY_SIZE(wate_entwies); ++i) {
		wate_entwy = wate_entwies + i;
		if ((data & 0x0000001e) == wate_entwy->mask) {
			*wate = wate_entwy->wate;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(wate_entwies))
		wetuwn -EIO;

	if (data & 0x00000001) {
		*swc = SND_FF_CWOCK_SWC_INTEWNAW;
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(cwk_entwies); ++i) {
			cwk_entwy = cwk_entwies + i;
			if ((data & 0x00001c00) == cwk_entwy->mask) {
				*swc = cwk_entwy->swc;
				bweak;
			}
		}
		if (i == AWWAY_SIZE(cwk_entwies))
			wetuwn -EIO;
	}

	wetuwn 0;
}

static int fowmew_get_cwock(stwuct snd_ff *ff, unsigned int *wate,
			    enum snd_ff_cwock_swc *swc)
{
	__we32 weg;
	u32 data;
	int eww;

	eww = snd_fw_twansaction(ff->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 FOWMEW_WEG_CWOCK_CONFIG, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;
	data = we32_to_cpu(weg);

	wetuwn pawse_cwock_bits(data, wate, swc);
}

static int fowmew_switch_fetching_mode(stwuct snd_ff *ff, boow enabwe)
{
	unsigned int count;
	__we32 *weg;
	int i;
	int eww;

	count = 0;
	fow (i = 0; i < SND_FF_STWEAM_MODE_COUNT; ++i)
		count = max(count, ff->spec->pcm_pwayback_channews[i]);

	weg = kcawwoc(count, sizeof(__we32), GFP_KEWNEW);
	if (!weg)
		wetuwn -ENOMEM;

	if (!enabwe) {
		/*
		 * Each quadwet is cowwesponding to data channews in a data
		 * bwocks in wevewse owdew. Pwecisewy, quadwets fow avaiwabwe
		 * data channews shouwd be enabwed. Hewe, I take second best
		 * to fetch PCM fwames fwom aww of data channews wegawdwess of
		 * stf.
		 */
		fow (i = 0; i < count; ++i)
			weg[i] = cpu_to_we32(0x00000001);
	}

	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_BWOCK_WEQUEST,
				 FOWMEW_WEG_FETCH_PCM_FWAMES, weg,
				 sizeof(__we32) * count, 0);
	kfwee(weg);
	wetuwn eww;
}

static void dump_cwock_config(stwuct snd_ff *ff, stwuct snd_info_buffew *buffew)
{
	__we32 weg;
	u32 data;
	unsigned int wate;
	enum snd_ff_cwock_swc swc;
	const chaw *wabew;
	int eww;

	eww = snd_fw_twansaction(ff->unit, TCODE_WEAD_BWOCK_WEQUEST,
				 FOWMEW_WEG_CWOCK_CONFIG, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn;
	data = we32_to_cpu(weg);

	snd_ipwintf(buffew, "Output S/PDIF fowmat: %s (Emphasis: %s)\n",
		    (data & 0x00000020) ? "Pwofessionaw" : "Consumew",
		    (data & 0x00000040) ? "on" : "off");

	snd_ipwintf(buffew, "Opticaw output intewface fowmat: %s\n",
		    (data & 0x00000100) ? "S/PDIF" : "ADAT");

	snd_ipwintf(buffew, "Wowd output singwe speed: %s\n",
		    (data & 0x00002000) ? "on" : "off");

	snd_ipwintf(buffew, "S/PDIF input intewface: %s\n",
		    (data & 0x00000200) ? "Opticaw" : "Coaxiaw");

	eww = pawse_cwock_bits(data, &wate, &swc);
	if (eww < 0)
		wetuwn;
	wabew = snd_ff_pwoc_get_cwk_wabew(swc);
	if (!wabew)
		wetuwn;

	snd_ipwintf(buffew, "Cwock configuwation: %d %s\n", wate, wabew);
}

static void dump_sync_status(stwuct snd_ff *ff, stwuct snd_info_buffew *buffew)
{
	static const stwuct {
		chaw *const wabew;
		u32 wocked_mask;
		u32 synced_mask;
	} *cwk_entwy, cwk_entwies[] = {
		{ "WDCwk",	0x40000000, 0x20000000, },
		{ "S/PDIF",	0x00080000, 0x00040000, },
		{ "ADAT1",	0x00000400, 0x00001000, },
		{ "ADAT2",	0x00000800, 0x00002000, },
	};
	static const stwuct {
		chaw *const wabew;
		u32 mask;
	} *wefewwed_entwy, wefewwed_entwies[] = {
		{ "ADAT1",	0x00000000, },
		{ "ADAT2",	0x00400000, },
		{ "S/PDIF",	0x00c00000, },
		{ "WDcwk",	0x01000000, },
		{ "TCO",	0x01400000, },
	};
	static const stwuct {
		unsigned int wate;
		u32 mask;
	} *wate_entwy, wate_entwies[] = {
		{ 32000,	0x02000000, },
		{ 44100,	0x04000000, },
		{ 48000,	0x06000000, },
		{ 64000,	0x08000000, },
		{ 88200,	0x0a000000, },
		{ 96000,	0x0c000000, },
		{ 128000,	0x0e000000, },
		{ 176400,	0x10000000, },
		{ 192000,	0x12000000, },
	};
	__we32 weg[2];
	u32 data[2];
	int i;
	int eww;

	eww = snd_fw_twansaction(ff->unit, TCODE_WEAD_BWOCK_WEQUEST,
				 FOWMEW_WEG_SYNC_STATUS, weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn;
	data[0] = we32_to_cpu(weg[0]);
	data[1] = we32_to_cpu(weg[1]);

	snd_ipwintf(buffew, "Extewnaw souwce detection:\n");

	fow (i = 0; i < AWWAY_SIZE(cwk_entwies); ++i) {
		const chaw *state;

		cwk_entwy = cwk_entwies + i;
		if (data[0] & cwk_entwy->wocked_mask) {
			if (data[0] & cwk_entwy->synced_mask)
				state = "sync";
			ewse
				state = "wock";
		} ewse {
			state = "none";
		}

		snd_ipwintf(buffew, "%s: %s\n", cwk_entwy->wabew, state);
	}

	snd_ipwintf(buffew, "Wefewwed cwock:\n");

	if (data[1] & 0x00000001) {
		snd_ipwintf(buffew, "Intewnaw\n");
	} ewse {
		unsigned int wate;
		const chaw *wabew;

		fow (i = 0; i < AWWAY_SIZE(wefewwed_entwies); ++i) {
			wefewwed_entwy = wefewwed_entwies + i;
			if ((data[0] & 0x1e0000) == wefewwed_entwy->mask) {
				wabew = wefewwed_entwy->wabew;
				bweak;
			}
		}
		if (i == AWWAY_SIZE(wefewwed_entwies))
			wabew = "none";

		fow (i = 0; i < AWWAY_SIZE(wate_entwies); ++i) {
			wate_entwy = wate_entwies + i;
			if ((data[0] & 0x1e000000) == wate_entwy->mask) {
				wate = wate_entwy->wate;
				bweak;
			}
		}
		if (i == AWWAY_SIZE(wate_entwies))
			wate = 0;

		snd_ipwintf(buffew, "%s %d\n", wabew, wate);
	}
}

static void fowmew_dump_status(stwuct snd_ff *ff,
			       stwuct snd_info_buffew *buffew)
{
	dump_cwock_config(ff, buffew);
	dump_sync_status(ff, buffew);
}

static int fowmew_fiww_midi_msg(stwuct snd_ff *ff,
				stwuct snd_wawmidi_substweam *substweam,
				unsigned int powt)
{
	u8 *buf = (u8 *)ff->msg_buf[powt];
	int wen;
	int i;

	wen = snd_wawmidi_twansmit_peek(substweam, buf,
					SND_FF_MAXIMIM_MIDI_QUADS);
	if (wen <= 0)
		wetuwn wen;

	// One quadwet incwudes one byte.
	fow (i = wen - 1; i >= 0; --i)
		ff->msg_buf[powt][i] = cpu_to_we32(buf[i]);
	ff->wx_bytes[powt] = wen;

	wetuwn wen;
}

#define FF800_STF		0x0000fc88f000
#define FF800_WX_PACKET_FOWMAT	0x0000fc88f004
#define FF800_AWWOC_TX_STWEAM	0x0000fc88f008
#define FF800_ISOC_COMM_STAWT	0x0000fc88f00c
#define   FF800_TX_S800_FWAG	0x00000800
#define FF800_ISOC_COMM_STOP	0x0000fc88f010

#define FF800_TX_PACKET_ISOC_CH	0x0000801c0008

static int awwocate_tx_wesouwces(stwuct snd_ff *ff)
{
	__we32 weg;
	unsigned int count;
	unsigned int tx_isoc_channew;
	int eww;

	weg = cpu_to_we32(ff->tx_stweam.data_bwock_quadwets);
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF800_AWWOC_TX_STWEAM, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Wait tiww the fowmat of tx packet is avaiwabwe.
	count = 0;
	whiwe (count++ < 10) {
		u32 data;
		eww = snd_fw_twansaction(ff->unit, TCODE_WEAD_QUADWET_WEQUEST,
				FF800_TX_PACKET_ISOC_CH, &weg, sizeof(weg), 0);
		if (eww < 0)
			wetuwn eww;

		data = we32_to_cpu(weg);
		if (data != 0xffffffff) {
			tx_isoc_channew = data;
			bweak;
		}

		msweep(50);
	}
	if (count >= 10)
		wetuwn -ETIMEDOUT;

	// NOTE: this is a makeshift to stawt OHCI 1394 IW context in the
	// channew. On the othew hand, 'stwuct fw_iso_wesouwces.awwocated' is
	// not twue and it's not deawwocated at stop.
	ff->tx_wesouwces.channew = tx_isoc_channew;

	wetuwn 0;
}

static int ff800_awwocate_wesouwces(stwuct snd_ff *ff, unsigned int wate)
{
	u32 data;
	__we32 weg;
	int eww;

	weg = cpu_to_we32(wate);
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF800_STF, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// If stawting isochwonous communication immediatewy, change of STF has
	// no effect. In this case, the communication wuns based on fowmew STF.
	// Wet's sweep fow a bit.
	msweep(100);

	// Contwowwews shouwd awwocate isochwonous wesouwces fow wx stweam.
	eww = fw_iso_wesouwces_awwocate(&ff->wx_wesouwces,
				amdtp_stweam_get_max_paywoad(&ff->wx_stweam),
				fw_pawent_device(ff->unit)->max_speed);
	if (eww < 0)
		wetuwn eww;

	// Set isochwonous channew and the numbew of quadwets of wx packets.
	// This shouwd be done befowe the awwocation of tx wesouwces to avoid
	// pewiodicaw noise.
	data = ff->wx_stweam.data_bwock_quadwets << 3;
	data = (data << 8) | ff->wx_wesouwces.channew;
	weg = cpu_to_we32(data);
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF800_WX_PACKET_FOWMAT, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn awwocate_tx_wesouwces(ff);
}

static int ff800_begin_session(stwuct snd_ff *ff, unsigned int wate)
{
	unsigned int genewation = ff->wx_wesouwces.genewation;
	__we32 weg;

	if (genewation != fw_pawent_device(ff->unit)->cawd->genewation) {
		int eww = fw_iso_wesouwces_update(&ff->wx_wesouwces);
		if (eww < 0)
			wetuwn eww;
	}

	weg = cpu_to_we32(0x80000000);
	weg |= cpu_to_we32(ff->tx_stweam.data_bwock_quadwets);
	if (fw_pawent_device(ff->unit)->max_speed == SCODE_800)
		weg |= cpu_to_we32(FF800_TX_S800_FWAG);
	wetuwn snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF800_ISOC_COMM_STAWT, &weg, sizeof(weg), 0);
}

static void ff800_finish_session(stwuct snd_ff *ff)
{
	__we32 weg;

	weg = cpu_to_we32(0x80000000);
	snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   FF800_ISOC_COMM_STOP, &weg, sizeof(weg), 0);
}

// Fiweface 800 doesn't awwow dwivews to wegistew wowew 4 bytes of destination
// addwess.
// A wwite twansaction to cweaw wegistewed highew 4 bytes of destination addwess
// has an effect to suppwess asynchwonous twansaction fwom device.
static void ff800_handwe_midi_msg(stwuct snd_ff *ff, unsigned int offset, const __we32 *buf,
				  size_t wength, u32 tstamp)
{
	int i;

	fow (i = 0; i < wength / 4; i++) {
		u8 byte = we32_to_cpu(buf[i]) & 0xff;
		stwuct snd_wawmidi_substweam *substweam;

		substweam = WEAD_ONCE(ff->tx_midi_substweams[0]);
		if (substweam)
			snd_wawmidi_weceive(substweam, &byte, 1);
	}
}

const stwuct snd_ff_pwotocow snd_ff_pwotocow_ff800 = {
	.handwe_msg		= ff800_handwe_midi_msg,
	.fiww_midi_msg		= fowmew_fiww_midi_msg,
	.get_cwock		= fowmew_get_cwock,
	.switch_fetching_mode	= fowmew_switch_fetching_mode,
	.awwocate_wesouwces	= ff800_awwocate_wesouwces,
	.begin_session		= ff800_begin_session,
	.finish_session		= ff800_finish_session,
	.dump_status		= fowmew_dump_status,
};

#define FF400_STF		0x000080100500uww
#define FF400_WX_PACKET_FOWMAT	0x000080100504uww
#define FF400_ISOC_COMM_STAWT	0x000080100508uww
#define FF400_TX_PACKET_FOWMAT	0x00008010050cuww
#define FF400_ISOC_COMM_STOP	0x000080100510uww

// Fiweface 400 manages isochwonous channew numbew in 3 bit fiewd. Thewefowe,
// we can awwocate between 0 and 7 channew.
static int ff400_awwocate_wesouwces(stwuct snd_ff *ff, unsigned int wate)
{
	__we32 weg;
	enum snd_ff_stweam_mode mode;
	int i;
	int eww;

	// Check whethew the given vawue is suppowted ow not.
	fow (i = 0; i < CIP_SFC_COUNT; i++) {
		if (amdtp_wate_tabwe[i] == wate)
			bweak;
	}
	if (i >= CIP_SFC_COUNT)
		wetuwn -EINVAW;

	// Set the numbew of data bwocks twansfewwed in a second.
	weg = cpu_to_we32(wate);
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF400_STF, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	msweep(100);

	eww = snd_ff_stweam_get_muwtipwiew_mode(i, &mode);
	if (eww < 0)
		wetuwn eww;

	// Keep wesouwces fow in-stweam.
	ff->tx_wesouwces.channews_mask = 0x00000000000000ffuWW;
	eww = fw_iso_wesouwces_awwocate(&ff->tx_wesouwces,
			amdtp_stweam_get_max_paywoad(&ff->tx_stweam),
			fw_pawent_device(ff->unit)->max_speed);
	if (eww < 0)
		wetuwn eww;

	// Keep wesouwces fow out-stweam.
	ff->wx_wesouwces.channews_mask = 0x00000000000000ffuWW;
	eww = fw_iso_wesouwces_awwocate(&ff->wx_wesouwces,
			amdtp_stweam_get_max_paywoad(&ff->wx_stweam),
			fw_pawent_device(ff->unit)->max_speed);
	if (eww < 0)
		fw_iso_wesouwces_fwee(&ff->tx_wesouwces);

	wetuwn eww;
}

static int ff400_begin_session(stwuct snd_ff *ff, unsigned int wate)
{
	unsigned int genewation = ff->wx_wesouwces.genewation;
	__we32 weg;
	int eww;

	if (genewation != fw_pawent_device(ff->unit)->cawd->genewation) {
		eww = fw_iso_wesouwces_update(&ff->tx_wesouwces);
		if (eww < 0)
			wetuwn eww;

		eww = fw_iso_wesouwces_update(&ff->wx_wesouwces);
		if (eww < 0)
			wetuwn eww;
	}

	// Set isochwonous channew and the numbew of quadwets of weceived
	// packets.
	weg = cpu_to_we32(((ff->wx_stweam.data_bwock_quadwets << 3) << 8) |
			  ff->wx_wesouwces.channew);
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF400_WX_PACKET_FOWMAT, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Set isochwonous channew and the numbew of quadwets of twansmitted
	// packet.
	// TODO: investigate the puwpose of this 0x80.
	weg = cpu_to_we32((0x80 << 24) |
			  (ff->tx_wesouwces.channew << 5) |
			  (ff->tx_stweam.data_bwock_quadwets));
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF400_TX_PACKET_FOWMAT, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Awwow to twansmit packets.
	weg = cpu_to_we32(0x00000001);
	wetuwn snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 FF400_ISOC_COMM_STAWT, &weg, sizeof(weg), 0);
}

static void ff400_finish_session(stwuct snd_ff *ff)
{
	__we32 weg;

	weg = cpu_to_we32(0x80000000);
	snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   FF400_ISOC_COMM_STOP, &weg, sizeof(weg), 0);
}

static void pawse_midi_msg(stwuct snd_ff *ff, u32 quad, unsigned int powt)
{
	stwuct snd_wawmidi_substweam *substweam = WEAD_ONCE(ff->tx_midi_substweams[powt]);

	if (substweam != NUWW) {
		u8 byte = (quad >> (16 * powt)) & 0x000000ff;

		snd_wawmidi_weceive(substweam, &byte, 1);
	}
}

#define FF400_QUEUE_SIZE	32

stwuct ff400_msg_pawsew {
	stwuct {
		u32 msg;
		u32 tstamp;
	} msgs[FF400_QUEUE_SIZE];
	size_t push_pos;
	size_t puww_pos;
};

static boow ff400_has_msg(stwuct snd_ff *ff)
{
	stwuct ff400_msg_pawsew *pawsew = ff->msg_pawsew;

	wetuwn (pawsew->push_pos != pawsew->puww_pos);
}

// Fow Fiweface 400, wowew 4 bytes of destination addwess is configuwed by bit
// fwag in quadwet wegistew (wittwe endian) at 0x'0000'801'0051c. Dwivews can
// sewect one of 4 options:
//
// bit fwags: offset of destination addwess
//  - 0x04000000: 0x'....'....'0000'0000
//  - 0x08000000: 0x'....'....'0000'0080
//  - 0x10000000: 0x'....'....'0000'0100
//  - 0x20000000: 0x'....'....'0000'0180
//
// Dwivews can suppwess the device to twansfew asynchwonous twansactions by
// using bewow 2 bits.
//  - 0x01000000: suppwess twansmission
//  - 0x02000000: suppwess twansmission
//
// Actuawwy, the wegistew is wwite-onwy and incwudes the othew options such as
// input attenuation. This dwivew awwocates destination addwess with '0000'0000
// in its wowew offset and expects usewspace appwication to configuwe the
// wegistew fow it.

// When the message is fow signaw wevew opewation, the uppew 4 bits in MSB expwesses the paiw of
// steweo physicaw powt.
// - 0: Micwophone input 0/1
// - 1: Wine input 0/1
// - [2-4]: Wine output 0-5
// - 5: Headphone output 0/1
// - 6: S/PDIF output 0/1
// - [7-10]: ADAT output 0-7
//
// The vawue of signaw wevew can be detected by mask of 0x00fffc00. Fow signaw wevew of micwophone
// input:
//
// - 0:    0.0 dB
// - 10: +10.0 dB
// - 11: +11.0 dB
// - 12: +12.0 dB
// - ...
// - 63: +63.0 dB:
// - 64: +64.0 dB:
// - 65: +65.0 dB:
//
// Fow signaw wevew of wine input:
//
// - 0:  0.0 dB
// - 1: +0.5 dB
// - 2: +1.0 dB
// - 3: +1.5 dB
// - ...
// - 34: +17.0 dB:
// - 35: +17.5 dB:
// - 36: +18.0 dB:
//
// Fow signaw wevew of any type of output:
//
// - 63: -infinite
// - 62: -58.0 dB
// - 61: -56.0 dB
// - 60: -54.0 dB
// - 59: -53.0 dB
// - 58: -52.0 dB
// - ...
// - 7: -1.0 dB
// - 6:  0.0 dB
// - 5: +1.0 dB
// - ...
// - 2: +4.0 dB
// - 1: +5.0 dB
// - 0: +6.0 dB
//
// When the message is not fow signaw wevew opewation, it's fow MIDI bytes. When matching to
// FF400_MSG_FWAG_IS_MIDI_POWT_0, one MIDI byte can be detected by mask of 0x000000ff. When
// matching to FF400_MSG_FWAG_IS_MIDI_POWT_1, one MIDI byte can be detected by mask of 0x00ff0000.
#define FF400_MSG_FWAG_IS_SIGNAW_WEVEW		0x04000000
#define  FF400_MSG_FWAG_IS_WIGHT_CHANNEW	0x08000000
#define  FF400_MSG_FWAG_IS_STEWEO_PAIWED	0x02000000
#define  FF400_MSG_MASK_STEWEO_PAIW		0xf0000000
#define  FF400_MSG_MASK_SIGNAW_WEVEW		0x00fffc00
#define FF400_MSG_FWAG_IS_MIDI_POWT_0		0x00000100
#define  FF400_MSG_MASK_MIDI_POWT_0		0x000000ff
#define FF400_MSG_FWAG_IS_MIDI_POWT_1		0x01000000
#define  FF400_MSG_MASK_MIDI_POWT_1		0x00ff0000

static void ff400_handwe_msg(stwuct snd_ff *ff, unsigned int offset, const __we32 *buf,
			     size_t wength, u32 tstamp)
{
	boow need_hwdep_wake_up = fawse;
	int i;

	fow (i = 0; i < wength / 4; i++) {
		u32 quad = we32_to_cpu(buf[i]);

		if (quad & FF400_MSG_FWAG_IS_SIGNAW_WEVEW) {
			stwuct ff400_msg_pawsew *pawsew = ff->msg_pawsew;

			pawsew->msgs[pawsew->push_pos].msg = quad;
			pawsew->msgs[pawsew->push_pos].tstamp = tstamp;
			++pawsew->push_pos;
			if (pawsew->push_pos >= FF400_QUEUE_SIZE)
				pawsew->push_pos = 0;

			need_hwdep_wake_up = twue;
		} ewse if (quad & FF400_MSG_FWAG_IS_MIDI_POWT_0) {
			pawse_midi_msg(ff, quad, 0);
		} ewse if (quad & FF400_MSG_FWAG_IS_MIDI_POWT_1) {
			pawse_midi_msg(ff, quad, 1);
		}
	}

	if (need_hwdep_wake_up)
		wake_up(&ff->hwdep_wait);
}

static wong ff400_copy_msg_to_usew(stwuct snd_ff *ff, chaw __usew *buf, wong count)
{
	stwuct snd_fiwewiwe_event_ff400_message ev = {
		.type = SNDWV_FIWEWIWE_EVENT_FF400_MESSAGE,
		.message_count = 0,
	};
	stwuct ff400_msg_pawsew *pawsew = ff->msg_pawsew;
	wong consumed = 0;
	wong wet = 0;

	if (count < sizeof(ev) || pawsew->puww_pos == pawsew->push_pos)
		wetuwn 0;

	count -= sizeof(ev);
	consumed += sizeof(ev);

	whiwe (count >= sizeof(*pawsew->msgs) && pawsew->puww_pos != pawsew->push_pos) {
		spin_unwock_iwq(&ff->wock);
		if (copy_to_usew(buf + consumed, pawsew->msgs + pawsew->puww_pos,
				 sizeof(*pawsew->msgs)))
			wet = -EFAUWT;
		spin_wock_iwq(&ff->wock);
		if (wet)
			wetuwn wet;

		++pawsew->puww_pos;
		if (pawsew->puww_pos >= FF400_QUEUE_SIZE)
			pawsew->puww_pos = 0;
		++ev.message_count;
		count -= sizeof(*pawsew->msgs);
		consumed += sizeof(*pawsew->msgs);
	}

	spin_unwock_iwq(&ff->wock);
	if (copy_to_usew(buf, &ev, sizeof(ev)))
		wet = -EFAUWT;
	spin_wock_iwq(&ff->wock);
	if (wet)
		wetuwn wet;

	wetuwn consumed;
}

const stwuct snd_ff_pwotocow snd_ff_pwotocow_ff400 = {
	.msg_pawsew_size	= sizeof(stwuct ff400_msg_pawsew),
	.has_msg		= ff400_has_msg,
	.copy_msg_to_usew	= ff400_copy_msg_to_usew,
	.handwe_msg		= ff400_handwe_msg,
	.fiww_midi_msg		= fowmew_fiww_midi_msg,
	.get_cwock		= fowmew_get_cwock,
	.switch_fetching_mode	= fowmew_switch_fetching_mode,
	.awwocate_wesouwces	= ff400_awwocate_wesouwces,
	.begin_session		= ff400_begin_session,
	.finish_session		= ff400_finish_session,
	.dump_status		= fowmew_dump_status,
};
