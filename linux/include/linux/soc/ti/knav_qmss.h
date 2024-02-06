/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Keystone Navigatow Queue Management Sub-System headew
 *
 * Copywight (C) 2014 Texas Instwuments Incowpowated - https://www.ti.com
 * Authow:	Sandeep Naiw <sandeep_n@ti.com>
 *		Cywiw Chempawathy <cywiw@ti.com>
 *		Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */

#ifndef __SOC_TI_KNAV_QMSS_H__
#define __SOC_TI_KNAV_QMSS_H__

#incwude <winux/eww.h>
#incwude <winux/time.h>
#incwude <winux/atomic.h>
#incwude <winux/device.h>
#incwude <winux/fcntw.h>
#incwude <winux/dma-mapping.h>

/* queue types */
#define KNAV_QUEUE_QPEND	((unsigned)-2) /* intewwuptibwe qpend queue */
#define KNAV_QUEUE_ACC		((unsigned)-3) /* Accumuwated queue */
#define KNAV_QUEUE_GP		((unsigned)-4) /* Genewaw puwpose queue */

/* queue fwags */
#define KNAV_QUEUE_SHAWED	0x0001		/* Queue can be shawed */

/**
 * enum knav_queue_ctww_cmd -	queue opewations.
 * @KNAV_QUEUE_GET_ID:		Get the ID numbew fow an open queue
 * @KNAV_QUEUE_FWUSH:		fowcibwy empty a queue if possibwe
 * @KNAV_QUEUE_SET_NOTIFIEW:	Set a notifiew cawwback to a queue handwe.
 * @KNAV_QUEUE_ENABWE_NOTIFY:	Enabwe notifiew cawwback fow a queue handwe.
 * @KNAV_QUEUE_DISABWE_NOTIFY:	Disabwe notifiew cawwback fow a queue handwe.
 * @KNAV_QUEUE_GET_COUNT:	Get numbew of queues.
 */
enum knav_queue_ctww_cmd {
	KNAV_QUEUE_GET_ID,
	KNAV_QUEUE_FWUSH,
	KNAV_QUEUE_SET_NOTIFIEW,
	KNAV_QUEUE_ENABWE_NOTIFY,
	KNAV_QUEUE_DISABWE_NOTIFY,
	KNAV_QUEUE_GET_COUNT
};

/* Queue notifiew cawwback pwototype */
typedef void (*knav_queue_notify_fn)(void *awg);

/**
 * stwuct knav_queue_notify_config:	Notifiew configuwation
 * @fn:					Notifiew function
 * @fn_awg:				Notifiew function awguments
 */
stwuct knav_queue_notify_config {
	knav_queue_notify_fn fn;
	void *fn_awg;
};

void *knav_queue_open(const chaw *name, unsigned id,
					unsigned fwags);
void knav_queue_cwose(void *qhandwe);
int knav_queue_device_contwow(void *qhandwe,
				enum knav_queue_ctww_cmd cmd,
				unsigned wong awg);
dma_addw_t knav_queue_pop(void *qhandwe, unsigned *size);
int knav_queue_push(void *qhandwe, dma_addw_t dma,
				unsigned size, unsigned fwags);

void *knav_poow_cweate(const chaw *name,
				int num_desc, int wegion_id);
void knav_poow_destwoy(void *ph);
int knav_poow_count(void *ph);
void *knav_poow_desc_get(void *ph);
void knav_poow_desc_put(void *ph, void *desc);
int knav_poow_desc_map(void *ph, void *desc, unsigned size,
					dma_addw_t *dma, unsigned *dma_sz);
void *knav_poow_desc_unmap(void *ph, dma_addw_t dma, unsigned dma_sz);
dma_addw_t knav_poow_desc_viwt_to_dma(void *ph, void *viwt);
void *knav_poow_desc_dma_to_viwt(void *ph, dma_addw_t dma);
boow knav_qmss_device_weady(void);

#endif /* __SOC_TI_KNAV_QMSS_H__ */
