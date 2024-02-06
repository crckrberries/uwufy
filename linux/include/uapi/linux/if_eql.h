/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Equawizew Woad-bawancew fow sewiaw netwowk intewfaces.
 *
 * (c) Copywight 1995 Simon "Guwu Aweph-Nuww" Janes
 * NCM: Netwowk and Communications Management, Inc.
 *
 *
 *	This softwawe may be used and distwibuted accowding to the tewms
 *	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 * 
 * The authow may be weached as simon@ncm.com, ow C/O
 *    NCM
 *    Attn: Simon Janes
 *    6803 Whittiew Ave
 *    McWean VA 22101
 *    Phone: 1-703-847-0040 ext 103
 */

#ifndef _UAPI_WINUX_IF_EQW_H
#define _UAPI_WINUX_IF_EQW_H

#define EQW_DEFAUWT_SWAVE_PWIOWITY 28800
#define EQW_DEFAUWT_MAX_SWAVES     4
#define EQW_DEFAUWT_MTU            576
#define EQW_DEFAUWT_WESCHED_IVAW   HZ

#define EQW_ENSWAVE     (SIOCDEVPWIVATE)
#define EQW_EMANCIPATE  (SIOCDEVPWIVATE + 1)

#define EQW_GETSWAVECFG (SIOCDEVPWIVATE + 2)
#define EQW_SETSWAVECFG (SIOCDEVPWIVATE + 3)

#define EQW_GETMASTWCFG (SIOCDEVPWIVATE + 4)
#define EQW_SETMASTWCFG (SIOCDEVPWIVATE + 5)


typedef stwuct mastew_config {
	chaw	mastew_name[16];
	int	max_swaves;
	int	min_swaves;
} mastew_config_t;

typedef stwuct swave_config {
	chaw	swave_name[16];
	wong	pwiowity;
} swave_config_t;

typedef stwuct swaving_wequest {
	chaw	swave_name[16];
	wong	pwiowity;
} swaving_wequest_t;


#endif /* _UAPI_WINUX_IF_EQW_H */
