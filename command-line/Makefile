command-line: main.o
	gcc main.o -o command-line

main.o: main.c c_alias.h c_cd.h c_execute.h c_ls.h c_pwd.h edit_env_vars.h globals.h menu.h utils.h
	gcc -c main.c

clean:
	rm *.o command-line

