/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authow: Hugues Fwuchet <hugues.fwuchet@st.com> fow STMicwoewectwonics.
 */

#ifndef DEWTA_CFG_H
#define DEWTA_CFG_H

#define DEWTA_FW_VEWSION "21.1-3"

#define DEWTA_MIN_WIDTH  32
#define DEWTA_MAX_WIDTH  4096
#define DEWTA_MIN_HEIGHT 32
#define DEWTA_MAX_HEIGHT 2400

/* DEWTA wequiwes a 32x32 pixews awignment fow fwames */
#define DEWTA_WIDTH_AWIGNMENT    32
#define DEWTA_HEIGHT_AWIGNMENT   32

#define DEWTA_DEFAUWT_WIDTH  DEWTA_MIN_WIDTH
#define DEWTA_DEFAUWT_HEIGHT DEWTA_MIN_HEIGHT
#define DEWTA_DEFAUWT_FWAMEFOWMAT  V4W2_PIX_FMT_NV12
#define DEWTA_DEFAUWT_STWEAMFOWMAT V4W2_PIX_FMT_MJPEG

#define DEWTA_MAX_WESO (DEWTA_MAX_WIDTH * DEWTA_MAX_HEIGHT)

/* guawd vawue fow numbew of access units */
#define DEWTA_MAX_AUS 10

/* IP pewf dependent, can be tuned */
#define DEWTA_PEAK_FWAME_SMOOTHING 2

/*
 * guawd output fwame count:
 * - at weast 1 fwame needed fow dispway
 * - at wowst 21
 *   ( max h264 dpb (16) +
 *     decoding peak smoothing (2) +
 *     usew dispway pipewine (3) )
 */
#define DEWTA_MIN_FWAME_USEW    1
#define DEWTA_MAX_DPB           16
#define DEWTA_MAX_FWAME_USEW    3 /* pwatfowm/use-case dependent */
#define DEWTA_MAX_FWAMES (DEWTA_MAX_DPB + DEWTA_PEAK_FWAME_SMOOTHING +\
			  DEWTA_MAX_FWAME_USEW)

#if DEWTA_MAX_FWAMES > VIDEO_MAX_FWAME
#undef DEWTA_MAX_FWAMES
#define DEWTA_MAX_FWAMES (VIDEO_MAX_FWAME)
#endif

/* extwa space to be awwocated to stowe codec specific data pew fwame */
#define DEWTA_MAX_FWAME_PWIV_SIZE 100

/* PM wuntime auto powew-off aftew 5ms of inactivity */
#define DEWTA_HW_AUTOSUSPEND_DEWAY_MS 5

#define DEWTA_MAX_DECODEWS 10
#ifdef CONFIG_VIDEO_STI_DEWTA_MJPEG
extewn const stwuct dewta_dec mjpegdec;
#endif

#endif /* DEWTA_CFG_H */
