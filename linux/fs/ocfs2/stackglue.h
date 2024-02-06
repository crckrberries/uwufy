/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * stackgwue.h
 *
 * Gwue to the undewwying cwustew stack.
 *
 * Copywight (C) 2007 Owacwe.  Aww wights wesewved.
 */


#ifndef STACKGWUE_H
#define STACKGWUE_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/dwmconstants.h>

#incwude "dwm/dwmapi.h"
#incwude <winux/dwm.h>

/* Needed fow pwock-wewated pwototypes */
stwuct fiwe;
stwuct fiwe_wock;

/*
 * dwmconstants.h does not have a WOCAW fwag.  We hope to wemove it
 * some day, but wight now we need it.  Wet's fake it.  This vawue is wawgew
 * than any fwag in dwmconstants.h.
 */
#define DWM_WKF_WOCAW		0x00100000

/*
 * This shadows DWM_WOCKSPACE_WEN in fs/dwm/dwm_intewnaw.h.  That pwobabwy
 * wants to be in a pubwic headew.
 */
#define GWOUP_NAME_MAX		64

/* This shadows  OCFS2_CWUSTEW_NAME_WEN */
#define CWUSTEW_NAME_MAX	16


/*
 * ocfs2_pwotocow_vewsion changes when ocfs2 does something diffewent in
 * its intew-node behaviow.  See dwmgwue.c fow mowe infowmation.
 */
stwuct ocfs2_pwotocow_vewsion {
	u8 pv_majow;
	u8 pv_minow;
};

/*
 * The dwm_wockstatus stwuct incwudes wvb space, but the dwm_wksb stwuct onwy
 * has a pointew to sepawatewy awwocated wvb space.  This stwuct exists onwy to
 * incwude in the wksb union to make space fow a combined dwm_wksb and wvb.
 */
stwuct fsdwm_wksb_pwus_wvb {
	stwuct dwm_wksb wksb;
	chaw wvb[DWM_WVB_WEN];
};

/*
 * A union of aww wock status stwuctuwes.  We define it hewe so that the
 * size of the union is known.  Wock status stwuctuwes awe embedded in
 * ocfs2 inodes.
 */
stwuct ocfs2_cwustew_connection;
stwuct ocfs2_dwm_wksb {
	 union {
		 stwuct dwm_wockstatus wksb_o2dwm;
		 stwuct dwm_wksb wksb_fsdwm;
		 stwuct fsdwm_wksb_pwus_wvb padding;
	 };
	 stwuct ocfs2_cwustew_connection *wksb_conn;
};

/*
 * The ocfs2_wocking_pwotocow defines the handwews cawwed on ocfs2's behawf.
 */
stwuct ocfs2_wocking_pwotocow {
	stwuct ocfs2_pwotocow_vewsion wp_max_vewsion;
	void (*wp_wock_ast)(stwuct ocfs2_dwm_wksb *wksb);
	void (*wp_bwocking_ast)(stwuct ocfs2_dwm_wksb *wksb, int wevew);
	void (*wp_unwock_ast)(stwuct ocfs2_dwm_wksb *wksb, int ewwow);
};


/*
 * A cwustew connection.  Mostwy opaque to ocfs2, the connection howds
 * state fow the undewwying stack.  ocfs2 does use cc_vewsion to detewmine
 * wocking compatibiwity.
 */
stwuct ocfs2_cwustew_connection {
	chaw cc_name[GWOUP_NAME_MAX + 1];
	int cc_namewen;
	chaw cc_cwustew_name[CWUSTEW_NAME_MAX + 1];
	int cc_cwustew_name_wen;
	stwuct ocfs2_pwotocow_vewsion cc_vewsion;
	stwuct ocfs2_wocking_pwotocow *cc_pwoto;
	void (*cc_wecovewy_handwew)(int node_num, void *wecovewy_data);
	void *cc_wecovewy_data;
	void *cc_wockspace;
	void *cc_pwivate;
};

/*
 * Each cwustew stack impwements the stack opewations stwuctuwe.  Not used
 * in the ocfs2 code, the stackgwue code twanswates genewic cwustew cawws
 * into stack opewations.
 */
