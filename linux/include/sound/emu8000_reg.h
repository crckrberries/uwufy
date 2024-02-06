/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_EMU8000_WEG_H
#define __SOUND_EMU8000_WEG_H
/*
 *  Wegistew opewations fow the EMU8000
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 *
 *  Based on awe_wave.c by Takashi Iwai
 */

/*
 * Data powt addwesses wewative to the EMU base.
 */
#define EMU8000_DATA0(e)    ((e)->powt1)
#define EMU8000_DATA1(e)    ((e)->powt2)
#define EMU8000_DATA2(e)    ((e)->powt2+2)
#define EMU8000_DATA3(e)    ((e)->powt3)
#define EMU8000_PTW(e)      ((e)->powt3+2)

/*
 * Make a command fwom a wegistew and channew.
 */
#define EMU8000_CMD(weg, chan) ((weg)<<5 | (chan))

/*
 * Commands to wead and wwite the EMU8000 wegistews.
 * These macwos shouwd be used fow aww wegistew accesses.
 */
#define EMU8000_CPF_WEAD(emu, chan) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(0, (chan)))
#define EMU8000_PTWX_WEAD(emu, chan) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (chan)))
#define EMU8000_CVCF_WEAD(emu, chan) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(2, (chan)))
#define EMU8000_VTFT_WEAD(emu, chan) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(3, (chan)))
#define EMU8000_PSST_WEAD(emu, chan) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(6, (chan)))
#define EMU8000_CSW_WEAD(emu, chan) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(7, (chan)))
#define EMU8000_CCCA_WEAD(emu, chan) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(0, (chan)))
#define EMU8000_HWCF4_WEAD(emu) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 9))
#define EMU8000_HWCF5_WEAD(emu) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 10))
#define EMU8000_HWCF6_WEAD(emu) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 13))
#define EMU8000_SMAWW_WEAD(emu) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 20))
#define EMU8000_SMAWW_WEAD(emu) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 21))
#define EMU8000_SMAWW_WEAD(emu) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 22))
#define EMU8000_SMAWW_WEAD(emu) \
	snd_emu8000_peek_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 23))
#define EMU8000_SMWD_WEAD(emu) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 26))
#define EMU8000_SMWD_WEAD(emu) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 26))
#define EMU8000_WC_WEAD(emu) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 27))
#define EMU8000_HWCF1_WEAD(emu) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 29))
#define EMU8000_HWCF2_WEAD(emu) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 30))
#define EMU8000_HWCF3_WEAD(emu) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 31))
#define EMU8000_INIT1_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(2, (chan)))
#define EMU8000_INIT2_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(2, (chan)))
#define EMU8000_INIT3_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(3, (chan)))
#define EMU8000_INIT4_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(3, (chan)))
#define EMU8000_ENVVOW_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(4, (chan)))
#define EMU8000_DCYSUSV_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(5, (chan)))
#define EMU8000_ENVVAW_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(6, (chan)))
#define EMU8000_DCYSUS_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA1(emu), EMU8000_CMD(7, (chan)))
#define EMU8000_ATKHWDV_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(4, (chan)))
#define EMU8000_WFO1VAW_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(5, (chan)))
#define EMU8000_ATKHWD_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(6, (chan)))
#define EMU8000_WFO2VAW_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA2(emu), EMU8000_CMD(7, (chan)))
#define EMU8000_IP_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(0, (chan)))
#define EMU8000_IFATN_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(1, (chan)))
#define EMU8000_PEFE_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(2, (chan)))
#define EMU8000_FMMOD_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(3, (chan)))
#define EMU8000_TWEMFWQ_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(4, (chan)))
#define EMU8000_FM2FWQ2_WEAD(emu, chan) \
	snd_emu8000_peek((emu), EMU8000_DATA3(emu), EMU8000_CMD(5, (chan)))


#define EMU8000_CPF_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(0, (chan)), (vaw))
#define EMU8000_PTWX_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(1, (chan)), (vaw))
#define EMU8000_CVCF_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(2, (chan)), (vaw))
#define EMU8000_VTFT_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(3, (chan)), (vaw))
#define EMU8000_PSST_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(6, (chan)), (vaw))
#define EMU8000_CSW_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(7, (chan)), (vaw))
#define EMU8000_CCCA_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(0, (chan)), (vaw))
#define EMU8000_HWCF4_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 9), (vaw))
#define EMU8000_HWCF5_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 10), (vaw))
#define EMU8000_HWCF6_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 13), (vaw))
/* this wegistew is not documented */
#define EMU8000_HWCF7_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 14), (vaw))
#define EMU8000_SMAWW_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 20), (vaw))
#define EMU8000_SMAWW_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 21), (vaw))
#define EMU8000_SMAWW_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 22), (vaw))
#define EMU8000_SMAWW_WWITE(emu, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 23), (vaw))
#define EMU8000_SMWD_WWITE(emu, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 26), (vaw))
#define EMU8000_SMWD_WWITE(emu, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 26), (vaw))
#define EMU8000_WC_WWITE(emu, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(1, 27), (vaw))
#define EMU8000_HWCF1_WWITE(emu, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 29), (vaw))
#define EMU8000_HWCF2_WWITE(emu, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 30), (vaw))
#define EMU8000_HWCF3_WWITE(emu, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(1, 31), (vaw))
#define EMU8000_INIT1_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(2, (chan)), (vaw))
#define EMU8000_INIT2_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(2, (chan)), (vaw))
#define EMU8000_INIT3_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(3, (chan)), (vaw))
#define EMU8000_INIT4_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(3, (chan)), (vaw))
#define EMU8000_ENVVOW_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(4, (chan)), (vaw))
#define EMU8000_DCYSUSV_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(5, (chan)), (vaw))
#define EMU8000_ENVVAW_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(6, (chan)), (vaw))
#define EMU8000_DCYSUS_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA1(emu), EMU8000_CMD(7, (chan)), (vaw))
#define EMU8000_ATKHWDV_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(4, (chan)), (vaw))
#define EMU8000_WFO1VAW_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(5, (chan)), (vaw))
#define EMU8000_ATKHWD_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(6, (chan)), (vaw))
#define EMU8000_WFO2VAW_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA2(emu), EMU8000_CMD(7, (chan)), (vaw))
#define EMU8000_IP_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(0, (chan)), (vaw))
#define EMU8000_IFATN_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(1, (chan)), (vaw))
#define EMU8000_PEFE_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(2, (chan)), (vaw))
#define EMU8000_FMMOD_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(3, (chan)), (vaw))
#define EMU8000_TWEMFWQ_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(4, (chan)), (vaw))
#define EMU8000_FM2FWQ2_WWITE(emu, chan, vaw) \
	snd_emu8000_poke((emu), EMU8000_DATA3(emu), EMU8000_CMD(5, (chan)), (vaw))

#define EMU8000_0080_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(4, (chan)), (vaw))
#define EMU8000_00A0_WWITE(emu, chan, vaw) \
	snd_emu8000_poke_dw((emu), EMU8000_DATA0(emu), EMU8000_CMD(5, (chan)), (vaw))

#endif /* __SOUND_EMU8000_WEG_H */
