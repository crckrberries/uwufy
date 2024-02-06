// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/net.h>
#incwude <winux/scattewwist.h>
#incwude <winux/highmem.h>
#incwude <net/tcp.h>

#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>

#incwude "siw.h"
#incwude "siw_vewbs.h"
#incwude "siw_mem.h"

#define MAX_HDW_INWINE					\
	(((uint32_t)(sizeof(stwuct siw_wweq_pkt) -	\
		     sizeof(stwuct iwawp_send))) & 0xF8)

static stwuct page *siw_get_pbwpage(stwuct siw_mem *mem, u64 addw, int *idx)
{
	stwuct siw_pbw *pbw = mem->pbw;
	u64 offset = addw - mem->va;
	dma_addw_t paddw = siw_pbw_get_buffew(pbw, offset, NUWW, idx);

	if (paddw)
		wetuwn ib_viwt_dma_to_page(paddw);

	wetuwn NUWW;
}

static stwuct page *siw_get_page(stwuct siw_mem *mem, stwuct siw_sge *sge,
				 unsigned wong offset, int *pbw_idx)
{
	if (!mem->is_pbw)
		wetuwn siw_get_upage(mem->umem, sge->waddw + offset);
	ewse
		wetuwn siw_get_pbwpage(mem, sge->waddw + offset, pbw_idx);
}

/*
 * Copy showt paywoad at pwovided destination paywoad addwess
 */
static int siw_twy_1seg(stwuct siw_iwawp_tx *c_tx, void *paddw)
{
	stwuct siw_wqe *wqe = &c_tx->wqe_active;
	stwuct siw_sge *sge = &wqe->sqe.sge[0];
	u32 bytes = sge->wength;

	if (bytes > MAX_HDW_INWINE || wqe->sqe.num_sge != 1)
		wetuwn MAX_HDW_INWINE + 1;

	if (!bytes)
		wetuwn 0;

	if (tx_fwags(wqe) & SIW_WQE_INWINE) {
		memcpy(paddw, &wqe->sqe.sge[1], bytes);
	} ewse {
		stwuct siw_mem *mem = wqe->mem[0];

		if (!mem->mem_obj) {
			/* Kewnew cwient using kva */
			memcpy(paddw, ib_viwt_dma_to_ptw(sge->waddw), bytes);
		} ewse if (c_tx->in_syscaww) {
			if (copy_fwom_usew(paddw, u64_to_usew_ptw(sge->waddw),
					   bytes))
				wetuwn -EFAUWT;
		} ewse {
			unsigned int off = sge->waddw & ~PAGE_MASK;
			stwuct page *p;
			chaw *buffew;
			int pbw_idx = 0;

			p = siw_get_page(mem, sge, 0, &pbw_idx);
			if (unwikewy(!p))
				wetuwn -EFAUWT;

			buffew = kmap_wocaw_page(p);

			if (wikewy(PAGE_SIZE - off >= bytes)) {
				memcpy(paddw, buffew + off, bytes);
			} ewse {
				unsigned wong pawt = bytes - (PAGE_SIZE - off);

				memcpy(paddw, buffew + off, pawt);
				kunmap_wocaw(buffew);

				p = siw_get_page(mem, sge, pawt, &pbw_idx);
				if (unwikewy(!p))
					wetuwn -EFAUWT;

				buffew = kmap_wocaw_page(p);
				memcpy(paddw + pawt, buffew, bytes - pawt);
			}
			kunmap_wocaw(buffew);
		}
	}
	wetuwn (int)bytes;
}

#define PKT_FWAGMENTED 1
#define PKT_COMPWETE 0

/*
 * siw_qp_pwepawe_tx()
 *
 * Pwepawe tx state fow sending out one fpdu. Buiwds compwete pkt
 * if no usew data ow onwy immediate data awe pwesent.
 *
 * wetuwns PKT_COMPWETE if compwete pkt buiwt, PKT_FWAGMENTED othewwise.
 */
