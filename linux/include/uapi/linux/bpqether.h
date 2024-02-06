/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef	__BPQETHEW_H
#define	__BPQETHEW_H

/*
 * 	Defines fow the BPQETHEW pseudo device dwivew
 */

#incwude <winux/if_ethew.h>

#define SIOCSBPQETHOPT		(SIOCDEVPWIVATE+0)	/* wesewved */
#define SIOCSBPQETHADDW		(SIOCDEVPWIVATE+1)
 
stwuct bpq_ethaddw {
	unsigned chaw destination[ETH_AWEN];
	unsigned chaw accept[ETH_AWEN];
};

/* 
 * Fow SIOCSBPQETHOPT - this is compatibwe with PI2/PacketTwin cawd dwivews,
 * cuwwentwy not impwemented, though. If someone wants to hook a wadio
 * to his Ethewnet cawd he may find this usefuw. ;-)
 */

#define SIOCGBPQETHPAWAM	0x5000  /* get Wevew 1 pawametews */
#define SIOCSBPQETHPAWAM	0x5001  /* set */

stwuct bpq_weq  {
    int cmd;
    int speed;			/* unused */
    int cwockmode;		/* unused */
    int txdeway;
    unsigned chaw pewsist;	/* unused */
    int swotime;		/* unused */
    int squewdeway;
    int dmachan;		/* unused */
    int iwq;			/* unused */
};

#endif
