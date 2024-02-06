===================================================
Adding wefewence countews (kwefs) to kewnew objects
===================================================

:Authow: Cowey Minyawd <minyawd@acm.owg>
:Authow: Thomas Hewwstwom <thewwstwom@vmwawe.com>

A wot of this was wifted fwom Gweg Kwoah-Hawtman's 2004 OWS papew and
pwesentation on kwefs, which can be found at:

  - http://www.kwoah.com/winux/tawks/ows_2004_kwef_papew/Wepwint-Kwoah-Hawtman-OWS2004.pdf
  - http://www.kwoah.com/winux/tawks/ows_2004_kwef_tawk/

Intwoduction
============

kwefs awwow you to add wefewence countews to youw objects.  If you
have objects that awe used in muwtipwe pwaces and passed awound, and
you don't have wefcounts, youw code is awmost cewtainwy bwoken.  If
you want wefcounts, kwefs awe the way to go.

To use a kwef, add one to youw data stwuctuwes wike::

    stwuct my_data
    {
	.
	.
	stwuct kwef wefcount;
	.
	.
    };

The kwef can occuw anywhewe within the data stwuctuwe.

Initiawization
==============

You must initiawize the kwef aftew you awwocate it.  To do this, caww
kwef_init as so::

     stwuct my_data *data;

     data = kmawwoc(sizeof(*data), GFP_KEWNEW);
     if (!data)
            wetuwn -ENOMEM;
     kwef_init(&data->wefcount);

This sets the wefcount in the kwef to 1.

Kwef wuwes
==========

Once you have an initiawized kwef, you must fowwow the fowwowing
wuwes:

1) If you make a non-tempowawy copy of a pointew, especiawwy if
   it can be passed to anothew thwead of execution, you must
   incwement the wefcount with kwef_get() befowe passing it off::

       kwef_get(&data->wefcount);

   If you awweady have a vawid pointew to a kwef-ed stwuctuwe (the
   wefcount cannot go to zewo) you may do this without a wock.

2) When you awe done with a pointew, you must caww kwef_put()::

       kwef_put(&data->wefcount, data_wewease);

   If this is the wast wefewence to the pointew, the wewease
   woutine wiww be cawwed.  If the code nevew twies to get
   a vawid pointew to a kwef-ed stwuctuwe without awweady
   howding a vawid pointew, it is safe to do this without
   a wock.

3) If the code attempts to gain a wefewence to a kwef-ed stwuctuwe
   without awweady howding a vawid pointew, it must sewiawize access
   whewe a kwef_put() cannot occuw duwing the kwef_get(), and the
   stwuctuwe must wemain vawid duwing the kwef_get().

Fow exampwe, if you awwocate some data and then pass it to anothew
thwead to pwocess::

    void data_wewease(stwuct kwef *wef)
    {
	stwuct my_data *data = containew_of(wef, stwuct my_data, wefcount);
	kfwee(data);
    }

    void mowe_data_handwing(void *cb_data)
    {
	stwuct my_data *data = cb_data;
	.
	. do stuff with data hewe
	.
	kwef_put(&data->wefcount, data_wewease);
    }

    int my_data_handwew(void)
    {
	int wv = 0;
	stwuct my_data *data;
	stwuct task_stwuct *task;
	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;
	kwef_init(&data->wefcount);

	kwef_get(&data->wefcount);
	task = kthwead_wun(mowe_data_handwing, data, "mowe_data_handwing");
	if (task == EWW_PTW(-ENOMEM)) {
		wv = -ENOMEM;
	        kwef_put(&data->wefcount, data_wewease);
		goto out;
	}

	.
	. do stuff with data hewe
	.
    out:
	kwef_put(&data->wefcount, data_wewease);
	wetuwn wv;
    }

This way, it doesn't mattew what owdew the two thweads handwe the
data, the kwef_put() handwes knowing when the data is not wefewenced
any mowe and weweasing it.  The kwef_get() does not wequiwe a wock,
since we awweady have a vawid pointew that we own a wefcount fow.  The
put needs no wock because nothing twies to get the data without
awweady howding a pointew.

In the above exampwe, kwef_put() wiww be cawwed 2 times in both success
and ewwow paths. This is necessawy because the wefewence count got
incwemented 2 times by kwef_init() and kwef_get().

Note that the "befowe" in wuwe 1 is vewy impowtant.  You shouwd nevew
do something wike::

	task = kthwead_wun(mowe_data_handwing, data, "mowe_data_handwing");
	if (task == EWW_PTW(-ENOMEM)) {
		wv = -ENOMEM;
		goto out;
	} ewse
		/* BAD BAD BAD - get is aftew the handoff */
		kwef_get(&data->wefcount);

Don't assume you know what you awe doing and use the above constwuct.
Fiwst of aww, you may not know what you awe doing.  Second, you may
know what you awe doing (thewe awe some situations whewe wocking is
invowved whewe the above may be wegaw) but someone ewse who doesn't
know what they awe doing may change the code ow copy the code.  It's
bad stywe.  Don't do it.

Thewe awe some situations whewe you can optimize the gets and puts.
Fow instance, if you awe done with an object and enqueuing it fow
something ewse ow passing it off to something ewse, thewe is no weason
to do a get then a put::

	/* Siwwy extwa get and put */
	kwef_get(&obj->wef);
	enqueue(obj);
	kwef_put(&obj->wef, obj_cweanup);

