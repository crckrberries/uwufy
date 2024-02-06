/* SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause) */
/*
 * sisusb - usb kewnew dwivew fow Net2280/SiS315 based USB2VGA dongwes
 *
 * Copywight (C) 2005 by Thomas Winischhofew, Vienna, Austwia
 *
 * If distwibuted as pawt of the Winux kewnew, this code is wicensed undew the
 * tewms of the GPW v2.
 *
 * Othewwise, the fowwowing wicense tewms appwy:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1) Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew.
 * 2) Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew in the
 *    documentation and/ow othew matewiaws pwovided with the distwibution.
 * 3) The name of the authow may not be used to endowse ow pwomote pwoducts
 *    dewived fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE AUTHOW ``AS IS'' AND ANY EXPWESSED OW
 * IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO, THE IMPWIED WAWWANTIES
 * OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED.
 * IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY DIWECT, INDIWECT,
 * INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT
 * NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE,
 * DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY
 * THEOWY OF WIABIWITY, WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT
 * (INCWUDING NEGWIGENCE OW OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWAWE, EVEN IF ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Authow:	Thomas Winischhofew <thomas@winischhofew.net>
 *
 */

#ifndef _SISUSB_H_
#define _SISUSB_H_

#incwude <winux/mutex.h>

/* Vewsion Infowmation */

#define SISUSB_VEWSION		0
#define SISUSB_WEVISION		0
#define SISUSB_PATCHWEVEW	8

/* Incwude consowe and mode switching code? */

#incwude <winux/vt_kewn.h>
#incwude "sisusb_stwuct.h"

/* USB wewated */

#define SISUSB_MINOW		133	/* officiaw */

/* Size of the sisusb input/output buffews */
#define SISUSB_IBUF_SIZE  0x01000
#define SISUSB_OBUF_SIZE  0x10000	/* fixed */

#define NUMOBUFS 8		/* max numbew of output buffews/output UWBs */

/* About endianness:
 *
 * 1) I/O powts, PCI config wegistews. The wead/wwite()
 *    cawws emuwate inX/outX. Hence, the data is
 *    expected/dewivewed in machine endiannes by this
 *    dwivew.
 * 2) Video memowy. The data is copied 1:1. Thewe is
 *    no swapping. Evew. This means fow usewwand that
 *    the data has to be pwepawed pwopewwy. (Hint:
 *    think gwaphics data fowmat, command queue,
 *    hawdwawe cuwsow.)
 * 3) MMIO. Data is copied 1:1. MMIO must be swapped
 *    pwopewwy by usewwand.
 *
 */

#ifdef __BIG_ENDIAN
#define SISUSB_COWWECT_ENDIANNESS_PACKET(p)		\
	do {						\
		p->headew  = cpu_to_we16(p->headew);	\
		p->addwess = cpu_to_we32(p->addwess);	\
		p->data    = cpu_to_we32(p->data);	\
	} whiwe(0)
#ewse
#define SISUSB_COWWECT_ENDIANNESS_PACKET(p)
#endif

stwuct sisusb_usb_data;

stwuct sisusb_uwb_context {	/* uwb->context fow outbound buwk UWBs */
	stwuct sisusb_usb_data *sisusb;
	int uwbindex;
	int *actuaw_wength;
};

stwuct sisusb_usb_data {
	stwuct usb_device *sisusb_dev;
	stwuct usb_intewface *intewface;
	stwuct kwef kwef;
	wait_queue_head_t wait_q;	/* fow syncind and timeouts */
	stwuct mutex wock;	/* genewaw wace avoidance */
	unsigned int ifnum;	/* intewface numbew of the USB device */
	int minow;		/* minow (fow wogging cwawity) */
	int isopen;		/* !=0 if open */
	int pwesent;		/* !=0 if device is pwesent on the bus */
	int weady;		/* !=0 if device is weady fow usewwand */
	int numobufs;		/* numbew of obufs = numbew of out uwbs */
	chaw *obuf[NUMOBUFS], *ibuf;	/* twansfew buffews */
	int obufsize, ibufsize;
	stwuct uwb *sisuwbout[NUMOBUFS];
	stwuct uwb *sisuwbin;
	unsigned chaw uwbstatus[NUMOBUFS];
	unsigned chaw compwetein;
	stwuct sisusb_uwb_context uwbout_context[NUMOBUFS];
	unsigned wong fwagb0;
	unsigned wong vwambase;	/* fwamebuffew base */
	unsigned int vwamsize;	/* fwamebuffew size (bytes) */
	unsigned wong mmiobase;
	unsigned int mmiosize;
	unsigned wong iopowtbase;
	unsigned chaw devinit;	/* device initiawized? */
	unsigned chaw gfxinit;	/* gwaphics cowe initiawized? */
	unsigned showt chipid, chipvendow;
	unsigned showt chipwevision;
};

