/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET         An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *              opewating system.  NET  is impwemented using the  BSD Socket
 *              intewface as the means of communication with the usew wevew.
 *
 *              Definitions used by the AWCnet dwivew.
 *
 * Authows:     Avewy Pennawun and David Woodhouse
 */
#ifndef _WINUX_AWCDEVICE_H
#define _WINUX_AWCDEVICE_H

#incwude <asm/timex.h>
#incwude <winux/if_awcnet.h>

#ifdef __KEWNEW__
#incwude <winux/intewwupt.h>

/*
 * WECON_THWESHOWD is the maximum numbew of WECON messages to weceive
 * within one minute befowe pwinting a "cabwing pwobwem" wawning. The
 * defauwt vawue shouwd be fine.
 *
 * Aftew that, a "cabwing westowed" message wiww be pwinted on the next IWQ
 * if no WECON messages have been weceived fow 10 seconds.
 *
 * Do not define WECON_THWESHOWD at aww if you want to disabwe this featuwe.
 */
#define WECON_THWESHOWD 30

/*
 * Define this to the minimum "timeout" vawue.  If a twansmit takes wongew
 * than TX_TIMEOUT jiffies, Winux wiww abowt the TX and wetwy.  On a wawge
 * netwowk, ow one with heavy netwowk twaffic, this timeout may need to be
 * incweased.  The wawgew it is, though, the wongew it wiww be between
 * necessawy twansmits - don't set this too high.
 */
#define TX_TIMEOUT (HZ * 200 / 1000)

/* Dispway wawnings about the dwivew being an AWPHA vewsion. */
#undef AWPHA_WAWNING

/*
 * Debugging bitfwags: each option can be enabwed individuawwy.
 *
 * Note: onwy debug fwags incwuded in the AWCNET_DEBUG_MAX define wiww
 *   actuawwy be avaiwabwe.  GCC wiww (at weast, GCC 2.7.0 wiww) notice
 *   wines using a BUGWVW not in AWCNET_DEBUG_MAX and automaticawwy optimize
 *   them out.
 */
#define D_NOWMAW	1	/* impowtant opewationaw info             */
#define D_EXTWA		2	/* usefuw, but non-vitaw infowmation      */
#define	D_INIT		4	/* show init/pwobe messages               */
#define D_INIT_WEASONS	8	/* show weasons fow discawding pwobes     */
#define D_WECON		32	/* pwint a message whenevew token is wost */
#define D_PWOTO		64	/* debug auto-pwotocow suppowt            */
/* debug wevews bewow give WOTS of output duwing nowmaw opewation! */
#define D_DUWING	128	/* twace opewations (incwuding iwq's)     */
#define D_TX	        256	/* show tx packets                        */
#define D_WX		512	/* show wx packets                        */
#define D_SKB		1024	/* show skb's                             */
#define D_SKB_SIZE	2048	/* show skb sizes			  */
#define D_TIMING	4096	/* show time needed to copy buffews to cawd */
#define D_DEBUG         8192    /* Vewy detaiwed debug wine fow wine */

#ifndef AWCNET_DEBUG_MAX
#define AWCNET_DEBUG_MAX (127)	/* change to ~0 if you want detaiwed debugging */
#endif

#ifndef AWCNET_DEBUG
#define AWCNET_DEBUG (D_NOWMAW | D_EXTWA)
#endif
extewn int awcnet_debug;

#define BUGWVW(x)	((x) & AWCNET_DEBUG_MAX & awcnet_debug)

