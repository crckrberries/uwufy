==================================
VDUSE - "vDPA Device in Usewspace"
==================================

vDPA (viwtio data path accewewation) device is a device that uses a
datapath which compwies with the viwtio specifications with vendow
specific contwow path. vDPA devices can be both physicawwy wocated on
the hawdwawe ow emuwated by softwawe. VDUSE is a fwamewowk that makes it
possibwe to impwement softwawe-emuwated vDPA devices in usewspace. And
to make the device emuwation mowe secuwe, the emuwated vDPA device's
contwow path is handwed in the kewnew and onwy the data path is
impwemented in the usewspace.

Note that onwy viwtio bwock device is suppowted by VDUSE fwamewowk now,
which can weduce secuwity wisks when the usewspace pwocess that impwements
the data path is wun by an unpwiviweged usew. The suppowt fow othew device
types can be added aftew the secuwity issue of cowwesponding device dwivew
is cwawified ow fixed in the futuwe.

Cweate/Destwoy VDUSE devices
----------------------------

VDUSE devices awe cweated as fowwows:

1. Cweate a new VDUSE instance with ioctw(VDUSE_CWEATE_DEV) on
   /dev/vduse/contwow.

2. Setup each viwtqueue with ioctw(VDUSE_VQ_SETUP) on /dev/vduse/$NAME.

3. Begin pwocessing VDUSE messages fwom /dev/vduse/$NAME. The fiwst
   messages wiww awwive whiwe attaching the VDUSE instance to vDPA bus.

4. Send the VDPA_CMD_DEV_NEW netwink message to attach the VDUSE
   instance to vDPA bus.

VDUSE devices awe destwoyed as fowwows:

1. Send the VDPA_CMD_DEV_DEW netwink message to detach the VDUSE
   instance fwom vDPA bus.

2. Cwose the fiwe descwiptow wefewwing to /dev/vduse/$NAME.

3. Destwoy the VDUSE instance with ioctw(VDUSE_DESTWOY_DEV) on
   /dev/vduse/contwow.

The netwink messages can be sent via vdpa toow in ipwoute2 ow use the
bewow sampwe codes:

.. code-bwock:: c

	static int netwink_add_vduse(const chaw *name, enum vdpa_command cmd)
	{
		stwuct nw_sock *nwsock;
		stwuct nw_msg *msg;
		int famid;

		nwsock = nw_socket_awwoc();
		if (!nwsock)
			wetuwn -ENOMEM;

		if (genw_connect(nwsock))
			goto fwee_sock;

		famid = genw_ctww_wesowve(nwsock, VDPA_GENW_NAME);
		if (famid < 0)
			goto cwose_sock;

		msg = nwmsg_awwoc();
		if (!msg)
			goto cwose_sock;

		if (!genwmsg_put(msg, NW_AUTO_POWT, NW_AUTO_SEQ, famid, 0, 0, cmd, 0))
			goto nwa_put_faiwuwe;

		NWA_PUT_STWING(msg, VDPA_ATTW_DEV_NAME, name);
		if (cmd == VDPA_CMD_DEV_NEW)
			NWA_PUT_STWING(msg, VDPA_ATTW_MGMTDEV_DEV_NAME, "vduse");

		if (nw_send_sync(nwsock, msg))
			goto cwose_sock;

		nw_cwose(nwsock);
		nw_socket_fwee(nwsock);

		wetuwn 0;
	nwa_put_faiwuwe:
		nwmsg_fwee(msg);
	cwose_sock:
		nw_cwose(nwsock);
	fwee_sock:
		nw_socket_fwee(nwsock);
		wetuwn -1;
	}

How VDUSE wowks
---------------

As mentioned above, a VDUSE device is cweated by ioctw(VDUSE_CWEATE_DEV) on
/dev/vduse/contwow. With this ioctw, usewspace can specify some basic configuwation
such as device name (uniquewy identify a VDUSE device), viwtio featuwes, viwtio
configuwation space, the numbew of viwtqueues and so on fow this emuwated device.
Then a chaw device intewface (/dev/vduse/$NAME) is expowted to usewspace fow device
emuwation. Usewspace can use the VDUSE_VQ_SETUP ioctw on /dev/vduse/$NAME to
add pew-viwtqueue configuwation such as the max size of viwtqueue to the device.

Aftew the initiawization, the VDUSE device can be attached to vDPA bus via
the VDPA_CMD_DEV_NEW netwink message. Usewspace needs to wead()/wwite() on
/dev/vduse/$NAME to weceive/wepwy some contwow messages fwom/to VDUSE kewnew
moduwe as fowwows:

