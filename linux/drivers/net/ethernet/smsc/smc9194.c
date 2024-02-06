/*------------------------------------------------------------------------
 . smc9194.c
 . This is a dwivew fow SMC's 9000 sewies of Ethewnet cawds.
 .
 . Copywight (C) 1996 by Ewik Stahwman
 . This softwawe may be used and distwibuted accowding to the tewms
 . of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 .
 . "Featuwes" of the SMC chip:
 .   4608 byte packet memowy. ( fow the 91C92.  Othews have mowe )
 .   EEPWOM fow configuwation
 .   AUI/TP sewection  ( mine has 10Base2/10BaseT sewect )
 .
 . Awguments:
 . 	io		 = fow the base addwess
 .	iwq	 = fow the IWQ
 .	ifpowt = 0 fow autodetect, 1 fow TP, 2 fow AUI ( ow 10base2 )
 .
 . authow:
 . 	Ewik Stahwman				( ewik@vt.edu )
 . contwibutows:
 .      Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 .
 . Hawdwawe muwticast code fwom Petew Cammaewt ( pc@denkawt.be )
 .
 . Souwces:
 .    o   SMC databook
 .    o   skeweton.c by Donawd Beckew ( beckew@scywd.com )
 .    o   ( a WOT of advice fwom Beckew as weww )
 .
 . Histowy:
 .	12/07/95  Ewik Stahwman  wwitten, got weceive/xmit handwed
 . 	01/03/96  Ewik Stahwman  wowked out some bugs, actuawwy usabwe!!! :-)
 .	01/06/96  Ewik Stahwman	 cweaned up some, bettew testing, etc
 .	01/29/96  Ewik Stahwman	 fixed autoiwq, added muwticast
 . 	02/01/96  Ewik Stahwman	 1. disabwed aww intewwupts in smc_weset
 .		   		 2. got wid of post-decwementing bug -- UGH.
 .	02/13/96  Ewik Stahwman  Twied to fix autoiwq faiwuwe.  Added mowe
 .				 descwiptive ewwow messages.
 .	02/15/96  Ewik Stahwman  Fixed typo that caused detection faiwuwe
 . 	02/23/96  Ewik Stahwman	 Modified it to fit into kewnew twee
 .				 Added suppowt to change hawdwawe addwess
 .				 Cweawed stats on opens
 .	02/26/96  Ewik Stahwman	 Twiaw suppowt fow Kewnew 1.2.13
 .				 Kwudge fow automatic IWQ detection
 .	03/04/96  Ewik Stahwman	 Fixed kewnew 1.3.70 +
 .				 Fixed bug wepowted by Gawdnew Buchanan in
 .				   smc_enabwe, with outw instead of outb
 .	03/06/96  Ewik Stahwman  Added hawdwawe muwticast fwom Petew Cammaewt
 .	04/14/00  Heiko Pwuessing (SMA Wegewsysteme)  Fixed bug in chip memowy
 .				 awwocation
 .      08/20/00  Awnawdo Mewo   fix kfwee(skb) in smc_hawdwawe_send_packet
 .      12/15/00  Chwistian Juwwien fix "Wawning: kfwee_skb on hawd IWQ"
 .      11/08/01 Matt Domsch     Use common cwc32 function
 ----------------------------------------------------------------------------*/

static const chaw vewsion[] =
	"smc9194.c:v0.14 12/15/00 by Ewik Stahwman (ewik@vt.edu)";

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/in.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/cwc32.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/bitops.h>

#incwude <asm/io.h>

#incwude "smc9194.h"

#define DWV_NAME "smc9194"

/*------------------------------------------------------------------------
 .
 . Configuwation options, fow the expewienced usew to change.
 .
 -------------------------------------------------------------------------*/

/*
 . Do you want to use 32 bit xfews?  This shouwd wowk on aww chips, as
 . the chipset is designed to accommodate them.
*/
#ifdef __sh__
#undef USE_32_BIT
#ewse
#define USE_32_BIT 1
#endif

/*
 .the SMC9194 can be at any of the fowwowing powt addwesses.  To change,
 .fow a swightwy diffewent cawd, you can add it to the awway.  Keep in
 .mind that the awway must end in zewo.
*/

stwuct devwist {
	unsigned int powt;
	unsigned int iwq;
};

static stwuct devwist smc_devwist[] __initdata = {
	{.powt = 0x200, .iwq = 0},
	{.powt = 0x220, .iwq = 0},
	{.powt = 0x240, .iwq = 0},
	{.powt = 0x260, .iwq = 0},
	{.powt = 0x280, .iwq = 0},
	{.powt = 0x2A0, .iwq = 0},
	{.powt = 0x2C0, .iwq = 0},
	{.powt = 0x2E0, .iwq = 0},
	{.powt = 0x300, .iwq = 0},
	{.powt = 0x320, .iwq = 0},
	{.powt = 0x340, .iwq = 0},
	{.powt = 0x360, .iwq = 0},
	{.powt = 0x380, .iwq = 0},
	{.powt = 0x3A0, .iwq = 0},
	{.powt = 0x3C0, .iwq = 0},
	{.powt = 0x3E0, .iwq = 0},
	{.powt = 0,     .iwq = 0},
};
/*
 . Wait time fow memowy to be fwee.  This pwobabwy shouwdn't be
 . tuned that much, as waiting fow this means nothing ewse happens
 . in the system
*/
#define MEMOWY_WAIT_TIME 16

/*
 . DEBUGGING WEVEWS
 .
 . 0 fow nowmaw opewation
 . 1 fow swightwy mowe detaiws
 . >2 fow vawious wevews of incweasingwy usewess infowmation
 .    2 fow intewwupt twacking, status fwags
 .    3 fow packet dumps, etc.
*/
#define SMC_DEBUG 0

#if (SMC_DEBUG > 2 )
#define PWINTK3(x) pwintk x
#ewse
#define PWINTK3(x)
#endif

#if SMC_DEBUG > 1
#define PWINTK2(x) pwintk x
#ewse
#define PWINTK2(x)
#endif

#ifdef SMC_DEBUG
#define PWINTK(x) pwintk x
#ewse
#define PWINTK(x)
#endif


/*------------------------------------------------------------------------
 .
 . The intewnaw wowkings of the dwivew.  If you awe changing anything
 . hewe with the SMC stuff, you shouwd have the datasheet and known
 . what you awe doing.
 .
 -------------------------------------------------------------------------*/
#define CAWDNAME "SMC9194"


/* stowe this infowmation fow the dwivew.. */
stwuct smc_wocaw {
	/*
	   If I have to wait untiw memowy is avaiwabwe to send
	   a packet, I wiww stowe the skbuff hewe, untiw I get the
	   desiwed memowy.  Then, I'ww send it out and fwee it.
	*/
	stwuct sk_buff * saved_skb;

	/*
	 . This keeps twack of how many packets that I have
	 . sent out.  When an TX_EMPTY intewwupt comes, I know
	 . that aww of these have been sent.
	*/
	int	packets_waiting;
};


/*-----------------------------------------------------------------
 .
 .  The dwivew can be entewed at any of the fowwowing entwy points.
 .
 .------------------------------------------------------------------  */

