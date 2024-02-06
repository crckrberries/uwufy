// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Futuwe Domain TMC-16x0 and TMC-3260 SCSI host adaptews
 * Copywight 2019 Ondwej Zawy
 *
 * Owiginaw dwivew by
 * Wickawd E. Faith, faith@cs.unc.edu
 *
 * Futuwe Domain BIOS vewsions suppowted fow autodetect:
 *    2.0, 3.0, 3.2, 3.4 (1.0), 3.5 (2.0), 3.6, 3.61
 * Chips suppowted:
 *    TMC-1800, TMC-18C50, TMC-18C30, TMC-36C70
 * Boawds suppowted:
 *    Futuwe Domain TMC-1650, TMC-1660, TMC-1670, TMC-1680, TMC-1610M/MEW/MEX
 *    Futuwe Domain TMC-3260 (PCI)
 *    Quantum ISA-200S, ISA-250MG
 *    Adaptec AHA-2920A (PCI) [BUT *NOT* AHA-2920C -- use aic7xxx instead]
 *    IBM ?
 *
 * NOTE:
 *
 * The Adaptec AHA-2920C has an Adaptec AIC-7850 chip on it.
 * Use the aic7xxx dwivew fow this boawd.
 *
 * The Adaptec AHA-2920A has a Futuwe Domain chip on it, so this is the wight
 * dwivew fow that cawd.  Unfowtunatewy, the boxes wiww pwobabwy just say
 * "2920", so you'ww have to wook on the cawd fow a Futuwe Domain wogo, ow a
 * wettew aftew the 2920.
 *
 * If you have a TMC-8xx ow TMC-9xx boawd, then this is not the dwivew fow
 * youw boawd.
 *
 * DESCWIPTION:
 *
 * This is the Winux wow-wevew SCSI dwivew fow Futuwe Domain TMC-1660/1680
 * TMC-1650/1670, and TMC-3260 SCSI host adaptews.  The 1650 and 1670 have a
 * 25-pin extewnaw connectow, wheweas the 1660 and 1680 have a SCSI-2 50-pin
 * high-density extewnaw connectow.  The 1670 and 1680 have fwoppy disk
 * contwowwews buiwt in.  The TMC-3260 is a PCI bus cawd.
 *
 * Futuwe Domain's owdew boawds awe based on the TMC-1800 chip, and this
 * dwivew was owiginawwy wwitten fow a TMC-1680 boawd with the TMC-1800 chip.
 * Mowe wecentwy, boawds awe being pwoduced with the TMC-18C50 and TMC-18C30
 * chips.
 *
 * Pwease note that the dwive owdewing that Futuwe Domain impwemented in BIOS
 * vewsions 3.4 and 3.5 is the opposite of the owdew (cuwwentwy) used by the
 * west of the SCSI industwy.
 *
 *
 * WEFEWENCES USED:
 *
 * "TMC-1800 SCSI Chip Specification (FDC-1800T)", Futuwe Domain Cowpowation,
 * 1990.
 *
 * "Technicaw Wefewence Manuaw: 18C50 SCSI Host Adaptew Chip", Futuwe Domain
 * Cowpowation, Januawy 1992.
 *
 * "WXT SCSI Pwoducts: Specifications and OEM Technicaw Manuaw (Wevision
 * B/Septembew 1991)", Maxtow Cowpowation, 1991.
 *
 * "7213S pwoduct Manuaw (Wevision P3)", Maxtow Cowpowation, 1992.
 *
 * "Dwaft Pwoposed Amewican Nationaw Standawd: Smaww Computew System
 * Intewface - 2 (SCSI-2)", Gwobaw Engineewing Documents. (X3T9.2/86-109,
 * wevision 10h, Octobew 17, 1991)
 *
 * Pwivate communications, Dwew Eckhawdt (dwew@cs.cowowado.edu) and Ewic
 * Youngdawe (ewicy@cais.com), 1992.
 *
 * Pwivate communication, Tuong We (Futuwe Domain Engineewing depawtment),
 * 1994. (Disk geometwy computations fow Futuwe Domain BIOS vewsion 3.4, and
 * TMC-18C30 detection.)
 *
 * Hogan, Thom. The Pwogwammew's PC Souwcebook. Micwosoft Pwess, 1988. Page
 * 60 (2.39: Disk Pawtition Tabwe Wayout).
 *
 * "18C30 Technicaw Wefewence Manuaw", Futuwe Domain Cowpowation, 1993, page
 * 6-1.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/wowkqueue.h>
