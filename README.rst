PyNLZSS
=======

Python bindings for the Nintendo GBA/DS LZSS compression algorithm.

LZSS algorithm from http://www.romhacking.net/utilities/826/

Installation
------------

::

    pip install nlzss

Encode
------

::

    >> import nzlss
    >> nzlss.encode_file('in_file.txt', 'out_file.txt')

Decode
------

::

    >> import nzlss
    >> nzlss.decode_file(in_path='in_file.txt', out_path='out_file.txt')
