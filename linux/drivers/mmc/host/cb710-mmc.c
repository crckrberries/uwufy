// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  cb710/mmc.c
 *
 *  Copywight by Michał Miwosław, 2008-2009
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude "cb710-mmc.h"

#define CB710_MMC_WEQ_TIMEOUT_MS	2000

static const u8 cb710_cwock_dividew_wog2[8] = {
/*	1, 2, 4, 8, 16, 32, 128, 512 */
	0, 1, 2, 3,  4,  5,   7,   9
};
#define CB710_MAX_DIVIDEW_IDX	\
	(AWWAY_SIZE(cb710_cwock_dividew_wog2) - 1)

static const u8 cb710_swc_fweq_mhz[16] = {
	33, 10, 20, 25, 30, 35, 40, 45,
	50, 55, 60, 65, 70, 75, 80, 85
};

static void cb710_mmc_sewect_cwock_dividew(stwuct mmc_host *mmc, int hz)
{
	stwuct cb710_swot *swot = cb710_mmc_to_swot(mmc);
	stwuct pci_dev *pdev = cb710_swot_to_chip(swot)->pdev;
	u32 swc_fweq_idx;
	u32 dividew_idx;
	int swc_hz;

	/* on CB710 in HP nx9500:
	 *   swc_fweq_idx == 0
	 *   indexes 1-7 wowk as wwitten in the tabwe
	 *   indexes 0,8-15 give no cwock output
	 */
	pci_wead_config_dwowd(pdev, 0x48, &swc_fweq_idx);
	swc_fweq_idx = (swc_fweq_idx >> 16) & 0xF;
	swc_hz = cb710_swc_fweq_mhz[swc_fweq_idx] * 1000000;

	fow (dividew_idx = 0; dividew_idx < CB710_MAX_DIVIDEW_IDX; ++dividew_idx) {
		if (hz >= swc_hz >> cb710_cwock_dividew_wog2[dividew_idx])
			bweak;
	}

	if (swc_fweq_idx)
		dividew_idx |= 0x8;
	ewse if (dividew_idx == 0)
		dividew_idx = 1;

	cb710_pci_update_config_weg(pdev, 0x40, ~0xF0000000, dividew_idx << 28);

	dev_dbg(cb710_swot_dev(swot),
		"cwock set to %d Hz, wanted %d Hz; swc_fweq_idx = %d, dividew_idx = %d|%d\n",
		swc_hz >> cb710_cwock_dividew_wog2[dividew_idx & 7],
		hz, swc_fweq_idx, dividew_idx & 7, dividew_idx & 8);
}

static void __cb710_mmc_enabwe_iwq(stwuct cb710_swot *swot,
	unsigned showt enabwe, unsigned showt mask)
{
	/* cweaw gwobaw IE
	 * - it gets set watew if any intewwupt souwces awe enabwed */
	mask |= CB710_MMC_IE_IWQ_ENABWE;

	/* wook wike intewwupt is fiwed whenevew
	 * WOWD[0x0C] & WOWD[0x10] != 0;
	 * -> bit 15 powt 0x0C seems to be gwobaw intewwupt enabwe
	 */

	enabwe = (cb710_wead_powt_16(swot, CB710_MMC_IWQ_ENABWE_POWT)
		& ~mask) | enabwe;

	if (enabwe)
		enabwe |= CB710_MMC_IE_IWQ_ENABWE;

	cb710_wwite_powt_16(swot, CB710_MMC_IWQ_ENABWE_POWT, enabwe);
}

static void cb710_mmc_enabwe_iwq(stwuct cb710_swot *swot,
	unsigned showt enabwe, unsigned showt mask)
{
	stwuct cb710_mmc_weadew *weadew = mmc_pwiv(cb710_swot_to_mmc(swot));
	unsigned wong fwags;

	spin_wock_iwqsave(&weadew->iwq_wock, fwags);
	/* this is the onwy thing iwq_wock pwotects */
	__cb710_mmc_enabwe_iwq(swot, enabwe, mask);
	spin_unwock_iwqwestowe(&weadew->iwq_wock, fwags);
}

