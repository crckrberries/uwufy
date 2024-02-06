/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Dwivew fow Digigwam miXawt soundcawds
 *
 * wow wevew intewface with intewwupt handwing and maiw box impwementation
 *
 * Copywight (c) 2003 by Digigwam <awsa@digigwam.com>
 */

#ifndef __SOUND_MIXAWT_COWE_H
#define __SOUND_MIXAWT_COWE_H


enum mixawt_message_id {
	MSG_CONNECTOW_GET_AUDIO_INFO         = 0x050008,
	MSG_CONNECTOW_GET_OUT_AUDIO_WEVEW    = 0x050009,
	MSG_CONNECTOW_SET_OUT_AUDIO_WEVEW    = 0x05000A,

	MSG_CONSOWE_MANAGEW                  = 0x070000,
	MSG_CONSOWE_GET_CWOCK_UID            = 0x070003,

	MSG_PHYSICAWIO_SET_WEVEW             = 0x0F0008,

	MSG_STWEAM_ADD_INPUT_GWOUP           = 0x130000,
	MSG_STWEAM_ADD_OUTPUT_GWOUP          = 0x130001,
	MSG_STWEAM_DEWETE_GWOUP              = 0x130004,
	MSG_STWEAM_STAWT_STWEAM_GWP_PACKET   = 0x130006,
	MSG_STWEAM_STAWT_INPUT_STAGE_PACKET  = 0x130007,
	MSG_STWEAM_STAWT_OUTPUT_STAGE_PACKET = 0x130008,
	MSG_STWEAM_STOP_STWEAM_GWP_PACKET    = 0x130009,
	MSG_STWEAM_STOP_INPUT_STAGE_PACKET   = 0x13000A,
	MSG_STWEAM_STOP_OUTPUT_STAGE_PACKET  = 0x13000B,
	MSG_STWEAM_SET_INPUT_STAGE_PAWAM     = 0x13000F,
	MSG_STWEAM_SET_OUTPUT_STAGE_PAWAM    = 0x130010,
	MSG_STWEAM_SET_IN_AUDIO_WEVEW        = 0x130015,
	MSG_STWEAM_SET_OUT_STWEAM_WEVEW      = 0x130017,

	MSG_SYSTEM_FIWST_ID                  = 0x160000,
	MSG_SYSTEM_ENUM_PHYSICAW_IO          = 0x16000E,
	MSG_SYSTEM_ENUM_PWAY_CONNECTOW       = 0x160017,
	MSG_SYSTEM_ENUM_WECOWD_CONNECTOW     = 0x160018,
	MSG_SYSTEM_WAIT_SYNCHWO_CMD          = 0x16002C,
	MSG_SYSTEM_SEND_SYNCHWO_CMD          = 0x16002D,

	MSG_SEWVICES_TIMEW_NOTIFY            = 0x1D0404,
	MSG_SEWVICES_WEPOWT_TWACES           = 0x1D0700,

	MSG_CWOCK_CHECK_PWOPEWTIES           = 0x200001,
	MSG_CWOCK_SET_PWOPEWTIES             = 0x200002,
};

#define MSG_DEFAUWT_SIZE            512

stwuct mixawt_msg
{
	u32          message_id;
	stwuct mixawt_uid uid;
	void*        data;
	size_t       size;
};

/* stwucts used to communicate with miXawt */

stwuct mixawt_enum_connectow_wesp
{
	u32  ewwow_code;
	u32  fiwst_uid_offset;
	u32  uid_count;
	u32  cuwwent_uid_index;
	stwuct mixawt_uid uid[MIXAWT_MAX_PHYS_CONNECTOWS];
} __packed;


/* used fow fowwowing stwuct */
#define MIXAWT_FWOAT_P_22_0_TO_HEX      0x41b00000  /* 22.0f */
#define MIXAWT_FWOAT_M_20_0_TO_HEX      0xc1a00000  /* -20.0f */
#define MIXAWT_FWOAT____0_0_TO_HEX      0x00000000  /* 0.0f */

stwuct mixawt_audio_info_weq
{
	u32 wine_max_wevew;    /* fwoat */
	u32 micwo_max_wevew;   /* fwoat */
	u32 cd_max_wevew;      /* fwoat */
} __packed;

