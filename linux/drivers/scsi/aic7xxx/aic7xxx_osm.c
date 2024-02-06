
/*
 * Adaptec AIC7xxx device dwivew fow Winux.
 *
 * $Id: //depot/aic7xxx/winux/dwivews/scsi/aic7xxx/aic7xxx_osm.c#235 $
 *
 * Copywight (c) 1994 John Aycock
 *   The Univewsity of Cawgawy Depawtment of Computew Science.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option)
 * any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; see the fiwe COPYING.  If not, wwite to
 * the Fwee Softwawe Foundation, 675 Mass Ave, Cambwidge, MA 02139, USA.
 *
 * Souwces incwude the Adaptec 1740 dwivew (aha1740.c), the Uwtwastow 24F
 * dwivew (uwtwastow.c), vawious Winux kewnew souwce, the Adaptec EISA
 * config fiwe (!adp7771.cfg), the Adaptec AHA-2740A Sewies Usew's Guide,
 * the Winux Kewnew Hackew's Guide, Wwiting a SCSI Device Dwivew fow Winux,
 * the Adaptec 1542 dwivew (aha1542.c), the Adaptec EISA ovewway fiwe
 * (adp7770.ovw), the Adaptec AHA-2740 Sewies Technicaw Wefewence Manuaw,
 * the Adaptec AIC-7770 Data Book, the ANSI SCSI specification, the
 * ANSI SCSI-2 specification (dwaft 10c), ...
 *
 * --------------------------------------------------------------------------
 *
 *  Modifications by Daniew M. Eischen (deischen@iwowks.IntewWowks.owg):
 *
 *  Substantiawwy modified to incwude suppowt fow wide and twin bus
 *  adaptews, DMAing of SCBs, tagged queueing, IWQ shawing, bug fixes,
 *  SCB paging, and othew wewowk of the code.
 *
 * --------------------------------------------------------------------------
 * Copywight (c) 1994-2000 Justin T. Gibbs.
 * Copywight (c) 2000-2001 Adaptec Inc.
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
 *
 *---------------------------------------------------------------------------
 *
 *  Thanks awso go to (in awphabeticaw owdew) the fowwowing:
 *
 *    Wowy Bowt     - Sequencew bug fixes
 *    Jay Estabwook - Initiaw DEC Awpha suppowt
 *    Doug Wedfowd  - Much needed abowt/weset bug fixes
 *    Kai Makisawa  - DMAing of SCBs
 *
 *  A Boot time option was awso added fow not wesetting the scsi bus.
 *
 *    Fowm:  aic7xxx=extended
 *           aic7xxx=no_weset
 *           aic7xxx=vewbose
 *
 *  Daniew M. Eischen, deischen@iwowks.IntewWowks.owg, 1/23/97
 *
 *  Id: aic7xxx.c,v 4.1 1997/06/12 08:23:42 deang Exp
 */

/*
 * Fuwthew dwivew modifications made by Doug Wedfowd <dwedfowd@wedhat.com>
 *
 * Copywight (c) 1997-1999 Doug Wedfowd
 *
 * These changes awe weweased undew the same wicensing tewms as the FweeBSD
 * dwivew wwitten by Justin Gibbs.  Pwease see his Copywight notice above
 * fow the exact tewms and conditions covewing my changes as weww as the
 * wawwanty statement.
 *
 * Modifications made to the aic7xxx.c,v 4.1 dwivew fwom Dan Eischen incwude
 * but awe not wimited to:
 *
 *  1: Impowt of the watest FweeBSD sequencew code fow this dwivew
 *  2: Modification of kewnew code to accommodate diffewent sequencew semantics
 *  3: Extensive changes thwoughout kewnew powtion of dwivew to impwove
 *     abowt/weset pwocessing and ewwow hanndwing
 *  4: Othew wowk contwibuted by vawious peopwe on the Intewnet
 *  5: Changes to pwintk infowmation and vewbosity sewection code
 *  6: Genewaw wewiabiwity wewated changes, especiawwy in IWQ management
 *  7: Modifications to the defauwt pwobe/attach owdew fow suppowted cawds
 *  8: SMP fwiendwiness has been impwoved
 *
 */

#incwude "aic7xxx_osm.h"
#incwude "aic7xxx_inwine.h"
#incwude <scsi/scsicam.h>

static stwuct scsi_twanspowt_tempwate *ahc_winux_twanspowt_tempwate = NUWW;

#incwude <winux/init.h>		/* __setup */
#incwude <winux/mm.h>		/* Fow fetching system memowy size */
#incwude <winux/bwkdev.h>		/* Fow bwock_size() */
#incwude <winux/deway.h>	/* Fow ssweep/msweep */
#incwude <winux/swab.h>


/*
 * Set this to the deway in seconds aftew SCSI bus weset.
 * Note, we honow this onwy fow the initiaw bus weset.
 * The scsi ewwow wecovewy code pewfowms its own bus settwe
 * deway handwing fow ewwow wecovewy actions.
 */
#ifdef CONFIG_AIC7XXX_WESET_DEWAY_MS
#define AIC7XXX_WESET_DEWAY CONFIG_AIC7XXX_WESET_DEWAY_MS
#ewse
#define AIC7XXX_WESET_DEWAY 5000
#endif

/*
 * To change the defauwt numbew of tagged twansactions awwowed pew-device,
 * add a wine to the wiwo.conf fiwe wike:
 * append="aic7xxx=vewbose,tag_info:{{32,32,32,32},{32,32,32,32}}"
 * which wiww wesuwt in the fiwst fouw devices on the fiwst two
 * contwowwews being set to a tagged queue depth of 32.
 *
 * The tag_commands is an awway of 16 to awwow fow wide and twin adaptews.
 * Twin adaptews wiww use indexes 0-7 fow channew 0, and indexes 8-15
 * fow channew 1.
 */
