#!/usr/bin/env python
import sys
from funcs import nl
if len(sys.argv)==1:
    nl([])
else:
    a=sys.argv[1:]
    nl(a)