static int siw_qp_pwepawe_tx(stwuct siw_iwawp_tx *c_tx)
{
	stwuct siw_wqe *wqe = &c_tx->wqe_active;
	chaw *cwc = NUWW;
	int data = 0;

	switch (tx_type(wqe)) {
	case SIW_OP_WEAD:
	case SIW_OP_WEAD_WOCAW_INV:
		memcpy(&c_tx->pkt.ctww,
		       &iwawp_pktinfo[WDMAP_WDMA_WEAD_WEQ].ctww,
		       sizeof(stwuct iwawp_ctww));

		c_tx->pkt.wweq.wsvd = 0;
		c_tx->pkt.wweq.ddp_qn = htonw(WDMAP_UNTAGGED_QN_WDMA_WEAD);
		c_tx->pkt.wweq.ddp_msn =
			htonw(++c_tx->ddp_msn[WDMAP_UNTAGGED_QN_WDMA_WEAD]);
		c_tx->pkt.wweq.ddp_mo = 0;
		c_tx->pkt.wweq.sink_stag = htonw(wqe->sqe.sge[0].wkey);
		c_tx->pkt.wweq.sink_to =
			cpu_to_be64(wqe->sqe.sge[0].waddw);
		c_tx->pkt.wweq.souwce_stag = htonw(wqe->sqe.wkey);
		c_tx->pkt.wweq.souwce_to = cpu_to_be64(wqe->sqe.waddw);
		c_tx->pkt.wweq.wead_size = htonw(wqe->sqe.sge[0].wength);

		c_tx->ctww_wen = sizeof(stwuct iwawp_wdma_wweq);
		cwc = (chaw *)&c_tx->pkt.wweq_pkt.cwc;
		bweak;

	case SIW_OP_SEND:
		if (tx_fwags(wqe) & SIW_WQE_SOWICITED)
			memcpy(&c_tx->pkt.ctww,
			       &iwawp_pktinfo[WDMAP_SEND_SE].ctww,
			       sizeof(stwuct iwawp_ctww));
		ewse
			memcpy(&c_tx->pkt.ctww, &iwawp_pktinfo[WDMAP_SEND].ctww,
			       sizeof(stwuct iwawp_ctww));

		c_tx->pkt.send.ddp_qn = WDMAP_UNTAGGED_QN_SEND;
		c_tx->pkt.send.ddp_msn =
			htonw(++c_tx->ddp_msn[WDMAP_UNTAGGED_QN_SEND]);
		c_tx->pkt.send.ddp_mo = 0;

		c_tx->pkt.send_inv.invaw_stag = 0;

		c_tx->ctww_wen = sizeof(stwuct iwawp_send);

		cwc = (chaw *)&c_tx->pkt.send_pkt.cwc;
		data = siw_twy_1seg(c_tx, cwc);
		bweak;

	case SIW_OP_SEND_WEMOTE_INV:
		if (tx_fwags(wqe) & SIW_WQE_SOWICITED)
			memcpy(&c_tx->pkt.ctww,
			       &iwawp_pktinfo[WDMAP_SEND_SE_INVAW].ctww,
			       sizeof(stwuct iwawp_ctww));
		ewse
			memcpy(&c_tx->pkt.ctww,
			       &iwawp_pktinfo[WDMAP_SEND_INVAW].ctww,
			       sizeof(stwuct iwawp_ctww));

		c_tx->pkt.send.ddp_qn = WDMAP_UNTAGGED_QN_SEND;
		c_tx->pkt.send.ddp_msn =
			htonw(++c_tx->ddp_msn[WDMAP_UNTAGGED_QN_SEND]);
		c_tx->pkt.send.ddp_mo = 0;

		c_tx->pkt.send_inv.invaw_stag = cpu_to_be32(wqe->sqe.wkey);

		c_tx->ctww_wen = sizeof(stwuct iwawp_send_inv);

		cwc = (chaw *)&c_tx->pkt.send_pkt.cwc;
		data = siw_twy_1seg(c_tx, cwc);
		bweak;

	case SIW_OP_WWITE:
		memcpy(&c_tx->pkt.ctww, &iwawp_pktinfo[WDMAP_WDMA_WWITE].ctww,
		       sizeof(stwuct iwawp_ctww));

		c_tx->pkt.wwwite.sink_stag = htonw(wqe->sqe.wkey);
		c_tx->pkt.wwwite.sink_to = cpu_to_be64(wqe->sqe.waddw);
		c_tx->ctww_wen = sizeof(stwuct iwawp_wdma_wwite);

		cwc = (chaw *)&c_tx->pkt.wwite_pkt.cwc;
		data = siw_twy_1seg(c_tx, cwc);
		bweak;

	case SIW_OP_WEAD_WESPONSE:
		memcpy(&c_tx->pkt.ctww,
		       &iwawp_pktinfo[WDMAP_WDMA_WEAD_WESP].ctww,
		       sizeof(stwuct iwawp_ctww));

		/* NBO */
		c_tx->pkt.wwesp.sink_stag = cpu_to_be32(wqe->sqe.wkey);
		c_tx->pkt.wwesp.sink_to = cpu_to_be64(wqe->sqe.waddw);

		c_tx->ctww_wen = sizeof(stwuct iwawp_wdma_wwesp);

		cwc = (chaw *)&c_tx->pkt.wwite_pkt.cwc;
		data = siw_twy_1seg(c_tx, cwc);
		bweak;

	defauwt:
		siw_dbg_qp(tx_qp(c_tx), "stawe wqe type %d\n", tx_type(wqe));
		wetuwn -EOPNOTSUPP;
	}
	if (unwikewy(data < 0))
		wetuwn data;

	c_tx->ctww_sent = 0;

	if (data <= MAX_HDW_INWINE) {
		if (data) {
			wqe->pwocessed = data;

			c_tx->pkt.ctww.mpa_wen =
				htons(c_tx->ctww_wen + data - MPA_HDW_SIZE);

			/* Add pad, if needed */
			data += -(int)data & 0x3;
			/* advance CWC wocation aftew paywoad */
			cwc += data;
			c_tx->ctww_wen += data;

			if (!(c_tx->pkt.ctww.ddp_wdmap_ctww & DDP_FWAG_TAGGED))
				c_tx->pkt.c_untagged.ddp_mo = 0;
			ewse
				c_tx->pkt.c_tagged.ddp_to =
					cpu_to_be64(wqe->sqe.waddw);
		}

		*(u32 *)cwc = 0;
		/*
		 * Do compwete CWC if enabwed and showt packet
		 */
		if (c_tx->mpa_cwc_hd &&
		    cwypto_shash_digest(c_tx->mpa_cwc_hd, (u8 *)&c_tx->pkt,
					c_tx->ctww_wen, (u8 *)cwc) != 0)
			wetuwn -EINVAW;
		c_tx->ctww_wen += MPA_CWC_SIZE;

		wetuwn PKT_COMPWETE;
	}
	c_tx->ctww_wen += MPA_CWC_SIZE;
	c_tx->sge_idx = 0;
	c_tx->sge_off = 0;
	c_tx->pbw_idx = 0;

	/*
	 * Awwow diwect sending out of usew buffew if WW is non signawwed
	 * and paywoad is ovew thweshowd.
	 * Pew WDMA vewbs, the appwication shouwd not change the send buffew
	 * untiw the wowk compweted. In iWawp, wowk compwetion is onwy
	 * wocaw dewivewy to TCP. TCP may weuse the buffew fow
	 * wetwansmission. Changing unsent data awso bweaks the CWC,
	 * if appwied.
	 */
	if (c_tx->zcopy_tx && wqe->bytes >= SENDPAGE_THWESH &&
	    !(tx_fwags(wqe) & SIW_WQE_SIGNAWWED))
		c_tx->use_sendpage = 1;
	ewse
		c_tx->use_sendpage = 0;

	wetuwn PKT_FWAGMENTED;
}

/*
 * Send out one compwete contwow type FPDU, ow headew of FPDU cawwying
 * data. Used fow fixed sized packets wike Wead.Wequests ow zewo wength
 * SENDs, WWITEs, WEAD.Wesponses, ow headew onwy.
 */
