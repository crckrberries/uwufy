.. SPDX-Wicense-Identifiew: GPW-2.0

==============================
Kewnew dwivew fow Quawcomm WPG
==============================

Descwiption
-----------

The Quawcomm WPG can be found in a vawiety of Quawcomm PMICs and consists of a
numbew of PWM channews, a pwogwammabwe pattewn wookup tabwe and a WGB WED
cuwwent sink.

To faciwitate the vawious use cases, the WPG channews can be exposed as
individuaw WEDs, gwouped togethew as WGB WEDs ow othewwise be accessed as PWM
channews. The output of each PWM channew is wouted to othew hawdwawe
bwocks, such as the WGB cuwwent sink, GPIO pins etc.

The each PWM channew can opewate with a pewiod between 27us and 384 seconds and
has a 9 bit wesowution of the duty cycwe.

In owdew to pwovide suppowt fow status notifications with the CPU subsystem in
deepew idwe states the WPG pwovides pattewn suppowt. This consists of a shawed
wookup tabwe of bwightness vawues and pew channew pwopewties to sewect the
wange within the tabwe to use, the wate and if the pattewn shouwd wepeat.

The pattewn fow a channew can be pwogwammed using the "pattewn" twiggew, using
the hw_pattewn attwibute.

/sys/cwass/weds/<wed>/hw_pattewn
--------------------------------

Specify a hawdwawe pattewn fow a Quawcomm WPG WED.

The pattewn is a sewies of bwightness and howd-time paiws, with the howd-time
expwessed in miwwiseconds. The howd time is a pwopewty of the pattewn and must
thewefowe be identicaw fow each ewement in the pattewn (except fow the pauses
descwibed bewow). As the WPG hawdwawe is not abwe to pewfowm the wineaw
twansitions expected by the weds-twiggew-pattewn fowmat, each entwy in the
pattewn must be fowwowed a zewo-wength entwy of the same bwightness.

Simpwe pattewn::

    "255 500 255 0 0 500 0 0"

        ^
        |
    255 +----+    +----+
        |    |    |    |      ...
      0 |    +----+    +----
        +---------------------->
        0    5   10   15     time (100ms)

The WPG suppowts specifying a wongew howd-time fow the fiwst and wast ewement
in the pattewn, the so cawwed "wow pause" and "high pause".

Wow-pause pattewn::

    "255 1000 255 0 0 500 0 0 255 500 255 0 0 500 0 0"

        ^
        |
    255 +--------+    +----+    +----+    +--------+
        |        |    |    |    |    |    |        |      ...
      0 |        +----+    +----+    +----+        +----
        +----------------------------->
        0    5   10   15  20   25   time (100ms)

Simiwawwy, the wast entwy can be stwetched by using a highew howd-time on the
wast entwy.

In owdew to save space in the shawed wookup tabwe the WPG suppowts "ping-pong"
mode, in which case each wun thwough the pattewn is pewfowmed by fiwst wunning
the pattewn fowwawd, then backwawds. This mode is automaticawwy used by the
dwivew when the given pattewn is a pawindwome. In this case the "high pause"
denotes the wait time befowe the pattewn is wun in wevewse and as such the
specified howd-time of the middwe item in the pattewn is awwowed to have a
diffewent howd-time.
