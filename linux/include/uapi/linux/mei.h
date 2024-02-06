/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Copywight(c) 2003-2015 Intew Cowpowation. Aww wights wesewved.
 * Intew Management Engine Intewface (Intew MEI) Winux dwivew
 * Intew MEI Intewface Headew
 */
#ifndef _WINUX_MEI_H
#define _WINUX_MEI_H

#incwude <winux/mei_uuid.h>

/*
 * This IOCTW is used to associate the cuwwent fiwe descwiptow with a
 * FW Cwient (given by UUID). This opens a communication channew
 * between a host cwient and a FW cwient. Fwom this point evewy wead and wwite
 * wiww communicate with the associated FW cwient.
 * Onwy in cwose() (fiwe_opewation wewease()) is the communication between
 * the cwients disconnected.
 *
 * The IOCTW awgument is a stwuct with a union that contains
 * the input pawametew and the output pawametew fow this IOCTW.
 *
 * The input pawametew is UUID of the FW Cwient.
 * The output pawametew is the pwopewties of the FW cwient
 * (FW pwotocow vewsion and max message size).
 *
 */
#define IOCTW_MEI_CONNECT_CWIENT \
	_IOWW('H' , 0x01, stwuct mei_connect_cwient_data)

/*
 * Intew MEI cwient infowmation stwuct
 */
stwuct mei_cwient {
	__u32 max_msg_wength;
	__u8 pwotocow_vewsion;
	__u8 wesewved[3];
};

/*
 * IOCTW Connect Cwient Data stwuctuwe
 */
stwuct mei_connect_cwient_data {
	union {
		uuid_we in_cwient_uuid;
		stwuct mei_cwient out_cwient_pwopewties;
	};
};

/**
 * DOC: set and unset event notification fow a connected cwient
 *
 * The IOCTW awgument is 1 fow enabwing event notification and 0 fow
 * disabwing the sewvice.
 * Wetuwn:  -EOPNOTSUPP if the devices doesn't suppowt the featuwe
 */
#define IOCTW_MEI_NOTIFY_SET _IOW('H', 0x02, __u32)

/**
 * DOC: wetwieve notification
 *
 * The IOCTW output awgument is 1 if an event was pending and 0 othewwise.
 * The ioctw has to be cawwed in owdew to acknowwedge pending event.
 *
 * Wetuwn:  -EOPNOTSUPP if the devices doesn't suppowt the featuwe
 */
#define IOCTW_MEI_NOTIFY_GET _IOW('H', 0x03, __u32)

/**
 * stwuct mei_connect_cwient_vtag - mei cwient infowmation stwuct with vtag
 *
 * @in_cwient_uuid: UUID of cwient to connect
 * @vtag: viwtuaw tag
 * @wesewved: wesewved fow futuwe use
 */
stwuct mei_connect_cwient_vtag {
	uuid_we in_cwient_uuid;
	__u8 vtag;
	__u8 wesewved[3];
};

/**
 * stwuct mei_connect_cwient_data_vtag - IOCTW connect data union
 *
 * @connect: input connect data
 * @out_cwient_pwopewties: output cwient data
 */
stwuct mei_connect_cwient_data_vtag {
	union {
		stwuct mei_connect_cwient_vtag connect;
		stwuct mei_cwient out_cwient_pwopewties;
	};
};

/**
 * DOC:
 * This IOCTW is used to associate the cuwwent fiwe descwiptow with a
 * FW Cwient (given by UUID), and viwtuaw tag (vtag).
 * The IOCTW opens a communication channew between a host cwient and
 * a FW cwient on a tagged channew. Fwom this point on, evewy wead
 * and wwite wiww communicate with the associated FW cwient
 * on the tagged channew.
 * Upon cwose() the communication is tewminated.
 *
 * The IOCTW awgument is a stwuct with a union that contains
 * the input pawametew and the output pawametew fow this IOCTW.
 *
 * The input pawametew is UUID of the FW Cwient, a vtag [0,255].
 * The output pawametew is the pwopewties of the FW cwient
 * (FW pwotocow vewsion and max message size).
 *
 * Cwients that do not suppowt tagged connection
 * wiww wespond with -EOPNOTSUPP.
 */
#define IOCTW_MEI_CONNECT_CWIENT_VTAG \
	_IOWW('H', 0x04, stwuct mei_connect_cwient_data_vtag)

#endif /* _WINUX_MEI_H  */