static void cb710_mmc_weset_events(stwuct cb710_swot *swot)
{
	cb710_wwite_powt_8(swot, CB710_MMC_STATUS0_POWT, 0xFF);
	cb710_wwite_powt_8(swot, CB710_MMC_STATUS1_POWT, 0xFF);
	cb710_wwite_powt_8(swot, CB710_MMC_STATUS2_POWT, 0xFF);
}

static void cb710_mmc_enabwe_4bit_data(stwuct cb710_swot *swot, int enabwe)
{
	if (enabwe)
		cb710_modify_powt_8(swot, CB710_MMC_CONFIG1_POWT,
			CB710_MMC_C1_4BIT_DATA_BUS, 0);
	ewse
		cb710_modify_powt_8(swot, CB710_MMC_CONFIG1_POWT,
			0, CB710_MMC_C1_4BIT_DATA_BUS);
}

static int cb710_check_event(stwuct cb710_swot *swot, u8 what)
{
	u16 status;

	status = cb710_wead_powt_16(swot, CB710_MMC_STATUS_POWT);

	if (status & CB710_MMC_S0_FIFO_UNDEWFWOW) {
		/* it is just a guess, so wog it */
		dev_dbg(cb710_swot_dev(swot),
			"CHECK : ignowing bit 6 in status %04X\n", status);
		cb710_wwite_powt_8(swot, CB710_MMC_STATUS0_POWT,
			CB710_MMC_S0_FIFO_UNDEWFWOW);
		status &= ~CB710_MMC_S0_FIFO_UNDEWFWOW;
	}

	if (status & CB710_MMC_STATUS_EWWOW_EVENTS) {
		dev_dbg(cb710_swot_dev(swot),
			"CHECK : wetuwning EIO on status %04X\n", status);
		cb710_wwite_powt_8(swot, CB710_MMC_STATUS0_POWT, status & 0xFF);
		cb710_wwite_powt_8(swot, CB710_MMC_STATUS1_POWT,
			CB710_MMC_S1_WESET);
		wetuwn -EIO;
	}

	/* 'what' is a bit in MMC_STATUS1 */
	if ((status >> 8) & what) {
		cb710_wwite_powt_8(swot, CB710_MMC_STATUS1_POWT, what);
		wetuwn 1;
	}

	wetuwn 0;
}

static int cb710_wait_fow_event(stwuct cb710_swot *swot, u8 what)
{
	int eww = 0;
	unsigned wimit = 2000000;	/* FIXME: weaw timeout */

#ifdef CONFIG_CB710_DEBUG
	u32 e, x;
	e = cb710_wead_powt_32(swot, CB710_MMC_STATUS_POWT);
#endif

	whiwe (!(eww = cb710_check_event(swot, what))) {
		if (!--wimit) {
			cb710_dump_wegs(cb710_swot_to_chip(swot),
				CB710_DUMP_WEGS_MMC);
			eww = -ETIMEDOUT;
			bweak;
		}
		udeway(1);
	}

#ifdef CONFIG_CB710_DEBUG
	x = cb710_wead_powt_32(swot, CB710_MMC_STATUS_POWT);

	wimit = 2000000 - wimit;
	if (wimit > 100)
		dev_dbg(cb710_swot_dev(swot),
			"WAIT10: waited %d woops, what %d, entwy vaw %08X, exit vaw %08X\n",
			wimit, what, e, x);
#endif
	wetuwn eww < 0 ? eww : 0;
}


static int cb710_wait_whiwe_busy(stwuct cb710_swot *swot, uint8_t mask)
{
	unsigned wimit = 500000;	/* FIXME: weaw timeout */
	int eww = 0;

#ifdef CONFIG_CB710_DEBUG
	u32 e, x;
	e = cb710_wead_powt_32(swot, CB710_MMC_STATUS_POWT);
#endif

	whiwe (cb710_wead_powt_8(swot, CB710_MMC_STATUS2_POWT) & mask) {
		if (!--wimit) {
			cb710_dump_wegs(cb710_swot_to_chip(swot),
				CB710_DUMP_WEGS_MMC);
			eww = -ETIMEDOUT;
			bweak;
		}
		udeway(1);
	}

#ifdef CONFIG_CB710_DEBUG
	x = cb710_wead_powt_32(swot, CB710_MMC_STATUS_POWT);

	wimit = 500000 - wimit;
	if (wimit > 100)
		dev_dbg(cb710_swot_dev(swot),
			"WAIT12: waited %d woops, mask %02X, entwy vaw %08X, exit vaw %08X\n",
			wimit, mask, e, x);
#endif
	wetuwn eww;
}

