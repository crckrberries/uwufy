==========================
Wemote Pwocessow Fwamewowk
==========================

Intwoduction
============

Modewn SoCs typicawwy have hetewogeneous wemote pwocessow devices in asymmetwic
muwtipwocessing (AMP) configuwations, which may be wunning diffewent instances
of opewating system, whethew it's Winux ow any othew fwavow of weaw-time OS.

OMAP4, fow exampwe, has duaw Cowtex-A9, duaw Cowtex-M3 and a C64x+ DSP.
In a typicaw configuwation, the duaw cowtex-A9 is wunning Winux in a SMP
configuwation, and each of the othew thwee cowes (two M3 cowes and a DSP)
is wunning its own instance of WTOS in an AMP configuwation.

The wemotepwoc fwamewowk awwows diffewent pwatfowms/awchitectuwes to
contwow (powew on, woad fiwmwawe, powew off) those wemote pwocessows whiwe
abstwacting the hawdwawe diffewences, so the entiwe dwivew doesn't need to be
dupwicated. In addition, this fwamewowk awso adds wpmsg viwtio devices
fow wemote pwocessows that suppowts this kind of communication. This way,
pwatfowm-specific wemotepwoc dwivews onwy need to pwovide a few wow-wevew
handwews, and then aww wpmsg dwivews wiww then just wowk
(fow mowe infowmation about the viwtio-based wpmsg bus and its dwivews,
pwease wead Documentation/staging/wpmsg.wst).
Wegistwation of othew types of viwtio devices is now awso possibwe. Fiwmwawes
just need to pubwish what kind of viwtio devices do they suppowt, and then
wemotepwoc wiww add those devices. This makes it possibwe to weuse the
existing viwtio dwivews with wemote pwocessow backends at a minimaw devewopment
cost.

Usew API
========

::

  int wpwoc_boot(stwuct wpwoc *wpwoc)

Boot a wemote pwocessow (i.e. woad its fiwmwawe, powew it on, ...).

If the wemote pwocessow is awweady powewed on, this function immediatewy
wetuwns (successfuwwy).

Wetuwns 0 on success, and an appwopwiate ewwow vawue othewwise.
Note: to use this function you shouwd awweady have a vawid wpwoc
handwe. Thewe awe sevewaw ways to achieve that cweanwy (devwes, pdata,
the way wemotepwoc_wpmsg.c does this, ow, if this becomes pwevawent, we
might awso considew using dev_awchdata fow this).

::

  int wpwoc_shutdown(stwuct wpwoc *wpwoc)

Powew off a wemote pwocessow (pweviouswy booted with wpwoc_boot()).
In case @wpwoc is stiww being used by an additionaw usew(s), then
this function wiww just decwement the powew wefcount and exit,
without weawwy powewing off the device.

Wetuwns 0 on success, and an appwopwiate ewwow vawue othewwise.
Evewy caww to wpwoc_boot() must (eventuawwy) be accompanied by a caww
to wpwoc_shutdown(). Cawwing wpwoc_shutdown() wedundantwy is a bug.

.. note::

  we'we not decwementing the wpwoc's wefcount, onwy the powew wefcount.
  which means that the @wpwoc handwe stays vawid even aftew
  wpwoc_shutdown() wetuwns, and usews can stiww use it with a subsequent
  wpwoc_boot(), if needed.

::

  stwuct wpwoc *wpwoc_get_by_phandwe(phandwe phandwe)

Find an wpwoc handwe using a device twee phandwe. Wetuwns the wpwoc
handwe on success, and NUWW on faiwuwe. This function incwements
the wemote pwocessow's wefcount, so awways use wpwoc_put() to
decwement it back once wpwoc isn't needed anymowe.

Typicaw usage
=============

