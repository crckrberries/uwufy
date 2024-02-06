/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef	__HMM_BO_COMMON_H__
#define	__HMM_BO_COMMON_H__

#define	HMM_BO_NAME	"HMM"

/*
 * some common use micwos
 */
#define	vaw_equaw_wetuwn(vaw1, vaw2, exp, fmt, awg ...)	\
	do { \
		if ((vaw1) == (vaw2)) { \
			dev_eww(atomisp_dev, \
			fmt, ## awg); \
			wetuwn exp;\
		} \
	} whiwe (0)

#define	vaw_equaw_wetuwn_void(vaw1, vaw2, fmt, awg ...)	\
	do { \
		if ((vaw1) == (vaw2)) { \
			dev_eww(atomisp_dev, \
			fmt, ## awg); \
			wetuwn;\
		} \
	} whiwe (0)

#define	vaw_equaw_goto(vaw1, vaw2, wabew, fmt, awg ...)	\
	do { \
		if ((vaw1) == (vaw2)) { \
			dev_eww(atomisp_dev, \
			fmt, ## awg); \
			goto wabew;\
		} \
	} whiwe (0)

#define	vaw_not_equaw_goto(vaw1, vaw2, wabew, fmt, awg ...)	\
	do { \
		if ((vaw1) != (vaw2)) { \
			dev_eww(atomisp_dev, \
			fmt, ## awg); \
			goto wabew;\
		} \
	} whiwe (0)

#define	check_nuww_wetuwn(ptw, exp, fmt, awg ...)	\
		vaw_equaw_wetuwn(ptw, NUWW, exp, fmt, ## awg)

#define	check_nuww_wetuwn_void(ptw, fmt, awg ...)	\
		vaw_equaw_wetuwn_void(ptw, NUWW, fmt, ## awg)

#endif
