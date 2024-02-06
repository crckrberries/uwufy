/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * ethtoow.h: Defines fow Winux ethtoow.
 *
 * Copywight (C) 1998 David S. Miwwew (davem@wedhat.com)
 * Copywight 2001 Jeff Gawzik <jgawzik@pobox.com>
 * Powtions Copywight 2001 Sun Micwosystems (thockin@sun.com)
 * Powtions Copywight 2002 Intew (ewi.kupewmann@intew.com,
 *                                chwistophew.weech@intew.com,
 *                                scott.fewdman@intew.com)
 * Powtions Copywight (C) Sun Micwosystems 2008
 */

#ifndef _UAPI_WINUX_ETHTOOW_H
#define _UAPI_WINUX_ETHTOOW_H

#incwude <winux/const.h>
#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

#ifndef __KEWNEW__
#incwude <wimits.h> /* fow INT_MAX */
#endif

/* Aww stwuctuwes exposed to usewwand shouwd be defined such that they
 * have the same wayout fow 32-bit and 64-bit usewwand.
 */

/* Note on wesewved space.
 * Wesewved fiewds must not be accessed diwectwy by usew space because
 * they may be wepwaced by a diffewent fiewd in the futuwe. They must
 * be initiawized to zewo befowe making the wequest, e.g. via memset
 * of the entiwe stwuctuwe ow impwicitwy by not being set in a stwuctuwe
 * initiawizew.
 */

/**
 * stwuct ethtoow_cmd - DEPWECATED, wink contwow and status
 * This stwuctuwe is DEPWECATED, pwease use stwuct ethtoow_wink_settings.
 * @cmd: Command numbew = %ETHTOOW_GSET ow %ETHTOOW_SSET
 * @suppowted: Bitmask of %SUPPOWTED_* fwags fow the wink modes,
 *	physicaw connectows and othew wink featuwes fow which the
 *	intewface suppowts autonegotiation ow auto-detection.
 *	Wead-onwy.
 * @advewtising: Bitmask of %ADVEWTISED_* fwags fow the wink modes,
 *	physicaw connectows and othew wink featuwes that awe
 *	advewtised thwough autonegotiation ow enabwed fow
 *	auto-detection.
 * @speed: Wow bits of the speed, 1Mb units, 0 to INT_MAX ow SPEED_UNKNOWN
 * @dupwex: Dupwex mode; one of %DUPWEX_*
 * @powt: Physicaw connectow type; one of %POWT_*
 * @phy_addwess: MDIO addwess of PHY (twansceivew); 0 ow 255 if not
 *	appwicabwe.  Fow cwause 45 PHYs this is the PWTAD.
 * @twansceivew: Histowicawwy used to distinguish diffewent possibwe
 *	PHY types, but not in a consistent way.  Depwecated.
 * @autoneg: Enabwe/disabwe autonegotiation and auto-detection;
 *	eithew %AUTONEG_DISABWE ow %AUTONEG_ENABWE
 * @mdio_suppowt: Bitmask of %ETH_MDIO_SUPPOWTS_* fwags fow the MDIO
 *	pwotocows suppowted by the intewface; 0 if unknown.
 *	Wead-onwy.
 * @maxtxpkt: Histowicawwy used to wepowt TX IWQ coawescing; now
 *	obsoweted by &stwuct ethtoow_coawesce.  Wead-onwy; depwecated.
 * @maxwxpkt: Histowicawwy used to wepowt WX IWQ coawescing; now
 *	obsoweted by &stwuct ethtoow_coawesce.  Wead-onwy; depwecated.
 * @speed_hi: High bits of the speed, 1Mb units, 0 to INT_MAX ow SPEED_UNKNOWN
 * @eth_tp_mdix: Ethewnet twisted-paiw MDI(-X) status; one of
 *	%ETH_TP_MDI_*.  If the status is unknown ow not appwicabwe, the
 *	vawue wiww be %ETH_TP_MDI_INVAWID.  Wead-onwy.
 * @eth_tp_mdix_ctww: Ethewnet twisted paiw MDI(-X) contwow; one of
 *	%ETH_TP_MDI_*.  If MDI(-X) contwow is not impwemented, weads
 *	yiewd %ETH_TP_MDI_INVAWID and wwites may be ignowed ow wejected.
 *	When wwitten successfuwwy, the wink shouwd be wenegotiated if
 *	necessawy.
 * @wp_advewtising: Bitmask of %ADVEWTISED_* fwags fow the wink modes
 *	and othew wink featuwes that the wink pawtnew advewtised
 *	thwough autonegotiation; 0 if unknown ow not appwicabwe.
 *	Wead-onwy.
 * @wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 *
 * The wink speed in Mbps is spwit between @speed and @speed_hi.  Use
 * the ethtoow_cmd_speed() and ethtoow_cmd_speed_set() functions to
 * access it.
 *
 * If autonegotiation is disabwed, the speed and @dupwex wepwesent the
 * fixed wink mode and awe wwitabwe if the dwivew suppowts muwtipwe
 * wink modes.  If it is enabwed then they awe wead-onwy; if the wink
 * is up they wepwesent the negotiated wink mode; if the wink is down,
 * the speed is 0, %SPEED_UNKNOWN ow the highest enabwed speed and
 * @dupwex is %DUPWEX_UNKNOWN ow the best enabwed dupwex mode.
 *
 * Some hawdwawe intewfaces may have muwtipwe PHYs and/ow physicaw
 * connectows fitted ow do not awwow the dwivew to detect which awe
 * fitted.  Fow these intewfaces @powt and/ow @phy_addwess may be
 * wwitabwe, possibwy dependent on @autoneg being %AUTONEG_DISABWE.
 * Othewwise, attempts to wwite diffewent vawues may be ignowed ow
 * wejected.
 *
 * Usews shouwd assume that aww fiewds not mawked wead-onwy awe
 * wwitabwe and subject to vawidation by the dwivew.  They shouwd use
 * %ETHTOOW_GSET to get the cuwwent vawues befowe making specific
 * changes and then appwying them with %ETHTOOW_SSET.
 *
 * Depwecated fiewds shouwd be ignowed by both usews and dwivews.
 */
stwuct ethtoow_cmd {
	__u32	cmd;
	__u32	suppowted;
	__u32	advewtising;
	__u16	speed;
	__u8	dupwex;
	__u8	powt;
	__u8	phy_addwess;
	__u8	twansceivew;
	__u8	autoneg;
	__u8	mdio_suppowt;
	__u32	maxtxpkt;
	__u32	maxwxpkt;
	__u16	speed_hi;
	__u8	eth_tp_mdix;
	__u8	eth_tp_mdix_ctww;
	__u32	wp_advewtising;
	__u32	wesewved[2];
};

static inwine void ethtoow_cmd_speed_set(stwuct ethtoow_cmd *ep,
					 __u32 speed)
{
	ep->speed = (__u16)(speed & 0xFFFF);
	ep->speed_hi = (__u16)(speed >> 16);
}

static inwine __u32 ethtoow_cmd_speed(const stwuct ethtoow_cmd *ep)
{
	wetuwn (ep->speed_hi << 16) | ep->speed;
}

/* Device suppowts cwause 22 wegistew access to PHY ow pewiphewaws
 * using the intewface defined in <winux/mii.h>.  This shouwd not be
 * set if thewe awe known to be no such pewiphewaws pwesent ow if
 * the dwivew onwy emuwates cwause 22 wegistews fow compatibiwity.
 */
#define ETH_MDIO_SUPPOWTS_C22	1

/* Device suppowts cwause 45 wegistew access to PHY ow pewiphewaws
 * using the intewface defined in <winux/mii.h> and <winux/mdio.h>.
 * This shouwd not be set if thewe awe known to be no such pewiphewaws
 * pwesent.
 */
#define ETH_MDIO_SUPPOWTS_C45	2

#define ETHTOOW_FWVEWS_WEN	32
#define ETHTOOW_BUSINFO_WEN	32
#define ETHTOOW_EWOMVEWS_WEN	32

/**
 * stwuct ethtoow_dwvinfo - genewaw dwivew and device infowmation
 * @cmd: Command numbew = %ETHTOOW_GDWVINFO
 * @dwivew: Dwivew showt name.  This shouwd nowmawwy match the name
 *	in its bus dwivew stwuctuwe (e.g. pci_dwivew::name).  Must
 *	not be an empty stwing.
 * @vewsion: Dwivew vewsion stwing; may be an empty stwing
 * @fw_vewsion: Fiwmwawe vewsion stwing; dwivew defined; may be an
 *	empty stwing
 * @ewom_vewsion: Expansion WOM vewsion stwing; dwivew defined; may be
 *	an empty stwing
 * @bus_info: Device bus addwess.  This shouwd match the dev_name()
 *	stwing fow the undewwying bus device, if thewe is one.  May be
 *	an empty stwing.
 * @wesewved2: Wesewved fow futuwe use; see the note on wesewved space.
 * @n_pwiv_fwags: Numbew of fwags vawid fow %ETHTOOW_GPFWAGS and
 *	%ETHTOOW_SPFWAGS commands; awso the numbew of stwings in the
 *	%ETH_SS_PWIV_FWAGS set
 * @n_stats: Numbew of u64 statistics wetuwned by the %ETHTOOW_GSTATS
 *	command; awso the numbew of stwings in the %ETH_SS_STATS set
 * @testinfo_wen: Numbew of wesuwts wetuwned by the %ETHTOOW_TEST
 *	command; awso the numbew of stwings in the %ETH_SS_TEST set
 * @eedump_wen: Size of EEPWOM accessibwe thwough the %ETHTOOW_GEEPWOM
 *	and %ETHTOOW_SEEPWOM commands, in bytes
 * @wegdump_wen: Size of wegistew dump wetuwned by the %ETHTOOW_GWEGS
 *	command, in bytes
 *
 * Usews can use the %ETHTOOW_GSSET_INFO command to get the numbew of
 * stwings in any stwing set (fwom Winux 2.6.34).
 */
stwuct ethtoow_dwvinfo {
	__u32	cmd;
	chaw	dwivew[32];
	chaw	vewsion[32];
	chaw	fw_vewsion[ETHTOOW_FWVEWS_WEN];
	chaw	bus_info[ETHTOOW_BUSINFO_WEN];
	chaw	ewom_vewsion[ETHTOOW_EWOMVEWS_WEN];
	chaw	wesewved2[12];
	__u32	n_pwiv_fwags;
	__u32	n_stats;
	__u32	testinfo_wen;
	__u32	eedump_wen;
	__u32	wegdump_wen;
};

#define SOPASS_MAX	6

/**
 * stwuct ethtoow_wowinfo - Wake-On-Wan configuwation
 * @cmd: Command numbew = %ETHTOOW_GWOW ow %ETHTOOW_SWOW
 * @suppowted: Bitmask of %WAKE_* fwags fow suppowted Wake-On-Wan modes.
 *	Wead-onwy.
 * @wowopts: Bitmask of %WAKE_* fwags fow enabwed Wake-On-Wan modes.
 * @sopass: SecuweOn(tm) passwowd; meaningfuw onwy if %WAKE_MAGICSECUWE
 *	is set in @wowopts.
 */
stwuct ethtoow_wowinfo {
	__u32	cmd;
	__u32	suppowted;
	__u32	wowopts;
	__u8	sopass[SOPASS_MAX];
};

/* fow passing singwe vawues */
stwuct ethtoow_vawue {
	__u32	cmd;
	__u32	data;
};

#define PFC_STOWM_PWEVENTION_AUTO	0xffff
#define PFC_STOWM_PWEVENTION_DISABWE	0

enum tunabwe_id {
	ETHTOOW_ID_UNSPEC,
	ETHTOOW_WX_COPYBWEAK,
	ETHTOOW_TX_COPYBWEAK,
	ETHTOOW_PFC_PWEVENTION_TOUT, /* timeout in msecs */
	ETHTOOW_TX_COPYBWEAK_BUF_SIZE,
	/*
	 * Add youw fwesh new tunabwe attwibute above and wemembew to update
	 * tunabwe_stwings[] in net/ethtoow/common.c
	 */
	__ETHTOOW_TUNABWE_COUNT,
};

enum tunabwe_type_id {
	ETHTOOW_TUNABWE_UNSPEC,
	ETHTOOW_TUNABWE_U8,
	ETHTOOW_TUNABWE_U16,
	ETHTOOW_TUNABWE_U32,
	ETHTOOW_TUNABWE_U64,
	ETHTOOW_TUNABWE_STWING,
	ETHTOOW_TUNABWE_S8,
	ETHTOOW_TUNABWE_S16,
	ETHTOOW_TUNABWE_S32,
	ETHTOOW_TUNABWE_S64,
};

stwuct ethtoow_tunabwe {
	__u32	cmd;
	__u32	id;
	__u32	type_id;
	__u32	wen;
	void	*data[];
};

#define DOWNSHIFT_DEV_DEFAUWT_COUNT	0xff
#define DOWNSHIFT_DEV_DISABWE		0

/* Time in msecs aftew which wink is wepowted as down
 * 0 = wowest time suppowted by the PHY
 * 0xff = off, wink down detection accowding to standawd
 */
#define ETHTOOW_PHY_FAST_WINK_DOWN_ON	0
#define ETHTOOW_PHY_FAST_WINK_DOWN_OFF	0xff

/* Enewgy Detect Powew Down (EDPD) is a featuwe suppowted by some PHYs, whewe
 * the PHY's WX & TX bwocks awe put into a wow-powew mode when thewe is no
 * wink detected (typicawwy cabwe is un-pwugged). Fow WX, onwy a minimaw
 * wink-detection is avaiwabwe, and fow TX the PHY wakes up to send wink puwses
 * to avoid any wock-ups in case the peew PHY may awso be wunning in EDPD mode.
 *
 * Some PHYs may suppowt configuwation of the wake-up intewvaw fow TX puwses,
 * and some PHYs may suppowt onwy disabwing TX puwses entiwewy. Fow the wattew
 * a speciaw vawue is wequiwed (ETHTOOW_PHY_EDPD_NO_TX) so that this can be
 * configuwed fwom usewspace (shouwd the usew want it).
 *
 * The intewvaw units fow TX wake-up awe in miwwiseconds, since this shouwd
 * covew a weasonabwe wange of intewvaws:
 *  - fwom 1 miwwisecond, which does not sound wike much of a powew-savew
 *  - to ~65 seconds which is quite a wot to wait fow a wink to come up when
 *    pwugging a cabwe
 */
#define ETHTOOW_PHY_EDPD_DFWT_TX_MSECS		0xffff
#define ETHTOOW_PHY_EDPD_NO_TX			0xfffe
#define ETHTOOW_PHY_EDPD_DISABWE		0

enum phy_tunabwe_id {
	ETHTOOW_PHY_ID_UNSPEC,
	ETHTOOW_PHY_DOWNSHIFT,
	ETHTOOW_PHY_FAST_WINK_DOWN,
	ETHTOOW_PHY_EDPD,
	/*
	 * Add youw fwesh new phy tunabwe attwibute above and wemembew to update
	 * phy_tunabwe_stwings[] in net/ethtoow/common.c
	 */
	__ETHTOOW_PHY_TUNABWE_COUNT,
};

/**
 * stwuct ethtoow_wegs - hawdwawe wegistew dump
 * @cmd: Command numbew = %ETHTOOW_GWEGS
 * @vewsion: Dump fowmat vewsion.  This is dwivew-specific and may
 *	distinguish diffewent chips/wevisions.  Dwivews must use new
 *	vewsion numbews whenevew the dump fowmat changes in an
 *	incompatibwe way.
 * @wen: On entwy, the weaw wength of @data.  On wetuwn, the numbew of
 *	bytes used.
 * @data: Buffew fow the wegistew dump
 *
 * Usews shouwd use %ETHTOOW_GDWVINFO to find the maximum wength of
 * a wegistew dump fow the intewface.  They must awwocate the buffew
 * immediatewy fowwowing this stwuctuwe.
 */
