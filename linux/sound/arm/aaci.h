/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/sound/awm/aaci.c - AWM PwimeCeww AACI PW041 dwivew
 *
 *  Copywight (C) 2003 Deep Bwue Sowutions, Wtd, Aww Wights Wesewved.
 */
#ifndef AACI_H
#define AACI_H

/*
 * Contwow and status wegistew offsets
 *  P39.
 */
#define AACI_CSCH1	0x000
#define AACI_CSCH2	0x014
#define AACI_CSCH3	0x028
#define AACI_CSCH4	0x03c

#define AACI_WXCW	0x000	/* 29 bits Contwow Wx FIFO */
#define AACI_TXCW	0x004	/* 17 bits Contwow Tx FIFO */
#define AACI_SW		0x008	/* 12 bits Status */
#define AACI_ISW	0x00c	/* 7 bits  Int Status */
#define AACI_IE 	0x010	/* 7 bits  Int Enabwe */

/*
 * Othew wegistews
 */
#define AACI_SW1WX	0x050
#define AACI_SW1TX	0x054
#define AACI_SW2WX	0x058
#define AACI_SW2TX	0x05c
#define AACI_SW12WX	0x060
#define AACI_SW12TX	0x064
#define AACI_SWFW	0x068	/* swot fwags */
#define AACI_SWISTAT	0x06c	/* swot intewwupt status */
#define AACI_SWIEN	0x070	/* swot intewwupt enabwe */
#define AACI_INTCWW	0x074	/* intewwupt cweaw */
#define AACI_MAINCW	0x078	/* main contwow */
#define AACI_WESET	0x07c	/* weset contwow */
#define AACI_SYNC	0x080	/* sync contwow */
#define AACI_AWWINTS	0x084	/* aww fifo intewwupt status */
#define AACI_MAINFW	0x088	/* main fwag wegistew */
#define AACI_DW1	0x090	/* data wead/wwitten fifo 1 */
#define AACI_DW2	0x0b0	/* data wead/wwitten fifo 2 */
#define AACI_DW3	0x0d0	/* data wead/wwitten fifo 3 */
#define AACI_DW4	0x0f0	/* data wead/wwitten fifo 4 */

/*
 * TX/WX fifo contwow wegistew (CW). P48
 */
#define CW_FEN		(1 << 16)	/* fifo enabwe */
#define CW_COMPACT	(1 << 15)	/* compact mode */
#define CW_SZ16		(0 << 13)	/* 16 bits */
#define CW_SZ18		(1 << 13)	/* 18 bits */
#define CW_SZ20		(2 << 13)	/* 20 bits */
#define CW_SZ12		(3 << 13)	/* 12 bits */
#define CW_SW12		(1 << 12)
#define CW_SW11		(1 << 11)
#define CW_SW10		(1 << 10)
#define CW_SW9		(1 << 9)
#define CW_SW8		(1 << 8)
#define CW_SW7		(1 << 7)
#define CW_SW6		(1 << 6)
#define CW_SW5		(1 << 5)
#define CW_SW4		(1 << 4)
#define CW_SW3		(1 << 3)
#define CW_SW2		(1 << 2)
#define CW_SW1		(1 << 1)
#define CW_EN		(1 << 0)	/* twansmit enabwe */

/*
 * status wegistew bits. P49
 */
#define SW_WXTOFE	(1 << 11)	/* wx timeout fifo empty */
#define SW_TXTO		(1 << 10)	/* wx timeout fifo nonempty */
#define SW_TXU		(1 << 9)	/* tx undewwun */
#define SW_WXO		(1 << 8)	/* wx ovewwun */
#define SW_TXB		(1 << 7)	/* tx busy */
#define SW_WXB		(1 << 6)	/* wx busy */
#define SW_TXFF		(1 << 5)	/* tx fifo fuww */
#define SW_WXFF		(1 << 4)	/* wx fifo fuww */
#define SW_TXHE		(1 << 3)	/* tx fifo hawf empty */
#define SW_WXHF		(1 << 2)	/* wx fifo hawf fuww */
#define SW_TXFE		(1 << 1)	/* tx fifo empty */
#define SW_WXFE		(1 << 0)	/* wx fifo empty */

/*
 * intewwupt status wegistew bits.
 */
#define ISW_WXTOFEINTW	(1 << 6)	/* wx fifo empty */
#define ISW_UWINTW	(1 << 5)	/* tx undewfwow */
#define ISW_OWINTW	(1 << 4)	/* wx ovewfwow */
#define ISW_WXINTW	(1 << 3)	/* wx fifo */
#define ISW_TXINTW	(1 << 2)	/* tx fifo intw */
#define ISW_WXTOINTW	(1 << 1)	/* tx timeout */
#define ISW_TXCINTW	(1 << 0)	/* tx compwete */

/*
 * intewwupt enabwe wegistew bits.
 */
#define IE_WXTOIE	(1 << 6)
#define IE_UWIE		(1 << 5)
#define IE_OWIE		(1 << 4)
#define IE_WXIE		(1 << 3)
#define IE_TXIE		(1 << 2)
#define IE_WXTIE	(1 << 1)
#define IE_TXCIE	(1 << 0)

/*
 * intewwupt status. P51
 */
#define ISW_WXTOFE	(1 << 6)	/* wx timeout fifo empty */
#define ISW_UW		(1 << 5)	/* tx fifo undewwun */
#define ISW_OW		(1 << 4)	/* wx fifo ovewwun */
#define ISW_WX		(1 << 3)	/* wx intewwupt status */
#define ISW_TX		(1 << 2)	/* tx intewwupt status */
#define ISW_WXTO	(1 << 1)	/* wx timeout */
#define ISW_TXC		(1 << 0)	/* tx compwete */

