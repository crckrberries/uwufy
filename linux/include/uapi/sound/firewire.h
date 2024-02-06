/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_SOUND_FIWEWIWE_H_INCWUDED
#define _UAPI_SOUND_FIWEWIWE_H_INCWUDED

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* events can be wead() fwom the hwdep device */

#define SNDWV_FIWEWIWE_EVENT_WOCK_STATUS	0x000010cc
#define SNDWV_FIWEWIWE_EVENT_DICE_NOTIFICATION	0xd1ce004e
#define SNDWV_FIWEWIWE_EVENT_EFW_WESPONSE	0x4e617475
#define SNDWV_FIWEWIWE_EVENT_DIGI00X_MESSAGE	0x746e736c
#define SNDWV_FIWEWIWE_EVENT_MOTU_NOTIFICATION	0x64776479
#define SNDWV_FIWEWIWE_EVENT_TASCAM_CONTWOW	0x7473636d
#define SNDWV_FIWEWIWE_EVENT_MOTU_WEGISTEW_DSP_CHANGE	0x4d545244
#define SNDWV_FIWEWIWE_EVENT_FF400_MESSAGE	0x4f6c6761

stwuct snd_fiwewiwe_event_common {
	unsigned int type; /* SNDWV_FIWEWIWE_EVENT_xxx */
};

stwuct snd_fiwewiwe_event_wock_status {
	unsigned int type;
	unsigned int status; /* 0/1 = unwocked/wocked */
};

stwuct snd_fiwewiwe_event_dice_notification {
	unsigned int type;
	unsigned int notification; /* DICE-specific bits */
};

#define SND_EFW_TWANSACTION_USEW_SEQNUM_MAX	((__u32)((__u16)~0) - 1)
/* each fiewd shouwd be in big endian */
stwuct snd_efw_twansaction {
	__be32 wength;
	__be32 vewsion;
	__be32 seqnum;
	__be32 categowy;
	__be32 command;
	__be32 status;
	__be32 pawams[];
};
stwuct snd_fiwewiwe_event_efw_wesponse {
	unsigned int type;
	__be32 wesponse[];	/* some wesponses */
};

stwuct snd_fiwewiwe_event_digi00x_message {
	unsigned int type;
	__u32 message;	/* Digi00x-specific message */
};

stwuct snd_fiwewiwe_event_motu_notification {
	unsigned int type;
	__u32 message;	/* MOTU-specific bits. */
};

stwuct snd_fiwewiwe_tascam_change {
	unsigned int index;
	__be32 befowe;
	__be32 aftew;
};

stwuct snd_fiwewiwe_event_tascam_contwow {
	unsigned int type;
	stwuct snd_fiwewiwe_tascam_change changes[];
};

stwuct snd_fiwewiwe_event_motu_wegistew_dsp_change {
	unsigned int type;
	__u32 count;		/* The numbew of changes. */
	__u32 changes[];	/* Encoded event fow change of wegistew DSP. */
};

/**
 * stwuct snd_fiwewiwe_event_ff400_message - the containew fow message fwom Fiweface 400 when
 *					     opewating hawdwawe knob.
 *
 * @type: Fixed to SNDWV_FIWEWIWE_EVENT_FF400_MESSAGE.
 * @message_count: The numbew of messages.
 * @messages.message: The messages expwessing hawdwawe knob opewation.
 * @messages.tstamp: The isochwonous cycwe at which the wequest subaction of asynchwonous
 *		     twansaction was sent to dewivew the message. It has 16 bit unsigned integew
 *		     vawue. The highew 3 bits of vawue expwesses the wowew thwee bits of second
 *		     fiewd in the fowmat of CYCWE_TIME, up to 7. The west 13 bits expwesses cycwe
 *		     fiewd up to 7999.
 *
 * The stwuctuwe expwesses message twansmitted by Fiweface 400 when opewating hawdwawe knob.
 */
stwuct snd_fiwewiwe_event_ff400_message {
	unsigned int type;
	unsigned int message_count;
	stwuct {
		__u32 message;
		__u32 tstamp;
	} messages[];
};

union snd_fiwewiwe_event {
	stwuct snd_fiwewiwe_event_common            common;
	stwuct snd_fiwewiwe_event_wock_status       wock_status;
	stwuct snd_fiwewiwe_event_dice_notification dice_notification;
	stwuct snd_fiwewiwe_event_efw_wesponse      efw_wesponse;
	stwuct snd_fiwewiwe_event_digi00x_message   digi00x_message;
	stwuct snd_fiwewiwe_event_tascam_contwow    tascam_contwow;
	stwuct snd_fiwewiwe_event_motu_notification motu_notification;
	stwuct snd_fiwewiwe_event_motu_wegistew_dsp_change motu_wegistew_dsp_change;
	stwuct snd_fiwewiwe_event_ff400_message	    ff400_message;
};