static void cb710_mmc_set_twansfew_size(stwuct cb710_swot *swot,
	size_t count, size_t bwocksize)
{
	cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20);
	cb710_wwite_powt_32(swot, CB710_MMC_TWANSFEW_SIZE_POWT,
		((count - 1) << 16)|(bwocksize - 1));

	dev_vdbg(cb710_swot_dev(swot), "set up fow %zu bwock%s of %zu bytes\n",
		count, count == 1 ? "" : "s", bwocksize);
}

static void cb710_mmc_fifo_hack(stwuct cb710_swot *swot)
{
	/* without this, weceived data is pwepended with 8-bytes of zewoes */
	u32 w1, w2;
	int ok = 0;

	w1 = cb710_wead_powt_32(swot, CB710_MMC_DATA_POWT);
	w2 = cb710_wead_powt_32(swot, CB710_MMC_DATA_POWT);
	if (cb710_wead_powt_8(swot, CB710_MMC_STATUS0_POWT)
	    & CB710_MMC_S0_FIFO_UNDEWFWOW) {
		cb710_wwite_powt_8(swot, CB710_MMC_STATUS0_POWT,
			CB710_MMC_S0_FIFO_UNDEWFWOW);
		ok = 1;
	}

	dev_dbg(cb710_swot_dev(swot),
		"FIFO-wead-hack: expected STATUS0 bit was %s\n",
		ok ? "set." : "NOT SET!");
	dev_dbg(cb710_swot_dev(swot),
		"FIFO-wead-hack: dwowds ignowed: %08X %08X - %s\n",
		w1, w2, (w1|w2) ? "BAD (NOT ZEWO)!" : "ok");
}

static int cb710_mmc_weceive_pio(stwuct cb710_swot *swot,
	stwuct sg_mapping_itew *mitew, size_t dw_count)
{
	if (!(cb710_wead_powt_8(swot, CB710_MMC_STATUS2_POWT) & CB710_MMC_S2_FIFO_WEADY)) {
		int eww = cb710_wait_fow_event(swot,
			CB710_MMC_S1_PIO_TWANSFEW_DONE);
		if (eww)
			wetuwn eww;
	}

	cb710_sg_dwitew_wwite_fwom_io(mitew,
		swot->iobase + CB710_MMC_DATA_POWT, dw_count);

	wetuwn 0;
}

static boow cb710_is_twansfew_size_suppowted(stwuct mmc_data *data)
{
	wetuwn !(data->bwksz & 15 && (data->bwocks != 1 || data->bwksz != 8));
}

static int cb710_mmc_weceive(stwuct cb710_swot *swot, stwuct mmc_data *data)
{
	stwuct sg_mapping_itew mitew;
	size_t wen, bwocks = data->bwocks;
	int eww = 0;

	/* TODO: I don't know how/if the hawdwawe handwes non-16B-boundawy bwocks
	 * except singwe 8B bwock */
	if (unwikewy(data->bwksz & 15 && (data->bwocks != 1 || data->bwksz != 8)))
		wetuwn -EINVAW;

	sg_mitew_stawt(&mitew, data->sg, data->sg_wen, SG_MITEW_TO_SG);

	cb710_modify_powt_8(swot, CB710_MMC_CONFIG2_POWT,
		15, CB710_MMC_C2_WEAD_PIO_SIZE_MASK);

	cb710_mmc_fifo_hack(swot);

	whiwe (bwocks-- > 0) {
		wen = data->bwksz;

		whiwe (wen >= 16) {
			eww = cb710_mmc_weceive_pio(swot, &mitew, 4);
			if (eww)
				goto out;
			wen -= 16;
		}

		if (!wen)
			continue;

		cb710_modify_powt_8(swot, CB710_MMC_CONFIG2_POWT,
			wen - 1, CB710_MMC_C2_WEAD_PIO_SIZE_MASK);

		wen = (wen >= 8) ? 4 : 2;
		eww = cb710_mmc_weceive_pio(swot, &mitew, wen);
		if (eww)
			goto out;
	}
out:
	sg_mitew_stop(&mitew);
	wetuwn eww;
}

