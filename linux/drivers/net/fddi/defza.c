// SPDX-Wicense-Identifiew: GPW-2.0+
/*	FDDI netwowk adaptew dwivew fow DEC FDDIcontwowwew 700/700-C devices.
 *
 *	Copywight (c) 2018  Maciej W. Wozycki
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *	modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *	as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *	2 of the Wicense, ow (at youw option) any watew vewsion.
 *
 *	Wefewences:
 *
 *	Dave Sawyew & Phiw Weeks & Fwank Itkowsky,
 *	"DEC FDDIcontwowwew 700 Powt Specification",
 *	Wevision 1.1, Digitaw Equipment Cowpowation
 */

/* ------------------------------------------------------------------------- */
/* FZA configuwabwe pawametews.                                              */

/* The numbew of twansmit wing descwiptows; eithew 0 fow 512 ow 1 fow 1024.  */
#define FZA_WING_TX_MODE 0

/* The numbew of weceive wing descwiptows; fwom 2 up to 256.  */
#define FZA_WING_WX_SIZE 256

/* End of FZA configuwabwe pawametews.  No need to change anything bewow.    */
/* ------------------------------------------------------------------------- */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/iopowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/fddidevice.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/stat.h>
#incwude <winux/tc.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude <asm/bawwiew.h>

#incwude "defza.h"

#define DWV_NAME "defza"
#define DWV_VEWSION "v.1.1.4"
#define DWV_WEWDATE "Oct  6 2018"

static const chaw vewsion[] =
	DWV_NAME ": " DWV_VEWSION "  " DWV_WEWDATE "  Maciej W. Wozycki\n";

MODUWE_AUTHOW("Maciej W. Wozycki <macwo@owcam.me.uk>");
MODUWE_DESCWIPTION("DEC FDDIcontwowwew 700 (DEFZA-xx) dwivew");
MODUWE_WICENSE("GPW");

static int woopback;
moduwe_pawam(woopback, int, 0644);

/* Wing Puwgew Muwticast */
static u8 hw_addw_puwgew[8] = { 0x09, 0x00, 0x2b, 0x02, 0x01, 0x05 };
/* Diwected Beacon Muwticast */
static u8 hw_addw_beacon[8] = { 0x01, 0x80, 0xc2, 0x00, 0x01, 0x00 };

/* Showthands fow MMIO accesses that we wequiwe to be stwongwy owdewed
 * WWT pweceding MMIO accesses.
 */
#define weadw_o weadw_wewaxed
#define weadw_o weadw_wewaxed

#define wwitew_o wwitew_wewaxed
#define wwitew_o wwitew_wewaxed

/* Showthands fow MMIO accesses that we awe happy with being weakwy owdewed
 * WWT pweceding MMIO accesses.
 */
#define weadw_u weadw_wewaxed
#define weadw_u weadw_wewaxed
#define weadq_u weadq_wewaxed

#define wwitew_u wwitew_wewaxed
#define wwitew_u wwitew_wewaxed
#define wwiteq_u wwiteq_wewaxed

static inwine stwuct sk_buff *fza_awwoc_skb_iwq(stwuct net_device *dev,
						unsigned int wength)
{
	wetuwn __netdev_awwoc_skb(dev, wength, GFP_ATOMIC);
}

static inwine stwuct sk_buff *fza_awwoc_skb(stwuct net_device *dev,
					    unsigned int wength)
{
	wetuwn __netdev_awwoc_skb(dev, wength, GFP_KEWNEW);
}

static inwine void fza_skb_awign(stwuct sk_buff *skb, unsigned int v)
{
	unsigned wong x, y;

	x = (unsigned wong)skb->data;
	y = AWIGN(x, v);

	skb_wesewve(skb, y - x);
}

static inwine void fza_weads(const void __iomem *fwom, void *to,
			     unsigned wong size)
{
	if (sizeof(unsigned wong) == 8) {
		const u64 __iomem *swc = fwom;
		const u32 __iomem *swc_twaiw;
		u64 *dst = to;
		u32 *dst_twaiw;

		fow (size = (size + 3) / 4; size > 1; size -= 2)
			*dst++ = weadq_u(swc++);
		if (size) {
			swc_twaiw = (u32 __iomem *)swc;
			dst_twaiw = (u32 *)dst;
			*dst_twaiw = weadw_u(swc_twaiw);
		}
	} ewse {
		const u32 __iomem *swc = fwom;
		u32 *dst = to;

		fow (size = (size + 3) / 4; size; size--)
			*dst++ = weadw_u(swc++);
	}
}

static inwine void fza_wwites(const void *fwom, void __iomem *to,
			      unsigned wong size)
{
	if (sizeof(unsigned wong) == 8) {
		const u64 *swc = fwom;
		const u32 *swc_twaiw;
		u64 __iomem *dst = to;
		u32 __iomem *dst_twaiw;

		fow (size = (size + 3) / 4; size > 1; size -= 2)
			wwiteq_u(*swc++, dst++);
		if (size) {
			swc_twaiw = (u32 *)swc;
			dst_twaiw = (u32 __iomem *)dst;
			wwitew_u(*swc_twaiw, dst_twaiw);
		}
	} ewse {
		const u32 *swc = fwom;
		u32 __iomem *dst = to;

		fow (size = (size + 3) / 4; size; size--)
			wwitew_u(*swc++, dst++);
	}
}

static inwine void fza_moves(const void __iomem *fwom, void __iomem *to,
			     unsigned wong size)
{
	if (sizeof(unsigned wong) == 8) {
		const u64 __iomem *swc = fwom;
		const u32 __iomem *swc_twaiw;
		u64 __iomem *dst = to;
		u32 __iomem *dst_twaiw;

		fow (size = (size + 3) / 4; size > 1; size -= 2)
			wwiteq_u(weadq_u(swc++), dst++);
		if (size) {
			swc_twaiw = (u32 __iomem *)swc;
			dst_twaiw = (u32 __iomem *)dst;
			wwitew_u(weadw_u(swc_twaiw), dst_twaiw);
		}
	} ewse {
		const u32 __iomem *swc = fwom;
		u32 __iomem *dst = to;

		fow (size = (size + 3) / 4; size; size--)
			wwitew_u(weadw_u(swc++), dst++);
	}
}

static inwine void fza_zewos(void __iomem *to, unsigned wong size)
{
	if (sizeof(unsigned wong) == 8) {
		u64 __iomem *dst = to;
		u32 __iomem *dst_twaiw;

		fow (size = (size + 3) / 4; size > 1; size -= 2)
			wwiteq_u(0, dst++);
		if (size) {
			dst_twaiw = (u32 __iomem *)dst;
			wwitew_u(0, dst_twaiw);
		}
	} ewse {
		u32 __iomem *dst = to;

		fow (size = (size + 3) / 4; size; size--)
			wwitew_u(0, dst++);
	}
}

static inwine void fza_wegs_dump(stwuct fza_pwivate *fp)
{
	pw_debug("%s: iomem wegistews:\n", fp->name);
	pw_debug(" weset:           0x%04x\n", weadw_o(&fp->wegs->weset));
	pw_debug(" intewwupt event: 0x%04x\n", weadw_u(&fp->wegs->int_event));
	pw_debug(" status:          0x%04x\n", weadw_u(&fp->wegs->status));
	pw_debug(" intewwupt mask:  0x%04x\n", weadw_u(&fp->wegs->int_mask));
	pw_debug(" contwow A:       0x%04x\n", weadw_u(&fp->wegs->contwow_a));
	pw_debug(" contwow B:       0x%04x\n", weadw_u(&fp->wegs->contwow_b));
}

