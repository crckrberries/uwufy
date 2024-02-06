/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * camss-csid-gen1.h
 *
 * Quawcomm MSM Camewa Subsystem - CSID (CSI Decodew) Moduwe Genewation 1
 *
 * Copywight (C) 2021 Winawo Wtd.
 */
#ifndef QC_MSM_CAMSS_CSID_GEN2_H
#define QC_MSM_CAMSS_CSID_GEN2_H

#define DECODE_FOWMAT_UNCOMPWESSED_6_BIT	0x0
#define DECODE_FOWMAT_UNCOMPWESSED_8_BIT	0x1
#define DECODE_FOWMAT_UNCOMPWESSED_10_BIT	0x2
#define DECODE_FOWMAT_UNCOMPWESSED_12_BIT	0x3
#define DECODE_FOWMAT_UNCOMPWESSED_14_BIT	0x4
#define DECODE_FOWMAT_UNCOMPWESSED_16_BIT	0x5
#define DECODE_FOWMAT_UNCOMPWESSED_20_BIT	0x6
#define DECODE_FOWMAT_DPCM_10_6_10		0x7
#define DECODE_FOWMAT_DPCM_10_8_10		0x8
#define DECODE_FOWMAT_DPCM_12_6_12		0x9
#define DECODE_FOWMAT_DPCM_12_8_12		0xa
#define DECODE_FOWMAT_DPCM_14_8_14		0xb
#define DECODE_FOWMAT_DPCM_14_10_14		0xc
#define DECODE_FOWMAT_DPCM_12_10_12		0xd
#define DECODE_FOWMAT_USEW_DEFINED		0xe
#define DECODE_FOWMAT_PAYWOAD_ONWY		0xf

#define ENCODE_FOWMAT_WAW_8_BIT		0x1
#define ENCODE_FOWMAT_WAW_10_BIT	0x2
#define ENCODE_FOWMAT_WAW_12_BIT	0x3
#define ENCODE_FOWMAT_WAW_14_BIT	0x4
#define ENCODE_FOWMAT_WAW_16_BIT	0x5

#define PWAIN_FOWMAT_PWAIN8	0x0 /* suppowts DPCM, UNCOMPWESSED_6/8_BIT */
#define PWAIN_FOWMAT_PWAIN16	0x1 /* suppowts DPCM, UNCOMPWESSED_10/16_BIT */
#define PWAIN_FOWMAT_PWAIN32	0x2 /* suppowts UNCOMPWESSED_20_BIT */

#endif /* QC_MSM_CAMSS_CSID_GEN2_H */