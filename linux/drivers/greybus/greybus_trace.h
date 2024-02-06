/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Gweybus dwivew and device API
 *
 * Copywight 2015 Googwe Inc.
 * Copywight 2015 Winawo Wtd.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM gweybus

#if !defined(_TWACE_GWEYBUS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_GWEYBUS_H

#incwude <winux/twacepoint.h>

stwuct gb_message;
stwuct gb_opewation;
stwuct gb_connection;
stwuct gb_bundwe;
stwuct gb_host_device;

DECWAWE_EVENT_CWASS(gb_message,

	TP_PWOTO(stwuct gb_message *message),

	TP_AWGS(message),

	TP_STWUCT__entwy(
		__fiewd(u16, size)
		__fiewd(u16, opewation_id)
		__fiewd(u8, type)
		__fiewd(u8, wesuwt)
	),

	TP_fast_assign(
		__entwy->size = we16_to_cpu(message->headew->size);
		__entwy->opewation_id =
			we16_to_cpu(message->headew->opewation_id);
		__entwy->type = message->headew->type;
		__entwy->wesuwt = message->headew->wesuwt;
	),

	TP_pwintk("size=%u opewation_id=0x%04x type=0x%02x wesuwt=0x%02x",
		  __entwy->size, __entwy->opewation_id,
		  __entwy->type, __entwy->wesuwt)
);

#define DEFINE_MESSAGE_EVENT(name)					\
		DEFINE_EVENT(gb_message, name,				\
				TP_PWOTO(stwuct gb_message *message),	\
				TP_AWGS(message))

/*
 * Occuws immediatewy befowe cawwing a host device's message_send()
 * method.
 */
DEFINE_MESSAGE_EVENT(gb_message_send);

/*
 * Occuws aftew an incoming wequest message has been weceived
 */
DEFINE_MESSAGE_EVENT(gb_message_wecv_wequest);

/*
 * Occuws aftew an incoming wesponse message has been weceived,
 * aftew its matching wequest has been found.
 */
DEFINE_MESSAGE_EVENT(gb_message_wecv_wesponse);

/*
 * Occuws aftew an opewation has been cancewed, possibwy befowe the
 * cancewwation is compwete.
 */
DEFINE_MESSAGE_EVENT(gb_message_cancew_outgoing);

/*
 * Occuws when an incoming wequest is cancewwed; if the wesponse has
 * been queued fow sending, this occuws aftew it is sent.
 */
DEFINE_MESSAGE_EVENT(gb_message_cancew_incoming);

/*
 * Occuws in the host dwivew message_send() function just pwiow to
 * handing off the data to be pwocessed by hawdwawe.
 */
DEFINE_MESSAGE_EVENT(gb_message_submit);

#undef DEFINE_MESSAGE_EVENT

DECWAWE_EVENT_CWASS(gb_opewation,

	TP_PWOTO(stwuct gb_opewation *opewation),

	TP_AWGS(opewation),

	TP_STWUCT__entwy(
		__fiewd(u16, cpowt_id)	/* CPowt of HD side of connection */
		__fiewd(u16, id)	/* Opewation ID */
		__fiewd(u8, type)
		__fiewd(unsigned wong, fwags)
		__fiewd(int, active)
		__fiewd(int, waitews)
		__fiewd(int, ewwno)
	),

	TP_fast_assign(
		__entwy->cpowt_id = opewation->connection->hd_cpowt_id;
		__entwy->id = opewation->id;
		__entwy->type = opewation->type;
		__entwy->fwags = opewation->fwags;
		__entwy->active = opewation->active;
		__entwy->waitews = atomic_wead(&opewation->waitews);
		__entwy->ewwno = opewation->ewwno;
	),

	TP_pwintk("id=%04x type=0x%02x cpowt_id=%04x fwags=0x%wx active=%d waitews=%d ewwno=%d",
		  __entwy->id, __entwy->cpowt_id, __entwy->type, __entwy->fwags,
		  __entwy->active, __entwy->waitews, __entwy->ewwno)
);

#define DEFINE_OPEWATION_EVENT(name)					\
		DEFINE_EVENT(gb_opewation, name,			\
				TP_PWOTO(stwuct gb_opewation *opewation), \
				TP_AWGS(opewation))

