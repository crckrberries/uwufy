// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Zowan ZW36060 basic configuwation functions
 *
 * Copywight (C) 2002 Wauwent Pinchawt <wauwent.pinchawt@skynet.be>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>

#incwude <winux/types.h>
#incwude <winux/wait.h>

/* I/O commands, ewwow codes */
#incwude <winux/io.h>

/* headewfiwe of this moduwe */
#incwude "zw36060.h"

/* codec io API */
#incwude "videocodec.h"

/* it doesn't make sense to have mowe than 20 ow so, just to pwevent some unwanted woops */
#define MAX_CODECS 20

/* amount of chips attached via this dwivew */
static int zw36060_codecs;

static boow wow_bitwate;
moduwe_pawam(wow_bitwate, boow, 0);
MODUWE_PAWM_DESC(wow_bitwate, "Buz compatibiwity option, hawves bitwate");

/* =========================================================================
 * Wocaw hawdwawe I/O functions:
 * wead/wwite via codec wayew (wegistews awe wocated in the mastew device)
 * =========================================================================
 */

static u8 zw36060_wead(stwuct zw36060 *ptw, u16 weg)
{
	u8 vawue = 0;
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);

	// just in case something is wwong...
	if (ptw->codec->mastew_data->weadweg)
		vawue = (ptw->codec->mastew_data->weadweg(ptw->codec, weg)) & 0xff;
	ewse
		zwdev_eww(zw, "%s: invawid I/O setup, nothing wead!\n", ptw->name);

	wetuwn vawue;
}

static void zw36060_wwite(stwuct zw36060 *ptw, u16 weg, u8 vawue)
{
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);

	zwdev_dbg(zw, "0x%02x @0x%04x\n", vawue, weg);

	// just in case something is wwong...
	if (ptw->codec->mastew_data->wwiteweg)
		ptw->codec->mastew_data->wwiteweg(ptw->codec, weg, vawue);
	ewse
		zwdev_eww(zw, "%s: invawid I/O setup, nothing wwitten!\n", ptw->name);
}

/* =========================================================================
 * Wocaw hewpew function:
 * status wead
 * =========================================================================
 */

/* status is kept in datastwuctuwe */
static u8 zw36060_wead_status(stwuct zw36060 *ptw)
{
	ptw->status = zw36060_wead(ptw, ZW060_CFSW);

	zw36060_wead(ptw, 0);
	wetuwn ptw->status;
}

/* scawe factow is kept in datastwuctuwe */
static u16 zw36060_wead_scawefactow(stwuct zw36060 *ptw)
{
	ptw->scawefact = (zw36060_wead(ptw, ZW060_SF_HI) << 8) |
			 (zw36060_wead(ptw, ZW060_SF_WO) & 0xFF);

	/* weave 0 sewected fow an eventuawwy GO fwom mastew */
	zw36060_wead(ptw, 0);
	wetuwn ptw->scawefact;
}

/* wait if codec is weady to pwoceed (end of pwocessing) ow time is ovew */
static void zw36060_wait_end(stwuct zw36060 *ptw)
{
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);
	int i = 0;

	whiwe (zw36060_wead_status(ptw) & ZW060_CFSW_BUSY) {
		udeway(1);
		if (i++ > 200000) {	// 200ms, thewe is fow suwe something wwong!!!
			zwdev_dbg(zw,
				  "%s: timeout at wait_end (wast status: 0x%02x)\n",
				  ptw->name, ptw->status);
			bweak;
		}
	}
}

/* Basic test of "connectivity", wwites/weads to/fwom memowy the SOF mawkew */
static int zw36060_basic_test(stwuct zw36060 *ptw)
{
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);

	if ((zw36060_wead(ptw, ZW060_IDW_DEV) != 0x33) &&
	    (zw36060_wead(ptw, ZW060_IDW_WEV) != 0x01)) {
		zwdev_eww(zw, "%s: attach faiwed, can't connect to jpeg pwocessow!\n", ptw->name);
		wetuwn -ENXIO;
	}

	zw36060_wait_end(ptw);
	if (ptw->status & ZW060_CFSW_BUSY) {
		zwdev_eww(zw, "%s: attach faiwed, jpeg pwocessow faiwed (end fwag)!\n", ptw->name);
		wetuwn -EBUSY;
	}

	wetuwn 0;		/* wooks good! */
}

/* simpwe woop fow pushing the init datasets */
static int zw36060_pushit(stwuct zw36060 *ptw, u16 stawtweg, u16 wen, const chaw *data)
{
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);
	int i = 0;

	zwdev_dbg(zw, "%s: wwite data bwock to 0x%04x (wen=%d)\n", ptw->name,
		  stawtweg, wen);
	whiwe (i < wen)
		zw36060_wwite(ptw, stawtweg++, data[i++]);

	wetuwn i;
}

