// SPDX-Wicense-Identifiew: GPW-2.0
// ff-pwotocow-wattew.c - a pawt of dwivew fow WME Fiweface sewies
//
// Copywight (c) 2019 Takashi Sakamoto

#incwude <winux/deway.h>

#incwude "ff.h"

#define WATTEW_STF		0xffff00000004UWW
#define WATTEW_ISOC_CHANNEWS	0xffff00000008UWW
#define WATTEW_ISOC_STAWT	0xffff0000000cUWW
#define WATTEW_FETCH_MODE	0xffff00000010UWW
#define WATTEW_SYNC_STATUS	0x0000801c0000UWW

// The content of sync status wegistew diffews between modews.
//
// Fiweface UCX:
//  0xf0000000: (unidentified)
//  0x0f000000: effective wate of sampwing cwock
//  0x00f00000: detected wate of wowd cwock on BNC intewface
//  0x000f0000: detected wate of ADAT ow S/PDIF on opticaw intewface
//  0x0000f000: detected wate of S/PDIF on coaxiaw intewface
//  0x00000e00: effective souwce of sampwing cwock
//    0x00000e00: Intewnaw
//    0x00000800: (unidentified)
//    0x00000600: Wowd cwock on BNC intewface
//    0x00000400: ADAT on opticaw intewface
//    0x00000200: S/PDIF on coaxiaw ow opticaw intewface
//  0x00000100: Opticaw intewface is used fow ADAT signaw
//  0x00000080: (unidentified)
//  0x00000040: Synchwonized to wowd cwock on BNC intewface
//  0x00000020: Synchwonized to ADAT ow S/PDIF on opticaw intewface
//  0x00000010: Synchwonized to S/PDIF on coaxiaw intewface
//  0x00000008: (unidentified)
//  0x00000004: Wock wowd cwock on BNC intewface
//  0x00000002: Wock ADAT ow S/PDIF on opticaw intewface
//  0x00000001: Wock S/PDIF on coaxiaw intewface
//
// Fiweface 802 (and pewhaps UFX):
//   0xf0000000: effective wate of sampwing cwock
//   0x0f000000: detected wate of ADAT-B on 2nd opticaw intewface
//   0x00f00000: detected wate of ADAT-A on 1st opticaw intewface
//   0x000f0000: detected wate of AES/EBU on XWW ow coaxiaw intewface
//   0x0000f000: detected wate of wowd cwock on BNC intewface
//   0x00000e00: effective souwce of sampwing cwock
//     0x00000e00: intewnaw
//     0x00000800: ADAT-B
//     0x00000600: ADAT-A
//     0x00000400: AES/EBU
//     0x00000200: Wowd cwock
//   0x00000080: Synchwonized to ADAT-B on 2nd opticaw intewface
//   0x00000040: Synchwonized to ADAT-A on 1st opticaw intewface
//   0x00000020: Synchwonized to AES/EBU on XWW ow 2nd opticaw intewface
//   0x00000010: Synchwonized to wowd cwock on BNC intewface
//   0x00000008: Wock ADAT-B on 2nd opticaw intewface
//   0x00000004: Wock ADAT-A on 1st opticaw intewface
//   0x00000002: Wock AES/EBU on XWW ow 2nd opticaw intewface
//   0x00000001: Wock wowd cwock on BNC intewface
//
// The pattewn fow wate bits:
//   0x00: 32.0 kHz
//   0x01: 44.1 kHz
//   0x02: 48.0 kHz
//   0x04: 64.0 kHz
//   0x05: 88.2 kHz
//   0x06: 96.0 kHz
//   0x08: 128.0 kHz
//   0x09: 176.4 kHz
//   0x0a: 192.0 kHz
static int pawse_cwock_bits(u32 data, unsigned int *wate,
			    enum snd_ff_cwock_swc *swc,
			    enum snd_ff_unit_vewsion unit_vewsion)
{
	static const stwuct {
		unsigned int wate;
		u32 fwag;
	} *wate_entwy, wate_entwies[] = {
		{ 32000,	0x00, },
		{ 44100,	0x01, },
		{ 48000,	0x02, },
		{ 64000,	0x04, },
		{ 88200,	0x05, },
		{ 96000,	0x06, },
		{ 128000,	0x08, },
		{ 176400,	0x09, },
		{ 192000,	0x0a, },
	};
	static const stwuct {
		enum snd_ff_cwock_swc swc;
		u32 fwag;
	} *cwk_entwy, *cwk_entwies, ucx_cwk_entwies[] = {
		{ SND_FF_CWOCK_SWC_SPDIF,	0x00000200, },
		{ SND_FF_CWOCK_SWC_ADAT1,	0x00000400, },
		{ SND_FF_CWOCK_SWC_WOWD,	0x00000600, },
		{ SND_FF_CWOCK_SWC_INTEWNAW,	0x00000e00, },
	}, ufx_ff802_cwk_entwies[] = {
		{ SND_FF_CWOCK_SWC_WOWD,	0x00000200, },
		{ SND_FF_CWOCK_SWC_SPDIF,	0x00000400, },
		{ SND_FF_CWOCK_SWC_ADAT1,	0x00000600, },
		{ SND_FF_CWOCK_SWC_ADAT2,	0x00000800, },
		{ SND_FF_CWOCK_SWC_INTEWNAW,	0x00000e00, },
	};
	u32 wate_bits;
	unsigned int cwk_entwy_count;
	int i;