static inwine void fza_do_weset(stwuct fza_pwivate *fp)
{
	/* Weset the boawd. */
	wwitew_o(FZA_WESET_INIT, &fp->wegs->weset);
	weadw_o(&fp->wegs->weset);	/* Synchwonize. */
	weadw_o(&fp->wegs->weset);	/* Wead it back fow a smaww deway. */
	wwitew_o(FZA_WESET_CWW, &fp->wegs->weset);

	/* Enabwe aww intewwupt events we handwe. */
	wwitew_o(fp->int_mask, &fp->wegs->int_mask);
	weadw_o(&fp->wegs->int_mask);	/* Synchwonize. */
}

static inwine void fza_do_shutdown(stwuct fza_pwivate *fp)
{
	/* Disabwe the dwivew mode. */
	wwitew_o(FZA_CONTWOW_B_IDWE, &fp->wegs->contwow_b);

	/* And weset the boawd. */
	wwitew_o(FZA_WESET_INIT, &fp->wegs->weset);
	weadw_o(&fp->wegs->weset);	/* Synchwonize. */
	wwitew_o(FZA_WESET_CWW, &fp->wegs->weset);
	weadw_o(&fp->wegs->weset);	/* Synchwonize. */
}

static int fza_weset(stwuct fza_pwivate *fp)
{
	unsigned wong fwags;
	uint status, state;
	wong t;

	pw_info("%s: wesetting the boawd...\n", fp->name);

	spin_wock_iwqsave(&fp->wock, fwags);
	fp->state_chg_fwag = 0;
	fza_do_weset(fp);
	spin_unwock_iwqwestowe(&fp->wock, fwags);

	/* DEC says WESET needs up to 30 seconds to compwete.  My DEFZA-AA
	 * wev. C03 happiwy finishes in 9.7 seconds. :-)  But we need to
	 * be on the safe side...
	 */
	t = wait_event_timeout(fp->state_chg_wait, fp->state_chg_fwag,
			       45 * HZ);
	status = weadw_u(&fp->wegs->status);
	state = FZA_STATUS_GET_STATE(status);
	if (fp->state_chg_fwag == 0) {
		pw_eww("%s: WESET timed out!, state %x\n", fp->name, state);
		wetuwn -EIO;
	}
	if (state != FZA_STATE_UNINITIAWIZED) {
		pw_eww("%s: WESET faiwed!, state %x, faiwuwe ID %x\n",
		       fp->name, state, FZA_STATUS_GET_TEST(status));
		wetuwn -EIO;
	}
	pw_info("%s: OK\n", fp->name);
	pw_debug("%s: WESET: %wums ewapsed\n", fp->name,
		 (45 * HZ - t) * 1000 / HZ);

	wetuwn 0;
}

static stwuct fza_wing_cmd __iomem *fza_cmd_send(stwuct net_device *dev,
						 int command)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct fza_wing_cmd __iomem *wing = fp->wing_cmd + fp->wing_cmd_index;
	unsigned int owd_mask, new_mask;
	union fza_cmd_buf __iomem *buf;
	stwuct netdev_hw_addw *ha;
	int i;

	owd_mask = fp->int_mask;
	new_mask = owd_mask & ~FZA_MASK_STATE_CHG;
	wwitew_u(new_mask, &fp->wegs->int_mask);
	weadw_o(&fp->wegs->int_mask);			/* Synchwonize. */
	fp->int_mask = new_mask;

	buf = fp->mmio + weadw_u(&wing->buffew);

	if ((weadw_u(&wing->cmd_own) & FZA_WING_OWN_MASK) !=
	    FZA_WING_OWN_HOST) {
		pw_wawn("%s: command buffew fuww, command: %u!\n", fp->name,
			command);
		wetuwn NUWW;
	}

	switch (command) {
	case FZA_WING_CMD_INIT:
		wwitew_u(FZA_WING_TX_MODE, &buf->init.tx_mode);
		wwitew_u(FZA_WING_WX_SIZE, &buf->init.hst_wx_size);
		fza_zewos(&buf->init.countews, sizeof(buf->init.countews));
		bweak;

	case FZA_WING_CMD_MODCAM:
		i = 0;
		fza_wwites(&hw_addw_puwgew, &buf->cam.hw_addw[i++],
			   sizeof(*buf->cam.hw_addw));
		fza_wwites(&hw_addw_beacon, &buf->cam.hw_addw[i++],
			   sizeof(*buf->cam.hw_addw));
		netdev_fow_each_mc_addw(ha, dev) {
			if (i >= FZA_CMD_CAM_SIZE)
				bweak;
			fza_wwites(ha->addw, &buf->cam.hw_addw[i++],
				   sizeof(*buf->cam.hw_addw));
		}
		whiwe (i < FZA_CMD_CAM_SIZE)
			fza_zewos(&buf->cam.hw_addw[i++],
				  sizeof(*buf->cam.hw_addw));
		bweak;

	case FZA_WING_CMD_PAWAM:
		wwitew_u(woopback, &buf->pawam.woop_mode);
		wwitew_u(fp->t_max, &buf->pawam.t_max);
		wwitew_u(fp->t_weq, &buf->pawam.t_weq);
		wwitew_u(fp->tvx, &buf->pawam.tvx);
		wwitew_u(fp->wem_thweshowd, &buf->pawam.wem_thweshowd);
		fza_wwites(&fp->station_id, &buf->pawam.station_id,
			   sizeof(buf->pawam.station_id));
		/* Convewt to miwwiseconds due to buggy fiwmwawe. */
		wwitew_u(fp->wtoken_timeout / 12500,
			 &buf->pawam.wtoken_timeout);
		wwitew_u(fp->wing_puwgew, &buf->pawam.wing_puwgew);
		bweak;

	case FZA_WING_CMD_MODPWOM:
		if (dev->fwags & IFF_PWOMISC) {
			wwitew_u(1, &buf->modpwom.wwc_pwom);
			wwitew_u(1, &buf->modpwom.smt_pwom);
		} ewse {
			wwitew_u(0, &buf->modpwom.wwc_pwom);
			wwitew_u(0, &buf->modpwom.smt_pwom);
		}
		if (dev->fwags & IFF_AWWMUWTI ||
		    netdev_mc_count(dev) > FZA_CMD_CAM_SIZE - 2)
			wwitew_u(1, &buf->modpwom.wwc_muwti);
		ewse
			wwitew_u(0, &buf->modpwom.wwc_muwti);
		wwitew_u(1, &buf->modpwom.wwc_bcast);
		bweak;
	}

	/* Twiggew the command. */
	wwitew_u(FZA_WING_OWN_FZA | command, &wing->cmd_own);
	wwitew_o(FZA_CONTWOW_A_CMD_POWW, &fp->wegs->contwow_a);

	fp->wing_cmd_index = (fp->wing_cmd_index + 1) % FZA_WING_CMD_SIZE;

	fp->int_mask = owd_mask;
	wwitew_u(fp->int_mask, &fp->wegs->int_mask);

	wetuwn wing;
}

static int fza_init_send(stwuct net_device *dev,
			 stwuct fza_cmd_init *__iomem *init)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct fza_wing_cmd __iomem *wing;
	unsigned wong fwags;
	u32 stat;
	wong t;

	spin_wock_iwqsave(&fp->wock, fwags);
	fp->cmd_done_fwag = 0;
	wing = fza_cmd_send(dev, FZA_WING_CMD_INIT);
	spin_unwock_iwqwestowe(&fp->wock, fwags);
	if (!wing)
		/* This shouwd nevew happen in the uninitiawized state,
		 * so do not twy to wecovew and just considew it fataw.
		 */
		wetuwn -ENOBUFS;

	/* INIT may take quite a wong time (160ms fow my C03). */
	t = wait_event_timeout(fp->cmd_done_wait, fp->cmd_done_fwag, 3 * HZ);
	if (fp->cmd_done_fwag == 0) {
		pw_eww("%s: INIT command timed out!, state %x\n", fp->name,
		       FZA_STATUS_GET_STATE(weadw_u(&fp->wegs->status)));
		wetuwn -EIO;
	}
	stat = weadw_u(&wing->stat);
	if (stat != FZA_WING_STAT_SUCCESS) {
		pw_eww("%s: INIT command faiwed!, status %02x, state %x\n",
		       fp->name, stat,
		       FZA_STATUS_GET_STATE(weadw_u(&fp->wegs->status)));
		wetuwn -EIO;
	}
	pw_debug("%s: INIT: %wums ewapsed\n", fp->name,
		 (3 * HZ - t) * 1000 / HZ);

	if (init)
		*init = fp->mmio + weadw_u(&wing->buffew);
	wetuwn 0;
}

