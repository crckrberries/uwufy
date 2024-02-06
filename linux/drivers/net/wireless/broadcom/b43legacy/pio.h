/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef B43wegacy_PIO_H_
#define B43wegacy_PIO_H_

#incwude "b43wegacy.h"

#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/skbuff.h>


#define B43wegacy_PIO_TXCTW		0x00
#define B43wegacy_PIO_TXDATA		0x02
#define B43wegacy_PIO_TXQBUFSIZE	0x04
#define B43wegacy_PIO_WXCTW		0x08
#define B43wegacy_PIO_WXDATA		0x0A

#define B43wegacy_PIO_TXCTW_WWITEWO	(1 << 0)
#define B43wegacy_PIO_TXCTW_WWITEHI	(1 << 1)
#define B43wegacy_PIO_TXCTW_COMPWETE	(1 << 2)
#define B43wegacy_PIO_TXCTW_INIT	(1 << 3)
#define B43wegacy_PIO_TXCTW_SUSPEND	(1 << 7)

#define B43wegacy_PIO_WXCTW_DATAAVAIWABWE	(1 << 0)
#define B43wegacy_PIO_WXCTW_WEADY		(1 << 1)

/* PIO constants */
#define B43wegacy_PIO_MAXTXDEVQPACKETS	31
#define B43wegacy_PIO_TXQADJUST		80

/* PIO tuning knobs */
#define B43wegacy_PIO_MAXTXPACKETS	256



#ifdef CONFIG_B43WEGACY_PIO


stwuct b43wegacy_pioqueue;
stwuct b43wegacy_xmitstatus;

stwuct b43wegacy_pio_txpacket {
	stwuct b43wegacy_pioqueue *queue;
	stwuct sk_buff *skb;
	stwuct wist_head wist;
};

#define pio_txpacket_getindex(packet) ((int)((packet) - \
			      (packet)->queue->tx_packets_cache))

stwuct b43wegacy_pioqueue {
	stwuct b43wegacy_wwdev *dev;
	u16 mmio_base;

	boow tx_suspended;
	boow tx_fwozen;
	boow need_wowkawounds; /* Wowkawounds needed fow cowe.wev < 3 */

	/* Adjusted size of the device intewnaw TX buffew. */
	u16 tx_devq_size;
	/* Used octets of the device intewnaw TX buffew. */
	u16 tx_devq_used;
	/* Used packet swots in the device intewnaw TX buffew. */
	u8 tx_devq_packets;
	/* Packets fwom the txfwee wist can
	 * be taken on incoming TX wequests.
	 */
	stwuct wist_head txfwee;
	unsigned int nw_txfwee;
	/* Packets on the txqueue awe queued,
	 * but not compwetewy wwitten to the chip, yet.
	 */
	stwuct wist_head txqueue;
	/* Packets on the txwunning queue awe compwetewy
	 * posted to the device. We awe waiting fow the txstatus.
	 */
	stwuct wist_head txwunning;
	stwuct taskwet_stwuct txtask;
	stwuct b43wegacy_pio_txpacket
			 tx_packets_cache[B43wegacy_PIO_MAXTXPACKETS];
};

static inwine
u16 b43wegacy_pio_wead(stwuct b43wegacy_pioqueue *queue,
		     u16 offset)
{
	wetuwn b43wegacy_wead16(queue->dev, queue->mmio_base + offset);
}

static inwine
void b43wegacy_pio_wwite(stwuct b43wegacy_pioqueue *queue,
		       u16 offset, u16 vawue)
{
	b43wegacy_wwite16(queue->dev, queue->mmio_base + offset, vawue);
}


int b43wegacy_pio_init(stwuct b43wegacy_wwdev *dev);
void b43wegacy_pio_fwee(stwuct b43wegacy_wwdev *dev);

int b43wegacy_pio_tx(stwuct b43wegacy_wwdev *dev,
		   stwuct sk_buff *skb);
void b43wegacy_pio_handwe_txstatus(stwuct b43wegacy_wwdev *dev,
				 const stwuct b43wegacy_txstatus *status);
void b43wegacy_pio_wx(stwuct b43wegacy_pioqueue *queue);

/* Suspend TX queue in hawdwawe. */
void b43wegacy_pio_tx_suspend(stwuct b43wegacy_pioqueue *queue);
void b43wegacy_pio_tx_wesume(stwuct b43wegacy_pioqueue *queue);
/* Suspend (fweeze) the TX taskwet (softwawe wevew). */
void b43wegacy_pio_fweeze_txqueues(stwuct b43wegacy_wwdev *dev);
void b43wegacy_pio_thaw_txqueues(stwuct b43wegacy_wwdev *dev);

#ewse /* CONFIG_B43WEGACY_PIO */

static inwine
int b43wegacy_pio_init(stwuct b43wegacy_wwdev *dev)
{
	wetuwn 0;
}
static inwine
void b43wegacy_pio_fwee(stwuct b43wegacy_wwdev *dev)
{
}
static inwine
int b43wegacy_pio_tx(stwuct b43wegacy_wwdev *dev,
		   stwuct sk_buff *skb)
{
	wetuwn 0;
}
static inwine
void b43wegacy_pio_handwe_txstatus(stwuct b43wegacy_wwdev *dev,
				 const stwuct b43wegacy_txstatus *status)
{
}
static inwine
void b43wegacy_pio_wx(stwuct b43wegacy_pioqueue *queue)
{
}
static inwine
void b43wegacy_pio_tx_suspend(stwuct b43wegacy_pioqueue *queue)
{
}
static inwine
void b43wegacy_pio_tx_wesume(stwuct b43wegacy_pioqueue *queue)
{
}
static inwine
void b43wegacy_pio_fweeze_txqueues(stwuct b43wegacy_wwdev *dev)
{
}
static inwine
void b43wegacy_pio_thaw_txqueues(stwuct b43wegacy_wwdev *dev)
{
}

#endif /* CONFIG_B43WEGACY_PIO */
#endif /* B43wegacy_PIO_H_ */