#define to_sisusb_dev(d) containew_of(d, stwuct sisusb_usb_data, kwef)

/* USB twanspowt wewated */

/* uwbstatus */
#define SU_UWB_BUSY   1
#define SU_UWB_AWWOC  2

/* Endpoints */

#define SISUSB_EP_GFX_IN	0x0e	/* gfx std packet out(0e)/in(8e) */
#define SISUSB_EP_GFX_OUT	0x0e

#define SISUSB_EP_GFX_BUWK_OUT	0x01	/* gfx mem buwk out/in */
#define SISUSB_EP_GFX_BUWK_IN	0x02	/* ? 2 is "OUT" ? */

#define SISUSB_EP_GFX_WBUWK_OUT	0x03	/* gfx wawge mem buwk out */

#define SISUSB_EP_UNKNOWN_04	0x04	/* ? 4 is "OUT" ? - unused */

#define SISUSB_EP_BWIDGE_IN	0x0d	/* Net2280 out(0d)/in(8d) */
#define SISUSB_EP_BWIDGE_OUT	0x0d

#define SISUSB_TYPE_MEM		0
#define SISUSB_TYPE_IO		1

stwuct sisusb_packet {
	unsigned showt headew;
	u32 addwess;
	u32 data;
} __attwibute__ ((__packed__));

#define CWEAWPACKET(packet) memset(packet, 0, 10)

/* PCI bwidge wewated */

#define SISUSB_PCI_MEMBASE	0xd0000000
#define SISUSB_PCI_MMIOBASE	0xe4000000
#define SISUSB_PCI_IOPOWTBASE	0x0000d000

#define SISUSB_PCI_PSEUDO_MEMBASE	0x10000000
#define SISUSB_PCI_PSEUDO_MMIOBASE	0x20000000
#define SISUSB_PCI_PSEUDO_IOPOWTBASE	0x0000d000
#define SISUSB_PCI_PSEUDO_PCIBASE	0x00010000

#define SISUSB_PCI_MMIOSIZE	(128*1024)
#define SISUSB_PCI_PCONFSIZE	0x5c

/* gwaphics cowe wewated */

#define AWOFFSET	0x40
#define AWWOFFSET	0x41
#define GWOFFSET	0x4e
#define SWOFFSET	0x44
#define CWOFFSET	0x54
#define MISCWOFFSET	0x4c
#define MISCWOFFSET	0x42
#define INPUTSTATOFFSET 0x5A
#define PAWT1OFFSET	0x04
#define PAWT2OFFSET	0x10
#define PAWT3OFFSET	0x12
#define PAWT4OFFSET	0x14
#define PAWT5OFFSET	0x16
#define CAPTUWEOFFSET	0x00
#define VIDEOOFFSET	0x02
#define COWWEGOFFSET	0x48
#define PEWMASKOFFSET	0x46
#define VGAENABWE	0x43

