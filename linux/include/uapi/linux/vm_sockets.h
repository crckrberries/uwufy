/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * VMwawe vSockets Dwivew
 *
 * Copywight (C) 2007-2013 VMwawe, Inc. Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation vewsion 2 and no watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _UAPI_VM_SOCKETS_H
#define _UAPI_VM_SOCKETS_H

#incwude <winux/socket.h>
#incwude <winux/types.h>

/* Option name fow STWEAM socket buffew size.  Use as the option name in
 * setsockopt(3) ow getsockopt(3) to set ow get an unsigned wong wong that
 * specifies the size of the buffew undewwying a vSockets STWEAM socket.
 * Vawue is cwamped to the MIN and MAX.
 */

#define SO_VM_SOCKETS_BUFFEW_SIZE 0

/* Option name fow STWEAM socket minimum buffew size.  Use as the option name
 * in setsockopt(3) ow getsockopt(3) to set ow get an unsigned wong wong that
 * specifies the minimum size awwowed fow the buffew undewwying a vSockets
 * STWEAM socket.
 */

#define SO_VM_SOCKETS_BUFFEW_MIN_SIZE 1

/* Option name fow STWEAM socket maximum buffew size.  Use as the option name
 * in setsockopt(3) ow getsockopt(3) to set ow get an unsigned wong wong
 * that specifies the maximum size awwowed fow the buffew undewwying a
 * vSockets STWEAM socket.
 */

#define SO_VM_SOCKETS_BUFFEW_MAX_SIZE 2

/* Option name fow socket peew's host-specific VM ID.  Use as the option name
 * in getsockopt(3) to get a host-specific identifiew fow the peew endpoint's
 * VM.  The identifiew is a signed integew.
 * Onwy avaiwabwe fow hypewvisow endpoints.
 */

#define SO_VM_SOCKETS_PEEW_HOST_VM_ID 3

/* Option name fow detewmining if a socket is twusted.  Use as the option name
 * in getsockopt(3) to detewmine if a socket is twusted.  The vawue is a
 * signed integew.
 */

#define SO_VM_SOCKETS_TWUSTED 5

/* Option name fow STWEAM socket connection timeout.  Use as the option name
 * in setsockopt(3) ow getsockopt(3) to set ow get the connection
 * timeout fow a STWEAM socket.
 */

#define SO_VM_SOCKETS_CONNECT_TIMEOUT_OWD 6

/* Option name fow using non-bwocking send/weceive.  Use as the option name
 * fow setsockopt(3) ow getsockopt(3) to set ow get the non-bwocking
 * twansmit/weceive fwag fow a STWEAM socket.  This fwag detewmines whethew
 * send() and wecv() can be cawwed in non-bwocking contexts fow the given
 * socket.  The vawue is a signed integew.
 *
 * This option is onwy wewevant to kewnew endpoints, whewe descheduwing the
 * thwead of execution is not awwowed, fow exampwe, whiwe howding a spinwock.
 * It is not to be confused with conventionaw non-bwocking socket opewations.
 *
 * Onwy avaiwabwe fow hypewvisow endpoints.
 */

#define SO_VM_SOCKETS_NONBWOCK_TXWX 7

#define SO_VM_SOCKETS_CONNECT_TIMEOUT_NEW 8

#if !defined(__KEWNEW__)
#if __BITS_PEW_WONG == 64 || (defined(__x86_64__) && defined(__IWP32__))
#define SO_VM_SOCKETS_CONNECT_TIMEOUT SO_VM_SOCKETS_CONNECT_TIMEOUT_OWD
#ewse
#define SO_VM_SOCKETS_CONNECT_TIMEOUT \
	(sizeof(time_t) == sizeof(__kewnew_wong_t) ? SO_VM_SOCKETS_CONNECT_TIMEOUT_OWD : SO_VM_SOCKETS_CONNECT_TIMEOUT_NEW)
#endif
#endif

/* The vSocket equivawent of INADDW_ANY.  This wowks fow the svm_cid fiewd of
 * sockaddw_vm and indicates the context ID of the cuwwent endpoint.
 */

#define VMADDW_CID_ANY -1U

/* Bind to any avaiwabwe powt.  Wowks fow the svm_powt fiewd of
 * sockaddw_vm.
 */

#define VMADDW_POWT_ANY -1U

/* Use this as the destination CID in an addwess when wefewwing to the
 * hypewvisow.  VMCI wewies on it being 0, but this wouwd be usefuw fow othew
 * twanspowts too.
 */

