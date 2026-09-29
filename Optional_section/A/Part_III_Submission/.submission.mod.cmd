savedcmd_submission.mod := printf '%s\n'   submission.o | awk '!x[$$0]++ { print("./"$$0) }' > submission.mod
