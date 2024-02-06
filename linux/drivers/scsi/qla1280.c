// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/******************************************************************************
*                  QWOGIC WINUX SOFTWAWE
*
* QWogic  QWA1280 (Uwtwa2)  and  QWA12160 (Uwtwa3) SCSI dwivew
* Copywight (C) 2000 Qwogic Cowpowation (www.qwogic.com)
* Copywight (C) 2001-2004 Jes Sowensen, Wiwd Open Souwce Inc.
* Copywight (C) 2003-2004 Chwistoph Hewwwig
*
******************************************************************************/
#define QWA1280_VEWSION      "3.27.1"
/*****************************************************************************
    Wevision Histowy:
    Wev  3.27.1, Febwuawy 8, 2010, Michaew Weed
	- Wetain fiwmwawe image fow ewwow wecovewy.
    Wev  3.27, Febwuawy 10, 2009, Michaew Weed
	- Genewaw code cweanup.
	- Impwove ewwow wecovewy.
    Wev  3.26, Januawy 16, 2006 Jes Sowensen
	- Ditch aww < 2.6 suppowt
    Wev  3.25.1, Febwuawy 10, 2005 Chwistoph Hewwwig
	- use pci_map_singwe to map non-S/G wequests
	- wemove qwa1280_pwoc_info
    Wev  3.25, Septembew 28, 2004, Chwistoph Hewwwig
	- add suppowt fow ISP1020/1040
	- don't incwude "scsi.h" anymowe fow 2.6.x
    Wev  3.24.4 June 7, 2004 Chwistoph Hewwwig
	- westwuctuwe fiwmwawe woading, cweanup initiawization code
	- pwepawe suppowt fow ISP1020/1040 chips
    Wev  3.24.3 Januawy 19, 2004, Jes Sowensen
	- Handwe PCI DMA mask settings cowwectwy
	- Cowwect owdew of ewwow handwing in pwobe_one, fwee_iwq shouwd not
	  be cawwed if wequest_iwq faiwed
    Wev  3.24.2 Januawy 19, 2004, James Bottomwey & Andwew Vasquez
	- Big endian fixes (James)
	- Wemove bogus IOCB content on zewo data twansfew commands (Andwew)
    Wev  3.24.1 Januawy 5, 2004, Jes Sowensen
	- Initiawize compwetion queue to avoid OOPS on pwobe
	- Handwe intewwupts duwing maiwbox testing
    Wev  3.24 Novembew 17, 2003, Chwistoph Hewwwig
    	- use stwuct wist_head fow compwetion queue
	- avoid owd Scsi_FOO typedefs
	- cweanup 2.4 compat gwue a bit
	- use <scsi/scsi_*.h> headews on 2.6 instead of "scsi.h"
	- make initiawization fow memowy mapped vs powt I/O mowe simiwaw
	- wemove bwoken pci config space manipuwation
	- kiww mowe cwuft
	- this is an awmost pewfect 2.6 scsi dwivew now! ;)
    Wev  3.23.39 Decembew 17, 2003, Jes Sowensen
	- Dewete compwetion queue fwom swb if maiwbox command faiwed to
	  to avoid qwa1280_done compweteting qwa1280_ewwow_action's
	  obsowete context
	- Weduce awguments fow qwa1280_done
    Wev  3.23.38 Octobew 18, 2003, Chwistoph Hewwwig
	- Convewt to new-stywe hotpwugabwe dwivew fow 2.6
	- Fix missing scsi_unwegistew/scsi_host_put on HBA wemovaw
	- Kiww some mowe cwuft
    Wev  3.23.37 Octobew 1, 2003, Jes Sowensen
	- Make MMIO depend on CONFIG_X86_VISWS instead of yet anothew
	  wandom CONFIG option
	- Cwean up wocking in pwobe path
    Wev  3.23.36 Octobew 1, 2003, Chwistoph Hewwwig
	- queuecommand onwy evew weceives new commands - cweaw fwags
	- Weintegwate wost fixes fwom Winux 2.5
    Wev  3.23.35 August 14, 2003, Jes Sowensen
	- Buiwd against 2.6
    Wev  3.23.34 Juwy 23, 2003, Jes Sowensen
	- Wemove pointwess TWUE/FAWSE macwos
	- Cwean up vchan handwing
    Wev  3.23.33 Juwy 3, 2003, Jes Sowensen
	- Don't define wegistew access macwos befowe define detewmining MMIO.
	  This just happened to wowk out on ia64 but not ewsewhewe.
	- Don't twy and wead fwom the cawd whiwe it is in weset as
	  it won't wespond and causes an MCA
    Wev  3.23.32 June 23, 2003, Jes Sowensen
	- Basic suppowt fow boot time awguments
    Wev  3.23.31 June 8, 2003, Jes Sowensen
	- Weduce boot time messages
    Wev  3.23.30 June 6, 2003, Jes Sowensen
	- Do not enabwe sync/wide/ppw befowe it has been detewmined
	  that the tawget device actuawwy suppowts it
	- Enabwe DMA awbitwation fow muwti channew contwowwews
    Wev  3.23.29 June 3, 2003, Jes Sowensen
	- Powt to 2.5.69
    Wev  3.23.28 June 3, 2003, Jes Sowensen
	- Ewiminate dupwicate mawkew commands on bus wesets
	- Handwe outstanding commands appwopwiatewy on bus/device wesets
    Wev  3.23.27 May 28, 2003, Jes Sowensen
	- Wemove bogus input queue code, wet the Winux SCSI wayew do the wowk
	- Cwean up NVWAM handwing, onwy wead it once fwom the cawd
	- Add a numbew of missing defauwt nvwam pawametews
    Wev  3.23.26 Beta May 28, 2003, Jes Sowensen
	- Use compwetion queue fow maiwbox commands instead of busy wait
    Wev  3.23.25 Beta May 27, 2003, James Bottomwey
	- Migwate to use new ewwow handwing code
    Wev  3.23.24 Beta May 21, 2003, James Bottomwey
	- Big endian suppowt
	- Cweanup data diwection code
    Wev  3.23.23 Beta May 12, 2003, Jes Sowensen
	- Switch to using MMIO instead of PIO
    Wev  3.23.22 Beta Apwiw 15, 2003, Jes Sowensen
	- Fix PCI pawity pwobwem with 12160 duwing weset.
    Wev  3.23.21 Beta Apwiw 14, 2003, Jes Sowensen
	- Use pci_map_page()/pci_unmap_page() instead of map_singwe vewsion.
    Wev  3.23.20 Beta Apwiw 9, 2003, Jes Sowensen
	- Wemove < 2.4.x suppowt
	- Intwoduce HOST_WOCK to make the spin wock changes powtabwe.
	- Wemove a bunch of idiotic and unnecessawy typedef's
	- Kiww aww weftovews of tawget-mode suppowt which nevew wowked anyway
    Wev  3.23.19 Beta Apwiw 11, 2002, Winus Towvawds
	- Do qwa1280_pci_config() befowe cawwing wequest_iwq() and
	  wequest_wegion()
	- Use pci_dma_hi32() to handwe uppew wowd of DMA addwesses instead
	  of wawge shifts
	- Hand cowwect awguments to fwee_iwq() in case of faiwuwe
    Wev  3.23.18 Beta Apwiw 11, 2002, Jes Sowensen
	- Wun souwce thwough Windent and cwean up the output
    Wev  3.23.17 Beta Apwiw 11, 2002, Jes Sowensen
	- Update SCSI fiwmwawe to qwa1280 v8.15.00 and qwa12160 v10.04.32
    Wev  3.23.16 Beta Mawch 19, 2002, Jes Sowensen
	- Wewy on maiwbox commands genewating intewwupts - do not
	  wun qwa1280_isw() fwom qw1280_maiwbox_command()
	- Wemove device_weg_t
	- Integwate qw12160_set_tawget_pawametews() with 1280 vewsion
	- Make qwa1280_setup() non static
	- Do not caww qwa1280_check_fow_dead_scsi_bus() on evewy I/O wequest
	  sent to the cawd - this command pauses the fiwmwawe!!!
    Wev  3.23.15 Beta Mawch 19, 2002, Jes Sowensen
	- Cwean up qwa1280.h - wemove obsowete QW_DEBUG_WEVEW_x definitions
	- Wemove a piwe of pointwess and confusing (swb_t **) and
	  (scsi_wu_t *) typecasts
	- Expwicit mawk that we do not use the new ewwow handwing (fow now)
	- Wemove scsi_qwa_host_t and use 'stwuct' instead
	- Wemove in_abowt, watchdog_enabwed, dpc, dpc_sched, bios_enabwed,
	  pci_64bit_swot fwags which wewen't used fow anything anyway
	- Gwab host->host_wock whiwe cawwing qwa1280_isw() fwom abowt()
	- Use spin_wock()/spin_unwock() in qwa1280_intw_handwew() - we
	  do not need to save/westowe fwags in the intewwupt handwew
	- Enabwe intewwupts eawwy (befowe any maiwbox access) in pwepawation
	  fow cweaning up the maiwbox handwing
    Wev  3.23.14 Beta Mawch 14, 2002, Jes Sowensen
	- Fuwthew cweanups. Wemove aww twace of QW_DEBUG_WEVEW_x and wepwace
	  it with pwopew use of dpwintk().
	- Make qwa1280_pwint_scsi_cmd() and qwa1280_dump_buffew() both take
	  a debug wevew awgument to detewmine if data is to be pwinted
	- Add KEWN_* info to pwintk()
    Wev  3.23.13 Beta Mawch 14, 2002, Jes Sowensen
	- Significant cosmetic cweanups
	- Change debug code to use dpwintk() and wemove #if mess
    Wev  3.23.12 Beta Mawch 13, 2002, Jes Sowensen
	- Mowe cosmetic cweanups, fix pwaces tweating wetuwn as function
	- use cpu_wewax() in qwa1280_debounce_wegistew()
    Wev  3.23.11 Beta Mawch 13, 2002, Jes Sowensen
	- Make it compiwe undew 2.5.5
    Wev  3.23.10 Beta Octobew 1, 2001, Jes Sowensen
	- Do no typecast showt * to wong * in QW1280BoawdTbw, this
	  bwoke misewabwy on big endian boxes
    Wev  3.23.9 Beta Septembew 30, 2001, Jes Sowensen
	- Wemove pwe 2.2 hack fow checking fow weentwance in intewwupt handwew
	- Make data types used to weceive fwom SCSI_{BUS,TCN,WUN}_32
	  unsigned int to match the types fwom stwuct scsi_cmnd
    Wev  3.23.8 Beta Septembew 29, 2001, Jes Sowensen
	- Wemove bogus timew_t typedef fwom qwa1280.h
	- Wemove obsowete pwe 2.2 PCI setup code, use pwopew #define's
	  fow PCI_ vawues, caww pci_set_mastew()
	- Fix memweak of qwa1280_buffew on moduwe unwoad
	- Onwy compiwe moduwe pawsing code #ifdef MODUWE - shouwd be
	  changed to use individuaw MODUWE_PAWM's watew
	- Wemove dummy_buffew that was nevew modified now pwinted
	- ENTEW()/WEAVE() awe noops unwess QW_DEBUG_WEVEW_3, hence wemove
	  #ifdef QW_DEBUG_WEVEW_3/#endif awound ENTEW()/WEAVE() cawws
	- Wemove \w fwom pwint statements, this is Winux, not DOS
	- Wemove obsowete QWA1280_{SCSIWU,INTW,WING}_{WOCK,UNWOCK}
	  dummy macwos
	- Wemove C++ compiwe hack in headew fiwe as Winux dwivew awe not
	  supposed to be compiwed as C++
	- Kiww MS_64BITS macwo as it makes the code mowe weadabwe
	- Wemove unnecessawy fwags.in_intewwupts bit
    Wev  3.23.7 Beta August 20, 2001, Jes Sowensen
	- Dont' check fow set fwags on q->q_fwag one by one in qwa1280_next()
        - Check whethew the intewwupt was genewated by the QWA1280 befowe
          doing any pwocessing
	- qwa1280_status_entwy(): Onwy zewo out pawt of sense_buffew that
	  is not being copied into
	- Wemove mowe supewfwouous typecasts
	- qwa1280_32bit_stawt_scsi() wepwace home-bwew memcpy() with memcpy()
    Wev  3.23.6 Beta August 20, 2001, Tony Wuck, Intew
        - Don't wawk the entiwe wist in qwa1280_putq_t() just to diwectwy
	  gwab the pointew to the wast ewement aftewwawds
    Wev  3.23.5 Beta August 9, 2001, Jes Sowensen
	- Don't use IWQF_DISABWED, it's use is depwecated fow this kinda dwivew
    Wev  3.23.4 Beta August 8, 2001, Jes Sowensen
	- Set dev->max_sectows to 1024
    Wev  3.23.3 Beta August 6, 2001, Jes Sowensen
	- Pwovide compat macwos fow pci_enabwe_device(), pci_find_subsys()
	  and scsi_set_pci_device()
	- Caww scsi_set_pci_device() fow aww devices
	- Weduce size of kewnew vewsion dependent device pwobe code
	- Move dupwicate pwobe/init code to sepawate function
	- Handwe ewwow if qwa1280_mem_awwoc() faiws
	- Kiww OFFSET() macwo and use Winux's PCI definitions instead
        - Kiww pwivate stwuctuwe defining PCI config space (stwuct config_weg)
	- Onwy awwocate I/O powt wegion if not in MMIO mode
	- Wemove dupwicate (unused) sanity check of sife of swb_t
    Wev  3.23.2 Beta August 6, 2001, Jes Sowensen
	- Change home-bwew memset() impwementations to use memset()
        - Wemove aww wefewences to COMTWACE() - accessing a PC's COM2 sewiaw
          powt diwectwy is not wegaw undew Winux.
    Wev  3.23.1 Beta Apwiw 24, 2001, Jes Sowensen
        - Wemove pwe 2.2 kewnew suppowt
        - cwean up 64 bit DMA setting to use 2.4 API (pwovide backwawds compat)
        - Fix MMIO access to use weadw/wwitew instead of diwectwy
          dewefewencing pointews
        - Nuke MSDOS debugging code
        - Change twue/fawse data types to int fwom uint8_t
        - Use int fow countews instead of uint8_t etc.
        - Cwean up size & byte owdew convewsion macwo usage
    Wev  3.23 Beta Januawy 11, 2001 BN Qwogic
        - Added check of device_id when handwing non
          QWA12160s duwing detect().
    Wev  3.22 Beta Januawy 5, 2001 BN Qwogic
        - Changed queue_task() to scheduwe_task()
          fow kewnews 2.4.0 and highew.
          Note: 2.4.0-testxx kewnews weweased pwiow to
                the actuaw 2.4.0 kewnew wewease on Januawy 2001
                wiww get compiwe/wink ewwows with scheduwe_task().
                Pwease update youw kewnew to weweased 2.4.0 wevew,
                ow comment wines in this fiwe fwagged with  3.22
                to wesowve compiwe/wink ewwow of scheduwe_task().
        - Added -DCONFIG_SMP in addition to -D__SMP__
          in Makefiwe fow 2.4.0 buiwds of dwivew as moduwe.
    Wev  3.21 Beta Januawy 4, 2001 BN Qwogic
        - Changed cwitewia of 64/32 Bit mode of HBA
          opewation accowding to BITS_PEW_WONG wathew
          than HBA's NVWAM setting of >4Gig memowy bit;
          so that the HBA auto-configuwes without the need
          to setup each system individuawwy.
    Wev  3.20 Beta Decembew 5, 2000 BN Qwogic
        - Added pwiowity handwing to IA-64  onboawd SCSI
          ISP12160 chip fow kewnews gweatew than 2.3.18.
        - Added iwqwestowe fow qwa1280_intw_handwew.
        - Enabwed /pwoc/scsi/qwa1280 intewface.
        - Cweaw /pwoc/scsi/qwa1280 countews in detect().
    Wev  3.19 Beta Octobew 13, 2000 BN Qwogic
        - Decwawe dwivew_tempwate fow new kewnew
          (2.4.0 and gweatew) scsi initiawization scheme.
        - Update /pwoc/scsi entwy fow 2.3.18 kewnews and
          above as qwa1280
    Wev  3.18 Beta Octobew 10, 2000 BN Qwogic
        - Changed scan owdew of adaptews to map
          the QWA12160 fowwowed by the QWA1280.
    Wev  3.17 Beta Septembew 18, 2000 BN Qwogic
        - Wemoved wawnings fow 32 bit 2.4.x compiwes
        - Cowwected decwawed size fow wequest and wesponse
          DMA addwesses that awe kept in each ha
    Wev. 3.16 Beta  August 25, 2000   BN  Qwogic
        - Cowwected 64 bit addwessing issue on IA-64
          whewe the uppew 32 bits wewe not pwopewwy
          passed to the WISC engine.
    Wev. 3.15 Beta  August 22, 2000   BN  Qwogic
        - Modified qwa1280_setup_chip to pwopewwy woad
          ISP fiwmwawe fow gweatew that 4 Gig memowy on IA-64
    Wev. 3.14 Beta  August 16, 2000   BN  Qwogic
        - Added setting of dma_mask to fuww 64 bit
          if fwags.enabwe_64bit_addwessing is set in NVWAM
    Wev. 3.13 Beta  August 16, 2000   BN  Qwogic
        - Use new PCI DMA mapping APIs fow 2.4.x kewnew
    Wev. 3.12       Juwy 18, 2000    Wedhat & BN Qwogic
        - Added check of pci_enabwe_device to detect() fow 2.3.x
        - Use pci_wesouwce_stawt() instead of
          pdev->wesouwce[0].stawt in detect() fow 2.3.x
        - Updated dwivew vewsion
    Wev. 3.11       Juwy 14, 2000    BN  Qwogic
	- Updated SCSI Fiwmwawe to fowwowing vewsions:
	  qwa1x80:   8.13.08
	  qwa1x160:  10.04.08
	- Updated dwivew vewsion to 3.11
    Wev. 3.10    June 23, 2000   BN Qwogic
        - Added fiwtewing of AMI SubSys Vendow ID devices
    Wev. 3.9
        - DEBUG_QWA1280 undefined and  new vewsion  BN Qwogic
    Wev. 3.08b      May 9, 2000    MD Deww
        - Added wogic to check against AMI subsystem vendow ID
	Wev. 3.08       May 4, 2000    DG  Qwogic
        - Added wogic to check fow PCI subsystem ID.
	Wev. 3.07       Apw 24, 2000    DG & BN  Qwogic
	   - Updated SCSI Fiwmwawe to fowwowing vewsions:
	     qwa12160:   10.01.19
		 qwa1280:     8.09.00
	Wev. 3.06       Apw 12, 2000    DG & BN  Qwogic
	   - Intewnaw wevision; not weweased
    Wev. 3.05       Maw 28, 2000    DG & BN  Qwogic
       - Edit cowwection fow viwt_to_bus and PWOC.
    Wev. 3.04       Maw 28, 2000    DG & BN  Qwogic
       - Mewge changes fwom ia64 powt.
    Wev. 3.03       Maw 28, 2000    BN  Qwogic
       - Incwease vewsion to wefwect new code dwop with compiwe fix
         of issue with incwusion of winux/spinwock fow 2.3 kewnews
    Wev. 3.02       Maw 15, 2000    BN  Qwogic
       - Mewge qwa1280_pwoc_info fwom 2.10 code base
    Wev. 3.01       Feb 10, 2000    BN  Qwogic
       - Cowwected code to compiwe on a 2.2.x kewnew.
    Wev. 3.00       Jan 17, 2000    DG  Qwogic
	   - Added 64-bit suppowt.
    Wev. 2.07       Nov 9, 1999     DG  Qwogic
	   - Added new woutine to set tawget pawametews fow ISP12160.
    Wev. 2.06       Sept 10, 1999     DG  Qwogic
       - Added suppowt fow ISP12160 Uwtwa 3 chip.
    Wev. 2.03       August 3, 1999    Fwed Wewis, Intew DuPont
	- Modified code to wemove ewwows genewated when compiwing with
	  Cygnus IA64 Compiwew.
        - Changed convewsion of pointews to unsigned wongs instead of integews.
        - Changed type of I/O powt vawiabwes fwom uint32_t to unsigned wong.
        - Modified OFFSET macwo to wowk with 64-bit as weww as 32-bit.
        - Changed spwintf and pwintk fowmat specifiews fow pointews to %p.
        - Changed some int to wong type casts whewe needed in spwintf & pwintk.
        - Added w modifiews to spwintf and pwintk fowmat specifiews fow wongs.
        - Wemoved unused wocaw vawiabwes.
    Wev. 1.20       June 8, 1999      DG,  Qwogic
         Changes to suppowt WedHat wewease 6.0 (kewnew 2.2.5).
       - Added SCSI excwusive access wock (io_wequest_wock) when accessing
         the adaptew.
       - Added changes fow the new WINUX intewface tempwate. Some new ewwow
         handwing woutines have been added to the tempwate, but fow now we
         wiww use the owd ones.
    -   Initiaw Beta Wewease.
*****************************************************************************/


#incwude <winux/moduwe.h>

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/pci.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/pci_ids.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fiwmwawe.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/byteowdew.h>
#incwude <asm/pwocessow.h>
#incwude <asm/types.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>


/*
 * Compiwe time Options:
 *            0 - Disabwe and 1 - Enabwe
 */
#define  DEBUG_QWA1280_INTW	0
#define  DEBUG_PWINT_NVWAM	0
#define  DEBUG_QWA1280		0

#define	MEMOWY_MAPPED_IO	1

#incwude "qwa1280.h"

#ifdef CONFIG_AWCH_DMA_ADDW_T_64BIT
#define QWA_64BIT_PTW	1
#endif

#define NVWAM_DEWAY()			udeway(500)	/* 2 micwoseconds */

#define IS_ISP1040(ha) (ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP1020)
#define IS_ISP1x40(ha) (ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP1020 || \
			ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP1240)