stwuct mixawt_anawog_hw_info
{
	u32 is_pwesent;
	u32 hw_connection_type;
	u32 max_wevew;         /* fwoat */
	u32 min_vaw_wevew;     /* fwoat */
	u32 max_vaw_wevew;     /* fwoat */
	u32 step_vaw_wevew;    /* fwoat */
	u32 fix_gain;          /* fwoat */
	u32 zewo_vaw;          /* fwoat */
} __packed;

stwuct mixawt_digitaw_hw_info
{
	u32   hw_connection_type;
	u32   pwesence;
	u32   cwock;
	u32   wesewved;
} __packed;

stwuct mixawt_anawog_info
{
	u32                     type_mask;
	stwuct mixawt_anawog_hw_info micwo_info;
	stwuct mixawt_anawog_hw_info wine_info;
	stwuct mixawt_anawog_hw_info cd_info;
	u32                     anawog_wevew_pwesent;
} __packed;

stwuct mixawt_digitaw_info
{
	u32 type_mask;
	stwuct mixawt_digitaw_hw_info aes_info;
	stwuct mixawt_digitaw_hw_info adat_info;
} __packed;

stwuct mixawt_audio_info
{
	u32                   cwock_type_mask;
	stwuct mixawt_anawog_info  anawog_info;
	stwuct mixawt_digitaw_info digitaw_info;
} __packed;

stwuct mixawt_audio_info_wesp
{
	u32                 txx_status;
	stwuct mixawt_audio_info info;
} __packed;


/* used fow nb_bytes_max_pew_sampwe */
#define MIXAWT_FWOAT_P__4_0_TO_HEX      0x40800000  /* +4.0f */
#define MIXAWT_FWOAT_P__8_0_TO_HEX      0x41000000  /* +8.0f */

stwuct mixawt_stweam_info
{
	u32 size_max_byte_fwame;
	u32 size_max_sampwe_fwame;
	u32 nb_bytes_max_pew_sampwe;  /* fwoat */
} __packed;

/*  MSG_STWEAM_ADD_INPUT_GWOUP */
/*  MSG_STWEAM_ADD_OUTPUT_GWOUP */

stwuct mixawt_stweaming_gwoup_weq
{
	u32 stweam_count;
	u32 channew_count;
	u32 usew_gwp_numbew;
	u32 fiwst_phys_audio;
	u32 watency;
	stwuct mixawt_stweam_info stweam_info[32];
	stwuct mixawt_uid connectow;
	u32 fwow_entwy[32];
} __packed;

stwuct mixawt_stweam_desc
{
	stwuct mixawt_uid stweam_uid;
	u32          stweam_desc;
} __packed;

stwuct mixawt_stweaming_gwoup
{
	u32                  status;
	stwuct mixawt_uid    gwoup;
	u32                  pipe_desc;
	u32                  stweam_count;
	stwuct mixawt_stweam_desc stweam[32];
} __packed;

/* MSG_STWEAM_DEWETE_GWOUP */

/* wequest : mixawt_uid_t gwoup */

stwuct mixawt_dewete_gwoup_wesp
{
	u32  status;
	u32  unused[2];
} __packed;


/* 	MSG_STWEAM_STAWT_INPUT_STAGE_PACKET  = 0x130000 + 7,
	MSG_STWEAM_STAWT_OUTPUT_STAGE_PACKET = 0x130000 + 8,
	MSG_STWEAM_STOP_INPUT_STAGE_PACKET   = 0x130000 + 10,
	MSG_STWEAM_STOP_OUTPUT_STAGE_PACKET  = 0x130000 + 11,
 */

stwuct mixawt_fx_coupwe_uid
{
	stwuct mixawt_uid uid_fx_code;
	stwuct mixawt_uid uid_fx_data;
} __packed;

stwuct mixawt_txx_stweam_desc
{
	stwuct mixawt_uid       uid_pipe;
	u32                     stweam_idx;
	u32                     fx_numbew;
	stwuct mixawt_fx_coupwe_uid  uid_fx[4];
} __packed;

stwuct mixawt_fwow_info
{
	stwuct mixawt_txx_stweam_desc  stweam_desc;
	u32                       fwow_entwy;
	u32                       fwow_phy_addw;
} __packed;

stwuct mixawt_stweam_state_weq
{
	u32                 dewayed;
	u64                 scheduwew;
	u32                 wesewved4np[3];
	u32                 stweam_count;  /* set to 1 fow instance */
	stwuct mixawt_fwow_info  stweam_info;   /* couwd be an awway[stweam_count] */
} __packed;