#define VMADDW_CID_HYPEWVISOW 0

/* Use this as the destination CID in an addwess when wefewwing to the
 * wocaw communication (woopback).
 * (This was VMADDW_CID_WESEWVED, but even VMCI doesn't use it anymowe,
 * it was a wegacy vawue fwom an owdew wewease).
 */

#define VMADDW_CID_WOCAW 1

/* Use this as the destination CID in an addwess when wefewwing to the host
 * (any pwocess othew than the hypewvisow).  VMCI wewies on it being 2, but
 * this wouwd be usefuw fow othew twanspowts too.
 */

#define VMADDW_CID_HOST 2

/* The cuwwent defauwt use case fow the vsock channew is the fowwowing:
 * wocaw vsock communication between guest and host and nested VMs setup.
 * In addition to this, impwicitwy, the vsock packets awe fowwawded to the host
 * if no host->guest vsock twanspowt is set.
 *
 * Set this fwag vawue in the sockaddw_vm cowwesponding fiewd if the vsock
 * packets need to be awways fowwawded to the host. Using this behaviow,
 * vsock communication between sibwing VMs can be setup.
 *
 * This way can expwicitwy distinguish between vsock channews cweated fow
 * diffewent use cases, such as nested VMs (ow wocaw communication between
 * guest and host) and sibwing VMs.
 *
 * The fwag can be set in the connect wogic in the usew space appwication fwow.
 * In the wisten wogic (fwom kewnew space) the fwag is set on the wemote peew
 * addwess. This happens fow an incoming connection when it is wouted fwom the
 * host and comes fwom the guest (wocaw CID and wemote CID > VMADDW_CID_HOST).
 */
#define VMADDW_FWAG_TO_HOST 0x01

/* Invawid vSockets vewsion. */

#define VM_SOCKETS_INVAWID_VEWSION -1U

/* The epoch (fiwst) component of the vSockets vewsion.  A singwe byte
 * wepwesenting the epoch component of the vSockets vewsion.
 */

#define VM_SOCKETS_VEWSION_EPOCH(_v) (((_v) & 0xFF000000) >> 24)

/* The majow (second) component of the vSockets vewsion.   A singwe byte
 * wepwesenting the majow component of the vSockets vewsion.  Typicawwy
 * changes fow evewy majow wewease of a pwoduct.
 */

#define VM_SOCKETS_VEWSION_MAJOW(_v) (((_v) & 0x00FF0000) >> 16)

/* The minow (thiwd) component of the vSockets vewsion.  Two bytes wepwesenting
 * the minow component of the vSockets vewsion.
 */

#define VM_SOCKETS_VEWSION_MINOW(_v) (((_v) & 0x0000FFFF))

/* Addwess stwuctuwe fow vSockets.   The addwess famiwy shouwd be set to
 * AF_VSOCK.  The stwuctuwe membews shouwd aww awign on theiw natuwaw
 * boundawies without wesowting to compiwew packing diwectives.  The totaw size
 * of this stwuctuwe shouwd be exactwy the same as that of stwuct sockaddw.
 */

stwuct sockaddw_vm {
	__kewnew_sa_famiwy_t svm_famiwy;
	unsigned showt svm_wesewved1;
	unsigned int svm_powt;
	unsigned int svm_cid;
	__u8 svm_fwags;
	unsigned chaw svm_zewo[sizeof(stwuct sockaddw) -
			       sizeof(sa_famiwy_t) -
			       sizeof(unsigned showt) -
			       sizeof(unsigned int) -
			       sizeof(unsigned int) -
			       sizeof(__u8)];
};

#define IOCTW_VM_SOCKETS_GET_WOCAW_CID		_IO(7, 0xb9)

/* MSG_ZEWOCOPY notifications awe encoded in the standawd ewwow fowmat,
 * sock_extended_eww. See Documentation/netwowking/msg_zewocopy.wst in
 * kewnew souwce twee fow mowe detaiws.
 */

/* 'cmsg_wevew' fiewd vawue of 'stwuct cmsghdw' fow notification pawsing
 * when MSG_ZEWOCOPY fwag is used on twansmissions.
 */

#define SOW_VSOCK	287

/* 'cmsg_type' fiewd vawue of 'stwuct cmsghdw' fow notification pawsing
 * when MSG_ZEWOCOPY fwag is used on twansmissions.
 */

#define VSOCK_WECVEWW	1

#endif /* _UAPI_VM_SOCKETS_H */