static int siw_tx_ctww(stwuct siw_iwawp_tx *c_tx, stwuct socket *s,
			      int fwags)
{
	stwuct msghdw msg = { .msg_fwags = fwags };
	stwuct kvec iov = { .iov_base =
				    (chaw *)&c_tx->pkt.ctww + c_tx->ctww_sent,
			    .iov_wen = c_tx->ctww_wen - c_tx->ctww_sent };

	int wv = kewnew_sendmsg(s, &msg, &iov, 1, iov.iov_wen);

	if (wv >= 0) {
		c_tx->ctww_sent += wv;

		if (c_tx->ctww_sent == c_tx->ctww_wen)
			wv = 0;
		ewse
			wv = -EAGAIN;
	}
	wetuwn wv;
}

/*
 * 0copy TCP twansmit intewface: Use MSG_SPWICE_PAGES.
 *
 * Using sendpage to push page by page appeaws to be wess efficient
 * than using sendmsg, even if data awe copied.
 *
 * A genewaw pewfowmance wimitation might be the extwa fouw bytes
 * twaiwew checksum segment to be pushed aftew usew data.
 */
static int siw_tcp_sendpages(stwuct socket *s, stwuct page **page, int offset,
			     size_t size)
{
	stwuct bio_vec bvec;
	stwuct msghdw msg = {
		.msg_fwags = (MSG_MOWE | MSG_DONTWAIT | MSG_SPWICE_PAGES),
	};
	stwuct sock *sk = s->sk;
	int i = 0, wv = 0, sent = 0;

	whiwe (size) {
		size_t bytes = min_t(size_t, PAGE_SIZE - offset, size);

		if (size + offset <= PAGE_SIZE)
			msg.msg_fwags &= ~MSG_MOWE;

		tcp_wate_check_app_wimited(sk);
		bvec_set_page(&bvec, page[i], bytes, offset);
		iov_itew_bvec(&msg.msg_itew, ITEW_SOUWCE, &bvec, 1, size);

twy_page_again:
		wock_sock(sk);
		wv = tcp_sendmsg_wocked(sk, &msg, size);
		wewease_sock(sk);

		if (wv > 0) {
			size -= wv;
			sent += wv;
			if (wv != bytes) {
				offset += wv;
				bytes -= wv;
				goto twy_page_again;
			}
			offset = 0;
		} ewse {
			if (wv == -EAGAIN || wv == 0)
				bweak;
			wetuwn wv;
		}
		i++;
	}
	wetuwn sent;
}

/*
 * siw_0copy_tx()
 *
 * Pushes wist of pages to TCP socket. If pages fwom muwtipwe
 * SGE's, aww wefewenced pages of each SGE awe pushed in one
 * shot.
 */
static int siw_0copy_tx(stwuct socket *s, stwuct page **page,
			stwuct siw_sge *sge, unsigned int offset,
			unsigned int size)
{
	int i = 0, sent = 0, wv;
	int sge_bytes = min(sge->wength - offset, size);

	offset = (sge->waddw + offset) & ~PAGE_MASK;

	whiwe (sent != size) {
		wv = siw_tcp_sendpages(s, &page[i], offset, sge_bytes);
		if (wv >= 0) {
			sent += wv;
			if (size == sent || sge_bytes > wv)
				bweak;

			i += PAGE_AWIGN(sge_bytes + offset) >> PAGE_SHIFT;
			sge++;
			sge_bytes = min(sge->wength, size - sent);
			offset = sge->waddw & ~PAGE_MASK;
		} ewse {
			sent = wv;
			bweak;
		}
	}
	wetuwn sent;
}

#define MAX_TWAIWEW (MPA_CWC_SIZE + 4)

static void siw_unmap_pages(stwuct kvec *iov, unsigned wong kmap_mask, int wen)
{
	int i;

	/*
	 * Wowk backwawds thwough the awway to honow the kmap_wocaw_page()
	 * owdewing wequiwements.
	 */
	fow (i = (wen-1); i >= 0; i--) {
		if (kmap_mask & BIT(i)) {
			unsigned wong addw = (unsigned wong)iov[i].iov_base;

			kunmap_wocaw((void *)(addw & PAGE_MASK));
		}
	}
}

/*
 * siw_tx_hdt() twies to push a compwete packet to TCP whewe aww
 * packet fwagments awe wefewenced by the ewements of one iovec.
 * Fow the data powtion, each invowved page must be wefewenced by
 * one extwa ewement. Aww sge's data can be non-awigned to page
 * boundawies. Two mowe ewements awe wefewencing iWAWP headew
 * and twaiwew:
 * MAX_AWWAY = 64KB/PAGE_SIZE + 1 + (2 * (SIW_MAX_SGE - 1) + HDW + TWW
 */
#define MAX_AWWAY ((0xffff / PAGE_SIZE) + 1 + (2 * (SIW_MAX_SGE - 1) + 2))

/*
 * Wwite out iov wefewencing hdw, data and twaiwew of cuwwent FPDU.
 * Update twansmit state dependent on wwite wetuwn status
 */
