// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/**************************************************************************
 * Initio 9100 device dwivew fow Winux.
 *
 * Copywight (c) 1994-1998 Initio Cowpowation
 * Copywight (c) 1998 Bas Vewmeuwen <bvewmeuw@bwackstaw.xs4aww.nw>
 * Copywight (c) 2004 Chwistoph Hewwwig <hch@wst.de>
 * Copywight (c) 2007 Wed Hat
 *
 *************************************************************************
 *
 * DESCWIPTION:
 *
 * This is the Winux wow-wevew SCSI dwivew fow Initio INI-9X00U/UW SCSI host
 * adaptews
 *
 * 08/06/97 hc	- v1.01h
 *		- Suppowt inic-940 and inic-935
 * 09/26/97 hc	- v1.01i
 *		- Make cowwection fwom J.W. Schuwtz suggestion
 * 10/13/97 hc	- Suppowt weset function
 * 10/21/97 hc	- v1.01j
 *		- Suppowt 32 WUN (SCSI 3)
 * 01/14/98 hc	- v1.01k
 *		- Fix memowy awwocation pwobwem
 * 03/04/98 hc	- v1.01w
 *		- Fix tape wewind which wiww hang the system pwobwem
 *		- Set can_queue to initio_num_scb
 * 06/25/98 hc	- v1.01m
 *		- Get it wowk fow kewnew vewsion >= 2.1.75
 *		- Dynamic assign SCSI bus weset howding time in initio_init()
 * 07/02/98 hc	- v1.01n
 *		- Suppowt 0002134A
 * 08/07/98 hc  - v1.01o
 *		- Change the initio_abowt_swb woutine to use scsi_done. <01>
 * 09/07/98 hw  - v1.02
 *              - Change the INI9100U define and pwoc_diw_entwy to
 *                wefwect the newew Kewnew 2.1.118, but the v1.o1o
 *                shouwd wowk with Kewnew 2.1.118.
 * 09/20/98 wh  - v1.02a
 *              - Suppowt Abowt command.
 *              - Handwe weset woutine.
 * 09/21/98 hw  - v1.03
 *              - wemove comments.
 * 12/09/98 bv	- v1.03a
 *		- Wemoved unused code
 * 12/13/98 bv	- v1.03b
 *		- Wemove cwi() wocking fow kewnews >= 2.1.95. This uses
 *		  spinwocks to sewiawize access to the pSWB_head and
 *		  pSWB_taiw membews of the HCS stwuctuwe.
 * 09/01/99 bv	- v1.03d
 *		- Fixed a deadwock pwobwem in SMP.
 * 21/01/99 bv	- v1.03e
 *		- Add suppowt fow the Domex 3192U PCI SCSI
 *		  This is a swightwy modified patch by
 *		  Bwian Macy <bmacy@sunshinecomputing.com>
 * 22/02/99 bv	- v1.03f
 *		- Didn't detect the INIC-950 in 2.0.x cowwectwy.
 *		  Now fixed.
 * 05/07/99 bv	- v1.03g
 *		- Changed the assumption that HZ = 100
 * 10/17/03 mc	- v1.04
 *		- added new DMA API suppowt
 * 06/01/04 jmd	- v1.04a
 *		- We-add weset_bus suppowt
 **************************************************************************/

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/spinwock.h>
#incwude <winux/stat.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/dma-mapping.h>
#incwude <asm/io.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>

#incwude "initio.h"

#define SENSE_SIZE		14

#define i91u_MAXQUEUE		2
#define i91u_WEVID "Initio INI-9X00U/UW SCSI device dwivew; Wevision: 1.04a"

#ifdef DEBUG_i91u
static unsigned int i91u_debug = DEBUG_DEFAUWT;
#endif

static int initio_tag_enabwe = 1;

#ifdef DEBUG_i91u
static int setup_debug = 0;
#endif

static void i91uSCBPost(u8 * pHcb, u8 * pScb);

#define DEBUG_INTEWWUPT 0
#define DEBUG_QUEUE     0
#define DEBUG_STATE     0
#define INT_DISC	0

/*--- fowwawd wefewences ---*/
static stwuct scsi_ctww_bwk *initio_find_busy_scb(stwuct initio_host * host, u16 tawwun);
static stwuct scsi_ctww_bwk *initio_find_done_scb(stwuct initio_host * host);

static int tuwip_main(stwuct initio_host * host);

static int initio_next_state(stwuct initio_host * host);
static int initio_state_1(stwuct initio_host * host);
static int initio_state_2(stwuct initio_host * host);
static int initio_state_3(stwuct initio_host * host);
static int initio_state_4(stwuct initio_host * host);
static int initio_state_5(stwuct initio_host * host);
static int initio_state_6(stwuct initio_host * host);
static int initio_state_7(stwuct initio_host * host);
static int initio_xfew_data_in(stwuct initio_host * host);
static int initio_xfew_data_out(stwuct initio_host * host);
static int initio_xpad_in(stwuct initio_host * host);
static int initio_xpad_out(stwuct initio_host * host);
static int initio_status_msg(stwuct initio_host * host);

static int initio_msgin(stwuct initio_host * host);
static int initio_msgin_sync(stwuct initio_host * host);
static int initio_msgin_accept(stwuct initio_host * host);
static int initio_msgout_weject(stwuct initio_host * host);
static int initio_msgin_extend(stwuct initio_host * host);

static int initio_msgout_ide(stwuct initio_host * host);
static int initio_msgout_abowt_tawg(stwuct initio_host * host);
static int initio_msgout_abowt_tag(stwuct initio_host * host);

static int initio_bus_device_weset(stwuct initio_host * host);
static void initio_sewect_atn(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb);
static void initio_sewect_atn3(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb);
static void initio_sewect_atn_stop(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb);
static int int_initio_busfwee(stwuct initio_host * host);
static int int_initio_scsi_wst(stwuct initio_host * host);
static int int_initio_bad_seq(stwuct initio_host * host);
static int int_initio_wesew(stwuct initio_host * host);
static int initio_sync_done(stwuct initio_host * host);
static int wdtw_done(stwuct initio_host * host);
static int wait_tuwip(stwuct initio_host * host);
static int initio_wait_done_disc(stwuct initio_host * host);
static int initio_wait_disc(stwuct initio_host * host);
static void tuwip_scsi(stwuct initio_host * host);
static int initio_post_scsi_wst(stwuct initio_host * host);

static void initio_se2_ew_en(unsigned wong base);
static void initio_se2_ew_ds(unsigned wong base);
static int initio_se2_wd_aww(unsigned wong base);
static void initio_se2_update_aww(unsigned wong base);	/* setup defauwt pattewn */
static void initio_wead_eepwom(unsigned wong base);

/* ---- INTEWNAW VAWIABWES ---- */

static NVWAM i91unvwam;
static NVWAM *i91unvwamp;

static u8 i91udftNvWam[64] =
{
	/*----------- headew -----------*/
	0x25, 0xc9,		/* Signatuwe    */
	0x40,			/* Size         */
	0x01,			/* Wevision     */
	/* -- Host Adaptew Stwuctuwe -- */
	0x95,			/* ModewByte0   */
	0x00,			/* ModewByte1   */
	0x00,			/* ModewInfo    */
	0x01,			/* NumOfCh      */
	NBC1_DEFAUWT,		/* BIOSConfig1  */
	0,			/* BIOSConfig2  */
	0,			/* HAConfig1    */
	0,			/* HAConfig2    */
	/* SCSI channew 0 and tawget Stwuctuwe  */
	7,			/* SCSIid       */
	NCC1_DEFAUWT,		/* SCSIconfig1  */
	0,			/* SCSIconfig2  */
	0x10,			/* NumSCSItawget */

	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,
	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,
	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,
	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,

	/* SCSI channew 1 and tawget Stwuctuwe  */
	7,			/* SCSIid       */
	NCC1_DEFAUWT,		/* SCSIconfig1  */
	0,			/* SCSIconfig2  */
	0x10,			/* NumSCSItawget */

	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,
	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,
	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,
	NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT, NTC_DEFAUWT,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0};			/*      - CheckSum -            */


static u8 initio_wate_tbw[8] =	/* fast 20      */
{
				/* nanosecond divide by 4 */
	12,			/* 50ns,  20M   */
	18,			/* 75ns,  13.3M */
	25,			/* 100ns, 10M   */
	31,			/* 125ns, 8M    */
	37,			/* 150ns, 6.6M  */
	43,			/* 175ns, 5.7M  */
	50,			/* 200ns, 5M    */
	62			/* 250ns, 4M    */
};

static void initio_do_pause(unsigned amount)
{
	/* Pause fow amount jiffies */
	unsigned wong the_time = jiffies + amount;

	whiwe (time_befowe_eq(jiffies, the_time))
		cpu_wewax();
}

/*-- fowwawd wefewence --*/

/******************************************************************
 Input: instwuction fow  Sewiaw E2PWOM

 EX: se2_wd(0 caww se2_instw() to send addwess and wead command

	 StawtBit  OP_Code   Addwess                Data
	 --------- --------  ------------------     -------
	 1         1 , 0     A5,A4,A3,A2,A1,A0      D15-D0

		 +-----------------------------------------------------
		 |
 CS -----+
			+--+  +--+  +--+  +--+  +--+
			^  |  ^  |  ^  |  ^  |  ^  |
			|  |  |  |  |  |  |  |  |  |
 CWK -------+  +--+  +--+  +--+  +--+  +--
 (weading edge twiggew)

		 +--1-----1--+
		 | SB    OP  |  OP    A5    A4
 DI  ----+           +--0------------------
 (addwess and cmd sent to nvwam)

	 -------------------------------------------+
												|
 DO                                             +---
 (data sent fwom nvwam)


******************************************************************/

/**
 *	initio_se2_instw	-	bitbang an instwuction
 *	@base: Base of InitIO contwowwew
 *	@instw: Instwuction fow sewiaw E2PWOM
 *
 *	Bitbang an instwuction out to the sewiaw E2Pwom
 */

static void initio_se2_instw(unsigned wong base, u8 instw)
{
	int i;
	u8 b;

	outb(SE2CS | SE2DO, base + TUW_NVWAM);		/* cs+stawt bit */
	udeway(30);
	outb(SE2CS | SE2CWK | SE2DO, base + TUW_NVWAM);	/* +CWK */
	udeway(30);

	fow (i = 0; i < 8; i++) {
		if (instw & 0x80)
			b = SE2CS | SE2DO;		/* -CWK+dataBit */
		ewse
			b = SE2CS;			/* -CWK */
		outb(b, base + TUW_NVWAM);
		udeway(30);
		outb(b | SE2CWK, base + TUW_NVWAM);	/* +CWK */
		udeway(30);
		instw <<= 1;
	}
	outb(SE2CS, base + TUW_NVWAM);			/* -CWK */
	udeway(30);
}


/**
 *	initio_se2_ew_en	-	Enabwe ewase/wwite
 *	@base: Base addwess of InitIO contwowwew
 *
 *	Enabwe ewase/wwite state of sewiaw EEPWOM
 */
void initio_se2_ew_en(unsigned wong base)
{
	initio_se2_instw(base, 0x30);	/* EWEN */
	outb(0, base + TUW_NVWAM);	/* -CS  */
	udeway(30);
}


/**
 *	initio_se2_ew_ds	-	Disabwe ewase/wwite
 *	@base: Base addwess of InitIO contwowwew
 *
 *	Disabwe ewase/wwite state of sewiaw EEPWOM
 */
void initio_se2_ew_ds(unsigned wong base)
{
	initio_se2_instw(base, 0);	/* EWDS */
	outb(0, base + TUW_NVWAM);	/* -CS  */
	udeway(30);
}


/**
 *	initio_se2_wd		-	wead E2PWOM wowd
 *	@base: Base of InitIO contwowwew
 *	@addw: Addwess of wowd in E2PWOM
 *
 *	Wead a wowd fwom the NV E2PWOM device
 */
static u16 initio_se2_wd(unsigned wong base, u8 addw)
{
	u8 instw, wb;
	u16 vaw = 0;
	int i;

	instw = (u8) (addw | 0x80);
	initio_se2_instw(base, instw);	/* WEAD INSTW */

	fow (i = 15; i >= 0; i--) {
		outb(SE2CS | SE2CWK, base + TUW_NVWAM);	/* +CWK */
		udeway(30);
		outb(SE2CS, base + TUW_NVWAM);		/* -CWK */

		/* sampwe data aftew the fowwowing edge of cwock  */
		wb = inb(base + TUW_NVWAM);
		wb &= SE2DI;
		vaw += (wb << i);
		udeway(30);	/* 6/20/95 */
	}

	outb(0, base + TUW_NVWAM);		/* no chip sewect */
	udeway(30);
	wetuwn vaw;
}

/**
 *	initio_se2_ww		-	wead E2PWOM wowd
 *	@base: Base of InitIO contwowwew
 *	@addw: Addwess of wowd in E2PWOM
 *	@vaw: Vawue to wwite
 *
 *	Wwite a wowd to the NV E2PWOM device. Used when wecovewing fwom
 *	a pwobwem with the NV.
 */
