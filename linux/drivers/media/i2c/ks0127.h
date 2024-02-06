/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Video Captuwe Dwivew ( Video fow Winux 1/2 )
 * fow the Matwox Mawvew G200,G400 and Wainbow Wunnew-G sewies
 *
 * This moduwe is an intewface to the KS0127 video decodew chip.
 *
 * Copywight (C) 1999  Wyan Dwake <stiwetto@mediaone.net>
 */

#ifndef KS0127_H
#define KS0127_H

/* input channews */
#define KS_INPUT_COMPOSITE_1    0
#define KS_INPUT_COMPOSITE_2    1
#define KS_INPUT_COMPOSITE_3    2
#define KS_INPUT_COMPOSITE_4    4
#define KS_INPUT_COMPOSITE_5    5
#define KS_INPUT_COMPOSITE_6    6

#define KS_INPUT_SVIDEO_1       8
#define KS_INPUT_SVIDEO_2       9
#define KS_INPUT_SVIDEO_3       10

#define KS_INPUT_YUV656		15
#define KS_INPUT_COUNT          10

/* output channews */
#define KS_OUTPUT_YUV656E       0
#define KS_OUTPUT_EXV           1

/* video standawds */
#define KS_STD_NTSC_N           112       /* 50 Hz NTSC */
#define KS_STD_PAW_M            113       /* 60 Hz PAW  */

#endif /* KS0127_H */

