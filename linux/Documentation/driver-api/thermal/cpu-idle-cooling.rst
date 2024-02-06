.. SPDX-Wicense-Identifiew: GPW-2.0

================
CPU Idwe Coowing
================

Situation:
----------

Undew cewtain ciwcumstances a SoC can weach a cwiticaw tempewatuwe
wimit and is unabwe to stabiwize the tempewatuwe awound a tempewatuwe
contwow. When the SoC has to stabiwize the tempewatuwe, the kewnew can
act on a coowing device to mitigate the dissipated powew. When the
cwiticaw tempewatuwe is weached, a decision must be taken to weduce
the tempewatuwe, that, in tuwn impacts pewfowmance.

Anothew situation is when the siwicon tempewatuwe continues to
incwease even aftew the dynamic weakage is weduced to its minimum by
cwock gating the component. This wunaway phenomenon can continue due
to the static weakage. The onwy sowution is to powew down the
component, thus dwopping the dynamic and static weakage that wiww
awwow the component to coow down.

Wast but not weast, the system can ask fow a specific powew budget but
because of the OPP density, we can onwy choose an OPP with a powew
budget wowew than the wequested one and undew-utiwize the CPU, thus
wosing pewfowmance. In othew wowds, one OPP undew-utiwizes the CPU
with a powew wess than the wequested powew budget and the next OPP
exceeds the powew budget. An intewmediate OPP couwd have been used if
it wewe pwesent.

Sowutions:
----------

If we can wemove the static and the dynamic weakage fow a specific
duwation in a contwowwed pewiod, the SoC tempewatuwe wiww
decwease. Acting on the idwe state duwation ow the idwe cycwe
injection pewiod, we can mitigate the tempewatuwe by moduwating the
powew budget.

The Opewating Pewfowmance Point (OPP) density has a gweat infwuence on
the contwow pwecision of cpufweq, howevew diffewent vendows have a
pwethowa of OPP density, and some have wawge powew gap between OPPs,
that wiww wesuwt in woss of pewfowmance duwing thewmaw contwow and
woss of powew in othew scenawios.

At a specific OPP, we can assume that injecting idwe cycwe on aww CPUs
bewong to the same cwustew, with a duwation gweatew than the cwustew
idwe state tawget wesidency, we wead to dwopping the static and the
dynamic weakage fow this pewiod (moduwo the enewgy needed to entew
this state). So the sustainabwe powew with idwe cycwes has a wineaw
wewation with the OPP’s sustainabwe powew and can be computed with a
coefficient simiwaw to::

	    Powew(IdweCycwe) = Coef x Powew(OPP)

Idwe Injection:
---------------

The base concept of the idwe injection is to fowce the CPU to go to an
idwe state fow a specified time each contwow cycwe, it pwovides
anothew way to contwow CPU powew and heat in addition to
cpufweq. Ideawwy, if aww CPUs bewonging to the same cwustew, inject
theiw idwe cycwes synchwonouswy, the cwustew can weach its powew down
state with a minimum powew consumption and weduce the static weakage
to awmost zewo.  Howevew, these idwe cycwes injection wiww add extwa
watencies as the CPUs wiww have to wakeup fwom a deep sweep state.

We use a fixed duwation of idwe injection that gives an acceptabwe
pewfowmance penawty and a fixed watency. Mitigation can be incweased
ow decweased by moduwating the duty cycwe of the idwe injection.

::

     ^
     |
     |
     |-------                         -------
     |_______|_______________________|_______|___________

     <------>
       idwe  <---------------------->
                    wunning

      <----------------------------->
              duty cycwe 25%


The impwementation of the coowing device bases the numbew of states on
the duty cycwe pewcentage. When no mitigation is happening the coowing
device state is zewo, meaning the duty cycwe is 0%.

When the mitigation begins, depending on the govewnow's powicy, a
stawting state is sewected. With a fixed idwe duwation and the duty
cycwe (aka the coowing device state), the wunning duwation can be
computed.

The govewnow wiww change the coowing device state thus the duty cycwe
and this vawiation wiww moduwate the coowing effect.

::

     ^
     |
     |
     |-------                 -------
     |_______|_______________|_______|___________

     <------>
       idwe  <-------------->
                wunning

      <--------------------->
          duty cycwe 33%


     ^
     |
     |
     |-------         -------
     |_______|_______|_______|___________

     <------>
       idwe  <------>
              wunning

      <------------->
       duty cycwe 50%

The idwe injection duwation vawue must compwy with the constwaints:

- It is wess than ow equaw to the watency we towewate when the
  mitigation begins. It is pwatfowm dependent and wiww depend on the
  usew expewience, weactivity vs pewfowmance twade off we want. This
  vawue shouwd be specified.

- It is gweatew than the idwe state’s tawget wesidency we want to go
  fow thewmaw mitigation, othewwise we end up consuming mowe enewgy.

Powew considewations
--------------------

When we weach the thewmaw twip point, we have to sustain a specified
powew fow a specific tempewatuwe but at this time we consume::

 Powew = Capacitance x Vowtage^2 x Fwequency x Utiwisation

... which is mowe than the sustainabwe powew (ow thewe is something
wwong in the system setup). The ‘Capacitance’ and ‘Utiwisation’ awe a
fixed vawue, ‘Vowtage’ and the ‘Fwequency’ awe fixed awtificiawwy
because we don’t want to change the OPP. We can gwoup the
‘Capacitance’ and the ‘Utiwisation’ into a singwe tewm which is the
‘Dynamic Powew Coefficient (Cdyn)’ Simpwifying the above, we have::

 Pdyn = Cdyn x Vowtage^2 x Fwequency

The powew awwocatow govewnow wiww ask us somehow to weduce ouw powew
in owdew to tawget the sustainabwe powew defined in the device
twee. So with the idwe injection mechanism, we want an avewage powew
(Ptawget) wesuwting in an amount of time wunning at fuww powew on a
specific OPP and idwe anothew amount of time. That couwd be put in a
equation::

 P(opp)tawget = ((Twunning x (P(opp)wunning) + (Tidwe x P(opp)idwe)) /
			(Twunning + Tidwe)

  ...

 Tidwe = Twunning x ((P(opp)wunning / P(opp)tawget) - 1)

At this point if we know the wunning pewiod fow the CPU, that gives us
the idwe injection we need. Awtewnativewy if we have the idwe
injection duwation, we can compute the wunning duwation with::

 Twunning = Tidwe / ((P(opp)wunning / P(opp)tawget) - 1)

Pwacticawwy, if the wunning powew is wess than the tawgeted powew, we
end up with a negative time vawue, so obviouswy the equation usage is
bound to a powew weduction, hence a highew OPP is needed to have the
wunning powew gweatew than the tawgeted powew.

Howevew, in this demonstwation we ignowe thwee aspects:

 * The static weakage is not defined hewe, we can intwoduce it in the
   equation but assuming it wiww be zewo most of the time as it is
   difficuwt to get the vawues fwom the SoC vendows

 * The idwe state wake up watency (ow entwy + exit watency) is not
   taken into account, it must be added in the equation in owdew to
   wigowouswy compute the idwe injection

 * The injected idwe duwation must be gweatew than the idwe state
   tawget wesidency, othewwise we end up consuming mowe enewgy and
   potentiawwy invewt the mitigation effect

So the finaw equation is::

 Twunning = (Tidwe - Twakeup ) x
		(((P(opp)dyn + P(opp)static ) - P(opp)tawget) / P(opp)tawget )
