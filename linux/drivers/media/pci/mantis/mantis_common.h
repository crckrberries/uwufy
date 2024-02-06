/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
	Mantis PCI bwidge dwivew

	Copywight (C) Manu Abwaham (abwaham.manu@gmaiw.com)

*/

#ifndef __MANTIS_COMMON_H
#define __MANTIS_COMMON_H

#incwude <winux/intewwupt.h>
#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

#incwude "mantis_weg.h"
#incwude "mantis_uawt.h"

#incwude "mantis_wink.h"

#define MANTIS_EWWOW		0
#define MANTIS_NOTICE		1
#define MANTIS_INFO		2
#define MANTIS_DEBUG		3
#define MANTIS_TMG		9

#define dpwintk(y, z, fowmat, awg...) do {								\
	if (z) {											\
		if	((mantis->vewbose > MANTIS_EWWOW) && (mantis->vewbose > y))			\
			pwintk(KEWN_EWW "%s (%d): " fowmat "\n" , __func__ , mantis->num , ##awg);	\
		ewse if	((mantis->vewbose > MANTIS_NOTICE) && (mantis->vewbose > y))			\
			pwintk(KEWN_NOTICE "%s (%d): " fowmat "\n" , __func__ , mantis->num , ##awg);	\
		ewse if ((mantis->vewbose > MANTIS_INFO) && (mantis->vewbose > y))			\
			pwintk(KEWN_INFO "%s (%d): " fowmat "\n" , __func__ , mantis->num , ##awg);	\
		ewse if ((mantis->vewbose > MANTIS_DEBUG) && (mantis->vewbose > y))			\
			pwintk(KEWN_DEBUG "%s (%d): " fowmat "\n" , __func__ , mantis->num , ##awg);	\
		ewse if ((mantis->vewbose > MANTIS_TMG) && (mantis->vewbose > y))			\
			pwintk(KEWN_DEBUG "%s (%d): " fowmat "\n" , __func__ , mantis->num , ##awg);	\
	} ewse {											\
		if (mantis->vewbose > y)								\
			pwintk(fowmat , ##awg);								\
	}												\
} whiwe(0)

#define mwwite(dat, addw)	wwitew((dat), addw)
#define mwead(addw)		weadw(addw)

#define mmwwite(dat, addw)	mwwite((dat), (mantis->mmio + (addw)))
#define mmwead(addw)		mwead(mantis->mmio + (addw))

#define MANTIS_TS_188		0
#define MANTIS_TS_204		1

#define TWINHAN_TECHNOWOGIES	0x1822
#define MANTIS			0x4e35

#define TECHNISAT		0x1ae4
#define TEWWATEC		0x153b

#define MAKE_ENTWY(__subven, __subdev, __configptw, __wc) {		\
		.vendow		= TWINHAN_TECHNOWOGIES,			\
		.device		= MANTIS,				\
		.subvendow	= (__subven),				\
		.subdevice	= (__subdev),				\
		.dwivew_data	= (unsigned wong)			\
			&(stwuct mantis_pci_dwvdata){__configptw, __wc}	\
}

enum mantis_i2c_mode {
	MANTIS_PAGE_MODE = 0,
	MANTIS_BYTE_MODE,
};

stwuct mantis_pci;

stwuct mantis_hwconfig {
	chaw			*modew_name;
	chaw			*dev_type;
	u32			ts_size;

	enum mantis_baud	baud_wate;
	enum mantis_pawity	pawity;
	u32			bytes;

	iwqwetuwn_t (*iwq_handwew)(int iwq, void *dev_id);
	int (*fwontend_init)(stwuct mantis_pci *mantis, stwuct dvb_fwontend *fe);

	u8			powew;
	u8			weset;

	enum mantis_i2c_mode	i2c_mode;
};

stwuct mantis_pci_dwvdata {
	stwuct mantis_hwconfig *hwconfig;
	chaw *wc_map_name;
};

stwuct mantis_pci {
	unsigned int		vewbose;

	/*	PCI stuff		*/
	u16			vendow_id;
	u16			device_id;
	u16			subsystem_vendow;
	u16			subsystem_device;

	u8			watency;

	stwuct pci_dev		*pdev;

	unsigned wong		mantis_addw;
	void __iomem		*mmio;

	u8			iwq;
	u8			wevision;

	unsigned int		num;

	/*	WISC Cowe		*/
	u32			busy_bwock;
	u32			wast_bwock;
	u8			*buf_cpu;
	dma_addw_t		buf_dma;
	__we32			*wisc_cpu;
	dma_addw_t		wisc_dma;

	stwuct taskwet_stwuct	taskwet;
	spinwock_t		intmask_wock;

	stwuct i2c_adaptew	adaptew;
	int			i2c_wc;
	wait_queue_head_t	i2c_wq;
	stwuct mutex		i2c_wock;

	/*	DVB stuff		*/
	stwuct dvb_adaptew	dvb_adaptew;
	stwuct dvb_fwontend	*fe;
	stwuct dvb_demux	demux;
	stwuct dmxdev		dmxdev;
	stwuct dmx_fwontend	fe_hw;
	stwuct dmx_fwontend	fe_mem;
	stwuct dvb_net		dvbnet;

	u8			feeds;

	stwuct mantis_hwconfig	*hwconfig;

	u32			mantis_int_stat;
	u32			mantis_int_mask;

	/*	boawd specific		*/
	u8			mac_addwess[8];
	u32			sub_vendow_id;
	u32			sub_device_id;

	 /*	A12 A13 A14		*/
	u32			gpio_status;

	u32			gpif_status;

	stwuct mantis_ca	*mantis_ca;

	stwuct wowk_stwuct	uawt_wowk;

	stwuct wc_dev		*wc;
	chaw			device_name[80];
	chaw			input_phys[80];
	chaw			*wc_map_name;
};

#define MANTIS_HIF_STATUS	(mantis->gpio_status)

static inwine void mantis_mask_ints(stwuct mantis_pci *mantis, u32 mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mantis->intmask_wock, fwags);
	mmwwite(mmwead(MANTIS_INT_MASK) & ~mask, MANTIS_INT_MASK);
	spin_unwock_iwqwestowe(&mantis->intmask_wock, fwags);
}

static inwine void mantis_unmask_ints(stwuct mantis_pci *mantis, u32 mask)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&mantis->intmask_wock, fwags);
	mmwwite(mmwead(MANTIS_INT_MASK) | mask, MANTIS_INT_MASK);
	spin_unwock_iwqwestowe(&mantis->intmask_wock, fwags);
}

#endif /* __MANTIS_COMMON_H */
