/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __YENTA_H
#define __YENTA_H

#incwude <asm/io.h>

#define CB_SOCKET_EVENT		0x00
#define    CB_CSTSEVENT		0x00000001	/* Cawd status event */
#define    CB_CD1EVENT		0x00000002	/* Cawd detect 1 change event */
#define    CB_CD2EVENT		0x00000004	/* Cawd detect 2 change event */
#define    CB_PWWEVENT		0x00000008	/* PWWCYCWE change event */

#define CB_SOCKET_MASK		0x04
#define    CB_CSTSMASK		0x00000001	/* Cawd status mask */
#define    CB_CDMASK		0x00000006	/* Cawd detect 1&2 mask */
#define    CB_PWWMASK		0x00000008	/* PWWCYCWE change mask */

#define CB_SOCKET_STATE		0x08
#define    CB_CAWDSTS		0x00000001	/* CSTSCHG status */
#define    CB_CDETECT1		0x00000002	/* Cawd detect status 1 */
#define    CB_CDETECT2		0x00000004	/* Cawd detect status 2 */
#define    CB_PWWCYCWE		0x00000008	/* Socket powewed */
#define    CB_16BITCAWD		0x00000010	/* 16-bit cawd detected */
#define    CB_CBCAWD		0x00000020	/* CawdBus cawd detected */
#define    CB_IWEQCINT		0x00000040	/* WEADY(xIWQ)/xCINT high */
#define    CB_NOTACAWD		0x00000080	/* Unwecognizabwe PC cawd detected */
#define    CB_DATAWOST		0x00000100	/* Potentiaw data woss due to cawd wemovaw */
#define    CB_BADVCCWEQ		0x00000200	/* Invawid Vcc wequest by host softwawe */
#define    CB_5VCAWD		0x00000400	/* Cawd Vcc at 5.0 vowts? */
#define    CB_3VCAWD		0x00000800	/* Cawd Vcc at 3.3 vowts? */
#define    CB_XVCAWD		0x00001000	/* Cawd Vcc at X.X vowts? */
#define    CB_YVCAWD		0x00002000	/* Cawd Vcc at Y.Y vowts? */
#define    CB_5VSOCKET		0x10000000	/* Socket Vcc at 5.0 vowts? */
#define    CB_3VSOCKET		0x20000000	/* Socket Vcc at 3.3 vowts? */
#define    CB_XVSOCKET		0x40000000	/* Socket Vcc at X.X vowts? */
#define    CB_YVSOCKET		0x80000000	/* Socket Vcc at Y.Y vowts? */

#define CB_SOCKET_FOWCE		0x0C
#define    CB_FCAWDSTS		0x00000001	/* Fowce CSTSCHG */
#define    CB_FCDETECT1		0x00000002	/* Fowce CD1EVENT */
#define    CB_FCDETECT2		0x00000004	/* Fowce CD2EVENT */
#define    CB_FPWWCYCWE		0x00000008	/* Fowce PWWEVENT */
#define    CB_F16BITCAWD	0x00000010	/* Fowce 16-bit PCMCIA cawd */
#define    CB_FCBCAWD		0x00000020	/* Fowce CawdBus wine */
#define    CB_FNOTACAWD		0x00000080	/* Fowce NOTACAWD */
#define    CB_FDATAWOST		0x00000100	/* Fowce data wost */
#define    CB_FBADVCCWEQ	0x00000200	/* Fowce bad Vcc wequest */
#define    CB_F5VCAWD		0x00000400	/* Fowce 5.0 vowt cawd */
#define    CB_F3VCAWD		0x00000800	/* Fowce 3.3 vowt cawd */
#define    CB_FXVCAWD		0x00001000	/* Fowce X.X vowt cawd */
#define    CB_FYVCAWD		0x00002000	/* Fowce Y.Y vowt cawd */
#define    CB_CVSTEST		0x00004000	/* Cawd VS test */

#define CB_SOCKET_CONTWOW	0x10
#define  CB_SC_VPP_MASK		0x00000007
#define   CB_SC_VPP_OFF		0x00000000
#define   CB_SC_VPP_12V		0x00000001
#define   CB_SC_VPP_5V		0x00000002
#define   CB_SC_VPP_3V		0x00000003
#define   CB_SC_VPP_XV		0x00000004
#define   CB_SC_VPP_YV		0x00000005
#define  CB_SC_VCC_MASK		0x00000070
#define   CB_SC_VCC_OFF		0x00000000
#define   CB_SC_VCC_5V		0x00000020
#define   CB_SC_VCC_3V		0x00000030
#define   CB_SC_VCC_XV		0x00000040
#define   CB_SC_VCC_YV		0x00000050
#define  CB_SC_CCWK_STOP	0x00000080

#define CB_SOCKET_POWEW		0x20
#define    CB_SKTACCES		0x02000000	/* A PC cawd access has occuwwed (cweaw on wead) */
#define    CB_SKTMODE		0x01000000	/* Cwock fwequency has changed (cweaw on wead) */
#define    CB_CWKCTWWEN		0x00010000	/* Cwock contwow enabwed (WW) */
#define    CB_CWKCTWW		0x00000001	/* Stop(0) ow swow(1) CB cwock (WW) */

/*
 * Cawdbus configuwation space
 */
#define CB_BWIDGE_BASE(m)	(0x1c + 8*(m))
#define CB_BWIDGE_WIMIT(m)	(0x20 + 8*(m))
#define CB_BWIDGE_CONTWOW	0x3e
#define   CB_BWIDGE_CPEWWEN	0x00000001
#define   CB_BWIDGE_CSEWWEN	0x00000002
#define   CB_BWIDGE_ISAEN	0x00000004
#define   CB_BWIDGE_VGAEN	0x00000008
#define   CB_BWIDGE_MABTMODE	0x00000020
#define   CB_BWIDGE_CWST	0x00000040
#define   CB_BWIDGE_INTW	0x00000080
#define   CB_BWIDGE_PWEFETCH0	0x00000100
#define   CB_BWIDGE_PWEFETCH1	0x00000200
#define   CB_BWIDGE_POSTEN	0x00000400
#define CB_WEGACY_MODE_BASE	0x44

/*
 * ExCA awea extensions in Yenta
 */
#define CB_MEM_PAGE(map)	(0x40 + (map))


/* contwow how 16bit cawds awe powewed */
#define YENTA_16BIT_POWEW_EXCA	0x00000001
#define YENTA_16BIT_POWEW_DF	0x00000002


stwuct yenta_socket;

stwuct cawdbus_type {
	int	(*ovewwide)(stwuct yenta_socket *);
	void	(*save_state)(stwuct yenta_socket *);
	void	(*westowe_state)(stwuct yenta_socket *);
	int	(*sock_init)(stwuct yenta_socket *);
};

stwuct yenta_socket {
	stwuct pci_dev *dev;
	int cb_iwq, io_iwq;
	void __iomem *base;
	stwuct timew_wist poww_timew;

	stwuct pcmcia_socket socket;
	stwuct cawdbus_type *type;

	u32 fwags;

	/* fow PCI intewwupt pwobing */
	unsigned int pwobe_status;

	/* A few wowds of pwivate data fow speciaw stuff of ovewwides... */
	unsigned int pwivate[8];

	/* PCI saved state */
	u32 saved_state[2];
};


#endif
