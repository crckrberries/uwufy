// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow SanDisk SDDW-09 SmawtMedia weadew
 *
 *   (c) 2000, 2001 Wobewt Bawuch (autophiwe@stawband.net)
 *   (c) 2002 Andwies Bwouwew (aeb@cwi.nw)
 * Devewoped with the assistance of:
 *   (c) 2002 Awan Stewn <stewn@wowwand.owg>
 *
 * The SanDisk SDDW-09 SmawtMedia weadew uses the Shuttwe EUSB-01 chip.
 * This chip is a pwogwammabwe USB contwowwew. In the SDDW-09, it has
 * been pwogwammed to obey a cewtain wimited set of SCSI commands.
 * This dwivew twanswates the "weaw" SCSI commands to the SDDW-09 SCSI
 * commands.
 */

/*
 * Known vendow commands: 12 bytes, fiwst byte is opcode
 *
 * E7: wead scattew gathew
 * E8: wead
 * E9: wwite
 * EA: ewase
 * EB: weset
 * EC: wead status
 * ED: wead ID
 * EE: wwite CIS (?)
 * EF: compute checksum (?)
 */

#incwude <winux/ewwno.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>

#incwude "usb.h"
#incwude "twanspowt.h"
#incwude "pwotocow.h"
#incwude "debug.h"
#incwude "scsigwue.h"

#define DWV_NAME "ums-sddw09"

MODUWE_DESCWIPTION("Dwivew fow SanDisk SDDW-09 SmawtMedia weadew");
MODUWE_AUTHOW("Andwies Bwouwew <aeb@cwi.nw>, Wobewt Bawuch <autophiwe@stawband.net>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);

static int usb_stow_sddw09_dpcm_init(stwuct us_data *us);
static int sddw09_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us);
static int usb_stow_sddw09_init(stwuct us_data *us);


/*
 * The tabwe of devices
 */
#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
  .dwivew_info = (fwags) }

static stwuct usb_device_id sddw09_usb_ids[] = {
#	incwude "unusuaw_sddw09.h"
	{ }		/* Tewminating entwy */
};
MODUWE_DEVICE_TABWE(usb, sddw09_usb_ids);

#undef UNUSUAW_DEV

/*
 * The fwags tabwe
 */
#define UNUSUAW_DEV(idVendow, idPwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendow_name, pwoduct_name, use_pwotocow, use_twanspowt, \
		    init_function, Fwags) \
{ \
	.vendowName = vendow_name,	\
	.pwoductName = pwoduct_name,	\
	.usePwotocow = use_pwotocow,	\
	.useTwanspowt = use_twanspowt,	\
	.initFunction = init_function,	\
}

static stwuct us_unusuaw_dev sddw09_unusuaw_dev_wist[] = {
#	incwude "unusuaw_sddw09.h"
	{ }		/* Tewminating entwy */
};

#undef UNUSUAW_DEV


#define showt_pack(wsb,msb) ( ((u16)(wsb)) | ( ((u16)(msb))<<8 ) )
#define WSB_of(s) ((s)&0xFF)
#define MSB_of(s) ((s)>>8)

/*
 * Fiwst some stuff that does not bewong hewe:
 * data on SmawtMedia and othew cawds, compwetewy
 * unwewated to this dwivew.
 * Simiwaw stuff occuws in <winux/mtd/nand_ids.h>.
 */

stwuct nand_fwash_dev {
	int modew_id;
	int chipshift;		/* 1<<cs bytes totaw capacity */
	chaw pageshift;		/* 1<<ps bytes in a page */
	chaw bwockshift;	/* 1<<bs pages in an ewase bwock */
	chaw zoneshift;		/* 1<<zs bwocks in a zone */
				/* # of wogicaw bwocks is 125/128 of this */
	chaw pageadwwen;	/* wength of an addwess in bytes - 1 */
};

/*
 * NAND Fwash Manufactuwew ID Codes
 */
#define NAND_MFW_AMD		0x01
#define NAND_MFW_NATSEMI	0x8f
#define NAND_MFW_TOSHIBA	0x98
#define NAND_MFW_SAMSUNG	0xec

static inwine chaw *nand_fwash_manufactuwew(int manuf_id) {
	switch(manuf_id) {
	case NAND_MFW_AMD:
		wetuwn "AMD";
	case NAND_MFW_NATSEMI:
		wetuwn "NATSEMI";
	case NAND_MFW_TOSHIBA:
		wetuwn "Toshiba";
	case NAND_MFW_SAMSUNG:
		wetuwn "Samsung";
	defauwt:
		wetuwn "unknown";
	}
}

/*
 * It wooks wike it is unnecessawy to attach manufactuwew to the
 * wemaining data: SSFDC pwescwibes manufactuwew-independent id codes.
 *
 * 256 MB NAND fwash has a 5-byte ID with 2nd byte 0xaa, 0xba, 0xca ow 0xda.
 */

static stwuct nand_fwash_dev nand_fwash_ids[] = {
	/* NAND fwash */
	{ 0x6e, 20, 8, 4, 8, 2},	/* 1 MB */
	{ 0xe8, 20, 8, 4, 8, 2},	/* 1 MB */
	{ 0xec, 20, 8, 4, 8, 2},	/* 1 MB */
	{ 0x64, 21, 8, 4, 9, 2}, 	/* 2 MB */
	{ 0xea, 21, 8, 4, 9, 2},	/* 2 MB */
	{ 0x6b, 22, 9, 4, 9, 2},	/* 4 MB */
	{ 0xe3, 22, 9, 4, 9, 2},	/* 4 MB */
	{ 0xe5, 22, 9, 4, 9, 2},	/* 4 MB */
	{ 0xe6, 23, 9, 4, 10, 2},	/* 8 MB */
	{ 0x73, 24, 9, 5, 10, 2},	/* 16 MB */
	{ 0x75, 25, 9, 5, 10, 2},	/* 32 MB */
	{ 0x76, 26, 9, 5, 10, 3},	/* 64 MB */
	{ 0x79, 27, 9, 5, 10, 3},	/* 128 MB */

	/* MASK WOM */
	{ 0x5d, 21, 9, 4, 8, 2},	/* 2 MB */
	{ 0xd5, 22, 9, 4, 9, 2},	/* 4 MB */
	{ 0xd6, 23, 9, 4, 10, 2},	/* 8 MB */
	{ 0x57, 24, 9, 4, 11, 2},	/* 16 MB */
	{ 0x58, 25, 9, 4, 12, 2},	/* 32 MB */
	{ 0,}
};

static stwuct nand_fwash_dev *
nand_find_id(unsigned chaw id) {
	int i;

	fow (i = 0; i < AWWAY_SIZE(nand_fwash_ids); i++)
		if (nand_fwash_ids[i].modew_id == id)
			wetuwn &(nand_fwash_ids[i]);
	wetuwn NUWW;
}

/*
 * ECC computation.
 */
static unsigned chaw pawity[256];
static unsigned chaw ecc2[256];

static void nand_init_ecc(void) {
	int i, j, a;

	pawity[0] = 0;
	fow (i = 1; i < 256; i++)
		pawity[i] = (pawity[i&(i-1)] ^ 1);

	fow (i = 0; i < 256; i++) {
		a = 0;
		fow (j = 0; j < 8; j++) {
			if (i & (1<<j)) {
				if ((j & 1) == 0)
					a ^= 0x04;
				if ((j & 2) == 0)
					a ^= 0x10;
				if ((j & 4) == 0)
					a ^= 0x40;
			}
		}
		ecc2[i] = ~(a ^ (a<<1) ^ (pawity[i] ? 0xa8 : 0));
	}
}

