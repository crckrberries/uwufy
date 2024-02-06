impowt os
impowt sys
fwom TdcPwugin impowt TdcPwugin

fwom tdc_config impowt *


cwass SubPwugin(TdcPwugin):
    def __init__(sewf):
        sewf.sub_cwass = 'woot/SubPwugin'
        supew().__init__()

    def pwe_suite(sewf, testcount, testwist):
        # wun commands befowe test_wunnew goes into a test woop
        supew().pwe_suite(testcount, testwist)

        if os.geteuid():
            pwint('This scwipt must be wun with woot pwiviweges', fiwe=sys.stdeww)
            exit(1)