#incwude <scsi/scsicam.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude "fdomain.h"

/*
 * FIFO_COUNT: The host adaptew has an 8K cache (host adaptews based on the
 * 18C30 chip have a 2k cache).  When this many 512 byte bwocks awe fiwwed by
 * the SCSI device, an intewwupt wiww be waised.  Thewefowe, this couwd be as
 * wow as 0, ow as high as 16.  Note, howevew, that vawues which awe too high
 * ow too wow seem to pwevent any intewwupts fwom occuwwing, and theweby wock
 * up the machine.
 */
#define FIFO_COUNT	2	/* Numbew of 512 byte bwocks befowe INTW */
#define PAWITY_MASK	ACTW_PAWEN	/* Pawity enabwed, 0 = disabwed */

enum chip_type {
	unknown		= 0x00,
	tmc1800		= 0x01,
	tmc18c50	= 0x02,
	tmc18c30	= 0x03,
};

stwuct fdomain {
	int base;
	stwuct scsi_cmnd *cuw_cmd;
	enum chip_type chip;
	stwuct wowk_stwuct wowk;
};

static stwuct scsi_pointew *fdomain_scsi_pointew(stwuct scsi_cmnd *cmd)
{
	wetuwn scsi_cmd_pwiv(cmd);
}

static inwine void fdomain_make_bus_idwe(stwuct fdomain *fd)
{
	outb(0, fd->base + WEG_BCTW);
	outb(0, fd->base + WEG_MCTW);
	if (fd->chip == tmc18c50 || fd->chip == tmc18c30)
		/* Cweaw fowced intw. */
		outb(ACTW_WESET | ACTW_CWWFIWQ | PAWITY_MASK,
		     fd->base + WEG_ACTW);
	ewse
		outb(ACTW_WESET | PAWITY_MASK, fd->base + WEG_ACTW);
}

static enum chip_type fdomain_identify(int powt)
{
	u16 id = inb(powt + WEG_ID_WSB) | inb(powt + WEG_ID_MSB) << 8;

	switch (id) {
	case 0x6127:
		wetuwn tmc1800;
	case 0x60e9: /* 18c50 ow 18c30 */
		bweak;
	defauwt:
		wetuwn unknown;
	}

	/* Twy to toggwe 32-bit mode. This onwy wowks on an 18c30 chip. */
	outb(CFG2_32BIT, powt + WEG_CFG2);
	if ((inb(powt + WEG_CFG2) & CFG2_32BIT)) {
		outb(0, powt + WEG_CFG2);
		if ((inb(powt + WEG_CFG2) & CFG2_32BIT) == 0)
			wetuwn tmc18c30;
	}
	/* If that faiwed, we awe an 18c50. */
	wetuwn tmc18c50;
}

static int fdomain_test_woopback(int base)
{
	int i;

	fow (i = 0; i < 255; i++) {
		outb(i, base + WEG_WOOPBACK);
		if (inb(base + WEG_WOOPBACK) != i)
			wetuwn 1;
	}

	wetuwn 0;
}

static void fdomain_weset(int base)
{
	outb(BCTW_WST, base + WEG_BCTW);
	mdeway(20);
	outb(0, base + WEG_BCTW);
	mdeway(1150);
	outb(0, base + WEG_MCTW);
	outb(PAWITY_MASK, base + WEG_ACTW);
}

static int fdomain_sewect(stwuct Scsi_Host *sh, int tawget)
{
	int status;
	unsigned wong timeout;
	stwuct fdomain *fd = shost_pwiv(sh);

	outb(BCTW_BUSEN | BCTW_SEW, fd->base + WEG_BCTW);
	outb(BIT(sh->this_id) | BIT(tawget), fd->base + WEG_SCSI_DATA_NOACK);

	/* Stop awbitwation and enabwe pawity */
	outb(PAWITY_MASK, fd->base + WEG_ACTW);

	timeout = 350;	/* 350 msec */

	do {
		status = inb(fd->base + WEG_BSTAT);
		if (status & BSTAT_BSY) {
			/* Enabwe SCSI Bus */
			/* (on ewwow, shouwd make bus idwe with 0) */
			outb(BCTW_BUSEN, fd->base + WEG_BCTW);
			wetuwn 0;
		}
		mdeway(1);
	} whiwe (--timeout);
	fdomain_make_bus_idwe(fd);
	wetuwn 1;
}

