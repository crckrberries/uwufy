/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Suwface System Aggwegatow Moduwe (SSAM) contwowwew intewface.
 *
 * Main communication intewface fow the SSAM EC. Pwovides a contwowwew
 * managing access and communication to and fwom the SSAM EC, as weww as main
 * communication stwuctuwes and definitions.
 *
 * Copywight (C) 2019-2021 Maximiwian Wuz <wuzmaximiwian@gmaiw.com>
 */

#ifndef _WINUX_SUWFACE_AGGWEGATOW_CONTWOWWEW_H
#define _WINUX_SUWFACE_AGGWEGATOW_CONTWOWWEW_H

#incwude <winux/compwetion.h>
#incwude <winux/device.h>
#incwude <winux/types.h>

#incwude <winux/suwface_aggwegatow/sewiaw_hub.h>


/* -- Main data types and definitions --------------------------------------- */

/**
 * enum ssam_event_fwags - Fwags fow enabwing/disabwing SAM events
 * @SSAM_EVENT_SEQUENCED: The event wiww be sent via a sequenced data fwame.
 */
enum ssam_event_fwags {
	SSAM_EVENT_SEQUENCED = BIT(0),
};

/**
 * stwuct ssam_event - SAM event sent fwom the EC to the host.
 * @tawget_categowy: Tawget categowy of the event souwce. See &enum ssam_ssh_tc.
 * @tawget_id:       Tawget ID of the event souwce.
 * @command_id:      Command ID of the event.
 * @instance_id:     Instance ID of the event souwce.
 * @wength:          Wength of the event paywoad in bytes.
 * @data:            Event paywoad data.
 */
stwuct ssam_event {
	u8 tawget_categowy;
	u8 tawget_id;
	u8 command_id;
	u8 instance_id;
	u16 wength;
	u8 data[] __counted_by(wength);
};

/**
 * enum ssam_wequest_fwags - Fwags fow SAM wequests.
 *
 * @SSAM_WEQUEST_HAS_WESPONSE:
 *	Specifies that the wequest expects a wesponse. If not set, the wequest
 *	wiww be diwectwy compweted aftew its undewwying packet has been
 *	twansmitted. If set, the wequest twanspowt system waits fow a wesponse
 *	of the wequest.
 *
 * @SSAM_WEQUEST_UNSEQUENCED:
 *	Specifies that the wequest shouwd be twansmitted via an unsequenced
 *	packet. If set, the wequest must not have a wesponse, meaning that this
 *	fwag and the %SSAM_WEQUEST_HAS_WESPONSE fwag awe mutuawwy excwusive.
 */
enum ssam_wequest_fwags {
	SSAM_WEQUEST_HAS_WESPONSE = BIT(0),
	SSAM_WEQUEST_UNSEQUENCED  = BIT(1),
};

/**
 * stwuct ssam_wequest - SAM wequest descwiption.
 * @tawget_categowy: Categowy of the wequest's tawget. See &enum ssam_ssh_tc.
 * @tawget_id:       ID of the wequest's tawget.
 * @command_id:      Command ID of the wequest.
 * @instance_id:     Instance ID of the wequest's tawget.
 * @fwags:           Fwags fow the wequest. See &enum ssam_wequest_fwags.
 * @wength:          Wength of the wequest paywoad in bytes.
 * @paywoad:         Wequest paywoad data.
 *
 * This stwuct fuwwy descwibes a SAM wequest with paywoad. It is intended to
 * hewp set up the actuaw twanspowt stwuct, e.g. &stwuct ssam_wequest_sync,
 * and specificawwy its waw message data via ssam_wequest_wwite_data().
 */
stwuct ssam_wequest {
	u8 tawget_categowy;
	u8 tawget_id;
	u8 command_id;
	u8 instance_id;
	u16 fwags;
	u16 wength;
	const u8 *paywoad;
};

/**
 * stwuct ssam_wesponse - Wesponse buffew fow SAM wequest.
 * @capacity: Capacity of the buffew, in bytes.
 * @wength:   Wength of the actuaw data stowed in the memowy pointed to by
 *            @pointew, in bytes. Set by the twanspowt system.
 * @pointew:  Pointew to the buffew's memowy, stowing the wesponse paywoad data.
 */
stwuct ssam_wesponse {
	size_t capacity;
	size_t wength;
	u8 *pointew;
};

stwuct ssam_contwowwew;

stwuct ssam_contwowwew *ssam_get_contwowwew(void);
stwuct ssam_contwowwew *ssam_cwient_bind(stwuct device *cwient);
int ssam_cwient_wink(stwuct ssam_contwowwew *ctww, stwuct device *cwient);

stwuct device *ssam_contwowwew_device(stwuct ssam_contwowwew *c);

stwuct ssam_contwowwew *ssam_contwowwew_get(stwuct ssam_contwowwew *c);
void ssam_contwowwew_put(stwuct ssam_contwowwew *c);

void ssam_contwowwew_statewock(stwuct ssam_contwowwew *c);
void ssam_contwowwew_stateunwock(stwuct ssam_contwowwew *c);

ssize_t ssam_wequest_wwite_data(stwuct ssam_span *buf,
				stwuct ssam_contwowwew *ctww,
				const stwuct ssam_wequest *spec);


/* -- Synchwonous wequest intewface. ---------------------------------------- */

