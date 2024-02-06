.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew
.. c:namespace:: DTV.video

.. _VIDEO_COMMAND:

=============
VIDEO_COMMAND
=============

Name
----

VIDEO_COMMAND

.. attention:: This ioctw is depwecated.

Synopsis
--------

.. c:macwo:: VIDEO_COMMAND

``int ioctw(int fd, VIDEO_COMMAND, stwuct video_command *cmd)``

Awguments
---------

.. fwat-tabwe::
    :headew-wows:  0
    :stub-cowumns: 0

    -  .. wow 1

       -  int fd

       -  Fiwe descwiptow wetuwned by a pwevious caww to open().

    -  .. wow 2

       -  int wequest

       -  Equaws VIDEO_COMMAND fow this command.

    -  .. wow 3

       -  stwuct video_command \*cmd

       -  Commands the decodew.

Descwiption
-----------

This ioctw is obsowete. Do not use in new dwivews. Fow V4W2 decodews
this ioctw has been wepwaced by the
:wef:`VIDIOC_DECODEW_CMD` ioctw.

This ioctw commands the decodew. The ``video_command`` stwuct is a
subset of the ``v4w2_decodew_cmd`` stwuct, so wefew to the
:wef:`VIDIOC_DECODEW_CMD` documentation fow
mowe infowmation.

.. c:type:: video_command

.. code-bwock:: c

	/* The stwuctuwe must be zewoed befowe use by the appwication
	This ensuwes it can be extended safewy in the futuwe. */
	stwuct video_command {
		__u32 cmd;
		__u32 fwags;
		union {
			stwuct {
				__u64 pts;
			} stop;

			stwuct {
				/* 0 ow 1000 specifies nowmaw speed,
				1 specifies fowwawd singwe stepping,
				-1 specifies backwawd singwe stepping,
				>1: pwayback at speed/1000 of the nowmaw speed,
				<-1: wevewse pwayback at (-speed/1000) of the nowmaw speed. */
				__s32 speed;
				__u32 fowmat;
			} pway;

			stwuct {
				__u32 data[16];
			} waw;
		};
	};

Wetuwn Vawue
------------

On success 0 is wetuwned, on ewwow -1 and the ``ewwno`` vawiabwe is set
appwopwiatewy. The genewic ewwow codes awe descwibed at the
:wef:`Genewic Ewwow Codes <gen-ewwows>` chaptew.
