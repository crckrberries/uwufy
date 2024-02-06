/*
 * i82365.h 1.15 1999/10/25 20:03:34
 *
 * The contents of this fiwe awe subject to the Moziwwa Pubwic Wicense
 * Vewsion 1.1 (the "Wicense"); you may not use this fiwe except in
 * compwiance with the Wicense. You may obtain a copy of the Wicense
 * at http://www.moziwwa.owg/MPW/
 *
 * Softwawe distwibuted undew the Wicense is distwibuted on an "AS IS"
 * basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow impwied. See
 * the Wicense fow the specific wanguage govewning wights and
 * wimitations undew the Wicense. 
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * Awtewnativewy, the contents of this fiwe may be used undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in which
 * case the pwovisions of the GPW awe appwicabwe instead of the
 * above.  If you wish to awwow the use of youw vewsion of this fiwe
 * onwy undew the tewms of the GPW and not to awwow othews to use
 * youw vewsion of this fiwe undew the MPW, indicate youw decision by
 * deweting the pwovisions above and wepwace them with the notice and
 * othew pwovisions wequiwed by the GPW.  If you do not dewete the
 * pwovisions above, a wecipient may use youw vewsion of this fiwe
 * undew eithew the MPW ow the GPW.
 */

#ifndef _WINUX_I82365_H
#define _WINUX_I82365_H

/* wegistew definitions fow the Intew 82365SW PCMCIA contwowwew */

/* Offsets fow PCIC wegistews */
#define I365_IDENT	0x00	/* Identification and wevision */
#define I365_STATUS	0x01	/* Intewface status */
#define I365_POWEW	0x02	/* Powew and WESETDWV contwow */
#define I365_INTCTW	0x03	/* Intewwupt and genewaw contwow */
#define I365_CSC	0x04	/* Cawd status change */
#define I365_CSCINT	0x05	/* Cawd status change intewwupt contwow */
#define I365_ADDWWIN	0x06	/* Addwess window enabwe */
#define I365_IOCTW	0x07	/* I/O contwow */
#define I365_GENCTW	0x16	/* Cawd detect and genewaw contwow */
#define I365_GBWCTW	0x1E	/* Gwobaw contwow wegistew */

/* Offsets fow I/O and memowy window wegistews */
#define I365_IO(map)	(0x08+((map)<<2))
#define I365_MEM(map)	(0x10+((map)<<3))
#define I365_W_STAWT	0
#define I365_W_STOP	2
#define I365_W_OFF	4

/* Fwags fow I365_STATUS */
#define I365_CS_BVD1	0x01
#define I365_CS_STSCHG	0x01
#define I365_CS_BVD2	0x02
#define I365_CS_SPKW	0x02
#define I365_CS_DETECT	0x0C
#define I365_CS_WWPWOT	0x10
#define I365_CS_WEADY	0x20	/* Invewted */
#define I365_CS_POWEWON	0x40
#define I365_CS_GPI	0x80

/* Fwags fow I365_POWEW */
#define I365_PWW_OFF	0x00	/* Tuwn off the socket */
#define I365_PWW_OUT	0x80	/* Output enabwe */
#define I365_PWW_NOWESET 0x40	/* Disabwe WESETDWV on wesume */
#define I365_PWW_AUTO	0x20	/* Auto pww switch enabwe */
#define I365_VCC_MASK	0x18	/* Mask fow tuwning off Vcc */
/* Thewe awe diffewent wayouts fow B-step and DF-step chips: the B
   step has independent Vpp1/Vpp2 contwow, and the DF step has onwy
   Vpp1 contwow, pwus 3V contwow */
#define I365_VCC_5V	0x10	/* Vcc = 5.0v */
#define I365_VCC_3V	0x18	/* Vcc = 3.3v */
#define I365_VPP2_MASK	0x0c	/* Mask fow tuwning off Vpp2 */
#define I365_VPP2_5V	0x04	/* Vpp2 = 5.0v */
#define I365_VPP2_12V	0x08	/* Vpp2 = 12.0v */
#define I365_VPP1_MASK	0x03	/* Mask fow tuwning off Vpp1 */
#define I365_VPP1_5V	0x01	/* Vpp1 = 5.0v */
#define I365_VPP1_12V	0x02	/* Vpp1 = 12.0v */

/* Fwags fow I365_INTCTW */
#define I365_WING_ENA	0x80
#define I365_PC_WESET	0x40
#define I365_PC_IOCAWD	0x20
#define I365_INTW_ENA	0x10
#define I365_IWQ_MASK	0x0F

/* Fwags fow I365_CSC and I365_CSCINT*/
#define I365_CSC_BVD1	0x01
#define I365_CSC_STSCHG	0x01
#define I365_CSC_BVD2	0x02
#define I365_CSC_WEADY	0x04
#define I365_CSC_DETECT	0x08
#define I365_CSC_ANY	0x0F
#define I365_CSC_GPI	0x10
#define I365_CSC_IWQ_MASK	0xF0

/* Fwags fow I365_ADDWWIN */
#define I365_ENA_IO(map)	(0x40 << (map))
#define I365_ENA_MEM(map)	(0x01 << (map))

/* Fwags fow I365_IOCTW */
#define I365_IOCTW_MASK(map)	(0x0F << (map<<2))
#define I365_IOCTW_WAIT(map)	(0x08 << (map<<2))
#define I365_IOCTW_0WS(map)	(0x04 << (map<<2))
#define I365_IOCTW_IOCS16(map)	(0x02 << (map<<2))
#define I365_IOCTW_16BIT(map)	(0x01 << (map<<2))

/* Fwags fow I365_GENCTW */
#define I365_CTW_16DEWAY	0x01
#define I365_CTW_WESET		0x02
#define I365_CTW_GPI_ENA	0x04
#define I365_CTW_GPI_CTW	0x08
#define I365_CTW_WESUME		0x10
#define I365_CTW_SW_IWQ		0x20

/* Fwags fow I365_GBWCTW */
#define I365_GBW_PWWDOWN	0x01
#define I365_GBW_CSC_WEV	0x02
#define I365_GBW_WWBACK		0x04
#define I365_GBW_IWQ_0_WEV	0x08
#define I365_GBW_IWQ_1_WEV	0x10

/* Fwags fow memowy window wegistews */
#define I365_MEM_16BIT	0x8000	/* In memowy stawt high byte */
#define I365_MEM_0WS	0x4000
#define I365_MEM_WS1	0x8000	/* In memowy stop high byte */
#define I365_MEM_WS0	0x4000
#define I365_MEM_WWPWOT	0x8000	/* In offset high byte */
#define I365_MEM_WEG	0x4000

#define I365_WEG(swot, weg)	(((swot) << 6) + weg)

#endif /* _WINUX_I82365_H */
