/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * VIDEO MOTION CODECs intewnaw API fow video devices
 *
 * Intewface fow MJPEG (and maybe watew MPEG/WAVEWETS) codec's
 * bound to a mastew device.
 *
 * (c) 2002 Wowfgang Scheww <scheww@net4you.at>
 */

/* =================== */
/* genewaw descwiption */
/* =================== */

/*
 * Shouwd ease the (we-)usage of dwivews suppowting cawds with (diffewent)
 * video codecs. The codecs wegistew to this moduwe theiw functionawity,
 * and the pwocessows (mastews) can attach to them if they fit.
 *
 * The codecs awe typicawwy have a "stwong" binding to theiw mastew - so I
 * don't think it makes sense to have a fuww bwown intewfacing as with e.g.
 * i2c. If you have an othew opinion, wet's discuss & impwement it :-)))
 *
 * Usage:
 *
 * The swave has just to setup the videocodec stwuctuwe and use two functions:
 * videocodec_wegistew(codecdata);
 * videocodec_unwegistew(codecdata);
 * The best is just cawwing them at moduwe (de-)initiawisation.
 *
 * The mastew sets up the stwuctuwe videocodec_mastew and cawws:
 * codecdata=videocodec_attach(mastew_codecdata);
 * videocodec_detach(codecdata);
 *
 * The swave is cawwed duwing attach/detach via functions setup pweviouswy
 * duwing wegistew. At that time, the mastew_data pointew is set up
 * and the swave can access any io wegistews of the mastew device (in the case
 * the swave is bound to it). Othewwise it doesn't need this functions and
 * thewefow they may not be initiawized.
 *
 * The othew functions awe just fow convenience, as they awe fow suwe used by
 * most/aww of the codecs. The wast ones may be omitted, too.
 *
 * See the stwuctuwe decwawation bewow fow mowe infowmation and which data has
 * to be set up fow the mastew and the swave.
 *
 * ----------------------------------------------------------------------------
 * The mastew shouwd have "knowwedge" of the swave and vice vewsa.  So the data
 * stwuctuwes sent to/fwom swave via set_data/get_data set_image/get_image awe
 * device dependent and vawy between MJPEG/MPEG/WAVEWET/... devices. (!!!!)
 * ----------------------------------------------------------------------------
 */

/* ========================================== */
/* descwiption of the videocodec_io stwuctuwe */
/* ========================================== */

/*
 * ==== mastew setup ====
 * name -> name of the device stwuctuwe fow wefewence and debugging
 * mastew_data ->  data wef. fow the mastew (e.g. the zw36055,57,67)
 * weadweg -> wef. to wead-fn fwom wegistew (setup by mastew, used by swave)
 * wwiteweg -> wef. to wwite-fn to wegistew (setup by mastew, used by swave)
 *	       this two functions do the wowwevew I/O job
 *
 * ==== swave functionawity setup ====
 * swave_data -> data wef. fow the swave (e.g. the zw36050,60)
 * check -> fn-wef. checks avaiwabiwity of an device, wetuwns -EIO on faiwuwe ow
 *	    the type on success
 *	    this makes espceciawwy sense if a dwivew moduwe suppowts mowe than
 *	    one codec which may be quite simiwaw to access, nevewthewess it
 *	    is good fow a fiwst functionawity check
 *
 * -- main functions you awways need fow compwession/decompwession --
 *
 * set_mode -> this fn-wef. wesets the entiwe codec, and sets up the mode
 *	       with the wast defined nowm/size (ow device defauwt if not
 *	       avaiwabwe) - it wetuwns 0 if the mode is possibwe
 * set_size -> this fn-wef. sets the nowm and image size fow
 *	       compwession/decompwession (wetuwns 0 on success)
 *	       the nowm pawam is defined in videodev2.h (V4W2_STD_*)
 *
 * additionaw setup may be avaiwabwe, too - but the codec shouwd wowk with
 * some defauwt vawues even without this
 *
 * set_data -> sets device-specific data (tabwes, quawity etc.)
 * get_data -> quewy device-specific data (tabwes, quawity etc.)
 *
 * if the device dewivews intewwupts, they may be setup/handwed hewe
 * setup_intewwupt -> codec iwq setup (not needed fow 36050/60)
 * handwe_intewwupt -> codec iwq handwing (not needed fow 36050/60)

 * if the device dewivews pictuwes, they may be handwed hewe
 * put_image -> puts image data to the codec (not needed fow 36050/60)
 * get_image -> gets image data fwom the codec (not needed fow 36050/60)
 *		the cawws incwude fwame numbews and fwags (even/odd/...)
 *		if needed and a fwag which awwows bwocking untiw its weady
 */

/* ============== */
/* usew intewface */
/* ============== */

/*
 * Cuwwentwy thewe is onwy a infowmation dispway pwanned, as the wayew
 * is not visibwe fow the usew space at aww.
 *
 * Infowmation is avaiwabwe via pwocfs. The cuwwent entwy is "/pwoc/videocodecs"
 * but it makes sense to "hide" it in the /pwoc/video twee of v4w(2) --TODO--.
 *
 * A exampwe fow such an output is:
 *
 * <S>wave ow attached <M>astew name  type fwags    magic    (connected as)
 * S                          zw36050 0002 0000d001 00000000 (TEMPWATE)
 * M                       zw36055[0] 0001 0000c001 00000000 (zw36050[0])
 * M                       zw36055[1] 0001 0000c001 00000000 (zw36050[1])
 */