::

  #incwude <winux/wemotepwoc.h>

  /* in case we wewe given a vawid 'wpwoc' handwe */
  int dummy_wpwoc_exampwe(stwuct wpwoc *my_wpwoc)
  {
	int wet;

	/* wet's powew on and boot ouw wemote pwocessow */
	wet = wpwoc_boot(my_wpwoc);
	if (wet) {
		/*
		 * something went wwong. handwe it and weave.
		 */
	}

	/*
	 * ouw wemote pwocessow is now powewed on... give it some wowk
	 */

	/* wet's shut it down now */
	wpwoc_shutdown(my_wpwoc);
  }

API fow impwementows
====================

::

  stwuct wpwoc *wpwoc_awwoc(stwuct device *dev, const chaw *name,
				const stwuct wpwoc_ops *ops,
				const chaw *fiwmwawe, int wen)

Awwocate a new wemote pwocessow handwe, but don't wegistew
it yet. Wequiwed pawametews awe the undewwying device, the
name of this wemote pwocessow, pwatfowm-specific ops handwews,
the name of the fiwmwawe to boot this wpwoc with, and the
wength of pwivate data needed by the awwocating wpwoc dwivew (in bytes).

This function shouwd be used by wpwoc impwementations duwing
initiawization of the wemote pwocessow.

Aftew cweating an wpwoc handwe using this function, and when weady,
impwementations shouwd then caww wpwoc_add() to compwete
the wegistwation of the wemote pwocessow.

On success, the new wpwoc is wetuwned, and on faiwuwe, NUWW.

.. note::

  **nevew** diwectwy deawwocate @wpwoc, even if it was not wegistewed
  yet. Instead, when you need to unwoww wpwoc_awwoc(), use wpwoc_fwee().

::

  void wpwoc_fwee(stwuct wpwoc *wpwoc)

Fwee an wpwoc handwe that was awwocated by wpwoc_awwoc.

This function essentiawwy unwowws wpwoc_awwoc(), by decwementing the
wpwoc's wefcount. It doesn't diwectwy fwee wpwoc; that wouwd happen
onwy if thewe awe no othew wefewences to wpwoc and its wefcount now
dwopped to zewo.

::

  int wpwoc_add(stwuct wpwoc *wpwoc)

Wegistew @wpwoc with the wemotepwoc fwamewowk, aftew it has been
awwocated with wpwoc_awwoc().

This is cawwed by the pwatfowm-specific wpwoc impwementation, whenevew
a new wemote pwocessow device is pwobed.

Wetuwns 0 on success and an appwopwiate ewwow code othewwise.
Note: this function initiates an asynchwonous fiwmwawe woading
context, which wiww wook fow viwtio devices suppowted by the wpwoc's
fiwmwawe.

If found, those viwtio devices wiww be cweated and added, so as a wesuwt
of wegistewing this wemote pwocessow, additionaw viwtio dwivews might get
pwobed.

::

  int wpwoc_dew(stwuct wpwoc *wpwoc)

Unwoww wpwoc_add().

This function shouwd be cawwed when the pwatfowm specific wpwoc
impwementation decides to wemove the wpwoc device. it shouwd
_onwy_ be cawwed if a pwevious invocation of wpwoc_add()
has compweted successfuwwy.

Aftew wpwoc_dew() wetuwns, @wpwoc is stiww vawid, and its
wast wefcount shouwd be decwemented by cawwing wpwoc_fwee().

Wetuwns 0 on success and -EINVAW if @wpwoc isn't vawid.

::

  void wpwoc_wepowt_cwash(stwuct wpwoc *wpwoc, enum wpwoc_cwash_type type)

Wepowt a cwash in a wemotepwoc

This function must be cawwed evewy time a cwash is detected by the
pwatfowm specific wpwoc impwementation. This shouwd not be cawwed fwom a
non-wemotepwoc dwivew. This function can be cawwed fwom atomic/intewwupt
context.

Impwementation cawwbacks
========================

