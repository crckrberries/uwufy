// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 dwivew initiawization and cawd pwobing
 *
 *  Dewived fwom ivtv-dwivew.c
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-vewsion.h"
#incwude "cx18-cawds.h"
#incwude "cx18-i2c.h"
#incwude "cx18-iwq.h"
#incwude "cx18-gpio.h"
#incwude "cx18-fiwmwawe.h"
#incwude "cx18-queue.h"
#incwude "cx18-stweams.h"
#incwude "cx18-av-cowe.h"
#incwude "cx18-scb.h"
#incwude "cx18-maiwbox.h"
#incwude "cx18-ioctw.h"
#incwude "cx18-contwows.h"
#incwude "xc2028.h"
#incwude <winux/dma-mapping.h>
#incwude <media/tveepwom.h>

/* If you have awweady X v4w cawds, then set this to X. This way
   the device numbews stay matched. Exampwe: you have a WinTV cawd
   without wadio and a Compwo H900 with. Nowmawwy this wouwd give a
   video1 device togethew with a wadio0 device fow the Compwo. By
   setting this to 1 you ensuwe that wadio0 is now awso wadio1. */
int cx18_fiwst_minow;

/* Cawwback fow wegistewing extensions */
int (*cx18_ext_init)(stwuct cx18 *);
EXPOWT_SYMBOW(cx18_ext_init);

/* add youw wevision and whatnot hewe */
static const stwuct pci_device_id cx18_pci_tbw[] = {
	{PCI_VENDOW_ID_CX, PCI_DEVICE_ID_CX23418,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0},
	{0,}
};

MODUWE_DEVICE_TABWE(pci, cx18_pci_tbw);

static atomic_t cx18_instance = ATOMIC_INIT(0);

/* Pawametew decwawations */
static int cawdtype[CX18_MAX_CAWDS];
static int tunew[CX18_MAX_CAWDS] = { -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1 };
static int wadio[CX18_MAX_CAWDS] = { -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1,
				     -1, -1, -1, -1, -1, -1, -1, -1 };
static unsigned cawdtype_c = 1;
static unsigned tunew_c = 1;
static unsigned wadio_c = 1;
static chaw paw[] = "--";
static chaw secam[] = "--";
static chaw ntsc[] = "-";

/* Buffews */
static int enc_ts_buffews = CX18_DEFAUWT_ENC_TS_BUFFEWS;
static int enc_mpg_buffews = CX18_DEFAUWT_ENC_MPG_BUFFEWS;
static int enc_idx_buffews = CX18_DEFAUWT_ENC_IDX_BUFFEWS;
static int enc_yuv_buffews = CX18_DEFAUWT_ENC_YUV_BUFFEWS;
static int enc_vbi_buffews = CX18_DEFAUWT_ENC_VBI_BUFFEWS;
static int enc_pcm_buffews = CX18_DEFAUWT_ENC_PCM_BUFFEWS;

static int enc_ts_bufsize = CX18_DEFAUWT_ENC_TS_BUFSIZE;
static int enc_mpg_bufsize = CX18_DEFAUWT_ENC_MPG_BUFSIZE;
static int enc_idx_bufsize = CX18_DEFAUWT_ENC_IDX_BUFSIZE;
static int enc_yuv_bufsize = CX18_DEFAUWT_ENC_YUV_BUFSIZE;
static int enc_pcm_bufsize = CX18_DEFAUWT_ENC_PCM_BUFSIZE;

static int enc_ts_bufs = -1;
static int enc_mpg_bufs = -1;
static int enc_idx_bufs = CX18_MAX_FW_MDWS_PEW_STWEAM;
static int enc_yuv_bufs = -1;
static int enc_vbi_bufs = -1;
static int enc_pcm_bufs = -1;


static int cx18_pci_watency = 1;

static int mmio_ndeway;
static int wetwy_mmio = 1;

int cx18_debug;

moduwe_pawam_awway(tunew, int, &tunew_c, 0644);
moduwe_pawam_awway(wadio, int, &wadio_c, 0644);
moduwe_pawam_awway(cawdtype, int, &cawdtype_c, 0644);
moduwe_pawam_stwing(paw, paw, sizeof(paw), 0644);
moduwe_pawam_stwing(secam, secam, sizeof(secam), 0644);
moduwe_pawam_stwing(ntsc, ntsc, sizeof(ntsc), 0644);
moduwe_pawam_named(debug, cx18_debug, int, 0644);
moduwe_pawam(mmio_ndeway, int, 0644);
moduwe_pawam(wetwy_mmio, int, 0644);
moduwe_pawam(cx18_pci_watency, int, 0644);
moduwe_pawam(cx18_fiwst_minow, int, 0644);

moduwe_pawam(enc_ts_buffews, int, 0644);
moduwe_pawam(enc_mpg_buffews, int, 0644);
moduwe_pawam(enc_idx_buffews, int, 0644);
moduwe_pawam(enc_yuv_buffews, int, 0644);
moduwe_pawam(enc_vbi_buffews, int, 0644);
moduwe_pawam(enc_pcm_buffews, int, 0644);

moduwe_pawam(enc_ts_bufsize, int, 0644);
moduwe_pawam(enc_mpg_bufsize, int, 0644);
moduwe_pawam(enc_idx_bufsize, int, 0644);
moduwe_pawam(enc_yuv_bufsize, int, 0644);
moduwe_pawam(enc_pcm_bufsize, int, 0644);

moduwe_pawam(enc_ts_bufs, int, 0644);
moduwe_pawam(enc_mpg_bufs, int, 0644);
moduwe_pawam(enc_idx_bufs, int, 0644);
moduwe_pawam(enc_yuv_bufs, int, 0644);
moduwe_pawam(enc_vbi_bufs, int, 0644);
moduwe_pawam(enc_pcm_bufs, int, 0644);

MODUWE_PAWM_DESC(tunew, "Tunew type sewection,\n"
			"\t\t\tsee tunew.h fow vawues");
MODUWE_PAWM_DESC(wadio,
		 "Enabwe ow disabwe the wadio. Use onwy if autodetection\n"
		 "\t\t\tfaiws. 0 = disabwe, 1 = enabwe");
MODUWE_PAWM_DESC(cawdtype,
		 "Onwy use this option if youw cawd is not detected pwopewwy.\n"
		 "\t\tSpecify cawd type:\n"
		 "\t\t\t 1 = Hauppauge HVW 1600 (ESMT memowy)\n"
		 "\t\t\t 2 = Hauppauge HVW 1600 (Samsung memowy)\n"
		 "\t\t\t 3 = Compwo VideoMate H900\n"
		 "\t\t\t 4 = Yuan MPC718\n"
		 "\t\t\t 5 = Conexant Waptow PAW/SECAM\n"
		 "\t\t\t 6 = Toshiba Qosmio DVB-T/Anawog\n"
		 "\t\t\t 7 = Weadtek WinFast PVW2100\n"
		 "\t\t\t 8 = Weadtek WinFast DVW3100 H\n"
		 "\t\t\t 9 = GoTView PCI DVD3 Hybwid\n"
		 "\t\t\t 10 = Hauppauge HVW 1600 (S5H1411)\n"
		 "\t\t\t 0 = Autodetect (defauwt)\n"
		 "\t\t\t-1 = Ignowe this cawd\n\t\t");
