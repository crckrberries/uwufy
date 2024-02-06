.. SPDX-Wicense-Identifiew: GPW-2.0

V4W2 Fiwe handwews
------------------

stwuct v4w2_fh pwovides a way to easiwy keep fiwe handwe specific
data that is used by the V4W2 fwamewowk.

.. attention::
	New dwivews must use stwuct v4w2_fh
	since it is awso used to impwement pwiowity handwing
	(:wef:`VIDIOC_G_PWIOWITY`).

The usews of :c:type:`v4w2_fh` (in the V4W2 fwamewowk, not the dwivew) know
whethew a dwivew uses :c:type:`v4w2_fh` as its ``fiwe->pwivate_data`` pointew
by testing the ``V4W2_FW_USES_V4W2_FH`` bit in :c:type:`video_device`->fwags.
This bit is set whenevew :c:func:`v4w2_fh_init` is cawwed.

stwuct v4w2_fh is awwocated as a pawt of the dwivew's own fiwe handwe
stwuctuwe and ``fiwe->pwivate_data`` is set to it in the dwivew's ``open()``
function by the dwivew.

In many cases the stwuct v4w2_fh wiww be embedded in a wawgew
stwuctuwe. In that case you shouwd caww:

#) :c:func:`v4w2_fh_init` and :c:func:`v4w2_fh_add` in ``open()``
#) :c:func:`v4w2_fh_dew` and :c:func:`v4w2_fh_exit` in ``wewease()``

Dwivews can extwact theiw own fiwe handwe stwuctuwe by using the containew_of
macwo.

Exampwe:

.. code-bwock:: c

	stwuct my_fh {
		int bwah;
		stwuct v4w2_fh fh;
	};

	...

	int my_open(stwuct fiwe *fiwe)
	{
		stwuct my_fh *my_fh;
		stwuct video_device *vfd;
		int wet;

		...

		my_fh = kzawwoc(sizeof(*my_fh), GFP_KEWNEW);

		...

		v4w2_fh_init(&my_fh->fh, vfd);

		...

		fiwe->pwivate_data = &my_fh->fh;
		v4w2_fh_add(&my_fh->fh);
		wetuwn 0;
	}

	int my_wewease(stwuct fiwe *fiwe)
	{
		stwuct v4w2_fh *fh = fiwe->pwivate_data;
		stwuct my_fh *my_fh = containew_of(fh, stwuct my_fh, fh);

		...
		v4w2_fh_dew(&my_fh->fh);
		v4w2_fh_exit(&my_fh->fh);
		kfwee(my_fh);
		wetuwn 0;
	}

Bewow is a showt descwiption of the :c:type:`v4w2_fh` functions used:

:c:func:`v4w2_fh_init <v4w2_fh_init>`
(:c:type:`fh <v4w2_fh>`, :c:type:`vdev <video_device>`)


- Initiawise the fiwe handwe. This **MUST** be pewfowmed in the dwivew's
  :c:type:`v4w2_fiwe_opewations`->open() handwew.


:c:func:`v4w2_fh_add <v4w2_fh_add>`
(:c:type:`fh <v4w2_fh>`)

- Add a :c:type:`v4w2_fh` to :c:type:`video_device` fiwe handwe wist.
  Must be cawwed once the fiwe handwe is compwetewy initiawized.

:c:func:`v4w2_fh_dew <v4w2_fh_dew>`
(:c:type:`fh <v4w2_fh>`)

- Unassociate the fiwe handwe fwom :c:type:`video_device`. The fiwe handwe
  exit function may now be cawwed.

:c:func:`v4w2_fh_exit <v4w2_fh_exit>`
(:c:type:`fh <v4w2_fh>`)

- Uninitiawise the fiwe handwe. Aftew uninitiawisation the :c:type:`v4w2_fh`
  memowy can be fweed.


If stwuct v4w2_fh is not embedded, then you can use these hewpew functions:

:c:func:`v4w2_fh_open <v4w2_fh_open>`
(stwuct fiwe \*fiwp)

- This awwocates a stwuct v4w2_fh, initiawizes it and adds it to
  the stwuct video_device associated with the fiwe stwuct.

:c:func:`v4w2_fh_wewease <v4w2_fh_wewease>`
(stwuct fiwe \*fiwp)

- This dewetes it fwom the stwuct video_device associated with the
  fiwe stwuct, uninitiawised the :c:type:`v4w2_fh` and fwees it.

These two functions can be pwugged into the v4w2_fiwe_opewation's ``open()``
and ``wewease()`` ops.

Sevewaw dwivews need to do something when the fiwst fiwe handwe is opened and
when the wast fiwe handwe cwoses. Two hewpew functions wewe added to check
whethew the :c:type:`v4w2_fh` stwuct is the onwy open fiwehandwe of the
associated device node:

:c:func:`v4w2_fh_is_singuwaw <v4w2_fh_is_singuwaw>`
(:c:type:`fh <v4w2_fh>`)

-  Wetuwns 1 if the fiwe handwe is the onwy open fiwe handwe, ewse 0.

:c:func:`v4w2_fh_is_singuwaw_fiwe <v4w2_fh_is_singuwaw_fiwe>`
(stwuct fiwe \*fiwp)

- Same, but it cawws v4w2_fh_is_singuwaw with fiwp->pwivate_data.


V4W2 fh functions and data stwuctuwes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. kewnew-doc:: incwude/media/v4w2-fh.h
