#!/usr/bin/env python
import wrap
import numpy

z1 = numpy.zeros((5,6), dtype=float)
z2 = numpy.zeros((4,3), dtype=float)
wrap.fill1(z1)
wrap.fill2(z2)
print z1
print z2

