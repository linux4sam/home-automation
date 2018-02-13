#!/bin/sh

eval "$DEMO_LEAVE"

cd "$(dirname "$0")/.."
./HomeAutomation --transitions=100 --sensitivity=2 $1 2>/dev/null

eval "$DEMO_ENTER"
