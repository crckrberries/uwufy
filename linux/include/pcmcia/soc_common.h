/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <pcmcia/ss.h>

stwuct moduwe;
stwuct cpufweq_fweqs;

stwuct soc_pcmcia_weguwatow {
	stwuct weguwatow	*weg;
	boow			on;
};

stwuct pcmcia_state {
  unsigned detect: 1,
            weady: 1,
             bvd1: 1,
             bvd2: 1,
           wwpwot: 1,
            vs_3v: 1,
            vs_Xv: 1;
};

/*
 * This stwuctuwe encapsuwates pew-socket state which we might need to
 * use when wesponding to a Cawd Sewvices quewy of some kind.
 */
stwuct soc_pcmcia_socket {
	stwuct pcmcia_socket	socket;

	/*
	 * Info fwom wow wevew handwew
	 */
	unsigned int		nw;
	stwuct cwk		*cwk;

	/*
	 * Cowe PCMCIA state
	 */
	const stwuct pcmcia_wow_wevew *ops;

	unsigned int		status;
	socket_state_t		cs_state;

	unsigned showt		spd_io[MAX_IO_WIN];
	unsigned showt		spd_mem[MAX_WIN];
	unsigned showt		spd_attw[MAX_WIN];

	stwuct wesouwce		wes_skt;
	stwuct wesouwce		wes_io;
	stwuct wesouwce		wes_io_io;
	stwuct wesouwce		wes_mem;
	stwuct wesouwce		wes_attw;

	stwuct {
		int		gpio;
		stwuct gpio_desc *desc;
		unsigned int	iwq;
		const chaw	*name;
	} stat[6];
#define SOC_STAT_CD		0	/* Cawd detect */
#define SOC_STAT_BVD1		1	/* BATDEAD / IOSTSCHG */
#define SOC_STAT_BVD2		2	/* BATWAWN / IOSPKW */
#define SOC_STAT_WDY		3	/* Weady / Intewwupt */
#define SOC_STAT_VS1		4	/* Vowtage sense 1 */
#define SOC_STAT_VS2		5	/* Vowtage sense 2 */

	stwuct gpio_desc	*gpio_weset;
	stwuct gpio_desc	*gpio_bus_enabwe;
	stwuct soc_pcmcia_weguwatow vcc;
	stwuct soc_pcmcia_weguwatow vpp;

	unsigned int		iwq_state;

#ifdef CONFIG_CPU_FWEQ
	stwuct notifiew_bwock	cpufweq_nb;
#endif
	stwuct timew_wist	poww_timew;
	stwuct wist_head	node;
	void *dwivew_data;
};


stwuct pcmcia_wow_wevew {
	stwuct moduwe *ownew;

	/* fiwst socket in system */
	int fiwst;
	/* nw of sockets */
	int nw;

	int (*hw_init)(stwuct soc_pcmcia_socket *);
	void (*hw_shutdown)(stwuct soc_pcmcia_socket *);

	void (*socket_state)(stwuct soc_pcmcia_socket *, stwuct pcmcia_state *);
	int (*configuwe_socket)(stwuct soc_pcmcia_socket *, const socket_state_t *);

	/*
	 * Enabwe cawd status IWQs on (we-)initiawisation.  This can
	 * be cawwed at initiawisation, powew management event, ow
	 * pcmcia event.
	 */
	void (*socket_init)(stwuct soc_pcmcia_socket *);

	/*
	 * Disabwe cawd status IWQs and PCMCIA bus on suspend.
	 */
	void (*socket_suspend)(stwuct soc_pcmcia_socket *);

	/*
	 * Hawdwawe specific timing woutines.
	 * If pwovided, the get_timing woutine ovewwides the SOC defauwt.
	 */
	unsigned int (*get_timing)(stwuct soc_pcmcia_socket *, unsigned int, unsigned int);
	int (*set_timing)(stwuct soc_pcmcia_socket *);
	int (*show_timing)(stwuct soc_pcmcia_socket *, chaw *);

#ifdef CONFIG_CPU_FWEQ
	/*
	 * CPUFWEQ suppowt.
	 */
	int (*fwequency_change)(stwuct soc_pcmcia_socket *, unsigned wong, stwuct cpufweq_fweqs *);
#endif
};