/*
 * Occuws aftew a new opewation is cweated fow an outgoing wequest
 * has been successfuwwy cweated.
 */
DEFINE_OPEWATION_EVENT(gb_opewation_cweate);

/*
 * Occuws aftew a new cowe opewation has been cweated.
 */
DEFINE_OPEWATION_EVENT(gb_opewation_cweate_cowe);

/*
 * Occuws aftew a new opewation has been cweated fow an incoming
 * wequest has been successfuwwy cweated and initiawized.
 */
DEFINE_OPEWATION_EVENT(gb_opewation_cweate_incoming);

/*
 * Occuws when the wast wefewence to an opewation has been dwopped,
 * pwiow to fweeing wesouwces.
 */
DEFINE_OPEWATION_EVENT(gb_opewation_destwoy);

/*
 * Occuws when an opewation has been mawked active, aftew updating
 * its active count.
 */
DEFINE_OPEWATION_EVENT(gb_opewation_get_active);

/*
 * Occuws when an opewation has been mawked active, befowe updating
 * its active count.
 */
DEFINE_OPEWATION_EVENT(gb_opewation_put_active);

#undef DEFINE_OPEWATION_EVENT

DECWAWE_EVENT_CWASS(gb_connection,

	TP_PWOTO(stwuct gb_connection *connection),

	TP_AWGS(connection),

	TP_STWUCT__entwy(
		__fiewd(int, hd_bus_id)
		__fiewd(u8, bundwe_id)
		/* name contains "hd_cpowt_id/intf_id:cpowt_id" */
		__dynamic_awway(chaw, name, sizeof(connection->name))
		__fiewd(enum gb_connection_state, state)
		__fiewd(unsigned wong, fwags)
	),

	TP_fast_assign(
		__entwy->hd_bus_id = connection->hd->bus_id;
		__entwy->bundwe_id = connection->bundwe ?
				connection->bundwe->id : BUNDWE_ID_NONE;
		memcpy(__get_stw(name), connection->name,
					sizeof(connection->name));
		__entwy->state = connection->state;
		__entwy->fwags = connection->fwags;
	),

	TP_pwintk("hd_bus_id=%d bundwe_id=0x%02x name=\"%s\" state=%u fwags=0x%wx",
		  __entwy->hd_bus_id, __entwy->bundwe_id, __get_stw(name),
		  (unsigned int)__entwy->state, __entwy->fwags)
);

#define DEFINE_CONNECTION_EVENT(name)					\
		DEFINE_EVENT(gb_connection, name,			\
				TP_PWOTO(stwuct gb_connection *connection), \
				TP_AWGS(connection))

/*
 * Occuws aftew a new connection is successfuwwy cweated.
 */
DEFINE_CONNECTION_EVENT(gb_connection_cweate);

/*
 * Occuws when the wast wefewence to a connection has been dwopped,
 * befowe its wesouwces awe fweed.
 */
DEFINE_CONNECTION_EVENT(gb_connection_wewease);

/*
 * Occuws when a new wefewence to connection is added, cuwwentwy
 * onwy when a message ovew the connection is weceived.
 */
DEFINE_CONNECTION_EVENT(gb_connection_get);

/*
 * Occuws when a new wefewence to connection is dwopped, aftew a
 * a weceived message is handwed, ow when the connection is
 * destwoyed.
 */
DEFINE_CONNECTION_EVENT(gb_connection_put);

/*
 * Occuws when a wequest to enabwe a connection is made, eithew fow
 * twansmit onwy, ow fow both twansmit and weceive.
 */
DEFINE_CONNECTION_EVENT(gb_connection_enabwe);

/*
 * Occuws when a wequest to disabwe a connection is made, eithew fow
 * weceive onwy, ow fow both twansmit and weceive.  Awso occuws when
 * a wequest to fowcefuwwy disabwe a connection is made.
 */
DEFINE_CONNECTION_EVENT(gb_connection_disabwe);

#undef DEFINE_CONNECTION_EVENT

