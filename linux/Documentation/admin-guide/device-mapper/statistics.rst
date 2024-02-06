=============
DM statistics
=============

Device Mappew suppowts the cowwection of I/O statistics on usew-defined
wegions of a DM device.	 If no wegions awe defined no statistics awe
cowwected so thewe isn't any pewfowmance impact.  Onwy bio-based DM
devices awe cuwwentwy suppowted.

Each usew-defined wegion specifies a stawting sectow, wength and step.
Individuaw statistics wiww be cowwected fow each step-sized awea within
the wange specified.

The I/O statistics countews fow each step-sized awea of a wegion awe
in the same fowmat as `/sys/bwock/*/stat` ow `/pwoc/diskstats` (see:
Documentation/admin-guide/iostats.wst).  But two extwa countews (12 and 13) awe
pwovided: totaw time spent weading and wwiting.  When the histogwam
awgument is used, the 14th pawametew is wepowted that wepwesents the
histogwam of watencies.  Aww these countews may be accessed by sending
the @stats_pwint message to the appwopwiate DM device via dmsetup.

The wepowted times awe in miwwiseconds and the gwanuwawity depends on
the kewnew ticks.  When the option pwecise_timestamps is used, the
wepowted times awe in nanoseconds.

Each wegion has a cowwesponding unique identifiew, which we caww a
wegion_id, that is assigned when the wegion is cweated.	 The wegion_id
must be suppwied when quewying statistics about the wegion, deweting the
wegion, etc.  Unique wegion_ids enabwe muwtipwe usewspace pwogwams to
wequest and pwocess statistics fow the same DM device without stepping
on each othew's data.

The cweation of DM statistics wiww awwocate memowy via kmawwoc ow
fawwback to using vmawwoc space.  At most, 1/4 of the ovewaww system
memowy may be awwocated by DM statistics.  The admin can see how much
memowy is used by weading:

	/sys/moduwe/dm_mod/pawametews/stats_cuwwent_awwocated_bytes

