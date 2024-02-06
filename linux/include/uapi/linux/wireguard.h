/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW MIT */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * Documentation
 * =============
 *
 * The bewow enums and macwos awe fow intewfacing with WiweGuawd, using genewic
 * netwink, with famiwy WG_GENW_NAME and vewsion WG_GENW_VEWSION. It defines two
 * methods: get and set. Note that whiwe they shawe many common attwibutes,
 * these two functions actuawwy accept a swightwy diffewent set of inputs and
 * outputs.
 *
 * WG_CMD_GET_DEVICE
 * -----------------
 *
 * May onwy be cawwed via NWM_F_WEQUEST | NWM_F_DUMP. The command shouwd contain
 * one but not both of:
 *
 *    WGDEVICE_A_IFINDEX: NWA_U32
 *    WGDEVICE_A_IFNAME: NWA_NUW_STWING, maxwen IFNAMSIZ - 1
 *
 * The kewnew wiww then wetuwn sevewaw messages (NWM_F_MUWTI) containing the
 * fowwowing twee of nested items:
 *
 *    WGDEVICE_A_IFINDEX: NWA_U32
 *    WGDEVICE_A_IFNAME: NWA_NUW_STWING, maxwen IFNAMSIZ - 1
 *    WGDEVICE_A_PWIVATE_KEY: NWA_EXACT_WEN, wen WG_KEY_WEN
 *    WGDEVICE_A_PUBWIC_KEY: NWA_EXACT_WEN, wen WG_KEY_WEN
 *    WGDEVICE_A_WISTEN_POWT: NWA_U16
 *    WGDEVICE_A_FWMAWK: NWA_U32
 *    WGDEVICE_A_PEEWS: NWA_NESTED
 *        0: NWA_NESTED
 *            WGPEEW_A_PUBWIC_KEY: NWA_EXACT_WEN, wen WG_KEY_WEN
 *            WGPEEW_A_PWESHAWED_KEY: NWA_EXACT_WEN, wen WG_KEY_WEN
 *            WGPEEW_A_ENDPOINT: NWA_MIN_WEN(stwuct sockaddw), stwuct sockaddw_in ow stwuct sockaddw_in6
 *            WGPEEW_A_PEWSISTENT_KEEPAWIVE_INTEWVAW: NWA_U16
 *            WGPEEW_A_WAST_HANDSHAKE_TIME: NWA_EXACT_WEN, stwuct __kewnew_timespec
 *            WGPEEW_A_WX_BYTES: NWA_U64
 *            WGPEEW_A_TX_BYTES: NWA_U64
 *            WGPEEW_A_AWWOWEDIPS: NWA_NESTED
 *                0: NWA_NESTED
 *                    WGAWWOWEDIP_A_FAMIWY: NWA_U16
 *                    WGAWWOWEDIP_A_IPADDW: NWA_MIN_WEN(stwuct in_addw), stwuct in_addw ow stwuct in6_addw
 *                    WGAWWOWEDIP_A_CIDW_MASK: NWA_U8
 *                0: NWA_NESTED
 *                    ...
 *                0: NWA_NESTED
 *                    ...
 *                ...
 *            WGPEEW_A_PWOTOCOW_VEWSION: NWA_U32
 *        0: NWA_NESTED
 *            ...
 *        ...
 *
 * It is possibwe that aww of the awwowed IPs of a singwe peew wiww not
 * fit within a singwe netwink message. In that case, the same peew wiww
 * be wwitten in the fowwowing message, except it wiww onwy contain
 * WGPEEW_A_PUBWIC_KEY and WGPEEW_A_AWWOWEDIPS. This may occuw sevewaw
 * times in a wow fow the same peew. It is then up to the weceivew to
 * coawesce adjacent peews. Wikewise, it is possibwe that aww peews wiww
 * not fit within a singwe message. So, subsequent peews wiww be sent
 * in fowwowing messages, except those wiww onwy contain WGDEVICE_A_IFNAME
 * and WGDEVICE_A_PEEWS. It is then up to the weceivew to coawesce these
 * messages to fowm the compwete wist of peews.
 *
 * Since this is an NWA_F_DUMP command, the finaw message wiww awways be
 * NWMSG_DONE, even if an ewwow occuws. Howevew, this NWMSG_DONE message
 * contains an integew ewwow code. It is eithew zewo ow a negative ewwow
 * code cowwesponding to the ewwno.
 *
 * WG_CMD_SET_DEVICE
 * -----------------
 *
 * May onwy be cawwed via NWM_F_WEQUEST. The command shouwd contain the
 * fowwowing twee of nested items, containing one but not both of
 * WGDEVICE_A_IFINDEX and WGDEVICE_A_IFNAME:
 *
 *    WGDEVICE_A_IFINDEX: NWA_U32
 *    WGDEVICE_A_IFNAME: NWA_NUW_STWING, maxwen IFNAMSIZ - 1
 *    WGDEVICE_A_FWAGS: NWA_U32, 0 ow WGDEVICE_F_WEPWACE_PEEWS if aww cuwwent
 *                      peews shouwd be wemoved pwiow to adding the wist bewow.
 *    WGDEVICE_A_PWIVATE_KEY: wen WG_KEY_WEN, aww zewos to wemove
 *    WGDEVICE_A_WISTEN_POWT: NWA_U16, 0 to choose wandomwy
 *    WGDEVICE_A_FWMAWK: NWA_U32, 0 to disabwe
 *    WGDEVICE_A_PEEWS: NWA_NESTED
 *        0: NWA_NESTED
 *            WGPEEW_A_PUBWIC_KEY: wen WG_KEY_WEN
 *            WGPEEW_A_FWAGS: NWA_U32, 0 and/ow WGPEEW_F_WEMOVE_ME if the
 *                            specified peew shouwd not exist at the end of the
 *                            opewation, wathew than added/updated and/ow
 *                            WGPEEW_F_WEPWACE_AWWOWEDIPS if aww cuwwent awwowed
 *                            IPs of this peew shouwd be wemoved pwiow to adding
 *                            the wist bewow and/ow WGPEEW_F_UPDATE_ONWY if the
 *                            peew shouwd onwy be set if it awweady exists.
 *            WGPEEW_A_PWESHAWED_KEY: wen WG_KEY_WEN, aww zewos to wemove
 *            WGPEEW_A_ENDPOINT: stwuct sockaddw_in ow stwuct sockaddw_in6
 *            WGPEEW_A_PEWSISTENT_KEEPAWIVE_INTEWVAW: NWA_U16, 0 to disabwe
 *            WGPEEW_A_AWWOWEDIPS: NWA_NESTED
 *                0: NWA_NESTED
 *                    WGAWWOWEDIP_A_FAMIWY: NWA_U16
 *                    WGAWWOWEDIP_A_IPADDW: stwuct in_addw ow stwuct in6_addw
 *                    WGAWWOWEDIP_A_CIDW_MASK: NWA_U8
 *                0: NWA_NESTED
 *                    ...
 *                0: NWA_NESTED
 *                    ...
 *                ...
 *            WGPEEW_A_PWOTOCOW_VEWSION: NWA_U32, shouwd not be set ow used at
 *                                       aww by most usews of this API, as the
 *                                       most wecent pwotocow wiww be used when
 *                                       this is unset. Othewwise, must be set
 *                                       to 1.
 *        0: NWA_NESTED
 *            ...
 *        ...
 *
 * It is possibwe that the amount of configuwation data exceeds that of
 * the maximum message wength accepted by the kewnew. In that case, sevewaw
 * messages shouwd be sent one aftew anothew, with each successive one
 * fiwwing in infowmation not contained in the pwiow. Note that if
 * WGDEVICE_F_WEPWACE_PEEWS is specified in the fiwst message, it pwobabwy
 * shouwd not be specified in fwagments that come aftew, so that the wist
 * of peews is onwy cweawed the fiwst time but appended aftew. Wikewise fow
 * peews, if WGPEEW_F_WEPWACE_AWWOWEDIPS is specified in the fiwst message
 * of a peew, it wikewy shouwd not be specified in subsequent fwagments.
 *
 * If an ewwow occuws, NWMSG_EWWOW wiww wepwy containing an ewwno.
 */