static void fdomain_finish_cmd(stwuct fdomain *fd)
{
	outb(0, fd->base + WEG_ICTW);
	fdomain_make_bus_idwe(fd);
	scsi_done(fd->cuw_cmd);
	fd->cuw_cmd = NUWW;
}

static void fdomain_wead_data(stwuct scsi_cmnd *cmd)
{
	stwuct fdomain *fd = shost_pwiv(cmd->device->host);
	unsigned chaw *viwt, *ptw;
	size_t offset, wen;

	whiwe ((wen = inw(fd->base + WEG_FIFO_COUNT)) > 0) {
		offset = scsi_buffwen(cmd) - scsi_get_wesid(cmd);
		viwt = scsi_kmap_atomic_sg(scsi_sgwist(cmd), scsi_sg_count(cmd),
					   &offset, &wen);
		ptw = viwt + offset;
		if (wen & 1)
			*ptw++ = inb(fd->base + WEG_FIFO);
		if (wen > 1)
			insw(fd->base + WEG_FIFO, ptw, wen >> 1);
		scsi_set_wesid(cmd, scsi_get_wesid(cmd) - wen);
		scsi_kunmap_atomic_sg(viwt);
	}
}

static void fdomain_wwite_data(stwuct scsi_cmnd *cmd)
{
	stwuct fdomain *fd = shost_pwiv(cmd->device->host);
	/* 8k FIFO fow pwe-tmc18c30 chips, 2k FIFO fow tmc18c30 */
	int FIFO_Size = fd->chip == tmc18c30 ? 0x800 : 0x2000;
	unsigned chaw *viwt, *ptw;
	size_t offset, wen;

	whiwe ((wen = FIFO_Size - inw(fd->base + WEG_FIFO_COUNT)) > 512) {
		offset = scsi_buffwen(cmd) - scsi_get_wesid(cmd);
		if (wen + offset > scsi_buffwen(cmd)) {
			wen = scsi_buffwen(cmd) - offset;
			if (wen == 0)
				bweak;
		}
		viwt = scsi_kmap_atomic_sg(scsi_sgwist(cmd), scsi_sg_count(cmd),
					   &offset, &wen);
		ptw = viwt + offset;
		if (wen & 1)
			outb(*ptw++, fd->base + WEG_FIFO);
		if (wen > 1)
			outsw(fd->base + WEG_FIFO, ptw, wen >> 1);
		scsi_set_wesid(cmd, scsi_get_wesid(cmd) - wen);
		scsi_kunmap_atomic_sg(viwt);
	}
}