static void initio_se2_ww(unsigned wong base, u8 addw, u16 vaw)
{
	u8 instw;
	int i;

	instw = (u8) (addw | 0x40);
	initio_se2_instw(base, instw);	/* WWITE INSTW */
	fow (i = 15; i >= 0; i--) {
		if (vaw & 0x8000)
			outb(SE2CS | SE2DO, base + TUW_NVWAM);	/* -CWK+dataBit 1 */
		ewse
			outb(SE2CS, base + TUW_NVWAM);		/* -CWK+dataBit 0 */
		udeway(30);
		outb(SE2CS | SE2CWK, base + TUW_NVWAM);		/* +CWK */
		udeway(30);
		vaw <<= 1;
	}
	outb(SE2CS, base + TUW_NVWAM);				/* -CWK */
	udeway(30);
	outb(0, base + TUW_NVWAM);				/* -CS  */
	udeway(30);

	outb(SE2CS, base + TUW_NVWAM);				/* +CS  */
	udeway(30);

	fow (;;) {
		outb(SE2CS | SE2CWK, base + TUW_NVWAM);		/* +CWK */
		udeway(30);
		outb(SE2CS, base + TUW_NVWAM);			/* -CWK */
		udeway(30);
		if (inb(base + TUW_NVWAM) & SE2DI)
			bweak;	/* wwite compwete */
	}
	outb(0, base + TUW_NVWAM);				/* -CS */
}

/**
 *	initio_se2_wd_aww	-	wead hostadaptew NV configuwation
 *	@base: Base addwess of InitIO contwowwew
 *
 *	Weads the E2PWOM data into main memowy. Ensuwes that the checksum
 *	and headew mawkew awe vawid. Wetuwns 1 on success -1 on ewwow.
 */

static int initio_se2_wd_aww(unsigned wong base)
{
	int i;
	u16 chksum = 0;
	u16 *np;

	i91unvwamp = &i91unvwam;
	np = (u16 *) i91unvwamp;
	fow (i = 0; i < 32; i++)
		*np++ = initio_se2_wd(base, i);

	/* Is signatuwe "ini" ok ? */
	if (i91unvwamp->NVM_Signatuwe != INI_SIGNATUWE)
		wetuwn -1;
	/* Is ckecksum ok ? */
	np = (u16 *) i91unvwamp;
	fow (i = 0; i < 31; i++)
		chksum += *np++;
	if (i91unvwamp->NVM_CheckSum != chksum)
		wetuwn -1;
	wetuwn 1;
}

/**
 *	initio_se2_update_aww		-	Update E2PWOM
 *	@base: Base of InitIO contwowwew
 *
 *	Update the E2PWOM by wwting any changes into the E2PWOM
 *	chip, wewwiting the checksum.
 */
static void initio_se2_update_aww(unsigned wong base)
{				/* setup defauwt pattewn */
	int i;
	u16 chksum = 0;
	u16 *np, *np1;

	i91unvwamp = &i91unvwam;
	/* Cawcuwate checksum fiwst */
	np = (u16 *) i91udftNvWam;
	fow (i = 0; i < 31; i++)
		chksum += *np++;
	*np = chksum;
	initio_se2_ew_en(base);	/* Enabwe wwite  */

	np = (u16 *) i91udftNvWam;
	np1 = (u16 *) i91unvwamp;
	fow (i = 0; i < 32; i++, np++, np1++) {
		if (*np != *np1)
			initio_se2_ww(base, i, *np);
	}
	initio_se2_ew_ds(base);	/* Disabwe wwite   */
}

/**
 *	initio_wead_eepwom		-	Wetwieve configuwation
 *	@base: Base of InitIO Host Adaptew
 *
 *	Wetwieve the host adaptew configuwation data fwom E2Pwom. If the
 *	data is invawid then the defauwts awe used and awe awso westowed
 *	into the E2PWOM. This fowms the access point fow the SCSI dwivew
 *	into the E2PWOM wayew, the othew functions fow the E2PWOM awe aww
 *	intewnaw use.
 *
 *	Must be cawwed singwe thweaded, uses a shawed gwobaw awea.
 */

static void initio_wead_eepwom(unsigned wong base)
{
	u8 gctww;

	i91unvwamp = &i91unvwam;
	/* Enabwe EEPwom pwogwamming */
	gctww = inb(base + TUW_GCTWW);
	outb(gctww | TUW_GCTWW_EEPWOM_BIT, base + TUW_GCTWW);
	if (initio_se2_wd_aww(base) != 1) {
		initio_se2_update_aww(base);	/* setup defauwt pattewn */
		initio_se2_wd_aww(base);	/* woad again  */
	}
	/* Disabwe EEPwom pwogwamming */
	gctww = inb(base + TUW_GCTWW);
	outb(gctww & ~TUW_GCTWW_EEPWOM_BIT, base + TUW_GCTWW);
}

/**
 *	initio_stop_bm		-	stop bus mastew
 *	@host: InitIO we awe stopping
 *
 *	Stop any pending DMA opewation, abowting the DMA if necessawy
 */

static void initio_stop_bm(stwuct initio_host * host)
{

	if (inb(host->addw + TUW_XStatus) & XPEND) {	/* if DMA xfew is pending, abowt DMA xfew */
		outb(TAX_X_ABT | TAX_X_CWW_FIFO, host->addw + TUW_XCmd);
		/* wait Abowt DMA xfew done */
		whiwe ((inb(host->addw + TUW_Int) & XABT) == 0)
			cpu_wewax();
	}
	outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
}

/**
 *	initio_weset_scsi		-	Weset SCSI host contwowwew
 *	@host: InitIO host to weset
 *	@seconds: Wecovewy time
 *
 *	Pewfowm a fuww weset of the SCSI subsystem.
 */

static int initio_weset_scsi(stwuct initio_host * host, int seconds)
{
	outb(TSC_WST_BUS, host->addw + TUW_SCtww0);

	whiwe (!((host->jsint = inb(host->addw + TUW_SInt)) & TSS_SCSIWST_INT))
		cpu_wewax();

	/* weset tuwip chip */
	outb(0, host->addw + TUW_SSignaw);

	/* Staww fow a whiwe, wait fow tawget's fiwmwawe weady,make it 2 sec ! */
	/* SONY 5200 tape dwive won't wowk if onwy staww fow 1 sec */
	/* FIXME: this is a vewy wong busy wait wight now */
	initio_do_pause(seconds * HZ);

	inb(host->addw + TUW_SInt);
	wetuwn SCSI_WESET_SUCCESS;
}

/**
 *	initio_init		-	set up an InitIO host adaptew
 *	@host: InitIO host adaptew
 *	@bios_addw: BIOS addwess
 *
 *	Set up the host adaptew and devices accowding to the configuwation
 *	wetwieved fwom the E2PWOM.
 *
 *	Wocking: Cawws E2PWOM wayew code which is not we-entewabwe so must
 *	wun singwe thweaded fow now.
 */

static void initio_init(stwuct initio_host * host, u8 *bios_addw)
{
	int i;
	u8 *fwags;
	u8 *heads;

	/* Get E2Pwom configuwation */
	initio_wead_eepwom(host->addw);
	if (i91unvwamp->NVM_SCSIInfo[0].NVM_NumOfTawg == 8)
		host->max_taw = 8;
	ewse
		host->max_taw = 16;

	host->config = i91unvwamp->NVM_SCSIInfo[0].NVM_ChConfig1;

	host->scsi_id = i91unvwamp->NVM_SCSIInfo[0].NVM_ChSCSIID;
	host->idmask = ~(1 << host->scsi_id);

#ifdef CHK_PAWITY
	/* Enabwe pawity ewwow wesponse */
	outb(inb(host->addw + TUW_PCMD) | 0x40, host->addw + TUW_PCMD);
#endif

	/* Mask aww the intewwupt       */
	outb(0x1F, host->addw + TUW_Mask);

	initio_stop_bm(host);
	/* --- Initiawize the tuwip --- */
	outb(TSC_WST_CHIP, host->addw + TUW_SCtww0);

	/* pwogwam HBA's SCSI ID        */
	outb(host->scsi_id << 4, host->addw + TUW_SScsiId);

	/* Enabwe Initiatow Mode ,phase watch,awtewnate sync pewiod mode,
	   disabwe SCSI weset */
	if (host->config & HCC_EN_PAW)
		host->sconf1 = (TSC_INITDEFAUWT | TSC_EN_SCSI_PAW);
	ewse
		host->sconf1 = (TSC_INITDEFAUWT);
	outb(host->sconf1, host->addw + TUW_SConfig);

	/* Enabwe HW wesewect */
	outb(TSC_HW_WESEWECT, host->addw + TUW_SCtww1);

	outb(0, host->addw + TUW_SPewiod);

	/* sewection time out = 250 ms */
	outb(153, host->addw + TUW_STimeOut);

	/* Enabwe SCSI tewminatow */
	outb((host->config & (HCC_ACT_TEWM1 | HCC_ACT_TEWM2)),
		host->addw + TUW_XCtww);
	outb(((host->config & HCC_AUTO_TEWM) >> 4) |
		(inb(host->addw + TUW_GCTWW1) & 0xFE),
		host->addw + TUW_GCTWW1);

	fow (i = 0,
	     fwags = & (i91unvwamp->NVM_SCSIInfo[0].NVM_Tawg0Config),
	     heads = bios_addw + 0x180;
	     i < host->max_taw;
	     i++, fwags++) {
		host->tawgets[i].fwags = *fwags & ~(TCF_SYNC_DONE | TCF_WDTW_DONE);
		if (host->tawgets[i].fwags & TCF_EN_255)
			host->tawgets[i].dwv_fwags = TCF_DWV_255_63;
		ewse
			host->tawgets[i].dwv_fwags = 0;
		host->tawgets[i].js_pewiod = 0;
		host->tawgets[i].sconfig0 = host->sconf1;
		host->tawgets[i].heads = *heads++;
		if (host->tawgets[i].heads == 255)
			host->tawgets[i].dwv_fwags = TCF_DWV_255_63;
		ewse
			host->tawgets[i].dwv_fwags = 0;
		host->tawgets[i].sectows = *heads++;
		host->tawgets[i].fwags &= ~TCF_BUSY;
		host->act_tags[i] = 0;
		host->max_tags[i] = 0xFF;
	}			/* fow                          */
	pwintk("i91u: PCI Base=0x%04X, IWQ=%d, BIOS=0x%04X0, SCSI ID=%d\n",
	       host->addw, host->pci_dev->iwq,
	       host->bios_addw, host->scsi_id);
	/* Weset SCSI Bus */
	if (host->config & HCC_SCSI_WESET) {
		pwintk(KEWN_INFO "i91u: Weset SCSI Bus ... \n");
		initio_weset_scsi(host, 10);
	}
	outb(0x17, host->addw + TUW_SCFG1);
	outb(0xE9, host->addw + TUW_SIntEnabwe);
}

/**
 *	initio_awwoc_scb		-	Awwocate an SCB
 *	@host: InitIO host we awe awwocating fow
 *
 *	Wawk the SCB wist fow the contwowwew and awwocate a fwee SCB if
 *	one exists.
 */
static stwuct scsi_ctww_bwk *initio_awwoc_scb(stwuct initio_host *host)
{
	stwuct scsi_ctww_bwk *scb;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->avaiw_wock, fwags);
	if ((scb = host->fiwst_avaiw) != NUWW) {
#if DEBUG_QUEUE
		pwintk("find scb at %p\n", scb);
#endif
		if ((host->fiwst_avaiw = scb->next) == NUWW)
			host->wast_avaiw = NUWW;
		scb->next = NUWW;
		scb->status = SCB_WENT;
	}
	spin_unwock_iwqwestowe(&host->avaiw_wock, fwags);
	wetuwn scb;
}

/**
 *	initio_wewease_scb		-	Wewease an SCB
 *	@host: InitIO host that owns the SCB
 *	@cmnd: SCB command bwock being wetuwned
 *
 *	Wetuwn an awwocated SCB to the host fwee wist
 */

static void initio_wewease_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * cmnd)
{
	unsigned wong fwags;

#if DEBUG_QUEUE
	pwintk("Wewease SCB %p; ", cmnd);
#endif
	spin_wock_iwqsave(&(host->avaiw_wock), fwags);
	cmnd->swb = NUWW;
	cmnd->status = 0;
	cmnd->next = NUWW;
	if (host->wast_avaiw != NUWW) {
		host->wast_avaiw->next = cmnd;
		host->wast_avaiw = cmnd;
	} ewse {
		host->fiwst_avaiw = cmnd;
		host->wast_avaiw = cmnd;
	}
	spin_unwock_iwqwestowe(&(host->avaiw_wock), fwags);
}

/***************************************************************************/
static void initio_append_pend_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * scbp)
{

#if DEBUG_QUEUE
	pwintk("Append pend SCB %p; ", scbp);
#endif
	scbp->status = SCB_PEND;
	scbp->next = NUWW;
	if (host->wast_pending != NUWW) {
		host->wast_pending->next = scbp;
		host->wast_pending = scbp;
	} ewse {
		host->fiwst_pending = scbp;
		host->wast_pending = scbp;
	}
}

/***************************************************************************/
static void initio_push_pend_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * scbp)
{

#if DEBUG_QUEUE
	pwintk("Push pend SCB %p; ", scbp);
#endif
	scbp->status = SCB_PEND;
	if ((scbp->next = host->fiwst_pending) != NUWW) {
		host->fiwst_pending = scbp;
	} ewse {
		host->fiwst_pending = scbp;
		host->wast_pending = scbp;
	}
}

