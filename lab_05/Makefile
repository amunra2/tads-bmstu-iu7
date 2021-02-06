CC := gcc

CFILES_DIR := ./src
CFILES := $(wildcard $(CFILES_DIR)/*.c)
INC_DIR := ./inc
INCLUDES := $(wildcard $(INC_DIR)/*.h)

OBJ_DIR := ./out
OBJECTS := $(CFILES:$(CFILES_DIR)/%.c=$(OBJ_DIR)/%.o)
FLAGS := -std=c99 -Wall -Werror -pedantic


APP = app.exe


.PHONY : clean push run unit


$(APP): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lm


$(OBJ_DIR):
	@mkdir -p $@


$(OBJ_DIR)/%.o: $(CFILES_DIR)/%.c $(INCLUDES) $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@


run: $(APP)
	clear
	./app.exe
	

debug: $(APP)
	valgrind --leak-check=full --leak-resolution=med --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./app.exe

clean:
	@rm -rf $(OBJ_DIR) *.exe *.txt; \
	echo "Clean OK"
 

push:
	@git add . ; \
	echo "Input reason of a commit:"; \
	read MSG; \
	git commit -m "$$MSG"; \
	echo "Commit added with message:" $$MSG; \
	git push; \
	echo "Pushed OK"


create_dirs:
	@mkdir -p $(CFILES_DIR) ;\
	cd ./$(CFILES_DIR) ;\
	touch main.c ;\
	cd .. ;\
	mkdir -p $(INC_DIR) ;\
	cd ./$(INC_DIR) ;\
	touch main_inc.h ;\
	touch structs.h ;\
	cd .. ;\
	mkdir -p docs ;\
	echo "Created dirs"
