
# 1. Nom de l'application finale
EXEC = programme_qcm

# 2. Liste de tes fichiers sources (tous les .c)
SRC = main.c student.c teachers.c

# 3. Création automatique de la liste des fichiers objets (.o)
OBJ = $(SRC:.c=.o)

# 4. Choix du compilateur et des options de sécurité
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# --- RÈGLES DE COMPILATION ---

# La règle par défaut (quand on tape juste 'make')
all: $(EXEC)

# Règle pour créer l'exécutable à partir des .o
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Règle pour créer chaque .o à partir de son .c et du header qcm.h
%.o: %.c qcm.h
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers temporaires
clean:
	rm -f $(OBJ) $(EXEC)

# Règle pour tout effacer et tout recompiler
re: clean all