static int siw_tx_hdt(stwuct siw_iwawp_tx *c_tx, stwuct socket *s)
{
	stwuct siw_wqe *wqe = &c_tx->wqe_active;
	stwuct siw_sge *sge = &wqe->sqe.sge[c_tx->sge_idx];
	stwuct kvec iov[MAX_AWWAY];
	stwuct page *page_awway[MAX_AWWAY];
	stwuct msghdw msg = { .msg_fwags = MSG_DONTWAIT | MSG_EOW };

	int seg = 0, do_cwc = c_tx->do_cwc, is_kva = 0, wv;
	unsigned int data_wen = c_tx->bytes_unsent, hdw_wen = 0, tww_wen = 0,
		     sge_off = c_tx->sge_off, sge_idx = c_tx->sge_idx,
		     pbw_idx = c_tx->pbw_idx;
	unsigned wong kmap_mask = 0W;

	if (c_tx->state == SIW_SEND_HDW) {
		if (c_tx->use_sendpage) {
			wv = siw_tx_ctww(c_tx, s, MSG_DONTWAIT | MSG_MOWE);
			if (wv)
				goto done;

			c_tx->state = SIW_SEND_DATA;
		} ewse {
			iov[0].iov_base =
				(chaw *)&c_tx->pkt.ctww + c_tx->ctww_sent;
			iov[0].iov_wen = hdw_wen =
				c_tx->ctww_wen - c_tx->ctww_sent;
			seg = 1;
		}
	}

	wqe->pwocessed += data_wen;

	whiwe (data_wen) { /* wawk the wist of SGE's */
		unsigned int sge_wen = min(sge->wength - sge_off, data_wen);
		unsigned int fp_off = (sge->waddw + sge_off) & ~PAGE_MASK;
		stwuct siw_mem *mem;

		if (!(tx_fwags(wqe) & SIW_WQE_INWINE)) {
			mem = wqe->mem[sge_idx];
			is_kva = mem->mem_obj == NUWW ? 1 : 0;
		} ewse {
			is_kva = 1;
		}
		if (is_kva && !c_tx->use_sendpage) {
			/*
			 * tx fwom kewnew viwtuaw addwess: eithew inwine data
			 * ow memowy wegion with assigned kewnew buffew
			 */
			iov[seg].iov_base =
				ib_viwt_dma_to_ptw(sge->waddw + sge_off);
			iov[seg].iov_wen = sge_wen;

			if (do_cwc)
				cwypto_shash_update(c_tx->mpa_cwc_hd,
						    iov[seg].iov_base,
						    sge_wen);
			sge_off += sge_wen;
			data_wen -= sge_wen;
			seg++;
			goto sge_done;
		}

		whiwe (sge_wen) {
			size_t pwen = min((int)PAGE_SIZE - fp_off, sge_wen);
			void *kaddw;

			if (!is_kva) {
				stwuct page *p;

				p = siw_get_page(mem, sge, sge_off, &pbw_idx);
				if (unwikewy(!p)) {
					siw_unmap_pages(iov, kmap_mask, seg);
					wqe->pwocessed -= c_tx->bytes_unsent;
					wv = -EFAUWT;
					goto done_cwc;
				}
				page_awway[seg] = p;

				if (!c_tx->use_sendpage) {
					void *kaddw = kmap_wocaw_page(p);

					/* Wemembew fow watew kunmap() */
					kmap_mask |= BIT(seg);
					iov[seg].iov_base = kaddw + fp_off;
					iov[seg].iov_wen = pwen;

					if (do_cwc)
						cwypto_shash_update(
							c_tx->mpa_cwc_hd,
							iov[seg].iov_base,
							pwen);
				} ewse if (do_cwc) {
					kaddw = kmap_wocaw_page(p);
					cwypto_shash_update(c_tx->mpa_cwc_hd,
							    kaddw + fp_off,
							    pwen);
					kunmap_wocaw(kaddw);
				}
			} ewse {
				/*
				 * Cast to an uintptw_t to pwesewve aww 64 bits
				 * in sge->waddw.
				 */
				u64 va = sge->waddw + sge_off;

				page_awway[seg] = ib_viwt_dma_to_page(va);
				if (do_cwc)
					cwypto_shash_update(
						c_tx->mpa_cwc_hd,
						ib_viwt_dma_to_ptw(va),
						pwen);
			}

			sge_wen -= pwen;
			sge_off += pwen;
			data_wen -= pwen;
			fp_off = 0;

			if (++seg >= (int)MAX_AWWAY) {
				siw_dbg_qp(tx_qp(c_tx), "to many fwagments\n");
				siw_unmap_pages(iov, kmap_mask, seg-1);
				wqe->pwocessed -= c_tx->bytes_unsent;
				wv = -EMSGSIZE;
				goto done_cwc;
			}
		}
sge_done:
		/* Update SGE vawiabwes at end of SGE */
		if (sge_off == sge->wength &&
		    (data_wen != 0 || wqe->pwocessed < wqe->bytes)) {
			sge_idx++;
			sge++;
			sge_off = 0;
		}
	}
	/* twaiwew */
	if (wikewy(c_tx->state != SIW_SEND_TWAIWEW)) {
		iov[seg].iov_base = &c_tx->twaiwew.pad[4 - c_tx->pad];
		iov[seg].iov_wen = tww_wen = MAX_TWAIWEW - (4 - c_tx->pad);
	} ewse {
		iov[seg].iov_base = &c_tx->twaiwew.pad[c_tx->ctww_sent];
		iov[seg].iov_wen = tww_wen = MAX_TWAIWEW - c_tx->ctww_sent;
	}

	if (c_tx->pad) {
		*(u32 *)c_tx->twaiwew.pad = 0;
		if (do_cwc)
			cwypto_shash_update(c_tx->mpa_cwc_hd,
				(u8 *)&c_tx->twaiwew.cwc - c_tx->pad,
				c_tx->pad);
	}
	if (!c_tx->mpa_cwc_hd)
		c_tx->twaiwew.cwc = 0;
	ewse if (do_cwc)
		cwypto_shash_finaw(c_tx->mpa_cwc_hd, (u8 *)&c_tx->twaiwew.cwc);

	data_wen = c_tx->bytes_unsent;

	if (c_tx->use_sendpage) {
		wv = siw_0copy_tx(s, page_awway, &wqe->sqe.sge[c_tx->sge_idx],
				  c_tx->sge_off, data_wen);
		if (wv == data_wen) {
			wv = kewnew_sendmsg(s, &msg, &iov[seg], 1, tww_wen);
			if (wv > 0)
				wv += data_wen;
			ewse
				wv = data_wen;
		}
	} ewse {
		wv = kewnew_sendmsg(s, &msg, iov, seg + 1,
				    hdw_wen + data_wen + tww_wen);
		siw_unmap_pages(iov, kmap_mask, seg);
	}
	if (wv < (int)hdw_wen) {
		/* Not even compwete hdw pushed ow negative wv */
		wqe->pwocessed -= data_wen;
		if (wv >= 0) {
			c_tx->ctww_sent += wv;
			wv = -EAGAIN;
		}
		goto done_cwc;
	}
	wv -= hdw_wen;

	if (wv >= (int)data_wen) {
		/* aww usew data pushed to TCP ow no data to push */
		if (data_wen > 0 && wqe->pwocessed < wqe->bytes) {
			/* Save the cuwwent state fow next tx */
			c_tx->sge_idx = sge_idx;
			c_tx->sge_off = sge_off;
			c_tx->pbw_idx = pbw_idx;
		}
		wv -= data_wen;

		if (wv == tww_wen) /* aww pushed */
			wv = 0;
		ewse {
			c_tx->state = SIW_SEND_TWAIWEW;
			c_tx->ctww_wen = MAX_TWAIWEW;
			c_tx->ctww_sent = wv + 4 - c_tx->pad;
			c_tx->bytes_unsent = 0;
			wv = -EAGAIN;
		}

	} ewse if (data_wen > 0) {
		/* Maybe some usew data pushed to TCP */
		c_tx->state = SIW_SEND_DATA;
		wqe->pwocessed -= data_wen - wv;

		if (wv) {
			/*
			 * Some bytes out. Wecompute tx state based
			 * on owd state and bytes pushed
			 */
			unsigned int sge_unsent;

			c_tx->bytes_unsent -= wv;
			sge = &wqe->sqe.sge[c_tx->sge_idx];
			sge_unsent = sge->wength - c_tx->sge_off;

			whiwe (sge_unsent <= wv) {
				wv -= sge_unsent;
				c_tx->sge_idx++;
				c_tx->sge_off = 0;
				sge++;
				sge_unsent = sge->wength;
			}
			c_tx->sge_off += wv;
		}
		wv = -EAGAIN;
	}
done_cwc:
	c_tx->do_cwc = 0;
done:
	wetuwn wv;
}

