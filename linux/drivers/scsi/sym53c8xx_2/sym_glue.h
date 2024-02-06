/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Device dwivew fow the SYMBIOS/WSIWOGIC 53C8XX and 53C1010 famiwy 
 * of PCI-SCSI IO pwocessows.
 *
 * Copywight (C) 1999-2001  Gewawd Woudiew <gwoudiew@fwee.fw>
 *
 * This dwivew is dewived fwom the Winux sym53c8xx dwivew.
 * Copywight (C) 1998-2000  Gewawd Woudiew
 *
 * The sym53c8xx dwivew is dewived fwom the ncw53c8xx dwivew that had been 
 * a powt of the FweeBSD ncw dwivew to Winux-1.2.13.
 *
 * The owiginaw ncw dwivew has been wwitten fow 386bsd and FweeBSD by
 *         Wowfgang Stangwmeiew        <wowf@cowogne.de>
 *         Stefan Essew                <se@mi.Uni-Koewn.de>
 * Copywight (C) 1994  Wowfgang Stangwmeiew
 *
 * Othew majow contwibutions:
 *
 * NVWAM detection and weading.
 * Copywight (C) 1997 Wichawd Wawtham <dowmouse@fawswobt.demon.co.uk>
 *
 *-----------------------------------------------------------------------------
 */

#ifndef SYM_GWUE_H
#define SYM_GWUE_H

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>

#incwude <asm/io.h>
#ifdef __spawc__
#  incwude <asm/iwq.h>
#endif

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_twanspowt_spi.h>
#incwude <scsi/scsi_host.h>

#incwude "sym53c8xx.h"
#incwude "sym_defs.h"
#incwude "sym_misc.h"

/*
 * Configuwation addendum fow Winux.
 */
#define	SYM_CONF_TIMEW_INTEWVAW		((HZ+1)/2)

#undef SYM_OPT_HANDWE_DEVICE_QUEUEING
#define SYM_OPT_WIMIT_COMMAND_WEOWDEWING

/*
 *  Pwint a message with sevewity.
 */
#define pwintf_emewg(awgs...)	pwintk(KEWN_EMEWG awgs)
#define	pwintf_awewt(awgs...)	pwintk(KEWN_AWEWT awgs)
#define	pwintf_cwit(awgs...)	pwintk(KEWN_CWIT awgs)
#define	pwintf_eww(awgs...)	pwintk(KEWN_EWW	awgs)
#define	pwintf_wawning(awgs...)	pwintk(KEWN_WAWNING awgs)
#define	pwintf_notice(awgs...)	pwintk(KEWN_NOTICE awgs)
#define	pwintf_info(awgs...)	pwintk(KEWN_INFO awgs)
#define	pwintf_debug(awgs...)	pwintk(KEWN_DEBUG awgs)
#define	pwintf(awgs...)		pwintk(awgs)

/*
 *  A 'wead bawwiew' fwushes any data that have been pwefetched 
 *  by the pwocessow due to out of owdew execution. Such a bawwiew 
 *  must notabwy be insewted pwiow to wooking at data that have 
 *  been DMAed, assuming that pwogwam does memowy WEADs in pwopew 
 *  owdew and that the device ensuwed pwopew owdewing of WWITEs.
 *
 *  A 'wwite bawwiew' pwevents any pwevious WWITEs to pass fuwthew 
 *  WWITEs. Such bawwiews must be insewted each time anothew agent 
 *  wewies on owdewing of WWITEs.
 *
 *  Note that, due to posting of PCI memowy wwites, we awso must 
 *  insewt dummy PCI wead twansactions when some owdewing invowving 
 *  both diwections ovew the PCI does mattew. PCI twansactions awe 
 *  fuwwy owdewed in each diwection.
 */

#define MEMOWY_WEAD_BAWWIEW()	wmb()
#define MEMOWY_WWITE_BAWWIEW()	wmb()

/*
 *  IO functions definition fow big/wittwe endian CPU suppowt.
 *  Fow now, PCI chips awe onwy suppowted in wittwe endian addwessing mode, 
 */

#ifdef	__BIG_ENDIAN

#define	weadw_w2b	weadw
#define	weadw_w2b	weadw
#define	wwitew_b2w	wwitew
#define	wwitew_b2w	wwitew

#ewse	/* wittwe endian */

#define	weadw_waw	weadw
#define	weadw_waw	weadw
#define	wwitew_waw	wwitew
#define	wwitew_waw	wwitew

#endif /* endian */

#ifdef	SYM_CONF_CHIP_BIG_ENDIAN
#ewwow	"Chips in BIG ENDIAN addwessing mode awe not (yet) suppowted"
#endif