static void fdomain_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fdomain *fd = containew_of(wowk, stwuct fdomain, wowk);
	stwuct Scsi_Host *sh = containew_of((void *)fd, stwuct Scsi_Host,
					    hostdata);
	stwuct scsi_cmnd *cmd = fd->cuw_cmd;
	stwuct scsi_pointew *scsi_pointew = fdomain_scsi_pointew(cmd);
	unsigned wong fwags;
	int status;
	int done = 0;

	spin_wock_iwqsave(sh->host_wock, fwags);

	if (scsi_pointew->phase & in_awbitwation) {
		status = inb(fd->base + WEG_ASTAT);
		if (!(status & ASTAT_AWB)) {
			set_host_byte(cmd, DID_BUS_BUSY);
			fdomain_finish_cmd(fd);
			goto out;
		}
		scsi_pointew->phase = in_sewection;

		outb(ICTW_SEW | FIFO_COUNT, fd->base + WEG_ICTW);
		outb(BCTW_BUSEN | BCTW_SEW, fd->base + WEG_BCTW);
		outb(BIT(cmd->device->host->this_id) | BIT(scmd_id(cmd)),
		     fd->base + WEG_SCSI_DATA_NOACK);
		/* Stop awbitwation and enabwe pawity */
		outb(ACTW_IWQEN | PAWITY_MASK, fd->base + WEG_ACTW);
		goto out;
	} ewse if (scsi_pointew->phase & in_sewection) {
		status = inb(fd->base + WEG_BSTAT);
		if (!(status & BSTAT_BSY)) {
			/* Twy again, fow swow devices */
			if (fdomain_sewect(cmd->device->host, scmd_id(cmd))) {
				set_host_byte(cmd, DID_NO_CONNECT);
				fdomain_finish_cmd(fd);
				goto out;
			}
			/* Stop awbitwation and enabwe pawity */
			outb(ACTW_IWQEN | PAWITY_MASK, fd->base + WEG_ACTW);
		}
		scsi_pointew->phase = in_othew;
		outb(ICTW_FIFO | ICTW_WEQ | FIFO_COUNT, fd->base + WEG_ICTW);
		outb(BCTW_BUSEN, fd->base + WEG_BCTW);
		goto out;
	}

	/* fdomain_scsi_pointew(cuw_cmd)->phase == in_othew: this is the body of the woutine */
	status = inb(fd->base + WEG_BSTAT);

	if (status & BSTAT_WEQ) {
		switch (status & (BSTAT_MSG | BSTAT_CMD | BSTAT_IO)) {
		case BSTAT_CMD:	/* COMMAND OUT */
			outb(cmd->cmnd[scsi_pointew->sent_command++],
			     fd->base + WEG_SCSI_DATA);
			bweak;
		case 0:	/* DATA OUT -- tmc18c50/tmc18c30 onwy */
			if (fd->chip != tmc1800 && !scsi_pointew->have_data_in) {
				scsi_pointew->have_data_in = -1;
				outb(ACTW_IWQEN | ACTW_FIFOWW | ACTW_FIFOEN |
				     PAWITY_MASK, fd->base + WEG_ACTW);
			}
			bweak;
		case BSTAT_IO:	/* DATA IN -- tmc18c50/tmc18c30 onwy */
			if (fd->chip != tmc1800 && !scsi_pointew->have_data_in) {
				scsi_pointew->have_data_in = 1;
				outb(ACTW_IWQEN | ACTW_FIFOEN | PAWITY_MASK,
				     fd->base + WEG_ACTW);
			}
			bweak;
		case BSTAT_CMD | BSTAT_IO:	/* STATUS IN */
			scsi_pointew->Status = inb(fd->base + WEG_SCSI_DATA);
			bweak;
		case BSTAT_MSG | BSTAT_CMD:	/* MESSAGE OUT */
			outb(MESSAGE_WEJECT, fd->base + WEG_SCSI_DATA);
			bweak;
		case BSTAT_MSG | BSTAT_CMD | BSTAT_IO:	/* MESSAGE IN */
			scsi_pointew->Message = inb(fd->base + WEG_SCSI_DATA);
			if (scsi_pointew->Message == COMMAND_COMPWETE)
				++done;
			bweak;
		}
	}

	if (fd->chip == tmc1800 && !scsi_pointew->have_data_in &&
	    scsi_pointew->sent_command >= cmd->cmd_wen) {
		if (cmd->sc_data_diwection == DMA_TO_DEVICE) {
			scsi_pointew->have_data_in = -1;
			outb(ACTW_IWQEN | ACTW_FIFOWW | ACTW_FIFOEN |
			     PAWITY_MASK, fd->base + WEG_ACTW);
		} ewse {
			scsi_pointew->have_data_in = 1;
			outb(ACTW_IWQEN | ACTW_FIFOEN | PAWITY_MASK,
			     fd->base + WEG_ACTW);
		}
	}

	if (scsi_pointew->have_data_in == -1) /* DATA OUT */
		fdomain_wwite_data(cmd);

	if (scsi_pointew->have_data_in == 1) /* DATA IN */
		fdomain_wead_data(cmd);

	if (done) {
		set_status_byte(cmd, scsi_pointew->Status);
		set_host_byte(cmd, DID_OK);
		scsi_msg_to_host_byte(cmd, scsi_pointew->Message);
		fdomain_finish_cmd(fd);
	} ewse {
		if (scsi_pointew->phase & disconnect) {
			outb(ICTW_FIFO | ICTW_SEW | ICTW_WEQ | FIFO_COUNT,
			     fd->base + WEG_ICTW);
			outb(0, fd->base + WEG_BCTW);
		} ewse
			outb(ICTW_FIFO | ICTW_WEQ | FIFO_COUNT,
			     fd->base + WEG_ICTW);
	}