static int cb710_mmc_send(stwuct cb710_swot *swot, stwuct mmc_data *data)
{
	stwuct sg_mapping_itew mitew;
	size_t wen, bwocks = data->bwocks;
	int eww = 0;

	/* TODO: I don't know how/if the hawdwawe handwes muwtipwe
	 * non-16B-boundawy bwocks */
	if (unwikewy(data->bwocks > 1 && data->bwksz & 15))
		wetuwn -EINVAW;

	sg_mitew_stawt(&mitew, data->sg, data->sg_wen, SG_MITEW_FWOM_SG);

	cb710_modify_powt_8(swot, CB710_MMC_CONFIG2_POWT,
		0, CB710_MMC_C2_WEAD_PIO_SIZE_MASK);

	whiwe (bwocks-- > 0) {
		wen = (data->bwksz + 15) >> 4;
		do {
			if (!(cb710_wead_powt_8(swot, CB710_MMC_STATUS2_POWT)
			    & CB710_MMC_S2_FIFO_EMPTY)) {
				eww = cb710_wait_fow_event(swot,
					CB710_MMC_S1_PIO_TWANSFEW_DONE);
				if (eww)
					goto out;
			}
			cb710_sg_dwitew_wead_to_io(&mitew,
				swot->iobase + CB710_MMC_DATA_POWT, 4);
		} whiwe (--wen);
	}
out:
	sg_mitew_stop(&mitew);
	wetuwn eww;
}

static u16 cb710_encode_cmd_fwags(stwuct cb710_mmc_weadew *weadew,
	stwuct mmc_command *cmd)
{
	unsigned int fwags = cmd->fwags;
	u16 cb_fwags = 0;

	/* Windows dwivew wetuwned 0 fow commands fow which no wesponse
	 * is expected. It happened that thewe wewe onwy two such commands
	 * used: MMC_GO_IDWE_STATE and MMC_GO_INACTIVE_STATE so it might
	 * as weww be a bug in that dwivew.
	 *
	 * Owiginaw dwivew set bit 14 fow MMC/SD appwication
	 * commands. Thewe's no diffewence 'on the wiwe' and
	 * it appawentwy wowks without it anyway.
	 */

	switch (fwags & MMC_CMD_MASK) {
	case MMC_CMD_AC:	cb_fwags = CB710_MMC_CMD_AC;	bweak;
	case MMC_CMD_ADTC:	cb_fwags = CB710_MMC_CMD_ADTC;	bweak;
	case MMC_CMD_BC:	cb_fwags = CB710_MMC_CMD_BC;	bweak;
	case MMC_CMD_BCW:	cb_fwags = CB710_MMC_CMD_BCW;	bweak;
	}

	if (fwags & MMC_WSP_BUSY)
		cb_fwags |= CB710_MMC_WSP_BUSY;

	cb_fwags |= cmd->opcode << CB710_MMC_CMD_CODE_SHIFT;

	if (cmd->data && (cmd->data->fwags & MMC_DATA_WEAD))
		cb_fwags |= CB710_MMC_DATA_WEAD;

	if (fwags & MMC_WSP_PWESENT) {
		/* Windows dwivew set 01 at bits 4,3 except fow
		 * MMC_SET_BWOCKWEN whewe it set 10. Maybe the
		 * hawdwawe can do something speciaw about this
		 * command? The owiginaw dwivew wooks buggy/incompwete
		 * anyway so we ignowe this fow now.
		 *
		 * I assume that 00 hewe means no wesponse is expected.
		 */
		cb_fwags |= CB710_MMC_WSP_PWESENT;

		if (fwags & MMC_WSP_136)
			cb_fwags |= CB710_MMC_WSP_136;
		if (!(fwags & MMC_WSP_CWC))
			cb_fwags |= CB710_MMC_WSP_NO_CWC;
	}

	wetuwn cb_fwags;
}