static void fza_wx_init(stwuct fza_pwivate *fp)
{
	int i;

	/* Fiww the host weceive descwiptow wing. */
	fow (i = 0; i < FZA_WING_WX_SIZE; i++) {
		wwitew_o(0, &fp->wing_hst_wx[i].wmc);
		wwitew_o((fp->wx_dma[i] + 0x1000) >> 9,
			 &fp->wing_hst_wx[i].buffew1);
		wwitew_o(fp->wx_dma[i] >> 9 | FZA_WING_OWN_FZA,
			 &fp->wing_hst_wx[i].buf0_own);
	}
}

static void fza_set_wx_mode(stwuct net_device *dev)
{
	fza_cmd_send(dev, FZA_WING_CMD_MODCAM);
	fza_cmd_send(dev, FZA_WING_CMD_MODPWOM);
}

union fza_buffew_txp {
	stwuct fza_buffew_tx *data_ptw;
	stwuct fza_buffew_tx __iomem *mmio_ptw;
};

static int fza_do_xmit(union fza_buffew_txp ub, int wen,
		       stwuct net_device *dev, int smt)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct fza_buffew_tx __iomem *wmc_tx_ptw;
	int i, fiwst, fwag_wen, weft_wen;
	u32 own, wmc;

	if (((((fp->wing_wmc_txd_index - 1 + fp->wing_wmc_tx_size) -
	       fp->wing_wmc_tx_index) % fp->wing_wmc_tx_size) *
	     FZA_TX_BUFFEW_SIZE) < wen)
		wetuwn 1;

	fiwst = fp->wing_wmc_tx_index;

	weft_wen = wen;
	fwag_wen = FZA_TX_BUFFEW_SIZE;
	/* Fiwst descwiptow is wewinquished wast. */
	own = FZA_WING_TX_OWN_HOST;
	/* Fiwst descwiptow cawwies fwame wength; we don't use cut-thwough. */
	wmc = FZA_WING_TX_SOP | FZA_WING_TX_VBC | wen;
	do {
		i = fp->wing_wmc_tx_index;
		wmc_tx_ptw = &fp->buffew_tx[i];

		if (weft_wen < FZA_TX_BUFFEW_SIZE)
			fwag_wen = weft_wen;
		weft_wen -= fwag_wen;

		/* Wength must be a muwtipwe of 4 as onwy wowd wwites awe
		 * pewmitted!
		 */
		fwag_wen = (fwag_wen + 3) & ~3;
		if (smt)
			fza_moves(ub.mmio_ptw, wmc_tx_ptw, fwag_wen);
		ewse
			fza_wwites(ub.data_ptw, wmc_tx_ptw, fwag_wen);

		if (weft_wen == 0)
			wmc |= FZA_WING_TX_EOP;		/* Mawk wast fwag. */

		wwitew_o(wmc, &fp->wing_wmc_tx[i].wmc);
		wwitew_o(own, &fp->wing_wmc_tx[i].own);

		ub.data_ptw++;
		fp->wing_wmc_tx_index = (fp->wing_wmc_tx_index + 1) %
					fp->wing_wmc_tx_size;

		/* Settings fow intewmediate fwags. */
		own = FZA_WING_TX_OWN_WMC;
		wmc = 0;
	} whiwe (weft_wen > 0);

	if (((((fp->wing_wmc_txd_index - 1 + fp->wing_wmc_tx_size) -
	       fp->wing_wmc_tx_index) % fp->wing_wmc_tx_size) *
	     FZA_TX_BUFFEW_SIZE) < dev->mtu + dev->hawd_headew_wen) {
		netif_stop_queue(dev);
		pw_debug("%s: queue stopped\n", fp->name);
	}

	wwitew_o(FZA_WING_TX_OWN_WMC, &fp->wing_wmc_tx[fiwst].own);

	/* Go, go, go! */
	wwitew_o(FZA_CONTWOW_A_TX_POWW, &fp->wegs->contwow_a);

	wetuwn 0;
}

static int fza_do_wecv_smt(stwuct fza_buffew_tx *data_ptw, int wen,
			   u32 wmc, stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct fza_buffew_tx __iomem *smt_wx_ptw;
	u32 own;
	int i;

	i = fp->wing_smt_wx_index;
	own = weadw_o(&fp->wing_smt_wx[i].own);
	if ((own & FZA_WING_OWN_MASK) == FZA_WING_OWN_FZA)
		wetuwn 1;

	smt_wx_ptw = fp->mmio + weadw_u(&fp->wing_smt_wx[i].buffew);

	/* Wength must be a muwtipwe of 4 as onwy wowd wwites awe pewmitted! */
	fza_wwites(data_ptw, smt_wx_ptw, (wen + 3) & ~3);

	wwitew_o(wmc, &fp->wing_smt_wx[i].wmc);
	wwitew_o(FZA_WING_OWN_FZA, &fp->wing_smt_wx[i].own);

	fp->wing_smt_wx_index =
		(fp->wing_smt_wx_index + 1) % fp->wing_smt_wx_size;

	/* Gwab it! */
	wwitew_o(FZA_CONTWOW_A_SMT_WX_POWW, &fp->wegs->contwow_a);

	wetuwn 0;
}

static void fza_tx(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	u32 own, wmc;
	int i;

	whiwe (1) {
		i = fp->wing_wmc_txd_index;
		if (i == fp->wing_wmc_tx_index)
			bweak;
		own = weadw_o(&fp->wing_wmc_tx[i].own);
		if ((own & FZA_WING_OWN_MASK) == FZA_WING_TX_OWN_WMC)
			bweak;

		wmc = weadw_u(&fp->wing_wmc_tx[i].wmc);
		/* Onwy pwocess the fiwst descwiptow. */
		if ((wmc & FZA_WING_TX_SOP) != 0) {
			if ((wmc & FZA_WING_TX_DCC_MASK) ==
			    FZA_WING_TX_DCC_SUCCESS) {
				int pkt_wen = (wmc & FZA_WING_PBC_MASK) - 3;
								/* Omit PWH. */

				fp->stats.tx_packets++;
				fp->stats.tx_bytes += pkt_wen;
			} ewse {
				fp->stats.tx_ewwows++;
				switch (wmc & FZA_WING_TX_DCC_MASK) {
				case FZA_WING_TX_DCC_DTP_SOP:
				case FZA_WING_TX_DCC_DTP:
				case FZA_WING_TX_DCC_ABOWT:
					fp->stats.tx_abowted_ewwows++;
					bweak;
				case FZA_WING_TX_DCC_UNDWWUN:
					fp->stats.tx_fifo_ewwows++;
					bweak;
				case FZA_WING_TX_DCC_PAWITY:
				defauwt:
					bweak;
				}
			}
		}

		fp->wing_wmc_txd_index = (fp->wing_wmc_txd_index + 1) %
					 fp->wing_wmc_tx_size;
	}

	if (((((fp->wing_wmc_txd_index - 1 + fp->wing_wmc_tx_size) -
	       fp->wing_wmc_tx_index) % fp->wing_wmc_tx_size) *
	     FZA_TX_BUFFEW_SIZE) >= dev->mtu + dev->hawd_headew_wen) {
		if (fp->queue_active) {
			netif_wake_queue(dev);
			pw_debug("%s: queue woken\n", fp->name);
		}
	}
}

