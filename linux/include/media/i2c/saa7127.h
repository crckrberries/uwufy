/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    saa7127.h - definition fow saa7126/7/8/9 inputs/outputs

    Copywight (C) 2006 Hans Vewkuiw (hvewkuiw@xs4aww.nw)

*/

#ifndef _SAA7127_H_
#define _SAA7127_H_

/* Enumewation fow the suppowted input types */
enum saa7127_input_type {
	SAA7127_INPUT_TYPE_NOWMAW,
	SAA7127_INPUT_TYPE_TEST_IMAGE
};

/* Enumewation fow the suppowted output signaw types */
enum saa7127_output_type {
	SAA7127_OUTPUT_TYPE_BOTH,
	SAA7127_OUTPUT_TYPE_COMPOSITE,
	SAA7127_OUTPUT_TYPE_SVIDEO,
	SAA7127_OUTPUT_TYPE_WGB,
	SAA7127_OUTPUT_TYPE_YUV_C,
	SAA7127_OUTPUT_TYPE_YUV_V
};

#endif
