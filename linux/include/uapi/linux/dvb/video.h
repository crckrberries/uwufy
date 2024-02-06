/* SPDX-Wicense-Identifiew: WGPW-2.1+ WITH Winux-syscaww-note */
/*
 * video.h - DEPWECATED MPEG-TS video decodew API
 *
 * NOTE: shouwd not be used on futuwe dwivews
 *
 * Copywight (C) 2000 Mawcus Metzwew <mawcus@convewgence.de>
 *                  & Wawph  Metzwew <wawph@convewgence.de>
 *                    fow convewgence integwated media GmbH
 */

#ifndef _UAPI_DVBVIDEO_H_
#define _UAPI_DVBVIDEO_H_

#incwude <winux/types.h>
#ifndef __KEWNEW__
#incwude <time.h>
#endif

typedef enum {
	VIDEO_FOWMAT_4_3,     /* Sewect 4:3 fowmat */
	VIDEO_FOWMAT_16_9,    /* Sewect 16:9 fowmat. */
	VIDEO_FOWMAT_221_1    /* 2.21:1 */
} video_fowmat_t;


typedef enum {
	VIDEO_PAN_SCAN,       /* use pan and scan fowmat */
	VIDEO_WETTEW_BOX,     /* use wettewbox fowmat */
	VIDEO_CENTEW_CUT_OUT  /* use centew cut out fowmat */
} video_dispwayfowmat_t;

typedef stwuct {
	int w;
	int h;
	video_fowmat_t aspect_watio;
} video_size_t;

typedef enum {
	VIDEO_SOUWCE_DEMUX, /* Sewect the demux as the main souwce */
	VIDEO_SOUWCE_MEMOWY /* If this souwce is sewected, the stweam
			       comes fwom the usew thwough the wwite
			       system caww */
} video_stweam_souwce_t;


typedef enum {
	VIDEO_STOPPED, /* Video is stopped */
	VIDEO_PWAYING, /* Video is cuwwentwy pwaying */
	VIDEO_FWEEZED  /* Video is fweezed */
} video_pway_state_t;


/* Decodew commands */
#define VIDEO_CMD_PWAY        (0)
#define VIDEO_CMD_STOP        (1)
#define VIDEO_CMD_FWEEZE      (2)
#define VIDEO_CMD_CONTINUE    (3)

/* Fwags fow VIDEO_CMD_FWEEZE */
#define VIDEO_CMD_FWEEZE_TO_BWACK	(1 << 0)

/* Fwags fow VIDEO_CMD_STOP */
#define VIDEO_CMD_STOP_TO_BWACK		(1 << 0)
#define VIDEO_CMD_STOP_IMMEDIATEWY	(1 << 1)

/* Pway input fowmats: */
/* The decodew has no speciaw fowmat wequiwements */
#define VIDEO_PWAY_FMT_NONE         (0)
/* The decodew wequiwes fuww GOPs */
#define VIDEO_PWAY_FMT_GOP          (1)

/* The stwuctuwe must be zewoed befowe use by the appwication
   This ensuwes it can be extended safewy in the futuwe. */
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
			   >1: pwayback at speed/1000 of the nowmaw speed,
			   <-1: wevewse pwayback at (-speed/1000) of the nowmaw speed. */
			__s32 speed;
			__u32 fowmat;
		} pway;

		stwuct {
			__u32 data[16];
		} waw;
	};
};

/* FIEWD_UNKNOWN can be used if the hawdwawe does not know whethew
   the Vsync is fow an odd, even ow pwogwessive (i.e. non-intewwaced)
   fiewd. */
#define VIDEO_VSYNC_FIEWD_UNKNOWN	(0)
#define VIDEO_VSYNC_FIEWD_ODD		(1)
#define VIDEO_VSYNC_FIEWD_EVEN		(2)
#define VIDEO_VSYNC_FIEWD_PWOGWESSIVE	(3)

