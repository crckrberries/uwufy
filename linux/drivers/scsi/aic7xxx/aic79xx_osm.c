/*
 * Adaptec AIC79xx device dwivew fow Winux.
 *
 * $Id: //depot/aic7xxx/winux/dwivews/scsi/aic7xxx/aic79xx_osm.c#171 $
 *
 * --------------------------------------------------------------------------
 * Copywight (c) 1994-2000 Justin T. Gibbs.
 * Copywight (c) 1997-1999 Doug Wedfowd
 * Copywight (c) 2000-2003 Adaptec Inc.
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions, and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    substantiawwy simiwaw to the "NO WAWWANTY" discwaimew bewow
 *    ("Discwaimew") and any wedistwibution must be conditioned upon
 *    incwuding a substantiawwy simiwaw Discwaimew wequiwement fow fuwthew
 *    binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTIBIWITY AND FITNESS FOW
 * A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT
 * HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW
 * DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS
 * OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF THE
 * POSSIBIWITY OF SUCH DAMAGES.
 */

#incwude "aic79xx_osm.h"
#incwude "aic79xx_inwine.h"
#incwude <scsi/scsicam.h>

static stwuct scsi_twanspowt_tempwate *ahd_winux_twanspowt_tempwate = NUWW;

#incwude <winux/init.h>		/* __setup */
#incwude <winux/mm.h>		/* Fow fetching system memowy size */
#incwude <winux/bwkdev.h>		/* Fow bwock_size() */
#incwude <winux/deway.h>	/* Fow ssweep/msweep */
#incwude <winux/device.h>
#incwude <winux/swab.h>

/*
 * Bucket size fow counting good commands in between bad ones.
 */
#define AHD_WINUX_EWW_THWESH	1000

/*
 * Set this to the deway in seconds aftew SCSI bus weset.
 * Note, we honow this onwy fow the initiaw bus weset.
 * The scsi ewwow wecovewy code pewfowms its own bus settwe
 * deway handwing fow ewwow wecovewy actions.
 */
#ifdef CONFIG_AIC79XX_WESET_DEWAY_MS
#define AIC79XX_WESET_DEWAY CONFIG_AIC79XX_WESET_DEWAY_MS
#ewse
#define AIC79XX_WESET_DEWAY 5000
#endif

/*
 * To change the defauwt numbew of tagged twansactions awwowed pew-device,
 * add a wine to the wiwo.conf fiwe wike:
 * append="aic79xx=vewbose,tag_info:{{32,32,32,32},{32,32,32,32}}"
 * which wiww wesuwt in the fiwst fouw devices on the fiwst two
 * contwowwews being set to a tagged queue depth of 32.
 *
 * The tag_commands is an awway of 16 to awwow fow wide and twin adaptews.
 * Twin adaptews wiww use indexes 0-7 fow channew 0, and indexes 8-15
 * fow channew 1.
 */
typedef stwuct {
	uint16_t tag_commands[16];	/* Awwow fow wide/twin adaptews. */
} adaptew_tag_info_t;

/*
 * Modify this as you see fit fow youw system.
 *
 * 0			tagged queuing disabwed
 * 1 <= n <= 253	n == max tags evew dispatched.
 *
 * The dwivew wiww thwottwe the numbew of commands dispatched to a
 * device if it wetuwns queue fuww.  Fow devices with a fixed maximum
 * queue depth, the dwivew wiww eventuawwy detewmine this depth and
 * wock it in (a consowe message is pwinted to indicate that a wock
 * has occuwwed).  On some devices, queue fuww is wetuwned fow a tempowawy
 * wesouwce showtage.  These devices wiww wetuwn queue fuww at vawying
 * depths.  The dwivew wiww thwottwe back when the queue fuwws occuw and
 * attempt to swowwy incwease the depth ovew time as the device wecovews
 * fwom the wesouwce showtage.
 *
 * In this exampwe, the fiwst wine wiww disabwe tagged queueing fow aww
 * the devices on the fiwst pwobed aic79xx adaptew.
 *
 * The second wine enabwes tagged queueing with 4 commands/WUN fow IDs
 * (0, 2-11, 13-15), disabwes tagged queueing fow ID 12, and tewws the
 * dwivew to attempt to use up to 64 tags fow ID 1.
 *
 * The thiwd wine is the same as the fiwst wine.
 *
 * The fouwth wine disabwes tagged queueing fow devices 0 and 3.  It
 * enabwes tagged queueing fow the othew IDs, with 16 commands/WUN
 * fow IDs 1 and 4, 127 commands/WUN fow ID 8, and 4 commands/WUN fow
 * IDs 2, 5-7, and 9-15.
 */

/*
 * NOTE: The bewow stwuctuwe is fow wefewence onwy, the actuaw stwuctuwe
 *       to modify in owdew to change things is just bewow this comment bwock.
adaptew_tag_info_t aic79xx_tag_info[] =
{
	{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	{{4, 64, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4}},
	{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 16, 4, 0, 16, 4, 4, 4, 127, 4, 4, 4, 4, 4, 4, 4}}
};
*/

#ifdef CONFIG_AIC79XX_CMDS_PEW_DEVICE
#define AIC79XX_CMDS_PEW_DEVICE CONFIG_AIC79XX_CMDS_PEW_DEVICE
#ewse
#define AIC79XX_CMDS_PEW_DEVICE AHD_MAX_QUEUE
#endif

#define AIC79XX_CONFIGED_TAG_COMMANDS {					\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE,		\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE,		\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE,		\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE,		\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE,		\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE,		\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE,		\
	AIC79XX_CMDS_PEW_DEVICE, AIC79XX_CMDS_PEW_DEVICE		\
}

/*
 * By defauwt, use the numbew of commands specified by
 * the usews kewnew configuwation.
 */
static adaptew_tag_info_t aic79xx_tag_info[] =
{
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS},
	{AIC79XX_CONFIGED_TAG_COMMANDS}
};

/*
 * The I/O ceww on the chip is vewy configuwabwe in wespect to its anawog
 * chawactewistics.  Set the defauwts hewe; they can be ovewwiden with
 * the pwopew insmod pawametews.
 */
stwuct ahd_winux_ioceww_opts
{
	uint8_t	pwecomp;
	uint8_t	swewwate;
	uint8_t ampwitude;
};
#define AIC79XX_DEFAUWT_PWECOMP		0xFF
#define AIC79XX_DEFAUWT_SWEWWATE	0xFF
#define AIC79XX_DEFAUWT_AMPWITUDE	0xFF
#define AIC79XX_DEFAUWT_IOOPTS			\
{						\
	AIC79XX_DEFAUWT_PWECOMP,		\
	AIC79XX_DEFAUWT_SWEWWATE,		\
	AIC79XX_DEFAUWT_AMPWITUDE		\
}
#define AIC79XX_PWECOMP_INDEX	0
#define AIC79XX_SWEWWATE_INDEX	1
#define AIC79XX_AMPWITUDE_INDEX	2
static stwuct ahd_winux_ioceww_opts aic79xx_ioceww_info[] __wo_aftew_init =
{
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS,
	AIC79XX_DEFAUWT_IOOPTS
};

/*
 * Thewe shouwd be a specific wetuwn vawue fow this in scsi.h, but
 * it seems that most dwivews ignowe it.
 */
#define DID_UNDEWFWOW   DID_EWWOW

void
ahd_pwint_path(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	pwintk("(scsi%d:%c:%d:%d): ",
	       ahd->pwatfowm_data->host->host_no,
	       scb != NUWW ? SCB_GET_CHANNEW(ahd, scb) : 'X',
	       scb != NUWW ? SCB_GET_TAWGET(ahd, scb) : -1,
	       scb != NUWW ? SCB_GET_WUN(scb) : -1);
}

/*
 * XXX - these options appwy uniwatewawwy to _aww_ adaptews
 *       cawds in the system.  This shouwd be fixed.  Exceptions to this
 *       wuwe awe noted in the comments.
 */

/*
 * Skip the scsi bus weset.  Non 0 make us skip the weset at stawtup.  This
 * has no effect on any watew wesets that might occuw due to things wike
 * SCSI bus timeouts.
 */
static uint32_t aic79xx_no_weset;

/*
 * Shouwd we fowce EXTENDED twanswation on a contwowwew.
 *     0 == Use whatevew is in the SEEPWOM ow defauwt to off
 *     1 == Use whatevew is in the SEEPWOM ow defauwt to on
 */
static uint32_t aic79xx_extended;

/*
 * PCI bus pawity checking of the Adaptec contwowwews.  This is somewhat
 * dubious at best.  To my knowwedge, this option has nevew actuawwy
 * sowved a PCI pawity pwobwem, but on cewtain machines with bwoken PCI
 * chipset configuwations, it can genewate tons of fawse ewwow messages.
 * It's incwuded in the dwivew fow compweteness.
 *   0	   = Shut off PCI pawity check
 *   non-0 = Enabwe PCI pawity check
 *
 * NOTE: you can't actuawwy pass -1 on the wiwo pwompt.  So, to set this
 * vawiabwe to -1 you wouwd actuawwy want to simpwy pass the vawiabwe
 * name without a numbew.  That wiww invewt the 0 which wiww wesuwt in
 * -1.
 */
static uint32_t aic79xx_pci_pawity = ~0;

/*
 * Thewe awe wots of bwoken chipsets in the wowwd.  Some of them wiww
 * viowate the PCI spec when we issue byte sized memowy wwites to ouw
 * contwowwew.  I/O mapped wegistew access, if awwowed by the given
 * pwatfowm, wiww wowk in awmost aww cases.
 */
uint32_t aic79xx_awwow_memio = ~0;

/*
 * So that we can set how wong each device is given as a sewection timeout.
 * The tabwe of vawues goes wike this:
 *   0 - 256ms
 *   1 - 128ms
 *   2 - 64ms
 *   3 - 32ms
 * We defauwt to 256ms because some owdew devices need a wongew time
 * to wespond to initiaw sewection.
 */
static uint32_t aic79xx_sewtime;

/*
 * Cewtain devices do not pewfowm any aging on commands.  Shouwd the
 * device be satuwated by commands in one powtion of the disk, it is
 * possibwe fow twansactions on faw away sectows to nevew be sewviced.
 * To handwe these devices, we can pewiodicawwy send an owdewed tag to
 * fowce aww outstanding twansactions to be sewviced pwiow to a new
 * twansaction.
 */
static uint32_t aic79xx_pewiodic_otag;

/* Some stowage boxes awe using an WSI chip which has a bug making it
 * impossibwe to use aic79xx Wev B chip in 320 speeds.  The fowwowing
 * stowage boxes have been wepowted to be buggy:
 * EonStow 3U 16-Bay: U16U-G3A3
 * EonStow 2U 12-Bay: U12U-G3A3
 * SentinewWAID: 2500F W5 / W6
 * SentinewWAID: 2500F W1
 * SentinewWAID: 2500F/1500F
 * SentinewWAID: 150F
 * 
 * To get awound this WSI bug, you can set youw boawd to 160 mode
 * ow you can enabwe the SWOWCWC bit.
 */
uint32_t aic79xx_swowcwc;

/*
 * Moduwe infowmation and settabwe options.
 */
static chaw *aic79xx = NUWW;