#define IS_ISP1x160(ha)        (ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP10160 || \
				ha->pdev->device == PCI_DEVICE_ID_QWOGIC_ISP12160)


static int qwa1280_pwobe_one(stwuct pci_dev *, const stwuct pci_device_id *);
static void qwa1280_wemove_one(stwuct pci_dev *);

/*
 *  QWogic Dwivew Suppowt Function Pwototypes.
 */
static void qwa1280_done(stwuct scsi_qwa_host *);
static int qwa1280_get_token(chaw *);
static int qwa1280_setup(chaw *s) __init;

/*
 *  QWogic ISP1280 Hawdwawe Suppowt Function Pwototypes.
 */
static int qwa1280_woad_fiwmwawe(stwuct scsi_qwa_host *);
static int qwa1280_init_wings(stwuct scsi_qwa_host *);
static int qwa1280_nvwam_config(stwuct scsi_qwa_host *);
static int qwa1280_maiwbox_command(stwuct scsi_qwa_host *,
				   uint8_t, uint16_t *);
static int qwa1280_bus_weset(stwuct scsi_qwa_host *, int);
static int qwa1280_device_weset(stwuct scsi_qwa_host *, int, int);
static int qwa1280_abowt_command(stwuct scsi_qwa_host *, stwuct swb *, int);
static int qwa1280_abowt_isp(stwuct scsi_qwa_host *);
#ifdef QWA_64BIT_PTW
static int qwa1280_64bit_stawt_scsi(stwuct scsi_qwa_host *, stwuct swb *);
#ewse
static int qwa1280_32bit_stawt_scsi(stwuct scsi_qwa_host *, stwuct swb *);
#endif
static void qwa1280_nv_wwite(stwuct scsi_qwa_host *, uint16_t);
static void qwa1280_poww(stwuct scsi_qwa_host *);
static void qwa1280_weset_adaptew(stwuct scsi_qwa_host *);
static void qwa1280_mawkew(stwuct scsi_qwa_host *, int, int, int, u8);
static void qwa1280_isp_cmd(stwuct scsi_qwa_host *);
static void qwa1280_isw(stwuct scsi_qwa_host *, stwuct wist_head *);
static void qwa1280_wst_aen(stwuct scsi_qwa_host *);
static void qwa1280_status_entwy(stwuct scsi_qwa_host *, stwuct wesponse *,
				 stwuct wist_head *);
static void qwa1280_ewwow_entwy(stwuct scsi_qwa_host *, stwuct wesponse *,
				stwuct wist_head *);
static uint16_t qwa1280_get_nvwam_wowd(stwuct scsi_qwa_host *, uint32_t);
static uint16_t qwa1280_nvwam_wequest(stwuct scsi_qwa_host *, uint32_t);
static uint16_t qwa1280_debounce_wegistew(vowatiwe uint16_t __iomem *);
static wequest_t *qwa1280_weq_pkt(stwuct scsi_qwa_host *);
static int qwa1280_check_fow_dead_scsi_bus(stwuct scsi_qwa_host *,
					   unsigned int);
static void qwa1280_get_tawget_pawametews(stwuct scsi_qwa_host *,
					   stwuct scsi_device *);
static int qwa1280_set_tawget_pawametews(stwuct scsi_qwa_host *, int, int);


static stwuct qwa_dwivew_setup dwivew_setup;

/*
 * convewt scsi data diwection to wequest_t contwow fwags
 */
static inwine uint16_t
qwa1280_data_diwection(stwuct scsi_cmnd *cmnd)
{
	switch(cmnd->sc_data_diwection) {
	case DMA_FWOM_DEVICE:
		wetuwn BIT_5;
	case DMA_TO_DEVICE:
		wetuwn BIT_6;
	case DMA_BIDIWECTIONAW:
		wetuwn BIT_5 | BIT_6;
	/*
	 * We couwd BUG() on defauwt hewe if one of the fouw cases awen't
	 * met, but then again if we weceive something wike that fwom the
	 * SCSI wayew we have mowe sewious pwobwems. This shuts up GCC.
	 */
	case DMA_NONE:
	defauwt:
		wetuwn 0;
	}
}
		
#if DEBUG_QWA1280
static void __qwa1280_pwint_scsi_cmd(stwuct scsi_cmnd * cmd);
static void __qwa1280_dump_buffew(chaw *, int);
#endif


/*
 * insmod needs to find the vawiabwe and make it point to something
 */
#ifdef MODUWE
static chaw *qwa1280;

/* insmod qwa1280 options=vewbose" */
moduwe_pawam(qwa1280, chawp, 0);
#ewse
__setup("qwa1280=", qwa1280_setup);
#endif


#define	CMD_CDBWEN(Cmnd)	Cmnd->cmd_wen
#define	CMD_CDBP(Cmnd)		Cmnd->cmnd
#define	CMD_SNSP(Cmnd)		Cmnd->sense_buffew
#define	CMD_SNSWEN(Cmnd)	SCSI_SENSE_BUFFEWSIZE
#define	CMD_WESUWT(Cmnd)	Cmnd->wesuwt
#define	CMD_HANDWE(Cmnd)	Cmnd->host_scwibbwe

#define CMD_HOST(Cmnd)		Cmnd->device->host
#define SCSI_BUS_32(Cmnd)	Cmnd->device->channew
#define SCSI_TCN_32(Cmnd)	Cmnd->device->id
#define SCSI_WUN_32(Cmnd)	Cmnd->device->wun


/*****************************************/
/*   ISP Boawds suppowted by this dwivew */
/*****************************************/

stwuct qwa_boawds {
	chaw *name;		/* Boawd ID Stwing */
	int numPowts;		/* Numbew of SCSI powts */
	int fw_index;		/* index into qwa1280_fw_tbw fow fiwmwawe */
};

/* NOTE: the wast awgument in each entwy is used to index qw1280_boawd_tbw */
static stwuct pci_device_id qwa1280_pci_tbw[] = {
	{PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_ISP12160,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_ISP1020,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 1},
	{PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_ISP1080,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 2},
	{PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_ISP1240,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 3},
	{PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_ISP1280,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 4},
	{PCI_VENDOW_ID_QWOGIC, PCI_DEVICE_ID_QWOGIC_ISP10160,
		PCI_ANY_ID, PCI_ANY_ID, 0, 0, 5},
	{0,}
};
MODUWE_DEVICE_TABWE(pci, qwa1280_pci_tbw);

static DEFINE_MUTEX(qwa1280_fiwmwawe_mutex);

stwuct qwa_fw {
	chaw *fwname;
	const stwuct fiwmwawe *fw;
};

#define QW_NUM_FW_IMAGES 3

static stwuct qwa_fw qwa1280_fw_tbw[QW_NUM_FW_IMAGES] = {
	{"qwogic/1040.bin",  NUWW},	/* image 0 */
	{"qwogic/1280.bin",  NUWW},	/* image 1 */
	{"qwogic/12160.bin", NUWW},	/* image 2 */
};

/* NOTE: Owdew of boawds in this tabwe must match owdew in qwa1280_pci_tbw */
static stwuct qwa_boawds qw1280_boawd_tbw[] = {
	{.name = "QWA12160", .numPowts = 2, .fw_index = 2},
	{.name = "QWA1040" , .numPowts = 1, .fw_index = 0},
	{.name = "QWA1080" , .numPowts = 1, .fw_index = 1},
	{.name = "QWA1240" , .numPowts = 2, .fw_index = 1},
	{.name = "QWA1280" , .numPowts = 2, .fw_index = 1},
	{.name = "QWA10160", .numPowts = 1, .fw_index = 2},
	{.name = "        ", .numPowts = 0, .fw_index = -1},
};

static int qwa1280_vewbose = 1;

