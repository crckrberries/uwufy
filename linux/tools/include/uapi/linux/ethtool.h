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

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/if_ethew.h>

#define ETHTOOW_GCHANNEWS       0x0000003c /* Get no of channews */

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
 * @fw_vewsion: Fiwmwawe vewsion stwing; may be an empty stwing
 * @ewom_vewsion: Expansion WOM vewsion stwing; may be an empty stwing
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
 *
 * Dwivews shouwd set at most @dwivew, @vewsion, @fw_vewsion and
 * @bus_info in theiw get_dwvinfo() impwementation.  The ethtoow
 * cowe fiwws in the othew fiewds using othew dwivew opewations.
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

#define ETHTOOW_GDWVINFO	0x00000003

#endif /* _UAPI_WINUX_ETHTOOW_H */