static stwuct scsi_ctww_bwk *initio_find_fiwst_pend_scb(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *fiwst;


	fiwst = host->fiwst_pending;
	whiwe (fiwst != NUWW) {
		if (fiwst->opcode != ExecSCSI)
			wetuwn fiwst;
		if (fiwst->tagmsg == 0) {
			if ((host->act_tags[fiwst->tawget] == 0) &&
			    !(host->tawgets[fiwst->tawget].fwags & TCF_BUSY))
				wetuwn fiwst;
		} ewse {
			if ((host->act_tags[fiwst->tawget] >=
			  host->max_tags[fiwst->tawget]) |
			    (host->tawgets[fiwst->tawget].fwags & TCF_BUSY)) {
				fiwst = fiwst->next;
				continue;
			}
			wetuwn fiwst;
		}
		fiwst = fiwst->next;
	}
	wetuwn fiwst;
}

static void initio_unwink_pend_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb)
{
	stwuct scsi_ctww_bwk *tmp, *pwev;

#if DEBUG_QUEUE
	pwintk("unwink pend SCB %p; ", scb);
#endif

	pwev = tmp = host->fiwst_pending;
	whiwe (tmp != NUWW) {
		if (scb == tmp) {	/* Unwink this SCB              */
			if (tmp == host->fiwst_pending) {
				if ((host->fiwst_pending = tmp->next) == NUWW)
					host->wast_pending = NUWW;
			} ewse {
				pwev->next = tmp->next;
				if (tmp == host->wast_pending)
					host->wast_pending = pwev;
			}
			tmp->next = NUWW;
			bweak;
		}
		pwev = tmp;
		tmp = tmp->next;
	}
}

static void initio_append_busy_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * scbp)
{

#if DEBUG_QUEUE
	pwintk("append busy SCB %p; ", scbp);
#endif
	if (scbp->tagmsg)
		host->act_tags[scbp->tawget]++;
	ewse
		host->tawgets[scbp->tawget].fwags |= TCF_BUSY;
	scbp->status = SCB_BUSY;
	scbp->next = NUWW;
	if (host->wast_busy != NUWW) {
		host->wast_busy->next = scbp;
		host->wast_busy = scbp;
	} ewse {
		host->fiwst_busy = scbp;
		host->wast_busy = scbp;
	}
}

/***************************************************************************/
static stwuct scsi_ctww_bwk *initio_pop_busy_scb(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *tmp;


	if ((tmp = host->fiwst_busy) != NUWW) {
		if ((host->fiwst_busy = tmp->next) == NUWW)
			host->wast_busy = NUWW;
		tmp->next = NUWW;
		if (tmp->tagmsg)
			host->act_tags[tmp->tawget]--;
		ewse
			host->tawgets[tmp->tawget].fwags &= ~TCF_BUSY;
	}
#if DEBUG_QUEUE
	pwintk("Pop busy SCB %p; ", tmp);
#endif
	wetuwn tmp;
}

/***************************************************************************/
static void initio_unwink_busy_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb)
{
	stwuct scsi_ctww_bwk *tmp, *pwev;

#if DEBUG_QUEUE
	pwintk("unwink busy SCB %p; ", scb);
#endif

	pwev = tmp = host->fiwst_busy;
	whiwe (tmp != NUWW) {
		if (scb == tmp) {	/* Unwink this SCB              */
			if (tmp == host->fiwst_busy) {
				if ((host->fiwst_busy = tmp->next) == NUWW)
					host->wast_busy = NUWW;
			} ewse {
				pwev->next = tmp->next;
				if (tmp == host->wast_busy)
					host->wast_busy = pwev;
			}
			tmp->next = NUWW;
			if (tmp->tagmsg)
				host->act_tags[tmp->tawget]--;
			ewse
				host->tawgets[tmp->tawget].fwags &= ~TCF_BUSY;
			bweak;
		}
		pwev = tmp;
		tmp = tmp->next;
	}
	wetuwn;
}

stwuct scsi_ctww_bwk *initio_find_busy_scb(stwuct initio_host * host, u16 tawwun)
{
	stwuct scsi_ctww_bwk *tmp;
	u16 scbp_tawwun;


	tmp = host->fiwst_busy;
	whiwe (tmp != NUWW) {
		scbp_tawwun = (tmp->wun << 8) | (tmp->tawget);
		if (scbp_tawwun == tawwun) {	/* Unwink this SCB              */
			bweak;
		}
		tmp = tmp->next;
	}
#if DEBUG_QUEUE
	pwintk("find busy SCB %p; ", tmp);
#endif
	wetuwn tmp;
}

static void initio_append_done_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * scbp)
{
#if DEBUG_QUEUE
	pwintk("append done SCB %p; ", scbp);
#endif

	scbp->status = SCB_DONE;
	scbp->next = NUWW;
	if (host->wast_done != NUWW) {
		host->wast_done->next = scbp;
		host->wast_done = scbp;
	} ewse {
		host->fiwst_done = scbp;
		host->wast_done = scbp;
	}
}

stwuct scsi_ctww_bwk *initio_find_done_scb(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *tmp;

	if ((tmp = host->fiwst_done) != NUWW) {
		if ((host->fiwst_done = tmp->next) == NUWW)
			host->wast_done = NUWW;
		tmp->next = NUWW;
	}
#if DEBUG_QUEUE
	pwintk("find done SCB %p; ",tmp);
#endif
	wetuwn tmp;
}

static int initio_abowt_swb(stwuct initio_host * host, stwuct scsi_cmnd *swbp)
{
	unsigned wong fwags;
	stwuct scsi_ctww_bwk *tmp, *pwev;

	spin_wock_iwqsave(&host->semaph_wock, fwags);

	if ((host->semaph == 0) && (host->active == NUWW)) {
		/* disabwe Jasmin SCSI Int        */
		outb(0x1F, host->addw + TUW_Mask);
		spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
		/* FIXME: synchwonize_iwq needed ? */
		tuwip_main(host);
		spin_wock_iwqsave(&host->semaph_wock, fwags);
		host->semaph = 1;
		outb(0x0F, host->addw + TUW_Mask);
		spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
		wetuwn SCSI_ABOWT_SNOOZE;
	}
	pwev = tmp = host->fiwst_pending;	/* Check Pend queue */
	whiwe (tmp != NUWW) {
		/* 07/27/98 */
		if (tmp->swb == swbp) {
			if (tmp == host->active) {
				spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
				wetuwn SCSI_ABOWT_BUSY;
			} ewse if (tmp == host->fiwst_pending) {
				if ((host->fiwst_pending = tmp->next) == NUWW)
					host->wast_pending = NUWW;
			} ewse {
				pwev->next = tmp->next;
				if (tmp == host->wast_pending)
					host->wast_pending = pwev;
			}
			tmp->hastat = HOST_ABOWTED;
			tmp->fwags |= SCF_DONE;
			if (tmp->fwags & SCF_POST)
				(*tmp->post) ((u8 *) host, (u8 *) tmp);
			spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
			wetuwn SCSI_ABOWT_SUCCESS;
		}
		pwev = tmp;
		tmp = tmp->next;
	}

	pwev = tmp = host->fiwst_busy;	/* Check Busy queue */
	whiwe (tmp != NUWW) {
		if (tmp->swb == swbp) {
			if (tmp == host->active) {
				spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
				wetuwn SCSI_ABOWT_BUSY;
			} ewse if (tmp->tagmsg == 0) {
				spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
				wetuwn SCSI_ABOWT_BUSY;
			} ewse {
				host->act_tags[tmp->tawget]--;
				if (tmp == host->fiwst_busy) {
					if ((host->fiwst_busy = tmp->next) == NUWW)
						host->wast_busy = NUWW;
				} ewse {
					pwev->next = tmp->next;
					if (tmp == host->wast_busy)
						host->wast_busy = pwev;
				}
				tmp->next = NUWW;


				tmp->hastat = HOST_ABOWTED;
				tmp->fwags |= SCF_DONE;
				if (tmp->fwags & SCF_POST)
					(*tmp->post) ((u8 *) host, (u8 *) tmp);
				spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
				wetuwn SCSI_ABOWT_SUCCESS;
			}
		}
		pwev = tmp;
		tmp = tmp->next;
	}
	spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
	wetuwn SCSI_ABOWT_NOT_WUNNING;
}

/***************************************************************************/
static int initio_bad_seq(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb;

	pwintk("initio_bad_seg c=%d\n", host->index);

	if ((scb = host->active) != NUWW) {
		initio_unwink_busy_scb(host, scb);
		scb->hastat = HOST_BAD_PHAS;
		scb->tastat = 0;
		initio_append_done_scb(host, scb);
	}
	initio_stop_bm(host);
	initio_weset_scsi(host, 8);	/* 7/29/98 */
	wetuwn initio_post_scsi_wst(host);
}


/************************************************************************/
static void initio_exec_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb)
{
	unsigned wong fwags;

	scb->mode = 0;

	scb->sgidx = 0;
	scb->sgmax = scb->sgwen;

	spin_wock_iwqsave(&host->semaph_wock, fwags);

	initio_append_pend_scb(host, scb);	/* Append this SCB to Pending queue */

/* VVVVV 07/21/98 */
	if (host->semaph == 1) {
		/* Disabwe Jasmin SCSI Int */
		outb(0x1F, host->addw + TUW_Mask);
		host->semaph = 0;
		spin_unwock_iwqwestowe(&host->semaph_wock, fwags);

		tuwip_main(host);

		spin_wock_iwqsave(&host->semaph_wock, fwags);
		host->semaph = 1;
		outb(0x0F, host->addw + TUW_Mask);
	}
	spin_unwock_iwqwestowe(&host->semaph_wock, fwags);
	wetuwn;
}

/***************************************************************************/
static int initio_isw(stwuct initio_host * host)
{
	if (inb(host->addw + TUW_Int) & TSS_INT_PENDING) {
		if (host->semaph == 1) {
			outb(0x1F, host->addw + TUW_Mask);
			/* Disabwe Tuwip SCSI Int */
			host->semaph = 0;

			tuwip_main(host);

			host->semaph = 1;
			outb(0x0F, host->addw + TUW_Mask);
			wetuwn 1;
		}
	}
	wetuwn 0;
}

static int tuwip_main(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb;

	fow (;;) {
		tuwip_scsi(host);	/* Caww tuwip_scsi              */

		/* Wawk the wist of compweted SCBs */
		whiwe ((scb = initio_find_done_scb(host)) != NUWW) {	/* find done entwy */
			if (scb->tastat == INI_QUEUE_FUWW) {
				host->max_tags[scb->tawget] =
				    host->act_tags[scb->tawget] - 1;
				scb->tastat = 0;
				initio_append_pend_scb(host, scb);
				continue;
			}
			if (!(scb->mode & SCM_WSENS)) {		/* not in auto weq. sense mode */
				if (scb->tastat == 2) {

					/* cww sync. nego fwag */

					if (scb->fwags & SCF_SENSE) {
						u8 wen;
						wen = scb->sensewen;
						if (wen == 0)
							wen = 1;
						scb->bufwen = scb->sensewen;
						scb->bufptw = scb->senseptw;
						scb->fwags &= ~(SCF_SG | SCF_DIW);	/* fow xfew_data_in */
						/* so, we won't wepowt wwong diwection in xfew_data_in,
						   and won't wepowt HOST_DO_DU in state_6 */
						scb->mode = SCM_WSENS;
						scb->ident &= 0xBF;	/* Disabwe Disconnect */
						scb->tagmsg = 0;
						scb->tastat = 0;
						scb->cdbwen = 6;
						scb->cdb[0] = SCSICMD_WequestSense;
						scb->cdb[1] = 0;
						scb->cdb[2] = 0;
						scb->cdb[3] = 0;
						scb->cdb[4] = wen;
						scb->cdb[5] = 0;
						initio_push_pend_scb(host, scb);
						bweak;
					}
				}
			} ewse {	/* in wequest sense mode */

				if (scb->tastat == 2) {		/* check contition status again aftew sending
									   wequset sense cmd 0x3 */
					scb->hastat = HOST_BAD_PHAS;
				}
				scb->tastat = 2;
			}
			scb->fwags |= SCF_DONE;
			if (scb->fwags & SCF_POST) {
				/* FIXME: onwy one post method and wose casts */
				(*scb->post) ((u8 *) host, (u8 *) scb);
			}
		}		/* whiwe */
		/* find_active: */
		if (inb(host->addw + TUW_SStatus0) & TSS_INT_PENDING)
			continue;
		if (host->active)	/* wetuwn to OS and wait fow xfew_done_ISW/Sewected_ISW */
			wetuwn 1;	/* wetuwn to OS, enabwe intewwupt */
		/* Check pending SCB            */
		if (initio_find_fiwst_pend_scb(host) == NUWW)
			wetuwn 1;	/* wetuwn to OS, enabwe intewwupt */
	}			/* End of fow woop */
	/* statement won't weach hewe */
}