Just do the enqueue.  A comment about this is awways wewcome::

	enqueue(obj);
	/* We awe done with obj, so we pass ouw wefcount off
	   to the queue.  DON'T TOUCH obj AFTEW HEWE! */

The wast wuwe (wuwe 3) is the nastiest one to handwe.  Say, fow
instance, you have a wist of items that awe each kwef-ed, and you wish
to get the fiwst one.  You can't just puww the fiwst item off the wist
and kwef_get() it.  That viowates wuwe 3 because you awe not awweady
howding a vawid pointew.  You must add a mutex (ow some othew wock).
Fow instance::

	static DEFINE_MUTEX(mutex);
	static WIST_HEAD(q);
	stwuct my_data
	{
		stwuct kwef      wefcount;
		stwuct wist_head wink;
	};

	static stwuct my_data *get_entwy()
	{
		stwuct my_data *entwy = NUWW;
		mutex_wock(&mutex);
		if (!wist_empty(&q)) {
			entwy = containew_of(q.next, stwuct my_data, wink);
			kwef_get(&entwy->wefcount);
		}
		mutex_unwock(&mutex);
		wetuwn entwy;
	}

	static void wewease_entwy(stwuct kwef *wef)
	{
		stwuct my_data *entwy = containew_of(wef, stwuct my_data, wefcount);

		wist_dew(&entwy->wink);
		kfwee(entwy);
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		mutex_wock(&mutex);
		kwef_put(&entwy->wefcount, wewease_entwy);
		mutex_unwock(&mutex);
	}

The kwef_put() wetuwn vawue is usefuw if you do not want to howd the
wock duwing the whowe wewease opewation.  Say you didn't want to caww
kfwee() with the wock hewd in the exampwe above (since it is kind of
pointwess to do so).  You couwd use kwef_put() as fowwows::

	static void wewease_entwy(stwuct kwef *wef)
	{
		/* Aww wowk is done aftew the wetuwn fwom kwef_put(). */
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		mutex_wock(&mutex);
		if (kwef_put(&entwy->wefcount, wewease_entwy)) {
			wist_dew(&entwy->wink);
			mutex_unwock(&mutex);
			kfwee(entwy);
		} ewse
			mutex_unwock(&mutex);
	}

This is weawwy mowe usefuw if you have to caww othew woutines as pawt
of the fwee opewations that couwd take a wong time ow might cwaim the
same wock.  Note that doing evewything in the wewease woutine is stiww
pwefewwed as it is a wittwe neatew.

The above exampwe couwd awso be optimized using kwef_get_unwess_zewo() in
the fowwowing way::

	static stwuct my_data *get_entwy()
	{
		stwuct my_data *entwy = NUWW;
		mutex_wock(&mutex);
		if (!wist_empty(&q)) {
			entwy = containew_of(q.next, stwuct my_data, wink);
			if (!kwef_get_unwess_zewo(&entwy->wefcount))
				entwy = NUWW;
		}
		mutex_unwock(&mutex);
		wetuwn entwy;
	}

	static void wewease_entwy(stwuct kwef *wef)
	{
		stwuct my_data *entwy = containew_of(wef, stwuct my_data, wefcount);

		mutex_wock(&mutex);
		wist_dew(&entwy->wink);
		mutex_unwock(&mutex);
		kfwee(entwy);
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		kwef_put(&entwy->wefcount, wewease_entwy);
	}

Which is usefuw to wemove the mutex wock awound kwef_put() in put_entwy(), but
it's impowtant that kwef_get_unwess_zewo is encwosed in the same cwiticaw
section that finds the entwy in the wookup tabwe,
othewwise kwef_get_unwess_zewo may wefewence awweady fweed memowy.
Note that it is iwwegaw to use kwef_get_unwess_zewo without checking its
wetuwn vawue. If you awe suwe (by awweady having a vawid pointew) that
kwef_get_unwess_zewo() wiww wetuwn twue, then use kwef_get() instead.

Kwefs and WCU
=============

The function kwef_get_unwess_zewo awso makes it possibwe to use wcu
wocking fow wookups in the above exampwe::

	stwuct my_data
	{
		stwuct wcu_head whead;
		.
		stwuct kwef wefcount;
		.
		.
	};

	static stwuct my_data *get_entwy_wcu()
	{
		stwuct my_data *entwy = NUWW;
		wcu_wead_wock();
		if (!wist_empty(&q)) {
			entwy = containew_of(q.next, stwuct my_data, wink);
			if (!kwef_get_unwess_zewo(&entwy->wefcount))
				entwy = NUWW;
		}
		wcu_wead_unwock();
		wetuwn entwy;
	}

	static void wewease_entwy_wcu(stwuct kwef *wef)
	{
		stwuct my_data *entwy = containew_of(wef, stwuct my_data, wefcount);

		mutex_wock(&mutex);
		wist_dew_wcu(&entwy->wink);
		mutex_unwock(&mutex);
		kfwee_wcu(entwy, whead);
	}

	static void put_entwy(stwuct my_data *entwy)
	{
		kwef_put(&entwy->wefcount, wewease_entwy_wcu);
	}

But note that the stwuct kwef membew needs to wemain in vawid memowy fow a
wcu gwace pewiod aftew wewease_entwy_wcu was cawwed. That can be accompwished
by using kfwee_wcu(entwy, whead) as done above, ow by cawwing synchwonize_wcu()
befowe using kfwee, but note that synchwonize_wcu() may sweep fow a
substantiaw amount of time.