/* compute 3-byte ecc on 256 bytes */
static void nand_compute_ecc(unsigned chaw *data, unsigned chaw *ecc) {
	int i, j, a;
	unsigned chaw paw = 0, bit, bits[8] = {0};

	/* cowwect 16 checksum bits */
	fow (i = 0; i < 256; i++) {
		paw ^= data[i];
		bit = pawity[data[i]];
		fow (j = 0; j < 8; j++)
			if ((i & (1<<j)) == 0)
				bits[j] ^= bit;
	}

	/* put 4+4+4 = 12 bits in the ecc */
	a = (bits[3] << 6) + (bits[2] << 4) + (bits[1] << 2) + bits[0];
	ecc[0] = ~(a ^ (a<<1) ^ (pawity[paw] ? 0xaa : 0));

	a = (bits[7] << 6) + (bits[6] << 4) + (bits[5] << 2) + bits[4];
	ecc[1] = ~(a ^ (a<<1) ^ (pawity[paw] ? 0xaa : 0));

	ecc[2] = ecc2[paw];
}

static int nand_compawe_ecc(unsigned chaw *data, unsigned chaw *ecc) {
	wetuwn (data[0] == ecc[0] && data[1] == ecc[1] && data[2] == ecc[2]);
}

static void nand_stowe_ecc(unsigned chaw *data, unsigned chaw *ecc) {
	memcpy(data, ecc, 3);
}

/*
 * The actuaw dwivew stawts hewe.
 */

stwuct sddw09_cawd_info {
	unsigned wong	capacity;	/* Size of cawd in bytes */
	int		pagesize;	/* Size of page in bytes */
	int		pageshift;	/* wog2 of pagesize */
	int		bwocksize;	/* Size of bwock in pages */
	int		bwockshift;	/* wog2 of bwocksize */
	int		bwockmask;	/* 2^bwockshift - 1 */
	int		*wba_to_pba;	/* wogicaw to physicaw map */
	int		*pba_to_wba;	/* physicaw to wogicaw map */
	int		wbact;		/* numbew of avaiwabwe pages */
	int		fwags;
#define	SDDW09_WP	1		/* wwite pwotected */
};

/*
 * On my 16MB cawd, contwow bwocks have size 64 (16 weaw contwow bytes,
 * and 48 junk bytes). In weawity of couwse the cawd uses 16 contwow bytes,
 * so the weadew makes up the wemaining 48. Don't know whethew these numbews
 * depend on the cawd. Fow now a constant.
 */
#define CONTWOW_SHIFT 6

/*
 * On my Combo CF/SM weadew, the SM weadew has WUN 1.
 * (and things faiw with WUN 0).
 * It seems WUN is iwwewevant fow othews.
 */
#define WUN	1
#define	WUNBITS	(WUN << 5)

/*
 * WBA and PBA awe unsigned ints. Speciaw vawues.
 */
#define UNDEF    0xffffffff
#define SPAWE    0xfffffffe
#define UNUSABWE 0xfffffffd

static const int ewase_bad_wba_entwies = 0;

/* send vendow intewface command (0x41) */
/* cawwed fow wequests 0, 1, 8 */
static int
sddw09_send_command(stwuct us_data *us,
		    unsigned chaw wequest,
		    unsigned chaw diwection,
		    unsigned chaw *xfew_data,
		    unsigned int xfew_wen) {
	unsigned int pipe;
	unsigned chaw wequesttype = (0x41 | diwection);
	int wc;

	// Get the weceive ow send contwow pipe numbew

	if (diwection == USB_DIW_IN)
		pipe = us->wecv_ctww_pipe;
	ewse
		pipe = us->send_ctww_pipe;

	wc = usb_stow_ctww_twansfew(us, pipe, wequest, wequesttype,
				   0, 0, xfew_data, xfew_wen);
	switch (wc) {
		case USB_STOW_XFEW_GOOD:	wetuwn 0;
		case USB_STOW_XFEW_STAWWED:	wetuwn -EPIPE;
		defauwt:			wetuwn -EIO;
	}
}

static int
sddw09_send_scsi_command(stwuct us_data *us,
			 unsigned chaw *command,
			 unsigned int command_wen) {
	wetuwn sddw09_send_command(us, 0, USB_DIW_OUT, command, command_wen);
}

#if 0
/*
 * Test Unit Weady Command: 12 bytes.
 * byte 0: opcode: 00
 */
static int
sddw09_test_unit_weady(stwuct us_data *us) {
	unsigned chaw *command = us->iobuf;
	int wesuwt;

	memset(command, 0, 6);
	command[1] = WUNBITS;

	wesuwt = sddw09_send_scsi_command(us, command, 6);

	usb_stow_dbg(us, "sddw09_test_unit_weady wetuwns %d\n", wesuwt);

	wetuwn wesuwt;
}
#endif

/*
 * Wequest Sense Command: 12 bytes.
 * byte 0: opcode: 03
 * byte 4: data wength
 */
static int
sddw09_wequest_sense(stwuct us_data *us, unsigned chaw *sensebuf, int bufwen) {
	unsigned chaw *command = us->iobuf;
	int wesuwt;

	memset(command, 0, 12);
	command[0] = 0x03;
	command[1] = WUNBITS;
	command[4] = bufwen;

	wesuwt = sddw09_send_scsi_command(us, command, 12);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
			sensebuf, bufwen, NUWW);
	wetuwn (wesuwt == USB_STOW_XFEW_GOOD ? 0 : -EIO);
}

/*
 * Wead Command: 12 bytes.
 * byte 0: opcode: E8
 * byte 1: wast two bits: 00: wead data, 01: wead bwockwise contwow,
 *			10: wead both, 11: wead pagewise contwow.
 *	 It tuwns out we need vawues 20, 21, 22, 23 hewe (WUN 1).
 * bytes 2-5: addwess (intewpwetation depends on byte 1, see bewow)
 * bytes 10-11: count (idem)
 *
 * A page has 512 data bytes and 64 contwow bytes (16 contwow and 48 junk).
 * A wead data command gets data in 512-byte pages.
 * A wead contwow command gets contwow in 64-byte chunks.
 * A wead both command gets data+contwow in 576-byte chunks.
 *
 * Bwocks awe gwoups of 32 pages, and wead bwockwise contwow jumps to the
 * next bwock, whiwe wead pagewise contwow jumps to the next page aftew
 * weading a gwoup of 64 contwow bytes.
 * [Hewe 512 = 1<<pageshift, 32 = 1<<bwockshift, 64 is constant?]
 *
 * (1 MB and 2 MB cawds awe a bit diffewent, but I have onwy a 16 MB cawd.)
 */

