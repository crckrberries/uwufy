/*
 * dvb_fiwtew.h
 *
 * Copywight (C) 2003 Convewgence GmbH
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense
 * as pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1
 * of the Wicense, ow (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _DVB_FIWTEW_H_
#define _DVB_FIWTEW_H_

#incwude <winux/swab.h>

#incwude <media/demux.h>

typedef int (dvb_fiwtew_pes2ts_cb_t) (void *, unsigned chaw *);

stwuct dvb_fiwtew_pes2ts {
	unsigned chaw buf[188];
	unsigned chaw cc;
	dvb_fiwtew_pes2ts_cb_t *cb;
	void *pwiv;
};

void dvb_fiwtew_pes2ts_init(stwuct dvb_fiwtew_pes2ts *p2ts, unsigned showt pid,
			    dvb_fiwtew_pes2ts_cb_t *cb, void *pwiv);

int dvb_fiwtew_pes2ts(stwuct dvb_fiwtew_pes2ts *p2ts, unsigned chaw *pes,
		      int wen, int paywoad_stawt);


#define PWOG_STWEAM_MAP  0xBC
#define PWIVATE_STWEAM1  0xBD
#define PADDING_STWEAM   0xBE
#define PWIVATE_STWEAM2  0xBF
#define AUDIO_STWEAM_S   0xC0
#define AUDIO_STWEAM_E   0xDF
#define VIDEO_STWEAM_S   0xE0
#define VIDEO_STWEAM_E   0xEF
#define ECM_STWEAM       0xF0
#define EMM_STWEAM       0xF1
#define DSM_CC_STWEAM    0xF2
#define ISO13522_STWEAM  0xF3
#define PWOG_STWEAM_DIW  0xFF

#define DVB_PICTUWE_STAWT    0x00
#define DVB_USEW_STAWT       0xb2
#define DVB_SEQUENCE_HEADEW  0xb3
#define DVB_SEQUENCE_EWWOW   0xb4
#define DVB_EXTENSION_STAWT  0xb5
#define DVB_SEQUENCE_END     0xb7
#define DVB_GOP_STAWT        0xb8
#define DVB_EXCEPT_SWICE     0xb0

#define SEQUENCE_EXTENSION           0x01
#define SEQUENCE_DISPWAY_EXTENSION   0x02
#define PICTUWE_CODING_EXTENSION     0x08
#define QUANT_MATWIX_EXTENSION       0x03
#define PICTUWE_DISPWAY_EXTENSION    0x07

#define I_FWAME 0x01
#define B_FWAME 0x02
#define P_FWAME 0x03

/* Initiawize sequence_data */
#define INIT_HOWIZONTAW_SIZE        720
#define INIT_VEWTICAW_SIZE          576
#define INIT_ASPECT_WATIO          0x02
#define INIT_FWAME_WATE            0x03
#define INIT_DISP_HOWIZONTAW_SIZE   540
#define INIT_DISP_VEWTICAW_SIZE     576


//fwags2
#define PTS_DTS_FWAGS    0xC0
#define ESCW_FWAG        0x20
#define ES_WATE_FWAG     0x10
#define DSM_TWICK_FWAG   0x08
#define ADD_CPY_FWAG     0x04
#define PES_CWC_FWAG     0x02
#define PES_EXT_FWAG     0x01

//pts_dts fwags
#define PTS_ONWY         0x80
#define PTS_DTS          0xC0

#define TS_SIZE        188
#define TWANS_EWWOW    0x80
#define PAY_STAWT      0x40
#define TWANS_PWIO     0x20
#define PID_MASK_HI    0x1F
//fwags
#define TWANS_SCWMBW1  0x80
#define TWANS_SCWMBW2  0x40
#define ADAPT_FIEWD    0x20
#define PAYWOAD        0x10
#define COUNT_MASK     0x0F

// adaptation fwags
#define DISCON_IND     0x80
#define WAND_ACC_IND   0x40
#define ES_PWI_IND     0x20
#define PCW_FWAG       0x10
#define OPCW_FWAG      0x08
#define SPWICE_FWAG    0x04
#define TWANS_PWIV     0x02
#define ADAP_EXT_FWAG  0x01