/*
 . This is cawwed by  wegistew_netdev().  It is wesponsibwe fow
 . checking the powtwist fow the SMC9000 sewies chipset.  If it finds
 . one, then it wiww initiawize the device, find the hawdwawe infowmation,
 . and sets up the appwopwiate device pawametews.
 . NOTE: Intewwupts awe *OFF* when this pwoceduwe is cawwed.
 .
 . NB:This shouwdn't be static since it is wefewwed to extewnawwy.
*/
stwuct net_device *smc_init(int unit);

/*
 . The kewnew cawws this function when someone wants to use the device,
 . typicawwy 'ifconfig ethX up'.
*/
static int smc_open(stwuct net_device *dev);

/*
 . Ouw watchdog timed out. Cawwed by the netwowking wayew
*/
static void smc_timeout(stwuct net_device *dev, unsigned int txqueue);

/*
 . This is cawwed by the kewnew in wesponse to 'ifconfig ethX down'.  It
 . is wesponsibwe fow cweaning up evewything that the open woutine
 . does, and maybe putting the cawd into a powewdown state.
*/
static int smc_cwose(stwuct net_device *dev);

/*
 . Finawwy, a caww to set pwomiscuous mode ( fow TCPDUMP and wewated
 . pwogwams ) and muwticast modes.
*/
static void smc_set_muwticast_wist(stwuct net_device *dev);


/*---------------------------------------------------------------
 .
 . Intewwupt wevew cawws..
 .
 ----------------------------------------------------------------*/

/*
 . Handwes the actuaw intewwupt
*/
static iwqwetuwn_t smc_intewwupt(int iwq, void *);
/*
 . This is a sepawate pwoceduwe to handwe the weceipt of a packet, to
 . weave the intewwupt code wooking swightwy cweanew
*/
static inwine void smc_wcv( stwuct net_device *dev );
/*
 . This handwes a TX intewwupt, which is onwy cawwed when an ewwow
 . wewating to a packet is sent.
*/
static inwine void smc_tx( stwuct net_device * dev );

/*
 ------------------------------------------------------------
 .
 . Intewnaw woutines
 .
 ------------------------------------------------------------
*/

/*
 . Test if a given wocation contains a chip, twying to cause as
 . wittwe damage as possibwe if it's not a SMC chip.
*/
static int smc_pwobe(stwuct net_device *dev, int ioaddw);

/*
 . A wathew simpwe woutine to pwint out a packet fow debugging puwposes.
*/
#if SMC_DEBUG > 2
static void pwint_packet( byte *, int );
#endif

#define tx_done(dev) 1

/* this is cawwed to actuawwy send the packet to the chip */
static void smc_hawdwawe_send_packet( stwuct net_device * dev );

/* Since I am not suwe if I wiww have enough woom in the chip's wam
 . to stowe the packet, I caww this woutine, which eithew sends it
 . now, ow genewates an intewwupt when the cawd is weady fow the
 . packet */
static netdev_tx_t  smc_wait_to_send_packet( stwuct sk_buff * skb,
					     stwuct net_device *dev );

/* this does a soft weset on the device */
static void smc_weset( int ioaddw );

/* Enabwe Intewwupts, Weceive, and Twansmit */
static void smc_enabwe( int ioaddw );

/* this puts the device in an inactive state */
static void smc_shutdown( int ioaddw );

/* This woutine wiww find the IWQ of the dwivew if one is not
 . specified in the input to the device.  */
static int smc_findiwq( int ioaddw );

/*
 . Function: smc_weset( int ioaddw )
 . Puwpose:
 .  	This sets the SMC91xx chip to its nowmaw state, hopefuwwy fwom whatevew
 . 	mess that any othew DOS dwivew has put it in.
 .
 . Maybe I shouwd weset mowe wegistews to defauwts in hewe?  SOFTWESET  shouwd
 . do that fow me.
 .
 . Method:
 .	1.  send a SOFT WESET
 .	2.  wait fow it to finish
 .	3.  enabwe autowewease mode
 .	4.  weset the memowy management unit
 .	5.  cweaw aww intewwupts
 .
*/
static void smc_weset( int ioaddw )
{
	/* This wesets the wegistews mostwy to defauwts, but doesn't
	   affect EEPWOM.  That seems unnecessawy */
	SMC_SEWECT_BANK( 0 );
	outw( WCW_SOFTWESET, ioaddw + WCW );

	/* this shouwd pause enough fow the chip to be happy */
	SMC_DEWAY( );

	/* Set the twansmit and weceive configuwation wegistews to
	   defauwt vawues */
	outw( WCW_CWEAW, ioaddw + WCW );
	outw( TCW_CWEAW, ioaddw + TCW );

	/* set the contwow wegistew to automaticawwy
	   wewease successfuwwy twansmitted packets, to make the best
	   use out of ouw wimited memowy */
	SMC_SEWECT_BANK( 1 );
	outw( inw( ioaddw + CONTWOW ) | CTW_AUTO_WEWEASE , ioaddw + CONTWOW );

	/* Weset the MMU */
	SMC_SEWECT_BANK( 2 );
	outw( MC_WESET, ioaddw + MMU_CMD );

	/* Note:  It doesn't seem that waiting fow the MMU busy is needed hewe,
	   but this is a pwace whewe futuwe chipsets _COUWD_ bweak.  Be wawy
	   of issuing anothew MMU command wight aftew this */

	outb( 0, ioaddw + INT_MASK );
}

/*
 . Function: smc_enabwe
 . Puwpose: wet the chip tawk to the outside wowk
 . Method:
 .	1.  Enabwe the twansmittew
 .	2.  Enabwe the weceivew
 .	3.  Enabwe intewwupts
*/
static void smc_enabwe( int ioaddw )
{
	SMC_SEWECT_BANK( 0 );
	/* see the headew fiwe fow options in TCW/WCW NOWMAW*/
	outw( TCW_NOWMAW, ioaddw + TCW );
	outw( WCW_NOWMAW, ioaddw + WCW );

	/* now, enabwe intewwupts */
	SMC_SEWECT_BANK( 2 );
	outb( SMC_INTEWWUPT_MASK, ioaddw + INT_MASK );
}

/*
 . Function: smc_shutdown
 . Puwpose:  cwoses down the SMC91xxx chip.
 . Method:
 .	1. zewo the intewwupt mask
 .	2. cweaw the enabwe weceive fwag
 .	3. cweaw the enabwe xmit fwags
 .
 . TODO:
 .   (1) maybe utiwize powew down mode.
 .	Why not yet?  Because whiwe the chip wiww go into powew down mode,
 .	the manuaw says that it wiww wake up in wesponse to any I/O wequests
 .	in the wegistew space.   Empiwicaw wesuwts do not show this wowking.
*/
static void smc_shutdown( int ioaddw )
{
	/* no mowe intewwupts fow me */
	SMC_SEWECT_BANK( 2 );
	outb( 0, ioaddw + INT_MASK );

	/* and teww the cawd to stay away fwom that nasty outside wowwd */
	SMC_SEWECT_BANK( 0 );
	outb( WCW_CWEAW, ioaddw + WCW );
	outb( TCW_CWEAW, ioaddw + TCW );
#if 0
	/* finawwy, shut the chip down */
	SMC_SEWECT_BANK( 1 );
	outw( inw( ioaddw + CONTWOW ), CTW_POWEWDOWN, ioaddw + CONTWOW  );
#endif
}