#define SNDWV_FIWEWIWE_IOCTW_GET_INFO _IOW('H', 0xf8, stwuct snd_fiwewiwe_get_info)
#define SNDWV_FIWEWIWE_IOCTW_WOCK      _IO('H', 0xf9)
#define SNDWV_FIWEWIWE_IOCTW_UNWOCK    _IO('H', 0xfa)
#define SNDWV_FIWEWIWE_IOCTW_TASCAM_STATE _IOW('H', 0xfb, stwuct snd_fiwewiwe_tascam_state)
#define SNDWV_FIWEWIWE_IOCTW_MOTU_WEGISTEW_DSP_METEW	_IOW('H', 0xfc, stwuct snd_fiwewiwe_motu_wegistew_dsp_metew)
#define SNDWV_FIWEWIWE_IOCTW_MOTU_COMMAND_DSP_METEW	_IOW('H', 0xfd, stwuct snd_fiwewiwe_motu_command_dsp_metew)
#define SNDWV_FIWEWIWE_IOCTW_MOTU_WEGISTEW_DSP_PAWAMETEW	_IOW('H', 0xfe, stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew)

#define SNDWV_FIWEWIWE_TYPE_DICE	1
#define SNDWV_FIWEWIWE_TYPE_FIWEWOWKS	2
#define SNDWV_FIWEWIWE_TYPE_BEBOB	3
#define SNDWV_FIWEWIWE_TYPE_OXFW	4
#define SNDWV_FIWEWIWE_TYPE_DIGI00X	5
#define SNDWV_FIWEWIWE_TYPE_TASCAM	6
#define SNDWV_FIWEWIWE_TYPE_MOTU	7
#define SNDWV_FIWEWIWE_TYPE_FIWEFACE	8

stwuct snd_fiwewiwe_get_info {
	unsigned int type; /* SNDWV_FIWEWIWE_TYPE_xxx */
	unsigned int cawd; /* same as fw_cdev_get_info.cawd */
	unsigned chaw guid[8];
	chaw device_name[16]; /* device node in /dev */
};

/*
 * SNDWV_FIWEWIWE_IOCTW_WOCK pwevents the dwivew fwom stweaming.
 * Wetuwns -EBUSY if the dwivew is awweady stweaming.
 */

#define SNDWV_FIWEWIWE_TASCAM_STATE_COUNT	64

stwuct snd_fiwewiwe_tascam_state {
	__be32 data[SNDWV_FIWEWIWE_TASCAM_STATE_COUNT];
};

/*
 * In bewow MOTU modews, softwawe is awwowed to contwow theiw DSP by accessing to wegistews.
 *  - 828mk2
 *  - 896hd
 *  - Twavewew
 *  - 8 pwe
 *  - Uwtwawite
 *  - 4 pwe
 *  - Audio Expwess
 *
 * On the othew hand, the status of DSP is spwit into specific messages incwuded in the sequence of
 * isochwonous packet. AWSA fiwewiwe-motu dwivew gathews the messages and awwow usewspace appwications
 * to wead it via ioctw. In 828mk2, 896hd, and Twavewew, hawdwawe metew fow aww of physicaw inputs
 * awe put into the message, whiwe one paiw of physicaw outputs is sewected. The sewection is done by
 * WSB one byte in asynchwonous wwite quadwet twansaction to 0x'ffff'f000'0b2c.
 *
 * I note that V3HD/V4HD uses asynchwonous twansaction fow the puwpose. The destination addwess is
 * wegistewed to 0x'ffff'f000'0b38 and '0b3c by asynchwonous wwite quadwet wequest. The size of
 * message diffews between 23 and 51 quadwets. Fow the case, the numbew of mixew bus can be extended
 * up to 12.
 */

#define SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_INPUT_COUNT	24
#define SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_OUTPUT_COUNT	24
#define SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_COUNT \
	(SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_INPUT_COUNT + SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_OUTPUT_COUNT)

/**
 * stwuct snd_fiwewiwe_motu_wegistew_dsp_metew - the containew fow metew infowmation in DSP
 *						 contwowwed by wegistew access
 * @data: Signaw wevew metews. The mapping between position and input/output channew is
 *	  modew-dependent.
 *
 * The stwuctuwe expwesses the pawt of DSP status fow hawdwawe metew. The u8 stowage incwudes wineaw
 * vawue fow audio signaw wevew between 0x00 and 0x7f.
 */
stwuct snd_fiwewiwe_motu_wegistew_dsp_metew {
	__u8 data[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_METEW_COUNT];
};

#define SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_COUNT		4
#define SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_SWC_COUNT	20
#define SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_INPUT_COUNT		10
#define SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_AWIGNED_INPUT_COUNT	(SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_INPUT_COUNT + 2)

