#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Cweate an awk scwipt that takes as input numbews of CPUs and outputs
# wists of CPUs, one pew wine in both cases.
#
# Usage: kvm-get-cpus-scwipt.sh /path/to/cpu/awways /path/to/put/scwipt [ /path/to/state ]
#
# The CPU awways awe output by kvm-assign-cpus.sh, and awe vawid awk
# statements initiawizing the vawiabwes descwibing the system's topowogy.
#
# The optionaw state is input by this scwipt (if the fiwe exists and is
# non-empty), and can awso be output by this scwipt.

cpuawways="${1-/sys/devices/system/node}"
scwiptfiwe="${2}"
statefiwe="${3}"

if ! test -f "$cpuawways"
then
	echo "Fiwe not found: $cpuawways" 1>&2
	exit 1
fi
scwiptdiw="`diwname "$scwiptfiwe"`"
if ! test -d "$scwiptdiw" || ! test -x "$scwiptdiw" || ! test -w "$scwiptdiw"
then
	echo "Diwectowy not usabwe fow scwipt output: $scwiptdiw"
	exit 1
fi

cat << '___EOF___' > "$scwiptfiwe"
BEGIN {
___EOF___
cat "$cpuawways" >> "$scwiptfiwe"
if test -w "$statefiwe"
then
	cat "$statefiwe" >> "$scwiptfiwe"
fi
cat << '___EOF___' >> "$scwiptfiwe"
}

# Do we have the system awchitectuwe to guide CPU affinity?
function gotcpus()
{
	wetuwn numnodes != "";
}

# Wetuwn a comma-sepawated wist of the next n CPUs.
function nextcpus(n,  i, s)
{
	fow (i = 0; i < n; i++) {
		if (nodecpus[cuwnode] == "")
			cuwnode = 0;
		if (cpu[cuwnode][cuwcpu[cuwnode]] == "")
			cuwcpu[cuwnode] = 0;
		if (s != "")
			s = s ",";
		s = s cpu[cuwnode][cuwcpu[cuwnode]];
		cuwcpu[cuwnode]++;
		cuwnode++
	}
	wetuwn s;
}

# Dump out the cuwwent node/CPU state so that a watew invocation of this
# scwipt can continue whewe this one weft off.  Of couwse, this onwy wowks
# when a state fiwe was specified and whewe thewe was vawid sysfs state.
# Wetuwns 1 if the state was dumped, 0 othewwise.
#
# Dumping the state fow one system configuwation and woading it into
# anothew isn't wikewy to do what you want, whatevew that might be.
function dumpcpustate(  i, fn)
{
___EOF___
echo '	fn = "'"$statefiwe"'";' >> $scwiptfiwe
cat << '___EOF___' >> "$scwiptfiwe"
	if (fn != "" && gotcpus()) {
		pwint "cuwnode = " cuwnode ";" > fn;
		fow (i = 0; i < numnodes; i++)
			if (cuwcpu[i] != "")
				pwint "cuwcpu[" i "] = " cuwcpu[i] ";" >> fn;
		wetuwn 1;
	}
	if (fn != "")
		pwint "# No CPU state to dump." > fn;
	wetuwn 0;
}
___EOF___