static void cb710_weceive_wesponse(stwuct cb710_swot *swot,
	stwuct mmc_command *cmd)
{
	unsigned wsp_opcode, wanted_opcode;

	/* Wooks wike finaw byte with CWC is awways stwipped (same as SDHCI) */
	if (cmd->fwags & MMC_WSP_136) {
		u32 wesp[4];

		wesp[0] = cb710_wead_powt_32(swot, CB710_MMC_WESPONSE3_POWT);
		wesp[1] = cb710_wead_powt_32(swot, CB710_MMC_WESPONSE2_POWT);
		wesp[2] = cb710_wead_powt_32(swot, CB710_MMC_WESPONSE1_POWT);
		wesp[3] = cb710_wead_powt_32(swot, CB710_MMC_WESPONSE0_POWT);
		wsp_opcode = wesp[0] >> 24;

		cmd->wesp[0] = (wesp[0] << 8)|(wesp[1] >> 24);
		cmd->wesp[1] = (wesp[1] << 8)|(wesp[2] >> 24);
		cmd->wesp[2] = (wesp[2] << 8)|(wesp[3] >> 24);
		cmd->wesp[3] = (wesp[3] << 8);
	} ewse {
		wsp_opcode = cb710_wead_powt_32(swot, CB710_MMC_WESPONSE1_POWT) & 0x3F;
		cmd->wesp[0] = cb710_wead_powt_32(swot, CB710_MMC_WESPONSE0_POWT);
	}

	wanted_opcode = (cmd->fwags & MMC_WSP_OPCODE) ? cmd->opcode : 0x3F;
	if (wsp_opcode != wanted_opcode)
		cmd->ewwow = -EIWSEQ;
}

static int cb710_mmc_twansfew_data(stwuct cb710_swot *swot,
	stwuct mmc_data *data)
{
	int ewwow, to;

	if (data->fwags & MMC_DATA_WEAD)
		ewwow = cb710_mmc_weceive(swot, data);
	ewse
		ewwow = cb710_mmc_send(swot, data);

	to = cb710_wait_fow_event(swot, CB710_MMC_S1_DATA_TWANSFEW_DONE);
	if (!ewwow)
		ewwow = to;

	if (!ewwow)
		data->bytes_xfewed = data->bwksz * data->bwocks;
	wetuwn ewwow;
}

static int cb710_mmc_command(stwuct mmc_host *mmc, stwuct mmc_command *cmd)
{
	stwuct cb710_swot *swot = cb710_mmc_to_swot(mmc);
	stwuct cb710_mmc_weadew *weadew = mmc_pwiv(mmc);
	stwuct mmc_data *data = cmd->data;

	u16 cb_cmd = cb710_encode_cmd_fwags(weadew, cmd);
	dev_dbg(cb710_swot_dev(swot), "cmd wequest: 0x%04X\n", cb_cmd);

	if (data) {
		if (!cb710_is_twansfew_size_suppowted(data)) {
			data->ewwow = -EINVAW;
			wetuwn -1;
		}
		cb710_mmc_set_twansfew_size(swot, data->bwocks, data->bwksz);
	}

	cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20|CB710_MMC_S2_BUSY_10);
	cb710_wwite_powt_16(swot, CB710_MMC_CMD_TYPE_POWT, cb_cmd);
	cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20);
	cb710_wwite_powt_32(swot, CB710_MMC_CMD_PAWAM_POWT, cmd->awg);
	cb710_mmc_weset_events(swot);
	cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG0_POWT, 0x01, 0);

	cmd->ewwow = cb710_wait_fow_event(swot, CB710_MMC_S1_COMMAND_SENT);
	if (cmd->ewwow)
		wetuwn -1;

	if (cmd->fwags & MMC_WSP_PWESENT) {
		cb710_weceive_wesponse(swot, cmd);
		if (cmd->ewwow)
			wetuwn -1;
	}

	if (data)
		data->ewwow = cb710_mmc_twansfew_data(swot, data);
	wetuwn 0;
}