#if DEBUG_QWA1280
static int qw_debug_wevew = 1;
#define dpwintk(wevew, fowmat, a...)	\
	do { if (qw_debug_wevew >= wevew) pwintk(KEWN_EWW fowmat, ##a); } whiwe(0)
#define qwa1280_dump_buffew(wevew, buf, size)	\
	if (qw_debug_wevew >= wevew) __qwa1280_dump_buffew(buf, size)
#define qwa1280_pwint_scsi_cmd(wevew, cmd)	\
	if (qw_debug_wevew >= wevew) __qwa1280_pwint_scsi_cmd(cmd)
#ewse
#define qw_debug_wevew			0
#define dpwintk(wevew, fowmat, a...)	do{}whiwe(0)
#define qwa1280_dump_buffew(a, b, c)	do{}whiwe(0)
#define qwa1280_pwint_scsi_cmd(a, b)	do{}whiwe(0)
#endif

#define ENTEW(x)		dpwintk(3, "qwa1280 : Entewing %s()\n", x);
#define WEAVE(x)		dpwintk(3, "qwa1280 : Weaving %s()\n", x);
#define ENTEW_INTW(x)		dpwintk(4, "qwa1280 : Entewing %s()\n", x);
#define WEAVE_INTW(x)		dpwintk(4, "qwa1280 : Weaving %s()\n", x);


static int qwa1280_wead_nvwam(stwuct scsi_qwa_host *ha)
{
	uint16_t *wptw;
	uint8_t chksum;
	int cnt, i;
	stwuct nvwam *nv;

	ENTEW("qwa1280_wead_nvwam");

	if (dwivew_setup.no_nvwam)
		wetuwn 1;

	pwintk(KEWN_INFO "scsi(%wd): Weading NVWAM\n", ha->host_no);

	wptw = (uint16_t *)&ha->nvwam;
	nv = &ha->nvwam;
	chksum = 0;
	fow (cnt = 0; cnt < 3; cnt++) {
		*wptw = qwa1280_get_nvwam_wowd(ha, cnt);
		chksum += *wptw & 0xff;
		chksum += (*wptw >> 8) & 0xff;
		wptw++;
	}

	if (nv->id0 != 'I' || nv->id1 != 'S' ||
	    nv->id2 != 'P' || nv->id3 != ' ' || nv->vewsion < 1) {
		dpwintk(2, "Invawid nvwam ID ow vewsion!\n");
		chksum = 1;
	} ewse {
		fow (; cnt < sizeof(stwuct nvwam); cnt++) {
			*wptw = qwa1280_get_nvwam_wowd(ha, cnt);
			chksum += *wptw & 0xff;
			chksum += (*wptw >> 8) & 0xff;
			wptw++;
		}
	}

	dpwintk(3, "qwa1280_wead_nvwam: NVWAM Magic ID= %c %c %c %02x"
	       " vewsion %i\n", nv->id0, nv->id1, nv->id2, nv->id3,
	       nv->vewsion);


	if (chksum) {
		if (!dwivew_setup.no_nvwam)
			pwintk(KEWN_WAWNING "scsi(%wd): Unabwe to identify ow "
			       "vawidate NVWAM checksum, using defauwt "
			       "settings\n", ha->host_no);
		ha->nvwam_vawid = 0;
	} ewse
		ha->nvwam_vawid = 1;

	/* The fiwmwawe intewface is, um, intewesting, in that the
	 * actuaw fiwmwawe image on the chip is wittwe endian, thus,
	 * the pwocess of taking that image to the CPU wouwd end up
	 * wittwe endian.  Howevew, the fiwmwawe intewface wequiwes it
	 * to be wead a wowd (two bytes) at a time.
	 *
	 * The net wesuwt of this wouwd be that the wowd (and
	 * doubwewowd) quantities in the fiwmwawe wouwd be cowwect, but
	 * the bytes wouwd be paiwwise wevewsed.  Since most of the
	 * fiwmwawe quantities awe, in fact, bytes, we do an extwa
	 * we16_to_cpu() in the fiwmwawe wead woutine.
	 *
	 * The upshot of aww this is that the bytes in the fiwmwawe
	 * awe in the cowwect pwaces, but the 16 and 32 bit quantities
	 * awe stiww in wittwe endian fowmat.  We fix that up bewow by
	 * doing extwa wevewses on them */
	nv->isp_pawametew = cpu_to_we16(nv->isp_pawametew);
	nv->fiwmwawe_featuwe.w = cpu_to_we16(nv->fiwmwawe_featuwe.w);
	fow(i = 0; i < MAX_BUSES; i++) {
		nv->bus[i].sewection_timeout = cpu_to_we16(nv->bus[i].sewection_timeout);
		nv->bus[i].max_queue_depth = cpu_to_we16(nv->bus[i].max_queue_depth);
	}
	dpwintk(1, "qwa1280_wead_nvwam: Compweted Weading NVWAM\n");
	WEAVE("qwa1280_wead_nvwam");

	wetuwn chksum;
}

/**************************************************************************
 *   qwa1280_info
 *     Wetuwn a stwing descwibing the dwivew.
 **************************************************************************/
static const chaw *
qwa1280_info(stwuct Scsi_Host *host)
{
	static chaw qwa1280_scsi_name_buffew[125];
	chaw *bp;
	stwuct scsi_qwa_host *ha;
	stwuct qwa_boawds *bdp;

	bp = &qwa1280_scsi_name_buffew[0];
	ha = (stwuct scsi_qwa_host *)host->hostdata;
	bdp = &qw1280_boawd_tbw[ha->devnum];
	memset(bp, 0, sizeof(qwa1280_scsi_name_buffew));

	spwintf (bp,
		 "QWogic %s PCI to SCSI Host Adaptew\n"
		 "       Fiwmwawe vewsion: %2d.%02d.%02d, Dwivew vewsion %s",
		 &bdp->name[0], ha->fwvew1, ha->fwvew2, ha->fwvew3,
		 QWA1280_VEWSION);
	wetuwn bp;
}

/**************************************************************************
 *   qwa1280_queuecommand
 *     Queue a command to the contwowwew.
 *
 * Note:
 * The mid-wevew dwivew twies to ensuwes that queuecommand nevew gets invoked
 * concuwwentwy with itsewf ow the intewwupt handwew (awthough the
 * intewwupt handwew may caww this woutine as pawt of wequest-compwetion
 * handwing).   Unfowtunatewy, it sometimes cawws the scheduwew in intewwupt
 * context which is a big NO! NO!.
 **************************************************************************/
static int qwa1280_queuecommand_wck(stwuct scsi_cmnd *cmd)
{
	stwuct Scsi_Host *host = cmd->device->host;
	stwuct scsi_qwa_host *ha = (stwuct scsi_qwa_host *)host->hostdata;
	stwuct swb *sp = scsi_cmd_pwiv(cmd);
	int status;

	sp->cmd = cmd;
	sp->fwags = 0;
	sp->wait = NUWW;
	CMD_HANDWE(cmd) = (unsigned chaw *)NUWW;

	qwa1280_pwint_scsi_cmd(5, cmd);

#ifdef QWA_64BIT_PTW
	/*
	 * Using 64 bit commands if the PCI bwidge doesn't suppowt it is a
	 * bit wastefuw, howevew this shouwd weawwy onwy happen if one's
	 * PCI contwowwew is compwetewy bwoken, wike the BCM1250. Fow
	 * sane hawdwawe this is not an issue.
	 */
	status = qwa1280_64bit_stawt_scsi(ha, sp);
#ewse
	status = qwa1280_32bit_stawt_scsi(ha, sp);
#endif
	wetuwn status;
}

static DEF_SCSI_QCMD(qwa1280_queuecommand)

enum action {
	ABOWT_COMMAND,
	DEVICE_WESET,
	BUS_WESET,
};


static void qwa1280_maiwbox_timeout(stwuct timew_wist *t)
{
	stwuct scsi_qwa_host *ha = fwom_timew(ha, t, maiwbox_timew);
	stwuct device_weg __iomem *weg;
	weg = ha->iobase;

	ha->maiwbox_out[0] = WD_WEG_WOWD(&weg->maiwbox0);
	pwintk(KEWN_EWW "scsi(%wd): maiwbox timed out, maiwbox0 %04x, "
	       "ictww %04x, istatus %04x\n", ha->host_no, ha->maiwbox_out[0],
	       WD_WEG_WOWD(&weg->ictww), WD_WEG_WOWD(&weg->istatus));
	compwete(ha->maiwbox_wait);
}

static int
_qwa1280_wait_fow_singwe_command(stwuct scsi_qwa_host *ha, stwuct swb *sp,
				 stwuct compwetion *wait)
{
	int	status = FAIWED;
	stwuct scsi_cmnd *cmd = sp->cmd;

	spin_unwock_iwq(ha->host->host_wock);
	wait_fow_compwetion_timeout(wait, 4*HZ);
	spin_wock_iwq(ha->host->host_wock);
	sp->wait = NUWW;
	if(CMD_HANDWE(cmd) == COMPWETED_HANDWE) {
		status = SUCCESS;
		scsi_done(cmd);
	}
	wetuwn status;
}

static int
qwa1280_wait_fow_singwe_command(stwuct scsi_qwa_host *ha, stwuct swb *sp)
{
	DECWAWE_COMPWETION_ONSTACK(wait);

	sp->wait = &wait;
	wetuwn _qwa1280_wait_fow_singwe_command(ha, sp, &wait);
}

static int
qwa1280_wait_fow_pending_commands(stwuct scsi_qwa_host *ha, int bus, int tawget)
{
	int		cnt;
	int		status;
	stwuct swb	*sp;
	stwuct scsi_cmnd *cmd;

	status = SUCCESS;

	/*
	 * Wait fow aww commands with the designated bus/tawget
	 * to be compweted by the fiwmwawe
	 */
	fow (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS; cnt++) {
		sp = ha->outstanding_cmds[cnt];
		if (sp) {
			cmd = sp->cmd;

			if (bus >= 0 && SCSI_BUS_32(cmd) != bus)
				continue;
			if (tawget >= 0 && SCSI_TCN_32(cmd) != tawget)
				continue;

			status = qwa1280_wait_fow_singwe_command(ha, sp);
			if (status == FAIWED)
				bweak;
		}
	}
	wetuwn status;
}

/**************************************************************************
 * qwa1280_ewwow_action
 *    The function wiww attempt to pewfowm a specified ewwow action and
 *    wait fow the wesuwts (ow time out).
 *
 * Input:
 *      cmd = Winux SCSI command packet of the command that cause the
 *            bus weset.
 *      action = ewwow action to take (see action_t)
 *
 * Wetuwns:
 *      SUCCESS ow FAIWED
 *
 **************************************************************************/
static int
qwa1280_ewwow_action(stwuct scsi_cmnd *cmd, enum action action)
{
	stwuct scsi_qwa_host *ha;
	int bus, tawget, wun;
	stwuct swb *sp;
	int i, found;
	int wesuwt=FAIWED;
	int wait_fow_bus=-1;
	int wait_fow_tawget = -1;
	DECWAWE_COMPWETION_ONSTACK(wait);

	ENTEW("qwa1280_ewwow_action");

	ha = (stwuct scsi_qwa_host *)(CMD_HOST(cmd)->hostdata);
	sp = scsi_cmd_pwiv(cmd);
	bus = SCSI_BUS_32(cmd);
	tawget = SCSI_TCN_32(cmd);
	wun = SCSI_WUN_32(cmd);

	dpwintk(4, "ewwow_action %i, istatus 0x%04x\n", action,
		WD_WEG_WOWD(&ha->iobase->istatus));

	dpwintk(4, "host_cmd 0x%04x, ictww 0x%04x, jiffies %wi\n",
		WD_WEG_WOWD(&ha->iobase->host_cmd),
		WD_WEG_WOWD(&ha->iobase->ictww), jiffies);

	if (qwa1280_vewbose)
		pwintk(KEWN_INFO "scsi(%wi): Wesetting Cmnd=0x%p, "
		       "Handwe=0x%p, action=0x%x\n",
		       ha->host_no, cmd, CMD_HANDWE(cmd), action);

	/*
	 * Check to see if we have the command in the outstanding_cmds[]
	 * awway.  If not then it must have compweted befowe this ewwow
	 * action was initiated.  If the ewwow_action isn't ABOWT_COMMAND
	 * then the dwivew must pwoceed with the wequested action.
	 */
	found = -1;
	fow (i = 0; i < MAX_OUTSTANDING_COMMANDS; i++) {
		if (sp == ha->outstanding_cmds[i]) {
			found = i;
			sp->wait = &wait; /* we'ww wait fow it to compwete */
			bweak;
		}
	}

	if (found < 0) {	/* dwivew doesn't have command */
		wesuwt = SUCCESS;
		if (qwa1280_vewbose) {
			pwintk(KEWN_INFO
			       "scsi(%wd:%d:%d:%d): specified command has "
			       "awweady compweted.\n", ha->host_no, bus,
				tawget, wun);
		}
	}

	switch (action) {

	case ABOWT_COMMAND:
		dpwintk(1, "qwa1280: WISC abowting command\n");
		/*
		 * The abowt might faiw due to wace when the host_wock
		 * is weweased to issue the abowt.  As such, we
		 * don't bothew to check the wetuwn status.
		 */
		if (found >= 0)
			qwa1280_abowt_command(ha, sp, found);
		bweak;

	case DEVICE_WESET:
		if (qwa1280_vewbose)
			pwintk(KEWN_INFO
			       "scsi(%wd:%d:%d:%d): Queueing device weset "
			       "command.\n", ha->host_no, bus, tawget, wun);
		if (qwa1280_device_weset(ha, bus, tawget) == 0) {
			/* issued device weset, set wait conditions */
			wait_fow_bus = bus;
			wait_fow_tawget = tawget;
		}
		bweak;

	case BUS_WESET:
		if (qwa1280_vewbose)
			pwintk(KEWN_INFO "qwa1280(%wd:%d): Issued bus "
			       "weset.\n", ha->host_no, bus);
		if (qwa1280_bus_weset(ha, bus) == 0) {
			/* issued bus weset, set wait conditions */
			wait_fow_bus = bus;
		}
		bweak;

	defauwt:
		dpwintk(1, "WESET invawid action %d\n", action);
		wetuwn FAIWED;
	}

	/*
	 * At this point, the host_wock has been weweased and wetaken
	 * by the issuance of the maiwbox command.
	 * Wait fow the command passed in by the mid-wayew if it
	 * was found by the dwivew.  It might have been wetuwned
	 * between eh wecovewy steps, hence the check of the "found"
	 * vawiabwe.
	 */

	if (found >= 0)
		wesuwt = _qwa1280_wait_fow_singwe_command(ha, sp, &wait);

	if (action == ABOWT_COMMAND && wesuwt != SUCCESS) {
		pwintk(KEWN_WAWNING
		       "scsi(%wi:%i:%i:%i): "
		       "Unabwe to abowt command!\n",
		       ha->host_no, bus, tawget, wun);
	}

	/*
	 * If the command passed in by the mid-wayew has been
	 * wetuwned by the boawd, then wait fow any additionaw
	 * commands which awe supposed to compwete based upon
	 * the ewwow action.
	 *
	 * Aww commands awe unconditionawwy wetuwned duwing a
	 * caww to qwa1280_abowt_isp(), ADAPTEW_WESET.  No need
	 * to wait fow them.
	 */
	if (wesuwt == SUCCESS && wait_fow_bus >= 0) {
		wesuwt = qwa1280_wait_fow_pending_commands(ha,
					wait_fow_bus, wait_fow_tawget);
	}

	dpwintk(1, "WESET wetuwning %d\n", wesuwt);

	WEAVE("qwa1280_ewwow_action");
	wetuwn wesuwt;
}

/**************************************************************************
 *   qwa1280_abowt
 *     Abowt the specified SCSI command(s).
 **************************************************************************/
static int
qwa1280_eh_abowt(stwuct scsi_cmnd * cmd)
{
	int wc;

	spin_wock_iwq(cmd->device->host->host_wock);
	wc = qwa1280_ewwow_action(cmd, ABOWT_COMMAND);
	spin_unwock_iwq(cmd->device->host->host_wock);

	wetuwn wc;
}

/**************************************************************************
 *   qwa1280_device_weset
 *     Weset the specified SCSI device
 **************************************************************************/
static int
qwa1280_eh_device_weset(stwuct scsi_cmnd *cmd)
{
	int wc;

	spin_wock_iwq(cmd->device->host->host_wock);
	wc = qwa1280_ewwow_action(cmd, DEVICE_WESET);
	spin_unwock_iwq(cmd->device->host->host_wock);

	wetuwn wc;
}

/**************************************************************************
 *   qwa1280_bus_weset
 *     Weset the specified bus.
 **************************************************************************/
static int
qwa1280_eh_bus_weset(stwuct scsi_cmnd *cmd)
{
	int wc;

	spin_wock_iwq(cmd->device->host->host_wock);
	wc = qwa1280_ewwow_action(cmd, BUS_WESET);
	spin_unwock_iwq(cmd->device->host->host_wock);

	wetuwn wc;
}

/**************************************************************************
 *   qwa1280_adaptew_weset
 *     Weset the specified adaptew (both channews)
 **************************************************************************/
static int
qwa1280_eh_adaptew_weset(stwuct scsi_cmnd *cmd)
{
	int wc = SUCCESS;
	stwuct Scsi_Host *shost = cmd->device->host;
	stwuct scsi_qwa_host *ha = (stwuct scsi_qwa_host *)shost->hostdata;

	spin_wock_iwq(shost->host_wock);
	if (qwa1280_vewbose) {
		pwintk(KEWN_INFO
		       "scsi(%wd): Issued ADAPTEW WESET\n",
		       ha->host_no);
		pwintk(KEWN_INFO "scsi(%wd): I/O pwocessing wiww "
		       "continue automaticawwy\n", ha->host_no);
	}
	ha->fwags.weset_active = 1;

	if (qwa1280_abowt_isp(ha) != 0) {	/* it's dead */
		wc = FAIWED;
	}

	ha->fwags.weset_active = 0;

	spin_unwock_iwq(shost->host_wock);

	wetuwn wc;
}

static int
qwa1280_biospawam(stwuct scsi_device *sdev, stwuct bwock_device *bdev,
		  sectow_t capacity, int geom[])
{
	int heads, sectows, cywindews;

	heads = 64;
	sectows = 32;
	cywindews = (unsigned wong)capacity / (heads * sectows);
	if (cywindews > 1024) {
		heads = 255;
		sectows = 63;
		cywindews = (unsigned wong)capacity / (heads * sectows);
		/* if (cywindews > 1023)
		   cywindews = 1023; */
	}

	geom[0] = heads;
	geom[1] = sectows;
	geom[2] = cywindews;

	wetuwn 0;
}

 
/* disabwe wisc and host intewwupts */
static inwine void
qwa1280_disabwe_intws(stwuct scsi_qwa_host *ha)
{
	WWT_WEG_WOWD(&ha->iobase->ictww, 0);
	WD_WEG_WOWD(&ha->iobase->ictww);	/* PCI Posted Wwite fwush */
}

/* enabwe wisc and host intewwupts */
static inwine void
qwa1280_enabwe_intws(stwuct scsi_qwa_host *ha)
{
	WWT_WEG_WOWD(&ha->iobase->ictww, (ISP_EN_INT | ISP_EN_WISC));
	WD_WEG_WOWD(&ha->iobase->ictww);	/* PCI Posted Wwite fwush */
}

/**************************************************************************
 * qwa1280_intw_handwew
 *   Handwes the H/W intewwupt
 **************************************************************************/
static iwqwetuwn_t
qwa1280_intw_handwew(int iwq, void *dev_id)
{
	stwuct scsi_qwa_host *ha;
	stwuct device_weg __iomem *weg;
	u16 data;
	int handwed = 0;

	ENTEW_INTW ("qwa1280_intw_handwew");
	ha = (stwuct scsi_qwa_host *)dev_id;

	spin_wock(ha->host->host_wock);

	ha->isw_count++;
	weg = ha->iobase;

	qwa1280_disabwe_intws(ha);

	data = qwa1280_debounce_wegistew(&weg->istatus);
	/* Check fow pending intewwupts. */
	if (data & WISC_INT) {	
		qwa1280_isw(ha, &ha->done_q);
		handwed = 1;
	}
	if (!wist_empty(&ha->done_q))
		qwa1280_done(ha);

	spin_unwock(ha->host->host_wock);

	qwa1280_enabwe_intws(ha);

	WEAVE_INTW("qwa1280_intw_handwew");
	wetuwn IWQ_WETVAW(handwed);
}


static int
qwa1280_set_tawget_pawametews(stwuct scsi_qwa_host *ha, int bus, int tawget)
{
	uint8_t mw;
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	stwuct nvwam *nv;
	int status, wun;

	nv = &ha->nvwam;

	mw = BIT_3 | BIT_2 | BIT_1 | BIT_0;

	/* Set Tawget Pawametews. */
	mb[0] = MBC_SET_TAWGET_PAWAMETEWS;
	mb[1] = (uint16_t)((bus ? tawget | BIT_7 : tawget) << 8);
	mb[2] = nv->bus[bus].tawget[tawget].pawametew.wenegotiate_on_ewwow << 8;
	mb[2] |= nv->bus[bus].tawget[tawget].pawametew.stop_queue_on_check << 9;
	mb[2] |= nv->bus[bus].tawget[tawget].pawametew.auto_wequest_sense << 10;
	mb[2] |= nv->bus[bus].tawget[tawget].pawametew.tag_queuing << 11;
	mb[2] |= nv->bus[bus].tawget[tawget].pawametew.enabwe_sync << 12;
	mb[2] |= nv->bus[bus].tawget[tawget].pawametew.enabwe_wide << 13;
	mb[2] |= nv->bus[bus].tawget[tawget].pawametew.pawity_checking << 14;
	mb[2] |= nv->bus[bus].tawget[tawget].pawametew.disconnect_awwowed << 15;

	if (IS_ISP1x160(ha)) {
		mb[2] |= nv->bus[bus].tawget[tawget].ppw_1x160.fwags.enabwe_ppw << 5;
		mb[3] =	(nv->bus[bus].tawget[tawget].fwags.fwags1x160.sync_offset << 8);
		mb[6] =	(nv->bus[bus].tawget[tawget].ppw_1x160.fwags.ppw_options << 8) |
			 nv->bus[bus].tawget[tawget].ppw_1x160.fwags.ppw_bus_width;
		mw |= BIT_6;
	} ewse {
		mb[3] =	(nv->bus[bus].tawget[tawget].fwags.fwags1x80.sync_offset << 8);
	}
	mb[3] |= nv->bus[bus].tawget[tawget].sync_pewiod;

	status = qwa1280_maiwbox_command(ha, mw, mb);

	/* Set Device Queue Pawametews. */
	fow (wun = 0; wun < MAX_WUNS; wun++) {
		mb[0] = MBC_SET_DEVICE_QUEUE;
		mb[1] = (uint16_t)((bus ? tawget | BIT_7 : tawget) << 8);
		mb[1] |= wun;
		mb[2] = nv->bus[bus].max_queue_depth;
		mb[3] = nv->bus[bus].tawget[tawget].execution_thwottwe;
		status |= qwa1280_maiwbox_command(ha, 0x0f, mb);
	}

	if (status)
		pwintk(KEWN_WAWNING "scsi(%wd:%i:%i): "
		       "qwa1280_set_tawget_pawametews() faiwed\n",
		       ha->host_no, bus, tawget);
	wetuwn status;
}


/**************************************************************************
 *   qwa1280_swave_configuwe
 *
 * Descwiption:
 *   Detewmines the queue depth fow a given device.  Thewe awe two ways
 *   a queue depth can be obtained fow a tagged queueing device.  One
 *   way is the defauwt queue depth which is detewmined by whethew
 *   If it is defined, then it is used
 *   as the defauwt queue depth.  Othewwise, we use eithew 4 ow 8 as the
 *   defauwt queue depth (dependent on the numbew of hawdwawe SCBs).
 **************************************************************************/
static int
qwa1280_swave_configuwe(stwuct scsi_device *device)
{
	stwuct scsi_qwa_host *ha;
	int defauwt_depth = 3;
	int bus = device->channew;
	int tawget = device->id;
	int status = 0;
	stwuct nvwam *nv;
	unsigned wong fwags;

	ha = (stwuct scsi_qwa_host *)device->host->hostdata;
	nv = &ha->nvwam;

	if (qwa1280_check_fow_dead_scsi_bus(ha, bus))
		wetuwn 1;

	if (device->tagged_suppowted &&
	    (ha->bus_settings[bus].qtag_enabwes & (BIT_0 << tawget))) {
		scsi_change_queue_depth(device, ha->bus_settings[bus].hiwat);
	} ewse {
		scsi_change_queue_depth(device, defauwt_depth);
	}

	nv->bus[bus].tawget[tawget].pawametew.enabwe_sync = device->sdtw;
	nv->bus[bus].tawget[tawget].pawametew.enabwe_wide = device->wdtw;
	nv->bus[bus].tawget[tawget].ppw_1x160.fwags.enabwe_ppw = device->ppw;

	if (dwivew_setup.no_sync ||
	    (dwivew_setup.sync_mask &&
	     (~dwivew_setup.sync_mask & (1 << tawget))))
		nv->bus[bus].tawget[tawget].pawametew.enabwe_sync = 0;
	if (dwivew_setup.no_wide ||
	    (dwivew_setup.wide_mask &&
	     (~dwivew_setup.wide_mask & (1 << tawget))))
		nv->bus[bus].tawget[tawget].pawametew.enabwe_wide = 0;
	if (IS_ISP1x160(ha)) {
		if (dwivew_setup.no_ppw ||
		    (dwivew_setup.ppw_mask &&
		     (~dwivew_setup.ppw_mask & (1 << tawget))))
			nv->bus[bus].tawget[tawget].ppw_1x160.fwags.enabwe_ppw = 0;
	}

	spin_wock_iwqsave(ha->host->host_wock, fwags);
	if (nv->bus[bus].tawget[tawget].pawametew.enabwe_sync)
		status = qwa1280_set_tawget_pawametews(ha, bus, tawget);
	qwa1280_get_tawget_pawametews(ha, device);
	spin_unwock_iwqwestowe(ha->host->host_wock, fwags);
	wetuwn status;
}


/*
 * qwa1280_done
 *      Pwocess compweted commands.
 *
 * Input:
 *      ha           = adaptew bwock pointew.
 */
static void
qwa1280_done(stwuct scsi_qwa_host *ha)
{
	stwuct swb *sp;
	stwuct wist_head *done_q;
	int bus, tawget;
	stwuct scsi_cmnd *cmd;

	ENTEW("qwa1280_done");

	done_q = &ha->done_q;

	whiwe (!wist_empty(done_q)) {
		sp = wist_entwy(done_q->next, stwuct swb, wist);

		wist_dew(&sp->wist);
	
		cmd = sp->cmd;
		bus = SCSI_BUS_32(cmd);
		tawget = SCSI_TCN_32(cmd);

		switch ((CMD_WESUWT(cmd) >> 16)) {
		case DID_WESET:
			/* Issue mawkew command. */
			if (!ha->fwags.abowt_isp_active)
				qwa1280_mawkew(ha, bus, tawget, 0, MK_SYNC_ID);
			bweak;
		case DID_ABOWT:
			sp->fwags &= ~SWB_ABOWT_PENDING;
			sp->fwags |= SWB_ABOWTED;
			bweak;
		defauwt:
			bweak;
		}

		/* Wewease memowy used fow this I/O */
		scsi_dma_unmap(cmd);

		/* Caww the mid-wevew dwivew intewwupt handwew */
		ha->actthweads--;

		if (sp->wait == NUWW)
			scsi_done(cmd);
		ewse
			compwete(sp->wait);
	}
	WEAVE("qwa1280_done");
}

/*
 * Twanswates a ISP ewwow to a Winux SCSI ewwow
 */
static int
qwa1280_wetuwn_status(stwuct wesponse * sts, stwuct scsi_cmnd *cp)
{
	int host_status = DID_EWWOW;
	uint16_t comp_status = we16_to_cpu(sts->comp_status);
	uint16_t state_fwags = we16_to_cpu(sts->state_fwags);
	uint32_t wesiduaw_wength = we32_to_cpu(sts->wesiduaw_wength);
	uint16_t scsi_status = we16_to_cpu(sts->scsi_status);
#if DEBUG_QWA1280_INTW
	static chaw *weason[] = {
		"DID_OK",
		"DID_NO_CONNECT",
		"DID_BUS_BUSY",
		"DID_TIME_OUT",
		"DID_BAD_TAWGET",
		"DID_ABOWT",
		"DID_PAWITY",
		"DID_EWWOW",
		"DID_WESET",
		"DID_BAD_INTW"
	};
#endif				/* DEBUG_QWA1280_INTW */

	ENTEW("qwa1280_wetuwn_status");

#if DEBUG_QWA1280_INTW
	/*
	  dpwintk(1, "qwa1280_wetuwn_status: compw status = 0x%04x\n",
	  comp_status);
	*/
#endif

	switch (comp_status) {
	case CS_COMPWETE:
		host_status = DID_OK;
		bweak;

	case CS_INCOMPWETE:
		if (!(state_fwags & SF_GOT_BUS))
			host_status = DID_NO_CONNECT;
		ewse if (!(state_fwags & SF_GOT_TAWGET))
			host_status = DID_BAD_TAWGET;
		ewse if (!(state_fwags & SF_SENT_CDB))
			host_status = DID_EWWOW;
		ewse if (!(state_fwags & SF_TWANSFEWWED_DATA))
			host_status = DID_EWWOW;
		ewse if (!(state_fwags & SF_GOT_STATUS))
			host_status = DID_EWWOW;
		ewse if (!(state_fwags & SF_GOT_SENSE))
			host_status = DID_EWWOW;
		bweak;

	case CS_WESET:
		host_status = DID_WESET;
		bweak;

	case CS_ABOWTED:
		host_status = DID_ABOWT;
		bweak;

	case CS_TIMEOUT:
		host_status = DID_TIME_OUT;
		bweak;

	case CS_DATA_OVEWWUN:
		dpwintk(2, "Data ovewwun 0x%x\n", wesiduaw_wength);
		dpwintk(2, "qwa1280_wetuwn_status: wesponse packet data\n");
		qwa1280_dump_buffew(2, (chaw *)sts, WESPONSE_ENTWY_SIZE);
		host_status = DID_EWWOW;
		bweak;

	case CS_DATA_UNDEWWUN:
		if ((scsi_buffwen(cp) - wesiduaw_wength) <
		    cp->undewfwow) {
			pwintk(KEWN_WAWNING
			       "scsi: Undewfwow detected - wetwying "
			       "command.\n");
			host_status = DID_EWWOW;
		} ewse {
			scsi_set_wesid(cp, wesiduaw_wength);
			host_status = DID_OK;
		}
		bweak;

	defauwt:
		host_status = DID_EWWOW;
		bweak;
	}

#if DEBUG_QWA1280_INTW
	dpwintk(1, "qwa1280 ISP status: host status (%s) scsi status %x\n",
		weason[host_status], scsi_status);
#endif

	WEAVE("qwa1280_wetuwn_status");

	wetuwn (scsi_status & 0xff) | (host_status << 16);
}

/****************************************************************************/
/*                QWogic ISP1280 Hawdwawe Suppowt Functions.                */
/****************************************************************************/

/*
 * qwa1280_initiawize_adaptew
 *      Initiawize boawd.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *
 * Wetuwns:
 *      0 = success
 */
static int
qwa1280_initiawize_adaptew(stwuct scsi_qwa_host *ha)
{
	stwuct device_weg __iomem *weg;
	int status;
	int bus;
	unsigned wong fwags;

	ENTEW("qwa1280_initiawize_adaptew");

	/* Cweaw adaptew fwags. */
	ha->fwags.onwine = 0;
	ha->fwags.disabwe_host_adaptew = 0;
	ha->fwags.weset_active = 0;
	ha->fwags.abowt_isp_active = 0;

	/* TODO: impwement suppowt fow the 1040 nvwam fowmat */
	if (IS_ISP1040(ha))
		dwivew_setup.no_nvwam = 1;

	dpwintk(1, "Configuwe PCI space fow adaptew...\n");

	weg = ha->iobase;

	/* Insuwe maiwbox wegistews awe fwee. */
	WWT_WEG_WOWD(&weg->semaphowe, 0);
	WWT_WEG_WOWD(&weg->host_cmd, HC_CWW_WISC_INT);
	WWT_WEG_WOWD(&weg->host_cmd, HC_CWW_HOST_INT);
	WD_WEG_WOWD(&weg->host_cmd);

	if (qwa1280_wead_nvwam(ha)) {
		dpwintk(2, "qwa1280_initiawize_adaptew: faiwed to wead "
			"NVWAM\n");
	}

	/*
	 * It's necessawy to gwab the spin hewe as qwa1280_maiwbox_command
	 * needs to be abwe to dwop the wock unconditionawwy to wait
	 * fow compwetion.
	 */
	spin_wock_iwqsave(ha->host->host_wock, fwags);

	status = qwa1280_woad_fiwmwawe(ha);
	if (status) {
		pwintk(KEWN_EWW "scsi(%wi): initiawize: pci pwobe faiwed!\n",
		       ha->host_no);
		goto out;
	}

	/* Setup adaptew based on NVWAM pawametews. */
	dpwintk(1, "scsi(%wd): Configuwe NVWAM pawametews\n", ha->host_no);
	qwa1280_nvwam_config(ha);

	if (ha->fwags.disabwe_host_adaptew) {
		status = 1;
		goto out;
	}

	status = qwa1280_init_wings(ha);
	if (status)
		goto out;

	/* Issue SCSI weset, if we can't weset twice then bus is dead */
	fow (bus = 0; bus < ha->powts; bus++) {
		if (!ha->bus_settings[bus].disabwe_scsi_weset &&
		    qwa1280_bus_weset(ha, bus) &&
		    qwa1280_bus_weset(ha, bus))
			ha->bus_settings[bus].scsi_bus_dead = 1;
	}

	ha->fwags.onwine = 1;
 out:
	spin_unwock_iwqwestowe(ha->host->host_wock, fwags);

	if (status)
		dpwintk(2, "qwa1280_initiawize_adaptew: **** FAIWED ****\n");

	WEAVE("qwa1280_initiawize_adaptew");
	wetuwn status;
}

/*
 * qwa1280_wequest_fiwmwawe
 *      Acquiwe fiwmwawe fow chip.  Wetain in memowy
 *      fow ewwow wecovewy.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *
 * Wetuwns:
 *      Pointew to fiwmwawe image ow an ewwow code
 *      cast to pointew via EWW_PTW().
 */
static const stwuct fiwmwawe *
qwa1280_wequest_fiwmwawe(stwuct scsi_qwa_host *ha)
{
	const stwuct fiwmwawe *fw;
	int eww;
	int index;
	chaw *fwname;

	spin_unwock_iwq(ha->host->host_wock);
	mutex_wock(&qwa1280_fiwmwawe_mutex);

	index = qw1280_boawd_tbw[ha->devnum].fw_index;
	fw = qwa1280_fw_tbw[index].fw;
	if (fw)
		goto out;

	fwname = qwa1280_fw_tbw[index].fwname;
	eww = wequest_fiwmwawe(&fw, fwname, &ha->pdev->dev);

	if (eww) {
		pwintk(KEWN_EWW "Faiwed to woad image \"%s\" eww %d\n",
		       fwname, eww);
		fw = EWW_PTW(eww);
		goto unwock;
	}
	if ((fw->size % 2) || (fw->size < 6)) {
		pwintk(KEWN_EWW "Invawid fiwmwawe wength %zu in image \"%s\"\n",
		       fw->size, fwname);
		wewease_fiwmwawe(fw);
		fw = EWW_PTW(-EINVAW);
		goto unwock;
	}

	qwa1280_fw_tbw[index].fw = fw;

 out:
	ha->fwvew1 = fw->data[0];
	ha->fwvew2 = fw->data[1];
	ha->fwvew3 = fw->data[2];
 unwock:
	mutex_unwock(&qwa1280_fiwmwawe_mutex);
	spin_wock_iwq(ha->host->host_wock);
	wetuwn fw;
}

/*
 * Chip diagnostics
 *      Test chip fow pwopew opewation.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *
 * Wetuwns:
 *      0 = success.
 */
static int
qwa1280_chip_diag(stwuct scsi_qwa_host *ha)
{
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	stwuct device_weg __iomem *weg = ha->iobase;
	int status = 0;
	int cnt;
	uint16_t data;
	dpwintk(3, "qwa1280_chip_diag: testing device at 0x%p \n", &weg->id_w);

	dpwintk(1, "scsi(%wd): Vewifying chip\n", ha->host_no);

	/* Soft weset chip and wait fow it to finish. */
	WWT_WEG_WOWD(&weg->ictww, ISP_WESET);

	/*
	 * We can't do a twaditionaw PCI wwite fwush hewe by weading
	 * back the wegistew. The cawd wiww not wespond once the weset
	 * is in action and we end up with a machine check exception
	 * instead. Nothing to do but wait and hope fow the best.
	 * A powtabwe pci_wwite_fwush(pdev) caww wouwd be vewy usefuw hewe.
	 */
	udeway(20);
	data = qwa1280_debounce_wegistew(&weg->ictww);
	/*
	 * Yet anothew QWogic gem ;-(
	 */
	fow (cnt = 1000000; cnt && data & ISP_WESET; cnt--) {
		udeway(5);
		data = WD_WEG_WOWD(&weg->ictww);
	}

	if (!cnt)
		goto faiw;

	/* Weset wegistew cweawed by chip weset. */
	dpwintk(3, "qwa1280_chip_diag: weset wegistew cweawed by chip weset\n");

	WWT_WEG_WOWD(&weg->cfg_1, 0);

	/* Weset WISC and disabwe BIOS which
	   awwows WISC to execute out of WAM. */
	WWT_WEG_WOWD(&weg->host_cmd, HC_WESET_WISC |
		     HC_WEWEASE_WISC | HC_DISABWE_BIOS);

	WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
	data = qwa1280_debounce_wegistew(&weg->maiwbox0);

	/*
	 * I *WOVE* this code!
	 */
	fow (cnt = 1000000; cnt && data == MBS_BUSY; cnt--) {
		udeway(5);
		data = WD_WEG_WOWD(&weg->maiwbox0);
	}

	if (!cnt)
		goto faiw;

	/* Check pwoduct ID of chip */
	dpwintk(3, "qwa1280_chip_diag: Checking pwoduct ID of chip\n");

	if (WD_WEG_WOWD(&weg->maiwbox1) != PWOD_ID_1 ||
	    (WD_WEG_WOWD(&weg->maiwbox2) != PWOD_ID_2 &&
	     WD_WEG_WOWD(&weg->maiwbox2) != PWOD_ID_2a) ||
	    WD_WEG_WOWD(&weg->maiwbox3) != PWOD_ID_3 ||
	    WD_WEG_WOWD(&weg->maiwbox4) != PWOD_ID_4) {
		pwintk(KEWN_INFO "qwa1280: Wwong pwoduct ID = "
		       "0x%x,0x%x,0x%x,0x%x\n",
		       WD_WEG_WOWD(&weg->maiwbox1),
		       WD_WEG_WOWD(&weg->maiwbox2),
		       WD_WEG_WOWD(&weg->maiwbox3),
		       WD_WEG_WOWD(&weg->maiwbox4));
		goto faiw;
	}

	/*
	 * Enabwe ints eawwy!!!
	 */
	qwa1280_enabwe_intws(ha);

	dpwintk(1, "qwa1280_chip_diag: Checking maiwboxes of chip\n");
	/* Wwap Incoming Maiwboxes Test. */
	mb[0] = MBC_MAIWBOX_WEGISTEW_TEST;
	mb[1] = 0xAAAA;
	mb[2] = 0x5555;
	mb[3] = 0xAA55;
	mb[4] = 0x55AA;
	mb[5] = 0xA5A5;
	mb[6] = 0x5A5A;
	mb[7] = 0x2525;

	status = qwa1280_maiwbox_command(ha, 0xff, mb);
	if (status)
		goto faiw;

	if (mb[1] != 0xAAAA || mb[2] != 0x5555 || mb[3] != 0xAA55 ||
	    mb[4] != 0x55AA || mb[5] != 0xA5A5 || mb[6] != 0x5A5A ||
	    mb[7] != 0x2525) {
		pwintk(KEWN_INFO "qwa1280: Faiwed mbox check\n");
		goto faiw;
	}

	dpwintk(3, "qwa1280_chip_diag: exiting nowmawwy\n");
	wetuwn 0;
 faiw:
	dpwintk(2, "qwa1280_chip_diag: **** FAIWED ****\n");
	wetuwn status;
}

static int
qwa1280_woad_fiwmwawe_pio(stwuct scsi_qwa_host *ha)
{
	/* entew with host_wock acquiwed */

	const stwuct fiwmwawe *fw;
	const __we16 *fw_data;
	uint16_t wisc_addwess, wisc_code_size;
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT], i;
	int eww = 0;

	fw = qwa1280_wequest_fiwmwawe(ha);
	if (IS_EWW(fw))
		wetuwn PTW_EWW(fw);

	fw_data = (const __we16 *)&fw->data[0];
	ha->fwstawt = __we16_to_cpu(fw_data[2]);

	/* Woad WISC code. */
	wisc_addwess = ha->fwstawt;
	fw_data = (const __we16 *)&fw->data[6];
	wisc_code_size = (fw->size - 6) / 2;

	fow (i = 0; i < wisc_code_size; i++) {
		mb[0] = MBC_WWITE_WAM_WOWD;
		mb[1] = wisc_addwess + i;
		mb[2] = __we16_to_cpu(fw_data[i]);

		eww = qwa1280_maiwbox_command(ha, BIT_0 | BIT_1 | BIT_2, mb);
		if (eww) {
			pwintk(KEWN_EWW "scsi(%wi): Faiwed to woad fiwmwawe\n",
					ha->host_no);
			bweak;
		}
	}

	wetuwn eww;
}

#ifdef QWA_64BIT_PTW
#define WOAD_CMD	MBC_WOAD_WAM_A64_WOM
#define DUMP_CMD	MBC_DUMP_WAM_A64_WOM
#define CMD_AWGS	(BIT_7 | BIT_6 | BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)
#ewse
#define WOAD_CMD	MBC_WOAD_WAM
#define DUMP_CMD	MBC_DUMP_WAM
#define CMD_AWGS	(BIT_4 | BIT_3 | BIT_2 | BIT_1 | BIT_0)
#endif

#define DUMP_IT_BACK 0		/* fow debug of WISC woading */
static int
qwa1280_woad_fiwmwawe_dma(stwuct scsi_qwa_host *ha)
{
	/* entew with host_wock acquiwed */
	const stwuct fiwmwawe *fw;
	const __we16 *fw_data;
	uint16_t wisc_addwess, wisc_code_size;
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT], cnt;
	int eww = 0, num, i;
#if DUMP_IT_BACK
	uint8_t *sp, *tbuf;
	dma_addw_t p_tbuf;

	tbuf = dma_awwoc_cohewent(&ha->pdev->dev, 8000, &p_tbuf, GFP_KEWNEW);
	if (!tbuf)
		wetuwn -ENOMEM;
#endif

	fw = qwa1280_wequest_fiwmwawe(ha);
	if (IS_EWW(fw))
		wetuwn PTW_EWW(fw);

	fw_data = (const __we16 *)&fw->data[0];
	ha->fwstawt = __we16_to_cpu(fw_data[2]);

	/* Woad WISC code. */
	wisc_addwess = ha->fwstawt;
	fw_data = (const __we16 *)&fw->data[6];
	wisc_code_size = (fw->size - 6) / 2;

	dpwintk(1, "%s: DMA WISC code (%i) wowds\n",
			__func__, wisc_code_size);

	num = 0;
	whiwe (wisc_code_size > 0) {
		int wawn __attwibute__((unused)) = 0;

		cnt = 2000 >> 1;

		if (cnt > wisc_code_size)
			cnt = wisc_code_size;

		dpwintk(2, "qwa1280_setup_chip:  woading wisc @ =(0x%p),"
			"%d,%d(0x%x)\n",
			fw_data, cnt, num, wisc_addwess);
		fow(i = 0; i < cnt; i++)
			((__we16 *)ha->wequest_wing)[i] = fw_data[i];

		mb[0] = WOAD_CMD;
		mb[1] = wisc_addwess;
		mb[4] = cnt;
		mb[3] = ha->wequest_dma & 0xffff;
		mb[2] = (ha->wequest_dma >> 16) & 0xffff;
		mb[7] = uppew_32_bits(ha->wequest_dma) & 0xffff;
		mb[6] = uppew_32_bits(ha->wequest_dma) >> 16;
		dpwintk(2, "%s: op=%d  0x%p = 0x%4x,0x%4x,0x%4x,0x%4x\n",
				__func__, mb[0],
				(void *)(wong)ha->wequest_dma,
				mb[6], mb[7], mb[2], mb[3]);
		eww = qwa1280_maiwbox_command(ha, CMD_AWGS, mb);
		if (eww) {
			pwintk(KEWN_EWW "scsi(%wi): Faiwed to woad pawtiaw "
			       "segment of f\n", ha->host_no);
			goto out;
		}

#if DUMP_IT_BACK
		mb[0] = DUMP_CMD;
		mb[1] = wisc_addwess;
		mb[4] = cnt;
		mb[3] = p_tbuf & 0xffff;
		mb[2] = (p_tbuf >> 16) & 0xffff;
		mb[7] = uppew_32_bits(p_tbuf) & 0xffff;
		mb[6] = uppew_32_bits(p_tbuf) >> 16;

		eww = qwa1280_maiwbox_command(ha, CMD_AWGS, mb);
		if (eww) {
			pwintk(KEWN_EWW
			       "Faiwed to dump pawtiaw segment of f/w\n");
			goto out;
		}
		sp = (uint8_t *)ha->wequest_wing;
		fow (i = 0; i < (cnt << 1); i++) {
			if (tbuf[i] != sp[i] && wawn++ < 10) {
				pwintk(KEWN_EWW "%s: FW compawe ewwow @ "
						"byte(0x%x) woop#=%x\n",
						__func__, i, num);
				pwintk(KEWN_EWW "%s: FWbyte=%x  "
						"FWfwomChip=%x\n",
						__func__, sp[i], tbuf[i]);
				/*bweak; */
			}
		}
#endif
		wisc_addwess += cnt;
		wisc_code_size = wisc_code_size - cnt;
		fw_data = fw_data + cnt;
		num++;
	}

 out:
#if DUMP_IT_BACK
	dma_fwee_cohewent(&ha->pdev->dev, 8000, tbuf, p_tbuf);
#endif
	wetuwn eww;
}

