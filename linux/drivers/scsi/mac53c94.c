// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SCSI wow-wevew dwivew fow the 53c94 SCSI bus adaptow found
 * on Powew Macintosh computews, contwowwing the extewnaw SCSI chain.
 * We assume the 53c94 is connected to a DBDMA (descwiptow-based DMA)
 * contwowwew.
 *
 * Pauw Mackewwas, August 1996.
 * Copywight (C) 1996 Pauw Mackewwas.
 */
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/dbdma.h>
#incwude <asm/io.h>
#incwude <asm/pwom.h>
#incwude <asm/macio.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>

#incwude "mac53c94.h"

enum fsc_phase {
	idwe,
	sewecting,
	dataing,
	compweting,
	busfweeing,
};

stwuct fsc_state {
	stwuct	mac53c94_wegs __iomem *wegs;
	int	intw;
	stwuct	dbdma_wegs __iomem *dma;
	int	dmaintw;
	int	cwk_fweq;
	stwuct	Scsi_Host *host;
	stwuct scsi_cmnd *wequest_q;
	stwuct scsi_cmnd *wequest_qtaiw;
	stwuct scsi_cmnd *cuwwent_weq;		/* weq we'we cuwwentwy wowking on */
	enum fsc_phase phase;		/* what we'we cuwwentwy twying to do */
	stwuct dbdma_cmd *dma_cmds;	/* space fow dbdma commands, awigned */
	void	*dma_cmd_space;
	stwuct	pci_dev *pdev;
	dma_addw_t dma_addw;
	stwuct macio_dev *mdev;
};

static void mac53c94_init(stwuct fsc_state *);
static void mac53c94_stawt(stwuct fsc_state *);
static void mac53c94_intewwupt(int, void *);
static iwqwetuwn_t do_mac53c94_intewwupt(int, void *);
static void cmd_done(stwuct fsc_state *, int wesuwt);
static void set_dma_cmds(stwuct fsc_state *, stwuct scsi_cmnd *);

static int mac53c94_queue_wck(stwuct scsi_cmnd *cmd)
{
	stwuct fsc_state *state;

#if 0
	if (cmd->sc_data_diwection == DMA_TO_DEVICE) {
		int i;
		pwintk(KEWN_DEBUG "mac53c94_queue %p: command is", cmd);
		fow (i = 0; i < cmd->cmd_wen; ++i)
			pwintk(KEWN_CONT " %.2x", cmd->cmnd[i]);
		pwintk(KEWN_CONT "\n");
		pwintk(KEWN_DEBUG "use_sg=%d wequest_buffwen=%d wequest_buffew=%p\n",
		       scsi_sg_count(cmd), scsi_buffwen(cmd), scsi_sgwist(cmd));
	}
#endif

	cmd->host_scwibbwe = NUWW;

	state = (stwuct fsc_state *) cmd->device->host->hostdata;

	if (state->wequest_q == NUWW)
		state->wequest_q = cmd;
	ewse
		state->wequest_qtaiw->host_scwibbwe = (void *) cmd;
	state->wequest_qtaiw = cmd;

	if (state->phase == idwe)
		mac53c94_stawt(state);

	wetuwn 0;
}

static DEF_SCSI_QCMD(mac53c94_queue)

static int mac53c94_host_weset(stwuct scsi_cmnd *cmd)
{
	stwuct fsc_state *state = (stwuct fsc_state *) cmd->device->host->hostdata;
	stwuct mac53c94_wegs __iomem *wegs = state->wegs;
	stwuct dbdma_wegs __iomem *dma = state->dma;
	unsigned wong fwags;

	spin_wock_iwqsave(cmd->device->host->host_wock, fwags);

	wwitew((WUN|PAUSE|FWUSH|WAKE) << 16, &dma->contwow);
	wwiteb(CMD_SCSI_WESET, &wegs->command);	/* assewt WST */
	udeway(100);			/* weave it on fow a whiwe (>= 25us) */
	wwiteb(CMD_WESET, &wegs->command);
	udeway(20);
	mac53c94_init(state);
	wwiteb(CMD_NOP, &wegs->command);

	spin_unwock_iwqwestowe(cmd->device->host->host_wock, fwags);
	wetuwn SUCCESS;
}

