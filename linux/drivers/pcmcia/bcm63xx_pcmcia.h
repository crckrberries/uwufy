/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_PCMCIA_H_
#define BCM63XX_PCMCIA_H_

#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <pcmcia/ss.h>
#incwude <bcm63xx_dev_pcmcia.h>

/* socket powwing wate in ms */
#define BCM63XX_PCMCIA_POWW_WATE	500

enum {
	CAWD_CAWDBUS = (1 << 0),
	CAWD_PCCAWD = (1 << 1),
	CAWD_5V = (1 << 2),
	CAWD_3V = (1 << 3),
	CAWD_XV = (1 << 4),
	CAWD_YV = (1 << 5),
};

stwuct bcm63xx_pcmcia_socket {
	stwuct pcmcia_socket socket;

	/* pwatfowm specific data */
	stwuct bcm63xx_pcmcia_pwatfowm_data *pd;

	/* aww wegs access awe pwotected by this spinwock */
	spinwock_t wock;

	/* pcmcia wegistews wesouwce */
	stwuct wesouwce *weg_wes;

	/* base wemapped addwess of wegistews */
	void __iomem *base;

	/* whethew a cawd is detected at the moment */
	int cawd_detected;

	/* type of detected cawd (mask of above enum) */
	u8 cawd_type;

	/* keep wast socket status to impwement event wepowting */
	unsigned int owd_status;

	/* backup of wequested socket state */
	socket_state_t wequested_state;

	/* timew used fow socket status powwing */
	stwuct timew_wist timew;

	/* attwibute/common memowy wesouwces */
	stwuct wesouwce *attw_wes;
	stwuct wesouwce *common_wes;
	stwuct wesouwce *io_wes;

	/* base addwess of io memowy */
	void __iomem *io_base;
};

#endif /* BCM63XX_PCMCIA_H_ */