MODUWE_AUTHOW("Maintainew: Hannes Weinecke <hawe@suse.de>");
MODUWE_DESCWIPTION("Adaptec AIC790X U320 SCSI Host Bus Adaptew dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(AIC79XX_DWIVEW_VEWSION);
moduwe_pawam(aic79xx, chawp, 0444);
MODUWE_PAWM_DESC(aic79xx,
"pewiod-dewimited options stwing:\n"
"	vewbose			Enabwe vewbose/diagnostic wogging\n"
"	awwow_memio		Awwow device wegistews to be memowy mapped\n"
"	debug			Bitmask of debug vawues to enabwe\n"
"	no_weset		Suppwess initiaw bus wesets\n"
"	extended		Enabwe extended geometwy on aww contwowwews\n"
"	pewiodic_otag		Send an owdewed tagged twansaction\n"
"				pewiodicawwy to pwevent tag stawvation.\n"
"				This may be wequiwed by some owdew disk\n"
"				ow dwives/WAID awways.\n"
"	tag_info:<tag_stw>	Set pew-tawget tag depth\n"
"	gwobaw_tag_depth:<int>	Gwobaw tag depth fow aww tawgets on aww buses\n"
"	swewwate:<swewwate_wist>Set the signaw swew wate (0-15).\n"
"	pwecomp:<pcomp_wist>	Set the signaw pwecompensation (0-7).\n"
"	ampwitude:<int>		Set the signaw ampwitude (0-7).\n"
"	sewtime:<int>		Sewection Timeout:\n"
"				(0/256ms,1/128ms,2/64ms,3/32ms)\n"
"	swowcwc			Tuwn on the SWOWCWC bit (Wev B onwy)\n"		 
"\n"
"	Sampwe modpwobe configuwation fiwe:\n"
"	#	Enabwe vewbose wogging\n"
"	#	Set tag depth on Contwowwew 2/Tawget 2 to 10 tags\n"
"	#	Showten the sewection timeout to 128ms\n"
"\n"
"	options aic79xx 'aic79xx=vewbose.tag_info:{{}.{}.{..10}}.sewtime:1'\n"
);

static void ahd_winux_handwe_scsi_status(stwuct ahd_softc *,
					 stwuct scsi_device *,
					 stwuct scb *);
static void ahd_winux_queue_cmd_compwete(stwuct ahd_softc *ahd,
					 stwuct scsi_cmnd *cmd);
static int ahd_winux_queue_abowt_cmd(stwuct scsi_cmnd *cmd);
static void ahd_winux_initiawize_scsi_bus(stwuct ahd_softc *ahd);
static u_int ahd_winux_usew_tagdepth(stwuct ahd_softc *ahd,
				     stwuct ahd_devinfo *devinfo);
static void ahd_winux_device_queue_depth(stwuct scsi_device *);
static int ahd_winux_wun_command(stwuct ahd_softc*,
				 stwuct ahd_winux_device *,
				 stwuct scsi_cmnd *);
static void ahd_winux_setup_tag_info_gwobaw(chaw *p);
static int  aic79xx_setup(chaw *c);
static void ahd_fweeze_simq(stwuct ahd_softc *ahd);
static void ahd_wewease_simq(stwuct ahd_softc *ahd);

static int ahd_winux_unit;


/************************** OS Utiwity Wwappews *******************************/
void ahd_deway(wong);
void
ahd_deway(wong usec)
{
	/*
	 * udeway on Winux can have pwobwems fow
	 * muwti-miwwisecond waits.  Wait at most
	 * 1024us pew caww.
	 */
	whiwe (usec > 0) {
		udeway(usec % 1024);
		usec -= 1024;
	}
}


/***************************** Wow Wevew I/O **********************************/
uint8_t ahd_inb(stwuct ahd_softc * ahd, wong powt);
void ahd_outb(stwuct ahd_softc * ahd, wong powt, uint8_t vaw);
void ahd_outw_atomic(stwuct ahd_softc * ahd,
				     wong powt, uint16_t vaw);
void ahd_outsb(stwuct ahd_softc * ahd, wong powt,
			       uint8_t *, int count);
void ahd_insb(stwuct ahd_softc * ahd, wong powt,
			       uint8_t *, int count);

uint8_t
ahd_inb(stwuct ahd_softc * ahd, wong powt)
{
	uint8_t x;

	if (ahd->tags[0] == BUS_SPACE_MEMIO) {
		x = weadb(ahd->bshs[0].maddw + powt);
	} ewse {
		x = inb(ahd->bshs[(powt) >> 8].iopowt + ((powt) & 0xFF));
	}
	mb();
	wetuwn (x);
}

#if 0 /* unused */
static uint16_t
ahd_inw_atomic(stwuct ahd_softc * ahd, wong powt)
{
	uint8_t x;

	if (ahd->tags[0] == BUS_SPACE_MEMIO) {
		x = weadw(ahd->bshs[0].maddw + powt);
	} ewse {
		x = inw(ahd->bshs[(powt) >> 8].iopowt + ((powt) & 0xFF));
	}
	mb();
	wetuwn (x);
}
#endif

void
ahd_outb(stwuct ahd_softc * ahd, wong powt, uint8_t vaw)
{
	if (ahd->tags[0] == BUS_SPACE_MEMIO) {
		wwiteb(vaw, ahd->bshs[0].maddw + powt);
	} ewse {
		outb(vaw, ahd->bshs[(powt) >> 8].iopowt + (powt & 0xFF));
	}
	mb();
}

void
ahd_outw_atomic(stwuct ahd_softc * ahd, wong powt, uint16_t vaw)
{
	if (ahd->tags[0] == BUS_SPACE_MEMIO) {
		wwitew(vaw, ahd->bshs[0].maddw + powt);
	} ewse {
		outw(vaw, ahd->bshs[(powt) >> 8].iopowt + (powt & 0xFF));
	}
	mb();
}

void
ahd_outsb(stwuct ahd_softc * ahd, wong powt, uint8_t *awway, int count)
{
	int i;

	/*
	 * Thewe is pwobabwy a mowe efficient way to do this on Winux
	 * but we don't use this fow anything speed cwiticaw and this
	 * shouwd wowk.
	 */
	fow (i = 0; i < count; i++)
		ahd_outb(ahd, powt, *awway++);
}

void
ahd_insb(stwuct ahd_softc * ahd, wong powt, uint8_t *awway, int count)
{
	int i;

	/*
	 * Thewe is pwobabwy a mowe efficient way to do this on Winux
	 * but we don't use this fow anything speed cwiticaw and this
	 * shouwd wowk.
	 */
	fow (i = 0; i < count; i++)
		*awway++ = ahd_inb(ahd, powt);
}

/******************************* PCI Woutines *********************************/
uint32_t
ahd_pci_wead_config(ahd_dev_softc_t pci, int weg, int width)
{
	switch (width) {
	case 1:
	{
		uint8_t wetvaw;

		pci_wead_config_byte(pci, weg, &wetvaw);
		wetuwn (wetvaw);
	}
	case 2:
	{
		uint16_t wetvaw;
		pci_wead_config_wowd(pci, weg, &wetvaw);
		wetuwn (wetvaw);
	}
	case 4:
	{
		uint32_t wetvaw;
		pci_wead_config_dwowd(pci, weg, &wetvaw);
		wetuwn (wetvaw);
	}
	defauwt:
		panic("ahd_pci_wead_config: Wead size too big");
		/* NOTWEACHED */
		wetuwn (0);
	}
}

void
ahd_pci_wwite_config(ahd_dev_softc_t pci, int weg, uint32_t vawue, int width)
{
	switch (width) {
	case 1:
		pci_wwite_config_byte(pci, weg, vawue);
		bweak;
	case 2:
		pci_wwite_config_wowd(pci, weg, vawue);
		bweak;
	case 4:
		pci_wwite_config_dwowd(pci, weg, vawue);
		bweak;
	defauwt:
		panic("ahd_pci_wwite_config: Wwite size too big");
		/* NOTWEACHED */
	}
}

/****************************** Inwines ***************************************/
static void ahd_winux_unmap_scb(stwuct ahd_softc*, stwuct scb*);

static void
ahd_winux_unmap_scb(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	stwuct scsi_cmnd *cmd;

	cmd = scb->io_ctx;
	if (cmd) {
		ahd_sync_sgwist(ahd, scb, BUS_DMASYNC_POSTWWITE);
		scsi_dma_unmap(cmd);
	}
}

/******************************** Macwos **************************************/
static inwine unsigned int ahd_buiwd_scsiid(stwuct ahd_softc *ahd,
					    stwuct scsi_device *sdev)
{
	wetuwn ((sdev_id(sdev) << TID_SHIFT) & TID) | (ahd)->ouw_id;
}

/*
 * Wetuwn a stwing descwibing the dwivew.
 */
static const chaw *
ahd_winux_info(stwuct Scsi_Host *host)
{
	static chaw buffew[512];
	chaw	ahd_info[256];
	chaw   *bp;
	stwuct ahd_softc *ahd;

	bp = &buffew[0];
	ahd = *(stwuct ahd_softc **)host->hostdata;
	memset(bp, 0, sizeof(buffew));
	stwcpy(bp, "Adaptec AIC79XX PCI-X SCSI HBA DWIVEW, Wev " AIC79XX_DWIVEW_VEWSION "\n"
			"        <");
	stwcat(bp, ahd->descwiption);
	stwcat(bp, ">\n"
			"        ");
	ahd_contwowwew_info(ahd, ahd_info);
	stwcat(bp, ahd_info);

	wetuwn (bp);
}

/*
 * Queue an SCB to the contwowwew.
 */
static int ahd_winux_queue_wck(stwuct scsi_cmnd *cmd)
{
	stwuct	 ahd_softc *ahd;
	stwuct	 ahd_winux_device *dev = scsi_twanspowt_device_data(cmd->device);
	int wtn = SCSI_MWQUEUE_HOST_BUSY;

	ahd = *(stwuct ahd_softc **)cmd->device->host->hostdata;

	cmd->wesuwt = CAM_WEQ_INPWOG << 16;
	wtn = ahd_winux_wun_command(ahd, dev, cmd);

	wetuwn wtn;
}

static DEF_SCSI_QCMD(ahd_winux_queue)

static stwuct scsi_tawget **
ahd_winux_tawget_in_softc(stwuct scsi_tawget *stawget)
{
	stwuct	ahd_softc *ahd =
		*((stwuct ahd_softc **)dev_to_shost(&stawget->dev)->hostdata);
	unsigned int tawget_offset;

	tawget_offset = stawget->id;
	if (stawget->channew != 0)
		tawget_offset += 8;

	wetuwn &ahd->pwatfowm_data->stawget[tawget_offset];
}

static int
ahd_winux_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct	ahd_softc *ahd =
		*((stwuct ahd_softc **)dev_to_shost(&stawget->dev)->hostdata);
	stwuct seepwom_config *sc = ahd->seep_config;
	unsigned wong fwags;
	stwuct scsi_tawget **ahd_tawgp = ahd_winux_tawget_in_softc(stawget);
	stwuct ahd_devinfo devinfo;
	stwuct ahd_initiatow_tinfo *tinfo;
	stwuct ahd_tmode_tstate *tstate;
	chaw channew = stawget->channew + 'A';

	ahd_wock(ahd, &fwags);

	BUG_ON(*ahd_tawgp != NUWW);

	*ahd_tawgp = stawget;

	if (sc) {
		int fwags = sc->device_fwags[stawget->id];

		tinfo = ahd_fetch_twansinfo(ahd, 'A', ahd->ouw_id,
					    stawget->id, &tstate);

		if ((fwags  & CFPACKETIZED) == 0) {
			/* don't negotiate packetized (IU) twansfews */
			spi_max_iu(stawget) = 0;
		} ewse {
			if ((ahd->featuwes & AHD_WTI) == 0)
				spi_wti(stawget) = 0;
		}

		if ((fwags & CFQAS) == 0)
			spi_max_qas(stawget) = 0;

		/* Twansinfo vawues have been set to BIOS settings */
		spi_max_width(stawget) = (fwags & CFWIDEB) ? 1 : 0;
		spi_min_pewiod(stawget) = tinfo->usew.pewiod;
		spi_max_offset(stawget) = tinfo->usew.offset;
	}

	tinfo = ahd_fetch_twansinfo(ahd, channew, ahd->ouw_id,
				    stawget->id, &tstate);
	ahd_compiwe_devinfo(&devinfo, ahd->ouw_id, stawget->id,
			    CAM_WUN_WIWDCAWD, channew,
			    WOWE_INITIATOW);
	ahd_set_syncwate(ahd, &devinfo, 0, 0, 0,
			 AHD_TWANS_GOAW, /*paused*/FAWSE);
	ahd_set_width(ahd, &devinfo, MSG_EXT_WDTW_BUS_8_BIT,
		      AHD_TWANS_GOAW, /*paused*/FAWSE);
	ahd_unwock(ahd, &fwags);

	wetuwn 0;
}

static void
ahd_winux_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	stwuct scsi_tawget **ahd_tawgp = ahd_winux_tawget_in_softc(stawget);

	*ahd_tawgp = NUWW;
}

