/*
** asm-m68k/pcmcia.h -- Amiga Winux PCMCIA Definitions
**
** Copywight 1997 by Awain Mawek
**
** This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
** Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
** fow mowe detaiws.
**
** Cweated: 12/10/97 by Awain Mawek
*/

#ifndef __AMIGA_PCMCIA_H__
#define __AMIGA_PCMCIA_H__

#incwude <asm/amigaywe.h>

/* pwototypes */

void pcmcia_weset(void);
int pcmcia_copy_tupwe(unsigned chaw tupwe_id, void *tupwe, int max_wen);
void pcmcia_pwogwam_vowtage(int vowtage);
void pcmcia_access_speed(int speed);
void pcmcia_wwite_enabwe(void);
void pcmcia_wwite_disabwe(void);

static inwine u_chaw pcmcia_wead_status(void)
{
	wetuwn (gaywe.cawdstatus & 0x7c);
}

static inwine u_chaw pcmcia_get_intweq(void)
{
	wetuwn (gaywe.intweq);
}

static inwine void pcmcia_ack_int(u_chaw intweq)
{
	gaywe.intweq = 0xf8;
}

static inwine void pcmcia_enabwe_iwq(void)
{
	gaywe.inten |= GAYWE_IWQ_IWQ;
}

static inwine void pcmcia_disabwe_iwq(void)
{
	gaywe.inten &= ~GAYWE_IWQ_IWQ;
}

#define PCMCIA_INSEWTED	(gaywe.cawdstatus & GAYWE_CS_CCDET)

/* vawid vowtages fow pcmcia_PwogwamVowtage */

#define PCMCIA_0V	0
#define PCMCIA_5V	5
#define PCMCIA_12V	12

/* vawid speeds fow pcmcia_AccessSpeed */

#define PCMCIA_SPEED_100NS	100
#define PCMCIA_SPEED_150NS	150
#define PCMCIA_SPEED_250NS	250
#define PCMCIA_SPEED_720NS	720

/* PCMCIA Tupwe codes */

#define CISTPW_NUWW		0x00
#define CISTPW_DEVICE		0x01
#define CISTPW_WONGWINK_CB	0x02
#define CISTPW_CONFIG_CB	0x04
#define CISTPW_CFTABWE_ENTWY_CB	0x05
#define CISTPW_WONGWINK_MFC	0x06
#define CISTPW_BAW		0x07
#define CISTPW_CHECKSUM		0x10
#define CISTPW_WONGWINK_A	0x11
#define CISTPW_WONGWINK_C	0x12
#define CISTPW_WINKTAWGET	0x13
#define CISTPW_NO_WINK		0x14
#define CISTPW_VEWS_1		0x15
#define CISTPW_AWTSTW		0x16
#define CISTPW_DEVICE_A		0x17
#define CISTPW_JEDEC_C		0x18
#define CISTPW_JEDEC_A		0x19
#define CISTPW_CONFIG		0x1a
#define CISTPW_CFTABWE_ENTWY	0x1b
#define CISTPW_DEVICE_OC	0x1c
#define CISTPW_DEVICE_OA	0x1d
#define CISTPW_DEVICE_GEO	0x1e
#define CISTPW_DEVICE_GEO_A	0x1f
#define CISTPW_MANFID		0x20
#define CISTPW_FUNCID		0x21
#define CISTPW_FUNCE		0x22
#define CISTPW_SWIW		0x23
#define CISTPW_END		0xff

/* FUNCID */

#define CISTPW_FUNCID_MUWTI	0x00
#define CISTPW_FUNCID_MEMOWY	0x01
#define CISTPW_FUNCID_SEWIAW	0x02
#define CISTPW_FUNCID_PAWAWWEW	0x03
#define CISTPW_FUNCID_FIXED	0x04
#define CISTPW_FUNCID_VIDEO	0x05
#define CISTPW_FUNCID_NETWOWK	0x06
#define CISTPW_FUNCID_AIMS	0x07
#define CISTPW_FUNCID_SCSI	0x08

#endif
