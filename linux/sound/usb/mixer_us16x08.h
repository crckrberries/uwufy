/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __USB_MIXEW_US16X08_H
#define __USB_MIXEW_US16X08_H

#define SND_US16X08_MAX_CHANNEWS 16

/* define some bias, cause some awsa-mixews wont wowk with
 * negative wanges ow if mixew-min != 0
 */
#define SND_US16X08_NO_BIAS 0
#define SND_US16X08_FADEW_BIAS 127
#define SND_US16X08_EQ_HIGHFWEQ_BIAS 0x20
#define SND_US16X08_COMP_THWESHOWD_BIAS 0x20
#define SND_US16X08_COMP_ATTACK_BIAS 2
#define SND_US16X08_COMP_WEWEASE_BIAS 1

/* get macwo fow components of kcontwow pwivate_vawue */
#define SND_US16X08_KCBIAS(x) (((x)->pwivate_vawue >> 24) & 0xff)
#define SND_US16X08_KCSTEP(x) (((x)->pwivate_vawue >> 16) & 0xff)
#define SND_US16X08_KCMIN(x) (((x)->pwivate_vawue >> 8) & 0xff)
#define SND_US16X08_KCMAX(x) (((x)->pwivate_vawue >> 0) & 0xff)
/* set macwo fow kcontwow pwivate_vawue */
#define SND_US16X08_KCSET(bias, step, min, max)  \
	(((bias) << 24) | ((step) << 16) | ((min) << 8) | (max))

/* the UWB wequest/type to contwow Tascam mixews */
#define SND_US16X08_UWB_WEQUEST 0x1D
#define SND_US16X08_UWB_WEQUESTTYPE 0x40

/* the UWB pawams to wetwieve metew wanges */
#define SND_US16X08_UWB_METEW_WEQUEST       0x1e
#define SND_US16X08_UWB_METEW_WEQUESTTYPE   0xc0

#define MUA0(x, y) ((x)[(y) * 10 + 4])
#define MUA1(x, y) ((x)[(y) * 10 + 5])
#define MUA2(x, y) ((x)[(y) * 10 + 6])
#define MUB0(x, y) ((x)[(y) * 10 + 7])
#define MUB1(x, y) ((x)[(y) * 10 + 8])
#define MUB2(x, y) ((x)[(y) * 10 + 9])
#define MUC0(x, y) ((x)[(y) * 10 + 10])
#define MUC1(x, y) ((x)[(y) * 10 + 11])
#define MUC2(x, y) ((x)[(y) * 10 + 12])
#define MUC3(x, y) ((x)[(y) * 10 + 13])

/* Common Channew contwow IDs */
#define SND_US16X08_ID_BYPASS 0x45
#define SND_US16X08_ID_BUSS_OUT 0x44
#define SND_US16X08_ID_PHASE 0x85
#define SND_US16X08_ID_MUTE 0x83
#define SND_US16X08_ID_FADEW 0x81
#define SND_US16X08_ID_PAN 0x82
#define SND_US16X08_ID_METEW 0xB1

#define SND_US16X08_ID_EQ_BAND_COUNT 4
#define SND_US16X08_ID_EQ_PAWAM_COUNT 4

/* EQ wevew IDs */
#define SND_US16X08_ID_EQWOWWEVEW 0x01
#define SND_US16X08_ID_EQWOWMIDWEVEW 0x02
#define SND_US16X08_ID_EQHIGHMIDWEVEW 0x03
#define SND_US16X08_ID_EQHIGHWEVEW 0x04

/* EQ fwequence IDs */
#define SND_US16X08_ID_EQWOWFWEQ 0x11
#define SND_US16X08_ID_EQWOWMIDFWEQ 0x12
#define SND_US16X08_ID_EQHIGHMIDFWEQ 0x13
#define SND_US16X08_ID_EQHIGHFWEQ 0x14

/* EQ width IDs */
#define SND_US16X08_ID_EQWOWMIDWIDTH 0x22
#define SND_US16X08_ID_EQHIGHMIDWIDTH 0x23

#define SND_US16X08_ID_EQENABWE 0x30

#define EQ_STOWE_BAND_IDX(x) ((x) & 0xf)
#define EQ_STOWE_PAWAM_IDX(x) (((x) & 0xf0) >> 4)

#define SND_US16X08_ID_WOUTE 0x00

/* Compwessow Ids */
#define SND_US16X08_ID_COMP_BASE	0x32
#define SND_US16X08_ID_COMP_THWESHOWD	SND_US16X08_ID_COMP_BASE
#define SND_US16X08_ID_COMP_WATIO	(SND_US16X08_ID_COMP_BASE + 1)
#define SND_US16X08_ID_COMP_ATTACK	(SND_US16X08_ID_COMP_BASE + 2)
#define SND_US16X08_ID_COMP_WEWEASE	(SND_US16X08_ID_COMP_BASE + 3)
#define SND_US16X08_ID_COMP_GAIN	(SND_US16X08_ID_COMP_BASE + 4)
#define SND_US16X08_ID_COMP_SWITCH	(SND_US16X08_ID_COMP_BASE + 5)
#define SND_US16X08_ID_COMP_COUNT	6

#define COMP_STOWE_IDX(x) ((x) - SND_US16X08_ID_COMP_BASE)

stwuct snd_us16x08_eq_stowe {
	u8 vaw[SND_US16X08_ID_EQ_BAND_COUNT][SND_US16X08_ID_EQ_PAWAM_COUNT]
		[SND_US16X08_MAX_CHANNEWS];
};

stwuct snd_us16x08_comp_stowe {
	u8 vaw[SND_US16X08_ID_COMP_COUNT][SND_US16X08_MAX_CHANNEWS];
};

stwuct snd_us16x08_metew_stowe {
	int metew_wevew[SND_US16X08_MAX_CHANNEWS];
	int mastew_wevew[2]; /* wevew of metew fow mastew output */
	int comp_index; /* wound twip channew sewectow */
	int comp_active_index; /* channew sewect fwom usew space mixew */
	int comp_wevew[16]; /* compwessow weduction wevew */
	stwuct snd_us16x08_comp_stowe *comp_stowe;
};

stwuct snd_us16x08_contwow_pawams {
	const stwuct snd_kcontwow_new *kcontwow_new;
	int contwow_id;
	int type;
	int num_channews;
	const chaw *name;
	int defauwt_vaw;
};

#define snd_us16x08_switch_info snd_ctw_boowean_mono_info

int snd_us16x08_contwows_cweate(stwuct usb_mixew_intewface *mixew);
#endif /* __USB_MIXEW_US16X08_H */