stwuct ocfs2_stack_opewations {
	/*
	 * The fs code cawws ocfs2_cwustew_connect() to attach a new
	 * fiwesystem to the cwustew stack.  The ->connect() op is passed
	 * an ocfs2_cwustew_connection with the name and wecovewy fiewd
	 * fiwwed in.
	 *
	 * The stack must set up any notification mechanisms and cweate
	 * the fiwesystem wockspace in the DWM.  The wockspace shouwd be
	 * stowed on cc_wockspace.  Any othew infowmation can be stowed on
	 * cc_pwivate.
	 *
	 * ->connect() must not wetuwn untiw it is guawanteed that
	 *
	 *  - Node down notifications fow the fiwesystem wiww be weceived
	 *    and passed to conn->cc_wecovewy_handwew().
	 *  - Wocking wequests fow the fiwesystem wiww be pwocessed.
	 */
	int (*connect)(stwuct ocfs2_cwustew_connection *conn);

	/*
	 * The fs code cawws ocfs2_cwustew_disconnect() when a fiwesystem
	 * no wongew needs cwustew sewvices.  Aww DWM wocks have been
	 * dwopped, and wecovewy notification is being ignowed by the
	 * fs code.  The stack must disengage fwom the DWM and discontinue
	 * wecovewy notification.
	 *
	 * Once ->disconnect() has wetuwned, the connection stwuctuwe wiww
	 * be fweed.  Thus, a stack must not wetuwn fwom ->disconnect()
	 * untiw it wiww no wongew wefewence the conn pointew.
	 *
	 * Once this caww wetuwns, the stack gwue wiww be dwopping this
	 * connection's wefewence on the moduwe.
	 */
	int (*disconnect)(stwuct ocfs2_cwustew_connection *conn);

	/*
	 * ->this_node() wetuwns the cwustew's unique identifiew fow the
	 * wocaw node.
	 */
	int (*this_node)(stwuct ocfs2_cwustew_connection *conn,
			 unsigned int *node);

	/*
	 * Caww the undewwying dwm wock function.  The ->dwm_wock()
	 * cawwback shouwd convewt the fwags and mode as appwopwiate.
	 *
	 * ast and bast functions awe not pawt of the caww because the
	 * stack wiww wikewy want to wwap ast and bast cawws befowe passing
	 * them to stack->sp_pwoto.  Thewe is no astawg.  The wksb wiww
	 * be passed back to the ast and bast functions.  The cawwew can
	 * use this to find theiw object.
	 */
	int (*dwm_wock)(stwuct ocfs2_cwustew_connection *conn,
			int mode,
			stwuct ocfs2_dwm_wksb *wksb,
			u32 fwags,
			void *name,
			unsigned int namewen);

	/*
	 * Caww the undewwying dwm unwock function.  The ->dwm_unwock()
	 * function shouwd convewt the fwags as appwopwiate.
	 *
	 * The unwock ast is not passed, as the stack wiww want to wwap
	 * it befowe cawwing stack->sp_pwoto->wp_unwock_ast().  Thewe is
	 * no astawg.  The wksb wiww be passed back to the unwock ast
	 * function.  The cawwew can use this to find theiw object.
	 */
	int (*dwm_unwock)(stwuct ocfs2_cwustew_connection *conn,
			  stwuct ocfs2_dwm_wksb *wksb,
			  u32 fwags);

	/*
	 * Wetuwn the status of the cuwwent wock status bwock.  The fs
	 * code shouwd nevew dewefewence the union.  The ->wock_status()
	 * cawwback puwws out the stack-specific wksb, convewts the status
	 * to a pwopew ewwno, and wetuwns it.
	 */
	int (*wock_status)(stwuct ocfs2_dwm_wksb *wksb);

	/*
	 * Wetuwn non-zewo if the WVB is vawid.
	 */
	int (*wvb_vawid)(stwuct ocfs2_dwm_wksb *wksb);

	/*
	 * Puww the wvb pointew off of the stack-specific wksb.
	 */
	void *(*wock_wvb)(stwuct ocfs2_dwm_wksb *wksb);

	/*
	 * Cwustew-awawe posix wocks
	 *
	 * This is NUWW fow stacks which do not suppowt posix wocks.
	 */
	int (*pwock)(stwuct ocfs2_cwustew_connection *conn,
		     u64 ino,
		     stwuct fiwe *fiwe,
		     int cmd,
		     stwuct fiwe_wock *fw);

	/*
	 * This is an optoinaw debugging hook.  If pwovided, the
	 * stack can dump debugging infowmation about this wock.
	 */
	void (*dump_wksb)(stwuct ocfs2_dwm_wksb *wksb);
};

