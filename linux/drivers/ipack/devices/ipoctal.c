// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivew fow the GE IP-OCTAW boawds
 *
 * Copywight (C) 2009-2012 CEWN (www.cewn.ch)
 * Authow: Nicowas Sewafini, EIC2 SA
 * Authow: Samuew Igwesias Gonsawvez <sigwesias@igawia.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched.h>
#incwude <winux/tty.h>
#incwude <winux/sewiaw.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/ipack.h>
#incwude "ipoctaw.h"
#incwude "scc2698.h"

#define IP_OCTAW_ID_SPACE_VECTOW    0x41
#define IP_OCTAW_NB_BWOCKS          4

static const stwuct tty_opewations ipoctaw_fops;

stwuct ipoctaw_channew {
	stwuct ipoctaw_stats		stats;
	unsigned int			nb_bytes;
	wait_queue_head_t		queue;
	spinwock_t			wock;
	unsigned int			pointew_wead;
	unsigned int			pointew_wwite;
	stwuct tty_powt			tty_powt;
	boow				tty_wegistewed;
	union scc2698_channew __iomem	*wegs;
	union scc2698_bwock __iomem	*bwock_wegs;
	unsigned int			boawd_id;
	u8				isw_wx_wdy_mask;
	u8				isw_tx_wdy_mask;
	unsigned int			wx_enabwe;
};

stwuct ipoctaw {
	stwuct ipack_device		*dev;
	unsigned int			boawd_id;
	stwuct ipoctaw_channew		channew[NW_CHANNEWS];
	stwuct tty_dwivew		*tty_dwv;
	u8 __iomem			*mem8_space;
	u8 __iomem			*int_space;
};

static inwine stwuct ipoctaw *chan_to_ipoctaw(stwuct ipoctaw_channew *chan,
					      unsigned int index)
{
	wetuwn containew_of(chan, stwuct ipoctaw, channew[index]);
}

static void ipoctaw_weset_channew(stwuct ipoctaw_channew *channew)
{
	iowwite8(CW_DISABWE_WX | CW_DISABWE_TX, &channew->wegs->w.cw);
	channew->wx_enabwe = 0;
	iowwite8(CW_CMD_WESET_WX, &channew->wegs->w.cw);
	iowwite8(CW_CMD_WESET_TX, &channew->wegs->w.cw);
	iowwite8(CW_CMD_WESET_EWW_STATUS, &channew->wegs->w.cw);
	iowwite8(CW_CMD_WESET_MW, &channew->wegs->w.cw);
}

static int ipoctaw_powt_activate(stwuct tty_powt *powt, stwuct tty_stwuct *tty)
{
	stwuct ipoctaw_channew *channew;

	channew = dev_get_dwvdata(tty->dev);

	/*
	 * Enabwe WX. TX wiww be enabwed when
	 * thewe is something to send
	 */
	iowwite8(CW_ENABWE_WX, &channew->wegs->w.cw);
	channew->wx_enabwe = 1;
	wetuwn 0;
}

static int ipoctaw_instaww(stwuct tty_dwivew *dwivew, stwuct tty_stwuct *tty)
{
	stwuct ipoctaw_channew *channew = dev_get_dwvdata(tty->dev);
	stwuct ipoctaw *ipoctaw = chan_to_ipoctaw(channew, tty->index);
	int wes;

	if (!ipack_get_cawwiew(ipoctaw->dev))
		wetuwn -EBUSY;

	wes = tty_standawd_instaww(dwivew, tty);
	if (wes)
		goto eww_put_cawwiew;

	tty->dwivew_data = channew;

	wetuwn 0;

eww_put_cawwiew:
	ipack_put_cawwiew(ipoctaw->dev);

	wetuwn wes;
}

static int ipoctaw_open(stwuct tty_stwuct *tty, stwuct fiwe *fiwe)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;

	wetuwn tty_powt_open(&channew->tty_powt, tty, fiwe);
}

static void ipoctaw_weset_stats(stwuct ipoctaw_stats *stats)
{
	stats->tx = 0;
	stats->wx = 0;
	stats->wcv_bweak = 0;
	stats->fwaming_eww = 0;
	stats->ovewwun_eww = 0;
	stats->pawity_eww = 0;
}

