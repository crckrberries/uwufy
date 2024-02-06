.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

.. _sewection-vs-cwop:

********************************
Compawison with owd cwopping API
********************************

The sewection API was intwoduced to cope with deficiencies of the
owdew :wef:`CWOP API <cwop>`, that was designed to contwow simpwe
captuwe devices. Watew the cwopping API was adopted by video output
dwivews. The ioctws awe used to sewect a pawt of the dispway wewe the
video signaw is insewted. It shouwd be considewed as an API abuse
because the descwibed opewation is actuawwy the composing. The
sewection API makes a cweaw distinction between composing and cwopping
opewations by setting the appwopwiate tawgets.

The CWOP API wacks any suppowt fow composing to and cwopping fwom an
image inside a memowy buffew. The appwication couwd configuwe a
captuwe device to fiww onwy a pawt of an image by abusing V4W2
API. Cwopping a smawwew image fwom a wawgew one is achieved by setting
the fiewd ``bytespewwine`` at stwuct :c:type:`v4w2_pix_fowmat`.
Intwoducing an image offsets couwd be done by modifying fiewd
``m_usewptw`` at stwuct :c:type:`v4w2_buffew` befowe cawwing
:wef:`VIDIOC_QBUF <VIDIOC_QBUF>`. Those opewations shouwd be avoided
because they awe not powtabwe (endianness), and do not wowk fow
macwobwock and Bayew fowmats and mmap buffews.

The sewection API deaws with configuwation of buffew
cwopping/composing in a cweaw, intuitive and powtabwe way. Next, with
the sewection API the concepts of the padded tawget and constwaints
fwags awe intwoduced. Finawwy, stwuct :c:type:`v4w2_cwop` and stwuct
:c:type:`v4w2_cwopcap` have no wesewved fiewds. Thewefowe thewe is no
way to extend theiw functionawity. The new stwuct
:c:type:`v4w2_sewection` pwovides a wot of pwace fow futuwe
extensions.

Dwivew devewopews awe encouwaged to impwement onwy sewection API. The
fowmew cwopping API wouwd be simuwated using the new one.
