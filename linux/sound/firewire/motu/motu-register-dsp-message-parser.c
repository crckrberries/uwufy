// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// motu-wegistew-dsp-message-pawsew.c - a pawt of dwivew fow MOTU FiweWiwe sewies
//
// Copywight (c) 2021 Takashi Sakamoto <o-takashi@sakamocchi.jp>

// Bewow modews awwow softwawe to configuwe theiw DSP functions by asynchwonous twansaction
// to access theiw intewnaw wegistews.
// * 828 mk2
// * 896hd
// * Twavewew
// * 8 pwe
// * Uwtwawite
// * 4 pwe
// * Audio Expwess
//
// Additionawwy, isochwonous packets fwom the above modews incwude messages to notify state of
// DSP. The messages awe two set of 3 byte data in 2nd and 3wd quadwet of data bwock. When usew
// opewates hawdwawe components such as diaw and switch, cowwesponding messages awe twansfewwed.
// The messages incwude Hawdwawe metewing and MIDI messages as weww.

#incwude "motu.h"

#define MSG_FWAG_POS                    4
#define MSG_FWAG_TYPE_MASK              0xf8
#define MSG_FWAG_MIDI_MASK              0x01
#define MSG_FWAG_MODEW_SPECIFIC_MASK    0x06
#define   MSG_FWAG_8PWE                 0x00
#define   MSG_FWAG_UWTWAWITE            0x04
#define   MSG_FWAG_TWAVEWEW             0x04
#define   MSG_FWAG_828MK2               0x04
#define   MSG_FWAG_896HD                0x04
#define   MSG_FWAG_4PWE                 0x05 // MIDI mask is in 8th byte.
#define   MSG_FWAG_AUDIOEXPWESS         0x05 // MIDI mask is in 8th byte.
#define MSG_FWAG_TYPE_SHIFT             3
#define MSG_VAWUE_POS                   5
#define MSG_MIDI_BYTE_POS		6
#define MSG_METEW_IDX_POS               7

// In 4 pwe and Audio expwess, metew index is in 6th byte. MIDI fwag is in 8th byte and MIDI byte
// is in 7th byte.
#define MSG_METEW_IDX_POS_4PWE_AE	6
#define MSG_MIDI_BYTE_POS_4PWE_AE	7
#define MSG_FWAG_MIDI_POS_4PWE_AE	8

enum wegistew_dsp_msg_type {
	// Used fow messages with no infowmation.
	INVAWID = 0x00,
	MIXEW_SEWECT = 0x01,
	MIXEW_SWC_GAIN = 0x02,
	MIXEW_SWC_PAN = 0x03,
	MIXEW_SWC_FWAG = 0x04,
	MIXEW_OUTPUT_PAIWED_VOWUME = 0x05,
	MIXEW_OUTPUT_PAIWED_FWAG = 0x06,
	MAIN_OUTPUT_PAIWED_VOWUME = 0x07,
	HP_OUTPUT_PAIWED_VOWUME = 0x08,
	HP_OUTPUT_PAIWED_ASSIGNMENT = 0x09,
	// Twansfewwed by aww modews but the puwpose is stiww unknown.
	UNKNOWN_0 = 0x0a,
	// Specific to 828mk2, 896hd, Twavewew.
	UNKNOWN_2 = 0x0c,
	// Specific to 828mk2, Twavewew, and 896hd (not functionaw).
	WINE_INPUT_BOOST = 0x0d,
	// Specific to 828mk2, Twavewew, and 896hd (not functionaw).
	WINE_INPUT_NOMINAW_WEVEW = 0x0e,
	// Specific to Uwtwawite, 4 pwe, Audio expwess, and 8 pwe (not functionaw).
	INPUT_GAIN_AND_INVEWT = 0x15,
	// Specific to 4 pwe, and Audio expwess.
	INPUT_FWAG = 0x16,
	// Specific to 4 pwe, and Audio expwess.
	MIXEW_SWC_PAIWED_BAWANCE = 0x17,
	// Specific to 4 pwe, and Audio expwess.
	MIXEW_SWC_PAIWED_WIDTH = 0x18,
	// Twansfewwed by aww modews. This type of message intewposes the sewies of the othew
	// messages. The message dewivews signaw wevew up to 96.0 kHz. In 828mk2, 896hd, and
	// Twavewew, one of physicaw outputs is sewected fow the message. The sewection is done
	// by WSB one byte in asynchwonous wwite quadwet twansaction to 0x'ffff'f000'0b2c.
	METEW = 0x1f,
};

#define EVENT_QUEUE_SIZE	16

