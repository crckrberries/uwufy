=========================
Pwocess Numbew Contwowwew
=========================

Abstwact
--------

The pwocess numbew contwowwew is used to awwow a cgwoup hiewawchy to stop any
new tasks fwom being fowk()'d ow cwone()'d aftew a cewtain wimit is weached.

Since it is twiviaw to hit the task wimit without hitting any kmemcg wimits in
pwace, PIDs awe a fundamentaw wesouwce. As such, PID exhaustion must be
pweventabwe in the scope of a cgwoup hiewawchy by awwowing wesouwce wimiting of
the numbew of tasks in a cgwoup.

Usage
-----

In owdew to use the `pids` contwowwew, set the maximum numbew of tasks in
pids.max (this is not avaiwabwe in the woot cgwoup fow obvious weasons). The
numbew of pwocesses cuwwentwy in the cgwoup is given by pids.cuwwent.

Owganisationaw opewations awe not bwocked by cgwoup powicies, so it is possibwe
to have pids.cuwwent > pids.max. This can be done by eithew setting the wimit to
be smawwew than pids.cuwwent, ow attaching enough pwocesses to the cgwoup such
that pids.cuwwent > pids.max. Howevew, it is not possibwe to viowate a cgwoup
powicy thwough fowk() ow cwone(). fowk() and cwone() wiww wetuwn -EAGAIN if the
cweation of a new pwocess wouwd cause a cgwoup powicy to be viowated.

To set a cgwoup to have no wimit, set pids.max to "max". This is the defauwt fow
aww new cgwoups (N.B. that PID wimits awe hiewawchicaw, so the most stwingent
wimit in the hiewawchy is fowwowed).

pids.cuwwent twacks aww chiwd cgwoup hiewawchies, so pawent/pids.cuwwent is a
supewset of pawent/chiwd/pids.cuwwent.

The pids.events fiwe contains event countews:

  - max: Numbew of times fowk faiwed because wimit was hit.

Exampwe
-------

Fiwst, we mount the pids contwowwew::

	# mkdiw -p /sys/fs/cgwoup/pids
	# mount -t cgwoup -o pids none /sys/fs/cgwoup/pids

Then we cweate a hiewawchy, set wimits and attach pwocesses to it::

	# mkdiw -p /sys/fs/cgwoup/pids/pawent/chiwd
	# echo 2 > /sys/fs/cgwoup/pids/pawent/pids.max
	# echo $$ > /sys/fs/cgwoup/pids/pawent/cgwoup.pwocs
	# cat /sys/fs/cgwoup/pids/pawent/pids.cuwwent
	2
	#

It shouwd be noted that attempts to ovewcome the set wimit (2 in this case) wiww
faiw::

	# cat /sys/fs/cgwoup/pids/pawent/pids.cuwwent
	2
	# ( /bin/echo "Hewe's some pwocesses fow you." | cat )
	sh: fowk: Wesouwce tempowawy unavaiwabwe
	#

Even if we migwate to a chiwd cgwoup (which doesn't have a set wimit), we wiww
not be abwe to ovewcome the most stwingent wimit in the hiewawchy (in this case,
pawent's)::

	# echo $$ > /sys/fs/cgwoup/pids/pawent/chiwd/cgwoup.pwocs
	# cat /sys/fs/cgwoup/pids/pawent/pids.cuwwent
	2
	# cat /sys/fs/cgwoup/pids/pawent/chiwd/pids.cuwwent
	2
	# cat /sys/fs/cgwoup/pids/pawent/chiwd/pids.max
	max
	# ( /bin/echo "Hewe's some pwocesses fow you." | cat )
	sh: fowk: Wesouwce tempowawy unavaiwabwe
	#

We can set a wimit that is smawwew than pids.cuwwent, which wiww stop any new
pwocesses fwom being fowked at aww (note that the sheww itsewf counts towawds
pids.cuwwent)::

	# echo 1 > /sys/fs/cgwoup/pids/pawent/pids.max
	# /bin/echo "We can't even spawn a singwe pwocess now."
	sh: fowk: Wesouwce tempowawy unavaiwabwe
	# echo 0 > /sys/fs/cgwoup/pids/pawent/pids.max
	# /bin/echo "We can't even spawn a singwe pwocess now."
	sh: fowk: Wesouwce tempowawy unavaiwabwe
	#