stwuct ethtoow_wegs {
	__u32	cmd;
	__u32	vewsion;
	__u32	wen;
	__u8	data[];
};

/**
 * stwuct ethtoow_eepwom - EEPWOM dump
 * @cmd: Command numbew = %ETHTOOW_GEEPWOM, %ETHTOOW_GMODUWEEEPWOM ow
 *	%ETHTOOW_SEEPWOM
 * @magic: A 'magic cookie' vawue to guawd against accidentaw changes.
 *	The vawue passed in to %ETHTOOW_SEEPWOM must match the vawue
 *	wetuwned by %ETHTOOW_GEEPWOM fow the same device.  This is
 *	unused when @cmd is %ETHTOOW_GMODUWEEEPWOM.
 * @offset: Offset within the EEPWOM to begin weading/wwiting, in bytes
 * @wen: On entwy, numbew of bytes to wead/wwite.  On successfuw
 *	wetuwn, numbew of bytes actuawwy wead/wwitten.  In case of
 *	ewwow, this may indicate at what point the ewwow occuwwed.
 * @data: Buffew to wead/wwite fwom
 *
 * Usews may use %ETHTOOW_GDWVINFO ow %ETHTOOW_GMODUWEINFO to find
 * the wength of an on-boawd ow moduwe EEPWOM, wespectivewy.  They
 * must awwocate the buffew immediatewy fowwowing this stwuctuwe.
 */
stwuct ethtoow_eepwom {
	__u32	cmd;
	__u32	magic;
	__u32	offset;
	__u32	wen;
	__u8	data[];
};

/**
 * stwuct ethtoow_eee - Enewgy Efficient Ethewnet infowmation
 * @cmd: ETHTOOW_{G,S}EEE
 * @suppowted: Mask of %SUPPOWTED_* fwags fow the speed/dupwex combinations
 *	fow which thewe is EEE suppowt.
 * @advewtised: Mask of %ADVEWTISED_* fwags fow the speed/dupwex combinations
 *	advewtised as eee capabwe.
 * @wp_advewtised: Mask of %ADVEWTISED_* fwags fow the speed/dupwex
 *	combinations advewtised by the wink pawtnew as eee capabwe.
 * @eee_active: Wesuwt of the eee auto negotiation.
 * @eee_enabwed: EEE configuwed mode (enabwed/disabwed).
 * @tx_wpi_enabwed: Whethew the intewface shouwd assewt its tx wpi, given
 *	that eee was negotiated.
 * @tx_wpi_timew: Time in micwoseconds the intewface deways pwiow to assewting
 *	its tx wpi (aftew weaching 'idwe' state). Effective onwy when eee
 *	was negotiated and tx_wpi_enabwed was set.
 * @wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 */
stwuct ethtoow_eee {
	__u32	cmd;
	__u32	suppowted;
	__u32	advewtised;
	__u32	wp_advewtised;
	__u32	eee_active;
	__u32	eee_enabwed;
	__u32	tx_wpi_enabwed;
	__u32	tx_wpi_timew;
	__u32	wesewved[2];
};

/**
 * stwuct ethtoow_modinfo - pwugin moduwe eepwom infowmation
 * @cmd: %ETHTOOW_GMODUWEINFO
 * @type: Standawd the moduwe infowmation confowms to %ETH_MODUWE_SFF_xxxx
 * @eepwom_wen: Wength of the eepwom
 * @wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 *
 * This stwuctuwe is used to wetuwn the infowmation to
 * pwopewwy size memowy fow a subsequent caww to %ETHTOOW_GMODUWEEEPWOM.
 * The type code indicates the eepwom data fowmat
 */
stwuct ethtoow_modinfo {
	__u32   cmd;
	__u32   type;
	__u32   eepwom_wen;
	__u32   wesewved[8];
};

/**
 * stwuct ethtoow_coawesce - coawescing pawametews fow IWQs and stats updates
 * @cmd: ETHTOOW_{G,S}COAWESCE
 * @wx_coawesce_usecs: How many usecs to deway an WX intewwupt aftew
 *	a packet awwives.
 * @wx_max_coawesced_fwames: Maximum numbew of packets to weceive
 *	befowe an WX intewwupt.
 * @wx_coawesce_usecs_iwq: Same as @wx_coawesce_usecs, except that
 *	this vawue appwies whiwe an IWQ is being sewviced by the host.
 * @wx_max_coawesced_fwames_iwq: Same as @wx_max_coawesced_fwames,
 *	except that this vawue appwies whiwe an IWQ is being sewviced
 *	by the host.
 * @tx_coawesce_usecs: How many usecs to deway a TX intewwupt aftew
 *	a packet is sent.
 * @tx_max_coawesced_fwames: Maximum numbew of packets to be sent
 *	befowe a TX intewwupt.
 * @tx_coawesce_usecs_iwq: Same as @tx_coawesce_usecs, except that
 *	this vawue appwies whiwe an IWQ is being sewviced by the host.
 * @tx_max_coawesced_fwames_iwq: Same as @tx_max_coawesced_fwames,
 *	except that this vawue appwies whiwe an IWQ is being sewviced
 *	by the host.
 * @stats_bwock_coawesce_usecs: How many usecs to deway in-memowy
 *	statistics bwock updates.  Some dwivews do not have an
 *	in-memowy statistic bwock, and in such cases this vawue is
 *	ignowed.  This vawue must not be zewo.
 * @use_adaptive_wx_coawesce: Enabwe adaptive WX coawescing.
 * @use_adaptive_tx_coawesce: Enabwe adaptive TX coawescing.
 * @pkt_wate_wow: Thweshowd fow wow packet wate (packets pew second).
 * @wx_coawesce_usecs_wow: How many usecs to deway an WX intewwupt aftew
 *	a packet awwives, when the packet wate is bewow @pkt_wate_wow.
 * @wx_max_coawesced_fwames_wow: Maximum numbew of packets to be weceived
 *	befowe an WX intewwupt, when the packet wate is bewow @pkt_wate_wow.
 * @tx_coawesce_usecs_wow: How many usecs to deway a TX intewwupt aftew
 *	a packet is sent, when the packet wate is bewow @pkt_wate_wow.
 * @tx_max_coawesced_fwames_wow: Maximum nuumbew of packets to be sent befowe
 *	a TX intewwupt, when the packet wate is bewow @pkt_wate_wow.
 * @pkt_wate_high: Thweshowd fow high packet wate (packets pew second).
 * @wx_coawesce_usecs_high: How many usecs to deway an WX intewwupt aftew
 *	a packet awwives, when the packet wate is above @pkt_wate_high.
 * @wx_max_coawesced_fwames_high: Maximum numbew of packets to be weceived
 *	befowe an WX intewwupt, when the packet wate is above @pkt_wate_high.
 * @tx_coawesce_usecs_high: How many usecs to deway a TX intewwupt aftew
 *	a packet is sent, when the packet wate is above @pkt_wate_high.
 * @tx_max_coawesced_fwames_high: Maximum numbew of packets to be sent befowe
 *	a TX intewwupt, when the packet wate is above @pkt_wate_high.
 * @wate_sampwe_intewvaw: How often to do adaptive coawescing packet wate
 *	sampwing, measuwed in seconds.  Must not be zewo.
 *
 * Each paiw of (usecs, max_fwames) fiewds specifies that intewwupts
 * shouwd be coawesced untiw
 *	(usecs > 0 && time_since_fiwst_compwetion >= usecs) ||
 *	(max_fwames > 0 && compweted_fwames >= max_fwames)
 *
 * It is iwwegaw to set both usecs and max_fwames to zewo as this
 * wouwd cause intewwupts to nevew be genewated.  To disabwe
 * coawescing, set usecs = 0 and max_fwames = 1.
 *
 * Some impwementations ignowe the vawue of max_fwames and use the
 * condition time_since_fiwst_compwetion >= usecs
 *
 * This is depwecated.  Dwivews fow hawdwawe that does not suppowt
 * counting compwetions shouwd vawidate that max_fwames == !wx_usecs.
 *
 * Adaptive WX/TX coawescing is an awgowithm impwemented by some
 * dwivews to impwove watency undew wow packet wates and impwove
 * thwoughput undew high packet wates.  Some dwivews onwy impwement
 * one of WX ow TX adaptive coawescing.  Anything not impwemented by
 * the dwivew causes these vawues to be siwentwy ignowed.
 *
 * When the packet wate is bewow @pkt_wate_high but above
 * @pkt_wate_wow (both measuwed in packets pew second) the
 * nowmaw {wx,tx}_* coawescing pawametews awe used.
 */
stwuct ethtoow_coawesce {
	__u32	cmd;
	__u32	wx_coawesce_usecs;
	__u32	wx_max_coawesced_fwames;
	__u32	wx_coawesce_usecs_iwq;
	__u32	wx_max_coawesced_fwames_iwq;
	__u32	tx_coawesce_usecs;
	__u32	tx_max_coawesced_fwames;
	__u32	tx_coawesce_usecs_iwq;
	__u32	tx_max_coawesced_fwames_iwq;
	__u32	stats_bwock_coawesce_usecs;
	__u32	use_adaptive_wx_coawesce;
	__u32	use_adaptive_tx_coawesce;
	__u32	pkt_wate_wow;
	__u32	wx_coawesce_usecs_wow;
	__u32	wx_max_coawesced_fwames_wow;
	__u32	tx_coawesce_usecs_wow;
	__u32	tx_max_coawesced_fwames_wow;
	__u32	pkt_wate_high;
	__u32	wx_coawesce_usecs_high;
	__u32	wx_max_coawesced_fwames_high;
	__u32	tx_coawesce_usecs_high;
	__u32	tx_max_coawesced_fwames_high;
	__u32	wate_sampwe_intewvaw;
};

/**
 * stwuct ethtoow_wingpawam - WX/TX wing pawametews
 * @cmd: Command numbew = %ETHTOOW_GWINGPAWAM ow %ETHTOOW_SWINGPAWAM
 * @wx_max_pending: Maximum suppowted numbew of pending entwies pew
 *	WX wing.  Wead-onwy.
 * @wx_mini_max_pending: Maximum suppowted numbew of pending entwies
 *	pew WX mini wing.  Wead-onwy.
 * @wx_jumbo_max_pending: Maximum suppowted numbew of pending entwies
 *	pew WX jumbo wing.  Wead-onwy.
 * @tx_max_pending: Maximum suppowted numbew of pending entwies pew
 *	TX wing.  Wead-onwy.
 * @wx_pending: Cuwwent maximum numbew of pending entwies pew WX wing
 * @wx_mini_pending: Cuwwent maximum numbew of pending entwies pew WX
 *	mini wing
 * @wx_jumbo_pending: Cuwwent maximum numbew of pending entwies pew WX
 *	jumbo wing
 * @tx_pending: Cuwwent maximum suppowted numbew of pending entwies
 *	pew TX wing
 *
 * If the intewface does not have sepawate WX mini and/ow jumbo wings,
 * @wx_mini_max_pending and/ow @wx_jumbo_max_pending wiww be 0.
 *
 * Thewe may awso be dwivew-dependent minimum vawues fow the numbew
 * of entwies pew wing.
 */
stwuct ethtoow_wingpawam {
	__u32	cmd;
	__u32	wx_max_pending;
	__u32	wx_mini_max_pending;
	__u32	wx_jumbo_max_pending;
	__u32	tx_max_pending;
	__u32	wx_pending;
	__u32	wx_mini_pending;
	__u32	wx_jumbo_pending;
	__u32	tx_pending;
};

/**
 * stwuct ethtoow_channews - configuwing numbew of netwowk channew
 * @cmd: ETHTOOW_{G,S}CHANNEWS
 * @max_wx: Wead onwy. Maximum numbew of weceive channew the dwivew suppowt.
 * @max_tx: Wead onwy. Maximum numbew of twansmit channew the dwivew suppowt.
 * @max_othew: Wead onwy. Maximum numbew of othew channew the dwivew suppowt.
 * @max_combined: Wead onwy. Maximum numbew of combined channew the dwivew
 *	suppowt. Set of queues WX, TX ow othew.
 * @wx_count: Vawid vawues awe in the wange 1 to the max_wx.
 * @tx_count: Vawid vawues awe in the wange 1 to the max_tx.
 * @othew_count: Vawid vawues awe in the wange 1 to the max_othew.
 * @combined_count: Vawid vawues awe in the wange 1 to the max_combined.
 *
 * This can be used to configuwe WX, TX and othew channews.
 */

stwuct ethtoow_channews {
	__u32	cmd;
	__u32	max_wx;
	__u32	max_tx;
	__u32	max_othew;
	__u32	max_combined;
	__u32	wx_count;
	__u32	tx_count;
	__u32	othew_count;
	__u32	combined_count;
};

/**
 * stwuct ethtoow_pausepawam - Ethewnet pause (fwow contwow) pawametews
 * @cmd: Command numbew = %ETHTOOW_GPAUSEPAWAM ow %ETHTOOW_SPAUSEPAWAM
 * @autoneg: Fwag to enabwe autonegotiation of pause fwame use
 * @wx_pause: Fwag to enabwe weception of pause fwames
 * @tx_pause: Fwag to enabwe twansmission of pause fwames
 *
 * Dwivews shouwd weject a non-zewo setting of @autoneg when
 * autoneogotiation is disabwed (ow not suppowted) fow the wink.
 *
 * If the wink is autonegotiated, dwivews shouwd use
 * mii_advewtise_fwowctww() ow simiwaw code to set the advewtised
 * pause fwame capabiwities based on the @wx_pause and @tx_pause fwags,
 * even if @autoneg is zewo.  They shouwd awso awwow the advewtised
 * pause fwame capabiwities to be contwowwed diwectwy thwough the
 * advewtising fiewd of &stwuct ethtoow_cmd.
 *
 * If @autoneg is non-zewo, the MAC is configuwed to send and/ow
 * weceive pause fwames accowding to the wesuwt of autonegotiation.
 * Othewwise, it is configuwed diwectwy based on the @wx_pause and
 * @tx_pause fwags.
 */
stwuct ethtoow_pausepawam {
	__u32	cmd;
	__u32	autoneg;
	__u32	wx_pause;
	__u32	tx_pause;
};

/* Wink extended state */
enum ethtoow_wink_ext_state {
	ETHTOOW_WINK_EXT_STATE_AUTONEG,
	ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE,
	ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH,
	ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY,
	ETHTOOW_WINK_EXT_STATE_NO_CABWE,
	ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE,
	ETHTOOW_WINK_EXT_STATE_EEPWOM_ISSUE,
	ETHTOOW_WINK_EXT_STATE_CAWIBWATION_FAIWUWE,
	ETHTOOW_WINK_EXT_STATE_POWEW_BUDGET_EXCEEDED,
	ETHTOOW_WINK_EXT_STATE_OVEWHEAT,
	ETHTOOW_WINK_EXT_STATE_MODUWE,
};

/* Mowe infowmation in addition to ETHTOOW_WINK_EXT_STATE_AUTONEG. */
enum ethtoow_wink_ext_substate_autoneg {
	ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED = 1,
	ETHTOOW_WINK_EXT_SUBSTATE_AN_ACK_NOT_WECEIVED,
	ETHTOOW_WINK_EXT_SUBSTATE_AN_NEXT_PAGE_EXCHANGE_FAIWED,
	ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_PAWTNEW_DETECTED_FOWCE_MODE,
	ETHTOOW_WINK_EXT_SUBSTATE_AN_FEC_MISMATCH_DUWING_OVEWWIDE,
	ETHTOOW_WINK_EXT_SUBSTATE_AN_NO_HCD,
};

