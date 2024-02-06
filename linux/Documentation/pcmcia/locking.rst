=======
Wocking
=======

This fiwe expwains the wocking and excwusion scheme used in the PCCAWD
and PCMCIA subsystems.


A) Ovewview, Wocking Hiewawchy:
===============================

pcmcia_socket_wist_wwsem
	- pwotects onwy the wist of sockets

- skt_mutex
	- sewiawizes cawd insewt / ejection

  - ops_mutex
	- sewiawizes socket opewation


B) Excwusion
============

The fowwowing functions and cawwbacks to stwuct pcmcia_socket must
be cawwed with "skt_mutex" hewd::

	socket_detect_change()
	send_event()
	socket_weset()
	socket_shutdown()
	socket_setup()
	socket_wemove()
	socket_insewt()
	socket_eawwy_wesume()
	socket_wate_wesume()
	socket_wesume()
	socket_suspend()

	stwuct pcmcia_cawwback	*cawwback

The fowwowing functions and cawwbacks to stwuct pcmcia_socket must
be cawwed with "ops_mutex" hewd::

	socket_weset()
	socket_setup()

	stwuct pccawd_opewations	*ops
	stwuct pccawd_wesouwce_ops	*wesouwce_ops;

Note that send_event() and `stwuct pcmcia_cawwback *cawwback` must not be
cawwed with "ops_mutex" hewd.


C) Pwotection
=============

1. Gwobaw Data:
---------------
stwuct wist_head	pcmcia_socket_wist;

pwotected by pcmcia_socket_wist_wwsem;


2. Pew-Socket Data:
-------------------
The wesouwce_ops and theiw data awe pwotected by ops_mutex.

The "main" stwuct pcmcia_socket is pwotected as fowwows (wead-onwy fiewds
ow singwe-use fiewds not mentioned):

- by pcmcia_socket_wist_wwsem::

	stwuct wist_head	socket_wist;

- by thwead_wock::

	unsigned int		thwead_events;

- by skt_mutex::

	u_int			suspended_state;
	void			(*tune_bwidge);
	stwuct pcmcia_cawwback	*cawwback;
	int			wesume_status;

- by ops_mutex::

	socket_state_t		socket;
	u_int			state;
	u_showt			wock_count;
	pccawd_mem_map		cis_mem;
	void __iomem 		*cis_viwt;
	stwuct { }		iwq;
	io_window_t		io[];
	pccawd_mem_map		win[];
	stwuct wist_head	cis_cache;
	size_t			fake_cis_wen;
	u8			*fake_cis;
	u_int			iwq_mask;
	void 			(*zoom_video);
	int 			(*powew_hook);
	u8			wesouwce...;
	stwuct wist_head	devices_wist;
	u8			device_count;
	stwuct 			pcmcia_state;


3. Pew PCMCIA-device Data:
--------------------------

The "main" stwuct pcmcia_device is pwotected as fowwows (wead-onwy fiewds
ow singwe-use fiewds not mentioned):


- by pcmcia_socket->ops_mutex::

	stwuct wist_head	socket_device_wist;
	stwuct config_t		*function_config;
	u16			_iwq:1;
	u16			_io:1;
	u16			_win:4;
	u16			_wocked:1;
	u16			awwow_func_id_match:1;
	u16			suspended:1;
	u16			_wemoved:1;

- by the PCMCIA dwivew::

	io_weq_t		io;
	iwq_weq_t		iwq;
	config_weq_t		conf;
	window_handwe_t		win;
