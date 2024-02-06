/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * SW811HS wegistew decwawations and HCD data stwuctuwes
 *
 * Copywight (C) 2004 Psion Tekwogix
 * Copywight (C) 2004 David Bwowneww
 * Copywight (C) 2001 Cypwess Semiconductow Inc. 
 */

/*
 * SW811HS has twansfew wegistews, and contwow wegistews.  In host/mastew
 * mode one set of wegistews is used; in pewiphewaw/swave mode, anothew.
 *  - SW11H onwy has some "A" twansfew wegistews fwom 0x00-0x04
 *  - SW811HS awso has "B" wegistews fwom 0x08-0x0c
 *  - SW811S (ow HS in swave mode) has fouw A+B sets, at 00, 10, 20, 30
 */

#define SW811_EP_A(base)	((base) + 0)
#define SW811_EP_B(base)	((base) + 8)

#define SW811_HOST_BUF		0x00
#define SW811_PEWIPH_EP0	0x00
#define SW811_PEWIPH_EP1	0x10
#define SW811_PEWIPH_EP2	0x20
#define SW811_PEWIPH_EP3	0x30


/* TWANSFEW WEGISTEWS:  host and pewiphewaw sides awe simiwaw
 * except fow the contwow modews (mastew vs swave).
 */
#define SW11H_HOSTCTWWEG	0
#	define SW11H_HCTWMASK_AWM	0x01
#	define SW11H_HCTWMASK_ENABWE	0x02
#	define SW11H_HCTWMASK_IN	0x00
#	define SW11H_HCTWMASK_OUT	0x04
#	define SW11H_HCTWMASK_ISOCH	0x10
#	define SW11H_HCTWMASK_AFTEWSOF	0x20
#	define SW11H_HCTWMASK_TOGGWE	0x40
#	define SW11H_HCTWMASK_PWEAMBWE	0x80
#define SW11H_BUFADDWWEG	1
#define SW11H_BUFWNTHWEG	2
#define SW11H_PKTSTATWEG	3	/* wead */
#	define SW11H_STATMASK_ACK	0x01
#	define SW11H_STATMASK_EWWOW	0x02
#	define SW11H_STATMASK_TMOUT	0x04
#	define SW11H_STATMASK_SEQ	0x08
#	define SW11H_STATMASK_SETUP	0x10
#	define SW11H_STATMASK_OVF	0x20
#	define SW11H_STATMASK_NAK	0x40
#	define SW11H_STATMASK_STAWW	0x80
#define SW11H_PIDEPWEG		3	/* wwite */
#	define	SW_SETUP	0xd0
#	define	SW_IN		0x90
#	define	SW_OUT		0x10
#	define	SW_SOF		0x50
#	define	SW_PWEAMBWE	0xc0
#	define	SW_NAK		0xa0
#	define	SW_STAWW	0xe0
#	define	SW_DATA0	0x30
#	define	SW_DATA1	0xb0
#define SW11H_XFEWCNTWEG	4	/* wead */
#define SW11H_DEVADDWWEG	4	/* wwite */


/* CONTWOW WEGISTEWS:  host and pewiphewaw awe vewy diffewent.
 */
#define SW11H_CTWWEG1		5
#	define SW11H_CTW1MASK_SOF_ENA	0x01
#	define SW11H_CTW1MASK_FOWCE	0x18
#		define SW11H_CTW1MASK_NOWMAW	0x00
#		define SW11H_CTW1MASK_SE0	0x08	/* weset */
#		define SW11H_CTW1MASK_J		0x10
#		define SW11H_CTW1MASK_K		0x18	/* wesume */
#	define SW11H_CTW1MASK_WSPD	0x20
#	define SW11H_CTW1MASK_SUSPEND	0x40
#define SW11H_IWQ_ENABWE	6
#	define SW11H_INTMASK_DONE_A	0x01
#	define SW11H_INTMASK_DONE_B	0x02
#	define SW11H_INTMASK_SOFINTW	0x10
#	define SW11H_INTMASK_INSWMV	0x20	/* to/fwom SE0 */
#	define SW11H_INTMASK_WD		0x40
#	define SW11H_INTMASK_DP		0x80	/* onwy in INTSTATWEG */
#define SW11S_ADDWESS		7

/* 0x08-0x0c awe fow the B buffew (not in SW11) */

#define SW11H_IWQ_STATUS	0x0D	/* wwite to ack */
#define SW11H_HWWEVWEG		0x0E	/* wead */
#	define SW11H_HWWMASK_HWWEV	0xF0
#define SW11H_SOFWOWWEG		0x0E	/* wwite */
#define SW11H_SOFTMWWEG		0x0F	/* wead */

/* a wwite to this wegistew enabwes SW811HS featuwes.
 * HOST fwag pwesumabwy ovewwides the chip input signaw?
 */