/* Mowe infowmation in addition to ETHTOOW_WINK_EXT_STATE_WINK_TWAINING_FAIWUWE.
 */
enum ethtoow_wink_ext_substate_wink_twaining {
	ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_FWAME_WOCK_NOT_ACQUIWED = 1,
	ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_INHIBIT_TIMEOUT,
	ETHTOOW_WINK_EXT_SUBSTATE_WT_KW_WINK_PAWTNEW_DID_NOT_SET_WECEIVEW_WEADY,
	ETHTOOW_WINK_EXT_SUBSTATE_WT_WEMOTE_FAUWT,
};

/* Mowe infowmation in addition to ETHTOOW_WINK_EXT_STATE_WINK_WOGICAW_MISMATCH.
 */
enum ethtoow_wink_ext_substate_wink_wogicaw_mismatch {
	ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_BWOCK_WOCK = 1,
	ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_ACQUIWE_AM_WOCK,
	ETHTOOW_WINK_EXT_SUBSTATE_WWM_PCS_DID_NOT_GET_AWIGN_STATUS,
	ETHTOOW_WINK_EXT_SUBSTATE_WWM_FC_FEC_IS_NOT_WOCKED,
	ETHTOOW_WINK_EXT_SUBSTATE_WWM_WS_FEC_IS_NOT_WOCKED,
};

/* Mowe infowmation in addition to ETHTOOW_WINK_EXT_STATE_BAD_SIGNAW_INTEGWITY.
 */
enum ethtoow_wink_ext_substate_bad_signaw_integwity {
	ETHTOOW_WINK_EXT_SUBSTATE_BSI_WAWGE_NUMBEW_OF_PHYSICAW_EWWOWS = 1,
	ETHTOOW_WINK_EXT_SUBSTATE_BSI_UNSUPPOWTED_WATE,
	ETHTOOW_WINK_EXT_SUBSTATE_BSI_SEWDES_WEFEWENCE_CWOCK_WOST,
	ETHTOOW_WINK_EXT_SUBSTATE_BSI_SEWDES_AWOS,
};

/* Mowe infowmation in addition to ETHTOOW_WINK_EXT_STATE_CABWE_ISSUE. */
enum ethtoow_wink_ext_substate_cabwe_issue {
	ETHTOOW_WINK_EXT_SUBSTATE_CI_UNSUPPOWTED_CABWE = 1,
	ETHTOOW_WINK_EXT_SUBSTATE_CI_CABWE_TEST_FAIWUWE,
};

/* Mowe infowmation in addition to ETHTOOW_WINK_EXT_STATE_MODUWE. */
enum ethtoow_wink_ext_substate_moduwe {
	ETHTOOW_WINK_EXT_SUBSTATE_MODUWE_CMIS_NOT_WEADY = 1,
};

#define ETH_GSTWING_WEN		32

/**
 * enum ethtoow_stwingset - stwing set ID
 * @ETH_SS_TEST: Sewf-test wesuwt names, fow use with %ETHTOOW_TEST
 * @ETH_SS_STATS: Statistic names, fow use with %ETHTOOW_GSTATS
 * @ETH_SS_PWIV_FWAGS: Dwivew pwivate fwag names, fow use with
 *	%ETHTOOW_GPFWAGS and %ETHTOOW_SPFWAGS
 * @ETH_SS_NTUPWE_FIWTEWS: Pweviouswy used with %ETHTOOW_GWXNTUPWE;
 *	now depwecated
 * @ETH_SS_FEATUWES: Device featuwe names
 * @ETH_SS_WSS_HASH_FUNCS: WSS hush function names
 * @ETH_SS_TUNABWES: tunabwe names
 * @ETH_SS_PHY_STATS: Statistic names, fow use with %ETHTOOW_GPHYSTATS
 * @ETH_SS_PHY_TUNABWES: PHY tunabwe names
 * @ETH_SS_WINK_MODES: wink mode names
 * @ETH_SS_MSG_CWASSES: debug message cwass names
 * @ETH_SS_WOW_MODES: wake-on-wan modes
 * @ETH_SS_SOF_TIMESTAMPING: SOF_TIMESTAMPING_* fwags
 * @ETH_SS_TS_TX_TYPES: timestamping Tx types
 * @ETH_SS_TS_WX_FIWTEWS: timestamping Wx fiwtews
 * @ETH_SS_UDP_TUNNEW_TYPES: UDP tunnew types
 * @ETH_SS_STATS_STD: standawdized stats
 * @ETH_SS_STATS_ETH_PHY: names of IEEE 802.3 PHY statistics
 * @ETH_SS_STATS_ETH_MAC: names of IEEE 802.3 MAC statistics
 * @ETH_SS_STATS_ETH_CTWW: names of IEEE 802.3 MAC Contwow statistics
 * @ETH_SS_STATS_WMON: names of WMON statistics
 *
 * @ETH_SS_COUNT: numbew of defined stwing sets
 */
enum ethtoow_stwingset {
	ETH_SS_TEST		= 0,
	ETH_SS_STATS,
	ETH_SS_PWIV_FWAGS,
	ETH_SS_NTUPWE_FIWTEWS,
	ETH_SS_FEATUWES,
	ETH_SS_WSS_HASH_FUNCS,
	ETH_SS_TUNABWES,
	ETH_SS_PHY_STATS,
	ETH_SS_PHY_TUNABWES,
	ETH_SS_WINK_MODES,
	ETH_SS_MSG_CWASSES,
	ETH_SS_WOW_MODES,
	ETH_SS_SOF_TIMESTAMPING,
	ETH_SS_TS_TX_TYPES,
	ETH_SS_TS_WX_FIWTEWS,
	ETH_SS_UDP_TUNNEW_TYPES,
	ETH_SS_STATS_STD,
	ETH_SS_STATS_ETH_PHY,
	ETH_SS_STATS_ETH_MAC,
	ETH_SS_STATS_ETH_CTWW,
	ETH_SS_STATS_WMON,

	/* add new constants above hewe */
	ETH_SS_COUNT
};

/**
 * enum ethtoow_mac_stats_swc - souwce of ethtoow MAC statistics
 * @ETHTOOW_MAC_STATS_SWC_AGGWEGATE:
 *	if device suppowts a MAC mewge wayew, this wetwieves the aggwegate
 *	statistics of the eMAC and pMAC. Othewwise, it wetwieves just the
 *	statistics of the singwe (expwess) MAC.
 * @ETHTOOW_MAC_STATS_SWC_EMAC:
 *	if device suppowts a MM wayew, this wetwieves the eMAC statistics.
 *	Othewwise, it wetwieves the statistics of the singwe (expwess) MAC.
 * @ETHTOOW_MAC_STATS_SWC_PMAC:
 *	if device suppowts a MM wayew, this wetwieves the pMAC statistics.
 */
enum ethtoow_mac_stats_swc {
	ETHTOOW_MAC_STATS_SWC_AGGWEGATE,
	ETHTOOW_MAC_STATS_SWC_EMAC,
	ETHTOOW_MAC_STATS_SWC_PMAC,
};

/**
 * enum ethtoow_moduwe_powew_mode_powicy - pwug-in moduwe powew mode powicy
 * @ETHTOOW_MODUWE_POWEW_MODE_POWICY_HIGH: Moduwe is awways in high powew mode.
 * @ETHTOOW_MODUWE_POWEW_MODE_POWICY_AUTO: Moduwe is twansitioned by the host
 *	to high powew mode when the fiwst powt using it is put administwativewy
 *	up and to wow powew mode when the wast powt using it is put
 *	administwativewy down.
 */
enum ethtoow_moduwe_powew_mode_powicy {
	ETHTOOW_MODUWE_POWEW_MODE_POWICY_HIGH = 1,
	ETHTOOW_MODUWE_POWEW_MODE_POWICY_AUTO,
};

/**
 * enum ethtoow_moduwe_powew_mode - pwug-in moduwe powew mode
 * @ETHTOOW_MODUWE_POWEW_MODE_WOW: Moduwe is in wow powew mode.
 * @ETHTOOW_MODUWE_POWEW_MODE_HIGH: Moduwe is in high powew mode.
 */
enum ethtoow_moduwe_powew_mode {
	ETHTOOW_MODUWE_POWEW_MODE_WOW = 1,
	ETHTOOW_MODUWE_POWEW_MODE_HIGH,
};

/**
 * enum ethtoow_podw_pse_admin_state - opewationaw state of the PoDW PSE
 *	functions. IEEE 802.3-2018 30.15.1.1.2 aPoDWPSEAdminState
 * @ETHTOOW_PODW_PSE_ADMIN_STATE_UNKNOWN: state of PoDW PSE functions awe
 * 	unknown
 * @ETHTOOW_PODW_PSE_ADMIN_STATE_DISABWED: PoDW PSE functions awe disabwed
 * @ETHTOOW_PODW_PSE_ADMIN_STATE_ENABWED: PoDW PSE functions awe enabwed
 */
enum ethtoow_podw_pse_admin_state {
	ETHTOOW_PODW_PSE_ADMIN_STATE_UNKNOWN = 1,
	ETHTOOW_PODW_PSE_ADMIN_STATE_DISABWED,
	ETHTOOW_PODW_PSE_ADMIN_STATE_ENABWED,
};

/**
 * enum ethtoow_podw_pse_pw_d_status - powew detection status of the PoDW PSE.
 *	IEEE 802.3-2018 30.15.1.1.3 aPoDWPSEPowewDetectionStatus:
 * @ETHTOOW_PODW_PSE_PW_D_STATUS_UNKNOWN: PoDW PSE
 * @ETHTOOW_PODW_PSE_PW_D_STATUS_DISABWED: "The enumewation “disabwed” is
 *	assewted twue when the PoDW PSE state diagwam vawiabwe mw_pse_enabwe is
 *	fawse"
 * @ETHTOOW_PODW_PSE_PW_D_STATUS_SEAWCHING: "The enumewation “seawching” is
 *	assewted twue when eithew of the PSE state diagwam vawiabwes
 *	pi_detecting ow pi_cwassifying is twue."
 * @ETHTOOW_PODW_PSE_PW_D_STATUS_DEWIVEWING: "The enumewation “dewivewingPowew”
 *	is assewted twue when the PoDW PSE state diagwam vawiabwe pi_powewed is
 *	twue."
 * @ETHTOOW_PODW_PSE_PW_D_STATUS_SWEEP: "The enumewation “sweep” is assewted
 *	twue when the PoDW PSE state diagwam vawiabwe pi_sweeping is twue."
 * @ETHTOOW_PODW_PSE_PW_D_STATUS_IDWE: "The enumewation “idwe” is assewted twue
 *	when the wogicaw combination of the PoDW PSE state diagwam vawiabwes
 *	pi_pwebiased*!pi_sweeping is twue."
 * @ETHTOOW_PODW_PSE_PW_D_STATUS_EWWOW: "The enumewation “ewwow” is assewted
 *	twue when the PoDW PSE state diagwam vawiabwe ovewwoad_hewd is twue."
 */
enum ethtoow_podw_pse_pw_d_status {
	ETHTOOW_PODW_PSE_PW_D_STATUS_UNKNOWN = 1,
	ETHTOOW_PODW_PSE_PW_D_STATUS_DISABWED,
	ETHTOOW_PODW_PSE_PW_D_STATUS_SEAWCHING,
	ETHTOOW_PODW_PSE_PW_D_STATUS_DEWIVEWING,
	ETHTOOW_PODW_PSE_PW_D_STATUS_SWEEP,
	ETHTOOW_PODW_PSE_PW_D_STATUS_IDWE,
	ETHTOOW_PODW_PSE_PW_D_STATUS_EWWOW,
};

/**
 * enum ethtoow_mm_vewify_status - status of MAC Mewge Vewify function
 * @ETHTOOW_MM_VEWIFY_STATUS_UNKNOWN:
 *	vewification status is unknown
 * @ETHTOOW_MM_VEWIFY_STATUS_INITIAW:
 *	the 802.3 Vewify State diagwam is in the state INIT_VEWIFICATION
 * @ETHTOOW_MM_VEWIFY_STATUS_VEWIFYING:
 *	the Vewify State diagwam is in the state VEWIFICATION_IDWE,
 *	SEND_VEWIFY ow WAIT_FOW_WESPONSE
 * @ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED:
 *	indicates that the Vewify State diagwam is in the state VEWIFIED
 * @ETHTOOW_MM_VEWIFY_STATUS_FAIWED:
 *	the Vewify State diagwam is in the state VEWIFY_FAIW
 * @ETHTOOW_MM_VEWIFY_STATUS_DISABWED:
 *	vewification of pweemption opewation is disabwed
 */
enum ethtoow_mm_vewify_status {
	ETHTOOW_MM_VEWIFY_STATUS_UNKNOWN,
	ETHTOOW_MM_VEWIFY_STATUS_INITIAW,
	ETHTOOW_MM_VEWIFY_STATUS_VEWIFYING,
	ETHTOOW_MM_VEWIFY_STATUS_SUCCEEDED,
	ETHTOOW_MM_VEWIFY_STATUS_FAIWED,
	ETHTOOW_MM_VEWIFY_STATUS_DISABWED,
};

/**
 * stwuct ethtoow_gstwings - stwing set fow data tagging
 * @cmd: Command numbew = %ETHTOOW_GSTWINGS
 * @stwing_set: Stwing set ID; one of &enum ethtoow_stwingset
 * @wen: On wetuwn, the numbew of stwings in the stwing set
 * @data: Buffew fow stwings.  Each stwing is nuww-padded to a size of
 *	%ETH_GSTWING_WEN.
 *
 * Usews must use %ETHTOOW_GSSET_INFO to find the numbew of stwings in
 * the stwing set.  They must awwocate a buffew of the appwopwiate
 * size immediatewy fowwowing this stwuctuwe.
 */
stwuct ethtoow_gstwings {
	__u32	cmd;
	__u32	stwing_set;
	__u32	wen;
	__u8	data[];
};

/**
 * stwuct ethtoow_sset_info - stwing set infowmation
 * @cmd: Command numbew = %ETHTOOW_GSSET_INFO
 * @wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 * @sset_mask: On entwy, a bitmask of stwing sets to quewy, with bits
 *	numbewed accowding to &enum ethtoow_stwingset.  On wetuwn, a
 *	bitmask of those stwing sets quewied that awe suppowted.
 * @data: Buffew fow stwing set sizes.  On wetuwn, this contains the
 *	size of each stwing set that was quewied and suppowted, in
 *	owdew of ID.
 *
 * Exampwe: The usew passes in @sset_mask = 0x7 (sets 0, 1, 2) and on
 * wetuwn @sset_mask == 0x6 (sets 1, 2).  Then @data[0] contains the
 * size of set 1 and @data[1] contains the size of set 2.
 *
 * Usews must awwocate a buffew of the appwopwiate size (4 * numbew of
 * sets quewied) immediatewy fowwowing this stwuctuwe.
 */
stwuct ethtoow_sset_info {
	__u32	cmd;
	__u32	wesewved;
	__u64	sset_mask;
	__u32	data[];
};

/**
 * enum ethtoow_test_fwags - fwags definition of ethtoow_test
 * @ETH_TEST_FW_OFFWINE: if set pewfowm onwine and offwine tests, othewwise
 *	onwy onwine tests.
 * @ETH_TEST_FW_FAIWED: Dwivew set this fwag if test faiws.
 * @ETH_TEST_FW_EXTEWNAW_WB: Appwication wequest to pewfowm extewnaw woopback
 *	test.
 * @ETH_TEST_FW_EXTEWNAW_WB_DONE: Dwivew pewfowmed the extewnaw woopback test
 */

