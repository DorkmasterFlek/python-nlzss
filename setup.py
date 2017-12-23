# Python package for Nintendo LZSS encoding/decoding - setup.py
#
# Copyright (C) 2017
#
#     Nintendo LZSS algorithm: CUE
#     Python package: Dorkmaster Flek <dorkmasterflek@gmail.com>
#
# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
# License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

from setuptools import setup, Extension

setup(name="nlzss",
      version='0.1',
      description="Nintendo LZSS compression algorithm",
      author="CUE",
      author_email="",
      maintainer="Dorkmaster Flek",
      maintainer_email="dorkmasterflek@gmail.com",
      license="GNU GPL v3",
      platforms=["Windows", "Linux"],
      ext_modules=[Extension(
            "nlzss",
            sources=["pynlzss.c", "lib/nlzss.c"],
            include_dirs=['./include'],
            language="C")],
      long_description="""A package for decoding / encoding LZSS-compressed data for Nintendo GBA/DS""")