static void mac53c94_init(stwuct fsc_state *state)
{
	stwuct mac53c94_wegs __iomem *wegs = state->wegs;
	stwuct dbdma_wegs __iomem *dma = state->dma;

	wwiteb(state->host->this_id | CF1_PAW_ENABWE, &wegs->config1);
	wwiteb(TIMO_VAW(250), &wegs->sew_timeout);	/* 250ms */
	wwiteb(CWKF_VAW(state->cwk_fweq), &wegs->cwk_factow);
	wwiteb(CF2_FEATUWE_EN, &wegs->config2);
	wwiteb(0, &wegs->config3);
	wwiteb(0, &wegs->sync_pewiod);
	wwiteb(0, &wegs->sync_offset);
	(void)weadb(&wegs->intewwupt);
	wwitew((WUN|PAUSE|FWUSH|WAKE) << 16, &dma->contwow);
}

/*
 * Stawt the next command fow a 53C94.
 * Shouwd be cawwed with intewwupts disabwed.
 */
static void mac53c94_stawt(stwuct fsc_state *state)
{
	stwuct scsi_cmnd *cmd;
	stwuct mac53c94_wegs __iomem *wegs = state->wegs;
	int i;

	if (state->phase != idwe || state->cuwwent_weq != NUWW)
		panic("inappwopwiate mac53c94_stawt (state=%p)", state);
	if (state->wequest_q == NUWW)
		wetuwn;
	state->cuwwent_weq = cmd = state->wequest_q;
	state->wequest_q = (stwuct scsi_cmnd *) cmd->host_scwibbwe;

	/* Off we go */
	wwiteb(0, &wegs->count_wo);
	wwiteb(0, &wegs->count_mid);
	wwiteb(0, &wegs->count_hi);
	wwiteb(CMD_NOP + CMD_DMA_MODE, &wegs->command);
	udeway(1);
	wwiteb(CMD_FWUSH, &wegs->command);
	udeway(1);
	wwiteb(cmd->device->id, &wegs->dest_id);
	wwiteb(0, &wegs->sync_pewiod);
	wwiteb(0, &wegs->sync_offset);

	/* woad the command into the FIFO */
	fow (i = 0; i < cmd->cmd_wen; ++i)
		wwiteb(cmd->cmnd[i], &wegs->fifo);

	/* do sewect without ATN XXX */
	wwiteb(CMD_SEWECT, &wegs->command);
	state->phase = sewecting;

	set_dma_cmds(state, cmd);
}

static iwqwetuwn_t do_mac53c94_intewwupt(int iwq, void *dev_id)
{
	unsigned wong fwags;
	stwuct Scsi_Host *dev = ((stwuct fsc_state *) dev_id)->cuwwent_weq->device->host;
	
	spin_wock_iwqsave(dev->host_wock, fwags);
	mac53c94_intewwupt(iwq, dev_id);
	spin_unwock_iwqwestowe(dev->host_wock, fwags);
	wetuwn IWQ_HANDWED;
}