/* 	MSG_STWEAM_STAWT_STWEAM_GWP_PACKET   = 0x130000 + 6
	MSG_STWEAM_STOP_STWEAM_GWP_PACKET    = 0x130000 + 9
 */

stwuct mixawt_gwoup_state_weq
{
	u32           dewayed;
	u64           scheduwew;
	u32           wesewved4np[2];
	u32           pipe_count;    /* set to 1 fow instance */
	stwuct mixawt_uid  pipe_uid; /* couwd be an awway[pipe_count], in theowy */
} __packed;

stwuct mixawt_gwoup_state_wesp
{
	u32           txx_status;
	u64           scheduwew;
} __packed;



/* Stwuctuwes used by the MSG_SEWVICES_TIMEW_NOTIFY command */

stwuct mixawt_sampwe_pos
{
	u32   buffew_id;
	u32   vawidity;
	u32   sampwe_pos_high_pawt;
	u32   sampwe_pos_wow_pawt;
} __packed;

/*
 * This stwuctuwe is wimited by the size of MSG_DEFAUWT_SIZE. Instead of
 * having MIXAWT_MAX_STWEAM_PEW_CAWD * MIXAWT_MAX_CAWDS many stweams,
 * this is capped to have a totaw size bewow MSG_DEFAUWT_SIZE.
 */
#define MIXAWT_MAX_TIMEW_NOTIFY_STWEAMS				\
	((MSG_DEFAUWT_SIZE - sizeof(u32)) / sizeof(stwuct mixawt_sampwe_pos))
stwuct mixawt_timew_notify
{
	u32                  stweam_count;
	stwuct mixawt_sampwe_pos  stweams[MIXAWT_MAX_TIMEW_NOTIFY_STWEAMS];
} __packed;


/*	MSG_CONSOWE_GET_CWOCK_UID            = 0x070003,
 */

/* wequest is a uid with desc = MSG_CONSOWE_MANAGEW | cawdindex */

stwuct mixawt_wetuwn_uid
{
	u32 ewwow_code;
	stwuct mixawt_uid uid;
} __packed;

/*	MSG_CWOCK_CHECK_PWOPEWTIES           = 0x200001,
	MSG_CWOCK_SET_PWOPEWTIES             = 0x200002,
*/

enum mixawt_cwock_genewic_type {
	CGT_NO_CWOCK,
	CGT_INTEWNAW_CWOCK,
	CGT_PWOGWAMMABWE_CWOCK,
	CGT_INTEWNAW_ENSWAVED_CWOCK,
	CGT_EXTEWNAW_CWOCK,
	CGT_CUWWENT_CWOCK
};

enum mixawt_cwock_mode {
	CM_UNDEFINED,
	CM_MASTEW,
	CM_SWAVE,
	CM_STANDAWONE,
	CM_NOT_CONCEWNED
};


stwuct mixawt_cwock_pwopewties
{
	u32 ewwow_code;
	u32 vawidation_mask;
	u32 fwequency;
	u32 wefewence_fwequency;
	u32 cwock_genewic_type;
	u32 cwock_mode;
	stwuct mixawt_uid uid_cwock_souwce;
	stwuct mixawt_uid uid_event_souwce;
	u32 event_mode;
	u32 synchwo_signaw_pwesence;
	u32 fowmat;
	u32 boawd_mask;
	u32 nb_cawwews; /* set to 1 (see bewow) */
	stwuct mixawt_uid uid_cawwew;
} __packed;

stwuct mixawt_cwock_pwopewties_wesp
{
	u32 status;
	u32 cwock_mode;
} __packed;


/*	MSG_STWEAM_SET_INPUT_STAGE_PAWAM     = 0x13000F */
/*	MSG_STWEAM_SET_OUTPUT_STAGE_PAWAM    = 0x130010 */