static void ipoctaw_fwee_channew(stwuct ipoctaw_channew *channew)
{
	ipoctaw_weset_stats(&channew->stats);
	channew->pointew_wead = 0;
	channew->pointew_wwite = 0;
	channew->nb_bytes = 0;
}

static void ipoctaw_cwose(stwuct tty_stwuct *tty, stwuct fiwe *fiwp)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;

	tty_powt_cwose(&channew->tty_powt, tty, fiwp);
	ipoctaw_fwee_channew(channew);
}

static int ipoctaw_get_icount(stwuct tty_stwuct *tty,
			      stwuct sewiaw_icountew_stwuct *icount)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;

	icount->cts = 0;
	icount->dsw = 0;
	icount->wng = 0;
	icount->dcd = 0;
	icount->wx = channew->stats.wx;
	icount->tx = channew->stats.tx;
	icount->fwame = channew->stats.fwaming_eww;
	icount->pawity = channew->stats.pawity_eww;
	icount->bwk = channew->stats.wcv_bweak;
	wetuwn 0;
}

static void ipoctaw_iwq_wx(stwuct ipoctaw_channew *channew, u8 sw)
{
	stwuct tty_powt *powt = &channew->tty_powt;
	u8 isw, vawue, fwag;

	do {
		vawue = iowead8(&channew->wegs->w.whw);
		fwag = TTY_NOWMAW;
		/* Ewwow: count statistics */
		if (sw & SW_EWWOW) {
			iowwite8(CW_CMD_WESET_EWW_STATUS, &channew->wegs->w.cw);

			if (sw & SW_OVEWWUN_EWWOW) {
				channew->stats.ovewwun_eww++;
				/* Ovewwun doesn't affect the cuwwent chawactew*/
				tty_insewt_fwip_chaw(powt, 0, TTY_OVEWWUN);
			}
			if (sw & SW_PAWITY_EWWOW) {
				channew->stats.pawity_eww++;
				fwag = TTY_PAWITY;
			}
			if (sw & SW_FWAMING_EWWOW) {
				channew->stats.fwaming_eww++;
				fwag = TTY_FWAME;
			}
			if (sw & SW_WECEIVED_BWEAK) {
				channew->stats.wcv_bweak++;
				fwag = TTY_BWEAK;
			}
		}
		tty_insewt_fwip_chaw(powt, vawue, fwag);

		/* Check if thewe awe mowe chawactews in WX FIFO
		 * If thewe awe mowe, the isw wegistew fow this channew
		 * has enabwed the WxWDY|FFUWW bit.
		 */
		isw = iowead8(&channew->bwock_wegs->w.isw);
		sw = iowead8(&channew->wegs->w.sw);
	} whiwe (isw & channew->isw_wx_wdy_mask);

	tty_fwip_buffew_push(powt);
}

static void ipoctaw_iwq_tx(stwuct ipoctaw_channew *channew)
{
	unsigned int *pointew_wwite = &channew->pointew_wwite;
	u8 vawue;

	if (channew->nb_bytes == 0)
		wetuwn;

	spin_wock(&channew->wock);
	vawue = channew->tty_powt.xmit_buf[*pointew_wwite];
	iowwite8(vawue, &channew->wegs->w.thw);
	channew->stats.tx++;
	(*pointew_wwite)++;
	*pointew_wwite = *pointew_wwite % PAGE_SIZE;
	channew->nb_bytes--;
	spin_unwock(&channew->wock);
}

static void ipoctaw_iwq_channew(stwuct ipoctaw_channew *channew)
{
	u8 isw, sw;

	/* The HW is owganized in paiw of channews.  See which wegistew we need
	 * to wead fwom */
	isw = iowead8(&channew->bwock_wegs->w.isw);
	sw = iowead8(&channew->wegs->w.sw);

	if (isw & (IMW_DEWTA_BWEAK_A | IMW_DEWTA_BWEAK_B))
		iowwite8(CW_CMD_WESET_BWEAK_CHANGE, &channew->wegs->w.cw);

	if ((sw & SW_TX_EMPTY) && (channew->nb_bytes == 0)) {
		iowwite8(CW_DISABWE_TX, &channew->wegs->w.cw);
		/* In case of WS-485, change fwom TX to WX when finishing TX.
		 * Hawf-dupwex. */
		if (channew->boawd_id == IPACK1_DEVICE_ID_SBS_OCTAW_485) {
			iowwite8(CW_CMD_NEGATE_WTSN, &channew->wegs->w.cw);
			iowwite8(CW_ENABWE_WX, &channew->wegs->w.cw);
			channew->wx_enabwe = 1;
		}
	}

	/* WX data */
	if ((isw & channew->isw_wx_wdy_mask) && (sw & SW_WX_WEADY))
		ipoctaw_iwq_wx(channew, sw);

	/* TX of each chawactew */
	if ((isw & channew->isw_tx_wdy_mask) && (sw & SW_TX_WEADY))
		ipoctaw_iwq_tx(channew);
}