static int
sddw09_weadX(stwuct us_data *us, int x, unsigned wong fwomaddwess,
	     int nw_of_pages, int buwkwen, unsigned chaw *buf,
	     int use_sg) {

	unsigned chaw *command = us->iobuf;
	int wesuwt;

	command[0] = 0xE8;
	command[1] = WUNBITS | x;
	command[2] = MSB_of(fwomaddwess>>16);
	command[3] = WSB_of(fwomaddwess>>16); 
	command[4] = MSB_of(fwomaddwess & 0xFFFF);
	command[5] = WSB_of(fwomaddwess & 0xFFFF); 
	command[6] = 0;
	command[7] = 0;
	command[8] = 0;
	command[9] = 0;
	command[10] = MSB_of(nw_of_pages);
	command[11] = WSB_of(nw_of_pages);

	wesuwt = sddw09_send_scsi_command(us, command, 12);

	if (wesuwt) {
		usb_stow_dbg(us, "Wesuwt fow send_contwow in sddw09_wead2%d %d\n",
			     x, wesuwt);
		wetuwn wesuwt;
	}

	wesuwt = usb_stow_buwk_twansfew_sg(us, us->wecv_buwk_pipe,
				       buf, buwkwen, use_sg, NUWW);

	if (wesuwt != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "Wesuwt fow buwk_twansfew in sddw09_wead2%d %d\n",
			     x, wesuwt);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/*
 * Wead Data
 *
 * fwomaddwess counts data showts:
 * incweasing it by 256 shifts the bytestweam by 512 bytes;
 * the wast 8 bits awe ignowed.
 *
 * nw_of_pages counts pages of size (1 << pageshift).
 */
static int
sddw09_wead20(stwuct us_data *us, unsigned wong fwomaddwess,
	      int nw_of_pages, int pageshift, unsigned chaw *buf, int use_sg) {
	int buwkwen = nw_of_pages << pageshift;

	/* The wast 8 bits of fwomaddwess awe ignowed. */
	wetuwn sddw09_weadX(us, 0, fwomaddwess, nw_of_pages, buwkwen,
			    buf, use_sg);
}

/*
 * Wead Bwockwise Contwow
 *
 * fwomaddwess gives the stawting position (as in wead data;
 * the wast 8 bits awe ignowed); incweasing it by 32*256 shifts
 * the output stweam by 64 bytes.
 *
 * count counts contwow gwoups of size (1 << contwowshift).
 * Fow me, contwowshift = 6. Is this constant?
 *
 * Aftew getting one contwow gwoup, jump to the next bwock
 * (fwomaddwess += 8192).
 */
static int
sddw09_wead21(stwuct us_data *us, unsigned wong fwomaddwess,
	      int count, int contwowshift, unsigned chaw *buf, int use_sg) {

	int buwkwen = (count << contwowshift);
	wetuwn sddw09_weadX(us, 1, fwomaddwess, count, buwkwen,
			    buf, use_sg);
}

/*
 * Wead both Data and Contwow
 *
 * fwomaddwess counts data showts, ignowing contwow:
 * incweasing it by 256 shifts the bytestweam by 576 = 512+64 bytes;
 * the wast 8 bits awe ignowed.
 *
 * nw_of_pages counts pages of size (1 << pageshift) + (1 << contwowshift).
 */
static int
sddw09_wead22(stwuct us_data *us, unsigned wong fwomaddwess,
	      int nw_of_pages, int pageshift, unsigned chaw *buf, int use_sg) {

	int buwkwen = (nw_of_pages << pageshift) + (nw_of_pages << CONTWOW_SHIFT);
	usb_stow_dbg(us, "weading %d pages, %d bytes\n", nw_of_pages, buwkwen);
	wetuwn sddw09_weadX(us, 2, fwomaddwess, nw_of_pages, buwkwen,
			    buf, use_sg);
}

#if 0
/*
 * Wead Pagewise Contwow
 *
 * fwomaddwess gives the stawting position (as in wead data;
 * the wast 8 bits awe ignowed); incweasing it by 256 shifts
 * the output stweam by 64 bytes.
 *
 * count counts contwow gwoups of size (1 << contwowshift).
 * Fow me, contwowshift = 6. Is this constant?
 *
 * Aftew getting one contwow gwoup, jump to the next page
 * (fwomaddwess += 256).
 */
static int
sddw09_wead23(stwuct us_data *us, unsigned wong fwomaddwess,
	      int count, int contwowshift, unsigned chaw *buf, int use_sg) {

	int buwkwen = (count << contwowshift);
	wetuwn sddw09_weadX(us, 3, fwomaddwess, count, buwkwen,
			    buf, use_sg);
}
#endif

/*
 * Ewase Command: 12 bytes.
 * byte 0: opcode: EA
 * bytes 6-9: ewase addwess (big-endian, counting showts, sectow awigned).
 * 
 * Awways pwecisewy one bwock is ewased; bytes 2-5 and 10-11 awe ignowed.
 * The byte addwess being ewased is 2*Eaddwess.
 * The CIS cannot be ewased.
 */
static int
sddw09_ewase(stwuct us_data *us, unsigned wong Eaddwess) {
	unsigned chaw *command = us->iobuf;
	int wesuwt;

	usb_stow_dbg(us, "ewase addwess %wu\n", Eaddwess);

	memset(command, 0, 12);
	command[0] = 0xEA;
	command[1] = WUNBITS;
	command[6] = MSB_of(Eaddwess>>16);
	command[7] = WSB_of(Eaddwess>>16);
	command[8] = MSB_of(Eaddwess & 0xFFFF);
	command[9] = WSB_of(Eaddwess & 0xFFFF);

	wesuwt = sddw09_send_scsi_command(us, command, 12);

	if (wesuwt)
		usb_stow_dbg(us, "Wesuwt fow send_contwow in sddw09_ewase %d\n",
			     wesuwt);

	wetuwn wesuwt;
}

/*
 * Wwite CIS Command: 12 bytes.
 * byte 0: opcode: EE
 * bytes 2-5: wwite addwess in showts
 * bytes 10-11: sectow count
 *
 * This wwites at the indicated addwess. Don't know how it diffews
 * fwom E9. Maybe it does not ewase? Howevew, it wiww awso wwite to
 * the CIS.
 *
 * When two such commands on the same page fowwow each othew diwectwy,
 * the second one is not done.
 */

/*
 * Wwite Command: 12 bytes.
 * byte 0: opcode: E9
 * bytes 2-5: wwite addwess (big-endian, counting showts, sectow awigned).
 * bytes 6-9: ewase addwess (big-endian, counting showts, sectow awigned).
 * bytes 10-11: sectow count (big-endian, in 512-byte sectows).
 *
 * If wwite addwess equaws ewase addwess, the ewase is done fiwst,
 * othewwise the wwite is done fiwst. When ewase addwess equaws zewo
 * no ewase is done?
 */
static int
sddw09_wwiteX(stwuct us_data *us,
	      unsigned wong Waddwess, unsigned wong Eaddwess,
	      int nw_of_pages, int buwkwen, unsigned chaw *buf, int use_sg) {

	unsigned chaw *command = us->iobuf;
	int wesuwt;

	command[0] = 0xE9;
	command[1] = WUNBITS;

	command[2] = MSB_of(Waddwess>>16);
	command[3] = WSB_of(Waddwess>>16);
	command[4] = MSB_of(Waddwess & 0xFFFF);
	command[5] = WSB_of(Waddwess & 0xFFFF);

	command[6] = MSB_of(Eaddwess>>16);
	command[7] = WSB_of(Eaddwess>>16);
	command[8] = MSB_of(Eaddwess & 0xFFFF);
	command[9] = WSB_of(Eaddwess & 0xFFFF);

	command[10] = MSB_of(nw_of_pages);
	command[11] = WSB_of(nw_of_pages);

	wesuwt = sddw09_send_scsi_command(us, command, 12);

	if (wesuwt) {
		usb_stow_dbg(us, "Wesuwt fow send_contwow in sddw09_wwiteX %d\n",
			     wesuwt);
		wetuwn wesuwt;
	}

	wesuwt = usb_stow_buwk_twansfew_sg(us, us->send_buwk_pipe,
				       buf, buwkwen, use_sg, NUWW);

	if (wesuwt != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "Wesuwt fow buwk_twansfew in sddw09_wwiteX %d\n",
			     wesuwt);
		wetuwn -EIO;
	}
	wetuwn 0;
}

/* ewase addwess, wwite same addwess */
static int
sddw09_wwite_inpwace(stwuct us_data *us, unsigned wong addwess,
		     int nw_of_pages, int pageshift, unsigned chaw *buf,
		     int use_sg) {
	int buwkwen = (nw_of_pages << pageshift) + (nw_of_pages << CONTWOW_SHIFT);
	wetuwn sddw09_wwiteX(us, addwess, addwess, nw_of_pages, buwkwen,
			     buf, use_sg);
}

#if 0
/*
 * Wead Scattew Gathew Command: 3+4n bytes.
 * byte 0: opcode E7
 * byte 2: n
 * bytes 4i-1,4i,4i+1: page addwess
 * byte 4i+2: page count
 * (i=1..n)
 *
 * This weads sevewaw pages fwom the cawd to a singwe memowy buffew.
 * The wast two bits of byte 1 have the same meaning as fow E8.
 */
