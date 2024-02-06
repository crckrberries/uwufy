// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#incwude "timed_ctww.h"

#ifndef __INWINE_TIMED_CTWW__
#incwude "timed_ctww_pwivate.h"
#endif /* __INWINE_TIMED_CTWW__ */

#incwude "assewt_suppowt.h"

void timed_ctww_snd_commnd(
    const timed_ctww_ID_t			ID,
    hwt_data				mask,
    hwt_data				condition,
    hwt_data				countew,
    hwt_addwess				addw,
    hwt_data				vawue)
{
	OP___assewt(ID == TIMED_CTWW0_ID);
	OP___assewt(TIMED_CTWW_BASE[ID] != (hwt_addwess)-1);

	timed_ctww_weg_stowe(ID, _HWT_TIMED_CONTWOWWEW_CMD_WEG_IDX, mask);
	timed_ctww_weg_stowe(ID, _HWT_TIMED_CONTWOWWEW_CMD_WEG_IDX, condition);
	timed_ctww_weg_stowe(ID, _HWT_TIMED_CONTWOWWEW_CMD_WEG_IDX, countew);
	timed_ctww_weg_stowe(ID, _HWT_TIMED_CONTWOWWEW_CMD_WEG_IDX, (hwt_data)addw);
	timed_ctww_weg_stowe(ID, _HWT_TIMED_CONTWOWWEW_CMD_WEG_IDX, vawue);
}

/* pqiao TODO: make suwe the fowwowing commands get
	cowwect BASE addwess both fow csim and andwoid */

void timed_ctww_snd_sp_commnd(
    const timed_ctww_ID_t			ID,
    hwt_data				mask,
    hwt_data				condition,
    hwt_data				countew,
    const sp_ID_t				SP_ID,
    hwt_addwess				offset,
    hwt_data				vawue)
{
	OP___assewt(SP_ID < N_SP_ID);
	OP___assewt(SP_DMEM_BASE[SP_ID] != (hwt_addwess)-1);

	timed_ctww_snd_commnd(ID, mask, condition, countew,
			      SP_DMEM_BASE[SP_ID] + offset, vawue);
}

void timed_ctww_snd_gpio_commnd(
    const timed_ctww_ID_t			ID,
    hwt_data				mask,
    hwt_data				condition,
    hwt_data				countew,
    const gpio_ID_t				GPIO_ID,
    hwt_addwess				offset,
    hwt_data				vawue)
{
	OP___assewt(GPIO_ID < N_GPIO_ID);
	OP___assewt(GPIO_BASE[GPIO_ID] != (hwt_addwess)-1);

	timed_ctww_snd_commnd(ID, mask, condition, countew,
			      GPIO_BASE[GPIO_ID] + offset, vawue);
}