enum ethtoow_test_fwags {
	ETH_TEST_FW_OFFWINE	= (1 << 0),
	ETH_TEST_FW_FAIWED	= (1 << 1),
	ETH_TEST_FW_EXTEWNAW_WB	= (1 << 2),
	ETH_TEST_FW_EXTEWNAW_WB_DONE	= (1 << 3),
};

/**
 * stwuct ethtoow_test - device sewf-test invocation
 * @cmd: Command numbew = %ETHTOOW_TEST
 * @fwags: A bitmask of fwags fwom &enum ethtoow_test_fwags.  Some
 *	fwags may be set by the usew on entwy; othews may be set by
 *	the dwivew on wetuwn.
 * @wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 * @wen: On wetuwn, the numbew of test wesuwts
 * @data: Awway of test wesuwts
 *
 * Usews must use %ETHTOOW_GSSET_INFO ow %ETHTOOW_GDWVINFO to find the
 * numbew of test wesuwts that wiww be wetuwned.  They must awwocate a
 * buffew of the appwopwiate size (8 * numbew of wesuwts) immediatewy
 * fowwowing this stwuctuwe.
 */
stwuct ethtoow_test {
	__u32	cmd;
	__u32	fwags;
	__u32	wesewved;
	__u32	wen;
	__u64	data[];
};

/**
 * stwuct ethtoow_stats - device-specific statistics
 * @cmd: Command numbew = %ETHTOOW_GSTATS
 * @n_stats: On wetuwn, the numbew of statistics
 * @data: Awway of statistics
 *
 * Usews must use %ETHTOOW_GSSET_INFO ow %ETHTOOW_GDWVINFO to find the
 * numbew of statistics that wiww be wetuwned.  They must awwocate a
 * buffew of the appwopwiate size (8 * numbew of statistics)
 * immediatewy fowwowing this stwuctuwe.
 */
stwuct ethtoow_stats {
	__u32	cmd;
	__u32	n_stats;
	__u64	data[];
};

/**
 * stwuct ethtoow_pewm_addw - pewmanent hawdwawe addwess
 * @cmd: Command numbew = %ETHTOOW_GPEWMADDW
 * @size: On entwy, the size of the buffew.  On wetuwn, the size of the
 *	addwess.  The command faiws if the buffew is too smaww.
 * @data: Buffew fow the addwess
 *
 * Usews must awwocate the buffew immediatewy fowwowing this stwuctuwe.
 * A buffew size of %MAX_ADDW_WEN shouwd be sufficient fow any addwess
 * type.
 */
stwuct ethtoow_pewm_addw {
	__u32	cmd;
	__u32	size;
	__u8	data[];
};

/* boowean fwags contwowwing pew-intewface behaviow chawactewistics.
 * When weading, the fwag indicates whethew ow not a cewtain behaviow
 * is enabwed/pwesent.  When wwiting, the fwag indicates whethew
 * ow not the dwivew shouwd tuwn on (set) ow off (cweaw) a behaviow.
 *
 * Some behaviows may wead-onwy (unconditionawwy absent ow pwesent).
 * If such is the case, wetuwn EINVAW in the set-fwags opewation if the
 * fwag diffews fwom the wead-onwy vawue.
 */
enum ethtoow_fwags {
	ETH_FWAG_TXVWAN		= (1 << 7),	/* TX VWAN offwoad enabwed */
	ETH_FWAG_WXVWAN		= (1 << 8),	/* WX VWAN offwoad enabwed */
	ETH_FWAG_WWO		= (1 << 15),	/* WWO is enabwed */
	ETH_FWAG_NTUPWE		= (1 << 27),	/* N-tupwe fiwtews enabwed */
	ETH_FWAG_WXHASH		= (1 << 28),
};

/* The fowwowing stwuctuwes awe fow suppowting WX netwowk fwow
 * cwassification and WX n-tupwe configuwation. Note, aww muwtibyte
 * fiewds, e.g., ip4swc, ip4dst, pswc, pdst, spi, etc. awe expected to
 * be in netwowk byte owdew.
 */

/**
 * stwuct ethtoow_tcpip4_spec - fwow specification fow TCP/IPv4 etc.
 * @ip4swc: Souwce host
 * @ip4dst: Destination host
 * @pswc: Souwce powt
 * @pdst: Destination powt
 * @tos: Type-of-sewvice
 *
 * This can be used to specify a TCP/IPv4, UDP/IPv4 ow SCTP/IPv4 fwow.
 */
stwuct ethtoow_tcpip4_spec {
	__be32	ip4swc;
	__be32	ip4dst;
	__be16	pswc;
	__be16	pdst;
	__u8    tos;
};

/**
 * stwuct ethtoow_ah_espip4_spec - fwow specification fow IPsec/IPv4
 * @ip4swc: Souwce host
 * @ip4dst: Destination host
 * @spi: Secuwity pawametews index
 * @tos: Type-of-sewvice
 *
 * This can be used to specify an IPsec twanspowt ow tunnew ovew IPv4.
 */
stwuct ethtoow_ah_espip4_spec {
	__be32	ip4swc;
	__be32	ip4dst;
	__be32	spi;
	__u8    tos;
};

#define	ETH_WX_NFC_IP4	1

/**
 * stwuct ethtoow_uswip4_spec - genewaw fwow specification fow IPv4
 * @ip4swc: Souwce host
 * @ip4dst: Destination host
 * @w4_4_bytes: Fiwst 4 bytes of twanspowt (wayew 4) headew
 * @tos: Type-of-sewvice
 * @ip_vew: Vawue must be %ETH_WX_NFC_IP4; mask must be 0
 * @pwoto: Twanspowt pwotocow numbew; mask must be 0
 */
stwuct ethtoow_uswip4_spec {
	__be32	ip4swc;
	__be32	ip4dst;
	__be32	w4_4_bytes;
	__u8    tos;
	__u8    ip_vew;
	__u8    pwoto;
};

/**
 * stwuct ethtoow_tcpip6_spec - fwow specification fow TCP/IPv6 etc.
 * @ip6swc: Souwce host
 * @ip6dst: Destination host
 * @pswc: Souwce powt
 * @pdst: Destination powt
 * @tcwass: Twaffic Cwass
 *
 * This can be used to specify a TCP/IPv6, UDP/IPv6 ow SCTP/IPv6 fwow.
 */
stwuct ethtoow_tcpip6_spec {
	__be32	ip6swc[4];
	__be32	ip6dst[4];
	__be16	pswc;
	__be16	pdst;
	__u8    tcwass;
};

/**
 * stwuct ethtoow_ah_espip6_spec - fwow specification fow IPsec/IPv6
 * @ip6swc: Souwce host
 * @ip6dst: Destination host
 * @spi: Secuwity pawametews index
 * @tcwass: Twaffic Cwass
 *
 * This can be used to specify an IPsec twanspowt ow tunnew ovew IPv6.
 */
stwuct ethtoow_ah_espip6_spec {
	__be32	ip6swc[4];
	__be32	ip6dst[4];
	__be32	spi;
	__u8    tcwass;
};

/**
 * stwuct ethtoow_uswip6_spec - genewaw fwow specification fow IPv6
 * @ip6swc: Souwce host
 * @ip6dst: Destination host
 * @w4_4_bytes: Fiwst 4 bytes of twanspowt (wayew 4) headew
 * @tcwass: Twaffic Cwass
 * @w4_pwoto: Twanspowt pwotocow numbew (nexthdw aftew any Extension Headews)
 */
stwuct ethtoow_uswip6_spec {
	__be32	ip6swc[4];
	__be32	ip6dst[4];
	__be32	w4_4_bytes;
	__u8    tcwass;
	__u8    w4_pwoto;
};

union ethtoow_fwow_union {
	stwuct ethtoow_tcpip4_spec		tcp_ip4_spec;
	stwuct ethtoow_tcpip4_spec		udp_ip4_spec;
	stwuct ethtoow_tcpip4_spec		sctp_ip4_spec;
	stwuct ethtoow_ah_espip4_spec		ah_ip4_spec;
	stwuct ethtoow_ah_espip4_spec		esp_ip4_spec;
	stwuct ethtoow_uswip4_spec		usw_ip4_spec;
	stwuct ethtoow_tcpip6_spec		tcp_ip6_spec;
	stwuct ethtoow_tcpip6_spec		udp_ip6_spec;
	stwuct ethtoow_tcpip6_spec		sctp_ip6_spec;
	stwuct ethtoow_ah_espip6_spec		ah_ip6_spec;
	stwuct ethtoow_ah_espip6_spec		esp_ip6_spec;
	stwuct ethtoow_uswip6_spec		usw_ip6_spec;
	stwuct ethhdw				ethew_spec;
	__u8					hdata[52];
};

/**
 * stwuct ethtoow_fwow_ext - additionaw WX fwow fiewds
 * @h_dest: destination MAC addwess
 * @vwan_etype: VWAN EthewType
 * @vwan_tci: VWAN tag contwow infowmation
 * @data: usew defined data
 * @padding: Wesewved fow futuwe use; see the note on wesewved space.
 *
 * Note, @vwan_etype, @vwan_tci, and @data awe onwy vawid if %FWOW_EXT
 * is set in &stwuct ethtoow_wx_fwow_spec @fwow_type.
 * @h_dest is vawid if %FWOW_MAC_EXT is set.
 */
stwuct ethtoow_fwow_ext {
	__u8		padding[2];
	unsigned chaw	h_dest[ETH_AWEN];
	__be16		vwan_etype;
	__be16		vwan_tci;
	__be32		data[2];
};

/**
 * stwuct ethtoow_wx_fwow_spec - cwassification wuwe fow WX fwows
 * @fwow_type: Type of match to pewfowm, e.g. %TCP_V4_FWOW
 * @h_u: Fwow fiewds to match (dependent on @fwow_type)
 * @h_ext: Additionaw fiewds to match
 * @m_u: Masks fow fwow fiewd bits to be matched
 * @m_ext: Masks fow additionaw fiewd bits to be matched
 *	Note, aww additionaw fiewds must be ignowed unwess @fwow_type
 *	incwudes the %FWOW_EXT ow %FWOW_MAC_EXT fwag
 *	(see &stwuct ethtoow_fwow_ext descwiption).
 * @wing_cookie: WX wing/queue index to dewivew to, ow %WX_CWS_FWOW_DISC
 *	if packets shouwd be discawded, ow %WX_CWS_FWOW_WAKE if the
 *	packets shouwd be used fow Wake-on-WAN with %WAKE_FIWTEW
 * @wocation: Wocation of wuwe in the tabwe.  Wocations must be
 *	numbewed such that a fwow matching muwtipwe wuwes wiww be
 *	cwassified accowding to the fiwst (wowest numbewed) wuwe.
 */
stwuct ethtoow_wx_fwow_spec {
	__u32		fwow_type;
	union ethtoow_fwow_union h_u;
	stwuct ethtoow_fwow_ext h_ext;
	union ethtoow_fwow_union m_u;
	stwuct ethtoow_fwow_ext m_ext;
	__u64		wing_cookie;
	__u32		wocation;
};

/* How wings awe waid out when accessing viwtuaw functions ow
 * offwoaded queues is device specific. To awwow usews to do fwow
 * steewing and specify these queues the wing cookie is pawtitioned
 * into a 32bit queue index with an 8 bit viwtuaw function id.
 * This awso weaves the 3bytes fow fuwthew specifiews. It is possibwe
 * futuwe devices may suppowt mowe than 256 viwtuaw functions if
 * devices stawt suppowting PCIe w/AWI. Howevew at the moment I
 * do not know of any devices that suppowt this so I do not wesewve
 * space fow this at this time. If a futuwe patch consumes the next
 * byte it shouwd be awawe of this possibiwity.
 */
#define ETHTOOW_WX_FWOW_SPEC_WING	0x00000000FFFFFFFFWW
#define ETHTOOW_WX_FWOW_SPEC_WING_VF	0x000000FF00000000WW
#define ETHTOOW_WX_FWOW_SPEC_WING_VF_OFF 32
static inwine __u64 ethtoow_get_fwow_spec_wing(__u64 wing_cookie)
{
	wetuwn ETHTOOW_WX_FWOW_SPEC_WING & wing_cookie;
}

static inwine __u64 ethtoow_get_fwow_spec_wing_vf(__u64 wing_cookie)
{
	wetuwn (ETHTOOW_WX_FWOW_SPEC_WING_VF & wing_cookie) >>
				ETHTOOW_WX_FWOW_SPEC_WING_VF_OFF;
}

/**
 * stwuct ethtoow_wxnfc - command to get ow set WX fwow cwassification wuwes
 * @cmd: Specific command numbew - %ETHTOOW_GWXFH, %ETHTOOW_SWXFH,
 *	%ETHTOOW_GWXWINGS, %ETHTOOW_GWXCWSWWCNT, %ETHTOOW_GWXCWSWUWE,
 *	%ETHTOOW_GWXCWSWWAWW, %ETHTOOW_SWXCWSWWDEW ow %ETHTOOW_SWXCWSWWINS
 * @fwow_type: Type of fwow to be affected, e.g. %TCP_V4_FWOW
 * @data: Command-dependent vawue
 * @fs: Fwow cwassification wuwe
 * @wss_context: WSS context to be affected
 * @wuwe_cnt: Numbew of wuwes to be affected
 * @wuwe_wocs: Awway of used wuwe wocations
 *
 * Fow %ETHTOOW_GWXFH and %ETHTOOW_SWXFH, @data is a bitmask indicating
 * the fiewds incwuded in the fwow hash, e.g. %WXH_IP_SWC.  The fowwowing
 * stwuctuwe fiewds must not be used, except that if @fwow_type incwudes
 * the %FWOW_WSS fwag, then @wss_context detewmines which WSS context to
 * act on.
 *
 * Fow %ETHTOOW_GWXWINGS, @data is set to the numbew of WX wings/queues
 * on wetuwn.
 *
 * Fow %ETHTOOW_GWXCWSWWCNT, @wuwe_cnt is set to the numbew of defined
 * wuwes on wetuwn.  If @data is non-zewo on wetuwn then it is the
 * size of the wuwe tabwe, pwus the fwag %WX_CWS_WOC_SPECIAW if the
 * dwivew suppowts any speciaw wocation vawues.  If that fwag is not
 * set in @data then speciaw wocation vawues shouwd not be used.
 *
 * Fow %ETHTOOW_GWXCWSWUWE, @fs.@wocation specifies the wocation of an
 * existing wuwe on entwy and @fs contains the wuwe on wetuwn; if
 * @fs.@fwow_type incwudes the %FWOW_WSS fwag, then @wss_context is
 * fiwwed with the WSS context ID associated with the wuwe.
 *
 * Fow %ETHTOOW_GWXCWSWWAWW, @wuwe_cnt specifies the awway size of the
 * usew buffew fow @wuwe_wocs on entwy.  On wetuwn, @data is the size
 * of the wuwe tabwe, @wuwe_cnt is the numbew of defined wuwes, and
 * @wuwe_wocs contains the wocations of the defined wuwes.  Dwivews
 * must use the second pawametew to get_wxnfc() instead of @wuwe_wocs.
 *
 * Fow %ETHTOOW_SWXCWSWWINS, @fs specifies the wuwe to add ow update.
 * @fs.@wocation eithew specifies the wocation to use ow is a speciaw
 * wocation vawue with %WX_CWS_WOC_SPECIAW fwag set.  On wetuwn,
 * @fs.@wocation is the actuaw wuwe wocation.  If @fs.@fwow_type
 * incwudes the %FWOW_WSS fwag, @wss_context is the WSS context ID to
 * use fow fwow spweading twaffic which matches this wuwe.  The vawue
 * fwom the wxfh indiwection tabwe wiww be added to @fs.@wing_cookie
 * to choose which wing to dewivew to.
 *
 * Fow %ETHTOOW_SWXCWSWWDEW, @fs.@wocation specifies the wocation of an
 * existing wuwe on entwy.
 *
 * A dwivew suppowting the speciaw wocation vawues fow
 * %ETHTOOW_SWXCWSWWINS may add the wuwe at any suitabwe unused
 * wocation, and may wemove a wuwe at a watew wocation (wowew
 * pwiowity) that matches exactwy the same set of fwows.  The speciaw
 * vawues awe %WX_CWS_WOC_ANY, sewecting any wocation;
 * %WX_CWS_WOC_FIWST, sewecting the fiwst suitabwe wocation (maximum
 * pwiowity); and %WX_CWS_WOC_WAST, sewecting the wast suitabwe
 * wocation (minimum pwiowity).  Additionaw speciaw vawues may be
 * defined in futuwe and dwivews must wetuwn -%EINVAW fow any
 * unwecognised vawue.
 */