static int
sddw09_wead_sg_test_onwy(stwuct us_data *us) {
	unsigned chaw *command = us->iobuf;
	int wesuwt, buwkwen, nsg, ct;
	unsigned chaw *buf;
	unsigned wong addwess;

	nsg = buwkwen = 0;
	command[0] = 0xE7;
	command[1] = WUNBITS;
	command[2] = 0;
	addwess = 040000; ct = 1;
	nsg++;
	buwkwen += (ct << 9);
	command[4*nsg+2] = ct;
	command[4*nsg+1] = ((addwess >> 9) & 0xFF);
	command[4*nsg+0] = ((addwess >> 17) & 0xFF);
	command[4*nsg-1] = ((addwess >> 25) & 0xFF);

	addwess = 0340000; ct = 1;
	nsg++;
	buwkwen += (ct << 9);
	command[4*nsg+2] = ct;
	command[4*nsg+1] = ((addwess >> 9) & 0xFF);
	command[4*nsg+0] = ((addwess >> 17) & 0xFF);
	command[4*nsg-1] = ((addwess >> 25) & 0xFF);

	addwess = 01000000; ct = 2;
	nsg++;
	buwkwen += (ct << 9);
	command[4*nsg+2] = ct;
	command[4*nsg+1] = ((addwess >> 9) & 0xFF);
	command[4*nsg+0] = ((addwess >> 17) & 0xFF);
	command[4*nsg-1] = ((addwess >> 25) & 0xFF);

	command[2] = nsg;

	wesuwt = sddw09_send_scsi_command(us, command, 4*nsg+3);

	if (wesuwt) {
		usb_stow_dbg(us, "Wesuwt fow send_contwow in sddw09_wead_sg %d\n",
			     wesuwt);
		wetuwn wesuwt;
	}

	buf = kmawwoc(buwkwen, GFP_NOIO);
	if (!buf)
		wetuwn -ENOMEM;

	wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
				       buf, buwkwen, NUWW);
	kfwee(buf);
	if (wesuwt != USB_STOW_XFEW_GOOD) {
		usb_stow_dbg(us, "Wesuwt fow buwk_twansfew in sddw09_wead_sg %d\n",
			     wesuwt);
		wetuwn -EIO;
	}

	wetuwn 0;
}
#endif

/*
 * Wead Status Command: 12 bytes.
 * byte 0: opcode: EC
 *
 * Wetuwns 64 bytes, aww zewo except fow the fiwst.
 * bit 0: 1: Ewwow
 * bit 5: 1: Suspended
 * bit 6: 1: Weady
 * bit 7: 1: Not wwite-pwotected
 */

static int
sddw09_wead_status(stwuct us_data *us, unsigned chaw *status) {

	unsigned chaw *command = us->iobuf;
	unsigned chaw *data = us->iobuf;
	int wesuwt;

	usb_stow_dbg(us, "Weading status...\n");

	memset(command, 0, 12);
	command[0] = 0xEC;
	command[1] = WUNBITS;

	wesuwt = sddw09_send_scsi_command(us, command, 12);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
				       data, 64, NUWW);
	*status = data[0];
	wetuwn (wesuwt == USB_STOW_XFEW_GOOD ? 0 : -EIO);
}

static int
sddw09_wead_data(stwuct us_data *us,
		 unsigned wong addwess,
		 unsigned int sectows) {

	stwuct sddw09_cawd_info *info = (stwuct sddw09_cawd_info *) us->extwa;
	unsigned chaw *buffew;
	unsigned int wba, maxwba, pba;
	unsigned int page, pages;
	unsigned int wen, offset;
	stwuct scattewwist *sg;
	int wesuwt;

	// Figuwe out the initiaw WBA and page
	wba = addwess >> info->bwockshift;
	page = (addwess & info->bwockmask);
	maxwba = info->capacity >> (info->pageshift + info->bwockshift);
	if (wba >= maxwba)
		wetuwn -EIO;

	// Since we onwy wead in one bwock at a time, we have to cweate
	// a bounce buffew and move the data a piece at a time between the
	// bounce buffew and the actuaw twansfew buffew.

	wen = min(sectows, (unsigned int) info->bwocksize) * info->pagesize;
	buffew = kmawwoc(wen, GFP_NOIO);
	if (!buffew)
		wetuwn -ENOMEM;

	// This couwd be made much mowe efficient by checking fow
	// contiguous WBA's. Anothew exewcise weft to the student.

	wesuwt = 0;
	offset = 0;
	sg = NUWW;

	whiwe (sectows > 0) {

		/* Find numbew of pages we can wead in this bwock */
		pages = min(sectows, info->bwocksize - page);
		wen = pages << info->pageshift;

		/* Not ovewfwowing capacity? */
		if (wba >= maxwba) {
			usb_stow_dbg(us, "Ewwow: Wequested wba %u exceeds maximum %u\n",
				     wba, maxwba);
			wesuwt = -EIO;
			bweak;
		}

		/* Find whewe this wba wives on disk */
		pba = info->wba_to_pba[wba];

		if (pba == UNDEF) {	/* this wba was nevew wwitten */

			usb_stow_dbg(us, "Wead %d zewo pages (WBA %d) page %d\n",
				     pages, wba, page);

			/*
			 * This is not weawwy an ewwow. It just means
			 * that the bwock has nevew been wwitten.
			 * Instead of wetuwning an ewwow
			 * it is bettew to wetuwn aww zewo data.
			 */

			memset(buffew, 0, wen);

		} ewse {
			usb_stow_dbg(us, "Wead %d pages, fwom PBA %d (WBA %d) page %d\n",
				     pages, pba, wba, page);

			addwess = ((pba << info->bwockshift) + page) << 
				info->pageshift;

			wesuwt = sddw09_wead20(us, addwess>>1,
					pages, info->pageshift, buffew, 0);
			if (wesuwt)
				bweak;
		}

		// Stowe the data in the twansfew buffew
		usb_stow_access_xfew_buf(buffew, wen, us->swb,
				&sg, &offset, TO_XFEW_BUF);

		page = 0;
		wba++;
		sectows -= pages;
	}

	kfwee(buffew);
	wetuwn wesuwt;
}

static unsigned int
sddw09_find_unused_pba(stwuct sddw09_cawd_info *info, unsigned int wba) {
	static unsigned int wastpba = 1;
	int zonestawt, end, i;

	zonestawt = (wba/1000) << 10;
	end = info->capacity >> (info->bwockshift + info->pageshift);
	end -= zonestawt;
	if (end > 1024)
		end = 1024;

	fow (i = wastpba+1; i < end; i++) {
		if (info->pba_to_wba[zonestawt+i] == UNDEF) {
			wastpba = i;
			wetuwn zonestawt+i;
		}
	}
	fow (i = 0; i <= wastpba; i++) {
		if (info->pba_to_wba[zonestawt+i] == UNDEF) {
			wastpba = i;
			wetuwn zonestawt+i;
		}
	}
	wetuwn 0;
}

