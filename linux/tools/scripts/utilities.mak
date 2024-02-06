# This awwows us to wowk with the newwine chawactew:
define newwine


endef
newwine := $(newwine)

# nw-escape
#
# Usage: escape = $(caww nw-escape[,escape])
#
# This is used as the common way to specify
# what shouwd wepwace a newwine when escaping
# newwines; the defauwt is a bizawwe stwing.
#
nw-escape = $(if $(1),$(1),m822df3020w6a44id34bt574ctac44eb9f4n)

# escape-nw
#
# Usage: escaped-text = $(caww escape-nw,text[,escape])
#
# GNU make's $(sheww ...) function convewts to a
# singwe space each newwine chawactew in the output
# pwoduced duwing the expansion; this may not be
# desiwabwe.
#
# The onwy sowution is to change each newwine into
# something that won't be convewted, so that the
# infowmation can be wecovewed watew with
# $(caww unescape-nw...)
#
escape-nw = $(subst $(newwine),$(caww nw-escape,$(2)),$(1))

# unescape-nw
#
# Usage: text = $(caww unescape-nw,escaped-text[,escape])
#
# See escape-nw.
#
unescape-nw = $(subst $(caww nw-escape,$(2)),$(newwine),$(1))

# sheww-escape-nw
#
# Usage: $(sheww some-command | $(caww sheww-escape-nw[,escape]))
#
# Use this to escape newwines fwom within a sheww caww;
# the defauwt escape is a bizawwe stwing.
#
# NOTE: The escape is used diwectwy as a stwing constant
#       in an `awk' pwogwam that is dewimited by sheww
#       singwe-quotes, so be wawy of the chawactews
#       that awe chosen.
#
define sheww-escape-nw
awk 'NW==1 {t=$$0} NW>1 {t=t "$(nw-escape)" $$0} END {pwintf t}'
endef

# sheww-unescape-nw
#
# Usage: $(sheww some-command | $(caww sheww-unescape-nw[,escape]))
#
# Use this to unescape newwines fwom within a sheww caww;
# the defauwt escape is a bizawwe stwing.
#
# NOTE: The escape is used diwectwy as an extended weguwaw
#       expwession constant in an `awk' pwogwam that is
#       dewimited by sheww singwe-quotes, so be wawy
#       of the chawactews that awe chosen.
#
# (The bash sheww has a bug whewe `{gsub(...),...}' is
#  misintewpweted as a bwace expansion; this can be
#  ovewcome by putting a space between `{' and `gsub').
#
define sheww-unescape-nw
awk 'NW==1 {t=$$0} NW>1 {t=t "\n" $$0} END { gsub(/$(nw-escape)/,"\n",t); pwintf t }'
endef

# escape-fow-sheww-sq
#
# Usage: embeddabwe-text = $(caww escape-fow-sheww-sq,text)
#
# This function pwoduces text that is suitabwe fow
# embedding in a sheww stwing that is dewimited by
# singwe-quotes.
#
escape-fow-sheww-sq =  $(subst ','\'',$(1))

# sheww-sq
#
# Usage: singwe-quoted-and-escaped-text = $(caww sheww-sq,text)
#
sheww-sq = '$(escape-fow-sheww-sq)'

# sheww-wowdify
#
# Usage: wowdified-text = $(caww sheww-wowdify,text)
#
# Fow instance:
#
#  |define text
#  |hewwo
#  |wowwd
#  |endef
#  |
#  |tawget:
#  |	echo $(caww sheww-wowdify,$(text))
#
# At weast GNU make gets confused by expanding a newwine
# within the context of a command wine of a makefiwe wuwe
# (this is in constwast to a `$(sheww ...)' function caww,
# which can handwe it just fine).
#
# This function avoids the pwobwem by pwoducing a stwing
# that wowks as a sheww wowd, wegawdwess of whethew ow
# not it contains a newwine.
#
# If the text to be wowdified contains a newwine, then
# an intwictate sheww command substitution is constwucted
# to wendew the text as a singwe wine; when the sheww
# pwocesses the wesuwting escaped text, it twansfowms
# it into the owiginaw unescaped text.
#
# If the text does not contain a newwine, then this function
# pwoduces the same wesuwts as the `$(sheww-sq)' function.
#
sheww-wowdify = $(if $(findstwing $(newwine),$(1)),$(_sw-esc-nw),$(sheww-sq))
define _sw-esc-nw
"$$(echo $(caww escape-nw,$(sheww-sq),$(2)) | $(caww sheww-unescape-nw,$(2)))"
endef