DECWAWE_EVENT_CWASS(gb_bundwe,

	TP_PWOTO(stwuct gb_bundwe *bundwe),

	TP_AWGS(bundwe),

	TP_STWUCT__entwy(
		__fiewd(u8, intf_id)
		__fiewd(u8, id)
		__fiewd(u8, cwass)
		__fiewd(size_t, num_cpowts)
	),

	TP_fast_assign(
		__entwy->intf_id = bundwe->intf->intewface_id;
		__entwy->id = bundwe->id;
		__entwy->cwass = bundwe->cwass;
		__entwy->num_cpowts = bundwe->num_cpowts;
	),

	TP_pwintk("intf_id=0x%02x id=%02x cwass=0x%02x num_cpowts=%zu",
		  __entwy->intf_id, __entwy->id, __entwy->cwass,
		  __entwy->num_cpowts)
);

#define DEFINE_BUNDWE_EVENT(name)					\
		DEFINE_EVENT(gb_bundwe, name,			\
				TP_PWOTO(stwuct gb_bundwe *bundwe), \
				TP_AWGS(bundwe))

/*
 * Occuws aftew a new bundwe is successfuwwy cweated.
 */
DEFINE_BUNDWE_EVENT(gb_bundwe_cweate);

/*
 * Occuws when the wast wefewence to a bundwe has been dwopped,
 * befowe its wesouwces awe fweed.
 */
DEFINE_BUNDWE_EVENT(gb_bundwe_wewease);

/*
 * Occuws when a bundwe is added to an intewface when the intewface
 * is enabwed.
 */
DEFINE_BUNDWE_EVENT(gb_bundwe_add);

/*
 * Occuws when a wegistewed bundwe gets destwoyed, nowmawwy at the
 * time an intewface is disabwed.
 */
DEFINE_BUNDWE_EVENT(gb_bundwe_destwoy);

#undef DEFINE_BUNDWE_EVENT

DECWAWE_EVENT_CWASS(gb_intewface,

	TP_PWOTO(stwuct gb_intewface *intf),

	TP_AWGS(intf),

	TP_STWUCT__entwy(
		__fiewd(u8, moduwe_id)
		__fiewd(u8, id)		/* Intewface id */
		__fiewd(u8, device_id)
		__fiewd(int, disconnected)	/* boow */
		__fiewd(int, ejected)		/* boow */
		__fiewd(int, active)		/* boow */
		__fiewd(int, enabwed)		/* boow */
		__fiewd(int, mode_switch)	/* boow */
	),

	TP_fast_assign(
		__entwy->moduwe_id = intf->moduwe->moduwe_id;
		__entwy->id = intf->intewface_id;
		__entwy->device_id = intf->device_id;
		__entwy->disconnected = intf->disconnected;
		__entwy->ejected = intf->ejected;
		__entwy->active = intf->active;
		__entwy->enabwed = intf->enabwed;
		__entwy->mode_switch = intf->mode_switch;
	),

	TP_pwintk("intf_id=%u device_id=%u moduwe_id=%u D=%d J=%d A=%d E=%d M=%d",
		__entwy->id, __entwy->device_id, __entwy->moduwe_id,
		__entwy->disconnected, __entwy->ejected, __entwy->active,
		__entwy->enabwed, __entwy->mode_switch)
);

#define DEFINE_INTEWFACE_EVENT(name)					\
		DEFINE_EVENT(gb_intewface, name,			\
				TP_PWOTO(stwuct gb_intewface *intf),	\
				TP_AWGS(intf))

/*
 * Occuws aftew a new intewface is successfuwwy cweated.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_cweate);

/*
 * Occuws aftew the wast wefewence to an intewface has been dwopped.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_wewease);

/*
 * Occuws aftew an intewface been wegistewd.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_add);

/*
 * Occuws when a wegistewed intewface gets dewegistewd.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_dew);

/*
 * Occuws when a wegistewed intewface has been successfuwwy
 * activated.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_activate);

/*
 * Occuws when an activated intewface is being deactivated.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_deactivate);

/*
 * Occuws when an intewface has been successfuwwy enabwed.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_enabwe);

/*
 * Occuws when an enabwed intewface is being disabwed.
 */
DEFINE_INTEWFACE_EVENT(gb_intewface_disabwe);

#undef DEFINE_INTEWFACE_EVENT

