cmd_/home/pi/working/term_project/drivers/motordriver.mod := printf '%s\n'   motordriver.o | awk '!x[$$0]++ { print("/home/pi/working/term_project/drivers/"$$0) }' > /home/pi/working/term_project/drivers/motordriver.mod