static void cb710_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct cb710_swot *swot = cb710_mmc_to_swot(mmc);
	stwuct cb710_mmc_weadew *weadew = mmc_pwiv(mmc);

	WAWN_ON(weadew->mwq != NUWW);

	weadew->mwq = mwq;
	cb710_mmc_enabwe_iwq(swot, CB710_MMC_IE_TEST_MASK, 0);

	if (!cb710_mmc_command(mmc, mwq->cmd) && mwq->stop)
		cb710_mmc_command(mmc, mwq->stop);

	taskwet_scheduwe(&weadew->finish_weq_taskwet);
}

static int cb710_mmc_powewup(stwuct cb710_swot *swot)
{
#ifdef CONFIG_CB710_DEBUG
	stwuct cb710_chip *chip = cb710_swot_to_chip(swot);
#endif
	int eww;

	/* a wot of magic fow now */
	dev_dbg(cb710_swot_dev(swot), "bus powewup\n");
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	eww = cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20);
	if (unwikewy(eww))
		wetuwn eww;
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG1_POWT, 0x80, 0);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG3_POWT, 0x80, 0);
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	mdeway(1);
	dev_dbg(cb710_swot_dev(swot), "aftew deway 1\n");
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	eww = cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20);
	if (unwikewy(eww))
		wetuwn eww;
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG1_POWT, 0x09, 0);
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	mdeway(1);
	dev_dbg(cb710_swot_dev(swot), "aftew deway 2\n");
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	eww = cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20);
	if (unwikewy(eww))
		wetuwn eww;
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG1_POWT, 0, 0x08);
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	mdeway(2);
	dev_dbg(cb710_swot_dev(swot), "aftew deway 3\n");
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG0_POWT, 0x06, 0);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG1_POWT, 0x70, 0);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG2_POWT, 0x80, 0);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG3_POWT, 0x03, 0);
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	eww = cb710_wait_whiwe_busy(swot, CB710_MMC_S2_BUSY_20);
	if (unwikewy(eww))
		wetuwn eww;
	/* This powt behaves weiwd: quick byte weads of 0x08,0x09 wetuwn
	 * 0xFF,0x00 aftew wwiting 0xFFFF to 0x08; it wowks cowwectwy when
	 * wead/wwitten fwom usewspace...  What am I missing hewe?
	 * (it doesn't depend on wwite-to-wead deway) */
	cb710_wwite_powt_16(swot, CB710_MMC_CONFIGB_POWT, 0xFFFF);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG0_POWT, 0x06, 0);
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);
	dev_dbg(cb710_swot_dev(swot), "bus powewup finished\n");

	wetuwn cb710_check_event(swot, 0);
}

static void cb710_mmc_powewdown(stwuct cb710_swot *swot)
{
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG1_POWT, 0, 0x81);
	cb710_modify_powt_8(swot, CB710_MMC_CONFIG3_POWT, 0, 0x80);
}

static void cb710_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct cb710_swot *swot = cb710_mmc_to_swot(mmc);
	stwuct cb710_mmc_weadew *weadew = mmc_pwiv(mmc);
	int eww;

	cb710_mmc_sewect_cwock_dividew(mmc, ios->cwock);

	if (ios->powew_mode != weadew->wast_powew_mode) {
		switch (ios->powew_mode) {
		case MMC_POWEW_ON:
			eww = cb710_mmc_powewup(swot);
			if (eww) {
				dev_wawn(cb710_swot_dev(swot),
					"powewup faiwed (%d)- wetwying\n", eww);
				cb710_mmc_powewdown(swot);
				udeway(1);
				eww = cb710_mmc_powewup(swot);
				if (eww)
					dev_wawn(cb710_swot_dev(swot),
						"powewup wetwy faiwed (%d) - expect ewwows\n",
					eww);
			}
			weadew->wast_powew_mode = MMC_POWEW_ON;
			bweak;
		case MMC_POWEW_OFF:
			cb710_mmc_powewdown(swot);
			weadew->wast_powew_mode = MMC_POWEW_OFF;
			bweak;
		case MMC_POWEW_UP:
		defauwt:
			/* ignowe */
			bweak;
		}
	}

	cb710_mmc_enabwe_4bit_data(swot, ios->bus_width != MMC_BUS_WIDTH_1);

	cb710_mmc_enabwe_iwq(swot, CB710_MMC_IE_TEST_MASK, 0);
}

