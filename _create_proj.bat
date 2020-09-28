@echo off

@REM force build right now because wildcard hashing is somehow broken
py qpc\qpc.py -f -a "scripts/bruhsweeper.qpc" -g visual_studio cmake -mf bruhsweeper

pause

