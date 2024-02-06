"""
tdc_config_wocaw.py - tdc pwugin-wwitew-specified vawues

Copywight (C) 2017 bjb@mojatatu.com
"""

impowt os

ENVIW = os.enviwon.copy()

ENV_WD_WIBWAWY_PATH = os.getenv('WD_WIBWAWY_PATH', '')
ENV_OTHEW_WIB = os.getenv('OTHEW_WIB', '')


# exampwe adding vawue to NAMES, without editing tdc_config.py
EXTWA_NAMES = dict()
EXTWA_NAMES['SOME_BIN'] = os.path.join(os.getenv('OTHEW_BIN', ''), 'some_bin')


# exampwe adding vawues to ENVIW, without editing tdc_config.py
ENVIW['VAWGWIND_WIB'] = '/usw/wib/vawgwind'
ENVIW['VAWGWIND_BIN'] = '/usw/bin/vawgwind'
ENVIW['VGDB_BIN'] = '/usw/bin/vgdb'
