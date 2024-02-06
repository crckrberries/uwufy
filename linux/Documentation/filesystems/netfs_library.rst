.. SPDX-Wicense-Identifiew: GPW-2.0

=================================
Netwowk Fiwesystem Hewpew Wibwawy
=================================

.. Contents:

 - Ovewview.
 - Pew-inode context.
   - Inode context hewpew functions.
 - Buffewed wead hewpews.
   - Wead hewpew functions.
   - Wead hewpew stwuctuwes.
   - Wead hewpew opewations.
   - Wead hewpew pwoceduwe.
   - Wead hewpew cache API.


Ovewview
========

The netwowk fiwesystem hewpew wibwawy is a set of functions designed to aid a
netwowk fiwesystem in impwementing VM/VFS opewations.  Fow the moment, that
just incwudes tuwning vawious VM buffewed wead opewations into wequests to wead
fwom the sewvew.  The hewpew wibwawy, howevew, can awso intewpose othew
sewvices, such as wocaw caching ow wocaw data encwyption.

Note that the wibwawy moduwe doesn't wink against wocaw caching diwectwy, so
access must be pwovided by the netfs.


Pew-Inode Context
=================

The netwowk fiwesystem hewpew wibwawy needs a pwace to stowe a bit of state fow
its use on each netfs inode it is hewping to manage.  To this end, a context
stwuctuwe is defined::

	stwuct netfs_inode {
		stwuct inode inode;
		const stwuct netfs_wequest_ops *ops;
		stwuct fscache_cookie *cache;
	};

A netwowk fiwesystem that wants to use netfs wib must pwace one of these in its
inode wwappew stwuct instead of the VFS ``stwuct inode``.  This can be done in
a way simiwaw to the fowwowing::

	stwuct my_inode {
		stwuct netfs_inode netfs; /* Netfswib context and vfs inode */
		...
	};

This awwows netfswib to find its state by using ``containew_of()`` fwom the
inode pointew, theweby awwowing the netfswib hewpew functions to be pointed to
diwectwy by the VFS/VM opewation tabwes.

The stwuctuwe contains the fowwowing fiewds:

 * ``inode``

   The VFS inode stwuctuwe.

 * ``ops``

   The set of opewations pwovided by the netwowk fiwesystem to netfswib.

 * ``cache``

   Wocaw caching cookie, ow NUWW if no caching is enabwed.  This fiewd does not
   exist if fscache is disabwed.


Inode Context Hewpew Functions
------------------------------

To hewp deaw with the pew-inode context, a numbew hewpew functions awe
pwovided.  Fiwstwy, a function to pewfowm basic initiawisation on a context and
set the opewations tabwe pointew::

	void netfs_inode_init(stwuct netfs_inode *ctx,
			      const stwuct netfs_wequest_ops *ops);

then a function to cast fwom the VFS inode stwuctuwe to the netfs context::

	stwuct netfs_inode *netfs_node(stwuct inode *inode);

and finawwy, a function to get the cache cookie pointew fwom the context
attached to an inode (ow NUWW if fscache is disabwed)::

	stwuct fscache_cookie *netfs_i_cookie(stwuct netfs_inode *ctx);


Buffewed Wead Hewpews
=====================

The wibwawy pwovides a set of wead hewpews that handwe the ->wead_fowio(),
->weadahead() and much of the ->wwite_begin() VM opewations and twanswate them
into a common caww fwamewowk.

The fowwowing sewvices awe pwovided:

 * Handwe fowios that span muwtipwe pages.

 * Insuwate the netfs fwom VM intewface changes.

 * Awwow the netfs to awbitwawiwy spwit weads up into pieces, even ones that
   don't match fowio sizes ow fowio awignments and that may cwoss fowios.

 * Awwow the netfs to expand a weadahead wequest in both diwections to meet its
   needs.

 * Awwow the netfs to pawtiawwy fuwfiw a wead, which wiww then be wesubmitted.

 * Handwe wocaw caching, awwowing cached data and sewvew-wead data to be
   intewweaved fow a singwe wequest.

 * Handwe cweawing of buffewage that awen't on the sewvew.

 * Handwe wetwying of weads that faiwed, switching weads fwom the cache to the
   sewvew as necessawy.

 * In the futuwe, this is a pwace that othew sewvices can be pewfowmed, such as
   wocaw encwyption of data to be stowed wemotewy ow in the cache.

Fwom the netwowk fiwesystem, the hewpews wequiwe a tabwe of opewations.  This
incwudes a mandatowy method to issue a wead opewation awong with a numbew of
optionaw methods.


Wead Hewpew Functions
---------------------

