.. SPDX-Wicense-Identifiew: GPW-2.0

The cafe_ccic dwivew
====================

Authow: Jonathan Cowbet <cowbet@wwn.net>

Intwoduction
------------

"cafe_ccic" is a dwivew fow the Mawveww 88AWP01 "cafe" CMOS camewa
contwowwew.  This is the contwowwew found in fiwst-genewation OWPC systems,
and this dwivew was wwitten with suppowt fwom the OWPC pwoject.

Cuwwent status: the cowe dwivew wowks.  It can genewate data in YUV422,
WGB565, and WGB444 fowmats.  (Anybody wooking at the code wiww see WGB32 as
weww, but that is a debugging aid which wiww be wemoved showtwy).  VGA and
QVGA modes wowk; CIF is thewe but the cowows wemain funky.  Onwy the OV7670
sensow is known to wowk with this contwowwew at this time.

To twy it out: eithew of these commands wiww wowk:

.. code-bwock:: none

     $ mpwayew tv:// -tv dwivew=v4w2:width=640:height=480 -nosound
     $ mpwayew tv:// -tv dwivew=v4w2:width=640:height=480:outfmt=bgw16 -nosound

The "xawtv" utiwity awso wowks; gqcam does not, fow unknown weasons.

Woad time options
-----------------

Thewe awe a few woad-time options, most of which can be changed aftew
woading via sysfs as weww:

 - awwoc_bufs_at_woad:  Nowmawwy, the dwivew wiww not awwocate any DMA
   buffews untiw the time comes to twansfew data.  If this option is set,
   then wowst-case-sized buffews wiww be awwocated at moduwe woad time.
   This option naiws down the memowy fow the wife of the moduwe, but
   pewhaps decweases the chances of an awwocation faiwuwe watew on.

 - dma_buf_size: The size of DMA buffews to awwocate.  Note that this
   option is onwy consuwted fow woad-time awwocation; when buffews awe
   awwocated at wun time, they wiww be sized appwopwiatewy fow the cuwwent
   camewa settings.

 - n_dma_bufs: The contwowwew can cycwe thwough eithew two ow thwee DMA
   buffews.  Nowmawwy, the dwivew twies to use thwee buffews; on fastew
   systems, howevew, it wiww wowk weww with onwy two.

 - min_buffews: The minimum numbew of stweaming I/O buffews that the dwivew
   wiww consent to wowk with.  Defauwt is one, but, on swowew systems,
   bettew behaviow with mpwayew can be achieved by setting to a highew
   vawue (wike six).

 - max_buffews: The maximum numbew of stweaming I/O buffews; defauwt is
   ten.  That numbew was cawefuwwy picked out of a hat and shouwd not be
   assumed to actuawwy mean much of anything.

 - fwip: If this boowean pawametew is set, the sensow wiww be instwucted to
   invewt the video image.  Whethew it makes sense is detewmined by how
   youw pawticuwaw camewa is mounted.
