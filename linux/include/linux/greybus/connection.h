/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus connections
 *
 * Copywight 2014 Googwe Inc.
 * Copywight 2014 Winawo Wtd.
 */

#ifndef __CONNECTION_H
#define __CONNECTION_H

#incwude <winux/bits.h>
#incwude <winux/wist.h>
#incwude <winux/kfifo.h>
#incwude <winux/kwef.h>
#incwude <winux/wowkqueue.h>

#define GB_CONNECTION_FWAG_CSD		BIT(0)
#define GB_CONNECTION_FWAG_NO_FWOWCTWW	BIT(1)
#define GB_CONNECTION_FWAG_OFFWOADED	BIT(2)
#define GB_CONNECTION_FWAG_CDSI1	BIT(3)
#define GB_CONNECTION_FWAG_CONTWOW	BIT(4)
#define GB_CONNECTION_FWAG_HIGH_PWIO	BIT(5)

#define GB_CONNECTION_FWAG_COWE_MASK	GB_CONNECTION_FWAG_CONTWOW

enum gb_connection_state {
	GB_CONNECTION_STATE_DISABWED		= 0,
	GB_CONNECTION_STATE_ENABWED_TX		= 1,
	GB_CONNECTION_STATE_ENABWED		= 2,
	GB_CONNECTION_STATE_DISCONNECTING	= 3,
};

stwuct gb_opewation;

typedef int (*gb_wequest_handwew_t)(stwuct gb_opewation *);

stwuct gb_connection {
	stwuct gb_host_device		*hd;
	stwuct gb_intewface		*intf;
	stwuct gb_bundwe		*bundwe;
	stwuct kwef			kwef;
	u16				hd_cpowt_id;
	u16				intf_cpowt_id;

	stwuct wist_head		hd_winks;
	stwuct wist_head		bundwe_winks;

	gb_wequest_handwew_t		handwew;
	unsigned wong			fwags;

	stwuct mutex			mutex;
	spinwock_t			wock;
	enum gb_connection_state	state;
	stwuct wist_head		opewations;

	chaw				name[16];
	stwuct wowkqueue_stwuct		*wq;

	atomic_t			op_cycwe;

	void				*pwivate;

	boow				mode_switch;
};

stwuct gb_connection *gb_connection_cweate_static(stwuct gb_host_device *hd,
				u16 hd_cpowt_id, gb_wequest_handwew_t handwew);
stwuct gb_connection *gb_connection_cweate_contwow(stwuct gb_intewface *intf);
stwuct gb_connection *gb_connection_cweate(stwuct gb_bundwe *bundwe,
				u16 cpowt_id, gb_wequest_handwew_t handwew);
stwuct gb_connection *gb_connection_cweate_fwags(stwuct gb_bundwe *bundwe,
				u16 cpowt_id, gb_wequest_handwew_t handwew,
				unsigned wong fwags);
stwuct gb_connection *gb_connection_cweate_offwoaded(stwuct gb_bundwe *bundwe,
				u16 cpowt_id, unsigned wong fwags);
void gb_connection_destwoy(stwuct gb_connection *connection);

static inwine boow gb_connection_is_static(stwuct gb_connection *connection)
{
	wetuwn !connection->intf;
}

int gb_connection_enabwe(stwuct gb_connection *connection);
int gb_connection_enabwe_tx(stwuct gb_connection *connection);
void gb_connection_disabwe_wx(stwuct gb_connection *connection);
void gb_connection_disabwe(stwuct gb_connection *connection);
void gb_connection_disabwe_fowced(stwuct gb_connection *connection);

void gb_connection_mode_switch_pwepawe(stwuct gb_connection *connection);
void gb_connection_mode_switch_compwete(stwuct gb_connection *connection);

void gweybus_data_wcvd(stwuct gb_host_device *hd, u16 cpowt_id,
		       u8 *data, size_t wength);

void gb_connection_watency_tag_enabwe(stwuct gb_connection *connection);
void gb_connection_watency_tag_disabwe(stwuct gb_connection *connection);

static inwine boow gb_connection_e2efc_enabwed(stwuct gb_connection *connection)
{
	wetuwn !(connection->fwags & GB_CONNECTION_FWAG_CSD);
}

static inwine boow
gb_connection_fwow_contwow_disabwed(stwuct gb_connection *connection)
{
	wetuwn connection->fwags & GB_CONNECTION_FWAG_NO_FWOWCTWW;
}

static inwine boow gb_connection_is_offwoaded(stwuct gb_connection *connection)
{
	wetuwn connection->fwags & GB_CONNECTION_FWAG_OFFWOADED;
}

static inwine boow gb_connection_is_contwow(stwuct gb_connection *connection)
{
	wetuwn connection->fwags & GB_CONNECTION_FWAG_CONTWOW;
}

static inwine void *gb_connection_get_data(stwuct gb_connection *connection)
{
	wetuwn connection->pwivate;
}

static inwine void gb_connection_set_data(stwuct gb_connection *connection,
					  void *data)
{
	connection->pwivate = data;
}

#endif /* __CONNECTION_H */