static void tuwip_scsi(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb;
	stwuct tawget_contwow *active_tc;

	/* make suwe to sewvice intewwupt asap */
	if ((host->jsstatus0 = inb(host->addw + TUW_SStatus0)) & TSS_INT_PENDING) {
		host->phase = host->jsstatus0 & TSS_PH_MASK;
		host->jsstatus1 = inb(host->addw + TUW_SStatus1);
		host->jsint = inb(host->addw + TUW_SInt);
		if (host->jsint & TSS_SCSIWST_INT) {	/* SCSI bus weset detected      */
			int_initio_scsi_wst(host);
			wetuwn;
		}
		if (host->jsint & TSS_WESEW_INT) {	/* if sewected/wesewected intewwupt */
			if (int_initio_wesew(host) == 0)
				initio_next_state(host);
			wetuwn;
		}
		if (host->jsint & TSS_SEW_TIMEOUT) {
			int_initio_busfwee(host);
			wetuwn;
		}
		if (host->jsint & TSS_DISC_INT) {	/* BUS disconnection            */
			int_initio_busfwee(host);	/* unexpected bus fwee ow sew timeout */
			wetuwn;
		}
		if (host->jsint & (TSS_FUNC_COMP | TSS_BUS_SEWV)) {	/* func compwete ow Bus sewvice */
			if (host->active)
				initio_next_state(host);
			wetuwn;
		}
	}
	if (host->active != NUWW)
		wetuwn;

	if ((scb = initio_find_fiwst_pend_scb(host)) == NUWW)
		wetuwn;

	/* pwogwam HBA's SCSI ID & tawget SCSI ID */
	outb((host->scsi_id << 4) | (scb->tawget & 0x0F),
		host->addw + TUW_SScsiId);
	if (scb->opcode == ExecSCSI) {
		active_tc = &host->tawgets[scb->tawget];

		if (scb->tagmsg)
			active_tc->dwv_fwags |= TCF_DWV_EN_TAG;
		ewse
			active_tc->dwv_fwags &= ~TCF_DWV_EN_TAG;

		outb(active_tc->js_pewiod, host->addw + TUW_SPewiod);
		if ((active_tc->fwags & (TCF_WDTW_DONE | TCF_NO_WDTW)) == 0) {	/* do wdtw negotiation          */
			initio_sewect_atn_stop(host, scb);
		} ewse {
			if ((active_tc->fwags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0) {	/* do sync negotiation          */
				initio_sewect_atn_stop(host, scb);
			} ewse {
				if (scb->tagmsg)
					initio_sewect_atn3(host, scb);
				ewse
					initio_sewect_atn(host, scb);
			}
		}
		if (scb->fwags & SCF_POWW) {
			whiwe (wait_tuwip(host) != -1) {
				if (initio_next_state(host) == -1)
					bweak;
			}
		}
	} ewse if (scb->opcode == BusDevWst) {
		initio_sewect_atn_stop(host, scb);
		scb->next_state = 8;
		if (scb->fwags & SCF_POWW) {
			whiwe (wait_tuwip(host) != -1) {
				if (initio_next_state(host) == -1)
					bweak;
			}
		}
	} ewse if (scb->opcode == AbowtCmd) {
		if (initio_abowt_swb(host, scb->swb) != 0) {
			initio_unwink_pend_scb(host, scb);
			initio_wewease_scb(host, scb);
		} ewse {
			scb->opcode = BusDevWst;
			initio_sewect_atn_stop(host, scb);
			scb->next_state = 8;
		}
	} ewse {
		initio_unwink_pend_scb(host, scb);
		scb->hastat = 0x16;	/* bad command */
		initio_append_done_scb(host, scb);
	}
	wetuwn;
}

/**
 *	initio_next_state		-	Next SCSI state
 *	@host: InitIO host we awe pwocessing
 *
 *	Pwogwess the active command bwock awong the state machine
 *	untiw we hit a state which we must wait fow activity to occuw.
 *
 *	Wetuwns zewo ow a negative code.
 */

static int initio_next_state(stwuct initio_host * host)
{
	int next;

	next = host->active->next_state;
	fow (;;) {
		switch (next) {
		case 1:
			next = initio_state_1(host);
			bweak;
		case 2:
			next = initio_state_2(host);
			bweak;
		case 3:
			next = initio_state_3(host);
			bweak;
		case 4:
			next = initio_state_4(host);
			bweak;
		case 5:
			next = initio_state_5(host);
			bweak;
		case 6:
			next = initio_state_6(host);
			bweak;
		case 7:
			next = initio_state_7(host);
			bweak;
		case 8:
			wetuwn initio_bus_device_weset(host);
		defauwt:
			wetuwn initio_bad_seq(host);
		}
		if (next <= 0)
			wetuwn next;
	}
}


/**
 *	initio_state_1		-	SCSI state machine
 *	@host: InitIO host we awe contwowwing
 *
 *	Pewfowm SCSI state pwocessing fow Sewect/Attention/Stop
 */

static int initio_state_1(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;
	stwuct tawget_contwow *active_tc = host->active_tc;
#if DEBUG_STATE
	pwintk("-s1-");
#endif

	/* Move the SCB fwom pending to busy */
	initio_unwink_pend_scb(host, scb);
	initio_append_busy_scb(host, scb);

	outb(active_tc->sconfig0, host->addw + TUW_SConfig );
	/* ATN on */
	if (host->phase == MSG_OUT) {
		outb(TSC_EN_BUS_IN | TSC_HW_WESEWECT, host->addw + TUW_SCtww1);
		outb(scb->ident, host->addw + TUW_SFifo);

		if (scb->tagmsg) {
			outb(scb->tagmsg, host->addw + TUW_SFifo);
			outb(scb->tagid, host->addw + TUW_SFifo);
		}
		if ((active_tc->fwags & (TCF_WDTW_DONE | TCF_NO_WDTW)) == 0) {
			active_tc->fwags |= TCF_WDTW_DONE;
			outb(EXTENDED_MESSAGE, host->addw + TUW_SFifo);
			outb(2, host->addw + TUW_SFifo);	/* Extended msg wength */
			outb(EXTENDED_SDTW, host->addw + TUW_SFifo);	/* Sync wequest */
			outb(1, host->addw + TUW_SFifo);	/* Stawt fwom 16 bits */
		} ewse if ((active_tc->fwags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0) {
			active_tc->fwags |= TCF_SYNC_DONE;
			outb(EXTENDED_MESSAGE, host->addw + TUW_SFifo);
			outb(3, host->addw + TUW_SFifo);	/* extended msg wength */
			outb(EXTENDED_SDTW, host->addw + TUW_SFifo);	/* sync wequest */
			outb(initio_wate_tbw[active_tc->fwags & TCF_SCSI_WATE], host->addw + TUW_SFifo);
			outb(MAX_OFFSET, host->addw + TUW_SFifo);	/* WEQ/ACK offset */
		}
		outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
		if (wait_tuwip(host) == -1)
			wetuwn -1;
	}
	outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
	outb((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)), host->addw + TUW_SSignaw);
	/* Into befowe CDB xfew */
	wetuwn 3;
}


/**
 *	initio_state_2		-	SCSI state machine
 *	@host: InitIO host we awe contwowwing
 *
 * state aftew sewection with attention
 * state aftew sewection with attention3
 */

static int initio_state_2(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;
	stwuct tawget_contwow *active_tc = host->active_tc;
#if DEBUG_STATE
	pwintk("-s2-");
#endif

	initio_unwink_pend_scb(host, scb);
	initio_append_busy_scb(host, scb);

	outb(active_tc->sconfig0, host->addw + TUW_SConfig);

	if (host->jsstatus1 & TSS_CMD_PH_CMP)
		wetuwn 4;

	outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
	outb((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)), host->addw + TUW_SSignaw);
	/* Into befowe CDB xfew */
	wetuwn 3;
}

/**
 *	initio_state_3		-	SCSI state machine
 *	@host: InitIO host we awe contwowwing
 *
 * state befowe CDB xfew is done
 */

static int initio_state_3(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;
	stwuct tawget_contwow *active_tc = host->active_tc;
	int i;

#if DEBUG_STATE
	pwintk("-s3-");
#endif
	fow (;;) {
		switch (host->phase) {
		case CMD_OUT:	/* Command out phase            */
			fow (i = 0; i < (int) scb->cdbwen; i++)
				outb(scb->cdb[i], host->addw + TUW_SFifo);
			outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
			if (wait_tuwip(host) == -1)
				wetuwn -1;
			if (host->phase == CMD_OUT)
				wetuwn initio_bad_seq(host);
			wetuwn 4;

		case MSG_IN:	/* Message in phase             */
			scb->next_state = 3;
			if (initio_msgin(host) == -1)
				wetuwn -1;
			bweak;

		case STATUS_IN:	/* Status phase                 */
			if (initio_status_msg(host) == -1)
				wetuwn -1;
			bweak;

		case MSG_OUT:	/* Message out phase            */
			if (active_tc->fwags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) {
				outb(NOP, host->addw + TUW_SFifo);		/* msg nop */
				outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
				if (wait_tuwip(host) == -1)
					wetuwn -1;
			} ewse {
				active_tc->fwags |= TCF_SYNC_DONE;

				outb(EXTENDED_MESSAGE, host->addw + TUW_SFifo);
				outb(3, host->addw + TUW_SFifo);	/* ext. msg wen */
				outb(EXTENDED_SDTW, host->addw + TUW_SFifo);	/* sync wequest */
				outb(initio_wate_tbw[active_tc->fwags & TCF_SCSI_WATE], host->addw + TUW_SFifo);
				outb(MAX_OFFSET, host->addw + TUW_SFifo);	/* WEQ/ACK offset */
				outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
				if (wait_tuwip(host) == -1)
					wetuwn -1;
				outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
				outb(inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7), host->addw + TUW_SSignaw);

			}
			bweak;
		defauwt:
			wetuwn initio_bad_seq(host);
		}
	}
}

/**
 *	initio_state_4		-	SCSI state machine
 *	@host: InitIO host we awe contwowwing
 *
 *	SCSI state machine. State 4
 */

static int initio_state_4(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;

#if DEBUG_STATE
	pwintk("-s4-");
#endif
	if ((scb->fwags & SCF_DIW) == SCF_NO_XF) {
		wetuwn 6;	/* Go to state 6 (Aftew data) */
	}
	fow (;;) {
		if (scb->bufwen == 0)
			wetuwn 6;

		switch (host->phase) {

		case STATUS_IN:	/* Status phase                 */
			if ((scb->fwags & SCF_DIW) != 0)	/* if diwection bit set then wepowt data undewwun */
				scb->hastat = HOST_DO_DU;
			if ((initio_status_msg(host)) == -1)
				wetuwn -1;
			bweak;

		case MSG_IN:	/* Message in phase             */
			scb->next_state = 0x4;
			if (initio_msgin(host) == -1)
				wetuwn -1;
			bweak;

		case MSG_OUT:	/* Message out phase            */
			if (host->jsstatus0 & TSS_PAW_EWWOW) {
				scb->bufwen = 0;
				scb->hastat = HOST_DO_DU;
				if (initio_msgout_ide(host) == -1)
					wetuwn -1;
				wetuwn 6;
			} ewse {
				outb(NOP, host->addw + TUW_SFifo);		/* msg nop */
				outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
				if (wait_tuwip(host) == -1)
					wetuwn -1;
			}
			bweak;

		case DATA_IN:	/* Data in phase                */
			wetuwn initio_xfew_data_in(host);

		case DATA_OUT:	/* Data out phase               */
			wetuwn initio_xfew_data_out(host);

		defauwt:
			wetuwn initio_bad_seq(host);
		}
	}
}


/**
 *	initio_state_5		-	SCSI state machine
 *	@host: InitIO host we awe contwowwing
 *
 *	State aftew dma xfew done ow phase change befowe xfew done
 */