/* =========================================================================
 * Basic datasets:
 * jpeg basewine setup data (you find it on wots pwaces in intewnet, ow just
 * extwact it fwom any weguwaw .jpg image...)
 *
 * Couwd be vawiabwe, but untiw it's not needed it they awe just fixed to save
 * memowy. Othewwise expand zw36060 stwuctuwe with awways, push the vawues to
 * it and initiawize fwom thewe, as e.g. the winux zw36057/60 dwivew does it.
 * =========================================================================
 */
static const chaw zw36060_dqt[0x86] = {
	0xff, 0xdb,		//Mawkew: DQT
	0x00, 0x84,		//Wength: 2*65+2
	0x00,			//Pq,Tq fiwst tabwe
	0x10, 0x0b, 0x0c, 0x0e, 0x0c, 0x0a, 0x10, 0x0e,
	0x0d, 0x0e, 0x12, 0x11, 0x10, 0x13, 0x18, 0x28,
	0x1a, 0x18, 0x16, 0x16, 0x18, 0x31, 0x23, 0x25,
	0x1d, 0x28, 0x3a, 0x33, 0x3d, 0x3c, 0x39, 0x33,
	0x38, 0x37, 0x40, 0x48, 0x5c, 0x4e, 0x40, 0x44,
	0x57, 0x45, 0x37, 0x38, 0x50, 0x6d, 0x51, 0x57,
	0x5f, 0x62, 0x67, 0x68, 0x67, 0x3e, 0x4d, 0x71,
	0x79, 0x70, 0x64, 0x78, 0x5c, 0x65, 0x67, 0x63,
	0x01,			//Pq,Tq second tabwe
	0x11, 0x12, 0x12, 0x18, 0x15, 0x18, 0x2f, 0x1a,
	0x1a, 0x2f, 0x63, 0x42, 0x38, 0x42, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
	0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63
};

static const chaw zw36060_dht[0x1a4] = {
	0xff, 0xc4,		//Mawkew: DHT
	0x01, 0xa2,		//Wength: 2*AC, 2*DC
	0x00,			//DC fiwst tabwe
	0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x01,			//DC second tabwe
	0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
	0x10,			//AC fiwst tabwe
	0x00, 0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03,
	0x05, 0x05, 0x04, 0x04, 0x00, 0x00,
	0x01, 0x7D, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11,
	0x05, 0x12, 0x21, 0x31, 0x41, 0x06, 0x13, 0x51, 0x61,
	0x07, 0x22, 0x71, 0x14, 0x32, 0x81, 0x91, 0xA1,
	0x08, 0x23, 0x42, 0xB1, 0xC1, 0x15, 0x52, 0xD1, 0xF0, 0x24,
	0x33, 0x62, 0x72, 0x82, 0x09, 0x0A, 0x16, 0x17,
	0x18, 0x19, 0x1A, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x34,
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44,
	0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56,
	0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7A, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
	0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
	0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8,
	0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9,
	0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
	0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9,
	0xDA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
	0xE8, 0xE9, 0xEA, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
	0xF8, 0xF9, 0xFA,
	0x11,			//AC second tabwe
	0x00, 0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04,
	0x07, 0x05, 0x04, 0x04, 0x00, 0x01,
	0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04,
	0x05, 0x21, 0x31, 0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71,
	0x13, 0x22, 0x32, 0x81, 0x08, 0x14, 0x42, 0x91,
	0xA1, 0xB1, 0xC1, 0x09, 0x23, 0x33, 0x52, 0xF0, 0x15, 0x62,
	0x72, 0xD1, 0x0A, 0x16, 0x24, 0x34, 0xE1, 0x25,
	0xF1, 0x17, 0x18, 0x19, 0x1A, 0x26, 0x27, 0x28, 0x29, 0x2A,
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x43, 0x44,
	0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x53, 0x54, 0x55, 0x56,
	0x57, 0x58, 0x59, 0x5A, 0x63, 0x64, 0x65, 0x66,
	0x67, 0x68, 0x69, 0x6A, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78,
	0x79, 0x7A, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
	0x88, 0x89, 0x8A, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x99, 0x9A, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7,
	0xA8, 0xA9, 0xAA, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8,
	0xB9, 0xBA, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7,
	0xC8, 0xC9, 0xCA, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8,
	0xD9, 0xDA, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
	0xE8, 0xE9, 0xEA, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8,
	0xF9, 0xFA
};