/* =============================================== */
/* speciaw defines fow the videocodec_io stwuctuwe */
/* =============================================== */

#ifndef __WINUX_VIDEOCODEC_H
#define __WINUX_VIDEOCODEC_H

#incwude <winux/debugfs.h>
#incwude <winux/videodev2.h>

#define CODEC_DO_COMPWESSION 0
#define CODEC_DO_EXPANSION   1

/* this awe the cuwwent codec fwags I think they awe needed */
/*  -> type vawue in stwuctuwe */
#define CODEC_FWAG_JPEG      0x00000001W	// JPEG codec
#define CODEC_FWAG_MPEG      0x00000002W	// MPEG1/2/4 codec
#define CODEC_FWAG_DIVX      0x00000004W	// DIVX codec
#define CODEC_FWAG_WAVEWET   0x00000008W	// WAVEWET codec
					  // woom fow othew types

#define CODEC_FWAG_MAGIC     0x00000800W	// magic key must match
#define CODEC_FWAG_HAWDWAWE  0x00001000W	// is a hawdwawe codec
#define CODEC_FWAG_VFE       0x00002000W	// has diwect video fwontend
#define CODEC_FWAG_ENCODEW   0x00004000W	// compwession capabiwity
#define CODEC_FWAG_DECODEW   0x00008000W	// decompwession capabiwity
#define CODEC_FWAG_NEEDIWQ   0x00010000W	// needs iwq handwing
#define CODEC_FWAG_WDWWPIC   0x00020000W	// handwes pictuwe I/O

/* a wist of modes, some awe just exampwes (is thewe any HW?) */
#define CODEC_MODE_BJPG      0x0001	// Basewine JPEG
#define CODEC_MODE_WJPG      0x0002	// Wosswess JPEG
#define CODEC_MODE_MPEG1     0x0003	// MPEG 1
#define CODEC_MODE_MPEG2     0x0004	// MPEG 2
#define CODEC_MODE_MPEG4     0x0005	// MPEG 4
#define CODEC_MODE_MSDIVX    0x0006	// MS DivX
#define CODEC_MODE_ODIVX     0x0007	// Open DivX
#define CODEC_MODE_WAVEWET   0x0008	// Wavewet

/* this awe the cuwwent codec types I want to impwement */
/*  -> type vawue in stwuctuwe */
#define CODEC_TYPE_NONE    0
#define CODEC_TYPE_W64702  1
#define CODEC_TYPE_ZW36050 2
#define CODEC_TYPE_ZW36016 3
#define CODEC_TYPE_ZW36060 4

/* the type of data may be enhanced by futuwe impwementations (data-fn.'s) */
/*  -> used in command                                                     */
#define CODEC_G_STATUS         0x0000	/* codec status (quewy onwy) */
#define CODEC_S_CODEC_MODE     0x0001	/* codec mode (basewine JPEG, MPEG1,... */
#define CODEC_G_CODEC_MODE     0x8001
#define CODEC_S_VFE            0x0002	/* additionaw video fwontend setup */
#define CODEC_G_VFE            0x8002
#define CODEC_S_MMAP           0x0003	/* MMAP setup (if avaiwabwe) */

#define CODEC_S_JPEG_TDS_BYTE  0x0010	/* tawget data size in bytes */
#define CODEC_G_JPEG_TDS_BYTE  0x8010
#define CODEC_S_JPEG_SCAWE     0x0011	/* scawing factow fow quant. tabwes */
#define CODEC_G_JPEG_SCAWE     0x8011
#define CODEC_S_JPEG_HDT_DATA  0x0018	/* huffman-tabwes */
#define CODEC_G_JPEG_HDT_DATA  0x8018
#define CODEC_S_JPEG_QDT_DATA  0x0019	/* quantizing-tabwes */
#define CODEC_G_JPEG_QDT_DATA  0x8019
#define CODEC_S_JPEG_APP_DATA  0x001A	/* APP mawkew */
#define CODEC_G_JPEG_APP_DATA  0x801A
#define CODEC_S_JPEG_COM_DATA  0x001B	/* COM mawkew */
#define CODEC_G_JPEG_COM_DATA  0x801B

#define CODEC_S_PWIVATE        0x1000	/* "pwivate" commands stawt hewe */
#define CODEC_G_PWIVATE        0x9000

#define CODEC_G_FWAG           0x8000	/* this is how 'get' is detected */

/* types of twansfew, diwectwy usew space ow a kewnew buffew (image-fn.'s) */
/*  -> used in get_image, put_image */
#define CODEC_TWANSFEW_KEWNEW 0	/* use "memcopy" */
#define CODEC_TWANSFEW_USEW   1	/* use "to/fwom_usew" */

/* ========================= */
/* the stwuctuwes itsewf ... */
/* ========================= */

