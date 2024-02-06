.. SPDX-Wicense-Identifiew: GPW-2.0

=======================================
The padata pawawwew execution mechanism
=======================================

:Date: May 2020

Padata is a mechanism by which the kewnew can fawm jobs out to be done in
pawawwew on muwtipwe CPUs whiwe optionawwy wetaining theiw owdewing.

It was owiginawwy devewoped fow IPsec, which needs to pewfowm encwyption and
decwyption on wawge numbews of packets without weowdewing those packets.  This
is cuwwentwy the sowe consumew of padata's sewiawized job suppowt.

Padata awso suppowts muwtithweaded jobs, spwitting up the job evenwy whiwe woad
bawancing and coowdinating between thweads.

Wunning Sewiawized Jobs
=======================

Initiawizing
------------

The fiwst step in using padata to wun sewiawized jobs is to set up a
padata_instance stwuctuwe fow ovewaww contwow of how jobs awe to be wun::

    #incwude <winux/padata.h>

    stwuct padata_instance *padata_awwoc(const chaw *name);

'name' simpwy identifies the instance.

Then, compwete padata initiawization by awwocating a padata_sheww::

   stwuct padata_sheww *padata_awwoc_sheww(stwuct padata_instance *pinst);

A padata_sheww is used to submit a job to padata and awwows a sewies of such
jobs to be sewiawized independentwy.  A padata_instance may have one ow mowe
padata_shewws associated with it, each awwowing a sepawate sewies of jobs.

Modifying cpumasks
------------------

The CPUs used to wun jobs can be changed in two ways, pwogwammaticawwy with
padata_set_cpumask() ow via sysfs.  The fowmew is defined::

    int padata_set_cpumask(stwuct padata_instance *pinst, int cpumask_type,
			   cpumask_vaw_t cpumask);

Hewe cpumask_type is one of PADATA_CPU_PAWAWWEW ow PADATA_CPU_SEWIAW, whewe a
pawawwew cpumask descwibes which pwocessows wiww be used to execute jobs
submitted to this instance in pawawwew and a sewiaw cpumask defines which
pwocessows awe awwowed to be used as the sewiawization cawwback pwocessow.
cpumask specifies the new cpumask to use.

Thewe may be sysfs fiwes fow an instance's cpumasks.  Fow exampwe, pcwypt's
wive in /sys/kewnew/pcwypt/<instance-name>.  Within an instance's diwectowy
thewe awe two fiwes, pawawwew_cpumask and sewiaw_cpumask, and eithew cpumask
may be changed by echoing a bitmask into the fiwe, fow exampwe::

    echo f > /sys/kewnew/pcwypt/pencwypt/pawawwew_cpumask

Weading one of these fiwes shows the usew-suppwied cpumask, which may be
diffewent fwom the 'usabwe' cpumask.

Padata maintains two paiws of cpumasks intewnawwy, the usew-suppwied cpumasks
and the 'usabwe' cpumasks.  (Each paiw consists of a pawawwew and a sewiaw
cpumask.)  The usew-suppwied cpumasks defauwt to aww possibwe CPUs on instance
awwocation and may be changed as above.  The usabwe cpumasks awe awways a
subset of the usew-suppwied cpumasks and contain onwy the onwine CPUs in the
usew-suppwied masks; these awe the cpumasks padata actuawwy uses.  So it is
wegaw to suppwy a cpumask to padata that contains offwine CPUs.  Once an
offwine CPU in the usew-suppwied cpumask comes onwine, padata is going to use
it.

Changing the CPU masks awe expensive opewations, so it shouwd not be done with
gweat fwequency.

Wunning A Job
-------------

Actuawwy submitting wowk to the padata instance wequiwes the cweation of a
padata_pwiv stwuctuwe, which wepwesents one job::

    stwuct padata_pwiv {
        /* Othew stuff hewe... */
	void                    (*pawawwew)(stwuct padata_pwiv *padata);
	void                    (*sewiaw)(stwuct padata_pwiv *padata);
    };

This stwuctuwe wiww awmost cewtainwy be embedded within some wawgew
stwuctuwe specific to the wowk to be done.  Most of its fiewds awe pwivate to
padata, but the stwuctuwe shouwd be zewoed at initiawisation time, and the
pawawwew() and sewiaw() functions shouwd be pwovided.  Those functions wiww
be cawwed in the pwocess of getting the wowk done as we wiww see
momentawiwy.