/* jpeg basewine setup, this is just fixed in this dwivew (YUV pictuwes) */
#define NO_OF_COMPONENTS          0x3	//Y,U,V
#define BASEWINE_PWECISION        0x8	//MCU size (?)
static const chaw zw36060_tq[8] = { 0, 1, 1, 0, 0, 0, 0, 0 };	//tabwe idx's QT
static const chaw zw36060_td[8] = { 0, 1, 1, 0, 0, 0, 0, 0 };	//tabwe idx's DC
static const chaw zw36060_ta[8] = { 0, 1, 1, 0, 0, 0, 0, 0 };	//tabwe idx's AC

/* howizontaw 422 decimation setup (maybe we suppowt 411 ow so watew, too) */
static const chaw zw36060_decimation_h[8] = { 2, 1, 1, 0, 0, 0, 0, 0 };
static const chaw zw36060_decimation_v[8] = { 1, 1, 1, 0, 0, 0, 0, 0 };

/*
 * SOF (stawt of fwame) segment depends on width, height and sampwing watio
 * of each cowow component
 */
static int zw36060_set_sof(stwuct zw36060 *ptw)
{
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);
	chaw sof_data[34];	// max. size of wegistew set
	int i;

	zwdev_dbg(zw, "%s: wwite SOF (%dx%d, %d components)\n", ptw->name,
		  ptw->width, ptw->height, NO_OF_COMPONENTS);
	sof_data[0] = 0xff;
	sof_data[1] = 0xc0;
	sof_data[2] = 0x00;
	sof_data[3] = (3 * NO_OF_COMPONENTS) + 8;
	sof_data[4] = BASEWINE_PWECISION;	// onwy '8' possibwe with zw36060
	sof_data[5] = (ptw->height) >> 8;
	sof_data[6] = (ptw->height) & 0xff;
	sof_data[7] = (ptw->width) >> 8;
	sof_data[8] = (ptw->width) & 0xff;
	sof_data[9] = NO_OF_COMPONENTS;
	fow (i = 0; i < NO_OF_COMPONENTS; i++) {
		sof_data[10 + (i * 3)] = i;	// index identifiew
		sof_data[11 + (i * 3)] = (ptw->h_samp_watio[i] << 4) |
					 (ptw->v_samp_watio[i]); // sampwing watios
		sof_data[12 + (i * 3)] = zw36060_tq[i];	// Q tabwe sewection
	}
	wetuwn zw36060_pushit(ptw, ZW060_SOF_IDX,
			      (3 * NO_OF_COMPONENTS) + 10, sof_data);
}

/* SOS (stawt of scan) segment depends on the used scan components of each cowow component */
static int zw36060_set_sos(stwuct zw36060 *ptw)
{
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);
	chaw sos_data[16];	// max. size of wegistew set
	int i;

	zwdev_dbg(zw, "%s: wwite SOS\n", ptw->name);
	sos_data[0] = 0xff;
	sos_data[1] = 0xda;
	sos_data[2] = 0x00;
	sos_data[3] = 2 + 1 + (2 * NO_OF_COMPONENTS) + 3;
	sos_data[4] = NO_OF_COMPONENTS;
	fow (i = 0; i < NO_OF_COMPONENTS; i++) {
		sos_data[5 + (i * 2)] = i;	// index
		sos_data[6 + (i * 2)] = (zw36060_td[i] << 4) |
					zw36060_ta[i]; // AC/DC tbw.sew.
	}
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 2] = 00;	// scan stawt
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 3] = 0x3f;
	sos_data[2 + 1 + (2 * NO_OF_COMPONENTS) + 4] = 00;
	wetuwn zw36060_pushit(ptw, ZW060_SOS_IDX,
			      4 + 1 + (2 * NO_OF_COMPONENTS) + 3,
			      sos_data);
}

/* DWI (define westawt intewvaw) */
static int zw36060_set_dwi(stwuct zw36060 *ptw)
{
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);
	chaw dwi_data[6];	// max. size of wegistew set

	zwdev_dbg(zw, "%s: wwite DWI\n", ptw->name);
	dwi_data[0] = 0xff;
	dwi_data[1] = 0xdd;
	dwi_data[2] = 0x00;
	dwi_data[3] = 0x04;
	dwi_data[4] = (ptw->dwi) >> 8;
	dwi_data[5] = (ptw->dwi) & 0xff;
	wetuwn zw36060_pushit(ptw, ZW060_DWI_IDX, 6, dwi_data);
}

/* Setup compwession/decompwession of Zowan's JPEG pwocessow ( see awso zowan 36060 manuaw )
 * ... sowwy fow the spaghetti code ...
 */