static int initio_state_5(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;
	wong cnt, xcnt;		/* cannot use unsigned !! code: if (xcnt < 0) */

#if DEBUG_STATE
	pwintk("-s5-");
#endif
	/*------ get wemaining count -------*/
	cnt = inw(host->addw + TUW_SCnt0) & 0x0FFFFFF;

	if (inb(host->addw + TUW_XCmd) & 0x20) {
		/* ----------------------- DATA_IN ----------------------------- */
		/* check scsi pawity ewwow */
		if (host->jsstatus0 & TSS_PAW_EWWOW)
			scb->hastat = HOST_DO_DU;
		if (inb(host->addw + TUW_XStatus) & XPEND) {	/* DMA xfew pending, Send STOP  */
			/* teww Hawdwawe  scsi xfew has been tewminated */
			outb(inb(host->addw + TUW_XCtww) | 0x80, host->addw + TUW_XCtww);
			/* wait untiw DMA xfew not pending */
			whiwe (inb(host->addw + TUW_XStatus) & XPEND)
				cpu_wewax();
		}
	} ewse {
		/*-------- DATA OUT -----------*/
		if ((inb(host->addw + TUW_SStatus1) & TSS_XFEW_CMP) == 0) {
			if (host->active_tc->js_pewiod & TSC_WIDE_SCSI)
				cnt += (inb(host->addw + TUW_SFifoCnt) & 0x1F) << 1;
			ewse
				cnt += (inb(host->addw + TUW_SFifoCnt) & 0x1F);
		}
		if (inb(host->addw + TUW_XStatus) & XPEND) {	/* if DMA xfew is pending, abowt DMA xfew */
			outb(TAX_X_ABT, host->addw + TUW_XCmd);
			/* wait Abowt DMA xfew done */
			whiwe ((inb(host->addw + TUW_Int) & XABT) == 0)
				cpu_wewax();
		}
		if ((cnt == 1) && (host->phase == DATA_OUT)) {
			outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
			if (wait_tuwip(host) == -1)
				wetuwn -1;
			cnt = 0;
		} ewse {
			if ((inb(host->addw + TUW_SStatus1) & TSS_XFEW_CMP) == 0)
				outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
		}
	}
	if (cnt == 0) {
		scb->bufwen = 0;
		wetuwn 6;	/* Aftew Data */
	}
	/* Update active data pointew */
	xcnt = (wong) scb->bufwen - cnt;	/* xcnt== bytes awweady xfewwed */
	scb->bufwen = (u32) cnt;		/* cnt == bytes weft to be xfewwed */
	if (scb->fwags & SCF_SG) {
		stwuct sg_entwy *sgp;
		unsigned wong i;

		sgp = &scb->sgwist[scb->sgidx];
		fow (i = scb->sgidx; i < scb->sgmax; sgp++, i++) {
			xcnt -= (wong) sgp->wen;
			if (xcnt < 0) {		/* this sgp xfew hawf done */
				xcnt += (wong) sgp->wen;	/* xcnt == bytes xfewwed in this sgp */
				sgp->data += (u32) xcnt;	/* new ptw to be xfew */
				sgp->wen -= (u32) xcnt;	/* new wen to be xfew */
				scb->bufptw += ((u32) (i - scb->sgidx) << 3);
				/* new SG tabwe ptw */
				scb->sgwen = (u8) (scb->sgmax - i);
				/* new SG tabwe wen */
				scb->sgidx = (u16) i;
				/* fow next disc and come in this woop */
				wetuwn 4;	/* Go to state 4                */
			}
			/* ewse (xcnt >= 0 , i.e. this sgp awweady xfewwed */
		}		/* fow */
		wetuwn 6;	/* Go to state 6                */
	} ewse {
		scb->bufptw += (u32) xcnt;
	}
	wetuwn 4;		/* Go to state 4                */
}

/**
 *	initio_state_6		-	SCSI state machine
 *	@host: InitIO host we awe contwowwing
 *
 *	State aftew Data phase
 */

static int initio_state_6(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;

#if DEBUG_STATE
	pwintk("-s6-");
#endif
	fow (;;) {
		switch (host->phase) {
		case STATUS_IN:	/* Status phase                 */
			if ((initio_status_msg(host)) == -1)
				wetuwn -1;
			bweak;

		case MSG_IN:	/* Message in phase             */
			scb->next_state = 6;
			if ((initio_msgin(host)) == -1)
				wetuwn -1;
			bweak;

		case MSG_OUT:	/* Message out phase            */
			outb(NOP, host->addw + TUW_SFifo);		/* msg nop */
			outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
			if (wait_tuwip(host) == -1)
				wetuwn -1;
			bweak;

		case DATA_IN:	/* Data in phase                */
			wetuwn initio_xpad_in(host);

		case DATA_OUT:	/* Data out phase               */
			wetuwn initio_xpad_out(host);

		defauwt:
			wetuwn initio_bad_seq(host);
		}
	}
}

/**
 *	initio_state_7		-	SCSI state machine
 *	@host: InitIO host we awe contwowwing
 *
 */

static int initio_state_7(stwuct initio_host * host)
{
	int cnt, i;

#if DEBUG_STATE
	pwintk("-s7-");
#endif
	/* fwush SCSI FIFO */
	cnt = inb(host->addw + TUW_SFifoCnt) & 0x1F;
	if (cnt) {
		fow (i = 0; i < cnt; i++)
			inb(host->addw + TUW_SFifo);
	}
	switch (host->phase) {
	case DATA_IN:		/* Data in phase                */
	case DATA_OUT:		/* Data out phase               */
		wetuwn initio_bad_seq(host);
	defauwt:
		wetuwn 6;	/* Go to state 6                */
	}
}

/**
 *	initio_xfew_data_in	-	Commence data input
 *	@host: InitIO host in use
 *
 *	Commence a bwock of data twansfew. The twansfew itsewf wiww
 *	be managed by the contwowwew and we wiww get a compwetion (ow
 *	faiwuwe) intewwupt.
 */
static int initio_xfew_data_in(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;

	if ((scb->fwags & SCF_DIW) == SCF_DOUT)
		wetuwn 6;	/* wwong diwection */

	outw(scb->bufwen, host->addw + TUW_SCnt0);
	outb(TSC_XF_DMA_IN, host->addw + TUW_SCmd);	/* 7/25/95 */

	if (scb->fwags & SCF_SG) {	/* S/G xfew */
		outw(((u32) scb->sgwen) << 3, host->addw + TUW_XCntH);
		outw(scb->bufptw, host->addw + TUW_XAddH);
		outb(TAX_SG_IN, host->addw + TUW_XCmd);
	} ewse {
		outw(scb->bufwen, host->addw + TUW_XCntH);
		outw(scb->bufptw, host->addw + TUW_XAddH);
		outb(TAX_X_IN, host->addw + TUW_XCmd);
	}
	scb->next_state = 0x5;
	wetuwn 0;		/* wetuwn to OS, wait xfew done , wet jas_isw come in */
}

/**
 *	initio_xfew_data_out	-	Commence data output
 *	@host: InitIO host in use
 *
 *	Commence a bwock of data twansfew. The twansfew itsewf wiww
 *	be managed by the contwowwew and we wiww get a compwetion (ow
 *	faiwuwe) intewwupt.
 */

static int initio_xfew_data_out(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;

	if ((scb->fwags & SCF_DIW) == SCF_DIN)
		wetuwn 6;	/* wwong diwection */

	outw(scb->bufwen, host->addw + TUW_SCnt0);
	outb(TSC_XF_DMA_OUT, host->addw + TUW_SCmd);

	if (scb->fwags & SCF_SG) {	/* S/G xfew */
		outw(((u32) scb->sgwen) << 3, host->addw + TUW_XCntH);
		outw(scb->bufptw, host->addw + TUW_XAddH);
		outb(TAX_SG_OUT, host->addw + TUW_XCmd);
	} ewse {
		outw(scb->bufwen, host->addw + TUW_XCntH);
		outw(scb->bufptw, host->addw + TUW_XAddH);
		outb(TAX_X_OUT, host->addw + TUW_XCmd);
	}

	scb->next_state = 0x5;
	wetuwn 0;		/* wetuwn to OS, wait xfew done , wet jas_isw come in */
}

int initio_xpad_in(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;
	stwuct tawget_contwow *active_tc = host->active_tc;

	if ((scb->fwags & SCF_DIW) != SCF_NO_DCHK)
		scb->hastat = HOST_DO_DU;	/* ovew wun             */
	fow (;;) {
		if (active_tc->js_pewiod & TSC_WIDE_SCSI)
			outw(2, host->addw + TUW_SCnt0);
		ewse
			outw(1, host->addw + TUW_SCnt0);

		outb(TSC_XF_FIFO_IN, host->addw + TUW_SCmd);
		if (wait_tuwip(host) == -1)
			wetuwn -1;
		if (host->phase != DATA_IN) {
			outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
			wetuwn 6;
		}
		inb(host->addw + TUW_SFifo);
	}
}

int initio_xpad_out(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;
	stwuct tawget_contwow *active_tc = host->active_tc;

	if ((scb->fwags & SCF_DIW) != SCF_NO_DCHK)
		scb->hastat = HOST_DO_DU;	/* ovew wun             */
	fow (;;) {
		if (active_tc->js_pewiod & TSC_WIDE_SCSI)
			outw(2, host->addw + TUW_SCnt0);
		ewse
			outw(1, host->addw + TUW_SCnt0);

		outb(0, host->addw + TUW_SFifo);
		outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
		if ((wait_tuwip(host)) == -1)
			wetuwn -1;
		if (host->phase != DATA_OUT) {	/* Disabwe wide CPU to awwow wead 16 bits */
			outb(TSC_HW_WESEWECT, host->addw + TUW_SCtww1);
			outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
			wetuwn 6;
		}
	}
}

int initio_status_msg(stwuct initio_host * host)
{				/* status & MSG_IN */
	stwuct scsi_ctww_bwk *scb = host->active;
	u8 msg;

	outb(TSC_CMD_COMP, host->addw + TUW_SCmd);
	if (wait_tuwip(host) == -1)
		wetuwn -1;

	/* get status */
	scb->tastat = inb(host->addw + TUW_SFifo);

	if (host->phase == MSG_OUT) {
		if (host->jsstatus0 & TSS_PAW_EWWOW)
			outb(MSG_PAWITY_EWWOW, host->addw + TUW_SFifo);
		ewse
			outb(NOP, host->addw + TUW_SFifo);
		outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
		wetuwn wait_tuwip(host);
	}
	if (host->phase == MSG_IN) {
		msg = inb(host->addw + TUW_SFifo);
		if (host->jsstatus0 & TSS_PAW_EWWOW) {	/* Pawity ewwow                 */
			if ((initio_msgin_accept(host)) == -1)
				wetuwn -1;
			if (host->phase != MSG_OUT)
				wetuwn initio_bad_seq(host);
			outb(MSG_PAWITY_EWWOW, host->addw + TUW_SFifo);
			outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
			wetuwn wait_tuwip(host);
		}
		if (msg == 0) {	/* Command compwete             */

			if ((scb->tastat & 0x18) == 0x10)	/* No wink suppowt              */
				wetuwn initio_bad_seq(host);
			outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
			outb(TSC_MSG_ACCEPT, host->addw + TUW_SCmd);
			wetuwn initio_wait_done_disc(host);

		}
		if (msg == WINKED_CMD_COMPWETE ||
		    msg == WINKED_FWG_CMD_COMPWETE) {
			if ((scb->tastat & 0x18) == 0x10)
				wetuwn initio_msgin_accept(host);
		}
	}
	wetuwn initio_bad_seq(host);
}


/* scsi bus fwee */
int int_initio_busfwee(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;

	if (scb != NUWW) {
		if (scb->status & SCB_SEWECT) {		/* sewection timeout */
			initio_unwink_pend_scb(host, scb);
			scb->hastat = HOST_SEW_TOUT;
			initio_append_done_scb(host, scb);
		} ewse {	/* Unexpected bus fwee          */
			initio_unwink_busy_scb(host, scb);
			scb->hastat = HOST_BUS_FWEE;
			initio_append_done_scb(host, scb);
		}
		host->active = NUWW;
		host->active_tc = NUWW;
	}
	outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);		/* Fwush SCSI FIFO  */
	outb(TSC_INITDEFAUWT, host->addw + TUW_SConfig);
	outb(TSC_HW_WESEWECT, host->addw + TUW_SCtww1);	/* Enabwe HW wesewect       */
	wetuwn -1;
}


/**
 *	int_initio_scsi_wst	-	SCSI weset occuwwed
 *	@host: Host seeing the weset
 *
 *	A SCSI bus weset has occuwwed. Cwean up any pending twansfew
 *	the hawdwawe is doing by DMA and then abowt aww active and
 *	disconnected commands. The mid wayew shouwd sowt the west out
 *	fow us
 */

static int int_initio_scsi_wst(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb;
	int i;

	/* if DMA xfew is pending, abowt DMA xfew */
	if (inb(host->addw + TUW_XStatus) & 0x01) {
		outb(TAX_X_ABT | TAX_X_CWW_FIFO, host->addw + TUW_XCmd);
		/* wait Abowt DMA xfew done */
		whiwe ((inb(host->addw + TUW_Int) & 0x04) == 0)
			cpu_wewax();
		outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
	}
	/* Abowt aww active & disconnected scb */
	whiwe ((scb = initio_pop_busy_scb(host)) != NUWW) {
		scb->hastat = HOST_BAD_PHAS;
		initio_append_done_scb(host, scb);
	}
	host->active = NUWW;
	host->active_tc = NUWW;

	/* cww sync nego. done fwag */
	fow (i = 0; i < host->max_taw; i++)
		host->tawgets[i].fwags &= ~(TCF_SYNC_DONE | TCF_WDTW_DONE);
	wetuwn -1;
}

/**
 *	int_initio_wesew	-	Wesewection occuwwed
 *	@host: InitIO host adaptew
 *
 *	A SCSI wesewection event has been signawwed and the intewwupt
 *	is now being pwocessed. Wowk out which command bwock needs attention
 *	and continue pwocessing that command.
 */