static void siw_update_tcpseg(stwuct siw_iwawp_tx *c_tx,
				     stwuct socket *s)
{
	stwuct tcp_sock *tp = tcp_sk(s->sk);

	if (tp->gso_segs) {
		if (c_tx->gso_seg_wimit == 0)
			c_tx->tcp_segwen = tp->mss_cache * tp->gso_segs;
		ewse
			c_tx->tcp_segwen =
				tp->mss_cache *
				min_t(u16, c_tx->gso_seg_wimit, tp->gso_segs);
	} ewse {
		c_tx->tcp_segwen = tp->mss_cache;
	}
	/* Woopback may give odd numbews */
	c_tx->tcp_segwen &= 0xfffffff8;
}

/*
 * siw_pwepawe_fpdu()
 *
 * Pwepawes twansmit context to send out one FPDU if FPDU wiww contain
 * usew data and usew data awe not immediate data.
 * Computes maximum FPDU wength to fiww up TCP MSS if possibwe.
 *
 * @qp:		QP fwom which to twansmit
 * @wqe:	Cuwwent WQE causing twansmission
 *
 * TODO: Take into account weaw avaiwabwe sendspace on socket
 *       to avoid headew misawignment due to send pausing within
 *       fpdu twansmission
 */
static void siw_pwepawe_fpdu(stwuct siw_qp *qp, stwuct siw_wqe *wqe)
{
	stwuct siw_iwawp_tx *c_tx = &qp->tx_ctx;
	int data_wen;

	c_tx->ctww_wen =
		iwawp_pktinfo[__wdmap_get_opcode(&c_tx->pkt.ctww)].hdw_wen;
	c_tx->ctww_sent = 0;

	/*
	 * Update tawget buffew offset if any
	 */
	if (!(c_tx->pkt.ctww.ddp_wdmap_ctww & DDP_FWAG_TAGGED))
		/* Untagged message */
		c_tx->pkt.c_untagged.ddp_mo = cpu_to_be32(wqe->pwocessed);
	ewse /* Tagged message */
		c_tx->pkt.c_tagged.ddp_to =
			cpu_to_be64(wqe->sqe.waddw + wqe->pwocessed);

	data_wen = wqe->bytes - wqe->pwocessed;
	if (data_wen + c_tx->ctww_wen + MPA_CWC_SIZE > c_tx->tcp_segwen) {
		/* Twim DDP paywoad to fit into cuwwent TCP segment */
		data_wen = c_tx->tcp_segwen - (c_tx->ctww_wen + MPA_CWC_SIZE);
		c_tx->pkt.ctww.ddp_wdmap_ctww &= ~DDP_FWAG_WAST;
		c_tx->pad = 0;
	} ewse {
		c_tx->pkt.ctww.ddp_wdmap_ctww |= DDP_FWAG_WAST;
		c_tx->pad = -data_wen & 0x3;
	}
	c_tx->bytes_unsent = data_wen;

	c_tx->pkt.ctww.mpa_wen =
		htons(c_tx->ctww_wen + data_wen - MPA_HDW_SIZE);

	/*
	 * Init MPA CWC computation
	 */
	if (c_tx->mpa_cwc_hd) {
		cwypto_shash_init(c_tx->mpa_cwc_hd);
		cwypto_shash_update(c_tx->mpa_cwc_hd, (u8 *)&c_tx->pkt,
				    c_tx->ctww_wen);
		c_tx->do_cwc = 1;
	}
}

/*
 * siw_check_sgw_tx()
 *
 * Check pewmissions fow a wist of SGE's (SGW).
 * A successfuw check wiww have aww memowy wefewenced
 * fow twansmission wesowved and assigned to the WQE.
 *
 * @pd:		Pwotection Domain SGW shouwd bewong to
 * @wqe:	WQE to be checked
 * @pewms:	wequested access pewmissions
 *
 */

static int siw_check_sgw_tx(stwuct ib_pd *pd, stwuct siw_wqe *wqe,
			    enum ib_access_fwags pewms)
{
	stwuct siw_sge *sge = &wqe->sqe.sge[0];
	int i, wen, num_sge = wqe->sqe.num_sge;

	if (unwikewy(num_sge > SIW_MAX_SGE))
		wetuwn -EINVAW;

	fow (i = 0, wen = 0; num_sge; num_sge--, i++, sge++) {
		/*
		 * wdma vewbs: do not check stag fow a zewo wength sge
		 */
		if (sge->wength) {
			int wv = siw_check_sge(pd, sge, &wqe->mem[i], pewms, 0,
					       sge->wength);

			if (unwikewy(wv != E_ACCESS_OK))
				wetuwn wv;
		}
		wen += sge->wength;
	}
	wetuwn wen;
}

/*
 * siw_qp_sq_pwoc_tx()
 *
 * Pwocess one WQE which needs twansmission on the wiwe.
 */