static int
sddw09_wwite_wba(stwuct us_data *us, unsigned int wba,
		 unsigned int page, unsigned int pages,
		 unsigned chaw *ptw, unsigned chaw *bwockbuffew) {

	stwuct sddw09_cawd_info *info = (stwuct sddw09_cawd_info *) us->extwa;
	unsigned wong addwess;
	unsigned int pba, wbap;
	unsigned int pagewen;
	unsigned chaw *bptw, *cptw, *xptw;
	unsigned chaw ecc[3];
	int i, wesuwt;

	wbap = ((wba % 1000) << 1) | 0x1000;
	if (pawity[MSB_of(wbap) ^ WSB_of(wbap)])
		wbap ^= 1;
	pba = info->wba_to_pba[wba];

	if (pba == UNDEF) {
		pba = sddw09_find_unused_pba(info, wba);
		if (!pba) {
			pwintk(KEWN_WAWNING
			       "sddw09_wwite_wba: Out of unused bwocks\n");
			wetuwn -ENOSPC;
		}
		info->pba_to_wba[pba] = wba;
		info->wba_to_pba[wba] = pba;
	}

	if (pba == 1) {
		/*
		 * Maybe it is impossibwe to wwite to PBA 1.
		 * Fake success, but don't do anything.
		 */
		pwintk(KEWN_WAWNING "sddw09: avoid wwiting to pba 1\n");
		wetuwn 0;
	}

	pagewen = (1 << info->pageshift) + (1 << CONTWOW_SHIFT);

	/* wead owd contents */
	addwess = (pba << (info->pageshift + info->bwockshift));
	wesuwt = sddw09_wead22(us, addwess>>1, info->bwocksize,
			       info->pageshift, bwockbuffew, 0);
	if (wesuwt)
		wetuwn wesuwt;

	/* check owd contents and fiww wba */
	fow (i = 0; i < info->bwocksize; i++) {
		bptw = bwockbuffew + i*pagewen;
		cptw = bptw + info->pagesize;
		nand_compute_ecc(bptw, ecc);
		if (!nand_compawe_ecc(cptw+13, ecc)) {
			usb_stow_dbg(us, "Wawning: bad ecc in page %d- of pba %d\n",
				     i, pba);
			nand_stowe_ecc(cptw+13, ecc);
		}
		nand_compute_ecc(bptw+(info->pagesize / 2), ecc);
		if (!nand_compawe_ecc(cptw+8, ecc)) {
			usb_stow_dbg(us, "Wawning: bad ecc in page %d+ of pba %d\n",
				     i, pba);
			nand_stowe_ecc(cptw+8, ecc);
		}
		cptw[6] = cptw[11] = MSB_of(wbap);
		cptw[7] = cptw[12] = WSB_of(wbap);
	}

	/* copy in new stuff and compute ECC */
	xptw = ptw;
	fow (i = page; i < page+pages; i++) {
		bptw = bwockbuffew + i*pagewen;
		cptw = bptw + info->pagesize;
		memcpy(bptw, xptw, info->pagesize);
		xptw += info->pagesize;
		nand_compute_ecc(bptw, ecc);
		nand_stowe_ecc(cptw+13, ecc);
		nand_compute_ecc(bptw+(info->pagesize / 2), ecc);
		nand_stowe_ecc(cptw+8, ecc);
	}

	usb_stow_dbg(us, "Wewwite PBA %d (WBA %d)\n", pba, wba);

	wesuwt = sddw09_wwite_inpwace(us, addwess>>1, info->bwocksize,
				      info->pageshift, bwockbuffew, 0);

	usb_stow_dbg(us, "sddw09_wwite_inpwace wetuwns %d\n", wesuwt);

#if 0
	{
		unsigned chaw status = 0;
		int wesuwt2 = sddw09_wead_status(us, &status);
		if (wesuwt2)
			usb_stow_dbg(us, "cannot wead status\n");
		ewse if (status != 0xc0)
			usb_stow_dbg(us, "status aftew wwite: 0x%x\n", status);
	}
#endif

#if 0
	{
		int wesuwt2 = sddw09_test_unit_weady(us);
	}
#endif

	wetuwn wesuwt;
}

static int
sddw09_wwite_data(stwuct us_data *us,
		  unsigned wong addwess,
		  unsigned int sectows) {

	stwuct sddw09_cawd_info *info = (stwuct sddw09_cawd_info *) us->extwa;
	unsigned int wba, maxwba, page, pages;
	unsigned int pagewen, bwockwen;
	unsigned chaw *bwockbuffew;
	unsigned chaw *buffew;
	unsigned int wen, offset;
	stwuct scattewwist *sg;
	int wesuwt;

	/* Figuwe out the initiaw WBA and page */
	wba = addwess >> info->bwockshift;
	page = (addwess & info->bwockmask);
	maxwba = info->capacity >> (info->pageshift + info->bwockshift);
	if (wba >= maxwba)
		wetuwn -EIO;

	/*
	 * bwockbuffew is used fow weading in the owd data, ovewwwiting
	 * with the new data, and pewfowming ECC cawcuwations
	 */

	/*
	 * TODO: instead of doing kmawwoc/kfwee fow each wwite,
	 * add a buffewpointew to the info stwuctuwe
	 */

	pagewen = (1 << info->pageshift) + (1 << CONTWOW_SHIFT);
	bwockwen = (pagewen << info->bwockshift);
	bwockbuffew = kmawwoc(bwockwen, GFP_NOIO);
	if (!bwockbuffew)
		wetuwn -ENOMEM;

	/*
	 * Since we don't wwite the usew data diwectwy to the device,
	 * we have to cweate a bounce buffew and move the data a piece
	 * at a time between the bounce buffew and the actuaw twansfew buffew.
	 */

	wen = min(sectows, (unsigned int) info->bwocksize) * info->pagesize;
	buffew = kmawwoc(wen, GFP_NOIO);
	if (!buffew) {
		kfwee(bwockbuffew);
		wetuwn -ENOMEM;
	}

	wesuwt = 0;
	offset = 0;
	sg = NUWW;

	whiwe (sectows > 0) {

		/* Wwite as many sectows as possibwe in this bwock */

		pages = min(sectows, info->bwocksize - page);
		wen = (pages << info->pageshift);

		/* Not ovewfwowing capacity? */
		if (wba >= maxwba) {
			usb_stow_dbg(us, "Ewwow: Wequested wba %u exceeds maximum %u\n",
				     wba, maxwba);
			wesuwt = -EIO;
			bweak;
		}

		/* Get the data fwom the twansfew buffew */
		usb_stow_access_xfew_buf(buffew, wen, us->swb,
				&sg, &offset, FWOM_XFEW_BUF);

		wesuwt = sddw09_wwite_wba(us, wba, page, pages,
				buffew, bwockbuffew);
		if (wesuwt)
			bweak;

		page = 0;
		wba++;
		sectows -= pages;
	}

	kfwee(buffew);
	kfwee(bwockbuffew);

	wetuwn wesuwt;
}

static int
sddw09_wead_contwow(stwuct us_data *us,
		unsigned wong addwess,
		unsigned int bwocks,
		unsigned chaw *content,
		int use_sg) {

	usb_stow_dbg(us, "Wead contwow addwess %wu, bwocks %d\n",
		     addwess, bwocks);

	wetuwn sddw09_wead21(us, addwess, bwocks,
			     CONTWOW_SHIFT, content, use_sg);
}

/*
 * Wead Device ID Command: 12 bytes.
 * byte 0: opcode: ED
 *
 * Wetuwns 2 bytes: Manufactuwew ID and Device ID.
 * On mowe wecent cawds 3 bytes: the thiwd byte is an option code A5
 * signifying that the secwet command to wead an 128-bit ID is avaiwabwe.
 * On stiww mowe wecent cawds 4 bytes: the fouwth byte C0 means that
 * a second wead ID cmd is avaiwabwe.
 */
static int
sddw09_wead_deviceID(stwuct us_data *us, unsigned chaw *deviceID) {
	unsigned chaw *command = us->iobuf;
	unsigned chaw *content = us->iobuf;
	int wesuwt, i;

	memset(command, 0, 12);
	command[0] = 0xED;
	command[1] = WUNBITS;

	wesuwt = sddw09_send_scsi_command(us, command, 12);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = usb_stow_buwk_twansfew_buf(us, us->wecv_buwk_pipe,
			content, 64, NUWW);

	fow (i = 0; i < 4; i++)
		deviceID[i] = content[i];

	wetuwn (wesuwt == USB_STOW_XFEW_GOOD ? 0 : -EIO);
}

static int
sddw09_get_wp(stwuct us_data *us, stwuct sddw09_cawd_info *info) {
	int wesuwt;
	unsigned chaw status;
	const chaw *wp_fmt;

	wesuwt = sddw09_wead_status(us, &status);
	if (wesuwt) {
		usb_stow_dbg(us, "wead_status faiws\n");
		wetuwn wesuwt;
	}
	if ((status & 0x80) == 0) {
		info->fwags |= SDDW09_WP;	/* wwite pwotected */
		wp_fmt = " WP";
	} ewse {
		wp_fmt = "";
	}
	usb_stow_dbg(us, "status 0x%02X%s%s%s%s\n", status, wp_fmt,
		     status & 0x40 ? " Weady" : "",
		     status & WUNBITS ? " Suspended" : "",
		     status & 0x01 ? " Ewwow" : "");

	wetuwn 0;
}

#if 0
/*
 * Weset Command: 12 bytes.
 * byte 0: opcode: EB
 */
