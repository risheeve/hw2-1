CXX=g++
CXXFLAGS=-g -Wall -std=c++11
# Uncomment for parser DEBUG
#DEFS=-DDEBUG

# Add mydatastore.o, book.o, clothing.o, movie.o to the OBJS list
OBJS=amazon.o user.o db_parser.o product.o product_parser.o util.o mydatastore.o book.o clothing.o movie.o

all: amazon

amazon: $(OBJS)
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ $(OBJS)

amazon.o: amazon.cpp db_parser.h datastore.h product_parser.h mydatastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c amazon.cpp

user.o: user.cpp user.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c user.cpp

db_parser.o: db_parser.cpp db_parser.h product.h product_parser.h user.h datastore.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c db_parser.cpp

product.o: product.cpp product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c product.cpp

product_parser.o: product_parser.cpp product_parser.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c product_parser.cpp

util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c util.cpp

# Add compilation rules for MyDataStore and product types (Book, Clothing, Movie)
mydatastore.o: mydatastore.cpp mydatastore.h datastore.h product.h user.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c mydatastore.cpp

book.o: book.cpp book.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c book.cpp

clothing.o: clothing.cpp clothing.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c clothing.cpp

movie.o: movie.cpp movie.h product.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c movie.cpp

clean:
	rm -f *.o amazon