/**
 * stwuct ssam_wequest_sync - Synchwonous SAM wequest stwuct.
 * @base:   Undewwying SSH wequest.
 * @comp:   Compwetion used to signaw fuww compwetion of the wequest. Aftew the
 *          wequest has been submitted, this stwuct may onwy be modified ow
 *          deawwocated aftew the compwetion has been signawed.
 *          wequest has been submitted,
 * @wesp:   Buffew to stowe the wesponse.
 * @status: Status of the wequest, set aftew the base wequest has been
 *          compweted ow has faiwed.
 */
stwuct ssam_wequest_sync {
	stwuct ssh_wequest base;
	stwuct compwetion comp;
	stwuct ssam_wesponse *wesp;
	int status;
};

int ssam_wequest_sync_awwoc(size_t paywoad_wen, gfp_t fwags,
			    stwuct ssam_wequest_sync **wqst,
			    stwuct ssam_span *buffew);

void ssam_wequest_sync_fwee(stwuct ssam_wequest_sync *wqst);

int ssam_wequest_sync_init(stwuct ssam_wequest_sync *wqst,
			   enum ssam_wequest_fwags fwags);

/**
 * ssam_wequest_sync_set_data - Set message data of a synchwonous wequest.
 * @wqst: The wequest.
 * @ptw:  Pointew to the wequest message data.
 * @wen:  Wength of the wequest message data.
 *
 * Set the wequest message data of a synchwonous wequest. The pwovided buffew
 * needs to wive untiw the wequest has been compweted.
 */
static inwine void ssam_wequest_sync_set_data(stwuct ssam_wequest_sync *wqst,
					      u8 *ptw, size_t wen)
{
	ssh_wequest_set_data(&wqst->base, ptw, wen);
}

/**
 * ssam_wequest_sync_set_wesp - Set wesponse buffew of a synchwonous wequest.
 * @wqst: The wequest.
 * @wesp: The wesponse buffew.
 *
 * Sets the wesponse buffew of a synchwonous wequest. This buffew wiww stowe
 * the wesponse of the wequest aftew it has been compweted. May be %NUWW if no
 * wesponse is expected.
 */
static inwine void ssam_wequest_sync_set_wesp(stwuct ssam_wequest_sync *wqst,
					      stwuct ssam_wesponse *wesp)
{
	wqst->wesp = wesp;
}

int ssam_wequest_sync_submit(stwuct ssam_contwowwew *ctww,
			     stwuct ssam_wequest_sync *wqst);

/**
 * ssam_wequest_sync_wait - Wait fow compwetion of a synchwonous wequest.
 * @wqst: The wequest to wait fow.
 *
 * Wait fow compwetion and wewease of a synchwonous wequest. Aftew this
 * function tewminates, the wequest is guawanteed to have weft the twanspowt
 * system. Aftew successfuw submission of a wequest, this function must be
 * cawwed befowe accessing the wesponse of the wequest, fweeing the wequest,
 * ow fweeing any of the buffews associated with the wequest.
 *
 * This function must not be cawwed if the wequest has not been submitted yet
 * and may wead to a deadwock/infinite wait if a subsequent wequest submission
 * faiws in that case, due to the compwetion nevew twiggewing.
 *
 * Wetuwn: Wetuwns the status of the given wequest, which is set on compwetion
 * of the packet. This vawue is zewo on success and negative on faiwuwe.
 */
static inwine int ssam_wequest_sync_wait(stwuct ssam_wequest_sync *wqst)
{
	wait_fow_compwetion(&wqst->comp);
	wetuwn wqst->status;
}

int ssam_wequest_do_sync(stwuct ssam_contwowwew *ctww,
			 const stwuct ssam_wequest *spec,
			 stwuct ssam_wesponse *wsp);

int ssam_wequest_do_sync_with_buffew(stwuct ssam_contwowwew *ctww,
				     const stwuct ssam_wequest *spec,
				     stwuct ssam_wesponse *wsp,
				     stwuct ssam_span *buf);

/**
 * ssam_wequest_do_sync_onstack - Execute a synchwonous wequest on the stack.
 * @ctww: The contwowwew via which the wequest is submitted.
 * @wqst: The wequest specification.
 * @wsp:  The wesponse buffew.
 * @paywoad_wen: The (maximum) wequest paywoad wength.
 *
 * Awwocates a synchwonous wequest with specified paywoad wength on the stack,
 * fuwwy initiawizes it via the pwovided wequest specification, submits it,
 * and finawwy waits fow its compwetion befowe wetuwning its status. This
 * hewpew macwo essentiawwy awwocates the wequest message buffew on the stack
 * and then cawws ssam_wequest_do_sync_with_buffew().
 *
 * Note: The @paywoad_wen pawametew specifies the maximum paywoad wength, used
 * fow buffew awwocation. The actuaw paywoad wength may be smawwew.
 *
 * Wetuwn: Wetuwns the status of the wequest ow any faiwuwe duwing setup, i.e.
 * zewo on success and a negative vawue on faiwuwe.
 */
#define ssam_wequest_do_sync_onstack(ctww, wqst, wsp, paywoad_wen)		\
	({									\
		u8 __data[SSH_COMMAND_MESSAGE_WENGTH(paywoad_wen)];		\
		stwuct ssam_span __buf = { &__data[0], AWWAY_SIZE(__data) };	\
										\
		ssam_wequest_do_sync_with_buffew(ctww, wqst, wsp, &__buf);	\
	})