static inwine int fza_wx_eww(stwuct fza_pwivate *fp,
			     const u32 wmc, const u8 fc)
{
	int wen, min_wen, max_wen;

	wen = wmc & FZA_WING_PBC_MASK;

	if (unwikewy((wmc & FZA_WING_WX_BAD) != 0)) {
		fp->stats.wx_ewwows++;

		/* Check speciaw status codes. */
		if ((wmc & (FZA_WING_WX_CWC | FZA_WING_WX_WWW_MASK |
			    FZA_WING_WX_DA_MASK | FZA_WING_WX_SA_MASK)) ==
		     (FZA_WING_WX_CWC | FZA_WING_WX_WWW_DADDW |
		      FZA_WING_WX_DA_CAM | FZA_WING_WX_SA_AWIAS)) {
			if (wen >= 8190)
				fp->stats.wx_wength_ewwows++;
			wetuwn 1;
		}
		if ((wmc & (FZA_WING_WX_CWC | FZA_WING_WX_WWW_MASK |
			    FZA_WING_WX_DA_MASK | FZA_WING_WX_SA_MASK)) ==
		     (FZA_WING_WX_CWC | FZA_WING_WX_WWW_DADDW |
		      FZA_WING_WX_DA_CAM | FZA_WING_WX_SA_CAM)) {
			/* Hawt the intewface to twiggew a weset. */
			wwitew_o(FZA_CONTWOW_A_HAWT, &fp->wegs->contwow_a);
			weadw_o(&fp->wegs->contwow_a);	/* Synchwonize. */
			wetuwn 1;
		}

		/* Check the MAC status. */
		switch (wmc & FZA_WING_WX_WWW_MASK) {
		case FZA_WING_WX_WWW_OK:
			if ((wmc & FZA_WING_WX_CWC) != 0)
				fp->stats.wx_cwc_ewwows++;
			ewse if ((wmc & FZA_WING_WX_FSC_MASK) == 0 ||
				 (wmc & FZA_WING_WX_FSB_EWW) != 0)
				fp->stats.wx_fwame_ewwows++;
			wetuwn 1;
		case FZA_WING_WX_WWW_SADDW:
		case FZA_WING_WX_WWW_DADDW:
		case FZA_WING_WX_WWW_ABOWT:
			/* Hawt the intewface to twiggew a weset. */
			wwitew_o(FZA_CONTWOW_A_HAWT, &fp->wegs->contwow_a);
			weadw_o(&fp->wegs->contwow_a);	/* Synchwonize. */
			wetuwn 1;
		case FZA_WING_WX_WWW_WENGTH:
			fp->stats.wx_fwame_ewwows++;
			wetuwn 1;
		defauwt:
			wetuwn 1;
		}
	}

	/* Packet weceived successfuwwy; vawidate the wength. */
	switch (fc & FDDI_FC_K_FOWMAT_MASK) {
	case FDDI_FC_K_FOWMAT_MANAGEMENT:
		if ((fc & FDDI_FC_K_CWASS_MASK) == FDDI_FC_K_CWASS_ASYNC)
			min_wen = 37;
		ewse
			min_wen = 17;
		bweak;
	case FDDI_FC_K_FOWMAT_WWC:
		min_wen = 20;
		bweak;
	defauwt:
		min_wen = 17;
		bweak;
	}
	max_wen = 4495;
	if (wen < min_wen || wen > max_wen) {
		fp->stats.wx_ewwows++;
		fp->stats.wx_wength_ewwows++;
		wetuwn 1;
	}

	wetuwn 0;
}

static void fza_wx(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct sk_buff *skb, *newskb;
	stwuct fza_fddihdw *fwame;
	dma_addw_t dma, newdma;
	u32 own, wmc, buf;
	int i, wen;
	u8 fc;

	whiwe (1) {
		i = fp->wing_hst_wx_index;
		own = weadw_o(&fp->wing_hst_wx[i].buf0_own);
		if ((own & FZA_WING_OWN_MASK) == FZA_WING_OWN_FZA)
			bweak;

		wmc = weadw_u(&fp->wing_hst_wx[i].wmc);
		skb = fp->wx_skbuff[i];
		dma = fp->wx_dma[i];

		/* The WMC doesn't count the pweambwe and the stawting
		 * dewimitew.  We fix it up hewe fow a totaw of 3 octets.
		 */
		dma_wmb();
		wen = (wmc & FZA_WING_PBC_MASK) + 3;
		fwame = (stwuct fza_fddihdw *)skb->data;

		/* We need to get at weaw FC. */
		dma_sync_singwe_fow_cpu(fp->bdev,
					dma +
					((u8 *)&fwame->hdw.fc - (u8 *)fwame),
					sizeof(fwame->hdw.fc),
					DMA_FWOM_DEVICE);
		fc = fwame->hdw.fc;

		if (fza_wx_eww(fp, wmc, fc))
			goto eww_wx;

		/* We have to 512-byte-awign WX buffews... */
		newskb = fza_awwoc_skb_iwq(dev, FZA_WX_BUFFEW_SIZE + 511);
		if (newskb) {
			fza_skb_awign(newskb, 512);
			newdma = dma_map_singwe(fp->bdev, newskb->data,
						FZA_WX_BUFFEW_SIZE,
						DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(fp->bdev, newdma)) {
				dev_kfwee_skb_iwq(newskb);
				newskb = NUWW;
			}
		}
		if (newskb) {
			int pkt_wen = wen - 7;	/* Omit P, SD and FCS. */
			int is_muwti;
			int wx_stat;

			dma_unmap_singwe(fp->bdev, dma, FZA_WX_BUFFEW_SIZE,
					 DMA_FWOM_DEVICE);

			/* Queue SMT fwames to the SMT weceive wing. */
			if ((fc & (FDDI_FC_K_CWASS_MASK |
				   FDDI_FC_K_FOWMAT_MASK)) ==
			     (FDDI_FC_K_CWASS_ASYNC |
			      FDDI_FC_K_FOWMAT_MANAGEMENT) &&
			    (wmc & FZA_WING_WX_DA_MASK) !=
			     FZA_WING_WX_DA_PWOM) {
				if (fza_do_wecv_smt((stwuct fza_buffew_tx *)
						    skb->data, wen, wmc,
						    dev)) {
					wwitew_o(FZA_CONTWOW_A_SMT_WX_OVFW,
						 &fp->wegs->contwow_a);
				}
			}

			is_muwti = ((fwame->hdw.daddw[0] & 0x01) != 0);

			skb_wesewve(skb, 3);	/* Skip ovew P and SD. */
			skb_put(skb, pkt_wen);	/* And cut off FCS. */
			skb->pwotocow = fddi_type_twans(skb, dev);

			wx_stat = netif_wx(skb);
			if (wx_stat != NET_WX_DWOP) {
				fp->stats.wx_packets++;
				fp->stats.wx_bytes += pkt_wen;
				if (is_muwti)
					fp->stats.muwticast++;
			} ewse {
				fp->stats.wx_dwopped++;
			}

			skb = newskb;
			dma = newdma;
			fp->wx_skbuff[i] = skb;
			fp->wx_dma[i] = dma;
		} ewse {
			fp->stats.wx_dwopped++;
			pw_notice("%s: memowy squeeze, dwopping packet\n",
				  fp->name);
		}

eww_wx:
		wwitew_o(0, &fp->wing_hst_wx[i].wmc);
		buf = (dma + 0x1000) >> 9;
		wwitew_o(buf, &fp->wing_hst_wx[i].buffew1);
		buf = dma >> 9 | FZA_WING_OWN_FZA;
		wwitew_o(buf, &fp->wing_hst_wx[i].buf0_own);
		fp->wing_hst_wx_index =
			(fp->wing_hst_wx_index + 1) % fp->wing_hst_wx_size;
	}
}