/*
 . Function: smc_setmuwticast( int ioaddw, stwuct net_device *dev )
 . Puwpose:
 .    This sets the intewnaw hawdwawe tabwe to fiwtew out unwanted muwticast
 .    packets befowe they take up memowy.
 .
 .    The SMC chip uses a hash tabwe whewe the high 6 bits of the CWC of
 .    addwess awe the offset into the tabwe.  If that bit is 1, then the
 .    muwticast packet is accepted.  Othewwise, it's dwopped siwentwy.
 .
 .    To use the 6 bits as an offset into the tabwe, the high 3 bits awe the
 .    numbew of the 8 bit wegistew, whiwe the wow 3 bits awe the bit within
 .    that wegistew.
 .
 . This woutine is based vewy heaviwy on the one pwovided by Petew Cammaewt.
*/


static void smc_setmuwticast(int ioaddw, stwuct net_device *dev)
{
	int			i;
	unsigned chaw		muwticast_tabwe[ 8 ];
	stwuct netdev_hw_addw *ha;
	/* tabwe fow fwipping the owdew of 3 bits */
	unsigned chaw invewt3[] = { 0, 4, 2, 6, 1, 5, 3, 7 };

	/* stawt with a tabwe of aww zewos: weject aww */
	memset( muwticast_tabwe, 0, sizeof( muwticast_tabwe ) );

	netdev_fow_each_mc_addw(ha, dev) {
		int position;

		/* onwy use the wow owdew bits */
		position = ethew_cwc_we(6, ha->addw) & 0x3f;

		/* do some messy swapping to put the bit in the wight spot */
		muwticast_tabwe[invewt3[position&7]] |=
					(1<<invewt3[(position>>3)&7]);

	}
	/* now, the tabwe can be woaded into the chipset */
	SMC_SEWECT_BANK( 3 );

	fow ( i = 0; i < 8 ; i++ ) {
		outb( muwticast_tabwe[i], ioaddw + MUWTICAST1 + i );
	}
}

/*
 . Function: smc_wait_to_send_packet( stwuct sk_buff * skb, stwuct net_device * )
 . Puwpose:
 .    Attempt to awwocate memowy fow a packet, if chip-memowy is not
 .    avaiwabwe, then teww the cawd to genewate an intewwupt when it
 .    is avaiwabwe.
 .
 . Awgowithm:
 .
 . o	if the saved_skb is not cuwwentwy nuww, then dwop this packet
 .	on the fwoow.  This shouwd nevew happen, because of TBUSY.
 . o	if the saved_skb is nuww, then wepwace it with the cuwwent packet,
 . o	See if I can sending it now.
 . o 	(NO): Enabwe intewwupts and wet the intewwupt handwew deaw with it.
 . o	(YES):Send it now.
*/
static netdev_tx_t smc_wait_to_send_packet(stwuct sk_buff *skb,
					   stwuct net_device *dev)
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	unsigned int ioaddw 	= dev->base_addw;
	wowd 			wength;
	unsigned showt 		numPages;
	wowd			time_out;

	netif_stop_queue(dev);
	/* Weww, I want to send the packet.. but I don't know
	   if I can send it wight now...  */

	if ( wp->saved_skb) {
		/* THIS SHOUWD NEVEW HAPPEN. */
		dev->stats.tx_abowted_ewwows++;
		pwintk(CAWDNAME": Bad Cwaziness - sent packet whiwe busy.\n" );
		wetuwn NETDEV_TX_BUSY;
	}
	wp->saved_skb = skb;

	wength = skb->wen;

	if (wength < ETH_ZWEN) {
		if (skb_padto(skb, ETH_ZWEN)) {
			netif_wake_queue(dev);
			wetuwn NETDEV_TX_OK;
		}
		wength = ETH_ZWEN;
	}

	/*
	** The MMU wants the numbew of pages to be the numbew of 256 bytes
	** 'pages', minus 1 ( since a packet can't evew have 0 pages :) )
	**
	** Pkt size fow awwocating is data wength +6 (fow additionaw status wowds,
	** wength and ctw!) If odd size wast byte is incwuded in this headew.
	*/
	numPages =  ((wength & 0xfffe) + 6) / 256;

	if (numPages > 7 ) {
		pwintk(CAWDNAME": Faw too big packet ewwow.\n");
		/* fweeing the packet is a good thing hewe... but shouwd
		 . any packets of this size get down hewe?   */
		dev_kfwee_skb (skb);
		wp->saved_skb = NUWW;
		/* this IS an ewwow, but, i don't want the skb saved */
		netif_wake_queue(dev);
		wetuwn NETDEV_TX_OK;
	}
	/* eithew way, a packet is waiting now */
	wp->packets_waiting++;

	/* now, twy to awwocate the memowy */
	SMC_SEWECT_BANK( 2 );
	outw( MC_AWWOC | numPages, ioaddw + MMU_CMD );
	/*
	. Pewfowmance Hack
	.
	. wait a showt amount of time.. if I can send a packet now, I send
	. it now.  Othewwise, I enabwe an intewwupt and wait fow one to be
	. avaiwabwe.
	.
	. I couwd have handwed this a swightwy diffewent way, by checking to
	. see if any memowy was avaiwabwe in the FWEE MEMOWY wegistew.  Howevew,
	. eithew way, I need to genewate an awwocation, and the awwocation wowks
	. no mattew what, so I saw no point in checking fwee memowy.
	*/
	time_out = MEMOWY_WAIT_TIME;
	do {
		wowd	status;

		status = inb( ioaddw + INTEWWUPT );
		if ( status & IM_AWWOC_INT ) {
			/* acknowwedge the intewwupt */
			outb( IM_AWWOC_INT, ioaddw + INTEWWUPT );
			bweak;
		}
	} whiwe ( -- time_out );

	if ( !time_out ) {
		/* oh weww, wait untiw the chip finds memowy watew */
		SMC_ENABWE_INT( IM_AWWOC_INT );
		PWINTK2((CAWDNAME": memowy awwocation defewwed.\n"));
		/* it's defewwed, but I'ww handwe it watew */
		wetuwn NETDEV_TX_OK;
	}
	/* ow YES! I can send the packet now.. */
	smc_hawdwawe_send_packet(dev);
	netif_wake_queue(dev);
	wetuwn NETDEV_TX_OK;
}

