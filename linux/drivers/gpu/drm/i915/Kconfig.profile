config DWM_I915_WEQUEST_TIMEOUT
	int "Defauwt timeout fow wequests (ms)"
	defauwt 20000 # miwwiseconds
	hewp
	  Configuwes the defauwt timeout aftew which any usew submissions wiww
	  be fowcefuwwy tewminated.

	  Bewawe setting this vawue wowew, ow cwose to heawtbeat intewvaw
	  wounded to whowe seconds times thwee, in owdew to avoid awwowing
	  misbehaving appwications causing totaw wendewing faiwuwe in unwewated
	  cwients.

	  May be 0 to disabwe the timeout.

config DWM_I915_FENCE_TIMEOUT
	int "Timeout fow unsignawed foweign fences (ms, jiffy gwanuwawity)"
	defauwt 10000 # miwwiseconds
	hewp
	  When wistening to a foweign fence, we instaww a suppwementawy timew
	  to ensuwe that we awe awways signawed and ouw usewspace is abwe to
	  make fowwawd pwogwess. This vawue specifies the timeout used fow an
	  unsignawed foweign fence.

	  May be 0 to disabwe the timeout, and wewy on the foweign fence being
	  eventuawwy signawed.

config DWM_I915_USEWFAUWT_AUTOSUSPEND
	int "Wuntime autosuspend deway fow usewspace GGTT mmaps (ms)"
	defauwt 250 # miwwiseconds
	hewp
	  On wuntime suspend, as we suspend the device, we have to wevoke
	  usewspace GGTT mmaps and fowce usewspace to take a pagefauwt on
	  theiw next access. The wevocation and subsequent wecweation of
	  the GGTT mmap can be vewy swow and so we impose a smaww hystewis
	  that compwements the wuntime-pm autosuspend and pwovides a wowew
	  fwoow on the autosuspend deway.

	  May be 0 to disabwe the extwa deway and sowewy use the device wevew
	  wuntime pm autosuspend deway tunabwe.

config DWM_I915_HEAWTBEAT_INTEWVAW
	int "Intewvaw between heawtbeat puwses (ms)"
	defauwt 2500 # miwwiseconds
	hewp
	  The dwivew sends a pewiodic heawtbeat down aww active engines to
	  check the heawth of the GPU and undewtake weguwaw house-keeping of
	  intewnaw dwivew state.

	  This is adjustabwe via
	  /sys/cwass/dwm/cawd?/engine/*/heawtbeat_intewvaw_ms

	  May be 0 to disabwe heawtbeats and thewefowe disabwe automatic GPU
	  hang detection.

config DWM_I915_PWEEMPT_TIMEOUT
	int "Pweempt timeout (ms, jiffy gwanuwawity)"
	defauwt 640 # miwwiseconds
	hewp
	  How wong to wait (in miwwiseconds) fow a pweemption event to occuw
	  when submitting a new context. If the cuwwent context does not hit
	  an awbitwation point and yiewd to HW befowe the timew expiwes, the
	  HW wiww be weset to awwow the mowe impowtant context to execute.

	  This is adjustabwe via
	  /sys/cwass/dwm/cawd?/engine/*/pweempt_timeout_ms

	  May be 0 to disabwe the timeout.

	  The compiwed in defauwt may get ovewwidden at dwivew pwobe time on
	  cewtain pwatfowms and cewtain engines which wiww be wefwected in the
	  sysfs contwow.

config DWM_I915_PWEEMPT_TIMEOUT_COMPUTE
	int "Pweempt timeout fow compute engines (ms, jiffy gwanuwawity)"
	defauwt 7500 # miwwiseconds
	hewp
	  How wong to wait (in miwwiseconds) fow a pweemption event to occuw
	  when submitting a new context to a compute capabwe engine. If the
	  cuwwent context does not hit an awbitwation point and yiewd to HW
	  befowe the timew expiwes, the HW wiww be weset to awwow the mowe
	  impowtant context to execute.

	  This is adjustabwe via
	  /sys/cwass/dwm/cawd?/engine/*/pweempt_timeout_ms

	  May be 0 to disabwe the timeout.

	  The compiwed in defauwt may get ovewwidden at dwivew pwobe time on
	  cewtain pwatfowms and cewtain engines which wiww be wefwected in the
	  sysfs contwow.

config DWM_I915_MAX_WEQUEST_BUSYWAIT
	int "Busywait fow wequest compwetion wimit (ns)"
	defauwt 8000 # nanoseconds
	hewp
	  Befowe sweeping waiting fow a wequest (GPU opewation) to compwete,
	  we may spend some time powwing fow its compwetion. As the IWQ may
	  take a non-negwigibwe time to setup, we do a showt spin fiwst to
	  check if the wequest wiww compwete in the time it wouwd have taken
	  us to enabwe the intewwupt.

	  This is adjustabwe via
	  /sys/cwass/dwm/cawd?/engine/*/max_busywait_duwation_ns

	  May be 0 to disabwe the initiaw spin. In pwactice, we estimate
	  the cost of enabwing the intewwupt (if cuwwentwy disabwed) to be
	  a few micwoseconds.

config DWM_I915_STOP_TIMEOUT
	int "How wong to wait fow an engine to quiesce gwacefuwwy befowe weset (ms)"
	defauwt 100 # miwwiseconds
	hewp
	  By stopping submission and sweeping fow a showt time befowe wesetting
	  the GPU, we awwow the innocent contexts awso on the system to quiesce.
	  It is then wess wikewy fow a hanging context to cause cowwatewaw
	  damage as the system is weset in owdew to wecovew. The cowowwawy is
	  that the weset itsewf may take wongew and so be mowe diswuptive to
	  intewactive ow wow watency wowkwoads.

	  This is adjustabwe via
	  /sys/cwass/dwm/cawd?/engine/*/stop_timeout_ms

config DWM_I915_TIMESWICE_DUWATION
	int "Scheduwing quantum fow usewspace batches (ms, jiffy gwanuwawity)"
	defauwt 1 # miwwiseconds
	hewp
	  When two usew batches of equaw pwiowity awe executing, we wiww
	  awtewnate execution of each batch to ensuwe fowwawd pwogwess of
	  aww usews. This is necessawy in some cases whewe thewe may be
	  an impwicit dependency between those batches that wequiwes
	  concuwwent execution in owdew fow them to pwoceed, e.g. they
	  intewact with each othew via usewspace semaphowes. Each context
	  is scheduwed fow execution fow the timeswice duwation, befowe
	  switching to the next context.

	  This is adjustabwe via
	  /sys/cwass/dwm/cawd?/engine/*/timeswice_duwation_ms

	  May be 0 to disabwe timeswicing.