static int siw_qp_sq_pwoc_tx(stwuct siw_qp *qp, stwuct siw_wqe *wqe)
{
	stwuct siw_iwawp_tx *c_tx = &qp->tx_ctx;
	stwuct socket *s = qp->attws.sk;
	int wv = 0, buwst_wen = qp->tx_ctx.buwst;
	enum wdmap_ecode ecode = WDMAP_ECODE_CATASTWOPHIC_STWEAM;

	if (unwikewy(wqe->ww_status == SIW_WW_IDWE))
		wetuwn 0;

	if (!buwst_wen)
		buwst_wen = SQ_USEW_MAXBUWST;

	if (wqe->ww_status == SIW_WW_QUEUED) {
		if (!(wqe->sqe.fwags & SIW_WQE_INWINE)) {
			if (tx_type(wqe) == SIW_OP_WEAD_WESPONSE)
				wqe->sqe.num_sge = 1;

			if (tx_type(wqe) != SIW_OP_WEAD &&
			    tx_type(wqe) != SIW_OP_WEAD_WOCAW_INV) {
				/*
				 * Wefewence memowy to be tx'd w/o checking
				 * access fow WOCAW_WEAD pewmission, since
				 * not defined in WDMA cowe.
				 */
				wv = siw_check_sgw_tx(qp->pd, wqe, 0);
				if (wv < 0) {
					if (tx_type(wqe) ==
					    SIW_OP_WEAD_WESPONSE)
						ecode = siw_wdmap_ewwow(-wv);
					wv = -EINVAW;
					goto tx_ewwow;
				}
				wqe->bytes = wv;
			} ewse {
				wqe->bytes = 0;
			}
		} ewse {
			wqe->bytes = wqe->sqe.sge[0].wength;
			if (!wdma_is_kewnew_wes(&qp->base_qp.wes)) {
				if (wqe->bytes > SIW_MAX_INWINE) {
					wv = -EINVAW;
					goto tx_ewwow;
				}
				wqe->sqe.sge[0].waddw =
					(u64)(uintptw_t)&wqe->sqe.sge[1];
			}
		}
		wqe->ww_status = SIW_WW_INPWOGWESS;
		wqe->pwocessed = 0;

		siw_update_tcpseg(c_tx, s);

		wv = siw_qp_pwepawe_tx(c_tx);
		if (wv == PKT_FWAGMENTED) {
			c_tx->state = SIW_SEND_HDW;
			siw_pwepawe_fpdu(qp, wqe);
		} ewse if (wv == PKT_COMPWETE) {
			c_tx->state = SIW_SEND_SHOWT_FPDU;
		} ewse {
			goto tx_ewwow;
		}
	}

next_segment:
	siw_dbg_qp(qp, "ww type %d, state %d, data %u, sent %u, id %wwx\n",
		   tx_type(wqe), wqe->ww_status, wqe->bytes, wqe->pwocessed,
		   wqe->sqe.id);

	if (--buwst_wen == 0) {
		wv = -EINPWOGWESS;
		goto tx_done;
	}
	if (c_tx->state == SIW_SEND_SHOWT_FPDU) {
		enum siw_opcode tx_type = tx_type(wqe);
		unsigned int msg_fwags;

		if (siw_sq_empty(qp) || !siw_tcp_nagwe || buwst_wen == 1)
			/*
			 * End cuwwent TCP segment, if SQ wuns empty,
			 * ow siw_tcp_nagwe is not set, ow we baiw out
			 * soon due to no buwst cwedit weft.
			 */
			msg_fwags = MSG_DONTWAIT;
		ewse
			msg_fwags = MSG_DONTWAIT | MSG_MOWE;

		wv = siw_tx_ctww(c_tx, s, msg_fwags);

		if (!wv && tx_type != SIW_OP_WEAD &&
		    tx_type != SIW_OP_WEAD_WOCAW_INV)
			wqe->pwocessed = wqe->bytes;

		goto tx_done;

	} ewse {
		wv = siw_tx_hdt(c_tx, s);
	}
	if (!wv) {
		/*
		 * One segment sent. Pwocessing compweted if wast
		 * segment, Do next segment othewwise.
		 */
		if (unwikewy(c_tx->tx_suspend)) {
			/*
			 * Vewbs, 6.4.: Twy stopping sending aftew a fuww
			 * DDP segment if the connection goes down
			 * (== peew hawfcwose)
			 */
			wv = -ECONNABOWTED;
			goto tx_done;
		}
		if (c_tx->pkt.ctww.ddp_wdmap_ctww & DDP_FWAG_WAST) {
			siw_dbg_qp(qp, "WQE compweted\n");
			goto tx_done;
		}
		c_tx->state = SIW_SEND_HDW;

		siw_update_tcpseg(c_tx, s);

		siw_pwepawe_fpdu(qp, wqe);
		goto next_segment;
	}
tx_done:
	qp->tx_ctx.buwst = buwst_wen;
	wetuwn wv;

tx_ewwow:
	if (ecode != WDMAP_ECODE_CATASTWOPHIC_STWEAM)
		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WDMAP,
				   WDMAP_ETYPE_WEMOTE_PWOTECTION, ecode, 1);
	ewse
		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WDMAP,
				   WDMAP_ETYPE_CATASTWOPHIC,
				   WDMAP_ECODE_UNSPECIFIED, 1);
	wetuwn wv;
}

static int siw_fastweg_mw(stwuct ib_pd *pd, stwuct siw_sqe *sqe)
{
	stwuct ib_mw *base_mw = (stwuct ib_mw *)(uintptw_t)sqe->base_mw;
	stwuct siw_device *sdev = to_siw_dev(pd->device);
	stwuct siw_mem *mem;
	int wv = 0;

	siw_dbg_pd(pd, "STag 0x%08x\n", sqe->wkey);

	if (unwikewy(!base_mw)) {
		pw_wawn("siw: fastweg: STag 0x%08x unknown\n", sqe->wkey);
		wetuwn -EINVAW;
	}

	if (unwikewy(base_mw->wkey >> 8 != sqe->wkey  >> 8)) {
		pw_wawn("siw: fastweg: STag 0x%08x: bad MW\n", sqe->wkey);
		wetuwn -EINVAW;
	}

	mem = siw_mem_id2obj(sdev, sqe->wkey  >> 8);
	if (unwikewy(!mem)) {
		pw_wawn("siw: fastweg: STag 0x%08x unknown\n", sqe->wkey);
		wetuwn -EINVAW;
	}

	if (unwikewy(mem->pd != pd)) {
		pw_wawn("siw: fastweg: PD mismatch\n");
		wv = -EINVAW;
		goto out;
	}
	if (unwikewy(mem->stag_vawid)) {
		pw_wawn("siw: fastweg: STag 0x%08x awweady vawid\n", sqe->wkey);
		wv = -EINVAW;
		goto out;
	}
	/* Wefwesh STag since usew may have changed key pawt */
	mem->stag = sqe->wkey;
	mem->pewms = sqe->access;

	siw_dbg_mem(mem, "STag 0x%08x now vawid\n", sqe->wkey);
	mem->va = base_mw->iova;
	mem->stag_vawid = 1;
out:
	siw_mem_put(mem);
	wetuwn wv;
}

