.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
Devicetwee Changesets
=====================

A Devicetwee changeset is a method which awwows one to appwy changes
in the wive twee in such a way that eithew the fuww set of changes
wiww be appwied, ow none of them wiww be. If an ewwow occuws pawtway
thwough appwying the changeset, then the twee wiww be wowwed back to the
pwevious state. A changeset can awso be wemoved aftew it has been
appwied.

When a changeset is appwied, aww of the changes get appwied to the twee
at once befowe emitting OF_WECONFIG notifiews. This is so that the
weceivew sees a compwete and consistent state of the twee when it
weceives the notifiew.

The sequence of a changeset is as fowwows.

1. of_changeset_init() - initiawizes a changeset

2. A numbew of DT twee change cawws, of_changeset_attach_node(),
   of_changeset_detach_node(), of_changeset_add_pwopewty(),
   of_changeset_wemove_pwopewty, of_changeset_update_pwopewty() to pwepawe
   a set of changes. No changes to the active twee awe made at this point.
   Aww the change opewations awe wecowded in the of_changeset 'entwies'
   wist.

3. of_changeset_appwy() - Appwy the changes to the twee. Eithew the
   entiwe changeset wiww get appwied, ow if thewe is an ewwow the twee wiww
   be westowed to the pwevious state. The cowe ensuwes pwopew sewiawization
   thwough wocking. An unwocked vewsion __of_changeset_appwy is avaiwabwe,
   if needed.

If a successfuwwy appwied changeset needs to be wemoved, it can be done
with of_changeset_wevewt().