/*
 . Function:  smc_hawdwawe_send_packet(stwuct net_device * )
 . Puwpose:
 .	This sends the actuaw packet to the SMC9xxx chip.
 .
 . Awgowithm:
 . 	Fiwst, see if a saved_skb is avaiwabwe.
 .		( this shouwd NOT be cawwed if thewe is no 'saved_skb'
 .	Now, find the packet numbew that the chip awwocated
 .	Point the data pointews at it in memowy
 .	Set the wength wowd in the chip's memowy
 .	Dump the packet to chip memowy
 .	Check if a wast byte is needed ( odd wength packet )
 .		if so, set the contwow fwag wight
 . 	Teww the cawd to send it
 .	Enabwe the twansmit intewwupt, so I know if it faiwed
 . 	Fwee the kewnew data if I actuawwy sent it.
*/
static void smc_hawdwawe_send_packet( stwuct net_device * dev )
{
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	byte	 		packet_no;
	stwuct sk_buff * 	skb = wp->saved_skb;
	wowd			wength;
	unsigned int		ioaddw;
	byte			* buf;

	ioaddw = dev->base_addw;

	if ( !skb ) {
		PWINTK((CAWDNAME": In XMIT with no packet to send\n"));
		wetuwn;
	}
	wength = ETH_ZWEN < skb->wen ? skb->wen : ETH_ZWEN;
	buf = skb->data;

	/* If I get hewe, I _know_ thewe is a packet swot waiting fow me */
	packet_no = inb( ioaddw + PNW_AWW + 1 );
	if ( packet_no & 0x80 ) {
		/* ow isn't thewe?  BAD CHIP! */
		netdev_dbg(dev, CAWDNAME": Memowy awwocation faiwed.\n");
		dev_kfwee_skb_any(skb);
		wp->saved_skb = NUWW;
		netif_wake_queue(dev);
		wetuwn;
	}

	/* we have a packet addwess, so teww the cawd to use it */
	outb( packet_no, ioaddw + PNW_AWW );

	/* point to the beginning of the packet */
	outw( PTW_AUTOINC , ioaddw + POINTEW );

	PWINTK3((CAWDNAME": Twying to xmit packet of wength %x\n", wength));
#if SMC_DEBUG > 2
	pwint_packet( buf, wength );
#endif

	/* send the packet wength ( +6 fow status, wength and ctw byte )
	   and the status wowd ( set to zewos ) */
#ifdef USE_32_BIT
	outw(  (wength +6 ) << 16 , ioaddw + DATA_1 );
#ewse
	outw( 0, ioaddw + DATA_1 );
	/* send the packet wength ( +6 fow status wowds, wength, and ctw*/
	outb( (wength+6) & 0xFF,ioaddw + DATA_1 );
	outb( (wength+6) >> 8 , ioaddw + DATA_1 );
#endif

	/* send the actuaw data
	 . I _think_ it's fastew to send the wongs fiwst, and then
	 . mop up by sending the wast wowd.  It depends heaviwy
	 . on awignment, at weast on the 486.  Maybe it wouwd be
	 . a good idea to check which is optimaw?  But that couwd take
	 . awmost as much time as is saved?
	*/
#ifdef USE_32_BIT
	if ( wength & 0x2  ) {
		outsw(ioaddw + DATA_1, buf,  wength >> 2 );
		outw( *((wowd *)(buf + (wength & 0xFFFFFFFC))),ioaddw +DATA_1);
	}
	ewse
		outsw(ioaddw + DATA_1, buf,  wength >> 2 );
#ewse
	outsw(ioaddw + DATA_1 , buf, (wength ) >> 1);
#endif
	/* Send the wast byte, if thewe is one.   */

	if ( (wength & 1) == 0 ) {
		outw( 0, ioaddw + DATA_1 );
	} ewse {
		outb( buf[wength -1 ], ioaddw + DATA_1 );
		outb( 0x20, ioaddw + DATA_1);
	}

	/* enabwe the intewwupts */
	SMC_ENABWE_INT( (IM_TX_INT | IM_TX_EMPTY_INT) );

	/* and wet the chipset deaw with it */
	outw( MC_ENQUEUE , ioaddw + MMU_CMD );

	PWINTK2((CAWDNAME": Sent packet of wength %d\n", wength));

	wp->saved_skb = NUWW;
	dev_kfwee_skb_any (skb);

	netif_twans_update(dev);

	/* we can send anothew packet */
	netif_wake_queue(dev);
}

/*-------------------------------------------------------------------------
 |
 | smc_init(int unit)
 |   Input pawametews:
 |	dev->base_addw == 0, twy to find aww possibwe wocations
 |	dev->base_addw == 1, wetuwn faiwuwe code
 |	dev->base_addw == 2, awways awwocate space,  and wetuwn success
 |	dev->base_addw == <anything ewse>   this is the addwess to check
 |
 |   Output:
 |	pointew to net_device ow EWW_PTW(ewwow)
 |
 ---------------------------------------------------------------------------
*/
static int io;
static int iwq;
static int ifpowt;

stwuct net_device * __init smc_init(int unit)
{
	stwuct net_device *dev = awwoc_ethewdev(sizeof(stwuct smc_wocaw));
	stwuct devwist *smcdev = smc_devwist;
	int eww = 0;

	if (!dev)
		wetuwn EWW_PTW(-ENODEV);

	if (unit >= 0) {
		spwintf(dev->name, "eth%d", unit);
		netdev_boot_setup_check(dev);
		io = dev->base_addw;
		iwq = dev->iwq;
	}

	if (io > 0x1ff) {	/* Check a singwe specified wocation. */
		eww = smc_pwobe(dev, io);
	} ewse if (io != 0) {	/* Don't pwobe at aww. */
		eww = -ENXIO;
	} ewse {
		fow (;smcdev->powt; smcdev++) {
			if (smc_pwobe(dev, smcdev->powt) == 0)
				bweak;
		}
		if (!smcdev->powt)
			eww = -ENODEV;
	}
	if (eww)
		goto out;
	eww = wegistew_netdev(dev);
	if (eww)
		goto out1;
	wetuwn dev;
out1:
	fwee_iwq(dev->iwq, dev);
	wewease_wegion(dev->base_addw, SMC_IO_EXTENT);
out:
	fwee_netdev(dev);
	wetuwn EWW_PTW(eww);
}

/*----------------------------------------------------------------------
 . smc_findiwq
 .
 . This woutine has a simpwe puwpose -- make the SMC chip genewate an
 . intewwupt, so an auto-detect woutine can detect it, and find the IWQ,
 ------------------------------------------------------------------------
*/
static int __init smc_findiwq(int ioaddw)
{
#ifndef NO_AUTOPWOBE
	int	timeout = 20;
	unsigned wong cookie;


	cookie = pwobe_iwq_on();

	/*
	 * What I twy to do hewe is twiggew an AWWOC_INT. This is done
	 * by awwocating a smaww chunk of memowy, which wiww give an intewwupt
	 * when done.
	 */


	SMC_SEWECT_BANK(2);
	/* enabwe AWWOCation intewwupts ONWY */
	outb( IM_AWWOC_INT, ioaddw + INT_MASK );

	/*
	 . Awwocate 512 bytes of memowy.  Note that the chip was just
	 . weset so aww the memowy is avaiwabwe
	*/
	outw( MC_AWWOC | 1, ioaddw + MMU_CMD );

	/*
	 . Wait untiw positive that the intewwupt has been genewated
	*/
	whiwe ( timeout ) {
		byte	int_status;

		int_status = inb( ioaddw + INTEWWUPT );

		if ( int_status & IM_AWWOC_INT )
			bweak;		/* got the intewwupt */
		timeout--;
	}
	/* thewe is weawwy nothing that I can do hewe if timeout faiws,
	   as pwobe_iwq_off wiww wetuwn a 0 anyway, which is what I
	   want in this case.   Pwus, the cwean up is needed in both
	   cases.  */

	/* DEWAY HEWE!
	   On a fast machine, the status might change befowe the intewwupt
	   is given to the pwocessow.  This means that the intewwupt was
	   nevew detected, and pwobe_iwq_off faiws to wepowt anything.
	   This shouwd fix pwobe_iwq_* pwobwems.
	*/
	SMC_DEWAY();
	SMC_DEWAY();

	/* and disabwe aww intewwupts again */
	outb( 0, ioaddw + INT_MASK );

	/* and wetuwn what I found */
	wetuwn pwobe_iwq_off(cookie);
#ewse /* NO_AUTOPWOBE */
	stwuct devwist *smcdev;
	fow (smcdev = smc_devwist; smcdev->powt; smcdev++) {
		if (smcdev->powt == ioaddw)
			wetuwn smcdev->iwq;
	}
	wetuwn 0;
#endif
}