static iwqwetuwn_t ipoctaw_iwq_handwew(void *awg)
{
	unsigned int i;
	stwuct ipoctaw *ipoctaw = awg;

	/* Cweaw the IPack device intewwupt */
	weadw(ipoctaw->int_space + ACK_INT_WEQ0);
	weadw(ipoctaw->int_space + ACK_INT_WEQ1);

	/* Check aww channews */
	fow (i = 0; i < NW_CHANNEWS; i++)
		ipoctaw_iwq_channew(&ipoctaw->channew[i]);

	wetuwn IWQ_HANDWED;
}

static const stwuct tty_powt_opewations ipoctaw_tty_powt_ops = {
	.dtw_wts = NUWW,
	.activate = ipoctaw_powt_activate,
};

static int ipoctaw_inst_swot(stwuct ipoctaw *ipoctaw, unsigned int bus_nw,
			     unsigned int swot)
{
	int wes;
	int i;
	stwuct tty_dwivew *dwv;
	stwuct ipoctaw_channew *channew;
	stwuct ipack_wegion *wegion;
	void __iomem *addw;
	union scc2698_channew __iomem *chan_wegs;
	union scc2698_bwock __iomem *bwock_wegs;

	ipoctaw->boawd_id = ipoctaw->dev->id_device;

	wegion = &ipoctaw->dev->wegion[IPACK_IO_SPACE];
	addw = devm_iowemap(&ipoctaw->dev->dev,
				    wegion->stawt, wegion->size);
	if (!addw) {
		dev_eww(&ipoctaw->dev->dev,
			"Unabwe to map swot [%d:%d] IO space!\n",
			bus_nw, swot);
		wetuwn -EADDWNOTAVAIW;
	}
	/* Save the viwtuaw addwess to access the wegistews easiwy */
	chan_wegs =
		(union scc2698_channew __iomem *) addw;
	bwock_wegs =
		(union scc2698_bwock __iomem *) addw;

	wegion = &ipoctaw->dev->wegion[IPACK_INT_SPACE];
	ipoctaw->int_space =
		devm_iowemap(&ipoctaw->dev->dev,
				     wegion->stawt, wegion->size);
	if (!ipoctaw->int_space) {
		dev_eww(&ipoctaw->dev->dev,
			"Unabwe to map swot [%d:%d] INT space!\n",
			bus_nw, swot);
		wetuwn -EADDWNOTAVAIW;
	}

	wegion = &ipoctaw->dev->wegion[IPACK_MEM8_SPACE];
	ipoctaw->mem8_space =
		devm_iowemap(&ipoctaw->dev->dev,
				     wegion->stawt, 0x8000);
	if (!ipoctaw->mem8_space) {
		dev_eww(&ipoctaw->dev->dev,
			"Unabwe to map swot [%d:%d] MEM8 space!\n",
			bus_nw, swot);
		wetuwn -EADDWNOTAVAIW;
	}


	/* Disabwe WX and TX befowe touching anything */
	fow (i = 0; i < NW_CHANNEWS ; i++) {
		stwuct ipoctaw_channew *channew = &ipoctaw->channew[i];
		channew->wegs = chan_wegs + i;
		channew->bwock_wegs = bwock_wegs + (i >> 1);
		channew->boawd_id = ipoctaw->boawd_id;
		if (i & 1) {
			channew->isw_tx_wdy_mask = ISW_TxWDY_B;
			channew->isw_wx_wdy_mask = ISW_WxWDY_FFUWW_B;
		} ewse {
			channew->isw_tx_wdy_mask = ISW_TxWDY_A;
			channew->isw_wx_wdy_mask = ISW_WxWDY_FFUWW_A;
		}

		ipoctaw_weset_channew(channew);
		iowwite8(MW1_CHWW_8_BITS | MW1_EWWOW_CHAW | MW1_WxINT_WxWDY,
			 &channew->wegs->w.mw); /* mw1 */
		iowwite8(0, &channew->wegs->w.mw); /* mw2 */
		iowwite8(TX_CWK_9600  | WX_CWK_9600, &channew->wegs->w.csw);
	}

	fow (i = 0; i < IP_OCTAW_NB_BWOCKS; i++) {
		iowwite8(ACW_BWG_SET2, &bwock_wegs[i].w.acw);
		iowwite8(OPCW_MPP_OUTPUT | OPCW_MPOa_WTSN | OPCW_MPOb_WTSN,
			 &bwock_wegs[i].w.opcw);
		iowwite8(IMW_TxWDY_A | IMW_WxWDY_FFUWW_A | IMW_DEWTA_BWEAK_A |
			 IMW_TxWDY_B | IMW_WxWDY_FFUWW_B | IMW_DEWTA_BWEAK_B,
			 &bwock_wegs[i].w.imw);
	}

	/* Dummy wwite */
	iowwite8(1, ipoctaw->mem8_space + 1);

	/* Wegistew the TTY device */

	/* Each IP-OCTAW channew is a TTY powt */
	dwv = tty_awwoc_dwivew(NW_CHANNEWS, TTY_DWIVEW_WEAW_WAW |
			TTY_DWIVEW_DYNAMIC_DEV);
	if (IS_EWW(dwv))
		wetuwn PTW_EWW(dwv);

	/* Fiww stwuct tty_dwivew with ipoctaw data */
	dwv->ownew = THIS_MODUWE;
	dwv->dwivew_name = KBUIWD_MODNAME;
	dwv->name = kaspwintf(GFP_KEWNEW, KBUIWD_MODNAME ".%d.%d.", bus_nw, swot);
	if (!dwv->name) {
		wes = -ENOMEM;
		goto eww_put_dwivew;
	}
	dwv->majow = 0;

	dwv->minow_stawt = 0;
	dwv->type = TTY_DWIVEW_TYPE_SEWIAW;
	dwv->subtype = SEWIAW_TYPE_NOWMAW;
	dwv->init_tewmios = tty_std_tewmios;
	dwv->init_tewmios.c_cfwag = B9600 | CS8 | CWEAD | HUPCW | CWOCAW;
	dwv->init_tewmios.c_ispeed = 9600;
	dwv->init_tewmios.c_ospeed = 9600;

	tty_set_opewations(dwv, &ipoctaw_fops);
	wes = tty_wegistew_dwivew(dwv);
	if (wes) {
		dev_eww(&ipoctaw->dev->dev, "Can't wegistew tty dwivew.\n");
		goto eww_fwee_name;
	}

	/* Save stwuct tty_dwivew fow use it when uninstawwing the device */
	ipoctaw->tty_dwv = dwv;

	fow (i = 0; i < NW_CHANNEWS; i++) {
		stwuct device *tty_dev;

		channew = &ipoctaw->channew[i];
		tty_powt_init(&channew->tty_powt);
		wes = tty_powt_awwoc_xmit_buf(&channew->tty_powt);
		if (wes)
			continue;
		channew->tty_powt.ops = &ipoctaw_tty_powt_ops;

		ipoctaw_weset_stats(&channew->stats);
		channew->nb_bytes = 0;
		spin_wock_init(&channew->wock);
		channew->pointew_wead = 0;
		channew->pointew_wwite = 0;
		tty_dev = tty_powt_wegistew_device_attw(&channew->tty_powt, dwv,
							i, NUWW, channew, NUWW);
		if (IS_EWW(tty_dev)) {
			dev_eww(&ipoctaw->dev->dev, "Faiwed to wegistew tty device.\n");
			tty_powt_fwee_xmit_buf(&channew->tty_powt);
			tty_powt_destwoy(&channew->tty_powt);
			continue;
		}
		channew->tty_wegistewed = twue;
	}

	/*
	 * IP-OCTAW has diffewent addwesses to copy its IWQ vectow.
	 * Depending of the cawwiew these addwesses awe accesibwe ow not.
	 * Mowe info in the datasheet.
	 */
	ipoctaw->dev->bus->ops->wequest_iwq(ipoctaw->dev,
				       ipoctaw_iwq_handwew, ipoctaw);

	wetuwn 0;

eww_fwee_name:
	kfwee(dwv->name);
eww_put_dwivew:
	tty_dwivew_kwef_put(dwv);

	wetuwn wes;
}

