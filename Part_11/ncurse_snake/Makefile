
#-------Local build information-------------------------------------------------
LBIN    = bin
LOBJ    = obj
LSRC    = src

#-------Compile-----------------------------------------------------------------
CC	    = gcc -g -m32
EXE	    = nsnake
CDEBUG	=
CFLAGS	= $(CDEBUG) -Wall
LIBS	= -lncurses
OBJ	    = $(LOBJ)/fruit.o      \
          $(LOBJ)/main.o       \
          $(LOBJ)/player.o     \
          $(LOBJ)/nsnake.o     \
          $(LOBJ)/engine.o     \
          $(LOBJ)/hscores.o    \

SCORE	= -DSCORE_PATH=\"$(SCORE_PATH)\"


#-------Verbose Mode------------------------------------------------------------

ifndef V
MUTE = @
endif


#-------Standard Makes----------------------------------------------------------

all: $(EXE)
	@echo "* Ready to Play!"

#	To make the executable file
$(EXE): $(OBJ)
	@echo "* Linking..."
	$(MUTE)$(CC) $(OBJ) -o $(LBIN)/$(EXE) $(LIBS)

#	All the object files
$(LOBJ)/%.o: $(LSRC)/%.c
	@echo "* Compiling $<..."
	$(MUTE)$(CC) $(CFLAGS) $< -c -o $@ $(SCORE)


#-------Compile or clean up the program------------------------------------------
run: all
	@echo "* Running..."
	$(MUTE)./$(LBIN)/$(EXE)

memcheck: all
	   @echo "* Running memleak check..."
	   $(MUTE) valgrind ./$(LBIN)/$(EXE)

clean:
	@echo "* Cleaning..."
	$(MUTE)rm $(VTAG) -f $(LOBJ)/*.o
	$(MUTE)rm $(VTAG) -f $(LBIN)/*


#------------------------------------------------------------------------------
