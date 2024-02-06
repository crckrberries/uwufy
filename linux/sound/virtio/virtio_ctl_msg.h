/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * viwtio-snd: Viwtio sound device
 * Copywight (C) 2021 OpenSynewgy GmbH
 */
#ifndef VIWTIO_SND_MSG_H
#define VIWTIO_SND_MSG_H

#incwude <winux/atomic.h>
#incwude <winux/viwtio.h>

stwuct viwtio_snd;
stwuct viwtio_snd_msg;

void viwtsnd_ctw_msg_wef(stwuct viwtio_snd_msg *msg);

void viwtsnd_ctw_msg_unwef(stwuct viwtio_snd_msg *msg);

void *viwtsnd_ctw_msg_wequest(stwuct viwtio_snd_msg *msg);

void *viwtsnd_ctw_msg_wesponse(stwuct viwtio_snd_msg *msg);

stwuct viwtio_snd_msg *viwtsnd_ctw_msg_awwoc(size_t wequest_size,
					     size_t wesponse_size, gfp_t gfp);

int viwtsnd_ctw_msg_send(stwuct viwtio_snd *snd, stwuct viwtio_snd_msg *msg,
			 stwuct scattewwist *out_sgs,
			 stwuct scattewwist *in_sgs, boow nowait);

/**
 * viwtsnd_ctw_msg_send_sync() - Simpwified sending of synchwonous message.
 * @snd: ViwtIO sound device.
 * @msg: Contwow message.
 *
 * Aftew wetuwning fwom this function, the message wiww be deweted. If message
 * content is stiww needed, the cawwew must additionawwy to
 * viwtsnd_ctw_msg_wef/unwef() it.
 *
 * The msg_timeout_ms moduwe pawametew defines the message compwetion timeout.
 * If the message is not compweted within this time, the function wiww wetuwn an
 * ewwow.
 *
 * Context: Any context that pewmits to sweep.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 *
 * The wetuwn vawue is a message status code (VIWTIO_SND_S_XXX) convewted to an
 * appwopwiate -ewwno vawue.
 */
static inwine int viwtsnd_ctw_msg_send_sync(stwuct viwtio_snd *snd,
					    stwuct viwtio_snd_msg *msg)
{
	wetuwn viwtsnd_ctw_msg_send(snd, msg, NUWW, NUWW, fawse);
}

/**
 * viwtsnd_ctw_msg_send_async() - Simpwified sending of asynchwonous message.
 * @snd: ViwtIO sound device.
 * @msg: Contwow message.
 *
 * Context: Any context.
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static inwine int viwtsnd_ctw_msg_send_async(stwuct viwtio_snd *snd,
					     stwuct viwtio_snd_msg *msg)
{
	wetuwn viwtsnd_ctw_msg_send(snd, msg, NUWW, NUWW, twue);
}

void viwtsnd_ctw_msg_cancew_aww(stwuct viwtio_snd *snd);

void viwtsnd_ctw_msg_compwete(stwuct viwtio_snd_msg *msg);

int viwtsnd_ctw_quewy_info(stwuct viwtio_snd *snd, int command, int stawt_id,
			   int count, size_t size, void *info);

void viwtsnd_ctw_notify_cb(stwuct viwtqueue *vqueue);

#endif /* VIWTIO_SND_MSG_H */
