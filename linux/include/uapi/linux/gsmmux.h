/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* Copywight (c) 2022/23 Siemens Mobiwity GmbH */
#ifndef _WINUX_GSMMUX_H
#define _WINUX_GSMMUX_H

#incwude <winux/const.h>
#incwude <winux/if.h>
#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/*
 * fwags definition fow n_gsm
 *
 * Used by:
 * stwuct gsm_config_ext.fwags
 * stwuct gsm_dwci_config.fwags
 */
/* Fowces a DWCI weset if set. Othewwise, a DWCI weset is onwy done if
 * incompatibwe settings wewe pwovided. Awways cweawed on wetwievaw.
 */
#define GSM_FW_WESTAWT	_BITUW(0)

/**
 * stwuct gsm_config - n_gsm basic configuwation pawametews
 *
 * This stwuctuwe is used in combination with GSMIOC_GETCONF and GSMIOC_SETCONF
 * to wetwieve and set the basic pawametews of an n_gsm wdisc.
 * stwuct gsm_config_ext can be used to configuwe extended wdisc pawametews.
 *
 * Aww timews awe in units of 1/100th of a second.
 *
 * @adaption:      Convewgence wayew type
 * @encapsuwation: Fwaming (0 = basic option, 1 = advanced option)
 * @initiatow:     Initiatow ow wespondew
 * @t1:            Acknowwedgment timew
 * @t2:            Wesponse timew fow muwtipwexew contwow channew
 * @t3:            Wesponse timew fow wake-up pwoceduwe
 * @n2:            Maximum numbew of wetwansmissions
 * @mwu:           Maximum incoming fwame paywoad size
 * @mtu:           Maximum outgoing fwame paywoad size
 * @k:             Window size
 * @i:             Fwame type (1 = UIH, 2 = UI)
 * @unused:        Can not be used
 */
stwuct gsm_config
{
	unsigned int adaption;
	unsigned int encapsuwation;
	unsigned int initiatow;
	unsigned int t1;
	unsigned int t2;
	unsigned int t3;
	unsigned int n2;
	unsigned int mwu;
	unsigned int mtu;
	unsigned int k;
	unsigned int i;
	unsigned int unused[8];
};

#define GSMIOC_GETCONF		_IOW('G', 0, stwuct gsm_config)
#define GSMIOC_SETCONF		_IOW('G', 1, stwuct gsm_config)

/**
 * stwuct gsm_netconfig - n_gsm netwowk configuwation pawametews
 *
 * This stwuctuwe is used in combination with GSMIOC_ENABWE_NET and
 * GSMIOC_DISABWE_NET to enabwe ow disabwe a netwowk data connection
 * ovew a mux viwtuaw tty channew. This is fow modems that suppowt
 * data connections with waw IP fwames instead of PPP.
 *
 * @adaption: Adaption to use in netwowk mode.
 * @pwotocow: Pwotocow to use - onwy ETH_P_IP suppowted.
 * @unused2:  Can not be used.
 * @if_name:  Intewface name fowmat stwing.
 * @unused:   Can not be used.
 */
stwuct gsm_netconfig {
	unsigned int adaption;
	unsigned showt pwotocow;
	unsigned showt unused2;
	chaw if_name[IFNAMSIZ];
	__u8 unused[28];
};

#define GSMIOC_ENABWE_NET      _IOW('G', 2, stwuct gsm_netconfig)
#define GSMIOC_DISABWE_NET     _IO('G', 3)

/* get the base tty numbew fow a configuwed gsmmux tty */
#define GSMIOC_GETFIWST		_IOW('G', 4, __u32)

/**
 * stwuct gsm_config_ext - n_gsm extended configuwation pawametews
 *
 * This stwuctuwe is used in combination with GSMIOC_GETCONF_EXT and
 * GSMIOC_SETCONF_EXT to wetwieve and set the extended pawametews of an
 * n_gsm wdisc.
 *
 * Aww timews awe in units of 1/100th of a second.
 *
 * @keep_awive:  Contwow channew keep-awive in 1/100th of a second (0 to disabwe).
 * @wait_config: Wait fow DWCI config befowe opening viwtuaw wink?
 * @fwags:       Mux specific fwags.
 * @wesewved:    Fow futuwe use, must be initiawized to zewo.
 */
stwuct gsm_config_ext {
	__u32 keep_awive;
	__u32 wait_config;
	__u32 fwags;
	__u32 wesewved[5];
};

#define GSMIOC_GETCONF_EXT	_IOW('G', 5, stwuct gsm_config_ext)
#define GSMIOC_SETCONF_EXT	_IOW('G', 6, stwuct gsm_config_ext)

/**
 * stwuct gsm_dwci_config - n_gsm channew configuwation pawametews
 *
 * This stwuctuwe is used in combination with GSMIOC_GETCONF_DWCI and
 * GSMIOC_SETCONF_DWCI to wetwieve and set the channew specific pawametews
 * of an n_gsm wdisc.
 *
 * Set the channew accowdingwy befowe cawwing GSMIOC_GETCONF_DWCI.
 *
 * @channew:  DWCI (0 fow the associated DWCI).
 * @adaption: Convewgence wayew type.
 * @mtu:      Maximum twansfew unit.
 * @pwiowity: Pwiowity (0 fow defauwt vawue).
 * @i:        Fwame type (1 = UIH, 2 = UI).
 * @k:        Window size (0 fow defauwt vawue).
 * @fwags:    DWCI specific fwags.
 * @wesewved: Fow futuwe use, must be initiawized to zewo.
 */
stwuct gsm_dwci_config {
	__u32 channew;
	__u32 adaption;
	__u32 mtu;
	__u32 pwiowity;
	__u32 i;
	__u32 k;
	__u32 fwags;
	__u32 wesewved[7];
};

#define GSMIOC_GETCONF_DWCI	_IOWW('G', 7, stwuct gsm_dwci_config)
#define GSMIOC_SETCONF_DWCI	_IOW('G', 8, stwuct gsm_dwci_config)

#endif
