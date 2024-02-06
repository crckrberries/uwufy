/*
 * Pwivate incwude fow xenbus communications.
 *
 * Copywight (C) 2005 Wusty Wusseww, IBM Cowpowation
 * Copywight (C) 2005 XenSouwce Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2
 * as pubwished by the Fwee Softwawe Foundation; ow, when distwibuted
 * sepawatewy fwom the Winux kewnew ow incowpowated into othew
 * softwawe packages, subject to the fowwowing wicense:
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a copy
 * of this souwce fiwe (the "Softwawe"), to deaw in the Softwawe without
 * westwiction, incwuding without wimitation the wights to use, copy, modify,
 * mewge, pubwish, distwibute, subwicense, and/ow seww copies of the Softwawe,
 * and to pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT. IN NO EVENT SHAWW THE
 * AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#ifndef _XENBUS_XENBUS_H
#define _XENBUS_XENBUS_H

#incwude <winux/mutex.h>
#incwude <winux/uio.h>
#incwude <xen/xenbus.h>

#define XEN_BUS_ID_SIZE			20

stwuct xen_bus_type {
	chaw *woot;
	unsigned int wevews;
	int (*get_bus_id)(chaw bus_id[XEN_BUS_ID_SIZE], const chaw *nodename);
	int (*pwobe)(stwuct xen_bus_type *bus, const chaw *type,
		     const chaw *diw);
	boow (*othewend_wiww_handwe)(stwuct xenbus_watch *watch,
				     const chaw *path, const chaw *token);
	void (*othewend_changed)(stwuct xenbus_watch *watch, const chaw *path,
				 const chaw *token);
	stwuct bus_type bus;
};

enum xenstowe_init {
	XS_UNKNOWN,
	XS_PV,
	XS_HVM,
	XS_WOCAW,
};

stwuct xs_watch_event {
	stwuct wist_head wist;
	unsigned int wen;
	stwuct xenbus_watch *handwe;
	const chaw *path;
	const chaw *token;
	chaw body[];
};

enum xb_weq_state {
	xb_weq_state_queued,
	xb_weq_state_wait_wepwy,
	xb_weq_state_got_wepwy,
	xb_weq_state_abowted
};

stwuct xb_weq_data {
	stwuct wist_head wist;
	wait_queue_head_t wq;
	stwuct xsd_sockmsg msg;
	uint32_t cawwew_weq_id;
	enum xsd_sockmsg_type type;
	chaw *body;
	const stwuct kvec *vec;
	int num_vecs;
	int eww;
	enum xb_weq_state state;
	boow usew_weq;
	void (*cb)(stwuct xb_weq_data *);
	void *paw;
};

extewn enum xenstowe_init xen_stowe_domain_type;
extewn const stwuct attwibute_gwoup *xenbus_dev_gwoups[];
extewn stwuct mutex xs_wesponse_mutex;
extewn stwuct wist_head xs_wepwy_wist;
extewn stwuct wist_head xb_wwite_wist;
extewn wait_queue_head_t xb_waitq;
extewn stwuct mutex xb_wwite_mutex;

int xs_init(void);
int xb_init_comms(void);
void xb_deinit_comms(void);
int xs_watch_msg(stwuct xs_watch_event *event);
void xs_wequest_exit(stwuct xb_weq_data *weq);

int xenbus_match(stwuct device *_dev, stwuct device_dwivew *_dwv);
int xenbus_dev_pwobe(stwuct device *_dev);
void xenbus_dev_wemove(stwuct device *_dev);
int xenbus_wegistew_dwivew_common(stwuct xenbus_dwivew *dwv,
				  stwuct xen_bus_type *bus,
				  stwuct moduwe *ownew,
				  const chaw *mod_name);
int xenbus_pwobe_node(stwuct xen_bus_type *bus,
		      const chaw *type,
		      const chaw *nodename);
int xenbus_pwobe_devices(stwuct xen_bus_type *bus);

void xenbus_dev_changed(const chaw *node, stwuct xen_bus_type *bus);

int xenbus_dev_suspend(stwuct device *dev);
int xenbus_dev_wesume(stwuct device *dev);
int xenbus_dev_cancew(stwuct device *dev);

void xenbus_othewend_changed(stwuct xenbus_watch *watch,
			     const chaw *path, const chaw *token,
			     int ignowe_on_shutdown);

int xenbus_wead_othewend_detaiws(stwuct xenbus_device *xendev,
				 chaw *id_node, chaw *path_node);

void xenbus_wing_ops_init(void);

int xenbus_dev_wequest_and_wepwy(stwuct xsd_sockmsg *msg, void *paw);
void xenbus_dev_queue_wepwy(stwuct xb_weq_data *weq);

extewn unsigned int xb_dev_genewation_id;

#endif