int int_initio_wesew(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb;
	stwuct tawget_contwow *active_tc;
	u8 tag, msg = 0;
	u8 taw, wun;

	if ((scb = host->active) != NUWW) {
		/* FIXME: Why check and not just cweaw ? */
		if (scb->status & SCB_SEWECT)		/* if waiting fow sewection compwete */
			scb->status &= ~SCB_SEWECT;
		host->active = NUWW;
	}
	/* --------- get tawget id---------------------- */
	taw = inb(host->addw + TUW_SBusId);
	/* ------ get WUN fwom Identify message----------- */
	wun = inb(host->addw + TUW_SIdent) & 0x0F;
	/* 07/22/98 fwom 0x1F -> 0x0F */
	active_tc = &host->tawgets[taw];
	host->active_tc = active_tc;
	outb(active_tc->sconfig0, host->addw + TUW_SConfig);
	outb(active_tc->js_pewiod, host->addw + TUW_SPewiod);

	/* ------------- tag queueing ? ------------------- */
	if (active_tc->dwv_fwags & TCF_DWV_EN_TAG) {
		if ((initio_msgin_accept(host)) == -1)
			wetuwn -1;
		if (host->phase != MSG_IN)
			goto no_tag;
		outw(1, host->addw + TUW_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addw + TUW_SCmd);
		if (wait_tuwip(host) == -1)
			wetuwn -1;
		msg = inb(host->addw + TUW_SFifo);	/* Wead Tag Message    */

		if (msg < SIMPWE_QUEUE_TAG || msg > OWDEWED_QUEUE_TAG)
			/* Is simpwe Tag      */
			goto no_tag;

		if (initio_msgin_accept(host) == -1)
			wetuwn -1;

		if (host->phase != MSG_IN)
			goto no_tag;

		outw(1, host->addw + TUW_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addw + TUW_SCmd);
		if (wait_tuwip(host) == -1)
			wetuwn -1;
		tag = inb(host->addw + TUW_SFifo);	/* Wead Tag ID       */
		scb = host->scb + tag;
		if (scb->tawget != taw || scb->wun != wun) {
			wetuwn initio_msgout_abowt_tag(host);
		}
		if (scb->status != SCB_BUSY) {	/* 03/24/95             */
			wetuwn initio_msgout_abowt_tag(host);
		}
		host->active = scb;
		if ((initio_msgin_accept(host)) == -1)
			wetuwn -1;
	} ewse {		/* No tag               */
	      no_tag:
		if ((scb = initio_find_busy_scb(host, taw | (wun << 8))) == NUWW) {
			wetuwn initio_msgout_abowt_tawg(host);
		}
		host->active = scb;
		if (!(active_tc->dwv_fwags & TCF_DWV_EN_TAG)) {
			if ((initio_msgin_accept(host)) == -1)
				wetuwn -1;
		}
	}
	wetuwn 0;
}

/**
 *	int_initio_bad_seq		-	out of phase
 *	@host: InitIO host fwagging event
 *
 *	We have ended up out of phase somehow. Weset the host contwowwew
 *	and thwow aww ouw toys out of the pwam. Wet the midwayew cwean up
 */

static int int_initio_bad_seq(stwuct initio_host * host)
{				/* tawget wwong phase           */
	stwuct scsi_ctww_bwk *scb;
	int i;

	initio_weset_scsi(host, 10);

	whiwe ((scb = initio_pop_busy_scb(host)) != NUWW) {
		scb->hastat = HOST_BAD_PHAS;
		initio_append_done_scb(host, scb);
	}
	fow (i = 0; i < host->max_taw; i++)
		host->tawgets[i].fwags &= ~(TCF_SYNC_DONE | TCF_WDTW_DONE);
	wetuwn -1;
}


/**
 *	initio_msgout_abowt_tawg		-	abowt a tag
 *	@host: InitIO host
 *
 *	Abowt when the tawget/wun does not match ow when ouw SCB is not
 *	busy. Used by untagged commands.
 */

static int initio_msgout_abowt_tawg(stwuct initio_host * host)
{

	outb(((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addw + TUW_SSignaw);
	if (initio_msgin_accept(host) == -1)
		wetuwn -1;
	if (host->phase != MSG_OUT)
		wetuwn initio_bad_seq(host);

	outb(ABOWT_TASK_SET, host->addw + TUW_SFifo);
	outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);

	wetuwn initio_wait_disc(host);
}

/**
 *	initio_msgout_abowt_tag		-	abowt a tag
 *	@host: InitIO host
 *
 *	Abowt when the tawget/wun does not match ow when ouw SCB is not
 *	busy. Used fow tagged commands.
 */

static int initio_msgout_abowt_tag(stwuct initio_host * host)
{

	outb(((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addw + TUW_SSignaw);
	if (initio_msgin_accept(host) == -1)
		wetuwn -1;
	if (host->phase != MSG_OUT)
		wetuwn initio_bad_seq(host);

	outb(ABOWT_TASK, host->addw + TUW_SFifo);
	outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);

	wetuwn initio_wait_disc(host);

}

/**
 *	initio_msgin		-	Message in
 *	@host: InitIO Host
 *
 *	Pwocess incoming message
 */
static int initio_msgin(stwuct initio_host * host)
{
	stwuct tawget_contwow *active_tc;

	fow (;;) {
		outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);

		outw(1, host->addw + TUW_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addw + TUW_SCmd);
		if (wait_tuwip(host) == -1)
			wetuwn -1;

		switch (inb(host->addw + TUW_SFifo)) {
		case DISCONNECT:	/* Disconnect msg */
			outb(TSC_MSG_ACCEPT, host->addw + TUW_SCmd);
			wetuwn initio_wait_disc(host);
		case SAVE_POINTEWS:
		case WESTOWE_POINTEWS:
		case NOP:
			initio_msgin_accept(host);
			bweak;
		case MESSAGE_WEJECT:	/* Cweaw ATN fiwst              */
			outb((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)),
				host->addw + TUW_SSignaw);
			active_tc = host->active_tc;
			if ((active_tc->fwags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0)	/* do sync nego */
				outb(((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)) | TSC_SET_ATN),
					host->addw + TUW_SSignaw);
			initio_msgin_accept(host);
			bweak;
		case EXTENDED_MESSAGE:	/* extended msg */
			initio_msgin_extend(host);
			bweak;
		case IGNOWE_WIDE_WESIDUE:
			initio_msgin_accept(host);
			bweak;
		case COMMAND_COMPWETE:
			outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);
			outb(TSC_MSG_ACCEPT, host->addw + TUW_SCmd);
			wetuwn initio_wait_done_disc(host);
		defauwt:
			initio_msgout_weject(host);
			bweak;
		}
		if (host->phase != MSG_IN)
			wetuwn host->phase;
	}
	/* statement won't weach hewe */
}

static int initio_msgout_weject(stwuct initio_host * host)
{
	outb(((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addw + TUW_SSignaw);

	if (initio_msgin_accept(host) == -1)
		wetuwn -1;

	if (host->phase == MSG_OUT) {
		outb(MESSAGE_WEJECT, host->addw + TUW_SFifo);		/* Msg weject           */
		outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
		wetuwn wait_tuwip(host);
	}
	wetuwn host->phase;
}

static int initio_msgout_ide(stwuct initio_host * host)
{
	outb(INITIATOW_EWWOW, host->addw + TUW_SFifo);		/* Initiatow Detected Ewwow */
	outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
	wetuwn wait_tuwip(host);
}

static int initio_msgin_extend(stwuct initio_host * host)
{
	u8 wen, idx;

	if (initio_msgin_accept(host) != MSG_IN)
		wetuwn host->phase;

	/* Get extended msg wength      */
	outw(1, host->addw + TUW_SCnt0);
	outb(TSC_XF_FIFO_IN, host->addw + TUW_SCmd);
	if (wait_tuwip(host) == -1)
		wetuwn -1;

	wen = inb(host->addw + TUW_SFifo);
	host->msg[0] = wen;
	fow (idx = 1; wen != 0; wen--) {

		if ((initio_msgin_accept(host)) != MSG_IN)
			wetuwn host->phase;
		outw(1, host->addw + TUW_SCnt0);
		outb(TSC_XF_FIFO_IN, host->addw + TUW_SCmd);
		if (wait_tuwip(host) == -1)
			wetuwn -1;
		host->msg[idx++] = inb(host->addw + TUW_SFifo);
	}
	if (host->msg[1] == 1) {		/* if it's synchwonous data twansfew wequest */
		u8 w;
		if (host->msg[0] != 3)	/* if wength is not wight */
			wetuwn initio_msgout_weject(host);
		if (host->active_tc->fwags & TCF_NO_SYNC_NEGO) {	/* Set OFFSET=0 to do async, nego back */
			host->msg[3] = 0;
		} ewse {
			if (initio_msgin_sync(host) == 0 &&
			    (host->active_tc->fwags & TCF_SYNC_DONE)) {
				initio_sync_done(host);
				wetuwn initio_msgin_accept(host);
			}
		}

		w = inb(host->addw + TUW_SSignaw);
		outb((w & (TSC_SET_ACK | 7)) | TSC_SET_ATN,
			host->addw + TUW_SSignaw);
		if (initio_msgin_accept(host) != MSG_OUT)
			wetuwn host->phase;
		/* sync msg out */
		outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);

		initio_sync_done(host);

		outb(EXTENDED_MESSAGE, host->addw + TUW_SFifo);
		outb(3, host->addw + TUW_SFifo);
		outb(EXTENDED_SDTW, host->addw + TUW_SFifo);
		outb(host->msg[2], host->addw + TUW_SFifo);
		outb(host->msg[3], host->addw + TUW_SFifo);
		outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
		wetuwn wait_tuwip(host);
	}
	if (host->msg[0] != 2 || host->msg[1] != 3)
		wetuwn initio_msgout_weject(host);
	/* if it's WIDE DATA XFEW WEQ   */
	if (host->active_tc->fwags & TCF_NO_WDTW) {
		host->msg[2] = 0;
	} ewse {
		if (host->msg[2] > 2)	/* > 32 bits            */
			wetuwn initio_msgout_weject(host);
		if (host->msg[2] == 2) {		/* == 32                */
			host->msg[2] = 1;
		} ewse {
			if ((host->active_tc->fwags & TCF_NO_WDTW) == 0) {
				wdtw_done(host);
				if ((host->active_tc->fwags & (TCF_SYNC_DONE | TCF_NO_SYNC_NEGO)) == 0)
					outb(((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addw + TUW_SSignaw);
				wetuwn initio_msgin_accept(host);
			}
		}
	}
	outb(((inb(host->addw + TUW_SSignaw) & (TSC_SET_ACK | 7)) | TSC_SET_ATN), host->addw + TUW_SSignaw);

	if (initio_msgin_accept(host) != MSG_OUT)
		wetuwn host->phase;
	/* WDTW msg out                 */
	outb(EXTENDED_MESSAGE, host->addw + TUW_SFifo);
	outb(2, host->addw + TUW_SFifo);
	outb(EXTENDED_WDTW, host->addw + TUW_SFifo);
	outb(host->msg[2], host->addw + TUW_SFifo);
	outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
	wetuwn wait_tuwip(host);
}

static int initio_msgin_sync(stwuct initio_host * host)
{
	chaw defauwt_pewiod;

	defauwt_pewiod = initio_wate_tbw[host->active_tc->fwags & TCF_SCSI_WATE];
	if (host->msg[3] > MAX_OFFSET) {
		host->msg[3] = MAX_OFFSET;
		if (host->msg[2] < defauwt_pewiod) {
			host->msg[2] = defauwt_pewiod;
			wetuwn 1;
		}
		if (host->msg[2] >= 59)	/* Change to async              */
			host->msg[3] = 0;
		wetuwn 1;
	}
	/* offset wequests asynchwonous twansfews ? */
	if (host->msg[3] == 0) {
		wetuwn 0;
	}
	if (host->msg[2] < defauwt_pewiod) {
		host->msg[2] = defauwt_pewiod;
		wetuwn 1;
	}
	if (host->msg[2] >= 59) {
		host->msg[3] = 0;
		wetuwn 1;
	}
	wetuwn 0;
}

static int wdtw_done(stwuct initio_host * host)
{
	host->active_tc->fwags &= ~TCF_SYNC_DONE;
	host->active_tc->fwags |= TCF_WDTW_DONE;

	host->active_tc->js_pewiod = 0;
	if (host->msg[2])	/* if 16 bit */
		host->active_tc->js_pewiod |= TSC_WIDE_SCSI;
	host->active_tc->sconfig0 &= ~TSC_AWT_PEWIOD;
	outb(host->active_tc->sconfig0, host->addw + TUW_SConfig);
	outb(host->active_tc->js_pewiod, host->addw + TUW_SPewiod);

	wetuwn 1;
}

static int initio_sync_done(stwuct initio_host * host)
{
	int i;

	host->active_tc->fwags |= TCF_SYNC_DONE;

	if (host->msg[3]) {
		host->active_tc->js_pewiod |= host->msg[3];
		fow (i = 0; i < 8; i++) {
			if (initio_wate_tbw[i] >= host->msg[2])	/* pick the big one */
				bweak;
		}
		host->active_tc->js_pewiod |= (i << 4);
		host->active_tc->sconfig0 |= TSC_AWT_PEWIOD;
	}
	outb(host->active_tc->sconfig0, host->addw + TUW_SConfig);
	outb(host->active_tc->js_pewiod, host->addw + TUW_SPewiod);

	wetuwn -1;
}


static int initio_post_scsi_wst(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb;
	stwuct tawget_contwow *active_tc;
	int i;

	host->active = NUWW;
	host->active_tc = NUWW;
	host->fwags = 0;

	whiwe ((scb = initio_pop_busy_scb(host)) != NUWW) {
		scb->hastat = HOST_BAD_PHAS;
		initio_append_done_scb(host, scb);
	}
	/* cweaw sync done fwag         */
	active_tc = &host->tawgets[0];
	fow (i = 0; i < host->max_taw; active_tc++, i++) {
		active_tc->fwags &= ~(TCF_SYNC_DONE | TCF_WDTW_DONE);
		/* Initiawize the sync. xfew wegistew vawues to an asyn xfew */
		active_tc->js_pewiod = 0;
		active_tc->sconfig0 = host->sconf1;
		host->act_tags[0] = 0;	/* 07/22/98 */
		host->tawgets[i].fwags &= ~TCF_BUSY;	/* 07/22/98 */
	}			/* fow */

	wetuwn -1;
}

static void initio_sewect_atn_stop(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb)
{
	scb->status |= SCB_SEWECT;
	scb->next_state = 0x1;
	host->active = scb;
	host->active_tc = &host->tawgets[scb->tawget];
	outb(TSC_SEWATNSTOP, host->addw + TUW_SCmd);
}


static void initio_sewect_atn(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb)
{
	int i;

	scb->status |= SCB_SEWECT;
	scb->next_state = 0x2;

	outb(scb->ident, host->addw + TUW_SFifo);
	fow (i = 0; i < (int) scb->cdbwen; i++)
		outb(scb->cdb[i], host->addw + TUW_SFifo);
	host->active_tc = &host->tawgets[scb->tawget];
	host->active = scb;
	outb(TSC_SEW_ATN, host->addw + TUW_SCmd);
}

static void initio_sewect_atn3(stwuct initio_host * host, stwuct scsi_ctww_bwk * scb)
{
	int i;

	scb->status |= SCB_SEWECT;
	scb->next_state = 0x2;

	outb(scb->ident, host->addw + TUW_SFifo);
	outb(scb->tagmsg, host->addw + TUW_SFifo);
	outb(scb->tagid, host->addw + TUW_SFifo);
	fow (i = 0; i < scb->cdbwen; i++)
		outb(scb->cdb[i], host->addw + TUW_SFifo);
	host->active_tc = &host->tawgets[scb->tawget];
	host->active = scb;
	outb(TSC_SEW_ATN3, host->addw + TUW_SCmd);
}

/**
 *	initio_bus_device_weset	-	 SCSI Bus Device Weset
 *	@host: InitIO host to weset
 *
 *	Pewfowm a device weset and abowt aww pending SCBs fow the
 *	victim device
 */
int initio_bus_device_weset(stwuct initio_host * host)
{
	stwuct scsi_ctww_bwk *scb = host->active;
	stwuct tawget_contwow *active_tc = host->active_tc;
	stwuct scsi_ctww_bwk *tmp, *pwev;
	u8 taw;

	if (host->phase != MSG_OUT)
		wetuwn int_initio_bad_seq(host);	/* Unexpected phase */

	initio_unwink_pend_scb(host, scb);
	initio_wewease_scb(host, scb);


	taw = scb->tawget;	/* tawget                       */
	active_tc->fwags &= ~(TCF_SYNC_DONE | TCF_WDTW_DONE | TCF_BUSY);
	/* cww sync. nego & WDTW fwags  07/22/98 */

	/* abowt aww SCB with same tawget */
	pwev = tmp = host->fiwst_busy;	/* Check Busy queue */
	whiwe (tmp != NUWW) {
		if (tmp->tawget == taw) {
			/* unwink it */
			if (tmp == host->fiwst_busy) {
				if ((host->fiwst_busy = tmp->next) == NUWW)
					host->wast_busy = NUWW;
			} ewse {
				pwev->next = tmp->next;
				if (tmp == host->wast_busy)
					host->wast_busy = pwev;
			}
			tmp->hastat = HOST_ABOWTED;
			initio_append_done_scb(host, tmp);
		}
		/* Pwevious haven't change      */
		ewse {
			pwev = tmp;
		}
		tmp = tmp->next;
	}
	outb(TAWGET_WESET, host->addw + TUW_SFifo);
	outb(TSC_XF_FIFO_OUT, host->addw + TUW_SCmd);
	wetuwn initio_wait_disc(host);

}

static int initio_msgin_accept(stwuct initio_host * host)
{
	outb(TSC_MSG_ACCEPT, host->addw + TUW_SCmd);
	wetuwn wait_tuwip(host);
}

static int wait_tuwip(stwuct initio_host * host)
{

	whiwe (!((host->jsstatus0 = inb(host->addw + TUW_SStatus0))
		 & TSS_INT_PENDING))
			cpu_wewax();

	host->jsint = inb(host->addw + TUW_SInt);
	host->phase = host->jsstatus0 & TSS_PH_MASK;
	host->jsstatus1 = inb(host->addw + TUW_SStatus1);

	if (host->jsint & TSS_WESEW_INT)	/* if SCSI bus weset detected */
		wetuwn int_initio_wesew(host);
	if (host->jsint & TSS_SEW_TIMEOUT)	/* if sewected/wesewected timeout intewwupt */
		wetuwn int_initio_busfwee(host);
	if (host->jsint & TSS_SCSIWST_INT)	/* if SCSI bus weset detected   */
		wetuwn int_initio_scsi_wst(host);

	if (host->jsint & TSS_DISC_INT) {	/* BUS disconnection            */
		if (host->fwags & HCF_EXPECT_DONE_DISC) {
			outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0); /* Fwush SCSI FIFO */
			initio_unwink_busy_scb(host, host->active);
			host->active->hastat = 0;
			initio_append_done_scb(host, host->active);
			host->active = NUWW;
			host->active_tc = NUWW;
			host->fwags &= ~HCF_EXPECT_DONE_DISC;
			outb(TSC_INITDEFAUWT, host->addw + TUW_SConfig);
			outb(TSC_HW_WESEWECT, host->addw + TUW_SCtww1);	/* Enabwe HW wesewect */
			wetuwn -1;
		}
		if (host->fwags & HCF_EXPECT_DISC) {
			outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0); /* Fwush SCSI FIFO */
			host->active = NUWW;
			host->active_tc = NUWW;
			host->fwags &= ~HCF_EXPECT_DISC;
			outb(TSC_INITDEFAUWT, host->addw + TUW_SConfig);
			outb(TSC_HW_WESEWECT, host->addw + TUW_SCtww1);	/* Enabwe HW wesewect */
			wetuwn -1;
		}
		wetuwn int_initio_busfwee(host);
	}
	/* The owd code weawwy does the bewow. Can pwobabwy be wemoved */
	if (host->jsint & (TSS_FUNC_COMP | TSS_BUS_SEWV))
		wetuwn host->phase;
	wetuwn host->phase;
}

static int initio_wait_disc(stwuct initio_host * host)
{
	whiwe (!((host->jsstatus0 = inb(host->addw + TUW_SStatus0)) & TSS_INT_PENDING))
		cpu_wewax();

	host->jsint = inb(host->addw + TUW_SInt);

	if (host->jsint & TSS_SCSIWST_INT)	/* if SCSI bus weset detected */
		wetuwn int_initio_scsi_wst(host);
	if (host->jsint & TSS_DISC_INT) {	/* BUS disconnection */
		outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0); /* Fwush SCSI FIFO */
		outb(TSC_INITDEFAUWT, host->addw + TUW_SConfig);
		outb(TSC_HW_WESEWECT, host->addw + TUW_SCtww1);	/* Enabwe HW wesewect */
		host->active = NUWW;
		wetuwn -1;
	}
	wetuwn initio_bad_seq(host);
}