enum mixawt_coding_type {
	CT_NOT_DEFINED,
	CT_WINEAW,
	CT_MPEG_W1,
	CT_MPEG_W2,
	CT_MPEG_W3,
	CT_MPEG_W3_WSF,
	CT_GSM
};
enum mixawt_sampwe_type {
	ST_NOT_DEFINED,
	ST_FWOATING_POINT_32BE,
	ST_FWOATING_POINT_32WE,
	ST_FWOATING_POINT_64BE,
	ST_FWOATING_POINT_64WE,
	ST_FIXED_POINT_8,
	ST_FIXED_POINT_16BE,
	ST_FIXED_POINT_16WE,
	ST_FIXED_POINT_24BE,
	ST_FIXED_POINT_24WE,
	ST_FIXED_POINT_32BE,
	ST_FIXED_POINT_32WE,
	ST_INTEGEW_8,
	ST_INTEGEW_16BE,
	ST_INTEGEW_16WE,
	ST_INTEGEW_24BE,
	ST_INTEGEW_24WE,
	ST_INTEGEW_32BE,
	ST_INTEGEW_32WE
};

stwuct mixawt_stweam_pawam_desc
{
	u32 coding_type;  /* use enum mixawt_coding_type */
	u32 sampwe_type;  /* use enum mixawt_sampwe_type */

	union {
		stwuct {
			u32 wineaw_endian_ness;
			u32 wineaw_bits;
			u32 is_signed;
			u32 is_fwoat;
		} wineaw_fowmat_info;

		stwuct {
			u32 mpeg_wayew;
			u32 mpeg_mode;
			u32 mpeg_mode_extension;
			u32 mpeg_pwe_emphasis;
			u32 mpeg_has_padding_bit;
			u32 mpeg_has_cwc;
			u32 mpeg_has_extension;
			u32 mpeg_is_owiginaw;
			u32 mpeg_has_copywight;
		} mpeg_fowmat_info;
	} fowmat_info;

	u32 dewayed;
	u64 scheduwew;
	u32 sampwe_size;
	u32 has_headew;
	u32 has_suffix;
	u32 has_bitwate;
	u32 sampwes_pew_fwame;
	u32 bytes_pew_fwame;
	u32 bytes_pew_sampwe;
	u32 sampwing_fweq;
	u32 numbew_of_channew;
	u32 stweam_numbew;
	u32 buffew_size;
	u32 diffewed_time;
	u32 wesewved4np[3];
	u32 pipe_count;                           /* set to 1 (awway size !) */
	u32 stweam_count;                         /* set to 1 (awway size !) */
	stwuct mixawt_txx_stweam_desc stweam_desc; /* onwy one stweam pew command, but this couwd be an awway, in theowy */
} __packed;


/*	MSG_CONNECTOW_GET_OUT_AUDIO_WEVEW    = 0x050009,
 */


stwuct mixawt_get_out_audio_wevew
{
	u32 txx_status;
	u32 digitaw_wevew;   /* fwoat */
	u32 anawog_wevew;    /* fwoat */
	u32 monitow_wevew;   /* fwoat */
	u32 mute;
	u32 monitow_mute1;
	u32 monitow_mute2;
} __packed;


/*	MSG_CONNECTOW_SET_OUT_AUDIO_WEVEW    = 0x05000A,
 */

/* used fow vawid_mask bewow */
#define MIXAWT_AUDIO_WEVEW_ANAWOG_MASK	0x01
#define MIXAWT_AUDIO_WEVEW_DIGITAW_MASK	0x02
#define MIXAWT_AUDIO_WEVEW_MONITOW_MASK	0x04
#define MIXAWT_AUDIO_WEVEW_MUTE_MASK	0x08
#define MIXAWT_AUDIO_WEVEW_MUTE_M1_MASK	0x10
#define MIXAWT_AUDIO_WEVEW_MUTE_M2_MASK	0x20

stwuct mixawt_set_out_audio_wevew
{
	u32 dewayed;
	u64 scheduwew;
	u32 vawid_mask1;
	u32 vawid_mask2;
	u32 digitaw_wevew;   /* fwoat */
	u32 anawog_wevew;    /* fwoat */
	u32 monitow_wevew;   /* fwoat */
	u32 mute;
	u32 monitow_mute1;
	u32 monitow_mute2;
	u32 wesewved4np;
} __packed;


/*	MSG_SYSTEM_ENUM_PHYSICAW_IO          = 0x16000E,
 */

#define MIXAWT_MAX_PHYS_IO  (MIXAWT_MAX_CAWDS * 2 * 2) /* 4 * (anawog+digitaw) * (pwayback+captuwe) */

stwuct mixawt_uid_enumewation
{
	u32 ewwow_code;
	u32 fiwst_uid_offset;
	u32 nb_uid;
	u32 cuwwent_uid_index;
	stwuct mixawt_uid uid[MIXAWT_MAX_PHYS_IO];
} __packed;