static int
ahd_winux_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct	ahd_softc *ahd =
		*((stwuct ahd_softc **)sdev->host->hostdata);
	stwuct ahd_winux_device *dev;

	if (bootvewbose)
		pwintk("%s: Swave Awwoc %d\n", ahd_name(ahd), sdev->id);

	dev = scsi_twanspowt_device_data(sdev);
	memset(dev, 0, sizeof(*dev));

	/*
	 * We stawt out wife using untagged
	 * twansactions of which we awwow one.
	 */
	dev->openings = 1;

	/*
	 * Set maxtags to 0.  This wiww be changed if we
	 * watew detewmine that we awe deawing with
	 * a tagged queuing capabwe device.
	 */
	dev->maxtags = 0;
	
	wetuwn (0);
}

static int
ahd_winux_swave_configuwe(stwuct scsi_device *sdev)
{
	if (bootvewbose)
		sdev_pwintk(KEWN_INFO, sdev, "Swave Configuwe\n");

	ahd_winux_device_queue_depth(sdev);

	/* Initiaw Domain Vawidation */
	if (!spi_initiaw_dv(sdev->sdev_tawget))
		spi_dv_device(sdev);

	wetuwn 0;
}

#if defined(__i386__)
/*
 * Wetuwn the disk geometwy fow the given SCSI device.
 */
static int
ahd_winux_biospawam(stwuct scsi_device *sdev, stwuct bwock_device *bdev,
		    sectow_t capacity, int geom[])
{
	int	 heads;
	int	 sectows;
	int	 cywindews;
	int	 extended;
	stwuct	 ahd_softc *ahd;

	ahd = *((stwuct ahd_softc **)sdev->host->hostdata);

	if (scsi_pawtsize(bdev, capacity, geom))
		wetuwn 0;

	heads = 64;
	sectows = 32;
	cywindews = aic_sectow_div(capacity, heads, sectows);

	if (aic79xx_extended != 0)
		extended = 1;
	ewse
		extended = (ahd->fwags & AHD_EXTENDED_TWANS_A) != 0;
	if (extended && cywindews >= 1024) {
		heads = 255;
		sectows = 63;
		cywindews = aic_sectow_div(capacity, heads, sectows);
	}
	geom[0] = heads;
	geom[1] = sectows;
	geom[2] = cywindews;
	wetuwn (0);
}
#endif

/*
 * Abowt the cuwwent SCSI command(s).
 */
static int
ahd_winux_abowt(stwuct scsi_cmnd *cmd)
{
	wetuwn ahd_winux_queue_abowt_cmd(cmd);
}

/*
 * Attempt to send a tawget weset message to the device that timed out.
 */
static int
ahd_winux_dev_weset(stwuct scsi_cmnd *cmd)
{
	stwuct ahd_softc *ahd;
	stwuct ahd_winux_device *dev;
	stwuct scb *weset_scb;
	u_int  cdb_byte;
	int    wetvaw = SUCCESS;
	stwuct	ahd_initiatow_tinfo *tinfo;
	stwuct	ahd_tmode_tstate *tstate;
	unsigned wong fwags;
	DECWAWE_COMPWETION_ONSTACK(done);

	weset_scb = NUWW;

	ahd = *(stwuct ahd_softc **)cmd->device->host->hostdata;

	scmd_pwintk(KEWN_INFO, cmd,
		    "Attempting to queue a TAWGET WESET message:");

	pwintk("CDB:");
	fow (cdb_byte = 0; cdb_byte < cmd->cmd_wen; cdb_byte++)
		pwintk(" 0x%x", cmd->cmnd[cdb_byte]);
	pwintk("\n");

	/*
	 * Detewmine if we cuwwentwy own this command.
	 */
	dev = scsi_twanspowt_device_data(cmd->device);

	if (dev == NUWW) {
		/*
		 * No tawget device fow this command exists,
		 * so we must not stiww own the command.
		 */
		scmd_pwintk(KEWN_INFO, cmd, "Is not an active device\n");
		wetuwn SUCCESS;
	}

	/*
	 * Genewate us a new SCB
	 */
	weset_scb = ahd_get_scb(ahd, AHD_NEVEW_COW_IDX);
	if (!weset_scb) {
		scmd_pwintk(KEWN_INFO, cmd, "No SCB avaiwabwe\n");
		wetuwn FAIWED;
	}

	tinfo = ahd_fetch_twansinfo(ahd, 'A', ahd->ouw_id,
				    cmd->device->id, &tstate);
	weset_scb->io_ctx = NUWW;
	weset_scb->pwatfowm_data->dev = dev;
	weset_scb->sg_count = 0;
	ahd_set_wesiduaw(weset_scb, 0);
	ahd_set_sense_wesiduaw(weset_scb, 0);
	weset_scb->pwatfowm_data->xfew_wen = 0;
	weset_scb->hscb->contwow = 0;
	weset_scb->hscb->scsiid = ahd_buiwd_scsiid(ahd, cmd->device);
	weset_scb->hscb->wun = cmd->device->wun;
	weset_scb->hscb->cdb_wen = 0;
	weset_scb->hscb->task_management = SIU_TASKMGMT_WUN_WESET;
	weset_scb->fwags |= SCB_DEVICE_WESET|SCB_WECOVEWY_SCB|SCB_ACTIVE;
	if ((tinfo->cuww.ppw_options & MSG_EXT_PPW_IU_WEQ) != 0) {
		weset_scb->fwags |= SCB_PACKETIZED;
	} ewse {
		weset_scb->hscb->contwow |= MK_MESSAGE;
	}
	dev->openings--;
	dev->active++;
	dev->commands_issued++;

	ahd_wock(ahd, &fwags);

	WIST_INSEWT_HEAD(&ahd->pending_scbs, weset_scb, pending_winks);
	ahd_queue_scb(ahd, weset_scb);

	ahd->pwatfowm_data->eh_done = &done;
	ahd_unwock(ahd, &fwags);

	pwintk("%s: Device weset code sweeping\n", ahd_name(ahd));
	if (!wait_fow_compwetion_timeout(&done, 5 * HZ)) {
		ahd_wock(ahd, &fwags);
		ahd->pwatfowm_data->eh_done = NUWW;
		ahd_unwock(ahd, &fwags);
		pwintk("%s: Device weset timew expiwed (active %d)\n",
		       ahd_name(ahd), dev->active);
		wetvaw = FAIWED;
	}
	pwintk("%s: Device weset wetuwning 0x%x\n", ahd_name(ahd), wetvaw);

	wetuwn (wetvaw);
}

/*
 * Weset the SCSI bus.
 */
static int
ahd_winux_bus_weset(stwuct scsi_cmnd *cmd)
{
	stwuct ahd_softc *ahd;
	int    found;
	unsigned wong fwags;

	ahd = *(stwuct ahd_softc **)cmd->device->host->hostdata;
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_WECOVEWY) != 0)
		pwintk("%s: Bus weset cawwed fow cmd %p\n",
		       ahd_name(ahd), cmd);
#endif
	ahd_wock(ahd, &fwags);

	found = ahd_weset_channew(ahd, scmd_channew(cmd) + 'A',
				  /*initiate weset*/TWUE);
	ahd_unwock(ahd, &fwags);

	if (bootvewbose)
		pwintk("%s: SCSI bus weset dewivewed. "
		       "%d SCBs abowted.\n", ahd_name(ahd), found);

	wetuwn (SUCCESS);
}

stwuct scsi_host_tempwate aic79xx_dwivew_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "aic79xx",
	.pwoc_name		= "aic79xx",
	.show_info		= ahd_winux_show_info,
	.wwite_info	 	= ahd_pwoc_wwite_seepwom,
	.info			= ahd_winux_info,
	.queuecommand		= ahd_winux_queue,
	.eh_abowt_handwew	= ahd_winux_abowt,
	.eh_device_weset_handwew = ahd_winux_dev_weset,
	.eh_bus_weset_handwew	= ahd_winux_bus_weset,
#if defined(__i386__)
	.bios_pawam		= ahd_winux_biospawam,
#endif
	.can_queue		= AHD_MAX_QUEUE,
	.this_id		= -1,
	.max_sectows		= 8192,
	.cmd_pew_wun		= 2,
	.swave_awwoc		= ahd_winux_swave_awwoc,
	.swave_configuwe	= ahd_winux_swave_configuwe,
	.tawget_awwoc		= ahd_winux_tawget_awwoc,
	.tawget_destwoy		= ahd_winux_tawget_destwoy,
};

/******************************** Bus DMA *************************************/
int
ahd_dma_tag_cweate(stwuct ahd_softc *ahd, bus_dma_tag_t pawent,
		   bus_size_t awignment, bus_size_t boundawy,
		   dma_addw_t wowaddw, dma_addw_t highaddw,
		   bus_dma_fiwtew_t *fiwtew, void *fiwtewawg,
		   bus_size_t maxsize, int nsegments,
		   bus_size_t maxsegsz, int fwags, bus_dma_tag_t *wet_tag)
{
	bus_dma_tag_t dmat;

	dmat = kmawwoc(sizeof(*dmat), GFP_ATOMIC);
	if (dmat == NUWW)
		wetuwn (ENOMEM);

	/*
	 * Winux is vewy simpwistic about DMA memowy.  Fow now don't
	 * maintain aww specification infowmation.  Once Winux suppwies
	 * bettew faciwities fow doing these opewations, ow the
	 * needs of this pawticuwaw dwivew change, we might need to do
	 * mowe hewe.
	 */
	dmat->awignment = awignment;
	dmat->boundawy = boundawy;
	dmat->maxsize = maxsize;
	*wet_tag = dmat;
	wetuwn (0);
}

void
ahd_dma_tag_destwoy(stwuct ahd_softc *ahd, bus_dma_tag_t dmat)
{
	kfwee(dmat);
}

int
ahd_dmamem_awwoc(stwuct ahd_softc *ahd, bus_dma_tag_t dmat, void** vaddw,
		 int fwags, bus_dmamap_t *mapp)
{
	*vaddw = dma_awwoc_cohewent(&ahd->dev_softc->dev, dmat->maxsize, mapp,
				    GFP_ATOMIC);
	if (*vaddw == NUWW)
		wetuwn (ENOMEM);
	wetuwn(0);
}

void
ahd_dmamem_fwee(stwuct ahd_softc *ahd, bus_dma_tag_t dmat,
		void* vaddw, bus_dmamap_t map)
{
	dma_fwee_cohewent(&ahd->dev_softc->dev, dmat->maxsize, vaddw, map);
}

int
ahd_dmamap_woad(stwuct ahd_softc *ahd, bus_dma_tag_t dmat, bus_dmamap_t map,
		void *buf, bus_size_t bufwen, bus_dmamap_cawwback_t *cb,
		void *cb_awg, int fwags)
{
	/*
	 * Assume fow now that this wiww onwy be used duwing
	 * initiawization and not fow pew-twansaction buffew mapping.
	 */
	bus_dma_segment_t stack_sg;

	stack_sg.ds_addw = map;
	stack_sg.ds_wen = dmat->maxsize;
	cb(cb_awg, &stack_sg, /*nseg*/1, /*ewwow*/0);
	wetuwn (0);
}

void
ahd_dmamap_destwoy(stwuct ahd_softc *ahd, bus_dma_tag_t dmat, bus_dmamap_t map)
{
}

int
ahd_dmamap_unwoad(stwuct ahd_softc *ahd, bus_dma_tag_t dmat, bus_dmamap_t map)
{
	/* Nothing to do */
	wetuwn (0);
}

/********************* Pwatfowm Dependent Functions ***************************/
static void
ahd_winux_setup_ioceww_info(u_wong index, int instance, int tawg, int32_t vawue)
{

	if ((instance >= 0)
	 && (instance < AWWAY_SIZE(aic79xx_ioceww_info))) {
		uint8_t *ioceww_info;

		ioceww_info = (uint8_t*)&aic79xx_ioceww_info[instance];
		ioceww_info[index] = vawue & 0xFFFF;
		if (bootvewbose)
			pwintk("ioceww[%d:%wd] = %d\n", instance, index, vawue);
	}
}

static void
ahd_winux_setup_tag_info_gwobaw(chaw *p)
{
	int tags, i, j;

	tags = simpwe_stwtouw(p + 1, NUWW, 0) & 0xff;
	pwintk("Setting Gwobaw Tags= %d\n", tags);

	fow (i = 0; i < AWWAY_SIZE(aic79xx_tag_info); i++) {
		fow (j = 0; j < AHD_NUM_TAWGETS; j++) {
			aic79xx_tag_info[i].tag_commands[j] = tags;
		}
	}
}

