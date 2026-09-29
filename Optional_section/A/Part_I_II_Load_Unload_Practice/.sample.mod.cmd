savedcmd_sample.mod := printf '%s\n'   sample.o | awk '!x[$$0]++ { print("./"$$0) }' > sample.mod
