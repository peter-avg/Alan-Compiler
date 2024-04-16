#!/bin/bash

llc out.ll -o out.s;
gcc -o a.out out.s library.a;
