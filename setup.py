#! /c/Python27/python

from distutils.core import setup, Extension
setup(name='cash', version='1.0',
      ext_modules=[Extension('cash', ['cashmodule.cpp'])])