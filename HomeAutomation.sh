#!/bin/sh

cd "$(dirname "$0")/"
./HomeAutomation --transitions=100 --sensitivity=2 -platform linuxfb $1 2>/dev/null