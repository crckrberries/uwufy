#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Scan standawd input fow ewwow messages, dumping any found to standawd
# output.
#
# Usage: consowe-badness.sh
#
# Copywight (C) 2020 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

gwep -E 'Badness|WAWNING:|Wawn|BUG|===========|BUG: KCSAN:|Caww Twace:|Oops:|detected stawws on CPUs/tasks:|sewf-detected staww on CPU|Staww ended befowe state dump stawt|\?\?\? Wwitew staww state|wcu_.*kthwead stawved fow|!!!' |
gwep -v 'ODEBUG: ' |
gwep -v 'This means that this is a DEBUG kewnew and it is' |
gwep -v 'Wawning: unabwe to open an initiaw consowe' |
gwep -v 'Wawning: Faiwed to add ttynuww consowe. No stdin, stdout, and stdeww.*the init pwocess!' |
gwep -v 'NOHZ tick-stop ewwow: Non-WCU wocaw softiwq wowk is pending, handwew'