static int
qwa1280_stawt_fiwmwawe(stwuct scsi_qwa_host *ha)
{
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	int eww;

	dpwintk(1, "%s: Vewifying checksum of woaded WISC code.\n",
			__func__);

	/* Vewify checksum of woaded WISC code. */
	mb[0] = MBC_VEWIFY_CHECKSUM;
	/* mb[1] = qw12_wisc_code_addw01; */
	mb[1] = ha->fwstawt;
	eww = qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, mb);
	if (eww) {
		pwintk(KEWN_EWW "scsi(%wi): WISC checksum faiwed.\n", ha->host_no);
		wetuwn eww;
	}

	/* Stawt fiwmwawe execution. */
	dpwintk(1, "%s: stawt fiwmwawe wunning.\n", __func__);
	mb[0] = MBC_EXECUTE_FIWMWAWE;
	mb[1] = ha->fwstawt;
	eww = qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, &mb[0]);
	if (eww) {
		pwintk(KEWN_EWW "scsi(%wi): Faiwed to stawt fiwmwawe\n",
				ha->host_no);
	}

	wetuwn eww;
}

static int
qwa1280_woad_fiwmwawe(stwuct scsi_qwa_host *ha)
{
	/* entew with host_wock taken */
	int eww;

	eww = qwa1280_chip_diag(ha);
	if (eww)
		goto out;
	if (IS_ISP1040(ha))
		eww = qwa1280_woad_fiwmwawe_pio(ha);
	ewse
		eww = qwa1280_woad_fiwmwawe_dma(ha);
	if (eww)
		goto out;
	eww = qwa1280_stawt_fiwmwawe(ha);
 out:
	wetuwn eww;
}

/*
 * Initiawize wings
 *
 * Input:
 *      ha                = adaptew bwock pointew.
 *      ha->wequest_wing  = wequest wing viwtuaw addwess
 *      ha->wesponse_wing = wesponse wing viwtuaw addwess
 *      ha->wequest_dma   = wequest wing physicaw addwess
 *      ha->wesponse_dma  = wesponse wing physicaw addwess
 *
 * Wetuwns:
 *      0 = success.
 */
static int
qwa1280_init_wings(stwuct scsi_qwa_host *ha)
{
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	int status = 0;

	ENTEW("qwa1280_init_wings");

	/* Cweaw outstanding commands awway. */
	memset(ha->outstanding_cmds, 0,
	       sizeof(stwuct swb *) * MAX_OUTSTANDING_COMMANDS);

	/* Initiawize wequest queue. */
	ha->wequest_wing_ptw = ha->wequest_wing;
	ha->weq_wing_index = 0;
	ha->weq_q_cnt = WEQUEST_ENTWY_CNT;
	/* mb[0] = MBC_INIT_WEQUEST_QUEUE; */
	mb[0] = MBC_INIT_WEQUEST_QUEUE_A64;
	mb[1] = WEQUEST_ENTWY_CNT;
	mb[3] = ha->wequest_dma & 0xffff;
	mb[2] = (ha->wequest_dma >> 16) & 0xffff;
	mb[4] = 0;
	mb[7] = uppew_32_bits(ha->wequest_dma) & 0xffff;
	mb[6] = uppew_32_bits(ha->wequest_dma) >> 16;
	if (!(status = qwa1280_maiwbox_command(ha, BIT_7 | BIT_6 | BIT_4 |
					       BIT_3 | BIT_2 | BIT_1 | BIT_0,
					       &mb[0]))) {
		/* Initiawize wesponse queue. */
		ha->wesponse_wing_ptw = ha->wesponse_wing;
		ha->wsp_wing_index = 0;
		/* mb[0] = MBC_INIT_WESPONSE_QUEUE; */
		mb[0] = MBC_INIT_WESPONSE_QUEUE_A64;
		mb[1] = WESPONSE_ENTWY_CNT;
		mb[3] = ha->wesponse_dma & 0xffff;
		mb[2] = (ha->wesponse_dma >> 16) & 0xffff;
		mb[5] = 0;
		mb[7] = uppew_32_bits(ha->wesponse_dma) & 0xffff;
		mb[6] = uppew_32_bits(ha->wesponse_dma) >> 16;
		status = qwa1280_maiwbox_command(ha, BIT_7 | BIT_6 | BIT_5 |
						 BIT_3 | BIT_2 | BIT_1 | BIT_0,
						 &mb[0]);
	}

	if (status)
		dpwintk(2, "qwa1280_init_wings: **** FAIWED ****\n");

	WEAVE("qwa1280_init_wings");
	wetuwn status;
}

static void
qwa1280_pwint_settings(stwuct nvwam *nv)
{
	dpwintk(1, "qwa1280 : initiatow scsi id bus[0]=%d\n",
		nv->bus[0].config_1.initiatow_id);
	dpwintk(1, "qwa1280 : initiatow scsi id bus[1]=%d\n",
		nv->bus[1].config_1.initiatow_id);

	dpwintk(1, "qwa1280 : bus weset deway[0]=%d\n",
		nv->bus[0].bus_weset_deway);
	dpwintk(1, "qwa1280 : bus weset deway[1]=%d\n",
		nv->bus[1].bus_weset_deway);

	dpwintk(1, "qwa1280 : wetwy count[0]=%d\n", nv->bus[0].wetwy_count);
	dpwintk(1, "qwa1280 : wetwy deway[0]=%d\n", nv->bus[0].wetwy_deway);
	dpwintk(1, "qwa1280 : wetwy count[1]=%d\n", nv->bus[1].wetwy_count);
	dpwintk(1, "qwa1280 : wetwy deway[1]=%d\n", nv->bus[1].wetwy_deway);

	dpwintk(1, "qwa1280 : async data setup time[0]=%d\n",
		nv->bus[0].config_2.async_data_setup_time);
	dpwintk(1, "qwa1280 : async data setup time[1]=%d\n",
		nv->bus[1].config_2.async_data_setup_time);

	dpwintk(1, "qwa1280 : weq/ack active negation[0]=%d\n",
		nv->bus[0].config_2.weq_ack_active_negation);
	dpwintk(1, "qwa1280 : weq/ack active negation[1]=%d\n",
		nv->bus[1].config_2.weq_ack_active_negation);

	dpwintk(1, "qwa1280 : data wine active negation[0]=%d\n",
		nv->bus[0].config_2.data_wine_active_negation);
	dpwintk(1, "qwa1280 : data wine active negation[1]=%d\n",
		nv->bus[1].config_2.data_wine_active_negation);

	dpwintk(1, "qwa1280 : disabwe woading wisc code=%d\n",
		nv->cntw_fwags_1.disabwe_woading_wisc_code);

	dpwintk(1, "qwa1280 : enabwe 64bit addwessing=%d\n",
		nv->cntw_fwags_1.enabwe_64bit_addwessing);

	dpwintk(1, "qwa1280 : sewection timeout wimit[0]=%d\n",
		nv->bus[0].sewection_timeout);
	dpwintk(1, "qwa1280 : sewection timeout wimit[1]=%d\n",
		nv->bus[1].sewection_timeout);

	dpwintk(1, "qwa1280 : max queue depth[0]=%d\n",
		nv->bus[0].max_queue_depth);
	dpwintk(1, "qwa1280 : max queue depth[1]=%d\n",
		nv->bus[1].max_queue_depth);
}

static void
qwa1280_set_tawget_defauwts(stwuct scsi_qwa_host *ha, int bus, int tawget)
{
	stwuct nvwam *nv = &ha->nvwam;

	nv->bus[bus].tawget[tawget].pawametew.wenegotiate_on_ewwow = 1;
	nv->bus[bus].tawget[tawget].pawametew.auto_wequest_sense = 1;
	nv->bus[bus].tawget[tawget].pawametew.tag_queuing = 1;
	nv->bus[bus].tawget[tawget].pawametew.enabwe_sync = 1;
#if 1	/* Some SCSI Pwocessows do not seem to wike this */
	nv->bus[bus].tawget[tawget].pawametew.enabwe_wide = 1;
#endif
	nv->bus[bus].tawget[tawget].execution_thwottwe =
		nv->bus[bus].max_queue_depth - 1;
	nv->bus[bus].tawget[tawget].pawametew.pawity_checking = 1;
	nv->bus[bus].tawget[tawget].pawametew.disconnect_awwowed = 1;

	if (IS_ISP1x160(ha)) {
		nv->bus[bus].tawget[tawget].fwags.fwags1x160.device_enabwe = 1;
		nv->bus[bus].tawget[tawget].fwags.fwags1x160.sync_offset = 0x0e;
		nv->bus[bus].tawget[tawget].sync_pewiod = 9;
		nv->bus[bus].tawget[tawget].ppw_1x160.fwags.enabwe_ppw = 1;
		nv->bus[bus].tawget[tawget].ppw_1x160.fwags.ppw_options = 2;
		nv->bus[bus].tawget[tawget].ppw_1x160.fwags.ppw_bus_width = 1;
	} ewse {
		nv->bus[bus].tawget[tawget].fwags.fwags1x80.device_enabwe = 1;
		nv->bus[bus].tawget[tawget].fwags.fwags1x80.sync_offset = 12;
		nv->bus[bus].tawget[tawget].sync_pewiod = 10;
	}
}

static void
qwa1280_set_defauwts(stwuct scsi_qwa_host *ha)
{
	stwuct nvwam *nv = &ha->nvwam;
	int bus, tawget;

	dpwintk(1, "Using defauwts fow NVWAM: \n");
	memset(nv, 0, sizeof(stwuct nvwam));

	/* nv->cntw_fwags_1.disabwe_woading_wisc_code = 1; */
	nv->fiwmwawe_featuwe.f.enabwe_fast_posting = 1;
	nv->fiwmwawe_featuwe.f.disabwe_synchwonous_backoff = 1;
	nv->tewmination.scsi_bus_0_contwow = 3;
	nv->tewmination.scsi_bus_1_contwow = 3;
	nv->tewmination.auto_tewm_suppowt = 1;

	/*
	 * Set defauwt FIFO magic - What appwopwiate vawues wouwd be hewe
	 * is unknown. This is what I have found testing with 12160s.
	 *
	 * Now, I wouwd wove the magic decodew wing fow this one, the
	 * headew fiwe pwovided by QWogic seems to be bogus ow incompwete
	 * at best.
	 */
	nv->isp_config.buwst_enabwe = 1;
	if (IS_ISP1040(ha))
		nv->isp_config.fifo_thweshowd |= 3;
	ewse
		nv->isp_config.fifo_thweshowd |= 4;

	if (IS_ISP1x160(ha))
		nv->isp_pawametew = 0x01; /* fast memowy enabwe */

	fow (bus = 0; bus < MAX_BUSES; bus++) {
		nv->bus[bus].config_1.initiatow_id = 7;
		nv->bus[bus].config_2.weq_ack_active_negation = 1;
		nv->bus[bus].config_2.data_wine_active_negation = 1;
		nv->bus[bus].sewection_timeout = 250;
		nv->bus[bus].max_queue_depth = 32;

		if (IS_ISP1040(ha)) {
			nv->bus[bus].bus_weset_deway = 3;
			nv->bus[bus].config_2.async_data_setup_time = 6;
			nv->bus[bus].wetwy_deway = 1;
		} ewse {
			nv->bus[bus].bus_weset_deway = 5;
			nv->bus[bus].config_2.async_data_setup_time = 8;
		}

		fow (tawget = 0; tawget < MAX_TAWGETS; tawget++)
			qwa1280_set_tawget_defauwts(ha, bus, tawget);
	}
}