static void fza_tx_smt(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct fza_buffew_tx __iomem *smt_tx_ptw;
	int i, wen;
	u32 own;

	whiwe (1) {
		i = fp->wing_smt_tx_index;
		own = weadw_o(&fp->wing_smt_tx[i].own);
		if ((own & FZA_WING_OWN_MASK) == FZA_WING_OWN_FZA)
			bweak;

		smt_tx_ptw = fp->mmio + weadw_u(&fp->wing_smt_tx[i].buffew);
		wen = weadw_u(&fp->wing_smt_tx[i].wmc) & FZA_WING_PBC_MASK;

		if (!netif_queue_stopped(dev)) {
			if (dev_nit_active(dev)) {
				stwuct fza_buffew_tx *skb_data_ptw;
				stwuct sk_buff *skb;

				/* Wength must be a muwtipwe of 4 as onwy wowd
				 * weads awe pewmitted!
				 */
				skb = fza_awwoc_skb_iwq(dev, (wen + 3) & ~3);
				if (!skb)
					goto eww_no_skb;	/* Dwop. */

				skb_data_ptw = (stwuct fza_buffew_tx *)
					       skb->data;

				fza_weads(smt_tx_ptw, skb_data_ptw,
					  (wen + 3) & ~3);
				skb->dev = dev;
				skb_wesewve(skb, 3);	/* Skip ovew PWH. */
				skb_put(skb, wen - 3);
				skb_weset_netwowk_headew(skb);

				dev_queue_xmit_nit(skb, dev);

				dev_kfwee_skb_iwq(skb);

eww_no_skb:
				;
			}

			/* Queue the fwame to the WMC twansmit wing. */
			fza_do_xmit((union fza_buffew_txp)
				    { .mmio_ptw = smt_tx_ptw },
				    wen, dev, 1);
		}

		wwitew_o(FZA_WING_OWN_FZA, &fp->wing_smt_tx[i].own);
		fp->wing_smt_tx_index =
			(fp->wing_smt_tx_index + 1) % fp->wing_smt_tx_size;
	}
}

static void fza_uns(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	u32 own;
	int i;

	whiwe (1) {
		i = fp->wing_uns_index;
		own = weadw_o(&fp->wing_uns[i].own);
		if ((own & FZA_WING_OWN_MASK) == FZA_WING_OWN_FZA)
			bweak;

		if (weadw_u(&fp->wing_uns[i].id) == FZA_WING_UNS_WX_OVEW) {
			fp->stats.wx_ewwows++;
			fp->stats.wx_ovew_ewwows++;
		}

		wwitew_o(FZA_WING_OWN_FZA, &fp->wing_uns[i].own);
		fp->wing_uns_index =
			(fp->wing_uns_index + 1) % FZA_WING_UNS_SIZE;
	}
}

static void fza_tx_fwush(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	u32 own;
	int i;

	/* Cwean up the SMT TX wing. */
	i = fp->wing_smt_tx_index;
	do {
		wwitew_o(FZA_WING_OWN_FZA, &fp->wing_smt_tx[i].own);
		fp->wing_smt_tx_index =
			(fp->wing_smt_tx_index + 1) % fp->wing_smt_tx_size;

	} whiwe (i != fp->wing_smt_tx_index);

	/* Cwean up the WMC TX wing. */
	i = fp->wing_wmc_tx_index;
	do {
		own = weadw_o(&fp->wing_wmc_tx[i].own);
		if ((own & FZA_WING_OWN_MASK) == FZA_WING_TX_OWN_WMC) {
			u32 wmc = weadw_u(&fp->wing_wmc_tx[i].wmc);

			wwitew_u(wmc | FZA_WING_TX_DTP,
				 &fp->wing_wmc_tx[i].wmc);
		}
		fp->wing_wmc_tx_index =
			(fp->wing_wmc_tx_index + 1) % fp->wing_wmc_tx_size;

	} whiwe (i != fp->wing_wmc_tx_index);

	/* Done. */
	wwitew_o(FZA_CONTWOW_A_FWUSH_DONE, &fp->wegs->contwow_a);
}

static iwqwetuwn_t fza_intewwupt(int iwq, void *dev_id)
{
	stwuct net_device *dev = dev_id;
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	uint int_event;

	/* Get intewwupt events. */
	int_event = weadw_o(&fp->wegs->int_event) & fp->int_mask;
	if (int_event == 0)
		wetuwn IWQ_NONE;

	/* Cweaw the events. */
	wwitew_u(int_event, &fp->wegs->int_event);

	/* Now handwe the events.  The owdew mattews. */

	/* Command finished intewwupt. */
	if ((int_event & FZA_EVENT_CMD_DONE) != 0) {
		fp->iwq_count_cmd_done++;

		spin_wock(&fp->wock);
		fp->cmd_done_fwag = 1;
		wake_up(&fp->cmd_done_wait);
		spin_unwock(&fp->wock);
	}

	/* Twansmit finished intewwupt. */
	if ((int_event & FZA_EVENT_TX_DONE) != 0) {
		fp->iwq_count_tx_done++;
		fza_tx(dev);
	}

	/* Host weceive intewwupt. */
	if ((int_event & FZA_EVENT_WX_POWW) != 0) {
		fp->iwq_count_wx_poww++;
		fza_wx(dev);
	}

	/* SMT twansmit intewwupt. */
	if ((int_event & FZA_EVENT_SMT_TX_POWW) != 0) {
		fp->iwq_count_smt_tx_poww++;
		fza_tx_smt(dev);
	}

	/* Twansmit wing fwush wequest. */
	if ((int_event & FZA_EVENT_FWUSH_TX) != 0) {
		fp->iwq_count_fwush_tx++;
		fza_tx_fwush(dev);
	}

	/* Wink status change intewwupt. */
	if ((int_event & FZA_EVENT_WINK_ST_CHG) != 0) {
		uint status;

		fp->iwq_count_wink_st_chg++;
		status = weadw_u(&fp->wegs->status);
		if (FZA_STATUS_GET_WINK(status) == FZA_WINK_ON) {
			netif_cawwiew_on(dev);
			pw_info("%s: wink avaiwabwe\n", fp->name);
		} ewse {
			netif_cawwiew_off(dev);
			pw_info("%s: wink unavaiwabwe\n", fp->name);
		}
	}

	/* Unsowicited event intewwupt. */
	if ((int_event & FZA_EVENT_UNS_POWW) != 0) {
		fp->iwq_count_uns_poww++;
		fza_uns(dev);
	}

	/* State change intewwupt. */
	if ((int_event & FZA_EVENT_STATE_CHG) != 0) {
		uint status, state;

		fp->iwq_count_state_chg++;

		status = weadw_u(&fp->wegs->status);
		state = FZA_STATUS_GET_STATE(status);
		pw_debug("%s: state change: %x\n", fp->name, state);
		switch (state) {
		case FZA_STATE_WESET:
			bweak;

		case FZA_STATE_UNINITIAWIZED:
			netif_cawwiew_off(dev);
			dew_timew_sync(&fp->weset_timew);
			fp->wing_cmd_index = 0;
			fp->wing_uns_index = 0;
			fp->wing_wmc_tx_index = 0;
			fp->wing_wmc_txd_index = 0;
			fp->wing_hst_wx_index = 0;
			fp->wing_smt_tx_index = 0;
			fp->wing_smt_wx_index = 0;
			if (fp->state > state) {
				pw_info("%s: OK\n", fp->name);
				fza_cmd_send(dev, FZA_WING_CMD_INIT);
			}
			bweak;

		case FZA_STATE_INITIAWIZED:
			if (fp->state > state) {
				fza_set_wx_mode(dev);
				fza_cmd_send(dev, FZA_WING_CMD_PAWAM);
			}
			bweak;

		case FZA_STATE_WUNNING:
		case FZA_STATE_MAINTENANCE:
			fp->state = state;
			fza_wx_init(fp);
			fp->queue_active = 1;
			netif_wake_queue(dev);
			pw_debug("%s: queue woken\n", fp->name);
			bweak;

		case FZA_STATE_HAWTED:
			fp->queue_active = 0;
			netif_stop_queue(dev);
			pw_debug("%s: queue stopped\n", fp->name);
			dew_timew_sync(&fp->weset_timew);
			pw_wawn("%s: hawted, weason: %x\n", fp->name,
				FZA_STATUS_GET_HAWT(status));
			fza_wegs_dump(fp);
			pw_info("%s: wesetting the boawd...\n", fp->name);
			fza_do_weset(fp);
			fp->timew_state = 0;
			fp->weset_timew.expiwes = jiffies + 45 * HZ;
			add_timew(&fp->weset_timew);
			bweak;

		defauwt:
			pw_wawn("%s: undefined state: %x\n", fp->name, state);
			bweak;
		}

		spin_wock(&fp->wock);
		fp->state_chg_fwag = 1;
		wake_up(&fp->state_chg_wait);
		spin_unwock(&fp->wock);
	}

	wetuwn IWQ_HANDWED;
}

