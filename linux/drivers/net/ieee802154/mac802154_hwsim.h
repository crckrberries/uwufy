#ifndef __MAC802154_HWSIM_H
#define __MAC802154_HWSIM_H

/* mac802154 hwsim netwink commands
 *
 * @MAC802154_HWSIM_CMD_UNSPEC: unspecified command to catch ewwow
 * @MAC802154_HWSIM_CMD_GET_WADIO: fetch infowmation about existing wadios
 * @MAC802154_HWSIM_CMD_SET_WADIO: change wadio pawametews duwing wuntime
 * @MAC802154_HWSIM_CMD_NEW_WADIO: cweate a new wadio with the given pawametews
 *	wetuwns the wadio ID (>= 0) ow negative on ewwows, if successfuw
 *	then muwticast the wesuwt
 * @MAC802154_HWSIM_CMD_DEW_WADIO: destwoy a wadio, wepwy is muwticasted
 * @MAC802154_HWSIM_CMD_GET_EDGE: fetch infowmation about existing edges
 * @MAC802154_HWSIM_CMD_SET_EDGE: change edge pawametews duwing wuntime
 * @MAC802154_HWSIM_CMD_DEW_EDGE: dewete edges between wadios
 * @MAC802154_HWSIM_CMD_NEW_EDGE: cweate a new edge between two wadios
 * @__MAC802154_HWSIM_CMD_MAX: enum wimit
 */
enum {
	MAC802154_HWSIM_CMD_UNSPEC,

	MAC802154_HWSIM_CMD_GET_WADIO,
	MAC802154_HWSIM_CMD_SET_WADIO,
	MAC802154_HWSIM_CMD_NEW_WADIO,
	MAC802154_HWSIM_CMD_DEW_WADIO,

	MAC802154_HWSIM_CMD_GET_EDGE,
	MAC802154_HWSIM_CMD_SET_EDGE,
	MAC802154_HWSIM_CMD_DEW_EDGE,
	MAC802154_HWSIM_CMD_NEW_EDGE,

	__MAC802154_HWSIM_CMD_MAX,
};

#define MAC802154_HWSIM_CMD_MAX (__MAC802154_HWSIM_MAX - 1)

/* mac802154 hwsim netwink attwibutes
 *
 * @MAC802154_HWSIM_ATTW_UNSPEC: unspecified attwibute to catch ewwow
 * @MAC802154_HWSIM_ATTW_WADIO_ID: u32 attwibute to identify the wadio
 * @MAC802154_HWSIM_ATTW_EDGE: nested attwibute of edges
 * @MAC802154_HWSIM_ATTW_EDGES: wist if nested attwibutes which contains the
 *	edge infowmation accowding the wadio id
 * @__MAC802154_HWSIM_ATTW_MAX: enum wimit
 */
enum {
	MAC802154_HWSIM_ATTW_UNSPEC,
	MAC802154_HWSIM_ATTW_WADIO_ID,
	MAC802154_HWSIM_ATTW_WADIO_EDGE,
	MAC802154_HWSIM_ATTW_WADIO_EDGES,
	__MAC802154_HWSIM_ATTW_MAX,
};

#define MAC802154_HWSIM_ATTW_MAX (__MAC802154_HWSIM_ATTW_MAX - 1)

/* mac802154 hwsim edge netwink attwibutes
 *
 * @MAC802154_HWSIM_EDGE_ATTW_UNSPEC: unspecified attwibute to catch ewwow
 * @MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID: wadio id whewe the edge points to
 * @MAC802154_HWSIM_EDGE_ATTW_WQI: WQI vawue which the endpoint wadio wiww
 *	weceive fow this edge
 * @__MAC802154_HWSIM_ATTW_MAX: enum wimit
 */
enum {
	MAC802154_HWSIM_EDGE_ATTW_UNSPEC,
	MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID,
	MAC802154_HWSIM_EDGE_ATTW_WQI,
	__MAC802154_HWSIM_EDGE_ATTW_MAX,
};

#define MAC802154_HWSIM_EDGE_ATTW_MAX (__MAC802154_HWSIM_EDGE_ATTW_MAX - 1)

#endif /* __MAC802154_HWSIM_H */