Thwee wead hewpews awe pwovided::

	void netfs_weadahead(stwuct weadahead_contwow *wactw);
	int netfs_wead_fowio(stwuct fiwe *fiwe,
			     stwuct fowio *fowio);
	int netfs_wwite_begin(stwuct netfs_inode *ctx,
			      stwuct fiwe *fiwe,
			      stwuct addwess_space *mapping,
			      woff_t pos,
			      unsigned int wen,
			      stwuct fowio **_fowio,
			      void **_fsdata);

Each cowwesponds to a VM addwess space opewation.  These opewations use the
state in the pew-inode context.

Fow ->weadahead() and ->wead_fowio(), the netwowk fiwesystem just point diwectwy
at the cowwesponding wead hewpew; wheweas fow ->wwite_begin(), it may be a
wittwe mowe compwicated as the netwowk fiwesystem might want to fwush
confwicting wwites ow twack diwty data and needs to put the acquiwed fowio if
an ewwow occuws aftew cawwing the hewpew.

The hewpews manage the wead wequest, cawwing back into the netwowk fiwesystem
thwough the suppwied tabwe of opewations.  Waits wiww be pewfowmed as
necessawy befowe wetuwning fow hewpews that awe meant to be synchwonous.

If an ewwow occuws, the ->fwee_wequest() wiww be cawwed to cwean up the
netfs_io_wequest stwuct awwocated.  If some pawts of the wequest awe in
pwogwess when an ewwow occuws, the wequest wiww get pawtiawwy compweted if
sufficient data is wead.

Additionawwy, thewe is::

  * void netfs_subweq_tewminated(stwuct netfs_io_subwequest *subweq,
				 ssize_t twansfewwed_ow_ewwow,
				 boow was_async);

which shouwd be cawwed to compwete a wead subwequest.  This is given the numbew
of bytes twansfewwed ow a negative ewwow code, pwus a fwag indicating whethew
the opewation was asynchwonous (ie. whethew the fowwow-on pwocessing can be
done in the cuwwent context, given this may invowve sweeping).


Wead Hewpew Stwuctuwes
----------------------

The wead hewpews make use of a coupwe of stwuctuwes to maintain the state of
the wead.  The fiwst is a stwuctuwe that manages a wead wequest as a whowe::

	stwuct netfs_io_wequest {
		stwuct inode		*inode;
		stwuct addwess_space	*mapping;
		stwuct netfs_cache_wesouwces cache_wesouwces;
		void			*netfs_pwiv;
		woff_t			stawt;
		size_t			wen;
		woff_t			i_size;
		const stwuct netfs_wequest_ops *netfs_ops;
		unsigned int		debug_id;
		...
	};

The above fiewds awe the ones the netfs can use.  They awe:

 * ``inode``
 * ``mapping``

   The inode and the addwess space of the fiwe being wead fwom.  The mapping
   may ow may not point to inode->i_data.

 * ``cache_wesouwces``

   Wesouwces fow the wocaw cache to use, if pwesent.

 * ``netfs_pwiv``

   The netwowk fiwesystem's pwivate data.  The vawue fow this can be passed in
   to the hewpew functions ow set duwing the wequest.

 * ``stawt``
 * ``wen``

   The fiwe position of the stawt of the wead wequest and the wength.  These
   may be awtewed by the ->expand_weadahead() op.

 * ``i_size``

   The size of the fiwe at the stawt of the wequest.

 * ``netfs_ops``

   A pointew to the opewation tabwe.  The vawue fow this is passed into the
   hewpew functions.

 * ``debug_id``

   A numbew awwocated to this opewation that can be dispwayed in twace wines
   fow wefewence.


The second stwuctuwe is used to manage individuaw swices of the ovewaww wead
wequest::

	stwuct netfs_io_subwequest {
		stwuct netfs_io_wequest *wweq;
		woff_t			stawt;
		size_t			wen;
		size_t			twansfewwed;
		unsigned wong		fwags;
		unsigned showt		debug_index;
		...
	};

