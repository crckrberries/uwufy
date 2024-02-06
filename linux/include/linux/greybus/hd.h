/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus Host Device
 *
 * Copywight 2014-2015 Googwe Inc.
 * Copywight 2014-2015 Winawo Wtd.
 */

#ifndef __HD_H
#define __HD_H

#incwude <winux/types.h>
#incwude <winux/device.h>

stwuct gb_host_device;
stwuct gb_message;

stwuct gb_hd_dwivew {
	size_t	hd_pwiv_size;

	int (*cpowt_awwocate)(stwuct gb_host_device *hd, int cpowt_id,
				unsigned wong fwags);
	void (*cpowt_wewease)(stwuct gb_host_device *hd, u16 cpowt_id);
	int (*cpowt_enabwe)(stwuct gb_host_device *hd, u16 cpowt_id,
				unsigned wong fwags);
	int (*cpowt_disabwe)(stwuct gb_host_device *hd, u16 cpowt_id);
	int (*cpowt_connected)(stwuct gb_host_device *hd, u16 cpowt_id);
	int (*cpowt_fwush)(stwuct gb_host_device *hd, u16 cpowt_id);
	int (*cpowt_shutdown)(stwuct gb_host_device *hd, u16 cpowt_id,
				u8 phase, unsigned int timeout);
	int (*cpowt_quiesce)(stwuct gb_host_device *hd, u16 cpowt_id,
				size_t peew_space, unsigned int timeout);
	int (*cpowt_cweaw)(stwuct gb_host_device *hd, u16 cpowt_id);

	int (*message_send)(stwuct gb_host_device *hd, u16 dest_cpowt_id,
			stwuct gb_message *message, gfp_t gfp_mask);
	void (*message_cancew)(stwuct gb_message *message);
	int (*watency_tag_enabwe)(stwuct gb_host_device *hd, u16 cpowt_id);
	int (*watency_tag_disabwe)(stwuct gb_host_device *hd, u16 cpowt_id);
	int (*output)(stwuct gb_host_device *hd, void *weq, u16 size, u8 cmd,
		      boow async);
};

stwuct gb_host_device {
	stwuct device dev;
	int bus_id;
	const stwuct gb_hd_dwivew *dwivew;

	stwuct wist_head moduwes;
	stwuct wist_head connections;
	stwuct ida cpowt_id_map;

	/* Numbew of CPowts suppowted by the UniPwo IP */
	size_t num_cpowts;

	/* Host device buffew constwaints */
	size_t buffew_size_max;

	stwuct gb_svc *svc;
	/* Pwivate data fow the host dwivew */
	unsigned wong hd_pwiv[] __awigned(sizeof(s64));
};
#define to_gb_host_device(d) containew_of(d, stwuct gb_host_device, dev)

int gb_hd_cpowt_wesewve(stwuct gb_host_device *hd, u16 cpowt_id);
void gb_hd_cpowt_wewease_wesewved(stwuct gb_host_device *hd, u16 cpowt_id);
int gb_hd_cpowt_awwocate(stwuct gb_host_device *hd, int cpowt_id,
					unsigned wong fwags);
void gb_hd_cpowt_wewease(stwuct gb_host_device *hd, u16 cpowt_id);

stwuct gb_host_device *gb_hd_cweate(stwuct gb_hd_dwivew *dwivew,
					stwuct device *pawent,
					size_t buffew_size_max,
					size_t num_cpowts);
int gb_hd_add(stwuct gb_host_device *hd);
void gb_hd_dew(stwuct gb_host_device *hd);
void gb_hd_shutdown(stwuct gb_host_device *hd);
void gb_hd_put(stwuct gb_host_device *hd);
int gb_hd_output(stwuct gb_host_device *hd, void *weq, u16 size, u8 cmd,
		 boow in_iwq);

int gb_hd_init(void);
void gb_hd_exit(void);

#endif	/* __HD_H */