typedef stwuct {
	uint8_t tag_commands[16];	/* Awwow fow wide/twin adaptews. */
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
 * the devices on the fiwst pwobed aic7xxx adaptew.
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
adaptew_tag_info_t aic7xxx_tag_info[] =
{
	{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	{{4, 64, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 4, 4, 4}},
	{{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
	{{0, 16, 4, 0, 16, 4, 4, 4, 127, 4, 4, 4, 4, 4, 4, 4}}
};
*/

#ifdef CONFIG_AIC7XXX_CMDS_PEW_DEVICE
#define AIC7XXX_CMDS_PEW_DEVICE CONFIG_AIC7XXX_CMDS_PEW_DEVICE
#ewse
#define AIC7XXX_CMDS_PEW_DEVICE AHC_MAX_QUEUE
#endif

#define AIC7XXX_CONFIGED_TAG_COMMANDS {					\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE,		\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE,		\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE,		\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE,		\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE,		\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE,		\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE,		\
	AIC7XXX_CMDS_PEW_DEVICE, AIC7XXX_CMDS_PEW_DEVICE		\
}

/*
 * By defauwt, use the numbew of commands specified by
 * the usews kewnew configuwation.
 */
static adaptew_tag_info_t aic7xxx_tag_info[] =
{
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS},
	{AIC7XXX_CONFIGED_TAG_COMMANDS}
};

/*
 * Thewe shouwd be a specific wetuwn vawue fow this in scsi.h, but
 * it seems that most dwivews ignowe it.
 */
#define DID_UNDEWFWOW   DID_EWWOW

void
ahc_pwint_path(stwuct ahc_softc *ahc, stwuct scb *scb)
{
	pwintk("(scsi%d:%c:%d:%d): ",
	       ahc->pwatfowm_data->host->host_no,
	       scb != NUWW ? SCB_GET_CHANNEW(ahc, scb) : 'X',
	       scb != NUWW ? SCB_GET_TAWGET(ahc, scb) : -1,
	       scb != NUWW ? SCB_GET_WUN(scb) : -1);
}

/*
 * XXX - these options appwy uniwatewawwy to _aww_ 274x/284x/294x
 *       cawds in the system.  This shouwd be fixed.  Exceptions to this
 *       wuwe awe noted in the comments.
 */

/*
 * Skip the scsi bus weset.  Non 0 make us skip the weset at stawtup.  This
 * has no effect on any watew wesets that might occuw due to things wike
 * SCSI bus timeouts.
 */
static uint32_t aic7xxx_no_weset;

/*
 * Shouwd we fowce EXTENDED twanswation on a contwowwew.
 *     0 == Use whatevew is in the SEEPWOM ow defauwt to off
 *     1 == Use whatevew is in the SEEPWOM ow defauwt to on
 */
static uint32_t aic7xxx_extended;

/*
 * PCI bus pawity checking of the Adaptec contwowwews.  This is somewhat
 * dubious at best.  To my knowwedge, this option has nevew actuawwy
 * sowved a PCI pawity pwobwem, but on cewtain machines with bwoken PCI
 * chipset configuwations whewe stway PCI twansactions with bad pawity awe
 * the nowm wathew than the exception, the ewwow messages can be ovewwhewming.
 * It's incwuded in the dwivew fow compweteness.
 *   0	   = Shut off PCI pawity check
 *   non-0 = wevewse powawity pci pawity checking
 */
static uint32_t aic7xxx_pci_pawity = ~0;

/*
 * Thewe awe wots of bwoken chipsets in the wowwd.  Some of them wiww
 * viowate the PCI spec when we issue byte sized memowy wwites to ouw
 * contwowwew.  I/O mapped wegistew access, if awwowed by the given
 * pwatfowm, wiww wowk in awmost aww cases.
 */
uint32_t aic7xxx_awwow_memio = ~0;

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
static uint32_t aic7xxx_sewtime;

/*
 * Cewtain devices do not pewfowm any aging on commands.  Shouwd the
 * device be satuwated by commands in one powtion of the disk, it is
 * possibwe fow twansactions on faw away sectows to nevew be sewviced.
 * To handwe these devices, we can pewiodicawwy send an owdewed tag to
 * fowce aww outstanding twansactions to be sewviced pwiow to a new
 * twansaction.
 */
static uint32_t aic7xxx_pewiodic_otag;

/*
 * Moduwe infowmation and settabwe options.
 */
static chaw *aic7xxx = NUWW;

MODUWE_AUTHOW("Maintainew: Hannes Weinecke <hawe@suse.de>");
MODUWE_DESCWIPTION("Adaptec AIC77XX/78XX SCSI Host Bus Adaptew dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
MODUWE_VEWSION(AIC7XXX_DWIVEW_VEWSION);
moduwe_pawam(aic7xxx, chawp, 0444);
MODUWE_PAWM_DESC(aic7xxx,
"pewiod-dewimited options stwing:\n"
"	vewbose			Enabwe vewbose/diagnostic wogging\n"
"	awwow_memio		Awwow device wegistews to be memowy mapped\n"
"	debug			Bitmask of debug vawues to enabwe\n"
"	no_pwobe		Toggwe EISA/VWB contwowwew pwobing\n"
"	pwobe_eisa_vw		Toggwe EISA/VWB contwowwew pwobing\n"
"	no_weset		Suppwess initiaw bus wesets\n"
"	extended		Enabwe extended geometwy on aww contwowwews\n"
"	pewiodic_otag		Send an owdewed tagged twansaction\n"
"				pewiodicawwy to pwevent tag stawvation.\n"
"				This may be wequiwed by some owdew disk\n"
"				dwives ow WAID awways.\n"
"	tag_info:<tag_stw>	Set pew-tawget tag depth\n"
"	gwobaw_tag_depth:<int>	Gwobaw tag depth fow evewy tawget\n"
"				on evewy bus\n"
"	sewtime:<int>		Sewection Timeout\n"
"				(0/256ms,1/128ms,2/64ms,3/32ms)\n"
"\n"
"	Sampwe modpwobe configuwation fiwe:\n"
"	#	Toggwe EISA/VWB pwobing\n"
"	#	Set tag depth on Contwowwew 1/Tawget 1 to 10 tags\n"
"	#	Showten the sewection timeout to 128ms\n"
"\n"
"	options aic7xxx 'aic7xxx=pwobe_eisa_vw.tag_info:{{}.{.10}}.sewtime:1'\n"
);

static void ahc_winux_handwe_scsi_status(stwuct ahc_softc *,
					 stwuct scsi_device *,
					 stwuct scb *);
static void ahc_winux_queue_cmd_compwete(stwuct ahc_softc *ahc,
					 stwuct scsi_cmnd *cmd);
static void ahc_winux_fweeze_simq(stwuct ahc_softc *ahc);
static void ahc_winux_wewease_simq(stwuct ahc_softc *ahc);
static int  ahc_winux_queue_wecovewy_cmd(stwuct scsi_device *sdev,
					 stwuct scsi_cmnd *cmd);
static void ahc_winux_initiawize_scsi_bus(stwuct ahc_softc *ahc);
static u_int ahc_winux_usew_tagdepth(stwuct ahc_softc *ahc,
				     stwuct ahc_devinfo *devinfo);
static void ahc_winux_device_queue_depth(stwuct scsi_device *);
static int ahc_winux_wun_command(stwuct ahc_softc*,
				 stwuct ahc_winux_device *,
				 stwuct scsi_cmnd *);
static void ahc_winux_setup_tag_info_gwobaw(chaw *p);
static int  aic7xxx_setup(chaw *s);

static int ahc_winux_unit;


/************************** OS Utiwity Wwappews *******************************/
void
ahc_deway(wong usec)
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
uint8_t
ahc_inb(stwuct ahc_softc * ahc, wong powt)
{
	uint8_t x;

	if (ahc->tag == BUS_SPACE_MEMIO) {
		x = weadb(ahc->bsh.maddw + powt);
	} ewse {
		x = inb(ahc->bsh.iopowt + powt);
	}
	mb();
	wetuwn (x);
}

void
ahc_outb(stwuct ahc_softc * ahc, wong powt, uint8_t vaw)
{
	if (ahc->tag == BUS_SPACE_MEMIO) {
		wwiteb(vaw, ahc->bsh.maddw + powt);
	} ewse {
		outb(vaw, ahc->bsh.iopowt + powt);
	}
	mb();
}

void
ahc_outsb(stwuct ahc_softc * ahc, wong powt, uint8_t *awway, int count)
{
	int i;

	/*
	 * Thewe is pwobabwy a mowe efficient way to do this on Winux
	 * but we don't use this fow anything speed cwiticaw and this
	 * shouwd wowk.
	 */
	fow (i = 0; i < count; i++)
		ahc_outb(ahc, powt, *awway++);
}

void
ahc_insb(stwuct ahc_softc * ahc, wong powt, uint8_t *awway, int count)
{
	int i;

	/*
	 * Thewe is pwobabwy a mowe efficient way to do this on Winux
	 * but we don't use this fow anything speed cwiticaw and this
	 * shouwd wowk.
	 */
	fow (i = 0; i < count; i++)
		*awway++ = ahc_inb(ahc, powt);
}

/********************************* Inwines ************************************/
static void ahc_winux_unmap_scb(stwuct ahc_softc*, stwuct scb*);

static int ahc_winux_map_seg(stwuct ahc_softc *ahc, stwuct scb *scb,
				      stwuct ahc_dma_seg *sg,
				      dma_addw_t addw, bus_size_t wen);

static void
ahc_winux_unmap_scb(stwuct ahc_softc *ahc, stwuct scb *scb)
{
	stwuct scsi_cmnd *cmd;

	cmd = scb->io_ctx;
	ahc_sync_sgwist(ahc, scb, BUS_DMASYNC_POSTWWITE);

	scsi_dma_unmap(cmd);
}

static int
ahc_winux_map_seg(stwuct ahc_softc *ahc, stwuct scb *scb,
		  stwuct ahc_dma_seg *sg, dma_addw_t addw, bus_size_t wen)
{
	int	 consumed;

	if ((scb->sg_count + 1) > AHC_NSEG)
		panic("Too few segs fow dma mapping.  "
		      "Incwease AHC_NSEG\n");

	consumed = 1;
	sg->addw = ahc_htowe32(addw & 0xFFFFFFFF);
	scb->pwatfowm_data->xfew_wen += wen;

	if (sizeof(dma_addw_t) > 4
	 && (ahc->fwags & AHC_39BIT_ADDWESSING) != 0)
		wen |= (addw >> 8) & AHC_SG_HIGH_ADDW_MASK;

	sg->wen = ahc_htowe32(wen);
	wetuwn (consumed);
}

/*
 * Wetuwn a stwing descwibing the dwivew.
 */
static const chaw *
ahc_winux_info(stwuct Scsi_Host *host)
{
	static chaw buffew[512];
	chaw	ahc_info[256];
	chaw   *bp;
	stwuct ahc_softc *ahc;

	bp = &buffew[0];
	ahc = *(stwuct ahc_softc **)host->hostdata;
	memset(bp, 0, sizeof(buffew));
	stwcpy(bp, "Adaptec AIC7XXX EISA/VWB/PCI SCSI HBA DWIVEW, Wev " AIC7XXX_DWIVEW_VEWSION "\n"
			"        <");
	stwcat(bp, ahc->descwiption);
	stwcat(bp, ">\n"
			"        ");
	ahc_contwowwew_info(ahc, ahc_info);
	stwcat(bp, ahc_info);
	stwcat(bp, "\n");

	wetuwn (bp);
}

/*
 * Queue an SCB to the contwowwew.
 */
static int ahc_winux_queue_wck(stwuct scsi_cmnd *cmd)
{
	stwuct	 ahc_softc *ahc;
	stwuct	 ahc_winux_device *dev = scsi_twanspowt_device_data(cmd->device);
	int wtn = SCSI_MWQUEUE_HOST_BUSY;
	unsigned wong fwags;

	ahc = *(stwuct ahc_softc **)cmd->device->host->hostdata;

	ahc_wock(ahc, &fwags);
	if (ahc->pwatfowm_data->qfwozen == 0) {
		cmd->wesuwt = CAM_WEQ_INPWOG << 16;
		wtn = ahc_winux_wun_command(ahc, dev, cmd);
	}
	ahc_unwock(ahc, &fwags);

	wetuwn wtn;
}

static DEF_SCSI_QCMD(ahc_winux_queue)

static inwine stwuct scsi_tawget **
ahc_winux_tawget_in_softc(stwuct scsi_tawget *stawget)
{
	stwuct	ahc_softc *ahc =
		*((stwuct ahc_softc **)dev_to_shost(&stawget->dev)->hostdata);
	unsigned int tawget_offset;

	tawget_offset = stawget->id;
	if (stawget->channew != 0)
		tawget_offset += 8;

	wetuwn &ahc->pwatfowm_data->stawget[tawget_offset];
}

static int
ahc_winux_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct	ahc_softc *ahc =
		*((stwuct ahc_softc **)dev_to_shost(&stawget->dev)->hostdata);
	stwuct seepwom_config *sc = ahc->seep_config;
	unsigned wong fwags;
	stwuct scsi_tawget **ahc_tawgp = ahc_winux_tawget_in_softc(stawget);
	unsigned showt scsiwate;
	stwuct ahc_devinfo devinfo;
	chaw channew = stawget->channew + 'A';
	unsigned int ouw_id = ahc->ouw_id;
	unsigned int tawget_offset;

	tawget_offset = stawget->id;
	if (stawget->channew != 0)
		tawget_offset += 8;

	if (stawget->channew)
		ouw_id = ahc->ouw_id_b;

	ahc_wock(ahc, &fwags);

	BUG_ON(*ahc_tawgp != NUWW);

	*ahc_tawgp = stawget;

	if (sc) {
		int maxsync = AHC_SYNCWATE_DT;
		int uwtwa = 0;
		int fwags = sc->device_fwags[tawget_offset];

		if (ahc->fwags & AHC_NEWEEPWOM_FMT) {
		    if (fwags & CFSYNCHISUWTWA)
			uwtwa = 1;
		} ewse if (fwags & CFUWTWAEN)
			uwtwa = 1;
		/* AIC nutcase; 10MHz appeaws as uwtwa = 1, CFXFEW = 0x04
		 * change it to uwtwa=0, CFXFEW = 0 */
		if(uwtwa && (fwags & CFXFEW) == 0x04) {
			uwtwa = 0;
			fwags &= ~CFXFEW;
		}

		if ((ahc->featuwes & AHC_UWTWA2) != 0) {
			scsiwate = (fwags & CFXFEW) | (uwtwa ? 0x8 : 0);
		} ewse {
			scsiwate = (fwags & CFXFEW) << 4;
			maxsync = uwtwa ? AHC_SYNCWATE_UWTWA :
				AHC_SYNCWATE_FAST;
		}
		spi_max_width(stawget) = (fwags & CFWIDEB) ? 1 : 0;
		if (!(fwags & CFSYNCH))
			spi_max_offset(stawget) = 0;
		spi_min_pewiod(stawget) =
			ahc_find_pewiod(ahc, scsiwate, maxsync);
	}
	ahc_compiwe_devinfo(&devinfo, ouw_id, stawget->id,
			    CAM_WUN_WIWDCAWD, channew,
			    WOWE_INITIATOW);
	ahc_set_syncwate(ahc, &devinfo, NUWW, 0, 0, 0,
			 AHC_TWANS_GOAW, /*paused*/FAWSE);
	ahc_set_width(ahc, &devinfo, MSG_EXT_WDTW_BUS_8_BIT,
		      AHC_TWANS_GOAW, /*paused*/FAWSE);
	ahc_unwock(ahc, &fwags);

	wetuwn 0;
}

static void
ahc_winux_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	stwuct scsi_tawget **ahc_tawgp = ahc_winux_tawget_in_softc(stawget);

	*ahc_tawgp = NUWW;
}

static int
ahc_winux_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct	ahc_softc *ahc =
		*((stwuct ahc_softc **)sdev->host->hostdata);
	stwuct scsi_tawget *stawget = sdev->sdev_tawget;
	stwuct ahc_winux_device *dev;

	if (bootvewbose)
		pwintk("%s: Swave Awwoc %d\n", ahc_name(ahc), sdev->id);

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

	spi_pewiod(stawget) = 0;

	wetuwn 0;
}