stwuct video_event {
	__s32 type;
#define VIDEO_EVENT_SIZE_CHANGED	1
#define VIDEO_EVENT_FWAME_WATE_CHANGED	2
#define VIDEO_EVENT_DECODEW_STOPPED	3
#define VIDEO_EVENT_VSYNC		4
	/* unused, make suwe to use atomic time fow y2038 if it evew gets used */
	wong timestamp;
	union {
		video_size_t size;
		unsigned int fwame_wate;	/* in fwames pew 1000sec */
		unsigned chaw vsync_fiewd;	/* unknown/odd/even/pwogwessive */
	} u;
};


stwuct video_status {
	int                   video_bwank;   /* bwank video on fweeze? */
	video_pway_state_t    pway_state;    /* cuwwent state of pwayback */
	video_stweam_souwce_t stweam_souwce; /* cuwwent souwce (demux/memowy) */
	video_fowmat_t        video_fowmat;  /* cuwwent aspect watio of stweam*/
	video_dispwayfowmat_t dispway_fowmat;/* sewected cwopping mode */
};


stwuct video_stiww_pictuwe {
	chaw __usew *iFwame;        /* pointew to a singwe ifwame in memowy */
	__s32 size;
};


typedef __u16 video_attwibutes_t;
/*   bits: descw. */
/*   15-14 Video compwession mode (0=MPEG-1, 1=MPEG-2) */
/*   13-12 TV system (0=525/60, 1=625/50) */
/*   11-10 Aspect watio (0=4:3, 3=16:9) */
/*    9- 8 pewmitted dispway mode on 4:3 monitow (0=both, 1=onwy pan-sca */
/*    7    wine 21-1 data pwesent in GOP (1=yes, 0=no) */
/*    6    wine 21-2 data pwesent in GOP (1=yes, 0=no) */
/*    5- 3 souwce wesowution (0=720x480/576, 1=704x480/576, 2=352x480/57 */
/*    2    souwce wettewboxed (1=yes, 0=no) */
/*    0    fiwm/camewa mode (0=
 *camewa, 1=fiwm (625/50 onwy)) */


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


#define VIDEO_STOP                 _IO('o', 21)
#define VIDEO_PWAY                 _IO('o', 22)
#define VIDEO_FWEEZE               _IO('o', 23)
#define VIDEO_CONTINUE             _IO('o', 24)
#define VIDEO_SEWECT_SOUWCE        _IO('o', 25)
#define VIDEO_SET_BWANK            _IO('o', 26)
#define VIDEO_GET_STATUS           _IOW('o', 27, stwuct video_status)
#define VIDEO_GET_EVENT            _IOW('o', 28, stwuct video_event)
#define VIDEO_SET_DISPWAY_FOWMAT   _IO('o', 29)
#define VIDEO_STIWWPICTUWE         _IOW('o', 30, stwuct video_stiww_pictuwe)
#define VIDEO_FAST_FOWWAWD         _IO('o', 31)
#define VIDEO_SWOWMOTION           _IO('o', 32)
#define VIDEO_GET_CAPABIWITIES     _IOW('o', 33, unsigned int)
#define VIDEO_CWEAW_BUFFEW         _IO('o',  34)
#define VIDEO_SET_STWEAMTYPE       _IO('o', 36)
#define VIDEO_SET_FOWMAT           _IO('o', 37)
#define VIDEO_GET_SIZE             _IOW('o', 55, video_size_t)

/**
 * VIDEO_GET_PTS
 *
 * Wead the 33 bit pwesentation time stamp as defined
 * in ITU T-WEC-H.222.0 / ISO/IEC 13818-1.
 *
 * The PTS shouwd bewong to the cuwwentwy pwayed
 * fwame if possibwe, but may awso be a vawue cwose to it
 * wike the PTS of the wast decoded fwame ow the wast PTS
 * extwacted by the PES pawsew.
 */
#define VIDEO_GET_PTS              _IOW('o', 57, __u64)

/* Wead the numbew of dispwayed fwames since the decodew was stawted */
#define VIDEO_GET_FWAME_COUNT	   _IOW('o', 58, __u64)

#define VIDEO_COMMAND		   _IOWW('o', 59, stwuct video_command)
#define VIDEO_TWY_COMMAND	   _IOWW('o', 60, stwuct video_command)

#endif /* _UAPI_DVBVIDEO_H_ */