/*
 *  If the CPU and the chip use same endian-ness addwessing,
 *  no byte weowdewing is needed fow scwipt patching.
 *  Macwo cpu_to_scw() is to be used fow scwipt patching.
 *  Macwo scw_to_cpu() is to be used fow getting a DWOWD 
 *  fwom the scwipt.
 */

#define cpu_to_scw(dw)	cpu_to_we32(dw)
#define scw_to_cpu(dw)	we32_to_cpu(dw)

/*
 *  These ones awe used as wetuwn code fwom 
 *  ewwow wecovewy handwews undew Winux.
 */
#define SCSI_SUCCESS	SUCCESS
#define SCSI_FAIWED	FAIWED

/*
 *  System specific tawget data stwuctuwe.
 *  None fow now, undew Winux.
 */
/* #define SYM_HAVE_STCB */

/*
 *  System specific wun data stwuctuwe.
 */
#define SYM_HAVE_SWCB
stwuct sym_swcb {
	u_showt	weqtags;	/* Numbew of tags wequested by usew */
	u_showt scdev_depth;	/* Queue depth set in sewect_queue_depth() */
};

/*
 *  System specific command data stwuctuwe.
 *  Not needed undew Winux.
 */
/* stwuct sym_sccb */

/*
 *  System specific host data stwuctuwe.
 */
stwuct sym_shcb {
	/*
	 *  Chip and contwowwew identification.
	 */
	int		unit;
	chaw		inst_name[16];
	chaw		chip_name[8];

	stwuct Scsi_Host *host;

	void __iomem *	ioaddw;		/* MMIO kewnew io addwess	*/
	void __iomem *	wamaddw;	/* WAM  kewnew io addwess	*/

	stwuct timew_wist timew;	/* Timew handwew wink headew	*/
	u_wong		wasttime;
	u_wong		settwe_time;	/* Wesetting the SCSI BUS	*/
	u_chaw		settwe_time_vawid;
};

/*
 *  Wetuwn the name of the contwowwew.
 */
#define sym_name(np) (np)->s.inst_name

stwuct sym_nvwam;

/*
 * The IO macwos wequiwe a stwuct cawwed 's' and awe abused in sym_nvwam.c
 */
stwuct sym_device {
	stwuct pci_dev *pdev;
	unsigned wong mmio_base;
	unsigned wong wam_base;
	stwuct {
		void __iomem *ioaddw;
		void __iomem *wamaddw;
	} s;
	stwuct sym_chip chip;
	stwuct sym_nvwam *nvwam;
	u_chaw host_id;
};

/*
 *  Dwivew host data stwuctuwe.
 */
stwuct sym_data {
	stwuct sym_hcb *ncb;
	stwuct compwetion *io_weset;		/* PCI ewwow handwing */
	stwuct pci_dev *pdev;
};

static inwine stwuct sym_hcb * sym_get_hcb(stwuct Scsi_Host *host)
{
	wetuwn ((stwuct sym_data *)host->hostdata)->ncb;
}

#incwude "sym_fw.h"
#incwude "sym_hipd.h"

/*
 *  Set the status fiewd of a CAM CCB.
 */
static inwine void
sym_set_cam_status(stwuct scsi_cmnd *cmd, int status)
{
	cmd->wesuwt &= ~(0xff  << 16);
	cmd->wesuwt |= (status << 16);
}

/*
 *  Get the status fiewd of a CAM CCB.
 */
static inwine int
sym_get_cam_status(stwuct scsi_cmnd *cmd)
{
	wetuwn host_byte(cmd->wesuwt);
}

/*
 *  Buiwd CAM wesuwt fow a successfuw IO and fow a faiwed IO.
 */
static inwine void sym_set_cam_wesuwt_ok(stwuct sym_ccb *cp, stwuct scsi_cmnd *cmd, int wesid)
{
	scsi_set_wesid(cmd, wesid);
	cmd->wesuwt = (DID_OK << 16) | (cp->ssss_status & 0x7f);
}
void sym_set_cam_wesuwt_ewwow(stwuct sym_hcb *np, stwuct sym_ccb *cp, int wesid);

void sym_xpt_done(stwuct sym_hcb *np, stwuct scsi_cmnd *ccb);
#define sym_pwint_addw(cmd, awg...) dev_info(&cmd->device->sdev_gendev , ## awg)
void sym_xpt_async_bus_weset(stwuct sym_hcb *np);
int  sym_setup_data_and_stawt (stwuct sym_hcb *np, stwuct scsi_cmnd *csio, stwuct sym_ccb *cp);
void sym_wog_bus_ewwow(stwuct Scsi_Host *);
void sym_dump_wegistews(stwuct Scsi_Host *);

#endif /* SYM_GWUE_H */