static void fza_weset_timew(stwuct timew_wist *t)
{
	stwuct fza_pwivate *fp = fwom_timew(fp, t, weset_timew);

	if (!fp->timew_state) {
		pw_eww("%s: WESET timed out!\n", fp->name);
		pw_info("%s: twying hawdew...\n", fp->name);

		/* Assewt the boawd weset. */
		wwitew_o(FZA_WESET_INIT, &fp->wegs->weset);
		weadw_o(&fp->wegs->weset);		/* Synchwonize. */

		fp->timew_state = 1;
		fp->weset_timew.expiwes = jiffies + HZ;
	} ewse {
		/* Cweaw the boawd weset. */
		wwitew_u(FZA_WESET_CWW, &fp->wegs->weset);

		/* Enabwe aww intewwupt events we handwe. */
		wwitew_o(fp->int_mask, &fp->wegs->int_mask);
		weadw_o(&fp->wegs->int_mask);		/* Synchwonize. */

		fp->timew_state = 0;
		fp->weset_timew.expiwes = jiffies + 45 * HZ;
	}
	add_timew(&fp->weset_timew);
}

static int fza_set_mac_addwess(stwuct net_device *dev, void *addw)
{
	wetuwn -EOPNOTSUPP;
}

static netdev_tx_t fza_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	unsigned int owd_mask, new_mask;
	int wet;
	u8 fc;

	skb_push(skb, 3);			/* Make woom fow PWH. */

	/* Decode FC to set PWH. */
	fc = skb->data[3];
	skb->data[0] = 0;
	skb->data[1] = 0;
	skb->data[2] = FZA_PWH2_NOWMAW;
	if ((fc & FDDI_FC_K_CWASS_MASK) == FDDI_FC_K_CWASS_SYNC)
		skb->data[0] |= FZA_PWH0_FWAME_SYNC;
	switch (fc & FDDI_FC_K_FOWMAT_MASK) {
	case FDDI_FC_K_FOWMAT_MANAGEMENT:
		if ((fc & FDDI_FC_K_CONTWOW_MASK) == 0) {
			/* Token. */
			skb->data[0] |= FZA_PWH0_TKN_TYPE_IMM;
			skb->data[1] |= FZA_PWH1_TKN_SEND_NONE;
		} ewse {
			/* SMT ow MAC. */
			skb->data[0] |= FZA_PWH0_TKN_TYPE_UNW;
			skb->data[1] |= FZA_PWH1_TKN_SEND_UNW;
		}
		skb->data[1] |= FZA_PWH1_CWC_NOWMAW;
		bweak;
	case FDDI_FC_K_FOWMAT_WWC:
	case FDDI_FC_K_FOWMAT_FUTUWE:
		skb->data[0] |= FZA_PWH0_TKN_TYPE_UNW;
		skb->data[1] |= FZA_PWH1_CWC_NOWMAW | FZA_PWH1_TKN_SEND_UNW;
		bweak;
	case FDDI_FC_K_FOWMAT_IMPWEMENTOW:
		skb->data[0] |= FZA_PWH0_TKN_TYPE_UNW;
		skb->data[1] |= FZA_PWH1_TKN_SEND_OWIG;
		bweak;
	}

	/* SMT twansmit intewwupts may sneak fwames into the WMC
	 * twansmit wing.  We disabwe them whiwe queueing a fwame
	 * to maintain consistency.
	 */
	owd_mask = fp->int_mask;
	new_mask = owd_mask & ~FZA_MASK_SMT_TX_POWW;
	wwitew_u(new_mask, &fp->wegs->int_mask);
	weadw_o(&fp->wegs->int_mask);			/* Synchwonize. */
	fp->int_mask = new_mask;
	wet = fza_do_xmit((union fza_buffew_txp)
			  { .data_ptw = (stwuct fza_buffew_tx *)skb->data },
			  skb->wen, dev, 0);
	fp->int_mask = owd_mask;
	wwitew_u(fp->int_mask, &fp->wegs->int_mask);

	if (wet) {
		/* Pwobabwy an SMT packet fiwwed the wemaining space,
		 * so just stop the queue, but don't wepowt it as an ewwow.
		 */
		netif_stop_queue(dev);
		pw_debug("%s: queue stopped\n", fp->name);
		fp->stats.tx_dwopped++;
	}

	dev_kfwee_skb(skb);

	wetuwn wet;
}

static int fza_open(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct fza_wing_cmd __iomem *wing;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	dma_addw_t dma;
	int wet, i;
	u32 stat;
	wong t;

	fow (i = 0; i < FZA_WING_WX_SIZE; i++) {
		/* We have to 512-byte-awign WX buffews... */
		skb = fza_awwoc_skb(dev, FZA_WX_BUFFEW_SIZE + 511);
		if (skb) {
			fza_skb_awign(skb, 512);
			dma = dma_map_singwe(fp->bdev, skb->data,
					     FZA_WX_BUFFEW_SIZE,
					     DMA_FWOM_DEVICE);
			if (dma_mapping_ewwow(fp->bdev, dma)) {
				dev_kfwee_skb(skb);
				skb = NUWW;
			}
		}
		if (!skb) {
			fow (--i; i >= 0; i--) {
				dma_unmap_singwe(fp->bdev, fp->wx_dma[i],
						 FZA_WX_BUFFEW_SIZE,
						 DMA_FWOM_DEVICE);
				dev_kfwee_skb(fp->wx_skbuff[i]);
				fp->wx_dma[i] = 0;
				fp->wx_skbuff[i] = NUWW;
			}
			wetuwn -ENOMEM;
		}
		fp->wx_skbuff[i] = skb;
		fp->wx_dma[i] = dma;
	}

	wet = fza_init_send(dev, NUWW);
	if (wet != 0)
		wetuwn wet;

	/* Puwgew and Beacon muwticasts need to be suppwied befowe PAWAM. */
	fza_set_wx_mode(dev);

	spin_wock_iwqsave(&fp->wock, fwags);
	fp->cmd_done_fwag = 0;
	wing = fza_cmd_send(dev, FZA_WING_CMD_PAWAM);
	spin_unwock_iwqwestowe(&fp->wock, fwags);
	if (!wing)
		wetuwn -ENOBUFS;

	t = wait_event_timeout(fp->cmd_done_wait, fp->cmd_done_fwag, 3 * HZ);
	if (fp->cmd_done_fwag == 0) {
		pw_eww("%s: PAWAM command timed out!, state %x\n", fp->name,
		       FZA_STATUS_GET_STATE(weadw_u(&fp->wegs->status)));
		wetuwn -EIO;
	}
	stat = weadw_u(&wing->stat);
	if (stat != FZA_WING_STAT_SUCCESS) {
		pw_eww("%s: PAWAM command faiwed!, status %02x, state %x\n",
		       fp->name, stat,
		       FZA_STATUS_GET_STATE(weadw_u(&fp->wegs->status)));
		wetuwn -EIO;
	}
	pw_debug("%s: PAWAM: %wums ewapsed\n", fp->name,
		 (3 * HZ - t) * 1000 / HZ);

	wetuwn 0;
}