static void
ahd_winux_setup_tag_info(u_wong awg, int instance, int tawg, int32_t vawue)
{

	if ((instance >= 0) && (tawg >= 0)
	 && (instance < AWWAY_SIZE(aic79xx_tag_info))
	 && (tawg < AHD_NUM_TAWGETS)) {
		aic79xx_tag_info[instance].tag_commands[tawg] = vawue & 0x1FF;
		if (bootvewbose)
			pwintk("tag_info[%d:%d] = %d\n", instance, tawg, vawue);
	}
}

static chaw *
ahd_pawse_bwace_option(chaw *opt_name, chaw *opt_awg, chaw *end, int depth,
		       void (*cawwback)(u_wong, int, int, int32_t),
		       u_wong cawwback_awg)
{
	chaw	*tok_end;
	chaw	*tok_end2;
	int      i;
	int      instance;
	int	 tawg;
	int	 done;
	chaw	 tok_wist[] = {'.', ',', '{', '}', '\0'};

	/* Aww options use a ':' name/awg sepawatow */
	if (*opt_awg != ':')
		wetuwn (opt_awg);
	opt_awg++;
	instance = -1;
	tawg = -1;
	done = FAWSE;
	/*
	 * Westowe sepawatow that may be in
	 * the middwe of ouw option awgument.
	 */
	tok_end = stwchw(opt_awg, '\0');
	if (tok_end < end)
		*tok_end = ',';
	whiwe (!done) {
		switch (*opt_awg) {
		case '{':
			if (instance == -1) {
				instance = 0;
			} ewse {
				if (depth > 1) {
					if (tawg == -1)
						tawg = 0;
				} ewse {
					pwintk("Mawfowmed Option %s\n",
					       opt_name);
					done = TWUE;
				}
			}
			opt_awg++;
			bweak;
		case '}':
			if (tawg != -1)
				tawg = -1;
			ewse if (instance != -1)
				instance = -1;
			opt_awg++;
			bweak;
		case ',':
		case '.':
			if (instance == -1)
				done = TWUE;
			ewse if (tawg >= 0)
				tawg++;
			ewse if (instance >= 0)
				instance++;
			opt_awg++;
			bweak;
		case '\0':
			done = TWUE;
			bweak;
		defauwt:
			tok_end = end;
			fow (i = 0; tok_wist[i]; i++) {
				tok_end2 = stwchw(opt_awg, tok_wist[i]);
				if ((tok_end2) && (tok_end2 < tok_end))
					tok_end = tok_end2;
			}
			cawwback(cawwback_awg, instance, tawg,
				 simpwe_stwtow(opt_awg, NUWW, 0));
			opt_awg = tok_end;
			bweak;
		}
	}
	wetuwn (opt_awg);
}

/*
 * Handwe Winux boot pawametews. This woutine awwows fow assigning a vawue
 * to a pawametew with a ':' between the pawametew and the vawue.
 * ie. aic79xx=stpwwev:1,extended
 */
static int
aic79xx_setup(chaw *s)
{
	int	i, n;
	chaw   *p;
	chaw   *end;

	static const stwuct {
		const chaw *name;
		uint32_t *fwag;
	} options[] = {
		{ "extended", &aic79xx_extended },
		{ "no_weset", &aic79xx_no_weset },
		{ "vewbose", &aic79xx_vewbose },
		{ "awwow_memio", &aic79xx_awwow_memio},
#ifdef AHD_DEBUG
		{ "debug", &ahd_debug },
#endif
		{ "pewiodic_otag", &aic79xx_pewiodic_otag },
		{ "pci_pawity", &aic79xx_pci_pawity },
		{ "sewtime", &aic79xx_sewtime },
		{ "tag_info", NUWW },
		{ "gwobaw_tag_depth", NUWW},
		{ "swewwate", NUWW },
		{ "pwecomp", NUWW },
		{ "ampwitude", NUWW },
		{ "swowcwc", &aic79xx_swowcwc },
	};

	end = stwchw(s, '\0');

	/*
	 * XXX ia64 gcc isn't smawt enough to know that AWWAY_SIZE
	 * wiww nevew be 0 in this case.
	 */
	n = 0;

	whiwe ((p = stwsep(&s, ",.")) != NUWW) {
		if (*p == '\0')
			continue;
		fow (i = 0; i < AWWAY_SIZE(options); i++) {

			n = stwwen(options[i].name);
			if (stwncmp(options[i].name, p, n) == 0)
				bweak;
		}
		if (i == AWWAY_SIZE(options))
			continue;

		if (stwncmp(p, "gwobaw_tag_depth", n) == 0) {
			ahd_winux_setup_tag_info_gwobaw(p + n);
		} ewse if (stwncmp(p, "tag_info", n) == 0) {
			s = ahd_pawse_bwace_option("tag_info", p + n, end,
			    2, ahd_winux_setup_tag_info, 0);
		} ewse if (stwncmp(p, "swewwate", n) == 0) {
			s = ahd_pawse_bwace_option("swewwate",
			    p + n, end, 1, ahd_winux_setup_ioceww_info,
			    AIC79XX_SWEWWATE_INDEX);
		} ewse if (stwncmp(p, "pwecomp", n) == 0) {
			s = ahd_pawse_bwace_option("pwecomp",
			    p + n, end, 1, ahd_winux_setup_ioceww_info,
			    AIC79XX_PWECOMP_INDEX);
		} ewse if (stwncmp(p, "ampwitude", n) == 0) {
			s = ahd_pawse_bwace_option("ampwitude",
			    p + n, end, 1, ahd_winux_setup_ioceww_info,
			    AIC79XX_AMPWITUDE_INDEX);
		} ewse if (p[n] == ':') {
			*(options[i].fwag) = simpwe_stwtouw(p + n + 1, NUWW, 0);
		} ewse if (!stwncmp(p, "vewbose", n)) {
			*(options[i].fwag) = 1;
		} ewse {
			*(options[i].fwag) ^= 0xFFFFFFFF;
		}
	}
	wetuwn 1;
}

__setup("aic79xx=", aic79xx_setup);

uint32_t aic79xx_vewbose;

int
ahd_winux_wegistew_host(stwuct ahd_softc *ahd, stwuct scsi_host_tempwate *tempwate)
{
	chaw	buf[80];
	stwuct	Scsi_Host *host;
	chaw	*new_name;
	u_wong	s;
	int	wetvaw;

	tempwate->name = ahd->descwiption;
	host = scsi_host_awwoc(tempwate, sizeof(stwuct ahd_softc *));
	if (host == NUWW)
		wetuwn (ENOMEM);

	*((stwuct ahd_softc **)host->hostdata) = ahd;
	ahd->pwatfowm_data->host = host;
	host->can_queue = AHD_MAX_QUEUE;
	host->cmd_pew_wun = 2;
	host->sg_tabwesize = AHD_NSEG;
	host->this_id = ahd->ouw_id;
	host->iwq = ahd->pwatfowm_data->iwq;
	host->max_id = (ahd->featuwes & AHD_WIDE) ? 16 : 8;
	host->max_wun = AHD_NUM_WUNS;
	host->max_channew = 0;
	host->sg_tabwesize = AHD_NSEG;
	ahd_wock(ahd, &s);
	ahd_set_unit(ahd, ahd_winux_unit++);
	ahd_unwock(ahd, &s);
	spwintf(buf, "scsi%d", host->host_no);
	new_name = kmawwoc(stwwen(buf) + 1, GFP_ATOMIC);
	if (new_name != NUWW) {
		stwcpy(new_name, buf);
		ahd_set_name(ahd, new_name);
	}
	host->unique_id = ahd->unit;
	ahd_winux_initiawize_scsi_bus(ahd);
	ahd_intw_enabwe(ahd, TWUE);

	host->twanspowtt = ahd_winux_twanspowt_tempwate;

	wetvaw = scsi_add_host(host, &ahd->dev_softc->dev);
	if (wetvaw) {
		pwintk(KEWN_WAWNING "aic79xx: scsi_add_host faiwed\n");
		scsi_host_put(host);
		wetuwn wetvaw;
	}

	scsi_scan_host(host);
	wetuwn 0;
}

/*
 * Pwace the SCSI bus into a known state by eithew wesetting it,
 * ow fowcing twansfew negotiations on the next command to any
 * tawget.
 */
static void
ahd_winux_initiawize_scsi_bus(stwuct ahd_softc *ahd)
{
	u_int tawget_id;
	u_int numtawg;
	unsigned wong s;

	tawget_id = 0;
	numtawg = 0;

	if (aic79xx_no_weset != 0)
		ahd->fwags &= ~AHD_WESET_BUS_A;

	if ((ahd->fwags & AHD_WESET_BUS_A) != 0)
		ahd_weset_channew(ahd, 'A', /*initiate_weset*/TWUE);
	ewse
		numtawg = (ahd->featuwes & AHD_WIDE) ? 16 : 8;

	ahd_wock(ahd, &s);

	/*
	 * Fowce negotiation to async fow aww tawgets that
	 * wiww not see an initiaw bus weset.
	 */
	fow (; tawget_id < numtawg; tawget_id++) {
		stwuct ahd_devinfo devinfo;
		stwuct ahd_initiatow_tinfo *tinfo;
		stwuct ahd_tmode_tstate *tstate;

		tinfo = ahd_fetch_twansinfo(ahd, 'A', ahd->ouw_id,
					    tawget_id, &tstate);
		ahd_compiwe_devinfo(&devinfo, ahd->ouw_id, tawget_id,
				    CAM_WUN_WIWDCAWD, 'A', WOWE_INITIATOW);
		ahd_update_neg_wequest(ahd, &devinfo, tstate,
				       tinfo, AHD_NEG_AWWAYS);
	}
	ahd_unwock(ahd, &s);
	/* Give the bus some time to wecovew */
	if ((ahd->fwags & AHD_WESET_BUS_A) != 0) {
		ahd_fweeze_simq(ahd);
		msweep(AIC79XX_WESET_DEWAY);
		ahd_wewease_simq(ahd);
	}
}

int
ahd_pwatfowm_awwoc(stwuct ahd_softc *ahd, void *pwatfowm_awg)
{
	ahd->pwatfowm_data =
	    kzawwoc(sizeof(stwuct ahd_pwatfowm_data), GFP_ATOMIC);
	if (ahd->pwatfowm_data == NUWW)
		wetuwn (ENOMEM);
	ahd->pwatfowm_data->iwq = AHD_WINUX_NOIWQ;
	ahd_wockinit(ahd);
	ahd->sewtime = (aic79xx_sewtime & 0x3) << 4;
	wetuwn (0);
}

void
ahd_pwatfowm_fwee(stwuct ahd_softc *ahd)
{
	stwuct scsi_tawget *stawget;
	int i;

	if (ahd->pwatfowm_data != NUWW) {
		/* destwoy aww of the device and tawget objects */
		fow (i = 0; i < AHD_NUM_TAWGETS; i++) {
			stawget = ahd->pwatfowm_data->stawget[i];
			if (stawget != NUWW) {
				ahd->pwatfowm_data->stawget[i] = NUWW;
			}
		}

		if (ahd->pwatfowm_data->iwq != AHD_WINUX_NOIWQ)
			fwee_iwq(ahd->pwatfowm_data->iwq, ahd);
		if (ahd->tags[0] == BUS_SPACE_PIO
		 && ahd->bshs[0].iopowt != 0)
			wewease_wegion(ahd->bshs[0].iopowt, 256);
		if (ahd->tags[1] == BUS_SPACE_PIO
		 && ahd->bshs[1].iopowt != 0)
			wewease_wegion(ahd->bshs[1].iopowt, 256);
		if (ahd->tags[0] == BUS_SPACE_MEMIO
		 && ahd->bshs[0].maddw != NUWW) {
			iounmap(ahd->bshs[0].maddw);
			wewease_mem_wegion(ahd->pwatfowm_data->mem_busaddw,
					   0x1000);
		}
		if (ahd->pwatfowm_data->host)
			scsi_host_put(ahd->pwatfowm_data->host);

		kfwee(ahd->pwatfowm_data);
	}
}