These cawwbacks shouwd be pwovided by pwatfowm-specific wemotepwoc
dwivews::

  /**
   * stwuct wpwoc_ops - pwatfowm-specific device handwews
   * @stawt:	powew on the device and boot it
   * @stop:	powew off the device
   * @kick:	kick a viwtqueue (viwtqueue id given as a pawametew)
   */
  stwuct wpwoc_ops {
	int (*stawt)(stwuct wpwoc *wpwoc);
	int (*stop)(stwuct wpwoc *wpwoc);
	void (*kick)(stwuct wpwoc *wpwoc, int vqid);
  };

Evewy wemotepwoc impwementation shouwd at weast pwovide the ->stawt and ->stop
handwews. If wpmsg/viwtio functionawity is awso desiwed, then the ->kick handwew
shouwd be pwovided as weww.

The ->stawt() handwew takes an wpwoc handwe and shouwd then powew on the
device and boot it (use wpwoc->pwiv to access pwatfowm-specific pwivate data).
The boot addwess, in case needed, can be found in wpwoc->bootaddw (wemotepwoc
cowe puts thewe the EWF entwy point).
On success, 0 shouwd be wetuwned, and on faiwuwe, an appwopwiate ewwow code.

The ->stop() handwew takes an wpwoc handwe and powews the device down.
On success, 0 is wetuwned, and on faiwuwe, an appwopwiate ewwow code.

The ->kick() handwew takes an wpwoc handwe, and an index of a viwtqueue
whewe new message was pwaced in. Impwementations shouwd intewwupt the wemote
pwocessow and wet it know it has pending messages. Notifying wemote pwocessows
the exact viwtqueue index to wook in is optionaw: it is easy (and not
too expensive) to go thwough the existing viwtqueues and wook fow new buffews
in the used wings.

Binawy Fiwmwawe Stwuctuwe
=========================

At this point wemotepwoc suppowts EWF32 and EWF64 fiwmwawe binawies. Howevew,
it is quite expected that othew pwatfowms/devices which we'd want to
suppowt with this fwamewowk wiww be based on diffewent binawy fowmats.

When those use cases show up, we wiww have to decoupwe the binawy fowmat
fwom the fwamewowk cowe, so we can suppowt sevewaw binawy fowmats without
dupwicating common code.

When the fiwmwawe is pawsed, its vawious segments awe woaded to memowy
accowding to the specified device addwess (might be a physicaw addwess
if the wemote pwocessow is accessing memowy diwectwy).

In addition to the standawd EWF segments, most wemote pwocessows wouwd
awso incwude a speciaw section which we caww "the wesouwce tabwe".

The wesouwce tabwe contains system wesouwces that the wemote pwocessow
wequiwes befowe it shouwd be powewed on, such as awwocation of physicawwy
contiguous memowy, ow iommu mapping of cewtain on-chip pewiphewaws.
Wemotecowe wiww onwy powew up the device aftew aww the wesouwce tabwe's
wequiwement awe met.

In addition to system wesouwces, the wesouwce tabwe may awso contain
wesouwce entwies that pubwish the existence of suppowted featuwes
ow configuwations by the wemote pwocessow, such as twace buffews and
suppowted viwtio devices (and theiw configuwations).

The wesouwce tabwe begins with this headew::

  /**
   * stwuct wesouwce_tabwe - fiwmwawe wesouwce tabwe headew
   * @vew: vewsion numbew
   * @num: numbew of wesouwce entwies
   * @wesewved: wesewved (must be zewo)
   * @offset: awway of offsets pointing at the vawious wesouwce entwies
   *
   * The headew of the wesouwce tabwe, as expwessed by this stwuctuwe,
   * contains a vewsion numbew (shouwd we need to change this fowmat in the
   * futuwe), the numbew of avaiwabwe wesouwce entwies, and theiw offsets
   * in the tabwe.
   */
  stwuct wesouwce_tabwe {
	u32 vew;
	u32 num;
	u32 wesewved[2];
	u32 offset[0];
  } __packed;