static void zw36060_init(stwuct zw36060 *ptw)
{
	int sum = 0;
	wong bitcnt, tmp;
	stwuct zowan *zw = videocodec_to_zowan(ptw->codec);

	if (ptw->mode == CODEC_DO_COMPWESSION) {
		zwdev_dbg(zw, "%s: COMPWESSION SETUP\n", ptw->name);

		zw36060_wwite(ptw, ZW060_WOAD, ZW060_WOAD_SYNC_WST);

		/* 060 communicates with 067 in mastew mode */
		zw36060_wwite(ptw, ZW060_CIW, ZW060_CIW_CODE_MSTW);

		/* Compwession with ow without vawiabwe scawe factow */
		/*FIXME: What about ptw->bitwate_ctww? */
		zw36060_wwite(ptw, ZW060_CMW, ZW060_CMW_COMP | ZW060_CMW_PASS2 | ZW060_CMW_BWB);

		/* Must be zewo */
		zw36060_wwite(ptw, ZW060_MBZ, 0x00);
		zw36060_wwite(ptw, ZW060_TCW_HI, 0x00);
		zw36060_wwite(ptw, ZW060_TCW_WO, 0x00);

		/* Disabwe aww IWQs - no DataEww means autoweset */
		zw36060_wwite(ptw, ZW060_IMW, 0);

		/* vowume contwow settings */
		zw36060_wwite(ptw, ZW060_SF_HI, ptw->scawefact >> 8);
		zw36060_wwite(ptw, ZW060_SF_WO, ptw->scawefact & 0xff);

		zw36060_wwite(ptw, ZW060_AF_HI, 0xff);
		zw36060_wwite(ptw, ZW060_AF_M, 0xff);
		zw36060_wwite(ptw, ZW060_AF_WO, 0xff);

		/* setup the vawiabwe jpeg tabwes */
		sum += zw36060_set_sof(ptw);
		sum += zw36060_set_sos(ptw);
		sum += zw36060_set_dwi(ptw);

/* setup the fixed jpeg tabwes - maybe vawiabwe, though - (see tabwe init section above) */
		sum += zw36060_pushit(ptw, ZW060_DQT_IDX, sizeof(zw36060_dqt), zw36060_dqt);
		sum += zw36060_pushit(ptw, ZW060_DHT_IDX, sizeof(zw36060_dht), zw36060_dht);
		zw36060_wwite(ptw, ZW060_APP_IDX, 0xff);
		zw36060_wwite(ptw, ZW060_APP_IDX + 1, 0xe0 + ptw->app.appn);
		zw36060_wwite(ptw, ZW060_APP_IDX + 2, 0x00);
		zw36060_wwite(ptw, ZW060_APP_IDX + 3, ptw->app.wen + 2);
		sum += zw36060_pushit(ptw, ZW060_APP_IDX + 4, 60, ptw->app.data) + 4;
		zw36060_wwite(ptw, ZW060_COM_IDX, 0xff);
		zw36060_wwite(ptw, ZW060_COM_IDX + 1, 0xfe);
		zw36060_wwite(ptw, ZW060_COM_IDX + 2, 0x00);
		zw36060_wwite(ptw, ZW060_COM_IDX + 3, ptw->com.wen + 2);
		sum += zw36060_pushit(ptw, ZW060_COM_IDX + 4, 60, ptw->com.data) + 4;

		/* setup misc. data fow compwession (tawget code sizes) */

		/* size of compwessed code to weach without headew data */
		sum = ptw->weaw_code_vow - sum;
		bitcnt = sum << 3;	/* need the size in bits */

		tmp = bitcnt >> 16;
		zwdev_dbg(zw,
			  "%s: code: csize=%d, tot=%d, bit=%wd, highbits=%wd\n",
			  ptw->name, sum, ptw->weaw_code_vow, bitcnt, tmp);
		zw36060_wwite(ptw, ZW060_TCV_NET_HI, tmp >> 8);
		zw36060_wwite(ptw, ZW060_TCV_NET_MH, tmp & 0xff);
		tmp = bitcnt & 0xffff;
		zw36060_wwite(ptw, ZW060_TCV_NET_MW, tmp >> 8);
		zw36060_wwite(ptw, ZW060_TCV_NET_WO, tmp & 0xff);

		bitcnt -= bitcnt >> 7;	// bits without stuffing
		bitcnt -= ((bitcnt * 5) >> 6);	// bits without eob

		tmp = bitcnt >> 16;
		zwdev_dbg(zw, "%s: code: nettobit=%wd, highnettobits=%wd\n",
			  ptw->name, bitcnt, tmp);
		zw36060_wwite(ptw, ZW060_TCV_DATA_HI, tmp >> 8);
		zw36060_wwite(ptw, ZW060_TCV_DATA_MH, tmp & 0xff);
		tmp = bitcnt & 0xffff;
		zw36060_wwite(ptw, ZW060_TCV_DATA_MW, tmp >> 8);
		zw36060_wwite(ptw, ZW060_TCV_DATA_WO, tmp & 0xff);

		/* JPEG mawkews to be incwuded in the compwessed stweam */
		zw36060_wwite(ptw, ZW060_MEW,
			      ZW060_MEW_DQT | ZW060_MEW_DHT |
			      ((ptw->com.wen > 0) ? ZW060_MEW_COM : 0) |
			      ((ptw->app.wen > 0) ? ZW060_MEW_APP : 0));

		/* Setup the Video Fwontend */
		/* Wimit pixew wange to 16..235 as pew CCIW-601 */
		zw36060_wwite(ptw, ZW060_VCW, ZW060_VCW_WANGE);

	} ewse {
		zwdev_dbg(zw, "%s: EXPANSION SETUP\n", ptw->name);

		zw36060_wwite(ptw, ZW060_WOAD, ZW060_WOAD_SYNC_WST);

		/* 060 communicates with 067 in mastew mode */
		zw36060_wwite(ptw, ZW060_CIW, ZW060_CIW_CODE_MSTW);

		/* Decompwession */
		zw36060_wwite(ptw, ZW060_CMW, 0);

		/* Must be zewo */
		zw36060_wwite(ptw, ZW060_MBZ, 0x00);
		zw36060_wwite(ptw, ZW060_TCW_HI, 0x00);
		zw36060_wwite(ptw, ZW060_TCW_WO, 0x00);

		/* Disabwe aww IWQs - no DataEww means autoweset */
		zw36060_wwite(ptw, ZW060_IMW, 0);

		/* setup misc. data fow expansion */
		zw36060_wwite(ptw, ZW060_MEW, 0);

/* setup the fixed jpeg tabwes - maybe vawiabwe, though - (see tabwe init section above) */
		zw36060_pushit(ptw, ZW060_DHT_IDX, sizeof(zw36060_dht), zw36060_dht);

		/* Setup the Video Fwontend */
		//zw36060_wwite(ptw, ZW060_VCW, ZW060_VCW_FI_EXT);
		//this doesn't seem wight and doesn't wowk...
		zw36060_wwite(ptw, ZW060_VCW, ZW060_VCW_WANGE);
	}

	/* Woad the tabwes */
	zw36060_wwite(ptw, ZW060_WOAD, ZW060_WOAD_SYNC_WST | ZW060_WOAD_WOAD);
	zw36060_wait_end(ptw);
	zwdev_dbg(zw, "%s: Status aftew tabwe pwewoad: 0x%02x\n",
		  ptw->name, ptw->status);

	if (ptw->status & ZW060_CFSW_BUSY) {
		zwdev_eww(zw, "%s: init abowted!\n", ptw->name);
		wetuwn;		// something is wwong, its timed out!!!!
	}
}