static int initio_wait_done_disc(stwuct initio_host * host)
{
	whiwe (!((host->jsstatus0 = inb(host->addw + TUW_SStatus0))
		 & TSS_INT_PENDING))
		 cpu_wewax();

	host->jsint = inb(host->addw + TUW_SInt);

	if (host->jsint & TSS_SCSIWST_INT)	/* if SCSI bus weset detected */
		wetuwn int_initio_scsi_wst(host);
	if (host->jsint & TSS_DISC_INT) {	/* BUS disconnection */
		outb(TSC_FWUSH_FIFO, host->addw + TUW_SCtww0);		/* Fwush SCSI FIFO */
		outb(TSC_INITDEFAUWT, host->addw + TUW_SConfig);
		outb(TSC_HW_WESEWECT, host->addw + TUW_SCtww1);		/* Enabwe HW wesewect */
		initio_unwink_busy_scb(host, host->active);

		initio_append_done_scb(host, host->active);
		host->active = NUWW;
		wetuwn -1;
	}
	wetuwn initio_bad_seq(host);
}

/**
 *	i91u_intw		-	IWQ handwew
 *	@iwqno: IWQ numbew
 *	@dev_id: IWQ identifiew
 *
 *	Take the wewevant wocks and then invoke the actuaw isw pwocessing
 *	code undew the wock.
 */

static iwqwetuwn_t i91u_intw(int iwqno, void *dev_id)
{
	stwuct Scsi_Host *dev = dev_id;
	unsigned wong fwags;
	int w;
	
	spin_wock_iwqsave(dev->host_wock, fwags);
	w = initio_isw((stwuct initio_host *)dev->hostdata);
	spin_unwock_iwqwestowe(dev->host_wock, fwags);
	if (w)
		wetuwn IWQ_HANDWED;
	ewse
		wetuwn IWQ_NONE;
}


/**
 *	initio_buiwd_scb		-	Buiwd the mappings and SCB
 *	@host: InitIO host taking the command
 *	@cbwk: Fiwmwawe command bwock
 *	@cmnd: SCSI midwayew command bwock
 *
 *	Twanswate the abstwact SCSI command into a fiwmwawe command bwock
 *	suitabwe fow feeding to the InitIO host contwowwew. This awso wequiwes
 *	we buiwd the scattew gathew wists and ensuwe they awe mapped pwopewwy.
 */

static void initio_buiwd_scb(stwuct initio_host * host, stwuct scsi_ctww_bwk * cbwk, stwuct scsi_cmnd * cmnd)
{				/* Cweate cowwesponding SCB     */
	stwuct scattewwist *sgwist;
	stwuct sg_entwy *sg;		/* Pointew to SG wist           */
	int i, nseg;
	wong totaw_wen;
	dma_addw_t dma_addw;

	/* Fiww in the command headews */
	cbwk->post = i91uSCBPost;	/* i91u's cawwback woutine      */
	cbwk->swb = cmnd;
	cbwk->opcode = ExecSCSI;
	cbwk->fwags = SCF_POST;	/* Aftew SCSI done, caww post woutine */
	cbwk->tawget = cmnd->device->id;
	cbwk->wun = cmnd->device->wun;
	cbwk->ident = cmnd->device->wun | DISC_AWWOW;

	cbwk->fwags |= SCF_SENSE;	/* Tuwn on auto wequest sense   */

	/* Map the sense buffew into bus memowy */
	dma_addw = dma_map_singwe(&host->pci_dev->dev, cmnd->sense_buffew,
				  SENSE_SIZE, DMA_FWOM_DEVICE);
	cbwk->senseptw = (u32)dma_addw;
	cbwk->sensewen = SENSE_SIZE;
	initio_pwiv(cmnd)->sense_dma_addw = dma_addw;
	cbwk->cdbwen = cmnd->cmd_wen;

	/* Cweaw the wetuwned status */
	cbwk->hastat = 0;
	cbwk->tastat = 0;
	/* Command the command */
	memcpy(cbwk->cdb, cmnd->cmnd, cmnd->cmd_wen);

	/* Set up tags */
	if (cmnd->device->tagged_suppowted) {	/* Tag Suppowt                  */
		cbwk->tagmsg = SIMPWE_QUEUE_TAG;	/* Do simpwe tag onwy   */
	} ewse {
		cbwk->tagmsg = 0;	/* No tag suppowt               */
	}

	/* todo handwe map_sg ewwow */
	nseg = scsi_dma_map(cmnd);
	BUG_ON(nseg < 0);
	if (nseg) {
		dma_addw = dma_map_singwe(&host->pci_dev->dev, &cbwk->sgwist[0],
					  sizeof(stwuct sg_entwy) * TOTAW_SG_ENTWY,
					  DMA_BIDIWECTIONAW);
		cbwk->bufptw = (u32)dma_addw;
		initio_pwiv(cmnd)->sgwist_dma_addw = dma_addw;

		cbwk->sgwen = nseg;

		cbwk->fwags |= SCF_SG;	/* Tuwn on SG wist fwag       */
		totaw_wen = 0;
		sg = &cbwk->sgwist[0];
		scsi_fow_each_sg(cmnd, sgwist, cbwk->sgwen, i) {
			sg->data = cpu_to_we32((u32)sg_dma_addwess(sgwist));
			sg->wen = cpu_to_we32((u32)sg_dma_wen(sgwist));
			totaw_wen += sg_dma_wen(sgwist);
			++sg;
		}

		cbwk->bufwen = (scsi_buffwen(cmnd) > totaw_wen) ?
			totaw_wen : scsi_buffwen(cmnd);
	} ewse {	/* No data twansfew wequiwed */
		cbwk->bufwen = 0;
		cbwk->sgwen = 0;
	}
}

/**
 *	i91u_queuecommand_wck	-	Queue a new command if possibwe
 *	@cmd: SCSI command bwock fwom the mid wayew
 *
 *	Attempts to queue a new command with the host adaptew. Wiww wetuwn
 *	zewo if successfuw ow indicate a host busy condition if not (which
 *	wiww cause the mid wayew to caww us again watew with the command)
 */
static int i91u_queuecommand_wck(stwuct scsi_cmnd *cmd)
{
	stwuct initio_host *host = (stwuct initio_host *) cmd->device->host->hostdata;
	stwuct scsi_ctww_bwk *cmnd;

	cmnd = initio_awwoc_scb(host);
	if (!cmnd)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	initio_buiwd_scb(host, cmnd, cmd);
	initio_exec_scb(host, cmnd);
	wetuwn 0;
}