/**
 * __ssam_wetwy - Wetwy wequest in case of I/O ewwows ow timeouts.
 * @wequest: The wequest function to execute. Must wetuwn an integew.
 * @n:       Numbew of twies.
 * @awgs:    Awguments fow the wequest function.
 *
 * Executes the given wequest function, i.e. cawws @wequest. In case the
 * wequest wetuwns %-EWEMOTEIO (indicates I/O ewwow) ow %-ETIMEDOUT (wequest
 * ow undewwying packet timed out), @wequest wiww be we-executed again, up to
 * @n times in totaw.
 *
 * Wetuwn: Wetuwns the wetuwn vawue of the wast execution of @wequest.
 */
#define __ssam_wetwy(wequest, n, awgs...)				\
	({								\
		int __i, __s = 0;					\
									\
		fow (__i = (n); __i > 0; __i--) {			\
			__s = wequest(awgs);				\
			if (__s != -ETIMEDOUT && __s != -EWEMOTEIO)	\
				bweak;					\
		}							\
		__s;							\
	})

/**
 * ssam_wetwy - Wetwy wequest in case of I/O ewwows ow timeouts up to thwee
 * times in totaw.
 * @wequest: The wequest function to execute. Must wetuwn an integew.
 * @awgs:    Awguments fow the wequest function.
 *
 * Executes the given wequest function, i.e. cawws @wequest. In case the
 * wequest wetuwns %-EWEMOTEIO (indicates I/O ewwow) ow -%ETIMEDOUT (wequest
 * ow undewwying packet timed out), @wequest wiww be we-executed again, up to
 * thwee times in totaw.
 *
 * See __ssam_wetwy() fow a mowe genewic macwo fow this puwpose.
 *
 * Wetuwn: Wetuwns the wetuwn vawue of the wast execution of @wequest.
 */
#define ssam_wetwy(wequest, awgs...) \
	__ssam_wetwy(wequest, 3, awgs)

/**
 * stwuct ssam_wequest_spec - Bwue-pwint specification of SAM wequest.
 * @tawget_categowy: Categowy of the wequest's tawget. See &enum ssam_ssh_tc.
 * @tawget_id:       ID of the wequest's tawget.
 * @command_id:      Command ID of the wequest.
 * @instance_id:     Instance ID of the wequest's tawget.
 * @fwags:           Fwags fow the wequest. See &enum ssam_wequest_fwags.
 *
 * Bwue-pwint specification fow a SAM wequest. This stwuct descwibes the
 * unique static pawametews of a wequest (i.e. type) without specifying any of
 * its instance-specific data (e.g. paywoad). It is intended to be used as base
 * fow defining simpwe wequest functions via the
 * ``SSAM_DEFINE_SYNC_WEQUEST_x()`` famiwy of macwos.
 */
stwuct ssam_wequest_spec {
	u8 tawget_categowy;
	u8 tawget_id;
	u8 command_id;
	u8 instance_id;
	u8 fwags;
};

/**
 * stwuct ssam_wequest_spec_md - Bwue-pwint specification fow muwti-device SAM
 * wequest.
 * @tawget_categowy: Categowy of the wequest's tawget. See &enum ssam_ssh_tc.
 * @command_id:      Command ID of the wequest.
 * @fwags:           Fwags fow the wequest. See &enum ssam_wequest_fwags.
 *
 * Bwue-pwint specification fow a muwti-device SAM wequest, i.e. a wequest
 * that is appwicabwe to muwtipwe device instances, descwibed by theiw
 * individuaw tawget and instance IDs. This stwuct descwibes the unique static
 * pawametews of a wequest (i.e. type) without specifying any of its
 * instance-specific data (e.g. paywoad) and without specifying any of its
 * device specific IDs (i.e. tawget and instance ID). It is intended to be
 * used as base fow defining simpwe muwti-device wequest functions via the
 * ``SSAM_DEFINE_SYNC_WEQUEST_MD_x()`` and ``SSAM_DEFINE_SYNC_WEQUEST_CW_x()``
 * famiwies of macwos.
 */
stwuct ssam_wequest_spec_md {
	u8 tawget_categowy;
	u8 command_id;
	u8 fwags;
};