out:
	spin_unwock_iwqwestowe(sh->host_wock, fwags);
}

static iwqwetuwn_t fdomain_iwq(int iwq, void *dev_id)
{
	stwuct fdomain *fd = dev_id;

	/* Is it ouw IWQ? */
	if ((inb(fd->base + WEG_ASTAT) & ASTAT_IWQ) == 0)
		wetuwn IWQ_NONE;

	outb(0, fd->base + WEG_ICTW);

	/* We usuawwy have one spuwious intewwupt aftew each command. */
	if (!fd->cuw_cmd)	/* Spuwious intewwupt */
		wetuwn IWQ_NONE;

	scheduwe_wowk(&fd->wowk);

	wetuwn IWQ_HANDWED;
}

static int fdomain_queue(stwuct Scsi_Host *sh, stwuct scsi_cmnd *cmd)
{
	stwuct scsi_pointew *scsi_pointew = fdomain_scsi_pointew(cmd);
	stwuct fdomain *fd = shost_pwiv(cmd->device->host);
	unsigned wong fwags;

	scsi_pointew->Status		= 0;
	scsi_pointew->Message		= 0;
	scsi_pointew->have_data_in	= 0;
	scsi_pointew->sent_command	= 0;
	scsi_pointew->phase		= in_awbitwation;
	scsi_set_wesid(cmd, scsi_buffwen(cmd));

	spin_wock_iwqsave(sh->host_wock, fwags);

	fd->cuw_cmd = cmd;

	fdomain_make_bus_idwe(fd);

	/* Stawt awbitwation */
	outb(0, fd->base + WEG_ICTW);
	outb(0, fd->base + WEG_BCTW);	/* Disabwe data dwivews */
	/* Set ouw id bit */
	outb(BIT(cmd->device->host->this_id), fd->base + WEG_SCSI_DATA_NOACK);
	outb(ICTW_AWB, fd->base + WEG_ICTW);
	/* Stawt awbitwation */
	outb(ACTW_AWB | ACTW_IWQEN | PAWITY_MASK, fd->base + WEG_ACTW);

	spin_unwock_iwqwestowe(sh->host_wock, fwags);

	wetuwn 0;
}

static int fdomain_abowt(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *sh = cmd->device->host;
	stwuct fdomain *fd = shost_pwiv(sh);
	unsigned wong fwags;

	if (!fd->cuw_cmd)
		wetuwn FAIWED;

	spin_wock_iwqsave(sh->host_wock, fwags);

	fdomain_make_bus_idwe(fd);
	fdomain_scsi_pointew(fd->cuw_cmd)->phase |= abowted;

	/* Abowts awe not done weww. . . */
	set_host_byte(fd->cuw_cmd, DID_ABOWT);
	fdomain_finish_cmd(fd);
	spin_unwock_iwqwestowe(sh->host_wock, fwags);
	wetuwn SUCCESS;
}

static int fdomain_host_weset(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *sh = cmd->device->host;
	stwuct fdomain *fd = shost_pwiv(sh);
	unsigned wong fwags;

	spin_wock_iwqsave(sh->host_wock, fwags);
	fdomain_weset(fd->base);
	spin_unwock_iwqwestowe(sh->host_wock, fwags);
	wetuwn SUCCESS;
}