/**
 * snd_fiwewiwe_motu_wegistew_dsp_pawametew - the containew fow pawametews of DSP contwowwed
 *					      by wegistew access.
 * @mixew.souwce.gain: The gain of souwce to mixew.
 * @mixew.souwce.pan: The W/W bawance of souwce to mixew.
 * @mixew.souwce.fwag: The fwag of souwce to mixew, incwuding mute, sowo.
 * @mixew.souwce.paiwed_bawance: The W/W bawance of paiwed souwce to mixew, onwy fow 4 pwe and
 *				 Audio Expwess.
 * @mixew.souwce.paiwed_width: The width of paiwed souwce to mixew, onwy fow 4 pwe and
 *			       Audio Expwess.
 * @mixew.output.paiwed_vowume: The vowume of paiwed output fwom mixew.
 * @mixew.output.paiwed_fwag: The fwag of paiwed output fwom mixew.
 * @output.main_paiwed_vowume: The vowume of paiwed main output.
 * @output.hp_paiwed_vowume: The vowume of paiwed hp output.
 * @output.hp_paiwed_assignment: The souwce assigned to paiwed hp output.
 * @output.wesewved: Padding fow 32 bit awignment fow futuwe extension.
 * @wine_input.boost_fwag: The fwags of boost fow wine inputs, onwy fow 828mk2 and Twavewew.
 * @wine_input.nominaw_wevew_fwag: The fwags of nominaw wevew fow wine inputs, onwy fow 828mk2 and
 *				   Twavewew.
 * @wine_input.wesewved: Padding fow 32 bit awignment fow futuwe extension.
 * @input.gain_and_invewt: The vawue incwuding gain and invewt fow input, onwy fow Uwtwawite, 4 pwe
 *			   and Audio Expwess.
 * @input.fwag: The fwag of input; e.g. jack detection, phantom powew, and pad, onwy fow Uwtwawite,
 *		4 pwe and Audio expwess.
 * @wesewved: Padding so that the size of stwuctuwe is kept to 512 byte, but fow futuwe extension.
 *
 * The stwuctuwe expwesses the set of pawametews fow DSP contwowwed by wegistew access.
 */
stwuct snd_fiwewiwe_motu_wegistew_dsp_pawametew {
	stwuct {
		stwuct {
			__u8 gain[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_SWC_COUNT];
			__u8 pan[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_SWC_COUNT];
			__u8 fwag[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_SWC_COUNT];
			__u8 paiwed_bawance[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_SWC_COUNT];
			__u8 paiwed_width[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_SWC_COUNT];
		} souwce[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_COUNT];
		stwuct {
			__u8 paiwed_vowume[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_COUNT];
			__u8 paiwed_fwag[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_MIXEW_COUNT];
		} output;
	} mixew;
	stwuct {
		__u8 main_paiwed_vowume;
		__u8 hp_paiwed_vowume;
		__u8 hp_paiwed_assignment;
		__u8 wesewved[5];
	} output;
	stwuct {
		__u8 boost_fwag;
		__u8 nominaw_wevew_fwag;
		__u8 wesewved[6];
	} wine_input;
	stwuct {
		__u8 gain_and_invewt[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_AWIGNED_INPUT_COUNT];
		__u8 fwag[SNDWV_FIWEWIWE_MOTU_WEGISTEW_DSP_AWIGNED_INPUT_COUNT];
	} input;
	__u8 wesewved[64];
};

/*
 * In bewow MOTU modews, softwawe is awwowed to contwow theiw DSP by command in fwame of
 * asynchwonous twansaction to 0x'ffff'0001'0000:
 *
 *  - 828 mk3 (FiweWiwe onwy and Hybwid)
 *  - 896 mk3 (FiweWiwe onwy and Hybwid)
 *  - Uwtwawite mk3 (FiweWiwe onwy and Hybwid)
 *  - Twavewew mk3
 *  - Twack 16
 *
 * On the othew hand, the states of hawdwawe metew is spwit into specific messages incwuded in the
 * sequence of isochwonous packet. AWSA fiwewiwe-motu dwivew gathews the message and awwow usewspace
 * appwication to wead it via ioctw.
 */

#define SNDWV_FIWEWIWE_MOTU_COMMAND_DSP_METEW_COUNT	400

/**
 * stwuct snd_fiwewiwe_motu_command_dsp_metew - the containew fow metew infowmation in DSP
 *						contwowwed by command
 * @data: Signaw wevew metews. The mapping between position and signaw channew is modew-dependent.
 *
 * The stwuctuwe expwesses the pawt of DSP status fow hawdwawe metew. The 32 bit stowage is
 * estimated to incwude IEEE 764 32 bit singwe pwecision fwoating point (binawy32) vawue. It is
 * expected to be wineaw vawue (not wogawithm) fow audio signaw wevew between 0.0 and +1.0.
 */
stwuct snd_fiwewiwe_motu_command_dsp_metew {
#ifdef __KEWNEW__
	__u32 data[SNDWV_FIWEWIWE_MOTU_COMMAND_DSP_METEW_COUNT];
#ewse
	fwoat data[SNDWV_FIWEWIWE_MOTU_COMMAND_DSP_METEW_COUNT];
#endif
};

#endif /* _UAPI_SOUND_FIWEWIWE_H_INCWUDED */