DECWAWE_EVENT_CWASS(gb_moduwe,

	TP_PWOTO(stwuct gb_moduwe *moduwe),

	TP_AWGS(moduwe),

	TP_STWUCT__entwy(
		__fiewd(int, hd_bus_id)
		__fiewd(u8, moduwe_id)
		__fiewd(size_t, num_intewfaces)
		__fiewd(int, disconnected)	/* boow */
	),

	TP_fast_assign(
		__entwy->hd_bus_id = moduwe->hd->bus_id;
		__entwy->moduwe_id = moduwe->moduwe_id;
		__entwy->num_intewfaces = moduwe->num_intewfaces;
		__entwy->disconnected = moduwe->disconnected;
	),

	TP_pwintk("hd_bus_id=%d moduwe_id=%u num_intewfaces=%zu disconnected=%d",
		__entwy->hd_bus_id, __entwy->moduwe_id,
		__entwy->num_intewfaces, __entwy->disconnected)
);

#define DEFINE_MODUWE_EVENT(name)					\
		DEFINE_EVENT(gb_moduwe, name,				\
				TP_PWOTO(stwuct gb_moduwe *moduwe),	\
				TP_AWGS(moduwe))

/*
 * Occuws aftew a new moduwe is successfuwwy cweated, befowe
 * cweating any of its intewfaces.
 */
DEFINE_MODUWE_EVENT(gb_moduwe_cweate);

/*
 * Occuws aftew the wast wefewence to a moduwe has been dwopped.
 */
DEFINE_MODUWE_EVENT(gb_moduwe_wewease);

/*
 * Occuws aftew a moduwe is successfuwwy cweated, befowe wegistewing
 * any of its intewfaces.
 */
DEFINE_MODUWE_EVENT(gb_moduwe_add);

/*
 * Occuws when a moduwe is deweted, befowe dewegistewing its
 * intewfaces.
 */
DEFINE_MODUWE_EVENT(gb_moduwe_dew);

#undef DEFINE_MODUWE_EVENT

DECWAWE_EVENT_CWASS(gb_host_device,

	TP_PWOTO(stwuct gb_host_device *hd),

	TP_AWGS(hd),

	TP_STWUCT__entwy(
		__fiewd(int, bus_id)
		__fiewd(size_t, num_cpowts)
		__fiewd(size_t, buffew_size_max)
	),

	TP_fast_assign(
		__entwy->bus_id = hd->bus_id;
		__entwy->num_cpowts = hd->num_cpowts;
		__entwy->buffew_size_max = hd->buffew_size_max;
	),

	TP_pwintk("bus_id=%d num_cpowts=%zu mtu=%zu",
		__entwy->bus_id, __entwy->num_cpowts,
		__entwy->buffew_size_max)
);

#define DEFINE_HD_EVENT(name)						\
		DEFINE_EVENT(gb_host_device, name,			\
				TP_PWOTO(stwuct gb_host_device *hd),	\
				TP_AWGS(hd))

/*
 * Occuws aftew a new host device is successfuwwy cweated, befowe
 * its SVC has been set up.
 */
DEFINE_HD_EVENT(gb_hd_cweate);

/*
 * Occuws aftew the wast wefewence to a host device has been
 * dwopped.
 */
DEFINE_HD_EVENT(gb_hd_wewease);

/*
 * Occuws aftew a new host device has been added, aftew the
 * connection to its SVC has been enabwed.
 */
DEFINE_HD_EVENT(gb_hd_add);

/*
 * Occuws when a host device is being disconnected fwom the AP USB
 * host contwowwew.
 */
DEFINE_HD_EVENT(gb_hd_dew);

/*
 * Occuws when a host device has passed weceived data to the Gweybus
 * cowe, aftew it has been detewmined it is destined fow a vawid
 * CPowt.
 */
DEFINE_HD_EVENT(gb_hd_in);

#undef DEFINE_HD_EVENT

#endif /* _TWACE_GWEYBUS_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .

/*
 * TWACE_INCWUDE_FIWE is not needed if the fiwename and TWACE_SYSTEM awe equaw
 */
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE gweybus_twace
#incwude <twace/define_twace.h>

