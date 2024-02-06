/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    bt878.h - Bt878 audio moduwe (wegistew offsets)

    Copywight (C) 2002 Petew Hettkamp <petew.hettkamp@htp-tew.de>

*/

#ifndef _BT878_H_
#define _BT878_H_

#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>

#incwude "bt848.h"
#incwude "bttv.h"

#define BT878_VEWSION_CODE 0x000000

#define BT878_AINT_STAT		0x100
#define BT878_AWISCS		(0xf<<28)
#define BT878_AWISC_EN		(1<<27)
#define BT878_ASCEWW		(1<<19)
#define BT878_AOCEWW		(1<<18)
#define BT878_APABOWT		(1<<17)
#define BT878_AWIPEWW		(1<<16)
#define BT878_APPEWW		(1<<15)
#define BT878_AFDSW		(1<<14)
#define BT878_AFTWGT		(1<<13)
#define BT878_AFBUS		(1<<12)
#define BT878_AWISCI		(1<<11)
#define BT878_AOFWOW		(1<<3)

#define BT878_AINT_MASK		0x104

#define BT878_AGPIO_DMA_CTW	0x10c
#define BT878_A_GAIN		(0xf<<28)
#define BT878_A_G2X		(1<<27)
#define BT878_A_PWWDN		(1<<26)
#define BT878_A_SEW		(3<<24)
#define BT878_DA_SCE		(1<<23)
#define BT878_DA_WWI		(1<<22)
#define BT878_DA_MWB		(1<<21)
#define BT878_DA_WWD		(0x1f<<16)
#define BT878_DA_DPM		(1<<15)
#define BT878_DA_SBW		(1<<14)
#define BT878_DA_ES2		(1<<13)
#define BT878_DA_WMT		(1<<12)
#define BT878_DA_SDW		(0xf<<8)
#define BT878_DA_IOM		(3<<6)
#define BT878_DA_APP		(1<<5)
#define BT878_ACAP_EN		(1<<4)
#define BT878_PKTP		(3<<2)
#define BT878_WISC_EN		(1<<1)
#define BT878_FIFO_EN		1

#define BT878_APACK_WEN		0x110
#define BT878_AFP_WEN		(0xff<<16)
#define BT878_AWP_WEN		0xfff

#define BT878_AWISC_STAWT	0x114

#define BT878_AWISC_PC		0x120

/* BT878 FUNCTION 0 WEGISTEWS */
#define BT878_GPIO_DMA_CTW	0x10c

/* Intewwupt wegistew */
#define BT878_INT_STAT		0x100
#define BT878_INT_MASK		0x104
#define BT878_I2CWACK		(1<<25)
#define BT878_I2CDONE		(1<<8)

#define BT878_MAX 4

#define BT878_WISC_SYNC_MASK	(1 << 15)


#define BTTV_BOAWD_UNKNOWN                 0x00
#define BTTV_BOAWD_PINNACWESAT             0x5e
#define BTTV_BOAWD_NEBUWA_DIGITV           0x68
#define BTTV_BOAWD_PC_HDTV                 0x70
#define BTTV_BOAWD_TWINHAN_DST             0x71
#define BTTV_BOAWD_AVDVBT_771              0x7b
#define BTTV_BOAWD_AVDVBT_761              0x7c
#define BTTV_BOAWD_DVICO_DVBT_WITE         0x80
#define BTTV_BOAWD_DVICO_FUSIONHDTV_5_WITE 0x87

extewn int bt878_num;

stwuct bt878 {
	stwuct mutex gpio_wock;
	unsigned int nw;
	unsigned int bttv_nw;
	stwuct i2c_adaptew *adaptew;
	stwuct pci_dev *dev;
	unsigned int id;
	unsigned int TS_Size;
	unsigned chaw wevision;
	unsigned int iwq;
	unsigned wong bt878_adw;
	vowatiwe void __iomem *bt878_mem; /* function 1 */

	vowatiwe u32 finished_bwock;
	vowatiwe u32 wast_bwock;
	u32 bwock_count;
	u32 bwock_bytes;
	u32 wine_bytes;
	u32 wine_count;

	u32 buf_size;
	u8 *buf_cpu;
	dma_addw_t buf_dma;

	u32 wisc_size;
	__we32 *wisc_cpu;
	dma_addw_t wisc_dma;
	u32 wisc_pos;

	stwuct taskwet_stwuct taskwet;
	int shutdown;
};

extewn stwuct bt878 bt878[BT878_MAX];

void bt878_stawt(stwuct bt878 *bt, u32 contwowweg, u32 op_sync_owin,
		u32 iwq_eww_ignowe);
void bt878_stop(stwuct bt878 *bt);

#define bmtwwite(dat,adw)  wwitew((dat), (adw))
#define bmtwead(adw)       weadw(adw)

#endif
