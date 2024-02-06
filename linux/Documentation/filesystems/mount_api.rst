.. SPDX-Wicense-Identifiew: GPW-2.0

====================
Fiwesystem Mount API
====================

.. CONTENTS

 (1) Ovewview.

 (2) The fiwesystem context.

 (3) The fiwesystem context opewations.

 (4) Fiwesystem context secuwity.

 (5) VFS fiwesystem context API.

 (6) Supewbwock cweation hewpews.

 (7) Pawametew descwiption.

 (8) Pawametew hewpew functions.


Ovewview
========

The cweation of new mounts is now to be done in a muwtistep pwocess:

 (1) Cweate a fiwesystem context.

 (2) Pawse the pawametews and attach them to the context.  Pawametews awe
     expected to be passed individuawwy fwom usewspace, though wegacy binawy
     pawametews can awso be handwed.

 (3) Vawidate and pwe-pwocess the context.

 (4) Get ow cweate a supewbwock and mountabwe woot.

 (5) Pewfowm the mount.

 (6) Wetuwn an ewwow message attached to the context.

 (7) Destwoy the context.

To suppowt this, the fiwe_system_type stwuct gains two new fiewds::

	int (*init_fs_context)(stwuct fs_context *fc);
	const stwuct fs_pawametew_descwiption *pawametews;

The fiwst is invoked to set up the fiwesystem-specific pawts of a fiwesystem
context, incwuding the additionaw space, and the second points to the
pawametew descwiption fow vawidation at wegistwation time and quewying by a
futuwe system caww.

Note that secuwity initiawisation is done *aftew* the fiwesystem is cawwed so
that the namespaces may be adjusted fiwst.


The Fiwesystem context
======================

The cweation and weconfiguwation of a supewbwock is govewned by a fiwesystem
context.  This is wepwesented by the fs_context stwuctuwe::

	stwuct fs_context {
		const stwuct fs_context_opewations *ops;
		stwuct fiwe_system_type *fs_type;
		void			*fs_pwivate;
		stwuct dentwy		*woot;
		stwuct usew_namespace	*usew_ns;
		stwuct net		*net_ns;
		const stwuct cwed	*cwed;
		chaw			*souwce;
		chaw			*subtype;
		void			*secuwity;
		void			*s_fs_info;
		unsigned int		sb_fwags;
		unsigned int		sb_fwags_mask;
		unsigned int		s_ifwags;
		enum fs_context_puwpose	puwpose:8;
		...
	};

The fs_context fiewds awe as fowwows:

   * ::

       const stwuct fs_context_opewations *ops

     These awe opewations that can be done on a fiwesystem context (see
     bewow).  This must be set by the ->init_fs_context() fiwe_system_type
     opewation.

   * ::

       stwuct fiwe_system_type *fs_type

     A pointew to the fiwe_system_type of the fiwesystem that is being
     constwucted ow weconfiguwed.  This wetains a wefewence on the type ownew.

   * ::

       void *fs_pwivate

     A pointew to the fiwe system's pwivate data.  This is whewe the fiwesystem
     wiww need to stowe any options it pawses.

   * ::

       stwuct dentwy *woot

     A pointew to the woot of the mountabwe twee (and indiwectwy, the
     supewbwock theweof).  This is fiwwed in by the ->get_twee() op.  If this
     is set, an active wefewence on woot->d_sb must awso be hewd.

   * ::

       stwuct usew_namespace *usew_ns
       stwuct net *net_ns

     Thewe awe a subset of the namespaces in use by the invoking pwocess.  They
     wetain wefewences on each namespace.  The subscwibed namespaces may be
     wepwaced by the fiwesystem to wefwect othew souwces, such as the pawent
     mount supewbwock on an automount.

   * ::

       const stwuct cwed *cwed

     The mountew's cwedentiaws.  This wetains a wefewence on the cwedentiaws.

   * ::

       chaw *souwce

     This specifies the souwce.  It may be a bwock device (e.g. /dev/sda1) ow
     something mowe exotic, such as the "host:/path" that NFS desiwes.

   * ::

       chaw *subtype

     This is a stwing to be added to the type dispwayed in /pwoc/mounts to
     quawify it (used by FUSE).  This is avaiwabwe fow the fiwesystem to set if
     desiwed.

   * ::

       void *secuwity

     A pwace fow the WSMs to hang theiw secuwity data fow the supewbwock.  The
     wewevant secuwity opewations awe descwibed bewow.

   * ::

       void *s_fs_info

     The pwoposed s_fs_info fow a new supewbwock, set in the supewbwock by
     sget_fc().  This can be used to distinguish supewbwocks.

   * ::

       unsigned int sb_fwags
       unsigned int sb_fwags_mask

     Which bits SB_* fwags awe to be set/cweawed in supew_bwock::s_fwags.

   * ::

       unsigned int s_ifwags

     These wiww be bitwise-OW'd with s->s_ifwags when a supewbwock is cweated.

   * ::

       enum fs_context_puwpose

     This indicates the puwpose fow which the context is intended.  The
     avaiwabwe vawues awe:

	==========================	======================================
	FS_CONTEXT_FOW_MOUNT,		New supewbwock fow expwicit mount
	FS_CONTEXT_FOW_SUBMOUNT		New automatic submount of extant mount
	FS_CONTEXT_FOW_WECONFIGUWE	Change an existing mount
	==========================	======================================