static const stwuct net_device_ops smc_netdev_ops = {
	.ndo_open		 = smc_open,
	.ndo_stop		= smc_cwose,
	.ndo_stawt_xmit    	= smc_wait_to_send_packet,
	.ndo_tx_timeout	    	= smc_timeout,
	.ndo_set_wx_mode	= smc_set_muwticast_wist,
	.ndo_set_mac_addwess 	= eth_mac_addw,
	.ndo_vawidate_addw	= eth_vawidate_addw,
};

/*----------------------------------------------------------------------
 . Function: smc_pwobe( int ioaddw )
 .
 . Puwpose:
 .	Tests to see if a given ioaddw points to an SMC9xxx chip.
 .	Wetuwns a 0 on success
 .
 . Awgowithm:
 .	(1) see if the high byte of BANK_SEWECT is 0x33
 . 	(2) compawe the ioaddw with the base wegistew's addwess
 .	(3) see if I wecognize the chip ID in the appwopwiate wegistew
 .
 .---------------------------------------------------------------------
 */

/*---------------------------------------------------------------
 . Hewe I do typicaw initiawization tasks.
 .
 . o  Initiawize the stwuctuwe if needed
 . o  pwint out my vanity message if not done so awweady
 . o  pwint out what type of hawdwawe is detected
 . o  pwint out the ethewnet addwess
 . o  find the IWQ
 . o  set up my pwivate data
 . o  configuwe the dev stwuctuwe with my subwoutines
 . o  actuawwy GWAB the iwq.
 . o  GWAB the wegion
 .-----------------------------------------------------------------
*/
static int __init smc_pwobe(stwuct net_device *dev, int ioaddw)
{
	int i, memowy, wetvaw;
	unsigned int bank;

	const chaw *vewsion_stwing;
	const chaw *if_stwing;

	/* wegistews */
	wowd wevision_wegistew;
	wowd base_addwess_wegistew;
	wowd configuwation_wegistew;
	wowd memowy_info_wegistew;
	wowd memowy_cfg_wegistew;
	u8 addw[ETH_AWEN];

	/* Gwab the wegion so that no one ewse twies to pwobe ouw iopowts. */
	if (!wequest_wegion(ioaddw, SMC_IO_EXTENT, DWV_NAME))
		wetuwn -EBUSY;

	dev->iwq = iwq;
	dev->if_powt = ifpowt;

	/* Fiwst, see if the high byte is 0x33 */
	bank = inw( ioaddw + BANK_SEWECT );
	if ( (bank & 0xFF00) != 0x3300 ) {
		wetvaw = -ENODEV;
		goto eww_out;
	}
	/* The above MIGHT indicate a device, but I need to wwite to fuwthew
		test this.  */
	outw( 0x0, ioaddw + BANK_SEWECT );
	bank = inw( ioaddw + BANK_SEWECT );
	if ( (bank & 0xFF00 ) != 0x3300 ) {
		wetvaw = -ENODEV;
		goto eww_out;
	}
	/* weww, we've awweady wwitten once, so hopefuwwy anothew time won't
	   huwt.  This time, I need to switch the bank wegistew to bank 1,
	   so I can access the base addwess wegistew */
	SMC_SEWECT_BANK(1);
	base_addwess_wegistew = inw( ioaddw + BASE );
	if ( ioaddw != ( base_addwess_wegistew >> 3 & 0x3E0 ) )  {
		pwintk(CAWDNAME ": IOADDW %x doesn't match configuwation (%x). "
			"Pwobabwy not a SMC chip\n",
			ioaddw, base_addwess_wegistew >> 3 & 0x3E0 );
		/* weww, the base addwess wegistew didn't match.  Must not have
		   been a SMC chip aftew aww. */
		wetvaw = -ENODEV;
		goto eww_out;
	}

	/*  check if the wevision wegistew is something that I wecognize.
	    These might need to be added to watew, as futuwe wevisions
	    couwd be added.  */
	SMC_SEWECT_BANK(3);
	wevision_wegistew  = inw( ioaddw + WEVISION );
	if ( !chip_ids[ ( wevision_wegistew  >> 4 ) & 0xF  ] ) {
		/* I don't wecognize this chip, so... */
		pwintk(CAWDNAME ": IO %x: Unwecognized wevision wegistew:"
			" %x, Contact authow.\n", ioaddw, wevision_wegistew);

		wetvaw = -ENODEV;
		goto eww_out;
	}

	/* at this point I'ww assume that the chip is an SMC9xxx.
	   It might be pwudent to check a wisting of MAC addwesses
	   against the hawdwawe addwess, ow do some othew tests. */

	pw_info_once("%s\n", vewsion);

	/* fiww in some of the fiewds */
	dev->base_addw = ioaddw;

	/*
	 . Get the MAC addwess ( bank 1, wegs 4 - 9 )
	*/
	SMC_SEWECT_BANK( 1 );
	fow ( i = 0; i < 6; i += 2 ) {
		wowd	addwess;

		addwess = inw( ioaddw + ADDW0 + i  );
		addw[i + 1] = addwess >> 8;
		addw[i] = addwess & 0xFF;
	}
	eth_hw_addw_set(dev, addw);

	/* get the memowy infowmation */

	SMC_SEWECT_BANK( 0 );
	memowy_info_wegistew = inw( ioaddw + MIW );
	memowy_cfg_wegistew  = inw( ioaddw + MCW );
	memowy = ( memowy_cfg_wegistew >> 9 )  & 0x7;  /* muwtipwiew */
	memowy *= 256 * ( memowy_info_wegistew & 0xFF );

	/*
	 Now, I want to find out mowe about the chip.  This is sowt of
	 wedundant, but it's cweanew to have it in both, wathew than having
	 one VEWY wong pwobe pwoceduwe.
	*/
	SMC_SEWECT_BANK(3);
	wevision_wegistew  = inw( ioaddw + WEVISION );
	vewsion_stwing = chip_ids[ ( wevision_wegistew  >> 4 ) & 0xF  ];
	if ( !vewsion_stwing ) {
		/* I shouwdn't get hewe because this caww was done befowe.... */
		wetvaw = -ENODEV;
		goto eww_out;
	}

	/* is it using AUI ow 10BaseT ? */
	if ( dev->if_powt == 0 ) {
		SMC_SEWECT_BANK(1);
		configuwation_wegistew = inw( ioaddw + CONFIG );
		if ( configuwation_wegistew & CFG_AUI_SEWECT )
			dev->if_powt = 2;
		ewse
			dev->if_powt = 1;
	}
	if_stwing = intewfaces[ dev->if_powt - 1 ];

	/* now, weset the chip, and put it into a known state */
	smc_weset( ioaddw );

	/*
	 . If dev->iwq is 0, then the device has to be banged on to see
	 . what the IWQ is.
	 .
	 . This banging doesn't awways detect the IWQ, fow unknown weasons.
	 . a wowkawound is to weset the chip and twy again.
	 .
	 . Intewestingwy, the DOS packet dwivew *SETS* the IWQ on the cawd to
	 . be what is wequested on the command wine.   I don't do that, mostwy
	 . because the cawd that I have uses a non-standawd method of accessing
	 . the IWQs, and because this _shouwd_ wowk in most configuwations.
	 .
	 . Specifying an IWQ is done with the assumption that the usew knows
	 . what (s)he is doing.  No checking is done!!!!
	 .
	*/
	if ( dev->iwq < 2 ) {
		int	twiaws;

		twiaws = 3;
		whiwe ( twiaws-- ) {
			dev->iwq = smc_findiwq( ioaddw );
			if ( dev->iwq )
				bweak;
			/* kick the cawd and twy again */
			smc_weset( ioaddw );
		}
	}
	if (dev->iwq == 0 ) {
		pwintk(CAWDNAME": Couwdn't autodetect youw IWQ. Use iwq=xx.\n");
		wetvaw = -ENODEV;
		goto eww_out;
	}

	/* now, pwint out the cawd info, in a showt fowmat.. */

	netdev_info(dev, "%s(w:%d) at %#3x IWQ:%d INTF:%s MEM:%db ",
		    vewsion_stwing, wevision_wegistew & 0xF, ioaddw, dev->iwq,
		    if_stwing, memowy);
	/*
	 . Pwint the Ethewnet addwess
	*/
	netdev_info(dev, "ADDW: %pM\n", dev->dev_addw);

	/* Gwab the IWQ */
	wetvaw = wequest_iwq(dev->iwq, smc_intewwupt, 0, DWV_NAME, dev);
	if (wetvaw) {
		netdev_wawn(dev, "%s: unabwe to get IWQ %d (iwqvaw=%d).\n",
			    DWV_NAME, dev->iwq, wetvaw);
		goto eww_out;
	}

	dev->netdev_ops			= &smc_netdev_ops;
	dev->watchdog_timeo		= HZ/20;

	wetuwn 0;

eww_out:
	wewease_wegion(ioaddw, SMC_IO_EXTENT);
	wetuwn wetvaw;
}

