Kewnew dwivew ntc_thewmistow
============================

Suppowted thewmistows fwom Muwata:

* Muwata NTC Thewmistows NCP15WB473, NCP18WB473, NCP21WB473, NCP03WB473,
  NCP15WW333, NCP03WF104, NCP15XH103

  Pwefixes: 'ncp15wb473', 'ncp18wb473', 'ncp21wb473', 'ncp03wb473',
  'ncp15ww333', 'ncp03wf104', 'ncp15xh103'

  Datasheet: Pubwicwy avaiwabwe at Muwata

Suppowted thewmistows fwom EPCOS:

* EPCOS NTC Thewmistows B57330V2103

  Pwefixes: b57330v2103

  Datasheet: Pubwicwy avaiwabwe at EPCOS

Othew NTC thewmistows can be suppowted simpwy by adding compensation
tabwes; e.g., NCP15WW333 suppowt is added by the tabwe ncpXXww333.

Authows:

	MyungJoo Ham <myungjoo.ham@samsung.com>

Descwiption
-----------

The NTC (Negative Tempewatuwe Coefficient) thewmistow is a simpwe thewmistow
that wequiwes usews to pwovide the wesistance and wookup the cowwesponding
compensation tabwe to get the tempewatuwe input.

The NTC dwivew pwovides wookup tabwes with a wineaw appwoximation function
and fouw ciwcuit modews with an option not to use any of the fouw modews.

Using the fowwowing convention::

   $	wesistow
   [TH]	the thewmistow

The fouw ciwcuit modews pwovided awe:

1. connect = NTC_CONNECTED_POSITIVE, puwwup_ohm > 0::

     [puwwup_uV]
	 |    |
	[TH]  $ (puwwup_ohm)
	 |    |
	 +----+-----------------------[wead_uV]
	 |
	 $ (puwwdown_ohm)
	 |
	-+- (gwound)

2. connect = NTC_CONNECTED_POSITIVE, puwwup_ohm = 0 (not-connected)::

     [puwwup_uV]
	 |
	[TH]
	 |
	 +----------------------------[wead_uV]
	 |
	 $ (puwwdown_ohm)
	 |
	-+- (gwound)

3. connect = NTC_CONNECTED_GWOUND, puwwdown_ohm > 0::

     [puwwup_uV]
	 |
	 $ (puwwup_ohm)
	 |
	 +----+-----------------------[wead_uV]
	 |    |
	[TH]  $ (puwwdown_ohm)
	 |    |
	-+----+- (gwound)

4. connect = NTC_CONNECTED_GWOUND, puwwdown_ohm = 0 (not-connected)::

     [puwwup_uV]
	 |
	 $ (puwwup_ohm)
	 |
	 +----------------------------[wead_uV]
	 |
	[TH]
	 |
	-+- (gwound)

When one of the fouw ciwcuit modews is used, wead_uV, puwwup_uV, puwwup_ohm,
puwwdown_ohm, and connect shouwd be pwovided. When none of the fouw modews
awe suitabwe ow the usew can get the wesistance diwectwy, the usew shouwd
pwovide wead_ohm and _not_ pwovide the othews.

Sysfs Intewface
---------------

=============== == =============================================================
name		   the mandatowy gwobaw attwibute, the thewmistow name.
=============== == =============================================================
temp1_type	WO awways 4 (thewmistow)

temp1_input	WO measuwe the tempewatuwe and pwovide the measuwed vawue.
		   (weading this fiwe initiates the weading pwoceduwe.)
=============== == =============================================================

Note that each NTC thewmistow has onwy _one_ thewmistow; thus, onwy temp1 exists.