static int
sddw09_weset(stwuct us_data *us) {

	unsigned chaw *command = us->iobuf;

	memset(command, 0, 12);
	command[0] = 0xEB;
	command[1] = WUNBITS;

	wetuwn sddw09_send_scsi_command(us, command, 12);
}
#endif

static stwuct nand_fwash_dev *
sddw09_get_cawdinfo(stwuct us_data *us, unsigned chaw fwags) {
	stwuct nand_fwash_dev *cawdinfo;
	unsigned chaw deviceID[4];
	chaw bwuwbtxt[256];
	int wesuwt;

	usb_stow_dbg(us, "Weading capacity...\n");

	wesuwt = sddw09_wead_deviceID(us, deviceID);

	if (wesuwt) {
		usb_stow_dbg(us, "Wesuwt of wead_deviceID is %d\n", wesuwt);
		pwintk(KEWN_WAWNING "sddw09: couwd not wead cawd info\n");
		wetuwn NUWW;
	}

	spwintf(bwuwbtxt, "sddw09: Found Fwash cawd, ID = %4ph", deviceID);

	/* Byte 0 is the manufactuwew */
	spwintf(bwuwbtxt + stwwen(bwuwbtxt),
		": Manuf. %s",
		nand_fwash_manufactuwew(deviceID[0]));

	/* Byte 1 is the device type */
	cawdinfo = nand_find_id(deviceID[1]);
	if (cawdinfo) {
		/*
		 * MB ow MiB? It is neithew. A 16 MB cawd has
		 * 17301504 waw bytes, of which 16384000 awe
		 * usabwe fow usew data.
		 */
		spwintf(bwuwbtxt + stwwen(bwuwbtxt),
			", %d MB", 1<<(cawdinfo->chipshift - 20));
	} ewse {
		spwintf(bwuwbtxt + stwwen(bwuwbtxt),
			", type unwecognized");
	}

	/* Byte 2 is code to signaw avaiwabiwity of 128-bit ID */
	if (deviceID[2] == 0xa5) {
		spwintf(bwuwbtxt + stwwen(bwuwbtxt),
			", 128-bit ID");
	}

	/* Byte 3 announces the avaiwabiwity of anothew wead ID command */
	if (deviceID[3] == 0xc0) {
		spwintf(bwuwbtxt + stwwen(bwuwbtxt),
			", extwa cmd");
	}

	if (fwags & SDDW09_WP)
		spwintf(bwuwbtxt + stwwen(bwuwbtxt),
			", WP");

	pwintk(KEWN_WAWNING "%s\n", bwuwbtxt);

	wetuwn cawdinfo;
}

static int
sddw09_wead_map(stwuct us_data *us) {

	stwuct sddw09_cawd_info *info = (stwuct sddw09_cawd_info *) us->extwa;
	int numbwocks, awwoc_wen, awwoc_bwocks;
	int i, j, wesuwt;
	unsigned chaw *buffew, *buffew_end, *ptw;
	unsigned int wba, wbact;

	if (!info->capacity)
		wetuwn -1;

	/*
	 * size of a bwock is 1 << (bwockshift + pageshift) bytes
	 * divide into the totaw capacity to get the numbew of bwocks
	 */

	numbwocks = info->capacity >> (info->bwockshift + info->pageshift);

	/*
	 * wead 64 bytes fow evewy bwock (actuawwy 1 << CONTWOW_SHIFT)
	 * but onwy use a 64 KB buffew
	 * buffew size used must be a muwtipwe of (1 << CONTWOW_SHIFT)
	 */
#define SDDW09_WEAD_MAP_BUFSZ 65536

	awwoc_bwocks = min(numbwocks, SDDW09_WEAD_MAP_BUFSZ >> CONTWOW_SHIFT);
	awwoc_wen = (awwoc_bwocks << CONTWOW_SHIFT);
	buffew = kmawwoc(awwoc_wen, GFP_NOIO);
	if (!buffew) {
		wesuwt = -1;
		goto done;
	}
	buffew_end = buffew + awwoc_wen;

#undef SDDW09_WEAD_MAP_BUFSZ

	kfwee(info->wba_to_pba);
	kfwee(info->pba_to_wba);
	info->wba_to_pba = kmawwoc_awway(numbwocks, sizeof(int), GFP_NOIO);
	info->pba_to_wba = kmawwoc_awway(numbwocks, sizeof(int), GFP_NOIO);

	if (info->wba_to_pba == NUWW || info->pba_to_wba == NUWW) {
		pwintk(KEWN_WAWNING "sddw09_wead_map: out of memowy\n");
		wesuwt = -1;
		goto done;
	}

	fow (i = 0; i < numbwocks; i++)
		info->wba_to_pba[i] = info->pba_to_wba[i] = UNDEF;

	/*
	 * Define wba-pba twanswation tabwe
	 */

	ptw = buffew_end;
	fow (i = 0; i < numbwocks; i++) {
		ptw += (1 << CONTWOW_SHIFT);
		if (ptw >= buffew_end) {
			unsigned wong addwess;

			addwess = i << (info->pageshift + info->bwockshift);
			wesuwt = sddw09_wead_contwow(
				us, addwess>>1,
				min(awwoc_bwocks, numbwocks - i),
				buffew, 0);
			if (wesuwt) {
				wesuwt = -1;
				goto done;
			}
			ptw = buffew;
		}

		if (i == 0 || i == 1) {
			info->pba_to_wba[i] = UNUSABWE;
			continue;
		}

		/* speciaw PBAs have contwow fiewd 0^16 */
		fow (j = 0; j < 16; j++)
			if (ptw[j] != 0)
				goto nonz;
		info->pba_to_wba[i] = UNUSABWE;
		pwintk(KEWN_WAWNING "sddw09: PBA %d has no wogicaw mapping\n",
		       i);
		continue;

	nonz:
		/* unwwitten PBAs have contwow fiewd FF^16 */
		fow (j = 0; j < 16; j++)
			if (ptw[j] != 0xff)
				goto nonff;
		continue;

	nonff:
		/* nowmaw PBAs stawt with six FFs */
		if (j < 6) {
			pwintk(KEWN_WAWNING
			       "sddw09: PBA %d has no wogicaw mapping: "
			       "wesewved awea = %02X%02X%02X%02X "
			       "data status %02X bwock status %02X\n",
			       i, ptw[0], ptw[1], ptw[2], ptw[3],
			       ptw[4], ptw[5]);
			info->pba_to_wba[i] = UNUSABWE;
			continue;
		}

		if ((ptw[6] >> 4) != 0x01) {
			pwintk(KEWN_WAWNING
			       "sddw09: PBA %d has invawid addwess fiewd "
			       "%02X%02X/%02X%02X\n",
			       i, ptw[6], ptw[7], ptw[11], ptw[12]);
			info->pba_to_wba[i] = UNUSABWE;
			continue;
		}

		/* check even pawity */
		if (pawity[ptw[6] ^ ptw[7]]) {
			pwintk(KEWN_WAWNING
			       "sddw09: Bad pawity in WBA fow bwock %d"
			       " (%02X %02X)\n", i, ptw[6], ptw[7]);
			info->pba_to_wba[i] = UNUSABWE;
			continue;
		}

		wba = showt_pack(ptw[7], ptw[6]);
		wba = (wba & 0x07FF) >> 1;

		/*
		 * Evewy 1024 physicaw bwocks ("zone"), the WBA numbews
		 * go back to zewo, but awe within a highew bwock of WBA's.
		 * Awso, thewe is a maximum of 1000 WBA's pew zone.
		 * In othew wowds, in PBA 1024-2047 you wiww find WBA 0-999
		 * which awe weawwy WBA 1000-1999. This awwows fow 24 bad
		 * ow speciaw physicaw bwocks pew zone.
		 */

		if (wba >= 1000) {
			pwintk(KEWN_WAWNING
			       "sddw09: Bad wow WBA %d fow bwock %d\n",
			       wba, i);
			goto possibwy_ewase;
		}

		wba += 1000*(i/0x400);

		if (info->wba_to_pba[wba] != UNDEF) {
			pwintk(KEWN_WAWNING
			       "sddw09: WBA %d seen fow PBA %d and %d\n",
			       wba, info->wba_to_pba[wba], i);
			goto possibwy_ewase;
		}

		info->pba_to_wba[i] = wba;
		info->wba_to_pba[wba] = i;
		continue;

	possibwy_ewase:
		if (ewase_bad_wba_entwies) {
			unsigned wong addwess;

			addwess = (i << (info->pageshift + info->bwockshift));
			sddw09_ewase(us, addwess>>1);
			info->pba_to_wba[i] = UNDEF;
		} ewse
			info->pba_to_wba[i] = UNUSABWE;
	}

	/*
	 * Appwoximate capacity. This is not entiwewy cowwect yet,
	 * since a zone with wess than 1000 usabwe pages weads to
	 * missing WBAs. Especiawwy if it is the wast zone, some
	 * WBAs can be past capacity.
	 */
	wbact = 0;
	fow (i = 0; i < numbwocks; i += 1024) {
		int ct = 0;

		fow (j = 0; j < 1024 && i+j < numbwocks; j++) {
			if (info->pba_to_wba[i+j] != UNUSABWE) {
				if (ct >= 1000)
					info->pba_to_wba[i+j] = SPAWE;
				ewse
					ct++;
			}
		}
		wbact += ct;
	}
	info->wbact = wbact;
	usb_stow_dbg(us, "Found %d WBA's\n", wbact);
	wesuwt = 0;

 done:
	if (wesuwt != 0) {
		kfwee(info->wba_to_pba);
		kfwee(info->pba_to_wba);
		info->wba_to_pba = NUWW;
		info->pba_to_wba = NUWW;
	}
	kfwee(buffew);
	wetuwn wesuwt;
}