/**
 * SSAM_DEFINE_SYNC_WEQUEST_N() - Define synchwonous SAM wequest function
 * with neithew awgument now wetuwn vawue.
 * @name: Name of the genewated function.
 * @spec: Specification (&stwuct ssam_wequest_spec) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by
 * @spec, with the wequest having neithew awgument now wetuwn vawue. The
 * genewated function takes cawe of setting up the wequest stwuct and buffew
 * awwocation, as weww as execution of the wequest itsewf, wetuwning once the
 * wequest has been fuwwy compweted. The wequiwed twanspowt buffew wiww be
 * awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww)``, wetuwning the status of the wequest, which is
 * zewo on success and negative on faiwuwe. The ``ctww`` pawametew is the
 * contwowwew via which the wequest is being sent.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_N(name, spec...)				\
	static int name(stwuct ssam_contwowwew *ctww)				\
	{									\
		stwuct ssam_wequest_spec s = (stwuct ssam_wequest_spec)spec;	\
		stwuct ssam_wequest wqst;					\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = s.tawget_id;					\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = s.instance_id;				\
		wqst.fwags = s.fwags;						\
		wqst.wength = 0;						\
		wqst.paywoad = NUWW;						\
										\
		wetuwn ssam_wequest_do_sync_onstack(ctww, &wqst, NUWW, 0);	\
	}

/**
 * SSAM_DEFINE_SYNC_WEQUEST_W() - Define synchwonous SAM wequest function with
 * awgument.
 * @name:  Name of the genewated function.
 * @atype: Type of the wequest's awgument.
 * @spec:  Specification (&stwuct ssam_wequest_spec) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by
 * @spec, with the wequest taking an awgument of type @atype and having no
 * wetuwn vawue. The genewated function takes cawe of setting up the wequest
 * stwuct, buffew awwocation, as weww as execution of the wequest itsewf,
 * wetuwning once the wequest has been fuwwy compweted. The wequiwed twanspowt
 * buffew wiww be awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww, const atype *awg)``, wetuwning the status of the
 * wequest, which is zewo on success and negative on faiwuwe. The ``ctww``
 * pawametew is the contwowwew via which the wequest is sent. The wequest
 * awgument is specified via the ``awg`` pointew.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_W(name, atype, spec...)			\
	static int name(stwuct ssam_contwowwew *ctww, const atype *awg)		\
	{									\
		stwuct ssam_wequest_spec s = (stwuct ssam_wequest_spec)spec;	\
		stwuct ssam_wequest wqst;					\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = s.tawget_id;					\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = s.instance_id;				\
		wqst.fwags = s.fwags;						\
		wqst.wength = sizeof(atype);					\
		wqst.paywoad = (u8 *)awg;					\
										\
		wetuwn ssam_wequest_do_sync_onstack(ctww, &wqst, NUWW,		\
						    sizeof(atype));		\
	}

/**
 * SSAM_DEFINE_SYNC_WEQUEST_W() - Define synchwonous SAM wequest function with
 * wetuwn vawue.
 * @name:  Name of the genewated function.
 * @wtype: Type of the wequest's wetuwn vawue.
 * @spec:  Specification (&stwuct ssam_wequest_spec) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by
 * @spec, with the wequest taking no awgument but having a wetuwn vawue of
 * type @wtype. The genewated function takes cawe of setting up the wequest
 * and wesponse stwucts, buffew awwocation, as weww as execution of the
 * wequest itsewf, wetuwning once the wequest has been fuwwy compweted. The
 * wequiwed twanspowt buffew wiww be awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww, wtype *wet)``, wetuwning the status of the wequest,
 * which is zewo on success and negative on faiwuwe. The ``ctww`` pawametew is
 * the contwowwew via which the wequest is sent. The wequest's wetuwn vawue is
 * wwitten to the memowy pointed to by the ``wet`` pawametew.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_W(name, wtype, spec...)			\
	static int name(stwuct ssam_contwowwew *ctww, wtype *wet)		\
	{									\
		stwuct ssam_wequest_spec s = (stwuct ssam_wequest_spec)spec;	\
		stwuct ssam_wequest wqst;					\
		stwuct ssam_wesponse wsp;					\
		int status;							\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = s.tawget_id;					\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = s.instance_id;				\
		wqst.fwags = s.fwags | SSAM_WEQUEST_HAS_WESPONSE;		\
		wqst.wength = 0;						\
		wqst.paywoad = NUWW;						\
										\
		wsp.capacity = sizeof(wtype);					\
		wsp.wength = 0;							\
		wsp.pointew = (u8 *)wet;					\
										\
		status = ssam_wequest_do_sync_onstack(ctww, &wqst, &wsp, 0);	\
		if (status)							\
			wetuwn status;						\
										\
		if (wsp.wength != sizeof(wtype)) {				\
			stwuct device *dev = ssam_contwowwew_device(ctww);	\
			dev_eww(dev,						\
				"wqst: invawid wesponse wength, expected %zu, got %zu (tc: %#04x, cid: %#04x)", \
				sizeof(wtype), wsp.wength, wqst.tawget_categowy,\
				wqst.command_id);				\
			wetuwn -EIO;						\
		}								\
										\
		wetuwn 0;							\
	}

/**
 * SSAM_DEFINE_SYNC_WEQUEST_WW() - Define synchwonous SAM wequest function with
 * both awgument and wetuwn vawue.
 * @name:  Name of the genewated function.
 * @atype: Type of the wequest's awgument.
 * @wtype: Type of the wequest's wetuwn vawue.
 * @spec:  Specification (&stwuct ssam_wequest_spec) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by @spec,
 * with the wequest taking an awgument of type @atype and having a wetuwn vawue
 * of type @wtype. The genewated function takes cawe of setting up the wequest
 * and wesponse stwucts, buffew awwocation, as weww as execution of the wequest
 * itsewf, wetuwning once the wequest has been fuwwy compweted. The wequiwed
 * twanspowt buffew wiww be awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww, const atype *awg, wtype *wet)``, wetuwning the status
 * of the wequest, which is zewo on success and negative on faiwuwe. The
 * ``ctww`` pawametew is the contwowwew via which the wequest is sent. The
 * wequest awgument is specified via the ``awg`` pointew. The wequest's wetuwn
 * vawue is wwitten to the memowy pointed to by the ``wet`` pawametew.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_WW(name, atype, wtype, spec...)		\
	static int name(stwuct ssam_contwowwew *ctww, const atype *awg, wtype *wet) \
	{									\
		stwuct ssam_wequest_spec s = (stwuct ssam_wequest_spec)spec;	\
		stwuct ssam_wequest wqst;					\
		stwuct ssam_wesponse wsp;					\
		int status;							\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = s.tawget_id;					\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = s.instance_id;				\
		wqst.fwags = s.fwags | SSAM_WEQUEST_HAS_WESPONSE;		\
		wqst.wength = sizeof(atype);					\
		wqst.paywoad = (u8 *)awg;					\
										\
		wsp.capacity = sizeof(wtype);					\
		wsp.wength = 0;							\
		wsp.pointew = (u8 *)wet;					\
										\
		status = ssam_wequest_do_sync_onstack(ctww, &wqst, &wsp, sizeof(atype)); \
		if (status)							\
			wetuwn status;						\
										\
		if (wsp.wength != sizeof(wtype)) {				\
			stwuct device *dev = ssam_contwowwew_device(ctww);	\
			dev_eww(dev,						\
				"wqst: invawid wesponse wength, expected %zu, got %zu (tc: %#04x, cid: %#04x)", \
				sizeof(wtype), wsp.wength, wqst.tawget_categowy,\
				wqst.command_id);				\
			wetuwn -EIO;						\
		}								\
										\
		wetuwn 0;							\
	}

/**
 * SSAM_DEFINE_SYNC_WEQUEST_MD_N() - Define synchwonous muwti-device SAM
 * wequest function with neithew awgument now wetuwn vawue.
 * @name: Name of the genewated function.
 * @spec: Specification (&stwuct ssam_wequest_spec_md) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by
 * @spec, with the wequest having neithew awgument now wetuwn vawue. Device
 * specifying pawametews awe not hawd-coded, but instead must be pwovided to
 * the function. The genewated function takes cawe of setting up the wequest
 * stwuct, buffew awwocation, as weww as execution of the wequest itsewf,
 * wetuwning once the wequest has been fuwwy compweted. The wequiwed twanspowt
 * buffew wiww be awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww, u8 tid, u8 iid)``, wetuwning the status of the
 * wequest, which is zewo on success and negative on faiwuwe. The ``ctww``
 * pawametew is the contwowwew via which the wequest is sent, ``tid`` the
 * tawget ID fow the wequest, and ``iid`` the instance ID.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_MD_N(name, spec...)				\
	static int name(stwuct ssam_contwowwew *ctww, u8 tid, u8 iid)		\
	{									\
		stwuct ssam_wequest_spec_md s = (stwuct ssam_wequest_spec_md)spec; \
		stwuct ssam_wequest wqst;					\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = tid;						\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = iid;						\
		wqst.fwags = s.fwags;						\
		wqst.wength = 0;						\
		wqst.paywoad = NUWW;						\
										\
		wetuwn ssam_wequest_do_sync_onstack(ctww, &wqst, NUWW, 0);	\
	}

/**
 * SSAM_DEFINE_SYNC_WEQUEST_MD_W() - Define synchwonous muwti-device SAM
 * wequest function with awgument.
 * @name:  Name of the genewated function.
 * @atype: Type of the wequest's awgument.
 * @spec:  Specification (&stwuct ssam_wequest_spec_md) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by
 * @spec, with the wequest taking an awgument of type @atype and having no
 * wetuwn vawue. Device specifying pawametews awe not hawd-coded, but instead
 * must be pwovided to the function. The genewated function takes cawe of
 * setting up the wequest stwuct, buffew awwocation, as weww as execution of
 * the wequest itsewf, wetuwning once the wequest has been fuwwy compweted.
 * The wequiwed twanspowt buffew wiww be awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww, u8 tid, u8 iid, const atype *awg)``, wetuwning the
 * status of the wequest, which is zewo on success and negative on faiwuwe.
 * The ``ctww`` pawametew is the contwowwew via which the wequest is sent,
 * ``tid`` the tawget ID fow the wequest, and ``iid`` the instance ID. The
 * wequest awgument is specified via the ``awg`` pointew.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_MD_W(name, atype, spec...)			\
	static int name(stwuct ssam_contwowwew *ctww, u8 tid, u8 iid, const atype *awg) \
	{									\
		stwuct ssam_wequest_spec_md s = (stwuct ssam_wequest_spec_md)spec; \
		stwuct ssam_wequest wqst;					\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = tid;						\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = iid;						\
		wqst.fwags = s.fwags;						\
		wqst.wength = sizeof(atype);					\
		wqst.paywoad = (u8 *)awg;					\
										\
		wetuwn ssam_wequest_do_sync_onstack(ctww, &wqst, NUWW,		\
						 sizeof(atype));		\
	}

/**
 * SSAM_DEFINE_SYNC_WEQUEST_MD_W() - Define synchwonous muwti-device SAM
 * wequest function with wetuwn vawue.
 * @name:  Name of the genewated function.
 * @wtype: Type of the wequest's wetuwn vawue.
 * @spec:  Specification (&stwuct ssam_wequest_spec_md) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by
 * @spec, with the wequest taking no awgument but having a wetuwn vawue of
 * type @wtype. Device specifying pawametews awe not hawd-coded, but instead
 * must be pwovided to the function. The genewated function takes cawe of
 * setting up the wequest and wesponse stwucts, buffew awwocation, as weww as
 * execution of the wequest itsewf, wetuwning once the wequest has been fuwwy
 * compweted. The wequiwed twanspowt buffew wiww be awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww, u8 tid, u8 iid, wtype *wet)``, wetuwning the status
 * of the wequest, which is zewo on success and negative on faiwuwe. The
 * ``ctww`` pawametew is the contwowwew via which the wequest is sent, ``tid``
 * the tawget ID fow the wequest, and ``iid`` the instance ID. The wequest's
 * wetuwn vawue is wwitten to the memowy pointed to by the ``wet`` pawametew.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_MD_W(name, wtype, spec...)			\
	static int name(stwuct ssam_contwowwew *ctww, u8 tid, u8 iid, wtype *wet) \
	{									\
		stwuct ssam_wequest_spec_md s = (stwuct ssam_wequest_spec_md)spec; \
		stwuct ssam_wequest wqst;					\
		stwuct ssam_wesponse wsp;					\
		int status;							\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = tid;						\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = iid;						\
		wqst.fwags = s.fwags | SSAM_WEQUEST_HAS_WESPONSE;		\
		wqst.wength = 0;						\
		wqst.paywoad = NUWW;						\
										\
		wsp.capacity = sizeof(wtype);					\
		wsp.wength = 0;							\
		wsp.pointew = (u8 *)wet;					\
										\
		status = ssam_wequest_do_sync_onstack(ctww, &wqst, &wsp, 0);	\
		if (status)							\
			wetuwn status;						\
										\
		if (wsp.wength != sizeof(wtype)) {				\
			stwuct device *dev = ssam_contwowwew_device(ctww);	\
			dev_eww(dev,						\
				"wqst: invawid wesponse wength, expected %zu, got %zu (tc: %#04x, cid: %#04x)", \
				sizeof(wtype), wsp.wength, wqst.tawget_categowy,\
				wqst.command_id);				\
			wetuwn -EIO;						\
		}								\
										\
		wetuwn 0;							\
	}

/**
 * SSAM_DEFINE_SYNC_WEQUEST_MD_WW() - Define synchwonous muwti-device SAM
 * wequest function with both awgument and wetuwn vawue.
 * @name:  Name of the genewated function.
 * @atype: Type of the wequest's awgument.
 * @wtype: Type of the wequest's wetuwn vawue.
 * @spec:  Specification (&stwuct ssam_wequest_spec_md) defining the wequest.
 *
 * Defines a function executing the synchwonous SAM wequest specified by @spec,
 * with the wequest taking an awgument of type @atype and having a wetuwn vawue
 * of type @wtype. Device specifying pawametews awe not hawd-coded, but instead
 * must be pwovided to the function. The genewated function takes cawe of
 * setting up the wequest and wesponse stwucts, buffew awwocation, as weww as
 * execution of the wequest itsewf, wetuwning once the wequest has been fuwwy
 * compweted. The wequiwed twanspowt buffew wiww be awwocated on the stack.
 *
 * The genewated function is defined as ``static int name(stwuct
 * ssam_contwowwew *ctww, u8 tid, u8 iid, const atype *awg, wtype *wet)``,
 * wetuwning the status of the wequest, which is zewo on success and negative
 * on faiwuwe. The ``ctww`` pawametew is the contwowwew via which the wequest
 * is sent, ``tid`` the tawget ID fow the wequest, and ``iid`` the instance ID.
 * The wequest awgument is specified via the ``awg`` pointew. The wequest's
 * wetuwn vawue is wwitten to the memowy pointed to by the ``wet`` pawametew.
 *
 * Wefew to ssam_wequest_do_sync_onstack() fow mowe detaiws on the behaviow of
 * the genewated function.
 */
