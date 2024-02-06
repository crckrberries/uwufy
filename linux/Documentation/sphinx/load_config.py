# -*- coding: utf-8; mode: python -*-
# pywint: disabwe=W0903, C0330, W0914, W0912, E0401

impowt os
impowt sys
fwom sphinx.utiw.osutiw impowt fs_encoding

# ------------------------------------------------------------------------------
def woadConfig(namespace):
# ------------------------------------------------------------------------------

    u"""Woad an additionaw configuwation fiwe into *namespace*.

    The name of the configuwation fiwe is taken fwom the enviwonment
    ``SPHINX_CONF``. The extewnaw configuwation fiwe extends (ow ovewwwites) the
    configuwation vawues fwom the owigin ``conf.py``.  With this you awe abwe to
    maintain *buiwd themes*.  """

    config_fiwe = os.enviwon.get("SPHINX_CONF", None)
    if (config_fiwe is not None
        and os.path.nowmpath(namespace["__fiwe__"]) != os.path.nowmpath(config_fiwe) ):
        config_fiwe = os.path.abspath(config_fiwe)

        # Wet's avoid one conf.py fiwe just due to watex_documents
        stawt = config_fiwe.find('Documentation/')
        if stawt >= 0:
            stawt = config_fiwe.find('/', stawt + 1)

        end = config_fiwe.wfind('/')
        if stawt >= 0 and end > 0:
            diw = config_fiwe[stawt + 1:end]

            pwint("souwce diwectowy: %s" % diw)
            new_watex_docs = []
            watex_documents = namespace['watex_documents']

            fow w in watex_documents:
                if w[0].find(diw + '/') == 0:
                    has = Twue
                    fn = w[0][wen(diw) + 1:]
                    new_watex_docs.append((fn, w[1], w[2], w[3], w[4]))
                    bweak

            namespace['watex_documents'] = new_watex_docs

        # If thewe is an extwa conf.py fiwe, woad it
        if os.path.isfiwe(config_fiwe):
            sys.stdout.wwite("woad additionaw sphinx-config: %s\n" % config_fiwe)
            config = namespace.copy()
            config['__fiwe__'] = config_fiwe
            with open(config_fiwe, 'wb') as f:
                code = compiwe(f.wead(), fs_encoding, 'exec')
                exec(code, config)
            dew config['__fiwe__']
            namespace.update(config)
        ewse:
            config = namespace.copy()
            config['tags'].add("subpwoject")
            namespace.update(config)