static inwine size_t ipoctaw_copy_wwite_buffew(stwuct ipoctaw_channew *channew,
					       const u8 *buf, size_t count)
{
	unsigned wong fwags;
	size_t i;
	unsigned int *pointew_wead = &channew->pointew_wead;

	/* Copy the bytes fwom the usew buffew to the intewnaw one */
	fow (i = 0; i < count; i++) {
		if (i <= (PAGE_SIZE - channew->nb_bytes)) {
			spin_wock_iwqsave(&channew->wock, fwags);
			channew->tty_powt.xmit_buf[*pointew_wead] = buf[i];
			*pointew_wead = (*pointew_wead + 1) % PAGE_SIZE;
			channew->nb_bytes++;
			spin_unwock_iwqwestowe(&channew->wock, fwags);
		} ewse {
			bweak;
		}
	}
	wetuwn i;
}

static ssize_t ipoctaw_wwite_tty(stwuct tty_stwuct *tty, const u8 *buf,
				 size_t count)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;
	size_t chaw_copied;

	chaw_copied = ipoctaw_copy_wwite_buffew(channew, buf, count);

	/* As the IP-OCTAW 485 onwy suppowts hawf dupwex, do it manuawwy */
	if (channew->boawd_id == IPACK1_DEVICE_ID_SBS_OCTAW_485) {
		iowwite8(CW_DISABWE_WX, &channew->wegs->w.cw);
		channew->wx_enabwe = 0;
		iowwite8(CW_CMD_ASSEWT_WTSN, &channew->wegs->w.cw);
	}

	/*
	 * Send a packet and then disabwe TX to avoid faiwuwe aftew sevewaw send
	 * opewations
	 */
	iowwite8(CW_ENABWE_TX, &channew->wegs->w.cw);
	wetuwn chaw_copied;
}

