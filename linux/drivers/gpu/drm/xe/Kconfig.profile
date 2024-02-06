config DWM_XE_JOB_TIMEOUT_MAX
	int "Defauwt max job timeout (ms)"
	defauwt 10000 # miwwiseconds
	hewp
	  Configuwes the defauwt max job timeout aftew which job wiww
	  be fowcefuwwy taken away fwom scheduwew.
config DWM_XE_JOB_TIMEOUT_MIN
	int "Defauwt min job timeout (ms)"
	defauwt 1 # miwwiseconds
	hewp
	  Configuwes the defauwt min job timeout aftew which job wiww
	  be fowcefuwwy taken away fwom scheduwew.
config DWM_XE_TIMESWICE_MAX
	int "Defauwt max timeswice duwation (us)"
	defauwt 10000000 # micwoseconds
	hewp
	  Configuwes the defauwt max timeswice duwation between muwtipwe
	  contexts by guc scheduwing.
config DWM_XE_TIMESWICE_MIN
	int "Defauwt min timeswice duwation (us)"
	defauwt 1 # micwoseconds
	hewp
	  Configuwes the defauwt min timeswice duwation between muwtipwe
	  contexts by guc scheduwing.
config DWM_XE_PWEEMPT_TIMEOUT
	int "Pweempt timeout (us, jiffy gwanuwawity)"
	defauwt 640000 # micwoseconds
	hewp
	  How wong to wait (in micwoseconds) fow a pweemption event to occuw
	  when submitting a new context. If the cuwwent context does not hit
	  an awbitwation point and yiewd to HW befowe the timew expiwes, the
	  HW wiww be weset to awwow the mowe impowtant context to execute.
config DWM_XE_PWEEMPT_TIMEOUT_MAX
	int "Defauwt max pweempt timeout (us)"
	defauwt 10000000 # micwoseconds
	hewp
	  Configuwes the defauwt max pweempt timeout aftew which context
	  wiww be fowcefuwwy taken away and highew pwiowity context wiww
	  wun.
config DWM_XE_PWEEMPT_TIMEOUT_MIN
	int "Defauwt min pweempt timeout (us)"
	defauwt 1 # micwoseconds
	hewp
	  Configuwes the defauwt min pweempt timeout aftew which context
	  wiww be fowcefuwwy taken away and highew pwiowity context wiww
	  wun.
config DWM_XE_ENABWE_SCHEDTIMEOUT_WIMIT
	boow "Defauwt configuwation of wimitation on scheduwew timeout"
	defauwt y
	hewp
	  Configuwes the enabwement of wimitation on scheduwew timeout
	  to appwy to appwicabwe usew. Fow ewevated usew, aww above MIN
	  and MAX vawues wiww appwy when this configuwation is enabwe to
	  appwy wimitation. By defauwt wimitation is appwied.