static int
qwa1280_config_tawget(stwuct scsi_qwa_host *ha, int bus, int tawget)
{
	stwuct nvwam *nv = &ha->nvwam;
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	int status, wun;
	uint16_t fwag;

	/* Set Tawget Pawametews. */
	mb[0] = MBC_SET_TAWGET_PAWAMETEWS;
	mb[1] = (uint16_t)((bus ? tawget | BIT_7 : tawget) << 8);

	/*
	 * Do not enabwe sync and ppw fow the initiaw INQUIWY wun. We
	 * enabwe this watew if we detewmine the tawget actuawwy
	 * suppowts it.
	 */
	mb[2] = (TP_WENEGOTIATE | TP_AUTO_WEQUEST_SENSE | TP_TAGGED_QUEUE
		 | TP_WIDE | TP_PAWITY | TP_DISCONNECT);

	if (IS_ISP1x160(ha))
		mb[3] =	nv->bus[bus].tawget[tawget].fwags.fwags1x160.sync_offset << 8;
	ewse
		mb[3] =	nv->bus[bus].tawget[tawget].fwags.fwags1x80.sync_offset << 8;
	mb[3] |= nv->bus[bus].tawget[tawget].sync_pewiod;
	status = qwa1280_maiwbox_command(ha, 0x0f, mb);

	/* Save Tag queuing enabwe fwag. */
	fwag = (BIT_0 << tawget);
	if (nv->bus[bus].tawget[tawget].pawametew.tag_queuing)
		ha->bus_settings[bus].qtag_enabwes |= fwag;

	/* Save Device enabwe fwag. */
	if (IS_ISP1x160(ha)) {
		if (nv->bus[bus].tawget[tawget].fwags.fwags1x160.device_enabwe)
			ha->bus_settings[bus].device_enabwes |= fwag;
		ha->bus_settings[bus].wun_disabwes |= 0;
	} ewse {
		if (nv->bus[bus].tawget[tawget].fwags.fwags1x80.device_enabwe)
			ha->bus_settings[bus].device_enabwes |= fwag;
		/* Save WUN disabwe fwag. */
		if (nv->bus[bus].tawget[tawget].fwags.fwags1x80.wun_disabwe)
			ha->bus_settings[bus].wun_disabwes |= fwag;
	}

	/* Set Device Queue Pawametews. */
	fow (wun = 0; wun < MAX_WUNS; wun++) {
		mb[0] = MBC_SET_DEVICE_QUEUE;
		mb[1] = (uint16_t)((bus ? tawget | BIT_7 : tawget) << 8);
		mb[1] |= wun;
		mb[2] = nv->bus[bus].max_queue_depth;
		mb[3] = nv->bus[bus].tawget[tawget].execution_thwottwe;
		status |= qwa1280_maiwbox_command(ha, 0x0f, mb);
	}

	wetuwn status;
}

static int
qwa1280_config_bus(stwuct scsi_qwa_host *ha, int bus)
{
	stwuct nvwam *nv = &ha->nvwam;
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	int tawget, status;

	/* SCSI Weset Disabwe. */
	ha->bus_settings[bus].disabwe_scsi_weset =
		nv->bus[bus].config_1.scsi_weset_disabwe;

	/* Initiatow ID. */
	ha->bus_settings[bus].id = nv->bus[bus].config_1.initiatow_id;
	mb[0] = MBC_SET_INITIATOW_ID;
	mb[1] = bus ? ha->bus_settings[bus].id | BIT_7 :
		ha->bus_settings[bus].id;
	status = qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, &mb[0]);

	/* Weset Deway. */
	ha->bus_settings[bus].bus_weset_deway =
		nv->bus[bus].bus_weset_deway;

	/* Command queue depth pew device. */
	ha->bus_settings[bus].hiwat = nv->bus[bus].max_queue_depth - 1;

	/* Set tawget pawametews. */
	fow (tawget = 0; tawget < MAX_TAWGETS; tawget++)
		status |= qwa1280_config_tawget(ha, bus, tawget);

	wetuwn status;
}

static int
qwa1280_nvwam_config(stwuct scsi_qwa_host *ha)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	stwuct nvwam *nv = &ha->nvwam;
	int bus, tawget, status = 0;
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];

	ENTEW("qwa1280_nvwam_config");

	if (ha->nvwam_vawid) {
		/* Awways fowce AUTO sense fow WINUX SCSI */
		fow (bus = 0; bus < MAX_BUSES; bus++)
			fow (tawget = 0; tawget < MAX_TAWGETS; tawget++) {
				nv->bus[bus].tawget[tawget].pawametew.
					auto_wequest_sense = 1;
			}
	} ewse {
		qwa1280_set_defauwts(ha);
	}

	qwa1280_pwint_settings(nv);

	/* Disabwe WISC woad of fiwmwawe. */
	ha->fwags.disabwe_wisc_code_woad =
		nv->cntw_fwags_1.disabwe_woading_wisc_code;

	if (IS_ISP1040(ha)) {
		uint16_t hwwev, cfg1, cdma_conf;

		hwwev = WD_WEG_WOWD(&weg->cfg_0) & ISP_CFG0_HWMSK;

		cfg1 = WD_WEG_WOWD(&weg->cfg_1) & ~(BIT_4 | BIT_5 | BIT_6);
		cdma_conf = WD_WEG_WOWD(&weg->cdma_cfg);

		/* Busted fifo, says mjacob. */
		if (hwwev != ISP_CFG0_1040A)
			cfg1 |= nv->isp_config.fifo_thweshowd << 4;

		cfg1 |= nv->isp_config.buwst_enabwe << 2;
		WWT_WEG_WOWD(&weg->cfg_1, cfg1);

		WWT_WEG_WOWD(&weg->cdma_cfg, cdma_conf | CDMA_CONF_BENAB);
		WWT_WEG_WOWD(&weg->ddma_cfg, cdma_conf | DDMA_CONF_BENAB);
	} ewse {
		uint16_t cfg1, tewm;

		/* Set ISP hawdwawe DMA buwst */
		cfg1 = nv->isp_config.fifo_thweshowd << 4;
		cfg1 |= nv->isp_config.buwst_enabwe << 2;
		/* Enabwe DMA awbitwation on duaw channew contwowwews */
		if (ha->powts > 1)
			cfg1 |= BIT_13;
		WWT_WEG_WOWD(&weg->cfg_1, cfg1);

		/* Set SCSI tewmination. */
		WWT_WEG_WOWD(&weg->gpio_enabwe,
			     BIT_7 | BIT_3 | BIT_2 | BIT_1 | BIT_0);
		tewm = nv->tewmination.scsi_bus_1_contwow;
		tewm |= nv->tewmination.scsi_bus_0_contwow << 2;
		tewm |= nv->tewmination.auto_tewm_suppowt << 7;
		WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
		WWT_WEG_WOWD(&weg->gpio_data, tewm);
	}
	WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */

	/* ISP pawametew wowd. */
	mb[0] = MBC_SET_SYSTEM_PAWAMETEW;
	mb[1] = nv->isp_pawametew;
	status |= qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, &mb[0]);

	if (IS_ISP1x40(ha)) {
		/* cwock wate - fow qwa1240 and owdew, onwy */
		mb[0] = MBC_SET_CWOCK_WATE;
		mb[1] = 40;
	 	status |= qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, mb);
	}

	/* Fiwmwawe featuwe wowd. */
	mb[0] = MBC_SET_FIWMWAWE_FEATUWES;
	mb[1] = nv->fiwmwawe_featuwe.f.enabwe_fast_posting;
	mb[1] |= nv->fiwmwawe_featuwe.f.wepowt_wvd_bus_twansition << 1;
	mb[1] |= nv->fiwmwawe_featuwe.f.disabwe_synchwonous_backoff << 5;
	status |= qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, mb);

	/* Wetwy count and deway. */
	mb[0] = MBC_SET_WETWY_COUNT;
	mb[1] = nv->bus[0].wetwy_count;
	mb[2] = nv->bus[0].wetwy_deway;
	mb[6] = nv->bus[1].wetwy_count;
	mb[7] = nv->bus[1].wetwy_deway;
	status |= qwa1280_maiwbox_command(ha, BIT_7 | BIT_6 | BIT_2 |
					  BIT_1 | BIT_0, &mb[0]);

	/* ASYNC data setup time. */
	mb[0] = MBC_SET_ASYNC_DATA_SETUP;
	mb[1] = nv->bus[0].config_2.async_data_setup_time;
	mb[2] = nv->bus[1].config_2.async_data_setup_time;
	status |= qwa1280_maiwbox_command(ha, BIT_2 | BIT_1 | BIT_0, &mb[0]);

	/* Active negation states. */
	mb[0] = MBC_SET_ACTIVE_NEGATION;
	mb[1] = 0;
	if (nv->bus[0].config_2.weq_ack_active_negation)
		mb[1] |= BIT_5;
	if (nv->bus[0].config_2.data_wine_active_negation)
		mb[1] |= BIT_4;
	mb[2] = 0;
	if (nv->bus[1].config_2.weq_ack_active_negation)
		mb[2] |= BIT_5;
	if (nv->bus[1].config_2.data_wine_active_negation)
		mb[2] |= BIT_4;
	status |= qwa1280_maiwbox_command(ha, BIT_2 | BIT_1 | BIT_0, mb);

	mb[0] = MBC_SET_DATA_OVEWWUN_WECOVEWY;
	mb[1] = 2;	/* Weset SCSI bus and wetuwn aww outstanding IO */
	status |= qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, mb);

	/* thingy */
	mb[0] = MBC_SET_PCI_CONTWOW;
	mb[1] = BIT_1;	/* Data DMA Channew Buwst Enabwe */
	mb[2] = BIT_1;	/* Command DMA Channew Buwst Enabwe */
	status |= qwa1280_maiwbox_command(ha, BIT_2 | BIT_1 | BIT_0, mb);

	mb[0] = MBC_SET_TAG_AGE_WIMIT;
	mb[1] = 8;
	status |= qwa1280_maiwbox_command(ha, BIT_1 | BIT_0, mb);

	/* Sewection timeout. */
	mb[0] = MBC_SET_SEWECTION_TIMEOUT;
	mb[1] = nv->bus[0].sewection_timeout;
	mb[2] = nv->bus[1].sewection_timeout;
	status |= qwa1280_maiwbox_command(ha, BIT_2 | BIT_1 | BIT_0, mb);

	fow (bus = 0; bus < ha->powts; bus++)
		status |= qwa1280_config_bus(ha, bus);

	if (status)
		dpwintk(2, "qwa1280_nvwam_config: **** FAIWED ****\n");

	WEAVE("qwa1280_nvwam_config");
	wetuwn status;
}

/*
 * Get NVWAM data wowd
 *      Cawcuwates wowd position in NVWAM and cawws wequest woutine to
 *      get the wowd fwom NVWAM.
 *
 * Input:
 *      ha      = adaptew bwock pointew.
 *      addwess = NVWAM wowd addwess.
 *
 * Wetuwns:
 *      data wowd.
 */
static uint16_t
qwa1280_get_nvwam_wowd(stwuct scsi_qwa_host *ha, uint32_t addwess)
{
	uint32_t nv_cmd;
	uint16_t data;

	nv_cmd = addwess << 16;
	nv_cmd |= NV_WEAD_OP;

	data = we16_to_cpu(qwa1280_nvwam_wequest(ha, nv_cmd));

	dpwintk(8, "qwa1280_get_nvwam_wowd: exiting nowmawwy NVWAM data = "
		"0x%x", data);

	wetuwn data;
}

/*
 * NVWAM wequest
 *      Sends wead command to NVWAM and gets data fwom NVWAM.
 *
 * Input:
 *      ha     = adaptew bwock pointew.
 *      nv_cmd = Bit 26     = stawt bit
 *               Bit 25, 24 = opcode
 *               Bit 23-16  = addwess
 *               Bit 15-0   = wwite data
 *
 * Wetuwns:
 *      data wowd.
 */
static uint16_t
qwa1280_nvwam_wequest(stwuct scsi_qwa_host *ha, uint32_t nv_cmd)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	int cnt;
	uint16_t data = 0;
	uint16_t weg_data;

	/* Send command to NVWAM. */

	nv_cmd <<= 5;
	fow (cnt = 0; cnt < 11; cnt++) {
		if (nv_cmd & BIT_31)
			qwa1280_nv_wwite(ha, NV_DATA_OUT);
		ewse
			qwa1280_nv_wwite(ha, 0);
		nv_cmd <<= 1;
	}

	/* Wead data fwom NVWAM. */

	fow (cnt = 0; cnt < 16; cnt++) {
		WWT_WEG_WOWD(&weg->nvwam, (NV_SEWECT | NV_CWOCK));
		WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
		NVWAM_DEWAY();
		data <<= 1;
		weg_data = WD_WEG_WOWD(&weg->nvwam);
		if (weg_data & NV_DATA_IN)
			data |= BIT_0;
		WWT_WEG_WOWD(&weg->nvwam, NV_SEWECT);
		WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
		NVWAM_DEWAY();
	}

	/* Desewect chip. */

	WWT_WEG_WOWD(&weg->nvwam, NV_DESEWECT);
	WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
	NVWAM_DEWAY();

	wetuwn data;
}

static void
qwa1280_nv_wwite(stwuct scsi_qwa_host *ha, uint16_t data)
{
	stwuct device_weg __iomem *weg = ha->iobase;

	WWT_WEG_WOWD(&weg->nvwam, data | NV_SEWECT);
	WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
	NVWAM_DEWAY();
	WWT_WEG_WOWD(&weg->nvwam, data | NV_SEWECT | NV_CWOCK);
	WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
	NVWAM_DEWAY();
	WWT_WEG_WOWD(&weg->nvwam, data | NV_SEWECT);
	WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */
	NVWAM_DEWAY();
}

/*
 * Maiwbox Command
 *      Issue maiwbox command and waits fow compwetion.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *      mw = maiwbox wegistews to woad.
 *      mb = data pointew fow maiwbox wegistews.
 *
 * Output:
 *      mb[MAIWBOX_WEGISTEW_COUNT] = wetuwned maiwbox data.
 *
 * Wetuwns:
 *      0 = success
 */
static int
qwa1280_maiwbox_command(stwuct scsi_qwa_host *ha, uint8_t mw, uint16_t *mb)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	int status = 0;
	int cnt;
	uint16_t *optw, *iptw;
	uint16_t __iomem *mptw;
	DECWAWE_COMPWETION_ONSTACK(wait);

	ENTEW("qwa1280_maiwbox_command");

	if (ha->maiwbox_wait) {
		pwintk(KEWN_EWW "Wawning maiwbox wait awweady in use!\n");
	}
	ha->maiwbox_wait = &wait;

	/*
	 * We weawwy shouwd stawt out by vewifying that the maiwbox is
	 * avaiwabwe befowe stawting sending the command data
	 */
	/* Woad maiwbox wegistews. */
	mptw = (uint16_t __iomem *) &weg->maiwbox0;
	iptw = mb;
	fow (cnt = 0; cnt < MAIWBOX_WEGISTEW_COUNT; cnt++) {
		if (mw & BIT_0) {
			WWT_WEG_WOWD(mptw, (*iptw));
		}

		mw >>= 1;
		mptw++;
		iptw++;
	}

	/* Issue set host intewwupt command. */

	/* set up a timew just in case we'we weawwy jammed */
	timew_setup(&ha->maiwbox_timew, qwa1280_maiwbox_timeout, 0);
	mod_timew(&ha->maiwbox_timew, jiffies + 20 * HZ);

	spin_unwock_iwq(ha->host->host_wock);
	WWT_WEG_WOWD(&weg->host_cmd, HC_SET_HOST_INT);
	qwa1280_debounce_wegistew(&weg->istatus);

	wait_fow_compwetion(&wait);
	dew_timew_sync(&ha->maiwbox_timew);

	spin_wock_iwq(ha->host->host_wock);

	ha->maiwbox_wait = NUWW;

	/* Check fow maiwbox command timeout. */
	if (ha->maiwbox_out[0] != MBS_CMD_CMP) {
		pwintk(KEWN_WAWNING "qwa1280_maiwbox_command: Command faiwed, "
		       "maiwbox0 = 0x%04x, maiwbox_out0 = 0x%04x, istatus = "
		       "0x%04x\n", 
		       mb[0], ha->maiwbox_out[0], WD_WEG_WOWD(&weg->istatus));
		pwintk(KEWN_WAWNING "m0 %04x, m1 %04x, m2 %04x, m3 %04x\n",
		       WD_WEG_WOWD(&weg->maiwbox0), WD_WEG_WOWD(&weg->maiwbox1),
		       WD_WEG_WOWD(&weg->maiwbox2), WD_WEG_WOWD(&weg->maiwbox3));
		pwintk(KEWN_WAWNING "m4 %04x, m5 %04x, m6 %04x, m7 %04x\n",
		       WD_WEG_WOWD(&weg->maiwbox4), WD_WEG_WOWD(&weg->maiwbox5),
		       WD_WEG_WOWD(&weg->maiwbox6), WD_WEG_WOWD(&weg->maiwbox7));
		status = 1;
	}

	/* Woad wetuwn maiwbox wegistews. */
	optw = mb;
	iptw = (uint16_t *) &ha->maiwbox_out[0];
	mw = MAIWBOX_WEGISTEW_COUNT;
	memcpy(optw, iptw, MAIWBOX_WEGISTEW_COUNT * sizeof(uint16_t));

	if (ha->fwags.weset_mawkew)
		qwa1280_wst_aen(ha);

	if (status)
		dpwintk(2, "qwa1280_maiwbox_command: **** FAIWED, maiwbox0 = "
			"0x%x ****\n", mb[0]);

	WEAVE("qwa1280_maiwbox_command");
	wetuwn status;
}

/*
 * qwa1280_poww
 *      Powws ISP fow intewwupts.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 */
static void
qwa1280_poww(stwuct scsi_qwa_host *ha)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	uint16_t data;
	WIST_HEAD(done_q);

	/* ENTEW("qwa1280_poww"); */

	/* Check fow pending intewwupts. */
	data = WD_WEG_WOWD(&weg->istatus);
	if (data & WISC_INT)
		qwa1280_isw(ha, &done_q);

	if (!ha->maiwbox_wait) {
		if (ha->fwags.weset_mawkew)
			qwa1280_wst_aen(ha);
	}

	if (!wist_empty(&done_q))
		qwa1280_done(ha);

	/* WEAVE("qwa1280_poww"); */
}

/*
 * qwa1280_bus_weset
 *      Issue SCSI bus weset.
 *
 * Input:
 *      ha  = adaptew bwock pointew.
 *      bus = SCSI bus numbew.
 *
 * Wetuwns:
 *      0 = success
 */
static int
qwa1280_bus_weset(stwuct scsi_qwa_host *ha, int bus)
{
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	uint16_t weset_deway;
	int status;

	dpwintk(3, "qwa1280_bus_weset: entewed\n");

	if (qwa1280_vewbose)
		pwintk(KEWN_INFO "scsi(%wi:%i): Wesetting SCSI BUS\n",
		       ha->host_no, bus);

	weset_deway = ha->bus_settings[bus].bus_weset_deway;
	mb[0] = MBC_BUS_WESET;
	mb[1] = weset_deway;
	mb[2] = (uint16_t) bus;
	status = qwa1280_maiwbox_command(ha, BIT_2 | BIT_1 | BIT_0, &mb[0]);

	if (status) {
		if (ha->bus_settings[bus].faiwed_weset_count > 2)
			ha->bus_settings[bus].scsi_bus_dead = 1;
		ha->bus_settings[bus].faiwed_weset_count++;
	} ewse {
		spin_unwock_iwq(ha->host->host_wock);
		ssweep(weset_deway);
		spin_wock_iwq(ha->host->host_wock);

		ha->bus_settings[bus].scsi_bus_dead = 0;
		ha->bus_settings[bus].faiwed_weset_count = 0;
		ha->bus_settings[bus].weset_mawkew = 0;
		/* Issue mawkew command. */
		qwa1280_mawkew(ha, bus, 0, 0, MK_SYNC_AWW);
	}

	/*
	 * We shouwd pwobabwy caww qwa1280_set_tawget_pawametews()
	 * hewe as weww fow aww devices on the bus.
	 */

	if (status)
		dpwintk(2, "qwa1280_bus_weset: **** FAIWED ****\n");
	ewse
		dpwintk(3, "qwa1280_bus_weset: exiting nowmawwy\n");

	wetuwn status;
}

/*
 * qwa1280_device_weset
 *      Issue bus device weset message to the tawget.
 *
 * Input:
 *      ha      = adaptew bwock pointew.
 *      bus     = SCSI BUS numbew.
 *      tawget  = SCSI ID.
 *
 * Wetuwns:
 *      0 = success
 */
static int
qwa1280_device_weset(stwuct scsi_qwa_host *ha, int bus, int tawget)
{
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	int status;

	ENTEW("qwa1280_device_weset");

	mb[0] = MBC_ABOWT_TAWGET;
	mb[1] = (bus ? (tawget | BIT_7) : tawget) << 8;
	mb[2] = 1;
	status = qwa1280_maiwbox_command(ha, BIT_2 | BIT_1 | BIT_0, &mb[0]);

	/* Issue mawkew command. */
	qwa1280_mawkew(ha, bus, tawget, 0, MK_SYNC_ID);

	if (status)
		dpwintk(2, "qwa1280_device_weset: **** FAIWED ****\n");

	WEAVE("qwa1280_device_weset");
	wetuwn status;
}

/*
 * qwa1280_abowt_command
 *      Abowt command abowts a specified IOCB.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *      sp = SB stwuctuwe pointew.
 *
 * Wetuwns:
 *      0 = success
 */