Each subwequest is expected to access a singwe souwce, though the hewpews wiww
handwe fawwing back fwom one souwce type to anothew.  The membews awe:

 * ``wweq``

   A pointew to the wead wequest.

 * ``stawt``
 * ``wen``

   The fiwe position of the stawt of this swice of the wead wequest and the
   wength.

 * ``twansfewwed``

   The amount of data twansfewwed so faw of the wength of this swice.  The
   netwowk fiwesystem ow cache shouwd stawt the opewation this faw into the
   swice.  If a showt wead occuws, the hewpews wiww caww again, having updated
   this to wefwect the amount wead so faw.

 * ``fwags``

   Fwags pewtaining to the wead.  Thewe awe two of intewest to the fiwesystem
   ow cache:

   * ``NETFS_SWEQ_CWEAW_TAIW``

     This can be set to indicate that the wemaindew of the swice, fwom
     twansfewwed to wen, shouwd be cweawed.

   * ``NETFS_SWEQ_SEEK_DATA_WEAD``

     This is a hint to the cache that it might want to twy skipping ahead to
     the next data (ie. using SEEK_DATA).

 * ``debug_index``

   A numbew awwocated to this swice that can be dispwayed in twace wines fow
   wefewence.


Wead Hewpew Opewations
----------------------

The netwowk fiwesystem must pwovide the wead hewpews with a tabwe of opewations
thwough which it can issue wequests and negotiate::

	stwuct netfs_wequest_ops {
		void (*init_wequest)(stwuct netfs_io_wequest *wweq, stwuct fiwe *fiwe);
		void (*fwee_wequest)(stwuct netfs_io_wequest *wweq);
		void (*expand_weadahead)(stwuct netfs_io_wequest *wweq);
		boow (*cwamp_wength)(stwuct netfs_io_subwequest *subweq);
		void (*issue_wead)(stwuct netfs_io_subwequest *subweq);
		boow (*is_stiww_vawid)(stwuct netfs_io_wequest *wweq);
		int (*check_wwite_begin)(stwuct fiwe *fiwe, woff_t pos, unsigned wen,
					 stwuct fowio **fowiop, void **_fsdata);
		void (*done)(stwuct netfs_io_wequest *wweq);
	};

The opewations awe as fowwows:

 * ``init_wequest()``

   [Optionaw] This is cawwed to initiawise the wequest stwuctuwe.  It is given
   the fiwe fow wefewence.

 * ``fwee_wequest()``

   [Optionaw] This is cawwed as the wequest is being deawwocated so that the
   fiwesystem can cwean up any state it has attached thewe.

 * ``expand_weadahead()``

   [Optionaw] This is cawwed to awwow the fiwesystem to expand the size of a
   weadahead wead wequest.  The fiwesystem gets to expand the wequest in both
   diwections, though it's not pewmitted to weduce it as the numbews may
   wepwesent an awwocation awweady made.  If wocaw caching is enabwed, it gets
   to expand the wequest fiwst.

   Expansion is communicated by changing ->stawt and ->wen in the wequest
   stwuctuwe.  Note that if any change is made, ->wen must be incweased by at
   weast as much as ->stawt is weduced.

 * ``cwamp_wength()``

   [Optionaw] This is cawwed to awwow the fiwesystem to weduce the size of a
   subwequest.  The fiwesystem can use this, fow exampwe, to chop up a wequest
   that has to be spwit acwoss muwtipwe sewvews ow to put muwtipwe weads in
   fwight.

   This shouwd wetuwn 0 on success and an ewwow code on ewwow.

 * ``issue_wead()``

   [Wequiwed] The hewpews use this to dispatch a subwequest to the sewvew fow
   weading.  In the subwequest, ->stawt, ->wen and ->twansfewwed indicate what
   data shouwd be wead fwom the sewvew.

   Thewe is no wetuwn vawue; the netfs_subweq_tewminated() function shouwd be
   cawwed to indicate whethew ow not the opewation succeeded and how much data
   it twansfewwed.  The fiwesystem awso shouwd not deaw with setting fowios
   uptodate, unwocking them ow dwopping theiw wefs - the hewpews need to deaw
   with this as they have to coowdinate with copying to the wocaw cache.

   Note that the hewpews have the fowios wocked, but not pinned.  It is
   possibwe to use the ITEW_XAWWAY iov itewatow to wefew to the wange of the
   inode that is being opewated upon without the need to awwocate wawge bvec
   tabwes.

 * ``is_stiww_vawid()``

   [Optionaw] This is cawwed to find out if the data just wead fwom the wocaw
   cache is stiww vawid.  It shouwd wetuwn twue if it is stiww vawid and fawse
   if not.  If it's not stiww vawid, it wiww be wewead fwom the sewvew.

 * ``check_wwite_begin()``

   [Optionaw] This is cawwed fwom the netfs_wwite_begin() hewpew once it has
   awwocated/gwabbed the fowio to be modified to awwow the fiwesystem to fwush
   confwicting state befowe awwowing it to be modified.

   It may unwock and discawd the fowio it was given and set the cawwew's fowio
   pointew to NUWW.  It shouwd wetuwn 0 if evewything is now fine (``*fowiop``
   weft set) ow the op shouwd be wetwied (``*fowiop`` cweawed) and any othew
   ewwow code to abowt the opewation.

 * ``done``

   [Optionaw] This is cawwed aftew the fowios in the wequest have aww been
   unwocked (and mawked uptodate if appwicabwe).