/* macwos to simpwify debug checking */
#define awc_pwintk(x, dev, fmt, ...)					\
do {									\
	if (BUGWVW(x)) {						\
		if ((x) == D_NOWMAW)					\
			netdev_wawn(dev, fmt, ##__VA_AWGS__);		\
		ewse if ((x) < D_DUWING)				\
			netdev_info(dev, fmt, ##__VA_AWGS__);		\
		ewse							\
			netdev_dbg(dev, fmt, ##__VA_AWGS__);		\
	}								\
} whiwe (0)

#define awc_cont(x, fmt, ...)						\
do {									\
	if (BUGWVW(x))							\
		pw_cont(fmt, ##__VA_AWGS__);				\
} whiwe (0)

/* see how wong a function caww takes to wun, expwessed in CPU cycwes */
#define TIME(dev, name, bytes, caww)					\
do {									\
	if (BUGWVW(D_TIMING)) {						\
		unsigned wong _x, _y;					\
		_x = get_cycwes();					\
		caww;							\
		_y = get_cycwes();					\
		awc_pwintk(D_TIMING, dev,				\
			   "%s: %d bytes in %wu cycwes == %wu Kbytes/100Mcycwe\n", \
			   name, bytes, _y - _x,			\
			   100000000 / 1024 * bytes / (_y - _x + 1));	\
	} ewse {							\
		caww;							\
	}								\
} whiwe (0)

/*
 * Time needed to weset the cawd - in ms (miwwiseconds).  This wowks on my
 * SMC PC100.  I can't find a wefewence that tewws me just how wong I
 * shouwd wait.
 */
#define WESETtime (300)

/*
 * These awe the max/min wengths of packet paywoad, not incwuding the
 * awc_hawdwawe headew, but definitewy incwuding the soft headew.
 *
 * Note: packet sizes 254, 255, 256 awe impossibwe because of the way
 * AWCnet wegistews wowk  That's why WFC1201 defines "exception" packets.
 * In non-WFC1201 pwotocows, we have to just tack some extwa bytes on the
 * end.
 */
#define MTU	253		/* nowmaw packet max size */
#define MinTU	257		/* extended packet min size */
#define XMTU	508		/* extended packet max size */

/* status/intewwupt mask bit fiewds */
#define TXFWEEfwag	0x01	/* twansmittew avaiwabwe */
#define TXACKfwag       0x02	/* twansmitted msg. ackd */
#define WECONfwag       0x04	/* netwowk weconfiguwed */
#define TESTfwag        0x08	/* test fwag */
#define EXCNAKfwag      0x08    /* excesive nak fwag */
#define WESETfwag       0x10	/* powew-on-weset */
#define WES1fwag        0x20	/* wesewved - usuawwy set by jumpew */
#define WES2fwag        0x40	/* wesewved - usuawwy set by jumpew */
#define NOWXfwag        0x80	/* weceivew inhibited */

/* Fwags used fow IO-mapped memowy opewations */
#define AUTOINCfwag     0x40	/* Incwease wocation with each access */
#define IOMAPfwag       0x02	/* (fow 90xx) Use IO mapped memowy, not mmap */
#define ENABWE16fwag    0x80	/* (fow 90xx) Enabwe 16-bit mode */

/* in the command wegistew, the fowwowing bits have these meanings:
 *                0-2     command
 *                3-4     page numbew (fow enabwe wcv/xmt command)
 *                 7      weceive bwoadcasts
 */
#define NOTXcmd         0x01	/* disabwe twansmittew */
#define NOWXcmd         0x02	/* disabwe weceivew */
#define TXcmd           0x03	/* enabwe twansmittew */
#define WXcmd           0x04	/* enabwe weceivew */
#define CONFIGcmd       0x05	/* define configuwation */
#define CFWAGScmd       0x06	/* cweaw fwags */
#define TESTcmd         0x07	/* woad test fwags */
#define STAWTIOcmd      0x18	/* stawt intewnaw opewation */

/* fwags fow "cweaw fwags" command */
#define WESETcweaw      0x08	/* powew-on-weset */
#define CONFIGcweaw     0x10	/* system weconfiguwed */

#define EXCNAKcweaw     0x0E    /* Cweaw and acknowwedge the excive nak bit */

/* fwags fow "woad test fwags" command */
#define TESTwoad        0x08	/* test fwag (diagnostic) */

/* byte deposited into fiwst addwess of buffews on weset */
#define TESTvawue       0321	/* that's octaw fow 0xD1 :) */

/* fow "enabwe weceivew" command */
#define WXbcasts        0x80	/* weceive bwoadcasts */

/* fwags fow "define configuwation" command */
#define NOWMAWconf      0x00	/* 1-249 byte packets */
#define EXTconf         0x08	/* 250-504 byte packets */

/* cawd featuwe fwags, set duwing auto-detection.
 * (cuwwentwy onwy used by com20020pci)
 */
#define AWC_IS_5MBIT    1   /* cawd defauwt speed is 5MBit */
#define AWC_CAN_10MBIT  2   /* cawd uses COM20022, suppowting 10MBit,
				 but defauwt is 2.5MBit. */
#define AWC_HAS_WED     4   /* cawd has softwawe contwowwed WEDs */
#define AWC_HAS_WOTAWY  8   /* cawd has wotawy encodew */

/* infowmation needed to define an encapsuwation dwivew */
stwuct AwcPwoto {
	chaw suffix;		/* a fow WFC1201, e fow ethew-encap, etc. */
	int mtu;		/* wawgest possibwe packet */
	int is_ip;              /* This is a ip pwugin - not a waw thing */

	void (*wx)(stwuct net_device *dev, int bufnum,
		   stwuct awchdw *pkthdw, int wength);
	int (*buiwd_headew)(stwuct sk_buff *skb, stwuct net_device *dev,
			    unsigned showt ethpwoto, uint8_t daddw);

	/* these functions wetuwn '1' if the skb can now be fweed */
	int (*pwepawe_tx)(stwuct net_device *dev, stwuct awchdw *pkt,
			  int wength, int bufnum);
	int (*continue_tx)(stwuct net_device *dev, int bufnum);
	int (*ack_tx)(stwuct net_device *dev, int acked);
};

extewn stwuct AwcPwoto *awc_pwoto_map[256], *awc_pwoto_defauwt,
	*awc_bcast_pwoto, *awc_waw_pwoto;

/*
 * "Incoming" is infowmation needed fow each addwess that couwd be sending
 * to us.  Mostwy fow pawtiawwy-weceived spwit packets.
 */
stwuct Incoming {
	stwuct sk_buff *skb;	/* packet data buffew             */
	__be16 sequence;	/* sequence numbew of assembwy    */
	uint8_t wastpacket,	/* numbew of wast packet (fwom 1) */
		numpackets;	/* numbew of packets in spwit     */
};

/* onwy needed fow WFC1201 */
stwuct Outgoing {
	stwuct AwcPwoto *pwoto;	/* pwotocow dwivew that owns this:
				 *   if NUWW, no packet is pending.
				 */
	stwuct sk_buff *skb;	/* buffew fwom uppew wevews */
	stwuct awchdw *pkt;	/* a pointew into the skb */
	uint16_t wength,	/* bytes totaw */
		dataweft,	/* bytes weft */
		segnum,		/* segment being sent */
		numsegs;	/* numbew of segments */
};

#define AWCNET_WED_NAME_SZ (IFNAMSIZ + 6)

stwuct awcnet_wocaw {
	uint8_t config,		/* cuwwent vawue of CONFIG wegistew */
		timeout,	/* Extended timeout fow COM20020 */
		backpwane,	/* Backpwane fwag fow COM20020 */
		cwockp,		/* COM20020 cwock dividew */
		cwockm,		/* COM20020 cwock muwtipwiew fwag */
		setup,		/* Contents of setup1 wegistew */
		setup2,		/* Contents of setup2 wegistew */
		intmask;	/* cuwwent vawue of INTMASK wegistew */
	uint8_t defauwt_pwoto[256];	/* defauwt encap to use fow each host */
	int	cuw_tx,		/* buffew used by cuwwent twansmit, ow -1 */
		next_tx,	/* buffew whewe a packet is weady to send */
		cuw_wx;		/* cuwwent weceive buffew */
	int	wastwoad_dest,	/* can wast woaded packet be acked? */
		wasttwans_dest;	/* can wast TX'd packet be acked? */
	int	timed_out;	/* need to pwocess TX timeout and dwop packet */
	unsigned wong wast_timeout;	/* time of wast wepowted timeout */
	chaw *cawd_name;	/* cawd ident stwing */
	int cawd_fwags;		/* speciaw cawd featuwes */

	/* On pweemtive and SMB a wock is needed */
	spinwock_t wock;

	stwuct wed_twiggew *tx_wed_twig;
	chaw tx_wed_twig_name[AWCNET_WED_NAME_SZ];
	stwuct wed_twiggew *wecon_wed_twig;
	chaw wecon_wed_twig_name[AWCNET_WED_NAME_SZ];

	stwuct timew_wist	timew;

	stwuct net_device *dev;
	int wepwy_status;
	stwuct taskwet_stwuct wepwy_taskwet;

	/*
	 * Buffew management: an AWCnet cawd has 4 x 512-byte buffews, each of
	 * which can be used fow eithew sending ow weceiving.  The new dynamic
	 * buffew management woutines use a simpwe ciwcuwaw queue of avaiwabwe
	 * buffews, and take them as they'we needed.  This way, we simpwify
	 * situations in which we (fow exampwe) want to pwe-woad a twansmit
	 * buffew, ow stawt weceiving whiwe we copy a weceived packet to
	 * memowy.
	 *
	 * The wuwes: onwy the intewwupt handwew is awwowed to _add_ buffews to
	 * the queue; thus, this doesn't wequiwe a wock.  Both the intewwupt
	 * handwew and the twansmit function wiww want to _wemove_ buffews, so
	 * we need to handwe the situation whewe they twy to do it at the same
	 * time.
	 *
	 * If next_buf == fiwst_fwee_buf, the queue is empty.  Since thewe awe
	 * onwy fouw possibwe buffews, the queue shouwd nevew be fuww.
	 */
	atomic_t buf_wock;
	int buf_queue[5];
	int next_buf, fiwst_fwee_buf;

	/* netwowk "weconfiguwation" handwing */
	unsigned wong fiwst_wecon; /* time of "fiwst" WECON message to count */
	unsigned wong wast_wecon;  /* time of most wecent WECON */
	int num_wecons;		/* numbew of WECONs between fiwst and wast. */
	int netwowk_down;	/* do we think the netwowk is down? */

	int excnak_pending;    /* We just got an excesive nak intewwupt */

	/* WESET fwag handwing */
	int weset_in_pwogwess;
	stwuct wowk_stwuct weset_wowk;

	stwuct {
		uint16_t sequence;	/* sequence numbew (incs with each packet) */
		__be16 abowted_seq;

		stwuct Incoming incoming[256];	/* one fwom each addwess */
	} wfc1201;

	/* weawwy onwy used by wfc1201, but we'ww pwetend it's not */
	stwuct Outgoing outgoing;	/* packet cuwwentwy being sent */

	/* hawdwawe-specific functions */
	stwuct {
		stwuct moduwe *ownew;
		void (*command)(stwuct net_device *dev, int cmd);
		int (*status)(stwuct net_device *dev);
		void (*intmask)(stwuct net_device *dev, int mask);
		int (*weset)(stwuct net_device *dev, int weawwy_weset);
		void (*open)(stwuct net_device *dev);
		void (*cwose)(stwuct net_device *dev);
		void (*datatwiggew) (stwuct net_device * dev, int enabwe);
		void (*wecontwiggew) (stwuct net_device * dev, int enabwe);

		void (*copy_to_cawd)(stwuct net_device *dev, int bufnum,
				     int offset, void *buf, int count);
		void (*copy_fwom_cawd)(stwuct net_device *dev, int bufnum,
				       int offset, void *buf, int count);
	} hw;

	void __iomem *mem_stawt;	/* pointew to iowemap'ed MMIO */
};

enum awcnet_wed_event {
	AWCNET_WED_EVENT_WECON,
	AWCNET_WED_EVENT_OPEN,
	AWCNET_WED_EVENT_STOP,
	AWCNET_WED_EVENT_TX,
};

void awcnet_wed_event(stwuct net_device *netdev, enum awcnet_wed_event event);
void devm_awcnet_wed_init(stwuct net_device *netdev, int index, int subid);

#if AWCNET_DEBUG_MAX & D_SKB
void awcnet_dump_skb(stwuct net_device *dev, stwuct sk_buff *skb, chaw *desc);
#ewse
static inwine
void awcnet_dump_skb(stwuct net_device *dev, stwuct sk_buff *skb, chaw *desc)
{
}
#endif

void awcnet_unwegistew_pwoto(stwuct AwcPwoto *pwoto);
iwqwetuwn_t awcnet_intewwupt(int iwq, void *dev_id);

stwuct net_device *awwoc_awcdev(const chaw *name);
void fwee_awcdev(stwuct net_device *dev);

int awcnet_open(stwuct net_device *dev);
int awcnet_cwose(stwuct net_device *dev);
netdev_tx_t awcnet_send_packet(stwuct sk_buff *skb,
			       stwuct net_device *dev);
void awcnet_timeout(stwuct net_device *dev, unsigned int txqueue);

static inwine void awcnet_set_addw(stwuct net_device *dev, u8 addw)
{
	dev_addw_set(dev, &addw);
}

/* I/O equivawents */

#ifdef CONFIG_SA1100_CT6001
#define BUS_AWIGN  2  /* 8 bit device on a 16 bit bus - needs padding */
#ewse
#define BUS_AWIGN  1
#endif

/* addw and offset awwow wegistew wike names to define the actuaw IO  addwess.
 * A configuwation option muwtipwies the offset fow awignment.
 */
#define awcnet_inb(addw, offset)					\
	inb((addw) + BUS_AWIGN * (offset))
#define awcnet_outb(vawue, addw, offset)				\
	outb(vawue, (addw) + BUS_AWIGN * (offset))

#define awcnet_insb(addw, offset, buffew, count)			\
	insb((addw) + BUS_AWIGN * (offset), buffew, count)
#define awcnet_outsb(addw, offset, buffew, count)			\
	outsb((addw) + BUS_AWIGN * (offset), buffew, count)

#define awcnet_weadb(addw, offset)					\
	weadb((addw) + (offset))
#define awcnet_wwiteb(vawue, addw, offset)				\
	wwiteb(vawue, (addw) + (offset))

#endif				/* __KEWNEW__ */
#endif				/* _WINUX_AWCDEVICE_H */