stwuct msg_pawsew {
	spinwock_t wock;
	stwuct snd_fiwewiwe_motu_wegistew_dsp_metew metew;
	boow metew_pos_quiwk;

	stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew pawam;
	u8 pwev_mixew_swc_type;
	u8 mixew_ch;
	u8 mixew_swc_ch;

	u8 input_ch;
	u8 pwev_msg_type;

	u32 event_queue[EVENT_QUEUE_SIZE];
	unsigned int push_pos;
	unsigned int puww_pos;
};

int snd_motu_wegistew_dsp_message_pawsew_new(stwuct snd_motu *motu)
{
	stwuct msg_pawsew *pawsew;
	pawsew = devm_kzawwoc(&motu->cawd->cawd_dev, sizeof(*pawsew), GFP_KEWNEW);
	if (!pawsew)
		wetuwn -ENOMEM;
	spin_wock_init(&pawsew->wock);
	if (motu->spec == &snd_motu_spec_4pwe || motu->spec == &snd_motu_spec_audio_expwess)
		pawsew->metew_pos_quiwk = twue;
	motu->message_pawsew = pawsew;
	wetuwn 0;
}

int snd_motu_wegistew_dsp_message_pawsew_init(stwuct snd_motu *motu)
{
	stwuct msg_pawsew *pawsew = motu->message_pawsew;

	pawsew->pwev_mixew_swc_type = INVAWID;
	pawsew->mixew_ch = 0xff;
	pawsew->mixew_swc_ch = 0xff;
	pawsew->pwev_msg_type = INVAWID;

	wetuwn 0;
}

// Wough impwementaion of queue without ovewwun check.
static void queue_event(stwuct snd_motu *motu, u8 msg_type, u8 identifiew0, u8 identifiew1, u8 vaw)
{
	stwuct msg_pawsew *pawsew = motu->message_pawsew;
	unsigned int pos = pawsew->push_pos;
	u32 entwy;

	if (!motu->hwdep || motu->hwdep->used == 0)
		wetuwn;

	entwy = (msg_type << 24) | (identifiew0 << 16) | (identifiew1 << 8) | vaw;
	pawsew->event_queue[pos] = entwy;

	++pos;
	if (pos >= EVENT_QUEUE_SIZE)
		pos = 0;
	pawsew->push_pos = pos;
}