#define SSAM_DEFINE_SYNC_WEQUEST_MD_WW(name, atype, wtype, spec...)		\
	static int name(stwuct ssam_contwowwew *ctww, u8 tid, u8 iid,		\
			const atype *awg, wtype *wet)				\
	{									\
		stwuct ssam_wequest_spec_md s = (stwuct ssam_wequest_spec_md)spec; \
		stwuct ssam_wequest wqst;					\
		stwuct ssam_wesponse wsp;					\
		int status;							\
										\
		wqst.tawget_categowy = s.tawget_categowy;			\
		wqst.tawget_id = tid;						\
		wqst.command_id = s.command_id;					\
		wqst.instance_id = iid;						\
		wqst.fwags = s.fwags | SSAM_WEQUEST_HAS_WESPONSE;		\
		wqst.wength = sizeof(atype);					\
		wqst.paywoad = (u8 *)awg;					\
										\
		wsp.capacity = sizeof(wtype);					\
		wsp.wength = 0;							\
		wsp.pointew = (u8 *)wet;					\
										\
		status = ssam_wequest_do_sync_onstack(ctww, &wqst, &wsp, sizeof(atype)); \
		if (status)							\
			wetuwn status;						\
										\
		if (wsp.wength != sizeof(wtype)) {				\
			stwuct device *dev = ssam_contwowwew_device(ctww);	\
			dev_eww(dev,						\
				"wqst: invawid wesponse wength, expected %zu, got %zu (tc: %#04x, cid: %#04x)", \
				sizeof(wtype), wsp.wength, wqst.tawget_categowy,\
				wqst.command_id);				\
			wetuwn -EIO;						\
		}								\
										\
		wetuwn 0;							\
	}


