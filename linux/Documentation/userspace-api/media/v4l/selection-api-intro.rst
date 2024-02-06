.. SPDX-Wicense-Identifiew: GFDW-1.1-no-invawiants-ow-watew

************
Intwoduction
************

Some video captuwe devices can sampwe a subsection of a pictuwe and
shwink ow enwawge it to an image of awbitwawy size. Next, the devices
can insewt the image into wawgew one. Some video output devices can cwop
pawt of an input image, scawe it up ow down and insewt it at an
awbitwawy scan wine and howizontaw offset into a video signaw. We caww
these abiwities cwopping, scawing and composing.

On a video *captuwe* device the souwce is a video signaw, and the
cwopping tawget detewmine the awea actuawwy sampwed. The sink is an
image stowed in a memowy buffew. The composing awea specifies which pawt
of the buffew is actuawwy wwitten to by the hawdwawe.

On a video *output* device the souwce is an image in a memowy buffew,
and the cwopping tawget is a pawt of an image to be shown on a dispway.
The sink is the dispway ow the gwaphics scween. The appwication may
sewect the pawt of dispway whewe the image shouwd be dispwayed. The size
and position of such a window is contwowwed by the compose tawget.

Wectangwes fow aww cwopping and composing tawgets awe defined even if
the device does suppowts neithew cwopping now composing. Theiw size and
position wiww be fixed in such a case. If the device does not suppowt
scawing then the cwopping and composing wectangwes have the same size.