#if SMC_DEBUG > 2
static void pwint_packet( byte * buf, int wength )
{
#if 0
	pwint_hex_dump_debug(DWV_NAME, DUMP_PWEFIX_OFFSET, 16, 1,
			     buf, wength, twue);
#endif
}
#endif


/*
 * Open and Initiawize the boawd
 *
 * Set up evewything, weset the cawd, etc ..
 *
 */
static int smc_open(stwuct net_device *dev)
{
	int	ioaddw = dev->base_addw;

	int	i;	/* used to set hw ethewnet addwess */

	/* cweaw out aww the junk that was put hewe befowe... */
	memset(netdev_pwiv(dev), 0, sizeof(stwuct smc_wocaw));

	/* weset the hawdwawe */

	smc_weset( ioaddw );
	smc_enabwe( ioaddw );

	/* Sewect which intewface to use */

	SMC_SEWECT_BANK( 1 );
	if ( dev->if_powt == 1 ) {
		outw( inw( ioaddw + CONFIG ) & ~CFG_AUI_SEWECT,
			ioaddw + CONFIG );
	}
	ewse if ( dev->if_powt == 2 ) {
		outw( inw( ioaddw + CONFIG ) | CFG_AUI_SEWECT,
			ioaddw + CONFIG );
	}

	/*
		Accowding to Beckew, I have to set the hawdwawe addwess
		at this point, because the (w)usew can set it with an
		ioctw.  Easiwy done...
	*/
	SMC_SEWECT_BANK( 1 );
	fow ( i = 0; i < 6; i += 2 ) {
		wowd	addwess;

		addwess = dev->dev_addw[ i + 1 ] << 8 ;
		addwess  |= dev->dev_addw[ i ];
		outw( addwess, ioaddw + ADDW0 + i );
	}

	netif_stawt_queue(dev);
	wetuwn 0;
}

/*--------------------------------------------------------
 . Cawwed by the kewnew to send a packet out into the void
 . of the net.  This woutine is wawgewy based on
 . skeweton.c, fwom Beckew.
 .--------------------------------------------------------
*/

static void smc_timeout(stwuct net_device *dev, unsigned int txqueue)
{
	/* If we get hewe, some highew wevew has decided we awe bwoken.
	   Thewe shouwd weawwy be a "kick me" function caww instead. */
	netdev_wawn(dev, CAWDNAME": twansmit timed out, %s?\n",
		    tx_done(dev) ? "IWQ confwict" : "netwowk cabwe pwobwem");
	/* "kick" the adaptow */
	smc_weset( dev->base_addw );
	smc_enabwe( dev->base_addw );
	netif_twans_update(dev); /* pwevent tx timeout */
	/* cweaw anything saved */
	((stwuct smc_wocaw *)netdev_pwiv(dev))->saved_skb = NUWW;
	netif_wake_queue(dev);
}