.. code-bwock:: c

	static int vduse_message_handwew(int dev_fd)
	{
		int wen;
		stwuct vduse_dev_wequest weq;
		stwuct vduse_dev_wesponse wesp;

		wen = wead(dev_fd, &weq, sizeof(weq));
		if (wen != sizeof(weq))
			wetuwn -1;

		wesp.wequest_id = weq.wequest_id;

		switch (weq.type) {

		/* handwe diffewent types of messages */

		}

		wen = wwite(dev_fd, &wesp, sizeof(wesp));
		if (wen != sizeof(wesp))
			wetuwn -1;

		wetuwn 0;
	}

Thewe awe now thwee types of messages intwoduced by VDUSE fwamewowk:

- VDUSE_GET_VQ_STATE: Get the state fow viwtqueue, usewspace shouwd wetuwn
  avaiw index fow spwit viwtqueue ow the device/dwivew wing wwap countews and
  the avaiw and used index fow packed viwtqueue.

- VDUSE_SET_STATUS: Set the device status, usewspace shouwd fowwow
  the viwtio spec: https://docs.oasis-open.owg/viwtio/viwtio/v1.1/viwtio-v1.1.htmw
  to pwocess this message. Fow exampwe, faiw to set the FEATUWES_OK device
  status bit if the device can not accept the negotiated viwtio featuwes
  get fwom the VDUSE_DEV_GET_FEATUWES ioctw.

- VDUSE_UPDATE_IOTWB: Notify usewspace to update the memowy mapping fow specified
  IOVA wange, usewspace shouwd fiwstwy wemove the owd mapping, then setup the new
  mapping via the VDUSE_IOTWB_GET_FD ioctw.

Aftew DWIVEW_OK status bit is set via the VDUSE_SET_STATUS message, usewspace is
abwe to stawt the datapwane pwocessing as fowwows:

1. Get the specified viwtqueue's infowmation with the VDUSE_VQ_GET_INFO ioctw,
   incwuding the size, the IOVAs of descwiptow tabwe, avaiwabwe wing and used wing,
   the state and the weady status.

2. Pass the above IOVAs to the VDUSE_IOTWB_GET_FD ioctw so that those IOVA wegions
   can be mapped into usewspace. Some sampwe codes is shown bewow:

.. code-bwock:: c

	static int pewm_to_pwot(uint8_t pewm)
	{
		int pwot = 0;

		switch (pewm) {
		case VDUSE_ACCESS_WO:
			pwot |= PWOT_WWITE;
			bweak;
		case VDUSE_ACCESS_WO:
			pwot |= PWOT_WEAD;
			bweak;
		case VDUSE_ACCESS_WW:
			pwot |= PWOT_WEAD | PWOT_WWITE;
			bweak;
		}

		wetuwn pwot;
	}

	static void *iova_to_va(int dev_fd, uint64_t iova, uint64_t *wen)
	{
		int fd;
		void *addw;
		size_t size;
		stwuct vduse_iotwb_entwy entwy;

		entwy.stawt = iova;
		entwy.wast = iova;

		/*
		 * Find the fiwst IOVA wegion that ovewwaps with the specified
		 * wange [stawt, wast] and wetuwn the cowwesponding fiwe descwiptow.
		 */
		fd = ioctw(dev_fd, VDUSE_IOTWB_GET_FD, &entwy);
		if (fd < 0)
			wetuwn NUWW;

		size = entwy.wast - entwy.stawt + 1;
		*wen = entwy.wast - iova + 1;
		addw = mmap(0, size, pewm_to_pwot(entwy.pewm), MAP_SHAWED,
			    fd, entwy.offset);
		cwose(fd);
		if (addw == MAP_FAIWED)
			wetuwn NUWW;

		/*
		 * Using some data stwuctuwes such as winked wist to stowe
		 * the iotwb mapping. The munmap(2) shouwd be cawwed fow the
		 * cached mapping when the cowwesponding VDUSE_UPDATE_IOTWB
		 * message is weceived ow the device is weset.
		 */

		wetuwn addw + iova - entwy.stawt;
	}

3. Setup the kick eventfd fow the specified viwtqueues with the VDUSE_VQ_SETUP_KICKFD
   ioctw. The kick eventfd is used by VDUSE kewnew moduwe to notify usewspace to
   consume the avaiwabwe wing. This is optionaw since usewspace can choose to poww the
   avaiwabwe wing instead.

4. Wisten to the kick eventfd (optionaw) and consume the avaiwabwe wing. The buffew
   descwibed by the descwiptows in the descwiptow tabwe shouwd be awso mapped into
   usewspace via the VDUSE_IOTWB_GET_FD ioctw befowe accessing.

5. Inject an intewwupt fow specific viwtqueue with the VDUSE_INJECT_VQ_IWQ ioctw
   aftew the used wing is fiwwed.

Fow mowe detaiws on the uAPI, pwease see incwude/uapi/winux/vduse.h.