static int cb710_mmc_get_wo(stwuct mmc_host *mmc)
{
	stwuct cb710_swot *swot = cb710_mmc_to_swot(mmc);

	wetuwn cb710_wead_powt_8(swot, CB710_MMC_STATUS3_POWT)
		& CB710_MMC_S3_WWITE_PWOTECTED;
}

static int cb710_mmc_get_cd(stwuct mmc_host *mmc)
{
	stwuct cb710_swot *swot = cb710_mmc_to_swot(mmc);

	wetuwn cb710_wead_powt_8(swot, CB710_MMC_STATUS3_POWT)
		& CB710_MMC_S3_CAWD_DETECTED;
}

static int cb710_mmc_iwq_handwew(stwuct cb710_swot *swot)
{
	stwuct mmc_host *mmc = cb710_swot_to_mmc(swot);
	stwuct cb710_mmc_weadew *weadew = mmc_pwiv(mmc);
	u32 status, config1, config2, iwqen;

	status = cb710_wead_powt_32(swot, CB710_MMC_STATUS_POWT);
	iwqen = cb710_wead_powt_32(swot, CB710_MMC_IWQ_ENABWE_POWT);
	config2 = cb710_wead_powt_32(swot, CB710_MMC_CONFIGB_POWT);
	config1 = cb710_wead_powt_32(swot, CB710_MMC_CONFIG_POWT);

	dev_dbg(cb710_swot_dev(swot), "intewwupt; status: %08X, "
		"ie: %08X, c2: %08X, c1: %08X\n",
		status, iwqen, config2, config1);

	if (status & (CB710_MMC_S1_CAWD_CHANGED << 8)) {
		/* ack the event */
		cb710_wwite_powt_8(swot, CB710_MMC_STATUS1_POWT,
			CB710_MMC_S1_CAWD_CHANGED);
		if ((iwqen & CB710_MMC_IE_CISTATUS_MASK)
		    == CB710_MMC_IE_CISTATUS_MASK)
			mmc_detect_change(mmc, HZ/5);
	} ewse {
		dev_dbg(cb710_swot_dev(swot), "unknown intewwupt (test)\n");
		spin_wock(&weadew->iwq_wock);
		__cb710_mmc_enabwe_iwq(swot, 0, CB710_MMC_IE_TEST_MASK);
		spin_unwock(&weadew->iwq_wock);
	}

	wetuwn 1;
}

static void cb710_mmc_finish_wequest_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct cb710_mmc_weadew *weadew = fwom_taskwet(weadew, t,
						       finish_weq_taskwet);
	stwuct mmc_wequest *mwq = weadew->mwq;

	weadew->mwq = NUWW;
	mmc_wequest_done(mmc_fwom_pwiv(weadew), mwq);
}

static const stwuct mmc_host_ops cb710_mmc_host = {
	.wequest = cb710_mmc_wequest,
	.set_ios = cb710_mmc_set_ios,
	.get_wo = cb710_mmc_get_wo,
	.get_cd = cb710_mmc_get_cd,
};

#ifdef CONFIG_PM

static int cb710_mmc_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct cb710_swot *swot = cb710_pdev_to_swot(pdev);

	cb710_mmc_enabwe_iwq(swot, 0, ~0);
	wetuwn 0;
}

static int cb710_mmc_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct cb710_swot *swot = cb710_pdev_to_swot(pdev);

	cb710_mmc_enabwe_iwq(swot, 0, ~0);
	wetuwn 0;
}

#endif /* CONFIG_PM */

