savedcmd_/home/moafk/LDD/helloKernel/helloKernel.mod := printf '%s\n'   helloKernel.o | awk '!x[$$0]++ { print("/home/moafk/LDD/helloKernel/"$$0) }' > /home/moafk/LDD/helloKernel/helloKernel.mod