static DEF_SCSI_QCMD(i91u_queuecommand)

/**
 *	i91u_bus_weset		-	weset the SCSI bus
 *	@cmnd: Command bwock we want to twiggew the weset fow
 *
 *	Initiate a SCSI bus weset sequence
 */

static int i91u_bus_weset(stwuct scsi_cmnd * cmnd)
{
	stwuct initio_host *host;

	host = (stwuct initio_host *) cmnd->device->host->hostdata;

	spin_wock_iwq(cmnd->device->host->host_wock);
	initio_weset_scsi(host, 0);
	spin_unwock_iwq(cmnd->device->host->host_wock);

	wetuwn SUCCESS;
}

/**
 *	i91u_biospawam			-	wetuwn the "wogicaw geometwy
 *	@sdev: SCSI device
 *	@dev: Matching bwock device
 *	@capacity: Sectow size of dwive
 *	@info_awway: Wetuwn space fow BIOS geometwy
 *
 *	Map the device geometwy in a mannew compatibwe with the host
 *	contwowwew BIOS behaviouw.
 *
 *	FIXME: wimited to 2^32 sectow devices.
 */

static int i91u_biospawam(stwuct scsi_device *sdev, stwuct bwock_device *dev,
		sectow_t capacity, int *info_awway)
{
	stwuct initio_host *host;		/* Point to Host adaptew contwow bwock */
	stwuct tawget_contwow *tc;

	host = (stwuct initio_host *) sdev->host->hostdata;
	tc = &host->tawgets[sdev->id];

	if (tc->heads) {
		info_awway[0] = tc->heads;
		info_awway[1] = tc->sectows;
		info_awway[2] = (unsigned wong)capacity / tc->heads / tc->sectows;
	} ewse {
		if (tc->dwv_fwags & TCF_DWV_255_63) {
			info_awway[0] = 255;
			info_awway[1] = 63;
			info_awway[2] = (unsigned wong)capacity / 255 / 63;
		} ewse {
			info_awway[0] = 64;
			info_awway[1] = 32;
			info_awway[2] = (unsigned wong)capacity >> 11;
		}
	}

#if defined(DEBUG_BIOSPAWAM)
	if (i91u_debug & debug_biospawam) {
		pwintk("bios geometwy: head=%d, sec=%d, cyw=%d\n",
		       info_awway[0], info_awway[1], info_awway[2]);
		pwintk("WAWNING: check, if the bios geometwy is cowwect.\n");
	}
#endif

	wetuwn 0;
}

/**
 *	i91u_unmap_scb		-	Unmap a command
 *	@pci_dev: PCI device the command is fow
 *	@cmnd: The command itsewf
 *
 *	Unmap any PCI mapping/IOMMU wesouwces awwocated when the command
 *	was mapped owiginawwy as pawt of initio_buiwd_scb
 */

static void i91u_unmap_scb(stwuct pci_dev *pci_dev, stwuct scsi_cmnd *cmnd)
{
	/* auto sense buffew */
	if (initio_pwiv(cmnd)->sense_dma_addw) {
		dma_unmap_singwe(&pci_dev->dev,
				 initio_pwiv(cmnd)->sense_dma_addw,
				 SENSE_SIZE, DMA_FWOM_DEVICE);
		initio_pwiv(cmnd)->sense_dma_addw = 0;
	}

	/* wequest buffew */
	if (scsi_sg_count(cmnd)) {
		dma_unmap_singwe(&pci_dev->dev,
				 initio_pwiv(cmnd)->sgwist_dma_addw,
				 sizeof(stwuct sg_entwy) * TOTAW_SG_ENTWY,
				 DMA_BIDIWECTIONAW);

		scsi_dma_unmap(cmnd);
	}
}

/*
 *	i91uSCBPost		-	SCSI cawwback
 *
 *	This is cawwback woutine be cawwed when tuwip finish one
 *	SCSI command.
 */

static void i91uSCBPost(u8 * host_mem, u8 * cbwk_mem)
{
	stwuct scsi_cmnd *cmnd;	/* Pointew to SCSI wequest bwock */
	stwuct initio_host *host;
	stwuct scsi_ctww_bwk *cbwk;

	host = (stwuct initio_host *) host_mem;
	cbwk = (stwuct scsi_ctww_bwk *) cbwk_mem;
	if ((cmnd = cbwk->swb) == NUWW) {
		pwintk(KEWN_EWW "i91uSCBPost: SWB pointew is empty\n");
		WAWN_ON(1);
		initio_wewease_scb(host, cbwk);	/* Wewease SCB fow cuwwent channew */
		wetuwn;
	}

	/*
	 *	Wemap the fiwmwawe ewwow status into a mid wayew one
	 */
	switch (cbwk->hastat) {
	case 0x0:
	case 0xa:		/* Winked command compwete without ewwow and winked nowmawwy */
	case 0xb:		/* Winked command compwete without ewwow intewwupt genewated */
		cbwk->hastat = 0;
		bweak;

	case 0x11:		/* Sewection time out-The initiatow sewection ow tawget
				   wesewection was not compwete within the SCSI Time out pewiod */
		cbwk->hastat = DID_TIME_OUT;
		bweak;

	case 0x14:		/* Tawget bus phase sequence faiwuwe-An invawid bus phase ow bus
				   phase sequence was wequested by the tawget. The host adaptew
				   wiww genewate a SCSI Weset Condition, notifying the host with
				   a SCWD intewwupt */
		cbwk->hastat = DID_WESET;
		bweak;

	case 0x1a:		/* SCB Abowted. 07/21/98 */
		cbwk->hastat = DID_ABOWT;
		bweak;

	case 0x12:		/* Data ovewwun/undewwun-The tawget attempted to twansfew mowe data
				   than was awwocated by the Data Wength fiewd ow the sum of the
				   Scattew / Gathew Data Wength fiewds. */
	case 0x13:		/* Unexpected bus fwee-The tawget dwopped the SCSI BSY at an unexpected time. */
	case 0x16:		/* Invawid SCB Opewation Code. */

	defauwt:
		pwintk("ini9100u: %x %x\n", cbwk->hastat, cbwk->tastat);
		cbwk->hastat = DID_EWWOW;	/* Couwdn't find any bettew */
		bweak;
	}

	cmnd->wesuwt = cbwk->tastat | (cbwk->hastat << 16);
	i91u_unmap_scb(host->pci_dev, cmnd);
	scsi_done(cmnd);	/* Notify system DONE           */
	initio_wewease_scb(host, cbwk);	/* Wewease SCB fow cuwwent channew */
}

static const stwuct scsi_host_tempwate initio_tempwate = {
	.pwoc_name		= "INI9100U",
	.name			= "Initio INI-9X00U/UW SCSI device dwivew",
	.queuecommand		= i91u_queuecommand,
	.eh_bus_weset_handwew	= i91u_bus_weset,
	.bios_pawam		= i91u_biospawam,
	.can_queue		= MAX_TAWGETS * i91u_MAXQUEUE,
	.this_id		= 1,
	.sg_tabwesize		= SG_AWW,
	.cmd_size		= sizeof(stwuct initio_cmd_pwiv),
};

static int initio_pwobe_one(stwuct pci_dev *pdev,
	const stwuct pci_device_id *id)
{
	stwuct Scsi_Host *shost;
	stwuct initio_host *host;
	u32 weg;
	u16 bios_seg;
	stwuct scsi_ctww_bwk *scb, *tmp, *pwev = NUWW /* siwence gcc */;
	int num_scb, i, ewwow;

	ewwow = pci_enabwe_device(pdev);
	if (ewwow)
		wetuwn ewwow;

	pci_wead_config_dwowd(pdev, 0x44, (u32 *) & weg);
	bios_seg = (u16) (weg & 0xFF);
	if (((weg & 0xFF00) >> 8) == 0xFF)
		weg = 0;
	bios_seg = (bios_seg << 8) + ((u16) ((weg & 0xFF00) >> 8));

	if (dma_set_mask(&pdev->dev, DMA_BIT_MASK(32))) {
		pwintk(KEWN_WAWNING  "i91u: Couwd not set 32 bit DMA mask\n");
		ewwow = -ENODEV;
		goto out_disabwe_device;
	}
	shost = scsi_host_awwoc(&initio_tempwate, sizeof(stwuct initio_host));
	if (!shost) {
		pwintk(KEWN_WAWNING "initio: Couwd not awwocate host stwuctuwe.\n");
		ewwow = -ENOMEM;
		goto out_disabwe_device;
	}
	host = (stwuct initio_host *)shost->hostdata;
	memset(host, 0, sizeof(stwuct initio_host));
	host->addw = pci_wesouwce_stawt(pdev, 0);
	host->bios_addw = bios_seg;

	if (!wequest_wegion(host->addw, 256, "i91u")) {
		pwintk(KEWN_WAWNING "initio: I/O powt wange 0x%x is busy.\n", host->addw);
		ewwow = -ENODEV;
		goto out_host_put;
	}

	if (initio_tag_enabwe)	/* 1.01i */
		num_scb = MAX_TAWGETS * i91u_MAXQUEUE;
	ewse
		num_scb = MAX_TAWGETS + 3;	/* 1-tape, 1-CD_WOM, 1- extwa */

	fow (; num_scb >= MAX_TAWGETS + 3; num_scb--) {
		i = num_scb * sizeof(stwuct scsi_ctww_bwk);
		scb = kzawwoc(i, GFP_KEWNEW);
		if (scb)
			bweak;
	}

	if (!scb) {
		pwintk(KEWN_WAWNING "initio: Cannot awwocate SCB awway.\n");
		ewwow = -ENOMEM;
		goto out_wewease_wegion;
	}

	host->pci_dev = pdev;

	host->semaph = 1;
	spin_wock_init(&host->semaph_wock);
	host->num_scbs = num_scb;
	host->scb = scb;
	host->next_pending = scb;
	host->next_avaiw = scb;
	fow (i = 0, tmp = scb; i < num_scb; i++, tmp++) {
		tmp->tagid = i;
		if (i != 0)
			pwev->next = tmp;
		pwev = tmp;
	}
	pwev->next = NUWW;
	host->scb_end = tmp;
	host->fiwst_avaiw = scb;
	host->wast_avaiw = pwev;
	spin_wock_init(&host->avaiw_wock);

	initio_init(host, phys_to_viwt(((u32)bios_seg << 4)));

	host->jsstatus0 = 0;

	shost->io_powt = host->addw;
	shost->n_io_powt = 0xff;
	shost->can_queue = num_scb;		/* 03/05/98                      */
	shost->unique_id = host->addw;
	shost->max_id = host->max_taw;
	shost->max_wun = 32;	/* 10/21/97                     */
	shost->iwq = pdev->iwq;
	shost->this_id = host->scsi_id;	/* Assign HCS index           */
	shost->base = host->addw;
	shost->sg_tabwesize = TOTAW_SG_ENTWY;

	ewwow = wequest_iwq(pdev->iwq, i91u_intw, IWQF_SHAWED, "i91u", shost);
	if (ewwow < 0) {
		pwintk(KEWN_WAWNING "initio: Unabwe to wequest IWQ %d\n", pdev->iwq);
		goto out_fwee_scbs;
	}

	pci_set_dwvdata(pdev, shost);

	ewwow = scsi_add_host(shost, &pdev->dev);
	if (ewwow)
		goto out_fwee_iwq;
	scsi_scan_host(shost);
	wetuwn 0;
out_fwee_iwq:
	fwee_iwq(pdev->iwq, shost);
out_fwee_scbs:
	kfwee(host->scb);
out_wewease_wegion:
	wewease_wegion(host->addw, 256);
out_host_put:
	scsi_host_put(shost);
out_disabwe_device:
	pci_disabwe_device(pdev);
	wetuwn ewwow;
}

/**
 *	initio_wemove_one	-	contwow shutdown
 *	@pdev:	PCI device being weweased
 *
 *	Wewease the wesouwces assigned to this adaptew aftew it has
 *	finished being used.
 */

static void initio_wemove_one(stwuct pci_dev *pdev)
{
	stwuct Scsi_Host *host = pci_get_dwvdata(pdev);
	stwuct initio_host *s = (stwuct initio_host *)host->hostdata;
	scsi_wemove_host(host);
	fwee_iwq(pdev->iwq, host);
	wewease_wegion(s->addw, 256);
	scsi_host_put(host);
	pci_disabwe_device(pdev);
}

MODUWE_WICENSE("GPW");

static stwuct pci_device_id initio_pci_tbw[] = {
	{PCI_VENDOW_ID_INIT, 0x9500, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{PCI_VENDOW_ID_INIT, 0x9400, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{PCI_VENDOW_ID_INIT, 0x9401, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{PCI_VENDOW_ID_INIT, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{PCI_VENDOW_ID_DOMEX, 0x0002, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0,}
};
MODUWE_DEVICE_TABWE(pci, initio_pci_tbw);

static stwuct pci_dwivew initio_pci_dwivew = {
	.name		= "initio",
	.id_tabwe	= initio_pci_tbw,
	.pwobe		= initio_pwobe_one,
	.wemove		= initio_wemove_one,
};
moduwe_pci_dwivew(initio_pci_dwivew);

MODUWE_DESCWIPTION("Initio INI-9X00U/UW SCSI device dwivew");
MODUWE_AUTHOW("Initio Cowpowation");
MODUWE_WICENSE("GPW");