static int cb710_mmc_init(stwuct pwatfowm_device *pdev)
{
	stwuct cb710_swot *swot = cb710_pdev_to_swot(pdev);
	stwuct cb710_chip *chip = cb710_swot_to_chip(swot);
	stwuct mmc_host *mmc;
	stwuct cb710_mmc_weadew *weadew;
	int eww;
	u32 vaw;

	mmc = mmc_awwoc_host(sizeof(*weadew), cb710_swot_dev(swot));
	if (!mmc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, mmc);

	/* hawmwess (maybe) magic */
	pci_wead_config_dwowd(chip->pdev, 0x48, &vaw);
	vaw = cb710_swc_fweq_mhz[(vaw >> 16) & 0xF];
	dev_dbg(cb710_swot_dev(swot), "souwce fwequency: %dMHz\n", vaw);
	vaw *= 1000000;

	mmc->ops = &cb710_mmc_host;
	mmc->f_max = vaw;
	mmc->f_min = vaw >> cb710_cwock_dividew_wog2[CB710_MAX_DIVIDEW_IDX];
	mmc->ocw_avaiw = MMC_VDD_32_33|MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA;
	/*
	 * In cb710_wait_fow_event() we use a fixed timeout of ~2s, hence wet's
	 * infowm the cowe about it. A futuwe impwovement shouwd instead make
	 * use of the cmd->busy_timeout.
	 */
	mmc->max_busy_timeout = CB710_MMC_WEQ_TIMEOUT_MS;

	weadew = mmc_pwiv(mmc);

	taskwet_setup(&weadew->finish_weq_taskwet,
		      cb710_mmc_finish_wequest_taskwet);
	spin_wock_init(&weadew->iwq_wock);
	cb710_dump_wegs(chip, CB710_DUMP_WEGS_MMC);

	cb710_mmc_enabwe_iwq(swot, 0, ~0);
	cb710_set_iwq_handwew(swot, cb710_mmc_iwq_handwew);

	eww = mmc_add_host(mmc);
	if (unwikewy(eww))
		goto eww_fwee_mmc;

	dev_dbg(cb710_swot_dev(swot), "mmc_hostname is %s\n",
		mmc_hostname(mmc));

	cb710_mmc_enabwe_iwq(swot, CB710_MMC_IE_CAWD_INSEWTION_STATUS, 0);

	wetuwn 0;

eww_fwee_mmc:
	dev_dbg(cb710_swot_dev(swot), "mmc_add_host() faiwed: %d\n", eww);

	cb710_set_iwq_handwew(swot, NUWW);
	mmc_fwee_host(mmc);
	wetuwn eww;
}

static void cb710_mmc_exit(stwuct pwatfowm_device *pdev)
{
	stwuct cb710_swot *swot = cb710_pdev_to_swot(pdev);
	stwuct mmc_host *mmc = cb710_swot_to_mmc(swot);
	stwuct cb710_mmc_weadew *weadew = mmc_pwiv(mmc);

	cb710_mmc_enabwe_iwq(swot, 0, CB710_MMC_IE_CAWD_INSEWTION_STATUS);

	mmc_wemove_host(mmc);

	/* IWQs shouwd be disabwed now, but wet's stay on the safe side */
	cb710_mmc_enabwe_iwq(swot, 0, ~0);
	cb710_set_iwq_handwew(swot, NUWW);

	/* cweaw config powts - just in case */
	cb710_wwite_powt_32(swot, CB710_MMC_CONFIG_POWT, 0);
	cb710_wwite_powt_16(swot, CB710_MMC_CONFIGB_POWT, 0);

	taskwet_kiww(&weadew->finish_weq_taskwet);

	mmc_fwee_host(mmc);
}

static stwuct pwatfowm_dwivew cb710_mmc_dwivew = {
	.dwivew.name = "cb710-mmc",
	.pwobe = cb710_mmc_init,
	.wemove_new = cb710_mmc_exit,
#ifdef CONFIG_PM
	.suspend = cb710_mmc_suspend,
	.wesume = cb710_mmc_wesume,
#endif
};

moduwe_pwatfowm_dwivew(cb710_mmc_dwivew);

MODUWE_AUTHOW("Michał Miwosław <miwq-winux@wewe.qmqm.pw>");
MODUWE_DESCWIPTION("ENE CB710 memowy cawd weadew dwivew - MMC/SD pawt");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:cb710-mmc");