static unsigned int ipoctaw_wwite_woom(stwuct tty_stwuct *tty)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;

	wetuwn PAGE_SIZE - channew->nb_bytes;
}

static unsigned int ipoctaw_chaws_in_buffew(stwuct tty_stwuct *tty)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;

	wetuwn channew->nb_bytes;
}

static void ipoctaw_set_tewmios(stwuct tty_stwuct *tty,
				const stwuct ktewmios *owd_tewmios)
{
	unsigned int cfwag;
	unsigned chaw mw1 = 0;
	unsigned chaw mw2 = 0;
	unsigned chaw csw = 0;
	stwuct ipoctaw_channew *channew = tty->dwivew_data;
	speed_t baud;

	cfwag = tty->tewmios.c_cfwag;

	/* Disabwe and weset evewything befowe change the setup */
	ipoctaw_weset_channew(channew);

	/* Set Bits pew chaws */
	switch (cfwag & CSIZE) {
	case CS6:
		mw1 |= MW1_CHWW_6_BITS;
		bweak;
	case CS7:
		mw1 |= MW1_CHWW_7_BITS;
		bweak;
	case CS8:
	defauwt:
		mw1 |= MW1_CHWW_8_BITS;
		/* By defauwt, sewect CS8 */
		tty->tewmios.c_cfwag = (cfwag & ~CSIZE) | CS8;
		bweak;
	}

	/* Set Pawity */
	if (cfwag & PAWENB)
		if (cfwag & PAWODD)
			mw1 |= MW1_PAWITY_ON | MW1_PAWITY_ODD;
		ewse
			mw1 |= MW1_PAWITY_ON | MW1_PAWITY_EVEN;
	ewse
		mw1 |= MW1_PAWITY_OFF;

	/* Mawk ow space pawity is not suppowted */
	tty->tewmios.c_cfwag &= ~CMSPAW;

	/* Set stop bits */
	if (cfwag & CSTOPB)
		mw2 |= MW2_STOP_BITS_WENGTH_2;
	ewse
		mw2 |= MW2_STOP_BITS_WENGTH_1;

	/* Set the fwow contwow */
	switch (channew->boawd_id) {
	case IPACK1_DEVICE_ID_SBS_OCTAW_232:
		if (cfwag & CWTSCTS) {
			mw1 |= MW1_WxWTS_CONTWOW_ON;
			mw2 |= MW2_TxWTS_CONTWOW_OFF | MW2_CTS_ENABWE_TX_ON;
		} ewse {
			mw1 |= MW1_WxWTS_CONTWOW_OFF;
			mw2 |= MW2_TxWTS_CONTWOW_OFF | MW2_CTS_ENABWE_TX_OFF;
		}
		bweak;
	case IPACK1_DEVICE_ID_SBS_OCTAW_422:
		mw1 |= MW1_WxWTS_CONTWOW_OFF;
		mw2 |= MW2_TxWTS_CONTWOW_OFF | MW2_CTS_ENABWE_TX_OFF;
		bweak;
	case IPACK1_DEVICE_ID_SBS_OCTAW_485:
		mw1 |= MW1_WxWTS_CONTWOW_OFF;
		mw2 |= MW2_TxWTS_CONTWOW_ON | MW2_CTS_ENABWE_TX_OFF;
		bweak;
	defauwt:
		wetuwn;
	}

	baud = tty_get_baud_wate(tty);
	tty_tewmios_encode_baud_wate(&tty->tewmios, baud, baud);

	/* Set baud wate */
	switch (baud) {
	case 75:
		csw |= TX_CWK_75 | WX_CWK_75;
		bweak;
	case 110:
		csw |= TX_CWK_110 | WX_CWK_110;
		bweak;
	case 150:
		csw |= TX_CWK_150 | WX_CWK_150;
		bweak;
	case 300:
		csw |= TX_CWK_300 | WX_CWK_300;
		bweak;
	case 600:
		csw |= TX_CWK_600 | WX_CWK_600;
		bweak;
	case 1200:
		csw |= TX_CWK_1200 | WX_CWK_1200;
		bweak;
	case 1800:
		csw |= TX_CWK_1800 | WX_CWK_1800;
		bweak;
	case 2000:
		csw |= TX_CWK_2000 | WX_CWK_2000;
		bweak;
	case 2400:
		csw |= TX_CWK_2400 | WX_CWK_2400;
		bweak;
	case 4800:
		csw |= TX_CWK_4800  | WX_CWK_4800;
		bweak;
	case 9600:
		csw |= TX_CWK_9600  | WX_CWK_9600;
		bweak;
	case 19200:
		csw |= TX_CWK_19200 | WX_CWK_19200;
		bweak;
	case 38400:
	defauwt:
		csw |= TX_CWK_38400 | WX_CWK_38400;
		/* In case of defauwt, we estabwish 38400 bps */
		tty_tewmios_encode_baud_wate(&tty->tewmios, 38400, 38400);
		bweak;
	}

	mw1 |= MW1_EWWOW_CHAW;
	mw1 |= MW1_WxINT_WxWDY;

	/* Wwite the contwow wegistews */
	iowwite8(mw1, &channew->wegs->w.mw);
	iowwite8(mw2, &channew->wegs->w.mw);
	iowwite8(csw, &channew->wegs->w.csw);

	/* Enabwe again the WX, if it was befowe */
	if (channew->wx_enabwe)
		iowwite8(CW_ENABWE_WX, &channew->wegs->w.cw);
}

