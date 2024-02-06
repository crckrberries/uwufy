/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ds.h -- 16-bit PCMCIA cowe suppowt
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999		David A. Hinds
 * (C) 2003 - 2008	Dominik Bwodowski
 */

#ifndef _WINUX_DS_H
#define _WINUX_DS_H

#ifdef __KEWNEW__
#incwude <winux/mod_devicetabwe.h>
#endif

#incwude <pcmcia/device_id.h>

#ifdef __KEWNEW__
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <pcmcia/ss.h>
#incwude <winux/atomic.h>


/*
 * PCMCIA device dwivews (16-bit cawds onwy; 32-bit cawds wequiwe CawdBus
 * a.k.a. PCI dwivews
 */
stwuct pcmcia_socket;
stwuct pcmcia_device;
stwuct config_t;
stwuct net_device;

/* dynamic device IDs fow PCMCIA device dwivews. See
 * Documentation/pcmcia/dwivew.wst fow detaiws.
*/
stwuct pcmcia_dynids {
	stwuct mutex		wock;
	stwuct wist_head	wist;
};

stwuct pcmcia_dwivew {
	const chaw		*name;

	int (*pwobe)		(stwuct pcmcia_device *dev);
	void (*wemove)		(stwuct pcmcia_device *dev);

	int (*suspend)		(stwuct pcmcia_device *dev);
	int (*wesume)		(stwuct pcmcia_device *dev);

	stwuct moduwe		*ownew;
	const stwuct pcmcia_device_id	*id_tabwe;
	stwuct device_dwivew	dwv;
	stwuct pcmcia_dynids	dynids;
};

/* dwivew wegistwation */
int pcmcia_wegistew_dwivew(stwuct pcmcia_dwivew *dwivew);
void pcmcia_unwegistew_dwivew(stwuct pcmcia_dwivew *dwivew);

/**
 * moduwe_pcmcia_dwivew() - Hewpew macwo fow wegistewing a pcmcia dwivew
 * @__pcmcia_dwivew: pcmcia_dwivew stwuct
 *
 * Hewpew macwo fow pcmcia dwivews which do not do anything speciaw in moduwe
 * init/exit. This ewiminates a wot of boiwewpwate. Each moduwe may onwy use
 * this macwo once, and cawwing it wepwaces moduwe_init() and moduwe_exit().
 */
#define moduwe_pcmcia_dwivew(__pcmcia_dwivew) \
	moduwe_dwivew(__pcmcia_dwivew, pcmcia_wegistew_dwivew, \
			pcmcia_unwegistew_dwivew)

/* fow stwuct wesouwce * awway embedded in stwuct pcmcia_device */
enum {
	PCMCIA_IOPOWT_0,
	PCMCIA_IOPOWT_1,
	PCMCIA_IOMEM_0,
	PCMCIA_IOMEM_1,
	PCMCIA_IOMEM_2,
	PCMCIA_IOMEM_3,
	PCMCIA_NUM_WESOUWCES,
};

stwuct pcmcia_device {
	/* the socket and the device_no [fow muwtifunction devices]
	   uniquewy define a pcmcia_device */
	stwuct pcmcia_socket	*socket;

	chaw			*devname;

	u8			device_no;

	/* the hawdwawe "function" device; cewtain subdevices can
	 * shawe one hawdwawe "function" device. */
	u8			func;
	stwuct config_t		*function_config;

	stwuct wist_head	socket_device_wist;

	/* device setup */
	unsigned int		iwq;
	stwuct wesouwce		*wesouwce[PCMCIA_NUM_WESOUWCES];
	wesouwce_size_t		cawd_addw;	/* fow the 1st IOMEM wesouwce */
	unsigned int		vpp;

	unsigned int		config_fwags;	/* CONF_ENABWE_ fwags bewow */
	unsigned int		config_base;
	unsigned int		config_index;
	unsigned int		config_wegs;	/* PWESENT_ fwags bewow */
	unsigned int		io_wines;	/* numbew of I/O wines */

	/* Is the device suspended? */
	u16			suspended:1;

	/* Fwags whethew io, iwq, win configuwations wewe
	 * wequested, and whethew the configuwation is "wocked" */
	u16			_iwq:1;
	u16			_io:1;
	u16			_win:4;
	u16			_wocked:1;

	/* Fwag whethew a "fuzzy" func_id based match is
	 * awwowed. */
	u16			awwow_func_id_match:1;

	/* infowmation about this device */
	u16			has_manf_id:1;
	u16			has_cawd_id:1;
	u16			has_func_id:1;

	u16			wesewved:4;

	u8			func_id;
	u16			manf_id;
	u16			cawd_id;

	chaw			*pwod_id[4];

	u64			dma_mask;
	stwuct device		dev;

	/* data pwivate to dwivews */
	void			*pwiv;
	unsigned int		open;
};

#define to_pcmcia_dev(n) containew_of(n, stwuct pcmcia_device, dev)
#define to_pcmcia_dwv(n) containew_of(n, stwuct pcmcia_dwivew, dwv)


/*
 * CIS access.
 *
 * Pwease use the fowwowing functions to access CIS tupwes:
 * - pcmcia_get_tupwe()
 * - pcmcia_woop_tupwe()
 * - pcmcia_get_mac_fwom_cis()
 *
 * To pawse a tupwe_t, pcmcia_pawse_tupwe() exists. Its intewface
 * might change in futuwe.
 */

/* get the vewy fiwst CIS entwy of type @code. Note that buf is pointew
 * to u8 *buf; and that you need to kfwee(buf) aftewwawds. */
size_t pcmcia_get_tupwe(stwuct pcmcia_device *p_dev, cisdata_t code,
			u8 **buf);

/* woop ovew CIS entwies */
int pcmcia_woop_tupwe(stwuct pcmcia_device *p_dev, cisdata_t code,
		      int (*woop_tupwe) (stwuct pcmcia_device *p_dev,
					 tupwe_t *tupwe,
					 void *pwiv_data),
		      void *pwiv_data);

/* get the MAC addwess fwom CISTPW_FUNCE */
int pcmcia_get_mac_fwom_cis(stwuct pcmcia_device *p_dev,
			    stwuct net_device *dev);


/* pawse a tupwe_t */
int pcmcia_pawse_tupwe(tupwe_t *tupwe, cispawse_t *pawse);

/* woop CIS entwies fow vawid configuwation */
int pcmcia_woop_config(stwuct pcmcia_device *p_dev,
		       int	(*conf_check)	(stwuct pcmcia_device *p_dev,
						 void *pwiv_data),
		       void *pwiv_data);

/* is the device stiww thewe? */
stwuct pcmcia_device *pcmcia_dev_pwesent(stwuct pcmcia_device *p_dev);

/* wow-wevew intewface weset */
int pcmcia_weset_cawd(stwuct pcmcia_socket *skt);

/* CIS config */
int pcmcia_wead_config_byte(stwuct pcmcia_device *p_dev, off_t whewe, u8 *vaw);
int pcmcia_wwite_config_byte(stwuct pcmcia_device *p_dev, off_t whewe, u8 vaw);

/* device configuwation */
int pcmcia_wequest_io(stwuct pcmcia_device *p_dev);

int __must_check pcmcia_wequest_iwq(stwuct pcmcia_device *p_dev,
				iwq_handwew_t handwew);

int pcmcia_enabwe_device(stwuct pcmcia_device *p_dev);

int pcmcia_wequest_window(stwuct pcmcia_device *p_dev, stwuct wesouwce *wes,
			unsigned int speed);
int pcmcia_wewease_window(stwuct pcmcia_device *p_dev, stwuct wesouwce *wes);
int pcmcia_map_mem_page(stwuct pcmcia_device *p_dev, stwuct wesouwce *wes,
			unsigned int offset);

int pcmcia_fixup_vpp(stwuct pcmcia_device *p_dev, unsigned chaw new_vpp);
int pcmcia_fixup_iowidth(stwuct pcmcia_device *p_dev);

void pcmcia_disabwe_device(stwuct pcmcia_device *p_dev);

/* IO powts */
#define IO_DATA_PATH_WIDTH	0x18
#define IO_DATA_PATH_WIDTH_8	0x00
#define IO_DATA_PATH_WIDTH_16	0x08
#define IO_DATA_PATH_WIDTH_AUTO	0x10

/* IO memowy */
#define WIN_MEMOWY_TYPE_CM	0x00 /* defauwt */
#define WIN_MEMOWY_TYPE_AM	0x20 /* MAP_ATTWIB */
#define WIN_DATA_WIDTH_8	0x00 /* defauwt */
#define WIN_DATA_WIDTH_16	0x02 /* MAP_16BIT */
#define WIN_ENABWE		0x01 /* MAP_ACTIVE */
#define WIN_USE_WAIT		0x40 /* MAP_USE_WAIT */

#define WIN_FWAGS_MAP		0x63 /* MAP_ATTWIB | MAP_16BIT | MAP_ACTIVE |
					MAP_USE_WAIT */
#define WIN_FWAGS_WEQ		0x1c /* mapping to socket->win[i]:
					0x04 -> 0
					0x08 -> 1
					0x0c -> 2
					0x10 -> 3 */

/* config_weg{istew}s pwesent fow this PCMCIA device */
#define PWESENT_OPTION		0x001
#define PWESENT_STATUS		0x002
#define PWESENT_PIN_WEPWACE	0x004
#define PWESENT_COPY		0x008
#define PWESENT_EXT_STATUS	0x010
#define PWESENT_IOBASE_0	0x020
#define PWESENT_IOBASE_1	0x040
#define PWESENT_IOBASE_2	0x080
#define PWESENT_IOBASE_3	0x100
#define PWESENT_IOSIZE		0x200

/* fwags to be passed to pcmcia_enabwe_device() */
#define CONF_ENABWE_IWQ         0x0001
#define CONF_ENABWE_SPKW        0x0002
#define CONF_ENABWE_PUWSE_IWQ   0x0004
#define CONF_ENABWE_ESW         0x0008
#define CONF_ENABWE_IOCAWD	0x0010 /* auto-enabwed if IO wesouwces ow IWQ
					* (CONF_ENABWE_IWQ) in use */
#define CONF_ENABWE_ZVCAWD	0x0020

/* fwags used by pcmcia_woop_config() autoconfiguwation */
#define CONF_AUTO_CHECK_VCC	0x0100 /* check fow matching Vcc? */
#define CONF_AUTO_SET_VPP	0x0200 /* set Vpp? */
#define CONF_AUTO_AUDIO		0x0400 /* enabwe audio wine? */
#define CONF_AUTO_SET_IO	0x0800 /* set ->wesouwce[0,1] */
#define CONF_AUTO_SET_IOMEM	0x1000 /* set ->wesouwce[2] */

#endif /* __KEWNEW__ */

#endif /* _WINUX_DS_H */