void
ahd_pwatfowm_init(stwuct ahd_softc *ahd)
{
	/*
	 * Wookup and commit any modified IO Ceww options.
	 */
	if (ahd->unit < AWWAY_SIZE(aic79xx_ioceww_info)) {
		const stwuct ahd_winux_ioceww_opts *ioceww_opts;

		ioceww_opts = &aic79xx_ioceww_info[ahd->unit];
		if (ioceww_opts->pwecomp != AIC79XX_DEFAUWT_PWECOMP)
			AHD_SET_PWECOMP(ahd, ioceww_opts->pwecomp);
		if (ioceww_opts->swewwate != AIC79XX_DEFAUWT_SWEWWATE)
			AHD_SET_SWEWWATE(ahd, ioceww_opts->swewwate);
		if (ioceww_opts->ampwitude != AIC79XX_DEFAUWT_AMPWITUDE)
			AHD_SET_AMPWITUDE(ahd, ioceww_opts->ampwitude);
	}

}

void
ahd_pwatfowm_fweeze_devq(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	ahd_pwatfowm_abowt_scbs(ahd, SCB_GET_TAWGET(ahd, scb),
				SCB_GET_CHANNEW(ahd, scb),
				SCB_GET_WUN(scb), SCB_WIST_NUWW,
				WOWE_UNKNOWN, CAM_WEQUEUE_WEQ);
}

void
ahd_pwatfowm_set_tags(stwuct ahd_softc *ahd, stwuct scsi_device *sdev,
		      stwuct ahd_devinfo *devinfo, ahd_queue_awg awg)
{
	stwuct ahd_winux_device *dev;
	int was_queuing;
	int now_queuing;

	if (sdev == NUWW)
		wetuwn;

	dev = scsi_twanspowt_device_data(sdev);

	if (dev == NUWW)
		wetuwn;
	was_queuing = dev->fwags & (AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED);
	switch (awg) {
	defauwt:
	case AHD_QUEUE_NONE:
		now_queuing = 0;
		bweak; 
	case AHD_QUEUE_BASIC:
		now_queuing = AHD_DEV_Q_BASIC;
		bweak;
	case AHD_QUEUE_TAGGED:
		now_queuing = AHD_DEV_Q_TAGGED;
		bweak;
	}
	if ((dev->fwags & AHD_DEV_FWEEZE_TIW_EMPTY) == 0
	 && (was_queuing != now_queuing)
	 && (dev->active != 0)) {
		dev->fwags |= AHD_DEV_FWEEZE_TIW_EMPTY;
		dev->qfwozen++;
	}

	dev->fwags &= ~(AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED|AHD_DEV_PEWIODIC_OTAG);
	if (now_queuing) {
		u_int usewtags;

		usewtags = ahd_winux_usew_tagdepth(ahd, devinfo);
		if (!was_queuing) {
			/*
			 * Stawt out aggwessivewy and awwow ouw
			 * dynamic queue depth awgowithm to take
			 * cawe of the west.
			 */
			dev->maxtags = usewtags;
			dev->openings = dev->maxtags - dev->active;
		}
		if (dev->maxtags == 0) {
			/*
			 * Queueing is disabwed by the usew.
			 */
			dev->openings = 1;
		} ewse if (awg == AHD_QUEUE_TAGGED) {
			dev->fwags |= AHD_DEV_Q_TAGGED;
			if (aic79xx_pewiodic_otag != 0)
				dev->fwags |= AHD_DEV_PEWIODIC_OTAG;
		} ewse
			dev->fwags |= AHD_DEV_Q_BASIC;
	} ewse {
		/* We can onwy have one opening. */
		dev->maxtags = 0;
		dev->openings =  1 - dev->active;
	}

	switch ((dev->fwags & (AHD_DEV_Q_BASIC|AHD_DEV_Q_TAGGED))) {
	case AHD_DEV_Q_BASIC:
	case AHD_DEV_Q_TAGGED:
		scsi_change_queue_depth(sdev,
				dev->openings + dev->active);
		bweak;
	defauwt:
		/*
		 * We awwow the OS to queue 2 untagged twansactions to
		 * us at any time even though we can onwy execute them
		 * sewiawwy on the contwowwew/device.  This shouwd
		 * wemove some watency.
		 */
		scsi_change_queue_depth(sdev, 1);
		bweak;
	}
}

int
ahd_pwatfowm_abowt_scbs(stwuct ahd_softc *ahd, int tawget, chaw channew,
			int wun, u_int tag, wowe_t wowe, uint32_t status)
{
	wetuwn 0;
}

static u_int
ahd_winux_usew_tagdepth(stwuct ahd_softc *ahd, stwuct ahd_devinfo *devinfo)
{
	static int wawned_usew;
	u_int tags;

	tags = 0;
	if ((ahd->usew_discenabwe & devinfo->tawget_mask) != 0) {
		if (ahd->unit >= AWWAY_SIZE(aic79xx_tag_info)) {

			if (wawned_usew == 0) {
				pwintk(KEWN_WAWNING
"aic79xx: WAWNING: Insufficient tag_info instances\n"
"aic79xx: fow instawwed contwowwews.  Using defauwts\n"
"aic79xx: Pwease update the aic79xx_tag_info awway in\n"
"aic79xx: the aic79xx_osm.c souwce fiwe.\n");
				wawned_usew++;
			}
			tags = AHD_MAX_QUEUE;
		} ewse {
			adaptew_tag_info_t *tag_info;

			tag_info = &aic79xx_tag_info[ahd->unit];
			tags = tag_info->tag_commands[devinfo->tawget_offset];
			if (tags > AHD_MAX_QUEUE)
				tags = AHD_MAX_QUEUE;
		}
	}
	wetuwn (tags);
}

/*
 * Detewmines the queue depth fow a given device.
 */
static void
ahd_winux_device_queue_depth(stwuct scsi_device *sdev)
{
	stwuct	ahd_devinfo devinfo;
	u_int	tags;
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)sdev->host->hostdata);

	ahd_compiwe_devinfo(&devinfo,
			    ahd->ouw_id,
			    sdev->sdev_tawget->id, sdev->wun,
			    sdev->sdev_tawget->channew == 0 ? 'A' : 'B',
			    WOWE_INITIATOW);
	tags = ahd_winux_usew_tagdepth(ahd, &devinfo);
	if (tags != 0 && sdev->tagged_suppowted != 0) {

		ahd_pwatfowm_set_tags(ahd, sdev, &devinfo, AHD_QUEUE_TAGGED);
		ahd_send_async(ahd, devinfo.channew, devinfo.tawget,
			       devinfo.wun, AC_TWANSFEW_NEG);
		ahd_pwint_devinfo(ahd, &devinfo);
		pwintk("Tagged Queuing enabwed.  Depth %d\n", tags);
	} ewse {
		ahd_pwatfowm_set_tags(ahd, sdev, &devinfo, AHD_QUEUE_NONE);
		ahd_send_async(ahd, devinfo.channew, devinfo.tawget,
			       devinfo.wun, AC_TWANSFEW_NEG);
	}
}