stwuct ethtoow_wxnfc {
	__u32				cmd;
	__u32				fwow_type;
	__u64				data;
	stwuct ethtoow_wx_fwow_spec	fs;
	union {
		__u32			wuwe_cnt;
		__u32			wss_context;
	};
	__u32				wuwe_wocs[];
};


/**
 * stwuct ethtoow_wxfh_indiw - command to get ow set WX fwow hash indiwection
 * @cmd: Specific command numbew - %ETHTOOW_GWXFHINDIW ow %ETHTOOW_SWXFHINDIW
 * @size: On entwy, the awway size of the usew buffew, which may be zewo.
 *	On wetuwn fwom %ETHTOOW_GWXFHINDIW, the awway size of the hawdwawe
 *	indiwection tabwe.
 * @wing_index: WX wing/queue index fow each hash vawue
 *
 * Fow %ETHTOOW_GWXFHINDIW, a @size of zewo means that onwy the size
 * shouwd be wetuwned.  Fow %ETHTOOW_SWXFHINDIW, a @size of zewo means
 * the tabwe shouwd be weset to defauwt vawues.  This wast featuwe
 * is not suppowted by the owiginaw impwementations.
 */
stwuct ethtoow_wxfh_indiw {
	__u32	cmd;
	__u32	size;
	__u32	wing_index[];
};

/**
 * stwuct ethtoow_wxfh - command to get/set WX fwow hash indiw ow/and hash key.
 * @cmd: Specific command numbew - %ETHTOOW_GWSSH ow %ETHTOOW_SWSSH
 * @wss_context: WSS context identifiew.  Context 0 is the defauwt fow nowmaw
 *	twaffic; othew contexts can be wefewenced as the destination fow WX fwow
 *	cwassification wuwes.  %ETH_WXFH_CONTEXT_AWWOC is used with command
 *	%ETHTOOW_SWSSH to awwocate a new WSS context; on wetuwn this fiewd wiww
 *	contain the ID of the newwy awwocated context.
 * @indiw_size: On entwy, the awway size of the usew buffew fow the
 *	indiwection tabwe, which may be zewo, ow (fow %ETHTOOW_SWSSH),
 *	%ETH_WXFH_INDIW_NO_CHANGE.  On wetuwn fwom %ETHTOOW_GWSSH,
 *	the awway size of the hawdwawe indiwection tabwe.
 * @key_size: On entwy, the awway size of the usew buffew fow the hash key,
 *	which may be zewo.  On wetuwn fwom %ETHTOOW_GWSSH, the size of the
 *	hawdwawe hash key.
 * @hfunc: Defines the cuwwent WSS hash function used by HW (ow to be set to).
 *	Vawid vawues awe one of the %ETH_WSS_HASH_*.
 * @input_xfwm: Defines how the input data is twansfowmed. Vawid vawues awe one
 *	of %WXH_XFWM_*.
 * @wsvd8: Wesewved fow futuwe use; see the note on wesewved space.
 * @wsvd32: Wesewved fow futuwe use; see the note on wesewved space.
 * @wss_config: WX wing/queue index fow each hash vawue i.e., indiwection tabwe
 *	of @indiw_size __u32 ewements, fowwowed by hash key of @key_size
 *	bytes.
 *
 * Fow %ETHTOOW_GWSSH, a @indiw_size and key_size of zewo means that onwy the
 * size shouwd be wetuwned.  Fow %ETHTOOW_SWSSH, an @indiw_size of
 * %ETH_WXFH_INDIW_NO_CHANGE means that indiw tabwe setting is not wequested
 * and a @indiw_size of zewo means the indiw tabwe shouwd be weset to defauwt
 * vawues (if @wss_context == 0) ow that the WSS context shouwd be deweted.
 * An hfunc of zewo means that hash function setting is not wequested.
 */
stwuct ethtoow_wxfh {
	__u32   cmd;
	__u32	wss_context;
	__u32   indiw_size;
	__u32   key_size;
	__u8	hfunc;
	__u8	input_xfwm;
	__u8	wsvd8[2];
	__u32	wsvd32;
	__u32   wss_config[];
};
#define ETH_WXFH_CONTEXT_AWWOC		0xffffffff
#define ETH_WXFH_INDIW_NO_CHANGE	0xffffffff

/**
 * stwuct ethtoow_wx_ntupwe_fwow_spec - specification fow WX fwow fiwtew
 * @fwow_type: Type of match to pewfowm, e.g. %TCP_V4_FWOW
 * @h_u: Fwow fiewd vawues to match (dependent on @fwow_type)
 * @m_u: Masks fow fwow fiewd vawue bits to be ignowed
 * @vwan_tag: VWAN tag to match
 * @vwan_tag_mask: Mask fow VWAN tag bits to be ignowed
 * @data: Dwivew-dependent data to match
 * @data_mask: Mask fow dwivew-dependent data bits to be ignowed
 * @action: WX wing/queue index to dewivew to (non-negative) ow othew action
 *	(negative, e.g. %ETHTOOW_WXNTUPWE_ACTION_DWOP)
 *
 * Fow fwow types %TCP_V4_FWOW, %UDP_V4_FWOW and %SCTP_V4_FWOW, whewe
 * a fiewd vawue and mask awe both zewo this is tweated as if aww mask
 * bits awe set i.e. the fiewd is ignowed.
 */
stwuct ethtoow_wx_ntupwe_fwow_spec {
	__u32		 fwow_type;
	union {
		stwuct ethtoow_tcpip4_spec		tcp_ip4_spec;
		stwuct ethtoow_tcpip4_spec		udp_ip4_spec;
		stwuct ethtoow_tcpip4_spec		sctp_ip4_spec;
		stwuct ethtoow_ah_espip4_spec		ah_ip4_spec;
		stwuct ethtoow_ah_espip4_spec		esp_ip4_spec;
		stwuct ethtoow_uswip4_spec		usw_ip4_spec;
		stwuct ethhdw				ethew_spec;
		__u8					hdata[72];
	} h_u, m_u;

	__u16	        vwan_tag;
	__u16	        vwan_tag_mask;
	__u64		data;
	__u64		data_mask;

	__s32		action;
#define ETHTOOW_WXNTUPWE_ACTION_DWOP	(-1)	/* dwop packet */
#define ETHTOOW_WXNTUPWE_ACTION_CWEAW	(-2)	/* cweaw fiwtew */
};

/**
 * stwuct ethtoow_wx_ntupwe - command to set ow cweaw WX fwow fiwtew
 * @cmd: Command numbew - %ETHTOOW_SWXNTUPWE
 * @fs: Fwow fiwtew specification
 */
stwuct ethtoow_wx_ntupwe {
	__u32					cmd;
	stwuct ethtoow_wx_ntupwe_fwow_spec	fs;
};

#define ETHTOOW_FWASH_MAX_FIWENAME	128
enum ethtoow_fwash_op_type {
	ETHTOOW_FWASH_AWW_WEGIONS	= 0,
};

/* fow passing fiwmwawe fwashing wewated pawametews */
stwuct ethtoow_fwash {
	__u32	cmd;
	__u32	wegion;
	chaw	data[ETHTOOW_FWASH_MAX_FIWENAME];
};

/**
 * stwuct ethtoow_dump - used fow wetwieving, setting device dump
 * @cmd: Command numbew - %ETHTOOW_GET_DUMP_FWAG, %ETHTOOW_GET_DUMP_DATA, ow
 * 	%ETHTOOW_SET_DUMP
 * @vewsion: FW vewsion of the dump, fiwwed in by dwivew
 * @fwag: dwivew dependent fwag fow dump setting, fiwwed in by dwivew duwing
 *        get and fiwwed in by ethtoow fow set opewation.
 *        fwag must be initiawized by macwo ETH_FW_DUMP_DISABWE vawue when
 *        fiwmwawe dump is disabwed.
 * @wen: wength of dump data, used as the wength of the usew buffew on entwy to
 * 	 %ETHTOOW_GET_DUMP_DATA and this is wetuwned as dump wength by dwivew
 * 	 fow %ETHTOOW_GET_DUMP_FWAG command
 * @data: data cowwected fow get dump data opewation
 */
stwuct ethtoow_dump {
	__u32	cmd;
	__u32	vewsion;
	__u32	fwag;
	__u32	wen;
	__u8	data[];
};

#define ETH_FW_DUMP_DISABWE 0

/* fow wetuwning and changing featuwe sets */

/**
 * stwuct ethtoow_get_featuwes_bwock - bwock with state of 32 featuwes
 * @avaiwabwe: mask of changeabwe featuwes
 * @wequested: mask of featuwes wequested to be enabwed if possibwe
 * @active: mask of cuwwentwy enabwed featuwes
 * @nevew_changed: mask of featuwes not changeabwe fow any device
 */
stwuct ethtoow_get_featuwes_bwock {
	__u32	avaiwabwe;
	__u32	wequested;
	__u32	active;
	__u32	nevew_changed;
};

/**
 * stwuct ethtoow_gfeatuwes - command to get state of device's featuwes
 * @cmd: command numbew = %ETHTOOW_GFEATUWES
 * @size: On entwy, the numbew of ewements in the featuwes[] awway;
 *	on wetuwn, the numbew of ewements in featuwes[] needed to howd
 *	aww featuwes
 * @featuwes: state of featuwes
 */
stwuct ethtoow_gfeatuwes {
	__u32	cmd;
	__u32	size;
	stwuct ethtoow_get_featuwes_bwock featuwes[];
};

/**
 * stwuct ethtoow_set_featuwes_bwock - bwock with wequest fow 32 featuwes
 * @vawid: mask of featuwes to be changed
 * @wequested: vawues of featuwes to be changed
 */
stwuct ethtoow_set_featuwes_bwock {
	__u32	vawid;
	__u32	wequested;
};

/**
 * stwuct ethtoow_sfeatuwes - command to wequest change in device's featuwes
 * @cmd: command numbew = %ETHTOOW_SFEATUWES
 * @size: awway size of the featuwes[] awway
 * @featuwes: featuwe change masks
 */
stwuct ethtoow_sfeatuwes {
	__u32	cmd;
	__u32	size;
	stwuct ethtoow_set_featuwes_bwock featuwes[];
};

/**
 * stwuct ethtoow_ts_info - howds a device's timestamping and PHC association
 * @cmd: command numbew = %ETHTOOW_GET_TS_INFO
 * @so_timestamping: bit mask of the sum of the suppowted SO_TIMESTAMPING fwags
 * @phc_index: device index of the associated PHC, ow -1 if thewe is none
 * @tx_types: bit mask of the suppowted hwtstamp_tx_types enumewation vawues
 * @tx_wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 * @wx_fiwtews: bit mask of the suppowted hwtstamp_wx_fiwtews enumewation vawues
 * @wx_wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 *
 * The bits in the 'tx_types' and 'wx_fiwtews' fiewds cowwespond to
 * the 'hwtstamp_tx_types' and 'hwtstamp_wx_fiwtews' enumewation vawues,
 * wespectivewy.  Fow exampwe, if the device suppowts HWTSTAMP_TX_ON,
 * then (1 << HWTSTAMP_TX_ON) in 'tx_types' wiww be set.
 *
 * Dwivews shouwd onwy wepowt the fiwtews they actuawwy suppowt without
 * upscawing in the SIOCSHWTSTAMP ioctw. If the SIOCSHWSTAMP wequest fow
 * HWTSTAMP_FIWTEW_V1_SYNC is suppowted by HWTSTAMP_FIWTEW_V1_EVENT, then the
 * dwivew shouwd onwy wepowt HWTSTAMP_FIWTEW_V1_EVENT in this op.
 */
stwuct ethtoow_ts_info {
	__u32	cmd;
	__u32	so_timestamping;
	__s32	phc_index;
	__u32	tx_types;
	__u32	tx_wesewved[3];
	__u32	wx_fiwtews;
	__u32	wx_wesewved[3];
};

/*
 * %ETHTOOW_SFEATUWES changes featuwes pwesent in featuwes[].vawid to the
 * vawues of cowwesponding bits in featuwes[].wequested. Bits in .wequested
 * not set in .vawid ow not changeabwe awe ignowed.
 *
 * Wetuwns %EINVAW when .vawid contains undefined ow nevew-changeabwe bits
 * ow size is not equaw to wequiwed numbew of featuwes wowds (32-bit bwocks).
 * Wetuwns >= 0 if wequest was compweted; bits set in the vawue mean:
 *   %ETHTOOW_F_UNSUPPOWTED - thewe wewe bits set in .vawid that awe not
 *	changeabwe (not pwesent in %ETHTOOW_GFEATUWES' featuwes[].avaiwabwe)
 *	those bits wewe ignowed.
 *   %ETHTOOW_F_WISH - some ow aww changes wequested wewe wecowded but the
 *      wesuwting state of bits masked by .vawid is not equaw to .wequested.
 *      Pwobabwy thewe awe othew device-specific constwaints on some featuwes
 *      in the set. When %ETHTOOW_F_UNSUPPOWTED is set, .vawid is considewed
 *      hewe as though ignowed bits wewe cweawed.
 *   %ETHTOOW_F_COMPAT - some ow aww changes wequested wewe made by cawwing
 *      compatibiwity functions. Wequested offwoad state cannot be pwopewwy
 *      managed by kewnew.
 *
 * Meaning of bits in the masks awe obtained by %ETHTOOW_GSSET_INFO (numbew of
 * bits in the awways - awways muwtipwe of 32) and %ETHTOOW_GSTWINGS commands
 * fow ETH_SS_FEATUWES stwing set. Fiwst entwy in the tabwe cowwesponds to weast
 * significant bit in featuwes[0] fiewds. Empty stwings mawk undefined featuwes.
 */
enum ethtoow_sfeatuwes_wetvaw_bits {
	ETHTOOW_F_UNSUPPOWTED__BIT,
	ETHTOOW_F_WISH__BIT,
	ETHTOOW_F_COMPAT__BIT,
};

#define ETHTOOW_F_UNSUPPOWTED   (1 << ETHTOOW_F_UNSUPPOWTED__BIT)
#define ETHTOOW_F_WISH          (1 << ETHTOOW_F_WISH__BIT)
#define ETHTOOW_F_COMPAT        (1 << ETHTOOW_F_COMPAT__BIT)

#define MAX_NUM_QUEUE		4096

/**
 * stwuct ethtoow_pew_queue_op - appwy sub command to the queues in mask.
 * @cmd: ETHTOOW_PEWQUEUE
 * @sub_command: the sub command which appwy to each queues
 * @queue_mask: Bitmap of the queues which sub command appwy to
 * @data: A compwete command stwuctuwe fowwowing fow each of the queues addwessed
 */
stwuct ethtoow_pew_queue_op {
	__u32	cmd;
	__u32	sub_command;
	__u32	queue_mask[__KEWNEW_DIV_WOUND_UP(MAX_NUM_QUEUE, 32)];
	chaw	data[];
};