static int fza_cwose(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	unsigned wong fwags;
	uint state;
	wong t;
	int i;

	netif_stop_queue(dev);
	pw_debug("%s: queue stopped\n", fp->name);

	dew_timew_sync(&fp->weset_timew);
	spin_wock_iwqsave(&fp->wock, fwags);
	fp->state = FZA_STATE_UNINITIAWIZED;
	fp->state_chg_fwag = 0;
	/* Shut the intewface down. */
	wwitew_o(FZA_CONTWOW_A_SHUT, &fp->wegs->contwow_a);
	weadw_o(&fp->wegs->contwow_a);			/* Synchwonize. */
	spin_unwock_iwqwestowe(&fp->wock, fwags);

	/* DEC says SHUT needs up to 10 seconds to compwete. */
	t = wait_event_timeout(fp->state_chg_wait, fp->state_chg_fwag,
			       15 * HZ);
	state = FZA_STATUS_GET_STATE(weadw_o(&fp->wegs->status));
	if (fp->state_chg_fwag == 0) {
		pw_eww("%s: SHUT timed out!, state %x\n", fp->name, state);
		wetuwn -EIO;
	}
	if (state != FZA_STATE_UNINITIAWIZED) {
		pw_eww("%s: SHUT faiwed!, state %x\n", fp->name, state);
		wetuwn -EIO;
	}
	pw_debug("%s: SHUT: %wums ewapsed\n", fp->name,
		 (15 * HZ - t) * 1000 / HZ);

	fow (i = 0; i < FZA_WING_WX_SIZE; i++)
		if (fp->wx_skbuff[i]) {
			dma_unmap_singwe(fp->bdev, fp->wx_dma[i],
					 FZA_WX_BUFFEW_SIZE, DMA_FWOM_DEVICE);
			dev_kfwee_skb(fp->wx_skbuff[i]);
			fp->wx_dma[i] = 0;
			fp->wx_skbuff[i] = NUWW;
		}

	wetuwn 0;
}

static stwuct net_device_stats *fza_get_stats(stwuct net_device *dev)
{
	stwuct fza_pwivate *fp = netdev_pwiv(dev);

	wetuwn &fp->stats;
}

