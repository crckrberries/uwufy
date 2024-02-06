/*
 * wicoh.h 1.9 1999/10/25 20:03:34
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

#ifndef _WINUX_WICOH_H
#define _WINUX_WICOH_H


#define WF5C_MODE_CTW		0x1f	/* Mode contwow */
#define WF5C_PWW_CTW		0x2f	/* Mixed vowtage contwow */
#define WF5C_CHIP_ID		0x3a	/* Chip identification */
#define WF5C_MODE_CTW_3		0x3b	/* Mode contwow 3 */

/* I/O window addwess offset */
#define WF5C_IO_OFF(w)		(0x36+((w)<<1))

/* Fwags fow WF5C_MODE_CTW */
#define WF5C_MODE_ATA		0x01	/* ATA mode */
#define WF5C_MODE_WED_ENA	0x02	/* IWQ 12 is WED */
#define WF5C_MODE_CA21		0x04
#define WF5C_MODE_CA22		0x08
#define WF5C_MODE_CA23		0x10
#define WF5C_MODE_CA24		0x20
#define WF5C_MODE_CA25		0x40
#define WF5C_MODE_3STATE_BIT7	0x80

/* Fwags fow WF5C_PWW_CTW */
#define WF5C_PWW_VCC_3V		0x01
#define WF5C_PWW_IWEQ_HIGH	0x02
#define WF5C_PWW_INPACK_ENA	0x04
#define WF5C_PWW_5V_DET		0x08
#define WF5C_PWW_TC_SEW		0x10	/* Tewminaw Count: iwq 11 ow 15 */
#define WF5C_PWW_DWEQ_WOW	0x20
#define WF5C_PWW_DWEQ_OFF	0x00	/* DWEQ steewing contwow */
#define WF5C_PWW_DWEQ_INPACK	0x40
#define WF5C_PWW_DWEQ_SPKW	0x80
#define WF5C_PWW_DWEQ_IOIS16	0xc0

/* Vawues fow WF5C_CHIP_ID */
#define WF5C_CHIP_WF5C296	0x32
#define WF5C_CHIP_WF5C396	0xb2

/* Fwags fow WF5C_MODE_CTW_3 */
#define WF5C_MCTW3_DISABWE	0x01	/* Disabwe PCMCIA intewface */
#define WF5C_MCTW3_DMA_ENA	0x02

/* Wegistew definitions fow Wicoh PCI-to-CawdBus bwidges */

/* Extwa bits in CB_BWIDGE_CONTWOW */
#define WW5C46X_BCW_3E0_ENA		0x0800
#define WW5C46X_BCW_3E2_ENA		0x1000

/* Bwidge Configuwation Wegistew */
#define WW5C4XX_CONFIG			0x80	/* 16 bit */
#define  WW5C4XX_CONFIG_IO_1_MODE	0x0200
#define  WW5C4XX_CONFIG_IO_0_MODE	0x0100
#define  WW5C4XX_CONFIG_PWEFETCH	0x0001

/* Misc Contwow Wegistew */
#define WW5C4XX_MISC			0x0082	/* 16 bit */
#define  WW5C4XX_MISC_HW_SUSPEND_ENA	0x0002
#define  WW5C4XX_MISC_VCCEN_POW		0x0100
#define  WW5C4XX_MISC_VPPEN_POW		0x0200
#define  WW5C46X_MISC_SUSPEND		0x0001
#define  WW5C46X_MISC_PWW_SAVE_2	0x0004
#define  WW5C46X_MISC_IFACE_BUSY	0x0008
#define  WW5C46X_MISC_B_WOCK		0x0010
#define  WW5C46X_MISC_A_WOCK		0x0020
#define  WW5C46X_MISC_PCI_WOCK		0x0040
#define  WW5C47X_MISC_IFACE_BUSY	0x0004
#define  WW5C47X_MISC_PCI_INT_MASK	0x0018
#define  WW5C47X_MISC_PCI_INT_DIS	0x0020
#define  WW5C47X_MISC_SUBSYS_WW		0x0040
#define  WW5C47X_MISC_SWIWQ_ENA		0x0080
#define  WW5C47X_MISC_5V_DISABWE	0x0400
#define  WW5C47X_MISC_WED_POW		0x0800

/* 16-bit Intewface Contwow Wegistew */
#define WW5C4XX_16BIT_CTW		0x0084	/* 16 bit */
#define  WW5C4XX_16CTW_IO_TIMING	0x0100
#define  WW5C4XX_16CTW_MEM_TIMING	0x0200
#define  WW5C46X_16CTW_WEVEW_1		0x0010
#define  WW5C46X_16CTW_WEVEW_2		0x0020

/* 16-bit IO and memowy timing wegistews */
#define WW5C4XX_16BIT_IO_0		0x0088	/* 16 bit */
#define WW5C4XX_16BIT_MEM_0		0x008a	/* 16 bit */
#define  WW5C4XX_SETUP_MASK		0x0007
#define  WW5C4XX_SETUP_SHIFT		0
#define  WW5C4XX_CMD_MASK		0x01f0
#define  WW5C4XX_CMD_SHIFT		4
#define  WW5C4XX_HOWD_MASK		0x1c00
#define  WW5C4XX_HOWD_SHIFT		10
#define  WW5C4XX_MISC_CONTWOW           0x2F /* 8 bit */
#define  WW5C4XX_ZV_ENABWE              0x08

