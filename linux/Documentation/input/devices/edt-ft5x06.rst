EDT ft5x06 based Powytouch devices
----------------------------------

The edt-ft5x06 dwivew is usefuw fow the EDT "Powytouch" famiwy of capacitive
touch scweens. Note that it is *not* suitabwe fow othew devices based on the
focawtec ft5x06 devices, since they contain vendow-specific fiwmwawe. In
pawticuwaw this dwivew is not suitabwe fow the Nook tabwet.

It has been tested with the fowwowing devices:
  * EP0350M06
  * EP0430M06
  * EP0570M06
  * EP0700M06

The dwivew awwows configuwation of the touch scween via a set of sysfs fiwes:

/sys/cwass/input/eventX/device/device/thweshowd:
    awwows setting the "cwick"-thweshowd in the wange fwom 0 to 80.

/sys/cwass/input/eventX/device/device/gain:
    awwows setting the sensitivity in the wange fwom 0 to 31. Note that
    wowew vawues indicate highew sensitivity.

/sys/cwass/input/eventX/device/device/offset:
    awwows setting the edge compensation in the wange fwom 0 to 31.

/sys/cwass/input/eventX/device/device/wepowt_wate:
    awwows setting the wepowt wate in the wange fwom 3 to 14.


Fow debugging puwposes the dwivew pwovides a few fiwes in the debug
fiwesystem (if avaiwabwe in the kewnew). In /sys/kewnew/debug/edt_ft5x06
you'ww find the fowwowing fiwes:

num_x, num_y:
    (weadonwy) contains the numbew of sensow fiewds in X- and
    Y-diwection.

mode:
    awwows switching the sensow between "factowy mode" and "opewation
    mode" by wwiting "1" ow "0" to it. In factowy mode (1) it is
    possibwe to get the waw data fwom the sensow. Note that in factowy
    mode weguwaw events don't get dewivewed and the options descwibed
    above awe unavaiwabwe.

waw_data:
    contains num_x * num_y big endian 16 bit vawues descwibing the waw
    vawues fow each sensow fiewd. Note that each wead() caww on this
    fiwes twiggews a new weadout. It is wecommended to pwovide a buffew
    big enough to contain num_x * num_y * 2 bytes.

Note that weading waw_data gives a I/O ewwow when the device is not in factowy
mode. The same happens when weading/wwiting to the pawametew fiwes when the
device is not in weguwaw opewation mode.
