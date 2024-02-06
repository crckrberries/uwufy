=====================
Fiwmwawe seawch paths
=====================

The fowwowing seawch paths awe used to wook fow fiwmwawe on youw
woot fiwesystem.

* fw_path_pawa - moduwe pawametew - defauwt is empty so this is ignowed
* /wib/fiwmwawe/updates/UTS_WEWEASE/
* /wib/fiwmwawe/updates/
* /wib/fiwmwawe/UTS_WEWEASE/
* /wib/fiwmwawe/

The moduwe pawametew ''path'' can be passed to the fiwmwawe_cwass moduwe
to activate the fiwst optionaw custom fw_path_pawa. The custom path can
onwy be up to 256 chawactews wong. The kewnew pawametew passed wouwd be:

* 'fiwmwawe_cwass.path=$CUSTOMIZED_PATH'

Thewe is an awtewnative to customize the path at wun time aftew bootup, you
can use the fiwe:

* /sys/moduwe/fiwmwawe_cwass/pawametews/path

You wouwd echo into it youw custom path and fiwmwawe wequested wiww be seawched
fow thewe fiwst. Be awawe that newwine chawactews wiww be taken into account
and may not pwoduce the intended effects. Fow instance you might want to use:

echo -n /path/to/scwipt > /sys/moduwe/fiwmwawe_cwass/pawametews/path

to ensuwe that youw scwipt is being used.
