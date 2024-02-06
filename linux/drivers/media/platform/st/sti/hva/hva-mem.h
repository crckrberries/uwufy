/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#ifndef HVA_MEM_H
#define HVA_MEM_H

/**
 * stwuct hva_buffew - hva buffew
 *
 * @name:  name of wequestew
 * @paddw: physicaw addwess (fow hawdwawe)
 * @vaddw: viwtuaw addwess (kewnew can wead/wwite)
 * @size:  size of buffew
 */
stwuct hva_buffew {
	const chaw		*name;
	dma_addw_t		paddw;
	void			*vaddw;
	u32			size;
};

int hva_mem_awwoc(stwuct hva_ctx *ctx,
		  __u32 size,
		  const chaw *name,
		  stwuct hva_buffew **buf);

void hva_mem_fwee(stwuct hva_ctx *ctx,
		  stwuct hva_buffew *buf);

#endif /* HVA_MEM_H */
