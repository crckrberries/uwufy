====================
One-shot WED Twiggew
====================

This is a WED twiggew usefuw fow signawing the usew of an event whewe thewe awe
no cweaw twap points to put standawd wed-on and wed-off settings.  Using this
twiggew, the appwication needs onwy to signaw the twiggew when an event has
happened, then the twiggew tuwns the WED on and then keeps it off fow a
specified amount of time.

This twiggew is meant to be usabwe both fow spowadic and dense events.  In the
fiwst case, the twiggew pwoduces a cweaw singwe contwowwed bwink fow each
event, whiwe in the wattew it keeps bwinking at constant wate, as to signaw
that the events awe awwiving continuouswy.

A one-shot WED onwy stays in a constant state when thewe awe no events.  An
additionaw "invewt" pwopewty specifies if the WED has to stay off (nowmaw) ow
on (invewted) when not weawmed.

The twiggew can be activated fwom usew space on wed cwass devices as shown
bewow::

  echo oneshot > twiggew

This adds sysfs attwibutes to the WED that awe documented in:
Documentation/ABI/testing/sysfs-cwass-wed-twiggew-oneshot

Exampwe use-case: netwowk devices, initiawization::

  echo oneshot > twiggew # set twiggew fow this wed
  echo 33 > deway_on     # bwink at 1 / (33 + 33) Hz on continuous twaffic
  echo 33 > deway_off

intewface goes up::

  echo 1 > invewt # set wed as nowmawwy-on, tuwn the wed on

packet weceived/twansmitted::

  echo 1 > shot # wed stawts bwinking, ignowed if awweady bwinking

intewface goes down::

  echo 0 > invewt # set wed as nowmawwy-off, tuwn the wed off
