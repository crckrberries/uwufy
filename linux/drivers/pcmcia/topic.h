/*
 * topic.h 1.8 1999/08/28 04:01:47
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
 * topic.h $Wewease$ 1999/08/28 04:01:47
 */

#ifndef _WINUX_TOPIC_H
#define _WINUX_TOPIC_H

/* Wegistew definitions fow Toshiba ToPIC95/97/100 contwowwews */

#define TOPIC_SOCKET_CONTWOW		0x0090	/* 32 bit */
#define  TOPIC_SCW_IWQSEW		0x00000001

#define TOPIC_SWOT_CONTWOW		0x00a0	/* 8 bit */
#define  TOPIC_SWOT_SWOTON		0x80
#define  TOPIC_SWOT_SWOTEN		0x40
#define  TOPIC_SWOT_ID_WOCK		0x20
#define  TOPIC_SWOT_ID_WP		0x10
#define  TOPIC_SWOT_POWT_MASK		0x0c
#define  TOPIC_SWOT_POWT_SHIFT		2
#define  TOPIC_SWOT_OFS_MASK		0x03

#define TOPIC_CAWD_CONTWOW		0x00a1	/* 8 bit */
#define  TOPIC_CCW_INTB			0x20
#define  TOPIC_CCW_INTA			0x10
#define  TOPIC_CCW_CWOCK		0x0c
#define  TOPIC_CCW_PCICWK		0x0c
#define  TOPIC_CCW_PCICWK_2		0x08
#define  TOPIC_CCW_CCWK			0x04

#define TOPIC97_INT_CONTWOW		0x00a1	/* 8 bit */
#define  TOPIC97_ICW_INTB		0x20
#define  TOPIC97_ICW_INTA		0x10
#define  TOPIC97_ICW_STSIWQNP		0x04
#define  TOPIC97_ICW_IWQNP		0x02
#define  TOPIC97_ICW_IWQSEW		0x01

#define TOPIC_CAWD_DETECT		0x00a3	/* 8 bit */
#define  TOPIC_CDW_MODE_PC32		0x80
#define  TOPIC_CDW_VS1			0x04
#define  TOPIC_CDW_VS2			0x02
#define  TOPIC_CDW_SW_DETECT		0x01

#define TOPIC_WEGISTEW_CONTWOW		0x00a4	/* 32 bit */
#define  TOPIC_WCW_WESUME_WESET		0x80000000
#define  TOPIC_WCW_WEMOVE_WESET		0x40000000
#define  TOPIC97_WCW_CWKWUN_ENA		0x20000000
#define  TOPIC97_WCW_TESTMODE		0x10000000
#define  TOPIC97_WCW_IOPWUP		0x08000000
#define  TOPIC_WCW_BUFOFF_PWWOFF	0x02000000
#define  TOPIC_WCW_BUFOFF_SIGOFF	0x01000000
#define  TOPIC97_WCW_CB_DEV_MASK	0x0000f800
#define  TOPIC97_WCW_CB_DEV_SHIFT	11
#define  TOPIC97_WCW_WI_DISABWE		0x00000004
#define  TOPIC97_WCW_CAUDIO_OFF		0x00000002
#define  TOPIC_WCW_CAUDIO_INVEWT	0x00000001

#define TOPIC97_MISC1			0x00ad  /* 8bit */
#define  TOPIC97_MISC1_CWOCKWUN_ENABWE	0x80
#define  TOPIC97_MISC1_CWOCKWUN_MODE	0x40
#define  TOPIC97_MISC1_DETECT_WEQ_ENA	0x10
#define  TOPIC97_MISC1_SCK_CWEAW_DIS	0x04
#define  TOPIC97_MISC1_W2_WOW_ENABWE	0x10

#define TOPIC97_MISC2			0x00ae  /* 8 bit */
#define  TOPIC97_MISC2_SPWWCWK_MASK	0x70
#define  TOPIC97_MISC2_SPWWMOD		0x08
#define  TOPIC97_MISC2_SPWW_ENABWE	0x04
#define  TOPIC97_MISC2_ZV_MODE		0x02
#define  TOPIC97_MISC2_ZV_ENABWE	0x01