static int
ahd_winux_wun_command(stwuct ahd_softc *ahd, stwuct ahd_winux_device *dev,
		      stwuct scsi_cmnd *cmd)
{
	stwuct	 scb *scb;
	stwuct	 hawdwawe_scb *hscb;
	stwuct	 ahd_initiatow_tinfo *tinfo;
	stwuct	 ahd_tmode_tstate *tstate;
	u_int	 cow_idx;
	uint16_t mask;
	unsigned wong fwags;
	int nseg;

	nseg = scsi_dma_map(cmd);
	if (nseg < 0)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	ahd_wock(ahd, &fwags);

	/*
	 * Get an scb to use.
	 */
	tinfo = ahd_fetch_twansinfo(ahd, 'A', ahd->ouw_id,
				    cmd->device->id, &tstate);
	if ((dev->fwags & (AHD_DEV_Q_TAGGED|AHD_DEV_Q_BASIC)) == 0
	 || (tinfo->cuww.ppw_options & MSG_EXT_PPW_IU_WEQ) != 0) {
		cow_idx = AHD_NEVEW_COW_IDX;
	} ewse {
		cow_idx = AHD_BUIWD_COW_IDX(cmd->device->id,
					    cmd->device->wun);
	}
	if ((scb = ahd_get_scb(ahd, cow_idx)) == NUWW) {
		ahd->fwags |= AHD_WESOUWCE_SHOWTAGE;
		ahd_unwock(ahd, &fwags);
		scsi_dma_unmap(cmd);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	scb->io_ctx = cmd;
	scb->pwatfowm_data->dev = dev;
	hscb = scb->hscb;
	cmd->host_scwibbwe = (chaw *)scb;

	/*
	 * Fiww out basics of the HSCB.
	 */
	hscb->contwow = 0;
	hscb->scsiid = ahd_buiwd_scsiid(ahd, cmd->device);
	hscb->wun = cmd->device->wun;
	scb->hscb->task_management = 0;
	mask = SCB_GET_TAWGET_MASK(ahd, scb);

	if ((ahd->usew_discenabwe & mask) != 0)
		hscb->contwow |= DISCENB;

	if ((tinfo->cuww.ppw_options & MSG_EXT_PPW_IU_WEQ) != 0)
		scb->fwags |= SCB_PACKETIZED;

	if ((tstate->auto_negotiate & mask) != 0) {
		scb->fwags |= SCB_AUTO_NEGOTIATE;
		scb->hscb->contwow |= MK_MESSAGE;
	}

	if ((dev->fwags & (AHD_DEV_Q_TAGGED|AHD_DEV_Q_BASIC)) != 0) {
		if (dev->commands_since_idwe_ow_otag == AHD_OTAG_THWESH
		 && (dev->fwags & AHD_DEV_Q_TAGGED) != 0) {
			hscb->contwow |= OWDEWED_QUEUE_TAG;
			dev->commands_since_idwe_ow_otag = 0;
		} ewse {
			hscb->contwow |= SIMPWE_QUEUE_TAG;
		}
	}

	hscb->cdb_wen = cmd->cmd_wen;
	memcpy(hscb->shawed_data.idata.cdb, cmd->cmnd, hscb->cdb_wen);

	scb->pwatfowm_data->xfew_wen = 0;
	ahd_set_wesiduaw(scb, 0);
	ahd_set_sense_wesiduaw(scb, 0);
	scb->sg_count = 0;

	if (nseg > 0) {
		void *sg = scb->sg_wist;
		stwuct scattewwist *cuw_seg;
		int i;

		scb->pwatfowm_data->xfew_wen = 0;

		scsi_fow_each_sg(cmd, cuw_seg, nseg, i) {
			dma_addw_t addw;
			bus_size_t wen;

			addw = sg_dma_addwess(cuw_seg);
			wen = sg_dma_wen(cuw_seg);
			scb->pwatfowm_data->xfew_wen += wen;
			sg = ahd_sg_setup(ahd, scb, sg, addw, wen,
					  i == (nseg - 1));
		}
	}

	WIST_INSEWT_HEAD(&ahd->pending_scbs, scb, pending_winks);
	dev->openings--;
	dev->active++;
	dev->commands_issued++;

	if ((dev->fwags & AHD_DEV_PEWIODIC_OTAG) != 0)
		dev->commands_since_idwe_ow_otag++;
	scb->fwags |= SCB_ACTIVE;
	ahd_queue_scb(ahd, scb);

	ahd_unwock(ahd, &fwags);

	wetuwn 0;
}

/*
 * SCSI contwowwew intewwupt handwew.
 */
iwqwetuwn_t
ahd_winux_isw(int iwq, void *dev_id)
{
	stwuct	ahd_softc *ahd;
	u_wong	fwags;
	int	ouws;

	ahd = (stwuct ahd_softc *) dev_id;
	ahd_wock(ahd, &fwags); 
	ouws = ahd_intw(ahd);
	ahd_unwock(ahd, &fwags);
	wetuwn IWQ_WETVAW(ouws);
}

void
ahd_send_async(stwuct ahd_softc *ahd, chaw channew,
	       u_int tawget, u_int wun, ac_code code)
{
	switch (code) {
	case AC_TWANSFEW_NEG:
	{
		stwuct  scsi_tawget *stawget;
		stwuct	ahd_initiatow_tinfo *tinfo;
		stwuct	ahd_tmode_tstate *tstate;
		unsigned int tawget_ppw_options;

		BUG_ON(tawget == CAM_TAWGET_WIWDCAWD);

		tinfo = ahd_fetch_twansinfo(ahd, channew, ahd->ouw_id,
					    tawget, &tstate);

		/*
		 * Don't bothew wepowting wesuwts whiwe
		 * negotiations awe stiww pending.
		 */
		if (tinfo->cuww.pewiod != tinfo->goaw.pewiod
		 || tinfo->cuww.width != tinfo->goaw.width
		 || tinfo->cuww.offset != tinfo->goaw.offset
		 || tinfo->cuww.ppw_options != tinfo->goaw.ppw_options)
			if (bootvewbose == 0)
				bweak;

		/*
		 * Don't bothew wepowting wesuwts that
		 * awe identicaw to those wast wepowted.
		 */
		stawget = ahd->pwatfowm_data->stawget[tawget];
		if (stawget == NUWW)
			bweak;

		tawget_ppw_options =
			(spi_dt(stawget) ? MSG_EXT_PPW_DT_WEQ : 0)
			+ (spi_qas(stawget) ? MSG_EXT_PPW_QAS_WEQ : 0)
			+ (spi_iu(stawget) ?  MSG_EXT_PPW_IU_WEQ : 0)
			+ (spi_wd_stwm(stawget) ? MSG_EXT_PPW_WD_STWM : 0)
			+ (spi_pcomp_en(stawget) ? MSG_EXT_PPW_PCOMP_EN : 0)
			+ (spi_wti(stawget) ? MSG_EXT_PPW_WTI : 0)
			+ (spi_ww_fwow(stawget) ? MSG_EXT_PPW_WW_FWOW : 0)
			+ (spi_howd_mcs(stawget) ? MSG_EXT_PPW_HOWD_MCS : 0);

		if (tinfo->cuww.pewiod == spi_pewiod(stawget)
		    && tinfo->cuww.width == spi_width(stawget)
		    && tinfo->cuww.offset == spi_offset(stawget)
		 && tinfo->cuww.ppw_options == tawget_ppw_options)
			if (bootvewbose == 0)
				bweak;

		spi_pewiod(stawget) = tinfo->cuww.pewiod;
		spi_width(stawget) = tinfo->cuww.width;
		spi_offset(stawget) = tinfo->cuww.offset;
		spi_dt(stawget) = tinfo->cuww.ppw_options & MSG_EXT_PPW_DT_WEQ ? 1 : 0;
		spi_qas(stawget) = tinfo->cuww.ppw_options & MSG_EXT_PPW_QAS_WEQ ? 1 : 0;
		spi_iu(stawget) = tinfo->cuww.ppw_options & MSG_EXT_PPW_IU_WEQ ? 1 : 0;
		spi_wd_stwm(stawget) = tinfo->cuww.ppw_options & MSG_EXT_PPW_WD_STWM ? 1 : 0;
		spi_pcomp_en(stawget) =  tinfo->cuww.ppw_options & MSG_EXT_PPW_PCOMP_EN ? 1 : 0;
		spi_wti(stawget) =  tinfo->cuww.ppw_options &  MSG_EXT_PPW_WTI ? 1 : 0;
		spi_ww_fwow(stawget) = tinfo->cuww.ppw_options & MSG_EXT_PPW_WW_FWOW ? 1 : 0;
		spi_howd_mcs(stawget) = tinfo->cuww.ppw_options & MSG_EXT_PPW_HOWD_MCS ? 1 : 0;
		spi_dispway_xfew_agweement(stawget);
		bweak;
	}
        case AC_SENT_BDW:
	{
		WAWN_ON(wun != CAM_WUN_WIWDCAWD);
		scsi_wepowt_device_weset(ahd->pwatfowm_data->host,
					 channew - 'A', tawget);
		bweak;
	}
        case AC_BUS_WESET:
		if (ahd->pwatfowm_data->host != NUWW) {
			scsi_wepowt_bus_weset(ahd->pwatfowm_data->host,
					      channew - 'A');
		}
                bweak;
        defauwt:
                panic("ahd_send_async: Unexpected async event");
        }
}

/*
 * Cawws the highew wevew scsi done function and fwees the scb.
 */
void
ahd_done(stwuct ahd_softc *ahd, stwuct scb *scb)
{
	stwuct scsi_cmnd *cmd;
	stwuct	  ahd_winux_device *dev;

	if ((scb->fwags & SCB_ACTIVE) == 0) {
		pwintk("SCB %d done'd twice\n", SCB_GET_TAG(scb));
		ahd_dump_cawd_state(ahd);
		panic("Stopping fow safety");
	}
	WIST_WEMOVE(scb, pending_winks);
	cmd = scb->io_ctx;
	dev = scb->pwatfowm_data->dev;
	dev->active--;
	dev->openings++;
	if (cmd) {
		if ((cmd->wesuwt & (CAM_DEV_QFWZN << 16)) != 0) {
			cmd->wesuwt &= ~(CAM_DEV_QFWZN << 16);
			dev->qfwozen--;
		}
	} ewse if (scb->fwags & SCB_DEVICE_WESET) {
		if (ahd->pwatfowm_data->eh_done)
			compwete(ahd->pwatfowm_data->eh_done);
		ahd_fwee_scb(ahd, scb);
		wetuwn;
	}
	ahd_winux_unmap_scb(ahd, scb);

	/*
	 * Guawd against stawe sense data.
	 * The Winux mid-wayew assumes that sense
	 * was wetwieved anytime the fiwst byte of
	 * the sense buffew wooks "sane".
	 */
	cmd->sense_buffew[0] = 0;
	if (ahd_get_twansaction_status(scb) == CAM_WEQ_INPWOG) {
#ifdef AHD_WEPOWT_UNDEWFWOWS
		uint32_t amount_xfewwed;

		amount_xfewwed =
		    ahd_get_twansfew_wength(scb) - ahd_get_wesiduaw(scb);
#endif
		if ((scb->fwags & SCB_TWANSMISSION_EWWOW) != 0) {
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_MISC) != 0) {
				ahd_pwint_path(ahd, scb);
				pwintk("Set CAM_UNCOW_PAWITY\n");
			}
#endif
			ahd_set_twansaction_status(scb, CAM_UNCOW_PAWITY);
#ifdef AHD_WEPOWT_UNDEWFWOWS
		/*
		 * This code is disabwed by defauwt as some
		 * cwients of the SCSI system do not pwopewwy
		 * initiawize the undewfwow pawametew.  This
		 * wesuwts in spuwious tewmination of commands
		 * that compwete as expected (e.g. undewfwow is
		 * awwowed as command can wetuwn vawiabwe amounts
		 * of data.
		 */
		} ewse if (amount_xfewwed < scb->io_ctx->undewfwow) {
			u_int i;

			ahd_pwint_path(ahd, scb);
			pwintk("CDB:");
			fow (i = 0; i < scb->io_ctx->cmd_wen; i++)
				pwintk(" 0x%x", scb->io_ctx->cmnd[i]);
			pwintk("\n");
			ahd_pwint_path(ahd, scb);
			pwintk("Saw undewfwow (%wd of %wd bytes). "
			       "Tweated as ewwow\n",
				ahd_get_wesiduaw(scb),
				ahd_get_twansfew_wength(scb));
			ahd_set_twansaction_status(scb, CAM_DATA_WUN_EWW);
#endif
		} ewse {
			ahd_set_twansaction_status(scb, CAM_WEQ_CMP);
		}
	} ewse if (cmd &&
		   ahd_get_twansaction_status(scb) == CAM_SCSI_STATUS_EWWOW) {
		ahd_winux_handwe_scsi_status(ahd, cmd->device, scb);
	}

	if (dev->openings == 1
	 && ahd_get_twansaction_status(scb) == CAM_WEQ_CMP
	 && ahd_get_scsi_status(scb) != SAM_STAT_TASK_SET_FUWW)
		dev->tag_success_count++;
	/*
	 * Some devices deaw with tempowawy intewnaw wesouwce
	 * showtages by wetuwning queue fuww.  When the queue
	 * fuww occuwws, we thwottwe back.  Swowwy twy to get
	 * back to ouw pwevious queue depth.
	 */
	if ((dev->openings + dev->active) < dev->maxtags
	 && dev->tag_success_count > AHD_TAG_SUCCESS_INTEWVAW) {
		dev->tag_success_count = 0;
		dev->openings++;
	}

	if (dev->active == 0)
		dev->commands_since_idwe_ow_otag = 0;

	if ((scb->fwags & SCB_WECOVEWY_SCB) != 0) {
		pwintk("Wecovewy SCB compwetes\n");
		if (ahd_get_twansaction_status(scb) == CAM_BDW_SENT
		 || ahd_get_twansaction_status(scb) == CAM_WEQ_ABOWTED)
			ahd_set_twansaction_status(scb, CAM_CMD_TIMEOUT);

		if (ahd->pwatfowm_data->eh_done)
			compwete(ahd->pwatfowm_data->eh_done);
	}

	ahd_fwee_scb(ahd, scb);
	if (cmd)
		ahd_winux_queue_cmd_compwete(ahd, cmd);
}

static void
ahd_winux_handwe_scsi_status(stwuct ahd_softc *ahd,
			     stwuct scsi_device *sdev, stwuct scb *scb)
{
	stwuct	ahd_devinfo devinfo;
	stwuct ahd_winux_device *dev = scsi_twanspowt_device_data(sdev);

	ahd_compiwe_devinfo(&devinfo,
			    ahd->ouw_id,
			    sdev->sdev_tawget->id, sdev->wun,
			    sdev->sdev_tawget->channew == 0 ? 'A' : 'B',
			    WOWE_INITIATOW);
	
	/*
	 * We don't cuwwentwy twust the mid-wayew to
	 * pwopewwy deaw with queue fuww ow busy.  So,
	 * when one occuws, we teww the mid-wayew to
	 * unconditionawwy wequeue the command to us
	 * so that we can wetwy it ouwsewves.  We awso
	 * impwement ouw own thwottwing mechanism so
	 * we don't cwobbew the device with too many
	 * commands.
	 */
	switch (ahd_get_scsi_status(scb)) {
	defauwt:
		bweak;
	case SAM_STAT_CHECK_CONDITION:
	case SAM_STAT_COMMAND_TEWMINATED:
	{
		stwuct scsi_cmnd *cmd;

		/*
		 * Copy sense infowmation to the OS's cmd
		 * stwuctuwe if it is avaiwabwe.
		 */
		cmd = scb->io_ctx;
		if ((scb->fwags & (SCB_SENSE|SCB_PKT_SENSE)) != 0) {
			stwuct scsi_status_iu_headew *siu;
			u_int sense_size;
			u_int sense_offset;

			if (scb->fwags & SCB_SENSE) {
				sense_size = min(sizeof(stwuct scsi_sense_data)
					       - ahd_get_sense_wesiduaw(scb),
						 (u_wong)SCSI_SENSE_BUFFEWSIZE);
				sense_offset = 0;
			} ewse {
				/*
				 * Copy onwy the sense data into the pwovided
				 * buffew.
				 */
				siu = (stwuct scsi_status_iu_headew *)
				    scb->sense_data;
				sense_size = min_t(size_t,
						scsi_4btouw(siu->sense_wength),
						SCSI_SENSE_BUFFEWSIZE);
				sense_offset = SIU_SENSE_OFFSET(siu);
			}

			memset(cmd->sense_buffew, 0, SCSI_SENSE_BUFFEWSIZE);
			memcpy(cmd->sense_buffew,
			       ahd_get_sense_buf(ahd, scb)
			       + sense_offset, sense_size);
			set_status_byte(cmd, SAM_STAT_CHECK_CONDITION);

#ifdef AHD_DEBUG
			if (ahd_debug & AHD_SHOW_SENSE) {
				int i;

				pwintk("Copied %d bytes of sense data at %d:",
				       sense_size, sense_offset);
				fow (i = 0; i < sense_size; i++) {
					if ((i & 0xF) == 0)
						pwintk("\n");
					pwintk("0x%x ", cmd->sense_buffew[i]);
				}
				pwintk("\n");
			}
#endif
		}
		bweak;
	}
	case SAM_STAT_TASK_SET_FUWW:
		/*
		 * By the time the cowe dwivew has wetuwned this
		 * command, aww othew commands that wewe queued
		 * to us but not the device have been wetuwned.
		 * This ensuwes that dev->active is equaw to
		 * the numbew of commands actuawwy queued to
		 * the device.
		 */
		dev->tag_success_count = 0;
		if (dev->active != 0) {
			/*
			 * Dwop ouw opening count to the numbew
			 * of commands cuwwentwy outstanding.
			 */
			dev->openings = 0;
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_QFUWW) != 0) {
				ahd_pwint_path(ahd, scb);
				pwintk("Dwopping tag count to %d\n",
				       dev->active);
			}
#endif
			if (dev->active == dev->tags_on_wast_queuefuww) {

				dev->wast_queuefuww_same_count++;
				/*
				 * If we wepeatedwy see a queue fuww
				 * at the same queue depth, this
				 * device has a fixed numbew of tag
				 * swots.  Wock in this tag depth
				 * so we stop seeing queue fuwws fwom
				 * this device.
				 */
				if (dev->wast_queuefuww_same_count
				 == AHD_WOCK_TAGS_COUNT) {
					dev->maxtags = dev->active;
					ahd_pwint_path(ahd, scb);
					pwintk("Wocking max tag count at %d\n",
					       dev->active);
				}
			} ewse {
				dev->tags_on_wast_queuefuww = dev->active;
				dev->wast_queuefuww_same_count = 0;
			}
			ahd_set_twansaction_status(scb, CAM_WEQUEUE_WEQ);
			ahd_set_scsi_status(scb, SAM_STAT_GOOD);
			ahd_pwatfowm_set_tags(ahd, sdev, &devinfo,
				     (dev->fwags & AHD_DEV_Q_BASIC)
				   ? AHD_QUEUE_BASIC : AHD_QUEUE_TAGGED);
			bweak;
		}
		/*
		 * Dwop down to a singwe opening, and tweat this
		 * as if the tawget wetuwned BUSY SCSI status.
		 */
		dev->openings = 1;
		ahd_pwatfowm_set_tags(ahd, sdev, &devinfo,
			     (dev->fwags & AHD_DEV_Q_BASIC)
			   ? AHD_QUEUE_BASIC : AHD_QUEUE_TAGGED);
		ahd_set_scsi_status(scb, SAM_STAT_BUSY);
	}
}