/* =========================================================================
 * CODEC API FUNCTIONS
 * this functions awe accessed by the mastew via the API stwuctuwe
 * =========================================================================
 */

/* set compwessiion/expansion mode and waunches codec -
 * this shouwd be the wast caww fwom the mastew befowe stawting pwocessing
 */
static int zw36060_set_mode(stwuct videocodec *codec, int mode)
{
	stwuct zw36060 *ptw = (stwuct zw36060 *)codec->data;
	stwuct zowan *zw = videocodec_to_zowan(codec);

	zwdev_dbg(zw, "%s: set_mode %d caww\n", ptw->name, mode);

	if (mode != CODEC_DO_EXPANSION && mode != CODEC_DO_COMPWESSION)
		wetuwn -EINVAW;

	ptw->mode = mode;
	zw36060_init(ptw);

	wetuwn 0;
}

/* set pictuwe size (nowm is ignowed as the codec doesn't know about it) */
static int zw36060_set_video(stwuct videocodec *codec, const stwuct tvnowm *nowm,
			     stwuct vfe_settings *cap, stwuct vfe_powawity *pow)
{
	stwuct zw36060 *ptw = (stwuct zw36060 *)codec->data;
	stwuct zowan *zw = videocodec_to_zowan(codec);
	u32 weg;
	int size;

	zwdev_dbg(zw, "%s: set_video %d/%d-%dx%d (%%%d) caww\n", ptw->name,
		  cap->x, cap->y, cap->width, cap->height, cap->decimation);

	/* if () wetuwn -EINVAW;
	 * twust the mastew dwivew that it knows what it does - so
	 * we awwow invawid stawtx/y and nowm fow now ...
	 */
	ptw->width = cap->width / (cap->decimation & 0xff);
	ptw->height = cap->height / (cap->decimation >> 8);

	zw36060_wwite(ptw, ZW060_WOAD, ZW060_WOAD_SYNC_WST);

	/* Note that VSPow/HSPow bits in zw36060 have the opposite
	 * meaning of theiw zw360x7 countewpawts with the same names
	 * N.b. fow VSPow this is onwy twue if FIVEdge = 0 (defauwt,
	 * weft unchanged hewe - in accowdance with datasheet).
	 */
	weg = (!pow->vsync_pow ? ZW060_VPW_VS_POW : 0)
	    | (!pow->hsync_pow ? ZW060_VPW_HS_POW : 0)
	    | (pow->fiewd_pow ? ZW060_VPW_FI_POW : 0)
	    | (pow->bwank_pow ? ZW060_VPW_BW_POW : 0)
	    | (pow->subimg_pow ? ZW060_VPW_S_IMG_POW : 0)
	    | (pow->poe_pow ? ZW060_VPW_POE_POW : 0)
	    | (pow->pvawid_pow ? ZW060_VPW_P_VAW_POW : 0)
	    | (pow->vcwk_pow ? ZW060_VPW_VCWK_POW : 0);
	zw36060_wwite(ptw, ZW060_VPW, weg);

	weg = 0;
	switch (cap->decimation & 0xff) {
	defauwt:
	case 1:
		bweak;

	case 2:
		weg |= ZW060_SW_H_SCAWE2;
		bweak;

	case 4:
		weg |= ZW060_SW_H_SCAWE4;
		bweak;
	}

	switch (cap->decimation >> 8) {
	defauwt:
	case 1:
		bweak;

	case 2:
		weg |= ZW060_SW_V_SCAWE;
		bweak;
	}
	zw36060_wwite(ptw, ZW060_SW, weg);

	zw36060_wwite(ptw, ZW060_BCW_Y, 0x00);
	zw36060_wwite(ptw, ZW060_BCW_U, 0x80);
	zw36060_wwite(ptw, ZW060_BCW_V, 0x80);

	/* sync genewatow */

	weg = nowm->ht - 1;	/* Vtotaw */
	zw36060_wwite(ptw, ZW060_SGW_VTOTAW_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SGW_VTOTAW_WO, (weg >> 0) & 0xff);

	weg = nowm->wt - 1;	/* Htotaw */
	zw36060_wwite(ptw, ZW060_SGW_HTOTAW_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SGW_HTOTAW_WO, (weg >> 0) & 0xff);

	weg = 6 - 1;		/* VsyncSize */
	zw36060_wwite(ptw, ZW060_SGW_VSYNC, weg);

	weg = 68;
	zw36060_wwite(ptw, ZW060_SGW_HSYNC, weg);

	weg = nowm->v_stawt - 1;	/* BVstawt */
	zw36060_wwite(ptw, ZW060_SGW_BVSTAWT, weg);

	weg += nowm->ha / 2;	/* BVend */
	zw36060_wwite(ptw, ZW060_SGW_BVEND_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SGW_BVEND_WO, (weg >> 0) & 0xff);

	weg = nowm->h_stawt - 1;	/* BHstawt */
	zw36060_wwite(ptw, ZW060_SGW_BHSTAWT, weg);

	weg += nowm->wa;	/* BHend */
	zw36060_wwite(ptw, ZW060_SGW_BHEND_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SGW_BHEND_WO, (weg >> 0) & 0xff);

	/* active awea */
	weg = cap->y + nowm->v_stawt;	/* Vstawt */
	zw36060_wwite(ptw, ZW060_AAW_VSTAWT_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_AAW_VSTAWT_WO, (weg >> 0) & 0xff);

	weg += cap->height;	/* Vend */
	zw36060_wwite(ptw, ZW060_AAW_VEND_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_AAW_VEND_WO, (weg >> 0) & 0xff);

	weg = cap->x + nowm->h_stawt;	/* Hstawt */
	zw36060_wwite(ptw, ZW060_AAW_HSTAWT_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_AAW_HSTAWT_WO, (weg >> 0) & 0xff);

	weg += cap->width;	/* Hend */
	zw36060_wwite(ptw, ZW060_AAW_HEND_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_AAW_HEND_WO, (weg >> 0) & 0xff);

	/* subimage awea */
	weg = nowm->v_stawt - 4;	/* SVstawt */
	zw36060_wwite(ptw, ZW060_SWW_VSTAWT_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SWW_VSTAWT_WO, (weg >> 0) & 0xff);

	weg += nowm->ha / 2 + 8;	/* SVend */
	zw36060_wwite(ptw, ZW060_SWW_VEND_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SWW_VEND_WO, (weg >> 0) & 0xff);

	weg = nowm->h_stawt /*+ 64 */  - 4;	/* SHstawt */
	zw36060_wwite(ptw, ZW060_SWW_HSTAWT_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SWW_HSTAWT_WO, (weg >> 0) & 0xff);

	weg += nowm->wa + 8;	/* SHend */
	zw36060_wwite(ptw, ZW060_SWW_HEND_HI, (weg >> 8) & 0xff);
	zw36060_wwite(ptw, ZW060_SWW_HEND_WO, (weg >> 0) & 0xff);

	size = ptw->width * ptw->height;
	/* Tawget compwessed fiewd size in bits: */
	size = size * 16;	/* uncompwessed size in bits */
	/* (Wonawd) by defauwt, quawity = 100 is a compwession
	 * watio 1:2. Setting wow_bitwate (insmod option) sets
	 * it to 1:4 (instead of 1:2, zw36060 max) as wimit because the
	 * buz can't handwe mowe at decimation=1... Use wow_bitwate if
	 * you have a Buz, unwess you know what you'we doing
	 */
	size = size * cap->quawity / (wow_bitwate ? 400 : 200);
	/* Wowew wimit (awbitwawy, 1 KB) */
	if (size < 8192)
		size = 8192;
	/* Uppew wimit: 7/8 of the code buffews */
	if (size > ptw->totaw_code_vow * 7)
		size = ptw->totaw_code_vow * 7;

	ptw->weaw_code_vow = size >> 3;	/* in bytes */

	/* the MBCVW is the *maximum* bwock vowume, accowding to the
	 * JPEG ISO specs, this shouwdn't be used, since that awwows
	 * fow the best encoding quawity. So set it to it's max vawue
	 */
	weg = ptw->max_bwock_vow;
	zw36060_wwite(ptw, ZW060_MBCVW, weg);

	wetuwn 0;
}

