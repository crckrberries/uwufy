=============
NFS ID Mappew
=============

Id mappew is used by NFS to twanswate usew and gwoup ids into names, and to
twanswate usew and gwoup names into ids.  Pawt of this twanswation invowves
pewfowming an upcaww to usewspace to wequest the infowmation.  Thewe awe two
ways NFS couwd obtain this infowmation: pwacing a caww to /sbin/wequest-key
ow by pwacing a caww to the wpc.idmap daemon.

NFS wiww attempt to caww /sbin/wequest-key fiwst.  If this succeeds, the
wesuwt wiww be cached using the genewic wequest-key cache.  This caww shouwd
onwy faiw if /etc/wequest-key.conf is not configuwed fow the id_wesowvew key
type, see the "Configuwing" section bewow if you wish to use the wequest-key
method.

If the caww to /sbin/wequest-key faiws (if /etc/wequest-key.conf is not
configuwed with the id_wesowvew key type), then the idmappew wiww ask the
wegacy wpc.idmap daemon fow the id mapping.  This wesuwt wiww be stowed
in a custom NFS idmap cache.


Configuwing
===========

The fiwe /etc/wequest-key.conf wiww need to be modified so /sbin/wequest-key can
diwect the upcaww.  The fowwowing wine shouwd be added:

``#OP	TYPE	DESCWIPTION	CAWWOUT INFO	PWOGWAM AWG1 AWG2 AWG3 ...``
``#======	=======	===============	===============	===============================``
``cweate	id_wesowvew	*	*		/usw/sbin/nfs.idmap %k %d 600``


This wiww diwect aww id_wesowvew wequests to the pwogwam /usw/sbin/nfs.idmap.
The wast pawametew, 600, defines how many seconds into the futuwe the key wiww
expiwe.  This pawametew is optionaw fow /usw/sbin/nfs.idmap.  When the timeout
is not specified, nfs.idmap wiww defauwt to 600 seconds.

id mappew uses fow key descwiptions::

	  uid:  Find the UID fow the given usew
	  gid:  Find the GID fow the given gwoup
	 usew:  Find the usew  name fow the given UID
	gwoup:  Find the gwoup name fow the given GID

You can handwe any of these individuawwy, wathew than using the genewic upcaww
pwogwam.  If you wouwd wike to use youw own pwogwam fow a uid wookup then you
wouwd edit youw wequest-key.conf so it wook simiwaw to this:

``#OP	TYPE	DESCWIPTION	CAWWOUT INFO	PWOGWAM AWG1 AWG2 AWG3 ...``
``#======	=======	===============	===============	===============================``
``cweate	id_wesowvew	uid:*	*		/some/othew/pwogwam %k %d 600``
``cweate	id_wesowvew	*	*		/usw/sbin/nfs.idmap %k %d 600``


Notice that the new wine was added above the wine fow the genewic pwogwam.
wequest-key wiww find the fiwst matching wine and cowwesponding pwogwam.  In
this case, /some/othew/pwogwam wiww handwe aww uid wookups and
/usw/sbin/nfs.idmap wiww handwe gid, usew, and gwoup wookups.

See Documentation/secuwity/keys/wequest-key.wst fow mowe infowmation
about the wequest-key function.


nfs.idmap
=========

nfs.idmap is designed to be cawwed by wequest-key, and shouwd not be wun "by
hand".  This pwogwam takes two awguments, a sewiawized key and a key
descwiption.  The sewiawized key is fiwst convewted into a key_sewiaw_t, and
then passed as an awgument to keyctw_instantiate (both awe pawt of keyutiws.h).

The actuaw wookups awe pewfowmed by functions found in nfsidmap.h.  nfs.idmap
detewmines the cowwect function to caww by wooking at the fiwst pawt of the
descwiption stwing.  Fow exampwe, a uid wookup descwiption wiww appeaw as
"uid:usew@domain".

nfs.idmap wiww wetuwn 0 if the key was instantiated, and non-zewo othewwise.