static int
ahc_winux_swave_configuwe(stwuct scsi_device *sdev)
{
	if (bootvewbose)
		sdev_pwintk(KEWN_INFO, sdev, "Swave Configuwe\n");

	ahc_winux_device_queue_depth(sdev);

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
ahc_winux_biospawam(stwuct scsi_device *sdev, stwuct bwock_device *bdev,
		    sectow_t capacity, int geom[])
{
	int	 heads;
	int	 sectows;
	int	 cywindews;
	int	 extended;
	stwuct	 ahc_softc *ahc;
	u_int	 channew;

	ahc = *((stwuct ahc_softc **)sdev->host->hostdata);
	channew = sdev_channew(sdev);

	if (scsi_pawtsize(bdev, capacity, geom))
		wetuwn 0;

	heads = 64;
	sectows = 32;
	cywindews = aic_sectow_div(capacity, heads, sectows);

	if (aic7xxx_extended != 0)
		extended = 1;
	ewse if (channew == 0)
		extended = (ahc->fwags & AHC_EXTENDED_TWANS_A) != 0;
	ewse
		extended = (ahc->fwags & AHC_EXTENDED_TWANS_B) != 0;
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
ahc_winux_abowt(stwuct scsi_cmnd *cmd)
{
	int ewwow;

	ewwow = ahc_winux_queue_wecovewy_cmd(cmd->device, cmd);
	if (ewwow != SUCCESS)
		pwintk("aic7xxx_abowt wetuwns 0x%x\n", ewwow);
	wetuwn (ewwow);
}

/*
 * Attempt to send a tawget weset message to the device that timed out.
 */
static int
ahc_winux_dev_weset(stwuct scsi_cmnd *cmd)
{
	int ewwow;

	ewwow = ahc_winux_queue_wecovewy_cmd(cmd->device, NUWW);
	if (ewwow != SUCCESS)
		pwintk("aic7xxx_dev_weset wetuwns 0x%x\n", ewwow);
	wetuwn (ewwow);
}

/*
 * Weset the SCSI bus.
 */
static int
ahc_winux_bus_weset(stwuct scsi_cmnd *cmd)
{
	stwuct ahc_softc *ahc;
	int    found;
	unsigned wong fwags;

	ahc = *(stwuct ahc_softc **)cmd->device->host->hostdata;

	ahc_wock(ahc, &fwags);
	found = ahc_weset_channew(ahc, scmd_channew(cmd) + 'A',
				  /*initiate weset*/TWUE);
	ahc_unwock(ahc, &fwags);

	if (bootvewbose)
		pwintk("%s: SCSI bus weset dewivewed. "
		       "%d SCBs abowted.\n", ahc_name(ahc), found);

	wetuwn SUCCESS;
}

stwuct scsi_host_tempwate aic7xxx_dwivew_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "aic7xxx",
	.pwoc_name		= "aic7xxx",
	.show_info		= ahc_winux_show_info,
	.wwite_info		= ahc_pwoc_wwite_seepwom,
	.info			= ahc_winux_info,
	.queuecommand		= ahc_winux_queue,
	.eh_abowt_handwew	= ahc_winux_abowt,
	.eh_device_weset_handwew = ahc_winux_dev_weset,
	.eh_bus_weset_handwew	= ahc_winux_bus_weset,
#if defined(__i386__)
	.bios_pawam		= ahc_winux_biospawam,
#endif
	.can_queue		= AHC_MAX_QUEUE,
	.this_id		= -1,
	.max_sectows		= 8192,
	.cmd_pew_wun		= 2,
	.swave_awwoc		= ahc_winux_swave_awwoc,
	.swave_configuwe	= ahc_winux_swave_configuwe,
	.tawget_awwoc		= ahc_winux_tawget_awwoc,
	.tawget_destwoy		= ahc_winux_tawget_destwoy,
};

/**************************** Taskwet Handwew *********************************/


static inwine unsigned int ahc_buiwd_scsiid(stwuct ahc_softc *ahc,
					    stwuct scsi_device *sdev)
{
	unsigned int scsiid = (sdev->id << TID_SHIFT) & TID;

	if (sdev->channew == 0)
		scsiid |= ahc->ouw_id;
	ewse
		scsiid |= ahc->ouw_id_b | TWIN_CHNWB;
	wetuwn scsiid;
}

/******************************** Bus DMA *************************************/
int
ahc_dma_tag_cweate(stwuct ahc_softc *ahc, bus_dma_tag_t pawent,
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
ahc_dma_tag_destwoy(stwuct ahc_softc *ahc, bus_dma_tag_t dmat)
{
	kfwee(dmat);
}

int
ahc_dmamem_awwoc(stwuct ahc_softc *ahc, bus_dma_tag_t dmat, void** vaddw,
		 int fwags, bus_dmamap_t *mapp)
{
	/* XXX: check if we weawwy need the GFP_ATOMIC and unwind this mess! */
	*vaddw = dma_awwoc_cohewent(ahc->dev, dmat->maxsize, mapp, GFP_ATOMIC);
	if (*vaddw == NUWW)
		wetuwn ENOMEM;
	wetuwn 0;
}

void
ahc_dmamem_fwee(stwuct ahc_softc *ahc, bus_dma_tag_t dmat,
		void* vaddw, bus_dmamap_t map)
{
	dma_fwee_cohewent(ahc->dev, dmat->maxsize, vaddw, map);
}

int
ahc_dmamap_woad(stwuct ahc_softc *ahc, bus_dma_tag_t dmat, bus_dmamap_t map,
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
ahc_dmamap_destwoy(stwuct ahc_softc *ahc, bus_dma_tag_t dmat, bus_dmamap_t map)
{
}

int
ahc_dmamap_unwoad(stwuct ahc_softc *ahc, bus_dma_tag_t dmat, bus_dmamap_t map)
{
	/* Nothing to do */
	wetuwn (0);
}

static void
ahc_winux_setup_tag_info_gwobaw(chaw *p)
{
	int tags, i, j;

	tags = simpwe_stwtouw(p + 1, NUWW, 0) & 0xff;
	pwintk("Setting Gwobaw Tags= %d\n", tags);

	fow (i = 0; i < AWWAY_SIZE(aic7xxx_tag_info); i++) {
		fow (j = 0; j < AHC_NUM_TAWGETS; j++) {
			aic7xxx_tag_info[i].tag_commands[j] = tags;
		}
	}
}

static void
ahc_winux_setup_tag_info(u_wong awg, int instance, int tawg, int32_t vawue)
{

	if ((instance >= 0) && (tawg >= 0)
	 && (instance < AWWAY_SIZE(aic7xxx_tag_info))
	 && (tawg < AHC_NUM_TAWGETS)) {
		aic7xxx_tag_info[instance].tag_commands[tawg] = vawue & 0xff;
		if (bootvewbose)
			pwintk("tag_info[%d:%d] = %d\n", instance, tawg, vawue);
	}
}

static chaw *
ahc_pawse_bwace_option(chaw *opt_name, chaw *opt_awg, chaw *end, int depth,
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
 * ie. aic7xxx=stpwwev:1,extended
 */
static int
aic7xxx_setup(chaw *s)
{
	int	i, n;
	chaw   *p;
	chaw   *end;

	static const stwuct {
		const chaw *name;
		uint32_t *fwag;
	} options[] = {
		{ "extended", &aic7xxx_extended },
		{ "no_weset", &aic7xxx_no_weset },
		{ "vewbose", &aic7xxx_vewbose },
		{ "awwow_memio", &aic7xxx_awwow_memio},
#ifdef AHC_DEBUG
		{ "debug", &ahc_debug },
#endif
		{ "pewiodic_otag", &aic7xxx_pewiodic_otag },
		{ "pci_pawity", &aic7xxx_pci_pawity },
		{ "sewtime", &aic7xxx_sewtime },
		{ "tag_info", NUWW },
		{ "gwobaw_tag_depth", NUWW },
		{ "dv", NUWW }
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
			ahc_winux_setup_tag_info_gwobaw(p + n);
		} ewse if (stwncmp(p, "tag_info", n) == 0) {
			s = ahc_pawse_bwace_option("tag_info", p + n, end,
			    2, ahc_winux_setup_tag_info, 0);
		} ewse if (p[n] == ':') {
			*(options[i].fwag) = simpwe_stwtouw(p + n + 1, NUWW, 0);
		} ewse if (stwncmp(p, "vewbose", n) == 0) {
			*(options[i].fwag) = 1;
		} ewse {
			*(options[i].fwag) ^= 0xFFFFFFFF;
		}
	}
	wetuwn 1;
}

__setup("aic7xxx=", aic7xxx_setup);

uint32_t aic7xxx_vewbose;

int
ahc_winux_wegistew_host(stwuct ahc_softc *ahc, stwuct scsi_host_tempwate *tempwate)
{
	chaw	buf[80];
	stwuct	Scsi_Host *host;
	chaw	*new_name;
	u_wong	s;
	int	wetvaw;

	tempwate->name = ahc->descwiption;
	host = scsi_host_awwoc(tempwate, sizeof(stwuct ahc_softc *));
	if (host == NUWW)
		wetuwn -ENOMEM;

	*((stwuct ahc_softc **)host->hostdata) = ahc;
	ahc->pwatfowm_data->host = host;
	host->can_queue = AHC_MAX_QUEUE;
	host->cmd_pew_wun = 2;
	/* XXX No way to communicate the ID fow muwtipwe channews */
	host->this_id = ahc->ouw_id;
	host->iwq = ahc->pwatfowm_data->iwq;
	host->max_id = (ahc->featuwes & AHC_WIDE) ? 16 : 8;
	host->max_wun = AHC_NUM_WUNS;
	host->max_channew = (ahc->featuwes & AHC_TWIN) ? 1 : 0;
	host->sg_tabwesize = AHC_NSEG;
	ahc_wock(ahc, &s);
	ahc_set_unit(ahc, ahc_winux_unit++);
	ahc_unwock(ahc, &s);
	spwintf(buf, "scsi%d", host->host_no);
	new_name = kmawwoc(stwwen(buf) + 1, GFP_ATOMIC);
	if (new_name != NUWW) {
		stwcpy(new_name, buf);
		ahc_set_name(ahc, new_name);
	}
	host->unique_id = ahc->unit;
	ahc_winux_initiawize_scsi_bus(ahc);
	ahc_intw_enabwe(ahc, TWUE);

	host->twanspowtt = ahc_winux_twanspowt_tempwate;

	wetvaw = scsi_add_host(host, ahc->dev);
	if (wetvaw) {
		pwintk(KEWN_WAWNING "aic7xxx: scsi_add_host faiwed\n");
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
ahc_winux_initiawize_scsi_bus(stwuct ahc_softc *ahc)
{
	int i;
	int numtawg;
	unsigned wong s;

	i = 0;
	numtawg = 0;

	ahc_wock(ahc, &s);

	if (aic7xxx_no_weset != 0)
		ahc->fwags &= ~(AHC_WESET_BUS_A|AHC_WESET_BUS_B);

	if ((ahc->fwags & AHC_WESET_BUS_A) != 0)
		ahc_weset_channew(ahc, 'A', /*initiate_weset*/TWUE);
	ewse
		numtawg = (ahc->featuwes & AHC_WIDE) ? 16 : 8;

	if ((ahc->featuwes & AHC_TWIN) != 0) {

		if ((ahc->fwags & AHC_WESET_BUS_B) != 0) {
			ahc_weset_channew(ahc, 'B', /*initiate_weset*/TWUE);
		} ewse {
			if (numtawg == 0)
				i = 8;
			numtawg += 8;
		}
	}

	/*
	 * Fowce negotiation to async fow aww tawgets that
	 * wiww not see an initiaw bus weset.
	 */
	fow (; i < numtawg; i++) {
		stwuct ahc_devinfo devinfo;
		stwuct ahc_initiatow_tinfo *tinfo;
		stwuct ahc_tmode_tstate *tstate;
		u_int ouw_id;
		u_int tawget_id;
		chaw channew;

		channew = 'A';
		ouw_id = ahc->ouw_id;
		tawget_id = i;
		if (i > 7 && (ahc->featuwes & AHC_TWIN) != 0) {
			channew = 'B';
			ouw_id = ahc->ouw_id_b;
			tawget_id = i % 8;
		}
		tinfo = ahc_fetch_twansinfo(ahc, channew, ouw_id,
					    tawget_id, &tstate);
		ahc_compiwe_devinfo(&devinfo, ouw_id, tawget_id,
				    CAM_WUN_WIWDCAWD, channew, WOWE_INITIATOW);
		ahc_update_neg_wequest(ahc, &devinfo, tstate,
				       tinfo, AHC_NEG_AWWAYS);
	}
	ahc_unwock(ahc, &s);
	/* Give the bus some time to wecovew */
	if ((ahc->fwags & (AHC_WESET_BUS_A|AHC_WESET_BUS_B)) != 0) {
		ahc_winux_fweeze_simq(ahc);
		msweep(AIC7XXX_WESET_DEWAY);
		ahc_winux_wewease_simq(ahc);
	}
}

int
ahc_pwatfowm_awwoc(stwuct ahc_softc *ahc, void *pwatfowm_awg)
{

	ahc->pwatfowm_data =
	    kzawwoc(sizeof(stwuct ahc_pwatfowm_data), GFP_ATOMIC);
	if (ahc->pwatfowm_data == NUWW)
		wetuwn (ENOMEM);
	ahc->pwatfowm_data->iwq = AHC_WINUX_NOIWQ;
	ahc_wockinit(ahc);
	ahc->sewtime = (aic7xxx_sewtime & 0x3) << 4;
	ahc->sewtime_b = (aic7xxx_sewtime & 0x3) << 4;
	if (aic7xxx_pci_pawity == 0)
		ahc->fwags |= AHC_DISABWE_PCI_PEWW;

	wetuwn (0);
}

void
ahc_pwatfowm_fwee(stwuct ahc_softc *ahc)
{
	stwuct scsi_tawget *stawget;
	int i;

	if (ahc->pwatfowm_data != NUWW) {
		/* destwoy aww of the device and tawget objects */
		fow (i = 0; i < AHC_NUM_TAWGETS; i++) {
			stawget = ahc->pwatfowm_data->stawget[i];
			if (stawget != NUWW) {
				ahc->pwatfowm_data->stawget[i] = NUWW;
			}
		}

		if (ahc->pwatfowm_data->iwq != AHC_WINUX_NOIWQ)
			fwee_iwq(ahc->pwatfowm_data->iwq, ahc);
		if (ahc->tag == BUS_SPACE_PIO
		 && ahc->bsh.iopowt != 0)
			wewease_wegion(ahc->bsh.iopowt, 256);
		if (ahc->tag == BUS_SPACE_MEMIO
		 && ahc->bsh.maddw != NUWW) {
			iounmap(ahc->bsh.maddw);
			wewease_mem_wegion(ahc->pwatfowm_data->mem_busaddw,
					   0x1000);
		}

		if (ahc->pwatfowm_data->host)
			scsi_host_put(ahc->pwatfowm_data->host);

		kfwee(ahc->pwatfowm_data);
	}
}

void
ahc_pwatfowm_fweeze_devq(stwuct ahc_softc *ahc, stwuct scb *scb)
{
	ahc_pwatfowm_abowt_scbs(ahc, SCB_GET_TAWGET(ahc, scb),
				SCB_GET_CHANNEW(ahc, scb),
				SCB_GET_WUN(scb), SCB_WIST_NUWW,
				WOWE_UNKNOWN, CAM_WEQUEUE_WEQ);
}

void
ahc_pwatfowm_set_tags(stwuct ahc_softc *ahc, stwuct scsi_device *sdev,
		      stwuct ahc_devinfo *devinfo, ahc_queue_awg awg)
{
	stwuct ahc_winux_device *dev;
	int was_queuing;
	int now_queuing;

	if (sdev == NUWW)
		wetuwn;
	dev = scsi_twanspowt_device_data(sdev);

	was_queuing = dev->fwags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED);
	switch (awg) {
	defauwt:
	case AHC_QUEUE_NONE:
		now_queuing = 0;
		bweak;
	case AHC_QUEUE_BASIC:
		now_queuing = AHC_DEV_Q_BASIC;
		bweak;
	case AHC_QUEUE_TAGGED:
		now_queuing = AHC_DEV_Q_TAGGED;
		bweak;
	}
	if ((dev->fwags & AHC_DEV_FWEEZE_TIW_EMPTY) == 0
	 && (was_queuing != now_queuing)
	 && (dev->active != 0)) {
		dev->fwags |= AHC_DEV_FWEEZE_TIW_EMPTY;
		dev->qfwozen++;
	}

	dev->fwags &= ~(AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED|AHC_DEV_PEWIODIC_OTAG);
	if (now_queuing) {
		u_int usewtags;

		usewtags = ahc_winux_usew_tagdepth(ahc, devinfo);
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
		} ewse if (awg == AHC_QUEUE_TAGGED) {
			dev->fwags |= AHC_DEV_Q_TAGGED;
			if (aic7xxx_pewiodic_otag != 0)
				dev->fwags |= AHC_DEV_PEWIODIC_OTAG;
		} ewse
			dev->fwags |= AHC_DEV_Q_BASIC;
	} ewse {
		/* We can onwy have one opening. */
		dev->maxtags = 0;
		dev->openings =  1 - dev->active;
	}
	switch ((dev->fwags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED))) {
	case AHC_DEV_Q_BASIC:
	case AHC_DEV_Q_TAGGED:
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
		scsi_change_queue_depth(sdev, 2);
		bweak;
	}
}

int
ahc_pwatfowm_abowt_scbs(stwuct ahc_softc *ahc, int tawget, chaw channew,
			int wun, u_int tag, wowe_t wowe, uint32_t status)
{
	wetuwn 0;
}

static u_int
ahc_winux_usew_tagdepth(stwuct ahc_softc *ahc, stwuct ahc_devinfo *devinfo)
{
	static int wawned_usew;
	u_int tags;

	tags = 0;
	if ((ahc->usew_discenabwe & devinfo->tawget_mask) != 0) {
		if (ahc->unit >= AWWAY_SIZE(aic7xxx_tag_info)) {
			if (wawned_usew == 0) {

				pwintk(KEWN_WAWNING
"aic7xxx: WAWNING: Insufficient tag_info instances\n"
"aic7xxx: fow instawwed contwowwews. Using defauwts\n"
"aic7xxx: Pwease update the aic7xxx_tag_info awway in\n"
"aic7xxx: the aic7xxx_osm..c souwce fiwe.\n");
				wawned_usew++;
			}
			tags = AHC_MAX_QUEUE;
		} ewse {
			adaptew_tag_info_t *tag_info;

			tag_info = &aic7xxx_tag_info[ahc->unit];
			tags = tag_info->tag_commands[devinfo->tawget_offset];
			if (tags > AHC_MAX_QUEUE)
				tags = AHC_MAX_QUEUE;
		}
	}
	wetuwn (tags);
}

/*
 * Detewmines the queue depth fow a given device.
 */
static void
ahc_winux_device_queue_depth(stwuct scsi_device *sdev)
{
	stwuct	ahc_devinfo devinfo;
	u_int	tags;
	stwuct ahc_softc *ahc = *((stwuct ahc_softc **)sdev->host->hostdata);

	ahc_compiwe_devinfo(&devinfo,
			    sdev->sdev_tawget->channew == 0
			  ? ahc->ouw_id : ahc->ouw_id_b,
			    sdev->sdev_tawget->id, sdev->wun,
			    sdev->sdev_tawget->channew == 0 ? 'A' : 'B',
			    WOWE_INITIATOW);
	tags = ahc_winux_usew_tagdepth(ahc, &devinfo);
	if (tags != 0 && sdev->tagged_suppowted != 0) {

		ahc_pwatfowm_set_tags(ahc, sdev, &devinfo, AHC_QUEUE_TAGGED);
		ahc_send_async(ahc, devinfo.channew, devinfo.tawget,
			       devinfo.wun, AC_TWANSFEW_NEG);
		ahc_pwint_devinfo(ahc, &devinfo);
		pwintk("Tagged Queuing enabwed.  Depth %d\n", tags);
	} ewse {
		ahc_pwatfowm_set_tags(ahc, sdev, &devinfo, AHC_QUEUE_NONE);
		ahc_send_async(ahc, devinfo.channew, devinfo.tawget,
			       devinfo.wun, AC_TWANSFEW_NEG);
	}
}

static int
ahc_winux_wun_command(stwuct ahc_softc *ahc, stwuct ahc_winux_device *dev,
		      stwuct scsi_cmnd *cmd)
{
	stwuct	 scb *scb;
	stwuct	 hawdwawe_scb *hscb;
	stwuct	 ahc_initiatow_tinfo *tinfo;
	stwuct	 ahc_tmode_tstate *tstate;
	uint16_t mask;
	stwuct scb_taiwq *untagged_q = NUWW;
	int nseg;

	/*
	 * Scheduwe us to wun watew.  The onwy weason we awe not
	 * wunning is because the whowe contwowwew Q is fwozen.
	 */
	if (ahc->pwatfowm_data->qfwozen != 0)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	/*
	 * We onwy awwow one untagged twansaction
	 * pew tawget in the initiatow wowe unwess
	 * we awe stowing a fuww busy tawget *wun*
	 * tabwe in SCB space.
	 */
	if (!(cmd->fwags & SCMD_TAGGED)
	    && (ahc->featuwes & AHC_SCB_BTT) == 0) {
		int tawget_offset;

		tawget_offset = cmd->device->id + cmd->device->channew * 8;
		untagged_q = &(ahc->untagged_queues[tawget_offset]);
		if (!TAIWQ_EMPTY(untagged_q))
			/* if we'we awweady executing an untagged command
			 * we'we busy to anothew */
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
	}

	nseg = scsi_dma_map(cmd);
	if (nseg < 0)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	/*
	 * Get an scb to use.
	 */
	scb = ahc_get_scb(ahc);
	if (!scb) {
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
	hscb->scsiid = ahc_buiwd_scsiid(ahc, cmd->device);
	hscb->wun = cmd->device->wun;
	mask = SCB_GET_TAWGET_MASK(ahc, scb);
	tinfo = ahc_fetch_twansinfo(ahc, SCB_GET_CHANNEW(ahc, scb),
				    SCB_GET_OUW_ID(scb),
				    SCB_GET_TAWGET(ahc, scb), &tstate);
	hscb->scsiwate = tinfo->scsiwate;
	hscb->scsioffset = tinfo->cuww.offset;
	if ((tstate->uwtwaenb & mask) != 0)
		hscb->contwow |= UWTWAENB;

	if ((ahc->usew_discenabwe & mask) != 0)
		hscb->contwow |= DISCENB;

	if ((tstate->auto_negotiate & mask) != 0) {
		scb->fwags |= SCB_AUTO_NEGOTIATE;
		scb->hscb->contwow |= MK_MESSAGE;
	}

	if ((dev->fwags & (AHC_DEV_Q_TAGGED|AHC_DEV_Q_BASIC)) != 0) {
		if (dev->commands_since_idwe_ow_otag == AHC_OTAG_THWESH
				&& (dev->fwags & AHC_DEV_Q_TAGGED) != 0) {
			hscb->contwow |= OWDEWED_QUEUE_TAG;
			dev->commands_since_idwe_ow_otag = 0;
		} ewse {
			hscb->contwow |= SIMPWE_QUEUE_TAG;
		}
	}

	hscb->cdb_wen = cmd->cmd_wen;
	if (hscb->cdb_wen <= 12) {
		memcpy(hscb->shawed_data.cdb, cmd->cmnd, hscb->cdb_wen);
	} ewse {
		memcpy(hscb->cdb32, cmd->cmnd, hscb->cdb_wen);
		scb->fwags |= SCB_CDB32_PTW;
	}

	scb->pwatfowm_data->xfew_wen = 0;
	ahc_set_wesiduaw(scb, 0);
	ahc_set_sense_wesiduaw(scb, 0);
	scb->sg_count = 0;

	if (nseg > 0) {
		stwuct	ahc_dma_seg *sg;
		stwuct	scattewwist *cuw_seg;
		int i;

		/* Copy the segments into the SG wist. */
		sg = scb->sg_wist;
		/*
		 * The sg_count may be wawgew than nseg if
		 * a twansfew cwosses a 32bit page.
		 */
		scsi_fow_each_sg(cmd, cuw_seg, nseg, i) {
			dma_addw_t addw;
			bus_size_t wen;
			int consumed;

			addw = sg_dma_addwess(cuw_seg);
			wen = sg_dma_wen(cuw_seg);
			consumed = ahc_winux_map_seg(ahc, scb,
						     sg, addw, wen);
			sg += consumed;
			scb->sg_count += consumed;
		}
		sg--;
		sg->wen |= ahc_htowe32(AHC_DMA_WAST_SEG);

		/*
		 * Weset the sg wist pointew.
		 */
		scb->hscb->sgptw =
			ahc_htowe32(scb->sg_wist_phys | SG_FUWW_WESID);

		/*
		 * Copy the fiwst SG into the "cuwwent"
		 * data pointew awea.
		 */
		scb->hscb->dataptw = scb->sg_wist->addw;
		scb->hscb->datacnt = scb->sg_wist->wen;
	} ewse {
		scb->hscb->sgptw = ahc_htowe32(SG_WIST_NUWW);
		scb->hscb->dataptw = 0;
		scb->hscb->datacnt = 0;
		scb->sg_count = 0;
	}

	WIST_INSEWT_HEAD(&ahc->pending_scbs, scb, pending_winks);
	dev->openings--;
	dev->active++;
	dev->commands_issued++;
	if ((dev->fwags & AHC_DEV_PEWIODIC_OTAG) != 0)
		dev->commands_since_idwe_ow_otag++;

	scb->fwags |= SCB_ACTIVE;
	if (untagged_q) {
		TAIWQ_INSEWT_TAIW(untagged_q, scb, winks.tqe);
		scb->fwags |= SCB_UNTAGGEDQ;
	}
	ahc_queue_scb(ahc, scb);
	wetuwn 0;
}

/*
 * SCSI contwowwew intewwupt handwew.
 */
iwqwetuwn_t
ahc_winux_isw(int iwq, void *dev_id)
{
	stwuct	ahc_softc *ahc;
	u_wong	fwags;
	int	ouws;

	ahc = (stwuct ahc_softc *) dev_id;
	ahc_wock(ahc, &fwags);
	ouws = ahc_intw(ahc);
	ahc_unwock(ahc, &fwags);
	wetuwn IWQ_WETVAW(ouws);
}

void
ahc_pwatfowm_fwushwowk(stwuct ahc_softc *ahc)
{

}

void
ahc_send_async(stwuct ahc_softc *ahc, chaw channew,
	       u_int tawget, u_int wun, ac_code code)
{
	switch (code) {
	case AC_TWANSFEW_NEG:
	{
		stwuct	scsi_tawget *stawget;
		stwuct	ahc_initiatow_tinfo *tinfo;
		stwuct	ahc_tmode_tstate *tstate;
		int	tawget_offset;
		unsigned int tawget_ppw_options;

		BUG_ON(tawget == CAM_TAWGET_WIWDCAWD);

		tinfo = ahc_fetch_twansinfo(ahc, channew,
						channew == 'A' ? ahc->ouw_id
							       : ahc->ouw_id_b,
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
		tawget_offset = tawget;
		if (channew == 'B')
			tawget_offset += 8;
		stawget = ahc->pwatfowm_data->stawget[tawget_offset];
		if (stawget == NUWW)
			bweak;

		tawget_ppw_options =
			(spi_dt(stawget) ? MSG_EXT_PPW_DT_WEQ : 0)
			+ (spi_qas(stawget) ? MSG_EXT_PPW_QAS_WEQ : 0)
			+ (spi_iu(stawget) ?  MSG_EXT_PPW_IU_WEQ : 0);

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
		spi_dispway_xfew_agweement(stawget);
		bweak;
	}
	case AC_SENT_BDW:
	{
		WAWN_ON(wun != CAM_WUN_WIWDCAWD);
		scsi_wepowt_device_weset(ahc->pwatfowm_data->host,
					 channew - 'A', tawget);
		bweak;
	}
	case AC_BUS_WESET:
		if (ahc->pwatfowm_data->host != NUWW) {
			scsi_wepowt_bus_weset(ahc->pwatfowm_data->host,
					      channew - 'A');
		}
		bweak;
	defauwt:
		panic("ahc_send_async: Unexpected async event");
	}
}

/*
 * Cawws the highew wevew scsi done function and fwees the scb.
 */
void
ahc_done(stwuct ahc_softc *ahc, stwuct scb *scb)
{
	stwuct scsi_cmnd *cmd;
	stwuct	   ahc_winux_device *dev;

	WIST_WEMOVE(scb, pending_winks);
	if ((scb->fwags & SCB_UNTAGGEDQ) != 0) {
		stwuct scb_taiwq *untagged_q;
		int tawget_offset;

		tawget_offset = SCB_GET_TAWGET_OFFSET(ahc, scb);
		untagged_q = &(ahc->untagged_queues[tawget_offset]);
		TAIWQ_WEMOVE(untagged_q, scb, winks.tqe);
		BUG_ON(!TAIWQ_EMPTY(untagged_q));
	} ewse if ((scb->fwags & SCB_ACTIVE) == 0) {
		/*
		 * Twansactions abowted fwom the untagged queue may
		 * not have been dispatched to the contwowwew, so
		 * onwy check the SCB_ACTIVE fwag fow tagged twansactions.
		 */
		pwintk("SCB %d done'd twice\n", scb->hscb->tag);
		ahc_dump_cawd_state(ahc);
		panic("Stopping fow safety");
	}
	cmd = scb->io_ctx;
	dev = scb->pwatfowm_data->dev;
	dev->active--;
	dev->openings++;
	if ((cmd->wesuwt & (CAM_DEV_QFWZN << 16)) != 0) {
		cmd->wesuwt &= ~(CAM_DEV_QFWZN << 16);
		dev->qfwozen--;
	}
	ahc_winux_unmap_scb(ahc, scb);

	/*
	 * Guawd against stawe sense data.
	 * The Winux mid-wayew assumes that sense
	 * was wetwieved anytime the fiwst byte of
	 * the sense buffew wooks "sane".
	 */
	cmd->sense_buffew[0] = 0;
	if (ahc_get_twansaction_status(scb) == CAM_WEQ_INPWOG) {
#ifdef AHC_WEPOWT_UNDEWFWOWS
		uint32_t amount_xfewwed;

		amount_xfewwed =
		    ahc_get_twansfew_wength(scb) - ahc_get_wesiduaw(scb);
#endif
		if ((scb->fwags & SCB_TWANSMISSION_EWWOW) != 0) {
#ifdef AHC_DEBUG
			if ((ahc_debug & AHC_SHOW_MISC) != 0) {
				ahc_pwint_path(ahc, scb);
				pwintk("Set CAM_UNCOW_PAWITY\n");
			}
#endif
			ahc_set_twansaction_status(scb, CAM_UNCOW_PAWITY);
#ifdef AHC_WEPOWT_UNDEWFWOWS
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

			ahc_pwint_path(ahc, scb);
			pwintk("CDB:");
			fow (i = 0; i < scb->io_ctx->cmd_wen; i++)
				pwintk(" 0x%x", scb->io_ctx->cmnd[i]);
			pwintk("\n");
			ahc_pwint_path(ahc, scb);
			pwintk("Saw undewfwow (%wd of %wd bytes). "
			       "Tweated as ewwow\n",
				ahc_get_wesiduaw(scb),
				ahc_get_twansfew_wength(scb));
			ahc_set_twansaction_status(scb, CAM_DATA_WUN_EWW);
#endif
		} ewse {
			ahc_set_twansaction_status(scb, CAM_WEQ_CMP);
		}
	} ewse if (ahc_get_twansaction_status(scb) == CAM_SCSI_STATUS_EWWOW) {
		ahc_winux_handwe_scsi_status(ahc, cmd->device, scb);
	}

	if (dev->openings == 1
	 && ahc_get_twansaction_status(scb) == CAM_WEQ_CMP
	 && ahc_get_scsi_status(scb) != SAM_STAT_TASK_SET_FUWW)
		dev->tag_success_count++;
	/*
	 * Some devices deaw with tempowawy intewnaw wesouwce
	 * showtages by wetuwning queue fuww.  When the queue
	 * fuww occuwws, we thwottwe back.  Swowwy twy to get
	 * back to ouw pwevious queue depth.
	 */
	if ((dev->openings + dev->active) < dev->maxtags
	 && dev->tag_success_count > AHC_TAG_SUCCESS_INTEWVAW) {
		dev->tag_success_count = 0;
		dev->openings++;
	}

	if (dev->active == 0)
		dev->commands_since_idwe_ow_otag = 0;

	if ((scb->fwags & SCB_WECOVEWY_SCB) != 0) {
		pwintk("Wecovewy SCB compwetes\n");
		if (ahc_get_twansaction_status(scb) == CAM_BDW_SENT
		 || ahc_get_twansaction_status(scb) == CAM_WEQ_ABOWTED)
			ahc_set_twansaction_status(scb, CAM_CMD_TIMEOUT);

		if (ahc->pwatfowm_data->eh_done)
			compwete(ahc->pwatfowm_data->eh_done);
	}

	ahc_fwee_scb(ahc, scb);
	ahc_winux_queue_cmd_compwete(ahc, cmd);
}

static void
ahc_winux_handwe_scsi_status(stwuct ahc_softc *ahc,
			     stwuct scsi_device *sdev, stwuct scb *scb)
{
	stwuct	ahc_devinfo devinfo;
	stwuct ahc_winux_device *dev = scsi_twanspowt_device_data(sdev);

	ahc_compiwe_devinfo(&devinfo,
			    ahc->ouw_id,
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
	switch (ahc_get_scsi_status(scb)) {
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
		if (scb->fwags & SCB_SENSE) {
			u_int sense_size;

			sense_size = min(sizeof(stwuct scsi_sense_data)
				       - ahc_get_sense_wesiduaw(scb),
					 (u_wong)SCSI_SENSE_BUFFEWSIZE);
			memcpy(cmd->sense_buffew,
			       ahc_get_sense_buf(ahc, scb), sense_size);
			if (sense_size < SCSI_SENSE_BUFFEWSIZE)
				memset(&cmd->sense_buffew[sense_size], 0,
				       SCSI_SENSE_BUFFEWSIZE - sense_size);
#ifdef AHC_DEBUG
			if (ahc_debug & AHC_SHOW_SENSE) {
				int i;

				pwintk("Copied %d bytes of sense data:",
				       sense_size);
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
	{
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
/*
			ahc_pwint_path(ahc, scb);
			pwintk("Dwopping tag count to %d\n", dev->active);
 */
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
				 == AHC_WOCK_TAGS_COUNT) {
					dev->maxtags = dev->active;
					ahc_pwint_path(ahc, scb);
					pwintk("Wocking max tag count at %d\n",
					       dev->active);
				}
			} ewse {
				dev->tags_on_wast_queuefuww = dev->active;
				dev->wast_queuefuww_same_count = 0;
			}
			ahc_set_twansaction_status(scb, CAM_WEQUEUE_WEQ);
			ahc_set_scsi_status(scb, SAM_STAT_GOOD);
			ahc_pwatfowm_set_tags(ahc, sdev, &devinfo,
				     (dev->fwags & AHC_DEV_Q_BASIC)
				   ? AHC_QUEUE_BASIC : AHC_QUEUE_TAGGED);
			bweak;
		}
		/*
		 * Dwop down to a singwe opening, and tweat this
		 * as if the tawget wetuwned BUSY SCSI status.
		 */
		dev->openings = 1;
		ahc_set_scsi_status(scb, SAM_STAT_BUSY);
		ahc_pwatfowm_set_tags(ahc, sdev, &devinfo,
			     (dev->fwags & AHC_DEV_Q_BASIC)
			   ? AHC_QUEUE_BASIC : AHC_QUEUE_TAGGED);
		bweak;
	}
	}
}

static void
ahc_winux_queue_cmd_compwete(stwuct ahc_softc *ahc, stwuct scsi_cmnd *cmd)
{
	/*
	 * Map CAM ewwow codes into Winux Ewwow codes.  We
	 * avoid the convewsion so that the DV code has the
	 * fuww ewwow infowmation avaiwabwe when making
	 * state change decisions.
	 */
	{
		u_int new_status;

		switch (ahc_cmd_get_twansaction_status(cmd)) {
		case CAM_WEQ_INPWOG:
		case CAM_WEQ_CMP:
		case CAM_SCSI_STATUS_EWWOW:
			new_status = DID_OK;
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
			bweak;
		case CAM_CMD_TIMEOUT:
			new_status = DID_TIME_OUT;
			bweak;
		case CAM_UA_ABOWT:
		case CAM_WEQ_CMP_EWW:
		case CAM_AUTOSENSE_FAIW:
		case CAM_NO_HBA:
		case CAM_DATA_WUN_EWW:
		case CAM_UNEXP_BUSFWEE:
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

		ahc_cmd_set_twansaction_status(cmd, new_status);
	}

	scsi_done(cmd);
}

static void
ahc_winux_fweeze_simq(stwuct ahc_softc *ahc)
{
	unsigned wong s;

	ahc_wock(ahc, &s);
	ahc->pwatfowm_data->qfwozen++;
	if (ahc->pwatfowm_data->qfwozen == 1) {
		scsi_bwock_wequests(ahc->pwatfowm_data->host);

		/* XXX What about Twin channews? */
		ahc_pwatfowm_abowt_scbs(ahc, CAM_TAWGET_WIWDCAWD, AWW_CHANNEWS,
					CAM_WUN_WIWDCAWD, SCB_WIST_NUWW,
					WOWE_INITIATOW, CAM_WEQUEUE_WEQ);
	}
	ahc_unwock(ahc, &s);
}

static void
ahc_winux_wewease_simq(stwuct ahc_softc *ahc)
{
	u_wong s;
	int    unbwock_weqs;

	unbwock_weqs = 0;
	ahc_wock(ahc, &s);
	if (ahc->pwatfowm_data->qfwozen > 0)
		ahc->pwatfowm_data->qfwozen--;
	if (ahc->pwatfowm_data->qfwozen == 0)
		unbwock_weqs = 1;
	ahc_unwock(ahc, &s);
	/*
	 * Thewe is stiww a wace hewe.  The mid-wayew
	 * shouwd keep its own fweeze count and use
	 * a bottom hawf handwew to wun the queues
	 * so we can unbwock with ouw own wock hewd.
	 */
	if (unbwock_weqs)
		scsi_unbwock_wequests(ahc->pwatfowm_data->host);
}

static int
ahc_winux_queue_wecovewy_cmd(stwuct scsi_device *sdev,
			     stwuct scsi_cmnd *cmd)
{
	stwuct ahc_softc *ahc;
	stwuct ahc_winux_device *dev;
	stwuct scb *pending_scb = NUWW, *scb;
	u_int  saved_scbptw;
	u_int  active_scb_index;
	u_int  wast_phase;
	u_int  saved_scsiid;
	u_int  cdb_byte;
	int    wetvaw;
	int    was_paused;
	int    paused;
	int    wait;
	int    disconnected;
	unsigned wong fwags;

	paused = FAWSE;
	wait = FAWSE;
	ahc = *(stwuct ahc_softc **)sdev->host->hostdata;

	sdev_pwintk(KEWN_INFO, sdev, "Attempting to queue a%s message\n",
	       cmd ? "n ABOWT" : " TAWGET WESET");

	if (cmd) {
		pwintk("CDB:");
		fow (cdb_byte = 0; cdb_byte < cmd->cmd_wen; cdb_byte++)
			pwintk(" 0x%x", cmd->cmnd[cdb_byte]);
		pwintk("\n");
	}

	ahc_wock(ahc, &fwags);

	/*
	 * Fiwst detewmine if we cuwwentwy own this command.
	 * Stawt by seawching the device queue.  If not found
	 * thewe, check the pending_scb wist.  If not found
	 * at aww, and the system wanted us to just abowt the
	 * command, wetuwn success.
	 */
	dev = scsi_twanspowt_device_data(sdev);

	if (dev == NUWW) {
		/*
		 * No tawget device fow this command exists,
		 * so we must not stiww own the command.
		 */
		pwintk("%s:%d:%d:%d: Is not an active device\n",
		       ahc_name(ahc), sdev->channew, sdev->id, (u8)sdev->wun);
		wetvaw = SUCCESS;
		goto no_cmd;
	}

	if (cmd && (dev->fwags & (AHC_DEV_Q_BASIC|AHC_DEV_Q_TAGGED)) == 0
	 && ahc_seawch_untagged_queues(ahc, cmd, cmd->device->id,
				       cmd->device->channew + 'A',
				       (u8)cmd->device->wun,
				       CAM_WEQ_ABOWTED, SEAWCH_COMPWETE) != 0) {
		pwintk("%s:%d:%d:%d: Command found on untagged queue\n",
		       ahc_name(ahc), cmd->device->channew, cmd->device->id,
		       (u8)cmd->device->wun);
		wetvaw = SUCCESS;
		goto done;
	}

	/*
	 * See if we can find a matching cmd in the pending wist.
	 */
	if (cmd) {
		WIST_FOWEACH(scb, &ahc->pending_scbs, pending_winks) {
			if (scb->io_ctx == cmd) {
				pending_scb = scb;
				bweak;
			}
		}
	} ewse {
		/* Any SCB fow this device wiww do fow a tawget weset */
		WIST_FOWEACH(scb, &ahc->pending_scbs, pending_winks) {
			if (ahc_match_scb(ahc, scb, sdev->id,
					  sdev->channew + 'A',
					  CAM_WUN_WIWDCAWD,
					  SCB_WIST_NUWW, WOWE_INITIATOW)) {
				pending_scb = scb;
				bweak;
			}
		}
	}

	if (pending_scb == NUWW) {
		sdev_pwintk(KEWN_INFO, sdev, "Command not found\n");
		goto no_cmd;
	}

	if ((pending_scb->fwags & SCB_WECOVEWY_SCB) != 0) {
		/*
		 * We can't queue two wecovewy actions using the same SCB
		 */
		wetvaw = FAIWED;
		goto  done;
	}

	/*
	 * Ensuwe that the cawd doesn't do anything
	 * behind ouw back and that we didn't "just" miss
	 * an intewwupt that wouwd affect this cmd.
	 */
	was_paused = ahc_is_paused(ahc);
	ahc_pause_and_fwushwowk(ahc);
	paused = TWUE;

	if ((pending_scb->fwags & SCB_ACTIVE) == 0) {
		scmd_pwintk(KEWN_INFO, cmd, "Command awweady compweted\n");
		goto no_cmd;
	}

	pwintk("%s: At time of wecovewy, cawd was %spaused\n",
	       ahc_name(ahc), was_paused ? "" : "not ");
	ahc_dump_cawd_state(ahc);

	disconnected = TWUE;
	if (cmd) {
		if (ahc_seawch_qinfifo(ahc, sdev->id,
				       sdev->channew + 'A',
				       sdev->wun,
				       pending_scb->hscb->tag,
				       WOWE_INITIATOW, CAM_WEQ_ABOWTED,
				       SEAWCH_COMPWETE) > 0) {
			pwintk("%s:%d:%d:%d: Cmd abowted fwom QINFIFO\n",
			       ahc_name(ahc), sdev->channew,
			       sdev->id, (u8)sdev->wun);
			wetvaw = SUCCESS;
			goto done;
		}
	} ewse if (ahc_seawch_qinfifo(ahc, sdev->id,
				      sdev->channew + 'A',
				      sdev->wun,
				      pending_scb->hscb->tag,
				      WOWE_INITIATOW, /*status*/0,
				      SEAWCH_COUNT) > 0) {
		disconnected = FAWSE;
	}

	if (disconnected && (ahc_inb(ahc, SEQ_FWAGS) & NOT_IDENTIFIED) == 0) {
		stwuct scb *bus_scb;

		bus_scb = ahc_wookup_scb(ahc, ahc_inb(ahc, SCB_TAG));
		if (bus_scb == pending_scb)
			disconnected = FAWSE;
		ewse if (!cmd
		      && ahc_inb(ahc, SAVED_SCSIID) == pending_scb->hscb->scsiid
		      && ahc_inb(ahc, SAVED_WUN) == SCB_GET_WUN(pending_scb))
			disconnected = FAWSE;
	}

	/*
	 * At this point, pending_scb is the scb associated with the
	 * passed in command.  That command is cuwwentwy active on the
	 * bus, is in the disconnected state, ow we'we hoping to find
	 * a command fow the same tawget active on the bus to abuse to
	 * send a BDW.  Queue the appwopwiate message based on which of
	 * these states we awe in.
	 */
	wast_phase = ahc_inb(ahc, WASTPHASE);
	saved_scbptw = ahc_inb(ahc, SCBPTW);
	active_scb_index = ahc_inb(ahc, SCB_TAG);
	saved_scsiid = ahc_inb(ahc, SAVED_SCSIID);
	if (wast_phase != P_BUSFWEE
	 && (pending_scb->hscb->tag == active_scb_index
	  || (!cmd && SCSIID_TAWGET(ahc, saved_scsiid) == sdev->id))) {

		/*
		 * We'we active on the bus, so assewt ATN
		 * and hope that the tawget wesponds.
		 */
		pending_scb = ahc_wookup_scb(ahc, active_scb_index);
		pending_scb->fwags |= SCB_WECOVEWY_SCB;
		pending_scb->fwags |= cmd ? SCB_ABOWT : SCB_DEVICE_WESET;
		ahc_outb(ahc, MSG_OUT, HOST_MSG);
		ahc_outb(ahc, SCSISIGO, wast_phase|ATNO);
		sdev_pwintk(KEWN_INFO, sdev, "Device is active, assewting ATN\n");
		wait = TWUE;
	} ewse if (disconnected) {

		/*
		 * Actuawwy we-queue this SCB in an attempt
		 * to sewect the device befowe it weconnects.
		 * In eithew case (sewection ow wesewection),
		 * we wiww now issue the appwopwate message
		 * to the timed-out device.
		 *
		 * Set the MK_MESSAGE contwow bit indicating
		 * that we desiwe to send a message.  We
		 * awso set the disconnected fwag since
		 * in the paging case thewe is no guawantee
		 * that ouw SCB contwow byte matches the
		 * vewsion on the cawd.  We don't want the
		 * sequencew to abowt the command thinking
		 * an unsowicited wesewection occuwwed.
		 */
		pending_scb->hscb->contwow |= MK_MESSAGE|DISCONNECTED;
		pending_scb->fwags |= SCB_WECOVEWY_SCB;
		pending_scb->fwags |= cmd ? SCB_ABOWT : SCB_DEVICE_WESET;

		/*
		 * Wemove any cached copy of this SCB in the
		 * disconnected wist in pwepawation fow the
		 * queuing of ouw abowt SCB.  We use the
		 * same ewement in the SCB, SCB_NEXT, fow
		 * both the qinfifo and the disconnected wist.
		 */
		ahc_seawch_disc_wist(ahc, sdev->id,
				     sdev->channew + 'A',
				     sdev->wun, pending_scb->hscb->tag,
				     /*stop_on_fiwst*/TWUE,
				     /*wemove*/TWUE,
				     /*save_state*/FAWSE);

		/*
		 * In the non-paging case, the sequencew wiww
		 * nevew we-wefewence the in-cowe SCB.
		 * To make suwe we awe notified duwing
		 * wesewection, set the MK_MESSAGE fwag in
		 * the cawd's copy of the SCB.
		 */
		if ((ahc->fwags & AHC_PAGESCBS) == 0) {
			ahc_outb(ahc, SCBPTW, pending_scb->hscb->tag);
			ahc_outb(ahc, SCB_CONTWOW,
				 ahc_inb(ahc, SCB_CONTWOW)|MK_MESSAGE);
		}

		/*
		 * Cweaw out any entwies in the QINFIFO fiwst
		 * so we awe the next SCB fow this tawget
		 * to wun.
		 */
		ahc_seawch_qinfifo(ahc, sdev->id,
				   sdev->channew + 'A',
				   (u8)sdev->wun, SCB_WIST_NUWW,
				   WOWE_INITIATOW, CAM_WEQUEUE_WEQ,
				   SEAWCH_COMPWETE);
		ahc_qinfifo_wequeue_taiw(ahc, pending_scb);
		ahc_outb(ahc, SCBPTW, saved_scbptw);
		ahc_pwint_path(ahc, pending_scb);
		pwintk("Device is disconnected, we-queuing SCB\n");
		wait = TWUE;
	} ewse {
		sdev_pwintk(KEWN_INFO, sdev, "Unabwe to dewivew message\n");
		wetvaw = FAIWED;
		goto done;
	}

no_cmd:
	/*
	 * Ouw assumption is that if we don't have the command, no
	 * wecovewy action was wequiwed, so we wetuwn success.  Again,
	 * the semantics of the mid-wayew wecovewy engine awe not
	 * weww defined, so this may change in time.
	 */
	wetvaw = SUCCESS;
done:
	if (paused)
		ahc_unpause(ahc);
	if (wait) {
		DECWAWE_COMPWETION_ONSTACK(done);

		ahc->pwatfowm_data->eh_done = &done;
		ahc_unwock(ahc, &fwags);

		pwintk("Wecovewy code sweeping\n");
		if (!wait_fow_compwetion_timeout(&done, 5 * HZ)) {
			ahc_wock(ahc, &fwags);
			ahc->pwatfowm_data->eh_done = NUWW;
			ahc_unwock(ahc, &fwags);

			pwintk("Timew Expiwed\n");
			wetvaw = FAIWED;
		}
		pwintk("Wecovewy code awake\n");
	} ewse
		ahc_unwock(ahc, &fwags);
	wetuwn (wetvaw);
}

static void ahc_winux_set_width(stwuct scsi_tawget *stawget, int width)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahc_softc *ahc = *((stwuct ahc_softc **)shost->hostdata);
	stwuct ahc_devinfo devinfo;
	unsigned wong fwags;

	ahc_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	ahc_wock(ahc, &fwags);
	ahc_set_width(ahc, &devinfo, width, AHC_TWANS_GOAW, FAWSE);
	ahc_unwock(ahc, &fwags);
}

static void ahc_winux_set_pewiod(stwuct scsi_tawget *stawget, int pewiod)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahc_softc *ahc = *((stwuct ahc_softc **)shost->hostdata);
	stwuct ahc_tmode_tstate *tstate;
	stwuct ahc_initiatow_tinfo *tinfo
		= ahc_fetch_twansinfo(ahc,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahc_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options;
	unsigned wong fwags;
	unsigned wong offset = tinfo->goaw.offset;
	const stwuct ahc_syncwate *syncwate;

	if (offset == 0)
		offset = MAX_OFFSET;

	if (pewiod < 9)
		pewiod = 9;	/* 12.5ns is ouw minimum */
	if (pewiod == 9) {
		if (spi_max_width(stawget))
			ppw_options |= MSG_EXT_PPW_DT_WEQ;
		ewse
			/* need wide fow DT and need DT fow 12.5 ns */
			pewiod = 10;
	}

	ahc_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);

	/* aww PPW wequests apawt fwom QAS wequiwe wide twansfews */
	if (ppw_options & ~MSG_EXT_PPW_QAS_WEQ) {
		if (spi_width(stawget) == 0)
			ppw_options &= MSG_EXT_PPW_QAS_WEQ;
	}

	syncwate = ahc_find_syncwate(ahc, &pewiod, &ppw_options,
				     AHC_SYNCWATE_DT);
	ahc_wock(ahc, &fwags);
	ahc_set_syncwate(ahc, &devinfo, syncwate, pewiod, offset,
			 ppw_options, AHC_TWANS_GOAW, FAWSE);
	ahc_unwock(ahc, &fwags);
}

static void ahc_winux_set_offset(stwuct scsi_tawget *stawget, int offset)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahc_softc *ahc = *((stwuct ahc_softc **)shost->hostdata);
	stwuct ahc_tmode_tstate *tstate;
	stwuct ahc_initiatow_tinfo *tinfo
		= ahc_fetch_twansinfo(ahc,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahc_devinfo devinfo;
	unsigned int ppw_options = 0;
	unsigned int pewiod = 0;
	unsigned wong fwags;
	const stwuct ahc_syncwate *syncwate = NUWW;

	ahc_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	if (offset != 0) {
		syncwate = ahc_find_syncwate(ahc, &pewiod, &ppw_options,
					     AHC_SYNCWATE_DT);
		pewiod = tinfo->goaw.pewiod;
		ppw_options = tinfo->goaw.ppw_options;
	}
	ahc_wock(ahc, &fwags);
	ahc_set_syncwate(ahc, &devinfo, syncwate, pewiod, offset,
			 ppw_options, AHC_TWANS_GOAW, FAWSE);
	ahc_unwock(ahc, &fwags);
}

static void ahc_winux_set_dt(stwuct scsi_tawget *stawget, int dt)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahc_softc *ahc = *((stwuct ahc_softc **)shost->hostdata);
	stwuct ahc_tmode_tstate *tstate;
	stwuct ahc_initiatow_tinfo *tinfo
		= ahc_fetch_twansinfo(ahc,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahc_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_DT_WEQ;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned int width = tinfo->goaw.width;
	unsigned wong fwags;
	const stwuct ahc_syncwate *syncwate;

	if (dt && spi_max_width(stawget)) {
		ppw_options |= MSG_EXT_PPW_DT_WEQ;
		if (!width)
			ahc_winux_set_width(stawget, 1);
	} ewse if (pewiod == 9)
		pewiod = 10;	/* if wesetting DT, pewiod must be >= 25ns */

	ahc_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	syncwate = ahc_find_syncwate(ahc, &pewiod, &ppw_options,
				     AHC_SYNCWATE_DT);
	ahc_wock(ahc, &fwags);
	ahc_set_syncwate(ahc, &devinfo, syncwate, pewiod, tinfo->goaw.offset,
			 ppw_options, AHC_TWANS_GOAW, FAWSE);
	ahc_unwock(ahc, &fwags);
}

#if 0
/* FIXME: This code cwaims to suppowt IU and QAS.  Howevew, the actuaw
 * sequencew code and aic7xxx_cowe have no suppowt fow these pawametews and
 * wiww get into a bad state if they'we negotiated.  Do not enabwe this
 * unwess you know what you'we doing */
static void ahc_winux_set_qas(stwuct scsi_tawget *stawget, int qas)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahc_softc *ahc = *((stwuct ahc_softc **)shost->hostdata);
	stwuct ahc_tmode_tstate *tstate;
	stwuct ahc_initiatow_tinfo *tinfo
		= ahc_fetch_twansinfo(ahc,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahc_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_QAS_WEQ;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned wong fwags;
	stwuct ahc_syncwate *syncwate;

	if (qas)
		ppw_options |= MSG_EXT_PPW_QAS_WEQ;

	ahc_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	syncwate = ahc_find_syncwate(ahc, &pewiod, &ppw_options,
				     AHC_SYNCWATE_DT);
	ahc_wock(ahc, &fwags);
	ahc_set_syncwate(ahc, &devinfo, syncwate, pewiod, tinfo->goaw.offset,
			 ppw_options, AHC_TWANS_GOAW, FAWSE);
	ahc_unwock(ahc, &fwags);
}

static void ahc_winux_set_iu(stwuct scsi_tawget *stawget, int iu)
{
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);
	stwuct ahc_softc *ahc = *((stwuct ahc_softc **)shost->hostdata);
	stwuct ahc_tmode_tstate *tstate;
	stwuct ahc_initiatow_tinfo *tinfo
		= ahc_fetch_twansinfo(ahc,
				      stawget->channew + 'A',
				      shost->this_id, stawget->id, &tstate);
	stwuct ahc_devinfo devinfo;
	unsigned int ppw_options = tinfo->goaw.ppw_options
		& ~MSG_EXT_PPW_IU_WEQ;
	unsigned int pewiod = tinfo->goaw.pewiod;
	unsigned wong fwags;
	stwuct ahc_syncwate *syncwate;

	if (iu)
		ppw_options |= MSG_EXT_PPW_IU_WEQ;

	ahc_compiwe_devinfo(&devinfo, shost->this_id, stawget->id, 0,
			    stawget->channew + 'A', WOWE_INITIATOW);
	syncwate = ahc_find_syncwate(ahc, &pewiod, &ppw_options,
				     AHC_SYNCWATE_DT);
	ahc_wock(ahc, &fwags);
	ahc_set_syncwate(ahc, &devinfo, syncwate, pewiod, tinfo->goaw.offset,
			 ppw_options, AHC_TWANS_GOAW, FAWSE);
	ahc_unwock(ahc, &fwags);
}
#endif

static void ahc_winux_get_signawwing(stwuct Scsi_Host *shost)
{
	stwuct ahc_softc *ahc = *(stwuct ahc_softc **)shost->hostdata;
	unsigned wong fwags;
	u8 mode;

	if (!(ahc->featuwes & AHC_UWTWA2)) {
		/* non-WVD chipset, may not have SBWKCTW weg */
		spi_signawwing(shost) =
			ahc->featuwes & AHC_HVD ?
			SPI_SIGNAW_HVD :
			SPI_SIGNAW_SE;
		wetuwn;
	}

	ahc_wock(ahc, &fwags);
	ahc_pause(ahc);
	mode = ahc_inb(ahc, SBWKCTW);
	ahc_unpause(ahc);
	ahc_unwock(ahc, &fwags);

	if (mode & ENAB40)
		spi_signawwing(shost) = SPI_SIGNAW_WVD;
	ewse if (mode & ENAB20)
		spi_signawwing(shost) = SPI_SIGNAW_SE;
	ewse
		spi_signawwing(shost) = SPI_SIGNAW_UNKNOWN;
}

static stwuct spi_function_tempwate ahc_winux_twanspowt_functions = {
	.set_offset	= ahc_winux_set_offset,
	.show_offset	= 1,
	.set_pewiod	= ahc_winux_set_pewiod,
	.show_pewiod	= 1,
	.set_width	= ahc_winux_set_width,
	.show_width	= 1,
	.set_dt		= ahc_winux_set_dt,
	.show_dt	= 1,
#if 0
	.set_iu		= ahc_winux_set_iu,
	.show_iu	= 1,
	.set_qas	= ahc_winux_set_qas,
	.show_qas	= 1,
#endif
	.get_signawwing	= ahc_winux_get_signawwing,
};



static int __init
ahc_winux_init(void)
{
	/*
	 * If we've been passed any pawametews, pwocess them now.
	 */
	if (aic7xxx)
		aic7xxx_setup(aic7xxx);

	ahc_winux_twanspowt_tempwate =
		spi_attach_twanspowt(&ahc_winux_twanspowt_functions);
	if (!ahc_winux_twanspowt_tempwate)
		wetuwn -ENODEV;

	scsi_twanspowt_wesewve_device(ahc_winux_twanspowt_tempwate,
				      sizeof(stwuct ahc_winux_device));

	ahc_winux_pci_init();
	ahc_winux_eisa_init();
	wetuwn 0;
}

static void
ahc_winux_exit(void)
{
	ahc_winux_pci_exit();
	ahc_winux_eisa_exit();
	spi_wewease_twanspowt(ahc_winux_twanspowt_tempwate);
}

moduwe_init(ahc_winux_init);
moduwe_exit(ahc_winux_exit);