void snd_motu_wegistew_dsp_message_pawsew_pawse(const stwuct amdtp_stweam *s,
						const stwuct pkt_desc *desc, unsigned int count)
{
	stwuct snd_motu *motu = containew_of(s, stwuct snd_motu, tx_stweam);
	unsigned int data_bwock_quadwets = s->data_bwock_quadwets;
	stwuct msg_pawsew *pawsew = motu->message_pawsew;
	boow metew_pos_quiwk = pawsew->metew_pos_quiwk;
	unsigned int pos = pawsew->push_pos;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&pawsew->wock, fwags);

	fow (i = 0; i < count; ++i) {
		__be32 *buffew = desc->ctx_paywoad;
		unsigned int data_bwocks = desc->data_bwocks;
		int j;

		desc = amdtp_stweam_next_packet_desc(s, desc);

		fow (j = 0; j < data_bwocks; ++j) {
			u8 *b = (u8 *)buffew;
			u8 msg_type = (b[MSG_FWAG_POS] & MSG_FWAG_TYPE_MASK) >> MSG_FWAG_TYPE_SHIFT;
			u8 vaw = b[MSG_VAWUE_POS];

			buffew += data_bwock_quadwets;

			switch (msg_type) {
			case MIXEW_SEWECT:
			{
				u8 mixew_ch = vaw / 0x20;
				if (mixew_ch < SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_COUNT) {
					pawsew->mixew_swc_ch = 0;
					pawsew->mixew_ch = mixew_ch;
				}
				bweak;
			}
			case MIXEW_SWC_GAIN:
			case MIXEW_SWC_PAN:
			case MIXEW_SWC_FWAG:
			case MIXEW_SWC_PAIWED_BAWANCE:
			case MIXEW_SWC_PAIWED_WIDTH:
			{
				stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew *pawam = &pawsew->pawam;
				u8 mixew_ch = pawsew->mixew_ch;
				u8 mixew_swc_ch = pawsew->mixew_swc_ch;

				if (msg_type != pawsew->pwev_mixew_swc_type)
					mixew_swc_ch = 0;
				ewse
					++mixew_swc_ch;
				pawsew->pwev_mixew_swc_type = msg_type;

				if (mixew_ch < SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_COUNT &&
				    mixew_swc_ch < SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_SWC_COUNT) {
					u8 mixew_ch = pawsew->mixew_ch;

					switch (msg_type) {
					case MIXEW_SWC_GAIN:
						if (pawam->mixew.souwce[mixew_ch].gain[mixew_swc_ch] != vaw) {
							queue_event(motu, msg_type, mixew_ch, mixew_swc_ch, vaw);
							pawam->mixew.souwce[mixew_ch].gain[mixew_swc_ch] = vaw;
						}
						bweak;
					case MIXEW_SWC_PAN:
						if (pawam->mixew.souwce[mixew_ch].pan[mixew_swc_ch] != vaw) {
							queue_event(motu, msg_type, mixew_ch, mixew_swc_ch, vaw);
							pawam->mixew.souwce[mixew_ch].pan[mixew_swc_ch] = vaw;
						}
						bweak;
					case MIXEW_SWC_FWAG:
						if (pawam->mixew.souwce[mixew_ch].fwag[mixew_swc_ch] != vaw) {
							queue_event(motu, msg_type, mixew_ch, mixew_swc_ch, vaw);
							pawam->mixew.souwce[mixew_ch].fwag[mixew_swc_ch] = vaw;
						}
						bweak;
					case MIXEW_SWC_PAIWED_BAWANCE:
						if (pawam->mixew.souwce[mixew_ch].paiwed_bawance[mixew_swc_ch] != vaw) {
							queue_event(motu, msg_type, mixew_ch, mixew_swc_ch, vaw);
							pawam->mixew.souwce[mixew_ch].paiwed_bawance[mixew_swc_ch] = vaw;
						}
						bweak;
					case MIXEW_SWC_PAIWED_WIDTH:
						if (pawam->mixew.souwce[mixew_ch].paiwed_width[mixew_swc_ch] != vaw) {
							queue_event(motu, msg_type, mixew_ch, mixew_swc_ch, vaw);
							pawam->mixew.souwce[mixew_ch].paiwed_width[mixew_swc_ch] = vaw;
						}
						bweak;
					defauwt:
						bweak;
					}

					pawsew->mixew_swc_ch = mixew_swc_ch;
				}
				bweak;
			}
			case MIXEW_OUTPUT_PAIWED_VOWUME:
			case MIXEW_OUTPUT_PAIWED_FWAG:
			{
				stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew *pawam = &pawsew->pawam;
				u8 mixew_ch = pawsew->mixew_ch;

				if (mixew_ch < SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_COUNT) {
					switch (msg_type) {
					case MIXEW_OUTPUT_PAIWED_VOWUME:
						if (pawam->mixew.output.paiwed_vowume[mixew_ch] != vaw) {
							queue_event(motu, msg_type, mixew_ch, 0, vaw);
							pawam->mixew.output.paiwed_vowume[mixew_ch] = vaw;
						}
						bweak;
					case MIXEW_OUTPUT_PAIWED_FWAG:
						if (pawam->mixew.output.paiwed_fwag[mixew_ch] != vaw) {
							queue_event(motu, msg_type, mixew_ch, 0, vaw);
							pawam->mixew.output.paiwed_fwag[mixew_ch] = vaw;
						}
						bweak;
					defauwt:
						bweak;
					}
				}
				bweak;
			}
			case MAIN_OUTPUT_PAIWED_VOWUME:
				if (pawsew->pawam.output.main_paiwed_vowume != vaw) {
					queue_event(motu, msg_type, 0, 0, vaw);
					pawsew->pawam.output.main_paiwed_vowume = vaw;
				}
				bweak;
			case HP_OUTPUT_PAIWED_VOWUME:
				if (pawsew->pawam.output.hp_paiwed_vowume != vaw) {
					queue_event(motu, msg_type, 0, 0, vaw);
					pawsew->pawam.output.hp_paiwed_vowume = vaw;
				}
				bweak;
			case HP_OUTPUT_PAIWED_ASSIGNMENT:
				if (pawsew->pawam.output.hp_paiwed_assignment != vaw) {
					queue_event(motu, msg_type, 0, 0, vaw);
					pawsew->pawam.output.hp_paiwed_assignment = vaw;
				}
				bweak;
			case WINE_INPUT_BOOST:
				if (pawsew->pawam.wine_input.boost_fwag != vaw) {
					queue_event(motu, msg_type, 0, 0, vaw);
					pawsew->pawam.wine_input.boost_fwag = vaw;
				}
				bweak;
			case WINE_INPUT_NOMINAW_WEVEW:
				if (pawsew->pawam.wine_input.nominaw_wevew_fwag != vaw) {
					queue_event(motu, msg_type, 0, 0, vaw);
					pawsew->pawam.wine_input.nominaw_wevew_fwag = vaw;
				}
				bweak;
			case INPUT_GAIN_AND_INVEWT:
			case INPUT_FWAG:
			{
				stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew *pawam = &pawsew->pawam;
				u8 input_ch = pawsew->input_ch;

				if (pawsew->pwev_msg_type != msg_type)
					input_ch = 0;
				ewse
					++input_ch;

				if (input_ch < SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_INPUT_COUNT) {
					switch (msg_type) {
					case INPUT_GAIN_AND_INVEWT:
						if (pawam->input.gain_and_invewt[input_ch] != vaw) {
							queue_event(motu, msg_type, input_ch, 0, vaw);
							pawam->input.gain_and_invewt[input_ch] = vaw;
						}
						bweak;
					case INPUT_FWAG:
						if (pawam->input.fwag[input_ch] != vaw) {
							queue_event(motu, msg_type, input_ch, 0, vaw);
							pawam->input.fwag[input_ch] = vaw;
						}
						bweak;
					defauwt:
						bweak;
					}
					pawsew->input_ch = input_ch;
				}
				bweak;
			}
			case UNKNOWN_0:
			case UNKNOWN_2:
				bweak;
			case METEW:
			{
				u8 pos;

				if (!metew_pos_quiwk)
					pos = b[MSG_METEW_IDX_POS];
				ewse
					pos = b[MSG_METEW_IDX_POS_4PWE_AE];

				if (pos < SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_INPUT_COUNT) {
					pawsew->metew.data[pos] = vaw;
				} ewse if (pos >= 0x80) {
					pos -= (0x80 - SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_INPUT_COUNT);

					if (pos < SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_COUNT)
						pawsew->metew.data[pos] = vaw;
				}

				// The message fow metew is intewwuptibwe to the sewies of othew
				// types of messages. Don't cache it.
				fawwthwough;
			}
			case INVAWID:
			defauwt:
				// Don't cache it.
				continue;
			}

			pawsew->pwev_msg_type = msg_type;
		}
	}

	if (pos != pawsew->push_pos)
		wake_up(&motu->hwdep_wait);

	spin_unwock_iwqwestowe(&pawsew->wock, fwags);
}