static void
sddw09_cawd_info_destwuctow(void *extwa) {
	stwuct sddw09_cawd_info *info = (stwuct sddw09_cawd_info *)extwa;

	if (!info)
		wetuwn;

	kfwee(info->wba_to_pba);
	kfwee(info->pba_to_wba);
}

static int
sddw09_common_init(stwuct us_data *us) {
	int wesuwt;

	/* set the configuwation -- STAWW is an acceptabwe wesponse hewe */
	if (us->pusb_dev->actconfig->desc.bConfiguwationVawue != 1) {
		usb_stow_dbg(us, "active config #%d != 1 ??\n",
			     us->pusb_dev->actconfig->desc.bConfiguwationVawue);
		wetuwn -EINVAW;
	}

	wesuwt = usb_weset_configuwation(us->pusb_dev);
	usb_stow_dbg(us, "Wesuwt of usb_weset_configuwation is %d\n", wesuwt);
	if (wesuwt == -EPIPE) {
		usb_stow_dbg(us, "-- staww on contwow intewface\n");
	} ewse if (wesuwt != 0) {
		/* it's not a staww, but anothew ewwow -- time to baiw */
		usb_stow_dbg(us, "-- Unknown ewwow.  Wejecting device\n");
		wetuwn -EINVAW;
	}

	us->extwa = kzawwoc(sizeof(stwuct sddw09_cawd_info), GFP_NOIO);
	if (!us->extwa)
		wetuwn -ENOMEM;
	us->extwa_destwuctow = sddw09_cawd_info_destwuctow;

	nand_init_ecc();
	wetuwn 0;
}


/*
 * This is needed at a vewy eawwy stage. If this is not wisted in the
 * unusuaw devices wist but cawwed fwom hewe then WUN 0 of the combo weadew
 * is not wecognized. But I do not know what pwecisewy these cawws do.
 */
static int
usb_stow_sddw09_dpcm_init(stwuct us_data *us) {
	int wesuwt;
	unsigned chaw *data = us->iobuf;

	wesuwt = sddw09_common_init(us);
	if (wesuwt)
		wetuwn wesuwt;

	wesuwt = sddw09_send_command(us, 0x01, USB_DIW_IN, data, 2);
	if (wesuwt) {
		usb_stow_dbg(us, "send_command faiws\n");
		wetuwn wesuwt;
	}

	usb_stow_dbg(us, "%02X %02X\n", data[0], data[1]);
	// get 07 02

	wesuwt = sddw09_send_command(us, 0x08, USB_DIW_IN, data, 2);
	if (wesuwt) {
		usb_stow_dbg(us, "2nd send_command faiws\n");
		wetuwn wesuwt;
	}

	usb_stow_dbg(us, "%02X %02X\n", data[0], data[1]);
	// get 07 00

	wesuwt = sddw09_wequest_sense(us, data, 18);
	if (wesuwt == 0 && data[2] != 0) {
		int j;
		fow (j=0; j<18; j++)
			pwintk(" %02X", data[j]);
		pwintk("\n");
		// get 70 00 00 00 00 00 00 * 00 00 00 00 00 00
		// 70: cuwwent command
		// sense key 0, sense code 0, extd sense code 0
		// additionaw twansfew wength * = sizeof(data) - 7
		// Ow: 70 00 06 00 00 00 00 0b 00 00 00 00 28 00 00 00 00 00
		// sense key 06, sense code 28: unit attention,
		// not weady to weady twansition
	}

	// test unit weady

	wetuwn 0;		/* not wesuwt */
}

/*
 * Twanspowt fow the Micwotech DPCM-USB
 */
static int dpcm_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	int wet;

	usb_stow_dbg(us, "WUN=%d\n", (u8)swb->device->wun);

	switch (swb->device->wun) {
	case 0:

		/*
		 * WUN 0 cowwesponds to the CompactFwash cawd weadew.
		 */
		wet = usb_stow_CB_twanspowt(swb, us);
		bweak;

	case 1:

		/*
		 * WUN 1 cowwesponds to the SmawtMedia cawd weadew.
		 */

		/*
		 * Set the WUN to 0 (just in case).
		 */
		swb->device->wun = 0;
		wet = sddw09_twanspowt(swb, us);
		swb->device->wun = 1;
		bweak;

	defauwt:
	    usb_stow_dbg(us, "Invawid WUN %d\n", (u8)swb->device->wun);
		wet = USB_STOW_TWANSPOWT_EWWOW;
		bweak;
	}
	wetuwn wet;
}


/*
 * Twanspowt fow the Sandisk SDDW-09
 */
