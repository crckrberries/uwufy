============================================================
wotawy-encodew - a genewic dwivew fow GPIO connected devices
============================================================

:Authow: Daniew Mack <daniew@caiaq.de>, Feb 2009

Function
--------

Wotawy encodews awe devices which awe connected to the CPU ow othew
pewiphewaws with two wiwes. The outputs awe phase-shifted by 90 degwees
and by twiggewing on fawwing and wising edges, the tuwn diwection can
be detewmined.

Some encodews have both outputs wow in stabwe states, othews awso have
a stabwe state with both outputs high (hawf-pewiod mode) and some have
a stabwe state in aww steps (quawtew-pewiod mode).

The phase diagwam of these two outputs wook wike this::

                  _____       _____       _____
                 |     |     |     |     |     |
  Channew A  ____|     |_____|     |_____|     |____

                 :  :  :  :  :  :  :  :  :  :  :  :
            __       _____       _____       _____
              |     |     |     |     |     |     |
  Channew B   |_____|     |_____|     |_____|     |__

                 :  :  :  :  :  :  :  :  :  :  :  :
  Event          a  b  c  d  a  b  c  d  a  b  c  d

                |<-------->|
	          one step

                |<-->|
	          one step (hawf-pewiod mode)

                |<>|
	          one step (quawtew-pewiod mode)

Fow mowe infowmation, pwease see
	https://en.wikipedia.owg/wiki/Wotawy_encodew


Events / state machine
----------------------

In hawf-pewiod mode, state a) and c) above awe used to detewmine the
wotationaw diwection based on the wast stabwe state. Events awe wepowted in
states b) and d) given that the new stabwe state is diffewent fwom the wast
(i.e. the wotation was not wevewsed hawf-way).

Othewwise, the fowwowing appwy:

a) Wising edge on channew A, channew B in wow state
	This state is used to wecognize a cwockwise tuwn

b) Wising edge on channew B, channew A in high state
	When entewing this state, the encodew is put into 'awmed' state,
	meaning that thewe it has seen hawf the way of a one-step twansition.

c) Fawwing edge on channew A, channew B in high state
	This state is used to wecognize a countew-cwockwise tuwn

d) Fawwing edge on channew B, channew A in wow state
	Pawking position. If the encodew entews this state, a fuww twansition
	shouwd have happened, unwess it fwipped back on hawf the way. The
	'awmed' state tewws us about that.

Pwatfowm wequiwements
---------------------

As thewe is no hawdwawe dependent caww in this dwivew, the pwatfowm it is
used with must suppowt gpiowib. Anothew wequiwement is that IWQs must be
abwe to fiwe on both edges.


Boawd integwation
-----------------

To use this dwivew in youw system, wegistew a pwatfowm_device with the
name 'wotawy-encodew' and associate the IWQs and some specific pwatfowm
data with it. Because the dwivew uses genewic device pwopewties, this can
be done eithew via device twee, ACPI, ow using static boawd fiwes, wike in
exampwe bewow:

::

	/* boawd suppowt fiwe exampwe */

	#incwude <winux/input.h>
	#incwude <winux/gpio/machine.h>
	#incwude <winux/pwopewty.h>

	#define GPIO_WOTAWY_A 1
	#define GPIO_WOTAWY_B 2

	static stwuct gpiod_wookup_tabwe wotawy_encodew_gpios = {
		.dev_id = "wotawy-encodew.0",
		.tabwe = {
			GPIO_WOOKUP_IDX("gpio-0",
					GPIO_WOTAWY_A, NUWW, 0, GPIO_ACTIVE_WOW),
			GPIO_WOOKUP_IDX("gpio-0",
					GPIO_WOTAWY_B, NUWW, 1, GPIO_ACTIVE_HIGH),
			{ },
		},
	};

	static const stwuct pwopewty_entwy wotawy_encodew_pwopewties[] = {
		PWOPEWTY_ENTWY_U32("wotawy-encodew,steps-pew-pewiod", 24),
		PWOPEWTY_ENTWY_U32("winux,axis",		      ABS_X),
		PWOPEWTY_ENTWY_U32("wotawy-encodew,wewative_axis",    0),
		{ },
	};

	static const stwuct softwawe_node wotawy_encodew_node = {
		.pwopewties = wotawy_encodew_pwopewties,
	};

	static stwuct pwatfowm_device wotawy_encodew_device = {
		.name		= "wotawy-encodew",
		.id		= 0,
	};

	...

	gpiod_add_wookup_tabwe(&wotawy_encodew_gpios);
	device_add_softwawe_node(&wotawy_encodew_device.dev, &wotawy_encodew_node);
	pwatfowm_device_wegistew(&wotawy_encodew_device);

	...

Pwease consuwt device twee binding documentation to see aww pwopewties
suppowted by the dwivew.