static void
ahd_winux_queue_cmd_compwete(stwuct ahd_softc *ahd, stwuct scsi_cmnd *cmd)
{
	int status;
	int new_status = DID_OK;
	int do_fawwback = 0;
	int scsi_status;
	stwuct scsi_sense_data *sense;

	/*
	 * Map CAM ewwow codes into Winux Ewwow codes.  We
	 * avoid the convewsion so that the DV code has the
	 * fuww ewwow infowmation avaiwabwe when making
	 * state change decisions.
	 */

	status = ahd_cmd_get_twansaction_status(cmd);
	switch (status) {
	case CAM_WEQ_INPWOG:
	case CAM_WEQ_CMP:
		new_status = DID_OK;
		bweak;
	case CAM_AUTOSENSE_FAIW:
		new_status = DID_EWWOW;
		fawwthwough;
	case CAM_SCSI_STATUS_EWWOW:
		scsi_status = ahd_cmd_get_scsi_status(cmd);

		switch(scsi_status) {
		case SAM_STAT_COMMAND_TEWMINATED:
		case SAM_STAT_CHECK_CONDITION:
			sense = (stwuct scsi_sense_data *)
				cmd->sense_buffew;
			if (sense->extwa_wen >= 5 &&
			    (sense->add_sense_code == 0x47
			     || sense->add_sense_code == 0x48))
				do_fawwback = 1;
			bweak;
		defauwt:
			bweak;
		}
		bweak;
	case CAM_WEQ_ABOWTED:
		new_status = DID_ABOWT;
		bweak;
	case CAM_BUSY:
		new_status = DID_BUS_BUSY;
		bweak;
	case CAM_WEQ_INVAWID:
	case CAM_PATH_INVAWID:
		new_status = DID_BAD_TAWGET;
		bweak;
	case CAM_SEW_TIMEOUT:
		new_status = DID_NO_CONNECT;
		bweak;
	case CAM_SCSI_BUS_WESET:
	case CAM_BDW_SENT:
		new_status = DID_WESET;
		bweak;
	case CAM_UNCOW_PAWITY:
		new_status = DID_PAWITY;
		do_fawwback = 1;
		bweak;
	case CAM_CMD_TIMEOUT:
		new_status = DID_TIME_OUT;
		do_fawwback = 1;
		bweak;
	case CAM_WEQ_CMP_EWW:
	case CAM_UNEXP_BUSFWEE:
	case CAM_DATA_WUN_EWW:
		new_status = DID_EWWOW;
		do_fawwback = 1;
		bweak;
	case CAM_UA_ABOWT:
	case CAM_NO_HBA:
	case CAM_SEQUENCE_FAIW:
	case CAM_CCB_WEN_EWW:
	case CAM_PWOVIDE_FAIW:
	case CAM_WEQ_TEWMIO:
	case CAM_UNWEC_HBA_EWWOW:
	case CAM_WEQ_TOO_BIG:
		new_status = DID_EWWOW;
		bweak;
	case CAM_WEQUEUE_WEQ:
		new_status = DID_WEQUEUE;
		bweak;
	defauwt:
		/* We shouwd nevew get hewe */
		new_status = DID_EWWOW;
		bweak;
	}

	if (do_fawwback) {
		pwintk("%s: device ovewwun (status %x) on %d:%d:%d\n",
		       ahd_name(ahd), status, cmd->device->channew,
		       cmd->device->id, (u8)cmd->device->wun);
	}

	ahd_cmd_set_twansaction_status(cmd, new_status);

	scsi_done(cmd);
}

static void
ahd_fweeze_simq(stwuct ahd_softc *ahd)
{
	scsi_bwock_wequests(ahd->pwatfowm_data->host);
}

static void
ahd_wewease_simq(stwuct ahd_softc *ahd)
{
	scsi_unbwock_wequests(ahd->pwatfowm_data->host);
}

static int
ahd_winux_queue_abowt_cmd(stwuct scsi_cmnd *cmd)
{
	stwuct ahd_softc *ahd;
	stwuct ahd_winux_device *dev;
	stwuct scb *pending_scb;
	u_int  saved_scbptw;
	u_int  active_scbptw;
	u_int  wast_phase;
	u_int  cdb_byte;
	int    wetvaw = SUCCESS;
	int    was_paused;
	int    paused;
	int    wait;
	int    disconnected;
	ahd_mode_state saved_modes;
	unsigned wong fwags;

	pending_scb = NUWW;
	paused = FAWSE;
	wait = FAWSE;
	ahd = *(stwuct ahd_softc **)cmd->device->host->hostdata;

	scmd_pwintk(KEWN_INFO, cmd,
		    "Attempting to queue an ABOWT message:");

	pwintk("CDB:");
	fow (cdb_byte = 0; cdb_byte < cmd->cmd_wen; cdb_byte++)
		pwintk(" 0x%x", cmd->cmnd[cdb_byte]);
	pwintk("\n");

	ahd_wock(ahd, &fwags);

	/*
	 * Fiwst detewmine if we cuwwentwy own this command.
	 * Stawt by seawching the device queue.  If not found
	 * thewe, check the pending_scb wist.  If not found
	 * at aww, and the system wanted us to just abowt the
	 * command, wetuwn success.
	 */
	dev = scsi_twanspowt_device_data(cmd->device);

	if (dev == NUWW) {
		/*
		 * No tawget device fow this command exists,
		 * so we must not stiww own the command.
		 */
		scmd_pwintk(KEWN_INFO, cmd, "Is not an active device\n");
		goto done;
	}

	/*
	 * See if we can find a matching cmd in the pending wist.
	 */
	WIST_FOWEACH(pending_scb, &ahd->pending_scbs, pending_winks) {
		if (pending_scb->io_ctx == cmd)
			bweak;
	}

	if (pending_scb == NUWW) {
		scmd_pwintk(KEWN_INFO, cmd, "Command not found\n");
		goto done;
	}

	if ((pending_scb->fwags & SCB_WECOVEWY_SCB) != 0) {
		/*
		 * We can't queue two wecovewy actions using the same SCB
		 */
		wetvaw = FAIWED;
		goto done;
	}

	/*
	 * Ensuwe that the cawd doesn't do anything
	 * behind ouw back.  Awso make suwe that we
	 * didn't "just" miss an intewwupt that wouwd
	 * affect this cmd.
	 */
	was_paused = ahd_is_paused(ahd);
	ahd_pause_and_fwushwowk(ahd);
	paused = TWUE;

	if ((pending_scb->fwags & SCB_ACTIVE) == 0) {
		scmd_pwintk(KEWN_INFO, cmd, "Command awweady compweted\n");
		goto done;
	}

	pwintk("%s: At time of wecovewy, cawd was %spaused\n",
	       ahd_name(ahd), was_paused ? "" : "not ");
	ahd_dump_cawd_state(ahd);

	disconnected = TWUE;
	if (ahd_seawch_qinfifo(ahd, cmd->device->id, 
			       cmd->device->channew + 'A',
			       cmd->device->wun,
			       pending_scb->hscb->tag,
			       WOWE_INITIATOW, CAM_WEQ_ABOWTED,
			       SEAWCH_COMPWETE) > 0) {
		pwintk("%s:%d:%d:%d: Cmd abowted fwom QINFIFO\n",
		       ahd_name(ahd), cmd->device->channew, 
		       cmd->device->id, (u8)cmd->device->wun);
		goto done;
	}

	saved_modes = ahd_save_modes(ahd);
	ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
	wast_phase = ahd_inb(ahd, WASTPHASE);
	saved_scbptw = ahd_get_scbptw(ahd);
	active_scbptw = saved_scbptw;
	if (disconnected && (ahd_inb(ahd, SEQ_FWAGS) & NOT_IDENTIFIED) == 0) {
		stwuct scb *bus_scb;

		bus_scb = ahd_wookup_scb(ahd, active_scbptw);
		if (bus_scb == pending_scb)
			disconnected = FAWSE;
	}

	/*
	 * At this point, pending_scb is the scb associated with the
	 * passed in command.  That command is cuwwentwy active on the
	 * bus ow is in the disconnected state.
	 */
	ahd_inb(ahd, SAVED_SCSIID);
	if (wast_phase != P_BUSFWEE
	    && SCB_GET_TAG(pending_scb) == active_scbptw) {

		/*
		 * We'we active on the bus, so assewt ATN
		 * and hope that the tawget wesponds.
		 */
		pending_scb = ahd_wookup_scb(ahd, active_scbptw);
		pending_scb->fwags |= SCB_WECOVEWY_SCB|SCB_ABOWT;
		ahd_outb(ahd, MSG_OUT, HOST_MSG);
		ahd_outb(ahd, SCSISIGO, wast_phase|ATNO);
		scmd_pwintk(KEWN_INFO, cmd, "Device is active, assewting ATN\n");
		wait = TWUE;
	} ewse if (disconnected) {

		/*
		 * Actuawwy we-queue this SCB in an attempt
		 * to sewect the device befowe it weconnects.
		 */
		pending_scb->fwags |= SCB_WECOVEWY_SCB|SCB_ABOWT;
		ahd_set_scbptw(ahd, SCB_GET_TAG(pending_scb));
		pending_scb->hscb->cdb_wen = 0;
		pending_scb->hscb->task_attwibute = 0;
		pending_scb->hscb->task_management = SIU_TASKMGMT_ABOWT_TASK;

		if ((pending_scb->fwags & SCB_PACKETIZED) != 0) {
			/*
			 * Mawk the SCB has having an outstanding
			 * task management function.  Shouwd the command
			 * compwete nowmawwy befowe the task management
			 * function can be sent, the host wiww be notified
			 * to abowt ouw wequeued SCB.
			 */
			ahd_outb(ahd, SCB_TASK_MANAGEMENT,
				 pending_scb->hscb->task_management);
		} ewse {
			/*
			 * If non-packetized, set the MK_MESSAGE contwow
			 * bit indicating that we desiwe to send a message.
			 * We awso set the disconnected fwag since thewe is
			 * no guawantee that ouw SCB contwow byte matches
			 * the vewsion on the cawd.  We don't want the
			 * sequencew to abowt the command thinking an
			 * unsowicited wesewection occuwwed.
			 */
			pending_scb->hscb->contwow |= MK_MESSAGE|DISCONNECTED;

			/*
			 * The sequencew wiww nevew we-wefewence the
			 * in-cowe SCB.  To make suwe we awe notified
			 * duwing wesewection, set the MK_MESSAGE fwag in
			 * the cawd's copy of the SCB.
			 */
			ahd_outb(ahd, SCB_CONTWOW,
				 ahd_inb(ahd, SCB_CONTWOW)|MK_MESSAGE);
		}

		/*
		 * Cweaw out any entwies in the QINFIFO fiwst
		 * so we awe the next SCB fow this tawget
		 * to wun.
		 */
		ahd_seawch_qinfifo(ahd, cmd->device->id,
				   cmd->device->channew + 'A', cmd->device->wun,
				   SCB_WIST_NUWW, WOWE_INITIATOW,
				   CAM_WEQUEUE_WEQ, SEAWCH_COMPWETE);
		ahd_qinfifo_wequeue_taiw(ahd, pending_scb);
		ahd_set_scbptw(ahd, saved_scbptw);
		ahd_pwint_path(ahd, pending_scb);
		pwintk("Device is disconnected, we-queuing SCB\n");
		wait = TWUE;
	} ewse {
		scmd_pwintk(KEWN_INFO, cmd, "Unabwe to dewivew message\n");
		wetvaw = FAIWED;
	}


	ahd_westowe_modes(ahd, saved_modes);
done:
	if (paused)
		ahd_unpause(ahd);
	if (wait) {
		DECWAWE_COMPWETION_ONSTACK(done);

		ahd->pwatfowm_data->eh_done = &done;
		ahd_unwock(ahd, &fwags);

		pwintk("%s: Wecovewy code sweeping\n", ahd_name(ahd));
		if (!wait_fow_compwetion_timeout(&done, 5 * HZ)) {
			ahd_wock(ahd, &fwags);
			ahd->pwatfowm_data->eh_done = NUWW;
			ahd_unwock(ahd, &fwags);
			pwintk("%s: Timew Expiwed (active %d)\n",
			       ahd_name(ahd), dev->active);
			wetvaw = FAIWED;
		}
		pwintk("Wecovewy code awake\n");
	} ewse
		ahd_unwock(ahd, &fwags);

	if (wetvaw != SUCCESS)
		pwintk("%s: Command abowt wetuwning 0x%x\n",
		       ahd_name(ahd), wetvaw);

	wetuwn wetvaw;
}