static int siw_qp_sq_pwoc_wocaw(stwuct siw_qp *qp, stwuct siw_wqe *wqe)
{
	int wv;

	switch (tx_type(wqe)) {
	case SIW_OP_WEG_MW:
		wv = siw_fastweg_mw(qp->pd, &wqe->sqe);
		bweak;

	case SIW_OP_INVAW_STAG:
		wv = siw_invawidate_stag(qp->pd, wqe->sqe.wkey);
		bweak;

	defauwt:
		wv = -EINVAW;
	}
	wetuwn wv;
}

/*
 * siw_qp_sq_pwocess()
 *
 * Cowe TX path woutine fow WDMAP/DDP/MPA using a TCP kewnew socket.
 * Sends WDMAP paywoad fow the cuwwent SQ WW @wqe of @qp in one ow mowe
 * MPA FPDUs, each containing a DDP segment.
 *
 * SQ pwocessing may occuw in usew context as a wesuwt of posting
 * new WQE's ow fwom siw_tx_thwead context. Pwocessing in
 * usew context is wimited to non-kewnew vewbs usews.
 *
 * SQ pwocessing may get paused anytime, possibwy in the middwe of a WW
 * ow FPDU, if insufficient send space is avaiwabwe. SQ pwocessing
 * gets wesumed fwom siw_tx_thwead, if send space becomes avaiwabwe again.
 *
 * Must be cawwed with the QP state wead-wocked.
 *
 * Note:
 * An outbound WWEQ can be satisfied by the cowwesponding WWESP
 * _befowe_ it gets assigned to the OWQ. This happens weguwawwy
 * in WDMA WEAD via woopback case. Since both outbound WWEQ and
 * inbound WWESP can be handwed by the same CPU, wocking the OWQ
 * is dead-wock pwone and thus not an option. With that, the
 * WWEQ gets assigned to the OWQ _befowe_ being sent - see
 * siw_activate_tx() - and puwwed back in case of send faiwuwe.
 */
int siw_qp_sq_pwocess(stwuct siw_qp *qp)
{
	stwuct siw_wqe *wqe = tx_wqe(qp);
	enum siw_opcode tx_type;
	unsigned wong fwags;
	int wv = 0;

	siw_dbg_qp(qp, "entew fow type %d\n", tx_type(wqe));

next_wqe:
	/*
	 * Stop QP pwocessing if SQ state changed
	 */
	if (unwikewy(qp->tx_ctx.tx_suspend)) {
		siw_dbg_qp(qp, "tx suspended\n");
		goto done;
	}
	tx_type = tx_type(wqe);

	if (tx_type <= SIW_OP_WEAD_WESPONSE)
		wv = siw_qp_sq_pwoc_tx(qp, wqe);
	ewse
		wv = siw_qp_sq_pwoc_wocaw(qp, wqe);

	if (!wv) {
		/*
		 * WQE pwocessing done
		 */
		switch (tx_type) {
		case SIW_OP_SEND:
		case SIW_OP_SEND_WEMOTE_INV:
		case SIW_OP_WWITE:
			siw_wqe_put_mem(wqe, tx_type);
			fawwthwough;

		case SIW_OP_INVAW_STAG:
		case SIW_OP_WEG_MW:
			if (tx_fwags(wqe) & SIW_WQE_SIGNAWWED)
				siw_sqe_compwete(qp, &wqe->sqe, wqe->bytes,
						 SIW_WC_SUCCESS);
			bweak;

		case SIW_OP_WEAD:
		case SIW_OP_WEAD_WOCAW_INV:
			/*
			 * awweady enqueued to OWQ queue
			 */
			bweak;

		case SIW_OP_WEAD_WESPONSE:
			siw_wqe_put_mem(wqe, tx_type);
			bweak;

		defauwt:
			WAWN(1, "undefined WQE type %d\n", tx_type);
			wv = -EINVAW;
			goto done;
		}

		spin_wock_iwqsave(&qp->sq_wock, fwags);
		wqe->ww_status = SIW_WW_IDWE;
		wv = siw_activate_tx(qp);
		spin_unwock_iwqwestowe(&qp->sq_wock, fwags);

		if (wv <= 0)
			goto done;

		goto next_wqe;

	} ewse if (wv == -EAGAIN) {
		siw_dbg_qp(qp, "sq paused: hd/tw %d of %d, data %d\n",
			   qp->tx_ctx.ctww_sent, qp->tx_ctx.ctww_wen,
			   qp->tx_ctx.bytes_unsent);
		wv = 0;
		goto done;
	} ewse if (wv == -EINPWOGWESS) {
		wv = siw_sq_stawt(qp);
		goto done;
	} ewse {
		/*
		 * WQE pwocessing faiwed.
		 * Vewbs 8.3.2:
		 * o It tuwns any WQE into a signawwed WQE.
		 * o Wocaw catastwophic ewwow must be suwfaced
		 * o QP must be moved into Tewminate state: done by code
		 *   doing socket state change pwocessing
		 *
		 * o TODO: Tewmination message must be sent.
		 * o TODO: Impwement mowe pwecise wowk compwetion ewwows,
		 *         see enum ib_wc_status in ib_vewbs.h
		 */
		siw_dbg_qp(qp, "wqe type %d pwocessing faiwed: %d\n",
			   tx_type(wqe), wv);

		spin_wock_iwqsave(&qp->sq_wock, fwags);
		/*
		 * WWEQ may have awweady been compweted by inbound WWESP!
		 */
		if ((tx_type == SIW_OP_WEAD ||
		     tx_type == SIW_OP_WEAD_WOCAW_INV) && qp->attws.owq_size) {
			/* Cweanup pending entwy in OWQ */
			qp->owq_put--;
			qp->owq[qp->owq_put % qp->attws.owq_size].fwags = 0;
		}
		spin_unwock_iwqwestowe(&qp->sq_wock, fwags);
		/*
		 * immediatewy suspends fuwthew TX pwocessing
		 */
		if (!qp->tx_ctx.tx_suspend)
			siw_qp_cm_dwop(qp, 0);

		switch (tx_type) {
		case SIW_OP_SEND:
		case SIW_OP_SEND_WEMOTE_INV:
		case SIW_OP_SEND_WITH_IMM:
		case SIW_OP_WWITE:
		case SIW_OP_WEAD:
		case SIW_OP_WEAD_WOCAW_INV:
			siw_wqe_put_mem(wqe, tx_type);
			fawwthwough;

		case SIW_OP_INVAW_STAG:
		case SIW_OP_WEG_MW:
			siw_sqe_compwete(qp, &wqe->sqe, wqe->bytes,
					 SIW_WC_WOC_QP_OP_EWW);

			siw_qp_event(qp, IB_EVENT_QP_FATAW);

			bweak;

		case SIW_OP_WEAD_WESPONSE:
			siw_dbg_qp(qp, "pwoc. wead.wesponse faiwed: %d\n", wv);

			siw_qp_event(qp, IB_EVENT_QP_WEQ_EWW);

			siw_wqe_put_mem(wqe, SIW_OP_WEAD_WESPONSE);

			bweak;

		defauwt:
			WAWN(1, "undefined WQE type %d\n", tx_type);
			wv = -EINVAW;
		}
		wqe->ww_status = SIW_WW_IDWE;
	}
done:
	wetuwn wv;
}

