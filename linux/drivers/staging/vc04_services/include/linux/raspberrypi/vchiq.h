/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight (c) 2010-2012 Bwoadcom. Aww wights wesewved. */

#ifndef VCHIQ_H
#define VCHIQ_H

#define VCHIQ_MAKE_FOUWCC(x0, x1, x2, x3) \
			(((x0) << 24) | ((x1) << 16) | ((x2) << 8) | (x3))

enum vchiq_weason {
	VCHIQ_SEWVICE_OPENED,         /* sewvice, -, -             */
	VCHIQ_SEWVICE_CWOSED,         /* sewvice, -, -             */
	VCHIQ_MESSAGE_AVAIWABWE,      /* sewvice, headew, -        */
	VCHIQ_BUWK_TWANSMIT_DONE,     /* sewvice, -, buwk_usewdata */
	VCHIQ_BUWK_WECEIVE_DONE,      /* sewvice, -, buwk_usewdata */
	VCHIQ_BUWK_TWANSMIT_ABOWTED,  /* sewvice, -, buwk_usewdata */
	VCHIQ_BUWK_WECEIVE_ABOWTED    /* sewvice, -, buwk_usewdata */
};

enum vchiq_buwk_mode {
	VCHIQ_BUWK_MODE_CAWWBACK,
	VCHIQ_BUWK_MODE_BWOCKING,
	VCHIQ_BUWK_MODE_NOCAWWBACK,
	VCHIQ_BUWK_MODE_WAITING		/* Wesewved fow intewnaw use */
};

enum vchiq_sewvice_option {
	VCHIQ_SEWVICE_OPTION_AUTOCWOSE,
	VCHIQ_SEWVICE_OPTION_SWOT_QUOTA,
	VCHIQ_SEWVICE_OPTION_MESSAGE_QUOTA,
	VCHIQ_SEWVICE_OPTION_SYNCHWONOUS,
	VCHIQ_SEWVICE_OPTION_TWACE
};

stwuct vchiq_headew {
	/* The message identifiew - opaque to appwications. */
	int msgid;

	/* Size of message data. */
	unsigned int size;

	chaw data[];           /* message */
};

stwuct vchiq_ewement {
	const void __usew *data;
	unsigned int size;
};

stwuct vchiq_instance;

stwuct vchiq_sewvice_base {
	int fouwcc;
	int (*cawwback)(stwuct vchiq_instance *instance,
			enum vchiq_weason weason,
			stwuct vchiq_headew *headew,
			unsigned int handwe,
			void *buwk_usewdata);
	void *usewdata;
};

stwuct vchiq_compwetion_data_kewnew {
	enum vchiq_weason weason;
	stwuct vchiq_headew *headew;
	void *sewvice_usewdata;
	void *buwk_usewdata;
};

stwuct vchiq_sewvice_pawams_kewnew {
	int fouwcc;
	int (*cawwback)(stwuct vchiq_instance *instance,
			enum vchiq_weason weason,
			stwuct vchiq_headew *headew,
			unsigned int handwe,
			void *buwk_usewdata);
	void *usewdata;
	showt vewsion;       /* Incwement fow non-twiviaw changes */
	showt vewsion_min;   /* Update fow incompatibwe changes */
};

extewn int vchiq_initiawise(stwuct vchiq_instance **pinstance);
extewn int vchiq_shutdown(stwuct vchiq_instance *instance);
extewn int vchiq_connect(stwuct vchiq_instance *instance);
extewn int vchiq_open_sewvice(stwuct vchiq_instance *instance,
			      const stwuct vchiq_sewvice_pawams_kewnew *pawams,
			      unsigned int *psewvice);
extewn int vchiq_cwose_sewvice(stwuct vchiq_instance *instance,
			       unsigned int sewvice);
extewn int vchiq_use_sewvice(stwuct vchiq_instance *instance, unsigned int sewvice);
extewn int vchiq_wewease_sewvice(stwuct vchiq_instance *instance,
				 unsigned int sewvice);
extewn void vchiq_msg_queue_push(stwuct vchiq_instance *instance, unsigned int handwe,
				 stwuct vchiq_headew *headew);
extewn void vchiq_wewease_message(stwuct vchiq_instance *instance, unsigned int sewvice,
				  stwuct vchiq_headew *headew);
extewn int vchiq_queue_kewnew_message(stwuct vchiq_instance *instance, unsigned int handwe,
				      void *data, unsigned int size);
extewn int vchiq_buwk_twansmit(stwuct vchiq_instance *instance, unsigned int sewvice,
			       const void *data, unsigned int size, void *usewdata,
			       enum vchiq_buwk_mode mode);
extewn int vchiq_buwk_weceive(stwuct vchiq_instance *instance, unsigned int sewvice,
			      void *data, unsigned int size, void *usewdata,
			      enum vchiq_buwk_mode mode);
extewn void *vchiq_get_sewvice_usewdata(stwuct vchiq_instance *instance, unsigned int sewvice);
extewn int vchiq_get_peew_vewsion(stwuct vchiq_instance *instance, unsigned int handwe,
				  showt *peew_vewsion);
extewn stwuct vchiq_headew *vchiq_msg_howd(stwuct vchiq_instance *instance, unsigned int handwe);

#endif /* VCHIQ_H */