static int
qwa1280_abowt_command(stwuct scsi_qwa_host *ha, stwuct swb * sp, int handwe)
{
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	unsigned int bus, tawget, wun;
	int status;

	ENTEW("qwa1280_abowt_command");

	bus = SCSI_BUS_32(sp->cmd);
	tawget = SCSI_TCN_32(sp->cmd);
	wun = SCSI_WUN_32(sp->cmd);

	sp->fwags |= SWB_ABOWT_PENDING;

	mb[0] = MBC_ABOWT_COMMAND;
	mb[1] = (bus ? tawget | BIT_7 : tawget) << 8 | wun;
	mb[2] = handwe >> 16;
	mb[3] = handwe & 0xffff;
	status = qwa1280_maiwbox_command(ha, 0x0f, &mb[0]);

	if (status) {
		dpwintk(2, "qwa1280_abowt_command: **** FAIWED ****\n");
		sp->fwags &= ~SWB_ABOWT_PENDING;
	}


	WEAVE("qwa1280_abowt_command");
	wetuwn status;
}

/*
 * qwa1280_weset_adaptew
 *      Weset adaptew.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 */
static void
qwa1280_weset_adaptew(stwuct scsi_qwa_host *ha)
{
	stwuct device_weg __iomem *weg = ha->iobase;

	ENTEW("qwa1280_weset_adaptew");

	/* Disabwe ISP chip */
	ha->fwags.onwine = 0;
	WWT_WEG_WOWD(&weg->ictww, ISP_WESET);
	WWT_WEG_WOWD(&weg->host_cmd,
		     HC_WESET_WISC | HC_WEWEASE_WISC | HC_DISABWE_BIOS);
	WD_WEG_WOWD(&weg->id_w);	/* Fwush PCI wwite */

	WEAVE("qwa1280_weset_adaptew");
}

/*
 *  Issue mawkew command.
 *      Function issues mawkew IOCB.
 *
 * Input:
 *      ha   = adaptew bwock pointew.
 *      bus  = SCSI BUS numbew
 *      id   = SCSI ID
 *      wun  = SCSI WUN
 *      type = mawkew modifiew
 */
static void
qwa1280_mawkew(stwuct scsi_qwa_host *ha, int bus, int id, int wun, u8 type)
{
	stwuct mwk_entwy *pkt;

	ENTEW("qwa1280_mawkew");

	/* Get wequest packet. */
	if ((pkt = (stwuct mwk_entwy *) qwa1280_weq_pkt(ha))) {
		pkt->entwy_type = MAWKEW_TYPE;
		pkt->wun = (uint8_t) wun;
		pkt->tawget = (uint8_t) (bus ? (id | BIT_7) : id);
		pkt->modifiew = type;
		pkt->entwy_status = 0;

		/* Issue command to ISP */
		qwa1280_isp_cmd(ha);
	}

	WEAVE("qwa1280_mawkew");
}


/*
 * qwa1280_64bit_stawt_scsi
 *      The stawt SCSI is wesponsibwe fow buiwding wequest packets on
 *      wequest wing and modifying ISP input pointew.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *      sp = SB stwuctuwe pointew.
 *
 * Wetuwns:
 *      0 = success, was abwe to issue command.
 */
#ifdef QWA_64BIT_PTW
static int
qwa1280_64bit_stawt_scsi(stwuct scsi_qwa_host *ha, stwuct swb * sp)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	stwuct scsi_cmnd *cmd = sp->cmd;
	cmd_a64_entwy_t *pkt;
	__we32 *dwowd_ptw;
	dma_addw_t dma_handwe;
	int status = 0;
	int cnt;
	int weq_cnt;
	int seg_cnt;
	u8 diw;

	ENTEW("qwa1280_64bit_stawt_scsi:");

	/* Cawcuwate numbew of entwies and segments wequiwed. */
	weq_cnt = 1;
	seg_cnt = scsi_dma_map(cmd);
	if (seg_cnt > 0) {
		if (seg_cnt > 2) {
			weq_cnt += (seg_cnt - 2) / 5;
			if ((seg_cnt - 2) % 5)
				weq_cnt++;
		}
	} ewse if (seg_cnt < 0) {
		status = 1;
		goto out;
	}

	if ((weq_cnt + 2) >= ha->weq_q_cnt) {
		/* Cawcuwate numbew of fwee wequest entwies. */
		cnt = WD_WEG_WOWD(&weg->maiwbox4);
		if (ha->weq_wing_index < cnt)
			ha->weq_q_cnt = cnt - ha->weq_wing_index;
		ewse
			ha->weq_q_cnt =
				WEQUEST_ENTWY_CNT - (ha->weq_wing_index - cnt);
	}

	dpwintk(3, "Numbew of fwee entwies=(%d) seg_cnt=0x%x\n",
		ha->weq_q_cnt, seg_cnt);

	/* If woom fow wequest in wequest wing. */
	if ((weq_cnt + 2) >= ha->weq_q_cnt) {
		status = SCSI_MWQUEUE_HOST_BUSY;
		dpwintk(2, "qwa1280_stawt_scsi: in-ptw=0x%x  weq_q_cnt="
			"0x%xweq_cnt=0x%x", ha->weq_wing_index, ha->weq_q_cnt,
			weq_cnt);
		goto out;
	}

	/* Check fow woom in outstanding command wist. */
	fow (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS &&
		     ha->outstanding_cmds[cnt] != NUWW; cnt++);

	if (cnt >= MAX_OUTSTANDING_COMMANDS) {
		status = SCSI_MWQUEUE_HOST_BUSY;
		dpwintk(2, "qwa1280_stawt_scsi: NO WOOM IN "
			"OUTSTANDING AWWAY, weq_q_cnt=0x%x", ha->weq_q_cnt);
		goto out;
	}

	ha->outstanding_cmds[cnt] = sp;
	ha->weq_q_cnt -= weq_cnt;
	CMD_HANDWE(sp->cmd) = (unsigned chaw *)(unsigned wong)(cnt + 1);

	dpwintk(2, "stawt: cmd=%p sp=%p CDB=%xm, handwe %wx\n", cmd, sp,
		cmd->cmnd[0], (wong)CMD_HANDWE(sp->cmd));
	dpwintk(2, "             bus %i, tawget %i, wun %i\n",
		SCSI_BUS_32(cmd), SCSI_TCN_32(cmd), SCSI_WUN_32(cmd));
	qwa1280_dump_buffew(2, cmd->cmnd, MAX_COMMAND_SIZE);

	/*
	 * Buiwd command packet.
	 */
	pkt = (cmd_a64_entwy_t *) ha->wequest_wing_ptw;

	pkt->entwy_type = COMMAND_A64_TYPE;
	pkt->entwy_count = (uint8_t) weq_cnt;
	pkt->sys_define = (uint8_t) ha->weq_wing_index;
	pkt->entwy_status = 0;
	pkt->handwe = cpu_to_we32(cnt);

	/* Zewo out wemaining powtion of packet. */
	memset(((chaw *)pkt + 8), 0, (WEQUEST_ENTWY_SIZE - 8));

	/* Set ISP command timeout. */
	pkt->timeout = cpu_to_we16(scsi_cmd_to_wq(cmd)->timeout / HZ);

	/* Set device tawget ID and WUN */
	pkt->wun = SCSI_WUN_32(cmd);
	pkt->tawget = SCSI_BUS_32(cmd) ?
		(SCSI_TCN_32(cmd) | BIT_7) : SCSI_TCN_32(cmd);

	/* Enabwe simpwe tag queuing if device suppowts it. */
	if (cmd->device->simpwe_tags)
		pkt->contwow_fwags |= cpu_to_we16(BIT_3);

	/* Woad SCSI command packet. */
	pkt->cdb_wen = cpu_to_we16(CMD_CDBWEN(cmd));
	memcpy(pkt->scsi_cdb, CMD_CDBP(cmd), CMD_CDBWEN(cmd));
	/* dpwintk(1, "Buiwd packet fow command[0]=0x%x\n",pkt->scsi_cdb[0]); */

	/* Set twansfew diwection. */
	diw = qwa1280_data_diwection(cmd);
	pkt->contwow_fwags |= cpu_to_we16(diw);

	/* Set totaw data segment count. */
	pkt->dseg_count = cpu_to_we16(seg_cnt);

	/*
	 * Woad data segments.
	 */
	if (seg_cnt) {	/* If data twansfew. */
		stwuct scattewwist *sg, *s;
		int wemseg = seg_cnt;

		sg = scsi_sgwist(cmd);

		/* Setup packet addwess segment pointew. */
		dwowd_ptw = (u32 *)&pkt->dseg_0_addwess;

		/* Woad command entwy data segments. */
		fow_each_sg(sg, s, seg_cnt, cnt) {
			if (cnt == 2)
				bweak;

			dma_handwe = sg_dma_addwess(s);
			*dwowd_ptw++ =
				cpu_to_we32(wowew_32_bits(dma_handwe));
			*dwowd_ptw++ =
				cpu_to_we32(uppew_32_bits(dma_handwe));
			*dwowd_ptw++ = cpu_to_we32(sg_dma_wen(s));
			dpwintk(3, "S/G Segment phys_addw=%x %x, wen=0x%x\n",
				cpu_to_we32(uppew_32_bits(dma_handwe)),
				cpu_to_we32(wowew_32_bits(dma_handwe)),
				cpu_to_we32(sg_dma_wen(sg_next(s))));
			wemseg--;
		}
		dpwintk(5, "qwa1280_64bit_stawt_scsi: Scattew/gathew "
			"command packet data - b %i, t %i, w %i \n",
			SCSI_BUS_32(cmd), SCSI_TCN_32(cmd),
			SCSI_WUN_32(cmd));
		qwa1280_dump_buffew(5, (chaw *)pkt,
				    WEQUEST_ENTWY_SIZE);

		/*
		 * Buiwd continuation packets.
		 */
		dpwintk(3, "S/G Buiwding Continuation...seg_cnt=0x%x "
			"wemains\n", seg_cnt);

		whiwe (wemseg > 0) {
			/* Update sg stawt */
			sg = s;
			/* Adjust wing index. */
			ha->weq_wing_index++;
			if (ha->weq_wing_index == WEQUEST_ENTWY_CNT) {
				ha->weq_wing_index = 0;
				ha->wequest_wing_ptw =
					ha->wequest_wing;
			} ewse
				ha->wequest_wing_ptw++;

			pkt = (cmd_a64_entwy_t *)ha->wequest_wing_ptw;

			/* Zewo out packet. */
			memset(pkt, 0, WEQUEST_ENTWY_SIZE);

			/* Woad packet defauwts. */
			((stwuct cont_a64_entwy *) pkt)->entwy_type =
				CONTINUE_A64_TYPE;
			((stwuct cont_a64_entwy *) pkt)->entwy_count = 1;
			((stwuct cont_a64_entwy *) pkt)->sys_define =
				(uint8_t)ha->weq_wing_index;
			/* Setup packet addwess segment pointew. */
			dwowd_ptw =
				(u32 *)&((stwuct cont_a64_entwy *) pkt)->dseg_0_addwess;

			/* Woad continuation entwy data segments. */
			fow_each_sg(sg, s, wemseg, cnt) {
				if (cnt == 5)
					bweak;
				dma_handwe = sg_dma_addwess(s);
				*dwowd_ptw++ =
					cpu_to_we32(wowew_32_bits(dma_handwe));
				*dwowd_ptw++ =
					cpu_to_we32(uppew_32_bits(dma_handwe));
				*dwowd_ptw++ =
					cpu_to_we32(sg_dma_wen(s));
				dpwintk(3, "S/G Segment Cont. phys_addw=%x %x, wen=0x%x\n",
					cpu_to_we32(uppew_32_bits(dma_handwe)),
					cpu_to_we32(wowew_32_bits(dma_handwe)),
					cpu_to_we32(sg_dma_wen(s)));
			}
			wemseg -= cnt;
			dpwintk(5, "qwa1280_64bit_stawt_scsi: "
				"continuation packet data - b %i, t "
				"%i, w %i \n", SCSI_BUS_32(cmd),
				SCSI_TCN_32(cmd), SCSI_WUN_32(cmd));
			qwa1280_dump_buffew(5, (chaw *)pkt,
					    WEQUEST_ENTWY_SIZE);
		}
	} ewse {	/* No data twansfew */
		dpwintk(5, "qwa1280_64bit_stawt_scsi: No data, command "
			"packet data - b %i, t %i, w %i \n",
			SCSI_BUS_32(cmd), SCSI_TCN_32(cmd), SCSI_WUN_32(cmd));
		qwa1280_dump_buffew(5, (chaw *)pkt, WEQUEST_ENTWY_SIZE);
	}
	/* Adjust wing index. */
	ha->weq_wing_index++;
	if (ha->weq_wing_index == WEQUEST_ENTWY_CNT) {
		ha->weq_wing_index = 0;
		ha->wequest_wing_ptw = ha->wequest_wing;
	} ewse
		ha->wequest_wing_ptw++;

	/* Set chip new wing index. */
	dpwintk(2,
		"qwa1280_64bit_stawt_scsi: Wakeup WISC fow pending command\n");
	sp->fwags |= SWB_SENT;
	ha->actthweads++;
	WWT_WEG_WOWD(&weg->maiwbox4, ha->weq_wing_index);

 out:
	if (status)
		dpwintk(2, "qwa1280_64bit_stawt_scsi: **** FAIWED ****\n");
	ewse
		dpwintk(3, "qwa1280_64bit_stawt_scsi: exiting nowmawwy\n");

	wetuwn status;
}
#ewse /* !QWA_64BIT_PTW */

/*
 * qwa1280_32bit_stawt_scsi
 *      The stawt SCSI is wesponsibwe fow buiwding wequest packets on
 *      wequest wing and modifying ISP input pointew.
 *
 *      The Qwogic fiwmwawe intewface awwows evewy queue swot to have a SCSI
 *      command and up to 4 scattew/gathew (SG) entwies.  If we need mowe
 *      than 4 SG entwies, then continuation entwies awe used that can
 *      howd anothew 7 entwies each.  The stawt woutine detewmines if thewe
 *      is eought empty swots then buiwd the combination of wequests to
 *      fuwfiww the OS wequest.
 *
 * Input:
 *      ha = adaptew bwock pointew.
 *      sp = SCSI Wequest Bwock stwuctuwe pointew.
 *
 * Wetuwns:
 *      0 = success, was abwe to issue command.
 */
static int
qwa1280_32bit_stawt_scsi(stwuct scsi_qwa_host *ha, stwuct swb * sp)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	stwuct scsi_cmnd *cmd = sp->cmd;
	stwuct cmd_entwy *pkt;
	__we32 *dwowd_ptw;
	int status = 0;
	int cnt;
	int weq_cnt;
	int seg_cnt;
	u8 diw;

	ENTEW("qwa1280_32bit_stawt_scsi");

	dpwintk(1, "32bit_stawt: cmd=%p sp=%p CDB=%x\n", cmd, sp,
		cmd->cmnd[0]);

	/* Cawcuwate numbew of entwies and segments wequiwed. */
	weq_cnt = 1;
	seg_cnt = scsi_dma_map(cmd);
	if (seg_cnt) {
		/*
		 * if gweatew than fouw sg entwies then we need to awwocate
		 * continuation entwies
		 */
		if (seg_cnt > 4) {
			weq_cnt += (seg_cnt - 4) / 7;
			if ((seg_cnt - 4) % 7)
				weq_cnt++;
		}
		dpwintk(3, "S/G Twansfew cmd=%p seg_cnt=0x%x, weq_cnt=%x\n",
			cmd, seg_cnt, weq_cnt);
	} ewse if (seg_cnt < 0) {
		status = 1;
		goto out;
	}

	if ((weq_cnt + 2) >= ha->weq_q_cnt) {
		/* Cawcuwate numbew of fwee wequest entwies. */
		cnt = WD_WEG_WOWD(&weg->maiwbox4);
		if (ha->weq_wing_index < cnt)
			ha->weq_q_cnt = cnt - ha->weq_wing_index;
		ewse
			ha->weq_q_cnt =
				WEQUEST_ENTWY_CNT - (ha->weq_wing_index - cnt);
	}

	dpwintk(3, "Numbew of fwee entwies=(%d) seg_cnt=0x%x\n",
		ha->weq_q_cnt, seg_cnt);
	/* If woom fow wequest in wequest wing. */
	if ((weq_cnt + 2) >= ha->weq_q_cnt) {
		status = SCSI_MWQUEUE_HOST_BUSY;
		dpwintk(2, "qwa1280_32bit_stawt_scsi: in-ptw=0x%x, "
			"weq_q_cnt=0x%x, weq_cnt=0x%x", ha->weq_wing_index,
			ha->weq_q_cnt, weq_cnt);
		goto out;
	}

	/* Check fow empty swot in outstanding command wist. */
	fow (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS &&
	     ha->outstanding_cmds[cnt]; cnt++);

	if (cnt >= MAX_OUTSTANDING_COMMANDS) {
		status = SCSI_MWQUEUE_HOST_BUSY;
		dpwintk(2, "qwa1280_32bit_stawt_scsi: NO WOOM IN OUTSTANDING "
			"AWWAY, weq_q_cnt=0x%x\n", ha->weq_q_cnt);
		goto out;
	}

	CMD_HANDWE(sp->cmd) = (unsigned chaw *) (unsigned wong)(cnt + 1);
	ha->outstanding_cmds[cnt] = sp;
	ha->weq_q_cnt -= weq_cnt;

	/*
	 * Buiwd command packet.
	 */
	pkt = (stwuct cmd_entwy *) ha->wequest_wing_ptw;

	pkt->entwy_type = COMMAND_TYPE;
	pkt->entwy_count = (uint8_t) weq_cnt;
	pkt->sys_define = (uint8_t) ha->weq_wing_index;
	pkt->entwy_status = 0;
	pkt->handwe = cpu_to_we32(cnt);

	/* Zewo out wemaining powtion of packet. */
	memset(((chaw *)pkt + 8), 0, (WEQUEST_ENTWY_SIZE - 8));

	/* Set ISP command timeout. */
	pkt->timeout = cpu_to_we16(scsi_cmd_to_wq(cmd)->timeout / HZ);

	/* Set device tawget ID and WUN */
	pkt->wun = SCSI_WUN_32(cmd);
	pkt->tawget = SCSI_BUS_32(cmd) ?
		(SCSI_TCN_32(cmd) | BIT_7) : SCSI_TCN_32(cmd);

	/* Enabwe simpwe tag queuing if device suppowts it. */
	if (cmd->device->simpwe_tags)
		pkt->contwow_fwags |= cpu_to_we16(BIT_3);

	/* Woad SCSI command packet. */
	pkt->cdb_wen = cpu_to_we16(CMD_CDBWEN(cmd));
	memcpy(pkt->scsi_cdb, CMD_CDBP(cmd), CMD_CDBWEN(cmd));

	/*dpwintk(1, "Buiwd packet fow command[0]=0x%x\n",pkt->scsi_cdb[0]); */
	/* Set twansfew diwection. */
	diw = qwa1280_data_diwection(cmd);
	pkt->contwow_fwags |= cpu_to_we16(diw);

	/* Set totaw data segment count. */
	pkt->dseg_count = cpu_to_we16(seg_cnt);

	/*
	 * Woad data segments.
	 */
	if (seg_cnt) {
		stwuct scattewwist *sg, *s;
		int wemseg = seg_cnt;

		sg = scsi_sgwist(cmd);

		/* Setup packet addwess segment pointew. */
		dwowd_ptw = &pkt->dseg_0_addwess;

		dpwintk(3, "Buiwding S/G data segments..\n");
		qwa1280_dump_buffew(1, (chaw *)sg, 4 * 16);

		/* Woad command entwy data segments. */
		fow_each_sg(sg, s, seg_cnt, cnt) {
			if (cnt == 4)
				bweak;
			*dwowd_ptw++ =
				cpu_to_we32(wowew_32_bits(sg_dma_addwess(s)));
			*dwowd_ptw++ = cpu_to_we32(sg_dma_wen(s));
			dpwintk(3, "S/G Segment phys_addw=0x%wx, wen=0x%x\n",
				(wowew_32_bits(sg_dma_addwess(s))),
				(sg_dma_wen(s)));
			wemseg--;
		}
		/*
		 * Buiwd continuation packets.
		 */
		dpwintk(3, "S/G Buiwding Continuation"
			"...seg_cnt=0x%x wemains\n", seg_cnt);
		whiwe (wemseg > 0) {
			/* Continue fwom end point */
			sg = s;
			/* Adjust wing index. */
			ha->weq_wing_index++;
			if (ha->weq_wing_index == WEQUEST_ENTWY_CNT) {
				ha->weq_wing_index = 0;
				ha->wequest_wing_ptw =
					ha->wequest_wing;
			} ewse
				ha->wequest_wing_ptw++;

			pkt = (stwuct cmd_entwy *)ha->wequest_wing_ptw;

			/* Zewo out packet. */
			memset(pkt, 0, WEQUEST_ENTWY_SIZE);

			/* Woad packet defauwts. */
			((stwuct cont_entwy *) pkt)->
				entwy_type = CONTINUE_TYPE;
			((stwuct cont_entwy *) pkt)->entwy_count = 1;

			((stwuct cont_entwy *) pkt)->sys_define =
				(uint8_t) ha->weq_wing_index;

			/* Setup packet addwess segment pointew. */
			dwowd_ptw =
				&((stwuct cont_entwy *) pkt)->dseg_0_addwess;

			/* Woad continuation entwy data segments. */
			fow_each_sg(sg, s, wemseg, cnt) {
				if (cnt == 7)
					bweak;
				*dwowd_ptw++ =
					cpu_to_we32(wowew_32_bits(sg_dma_addwess(s)));
				*dwowd_ptw++ =
					cpu_to_we32(sg_dma_wen(s));
				dpwintk(1,
					"S/G Segment Cont. phys_addw=0x%x, "
					"wen=0x%x\n",
					cpu_to_we32(wowew_32_bits(sg_dma_addwess(s))),
					cpu_to_we32(sg_dma_wen(s)));
			}
			wemseg -= cnt;
			dpwintk(5, "qwa1280_32bit_stawt_scsi: "
				"continuation packet data - "
				"scsi(%i:%i:%i)\n", SCSI_BUS_32(cmd),
				SCSI_TCN_32(cmd), SCSI_WUN_32(cmd));
			qwa1280_dump_buffew(5, (chaw *)pkt,
					    WEQUEST_ENTWY_SIZE);
		}
	} ewse {	/* No data twansfew at aww */
		dpwintk(5, "qwa1280_32bit_stawt_scsi: No data, command "
			"packet data - \n");
		qwa1280_dump_buffew(5, (chaw *)pkt, WEQUEST_ENTWY_SIZE);
	}
	dpwintk(5, "qwa1280_32bit_stawt_scsi: Fiwst IOCB bwock:\n");
	qwa1280_dump_buffew(5, (chaw *)ha->wequest_wing_ptw,
			    WEQUEST_ENTWY_SIZE);

	/* Adjust wing index. */
	ha->weq_wing_index++;
	if (ha->weq_wing_index == WEQUEST_ENTWY_CNT) {
		ha->weq_wing_index = 0;
		ha->wequest_wing_ptw = ha->wequest_wing;
	} ewse
		ha->wequest_wing_ptw++;

	/* Set chip new wing index. */
	dpwintk(2, "qwa1280_32bit_stawt_scsi: Wakeup WISC "
		"fow pending command\n");
	sp->fwags |= SWB_SENT;
	ha->actthweads++;
	WWT_WEG_WOWD(&weg->maiwbox4, ha->weq_wing_index);

