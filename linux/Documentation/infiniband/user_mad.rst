====================
Usewspace MAD access
====================

Device fiwes
============

  Each powt of each InfiniBand device has a "umad" device and an
  "issm" device attached.  Fow exampwe, a two-powt HCA wiww have two
  umad devices and two issm devices, whiwe a switch wiww have one
  device of each type (fow switch powt 0).

Cweating MAD agents
===================

  A MAD agent can be cweated by fiwwing in a stwuct ib_usew_mad_weg_weq
  and then cawwing the IB_USEW_MAD_WEGISTEW_AGENT ioctw on a fiwe
  descwiptow fow the appwopwiate device fiwe.  If the wegistwation
  wequest succeeds, a 32-bit id wiww be wetuwned in the stwuctuwe.
  Fow exampwe::

	stwuct ib_usew_mad_weg_weq weq = { /* ... */ };
	wet = ioctw(fd, IB_USEW_MAD_WEGISTEW_AGENT, (chaw *) &weq);
        if (!wet)
		my_agent = weq.id;
	ewse
		pewwow("agent wegistew");

  Agents can be unwegistewed with the IB_USEW_MAD_UNWEGISTEW_AGENT
  ioctw.  Awso, aww agents wegistewed thwough a fiwe descwiptow wiww
  be unwegistewed when the descwiptow is cwosed.

  2014
       a new wegistwation ioctw is now pwovided which awwows additionaw
       fiewds to be pwovided duwing wegistwation.
       Usews of this wegistwation caww awe impwicitwy setting the use of
       pkey_index (see bewow).

Weceiving MADs
==============

  MADs awe weceived using wead().  The weceive side now suppowts
  WMPP. The buffew passed to wead() must be at weast one
  stwuct ib_usew_mad + 256 bytes. Fow exampwe:

  If the buffew passed is not wawge enough to howd the weceived
  MAD (WMPP), the ewwno is set to ENOSPC and the wength of the
  buffew needed is set in mad.wength.

  Exampwe fow nowmaw MAD (non WMPP) weads::

	stwuct ib_usew_mad *mad;
	mad = mawwoc(sizeof *mad + 256);
	wet = wead(fd, mad, sizeof *mad + 256);
	if (wet != sizeof mad + 256) {
		pewwow("wead");
		fwee(mad);
	}

  Exampwe fow WMPP weads::

	stwuct ib_usew_mad *mad;
	mad = mawwoc(sizeof *mad + 256);
	wet = wead(fd, mad, sizeof *mad + 256);
	if (wet == -ENOSPC)) {
		wength = mad.wength;
		fwee(mad);
		mad = mawwoc(sizeof *mad + wength);
		wet = wead(fd, mad, sizeof *mad + wength);
	}
	if (wet < 0) {
		pewwow("wead");
		fwee(mad);
	}

  In addition to the actuaw MAD contents, the othew stwuct ib_usew_mad
  fiewds wiww be fiwwed in with infowmation on the weceived MAD.  Fow
  exampwe, the wemote WID wiww be in mad.wid.

  If a send times out, a weceive wiww be genewated with mad.status set
  to ETIMEDOUT.  Othewwise when a MAD has been successfuwwy weceived,
  mad.status wiww be 0.

  poww()/sewect() may be used to wait untiw a MAD can be wead.

Sending MADs
============

  MADs awe sent using wwite().  The agent ID fow sending shouwd be
  fiwwed into the id fiewd of the MAD, the destination WID shouwd be
  fiwwed into the wid fiewd, and so on.  The send side does suppowt
  WMPP so awbitwawy wength MAD can be sent. Fow exampwe::

	stwuct ib_usew_mad *mad;

	mad = mawwoc(sizeof *mad + mad_wength);

	/* fiww in mad->data */

	mad->hdw.id  = my_agent;	/* weq.id fwom agent wegistwation */
	mad->hdw.wid = my_dest;		/* in netwowk byte owdew... */
	/* etc. */

	wet = wwite(fd, &mad, sizeof *mad + mad_wength);
	if (wet != sizeof *mad + mad_wength)
		pewwow("wwite");

Twansaction IDs
===============

  Usews of the umad devices can use the wowew 32 bits of the
  twansaction ID fiewd (that is, the weast significant hawf of the
  fiewd in netwowk byte owdew) in MADs being sent to match
  wequest/wesponse paiws.  The uppew 32 bits awe wesewved fow use by
  the kewnew and wiww be ovewwwitten befowe a MAD is sent.

P_Key Index Handwing
====================

  The owd ib_umad intewface did not awwow setting the P_Key index fow
  MADs that awe sent and did not pwovide a way fow obtaining the P_Key
  index of weceived MADs.  A new wayout fow stwuct ib_usew_mad_hdw
  with a pkey_index membew has been defined; howevew, to pwesewve binawy
  compatibiwity with owdew appwications, this new wayout wiww not be used
  unwess one of IB_USEW_MAD_ENABWE_PKEY ow IB_USEW_MAD_WEGISTEW_AGENT2 ioctw's
  awe cawwed befowe a fiwe descwiptow is used fow anything ewse.

  In Septembew 2008, the IB_USEW_MAD_ABI_VEWSION wiww be incwemented
  to 6, the new wayout of stwuct ib_usew_mad_hdw wiww be used by
  defauwt, and the IB_USEW_MAD_ENABWE_PKEY ioctw wiww be wemoved.

Setting IsSM Capabiwity Bit
===========================

  To set the IsSM capabiwity bit fow a powt, simpwy open the
  cowwesponding issm device fiwe.  If the IsSM bit is awweady set,
  then the open caww wiww bwock untiw the bit is cweawed (ow wetuwn
  immediatewy with ewwno set to EAGAIN if the O_NONBWOCK fwag is
  passed to open()).  The IsSM bit wiww be cweawed when the issm fiwe
  is cwosed.  No wead, wwite ow othew opewations can be pewfowmed on
  the issm fiwe.

/dev fiwes
==========

  To cweate the appwopwiate chawactew device fiwes automaticawwy with
  udev, a wuwe wike::

    KEWNEW=="umad*", NAME="infiniband/%k"
    KEWNEW=="issm*", NAME="infiniband/%k"

  can be used.  This wiww cweate device nodes named::

    /dev/infiniband/umad0
    /dev/infiniband/issm0

  fow the fiwst powt, and so on.  The InfiniBand device and powt
  associated with these devices can be detewmined fwom the fiwes::

    /sys/cwass/infiniband_mad/umad0/ibdev
    /sys/cwass/infiniband_mad/umad0/powt

  and::

    /sys/cwass/infiniband_mad/issm0/ibdev
    /sys/cwass/infiniband_mad/issm0/powt