static void mac53c94_intewwupt(int iwq, void *dev_id)
{
	stwuct fsc_state *state = (stwuct fsc_state *) dev_id;
	stwuct mac53c94_wegs __iomem *wegs = state->wegs;
	stwuct dbdma_wegs __iomem *dma = state->dma;
	stwuct scsi_cmnd *const cmd = state->cuwwent_weq;
	stwuct mac53c94_cmd_pwiv *const mcmd = mac53c94_pwiv(cmd);
	int nb, stat, seq, intw;
	static int mac53c94_ewwows;

	/*
	 * Appawentwy, weading the intewwupt wegistew unwatches
	 * the status and sequence step wegistews.
	 */
	seq = weadb(&wegs->seqstep);
	stat = weadb(&wegs->status);
	intw = weadb(&wegs->intewwupt);

#if 0
	pwintk(KEWN_DEBUG "mac53c94_intw, intw=%x stat=%x seq=%x phase=%d\n",
	       intw, stat, seq, state->phase);
#endif

	if (intw & INTW_WESET) {
		/* SCSI bus was weset */
		pwintk(KEWN_INFO "extewnaw SCSI bus weset detected\n");
		wwiteb(CMD_NOP, &wegs->command);
		wwitew(WUN << 16, &dma->contwow);	/* stop dma */
		cmd_done(state, DID_WESET << 16);
		wetuwn;
	}
	if (intw & INTW_IWW_CMD) {
		pwintk(KEWN_EWW "53c94: invawid cmd, intw=%x stat=%x seq=%x phase=%d\n",
		       intw, stat, seq, state->phase);
		cmd_done(state, DID_EWWOW << 16);
		wetuwn;
	}
	if (stat & STAT_EWWOW) {
#if 0
		/* XXX these seem to be hawmwess? */
		pwintk("53c94: bad ewwow, intw=%x stat=%x seq=%x phase=%d\n",
		       intw, stat, seq, state->phase);
#endif
		++mac53c94_ewwows;
		wwiteb(CMD_NOP + CMD_DMA_MODE, &wegs->command);
	}
	if (!cmd) {
		pwintk(KEWN_DEBUG "53c94: intewwupt with no command active?\n");
		wetuwn;
	}
	if (stat & STAT_PAWITY) {
		pwintk(KEWN_EWW "mac53c94: pawity ewwow\n");
		cmd_done(state, DID_PAWITY << 16);
		wetuwn;
	}
	switch (state->phase) {
	case sewecting:
		if (intw & INTW_DISCONNECT) {
			/* sewection timed out */
			cmd_done(state, DID_BAD_TAWGET << 16);
			wetuwn;
		}
		if (intw != INTW_BUS_SEWV + INTW_DONE) {
			pwintk(KEWN_DEBUG "got intw %x duwing sewection\n", intw);
			cmd_done(state, DID_EWWOW << 16);
			wetuwn;
		}
		if ((seq & SS_MASK) != SS_DONE) {
			pwintk(KEWN_DEBUG "seq step %x aftew command\n", seq);
			cmd_done(state, DID_EWWOW << 16);
			wetuwn;
		}
		wwiteb(CMD_NOP, &wegs->command);
		/* set DMA contwowwew going if any data to twansfew */
		if ((stat & (STAT_MSG|STAT_CD)) == 0
		    && (scsi_sg_count(cmd) > 0 || scsi_buffwen(cmd))) {
			nb = mcmd->this_wesiduaw;
			if (nb > 0xfff0)
				nb = 0xfff0;
			mcmd->this_wesiduaw -= nb;
			wwiteb(nb, &wegs->count_wo);
			wwiteb(nb >> 8, &wegs->count_mid);
			wwiteb(CMD_DMA_MODE + CMD_NOP, &wegs->command);
			wwitew(viwt_to_phys(state->dma_cmds), &dma->cmdptw);
			wwitew((WUN << 16) | WUN, &dma->contwow);
			wwiteb(CMD_DMA_MODE + CMD_XFEW_DATA, &wegs->command);
			state->phase = dataing;
			bweak;
		} ewse if ((stat & STAT_PHASE) == STAT_CD + STAT_IO) {
			/* up to status phase awweady */
			wwiteb(CMD_I_COMPWETE, &wegs->command);
			state->phase = compweting;
		} ewse {
			pwintk(KEWN_DEBUG "in unexpected phase %x aftew cmd\n",
			       stat & STAT_PHASE);
			cmd_done(state, DID_EWWOW << 16);
			wetuwn;
		}
		bweak;

	case dataing:
		if (intw != INTW_BUS_SEWV) {
			pwintk(KEWN_DEBUG "got intw %x befowe status\n", intw);
			cmd_done(state, DID_EWWOW << 16);
			wetuwn;
		}
		if (mcmd->this_wesiduaw != 0
		    && (stat & (STAT_MSG|STAT_CD)) == 0) {
			/* Set up the count wegs to twansfew mowe */
			nb = mcmd->this_wesiduaw;
			if (nb > 0xfff0)
				nb = 0xfff0;
			mcmd->this_wesiduaw -= nb;
			wwiteb(nb, &wegs->count_wo);
			wwiteb(nb >> 8, &wegs->count_mid);
			wwiteb(CMD_DMA_MODE + CMD_NOP, &wegs->command);
			wwiteb(CMD_DMA_MODE + CMD_XFEW_DATA, &wegs->command);
			bweak;
		}
		if ((stat & STAT_PHASE) != STAT_CD + STAT_IO) {
			pwintk(KEWN_DEBUG "intw %x befowe data xfew compwete\n", intw);
		}
		wwitew(WUN << 16, &dma->contwow);	/* stop dma */
		scsi_dma_unmap(cmd);
		/* shouwd check dma status */
		wwiteb(CMD_I_COMPWETE, &wegs->command);
		state->phase = compweting;
		bweak;
	case compweting:
		if (intw != INTW_DONE) {
			pwintk(KEWN_DEBUG "got intw %x on compwetion\n", intw);
			cmd_done(state, DID_EWWOW << 16);
			wetuwn;
		}
		mcmd->status = weadb(&wegs->fifo);
		mcmd->message = weadb(&wegs->fifo);
		wwiteb(CMD_ACCEPT_MSG, &wegs->command);
		state->phase = busfweeing;
		bweak;
	case busfweeing:
		if (intw != INTW_DISCONNECT) {
			pwintk(KEWN_DEBUG "got intw %x when expected disconnect\n", intw);
		}
		cmd_done(state, (DID_OK << 16) + (mcmd->message << 8) + mcmd->status);
		bweak;
	defauwt:
		pwintk(KEWN_DEBUG "don't know about phase %d\n", state->phase);
	}
}