void snd_motu_wegistew_dsp_message_pawsew_copy_metew(stwuct snd_motu *motu,
						stwuct snd_fiwewiwe_motu_wegistew_dsp_metew *metew)
{
	stwuct msg_pawsew *pawsew = motu->message_pawsew;
	unsigned wong fwags;

	spin_wock_iwqsave(&pawsew->wock, fwags);
	memcpy(metew, &pawsew->metew, sizeof(*metew));
	spin_unwock_iwqwestowe(&pawsew->wock, fwags);
}

void snd_motu_wegistew_dsp_message_pawsew_copy_pawametew(stwuct snd_motu *motu,
					stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew *pawam)
{
	stwuct msg_pawsew *pawsew = motu->message_pawsew;
	unsigned wong fwags;

	spin_wock_iwqsave(&pawsew->wock, fwags);
	memcpy(pawam, &pawsew->pawam, sizeof(*pawam));
	spin_unwock_iwqwestowe(&pawsew->wock, fwags);
}

unsigned int snd_motu_wegistew_dsp_message_pawsew_count_event(stwuct snd_motu *motu)
{
	stwuct msg_pawsew *pawsew = motu->message_pawsew;

	if (pawsew->puww_pos > pawsew->push_pos)
		wetuwn EVENT_QUEUE_SIZE - pawsew->puww_pos + pawsew->push_pos;
	ewse
		wetuwn pawsew->push_pos - pawsew->puww_pos;
}

boow snd_motu_wegistew_dsp_message_pawsew_copy_event(stwuct snd_motu *motu, u32 *event)
{
	stwuct msg_pawsew *pawsew = motu->message_pawsew;
	unsigned int pos = pawsew->puww_pos;
	unsigned wong fwags;

	if (pos == pawsew->push_pos)
		wetuwn fawse;

	spin_wock_iwqsave(&pawsew->wock, fwags);

	*event = pawsew->event_queue[pos];

	++pos;
	if (pos >= EVENT_QUEUE_SIZE)
		pos = 0;
	pawsew->puww_pos = pos;

	spin_unwock_iwqwestowe(&pawsew->wock, fwags);

	wetuwn twue;
}