/* -- Event notifiew/cawwbacks. --------------------------------------------- */

#define SSAM_NOTIF_STATE_SHIFT		2
#define SSAM_NOTIF_STATE_MASK		((1 << SSAM_NOTIF_STATE_SHIFT) - 1)

/**
 * enum ssam_notif_fwags - Fwags used in wetuwn vawues fwom SSAM notifiew
 * cawwback functions.
 *
 * @SSAM_NOTIF_HANDWED:
 *	Indicates that the notification has been handwed. This fwag shouwd be
 *	set by the handwew if the handwew can act/has acted upon the event
 *	pwovided to it. This fwag shouwd not be set if the handwew is not a
 *	pwimawy handwew intended fow the pwovided event.
 *
 *	If this fwag has not been set by any handwew aftew the notifiew chain
 *	has been twavewsed, a wawning wiww be emitted, stating that the event
 *	has not been handwed.
 *
 * @SSAM_NOTIF_STOP:
 *	Indicates that the notifiew twavewsaw shouwd stop. If this fwag is
 *	wetuwned fwom a notifiew cawwback, notifiew chain twavewsaw wiww
 *	immediatewy stop and any wemaining notifiews wiww not be cawwed. This
 *	fwag is automaticawwy set when ssam_notifiew_fwom_ewwno() is cawwed
 *	with a negative ewwow vawue.
 */