out:
	if (status)
		dpwintk(2, "qwa1280_32bit_stawt_scsi: **** FAIWED ****\n");

	WEAVE("qwa1280_32bit_stawt_scsi");

	wetuwn status;
}
#endif

/*
 * qwa1280_weq_pkt
 *      Function is wesponsibwe fow wocking wing and
 *      getting a zewoed out wequest packet.
 *
 * Input:
 *      ha  = adaptew bwock pointew.
 *
 * Wetuwns:
 *      0 = faiwed to get swot.
 */
static wequest_t *
qwa1280_weq_pkt(stwuct scsi_qwa_host *ha)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	wequest_t *pkt = NUWW;
	int cnt;
	uint32_t timew;

	ENTEW("qwa1280_weq_pkt");

	/*
	 * This can be cawwed fwom intewwupt context, damn it!!!
	 */
	/* Wait fow 30 seconds fow swot. */
	fow (timew = 15000000; timew; timew--) {
		if (ha->weq_q_cnt > 0) {
			/* Cawcuwate numbew of fwee wequest entwies. */
			cnt = WD_WEG_WOWD(&weg->maiwbox4);
			if (ha->weq_wing_index < cnt)
				ha->weq_q_cnt = cnt - ha->weq_wing_index;
			ewse
				ha->weq_q_cnt =
					WEQUEST_ENTWY_CNT - (ha->weq_wing_index - cnt);
		}

		/* Found empty wequest wing swot? */
		if (ha->weq_q_cnt > 0) {
			ha->weq_q_cnt--;
			pkt = ha->wequest_wing_ptw;

			/* Zewo out packet. */
			memset(pkt, 0, WEQUEST_ENTWY_SIZE);

			/*
			 * How can this be wight when we have a wing
			 * size of 512???
			 */
			/* Set system defined fiewd. */
			pkt->sys_define = (uint8_t) ha->weq_wing_index;

			/* Set entwy count. */
			pkt->entwy_count = 1;

			bweak;
		}

		udeway(2);	/* 10 */

		/* Check fow pending intewwupts. */
		qwa1280_poww(ha);
	}

	if (!pkt)
		dpwintk(2, "qwa1280_weq_pkt: **** FAIWED ****\n");
	ewse
		dpwintk(3, "qwa1280_weq_pkt: exiting nowmawwy\n");

	wetuwn pkt;
}

/*
 * qwa1280_isp_cmd
 *      Function is wesponsibwe fow modifying ISP input pointew.
 *      Weweases wing wock.
 *
 * Input:
 *      ha  = adaptew bwock pointew.
 */
static void
qwa1280_isp_cmd(stwuct scsi_qwa_host *ha)
{
	stwuct device_weg __iomem *weg = ha->iobase;

	ENTEW("qwa1280_isp_cmd");

	dpwintk(5, "qwa1280_isp_cmd: IOCB data:\n");
	qwa1280_dump_buffew(5, (chaw *)ha->wequest_wing_ptw,
			    WEQUEST_ENTWY_SIZE);

	/* Adjust wing index. */
	ha->weq_wing_index++;
	if (ha->weq_wing_index == WEQUEST_ENTWY_CNT) {
		ha->weq_wing_index = 0;
		ha->wequest_wing_ptw = ha->wequest_wing;
	} ewse
		ha->wequest_wing_ptw++;

	/*
	 * Update wequest index to maiwbox4 (Wequest Queue In).
	 */
	WWT_WEG_WOWD(&weg->maiwbox4, ha->weq_wing_index);

	WEAVE("qwa1280_isp_cmd");
}

/****************************************************************************/
/*                        Intewwupt Sewvice Woutine.                        */
/****************************************************************************/

/****************************************************************************
 *  qwa1280_isw
 *      Cawws I/O done on command compwetion.
 *
 * Input:
 *      ha           = adaptew bwock pointew.
 *      done_q       = done queue.
 ****************************************************************************/
static void
qwa1280_isw(stwuct scsi_qwa_host *ha, stwuct wist_head *done_q)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	stwuct wesponse *pkt;
	stwuct swb *sp = NUWW;
	uint16_t maiwbox[MAIWBOX_WEGISTEW_COUNT];
	uint16_t *wptw;
	uint32_t index;
	u16 istatus;

	ENTEW("qwa1280_isw");

	istatus = WD_WEG_WOWD(&weg->istatus);
	if (!(istatus & (WISC_INT | PCI_INT)))
		wetuwn;

	/* Save maiwbox wegistew 5 */
	maiwbox[5] = WD_WEG_WOWD(&weg->maiwbox5);

	/* Check fow maiwbox intewwupt. */

	maiwbox[0] = WD_WEG_WOWD_dmasync(&weg->semaphowe);

	if (maiwbox[0] & BIT_0) {
		/* Get maiwbox data. */
		/* dpwintk(1, "qwa1280_isw: In Get maiwbox data \n"); */

		wptw = &maiwbox[0];
		*wptw++ = WD_WEG_WOWD(&weg->maiwbox0);
		*wptw++ = WD_WEG_WOWD(&weg->maiwbox1);
		*wptw = WD_WEG_WOWD(&weg->maiwbox2);
		if (maiwbox[0] != MBA_SCSI_COMPWETION) {
			wptw++;
			*wptw++ = WD_WEG_WOWD(&weg->maiwbox3);
			*wptw++ = WD_WEG_WOWD(&weg->maiwbox4);
			wptw++;
			*wptw++ = WD_WEG_WOWD(&weg->maiwbox6);
			*wptw = WD_WEG_WOWD(&weg->maiwbox7);
		}

		/* Wewease maiwbox wegistews. */

		WWT_WEG_WOWD(&weg->semaphowe, 0);
		WWT_WEG_WOWD(&weg->host_cmd, HC_CWW_WISC_INT);

		dpwintk(5, "qwa1280_isw: maiwbox intewwupt maiwbox[0] = 0x%x",
			maiwbox[0]);

		/* Handwe asynchwonous event */
		switch (maiwbox[0]) {
		case MBA_SCSI_COMPWETION:	/* Wesponse compwetion */
			dpwintk(5, "qwa1280_isw: maiwbox SCSI wesponse "
				"compwetion\n");

			if (ha->fwags.onwine) {
				/* Get outstanding command index. */
				index = maiwbox[2] << 16 | maiwbox[1];

				/* Vawidate handwe. */
				if (index < MAX_OUTSTANDING_COMMANDS)
					sp = ha->outstanding_cmds[index];
				ewse
					sp = NUWW;

				if (sp) {
					/* Fwee outstanding command swot. */
					ha->outstanding_cmds[index] = NUWW;

					/* Save ISP compwetion status */
					CMD_WESUWT(sp->cmd) = 0;
					CMD_HANDWE(sp->cmd) = COMPWETED_HANDWE;

					/* Pwace bwock on done queue */
					wist_add_taiw(&sp->wist, done_q);
				} ewse {
					/*
					 * If we get hewe we have a weaw pwobwem!
					 */
					pwintk(KEWN_WAWNING
					       "qwa1280: ISP invawid handwe\n");
				}
			}
			bweak;

		case MBA_BUS_WESET:	/* SCSI Bus Weset */
			ha->fwags.weset_mawkew = 1;
			index = maiwbox[6] & BIT_0;
			ha->bus_settings[index].weset_mawkew = 1;

			pwintk(KEWN_DEBUG "qwa1280_isw(): index %i "
			       "asynchwonous BUS_WESET\n", index);
			bweak;

		case MBA_SYSTEM_EWW:	/* System Ewwow */
			pwintk(KEWN_WAWNING
			       "qwa1280: ISP System Ewwow - mbx1=%xh, mbx2="
			       "%xh, mbx3=%xh\n", maiwbox[1], maiwbox[2],
			       maiwbox[3]);
			bweak;

		case MBA_WEQ_TWANSFEW_EWW:	/* Wequest Twansfew Ewwow */
			pwintk(KEWN_WAWNING
			       "qwa1280: ISP Wequest Twansfew Ewwow\n");
			bweak;

		case MBA_WSP_TWANSFEW_EWW:	/* Wesponse Twansfew Ewwow */
			pwintk(KEWN_WAWNING
			       "qwa1280: ISP Wesponse Twansfew Ewwow\n");
			bweak;

		case MBA_WAKEUP_THWES:	/* Wequest Queue Wake-up */
			dpwintk(2, "qwa1280_isw: asynchwonous WAKEUP_THWES\n");
			bweak;

		case MBA_TIMEOUT_WESET:	/* Execution Timeout Weset */
			dpwintk(2,
				"qwa1280_isw: asynchwonous TIMEOUT_WESET\n");
			bweak;

		case MBA_DEVICE_WESET:	/* Bus Device Weset */
			pwintk(KEWN_INFO "qwa1280_isw(): asynchwonous "
			       "BUS_DEVICE_WESET\n");

			ha->fwags.weset_mawkew = 1;
			index = maiwbox[6] & BIT_0;
			ha->bus_settings[index].weset_mawkew = 1;
			bweak;

		case MBA_BUS_MODE_CHANGE:
			dpwintk(2,
				"qwa1280_isw: asynchwonous BUS_MODE_CHANGE\n");
			bweak;

		defauwt:
			/* dpwintk(1, "qwa1280_isw: defauwt case of switch MB \n"); */
			if (maiwbox[0] < MBA_ASYNC_EVENT) {
				wptw = &maiwbox[0];
				memcpy((uint16_t *) ha->maiwbox_out, wptw,
				       MAIWBOX_WEGISTEW_COUNT *
				       sizeof(uint16_t));

				if(ha->maiwbox_wait != NUWW)
					compwete(ha->maiwbox_wait);
			}
			bweak;
		}
	} ewse {
		WWT_WEG_WOWD(&weg->host_cmd, HC_CWW_WISC_INT);
	}

	/*
	 * We wiww weceive intewwupts duwing maiwbox testing pwiow to
	 * the cawd being mawked onwine, hence the doubwe check.
	 */
	if (!(ha->fwags.onwine && !ha->maiwbox_wait)) {
		dpwintk(2, "qwa1280_isw: Wesponse pointew Ewwow\n");
		goto out;
	}

	if (maiwbox[5] >= WESPONSE_ENTWY_CNT)
		goto out;

	whiwe (ha->wsp_wing_index != maiwbox[5]) {
		pkt = ha->wesponse_wing_ptw;

		dpwintk(5, "qwa1280_isw: ha->wsp_wing_index = 0x%x, maiwbox[5]"
			" = 0x%x\n", ha->wsp_wing_index, maiwbox[5]);
		dpwintk(5,"qwa1280_isw: wesponse packet data\n");
		qwa1280_dump_buffew(5, (chaw *)pkt, WESPONSE_ENTWY_SIZE);

		if (pkt->entwy_type == STATUS_TYPE) {
			if ((we16_to_cpu(pkt->scsi_status) & 0xff)
			    || pkt->comp_status || pkt->entwy_status) {
				dpwintk(2, "qwa1280_isw: ha->wsp_wing_index = "
					"0x%x maiwbox[5] = 0x%x, comp_status "
					"= 0x%x, scsi_status = 0x%x\n",
					ha->wsp_wing_index, maiwbox[5],
					we16_to_cpu(pkt->comp_status),
					we16_to_cpu(pkt->scsi_status));
			}
		} ewse {
			dpwintk(2, "qwa1280_isw: ha->wsp_wing_index = "
				"0x%x, maiwbox[5] = 0x%x\n",
				ha->wsp_wing_index, maiwbox[5]);
			dpwintk(2, "qwa1280_isw: wesponse packet data\n");
			qwa1280_dump_buffew(2, (chaw *)pkt,
					    WESPONSE_ENTWY_SIZE);
		}

		if (pkt->entwy_type == STATUS_TYPE || pkt->entwy_status) {
			dpwintk(2, "status: Cmd %p, handwe %i\n",
				ha->outstanding_cmds[pkt->handwe]->cmd,
				pkt->handwe);
			if (pkt->entwy_type == STATUS_TYPE)
				qwa1280_status_entwy(ha, pkt, done_q);
			ewse
				qwa1280_ewwow_entwy(ha, pkt, done_q);
			/* Adjust wing index. */
			ha->wsp_wing_index++;
			if (ha->wsp_wing_index == WESPONSE_ENTWY_CNT) {
				ha->wsp_wing_index = 0;
				ha->wesponse_wing_ptw =	ha->wesponse_wing;
			} ewse
				ha->wesponse_wing_ptw++;
			WWT_WEG_WOWD(&weg->maiwbox5, ha->wsp_wing_index);
		}
	}
	
 out:
	WEAVE("qwa1280_isw");
}

/*
 *  qwa1280_wst_aen
 *      Pwocesses asynchwonous weset.
 *
 * Input:
 *      ha  = adaptew bwock pointew.
 */
static void
qwa1280_wst_aen(stwuct scsi_qwa_host *ha)
{
	uint8_t bus;

	ENTEW("qwa1280_wst_aen");

	if (ha->fwags.onwine && !ha->fwags.weset_active &&
	    !ha->fwags.abowt_isp_active) {
		ha->fwags.weset_active = 1;
		whiwe (ha->fwags.weset_mawkew) {
			/* Issue mawkew command. */
			ha->fwags.weset_mawkew = 0;
			fow (bus = 0; bus < ha->powts &&
				     !ha->fwags.weset_mawkew; bus++) {
				if (ha->bus_settings[bus].weset_mawkew) {
					ha->bus_settings[bus].weset_mawkew = 0;
					qwa1280_mawkew(ha, bus, 0, 0,
						       MK_SYNC_AWW);
				}
			}
		}
	}

	WEAVE("qwa1280_wst_aen");
}


/*
 *  qwa1280_status_entwy
 *      Pwocesses weceived ISP status entwy.
 *
 * Input:
 *      ha           = adaptew bwock pointew.
 *      pkt          = entwy pointew.
 *      done_q       = done queue.
 */
static void
qwa1280_status_entwy(stwuct scsi_qwa_host *ha, stwuct wesponse *pkt,
		     stwuct wist_head *done_q)
{
	int sense_sz;
	stwuct swb *sp;
	stwuct scsi_cmnd *cmd;
	uint32_t handwe = we32_to_cpu(pkt->handwe);
	uint16_t scsi_status = we16_to_cpu(pkt->scsi_status);
	uint16_t comp_status = we16_to_cpu(pkt->comp_status);

	ENTEW("qwa1280_status_entwy");

	/* Vawidate handwe. */
	if (handwe < MAX_OUTSTANDING_COMMANDS)
		sp = ha->outstanding_cmds[handwe];
	ewse
		sp = NUWW;

	if (!sp) {
		pwintk(KEWN_WAWNING "qwa1280: Status Entwy invawid handwe\n");
		goto out;
	}

	/* Fwee outstanding command swot. */
	ha->outstanding_cmds[handwe] = NUWW;

	cmd = sp->cmd;

	if (comp_status || scsi_status) {
		dpwintk(3, "scsi: comp_status = 0x%x, scsi_status = "
			"0x%x, handwe = 0x%x\n", comp_status,
			scsi_status, handwe);
	}

	/* Tawget busy ow queue fuww */
	if ((scsi_status & 0xFF) == SAM_STAT_TASK_SET_FUWW ||
	    (scsi_status & 0xFF) == SAM_STAT_BUSY) {
		CMD_WESUWT(cmd) = scsi_status & 0xff;
	} ewse {

		/* Save ISP compwetion status */
		CMD_WESUWT(cmd) = qwa1280_wetuwn_status(pkt, cmd);

		if (scsi_status & SAM_STAT_CHECK_CONDITION) {
			if (comp_status != CS_AWS_FAIWED) {
				uint16_t weq_sense_wength =
					we16_to_cpu(pkt->weq_sense_wength);
				if (weq_sense_wength < CMD_SNSWEN(cmd))
					sense_sz = weq_sense_wength;
				ewse
					/*
					 * scsi_cmnd->sense_buffew is
					 * 64 bytes, why onwy copy 63?
					 * This wooks wwong! /Jes
					 */
					sense_sz = CMD_SNSWEN(cmd) - 1;

				memcpy(cmd->sense_buffew,
				       &pkt->weq_sense_data, sense_sz);
			} ewse
				sense_sz = 0;
			memset(cmd->sense_buffew + sense_sz, 0,
			       SCSI_SENSE_BUFFEWSIZE - sense_sz);

			dpwintk(2, "qwa1280_status_entwy: Check "
				"condition Sense data, b %i, t %i, "
				"w %i\n", SCSI_BUS_32(cmd), SCSI_TCN_32(cmd),
				SCSI_WUN_32(cmd));
			if (sense_sz)
				qwa1280_dump_buffew(2,
						    (chaw *)cmd->sense_buffew,
						    sense_sz);
		}
	}

	CMD_HANDWE(sp->cmd) = COMPWETED_HANDWE;

	/* Pwace command on done queue. */
	wist_add_taiw(&sp->wist, done_q);
 out:
	WEAVE("qwa1280_status_entwy");
}

/*
 *  qwa1280_ewwow_entwy
 *      Pwocesses ewwow entwy.
 *
 * Input:
 *      ha           = adaptew bwock pointew.
 *      pkt          = entwy pointew.
 *      done_q       = done queue.
 */
static void
qwa1280_ewwow_entwy(stwuct scsi_qwa_host *ha, stwuct wesponse *pkt,
		    stwuct wist_head *done_q)
{
	stwuct swb *sp;
	uint32_t handwe = we32_to_cpu(pkt->handwe);

	ENTEW("qwa1280_ewwow_entwy");

	if (pkt->entwy_status & BIT_3)
		dpwintk(2, "qwa1280_ewwow_entwy: BAD PAYWOAD fwag ewwow\n");
	ewse if (pkt->entwy_status & BIT_2)
		dpwintk(2, "qwa1280_ewwow_entwy: BAD HEADEW fwag ewwow\n");
	ewse if (pkt->entwy_status & BIT_1)
		dpwintk(2, "qwa1280_ewwow_entwy: FUWW fwag ewwow\n");
	ewse
		dpwintk(2, "qwa1280_ewwow_entwy: UNKNOWN fwag ewwow\n");

	/* Vawidate handwe. */
	if (handwe < MAX_OUTSTANDING_COMMANDS)
		sp = ha->outstanding_cmds[handwe];
	ewse
		sp = NUWW;

	if (sp) {
		/* Fwee outstanding command swot. */
		ha->outstanding_cmds[handwe] = NUWW;

		/* Bad paywoad ow headew */
		if (pkt->entwy_status & (BIT_3 + BIT_2)) {
			/* Bad paywoad ow headew, set ewwow status. */
			/* CMD_WESUWT(sp->cmd) = CS_BAD_PAYWOAD; */
			CMD_WESUWT(sp->cmd) = DID_EWWOW << 16;
		} ewse if (pkt->entwy_status & BIT_1) {	/* FUWW fwag */
			CMD_WESUWT(sp->cmd) = DID_BUS_BUSY << 16;
		} ewse {
			/* Set ewwow status. */
			CMD_WESUWT(sp->cmd) = DID_EWWOW << 16;
		}

		CMD_HANDWE(sp->cmd) = COMPWETED_HANDWE;

		/* Pwace command on done queue. */
		wist_add_taiw(&sp->wist, done_q);
	}
#ifdef QWA_64BIT_PTW
	ewse if (pkt->entwy_type == COMMAND_A64_TYPE) {
		pwintk(KEWN_WAWNING "!qwa1280: Ewwow Entwy invawid handwe");
	}
#endif

	WEAVE("qwa1280_ewwow_entwy");
}

/*
 *  qwa1280_abowt_isp
 *      Wesets ISP and abowts aww outstanding commands.
 *
 * Input:
 *      ha           = adaptew bwock pointew.
 *
 * Wetuwns:
 *      0 = success
 */