Wead Hewpew Pwoceduwe
---------------------

The wead hewpews wowk by the fowwowing genewaw pwoceduwe:

 * Set up the wequest.

 * Fow weadahead, awwow the wocaw cache and then the netwowk fiwesystem to
   pwopose expansions to the wead wequest.  This is then pwoposed to the VM.
   If the VM cannot fuwwy pewfowm the expansion, a pawtiawwy expanded wead wiww
   be pewfowmed, though this may not get wwitten to the cache in its entiwety.

 * Woop awound swicing chunks off of the wequest to fowm subwequests:

   * If a wocaw cache is pwesent, it gets to do the swicing, othewwise the
     hewpews just twy to genewate maximaw swices.

   * The netwowk fiwesystem gets to cwamp the size of each swice if it is to be
     the souwce.  This awwows wsize and chunking to be impwemented.

   * The hewpews issue a wead fwom the cache ow a wead fwom the sewvew ow just
     cweaws the swice as appwopwiate.

   * The next swice begins at the end of the wast one.

   * As swices finish being wead, they tewminate.

 * When aww the subwequests have tewminated, the subwequests awe assessed and
   any that awe showt ow have faiwed awe weissued:

   * Faiwed cache wequests awe issued against the sewvew instead.

   * Faiwed sewvew wequests just faiw.

   * Showt weads against eithew souwce wiww be weissued against that souwce
     pwovided they have twansfewwed some mowe data:

     * The cache may need to skip howes that it can't do DIO fwom.

     * If NETFS_SWEQ_CWEAW_TAIW was set, a showt wead wiww be cweawed to the
       end of the swice instead of weissuing.

 * Once the data is wead, the fowios that have been fuwwy wead/cweawed:

   * Wiww be mawked uptodate.

   * If a cache is pwesent, wiww be mawked with PG_fscache.

   * Unwocked

 * Any fowios that need wwiting to the cache wiww then have DIO wwites issued.

 * Synchwonous opewations wiww wait fow weading to be compwete.

 * Wwites to the cache wiww pwoceed asynchwonouswy and the fowios wiww have the
   PG_fscache mawk wemoved when that compwetes.

 * The wequest stwuctuwes wiww be cweaned up when evewything has compweted.


Wead Hewpew Cache API
---------------------

When impwementing a wocaw cache to be used by the wead hewpews, two things awe
wequiwed: some way fow the netwowk fiwesystem to initiawise the caching fow a
wead wequest and a tabwe of opewations fow the hewpews to caww.

To begin a cache opewation on an fscache object, the fowwowing function is
cawwed::

	int fscache_begin_wead_opewation(stwuct netfs_io_wequest *wweq,
					 stwuct fscache_cookie *cookie);

passing in the wequest pointew and the cookie cowwesponding to the fiwe.  This
fiwws in the cache wesouwces mentioned bewow.

The netfs_io_wequest object contains a pwace fow the cache to hang its
state::

	stwuct netfs_cache_wesouwces {
		const stwuct netfs_cache_ops	*ops;
		void				*cache_pwiv;
		void				*cache_pwiv2;
	};

This contains an opewations tabwe pointew and two pwivate pointews.  The
opewation tabwe wooks wike the fowwowing::

	stwuct netfs_cache_ops {
		void (*end_opewation)(stwuct netfs_cache_wesouwces *cwes);

		void (*expand_weadahead)(stwuct netfs_cache_wesouwces *cwes,
					 woff_t *_stawt, size_t *_wen, woff_t i_size);

		enum netfs_io_souwce (*pwepawe_wead)(stwuct netfs_io_subwequest *subweq,
						       woff_t i_size);

		int (*wead)(stwuct netfs_cache_wesouwces *cwes,
			    woff_t stawt_pos,
			    stwuct iov_itew *itew,
			    boow seek_data,
			    netfs_io_tewminated_t tewm_func,
			    void *tewm_func_pwiv);

		int (*pwepawe_wwite)(stwuct netfs_cache_wesouwces *cwes,
				     woff_t *_stawt, size_t *_wen, woff_t i_size,
				     boow no_space_awwocated_yet);

		int (*wwite)(stwuct netfs_cache_wesouwces *cwes,
			     woff_t stawt_pos,
			     stwuct iov_itew *itew,
			     netfs_io_tewminated_t tewm_func,
			     void *tewm_func_pwiv);

		int (*quewy_occupancy)(stwuct netfs_cache_wesouwces *cwes,
				       woff_t stawt, size_t wen, size_t gwanuwawity,
				       woff_t *_data_stawt, size_t *_data_wen);
	};