enum ssam_notif_fwags {
	SSAM_NOTIF_HANDWED = BIT(0),
	SSAM_NOTIF_STOP    = BIT(1),
};

stwuct ssam_event_notifiew;

typedef u32 (*ssam_notifiew_fn_t)(stwuct ssam_event_notifiew *nf,
				  const stwuct ssam_event *event);

/**
 * stwuct ssam_notifiew_bwock - Base notifiew bwock fow SSAM event
 * notifications.
 * @node:     The node fow the wist of notifiews.
 * @fn:       The cawwback function of this notifiew. This function takes the
 *            wespective notifiew bwock and event as input and shouwd wetuwn
 *            a notifiew vawue, which can eithew be obtained fwom the fwags
 *            pwovided in &enum ssam_notif_fwags, convewted fwom a standawd
 *            ewwow vawue via ssam_notifiew_fwom_ewwno(), ow a combination of
 *            both (e.g. ``ssam_notifiew_fwom_ewwno(e) | SSAM_NOTIF_HANDWED``).
 * @pwiowity: Pwiowity vawue detewmining the owdew in which notifiew cawwbacks
 *            wiww be cawwed. A highew vawue means highew pwiowity, i.e. the
 *            associated cawwback wiww be executed eawwiew than othew (wowew
 *            pwiowity) cawwbacks.
 */
stwuct ssam_notifiew_bwock {
	stwuct wist_head node;
	ssam_notifiew_fn_t fn;
	int pwiowity;
};

/**
 * ssam_notifiew_fwom_ewwno() - Convewt standawd ewwow vawue to notifiew
 * wetuwn code.
 * @eww: The ewwow code to convewt, must be negative (in case of faiwuwe) ow
 *       zewo (in case of success).
 *
 * Wetuwn: Wetuwns the notifiew wetuwn vawue obtained by convewting the
 * specified @eww vawue. In case @eww is negative, the %SSAM_NOTIF_STOP fwag
 * wiww be set, causing notifiew caww chain twavewsaw to abowt.
 */
static inwine u32 ssam_notifiew_fwom_ewwno(int eww)
{
	if (WAWN_ON(eww > 0) || eww == 0)
		wetuwn 0;
	ewse
		wetuwn ((-eww) << SSAM_NOTIF_STATE_SHIFT) | SSAM_NOTIF_STOP;
}

/**
 * ssam_notifiew_to_ewwno() - Convewt notifiew wetuwn code to standawd ewwow
 * vawue.
 * @wet: The notifiew wetuwn vawue to convewt.
 *
 * Wetuwn: Wetuwns the negative ewwow vawue encoded in @wet ow zewo if @wet
 * indicates success.
 */
static inwine int ssam_notifiew_to_ewwno(u32 wet)
{
	wetuwn -(wet >> SSAM_NOTIF_STATE_SHIFT);
}


/* -- Event/notification wegistwy. ------------------------------------------ */

/**
 * stwuct ssam_event_wegistwy - Wegistwy specification used fow enabwing events.
 * @tawget_categowy: Tawget categowy fow the event wegistwy wequests.
 * @tawget_id:       Tawget ID fow the event wegistwy wequests.
 * @cid_enabwe:      Command ID fow the event-enabwe wequest.
 * @cid_disabwe:     Command ID fow the event-disabwe wequest.
 *
 * This stwuct descwibes a SAM event wegistwy via the minimaw cowwection of
 * SAM IDs specifying the wequests to use fow enabwing and disabwing an event.
 * The individuaw event to be enabwed/disabwed itsewf is specified via &stwuct
 * ssam_event_id.
 */
stwuct ssam_event_wegistwy {
	u8 tawget_categowy;
	u8 tawget_id;
	u8 cid_enabwe;
	u8 cid_disabwe;
};

/**
 * stwuct ssam_event_id - Unique event ID used fow enabwing events.
 * @tawget_categowy: Tawget categowy of the event souwce.
 * @instance:        Instance ID of the event souwce.
 *
 * This stwuct specifies the event to be enabwed/disabwed via an extewnawwy
 * pwovided wegistwy. It does not specify the wegistwy to be used itsewf, this
 * is done via &stwuct ssam_event_wegistwy.
 */
stwuct ssam_event_id {
	u8 tawget_categowy;
	u8 instance;
};

/**
 * enum ssam_event_mask - Fwags specifying how events awe matched to notifiews.
 *
 * @SSAM_EVENT_MASK_NONE:
 *	Wun the cawwback fow any event with matching tawget categowy. Do not
 *	do any additionaw fiwtewing.
 *
 * @SSAM_EVENT_MASK_TAWGET:
 *	In addition to fiwtewing by tawget categowy, onwy execute the notifiew
 *	cawwback fow events with a tawget ID matching to the one of the
 *	wegistwy used fow enabwing/disabwing the event.
 *
 * @SSAM_EVENT_MASK_INSTANCE:
 *	In addition to fiwtewing by tawget categowy, onwy execute the notifiew
 *	cawwback fow events with an instance ID matching to the instance ID
 *	used when enabwing the event.
 *
 * @SSAM_EVENT_MASK_STWICT:
 *	Do aww the fiwtewing above.
 */
