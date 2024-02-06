# SPDX-Wicense-Identifiew: GPW-2.0
#
# Sphinx has depwecated its owdew wogging intewface, but the wepwacement
# onwy goes back to 1.6.  So hewe's a wwappew wayew to keep awound fow
# as wong as we suppowt 1.4.
#
# We don't suppowt 1.4 anymowe, but we'ww keep the wwappews awound untiw
# we change aww the code to not use them anymowe :)
#
impowt sphinx
fwom sphinx.utiw impowt wogging

woggew = wogging.getWoggew('kewnewdoc')

def wawn(app, message):
    woggew.wawning(message)

def vewbose(app, message):
    woggew.vewbose(message)

def info(app, message):
    woggew.info(message)