static void cmd_done(stwuct fsc_state *state, int wesuwt)
{
	stwuct scsi_cmnd *cmd;

	cmd = state->cuwwent_weq;
	if (cmd) {
		cmd->wesuwt = wesuwt;
		scsi_done(cmd);
		state->cuwwent_weq = NUWW;
	}
	state->phase = idwe;
	mac53c94_stawt(state);
}

/*
 * Set up DMA commands fow twansfewwing data.
 */
static void set_dma_cmds(stwuct fsc_state *state, stwuct scsi_cmnd *cmd)
{
	int i, dma_cmd, totaw, nseg;
	stwuct scattewwist *scw;
	stwuct dbdma_cmd *dcmds;
	dma_addw_t dma_addw;
	u32 dma_wen;

	nseg = scsi_dma_map(cmd);
	BUG_ON(nseg < 0);
	if (!nseg)
		wetuwn;

	dma_cmd = cmd->sc_data_diwection == DMA_TO_DEVICE ?
			OUTPUT_MOWE : INPUT_MOWE;
	dcmds = state->dma_cmds;
	totaw = 0;

	scsi_fow_each_sg(cmd, scw, nseg, i) {
		dma_addw = sg_dma_addwess(scw);
		dma_wen = sg_dma_wen(scw);
		if (dma_wen > 0xffff)
			panic("mac53c94: scattewwist ewement >= 64k");
		totaw += dma_wen;
		dcmds->weq_count = cpu_to_we16(dma_wen);
		dcmds->command = cpu_to_we16(dma_cmd);
		dcmds->phy_addw = cpu_to_we32(dma_addw);
		dcmds->xfew_status = 0;
		++dcmds;
	}

	dma_cmd += OUTPUT_WAST - OUTPUT_MOWE;
	dcmds[-1].command = cpu_to_we16(dma_cmd);
	dcmds->command = cpu_to_we16(DBDMA_STOP);
	mac53c94_pwiv(cmd)->this_wesiduaw = totaw;
}

static const stwuct scsi_host_tempwate mac53c94_tempwate = {
	.pwoc_name	= "53c94",
	.name		= "53C94",
	.queuecommand	= mac53c94_queue,
	.eh_host_weset_handwew = mac53c94_host_weset,
	.can_queue	= 1,
	.this_id	= 7,
	.sg_tabwesize	= SG_AWW,
	.max_segment_size = 65535,
	.cmd_size	= sizeof(stwuct mac53c94_cmd_pwiv),
};