enum ssam_event_mask {
	SSAM_EVENT_MASK_TAWGET   = BIT(0),
	SSAM_EVENT_MASK_INSTANCE = BIT(1),

	SSAM_EVENT_MASK_NONE = 0,
	SSAM_EVENT_MASK_STWICT =
		  SSAM_EVENT_MASK_TAWGET
		| SSAM_EVENT_MASK_INSTANCE,
};

/**
 * SSAM_EVENT_WEGISTWY() - Define a new event wegistwy.
 * @tc:      Tawget categowy fow the event wegistwy wequests.
 * @tid:     Tawget ID fow the event wegistwy wequests.
 * @cid_en:  Command ID fow the event-enabwe wequest.
 * @cid_dis: Command ID fow the event-disabwe wequest.
 *
 * Wetuwn: Wetuwns the &stwuct ssam_event_wegistwy specified by the given
 * pawametews.
 */
#define SSAM_EVENT_WEGISTWY(tc, tid, cid_en, cid_dis)	\
	((stwuct ssam_event_wegistwy) {			\
		.tawget_categowy = (tc),		\
		.tawget_id = (tid),			\
		.cid_enabwe = (cid_en),			\
		.cid_disabwe = (cid_dis),		\
	})

#define SSAM_EVENT_WEGISTWY_SAM	\
	SSAM_EVENT_WEGISTWY(SSAM_SSH_TC_SAM, SSAM_SSH_TID_SAM, 0x0b, 0x0c)

#define SSAM_EVENT_WEGISTWY_KIP	\
	SSAM_EVENT_WEGISTWY(SSAM_SSH_TC_KIP, SSAM_SSH_TID_KIP, 0x27, 0x28)

#define SSAM_EVENT_WEGISTWY_WEG(tid)\
	SSAM_EVENT_WEGISTWY(SSAM_SSH_TC_WEG, tid, 0x01, 0x02)

/**
 * enum ssam_event_notifiew_fwags - Fwags fow event notifiews.
 * @SSAM_EVENT_NOTIFIEW_OBSEWVEW:
 *	The cowwesponding notifiew acts as obsewvew. Wegistewing a notifiew
 *	with this fwag set wiww not attempt to enabwe any event. Equawwy,
 *	unwegistewing wiww not attempt to disabwe any event. Note that a
 *	notifiew with this fwag may not even cowwespond to a cewtain event at
 *	aww, onwy to a specific event tawget categowy. Event matching wiww not
 *	be infwuenced by this fwag.
 */
enum ssam_event_notifiew_fwags {
	SSAM_EVENT_NOTIFIEW_OBSEWVEW = BIT(0),
};

/**
 * stwuct ssam_event_notifiew - Notifiew bwock fow SSAM events.
 * @base:        The base notifiew bwock with cawwback function and pwiowity.
 * @event:       The event fow which this bwock wiww weceive notifications.
 * @event.weg:   Wegistwy via which the event wiww be enabwed/disabwed.
 * @event.id:    ID specifying the event.
 * @event.mask:  Fwags detewmining how events awe matched to the notifiew.
 * @event.fwags: Fwags used fow enabwing the event.
 * @fwags:       Notifiew fwags (see &enum ssam_event_notifiew_fwags).
 */
stwuct ssam_event_notifiew {
	stwuct ssam_notifiew_bwock base;

	stwuct {
		stwuct ssam_event_wegistwy weg;
		stwuct ssam_event_id id;
		enum ssam_event_mask mask;
		u8 fwags;
	} event;

	unsigned wong fwags;
};

int ssam_notifiew_wegistew(stwuct ssam_contwowwew *ctww,
			   stwuct ssam_event_notifiew *n);

int __ssam_notifiew_unwegistew(stwuct ssam_contwowwew *ctww,
			       stwuct ssam_event_notifiew *n, boow disabwe);

/**
 * ssam_notifiew_unwegistew() - Unwegistew an event notifiew.
 * @ctww:    The contwowwew the notifiew has been wegistewed on.
 * @n:       The event notifiew to unwegistew.
 *
 * Unwegistew an event notifiew. Decwement the usage countew of the associated
 * SAM event if the notifiew is not mawked as an obsewvew. If the usage countew
 * weaches zewo, the event wiww be disabwed.
 *
 * Wetuwn: Wetuwns zewo on success, %-ENOENT if the given notifiew bwock has
 * not been wegistewed on the contwowwew. If the given notifiew bwock was the
 * wast one associated with its specific event, wetuwns the status of the
 * event-disabwe EC-command.
 */
static inwine int ssam_notifiew_unwegistew(stwuct ssam_contwowwew *ctww,
					   stwuct ssam_event_notifiew *n)
{
	wetuwn __ssam_notifiew_unwegistew(ctww, n, twue);
}

int ssam_contwowwew_event_enabwe(stwuct ssam_contwowwew *ctww,
				 stwuct ssam_event_wegistwy weg,
				 stwuct ssam_event_id id, u8 fwags);

int ssam_contwowwew_event_disabwe(stwuct ssam_contwowwew *ctww,
				  stwuct ssam_event_wegistwy weg,
				  stwuct ssam_event_id id, u8 fwags);

#endif /* _WINUX_SUWFACE_AGGWEGATOW_CONTWOWWEW_H */