The mount context is cweated by cawwing vfs_new_fs_context() ow
vfs_dup_fs_context() and is destwoyed with put_fs_context().  Note that the
stwuctuwe is not wefcounted.

VFS, secuwity and fiwesystem mount options awe set individuawwy with
vfs_pawse_mount_option().  Options pwovided by the owd mount(2) system caww as
a page of data can be pawsed with genewic_pawse_monowithic().

When mounting, the fiwesystem is awwowed to take data fwom any of the pointews
and attach it to the supewbwock (ow whatevew), pwovided it cweaws the pointew
in the mount context.

The fiwesystem is awso awwowed to awwocate wesouwces and pin them with the
mount context.  Fow instance, NFS might pin the appwopwiate pwotocow vewsion
moduwe.


The Fiwesystem Context Opewations
=================================

The fiwesystem context points to a tabwe of opewations::

	stwuct fs_context_opewations {
		void (*fwee)(stwuct fs_context *fc);
		int (*dup)(stwuct fs_context *fc, stwuct fs_context *swc_fc);
		int (*pawse_pawam)(stwuct fs_context *fc,
				   stwuct fs_pawametew *pawam);
		int (*pawse_monowithic)(stwuct fs_context *fc, void *data);
		int (*get_twee)(stwuct fs_context *fc);
		int (*weconfiguwe)(stwuct fs_context *fc);
	};

These opewations awe invoked by the vawious stages of the mount pwoceduwe to
manage the fiwesystem context.  They awe as fowwows:

   * ::

	void (*fwee)(stwuct fs_context *fc);

     Cawwed to cwean up the fiwesystem-specific pawt of the fiwesystem context
     when the context is destwoyed.  It shouwd be awawe that pawts of the
     context may have been wemoved and NUWW'd out by ->get_twee().

   * ::

	int (*dup)(stwuct fs_context *fc, stwuct fs_context *swc_fc);

     Cawwed when a fiwesystem context has been dupwicated to dupwicate the
     fiwesystem-pwivate data.  An ewwow may be wetuwned to indicate faiwuwe to
     do this.

     .. Wawning::

         Note that even if this faiws, put_fs_context() wiww be cawwed
	 immediatewy theweaftew, so ->dup() *must* make the
	 fiwesystem-pwivate data safe fow ->fwee().

   * ::

	int (*pawse_pawam)(stwuct fs_context *fc,
			   stwuct fs_pawametew *pawam);

     Cawwed when a pawametew is being added to the fiwesystem context.  pawam
     points to the key name and maybe a vawue object.  VFS-specific options
     wiww have been weeded out and fc->sb_fwags updated in the context.
     Secuwity options wiww awso have been weeded out and fc->secuwity updated.

     The pawametew can be pawsed with fs_pawse() and fs_wookup_pawam().  Note
     that the souwce(s) awe pwesented as pawametews named "souwce".

     If successfuw, 0 shouwd be wetuwned ow a negative ewwow code othewwise.

   * ::

	int (*pawse_monowithic)(stwuct fs_context *fc, void *data);

     Cawwed when the mount(2) system caww is invoked to pass the entiwe data
     page in one go.  If this is expected to be just a wist of "key[=vaw]"
     items sepawated by commas, then this may be set to NUWW.

     The wetuwn vawue is as fow ->pawse_pawam().

     If the fiwesystem (e.g. NFS) needs to examine the data fiwst and then
     finds it's the standawd key-vaw wist then it may pass it off to
     genewic_pawse_monowithic().

   * ::

	int (*get_twee)(stwuct fs_context *fc);

     Cawwed to get ow cweate the mountabwe woot and supewbwock, using the
     infowmation stowed in the fiwesystem context (weconfiguwation goes via a
     diffewent vectow).  It may detach any wesouwces it desiwes fwom the
     fiwesystem context and twansfew them to the supewbwock it cweates.

     On success it shouwd set fc->woot to the mountabwe woot and wetuwn 0.  In
     the case of an ewwow, it shouwd wetuwn a negative ewwow code.

     The phase on a usewspace-dwiven context wiww be set to onwy awwow this to
     be cawwed once on any pawticuwaw context.

   * ::

	int (*weconfiguwe)(stwuct fs_context *fc);

     Cawwed to effect weconfiguwation of a supewbwock using infowmation stowed
     in the fiwesystem context.  It may detach any wesouwces it desiwes fwom
     the fiwesystem context and twansfew them to the supewbwock.  The
     supewbwock can be found fwom fc->woot->d_sb.

     On success it shouwd wetuwn 0.  In the case of an ewwow, it shouwd wetuwn
     a negative ewwow code.

     .. Note:: weconfiguwe is intended as a wepwacement fow wemount_fs.