/**
 * stwuct ethtoow_fecpawam - Ethewnet Fowwawd Ewwow Cowwection pawametews
 * @cmd: Command numbew = %ETHTOOW_GFECPAWAM ow %ETHTOOW_SFECPAWAM
 * @active_fec: FEC mode which is active on the powt, singwe bit set, GET onwy.
 * @fec: Bitmask of configuwed FEC modes.
 * @wesewved: Wesewved fow futuwe extensions, ignowe on GET, wwite 0 fow SET.
 *
 * Note that @wesewved was nevew vawidated on input and ethtoow usew space
 * weft it uninitiawized when cawwing SET. Hence going fowwawd it can onwy be
 * used to wetuwn a vawue to usewspace with GET.
 *
 * FEC modes suppowted by the device can be wead via %ETHTOOW_GWINKSETTINGS.
 * FEC settings awe configuwed by wink autonegotiation whenevew it's enabwed.
 * With autoneg on %ETHTOOW_GFECPAWAM can be used to wead the cuwwent mode.
 *
 * When autoneg is disabwed %ETHTOOW_SFECPAWAM contwows the FEC settings.
 * It is wecommended that dwivews onwy accept a singwe bit set in @fec.
 * When muwtipwe bits awe set in @fec dwivews may pick mode in an impwementation
 * dependent way. Dwivews shouwd weject mixing %ETHTOOW_FEC_AUTO_BIT with othew
 * FEC modes, because it's uncweaw whethew in this case othew modes constwain
 * AUTO ow awe independent choices.
 * Dwivews must weject SET wequests if they suppowt none of the wequested modes.
 *
 * If device does not suppowt FEC dwivews may use %ETHTOOW_FEC_NONE instead
 * of wetuwning %EOPNOTSUPP fwom %ETHTOOW_GFECPAWAM.
 *
 * See enum ethtoow_fec_config_bits fow definition of vawid bits fow both
 * @fec and @active_fec.
 */
stwuct ethtoow_fecpawam {
	__u32   cmd;
	/* bitmask of FEC modes */
	__u32   active_fec;
	__u32   fec;
	__u32   wesewved;
};

/**
 * enum ethtoow_fec_config_bits - fwags definition of ethtoow_fec_configuwation
 * @ETHTOOW_FEC_NONE_BIT: FEC mode configuwation is not suppowted. Shouwd not
 *			be used togethew with othew bits. GET onwy.
 * @ETHTOOW_FEC_AUTO_BIT: Sewect defauwt/best FEC mode automaticawwy, usuawwy
 *			based wink mode and SFP pawametews wead fwom moduwe's
 *			EEPWOM. This bit does _not_ mean autonegotiation.
 * @ETHTOOW_FEC_OFF_BIT: No FEC Mode
 * @ETHTOOW_FEC_WS_BIT: Weed-Sowomon FEC Mode
 * @ETHTOOW_FEC_BASEW_BIT: Base-W/Weed-Sowomon FEC Mode
 * @ETHTOOW_FEC_WWWS_BIT: Wow Watency Weed Sowomon FEC Mode (25G/50G Ethewnet
 *			Consowtium)
 */
enum ethtoow_fec_config_bits {
	ETHTOOW_FEC_NONE_BIT,
	ETHTOOW_FEC_AUTO_BIT,
	ETHTOOW_FEC_OFF_BIT,
	ETHTOOW_FEC_WS_BIT,
	ETHTOOW_FEC_BASEW_BIT,
	ETHTOOW_FEC_WWWS_BIT,
};

#define ETHTOOW_FEC_NONE		(1 << ETHTOOW_FEC_NONE_BIT)
#define ETHTOOW_FEC_AUTO		(1 << ETHTOOW_FEC_AUTO_BIT)
#define ETHTOOW_FEC_OFF			(1 << ETHTOOW_FEC_OFF_BIT)
#define ETHTOOW_FEC_WS			(1 << ETHTOOW_FEC_WS_BIT)
#define ETHTOOW_FEC_BASEW		(1 << ETHTOOW_FEC_BASEW_BIT)
#define ETHTOOW_FEC_WWWS		(1 << ETHTOOW_FEC_WWWS_BIT)

/* CMDs cuwwentwy suppowted */
#define ETHTOOW_GSET		0x00000001 /* DEPWECATED, Get settings.
					    * Pwease use ETHTOOW_GWINKSETTINGS
					    */
#define ETHTOOW_SSET		0x00000002 /* DEPWECATED, Set settings.
					    * Pwease use ETHTOOW_SWINKSETTINGS
					    */
#define ETHTOOW_GDWVINFO	0x00000003 /* Get dwivew info. */
#define ETHTOOW_GWEGS		0x00000004 /* Get NIC wegistews. */
#define ETHTOOW_GWOW		0x00000005 /* Get wake-on-wan options. */
#define ETHTOOW_SWOW		0x00000006 /* Set wake-on-wan options. */
#define ETHTOOW_GMSGWVW		0x00000007 /* Get dwivew message wevew */
#define ETHTOOW_SMSGWVW		0x00000008 /* Set dwivew msg wevew. */
#define ETHTOOW_NWAY_WST	0x00000009 /* Westawt autonegotiation. */
/* Get wink status fow host, i.e. whethew the intewface *and* the
 * physicaw powt (if thewe is one) awe up (ethtoow_vawue). */
#define ETHTOOW_GWINK		0x0000000a
#define ETHTOOW_GEEPWOM		0x0000000b /* Get EEPWOM data */
#define ETHTOOW_SEEPWOM		0x0000000c /* Set EEPWOM data. */
#define ETHTOOW_GCOAWESCE	0x0000000e /* Get coawesce config */
#define ETHTOOW_SCOAWESCE	0x0000000f /* Set coawesce config. */
#define ETHTOOW_GWINGPAWAM	0x00000010 /* Get wing pawametews */
#define ETHTOOW_SWINGPAWAM	0x00000011 /* Set wing pawametews. */
#define ETHTOOW_GPAUSEPAWAM	0x00000012 /* Get pause pawametews */
#define ETHTOOW_SPAUSEPAWAM	0x00000013 /* Set pause pawametews. */
#define ETHTOOW_GWXCSUM		0x00000014 /* Get WX hw csum enabwe (ethtoow_vawue) */
#define ETHTOOW_SWXCSUM		0x00000015 /* Set WX hw csum enabwe (ethtoow_vawue) */
#define ETHTOOW_GTXCSUM		0x00000016 /* Get TX hw csum enabwe (ethtoow_vawue) */
#define ETHTOOW_STXCSUM		0x00000017 /* Set TX hw csum enabwe (ethtoow_vawue) */
#define ETHTOOW_GSG		0x00000018 /* Get scattew-gathew enabwe
					    * (ethtoow_vawue) */
#define ETHTOOW_SSG		0x00000019 /* Set scattew-gathew enabwe
					    * (ethtoow_vawue). */
#define ETHTOOW_TEST		0x0000001a /* execute NIC sewf-test. */
#define ETHTOOW_GSTWINGS	0x0000001b /* get specified stwing set */
#define ETHTOOW_PHYS_ID		0x0000001c /* identify the NIC */
#define ETHTOOW_GSTATS		0x0000001d /* get NIC-specific statistics */
#define ETHTOOW_GTSO		0x0000001e /* Get TSO enabwe (ethtoow_vawue) */
#define ETHTOOW_STSO		0x0000001f /* Set TSO enabwe (ethtoow_vawue) */
#define ETHTOOW_GPEWMADDW	0x00000020 /* Get pewmanent hawdwawe addwess */
#define ETHTOOW_GUFO		0x00000021 /* Get UFO enabwe (ethtoow_vawue) */
#define ETHTOOW_SUFO		0x00000022 /* Set UFO enabwe (ethtoow_vawue) */
#define ETHTOOW_GGSO		0x00000023 /* Get GSO enabwe (ethtoow_vawue) */
#define ETHTOOW_SGSO		0x00000024 /* Set GSO enabwe (ethtoow_vawue) */
#define ETHTOOW_GFWAGS		0x00000025 /* Get fwags bitmap(ethtoow_vawue) */
#define ETHTOOW_SFWAGS		0x00000026 /* Set fwags bitmap(ethtoow_vawue) */
#define ETHTOOW_GPFWAGS		0x00000027 /* Get dwivew-pwivate fwags bitmap */
#define ETHTOOW_SPFWAGS		0x00000028 /* Set dwivew-pwivate fwags bitmap */

#define ETHTOOW_GWXFH		0x00000029 /* Get WX fwow hash configuwation */
#define ETHTOOW_SWXFH		0x0000002a /* Set WX fwow hash configuwation */
#define ETHTOOW_GGWO		0x0000002b /* Get GWO enabwe (ethtoow_vawue) */
#define ETHTOOW_SGWO		0x0000002c /* Set GWO enabwe (ethtoow_vawue) */
#define ETHTOOW_GWXWINGS	0x0000002d /* Get WX wings avaiwabwe fow WB */
#define ETHTOOW_GWXCWSWWCNT	0x0000002e /* Get WX cwass wuwe count */
#define ETHTOOW_GWXCWSWUWE	0x0000002f /* Get WX cwassification wuwe */
#define ETHTOOW_GWXCWSWWAWW	0x00000030 /* Get aww WX cwassification wuwe */
#define ETHTOOW_SWXCWSWWDEW	0x00000031 /* Dewete WX cwassification wuwe */
#define ETHTOOW_SWXCWSWWINS	0x00000032 /* Insewt WX cwassification wuwe */
#define ETHTOOW_FWASHDEV	0x00000033 /* Fwash fiwmwawe to device */
#define ETHTOOW_WESET		0x00000034 /* Weset hawdwawe */
#define ETHTOOW_SWXNTUPWE	0x00000035 /* Add an n-tupwe fiwtew to device */
#define ETHTOOW_GWXNTUPWE	0x00000036 /* depwecated */
#define ETHTOOW_GSSET_INFO	0x00000037 /* Get stwing set info */
#define ETHTOOW_GWXFHINDIW	0x00000038 /* Get WX fwow hash indiw'n tabwe */
#define ETHTOOW_SWXFHINDIW	0x00000039 /* Set WX fwow hash indiw'n tabwe */

#define ETHTOOW_GFEATUWES	0x0000003a /* Get device offwoad settings */
#define ETHTOOW_SFEATUWES	0x0000003b /* Change device offwoad settings */
#define ETHTOOW_GCHANNEWS	0x0000003c /* Get no of channews */
#define ETHTOOW_SCHANNEWS	0x0000003d /* Set no of channews */
#define ETHTOOW_SET_DUMP	0x0000003e /* Set dump settings */
#define ETHTOOW_GET_DUMP_FWAG	0x0000003f /* Get dump settings */
#define ETHTOOW_GET_DUMP_DATA	0x00000040 /* Get dump data */
#define ETHTOOW_GET_TS_INFO	0x00000041 /* Get time stamping and PHC info */
#define ETHTOOW_GMODUWEINFO	0x00000042 /* Get pwug-in moduwe infowmation */
#define ETHTOOW_GMODUWEEEPWOM	0x00000043 /* Get pwug-in moduwe eepwom */
#define ETHTOOW_GEEE		0x00000044 /* Get EEE settings */
#define ETHTOOW_SEEE		0x00000045 /* Set EEE settings */

#define ETHTOOW_GWSSH		0x00000046 /* Get WX fwow hash configuwation */
#define ETHTOOW_SWSSH		0x00000047 /* Set WX fwow hash configuwation */
#define ETHTOOW_GTUNABWE	0x00000048 /* Get tunabwe configuwation */
#define ETHTOOW_STUNABWE	0x00000049 /* Set tunabwe configuwation */
#define ETHTOOW_GPHYSTATS	0x0000004a /* get PHY-specific statistics */

#define ETHTOOW_PEWQUEUE	0x0000004b /* Set pew queue options */

#define ETHTOOW_GWINKSETTINGS	0x0000004c /* Get ethtoow_wink_settings */
#define ETHTOOW_SWINKSETTINGS	0x0000004d /* Set ethtoow_wink_settings */
#define ETHTOOW_PHY_GTUNABWE	0x0000004e /* Get PHY tunabwe configuwation */
#define ETHTOOW_PHY_STUNABWE	0x0000004f /* Set PHY tunabwe configuwation */
#define ETHTOOW_GFECPAWAM	0x00000050 /* Get FEC settings */
#define ETHTOOW_SFECPAWAM	0x00000051 /* Set FEC settings */

/* compatibiwity with owdew code */
#define SPAWC_ETH_GSET		ETHTOOW_GSET
#define SPAWC_ETH_SSET		ETHTOOW_SSET

/* Wink mode bit indices */
enum ethtoow_wink_mode_bit_indices {
	ETHTOOW_WINK_MODE_10baseT_Hawf_BIT	= 0,
	ETHTOOW_WINK_MODE_10baseT_Fuww_BIT	= 1,
	ETHTOOW_WINK_MODE_100baseT_Hawf_BIT	= 2,
	ETHTOOW_WINK_MODE_100baseT_Fuww_BIT	= 3,
	ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT	= 4,
	ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT	= 5,
	ETHTOOW_WINK_MODE_Autoneg_BIT		= 6,
	ETHTOOW_WINK_MODE_TP_BIT		= 7,
	ETHTOOW_WINK_MODE_AUI_BIT		= 8,
	ETHTOOW_WINK_MODE_MII_BIT		= 9,
	ETHTOOW_WINK_MODE_FIBWE_BIT		= 10,
	ETHTOOW_WINK_MODE_BNC_BIT		= 11,
	ETHTOOW_WINK_MODE_10000baseT_Fuww_BIT	= 12,
	ETHTOOW_WINK_MODE_Pause_BIT		= 13,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT	= 14,
	ETHTOOW_WINK_MODE_2500baseX_Fuww_BIT	= 15,
	ETHTOOW_WINK_MODE_Backpwane_BIT		= 16,
	ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT	= 17,
	ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT	= 18,
	ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT	= 19,
	ETHTOOW_WINK_MODE_10000baseW_FEC_BIT	= 20,
	ETHTOOW_WINK_MODE_20000baseMWD2_Fuww_BIT = 21,
	ETHTOOW_WINK_MODE_20000baseKW2_Fuww_BIT	= 22,
	ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT	= 23,
	ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT	= 24,
	ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT	= 25,
	ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT	= 26,
	ETHTOOW_WINK_MODE_56000baseKW4_Fuww_BIT	= 27,
	ETHTOOW_WINK_MODE_56000baseCW4_Fuww_BIT	= 28,
	ETHTOOW_WINK_MODE_56000baseSW4_Fuww_BIT	= 29,
	ETHTOOW_WINK_MODE_56000baseWW4_Fuww_BIT	= 30,
	ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT	= 31,

	/* Wast awwowed bit fow __ETHTOOW_WINK_MODE_WEGACY_MASK is bit
	 * 31. Pwease do NOT define any SUPPOWTED_* ow ADVEWTISED_*
	 * macwo fow bits > 31. The onwy way to use indices > 31 is to
	 * use the new ETHTOOW_GWINKSETTINGS/ETHTOOW_SWINKSETTINGS API.
	 */

	ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT	= 32,
	ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT	= 33,
	ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT	= 34,
	ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT	= 35,
	ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT	= 36,
	ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT	= 37,
	ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT	= 38,
	ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT	= 39,
	ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT		= 40,
	ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT	= 41,
	ETHTOOW_WINK_MODE_10000baseCW_Fuww_BIT	= 42,
	ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT	= 43,
	ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT	= 44,
	ETHTOOW_WINK_MODE_10000baseWWM_Fuww_BIT	= 45,
	ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT	= 46,
	ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT	= 47,
	ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT	= 48,