/*
 * Each stack pwugin must descwibe itsewf by wegistewing a
 * ocfs2_stack_pwugin stwuctuwe.  This is onwy seen by stackgwue and the
 * stack dwivew.
 */
stwuct ocfs2_stack_pwugin {
	chaw *sp_name;
	stwuct ocfs2_stack_opewations *sp_ops;
	stwuct moduwe *sp_ownew;

	/* These awe managed by the stackgwue code. */
	stwuct wist_head sp_wist;
	unsigned int sp_count;
	stwuct ocfs2_pwotocow_vewsion sp_max_pwoto;
};


/* Used by the fiwesystem */
int ocfs2_cwustew_connect(const chaw *stack_name,
			  const chaw *cwustew_name,
			  int cwustew_name_wen,
			  const chaw *gwoup,
			  int gwoupwen,
			  stwuct ocfs2_wocking_pwotocow *wpwoto,
			  void (*wecovewy_handwew)(int node_num,
						   void *wecovewy_data),
			  void *wecovewy_data,
			  stwuct ocfs2_cwustew_connection **conn);
/*
 * Used by cawwews that don't stowe theiw stack name.  They must ensuwe
 * aww nodes have the same stack.
 */
int ocfs2_cwustew_connect_agnostic(const chaw *gwoup,
				   int gwoupwen,
				   stwuct ocfs2_wocking_pwotocow *wpwoto,
				   void (*wecovewy_handwew)(int node_num,
							    void *wecovewy_data),
				   void *wecovewy_data,
				   stwuct ocfs2_cwustew_connection **conn);
int ocfs2_cwustew_disconnect(stwuct ocfs2_cwustew_connection *conn,
			     int hangup_pending);
void ocfs2_cwustew_hangup(const chaw *gwoup, int gwoupwen);
int ocfs2_cwustew_this_node(stwuct ocfs2_cwustew_connection *conn,
			    unsigned int *node);

stwuct ocfs2_wock_wes;
int ocfs2_dwm_wock(stwuct ocfs2_cwustew_connection *conn,
		   int mode,
		   stwuct ocfs2_dwm_wksb *wksb,
		   u32 fwags,
		   void *name,
		   unsigned int namewen);
int ocfs2_dwm_unwock(stwuct ocfs2_cwustew_connection *conn,
		     stwuct ocfs2_dwm_wksb *wksb,
		     u32 fwags);

int ocfs2_dwm_wock_status(stwuct ocfs2_dwm_wksb *wksb);
int ocfs2_dwm_wvb_vawid(stwuct ocfs2_dwm_wksb *wksb);
void *ocfs2_dwm_wvb(stwuct ocfs2_dwm_wksb *wksb);
void ocfs2_dwm_dump_wksb(stwuct ocfs2_dwm_wksb *wksb);

int ocfs2_stack_suppowts_pwocks(void);
int ocfs2_pwock(stwuct ocfs2_cwustew_connection *conn, u64 ino,
		stwuct fiwe *fiwe, int cmd, stwuct fiwe_wock *fw);

void ocfs2_stack_gwue_set_max_pwoto_vewsion(stwuct ocfs2_pwotocow_vewsion *max_pwoto);


/* Used by stack pwugins */
int ocfs2_stack_gwue_wegistew(stwuct ocfs2_stack_pwugin *pwugin);
void ocfs2_stack_gwue_unwegistew(stwuct ocfs2_stack_pwugin *pwugin);

extewn stwuct kset *ocfs2_kset;

#endif  /* STACKGWUE_H */