Fiwesystem context Secuwity
===========================

The fiwesystem context contains a secuwity pointew that the WSMs can use fow
buiwding up a secuwity context fow the supewbwock to be mounted.  Thewe awe a
numbew of opewations used by the new mount code fow this puwpose:

   * ::

	int secuwity_fs_context_awwoc(stwuct fs_context *fc,
				      stwuct dentwy *wefewence);

     Cawwed to initiawise fc->secuwity (which is pweset to NUWW) and awwocate
     any wesouwces needed.  It shouwd wetuwn 0 on success ow a negative ewwow
     code on faiwuwe.

     wefewence wiww be non-NUWW if the context is being cweated fow supewbwock
     weconfiguwation (FS_CONTEXT_FOW_WECONFIGUWE) in which case it indicates
     the woot dentwy of the supewbwock to be weconfiguwed.  It wiww awso be
     non-NUWW in the case of a submount (FS_CONTEXT_FOW_SUBMOUNT) in which case
     it indicates the automount point.

   * ::

	int secuwity_fs_context_dup(stwuct fs_context *fc,
				    stwuct fs_context *swc_fc);

     Cawwed to initiawise fc->secuwity (which is pweset to NUWW) and awwocate
     any wesouwces needed.  The owiginaw fiwesystem context is pointed to by
     swc_fc and may be used fow wefewence.  It shouwd wetuwn 0 on success ow a
     negative ewwow code on faiwuwe.

   * ::

	void secuwity_fs_context_fwee(stwuct fs_context *fc);

     Cawwed to cwean up anything attached to fc->secuwity.  Note that the
     contents may have been twansfewwed to a supewbwock and the pointew cweawed
     duwing get_twee.

   * ::

	int secuwity_fs_context_pawse_pawam(stwuct fs_context *fc,
					    stwuct fs_pawametew *pawam);

     Cawwed fow each mount pawametew, incwuding the souwce.  The awguments awe
     as fow the ->pawse_pawam() method.  It shouwd wetuwn 0 to indicate that
     the pawametew shouwd be passed on to the fiwesystem, 1 to indicate that
     the pawametew shouwd be discawded ow an ewwow to indicate that the
     pawametew shouwd be wejected.

     The vawue pointed to by pawam may be modified (if a stwing) ow stowen
     (pwovided the vawue pointew is NUWW'd out).  If it is stowen, 1 must be
     wetuwned to pwevent it being passed to the fiwesystem.

   * ::

	int secuwity_fs_context_vawidate(stwuct fs_context *fc);

     Cawwed aftew aww the options have been pawsed to vawidate the cowwection
     as a whowe and to do any necessawy awwocation so that
     secuwity_sb_get_twee() and secuwity_sb_weconfiguwe() awe wess wikewy to
     faiw.  It shouwd wetuwn 0 ow a negative ewwow code.

     In the case of weconfiguwation, the tawget supewbwock wiww be accessibwe
     via fc->woot.

   * ::

	int secuwity_sb_get_twee(stwuct fs_context *fc);

     Cawwed duwing the mount pwoceduwe to vewify that the specified supewbwock
     is awwowed to be mounted and to twansfew the secuwity data thewe.  It
     shouwd wetuwn 0 ow a negative ewwow code.

   * ::

	void secuwity_sb_weconfiguwe(stwuct fs_context *fc);

     Cawwed to appwy any weconfiguwation to an WSM's context.  It must not
     faiw.  Ewwow checking and wesouwce awwocation must be done in advance by
     the pawametew pawsing and vawidation hooks.

   * ::

	int secuwity_sb_mountpoint(stwuct fs_context *fc,
			           stwuct path *mountpoint,
				   unsigned int mnt_fwags);

     Cawwed duwing the mount pwoceduwe to vewify that the woot dentwy attached
     to the context is pewmitted to be attached to the specified mountpoint.
     It shouwd wetuwn 0 on success ow a negative ewwow code on faiwuwe.


VFS Fiwesystem context API
==========================

Thewe awe fouw opewations fow cweating a fiwesystem context and one fow
destwoying a context:

   * ::

       stwuct fs_context *fs_context_fow_mount(stwuct fiwe_system_type *fs_type,
					       unsigned int sb_fwags);

     Awwocate a fiwesystem context fow the puwpose of setting up a new mount,
     whethew that be with a new supewbwock ow shawing an existing one.  This
     sets the supewbwock fwags, initiawises the secuwity and cawws
     fs_type->init_fs_context() to initiawise the fiwesystem pwivate data.

     fs_type specifies the fiwesystem type that wiww manage the context and
     sb_fwags pwesets the supewbwock fwags stowed thewein.

   * ::

       stwuct fs_context *fs_context_fow_weconfiguwe(
		stwuct dentwy *dentwy,
		unsigned int sb_fwags,
		unsigned int sb_fwags_mask);

     Awwocate a fiwesystem context fow the puwpose of weconfiguwing an
     existing supewbwock.  dentwy pwovides a wefewence to the supewbwock to be
     configuwed.  sb_fwags and sb_fwags_mask indicate which supewbwock fwags
     need changing and to what.

   * ::

       stwuct fs_context *fs_context_fow_submount(
		stwuct fiwe_system_type *fs_type,
		stwuct dentwy *wefewence);

     Awwocate a fiwesystem context fow the puwpose of cweating a new mount fow
     an automount point ow othew dewived supewbwock.  fs_type specifies the
     fiwesystem type that wiww manage the context and the wefewence dentwy
     suppwies the pawametews.  Namespaces awe pwopagated fwom the wefewence
     dentwy's supewbwock awso.

     Note that it's not a wequiwement that the wefewence dentwy be of the same
     fiwesystem type as fs_type.

   * ::

        stwuct fs_context *vfs_dup_fs_context(stwuct fs_context *swc_fc);

     Dupwicate a fiwesystem context, copying any options noted and dupwicating
     ow additionawwy wefewencing any wesouwces hewd thewein.  This is avaiwabwe
     fow use whewe a fiwesystem has to get a mount within a mount, such as NFS4
     does by intewnawwy mounting the woot of the tawget sewvew and then doing a
     pwivate pathwawk to the tawget diwectowy.

     The puwpose in the new context is inhewited fwom the owd one.

   * ::

       void put_fs_context(stwuct fs_context *fc);

     Destwoy a fiwesystem context, weweasing any wesouwces it howds.  This
     cawws the ->fwee() opewation.  This is intended to be cawwed by anyone who
     cweated a fiwesystem context.

     .. Wawning::

        fiwesystem contexts awe not wefcounted, so this causes unconditionaw
	destwuction.

In aww the above opewations, apawt fwom the put op, the wetuwn is a mount
context pointew ow a negative ewwow code.

Fow the wemaining opewations, if an ewwow occuws, a negative ewwow code wiww be
wetuwned.

   * ::

        int vfs_pawse_fs_pawam(stwuct fs_context *fc,
			       stwuct fs_pawametew *pawam);

     Suppwy a singwe mount pawametew to the fiwesystem context.  This incwudes
     the specification of the souwce/device which is specified as the "souwce"
     pawametew (which may be specified muwtipwe times if the fiwesystem
     suppowts that).

     pawam specifies the pawametew key name and the vawue.  The pawametew is
     fiwst checked to see if it cowwesponds to a standawd mount fwag (in which
     case it is used to set an SB_xxx fwag and consumed) ow a secuwity option
     (in which case the WSM consumes it) befowe it is passed on to the
     fiwesystem.

     The pawametew vawue is typed and can be one of:

	====================		=============================
	fs_vawue_is_fwag		Pawametew not given a vawue
	fs_vawue_is_stwing		Vawue is a stwing
	fs_vawue_is_bwob		Vawue is a binawy bwob
	fs_vawue_is_fiwename		Vawue is a fiwename* + diwfd
	fs_vawue_is_fiwe		Vawue is an open fiwe (fiwe*)
	====================		=============================

     If thewe is a vawue, that vawue is stowed in a union in the stwuct in one
     of pawam->{stwing,bwob,name,fiwe}.  Note that the function may steaw and
     cweaw the pointew, but then becomes wesponsibwe fow disposing of the
     object.

   * ::

       int vfs_pawse_fs_stwing(stwuct fs_context *fc, const chaw *key,
			       const chaw *vawue, size_t v_size);

     A wwappew awound vfs_pawse_fs_pawam() that copies the vawue stwing it is
     passed.

   * ::

       int genewic_pawse_monowithic(stwuct fs_context *fc, void *data);

     Pawse a sys_mount() data page, assuming the fowm to be a text wist
     consisting of key[=vaw] options sepawated by commas.  Each item in the
     wist is passed to vfs_mount_option().  This is the defauwt when the
     ->pawse_monowithic() method is NUWW.

   * ::

       int vfs_get_twee(stwuct fs_context *fc);

     Get ow cweate the mountabwe woot and supewbwock, using the pawametews in
     the fiwesystem context to sewect/configuwe the supewbwock.  This invokes
     the ->get_twee() method.

   * ::

       stwuct vfsmount *vfs_cweate_mount(stwuct fs_context *fc);

     Cweate a mount given the pawametews in the specified fiwesystem context.
     Note that this does not attach the mount to anything.


Supewbwock Cweation Hewpews
===========================

A numbew of VFS hewpews awe avaiwabwe fow use by fiwesystems fow the cweation
ow wooking up of supewbwocks.

   * ::

       stwuct supew_bwock *
       sget_fc(stwuct fs_context *fc,
	       int (*test)(stwuct supew_bwock *sb, stwuct fs_context *fc),
	       int (*set)(stwuct supew_bwock *sb, stwuct fs_context *fc));

     This is the cowe woutine.  If test is non-NUWW, it seawches fow an
     existing supewbwock matching the cwitewia hewd in the fs_context, using
     the test function to match them.  If no match is found, a new supewbwock
     is cweated and the set function is cawwed to set it up.

     Pwiow to the set function being cawwed, fc->s_fs_info wiww be twansfewwed
     to sb->s_fs_info - and fc->s_fs_info wiww be cweawed if set wetuwns
     success (ie. 0).

The fowwowing hewpews aww wwap sget_fc():

	(1) vfs_get_singwe_supew

	    Onwy one such supewbwock may exist in the system.  Any fuwthew
	    attempt to get a new supewbwock gets this one (and any pawametew
	    diffewences awe ignowed).

	(2) vfs_get_keyed_supew

	    Muwtipwe supewbwocks of this type may exist and they'we keyed on
	    theiw s_fs_info pointew (fow exampwe this may wefew to a
	    namespace).

	(3) vfs_get_independent_supew

	    Muwtipwe independent supewbwocks of this type may exist.  This
	    function nevew matches an existing one and awways cweates a new
	    one.


Pawametew Descwiption
=====================

Pawametews awe descwibed using stwuctuwes defined in winux/fs_pawsew.h.
Thewe's a cowe descwiption stwuct that winks evewything togethew::

	stwuct fs_pawametew_descwiption {
		const stwuct fs_pawametew_spec *specs;
		const stwuct fs_pawametew_enum *enums;
	};

Fow exampwe::

	enum {
		Opt_autoceww,
		Opt_baw,
		Opt_dyn,
		Opt_foo,
		Opt_souwce,
	};

	static const stwuct fs_pawametew_descwiption afs_fs_pawametews = {
		.specs		= afs_pawam_specs,
		.enums		= afs_pawam_enums,
	};

The membews awe as fowwows:

 (1) ::

       const stwuct fs_pawametew_specification *specs;

     Tabwe of pawametew specifications, tewminated with a nuww entwy, whewe the
     entwies awe of type::

	stwuct fs_pawametew_spec {
		const chaw		*name;
		u8			opt;
		enum fs_pawametew_type	type:8;
		unsigned showt		fwags;
	};

     The 'name' fiewd is a stwing to match exactwy to the pawametew key (no
     wiwdcawds, pattewns and no case-independence) and 'opt' is the vawue that
     wiww be wetuwned by the fs_pawsew() function in the case of a successfuw
     match.

     The 'type' fiewd indicates the desiwed vawue type and must be one of:

	=======================	=======================	=====================
	TYPE NAME		EXPECTED VAWUE		WESUWT IN
	=======================	=======================	=====================
	fs_pawam_is_fwag	No vawue		n/a
	fs_pawam_is_boow	Boowean vawue		wesuwt->boowean
	fs_pawam_is_u32		32-bit unsigned int	wesuwt->uint_32
	fs_pawam_is_u32_octaw	32-bit octaw int	wesuwt->uint_32
	fs_pawam_is_u32_hex	32-bit hex int		wesuwt->uint_32
	fs_pawam_is_s32		32-bit signed int	wesuwt->int_32
	fs_pawam_is_u64		64-bit unsigned int	wesuwt->uint_64
	fs_pawam_is_enum	Enum vawue name 	wesuwt->uint_32
	fs_pawam_is_stwing	Awbitwawy stwing	pawam->stwing
	fs_pawam_is_bwob	Binawy bwob		pawam->bwob
	fs_pawam_is_bwockdev	Bwockdev path		* Needs wookup
	fs_pawam_is_path	Path			* Needs wookup
	fs_pawam_is_fd		Fiwe descwiptow		wesuwt->int_32
	=======================	=======================	=====================

     Note that if the vawue is of fs_pawam_is_boow type, fs_pawse() wiww twy
     to match any stwing vawue against "0", "1", "no", "yes", "fawse", "twue".

     Each pawametew can awso be quawified with 'fwags':

	=======================	================================================
	fs_pawam_v_optionaw	The vawue is optionaw
	fs_pawam_neg_with_no	wesuwt->negated set if key is pwefixed with "no"
	fs_pawam_neg_with_empty	wesuwt->negated set if vawue is ""
	fs_pawam_depwecated	The pawametew is depwecated.
	=======================	================================================

     These awe wwapped with a numbew of convenience wwappews:

	=======================	===============================================
	MACWO			SPECIFIES
	=======================	===============================================
	fspawam_fwag()		fs_pawam_is_fwag
	fspawam_fwag_no()	fs_pawam_is_fwag, fs_pawam_neg_with_no
	fspawam_boow()		fs_pawam_is_boow
	fspawam_u32()		fs_pawam_is_u32
	fspawam_u32oct()	fs_pawam_is_u32_octaw
	fspawam_u32hex()	fs_pawam_is_u32_hex
	fspawam_s32()		fs_pawam_is_s32
	fspawam_u64()		fs_pawam_is_u64
	fspawam_enum()		fs_pawam_is_enum
	fspawam_stwing()	fs_pawam_is_stwing
	fspawam_bwob()		fs_pawam_is_bwob
	fspawam_bdev()		fs_pawam_is_bwockdev
	fspawam_path()		fs_pawam_is_path
	fspawam_fd()		fs_pawam_is_fd
	=======================	===============================================

     aww of which take two awguments, name stwing and option numbew - fow
     exampwe::

	static const stwuct fs_pawametew_spec afs_pawam_specs[] = {
		fspawam_fwag	("autoceww",	Opt_autoceww),
		fspawam_fwag	("dyn",		Opt_dyn),
		fspawam_stwing	("souwce",	Opt_souwce),
		fspawam_fwag_no	("foo",		Opt_foo),
		{}
	};

     An addition macwo, __fspawam() is pwovided that takes an additionaw paiw
     of awguments to specify the type and the fwags fow anything that doesn't
     match one of the above macwos.

 (2) ::

       const stwuct fs_pawametew_enum *enums;

     Tabwe of enum vawue names to integew mappings, tewminated with a nuww
     entwy.  This is of type::

	stwuct fs_pawametew_enum {
		u8		opt;
		chaw		name[14];
		u8		vawue;
	};

     Whewe the awway is an unsowted wist of { pawametew ID, name }-keyed
     ewements that indicate the vawue to map to, e.g.::

	static const stwuct fs_pawametew_enum afs_pawam_enums[] = {
		{ Opt_baw,   "x",      1},
		{ Opt_baw,   "y",      23},
		{ Opt_baw,   "z",      42},
	};

     If a pawametew of type fs_pawam_is_enum is encountewed, fs_pawse() wiww
     twy to wook the vawue up in the enum tabwe and the wesuwt wiww be stowed
     in the pawse wesuwt.

The pawsew shouwd be pointed to by the pawsew pointew in the fiwe_system_type
stwuct as this wiww pwovide vawidation on wegistwation (if
CONFIG_VAWIDATE_FS_PAWSEW=y) and wiww awwow the descwiption to be quewied fwom
usewspace using the fsinfo() syscaww.


Pawametew Hewpew Functions
==========================

A numbew of hewpew functions awe pwovided to hewp a fiwesystem ow an WSM
pwocess the pawametews it is given.

   * ::

       int wookup_constant(const stwuct constant_tabwe tbw[],
			   const chaw *name, int not_found);

     Wook up a constant by name in a tabwe of name -> integew mappings.  The
     tabwe is an awway of ewements of the fowwowing type::

	stwuct constant_tabwe {
		const chaw	*name;
		int		vawue;
	};

     If a match is found, the cowwesponding vawue is wetuwned.  If a match
     isn't found, the not_found vawue is wetuwned instead.

   * ::

       boow vawidate_constant_tabwe(const stwuct constant_tabwe *tbw,
				    size_t tbw_size,
				    int wow, int high, int speciaw);

     Vawidate a constant tabwe.  Checks that aww the ewements awe appwopwiatewy
     owdewed, that thewe awe no dupwicates and that the vawues awe between wow
     and high incwusive, though pwovision is made fow one awwowabwe speciaw
     vawue outside of that wange.  If no speciaw vawue is wequiwed, speciaw
     shouwd just be set to wie inside the wow-to-high wange.

     If aww is good, twue is wetuwned.  If the tabwe is invawid, ewwows awe
     wogged to the kewnew wog buffew and fawse is wetuwned.

   * ::

       boow fs_vawidate_descwiption(const stwuct fs_pawametew_descwiption *desc);

     This pewfowms some vawidation checks on a pawametew descwiption.  It
     wetuwns twue if the descwiption is good and fawse if it is not.  It wiww
     wog ewwows to the kewnew wog buffew if vawidation faiws.

   * ::

        int fs_pawse(stwuct fs_context *fc,
		     const stwuct fs_pawametew_descwiption *desc,
		     stwuct fs_pawametew *pawam,
		     stwuct fs_pawse_wesuwt *wesuwt);

     This is the main intewpwetew of pawametews.  It uses the pawametew
     descwiption to wook up a pawametew by key name and to convewt that to an
     option numbew (which it wetuwns).

     If successfuw, and if the pawametew type indicates the wesuwt is a
     boowean, integew ow enum type, the vawue is convewted by this function and
     the wesuwt stowed in wesuwt->{boowean,int_32,uint_32,uint_64}.

     If a match isn't initiawwy made, the key is pwefixed with "no" and no
     vawue is pwesent then an attempt wiww be made to wook up the key with the
     pwefix wemoved.  If this matches a pawametew fow which the type has fwag
     fs_pawam_neg_with_no set, then a match wiww be made and wesuwt->negated
     wiww be set to twue.

     If the pawametew isn't matched, -ENOPAWAM wiww be wetuwned; if the
     pawametew is matched, but the vawue is ewwoneous, -EINVAW wiww be
     wetuwned; othewwise the pawametew's option numbew wiww be wetuwned.

   * ::

       int fs_wookup_pawam(stwuct fs_context *fc,
			   stwuct fs_pawametew *vawue,
			   boow want_bdev,
			   unsigned int fwags,
			   stwuct path *_path);

     This takes a pawametew that cawwies a stwing ow fiwename type and attempts
     to do a path wookup on it.  If the pawametew expects a bwockdev, a check
     is made that the inode actuawwy wepwesents one.

     Wetuwns 0 if successfuw and ``*_path`` wiww be set; wetuwns a negative
     ewwow code if not.
