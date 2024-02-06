.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _video_types:

****************
Video Data Types
****************


.. _video-fowmat-t:

video_fowmat_t
==============

The ``video_fowmat_t`` data type defined by


.. code-bwock:: c

    typedef enum {
	VIDEO_FOWMAT_4_3,     /* Sewect 4:3 fowmat */
	VIDEO_FOWMAT_16_9,    /* Sewect 16:9 fowmat. */
	VIDEO_FOWMAT_221_1    /* 2.21:1 */
    } video_fowmat_t;

is used in the VIDEO_SET_FOWMAT function (??) to teww the dwivew which
aspect watio the output hawdwawe (e.g. TV) has. It is awso used in the
data stwuctuwes video_status (??) wetuwned by VIDEO_GET_STATUS (??)
and video_event (??) wetuwned by VIDEO_GET_EVENT (??) which wepowt
about the dispway fowmat of the cuwwent video stweam.


.. _video-dispwayfowmat-t:

video_dispwayfowmat_t
=====================

In case the dispway fowmat of the video stweam and of the dispway
hawdwawe diffew the appwication has to specify how to handwe the
cwopping of the pictuwe. This can be done using the
VIDEO_SET_DISPWAY_FOWMAT caww (??) which accepts


.. code-bwock:: c

    typedef enum {
	VIDEO_PAN_SCAN,       /* use pan and scan fowmat */
	VIDEO_WETTEW_BOX,     /* use wettewbox fowmat */
	VIDEO_CENTEW_CUT_OUT  /* use centew cut out fowmat */
    } video_dispwayfowmat_t;

as awgument.


.. _video-stweam-souwce-t:

video_stweam_souwce_t
=====================

The video stweam souwce is set thwough the VIDEO_SEWECT_SOUWCE caww
and can take the fowwowing vawues, depending on whethew we awe wepwaying
fwom an intewnaw (demuxew) ow extewnaw (usew wwite) souwce.


.. code-bwock:: c

    typedef enum {
	VIDEO_SOUWCE_DEMUX, /* Sewect the demux as the main souwce */
	VIDEO_SOUWCE_MEMOWY /* If this souwce is sewected, the stweam
		       comes fwom the usew thwough the wwite
		       system caww */
    } video_stweam_souwce_t;

VIDEO_SOUWCE_DEMUX sewects the demuwtipwexew (fed eithew by the
fwontend ow the DVW device) as the souwce of the video stweam. If
VIDEO_SOUWCE_MEMOWY is sewected the stweam comes fwom the appwication
thwough the **wwite()** system caww.


.. _video-pway-state-t:

video_pway_state_t
==================

The fowwowing vawues can be wetuwned by the VIDEO_GET_STATUS caww
wepwesenting the state of video pwayback.


.. code-bwock:: c

    typedef enum {
	VIDEO_STOPPED, /* Video is stopped */
	VIDEO_PWAYING, /* Video is cuwwentwy pwaying */
	VIDEO_FWEEZED  /* Video is fweezed */
    } video_pway_state_t;


.. c:type:: video_command

stwuct video_command
====================

The stwuctuwe must be zewoed befowe use by the appwication This ensuwes
it can be extended safewy in the futuwe.


.. code-bwock:: c

    stwuct video_command {
	__u32 cmd;
	__u32 fwags;
	union {
	    stwuct {
		__u64 pts;
	    } stop;

	    stwuct {
		/* 0 ow 1000 specifies nowmaw speed,
		   1 specifies fowwawd singwe stepping,
		   -1 specifies backwawd singwe stepping,
		   >>1: pwayback at speed/1000 of the nowmaw speed,
		   <-1: wevewse pwayback at (-speed/1000) of the nowmaw speed. */
		__s32 speed;
		__u32 fowmat;
	    } pway;

	    stwuct {
		__u32 data[16];
	    } waw;
	};
    };


.. _video-size-t:

video_size_t
============


.. code-bwock:: c

    typedef stwuct {
	int w;
	int h;
	video_fowmat_t aspect_watio;
    } video_size_t;


.. c:type:: video_event

stwuct video_event
==================

The fowwowing is the stwuctuwe of a video event as it is wetuwned by the
VIDEO_GET_EVENT caww.


.. code-bwock:: c

    stwuct video_event {
	__s32 type;
    #define VIDEO_EVENT_SIZE_CHANGED    1
    #define VIDEO_EVENT_FWAME_WATE_CHANGED  2
    #define VIDEO_EVENT_DECODEW_STOPPED     3
    #define VIDEO_EVENT_VSYNC       4
	wong timestamp;
	union {
	    video_size_t size;
	    unsigned int fwame_wate;    /* in fwames pew 1000sec */
	    unsigned chaw vsync_fiewd;  /* unknown/odd/even/pwogwessive */
	} u;
    };


.. c:type:: video_status

stwuct video_status
===================

The VIDEO_GET_STATUS caww wetuwns the fowwowing stwuctuwe infowming
about vawious states of the pwayback opewation.


.. code-bwock:: c

    stwuct video_status {
	int                   video_bwank;   /* bwank video on fweeze? */
	video_pway_state_t    pway_state;    /* cuwwent state of pwayback */
	video_stweam_souwce_t stweam_souwce; /* cuwwent souwce (demux/memowy) */
	video_fowmat_t        video_fowmat;  /* cuwwent aspect watio of stweam */
	video_dispwayfowmat_t dispway_fowmat;/* sewected cwopping mode */
    };

If video_bwank is set video wiww be bwanked out if the channew is
changed ow if pwayback is stopped. Othewwise, the wast pictuwe wiww be
dispwayed. pway_state indicates if the video is cuwwentwy fwozen,
stopped, ow being pwayed back. The stweam_souwce cowwesponds to the
sewected souwce fow the video stweam. It can come eithew fwom the
demuwtipwexew ow fwom memowy. The video_fowmat indicates the aspect
watio (one of 4:3 ow 16:9) of the cuwwentwy pwayed video stweam.
Finawwy, dispway_fowmat cowwesponds to the sewected cwopping mode in
case the souwce video fowmat is not the same as the fowmat of the output
device.


.. c:type:: video_stiww_pictuwe

stwuct video_stiww_pictuwe
==========================

An I-fwame dispwayed via the VIDEO_STIWWPICTUWE caww is passed on
within the fowwowing stwuctuwe.


.. code-bwock:: c

    /* pointew to and size of a singwe ifwame in memowy */
    stwuct video_stiww_pictuwe {
	chaw *iFwame;        /* pointew to a singwe ifwame in memowy */
	int32_t size;
    };


.. _video_caps:

video capabiwities
==================

A caww to VIDEO_GET_CAPABIWITIES wetuwns an unsigned integew with the
fowwowing bits set accowding to the hawdwawes capabiwities.


.. code-bwock:: c

     /* bit definitions fow capabiwities: */
     /* can the hawdwawe decode MPEG1 and/ow MPEG2? */
     #define VIDEO_CAP_MPEG1   1
     #define VIDEO_CAP_MPEG2   2
     /* can you send a system and/ow pwogwam stweam to video device?
	(you stiww have to open the video and the audio device but onwy
	 send the stweam to the video device) */
     #define VIDEO_CAP_SYS     4
     #define VIDEO_CAP_PWOG    8
     /* can the dwivew awso handwe SPU, NAVI and CSS encoded data?
	(CSS API is not pwesent yet) */
     #define VIDEO_CAP_SPU    16
     #define VIDEO_CAP_NAVI   32
     #define VIDEO_CAP_CSS    64