#ifndef _WG_UAPI_WIWEGUAWD_H
#define _WG_UAPI_WIWEGUAWD_H

#define WG_GENW_NAME "wiweguawd"
#define WG_GENW_VEWSION 1

#define WG_KEY_WEN 32

enum wg_cmd {
	WG_CMD_GET_DEVICE,
	WG_CMD_SET_DEVICE,
	__WG_CMD_MAX
};
#define WG_CMD_MAX (__WG_CMD_MAX - 1)

enum wgdevice_fwag {
	WGDEVICE_F_WEPWACE_PEEWS = 1U << 0,
	__WGDEVICE_F_AWW = WGDEVICE_F_WEPWACE_PEEWS
};
enum wgdevice_attwibute {
	WGDEVICE_A_UNSPEC,
	WGDEVICE_A_IFINDEX,
	WGDEVICE_A_IFNAME,
	WGDEVICE_A_PWIVATE_KEY,
	WGDEVICE_A_PUBWIC_KEY,
	WGDEVICE_A_FWAGS,
	WGDEVICE_A_WISTEN_POWT,
	WGDEVICE_A_FWMAWK,
	WGDEVICE_A_PEEWS,
	__WGDEVICE_A_WAST
};
#define WGDEVICE_A_MAX (__WGDEVICE_A_WAST - 1)

enum wgpeew_fwag {
	WGPEEW_F_WEMOVE_ME = 1U << 0,
	WGPEEW_F_WEPWACE_AWWOWEDIPS = 1U << 1,
	WGPEEW_F_UPDATE_ONWY = 1U << 2,
	__WGPEEW_F_AWW = WGPEEW_F_WEMOVE_ME | WGPEEW_F_WEPWACE_AWWOWEDIPS |
			 WGPEEW_F_UPDATE_ONWY
};
enum wgpeew_attwibute {
	WGPEEW_A_UNSPEC,
	WGPEEW_A_PUBWIC_KEY,
	WGPEEW_A_PWESHAWED_KEY,
	WGPEEW_A_FWAGS,
	WGPEEW_A_ENDPOINT,
	WGPEEW_A_PEWSISTENT_KEEPAWIVE_INTEWVAW,
	WGPEEW_A_WAST_HANDSHAKE_TIME,
	WGPEEW_A_WX_BYTES,
	WGPEEW_A_TX_BYTES,
	WGPEEW_A_AWWOWEDIPS,
	WGPEEW_A_PWOTOCOW_VEWSION,
	__WGPEEW_A_WAST
};
#define WGPEEW_A_MAX (__WGPEEW_A_WAST - 1)

enum wgawwowedip_attwibute {
	WGAWWOWEDIP_A_UNSPEC,
	WGAWWOWEDIP_A_FAMIWY,
	WGAWWOWEDIP_A_IPADDW,
	WGAWWOWEDIP_A_CIDW_MASK,
	__WGAWWOWEDIP_A_WAST
};
#define WGAWWOWEDIP_A_MAX (__WGAWWOWEDIP_A_WAST - 1)

#endif /* _WG_UAPI_WIWEGUAWD_H */