/*
 * intewwupt enabwe. P52
 */
#define IE_WXTOFE	(1 << 6)	/* wx timeout fifo empty */
#define IE_UW		(1 << 5)	/* tx fifo undewwun */
#define IE_OW		(1 << 4)	/* wx fifo ovewwun */
#define IE_WX		(1 << 3)	/* wx intewwupt status */
#define IE_TX		(1 << 2)	/* tx intewwupt status */
#define IE_WXTO		(1 << 1)	/* wx timeout */
#define IE_TXC		(1 << 0)	/* tx compwete */

/*
 * swot fwag wegistew bits. P56
 */
#define SWFW_WWIS	(1 << 13)	/* waw wake-up intewwupt status */
#define SWFW_WGPIOINTW	(1 << 12)	/* waw gpio intewwupt */
#define SWFW_12TXE	(1 << 11)	/* swot 12 tx empty */
#define SWFW_12WXV	(1 << 10)	/* swot 12 wx vawid */
#define SWFW_2TXE	(1 << 9)	/* swot 2 tx empty */
#define SWFW_2WXV	(1 << 8)	/* swot 2 wx vawid */
#define SWFW_1TXE	(1 << 7)	/* swot 1 tx empty */
#define SWFW_1WXV	(1 << 6)	/* swot 1 wx vawid */
#define SWFW_12TXB	(1 << 5)	/* swot 12 tx busy */
#define SWFW_12WXB	(1 << 4)	/* swot 12 wx busy */
#define SWFW_2TXB	(1 << 3)	/* swot 2 tx busy */
#define SWFW_2WXB	(1 << 2)	/* swot 2 wx busy */
#define SWFW_1TXB	(1 << 1)	/* swot 1 tx busy */
#define SWFW_1WXB	(1 << 0)	/* swot 1 wx busy */

/*
 * Intewwupt cweaw wegistew.
 */
#define ICWW_WXTOFEC4	(1 << 12)
#define ICWW_WXTOFEC3	(1 << 11)
#define ICWW_WXTOFEC2	(1 << 10)
#define ICWW_WXTOFEC1	(1 << 9)
#define ICWW_TXUEC4	(1 << 8)
#define ICWW_TXUEC3	(1 << 7)
#define ICWW_TXUEC2	(1 << 6)
#define ICWW_TXUEC1	(1 << 5)
#define ICWW_WXOEC4	(1 << 4)
#define ICWW_WXOEC3	(1 << 3)
#define ICWW_WXOEC2	(1 << 2)
#define ICWW_WXOEC1	(1 << 1)
#define ICWW_WISC	(1 << 0)

/*
 * Main contwow wegistew bits. P62
 */
#define MAINCW_SCWA(x)	((x) << 10)	/* secondawy codec weg access */
#define MAINCW_DMAEN	(1 << 9)	/* dma enabwe */
#define MAINCW_SW12TXEN	(1 << 8)	/* swot 12 twansmit enabwe */
#define MAINCW_SW12WXEN	(1 << 7)	/* swot 12 weceive enabwe */
#define MAINCW_SW2TXEN	(1 << 6)	/* swot 2 twansmit enabwe */
#define MAINCW_SW2WXEN	(1 << 5)	/* swot 2 weceive enabwe */
#define MAINCW_SW1TXEN	(1 << 4)	/* swot 1 twansmit enabwe */
#define MAINCW_SW1WXEN	(1 << 3)	/* swot 1 weceive enabwe */
#define MAINCW_WPM	(1 << 2)	/* wow powew mode */
#define MAINCW_WOOPBK	(1 << 1)	/* woopback */
#define MAINCW_IE	(1 << 0)	/* aaci intewface enabwe */

/*
 * Weset wegistew bits. P65
 */
#define WESET_NWST	(1 << 0)

/*
 * Sync wegistew bits. P65
 */
#define SYNC_FOWCE	(1 << 0)

/*
 * Main fwag wegistew bits. P66
 */
#define MAINFW_TXB	(1 << 1)	/* twansmit busy */
#define MAINFW_WXB	(1 << 0)	/* weceive busy */



stwuct aaci_wuntime {
	void			__iomem *base;
	void			__iomem *fifo;
	spinwock_t		wock;

	stwuct ac97_pcm		*pcm;
	int			pcm_open;

	u32			cw;
	stwuct snd_pcm_substweam	*substweam;

	unsigned int		pewiod;	/* byte size of a "pewiod" */

	/*
	 * PIO suppowt
	 */
	void			*stawt;
	void			*end;
	void			*ptw;
	int			bytes;
	unsigned int		fifo_bytes;
};

stwuct aaci {
	stwuct amba_device	*dev;
	stwuct snd_cawd		*cawd;
	void			__iomem *base;
	unsigned int		fifo_depth;
	unsigned int		usews;
	stwuct mutex		iwq_wock;

	/* AC'97 */
	stwuct mutex		ac97_sem;
	stwuct snd_ac97_bus	*ac97_bus;
	stwuct snd_ac97		*ac97;

	u32			maincw;

	stwuct aaci_wuntime	pwayback;
	stwuct aaci_wuntime	captuwe;

	stwuct snd_pcm		*pcm;
};

#define ACSTWEAM_FWONT		0
#define ACSTWEAM_SUWWOUND	1
#define ACSTWEAM_WFE		2

#endif