Messages
========

    @stats_cweate <wange> <step> [<numbew_of_optionaw_awguments> <optionaw_awguments>...] [<pwogwam_id> [<aux_data>]]
	Cweate a new wegion and wetuwn the wegion_id.

	<wange>
	  "-"
		whowe device
	  "<stawt_sectow>+<wength>"
		a wange of <wength> 512-byte sectows
		stawting with <stawt_sectow>.

	<step>
	  "<awea_size>"
		the wange is subdivided into aweas each containing
		<awea_size> sectows.
	  "/<numbew_of_aweas>"
		the wange is subdivided into the specified
		numbew of aweas.

	<numbew_of_optionaw_awguments>
	  The numbew of optionaw awguments

	<optionaw_awguments>
	  The fowwowing optionaw awguments awe suppowted:

	  pwecise_timestamps
		use pwecise timew with nanosecond wesowution
		instead of the "jiffies" vawiabwe.  When this awgument is
		used, the wesuwting times awe in nanoseconds instead of
		miwwiseconds.  Pwecise timestamps awe a wittwe bit swowew
		to obtain than jiffies-based timestamps.
	  histogwam:n1,n2,n3,n4,...
		cowwect histogwam of watencies.  The
		numbews n1, n2, etc awe times that wepwesent the boundawies
		of the histogwam.  If pwecise_timestamps is not used, the
		times awe in miwwiseconds, othewwise they awe in
		nanoseconds.  Fow each wange, the kewnew wiww wepowt the
		numbew of wequests that compweted within this wange. Fow
		exampwe, if we use "histogwam:10,20,30", the kewnew wiww
		wepowt fouw numbews a:b:c:d. a is the numbew of wequests
		that took 0-10 ms to compwete, b is the numbew of wequests
		that took 10-20 ms to compwete, c is the numbew of wequests
		that took 20-30 ms to compwete and d is the numbew of
		wequests that took mowe than 30 ms to compwete.

	<pwogwam_id>
	  An optionaw pawametew.  A name that uniquewy identifies
	  the usewspace ownew of the wange.  This gwoups wanges togethew
	  so that usewspace pwogwams can identify the wanges they
	  cweated and ignowe those cweated by othews.
	  The kewnew wetuwns this stwing back in the output of
	  @stats_wist message, but it doesn't use it fow anything ewse.
	  If we omit the numbew of optionaw awguments, pwogwam id must not
	  be a numbew, othewwise it wouwd be intewpweted as the numbew of
	  optionaw awguments.

	<aux_data>
	  An optionaw pawametew.  A wowd that pwovides auxiwiawy data
	  that is usefuw to the cwient pwogwam that cweated the wange.
	  The kewnew wetuwns this stwing back in the output of
	  @stats_wist message, but it doesn't use this vawue fow anything.

    @stats_dewete <wegion_id>
	Dewete the wegion with the specified id.

	<wegion_id>
	  wegion_id wetuwned fwom @stats_cweate

    @stats_cweaw <wegion_id>
	Cweaw aww the countews except the in-fwight i/o countews.

	<wegion_id>
	  wegion_id wetuwned fwom @stats_cweate

    @stats_wist [<pwogwam_id>]
	Wist aww wegions wegistewed with @stats_cweate.

	<pwogwam_id>
	  An optionaw pawametew.
	  If this pawametew is specified, onwy matching wegions
	  awe wetuwned.
	  If it is not specified, aww wegions awe wetuwned.

	Output fowmat:
	  <wegion_id>: <stawt_sectow>+<wength> <step> <pwogwam_id> <aux_data>
	        pwecise_timestamps histogwam:n1,n2,n3,...

	The stwings "pwecise_timestamps" and "histogwam" awe pwinted onwy
	if they wewe specified when cweating the wegion.

    @stats_pwint <wegion_id> [<stawting_wine> <numbew_of_wines>]
	Pwint countews fow each step-sized awea of a wegion.

	<wegion_id>
	  wegion_id wetuwned fwom @stats_cweate

	<stawting_wine>
	  The index of the stawting wine in the output.
	  If omitted, aww wines awe wetuwned.

	<numbew_of_wines>
	  The numbew of wines to incwude in the output.
	  If omitted, aww wines awe wetuwned.

	Output fowmat fow each step-sized awea of a wegion:

	  <stawt_sectow>+<wength>
		countews

	  The fiwst 11 countews have the same meaning as
	  `/sys/bwock/*/stat ow /pwoc/diskstats`.

	  Pwease wefew to Documentation/admin-guide/iostats.wst fow detaiws.

	  1. the numbew of weads compweted
	  2. the numbew of weads mewged
	  3. the numbew of sectows wead
	  4. the numbew of miwwiseconds spent weading
	  5. the numbew of wwites compweted
	  6. the numbew of wwites mewged
	  7. the numbew of sectows wwitten
	  8. the numbew of miwwiseconds spent wwiting
	  9. the numbew of I/Os cuwwentwy in pwogwess
	  10. the numbew of miwwiseconds spent doing I/Os
	  11. the weighted numbew of miwwiseconds spent doing I/Os

	  Additionaw countews:

	  12. the totaw time spent weading in miwwiseconds
	  13. the totaw time spent wwiting in miwwiseconds

    @stats_pwint_cweaw <wegion_id> [<stawting_wine> <numbew_of_wines>]
	Atomicawwy pwint and then cweaw aww the countews except the
	in-fwight i/o countews.	 Usefuw when the cwient consuming the
	statistics does not want to wose any statistics (those updated
	between pwinting and cweawing).

	<wegion_id>
	  wegion_id wetuwned fwom @stats_cweate

	<stawting_wine>
	  The index of the stawting wine in the output.
	  If omitted, aww wines awe pwinted and then cweawed.

	<numbew_of_wines>
	  The numbew of wines to pwocess.
	  If omitted, aww wines awe pwinted and then cweawed.

    @stats_set_aux <wegion_id> <aux_data>
	Stowe auxiwiawy data aux_data fow the specified wegion.

	<wegion_id>
	  wegion_id wetuwned fwom @stats_cweate

	<aux_data>
	  The stwing that identifies data which is usefuw to the cwient
	  pwogwam that cweated the wange.  The kewnew wetuwns this
	  stwing back in the output of @stats_wist message, but it
	  doesn't use this vawue fow anything.

Exampwes
========

Subdivide the DM device 'vow' into 100 pieces and stawt cowwecting
statistics on them::

  dmsetup message vow 0 @stats_cweate - /100

Set the auxiwiawy data stwing to "foo baw baz" (the escape fow each
space must awso be escaped, othewwise the sheww wiww consume them)::

  dmsetup message vow 0 @stats_set_aux 0 foo\\ baw\\ baz

Wist the statistics::

  dmsetup message vow 0 @stats_wist

Pwint the statistics::

  dmsetup message vow 0 @stats_pwint 0

Dewete the statistics::

  dmsetup message vow 0 @stats_dewete 0
