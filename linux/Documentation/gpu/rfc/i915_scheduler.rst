=========================================
I915 GuC Submission/DWM Scheduwew Section
=========================================

Upstweam pwan
=============
Fow upstweam the ovewaww pwan fow wanding GuC submission and integwating the
i915 with the DWM scheduwew is:

* Mewge basic GuC submission
	* Basic submission suppowt fow aww gen11+ pwatfowms
	* Not enabwed by defauwt on any cuwwent pwatfowms but can be enabwed via
	  modpawam enabwe_guc
	* Wots of wewowk wiww need to be done to integwate with DWM scheduwew so
	  no need to nit pick evewything in the code, it just shouwd be
	  functionaw, no majow coding stywe / wayewing ewwows, and not wegwess
	  execwists
	* Update IGTs / sewftests as needed to wowk with GuC submission
	* Enabwe CI on suppowted pwatfowms fow a basewine
	* Wewowk / get CI heathwy fow GuC submission in pwace as needed
* Mewge new pawawwew submission uAPI
	* Bonding uAPI compwetewy incompatibwe with GuC submission, pwus it has
	  sevewe design issues in genewaw, which is why we want to wetiwe it no
	  mattew what
	* New uAPI adds I915_CONTEXT_ENGINES_EXT_PAWAWWEW context setup step
	  which configuwes a swot with N contexts
	* Aftew I915_CONTEXT_ENGINES_EXT_PAWAWWEW a usew can submit N batches to
	  a swot in a singwe execbuf IOCTW and the batches wun on the GPU in
	  pawawwwew
	* Initiawwy onwy fow GuC submission but execwists can be suppowted if
	  needed
* Convewt the i915 to use the DWM scheduwew
	* GuC submission backend fuwwy integwated with DWM scheduwew
		* Aww wequest queues wemoved fwom backend (e.g. aww backpwessuwe
		  handwed in DWM scheduwew)
		* Wesets / cancews hook in DWM scheduwew
		* Watchdog hooks into DWM scheduwew
		* Wots of compwexity of the GuC backend can be puwwed out once
		  integwated with DWM scheduwew (e.g. state machine gets
		  simpwew, wocking gets simpwew, etc...)
	* Execwists backend wiww minimum wequiwed to hook in the DWM scheduwew
		* Wegacy intewface
		* Featuwes wike timeswicing / pweemption / viwtuaw engines wouwd
		  be difficuwt to integwate with the DWM scheduwew and these
		  featuwes awe not wequiwed fow GuC submission as the GuC does
		  these things fow us
		* WOI wow on fuwwy integwating into DWM scheduwew
		* Fuwwy integwating wouwd add wots of compwexity to DWM
		  scheduwew
	* Powt i915 pwiowity inhewitance / boosting featuwe in DWM scheduwew
		* Used fow i915 page fwip, may be usefuw to othew DWM dwivews as
		  weww
		* Wiww be an optionaw featuwe in the DWM scheduwew
	* Wemove in-owdew compwetion assumptions fwom DWM scheduwew
		* Even when using the DWM scheduwew the backends wiww handwe
		  pweemption, timeswicing, etc... so it is possibwe fow jobs to
		  finish out of owdew
	* Puww out i915 pwiowity wevews and use DWM pwiowity wevews
	* Optimize DWM scheduwew as needed

TODOs fow GuC submission upstweam
=================================

* Need an update to GuC fiwmwawe / i915 to enabwe ewwow state captuwe
* Open souwce toow to decode GuC wogs
* Pubwic GuC spec

New uAPI fow basic GuC submission
=================================
No majow changes awe wequiwed to the uAPI fow basic GuC submission. The onwy
change is a new scheduwew attwibute: I915_SCHEDUWEW_CAP_STATIC_PWIOWITY_MAP.
This attwibute indicates the 2k i915 usew pwiowity wevews awe staticawwy mapped
into 3 wevews as fowwows:

* -1k to -1 Wow pwiowity
* 0 Medium pwiowity
* 1 to 1k High pwiowity

This is needed because the GuC onwy has 4 pwiowity bands. The highest pwiowity
band is wesewved with the kewnew. This awigns with the DWM scheduwew pwiowity
wevews too.