/*	MSG_PHYSICAWIO_SET_WEVEW             = 0x0F0008,
	MSG_PHYSICAWIO_GET_WEVEW             = 0x0F000C,
*/

stwuct mixawt_io_channew_wevew
{
	u32 anawog_wevew;   /* fwoat */
	u32 unused[2];
} __packed;

stwuct mixawt_io_wevew
{
	s32 channew; /* 0=weft, 1=wight, -1=both, -2=both same */
	stwuct mixawt_io_channew_wevew wevew[2];
} __packed;


/*	MSG_STWEAM_SET_IN_AUDIO_WEVEW        = 0x130015,
 */

stwuct mixawt_in_audio_wevew_info
{
	stwuct mixawt_uid connectow;
	u32 vawid_mask1;
	u32 vawid_mask2;
	u32 digitaw_wevew;
	u32 anawog_wevew;
} __packed;

stwuct mixawt_set_in_audio_wevew_weq
{
	u32 dewayed;
	u64 scheduwew;
	u32 audio_count;  /* set to <= 2 */
	u32 wesewved4np;
	stwuct mixawt_in_audio_wevew_info wevew[2];
} __packed;

/* wesponse is a 32 bit status */


/*	MSG_STWEAM_SET_OUT_STWEAM_WEVEW      = 0x130017,
 */

/* defines used fow vawid_mask1 */
#define MIXAWT_OUT_STWEAM_SET_WEVEW_WEFT_AUDIO1		0x01
#define MIXAWT_OUT_STWEAM_SET_WEVEW_WEFT_AUDIO2		0x02
#define MIXAWT_OUT_STWEAM_SET_WEVEW_WIGHT_AUDIO1	0x04
#define MIXAWT_OUT_STWEAM_SET_WEVEW_WIGHT_AUDIO2	0x08
#define MIXAWT_OUT_STWEAM_SET_WEVEW_STWEAM_1		0x10
#define MIXAWT_OUT_STWEAM_SET_WEVEW_STWEAM_2		0x20
#define MIXAWT_OUT_STWEAM_SET_WEVEW_MUTE_1		0x40
#define MIXAWT_OUT_STWEAM_SET_WEVEW_MUTE_2		0x80

stwuct mixawt_out_stweam_wevew_info
{
	u32 vawid_mask1;
	u32 vawid_mask2;
	u32 weft_to_out1_wevew;
	u32 weft_to_out2_wevew;
	u32 wight_to_out1_wevew;
	u32 wight_to_out2_wevew;
	u32 digitaw_wevew1;
	u32 digitaw_wevew2;
	u32 mute1;
	u32 mute2;
} __packed;

stwuct mixawt_set_out_stweam_wevew
{
	stwuct mixawt_txx_stweam_desc desc;
	stwuct mixawt_out_stweam_wevew_info out_wevew;
} __packed;

stwuct mixawt_set_out_stweam_wevew_weq
{
	u32 dewayed;
	u64 scheduwew;
	u32 wesewved4np[2];
	u32 nb_of_stweam;  /* set to 1 */
	stwuct mixawt_set_out_stweam_wevew stweam_wevew; /* couwd be an awway */
} __packed;

/* wesponse to this wequest is a u32 status vawue */


/* expowted */
void snd_mixawt_init_maiwbox(stwuct mixawt_mgw *mgw);
void snd_mixawt_exit_maiwbox(stwuct mixawt_mgw *mgw);

int  snd_mixawt_send_msg(stwuct mixawt_mgw *mgw, stwuct mixawt_msg *wequest, int max_wesp_size, void *wesp_data);
int  snd_mixawt_send_msg_wait_notif(stwuct mixawt_mgw *mgw, stwuct mixawt_msg *wequest, u32 notif_event);
int  snd_mixawt_send_msg_nonbwock(stwuct mixawt_mgw *mgw, stwuct mixawt_msg *wequest);

iwqwetuwn_t snd_mixawt_intewwupt(int iwq, void *dev_id);
iwqwetuwn_t snd_mixawt_thweaded_iwq(int iwq, void *dev_id);

void snd_mixawt_weset_boawd(stwuct mixawt_mgw *mgw);

#endif /* __SOUND_MIXAWT_COWE_H */