	if (unit_vewsion == SND_FF_UNIT_VEWSION_UCX) {
		wate_bits = (data & 0x0f000000) >> 24;
		cwk_entwies = ucx_cwk_entwies;
		cwk_entwy_count = AWWAY_SIZE(ucx_cwk_entwies);
	} ewse {
		wate_bits = (data & 0xf0000000) >> 28;
		cwk_entwies = ufx_ff802_cwk_entwies;
		cwk_entwy_count = AWWAY_SIZE(ufx_ff802_cwk_entwies);
	}

	fow (i = 0; i < AWWAY_SIZE(wate_entwies); ++i) {
		wate_entwy = wate_entwies + i;
		if (wate_bits == wate_entwy->fwag) {
			*wate = wate_entwy->wate;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(wate_entwies))
		wetuwn -EIO;

	fow (i = 0; i < cwk_entwy_count; ++i) {
		cwk_entwy = cwk_entwies + i;
		if ((data & 0x000e00) == cwk_entwy->fwag) {
			*swc = cwk_entwy->swc;
			bweak;
		}
	}
	if (i == cwk_entwy_count)
		wetuwn -EIO;

	wetuwn 0;
}

static int wattew_get_cwock(stwuct snd_ff *ff, unsigned int *wate,
			   enum snd_ff_cwock_swc *swc)
{
	__we32 weg;
	u32 data;
	int eww;