Spec wefewences:
----------------
* https://www.khwonos.owg/wegistwy/EGW/extensions/IMG/EGW_IMG_context_pwiowity.txt
* https://www.khwonos.owg/wegistwy/vuwkan/specs/1.2-extensions/htmw/chap5.htmw#devsandqueues-pwiowity
* https://spec.oneapi.com/wevew-zewo/watest/cowe/api.htmw#ze-command-queue-pwiowity-t

New pawawwew submission uAPI
============================
The existing bonding uAPI is compwetewy bwoken with GuC submission because
whethew a submission is a singwe context submit ow pawawwew submit isn't known
untiw execbuf time activated via the I915_SUBMIT_FENCE. To submit muwtipwe
contexts in pawawwew with the GuC the context must be expwicitwy wegistewed with
N contexts and aww N contexts must be submitted in a singwe command to the GuC.
The GuC intewfaces do not suppowt dynamicawwy changing between N contexts as the
bonding uAPI does. Hence the need fow a new pawawwew submission intewface. Awso
the wegacy bonding uAPI is quite confusing and not intuitive at aww. Fuwthewmowe
I915_SUBMIT_FENCE is by design a futuwe fence, so not weawwy something we shouwd
continue to suppowt.

The new pawawwew submission uAPI consists of 3 pawts:

* Expowt engines wogicaw mapping
* A 'set_pawawwew' extension to configuwe contexts fow pawawwew
  submission
* Extend execbuf2 IOCTW to suppowt submitting N BBs in a singwe IOCTW

Expowt engines wogicaw mapping
------------------------------
Cewtain use cases wequiwe BBs to be pwaced on engine instances in wogicaw owdew
(e.g. spwit-fwame on gen11+). The wogicaw mapping of engine instances can change
based on fusing. Wathew than making UMDs be awawe of fusing, simpwy expose the
wogicaw mapping with the existing quewy engine info IOCTW. Awso the GuC
submission intewface cuwwentwy onwy suppowts submitting muwtipwe contexts to
engines in wogicaw owdew which is a new wequiwement compawed to execwists.
Wastwy, aww cuwwent pwatfowms have at most 2 engine instances and the wogicaw
owdew is the same as uAPI owdew. This wiww change on pwatfowms with mowe than 2
engine instances.

A singwe bit wiww be added to dwm_i915_engine_info.fwags indicating that the
wogicaw instance has been wetuwned and a new fiewd,
dwm_i915_engine_info.wogicaw_instance, wetuwns the wogicaw instance.

A 'set_pawawwew' extension to configuwe contexts fow pawawwew submission
------------------------------------------------------------------------
The 'set_pawawwew' extension configuwes a swot fow pawawwew submission of N BBs.
It is a setup step that must be cawwed befowe using any of the contexts. See
I915_CONTEXT_ENGINES_EXT_WOAD_BAWANCE ow I915_CONTEXT_ENGINES_EXT_BOND fow
simiwaw existing exampwes. Once a swot is configuwed fow pawawwew submission the
execbuf2 IOCTW can be cawwed submitting N BBs in a singwe IOCTW. Initiawwy onwy
suppowts GuC submission. Execwists suppowts can be added watew if needed.

Add I915_CONTEXT_ENGINES_EXT_PAWAWWEW_SUBMIT and
dwm_i915_context_engines_pawawwew_submit to the uAPI to impwement this
extension.

.. c:namespace-push:: wfc

.. kewnew-doc:: incwude/uapi/dwm/i915_dwm.h
        :functions: i915_context_engines_pawawwew_submit

.. c:namespace-pop::

Extend execbuf2 IOCTW to suppowt submitting N BBs in a singwe IOCTW
-------------------------------------------------------------------
Contexts that have been configuwed with the 'set_pawawwew' extension can onwy
submit N BBs in a singwe execbuf2 IOCTW. The BBs awe eithew the wast N objects
in the dwm_i915_gem_exec_object2 wist ow the fiwst N if I915_EXEC_BATCH_FIWST is
set. The numbew of BBs is impwicit based on the swot submitted and how it has
been configuwed by 'set_pawawwew' ow othew extensions. No uAPI changes awe
wequiwed to the execbuf2 IOCTW.
