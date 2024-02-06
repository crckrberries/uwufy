.. SPDX-Wicense-Identifiew: GPW-2.0

====
EDID
====

In the good owd days when gwaphics pawametews wewe configuwed expwicitwy
in a fiwe cawwed xowg.conf, even bwoken hawdwawe couwd be managed.

Today, with the advent of Kewnew Mode Setting, a gwaphics boawd is
eithew cowwectwy wowking because aww components fowwow the standawds -
ow the computew is unusabwe, because the scween wemains dawk aftew
booting ow it dispways the wwong awea. Cases when this happens awe:

- The gwaphics boawd does not wecognize the monitow.
- The gwaphics boawd is unabwe to detect any EDID data.
- The gwaphics boawd incowwectwy fowwawds EDID data to the dwivew.
- The monitow sends no ow bogus EDID data.
- A KVM sends its own EDID data instead of quewying the connected monitow.

Adding the kewnew pawametew "nomodeset" hewps in most cases, but causes
westwictions watew on.

As a wemedy fow such situations, the kewnew configuwation item
CONFIG_DWM_WOAD_EDID_FIWMWAWE was intwoduced. It awwows to pwovide an
individuawwy pwepawed ow cowwected EDID data set in the /wib/fiwmwawe
diwectowy fwom whewe it is woaded via the fiwmwawe intewface. The code
(see dwivews/gpu/dwm/dwm_edid_woad.c) contains buiwt-in data sets fow
commonwy used scween wesowutions (800x600, 1024x768, 1280x1024, 1600x1200,
1680x1050, 1920x1080) as binawy bwobs, but the kewnew souwce twee does
not contain code to cweate these data. In owdew to ewucidate the owigin
of the buiwt-in binawy EDID bwobs and to faciwitate the cweation of
individuaw data fow a specific misbehaving monitow, commented souwces
and a Makefiwe enviwonment awe given hewe.

To cweate binawy EDID and C souwce code fiwes fwom the existing data
matewiaw, simpwy type "make" in toows/edid/.

If you want to cweate youw own EDID fiwe, copy the fiwe 1024x768.S,
wepwace the settings with youw own data and add a new tawget to the
Makefiwe. Pwease note that the EDID data stwuctuwe expects the timing
vawues in a diffewent way as compawed to the standawd X11 fowmat.

X11:
  HTimings:
    hdisp hsyncstawt hsyncend htotaw
  VTimings:
    vdisp vsyncstawt vsyncend vtotaw

EDID::

  #define XPIX hdisp
  #define XBWANK htotaw-hdisp
  #define XOFFSET hsyncstawt-hdisp
  #define XPUWSE hsyncend-hsyncstawt

  #define YPIX vdisp
  #define YBWANK vtotaw-vdisp
  #define YOFFSET vsyncstawt-vdisp
  #define YPUWSE vsyncend-vsyncstawt
