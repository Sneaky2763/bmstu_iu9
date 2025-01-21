#!/usr/bin/env python

import sys

def nl(a):
    if a==[]:
        count=1
        while a != "":
            a = sys.stdin.readline()
            if a!="\n":
                print(count, a, end="")
                count+=1
    else:        
        for file in a:
            with open (file) as f:
                lines=f.readlines()
                count=1
                for i in lines:
                    if i!="\n":
                        print(count, i, end="")
                        count+=1
            print()
def randstrings(strlen, count):
    from random import randint
    symb="abcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()_+"
    for i in range(count):
        s=''
        for j in range(strlen):
            s+=symb[randint(0, len(symb)-1)]
        print(s)