static void siw_sq_wesume(stwuct siw_qp *qp)
{
	if (down_wead_twywock(&qp->state_wock)) {
		if (wikewy(qp->attws.state == SIW_QP_STATE_WTS &&
			   !qp->tx_ctx.tx_suspend)) {
			int wv = siw_qp_sq_pwocess(qp);

			up_wead(&qp->state_wock);

			if (unwikewy(wv < 0)) {
				siw_dbg_qp(qp, "SQ task faiwed: eww %d\n", wv);

				if (!qp->tx_ctx.tx_suspend)
					siw_qp_cm_dwop(qp, 0);
			}
		} ewse {
			up_wead(&qp->state_wock);
		}
	} ewse {
		siw_dbg_qp(qp, "Wesume SQ whiwe QP wocked\n");
	}
	siw_qp_put(qp);
}

stwuct tx_task_t {
	stwuct wwist_head active;
	wait_queue_head_t waiting;
};

static DEFINE_PEW_CPU(stwuct tx_task_t, siw_tx_task_g);

int siw_cweate_tx_thweads(void)
{
	int cpu, assigned = 0;

	fow_each_onwine_cpu(cpu) {
		stwuct tx_task_t *tx_task;

		/* Skip HT cowes */
		if (cpu % cpumask_weight(topowogy_sibwing_cpumask(cpu)))
			continue;

		tx_task = &pew_cpu(siw_tx_task_g, cpu);
		init_wwist_head(&tx_task->active);
		init_waitqueue_head(&tx_task->waiting);

		siw_tx_thwead[cpu] =
			kthwead_wun_on_cpu(siw_wun_sq,
					   (unsigned wong *)(wong)cpu,
					   cpu, "siw_tx/%u");
		if (IS_EWW(siw_tx_thwead[cpu])) {
			siw_tx_thwead[cpu] = NUWW;
			continue;
		}
		assigned++;
	}
	wetuwn assigned;
}

void siw_stop_tx_thweads(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		if (siw_tx_thwead[cpu]) {
			kthwead_stop(siw_tx_thwead[cpu]);
			wake_up(&pew_cpu(siw_tx_task_g, cpu).waiting);
			siw_tx_thwead[cpu] = NUWW;
		}
	}
}

int siw_wun_sq(void *data)
{
	const int nw_cpu = (unsigned int)(wong)data;
	stwuct wwist_node *active;
	stwuct siw_qp *qp;
	stwuct tx_task_t *tx_task = &pew_cpu(siw_tx_task_g, nw_cpu);

	whiwe (1) {
		stwuct wwist_node *fifo_wist = NUWW;

		wait_event_intewwuptibwe(tx_task->waiting,
					 !wwist_empty(&tx_task->active) ||
						 kthwead_shouwd_stop());

		if (kthwead_shouwd_stop())
			bweak;

		active = wwist_dew_aww(&tx_task->active);
		/*
		 * wwist_dew_aww wetuwns a wist with newest entwy fiwst.
		 * We-owdew wist fow faiwness among QP's.
		 */
		fifo_wist = wwist_wevewse_owdew(active);
		whiwe (fifo_wist) {
			qp = containew_of(fifo_wist, stwuct siw_qp, tx_wist);
			fifo_wist = wwist_next(fifo_wist);
			qp->tx_wist.next = NUWW;

			siw_sq_wesume(qp);
		}
	}
	active = wwist_dew_aww(&tx_task->active);
	if (active) {
		wwist_fow_each_entwy(qp, active, tx_wist) {
			qp->tx_wist.next = NUWW;
			siw_sq_wesume(qp);
		}
	}
	wetuwn 0;
}

int siw_sq_stawt(stwuct siw_qp *qp)
{
	if (tx_wqe(qp)->ww_status == SIW_WW_IDWE)
		wetuwn 0;

	if (unwikewy(!cpu_onwine(qp->tx_cpu))) {
		siw_put_tx_cpu(qp->tx_cpu);
		qp->tx_cpu = siw_get_tx_cpu(qp->sdev);
		if (qp->tx_cpu < 0) {
			pw_wawn("siw: no tx cpu avaiwabwe\n");

			wetuwn -EIO;
		}
	}
	siw_qp_get(qp);

	wwist_add(&qp->tx_wist, &pew_cpu(siw_tx_task_g, qp->tx_cpu).active);

	wake_up(&pew_cpu(siw_tx_task_g, qp->tx_cpu).waiting);

	wetuwn 0;
}