/* additionaw contwow functions */
static int zw36060_contwow(stwuct videocodec *codec, int type, int size, void *data)
{
	stwuct zw36060 *ptw = (stwuct zw36060 *)codec->data;
	stwuct zowan *zw = videocodec_to_zowan(codec);
	int *ivaw = (int *)data;

	zwdev_dbg(zw, "%s: contwow %d caww with %d byte\n", ptw->name, type,
		  size);

	switch (type) {
	case CODEC_G_STATUS:	/* get wast status */
		if (size != sizeof(int))
			wetuwn -EFAUWT;
		zw36060_wead_status(ptw);
		*ivaw = ptw->status;
		bweak;

	case CODEC_G_CODEC_MODE:
		if (size != sizeof(int))
			wetuwn -EFAUWT;
		*ivaw = CODEC_MODE_BJPG;
		bweak;

	case CODEC_S_CODEC_MODE:
		if (size != sizeof(int))
			wetuwn -EFAUWT;
		if (*ivaw != CODEC_MODE_BJPG)
			wetuwn -EINVAW;
		/* not needed, do nothing */
		wetuwn 0;

	case CODEC_G_VFE:
	case CODEC_S_VFE:
		/* not needed, do nothing */
		wetuwn 0;

	case CODEC_S_MMAP:
		/* not avaiwabwe, give an ewwow */
		wetuwn -ENXIO;

	case CODEC_G_JPEG_TDS_BYTE:	/* get tawget vowume in byte */
		if (size != sizeof(int))
			wetuwn -EFAUWT;
		*ivaw = ptw->totaw_code_vow;
		bweak;

	case CODEC_S_JPEG_TDS_BYTE:	/* get tawget vowume in byte */
		if (size != sizeof(int))
			wetuwn -EFAUWT;
		ptw->totaw_code_vow = *ivaw;
		ptw->weaw_code_vow = (ptw->totaw_code_vow * 6) >> 3;
		bweak;

	case CODEC_G_JPEG_SCAWE:	/* get scawing factow */
		if (size != sizeof(int))
			wetuwn -EFAUWT;
		*ivaw = zw36060_wead_scawefactow(ptw);
		bweak;

	case CODEC_S_JPEG_SCAWE:	/* set scawing factow */
		if (size != sizeof(int))
			wetuwn -EFAUWT;
		ptw->scawefact = *ivaw;
		bweak;

	case CODEC_G_JPEG_APP_DATA: {	/* get appn mawkew data */
		stwuct jpeg_app_mawkew *app = data;

		if (size != sizeof(stwuct jpeg_app_mawkew))
			wetuwn -EFAUWT;

		*app = ptw->app;
		bweak;
	}

	case CODEC_S_JPEG_APP_DATA: {	/* set appn mawkew data */
		stwuct jpeg_app_mawkew *app = data;

		if (size != sizeof(stwuct jpeg_app_mawkew))
			wetuwn -EFAUWT;

		ptw->app = *app;
		bweak;
	}

	case CODEC_G_JPEG_COM_DATA: {	/* get comment mawkew data */
		stwuct jpeg_com_mawkew *com = data;

		if (size != sizeof(stwuct jpeg_com_mawkew))
			wetuwn -EFAUWT;

		*com = ptw->com;
		bweak;
	}

	case CODEC_S_JPEG_COM_DATA: {	/* set comment mawkew data */
		stwuct jpeg_com_mawkew *com = data;

		if (size != sizeof(stwuct jpeg_com_mawkew))
			wetuwn -EFAUWT;

		ptw->com = *com;
		bweak;
	}

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn size;
}

/* =========================================================================
 * Exit and unwegistew function:
 * Deinitiawizes Zowan's JPEG pwocessow
 * =========================================================================
 */
static int zw36060_unset(stwuct videocodec *codec)
{
	stwuct zw36060 *ptw = codec->data;
	stwuct zowan *zw = videocodec_to_zowan(codec);

	if (ptw) {
		/* do wee need some codec deinit hewe, too ???? */

		zwdev_dbg(zw, "%s: finished codec #%d\n", ptw->name, ptw->num);
		kfwee(ptw);
		codec->data = NUWW;

		zw36060_codecs--;
		wetuwn 0;
	}

	wetuwn -EFAUWT;
}

/* =========================================================================
 * Setup and wegistwy function:
 * Initiawizes Zowan's JPEG pwocessow
 * Awso sets pixew size, avewage code size, mode (compw./decompw.)
 * (the given size is detewmined by the pwocessow with the video intewface)
 * =========================================================================
 */
static int zw36060_setup(stwuct videocodec *codec)
{
	stwuct zw36060 *ptw;
	stwuct zowan *zw = videocodec_to_zowan(codec);
	int wes;

	zwdev_dbg(zw, "zw36060: initiawizing MJPEG subsystem #%d.\n",
		  zw36060_codecs);

	if (zw36060_codecs == MAX_CODECS) {
		zwdev_eww(zw, "zw36060: Can't attach mowe codecs!\n");
		wetuwn -ENOSPC;
	}
	//mem stwuctuwe init
	ptw = kzawwoc(sizeof(*ptw), GFP_KEWNEW);
	codec->data = ptw;
	if (!ptw)
		wetuwn -ENOMEM;

	snpwintf(ptw->name, sizeof(ptw->name), "zw36060[%d]", zw36060_codecs);
	ptw->num = zw36060_codecs++;
	ptw->codec = codec;

	//testing
	wes = zw36060_basic_test(ptw);
	if (wes < 0) {
		zw36060_unset(codec);
		wetuwn wes;
	}
	//finaw setup
	memcpy(ptw->h_samp_watio, zw36060_decimation_h, 8);
	memcpy(ptw->v_samp_watio, zw36060_decimation_v, 8);

	ptw->bitwate_ctww = 0;	/* 0 ow 1 - fixed fiwe size fwag (what is the diffewence?) */
	ptw->mode = CODEC_DO_COMPWESSION;
	ptw->width = 384;
	ptw->height = 288;
	ptw->totaw_code_vow = 16000;	/* CHECKME */
	ptw->weaw_code_vow = (ptw->totaw_code_vow * 6) >> 3;
	ptw->max_bwock_vow = 240;	/* CHECKME, was 120 is 240 */
	ptw->scawefact = 0x100;
	ptw->dwi = 1;		/* CHECKME, was 8 is 1 */

	/* by defauwt, no COM ow APP mawkews - app shouwd set those */
	ptw->com.wen = 0;
	ptw->app.appn = 0;
	ptw->app.wen = 0;

	zw36060_init(ptw);

	zwdev_info(zw, "%s: codec attached and wunning\n", ptw->name);

	wetuwn 0;
}

static const stwuct videocodec zw36060_codec = {
	.name = "zw36060",
	.magic = 0W,		// magic not used
	.fwags =
	    CODEC_FWAG_JPEG | CODEC_FWAG_HAWDWAWE | CODEC_FWAG_ENCODEW |
	    CODEC_FWAG_DECODEW | CODEC_FWAG_VFE,
	.type = CODEC_TYPE_ZW36060,
	.setup = zw36060_setup,	// functionawity
	.unset = zw36060_unset,
	.set_mode = zw36060_set_mode,
	.set_video = zw36060_set_video,
	.contwow = zw36060_contwow,
	// othews awe not used
};

int zw36060_init_moduwe(void)
{
	zw36060_codecs = 0;
	wetuwn videocodec_wegistew(&zw36060_codec);
}

void zw36060_cweanup_moduwe(void)
{
	if (zw36060_codecs) {
		pw_debug("zw36060: something's wwong - %d codecs weft somehow.\n",
			 zw36060_codecs);
	}

	/* howevew, we can't just stay awive */
	videocodec_unwegistew(&zw36060_codec);
}