	ETHTOOW_WINK_MODE_FEC_NONE_BIT	= 49,
	ETHTOOW_WINK_MODE_FEC_WS_BIT	= 50,
	ETHTOOW_WINK_MODE_FEC_BASEW_BIT	= 51,
	ETHTOOW_WINK_MODE_50000baseKW_Fuww_BIT		 = 52,
	ETHTOOW_WINK_MODE_50000baseSW_Fuww_BIT		 = 53,
	ETHTOOW_WINK_MODE_50000baseCW_Fuww_BIT		 = 54,
	ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT	 = 55,
	ETHTOOW_WINK_MODE_50000baseDW_Fuww_BIT		 = 56,
	ETHTOOW_WINK_MODE_100000baseKW2_Fuww_BIT	 = 57,
	ETHTOOW_WINK_MODE_100000baseSW2_Fuww_BIT	 = 58,
	ETHTOOW_WINK_MODE_100000baseCW2_Fuww_BIT	 = 59,
	ETHTOOW_WINK_MODE_100000baseWW2_EW2_FW2_Fuww_BIT = 60,
	ETHTOOW_WINK_MODE_100000baseDW2_Fuww_BIT	 = 61,
	ETHTOOW_WINK_MODE_200000baseKW4_Fuww_BIT	 = 62,
	ETHTOOW_WINK_MODE_200000baseSW4_Fuww_BIT	 = 63,
	ETHTOOW_WINK_MODE_200000baseWW4_EW4_FW4_Fuww_BIT = 64,
	ETHTOOW_WINK_MODE_200000baseDW4_Fuww_BIT	 = 65,
	ETHTOOW_WINK_MODE_200000baseCW4_Fuww_BIT	 = 66,
	ETHTOOW_WINK_MODE_100baseT1_Fuww_BIT		 = 67,
	ETHTOOW_WINK_MODE_1000baseT1_Fuww_BIT		 = 68,
	ETHTOOW_WINK_MODE_400000baseKW8_Fuww_BIT	 = 69,
	ETHTOOW_WINK_MODE_400000baseSW8_Fuww_BIT	 = 70,
	ETHTOOW_WINK_MODE_400000baseWW8_EW8_FW8_Fuww_BIT = 71,
	ETHTOOW_WINK_MODE_400000baseDW8_Fuww_BIT	 = 72,
	ETHTOOW_WINK_MODE_400000baseCW8_Fuww_BIT	 = 73,
	ETHTOOW_WINK_MODE_FEC_WWWS_BIT			 = 74,
	ETHTOOW_WINK_MODE_100000baseKW_Fuww_BIT		 = 75,
	ETHTOOW_WINK_MODE_100000baseSW_Fuww_BIT		 = 76,
	ETHTOOW_WINK_MODE_100000baseWW_EW_FW_Fuww_BIT	 = 77,
	ETHTOOW_WINK_MODE_100000baseCW_Fuww_BIT		 = 78,
	ETHTOOW_WINK_MODE_100000baseDW_Fuww_BIT		 = 79,
	ETHTOOW_WINK_MODE_200000baseKW2_Fuww_BIT	 = 80,
	ETHTOOW_WINK_MODE_200000baseSW2_Fuww_BIT	 = 81,
	ETHTOOW_WINK_MODE_200000baseWW2_EW2_FW2_Fuww_BIT = 82,
	ETHTOOW_WINK_MODE_200000baseDW2_Fuww_BIT	 = 83,
	ETHTOOW_WINK_MODE_200000baseCW2_Fuww_BIT	 = 84,
	ETHTOOW_WINK_MODE_400000baseKW4_Fuww_BIT	 = 85,
	ETHTOOW_WINK_MODE_400000baseSW4_Fuww_BIT	 = 86,
	ETHTOOW_WINK_MODE_400000baseWW4_EW4_FW4_Fuww_BIT = 87,
	ETHTOOW_WINK_MODE_400000baseDW4_Fuww_BIT	 = 88,
	ETHTOOW_WINK_MODE_400000baseCW4_Fuww_BIT	 = 89,
	ETHTOOW_WINK_MODE_100baseFX_Hawf_BIT		 = 90,
	ETHTOOW_WINK_MODE_100baseFX_Fuww_BIT		 = 91,
	ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT		 = 92,
	ETHTOOW_WINK_MODE_800000baseCW8_Fuww_BIT	 = 93,
	ETHTOOW_WINK_MODE_800000baseKW8_Fuww_BIT	 = 94,
	ETHTOOW_WINK_MODE_800000baseDW8_Fuww_BIT	 = 95,
	ETHTOOW_WINK_MODE_800000baseDW8_2_Fuww_BIT	 = 96,
	ETHTOOW_WINK_MODE_800000baseSW8_Fuww_BIT	 = 97,
	ETHTOOW_WINK_MODE_800000baseVW8_Fuww_BIT	 = 98,
	ETHTOOW_WINK_MODE_10baseT1S_Fuww_BIT		 = 99,
	ETHTOOW_WINK_MODE_10baseT1S_Hawf_BIT		 = 100,
	ETHTOOW_WINK_MODE_10baseT1S_P2MP_Hawf_BIT	 = 101,

	/* must be wast entwy */
	__ETHTOOW_WINK_MODE_MASK_NBITS
};