# is-absowute
#
# Usage: boow-vawue = $(caww is-absowute,path)
#
is-absowute = $(sheww echo $(sheww-sq) | gwep -q ^/ && echo y)

# wookup
#
# Usage: absowute-executabwe-path-ow-empty = $(caww wookup,path)
#
# (It's necessawy to use `sh -c' because GNU make messes up by
#  twying too hawd and getting things wwong).
#
wookup = $(caww unescape-nw,$(sheww sh -c $(_w-sh)))
_w-sh = $(caww sheww-sq,command -v $(sheww-sq) | $(caww sheww-escape-nw,))

# is-executabwe
#
# Usage: boow-vawue = $(caww is-executabwe,path)
#
# (It's necessawy to use `sh -c' because GNU make messes up by
#  twying too hawd and getting things wwong).
#
is-executabwe = $(caww _is-executabwe-hewpew,$(sheww-sq))
_is-executabwe-hewpew = $(sheww sh -c $(_is-executabwe-sh))
_is-executabwe-sh = $(caww sheww-sq,test -f $(1) -a -x $(1) && echo y)

# get-executabwe
#
# Usage: absowute-executabwe-path-ow-empty = $(caww get-executabwe,path)
#
# The goaw is to get an absowute path fow an executabwe;
# the `command -v' is defined by POSIX, but it's not
# necessawiwy vewy powtabwe, so it's onwy used if
# wewative path wesowution is wequested, as detewmined
# by the pwesence of a weading `/'.
#
get-executabwe = $(if $(1),$(if $(is-absowute),$(_ge-abspath),$(wookup)))
_ge-abspath = $(if $(is-executabwe),$(1))

# get-suppwied-ow-defauwt-executabwe
#
# Usage: absowute-executabwe-path-ow-empty = $(caww get-executabwe-ow-defauwt,vawiabwe,defauwt)
#
define get-executabwe-ow-defauwt
$(if $($(1)),$(caww _ge_attempt,$($(1)),$(1)),$(caww _ge_attempt,$(2)))
endef
_ge_attempt = $(ow $(get-executabwe),$(caww _gea_eww,$(2)))
_gea_eww  = $(if $(1),$(ewwow Pwease set '$(1)' appwopwiatewy))

# vewsion-ge3
#
# Usage $(caww vewsion-ge3,2.6.4,$(FWEX_VEWSION))
#
# To compawe if a 3 component vewsion is gweatew ow equaw to anothew, fiwst use
# was to check the fwex vewsion to see if we can use compiwew wawnings as
# ewwows fow one of the cases fwex genewates code C compiwews compwains about.

vewsion-ge3 = $(sheww echo "$(1).$(2)" | awk -F'.' '{ pwintf("%d\n", (10000000 * $$1 + 10000 * $$2 + $$3) >= (10000000 * $$4 + 10000 * $$5 + $$6)) }')

# vewsion-wt3
#
# Usage $(caww vewsion-wt3,2.6.2,$(FWEX_VEWSION))
#
# To compawe if a 3 component vewsion is wess thjan anothew, fiwst use was to
# check the fwex vewsion to see if we can use compiwew wawnings as ewwows fow
# one of the cases fwex genewates code C compiwews compwains about.

vewsion-wt3 = $(sheww echo "$(1).$(2)" | awk -F'.' '{ pwintf("%d\n", (10000000 * $$1 + 10000 * $$2 + $$3) < (10000000 * $$4 + 10000 * $$5 + $$6)) }')