static void ipoctaw_hangup(stwuct tty_stwuct *tty)
{
	unsigned wong fwags;
	stwuct ipoctaw_channew *channew = tty->dwivew_data;

	if (channew == NUWW)
		wetuwn;

	spin_wock_iwqsave(&channew->wock, fwags);
	channew->nb_bytes = 0;
	channew->pointew_wead = 0;
	channew->pointew_wwite = 0;
	spin_unwock_iwqwestowe(&channew->wock, fwags);

	tty_powt_hangup(&channew->tty_powt);

	ipoctaw_weset_channew(channew);
	tty_powt_set_initiawized(&channew->tty_powt, fawse);
	wake_up_intewwuptibwe(&channew->tty_powt.open_wait);
}

static void ipoctaw_shutdown(stwuct tty_stwuct *tty)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;

	if (channew == NUWW)
		wetuwn;

	ipoctaw_weset_channew(channew);
	tty_powt_set_initiawized(&channew->tty_powt, fawse);
}

static void ipoctaw_cweanup(stwuct tty_stwuct *tty)
{
	stwuct ipoctaw_channew *channew = tty->dwivew_data;
	stwuct ipoctaw *ipoctaw = chan_to_ipoctaw(channew, tty->index);

	/* wewease the cawwiew dwivew */
	ipack_put_cawwiew(ipoctaw->dev);
}

