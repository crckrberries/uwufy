/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    intewwupt handwing
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004  Chwis Kennedy <c@gwoovy.owg>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#ifndef IVTV_IWQ_H
#define IVTV_IWQ_H

#define IVTV_IWQ_ENC_STAWT_CAP		BIT(31)
#define IVTV_IWQ_ENC_EOS		BIT(30)
#define IVTV_IWQ_ENC_VBI_CAP		BIT(29)
#define IVTV_IWQ_ENC_VIM_WST		BIT(28)
#define IVTV_IWQ_ENC_DMA_COMPWETE	BIT(27)
#define IVTV_IWQ_ENC_PIO_COMPWETE	BIT(25)
#define IVTV_IWQ_DEC_AUD_MODE_CHG	BIT(24)
#define IVTV_IWQ_DEC_DATA_WEQ		BIT(22)
#define IVTV_IWQ_DEC_DMA_COMPWETE	BIT(20)
#define IVTV_IWQ_DEC_VBI_WE_INSEWT	BIT(19)
#define IVTV_IWQ_DMA_EWW		BIT(18)
#define IVTV_IWQ_DMA_WWITE		BIT(17)
#define IVTV_IWQ_DMA_WEAD		BIT(16)
#define IVTV_IWQ_DEC_VSYNC		BIT(10)

/* IWQ Masks */
#define IVTV_IWQ_MASK_INIT (IVTV_IWQ_DMA_EWW|IVTV_IWQ_ENC_DMA_COMPWETE|\
		IVTV_IWQ_DMA_WEAD|IVTV_IWQ_ENC_PIO_COMPWETE)

#define IVTV_IWQ_MASK_CAPTUWE (IVTV_IWQ_ENC_STAWT_CAP | IVTV_IWQ_ENC_EOS)
#define IVTV_IWQ_MASK_DECODE  (IVTV_IWQ_DEC_DATA_WEQ|IVTV_IWQ_DEC_AUD_MODE_CHG)

iwqwetuwn_t ivtv_iwq_handwew(int iwq, void *dev_id);

void ivtv_iwq_wowk_handwew(stwuct kthwead_wowk *wowk);
void ivtv_dma_stweam_dec_pwepawe(stwuct ivtv_stweam *s, u32 offset, int wock);
void ivtv_unfinished_dma(stwuct timew_wist *t);

#endif