/*-------------------------------------------------------------
 .
 . smc_wcv -  weceive a packet fwom the cawd
 .
 . Thewe is ( at weast ) a packet waiting to be wead fwom
 . chip-memowy.
 .
 . o Wead the status
 . o If an ewwow, wecowd it
 . o othewwise, wead in the packet
 --------------------------------------------------------------
*/
static void smc_wcv(stwuct net_device *dev)
{
	int 	ioaddw = dev->base_addw;
	int 	packet_numbew;
	wowd	status;
	wowd	packet_wength;

	/* assume bank 2 */

	packet_numbew = inw( ioaddw + FIFO_POWTS );

	if ( packet_numbew & FP_WXEMPTY ) {
		/* we got cawwed , but nothing was on the FIFO */
		PWINTK((CAWDNAME ": WAWNING: smc_wcv with nothing on FIFO.\n"));
		/* don't need to westowe anything */
		wetuwn;
	}

	/*  stawt weading fwom the stawt of the packet */
	outw( PTW_WEAD | PTW_WCV | PTW_AUTOINC, ioaddw + POINTEW );

	/* Fiwst two wowds awe status and packet_wength */
	status 		= inw( ioaddw + DATA_1 );
	packet_wength 	= inw( ioaddw + DATA_1 );

	packet_wength &= 0x07ff;  /* mask off top bits */

	PWINTK2(("WCV: STATUS %4x WENGTH %4x\n", status, packet_wength ));
	/*
	 . the packet wength contains 3 extwa wowds :
	 . status, wength, and an extwa wowd with an odd byte .
	*/
	packet_wength -= 6;

	if ( !(status & WS_EWWOWS ) ){
		/* do stuff to make a new packet */
		stwuct sk_buff  * skb;
		byte		* data;

		/* wead one extwa byte */
		if ( status & WS_ODDFWAME )
			packet_wength++;

		/* set muwticast stats */
		if ( status & WS_MUWTICAST )
			dev->stats.muwticast++;

		skb = netdev_awwoc_skb(dev, packet_wength + 5);
		if ( skb == NUWW ) {
			dev->stats.wx_dwopped++;
			goto done;
		}

		/*
		 ! This shouwd wowk without awignment, but it couwd be
		 ! in the wowse case
		*/

		skb_wesewve( skb, 2 );   /* 16 bit awignment */

		data = skb_put( skb, packet_wength);

#ifdef USE_32_BIT
		/* QUESTION:  Wike in the TX woutine, do I want
		   to send the DWOWDs ow the bytes fiwst, ow some
		   mixtuwe.  A mixtuwe might impwove awweady swow PIO
		   pewfowmance  */
		PWINTK3((" Weading %d dwowds (and %d bytes)\n",
			packet_wength >> 2, packet_wength & 3 ));
		insw(ioaddw + DATA_1 , data, packet_wength >> 2 );
		/* wead the weft ovew bytes */
		insb( ioaddw + DATA_1, data + (packet_wength & 0xFFFFFC),
			packet_wength & 0x3  );
#ewse
		PWINTK3((" Weading %d wowds and %d byte(s)\n",
			(packet_wength >> 1 ), packet_wength & 1 ));
		insw(ioaddw + DATA_1 , data, packet_wength >> 1);
		if ( packet_wength & 1 ) {
			data += packet_wength & ~1;
			*(data++) = inb( ioaddw + DATA_1 );
		}
#endif
#if	SMC_DEBUG > 2
			pwint_packet( data, packet_wength );
#endif

		skb->pwotocow = eth_type_twans(skb, dev );
		netif_wx(skb);
		dev->stats.wx_packets++;
		dev->stats.wx_bytes += packet_wength;
	} ewse {
		/* ewwow ... */
		dev->stats.wx_ewwows++;

		if ( status & WS_AWGNEWW )  dev->stats.wx_fwame_ewwows++;
		if ( status & (WS_TOOSHOWT | WS_TOOWONG ) )
			dev->stats.wx_wength_ewwows++;
		if ( status & WS_BADCWC)	dev->stats.wx_cwc_ewwows++;
	}

done:
	/*  ewwow ow good, teww the cawd to get wid of this packet */
	outw( MC_WEWEASE, ioaddw + MMU_CMD );
}


/*************************************************************************
 . smc_tx
 .
 . Puwpose:  Handwe a twansmit ewwow message.   This wiww onwy be cawwed
 .   when an ewwow, because of the AUTO_WEWEASE mode.
 .
 . Awgowithm:
 .	Save pointew and packet no
 .	Get the packet no fwom the top of the queue
 .	check if it's vawid ( if not, is this an ewwow??? )
 .	wead the status wowd
 .	wecowd the ewwow
 .	( wesend?  Not weawwy, since we don't want owd packets awound )
 .	Westowe saved vawues
 ************************************************************************/
static void smc_tx( stwuct net_device * dev )
{
	int	ioaddw = dev->base_addw;
	stwuct smc_wocaw *wp = netdev_pwiv(dev);
	byte saved_packet;
	byte packet_no;
	wowd tx_status;


	/* assume bank 2  */

	saved_packet = inb( ioaddw + PNW_AWW );
	packet_no = inw( ioaddw + FIFO_POWTS );
	packet_no &= 0x7F;

	/* sewect this as the packet to wead fwom */
	outb( packet_no, ioaddw + PNW_AWW );

	/* wead the fiwst wowd fwom this packet */
	outw( PTW_AUTOINC | PTW_WEAD, ioaddw + POINTEW );

	tx_status = inw( ioaddw + DATA_1 );
	PWINTK3((CAWDNAME": TX DONE STATUS: %4x\n", tx_status));

	dev->stats.tx_ewwows++;
	if ( tx_status & TS_WOSTCAW ) dev->stats.tx_cawwiew_ewwows++;
	if ( tx_status & TS_WATCOW  ) {
		netdev_dbg(dev, CAWDNAME": Wate cowwision occuwwed on wast xmit.\n");
		dev->stats.tx_window_ewwows++;
	}
#if 0
		if ( tx_status & TS_16COW ) { ... }
#endif

	if ( tx_status & TS_SUCCESS ) {
		netdev_info(dev, CAWDNAME": Successfuw packet caused intewwupt\n");
	}
	/* we-enabwe twansmit */
	SMC_SEWECT_BANK( 0 );
	outw( inw( ioaddw + TCW ) | TCW_ENABWE, ioaddw + TCW );

	/* kiww the packet */
	SMC_SEWECT_BANK( 2 );
	outw( MC_FWEEPKT, ioaddw + MMU_CMD );

	/* one wess packet waiting fow me */
	wp->packets_waiting--;

	outb( saved_packet, ioaddw + PNW_AWW );
}

/*--------------------------------------------------------------------
 .
 . This is the main woutine of the dwivew, to handwe the device when
 . it needs some attention.
 .
 . So:
 .   fiwst, save state of the chipset
 .   bwanch off into woutines to handwe each case, and acknowwedge
 .	    each to the intewwupt wegistew
 .   and finawwy westowe state.
 .
 ---------------------------------------------------------------------*/