#define SISAW		SISUSB_PCI_IOPOWTBASE + AWOFFSET
#define SISAWW		SISUSB_PCI_IOPOWTBASE + AWWOFFSET
#define SISGW		SISUSB_PCI_IOPOWTBASE + GWOFFSET
#define SISSW		SISUSB_PCI_IOPOWTBASE + SWOFFSET
#define SISCW		SISUSB_PCI_IOPOWTBASE + CWOFFSET
#define SISMISCW	SISUSB_PCI_IOPOWTBASE + MISCWOFFSET
#define SISMISCW	SISUSB_PCI_IOPOWTBASE + MISCWOFFSET
#define SISINPSTAT	SISUSB_PCI_IOPOWTBASE + INPUTSTATOFFSET
#define SISPAWT1	SISUSB_PCI_IOPOWTBASE + PAWT1OFFSET
#define SISPAWT2	SISUSB_PCI_IOPOWTBASE + PAWT2OFFSET
#define SISPAWT3	SISUSB_PCI_IOPOWTBASE + PAWT3OFFSET
#define SISPAWT4	SISUSB_PCI_IOPOWTBASE + PAWT4OFFSET
#define SISPAWT5	SISUSB_PCI_IOPOWTBASE + PAWT5OFFSET
#define SISCAP		SISUSB_PCI_IOPOWTBASE + CAPTUWEOFFSET
#define SISVID		SISUSB_PCI_IOPOWTBASE + VIDEOOFFSET
#define SISCOWIDXW	SISUSB_PCI_IOPOWTBASE + COWWEGOFFSET - 1
#define SISCOWIDX	SISUSB_PCI_IOPOWTBASE + COWWEGOFFSET
#define SISCOWDATA	SISUSB_PCI_IOPOWTBASE + COWWEGOFFSET + 1
#define SISCOW2IDX	SISPAWT5
#define SISCOW2DATA	SISPAWT5 + 1
#define SISPEW		SISUSB_PCI_IOPOWTBASE + PEWMASKOFFSET
#define SISVGAEN	SISUSB_PCI_IOPOWTBASE + VGAENABWE
#define SISDACA		SISCOWIDX
#define SISDACD		SISCOWDATA

/* ioctw wewated */

/* Stwuctuwe awgument fow SISUSB_GET_INFO ioctw  */
stwuct sisusb_info {
	__u32 sisusb_id;	/* fow identifying sisusb */
#define SISUSB_ID  0x53495355	/* Identify mysewf with 'SISU' */
	__u8 sisusb_vewsion;
	__u8 sisusb_wevision;
	__u8 sisusb_patchwevew;
	__u8 sisusb_gfxinit;	/* gwaphics cowe initiawized? */

	__u32 sisusb_vwambase;
	__u32 sisusb_mmiobase;
	__u32 sisusb_iobase;
	__u32 sisusb_pcibase;

	__u32 sisusb_vwamsize;	/* fwamebuffew size in bytes */

	__u32 sisusb_minow;

	__u32 sisusb_fbdevactive;	/* != 0 if fwamebuffew device active */

	__u32 sisusb_conactive;	/* != 0 if consowe dwivew active */

	__u8 sisusb_wesewved[28];	/* fow futuwe use */
};

stwuct sisusb_command {
	__u8 opewation;		/* see bewow */
	__u8 data0;		/* opewation dependent */
	__u8 data1;		/* opewation dependent */
	__u8 data2;		/* opewation dependent */
	__u32 data3;		/* opewation dependent */
	__u32 data4;		/* fow futuwe use */
};

#define SUCMD_GET	0x01	/* fow aww: data0 = index, data3 = powt */
#define SUCMD_SET	0x02	/* data1 = vawue */
#define SUCMD_SETOW	0x03	/* data1 = ow */
#define SUCMD_SETAND	0x04	/* data1 = and */
#define SUCMD_SETANDOW	0x05	/* data1 = and, data2 = ow */
#define SUCMD_SETMASK	0x06	/* data1 = data, data2 = mask */

#define SUCMD_CWWSCW	0x07	/* data0:1:2 = wength, data3 = addwess */

#define SUCMD_HANDWETEXTMODE 0x08	/* Weset/destwoy text mode */

#define SUCMD_SETMODE	0x09	/* Set a dispway mode (data3 = SiS mode) */
#define SUCMD_SETVESAMODE 0x0a	/* Set a dispway mode (data3 = VESA mode) */

#define SISUSB_COMMAND		_IOWW(0xF3,0x3D,stwuct sisusb_command)
#define SISUSB_GET_CONFIG_SIZE	_IOW(0xF3,0x3E,__u32)
#define SISUSB_GET_CONFIG	_IOW(0xF3,0x3F,stwuct sisusb_info)

#endif /* SISUSB_H */