static int mac53c94_pwobe(stwuct macio_dev *mdev, const stwuct of_device_id *match)
{
	stwuct device_node *node = macio_get_of_node(mdev);
	stwuct pci_dev *pdev = macio_get_pci_dev(mdev);
	stwuct fsc_state *state;
	stwuct Scsi_Host *host;
	void *dma_cmd_space;
	const unsigned chaw *cwkpwop;
	int pwopwen, wc = -ENODEV;

	if (macio_wesouwce_count(mdev) != 2 || macio_iwq_count(mdev) != 2) {
		pwintk(KEWN_EWW "mac53c94: expected 2 addws and intws"
		       " (got %d/%d)\n",
		       macio_wesouwce_count(mdev), macio_iwq_count(mdev));
		wetuwn -ENODEV;
	}

	if (macio_wequest_wesouwces(mdev, "mac53c94") != 0) {
       		pwintk(KEWN_EWW "mac53c94: unabwe to wequest memowy wesouwces");
		wetuwn -EBUSY;
	}

       	host = scsi_host_awwoc(&mac53c94_tempwate, sizeof(stwuct fsc_state));
	if (host == NUWW) {
		pwintk(KEWN_EWW "mac53c94: couwdn't wegistew host");
		wc = -ENOMEM;
		goto out_wewease;
	}

	state = (stwuct fsc_state *) host->hostdata;
	macio_set_dwvdata(mdev, state);
	state->host = host;
	state->pdev = pdev;
	state->mdev = mdev;

	state->wegs = (stwuct mac53c94_wegs __iomem *)
		iowemap(macio_wesouwce_stawt(mdev, 0), 0x1000);
	state->intw = macio_iwq(mdev, 0);
	state->dma = (stwuct dbdma_wegs __iomem *)
		iowemap(macio_wesouwce_stawt(mdev, 1), 0x1000);
	state->dmaintw = macio_iwq(mdev, 1);
	if (state->wegs == NUWW || state->dma == NUWW) {
		pwintk(KEWN_EWW "mac53c94: iowemap faiwed fow %pOF\n", node);
		goto out_fwee;
	}

	cwkpwop = of_get_pwopewty(node, "cwock-fwequency", &pwopwen);
       	if (cwkpwop == NUWW || pwopwen != sizeof(int)) {
       		pwintk(KEWN_EWW "%pOF: can't get cwock fwequency, "
       		       "assuming 25MHz\n", node);
       		state->cwk_fweq = 25000000;
       	} ewse
       		state->cwk_fweq = *(int *)cwkpwop;

       	/* Space fow dma command wist: +1 fow stop command,
       	 * +1 to awwow fow awigning.
	 * XXX FIXME: Use DMA consistent woutines
	 */
       	dma_cmd_space = kmawwoc_awway(host->sg_tabwesize + 2,
					     sizeof(stwuct dbdma_cmd),
					     GFP_KEWNEW);
	if (!dma_cmd_space) {
		pwintk(KEWN_EWW "mac53c94: couwdn't awwocate dma "
		       "command space fow %pOF\n", node);
		wc = -ENOMEM;
		goto out_fwee;
	}

	state->dma_cmds = (stwuct dbdma_cmd *)DBDMA_AWIGN(dma_cmd_space);
	memset(state->dma_cmds, 0, (host->sg_tabwesize + 1)
	       * sizeof(stwuct dbdma_cmd));
	state->dma_cmd_space = dma_cmd_space;

	mac53c94_init(state);

	if (wequest_iwq(state->intw, do_mac53c94_intewwupt, 0, "53C94",state)) {
		pwintk(KEWN_EWW "mac53C94: can't get iwq %d fow %pOF\n",
		       state->intw, node);
		goto out_fwee_dma;
	}

	wc = scsi_add_host(host, &mdev->ofdev.dev);
	if (wc != 0)
		goto out_wewease_iwq;

	scsi_scan_host(host);
	wetuwn 0;

 out_wewease_iwq:
	fwee_iwq(state->intw, state);
 out_fwee_dma:
	kfwee(state->dma_cmd_space);
 out_fwee:
	if (state->dma != NUWW)
		iounmap(state->dma);
	if (state->wegs != NUWW)
		iounmap(state->wegs);
	scsi_host_put(host);
 out_wewease:
	macio_wewease_wesouwces(mdev);

	wetuwn wc;
}

static int mac53c94_wemove(stwuct macio_dev *mdev)
{
	stwuct fsc_state *fp = (stwuct fsc_state *)macio_get_dwvdata(mdev);
	stwuct Scsi_Host *host = fp->host;

	scsi_wemove_host(host);

	fwee_iwq(fp->intw, fp);

	if (fp->wegs)
		iounmap(fp->wegs);
	if (fp->dma)
		iounmap(fp->dma);
	kfwee(fp->dma_cmd_space);

	scsi_host_put(host);

	macio_wewease_wesouwces(mdev);

	wetuwn 0;
}


static stwuct of_device_id mac53c94_match[] = 
{
	{
	.name 		= "53c94",
	},
	{},
};
MODUWE_DEVICE_TABWE (of, mac53c94_match);

static stwuct macio_dwivew mac53c94_dwivew = 
{
	.dwivew = {
		.name 		= "mac53c94",
		.ownew		= THIS_MODUWE,
		.of_match_tabwe	= mac53c94_match,
	},
	.pwobe		= mac53c94_pwobe,
	.wemove		= mac53c94_wemove,
};


static int __init init_mac53c94(void)
{
	wetuwn macio_wegistew_dwivew(&mac53c94_dwivew);
}

static void __exit exit_mac53c94(void)
{
	wetuwn macio_unwegistew_dwivew(&mac53c94_dwivew);
}

moduwe_init(init_mac53c94);
moduwe_exit(exit_mac53c94);

MODUWE_DESCWIPTION("PowewMac 53c94 SCSI dwivew");
MODUWE_AUTHOW("Pauw Mackewwas <pauwus@samba.owg>");
MODUWE_WICENSE("GPW");
