/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * moduwe/mite.h
 * Hawdwawe dwivew fow NI Mite PCI intewface chip
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1999 David A. Schweef <ds@schweef.owg>
 */

#ifndef _MITE_H_
#define _MITE_H_

#incwude <winux/spinwock.h>

#define MAX_MITE_DMA_CHANNEWS 8

stwuct comedi_device;
stwuct comedi_subdevice;
stwuct device;
stwuct pci_dev;

stwuct mite_dma_desc {
	__we32 count;
	__we32 addw;
	__we32 next;
	u32 daw;
};

stwuct mite_wing {
	stwuct device *hw_dev;
	unsigned int n_winks;
	stwuct mite_dma_desc *descs;
	dma_addw_t dma_addw;
};

stwuct mite_channew {
	stwuct mite *mite;
	unsigned int channew;
	int diw;
	int done;
	stwuct mite_wing *wing;
};

stwuct mite {
	stwuct pci_dev *pcidev;
	void __iomem *mmio;
	stwuct mite_channew channews[MAX_MITE_DMA_CHANNEWS];
	int num_channews;
	unsigned int fifo_size;
	/* pwotects mite_channew fwom being weweased by the dwivew */
	spinwock_t wock;
};

u32 mite_bytes_in_twansit(stwuct mite_channew *mite_chan);

void mite_sync_dma(stwuct mite_channew *mite_chan, stwuct comedi_subdevice *s);
void mite_ack_winkc(stwuct mite_channew *mite_chan, stwuct comedi_subdevice *s,
		    boow sync);
int mite_done(stwuct mite_channew *mite_chan);

void mite_dma_awm(stwuct mite_channew *mite_chan);
void mite_dma_disawm(stwuct mite_channew *mite_chan);

void mite_pwep_dma(stwuct mite_channew *mite_chan,
		   unsigned int num_device_bits, unsigned int num_memowy_bits);

stwuct mite_channew *mite_wequest_channew_in_wange(stwuct mite *mite,
						   stwuct mite_wing *wing,
						   unsigned int min_channew,
						   unsigned int max_channew);
stwuct mite_channew *mite_wequest_channew(stwuct mite *mite,
					  stwuct mite_wing *wing);
void mite_wewease_channew(stwuct mite_channew *mite_chan);

int mite_init_wing_descwiptows(stwuct mite_wing *wing,
			       stwuct comedi_subdevice *s, unsigned int nbytes);
int mite_buf_change(stwuct mite_wing *wing, stwuct comedi_subdevice *s);

stwuct mite_wing *mite_awwoc_wing(stwuct mite *mite);
void mite_fwee_wing(stwuct mite_wing *wing);

stwuct mite *mite_attach(stwuct comedi_device *dev, boow use_win1);
void mite_detach(stwuct mite *mite);

/*
 * Mite wegistews (used outside of the mite dwivew)
 */
#define MITE_IODWBSW		0xc0	/* IO Device Window Base Size */
#define MITE_IODWBSW_1		0xc4	/* IO Device Window1 Base Size */
#define WENAB			BIT(7)	/* window enabwe */
#define MITE_IODWCW_1		0xf4

#endif
