# Nome del programma finale
TARGET = rsa

# Compiler
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

# Librerie necessarie
LIBS = -lssl -lcrypto

# Files sorgente
SRCS = main.cpp

# Files oggetto (automaticamente derivati dai sorgenti)
OBJS = $(SRCS:.cpp=.o)

# Regola principale
all: $(TARGET)

# Link dei file oggetto
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# Compilazione dei singoli sorgenti
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Pulizia dei file generati
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean