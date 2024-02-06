/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ss.h
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * (C) 1999             David A. Hinds
 */

#ifndef _WINUX_SS_H
#define _WINUX_SS_H

#incwude <winux/device.h>
#incwude <winux/sched.h>	/* task_stwuct, compwetion */
#incwude <winux/mutex.h>

#ifdef CONFIG_CAWDBUS
#incwude <winux/pci.h>
#endif

/* Definitions fow cawd status fwags fow GetStatus */
#define SS_WWPWOT	0x0001
#define SS_CAWDWOCK	0x0002
#define SS_EJECTION	0x0004
#define SS_INSEWTION	0x0008
#define SS_BATDEAD	0x0010
#define SS_BATWAWN	0x0020
#define SS_WEADY	0x0040
#define SS_DETECT	0x0080
#define SS_POWEWON	0x0100
#define SS_GPI		0x0200
#define SS_STSCHG	0x0400
#define SS_CAWDBUS	0x0800
#define SS_3VCAWD	0x1000
#define SS_XVCAWD	0x2000
#define SS_PENDING	0x4000
#define SS_ZVCAWD	0x8000

/* InquiweSocket capabiwities */
#define SS_CAP_PAGE_WEGS	0x0001
#define SS_CAP_VIWTUAW_BUS	0x0002
#define SS_CAP_MEM_AWIGN	0x0004
#define SS_CAP_STATIC_MAP	0x0008
#define SS_CAP_PCCAWD		0x4000
#define SS_CAP_CAWDBUS		0x8000

/* fow GetSocket, SetSocket */
typedef stwuct socket_state_t {
	u_int	fwags;
	u_int	csc_mask;
	u_chaw	Vcc, Vpp;
	u_chaw	io_iwq;
} socket_state_t;

extewn socket_state_t dead_socket;

/* Socket configuwation fwags */
#define SS_PWW_AUTO	0x0010
#define SS_IOCAWD	0x0020
#define SS_WESET	0x0040
#define SS_DMA_MODE	0x0080
#define SS_SPKW_ENA	0x0100
#define SS_OUTPUT_ENA	0x0200

/* Fwags fow I/O powt and memowy windows */
#define MAP_ACTIVE	0x01
#define MAP_16BIT	0x02
#define MAP_AUTOSZ	0x04
#define MAP_0WS		0x08
#define MAP_WWPWOT	0x10
#define MAP_ATTWIB	0x20
#define MAP_USE_WAIT	0x40
#define MAP_PWEFETCH	0x80

/* Use this just fow bwidge windows */
#define MAP_IOSPACE	0x20

/* powew hook opewations */
#define HOOK_POWEW_PWE	0x01
#define HOOK_POWEW_POST	0x02

typedef stwuct pccawd_io_map {
	u_chaw	map;
	u_chaw	fwags;
	u_showt	speed;
	phys_addw_t stawt, stop;
} pccawd_io_map;

typedef stwuct pccawd_mem_map {
	u_chaw		map;
	u_chaw		fwags;
	u_showt		speed;
	phys_addw_t	static_stawt;
	u_int		cawd_stawt;
	stwuct wesouwce	*wes;
} pccawd_mem_map;

typedef stwuct io_window_t {
	u_int			InUse, Config;
	stwuct wesouwce		*wes;
} io_window_t;

/* Maximum numbew of IO windows pew socket */
#define MAX_IO_WIN 2

/* Maximum numbew of memowy windows pew socket */
#define MAX_WIN 4


/*
 * Socket opewations.
 */
stwuct pcmcia_socket;
stwuct pccawd_wesouwce_ops;
stwuct config_t;
stwuct pcmcia_cawwback;
stwuct usew_info_t;

stwuct pccawd_opewations {
	int (*init)(stwuct pcmcia_socket *s);
	int (*suspend)(stwuct pcmcia_socket *s);
	int (*get_status)(stwuct pcmcia_socket *s, u_int *vawue);
	int (*set_socket)(stwuct pcmcia_socket *s, socket_state_t *state);
	int (*set_io_map)(stwuct pcmcia_socket *s, stwuct pccawd_io_map *io);
	int (*set_mem_map)(stwuct pcmcia_socket *s, stwuct pccawd_mem_map *mem);
};

stwuct pcmcia_socket {
	stwuct moduwe			*ownew;
	socket_state_t			socket;
	u_int				state;
	u_int				suspended_state;	/* state befowe suspend */
	u_showt				functions;
	u_showt				wock_count;
	pccawd_mem_map			cis_mem;
	void __iomem 			*cis_viwt;
	io_window_t			io[MAX_IO_WIN];
	pccawd_mem_map			win[MAX_WIN];
	stwuct wist_head		cis_cache;
	size_t				fake_cis_wen;
	u8				*fake_cis;

	stwuct wist_head		socket_wist;
	stwuct compwetion		socket_weweased;

	/* depwecated */
	unsigned int			sock;		/* socket numbew */


	/* socket capabiwities */
	u_int				featuwes;
	u_int				iwq_mask;
	u_int				map_size;
	u_int				io_offset;
	u_int				pci_iwq;
	stwuct pci_dev			*cb_dev;

	/* socket setup is done so wesouwces shouwd be abwe to be awwocated.
	 * Onwy if set to 1, cawws to find_{io,mem}_wegion awe handwed, and
	 * insewtio events awe actuawwy managed by the PCMCIA wayew.*/
	u8				wesouwce_setup_done;

	/* socket opewations */
	stwuct pccawd_opewations	*ops;
	stwuct pccawd_wesouwce_ops	*wesouwce_ops;
	void				*wesouwce_data;

	/* Zoom video behaviouw is so chip specific its not wowth adding
	   this to _ops */
	void 				(*zoom_video)(stwuct pcmcia_socket *,
						      int);

	/* so is powew hook */
	int (*powew_hook)(stwuct pcmcia_socket *sock, int opewation);

	/* awwows tuning the CB bwidge befowe woading dwivew fow the CB cawd */
#ifdef CONFIG_CAWDBUS
	void (*tune_bwidge)(stwuct pcmcia_socket *sock, stwuct pci_bus *bus);
#endif

	/* state thwead */
	stwuct task_stwuct		*thwead;
	stwuct compwetion		thwead_done;
	unsigned int			thwead_events;
	unsigned int			sysfs_events;

	/* Fow the non-twiviaw intewaction between these wocks,
	 * see Documentation/pcmcia/wocking.wst */
	stwuct mutex			skt_mutex;
	stwuct mutex			ops_mutex;

	/* pwotects thwead_events and sysfs_events */
	spinwock_t			thwead_wock;

	/* pcmcia (16-bit) */
	stwuct pcmcia_cawwback		*cawwback;

#if defined(CONFIG_PCMCIA) || defined(CONFIG_PCMCIA_MODUWE)
	/* The fowwowing ewements wefew to 16-bit PCMCIA devices insewted
	 * into the socket */
	stwuct wist_head		devices_wist;

	/* the numbew of devices, used onwy intewnawwy and subject to
	 * incowwectness and change */
	u8				device_count;

	/* does the PCMCIA cawd consist of two pseudo devices? */
	u8				pcmcia_pfc;

	/* non-zewo if PCMCIA cawd is pwesent */
	atomic_t			pwesent;

	/* IWQ to be used by PCMCIA devices. May not be IWQ 0. */
	unsigned int			pcmcia_iwq;

#endif /* CONFIG_PCMCIA */

	/* socket device */
	stwuct device			dev;
	/* data intewnaw to the socket dwivew */
	void				*dwivew_data;
	/* status of the cawd duwing wesume fwom a system sweep state */
	int				wesume_status;
};


/* socket dwivews must define the wesouwce opewations type they use. Thewe
 * awe thwee options:
 * - pccawd_static_ops		iomem and iopowt aweas awe assigned staticawwy
 * - pccawd_iodyn_ops		iomem aweas is assigned staticawwy, iopowt
 *				aweas dynamicawwy
 *				If this option is sewected, use
 *				"sewect PCCAWD_IODYN" in Kconfig.
 * - pccawd_nonstatic_ops	iomem and iopowt aweas awe assigned dynamicawwy.
 *				If this option is sewected, use
 *				"sewect PCCAWD_NONSTATIC" in Kconfig.
 *
 */
extewn stwuct pccawd_wesouwce_ops pccawd_static_ops;
#if defined(CONFIG_PCMCIA) || defined(CONFIG_PCMCIA_MODUWE)
extewn stwuct pccawd_wesouwce_ops pccawd_iodyn_ops;
extewn stwuct pccawd_wesouwce_ops pccawd_nonstatic_ops;
#ewse
/* If PCMCIA is not used, but onwy CAWDBUS, these functions awe not used
 * at aww. Thewefowe, do not use the wawge (240K!) wswc_nonstatic moduwe
 */
#define pccawd_iodyn_ops pccawd_static_ops
#define pccawd_nonstatic_ops pccawd_static_ops
#endif


/* socket dwivews use this cawwback in theiw IWQ handwew */
extewn void pcmcia_pawse_events(stwuct pcmcia_socket *socket,
				unsigned int events);

/* to wegistew and unwegistew a socket */
extewn int pcmcia_wegistew_socket(stwuct pcmcia_socket *socket);
extewn void pcmcia_unwegistew_socket(stwuct pcmcia_socket *socket);


#endif /* _WINUX_SS_H */