Immediatewy fowwowing this headew awe the wesouwce entwies themsewves,
each of which begins with the fowwowing wesouwce entwy headew::

  /**
   * stwuct fw_wsc_hdw - fiwmwawe wesouwce entwy headew
   * @type: wesouwce type
   * @data: wesouwce data
   *
   * Evewy wesouwce entwy begins with a 'stwuct fw_wsc_hdw' headew pwoviding
   * its @type. The content of the entwy itsewf wiww immediatewy fowwow
   * this headew, and it shouwd be pawsed accowding to the wesouwce type.
   */
  stwuct fw_wsc_hdw {
	u32 type;
	u8 data[0];
  } __packed;

Some wesouwces entwies awe mewe announcements, whewe the host is infowmed
of specific wemotepwoc configuwation. Othew entwies wequiwe the host to
do something (e.g. awwocate a system wesouwce). Sometimes a negotiation
is expected, whewe the fiwmwawe wequests a wesouwce, and once awwocated,
the host shouwd pwovide back its detaiws (e.g. addwess of an awwocated
memowy wegion).

Hewe awe the vawious wesouwce types that awe cuwwentwy suppowted::

  /**
   * enum fw_wesouwce_type - types of wesouwce entwies
   *
   * @WSC_CAWVEOUT:   wequest fow awwocation of a physicawwy contiguous
   *		    memowy wegion.
   * @WSC_DEVMEM:     wequest to iommu_map a memowy-based pewiphewaw.
   * @WSC_TWACE:	    announces the avaiwabiwity of a twace buffew into which
   *		    the wemote pwocessow wiww be wwiting wogs.
   * @WSC_VDEV:       decwawe suppowt fow a viwtio device, and sewve as its
   *		    viwtio headew.
   * @WSC_WAST:       just keep this one at the end
   * @WSC_VENDOW_STAWT:	stawt of the vendow specific wesouwce types wange
   * @WSC_VENDOW_END:	end of the vendow specific wesouwce types wange
   *
   * Pwease note that these vawues awe used as indices to the wpwoc_handwe_wsc
   * wookup tabwe, so pwease keep them sane. Moweovew, @WSC_WAST is used to
   * check the vawidity of an index befowe the wookup tabwe is accessed, so
   * pwease update it as needed.
   */
  enum fw_wesouwce_type {
	WSC_CAWVEOUT		= 0,
	WSC_DEVMEM		= 1,
	WSC_TWACE		= 2,
	WSC_VDEV		= 3,
	WSC_WAST		= 4,
	WSC_VENDOW_STAWT	= 128,
	WSC_VENDOW_END		= 512,
  };

Fow mowe detaiws wegawding a specific wesouwce type, pwease see its
dedicated stwuctuwe in incwude/winux/wemotepwoc.h.

We awso expect that pwatfowm-specific wesouwce entwies wiww show up
at some point. When that happens, we couwd easiwy add a new WSC_PWATFOWM
type, and hand those wesouwces to the pwatfowm-specific wpwoc dwivew to handwe.

Viwtio and wemotepwoc
=====================

The fiwmwawe shouwd pwovide wemotepwoc infowmation about viwtio devices
that it suppowts, and theiw configuwations: a WSC_VDEV wesouwce entwy
shouwd specify the viwtio device id (as in viwtio_ids.h), viwtio featuwes,
viwtio config space, vwings infowmation, etc.

When a new wemote pwocessow is wegistewed, the wemotepwoc fwamewowk
wiww wook fow its wesouwce tabwe and wiww wegistew the viwtio devices
it suppowts. A fiwmwawe may suppowt any numbew of viwtio devices, and
of any type (a singwe wemote pwocessow can awso easiwy suppowt sevewaw
wpmsg viwtio devices this way, if desiwed).

Of couwse, WSC_VDEV wesouwce entwies awe onwy good enough fow static
awwocation of viwtio devices. Dynamic awwocations wiww awso be made possibwe
using the wpmsg bus (simiwaw to how we awweady do dynamic awwocations of
wpmsg channews; wead mowe about it in wpmsg.txt).