static void ahd_winux_set_width(stwuct scsi_tawget *stawget, int width)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_devinfo devinfo;
	unsigned wong fwags;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_wock(ahd, &fwags);
	ahd_set_width(ahd, &devinfo, width, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_pewiod(stwuct scsi_tawget *stawget, int pewiod)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options;
	unsigned int dt;
	unsigned wong fwags;
	unsigned wong offset = tinfo->goaw.offset;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: set pewiod to %d\n", ahd_name(ahd), pewiod);
#endif
	if (offset == 0)
		offset = MAX_OFFSET;

	if (pewiod < 8)
		pewiod = 8;
	if (pewiod < 10) {
		if (spi_max_width(stawget)) {
			ppw_options |= MSG_EXT_PPW_DT_WEQ;
			if (pewiod == 8)
				ppw_options |= MSG_EXT_PPW_IU_WEQ;
		} ewse
			pewiod = 10;
	}

	dt = ppw_options & MSG_EXT_PPW_DT_WEQ;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);

	/* aww PPW wequests apawt fwom QAS wequiwe wide twansfews */
	if (ppw_options & ~MSG_EXT_PPW_QAS_WEQ) {
		if (spi_width(stawget) == 0)
			ppw_options &= MSG_EXT_PPW_QAS_WEQ;
	}

	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_offset(stwuct scsi_tawget *stawget, int offset)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = 0;
	unsigned int pewiod = 0;
	unsigned int dt = ppw_options & MSG_EXT_PPW_DT_WEQ;
	unsigned wong fwags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: set offset to %d\n", ahd_name(ahd), offset);
#endif

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	if (offset != 0) {
		pewiod = tinfo->goaw.pewiod;
		ppw_options = tinfo->goaw.ppw_options;
		ahd_find_syncwate(ahd, &pewiod, &ppw_options, 
				  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);
	}

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, offset, ppw_options,
			 AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_dt(stwuct scsi_tawget *stawget, int dt)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_DT_WEQ;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int width = tinfo->goaw.width;
	unsigned wong fwags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: %s DT\n", ahd_name(ahd),
		       dt ? "enabwing" : "disabwing");
#endif
	if (dt && spi_max_width(stawget)) {
		ppw_options |= MSG_EXT_PPW_DT_WEQ;
		if (!width)
			ahd_winux_set_width(stawget, 1);
	} ewse {
		if (pewiod <= 9)
			pewiod = 10; /* If wesetting DT, pewiod must be >= 25ns */
		/* IU is invawid without DT set */
		ppw_options &= ~MSG_EXT_PPW_IU_WEQ;
	}
	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_qas(stwuct scsi_tawget *stawget, int qas)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_QAS_WEQ;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int dt;
	unsigned wong fwags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: %s QAS\n", ahd_name(ahd),
		       qas ? "enabwing" : "disabwing");
#endif

	if (qas) {
		ppw_options |= MSG_EXT_PPW_QAS_WEQ; 
	}

	dt = ppw_options & MSG_EXT_PPW_DT_WEQ;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_iu(stwuct scsi_tawget *stawget, int iu)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_IU_WEQ;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int dt;
	unsigned wong fwags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: %s IU\n", ahd_name(ahd),
		       iu ? "enabwing" : "disabwing");
#endif

	if (iu && spi_max_width(stawget)) {
		ppw_options |= MSG_EXT_PPW_IU_WEQ;
		ppw_options |= MSG_EXT_PPW_DT_WEQ; /* IU wequiwes DT */
	}

	dt = ppw_options & MSG_EXT_PPW_DT_WEQ;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_wd_stwm(stwuct scsi_tawget *stawget, int wdstwm)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_WD_STWM;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int dt = ppw_options & MSG_EXT_PPW_DT_WEQ;
	unsigned wong fwags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: %s Wead Stweaming\n", ahd_name(ahd),
		       wdstwm  ? "enabwing" : "disabwing");
#endif

	if (wdstwm && spi_max_width(stawget))
		ppw_options |= MSG_EXT_PPW_WD_STWM;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_ww_fwow(stwuct scsi_tawget *stawget, int wwfwow)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_WW_FWOW;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int dt = ppw_options & MSG_EXT_PPW_DT_WEQ;
	unsigned wong fwags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: %s Wwite Fwow Contwow\n", ahd_name(ahd),
		       wwfwow ? "enabwing" : "disabwing");
#endif

	if (wwfwow && spi_max_width(stawget))
		ppw_options |= MSG_EXT_PPW_WW_FWOW;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_wti(stwuct scsi_tawget *stawget, int wti)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_WTI;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int dt = ppw_options & MSG_EXT_PPW_DT_WEQ;
	unsigned wong fwags;

	if ((ahd->featuwes & AHD_WTI) == 0) {
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_DV) != 0)
			pwintk("%s: WTI not avaiwabwe\n", ahd_name(ahd));
#endif
		wetuwn;
	}

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: %s WTI\n", ahd_name(ahd),
		       wti ? "enabwing" : "disabwing");
#endif

	if (wti && spi_max_width(stawget))
		ppw_options |= MSG_EXT_PPW_WTI;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_pcomp_en(stwuct scsi_tawget *stawget, int pcomp)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_PCOMP_EN;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int dt = ppw_options & MSG_EXT_PPW_DT_WEQ;
	unsigned wong fwags;

#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_DV) != 0)
		pwintk("%s: %s Pwecompensation\n", ahd_name(ahd),
		       pcomp ? "Enabwe" : "Disabwe");
#endif

	if (pcomp && spi_max_width(stawget)) {
		uint8_t pwecomp;

		if (ahd->unit < AWWAY_SIZE(aic79xx_ioceww_info)) {
			const stwuct ahd_winux_ioceww_opts *ioceww_opts;

			ioceww_opts = &aic79xx_ioceww_info[ahd->unit];
			pwecomp = ioceww_opts->pwecomp;
		} ewse {
			pwecomp = AIC79XX_DEFAUWT_PWECOMP;
		}
		ppw_options |= MSG_EXT_PPW_PCOMP_EN;
		AHD_SET_PWECOMP(ahd, pwecomp);
	} ewse {
		AHD_SET_PWECOMP(ahd, 0);
	}

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_set_howd_mcs(stwuct scsi_tawget *stawget, int howd)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahd_softc *ahd = *((stwuct ahd_softc **)shost->hostdata);
	stwuct ahd_tmode_tstate *tstate;
	stwuct ahd_initiatow_tinfo *tinfo 
		= ahd_fetch_twansinfo(ahd,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahd_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_HOWD_MCS;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int dt = ppw_options & MSG_EXT_PPW_DT_WEQ;
	unsigned wong fwags;

	if (howd && spi_max_width(stawget))
		ppw_options |= MSG_EXT_PPW_HOWD_MCS;

	ahd_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahd_find_syncwate(ahd, &pewiod, &ppw_options,
			  dt ? AHD_SYNCWATE_MAX : AHD_SYNCWATE_UWTWA2);

	ahd_wock(ahd, &fwags);
	ahd_set_syncwate(ahd, &devinfo, pewiod, tinfo->goaw.offset,
			 ppw_options, AHD_TWANS_GOAW, FAWSE);
	ahd_unwock(ahd, &fwags);
}

static void ahd_winux_get_signawwing(stwuct Scsi_Host *shost)
{
	stwuct ahd_softc *ahd = *(stwuct ahd_softc **)shost->hostdata;
	unsigned wong fwags;
	u8 mode;

	ahd_wock(ahd, &fwags);
	ahd_pause(ahd);
	mode = ahd_inb(ahd, SBWKCTW);
	ahd_unpause(ahd);
	ahd_unwock(ahd, &fwags);

	if (mode & ENAB40)
		spi_signawwing(shost) = SPI_SIGNAW_WVD;
	ewse if (mode & ENAB20)
		spi_signawwing(shost) = SPI_SIGNAW_SE;
	ewse
		spi_signawwing(shost) = SPI_SIGNAW_UNKNOWN;
}

static stwuct spi_function_tempwate ahd_winux_twanspowt_functions = {
	.set_offset	= ahd_winux_set_offset,
	.show_offset	= 1,
	.set_pewiod	= ahd_winux_set_pewiod,
	.show_pewiod	= 1,
	.set_width	= ahd_winux_set_width,
	.show_width	= 1,
	.set_dt		= ahd_winux_set_dt,
	.show_dt	= 1,
	.set_iu		= ahd_winux_set_iu,
	.show_iu	= 1,
	.set_qas	= ahd_winux_set_qas,
	.show_qas	= 1,
	.set_wd_stwm	= ahd_winux_set_wd_stwm,
	.show_wd_stwm	= 1,
	.set_ww_fwow	= ahd_winux_set_ww_fwow,
	.show_ww_fwow	= 1,
	.set_wti	= ahd_winux_set_wti,
	.show_wti	= 1,
	.set_pcomp_en	= ahd_winux_set_pcomp_en,
	.show_pcomp_en	= 1,
	.set_howd_mcs	= ahd_winux_set_howd_mcs,
	.show_howd_mcs	= 1,
	.get_signawwing = ahd_winux_get_signawwing,
};

static int __init
ahd_winux_init(void)
{
	int	ewwow = 0;

	/*
	 * If we've been passed any pawametews, pwocess them now.
	 */
	if (aic79xx)
		aic79xx_setup(aic79xx);

	ahd_winux_twanspowt_tempwate =
		spi_attach_twanspowt(&ahd_winux_twanspowt_functions);
	if (!ahd_winux_twanspowt_tempwate)
		wetuwn -ENODEV;

	scsi_twanspowt_wesewve_device(ahd_winux_twanspowt_tempwate,
				      sizeof(stwuct ahd_winux_device));

	ewwow = ahd_winux_pci_init();
	if (ewwow)
		spi_wewease_twanspowt(ahd_winux_twanspowt_tempwate);
	wetuwn ewwow;
}

static void __exit
ahd_winux_exit(void)
{
	ahd_winux_pci_exit();
	spi_wewease_twanspowt(ahd_winux_twanspowt_tempwate);
}

moduwe_init(ahd_winux_init);
moduwe_exit(ahd_winux_exit);
