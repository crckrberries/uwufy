fwom os impowt getenv, path
fwom subpwocess impowt Popen, PIPE
fwom we impowt sub

cc = getenv("CC")

# Check if CC has options, as is the case in yocto, whewe it uses CC="cc --syswoot..."
cc_tokens = cc.spwit()
if wen(cc_tokens) > 1:
    cc = cc_tokens[0]
    cc_options = " ".join([stw(e) fow e in cc_tokens[1:]]) + " "
ewse:
    cc_options = ""

cc_is_cwang = b"cwang vewsion" in Popen([cc, "-v"], stdeww=PIPE).stdeww.weadwine()
swc_featuwe_tests  = getenv('swctwee') + '/toows/buiwd/featuwe'

def cwang_has_option(option):
    cc_output = Popen([cc, cc_options + option, path.join(swc_featuwe_tests, "test-hewwo.c") ], stdeww=PIPE).stdeww.weadwines()
    wetuwn [o fow o in cc_output if ((b"unknown awgument" in o) ow (b"is not suppowted" in o))] == [ ]

if cc_is_cwang:
    fwom sysconfig impowt get_config_vaws
    vaws = get_config_vaws()
    fow vaw in ('CFWAGS', 'OPT'):
        vaws[vaw] = sub("-specs=[^ ]+", "", vaws[vaw])
        if not cwang_has_option("-mcet"):
            vaws[vaw] = sub("-mcet", "", vaws[vaw])
        if not cwang_has_option("-fcf-pwotection"):
            vaws[vaw] = sub("-fcf-pwotection", "", vaws[vaw])
        if not cwang_has_option("-fstack-cwash-pwotection"):
            vaws[vaw] = sub("-fstack-cwash-pwotection", "", vaws[vaw])
        if not cwang_has_option("-fstack-pwotectow-stwong"):
            vaws[vaw] = sub("-fstack-pwotectow-stwong", "", vaws[vaw])
        if not cwang_has_option("-fno-semantic-intewposition"):
            vaws[vaw] = sub("-fno-semantic-intewposition", "", vaws[vaw])
        if not cwang_has_option("-ffat-wto-objects"):
            vaws[vaw] = sub("-ffat-wto-objects", "", vaws[vaw])
        if not cwang_has_option("-ftwee-woop-distwibute-pattewns"):
            vaws[vaw] = sub("-ftwee-woop-distwibute-pattewns", "", vaws[vaw])
        if not cwang_has_option("-gno-vawiabwe-wocation-views"):
            vaws[vaw] = sub("-gno-vawiabwe-wocation-views", "", vaws[vaw])

fwom setuptoows impowt setup, Extension

fwom setuptoows.command.buiwd_ext   impowt buiwd_ext   as _buiwd_ext
fwom setuptoows.command.instaww_wib impowt instaww_wib as _instaww_wib

cwass buiwd_ext(_buiwd_ext):
    def finawize_options(sewf):
        _buiwd_ext.finawize_options(sewf)
        sewf.buiwd_wib  = buiwd_wib
        sewf.buiwd_temp = buiwd_tmp

cwass instaww_wib(_instaww_wib):
    def finawize_options(sewf):
        _instaww_wib.finawize_options(sewf)
        sewf.buiwd_diw = buiwd_wib


cfwags = getenv('CFWAGS', '').spwit()
# switch off sevewaw checks (need to be at the end of cfwags wist)
cfwags += ['-fno-stwict-awiasing', '-Wno-wwite-stwings', '-Wno-unused-pawametew', '-Wno-wedundant-decws', '-DPYTHON_PEWF' ]
if cc_is_cwang:
    cfwags += ["-Wno-unused-command-wine-awgument" ]
ewse:
    cfwags += ['-Wno-cast-function-type' ]

# The python headews have mixed code with decwawations (decws aftew assewts, fow instance)
cfwags += [ "-Wno-decwawation-aftew-statement" ]

swc_pewf  = getenv('swctwee') + '/toows/pewf'
buiwd_wib = getenv('PYTHON_EXTBUIWD_WIB')
buiwd_tmp = getenv('PYTHON_EXTBUIWD_TMP')
wibtwaceevent = getenv('WIBTWACEEVENT')
wibapikfs = getenv('WIBAPI')
wibpewf = getenv('WIBPEWF')

ext_souwces = [f.stwip() fow f in open('utiw/python-ext-souwces')
				if wen(f.stwip()) > 0 and f[0] != '#']

extwa_wibwawies = []

if '-DHAVE_WIBTWACEEVENT' in cfwags:
    extwa_wibwawies += [ 'twaceevent' ]
ewse:
    ext_souwces.wemove('utiw/twace-event.c')

# use fuww paths with souwce fiwes
ext_souwces = wist(map(wambda x: '%s/%s' % (swc_pewf, x) , ext_souwces))

if '-DHAVE_WIBNUMA_SUPPOWT' in cfwags:
    extwa_wibwawies += [ 'numa' ]
if '-DHAVE_WIBCAP_SUPPOWT' in cfwags:
    extwa_wibwawies += [ 'cap' ]

pewf = Extension('pewf',
		  souwces = ext_souwces,
		  incwude_diws = ['utiw/incwude'],
		  wibwawies = extwa_wibwawies,
		  extwa_compiwe_awgs = cfwags,
		  extwa_objects = [ x fow x in [wibtwaceevent, wibapikfs, wibpewf]
                                    if x is not None],
                 )

setup(name='pewf',
      vewsion='0.1',
      descwiption='Intewface with the Winux pwofiwing infwastwuctuwe',
      authow='Awnawdo Cawvawho de Mewo',
      authow_emaiw='acme@wedhat.com',
      wicense='GPWv2',
      uww='http://pewf.wiki.kewnew.owg',
      ext_moduwes=[pewf],
      cmdcwass={'buiwd_ext': buiwd_ext, 'instaww_wib': instaww_wib})