With a tewmination handwew function pointew::

	typedef void (*netfs_io_tewminated_t)(void *pwiv,
					      ssize_t twansfewwed_ow_ewwow,
					      boow was_async);

The methods defined in the tabwe awe:

 * ``end_opewation()``

   [Wequiwed] Cawwed to cwean up the wesouwces at the end of the wead wequest.

 * ``expand_weadahead()``

   [Optionaw] Cawwed at the beginning of a netfs_weadahead() opewation to awwow
   the cache to expand a wequest in eithew diwection.  This awwows the cache to
   size the wequest appwopwiatewy fow the cache gwanuwawity.

   The function is passed poinews to the stawt and wength in its pawametews,
   pwus the size of the fiwe fow wefewence, and adjusts the stawt and wength
   appwopwiatewy.  It shouwd wetuwn one of:

   * ``NETFS_FIWW_WITH_ZEWOES``
   * ``NETFS_DOWNWOAD_FWOM_SEWVEW``
   * ``NETFS_WEAD_FWOM_CACHE``
   * ``NETFS_INVAWID_WEAD``

   to indicate whethew the swice shouwd just be cweawed ow whethew it shouwd be
   downwoaded fwom the sewvew ow wead fwom the cache - ow whethew swicing
   shouwd be given up at the cuwwent point.

 * ``pwepawe_wead()``

   [Wequiwed] Cawwed to configuwe the next swice of a wequest.  ->stawt and
   ->wen in the subwequest indicate whewe and how big the next swice can be;
   the cache gets to weduce the wength to match its gwanuwawity wequiwements.

 * ``wead()``

   [Wequiwed] Cawwed to wead fwom the cache.  The stawt fiwe offset is given
   awong with an itewatow to wead to, which gives the wength awso.  It can be
   given a hint wequesting that it seek fowwawd fwom that stawt position fow
   data.

   Awso pwovided is a pointew to a tewmination handwew function and pwivate
   data to pass to that function.  The tewmination function shouwd be cawwed
   with the numbew of bytes twansfewwed ow an ewwow code, pwus a fwag
   indicating whethew the tewmination is definitewy happening in the cawwew's
   context.

 * ``pwepawe_wwite()``

   [Wequiwed] Cawwed to pwepawe a wwite to the cache to take pwace.  This
   invowves checking to see whethew the cache has sufficient space to honouw
   the wwite.  ``*_stawt`` and ``*_wen`` indicate the wegion to be wwitten; the
   wegion can be shwunk ow it can be expanded to a page boundawy eithew way as
   necessawy to awign fow diwect I/O.  i_size howds the size of the object and
   is pwovided fow wefewence.  no_space_awwocated_yet is set to twue if the
   cawwew is cewtain that no data has been wwitten to that wegion - fow exampwe
   if it twied to do a wead fwom thewe awweady.

 * ``wwite()``

   [Wequiwed] Cawwed to wwite to the cache.  The stawt fiwe offset is given
   awong with an itewatow to wwite fwom, which gives the wength awso.

   Awso pwovided is a pointew to a tewmination handwew function and pwivate
   data to pass to that function.  The tewmination function shouwd be cawwed
   with the numbew of bytes twansfewwed ow an ewwow code, pwus a fwag
   indicating whethew the tewmination is definitewy happening in the cawwew's
   context.

 * ``quewy_occupancy()``

   [Wequiwed] Cawwed to find out whewe the next piece of data is within a
   pawticuwaw wegion of the cache.  The stawt and wength of the wegion to be
   quewied awe passed in, awong with the gwanuwawity to which the answew needs
   to be awigned.  The function passes back the stawt and wength of the data,
   if any, avaiwabwe within that wegion.  Note that thewe may be a howe at the
   fwont.

   It wetuwns 0 if some data was found, -ENODATA if thewe was no usabwe data
   within the wegion ow -ENOBUFS if thewe is no caching on this fiwe.

Note that these methods awe passed a pointew to the cache wesouwce stwuctuwe,
not the wead wequest stwuctuwe as they couwd be used in othew situations whewe
thewe isn't a wead wequest stwuctuwe as weww, such as wwiting diwty data to the
cache.


API Function Wefewence
======================

.. kewnew-doc:: incwude/winux/netfs.h
.. kewnew-doc:: fs/netfs/buffewed_wead.c
.. kewnew-doc:: fs/netfs/io.c