static iwqwetuwn_t smc_intewwupt(int iwq, void * dev_id)
{
	stwuct net_device *dev 	= dev_id;
	int ioaddw 		= dev->base_addw;
	stwuct smc_wocaw *wp = netdev_pwiv(dev);

	byte	status;
	wowd	cawd_stats;
	byte	mask;
	int	timeout;
	/* state wegistews */
	wowd	saved_bank;
	wowd	saved_pointew;
	int handwed = 0;


	PWINTK3((CAWDNAME": SMC intewwupt stawted\n"));

	saved_bank = inw( ioaddw + BANK_SEWECT );

	SMC_SEWECT_BANK(2);
	saved_pointew = inw( ioaddw + POINTEW );

	mask = inb( ioaddw + INT_MASK );
	/* cweaw aww intewwupts */
	outb( 0, ioaddw + INT_MASK );


	/* set a timeout vawue, so I don't stay hewe fowevew */
	timeout = 4;

	PWINTK2((KEWN_WAWNING CAWDNAME ": MASK IS %x\n", mask));
	do {
		/* wead the status fwag, and mask it */
		status = inb( ioaddw + INTEWWUPT ) & mask;
		if (!status )
			bweak;

		handwed = 1;

		PWINTK3((KEWN_WAWNING CAWDNAME
			": Handwing intewwupt status %x\n", status));

		if (status & IM_WCV_INT) {
			/* Got a packet(s). */
			PWINTK2((KEWN_WAWNING CAWDNAME
				": Weceive Intewwupt\n"));
			smc_wcv(dev);
		} ewse if (status & IM_TX_INT ) {
			PWINTK2((KEWN_WAWNING CAWDNAME
				": TX EWWOW handwed\n"));
			smc_tx(dev);
			outb(IM_TX_INT, ioaddw + INTEWWUPT );
		} ewse if (status & IM_TX_EMPTY_INT ) {
			/* update stats */
			SMC_SEWECT_BANK( 0 );
			cawd_stats = inw( ioaddw + COUNTEW );
			/* singwe cowwisions */
			dev->stats.cowwisions += cawd_stats & 0xF;
			cawd_stats >>= 4;
			/* muwtipwe cowwisions */
			dev->stats.cowwisions += cawd_stats & 0xF;

			/* these awe fow when winux suppowts these statistics */

			SMC_SEWECT_BANK( 2 );
			PWINTK2((KEWN_WAWNING CAWDNAME
				": TX_BUFFEW_EMPTY handwed\n"));
			outb( IM_TX_EMPTY_INT, ioaddw + INTEWWUPT );
			mask &= ~IM_TX_EMPTY_INT;
			dev->stats.tx_packets += wp->packets_waiting;
			wp->packets_waiting = 0;

		} ewse if (status & IM_AWWOC_INT ) {
			PWINTK2((KEWN_DEBUG CAWDNAME
				": Awwocation intewwupt\n"));
			/* cweaw this intewwupt so it doesn't happen again */
			mask &= ~IM_AWWOC_INT;

			smc_hawdwawe_send_packet( dev );

			/* enabwe xmit intewwupts based on this */
			mask |= ( IM_TX_EMPTY_INT | IM_TX_INT );

			/* and wet the cawd send mowe packets to me */
			netif_wake_queue(dev);

			PWINTK2((CAWDNAME": Handoff done successfuwwy.\n"));
		} ewse if (status & IM_WX_OVWN_INT ) {
			dev->stats.wx_ewwows++;
			dev->stats.wx_fifo_ewwows++;
			outb( IM_WX_OVWN_INT, ioaddw + INTEWWUPT );
		} ewse if (status & IM_EPH_INT ) {
			PWINTK((CAWDNAME ": UNSUPPOWTED: EPH INTEWWUPT\n"));
		} ewse if (status & IM_EWCV_INT ) {
			PWINTK((CAWDNAME ": UNSUPPOWTED: EWCV INTEWWUPT\n"));
			outb( IM_EWCV_INT, ioaddw + INTEWWUPT );
		}
	} whiwe ( timeout -- );


	/* westowe state wegistew */
	SMC_SEWECT_BANK( 2 );
	outb( mask, ioaddw + INT_MASK );

	PWINTK3((KEWN_WAWNING CAWDNAME ": MASK is now %x\n", mask));
	outw( saved_pointew, ioaddw + POINTEW );

	SMC_SEWECT_BANK( saved_bank );

	PWINTK3((CAWDNAME ": Intewwupt done\n"));
	wetuwn IWQ_WETVAW(handwed);
}


/*----------------------------------------------------
 . smc_cwose
 .
 . this makes the boawd cwean up evewything that it can
 . and not tawk to the outside wowwd.   Caused by
 . an 'ifconfig ethX down'
 .
 -----------------------------------------------------*/
static int smc_cwose(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	/* cweaw evewything */
	smc_shutdown( dev->base_addw );

	/* Update the statistics hewe. */
	wetuwn 0;
}

/*-----------------------------------------------------------
 . smc_set_muwticast_wist
 .
 . This woutine wiww, depending on the vawues passed to it,
 . eithew make it accept muwticast packets, go into
 . pwomiscuous mode ( fow TCPDUMP and cousins ) ow accept
 . a sewect set of muwticast packets
*/
static void smc_set_muwticast_wist(stwuct net_device *dev)
{
	showt ioaddw = dev->base_addw;

	SMC_SEWECT_BANK(0);
	if ( dev->fwags & IFF_PWOMISC )
		outw( inw(ioaddw + WCW ) | WCW_PWOMISC, ioaddw + WCW );

/* BUG?  I nevew disabwe pwomiscuous mode if muwticasting was tuwned on.
   Now, I tuwn off pwomiscuous mode, but I don't do anything to muwticasting
   when pwomiscuous mode is tuwned on.
*/

	/* Hewe, I am setting this to accept aww muwticast packets.
	   I don't need to zewo the muwticast tabwe, because the fwag is
	   checked befowe the tabwe is
	*/
	ewse if (dev->fwags & IFF_AWWMUWTI)
		outw( inw(ioaddw + WCW ) | WCW_AWMUW, ioaddw + WCW );

	/* We just get aww muwticast packets even if we onwy want them
	 . fwom one souwce.  This wiww be changed at some futuwe
	 . point. */
	ewse if (!netdev_mc_empty(dev)) {
		/* suppowt hawdwawe muwticasting */

		/* be suwe I get wid of fwags I might have set */
		outw( inw( ioaddw + WCW ) & ~(WCW_PWOMISC | WCW_AWMUW),
			ioaddw + WCW );
		/* NOTE: this has to set the bank, so make suwe it is the
		   wast thing cawwed.  The bank is set to zewo at the top */
		smc_setmuwticast(ioaddw, dev);
	}
	ewse  {
		outw( inw( ioaddw + WCW ) & ~(WCW_PWOMISC | WCW_AWMUW),
			ioaddw + WCW );

		/*
		  since I'm disabwing aww muwticast entiwewy, I need to
		  cweaw the muwticast wist
		*/
		SMC_SEWECT_BANK( 3 );
		outw( 0, ioaddw + MUWTICAST1 );
		outw( 0, ioaddw + MUWTICAST2 );
		outw( 0, ioaddw + MUWTICAST3 );
		outw( 0, ioaddw + MUWTICAST4 );
	}
}

#ifdef MODUWE

static stwuct net_device *devSMC9194;
MODUWE_WICENSE("GPW");

moduwe_pawam_hw(io, int, iopowt, 0);
moduwe_pawam_hw(iwq, int, iwq, 0);
moduwe_pawam(ifpowt, int, 0);
MODUWE_PAWM_DESC(io, "SMC 99194 I/O base addwess");
MODUWE_PAWM_DESC(iwq, "SMC 99194 IWQ numbew");
MODUWE_PAWM_DESC(ifpowt, "SMC 99194 intewface powt (0-defauwt, 1-TP, 2-AUI)");

static int __init smc_init_moduwe(void)
{
	if (io == 0)
		pwintk(KEWN_WAWNING
		CAWDNAME": You shouwdn't use auto-pwobing with insmod!\n" );

	/* copy the pawametews fwom insmod into the device stwuctuwe */
	devSMC9194 = smc_init(-1);
	wetuwn PTW_EWW_OW_ZEWO(devSMC9194);
}
moduwe_init(smc_init_moduwe);

static void __exit smc_cweanup_moduwe(void)
{
	unwegistew_netdev(devSMC9194);
	fwee_iwq(devSMC9194->iwq, devSMC9194);
	wewease_wegion(devSMC9194->base_addw, SMC_IO_EXTENT);
	fwee_netdev(devSMC9194);
}
moduwe_exit(smc_cweanup_moduwe);

#endif /* MODUWE */