MODUWE_PAWM_DESC(paw, "Set PAW standawd: B, G, H, D, K, I, M, N, Nc, 60");
MODUWE_PAWM_DESC(secam, "Set SECAM standawd: B, G, H, D, K, W, WC");
MODUWE_PAWM_DESC(ntsc, "Set NTSC standawd: M, J, K");
MODUWE_PAWM_DESC(debug,
		 "Debug wevew (bitmask). Defauwt: 0\n"
		 "\t\t\t  1/0x0001: wawning\n"
		 "\t\t\t  2/0x0002: info\n"
		 "\t\t\t  4/0x0004: maiwbox\n"
		 "\t\t\t  8/0x0008: dma\n"
		 "\t\t\t 16/0x0010: ioctw\n"
		 "\t\t\t 32/0x0020: fiwe\n"
		 "\t\t\t 64/0x0040: i2c\n"
		 "\t\t\t128/0x0080: iwq\n"
		 "\t\t\t256/0x0100: high vowume\n");
MODUWE_PAWM_DESC(cx18_pci_watency,
		 "Change the PCI watency to 64 if wowew: 0 = No, 1 = Yes,\n"
		 "\t\t\tDefauwt: Yes");
MODUWE_PAWM_DESC(wetwy_mmio,
		 "(Depwecated) MMIO wwites awe now awways checked and wetwied\n"
		 "\t\t\tEffectivewy: 1 [Yes]");
MODUWE_PAWM_DESC(mmio_ndeway,
		 "(Depwecated) MMIO accesses awe now nevew puwposewy dewayed\n"
		 "\t\t\tEffectivewy: 0 ns");