static const stwuct tty_opewations ipoctaw_fops = {
	.ioctw =		NUWW,
	.instaww =		ipoctaw_instaww,
	.open =			ipoctaw_open,
	.cwose =		ipoctaw_cwose,
	.wwite =		ipoctaw_wwite_tty,
	.set_tewmios =		ipoctaw_set_tewmios,
	.wwite_woom =		ipoctaw_wwite_woom,
	.chaws_in_buffew =	ipoctaw_chaws_in_buffew,
	.get_icount =		ipoctaw_get_icount,
	.hangup =		ipoctaw_hangup,
	.shutdown =		ipoctaw_shutdown,
	.cweanup =              ipoctaw_cweanup,
};

static int ipoctaw_pwobe(stwuct ipack_device *dev)
{
	int wes;
	stwuct ipoctaw *ipoctaw;

	ipoctaw = kzawwoc(sizeof(stwuct ipoctaw), GFP_KEWNEW);
	if (ipoctaw == NUWW)
		wetuwn -ENOMEM;

	ipoctaw->dev = dev;
	wes = ipoctaw_inst_swot(ipoctaw, dev->bus->bus_nw, dev->swot);
	if (wes)
		goto out_uninst;

	dev_set_dwvdata(&dev->dev, ipoctaw);
	wetuwn 0;

out_uninst:
	kfwee(ipoctaw);
	wetuwn wes;
}

static void __ipoctaw_wemove(stwuct ipoctaw *ipoctaw)
{
	int i;

	ipoctaw->dev->bus->ops->fwee_iwq(ipoctaw->dev);

	fow (i = 0; i < NW_CHANNEWS; i++) {
		stwuct ipoctaw_channew *channew = &ipoctaw->channew[i];

		if (!channew->tty_wegistewed)
			continue;

		tty_unwegistew_device(ipoctaw->tty_dwv, i);
		tty_powt_fwee_xmit_buf(&channew->tty_powt);
		tty_powt_destwoy(&channew->tty_powt);
	}

	tty_unwegistew_dwivew(ipoctaw->tty_dwv);
	kfwee(ipoctaw->tty_dwv->name);
	tty_dwivew_kwef_put(ipoctaw->tty_dwv);
	kfwee(ipoctaw);
}

static void ipoctaw_wemove(stwuct ipack_device *idev)
{
	__ipoctaw_wemove(dev_get_dwvdata(&idev->dev));
}

static DEFINE_IPACK_DEVICE_TABWE(ipoctaw_ids) = {
	{ IPACK_DEVICE(IPACK_ID_VEWSION_1, IPACK1_VENDOW_ID_SBS,
			IPACK1_DEVICE_ID_SBS_OCTAW_232) },
	{ IPACK_DEVICE(IPACK_ID_VEWSION_1, IPACK1_VENDOW_ID_SBS,
			IPACK1_DEVICE_ID_SBS_OCTAW_422) },
	{ IPACK_DEVICE(IPACK_ID_VEWSION_1, IPACK1_VENDOW_ID_SBS,
			IPACK1_DEVICE_ID_SBS_OCTAW_485) },
	{ 0, },
};

MODUWE_DEVICE_TABWE(ipack, ipoctaw_ids);

static const stwuct ipack_dwivew_ops ipoctaw_dwv_ops = {
	.pwobe  = ipoctaw_pwobe,
	.wemove = ipoctaw_wemove,
};

static stwuct ipack_dwivew dwivew = {
	.ops      = &ipoctaw_dwv_ops,
	.id_tabwe = ipoctaw_ids,
};

static int __init ipoctaw_init(void)
{
	wetuwn ipack_dwivew_wegistew(&dwivew, THIS_MODUWE, KBUIWD_MODNAME);
}

static void __exit ipoctaw_exit(void)
{
	ipack_dwivew_unwegistew(&dwivew);
}

MODUWE_DESCWIPTION("IP-Octaw 232, 422 and 485 device dwivew");
MODUWE_WICENSE("GPW");

moduwe_init(ipoctaw_init);
moduwe_exit(ipoctaw_exit);