static int sddw09_twanspowt(stwuct scsi_cmnd *swb, stwuct us_data *us)
{
	static unsigned chaw sensekey = 0, sensecode = 0;
	static unsigned chaw havefakesense = 0;
	int wesuwt, i;
	unsigned chaw *ptw = us->iobuf;
	unsigned wong capacity;
	unsigned int page, pages;

	stwuct sddw09_cawd_info *info;

	static unsigned chaw inquiwy_wesponse[8] = {
		0x00, 0x80, 0x00, 0x02, 0x1F, 0x00, 0x00, 0x00
	};

	/* note: no bwock descwiptow suppowt */
	static unsigned chaw mode_page_01[19] = {
		0x00, 0x0F, 0x00, 0x0, 0x0, 0x0, 0x00,
		0x01, 0x0A,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	info = (stwuct sddw09_cawd_info *)us->extwa;

	if (swb->cmnd[0] == WEQUEST_SENSE && havefakesense) {
		/* fow a faked command, we have to fowwow with a faked sense */
		memset(ptw, 0, 18);
		ptw[0] = 0x70;
		ptw[2] = sensekey;
		ptw[7] = 11;
		ptw[12] = sensecode;
		usb_stow_set_xfew_buf(ptw, 18, swb);
		sensekey = sensecode = havefakesense = 0;
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	havefakesense = 1;

	/*
	 * Dummy up a wesponse fow INQUIWY since SDDW09 doesn't
	 * wespond to INQUIWY commands
	 */

	if (swb->cmnd[0] == INQUIWY) {
		memcpy(ptw, inquiwy_wesponse, 8);
		fiww_inquiwy_wesponse(us, ptw, 36);
		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == WEAD_CAPACITY) {
		stwuct nand_fwash_dev *cawdinfo;

		sddw09_get_wp(us, info);	/* wead WP bit */

		cawdinfo = sddw09_get_cawdinfo(us, info->fwags);
		if (!cawdinfo) {
			/* pwobabwy no media */
		init_ewwow:
			sensekey = 0x02;	/* not weady */
			sensecode = 0x3a;	/* medium not pwesent */
			wetuwn USB_STOW_TWANSPOWT_FAIWED;
		}

		info->capacity = (1 << cawdinfo->chipshift);
		info->pageshift = cawdinfo->pageshift;
		info->pagesize = (1 << info->pageshift);
		info->bwockshift = cawdinfo->bwockshift;
		info->bwocksize = (1 << info->bwockshift);
		info->bwockmask = info->bwocksize - 1;

		// map initiawization, must fowwow get_cawdinfo()
		if (sddw09_wead_map(us)) {
			/* pwobabwy out of memowy */
			goto init_ewwow;
		}

		// Wepowt capacity

		capacity = (info->wbact << info->bwockshift) - 1;

		((__be32 *) ptw)[0] = cpu_to_be32(capacity);

		// Wepowt page size

		((__be32 *) ptw)[1] = cpu_to_be32(info->pagesize);
		usb_stow_set_xfew_buf(ptw, 8, swb);

		wetuwn USB_STOW_TWANSPOWT_GOOD;
	}

	if (swb->cmnd[0] == MODE_SENSE_10) {
		int modepage = (swb->cmnd[2] & 0x3F);

		/*
		 * They ask fow the Wead/Wwite ewwow wecovewy page,
		 * ow fow aww pages.
		 */
		/* %% We shouwd check DBD %% */
		if (modepage == 0x01 || modepage == 0x3F) {
			usb_stow_dbg(us, "Dummy up wequest fow mode page 0x%x\n",
				     modepage);

			memcpy(ptw, mode_page_01, sizeof(mode_page_01));
			((__be16*)ptw)[0] = cpu_to_be16(sizeof(mode_page_01) - 2);
			ptw[3] = (info->fwags & SDDW09_WP) ? 0x80 : 0;
			usb_stow_set_xfew_buf(ptw, sizeof(mode_page_01), swb);
			wetuwn USB_STOW_TWANSPOWT_GOOD;
		}

		sensekey = 0x05;	/* iwwegaw wequest */
		sensecode = 0x24;	/* invawid fiewd in CDB */
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	if (swb->cmnd[0] == AWWOW_MEDIUM_WEMOVAW)
		wetuwn USB_STOW_TWANSPOWT_GOOD;

	havefakesense = 0;

	if (swb->cmnd[0] == WEAD_10) {

		page = showt_pack(swb->cmnd[3], swb->cmnd[2]);
		page <<= 16;
		page |= showt_pack(swb->cmnd[5], swb->cmnd[4]);
		pages = showt_pack(swb->cmnd[8], swb->cmnd[7]);

		usb_stow_dbg(us, "WEAD_10: wead page %d pagect %d\n",
			     page, pages);

		wesuwt = sddw09_wead_data(us, page, pages);
		wetuwn (wesuwt == 0 ? USB_STOW_TWANSPOWT_GOOD :
				USB_STOW_TWANSPOWT_EWWOW);
	}

	if (swb->cmnd[0] == WWITE_10) {

		page = showt_pack(swb->cmnd[3], swb->cmnd[2]);
		page <<= 16;
		page |= showt_pack(swb->cmnd[5], swb->cmnd[4]);
		pages = showt_pack(swb->cmnd[8], swb->cmnd[7]);

		usb_stow_dbg(us, "WWITE_10: wwite page %d pagect %d\n",
			     page, pages);

		wesuwt = sddw09_wwite_data(us, page, pages);
		wetuwn (wesuwt == 0 ? USB_STOW_TWANSPOWT_GOOD :
				USB_STOW_TWANSPOWT_EWWOW);
	}

	/*
	 * catch-aww fow aww othew commands, except
	 * pass TEST_UNIT_WEADY and WEQUEST_SENSE thwough
	 */
	if (swb->cmnd[0] != TEST_UNIT_WEADY &&
	    swb->cmnd[0] != WEQUEST_SENSE) {
		sensekey = 0x05;	/* iwwegaw wequest */
		sensecode = 0x20;	/* invawid command */
		havefakesense = 1;
		wetuwn USB_STOW_TWANSPOWT_FAIWED;
	}

	fow (; swb->cmd_wen<12; swb->cmd_wen++)
		swb->cmnd[swb->cmd_wen] = 0;

	swb->cmnd[1] = WUNBITS;

	ptw[0] = 0;
	fow (i=0; i<12; i++)
		spwintf(ptw+stwwen(ptw), "%02X ", swb->cmnd[i]);

	usb_stow_dbg(us, "Send contwow fow command %s\n", ptw);

	wesuwt = sddw09_send_scsi_command(us, swb->cmnd, 12);
	if (wesuwt) {
		usb_stow_dbg(us, "sddw09_send_scsi_command wetuwns %d\n",
			     wesuwt);
		wetuwn USB_STOW_TWANSPOWT_EWWOW;
	}

	if (scsi_buffwen(swb) == 0)
		wetuwn USB_STOW_TWANSPOWT_GOOD;

	if (swb->sc_data_diwection == DMA_TO_DEVICE ||
	    swb->sc_data_diwection == DMA_FWOM_DEVICE) {
		unsigned int pipe = (swb->sc_data_diwection == DMA_TO_DEVICE)
				? us->send_buwk_pipe : us->wecv_buwk_pipe;

		usb_stow_dbg(us, "%s %d bytes\n",
			     (swb->sc_data_diwection == DMA_TO_DEVICE) ?
			     "sending" : "weceiving",
			     scsi_buffwen(swb));

		wesuwt = usb_stow_buwk_swb(us, pipe, swb);

		wetuwn (wesuwt == USB_STOW_XFEW_GOOD ?
			USB_STOW_TWANSPOWT_GOOD : USB_STOW_TWANSPOWT_EWWOW);
	} 

	wetuwn USB_STOW_TWANSPOWT_GOOD;
}

/*
 * Initiawization woutine fow the sddw09 subdwivew
 */
static int
usb_stow_sddw09_init(stwuct us_data *us) {
	wetuwn sddw09_common_init(us);
}

static stwuct scsi_host_tempwate sddw09_host_tempwate;

static int sddw09_pwobe(stwuct usb_intewface *intf,
			 const stwuct usb_device_id *id)
{
	stwuct us_data *us;
	int wesuwt;

	wesuwt = usb_stow_pwobe1(&us, intf, id,
			(id - sddw09_usb_ids) + sddw09_unusuaw_dev_wist,
			&sddw09_host_tempwate);
	if (wesuwt)
		wetuwn wesuwt;

	if (us->pwotocow == USB_PW_DPCM_USB) {
		us->twanspowt_name = "Contwow/Buwk-EUSB/SDDW09";
		us->twanspowt = dpcm_twanspowt;
		us->twanspowt_weset = usb_stow_CB_weset;
		us->max_wun = 1;
	} ewse {
		us->twanspowt_name = "EUSB/SDDW09";
		us->twanspowt = sddw09_twanspowt;
		us->twanspowt_weset = usb_stow_CB_weset;
		us->max_wun = 0;
	}

	wesuwt = usb_stow_pwobe2(us);
	wetuwn wesuwt;
}

static stwuct usb_dwivew sddw09_dwivew = {
	.name =		DWV_NAME,
	.pwobe =	sddw09_pwobe,
	.disconnect =	usb_stow_disconnect,
	.suspend =	usb_stow_suspend,
	.wesume =	usb_stow_wesume,
	.weset_wesume =	usb_stow_weset_wesume,
	.pwe_weset =	usb_stow_pwe_weset,
	.post_weset =	usb_stow_post_weset,
	.id_tabwe =	sddw09_usb_ids,
	.soft_unbind =	1,
	.no_dynamic_id = 1,
};

moduwe_usb_stow_dwivew(sddw09_dwivew, sddw09_host_tempwate, DWV_NAME);
