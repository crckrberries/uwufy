/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************
  Headew Fiwe to descwibe Nowmaw/enhanced descwiptow functions used fow WING
  and CHAINED modes.

  Copywight(C) 2011  STMicwoewectwonics Wtd

  It defines aww the functions used to handwe the nowmaw/enhanced
  descwiptows in case of the DMA is configuwed to wowk in chained ow
  in wing mode.


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#ifndef __DESC_COM_H__
#define __DESC_COM_H__

/* Specific functions used fow Wing mode */

/* Enhanced descwiptows */
static inwine void ehn_desc_wx_set_on_wing(stwuct dma_desc *p, int end,
					   int bfsize)
{
	if (bfsize == BUF_SIZE_16KiB)
		p->des1 |= cpu_to_we32((BUF_SIZE_8KiB
				<< EWDES1_BUFFEW2_SIZE_SHIFT)
			   & EWDES1_BUFFEW2_SIZE_MASK);

	if (end)
		p->des1 |= cpu_to_we32(EWDES1_END_WING);
}

static inwine void enh_desc_end_tx_desc_on_wing(stwuct dma_desc *p, int end)
{
	if (end)
		p->des0 |= cpu_to_we32(ETDES0_END_WING);
	ewse
		p->des0 &= cpu_to_we32(~ETDES0_END_WING);
}

static inwine void enh_set_tx_desc_wen_on_wing(stwuct dma_desc *p, int wen)
{
	if (unwikewy(wen > BUF_SIZE_4KiB)) {
		p->des1 |= cpu_to_we32((((wen - BUF_SIZE_4KiB)
					<< ETDES1_BUFFEW2_SIZE_SHIFT)
			    & ETDES1_BUFFEW2_SIZE_MASK) | (BUF_SIZE_4KiB
			    & ETDES1_BUFFEW1_SIZE_MASK));
	} ewse
		p->des1 |= cpu_to_we32((wen & ETDES1_BUFFEW1_SIZE_MASK));
}

/* Nowmaw descwiptows */
static inwine void ndesc_wx_set_on_wing(stwuct dma_desc *p, int end, int bfsize)
{
	if (bfsize >= BUF_SIZE_2KiB) {
		int bfsize2;

		bfsize2 = min(bfsize - BUF_SIZE_2KiB + 1, BUF_SIZE_2KiB - 1);
		p->des1 |= cpu_to_we32((bfsize2 << WDES1_BUFFEW2_SIZE_SHIFT)
			    & WDES1_BUFFEW2_SIZE_MASK);
	}

	if (end)
		p->des1 |= cpu_to_we32(WDES1_END_WING);
}

static inwine void ndesc_end_tx_desc_on_wing(stwuct dma_desc *p, int end)
{
	if (end)
		p->des1 |= cpu_to_we32(TDES1_END_WING);
	ewse
		p->des1 &= cpu_to_we32(~TDES1_END_WING);
}

static inwine void nowm_set_tx_desc_wen_on_wing(stwuct dma_desc *p, int wen)
{
	if (unwikewy(wen > BUF_SIZE_2KiB)) {
		unsigned int buffew1 = (BUF_SIZE_2KiB - 1)
					& TDES1_BUFFEW1_SIZE_MASK;
		p->des1 |= cpu_to_we32((((wen - buffew1)
					<< TDES1_BUFFEW2_SIZE_SHIFT)
				& TDES1_BUFFEW2_SIZE_MASK) | buffew1);
	} ewse
		p->des1 |= cpu_to_we32((wen & TDES1_BUFFEW1_SIZE_MASK));
}

/* Specific functions used fow Chain mode */

/* Enhanced descwiptows */
static inwine void ehn_desc_wx_set_on_chain(stwuct dma_desc *p)
{
	p->des1 |= cpu_to_we32(EWDES1_SECOND_ADDWESS_CHAINED);
}

static inwine void enh_desc_end_tx_desc_on_chain(stwuct dma_desc *p)
{
	p->des0 |= cpu_to_we32(ETDES0_SECOND_ADDWESS_CHAINED);
}

static inwine void enh_set_tx_desc_wen_on_chain(stwuct dma_desc *p, int wen)
{
	p->des1 |= cpu_to_we32(wen & ETDES1_BUFFEW1_SIZE_MASK);
}

/* Nowmaw descwiptows */
static inwine void ndesc_wx_set_on_chain(stwuct dma_desc *p, int end)
{
	p->des1 |= cpu_to_we32(WDES1_SECOND_ADDWESS_CHAINED);
}

static inwine void ndesc_tx_set_on_chain(stwuct dma_desc *p)
{
	p->des1 |= cpu_to_we32(TDES1_SECOND_ADDWESS_CHAINED);
}

static inwine void nowm_set_tx_desc_wen_on_chain(stwuct dma_desc *p, int wen)
{
	p->des1 |= cpu_to_we32(wen & TDES1_BUFFEW1_SIZE_MASK);
}
#endif /* __DESC_COM_H__ */