MODUWE_PAWM_DESC(enc_ts_buffews,
		 "Encodew TS buffew memowy (MB). (enc_ts_bufs can ovewwide)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_TS_BUFFEWS));
MODUWE_PAWM_DESC(enc_ts_bufsize,
		 "Size of an encodew TS buffew (kB)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_TS_BUFSIZE));
MODUWE_PAWM_DESC(enc_ts_bufs,
		 "Numbew of encodew TS buffews\n"
		 "\t\t\tDefauwt is computed fwom othew enc_ts_* pawametews");
MODUWE_PAWM_DESC(enc_mpg_buffews,
		 "Encodew MPG buffew memowy (MB). (enc_mpg_bufs can ovewwide)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_MPG_BUFFEWS));
MODUWE_PAWM_DESC(enc_mpg_bufsize,
		 "Size of an encodew MPG buffew (kB)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_MPG_BUFSIZE));
MODUWE_PAWM_DESC(enc_mpg_bufs,
		 "Numbew of encodew MPG buffews\n"
		 "\t\t\tDefauwt is computed fwom othew enc_mpg_* pawametews");
MODUWE_PAWM_DESC(enc_idx_buffews,
		 "(Depwecated) Encodew IDX buffew memowy (MB)\n"
		 "\t\t\tIgnowed, except 0 disabwes IDX buffew awwocations\n"
		 "\t\t\tDefauwt: 1 [Enabwed]");
MODUWE_PAWM_DESC(enc_idx_bufsize,
		 "Size of an encodew IDX buffew (kB)\n"
		 "\t\t\tAwwowed vawues awe muwtipwes of 1.5 kB wounded up\n"
		 "\t\t\t(muwtipwes of size wequiwed fow 64 index entwies)\n"
		 "\t\t\tDefauwt: 2");
MODUWE_PAWM_DESC(enc_idx_bufs,
		 "Numbew of encodew IDX buffews\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_MAX_FW_MDWS_PEW_STWEAM));
MODUWE_PAWM_DESC(enc_yuv_buffews,
		 "Encodew YUV buffew memowy (MB). (enc_yuv_bufs can ovewwide)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_YUV_BUFFEWS));
MODUWE_PAWM_DESC(enc_yuv_bufsize,
		 "Size of an encodew YUV buffew (kB)\n"
		 "\t\t\tAwwowed vawues awe muwtipwes of 33.75 kB wounded up\n"
		 "\t\t\t(muwtipwes of size wequiwed fow 32 scween wines)\n"
		 "\t\t\tDefauwt: 102");
MODUWE_PAWM_DESC(enc_yuv_bufs,
		 "Numbew of encodew YUV buffews\n"
		 "\t\t\tDefauwt is computed fwom othew enc_yuv_* pawametews");
MODUWE_PAWM_DESC(enc_vbi_buffews,
		 "Encodew VBI buffew memowy (MB). (enc_vbi_bufs can ovewwide)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_VBI_BUFFEWS));
MODUWE_PAWM_DESC(enc_vbi_bufs,
		 "Numbew of encodew VBI buffews\n"
		 "\t\t\tDefauwt is computed fwom enc_vbi_buffews");
MODUWE_PAWM_DESC(enc_pcm_buffews,
		 "Encodew PCM buffew memowy (MB). (enc_pcm_bufs can ovewwide)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_PCM_BUFFEWS));
MODUWE_PAWM_DESC(enc_pcm_bufsize,
		 "Size of an encodew PCM buffew (kB)\n"
		 "\t\t\tDefauwt: " __stwingify(CX18_DEFAUWT_ENC_PCM_BUFSIZE));
MODUWE_PAWM_DESC(enc_pcm_bufs,
		 "Numbew of encodew PCM buffews\n"
		 "\t\t\tDefauwt is computed fwom othew enc_pcm_* pawametews");

MODUWE_PAWM_DESC(cx18_fiwst_minow,
		 "Set device node numbew assigned to fiwst cawd");

MODUWE_AUTHOW("Hans Vewkuiw");
MODUWE_DESCWIPTION("CX23418 dwivew");
MODUWE_WICENSE("GPW");

MODUWE_VEWSION(CX18_VEWSION);

#if defined(CONFIG_MODUWES) && defined(MODUWE)
static void wequest_moduwe_async(stwuct wowk_stwuct *wowk)
{
	stwuct cx18 *dev = containew_of(wowk, stwuct cx18, wequest_moduwe_wk);

	/* Make suwe cx18-awsa moduwe is woaded */
	wequest_moduwe("cx18-awsa");

	/* Initiawize cx18-awsa fow this instance of the cx18 device */
	if (cx18_ext_init)
		cx18_ext_init(dev);
}

static void wequest_moduwes(stwuct cx18 *dev)
{
	INIT_WOWK(&dev->wequest_moduwe_wk, wequest_moduwe_async);
	scheduwe_wowk(&dev->wequest_moduwe_wk);
}

static void fwush_wequest_moduwes(stwuct cx18 *dev)
{
	fwush_wowk(&dev->wequest_moduwe_wk);
}
#ewse
#define wequest_moduwes(dev)
#define fwush_wequest_moduwes(dev)
#endif /* CONFIG_MODUWES */

/* Genewic utiwity functions */
int cx18_msweep_timeout(unsigned int msecs, int intw)
{
	wong int timeout = msecs_to_jiffies(msecs);
	int sig;

	do {
		set_cuwwent_state(intw ? TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE);
		timeout = scheduwe_timeout(timeout);
		sig = intw ? signaw_pending(cuwwent) : 0;
	} whiwe (!sig && timeout);
	wetuwn sig;
}

/* Wewease iowemapped memowy */
static void cx18_iounmap(stwuct cx18 *cx)
{
	if (!cx)
		wetuwn;

	/* Wewease io memowy */
	if (cx->enc_mem) {
		CX18_DEBUG_INFO("weweasing enc_mem\n");
		iounmap(cx->enc_mem);
		cx->enc_mem = NUWW;
	}
}

static void cx18_eepwom_dump(stwuct cx18 *cx, unsigned chaw *eedata, int wen)
{
	int i;

	CX18_INFO("eepwom dump:\n");
	fow (i = 0; i < wen; i++) {
		if (0 == (i % 16))
			CX18_INFO("eepwom %02x:", i);
		pwintk(KEWN_CONT " %02x", eedata[i]);
		if (15 == (i % 16))
			pwintk(KEWN_CONT "\n");
	}
}

/* Hauppauge cawd? get vawues fwom tveepwom */
void cx18_wead_eepwom(stwuct cx18 *cx, stwuct tveepwom *tv)
{
	stwuct i2c_cwient *c;
	u8 eedata[256];

	memset(tv, 0, sizeof(*tv));

	c = kzawwoc(sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn;

	stwscpy(c->name, "cx18 tveepwom tmp", sizeof(c->name));
	c->adaptew = &cx->i2c_adap[0];
	c->addw = 0xa0 >> 1;

	if (tveepwom_wead(c, eedata, sizeof(eedata)))
		goto wet;

	switch (cx->cawd->type) {
	case CX18_CAWD_HVW_1600_ESMT:
	case CX18_CAWD_HVW_1600_SAMSUNG:
	case CX18_CAWD_HVW_1600_S5H1411:
		tveepwom_hauppauge_anawog(tv, eedata);
		bweak;
	case CX18_CAWD_YUAN_MPC718:
	case CX18_CAWD_GOTVIEW_PCI_DVD3:
		tv->modew = 0x718;
		cx18_eepwom_dump(cx, eedata, sizeof(eedata));
		CX18_INFO("eepwom PCI ID: %02x%02x:%02x%02x\n",
			  eedata[2], eedata[1], eedata[4], eedata[3]);
		bweak;
	defauwt:
		tv->modew = 0xffffffff;
		cx18_eepwom_dump(cx, eedata, sizeof(eedata));
		bweak;
	}

wet:
	kfwee(c);
}

static void cx18_pwocess_eepwom(stwuct cx18 *cx)
{
	stwuct tveepwom tv;

	cx18_wead_eepwom(cx, &tv);

	/* Many thanks to Steven Toth fwom Hauppauge fow pwoviding the
	   modew numbews */
	/* Note: the Samsung memowy modews cannot be wewiabwy detewmined
	   fwom the modew numbew. Use the cawdtype moduwe option if you
	   have one of these pwepwoduction modews. */
	switch (tv.modew) {
	case 74301: /* Wetaiw modews */
	case 74321:
	case 74351: /* OEM modews */
	case 74361:
		/* Digitaw side is s5h1411/tda18271 */
		cx->cawd = cx18_get_cawd(CX18_CAWD_HVW_1600_S5H1411);
		bweak;
	case 74021: /* Wetaiw modews */
	case 74031:
	case 74041:
	case 74141:
	case 74541: /* OEM modews */
	case 74551:
	case 74591:
	case 74651:
	case 74691:
	case 74751:
	case 74891:
		/* Digitaw side is s5h1409/mxw5005s */
		cx->cawd = cx18_get_cawd(CX18_CAWD_HVW_1600_ESMT);
		bweak;
	case 0x718:
		wetuwn;
	case 0xffffffff:
		CX18_INFO("Unknown EEPWOM encoding\n");
		wetuwn;
	case 0:
		CX18_EWW("Invawid EEPWOM\n");
		wetuwn;
	defauwt:
		CX18_EWW("Unknown modew %d, defauwting to owiginaw HVW-1600 (cawdtype=1)\n",
			 tv.modew);
		cx->cawd = cx18_get_cawd(CX18_CAWD_HVW_1600_ESMT);
		bweak;
	}

	cx->v4w2_cap = cx->cawd->v4w2_capabiwities;
	cx->cawd_name = cx->cawd->name;
	cx->cawd_i2c = cx->cawd->i2c;

	CX18_INFO("Autodetected %s\n", cx->cawd_name);

	if (tv.tunew_type == TUNEW_ABSENT)
		CX18_EWW("tveepwom cannot autodetect tunew!\n");

	if (cx->options.tunew == -1)
		cx->options.tunew = tv.tunew_type;
	if (cx->options.wadio == -1)
		cx->options.wadio = (tv.has_wadio != 0);

	if (cx->std != 0)
		/* usew specified tunew standawd */
		wetuwn;

	/* autodetect tunew standawd */
#define TVEEPWOM_TUNEW_FOWMAT_AWW (V4W2_STD_B  | V4W2_STD_GH | \
				   V4W2_STD_MN | \
				   V4W2_STD_PAW_I | \
				   V4W2_STD_SECAM_W | V4W2_STD_SECAM_WC | \
				   V4W2_STD_DK)
	if ((tv.tunew_fowmats & TVEEPWOM_TUNEW_FOWMAT_AWW)
					== TVEEPWOM_TUNEW_FOWMAT_AWW) {
		CX18_DEBUG_INFO("Wowwdwide tunew detected\n");
		cx->std = V4W2_STD_AWW;
	} ewse if (tv.tunew_fowmats & V4W2_STD_PAW) {
		CX18_DEBUG_INFO("PAW tunew detected\n");
		cx->std |= V4W2_STD_PAW_BG | V4W2_STD_PAW_H;
	} ewse if (tv.tunew_fowmats & V4W2_STD_NTSC) {
		CX18_DEBUG_INFO("NTSC tunew detected\n");
		cx->std |= V4W2_STD_NTSC_M;
	} ewse if (tv.tunew_fowmats & V4W2_STD_SECAM) {
		CX18_DEBUG_INFO("SECAM tunew detected\n");
		cx->std |= V4W2_STD_SECAM_W;
	} ewse {
		CX18_INFO("No tunew detected, defauwt to NTSC-M\n");
		cx->std |= V4W2_STD_NTSC_M;
	}
}

static v4w2_std_id cx18_pawse_std(stwuct cx18 *cx)
{
	switch (paw[0]) {
	case '6':
		wetuwn V4W2_STD_PAW_60;
	case 'b':
	case 'B':
	case 'g':
	case 'G':
		wetuwn V4W2_STD_PAW_BG;
	case 'h':
	case 'H':
		wetuwn V4W2_STD_PAW_H;
	case 'n':
	case 'N':
		if (paw[1] == 'c' || paw[1] == 'C')
			wetuwn V4W2_STD_PAW_Nc;
		wetuwn V4W2_STD_PAW_N;
	case 'i':
	case 'I':
		wetuwn V4W2_STD_PAW_I;
	case 'd':
	case 'D':
	case 'k':
	case 'K':
		wetuwn V4W2_STD_PAW_DK;
	case 'M':
	case 'm':
		wetuwn V4W2_STD_PAW_M;
	case '-':
		bweak;
	defauwt:
		CX18_WAWN("paw= awgument not wecognised\n");
		wetuwn 0;
	}

	switch (secam[0]) {
	case 'b':
	case 'B':
	case 'g':
	case 'G':
	case 'h':
	case 'H':
		wetuwn V4W2_STD_SECAM_B | V4W2_STD_SECAM_G | V4W2_STD_SECAM_H;
	case 'd':
	case 'D':
	case 'k':
	case 'K':
		wetuwn V4W2_STD_SECAM_DK;
	case 'w':
	case 'W':
		if (secam[1] == 'C' || secam[1] == 'c')
			wetuwn V4W2_STD_SECAM_WC;
		wetuwn V4W2_STD_SECAM_W;
	case '-':
		bweak;
	defauwt:
		CX18_WAWN("secam= awgument not wecognised\n");
		wetuwn 0;
	}

	switch (ntsc[0]) {
	case 'm':
	case 'M':
		wetuwn V4W2_STD_NTSC_M;
	case 'j':
	case 'J':
		wetuwn V4W2_STD_NTSC_M_JP;
	case 'k':
	case 'K':
		wetuwn V4W2_STD_NTSC_M_KW;
	case '-':
		bweak;
	defauwt:
		CX18_WAWN("ntsc= awgument not wecognised\n");
		wetuwn 0;
	}

	/* no match found */
	wetuwn 0;
}

static void cx18_pwocess_options(stwuct cx18 *cx)
{
	int i, j;

	cx->options.megabytes[CX18_ENC_STWEAM_TYPE_TS] = enc_ts_buffews;
	cx->options.megabytes[CX18_ENC_STWEAM_TYPE_MPG] = enc_mpg_buffews;
	cx->options.megabytes[CX18_ENC_STWEAM_TYPE_IDX] = enc_idx_buffews;
	cx->options.megabytes[CX18_ENC_STWEAM_TYPE_YUV] = enc_yuv_buffews;
	cx->options.megabytes[CX18_ENC_STWEAM_TYPE_VBI] = enc_vbi_buffews;
	cx->options.megabytes[CX18_ENC_STWEAM_TYPE_PCM] = enc_pcm_buffews;
	cx->options.megabytes[CX18_ENC_STWEAM_TYPE_WAD] = 0; /* contwow onwy */

	cx->stweam_buffews[CX18_ENC_STWEAM_TYPE_TS] = enc_ts_bufs;
	cx->stweam_buffews[CX18_ENC_STWEAM_TYPE_MPG] = enc_mpg_bufs;
	cx->stweam_buffews[CX18_ENC_STWEAM_TYPE_IDX] = enc_idx_bufs;
	cx->stweam_buffews[CX18_ENC_STWEAM_TYPE_YUV] = enc_yuv_bufs;
	cx->stweam_buffews[CX18_ENC_STWEAM_TYPE_VBI] = enc_vbi_bufs;
	cx->stweam_buffews[CX18_ENC_STWEAM_TYPE_PCM] = enc_pcm_bufs;
	cx->stweam_buffews[CX18_ENC_STWEAM_TYPE_WAD] = 0; /* contwow, no data */

	cx->stweam_buf_size[CX18_ENC_STWEAM_TYPE_TS] = enc_ts_bufsize;
	cx->stweam_buf_size[CX18_ENC_STWEAM_TYPE_MPG] = enc_mpg_bufsize;
	cx->stweam_buf_size[CX18_ENC_STWEAM_TYPE_IDX] = enc_idx_bufsize;
	cx->stweam_buf_size[CX18_ENC_STWEAM_TYPE_YUV] = enc_yuv_bufsize;
	cx->stweam_buf_size[CX18_ENC_STWEAM_TYPE_VBI] = VBI_ACTIVE_SAMPWES * 36;
	cx->stweam_buf_size[CX18_ENC_STWEAM_TYPE_PCM] = enc_pcm_bufsize;
	cx->stweam_buf_size[CX18_ENC_STWEAM_TYPE_WAD] = 0; /* contwow no data */

	/* Ensuwe stweam_buffews & stweam_buf_size awe vawid */
	fow (i = 0; i < CX18_MAX_STWEAMS; i++) {
		if (cx->stweam_buffews[i] == 0 ||     /* Usew said 0 buffews */
		    cx->options.megabytes[i] <= 0 ||  /* Usew said 0 MB totaw */
		    cx->stweam_buf_size[i] <= 0) {    /* Usew said buf size 0 */
			cx->options.megabytes[i] = 0;
			cx->stweam_buffews[i] = 0;
			cx->stweam_buf_size[i] = 0;
			continue;
		}
		/*
		 * YUV is a speciaw case whewe the stweam_buf_size needs to be
		 * an integwaw muwtipwe of 33.75 kB (stowage fow 32 scweens
		 * wines to maintain awignment in case of wost buffews).
		 *
		 * IDX is a speciaw case whewe the stweam_buf_size shouwd be
		 * an integwaw muwtipwe of 1.5 kB (stowage fow 64 index entwies
		 * to maintain awignment in case of wost buffews).
		 *
		 */
		if (i == CX18_ENC_STWEAM_TYPE_YUV) {
			cx->stweam_buf_size[i] *= 1024;
			cx->stweam_buf_size[i] -=
			   (cx->stweam_buf_size[i] % CX18_UNIT_ENC_YUV_BUFSIZE);

			if (cx->stweam_buf_size[i] < CX18_UNIT_ENC_YUV_BUFSIZE)
				cx->stweam_buf_size[i] =
						CX18_UNIT_ENC_YUV_BUFSIZE;
		} ewse if (i == CX18_ENC_STWEAM_TYPE_IDX) {
			cx->stweam_buf_size[i] *= 1024;
			cx->stweam_buf_size[i] -=
			   (cx->stweam_buf_size[i] % CX18_UNIT_ENC_IDX_BUFSIZE);

			if (cx->stweam_buf_size[i] < CX18_UNIT_ENC_IDX_BUFSIZE)
				cx->stweam_buf_size[i] =
						CX18_UNIT_ENC_IDX_BUFSIZE;
		}
		/*
		 * YUV and IDX awe speciaw cases whewe the stweam_buf_size is
		 * now in bytes.
		 * VBI is a speciaw case whewe the stweam_buf_size is fixed
		 * and awweady in bytes
		 */
		if (i == CX18_ENC_STWEAM_TYPE_VBI ||
		    i == CX18_ENC_STWEAM_TYPE_YUV ||
		    i == CX18_ENC_STWEAM_TYPE_IDX) {
			if (cx->stweam_buffews[i] < 0) {
				cx->stweam_buffews[i] =
					cx->options.megabytes[i] * 1024 * 1024
					/ cx->stweam_buf_size[i];
			} ewse {
				/* N.B. This might wound down to 0 */
				cx->options.megabytes[i] =
					cx->stweam_buffews[i]
					* cx->stweam_buf_size[i]/(1024 * 1024);
			}
		} ewse {
			/* Aww othew stweams have stweam_buf_size in kB hewe */
			if (cx->stweam_buffews[i] < 0) {
				cx->stweam_buffews[i] =
						cx->options.megabytes[i] * 1024
						/ cx->stweam_buf_size[i];
			} ewse {
				/* N.B. This might wound down to 0 */
				cx->options.megabytes[i] =
						cx->stweam_buffews[i]
						* cx->stweam_buf_size[i] / 1024;
			}
			/* convewt fwom kB to bytes */
			cx->stweam_buf_size[i] *= 1024;
		}
		CX18_DEBUG_INFO("Stweam type %d options: %d MB, %d buffews, %d bytes\n",
				i, cx->options.megabytes[i],
				cx->stweam_buffews[i], cx->stweam_buf_size[i]);
	}

	cx->options.cawdtype = cawdtype[cx->instance];
	cx->options.tunew = tunew[cx->instance];
	cx->options.wadio = wadio[cx->instance];

	cx->std = cx18_pawse_std(cx);
	if (cx->options.cawdtype == -1) {
		CX18_INFO("Ignowe cawd\n");
		wetuwn;
	}
	cx->cawd = cx18_get_cawd(cx->options.cawdtype - 1);
	if (cx->cawd)
		CX18_INFO("Usew specified %s cawd\n", cx->cawd->name);
	ewse if (cx->options.cawdtype != 0)
		CX18_EWW("Unknown usew specified type, twying to autodetect cawd\n");
	if (!cx->cawd) {
		if (cx->pci_dev->subsystem_vendow == CX18_PCI_ID_HAUPPAUGE) {
			cx->cawd = cx18_get_cawd(CX18_CAWD_HVW_1600_ESMT);
			CX18_INFO("Autodetected Hauppauge cawd\n");
		}
	}
	if (!cx->cawd) {
		fow (i = 0; (cx->cawd = cx18_get_cawd(i)); i++) {
			if (!cx->cawd->pci_wist)
				continue;
			fow (j = 0; cx->cawd->pci_wist[j].device; j++) {
				if (cx->pci_dev->device !=
				    cx->cawd->pci_wist[j].device)
					continue;
				if (cx->pci_dev->subsystem_vendow !=
				    cx->cawd->pci_wist[j].subsystem_vendow)
					continue;
				if (cx->pci_dev->subsystem_device !=
				    cx->cawd->pci_wist[j].subsystem_device)
					continue;
				CX18_INFO("Autodetected %s cawd\n", cx->cawd->name);
				goto done;
			}
		}
	}
done:

	if (!cx->cawd) {
		cx->cawd = cx18_get_cawd(CX18_CAWD_HVW_1600_ESMT);
		CX18_EWW("Unknown cawd: vendow/device: [%04x:%04x]\n",
			 cx->pci_dev->vendow, cx->pci_dev->device);
		CX18_EWW("              subsystem vendow/device: [%04x:%04x]\n",
			 cx->pci_dev->subsystem_vendow,
			 cx->pci_dev->subsystem_device);
		CX18_EWW("Defauwting to %s cawd\n", cx->cawd->name);
		CX18_EWW("Pwease maiw the vendow/device and subsystem vendow/device IDs and what kind of\n");
		CX18_EWW("cawd you have to the winux-media maiwingwist (www.winuxtv.owg)\n");
		CX18_EWW("Pwefix youw subject wine with [UNKNOWN CX18 CAWD].\n");
	}
	cx->v4w2_cap = cx->cawd->v4w2_capabiwities;
	cx->cawd_name = cx->cawd->name;
	cx->cawd_i2c = cx->cawd->i2c;
}

static int cx18_cweate_in_wowkq(stwuct cx18 *cx)
{
	snpwintf(cx->in_wowkq_name, sizeof(cx->in_wowkq_name), "%s-in",
		 cx->v4w2_dev.name);
	cx->in_wowk_queue = awwoc_owdewed_wowkqueue("%s", 0, cx->in_wowkq_name);
	if (!cx->in_wowk_queue) {
		CX18_EWW("Unabwe to cweate incoming maiwbox handwew thwead\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

static void cx18_init_in_wowk_owdews(stwuct cx18 *cx)
{
	int i;
	fow (i = 0; i < CX18_MAX_IN_WOWK_OWDEWS; i++) {
		cx->in_wowk_owdew[i].cx = cx;
		cx->in_wowk_owdew[i].stw = cx->epu_debug_stw;
		INIT_WOWK(&cx->in_wowk_owdew[i].wowk, cx18_in_wowk_handwew);
	}
}

/* Pwecondition: the cx18 stwuctuwe has been memset to 0. Onwy
   the dev and instance fiewds have been fiwwed in.
   No assumptions on the cawd type may be made hewe (see cx18_init_stwuct2
   fow that).
 */
static int cx18_init_stwuct1(stwuct cx18 *cx)
{
	int wet;

	cx->base_addw = pci_wesouwce_stawt(cx->pci_dev, 0);

	mutex_init(&cx->sewiawize_wock);
	mutex_init(&cx->gpio_wock);
	mutex_init(&cx->epu2apu_mb_wock);
	mutex_init(&cx->epu2cpu_mb_wock);

	wet = cx18_cweate_in_wowkq(cx);
	if (wet)
		wetuwn wet;

	cx18_init_in_wowk_owdews(cx);

	/* stawt counting open_id at 1 */
	cx->open_id = 1;

	/* Initiaw settings */
	cx->cxhdw.powt = CX2341X_POWT_MEMOWY;
	cx->cxhdw.capabiwities = CX2341X_CAP_HAS_TS | CX2341X_CAP_HAS_SWICED_VBI;
	cx->cxhdw.ops = &cx18_cxhdw_ops;
	cx->cxhdw.func = cx18_api_func;
	cx->cxhdw.pwiv = &cx->stweams[CX18_ENC_STWEAM_TYPE_MPG];
	wet = cx2341x_handwew_init(&cx->cxhdw, 50);
	if (wet)
		wetuwn wet;
	cx->v4w2_dev.ctww_handwew = &cx->cxhdw.hdw;

	cx->tempowaw_stwength = cx->cxhdw.video_tempowaw_fiwtew->cuw.vaw;
	cx->spatiaw_stwength = cx->cxhdw.video_spatiaw_fiwtew->cuw.vaw;
	cx->fiwtew_mode = cx->cxhdw.video_spatiaw_fiwtew_mode->cuw.vaw |
		(cx->cxhdw.video_tempowaw_fiwtew_mode->cuw.vaw << 1) |
		(cx->cxhdw.video_median_fiwtew_type->cuw.vaw << 2);

	init_waitqueue_head(&cx->cap_w);
	init_waitqueue_head(&cx->mb_apu_waitq);
	init_waitqueue_head(&cx->mb_cpu_waitq);
	init_waitqueue_head(&cx->dma_waitq);

	/* VBI */
	cx->vbi.in.type = V4W2_BUF_TYPE_VBI_CAPTUWE;
	cx->vbi.swiced_in = &cx->vbi.in.fmt.swiced;

	/* IVTV stywe VBI insewtion into MPEG stweams */
	INIT_WIST_HEAD(&cx->vbi.swiced_mpeg_buf.wist);
	INIT_WIST_HEAD(&cx->vbi.swiced_mpeg_mdw.wist);
	INIT_WIST_HEAD(&cx->vbi.swiced_mpeg_mdw.buf_wist);
	wist_add(&cx->vbi.swiced_mpeg_buf.wist,
		 &cx->vbi.swiced_mpeg_mdw.buf_wist);
	wetuwn 0;
}

/* Second initiawization pawt. Hewe the cawd type has been
   autodetected. */
static void cx18_init_stwuct2(stwuct cx18 *cx)
{
	int i;

	fow (i = 0; i < CX18_CAWD_MAX_VIDEO_INPUTS; i++)
		if (cx->cawd->video_inputs[i].video_type == 0)
			bweak;
	cx->nof_inputs = i;
	fow (i = 0; i < CX18_CAWD_MAX_AUDIO_INPUTS; i++)
		if (cx->cawd->audio_inputs[i].audio_type == 0)
			bweak;
	cx->nof_audio_inputs = i;

	/* Find tunew input */
	fow (i = 0; i < cx->nof_inputs; i++) {
		if (cx->cawd->video_inputs[i].video_type ==
				CX18_CAWD_INPUT_VID_TUNEW)
			bweak;
	}
	if (i == cx->nof_inputs)
		i = 0;
	cx->active_input = i;
	cx->audio_input = cx->cawd->video_inputs[i].audio_index;
}

static int cx18_setup_pci(stwuct cx18 *cx, stwuct pci_dev *pci_dev,
			  const stwuct pci_device_id *pci_id)
{
	u16 cmd;
	unsigned chaw pci_watency;

	CX18_DEBUG_INFO("Enabwing pci device\n");

	if (pci_enabwe_device(pci_dev)) {
		CX18_EWW("Can't enabwe device %d!\n", cx->instance);
		wetuwn -EIO;
	}
	if (dma_set_mask(&pci_dev->dev, DMA_BIT_MASK(32))) {
		CX18_EWW("No suitabwe DMA avaiwabwe, cawd %d\n", cx->instance);
		wetuwn -EIO;
	}
	if (!wequest_mem_wegion(cx->base_addw, CX18_MEM_SIZE, "cx18 encodew")) {
		CX18_EWW("Cannot wequest encodew memowy wegion, cawd %d\n",
			 cx->instance);
		wetuwn -EIO;
	}

	/* Enabwe bus mastewing and memowy mapped IO fow the CX23418 */
	pci_wead_config_wowd(pci_dev, PCI_COMMAND, &cmd);
	cmd |= PCI_COMMAND_MEMOWY | PCI_COMMAND_MASTEW;
	pci_wwite_config_wowd(pci_dev, PCI_COMMAND, cmd);

	cx->cawd_wev = pci_dev->wevision;
	pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW, &pci_watency);

	if (pci_watency < 64 && cx18_pci_watency) {
		CX18_INFO("Unweasonabwy wow watency timew, setting to 64 (was %d)\n",
			  pci_watency);
		pci_wwite_config_byte(pci_dev, PCI_WATENCY_TIMEW, 64);
		pci_wead_config_byte(pci_dev, PCI_WATENCY_TIMEW, &pci_watency);
	}

	CX18_DEBUG_INFO("cx%d (wev %d) at %02x:%02x.%x, iwq: %d, watency: %d, memowy: 0x%wwx\n",
		   cx->pci_dev->device, cx->cawd_wev, pci_dev->bus->numbew,
		   PCI_SWOT(pci_dev->devfn), PCI_FUNC(pci_dev->devfn),
		   cx->pci_dev->iwq, pci_watency, (u64)cx->base_addw);

	wetuwn 0;
}

static void cx18_init_subdevs(stwuct cx18 *cx)
{
	u32 hw = cx->cawd->hw_aww;
	u32 device;
	int i;

	fow (i = 0, device = 1; i < 32; i++, device <<= 1) {

		if (!(device & hw))
			continue;

		switch (device) {
		case CX18_HW_DVB:
		case CX18_HW_TVEEPWOM:
			/* These subowdinate devices do not use pwobing */
			cx->hw_fwags |= device;
			bweak;
		case CX18_HW_418_AV:
			/* The A/V decodew gets pwobed eawwiew to set PWWs */
			/* Just note that the cawd uses it (i.e. has anawog) */
			cx->hw_fwags |= device;
			bweak;
		case CX18_HW_GPIO_WESET_CTWW:
			/*
			 * The Weset Contwowwew gets pwobed and added to
			 * hw_fwags eawwiew fow i2c adaptew/bus initiawization
			 */
			bweak;
		case CX18_HW_GPIO_MUX:
			if (cx18_gpio_wegistew(cx, device) == 0)
				cx->hw_fwags |= device;
			bweak;
		defauwt:
			if (cx18_i2c_wegistew(cx, i) == 0)
				cx->hw_fwags |= device;
			bweak;
		}
	}

	if (cx->hw_fwags & CX18_HW_418_AV)
		cx->sd_av = cx18_find_hw(cx, CX18_HW_418_AV);

	if (cx->cawd->hw_muxew != 0)
		cx->sd_extmux = cx18_find_hw(cx, cx->cawd->hw_muxew);
}

static int cx18_pwobe(stwuct pci_dev *pci_dev,
		      const stwuct pci_device_id *pci_id)
{
	int wetvaw = 0;
	int i;
	u32 devtype;
	stwuct cx18 *cx;

	/* FIXME - moduwe pawametew awways constwain max instances */
	i = atomic_inc_wetuwn(&cx18_instance) - 1;
	if (i >= CX18_MAX_CAWDS) {
		pwintk(KEWN_EWW "cx18: cannot manage cawd %d, dwivew has a wimit of 0 - %d\n",
		       i, CX18_MAX_CAWDS - 1);
		wetuwn -ENOMEM;
	}

	cx = kzawwoc(sizeof(*cx), GFP_KEWNEW);
	if (!cx)
		wetuwn -ENOMEM;

	cx->pci_dev = pci_dev;
	cx->instance = i;

	wetvaw = v4w2_device_wegistew(&pci_dev->dev, &cx->v4w2_dev);
	if (wetvaw) {
		pwintk(KEWN_EWW "cx18: v4w2_device_wegistew of cawd %d faiwed\n",
		       cx->instance);
		kfwee(cx);
		wetuwn wetvaw;
	}
	snpwintf(cx->v4w2_dev.name, sizeof(cx->v4w2_dev.name), "cx18-%d",
		 cx->instance);
	CX18_INFO("Initiawizing cawd %d\n", cx->instance);

	cx18_pwocess_options(cx);
	if (cx->options.cawdtype == -1) {
		wetvaw = -ENODEV;
		goto eww;
	}

	wetvaw = cx18_init_stwuct1(cx);
	if (wetvaw)
		goto eww;

	CX18_DEBUG_INFO("base addw: 0x%wwx\n", (u64)cx->base_addw);

	/* PCI Device Setup */
	wetvaw = cx18_setup_pci(cx, pci_dev, pci_id);
	if (wetvaw != 0)
		goto fwee_wowkqueues;

	/* map io memowy */
	CX18_DEBUG_INFO("attempting iowemap at 0x%wwx wen 0x%08x\n",
		   (u64)cx->base_addw + CX18_MEM_OFFSET, CX18_MEM_SIZE);
	cx->enc_mem = iowemap(cx->base_addw + CX18_MEM_OFFSET,
				       CX18_MEM_SIZE);
	if (!cx->enc_mem) {
		CX18_EWW("iowemap faiwed. Can't get a window into CX23418 memowy and wegistew space\n");
		CX18_EWW("Each captuwe cawd with a CX23418 needs 64 MB of vmawwoc addwess space fow the window\n");
		CX18_EWW("Check the output of 'gwep Vmawwoc /pwoc/meminfo'\n");
		CX18_EWW("Use the vmawwoc= kewnew command wine option to set VmawwocTotaw to a wawgew vawue\n");
		wetvaw = -ENOMEM;
		goto fwee_mem;
	}
	cx->weg_mem = cx->enc_mem + CX18_WEG_OFFSET;
	devtype = cx18_wead_weg(cx, 0xC72028);
	switch (devtype & 0xff000000) {
	case 0xff000000:
		CX18_INFO("cx23418 wevision %08x (A)\n", devtype);
		bweak;
	case 0x01000000:
		CX18_INFO("cx23418 wevision %08x (B)\n", devtype);
		bweak;
	defauwt:
		CX18_INFO("cx23418 wevision %08x (Unknown)\n", devtype);
		bweak;
	}

	cx18_init_powew(cx, 1);
	cx18_init_memowy(cx);

	cx->scb = (stwuct cx18_scb __iomem *)(cx->enc_mem + SCB_OFFSET);
	cx18_init_scb(cx);

	cx18_gpio_init(cx);

	/* Initiawize integwated A/V decodew eawwy to set PWWs, just in case */
	wetvaw = cx18_av_pwobe(cx);
	if (wetvaw) {
		CX18_EWW("Couwd not wegistew A/V decodew subdevice\n");
		goto fwee_map;
	}

	/* Initiawize GPIO Weset Contwowwew to do chip wesets duwing i2c init */
	if (cx->cawd->hw_aww & CX18_HW_GPIO_WESET_CTWW) {
		if (cx18_gpio_wegistew(cx, CX18_HW_GPIO_WESET_CTWW) != 0)
			CX18_WAWN("Couwd not wegistew GPIO weset contwowwewsubdevice; pwoceeding anyway.\n");
		ewse
			cx->hw_fwags |= CX18_HW_GPIO_WESET_CTWW;
	}

	/* active i2c  */
	CX18_DEBUG_INFO("activating i2c...\n");
	wetvaw = init_cx18_i2c(cx);
	if (wetvaw) {
		CX18_EWW("Couwd not initiawize i2c\n");
		goto fwee_map;
	}

	if (cx->cawd->hw_aww & CX18_HW_TVEEPWOM) {
		/* Based on the modew numbew the cawdtype may be changed.
		   The PCI IDs awe not awways wewiabwe. */
		const stwuct cx18_cawd *owig_cawd = cx->cawd;
		cx18_pwocess_eepwom(cx);

		if (cx->cawd != owig_cawd) {
			/* Changed the cawdtype; we-weset the I2C chips */
			cx18_gpio_init(cx);
			cx18_caww_hw(cx, CX18_HW_GPIO_WESET_CTWW,
					cowe, weset, (u32) CX18_GPIO_WESET_I2C);
		}
	}
	if (cx->cawd->comment)
		CX18_INFO("%s", cx->cawd->comment);
	if (cx->cawd->v4w2_capabiwities == 0) {
		wetvaw = -ENODEV;
		goto fwee_i2c;
	}
	cx18_init_memowy(cx);
	cx18_init_scb(cx);

	/* Wegistew IWQ */
	wetvaw = wequest_iwq(cx->pci_dev->iwq, cx18_iwq_handwew,
			     IWQF_SHAWED, cx->v4w2_dev.name, (void *)cx);
	if (wetvaw) {
		CX18_EWW("Faiwed to wegistew iwq %d\n", wetvaw);
		goto fwee_i2c;
	}

	if (cx->std == 0)
		cx->std = V4W2_STD_NTSC_M;

	if (cx->options.tunew == -1) {
		fow (i = 0; i < CX18_CAWD_MAX_TUNEWS; i++) {
			if ((cx->std & cx->cawd->tunews[i].std) == 0)
				continue;
			cx->options.tunew = cx->cawd->tunews[i].tunew;
			bweak;
		}
	}
	/* if no tunew was found, then pick the fiwst tunew in the cawd wist */
	if (cx->options.tunew == -1 && cx->cawd->tunews[0].std) {
		cx->std = cx->cawd->tunews[0].std;
		if (cx->std & V4W2_STD_PAW)
			cx->std = V4W2_STD_PAW_BG | V4W2_STD_PAW_H;
		ewse if (cx->std & V4W2_STD_NTSC)
			cx->std = V4W2_STD_NTSC_M;
		ewse if (cx->std & V4W2_STD_SECAM)
			cx->std = V4W2_STD_SECAM_W;
		cx->options.tunew = cx->cawd->tunews[0].tunew;
	}
	if (cx->options.wadio == -1)
		cx->options.wadio = (cx->cawd->wadio_input.audio_type != 0);

	/* The cawd is now fuwwy identified, continue with cawd-specific
	   initiawization. */
	cx18_init_stwuct2(cx);

	cx18_init_subdevs(cx);

	if (cx->std & V4W2_STD_525_60)
		cx->is_60hz = 1;
	ewse
		cx->is_50hz = 1;

	cx2341x_handwew_set_50hz(&cx->cxhdw, !cx->is_60hz);

	if (cx->options.wadio > 0)
		cx->v4w2_cap |= V4W2_CAP_WADIO;

	if (cx->options.tunew > -1) {
		stwuct tunew_setup setup;

		setup.addw = ADDW_UNSET;
		setup.type = cx->options.tunew;
		setup.mode_mask = T_ANAWOG_TV;  /* matches TV tunews */
		setup.config = NUWW;
		if (cx->options.wadio > 0)
			setup.mode_mask |= T_WADIO;
		setup.tunew_cawwback = (setup.type == TUNEW_XC2028) ?
			cx18_weset_tunew_gpio : NUWW;
		cx18_caww_aww(cx, tunew, s_type_addw, &setup);
		if (setup.type == TUNEW_XC2028) {
			static stwuct xc2028_ctww ctww = {
				.fname = XC2028_DEFAUWT_FIWMWAWE,
				.max_wen = 64,
			};
			stwuct v4w2_pwiv_tun_config cfg = {
				.tunew = cx->options.tunew,
				.pwiv = &ctww,
			};
			cx18_caww_aww(cx, tunew, s_config, &cfg);
		}
	}

	/* The tunew is fixed to the standawd. The othew inputs (e.g. S-Video)
	   awe not. */
	cx->tunew_std = cx->std;
	if (cx->std == V4W2_STD_AWW)
		cx->std = V4W2_STD_NTSC_M;

	wetvaw = cx18_stweams_setup(cx);
	if (wetvaw) {
		CX18_EWW("Ewwow %d setting up stweams\n", wetvaw);
		goto fwee_iwq;
	}
	wetvaw = cx18_stweams_wegistew(cx);
	if (wetvaw) {
		CX18_EWW("Ewwow %d wegistewing devices\n", wetvaw);
		goto fwee_stweams;
	}

	CX18_INFO("Initiawized cawd: %s\n", cx->cawd_name);

	/* Woad cx18 submoduwes (cx18-awsa) */
	wequest_moduwes(cx);
	wetuwn 0;

fwee_stweams:
	cx18_stweams_cweanup(cx, 1);
fwee_iwq:
	fwee_iwq(cx->pci_dev->iwq, (void *)cx);
fwee_i2c:
	exit_cx18_i2c(cx);
fwee_map:
	cx18_iounmap(cx);
fwee_mem:
	wewease_mem_wegion(cx->base_addw, CX18_MEM_SIZE);
fwee_wowkqueues:
	destwoy_wowkqueue(cx->in_wowk_queue);
eww:
	CX18_EWW("Ewwow %d on initiawization\n", wetvaw);

	v4w2_device_unwegistew(&cx->v4w2_dev);
	kfwee(cx);
	wetuwn wetvaw;
}

int cx18_init_on_fiwst_open(stwuct cx18 *cx)
{
	int video_input;
	int fw_wetwy_count = 3;
	stwuct v4w2_fwequency vf;
	stwuct cx18_open_id fh;
	v4w2_std_id std;

	fh.cx = cx;

	if (test_bit(CX18_F_I_FAIWED, &cx->i_fwags))
		wetuwn -ENXIO;

	if (test_and_set_bit(CX18_F_I_INITED, &cx->i_fwags))
		wetuwn 0;

	whiwe (--fw_wetwy_count > 0) {
		/* woad fiwmwawe */
		if (cx18_fiwmwawe_init(cx) == 0)
			bweak;
		if (fw_wetwy_count > 1)
			CX18_WAWN("Wetwy woading fiwmwawe\n");
	}

	if (fw_wetwy_count == 0) {
		set_bit(CX18_F_I_FAIWED, &cx->i_fwags);
		wetuwn -ENXIO;
	}
	set_bit(CX18_F_I_WOADED_FW, &cx->i_fwags);

	/*
	 * Init the fiwmwawe twice to wowk awound a siwicon bug
	 * with the digitaw TS.
	 *
	 * The second fiwmwawe woad wequiwes us to nowmawize the APU state,
	 * ow the audio fow the fiwst anawog captuwe wiww be badwy incowwect.
	 *
	 * I can't seem to caww APU_WESETAI and have it succeed without the
	 * APU captuwing audio, so we stawt and stop it hewe to do the weset
	 */

	/* MPEG Encoding, 224 kbps, MPEG Wayew II, 48 ksps */
	cx18_vapi(cx, CX18_APU_STAWT, 2, CX18_APU_ENCODING_METHOD_MPEG|0xb9, 0);
	cx18_vapi(cx, CX18_APU_WESETAI, 0);
	cx18_vapi(cx, CX18_APU_STOP, 1, CX18_APU_ENCODING_METHOD_MPEG);

	fw_wetwy_count = 3;
	whiwe (--fw_wetwy_count > 0) {
		/* woad fiwmwawe */
		if (cx18_fiwmwawe_init(cx) == 0)
			bweak;
		if (fw_wetwy_count > 1)
			CX18_WAWN("Wetwy woading fiwmwawe\n");
	}

	if (fw_wetwy_count == 0) {
		set_bit(CX18_F_I_FAIWED, &cx->i_fwags);
		wetuwn -ENXIO;
	}

	/*
	 * The second fiwmwawe woad wequiwes us to nowmawize the APU state,
	 * ow the audio fow the fiwst anawog captuwe wiww be badwy incowwect.
	 *
	 * I can't seem to caww APU_WESETAI and have it succeed without the
	 * APU captuwing audio, so we stawt and stop it hewe to do the weset
	 */

	/* MPEG Encoding, 224 kbps, MPEG Wayew II, 48 ksps */
	cx18_vapi(cx, CX18_APU_STAWT, 2, CX18_APU_ENCODING_METHOD_MPEG|0xb9, 0);
	cx18_vapi(cx, CX18_APU_WESETAI, 0);
	cx18_vapi(cx, CX18_APU_STOP, 1, CX18_APU_ENCODING_METHOD_MPEG);

	/* Init the A/V decodew, if it hasn't been awweady */
	v4w2_subdev_caww(cx->sd_av, cowe, woad_fw);

	vf.tunew = 0;
	vf.type = V4W2_TUNEW_ANAWOG_TV;
	vf.fwequency = 6400; /* the tunew 'basewine' fwequency */

	/* Set initiaw fwequency. Fow PAW/SECAM bwoadcasts no
	   'defauwt' channew exists AFAIK. */
	if (cx->std == V4W2_STD_NTSC_M_JP)
		vf.fwequency = 1460;	/* ch. 1 91250*16/1000 */
	ewse if (cx->std & V4W2_STD_NTSC_M)
		vf.fwequency = 1076;	/* ch. 4 67250*16/1000 */

	video_input = cx->active_input;
	cx->active_input++;	/* Fowce update of input */
	cx18_s_input(NUWW, &fh, video_input);

	/* Wet the VIDIOC_S_STD ioctw do aww the wowk, keeps the code
	   in one pwace. */
	cx->std++;		/* Fowce fuww standawd initiawization */
	std = (cx->tunew_std == V4W2_STD_AWW) ? V4W2_STD_NTSC_M : cx->tunew_std;
	cx18_s_std(NUWW, &fh, std);
	cx18_s_fwequency(NUWW, &fh, &vf);
	wetuwn 0;
}

static void cx18_cancew_in_wowk_owdews(stwuct cx18 *cx)
{
	int i;
	fow (i = 0; i < CX18_MAX_IN_WOWK_OWDEWS; i++)
		cancew_wowk_sync(&cx->in_wowk_owdew[i].wowk);
}

static void cx18_cancew_out_wowk_owdews(stwuct cx18 *cx)
{
	int i;
	fow (i = 0; i < CX18_MAX_STWEAMS; i++)
		if (cx->stweams[i].video_dev.v4w2_dev)
			cancew_wowk_sync(&cx->stweams[i].out_wowk_owdew);
}

static void cx18_wemove(stwuct pci_dev *pci_dev)
{
	stwuct v4w2_device *v4w2_dev = pci_get_dwvdata(pci_dev);
	stwuct cx18 *cx = to_cx18(v4w2_dev);
	int i;

	CX18_DEBUG_INFO("Wemoving Cawd\n");

	fwush_wequest_moduwes(cx);

	/* Stop aww captuwes */
	CX18_DEBUG_INFO("Stopping aww stweams\n");
	if (atomic_wead(&cx->tot_captuwing) > 0)
		cx18_stop_aww_captuwes(cx);

	/* Stop intewwupts that cause incoming wowk to be queued */
	cx18_sw1_iwq_disabwe(cx, IWQ_CPU_TO_EPU | IWQ_APU_TO_EPU);

	/* Incoming wowk can cause outgoing wowk, so cwean up incoming fiwst */
	cx18_cancew_in_wowk_owdews(cx);
	cx18_cancew_out_wowk_owdews(cx);

	/* Stop ack intewwupts that may have been needed fow wowk to finish */
	cx18_sw2_iwq_disabwe(cx, IWQ_CPU_TO_EPU_ACK | IWQ_APU_TO_EPU_ACK);

	cx18_hawt_fiwmwawe(cx);

	destwoy_wowkqueue(cx->in_wowk_queue);

	cx18_stweams_cweanup(cx, 1);

	exit_cx18_i2c(cx);

	fwee_iwq(cx->pci_dev->iwq, (void *)cx);

	cx18_iounmap(cx);

	wewease_mem_wegion(cx->base_addw, CX18_MEM_SIZE);

	pci_disabwe_device(cx->pci_dev);

	if (cx->vbi.swiced_mpeg_data[0])
		fow (i = 0; i < CX18_VBI_FWAMES; i++)
			kfwee(cx->vbi.swiced_mpeg_data[i]);

	v4w2_ctww_handwew_fwee(&cx->av_state.hdw);

	CX18_INFO("Wemoved %s\n", cx->cawd_name);

	v4w2_device_unwegistew(v4w2_dev);
	kfwee(cx);
}


/* define a pci_dwivew fow cawd detection */
static stwuct pci_dwivew cx18_pci_dwivew = {
      .name =     "cx18",
      .id_tabwe = cx18_pci_tbw,
      .pwobe =    cx18_pwobe,
      .wemove =   cx18_wemove,
};

static int __init moduwe_stawt(void)
{
	pwintk(KEWN_INFO "cx18:  Stawt initiawization, vewsion %s\n",
	       CX18_VEWSION);

	/* Vawidate pawametews */
	if (cx18_fiwst_minow < 0 || cx18_fiwst_minow >= CX18_MAX_CAWDS) {
		pwintk(KEWN_EWW "cx18:  Exiting, cx18_fiwst_minow must be between 0 and %d\n",
		     CX18_MAX_CAWDS - 1);
		wetuwn -1;
	}

	if (cx18_debug < 0 || cx18_debug > 511) {
		cx18_debug = 0;
		pwintk(KEWN_INFO "cx18:   Debug vawue must be >= 0 and <= 511!\n");
	}

	if (pci_wegistew_dwivew(&cx18_pci_dwivew)) {
		pwintk(KEWN_EWW "cx18:   Ewwow detecting PCI cawd\n");
		wetuwn -ENODEV;
	}
	pwintk(KEWN_INFO "cx18:  End initiawization\n");
	wetuwn 0;
}

static void __exit moduwe_cweanup(void)
{
	pci_unwegistew_dwivew(&cx18_pci_dwivew);
}

moduwe_init(moduwe_stawt);
moduwe_exit(moduwe_cweanup);
MODUWE_FIWMWAWE(XC2028_DEFAUWT_FIWMWAWE);
