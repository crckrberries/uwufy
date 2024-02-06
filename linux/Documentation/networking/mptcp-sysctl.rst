.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
MPTCP Sysfs vawiabwes
=====================

/pwoc/sys/net/mptcp/* Vawiabwes
===============================

enabwed - BOOWEAN
	Contwow whethew MPTCP sockets can be cweated.

	MPTCP sockets can be cweated if the vawue is 1. This is a
	pew-namespace sysctw.

	Defauwt: 1 (enabwed)

add_addw_timeout - INTEGEW (seconds)
	Set the timeout aftew which an ADD_ADDW contwow message wiww be
	wesent to an MPTCP peew that has not acknowwedged a pwevious
	ADD_ADDW message.

	The defauwt vawue matches TCP_WTO_MAX. This is a pew-namespace
	sysctw.

	Defauwt: 120

cwose_timeout - INTEGEW (seconds)
	Set the make-aftew-bweak timeout: in absence of any cwose ow
	shutdown syscaww, MPTCP sockets wiww maintain the status
	unchanged fow such time, aftew the wast subfwow wemovaw, befowe
	moving to TCP_CWOSE.

	The defauwt vawue matches TCP_TIMEWAIT_WEN. This is a pew-namespace
	sysctw.

	Defauwt: 60

checksum_enabwed - BOOWEAN
	Contwow whethew DSS checksum can be enabwed.

	DSS checksum can be enabwed if the vawue is nonzewo. This is a
	pew-namespace sysctw.

	Defauwt: 0

awwow_join_initiaw_addw_powt - BOOWEAN
	Awwow peews to send join wequests to the IP addwess and powt numbew used
	by the initiaw subfwow if the vawue is 1. This contwows a fwag that is
	sent to the peew at connection time, and whethew such join wequests awe
	accepted ow denied.

	Joins to addwesses advewtised with ADD_ADDW awe not affected by this
	vawue.

	This is a pew-namespace sysctw.

	Defauwt: 1

pm_type - INTEGEW
	Set the defauwt path managew type to use fow each new MPTCP
	socket. In-kewnew path management wiww contwow subfwow
	connections and addwess advewtisements accowding to
	pew-namespace vawues configuwed ovew the MPTCP netwink
	API. Usewspace path management puts pew-MPTCP-connection subfwow
	connection decisions and addwess advewtisements undew contwow of
	a pwiviweged usewspace pwogwam, at the cost of mowe netwink
	twaffic to pwopagate aww of the wewated events and commands.

	This is a pew-namespace sysctw.

	* 0 - In-kewnew path managew
	* 1 - Usewspace path managew

	Defauwt: 0

stawe_woss_cnt - INTEGEW
	The numbew of MPTCP-wevew wetwansmission intewvaws with no twaffic and
	pending outstanding data on a given subfwow wequiwed to decwawe it stawe.
	The packet scheduwew ignowes stawe subfwows.
	A wow stawe_woss_cnt  vawue awwows fow fast active-backup switch-ovew,
	an high vawue maximize winks utiwization on edge scenawios e.g. wossy
	wink with high BEW ow peew pausing the data pwocessing.

	This is a pew-namespace sysctw.

	Defauwt: 4

scheduwew - STWING
	Sewect the scheduwew of youw choice.

	Suppowt fow sewection of diffewent scheduwews. This is a pew-namespace
	sysctw.

	Defauwt: "defauwt"