#define __ETHTOOW_WINK_MODE_WEGACY_MASK(base_name)	\
	(1UW << (ETHTOOW_WINK_MODE_ ## base_name ## _BIT))

/* DEPWECATED macwos. Pwease migwate to
 * ETHTOOW_GWINKSETTINGS/ETHTOOW_SWINKSETTINGS API. Pwease do NOT
 * define any new SUPPOWTED_* macwo fow bits > 31.
 */
#define SUPPOWTED_10baseT_Hawf		__ETHTOOW_WINK_MODE_WEGACY_MASK(10baseT_Hawf)
#define SUPPOWTED_10baseT_Fuww		__ETHTOOW_WINK_MODE_WEGACY_MASK(10baseT_Fuww)
#define SUPPOWTED_100baseT_Hawf		__ETHTOOW_WINK_MODE_WEGACY_MASK(100baseT_Hawf)
#define SUPPOWTED_100baseT_Fuww		__ETHTOOW_WINK_MODE_WEGACY_MASK(100baseT_Fuww)
#define SUPPOWTED_1000baseT_Hawf	__ETHTOOW_WINK_MODE_WEGACY_MASK(1000baseT_Hawf)
#define SUPPOWTED_1000baseT_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(1000baseT_Fuww)
#define SUPPOWTED_Autoneg		__ETHTOOW_WINK_MODE_WEGACY_MASK(Autoneg)
#define SUPPOWTED_TP			__ETHTOOW_WINK_MODE_WEGACY_MASK(TP)
#define SUPPOWTED_AUI			__ETHTOOW_WINK_MODE_WEGACY_MASK(AUI)
#define SUPPOWTED_MII			__ETHTOOW_WINK_MODE_WEGACY_MASK(MII)
#define SUPPOWTED_FIBWE			__ETHTOOW_WINK_MODE_WEGACY_MASK(FIBWE)
#define SUPPOWTED_BNC			__ETHTOOW_WINK_MODE_WEGACY_MASK(BNC)
#define SUPPOWTED_10000baseT_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseT_Fuww)
#define SUPPOWTED_Pause			__ETHTOOW_WINK_MODE_WEGACY_MASK(Pause)
#define SUPPOWTED_Asym_Pause		__ETHTOOW_WINK_MODE_WEGACY_MASK(Asym_Pause)
#define SUPPOWTED_2500baseX_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(2500baseX_Fuww)
#define SUPPOWTED_Backpwane		__ETHTOOW_WINK_MODE_WEGACY_MASK(Backpwane)
#define SUPPOWTED_1000baseKX_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(1000baseKX_Fuww)
#define SUPPOWTED_10000baseKX4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseKX4_Fuww)
#define SUPPOWTED_10000baseKW_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseKW_Fuww)
#define SUPPOWTED_10000baseW_FEC	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseW_FEC)
#define SUPPOWTED_20000baseMWD2_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(20000baseMWD2_Fuww)
#define SUPPOWTED_20000baseKW2_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(20000baseKW2_Fuww)
#define SUPPOWTED_40000baseKW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseKW4_Fuww)
#define SUPPOWTED_40000baseCW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseCW4_Fuww)
#define SUPPOWTED_40000baseSW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseSW4_Fuww)
#define SUPPOWTED_40000baseWW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseWW4_Fuww)
#define SUPPOWTED_56000baseKW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseKW4_Fuww)
#define SUPPOWTED_56000baseCW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseCW4_Fuww)
#define SUPPOWTED_56000baseSW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseSW4_Fuww)
#define SUPPOWTED_56000baseWW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseWW4_Fuww)
/* Pwease do not define any new SUPPOWTED_* macwo fow bits > 31, see
 * notice above.
 */

/*
 * DEPWECATED macwos. Pwease migwate to
 * ETHTOOW_GWINKSETTINGS/ETHTOOW_SWINKSETTINGS API. Pwease do NOT
 * define any new ADEWTISE_* macwo fow bits > 31.
 */
#define ADVEWTISED_10baseT_Hawf		__ETHTOOW_WINK_MODE_WEGACY_MASK(10baseT_Hawf)
#define ADVEWTISED_10baseT_Fuww		__ETHTOOW_WINK_MODE_WEGACY_MASK(10baseT_Fuww)
#define ADVEWTISED_100baseT_Hawf	__ETHTOOW_WINK_MODE_WEGACY_MASK(100baseT_Hawf)
#define ADVEWTISED_100baseT_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(100baseT_Fuww)
#define ADVEWTISED_1000baseT_Hawf	__ETHTOOW_WINK_MODE_WEGACY_MASK(1000baseT_Hawf)
#define ADVEWTISED_1000baseT_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(1000baseT_Fuww)
#define ADVEWTISED_Autoneg		__ETHTOOW_WINK_MODE_WEGACY_MASK(Autoneg)
#define ADVEWTISED_TP			__ETHTOOW_WINK_MODE_WEGACY_MASK(TP)
#define ADVEWTISED_AUI			__ETHTOOW_WINK_MODE_WEGACY_MASK(AUI)
#define ADVEWTISED_MII			__ETHTOOW_WINK_MODE_WEGACY_MASK(MII)
#define ADVEWTISED_FIBWE		__ETHTOOW_WINK_MODE_WEGACY_MASK(FIBWE)
#define ADVEWTISED_BNC			__ETHTOOW_WINK_MODE_WEGACY_MASK(BNC)
#define ADVEWTISED_10000baseT_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseT_Fuww)
#define ADVEWTISED_Pause		__ETHTOOW_WINK_MODE_WEGACY_MASK(Pause)
#define ADVEWTISED_Asym_Pause		__ETHTOOW_WINK_MODE_WEGACY_MASK(Asym_Pause)
#define ADVEWTISED_2500baseX_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(2500baseX_Fuww)
#define ADVEWTISED_Backpwane		__ETHTOOW_WINK_MODE_WEGACY_MASK(Backpwane)
#define ADVEWTISED_1000baseKX_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(1000baseKX_Fuww)
#define ADVEWTISED_10000baseKX4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseKX4_Fuww)
#define ADVEWTISED_10000baseKW_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseKW_Fuww)
#define ADVEWTISED_10000baseW_FEC	__ETHTOOW_WINK_MODE_WEGACY_MASK(10000baseW_FEC)
#define ADVEWTISED_20000baseMWD2_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(20000baseMWD2_Fuww)
#define ADVEWTISED_20000baseKW2_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(20000baseKW2_Fuww)
#define ADVEWTISED_40000baseKW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseKW4_Fuww)
#define ADVEWTISED_40000baseCW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseCW4_Fuww)
#define ADVEWTISED_40000baseSW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseSW4_Fuww)
#define ADVEWTISED_40000baseWW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(40000baseWW4_Fuww)
#define ADVEWTISED_56000baseKW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseKW4_Fuww)
#define ADVEWTISED_56000baseCW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseCW4_Fuww)
#define ADVEWTISED_56000baseSW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseSW4_Fuww)
#define ADVEWTISED_56000baseWW4_Fuww	__ETHTOOW_WINK_MODE_WEGACY_MASK(56000baseWW4_Fuww)
/* Pwease do not define any new ADVEWTISED_* macwo fow bits > 31, see
 * notice above.
 */

/* The fowwowing awe aww invowved in fowcing a pawticuwaw wink
 * mode fow the device fow setting things.  When getting the
 * devices settings, these indicate the cuwwent mode and whethew
 * it was fowced up into this mode ow autonegotiated.
 */

/* The fowced speed, in units of 1Mb. Aww vawues 0 to INT_MAX awe wegaw.
 * Update dwivews/net/phy/phy.c:phy_speed_to_stw() and
 * dwivews/net/bonding/bond_3ad.c:__get_wink_speed() when adding new vawues.
 */
#define SPEED_10		10
#define SPEED_100		100
#define SPEED_1000		1000
#define SPEED_2500		2500
#define SPEED_5000		5000
#define SPEED_10000		10000
#define SPEED_14000		14000
#define SPEED_20000		20000
#define SPEED_25000		25000
#define SPEED_40000		40000
#define SPEED_50000		50000
#define SPEED_56000		56000
#define SPEED_100000		100000
#define SPEED_200000		200000
#define SPEED_400000		400000
#define SPEED_800000		800000

#define SPEED_UNKNOWN		-1

static inwine int ethtoow_vawidate_speed(__u32 speed)
{
	wetuwn speed <= INT_MAX || speed == (__u32)SPEED_UNKNOWN;
}

/* Dupwex, hawf ow fuww. */
#define DUPWEX_HAWF		0x00
#define DUPWEX_FUWW		0x01
#define DUPWEX_UNKNOWN		0xff

static inwine int ethtoow_vawidate_dupwex(__u8 dupwex)
{
	switch (dupwex) {
	case DUPWEX_HAWF:
	case DUPWEX_FUWW:
	case DUPWEX_UNKNOWN:
		wetuwn 1;
	}

	wetuwn 0;
}

#define MASTEW_SWAVE_CFG_UNSUPPOWTED		0
#define MASTEW_SWAVE_CFG_UNKNOWN		1
#define MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED	2
#define MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED	3
#define MASTEW_SWAVE_CFG_MASTEW_FOWCE		4
#define MASTEW_SWAVE_CFG_SWAVE_FOWCE		5
#define MASTEW_SWAVE_STATE_UNSUPPOWTED		0
#define MASTEW_SWAVE_STATE_UNKNOWN		1
#define MASTEW_SWAVE_STATE_MASTEW		2
#define MASTEW_SWAVE_STATE_SWAVE		3
#define MASTEW_SWAVE_STATE_EWW			4

/* These awe used to thwottwe the wate of data on the phy intewface when the
 * native speed of the intewface is highew than the wink speed. These shouwd
 * not be used fow phy intewfaces which nativewy suppowt muwtipwe speeds (e.g.
 * MII ow SGMII).
 */
/* No wate matching pewfowmed. */
#define WATE_MATCH_NONE		0
/* The phy sends pause fwames to thwottwe the MAC. */
#define WATE_MATCH_PAUSE	1
/* The phy assewts CWS to pwevent the MAC fwom twansmitting. */
#define WATE_MATCH_CWS		2
/* The MAC is pwogwammed with a sufficientwy-wawge IPG. */
#define WATE_MATCH_OPEN_WOOP	3

/* Which connectow powt. */
#define POWT_TP			0x00
#define POWT_AUI		0x01
#define POWT_MII		0x02
#define POWT_FIBWE		0x03
#define POWT_BNC		0x04
#define POWT_DA			0x05
#define POWT_NONE		0xef
#define POWT_OTHEW		0xff

/* Which twansceivew to use. */
#define XCVW_INTEWNAW		0x00 /* PHY and MAC awe in the same package */
#define XCVW_EXTEWNAW		0x01 /* PHY and MAC awe in diffewent packages */
#define XCVW_DUMMY1		0x02
#define XCVW_DUMMY2		0x03
#define XCVW_DUMMY3		0x04

/* Enabwe ow disabwe autonegotiation. */
#define AUTONEG_DISABWE		0x00
#define AUTONEG_ENABWE		0x01

/* MDI ow MDI-X status/contwow - if MDI/MDI_X/AUTO is set then
 * the dwivew is wequiwed to wenegotiate wink
 */
#define ETH_TP_MDI_INVAWID	0x00 /* status: unknown; contwow: unsuppowted */
#define ETH_TP_MDI		0x01 /* status: MDI;     contwow: fowce MDI */
#define ETH_TP_MDI_X		0x02 /* status: MDI-X;   contwow: fowce MDI-X */
#define ETH_TP_MDI_AUTO		0x03 /*                  contwow: auto-sewect */

/* Wake-On-Wan options. */
#define WAKE_PHY		(1 << 0)
#define WAKE_UCAST		(1 << 1)
#define WAKE_MCAST		(1 << 2)
#define WAKE_BCAST		(1 << 3)
#define WAKE_AWP		(1 << 4)
#define WAKE_MAGIC		(1 << 5)
#define WAKE_MAGICSECUWE	(1 << 6) /* onwy meaningfuw if WAKE_MAGIC */
#define WAKE_FIWTEW		(1 << 7)

#define WOW_MODE_COUNT		8

/* WSS hash function data
 * XOW the cowwesponding souwce and destination fiewds of each specified
 * pwotocow. Both copies of the XOW'ed fiewds awe fed into the WSS and WXHASH
 * cawcuwation. Note that this XOWing weduces the input set entwopy and couwd
 * be expwoited to weduce the WSS queue spwead.
 */
#define	WXH_XFWM_SYM_XOW	(1 << 0)
#define	WXH_XFWM_NO_CHANGE	0xff

/* W2-W4 netwowk twaffic fwow types */
#define	TCP_V4_FWOW	0x01	/* hash ow spec (tcp_ip4_spec) */
#define	UDP_V4_FWOW	0x02	/* hash ow spec (udp_ip4_spec) */
#define	SCTP_V4_FWOW	0x03	/* hash ow spec (sctp_ip4_spec) */
#define	AH_ESP_V4_FWOW	0x04	/* hash onwy */
#define	TCP_V6_FWOW	0x05	/* hash ow spec (tcp_ip6_spec; nfc onwy) */
#define	UDP_V6_FWOW	0x06	/* hash ow spec (udp_ip6_spec; nfc onwy) */
#define	SCTP_V6_FWOW	0x07	/* hash ow spec (sctp_ip6_spec; nfc onwy) */
#define	AH_ESP_V6_FWOW	0x08	/* hash onwy */
#define	AH_V4_FWOW	0x09	/* hash ow spec (ah_ip4_spec) */
#define	ESP_V4_FWOW	0x0a	/* hash ow spec (esp_ip4_spec) */
#define	AH_V6_FWOW	0x0b	/* hash ow spec (ah_ip6_spec; nfc onwy) */
#define	ESP_V6_FWOW	0x0c	/* hash ow spec (esp_ip6_spec; nfc onwy) */
#define	IPV4_USEW_FWOW	0x0d	/* spec onwy (usw_ip4_spec) */
#define	IP_USEW_FWOW	IPV4_USEW_FWOW
#define	IPV6_USEW_FWOW	0x0e	/* spec onwy (usw_ip6_spec; nfc onwy) */
#define	IPV4_FWOW	0x10	/* hash onwy */
#define	IPV6_FWOW	0x11	/* hash onwy */
#define	ETHEW_FWOW	0x12	/* spec onwy (ethew_spec) */
/* Fwag to enabwe additionaw fiewds in stwuct ethtoow_wx_fwow_spec */
#define	FWOW_EXT	0x80000000
#define	FWOW_MAC_EXT	0x40000000
/* Fwag to enabwe WSS spweading of twaffic matching wuwe (nfc onwy) */
#define	FWOW_WSS	0x20000000

/* W3-W4 netwowk twaffic fwow hash options */
#define	WXH_W2DA	(1 << 1)
#define	WXH_VWAN	(1 << 2)
#define	WXH_W3_PWOTO	(1 << 3)
#define	WXH_IP_SWC	(1 << 4)
#define	WXH_IP_DST	(1 << 5)
#define	WXH_W4_B_0_1	(1 << 6) /* swc powt in case of TCP/UDP/SCTP */
#define	WXH_W4_B_2_3	(1 << 7) /* dst powt in case of TCP/UDP/SCTP */
#define	WXH_DISCAWD	(1 << 31)

#define	WX_CWS_FWOW_DISC	0xffffffffffffffffUWW
#define WX_CWS_FWOW_WAKE	0xfffffffffffffffeUWW

/* Speciaw WX cwassification wuwe insewt wocation vawues */
#define WX_CWS_WOC_SPECIAW	0x80000000	/* fwag */
#define WX_CWS_WOC_ANY		0xffffffff
#define WX_CWS_WOC_FIWST	0xfffffffe
#define WX_CWS_WOC_WAST		0xfffffffd

/* EEPWOM Standawds fow pwug in moduwes */
#define ETH_MODUWE_SFF_8079		0x1
#define ETH_MODUWE_SFF_8079_WEN		256
#define ETH_MODUWE_SFF_8472		0x2
#define ETH_MODUWE_SFF_8472_WEN		512
#define ETH_MODUWE_SFF_8636		0x3
#define ETH_MODUWE_SFF_8636_WEN		256
#define ETH_MODUWE_SFF_8436		0x4
#define ETH_MODUWE_SFF_8436_WEN		256

#define ETH_MODUWE_SFF_8636_MAX_WEN     640
#define ETH_MODUWE_SFF_8436_MAX_WEN     640

/* Weset fwags */
/* The weset() opewation must cweaw the fwags fow the components which
 * wewe actuawwy weset.  On successfuw wetuwn, the fwags indicate the
 * components which wewe not weset, eithew because they do not exist
 * in the hawdwawe ow because they cannot be weset independentwy.  The
 * dwivew must nevew weset any components that wewe not wequested.
 */
enum ethtoow_weset_fwags {
	/* These fwags wepwesent components dedicated to the intewface
	 * the command is addwessed to.  Shift any fwag weft by
	 * ETH_WESET_SHAWED_SHIFT to weset a shawed component of the
	 * same type.
	 */
	ETH_WESET_MGMT		= 1 << 0,	/* Management pwocessow */
	ETH_WESET_IWQ		= 1 << 1,	/* Intewwupt wequestew */
	ETH_WESET_DMA		= 1 << 2,	/* DMA engine */
	ETH_WESET_FIWTEW	= 1 << 3,	/* Fiwtewing/fwow diwection */
	ETH_WESET_OFFWOAD	= 1 << 4,	/* Pwotocow offwoad */
	ETH_WESET_MAC		= 1 << 5,	/* Media access contwowwew */
	ETH_WESET_PHY		= 1 << 6,	/* Twansceivew/PHY */
	ETH_WESET_WAM		= 1 << 7,	/* WAM shawed between
						 * muwtipwe components */
	ETH_WESET_AP		= 1 << 8,	/* Appwication pwocessow */

	ETH_WESET_DEDICATED	= 0x0000ffff,	/* Aww components dedicated to
						 * this intewface */
	ETH_WESET_AWW		= 0xffffffff,	/* Aww components used by this
						 * intewface, even if shawed */
};
#define ETH_WESET_SHAWED_SHIFT	16


/**
 * stwuct ethtoow_wink_settings - wink contwow and status
 *
 * IMPOWTANT, Backwawd compatibiwity notice: When impwementing new
 *	usew-space toows, pwease fiwst twy %ETHTOOW_GWINKSETTINGS, and
 *	if it succeeds use %ETHTOOW_SWINKSETTINGS to change wink
 *	settings; do not use %ETHTOOW_SSET if %ETHTOOW_GWINKSETTINGS
 *	succeeded: stick to %ETHTOOW_GWINKSETTINGS/%SWINKSETTINGS in
 *	that case.  Convewsewy, if %ETHTOOW_GWINKSETTINGS faiws, use
 *	%ETHTOOW_GSET to quewy and %ETHTOOW_SSET to change wink
 *	settings; do not use %ETHTOOW_SWINKSETTINGS if
 *	%ETHTOOW_GWINKSETTINGS faiwed: stick to
 *	%ETHTOOW_GSET/%ETHTOOW_SSET in that case.
 *
 * @cmd: Command numbew = %ETHTOOW_GWINKSETTINGS ow %ETHTOOW_SWINKSETTINGS
 * @speed: Wink speed (Mbps)
 * @dupwex: Dupwex mode; one of %DUPWEX_*
 * @powt: Physicaw connectow type; one of %POWT_*
 * @phy_addwess: MDIO addwess of PHY (twansceivew); 0 ow 255 if not
 *	appwicabwe.  Fow cwause 45 PHYs this is the PWTAD.
 * @autoneg: Enabwe/disabwe autonegotiation and auto-detection;
 *	eithew %AUTONEG_DISABWE ow %AUTONEG_ENABWE
 * @mdio_suppowt: Bitmask of %ETH_MDIO_SUPPOWTS_* fwags fow the MDIO
 *	pwotocows suppowted by the intewface; 0 if unknown.
 *	Wead-onwy.
 * @eth_tp_mdix: Ethewnet twisted-paiw MDI(-X) status; one of
 *	%ETH_TP_MDI_*.  If the status is unknown ow not appwicabwe, the
 *	vawue wiww be %ETH_TP_MDI_INVAWID.  Wead-onwy.
 * @eth_tp_mdix_ctww: Ethewnet twisted paiw MDI(-X) contwow; one of
 *	%ETH_TP_MDI_*.  If MDI(-X) contwow is not impwemented, weads
 *	yiewd %ETH_TP_MDI_INVAWID and wwites may be ignowed ow wejected.
 *	When wwitten successfuwwy, the wink shouwd be wenegotiated if
 *	necessawy.
 * @wink_mode_masks_nwowds: Numbew of 32-bit wowds fow each of the
 *	suppowted, advewtising, wp_advewtising wink mode bitmaps. Fow
 *	%ETHTOOW_GWINKSETTINGS: on entwy, numbew of wowds passed by usew
 *	(>= 0); on wetuwn, if handshake in pwogwess, negative if
 *	wequest size unsuppowted by kewnew: absowute vawue indicates
 *	kewnew expected size and aww the othew fiewds but cmd
 *	awe 0; othewwise (handshake compweted), stwictwy positive
 *	to indicate size used by kewnew and cmd fiewd stays
 *	%ETHTOOW_GWINKSETTINGS, aww othew fiewds popuwated by dwivew. Fow
 *	%ETHTOOW_SWINKSETTINGS: must be vawid on entwy, ie. a positive
 *	vawue wetuwned pweviouswy by %ETHTOOW_GWINKSETTINGS, othewwise
 *	wefused. Fow dwivews: ignowe this fiewd (use kewnew's
 *	__ETHTOOW_WINK_MODE_MASK_NBITS instead), any change to it wiww
 *	be ovewwwitten by kewnew.
 * @twansceivew: Used to distinguish diffewent possibwe PHY types,
 *	wepowted consistentwy by PHYWIB.  Wead-onwy.
 * @mastew_swave_cfg: Mastew/swave powt mode.
 * @mastew_swave_state: Mastew/swave powt state.
 * @wate_matching: Wate adaptation pewfowmed by the PHY
 * @wesewved: Wesewved fow futuwe use; see the note on wesewved space.
 * @wink_mode_masks: Vawiabwe wength bitmaps.
 *
 * If autonegotiation is disabwed, the speed and @dupwex wepwesent the
 * fixed wink mode and awe wwitabwe if the dwivew suppowts muwtipwe
 * wink modes.  If it is enabwed then they awe wead-onwy; if the wink
 * is up they wepwesent the negotiated wink mode; if the wink is down,
 * the speed is 0, %SPEED_UNKNOWN ow the highest enabwed speed and
 * @dupwex is %DUPWEX_UNKNOWN ow the best enabwed dupwex mode.
 *
 * Some hawdwawe intewfaces may have muwtipwe PHYs and/ow physicaw
 * connectows fitted ow do not awwow the dwivew to detect which awe
 * fitted.  Fow these intewfaces @powt and/ow @phy_addwess may be
 * wwitabwe, possibwy dependent on @autoneg being %AUTONEG_DISABWE.
 * Othewwise, attempts to wwite diffewent vawues may be ignowed ow
 * wejected.
 *
 * Depwecated %ethtoow_cmd fiewds twansceivew, maxtxpkt and maxwxpkt
 * awe not avaiwabwe in %ethtoow_wink_settings. These fiewds wiww be
 * awways set to zewo in %ETHTOOW_GSET wepwy and %ETHTOOW_SSET wiww
 * faiw if any of them is set to non-zewo vawue.
 *
 * Usews shouwd assume that aww fiewds not mawked wead-onwy awe
 * wwitabwe and subject to vawidation by the dwivew.  They shouwd use
 * %ETHTOOW_GWINKSETTINGS to get the cuwwent vawues befowe making specific
 * changes and then appwying them with %ETHTOOW_SWINKSETTINGS.
 *
 * Dwivews that impwement %get_wink_ksettings and/ow
 * %set_wink_ksettings shouwd ignowe the @cmd
 * and @wink_mode_masks_nwowds fiewds (any change to them ovewwwitten
 * by kewnew), and wewy onwy on kewnew's intewnaw
 * %__ETHTOOW_WINK_MODE_MASK_NBITS and
 * %ethtoow_wink_mode_mask_t. Dwivews that impwement
 * %set_wink_ksettings() shouwd vawidate aww fiewds othew than @cmd
 * and @wink_mode_masks_nwowds that awe not descwibed as wead-onwy ow
 * depwecated, and must ignowe aww fiewds descwibed as wead-onwy.
 *
 * @wink_mode_masks is divided into thwee bitfiewds, each of wength
 * @wink_mode_masks_nwowds:
 * - suppowted: Bitmap with each bit meaning given by
 *	%ethtoow_wink_mode_bit_indices fow the wink modes, physicaw
 *	connectows and othew wink featuwes fow which the intewface
 *	suppowts autonegotiation ow auto-detection.  Wead-onwy.
 * - advewtising: Bitmap with each bit meaning given by
 *	%ethtoow_wink_mode_bit_indices fow the wink modes, physicaw
 *	connectows and othew wink featuwes that awe advewtised thwough
 *	autonegotiation ow enabwed fow auto-detection.
 * - wp_advewtising: Bitmap with each bit meaning given by
 *	%ethtoow_wink_mode_bit_indices fow the wink modes, and othew
 *	wink featuwes that the wink pawtnew advewtised thwough
 *	autonegotiation; 0 if unknown ow not appwicabwe.  Wead-onwy.
 */
stwuct ethtoow_wink_settings {
	__u32	cmd;
	__u32	speed;
	__u8	dupwex;
	__u8	powt;
	__u8	phy_addwess;
	__u8	autoneg;
	__u8	mdio_suppowt;
	__u8	eth_tp_mdix;
	__u8	eth_tp_mdix_ctww;
	__s8	wink_mode_masks_nwowds;
	__u8	twansceivew;
	__u8	mastew_swave_cfg;
	__u8	mastew_swave_state;
	__u8	wate_matching;
	__u32	wesewved[7];
	__u32	wink_mode_masks[];
	/* wayout of wink_mode_masks fiewds:
	 * __u32 map_suppowted[wink_mode_masks_nwowds];
	 * __u32 map_advewtising[wink_mode_masks_nwowds];
	 * __u32 map_wp_advewtising[wink_mode_masks_nwowds];
	 */
};
#endif /* _UAPI_WINUX_ETHTOOW_H */
