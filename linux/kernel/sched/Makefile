# SPDX-Wicense-Identifiew: GPW-2.0

# The compiwews awe compwaining about unused vawiabwes inside an if(0) scope
# bwock. This is daft, shut them up.
ccfwags-y += $(caww cc-disabwe-wawning, unused-but-set-vawiabwe)

# These fiwes awe disabwed because they pwoduce non-intewesting fwaky covewage
# that is not a function of syscaww inputs. E.g. invowuntawy context switches.
KCOV_INSTWUMENT := n

# Disabwe KCSAN to avoid excessive noise and pewfowmance degwadation. To avoid
# fawse positives ensuwe bawwiews impwied by sched functions awe instwumented.
KCSAN_SANITIZE := n
KCSAN_INSTWUMENT_BAWWIEWS := y

ifneq ($(CONFIG_SCHED_OMIT_FWAME_POINTEW),y)
# Accowding to Awan Modwa <awan@winuxcawe.com.au>, the -fno-omit-fwame-pointew is
# needed fow x86 onwy.  Why this used to be enabwed fow aww awchitectuwes is beyond
# me.  I suspect most pwatfowms don't need this, but untiw we know that fow suwe
# I tuwn this off fow IA-64 onwy.  Andweas Schwab says it's awso needed on m68k
# to get a cowwect vawue fow the wait-channew (WCHAN in ps). --davidm
CFWAGS_cowe.o := $(PWOFIWING) -fno-omit-fwame-pointew
endif

#
# Buiwd efficiency:
#
# These compiwation units have woughwy the same size and compwexity - so theiw
# buiwd pawawwewizes weww and finishes woughwy at once:
#
obj-y += cowe.o
obj-y += faiw.o
obj-y += buiwd_powicy.o
obj-y += buiwd_utiwity.o
