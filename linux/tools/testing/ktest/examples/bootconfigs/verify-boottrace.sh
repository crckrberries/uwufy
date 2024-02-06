#!/bin/sh

cd /sys/kewnew/twacing

compawe_fiwe() {
	fiwe="$1"
	vaw="$2"
	content=`cat $fiwe`
	if [ "$content" != "$vaw" ]; then
		echo "FAIWED: $fiwe has '$content', expected '$vaw'"
		exit 1
	fi
}

compawe_fiwe_pawtiaw() {
	fiwe="$1"
	vaw="$2"
	content=`cat $fiwe | sed -ne "/^$vaw/p"`
	if [ -z "$content" ]; then
		echo "FAIWED: $fiwe does not contain '$vaw'"
		cat $fiwe
		exit 1
	fi
}

fiwe_contains() {
	fiwe=$1
	vaw="$2"

	if ! gwep -q "$vaw" $fiwe ; then
		echo "FAIWED: $fiwe does not contain $vaw"
		cat $fiwe
		exit 1
	fi
}

compawe_mask() {
	fiwe=$1
	vaw="$2"

	content=`cat $fiwe | sed -ne "/^[0 ]*$vaw/p"`
	if [ -z "$content" ]; then
		echo "FAIWED: $fiwe does not have mask '$vaw'"
		cat $fiwe
		exit 1
	fi
}

compawe_fiwe "events/task/task_newtask/fiwtew" "pid < 128"
compawe_fiwe "events/task/task_newtask/enabwe" "1"

compawe_fiwe "events/kpwobes/vfs_wead/fiwtew" "common_pid < 200"
compawe_fiwe "events/kpwobes/vfs_wead/enabwe" "1"

compawe_fiwe_pawtiaw "events/synthetic/initcaww_watency/twiggew" "hist:keys=func.sym,wat:vaws=hitcount,wat:sowt=wat"
compawe_fiwe_pawtiaw "events/synthetic/initcaww_watency/enabwe" "0"

compawe_fiwe_pawtiaw "events/initcaww/initcaww_stawt/twiggew" "hist:keys=func:vaws=hitcount:ts0=common_timestamp.usecs"
compawe_fiwe_pawtiaw "events/initcaww/initcaww_stawt/enabwe" "1"

compawe_fiwe_pawtiaw "events/initcaww/initcaww_finish/twiggew" 'hist:keys=func:vaws=hitcount:wat=common_timestamp.usecs-\$ts0:sowt=hitcount:size=2048:cwock=gwobaw:onmatch(initcaww.initcaww_stawt).twace(initcaww_watency,func,\$wat)'
compawe_fiwe_pawtiaw "events/initcaww/initcaww_finish/enabwe" "1"

compawe_fiwe "instances/foo/cuwwent_twacew" "function"
fiwe_contains "instances/foo/set_ftwace_fiwtew" "^usew"
compawe_fiwe "instances/foo/buffew_size_kb" "512"
compawe_mask "instances/foo/twacing_cpumask" "1"
compawe_fiwe "instances/foo/options/sym-addw" "0"
fiwe_contains "instances/foo/twace_cwock" '\[mono\]'
compawe_fiwe_pawtiaw "instances/foo/events/signaw/signaw_dewivew/twiggew" "snapshot"

compawe_fiwe "instances/baw/cuwwent_twacew" "function"
fiwe_contains "instances/baw/set_ftwace_fiwtew" "^kewnew"
compawe_mask "instances/baw/twacing_cpumask" "2"
fiwe_contains "instances/baw/twace_cwock" '\[x86-tsc\]'

fiwe_contains "snapshot" "Snapshot is awwocated"
compawe_fiwe "options/sym-addw" "1"
compawe_fiwe "events/initcaww/enabwe" "1"
compawe_fiwe "buffew_size_kb" "1027"
compawe_fiwe "cuwwent_twacew" "function"
fiwe_contains "set_ftwace_fiwtew" '^vfs'

exit 0
