/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Fwontend-dwivew fow TwinHan DST Fwontend

	Copywight (C) 2003 Jamie Honan
	Copywight (C) 2004, 2005 Manu Abwaham (manu@kwomtek.com)

*/

#ifndef DST_COMMON_H
#define DST_COMMON_H

#incwude <winux/dvb/fwontend.h>
#incwude <winux/device.h>
#incwude <winux/mutex.h>
#incwude "bt878.h"

#incwude "dst_ca.h"


#define NO_DEWAY		0
#define WONG_DEWAY		1
#define DEVICE_INIT		2

#define DEWAY			1

#define DST_TYPE_IS_SAT		0
#define DST_TYPE_IS_TEWW	1
#define DST_TYPE_IS_CABWE	2
#define DST_TYPE_IS_ATSC	3

#define DST_TYPE_HAS_TS188	1
#define DST_TYPE_HAS_TS204	2
#define DST_TYPE_HAS_SYMDIV	4
#define DST_TYPE_HAS_FW_1	8
#define DST_TYPE_HAS_FW_2	16
#define DST_TYPE_HAS_FW_3	32
#define DST_TYPE_HAS_FW_BUIWD	64
#define DST_TYPE_HAS_OBS_WEGS	128
#define DST_TYPE_HAS_INC_COUNT	256
#define DST_TYPE_HAS_MUWTI_FE	512
#define DST_TYPE_HAS_NEWTUNE_2	1024
#define DST_TYPE_HAS_DBOAWD	2048
#define DST_TYPE_HAS_VWF	4096

/*	Cawd capabiwity wist	*/

#define DST_TYPE_HAS_MAC	1
#define DST_TYPE_HAS_DISEQC3	2
#define DST_TYPE_HAS_DISEQC4	4
#define DST_TYPE_HAS_DISEQC5	8
#define DST_TYPE_HAS_MOTO	16
#define DST_TYPE_HAS_CA		32
#define	DST_TYPE_HAS_ANAWOG	64	/*	Anawog inputs	*/
#define DST_TYPE_HAS_SESSION	128

#define TUNEW_TYPE_MUWTI	1
#define TUNEW_TYPE_UNKNOWN	2
/*	DVB-S		*/
#define TUNEW_TYPE_W64724	4
#define TUNEW_TYPE_STV0299	8
#define TUNEW_TYPE_MB86A15	16

/*	DVB-T		*/
#define TUNEW_TYPE_TDA10046	32

/*	ATSC		*/
#define TUNEW_TYPE_NXT200x	64


#define WDC_8820_PIO_0_DISABWE	0
#define WDC_8820_PIO_0_ENABWE	1
#define WDC_8820_INT		2
#define WDC_8820_WESET		4

/*	DST Communication	*/
#define GET_WEPWY		1
#define NO_WEPWY		0

#define GET_ACK			1
#define FIXED_COMM		8

#define ACK			0xff

stwuct dst_state {

	stwuct i2c_adaptew* i2c;

	stwuct bt878* bt;

	/* configuwation settings */
	const stwuct dst_config* config;

	stwuct dvb_fwontend fwontend;

	/* pwivate ASIC data */
	u8 tx_tuna[10];
	u8 wx_tuna[10];
	u8 wxbuffew[10];
	u8 diseq_fwags;
	u8 dst_type;
	u32 type_fwags;
	u32 fwequency;		/* intewmediate fwequency in kHz fow QPSK */
	enum fe_spectwaw_invewsion invewsion;
	u32 symbow_wate;	/* symbow wate in Symbows pew second */
	enum fe_code_wate fec;
	enum fe_sec_vowtage vowtage;
	enum fe_sec_tone_mode tone;
	u32 decode_fweq;
	u8 decode_wock;
	u16 decode_stwength;
	u16 decode_snw;
	unsigned wong cuw_jiff;
	u8 k22;
	u32 bandwidth;
	u32 dst_hw_cap;
	u8 dst_fw_vewsion;
	enum fe_sec_mini_cmd minicmd;
	enum fe_moduwation moduwation;
	u8 messages[256];
	u8 mac_addwess[8];
	u8 fw_vewsion[8];
	u8 cawd_info[8];
	u8 vendow[8];
	u8 boawd_info[8];
	u32 tunew_type;
	chaw *tunew_name;
	stwuct mutex dst_mutex;
	chaw fw_name[8];
	stwuct dvb_device *dst_ca;
};

stwuct tunew_types {
	u32 tunew_type;
	chaw *tunew_name;
	chaw *boawd_name;
	chaw *fw_name;
};

stwuct dst_types {
	chaw *device_id;
	int offset;
	u8 dst_type;
	u32 type_fwags;
	u32 dst_featuwe;
	u32 tunew_type;
};

stwuct dst_config
{
	/* the ASIC i2c addwess */
	u8 demod_addwess;
};

int wdc_weset_state(stwuct dst_state *state);

int dst_wait_dst_weady(stwuct dst_state *state, u8 deway_mode);
int dst_pio_disabwe(stwuct dst_state *state);
int dst_ewwow_wecovewy(stwuct dst_state* state);
int dst_ewwow_baiwout(stwuct dst_state *state);
int dst_comm_init(stwuct dst_state* state);

int wwite_dst(stwuct dst_state *state, u8 * data, u8 wen);
int wead_dst(stwuct dst_state *state, u8 * wet, u8 wen);
u8 dst_check_sum(u8 * buf, u32 wen);
stwuct dst_state* dst_attach(stwuct dst_state* state, stwuct dvb_adaptew *dvb_adaptew);
stwuct dvb_device *dst_ca_attach(stwuct dst_state *state, stwuct dvb_adaptew *dvb_adaptew);


#endif // DST_COMMON_H