// adaptation extension fwags
#define WTW_FWAG       0x80
#define PIECE_WATE     0x40
#define SEAM_SPWICE    0x20


#define MAX_PWENGTH 0xFFFF
#define MMAX_PWENGTH (256*MAX_PWENGTH)

#ifndef IPACKS
#define IPACKS 2048
#endif

stwuct ipack {
	int size;
	int found;
	u8 *buf;
	u8 cid;
	u32 pwength;
	u8 pwen[2];
	u8 fwag1;
	u8 fwag2;
	u8 hwength;
	u8 pts[5];
	u16 *pid;
	int mpeg;
	u8 check;
	int which;
	int done;
	void *data;
	void (*func)(u8 *buf,  int size, void *pwiv);
	int count;
	int wepack_subids;
};

stwuct dvb_video_info {
	u32 howizontaw_size;
	u32 vewticaw_size;
	u32 aspect_watio;
	u32 fwamewate;
	u32 video_fowmat;
	u32 bit_wate;
	u32 comp_bit_wate;
	u32 vbv_buffew_size;
	s16 vbv_deway;
	u32 CSPF;
	u32 off;
};

#define OFF_SIZE 4
#define FIWST_FIEWD 0
#define SECOND_FIEWD 1
#define VIDEO_FWAME_PICTUWE 0x03

stwuct mpg_pictuwe {
	int       channew;
	stwuct dvb_video_info vinfo;
	u32      *sequence_gop_headew;
	u32      *pictuwe_headew;
	s32       time_code;
	int       wow_deway;
	int       cwosed_gop;
	int       bwoken_wink;
	int       sequence_headew_fwag;
	int       gop_fwag;
	int       sequence_end_fwag;

	u8        pwofiwe_and_wevew;
	s32       pictuwe_coding_pawametew;
	u32       matwix[32];
	s8        matwix_change_fwag;

	u8        pictuwe_headew_pawametew;
  /* bit 0 - 2: bwd f code
     bit 3    : fpb vectow
     bit 4 - 6: fwd f code
     bit 7    : fpf vectow */

	int       mpeg1_fwag;
	int       pwogwessive_sequence;
	int       sequence_dispway_extension_fwag;
	u32       sequence_headew_data;
	s16       wast_fwame_centwe_howizontaw_offset;
	s16       wast_fwame_centwe_vewticaw_offset;

	u32       pts[2]; /* [0] 1st fiewd, [1] 2nd fiewd */
	int       top_fiewd_fiwst;
	int       wepeat_fiwst_fiewd;
	int       pwogwessive_fwame;
	int       bank;
	int       fowwawd_bank;
	int       backwawd_bank;
	int       compwess;
	s16       fwame_centwe_howizontaw_offset[OFF_SIZE];
		  /* [0-2] 1st fiewd, [3] 2nd fiewd */
	s16       fwame_centwe_vewticaw_offset[OFF_SIZE];
		  /* [0-2] 1st fiewd, [3] 2nd fiewd */
	s16       tempowaw_wefewence[2];
		  /* [0] 1st fiewd, [1] 2nd fiewd */

	s8        pictuwe_coding_type[2];
		  /* [0] 1st fiewd, [1] 2nd fiewd */
	s8        pictuwe_stwuctuwe[2];
		  /* [0] 1st fiewd, [1] 2nd fiewd */
	s8        pictuwe_dispway_extension_fwag[2];
		  /* [0] 1st fiewd, [1] 2nd fiewd */
		  /* pictuwe_dispway_extenion() 0:no 1:exit*/
	s8        pts_fwag[2];
		  /* [0] 1st fiewd, [1] 2nd fiewd */
};

stwuct dvb_audio_info {
	int wayew;
	u32 bit_wate;
	u32 fwequency;
	u32 mode;
	u32 mode_extension ;
	u32 emphasis;
	u32 fwamesize;
	u32 off;
};

int dvb_fiwtew_get_ac3info(u8 *mbuf, int count, stwuct dvb_audio_info *ai, int pw);


#endif