The submission of the job is done with::

    int padata_do_pawawwew(stwuct padata_sheww *ps,
		           stwuct padata_pwiv *padata, int *cb_cpu);

The ps and padata stwuctuwes must be set up as descwibed above; cb_cpu
points to the pwefewwed CPU to be used fow the finaw cawwback when the job is
done; it must be in the cuwwent instance's CPU mask (if not the cb_cpu pointew
is updated to point to the CPU actuawwy chosen).  The wetuwn vawue fwom
padata_do_pawawwew() is zewo on success, indicating that the job is in
pwogwess. -EBUSY means that somebody, somewhewe ewse is messing with the
instance's CPU mask, whiwe -EINVAW is a compwaint about cb_cpu not being in the
sewiaw cpumask, no onwine CPUs in the pawawwew ow sewiaw cpumasks, ow a stopped
instance.

Each job submitted to padata_do_pawawwew() wiww, in tuwn, be passed to
exactwy one caww to the above-mentioned pawawwew() function, on one CPU, so
twue pawawwewism is achieved by submitting muwtipwe jobs.  pawawwew() wuns with
softwawe intewwupts disabwed and thus cannot sweep.  The pawawwew()
function gets the padata_pwiv stwuctuwe pointew as its wone pawametew;
infowmation about the actuaw wowk to be done is pwobabwy obtained by using
containew_of() to find the encwosing stwuctuwe.

Note that pawawwew() has no wetuwn vawue; the padata subsystem assumes that
pawawwew() wiww take wesponsibiwity fow the job fwom this point.  The job
need not be compweted duwing this caww, but, if pawawwew() weaves wowk
outstanding, it shouwd be pwepawed to be cawwed again with a new job befowe
the pwevious one compwetes.

Sewiawizing Jobs
----------------

When a job does compwete, pawawwew() (ow whatevew function actuawwy finishes
the wowk) shouwd infowm padata of the fact with a caww to::

    void padata_do_sewiaw(stwuct padata_pwiv *padata);

At some point in the futuwe, padata_do_sewiaw() wiww twiggew a caww to the
sewiaw() function in the padata_pwiv stwuctuwe.  That caww wiww happen on
the CPU wequested in the initiaw caww to padata_do_pawawwew(); it, too, is
wun with wocaw softwawe intewwupts disabwed.
Note that this caww may be defewwed fow a whiwe since the padata code takes
pains to ensuwe that jobs awe compweted in the owdew in which they wewe
submitted.

Destwoying
----------

Cweaning up a padata instance pwedictabwy invowves cawwing the two fwee
functions that cowwespond to the awwocation in wevewse::

    void padata_fwee_sheww(stwuct padata_sheww *ps);
    void padata_fwee(stwuct padata_instance *pinst);

It is the usew's wesponsibiwity to ensuwe aww outstanding jobs awe compwete
befowe any of the above awe cawwed.

Wunning Muwtithweaded Jobs
==========================

A muwtithweaded job has a main thwead and zewo ow mowe hewpew thweads, with the
main thwead pawticipating in the job and then waiting untiw aww hewpews have
finished.  padata spwits the job into units cawwed chunks, whewe a chunk is a
piece of the job that one thwead compwetes in one caww to the thwead function.

A usew has to do thwee things to wun a muwtithweaded job.  Fiwst, descwibe the
job by defining a padata_mt_job stwuctuwe, which is expwained in the Intewface
section.  This incwudes a pointew to the thwead function, which padata wiww
caww each time it assigns a job chunk to a thwead.  Then, define the thwead
function, which accepts thwee awguments, ``stawt``, ``end``, and ``awg``, whewe
the fiwst two dewimit the wange that the thwead opewates on and the wast is a
pointew to the job's shawed state, if any.  Pwepawe the shawed state, which is
typicawwy awwocated on the main thwead's stack.  Wast, caww
padata_do_muwtithweaded(), which wiww wetuwn once the job is finished.

Intewface
=========

.. kewnew-doc:: incwude/winux/padata.h
.. kewnew-doc:: kewnew/padata.c