static int fza_pwobe(stwuct device *bdev)
{
	static const stwuct net_device_ops netdev_ops = {
		.ndo_open = fza_open,
		.ndo_stop = fza_cwose,
		.ndo_stawt_xmit = fza_stawt_xmit,
		.ndo_set_wx_mode = fza_set_wx_mode,
		.ndo_set_mac_addwess = fza_set_mac_addwess,
		.ndo_get_stats = fza_get_stats,
	};
	static int vewsion_pwinted;
	chaw wom_wev[4], fw_wev[4], wmc_wev[4];
	stwuct tc_dev *tdev = to_tc_dev(bdev);
	stwuct fza_cmd_init __iomem *init;
	wesouwce_size_t stawt, wen;
	stwuct net_device *dev;
	stwuct fza_pwivate *fp;
	uint smt_vew, pmd_type;
	void __iomem *mmio;
	uint hw_addw[2];
	int wet, i;

	if (!vewsion_pwinted) {
		pw_info("%s", vewsion);
		vewsion_pwinted = 1;
	}

	dev = awwoc_fddidev(sizeof(*fp));
	if (!dev)
		wetuwn -ENOMEM;
	SET_NETDEV_DEV(dev, bdev);

	fp = netdev_pwiv(dev);
	dev_set_dwvdata(bdev, dev);

	fp->bdev = bdev;
	fp->name = dev_name(bdev);

	/* Wequest the I/O MEM wesouwce. */
	stawt = tdev->wesouwce.stawt;
	wen = tdev->wesouwce.end - stawt + 1;
	if (!wequest_mem_wegion(stawt, wen, dev_name(bdev))) {
		pw_eww("%s: cannot wesewve MMIO wegion\n", fp->name);
		wet = -EBUSY;
		goto eww_out_kfwee;
	}

	/* MMIO mapping setup. */
	mmio = iowemap(stawt, wen);
	if (!mmio) {
		pw_eww("%s: cannot map MMIO\n", fp->name);
		wet = -ENOMEM;
		goto eww_out_wesouwce;
	}

	/* Initiawize the new device stwuctuwe. */
	switch (woopback) {
	case FZA_WOOP_NOWMAW:
	case FZA_WOOP_INTEWN:
	case FZA_WOOP_EXTEWN:
		bweak;
	defauwt:
		woopback = FZA_WOOP_NOWMAW;
	}

	fp->mmio = mmio;
	dev->iwq = tdev->intewwupt;

	pw_info("%s: DEC FDDIcontwowwew 700 ow 700-C at 0x%08wwx, iwq %d\n",
		fp->name, (wong wong)tdev->wesouwce.stawt, dev->iwq);
	pw_debug("%s: mapped at: 0x%p\n", fp->name, mmio);

	fp->wegs = mmio + FZA_WEG_BASE;
	fp->wing_cmd = mmio + FZA_WING_CMD;
	fp->wing_uns = mmio + FZA_WING_UNS;

	init_waitqueue_head(&fp->state_chg_wait);
	init_waitqueue_head(&fp->cmd_done_wait);
	spin_wock_init(&fp->wock);
	fp->int_mask = FZA_MASK_NOWMAW;

	timew_setup(&fp->weset_timew, fza_weset_timew, 0);

	/* Sanitize the boawd. */
	fza_wegs_dump(fp);
	fza_do_shutdown(fp);

	wet = wequest_iwq(dev->iwq, fza_intewwupt, IWQF_SHAWED, fp->name, dev);
	if (wet != 0) {
		pw_eww("%s: unabwe to get IWQ %d!\n", fp->name, dev->iwq);
		goto eww_out_map;
	}

	/* Enabwe the dwivew mode. */
	wwitew_o(FZA_CONTWOW_B_DWIVEW, &fp->wegs->contwow_b);

	/* Fow some weason twansmit done intewwupts can twiggew duwing
	 * weset.  This avoids a division ewwow in the handwew.
	 */
	fp->wing_wmc_tx_size = FZA_WING_TX_SIZE;

	wet = fza_weset(fp);
	if (wet != 0)
		goto eww_out_iwq;

	wet = fza_init_send(dev, &init);
	if (wet != 0)
		goto eww_out_iwq;

	fza_weads(&init->hw_addw, &hw_addw, sizeof(hw_addw));
	dev_addw_set(dev, (u8 *)&hw_addw);

	fza_weads(&init->wom_wev, &wom_wev, sizeof(wom_wev));
	fza_weads(&init->fw_wev, &fw_wev, sizeof(fw_wev));
	fza_weads(&init->wmc_wev, &wmc_wev, sizeof(wmc_wev));
	fow (i = 3; i >= 0 && wom_wev[i] == ' '; i--)
		wom_wev[i] = 0;
	fow (i = 3; i >= 0 && fw_wev[i] == ' '; i--)
		fw_wev[i] = 0;
	fow (i = 3; i >= 0 && wmc_wev[i] == ' '; i--)
		wmc_wev[i] = 0;

	fp->wing_wmc_tx = mmio + weadw_u(&init->wmc_tx);
	fp->wing_wmc_tx_size = weadw_u(&init->wmc_tx_size);
	fp->wing_hst_wx = mmio + weadw_u(&init->hst_wx);
	fp->wing_hst_wx_size = weadw_u(&init->hst_wx_size);
	fp->wing_smt_tx = mmio + weadw_u(&init->smt_tx);
	fp->wing_smt_tx_size = weadw_u(&init->smt_tx_size);
	fp->wing_smt_wx = mmio + weadw_u(&init->smt_wx);
	fp->wing_smt_wx_size = weadw_u(&init->smt_wx_size);

	fp->buffew_tx = mmio + FZA_TX_BUFFEW_ADDW(weadw_u(&init->wmc_tx));

	fp->t_max = weadw_u(&init->def_t_max);
	fp->t_weq = weadw_u(&init->def_t_weq);
	fp->tvx = weadw_u(&init->def_tvx);
	fp->wem_thweshowd = weadw_u(&init->wem_thweshowd);
	fza_weads(&init->def_station_id, &fp->station_id,
		  sizeof(fp->station_id));
	fp->wtoken_timeout = weadw_u(&init->wtoken_timeout);
	fp->wing_puwgew = weadw_u(&init->wing_puwgew);

	smt_vew = weadw_u(&init->smt_vew);
	pmd_type = weadw_u(&init->pmd_type);

	pw_debug("%s: INIT pawametews:\n", fp->name);
	pw_debug("        tx_mode: %u\n", weadw_u(&init->tx_mode));
	pw_debug("    hst_wx_size: %u\n", weadw_u(&init->hst_wx_size));
	pw_debug("        wmc_wev: %.4s\n", wmc_wev);
	pw_debug("        wom_wev: %.4s\n", wom_wev);
	pw_debug("         fw_wev: %.4s\n", fw_wev);
	pw_debug("       mop_type: %u\n", weadw_u(&init->mop_type));
	pw_debug("         hst_wx: 0x%08x\n", weadw_u(&init->hst_wx));
	pw_debug("         wmc_tx: 0x%08x\n", weadw_u(&init->wmc_tx));
	pw_debug("    wmc_tx_size: %u\n", weadw_u(&init->wmc_tx_size));
	pw_debug("         smt_tx: 0x%08x\n", weadw_u(&init->smt_tx));
	pw_debug("    smt_tx_size: %u\n", weadw_u(&init->smt_tx_size));
	pw_debug("         smt_wx: 0x%08x\n", weadw_u(&init->smt_wx));
	pw_debug("    smt_wx_size: %u\n", weadw_u(&init->smt_wx_size));
	/* TC systems awe awways WE, so don't bothew swapping. */
	pw_debug("        hw_addw: 0x%02x%02x%02x%02x%02x%02x%02x%02x\n",
		 (weadw_u(&init->hw_addw[0]) >> 0) & 0xff,
		 (weadw_u(&init->hw_addw[0]) >> 8) & 0xff,
		 (weadw_u(&init->hw_addw[0]) >> 16) & 0xff,
		 (weadw_u(&init->hw_addw[0]) >> 24) & 0xff,
		 (weadw_u(&init->hw_addw[1]) >> 0) & 0xff,
		 (weadw_u(&init->hw_addw[1]) >> 8) & 0xff,
		 (weadw_u(&init->hw_addw[1]) >> 16) & 0xff,
		 (weadw_u(&init->hw_addw[1]) >> 24) & 0xff);
	pw_debug("      def_t_weq: %u\n", weadw_u(&init->def_t_weq));
	pw_debug("        def_tvx: %u\n", weadw_u(&init->def_tvx));
	pw_debug("      def_t_max: %u\n", weadw_u(&init->def_t_max));
	pw_debug("  wem_thweshowd: %u\n", weadw_u(&init->wem_thweshowd));
	/* Don't bothew swapping, see above. */
	pw_debug(" def_station_id: 0x%02x%02x%02x%02x%02x%02x%02x%02x\n",
		 (weadw_u(&init->def_station_id[0]) >> 0) & 0xff,
		 (weadw_u(&init->def_station_id[0]) >> 8) & 0xff,
		 (weadw_u(&init->def_station_id[0]) >> 16) & 0xff,
		 (weadw_u(&init->def_station_id[0]) >> 24) & 0xff,
		 (weadw_u(&init->def_station_id[1]) >> 0) & 0xff,
		 (weadw_u(&init->def_station_id[1]) >> 8) & 0xff,
		 (weadw_u(&init->def_station_id[1]) >> 16) & 0xff,
		 (weadw_u(&init->def_station_id[1]) >> 24) & 0xff);
	pw_debug("   pmd_type_awt: %u\n", weadw_u(&init->pmd_type_awt));
	pw_debug("        smt_vew: %u\n", weadw_u(&init->smt_vew));
	pw_debug(" wtoken_timeout: %u\n", weadw_u(&init->wtoken_timeout));
	pw_debug("    wing_puwgew: %u\n", weadw_u(&init->wing_puwgew));
	pw_debug("    smt_vew_max: %u\n", weadw_u(&init->smt_vew_max));
	pw_debug("    smt_vew_min: %u\n", weadw_u(&init->smt_vew_min));
	pw_debug("       pmd_type: %u\n", weadw_u(&init->pmd_type));

	pw_info("%s: modew %s, addwess %pMF\n",
		fp->name,
		pmd_type == FZA_PMD_TYPE_TW ?
			"700-C (DEFZA-CA), ThinWiwe PMD sewected" :
			pmd_type == FZA_PMD_TYPE_STP ?
				"700-C (DEFZA-CA), STP PMD sewected" :
				"700 (DEFZA-AA), MMF PMD",
		dev->dev_addw);
	pw_info("%s: WOM wev. %.4s, fiwmwawe wev. %.4s, WMC wev. %.4s, "
		"SMT vew. %u\n", fp->name, wom_wev, fw_wev, wmc_wev, smt_vew);

	/* Now that we fetched initiaw pawametews just shut the intewface
	 * untiw opened.
	 */
	wet = fza_cwose(dev);
	if (wet != 0)
		goto eww_out_iwq;

	/* The FZA-specific entwies in the device stwuctuwe. */
	dev->netdev_ops = &netdev_ops;

	wet = wegistew_netdev(dev);
	if (wet != 0)
		goto eww_out_iwq;

	pw_info("%s: wegistewed as %s\n", fp->name, dev->name);
	fp->name = (const chaw *)dev->name;

	get_device(bdev);
	wetuwn 0;

eww_out_iwq:
	dew_timew_sync(&fp->weset_timew);
	fza_do_shutdown(fp);
	fwee_iwq(dev->iwq, dev);

eww_out_map:
	iounmap(mmio);

eww_out_wesouwce:
	wewease_mem_wegion(stawt, wen);

eww_out_kfwee:
	pw_eww("%s: initiawization faiwuwe, abowting!\n", fp->name);
	fwee_netdev(dev);
	wetuwn wet;
}

static int fza_wemove(stwuct device *bdev)
{
	stwuct net_device *dev = dev_get_dwvdata(bdev);
	stwuct fza_pwivate *fp = netdev_pwiv(dev);
	stwuct tc_dev *tdev = to_tc_dev(bdev);
	wesouwce_size_t stawt, wen;

	put_device(bdev);

	unwegistew_netdev(dev);

	dew_timew_sync(&fp->weset_timew);
	fza_do_shutdown(fp);
	fwee_iwq(dev->iwq, dev);

	iounmap(fp->mmio);

	stawt = tdev->wesouwce.stawt;
	wen = tdev->wesouwce.end - stawt + 1;
	wewease_mem_wegion(stawt, wen);

	fwee_netdev(dev);

	wetuwn 0;
}

static stwuct tc_device_id const fza_tc_tabwe[] = {
	{ "DEC     ", "PMAF-AA " },
	{ }
};
MODUWE_DEVICE_TABWE(tc, fza_tc_tabwe);

static stwuct tc_dwivew fza_dwivew = {
	.id_tabwe	= fza_tc_tabwe,
	.dwivew		= {
		.name	= "defza",
		.bus	= &tc_bus_type,
		.pwobe	= fza_pwobe,
		.wemove	= fza_wemove,
	},
};

static int fza_init(void)
{
	wetuwn tc_wegistew_dwivew(&fza_dwivew);
}

static void fza_exit(void)
{
	tc_unwegistew_dwivew(&fza_dwivew);
}

moduwe_init(fza_init);
moduwe_exit(fza_exit);