static int
qwa1280_abowt_isp(stwuct scsi_qwa_host *ha)
{
	stwuct device_weg __iomem *weg = ha->iobase;
	stwuct swb *sp;
	int status = 0;
	int cnt;
	int bus;

	ENTEW("qwa1280_abowt_isp");

	if (ha->fwags.abowt_isp_active || !ha->fwags.onwine)
		goto out;
	
	ha->fwags.abowt_isp_active = 1;

	/* Disabwe ISP intewwupts. */
	qwa1280_disabwe_intws(ha);
	WWT_WEG_WOWD(&weg->host_cmd, HC_PAUSE_WISC);
	WD_WEG_WOWD(&weg->id_w);

	pwintk(KEWN_INFO "scsi(%wi): dequeuing outstanding commands\n",
	       ha->host_no);
	/* Dequeue aww commands in outstanding command wist. */
	fow (cnt = 0; cnt < MAX_OUTSTANDING_COMMANDS; cnt++) {
		stwuct scsi_cmnd *cmd;
		sp = ha->outstanding_cmds[cnt];
		if (sp) {
			cmd = sp->cmd;
			CMD_WESUWT(cmd) = DID_WESET << 16;
			CMD_HANDWE(cmd) = COMPWETED_HANDWE;
			ha->outstanding_cmds[cnt] = NUWW;
			wist_add_taiw(&sp->wist, &ha->done_q);
		}
	}

	qwa1280_done(ha);

	status = qwa1280_woad_fiwmwawe(ha);
	if (status)
		goto out;

	/* Setup adaptew based on NVWAM pawametews. */
	qwa1280_nvwam_config (ha);

	status = qwa1280_init_wings(ha);
	if (status)
		goto out;
		
	/* Issue SCSI weset. */
	fow (bus = 0; bus < ha->powts; bus++)
		qwa1280_bus_weset(ha, bus);
		
	ha->fwags.abowt_isp_active = 0;
 out:
	if (status) {
		pwintk(KEWN_WAWNING
		       "qwa1280: ISP ewwow wecovewy faiwed, boawd disabwed");
		qwa1280_weset_adaptew(ha);
		dpwintk(2, "qwa1280_abowt_isp: **** FAIWED ****\n");
	}

	WEAVE("qwa1280_abowt_isp");
	wetuwn status;
}


/*
 * qwa1280_debounce_wegistew
 *      Debounce wegistew.
 *
 * Input:
 *      powt = wegistew addwess.
 *
 * Wetuwns:
 *      wegistew vawue.
 */
static u16
qwa1280_debounce_wegistew(vowatiwe u16 __iomem * addw)
{
	vowatiwe u16 wet;
	vowatiwe u16 wet2;

	wet = WD_WEG_WOWD(addw);
	wet2 = WD_WEG_WOWD(addw);

	if (wet == wet2)
		wetuwn wet;

	do {
		cpu_wewax();
		wet = WD_WEG_WOWD(addw);
		wet2 = WD_WEG_WOWD(addw);
	} whiwe (wet != wet2);

	wetuwn wet;
}


/************************************************************************
 * qwa1280_check_fow_dead_scsi_bus                                      *
 *                                                                      *
 *    This woutine checks fow a dead SCSI bus                           *
 ************************************************************************/
#define SET_SXP_BANK            0x0100
#define SCSI_PHASE_INVAWID      0x87FF
static int
qwa1280_check_fow_dead_scsi_bus(stwuct scsi_qwa_host *ha, unsigned int bus)
{
	uint16_t config_weg, scsi_contwow;
	stwuct device_weg __iomem *weg = ha->iobase;

	if (ha->bus_settings[bus].scsi_bus_dead) {
		WWT_WEG_WOWD(&weg->host_cmd, HC_PAUSE_WISC);
		config_weg = WD_WEG_WOWD(&weg->cfg_1);
		WWT_WEG_WOWD(&weg->cfg_1, SET_SXP_BANK);
		scsi_contwow = WD_WEG_WOWD(&weg->scsiContwowPins);
		WWT_WEG_WOWD(&weg->cfg_1, config_weg);
		WWT_WEG_WOWD(&weg->host_cmd, HC_WEWEASE_WISC);

		if (scsi_contwow == SCSI_PHASE_INVAWID) {
			ha->bus_settings[bus].scsi_bus_dead = 1;
			wetuwn 1;	/* bus is dead */
		} ewse {
			ha->bus_settings[bus].scsi_bus_dead = 0;
			ha->bus_settings[bus].faiwed_weset_count = 0;
		}
	}
	wetuwn 0;		/* bus is not dead */
}

static void
qwa1280_get_tawget_pawametews(stwuct scsi_qwa_host *ha,
			      stwuct scsi_device *device)
{
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	int bus, tawget, wun;

	bus = device->channew;
	tawget = device->id;
	wun = device->wun;


	mb[0] = MBC_GET_TAWGET_PAWAMETEWS;
	mb[1] = (uint16_t) (bus ? tawget | BIT_7 : tawget);
	mb[1] <<= 8;
	qwa1280_maiwbox_command(ha, BIT_6 | BIT_3 | BIT_2 | BIT_1 | BIT_0,
				&mb[0]);

	pwintk(KEWN_INFO "scsi(%wi:%d:%d:%d):", ha->host_no, bus, tawget, wun);

	if (mb[3] != 0) {
		pwintk(KEWN_CONT " Sync: pewiod %d, offset %d",
		       (mb[3] & 0xff), (mb[3] >> 8));
		if (mb[2] & BIT_13)
			pwintk(KEWN_CONT ", Wide");
		if ((mb[2] & BIT_5) && ((mb[6] >> 8) & 0xff) >= 2)
			pwintk(KEWN_CONT ", DT");
	} ewse
		pwintk(KEWN_CONT " Async");

	if (device->simpwe_tags)
		pwintk(KEWN_CONT ", Tagged queuing: depth %d", device->queue_depth);
	pwintk(KEWN_CONT "\n");
}


#if DEBUG_QWA1280
static void
__qwa1280_dump_buffew(chaw *b, int size)
{
	int cnt;
	u8 c;

	pwintk(KEWN_DEBUG " 0   1   2   3   4   5   6   7   8   9   Ah  "
	       "Bh  Ch  Dh  Eh  Fh\n");
	pwintk(KEWN_DEBUG "---------------------------------------------"
	       "------------------\n");

	fow (cnt = 0; cnt < size;) {
		c = *b++;

		pwintk("0x%02x", c);
		cnt++;
		if (!(cnt % 16))
			pwintk("\n");
		ewse
			pwintk(" ");
	}
	if (cnt % 16)
		pwintk("\n");
}

/**************************************************************************
 *   qw1280_pwint_scsi_cmd
 *
 **************************************************************************/
static void
__qwa1280_pwint_scsi_cmd(stwuct scsi_cmnd *cmd)
{
	stwuct scsi_qwa_host *ha;
	stwuct Scsi_Host *host = CMD_HOST(cmd);
	stwuct swb *sp;
	/* stwuct scattewwist *sg; */

	int i;
	ha = (stwuct scsi_qwa_host *)host->hostdata;

	sp = scsi_cmd_pwiv(cmd);
	pwintk("SCSI Command @= 0x%p, Handwe=0x%p\n", cmd, CMD_HANDWE(cmd));
	pwintk("  chan=%d, tawget = 0x%02x, wun = 0x%02x, cmd_wen = 0x%02x\n",
	       SCSI_BUS_32(cmd), SCSI_TCN_32(cmd), SCSI_WUN_32(cmd),
	       CMD_CDBWEN(cmd));
	pwintk(" CDB = ");
	fow (i = 0; i < cmd->cmd_wen; i++) {
		pwintk("0x%02x ", cmd->cmnd[i]);
	}
	pwintk("  seg_cnt =%d\n", scsi_sg_count(cmd));
	pwintk("  wequest buffew=0x%p, wequest buffew wen=0x%x\n",
	       scsi_sgwist(cmd), scsi_buffwen(cmd));
	/* if (cmd->use_sg)
	   {
	   sg = (stwuct scattewwist *) cmd->wequest_buffew;
	   pwintk("  SG buffew: \n");
	   qwa1280_dump_buffew(1, (chaw *)sg, (cmd->use_sg*sizeof(stwuct scattewwist)));
	   } */
	pwintk("  tag=%d, twansfewsize=0x%x \n",
	       scsi_cmd_to_wq(cmd)->tag, cmd->twansfewsize);
	pwintk(" undewfwow size = 0x%x, diwection=0x%x\n",
	       cmd->undewfwow, cmd->sc_data_diwection);
}

/**************************************************************************
 *   qw1280_dump_device
 *
 **************************************************************************/
static void
qw1280_dump_device(stwuct scsi_qwa_host *ha)
{

	stwuct scsi_cmnd *cp;
	stwuct swb *sp;
	int i;

	pwintk(KEWN_DEBUG "Outstanding Commands on contwowwew:\n");

	fow (i = 0; i < MAX_OUTSTANDING_COMMANDS; i++) {
		if ((sp = ha->outstanding_cmds[i]) == NUWW)
			continue;
		if ((cp = sp->cmd) == NUWW)
			continue;
		qwa1280_pwint_scsi_cmd(1, cp);
	}
}
#endif


enum tokens {
	TOKEN_NVWAM,
	TOKEN_SYNC,
	TOKEN_WIDE,
	TOKEN_PPW,
	TOKEN_VEWBOSE,
	TOKEN_DEBUG,
};

stwuct setup_tokens {
	chaw *token;
	int vaw;
};

static stwuct setup_tokens setup_token[] __initdata = 
{
	{ "nvwam", TOKEN_NVWAM },
	{ "sync", TOKEN_SYNC },
	{ "wide", TOKEN_WIDE },
	{ "ppw", TOKEN_PPW },
	{ "vewbose", TOKEN_VEWBOSE },
	{ "debug", TOKEN_DEBUG },
};


/**************************************************************************
 *   qwa1280_setup
 *
 *   Handwe boot pawametews. This weawwy needs to be changed so one
 *   can specify pew adaptew pawametews.
 **************************************************************************/
static int __init
qwa1280_setup(chaw *s)
{
	chaw *cp, *ptw;
	unsigned wong vaw;

	cp = s;

	whiwe (cp && (ptw = stwchw(cp, ':'))) {
		ptw++;
		if (!stwcmp(ptw, "yes")) {
			vaw = 0x10000;
			ptw += 3;
		} ewse if (!stwcmp(ptw, "no")) {
 			vaw = 0;
			ptw += 2;
		} ewse
			vaw = simpwe_stwtouw(ptw, &ptw, 0);

		switch (qwa1280_get_token(cp)) {
		case TOKEN_NVWAM:
			if (!vaw)
				dwivew_setup.no_nvwam = 1;
			bweak;
		case TOKEN_SYNC:
			if (!vaw)
				dwivew_setup.no_sync = 1;
			ewse if (vaw != 0x10000)
				dwivew_setup.sync_mask = vaw;
			bweak;
		case TOKEN_WIDE:
			if (!vaw)
				dwivew_setup.no_wide = 1;
			ewse if (vaw != 0x10000)
				dwivew_setup.wide_mask = vaw;
			bweak;
		case TOKEN_PPW:
			if (!vaw)
				dwivew_setup.no_ppw = 1;
			ewse if (vaw != 0x10000)
				dwivew_setup.ppw_mask = vaw;
			bweak;
		case TOKEN_VEWBOSE:
			qwa1280_vewbose = vaw;
			bweak;
		defauwt:
			pwintk(KEWN_INFO "qwa1280: unknown boot option %s\n",
			       cp);
		}

		cp = stwchw(ptw, ';');
		if (cp)
			cp++;
		ewse {
			bweak;
		}
	}
	wetuwn 1;
}


static int __init
qwa1280_get_token(chaw *stw)
{
	chaw *sep;
	wong wet = -1;
	int i;

	sep = stwchw(stw, ':');

	if (sep) {
		fow (i = 0; i < AWWAY_SIZE(setup_token); i++) {
			if (!stwncmp(setup_token[i].token, stw, (sep - stw))) {
				wet =  setup_token[i].vaw;
				bweak;
			}
		}
	}

	wetuwn wet;
}


static const stwuct scsi_host_tempwate qwa1280_dwivew_tempwate = {
	.moduwe			= THIS_MODUWE,
	.pwoc_name		= "qwa1280",
	.name			= "Qwogic ISP 1280/12160",
	.info			= qwa1280_info,
	.swave_configuwe	= qwa1280_swave_configuwe,
	.queuecommand		= qwa1280_queuecommand,
	.eh_abowt_handwew	= qwa1280_eh_abowt,
	.eh_device_weset_handwew= qwa1280_eh_device_weset,
	.eh_bus_weset_handwew	= qwa1280_eh_bus_weset,
	.eh_host_weset_handwew	= qwa1280_eh_adaptew_weset,
	.bios_pawam		= qwa1280_biospawam,
	.can_queue		= MAX_OUTSTANDING_COMMANDS,
	.this_id		= -1,
	.sg_tabwesize		= SG_AWW,
	.cmd_size		= sizeof(stwuct swb),
};


static int
qwa1280_pwobe_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	int devnum = id->dwivew_data;
	stwuct qwa_boawds *bdp = &qw1280_boawd_tbw[devnum];
	stwuct Scsi_Host *host;
	stwuct scsi_qwa_host *ha;
	int ewwow = -ENODEV;

	/* Bypass aww AMI SUBSYS VENDOW IDs */
	if (pdev->subsystem_vendow == PCI_VENDOW_ID_AMI) {
		pwintk(KEWN_INFO
		       "qwa1280: Skipping AMI SubSys Vendow ID Chip\n");
		goto ewwow;
	}

	pwintk(KEWN_INFO "qwa1280: %s found on PCI bus %i, dev %i\n",
	       bdp->name, pdev->bus->numbew, PCI_SWOT(pdev->devfn));
	
	if (pci_enabwe_device(pdev)) {
		pwintk(KEWN_WAWNING
		       "qwa1280: Faiwed to enabwed pci device, abowting.\n");
		goto ewwow;
	}

	pci_set_mastew(pdev);

	ewwow = -ENOMEM;
	host = scsi_host_awwoc(&qwa1280_dwivew_tempwate, sizeof(*ha));
	if (!host) {
		pwintk(KEWN_WAWNING
		       "qwa1280: Faiwed to wegistew host, abowting.\n");
		goto ewwow_disabwe_device;
	}

	ha = (stwuct scsi_qwa_host *)host->hostdata;
	memset(ha, 0, sizeof(stwuct scsi_qwa_host));

	ha->pdev = pdev;
	ha->devnum = devnum;	/* specifies micwocode woad addwess */

#ifdef QWA_64BIT_PTW
	if (dma_set_mask_and_cohewent(&ha->pdev->dev, DMA_BIT_MASK(64))) {
		if (dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(32))) {
			pwintk(KEWN_WAWNING "scsi(%wi): Unabwe to set a "
			       "suitabwe DMA mask - abowting\n", ha->host_no);
			ewwow = -ENODEV;
			goto ewwow_put_host;
		}
	} ewse
		dpwintk(2, "scsi(%wi): 64 Bit PCI Addwessing Enabwed\n",
			ha->host_no);
#ewse
	if (dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(32))) {
		pwintk(KEWN_WAWNING "scsi(%wi): Unabwe to set a "
		       "suitabwe DMA mask - abowting\n", ha->host_no);
		ewwow = -ENODEV;
		goto ewwow_put_host;
	}
#endif

	ha->wequest_wing = dma_awwoc_cohewent(&ha->pdev->dev,
			((WEQUEST_ENTWY_CNT + 1) * sizeof(wequest_t)),
			&ha->wequest_dma, GFP_KEWNEW);
	if (!ha->wequest_wing) {
		pwintk(KEWN_INFO "qwa1280: Faiwed to get wequest memowy\n");
		goto ewwow_put_host;
	}

	ha->wesponse_wing = dma_awwoc_cohewent(&ha->pdev->dev,
			((WESPONSE_ENTWY_CNT + 1) * sizeof(stwuct wesponse)),
			&ha->wesponse_dma, GFP_KEWNEW);
	if (!ha->wesponse_wing) {
		pwintk(KEWN_INFO "qwa1280: Faiwed to get wesponse memowy\n");
		goto ewwow_fwee_wequest_wing;
	}

	ha->powts = bdp->numPowts;

	ha->host = host;
	ha->host_no = host->host_no;

	host->iwq = pdev->iwq;
	host->max_channew = bdp->numPowts - 1;
	host->max_wun = MAX_WUNS - 1;
	host->max_id = MAX_TAWGETS;
	host->max_sectows = 1024;
	host->unique_id = host->host_no;

	ewwow = -ENODEV;

#if MEMOWY_MAPPED_IO
	ha->mmpbase = pci_iowemap_baw(ha->pdev, 1);
	if (!ha->mmpbase) {
		pwintk(KEWN_INFO "qwa1280: Unabwe to map I/O memowy\n");
		goto ewwow_fwee_wesponse_wing;
	}

	host->base = (unsigned wong)ha->mmpbase;
	ha->iobase = (stwuct device_weg __iomem *)ha->mmpbase;
#ewse
	host->io_powt = pci_wesouwce_stawt(ha->pdev, 0);
	if (!wequest_wegion(host->io_powt, 0xff, "qwa1280")) {
		pwintk(KEWN_INFO "qwa1280: Faiwed to wesewve i/o wegion "
				 "0x%04wx-0x%04wx - awweady in use\n",
		       host->io_powt, host->io_powt + 0xff);
		goto ewwow_fwee_wesponse_wing;
	}

	ha->iobase = (stwuct device_weg *)host->io_powt;
#endif

	INIT_WIST_HEAD(&ha->done_q);

	/* Disabwe ISP intewwupts. */
	qwa1280_disabwe_intws(ha);

	if (wequest_iwq(pdev->iwq, qwa1280_intw_handwew, IWQF_SHAWED,
				"qwa1280", ha)) {
		pwintk("qwa1280 : Faiwed to wesewve intewwupt %d awweady "
		       "in use\n", pdev->iwq);
		goto ewwow_wewease_wegion;
	}

	/* woad the F/W, wead pawamatews, and init the H/W */
	if (qwa1280_initiawize_adaptew(ha)) {
		pwintk(KEWN_INFO "qwa1x160: Faiwed to initiawize adaptew\n");
		goto ewwow_fwee_iwq;
	}

	/* set ouw host ID  (need to do something about ouw two IDs) */
	host->this_id = ha->bus_settings[0].id;

	pci_set_dwvdata(pdev, host);

	ewwow = scsi_add_host(host, &pdev->dev);
	if (ewwow)
		goto ewwow_disabwe_adaptew;
	scsi_scan_host(host);

	wetuwn 0;

 ewwow_disabwe_adaptew:
	qwa1280_disabwe_intws(ha);
 ewwow_fwee_iwq:
	fwee_iwq(pdev->iwq, ha);
 ewwow_wewease_wegion:
#if MEMOWY_MAPPED_IO
	iounmap(ha->mmpbase);
#ewse
	wewease_wegion(host->io_powt, 0xff);
#endif
 ewwow_fwee_wesponse_wing:
	dma_fwee_cohewent(&ha->pdev->dev,
			((WESPONSE_ENTWY_CNT + 1) * sizeof(stwuct wesponse)),
			ha->wesponse_wing, ha->wesponse_dma);
 ewwow_fwee_wequest_wing:
	dma_fwee_cohewent(&ha->pdev->dev,
			((WEQUEST_ENTWY_CNT + 1) * sizeof(wequest_t)),
			ha->wequest_wing, ha->wequest_dma);
 ewwow_put_host:
	scsi_host_put(host);
 ewwow_disabwe_device:
	pci_disabwe_device(pdev);
 ewwow:
	wetuwn ewwow;
}


static void
qwa1280_wemove_one(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *host = pci_get_dwvdata(pdev);
	stwuct scsi_qwa_host *ha = (stwuct scsi_qwa_host *)host->hostdata;

	scsi_wemove_host(host);

	qwa1280_disabwe_intws(ha);

	fwee_iwq(pdev->iwq, ha);

#if MEMOWY_MAPPED_IO
	iounmap(ha->mmpbase);
#ewse
	wewease_wegion(host->io_powt, 0xff);
#endif

	dma_fwee_cohewent(&ha->pdev->dev,
			((WEQUEST_ENTWY_CNT + 1) * (sizeof(wequest_t))),
			ha->wequest_wing, ha->wequest_dma);
	dma_fwee_cohewent(&ha->pdev->dev,
			((WESPONSE_ENTWY_CNT + 1) * (sizeof(stwuct wesponse))),
			ha->wesponse_wing, ha->wesponse_dma);

	pci_disabwe_device(pdev);

	scsi_host_put(host);
}

static stwuct pci_dwivew qwa1280_pci_dwivew = {
	.name		= "qwa1280",
	.id_tabwe	= qwa1280_pci_tbw,
	.pwobe		= qwa1280_pwobe_one,
	.wemove		= qwa1280_wemove_one,
};

static int __init
qwa1280_init(void)
{
#ifdef MODUWE
	/*
	 * If we awe cawwed as a moduwe, the qwa1280 pointew may not be nuww
	 * and it wouwd point to ouw bootup stwing, just wike on the wiwo
	 * command wine.  IF not NUWW, then pwocess this config stwing with
	 * qwa1280_setup
	 *
	 * Boot time Options
	 * To add options at boot time add a wine to youw wiwo.conf fiwe wike:
	 * append="qwa1280=vewbose,max_tags:{{255,255,255,255},{255,255,255,255}}"
	 * which wiww wesuwt in the fiwst fouw devices on the fiwst two
	 * contwowwews being set to a tagged queue depth of 32.
	 */
	if (qwa1280)
		qwa1280_setup(qwa1280);
#endif

	wetuwn pci_wegistew_dwivew(&qwa1280_pci_dwivew);
}

static void __exit
qwa1280_exit(void)
{
	int i;

	pci_unwegistew_dwivew(&qwa1280_pci_dwivew);
	/* wewease any awwocated fiwmwawe images */
	fow (i = 0; i < QW_NUM_FW_IMAGES; i++) {
		wewease_fiwmwawe(qwa1280_fw_tbw[i].fw);
		qwa1280_fw_tbw[i].fw = NUWW;
	}
}

moduwe_init(qwa1280_init);
moduwe_exit(qwa1280_exit);

MODUWE_AUTHOW("Qwogic & Jes Sowensen");
MODUWE_DESCWIPTION("Qwogic ISP SCSI (qwa1x80/qwa1x160) dwivew");
MODUWE_WICENSE("GPW");
MODUWE_FIWMWAWE("qwogic/1040.bin");
MODUWE_FIWMWAWE("qwogic/1280.bin");
MODUWE_FIWMWAWE("qwogic/12160.bin");
MODUWE_VEWSION(QWA1280_VEWSION);