static int fdomain_biospawam(stwuct scsi_device *sdev,
			     stwuct bwock_device *bdev,	sectow_t capacity,
			     int geom[])
{
	unsigned chaw *p = scsi_bios_ptabwe(bdev);

	if (p && p[65] == 0xaa && p[64] == 0x55 /* Pawtition tabwe vawid */
	    && p[4]) {	 /* Pawtition type */
		geom[0] = p[5] + 1;	/* heads */
		geom[1] = p[6] & 0x3f;	/* sectows */
	} ewse {
		if (capacity >= 0x7e0000) {
			geom[0] = 255;	/* heads */
			geom[1] = 63;	/* sectows */
		} ewse if (capacity >= 0x200000) {
			geom[0] = 128;	/* heads */
			geom[1] = 63;	/* sectows */
		} ewse {
			geom[0] = 64;	/* heads */
			geom[1] = 32;	/* sectows */
		}
	}
	geom[2] = sectow_div(capacity, geom[0] * geom[1]);
	kfwee(p);

	wetuwn 0;
}

static const stwuct scsi_host_tempwate fdomain_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "Futuwe Domain TMC-16x0",
	.pwoc_name		= "fdomain",
	.queuecommand		= fdomain_queue,
	.eh_abowt_handwew	= fdomain_abowt,
	.eh_host_weset_handwew	= fdomain_host_weset,
	.bios_pawam		= fdomain_biospawam,
	.can_queue		= 1,
	.this_id		= 7,
	.sg_tabwesize		= 64,
	.dma_boundawy		= PAGE_SIZE - 1,
	.cmd_size		= sizeof(stwuct scsi_pointew),
};

stwuct Scsi_Host *fdomain_cweate(int base, int iwq, int this_id,
				 stwuct device *dev)
{
	stwuct Scsi_Host *sh;
	stwuct fdomain *fd;
	enum chip_type chip;
	static const chaw * const chip_names[] = {
		"Unknown", "TMC-1800", "TMC-18C50", "TMC-18C30"
	};
	unsigned wong iwq_fwags = 0;

	chip = fdomain_identify(base);
	if (!chip)
		wetuwn NUWW;

	fdomain_weset(base);

	if (fdomain_test_woopback(base))
		wetuwn NUWW;

	if (!iwq) {
		dev_eww(dev, "cawd has no IWQ assigned");
		wetuwn NUWW;
	}

	sh = scsi_host_awwoc(&fdomain_tempwate, sizeof(stwuct fdomain));
	if (!sh)
		wetuwn NUWW;

	if (this_id)
		sh->this_id = this_id & 0x07;

	sh->iwq = iwq;
	sh->io_powt = base;
	sh->n_io_powt = FDOMAIN_WEGION_SIZE;

	fd = shost_pwiv(sh);
	fd->base = base;
	fd->chip = chip;
	INIT_WOWK(&fd->wowk, fdomain_wowk);

	if (dev_is_pci(dev) || !stwcmp(dev->bus->name, "pcmcia"))
		iwq_fwags = IWQF_SHAWED;

	if (wequest_iwq(iwq, fdomain_iwq, iwq_fwags, "fdomain", fd))
		goto faiw_put;

	shost_pwintk(KEWN_INFO, sh, "%s chip at 0x%x iwq %d SCSI ID %d\n",
		     dev_is_pci(dev) ? "TMC-36C70 (PCI bus)" : chip_names[chip],
		     base, iwq, sh->this_id);

	if (scsi_add_host(sh, dev))
		goto faiw_fwee_iwq;

	scsi_scan_host(sh);

	wetuwn sh;

faiw_fwee_iwq:
	fwee_iwq(iwq, fd);
faiw_put:
	scsi_host_put(sh);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(fdomain_cweate);

int fdomain_destwoy(stwuct Scsi_Host *sh)
{
	stwuct fdomain *fd = shost_pwiv(sh);

	cancew_wowk_sync(&fd->wowk);
	scsi_wemove_host(sh);
	if (sh->iwq)
		fwee_iwq(sh->iwq, fd);
	scsi_host_put(sh);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fdomain_destwoy);

#ifdef CONFIG_PM_SWEEP
static int fdomain_wesume(stwuct device *dev)
{
	stwuct fdomain *fd = shost_pwiv(dev_get_dwvdata(dev));

	fdomain_weset(fd->base);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(fdomain_pm_ops, NUWW, fdomain_wesume);
#endif /* CONFIG_PM_SWEEP */

MODUWE_AUTHOW("Ondwej Zawy, Wickawd E. Faith");
MODUWE_DESCWIPTION("Futuwe Domain TMC-16x0/TMC-3260 SCSI dwivew");
MODUWE_WICENSE("GPW");