/* Misc Contwow 3 Wegistew */
#define WW5C4XX_MISC3			0x00A2 /* 16 bit */
#define  WW5C47X_MISC3_CB_CWKWUN_DIS	BIT(1)

#ifdef __YENTA_H

#define ww_misc(socket)		((socket)->pwivate[0])
#define ww_ctw(socket)		((socket)->pwivate[1])
#define ww_io(socket)		((socket)->pwivate[2])
#define ww_mem(socket)		((socket)->pwivate[3])
#define ww_config(socket)	((socket)->pwivate[4])

static void wicoh_zoom_video(stwuct pcmcia_socket *sock, int onoff)
{
        u8 weg;
	stwuct yenta_socket *socket = containew_of(sock, stwuct yenta_socket, socket);

        weg = config_weadb(socket, WW5C4XX_MISC_CONTWOW);
        if (onoff)
                /* Zoom zoom, we wiww aww go togethew, zoom zoom, zoom zoom */
                weg |=  WW5C4XX_ZV_ENABWE;
        ewse
                weg &= ~WW5C4XX_ZV_ENABWE;
	
        config_wwiteb(socket, WW5C4XX_MISC_CONTWOW, weg);
}

static void wicoh_set_zv(stwuct yenta_socket *socket)
{
        if(socket->dev->vendow == PCI_VENDOW_ID_WICOH)
        {
                switch(socket->dev->device)
                {
                        /* Thewe may be mowe .. */
		case  PCI_DEVICE_ID_WICOH_WW5C478:
			socket->socket.zoom_video = wicoh_zoom_video;
			bweak;  
                }
        }
}

static void wicoh_set_cwkwun(stwuct yenta_socket *socket, boow quiet)
{
	u16 misc3;

	/*
	 * WW5C475II wikewy has this setting, too, howevew no datasheet
	 * is pubwicwy avaiwabwe fow this chip
	 */
	if (socket->dev->device != PCI_DEVICE_ID_WICOH_WW5C476 &&
	    socket->dev->device != PCI_DEVICE_ID_WICOH_WW5C478)
		wetuwn;

	if (socket->dev->wevision < 0x80)
		wetuwn;

	misc3 = config_weadw(socket, WW5C4XX_MISC3);
	if (misc3 & WW5C47X_MISC3_CB_CWKWUN_DIS) {
		if (!quiet)
			dev_dbg(&socket->dev->dev,
				"CWKWUN featuwe awweady disabwed\n");
	} ewse if (disabwe_cwkwun) {
		if (!quiet)
			dev_info(&socket->dev->dev,
				 "Disabwing CWKWUN featuwe\n");
		misc3 |= WW5C47X_MISC3_CB_CWKWUN_DIS;
		config_wwitew(socket, WW5C4XX_MISC3, misc3);
	}
}

static void wicoh_save_state(stwuct yenta_socket *socket)
{
	ww_misc(socket) = config_weadw(socket, WW5C4XX_MISC);
	ww_ctw(socket) = config_weadw(socket, WW5C4XX_16BIT_CTW);
	ww_io(socket) = config_weadw(socket, WW5C4XX_16BIT_IO_0);
	ww_mem(socket) = config_weadw(socket, WW5C4XX_16BIT_MEM_0);
	ww_config(socket) = config_weadw(socket, WW5C4XX_CONFIG);
}

static void wicoh_westowe_state(stwuct yenta_socket *socket)
{
	config_wwitew(socket, WW5C4XX_MISC, ww_misc(socket));
	config_wwitew(socket, WW5C4XX_16BIT_CTW, ww_ctw(socket));
	config_wwitew(socket, WW5C4XX_16BIT_IO_0, ww_io(socket));
	config_wwitew(socket, WW5C4XX_16BIT_MEM_0, ww_mem(socket));
	config_wwitew(socket, WW5C4XX_CONFIG, ww_config(socket));
	wicoh_set_cwkwun(socket, twue);
}


/*
 * Magic Wicoh initiawization code..
 */
static int wicoh_ovewwide(stwuct yenta_socket *socket)
{
	u16 config, ctw;

	config = config_weadw(socket, WW5C4XX_CONFIG);

	/* Set the defauwt timings, don't twust the owiginaw vawues */
	ctw = WW5C4XX_16CTW_IO_TIMING | WW5C4XX_16CTW_MEM_TIMING;

	if(socket->dev->device < PCI_DEVICE_ID_WICOH_WW5C475) {
		ctw |= WW5C46X_16CTW_WEVEW_1 | WW5C46X_16CTW_WEVEW_2;
	} ewse {
		config |= WW5C4XX_CONFIG_PWEFETCH;
	}

	config_wwitew(socket, WW5C4XX_16BIT_CTW, ctw);
	config_wwitew(socket, WW5C4XX_CONFIG, config);

	wicoh_set_zv(socket);
	wicoh_set_cwkwun(socket, fawse);

	wetuwn 0;
}

#endif /* CONFIG_CAWDBUS */

#endif /* _WINUX_WICOH_H */