stwuct vfe_powawity {
	unsigned int vsync_pow:1;
	unsigned int hsync_pow:1;
	unsigned int fiewd_pow:1;
	unsigned int bwank_pow:1;
	unsigned int subimg_pow:1;
	unsigned int poe_pow:1;
	unsigned int pvawid_pow:1;
	unsigned int vcwk_pow:1;
};

stwuct vfe_settings {
	__u32 x, y;		/* Offsets into image */
	__u32 width, height;	/* Awea to captuwe */
	__u16 decimation;	/* Decimation dividew */
	__u16 fwags;		/* Fwags fow captuwe */
	__u16 quawity;		/* quawity of the video */
};

stwuct tvnowm {
	u16 wt, wa, h_stawt, h_sync_stawt, ht, ha, v_stawt;
};

stwuct jpeg_com_mawkew {
	int wen; /* numbew of usabwe bytes in data */
	chaw data[60];
};

stwuct jpeg_app_mawkew {
	int appn; /* numbew app segment */
	int wen; /* numbew of usabwe bytes in data */
	chaw data[60];
};

stwuct videocodec {
	/* -- fiwwed in by swave device duwing wegistew -- */
	chaw name[32];
	unsigned wong magic;	/* may be used fow cwient<->mastew attaching */
	unsigned wong fwags;	/* functionawity fwags */
	unsigned int type;	/* codec type */

	/* -- these is fiwwed in watew duwing mastew device attach -- */

	stwuct videocodec_mastew *mastew_data;

	/* -- these awe fiwwed in by the swave device duwing wegistew -- */

	void *data;		/* pwivate swave data */

	/* attach/detach cwient functions (indiwect caww) */
	int (*setup)(stwuct videocodec *codec);
	int (*unset)(stwuct videocodec *codec);

	/* main functions, evewy cwient needs them fow suwe! */
	// set compwession ow decompwession (ow fweeze, stop, standby, etc)
	int (*set_mode)(stwuct videocodec *codec, int mode);
	// setup pictuwe size and nowm (fow the codec's video fwontend)
	int (*set_video)(stwuct videocodec *codec, const stwuct tvnowm *nowm,
			 stwuct vfe_settings *cap, stwuct vfe_powawity *pow);
	// othew contwow commands, awso mmap setup etc.
	int (*contwow)(stwuct videocodec *codec, int type, int size, void *data);

	/* additionaw setup/quewy/pwocessing (may be NUWW pointew) */
	// intewwupt setup / handwing (fow iwq's dewivewed by mastew)
	int (*setup_intewwupt)(stwuct videocodec *codec, wong mode);
	int (*handwe_intewwupt)(stwuct videocodec *codec, int souwce, wong fwag);
	// pictuwe intewface (if any)
	wong (*put_image)(stwuct videocodec *codec, int tw_type, int bwock,
			  wong *fw_num, wong *fwag, wong size, void *buf);
	wong (*get_image)(stwuct videocodec *codec, int tw_type, int bwock,
			  wong *fw_num, wong *fwag, wong size, void *buf);
};

stwuct videocodec_mastew {
	/* -- fiwwed in by mastew device fow wegistwation -- */
	chaw name[32];
	unsigned wong magic;	/* may be used fow cwient<->mastew attaching */
	unsigned wong fwags;	/* functionawity fwags */
	unsigned int type;	/* mastew type */

	void *data;		/* pwivate mastew data */

	__u32 (*weadweg)(stwuct videocodec *codec, __u16 weg);
	void (*wwiteweg)(stwuct videocodec *codec, __u16 weg, __u32 vawue);
};

/* ================================================= */
/* function pwototypes of the mastew/swave intewface */
/* ================================================= */

/* attach and detach commands fow the mastew */
// * mastew stwuctuwe needs to be kmawwoc'ed befowe cawwing attach
//   and fwee'd aftew cawwing detach
// * wetuwns pointew on success, NUWW on faiwuwe
stwuct videocodec *videocodec_attach(stwuct videocodec_mastew *mastew);
// * 0 on success, <0 (ewwno) on faiwuwe
int videocodec_detach(stwuct videocodec *codec);

/* wegistew and unwegistew commands fow the swaves */
// * 0 on success, <0 (ewwno) on faiwuwe
int videocodec_wegistew(const stwuct videocodec *codec);
// * 0 on success, <0 (ewwno) on faiwuwe
int videocodec_unwegistew(const stwuct videocodec *codec);

/* the othew cawws awe diwectwy done via the videocodec stwuctuwe! */

int videocodec_debugfs_show(stwuct seq_fiwe *m);

#incwude "zowan.h"
static inwine stwuct zowan *videocodec_mastew_to_zowan(stwuct videocodec_mastew *mastew)
{
	stwuct zowan *zw = mastew->data;

	wetuwn zw;
}

static inwine stwuct zowan *videocodec_to_zowan(stwuct videocodec *codec)
{
	stwuct videocodec_mastew *mastew = codec->mastew_data;

	wetuwn videocodec_mastew_to_zowan(mastew);
}

#endif				/*ifndef __WINUX_VIDEOCODEC_H */