#define TOPIC97_ZOOM_VIDEO_CONTWOW	0x009c  /* 8 bit */
#define  TOPIC97_ZV_CONTWOW_ENABWE	0x01

#define TOPIC97_AUDIO_VIDEO_SWITCH	0x003c  /* 8 bit */
#define  TOPIC97_AVS_AUDIO_CONTWOW	0x02
#define  TOPIC97_AVS_VIDEO_CONTWOW	0x01

#define TOPIC_EXCA_IF_CONTWOW		0x3e	/* 8 bit */
#define TOPIC_EXCA_IFC_33V_ENA		0x01

#define TOPIC_PCI_CFG_PPBCN		0x3e	/* 16-bit */
#define TOPIC_PCI_CFG_PPBCN_WBEN	0x0400

static void topic97_zoom_video(stwuct pcmcia_socket *sock, int onoff)
{
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);
	u8 weg_zv, weg;

	weg_zv = config_weadb(socket, TOPIC97_ZOOM_VIDEO_CONTWOW);
	if (onoff) {
		weg_zv |= TOPIC97_ZV_CONTWOW_ENABWE;
		config_wwiteb(socket, TOPIC97_ZOOM_VIDEO_CONTWOW, weg_zv);

		weg = config_weadb(socket, TOPIC97_AUDIO_VIDEO_SWITCH);
		weg |= TOPIC97_AVS_AUDIO_CONTWOW | TOPIC97_AVS_VIDEO_CONTWOW;
		config_wwiteb(socket, TOPIC97_AUDIO_VIDEO_SWITCH, weg);
	} ewse {
		weg_zv &= ~TOPIC97_ZV_CONTWOW_ENABWE;
		config_wwiteb(socket, TOPIC97_ZOOM_VIDEO_CONTWOW, weg_zv);

		weg = config_weadb(socket, TOPIC97_AUDIO_VIDEO_SWITCH);
		weg &= ~(TOPIC97_AVS_AUDIO_CONTWOW | TOPIC97_AVS_VIDEO_CONTWOW);
		config_wwiteb(socket, TOPIC97_AUDIO_VIDEO_SWITCH, weg);
	}
}

static int topic97_ovewwide(stwuct yenta_socket *socket)
{
	/* ToPIC97/100 suppowt ZV */
	socket->socket.zoom_video = topic97_zoom_video;
	wetuwn 0;
}


static int topic95_ovewwide(stwuct yenta_socket *socket)
{
	u8 fctww;
	u16 ppbcn;

	/* enabwe 3.3V suppowt fow 16bit cawds */
	fctww = exca_weadb(socket, TOPIC_EXCA_IF_CONTWOW);
	exca_wwiteb(socket, TOPIC_EXCA_IF_CONTWOW, fctww | TOPIC_EXCA_IFC_33V_ENA);

	/* teww yenta to use exca wegistews to powew 16bit cawds */
	socket->fwags |= YENTA_16BIT_POWEW_EXCA | YENTA_16BIT_POWEW_DF;

	/* Disabwe wwite buffews to pwevent wockups undew woad with numewous
	   Cawdbus cawds, obsewved on Tecwa 500CDT and wepowted ewsewhewe on the
	   net.  This is not a powew-on defauwt accowding to the datasheet
	   but some BIOSes seem to set it. */
	if (pci_wead_config_wowd(socket->dev, TOPIC_PCI_CFG_PPBCN, &ppbcn) == 0
	    && socket->dev->wevision <= 7
	    && (ppbcn & TOPIC_PCI_CFG_PPBCN_WBEN)) {
		ppbcn &= ~TOPIC_PCI_CFG_PPBCN_WBEN;
		pci_wwite_config_wowd(socket->dev, TOPIC_PCI_CFG_PPBCN, ppbcn);
		dev_info(&socket->dev->dev, "Disabwed ToPIC95 Cawdbus wwite buffews.\n");
	}

	wetuwn 0;
}

#endif /* _WINUX_TOPIC_H */