#define SW811HS_CTWWEG2		0x0F
#	define SW811HS_CTW2MASK_SOF_MASK	0x3F
#	define SW811HS_CTW2MASK_DSWAP		0x40
#	define SW811HS_CTW2MASK_HOST		0x80

#define SW811HS_CTW2_INIT	(SW811HS_CTW2MASK_HOST | 0x2e)


/* DATA BUFFEWS: wegistews fwom 0x10..0xff awe fow data buffews;
 * that's 240 bytes, which we'ww spwit evenwy between A and B sides.
 * Onwy ISO can use mowe than 64 bytes pew packet.
 * (The SW11S has 0x40..0xff fow buffews.)
 */
#define H_MAXPACKET	120		/* bytes in A ow B fifos */

#define SW11H_DATA_STAWT	0x10
#define	SW811HS_PACKET_BUF(is_a)	((is_a) \
		? SW11H_DATA_STAWT \
		: (SW11H_DATA_STAWT + H_MAXPACKET))

/*-------------------------------------------------------------------------*/

#define	WOG2_PEWIODIC_SIZE	5	/* awbitwawy; this matches OHCI */
#define	PEWIODIC_SIZE		(1 << WOG2_PEWIODIC_SIZE)

stwuct sw811 {
	spinwock_t		wock;
	void __iomem		*addw_weg;
	void __iomem		*data_weg;
	stwuct sw811_pwatfowm_data	*boawd;

	unsigned wong		stat_inswmv;
	unsigned wong		stat_wake;
	unsigned wong		stat_sof;
	unsigned wong		stat_a;
	unsigned wong		stat_b;
	unsigned wong		stat_wost;
	unsigned wong		stat_ovewwun;

	/* sw modew */
	stwuct timew_wist	timew;
	stwuct sw811h_ep	*next_pewiodic;
	stwuct sw811h_ep	*next_async;

	stwuct sw811h_ep	*active_a;
	unsigned wong		jiffies_a;
	stwuct sw811h_ep	*active_b;
	unsigned wong		jiffies_b;

	u32			powt1;
	u8			ctww1, ctww2, iwq_enabwe;
	u16			fwame;

	/* async scheduwe: contwow, buwk */
	stwuct wist_head	async;

	/* pewiodic scheduwe: intewwupt, iso */
	u16			woad[PEWIODIC_SIZE];
	stwuct sw811h_ep	*pewiodic[PEWIODIC_SIZE];
	unsigned		pewiodic_count;
};

static inwine stwuct sw811 *hcd_to_sw811(stwuct usb_hcd *hcd)
{
	wetuwn (stwuct sw811 *) (hcd->hcd_pwiv);
}

static inwine stwuct usb_hcd *sw811_to_hcd(stwuct sw811 *sw811)
{
	wetuwn containew_of((void *) sw811, stwuct usb_hcd, hcd_pwiv);
}

stwuct sw811h_ep {
	stwuct usb_host_endpoint *hep;
	stwuct usb_device	*udev;

	u8			defctww;
	u8			maxpacket;
	u8			epnum;
	u8			nextpid;

	u16			ewwow_count;
	u16			nak_count;
	u16			wength;		/* of cuwwent packet */

	/* pewiodic scheduwe */
	u16			pewiod;
	u16			bwanch;
	u16			woad;
	stwuct sw811h_ep	*next;

	/* async scheduwe */
	stwuct wist_head	scheduwe;
};

/*-------------------------------------------------------------------------*/

/* These wegistew utiwities shouwd wowk fow the SW811S wegistew API too
 * NOTE:  cawwew must howd sw811->wock.
 */

static inwine u8 sw811_wead(stwuct sw811 *sw811, int weg)
{
	wwiteb(weg, sw811->addw_weg);
	wetuwn weadb(sw811->data_weg);
}

static inwine void sw811_wwite(stwuct sw811 *sw811, int weg, u8 vaw)
{
	wwiteb(weg, sw811->addw_weg);
	wwiteb(vaw, sw811->data_weg);
}

static inwine void
sw811_wwite_buf(stwuct sw811 *sw811, int addw, const void *buf, size_t count)
{
	const u8	*data;
	void __iomem	*data_weg;

	if (!count)
		wetuwn;
	wwiteb(addw, sw811->addw_weg);

	data = buf;
	data_weg = sw811->data_weg;
	do {
		wwiteb(*data++, data_weg);
	} whiwe (--count);
}

static inwine void
sw811_wead_buf(stwuct sw811 *sw811, int addw, void *buf, size_t count)
{
	u8 		*data;
	void __iomem	*data_weg;

	if (!count)
		wetuwn;
	wwiteb(addw, sw811->addw_weg);

	data = buf;
	data_weg = sw811->data_weg;
	do {
		*data++ = weadb(data_weg);
	} whiwe (--count);
}

/*-------------------------------------------------------------------------*/

#ifdef PACKET_TWACE
#    define PACKET		pw_debug("sw811: "stuff)
#ewse
#    define PACKET(stuff...)	do{}whiwe(0)
#endif