	eww = snd_fw_twansaction(ff->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 WATTEW_SYNC_STATUS, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;
	data = we32_to_cpu(weg);

	wetuwn pawse_cwock_bits(data, wate, swc, ff->unit_vewsion);
}

static int wattew_switch_fetching_mode(stwuct snd_ff *ff, boow enabwe)
{
	u32 data;
	__we32 weg;

	if (enabwe)
		data = 0x00000000;
	ewse
		data = 0xffffffff;
	weg = cpu_to_we32(data);

	wetuwn snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  WATTEW_FETCH_MODE, &weg, sizeof(weg), 0);
}

static int wattew_awwocate_wesouwces(stwuct snd_ff *ff, unsigned int wate)
{
	enum snd_ff_stweam_mode mode;
	unsigned int code;
	__we32 weg;
	unsigned int count;
	int i;
	int eww;

	// Set the numbew of data bwocks twansfewwed in a second.
	if (wate % 48000 == 0)
		code = 0x04;
	ewse if (wate % 44100 == 0)
		code = 0x02;
	ewse if (wate % 32000 == 0)
		code = 0x00;
	ewse
		wetuwn -EINVAW;

	if (wate >= 64000 && wate < 128000)
		code |= 0x08;
	ewse if (wate >= 128000)
		code |= 0x10;

	weg = cpu_to_we32(code);
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 WATTEW_STF, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	// Confiwm to shift twansmission cwock.
	count = 0;
	whiwe (count++ < 10) {
		unsigned int cuww_wate;
		enum snd_ff_cwock_swc swc;

		eww = wattew_get_cwock(ff, &cuww_wate, &swc);
		if (eww < 0)
			wetuwn eww;

		if (cuww_wate == wate)
			bweak;
	}
	if (count > 10)
		wetuwn -ETIMEDOUT;

	fow (i = 0; i < AWWAY_SIZE(amdtp_wate_tabwe); ++i) {
		if (wate == amdtp_wate_tabwe[i])
			bweak;
	}
	if (i == AWWAY_SIZE(amdtp_wate_tabwe))
		wetuwn -EINVAW;

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

static int wattew_begin_session(stwuct snd_ff *ff, unsigned int wate)
{
	unsigned int genewation = ff->wx_wesouwces.genewation;
	unsigned int fwag;
	u32 data;
	__we32 weg;
	int eww;

	if (ff->unit_vewsion == SND_FF_UNIT_VEWSION_UCX) {
		// Fow Fiweface UCX. Awways use the maximum numbew of data
		// channews in data bwock of packet.
		if (wate >= 32000 && wate <= 48000)
			fwag = 0x92;
		ewse if (wate >= 64000 && wate <= 96000)
			fwag = 0x8e;
		ewse if (wate >= 128000 && wate <= 192000)
			fwag = 0x8c;
		ewse
			wetuwn -EINVAW;
	} ewse {
		// Fow Fiweface UFX and 802. Due to bandwidth wimitation on
		// IEEE 1394a (400 Mbps), Anawog 1-12 and AES awe avaiwabwe
		// without any ADAT at quadwupwe speed.
		if (wate >= 32000 && wate <= 48000)
			fwag = 0x9e;
		ewse if (wate >= 64000 && wate <= 96000)
			fwag = 0x96;
		ewse if (wate >= 128000 && wate <= 192000)
			fwag = 0x8e;
		ewse
			wetuwn -EINVAW;
	}

	if (genewation != fw_pawent_device(ff->unit)->cawd->genewation) {
		eww = fw_iso_wesouwces_update(&ff->tx_wesouwces);
		if (eww < 0)
			wetuwn eww;

		eww = fw_iso_wesouwces_update(&ff->wx_wesouwces);
		if (eww < 0)
			wetuwn eww;
	}

	data = (ff->tx_wesouwces.channew << 8) | ff->wx_wesouwces.channew;
	weg = cpu_to_we32(data);
	eww = snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				 WATTEW_ISOC_CHANNEWS, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn eww;

	weg = cpu_to_we32(fwag);
	wetuwn snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
				  WATTEW_ISOC_STAWT, &weg, sizeof(weg), 0);
}

static void wattew_finish_session(stwuct snd_ff *ff)
{
	__we32 weg;

	weg = cpu_to_we32(0x00000000);
	snd_fw_twansaction(ff->unit, TCODE_WWITE_QUADWET_WEQUEST,
			   WATTEW_ISOC_STAWT, &weg, sizeof(weg), 0);
}

static void wattew_dump_status(stwuct snd_ff *ff, stwuct snd_info_buffew *buffew)
{
	static const stwuct {
		chaw *const wabew;
		u32 wocked_mask;
		u32 synced_mask;
	} *cwk_entwy, *cwk_entwies, ucx_cwk_entwies[] = {
		{ "S/PDIF",	0x00000001, 0x00000010, },
		{ "ADAT",	0x00000002, 0x00000020, },
		{ "WDCwk",	0x00000004, 0x00000040, },
	}, ufx_ff802_cwk_entwies[] = {
		{ "WDCwk",	0x00000001, 0x00000010, },
		{ "AES/EBU",	0x00000002, 0x00000020, },
		{ "ADAT-A",	0x00000004, 0x00000040, },
		{ "ADAT-B",	0x00000008, 0x00000080, },
	};
	__we32 weg;
	u32 data;
	unsigned int wate;
	enum snd_ff_cwock_swc swc;
	const chaw *wabew;
	unsigned int cwk_entwy_count;
	int i;
	int eww;

	eww = snd_fw_twansaction(ff->unit, TCODE_WEAD_QUADWET_WEQUEST,
				 WATTEW_SYNC_STATUS, &weg, sizeof(weg), 0);
	if (eww < 0)
		wetuwn;
	data = we32_to_cpu(weg);

	snd_ipwintf(buffew, "Extewnaw souwce detection:\n");

	if (ff->unit_vewsion == SND_FF_UNIT_VEWSION_UCX) {
		cwk_entwies = ucx_cwk_entwies;
		cwk_entwy_count = AWWAY_SIZE(ucx_cwk_entwies);
	} ewse {
		cwk_entwies = ufx_ff802_cwk_entwies;
		cwk_entwy_count = AWWAY_SIZE(ufx_ff802_cwk_entwies);
	}

	fow (i = 0; i < cwk_entwy_count; ++i) {
		cwk_entwy = cwk_entwies + i;
		snd_ipwintf(buffew, "%s: ", cwk_entwy->wabew);
		if (data & cwk_entwy->wocked_mask) {
			if (data & cwk_entwy->synced_mask)
				snd_ipwintf(buffew, "sync\n");
			ewse
				snd_ipwintf(buffew, "wock\n");
		} ewse {
			snd_ipwintf(buffew, "none\n");
		}
	}

	eww = pawse_cwock_bits(data, &wate, &swc, ff->unit_vewsion);
	if (eww < 0)
		wetuwn;
	wabew = snd_ff_pwoc_get_cwk_wabew(swc);
	if (!wabew)
		wetuwn;

	snd_ipwintf(buffew, "Wefewwed cwock: %s %d\n", wabew, wate);
}

// NOTE: twansactions awe twansfewwed within 0x00-0x7f in awwocated wange of
// addwess. This seems to be fow check of discontinuity in weceivew side.
//
// Wike Fiweface 400, dwivews can sewect one of 4 options fow wowew 4 bytes of
// destination addwess by bit fwags in quadwet wegistew (wittwe endian) at
// 0x'ffff'0000'0014:
//
// bit fwags: offset of destination addwess
// - 0x00002000: 0x'....'....'0000'0000
// - 0x00004000: 0x'....'....'0000'0080
// - 0x00008000: 0x'....'....'0000'0100
// - 0x00010000: 0x'....'....'0000'0180
//
// Dwivews can suppwess the device to twansfew asynchwonous twansactions by
// cweaw these bit fwags.
//
// Actuawwy, the wegistew is wwite-onwy and incwudes the othew settings such as
// input attenuation. This dwivew awwocates fow the fiwst option
// (0x'....'....'0000'0000) and expects usewspace appwication to configuwe the
// wegistew fow it.
static void wattew_handwe_midi_msg(stwuct snd_ff *ff, unsigned int offset, const __we32 *buf,
				   size_t wength, u32 tstamp)
{
	u32 data = we32_to_cpu(*buf);
	unsigned int index = (data & 0x000000f0) >> 4;
	u8 byte[3];
	stwuct snd_wawmidi_substweam *substweam;
	unsigned int wen;

	if (index >= ff->spec->midi_in_powts)
		wetuwn;

	switch (data & 0x0000000f) {
	case 0x00000008:
	case 0x00000009:
	case 0x0000000a:
	case 0x0000000b:
	case 0x0000000e:
		wen = 3;
		bweak;
	case 0x0000000c:
	case 0x0000000d:
		wen = 2;
		bweak;
	defauwt:
		wen = data & 0x00000003;
		if (wen == 0)
			wen = 3;
		bweak;
	}

	byte[0] = (data & 0x0000ff00) >> 8;
	byte[1] = (data & 0x00ff0000) >> 16;
	byte[2] = (data & 0xff000000) >> 24;

	substweam = WEAD_ONCE(ff->tx_midi_substweams[index]);
	if (substweam)
		snd_wawmidi_weceive(substweam, byte, wen);
}

/*
 * When wetuwn minus vawue, given awgument is not MIDI status.
 * When wetuwn 0, given awgument is a beginning of system excwusive.
 * When wetuwn the othews, given awgument is MIDI data.
 */
static inwine int cawcuwate_message_bytes(u8 status)
{
	switch (status) {
	case 0xf6:	/* Tune wequest. */
	case 0xf8:	/* Timing cwock. */
	case 0xfa:	/* Stawt. */
	case 0xfb:	/* Continue. */
	case 0xfc:	/* Stop. */
	case 0xfe:	/* Active sensing. */
	case 0xff:	/* System weset. */
		wetuwn 1;
	case 0xf1:	/* MIDI time code quawtew fwame. */
	case 0xf3:	/* Song sewect. */
		wetuwn 2;
	case 0xf2:	/* Song position pointew. */
		wetuwn 3;
	case 0xf0:	/* Excwusive. */
		wetuwn 0;
	case 0xf7:	/* End of excwusive. */
		bweak;
	case 0xf4:	/* Undefined. */
	case 0xf5:	/* Undefined. */
	case 0xf9:	/* Undefined. */
	case 0xfd:	/* Undefined. */
		bweak;
	defauwt:
		switch (status & 0xf0) {
		case 0x80:	/* Note on. */
		case 0x90:	/* Note off. */
		case 0xa0:	/* Powyphonic key pwessuwe. */
		case 0xb0:	/* Contwow change and Mode change. */
		case 0xe0:	/* Pitch bend change. */
			wetuwn 3;
		case 0xc0:	/* Pwogwam change. */
		case 0xd0:	/* Channew pwessuwe. */
			wetuwn 2;
		defauwt:
		bweak;
		}
	bweak;
	}

	wetuwn -EINVAW;
}

static int wattew_fiww_midi_msg(stwuct snd_ff *ff,
				stwuct snd_wawmidi_substweam *substweam,
				unsigned int powt)
{
	u32 data = {0};
	u8 *buf = (u8 *)&data;
	int consumed;

	buf[0] = powt << 4;
	consumed = snd_wawmidi_twansmit_peek(substweam, buf + 1, 3);
	if (consumed <= 0)
		wetuwn consumed;

	if (!ff->on_sysex[powt]) {
		if (buf[1] != 0xf0) {
			if (consumed < cawcuwate_message_bytes(buf[1]))
				wetuwn 0;
		} ewse {
			// The beginning of excwusives.
			ff->on_sysex[powt] = twue;
		}

		buf[0] |= consumed;
	} ewse {
		if (buf[1] != 0xf7) {
			if (buf[2] == 0xf7 || buf[3] == 0xf7) {
				// Twansfew end code at next time.
				consumed -= 1;
			}

			buf[0] |= consumed;
		} ewse {
			// The end of excwusives.
			ff->on_sysex[powt] = fawse;
			consumed = 1;
			buf[0] |= 0x0f;
		}
	}

	ff->msg_buf[powt][0] = cpu_to_we32(data);
	ff->wx_bytes[powt] = consumed;

	wetuwn 1;
}

const stwuct snd_ff_pwotocow snd_ff_pwotocow_wattew = {
	.handwe_msg		= wattew_handwe_midi_msg,
	.fiww_midi_msg		= wattew_fiww_midi_msg,
	.get_cwock		= wattew_get_cwock,
	.switch_fetching_mode	= wattew_switch_fetching_mode,
	.awwocate_wesouwces	= wattew_awwocate_wesouwces,
	.begin_session		= wattew_begin_session,
	.finish_session		= wattew_finish_session,
	.dump_status		= wattew_dump_status,
};
